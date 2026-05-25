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
    
    static void                     AppendOrbiterAssignStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                                                  const std::vector<GAXSKVariable> &pWanderers,
                                                                  int pHotIndexBase,
                                                                  std::vector<GAXSKModelStatement> *pStatements);
    
    static void                     AppendWandererUpdateStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                                                   int pWandererCount,
                                                                   std::vector<GAXSKModelStatement> *pStatements);
    
    
    static void                     AppendOrbiterRoundStatements(const GAXSKModelOrbiterRound &pRound,
                                                                 int pHotIndex,
                                                                 std::vector<GAXSKModelStatement> *pStatements);
    
    
    static GAXSKModel               MakeOrbiterPlan(std::span<const GAXSKModelOrbiterRound> pRounds);
    
    
    
};

#endif /* GSKModel_hpp */
