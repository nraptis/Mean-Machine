#include "TwistExpander_Mothallah.hpp"
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

TwistExpander_Mothallah::TwistExpander_Mothallah()
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

void TwistExpander_Mothallah::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC59E669E206D5E42ULL; std::uint64_t aIngress = 0xE6F36B8B8099A083ULL; std::uint64_t aCarry = 0x8B5726405DF0EBD3ULL;

    std::uint64_t aWandererA = 0xEAA55F7FC4E3B6B0ULL; std::uint64_t aWandererB = 0xCB9F39AB0A53390FULL; std::uint64_t aWandererC = 0xCB9580035EA25D6AULL; std::uint64_t aWandererD = 0xBC76EE9BB05B54F0ULL;
    std::uint64_t aWandererE = 0xFA7EC3AD9CDF2080ULL; std::uint64_t aWandererF = 0xC12EB19B2F8C9D6DULL; std::uint64_t aWandererG = 0xEAC27D0E09587965ULL; std::uint64_t aWandererH = 0xE515477CD51151D9ULL;
    std::uint64_t aWandererI = 0xADED6D5690C735ADULL; std::uint64_t aWandererJ = 0x858CC18754CC86CBULL; std::uint64_t aWandererK = 0x95AA28651EB95864ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10172154802147982768U;
        aCarry = 12383082245238169165U;
        aWandererA = 14682501054829564929U;
        aWandererB = 11066049553751857918U;
        aWandererC = 12632971530747618176U;
        aWandererD = 12739252126063556741U;
        aWandererE = 17348153857193636816U;
        aWandererF = 11801245910948725411U;
        aWandererG = 16120967918163015225U;
        aWandererH = 10931940591731649793U;
        aWandererI = 11326491691025099450U;
        aWandererJ = 15470184794190578374U;
        aWandererK = 13138901319529035956U;
    TwistExpander_Mothallah_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mothallah::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD46A44B370021482ULL; std::uint64_t aIngress = 0xFD181746C7ABDAE0ULL; std::uint64_t aCarry = 0xC78599BD39692B9AULL;

    std::uint64_t aWandererA = 0xEFC046F49B8FC2DAULL; std::uint64_t aWandererB = 0xBFCEA56F5D3DA9E1ULL; std::uint64_t aWandererC = 0xA73F2A0129962931ULL; std::uint64_t aWandererD = 0xE5C4C13B3D590B34ULL;
    std::uint64_t aWandererE = 0xFC124A16D4388807ULL; std::uint64_t aWandererF = 0xB076E3952B08AEB8ULL; std::uint64_t aWandererG = 0xDD858088C830A073ULL; std::uint64_t aWandererH = 0x996EA85A36AE5071ULL;
    std::uint64_t aWandererI = 0xD3B52CE3F1967DEAULL; std::uint64_t aWandererJ = 0xE1D00041EA3E8AD4ULL; std::uint64_t aWandererK = 0x977CD3EE04EA95DFULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15862578883322570774U;
        aCarry = 16045151566848947205U;
        aWandererA = 12906874249272541561U;
        aWandererB = 12777333161349763178U;
        aWandererC = 13531366169112564059U;
        aWandererD = 9969424466970401537U;
        aWandererE = 11066818791938357455U;
        aWandererF = 10616301695505214000U;
        aWandererG = 16859605422619662358U;
        aWandererH = 11140931534552766407U;
        aWandererI = 10116709494086281404U;
        aWandererJ = 16214542874712315320U;
        aWandererK = 11787842409762913765U;
    TwistExpander_Mothallah_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mothallah::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD4A6ACA1955CBF5CULL;
    std::uint64_t aIngress = 0x9C171C1FB6282DABULL;
    std::uint64_t aCarry = 0xF97E922414C6B344ULL;

    std::uint64_t aWandererA = 0xD59B6F758DB3527CULL;
    std::uint64_t aWandererB = 0x827F91978BE1B43BULL;
    std::uint64_t aWandererC = 0xDD53CD7FEA10918BULL;
    std::uint64_t aWandererD = 0x9245AD0972DF48A6ULL;
    std::uint64_t aWandererE = 0xB19E68DB613FE807ULL;
    std::uint64_t aWandererF = 0xB077D730EAAFE9ACULL;
    std::uint64_t aWandererG = 0xF5C5B65A87D8D256ULL;
    std::uint64_t aWandererH = 0xCEDA0582DF9B5D72ULL;
    std::uint64_t aWandererI = 0x97FE2C1E1A5B79EDULL;
    std::uint64_t aWandererJ = 0xD1B4D4A0ED274430ULL;
    std::uint64_t aWandererK = 0x82F4F1A1E058A516ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneB, 0);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneD, 1);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneA, 2);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneB, 4);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneD, 5);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneA, 6);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    TwistExpander_Mothallah_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Mothallah_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Mothallah_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 22 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1794 / 1984 (90.42%)
// Total distance from earlier candidates: 38044
void TwistExpander_Mothallah::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2032U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 225U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 573U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 208U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 478U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1495U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 616U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 664U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 583U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 653U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 41U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 350U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 207U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1965U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 79U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2030U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1268U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 160U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 899U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1987U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 994U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1314U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 156U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 326U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1033U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1137U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1265U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1005U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1139U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 908U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 937U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 909U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1722U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 979U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 590U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1109U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 955U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2019U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1234U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1607U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 736U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 738U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1177U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 309U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 406U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1977U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 840U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 227U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1409U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 451U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1996U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 476U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 536U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 284U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 659U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1704U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 674U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 556U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1312U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1343U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1432U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1857U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1473U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 574U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 22U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1734U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1854U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 388U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1418U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1388U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1342U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 231U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 468U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1340U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1890U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1043U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1789U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1439U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 17U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 124U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 578U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1730U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1310U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1068U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1838U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1765U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1834U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1943U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 671U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1929U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1917U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1973U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 278U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1111U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1328U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1581U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 949U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1001U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1038U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 336U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 40U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 144U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1602U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1240U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 340U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1526U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 200U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 370U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 732U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1552U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1575U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 402U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1238U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1513U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1697U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 761U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 985U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 6U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1376U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2006U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 83U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 88U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 752U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Mothallah::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xAD02C291CE845748ULL; std::uint64_t aIngress = 0xC3EDDD8985AB9B2CULL; std::uint64_t aCarry = 0x8476260D42A462E4ULL;

    std::uint64_t aWandererA = 0x98ACF7F14A25EFADULL; std::uint64_t aWandererB = 0xC3E8910EDC9313B7ULL; std::uint64_t aWandererC = 0xB85D631866E01882ULL; std::uint64_t aWandererD = 0xBBA2841510836FAEULL;
    std::uint64_t aWandererE = 0x97E7ED10727DD686ULL; std::uint64_t aWandererF = 0xB4CC5755CAC0769CULL; std::uint64_t aWandererG = 0xB769F909A64A6A89ULL; std::uint64_t aWandererH = 0xDC134C681488F9FAULL;
    std::uint64_t aWandererI = 0xE64427290C5EC0D9ULL; std::uint64_t aWandererJ = 0xE4BE06CF2C381230ULL; std::uint64_t aWandererK = 0xFE26CB2D5320E74FULL;

    // [seed]
        aPrevious = 15228607872019785641U;
        aCarry = 11134316704343009899U;
        aWandererA = 10948748317352552343U;
        aWandererB = 15835233824851279201U;
        aWandererC = 17457870885382400369U;
        aWandererD = 9620867739077392189U;
        aWandererE = 15580271885405073869U;
        aWandererF = 14809756378855460246U;
        aWandererG = 11967460348468629449U;
        aWandererH = 15338621692372312641U;
        aWandererI = 11833497320358165595U;
        aWandererJ = 15601843416435290052U;
        aWandererK = 17725575528358695337U;
    TwistExpander_Mothallah_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Mothallah_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 22 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11389; nearest pair: 472 / 674
