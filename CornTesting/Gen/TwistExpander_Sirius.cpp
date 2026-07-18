#include "TwistExpander_Sirius.hpp"
#include "TwistDiffuse.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix32.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmConstants.hpp"
#include "TwistMemory.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include "TwistSquash.hpp"

#include <cstdint>
#include <cstring>

TwistExpander_Sirius::TwistExpander_Sirius()
: TwistExpander() {
    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;
    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;
    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;
    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;
    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;
    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;
    mDomainBundleInbuilt.mPhaseDSalts = kPhaseDSalts;
    mDomainBundleInbuilt.mPhaseDConstants = kPhaseDConstants;
    mDomainBundleInbuilt.mPhaseESalts = kPhaseESalts;
    mDomainBundleInbuilt.mPhaseEConstants = kPhaseEConstants;
    mDomainBundleInbuilt.mPhaseFSalts = kPhaseFSalts;
    mDomainBundleInbuilt.mPhaseFConstants = kPhaseFConstants;
    mDomainBundleInbuilt.mPhaseGSalts = kPhaseGSalts;
    mDomainBundleInbuilt.mPhaseGConstants = kPhaseGConstants;
    mDomainBundleInbuilt.mPhaseHSalts = kPhaseHSalts;
    mDomainBundleInbuilt.mPhaseHConstants = kPhaseHConstants;
    mDomainBundleEphemeral.Zero();
}

void TwistExpander_Sirius::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  std::uint8_t *pSnow,
                                  int pIndexKDF) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aWindLaneA = pWorkSpace->mWindLaneA;
    std::uint8_t *aWindLaneB = pWorkSpace->mWindLaneB;
    std::uint8_t *aWindLaneC = pWorkSpace->mWindLaneC;
    std::uint8_t *aWindLaneD = pWorkSpace->mWindLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xF71F9F78CEEEABBDULL; std::uint64_t aIngress = 0x8021306EF0DF5722ULL; std::uint64_t aCarry = 0x86B6531F46342BE1ULL;

    std::uint64_t aWandererA = 0x827487225CA4B587ULL; std::uint64_t aWandererB = 0xD6698C26834D633FULL; std::uint64_t aWandererC = 0x874CDEF5503179E7ULL; std::uint64_t aWandererD = 0x8C5947758A81F0F9ULL;
    std::uint64_t aWandererE = 0x84BBFAA887849CDBULL; std::uint64_t aWandererF = 0xDDF20CFFC9E6A9D1ULL; std::uint64_t aWandererG = 0x9B901B8EF31CB3A5ULL; std::uint64_t aWandererH = 0xE58D9A52221B740CULL;
    std::uint64_t aWandererI = 0xA7C1BEA7C53FFE48ULL; std::uint64_t aWandererJ = 0xB087E04007EDEF99ULL; std::uint64_t aWandererK = 0xF465316B0CCFA7E2ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12071828170364057218U;
        aCarry = 11430250053939750763U;
        aWandererA = 18011522937129689664U;
        aWandererB = 17506330698241938880U;
        aWandererC = 13014820344075463018U;
        aWandererD = 17887494051959358105U;
        aWandererE = 16553448762479711909U;
        aWandererF = 9611049599711774777U;
        aWandererG = 13585876402620850576U;
        aWandererH = 16991684149047790522U;
        aWandererI = 18071323912421949901U;
        aWandererJ = 16985716741649246467U;
        aWandererK = 12071719966249552301U;
    TwistExpander_Sirius_Arx::KDF_A_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::KDF_A_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::KDF_A_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::KDF_A_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aWindLaneA, aWindLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aWindLaneC, aWindLaneD, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Sirius_Arx::KDF_A_E(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 pSnow,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

}

