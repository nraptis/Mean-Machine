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
#include <initializer_list>
#include <string>
#include <vector>

/*
 // Orbit assign.
 a = s0 + RotL64(aIngress, 13U);
 b = s1 + RotL64(aScatter, 23U);
 c = s2 + RotL64(aPrevious, 37U);
 d = s3 + RotL64(aCross, 53U);

 // Orbit update round 0.
 a = a + b;
 d = d ^ a;
 d = RotL64(d * C0, 35U);

 // Orbit update round 1.
 b = b + c;
 a = a ^ b;
 a = RotL64(a * C1, 51U);

 // Orbit update round 2.
 c = c + d;
 b = b ^ c;
 b = RotL64(b * C2, 13U);

 // Orbit update round 3.
 d = d + a;
 c = c ^ d;
 c = RotL64(c * C3, 37U);
 */

/*
// Orbit assign.
a = s0 + RotL64(aIngress, 53U);
b = s1 + RotL64(aScatter, 23U);
c = s0 + RotL64(aPrevious, 27U);

// Orbit update round 0.
a = a + b;
c = c ^ a;
c = RotL64(c * C0, 37U);

// Orbit update round 1.
b = b + c;
a = a ^ b;
a = RotL64(a * C1, 53U);

// Orbit update round 2.
c = c + a;
b = b ^ c;
b = RotL64(b * C2, 19U);

// Unwind update.
s0 = s0 + RotL64(aIngress, 13U) + a + c;
s1 = s1 + RotL64(aScatter, 19U) + b + c;
*/



struct GAXSKModelTerm {
    GAXSKModelTermKind mKind = GAXSKModelTermKind::kInvalid;

    GAXSKVariable mVariable = GAXSKVariable::kInvalid;

    int mSaltSlot = -1;
    int mNonceSlot = -1;
    int mHotIndex = -1;

    bool mNeedsRotation = false;
};

struct GAXSKModelStatement {
    GAXSKModelOperation mOperation = GAXSKModelOperation::kInvalid;
    GAXSKVariable mTarget = GAXSKVariable::kInvalid;

    std::vector<GAXSKModelTerm> mTerms;

    // Used by kMulRotate.
    bool mNeedsRotation = false;
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
    std::vector<GAXSKVariable> mUnwind;
    
    std::vector<GAXSKModelStatement> mStatements;
    
    static GAXSKModelTerm           VarTerm(GAXSKVariable pVariable);
    static GAXSKModelTerm           RotVarTerm(GAXSKVariable pVariable);
    
    static GAXSKModelTerm           HotAddTerm(int pHotIndex = -1);
    static GAXSKModelTerm           HotMulTerm(int pHotIndex = -1);
    
    static GAXSKModelStatement      SetStatement(GAXSKVariable pTarget, const std::vector<GAXSKModelTerm> &pTerms);
    static GAXSKModelStatement      AddStatement(GAXSKVariable pTarget, const std::vector<GAXSKModelTerm> &pTerms);
    static GAXSKModelStatement      XorStatement(GAXSKVariable pTarget, const std::vector<GAXSKModelTerm> &pTerms);
    
    static GAXSKModelStatement      MulRotateStatement(GAXSKVariable pTarget);
    
    static GAXSKVariable            WandererForIndex(int pIndex);
    
    static void                     AppendOrbiterAssignStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                                                  const std::vector<GAXSKVariable> &pWanderers,
                                                                  std::vector<GAXSKModelStatement> *pStatements);
    
    static void                     AppendWandererUpdateStatements(const std::vector<GAXSKVariable> &pOrbiters,
                                                                   int pWandererCount,
                                                                   std::vector<GAXSKModelStatement> *pStatements);
    
    
    static void                     AppendOrbiterRoundStatements(const GAXSKModelOrbiterRound &pRound, std::vector<GAXSKModelStatement> *pStatements);
    
    static GAXSKModel               MakeOrbiterPlan4x4();
    
};

#endif /* GSKModel_hpp */