void TwistExpander_Mothallah::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1311U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5849U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1842U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5531U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6890U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6561U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3965U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2359U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2954U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 887U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 628U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3686U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7543U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 310U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1418U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 19U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1858U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1611U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 583U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 813U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2010U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 740U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1535U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1118U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 112U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2040U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 180U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1718U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1084U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 773U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 108U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 22 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11397; nearest pair: 457 / 674
void TwistExpander_Mothallah::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1093U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 688U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 109U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4339U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4166U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1973U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1951U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7607U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7943U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3294U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6961U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3967U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6978U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6799U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3516U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7162U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 623U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2014U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 240U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1120U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 356U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1265U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 447U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1478U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 555U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 456U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 622U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 41U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 396U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 50U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 35U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 923U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1044U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1068U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseASalts = {
    {
        {
            0x392BD564C148886DULL, 0x61AFD4E6871CBAB1ULL, 0x1101E2FE270A4D85ULL, 0x61BE07A3AC373C56ULL, 
            0xE26BF1E0B6FE5FF8ULL, 0x3163B6DDC8D6E916ULL, 0x4F87276F7829E883ULL, 0x40C94E68A221F576ULL, 
            0x98CCB082E8DD03DBULL, 0x5B2AC1ACF4395605ULL, 0xD7A23AC9E76074F8ULL, 0xE54E2D2F21A8DE21ULL, 
            0xA902B2CE2A9EC4D4ULL, 0xF2684F0F73B7FB01ULL, 0xC505C1CB1AF2B05FULL, 0x252E50A1B9FDBD13ULL, 
            0x167C521AB20DF94BULL, 0xB131C2C8505626FFULL, 0xE156ED34149E6B68ULL, 0x5969C01BAFFE3D64ULL, 
            0x2E8E270F91E4D0DBULL, 0x678807873B1AFA64ULL, 0x935687310B47D543ULL, 0xE6C781E72FEB9CBFULL, 
            0x186026CD692392E4ULL, 0xB96CD33B42183B5DULL, 0x6BC833682C33B6FAULL, 0x8197DF19E0DD0551ULL, 
            0x47A29BAD669EC8B8ULL, 0x8318DCE7C7B0A3BDULL, 0xCE82111FA45B1E90ULL, 0xE06852C9102BC26AULL
        },
        {
            0x47B845C7A89AA78BULL, 0x7AF6AAF4BEBE97C0ULL, 0xE54084012BBCD799ULL, 0xCDE4A15B3B5BAE1FULL, 
            0xE8D68BDBFC6F9C91ULL, 0xFAB12EFC1FC45DB1ULL, 0x6D5E29438F1B29FDULL, 0x3C8E8624C94C0D4FULL, 
            0x6AC70FE9014933F3ULL, 0xF3454925B976F5CCULL, 0xBDC7E041BA729454ULL, 0x47CF7D69FA62917AULL, 
            0x13615965A4EE7EACULL, 0x67D3C7426956804FULL, 0x333CA4A84702F8AFULL, 0x2944969CBB4AEC8BULL, 
            0x096174A0F32B609FULL, 0x418C431752764F64ULL, 0x5F2D64949D5E0378ULL, 0x2240AE34400290FFULL, 
            0x80F7AC06DBD90BBEULL, 0x1509A5BEA0CF5FF8ULL, 0x05ABF1BE2A30007FULL, 0xD149C1C0D8A1D356ULL, 
            0x0CF653A3394A6EB1ULL, 0x5017383BD3733B26ULL, 0x659FB7CE93B2E42DULL, 0xD53B6E60116A6B63ULL, 
            0x24E6E9CCDA333A94ULL, 0x3640AEED65757567ULL, 0x499E9AD84687BF0BULL, 0xCDD598075EDF6CCDULL
        },
        {
            0x6AEBBA29BC4CFE11ULL, 0x659C7678A2F86AEBULL, 0xC174E0A5F8463044ULL, 0xE4E08892F3CD9B09ULL, 
            0x1FC07FACC9DBB242ULL, 0xF0DCA2C19E68BA9BULL, 0xBF15F32067A21C79ULL, 0xE9D5D428B91012ABULL, 
            0x77DA1B048E4A15C3ULL, 0xFBF8DCFC6FCD3153ULL, 0xBDD4F6C6E406618AULL, 0x7259527349BFC29DULL, 
            0xF71A85378E3F5E4CULL, 0x6599447F8616067DULL, 0x946A42FF07DCF092ULL, 0x11101AD19F1FA12FULL, 
            0x2440A00E329EE4AAULL, 0x675F98F8D336589CULL, 0x241AB2EFB1BE8BC0ULL, 0x94C4E428227782A6ULL, 
            0xC3A4CE4551F70246ULL, 0x86F1685D1E17865AULL, 0xB7E1BDC80F3590AEULL, 0xEE5E311CA76BFB98ULL, 
            0x59C2A7B6196F7A23ULL, 0xFB7264046A468D34ULL, 0x64644ED84DB4E3CEULL, 0xE0A060F1AEFC0995ULL, 
            0x16948029721C8040ULL, 0xD00964105EB5AF1AULL, 0xA3A16C076DD180A1ULL, 0x86134A192B17D666ULL
        },
        {
            0x914A55FCB5C5C665ULL, 0xB97504D1374E20FCULL, 0xB376E1E90FD55F56ULL, 0x457C344E4EAB0806ULL, 
            0xE0599B450CD22AB4ULL, 0xB182337201E78F1FULL, 0x0487F52FD9B1D65CULL, 0x2A2F55D0CEFFA6EBULL, 
            0x9F9BDC676639FAC2ULL, 0xCC9C64AD583EACC3ULL, 0x9009EC411E5B2414ULL, 0x4F983A3D4ECCE328ULL, 
            0x22BB8DB2B59A7214ULL, 0x1860413FD3BBA2FBULL, 0x9D8E7C162696A7A1ULL, 0x6C943224459A7487ULL, 
            0x36078AA98625CBD9ULL, 0xC3A72DBC524BBE68ULL, 0x7ABA71902686DB0AULL, 0x4B52396512F42CCFULL, 
            0x8ACD91CA2EB3DA6DULL, 0xB4936856175F2C25ULL, 0x96E6ED2E72D26B9AULL, 0x0846B0DFE3A24839ULL, 
            0x193383F3FD8DD057ULL, 0x2C08740BF48ED3FFULL, 0x32890AE88BD855DEULL, 0xD41D0A382113DD9FULL, 
            0xAFAF10DF66DD2B03ULL, 0xA32817BBD99539DDULL, 0x89C3B4E8F0E8EF13ULL, 0x24A73CBFB1E3ABBBULL
        },
        {
            0x074696C01DA659ACULL, 0x4DD2F748827916E1ULL, 0x07031FE626EB09A4ULL, 0xF3164E9A88569D32ULL, 
            0x5D753EA2CB7AE078ULL, 0xB93363B97965BE50ULL, 0x0BA037576F660348ULL, 0x3BCD1EA935E783CEULL, 
            0x2164B8297A5EDCD5ULL, 0x54F6AB4182A57EF2ULL, 0x86C52BCF0779B426ULL, 0x3539FD370F243E41ULL, 
            0xE70AD43364EC0435ULL, 0x47980C7E30683C7BULL, 0xDF63C3C9EC6BB710ULL, 0xD36B1306BB0879C1ULL, 
            0x5F66AF2549704430ULL, 0x4F6849F0AB93CBCDULL, 0xD6E34D714F02BBE5ULL, 0x0E72F1502E6B86D9ULL, 
            0xCAB77FDC716B7185ULL, 0xFB3734D73CD3FA47ULL, 0xD7008C8385CEE1D9ULL, 0x9DEB7C1324F578C5ULL, 
            0x1FBFDA2716E92383ULL, 0xD4BABE8A0648E368ULL, 0xD4537A068A063720ULL, 0x69FA8010A2286B59ULL, 
            0x95E3F5C6A33E4671ULL, 0x2A8ECF2C87FB006AULL, 0x84B9019AD6EA86D5ULL, 0xA523732F1BA366A9ULL
        },
        {
            0xB636F3C248B8D12CULL, 0x0228CDFCD1A0AF08ULL, 0x029D14331968ED8EULL, 0x1D087AEC91E2B3EDULL, 
            0x08C3E970FC51C76DULL, 0xC7ACDC6289C015ECULL, 0x6C4F4FBC7100D404ULL, 0xE0A090A0EE8FEA02ULL, 
            0xDC2D5CFF2A540677ULL, 0x3EA0B65FF4206811ULL, 0x8254FDBD45A6B836ULL, 0x65EECFB8FC302B9AULL, 
            0xA0E804E3EC3F3E3AULL, 0xB0D3FB520A96B5EBULL, 0xA7D418846F9011C6ULL, 0x70E65562256CCED8ULL, 
            0x822A7C9613F3C7B6ULL, 0x806F87C94EAF8E76ULL, 0x045D0D18016D3309ULL, 0xC629D3AC70C7DD66ULL, 
            0x50ED9A4F0E4E6008ULL, 0xE1BA2A53086DBEAEULL, 0x34DED9BD025BF7D9ULL, 0x2500A924CAD8D372ULL, 
            0x3EBBC1ECAC3976EFULL, 0x7F2CD7D7D1F41453ULL, 0xB7C348C5E9A4C3EBULL, 0x4F670DEA54106830ULL, 
            0xADABBCA55DDFD991ULL, 0xF62D6E597A561F1FULL, 0x56AD332852AAC942ULL, 0xEB6063A5C2E2056DULL
        }
    },
    {
        {
            0x28E6913B97900E07ULL, 0x62FE1AB81699C923ULL, 0xC3244E5E05D6CA3DULL, 0xD1FADCC07ABAC38FULL, 
            0x94292370BB430978ULL, 0xD1C8F9345317AF31ULL, 0x743A17F9FDB34529ULL, 0x041E3F2858FA5DA6ULL, 
            0xE26676D38688EA1AULL, 0x33A269B9348E9FCCULL, 0xE30525CB8A74B758ULL, 0xF463BACEC7512014ULL, 
            0xA33490A6A30C8CB2ULL, 0x2A5882DC73E0E4A0ULL, 0xA7B9B7333FE2C81EULL, 0xC2C5B0E15506ACF2ULL, 
            0x8B0D432E46D73DE5ULL, 0x6497DDB1672B31FFULL, 0x7E42E04C2BF5F021ULL, 0x5087319101D4922BULL, 
            0x268F90A33CAB8044ULL, 0x0AF2DCD7CB040A7BULL, 0x2A61BEFC1F1A9CE3ULL, 0x0B6C449492ADBABBULL, 
            0x620FEAA305F22080ULL, 0xEE3D7650803C3221ULL, 0xB91D3B319E90E403ULL, 0xE3C0FBC3786A67B8ULL, 
            0xF9501473ACC395FDULL, 0x65D26D7BE781E1F5ULL, 0x39B33C27A95828D7ULL, 0xBDA8190D840A4A4FULL
        },
        {
            0xDD8F19A22A36EF1AULL, 0xA44F0A59DD78409BULL, 0x6332F98F6BE915BEULL, 0x0B9F38076D45A561ULL, 
            0xCB4ED50050CBA527ULL, 0x682808A55658F74DULL, 0x0B2C96CA2A352E27ULL, 0x472096011B1BAAFCULL, 
            0xB5E52C6C5D759993ULL, 0x7FBE155C0B704F3FULL, 0xA6A5BF8B6A47601BULL, 0x98DB3DDB9D82A83DULL, 
            0x94F1DFC63EA0379EULL, 0x8E5EBF1C88434477ULL, 0xFD77B43A62A8E48CULL, 0xD406FCD0025904D3ULL, 
            0xD4165C8E6BF1487EULL, 0x057D636BA12D4566ULL, 0xFC9FB10175689436ULL, 0x3DEA4CD8F39FF614ULL, 
            0xE2FCB337B7C0B012ULL, 0x03F2F54EE9C73B3CULL, 0xA72AD19924FC2EC4ULL, 0x724E04E46DDE6A2FULL, 
            0x585842522155E4F2ULL, 0x5837F4BB3F305342ULL, 0x7AD47F32743C085EULL, 0x3017E3E3B68C8093ULL, 
            0x10744D693471F904ULL, 0x31E1F855912DAFA9ULL, 0x6CA662BCD15D0493ULL, 0x74CEC28EC2B9BC92ULL
        },
        {
            0x7C6A970C8E853A93ULL, 0xAA540D71AB6E1FB1ULL, 0x16A9CEEFDF30531CULL, 0xEF6EA23451C5A4F1ULL, 
            0x4DBDB01845F4E1AEULL, 0xD8ABA206CDE60141ULL, 0x26EB00B27B3423F4ULL, 0x0936C110BB892E70ULL, 
            0x97BF70C65BDC5FAEULL, 0xA6A1FAAF69259279ULL, 0xA87AB034E8970E84ULL, 0xA9AC311A9FBFE08AULL, 
            0x0721E46A68C2C948ULL, 0xDED78154AA723BE5ULL, 0xB418BDD8739D443FULL, 0x6E7F6BBDF70B24E8ULL, 
            0x0790402FDAF49B4BULL, 0xE3FBAE5B81142220ULL, 0x7448935B8B3DF4AEULL, 0x84A69332D71C3CB9ULL, 
            0x52ECC0F8BEC0E1C2ULL, 0x08ED955D385EF432ULL, 0x2D95BD95B815BC55ULL, 0x00898D2473A89098ULL, 
            0xA795DD8172019531ULL, 0xF0DA4037AB0CCDE8ULL, 0xB059AFE2C6FC4703ULL, 0x6CBC757C0F2689ECULL, 
            0xB166418D36226901ULL, 0x7FCE2211D7478B3FULL, 0xDF9FE1A198527E92ULL, 0x4CE2169A219EAF80ULL
        },
        {
            0x2C32AD918534FDF3ULL, 0x6A5EA3115844D241ULL, 0xD7664A6966D81231ULL, 0x6FECFC8B2255C16CULL, 
            0x06CE24FAD6271302ULL, 0x35C28C2E24545AF8ULL, 0x9D8930549F325054ULL, 0xF6AAEEACD1D83701ULL, 
            0x08EF4B1F6FC6EEA9ULL, 0x5F9135BFA21DB1DEULL, 0x81559D234FED3576ULL, 0x9D30DBF9C8709D7CULL, 
            0xD841D1E65647F234ULL, 0x9FFC87C18B2D89ACULL, 0xF64E623F8CC385C2ULL, 0x7F20C3918920D8BEULL, 
            0x3B4424B5908797C6ULL, 0x093786DF4A806B98ULL, 0xC4913C9B7D6E1B62ULL, 0x73E6B1629A0D942FULL, 
            0x75F5AE2DBDAF9358ULL, 0xEDF37BC8EA028B5AULL, 0x1CDB852D9585B3F7ULL, 0x3CC38AD8A926CCFAULL, 
            0xB9240AD35D347B9CULL, 0xFA6CF911DB63E2D2ULL, 0x7CCB3C195B72C5EDULL, 0xDA16230E669856A8ULL, 
            0xD77C9E57817745CFULL, 0x1DDFD782ACC3A6D2ULL, 0x13CDFB75209040F7ULL, 0x38746F703516FEE4ULL
        },
        {
            0xC922F97CB94DF6E5ULL, 0x315CC54BC23D2956ULL, 0x7FFCF2721D4A3858ULL, 0x6DB67FB357F59F49ULL, 
            0xBC6F939A487B0B3CULL, 0xC80BB54E7A6AAF13ULL, 0x0C72DDAA57334989ULL, 0xC9530013D43CB568ULL, 
            0x26A654ADA5EB499FULL, 0xD84326C11EB66EB4ULL, 0x95F6F2A62E1D7BD3ULL, 0x0CBCF3AE3DB31020ULL, 
            0x5A5E50B165460FFEULL, 0xF78889FA48DA7BBBULL, 0xBE34438F75D4333DULL, 0x48A37A154AD3824BULL, 
            0x20D6C0D0F74B620AULL, 0xC20CA089AD262875ULL, 0x6C1AFB521501808FULL, 0x932E8160E0C712FEULL, 
            0x51131DC0262010C4ULL, 0x02AD26533E148EA1ULL, 0xC3AA5732421A4802ULL, 0xF2EB40783E5E5368ULL, 
            0x24331D1529354BEEULL, 0x1F827747EF8C692FULL, 0x34901BF725B1E191ULL, 0x20B749171AE73D0EULL, 
            0x6254CCEC92FAB16EULL, 0x742CBDF257538D76ULL, 0x24A2F9B0D1CE6E8EULL, 0x467EA04F33FFAC36ULL
        },
        {
            0x628458FE33CC9A8DULL, 0x769B2B7060DB0F2EULL, 0x370116D2DEEF5BAFULL, 0x6DE56800C2A5D02CULL, 
            0xD4C990C67DE901D9ULL, 0xB8B6DE493085FA52ULL, 0x813E2659110D3D66ULL, 0x7A3A54BEB8321459ULL, 
            0x87F5173ECFEFC7AAULL, 0x1B95A4AC7B0FF741ULL, 0x888F1F4879CA062AULL, 0x6D60883F96F657C5ULL, 
            0x83A5B2DB6014A06FULL, 0x01D4FF9D7BA2F257ULL, 0xE752CE864BD01AACULL, 0xA024BA9EC2C0E335ULL, 
            0x01C874838CCEC727ULL, 0x7CD3553BCFE7000EULL, 0x36BE35C870EE0D97ULL, 0x5CE6F46A70F68D4BULL, 
            0x61276DF87D9FE726ULL, 0x687DB05FB1CAFADCULL, 0x14B8E2CDB840FA97ULL, 0xFF69E93DAF6EC7AAULL, 
            0x77DB578FE639C5DFULL, 0xB60AAA8BDA968F32ULL, 0xD66BFE50A9D1A79CULL, 0xCBD71CF59F6ADB65ULL, 
            0x5FFEA208C7780456ULL, 0x22F6562F1F41F6D0ULL, 0x431659FAE389D199ULL, 0x360A96283A18A41FULL
        }
    },
    {
        {
            0xF35025C18B6A26F8ULL, 0x3DD57889993BAED9ULL, 0x85266ED1EFC0A232ULL, 0x61E83796BC2CD958ULL, 
            0x1B57DC27B84EEE98ULL, 0x48400C5F72D10DF2ULL, 0xC2937CC85C2D83C6ULL, 0x2AECFAEB1E4D63D8ULL, 
            0xA2BE184A992E5309ULL, 0xD00C146C7E9C54FBULL, 0x9B714470B114C267ULL, 0x904C00EAAFED3DA2ULL, 
            0x3177E7EBB5D4AD1EULL, 0xB95345C9761953FBULL, 0x7E00368AC3A28A14ULL, 0x8B8EB9C1A3FC7060ULL, 
            0x0DECDADB6E3B5FBBULL, 0x87827D9C95E29CBFULL, 0x73694945DF6499ABULL, 0xD6070E90037E19E2ULL, 
            0x4BFB0999832FB8BDULL, 0x957625300A630CB5ULL, 0x04C1BFBDA496DC3DULL, 0x3202B433CD0EC3D4ULL, 
            0xF7821E9B4EF6C0F0ULL, 0xD80DF3078FBE7330ULL, 0xD255631BE438EA12ULL, 0x96D35CCB284FFE32ULL, 
            0x4DC725387E2D6879ULL, 0xAE5BD620EC495420ULL, 0x6CCBBE60CD3C0868ULL, 0x9F8CBF0A4C88DCE9ULL
        },
        {
            0x3C879CA88F1B221BULL, 0xF3D0FDE7887E8E95ULL, 0x390482C42D895655ULL, 0x323516B9CD8CD3C5ULL, 
            0x66EED0F9C4B34179ULL, 0x9A1C53B9FF071A9EULL, 0xD9A9AB674B7164E5ULL, 0x872E460F9A3DA9AAULL, 
            0x39AB4620EC569111ULL, 0x1526C25158F3AB20ULL, 0xF0297814A416ADFCULL, 0x54392D1E4BE96E24ULL, 
            0xC8E666D7332A3E22ULL, 0x7DB01BAD55B7B362ULL, 0x1A4E1216F243FB28ULL, 0xF549415BA55FFC28ULL, 
            0x6E567CABFD01A0A6ULL, 0x41BDBF3E174730E5ULL, 0xAA6F36B0A07D02BCULL, 0x5F72627FED40A2AFULL, 
            0x9FD69AED46563F8BULL, 0x984CEA48F2DA312CULL, 0xA6235B08C7D00CAEULL, 0x361C444030D84F1CULL, 
            0x316F5E92C50BA685ULL, 0xF5EF0F5231E2CE63ULL, 0xD6DFC596CDFD7B31ULL, 0x9F92535F279E3832ULL, 
            0x8D345727ACA6D40BULL, 0x218E286E8C44152FULL, 0x3BB057869FF6175CULL, 0xD9481550974BA822ULL
        },
        {
            0xB6A9C14AD0F16A30ULL, 0x128CAF3F61399E7DULL, 0xAC2C19696176C3FCULL, 0x72681FF3A950C7F8ULL, 
            0xBC762A9A37A8006AULL, 0xC634C8B1989E15BFULL, 0xCECC08B872CC83EBULL, 0xDDF607EAA8173944ULL, 
            0x0969B7C9805A5BB7ULL, 0x513A9909D6769B69ULL, 0x6EC0EA6B6833161FULL, 0x4B8109E5BFBF41C3ULL, 
            0xCBDAFAE0E57E3C11ULL, 0xDDA07196F81F519DULL, 0xB21D9FD1511924F3ULL, 0xF66BF495B09BDDF4ULL, 
            0xB832E1C1E172C938ULL, 0xCDA1D7DED1305DA0ULL, 0x92CC7393BD80C693ULL, 0x399C443B1660158CULL, 
            0x4755E0C1E08C76D7ULL, 0x0D2213326B918FA7ULL, 0xC7E998FEB6A89C4FULL, 0xD181A4B307636F10ULL, 
            0x031649885BE17B50ULL, 0x41C00AA0AC5AEED9ULL, 0xBF5D7300AAE64BFAULL, 0xA1A76F33D7B8F8CDULL, 
            0x21D2BAB03759EF55ULL, 0x0F3512091D17013FULL, 0xBF9C39F76F301719ULL, 0x8464F069FE1A1ACDULL
        },
        {
            0xC60E8B1456BF494DULL, 0x0BCD9C45CBF19DBDULL, 0xA26E066BAB9173B9ULL, 0x19931C22EBEE074FULL, 
            0xBAF3626C083E3DF2ULL, 0x634AA0A9709F202EULL, 0xE77DF823DAFE876BULL, 0x501B7B315CED8C72ULL, 
            0xA0AC9A6857C69421ULL, 0xCC22CE4F6EBEB920ULL, 0x3FF4B515503F02A1ULL, 0xBD538AB7253C7711ULL, 
            0x1FCE4C838B4786DBULL, 0x09FDEB50D4235A80ULL, 0x4FAD579535204C7FULL, 0x2676610EA3AA280BULL, 
            0xCC7EA7654E72E125ULL, 0x5E08264FB5209D26ULL, 0x18386468EAA42441ULL, 0xD838DF573B9FD03BULL, 
            0x50E13B264B6B94B8ULL, 0x80F0F9E7E8164E29ULL, 0x7566870F3A21315BULL, 0x17BB48A7CF0655E9ULL, 
            0xBD1B8F6B36019E08ULL, 0x02D8B35686F10A04ULL, 0x5EAFB08C88B5EE0BULL, 0x5C799599E7E3717BULL, 
            0x14AAB00CA9C1256EULL, 0xE43DA0F3CD54D539ULL, 0x052716CD1672F57EULL, 0x61CC9E5CBDA13608ULL
        },
        {
            0xA166D7FBFFB80F98ULL, 0xF824C9378B6ADD65ULL, 0x2CB73279EFBD79D5ULL, 0x5A4CFC4974700CAFULL, 
            0x59A8FD1377624EF5ULL, 0xE33C682F2145528EULL, 0xC5040B46361C668DULL, 0x9A9C1164AA9C7679ULL, 
            0xCED52FA5F9FEF6EAULL, 0xFC3273DFEFB71891ULL, 0xA9A413DA961E3E6BULL, 0x75C0B39B0EE3FE9BULL, 
            0xC23444F515251D8CULL, 0xCED9DAFB63086347ULL, 0xAA7B6ED35DDFFFE1ULL, 0x57997F5B20F25672ULL, 
            0xC20F23DF115F1D41ULL, 0xF4112DEA460F53D8ULL, 0x1B3BB67F250EDF9CULL, 0xDC959C5F9F9360A2ULL, 
            0xF2C74AEF0FD27FD0ULL, 0xBD8264AE9ECDAE65ULL, 0x5263D77A397C25CDULL, 0xDE3CD4A395AC178AULL, 
            0x669FDEE90AEF3AE6ULL, 0x926D6A8075A40BECULL, 0x943B17B01CA44759ULL, 0x455183B476C7FE02ULL, 
            0x9FC1CEA85EB567FDULL, 0xDB05C3EF4F299993ULL, 0xFD89A65673928478ULL, 0x5EB520D3439641CAULL
        },
        {
            0x8A497E587C97B2E9ULL, 0x6753F0428FEC3849ULL, 0x9F29EB0F9B82C7C5ULL, 0xDBC909C0BB406BD0ULL, 
            0xAA91E62193FB5892ULL, 0x7801E470E55ABD37ULL, 0x82627229F504A4CBULL, 0x9EA8F8865C76B67FULL, 
            0xCC317C410BB3E8A1ULL, 0x0FCA79416BF7132EULL, 0x566018920F36CC4BULL, 0xA435BB3163CF601FULL, 
            0xD49BF589CBBE154DULL, 0x648F61EAE71214C3ULL, 0x93AED1B39B2890DBULL, 0xBBDB1E35E372EA1FULL, 
            0x6F053D6BD5C52458ULL, 0x94BE239F3B64ED75ULL, 0xD895C1D5C7C51167ULL, 0x45B6315269C6D665ULL, 
            0x00EB38A7030444FAULL, 0x5020F6368EB0A450ULL, 0xBA83DB3204C791A9ULL, 0x37E06752CF752F95ULL, 
            0x0E14976E71FC90F9ULL, 0x369470EE89ABA9F6ULL, 0xD2E79D356011CD6CULL, 0x85B1A11066512238ULL, 
            0xFECB4DBB8151E4E5ULL, 0xC7086E29896AD6E5ULL, 0x46293936297E637BULL, 0x0BB815F91A8F428BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseAConstants = {
    0x27611B6F6B63CCE3ULL,
    0xF0496B8A21F2A9B8ULL,
    0xC99911CE62FC92D9ULL,
    0x27611B6F6B63CCE3ULL,
    0xF0496B8A21F2A9B8ULL,
    0xC99911CE62FC92D9ULL,
    0x52E67836E8DE0246ULL,
    0xC73DC920D5FD69EAULL,
    0xC9,
    0xB1,
    0xD3,
    0xF4,
    0x5C,
    0xFB,
    0x27,
    0x16
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseBSalts = {
    {
        {
            0x059315A1CA9213E3ULL, 0x0679CCF78F715647ULL, 0xA926A185982F025AULL, 0xDB121A63A740353AULL, 
            0x4D809959C03631B4ULL, 0x768464FA8163E43AULL, 0x9A8BEEBDA12BF5AAULL, 0x2AD15438D50F5D13ULL, 
            0x9BC14E21230B80D0ULL, 0xA1F1D195FBED0CB1ULL, 0xE6F333B66C14BF9EULL, 0x4D015AFECFF50BC5ULL, 
            0x0035153F185D77ACULL, 0x4DBA349C2D9D1650ULL, 0x2CEC176CF5373768ULL, 0x604D2E48C41A6AADULL, 
            0x6A212032CB2A2C74ULL, 0xA5493EDE93EEDC13ULL, 0x23E296AA2890CD9FULL, 0x8D8108B7D35B80CDULL, 
            0x5B610CAD4BCAB0E7ULL, 0x7D3BFA31E49C6E25ULL, 0x5FF1CCD9E3853F09ULL, 0xC9238DA46FEF4959ULL, 
            0x05A6FAB186313691ULL, 0x3EFA744DD5EBF701ULL, 0xD567A340A145B946ULL, 0x3DD0882233D5186CULL, 
            0x1BA7958712C895C1ULL, 0x88BDE1A150F164CCULL, 0xCA0D02C6792CCC91ULL, 0x018B67D91D7389EFULL
        },
        {
            0x53077C462A223729ULL, 0x1BC1670DEA8BCC06ULL, 0x8D379A11AF9A8A33ULL, 0x13AB4BFA118BBE81ULL, 
            0xE345BD6D16180170ULL, 0x7333F1577A1B369DULL, 0x3C62C60B4531CF7AULL, 0xC6EAF83A29D92B68ULL, 
            0xCC4B9C33E4C4D93EULL, 0xFEAB7888DBB99A8AULL, 0x4C4A1F3EA42B5EECULL, 0xAB30C4780E8C807BULL, 
            0xB172281664E9D583ULL, 0x7F29604232586679ULL, 0xEA75E141F61C153CULL, 0x2FE0C992C9E192CCULL, 
            0xEB3BADCF9A4282E0ULL, 0xD772D7725530C8A2ULL, 0xFA61F9215D17E18DULL, 0x4D2C702CBEA575DEULL, 
            0x208F7ADA960EA1DDULL, 0x7FBFD28BD4761486ULL, 0x78C6B63933CF8BA9ULL, 0x24EEE3D592306DF1ULL, 
            0x300A6DD0738061B2ULL, 0xBA5F897A3B76D24FULL, 0x68FAC737981935F7ULL, 0x6210CACA60086872ULL, 
            0x34EF0AF846B27297ULL, 0x19122F8E161D0EF6ULL, 0x9DDC132F6FB65F78ULL, 0x67C5748D16EFEB29ULL
        },
        {
            0x897A396FD10BAFACULL, 0xC903E6522267B844ULL, 0x5CA3918671231540ULL, 0xC6EEA25CBDBE32B8ULL, 
            0x98759C5D63DFD8F0ULL, 0x36B2D9121E0941E0ULL, 0x69891259D50BF6B6ULL, 0xD725F3F7DCBDB9C0ULL, 
            0xB54A973D49A96905ULL, 0xFEA0234D903BA0DDULL, 0xDF73DF87A269B8ACULL, 0xE9DBEAF6BC464437ULL, 
            0x673F2D85E224057DULL, 0xC03F2AC2EF3D3271ULL, 0xEF1FBD45CC5C5F75ULL, 0xF758C78BF3FDFFCEULL, 
            0x18D8C12EC95F2ECDULL, 0x7772E1938487E521ULL, 0xBD22738EED88A9B3ULL, 0x6CDC18AEC3C3E69BULL, 
            0xDCD9E38FE6C4C43DULL, 0x2551FBD5001C167EULL, 0x8EE3194101DB267FULL, 0x9FE2C56DE34E4588ULL, 
            0xBBA832B397A188F4ULL, 0xE9C98CA91C37CFABULL, 0xF8649A349C14B3EBULL, 0x1A6FDCAF5A4FD4C4ULL, 
            0x7E456B7F04394BA1ULL, 0x7866341651E3E153ULL, 0x787ECA87CEC1AFD7ULL, 0xA911039E34BD6AEFULL
        },
        {
            0xCD4D8EB26433F594ULL, 0xE7B3C0E93B86E22DULL, 0x4B50B3D17A0CE224ULL, 0x727BCF7EAB15B67BULL, 
            0xF24416DEC1A5B177ULL, 0xFEC0428B5F2FD0EBULL, 0x75FBD2BC2F95570AULL, 0x602AA55C2340745FULL, 
            0x1A6C10D28D56019EULL, 0x2E640F57E063058FULL, 0x0120B479C241798AULL, 0x26F25A4AC731F094ULL, 
            0x59F55ED3154B4CD7ULL, 0x00AD4E64724D3E6AULL, 0x7168358B2E6A6959ULL, 0x6A15B61D41E3BE35ULL, 
            0xEF4DD6EAD182F71BULL, 0x9413CA1D1C9469B5ULL, 0xBA9A9F22C67DB930ULL, 0x3D81933CAC7574BCULL, 
            0x3240057222AC24C0ULL, 0x4BC937BEFC1D066FULL, 0xAE02BE25736FE420ULL, 0x437409955665F82EULL, 
            0xFD74E13F541983EDULL, 0xCEA564D39532432FULL, 0xE323408F84779673ULL, 0x0DB72D50FAA4B228ULL, 
            0x2BAF0CC7C8337F2FULL, 0x3AEBB63517A6D9CBULL, 0x5A09B2BB7EC04ECCULL, 0xE4E5BE8FA27EBD2BULL
        },
        {
            0xBB2F53CB98C20386ULL, 0x45F2A635DE7A0126ULL, 0x0A9E9028730D282DULL, 0xF399EF0DA59388D3ULL, 
            0x6A09F4912DE7041BULL, 0xC2C0C8F2E3645164ULL, 0xADDD57EF41ED363FULL, 0x6907DE59D9102ABAULL, 
            0xA17C7856ECDD7798ULL, 0x34A02FE182B162ACULL, 0x45A4897E6805DBF0ULL, 0x800FF262C9E75051ULL, 
            0xD5B55EF1823387E0ULL, 0x9A680370D101FD1FULL, 0x48AEE1C9BED0F478ULL, 0x6A1E41076FBA4EA6ULL, 
            0x44EA6691D9E97E7CULL, 0x87D4732B7DFC646BULL, 0x833BD7A5A8A0998EULL, 0xDBEB84D7126E41CCULL, 
            0x534D7FD06BD2823EULL, 0x4F083EACAD48124BULL, 0x8A9D22DE4267F639ULL, 0xE471E15CE94E87C6ULL, 
            0xDFB178DF1DBDEB50ULL, 0xBE5149B3EC4551F1ULL, 0xC9550E75FFA44690ULL, 0x0B4CBB21BBDF40F7ULL, 
            0x8B9165523E415AB9ULL, 0x45536D88C0F9DE26ULL, 0x15B8CEE4556B05E4ULL, 0x27FAADB8EB43D13CULL
        },
        {
            0x8F57C849C0C1EACCULL, 0x019832AF532DAEA4ULL, 0x87573057D2A0101DULL, 0x098AA2D1A2D943ECULL, 
            0x417312044D670CD0ULL, 0xAD87F98EF2E7EE63ULL, 0xC10EE54DCAA87E4EULL, 0xED7912A8CFBED736ULL, 
            0xE27BD7D38A7ED587ULL, 0xBA527CF89EC581A7ULL, 0x086A18CAE7A635ACULL, 0x4EA159CD02BD6C58ULL, 
            0xF597C1E28898DF72ULL, 0x74720D1F9DC25A11ULL, 0x413C936592F5BEA0ULL, 0x233F042E6BADAAF2ULL, 
            0xFD3B4BDA0B380E55ULL, 0xFC1A529C69496962ULL, 0x7D266AEB74A071D2ULL, 0xEFA9A28D5EABB0DBULL, 
            0x4ABB0B5E0B3C7BEBULL, 0xCBE7D73BA71D3F0BULL, 0xB4E6900615BF36E4ULL, 0xD571A8720623C240ULL, 
            0x290933B6929E5D16ULL, 0x7FC372D6839D308DULL, 0x6C53E9F0AF2BCC2AULL, 0x60E325A5D294B10AULL, 
            0xB151F993A82E737FULL, 0x7A2F97F039865C70ULL, 0xA4A2AD815319BD68ULL, 0x4476DA86075557FEULL
        }
    },
    {
        {
            0x8E99C6E73799CEE9ULL, 0xCA36BFABAC163617ULL, 0x8F8D0F5BF26B7216ULL, 0x82C2AD7619F81EF8ULL, 
            0x639165FE5D52C292ULL, 0xFDE48B803F587AAEULL, 0x341BCCE8D8B6036CULL, 0x423CF5204A376AE3ULL, 
            0xE58EE0B0ADB65E4AULL, 0x8B7E12E4E7FED8ACULL, 0x496BA0CC25CF4DBAULL, 0x74563B01A3167A97ULL, 
            0x64C43011A7E26B46ULL, 0x850E8E92397561FBULL, 0x841C90C603583ED5ULL, 0x6765E95B9A2AE861ULL, 
            0x9FC2C6BCC5AA4E40ULL, 0x9EF468A4AFBB0895ULL, 0xB04EF8301F64F942ULL, 0xD1DAC5BA2B769618ULL, 
            0x6D84226AD22F2FE6ULL, 0x6CAB9F1CED39CF72ULL, 0xF44E392DDAB964F4ULL, 0x03A8D3DFE4FD7A0EULL, 
            0x60362ADD523733A1ULL, 0xF41A961188F5C005ULL, 0x1E98D318466A5B9FULL, 0xFCC1C86943C8A0D6ULL, 
            0xFE6D40C1BA8A6C3EULL, 0x5360A3ABE8A6C10BULL, 0xE7FFDE1576617096ULL, 0x1D0DADDB28A46250ULL
        },
        {
            0x42106E5F0BF470D4ULL, 0xF539FE775F6DE70CULL, 0x52DAE065E7C7DBDDULL, 0x89CDAEED970A4CDEULL, 
            0x4E8718A939615953ULL, 0x1C594EB23E8A1B17ULL, 0xE73BD14AAFF53C34ULL, 0xA2BFB43713633A40ULL, 
            0xF053192CE237E0AEULL, 0x877DFA406779679FULL, 0x287643EB6479553BULL, 0x200139C3B046FFCDULL, 
            0xE6A3E7D41A125AF3ULL, 0x59A7C75C54A2017CULL, 0xB631F77D2FD47ADBULL, 0xC6CBF7A3D5A17952ULL, 
            0x51310A28F7939EE0ULL, 0xCC10ACEECEF7A76AULL, 0x1E9F60F1267B143DULL, 0x7395FFA84E9C2AFCULL, 
            0x4D7DE26D38E813BEULL, 0xF0DB5715D8C36789ULL, 0x18A2A4F84EAA483EULL, 0x02659F76C4AF0B10ULL, 
            0x74F6B613737609CFULL, 0x88925A52B1A50416ULL, 0x3B61A72D07D52C03ULL, 0xAA9887EA91A4C9D4ULL, 
            0x8C5A34587E266A5EULL, 0x8BED9CCA79185070ULL, 0xBA9B28225AFDB414ULL, 0x5D943A4D261B4911ULL
        },
        {
            0x6F6E83F3D9F43A91ULL, 0xAF5A1CAF3EBBCFAEULL, 0x3ED5C1CD164DBA41ULL, 0xBEE0B9D67373ABB3ULL, 
            0xE209732F8329BB19ULL, 0x0D2982126A923D22ULL, 0xB0CB49D3063B1436ULL, 0xD83D48FE3B44E035ULL, 
            0x0E8C24A723BB378FULL, 0xCB5E5D25903C0D89ULL, 0x03324223015DCED1ULL, 0x7F64FB3A7CD21651ULL, 
            0x344F8A98BF87E0D3ULL, 0xF2A86ACBE87FC432ULL, 0x7DB63C3818080347ULL, 0x596CC4E2F154FD23ULL, 
            0x57E26FA242D624B1ULL, 0x810953A38867092FULL, 0x88AE2A7DE6BC1233ULL, 0x0F10743264F00F34ULL, 
            0x2BDB2DFC78A39007ULL, 0x67F5EF632B41063DULL, 0xDC705E669482B646ULL, 0xD176ED125FF98F5FULL, 
            0x05386FEB87589C5AULL, 0x1F6CDCE8CDA1741FULL, 0x62DE4C16C6C7C7BAULL, 0xF00FC5479834865DULL, 
            0xDD984A204A0A1A39ULL, 0xC957644BB56942FEULL, 0xBAA9B14DDECCF643ULL, 0x4334CB625337E979ULL
        },
        {
            0xC5AA3E5A95B13819ULL, 0xC14ADE2D09CEC6B1ULL, 0x0E3852C36463BEF4ULL, 0x8A2F33E4490E2AECULL, 
            0xB163D56D394134DDULL, 0xE9CE4937C4268592ULL, 0x6EC56ABC877E6F18ULL, 0x3132013B2E8454A3ULL, 
            0xCFD403941A87B2E1ULL, 0xEB037F968CF39A2DULL, 0xD342FCD0F3CB56E7ULL, 0x09EB640413C1D895ULL, 
            0xAC2EE17BD2E6E036ULL, 0x0EB403C214731E3FULL, 0x8269C88A226A3890ULL, 0xCB56A8195E84309FULL, 
            0x153360CB02B9332DULL, 0x74E5F5CB867F7FA0ULL, 0xA6CFB09436427978ULL, 0x83EE1F444ED4913CULL, 
            0x14B51214C18BC22BULL, 0x29A944AE3576CEC1ULL, 0x5DF64ACE943AF30CULL, 0xA29F16B5C6A34CBDULL, 
            0xA719E7D79C0EA266ULL, 0x3E26A643CA2A9A62ULL, 0x86EF1401426ADFB1ULL, 0xEDEB3A5CBC7C3825ULL, 
            0xC9542D72E0FDFB86ULL, 0xEF19746FD74AF62DULL, 0xB62448E8FC128035ULL, 0x347D191526808F4FULL
        },
        {
            0x3D5CD42C11083ACDULL, 0xD82170F81EF60F42ULL, 0xF8323D6B71EAE7A5ULL, 0x4B4EC406FA482486ULL, 
            0x25B55B0F888E4CDAULL, 0x60299B654F8E60A3ULL, 0xDF7D8CD809DED5CEULL, 0x9A3C45D27AE45DE3ULL, 
            0x7D5CEAD728B0EA13ULL, 0x9B188F95389D3BE7ULL, 0xDAFC31E090C62AAEULL, 0x4B13DF2CFA803B3CULL, 
            0x2F74A60FFB8B9677ULL, 0x666A01CCB7375B92ULL, 0x9203A5E5958F6271ULL, 0x624ECE71D20324B1ULL, 
            0x9724C9617BFE1841ULL, 0x06890EBE19B15DD1ULL, 0x61FF821B9551C21AULL, 0x18ADDB806D4DD83CULL, 
            0xD078252A687C7102ULL, 0xC4CA027038570D96ULL, 0xDE9016AC0664B38BULL, 0x1C3FE4CBCCE71050ULL, 
            0x1EAB9F5A3D78B85FULL, 0x5C6F3AAC79885734ULL, 0x54D545FCB1AB6F7CULL, 0xC3A8DE1F4DCBB469ULL, 
            0xA60D2219FF830EAAULL, 0x0D2BB77F8B9BC1BBULL, 0x9DA062E53CE358ACULL, 0xD85C8B102831FBC8ULL
        },
        {
            0x6B6A800AFFE0B449ULL, 0x6BBEFEB1BD1BAFDEULL, 0x257E18DE237B4938ULL, 0xE14B11D776022439ULL, 
            0x4D241766CFEF3060ULL, 0xDD578EA0DCEB83A6ULL, 0xF35A2DF837B306D9ULL, 0x997934EA6BF0185CULL, 
            0xCEF47AB00EB16011ULL, 0x3B4D2A60D5AD435EULL, 0x67222D42B5DC4B23ULL, 0x62ACE79410B0E335ULL, 
            0x3A2CAEC1C745F9ABULL, 0x58BF98A59CB7A298ULL, 0x65C469F4BF90451EULL, 0xBEB6D56F4127E1B2ULL, 
            0x60EF656F7C10637BULL, 0xA40EF3A4F3E19D4CULL, 0x5F0365E9CD56EB39ULL, 0xD57571FAC4CB9495ULL, 
            0x2698C2D2D8E71581ULL, 0x70515920964AEF36ULL, 0xAD925AC18962AE24ULL, 0xBF6F8638FA2CC52CULL, 
            0x9FE7EB8B93FAF004ULL, 0xD489BF9DF3E93131ULL, 0x28D312E9CD4802D0ULL, 0x93FAF1E00CED69B1ULL, 
            0x05B242FA27C82329ULL, 0xD667750827CD2876ULL, 0x654F3A754197BDEEULL, 0x720B44025027BB73ULL
        }
    },
    {
        {
            0x7AB88C8E4CA1AB6FULL, 0x6A4E8836FD4F44ECULL, 0x5E4D86E8E2D0CD3AULL, 0xB3027E83F5A74A9DULL, 
            0xC931FD43F773E649ULL, 0x985C07E02A257A4FULL, 0xDDB87F94615A9B3DULL, 0x309DB6B8353D22B5ULL, 
            0x58F5FEAD1C60B515ULL, 0xB00626C4F3026C72ULL, 0x218A0650862E1284ULL, 0xC8D116AC7B03F5D3ULL, 
            0x83CE1BFAD0AD43A7ULL, 0x5CB071357E67C9C3ULL, 0x0DBF615A7A519056ULL, 0xDA63380056E544EBULL, 
            0x87AF050B7D78BEC5ULL, 0x7B451B8B0FF4E634ULL, 0xEC8B05891881D7C7ULL, 0xE713F63A671117B3ULL, 
            0x2BB33D7787B3E667ULL, 0xA77D92D86C294A47ULL, 0x21A75C455F69C9DEULL, 0xBD91B6170BCAA195ULL, 
            0xEEEA8D1C92D02376ULL, 0x197AFEF044E17ACEULL, 0xC2FD39CB0795A318ULL, 0xE3F9BDC9B160855DULL, 
            0xA1A4CD39AF4E7D6DULL, 0x87DABDB40AABEF6EULL, 0xD6AB87BD3C71E636ULL, 0x6A3EBF543D017306ULL
        },
        {
            0x1F080B828BE96071ULL, 0x8D157C009D2611B4ULL, 0x127DCAE2378E1F9AULL, 0xD1DD5DEF8106F266ULL, 
            0x4C8CC82F885945E3ULL, 0x01DDB1B614B5CA4DULL, 0xEBE6143B02F74889ULL, 0x019047E9A8593422ULL, 
            0x2BE3BE4C1F775166ULL, 0x131B0994BF669FDEULL, 0x5BD23C0800DBEA86ULL, 0x7EE0F1DA6E4D6088ULL, 
            0xA4676A9A2FF3B464ULL, 0x2827C461B3A2C9ECULL, 0x5D1E2F3F711B35A2ULL, 0x8B2C9EFBADC6A5C7ULL, 
            0x801ED5086222C296ULL, 0xF9E108B7A7C3C4CAULL, 0xF31E00AA36FCB71CULL, 0xC237B78C37E84B96ULL, 
            0x7032833383F695D5ULL, 0xC5CD61D15E21A385ULL, 0xB0705B91AA8009CFULL, 0x5AA71E58362EA90FULL, 
            0x69F367CEE6BC9DB4ULL, 0x445A5E30B88D7136ULL, 0x36F3293EC90EF645ULL, 0x10DC2A41A9B357A5ULL, 
            0x661941ECE656AAB9ULL, 0xC7E82B0837721157ULL, 0x54C0AB3C0E0B3EA3ULL, 0x485F026EBF7F05A7ULL
        },
        {
            0x59B39683D194907EULL, 0x6A0B1F0531C0B2E5ULL, 0x1A80190AFA3EE416ULL, 0x5C8B39BB6D785EF1ULL, 
            0x625F1EDF399FE39CULL, 0x6EE850B9DC1E6507ULL, 0xC0A26FB891AD467AULL, 0xC5019C3258837831ULL, 
            0xEFC070365261EEC4ULL, 0xA0582040D2EA7D84ULL, 0x2048B763F9E313A2ULL, 0x6D267734B285E68EULL, 
            0x9CE41D0FFAB92C70ULL, 0x912C32B20BE63932ULL, 0xE628ABD135C356EBULL, 0xDD8F1A59E43C86E1ULL, 
            0xE9E8E072573D1466ULL, 0xD21F197505816B40ULL, 0x4FC99D75921F1245ULL, 0xD03F18FF9BBE3B85ULL, 
            0xA76EF1BA7DBACE53ULL, 0x9051A5F2A8D28823ULL, 0x369C19CEA815DDE8ULL, 0x6606F22E729660ACULL, 
            0x72FB2C2773B2D112ULL, 0xA10BFD9AB73A3431ULL, 0x63CB94C297900FAFULL, 0x05B2B4E7AA2806CCULL, 
            0xBC881458B00868E6ULL, 0x4F9B19208A3654C4ULL, 0xBF0B0F4C07D62B57ULL, 0x93824BA812335129ULL
        },
        {
            0x947A71F7DC4533DCULL, 0x317B0FD3F6676B24ULL, 0x277BEAA20D2A26C7ULL, 0x557C71D1E46346A1ULL, 
            0x4130781E704DF7ADULL, 0x619E6F839F1F9DF1ULL, 0x38644709E2ED9C74ULL, 0x7F9AC5D83F29C0CFULL, 
            0xFBB48BE7E99C3B1FULL, 0x59F2F8E294663050ULL, 0x20A637196B3B90A6ULL, 0x075E496EA4FF3DD8ULL, 
            0x577F8E0AC893B81AULL, 0xD9073505CCA76AABULL, 0xAB10922A13C73750ULL, 0xEAB2352650CB8670ULL, 
            0x99E1908A61AEE63DULL, 0x8DF90DD54C11752FULL, 0x7528DD4155291420ULL, 0xF032474DCA20CE02ULL, 
            0xE7D1A7579DB76F02ULL, 0xFA6F4875B6568871ULL, 0x34B504C83F7D769FULL, 0x7F92DF12C71148E0ULL, 
            0x4D89135BD4B9C134ULL, 0x0659FB1BAA116C40ULL, 0x74F51FC51A1F15E1ULL, 0x68BA4B716350E02FULL, 
            0x737A551512C5EA4AULL, 0xEE154BE77F1595ADULL, 0x85F2203B8DF277E7ULL, 0x0B35633219A8EFCAULL
        },
        {
            0x21F29B7506538A99ULL, 0xC88EF9D9B493059CULL, 0x27E1CDAEDE118C22ULL, 0x92D9F8C347AFAC17ULL, 
            0xE72F67DFB734F000ULL, 0x23B20A4FBB3A5BFAULL, 0xF3044E3E332C9FF2ULL, 0xCAB27C4DEA40641EULL, 
            0x3B4DC4027FFB6FDCULL, 0x693CB2A9F41E8397ULL, 0x9CAFDE139DC772EFULL, 0x8C68FCF2F2A00344ULL, 
            0x9A1EF50A738A9E2CULL, 0x0223C6F8B447883CULL, 0xBA3DD1E9CABE7DC0ULL, 0x4B521F38AEB4B7F4ULL, 
            0x1BB0D5A478B94887ULL, 0xFD55CC1446A2D0D4ULL, 0xFF3BCCFC0BA56CD8ULL, 0xBADC03A3D03640DCULL, 
            0x4276560F6A3EA07BULL, 0x28B8B6E7C4C8AE77ULL, 0x3FC868CDF8FBF267ULL, 0x67EC9C2247C81053ULL, 
            0xA50C9BACBAB2303FULL, 0x44BCDEF56A3C3D63ULL, 0xD95F5FC382628709ULL, 0x124FA8204CB247BFULL, 
            0x51BE696D7D09FDBDULL, 0x53EF8EEF037ABAC9ULL, 0x0B2755EAFD08DD3EULL, 0x048AB1580437C07DULL
        },
        {
            0xDFC279B98A1EC060ULL, 0xE20AD8A15B1CAE53ULL, 0x6A702A9AD5B2F3A0ULL, 0xB462466C489622C0ULL, 
            0x88B3E7701A58B52CULL, 0x7D15C157A81432D7ULL, 0x3360C7AD5E82414BULL, 0x22D411C9A86453BBULL, 
            0x4CA79233FEAE6EF7ULL, 0xB3BCA8B1819701DDULL, 0x66B35554539C0FB2ULL, 0x4E341A05650FC008ULL, 
            0xD03E9AF8AD4274D3ULL, 0x53DA62D53802ED02ULL, 0x33B7A5FC816460F5ULL, 0xD516F8DE76585922ULL, 
            0xB37BBD6C4C4B4FD6ULL, 0x4F219011D4DCE66BULL, 0x55A523112B314EF1ULL, 0x86DF2F96D26BAC7DULL, 
            0x71FAE58C15F4C01FULL, 0x904895D446D6B871ULL, 0x4E650BE0904C2C90ULL, 0x9D9E4A8D43AF7D83ULL, 
            0x6986D07A114FB2C7ULL, 0xF39EF100DD2D15F6ULL, 0x4E7377F603AE8E9CULL, 0x1E947027946C4F53ULL, 
            0x39F399C90A2FB68FULL, 0x182091E002D2D043ULL, 0x55DEE80FC40A65BFULL, 0x9ED9F8534B935186ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseBConstants = {
    0xA4349976AC3CBC21ULL,
    0x5B2920EDD822E64BULL,
    0x32A7A005291E53F4ULL,
    0xA4349976AC3CBC21ULL,
    0x5B2920EDD822E64BULL,
    0x32A7A005291E53F4ULL,
    0x25E2083893E6DF1FULL,
    0x506565735DE7D97DULL,
    0xCA,
    0x24,
    0x68,
    0xB3,
    0xE2,
    0xB9,
    0xC3,
    0xAA
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseCSalts = {
    {
        {
            0x0E393B26B22A827AULL, 0x70AC86615A2FCA74ULL, 0xE6E0FC4675E0E6DAULL, 0x1393B15CEA83D71BULL, 
            0xF16D8F4492818DDBULL, 0xE1264A061EF0A3D8ULL, 0x5A3CDEB0CD086451ULL, 0x8AB8A48B66238BEBULL, 
            0x4895558D344E5A93ULL, 0x6D284915563EECEAULL, 0x63A497EA3815D8B1ULL, 0x40AE41E43A584677ULL, 
            0x66C46085043AC77AULL, 0xE62A427E7DBFEBFCULL, 0x315D806781DC3662ULL, 0x2C32BB4C4443B0B8ULL, 
            0xC95346370111FE67ULL, 0x22A835E535DED818ULL, 0xBF230D0869E92E40ULL, 0x6CECE17D0990FB21ULL, 
            0x9FF99A258F343DF9ULL, 0x43BF982E3E893128ULL, 0x10367507A1A7859FULL, 0xD33A890CA8B6F4E2ULL, 
            0xA2ABD79E97087C50ULL, 0x0AB97B2A1823267FULL, 0x7D6435D856711E65ULL, 0xA0EB7C77352CE8B4ULL, 
            0x4AF01E52762FCD38ULL, 0xE3AE941FD7B99BC9ULL, 0xCA15B251E6C1BDB9ULL, 0xA832E424DD08B297ULL
        },
        {
            0xF4F2F192090592C1ULL, 0x166D778BA90BA2F9ULL, 0xAE4CD130FBD95FA8ULL, 0x33590F37FCEAE68AULL, 
            0xD536C23883AF1EC2ULL, 0x5FC52F8BF1E16C15ULL, 0xCE741ADA153B854FULL, 0x7A2CCCC84C26E443ULL, 
            0xE010C9C4BCBE2290ULL, 0x55D61F01A57D0D79ULL, 0x6E8F2D13612490F6ULL, 0xAA3390148ABE695AULL, 
            0x6AA3DCABDF31A8C3ULL, 0x8E1D8EB3D7229600ULL, 0xFBB31E1EF1DAEE19ULL, 0x9C02D1D1F6E2029AULL, 
            0x73BFFE9E45281F8CULL, 0x13708EFBA65117BAULL, 0x7CE368A713EC8842ULL, 0x1C9B0B397EC0A034ULL, 
            0x6887652A469C1F73ULL, 0xCB4730C17424F9C7ULL, 0xE8979C12AE23F9F0ULL, 0x57BF9D67BE000FABULL, 
            0x1CDC187810FC6472ULL, 0x9A8B8DA6BC97CED4ULL, 0x51EC8C9E76032CEDULL, 0x46820C147BF112ECULL, 
            0x32B9DB9F4784E437ULL, 0x0B29BE810808C860ULL, 0x09C6F4D42316E5C9ULL, 0x63662F6EBDA65319ULL
        },
        {
            0x8541D337031E1A45ULL, 0x163A99CB2ADBA026ULL, 0x989EAE7DAA52671CULL, 0x04E44E62D40E9E2DULL, 
            0x3B7F196E148E8A3CULL, 0x81FEA5EF4A939675ULL, 0x421468F8A6DF7BA1ULL, 0x11B5FD008DC3A863ULL, 
            0xED7C35C9C69502E5ULL, 0xF3B4DFBF3C4C041EULL, 0x9F45A34B68A14468ULL, 0xD253DF6B96A38331ULL, 
            0x704F9A672845B453ULL, 0x39E7887B088E92CBULL, 0xAEB4BBFCAB7052BCULL, 0x4D34F5337EDE458CULL, 
            0x4FF22073AAE6A6F5ULL, 0x0A0F7155FC0D72F9ULL, 0xAE3C8EE2BD44E2B5ULL, 0x0FB042C087D52C65ULL, 
            0xD25BEF50AEAEBF16ULL, 0x94EA0B1239D29CBBULL, 0x4686EEDB3E085223ULL, 0xBC39F807852944C2ULL, 
            0x848E4DB2D61700D8ULL, 0x36F9AF051A3E459BULL, 0x3BB011677E95215BULL, 0x8DA64D53BA4B5C4EULL, 
            0x4440B0DDC1A34868ULL, 0x11F4695502CF1F79ULL, 0x30B780CA7A14214AULL, 0xA1E4590AE25E6A2CULL
        },
        {
            0x8256A399738CFE8DULL, 0x171E516E4E878024ULL, 0x21396E9614DE373BULL, 0xAB0B7B001884FD1BULL, 
            0x3BADB6A16E260D8BULL, 0xD21E004CDC595100ULL, 0x9AE1396B697CCC6BULL, 0x35DA30EED06ADA4EULL, 
            0xB0FB4DB58D50112BULL, 0xFAB4244559151FE3ULL, 0x4641D803B5CBB703ULL, 0x8D4B95E33361E9D5ULL, 
            0xF0D30DDDC4FC2BFFULL, 0x58369A15FB96BA4DULL, 0xF258EE45459AD4CBULL, 0xAD521D71C2C9EEDAULL, 
            0x206B0A60FD18984AULL, 0xC0468668086D0801ULL, 0x5B9FE4BE4225BEF7ULL, 0x2D61CD1060293356ULL, 
            0xFB53F8379DAEAB21ULL, 0x49C0143624DCA516ULL, 0xCCFE47D13D74C192ULL, 0xC366D348910C086EULL, 
            0x8D079CC4F538031EULL, 0x70ADED4E75114042ULL, 0x489F43DDD3E1903DULL, 0xC00DB0F2533ED74EULL, 
            0x1294D07F20D154F4ULL, 0x1BF778FC0BDBE440ULL, 0x53D2204E7B19C0A0ULL, 0x55D81CBB7810952BULL
        },
        {
            0xF5FBB75497828FB1ULL, 0x3A39E2C9466FBD5DULL, 0x6B0A41D0CF1E7C89ULL, 0xE82044B125DC70F6ULL, 
            0x243CAA02FD5A81D7ULL, 0x60AFA2D051513723ULL, 0x915BC5173B58E6B7ULL, 0xA75C6D134154C8F1ULL, 
            0x4815B6F3E5558363ULL, 0x3F874455242D3896ULL, 0xC84C0D67D51EE006ULL, 0x909955FA76772331ULL, 
            0x43A81E9309CA8E97ULL, 0xF07817778347CD2DULL, 0x274D200F86138466ULL, 0x67705CF7636E427FULL, 
            0xE0B15045C6F69FDDULL, 0x908EE7165A1D7611ULL, 0xFFD74BA9AFEE086AULL, 0x42854D2E42B6F6B6ULL, 
            0x6D3B0C3D6C6B7725ULL, 0x3B2BF1B918D80C47ULL, 0x03C071296291D686ULL, 0x506AA6494830D4CAULL, 
            0xDD5C003724CDBA56ULL, 0x5D661E9757FB9F71ULL, 0x7E68F2F04E23EB9CULL, 0x22A82E2A8F5E46DCULL, 
            0x8B94E487C3B96A68ULL, 0x5809217E2F800C81ULL, 0x3368178905B9A17FULL, 0x1E8CD7ED2C23ABADULL
        },
        {
            0x66D248EA26EA1488ULL, 0x1259EE59D6E3C720ULL, 0x631BC370B324F1C2ULL, 0x032356D950888669ULL, 
            0x21474ADF0A953D57ULL, 0xC5888357D4CD3993ULL, 0x2B8198F7795C9669ULL, 0x9E93B87E37195115ULL, 
            0xCFBB632457BE8FF9ULL, 0x49AE0AE7157B12C8ULL, 0x978C2CAF18CE8F0EULL, 0xE7B905419CC95C06ULL, 
            0xDDCC78B03D382368ULL, 0xBA8F88D79CB4C397ULL, 0x17103BA67E88F76EULL, 0xD6CD2366DBA49491ULL, 
            0x1A26ED24FE0BF3D4ULL, 0xA7FEF6810F924FAEULL, 0xEBF714A03A37A3B4ULL, 0xD651D684524D9801ULL, 
            0x78646B33F3A86FD6ULL, 0xAA30C53B0A5EFF63ULL, 0x2032F408689D3291ULL, 0xE8848A509810E395ULL, 
            0x0BA720BC55E27969ULL, 0xBA49ADF853B0E3F2ULL, 0x38203011272BD81AULL, 0xF5E83BDD83969827ULL, 
            0x3C9235530D3F82E6ULL, 0x176C6F2A8689658CULL, 0x48E208971F07CCC8ULL, 0xE630F5E01C57C883ULL
        }
    },
    {
        {
            0x82727F5DD6124E03ULL, 0x4FB4B52AFA1ED7CFULL, 0x635EDBA4F3932D39ULL, 0x2EE1D91CAFA33045ULL, 
            0x1E1FE8A271458576ULL, 0x6D1E0B41B94642F1ULL, 0x440C2F75927A493EULL, 0xA8E547612CEB8C11ULL, 
            0xABEAF9E75F1989E1ULL, 0x1162A09E58A07F6DULL, 0x3C3650A9F1BDE515ULL, 0x66BD742F2918240BULL, 
            0x43A9402FA5EC094EULL, 0x420F1359C226690CULL, 0x9C258858C5E47908ULL, 0x2590BD1B59CD28DDULL, 
            0x66FA57B785BEA441ULL, 0x6699F6867191BE71ULL, 0x62767CEE5EFA9560ULL, 0x09CCE2B632133046ULL, 
            0xDE8506CAF9377B0CULL, 0xC5127176AB47D4D6ULL, 0x9407EAC4F8F85D0AULL, 0xEA97CC0F4F66130FULL, 
            0x1CB37DDDB0CBFB0CULL, 0xB23BD9EB319B0FE5ULL, 0x1CD617529725B3ADULL, 0xC34B016AE9A73BEFULL, 
            0xF13F70C9D0FB8E4EULL, 0xCCD87CA2EE517A91ULL, 0x7DB5E4FB61851488ULL, 0x81E77187393F2A51ULL
        },
        {
            0xD7D5D9118AF41759ULL, 0x6ED2FA9C472F0B29ULL, 0x1D047EB91B5DDB0CULL, 0x8455B52F1491EBD6ULL, 
            0x43B89FB1E2EA43D4ULL, 0x29A404BB5C6B467CULL, 0x61F2898531C2EF03ULL, 0x7911390897376357ULL, 
            0xDB394B1983EA713FULL, 0xCFDCDE394F7C36E0ULL, 0xCED7F9992009CB72ULL, 0x7A203DFCF4442282ULL, 
            0x53BA5F733A920EE2ULL, 0xDA42F946989ACD20ULL, 0x419C868D677A7998ULL, 0xCD3A32CDBAE4539EULL, 
            0xF994D4B5FB91095DULL, 0xC063E497C7354BDDULL, 0x7BE1EF59ED002C96ULL, 0x448007203DA26F35ULL, 
            0xBE776B605E18F5E6ULL, 0x2E6B287757A440A2ULL, 0xFFEEF690E38EC694ULL, 0x826D7D55CEE922A5ULL, 
            0xC404C5DB86B8185DULL, 0x3EA9E5C267EAECA3ULL, 0xCE5ADCF84975CBA3ULL, 0x8B9C9C1308E4D519ULL, 
            0x7D7058AA86AC6207ULL, 0x28A22C4D242E0E7CULL, 0xB3EDE329DBD1C046ULL, 0x1DF13835F9749DBAULL
        },
        {
            0xDB647CFBFE9F6A92ULL, 0xA2F6B05DBD7BD08EULL, 0xD26E6494BFD98163ULL, 0x27591504630924A8ULL, 
            0x444EF3316812B5FBULL, 0xFD24E31A2C3F738CULL, 0xA74642FAA44309D0ULL, 0xD4CBB4DA6D43545EULL, 
            0x74E2D2C39A0E50F9ULL, 0x1EF2C1375D0B4C73ULL, 0x49214A72E0057034ULL, 0xC62ECDC6DEFFA3FFULL, 
            0x033E417FE1823740ULL, 0x8E3C995BDFF39834ULL, 0xDF682BFF2AA8EDA2ULL, 0x90DD1297562DDBD4ULL, 
            0xF94D0326C96A8A19ULL, 0x5E6DDFB7806D05B9ULL, 0xBECE48E6458A4B7CULL, 0x0479F44A89EFA0C2ULL, 
            0x305C045CB578441FULL, 0x3BECA07EBFFEEBF9ULL, 0x2FCA6CE2923B3CB7ULL, 0x07F990820992B47FULL, 
            0x061DBEA0141E2595ULL, 0xA72D6E8696AC88ECULL, 0x4E777523A0295593ULL, 0x8AE6D7451C59B705ULL, 
            0x9B76B3DC344097C2ULL, 0xB47087596F0DE54FULL, 0x4D8C3935CA6E5778ULL, 0xAC7943E302FAC8D1ULL
        },
        {
            0x7A9DDDFEE3B62299ULL, 0x83F518596A8414AAULL, 0x0FD66C545B77998AULL, 0xC0CC17E3F2F684BAULL, 
            0x4F594E70176CCB96ULL, 0x20EF1A0327456ED1ULL, 0x4C66613210E9E5D7ULL, 0x4D30F42CCEDDC931ULL, 
            0xDB4966517CF5255CULL, 0x1CF98CAD0E3B6108ULL, 0xE39BE56129C35E27ULL, 0x8061A7F01A762919ULL, 
            0x9880DFE0C8AB333FULL, 0x3DE4C2490D574024ULL, 0x327F92064AB92C28ULL, 0x8D636171A71D0DB9ULL, 
            0x6EDBB95E305080F5ULL, 0x7F53203A82AFABF3ULL, 0x277516D59B697C92ULL, 0x785C1F7CA03F5FAEULL, 
            0xE1FA26E262B7E40FULL, 0x99E90188A8D385BFULL, 0xCA937FD38EF2C6C4ULL, 0xF04511867E8C6C37ULL, 
            0xDDD24A62C92CBD5BULL, 0xD0351C6498211170ULL, 0xE9F9E88B7FD9B52CULL, 0x50408FA1E6536C30ULL, 
            0x91875524CE49C5F0ULL, 0xAE21B6ABF0599F3BULL, 0xA77D634BD5195ACEULL, 0x1A09BD6F6028699DULL
        },
        {
            0x1351033438828DB9ULL, 0xFDEB1F0669A9587FULL, 0x5457C3BCE989E853ULL, 0xA0CF2AE3B94BC90FULL, 
            0xB5CBD8C1F85F7D1FULL, 0x2CF39268DA3B712FULL, 0xBABC2C15AADEA533ULL, 0x98B2C7BA446C358EULL, 
            0x0397F8CAE0094B06ULL, 0xCC5EA924F2BDDF7AULL, 0x3C30CA979765AAE0ULL, 0xE5AF858708863809ULL, 
            0xC0821E540272FB01ULL, 0xDE8292BA0109B2A5ULL, 0x5F3DE652DA963DA9ULL, 0xE4EAA799DFF9927AULL, 
            0x17E13E0C37DCED9AULL, 0x72C8BB1953918BF5ULL, 0x052A4B42CB3F0A58ULL, 0x7477E7D15E1660AEULL, 
            0xA8F56D8784370F5CULL, 0xB36A62202C995BDEULL, 0x547C537F34605C1EULL, 0x8BBA82B2B8E0D5D6ULL, 
            0x30FFD0348419C3ABULL, 0x766739927F06984DULL, 0x710DA0EA84C38934ULL, 0x1B38A1204603C981ULL, 
            0x35C58B11EC085783ULL, 0x056259974D407198ULL, 0x2C29602DE9537F51ULL, 0xAF48A6C9F35D6A01ULL
        },
        {
            0xA53FD28D10EC27A5ULL, 0xCF2FB28A5F80D75DULL, 0xED3B2121AEF94692ULL, 0x0640DA4F675DF4D9ULL, 
            0x7BCA047E9ED61A98ULL, 0xA005D196AC5C4A55ULL, 0x84B7630A12FFB992ULL, 0x0A79A2EC0510B92CULL, 
            0x7B79B4B58A811DCBULL, 0x9E696674849514A3ULL, 0x5CF0A82B9F4AB220ULL, 0xC0A363D82D4968A7ULL, 
            0x392D74A2D7890471ULL, 0x98863522286E9098ULL, 0xCE5969C3E45F16BAULL, 0x6F66036F1B5ACDBEULL, 
            0xE463B625849479F1ULL, 0x11EE09CF0BE9C994ULL, 0x53BA2CB4C4DCECB0ULL, 0x4A99A21BCF66EC83ULL, 
            0xC7239D4C9CD7CE00ULL, 0xE62DED785ED8BEE6ULL, 0x545388E5B3637F5AULL, 0x638748AD0FA32365ULL, 
            0xEE0F8C0FD23CC8F5ULL, 0x35F87FBF657CF35EULL, 0x92621B08D11AAC09ULL, 0xC9A38A260653AC55ULL, 
            0x0173005B24307FF3ULL, 0xEC2D7AE978DEB277ULL, 0xFF16E8BB962C8D95ULL, 0xDEF4492FCFD36E64ULL
        }
    },
    {
        {
            0xC100EB989AB651AFULL, 0xA6835774AF3F5BC9ULL, 0xDED07A6CE0889F47ULL, 0x1214CA23395CA926ULL, 
            0xB4A36BC572896E02ULL, 0xF913C70A91621304ULL, 0x6B6DAAA9A9A6AE3EULL, 0x9CFD5B8202B5A553ULL, 
            0xAF3DF7B9FDDB1387ULL, 0x8BF60C66CFAE8E87ULL, 0xC33B82F8A7E6679CULL, 0x88F8AA2C6B3E3686ULL, 
            0xA968A49AB74C3224ULL, 0xE0441F59822E9A7AULL, 0x10BE8387A631E4BCULL, 0xDF83D1B59E6AA538ULL, 
            0x6EB04111B484C5FFULL, 0x9750498352A23644ULL, 0x742A72FB83877C0CULL, 0xEDDD8D2F19C7977CULL, 
            0x9BC6CE17241E7BB5ULL, 0x15D148110B6414EBULL, 0x568E4CA7687F7AF4ULL, 0x7B72AB6E5E413BE6ULL, 
            0x62D39C310CA6AF7CULL, 0x6269DD2C025B0DEEULL, 0x304C907E15C7772CULL, 0x0DDB5D78B226DBA9ULL, 
            0xAB8F163992E7E12BULL, 0x84E74662EFDCC88AULL, 0xE05AB4303DC25D36ULL, 0x13DAA0344E94A246ULL
        },
        {
            0x37D5D4A1B43E6646ULL, 0x0CEBF0261BF5EF5DULL, 0xF96E57A570B50226ULL, 0xBC71D927599A02C9ULL, 
            0x30DE386EC9D46251ULL, 0x3B485EA6BCF31127ULL, 0xF904C71E955A729CULL, 0x086190DCD095D816ULL, 
            0x36DFC77C4BE983DEULL, 0xDE3D00A819437959ULL, 0xBA478D870288C7E0ULL, 0x9614FD46F3879947ULL, 
            0xC983FB60E38B029FULL, 0xD1A8FA45E47A6F50ULL, 0x44913CD2326D47F6ULL, 0xE175F3DEA41935BCULL, 
            0x62A7CE3C3518EA22ULL, 0x623E08BCB74A6ADEULL, 0x483EAA2AC70A3C78ULL, 0xC086A06B05D1DACDULL, 
            0x88492E431C700600ULL, 0xDD6C862770065817ULL, 0xFE2197DEC083CD16ULL, 0xABEF52E55B91B58FULL, 
            0x0FA7CADA603DD69AULL, 0x423213F1BBDF38F7ULL, 0xC0EDFE8919729B75ULL, 0x83B0E855196AD0FFULL, 
            0x23C42D94065A3C91ULL, 0xCC1D76B37ADB98CBULL, 0x5AFE74870E150B92ULL, 0x32EB9B46817D1B84ULL
        },
        {
            0xEFDE70DB259D319FULL, 0x56486B9BD36C5AE1ULL, 0x9C14547342AE57E4ULL, 0x4ED5FBAF7B7F2ACAULL, 
            0x99FEACE8973CBF9DULL, 0x36A5FFCEDB559347ULL, 0x0A771639856D1717ULL, 0x90C2958889DF13E3ULL, 
            0x83C5C2EA49A0A145ULL, 0x79D96502984922EFULL, 0x639F09F034D27901ULL, 0xB8634EC273EEA9DDULL, 
            0xBFAEE44DB7CEE847ULL, 0xD3DD415CA497CBA8ULL, 0xF88D668403D56C09ULL, 0x389E8584187AEC23ULL, 
            0x6A45E437D15E0427ULL, 0x8C7FF9E2218E3F83ULL, 0x53663832EE414EA5ULL, 0x497F4FF9CBBE394DULL, 
            0x19536C032963FB12ULL, 0xB9FE91B0D45B0558ULL, 0x1A43AE3662331602ULL, 0xAC51068AAFD16E77ULL, 
            0xD114BB1F544F2DACULL, 0xF9D99B441DC2EAEBULL, 0xE6EB3E4A7D1CDB2EULL, 0xAA57D94BE5DE0A0EULL, 
            0x762496D066C17A2BULL, 0x954D2AE561016ACBULL, 0xE807EAB304368D81ULL, 0xF59B5AC812816B2DULL
        },
        {
            0x9D642AC8F0BEA744ULL, 0x82E9CB449AB71A85ULL, 0x8A627BC18DC1308DULL, 0x639885725845AEC5ULL, 
            0x17DEF0DD26A3F144ULL, 0x7CE54AA9CD3D39FDULL, 0x9D389E47F8BC3488ULL, 0x70159EA29CEF5007ULL, 
            0x449EBB3250E91523ULL, 0x93C7F1F85C3F0041ULL, 0x73F5D324D89D7DA7ULL, 0x151B9A9495BD332AULL, 
            0x092C44563B1B7241ULL, 0xAC13765C0C2C795FULL, 0x031305A0B066908EULL, 0x86129F2A35E60E3DULL, 
            0x9A10BF2AA7940ED5ULL, 0xB41BC3FC4F7F245FULL, 0x3C1E53BDC9FE9E82ULL, 0x8CC419B9EE93EC2EULL, 
            0x27AA409C0C4786EAULL, 0xE9DFB33941D0A3E0ULL, 0x9E622548AD491A9CULL, 0xA213E2133A37849CULL, 
            0x555B8024547ABA04ULL, 0xD8DAA5CE2C995C74ULL, 0x38189CC70E7CEB4FULL, 0xCD25D1F6730323B8ULL, 
            0xCCC99AF22A712291ULL, 0xAFAD24BC0B5169D5ULL, 0x13949DD4B1D7C67EULL, 0x1F2775F0E4561110ULL
        },
        {
            0x1773F39E2EF10329ULL, 0x532AC88A938EB1F5ULL, 0x4924F7EF3BF7C935ULL, 0x294F7291CDD2316CULL, 
            0x8B596DC9B694DC89ULL, 0xD0329CC076F25668ULL, 0x6595123E4E6D9817ULL, 0x57536C84D3F5F12BULL, 
            0x1F6D2471FF5FCFB6ULL, 0xE6213490C60EAB98ULL, 0x8B0EE52067F18E19ULL, 0x267FCA69206FFF05ULL, 
            0x2B35B51F5C168256ULL, 0x5E60AB9F030BF636ULL, 0x7E9944844F49A042ULL, 0xC0E366DB3E15BCD9ULL, 
            0xACFB8BAA7367DB8BULL, 0x65A7CC94C98C2AE4ULL, 0x572375CEA85B67E6ULL, 0x0270C08210006342ULL, 
            0x4812469897C098EDULL, 0x6D5B733DDD2385A6ULL, 0x545FD4FDB8917670ULL, 0x6585E476BB52330EULL, 
            0x2E35A6C37649C831ULL, 0x49EC76931937A9F9ULL, 0xBF54A3348DEAB3BFULL, 0xC91BD3D0E03F344BULL, 
            0x871F848B8BA55895ULL, 0x09C7017CD500F076ULL, 0x503A7BBF9EA1465FULL, 0x672B45D96B437AF1ULL
        },
        {
            0x043A56DB87D737C6ULL, 0x7D4C9B4D61982FE8ULL, 0x747F8215F8C5E278ULL, 0x5B183233FEAFDFDFULL, 
            0x6CBE02F20B6DD98CULL, 0xED5E049EC95BBCD4ULL, 0x8B59B4BF78A2967AULL, 0xC625BE15FEB65E7DULL, 
            0x3285708CE19FF0DCULL, 0x13D74D9F59D50B69ULL, 0x959B41223B45FB77ULL, 0x0337AA42948B7896ULL, 
            0xA4D370D7A164C452ULL, 0x651CA392D441C547ULL, 0x4AD33D3012C4240CULL, 0x161A72117F575343ULL, 
            0x51319E54D66626A8ULL, 0x4836CD25F6548D4CULL, 0xE49DB5305A2BDFECULL, 0x532CD0EF23E83BBBULL, 
            0xD958CBCADD4DB988ULL, 0xC75AA539333EABAEULL, 0x25B90B71CE6B515DULL, 0xEB9BC841CDDB61D8ULL, 
            0xA6F854545B48DD6FULL, 0x7BB89F3252CEED03ULL, 0xDEE73481980CDE45ULL, 0x0D00C054C66391B7ULL, 
            0x795DE442D48CAB5EULL, 0xE27B6EA2D8120E89ULL, 0x549A5EFAC91D5402ULL, 0x9C66BF9C31AE2F45ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseCConstants = {
    0x52B2FFDAB5C7B69EULL,
    0x139024E378679259ULL,
    0xA096C9EB91426D5CULL,
    0x52B2FFDAB5C7B69EULL,
    0x139024E378679259ULL,
    0xA096C9EB91426D5CULL,
    0x904A9057527E1381ULL,
    0x5B5513B1F10E9140ULL,
    0xE6,
    0x3B,
    0xA2,
    0x15,
    0x60,
    0x2C,
    0xA9,
    0xFD
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseDSalts = {
    {
        {
            0x4099E170E80ECD4BULL, 0xB5A0233F465199E7ULL, 0xED6678BDAC329D91ULL, 0x533F8FB98AB3F2B3ULL, 
            0x5CC61047B6F96CAAULL, 0x59D0B5AF41A43762ULL, 0x14303DBB6DD5638BULL, 0x087CB7FF6BB73A41ULL, 
            0xA5900D0C56EC5D6EULL, 0x782C0ED49BC981FFULL, 0x58DF5BE78428A052ULL, 0xDF8C9CC676D6A561ULL, 
            0xF8A2E2997F963610ULL, 0x9B1BD52223B28187ULL, 0x3892C19E174790E3ULL, 0x7F2EA3AC1EE498F7ULL, 
            0xE97CC301DF6651E3ULL, 0xC6301F9882554C0AULL, 0xBB71299E3A018B9EULL, 0xBEB72685F335D954ULL, 
            0x464612C10DE76315ULL, 0xECEE45ED25962379ULL, 0x234FF26E80AA9FC5ULL, 0x08983D7ED01CA19BULL, 
            0x100C840219561BF2ULL, 0x1AE33BD14A8BA932ULL, 0xD39FE2D822786D16ULL, 0xBCE584603BA5A16EULL, 
            0x5EDD937A308E30C3ULL, 0x4BEE2767899D3B10ULL, 0x5B39D4246EF452FAULL, 0x97E07B408368FF4CULL
        },
        {
            0x24CE704A741DF1A3ULL, 0xD6BE049DD2E125C3ULL, 0xFB223CFFD8B3E6B5ULL, 0x9D92EF5528782E13ULL, 
            0x18F5D09C9ADA8392ULL, 0x480059AEEA09D61FULL, 0x4127D55F24074624ULL, 0x761E1C8DA17B55B8ULL, 
            0x63ECA90478813AA4ULL, 0x0DFF5A31D8C80FC9ULL, 0x501BA8E72F6EA036ULL, 0xA3518BFAE163D499ULL, 
            0xAB4352830B2564EAULL, 0x58EC70EB9B0A601AULL, 0x75A369ECA92F7DFEULL, 0x1117455C9B00F7E1ULL, 
            0x43167FF944C5F5DEULL, 0x905F0A216AE0F593ULL, 0xE34897F27EF38ECDULL, 0xCDA010BAEDAF4313ULL, 
            0x7B6A9D15401CFA03ULL, 0xD3B08F2E41F637CCULL, 0xC15DCAB2EA663BEDULL, 0xBFE4AFC9DEBAF02BULL, 
            0x82C13ABE95BD4112ULL, 0xCB0630CC0BCBAF74ULL, 0x86F453976F13215AULL, 0x060D4818998F2C76ULL, 
            0xAB7F642F8F75B124ULL, 0x3232F2D1DA86D668ULL, 0xF94E50BB41F0F6C5ULL, 0xAB89C554E113C045ULL
        },
        {
            0x8F7A4B294A082017ULL, 0x93FA5FBE41606DB3ULL, 0x8804FFA9545FDBCEULL, 0xB5E5915A49746B71ULL, 
            0x55A1FA11C466B72AULL, 0x46EA656C92879A8CULL, 0x1BDA73C58431FD20ULL, 0x85A3646D13AE461DULL, 
            0x8D50D28A3EB52E37ULL, 0x01C3645D4D4432B7ULL, 0x4B754FD8A37962C9ULL, 0xCF5AAC5F5216CC7DULL, 
            0x671537E030239A95ULL, 0x0A318139B5DBF83AULL, 0xDEB8562479D4A0AEULL, 0x6A414879573EA255ULL, 
            0xF651A875B8F148AFULL, 0x03752A201494285CULL, 0x490C494058AB6706ULL, 0x32B6A8EF9628EADCULL, 
            0xEAE7219DD09EBF9FULL, 0x49BCA39F216696F1ULL, 0x0FCF78C3C18154FFULL, 0x3AF223D279E4FA0BULL, 
            0x5CFFD66CEE1D48ABULL, 0x594568C9C84FBCEEULL, 0xADFD468DB98E2E32ULL, 0xC961034AAF620950ULL, 
            0xE3B870FD240B5C1EULL, 0x665A32AFE979B65FULL, 0x4ED206A908226391ULL, 0xDF3EC4CFD9E4A192ULL
        },
        {
            0xED51AB36FAB6FE48ULL, 0xFF17F3CE00B4551BULL, 0x7E615238EE08C7E0ULL, 0x9ED9311D7A4F7A15ULL, 
            0xA01E9B834DC4F33DULL, 0x9462E8F6E33F7F02ULL, 0xB034B85000292CE0ULL, 0xE3FDFEE0303F5B5BULL, 
            0x656B1F0BF51FF7DDULL, 0xB789B5E746A0B6ADULL, 0x3C367F12EF5EDEF6ULL, 0xF4ED061813B7F9A8ULL, 
            0x5B06B4824B2658DFULL, 0xDBD83C11E36F344EULL, 0x3D76B3DB23A32162ULL, 0xEFFE48547BC9690AULL, 
            0x2F96149678F7BA1AULL, 0x29A01C1141BEFF4EULL, 0xE02F656FAD0505C2ULL, 0xC58BA9650F376800ULL, 
            0xD49C3E876EEC0232ULL, 0x9CF9EDC73914CFEDULL, 0x88C5A6476DEF5A0DULL, 0xDE84FC15E2AF298EULL, 
            0xE85CAD7CFCAAE19FULL, 0x71CF18062F0654E8ULL, 0x79CBCC773047BB6BULL, 0xCD4D04DCA15D448EULL, 
            0xB9BAFE8DE7E58990ULL, 0x10009C114454B658ULL, 0xD4E9EC07BCABE888ULL, 0x6CE55CB08A40F8A5ULL
        },
        {
            0xBB9181A2970EE9ABULL, 0x2242B63D094CE7B9ULL, 0x2ED5B8EC5F6E6678ULL, 0x01AAAB03B1F03DD1ULL, 
            0x81798E98AC1ADABEULL, 0x826E4FB712078B30ULL, 0x4189994BB870A1ADULL, 0x29B6165B866E8280ULL, 
            0x3F64AFFFF8E69D4DULL, 0xBECC56D0BE8A5909ULL, 0x1CA49A83EF8D2A56ULL, 0x970EDA765D63C10FULL, 
            0x087BD3818CE22F36ULL, 0xB42DB08DB630E8AFULL, 0x96EEE11FD0B60216ULL, 0x9DC5D17FC33C1754ULL, 
            0x2555DCCC70E368A8ULL, 0x9E08B7EC52856653ULL, 0x918A258818F2F407ULL, 0xBD82AC849F907AB6ULL, 
            0x0B23A0E4DD10DDE2ULL, 0x39E8B7A649828921ULL, 0xC2A28DE09A3644D0ULL, 0x4D6577C839ABC88BULL, 
            0xF4D643C1C7836887ULL, 0xF5CC90F7F895902FULL, 0x7570305072168F7CULL, 0x00EA17585A9C1BD5ULL, 
            0x69DA9A6BB2518D4AULL, 0xD6AF292D123749BFULL, 0xE42E08D5AC9F0AD2ULL, 0xE919E4769F982856ULL
        },
        {
            0x01BAAC83DAA35A66ULL, 0x8239EDBFA3A2F055ULL, 0xC78946335B25CF78ULL, 0xD5388040114C243BULL, 
            0x3BB68589757B3E73ULL, 0x36DA2DC663CA63E1ULL, 0xA4B1771D37AF4918ULL, 0xAA90CC965AFA6A16ULL, 
            0xE1B919A8DDD20A9FULL, 0xF3F6F24BC63AC365ULL, 0x03B3672588C6667EULL, 0x16EEE00AC8AE04B0ULL, 
            0x9974995D74870086ULL, 0x81E2FD8D6C101DFCULL, 0xAA5CC9DC72D1A133ULL, 0xC9D5B68E93BA18C5ULL, 
            0x47DACADE6B0C8839ULL, 0x890BBD001662007EULL, 0x0B28F1B077FDC070ULL, 0x9B8F8E162E136C01ULL, 
            0x552C9AC577960476ULL, 0xDD4DAAC1D8775962ULL, 0xC24578273E0F4D1BULL, 0xA2C23D24CDE4678BULL, 
            0x17B5F7A1FAEE4901ULL, 0x602CD38564D5F3A9ULL, 0xEEF12A36CCE5E065ULL, 0xAA912AA5BB71D442ULL, 
            0x295C111269918505ULL, 0x5195CE302CA44301ULL, 0xD11D29C0380BF20EULL, 0xFC407C326D1557C8ULL
        }
    },
    {
        {
            0x40CA04136B75C511ULL, 0xA26A151DEF5907A2ULL, 0xA00255AA65D981CAULL, 0x8176AF5A78AE2622ULL, 
            0x4266094B7A728358ULL, 0xC1A41AE67C14D870ULL, 0x1981A62BC22FDD6EULL, 0xC8F2CE00D94F4372ULL, 
            0x81C9D861C742CF72ULL, 0x4AA9208F654D9BFDULL, 0x0AF22079FB2670BAULL, 0x4731FB0311676905ULL, 
            0xDEA66BC701B5D0D0ULL, 0xAF056A239CC904D4ULL, 0xCDCA39D83F0AA27CULL, 0x8DCAFF5A5A68E426ULL, 
            0x516B5D393509D39DULL, 0x6DEA65F6A4E301F6ULL, 0xFCC578C154C34B9CULL, 0x9504071CCFBAB75FULL, 
            0x8F66E967D1BE12E6ULL, 0xB38A2FAD45020869ULL, 0x07DF649317067A44ULL, 0xEE3A2C9648C2A606ULL, 
            0xBA731D3CC8090F8CULL, 0xAC8E61B5701841EBULL, 0x741C27129EB8947AULL, 0x055A88BC4323608FULL, 
            0x751DA93F8C89571EULL, 0x51F67C2C2916CE55ULL, 0xC79185E81E72DD0CULL, 0xE27E7C83FB6732F6ULL
        },
        {
            0xBFCC419B2E6870B4ULL, 0xD430F3A8FB836F6CULL, 0x653A05BDF5436910ULL, 0x7350B9A735AA5181ULL, 
            0xF815B87E5424FB41ULL, 0xA68E67F6DE4E24FBULL, 0x1C84673AA5C364EEULL, 0x7FFFA2E9B0342D61ULL, 
            0xF119924367603AEEULL, 0x313066F3E7764F28ULL, 0xE4806301291588A7ULL, 0x2F8D16ACEE8EA754ULL, 
            0x708BB63F71500775ULL, 0x06EDE466C5DE2249ULL, 0x73F97644BA10FD8AULL, 0xA7D6CB132D40A645ULL, 
            0x1551F102B1AB6C15ULL, 0x175CF21727FA8442ULL, 0x40D1BDBD13E213CDULL, 0x7EE8504135527F70ULL, 
            0x4FAD2A5EABD12AC5ULL, 0x78F5CC75074A35B8ULL, 0x08107BBFE715B8C7ULL, 0x8FE07AE14BF30A73ULL, 
            0xED3EF69EBFA6F783ULL, 0x9CB3E00E8A1798C9ULL, 0x3D239112370D868BULL, 0x6D17B184722D7D1BULL, 
            0xA5598C5AEE709C5EULL, 0x8ABE3209226029E3ULL, 0x04F4B9BBED828430ULL, 0x0C114D5AA4D03D2EULL
        },
        {
            0x8F3127958E4AFEBEULL, 0x5E467598343518FAULL, 0x5A148748DE458BAAULL, 0x39CAB9C417B76D62ULL, 
            0x42AA78D4B8E8E156ULL, 0x2D2A80A4BBC97E81ULL, 0xD2549BD0158CD8B7ULL, 0xBAC25E590D91259EULL, 
            0x5DEF0F95D7AA0B24ULL, 0xC3F8F57C10F5FBDEULL, 0x9798D5CA1B032577ULL, 0x8CC009A331F18534ULL, 
            0xCE610CF01C02DE99ULL, 0xC960ECB03AFF395BULL, 0x75BF8932C9D6F6E1ULL, 0xDBB50DC6AC8539D8ULL, 
            0x6B25B6E2DAA13F29ULL, 0xBC55071EE9142B05ULL, 0x40D608285318678CULL, 0x2E5C9BFCDDC61F74ULL, 
            0x89154BD89D76A0E1ULL, 0xA7A1597022DE3EBFULL, 0x58B7AED4A8BC342BULL, 0x27FF8F92C5250126ULL, 
            0x43E8E84FA451F726ULL, 0x3AF48EDDE7619F11ULL, 0x378B517019D03A7CULL, 0x5E673887040E94A9ULL, 
            0x9F5C74D0934ED032ULL, 0xD3A7991662CFE598ULL, 0x70B2AB4AAEFB5FA8ULL, 0xE6ABD8C8EA94E081ULL
        },
        {
            0x91D1C29E3EB9A625ULL, 0xD10B12194E205A6FULL, 0xCEDE9CDCE1652539ULL, 0x92DC2221868537A8ULL, 
            0x5E2A0202A6500F62ULL, 0x8E16C8291DE4E07FULL, 0xB60C6EDCA328E2F4ULL, 0x6814392750224992ULL, 
            0xC16E82D0BC5FC730ULL, 0xB127B50E618AEED0ULL, 0x5CE3A2A1BE91AB6CULL, 0x5A1065FBA37CA376ULL, 
            0xCB64B16CB90A5514ULL, 0x96506DD305AC0DB4ULL, 0x139EE2CE7194F349ULL, 0x15D2D3EC3FB31D2EULL, 
            0x6F101572496D579CULL, 0x0628BCAC7681533CULL, 0xA436AC0BF606AC9FULL, 0x185D9BF350E915CFULL, 
            0xD91BC42C591D9AF2ULL, 0x6F024262576A2C6AULL, 0x06994B764405074EULL, 0xDA63B506DA671E1AULL, 
            0x44E6410176788239ULL, 0x4E6DA6E4FF6B19CEULL, 0x93883004867EBFFAULL, 0xB81F573D86167F20ULL, 
            0xE74BE32D1498267CULL, 0x432CAFCD604E6996ULL, 0x8DF2626C592B6BC4ULL, 0x2CB67EA31ED16CFAULL
        },
        {
            0x591CD3B6E49DB44CULL, 0xD7EAF0522E50CB2AULL, 0xC0BA19D0C5E7F7B1ULL, 0x5BD9C2B9E305986DULL, 
            0xCF22FF7A9AACB2B5ULL, 0x6F485CBD20F606F6ULL, 0x4A9DD6F80A7B33D1ULL, 0xEBD6EA4B0BCF3103ULL, 
            0x36D22DAE5BD51B7DULL, 0x6C912B8FE44A6DECULL, 0xBD87F636EBDD9D0AULL, 0x0443AD086AD16DCCULL, 
            0x6A8178A4C028E3FFULL, 0x0A39724C95DFF1B8ULL, 0x43A682D37C4F613DULL, 0xD4F033C3A95A66D2ULL, 
            0x33D25EDFEDA35E44ULL, 0xC7724948E448AA93ULL, 0x21429DABE2D83BB2ULL, 0x1A06B31C6708860BULL, 
            0xA76878B0815D2C75ULL, 0x468391172DBD3681ULL, 0x2A2E5AFBEB29F05AULL, 0x5EFB9EC0057A0786ULL, 
            0x98C7C08F80FAEA01ULL, 0x82A6B2E37F1E8C76ULL, 0x6AC78398C5774894ULL, 0xE5476F74011819BBULL, 
            0x26C8431C01602BD1ULL, 0x9816580B7C6219CFULL, 0xAE6F96C53B053CB0ULL, 0xA93E53B172BEF919ULL
        },
        {
            0x88A6EA61D8E5BB30ULL, 0x17B1DBF9884A6EB2ULL, 0xA7CD89A7BF8CE675ULL, 0xEEB46CC6CEF37B17ULL, 
            0xDEAB9C700CD90647ULL, 0x3EEA23B91F0E484FULL, 0x1362D23C7FFE137CULL, 0x2169A53C4F86064AULL, 
            0x83664F9E03868317ULL, 0x6793BE2B4C0D8A0EULL, 0x61006908376EC068ULL, 0x89AC65705FA7588EULL, 
            0x3E3EF588CA5F3363ULL, 0x6928A6F84EE507B7ULL, 0x5517EDB9436A4E81ULL, 0xB13A37633031FDC5ULL, 
            0xE3E067F86E96C8F3ULL, 0xFF18AD1D001AF32EULL, 0x0A860E7C1A6809E5ULL, 0x9E781C09E49C9F60ULL, 
            0xE2B66740E4DD20D1ULL, 0xE34F33DF270F71B8ULL, 0x5DCF5686FEBC8414ULL, 0x18AE71260D5B5287ULL, 
            0x4B3853520049171DULL, 0xC335F14CAE253B47ULL, 0x36100C48B0415AB7ULL, 0xCF1B8FE65E99256DULL, 
            0x94AB96CE68DDC64FULL, 0x1AF0623054DDD7B7ULL, 0xCC227B69D832EB7FULL, 0x0E65DF820BFB4AA0ULL
        }
    },
    {
        {
            0x69BE32B06CC4097FULL, 0x57CE8E56001A8D9BULL, 0xDE7F808DD91B43E8ULL, 0x9AFAC8FF239293D1ULL, 
            0x18C055859110F3C3ULL, 0x7848464C73C0EF51ULL, 0xE045B9FDBC966664ULL, 0x0967A172B452AA42ULL, 
            0x092858340EF0C27FULL, 0x1B1A8D8DC342F84FULL, 0x7976993EB96483ABULL, 0xDC54080EE0542529ULL, 
            0xDAE75F4C6955404FULL, 0x81CC3D189C930C00ULL, 0x4B7C713945A4601EULL, 0xCE16796FA5A60E05ULL, 
            0x28A10E8A10B98139ULL, 0x155E26DB9E82D8B1ULL, 0xC7AC9532A33B8B16ULL, 0xDA1D1812B38FAB81ULL, 
            0x2E10EC85C6F07F84ULL, 0xD1E1F9AABC0A1CE4ULL, 0x9404D4E22B8EC9ACULL, 0x7BD36B8AD52EEAFAULL, 
            0x8D73777C844DB48DULL, 0x274FB393B5B75E79ULL, 0xEA008F5F337027D3ULL, 0x3024B4DD66F191F8ULL, 
            0x209D5F45443FAB56ULL, 0xBE9222C1E2F9D6A5ULL, 0xB0375EA528A975EAULL, 0x815CAA11E9CB314EULL
        },
        {
            0x4DBEB7AA47E0E305ULL, 0xFC7C17A5C52CEFA1ULL, 0xF85492AADAAEC311ULL, 0xDF7232CE6365B52BULL, 
            0x41364D9DB588E8C1ULL, 0xA3EAD4881B2505C3ULL, 0x7A26921A6F9C762BULL, 0x4398CAE8952E95B1ULL, 
            0xADB32C57084E9E88ULL, 0xEED18751945FE5DBULL, 0x53A85944A6E8697DULL, 0x1C734E00768049B6ULL, 
            0xC168010BAB860124ULL, 0x60483E6CC7AE6E63ULL, 0xE3CC2BF6B440BB89ULL, 0x9821AEA09B499306ULL, 
            0x41823BC7C17FCDFFULL, 0xF76D0987F76B41EEULL, 0xA400B652B1EFDEB4ULL, 0xFCEEE2BEEFB28251ULL, 
            0x3151B5866D8FDD66ULL, 0x93A4B7776DF1447EULL, 0x74A4D9199B3924CAULL, 0x0CD4A6EB5A4AF653ULL, 
            0x157C4F0C7BB00E74ULL, 0xFA0D7238676128F3ULL, 0x227F5AE6F0D6866DULL, 0x8D032F3E1D0DEE01ULL, 
            0x64EC0633780A89A9ULL, 0xC61AB1E17826DE7FULL, 0xCC4B8219B094C0AAULL, 0xE8E0CAF4A1E540ABULL
        },
        {
            0x878E73F8A78DC006ULL, 0xF2E2FB0147C159D1ULL, 0x8D95F9B78E71DBA9ULL, 0xDFFFF50024C1D4C9ULL, 
            0x94AFD414B775075AULL, 0xF587B67F2D569138ULL, 0xD6ED0533A8DDDE96ULL, 0x8022A15D4D6F2657ULL, 
            0xF005654FD829EAC5ULL, 0x9BE57705EA64FD17ULL, 0xFFC95DE945F56FE9ULL, 0x37D043F52855E081ULL, 
            0x6C05C83957177E55ULL, 0xE5EF9D5C613B33F5ULL, 0x24EEC603F75AB58CULL, 0x7B66D7E9643E0740ULL, 
            0xAD384F3479D1132BULL, 0x76C3A1AE3D5F2FD2ULL, 0x974FB142DD5F7B6CULL, 0x06680E933F6F4FEFULL, 
            0x3736B7AB89B7F49AULL, 0x4638716EDB55BF24ULL, 0xEF3E6BF13EF9D1A4ULL, 0x6215E056ECC46CE7ULL, 
            0x54D6B25E8AF89265ULL, 0x8CB80B284CEE6412ULL, 0x7BAE162E183287DFULL, 0x47921B12392AF268ULL, 
            0x43DA7C661BB45617ULL, 0x7AD28F6297C8449DULL, 0xD2976AD924D3E7DDULL, 0x047A30FF39220C21ULL
        },
        {
            0xC3F03E99D6CCBBC3ULL, 0x278CB15133E5B166ULL, 0x0836F36B6F9C18A8ULL, 0x31800F14701F44DCULL, 
            0xCA537D7C2DA23694ULL, 0x36F2C2D37EBF493AULL, 0xF1AD3FF827DC0A65ULL, 0xB6F6CB4D223A7761ULL, 
            0x03C677C1DC96800CULL, 0xBD7B7FCC3A88BA0AULL, 0x8810D2621D56BEACULL, 0xDB5A581FAD3755D3ULL, 
            0x4FBE4FA003336477ULL, 0x890CF8FCEBC70709ULL, 0xD6ED9ECC761FB912ULL, 0x7E1755C09567AB86ULL, 
            0xB6AA27A3792B8A02ULL, 0xA313EF14F2E2A5ABULL, 0x98DF6A70086CEEC0ULL, 0xCBE0B265D4277011ULL, 
            0x9FA31583F83976EDULL, 0x2D3A06D68114F192ULL, 0x54FB45E215C585D2ULL, 0xBF6DE75F6B240E63ULL, 
            0xD2B3DC357C6E4800ULL, 0xEB5FF2F1D477733BULL, 0xE5789D402B36F119ULL, 0x5A565569D1C18E84ULL, 
            0x5312380B9E661050ULL, 0x243C836901226EE2ULL, 0x6A8917FC5385D2FDULL, 0x4162C3DE30CFE39EULL
        },
        {
            0x6AEDFECBE6F8FAB8ULL, 0x8311E659122638C1ULL, 0x7DD3B1B9494F81C9ULL, 0x563CBB538421D36DULL, 
            0x06CA22AA5DE9AB6BULL, 0xFC403AFC69C9B3AAULL, 0xEC1C7E3CBA4C75A7ULL, 0x4EB2D1DDB6FB877BULL, 
            0x0131EDB5249720E4ULL, 0xD7E6D889212168C4ULL, 0x966E7DDD902EC06AULL, 0x6AA7A22FF7D596F4ULL, 
            0xA8B84A55B51C1531ULL, 0xADCB1792F22CB38AULL, 0xD9A666543221FE04ULL, 0xD0D24E9FFF5C6349ULL, 
            0x17863B3E3C631C89ULL, 0x96325F0F435B9EF5ULL, 0xC3FA851FCC3D1599ULL, 0x67C8C34EC9C39B83ULL, 
            0x0782A73642FB9207ULL, 0xDC584F1FF908E9D6ULL, 0x7E911382103D2EA2ULL, 0xDFA71C70E6B85173ULL, 
            0x4F484E543D36E517ULL, 0x96A9DA975052F496ULL, 0x7738BCD8BC43CBADULL, 0x4F624192DB1E382FULL, 
            0xF41C2B6E56778940ULL, 0x00C4AE7ED545A3BAULL, 0x26849C01B8806F6CULL, 0x4862910E9B47DCE6ULL
        },
        {
            0x3B0E25C8724859C7ULL, 0xF47B49201A5ADCBEULL, 0xE22B4378BC325AE0ULL, 0x390F9668647F6BD7ULL, 
            0x3ACDACB30A1C43D5ULL, 0x61A87D4937A11284ULL, 0x19FC68914AC22B8EULL, 0x101236901F34F023ULL, 
            0x9A1DAC354578E0EEULL, 0xCD244E29C0E4574FULL, 0x49E2BCE59F509BCAULL, 0x4EDC49510DC17014ULL, 
            0x03A4E11A2A3F4B80ULL, 0xB9AF734445D1EEBAULL, 0x541115D4BEBCF7DEULL, 0xCCDD4520E9436DA9ULL, 
            0xB0DAFDEC82A46114ULL, 0xEA0D69FACBFF6936ULL, 0x3C80D8A54333FAAEULL, 0xCCDF8A5B314CE587ULL, 
            0x88B83A7C40E3A909ULL, 0x2F376CD073EE0438ULL, 0x28A97B033143E4E2ULL, 0xA8BDF3CFD3CE2446ULL, 
            0xC6A5A43256AFA80DULL, 0xB548C840F1FD534AULL, 0x9F067342F908F50EULL, 0x4097E83C6F1A0751ULL, 
            0xCC51ABA37888192FULL, 0xCCD694433D65B13CULL, 0xA929C07496B74B6DULL, 0xFFBEC305D6C7414EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseDConstants = {
    0xBF759AC6E49110D2ULL,
    0xC4F15D17B119B815ULL,
    0x805D8EC812BAA531ULL,
    0xBF759AC6E49110D2ULL,
    0xC4F15D17B119B815ULL,
    0x805D8EC812BAA531ULL,
    0xFA5A84D7EBC1F2DBULL,
    0x4F71B8124D0CC8BAULL,
    0xC3,
    0x4F,
    0xB0,
    0xD2,
    0x12,
    0x58,
    0x9E,
    0x5A
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseESalts = {
    {
        {
            0xD6BB9BA3D1E3C523ULL, 0xC7E061CEAE5F3F82ULL, 0x0610C21BFFEAA35BULL, 0x0CB88D2B1BD35805ULL, 
            0xF462CC71F7E44047ULL, 0xC0EA435CE289A974ULL, 0x2BFEC39494910538ULL, 0xA0B5DB9A1F2646C0ULL, 
            0x27C038E0B56BA493ULL, 0x516EA9EC3C580B52ULL, 0x4019CDE596BC9EABULL, 0x1305076F3AF7DDD8ULL, 
            0x8DCCF68FECF9B28AULL, 0xC65A1B225AFE6091ULL, 0xA87D750641DBD9A7ULL, 0xC801CD1B43D2D75AULL, 
            0x06A498B294EF7AC5ULL, 0x3ACF2C1020E15448ULL, 0x255EDD45F5ACB15CULL, 0x47C2F6FCF122ACB5ULL, 
            0x82F7B31C5B9A4117ULL, 0x149CC49ED9989A23ULL, 0x2B3D89F889B46DDAULL, 0xB1AF48FAC8FE298CULL, 
            0xF1923EA9B3EF065AULL, 0xEB4C0081A6024098ULL, 0x51029F0366AC0F08ULL, 0x6DABB4F6048BC368ULL, 
            0xE69355BEBE1D474AULL, 0xFCE5DA7EEB0079C4ULL, 0xA5145FF40AA0F2CFULL, 0x6C26FDECB8633F65ULL
        },
        {
            0x75225E4CA46D8564ULL, 0x8817810AA308A613ULL, 0x0F2444893CEF4A0CULL, 0xA286FDE113BC787FULL, 
            0x4113201168077364ULL, 0x0A5A9A611C284F7DULL, 0x419512F8E5CB10A7ULL, 0xF450CAFBC75D6E7EULL, 
            0x8CB6EEEA74D7981FULL, 0x3EDF2DDFEB4761ADULL, 0x3FEF81513DD2690AULL, 0x1BC954AD0EE5D901ULL, 
            0x97BA6D1699EE2737ULL, 0xB8CC4B8ED74ECDE4ULL, 0x9DD0BA67EF96113FULL, 0x162365EC5624121AULL, 
            0x1B34752448031FC3ULL, 0xB15A4DEE7979CBC0ULL, 0xFFABDBB0AFED3817ULL, 0x6898C7CD39397281ULL, 
            0x7E5A0FF468352D50ULL, 0xF118969A9288B11AULL, 0xBD809DAFB1D6A35CULL, 0xBCFF196138638107ULL, 
            0x43DAFDB9D1214689ULL, 0x335CCCD4AE9EC4EFULL, 0xCA58444AE8AC5E77ULL, 0xE44CC0959CFEC58AULL, 
            0x9F44C466B1E45656ULL, 0x10013BC09C0C8888ULL, 0xD34689CB31BC3586ULL, 0x8F9C90D875A50A87ULL
        },
        {
            0x0BE19BF418037AD9ULL, 0x5C31261243C1E92DULL, 0x6C12B91099259E08ULL, 0x63FA542DCE3F4332ULL, 
            0xE911A1E9CE34D6FAULL, 0x478228D275E0F12CULL, 0xE3D1FD4CF7A203CEULL, 0x292701953189196BULL, 
            0x45A2FD08CCB28490ULL, 0xD1D5925BFC182BBEULL, 0x194C657CD3643468ULL, 0x7AD438A6BEC62FE2ULL, 
            0x3FB6FDAF2E210E46ULL, 0x15BD259C4BE5F268ULL, 0x907292B36D4D5892ULL, 0x3F211E332BD345A4ULL, 
            0x6EE4DD47E9D6E0A1ULL, 0x0FF4D0787A373B82ULL, 0x78DA6F76393671DBULL, 0x66EFE42F8C6612B7ULL, 
            0x22EFDF117BE5A6B3ULL, 0xB3535CE2E5D3E713ULL, 0x37BE44DA095BACBFULL, 0x1991C15661697875ULL, 
            0xC6CBE3121B5EA126ULL, 0xC7206D57733434B8ULL, 0x6BAB07EEAA01360EULL, 0xC5BE7454A5D854CDULL, 
            0x76DB6D050E20CA98ULL, 0x9CD3AA757A8AF294ULL, 0x730F4ADB690BF428ULL, 0x958CC73723517E99ULL
        },
        {
            0x01F7485D94A996F8ULL, 0x0A2700E58A696614ULL, 0x3654DA462CC467FDULL, 0x8D60F8B217736DB6ULL, 
            0xC53AF6E7E24860B9ULL, 0x227C68F8C6CEAA47ULL, 0x6F40C581A3236037ULL, 0x2BB185277B32AE80ULL, 
            0x20FF4CE779E9F079ULL, 0xDC96D191DE074AFAULL, 0x7F4A093A2293FE72ULL, 0x3D898F664EA7F4EBULL, 
            0xB5B446A309809890ULL, 0x2A2BD70E3C092285ULL, 0xBC5E4D2129EE04DCULL, 0x5613940865AD0B01ULL, 
            0x2F9D64438A8CD493ULL, 0xDD4189130EA3E91EULL, 0xA01C76AA9ACB479DULL, 0x1CD619E88778A965ULL, 
            0x60C1B46BCBE71214ULL, 0x988C0BDC0E398D0FULL, 0x026FFAAF4722EE0CULL, 0x0D42285A2FDD5916ULL, 
            0x73B84DB0E11C79F5ULL, 0x764638BCC986B682ULL, 0x382B3EBB1D759CCBULL, 0x12DA226CD34D6AA3ULL, 
            0x54B5FEA512DA861BULL, 0x64CE6829EE2C6172ULL, 0x0F2C771BEDF7B25FULL, 0xEC9A405367814560ULL
        },
        {
            0x0BDAD77604CBAAB1ULL, 0x19D4EDD356BBCF9CULL, 0xBAD80BBE10090397ULL, 0xFB432F798FC34697ULL, 
            0x3972444C16CA6894ULL, 0x1332FB0668A4339EULL, 0x5C6363FF5D531205ULL, 0x2A6B7F5AACB0BD3EULL, 
            0x6C972A7E1FC68D2DULL, 0xF24A872798C2C54DULL, 0x7AC516EFC5DFB7C3ULL, 0x4D04028AD7086483ULL, 
            0x60D2BC8AA7523B0DULL, 0xE7D69F9C6E1A22E0ULL, 0xAD0D32A94155780BULL, 0x5E95FA4A288F950DULL, 
            0xE44B66CB64BE9D61ULL, 0x5C6275486952887EULL, 0xC9D36CB4868EFBD2ULL, 0x37789B780FDB6FBEULL, 
            0xEC99804226DDE258ULL, 0xCB8FC45AF30A54B6ULL, 0x7346CF396F035D4FULL, 0x5F2B4BBE61650A97ULL, 
            0x085AE63408F917F0ULL, 0xE502062741DA7334ULL, 0xA9CC1610359BECC0ULL, 0xDF7ADF7E10109C28ULL, 
            0x4BCC4AE357C68B8DULL, 0x932E6E36ED1E8AB2ULL, 0xD9FECEBB730FCCBCULL, 0xB21EAEBA289FC8A8ULL
        },
        {
            0xD3A27AADEE675E31ULL, 0x7399865ACE462CF1ULL, 0x66AFB0811E4EB2A7ULL, 0xC5DB9CD822EC17B2ULL, 
            0x69DAAFF781947767ULL, 0xB7786B3DA05A54DFULL, 0x75D1214D54652EB3ULL, 0x3E99EEC5F3DD7E66ULL, 
            0xAC81AD7DEC4D9FF5ULL, 0xE73BCEF475893A40ULL, 0x4995EC788BAC6FCFULL, 0x1E33F5E61C69B766ULL, 
            0x368A069DBED347F6ULL, 0xB241FB7FEB1FB322ULL, 0xC794CCAE2FC70C0FULL, 0x4E056A750E650DA7ULL, 
            0xF8CAFC9260B870C2ULL, 0xEC5B5CFB2FE80D07ULL, 0xA3B400BDB54087AEULL, 0x3DC68063444E34C9ULL, 
            0xACEF6DF53E0D7CC1ULL, 0x15078ABD57014508ULL, 0x66AC977E507C6D32ULL, 0x9AB1D79A3968E69CULL, 
            0xAD1AADC51E65A330ULL, 0xCD69FFBF0ED12BC1ULL, 0x6176C9FFAB968A77ULL, 0xAAA6663D48E124EBULL, 
            0xBBF8589FAB8DC615ULL, 0xDF46F2554ECE53B1ULL, 0xDAF52DC76ED9C3C3ULL, 0x45C7B77CDC440B1BULL
        }
    },
    {
        {
            0x2FFFD169A4C3529AULL, 0xFA78CA720F358B37ULL, 0xAC959E04D7DF680DULL, 0xD08E77A2AD7DCBDDULL, 
            0x857ACC6557F00A68ULL, 0x122C8A16F8652DF6ULL, 0xEA32F57503EC4B5EULL, 0xCCD73248E2BDFEC1ULL, 
            0x7ADBB5FC19BF4067ULL, 0xCEFC94A2C6097638ULL, 0xE19801763F772808ULL, 0x34BD1A09E3DBA23EULL, 
            0x7EDEB54660F1D1BDULL, 0x14719D7571DB00CEULL, 0x84CD3A5DC8EE45A5ULL, 0x4BE92DA71A6787CBULL, 
            0xC45E6BE1F874CD32ULL, 0x798A477FD56D0CCFULL, 0x2C5466A79BDA707FULL, 0xCC0C56A5F3A47D2CULL, 
            0x1C2E3774769FF709ULL, 0xC2B0A7FAA38FA291ULL, 0x59EB40EF6091007DULL, 0x547D22029F66490AULL, 
            0xBF1346EF852566F2ULL, 0x2169EF2149EA4859ULL, 0x4F69DA148B019B76ULL, 0x9D157612425F395AULL, 
            0x2A385BA86FECEA78ULL, 0x32063623FB91567AULL, 0x1C22CFCDD822C06AULL, 0x71792112BB60D16FULL
        },
        {
            0xBB6BE8917215FEE7ULL, 0x0B4CFC0BF55FA009ULL, 0x684B28A511893796ULL, 0x04974F4AEC00639BULL, 
            0x73BE866BEFBB7606ULL, 0x91E3A4E255908870ULL, 0xB5DE18FCB542E026ULL, 0xC99E2CF8A32EC632ULL, 
            0x4B28269D90C34396ULL, 0x15FB7643A95E97E8ULL, 0xC8F4CAB7EB6885DCULL, 0xE83D204BF2490304ULL, 
            0x8BA8DDB2EAA3971EULL, 0x0D5662FEBEC36D1AULL, 0x97776D8E731E68CBULL, 0xF6C1C86299B57E6AULL, 
            0x53D8E2D551AB05B0ULL, 0x4EFC4A1D1E188820ULL, 0x0AE4FFD0BD9B559AULL, 0xCFD34125E98678CAULL, 
            0xFD6B4178F6B05C9DULL, 0x9A299BE92CF72576ULL, 0xDA7A27333C41A505ULL, 0xB87B2A1CCDD0B987ULL, 
            0x2F8126E3E8644185ULL, 0x8F0C33A16468D347ULL, 0x2547CC47EC2C0025ULL, 0xB731862F0D413B67ULL, 
            0xF0B60B93F7FD9897ULL, 0xDB77289246D54B9CULL, 0x356E5F3F7D5E60DCULL, 0x418045DBDADB8B44ULL
        },
        {
            0x2DBEA8D1DAE905D3ULL, 0x6A0DF11332A1E7C9ULL, 0x8675EAAE19FC22ABULL, 0x408213BB77403985ULL, 
            0xE211711902312184ULL, 0x40115111F4A836E8ULL, 0x65A95AAADD2511BCULL, 0x4C77E5BD873866C6ULL, 
            0x6674E0241A9F9A1FULL, 0x8C8D8674E990D0EFULL, 0x5DFC7570A4BBDCC2ULL, 0x0493583C00F6E666ULL, 
            0x23F2A4359F45BFE3ULL, 0x56F20ECBB6A97AECULL, 0x1322B86DAD140950ULL, 0xA29FCA185D29B6C4ULL, 
            0xCA17D002A26B06F9ULL, 0xE7605433951C9E86ULL, 0x0878DC05022C6C8DULL, 0xB725697BAA91A63EULL, 
            0xFD8D1D18565EC5F0ULL, 0x35A6CA101BF28E14ULL, 0x5D33D0BB127FEEA1ULL, 0x2211996F16CD87A4ULL, 
            0x39A35024B5FD71B7ULL, 0xE0682B0EBA0052E9ULL, 0x1D622A29EF147C70ULL, 0x21A717EFC9DD9E39ULL, 
            0x3721E0EF467FCDC6ULL, 0x62D5B08593C794F2ULL, 0x4DC4F64625A5383CULL, 0x8A59FAE582699F56ULL
        },
        {
            0x4A48A499258D5D18ULL, 0x56B3FD9021DB8E3AULL, 0x215AED33DF66076FULL, 0x09A51516687679E1ULL, 
            0x6E3112D0051E353DULL, 0x17C15EEAB7E22FDBULL, 0xE99336A635297C5EULL, 0x97B65E97124F106AULL, 
            0x809AECDACC5058E6ULL, 0x5E892E8CAEBB8311ULL, 0xEBCBA4B95ABEE215ULL, 0xEA946326C34DF61CULL, 
            0x7D45FD1B8FA0A112ULL, 0x5A7CB0B8670DE1FEULL, 0x368D2BC3FEDDF9D0ULL, 0x8DCA02EDD35C3EAFULL, 
            0x8F1DAABEDB64B23EULL, 0x6A880FFD6140CA58ULL, 0x0AE4222D3F982DBDULL, 0x464C4BA6D69C91ECULL, 
            0x7622804DFD3A9965ULL, 0xFF9CF4FD4D496487ULL, 0x33C1B46151FAB837ULL, 0x11C08F033CD8F5D7ULL, 
            0xB7D7F0D4202FBBF1ULL, 0xBBC5E3A6937D219BULL, 0x8D0EECA39CE0BF84ULL, 0x786B3E5CC58EFEAAULL, 
            0x9107B1B9BB9CCF86ULL, 0xE81962FF0FB3D422ULL, 0x45B91A0033646F39ULL, 0x2C08E57A7C270FF8ULL
        },
        {
            0x214A203591D64F80ULL, 0x57D064BB900AC46AULL, 0x5CA91234416F9F8AULL, 0x6DBA1145380CA835ULL, 
            0x4A4302F430BAA00BULL, 0xA921E24EBA2B30CDULL, 0x712A36209650A932ULL, 0x8FBC52CD9AB5F930ULL, 
            0xE91818734CB9EEF0ULL, 0x090D206EF98F409DULL, 0x192860561E1127EAULL, 0xD96E0B4ABA26D03CULL, 
            0x993E6D9F37A06FF6ULL, 0x426A3975F2C83117ULL, 0x9A820CAFBADC6F5FULL, 0xB1EA221EDC7F13C6ULL, 
            0x3CAD7766903A5294ULL, 0x4C69C9E25CA2CDACULL, 0xEF8407D61309B854ULL, 0xC8F3EAE229817419ULL, 
            0x95D5E24566D5BFC2ULL, 0xA09D74760B5AB7FAULL, 0x731CC814B67279D6ULL, 0xB41322D1A5E982FBULL, 
            0xEC2B643A61BDC4D7ULL, 0xF046AED69158BADFULL, 0xB4727652F521FF31ULL, 0xB196F335C287CFA0ULL, 
            0x761BC848B1C7A861ULL, 0x7566FB833DC975E0ULL, 0xE1D210BC47C21D70ULL, 0x007C95AFE9DE105FULL
        },
        {
            0x4ACFE76B25F0EF03ULL, 0xCB7BEAED1111D843ULL, 0x2D2D5E83D477BED7ULL, 0x053B869EE26C84E8ULL, 
            0xFA2B754851974E2CULL, 0x9AD3890DAC668700ULL, 0x9CD40C75CF6093C9ULL, 0xDCF7E8BD4BED8356ULL, 
            0x5486AC0E9FB33E4DULL, 0x37ACCD39B407FBE6ULL, 0xF80116B6557CCD8CULL, 0x5039E163DB019892ULL, 
            0x7D5ABE0C829FCEF4ULL, 0x167636D565A03674ULL, 0xFA28884DF2C8E972ULL, 0xCB2060B27E98822CULL, 
            0xFCF60AE7DD01A182ULL, 0xF24C7E8E8891490DULL, 0x82B889F1AAFB96AEULL, 0x812A11D5C631A91AULL, 
            0xB71B13A5C1E48091ULL, 0x9650B2E7E61FCBB3ULL, 0xDD75E9803950057AULL, 0x67F1446F90318183ULL, 
            0x7CF3AAEF1062745EULL, 0xC109D82F45801481ULL, 0xFBE5A9B3B9E77C7AULL, 0x208EE800E2DCAB87ULL, 
            0xE874D026AB3D6541ULL, 0xED13E9AB4E04BE71ULL, 0x25049E738EAC493CULL, 0xD192D437F8E2943FULL
        }
    },
    {
        {
            0xC72DD48C78E5D019ULL, 0x832F1A394D426ED7ULL, 0x636F0826A4C2907FULL, 0xD91A5D48CFFD201FULL, 
            0x3053DE8FE37C376FULL, 0x216F8C593DF8A523ULL, 0x267729865DDC446EULL, 0xB6FE96C051E85343ULL, 
            0x56564859B99AA791ULL, 0x6D39FE050D43EED6ULL, 0xA7EB026512612FAAULL, 0x19AAD0214EA92EFBULL, 
            0x02B889F86E35A0F8ULL, 0x472A4EBC74F81200ULL, 0x59B43DDFDEC34E39ULL, 0x0B6D88CB16FEC329ULL, 
            0xDF6E178166B73268ULL, 0x4364ECF4FD0FB958ULL, 0x3834D046799C5D6CULL, 0x5547D528427A73F6ULL, 
            0xFEDBE1B1C6E044B5ULL, 0x6314BE5DD8C780BAULL, 0xF98F12326E0A0AADULL, 0xE9FF4AA36308D000ULL, 
            0xF39F29D1DB951CF4ULL, 0xB8F59D9837B6E8F3ULL, 0x50CFF0EEC2EFDE8CULL, 0x78BB9F1097F60A1BULL, 
            0x70A5A89FCD53AF73ULL, 0x05E198FB88BF1D3EULL, 0xEA086BD1996963F3ULL, 0x246918E562955393ULL
        },
        {
            0x5932A2301501BC74ULL, 0xCB51E912FF1B4B52ULL, 0x29C75BC714D35086ULL, 0x75A48B4B1D6C62F5ULL, 
            0xE7B0B92459A3B930ULL, 0xB32D04195A6AC5F5ULL, 0x0790C0F31876B89CULL, 0xA184D6F749F567D3ULL, 
            0x84EFC894EBCA7C17ULL, 0xDC6E188E0A8823BDULL, 0x4E23EE9EBDC4BDE9ULL, 0xF9B21840C76D99F9ULL, 
            0x1DA0BB8CDC159F3BULL, 0xB754301A653D7A4DULL, 0x9A69992BA088C536ULL, 0x111B5B81E9168DD6ULL, 
            0xDEC320DB796303B9ULL, 0xF4A2D4036E617B9CULL, 0x14834F418AAF2C85ULL, 0x9FC7DA9198D1F4DEULL, 
            0x60BEEE53DE40A90CULL, 0xFABF32B1063B019CULL, 0x8C72E270184E1C76ULL, 0x5E9A625EB84ED366ULL, 
            0x3A8378B48AE4CAFBULL, 0xF39FF30CD31B9997ULL, 0xACF365AA218995B4ULL, 0xF5090B8C81836860ULL, 
            0x1DEBB401EEABD1C4ULL, 0x6BB72C86AC3CEC45ULL, 0xFB7658FAC5790A01ULL, 0x020941D297340B42ULL
        },
        {
            0xACEF059DC6A81632ULL, 0xB79E5C67FF0B6D85ULL, 0x4CF2CCB270047832ULL, 0x8FA9F1EED311667AULL, 
            0xF212F04746CF10C9ULL, 0xF57B42C2526AA315ULL, 0x2408C327EF2EF7D0ULL, 0xDFC99004AA9DC84DULL, 
            0xB1B0079710362F9EULL, 0x25EEE696A9E6B09FULL, 0xB88C54443EFF9192ULL, 0xC0E12EA8224233F6ULL, 
            0x52567E53F44ED23BULL, 0xE496D8ABCD4AE69FULL, 0x113A73E8125BCD53ULL, 0xF02424E929DAB17DULL, 
            0xA235F3594791F2D5ULL, 0x9BDE27B342C66561ULL, 0xA5F2E857B9C4C714ULL, 0xBDD600C6C9A9E594ULL, 
            0x446BFD0AEA18ACB0ULL, 0x58B00C4A62D2BA2BULL, 0x3E1DCB6CF6B64EC1ULL, 0x07471E77552A9156ULL, 
            0xB617E125697DB687ULL, 0x74D4A657DEBFB8CDULL, 0x514C562AFC2BED7DULL, 0xC5E7AEC564A9534CULL, 
            0x4211ACE47571830EULL, 0x698C511A3013DA5AULL, 0x4828465AADFAF201ULL, 0x0BBEE97C21098C28ULL
        },
        {
            0xBB162990160F9E71ULL, 0x860D866053200D8DULL, 0x07F77FA38CA91880ULL, 0xFE288C62FD5B6F05ULL, 
            0xC4901F6833C4469FULL, 0xA06BBEE0C1C656DFULL, 0xD8A243AD03B68B5CULL, 0x38093F15FBE09F2FULL, 
            0xC5451B17DE5276BAULL, 0x554B4FC16CD6CB6BULL, 0x28FF66852BF7EDE9ULL, 0x0E92019CA37E95ACULL, 
            0x38016460A1DB4389ULL, 0x78C972F7DD69B99AULL, 0x55105C3EFCF5813FULL, 0x64CF54A41A64ED0CULL, 
            0x77D4305FF04542DAULL, 0x3B607825374E9754ULL, 0xB70524A8BD231205ULL, 0x7B17A75D90B7FEFBULL, 
            0x86BCF78764D3296CULL, 0x8C69C06E5797CE11ULL, 0x1A3FA2AA57B69F93ULL, 0xD5E1B3199591491DULL, 
            0xB4CD66AD46A0B909ULL, 0xB044CFC5953A2012ULL, 0x508DB75256F5B9B8ULL, 0x32CE117A5EDA337EULL, 
            0x9D0F66FF758B6B06ULL, 0x1A1380527C759D7AULL, 0xA1D6F8DD0D626C96ULL, 0x8812633BD19602F2ULL
        },
        {
            0x3AA18A2A9EA19A0EULL, 0xD9882CCB60B8F5EFULL, 0xB9CFB908B8C8B6CAULL, 0x0653CCE107D0902DULL, 
            0x1C464C6E1639637FULL, 0xC07AB2E8435AE660ULL, 0x194566C6ED1051D6ULL, 0x4BA9C1FC59B96683ULL, 
            0x24D639946BCF0187ULL, 0x699420138BDAD714ULL, 0x4FE7CB2A6DF98567ULL, 0xA66B002B681214B4ULL, 
            0xE4FBA3F330CA7949ULL, 0xEF402227D190B077ULL, 0x273A8BB1EE33607AULL, 0x98A122A3C4FA81F6ULL, 
            0x8B0A276CE7B475A4ULL, 0x25357DF7192A3AD3ULL, 0xCB3FD9BB54AA5D9FULL, 0x82873FF5CE2C4F70ULL, 
            0xFE86E4B2520D6FBDULL, 0x298C7CEF6E6A5505ULL, 0xB87F64206F7C1209ULL, 0xA31E2891118614B3ULL, 
            0x3082C514147C7897ULL, 0x674A8EA5DEEDDB4BULL, 0x8532E6A7113D17C3ULL, 0xBE73BA54052E87CDULL, 
            0x38AA354498D685E8ULL, 0x61E39C7F4F88DD45ULL, 0xD505839C21EE15F2ULL, 0xE21634DF5E207F60ULL
        },
        {
            0x9AD57012398045C8ULL, 0x30DAD0D5029B0FF2ULL, 0xD30973AFDA44763AULL, 0xBE9D8149B897D9C8ULL, 
            0xC8975ABF0F7BD771ULL, 0xD55B6DC0768119D4ULL, 0x2B8E12B0DA42142AULL, 0xFAA72808357EBA0CULL, 
            0x4EF3681D89DF4E7AULL, 0x1A85CE2C10AF094FULL, 0x06971E91C4813412ULL, 0x8FB54C13E8EFAF87ULL, 
            0xB2E6ED3912038373ULL, 0x3A329E6110AA4AFEULL, 0x8D6E99F1B2A8C8BEULL, 0xF50B626D68BD455EULL, 
            0x40ADF64B4279E01CULL, 0x9E10CFC4A90F6316ULL, 0xC140A121D64A8502ULL, 0x6C51CB1E2FEC897AULL, 
            0x59FAC090AD1E775DULL, 0xC7F3FA7E0DFD4023ULL, 0x1645679610DA65F1ULL, 0x55A04176963F2314ULL, 
            0x9B7B6B77760EDD05ULL, 0x06E9CB91EE70BF80ULL, 0x09B24C8D39A612A1ULL, 0x750839515327E72CULL, 
            0xAED555D39FF2A24CULL, 0xC3E22FE1B04F44C6ULL, 0x617BBD61C250087DULL, 0x139B0CF524F3F283ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseEConstants = {
    0x96F03678730E9B3DULL,
    0x26FEED6C7520F0DBULL,
    0x00D18E62A5085567ULL,
    0x96F03678730E9B3DULL,
    0x26FEED6C7520F0DBULL,
    0x00D18E62A5085567ULL,
    0xCEA66252A329C6A1ULL,
    0x76323A7BAAE3DF14ULL,
    0x8B,
    0x99,
    0x29,
    0x03,
    0xAC,
    0xD1,
    0xBD,
    0x97
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseFSalts = {
    {
        {
            0x2A8398BD8093AA3CULL, 0xF1D88A2CF4E8A974ULL, 0xB00554A73A8E5D56ULL, 0x85D4E53FA6D66C53ULL, 
            0x5B76CA87875D1DD2ULL, 0xDECC27CD9CC8434FULL, 0x7E1EB5A2FAD7E85EULL, 0xDC06D87223703A19ULL, 
            0xBF267B102B779F36ULL, 0x70093FF8A6EFA55AULL, 0x8090C1D152D6449EULL, 0xD068B430524FE108ULL, 
            0x5ADBDF45D4A1135EULL, 0x108A01EBB2DD2666ULL, 0x439A3450ED054C54ULL, 0x9B5F4732A005793BULL, 
            0x453DDE5FCEAD4CF8ULL, 0x86AA64BE181E1A78ULL, 0x746395A032064D08ULL, 0xD5AB20F9C3EEE5ABULL, 
            0x1146FFF3FDEA6D48ULL, 0x08133A874E7BC6ECULL, 0xB42B99E9A7B54656ULL, 0xA4A0A0A2AFF8A88CULL, 
            0xFF131BDECF2069F0ULL, 0x8BE2DB4CD0DF1DC0ULL, 0xEB9C8F7971C085D3ULL, 0xE0DC5C447E60ACDCULL, 
            0x2AE8553F393966AFULL, 0x3460218AB38355E1ULL, 0x60B56E9B7CB197A1ULL, 0x4BDBDEB36931183DULL
        },
        {
            0xFB0E4882A4CB5CD0ULL, 0xDD249F925AC51384ULL, 0x5CB9B70BB8009BB8ULL, 0xAEF31DDAFB2944BCULL, 
            0xC49511313D7E54DAULL, 0xA667F1243BC028CBULL, 0x195410C0014BF678ULL, 0x3630BCB6589A71CAULL, 
            0xCC7CF9E5A879369EULL, 0x9337FEA37BAB9F64ULL, 0x36EB865110BEAB99ULL, 0x240410274EC4526DULL, 
            0x54DA2199A26A6BB5ULL, 0x62F2E5530B38B8B8ULL, 0x37C43B4FAC6E5324ULL, 0x36894ED6E871134EULL, 
            0xE2EB0E354091DC7CULL, 0x775138170940D13DULL, 0x3272ADFD869748A6ULL, 0x2B05470761C0BC26ULL, 
            0x023200A115AE6D90ULL, 0xEF25F0B31FB70072ULL, 0xA6CCDE50BDA039CAULL, 0xCE64DAE31EDAFD9BULL, 
            0x0C860FEC4D31814AULL, 0x17208699CC39C622ULL, 0x51B197A757200A88ULL, 0x17E3361554BD8C60ULL, 
            0xAA8D001ADC0D82E5ULL, 0x606F8B1332AFF953ULL, 0xE8E9AD2EA6BEB94BULL, 0x17FB37A3500D512BULL
        },
        {
            0x95D592789D4F69D0ULL, 0x87C64D047F720CF6ULL, 0x0D0A3D6FDBBCF967ULL, 0x9CF9AC35C7251AEFULL, 
            0x47F5C5C0244ABAADULL, 0x24EA2971BA63C1A2ULL, 0x7853FEB9CFC818BCULL, 0x85F9716ABE883637ULL, 
            0x82654F9046F80EB5ULL, 0x7ADE552E10151399ULL, 0xE452F618691F398FULL, 0x43B090223BC86A39ULL, 
            0x2C05B4A0195B9B3FULL, 0x98306749B0D5B18FULL, 0x0E72E644ADABA871ULL, 0x6DEC7F4847F8B9CDULL, 
            0xC1AA6BF0F3FD0107ULL, 0x820E679F7D272218ULL, 0x5908F6081105D745ULL, 0xAF405CC6173AA157ULL, 
            0x5B83C663731582F9ULL, 0x187B5FE3A179EEA5ULL, 0x864BF81CAD06E364ULL, 0x342F18CAE26D7F12ULL, 
            0xE3885E41AD2D0B8FULL, 0x096B53EEFAC3CD70ULL, 0x45BA406318C4C6D6ULL, 0x13B1D6E863281AE2ULL, 
            0xFBE50591A846F6CEULL, 0x0751B91837FF5863ULL, 0x66DE3E7633799F60ULL, 0x51D22922FA59643DULL
        },
        {
            0xE806E4883532188FULL, 0x7F9666E5C3BE31C6ULL, 0x67C9FC6CBE645285ULL, 0xCB9A4A36CF6A9CC5ULL, 
            0xD51E3E9A23D9860CULL, 0x06EC8A05973CB423ULL, 0x773D2D42D68DE7AFULL, 0xD1F207ADEAA6B292ULL, 
            0x4D30258325A2FE9AULL, 0xC6A404F7FD3F45AFULL, 0xDCB1E48CA74F963EULL, 0xD940CC9FE3CF0EF2ULL, 
            0xC4597DA7EA7B33CFULL, 0xF805301A156CFE57ULL, 0xE35A1D732DDB77B6ULL, 0xFD6607679CB64854ULL, 
            0x3A23AA8B9C704032ULL, 0x16049E4CAB304197ULL, 0x6A2FB397C96B8918ULL, 0x03D6078E1D27E6AFULL, 
            0xBA05540907D02EC5ULL, 0x8FC311CC4B351F7AULL, 0x27BEBC0729A1E2B5ULL, 0x3C5FA991CD9C74F2ULL, 
            0x531418954AA61006ULL, 0xBD3AB692BC954B7AULL, 0xBB3AEF9276AA23B2ULL, 0x4793720CF0BB3B13ULL, 
            0xA7EF4CD72FE563E0ULL, 0xD94A35C81CA988F1ULL, 0xDA4CB12619327AF7ULL, 0xD7D25E8162797452ULL
        },
        {
            0xCAD4D62BAE61B5B5ULL, 0x414933D28FE43CC2ULL, 0xB4AED99E940A6195ULL, 0xC2F18D4D74E0E023ULL, 
            0xA11C734C9B49AD20ULL, 0xF2EA6DE4E5392057ULL, 0xA7626FE30332EE02ULL, 0x6C21E8F253F29642ULL, 
            0x09A8B42A7C7E9AE8ULL, 0x7D896022D2CC898CULL, 0xCE8536AB25C28B20ULL, 0xCDFB78875F9B03CBULL, 
            0x18879CA0840CCF9AULL, 0x2ADC1B63D624D591ULL, 0x9AF9EE827312614DULL, 0xEE95267F501D8338ULL, 
            0xE836D82054EC20B6ULL, 0x652AFD286DEB4CBDULL, 0xE82DD89B2C3D2ACCULL, 0x78885A969E953624ULL, 
            0xFFD903C83EDDB915ULL, 0xC862932DD59ACFD1ULL, 0x29A043DF90327958ULL, 0x2C27829B18DF887BULL, 
            0x79BEEF99ADAEEF7BULL, 0xBD118C36AA87856EULL, 0xEDF7A88178AD3660ULL, 0xEB4A26846C5E5146ULL, 
            0x56694D4953E243E4ULL, 0xD23DB12D71A646FDULL, 0xD47AC4167AE124FCULL, 0x175D1AFCB1DD474AULL
        },
        {
            0x3C9E25704B91B848ULL, 0x7C9617FF1044C618ULL, 0x8ABE412B138995BBULL, 0x34B949F05E662936ULL, 
            0x0034DA5DE6C5478AULL, 0x05DF85E77152A7C9ULL, 0x8E9A9D78BEA62AC6ULL, 0xA89D22EB2A169FF3ULL, 
            0x016B445D40D94451ULL, 0x3B25F1F0E4F92643ULL, 0xBF9541662C5E94D2ULL, 0x728E24EF3E25DE65ULL, 
            0xE4785071CA8314C3ULL, 0xA9052404835B5F81ULL, 0x0B1BAD39AFF19CBCULL, 0x62DDACC6A53454C9ULL, 
            0x0826542E832F8453ULL, 0xEA5EE8213C677ECFULL, 0x95E6CA94E09827D8ULL, 0xBA2FFF33294C8253ULL, 
            0x227EF5C64116E039ULL, 0xF1B29CFD9448B7CDULL, 0x2AEC06C6862402EBULL, 0xB34B97529BD91529ULL, 
            0x988524334D55B1BDULL, 0xE3378B80B7B2B6D9ULL, 0xC13ABB8FD0DD770FULL, 0x0906258516FAF70CULL, 
            0x0542ECD1192A9BFFULL, 0x2CE8EC04D6C1BD09ULL, 0x68B07BA77A293788ULL, 0x82B0449137714EE8ULL
        }
    },
    {
        {
            0x41DDF440CA60FE6EULL, 0x8C100D6D830D7353ULL, 0x56A2D6A0F8434967ULL, 0x8B8FBBF576A300B5ULL, 
            0xC238DC5AE3BF8BE3ULL, 0x6C28289FCF10E49DULL, 0x8EC5F32D75E8E5C3ULL, 0x4B3DCE51B31E4E69ULL, 
            0xA1F117A69A709E0DULL, 0x306484E7BC87B739ULL, 0x9CC9345D66D78254ULL, 0x964A0877D75B00BBULL, 
            0x5649888DA05D9C09ULL, 0x05639BE223502946ULL, 0x975262966ED0D23FULL, 0x99B00ABDC3F094E9ULL, 
            0xAE071CDDCF7944BEULL, 0x243769584CB47CDAULL, 0x207B896193C0347CULL, 0xE4D720F289ADEF87ULL, 
            0x44C8C2A22D04C132ULL, 0xBFD0898B9EA876C0ULL, 0x5F3F13F0C2B068FCULL, 0x47D7033AF5D1D2FDULL, 
            0x34777C7BD2D6B963ULL, 0xF13C2C3079E05623ULL, 0x1767A61E47549024ULL, 0xEAC49A2D31FCDE45ULL, 
            0xA16D8C072A26ABD7ULL, 0x9E082BF46D6223B7ULL, 0xA3D51CDAA05A2860ULL, 0x1E08DB4D10CA843CULL
        },
        {
            0x05C8F1DEEB01866CULL, 0x5F9DC55876F5A96DULL, 0xC01E1F2734C1D7E6ULL, 0x7F558441600A32ECULL, 
            0xF2A51E0A6A1AB5F2ULL, 0x65EF51136CFD20A8ULL, 0xD452C2BFDFB6FE68ULL, 0xC605F491C0DAE456ULL, 
            0x7E4B9DC5F9438ADEULL, 0x14A192572483785BULL, 0xA76D11AF0F99C1CEULL, 0xD61FC8B7BBFC303EULL, 
            0xF3A434BF09A95BE7ULL, 0x45572B7F0BBF1EDDULL, 0x45681FBEB6BF2A8AULL, 0x60CA33DF67DBD1D6ULL, 
            0x4B023E634D61E0C9ULL, 0x33183E2DDE460211ULL, 0x008C1C93D4AFD7C0ULL, 0xD36ECBAA218D3F71ULL, 
            0x9CCEF4BF1E1F6E77ULL, 0x1CF94E8CCC2C658EULL, 0x04A48BED37076390ULL, 0xC7835A58887E42F1ULL, 
            0x5C406BEFEAF21329ULL, 0xB366574040EBB2AAULL, 0xB906D5540FD29B34ULL, 0x50B3A8F55225D733ULL, 
            0x10D3FCDA40A51956ULL, 0xC7F4002F37F94746ULL, 0x1399555F5165C5A2ULL, 0x40A585D2FBB6E94CULL
        },
        {
            0x7DA09D82D00FC047ULL, 0xC92B5825E61CC951ULL, 0x3F97D1FC6EE5763EULL, 0x3A14CD2A400BA310ULL, 
            0x39197FBF2EE0734CULL, 0xFFE000F3A4EE3157ULL, 0x6CB26EC7500B2EBBULL, 0xF290FF04A6A2B3C6ULL, 
            0x1F9D2BD83E6E4772ULL, 0xE6AB440332138CC6ULL, 0xE586A147E1C00A44ULL, 0x8155D24A6809A693ULL, 
            0x10488074F95C0378ULL, 0x8BE1F059336A2ED6ULL, 0x2B64A9219B960009ULL, 0xC9C635470ECA0CD0ULL, 
            0xA90D442D3E262038ULL, 0xB4BA8687B9088874ULL, 0xE7910E7A068AFE37ULL, 0xA507485865F99B76ULL, 
            0xDC9F66018F36378CULL, 0x6967C482EBE690CEULL, 0xCCB8D43D5D3FFCA2ULL, 0x4799010C832FE82FULL, 
            0xA57226E2C8144F5FULL, 0x8B23672378B1FE8DULL, 0x01B637D364A2F383ULL, 0x660B2BE2C32417E6ULL, 
            0x1195D4F7A2EF7C0DULL, 0xBF201B615BE9D238ULL, 0x7C45BA4104C6E590ULL, 0xBB234FBDAE580B7AULL
        },
        {
            0x702CD3DEA475390BULL, 0xA6910DF7BE2DF376ULL, 0xC2FFC7AC33249A2CULL, 0x30D1DA1BA0747512ULL, 
            0x763FDA7714C95B1EULL, 0x7775ACBB47BA1FF0ULL, 0x0CFF1C769FE77684ULL, 0x516AC5B5E716600CULL, 
            0xC86B09341E66F0C6ULL, 0x6AC4D010DC23D126ULL, 0x9BA027123A768F03ULL, 0xFE45CD75E3FBD6BCULL, 
            0x50E9B4D40A6CFAD6ULL, 0x9DA1479B8E35C4D5ULL, 0x2008F7A6C3C551F3ULL, 0xE77A54CC604BB49FULL, 
            0xFE1397E711A6481AULL, 0x085019DBF2EE5322ULL, 0xD476970208377562ULL, 0xDB76BF2C9D9BBDAEULL, 
            0x118A33F10FBBB599ULL, 0x28EB7A0427997F27ULL, 0x26F02CE47297F057ULL, 0xA7039C829674BFCDULL, 
            0x4E14528ECBCEEBD7ULL, 0x6DD74B3BCAC021DEULL, 0x5D29E3E65A63665CULL, 0xF95CDAE25562E73DULL, 
            0x9F3F3C6B38CFE07FULL, 0xE77C2D7BDC0F6F7AULL, 0x0CC8D6641E86AC64ULL, 0x26C6C0BF5BF2F886ULL
        },
        {
            0x1F6829957ECA6054ULL, 0x583470225B02981BULL, 0xDC7F1BD087EB207BULL, 0x8805D7F4A62BAB9AULL, 
            0x03B56202B74B95F7ULL, 0x94F51F1074054711ULL, 0x617ACCA7A4A243FEULL, 0xFA3742178FA4892AULL, 
            0xE8D6A791A40C8913ULL, 0x5C4DDF1E5AC86170ULL, 0xF7BCC08C704AC59EULL, 0x2CC7F80D1E3199F5ULL, 
            0x9BF323BFC3A651F5ULL, 0x3980C6476DCC4C49ULL, 0xCA7ED27F4DC1A546ULL, 0x1AC43D5085250E68ULL, 
            0x09560ECF0FE5B4DAULL, 0x2F4AEFBB889C4356ULL, 0xCD596FE29634362DULL, 0x8E4554EB9CBB41E4ULL, 
            0xFF1F096846877A09ULL, 0x94653548F8E6CCB1ULL, 0x3CB51FF19EA2CDCFULL, 0xDE9E7A37181C743AULL, 
            0xBF134992A9928900ULL, 0x9AE8BED6E056672EULL, 0x0DDE12C44A3DB54CULL, 0xDD93AD4FE117F503ULL, 
            0x1F056C64C7D8F42BULL, 0xB9C890A92EFCA7CFULL, 0xD75E4D5970C38281ULL, 0xD637BDA75C718E41ULL
        },
        {
            0x6B582B6B9B1B64C2ULL, 0xC52C62507F6CF37EULL, 0x0B889C0C9DE79902ULL, 0x2C1B6AE205A9A87FULL, 
            0x2D604F1A6F52ABE9ULL, 0xC5AD1A8DD65D63ADULL, 0x3EF0DB43C3D28FDEULL, 0xC04F4C04FC686552ULL, 
            0xAA4E583F6A5089F0ULL, 0x642DCE221BCA16D2ULL, 0x2ABB38B0D6E3DA5EULL, 0xB0DAD83A88577776ULL, 
            0x27579A5B53ED188EULL, 0x74814C23C59AE9D8ULL, 0x8A1DFD51ABC36C8BULL, 0x593E51E95AFDA5A0ULL, 
            0xF4E30AF2B4A7C337ULL, 0x446EFD6E1AFD7102ULL, 0x07C6ED3BCA60DA1FULL, 0x5F70DBA702993B1AULL, 
            0x2ECADDC9BC382C35ULL, 0xF2BF647C38E52620ULL, 0x45C3D1B79AF6825AULL, 0x235FE62946444683ULL, 
            0xED200AB4271E545AULL, 0x0DC19F7E85E59528ULL, 0x800A9E776E38E2DAULL, 0xE45147082E5EC5F0ULL, 
            0xCECE0A24847CA514ULL, 0xC6B2048CC54779F2ULL, 0xCE7CDFAFADA745E7ULL, 0x6C43089296ADAD19ULL
        }
    },
    {
        {
            0x0BC9122BB6B188B2ULL, 0x898637B762C26A7BULL, 0xCEB260CD58E38767ULL, 0x876617FA9DB53990ULL, 
            0x8B05EBC9FD8244E6ULL, 0xE1CF0D42F5D929C8ULL, 0x5E8AB42F7768EB91ULL, 0x6540D08AB88B05E6ULL, 
            0x10AFA9945703FCA3ULL, 0x4A29EEE59EC711E8ULL, 0xCD5C7A26DF0F2525ULL, 0x92D82EB417BF6F6EULL, 
            0x9B9EC99FB99B8A06ULL, 0x3C308E4729BAAFBFULL, 0x1D83AD6E1CB3B659ULL, 0x7F96A62467F6D6E5ULL, 
            0x901778FD3F19ED2EULL, 0xE55F8B6A12724259ULL, 0x8FBA55CB05D22E7EULL, 0x461AE4913663BB39ULL, 
            0x4F89DF6EF7BAC8C9ULL, 0x622FA98175594325ULL, 0x339130C8EAA529A6ULL, 0x3495FB7BBEAEF6ABULL, 
            0x363CAFA1F008C4F6ULL, 0x8BEA9AEDED43EAACULL, 0xBE60E1DA615D46A5ULL, 0x73E1C46C64013392ULL, 
            0xB2B6A4BACF7FFF54ULL, 0x2DA107A2997C4166ULL, 0xBAECC585920EF687ULL, 0xA149E07F0EF7BDCDULL
        },
        {
            0xDB06FBE638242E36ULL, 0x01662389191650BCULL, 0xBA283EBE05C1162AULL, 0x8AABFA9870703567ULL, 
            0x4B86D269AECDCFE0ULL, 0x22387125900003F0ULL, 0xCBFF5BA6C8CA95E7ULL, 0x32B8A449032213C5ULL, 
            0x36B644A84254F7B8ULL, 0x435EA936375EC33FULL, 0x28B35850CB9F292DULL, 0xD5C7F117B4911E09ULL, 
            0x50F9E79879E260D7ULL, 0x594FB412AE06CF44ULL, 0xD1F9AD922ECA8E43ULL, 0xF6F5D4DF123774DFULL, 
            0xAC6B15944DA716C9ULL, 0x9A374329D8948DE9ULL, 0xC74C0B806EA34C0CULL, 0x84E968BD7D87A09EULL, 
            0xC88B9300F9BFBAFFULL, 0x8D8D1E60F725FF89ULL, 0x63DD3702371B83D0ULL, 0xAE8370C3BBC229EBULL, 
            0xEFD48D6B55E001EBULL, 0x2EE473F786D66C78ULL, 0xCB2FA1EC0827C227ULL, 0x963F72A679F104D5ULL, 
            0x8843912D4A600BFCULL, 0xDB90FA78565C5834ULL, 0xCA9309FCA2267F0DULL, 0xB602FF4193A0977FULL
        },
        {
            0xD5BE19DCCA4ABBC2ULL, 0x636BB3AED9634F4DULL, 0x59D8929A8C423937ULL, 0xA7E49770965A8F3CULL, 
            0xEE7EE615AB9EEFF1ULL, 0x98A671ACC0E9DDB2ULL, 0xCBEF3DDBF0B452ECULL, 0x0BC88140FA3CB8C8ULL, 
            0xC185A3C862052DB9ULL, 0x633CA607D84ACEA4ULL, 0xA1DD39A0B2224C8CULL, 0x4FF9C79121B4D81FULL, 
            0xFD62718E807C9E15ULL, 0x4CB4DEBF855F3DB6ULL, 0x32D7052EE82A6EB3ULL, 0x9AB4E42FD7854CA0ULL, 
            0x514229AECCE0A778ULL, 0x329BD9E217E1B8EBULL, 0x226C15A31F9BF2C4ULL, 0x5FA6C401E181D39BULL, 
            0x694E221E7603DA7EULL, 0x583EF5987BB36A76ULL, 0xFFC623845EA0BB73ULL, 0x9887990C853916F3ULL, 
            0x558A1D3EB1BDF033ULL, 0x9DD63CBC20F4A1C4ULL, 0x9FE0C97089CD9248ULL, 0xBDFE1C274824DA27ULL, 
            0xDBBE931D7BB1A310ULL, 0xEDAC9DB00B911C23ULL, 0xCC865BDEA7FA8409ULL, 0x13CE12765B194582ULL
        },
        {
            0xF2D2BFC4A606DDFBULL, 0xDC1CBC5EE165F431ULL, 0x97F882BCFFFBA88AULL, 0x3D0BDD44684E4740ULL, 
            0xC156C6CE10F18CC5ULL, 0x18374A25F18050B5ULL, 0x5D0CCC67698E80E9ULL, 0xD5CC4824CF05AD84ULL, 
            0x597FED0B2A061EC8ULL, 0x46E7DCFEAFBB1634ULL, 0x04DADF6B169CCB21ULL, 0xF8550D954E47F575ULL, 
            0xBD2142CBB84FF108ULL, 0xF37EA63510CE61FCULL, 0xAD0359BF6429EE60ULL, 0xB6EA3038F7C4E242ULL, 
            0xB09265455A46EE87ULL, 0xF49DF761B6C31B5CULL, 0xE9C6EFEE4188F6B1ULL, 0xBCD03D90948620EFULL, 
            0xE123DA9E79234076ULL, 0xEE5279978EBED7B7ULL, 0xCBF1D2107341B077ULL, 0xA3B48A543CDB98CDULL, 
            0x284CA87EA4C1B077ULL, 0x7B35956F4FB944EDULL, 0x8284CFA986E79361ULL, 0x9108265389096B15ULL, 
            0x03BE93BB9F2069AEULL, 0x69AE636679D10800ULL, 0x4668B24E5E6BD7B1ULL, 0x68EAD93FB7BB87EAULL
        },
        {
            0x6C93CB83B139E0F4ULL, 0xF37B00ECD12DC303ULL, 0x688A7017764B2895ULL, 0x0C35E70A1FC37FBBULL, 
            0x4679B0A6C5395AA1ULL, 0x8CC137D3545BD8F7ULL, 0xB406E754A54338CEULL, 0xCE55DF2FE060CFF7ULL, 
            0x4EE43DADEE616487ULL, 0x6A7F19E0283ADE51ULL, 0xD5360214C68A9837ULL, 0xBD925D1A3CDA7C0EULL, 
            0x87E1755A0A617FFBULL, 0x71CC77014661FDDBULL, 0x9146016672F14419ULL, 0x60679FC7BF2CF6A1ULL, 
            0x481BF3A64E063956ULL, 0x45925E9E86800D18ULL, 0xFEA30374023C61C2ULL, 0x5C14CACB7C07B941ULL, 
            0x31A8B88D4F886777ULL, 0xBCBF431CCA293BA8ULL, 0x1CF247AEE00A1396ULL, 0x44DC714BA5600106ULL, 
            0xBA59C18F7F364A2DULL, 0x9BE18BDEF1A60014ULL, 0xDF3BB4938A779F26ULL, 0x195B84D75D9E342FULL, 
            0x29241BEB2C0C98CFULL, 0xBF8B03E746382E4BULL, 0xDBF6FDF91011CE1CULL, 0x58033B9585CA247AULL
        },
        {
            0xE3F2BD3A4A750DD9ULL, 0x807261D24B4D7D4CULL, 0x785F55ECA6021223ULL, 0x4CD43EDF7AB59053ULL, 
            0x47993AD2B6C5F037ULL, 0xF33EC0CB85DEC113ULL, 0x073C39126CDA86F8ULL, 0x67B1F1E9D327A517ULL, 
            0x24A360A5E83BE42AULL, 0x298F3E819243DE04ULL, 0xCA37CA39B44737DEULL, 0x6FBB8EBC7A665EC5ULL, 
            0xAEAD9B3676CB1E02ULL, 0x5021981EE16C3112ULL, 0x969E9FE5874B53A0ULL, 0x4053D96181147807ULL, 
            0x01F674AC2124DCA0ULL, 0x45847251BC59A556ULL, 0xEAA4CF603ED3C32FULL, 0xB4ACF6CF00FA015FULL, 
            0x30AE1667F05BA6F2ULL, 0xF22668862EFF4A16ULL, 0x5BA71D67426E558DULL, 0xE25D9D9502F9F6F0ULL, 
            0x9F06A78AA602E8B5ULL, 0x6178DE3D65D0692AULL, 0x20AC1F953B42F9DDULL, 0x7FA36400F76C2A81ULL, 
            0xC5A76E8A754FB16BULL, 0xB023715A804511DCULL, 0x360CA5B3CAEBE52AULL, 0x4F71FD4AC92073F2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseFConstants = {
    0xA9D113C7CF067AFFULL,
    0xC73A91FD803CAE96ULL,
    0x0DCB116DFD9F2746ULL,
    0xA9D113C7CF067AFFULL,
    0xC73A91FD803CAE96ULL,
    0x0DCB116DFD9F2746ULL,
    0xDD060FF3C9B5EE2AULL,
    0xBFD0FB95764C264EULL,
    0x5C,
    0x6B,
    0xB3,
    0x46,
    0xB9,
    0x07,
    0x87,
    0xAA
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseGSalts = {
    {
        {
            0x8EA91F3CACF3B723ULL, 0x69FEA28B175C0000ULL, 0x6680C75D879B55E8ULL, 0x8C36E726936D18AAULL, 
            0xC94E9134F9C1404AULL, 0x29DBFEEC92073559ULL, 0x48DDC1C8B2FAC53DULL, 0xFD8C95631C938F71ULL, 
            0x75DF3061079C8463ULL, 0x715C4000E5D4A06AULL, 0x05043A504B697D00ULL, 0x39D590BC08C5E76CULL, 
            0xDD5FEBD2B991D83AULL, 0xC727D82764C7718DULL, 0xC5758A501242DE23ULL, 0x0D23A9E1B1B53CE7ULL, 
            0xEFDB2E7B35D9B2E0ULL, 0x2BBF1FAE5D5E09D1ULL, 0xD33C47D0ACD183A3ULL, 0x20785DCFB62DD968ULL, 
            0x79C45151BC4D45CAULL, 0x80EA2109A602EEE8ULL, 0x7DCE76C31EE2D593ULL, 0x207C7FBE0CDD2A1CULL, 
            0x9781688CBC801D01ULL, 0x3B4E64967635837DULL, 0x27391E4764C98F3CULL, 0xF9E8D5549D73271DULL, 
            0x62BA4FA3FD96A979ULL, 0x319EC449D38A1B24ULL, 0x3883D787FDB7016EULL, 0xA204065E7629B76AULL
        },
        {
            0xA920E76717D503BAULL, 0xA77C5E5C290DB394ULL, 0xCFDD03F5E88CC1CCULL, 0x3127B5D639C7B05BULL, 
            0x7CB790C22A7387D0ULL, 0x518E09F935E4FA19ULL, 0x530BC69A79D8DB42ULL, 0xD7E4EF45B7321042ULL, 
            0xD99A4CBBDE946A4DULL, 0x1FFCEFDE584A362DULL, 0x947CA9F5E814A473ULL, 0x32B21985CF18EB26ULL, 
            0xF8038600A2F368DBULL, 0x92DE4424D4FFDFB8ULL, 0x3A8401217E3FA823ULL, 0x2C94161200605B21ULL, 
            0x608CC31C25B89997ULL, 0x3F78FAC3F5857EAAULL, 0x636C2C75606BE932ULL, 0xAB5FC46D43B96202ULL, 
            0x69FC349E9F6293D3ULL, 0x0701AEF765A9FB74ULL, 0xC80AAC1B9C741249ULL, 0x3BAFDC743C4CEE24ULL, 
            0x6EA37CB20192C676ULL, 0x499077174BB8F1FAULL, 0x5D63BDB31B2411F6ULL, 0x5A4539AF34366100ULL, 
            0xC3E75B3A7A9D47D7ULL, 0xCB5DC2BB248C91CDULL, 0xD0B319F81451D290ULL, 0x88F51845DF6C7640ULL
        },
        {
            0xC4AA32D0D04336B7ULL, 0xFA254FEED898C3D9ULL, 0x73001E550C4F7F45ULL, 0x34F11EDF2BD05160ULL, 
            0x91EAFB73E7F9FF68ULL, 0xD60364B53A365E82ULL, 0xBD374FF9AD68B40BULL, 0x0CE1CEA2D2773CDAULL, 
            0x44FC39582277DF28ULL, 0x7D871BF5C50843B0ULL, 0x5CFAC9BEF126C1D6ULL, 0xEAFBE0ECE6257F26ULL, 
            0x29CF3EB01096CE2CULL, 0xCA0E497B9E27DC22ULL, 0x60D301BB630F6394ULL, 0xE9FD50ACE3823167ULL, 
            0xE1ABFAB4549CD98FULL, 0x2E75DE7E852FD6C9ULL, 0x5A92092F8D8D4B60ULL, 0x156AAF7E2F09D90EULL, 
            0x4042D8CBDB0C2FA3ULL, 0x383428C842DEC8B3ULL, 0x863DE31876D0E9D2ULL, 0x1CC2E472D1225568ULL, 
            0x88B61679FF26EE6BULL, 0x4CC2D9152751301CULL, 0x93A0643B38846F66ULL, 0xC23FDC6EE5D4A62EULL, 
            0xA36D551CB557B9AAULL, 0x603B0EE6781FF558ULL, 0x45EA1A956F28FBD2ULL, 0x340969A8AB4BF894ULL
        },
        {
            0x97B0AB1E820C3CA2ULL, 0xCA7F2BF69264C7CAULL, 0x5357EE431B4EE8D6ULL, 0xC0A50B3E651EF92EULL, 
            0x2A6FA8B37F8DF35EULL, 0xD69A4CD37D3AAAC8ULL, 0x308033D1CA3F5A8FULL, 0xCFE8AEF5B5C482ECULL, 
            0x7D04904F7C450DBAULL, 0xD0A2109223A14A3DULL, 0x8E601F45FF7C0AEFULL, 0xF6DE04396841FB5DULL, 
            0x61C3A7035E6D2652ULL, 0xD348706D01A17A47ULL, 0x291AC72BD75871A5ULL, 0x9D28FC5C8FB807DAULL, 
            0x6C32DFE1DB9D521DULL, 0x6E9D6B3545D7B42FULL, 0xC824A239912698FCULL, 0xE86C74DD933ACD41ULL, 
            0x3D3712D840834C77ULL, 0x4B2625A5BD1F356DULL, 0xE2BDB082AAE3E16FULL, 0xAF8F0377D1AFABBAULL, 
            0x4AD49D5EC2FC0F62ULL, 0x12AEE1108DD06DE4ULL, 0x6CF6C6E6E02EBB80ULL, 0xD42FC4FB25056765ULL, 
            0x05871ADCCEA41F5DULL, 0x4F05F6BB15127AE7ULL, 0x39B5138EE4B42A1EULL, 0x1D089A0119E9FE65ULL
        },
        {
            0x9F1C29DF93F4A05FULL, 0xC6A13449304AC624ULL, 0x6BAB1D0BA6DAC31CULL, 0xBCF426780B2BC591ULL, 
            0x9588580BA1966C14ULL, 0xFF7F428E962745C5ULL, 0x881B12BA7ED5F16BULL, 0x3CA82B932A591892ULL, 
            0x2048833E3A1B04C1ULL, 0x41DB92953B114559ULL, 0xEB901AFC16475847ULL, 0xECC40E268CD3128AULL, 
            0x4C9B8F798C891CACULL, 0xCECB2999A8C2FA83ULL, 0x05A9E5474CF4AE78ULL, 0xF11E5067956D6D32ULL, 
            0x92D65F89CC4BEFE0ULL, 0xD6CAF6EF81E7D513ULL, 0xD2A79410453F1F7AULL, 0x7C9BA54D7A5C4C31ULL, 
            0x0CF110B689FA6E0CULL, 0x4E052BD95428591EULL, 0x026FB45E236B1EBEULL, 0x26E7613194ACF56DULL, 
            0xE7308ACF20CC013CULL, 0x4E2FB0AA69E366F2ULL, 0xE764406EB4C0BF54ULL, 0x068190241D36EB16ULL, 
            0x14A794F6BB2E9FBCULL, 0xF59DB7025CEF05D2ULL, 0xFDE84278092F4991ULL, 0x26FF5651D3E45908ULL
        },
        {
            0x120FA17E10D78FFDULL, 0x6952C84DB8019285ULL, 0xE38C484BAD7B5BDCULL, 0xD15347D76D2F6D7FULL, 
            0x19F46E1EC590E34DULL, 0x0751270CF073DB8BULL, 0x7BEE67F0A0F74EC6ULL, 0xF87E7D88135CD909ULL, 
            0xBD9D2189231D2383ULL, 0xD913B502A9E3972DULL, 0x2666F72CE279D48AULL, 0x01EC07EB73B46D2CULL, 
            0xBE7A801C41B72F29ULL, 0x892CD57AFEC66F5DULL, 0x0C9B7BF3B7D35C14ULL, 0x357AE4534130C9D0ULL, 
            0x48EC2540A1DAF060ULL, 0x766CB980AF85BDAEULL, 0x9FA95BDDBC3586FFULL, 0xEB3030BBC900D69CULL, 
            0x862865C5B90BA381ULL, 0x9EA126D94C10F324ULL, 0x466123309F9C5AFDULL, 0x195B8ED6D2E0305CULL, 
            0xEBE3583DA4BCC3FEULL, 0x9EEB87D9E5C04498ULL, 0x914C2BA8C66FFB67ULL, 0xAC0F905B49B10686ULL, 
            0x9415D12513165D7CULL, 0x7C7246E585CD3E3DULL, 0x1F9461282DD9B1D4ULL, 0x0B031B30FABBF8A4ULL
        }
    },
    {
        {
            0x44EAB2A1FB579B33ULL, 0x6252BAB855B16C90ULL, 0x6C3542A701CDAC40ULL, 0x77C2972EBED5E3E7ULL, 
            0x56B1A27F4D5C2351ULL, 0xDB8ED3743521C6E3ULL, 0xFDEB73DD94A42BD5ULL, 0x2A50825965C14FC9ULL, 
            0x0013047B7382E684ULL, 0x7458FDAC4DD1F8BBULL, 0x1DDE666A98318FF0ULL, 0x10298CF5151F978BULL, 
            0xDDDAF170EE5D1A46ULL, 0x89129D7484217043ULL, 0xE8FBDA24827AC08AULL, 0xB200F7DF4E6EB6A4ULL, 
            0x2F58829CAA9827EEULL, 0xA1EB90B1A29B441FULL, 0x825510DDD459D4D3ULL, 0x84193ED28A7F4AA4ULL, 
            0x3F859D5AD1B18A96ULL, 0xCC489288F07A868CULL, 0xC2AEA9262FED12B2ULL, 0x70F88380C09C4414ULL, 
            0x67B6268275887835ULL, 0x4C7BA8B182EC111CULL, 0xC4AC6C37848AB6D6ULL, 0x3A319014B89DF083ULL, 
            0x772D5B8446F4720CULL, 0x4150336794779FF2ULL, 0xFBD6D2518CA8D51EULL, 0x2BB2868AEF9880B9ULL
        },
        {
            0x933F78318D1086C8ULL, 0x8D15BD03B9A132DAULL, 0x64B8BC8775FF4C5DULL, 0x057305E565B4E92CULL, 
            0x9BE180FABE5F6EF4ULL, 0x16984039A32010CEULL, 0x7E958FDD67A6C846ULL, 0x016211B2C5F09E74ULL, 
            0x2F6B667C799F2D42ULL, 0xB7C6C6D65EDA25B1ULL, 0xD9A0AA61FB153D87ULL, 0xEBB8789C16462B64ULL, 
            0x8C23A306F89E0291ULL, 0xB48948FD6DFC2058ULL, 0x31CD1F262CA62E96ULL, 0x2C496C9B8571CB23ULL, 
            0x6A07806FC81C4482ULL, 0x97705056A0989485ULL, 0x95F066372814D4B6ULL, 0xAF2B13CE0C2B3660ULL, 
            0x923828195FFCD4BEULL, 0xFB2749180CF361B6ULL, 0x55996C4283E63866ULL, 0x5450A67A2C1D7A5CULL, 
            0x93B975ECE2FA22DCULL, 0x617EE5178D3A5700ULL, 0x32A31174FAE97CA5ULL, 0x61FEE5BFE18E2083ULL, 
            0xD80E346CE77BCD8EULL, 0x56B427DE567DFB68ULL, 0xB94C6B434D033124ULL, 0xCC79A4AF717C96C2ULL
        },
        {
            0x9E8F1ECCEE8DF3C5ULL, 0xCDD6039903955D6CULL, 0x128AC13910702851ULL, 0x513CCBFC5ADA5E7BULL, 
            0xED98E028DA40E249ULL, 0xA3A9355619D4F141ULL, 0x7985CB4204991044ULL, 0x2815C2B1AAFE8D74ULL, 
            0x5CDA4117AC18E233ULL, 0x6CBE1EEE3CEEEC24ULL, 0xCA667CABA50904CDULL, 0xECBD4AB510B349AFULL, 
            0x5A330DC1D2D0CD7EULL, 0x7F8B9704711870A0ULL, 0xC685225692FB41B3ULL, 0x770147F3B94F9FB2ULL, 
            0x7869F2C7C7470AB3ULL, 0xF10778D8E575F682ULL, 0x43832C0DA46E9560ULL, 0xFC78A121EB7B8F6EULL, 
            0xA34D92D4DCE1C224ULL, 0x8089AB89DF785C7DULL, 0x8E05CEA268173110ULL, 0x0ED6E49608620967ULL, 
            0x4B1808744CB82EB1ULL, 0xBE40FAFAF3A01A52ULL, 0xE0788DF350E3C3FDULL, 0x7DE5B5945FA11FE5ULL, 
            0x980A1A2072C7C483ULL, 0x163F2ADD38AE2BE0ULL, 0x1AFE824143FD3A2CULL, 0xCB91EC1162F6F56BULL
        },
        {
            0x751BD0ADEE4ABCF6ULL, 0xE8AA54203B1D6A91ULL, 0x00568913D5E28A86ULL, 0xFFE18FA0FBADBCEFULL, 
            0xB203DEB3896D70E3ULL, 0x73942EB9926C2223ULL, 0x073246A8CD345B2CULL, 0x32F840C64B607AA3ULL, 
            0x4730BE91B3A7B6C5ULL, 0x55AA0C1B22D37EBAULL, 0xC0FD59A1FE77C86AULL, 0xD550C455772AB1C0ULL, 
            0x309A1B6F793939FEULL, 0x0F3B4F1EED28ED97ULL, 0x75BEA2C9C2EDB415ULL, 0x1055CF4A9D83860FULL, 
            0x5C8F292644C6B3ECULL, 0x710063A2A3820275ULL, 0x58822DCB80D5DA99ULL, 0xB1D19F668D0A70D3ULL, 
            0xE12809DA63D9ECC4ULL, 0xE8715811E0B46722ULL, 0xC2FEC081A5681ACBULL, 0xBFC479E61E1361CCULL, 
            0xDD19D0DE9568624EULL, 0x655D7B6AAC05A9BFULL, 0x0BC547A176F7D594ULL, 0x59E957F02373383EULL, 
            0x80E0499E61B35291ULL, 0xC9489D54F35E6FE5ULL, 0x5525FCC3117E91B5ULL, 0x6E98F2346B4E55A3ULL
        },
        {
            0x85793ED2D7EB703FULL, 0xF2F3D6743B92B0B5ULL, 0x191F75C60C0AB923ULL, 0x9B4650037E44A85CULL, 
            0x2AF157B4D94B5F25ULL, 0x99EC8304C8C00A40ULL, 0xDDA3798A5358ECDDULL, 0x6FD0884E517702F0ULL, 
            0x5FF04F144E36C710ULL, 0x184666F976D2592EULL, 0xC75D4726FDD7BEADULL, 0x29A872BDCC6D118BULL, 
            0x65A39EBCFA43DAA2ULL, 0xA485CE530DFAE547ULL, 0xBD1D7854D9B43574ULL, 0xDA43D5AD673295ACULL, 
            0x61A55AEE5FD73B4BULL, 0xD751832E8E6232E1ULL, 0x0FEE270E1F5566DDULL, 0x3E86B07E7F51E679ULL, 
            0xBCEB288B7899E3CCULL, 0x7AE32D202B5EB211ULL, 0xE5AA8F6979D534C3ULL, 0x729CEF09565842C3ULL, 
            0x77106B143A48B338ULL, 0x60E49E997DA4487BULL, 0x2588317E8AE85225ULL, 0x9E59689F0BC75178ULL, 
            0x8B02A21ABB0D21E8ULL, 0x6FEB60FC6A31D431ULL, 0x5565D81D105E7B13ULL, 0x2826B0E3FCB6C041ULL
        },
        {
            0x9587199E62FB65B4ULL, 0x2987E18BA712B939ULL, 0x2CD898A6052C34AEULL, 0x8BDF3329CDB49293ULL, 
            0x19EB882B86CC0202ULL, 0x8DB164868F012C7FULL, 0xDC6D5C305EAD5BC0ULL, 0xF397767D96A6093AULL, 
            0x7C121FE999A036BDULL, 0x2F5DD008AB2560E5ULL, 0x106B83C079530211ULL, 0x59B33C01ADCE9C3DULL, 
            0x1AC7CA45A224DF24ULL, 0xD9E12510AB6BF0EBULL, 0xF57CB8D21A50F784ULL, 0x7891A26E159D76E5ULL, 
            0x5DD86B0B8C3CCA32ULL, 0xEA28C44A097F8503ULL, 0xD86BD152CE227D83ULL, 0xA62B8CB58E1BED50ULL, 
            0xD415773D4054D230ULL, 0x32D74710B32A47D0ULL, 0x4A4689012F28431BULL, 0x4D48F02198160B18ULL, 
            0xC3EA3277CE1F441FULL, 0xA84F6371A85CE533ULL, 0x55BECE0E62236F5CULL, 0x74F556AB71D6A71DULL, 
            0xF331FD36C8F8ADB1ULL, 0x67993DF0AD449C1DULL, 0x27DDB3EAE046FA97ULL, 0x715DA80C7A9ECDF3ULL
        }
    },
    {
        {
            0xC1245E6E2B163913ULL, 0xCD8B284896E04378ULL, 0x6B25C1DF4D6D6878ULL, 0x49D600423528D6C8ULL, 
            0x1BAD953DE0FFBB26ULL, 0x04DD2436EF072101ULL, 0x68B91F4B1D21D8DCULL, 0x72EBE9C796DDEA4BULL, 
            0x9A8DD59702B977E2ULL, 0x32EDBEED08E14049ULL, 0x89D03A2E29FF3080ULL, 0x63499A3267A858DFULL, 
            0x367C15F2B13A1A64ULL, 0x0B964F443460CDF0ULL, 0x7606F470E93052C5ULL, 0x719AB1DC254175ECULL, 
            0x75E4686C2F2D388BULL, 0x29AD74DE6125F34DULL, 0x3399380AF9BD3772ULL, 0x06FCC41D5492CE09ULL, 
            0x4C70ED13CB28CB6AULL, 0x436EA6E25925FFB0ULL, 0x2D91FCFF25A69E4FULL, 0x2577F4ADF702D7F2ULL, 
            0x83F989C9BB353491ULL, 0xBA35ECD56F8EB8DFULL, 0x46713139AFA6C606ULL, 0x60B24BE79272AECCULL, 
            0xD2C02B9916F87330ULL, 0xFDF9CFA80D5715E7ULL, 0xCA0CEF853BDC3842ULL, 0x934817CD3AF195C3ULL
        },
        {
            0xD3C86A6D4F9BD6D3ULL, 0xCF70D342588A879BULL, 0xAD4667988A51EEFDULL, 0x73F07772D35FADE3ULL, 
            0x655B097D9859D54AULL, 0xCBB3A5026E5F359BULL, 0x4B04F77EE1010688ULL, 0xF8CD9A7ACC3C61A2ULL, 
            0xDF7CE5C555A17508ULL, 0x88444FEF44CF5FA8ULL, 0x800D5021B193AFEAULL, 0x29CF3CC907547435ULL, 
            0x4680EDC5BDF794B1ULL, 0xBA1FC15FF60F18BFULL, 0x19EE2CFC71F8E705ULL, 0x6EE31E96BF360429ULL, 
            0xAC6DBB19B0BAB212ULL, 0xF9C381C2C3AB0772ULL, 0xC7FE762296820500ULL, 0xA6D11B45F5CB2422ULL, 
            0x152D0C969678E897ULL, 0xB66491CF0778A934ULL, 0x091277C887D03A80ULL, 0xBC506766465D4330ULL, 
            0x76D4036F2BA45540ULL, 0xEB3D9B26A949C0ECULL, 0x6859792F7CC91377ULL, 0x8F7B644391BE2D5FULL, 
            0x8547B86EB8D71B7AULL, 0x6CA447D684A1CC25ULL, 0x9027BC22DBF0E67FULL, 0xD4671629C7A5C118ULL
        },
        {
            0xAA0B6073937A0773ULL, 0x0B739CC81CAE3C12ULL, 0x25795EC511667E79ULL, 0x11825CF20D66C898ULL, 
            0xA015EC232B9B0C7AULL, 0x98459D5F6EFA7161ULL, 0xE854E74810A73655ULL, 0xB85ADA0CEAFF4758ULL, 
            0x1A2F71613BBCD11FULL, 0xB0A8C939B99C60FAULL, 0xE2D36DF46B91CA66ULL, 0xA2D40697251EC337ULL, 
            0x5D911AEC18B21D57ULL, 0xBAF3215C4A9C8919ULL, 0x143F519685B99269ULL, 0xD18D90C01DE9F154ULL, 
            0xAAEBFFECBDA20E95ULL, 0xEEA67FAD9ED6663DULL, 0xF91EBB1F02FD3C1EULL, 0x84A7A4F304C0697EULL, 
            0xEF50A23FF48EE466ULL, 0x16E2060EF4C7C6F8ULL, 0xFC73B65671277FFBULL, 0xFDB6CFB87D0EE108ULL, 
            0x4C7B57B0E6DE610DULL, 0x003D096B98BA9858ULL, 0xD6A51DC70717ECABULL, 0x5B0B7D7659A4321AULL, 
            0x973999A4EE2EB110ULL, 0x0A8381FCA321C08EULL, 0x95217EE2CA225DA2ULL, 0x96BA8800D0B56838ULL
        },
        {
            0xE15A7773BA07B56FULL, 0xA187B2F5F0B38618ULL, 0x28650D86D22E6A1BULL, 0x34BA7D70370F596FULL, 
            0xCE82714114CDC11AULL, 0xBBD49637D23273ACULL, 0xCB289D87BBD7B87FULL, 0x0A1C8C07359B5893ULL, 
            0xED3F6EA539D81607ULL, 0x321C5C40479EE1BBULL, 0xF50CAD6E372B21ADULL, 0x3AB0BF1AB153B8C6ULL, 
            0xB11AF2FDEEAEA5FBULL, 0x458F6636C1AFE8C0ULL, 0xFB9C7EED683AFFB0ULL, 0xB7B78BE4F0FF187EULL, 
            0x08910A70CCF58E2BULL, 0x9FE753A94ACF533DULL, 0xCDE76D9C2F0F2ECBULL, 0xD3755B5539F17BC0ULL, 
            0x95E65B4DA16A9CAFULL, 0x92ACF02972A9BB1AULL, 0x5F794B95DE4ADDE1ULL, 0x9973C528E17F2F20ULL, 
            0xB002BB39CF50441BULL, 0x03DA273642C0BC2CULL, 0x2F5E183F4699ACDBULL, 0xF4ABD7A556EDEF75ULL, 
            0x5066E914DA7F8136ULL, 0x0AD74103E812E72CULL, 0xADB578752E5C50E1ULL, 0x18526770B777C9C3ULL
        },
        {
            0x8C7FA417B6341FACULL, 0xE5D3580694963B1DULL, 0xABAFDAD9980F0A58ULL, 0x4112C68CDF7A09A4ULL, 
            0xDCE45E70E40CD439ULL, 0xED77B957978BFECCULL, 0x0A2F804E9ABC0D96ULL, 0x3F750EAE89ED86CDULL, 
            0x3890BAC414D52036ULL, 0xAD9F3075BA8AE35FULL, 0xC18F0CA3A77229FDULL, 0xEF490570DFA4EB7FULL, 
            0xA3D147F3836C8B0BULL, 0x4DBABAA593EB48A9ULL, 0x528E05E9E310BBDCULL, 0x2B393FC691564F0AULL, 
            0x431BEACFF82DAE5FULL, 0xED3B1625B47FF52CULL, 0xADBDA9BBC0BEC264ULL, 0xB32C7F5B2015C729ULL, 
            0xA7A611775730F103ULL, 0xEF80EE915A1DB30CULL, 0x62A7267F024EA962ULL, 0x3B9AA7568DF8447DULL, 
            0x534381B96FE303F3ULL, 0x2559D3865F194D7DULL, 0xB8105D12DEEB7614ULL, 0xB6EC425A7280BE21ULL, 
            0x9E7A32E3D8B181EBULL, 0x0024658EACD5CC17ULL, 0x43D8A1B962705638ULL, 0xD1213376A23A3D56ULL
        },
        {
            0x84CC280074D39ED0ULL, 0x6B1DD431E04C31FCULL, 0xDBDC18DE43879223ULL, 0xAE3F9991C7A674E2ULL, 
            0xBED92439DB7AA87EULL, 0x51DEB0590256D4DEULL, 0xCA02DB873F523CFBULL, 0x75127533C39EF03BULL, 
            0x2661842C434D7A7BULL, 0x8E14E90C9A05295CULL, 0x597A55A2F0BD41B2ULL, 0xA22212F3F560FA1CULL, 
            0xF502270108DC6029ULL, 0x801C5C4ADA5CC560ULL, 0x0A9FAF44FAF3C354ULL, 0x868DFBB4E8386BC0ULL, 
            0x792261357486421AULL, 0x943646AEB8F33A1BULL, 0x65E3ECC39A665DDAULL, 0xA0B2A11EC0072EF0ULL, 
            0x928F7E7D21586F8CULL, 0x2E68335BB11EEA31ULL, 0xCB7E700EF7AC9BBFULL, 0xC346E73F7A69EEE1ULL, 
            0x13667CD99A43CAB4ULL, 0x8F20F86B0682B7A3ULL, 0xC38E50F8ADAF1E43ULL, 0x491F0FC6E7B9FAD3ULL, 
            0xC4504FD10C7BCF3FULL, 0xC768DF31EF645AD4ULL, 0xB664E8059A4534EFULL, 0x925AF2E541EB0217ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseGConstants = {
    0x7FA960807BE2AFA2ULL,
    0xC38DEB60DCA62AA8ULL,
    0x4125F8EDD649FB83ULL,
    0x7FA960807BE2AFA2ULL,
    0xC38DEB60DCA62AA8ULL,
    0x4125F8EDD649FB83ULL,
    0x1FE16CED7CB27276ULL,
    0xF830F984530A1D45ULL,
    0x97,
    0xEA,
    0xDD,
    0x61,
    0x8A,
    0x16,
    0xE9,
    0xFF
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseHSalts = {
    {
        {
            0x952220B39F507B87ULL, 0x36F480D69327B2D2ULL, 0x279A9AE1CA780504ULL, 0x0EF901B87AE00E60ULL, 
            0x72734BE432A01E50ULL, 0xDD9068F6A50B8BB1ULL, 0x6C0D52C83F53A2B5ULL, 0x529D5F2BB103FCA9ULL, 
            0xBA6988594A211D6AULL, 0x03335382BABFC613ULL, 0xA8F625650F38E555ULL, 0x2182908F02D4F326ULL, 
            0x611446D62405CF9AULL, 0xE3F89BCA4688B48BULL, 0x39FC29E77F656139ULL, 0x3DC97FE087C4DA01ULL, 
            0xC2E0FF3EEB63EC25ULL, 0x2B0278E3B89D4047ULL, 0x40BB79D644E635EEULL, 0xE676BAF3401024DDULL, 
            0xBA8FC931089A537DULL, 0x48116ADCBB6120F2ULL, 0xAE3AC865E7BD735FULL, 0xFCE7D179C4DD7A4FULL, 
            0x8776E2BB1E45E111ULL, 0x4B82DEB205539127ULL, 0x1096A1E5633056BFULL, 0x7ADBA13854B823C1ULL, 
            0xAACD7E8DF2A33F3FULL, 0x90C048E989D3CB49ULL, 0x08516083A6B84592ULL, 0xB23E79B09546B59AULL
        },
        {
            0x26B137135790D16FULL, 0xBAD09780B804F4DCULL, 0xB6A92E6E4612A32AULL, 0x3FB633E0CEFE2FA7ULL, 
            0x00A408B67D0954A1ULL, 0x3A9BD2687E3504B2ULL, 0x4BF6A042775C257DULL, 0xBFB559E1380B7681ULL, 
            0xCA0D1C9194535DEBULL, 0x42D71C96B2593844ULL, 0xE8E5CC53D994F10EULL, 0x1258A1106F0C653BULL, 
            0xD3CC623194175706ULL, 0x118F5C1441967998ULL, 0x649234DABDAE361AULL, 0xAB71F41CCCF4279AULL, 
            0xA11518C729E543E2ULL, 0xA9227C95AD42AECDULL, 0x170CE31709C5FEB1ULL, 0xC51BE47474CE5E9CULL, 
            0xFAE63BE49E2D4611ULL, 0xE0BB8656964584BFULL, 0x87A9BCF454D0B347ULL, 0x7F71C814B338525FULL, 
            0xB1E9A11FDB327783ULL, 0x2ED6F27547A21BDAULL, 0xCB1D7C93F92947B9ULL, 0x31346763BBD62FC7ULL, 
            0x7DA35D792516B4A3ULL, 0xEB3A0F0716EAD014ULL, 0x8A035AFD2E93EEC6ULL, 0x9C014AB4B3EAAD31ULL
        },
        {
            0xB8DD7752B0E3246FULL, 0xAB42E09AAEC15C4FULL, 0xA46224CC483F9097ULL, 0x0613F354567B7B02ULL, 
            0xF17B97ACB68A38D4ULL, 0x8ED72DBCD4A59F6FULL, 0x0B5E1F7333B8772FULL, 0x115FB0F4CD08601DULL, 
            0x90B3A121449F218CULL, 0xD7AE5AC48716013DULL, 0x9F5E23325AD05EBAULL, 0x2FF11FCF0D033202ULL, 
            0xC4A1503FCD996646ULL, 0x945102CC84D4FC43ULL, 0x2AC7FAC3F65A67F8ULL, 0x7A7DC2EACA1A7D2FULL, 
            0xA42D13DFE20475C6ULL, 0x9F6BD80429A43A9CULL, 0x9F4487146A71F0CBULL, 0xF9393EEFE0266DE8ULL, 
            0xAC51C23108764948ULL, 0xA7E1D410A6173E56ULL, 0x2962C7908CD002F9ULL, 0x322AFDF50047AC6EULL, 
            0x8379B55366545BFFULL, 0xF881CA96F6ABBDC9ULL, 0xCAAEAB3AD9338FB6ULL, 0x2865FCE1F9BD8BCEULL, 
            0xE409485B3E16888BULL, 0xD65E16E9165A1EC5ULL, 0x6943D416C9E0C4A5ULL, 0xCFDF1CCB6C870E78ULL
        },
        {
            0x0B5BD850D9F3412DULL, 0x47EC3EE681D33A5DULL, 0xDCC18379E7CB16B1ULL, 0xC3ED699FD0F83161ULL, 
            0x70B5ED4F0D6462C5ULL, 0x1245EC450E078B76ULL, 0x3F1D9837EFA22D2AULL, 0xA734896D1D40F2C6ULL, 
            0x97B9275A65CE1D3CULL, 0x5298414604903556ULL, 0x9F6573CF68473301ULL, 0x01BB7282F68FFB7CULL, 
            0xDF3581CA007A1B20ULL, 0xF7D7F4FD6138E096ULL, 0x61422DB7CBD80B10ULL, 0x61F62D71A9FBD517ULL, 
            0x602036BFEE7D3938ULL, 0x0DF9AA9D469F24DEULL, 0xECA7E1065C48F01BULL, 0xAB8256AC3966D79AULL, 
            0x4DB9D871643D6FA7ULL, 0xD9B65F1710C05951ULL, 0x50E265EB3A2317BAULL, 0x46457CE05F595C27ULL, 
            0xC1712D755A2B6441ULL, 0xC8955649B95F1088ULL, 0xE0244E3083B5AA58ULL, 0x363706D2143DF0B9ULL, 
            0x9146AF06094B2562ULL, 0xFDDE5DE64BCFAEFBULL, 0x695413B36AAD1841ULL, 0xE380B0A5AAF65145ULL
        },
        {
            0xC74051BF494A77CEULL, 0xC72741C8263FD213ULL, 0x86CDCCD68CB39CCAULL, 0x776EE05A9A75BDD3ULL, 
            0x94E573AA9DD9B07AULL, 0x483AB0E0F29BAE12ULL, 0xA86BD567D656C483ULL, 0xEBE255C31D7D88B0ULL, 
            0x681A2B362ECD5ACAULL, 0xAB5F9E2A1CC0BB8FULL, 0x3C19D1D912C1AF12ULL, 0xC4E5723C165259B3ULL, 
            0xBFFAC05E6D63EA8AULL, 0x93493573DFE45FC8ULL, 0xAD57975A3CA6E0A8ULL, 0x6C7F58A7643FB656ULL, 
            0x1D2D83EAA1CBDEE8ULL, 0x1BBCAAAC01666E1EULL, 0x6F5CEAD3F59B1011ULL, 0x9320F2B162C428DBULL, 
            0xD01365450E457E37ULL, 0xE71D4FBCAA33B4DAULL, 0x76CF8F99CFD277A9ULL, 0x6F90323C2DC0866DULL, 
            0x80924832CC19B1F9ULL, 0x2D279AA47077E493ULL, 0x200ABC7F055B68A6ULL, 0xCDC150D68894AE07ULL, 
            0x9E5C78E9652ECA39ULL, 0x14A3C99230937FDDULL, 0xCC0C46F47B5DB4BCULL, 0x27AF333ACD295C5AULL
        },
        {
            0x0B7CAD3C725A5361ULL, 0x69C05241144D07FFULL, 0xEA4B2ED7FBD9D950ULL, 0x0FDF8DBF8252ABD6ULL, 
            0x34525D30333B2AD3ULL, 0x8BA4D6D3E310D3D7ULL, 0xE4022A57E08F7421ULL, 0x2782DB8FC8B4CB88ULL, 
            0xE4A4BFBBF0FF1C47ULL, 0x1C32970C55EA191DULL, 0xD57EA1A3BA0F03ADULL, 0xB13EF4F25ACCD040ULL, 
            0x7E465AC358A17BCBULL, 0xD635B43171660178ULL, 0x2AB6F1EE826FA875ULL, 0x1844DB0AA9EF0D59ULL, 
            0xB0F1F8144455D447ULL, 0xD4BD8E5DAC10F71BULL, 0x11F93CE27A4E01B4ULL, 0x9347445D26775612ULL, 
            0xEBCA4A4E6A28222FULL, 0x863D0469C6D4E2D5ULL, 0xBFAC87EB55A42946ULL, 0x9BEC6678AC745505ULL, 
            0xA18084D0B88BDF68ULL, 0xCA9833398950FF26ULL, 0x7754C3448FA7DEE4ULL, 0x4C17E600B60784F3ULL, 
            0xBF7187A3104CC3CBULL, 0x68795F12B55BD655ULL, 0x3346BA02282625E6ULL, 0x3B6563C6F8FF5EB9ULL
        }
    },
    {
        {
            0xB50BFAB873F37C2EULL, 0xDDA0CBDDB0DF49CFULL, 0xF98EF9F75635D352ULL, 0xD80A9806E3577907ULL, 
            0xD470C41D1E8E836BULL, 0x6B81BDE89535C4A2ULL, 0x22211660DE7E8323ULL, 0x68FBB3C61A8E8A9CULL, 
            0x70D4A2681CA40486ULL, 0x3B12ACACB2FAC0F1ULL, 0x810356FFC5C02429ULL, 0xA48449BE70C26172ULL, 
            0xE973881045B94109ULL, 0x223728B0629A9F4EULL, 0xF5F774AFE81C116BULL, 0xABB016EACC639143ULL, 
            0x1AD72964BF7D60D5ULL, 0x8243C7CD6ADE7A52ULL, 0x608BBD2C971BED1FULL, 0x187974975D9508B9ULL, 
            0x480BE23BCBDC7CBFULL, 0xD59B2861EB97AF94ULL, 0x768DFF593E67A625ULL, 0xC29120DDE36763A2ULL, 
            0x09451C36CD890E04ULL, 0x7DF5918F1BA51242ULL, 0xAC7DA3B4618AE37BULL, 0x959AED0C6DB6901FULL, 
            0x0E721DE3E6EB39C9ULL, 0x745B45AB9617E45DULL, 0xCF1041079B6235F9ULL, 0x781EA30DEFCD617CULL
        },
        {
            0xC03A544B47252AA6ULL, 0xF30A91E7F90E15CFULL, 0x99FB5854227763A9ULL, 0x47913A6FDCDE033AULL, 
            0xC8AB6A54F0B26897ULL, 0x49CAD668B6D7BFDBULL, 0xB987B8437145FF2DULL, 0x25D5DCE624F684DAULL, 
            0x7875DF9851A7C3CBULL, 0x4B7BDE30BE2549E8ULL, 0x13276256ADC65342ULL, 0x3F876A278C7361ADULL, 
            0xA5F6101398B71FC4ULL, 0xC574C8473EA5480EULL, 0x933ED274C192A432ULL, 0xD5C088482507FF10ULL, 
            0xCA8D77C63229F008ULL, 0xFF8A91B94FFC03F2ULL, 0xB345450E04E93D04ULL, 0x111450949F5BEE86ULL, 
            0xF993357336B03F4EULL, 0x138EB380ED5B0444ULL, 0x634D5EDC8BCB2F4DULL, 0xD00E6CBEA867CDB3ULL, 
            0x2F1DBBBD6E9FB0F1ULL, 0x86D009A85AA8446BULL, 0xF5456F552508C907ULL, 0xC52ADC5B5467CFBCULL, 
            0xDB69303454076EB9ULL, 0x3043D645AE4343BBULL, 0x1602E1181EF3C937ULL, 0x4604D315288C2475ULL
        },
        {
            0xF76135BB008FD41CULL, 0x16A179E63855C372ULL, 0x8B33C0B2F9A254A9ULL, 0x931E08F3A945B511ULL, 
            0xA60AA1C973C3E6EBULL, 0x08363D29D056F5FAULL, 0x9B2336167F3FB61DULL, 0x571FE43C0E6C575AULL, 
            0xE9DEE5A14E955B7AULL, 0xA6781D64C0CF0FF6ULL, 0x65D5313769A73DBFULL, 0x7DED18A27F87CAE2ULL, 
            0xC3077BCC868D56A3ULL, 0x4F1AF89638F1CB2AULL, 0x18264A1CE050DADBULL, 0x245F074175B312C3ULL, 
            0xAA460D23C319C205ULL, 0x3AFE59ADA8A2CC30ULL, 0x09F8C07A1C42678FULL, 0x7F0DA8D092A1E931ULL, 
            0x2AC0E9C7EF4BC83EULL, 0xDB38D403EC213276ULL, 0x09827AF24FDF3A8FULL, 0x092B3074300316A2ULL, 
            0x24EFB79F02496282ULL, 0xFD6E281E38C5A2DBULL, 0xE46D2384022C5189ULL, 0xEC61363356B45E94ULL, 
            0xDAD48795E7619A0EULL, 0x0DA5F04F5F9C17E7ULL, 0xE1A148343E72802EULL, 0x8F6D0AA2F3DEDD09ULL
        },
        {
            0x1507CB5FE3820617ULL, 0xEAAD4839B4916C3AULL, 0x84655D18AD5E5A1DULL, 0xFECDB678C3D6100EULL, 
            0xAA82952DF47E1EE3ULL, 0x3D65DFA867217009ULL, 0x2B1E5E51A5F0B160ULL, 0x4EBC785A4976EB8AULL, 
            0x1113E1B0C71B3466ULL, 0xA32CCE209538DF2DULL, 0x206FC77CC2BB10BCULL, 0xCC53843594E06EE1ULL, 
            0x1115069C0CDBA315ULL, 0xE6011EA1D054F8AEULL, 0x5E5CF53810183AFEULL, 0x951268F64F510F52ULL, 
            0x6953B0002CAE673CULL, 0x34635537C83A9C63ULL, 0x00CB7ABC1957F90CULL, 0x4EBBEBA3CCD58C38ULL, 
            0x003511D99A6BF5FDULL, 0xE95B1FBC61C5424AULL, 0x0CB9DA57DC03AAA7ULL, 0x272BFEC30F7BF19DULL, 
            0xEF6B66E18C17B3C9ULL, 0x780A541403495D60ULL, 0x8FE71E4167C45988ULL, 0x7565A7EF2F15FB43ULL, 
            0x75CA1B9348AD2BE4ULL, 0x02F1D4498537BB64ULL, 0xC05BD9FF60C9C7CFULL, 0xC85341F23909CEF1ULL
        },
        {
            0xB26AC6ED6BE7D56EULL, 0x51FE72A54B13E0B7ULL, 0x70F9FC8914035440ULL, 0x627A2B0FB0ECA231ULL, 
            0x931541935E4A464FULL, 0x0C183C98E85A6829ULL, 0x70AA097C6580B0D7ULL, 0x04663510D0C8A4C3ULL, 
            0x9989A7C7E553F4CEULL, 0x952887D601982D5BULL, 0xB519E4FC5D84CB18ULL, 0x6FBC631CF86B76EFULL, 
            0xF2A57773A2B986FAULL, 0x0AE447BABC8B40F5ULL, 0x18B43F9904513885ULL, 0x0DA52B40A8A514C6ULL, 
            0xF4E4F36B9E2E7E7BULL, 0x8C4EF9D7289EBFA0ULL, 0xC19DB03BC36671C1ULL, 0xD386B6E73B6ED540ULL, 
            0x6D1503F22A6C9BDDULL, 0x8A0CE4322BC66FE8ULL, 0xDF3C3D3986609385ULL, 0xB2AEAFFD6D329996ULL, 
            0x2D1420157A0B8E40ULL, 0x08DCF60CBD4AD534ULL, 0x3B365E93074BCE24ULL, 0x781552EEF4C8710AULL, 
            0x26D72151217CA251ULL, 0x364AECE93260197EULL, 0xC52BC3148EBC6864ULL, 0x908624383D2A04DBULL
        },
        {
            0x01E77851C45FF191ULL, 0x08593DC6A2292603ULL, 0x41C26A9266BABEF7ULL, 0x641CA750AB532772ULL, 
            0xAE88CF04F32EDAFAULL, 0x26F927C9BB4BBC49ULL, 0xAE4E66EC81CBD2FEULL, 0x930FFD3300414203ULL, 
            0x39E004BA7CB0E6ACULL, 0xE378B720F93C62CAULL, 0x66082DC0842BDF73ULL, 0xDF9CF8E3ED401B4DULL, 
            0xC354FB2EC53910A3ULL, 0x800C8C42FFE5ABD3ULL, 0x2DF057A4B60D6666ULL, 0x923024BFDEB68718ULL, 
            0x3F79908E3D04DD40ULL, 0x8B32302C80E75039ULL, 0xCC151A132E1B00E4ULL, 0xF9B39634467FB7C1ULL, 
            0xF93FAA1BA59D3F14ULL, 0xC5B8A1FFE6813207ULL, 0xC4CD1AD52E28A925ULL, 0x0C256E4D14FCE7CCULL, 
            0xEDF9ABCC80F93767ULL, 0xCC3B81A31066DF8EULL, 0x24BB7586E8419989ULL, 0x9CEB29D0B1BD234CULL, 
            0xF7AB4448401DC9ECULL, 0xAD4822FF52CCCC28ULL, 0x218ECC90E4C62EBBULL, 0x26BA9313C30C2515ULL
        }
    },
    {
        {
            0xA9C695590B6A3BB5ULL, 0x826A7D582F8287BFULL, 0x293BE43AC13692C0ULL, 0xE79795C1F641C158ULL, 
            0x45DDC44F35F56849ULL, 0x99241E9AB477048CULL, 0x8F92A8BEED7B50AEULL, 0x8723E45412AD762FULL, 
            0xE84289C4D6260D3DULL, 0x249772B9DC9A0D1DULL, 0x5DF26557741703F4ULL, 0x7EB30EC9D408BB6BULL, 
            0xCBABA1B30F0A6C4DULL, 0x326D12499067DE43ULL, 0xC655A4760E890530ULL, 0x425E165A43741A81ULL, 
            0x0699411152809BBAULL, 0x4921AC7D367D793FULL, 0x41C3B1A3E7D86BB7ULL, 0x34A4DA79EA70EA15ULL, 
            0x81BFE95C44E664C8ULL, 0xDF832163A4B7AF1FULL, 0x8A1A69DD84B04A08ULL, 0x9BD58FAFD4BE03A0ULL, 
            0x252B9C8081B7921FULL, 0x4B4D59C841891347ULL, 0x9B56A73431A64C71ULL, 0x8BA72F174E3DA235ULL, 
            0x209F0ECE96B30532ULL, 0xBFA380034E3B976AULL, 0x78BAE64557E6377DULL, 0x5562EEF9F9CB8CAEULL
        },
        {
            0x289DBBFC4C40D87EULL, 0x850CCA1B7DCAD180ULL, 0x80BA348256F396E5ULL, 0x73252B49FDDB87BFULL, 
            0xF67FF9E040F2DAD9ULL, 0x6E096AFDCD32B4ECULL, 0xE468C5A19EF08859ULL, 0x45133020C4B63391ULL, 
            0x8694E019D264288DULL, 0xB1B2E1450C630187ULL, 0x8C82AF884091C12FULL, 0x974AF89DD706EC72ULL, 
            0xE74A3FFC66DD6108ULL, 0x09DB86E690114105ULL, 0xD6C6B4E2F3036D3EULL, 0xFFAC82700B8026DBULL, 
            0xBBC984F75C838F4DULL, 0x4454991292626D8CULL, 0x5B7F334674DA1CFAULL, 0x52754B410F44C52EULL, 
            0xAD3BA88AA70DD9C0ULL, 0xA49A090AF246FF9BULL, 0x47B56FB5150E63AFULL, 0x2BAD58E3FCB999AEULL, 
            0xC3A2761DD3965592ULL, 0x8E40318539FD21C9ULL, 0x29FAB2250277F6FBULL, 0x9EA77F7BE5DF433AULL, 
            0x7A3139305349C91EULL, 0x3EF0BFF71F43F9CEULL, 0xE4ED1EFD4C81C0DAULL, 0x416EC144BED184D1ULL
        },
        {
            0x6167016911C8E26BULL, 0x62A37CFD4A046AE7ULL, 0x32AD5883A8C591C5ULL, 0x36632ED3B46CD73FULL, 
            0x2A959CF2D770B15DULL, 0xA7A3E113D1E88D04ULL, 0x568B05ABF25DDF4EULL, 0xCF533718002D3ACBULL, 
            0x07829ED19754D4EBULL, 0x19AA5289260BAEF9ULL, 0xDA0DF10F46BF1E05ULL, 0x452DD0F5F7C2713EULL, 
            0xC67D3D56AF683C60ULL, 0x81640123CD357A89ULL, 0xAC9B45C3CAA90C65ULL, 0x21EE7A35F171ADBEULL, 
            0x59DD6D32EDDCFA01ULL, 0x551EC368E4704915ULL, 0x1C28163B7387FEDCULL, 0xEEB2967141911231ULL, 
            0x3343EC5488BC9FCAULL, 0x3E33A172166B9D43ULL, 0x57C7C112B16E1D1EULL, 0x1A087B184437B9C3ULL, 
            0x37DEF11CD3A6A9E5ULL, 0x5D7CE077B5BD17B6ULL, 0xCCD472EE91A6D6F0ULL, 0x3B0DA1A70C1609EFULL, 
            0xE7A4490103DCB9F1ULL, 0x8D956BD0F91AA099ULL, 0x5DC91C8459BE92EBULL, 0x3FA57859F0248F19ULL
        },
        {
            0xE06E50EB52E2F04AULL, 0xA40AFFB307FB6260ULL, 0x8616DF73575E2065ULL, 0x07996733D2D91200ULL, 
            0x6D5947F5FB183C06ULL, 0xB8E4E76EE6BD77AAULL, 0x7ADB64814EE8CE7FULL, 0x2C5169CDEEDF1ECDULL, 
            0xD9B9CB0E976EBD37ULL, 0x8C49453278D77498ULL, 0x31BFC34F5B6ABB52ULL, 0xB8BB96266299AC6FULL, 
            0x4ED3153B60557958ULL, 0x0F92B22AF9C765E6ULL, 0x17633587C9D90C60ULL, 0xEF3F3A04249F5422ULL, 
            0x8E4749B94ABAEDC5ULL, 0x87C2801DE9DC66D7ULL, 0xAD9122A1E1324ECFULL, 0x704698CC95859D2BULL, 
            0x19308247EB27115AULL, 0x537B952257324739ULL, 0x35E20C0D8D8954BDULL, 0xC2F61748E00B0482ULL, 
            0x19454A56BAEDA137ULL, 0x3784F52B6BE17228ULL, 0xA7B8CFB255B1A95CULL, 0xDC0A889A5DF09D94ULL, 
            0xCB842890FFC30177ULL, 0x12D73F918BD4C244ULL, 0x2844EFDF60AF426FULL, 0x22135FA41E92D768ULL
        },
        {
            0x0D31B85F3F175DB5ULL, 0x6ECF19ADC838C54CULL, 0x9F86768B899D6557ULL, 0x90265958251F031FULL, 
            0x1A879BD9BE153B5AULL, 0x44A36225F4EF68E0ULL, 0x33838684B035B868ULL, 0xCC5DC40EF795144BULL, 
            0x71600E4D06755E23ULL, 0xB3162686936FCFE9ULL, 0x7BF3B8571C0CDEFEULL, 0xC03BB4D402AA19AEULL, 
            0x44608C9B42B1CC95ULL, 0xF2838CD599873FD1ULL, 0xC449228AE75D53A3ULL, 0xEF5C24DDE889BADBULL, 
            0x58C0C9AAAA013030ULL, 0xC29F43B93A6DBBABULL, 0xF7EA1B588BACC495ULL, 0xB4F601446C09A41BULL, 
            0xA26EB0D975397C72ULL, 0x65E46B4A088D1181ULL, 0xBD41877DB3609D93ULL, 0x5D14BFBF56FC2B97ULL, 
            0x5B8182E86495EB40ULL, 0xC9C5A641B4C76C2EULL, 0x93E9CA47C0E59112ULL, 0x78BAF4BBD6AE02D1ULL, 
            0x2619E3197B7D31E3ULL, 0x4627A5D781858EA8ULL, 0xB394616887BB1D53ULL, 0x33DDD2008CC04022ULL
        },
        {
            0x1CDC3532D093FB96ULL, 0x37C2593463B4C7A0ULL, 0x468032AEC8C41042ULL, 0x68C9725E93C9CC6DULL, 
            0x280846572FEB1C2EULL, 0xB6EEAE0169EB51FEULL, 0xC51C3240A166517DULL, 0xE7A7B26684435481ULL, 
            0x4AADCCCFF3E5B8EBULL, 0xBAE6EAC170EDB293ULL, 0xEA5B216D33974F63ULL, 0xCDD09BE9BA3AD7D1ULL, 
            0x96D9E4C7066F86E7ULL, 0xA4D8157C5F5FF43AULL, 0x256E1A86A2B3D093ULL, 0x84F8F91B77255199ULL, 
            0xE391F9A375DB5C7CULL, 0x8C3D31FF2C74F578ULL, 0x88A08546F72F2DEDULL, 0xB3318D03635E89A8ULL, 
            0xD158F4A203DA560DULL, 0x779AF773A2C81AA4ULL, 0xC429C87413CF2C78ULL, 0xEF060814B51278F2ULL, 
            0xA933AB5AB1487AEAULL, 0x97F71C30FC3361D5ULL, 0x6CE38E5FBD26EB9EULL, 0xD6C1A06D7A5CB3DBULL, 
            0x23421EB649341A57ULL, 0xFB02012544848DC2ULL, 0x8354C4116CAF4DE2ULL, 0xD416C8D213A52174ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseHConstants = {
    0xEEF21599083BB522ULL,
    0xF4B22FEEF1544489ULL,
    0x24B6650B3D07F3C8ULL,
    0xEEF21599083BB522ULL,
    0xF4B22FEEF1544489ULL,
    0x24B6650B3D07F3C8ULL,
    0x0319429C2A2F069AULL,
    0x2B8CCD5DC85EB76DULL,
    0xBF,
    0x3A,
    0x24,
    0xB9,
    0xF5,
    0x67,
    0x24,
    0xB8
};

