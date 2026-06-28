//
//  ConsistencyTestsShared.hpp
//  CornTesting
//
//  Created by icarus black on 6/23/26.
//

#ifndef ConsistencyTestsShared_hpp
#define ConsistencyTestsShared_hpp

#include "Random.hpp"
#include "TwistExpander.hpp"
#include "TwistExpander_Greezy.hpp"

#include <cstddef>
#include <cstdio>
#include <cstdint>

#define CONSISTENCY_TESTS_EXPANDER TwistExpander_Greezy
#define CONSISTENCY_TESTS_ARX TwistExpander_Greezy_Arx

struct ConsistencyTestsArxVariables {
    TwistWorkSpace                          mWorkSpace;
    TwistDomainConstants                    mConstants = {};
    TwistDomainSaltSet                      mDomainSaltSet = {};
    
    std::uint8_t                            mSource[S_BLOCK] = {};
    std::uint8_t                            mSnow[S_BLOCK] = {};
    
    std::uint64_t                           mNonce = 0U;
    std::uint64_t                           mPrevious = 0U;
    std::uint64_t                           mIngress = 0U;
    std::uint64_t                           mCarry = 0U;
    
    std::uint64_t                           mWandererA = 0U;
    std::uint64_t                           mWandererB = 0U;
    std::uint64_t                           mWandererC = 0U;
    std::uint64_t                           mWandererD = 0U;
    std::uint64_t                           mWandererE = 0U;
    std::uint64_t                           mWandererF = 0U;
    std::uint64_t                           mWandererG = 0U;
    std::uint64_t                           mWandererH = 0U;
    std::uint64_t                           mWandererI = 0U;
    std::uint64_t                           mWandererJ = 0U;
    std::uint64_t                           mWandererK = 0U;
    
    ConsistencyTestsArxVariables Clone() const {
        return ConsistencyTestsArxVariables(*this);
    }
    
};

class ConsistencyTestsShared {
public:
    using Expander = CONSISTENCY_TESTS_EXPANDER;
    using ExpanderArx = CONSISTENCY_TESTS_ARX;

    static Expander MakeExpander() {
        return Expander();
    }

    static ExpanderArx MakeExpanderArx() {
        return ExpanderArx();
    }

    static ConsistencyTestsArxVariables MakeArxVariables() {
        ConsistencyTestsArxVariables aResult;
        
        FillWorkSpace(&aResult.mWorkSpace);
        FillConstants(&aResult.mConstants);
        FillSaltSet(&aResult.mDomainSaltSet);
        FillBytes(aResult.mSource, S_BLOCK);
        FillBytes(aResult.mSnow, S_BLOCK);
        
        aResult.mNonce = Random::Get64();
        aResult.mPrevious = Random::Get64();
        aResult.mIngress = Random::Get64();
        aResult.mCarry = Random::Get64();
        
        aResult.mWandererA = Random::Get64();
        aResult.mWandererB = Random::Get64();
        aResult.mWandererC = Random::Get64();
        aResult.mWandererD = Random::Get64();
        aResult.mWandererE = Random::Get64();
        aResult.mWandererF = Random::Get64();
        aResult.mWandererG = Random::Get64();
        aResult.mWandererH = Random::Get64();
        aResult.mWandererI = Random::Get64();
        aResult.mWandererJ = Random::Get64();
        aResult.mWandererK = Random::Get64();
        
        return aResult;
    }

    static bool EnsureExpansionLanesAreNotEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsNotEqual("EnsureExpansionLanesAreNotEqual", "mExpansionLaneA", pWorkSpaceA->mExpansionLaneA, pWorkSpaceB->mExpansionLaneA) &&
               EnsureByteLaneIsNotEqual("EnsureExpansionLanesAreNotEqual", "mExpansionLaneB", pWorkSpaceA->mExpansionLaneB, pWorkSpaceB->mExpansionLaneB) &&
               EnsureByteLaneIsNotEqual("EnsureExpansionLanesAreNotEqual", "mExpansionLaneC", pWorkSpaceA->mExpansionLaneC, pWorkSpaceB->mExpansionLaneC) &&
               EnsureByteLaneIsNotEqual("EnsureExpansionLanesAreNotEqual", "mExpansionLaneD", pWorkSpaceA->mExpansionLaneD, pWorkSpaceB->mExpansionLaneD);
    }

    static bool EnsureExpansionLanesAreEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsEqual("EnsureExpansionLanesAreEqual", "mExpansionLaneA", pWorkSpaceA->mExpansionLaneA, pWorkSpaceB->mExpansionLaneA) &&
               EnsureByteLaneIsEqual("EnsureExpansionLanesAreEqual", "mExpansionLaneB", pWorkSpaceA->mExpansionLaneB, pWorkSpaceB->mExpansionLaneB) &&
               EnsureByteLaneIsEqual("EnsureExpansionLanesAreEqual", "mExpansionLaneC", pWorkSpaceA->mExpansionLaneC, pWorkSpaceB->mExpansionLaneC) &&
               EnsureByteLaneIsEqual("EnsureExpansionLanesAreEqual", "mExpansionLaneD", pWorkSpaceA->mExpansionLaneD, pWorkSpaceB->mExpansionLaneD);
    }
    
    static bool EnsureOperationLanesAreNotEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsNotEqual("EnsureOperationLanesAreNotEqual", "mOperationLaneA", pWorkSpaceA->mOperationLaneA, pWorkSpaceB->mOperationLaneA) &&
               EnsureByteLaneIsNotEqual("EnsureOperationLanesAreNotEqual", "mOperationLaneB", pWorkSpaceA->mOperationLaneB, pWorkSpaceB->mOperationLaneB) &&
               EnsureByteLaneIsNotEqual("EnsureOperationLanesAreNotEqual", "mOperationLaneC", pWorkSpaceA->mOperationLaneC, pWorkSpaceB->mOperationLaneC) &&
               EnsureByteLaneIsNotEqual("EnsureOperationLanesAreNotEqual", "mOperationLaneD", pWorkSpaceA->mOperationLaneD, pWorkSpaceB->mOperationLaneD);
    }

    static bool EnsureOperationLanesAreEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsEqual("EnsureOperationLanesAreEqual", "mOperationLaneA", pWorkSpaceA->mOperationLaneA, pWorkSpaceB->mOperationLaneA) &&
               EnsureByteLaneIsEqual("EnsureOperationLanesAreEqual", "mOperationLaneB", pWorkSpaceA->mOperationLaneB, pWorkSpaceB->mOperationLaneB) &&
               EnsureByteLaneIsEqual("EnsureOperationLanesAreEqual", "mOperationLaneC", pWorkSpaceA->mOperationLaneC, pWorkSpaceB->mOperationLaneC) &&
               EnsureByteLaneIsEqual("EnsureOperationLanesAreEqual", "mOperationLaneD", pWorkSpaceA->mOperationLaneD, pWorkSpaceB->mOperationLaneD);
    }
    
    static bool EnsureWorkLanesAreNotEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsNotEqual("EnsureWorkLanesAreNotEqual", "mWorkLaneA", pWorkSpaceA->mWorkLaneA, pWorkSpaceB->mWorkLaneA) &&
               EnsureByteLaneIsNotEqual("EnsureWorkLanesAreNotEqual", "mWorkLaneB", pWorkSpaceA->mWorkLaneB, pWorkSpaceB->mWorkLaneB) &&
               EnsureByteLaneIsNotEqual("EnsureWorkLanesAreNotEqual", "mWorkLaneC", pWorkSpaceA->mWorkLaneC, pWorkSpaceB->mWorkLaneC) &&
               EnsureByteLaneIsNotEqual("EnsureWorkLanesAreNotEqual", "mWorkLaneD", pWorkSpaceA->mWorkLaneD, pWorkSpaceB->mWorkLaneD);
    }

    static bool EnsureWorkLanesAreEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsEqual("EnsureWorkLanesAreEqual", "mWorkLaneA", pWorkSpaceA->mWorkLaneA, pWorkSpaceB->mWorkLaneA) &&
               EnsureByteLaneIsEqual("EnsureWorkLanesAreEqual", "mWorkLaneB", pWorkSpaceA->mWorkLaneB, pWorkSpaceB->mWorkLaneB) &&
               EnsureByteLaneIsEqual("EnsureWorkLanesAreEqual", "mWorkLaneC", pWorkSpaceA->mWorkLaneC, pWorkSpaceB->mWorkLaneC) &&
               EnsureByteLaneIsEqual("EnsureWorkLanesAreEqual", "mWorkLaneD", pWorkSpaceA->mWorkLaneD, pWorkSpaceB->mWorkLaneD);
    }

    static bool EnsureWorkLanesABAreNotEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsNotEqual("EnsureWorkLanesABAreNotEqual", "mWorkLaneA", pWorkSpaceA->mWorkLaneA, pWorkSpaceB->mWorkLaneA) &&
               EnsureByteLaneIsNotEqual("EnsureWorkLanesABAreNotEqual", "mWorkLaneB", pWorkSpaceA->mWorkLaneB, pWorkSpaceB->mWorkLaneB);
    }

    static bool EnsureWorkLanesABAreEqual(TwistWorkSpace *pWorkSpaceA, TwistWorkSpace *pWorkSpaceB) {
        return EnsureByteLaneIsEqual("EnsureWorkLanesABAreEqual", "mWorkLaneA", pWorkSpaceA->mWorkLaneA, pWorkSpaceB->mWorkLaneA) &&
               EnsureByteLaneIsEqual("EnsureWorkLanesABAreEqual", "mWorkLaneB", pWorkSpaceA->mWorkLaneB, pWorkSpaceB->mWorkLaneB);
    }
    
