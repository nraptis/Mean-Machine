//
//  GSKModel.hpp
//  MeanMachine
//
//  Created by Nick Raptis on 5/21/26.
//

#ifndef GSKModel_hpp
#define GSKModel_hpp

#include "GAXSK.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <span>
#include <algorithm>

struct GAXSKModelTerm {
    GAXSKModelTermKind              mKind = GAXSKModelTermKind::kInvalid;

    GAXSKVariable                   mVariable = GAXSKVariable::kInvalid;
    int                             mHotIndex = -1;
    bool                            mNeedsRotation = false;
};

struct GAXSKModelStatement {
    GAXSKModelOperation             mOperation = GAXSKModelOperation::kInvalid;
    GAXSKVariable                   mTarget = GAXSKVariable::kInvalid;
    std::vector<GAXSKModelTerm>     mTerms;
    bool                            mNeedsRotation = false;
};

struct GAXSKModelOrbiterRound {
    GAXSKVariable mLead = GAXSKVariable::kInvalid;
    GAXSKVariable mSource = GAXSKVariable::kInvalid;
    GAXSKVariable mFeedback = GAXSKVariable::kInvalid;
};

struct GAXSKModelOrbiterAssignment {
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;
    GAXSKVariable mWanderer = GAXSKVariable::kInvalid;
    GAXSKVariable mContext = GAXSKVariable::kInvalid;
    bool mUseCarry = false;
};

struct GAXSKModelWandererUpdate {
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;
    GAXSKVariable mContext = GAXSKVariable::kInvalid;
    GAXSKVariable mOrbiterA = GAXSKVariable::kInvalid;
    GAXSKVariable mOrbiterB = GAXSKVariable::kInvalid;
    bool mUseXor = false;
    bool mUseCarry = false;
    bool mRotateFirst = false;
};

class GAXSKModel {
public:
    std::string mName;
    
    std::vector<GAXSKVariable> mOrbiters;
    std::vector<GAXSKVariable> mWanderers;
    
    std::vector<GAXSKModelStatement> mStatements;
    
    static GAXSKModelTerm           VarTerm(GAXSKVariable pVariable);
    static GAXSKModelTerm           RotVarTerm(GAXSKVariable pVariable);
    
    static GAXSKModelTerm           HotAddTerm(int pHotIndex = -1);
    static GAXSKModelTerm           HotMulTerm(int pHotIndex = -1);
    
    static GAXSKModelStatement      SetStatement(GAXSKVariable pTarget, const std::vector<GAXSKModelTerm> &pTerms);
    static GAXSKModelStatement      AddStatement(GAXSKVariable pTarget, const std::vector<GAXSKModelTerm> &pTerms);
    static GAXSKModelStatement      XorStatement(GAXSKVariable pTarget, const std::vector<GAXSKModelTerm> &pTerms);
    
    static GAXSKModelStatement      MulRotateStatement(GAXSKVariable pTarget,
                                                       int pHotIndex);
    
    static GAXSKVariable            WandererForIndex(int pIndex);
    
    static void                     AppendOrbiterAssignStatements(std::span<const GAXSKModelOrbiterAssignment> pAssignments,
                                                                  int pHotIndexBase,
                                                                  std::vector<GAXSKModelStatement> *pStatements);
    
    static void                     AppendWandererUpdateStatements(std::span<const GAXSKModelWandererUpdate> pUpdates,
                                                                   std::vector<GAXSKModelStatement> *pStatements);
    
    
    static void                     AppendOrbiterRoundStatements(const GAXSKModelOrbiterRound &pRound,
                                                                 int pHotIndex,
                                                                 std::vector<GAXSKModelStatement> *pStatements);
    
    
    static GAXSKModel               MakeOrbiterPlan(std::span<const GAXSKModelOrbiterRound> pRounds,
                                                    std::span<const GAXSKModelOrbiterAssignment> pAssignments,
                                                    std::span<const GAXSKModelWandererUpdate> pUpdates);
    
    
    
};

#endif /* GSKModel_hpp */
