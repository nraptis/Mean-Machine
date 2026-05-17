#include "GMoxPrinter.hpp"

#include <iostream>
#include <sstream>

static std::string DatumShortName(const GMoxDatum &datum) {
    switch (datum.mKind) {
        case GMoxDatumKind::kType:
            return datum.mType.Name();

        case GMoxDatumKind::kHotAdd:
            return "hot_add";

        case GMoxDatumKind::kHotMul:
            return "hot_mul";

        case GMoxDatumKind::kLoopKey:
            return "loop_key[lane=" +
                   std::to_string(datum.mSaltLaneIndex) +
                   ", off=" +
                   std::to_string(datum.mOffsetAmount) +
                   "]";

        case GMoxDatumKind::kPlugKey:
            return "plug(" +
                   datum.mPlugTypeA.Name() +
                   ", " +
                   datum.mPlugTypeB.Name() +
                   ")";

        default:
            return "invalid";
    }
}

static std::string StatementExpression(const GMoxStatement &statement) {
    std::string result = statement.mTarget.Name();
    result += " = ";

    for (std::size_t i = 0; i < statement.mDatums.size(); i++) {
        if (i > 0) {
            result += " + ";
        }

        result += DatumShortName(statement.mDatums[i]);
    }

    if (statement.mKind == GMoxStatementKind::kForwardRotate &&
        statement.mRotationAmount >= 0) {
        result += " ; rot=" + std::to_string(statement.mRotationAmount);
    }

    return result;
}

static const char *PatternKindName(GMoxPatternKind kind) {
    switch (kind) {
        case GMoxPatternKind::kRingForward: return "ring_forward";
        case GMoxPatternKind::kStrideForward: return "stride_forward";
        case GMoxPatternKind::kReverseRing: return "reverse_ring";
        case GMoxPatternKind::kLongCross: return "long_cross";
        case GMoxPatternKind::kInterleave: return "interleave";
        case GMoxPatternKind::kFoldback: return "foldback";
        default: return "invalid";
    }
}

static const char *StatementKindName(GMoxStatementKind kind) {
    switch (kind) {
        case GMoxStatementKind::kSeed: return "seed";
        case GMoxStatementKind::kForwardLead: return "forward_lead";
        case GMoxStatementKind::kForwardFeedback: return "forward_feedback";
        case GMoxStatementKind::kForwardRotate: return "forward_rotate";
        case GMoxStatementKind::kCrush: return "crush";
        case GMoxStatementKind::kUnwind: return "unwind";
        case GMoxStatementKind::kCarry: return "carry";
        case GMoxStatementKind::kHiddenPlugPrep: return "hidden_plug_prep";
        default: return "invalid";
    }
}

static const char *GroupKindName(GMoxGroupKind kind) {
    switch (kind) {
        case GMoxGroupKind::kSeed: return "seed";
        case GMoxGroupKind::kForwardTriplet: return "forward_triplet";
        case GMoxGroupKind::kCrush: return "crush";
        case GMoxGroupKind::kUnwind: return "unwind";
        case GMoxGroupKind::kCarry: return "carry";
        case GMoxGroupKind::kHiddenPlug: return "hidden_plug";
        default: return "invalid";
    }
}

static const char *DatumKindName(GMoxDatumKind kind) {
    switch (kind) {
        case GMoxDatumKind::kType: return "type";
        case GMoxDatumKind::kLoopKey: return "loop_key";
        case GMoxDatumKind::kPlugKey: return "plug_key";
        case GMoxDatumKind::kHotAdd: return "hot_add";
        case GMoxDatumKind::kHotMul: return "hot_mul";
        default: return "invalid";
    }
}

static bool PlugUsesHiddenTap(const GMoxDatum &datum) {
    if (datum.mKind != GMoxDatumKind::kPlugKey) {
        return false;
    }

    return datum.mPlugTypeA.IsHiddenState() ||
           datum.mPlugTypeB.IsHiddenState();
}

