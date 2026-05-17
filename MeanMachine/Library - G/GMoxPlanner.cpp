#include "GMoxPlanner.hpp"

#include "GMoxPlugPolicy.hpp"
#include "GMoxValidator.hpp"

static GMoxDatum MakeTypeDatum(GMoxType type) {
    GMoxDatum datum;
    datum.mKind = GMoxDatumKind::kType;
    datum.mType = type;
    return datum;
}

static GMoxDatum MakeHotAddDatum() {
    GMoxDatum datum;
    datum.mKind = GMoxDatumKind::kHotAdd;
    return datum;
}

static GMoxDatum MakeHotMulDatum() {
    GMoxDatum datum;
    datum.mKind = GMoxDatumKind::kHotMul;
    return datum;
}

static GMoxDatum MakePlugDatum() {
    GMoxDatum datum;
    datum.mKind = GMoxDatumKind::kPlugKey;
    return datum;
}

static GMoxBlendPlan MakeDefaultBlendPlan() {
    GMoxBlendPlan result;
    result.mRotationA = 7;
    result.mRotationB = 19;
    result.mRotationC = 37;
    result.mRotationD = 53;
    return result;
}

bool GMoxPlanner::Bake(GMoxPlan *plan,
                       const GMoxModel &model,
                       std::string *error) {
    if (plan == nullptr) {
        if (error != nullptr) {
            *error = "GMoxPlanner::Bake received null plan";
        }
        return false;
    }

    if (Configure(plan, error) == false) {
        return false;
    }

    plan->mModel = model;
    plan->mFormat = model.MakeFormat();
    plan->mSkeleton = GMoxSkeleton::Build(model);

    for (GMoxPassPlan *pass : plan->mPasses) {
        delete pass;
    }
    plan->mPasses.clear();

    for (std::size_t i = 0; i < plan->mSkeleton.mPasses.size(); i++) {
        GMoxPassPlan *pass = new GMoxPassPlan();

        pass->mStreamInputBlend = MakeDefaultBlendPlan();
        pass->mSecretInputBlend = MakeDefaultBlendPlan();
        pass->mCrossInputBlend = MakeDefaultBlendPlan();
        pass->mStreamScatterBlend = MakeDefaultBlendPlan();
        pass->mSecretScatterBlend = MakeDefaultBlendPlan();

        if (BuildSeeds(pass, plan->mFormat) == false ||
            BuildForward(pass, plan->mSkeleton.mPasses[i]) == false ||
            BuildCrush(pass) == false ||
            BuildUnwind(pass, plan->mSkeleton.mPasses[i]) == false ||
            BuildCarry(pass) == false) {
            delete pass;

            if (error != nullptr) {
                *error = "GMoxPlanner::Bake failed while building pass";
            }

            return false;
        }

        for (std::size_t groupIndex = 0; groupIndex < pass->mGroups.size(); groupIndex++) {
            GMoxStatementGroup *group = pass->mGroups[groupIndex];

            if (group == nullptr) {
                continue;
            }

            group->mZoneIndex = static_cast<int>(groupIndex);

            for (GMoxStatement *statement : group->mStatements) {
                if (statement != nullptr) {
                    statement->mGroupKind = group->mKind;
                }
            }
        }

        GMoxPlugPolicy plugPolicy;
        plugPolicy.mTapClass = model.mUseHiddenStateAsSaltPlug
            ? GMoxPlugTapClass::kStreamAndIntermediateHidden
            : GMoxPlugTapClass::kStreamOnly;
        plugPolicy.mEnableHiddenStatePlugOnIntermediateRound = model.mUseHiddenStateAsSaltPlug;

        if (plugPolicy.Assign(pass->mGroups, plan->mFormat, i) == false) {
            delete pass;

            if (error != nullptr) {
                *error = "GMoxPlanner::Bake failed plug assignment";
            }

            return false;
        }

        plan->mPasses.push_back(pass);
    }

    return GMoxValidator::Validate(*plan, error);
}

bool GMoxPlanner::Configure(GMoxPlan *plan, std::string *error) {
    if (plan == nullptr) {
        if (error != nullptr) {
            *error = "GMoxPlanner::Configure received null plan";
        }
        return false;
    }

    return true;
}

bool GMoxPlanner::BuildSeeds(GMoxPassPlan *pass, const GMoxFormat &format) {
    if (pass == nullptr) {
        return false;
    }

    std::vector<GMoxType> orbiters = format.Orbiters();
    std::vector<GMoxType> wanderers = format.Wanderers();

    if (orbiters.empty() || wanderers.empty()) {
        return false;
    }

    for (std::size_t i = 0; i < orbiters.size(); i++) {
        GMoxStatement *statement = new GMoxStatement(GMoxStatementKind::kSeed,
                                                     orbiters[i]);

        statement->mDatums.push_back(MakeTypeDatum(wanderers[i % wanderers.size()]));
        statement->mDatums.push_back(MakeTypeDatum(GMoxType::Secret(GMoxSecretKind::kCurrent)));
        statement->mDatums.push_back(MakeHotAddDatum());

        if (i == 1 || i == 2) {
            statement->mDatums.push_back(MakePlugDatum());
        }

        pass->mStatements.push_back(statement);

        GMoxStatementGroup *group = new GMoxStatementGroup(GMoxGroupKind::kSeed);
        group->mStatements.push_back(statement);
        pass->mGroups.push_back(group);
    }

    return true;
}

