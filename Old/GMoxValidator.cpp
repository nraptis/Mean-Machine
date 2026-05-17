#include "GMoxValidator.hpp"

static void SetError(std::string *error, const std::string &message) {
    if (error != nullptr) {
        *error = message;
    }
}

bool GMoxValidator::Validate(const GMoxPlan &plan, std::string *error) {
    if (ValidateFormat(plan.mFormat, error) == false) {
        return false;
    }

    if (plan.mPasses.size() != plan.mFormat.mPassCount) {
        SetError(error, "GMoxValidator: pass count mismatch");
        return false;
    }

    for (std::size_t i = 0; i < plan.mPasses.size(); i++) {
        const GMoxPassPlan *pass = plan.mPasses[i];

        if (pass == nullptr) {
            SetError(error, "GMoxValidator: null pass");
            return false;
        }

        if (ValidatePass(*pass, plan.mFormat, i, error) == false) {
            return false;
        }
    }

    return true;
}

bool GMoxValidator::ValidateFormat(const GMoxFormat &format, std::string *error) {
    if (format.IsValid() == false) {
        SetError(error, "GMoxValidator: invalid format");
        return false;
    }

    return true;
}

bool GMoxValidator::ValidatePass(const GMoxPassPlan &pass,
                                 const GMoxFormat &format,
                                 std::size_t passIndex,
                                 std::string *error) {
    (void)passIndex;

    if (pass.mStatements.empty()) {
        SetError(error, "GMoxValidator: empty pass statements");
        return false;
    }

    if (pass.mGroups.empty()) {
        SetError(error, "GMoxValidator: empty pass groups");
        return false;
    }

    for (const GMoxStatement *statement : pass.mStatements) {
        if (statement == nullptr) {
            SetError(error, "GMoxValidator: null statement");
            return false;
        }

        if (statement->mKind == GMoxStatementKind::kInvalid) {
            SetError(error, "GMoxValidator: invalid statement kind");
            return false;
        }

        if (statement->mKind != GMoxStatementKind::kCrush &&
            statement->mKind != GMoxStatementKind::kCarry &&
            statement->mTarget.IsValid() == false) {
            SetError(error, "GMoxValidator: invalid statement target");
            return false;
        }
    }

    if (ValidatePlugs(pass, format, error) == false) {
        return false;
    }

    if (ValidateSaltLanes(pass, format, error) == false) {
        return false;
    }

    if (ValidateRotations(pass, error) == false) {
        return false;
    }

    return true;
}

bool GMoxValidator::ValidatePlugs(const GMoxPassPlan &pass,
                                  const GMoxFormat &format,
                                  std::string *error) {
    for (const GMoxStatement *statement : pass.mStatements) {
        if (statement == nullptr) {
            continue;
        }

        for (const GMoxDatum &datum : statement->mDatums) {
            if (datum.mKind != GMoxDatumKind::kPlugKey) {
                continue;
            }

            if (datum.mPlugTypeA.IsValid() == false ||
                datum.mPlugTypeB.IsValid() == false) {
                SetError(error, "GMoxValidator: invalid plug tap");
                return false;
            }

            if (datum.mRotationAmount < 0) {
                SetError(error, "GMoxValidator: invalid plug rotation");
                return false;
            }

            if (datum.mOffsetAmount < 0) {
                SetError(error, "GMoxValidator: invalid plug offset");
                return false;
            }

            if (datum.mSaltLaneIndex < 0 ||
                static_cast<std::size_t>(datum.mSaltLaneIndex) >= format.mPlugLaneCount) {
                SetError(error, "GMoxValidator: invalid plug salt lane");
                return false;
            }
        }
    }

    return true;
}

bool GMoxValidator::ValidateRotations(const GMoxPassPlan &pass,
                                      std::string *error) {
    for (const GMoxStatement *statement : pass.mStatements) {
        if (statement == nullptr) {
            continue;
        }

        if (statement->mKind == GMoxStatementKind::kForwardRotate &&
            statement->mRotationAmount < 0) {
            SetError(error, "GMoxValidator: invalid forward rotation");
            return false;
        }

        for (const GMoxDatum &datum : statement->mDatums) {
            if (datum.mKind == GMoxDatumKind::kType &&
                datum.mRotationAmount < -1) {
                SetError(error, "GMoxValidator: invalid datum rotation");
                return false;
            }
        }
    }

    return true;
}

bool GMoxValidator::ValidateSaltLanes(const GMoxPassPlan &pass,
                                      const GMoxFormat &format,
                                      std::string *error) {
    for (const GMoxStatement *statement : pass.mStatements) {
        if (statement == nullptr) {
            continue;
        }

        for (const GMoxDatum &datum : statement->mDatums) {
            if (datum.mKind != GMoxDatumKind::kLoopKey) {
                continue;
            }

            if (datum.mOffsetAmount < 0) {
                SetError(error, "GMoxValidator: invalid loop salt offset");
                return false;
            }

            if (datum.mSaltLaneIndex < 0 ||
                static_cast<std::size_t>(datum.mSaltLaneIndex) >= format.mSaltLaneCount) {
                SetError(error, "GMoxValidator: invalid loop salt lane");
                return false;
            }
        }
    }

    return true;
}