void GMoxPrinter::Print(const GMoxPlan &plan) {
    Options options;
    Print(plan, options);
}

void GMoxPrinter::Print(const GMoxPlan &plan, const Options &options) {
    std::cout << ToString(plan);
    (void)options;
}

std::string GMoxPrinter::ToString(const GMoxPlan &plan) {
    std::ostringstream out;

    out << "GMoxPlan: " << plan.mModel.mName << "\n";
    out << "  orbiters: " << plan.mFormat.mOrbiterCount << "\n";
    out << "  wanderers: " << plan.mFormat.mWandererCount << "\n";
    out << "  passes: " << plan.mFormat.mPassCount << "\n";
    out << "  hidden_plug: "
        << (plan.mModel.mUseHiddenStateAsSaltPlug ? "enabled" : "disabled")
        << "\n\n";

    for (std::size_t passIndex = 0; passIndex < plan.mPasses.size(); passIndex++) {
        const GMoxPassPlan *pass = plan.mPasses[passIndex];

        if (passIndex < plan.mSkeleton.mPasses.size()) {
            out << "pass " << passIndex
                << " "
                << PatternKindName(plan.mSkeleton.mPasses[passIndex].mPattern)
                << "\n";
        } else {
            out << "pass " << passIndex << "\n";
        }

        if (pass == nullptr) {
            out << "  null pass\n";
            continue;
        }

        for (const GMoxStatementGroup *group : pass->mGroups) {
            if (group == nullptr) {
                out << "  null group\n";
                continue;
            }

            out << "  group[" << group->mZoneIndex << "] "
                << GroupKindName(group->mKind) << "\n";

            for (const GMoxStatement *statement : group->mStatements) {
                if (statement == nullptr) {
                    out << "    null statement\n";
                    continue;
                }
                
                out << "    "
                    << StatementKindName(statement->mKind)
                    << " -> "
                    << StatementExpression(*statement)
                    << "\n";

                out << "    "
                    << StatementKindName(statement->mKind)
                    << " -> "
                    << statement->mTarget.Name();

                if (statement->mRotationAmount >= 0) {
                    out << " rot=" << statement->mRotationAmount;
                }

                out << "\n";

                for (const GMoxDatum &datum : statement->mDatums) {
                    out << "      "
                        << DatumKindName(datum.mKind);

                    if (datum.mKind == GMoxDatumKind::kType) {
                        out << " " << datum.mType.Name();
                    } else if (datum.mKind == GMoxDatumKind::kPlugKey) {
                        out << " "
                            << datum.mPlugTypeA.Name()
                            << " + "
                            << datum.mPlugTypeB.Name()
                            << " lane=" << datum.mSaltLaneIndex
                            << " rot=" << datum.mRotationAmount
                            << " off=" << datum.mOffsetAmount;
                            if (PlugUsesHiddenTap(datum)) {
                                out << " hidden_tap=yes";
                            } else {
                                out << " hidden_tap=no";
                            }
                    } else if (datum.mKind == GMoxDatumKind::kLoopKey) {
                        out << " lane=" << datum.mSaltLaneIndex
                            << " off=" << datum.mOffsetAmount
                            << " inverted=" << (datum.mIsLoopIndexInverted ? "yes" : "no");
                    }

                    if (datum.mKind == GMoxDatumKind::kType &&
                        datum.mRotationAmount >= 0) {
                        out << " rot=" << datum.mRotationAmount;
                    }

                    out << "\n";
                }
            }
        }

        out << "\n";
    }

    return out.str();
}

std::string GMoxPrinter::ToJsonLikeString(const GMoxPlan &plan) {
    std::ostringstream out;

    out << "{\n";
    out << "  \"name\": \"" << plan.mModel.mName << "\",\n";
    out << "  \"orbiters\": " << plan.mFormat.mOrbiterCount << ",\n";
    out << "  \"wanderers\": " << plan.mFormat.mWandererCount << ",\n";
    out << "  \"passes\": " << plan.mFormat.mPassCount << "\n";
    out << "}\n";

    return out.str();
}