bool GMoxPlanner::BuildForward(GMoxPassPlan *pass, const GMoxSkeletonPass &skeleton) {
    if (pass == nullptr) {
        return false;
    }

    std::size_t rotateIndex = 0;

    for (const GMoxForwardRound &round : skeleton.mForward) {
        GMoxStatement *lead = new GMoxStatement(GMoxStatementKind::kForwardLead,
                                                round.mLead);
        lead->mDatums.push_back(MakeTypeDatum(round.mLead));
        lead->mDatums.push_back(MakeTypeDatum(round.mSource));
        lead->mDatums.push_back(MakeHotAddDatum());
        lead->mDatums.push_back(MakePlugDatum());

        GMoxStatement *feedback = new GMoxStatement(GMoxStatementKind::kForwardFeedback,
                                                    round.mFeedback);
        feedback->mDatums.push_back(MakeTypeDatum(round.mFeedback));
        feedback->mDatums.push_back(MakeTypeDatum(round.mLead));
        feedback->mDatums.push_back(MakeHotAddDatum());
        feedback->mDatums.push_back(MakePlugDatum());

        GMoxStatement *rotate = new GMoxStatement(GMoxStatementKind::kForwardRotate,
                                                  round.mFeedback);
        rotate->mDatums.push_back(MakeTypeDatum(round.mFeedback));
        rotate->mDatums.push_back(MakeHotMulDatum());
        rotate->mRotationAmount = static_cast<int>(7 + ((rotateIndex * 12) % 56));
        rotateIndex++;

        pass->mStatements.push_back(lead);
        pass->mStatements.push_back(feedback);
        pass->mStatements.push_back(rotate);

        GMoxStatementGroup *group = new GMoxStatementGroup(GMoxGroupKind::kForwardTriplet);
        group->mStatements.push_back(lead);
        group->mStatements.push_back(feedback);
        group->mStatements.push_back(rotate);
        pass->mGroups.push_back(group);
    }

    return true;
}

bool GMoxPlanner::BuildCrush(GMoxPassPlan *pass) {
    if (pass == nullptr) {
        return false;
    }

    GMoxStatement *statement = new GMoxStatement(
        GMoxStatementKind::kCrush,
        GMoxType::Secret(GMoxSecretKind::kCurrent)
    );

    pass->mStatements.push_back(statement);

    GMoxStatementGroup *group = new GMoxStatementGroup(GMoxGroupKind::kCrush);
    group->mStatements.push_back(statement);
    pass->mGroups.push_back(group);

    return true;
}

bool GMoxPlanner::BuildUnwind(GMoxPassPlan *pass, const GMoxSkeletonPass &skeleton) {
    if (pass == nullptr) {
        return false;
    }

    for (std::size_t i = 0; i < skeleton.mBackward.size(); i++) {
        const GMoxBackwardRound &round = skeleton.mBackward[i];

        GMoxStatement *statement = new GMoxStatement(GMoxStatementKind::kUnwind,
                                                     round.mTarget);

        statement->mDatums.push_back(MakeTypeDatum(round.mTarget));

        if (round.mInputA.IsValid()) {
            statement->mDatums.push_back(MakeTypeDatum(round.mInputA));
        }

        if (round.mInputB.IsValid()) {
            statement->mDatums.push_back(MakeTypeDatum(round.mInputB));
        }

        if (round.mInputC.IsValid()) {
            statement->mDatums.push_back(MakeTypeDatum(round.mInputC));
        }

        if ((i & 1U) == 0U || round.mShape == GMoxUnwindShape::kHiddenPlugMix) {
            statement->mDatums.push_back(MakePlugDatum());
        }

        statement->mDatums.push_back(MakeHotMulDatum());

        pass->mStatements.push_back(statement);

        GMoxStatementGroup *group = new GMoxStatementGroup(GMoxGroupKind::kUnwind);
        group->mStatements.push_back(statement);
        pass->mGroups.push_back(group);
    }

    return true;
}

bool GMoxPlanner::BuildCarry(GMoxPassPlan *pass) {
    if (pass == nullptr) {
        return false;
    }
    GMoxStatement *statement = new GMoxStatement(GMoxStatementKind::kCarry, GMoxType::Carry());
    pass->mStatements.push_back(statement);
    GMoxStatementGroup *group = new GMoxStatementGroup(GMoxGroupKind::kCarry);
    group->mStatements.push_back(statement);
    pass->mGroups.push_back(group);
    return true;
}