private:
    static bool EnsureByteLaneIsNotEqual(const char *pFunctionName,
                                         const char *pLaneName,
                                         const std::uint8_t *pLaneA,
                                         const std::uint8_t *pLaneB) {
        if (ByteLanesAreEqual(pLaneA, pLaneB, nullptr)) {
            printf("Fail: %s, %s, expected *not equal*\n", pFunctionName, pLaneName);
            return false;
        }
        return true;
    }
    
    static bool EnsureByteLaneIsEqual(const char *pFunctionName,
                                      const char *pLaneName,
                                      const std::uint8_t *pLaneA,
                                      const std::uint8_t *pLaneB) {
        int aFailedIndex = 0;
        if (ByteLanesAreEqual(pLaneA, pLaneB, &aFailedIndex) == false) {
            printf("Fail: %s, %s, expected *equal* (failed at %d)\n", pFunctionName, pLaneName, aFailedIndex);
            return false;
        }
        return true;
    }
    
    static bool ByteLanesAreEqual(const std::uint8_t *pLaneA,
                                  const std::uint8_t *pLaneB,
                                  int *pFailedIndex) {
        for (int aIndex = 0; aIndex < S_BLOCK; aIndex += 1) {
            if (pLaneA[aIndex] != pLaneB[aIndex]) {
                if (pFailedIndex != nullptr) {
                    *pFailedIndex = aIndex;
                }
                return false;
            }
        }
        return true;
    }
    
    static void FillBytes(std::uint8_t *pBytes,
                          std::size_t pCount) {
        for (std::size_t aIndex = 0U; aIndex < pCount; aIndex += 1U) {
            pBytes[aIndex] = Random::GetByte();
        }
    }
    
    static void Fill64(std::uint64_t *pWords,
                       std::size_t pCount) {
        for (std::size_t aIndex = 0U; aIndex < pCount; aIndex += 1U) {
            pWords[aIndex] = Random::Get64();
        }
    }
    
    static void FillConstants(TwistDomainConstants *pConstants) {
        pConstants->mIngress = Random::Get64();
        pConstants->mScatter = Random::Get64();
        pConstants->mCross = Random::Get64();
        
        pConstants->mDomainConstantPublicIngress = Random::Get64();
        pConstants->mDomainConstantPrivateIngress = Random::Get64();
        pConstants->mDomainConstantCrossIngress = Random::Get64();
        
        pConstants->mMatrixSelectA = Random::Get64();
        pConstants->mMatrixSelectB = Random::Get64();
        
        pConstants->mMatrixUnrollA = Random::GetByte();
        pConstants->mMatrixUnrollB = Random::GetByte();
        
        pConstants->mMatrixArgA = Random::GetByte();
        pConstants->mMatrixArgB = Random::GetByte();
        pConstants->mMatrixArgC = Random::GetByte();
        pConstants->mMatrixArgD = Random::GetByte();
        
        pConstants->mMaskMutateA = Random::GetByte();
        pConstants->mMaskMutateB = Random::GetByte();
    }
    
    static void FillSeedRoundMaterial(TwistDomainSeedRoundMaterial *pMaterial) {
        Fill64(pMaterial->mSaltA, S_SALT);
        Fill64(pMaterial->mSaltB, S_SALT);
        Fill64(pMaterial->mSaltC, S_SALT);
        Fill64(pMaterial->mSaltD, S_SALT);
        Fill64(pMaterial->mSaltE, S_SALT);
        Fill64(pMaterial->mSaltF, S_SALT);
    }
    
    static void FillSaltSet(TwistDomainSaltSet *pSaltSet) {
        FillSeedRoundMaterial(&pSaltSet->mOrbiterAssign);
        FillSeedRoundMaterial(&pSaltSet->mOrbiterUpdate);
        FillSeedRoundMaterial(&pSaltSet->mWandererUpdate);
    }
    
    static void FillDomainBundle(TwistDomainBundle *pBundle) {
        FillSaltSet(&pBundle->mPhaseASalts);
        FillConstants(&pBundle->mPhaseAConstants);
        FillSaltSet(&pBundle->mPhaseBSalts);
        FillConstants(&pBundle->mPhaseBConstants);
        FillSaltSet(&pBundle->mPhaseCSalts);
        FillConstants(&pBundle->mPhaseCConstants);
        FillSaltSet(&pBundle->mPhaseDSalts);
        FillConstants(&pBundle->mPhaseDConstants);
        FillSaltSet(&pBundle->mPhaseESalts);
        FillConstants(&pBundle->mPhaseEConstants);
        FillSaltSet(&pBundle->mPhaseFSalts);
        FillConstants(&pBundle->mPhaseFConstants);
        FillSaltSet(&pBundle->mPhaseGSalts);
        FillConstants(&pBundle->mPhaseGConstants);
        FillSaltSet(&pBundle->mPhaseHSalts);
        FillConstants(&pBundle->mPhaseHConstants);
    }
    
    static void FillWorkSpace(TwistWorkSpace *pWorkSpace) {
        FillBytes(&pWorkSpace->mKeyBoxA[0][0], S_KEY);
        FillBytes(&pWorkSpace->mKeyBoxB[0][0], S_KEY);
        
        FillBytes(pWorkSpace->mExpansionLaneA, S_BLOCK);
        FillBytes(pWorkSpace->mExpansionLaneB, S_BLOCK);
        FillBytes(pWorkSpace->mExpansionLaneC, S_BLOCK);
        FillBytes(pWorkSpace->mExpansionLaneD, S_BLOCK);
        
        FillBytes(pWorkSpace->mWorkLaneA, S_BLOCK);
        FillBytes(pWorkSpace->mWorkLaneB, S_BLOCK);
        FillBytes(pWorkSpace->mWorkLaneC, S_BLOCK);
        FillBytes(pWorkSpace->mWorkLaneD, S_BLOCK);
        
        FillBytes(pWorkSpace->mOperationLaneA, S_BLOCK);
        FillBytes(pWorkSpace->mOperationLaneB, S_BLOCK);
        FillBytes(pWorkSpace->mOperationLaneC, S_BLOCK);
        FillBytes(pWorkSpace->mOperationLaneD, S_BLOCK);
        
        FillBytes(pWorkSpace->mSnowLaneA, S_BLOCK);
        FillBytes(pWorkSpace->mSnowLaneB, S_BLOCK);
        FillBytes(pWorkSpace->mSnowLaneC, S_BLOCK);
        FillBytes(pWorkSpace->mSnowLaneD, S_BLOCK);

        FillBytes(pWorkSpace->mFireLaneA, S_BLOCK);
        FillBytes(pWorkSpace->mFireLaneB, S_BLOCK);
        FillBytes(pWorkSpace->mFireLaneC, S_BLOCK);
        FillBytes(pWorkSpace->mFireLaneD, S_BLOCK);
        
        FillBytes(pWorkSpace->mInvestLaneA, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneB, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneC, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneD, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneE, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneF, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneG, S_BLOCK);
        FillBytes(pWorkSpace->mInvestLaneH, S_BLOCK);
        
        FillDomainBundle(&pWorkSpace->mDomainBundle);
    }
};




#endif /* ConsistencyTestsShared_hpp */

/*

 ConsistencyTestsShared::Expander aExpander;
 CONSISTENCY_TESTS_ARX::KDF_A_A(...);

 To switch candidates for these tests, change the include and the two aliases above.

 */