void TwistExpander_Sirius::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  int pIndexKDF) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xA01B2AD25A2FB8B1ULL; std::uint64_t aIngress = 0xFA3834828BE2BBDFULL; std::uint64_t aCarry = 0xBA4A7FCA95DB4B69ULL;

    std::uint64_t aWandererA = 0xDE9DCCF5212E139FULL; std::uint64_t aWandererB = 0xE19728DB6EC25456ULL; std::uint64_t aWandererC = 0xB4200EA99EC38C65ULL; std::uint64_t aWandererD = 0xF8E75C7FAA41E98BULL;
    std::uint64_t aWandererE = 0xCA6D5B9781D29CC4ULL; std::uint64_t aWandererF = 0xE3AD47A995D35E78ULL; std::uint64_t aWandererG = 0xEA83AE27F80779BDULL; std::uint64_t aWandererH = 0xA46F3FE77A486D13ULL;
    std::uint64_t aWandererI = 0x9718BA750B0B1F2EULL; std::uint64_t aWandererJ = 0xF2897EF8631418A3ULL; std::uint64_t aWandererK = 0x9C1EA9067C6CDFA8ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12761732580983785216U;
        aCarry = 13304903064353340599U;
        aWandererA = 11518915948963961478U;
        aWandererB = 17320688746658390099U;
        aWandererC = 17521811306953506421U;
        aWandererD = 14442060987854174836U;
        aWandererE = 10003356115996646238U;
        aWandererF = 14026743484737321801U;
        aWandererG = 10962287850327848622U;
        aWandererH = 14526393586543964762U;
        aWandererI = 17296487590076937179U;
        aWandererJ = 17113453354024138382U;
        aWandererK = 11261471947174273085U;
    TwistExpander_Sirius_Arx::KDF_B_A(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::KDF_B_B(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::KDF_B_C(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aWorkLaneA, aWorkLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aWorkLaneC, aWorkLaneD, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Sirius_Arx::KDF_B_D(pWorkSpace,
                 pNonce,
                 pConstants,
                 pDomainSaltSet,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

}

void TwistExpander_Sirius::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pPassword,
                                 std::size_t pPasswordByteLength,
                                 std::uint8_t *pDestination) {
    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }
    std::uint8_t *aSource = pWorkSpace->mSource;
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aWaterLaneA = pWorkSpace->mWaterLaneA;
    std::uint8_t *aWaterLaneB = pWorkSpace->mWaterLaneB;
    std::uint8_t *aWaterLaneC = pWorkSpace->mWaterLaneC;
    std::uint8_t *aWaterLaneD = pWorkSpace->mWaterLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xB4E0D3120848B96DULL;
    std::uint64_t aIngress = 0xCE825112D164E14AULL;
    std::uint64_t aCarry = 0xA13288F5B7B645F4ULL;

    std::uint64_t aWandererA = 0xB8228747C8328C1AULL;
    std::uint64_t aWandererB = 0xB7D2C911D0088AA1ULL;
    std::uint64_t aWandererC = 0x81B28B8AFCE74C39ULL;
    std::uint64_t aWandererD = 0x9443D73864CC6D5AULL;
    std::uint64_t aWandererE = 0xDEE915F34BDE0232ULL;
    std::uint64_t aWandererF = 0xCF357C2E25C72B93ULL;
    std::uint64_t aWandererG = 0x8A268DB25206016FULL;
    std::uint64_t aWandererH = 0xCB4A2D08EE17826AULL;
    std::uint64_t aWandererI = 0x9E52C46476995682ULL;
    std::uint64_t aWandererJ = 0x8C407A3B8E544A2EULL;
    std::uint64_t aWandererK = 0xD2332C5BCD29BF9EULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneD, 0);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts), 0);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase B
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneA, 1);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts), 1);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseBConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase C
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneB, 2);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts), 2);
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseCConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase D
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneC, 3);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseDConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseDConstants), &(mDomainBundleEphemeral.mPhaseDSalts), 3);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseDConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase E
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneD, 4);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseEConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseEConstants), &(mDomainBundleEphemeral.mPhaseESalts), 4);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseEConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase F
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneA, 5);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseFConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseFConstants), &(mDomainBundleEphemeral.mPhaseFSalts), 5);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseFConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase G
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneB, 6);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseGConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseGConstants), &(mDomainBundleEphemeral.mPhaseGSalts), 6);
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseGConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase H
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneC, 7);
    pFarmSalt->Derive(aWaterLaneA, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aWaterLaneB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aWaterLaneC, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aWaterLaneD, &(mDomainBundleEphemeral.mPhaseHConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseHConstants), &(mDomainBundleEphemeral.mPhaseHSalts), 7);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(pWorkSpace->mDomainBundle.mPhaseHConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    // GSquashInvestToKeyBoxes (start)
    SquashInvestToKeyBoxes();
    // GSquashInvestToKeyBoxes (end)
    //
    TwistExpander_Sirius_Arx::Seed_A(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Seed_B(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Seed_C(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Seed_D(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aFireLaneA, aFireLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aFireLaneC, aFireLaneD, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Sirius_Arx::Seed_E(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Seed_F(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Seed_G(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Seed_H(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
    //
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aInvestLaneE, aInvestLaneF, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aInvestLaneG, aInvestLaneH, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    TwistExpander_Sirius_Arx::Seed_I(pWorkSpace,
                 pNonce,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Sirius_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyA(pWorkSpace);
    TwistExpander_Sirius_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyB(pWorkSpace);
    Zero_PostSeed();
}

// SmartSquash candidate 31 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1788 / 1984 (90.12%)
// Total distance from earlier candidates: 54375
void TwistExpander_Sirius::SquashInvestToKeyBoxes() {
    static_assert((S_BLOCK / W_KEY) == 16, "SquashInvestToKeyBoxes expects 16 invest fragments.");
    static_assert(H_KEY == 8, "SquashInvestToKeyBoxes expects 8 key rows per box.");
    if (mWorkspace == nullptr) { return; }
    std::uint8_t *aInvestLaneA = mWorkspace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = mWorkspace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = mWorkspace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = mWorkspace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = mWorkspace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = mWorkspace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = mWorkspace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = mWorkspace->mInvestLaneH;

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 940U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1950U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 400U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1186U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 792U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 315U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1313U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1271U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1726U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 547U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 191U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1829U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 148U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 440U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1574U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1437U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1402U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 161U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1123U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1352U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 621U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1078U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 686U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1364U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1468U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 216U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 166U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1309U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 561U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1331U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1441U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 885U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1945U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 108U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1371U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 336U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2039U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 394U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1363U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1976U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1396U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1918U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 578U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1530U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 466U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1385U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 580U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 912U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1543U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 691U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1062U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 46U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1392U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1677U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1242U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 746U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1061U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 599U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1097U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1339U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1117U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1467U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1265U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1567U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 271U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1337U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1220U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1096U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1814U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1120U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1386U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1946U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1557U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 569U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 598U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 564U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 78U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1338U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1303U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 719U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1378U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1151U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1561U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1895U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1665U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1769U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 977U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1649U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1840U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 87U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 341U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1306U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 860U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 902U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1746U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 889U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 224U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1940U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 563U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 577U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1610U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 493U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1568U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1176U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 834U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1538U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 665U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 263U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 949U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 71U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1334U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1547U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1140U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1824U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 482U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 975U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1571U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 206U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 296U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 120U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1050U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1230U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1148U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Sirius::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aFuseLaneA = pWorkSpace->mFuseLaneA;
    std::uint8_t *aFuseLaneB = pWorkSpace->mFuseLaneB;
    std::uint8_t *aFuseLaneC = pWorkSpace->mFuseLaneC;
    std::uint8_t *aFuseLaneD = pWorkSpace->mFuseLaneD;
    std::size_t *aIndexList256A = mIndexList256A;
    std::size_t *aIndexList256B = mIndexList256B;
    std::size_t *aIndexList256C = mIndexList256C;
    std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xA500AA4F4CEC6ACCULL; std::uint64_t aIngress = 0xEDF2C75F2BB1DB55ULL; std::uint64_t aCarry = 0xA7D9849830A3D140ULL;

    std::uint64_t aWandererA = 0x8917128D789A9441ULL; std::uint64_t aWandererB = 0xD1F749E4543CA887ULL; std::uint64_t aWandererC = 0xD832D08E5B972095ULL; std::uint64_t aWandererD = 0xB94E5E3DC27B8079ULL;
    std::uint64_t aWandererE = 0x8D8B0884C76B40D2ULL; std::uint64_t aWandererF = 0x86A84D53A0CCAC57ULL; std::uint64_t aWandererG = 0xA8B7266B77CDDF58ULL; std::uint64_t aWandererH = 0x929904D40A22D168ULL;
    std::uint64_t aWandererI = 0xEB1696DA4680E825ULL; std::uint64_t aWandererJ = 0xCFDDE36B155E366FULL; std::uint64_t aWandererK = 0xF0F86B0D2E40D77DULL;

    // [seed]
        aPrevious = 12807953165483037327U;
        aCarry = 16589390288336584546U;
        aWandererA = 9441141600482782957U;
        aWandererB = 12708077487099678940U;
        aWandererC = 14176439655535318031U;
        aWandererD = 13717879676433381892U;
        aWandererE = 13171920168511313292U;
        aWandererF = 18298676434596674854U;
        aWandererG = 10768122975798302709U;
        aWandererH = 10812393580322368715U;
        aWandererI = 10288222609755700643U;
        aWandererJ = 13088532699126577661U;
        aWandererK = 15431116499021463621U;
    TwistExpander_Sirius_Arx::Twist_A(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Twist_B(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Twist_C(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Twist_D(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Twist_E(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneA, aFuseLaneB,  // input lanes
                         aFireLaneA, aFireLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
        TwistDiffuse::DiffuseWithDomainWords(aFuseLaneC, aFuseLaneD,  // input lanes
                         aFireLaneC, aFireLaneD, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    TwistExpander_Sirius_Arx::Twist_F(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    TwistExpander_Sirius_Arx::Twist_G(pWorkSpace,
                 pSource,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    //
        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Sirius_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyA(pWorkSpace);
    TwistExpander_Sirius_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
                 &aWandererC,
                 &aWandererD,
                 &aWandererE,
                 &aWandererF,
                 &aWandererG,
                 &aWandererH,
                 &aWandererI,
                 &aWandererJ,
                 &aWandererK);

    GrowKeyB(pWorkSpace);
}

// GrowA candidate 31 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16224; nearest pair: 459 / 674
void TwistExpander_Sirius::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyA expects four expansion-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyA expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1308U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7188U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5508U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6067U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8140U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3288U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 195U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 909U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7032U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5710U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3818U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1075U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1522U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7943U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3813U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 821U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 313U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 530U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 622U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 933U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 178U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1236U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 854U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1483U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1415U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1591U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1435U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1652U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1678U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1757U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1463U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 349U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1361U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1685U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1422U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 31 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16201; nearest pair: 450 / 674
void TwistExpander_Sirius::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);
    static_assert((S_BLOCK / S_QUARTER) == 4, "GrowKeyB expects four work-lane quarters.");
    static_assert((S_QUARTER / W_KEY) == 4, "GrowKeyB expects four key chunks per quarter.");
    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6770U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3607U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6630U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1913U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4992U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8104U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3480U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5501U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6094U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3726U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1541U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4790U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4380U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3469U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4966U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 338U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1628U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 941U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1202U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 498U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1593U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 469U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 958U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 180U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 714U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1351U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 322U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 278U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1763U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1582U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 619U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1324U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 371U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 539U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1112U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1178U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseASalts = {
    {
        {
            0x39552CDA7D0597F7ULL, 0x329F69A059088D9EULL, 0xB77F330A08150060ULL, 0x9903FBE0D499C536ULL, 
            0x15797FA610A7923FULL, 0x60D1C228A6827ED5ULL, 0x4F29443846E9C2ABULL, 0xA439EC4475EFA7D3ULL, 
            0xAE3FFB398584DA5AULL, 0x4D3A2BEED861D1FBULL, 0xDA0D25CCF17CAA20ULL, 0x019E075BE991CD18ULL, 
            0xAC3F42D25F11E089ULL, 0x6CAF46F5BABFD3F8ULL, 0x7DA83B600E330470ULL, 0x2CA2B715C588AAC4ULL, 
            0x7764719C308CE63FULL, 0x12C876449FD093AFULL, 0xB8071BE2ED7AA161ULL, 0x61A5F808762FEFF8ULL, 
            0x82A81F1715A239CAULL, 0xCB1A8FC927ADDD74ULL, 0x886507D8744B14FDULL, 0xC4442D3C73A684A2ULL, 
            0xFF11D60DE6EC86CDULL, 0x61573FCED008E702ULL, 0x0BCCFE7C6732E914ULL, 0xEF660F59FE436E19ULL, 
            0xEAEC3EED2920026CULL, 0x7C02C37159999E0DULL, 0xE03B48D2E55C9A0DULL, 0x803C56F5870BB2BEULL
        },
        {
            0x818EEB43F244BD69ULL, 0x926B4A6A56729FCFULL, 0xFDDBAF12C29FB940ULL, 0x8689B70A866A199AULL, 
            0x275D17FDD20A7329ULL, 0xCFB4E88566A4E430ULL, 0x347BB7DE76011EAEULL, 0x1A7AC9B2FE0564B2ULL, 
            0x34621C562BDDF40BULL, 0xBF5508F487E0417DULL, 0x4599D507C3ED2506ULL, 0x280D06E7A7F33B79ULL, 
            0xEEA3D239E6DF2FB1ULL, 0xC6D2643286D14493ULL, 0x77F3D09AB076A2BCULL, 0xC254C23161CDBAC1ULL, 
            0xEED6A4C258A98B76ULL, 0xD38DC765993F9F91ULL, 0x087BF46FA199EAA2ULL, 0xD7C1D55DC14CFB9DULL, 
            0xA1DC3BDF0A678EB9ULL, 0xB4AD726131ED68C4ULL, 0xB5E968E86FA107E1ULL, 0xFDF65C1DDE7248C6ULL, 
            0xB4829A7478B69744ULL, 0xDE043473F1EA7D22ULL, 0x9DBF52CC0C1A809BULL, 0x7AC595370BC521EEULL, 
            0x3EDFA31CBDA4CD8EULL, 0x51D7729B6FE9EE74ULL, 0xC39870A1239B2F4AULL, 0x2EF473101956D6A2ULL
        },
        {
            0xC7C3ED7041EC85ADULL, 0xC0BA11E262D38528ULL, 0x8ED71E9C452BB9EBULL, 0x011A18BE83B5AEDBULL, 
            0x75708D42EBC9E251ULL, 0x58EFFCCE5658ED3FULL, 0x8279DEC79868807EULL, 0xE97A6C0A377A151CULL, 
            0xBC80843B084BB779ULL, 0x9EA0DC14920DEB34ULL, 0x47BB5C03634131E3ULL, 0x65ADBB2B4308A7CAULL, 
            0x340726A3B1A73757ULL, 0x8A6F2C451DF7951AULL, 0x932C093EC8D1F5DDULL, 0x24DEA76989568CDFULL, 
            0xB2BF3F1E7A086C7FULL, 0xCFC21525BB0C5BCEULL, 0xB2834B52860518F5ULL, 0x990C45603558F340ULL, 
            0x171CD0EB02EF2AC7ULL, 0x69FC6BD4FDE9050AULL, 0xAC2F43E0F8D92081ULL, 0x3A9B2E2F66A21B12ULL, 
            0xAF5B736B754CA412ULL, 0xF2203AABAC5D1366ULL, 0xF18E74B115D26319ULL, 0x8D8D2EB11D417FC5ULL, 
            0xB68D5697002F4CFFULL, 0x70BA4FF8CAC18EA7ULL, 0x06B709460B2F6467ULL, 0x44601358ABA04585ULL
        },
        {
            0x1DFE6F7F0A584857ULL, 0x351AB9BF9E5C7018ULL, 0x69CD834E03E25793ULL, 0xB9C054A61B865447ULL, 
            0x99CF7396D79EA935ULL, 0xCF6D827D52BB0CE6ULL, 0xFA24DB62F95EC4D0ULL, 0x14A7E7A298356543ULL, 
            0x2A70D7FF5EF27355ULL, 0x7E7C363065F6CA24ULL, 0xD2B05C86F2ECD28AULL, 0x03EEA6CF28497779ULL, 
            0x6AD35B367A1A0440ULL, 0xFB356E0A16345577ULL, 0x1A66E5283DB5D1FDULL, 0x8325C11E4A055EC2ULL, 
            0xB3C121CE40E01DF2ULL, 0x76FBC2FE96173B9BULL, 0x7E845977D0DE529FULL, 0x364F172C31A3AA40ULL, 
            0x59740367565D8A12ULL, 0x24EA9CC9186F69D7ULL, 0x57716D12175C0AE2ULL, 0x96B77D7E3AD1F7F4ULL, 
            0x7C4FDB4C9B581F1FULL, 0x3D725C9E4D940463ULL, 0x5FAFC7FB0CF2BECDULL, 0xA14AFE1FDA237880ULL, 
            0x54F1D2B9AFFA6DC3ULL, 0x08C4F9EA33B99C8BULL, 0x92F750507622C53EULL, 0xFE56D6D0AE9DF237ULL
        },
        {
            0x2083219B39F84868ULL, 0xFCB3C1FAEC4C912EULL, 0x7CCFD34C28B03AF0ULL, 0x0CBC008558C89FCFULL, 
            0x481F5E6521CCFCC5ULL, 0xEF847B3141A5FD42ULL, 0x1C69687BC1C8C1B0ULL, 0x7AFFD6611F305753ULL, 
            0xCC252BAA88E599ADULL, 0xBDB82E29BF94C47EULL, 0x37DFE54DF6AAB3F7ULL, 0x886D3AE7B15D5A09ULL, 
            0x052F4B87C1FB8698ULL, 0x57586E8F0069ED84ULL, 0xF16E2C611BB2BE02ULL, 0xA9DA8FC824074630ULL, 
            0x3040CA030F6EFB9BULL, 0xD9B919E6899DF2A2ULL, 0xBAB83075097578AEULL, 0x042C6F9BA0AB2712ULL, 
            0x9EAA1B0D11D31DBDULL, 0x28D7ABD6FEC80A36ULL, 0xECAA91FBD4A3A161ULL, 0xA2FACA3B4F674CD6ULL, 
            0x748FE74792F1822EULL, 0x8E0BFBA1AC6D8883ULL, 0xB7090113544038AAULL, 0xD03CB89954C8FB35ULL, 
            0x0B8F190989B0FD9DULL, 0x65A5EE9764A2B81BULL, 0xAEF95942BBC7C5EFULL, 0x007ABD1B709471CCULL
        },
        {
            0x0EF5CFA3E01DAD53ULL, 0xF21521D12B8D58DFULL, 0x9CD2073511DE4F9AULL, 0x98A6D156A6413289ULL, 
            0x642CE091B0EA1FEFULL, 0x2A4E29C30E1709EEULL, 0xC2DACDFEF54FC371ULL, 0xCDAA9F44568E222CULL, 
            0x079598CF3633B42DULL, 0xC286861EFD7EF17AULL, 0x2FE25B048E12B93CULL, 0x8F0D32556013B64DULL, 
            0x03FA38DBF150CE41ULL, 0xA7EDAC761E6E6F6AULL, 0xF6D9842E27352B4CULL, 0x82B1E0CA7C7D85C3ULL, 
            0xDF61DD6309C5B18EULL, 0x2E451D629F83974CULL, 0xDD844D4C1E9A8E21ULL, 0xC2004A86093DD9C6ULL, 
            0x518361F8F619C948ULL, 0x76481C2B82C95081ULL, 0xB1936D1167A65EF4ULL, 0xBC82F602C6AEA64EULL, 
            0xB661111AD95191D8ULL, 0x39E2323877899A7FULL, 0xC12449F06A5998EAULL, 0x5F30E7F547F172A6ULL, 
            0xA97CED95B23340FFULL, 0xB15AC92E414010F1ULL, 0xFFAEE11FFFF2C261ULL, 0x218FEF50AA90F407ULL
        }
    },
    {
        {
            0xB42C3BF7B2045824ULL, 0x304D6046500933E2ULL, 0xA5595BE7E67C96DDULL, 0x8F0B4D2B8DFD12CBULL, 
            0x63F060ABA3B14A62ULL, 0x12BE8C0A4C25928CULL, 0x0288472CD05F8C3EULL, 0x6EE6E3C1D9B87B47ULL, 
            0xD8B392EA119D76ABULL, 0xF2606521CCD91A93ULL, 0x2A926B0516EE64DEULL, 0x0E0AC95593FD8338ULL, 
            0x8DBC3C807AFBF832ULL, 0xC2F4C9ABE392D060ULL, 0xDE24A9BC7B1B5D24ULL, 0x023C21C1137009BFULL, 
            0x26098ACB30157C65ULL, 0x4B8376B095B1FD2EULL, 0xF34495793E206D50ULL, 0x425DFDEB390ECAA9ULL, 
            0x58BF1BC42EC90AFAULL, 0x7433CB06B119B53FULL, 0x5B1C25D52A423FC9ULL, 0x9E29E6ADD4595CBDULL, 
            0x7BF6C7E0BE4C9EA6ULL, 0x470A5F457F130AF8ULL, 0x1D40522B522D61DFULL, 0xC0C17B758C05A668ULL, 
            0xC3B27CBA00A8B367ULL, 0xEB312EF11217F18EULL, 0x330B2E305A0EA9D5ULL, 0x3362EDDA5C05FF91ULL
        },
        {
            0x6DAAE25C3B70AF38ULL, 0xDA852E0DAD549DE8ULL, 0x093EBBECEF2866E9ULL, 0xF599685B66B48CB5ULL, 
            0x83BBB9B857B4AA53ULL, 0xD1DFCA8C07D20AF3ULL, 0xB74AFDA359245842ULL, 0x87FF25A40EC1832DULL, 
            0xE2FC722E0D745A13ULL, 0x35CC06F2D82A5CAAULL, 0xF2E985B916EDBB8CULL, 0x92C3EC8D62D1DC74ULL, 
            0x36B9DCBD922887D4ULL, 0x160285D0A65DF0DCULL, 0x97094E448ADBEFD5ULL, 0x14DEFADEB5DE2996ULL, 
            0x973E8E0E3892572FULL, 0x2EC585A26228EF8EULL, 0xFAF5DB603EC44D6AULL, 0xC7CEA3036ACC2965ULL, 
            0x38C56DC848E0C093ULL, 0xBBFDE054B5F3B286ULL, 0x682D1B9279538652ULL, 0x8975BAC9B4FE5E05ULL, 
            0x6F760954DEEA757EULL, 0x8549BF3B4CEE68DDULL, 0x9F74318DEE23B2A8ULL, 0x16350A1352EBC0C5ULL, 
            0xA877157EC843A894ULL, 0x2FF6C11B4C66D4FFULL, 0xC8D3DC6B98CE4E0CULL, 0x1441D3C0ECE8B08DULL
        },
        {
            0xAE3E8D7E0A6AF9DDULL, 0xBF95213451B44E73ULL, 0x1434474DD26667F0ULL, 0x61F78207A810CEDFULL, 
            0xCADB2C791D67115BULL, 0x928ECF1AC091363CULL, 0x0862769C9EBDCEFAULL, 0x053791267DD2E022ULL, 
            0xDA1A063737C9758CULL, 0xF05BD90EB31FC6B6ULL, 0xAE2B1FD1EF7DDF71ULL, 0x53C568B336A0939BULL, 
            0x32D9F481E060FFA7ULL, 0xD5E4B7277DA31022ULL, 0x15128A1EC09F8DA4ULL, 0x2343D987F02FB89AULL, 
            0xBC8A68E7DE6CEB4AULL, 0x8FD6988A5BD85ADCULL, 0x7445BB2F73946BA3ULL, 0xD344F1F99A2D2AC2ULL, 
            0xDBFAB0EBCF7DA0BBULL, 0x8B36E8D5B396FF28ULL, 0x5BCE8428A8DE4ACFULL, 0x861F09B18869C92FULL, 
            0x614958EADC72908DULL, 0x8BBBC6D2AF8E8719ULL, 0x9575575511E67749ULL, 0xC32A1ED656E11545ULL, 
            0x4607E6CDBC47A621ULL, 0xB6B647C47AC3FCBBULL, 0x251A0812ACFBDE98ULL, 0xAA86C9F2CED66C66ULL
        },
        {
            0xFEEE5986450BF2D7ULL, 0x7CDD67134D32E3A9ULL, 0x6659AD4C2ED78787ULL, 0xE2C8AB033981083FULL, 
            0x8D42D21D60F50300ULL, 0xD5DE7E909EB210B3ULL, 0x211AB1151375425EULL, 0x5ACFB42E41888D21ULL, 
            0xCFF03AA47623DFB6ULL, 0xEE157671F70554C9ULL, 0x98CFDE7992D72C75ULL, 0xB4D9D4F0BD7A8791ULL, 
            0xEC42BE272860369DULL, 0x41C40B260A050B11ULL, 0x785D96EA3638EF1EULL, 0x12BBF54EC0C57A20ULL, 
            0x365A081911FC376FULL, 0x536228690F5879AAULL, 0x2795B72EF1A04EF8ULL, 0x7755852E2F5F8C39ULL, 
            0x8F0E12F9C7BBFFFFULL, 0x1405385E593754CDULL, 0x95AD8480FCF1965AULL, 0x0C8BE8FFF7A8C07BULL, 
            0x50BA053A11C46679ULL, 0x539C97683D2287A8ULL, 0x0247CCDB6D1E5A6FULL, 0x5FB8A02CD21B2ECEULL, 
            0x30418F64B483B381ULL, 0x5050329A27C9B1C1ULL, 0xB3CE784D40DC6CC9ULL, 0x945B27631D6975C6ULL
        },
        {
            0x80E35F7F2FB9D35AULL, 0x49BD10DA138E318CULL, 0x4221782F350044AFULL, 0x49E67775DAF7865EULL, 
            0x2868CA503585F231ULL, 0x87CA7BB144A12893ULL, 0xACD39F63CC48FED2ULL, 0x0C1D07A779A904D3ULL, 
            0x7B69BF8D7E3728E4ULL, 0xC4C317EB548EEC89ULL, 0xF8B4F69ACEC2A047ULL, 0x8FCEC3FF1FF2D55CULL, 
            0x8A4869F128597429ULL, 0xECD4BFC3F4D32F00ULL, 0x3A87264BA3D51F24ULL, 0x3993068B07E1F07CULL, 
            0x4397D6A5375F961AULL, 0x79009ADAD4E90D61ULL, 0x659C40D40112F5BBULL, 0xE1FBB6CAFDB2421DULL, 
            0xB7E0C83CA0F2227BULL, 0x2E265F780F481D22ULL, 0x877A8EE509E10364ULL, 0xC0EF34BBF5F0B6C3ULL, 
            0x8C6E445249E3512AULL, 0x060A41752B5D1AFFULL, 0x57122DA2B45AE4A3ULL, 0xED04DAB43FF7AE21ULL, 
            0xEAE6099A50B54BECULL, 0x9C424A274F2A7CB0ULL, 0x9EDACFEDAD85FE65ULL, 0x860F74397C4FA131ULL
        },
        {
            0x6FA203DE95D79EF3ULL, 0x74CAEDDB19F49A6FULL, 0x7037AA7749B7F4D9ULL, 0x9FB49A805B633BAFULL, 
            0x2AE72C35959859F3ULL, 0x34DAE4B354D8705DULL, 0x6E0169396970A67DULL, 0xBE74FEE7CC45128BULL, 
            0x48E49E32B15DCB7BULL, 0x1C4000C3E2BDFBEDULL, 0x4D866331229B4F33ULL, 0x67AC67707876DD3FULL, 
            0x510FF510039164D4ULL, 0x80E72B33EB389159ULL, 0x7304329A47705237ULL, 0x47E0AD36EA518C57ULL, 
            0xC8553740E8C8811DULL, 0x3D15E6C87F259DC2ULL, 0x65EB02A79C5B387EULL, 0x80BA5EF6BE3F0657ULL, 
            0x48922E54C8D6F4FBULL, 0x2620A0BFCD6BF88CULL, 0x18D44C1D24D43527ULL, 0x798158D72C8800C3ULL, 
            0x54E1419A2A068083ULL, 0xB7C614587C2C239AULL, 0x9C4C49BD4AEF82FFULL, 0xAAB3FA703F771D2AULL, 
            0x0AC2970716ACB6AAULL, 0xC4FAECFC111AB621ULL, 0xAF2213E7CEB566F1ULL, 0x98E62ECC4018514CULL
        }
    },
    {
        {
            0x80FE638F1E384147ULL, 0x1C3EE5DBDF033857ULL, 0x47FE797463CFE974ULL, 0x9D56828E6A0D85F6ULL, 
            0x5665CACEC40FB9CEULL, 0xE2CA62F37BB2F012ULL, 0xA9DFE3ABB0E7EA3AULL, 0x5451DD2C32E6FF71ULL, 
            0xE5EC0964E9EBFA6CULL, 0xB612AEF7B817B65AULL, 0x82E1DBA7080CDBC7ULL, 0xEDF4767D17B621A4ULL, 
            0xAF9CB9C50BFA72AFULL, 0xEE3A6E736BEF7984ULL, 0xBB15D2C1BF7DD9DDULL, 0x6A4E52EF8FCEA950ULL, 
            0xFD029D4809335131ULL, 0x9D1BA7C4755CD5D1ULL, 0xBB9DD2CC1531B026ULL, 0xD468B151573361A4ULL, 
            0x4866F2C3E757EC5EULL, 0x559D9F0A6242EA57ULL, 0xFC13EE5156B4BFBCULL, 0x22862C89990976D4ULL, 
            0x435CCD77E3BA9204ULL, 0x0C4E219CC4B43739ULL, 0x1C65B6EBEE63B6F8ULL, 0xB91616BC51F1C5BFULL, 
            0x71BFE5B307F42726ULL, 0x04D7064DB350A01AULL, 0x09E19D8C8C08F788ULL, 0x2C2FFC19C6E668D2ULL
        },
        {
            0x9172201E6579CB0FULL, 0x3F13821A65A264C5ULL, 0x04E1B138DF655C32ULL, 0xBCE58872991C2FA8ULL, 
            0xD4E3F044A474BA50ULL, 0x927E9803C04D02D6ULL, 0xB5710F35717EEBBCULL, 0xDA68F534D807083CULL, 
            0x6BA897D041E98664ULL, 0xB8677079B1B31FBCULL, 0x8833323991721654ULL, 0x3B8E41AB4FEE0752ULL, 
            0xDCDC1A98AD84A6B6ULL, 0xDFABDD1A9E37DE51ULL, 0x3E07C10CB378B370ULL, 0x3C26F4727A53F23FULL, 
            0xE73EDDB5E40C8E75ULL, 0xD560A716E8029714ULL, 0x2DFBDA0A91FFE6ECULL, 0xBE11E19208070EFCULL, 
            0x3AE4C1EF4280D82EULL, 0x5BA6211EF52F9DF5ULL, 0xB873F54C3F3B5E25ULL, 0x58EDD4887FB5C22EULL, 
            0x29750F58EF83D57CULL, 0x7C6E9FBACF41C59AULL, 0x504754BA81170472ULL, 0xBA4920A3117A9342ULL, 
            0x2C739B5BD102EF25ULL, 0x5C38875273E08D35ULL, 0xCFF2AC1879F7C235ULL, 0x2CCF7B00146C278EULL
        },
        {
            0x6FB20C1B932D0FC8ULL, 0xC271C5B1530789FCULL, 0x9594D72E3A9CF31DULL, 0x06E1BB2850EF0BE8ULL, 
            0x1DF45634DF436C78ULL, 0xD0BB408B8FDE599BULL, 0x739F2A3F9E4602BBULL, 0x225503C138401AA8ULL, 
            0xAC3919DEFACB2E52ULL, 0x7B007C3121B1B982ULL, 0xC69D4EB1F91E0D2FULL, 0x958D69D088D72DCFULL, 
            0xE4D974A4987C7495ULL, 0x0204D8A7C4D8F8E5ULL, 0x2FCAD723FB198AA1ULL, 0xAC525EA2C6CD8BE8ULL, 
            0x91F3D17D075F39E7ULL, 0x74896628F190EAE1ULL, 0xA26C50CB3A46F54BULL, 0x995FF60300D6066EULL, 
            0x9A4444EA30208332ULL, 0x1BD0F8E1FC3A2AEBULL, 0x58A5C6C4A95F86CCULL, 0x369B36C70E793511ULL, 
            0x397E0B7779FAA51AULL, 0x761AE80C2770A46FULL, 0x326A26EA26801251ULL, 0x69042A47816C1A90ULL, 
            0xE8B084B7BC80F5CAULL, 0x8281B23211433CE0ULL, 0x070428565FFCE46EULL, 0x24BDE9F3EFD49B09ULL
        },
        {
            0x7B2171BF326A509DULL, 0xA787A2617F325A89ULL, 0xD7D03B626EA94B10ULL, 0xA0FB5E501E7D7C73ULL, 
            0x69F4A55810CF3771ULL, 0xEB90828E6F89582BULL, 0x8FDAB5ADB94DD632ULL, 0xC7D3AB4BAA952123ULL, 
            0xD10EE187E5685A5AULL, 0x764D55D4634F5AB4ULL, 0xBB5B6AF5818CEC0AULL, 0x2BA7DB94530FBB67ULL, 
            0x3A3D11C5D2FDCF15ULL, 0xA7F5464CC6E433E4ULL, 0xA80AE5B5E6DDA656ULL, 0xCEA58E9856128100ULL, 
            0xE7D867E95073E77FULL, 0xC54390E2B4B37F6FULL, 0xF964D76F1FEFFF96ULL, 0x41B927FAB67E5FCEULL, 
            0xB0641CD26A016F8AULL, 0xB15881D219386FF9ULL, 0x9E318620FE1D2503ULL, 0x9A538BCC5EE49C91ULL, 
            0xFEA6B63202943BC4ULL, 0xDA90746ED51D1561ULL, 0x6F82AFECAB4C3281ULL, 0x3BA9DA037753DAD8ULL, 
            0x0FC1B6E4122A78DAULL, 0xC6312E64ED97C6FAULL, 0x54D9899BE4EE4B01ULL, 0x05BF45AB5C9E532DULL
        },
        {
            0x4ED468EC4ED5EDF0ULL, 0xDB5520BAD59D04E7ULL, 0xDFA31C5829DE6AC8ULL, 0xC3C46925D3EF89AAULL, 
            0x4DEBA2C7CCCFC836ULL, 0xC7D7B91C98B2D2D4ULL, 0x01B321CB34C96AB7ULL, 0x7E40EB2395F9144BULL, 
            0x1757514646C702E5ULL, 0x3C68104B63C334D9ULL, 0x5232675C2CCF9126ULL, 0x5B9AF6E8593F9B3AULL, 
            0xFC2FA51002F2EFAFULL, 0x31013D061A3EA599ULL, 0xF91325168E8159A1ULL, 0xBFB858FB7E512F63ULL, 
            0xF1A6B0F76803F0B5ULL, 0xD01137E27FE9C59DULL, 0xC5B6452009EA4E4FULL, 0x850795018DB776C6ULL, 
            0x571D23D797685DA9ULL, 0xB819643E546260DAULL, 0x22712E1C9DCFE326ULL, 0xCC35FE1CC1B0AAE8ULL, 
            0x0B9BA2AD7F98B362ULL, 0x46FA1C82C699012FULL, 0x3441E194E22460EFULL, 0x1E7864FB663B0A6EULL, 
            0xC30296B7338DBAD9ULL, 0x4545638249730859ULL, 0x028E28002E1EC79EULL, 0xD39D678B9C8EB423ULL
        },
        {
            0xECD06EE2B63FC9FBULL, 0x9C6A714D8203DE61ULL, 0xE98E6B38B8E03172ULL, 0x4F28AB06B771C972ULL, 
            0x252E0F5F9EB23BDEULL, 0x76EC5B8B01D67868ULL, 0x9EB623B98A42DA65ULL, 0x242DCE0EA07C74FEULL, 
            0x537E2D51EB3F8083ULL, 0x950A4197DA264B1CULL, 0x1C962530B8578D7FULL, 0x218F4537C3C0C808ULL, 
            0x86454C1B282AD4CDULL, 0xCCBD5A6B1A5C4E05ULL, 0xAE368757DA5336D7ULL, 0x5D40F721A68B9DB9ULL, 
            0xA2C634ECA1425876ULL, 0x1BAC4ADCA670A954ULL, 0x4AAAD5FFD926FBA6ULL, 0x9D67AC61A1B909BDULL, 
            0x8B3CA71DE833AB45ULL, 0x72F72CB4AFDC4761ULL, 0x5D755D1445363823ULL, 0xEC7BA131A818098EULL, 
            0x673ECD46550953C9ULL, 0xCF9AAA3D62316907ULL, 0x27262CE52D0A1196ULL, 0xAB6B89D60647FA62ULL, 
            0xC3026B3DA5411041ULL, 0x01EE29AD272006FBULL, 0x7C233CE910368B02ULL, 0x8629863DBB8D9560ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseAConstants = {
    0x90ADF276887101C4ULL,
    0xDACC8D991C027958ULL,
    0x46914792FF4AEFFCULL,
    0x90ADF276887101C4ULL,
    0xDACC8D991C027958ULL,
    0x46914792FF4AEFFCULL,
    0xE455207C80485DCEULL,
    0xC5AFD0AE061BA451ULL,
    0x04,
    0xBB,
    0x48,
    0x67,
    0x64,
    0xD7,
    0x2C,
    0xDD
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseBSalts = {
    {
        {
            0x16FE2FD3BA97C7E6ULL, 0x14AAFFDCEC577563ULL, 0x37176FD75B4AD0DDULL, 0xED27A8DF9FAAB4B3ULL, 
            0x6ADC585AC2C54134ULL, 0x41CCC56052FDB276ULL, 0xBDE19247D8932792ULL, 0x3230A27A7FB182A0ULL, 
            0xB08CCF6B2BF03E43ULL, 0xD4287E4AB0ED669AULL, 0x59D0333566E75858ULL, 0x9580C89CCF9D0EA6ULL, 
            0x5CA729AE80531EBDULL, 0x4153E8675B4C3628ULL, 0x6C338821D35CCCE4ULL, 0x38162EAB275FD49CULL, 
            0xADD3B2719462A173ULL, 0xE501572022804B87ULL, 0xA18294D74D0189C6ULL, 0x93CBCF16DB16C9AFULL, 
            0x0B67EA4423C38152ULL, 0x80A17AE4073C1113ULL, 0x05EAB5B1AD936F19ULL, 0x10A3FE568546F4D4ULL, 
            0x7E951823DF954D30ULL, 0xB65FA91852EAAF48ULL, 0xD20FF7144B008BDDULL, 0xD2694526E2507A09ULL, 
            0x5F4E048708860936ULL, 0x4C21479C6D4CF891ULL, 0x9D42E7D6AFE209FCULL, 0x9E5E10D1A358A999ULL
        },
        {
            0x89EA76772B490CC2ULL, 0x93EAF7849A1BC22BULL, 0x5E430972931A81C6ULL, 0x897026628477475EULL, 
            0x3FE01D32DA618EBAULL, 0x2F795A4F95EE75A2ULL, 0x156F7526A0DADBA6ULL, 0x26ED4E355014ABE0ULL, 
            0x1F1C3A994AC0B37DULL, 0xFA690C085FA72298ULL, 0x315E8BE3DF933434ULL, 0x72580AEB64C764E7ULL, 
            0x550E3F3FD83645B1ULL, 0x6E360B8C3192CC9BULL, 0x728C4EBE2FF173B8ULL, 0x65CAAF0C18972BE3ULL, 
            0xE6FBAD1F08F34BB9ULL, 0x3E611E337B43E15CULL, 0x7DA1876FA6D568E4ULL, 0x659C57EEF03954EEULL, 
            0xB47D99DF74B1F84AULL, 0x2F00BB98CF37F95CULL, 0x475B2B0EA4EF93E6ULL, 0xD2D45151430EB348ULL, 
            0x6EC8D1EC4FFDB667ULL, 0xD86E0759AD656EF9ULL, 0x6E4E091415A97FFBULL, 0xFC8F5FAE113A9E6FULL, 
            0x669F6E27455D65F4ULL, 0x6BC6512BE31E1D1FULL, 0x8C829F6E5279BFA6ULL, 0x71712965BCAB62C7ULL
        },
        {
            0xF1B26747E6A2E440ULL, 0x71D7AC9EE420286AULL, 0xD959AD71BB40E3E5ULL, 0x76052A821999DF23ULL, 
            0xF7DF3E7B1F6E2CBEULL, 0x1BE7850C043D482BULL, 0x373BD8EA44F036C5ULL, 0x4FDB91F31F8F8C3FULL, 
            0xB8388FDA83FF3308ULL, 0x7766EE9C8955E08BULL, 0x6EFE51962D51AB44ULL, 0xA7A6DDCA966DFA0AULL, 
            0x56827E9A22004B92ULL, 0x4C46B67FBB4FD308ULL, 0xC0722245035DEEFDULL, 0x7116AF4359866176ULL, 
            0x18C748C739504BCDULL, 0xC2ABDA99F280AF0EULL, 0x42017D3DEB41CAFBULL, 0x6EE87104C950638EULL, 
            0x0B36E4C37B058683ULL, 0xD9CEC72BFF6FFA48ULL, 0xA5E6D32410AE0534ULL, 0xCD20E82EEAF3C455ULL, 
            0x5A11D77B632DF900ULL, 0x4D5DAB862C9DBC0CULL, 0x66446EB4CFE1BF12ULL, 0x9FC840671D42F890ULL, 
            0xED2A7A171C64B0F5ULL, 0xCAD9FD01FCB8A2D5ULL, 0x3754617F1512D37FULL, 0x9C2F6E57FB28CB15ULL
        },
        {
            0xB8ADFAF2BA704F2BULL, 0xB8C57E687324F9A2ULL, 0xA1D7FBA22D4D1E08ULL, 0x703B4C17EF23FC9EULL, 
            0x91E09E3FE62C89DFULL, 0xDBFC45952BF1E187ULL, 0x4B8DE301BC9FB969ULL, 0x224D62293C3B6079ULL, 
            0x9981A3B39DEAF0C8ULL, 0x48C3A4EF2FD1C839ULL, 0xE7F4000019948BFEULL, 0x2AF4060A4313C5BAULL, 
            0x99799CD8AE7E5720ULL, 0xB88D4916C5C80D6BULL, 0x5518D8CC7EF7224AULL, 0x3D90B3FAA0398B46ULL, 
            0x937484809506035BULL, 0x57A3484DC6D78A36ULL, 0x148141EBEA5A4222ULL, 0x5C76758977F9CEF8ULL, 
            0xFE2C4FF64C2BF706ULL, 0x853DB6EB361BF598ULL, 0x0D618E0810D51CE4ULL, 0x30C2579DA0810F3EULL, 
            0x0977B53BA3E501C6ULL, 0x790A4864CFAE1AAFULL, 0xB4B2ADA3D08D0857ULL, 0xD03433A73D6F99FDULL, 
            0x520D53304432E07EULL, 0x3F83C3B7B63B8AE8ULL, 0xB539BDDCD89BA4F8ULL, 0xEB17279CD933C639ULL
        },
        {
            0x726C71CE1A224CBBULL, 0x74367CCFD63455E4ULL, 0x04C2263B4D7EAB76ULL, 0x2E10841295AE0BE0ULL, 
            0xCC6967CC0B40FC17ULL, 0x7D218DC8097476F8ULL, 0xE31531E845C0DC62ULL, 0x1E83BE26067B360AULL, 
            0x6B8BF7848EC9C144ULL, 0x11B65EC1DD6EB330ULL, 0x7C9E092B18746FCAULL, 0x12BBFC517E39B024ULL, 
            0x395E48C0B78B75C0ULL, 0x2F701715D48039ECULL, 0xB2F0177CE187DCABULL, 0xA44ACE059C277E6AULL, 
            0x75A676B3CBA17C83ULL, 0xF00DC1806CC81EC2ULL, 0x77FBA716B50FE54EULL, 0xBE2DFFEA347A9D1FULL, 
            0x9D4ABCB87B33BC38ULL, 0x2CD240D256697BB2ULL, 0x1295D2E679DCCE14ULL, 0x2E85CAD99AB45C13ULL, 
            0xC87969D2B706B7D8ULL, 0x94454B6FD1D4B8E2ULL, 0x044BF9EF93781336ULL, 0xFF0994FC842A7F45ULL, 
            0x9A7BAF6ED3642913ULL, 0xB2783E69F69EBA71ULL, 0xF3FC0576AD698010ULL, 0xC7734E0D9992B4ADULL
        },
        {
            0xB70512456E1462E4ULL, 0xCD21C0E7E2ACF27FULL, 0x69CC31D69A09BC1CULL, 0xD5CBBDB63562A266ULL, 
            0x5E1BBF747379EC27ULL, 0x4A228118B28EC9B5ULL, 0x00B8B7C0A68A39F1ULL, 0xC9ECF961A077AA19ULL, 
            0xDCCA11ABB5C17A74ULL, 0x38AA6E877665E9F6ULL, 0x1C92FCB203F73B63ULL, 0xE9D3D2CA75AC15E7ULL, 
            0x54C838B0AC2A429DULL, 0x2574A7612864E5F2ULL, 0xF1FF337E74639353ULL, 0x8DBDD187E625449EULL, 
            0x66B1F257A1D39D51ULL, 0x260409F8F9CA01D1ULL, 0x5117B47CD543DA52ULL, 0xB7C03156EDF82B28ULL, 
            0xE88576730004006FULL, 0x307B84DCE696EA7EULL, 0x676AC2FB06759E2FULL, 0x62BBA8A765F7639CULL, 
            0x9BD48E1C3F811F3AULL, 0xACCA4138F9B8392CULL, 0x508B81B0087D91EFULL, 0xBEBF6108E04F6879ULL, 
            0xD09F51C0CDC287D8ULL, 0xCD1BFE439373D184ULL, 0xE9BDCF8BA4E58556ULL, 0x29E3820B588E01E0ULL
        }
    },
    {
        {
            0x10148935D892869EULL, 0x91B4A4DCDB5E7E64ULL, 0xCA2560FDE6556497ULL, 0x05A144ECB43073DCULL, 
            0x50489B8C2DAB4DD9ULL, 0xDE7596050A4E68D2ULL, 0x49AE586D5695F803ULL, 0x94A76F922F2CB3C5ULL, 
            0x25066A1F4E4DD679ULL, 0xD4093E3C7C564D4BULL, 0xD9BFCCE4DD401931ULL, 0xF0A3BD556F69B3D4ULL, 
            0x65287597872EBF2EULL, 0xE3637C24C9F8EF85ULL, 0x0387AB51F747A8C8ULL, 0x35FC71B47CF8C7DEULL, 
            0x7435400989F89917ULL, 0x24BB40ABF5BA57A4ULL, 0xEAF01E95E016402EULL, 0x00347839DA76815DULL, 
            0x238D8BA4BB4C2BD5ULL, 0x86F1405ED0A24CCFULL, 0x203902270487202CULL, 0x9E05A98355DB4399ULL, 
            0x9B560F1437D846FFULL, 0x598EDA64174040ECULL, 0x830B38F9D2615B7FULL, 0x918F03FB60691D72ULL, 
            0xBF862F9117539FBFULL, 0x47245CD6198B5B7DULL, 0xC980E6B2F132F840ULL, 0xF903079CEC60C9E7ULL
        },
        {
            0x019DE59F6325BC00ULL, 0x2C507E74212D2DE0ULL, 0xD460B5FD23FB596DULL, 0x828AA16CC24C8E34ULL, 
            0x66C1FCE253622CCBULL, 0x68EEA190B37442CDULL, 0x22A9D8560F9A23CDULL, 0xF5FC53C0C7BE65E3ULL, 
            0xBD297F2CDD679C4EULL, 0x3FC51CC4CA81F3D8ULL, 0xEF667A13DCA8D678ULL, 0x9AAC139A4E286D39ULL, 
            0x8B7F6002569AD3CBULL, 0xC9489B797DE63D25ULL, 0x2156CEA1EFBCE4EAULL, 0x3C9414DD6C2AF148ULL, 
            0x44C59DA1D2D10151ULL, 0xA0CCFD811A41793CULL, 0x6FB0B40FE2EDA6D4ULL, 0x563EE788319BAFF7ULL, 
            0xAA443990D597C4C9ULL, 0x968C837473134E22ULL, 0x89E92BF4CC0606A4ULL, 0xA1269C95D479F291ULL, 
            0x199E9873ECD270F8ULL, 0x1DAAC3FB77EA1AA5ULL, 0x3A7A7E8DB29FF690ULL, 0x37F0249F76B93DE6ULL, 
            0xD48C60DE6F51467CULL, 0x59300643E9781928ULL, 0xA6239A28D53A51CBULL, 0x56474D0546E63DEEULL
        },
        {
            0x0679B58F9B74F717ULL, 0xD240EC7FB5F8B5D6ULL, 0x6E12FE04ED9FAE59ULL, 0x915606145A805DB0ULL, 
            0xF262BD67EFDBFE69ULL, 0x591E4E6E044F9ABBULL, 0xFFE62E5F403B7770ULL, 0x8A162EB37FBCC71BULL, 
            0x5291E55E89ECD882ULL, 0x2AB2D9F3EC8AFFCAULL, 0xFC5F06F6BF366A06ULL, 0x30716CBA088ABE82ULL, 
            0x02A8CE84AFA27384ULL, 0x1C23A95DD0D7D8B7ULL, 0xD4FE83C98AC14F8CULL, 0x3EA3055918553EF1ULL, 
            0xF341ABA51CB635B1ULL, 0x3013BBDD2EEFFABCULL, 0x511657F744E9149DULL, 0xE32E2CB9DC623A36ULL, 
            0xD0708ECDFEFD98C6ULL, 0x017C9A7BF3B7A613ULL, 0xE0F861E7676C9A78ULL, 0x954517825C7C94EEULL, 
            0xD05E9390F0D84B4FULL, 0x7DD50DF2D3A678CAULL, 0xDB2C4136487C3153ULL, 0x601A3243D7499758ULL, 
            0x765385DB58FD6FCFULL, 0x6C90F24EFB3F1C91ULL, 0x2836A667712D9C18ULL, 0xE0E860247F9A414EULL
        },
        {
            0x92EA9BF722816285ULL, 0xA735CE14683CFB27ULL, 0x3F48E837DCF20A41ULL, 0x72E044DE6AF3BD74ULL, 
            0x717D1AD20981DDDBULL, 0x70E28EFA649B051AULL, 0x067BD8AE6FE33BACULL, 0xCF30C2731ED4C0C1ULL, 
            0x6889C78FF5BEA496ULL, 0x0358D08A84AD6385ULL, 0x8A785C3FDFEEDDC6ULL, 0xEBA03263CFDEE213ULL, 
            0xCBAEF3D98071CC66ULL, 0xD1C8F0785ED62908ULL, 0x5D36E7C627B127EFULL, 0xDF7A58894C7BD555ULL, 
            0x6A3380C2E3BA1CC2ULL, 0xA91FCC2321F0E5A0ULL, 0x657044F451CB02B5ULL, 0xA6EB4E75890AC716ULL, 
            0x144A94C93015198DULL, 0x5CEE480553287D97ULL, 0xC66D512D0C33F4E1ULL, 0x23584ACF6FB97F82ULL, 
            0x05087685FB49F7E7ULL, 0xA1D254DE66A92C41ULL, 0xB216725EB9DE18A8ULL, 0x393B6B1C793585ECULL, 
            0x4A991816F56535E5ULL, 0xA5E211BF19A913B8ULL, 0x8B16609CBD157E84ULL, 0x003D89E945961F10ULL
        },
        {
            0x77FAAE58342A43C9ULL, 0xE36350D09025AB03ULL, 0xCF7DE85048EA0C6BULL, 0x643E1EA908749D03ULL, 
            0xF316B6FCC0A0DA6BULL, 0x49F5E059A9D356DDULL, 0xD71BD12A37AA101BULL, 0xC65071EE796B7496ULL, 
            0xC574B3AD71E94813ULL, 0x64448200A84B77DAULL, 0x68097FB07BCF3531ULL, 0x78C5C6DE5DB2B3BBULL, 
            0x151B032163912A76ULL, 0x60E2CA189B4BBAFEULL, 0x562F867BF5E065BEULL, 0x3CAE2F376FA4D2C8ULL, 
            0x7457497656241837ULL, 0xA1A1C6E676011142ULL, 0x98C767C7D59F8703ULL, 0x9429B2AEA894EDDBULL, 
            0xE809F4F2B767FB0BULL, 0x4AA817660FF93C74ULL, 0x7977D30D5A96E9F0ULL, 0x7EF7D35842091AC0ULL, 
            0xEF1BA127516FB63EULL, 0x4202801359651EC6ULL, 0x47B5A3A26F735F86ULL, 0x4BC72A3688EF2210ULL, 
            0x04132013864DDA9FULL, 0xC1F8A9246337ABEFULL, 0x688C29FB5270FA87ULL, 0x4E851EBB885CF38BULL
        },
        {
            0x13D7C50DA109A96FULL, 0xBC630C7A7C48B543ULL, 0x299D24ED6424BA20ULL, 0x35B395104A0D8AF7ULL, 
            0x4AC68CB691406781ULL, 0x1649152D82123B99ULL, 0xE1E83E4F432678A0ULL, 0x5AA64E1C2378F6CEULL, 
            0xBE9AA0F52C118196ULL, 0xFCF0B8FE632A3088ULL, 0x42408EE4A27BAAB4ULL, 0x4C1E2D5497EACFBDULL, 
            0xBA29090E267706B4ULL, 0x8D77E27AB687F3A7ULL, 0x3853B2A6FE02E1B0ULL, 0x9E4B3D502FF74AB6ULL, 
            0x699322FEAFB5A7F5ULL, 0x1292F849793EC120ULL, 0xFCA3621614CCBAFCULL, 0x74856F36C85876B3ULL, 
            0xD7B09BB51BDF7709ULL, 0xEB7341F9D727D4CDULL, 0xB4B6E16A5E5698CAULL, 0x69B2DF9E6787CF88ULL, 
            0x82D1EC165388A3AFULL, 0xE71CFD91361F264FULL, 0xA3394B3C283974D5ULL, 0xD8B4F2A3F63FDF00ULL, 
            0x1F014696BE1218D4ULL, 0x599DB271292BD533ULL, 0xCDF397466DCB1CBDULL, 0xD5AA287801D58ED8ULL
        }
    },
    {
        {
            0x8F96E8620D7BFAE5ULL, 0xB7EC4575A45A38C4ULL, 0x0549C1337B435044ULL, 0xC6BF2CEDA9AE82B3ULL, 
            0x2D08AFA0E044211EULL, 0x40ADC3D5103DD58EULL, 0xE9BC2C69288C4CF7ULL, 0x7591ECA0C3ACF611ULL, 
            0xB36E747B498D5FF4ULL, 0xF53AB7E912B57474ULL, 0x8E50BA644C8BC062ULL, 0xE61129DE507F80C0ULL, 
            0x92722536087B78DFULL, 0xD34982E172ED3445ULL, 0x976C3FBC4DDF585DULL, 0xCFE5F1E413C496A2ULL, 
            0xFCFE532C80D84E5CULL, 0x74D4D890B37CAD29ULL, 0xB6375DBE07A18262ULL, 0x59E5009C83136AA0ULL, 
            0x6DD178A4110C6F82ULL, 0xEF38205B04A00B43ULL, 0x1184EE8DDE8DA74BULL, 0x136DE7CEE9FBA362ULL, 
            0x0771B7B02F8A3D79ULL, 0xFC494D29CC3890DFULL, 0xF80859D506F9F0F7ULL, 0xE4ECE241D7174BAFULL, 
            0xEC19FAB13CF9E0FAULL, 0xB5D5102AD8F2B210ULL, 0xF5496C947FBB0382ULL, 0x2CCB1C6B4CB4478BULL
        },
        {
            0x40631554F3A5B5D1ULL, 0x7C24B03B9DB5CADFULL, 0x647FA05393524533ULL, 0x81316D758BFF2598ULL, 
            0xC9A8622FEE82A27BULL, 0x3F1EF5E53E39309FULL, 0xFD2755DA14ACC2FBULL, 0x1657C13DA8FB13D8ULL, 
            0x08057EC698D50046ULL, 0x9CDA998F5885E000ULL, 0x5B748202D77B515DULL, 0x80B7454A3574E881ULL, 
            0x162F01414946D2ACULL, 0xB92FBB141DE4523CULL, 0xF738735107E0BA92ULL, 0x6E7A66A9BF4D68FAULL, 
            0xCADDD1A99FAB01B5ULL, 0x091934971C0E6D11ULL, 0x1040260D69BE7F0AULL, 0xEFFF4A39AF0C8B0AULL, 
            0x593B08A36531632CULL, 0x8B4B6D7257835B7FULL, 0xA628B6AD3A9603D3ULL, 0xBC5C08BE51BD74E9ULL, 
            0x81A0EBCDDE2F5E35ULL, 0x30D84315821D7DB5ULL, 0x80B362C12EE4528EULL, 0x7D83BE03B659BE7AULL, 
            0x9C609AB0D08C0AC9ULL, 0xD26005C4F66C1505ULL, 0xD4E737215E400A98ULL, 0xAC5E01878ABEAB6EULL
        },
        {
            0xCBCCB7BE79983DB5ULL, 0x625B500E643F265CULL, 0x3F432FEC1C031033ULL, 0x9099071C3E407EB2ULL, 
            0x2ACF41536C481B65ULL, 0x209C3516CE8B299EULL, 0x315BCA0754E4C297ULL, 0x6341B6BEB2EEF380ULL, 
            0xB48F722F220F2666ULL, 0xF6E27452D61A5A1FULL, 0x9B128C10C2A3D891ULL, 0x642E258449CEAEE3ULL, 
            0x11E01881E6E72841ULL, 0x354F46891D0858CAULL, 0x04F6B3EE9B56AA62ULL, 0x4ACE07ADAA129685ULL, 
            0xFE865270E46422BCULL, 0x6F5BC2A72CD2A7F3ULL, 0x2D5BA430C1DCC37EULL, 0xA2A2982EAE4DD4EFULL, 
            0x77DD886F14835DA6ULL, 0x664D99ED63EECC5AULL, 0xDAED16DF467D29A6ULL, 0x5B5D03E36CAF48DCULL, 
            0xA097C73EE6D1F5CCULL, 0x3680326BAFCCC099ULL, 0xAD253CEF1D20878EULL, 0xD9BD1966739057D7ULL, 
            0xAC936EB0CFD54045ULL, 0x62D5FDBCF4121F1DULL, 0x5194C5167A13BAF5ULL, 0xFA65D92945BDBA46ULL
        },
        {
            0x3694D1E4B4DA042AULL, 0xA98AEC78ACA02F95ULL, 0xB1A4158A3C6C3FD2ULL, 0x1186F60EBB10DC84ULL, 
            0xCB6239E259D5D0D6ULL, 0x35ACC0EFAF9ABD72ULL, 0xD71923E924ACD7BDULL, 0x1F291C8A50A3263FULL, 
            0x30E9DB162B10B2E0ULL, 0x1CE810E02C57FA00ULL, 0x713CD959104BA57FULL, 0x91C53EB5D18F8A3AULL, 
            0x1CC8CDD79C584402ULL, 0xA41614BF1CC24B62ULL, 0x2A82217127E8CD91ULL, 0x6FD29F234B6F8808ULL, 
            0x119FFEAE74AD2639ULL, 0xCCA9C348141881C2ULL, 0x5EB9BDD2673022C2ULL, 0xCA8011F3BDD12F5EULL, 
            0x346249834076468EULL, 0xB0FC1CD4C6C54AF0ULL, 0x3FEC20F61E674E12ULL, 0xB889C03D20B82C75ULL, 
            0xFBBDF2A6F34F3073ULL, 0xADE7A22926D406FFULL, 0xF830D799E1FD1ED1ULL, 0x3BBD429775E45980ULL, 
            0xB16C1107D195631BULL, 0xBD0BEFE3BF251F01ULL, 0xF5F5C258FFF9210AULL, 0x386C937D743428D3ULL
        },
        {
            0xEE29495A49E43B32ULL, 0x4820ACF5467A3E42ULL, 0x82ACD54FFF588CCEULL, 0x6C91E480DF67F65CULL, 
            0xCD35955618184ECAULL, 0xF4ECBA90814ADA20ULL, 0xC69B612A8C1921E1ULL, 0xF4A45B839248A25BULL, 
            0x493A895284CDF33CULL, 0x9A21D7AB6A163196ULL, 0xA7AE80DCC21B64FCULL, 0x36AB4B25BC5CD36AULL, 
            0xCD352A06EC209BB9ULL, 0xF5EBA45E458D3378ULL, 0x63DE0E84F1F52E0AULL, 0x240CB91466B42840ULL, 
            0x3A13389113D9F1F4ULL, 0x8E0E49E7FD7D843AULL, 0x731E7935FC888C44ULL, 0xCA32F5E0646B2C36ULL, 
            0x48C79337FD847911ULL, 0xCF0A8A8101EB81D4ULL, 0xC78986A54934B517ULL, 0xBD9B729346393F9FULL, 
            0x418A2D6ACEC45735ULL, 0xBCDBB9459747D4D7ULL, 0x39A0CD15EE87B9F1ULL, 0x435027612B586D1AULL, 
            0x3BF63F2F16125BF4ULL, 0xDFC80A546DF9DAD2ULL, 0xB4CAE08EAE8CCF04ULL, 0xB50E2C633EF3487AULL
        },
        {
            0xD0090A033E7F0A56ULL, 0x2929E001733464E2ULL, 0x34B04182AF35A429ULL, 0x544680B51A0E4C2EULL, 
            0x3022F75C75EDC690ULL, 0xF4708F169DCC8D84ULL, 0x3A914275A96EDC2AULL, 0x0BC5A1D44B44C2E2ULL, 
            0xF513ECAC55EEB06CULL, 0x6FEB938BD4920472ULL, 0x1FE13657A2BFA941ULL, 0x9998647C0501F351ULL, 
            0xA77A5DF91260054EULL, 0x2D732A4A7DBB195BULL, 0x5CEF6713857794E5ULL, 0xC9F96B73175A0C0DULL, 
            0x6AD3106A615DE728ULL, 0x491B8B355B202C07ULL, 0x1D42E58C17034EE1ULL, 0x509F2EA18944CFA9ULL, 
            0x5E7D464281161EC7ULL, 0x553D568EB7DB95EDULL, 0x44F139DABAB6E37BULL, 0xAD9BCE64717C00CDULL, 
            0x232102682E3D15B7ULL, 0x6C64501325495764ULL, 0x4E1403314A2B6183ULL, 0xC23FE3D96241C88BULL, 
            0x5BBB51A57D0601DFULL, 0xAC0F72FF851292CBULL, 0x26816B382425CD25ULL, 0xC0ECF69EFE2F53A2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseBConstants = {
    0x2C499AA41C2677FEULL,
    0xD9A490B39DA3AF61ULL,
    0x380538B0B596E8C6ULL,
    0x2C499AA41C2677FEULL,
    0xD9A490B39DA3AF61ULL,
    0x380538B0B596E8C6ULL,
    0x5A67CE55A8A5AB08ULL,
    0xEB82A05A96B426DFULL,
    0x4E,
    0x96,
    0x5F,
    0x33,
    0x6E,
    0x02,
    0x99,
    0xF9
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseCSalts = {
    {
        {
            0x96997D479681A9E8ULL, 0xDBE7390F8CC3DFD0ULL, 0xDE8D4373EB545D6CULL, 0x67FCEE44B6FF1311ULL, 
            0x3D1EB49A0DB40B1FULL, 0x47E8553700C3C7ACULL, 0x8AC884B135ADFA99ULL, 0xBC566FF3871117BDULL, 
            0x1EF90C97CD60AE29ULL, 0xC5C29ECD46A4FC27ULL, 0x09CCB88D0970757EULL, 0x09C645CD96FF238EULL, 
            0xC1A5C938353E844BULL, 0x3E82A50F99AE5491ULL, 0x9A03D840958F9CA7ULL, 0xF3DFBFDA7BE2EFDEULL, 
            0x4CA958111EF471F9ULL, 0x9134E3E945840FBFULL, 0x366CA6437124D1F2ULL, 0xEA8FBAD0D81684C8ULL, 
            0xEE3B3EBB9AB0FE13ULL, 0xD45456846823A7EDULL, 0x8133A82495F39536ULL, 0xE9075156153031D8ULL, 
            0x20A03EF39D155BA3ULL, 0xBC21ACE3D1726C54ULL, 0x02453796D8585FF3ULL, 0xCF3E08DEC6570FA7ULL, 
            0x9EBB2BA5AEBC2601ULL, 0x2263CBCB22F14BA7ULL, 0xF8FD2E12AABEF377ULL, 0x8851D53EB17708DEULL
        },
        {
            0xAE12988A92C7A390ULL, 0x07B0B173FF77F298ULL, 0x83857E8956033B0AULL, 0x6A26EBBEA302699DULL, 
            0x892028A9DC4271CFULL, 0x536DAD3C86FC7D45ULL, 0x899262A072573385ULL, 0xF6EE093F67A1442DULL, 
            0xA0D74603BC33FA71ULL, 0x168C5B08EBA47782ULL, 0x95FB43AD542F42FBULL, 0xDFAC40976DDD2C80ULL, 
            0xA75FE8EFDA7D8EABULL, 0xD2D77DD4D313D732ULL, 0x7722D0788FBDE9DAULL, 0xDD2E5ED5E0ED13BCULL, 
            0x5AAC6D08634CA4A2ULL, 0xE95A44C4CCF69088ULL, 0x52B1190E3E4553DBULL, 0x5BC698D081B2C48FULL, 
            0xB9535FA1AD1D4D0CULL, 0xDB552FA30CB9CAA3ULL, 0xEEE3834AFD32C989ULL, 0xBC7C11C791A950D1ULL, 
            0x19B7DEDACB5640C1ULL, 0x4A7A5F29BE02C0B2ULL, 0xC986BA1BBE64417FULL, 0x54A74107B93F9D60ULL, 
            0xE23ABDAEC1E26943ULL, 0xF012E903AC4B4590ULL, 0x45347EA8B07651F9ULL, 0x2A4B5908C207D7EBULL
        },
        {
            0xBCCDCBC26048AC7EULL, 0xFE3793D9C69BF180ULL, 0xD3F92D9256B9B889ULL, 0x2F9D40C06B08E068ULL, 
            0x150C1E05A1F1E43EULL, 0xB708BBC29F1B84D5ULL, 0x8009BF6BE77D1ACCULL, 0x6F5F362DB80EE88CULL, 
            0x906C78B9BDB93D0DULL, 0xAA93684708AB3AA4ULL, 0x2BBFAA0B60A7DA47ULL, 0x800147B19814FA0CULL, 
            0x52B93CFDCE8C23EFULL, 0x8C1C362E560FD908ULL, 0xCC91280AD7F31699ULL, 0x349F8949E6613C95ULL, 
            0x7D688EC8A63EBF9EULL, 0x63AE0CB4488CD6A6ULL, 0xB4179DD5F4349EDBULL, 0x59018DF0DAC34DBDULL, 
            0xF18DC6DAFE2D727EULL, 0x79C71212C1666E2FULL, 0xDD7F07A9E4B67CEAULL, 0xF6F61066ED1CA5C3ULL, 
            0x21DB8D9767411AE9ULL, 0x8ACBB779F1B6E12EULL, 0x45DCA47147F46158ULL, 0xEB8CD03B7B627DC1ULL, 
            0xEBA824D16A64EAB6ULL, 0x88E015108BEC2CA8ULL, 0xFAEB512DA1CB294AULL, 0xC3221F5804487B59ULL
        },
        {
            0xCAF1D2B9F1885964ULL, 0xFF8EA67D3AD08DA3ULL, 0x5098E940C123C7B8ULL, 0x82ACA6877F0F01A2ULL, 
            0xD0309BF80693EBC8ULL, 0xB4009342A4CAC1C2ULL, 0x4EEE85518F2451C4ULL, 0x4F5736BF372CC844ULL, 
            0x94552521AA4D5A8FULL, 0xB44CE547593D4907ULL, 0xBADF303AAFD36EE8ULL, 0xBB9A1CCBEC2F5A8BULL, 
            0xB6A5D701124D2240ULL, 0x1ECCDD6398FA1835ULL, 0xA986F2EA8C4CB95BULL, 0x9DF9DE4504691E52ULL, 
            0x9F82690EA9E36D78ULL, 0x553632D4ABEA03B6ULL, 0x54956F037109012FULL, 0x4EF4CFF9F1EF6AD9ULL, 
            0x55D54308E01001D0ULL, 0xD5433DC260B2BF96ULL, 0xF450612DC470F339ULL, 0xE0D4B0529A4E4E20ULL, 
            0x98679C15AF3C8301ULL, 0xC8C262D4343CBA1FULL, 0xDBF77BB45D58C674ULL, 0x9F498688E1239433ULL, 
            0xB69B2F281B37DD8FULL, 0xC04397462AC4EE03ULL, 0x356B9B82B77D81ECULL, 0x9E705DD15792637CULL
        },
        {
            0x3289AF7BB387F122ULL, 0x9779FD1132A13B7BULL, 0xBD73C729DECA46FBULL, 0x9C73A82B371FFA6BULL, 
            0xA5BEAF988ECACB8CULL, 0x1B425E970C91EBB3ULL, 0x09598FECBE5160A0ULL, 0xCA3A9CD07FE48740ULL, 
            0xEAE7EA3EA8A694F2ULL, 0x6EFE05607A041C6EULL, 0x65DB1D95BEB64C5DULL, 0xC5503D0F194ED65EULL, 
            0x17824BAE5B790FE1ULL, 0x27292CC4D2E78AE1ULL, 0x868E5B46C9C490BAULL, 0x5C7D7E64CAACC032ULL, 
            0xD91E1E1908B6CEB8ULL, 0xD2AD4CDA793ABBAEULL, 0x3816B8695A807EDDULL, 0xEE2CB6547F9F0F2EULL, 
            0xC2C79CB575E5D866ULL, 0x488E4EA326FF3396ULL, 0x939536345C5ED35DULL, 0x421CB651438DF59FULL, 
            0x75F24BDD6801DFB6ULL, 0x6FBB057F057E5EFBULL, 0x62F56160A4E55D85ULL, 0x7C4F8276D53C3131ULL, 
            0x55DFB64E5470C51EULL, 0xB8F63510D2190F9BULL, 0xA0FAE53CC01773E6ULL, 0x65503598BECD0C9EULL
        },
        {
            0xAA8BB098FA4504F5ULL, 0x980019D502C268F9ULL, 0xC885E7B2FC6C09E3ULL, 0x8EDE8B89DCB838BCULL, 
            0xB21EF868B5CAEB60ULL, 0xA5B38B59E5E5E3D3ULL, 0x6F35D37B7EAADEFFULL, 0x04707EC0D56E500EULL, 
            0xF23AF5ED456BE0FFULL, 0x4FAE00F20A00879BULL, 0x8842EEBBA14C2F86ULL, 0xABABBA9359776591ULL, 
            0x81A1B3B4DE340423ULL, 0xF3576AFBD6E231B5ULL, 0x07A9047846E65A0AULL, 0x0A341BA867FF3207ULL, 
            0x17E263AD63DBBE9CULL, 0x9341DB0962878F72ULL, 0xDF3B6E3DE72E23B0ULL, 0x340E4CBF316139D3ULL, 
            0xC774B6694935718FULL, 0xA9F5CD254305A6C7ULL, 0xA2D9E6CE3F81CC66ULL, 0x03DA4FC3B9E186C5ULL, 
            0x557B2DE4C602954CULL, 0xC90A9B2E1E2C9CB2ULL, 0xC8AD3D7B10E62D67ULL, 0xDC0D95BFF39A8702ULL, 
            0x070F85A1A7451EDDULL, 0xEE30B0316953504DULL, 0x44809712E08986B4ULL, 0xAEEC7E0259A872E8ULL
        }
    },
    {
        {
            0x14DF1C8BDB0B5BB6ULL, 0xA629095778EBC8E3ULL, 0x8551A62A5D744064ULL, 0xB099F52E9D9391EBULL, 
            0x1FC6A5D5E77FFFBAULL, 0x045E7137EAD812D6ULL, 0x82ABC92CEBB7B2C8ULL, 0xC1D58568EFA3B535ULL, 
            0xB58548DB418842C0ULL, 0xB804CB6A665CD599ULL, 0xE2C36D93E6453B7EULL, 0x387AA81EDCE3CDE2ULL, 
            0x6F92D303707CAF60ULL, 0x9946A89F0FF638E0ULL, 0xED3A04C29CB50ED0ULL, 0x3F732D8791CFCA21ULL, 
            0xC2AD536DF730BE98ULL, 0xB5F645174DD76AE8ULL, 0xFA7CF8E6DF20BBE3ULL, 0x26E8C5E890021EA9ULL, 
            0xC7CAC836B275352FULL, 0x3031C130CE506D23ULL, 0x393C7ED8382939D6ULL, 0x7339D92096FD828BULL, 
            0x113B12A069154101ULL, 0xF566B018838C8EC8ULL, 0x1957C7849187662FULL, 0x0C44F472AA20DD13ULL, 
            0xC4C87CD0CD1ECCAAULL, 0x74A6C425FC9835CDULL, 0xAEC2361CDCCD531EULL, 0x5E63C8357DD00F7CULL
        },
        {
            0xA7AE3E9B37DF8E67ULL, 0x8BCD5CB901CFB919ULL, 0xAA615817788B4201ULL, 0xB491B02319BB5CD1ULL, 
            0x49F1CD1C92D73A5CULL, 0x174067DEA275DE89ULL, 0xF345631D512E4286ULL, 0x6A79DDF4C9B07477ULL, 
            0x638AF5EF70AE1BF4ULL, 0x5C1285F780224246ULL, 0x3512E38BEF9F4951ULL, 0x7ED85CD4266AA280ULL, 
            0x9E0FE357148D4C8BULL, 0x8A06F018799A1FE1ULL, 0xB67580AB88DB2922ULL, 0x9B94B98F9856A10EULL, 
            0x71A34D7355833183ULL, 0x97E51912628D0C91ULL, 0xF3CBDA80FC0D4D5DULL, 0x02E69F76887BC55DULL, 
            0xC22C039C61DC280AULL, 0xB55899D59587A284ULL, 0x71CE892F8368E58CULL, 0x75AA1B5835651897ULL, 
            0x980A0DFD099C3AA3ULL, 0xD594053743E80497ULL, 0x22AAAC179362CD05ULL, 0xF41F5492CDDB3663ULL, 
            0xABAA1B3EA6E9FE9EULL, 0x01E59C20C9F31963ULL, 0x45E36B2F7565592CULL, 0xDDE383A89DB8BF31ULL
        },
        {
            0xDD7DB925426A8E11ULL, 0x6C13CB373D4E8839ULL, 0x454BDB5D7A99BE7CULL, 0x4FC1111EF4E005C5ULL, 
            0x0538EFBD15774EE3ULL, 0x0BE50DC7E971F765ULL, 0x49FBEE65700999FDULL, 0xEDA0D06416D1FE97ULL, 
            0xAA6803EECFF18F3BULL, 0x0132C0818275BF7CULL, 0x1B35329636E87AB3ULL, 0xC403E2EA72A33B68ULL, 
            0xDC82FCE1F2125178ULL, 0x77B11E8F67FCB06DULL, 0xBFF1EE32FD2F19A2ULL, 0xEDD8E08D757E2AA2ULL, 
            0xC4C94A37DE0E73B2ULL, 0x8C7A263243546576ULL, 0xB68EA9224DE4D197ULL, 0x3BBBCAE220168291ULL, 
            0xE093566D57F00930ULL, 0x2E4755E63B8ADCE3ULL, 0xA2E559D261FCD139ULL, 0x2421E6B9CDF04EA8ULL, 
            0xE7F83B4AEA96946DULL, 0x09E2F21C09B88D0AULL, 0xB0D42981EE99DE9EULL, 0x6B30C864C5ED1DB7ULL, 
            0xB6D8E5197334993EULL, 0x7565F4F6F57D6549ULL, 0xBB644FA3E7041C7FULL, 0x511060C33849902DULL
        },
        {
            0xD3BD5EC88E47544FULL, 0xB76958EB86134BD0ULL, 0x8377752AFCC4966DULL, 0x2FB2EDA0A98D06B0ULL, 
            0x6A1EB2C1CF92E1E2ULL, 0x16F3AF58E8F83C7BULL, 0xA102EF138AA4CABCULL, 0xA28DB6D56600DE25ULL, 
            0x23053741726F1FA7ULL, 0xFF931774368FF272ULL, 0xF89B545A4D1A1CD0ULL, 0xB88CBDFBCFDD4ECEULL, 
            0x5D08F90BB147802AULL, 0xA58FC9482D08CC47ULL, 0x5DA4908D7C204C48ULL, 0x4561514CF0B9BC3AULL, 
            0x09E105ADCF1284D0ULL, 0xAC9E60B622F93C3EULL, 0xA8BEE97153E6A2C4ULL, 0xB6D87F01A40C20C8ULL, 
            0x0485C7CA1E0A709AULL, 0x298549B223BA6D9EULL, 0x24734051D4E77D5BULL, 0xD318522BFE6674CAULL, 
            0x5F69F5F8B746B9F0ULL, 0x2CFB2A70A7B49167ULL, 0xFBE11C77E7C52296ULL, 0xF6ED3E2ACA2B372FULL, 
            0x398A47EBE007C756ULL, 0x92AA8FDF9DB10853ULL, 0xEC5368BC5DCCAE11ULL, 0x10EBEE012DD002EDULL
        },
        {
            0x92A34C99D8D25550ULL, 0x307BEA8ACDE6F86FULL, 0x465C2615B0611A1BULL, 0xD75E8C8E454247D6ULL, 
            0xCF07E58FBA6EC667ULL, 0x855BDD9D9629D1D0ULL, 0x12C6545AF0EBF559ULL, 0x013A0A766F56D4FCULL, 
            0x5DF03142E3ABBC31ULL, 0x73D8C7353148E723ULL, 0x29096A7CD4C69301ULL, 0x2F820F8FA15878D8ULL, 
            0x5B401DD47D2E2076ULL, 0x077D740E5B180B19ULL, 0x4F569DD6D0ED0B7DULL, 0x2E7AC3350D635206ULL, 
            0x02D7CC011161F7BDULL, 0x867A53F6B69B2403ULL, 0x7A5CCC2FE1E487EBULL, 0x0D5956C19FA13A62ULL, 
            0xC6DF9875648C6726ULL, 0x7D4829B6E92D854AULL, 0x98D1D558E2CD3C5CULL, 0x4F535DD8D9C057DFULL, 
            0x0C6C04C90BA2282AULL, 0xC077CE905025A28DULL, 0x522782D584BC2333ULL, 0xBDAA005AD1108BC5ULL, 
            0x2CE399EC2AEE8752ULL, 0xBBD7F2651D3477CBULL, 0xB5B7C0A093B45DC7ULL, 0xF866D0281B7F16D4ULL
        },
        {
            0x177B954162F14EF8ULL, 0xE02BD6EB48B330BBULL, 0x1DA861CB8A331BC7ULL, 0xF791700211EC5226ULL, 
            0x3CE768451BA72B73ULL, 0x8278E04F3AF60782ULL, 0x7C3650B77C474B37ULL, 0x1FAD95253C74A6B2ULL, 
            0x5C55A6935684612EULL, 0x7A7BD99EF998B697ULL, 0xEF9CA989063C0562ULL, 0xF6229046057A4D83ULL, 
            0x93652ACD8605C44DULL, 0x48FA2D4E572CD964ULL, 0xA06E024A3BCF1BE5ULL, 0xA0902790A91CDE78ULL, 
            0x7907C5507B8C1478ULL, 0x3523EBAFA2045A11ULL, 0x02DB6E2B6903DB16ULL, 0xE9360C0E2B208032ULL, 
            0xD6FE3C518046B25AULL, 0x71A14394F4351FE7ULL, 0x3FFCFD7ABFF157F5ULL, 0x39B6397A0F8CF187ULL, 
            0x87FF490E41D43863ULL, 0x9C318BE8248705ADULL, 0x2EE2F70E755E9B45ULL, 0x02456F94278B5722ULL, 
            0x48D2A2219DBE4013ULL, 0x78C982344EEA7E9FULL, 0x0F9BB7AA18C0C252ULL, 0x4E6A153D6FBDA2FAULL
        }
    },
    {
        {
            0xF183FF79211A3F81ULL, 0x8E3031B10F97B756ULL, 0xAC779D4221AEC230ULL, 0x51336C260A2BFA8CULL, 
            0x3A2E361DDDB76132ULL, 0x4DFA941B14F01555ULL, 0x7B0CD50B04472AB6ULL, 0x692EDBA92D8F3ADFULL, 
            0x282DDC07FAF278F5ULL, 0xA82A48A0A1044D0EULL, 0x360D36DA1CCEB923ULL, 0x363E4800D993E7CEULL, 
            0x31759B1B64FBBF6AULL, 0xAF2FA759193559C0ULL, 0x2F679C18141BB404ULL, 0xCB7FE07515F694E1ULL, 
            0x80ACB8A9DE764622ULL, 0xFC4639D0667F03B0ULL, 0x6509A78400312C11ULL, 0x4F8C175CFDD3C557ULL, 
            0xF861D843C54CE966ULL, 0x6AC725B84F5351ACULL, 0xA9B541FB5FD2510EULL, 0xD9C079DE9ABE94D1ULL, 
            0x1FACFA356665276FULL, 0xDEC40E83C28BB12CULL, 0x85385DF42EDF7BF3ULL, 0x181570D19D1CB730ULL, 
            0x07241E4DE276C7CBULL, 0xD8102A0AA25A012AULL, 0x3875A86492D26571ULL, 0x01FF9235D5D4E549ULL
        },
        {
            0x89C2FBB594A1ABBAULL, 0x5152CC85D60D222EULL, 0xA0C3B4AE5C047634ULL, 0x6B62B79E2A28820DULL, 
            0x0C66676F2BEF394EULL, 0x4E9549174F842A07ULL, 0x1EB3470CD0188B7FULL, 0x5C512CAFF36E658EULL, 
            0xD2297B7D58878CBCULL, 0x5EE11EFCE7E1D68AULL, 0x601E15B233344934ULL, 0x62D6CCE680E2EB4CULL, 
            0x7031BE2D9EC47146ULL, 0xBFEE90AFE408E008ULL, 0xE16A9D73AF11C8DBULL, 0xAD9E76E06391B360ULL, 
            0xC314F130B5A3B1EBULL, 0x62909932062E513DULL, 0x85B9B379557C8378ULL, 0xE7780B0FD1E1816FULL, 
            0xCA431E8D1DE2D89DULL, 0xB0BB81F48B9EA373ULL, 0x34C1E158AE8CA6E0ULL, 0x4D7388C78F9F8690ULL, 
            0xA29EDB14197992D7ULL, 0x0A4097C10EF2A8F1ULL, 0x8F7F628BE650897EULL, 0xAD1ACEE3EA6789B4ULL, 
            0x2085783C8B93D68BULL, 0x0E4301E549B9D400ULL, 0xA05FC828EE60B51BULL, 0x1CAEF252B3C93399ULL
        },
        {
            0x64A9B63607DE6789ULL, 0x49BEA38617D48F9DULL, 0x0A019D31B0EAC353ULL, 0xF46A8C3140FA6DE9ULL, 
            0x68D5ABBB9BD2933EULL, 0xECE4A818F83735C9ULL, 0x958568B7D2FA6B02ULL, 0x9D8B0A7409F29722ULL, 
            0xE80DF294B57470AAULL, 0xE4A4D0372C384A89ULL, 0xAC5A5643BE846EFAULL, 0xB17BF57BDC970D08ULL, 
            0xAFC53B722D04FB09ULL, 0x6916CB57A0902979ULL, 0x29FC01BEFB1F9A60ULL, 0x7C8E7BE901B47FFFULL, 
            0x268AA1620B656FD1ULL, 0x3D0575C2421A109AULL, 0xF8A9D4E421C4ECD7ULL, 0x7DA7A1383D837DEDULL, 
            0x35042A7C2EA2B5A8ULL, 0x9B57029F2DE3FFDFULL, 0x26AF6883CC153506ULL, 0x2FB4D6D1CE372389ULL, 
            0x7CB83A81A7E5D434ULL, 0x929E60C4A0414F93ULL, 0xB80A4CD3B5149311ULL, 0x627CAF4A9E3085EEULL, 
            0x3727A7229E16A03BULL, 0xC7E04A573DFBFDA6ULL, 0x3547720F1C891FE9ULL, 0x31B5F6099130CE4EULL
        },
        {
            0xF8A6B475ED56BA28ULL, 0xB05CD8D9152487E9ULL, 0x9A3224A8F6676B40ULL, 0xAAB3A4B065CE8D7CULL, 
            0x5BDB41EB7D2E4436ULL, 0x4F57AEE86AB7B526ULL, 0x596847FA6AAA0761ULL, 0xAFE616B3E062A845ULL, 
            0x7D9E2A9B1AB7210CULL, 0x361AF90C052339D0ULL, 0x4E3804B00CBB1DD8ULL, 0x62EDA1D2B1209139ULL, 
            0x8148D8EB74470125ULL, 0xF6561D0BA8EA14C6ULL, 0xBEBB4E097CE8F771ULL, 0xA0F8D0424028B1AFULL, 
            0x6ADB2C85AD821686ULL, 0x94BA41F34BB4CCD4ULL, 0xD0E5C42CB334C231ULL, 0x2C329838486764C3ULL, 
            0xD51BD49B3E1DBAFEULL, 0x8E75AC619FF52785ULL, 0xDF609DEBDF9B55CDULL, 0x50E0BE7234E64851ULL, 
            0x1BD30BA65D9D8167ULL, 0xF000947A25A5DC1DULL, 0x4CB96AD29F40241EULL, 0xB15A9F578D210F6FULL, 
            0x511BEF7801D49CD4ULL, 0x52C999C108802F52ULL, 0x5813B7BCDF96A739ULL, 0x8B322BDE09D20000ULL
        },
        {
            0xE475F533EBCD70BEULL, 0xFE6E5E8CD83839B8ULL, 0xE4C233F400768E0BULL, 0xC9CD3968EC19B86DULL, 
            0x0D907E0FF7B968F5ULL, 0x5DDC7AAAB68ED061ULL, 0x133F6FF5D0EED054ULL, 0xD0444B26FB950D12ULL, 
            0x0BF7036329DA5AB8ULL, 0xB0CCAF1D850097D9ULL, 0x48B5FBC3433892A7ULL, 0xE751CF6936978BAFULL, 
            0x57B127BCBA29423DULL, 0x4132FB19FAE246C0ULL, 0x126E7BC02C1CDC37ULL, 0x038C8C69A51A9692ULL, 
            0x835A89C5B4216C0CULL, 0xC4976D7707EDD51AULL, 0x50CF17C2A21AA836ULL, 0xD45415298AB0525CULL, 
            0xB1ACF0F59B90356EULL, 0xF239BFA0DE6F5A13ULL, 0x0921EA4DA08E7656ULL, 0x9D2425A1B209D7CDULL, 
            0xE589028B1AE3A7A4ULL, 0x6E84659A7CD7D35AULL, 0xE5021255D10A3969ULL, 0x36A8774725E4320CULL, 
            0x66D408E49C9B2D03ULL, 0xA310E057BCA2F2C0ULL, 0x7A7E511E4E100B18ULL, 0x81B9AB53ECD6C535ULL
        },
        {
            0xE75E1CAFC103485DULL, 0x8D337A65ACB3C739ULL, 0x5FF71C65C8F5180CULL, 0xDBA78EA0B0F4FC0BULL, 
            0xAAC7BDEA448090C8ULL, 0x5D85468D5BA7C323ULL, 0x35AB33585A5D2D67ULL, 0x207A258B79760437ULL, 
            0x0A656138F1E53ED1ULL, 0xCA683BB1859360FDULL, 0x8850BDA39A4400F6ULL, 0x4DF8191702418CF0ULL, 
            0xEC11959005308449ULL, 0xAE64E6686BFBC752ULL, 0x7628270475BB848BULL, 0xB987799CC7E0713FULL, 
            0x201B7F8378B4A572ULL, 0x4005F5D3A891F771ULL, 0x01E4C687EC867E38ULL, 0x23357EC22130F935ULL, 
            0xD7FFA8A6BDDFC789ULL, 0x93869BC087759593ULL, 0x1CED98C70E064077ULL, 0x0FEC173CE96058D0ULL, 
            0x59BF03B1B1A0307AULL, 0x744A244682B87144ULL, 0x1D8C2B19C5BFFC35ULL, 0xC0C953445E4A1999ULL, 
            0x2368EAD2ADED47B1ULL, 0x9A0068DB600827B7ULL, 0xB028F3C86A492A0AULL, 0xB83E01E228B22FFFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseCConstants = {
    0x16FFBE64817545D2ULL,
    0xFEF91F911FEA15F2ULL,
    0xB9AB092DAD57DDACULL,
    0x16FFBE64817545D2ULL,
    0xFEF91F911FEA15F2ULL,
    0xB9AB092DAD57DDACULL,
    0xBFB0CFC3EDFD44EEULL,
    0xC41F98EFDF1F38DAULL,
    0x9D,
    0xF4,
    0x50,
    0xA0,
    0x5E,
    0x41,
    0x85,
    0xAB
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseDSalts = {
    {
        {
            0x52B4C5D728175A32ULL, 0x2561E76D163515FEULL, 0x22ADDAF49818CEDEULL, 0x5B4A1F831A003D28ULL, 
            0xCFFEEEF164A7D221ULL, 0x3DCBDE7789F83442ULL, 0xFDE2E0D2DB5B398CULL, 0x5D6215ED2E4A5B4DULL, 
            0x301ADB8475E1C294ULL, 0xF1B2E5BD137E7399ULL, 0x136920BA77924D7FULL, 0x26C30A7625B08114ULL, 
            0x198FED97C33CC160ULL, 0x9AC69739561670E9ULL, 0x8B981E3E623779BFULL, 0x3F7C72527E0DD53BULL, 
            0x581E5694650E1D90ULL, 0xBF583058CE4BA1BFULL, 0x75B39A604EC1485FULL, 0x813B4F8F6110507FULL, 
            0xB7772D81A9A38273ULL, 0xE1BFF2C2F8C9899FULL, 0x161A3BC96D727EF0ULL, 0x85312C9C815BAAD0ULL, 
            0xC919D4CCAD19BA20ULL, 0x567778FB661BC04FULL, 0x5BD15DBE5D256C9BULL, 0x5AC2B1203B944C15ULL, 
            0xD5DEA4CBE713EFC9ULL, 0xFA9179A5706148A1ULL, 0xF2AEB28100A1E408ULL, 0x047F7FF8B6082DD4ULL
        },
        {
            0x7336D041D5621B68ULL, 0xE6531FEA95D424E0ULL, 0x87C74F671C509675ULL, 0x861F07EE19FED6BAULL, 
            0x70C585EA125A9D8BULL, 0xB75C9869105D9FEFULL, 0xEA16001B2BFFE36EULL, 0x262E8CD8860B4FAFULL, 
            0xAB3703B4C18F4C32ULL, 0x814ABF0CAA71C3E9ULL, 0x09448D841F70F2B4ULL, 0xB35C847C3844AC2CULL, 
            0x6BB34A04E9DE2299ULL, 0x3214D950AE1220CAULL, 0x75FEEB869C9E37C6ULL, 0x9EBA4A22749CC2A1ULL, 
            0x2D065400F255E08FULL, 0x7EF4BAEB0EB1BCFCULL, 0x83DE5D096E2C530FULL, 0x21E0C9006E43A3D7ULL, 
            0x1091F73AD3EB9503ULL, 0x4D862B0DEE54969AULL, 0x226536713BD07DBDULL, 0xB9593F30D1402CFCULL, 
            0xEB9EC32B7BAB23B6ULL, 0x7F2C92A5437F85DBULL, 0x22627C25077E0791ULL, 0x83F5B61CA2146B59ULL, 
            0x4C65C4CCB7156F10ULL, 0xB0977B48E30D82CEULL, 0x210FCA96898250EEULL, 0x249BADB3D510A7C1ULL
        },
        {
            0x68F0AA9F80397AABULL, 0x5FD57BF5B4357C3FULL, 0x81F3D250BF8D2641ULL, 0xB469B87BC547EF44ULL, 
            0x9FF65219B5AC072CULL, 0x27A64AEDDA45AEDAULL, 0xF7D592E27791A65BULL, 0x8712755F627F8419ULL, 
            0x5A4409ECD0CD1862ULL, 0x930DB9168DB1692CULL, 0x97D61140A30AB4F5ULL, 0xA919BDEE97ECEEBFULL, 
            0x64C6A39C662591D3ULL, 0x32123233A38DF3C6ULL, 0xC6AF94129B74212BULL, 0xFC4C10A8C5C786C1ULL, 
            0xF780E3F9E4264D26ULL, 0x3C7B66AF6A32812AULL, 0xEC6519C759381CC2ULL, 0xDACD2C80F30BB051ULL, 
            0x4C8458439ACC0698ULL, 0x5132ABC5DB585CABULL, 0xEEAF8B900D5A6C1FULL, 0xBF228CB64F75103EULL, 
            0x9FC0356B48DAE881ULL, 0x1E2D90D79528EF7CULL, 0xCB791C9AAE91AC60ULL, 0x608DA8C9618CB3A6ULL, 
            0x257E2A6547A8F2DEULL, 0xD341092F0284794CULL, 0xA86C72BC5073CB7CULL, 0x02BF10F22824FEC6ULL
        },
        {
            0x52E71D3C2C611E79ULL, 0xF48BB2FF8778CD40ULL, 0x632F478B1501C42BULL, 0x4589B0D474C704D7ULL, 
            0x244698EA0EA8D9B0ULL, 0x7F01D50307A083BFULL, 0x783807E6A11005DFULL, 0xA203CC6B54D3183BULL, 
            0x29C261A0F395BD3DULL, 0xE708B703246B600AULL, 0xEF2EC800FB2CD324ULL, 0x0E4FB6875ACCBBCEULL, 
            0xCC253775EB8B089EULL, 0x20401BD5F5FA15FAULL, 0xC83ED2B1395248A7ULL, 0xC583B266FCFB08F3ULL, 
            0x0A5B6D6B1F0069D0ULL, 0x475AF5DC60956676ULL, 0x6A4F556CE8F8F318ULL, 0x1B80D8CCD167D482ULL, 
            0x7D4810193D2F0D09ULL, 0xF35355C7E6950281ULL, 0x7B8BCD37FDB48859ULL, 0x053DCD2354336D28ULL, 
            0xDE9468B2041694B8ULL, 0x4817AD215B87F78BULL, 0x6278EF988AA31E7EULL, 0x168490FCF32DA869ULL, 
            0x14C0752D9978B56BULL, 0x36A071F818443BF3ULL, 0x1943CA8B253283ADULL, 0xAEF47EDB39FF6D81ULL
        },
        {
            0x4C147106BF83CA62ULL, 0x12824C6D017218E7ULL, 0x347100A4D1A575DCULL, 0x821E56B4C9938EB2ULL, 
            0xF89D842BFD68424EULL, 0x87D5EAD4C29FD56DULL, 0x3E4488D139A59D02ULL, 0xCE26C8032F02D20FULL, 
            0x06B86FFC48EDB7CDULL, 0xBFF237181EEC0E07ULL, 0x5599E9C6ED7F86E9ULL, 0xCF6F800534AD667BULL, 
            0x1BC7BC70325117DDULL, 0x74FC48E42CAD5D19ULL, 0x772666B5B3E17B68ULL, 0x9BB0DC56BD271541ULL, 
            0x8DE4AA5FA20A86ACULL, 0xE7EA162B163CD558ULL, 0x1CA98FD58877E2A5ULL, 0x5D276DB7BE87D9F9ULL, 
            0x833E7F336F47BCA3ULL, 0x45F14065C4D49D01ULL, 0x2D158EC100139845ULL, 0x67A6E87583D18BDFULL, 
            0x866B93B46544C600ULL, 0xB80259D3F466A0EEULL, 0x26798FA4F042BACAULL, 0x4D30089197499EE7ULL, 
            0x06D0B944DE64D166ULL, 0x253A1AF854AFABC0ULL, 0x9C9B8F9B20853FE6ULL, 0x37AB4D1EEB1C13BEULL
        },
        {
            0x3AB093EA475A77E5ULL, 0x9A0BCB22D156B316ULL, 0x4670C2DDD2587749ULL, 0x7582D2C19CFA90ADULL, 
            0x0A9447C0103E528AULL, 0x3E30C63CF97271BFULL, 0x6997FC648A96E43DULL, 0xF734926C8D95CF01ULL, 
            0xB8EE0CEA88C3165AULL, 0xF540FE6B594330E3ULL, 0x766BCED41F71C571ULL, 0x4CF3BDC0F4AEAD06ULL, 
            0xFE7C79118E1983F5ULL, 0x204457E9E6603898ULL, 0x1922859F3FA93C43ULL, 0x783662092ECC90A1ULL, 
            0xAC2E0272F694BB03ULL, 0xA8964B4DA72B92ECULL, 0x0ECCF24E5D61AB08ULL, 0x5FABBAC11CB866DBULL, 
            0xF9EA34622732B7BCULL, 0x03708F8FA4EABE7FULL, 0xE8A8D0ECBBA4A206ULL, 0x65B91889748AF289ULL, 
            0xCF2E8D3FE98203F0ULL, 0x709D86AF0C8D6DBEULL, 0x84DC0A05877194FEULL, 0xEC888E40C73B2D87ULL, 
            0x0126C04FC5D9D768ULL, 0x0D4407CBB613608DULL, 0x3A6AC25669CF88A8ULL, 0xD1AA11378DDDA371ULL
        }
    },
    {
        {
            0x2D0D7D5C26354C4FULL, 0xBCAC59BD2A683409ULL, 0x9308DF56887B2148ULL, 0x76A436925F57EC82ULL, 
            0x22A86E9CBED1F01BULL, 0x5B42F5FBDAF4C47CULL, 0x572D339219E819CCULL, 0x6970EE7F5E127350ULL, 
            0x1286B4304E4197ADULL, 0x7A86EA75F470AB52ULL, 0x48C770DBDA4850AFULL, 0x790523772FBAF41BULL, 
            0xCEA90A99A81D95B5ULL, 0xBA28D1F5E13ACC6BULL, 0xBD62F9C1E6E19ECFULL, 0x246FB2BC821F348BULL, 
            0x84C69496CE4B1D0CULL, 0x92C594A809590AE9ULL, 0xD82FED2F42AC2E84ULL, 0x1298CC6C1D7DB0BFULL, 
            0x39BDFFD5C2CCB460ULL, 0x06A2424EDEAB4DABULL, 0x83567470CA7E579AULL, 0x122E4271D8E4E08AULL, 
            0x0CFE56CD3129E849ULL, 0xB04E3E8044BEEED3ULL, 0x80406C640EA67659ULL, 0x6788819B28832F2EULL, 
            0xAC60EC7EC6D8F5D4ULL, 0xA10FAFFA169F2CEAULL, 0x885CEA7BC8AFF452ULL, 0x21D08D9FE68E22BEULL
        },
        {
            0x2DF2B21E0AAF3A57ULL, 0x6FAF0EFAFD35A79FULL, 0x5C389F4A0F4F9F9DULL, 0xFEF672CEF2054A9CULL, 
            0x63EDE27B54EB2FF2ULL, 0xFDA3138DD53CC1D2ULL, 0xDFD0193451CDB746ULL, 0xC04679BC94D88130ULL, 
            0xFBE317ACE0A65C1BULL, 0x79D037CC1C62062EULL, 0xDA5F773EB264F09DULL, 0x1C62ADFAB009654BULL, 
            0x9D649893A21162E6ULL, 0x0A5CC2463E333A48ULL, 0x2B4445FE8E9A6221ULL, 0x98C530A71EB587BCULL, 
            0xFF345D68131A9CDFULL, 0xBA6F33E59AFAAA33ULL, 0x5A4AC778169F0379ULL, 0xFB176CBD2BBECFB0ULL, 
            0xC55CD2CC47689F86ULL, 0x28095897A7E010A0ULL, 0x7DB5011391CCD8C5ULL, 0x8A462636096BC0B8ULL, 
            0x4300C09950AA3626ULL, 0xFCFA0198D979B0AAULL, 0x10E7FC0B4CB0F87DULL, 0xBC98441BD0B1C6E8ULL, 
            0xB9A16657E537375FULL, 0x65A45105B1059F69ULL, 0xA2881EB8A46B4C18ULL, 0xFF4EDC8004875689ULL
        },
        {
            0x5062AF13AA86A620ULL, 0xE48FBAA3CDBB48F5ULL, 0x5D566BE0B8E65C8DULL, 0x39E04B0EE927FA17ULL, 
            0x94E23A8C7218AAD7ULL, 0x0BBE9AA0F23E5F18ULL, 0xB5B58F7ED33B4975ULL, 0x592F82B783099635ULL, 
            0x4EB22CBC1E5FCDE2ULL, 0x5A29677BEFB752DEULL, 0xB550EA1155ADA58BULL, 0xF0F35E81C82702CAULL, 
            0x5B1B0BB30E179C18ULL, 0x2D43F3531E082567ULL, 0x3769E1D5927109DDULL, 0xC0DCF499B3664785ULL, 
            0x764853639D8F1C7BULL, 0x3B6C1D16D3C060A7ULL, 0xBC82C0A27A5B17BFULL, 0xCC913DED453FEBC5ULL, 
            0x4ED1F1AD994A4663ULL, 0x82BC6A7E64DFE021ULL, 0x231FBD6695E81C9EULL, 0x9E8123228ABFAE96ULL, 
            0x32EE0835504F34F9ULL, 0xDDD15B1E247C88E9ULL, 0xE0E75D1A66803537ULL, 0x24685110E3A7E7D7ULL, 
            0x68899A2C51F210ADULL, 0xC4E32BC36D455DEFULL, 0x76300583C2B2CA4EULL, 0x669F09AE964AF0BBULL
        },
        {
            0xC11E56E664B8A715ULL, 0x47393AD1E6DBBE64ULL, 0x2751595EFAA72730ULL, 0x65519D45A72F42BBULL, 
            0xD7C4CA4C0DEEF8E1ULL, 0x354C7195F6C7FDC8ULL, 0xABF8888130036BE2ULL, 0xFF135EDD042DFE6FULL, 
            0x1C85A29066F0A0B9ULL, 0x092857CAD32D963BULL, 0xFF47C926FF3E9D1BULL, 0xC1F4E5DDCBF1895AULL, 
            0x33766E82D7C2D28BULL, 0x5F6C8DC13E1F01A8ULL, 0xC37137CAE12779BDULL, 0x32FDAF322505912AULL, 
            0x86E389EA6E61C5F4ULL, 0x6A6175C6DFE30DD7ULL, 0x1A21525FD1C736F6ULL, 0x61062884B8C6081AULL, 
            0x7F5A25355AD73C49ULL, 0x56C47D2DF79D4054ULL, 0x2D77FBD59B0626F8ULL, 0xE2B38076F18E797EULL, 
            0x7C3BF6444CF641D1ULL, 0x11B40E0661FB3613ULL, 0x0A7ED784ADCFE627ULL, 0x9E6FF5DD111C6591ULL, 
            0x63A814FC3DB9ABCDULL, 0xA1B1898CBE972583ULL, 0xF000F8D37BBF8A08ULL, 0x8351149FA90145C1ULL
        },
        {
            0x2D7A1C37961E1358ULL, 0xEFD4580327BAEBD8ULL, 0xF0D0E7EA3DBE9202ULL, 0x56019DBE3235010FULL, 
            0xF4D2B5DE40546C33ULL, 0xFE61FEE889005FA3ULL, 0x6B70BBC3DE9A3CB0ULL, 0x515204F2F604ABF1ULL, 
            0xEC77EC52923A7BBEULL, 0xE45D9B8512BC4413ULL, 0x1A68EE6C0121ED62ULL, 0xEFBEC09D183404B4ULL, 
            0x82F317C0ECA93564ULL, 0x483120B6FA4204CEULL, 0xCA00CACFEC5AEA69ULL, 0x09D5A740A8B6DFA4ULL, 
            0x4FD4F2B72F6E95A6ULL, 0x0F45270400833CE0ULL, 0xD39A036C4AC8C3A5ULL, 0x86A6DB0456C4C3BBULL, 
            0x0D751E2B31012776ULL, 0xF5C4B97C03B3D787ULL, 0x53C8596510D44CE1ULL, 0xA8757917E0F8084CULL, 
            0xFB0246A2674B09C7ULL, 0x96A40E9D67AA81D9ULL, 0x8CF9CAD79E71C3C8ULL, 0x094EDBBE9414E8C1ULL, 
            0xA80F4A771D3BDE90ULL, 0x586772D5AE5B161BULL, 0x4BA8AA32643F880EULL, 0xBEE1348C511F4143ULL
        },
        {
            0x646433C36E23C0BFULL, 0x389FE6A5462B1BCCULL, 0x2493497D99A5C9BEULL, 0x2D2FF006223A37C7ULL, 
            0x4CC991077318B84BULL, 0xAC1C5C5E996B4101ULL, 0xC0413C6125DA0EEEULL, 0xFD9CB481BD3284D5ULL, 
            0x152E3EC431EAB9A4ULL, 0xF7AE06783152502CULL, 0x7D29A88D1B3175B6ULL, 0x34AF2645475D3F26ULL, 
            0xB393090C44AE2315ULL, 0x5C5EA20C4E3CA345ULL, 0x4687803E5186E17CULL, 0x7B4D55E2B0006B44ULL, 
            0x914BEF7B16E32376ULL, 0xF2B91A1E8C511D3DULL, 0xAE535DF69F667085ULL, 0xA078228FBA0C7950ULL, 
            0x7CF136C682943B0AULL, 0xBAC493CC6B41CCE8ULL, 0x044C45237E323A7DULL, 0x230ED10D9D311711ULL, 
            0xCF65065BE7999C09ULL, 0x35A9430FA3F1448BULL, 0x2D4249DE619A5EB7ULL, 0x988617C9FAE5D01AULL, 
            0xFA086C2EF758C15DULL, 0x32AEA278764216E1ULL, 0xE7ACD2E2193D2968ULL, 0x079892FFC4366A7BULL
        }
    },
    {
        {
            0x9933657286F9FAEAULL, 0x62DF693E1DC505FDULL, 0x519992BC53C53660ULL, 0xE4E0F161C2D43E11ULL, 
            0xE800709FEAE56EB8ULL, 0x4E3913F7BEE836F5ULL, 0xE10687814B64BB72ULL, 0x589A6A4757D884B3ULL, 
            0x409C788B6A0CEF45ULL, 0x4E1D440CAC0C9FBBULL, 0xA71AA2D09705A6A9ULL, 0x80B4017FF4383E85ULL, 
            0xBC02B4CBC209CAC8ULL, 0x565DAF525639BAF6ULL, 0xCAC3080CB2377B5BULL, 0x89CFAB755FDBAAA3ULL, 
            0x8EE09576EAD29C53ULL, 0x77D3411CDE2DB125ULL, 0xBEFABEA9E0E87EA5ULL, 0x6010947E51DC9C93ULL, 
            0x8AD7BABD54786002ULL, 0x16C8B27794E9C41DULL, 0xCBBFD2C10D38F5F2ULL, 0x7CD82D9118A1E3C9ULL, 
            0xE217AA4279895E14ULL, 0x7545C79BD6C130B2ULL, 0xD7A0A37EEF7F1C5EULL, 0xE47931A1E14C3781ULL, 
            0x8D260566E4C7E946ULL, 0xED756BC11D47A222ULL, 0xF5B4DF22F022F3D3ULL, 0x9A13C7F3502D9956ULL
        },
        {
            0xC428BF9A3DCE92DFULL, 0x39C6A6899CEC3DFEULL, 0x3AD881EF44996570ULL, 0x63DD90FA4DCB681DULL, 
            0x12E85FD17B816876ULL, 0xFF1DD1FB806C42B4ULL, 0x6ACE58BCDCD107CAULL, 0x3D19C29388660B14ULL, 
            0xB413FE5E0AE6732EULL, 0x9042C6DC3DA4D932ULL, 0x9738E1B60C2FD236ULL, 0x41FD948F2AB4B3F4ULL, 
            0xF0DBC72A3F30B1CAULL, 0x515D2A506391DBCAULL, 0xFBD9B1E90E398A04ULL, 0xCBB74AF6FDC444A5ULL, 
            0xA762ACC919AA0E7AULL, 0x27008FAFF0A151BEULL, 0x596713D92EDF3394ULL, 0x35E1E37DA2B7A93CULL, 
            0x1D6EF4FB809CCAC0ULL, 0xE364F61A56F3DF16ULL, 0xDC4273CD78C616C5ULL, 0xDE7DF99B2590F88BULL, 
            0x4E84D4D316C9FC94ULL, 0x098E237C0F8191C4ULL, 0x4F554DD1405E4982ULL, 0xA74D3893B4B06576ULL, 
            0x3F03AA02FB506254ULL, 0xD2424BE121858BD2ULL, 0x2B370013D74957FDULL, 0x627CAE81D10EB22CULL
        },
        {
            0x86F16CF977AF8F71ULL, 0xC950EF03F9921BA8ULL, 0xF3E47C59ED82FECBULL, 0xE5AEE30AF5417985ULL, 
            0xFC0D85B03E947984ULL, 0x8FF6CB4EDC926F4CULL, 0x9EC09D650B2A53EFULL, 0xD0E647CA1C12AE23ULL, 
            0x6C7EC978ED51C781ULL, 0x646DF26B313284E2ULL, 0xFB8493A89019CDAAULL, 0xDD927DA28FF7BBE6ULL, 
            0xB476A9C98B92A994ULL, 0x4711360D8DE871FEULL, 0x80C74378511A76FCULL, 0x136ABD250AD4E3C7ULL, 
            0x735666446EC176DBULL, 0xC92371DF54D5A2DCULL, 0x931DEBD23B1D6098ULL, 0x804A8836107C9FA7ULL, 
            0x1EA347928882E19AULL, 0xBD918108AA3D59D8ULL, 0x0813183344CBE2E0ULL, 0x827887625C43D59EULL, 
            0x76154CBFB80F32A2ULL, 0x699FA7A88DB78D6EULL, 0x3BA0199305FDD8C8ULL, 0xAEAEEBCB68163386ULL, 
            0x30DBF2FDA566833CULL, 0xD6B330A810CF9075ULL, 0xA3E0D6A88FD06A2BULL, 0x6A9D0E15D57D9318ULL
        },
        {
            0x3284F0591C6E1673ULL, 0xF4BF489E68E26482ULL, 0x5B7C3CF8640C9540ULL, 0x9DE7096A818B20EFULL, 
            0x374C57D6BB138F11ULL, 0x009E366D1C816F84ULL, 0xDEB47DF9094E10D6ULL, 0x5F9C2954D59F668BULL, 
            0x720375AA9E6E58CFULL, 0xFAEAC4484A7E0E1AULL, 0x30D471B28383A697ULL, 0x0A5E0ED4F3F401D3ULL, 
            0xB8924E173A6FCF54ULL, 0xCFD3F2650058BB5BULL, 0xEF095CA61A232BC0ULL, 0x0C303097B2206E63ULL, 
            0xB81C232B79EEBEEEULL, 0xCD35236E76345649ULL, 0x45D1ED8C27E87798ULL, 0x2DF2B24D92390D0EULL, 
            0xB0FB6E9DA1C57E97ULL, 0x89450A6E0CCC463CULL, 0x0800039ECCBC2084ULL, 0x95088ADEC8EACB4EULL, 
            0xFEF29D8AEB460E8AULL, 0x243E0A6A28397453ULL, 0xB475A1C536AD9A84ULL, 0xDC08FA9D33C92ED3ULL, 
            0xB56237762D32D652ULL, 0x2C4D3121283AA4ADULL, 0xE5E80F8FC5B74F06ULL, 0x63CDDFFA0FE4DC86ULL
        },
        {
            0x2993055BB41C7090ULL, 0xE836B93026EDD9F4ULL, 0x7A410E8CDD61B18CULL, 0x6EB019B46171D928ULL, 
            0x97D094AD8F381010ULL, 0xC0208E9F600F9E0EULL, 0x35716EBF2B7A7AC1ULL, 0x1F9BEC96138D38AAULL, 
            0x2349B719F76FF8A4ULL, 0xEE5995C445D3DE67ULL, 0x453C79A8CF983D8EULL, 0x550671DF2C26F5B7ULL, 
            0x21AAA2CD90B75609ULL, 0x535548EC2D58DA49ULL, 0xF0B6B2F2CA2A8822ULL, 0x91B3E12A67F6DD4BULL, 
            0x15B690DDA8426B09ULL, 0xD46A2F86284AC33FULL, 0xED292493CC384BA7ULL, 0xA4C8F98E44086732ULL, 
            0xF64EB910100C749BULL, 0x62A569332E6E51E2ULL, 0x32639F7CA0939B91ULL, 0x9A9C2B46481EF389ULL, 
            0xEF5AF82485D84F8BULL, 0x3182C7FDBFA8205BULL, 0x3CC107551434468DULL, 0xC6212A66C916E28BULL, 
            0x39C048A604A0D487ULL, 0xDC9C1CC9F26F9339ULL, 0xEFCF884B8B2A87B3ULL, 0x9C92909684F7B9ABULL
        },
        {
            0xC1893AEDC997B51DULL, 0x9AB84C1632B37179ULL, 0x68209255A3027C2AULL, 0xE242C0418DB52ABBULL, 
            0x649C8E1EF5EDBAB4ULL, 0xD6019AC470F86516ULL, 0xF24CABFEEEF5A461ULL, 0x7F127021BC595424ULL, 
            0xB1E7BBF8200D0BE7ULL, 0xBF480E9A482D8711ULL, 0x69318750BBD7A080ULL, 0xBEC03929818CFC99ULL, 
            0x4C5E3EEBF4E5750CULL, 0x9E82A314BA4376B4ULL, 0xCFA0F000526676BBULL, 0xF21D60D9D18121ECULL, 
            0x9E8C8C3E78A84508ULL, 0x58D030A374E7B6C7ULL, 0xD0031539B3722C4EULL, 0x3B2748CBE4CCFE33ULL, 
            0xCBB83A7B4BC42930ULL, 0x484C22DF7551EA01ULL, 0xCBF51CC3FD4B140CULL, 0xE7D013864BC14B74ULL, 
            0x7ABA978D04B028E8ULL, 0xD36FDDED218CCB51ULL, 0x477E1288076D6588ULL, 0x4186E06A723D8042ULL, 
            0x904A2B4370B3D835ULL, 0x45918A8E6BE3276EULL, 0xE496B43EF8588AE7ULL, 0xFD2E69662A1C512FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseDConstants = {
    0x4291930C8AF6425BULL,
    0x0B218412CAFB486FULL,
    0xC2217344679A11F3ULL,
    0x4291930C8AF6425BULL,
    0x0B218412CAFB486FULL,
    0xC2217344679A11F3ULL,
    0xD032A0F5983ABCE8ULL,
    0x43C389576BEACB5FULL,
    0x9A,
    0x71,
    0x2D,
    0xE8,
    0x9A,
    0x69,
    0xBE,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseESalts = {
    {
        {
            0x6E13BD7AD77F655AULL, 0xFE570E44C5CDFA52ULL, 0x5D90989EA079EE85ULL, 0x71B542846AF694FFULL, 
            0x1EBBDEF817FF1D9BULL, 0x49EC48D8E3E8E92CULL, 0xEBD6335BD5E7C4BFULL, 0x42327A17A6AD8D3FULL, 
            0xFCAD7D29970E6C9AULL, 0x355FD53593E400A3ULL, 0x6140BD155D2E8932ULL, 0xCC5001C4127C9AE3ULL, 
            0x5C6031E47995A73FULL, 0xDD8BAC3F63FA117BULL, 0x5604765A53165296ULL, 0xF567382928CFB0F9ULL, 
            0xFE0AE25D47E18F98ULL, 0x67FD7BDF615D19A0ULL, 0x3D941580536C43CCULL, 0x647AB5C7F32D977DULL, 
            0xAF13B8851B5DF16FULL, 0x70A5164AE77F1DC2ULL, 0x44CDF7F0CAB0F3BCULL, 0x1C5995F8A05B90A5ULL, 
            0x8EE43C92B884B50EULL, 0xE68B859F8D0444DBULL, 0x1E6BC0D7CE447746ULL, 0x95C9346F7237BF84ULL, 
            0x08D1E7317F5F5818ULL, 0xC9479888417AFF5DULL, 0x3735A33277566431ULL, 0xC0F0A113D5478170ULL
        },
        {
            0x95BB65AB698F0ACAULL, 0xC1F7C5B52CF46AA8ULL, 0xC375950751D42F74ULL, 0xBF0C78A67FCAE1D8ULL, 
            0xA3E809354E9289B4ULL, 0x5A3DDDE4ADFBCED8ULL, 0x1E3C44B14115F1A0ULL, 0x5FF84879C1440362ULL, 
            0x0CD66C449845E41EULL, 0x50CE5964FEA07229ULL, 0x280275E3C70E7BBCULL, 0x79A9D9793465087EULL, 
            0x945F5E64994CA977ULL, 0x82ACDD3F856204A9ULL, 0xAA607D6D37AF7257ULL, 0x9AFE0B8A6B87AE51ULL, 
            0xBCDF6560288BF5FAULL, 0xBAFD27818D4E3259ULL, 0x11B62BA75E0FF9B6ULL, 0x3F01D4F727DC0108ULL, 
            0x976BA6DB5411C221ULL, 0x59FC6C65A55D9E52ULL, 0x7329B2476DF71101ULL, 0x008BF7D2E3508F5FULL, 
            0xDDAB23C4AD4BD2BEULL, 0x0B752C5D8895D970ULL, 0x3D55B38E55D55870ULL, 0x280102635AF943A1ULL, 
            0x218E62362DCB2598ULL, 0x24FF648A2A699255ULL, 0xEC2318EFB57DE9A1ULL, 0x59F94D1F4E7CB7A1ULL
        },
        {
            0x6C63019B37FA1856ULL, 0x75020B7B037DBFA1ULL, 0x4C2F78FFB7A91BB8ULL, 0x424F15F4430BCAD0ULL, 
            0x578D02D336817563ULL, 0x030474A11517C00DULL, 0xF02C57522E9F3642ULL, 0xF42BC4D7B62F9A04ULL, 
            0x0DA44588D56D83D0ULL, 0x106AC46C57DC6A3BULL, 0x6D1FD739D05989CDULL, 0xBC6E4D9B71C114DEULL, 
            0xD6CC07A51DA7485AULL, 0xF6F6FFD400041C92ULL, 0x22EC59C56F0CD526ULL, 0x6457614550D12EF4ULL, 
            0x966294BC3F9E73A6ULL, 0xC15CF8432C428E77ULL, 0xE8D8A5A5225D22A1ULL, 0xFBDB207BAD6C6711ULL, 
            0x081899AB0484D4D7ULL, 0xF6965DE63F60CBEDULL, 0xECBC2626410DFB9FULL, 0xCA9B9B13BD81CF0DULL, 
            0xDF483FFEB39927C5ULL, 0xDE7F40C103405221ULL, 0x01BA05CB21BB8F57ULL, 0xBC62681894142EB3ULL, 
            0xEFB0A0E3B927A701ULL, 0x5A32175994AF7391ULL, 0xB13CD9E403B2E62AULL, 0x0F777CCA02DF53B2ULL
        },
        {
            0x90045295E20FA9E1ULL, 0xF4B241B92BEBAB5DULL, 0xE52A04454335FC10ULL, 0x29816DBD9DCC1B02ULL, 
            0x89523678164C9ED6ULL, 0x6270FFB7529B5221ULL, 0x556C8185E908FF20ULL, 0xAD05AF3CAEA3DD81ULL, 
            0xCC8CF76954D7FCCAULL, 0xD411A15CD163FAA0ULL, 0x13429702B7949CC0ULL, 0x5C691F7549655856ULL, 
            0x137556C6B222F075ULL, 0x1F226BF7DE7CE968ULL, 0x4CC81CF3EA5120C3ULL, 0xF7A3C967DE11D32AULL, 
            0x27D9E252E941A11BULL, 0xDE2C5EA07C091B79ULL, 0x67C3A0367DFC9528ULL, 0x04295BD50F447534ULL, 
            0x1E22E754A6FDB64CULL, 0x65400871362C74F7ULL, 0x966F1038DE62301CULL, 0xAD4C0D9DA9F64F98ULL, 
            0x90BAB2353B4BBD0EULL, 0x13DBFF00A5BF9CFFULL, 0x78296BA9B4BC048BULL, 0xD95FF71C2288F418ULL, 
            0xE4518BE113932148ULL, 0x10F436126C015181ULL, 0xD028989E16ECB658ULL, 0x9C732C6C3F1D787FULL
        },
        {
            0x7172673FFB70FAABULL, 0xB192AA91715469B4ULL, 0x8E0C4C093C2A5CA3ULL, 0x0AF0447DAB4549D2ULL, 
            0x4F8FA804FDEEF2C0ULL, 0x4CFB5D04972D57A1ULL, 0x42A84AD26150FF22ULL, 0xA3BC43E7EEBC92BBULL, 
            0x8BEA0165771DBDC1ULL, 0xA8820C6CB3826B67ULL, 0x24F65502A9D0C534ULL, 0x2B7E0709BC8FB5C8ULL, 
            0x40E2EAF5A674850DULL, 0x36A45547132E3642ULL, 0x8C5526A1BF543BB4ULL, 0x3E783DAC5FF57F77ULL, 
            0xD6709DB8AC58E508ULL, 0xB569FCF2F838C6A0ULL, 0x005A13D61B87AF28ULL, 0x2651E2DB336D8CA3ULL, 
            0x164176B8455C9934ULL, 0x406074C0DEFDB5ADULL, 0xC81BA38BB6E17FC8ULL, 0xE1C5DC28F370882BULL, 
            0xF6035A57E706ADC4ULL, 0x3D040D6508266685ULL, 0xC72560C4AAE7B135ULL, 0x09FB4CEE27407743ULL, 
            0x079C66CFAB9D0C5BULL, 0x849A1C2E8BCA487DULL, 0x0287146B0D4B0CC9ULL, 0xA2C71C94112AC57AULL
        },
        {
            0xF353135B4559E385ULL, 0xCCBBBD1E1F676EABULL, 0x857E17C70CE70C52ULL, 0xDD6C679C0CFDB3EFULL, 
            0x55EC897CA116D6A5ULL, 0x183BF8822C64B87DULL, 0x54F3246ED83E6C23ULL, 0xA2C2C26840940AC7ULL, 
            0x6117276090521B7CULL, 0xBB7F3B32F3691C49ULL, 0x8F20962C1BAEA485ULL, 0xBEFBFE381CE2EB9FULL, 
            0xFBE1155E71756E12ULL, 0x84361EDB324F98F6ULL, 0xA36391DBF48DBC91ULL, 0x4846677791F2DAF2ULL, 
            0x4B001A9A477F67A8ULL, 0x97DE54BC62FE94A4ULL, 0xCAB0782009DAB2DCULL, 0x771236D2B1B606ADULL, 
            0xA31CDC1E3E0C0FE9ULL, 0x480185D388D95A26ULL, 0x383068CC751824F9ULL, 0x9EC1A38D9E8EE94BULL, 
            0x5DBE4052B392E827ULL, 0xB3FEF6A480B8616AULL, 0x77FCC5367FFA1D42ULL, 0x72A660C0D49CC898ULL, 
            0x84A08296A66373E2ULL, 0xBF6DBE18E70E3F3FULL, 0xC85F5EC3AD8AC2A0ULL, 0x2C65E09E980450B7ULL
        }
    },
    {
        {
            0x198E16CA0379E4BFULL, 0x63E050FE9662CFA5ULL, 0x0812F9CB235AA80BULL, 0xD1E61B23652A3362ULL, 
            0xD55E702993152195ULL, 0x9454F4D3CB4661CAULL, 0x470FCDDC2946641CULL, 0xE328316D758D6A1FULL, 
            0xB9C0AFCBED375438ULL, 0x5FE02064C0D362F0ULL, 0xE4A205E6CCBC4D8FULL, 0x4D6CF1529CFBDB7EULL, 
            0x71E4A1CE7F7E0114ULL, 0x8EDD9EA63B1797BDULL, 0x711532D099095506ULL, 0x1B7C2938D44C6297ULL, 
            0x357AC6647906E19DULL, 0x2665A58A69FA9160ULL, 0xC78001899751A04FULL, 0x1132FA91DC8017A3ULL, 
            0x088E7C46E7B3AF26ULL, 0xA49077B0FCFCD2AEULL, 0xFB3F7582D825D240ULL, 0x288E6744687C07E3ULL, 
            0x7B673C670753D0D2ULL, 0x93A8343AFCFF0AB8ULL, 0x2184F0BA4DE0AD39ULL, 0x255584B4030BE0C0ULL, 
            0xFFB4CB9B432CD51DULL, 0x9F57F3792C622F19ULL, 0x11E785CA9EA4EA86ULL, 0x2DF65562FAD0F8A4ULL
        },
        {
            0x25BAA2845217C9CBULL, 0x99D7E372D77F317EULL, 0x89CC57B545E73013ULL, 0xA63E7CD6B7389DCBULL, 
            0xD85B9B5995E7F941ULL, 0xB2A7611C7619A2D7ULL, 0x3EAB09A4A31CD3E6ULL, 0xCAA69365E378DBC6ULL, 
            0xA8B3915E1A6AC0F3ULL, 0x335F48495F71F833ULL, 0x4541C23600CF4C48ULL, 0xBFA3784353A8B184ULL, 
            0xB55214392D5A930CULL, 0x0EA7DBE43D22F862ULL, 0xF441E65B296D22DFULL, 0x49ADEB75690C9A66ULL, 
            0xA4AE1C7D6B8310A1ULL, 0x8662D721719558D9ULL, 0xBE5E2820B7467DEEULL, 0xCDE4C29008F6F102ULL, 
            0xC123206B8BD52BEEULL, 0xD3DBA5A2B8947470ULL, 0xD00661B0CBB81439ULL, 0xA4BD4A842414B20DULL, 
            0x82450C3DA44E766EULL, 0xFE5C7F95B3B4F5ECULL, 0xC221459054967411ULL, 0x5FCA4F33C45D96E9ULL, 
            0x0BFBE724FEF4A14EULL, 0xE89B743802582A33ULL, 0x6A8EB55517F43E4AULL, 0x9DC613C8C72EADB2ULL
        },
        {
            0x2129C6E71369FF49ULL, 0xCD8F6FEFF49F086BULL, 0x1EE00107EC51CE72ULL, 0x42CDDF71E40BBB34ULL, 
            0xCCFAFA3031388D82ULL, 0x1391BA55A51A4104ULL, 0xC3C887C588D2F9CEULL, 0x61EE90DE7F618154ULL, 
            0xD1A3FD933C47F468ULL, 0x9E0DAA6CB5BE6010ULL, 0x257FF166345A1035ULL, 0x16E53D3057287886ULL, 
            0x35E7F710551D1F58ULL, 0x5C02970D170CEB16ULL, 0x1F2A69BF17EAFD3AULL, 0xB780902C6452DBFAULL, 
            0xF75AB1AE65555284ULL, 0x4797D4040CF29F7BULL, 0xDF8A7698B5B46A40ULL, 0x177325241AB645A7ULL, 
            0xA4DB7D78F5AC6D1EULL, 0xEC5A033D57086747ULL, 0xDFDBA8C2058CE7F6ULL, 0xA488F5D10E188DF0ULL, 
            0xEADBB8380102C2B0ULL, 0xA1285B39ACD99E09ULL, 0xA2E11BBB213E82F7ULL, 0x740BF3B59E0539F1ULL, 
            0x47B48FE3E1E01797ULL, 0x97871598C5B87220ULL, 0xA4BC199C7AE8B3D0ULL, 0xCAE563DA2665FF12ULL
        },
        {
            0x4ECE244B4238D590ULL, 0x8EE10ACEF6C6FCFFULL, 0xF2D8E24683F432E8ULL, 0x7655D49865AB556FULL, 
            0xFD2C35CAAD1DD253ULL, 0xD520508982767957ULL, 0x2A9B85DBAE6971C5ULL, 0x3D28480C2A46B037ULL, 
            0x1416190105CA44EFULL, 0x99A293143952D217ULL, 0x85BCD97DF688E563ULL, 0xDDB3F7250AC4DCFBULL, 
            0xC57AD9F0182273D9ULL, 0xD04A30CA3946AB8BULL, 0xE10BD44D406D4577ULL, 0x70FB6E7419713E04ULL, 
            0x147936808B65A748ULL, 0xF9C11DA4534130EBULL, 0x7214951048A3720BULL, 0xB663D7FD1B994FFFULL, 
            0xCBDDD08BA493B901ULL, 0xA9910AAF0AF5B236ULL, 0x7BEFCF4F5323BDF4ULL, 0x8A8065B58CD444CAULL, 
            0xBB48615BE87F8B26ULL, 0x5613F519017CFE00ULL, 0x5423DC3BCB9A43B6ULL, 0x5AD807AF5A6AD850ULL, 
            0xB2807E6E49AA8CB9ULL, 0x9FAA512B9CEE718DULL, 0x029D3BAB552141E9ULL, 0xB1B18C447D0F3E79ULL
        },
        {
            0x0930347FDF621B48ULL, 0x6FE725590F1E4E7BULL, 0xDC73F139AAECD969ULL, 0x68C34105AE830707ULL, 
            0x635467CE3EB60027ULL, 0xA2A8257F8310B2C8ULL, 0x740C9560BAB9EB35ULL, 0xE24325120AF5371BULL, 
            0xBB23258FF3413F49ULL, 0x2D2B47DF5C0FC58BULL, 0xF2689C667A3DC85AULL, 0xA27A424A47D60765ULL, 
            0x5CB043728753E39BULL, 0xBDB6012A2421A48DULL, 0x5B1F7B59C45921DFULL, 0xA0893DF4A1D6F961ULL, 
            0x1C1A00A718C375BFULL, 0xCE2785642592D670ULL, 0x0D8CDACB7EAE5B6EULL, 0x3FA0B56C445FDB58ULL, 
            0x0ECA4B5D8EDBC1E7ULL, 0x8F38B33006C81DA2ULL, 0xACB8738634CCB828ULL, 0x919B405AC6AC36DEULL, 
            0x8795E1379DD02E32ULL, 0xCC6E25223A80C2CAULL, 0x51B7FA84ED12BE5AULL, 0x4C75214FF49707D2ULL, 
            0x57CE0B42AD60F9FBULL, 0x06A84B96141BB68FULL, 0x69AB801362074FD7ULL, 0xCCDD260AC407D7B7ULL
        },
        {
            0x00757A9C642AC29DULL, 0xA120F6226C634A0BULL, 0xF6C0BD1DA5EA373FULL, 0xED9FFD1AC4EDCA0FULL, 
            0x82905912A6C9F41BULL, 0x1B1E2F8570B62FBCULL, 0x7285A35F11BB5D02ULL, 0x9201471E9F8848E7ULL, 
            0x31D0F5353550A2D2ULL, 0x15BAEB7549BB2382ULL, 0x1B8AEE9EF377B1E5ULL, 0xA39355C7DB404F54ULL, 
            0x6A081AA75819668AULL, 0xD88667A0CCC55A66ULL, 0x775B6B18E4174566ULL, 0xF05F886C845A1734ULL, 
            0x8EB99E41FB0B79C6ULL, 0xDF9C9E6BF0A99D7FULL, 0xB8AC12E65D5F33CAULL, 0x869551BF1C86F9EBULL, 
            0x55CFC257C272D7E0ULL, 0x6EC12D6F2AFEEBFFULL, 0xEADEB09C2A66C4B3ULL, 0x9F091704079B9593ULL, 
            0x3ECEDAD40C25426DULL, 0x66CCE585F3CDC2D1ULL, 0x721E0AD98A6F9440ULL, 0x3E26FC45F969694BULL, 
            0x9806ED5799E0099EULL, 0x72A62DC02286F463ULL, 0x0D776804A8156DAEULL, 0xC55ABA74A2E299CAULL
        }
    },
    {
        {
            0xCBE2DE0EE2F52E71ULL, 0x36E3FA66D2D4E5BCULL, 0x96155F313330FE78ULL, 0xC5B28822D7877CEDULL, 
            0x782663F917A558C4ULL, 0xD81C52D348BFEFBFULL, 0xD6BE20B14CEA183FULL, 0xA5B62BFF7514EDA7ULL, 
            0x799D981DFCDFB106ULL, 0xBD4007F9135F7DD3ULL, 0xF0C5AA41C8BCE907ULL, 0x9567308618A1B9ABULL, 
            0x65BE23E80E98F201ULL, 0x0E968CB5924EC57FULL, 0x9E2DC8021F4D1947ULL, 0xA27F60394A3C9EA3ULL, 
            0x16FE49B39F4B2A06ULL, 0x2A7D8107BF75635AULL, 0x7051812872D9B0EEULL, 0x8FE65705441DF1E5ULL, 
            0xD125B4A4EED02AA1ULL, 0x74C29E16AEEFA3E8ULL, 0x7EB286FB2DA9A7B9ULL, 0x8C6EA3C8F8C9534EULL, 
            0x344A8B3557D2CA21ULL, 0xE09B881FDD837996ULL, 0xE1263F2DCD8EB51BULL, 0x61E8085A90DC7929ULL, 
            0x6F72F7C563D77F4BULL, 0x3134EA39E451A54AULL, 0x209502462C204818ULL, 0x2F9852A3E4653586ULL
        },
        {
            0x047FAB091C590B7DULL, 0x661693206D630CB7ULL, 0x57E86D22977B690AULL, 0x8A79EEE08F47A54CULL, 
            0x9570E7B6334DEFB7ULL, 0x318521D9772D6F5FULL, 0x9F024FE6C9DCF9E7ULL, 0x4D6E0BD5815E8353ULL, 
            0x7014FB61BAED82E8ULL, 0x039388403D5816BBULL, 0x9292AA8F8FE5292BULL, 0x6D97C195AFD78A02ULL, 
            0x347671940FF984EBULL, 0xED6622170338876CULL, 0x5424446322C667AFULL, 0x1EE5DB4EA66ECAAAULL, 
            0x17B7DD6B46C605F9ULL, 0x354259F9D6AED1F6ULL, 0x43853830B74BEA5CULL, 0x213845F5AAD70028ULL, 
            0xE98FE8B43BB7B648ULL, 0x3399EB6DD3E019F3ULL, 0x9789C3FE5BE3D6C1ULL, 0x243F098E9C341E30ULL, 
            0xA12254210BE0B307ULL, 0x2A770D647358F26CULL, 0x328DF0645C78C854ULL, 0x66BF1D22021193F5ULL, 
            0x311F01F902DD68B6ULL, 0xB72A6899766E17EDULL, 0x1F7FC1D5C6BE50EAULL, 0x7B6023C9BCA83A42ULL
        },
        {
            0x42EAD638955D71E2ULL, 0xB20F0533F2F8534CULL, 0x28F5BFA25C77FF0DULL, 0x2DFF64C93E779D77ULL, 
            0xB9198FB3CE5990FCULL, 0x5A0543E404550D1EULL, 0x66D2407D5F6BA2C6ULL, 0xB3043BC6EACD4A1BULL, 
            0xAE3A48283A214AAEULL, 0xDE4CAD8F85ABF021ULL, 0x0D68C42A76C9B504ULL, 0x10736B1FC01647CCULL, 
            0x3FB800AFD11F2730ULL, 0x142E347A909DD6E7ULL, 0xB9D09B9ABED7B0AAULL, 0x9C7239CA69B3F821ULL, 
            0x696F1EBB18D7A54BULL, 0xC67AFCB6499040DFULL, 0x31632D37A372518AULL, 0x5BC1175F5150CF17ULL, 
            0xCBE767A0662C8235ULL, 0x8E6A6F18D27DC305ULL, 0x08135B09979EB06AULL, 0x7E6AD7CE656E7264ULL, 
            0x021BFC9313AC07E9ULL, 0xE48D9E3660BEB450ULL, 0xB5CAD1EDC9173B92ULL, 0x5757D1A37CF1C3D0ULL, 
            0xE8696D78FEB6BEA1ULL, 0xB99103331A980DB2ULL, 0x4BD74CECC5044182ULL, 0x71C7E9357A81CE69ULL
        },
        {
            0xA9BFF37F550FC34FULL, 0x11D88482B17E176AULL, 0x2F844AFDBAFB2FD2ULL, 0xC050EDD3BB897F13ULL, 
            0xE1F973C5040712FAULL, 0xE423C76892CD455BULL, 0x9CC47EC986732815ULL, 0x35B3B82347645B22ULL, 
            0xCCC031481B2DC798ULL, 0xB232DD27F89DCE04ULL, 0xD59BB75502F4F27EULL, 0x7CBEF24DA9A269AEULL, 
            0x1E8AA3BD17FB5164ULL, 0xE0471886F0180B0BULL, 0x882BFD980C606602ULL, 0xB41613947B989AD7ULL, 
            0x6D45B4077FD89B7FULL, 0x410A3C62725275EFULL, 0x7DF25DF5F8819EECULL, 0x1B3AC1DF4AAB6F24ULL, 
            0x24DC8E20E0CFD12FULL, 0x0C7265516B38DE1CULL, 0x892A88D5404424DDULL, 0x145CAA0214EE6072ULL, 
            0x7EACA38A54FBF30BULL, 0xA0C3612572A45400ULL, 0x0843301D575EF85EULL, 0xB750F9516A07FF3EULL, 
            0xB341DCEA29BB92B4ULL, 0x2DD7F8D4FF66002CULL, 0x2CE0EBAE7ABB09B1ULL, 0x6770178A76D3931CULL
        },
        {
            0x84E3FAEA003E5844ULL, 0xC0D686092528CB05ULL, 0x87C80FD66CC20875ULL, 0x90FF6A248F5821D7ULL, 
            0x1018D5C2DCAD8420ULL, 0xC966A15C122F1CD4ULL, 0xCCFFBC5C974982AEULL, 0xA24B38A799C05F6CULL, 
            0x54FF89E3CF642DC2ULL, 0x3FDC0CE037F146D7ULL, 0xF989AE15F70066ADULL, 0x03EC8FB2C99980FAULL, 
            0x7237DAC5D6333B32ULL, 0x96B62D38D53C3967ULL, 0x55D171AB820E52D7ULL, 0x6E29A38738DA4BDEULL, 
            0x0B5F7A957C392C7AULL, 0x4DEDBCB795A82780ULL, 0xF43E553D41A6D5E0ULL, 0xDEFBA084515E8BECULL, 
            0xC9859952F4DF7C13ULL, 0x8C612E30E8EA7A86ULL, 0x53097EAC913A9086ULL, 0x9BB0E50F949404E2ULL, 
            0xA41DADB262612F39ULL, 0x5FA5F86FB2147A49ULL, 0x1AF35134A87D2035ULL, 0x6542B7D352E37B2EULL, 
            0x20722F13E2952E5DULL, 0x77E3910F2AF72016ULL, 0x887817130058D93AULL, 0x091BDC42FEA41BE9ULL
        },
        {
            0x903B8EDF747AFD9AULL, 0xA6516F1620E2C319ULL, 0x2779D09336A0D848ULL, 0x3CCEAB30F3779062ULL, 
            0x30953C1C08D140D2ULL, 0x3CF4C38F59EF3477ULL, 0x3609543CEE961090ULL, 0xD970D3C388D168F5ULL, 
            0xB07901ABD3CF976DULL, 0xBBAC6144CC610ED8ULL, 0x341F0AB59DD4FF9FULL, 0xCBC5CB8B37EDFE32ULL, 
            0x8256C3A746F00BCCULL, 0x935808E524280C04ULL, 0x81E41381145E9C9AULL, 0x7E5E5D97045A96D1ULL, 
            0x65E2C3CD8D0673AEULL, 0x47801800D539E018ULL, 0x333908EC7C476F15ULL, 0xDB982090B91435ADULL, 
            0xE4A7AD56CD7D63D6ULL, 0xCD79F43DABE48DC9ULL, 0x2046861604DF728FULL, 0x053FD0FAFC472481ULL, 
            0x1FE6DD83965C8185ULL, 0x1E34DB0A9802B1FDULL, 0xD4C3CF25FC11624CULL, 0x7D2BE42AF49122D0ULL, 
            0x75D28E74DDFA66DAULL, 0xF3CAB7B15D87736DULL, 0x22560FC44544CB99ULL, 0x33783A12633FF19DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseEConstants = {
    0xEB7E17BE143FE764ULL,
    0xCF8FFDF8F145D21DULL,
    0xF9A8D323F61C5F90ULL,
    0xEB7E17BE143FE764ULL,
    0xCF8FFDF8F145D21DULL,
    0xF9A8D323F61C5F90ULL,
    0x6C2AD2B0938A7792ULL,
    0xEC7A21B32C30FCB0ULL,
    0xF6,
    0x5C,
    0xEB,
    0xFB,
    0x8B,
    0xB6,
    0x66,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseFSalts = {
    {
        {
            0x0CA850DD24E0CB7CULL, 0x2428DE4ABDE5CECBULL, 0xFFE96BE893DC6CA0ULL, 0xC75F55DADA158FE5ULL, 
            0x02FFC559F0E8E280ULL, 0x7F42C8CE897AB524ULL, 0xAF8C11DC4BE43EF6ULL, 0x41CF672EBDC4F940ULL, 
            0x06A03565A57956B6ULL, 0xA5C707E0A54E081AULL, 0x2A6A441638DD338AULL, 0xF02A99B0127FFB7CULL, 
            0xCBD35E7E068DA476ULL, 0xA0FA4F01EB63828AULL, 0xDFACCDE01D908826ULL, 0xDC9CD18A7780EB19ULL, 
            0x5928E6ACA0EA31D9ULL, 0x097C84BCA0951183ULL, 0xADB891C86CCA9B06ULL, 0xECA9592639CB0FAAULL, 
            0xAF85CA76E69732B0ULL, 0x2274F089BD8CD047ULL, 0xF69A1B8E637BB7F6ULL, 0x3180EB338D38D40CULL, 
            0x2CA1613156235F4FULL, 0x05148B8C44797457ULL, 0x12A2A34D26DB2EF7ULL, 0x00FAE1D3EEA096BCULL, 
            0x448BA5E5B132AC8CULL, 0xCBAD38E386CE1403ULL, 0x64E8FB9CD39FB177ULL, 0x102FF241E6E11A6BULL
        },
        {
            0x9B2091CD44D9B267ULL, 0xECFCBABF51FEDCD5ULL, 0x77BE06A5225C1201ULL, 0xA232078E15BFF647ULL, 
            0x038C075C7320581AULL, 0x0021939661FAAD91ULL, 0xAEA4CE92CF70157AULL, 0x399973802FC3E73BULL, 
            0xEA2259B18C1A151AULL, 0x439E18B1B73474CBULL, 0xA45FD347593D1F9BULL, 0x448B8632F6F50EEEULL, 
            0x9B3D2C48595E82C1ULL, 0x44D04FD5F108D1E4ULL, 0xB00EEDEFE2A72F18ULL, 0x52BB6B40C1E40CEAULL, 
            0x6EA18E6C4C737010ULL, 0x103D510AB9F22D6DULL, 0xC2FD8B04560FE894ULL, 0xDF80A12435DC1AFCULL, 
            0xD107799A25591735ULL, 0x9289B3AA013A1437ULL, 0xD22E95D03CF7B569ULL, 0xE15BC1AE8CF7B5CFULL, 
            0x26639617BD690E56ULL, 0xC6F569FF4C38B892ULL, 0x67A1D4C9250ABEE3ULL, 0x07FF5442BF79E508ULL, 
            0x6E193493831C1EBAULL, 0x045453A1FD8CD81EULL, 0xFE74F2F781DE2272ULL, 0xF4DCFA45559DC93BULL
        },
        {
            0x87FA310226BF5FF0ULL, 0xA69D2B734EB6D13AULL, 0x1A880A7E4BDEA946ULL, 0x540435D50638DFCFULL, 
            0xAB3DB97D7C6163A0ULL, 0x444F590EA5C12A19ULL, 0x22EBD8984840A2F1ULL, 0x691EE9441C87B22FULL, 
            0x2724A7870084C7C0ULL, 0xD17ECDFB1A3D3C14ULL, 0x8ECB7116A87ACCC4ULL, 0x5A1A95205F96849EULL, 
            0xA01EEC241C9CD895ULL, 0xF4467F8F0637ED59ULL, 0x00C81141B1A0A5BBULL, 0xC746824BD18BBDFFULL, 
            0x21D382919A37FB12ULL, 0x06A1DA335EC779F1ULL, 0x445692D75F97BFA3ULL, 0x1C48944DC6340DA1ULL, 
            0xDE071545292F6DE8ULL, 0x20CFDB71BA6DB18DULL, 0x7E29F0F068099BA7ULL, 0xCF636A3D6C041BA2ULL, 
            0x88E74A0F43954639ULL, 0x0775E4846A477A18ULL, 0x2CDFC0A9EE898378ULL, 0xDD575188782F7640ULL, 
            0x2E563739B97961B9ULL, 0x6494018492E7B98DULL, 0x00F29F3E12D08882ULL, 0x57ED0D5DEC6E4D9EULL
        },
        {
            0x4F330667660FD3B0ULL, 0x07541358F81855B9ULL, 0xA8E80B903ECCA023ULL, 0xC4F284ED5F8F6B55ULL, 
            0x4EDCF0BFA16A0DC7ULL, 0x2BACEED2A6366408ULL, 0x211A4D54FDF32FEDULL, 0x3B53CEB9254BC316ULL, 
            0x06C8127B1B06E8D8ULL, 0xB5005E8B3F144564ULL, 0x8248857247657FE9ULL, 0xAEAD535ED25A3ABEULL, 
            0x20C6F161FED08CA5ULL, 0x8BB4CAC287128FA8ULL, 0x612F488690DEE4AFULL, 0x1E771A0B876E6F80ULL, 
            0xCAF95A047173B9DEULL, 0x4737409E2EA223F7ULL, 0x7AD0554A8E98E304ULL, 0xCC332327D982AE45ULL, 
            0x2B6B9D0B0DD4AC48ULL, 0xF1EFA0832F2F4522ULL, 0x54AB7A01C26489A2ULL, 0x99CC64C7BC29DBEAULL, 
            0x39E9347C9DE35CF6ULL, 0xDF1260B0A236046CULL, 0xD3139B40F2543ED1ULL, 0xF4EF28CCB213B5EAULL, 
            0x3A69D4E64F683604ULL, 0x1BED199F20E2E6FDULL, 0x10AB196472DE250CULL, 0x42A701734A857AE9ULL
        },
        {
            0xA2CEBCAE5478B216ULL, 0xAEE49A2878712D4BULL, 0x71CBE506C488C82BULL, 0x54948BC0321FD171ULL, 
            0x19F2C27DA2C8D2BDULL, 0x7EEC35258A4ED114ULL, 0xE133E064C6DEFFABULL, 0xE026759374EC4220ULL, 
            0x714320A3991ACCEBULL, 0x0CF60B6C8ED2B8A9ULL, 0x2D12BB8EAB8A248FULL, 0x50C3D7341CDC5476ULL, 
            0x30A3FF92764627A0ULL, 0x4FED3CCC1DD1BFFEULL, 0x4BFD4C9BBF58515CULL, 0xCB79D8B32072915CULL, 
            0xB45BD7DF37D2ACC7ULL, 0xB0E7CE6439BC683AULL, 0x4134E29005D5E07BULL, 0xA3341ABAA67B28CEULL, 
            0xD16CD88698F01C93ULL, 0x2442796E0E884925ULL, 0x2D5D27BA2F776B32ULL, 0xEE4549CEE8FE18C8ULL, 
            0x5404E82D39B07BD6ULL, 0xC95A20DBF0A964ADULL, 0xD75A091BD2C428F7ULL, 0x8A9F53869BA8AB8EULL, 
            0x9A0AA9098DAE88E4ULL, 0x4B28952F096A95EEULL, 0xEF59790A0E02DF8AULL, 0x3E5A45D46044B0CCULL
        },
        {
            0xE24E1EDF73EA25B6ULL, 0x797769A5CE565C94ULL, 0x89AB0CD7A56B5CA4ULL, 0x07F3AF3CDA20E7F5ULL, 
            0x343AB527EBE6CFE5ULL, 0x91AB361E041148FCULL, 0xE47426A4955039D9ULL, 0x6C5B4A2F51E5594CULL, 
            0x756B177BA75A11C9ULL, 0xA9C424B2D261C239ULL, 0x3B24A9FCA2D6B7B0ULL, 0xDB73737233861781ULL, 
            0x5F307D997F7F8512ULL, 0xE44D5C56A8997795ULL, 0x0855D29CD3F514FDULL, 0x7FECBAA3F85C420CULL, 
            0x06BA8280AC4AAD34ULL, 0x9ACAB601360ECDDFULL, 0x89777FBD6A9071C0ULL, 0xFF323CD679B6D4B2ULL, 
            0xC449CB09EBE54BD4ULL, 0x2C97014821D95461ULL, 0x4C6136ABD1719F6FULL, 0x31585B0539C93C98ULL, 
            0x9675F9BC34E20229ULL, 0x21848DA84E051207ULL, 0x59D2C9067E56B14EULL, 0x0472148F3423CE38ULL, 
            0x4A4DF9F66A48045AULL, 0x70C8B366A934F45DULL, 0x16917E659F49C6C5ULL, 0x0455D3955C0FF505ULL
        }
    },
    {
        {
            0x419F3128E6DC49FCULL, 0xE8841556DCCD9CC1ULL, 0xD5AA15482523C99EULL, 0xDB0AA98FA6910E83ULL, 
            0xF216FF151546B0B6ULL, 0xC18A8601E743BF12ULL, 0x37723D1D74EA59F2ULL, 0x523F014413634C74ULL, 
            0xBD81F542CEF87073ULL, 0xAA09F2C9004A6094ULL, 0xEC052308E506BDC4ULL, 0x5803A7AE86A371F0ULL, 
            0x644337CCA42AA246ULL, 0x943794C8662A89D8ULL, 0x4C50C2C97501F040ULL, 0x4E5F6603C1066077ULL, 
            0xF8303E3505B574B9ULL, 0x860E34E28316B789ULL, 0x121F2870F7EFF1B4ULL, 0xE74BA8517FB7913BULL, 
            0x57E494D9F6F979A8ULL, 0x53B1CD3CA4B46EA6ULL, 0x9FB82D6341315CE2ULL, 0xE6A92AAFE479B21BULL, 
            0x0D7FBDE60CAF24B2ULL, 0x4650C828E4BED92EULL, 0xD43F25DC3ABA56C8ULL, 0x6E8C6E3B9DC47C18ULL, 
            0xBF76C96B3559D195ULL, 0xDCC3355AAEC93F0DULL, 0xEA4A96CAFD51B51AULL, 0x61114330EE0C665DULL
        },
        {
            0x38C3B09561F71FA4ULL, 0xBC9A98E27AC53490ULL, 0x78E2D0CFEA738689ULL, 0xD586B218564993DFULL, 
            0xAA7F71D8B89166A0ULL, 0x6B304E3410AC43CAULL, 0x40E411BB10580B73ULL, 0x05BCA9FE96DB2411ULL, 
            0x291D07AE3A5C7217ULL, 0x71EB08799E4018F3ULL, 0x61E72ED2A6E98882ULL, 0xD95ABEC0A59B719FULL, 
            0xD79CD326A81A7754ULL, 0x999424B80F678B3DULL, 0x521E7EC43AA7E627ULL, 0xE59D1B120CA5EBB2ULL, 
            0x84CCD95B1062FC63ULL, 0x4490329207EC56FCULL, 0x5550457EBE0C4CD8ULL, 0x625191D3E4256323ULL, 
            0x5DB81E9A5FFE3EA0ULL, 0x1BF28075ABA3F5BDULL, 0xF2C072305511858FULL, 0x82AE787DE5A59935ULL, 
            0xA6ECD452E4163C95ULL, 0xDBB2E9859D2B0672ULL, 0x2F0103F1FC948EDCULL, 0x859E7C992DB778F5ULL, 
            0xC6DA8FEB76A5BD74ULL, 0xC3ED32DD73B69D34ULL, 0xE59338F90E8687CEULL, 0x44413D0FB28BD2E6ULL
        },
        {
            0xA3FB818AF4EF614EULL, 0xA623CCDB207C7E37ULL, 0x8E3A827CBBC79505ULL, 0x775327F239086CD4ULL, 
            0x2D34211A487F1D9EULL, 0x5E870C52307FD4E0ULL, 0x7CF9873FF7524C93ULL, 0x2269771129055C02ULL, 
            0x347B6D77D3B0318BULL, 0x455562F3429DECB3ULL, 0x1623D216976396AEULL, 0x4966579565A3B347ULL, 
            0xBFFFE01F5F7416EEULL, 0x5065B217AEB7C948ULL, 0x663F4156C5E78785ULL, 0x56F7C7650C0D5712ULL, 
            0x7F8F67ECAFF3060BULL, 0xA884757635B44923ULL, 0x1E6B8DFFA68B4465ULL, 0xA28F4A2A842C37D4ULL, 
            0xC832B51ECFCC9683ULL, 0x6A855DDDCD77312AULL, 0x399364D0CAFAF26DULL, 0x4716194C344BEF2BULL, 
            0x28C10A284B91F9D6ULL, 0xBAB7309C10C0339BULL, 0x818F58F4F277C4C4ULL, 0xFB7C8893DCB4C144ULL, 
            0xC49D83923D2BA8A0ULL, 0x798847203DCE1A25ULL, 0x87BACAE5FDE546ADULL, 0x5F39A34EE39E5051ULL
        },
        {
            0x5BD4F41E978676B9ULL, 0xD0193F30459D1777ULL, 0x8D7CBEB001FB9A5AULL, 0x4BA0E359843F04F7ULL, 
            0xD1DF478101DFF425ULL, 0xEE02B788B87F0361ULL, 0xE9F1BB5414549D43ULL, 0x4CD5A8F84A8C1065ULL, 
            0x087BFFDA35386778ULL, 0x86819DA2A63D73B4ULL, 0x8B031D498C0DEE84ULL, 0x90F3DAB9358F5CB9ULL, 
            0xF19D3F3AEC783243ULL, 0xB0100AFFA1DDD5E7ULL, 0x5CDA6C1B2901E72CULL, 0xD9534CFAB8633967ULL, 
            0x4DBB6CE2FE1E3AD0ULL, 0xDA625D03F24977C3ULL, 0xF55E326C4B086397ULL, 0x1BAC130A12BA4529ULL, 
            0xEE08B04B10970318ULL, 0x6AEA9772189F5403ULL, 0x20913383C339F9C3ULL, 0x14D4986271FE792DULL, 
            0x6FAAC0E0E1516712ULL, 0x033E946CC980D96FULL, 0xBC4BBA0369AD3E86ULL, 0xD4E6C611E91625E4ULL, 
            0x36013F70C8BC1BAAULL, 0x6A365D308580E9B5ULL, 0x1D46A1F2B3316723ULL, 0x15AB2ADEF3872236ULL
        },
        {
            0x84F4D1939DA22E3EULL, 0xEC28446A46C42CF5ULL, 0x7374066525FC9336ULL, 0x32E0A7DBB260507DULL, 
            0xB5BCA56C8089AE46ULL, 0x821042B12E87D282ULL, 0x3FF3D07A8E794413ULL, 0xE32D197A5D90FCD4ULL, 
            0xF655AF16E251AEEFULL, 0x6E4A57A66B41EBA9ULL, 0xA2D0D8F4E68C8724ULL, 0x355E522BD71DBB80ULL, 
            0x2869172057DD64D4ULL, 0x5E2C40ED88F424EFULL, 0x18740220B8EFB0C6ULL, 0x10FE1828DC3C8D86ULL, 
            0xEC40F007296B3364ULL, 0xD0DE4C01CD498D4BULL, 0xFCEA37FA6303B144ULL, 0xC743F0EA8CDF0126ULL, 
            0xE3C65BE0AC658819ULL, 0x7CF6145DA5C9F72DULL, 0x8330E1268EEB88F1ULL, 0x2FACBC190457639BULL, 
            0x6B99242FBF22B8A7ULL, 0x00B517D24A2440A1ULL, 0x97595E9D6FA5E294ULL, 0x77D63A0516A0855AULL, 
            0xF8C98B9D061AE2F9ULL, 0x99A37B55FCF9998EULL, 0x39179F3504C6D3B5ULL, 0x588017AE33B8B21AULL
        },
        {
            0xE986453520BA8E1AULL, 0xE080DDB3E4DB2A31ULL, 0xB0A8573543EFB989ULL, 0xBE7B2CD483C6BB47ULL, 
            0x1242D5429AFBDA65ULL, 0xA7C38B3648FDC1D1ULL, 0xE2F3EDEC6F46DF14ULL, 0xD7A355C9F6A4C5D9ULL, 
            0x67D1A176EF819438ULL, 0x006A8EB64A011828ULL, 0xEEDC0B903BB8FA9FULL, 0x9D07035C486EA2AFULL, 
            0x920554BA11B0F147ULL, 0x3711859FAA134145ULL, 0xD39A6E21E1B146BFULL, 0x9A7500E9B734ACE1ULL, 
            0xF5A5A0FAC16D43CEULL, 0xCFFB208C721BC6CAULL, 0x25CB77A220797039ULL, 0xDB5BAB2F4A8F9DE9ULL, 
            0xB811B1A8CACFF045ULL, 0x29BAEB982C64BFB7ULL, 0x0D19729D3303EF4FULL, 0x41D255F74CDF8C4FULL, 
            0x5A19E5750425A403ULL, 0x5AE06C83164B1C89ULL, 0x2D1C96E0FA62F0FFULL, 0x1538810E285C03FAULL, 
            0x42996F7DE4207BCEULL, 0x7ED5FC079F081084ULL, 0x92E4B55DE194471FULL, 0x45C531F055ED9A07ULL
        }
    },
    {
        {
            0x94427AB2370E2371ULL, 0xA2811E3A79FC41FEULL, 0x179DDBA3C7A63CB0ULL, 0xFB2868EA1AFC9902ULL, 
            0xD4B11CADDE7B3320ULL, 0x28B01A68CB7D141AULL, 0x9E62354C613CD1FDULL, 0xD3AEFFFDB2BA6C3EULL, 
            0xCC31CAEAF15C2116ULL, 0x94FE9718969A2AB7ULL, 0xC027CDC207449515ULL, 0x256E879D55714772ULL, 
            0xACFEF25DF7E52BCFULL, 0x42FA0E59686E9985ULL, 0xE17EC9869F7CF465ULL, 0x3BBD23CD411601F3ULL, 
            0x42EA2C3B1676BBADULL, 0x1FBF79F51515C81AULL, 0xEDFACCD07D82D2C4ULL, 0xD68D1A98C2E9F4ECULL, 
            0x2F4F215ECF469C8CULL, 0xA8120AC7753EF7B1ULL, 0xCF0E2EBEA5FE2B0EULL, 0x36F605ADCB269715ULL, 
            0x033FE2C583137347ULL, 0x8342DFB5AAE5449CULL, 0xBE0D238CC3091372ULL, 0x89BD77983C1E1240ULL, 
            0x48CA35AE47E4824DULL, 0x72DF93C6BB28F4DAULL, 0xEDC6DC747C4A85A7ULL, 0x24B526AC7103B60BULL
        },
        {
            0x702116A8509CDE2FULL, 0x23AB2586F8DFB445ULL, 0xFBE4245FE0C18A3CULL, 0x5D5F145D5B54DA5CULL, 
            0xC4BBBE0A5DBCFF27ULL, 0x9B9FC241C9B4E6E1ULL, 0xFFC0F5CF6E2A50AEULL, 0xB41799694FCF9889ULL, 
            0xCA4452A52D56FAD5ULL, 0x0B5A8358DB8E5DD7ULL, 0xF21EC8814329AAAAULL, 0xB95222F6C81D43D4ULL, 
            0xF14843ECD7B56680ULL, 0x5B6A8166F3BC42E9ULL, 0xE09BFE8CD138F5F0ULL, 0x04E2E4B5510E0F0DULL, 
            0x896CFA66557632AFULL, 0xB2A39FBAB21DDFB7ULL, 0x98FE3FEF67906D36ULL, 0xD73A8E36C081E8FEULL, 
            0xAEF913FC7BBECBB9ULL, 0x9D8A30AFF9F3AB1CULL, 0x76AAE8661D1BACC1ULL, 0x566EC2CB949FC3A4ULL, 
            0xB1AEF2C6ADDF94E0ULL, 0x685DEF3BE6CAA974ULL, 0x43141405F1F36357ULL, 0x4A97A14C001BCB7BULL, 
            0x00EEF48421F4335EULL, 0xF4620BF120B0CE9AULL, 0x6AA5FA0949804D86ULL, 0xE85088D55C3B8320ULL
        },
        {
            0x47720C1B01D199ACULL, 0xDB2A5E4D335A97C1ULL, 0x5C8FB7421CA4B543ULL, 0x23CB6DF7A2F58A2DULL, 
            0x8A257F336ADF1A89ULL, 0x0FC1360CF58347CEULL, 0x1DF554C18FB2252EULL, 0xA74FCD9058465501ULL, 
            0x915FE54D009361C4ULL, 0x66A7C08E7963E40DULL, 0xF2A946939BC4B0ECULL, 0xA8DA1FE22094BBAEULL, 
            0xCF859BBFC453AB78ULL, 0x04C996E3EE4C8A2EULL, 0x5A255F105A1D3FB3ULL, 0x08FD6F981B499020ULL, 
            0x44CBDC1F55A09A55ULL, 0x4E44A26FFD54AB51ULL, 0x33E51FDF874F0110ULL, 0x9AAD3093391E0FFFULL, 
            0x27C9A6977F052F61ULL, 0x1F2EA35A4D840335ULL, 0x2B95B65699244D46ULL, 0x26BCE02A3163B7A3ULL, 
            0xB8D96E6E00671549ULL, 0x78A6B868597E4879ULL, 0x9AB8289B844EEE42ULL, 0x648BF6CEE430AE4EULL, 
            0x0C3439C82BD81061ULL, 0x62B3F6501D585653ULL, 0x94823DC757CD7E91ULL, 0xDC81AA46E0C41EE6ULL
        },
        {
            0x3A38229DCAE45695ULL, 0x3602C8DB1A878BB2ULL, 0x1DDF554831BEE9E3ULL, 0x15B797CE2C43CF17ULL, 
            0x75D755BC68222980ULL, 0x6C47768D5476F3B2ULL, 0x6300C95021877E0CULL, 0x7A1C5CFE3D26C83BULL, 
            0xC8A6EFC7AB7D8AD1ULL, 0xEF70B7E852AEBBF1ULL, 0x53106D11D33E9903ULL, 0xF245D5B6B87B8478ULL, 
            0x61D1356845ADE9B5ULL, 0x73CE4B041F4EAC47ULL, 0x4B53B0B194B9508FULL, 0x0E7E0F2622DF107EULL, 
            0x7FA85DB81D00D59AULL, 0x94B88D327362B629ULL, 0x4A7ACDD0E2F8DF9FULL, 0x7E14B82EE0FC473AULL, 
            0x66F2053D27E835D8ULL, 0x3E801D3AE176B531ULL, 0x5E6C7CAD20843745ULL, 0x32057FDC5EC1F9D2ULL, 
            0xF972FF7F99873C46ULL, 0xF229FF217A6D93A9ULL, 0xDAE7FA53D3CBC749ULL, 0x2520DB0422DF20D0ULL, 
            0x9D6ABB8143248E51ULL, 0x4BF2C15252E3989DULL, 0xAC357D826EA65D6FULL, 0x8FADAC42D2754E80ULL
        },
        {
            0x05DA12E81225A246ULL, 0x9CE82C012520A966ULL, 0x554E7CA0B2BB136EULL, 0x5558046EB5EA2592ULL, 
            0xAE3F4E2738D8A463ULL, 0x314136C42AFD9E56ULL, 0x9EA4894CC3A6D137ULL, 0x6A5B1DEE07CE11CAULL, 
            0xBF9479C651C2F260ULL, 0xC2119586B383B9F5ULL, 0xF5A0563E10CAF687ULL, 0x8CEF968D364E246BULL, 
            0x4D9BB6DC01345000ULL, 0xF50A14A67D080F23ULL, 0x2983032457915EB7ULL, 0x4519CE751A2FD65FULL, 
            0xDAF9B581CFEA918CULL, 0x907F6851A323EB32ULL, 0x3F5E01C0709E00CBULL, 0xDB6E4B3F8B37A50AULL, 
            0x5080C68120AA4AB5ULL, 0x306C29A5C2BD8ACEULL, 0x700E0CDC20C0D26AULL, 0xADFD2B7BE9F3BEFBULL, 
            0x96C9FFF403C9E25DULL, 0xF0B8D2E8E80A70C4ULL, 0x572BFCBA38153C45ULL, 0xEED4E7F8CBDA07D8ULL, 
            0x0386960C6334CF34ULL, 0x57498F8717D37BE9ULL, 0xA5EB9121FE66577DULL, 0xBC73BCAE3012327AULL
        },
        {
            0x4A8352937D77387FULL, 0x7E04011F45368E32ULL, 0x0B8D2AD99A3939BDULL, 0xD1F90116914E18F6ULL, 
            0xA129CD7B2E80C926ULL, 0x76A8A96B3E485C71ULL, 0x579FADD455011D9BULL, 0x8678EF8E75F6208FULL, 
            0x96FB984F300E9C33ULL, 0x44614AA4325D271BULL, 0xF8CC5895099D7911ULL, 0x9CE90D471C1C1F8AULL, 
            0x706DBA0E90D3340AULL, 0xE2B618E846E9B4EDULL, 0x080C0BA13B3FEED9ULL, 0xDBDFF42858675492ULL, 
            0x5440F70A930EAB99ULL, 0xF1A05A23CE21649FULL, 0x954B44D7B186C1DFULL, 0x503989A1E4E0764BULL, 
            0x69A8D68DD020E75CULL, 0x5A7F6F301D73E408ULL, 0x177CF4A2A8E459B4ULL, 0x47A1075124A4AE4AULL, 
            0x59E4C7A6B21462C0ULL, 0x97FDDE55F6E7329EULL, 0x0DFE69E5A3B5BD50ULL, 0xF13091C09BF272D4ULL, 
            0xFE9B53D15BC43D06ULL, 0x0BDD40DBE50DC43FULL, 0xC870CF38872FD01CULL, 0xCDA48D53C859F319ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseFConstants = {
    0x3870DEB0365C10F2ULL,
    0xFC2C3B8AD1B6CBBEULL,
    0xD448E5269D0B0CDFULL,
    0x3870DEB0365C10F2ULL,
    0xFC2C3B8AD1B6CBBEULL,
    0xD448E5269D0B0CDFULL,
    0xA3608DF842C80290ULL,
    0x0D9DE6763AD3718DULL,
    0x35,
    0x3F,
    0x08,
    0x97,
    0x55,
    0x18,
    0x42,
    0x0D
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseGSalts = {
    {
        {
            0x6D4D3E379C913BCAULL, 0x1782278704F256F9ULL, 0x767332AA1000F8A8ULL, 0xE1039BFD1C05A3EBULL, 
            0xFBCDFC6B6D616C83ULL, 0x6316A33A93AEE5C1ULL, 0x23E76FA8CD0446D8ULL, 0xB258FD50CFBFDF45ULL, 
            0x23AB663947DBDD6EULL, 0x33E6182EAF517E6DULL, 0xA85EF4806C18C0AEULL, 0x1922E2EA5B7E5FF1ULL, 
            0x771D7F1EFDF8945EULL, 0xCCAC5986A2DFEB48ULL, 0x611C4CD1AE12F3E3ULL, 0xA7D9DA3C0ECB1F4CULL, 
            0x8368CC767513F125ULL, 0xDF0C870F2A882C6AULL, 0xE991179C9E527373ULL, 0x9D4EDF7E7859484CULL, 
            0x095BF45BE73542BFULL, 0x2C1DE581DCB41D72ULL, 0xEE74FDADD0DABA47ULL, 0x0FA619A85250A57FULL, 
            0x2513A6D28BF03FD9ULL, 0x81F8119AB0664442ULL, 0x0D31B0BD923CC621ULL, 0xA36CB6B5ED563058ULL, 
            0x66F54E987D8F64FAULL, 0x5A57B761583790FAULL, 0x6A18BC754D322CD8ULL, 0x2BE287C4D15E90B0ULL
        },
        {
            0x7D616DD27F825B76ULL, 0xF275D683CEC4C1CAULL, 0xCDCE06E1D087EE69ULL, 0x427A3281AFF37C99ULL, 
            0xE6C2226D7A2EE2BDULL, 0x42B29115AE56FEFAULL, 0x3977E2C1C2870E47ULL, 0x30FB99B3ECDCE575ULL, 
            0x8D94EC5B300FECF4ULL, 0x42D82519DE58775FULL, 0xE7267971C68C7CB2ULL, 0x0335552CCB903022ULL, 
            0x6819D4225FA803A6ULL, 0x8829C71B475A6BD5ULL, 0x249EBFAA7895479CULL, 0xDEF977074B0CA628ULL, 
            0xF1718A3BC342111BULL, 0xB38E75828056EB9FULL, 0xE85D12B1E6C7B269ULL, 0xF8410BF4FF079A24ULL, 
            0xDD1F0E94F2E09C0CULL, 0x84D2FD5FBBAB7596ULL, 0xB780A38301EB09D8ULL, 0x73A5DD509D1CD701ULL, 
            0x4039F08990E16A0AULL, 0x4DA3887BA97E8625ULL, 0x10A1B77A475619AFULL, 0x7B888404A2837DB7ULL, 
            0x7ED4EDE972814794ULL, 0xF7292A31349B4EE1ULL, 0xCF6B554EBFA8CDC9ULL, 0xED03A30C5475B694ULL
        },
        {
            0x0AFBC5DA30B8DC17ULL, 0xFB3E86D72876098DULL, 0x652BD4FE75D9829DULL, 0xB5D856FF932DC0C4ULL, 
            0xAFC53B1BA51BED89ULL, 0x8B9F7F466FA8EC74ULL, 0xDB8A48819B6D292EULL, 0x8E9E7010A20E7FBDULL, 
            0x744596614C45A0D7ULL, 0x0F786466800B9E72ULL, 0xB643F7678CB85417ULL, 0xE5592941E6BCF0BDULL, 
            0x56D183BE2B572F39ULL, 0xCA7CD8DBB748E33CULL, 0xBF1A2FBE614EA94AULL, 0x5026A6E550392A49ULL, 
            0xC93FD1B3BFE03305ULL, 0xD2F349D16B235BBFULL, 0x20516B475BB023CDULL, 0xA71FFAA539E8F476ULL, 
            0xF84ADAD10834E3F0ULL, 0x0B0B273DC29DCBCAULL, 0xCCFF4B6B11B4BFDDULL, 0x0AF9EB946B97719DULL, 
            0xBEBEFDF48C2B5C4BULL, 0x5601ECE50DD1D482ULL, 0xAB738239C57670BAULL, 0x676924CC14FA6075ULL, 
            0x698AB53EEB0A276FULL, 0x62E17DF5298D93B0ULL, 0xCD35C53ABA3CE2E8ULL, 0xEBE28E76907498CCULL
        },
        {
            0xAA7195B95C7B7973ULL, 0x84E54974438B0D8EULL, 0x343CB15FEE167B5DULL, 0x2643FA57980384FFULL, 
            0xF8FF7BACD2E7606FULL, 0x66FBD8187CE70A55ULL, 0x616B3C71A47534B8ULL, 0x7412F8CB8E3D2AEDULL, 
            0x3607860D566C6A6CULL, 0x87B67CBC625B3D4BULL, 0xBDD02E1835656BA1ULL, 0xF8A09394D46EF8B3ULL, 
            0xB88319A8CC636599ULL, 0xEC20D67FF426CD03ULL, 0x90DBCE2E3B6D622BULL, 0x874727FBE9057D08ULL, 
            0x9EA3B7D09218475EULL, 0x43570C6097428898ULL, 0x4D3B35F968633BEAULL, 0x9813B8ADAB08FA12ULL, 
            0x67BA37FE815ABB4DULL, 0x772375394358CB56ULL, 0x034EDD7893EFC495ULL, 0x6E93BDFE81760C5FULL, 
            0x221E728378391A1AULL, 0x1B5771181848B15AULL, 0x59BD92E10A65E6CAULL, 0x8F8FA2C8D86246AFULL, 
            0x87F2276CBCC6F3DBULL, 0x9E3688A05FFBE9AEULL, 0x665AADC2D26B7F34ULL, 0xBA041BFFB898320BULL
        },
        {
            0x1A49ACC59FD5C1C1ULL, 0xA9AA463DB1F05112ULL, 0x3B9354F1FBCDB3D0ULL, 0x0B59F96C61CB37A9ULL, 
            0xB13219CD16631F3CULL, 0x4FFEB6873B82BA45ULL, 0x3440BC2AC984751AULL, 0x28C20914841ABAC5ULL, 
            0x32DF1796EF5B0622ULL, 0x0CB126148C7D03E2ULL, 0xA0AEB96E979F0022ULL, 0x027330E3CF9C86EBULL, 
            0xFE7C25822B70DCEAULL, 0x23A8365F94EC53A7ULL, 0x461DDA407B396F29ULL, 0xDE8E69E7D7D9B0EEULL, 
            0x5ED6D84007240DC4ULL, 0x24380F1840C7CDDFULL, 0xAEA82EFA73387787ULL, 0xDD7070349F2655CAULL, 
            0xB342BDA322692670ULL, 0x6A824E734DED7CE7ULL, 0xA69018812CAB65C4ULL, 0x8D2535EAEF51C45AULL, 
            0xD19F6564D9C7FF87ULL, 0x1053807608A8563DULL, 0x1EAFDDD81BC996A3ULL, 0xC1596219859D125BULL, 
            0x809CCA021593DDAAULL, 0x7D90CB0DD9A5AA8BULL, 0xEBC4428452A12841ULL, 0x20871A2561BB38DAULL
        },
        {
            0xE53A37E8B175DC71ULL, 0x788DDB71D3F58962ULL, 0x3036FC278DFCA155ULL, 0xAB4B6295060717D5ULL, 
            0x79AA85AC60EAA26EULL, 0xE0D0CC03EAEBC598ULL, 0x568751AE2AB93CE6ULL, 0xC8D2BEE90847EAEDULL, 
            0xBD7C6F926C1418D6ULL, 0xF5CF1B87CF037BEAULL, 0x5149E48A5464EC3BULL, 0x3963510A33011806ULL, 
            0xD85343ED4A88BE9EULL, 0x5A946EB38696CF45ULL, 0x805BAD75AC572BD2ULL, 0x41C86AB19EBF0C91ULL, 
            0x05ED58CCFB6C9069ULL, 0x366CB39F6B8B2FA0ULL, 0xBCEE1BC5C21A9494ULL, 0xAA409D611B23633BULL, 
            0x443BB0ED73CDD6BDULL, 0x7968A6D7D759A092ULL, 0x86A5237DB7AAA0A4ULL, 0xB48FD9660FC146DCULL, 
            0xCA20E26B43518C13ULL, 0x737E6F937CF9741AULL, 0xB77351B3D19A682BULL, 0x195422B2D45EC65AULL, 
            0x2ED45DAE0EE163A2ULL, 0x052CC9C40AFC79C3ULL, 0x31ED9603E17ADF41ULL, 0xB89D3FA858B4EC42ULL
        }
    },
    {
        {
            0x6CEC572C9A705F0EULL, 0xFF1C1D74E76A7F05ULL, 0x7E2C0D214C44F476ULL, 0x8E80E6985F8090CDULL, 
            0x271B89DB1C0FBD01ULL, 0x1381A742CD1C00DEULL, 0xE8FFE80FEF0EF690ULL, 0x099C17888E36A670ULL, 
            0x2BCCC8C707DD00C4ULL, 0x57A656EAFD169C2DULL, 0x8FC084C3C9942311ULL, 0x4CF012CF4FB67B60ULL, 
            0x978AB5BB3360B75DULL, 0x9D4AE5BECB7769E3ULL, 0xD2AB341375B73D7EULL, 0xEAFD33B20A7FC23CULL, 
            0xDCCB9B654D375F55ULL, 0xF17029F3B43EEFC6ULL, 0xACACFA921A360CB7ULL, 0x0F78DD096D3DB1BEULL, 
            0xA6A3A1D13B5CD941ULL, 0x89173C2E4210B157ULL, 0x78ED442CEEC9F192ULL, 0xE508386998F8D890ULL, 
            0xEA4AB69411ECC8CDULL, 0xC96F7B09AA100894ULL, 0x1B4546E8FBDCA032ULL, 0x21FC1F4FA4A9F8ADULL, 
            0x9E9A015FF59FA8C6ULL, 0x36EDD2BF6C81A173ULL, 0x580E6609682BA7E8ULL, 0x066590D9A70541BBULL
        },
        {
            0xC8566E0F39FE5301ULL, 0x6A6A73BD48233D1BULL, 0xF949A7B6ADAEB4DDULL, 0x216A05583188F425ULL, 
            0x15825F375F200409ULL, 0x5C769772BE6BA7B3ULL, 0xEC4CA2D90A2A34A7ULL, 0xD28BAB0C21CB8903ULL, 
            0xDA73050FECB4BDDBULL, 0x31C7721239ABE260ULL, 0x7F17818EDDAFD035ULL, 0x28CBD976802A3DDDULL, 
            0xF64DDA4D0C4856F9ULL, 0xF173460132B30397ULL, 0x899228084E614017ULL, 0xF88E5C4A24156DE6ULL, 
            0xE5922496DF7ECF44ULL, 0xD7C432C8CC27BEEDULL, 0x6EF213BD8A615767ULL, 0x26C4522E82515708ULL, 
            0xE0C026E22BFB16F3ULL, 0xB75F48F406C09583ULL, 0x3160C8F68E4747CDULL, 0x36C3981BA14DFC95ULL, 
            0xE08F3C2D94EA8D56ULL, 0x6AE14FB441BFBE41ULL, 0x1398277306ADA8C3ULL, 0x0D59BD461221C1ADULL, 
            0xEC5C1DEB6E9291E2ULL, 0xD86BDFCF0BE2242EULL, 0x2DBC239E9E6D9C42ULL, 0x7DD911156D14F00BULL
        },
        {
            0xF868DDE77B8EA340ULL, 0xBCC65E054F212257ULL, 0x1E4E2709CFE0061EULL, 0x8F0B37C7D75003A2ULL, 
            0xEE8DCAED3AE82FF5ULL, 0xACA7ACB5106C7EADULL, 0xA4087B7479EAF288ULL, 0x659A67E2B908F098ULL, 
            0xB0ED544F0AEFC0A0ULL, 0x7BDDE2B0ABEAD93AULL, 0x3D7F04E1C7C298E1ULL, 0xC9732F91FEC2DD39ULL, 
            0x18761E6EE201E7C1ULL, 0x5D18548B448B324DULL, 0x910DA326035EFA11ULL, 0x24487D6B9D5C3904ULL, 
            0xECD4359CE613EDFBULL, 0x769922F2CE4FA507ULL, 0x76E2E790D6984B5BULL, 0x8AF735C726AC3D14ULL, 
            0x17123AE13A2B7348ULL, 0x9E6DE0FE2CD3F9D7ULL, 0xA7FEC9FAE7DA5413ULL, 0x30DC60FAB96895DEULL, 
            0x49CEA152182702CBULL, 0x2607A8BB106171E4ULL, 0xF5CD4CC751E601ECULL, 0x413FA973EB81EB97ULL, 
            0xC703963CC379618DULL, 0x32E96F145AD374B4ULL, 0xC938D95A374298CEULL, 0x74CD601562036997ULL
        },
        {
            0x172ACA1526A99E69ULL, 0xC07A6F983DD522F3ULL, 0x55D29997EF8D9F0AULL, 0x28BC1B0980A14478ULL, 
            0x7F3EC3B412BCB3A9ULL, 0x855EF40F6CA30CACULL, 0xF65336FF38136ACDULL, 0x6412D56F2EC219EEULL, 
            0x12116F719B527812ULL, 0xC7F7BA66BA8B83DAULL, 0xDEE9E188016DEAE9ULL, 0xA8C81BF95613C32CULL, 
            0xC19687C92B83B699ULL, 0x64D44A3329550F61ULL, 0x262C9461B7531F47ULL, 0xF51FBC953332102BULL, 
            0xD2EF34D78A5F734AULL, 0xCD4C7E9966886C72ULL, 0x34267E3486BE3E52ULL, 0x7BD3362C57207A0BULL, 
            0x225812869192ED5FULL, 0xA6538FADFD4C44B0ULL, 0x225307BD8F79D578ULL, 0xF6D858A59B2FE7CAULL, 
            0xA4374A9FDE6B86BAULL, 0x57B6E8D5A223E766ULL, 0x8AAE8B9F30FCF00AULL, 0x7D5864F3C807F944ULL, 
            0xB05FFA256B0C57E8ULL, 0x981789A4685D6BBEULL, 0x0CFAA69D9C9645CBULL, 0xC627EA20DF51EBD6ULL
        },
        {
            0x9637F76D21990FC6ULL, 0x326C6F0705008EECULL, 0x018D30874F24B502ULL, 0x593DB425547ABE15ULL, 
            0x58CADD32954A43A0ULL, 0x550A341EFB6236E6ULL, 0xCA2FDE3B08E746CCULL, 0x0C70F36705571602ULL, 
            0xC0D20E4BB3C33599ULL, 0x951B22775ACD210EULL, 0x592EACD7E1A25373ULL, 0xEC5F6A135BB25E47ULL, 
            0x9BDEAC2DD08BEFF2ULL, 0x407863D8954D5E30ULL, 0x997775EFD5DA8040ULL, 0x116DC5D256CBF884ULL, 
            0x2BD86D18D776715DULL, 0xD954F37E31C183F7ULL, 0x33054CA46C57BE50ULL, 0x73F6970FA3FF6267ULL, 
            0x56B880ED73A9C1F5ULL, 0xA2EEDEDF2278D9D1ULL, 0x7355509753935DAAULL, 0x2AE776757ABE2A5AULL, 
            0xE9BCD5DC927C3754ULL, 0x00AD8C097C487D12ULL, 0x4865959405FBBA56ULL, 0xDA81FBC8508086FEULL, 
            0x583E5D57F152D9D5ULL, 0x3001AA5AD2C32BD2ULL, 0x80107833F7495850ULL, 0x6DFF8E21A84A7E78ULL
        },
        {
            0x777622AC1ECDF44AULL, 0x03091C391B46AE66ULL, 0x6288C7DC8CCE4B5CULL, 0x16A3784C911A5AD3ULL, 
            0x82227ED7663D0F81ULL, 0x7BF18278FAACC147ULL, 0x7BDAB72A6C9869D5ULL, 0x2A1999FC49B16F95ULL, 
            0x05A0F71ED6A81401ULL, 0x6CA7A81676416765ULL, 0x69B7BCAF555AC72BULL, 0x4B35AE66E450BB0FULL, 
            0xE519FE6BC1E00511ULL, 0x45C3C9044348D90BULL, 0x442CF031A04E5BE0ULL, 0xC1A72D88BCA0AB46ULL, 
            0x24A3E18B30D3E75EULL, 0x77CE3125FFC0DD62ULL, 0xA8C3E323C26097CEULL, 0x867F024515A2D023ULL, 
            0x92EB113BF4BD1AF5ULL, 0x165767E5072C8ECDULL, 0x243E14369448BD18ULL, 0x9D056303E7ECF293ULL, 
            0xF928B52CD8408772ULL, 0x48DD676D9D2D8891ULL, 0x652E9D0D44143016ULL, 0x9F64C0943DA03C72ULL, 
            0xD0DD91C694EA5372ULL, 0x5103BF2E8024B9BBULL, 0x2718EC7BC523FCA6ULL, 0x325265CC870C5D3BULL
        }
    },
    {
        {
            0x0D5A2B3120E4AA79ULL, 0xA1A0144BD2E8DDF5ULL, 0xB372C39D0C00E5A5ULL, 0x7688BF2C4D06D938ULL, 
            0xFBFF6747593C3150ULL, 0x521F4E4314C609F4ULL, 0x2E4880C29A9AB162ULL, 0xFF4A995F3EB66EBDULL, 
            0xD993F5AA5B759245ULL, 0x8EE8CF1001D65641ULL, 0xBF1A3AA4ECBE1878ULL, 0xDC0084B2E2D9B00CULL, 
            0xDF54B7192BF4322DULL, 0xCD4E7BBA7EBC5F00ULL, 0x46AE43F3A590CBB8ULL, 0xBBCBED88CEE72702ULL, 
            0x55E5D645BDA64DB1ULL, 0x2958008BB893A989ULL, 0x90301659F1F9D074ULL, 0x0D1A853797E422D8ULL, 
            0xCBFD22D56FECF997ULL, 0xBFBF2B99F6B74D2EULL, 0xA8E1B867712B805AULL, 0xB0B29071EDE4BA3FULL, 
            0x36F26FDC87DC258CULL, 0x49D01AA87758A169ULL, 0xBE6031E06D4B067BULL, 0x70C8DE3566CB8E75ULL, 
            0x1FC7E0B33A752253ULL, 0x874ECF34B0F46408ULL, 0xF800BC1C19FF0644ULL, 0xA259BF44DFC80264ULL
        },
        {
            0xD2E1E93A7AFFB62BULL, 0x524BD1C6CB901143ULL, 0x7FF8FCB3F18C0F8AULL, 0x1BCC8C9CB1F34CC9ULL, 
            0xBE5F4A78C9D07D75ULL, 0x2FC224FADEF28E17ULL, 0xD759CD2EA0C3C15CULL, 0x521DD0149EB8AB88ULL, 
            0x63069837122345C4ULL, 0x8974680250DF7514ULL, 0x501847CD5F36BE09ULL, 0x8B32AD8D4684AE36ULL, 
            0x2EFD6A939D59DCEEULL, 0xF3756E512B88C823ULL, 0xB6CF005F699763BFULL, 0xB20CFDC26DCE7C85ULL, 
            0x7376AE370C59F627ULL, 0x980B09AEDBEA6370ULL, 0x3D82FAE56917CAAAULL, 0x4ED2A48CC6C64E79ULL, 
            0x0C41F0EE080C347CULL, 0x1E9CB8E804741D06ULL, 0x6F423B430DC113AFULL, 0xF06200C3B9DBC1BCULL, 
            0x8B086A4348F9ED11ULL, 0x31F263FFC457540BULL, 0x69AB7D864FD3062CULL, 0x27DE6C9E600079EDULL, 
            0x02709A03EB850FAFULL, 0xB0D57CFCEB3D90D0ULL, 0x9635860E978E9645ULL, 0x4A0A55D626DD20FBULL
        },
        {
            0x9C9BF729918A33BEULL, 0xE476368E473C5285ULL, 0x6153ACA0F591FA5EULL, 0x78CC1D9485102D61ULL, 
            0x66843E74EFCDD878ULL, 0xF7B958F65452C352ULL, 0xE6998EEFC8893D51ULL, 0x01B898159058EDB2ULL, 
            0x7C5B1363F1897183ULL, 0xD024DEF79ECCC549ULL, 0xBDE880E867665C2BULL, 0xE71638A9308EDCC1ULL, 
            0x321EB6EF30DCB6ECULL, 0x5A144F34899F577DULL, 0x2CE5A3BF76723A4FULL, 0x84FF61C2EACE003BULL, 
            0x8613BF4D60549F16ULL, 0x4D4DF858BBD5FDFCULL, 0xED8B430BAF3E65F8ULL, 0x846855CAB26892FDULL, 
            0x9F21B97F747D0C64ULL, 0x648026255B6DFFDAULL, 0x363EDDFEBF57F1E3ULL, 0xB72D78D0CA10428CULL, 
            0xCC6667860EF41526ULL, 0x5B606A8D5A4A11F4ULL, 0xA89063DA59308E78ULL, 0xC66852843329895AULL, 
            0xFC5BDBF2500A48D3ULL, 0x322FE17437F04CB5ULL, 0x70379C5130B53E8CULL, 0x1A1C21A295F03664ULL
        },
        {
            0xAF429B1C7E22550BULL, 0x3239EA371EA4F8E0ULL, 0x710FA31E900B7E17ULL, 0x83B4A5071570F986ULL, 
            0x3BE82E7F5D908EBEULL, 0x98020E639A429D69ULL, 0x8DA320A56FD8D614ULL, 0x06BFAACCB399028FULL, 
            0x1C0D18F235BA5345ULL, 0x94EBE9332ACCF288ULL, 0xEE48EAE7E7E026D7ULL, 0x7D55A9856FF47B5FULL, 
            0xBEDC70D29D1B8047ULL, 0x66271CAE81303E5EULL, 0xCFEB02EC0CF30420ULL, 0x88C4121E035F4CD5ULL, 
            0x6539C1871DDDA005ULL, 0xB758405F3B4DE7F7ULL, 0xE8D8821C6B4DF945ULL, 0x7E95F06E6923924BULL, 
            0x7C519F85ABABD040ULL, 0x190D80E2BCE95038ULL, 0xB0C77DE77AECA740ULL, 0xB4D818BED2616B13ULL, 
            0x27A327BCA562BEB3ULL, 0x08AF0271D2F4BD1AULL, 0x9192F74CCB4DC042ULL, 0x1C84CCF6334179EEULL, 
            0xB0D276014B782E2CULL, 0x55B74291773C4395ULL, 0x1EDDAA16975DE8B1ULL, 0x728DAF07B59B6B46ULL
        },
        {
            0xA2BFDD86481B8150ULL, 0x9C6FF9180049BCF9ULL, 0xC9261C9862701988ULL, 0x44E3AAA368C02202ULL, 
            0x9AFE7AEAD0C198F3ULL, 0x493CBAA50B2DDCADULL, 0x96D362CE43C3943DULL, 0xD4F27E1C354C5D3EULL, 
            0xE91C3721ED17D9BFULL, 0xA6BA44EBE1441E44ULL, 0x85449E53DE2E75ABULL, 0xBE0C3DA4FE9C7341ULL, 
            0xCD21C6B322735072ULL, 0xEE908E415C760504ULL, 0x191B4D4E1CC1AA3DULL, 0x70F369DF2B2771E9ULL, 
            0xE5AE1B5BF9D07DA1ULL, 0x1899D983AE278FE2ULL, 0x1CC3B0B1891AF25FULL, 0x6DE3C78DD31982B0ULL, 
            0x07EA7D174C51888DULL, 0x4ADA4F32786B9276ULL, 0x3482527F92269AC5ULL, 0xF5250606C7312F3FULL, 
            0x025702C93EAB86E4ULL, 0x64DFC6761F43A381ULL, 0x4143E3DA39E6A16BULL, 0xEA12E077028B92B9ULL, 
            0x1C1198C5787CA49DULL, 0xAF644B4CF327BACEULL, 0x4D94F490C8EDE2F8ULL, 0x02F80D17BFC26DADULL
        },
        {
            0x4AC7F7333EEDE673ULL, 0xDEEE26627CC52385ULL, 0x3E2EB028FA49445FULL, 0x85C72B58BF8ED8EFULL, 
            0xA7507FF8CC1BA3DFULL, 0xF2F91BB84DBE6FF8ULL, 0xD41582CAB2C7AF8CULL, 0x9C24F3E7D802FAEBULL, 
            0x85C6A16A9668D259ULL, 0x1A927400A9F4A5B4ULL, 0xA737C0BCD3A7F408ULL, 0x0D6499D011962E73ULL, 
            0xC46999301FC258CDULL, 0x38BC84A43F66B0CEULL, 0x8DAF1B14B3F80CAAULL, 0xB7B5065E53C878F4ULL, 
            0xE0B3BD7DB9C2E79EULL, 0x4DEA482E2D6A75D7ULL, 0x2A49DE363B8D8B27ULL, 0x935BE4D13FE8CA45ULL, 
            0x3CD050A15B5EAB7FULL, 0x4DD30C580B3857A0ULL, 0xB5283F92179981DDULL, 0x5237044D93C80264ULL, 
            0xD910369F30F8580EULL, 0xFAE8EC5BDC7C52CCULL, 0x3876BC95DD5744C5ULL, 0x2B0E3868EFA0C193ULL, 
            0x95971820A228FA07ULL, 0xAC1E473FADC8B466ULL, 0xE75700D61CC384F1ULL, 0x157EF4A82CBD6794ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseGConstants = {
    0x33C1BC8A52C6BEF6ULL,
    0x9172FD2A618EED77ULL,
    0x89394AC16CBC1FF1ULL,
    0x33C1BC8A52C6BEF6ULL,
    0x9172FD2A618EED77ULL,
    0x89394AC16CBC1FF1ULL,
    0x0B61F59ABC10A390ULL,
    0xD0E5215EB7B6F4DCULL,
    0xAC,
    0xBE,
    0xAD,
    0x1A,
    0x90,
    0xA5,
    0x84,
    0xC9
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseHSalts = {
    {
        {
            0x420F42C15487C53EULL, 0x1A311B0A9CF97E94ULL, 0x4E5F36CEE0243272ULL, 0xA60B63535A515C85ULL, 
            0x60B28482CF8CB972ULL, 0xA9108B66E3B2F1D6ULL, 0x0D9DC5B871A9BE5AULL, 0xF21C3A611FD28718ULL, 
            0x6D53A8C50E02848FULL, 0xD3C4A123794802B0ULL, 0x74D7D5B067F441E0ULL, 0x11BBF27D6BEC6968ULL, 
            0xA096CE076F2643C8ULL, 0x28EAE6BB379160ECULL, 0xF649A06D3D422FE5ULL, 0xFBD703CE89D0CFFBULL, 
            0x7A87094B9A9B5896ULL, 0x8EA7F7B8FD90241EULL, 0x5F37793366E69CA1ULL, 0x7A4F681FD80AE3B1ULL, 
            0x97E2BC6B6F2188A8ULL, 0x5917A662DBDDD4D2ULL, 0x55AED67D65904492ULL, 0x343025E2EA2B0BA9ULL, 
            0xB8768D8163092BE4ULL, 0x13AEE20FBC5D93ABULL, 0x2A4B6C41442833BDULL, 0x1817B9680842960EULL, 
            0x40AD423E850C7233ULL, 0x41A75130C36AF4C0ULL, 0x95E8E7AEA6C3A059ULL, 0x7E6F10E04B64712CULL
        },
        {
            0xD3D02BAB5A7DAD54ULL, 0xC92CAE34F0C14356ULL, 0xFE42FCA6AB7301F1ULL, 0xDFECC0415123A14DULL, 
            0x3DBCD15603DC86EDULL, 0x03C66E6D491CDDE4ULL, 0x1EF7AC1BE8C01C7CULL, 0x0FF5275F11AC91D3ULL, 
            0x67551138705F1CFAULL, 0x5B06DD1D7A70856FULL, 0x3574EE116C138F45ULL, 0x1947EDDEA8FBF269ULL, 
            0x2C68B8B964F93AD4ULL, 0x5460E6E122468CFFULL, 0x76A88CF63B8B1A88ULL, 0x5AF74BD2834F736EULL, 
            0x2DF27389CAE780D1ULL, 0x7F82C03BA276AAE3ULL, 0x890722FE69152700ULL, 0x969FDAE70D9FF2D7ULL, 
            0xE32004ACEA7D9A43ULL, 0x91E8F255BE15738CULL, 0x74320A483630ECC5ULL, 0x9C7E90ECBACEE405ULL, 
            0xCB65F1EBF5390080ULL, 0xEE9CAED13B4620A4ULL, 0xE4C8A6008D31F802ULL, 0xE80CE31FA27D4C77ULL, 
            0x0085AC9B5CAE2B86ULL, 0x228F6EBC7A44DC67ULL, 0x1937D6447F7662B2ULL, 0x06D358093BF63997ULL
        },
        {
            0x70CB2455606072F8ULL, 0x3C6575AB4CE1CBBDULL, 0x1F357BB7D5671F9FULL, 0x897D67C5B5DBB07BULL, 
            0x90774F8A2AFB5506ULL, 0x55D76DC4CD3A0CD0ULL, 0xD291237881184A28ULL, 0xB48D212A3251E919ULL, 
            0x31ABAE547FB24D53ULL, 0x5526E163EE79A111ULL, 0x5CFBA12A180195EDULL, 0x192FFB9BF3BFEA8EULL, 
            0x493558904F69F99CULL, 0x9624178993B474CDULL, 0xC95284FD41CF2270ULL, 0xC469C38979355B7CULL, 
            0xD9769578143D7E5BULL, 0x771B8D486CBD170CULL, 0x8147FCADF85E54BAULL, 0xDE565EC03AA77541ULL, 
            0x12CAF416F3D1416EULL, 0xDB72CCEB77133829ULL, 0x33B16225D6709672ULL, 0xC5ED1854B3185460ULL, 
            0xD519E966493E2771ULL, 0x7D37E1BFCCF105A1ULL, 0x2C15F463C0B79EA2ULL, 0xDB796733001F2A61ULL, 
            0x1AB77621362926DCULL, 0x50EE76AD6FF11AE5ULL, 0xCAF5807544B5FB34ULL, 0x85DCD8963411AD5DULL
        },
        {
            0x77C276ACCECD335AULL, 0x9C804D828FCDD5DEULL, 0xDE8513A3381B2A27ULL, 0xB2640CFBE968E6B2ULL, 
            0xDA1EB67894FB91DBULL, 0x9D60604691E933EFULL, 0x304A5B9A2AB46ABFULL, 0x7C412394EDBA315FULL, 
            0xFF43FE20D359E564ULL, 0x961A9B98DAD98D8FULL, 0xC19B042BFEEBE730ULL, 0xA81959B2DC80D3C7ULL, 
            0xBBAB2DD7644BD0A2ULL, 0x014D396365434931ULL, 0xA3D4FCAFEA8D1DAAULL, 0x102AA01181E27E5CULL, 
            0x6B8DE983DDCD3910ULL, 0x140EA5AE44135794ULL, 0xB22613C67ED81B7AULL, 0x51360A90D589A8C2ULL, 
            0xF2ED08FFEAFD9F44ULL, 0xFC6DD8FB66B89B02ULL, 0x6D8E19E2D9F905B0ULL, 0x0D632BBE2188D91DULL, 
            0x405699A2BD7CD456ULL, 0xEDBC97B7E241509FULL, 0x0894171B1B1645C1ULL, 0xF8DAAD1E599168E5ULL, 
            0xADFA8B94B0B028C6ULL, 0xF5F30F1F9729461FULL, 0xB84EA8306CE677D4ULL, 0x5736080A7C2E68C2ULL
        },
        {
            0x8E52A25775DA2685ULL, 0x63FF77723990C408ULL, 0xB1916A11DF7C1764ULL, 0xC88CA30CFDE9D03EULL, 
            0x056420D79FA3F099ULL, 0x64BBCF8D3FE12082ULL, 0x811CE10A6A9E3ADCULL, 0xC0468848DE59CCA1ULL, 
            0x1D40DF5045A917EAULL, 0x8F5A6990217E4159ULL, 0xAEF4015B6912173EULL, 0x5EBD32CA7652ABA8ULL, 
            0xC44D3583DEC05769ULL, 0x8E672F2AA9A89C27ULL, 0x7B9E09DBC7B52C0BULL, 0x1C1B58223F282726ULL, 
            0x1D9FC1D4BC0E3A4DULL, 0x4AEA7476468366F8ULL, 0xD211FAEE44D8474DULL, 0xC6D7B30250A497DDULL, 
            0x3EC7600F5FADB7A9ULL, 0x4FA0307292836260ULL, 0x5CAD738078B4A82EULL, 0xCC96CBF4AE6D609CULL, 
            0xCCD29E54203FB482ULL, 0x9219B5B29F5BC822ULL, 0x9AC693E4F2311E3FULL, 0x9076A9F9796E4B6BULL, 
            0xE76589A5C72C8CBAULL, 0x4DAFA65B71E05CDBULL, 0x1E75759C3E8F9B5CULL, 0x536112270E39F265ULL
        },
        {
            0xD50BEC239280EE0BULL, 0x2D8EF0CBC1E76726ULL, 0xC821EB1534AF6A17ULL, 0x6A67341139A32E09ULL, 
            0xCE8C4CCC5D8AF994ULL, 0xC63CC3245F3657FFULL, 0xCE3512454652F1BAULL, 0xFFCD1B82C2482FBBULL, 
            0x1458DD7F17FC5CACULL, 0xDE824222C3F7BC6BULL, 0x017EAE7A060232E6ULL, 0x8AD63BF564691FB7ULL, 
            0x0C814C49FC141B27ULL, 0x3E1F0B949FF56795ULL, 0x750BA03FA29A0225ULL, 0x37C834B90BA0EEA8ULL, 
            0x6B2C87F0083E3424ULL, 0xD42B8BEA60111BCDULL, 0x490B3BF6C6387BE9ULL, 0xA33A021D9B3BEEBAULL, 
            0x7BFAFF4D74CA10E4ULL, 0x509806495DD16C4DULL, 0x072B927480C0F25DULL, 0x6ED37FD57B20BB44ULL, 
            0xA3CD30C902592CB9ULL, 0xEE77A888AA83D8EAULL, 0x02ABAD1EF6974786ULL, 0xC46635D54153E69FULL, 
            0x0FE3B8EFAB8A1561ULL, 0xA4C7AD18F6B1DC9CULL, 0xAE6C3AE18B6EE18BULL, 0xB4401563BE2A22E7ULL
        }
    },
    {
        {
            0x56341E7F8114340CULL, 0x8979CADBAB000F52ULL, 0x749BCDA530D9F9D1ULL, 0xBFA79454FE747343ULL, 
            0x38AA793D394EAC8DULL, 0x727E9E23913238CFULL, 0x734EE42BEC1401FBULL, 0x3FBDF42CAF447DECULL, 
            0xFEF683C0F642CFCFULL, 0x04996C6815E12142ULL, 0x075D3F580E0832D6ULL, 0xAE8C8166CE0AD938ULL, 
            0x865E04462DCDB90DULL, 0x23EF9458ADBDE86EULL, 0xFCD38E09AAE202E4ULL, 0x80A64463F13711B2ULL, 
            0x6DBA9588087F1ADFULL, 0x5F6D0150808FB688ULL, 0x567921D8F800C7CEULL, 0xFBBBDA3B0258210AULL, 
            0xC0E98F59D666DB5FULL, 0xD4B637A448B6BEC6ULL, 0xCA3ABCF1D4655138ULL, 0xAE9AF9737F8707E1ULL, 
            0x60038A3CD4BCEFD7ULL, 0xF43048808191AC11ULL, 0x5615CBB71C2EE751ULL, 0xCA8BB937C1EB0D6AULL, 
            0xCF3EC53FBDEC6869ULL, 0x6C639B4292580158ULL, 0x4519A3E52314CE47ULL, 0xA13EFFF60DD2712FULL
        },
        {
            0xA55CF7B91E4A2648ULL, 0x6EF8EB70BB67A967ULL, 0x4AF14C45503E872EULL, 0x69A3107795D5FBE2ULL, 
            0x6B9E37535F09163DULL, 0x3FD19244730D5BC3ULL, 0x74790AF2AED6BC66ULL, 0x7617C20A14CCCEBCULL, 
            0x381E3E51530FE45DULL, 0x23C25E8F45FAAD08ULL, 0x5E5EFB947D987BC2ULL, 0x282AB9C1F6DFE812ULL, 
            0xF15547900DDA2AC1ULL, 0x5328B586A5C8CA8BULL, 0x7772C63F9D34F33EULL, 0xBE748C5EFAD22242ULL, 
            0x64E58576DB22B0F2ULL, 0xB561B8FC50BE970AULL, 0x1F4AB7D7C7F4A3B7ULL, 0xCC9DC841A6AD7F22ULL, 
            0x67A0EEC8671E00D5ULL, 0xAC40DBA00E85CDC9ULL, 0x22C17BF0B0EAFCA3ULL, 0x86FA272B9FD79EE4ULL, 
            0x56C905B0BDCEFDD0ULL, 0xB7F7364A0E8B9C8AULL, 0x4CB2740EB4D34157ULL, 0xB3006199924072E2ULL, 
            0xA36501498A21DA0FULL, 0xB7E2283D1F7F1AEAULL, 0xB4499C2A31F52A7DULL, 0x93312099A2038524ULL
        },
        {
            0x78EDD367FF550CB5ULL, 0x6FB6BDD9069498E0ULL, 0x9167DB9EE195B69CULL, 0xFA1D885A39A44BFBULL, 
            0x52A846291A5D4383ULL, 0xFA6464FA47E50185ULL, 0x2013DE925B52CE5AULL, 0xFD34CADF5F14170CULL, 
            0x1C0979F85706F22CULL, 0x03F3A8ED03318A5EULL, 0xE78A78791D64EE52ULL, 0x2E89A224BAB2526FULL, 
            0x37C3EE67941057ECULL, 0xE697FC1428205064ULL, 0xEA148037876CAFF8ULL, 0x4CA00E566EE10AEDULL, 
            0xC3DD633CD92E7232ULL, 0x2750D4058D9D16BDULL, 0xABD2F85A0D965F14ULL, 0xD6C51A29011FE3CDULL, 
            0xA02945B005AD8415ULL, 0xA037C674B64BF19AULL, 0xA1080DF5B7C396EBULL, 0xB9FB8E3798D3ABE7ULL, 
            0x3741C0CAF3615035ULL, 0x773F0D1826CF2102ULL, 0x0E8E724FD119A794ULL, 0x9109980C4BEA74FFULL, 
            0x4818710B0197EFC8ULL, 0x1D7C409995146551ULL, 0xEE8674FD5FF34A54ULL, 0x6FAC8652844411E8ULL
        },
        {
            0x649DFC2532AAFE8DULL, 0x8C85A85BB99CF2F0ULL, 0xB4B6A086ADDCFD0CULL, 0x8E7F4D067585AD08ULL, 
            0x2A94C061FF767B45ULL, 0xE5F6377814F145C2ULL, 0x996895AD101A06C8ULL, 0x500DA84BAE2558B5ULL, 
            0x3909BD1AF892B440ULL, 0x125BCF76F8B54A3FULL, 0xC9FE8F6BAA52BCF0ULL, 0x089F3079B5F9692AULL, 
            0xE4EFA5AE9F2E0057ULL, 0x0E9E06F99619524AULL, 0x5D3BA4ABCD5278D1ULL, 0x9397D6AA2D831C53ULL, 
            0x331CC2CA233F2100ULL, 0xD6DA6BA1D17F6E87ULL, 0xE593D88D66039568ULL, 0x5769E388989378D6ULL, 
            0x328A5D3AD931B90FULL, 0x38F17DE5BBD89AA2ULL, 0xBF34720F3549E939ULL, 0x626A4A09FBFAE1F5ULL, 
            0x0A7C22FBD14A0333ULL, 0xBD4F00F3BCB82C6EULL, 0xE2363ACDB59A7D74ULL, 0xD4FA6043586F35E5ULL, 
            0x2EE1EDF66FC00EB1ULL, 0x2FB7F57CDF0B3492ULL, 0x63C141CBCCAF54E2ULL, 0xB153A267ABCB168DULL
        },
        {
            0xAF1699C6401932C7ULL, 0x6E304D3A8950C137ULL, 0xDFFE30F6EF8F5E13ULL, 0x6B14C57D9B4AFCE4ULL, 
            0xE2F41D267AEEFD5EULL, 0xEE77323841798E04ULL, 0xA96B4D944EC342E2ULL, 0xC4C3D88CCBA3C27BULL, 
            0x0D0FC2C99D1510ACULL, 0xED44213FA6FF6209ULL, 0x2228F7224C123E22ULL, 0xD6AB2B5106F8FD67ULL, 
            0x3C3854009737B6CAULL, 0xA1083B9910A98603ULL, 0xB5596A9AA9B27680ULL, 0xED9742A8153DEB12ULL, 
            0x12DFF65D8117B368ULL, 0x224F19BC17464CDDULL, 0x6579BA0F61EDD5BEULL, 0x1378AA1AE6FC0B89ULL, 
            0xB5757D1123B0DF40ULL, 0xF6D99C268532A167ULL, 0x9340DB13B4E3547FULL, 0x43C85A8002E6E92BULL, 
            0xF4EF05EB3A884109ULL, 0x2659CF920C211A20ULL, 0x02B981C2B4250E4DULL, 0x05B27AD9B60950C5ULL, 
            0x78C2F54A9A276C7AULL, 0xF3BC8AFE25A2E548ULL, 0xD87EF1B01AB62C82ULL, 0xA1CB9793F13109C6ULL
        },
        {
            0xB2C652EBC87113C5ULL, 0x731893C9827C9E41ULL, 0x0D807A764717E822ULL, 0x2F25B191CFD83991ULL, 
            0xD829E5C8F8EE165BULL, 0xF9820941F3B5EB4CULL, 0x9EE19C6A06E9A4F4ULL, 0x09EA909B0AD2881CULL, 
            0x7D51B29070C90B98ULL, 0x11F1D6EDCC45CFE5ULL, 0x127FDE1B9884F3D1ULL, 0xA2734A6C778B9026ULL, 
            0xB459CEF9B8D80D51ULL, 0x63EC366C786489BBULL, 0x45F7105DFED1FDF8ULL, 0xF436809CD61A6ED0ULL, 
            0xC0DC55F572B2EA0BULL, 0xB496085D5706C65EULL, 0x3C9B1E548A15BEB3ULL, 0xCE84886D81542C57ULL, 
            0x7DE40D7F35386A4CULL, 0xDD8BE4468BAE1308ULL, 0xE1C74DE3908919D0ULL, 0xCF326420F8228ACEULL, 
            0x5959101D98EFB37EULL, 0x261A0807070FE149ULL, 0xA81909D7EDA40A99ULL, 0xD6C0FAFA115F0735ULL, 
            0x1E3E6FA843218005ULL, 0xF093A9E6A5027B3EULL, 0xE495C6E2159BAC75ULL, 0xCD29EC20FAD280A0ULL
        }
    },
    {
        {
            0xB9850C682D16F13DULL, 0x664C5693C3BCCDE2ULL, 0xBC12F17DAC32AB0EULL, 0xAE62245EA9285D4FULL, 
            0xB1968B58ADAF6F0CULL, 0xD974F53EA103C6E5ULL, 0x04968C87B643DDE9ULL, 0xE7DF7B727C624932ULL, 
            0xC0140EB56E95E10BULL, 0xF44849F9BECCA929ULL, 0xB9628C21A33B2464ULL, 0x6C7B8CE95B7E6215ULL, 
            0xF0D92C15F5E673DDULL, 0xFA59A50E6943335BULL, 0x93A6ED2F5477C6A4ULL, 0x9DFA18A933113236ULL, 
            0x7E6DCEE5D7116D41ULL, 0x4EB6AE8A5F50EEE8ULL, 0x5E26D3DCD12C847BULL, 0x30FFAD9C4E71D50DULL, 
            0x17B396497CE9E4BDULL, 0x4A9ADECB010D13C3ULL, 0x09EA26660471F548ULL, 0x55BF63120225CB2CULL, 
            0x336624CE3036AED5ULL, 0x69D33B8401DC077EULL, 0x01087D1D3491A839ULL, 0xEB321D1EACC6FF7AULL, 
            0xE6B028A4F22BF1D4ULL, 0x10C4470831CE2FB3ULL, 0xB68C510F4B0FDA7DULL, 0x140CBF45D0B908F2ULL
        },
        {
            0x4A6254AE8C56A974ULL, 0x034EA15F8773F2CDULL, 0xE89E39D30CB91E9DULL, 0x32A5B7E4558CBA70ULL, 
            0x2B3A30A1AB8BF683ULL, 0xF96EE6C558074FC7ULL, 0x4C6BAE4919AA1DB9ULL, 0xDE406815EC1D5DB9ULL, 
            0xB20E6453E70573CCULL, 0x06AFCECF3C3BADD4ULL, 0xB7B875A3C3CA83F7ULL, 0x63857E745A53D86BULL, 
            0x71A4C654ED568B67ULL, 0xCEB439D7516DBBAAULL, 0xE5F6124A4DFD440FULL, 0xFBCDAE44D57AD540ULL, 
            0x568BBABF8F1C4A1DULL, 0x7BD56DDE112FE537ULL, 0x54B17AD187372238ULL, 0xFBBB9A05E8B71CACULL, 
            0x671BC5ED9B326AD1ULL, 0x686F096BC6F341B2ULL, 0x827A472DB0476D56ULL, 0xD949DB4C2E5F5A1DULL, 
            0x23230F5366E47B9BULL, 0xB5DFCDE015DB6413ULL, 0x34F6D3578DC76A6FULL, 0x3D9E8097929D73A2ULL, 
            0xCD13F9042EBCE2D7ULL, 0x6D8D4ABD60323738ULL, 0x89F7D32A42D51B46ULL, 0x9906054D714D1F5DULL
        },
        {
            0x25FBE272DDD3C067ULL, 0x16F8B926FB23206BULL, 0xB7D7F00251E75DC3ULL, 0x3C05BE68E984CFFAULL, 
            0x82CE2E810EDE0843ULL, 0x71F5FCB94DCBC248ULL, 0xBADAAE029CD8E11DULL, 0x63397F82C34DF879ULL, 
            0xB4F6EB23FA361CF3ULL, 0x2B91BA66CF4B0770ULL, 0xDC23A15CB676D1CDULL, 0xD401B92ACFA4A299ULL, 
            0x21703083BAFE0901ULL, 0xADDC3ED499BF28FCULL, 0xE8EB935B0AF2B9D1ULL, 0xB173A1301C0E19FCULL, 
            0x93F12000E5437395ULL, 0x5265DD76CF91451DULL, 0x895F69C75C55D5CBULL, 0x91FCBAFF7D51F0AEULL, 
            0x6013FD52F67D3AEFULL, 0x1E410E4912CAFCBFULL, 0x21EDD454638D928CULL, 0x7CCAAD727D6FBC35ULL, 
            0xF3A1623A29F2DF8FULL, 0x868EAFDEF56941AAULL, 0x1B157CE5BAD25887ULL, 0x9344ED78C692D024ULL, 
            0x8D9C404E4C35DA49ULL, 0x17F630DD1BD187C6ULL, 0xE4CA3D58678CC354ULL, 0x4A865ECAD26BB5C0ULL
        },
        {
            0x9D569032D4FADAC6ULL, 0xD8097A1504B1CA17ULL, 0xBC75818905F2AE2DULL, 0x65E96C6BAF7300EEULL, 
            0x27D95827B28C4BB0ULL, 0x9ED5A169666521DEULL, 0x9DCD5595AAE73588ULL, 0xAF481518F61D892DULL, 
            0x22847D27981AF83FULL, 0x54884669C9609A82ULL, 0x97675D4F7630967CULL, 0x877103BEA069663EULL, 
            0xAD4327E98C7A87C5ULL, 0x260D6DC5E8BD1F77ULL, 0xAA63DE4016A50500ULL, 0x8D4731D8C7C382AFULL, 
            0x9F6EE1F19A680FB4ULL, 0xF6B6564E1482C34BULL, 0xBA0E656006FD1C9DULL, 0xBA50256708FA74D6ULL, 
            0x9D264F3817914006ULL, 0x5D34FB5E43476100ULL, 0x1542A8DFE0184850ULL, 0xAB588A3B04833314ULL, 
            0xB547F7773DD3954CULL, 0xC0596F5832533F62ULL, 0x4D5980E8939F7572ULL, 0xB0FF203F4AAB4D1DULL, 
            0x68F488D74E18AFC5ULL, 0x8004A104E2E93286ULL, 0xC981E8B4826C86DBULL, 0x6C8034D0E15AD653ULL
        },
        {
            0x52A943DE79CB7CDEULL, 0x7F7173AFF4C1BCA5ULL, 0x651A1F55C00E15BCULL, 0xA49A0208AA4204F2ULL, 
            0xCA9E061C920F23ACULL, 0xDD503D7C18F942D3ULL, 0xE9CD9680DB75323BULL, 0x67A37E744DF9629DULL, 
            0x8E25DD2F0967C08CULL, 0x95B9DE93949A6A0CULL, 0x6A39355A7353278FULL, 0x29B6FB26E82E4DAAULL, 
            0x16A981C41A94AA71ULL, 0x325B7EE39F1D0A59ULL, 0xD5584868AD142C8CULL, 0xE281D471A7186F7FULL, 
            0xA26905B707681EC8ULL, 0x5058918709F27303ULL, 0x0A523F7513728435ULL, 0x81B474035951FA77ULL, 
            0xECBA9FA7AB701D02ULL, 0xFAC1EABB7B56660BULL, 0x0F0FAF9DA13CD734ULL, 0x0A95D86010CDC812ULL, 
            0xD2568CC80B34272DULL, 0xD60718FC6B3D95BDULL, 0xADA7CBDCBDF2E8CFULL, 0xB0CDDBCEDF9BEC67ULL, 
            0xF7577CC986D79FF3ULL, 0xF0E0244432894E25ULL, 0xA989A27BAEF80EC6ULL, 0x08C1A030C4BE3C5DULL
        },
        {
            0x141A61AE84FB7E18ULL, 0xC7DAC884C043902BULL, 0x2C5B86273FB55E25ULL, 0xED0E17A847E6B6FFULL, 
            0xB60929CF79DF525DULL, 0x5C8B5EFEDACDF845ULL, 0x5DBF22D8175BD0D3ULL, 0x85BC6F09CFB2A371ULL, 
            0x5A48F27F6FAFCE03ULL, 0x1EA5808E91B7646CULL, 0x396DE8B8041FE8CDULL, 0x2D7A1C0DA7B78D32ULL, 
            0x5F03080D89BA8DE4ULL, 0x0876CBB1A949C39DULL, 0xCF44763E878120CCULL, 0xB5BC8AC6CA4ADD8AULL, 
            0xDAE351CB2662F5D2ULL, 0x1A8A7BA5A7ABF7CAULL, 0x8AE5BD77F0496181ULL, 0x062844592CC50766ULL, 
            0x853297B95DDC52F6ULL, 0x9434D79E1D102BAEULL, 0xEACB716F4D9F95F1ULL, 0x09BAABB2729DFB71ULL, 
            0xAE3BB4B96CCA3B44ULL, 0x2665B8EDF82A1EBEULL, 0xE3BA362CBDBE393DULL, 0xC69E70A060D2F1F4ULL, 
            0x8FD002902556BFB2ULL, 0x17BB4163E736DFBBULL, 0x8F79768203D45841ULL, 0x2217633D7B70EB90ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseHConstants = {
    0x51B4484747A02B11ULL,
    0xEB83A9379F1D2F21ULL,
    0x6965DE596164E3C3ULL,
    0x51B4484747A02B11ULL,
    0xEB83A9379F1D2F21ULL,
    0x6965DE596164E3C3ULL,
    0x03500A29DE31F2D3ULL,
    0x7BB5BBEE960D3E1BULL,
    0x52,
    0x5F,
    0xAF,
    0x75,
    0x70,
    0x51,
    0x42,
    0xE5
};

