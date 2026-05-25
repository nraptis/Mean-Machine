
#include "GeneratorBudgetOperation.hpp"

GeneratorBudgetOperation::GeneratorBudgetOperation() {
    mMultiplyRemaining = 0;
    mAllowRotate = true;
    
}

GeneratorBudgetOperation::~GeneratorBudgetOperation() {
}

bool GeneratorBudgetOperation::IsAllowed(GeneratorOperation pOp,
                                         bool pAllowRotateLocal) const {

    switch (pOp) {
        case GeneratorOperation::kMul:
            return (mMultiplyRemaining > 0);

        case GeneratorOperation::kRotateLeft:
        case GeneratorOperation::kRotateRight:
            return (mAllowRotate && pAllowRotateLocal);

        case GeneratorOperation::kAdd:
        case GeneratorOperation::kSub:
        case GeneratorOperation::kXor:
            return true;

        default:
            return false;
    }
}

void GeneratorBudgetOperation::Consume(GeneratorOperation pOp) {

    switch (pOp) {
        case GeneratorOperation::kMul:
            if (mMultiplyRemaining > 0) {
                mMultiplyRemaining--;
            }
            break;

        default:
            break;
    }
}

GeneratorBudgetOperation GeneratorBudgetOperation::Clone() const {
    GeneratorBudgetOperation copy;

    copy.mMultiplyRemaining = mMultiplyRemaining;
    copy.mAllowRotate       = mAllowRotate;

    return copy;
}
