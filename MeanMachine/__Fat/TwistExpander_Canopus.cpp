#include "TwistExpander_Canopus.hpp"
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

TwistExpander_Canopus::TwistExpander_Canopus()
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

void TwistExpander_Canopus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD6DE346FAAF6ABD7ULL; std::uint64_t aIngress = 0x8363AD0E1F192435ULL; std::uint64_t aCarry = 0xEE993C132B9790C4ULL;

    std::uint64_t aWandererA = 0x9B818B9236826324ULL; std::uint64_t aWandererB = 0xC6A1A5C26B0604D9ULL; std::uint64_t aWandererC = 0xD1D205EFB537A7B4ULL; std::uint64_t aWandererD = 0xB54A7E938FC35845ULL;
    std::uint64_t aWandererE = 0x9DC028718BDE8F14ULL; std::uint64_t aWandererF = 0xAA37D9063367DC2FULL; std::uint64_t aWandererG = 0x9EE701FF9E7389DFULL; std::uint64_t aWandererH = 0xF420928568E8CB95ULL;
    std::uint64_t aWandererI = 0x912D6A6EE2030510ULL; std::uint64_t aWandererJ = 0xAE94349686B354E0ULL; std::uint64_t aWandererK = 0x87586FA9A1995D33ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17509677589524086141U;
        aCarry = 13261759199630626434U;
        aWandererA = 17312242357162455624U;
        aWandererB = 14795874088482927261U;
        aWandererC = 14337784731072231770U;
        aWandererD = 10397399387650277647U;
        aWandererE = 9294114577855405850U;
        aWandererF = 10573810214681228527U;
        aWandererG = 13733774322513117547U;
        aWandererH = 15901195664266711509U;
        aWandererI = 18182424408816260083U;
        aWandererJ = 12216250428094838460U;
        aWandererK = 12195076050490970333U;
    TwistExpander_Canopus_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Canopus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x93F93B15ADB3B03CULL; std::uint64_t aIngress = 0x8991D1625C3E61BBULL; std::uint64_t aCarry = 0xDC141929FD85D32AULL;

    std::uint64_t aWandererA = 0xD5041D7498926E7BULL; std::uint64_t aWandererB = 0x823A872B9DEA99B8ULL; std::uint64_t aWandererC = 0xC1D01976E770AE7FULL; std::uint64_t aWandererD = 0xF9ABE7D83E7B0412ULL;
    std::uint64_t aWandererE = 0x83B440931D93AA25ULL; std::uint64_t aWandererF = 0xFD4979829DE72EE4ULL; std::uint64_t aWandererG = 0x91B13A463BCB5C88ULL; std::uint64_t aWandererH = 0xB4F0246F149EE8C1ULL;
    std::uint64_t aWandererI = 0x8F4E63A96FB419B9ULL; std::uint64_t aWandererJ = 0xACEA5D8CD81491B1ULL; std::uint64_t aWandererK = 0xD1DC833CF7F0CD6EULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17353770925758842667U;
        aCarry = 15776620121409222895U;
        aWandererA = 11209895589535989906U;
        aWandererB = 16990334974217697267U;
        aWandererC = 11560754328056436549U;
        aWandererD = 16152778648803347446U;
        aWandererE = 14054163948840680078U;
        aWandererF = 10797283698169222950U;
        aWandererG = 13825140498152538995U;
        aWandererH = 11285044310387642798U;
        aWandererI = 16321814219678049937U;
        aWandererJ = 15592376394335671878U;
        aWandererK = 15707711450472367765U;
    TwistExpander_Canopus_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Canopus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB34696FA03216563ULL;
    std::uint64_t aIngress = 0x88F33A826F3B6ECEULL;
    std::uint64_t aCarry = 0x9C2A8766E3FBB766ULL;

    std::uint64_t aWandererA = 0x8DDA9EC30ADE659FULL;
    std::uint64_t aWandererB = 0xFBECBACE58B3B2CDULL;
    std::uint64_t aWandererC = 0xF325A9EA4F41CDF0ULL;
    std::uint64_t aWandererD = 0xE2E5240DFC888EADULL;
    std::uint64_t aWandererE = 0xA3BE12573EC86A4BULL;
    std::uint64_t aWandererF = 0x806E435562B08F37ULL;
    std::uint64_t aWandererG = 0xE3D42E2D0D16BCEEULL;
    std::uint64_t aWandererH = 0xAB98EE467B11BB8BULL;
    std::uint64_t aWandererI = 0xB53A8756871F45B2ULL;
    std::uint64_t aWandererJ = 0x95314B9C8E42875FULL;
    std::uint64_t aWandererK = 0xCB26CC4C96874CD2ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneC, 0);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneB, 1);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneD, 2);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneA, 3);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneC, 4);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneB, 5);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneD, 6);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneA, 7);
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
    TwistExpander_Canopus_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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
    TwistExpander_Canopus_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 14 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1838 / 1984 (92.64%)
// Total distance from earlier candidates: 24142
void TwistExpander_Canopus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 443U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1133U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 101U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1111U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 389U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 433U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1820U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 650U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 982U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 880U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1494U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1515U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2040U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 971U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1564U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 182U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1656U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 799U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1469U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1215U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1594U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 872U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 662U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 858U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 59U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1360U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1122U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1021U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 135U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1420U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1449U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 876U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1955U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2022U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1655U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 891U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1200U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 17U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1809U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1435U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 617U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1256U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1796U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1312U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1770U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1085U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1927U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 458U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 429U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2023U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 525U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1545U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1811U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1815U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1016U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 0U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 42U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1269U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1003U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1491U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1649U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1349U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1959U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 45U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 868U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 995U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1115U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1236U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1418U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 138U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 234U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1429U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 855U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 800U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 465U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1072U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1322U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 100U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1636U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1279U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 23U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1608U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 648U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 860U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 361U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 104U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1548U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1982U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1744U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 796U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 466U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1918U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 131U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 883U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1185U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1368U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 892U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 235U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 231U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 394U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1695U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 373U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 422U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 790U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 642U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 545U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 30U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 405U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1393U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 709U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1710U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 492U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1742U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1917U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 289U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1885U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1238U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 179U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1835U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1908U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1358U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 166U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Canopus::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFB6F3307F3F65C44ULL; std::uint64_t aIngress = 0xC08097C76081C2CCULL; std::uint64_t aCarry = 0xF0F45FDE1BB8CFBFULL;

    std::uint64_t aWandererA = 0xE4E48A4D1A0C2EEAULL; std::uint64_t aWandererB = 0xED3FD5E9EB4E1ABEULL; std::uint64_t aWandererC = 0xC2FFE8E3B3A86194ULL; std::uint64_t aWandererD = 0xC75686E84E330FD7ULL;
    std::uint64_t aWandererE = 0xFAFF48CCE85EF106ULL; std::uint64_t aWandererF = 0xE348204DE76FBC00ULL; std::uint64_t aWandererG = 0x85C0692E9D75E8C7ULL; std::uint64_t aWandererH = 0x8AD3939714B712B2ULL;
    std::uint64_t aWandererI = 0xA1B4B901A8CA8CD7ULL; std::uint64_t aWandererJ = 0xD490666A14707E57ULL; std::uint64_t aWandererK = 0xC69AE9DC61298387ULL;

    // [seed]
        aPrevious = 13921494342801566715U;
        aCarry = 18302195814159153421U;
        aWandererA = 17507361129530527754U;
        aWandererB = 16775899185022649235U;
        aWandererC = 12961889180107873364U;
        aWandererD = 9728167932734744661U;
        aWandererE = 11220501363334713924U;
        aWandererF = 16288168380352145377U;
        aWandererG = 10815628718191942568U;
        aWandererH = 17344318177795004808U;
        aWandererI = 9724193444859010919U;
        aWandererJ = 14519949735718461482U;
        aWandererK = 16675882504442199819U;
    TwistExpander_Canopus_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_G(pWorkSpace,
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
        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Canopus_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 14 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7120; nearest pair: 509 / 674
void TwistExpander_Canopus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5994U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2962U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7432U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3749U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3506U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2853U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7698U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5188U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5133U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3863U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4178U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3000U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1275U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1204U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3963U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3710U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 947U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1327U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 515U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 788U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1565U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1911U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1844U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 170U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 387U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1175U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1785U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 671U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 46U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1613U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 217U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 870U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1031U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 14 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7134; nearest pair: 474 / 674
void TwistExpander_Canopus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3894U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3649U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6433U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6246U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3606U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4842U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6771U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6940U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6660U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3795U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3369U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4701U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1471U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2528U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2638U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5523U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1192U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1150U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1207U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1732U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 943U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1210U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1862U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1431U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1316U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1907U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1603U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1310U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 144U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1681U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1152U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1405U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1754U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1619U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseASalts = {
    {
        {
            0x6078AE2F76E1F760ULL, 0x12F6D34FF450AEC5ULL, 0xC361C477707E17C6ULL, 0xFA105506D75E178FULL, 
            0x5351701A226D8AD6ULL, 0x246BF9D97E32AE47ULL, 0xDF93A2707307DD25ULL, 0xE6441B56F372F064ULL, 
            0xD841F494AE4A1653ULL, 0xF7403DB4E783E9D5ULL, 0x4DCA36DE7403416EULL, 0x71A7BB6B0CF32EE4ULL, 
            0x1231888A1CBED640ULL, 0xC42E51163DC3129EULL, 0xF488318EC849C7E8ULL, 0xED8B5B3E8A591471ULL, 
            0x64D0EC319BE1413CULL, 0x61F3578058BD69FCULL, 0x2B10BB8B1E466672ULL, 0xD6947F8DBD146F15ULL, 
            0x676560C8274845E8ULL, 0x88E333BD888901A5ULL, 0x453DFF48BBF04FF8ULL, 0x596543A54B018DCDULL, 
            0x01EC96B91EDEA867ULL, 0xFEE3B6D50268B862ULL, 0xAEB5ECEE0EE5D6EFULL, 0x005BEB1EC91783DDULL, 
            0xBB8D91F5957E27E6ULL, 0x92B8AD72D353E9B2ULL, 0x03D1F30662F67963ULL, 0x24383C4400FE4A2AULL
        },
        {
            0xED005F732938B3ECULL, 0xE991DD64D98D1318ULL, 0x889A36ACFDE92876ULL, 0xBE668C45BCE8E129ULL, 
            0x749B03C737F686B2ULL, 0x49C1775A446DB3ACULL, 0x9E4E4199E3F7943CULL, 0xED369E52F3436165ULL, 
            0x33F8094C4C488EF0ULL, 0xE437163677B6FF19ULL, 0x6AEA662E3B9A3144ULL, 0x06390BD32D687EC8ULL, 
            0x896FC27FD2E5A6ECULL, 0xC0EB87CBCF8674A1ULL, 0xBD1D7CE2142935CBULL, 0x58BA82351710FD28ULL, 
            0xB63D45845D3AE955ULL, 0x8568D6691BCE1051ULL, 0x2E1A5D759B7C079CULL, 0x06111A736BF231BDULL, 
            0x101C853745185C09ULL, 0x2FE5A4208459D3E2ULL, 0x5260CC7EF651DD52ULL, 0x3434102BC7EC9DD8ULL, 
            0x5CFA2740347CEBC6ULL, 0x9B8342662AD69CA2ULL, 0xCA8B5881CD599B61ULL, 0x56FE32733E6299A0ULL, 
            0x31F8D2C2180A7695ULL, 0x0C289BFE38020322ULL, 0x2678058D063D528DULL, 0x9866658CE8A7CCCFULL
        },
        {
            0x982A44569389099FULL, 0x4F5D0AE5A611C81AULL, 0x213AF533AE35967CULL, 0x9A164CBC861E05D9ULL, 
            0x5109CAE3A8889831ULL, 0x4CF1C7F7E7FEA188ULL, 0xF4B5C63E0D1BA512ULL, 0xB831187C912EA8EEULL, 
            0xD03C1D3AAAFDB71DULL, 0x9ACC05931788F0C1ULL, 0x870E4416123FDA45ULL, 0x7ABF9C93BBD41027ULL, 
            0x0DF6D917115531E4ULL, 0x90E476D8541D452BULL, 0x5CDB368C1A7BC071ULL, 0xD522A84D9C5564D0ULL, 
            0x6153417D1FB45378ULL, 0x0806EBAEE5FA591BULL, 0x9DA6DC06ADD46729ULL, 0x4C06BD05A81BB33BULL, 
            0xE78CA75FF423DB71ULL, 0xC72B243B6447906DULL, 0x8D6E2B9FD0EE922AULL, 0x69EA1DB919FC78ABULL, 
            0x9617AB71F51CB905ULL, 0x7AF37FD69272DA3EULL, 0x331D47A7EA0377DFULL, 0x091C3BD4BDF69B23ULL, 
            0xF0E8F134269E8C36ULL, 0x0203A45600CDCDD4ULL, 0xB168CF1EB4773DB9ULL, 0x29542DC762702821ULL
        },
        {
            0x1870B39F463C81D7ULL, 0x24D687FB9EE53239ULL, 0xC2B94F31B6E10659ULL, 0x9632D3683898E034ULL, 
            0x1E6008A865B52122ULL, 0xDE23B85392B1F223ULL, 0xE70D83DB6BE230C4ULL, 0xB14D6A7FC01963A5ULL, 
            0x89D7A29B54BAF6F7ULL, 0x4F13D41928E480CDULL, 0x12A6D5909191904FULL, 0x9AC0519A8DC9611AULL, 
            0xE5EE68C3340D64F1ULL, 0x26BE948AA4DD5E34ULL, 0x9F1C1E2A8801D5A8ULL, 0x5FAC1F3CD11C1F9BULL, 
            0xB99AEC7BCC07744CULL, 0x5E1BD926B95938E6ULL, 0x820F79C189725942ULL, 0xE3BA2DAA962D096FULL, 
            0x3E0EF02B716E6636ULL, 0x86122E1B0CF4768CULL, 0x9156DAB8886A6EC8ULL, 0x7A216008389118B2ULL, 
            0x953CC7B434A1064EULL, 0xCEBAF4EA846706AAULL, 0xE7ED9BC8B28DFD3EULL, 0xFF6C417EC16EF106ULL, 
            0x1CD1E9A20878F8E9ULL, 0x8BF72A5D90F896CDULL, 0x2E61432C1CFD1DE7ULL, 0x8E9F49333B1E77F4ULL
        },
        {
            0xADC5B194964A66C4ULL, 0xB01997AAC3513F73ULL, 0xF1F7E122B7505BA9ULL, 0x648ECBCDD322ED21ULL, 
            0x362D62F0918EB752ULL, 0x8C3B12DAF9FAD82AULL, 0x1B93B6D82705A2DEULL, 0xD20C7743B3F1B2B9ULL, 
            0x512AE175DFF22562ULL, 0x3A861FBCC4093066ULL, 0xCA79F2E24DFBE01EULL, 0xAA37BEAC0254610DULL, 
            0x2EE4A26CD9B245C8ULL, 0x996E70A31A91A37CULL, 0x1EF2ED5BE0F55AFEULL, 0x7E766ECA6B1A00C6ULL, 
            0x617D9BA57781ABEAULL, 0x35DE064B5BEC344AULL, 0x65A5EEE1D57EE060ULL, 0x44995D97197B2C4DULL, 
            0xAE5603CF8920458AULL, 0x8B48799860F1699AULL, 0x6560030CA8D72EFAULL, 0x2E68F2BE88297C1EULL, 
            0x31E7760C6E207B8CULL, 0xC2655B6563138C0BULL, 0xE903DBBB8EEE3F82ULL, 0x3AF886AB8C22AC10ULL, 
            0xE961BAC9B96FFAAAULL, 0xFEC0C9F627AA21CAULL, 0xC53ABCC5BAC10698ULL, 0x29D9A7C1836A0B5CULL
        },
        {
            0x92EB696D375A0341ULL, 0x798CF7D48493503FULL, 0xD569A99BB3FD3151ULL, 0x9CE990E1A00287B1ULL, 
            0x728B8E5D685BF966ULL, 0x4E1A1CF7809BC612ULL, 0x4752162F065E7D96ULL, 0xB08DDB12467699D7ULL, 
            0x0456867D01BDCB3EULL, 0x6A93E101EB1AB614ULL, 0x7EE5987474FFEFBFULL, 0xD2AFC5D3CEACFAD4ULL, 
            0x6349FBB033A58CDFULL, 0x33BE7E0A34FBA0BEULL, 0xDDB3E48732765859ULL, 0x9C8F9272CF027B17ULL, 
            0x8C5CAAEDC51C516DULL, 0x7C0A5683161975A9ULL, 0xE5D27A1520B1F3A0ULL, 0xC5B9399B4C1E10D2ULL, 
            0xD91E0948658CE112ULL, 0xDDD1B9F4594D3D42ULL, 0x19C7C648F0ACD9A6ULL, 0x27F214306D962675ULL, 
            0x95716E5A4435DC58ULL, 0xF190B12B818690DEULL, 0xEA7915FE015A1098ULL, 0xC2C343E50879491BULL, 
            0x4CF77F35BFB77296ULL, 0xDBE9A8F2D2D420E1ULL, 0x5C58781017060F34ULL, 0x064008DFE0D86B76ULL
        }
    },
    {
        {
            0xA19600CF64EC8E55ULL, 0x20E6C1D0AB84E2F2ULL, 0x44ED9B8909228D27ULL, 0xB5E71902C6555B69ULL, 
            0x67A7AD8DE08B70C7ULL, 0x7A3054F1269AB8C5ULL, 0x24791E79428F5136ULL, 0x866F2944F4425642ULL, 
            0xA821DF6E1B2D258AULL, 0x5C9C5EBBBEEBC504ULL, 0x062E88918268E2A1ULL, 0x7593965CCA97111AULL, 
            0xA68A19E09F85FD56ULL, 0xE8517408E3FE645CULL, 0x62E9E4C2B8DF79B4ULL, 0x6CB1F2C81C221A05ULL, 
            0x0A8B04C478B912F6ULL, 0xA802F15CAA1F089EULL, 0x925F5DD7C7EE2E5AULL, 0x70C82656F6BCEF38ULL, 
            0x0C7D10CDAC394BB6ULL, 0xC6C7FE948C5D6B25ULL, 0xBC0E99C5EB7D7AF9ULL, 0x10B1387069619652ULL, 
            0x4E9EC2E43D657763ULL, 0xF8B9C3E288E47FDFULL, 0xC0C6034AF0D9DB8AULL, 0x7D063F6D5E88ADC4ULL, 
            0xA049C1B4F79997C2ULL, 0x1CBEC807CB7B387AULL, 0xC7B164A01B050123ULL, 0xE484FB11A185F637ULL
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
            0x25A2692999289159ULL, 0xBCB783BB9B73ABC0ULL, 0x3012A6139B449E31ULL, 0x01DA042D404DF05EULL, 
            0x7FE90878739CEB28ULL, 0xEEB74FD41FA177DDULL, 0xF3DC5F9D64C6BF5EULL, 0x9E3B003A2C6859F4ULL, 
            0x30FC6873911C7012ULL, 0x2D4D41B2DC9AC171ULL, 0xCF828607E638EADFULL, 0xFB63B4BF310195BAULL, 
            0x57BEC3A456339641ULL, 0xCC88455E375E4E5BULL, 0x387A2CCE959E4106ULL, 0x8FC547FC75915E13ULL, 
            0xE729FD80E40E2977ULL, 0x568FC0E80ECEAC33ULL, 0xEC04F3FA4C75BA3BULL, 0x06CD803DAB92ACB1ULL, 
            0xA3B01A72A8084387ULL, 0x1AE3A1E08D5B8D32ULL, 0xCA37631B47A37521ULL, 0xF9CF869004EE793BULL, 
            0xC5BC6C5D554A9D11ULL, 0xF2629788670D9644ULL, 0x03177269D40AE45CULL, 0x5AA74A8833EF74E5ULL, 
            0x441D9684C2B704C7ULL, 0xD0CF4A73F907304EULL, 0x46226BF90A2EE228ULL, 0xA362DA80C0976324ULL
        },
        {
            0x2F989F2AB7226822ULL, 0x12B0EBB402C357C9ULL, 0x4CBB1D7D99511934ULL, 0xE945068D5B5BDF21ULL, 
            0xA2F66D1353B79B67ULL, 0xC6CF74FE9DDCE345ULL, 0x34F94C578BBCA09BULL, 0xA6F1594CCE273A87ULL, 
            0x30A58D4806998BE7ULL, 0x68DB39F68DD80464ULL, 0x481E896666AE6F66ULL, 0x0625AAF9A1D8604BULL, 
            0x9C03AEDAB1A3A966ULL, 0x5F1A23C000A38A02ULL, 0x7E87641AF10833CBULL, 0xF168989F0F2586FAULL, 
            0x788D07E086A229C9ULL, 0x94AE375F7E0C897EULL, 0x3D5E7D86DDDCF558ULL, 0x9BDAD1B629CEF267ULL, 
            0x01FE47F4DA9C4A18ULL, 0xB2F41D98B2305FDFULL, 0xF30A442C589FA402ULL, 0x96FEACB8B200D574ULL, 
            0xE28F9360157256B3ULL, 0xBCE24EA5126BE187ULL, 0xA99D83511E97634AULL, 0x1246ED85F4A99723ULL, 
            0x458734E416ACF0C6ULL, 0x79E0C44EDA079CB6ULL, 0x42BC8E081ED2F6F4ULL, 0xEC07A6E9E934408BULL
        },
        {
            0xAD78CA357CB1A99FULL, 0xA59EA7F8545C1B32ULL, 0xE897DAED5C26A3C2ULL, 0x7C823BAEC9C86467ULL, 
            0x9BE431BB591CEC5AULL, 0xF19335C20A21D4E5ULL, 0x08526A72A73CDA17ULL, 0x98BA58DA2949107FULL, 
            0xDAE63B5F0899C86AULL, 0xCB719C548B6C6ED1ULL, 0x9281D2AD1B918322ULL, 0xD8425FF2EA92F992ULL, 
            0x667500325CF56E04ULL, 0x64CC8C8078C8E7FCULL, 0xD86953B8488AAF1CULL, 0xBB273C6CB4B99C96ULL, 
            0x34D806C1DF67362DULL, 0x2B9127E6100A9786ULL, 0x26B00C61ED8BE7BBULL, 0xD2A6A83A3DA24BCAULL, 
            0x632E4D87FF326684ULL, 0xDAB97A0F68E8992AULL, 0x67CD0AABC4FBB861ULL, 0xD91266E2D4D0CE8DULL, 
            0x1569F0B5B1207FC5ULL, 0x92F6C0DA89971F3DULL, 0xAACB759511958ABCULL, 0x975B74C32510F001ULL, 
            0x4FC66E5D96E2A5C1ULL, 0xA129684C3C338F7FULL, 0x53453363AE7FDD1AULL, 0x84E58C81704D7076ULL
        },
        {
            0x3B115A62BD6AB529ULL, 0x893D67AE937B0AE5ULL, 0xDDF4226FC0C621BBULL, 0x00118727A9667DE1ULL, 
            0xBF193FF9CE60591EULL, 0x8303E7B9100E4BD1ULL, 0xCF9AF1FE3DCC1B44ULL, 0x233D35FA3B98D2E8ULL, 
            0x094EB16319890C18ULL, 0x42385B003AB51FF9ULL, 0x6DB3FC9524F2ACC0ULL, 0x630CA7D18686F080ULL, 
            0x1C2260CFD01C8FD8ULL, 0x15ABE9DB82668C8FULL, 0x074422D98849BA2EULL, 0x62955E10FCBCE4D3ULL, 
            0xA409FB2BD40C4156ULL, 0xA3148229813C27CAULL, 0xDB5F978EC6D21125ULL, 0xCA4186012465C7EEULL, 
            0x0FE06FF54C3A8467ULL, 0xBE87BE3719BEA390ULL, 0xFBE0A14AAA52B105ULL, 0x2EB726D09E2A4805ULL, 
            0xAE366263B9795C43ULL, 0x7CB3FA945D4AE798ULL, 0x0B88277D2F5F351AULL, 0x0F409659C68230C9ULL, 
            0x835BB7C3241B4725ULL, 0x92B9018F3D0C8ECFULL, 0x315D81D0A8C2E06BULL, 0xCAED82363C054A69ULL
        }
    },
    {
        {
            0xFA13AF41ECCF7457ULL, 0x30B7DE35D780F9CFULL, 0x848010359616756CULL, 0xC9F7101868374702ULL, 
            0x4E165B1229766616ULL, 0x1B44992752199CE9ULL, 0x23811C2001B11E81ULL, 0x66698BE560F73863ULL, 
            0x68794B9C4984DCD9ULL, 0x7E2B01213A08E353ULL, 0x5E9217BD0719DAC0ULL, 0x411CC288AB831DAEULL, 
            0x49074A8E403E41C9ULL, 0xD4CEA8E4433F4E55ULL, 0x6D5870350283E640ULL, 0x9D61A34C5B633BEDULL, 
            0xF7CCE82051673F50ULL, 0x468FAA7925EADF0FULL, 0xE9EB4265DA76865AULL, 0xB92815E6566542C3ULL, 
            0xF7880CF5E84CE491ULL, 0x83AC35F6FCEB222AULL, 0xAB937CA81FBC2463ULL, 0x11706C6B770A6804ULL, 
            0x419FB9E4338D45ACULL, 0x34A04B7FAF878301ULL, 0xED6D4C35D293E079ULL, 0xE398A4BA3ABD6AECULL, 
            0x6EBBD3AD0E9CB145ULL, 0x3F02C5B87FD3CB14ULL, 0xF45CAF58A8440FEEULL, 0x86711275E2477E30ULL
        },
        {
            0x6F6A8C642493995BULL, 0x48BEAE2C05C15070ULL, 0x68AC402BEAD7796CULL, 0x7E7988665521DB49ULL, 
            0x0D705F0CF5877BCDULL, 0xAF16A4ABDE307466ULL, 0x6979285A1E7B60C0ULL, 0x30973EC7A158D09DULL, 
            0x1B0A8A2BBDDA020CULL, 0x51BB1072A0C8F55FULL, 0x87EBF8F051A23008ULL, 0xA5FCC6B55E1B8E92ULL, 
            0x2CA51A4EF4CF2BFFULL, 0xEF2FCD91D60EA4EBULL, 0xA31BB6DBBB389805ULL, 0x0836D9230E11AC64ULL, 
            0x0ACC1202D2671A12ULL, 0x044892318B058CD2ULL, 0x844AD9D5548E753DULL, 0x1C848AE80E21E564ULL, 
            0x89249BFF4C7D2AE4ULL, 0x63C517898E7DB9E8ULL, 0x3F94BB3325AB7722ULL, 0xD5E95A86CE5BE7BCULL, 
            0x58BF901F11995338ULL, 0xDB966275778BCBBFULL, 0xB3EB0F90D2BBADFBULL, 0xC917AA70B95073F1ULL, 
            0x87D019CF67E3095DULL, 0x17AA2FDA1CD7F1C6ULL, 0x27383F9C1F7241C8ULL, 0x2B956AE49C9A3B40ULL
        },
        {
            0x90BDA783733D2198ULL, 0xB69B223DFFC7829FULL, 0x6AC91A9694E3B2BAULL, 0x9C0BBB281066CBD3ULL, 
            0xD5535BD9F78DAC8AULL, 0x7E4D3A8D257011FAULL, 0xB7AC9B7AE24F5676ULL, 0xCA66691B268D2FBCULL, 
            0x87001913895795B3ULL, 0xDDD8B4CA4B4C7F2FULL, 0x5D56A6FF25AC990DULL, 0x3DDA6E75A57AEC43ULL, 
            0x956A073A7FE4E27EULL, 0x906181C55441B236ULL, 0xE2264B713D41348BULL, 0xF02335CB951778DEULL, 
            0x34CD86D1305FE06CULL, 0x1CF315052AC467B1ULL, 0x19C05A728F1F2582ULL, 0x07A268BF68B2B45EULL, 
            0x034D94CE0C4AA609ULL, 0xDFDCEDFBD02654F3ULL, 0x41AB44F578A97E45ULL, 0x751FA5620F9D6D88ULL, 
            0xDB04DAAD0AC92E4CULL, 0x6015E978EA4566CAULL, 0x0BF95B69B28810A8ULL, 0xFB45871F594ECC9EULL, 
            0x11F71D0A909B5976ULL, 0xAD355FB88F581011ULL, 0xA5B3BE25A2B4094DULL, 0x4BDF8C75C2AEAC4AULL
        },
        {
            0xE1FCF0A37D397B0BULL, 0x838F93FE491DF243ULL, 0xF69FE1AA20D49C89ULL, 0x8971A534A4D502E9ULL, 
            0x3C3A365F72FC31AAULL, 0x3E207ED43B408ABEULL, 0x07991719DCACE08DULL, 0x02B45D2F64868691ULL, 
            0x4559383056EE467EULL, 0x7DF30AF1E4A10ED1ULL, 0x025DC77BF693DCC2ULL, 0x695778CA233BF32FULL, 
            0x50C1F5EC0A1D6B1FULL, 0x17B3B4A4331679CAULL, 0x96675401F1C082F3ULL, 0xB02CAA86C808DB64ULL, 
            0xBA031D61CD602630ULL, 0xBFF30B31F1C8067BULL, 0xD2949285942BE81CULL, 0x2B3E8158171CF79AULL, 
            0x90D05EFB3807E059ULL, 0x85E2E6C5F5DF2D66ULL, 0x7548E7F5B5429152ULL, 0xFABF549F273902C9ULL, 
            0x0849BB254FF98315ULL, 0xB17D25CA7EE003BCULL, 0x5CFFE1C5E710839DULL, 0xC74BAB74725B0478ULL, 
            0x6431BB1EC34FDF64ULL, 0xB1D0FD544CE7A610ULL, 0x54BDC8B0B50C22F2ULL, 0xFF5E3929B25C0AABULL
        },
        {
            0xC3A05780A7844227ULL, 0xDC2A2094554F4DC5ULL, 0x791599F3D91100AFULL, 0xCCD53C4AB30EF8F7ULL, 
            0xFD1AF14E46B3AB0CULL, 0x7F8838AB3AE7DF88ULL, 0xE14481587AF6AB50ULL, 0xA7D873182835B556ULL, 
            0xF6003823432359BCULL, 0x80F4561A1F518843ULL, 0x15835752069EF12BULL, 0xFE28180839F938C5ULL, 
            0x7C89BDC1F30D367FULL, 0xD20CF0D24402ED2CULL, 0x19589D011C13E0B4ULL, 0x3B986FE067A30B37ULL, 
            0x6F272F67B3930880ULL, 0x798835C03F905FE8ULL, 0x3FCD9CEF16607FCCULL, 0x30EB1D7D294AAC6BULL, 
            0xE2169D2A69A33024ULL, 0xDC29AB87779E182DULL, 0xC1FF9119DCF640BFULL, 0x5B5FA2382AF61F38ULL, 
            0x4743D5591A5DC7B1ULL, 0xAC280B054691C444ULL, 0x97DE851E52AAA303ULL, 0xE57626AB1DAAE71AULL, 
            0x7B2889F8A01C0E4DULL, 0x4BD1D838EE1036A4ULL, 0xBDE82F59239B9755ULL, 0xA104D9A4AE912A1EULL
        },
        {
            0xCB014ECE75C6F509ULL, 0xECE57E39AD734980ULL, 0xED668C67F09BA31FULL, 0x848B2BA350C95430ULL, 
            0x49ED837BFF3BC3FAULL, 0x7EDE996C93BADBC0ULL, 0xF2C764BE98B37958ULL, 0xA51FB33588036770ULL, 
            0x495F882C21D38DDEULL, 0xE7DBA544486F408AULL, 0xF0FDA7141550E838ULL, 0xC764C4F9C6F8A335ULL, 
            0xFC76E72BF33A764CULL, 0x29735D6727B88F9DULL, 0x010BBA3D3580AAAEULL, 0xB3CC46D756BF0DAFULL, 
            0x758BF78AEE684F6DULL, 0x05666C0350D2C4F5ULL, 0xB7208A5834188D72ULL, 0xE5F311688D10075EULL, 
            0x44AB1AC08E62CF51ULL, 0xB7B911C003EAFC47ULL, 0x7E5B750CD92268FBULL, 0xDD5B4D1C4330E650ULL, 
            0x392D8509CEF05A8CULL, 0x176F01FFF5649B37ULL, 0x4D4A2946EED36457ULL, 0x4A135A86647AFDF5ULL, 
            0xA1B6DD764615EB60ULL, 0x8FB3E30081C25CB6ULL, 0x79B91862E65E6D78ULL, 0xB6AAE4B05B4362A6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseAConstants = {
    0xBDFFCB4F5867B3B6ULL,
    0x7318FFB3E15F7FD6ULL,
    0x6F1A0AB14B7BBBDAULL,
    0xBDFFCB4F5867B3B6ULL,
    0x7318FFB3E15F7FD6ULL,
    0x6F1A0AB14B7BBBDAULL,
    0x8771AB6FA43B0010ULL,
    0xA7C10DB51492FD24ULL,
    0x69,
    0x21,
    0x75,
    0x92,
    0x90,
    0x72,
    0x0E,
    0xE1
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseBSalts = {
    {
        {
            0x06DB41D1F4FCE5BFULL, 0x7B906253C1D18E10ULL, 0x04D18AF9566F4118ULL, 0xDCF2EF40C9386377ULL, 
            0x533B8CEB886E64D0ULL, 0x42B57A722AD9915AULL, 0x2201DEA1D8D4392EULL, 0x80CDED3E5635D621ULL, 
            0x5F803F9D70C4E3BFULL, 0x5A4C2C0D6DD9F4D8ULL, 0x3D74430EB8C17DF9ULL, 0xC2B2B0365190D201ULL, 
            0xAF3822BF27033609ULL, 0x1EEC45D77CE17DF6ULL, 0x583553BF53B0A95FULL, 0xC17EDA6893E93D18ULL, 
            0x6A82DBC9C311996EULL, 0x7687A17397D70B64ULL, 0x2786C7228A759F77ULL, 0xDA952D90A717A004ULL, 
            0x4EDDDC6FC8014F5CULL, 0x0A55C154BCB09779ULL, 0x5F81F0D94804FDC9ULL, 0xB28AADD67C8F259AULL, 
            0xEC77635E997F7FBBULL, 0xE240A57856FFFAD1ULL, 0x0AFD2FF84F9BD53BULL, 0x8A23787A979367A1ULL, 
            0x4DC9CFE872679BF1ULL, 0xBE7E16925FFAA36AULL, 0x4E046626E93C71CDULL, 0x291E79B1D1BA4173ULL
        },
        {
            0x702AEF68AE7B4010ULL, 0xF55C7B80D29633E3ULL, 0x2FF6FD2B292E3C71ULL, 0x431C7681767F3D2AULL, 
            0x988411C5C278E7F7ULL, 0x6F39D46E67B0C5F2ULL, 0xD724D3AED7A0AA98ULL, 0x84040AF1B584CB8AULL, 
            0x5E8893B50AFF8347ULL, 0x18FF5AB62806F77FULL, 0x92BB10B4A45868BFULL, 0x46A0D8C6DFD39D39ULL, 
            0x3DA86AB7B283FC81ULL, 0x351CCAD67B259EEEULL, 0xED36211C741597D5ULL, 0xE1D98778F2AFF3A6ULL, 
            0x813C9FD49CC2EC02ULL, 0x3998DCC828DBE6FAULL, 0xEAED70BFD62A67E4ULL, 0x3EE6753954DBF61EULL, 
            0x63886BF7A35F26CCULL, 0xB2BBA04A0B390DE7ULL, 0x77D3556FE55C5F11ULL, 0x25DAB2FA29737E11ULL, 
            0xEE2E7CF852DE67DDULL, 0x1674E272EAE9353AULL, 0x680B2D167B097155ULL, 0x37ED73DB3DC37D2BULL, 
            0x7EF587A0AB6C5113ULL, 0x2FCDC5E6B8C4A906ULL, 0x0940D017037DE109ULL, 0x0782B75AFE5A6BDFULL
        },
        {
            0xAF92F7FAAC3B9C4EULL, 0x0D541B1FE1677C8DULL, 0xFAA1FE62660C1E0BULL, 0xA66C12093C088B4EULL, 
            0x032BCD927E921821ULL, 0x169E6BA5C067F1FDULL, 0xE0FE0E43EC46420AULL, 0x2A2F63144EF9AC34ULL, 
            0x8B1DB7FC9EEACBE0ULL, 0xFF97FA00A5C79E0CULL, 0x709BC9F8037A666CULL, 0x78B8EFF31C970C49ULL, 
            0x0375B0C7386EAFE4ULL, 0x6C76E78FA86F4655ULL, 0xC02B481A481CDF27ULL, 0x57113F202CE3C571ULL, 
            0xCA1C88222D5D79B6ULL, 0x8059768AE1EC0693ULL, 0x66D9641A97D3DA5BULL, 0x368092A175EAAF08ULL, 
            0xCEB44DDA1B501473ULL, 0x3F439DB6FE19D275ULL, 0x4F17440A06B13C72ULL, 0xE4168AD92687CC6DULL, 
            0xD0453DD15A339AC7ULL, 0x07B6551673F1BB08ULL, 0x73969EE279D9B233ULL, 0xA1362BABFE455B08ULL, 
            0x9A383A9316A3BE6BULL, 0x8075206EFE3949FFULL, 0x53F95BC051271000ULL, 0x63B7D34421D252A1ULL
        },
        {
            0xD9659322B058537FULL, 0xC6DC67B78DBF371CULL, 0x7F93CE1D7742BFECULL, 0x0A2DBF5099AFA264ULL, 
            0xC859CE98BDE69B26ULL, 0xA97817056171C0E8ULL, 0xC2AEB7C68978FF5CULL, 0xC32F61935D558681ULL, 
            0xF4579056E2F6D4F0ULL, 0xA1EF7B86850B4F87ULL, 0x09D41E0F81EFC574ULL, 0x22E971E603FF0174ULL, 
            0x256B799119B3276CULL, 0x31BA5804159E80B8ULL, 0x73B8134BB92D4CB6ULL, 0x5B3A910C2057C3DFULL, 
            0xCEFB7CDD90D26991ULL, 0xD354CE7CC8923504ULL, 0x23D19B11E7C19859ULL, 0x1D71A4BED5F0263BULL, 
            0x178B35BC7BA951B2ULL, 0xE3BCAAE22E6ACAC8ULL, 0xD840549DFFACE6C6ULL, 0x5782A3FB9129A63FULL, 
            0x4D98EC437407FFF0ULL, 0xA19F5188131FEB0AULL, 0x849A0DBAA20B2A20ULL, 0x18D546094FAE9C8BULL, 
            0x05C5EB8E1EAEDC6CULL, 0xBCB496B847684817ULL, 0xB0F770580A266174ULL, 0xC02C61A8F55BBAD3ULL
        },
        {
            0x265ACC2260533F74ULL, 0x1AFFA885133D2D7FULL, 0x8F5DCCA62B94E5E7ULL, 0x43B379F8B8355D13ULL, 
            0x04648D964C31F5E9ULL, 0xA335F8BA5DF12EFDULL, 0xD1CEB7A0C5B7CAB8ULL, 0x4F35B15241CA7695ULL, 
            0x9784BA4186265463ULL, 0x6CE3556EEB0348EEULL, 0xD1E629528E7B14B9ULL, 0x0F16C891BB2C4CBAULL, 
            0xA7743F8C1EC027E0ULL, 0x64AE86F3D0A0A9D9ULL, 0xD9A0567A1E25EFB9ULL, 0x19ECEE88A244263AULL, 
            0x88A8D467D9B66EAAULL, 0x8F5D4A65100BCC50ULL, 0x1D899D6789923F85ULL, 0xDA37F1729D280F3CULL, 
            0x627F78C6821E4E78ULL, 0x69B0AD890D37FED7ULL, 0x6B333ADE43218717ULL, 0xC0AED9C3A990B3EEULL, 
            0xC69713AC8DB6B098ULL, 0x01F8DE4D3AD41D4AULL, 0xA6E081382A315C5DULL, 0xE0325BE4E1F119FBULL, 
            0x0D2A5A17ADB7CF90ULL, 0xB3152EB1E9FEB3CAULL, 0x1D93D6E97A042303ULL, 0x7C67E641FA55EC4CULL
        },
        {
            0x31876A5C9952E438ULL, 0x617D5772EF7204EDULL, 0xB0CDE4D7F939FF73ULL, 0x522F615F3B48739CULL, 
            0x0AAC48A54085CC26ULL, 0x4138BEBD479D87BDULL, 0x6C7A45263C2531A6ULL, 0x10A64A3D08AE34BCULL, 
            0xAB9391C5673132B6ULL, 0xABE2D9D37A4AF2A4ULL, 0x527E39F20DFDE78BULL, 0x27C0D2154EA463A9ULL, 
            0xE77B17E35FEBEEBCULL, 0xD96C6B2C993E46AFULL, 0x7D32C76BBE036745ULL, 0xE58659D14048810CULL, 
            0x8A540D622540B93CULL, 0xFBC1D77D27A670A5ULL, 0xA421B4D7AFD19A6BULL, 0x3403D5A307AE8933ULL, 
            0x0E77933835E9B44CULL, 0x0E5A2B379E2AFCB2ULL, 0x0D54700F7BDBF747ULL, 0xE4E58FA161271CB0ULL, 
            0x4E40BB76C8CDB6FDULL, 0x6383B2E292344E21ULL, 0x03CBBC8E00974E53ULL, 0x5D2B073870DD70D7ULL, 
            0x81025D57BEF57CD2ULL, 0xF06B7D2D219E90B7ULL, 0x99A3C9B1BE5A2CE0ULL, 0xC2960D56DA94421BULL
        }
    },
    {
        {
            0x9984D73D746C15D3ULL, 0xC94833472E29A0D5ULL, 0x0FA65D379053618CULL, 0xB68E62F6F4A9171CULL, 
            0x82A22130C96F011FULL, 0x7065EDB5D89AC7FBULL, 0xBFD977AEB31C51B7ULL, 0xA8117B6BB1D852A2ULL, 
            0xD61C3287A3F61BEAULL, 0x1B723BF83D19B8E6ULL, 0x1AAA7596F316A515ULL, 0x56078C8CC121CFC9ULL, 
            0x7FB60A6729139F80ULL, 0x5E6B4653A5A7CBC7ULL, 0x7B83F49E8A2D7991ULL, 0x2E999BE294045A40ULL, 
            0xF20EA24C56F327F5ULL, 0xC6B8EFDC19B153E8ULL, 0xAE678DFD8F33CBD4ULL, 0x181E67D4A598BF83ULL, 
            0xB0433CC72BA5BC72ULL, 0xEA8E7CEC20AC5A67ULL, 0xAA17E0AC177DB761ULL, 0xEE8D25057E2311A1ULL, 
            0x600F46146DF356D1ULL, 0x21A1869BE0B43452ULL, 0x5889E4B2BE869BCAULL, 0xF3887C2EAF0550E3ULL, 
            0x63E91CC659CA7B3CULL, 0xAB91D55DCECD2CD6ULL, 0xDFE3A8067B104E1EULL, 0x1E721A2E99B68F26ULL
        },
        {
            0x1D28FA4A7DC9D599ULL, 0x1F56CF90CA96EAFEULL, 0x0CA3D6754644244BULL, 0x3F7990F9759CF425ULL, 
            0x3F73E50591E2BAADULL, 0x0DA001FBB840B99EULL, 0x91233F0A2997E8CAULL, 0x6A220EA1B071DE2AULL, 
            0x584C799FE6F7CD76ULL, 0xE3563E9C63646E09ULL, 0x53B7757C76B80294ULL, 0x27856E7AD60DA8FAULL, 
            0x7960A11DBBA4D30FULL, 0x86608651A4708B19ULL, 0x0F6B04FFE3239201ULL, 0xCF051A40A3A4E6A3ULL, 
            0x659F27904F9AE813ULL, 0x720C9FAB628F2BF0ULL, 0x1EAE8507F9E3ABA5ULL, 0xC5A325AB956034C4ULL, 
            0x964C59BA72C70A52ULL, 0x8A9CDD98F1B3E8A8ULL, 0x7D550E6B18E3ADAEULL, 0xCB056CFFC2C69B97ULL, 
            0x5A8F361EB5A18E4EULL, 0x9BCED3EB76ED3D4AULL, 0x29B9F6C5C78FFAC2ULL, 0x566771F1F50ECC77ULL, 
            0xCAD81175227EE21BULL, 0x94FB5FBE209B56E5ULL, 0x575593361C0C5243ULL, 0xFFFE5EF16468C32DULL
        },
        {
            0x4D393184DCE096CDULL, 0xC998677841FF2ECCULL, 0xF96E3285F03909FAULL, 0x780BCF18A751691DULL, 
            0xCC3293AC9DC17FD7ULL, 0xC7552E40202E7283ULL, 0x971B737AADC667EEULL, 0x55D3CDAC4D9839F4ULL, 
            0xF667BBA32EC64598ULL, 0xFDD63D75A91D5967ULL, 0xED52193CB449C620ULL, 0x152E480DAC09FFE5ULL, 
            0x963EA058C6F72B00ULL, 0x535B2196C29A89C8ULL, 0x28C09C0AE9B4FA61ULL, 0x62773240E0BDF23FULL, 
            0xDD0EF45E183669BCULL, 0xFAF23D4C669920B1ULL, 0xD92801FFE8A7B09EULL, 0x09439176B9DC9847ULL, 
            0x2298A797FE33B211ULL, 0xBA640FECFAFB0E48ULL, 0xA7BB50FD39AD3195ULL, 0x94AF0B21C320B961ULL, 
            0x82E4F51DAC90CEFCULL, 0x1C6A11AC84637012ULL, 0xE3830B39F5AC5AC6ULL, 0xA4D865F1A1D76373ULL, 
            0xE63533CE79649108ULL, 0x9AED20FCB5CB781FULL, 0x2EC9537096541552ULL, 0x0295AB723B44E6A5ULL
        },
        {
            0xDBEF40CC56041E44ULL, 0xDD77A2703F7C0BC0ULL, 0x0D6E4E998498B186ULL, 0x37D761B967D5A2E4ULL, 
            0x05B6DAAC7DC8DAD0ULL, 0x78D767D1AF9CC973ULL, 0x7CD2997A9FD777ADULL, 0x90006307828C4BEDULL, 
            0xB674432CEBBB9060ULL, 0x63B3377A698340CBULL, 0xDBCE3172A232E544ULL, 0x923CFB882916B697ULL, 
            0xB55CFEDCFD7DBFFEULL, 0xEED1C2697DB80667ULL, 0xE42EC20A5AB93D3DULL, 0x85A946FDA169706AULL, 
            0x38935D7EBAE0632BULL, 0x4F19D9A924153AA0ULL, 0x9462137C0E411D7BULL, 0x37FA142C446FFBE1ULL, 
            0xB213374A7F3C6545ULL, 0x32BBD7DDFD43603EULL, 0x2BEC2369D10DEF32ULL, 0x434551342B4FEA1CULL, 
            0x0D57B1C37DF1A28DULL, 0x0BABC770E021C91EULL, 0xF93191FCE307B155ULL, 0xE9EE90DB70EC1F72ULL, 
            0xCE5DC10D01448EFCULL, 0x5CAB557A39B8F594ULL, 0xDB50D936E31D4AD3ULL, 0x8280B0E11C4B72A0ULL
        },
        {
            0xEE4A5F4C8B311A74ULL, 0x652C126D3CA4403DULL, 0x5608990033E74F0CULL, 0x07A31D15F4F33FA6ULL, 
            0x2BE4335F9B26BB1CULL, 0x9B8BD38963A2EED4ULL, 0x0563C1B549245E4CULL, 0xF6E02042305D3421ULL, 
            0xEEA643791B524990ULL, 0x913F4EE4CBC382F2ULL, 0xF564FC218843AE32ULL, 0x3F38A21EEC1CC810ULL, 
            0x6754222361B40D18ULL, 0x1EADE886C8E9E0E4ULL, 0xCB4940E5ABD6A6A5ULL, 0xB71EDDEECACFF9DDULL, 
            0x2EBBE3F12C51A207ULL, 0x6BA60F3B263849DCULL, 0xF134DB5B91AA7C13ULL, 0x48DE91C4F0F8BAC3ULL, 
            0x719435BDC6AB802CULL, 0x485AD7D45F3BBD44ULL, 0xDA1AEFC50B613520ULL, 0xF32FE75E91C6FC49ULL, 
            0xB3EC396C59A44D41ULL, 0xEBA8433D7196C436ULL, 0x492211BCA30FCBE8ULL, 0xF47AEBC6BD84B57CULL, 
            0x563CC4E47EF651F2ULL, 0xB32F1E74202B5707ULL, 0xAC6598C6FA91654DULL, 0xDC615198C5021358ULL
        },
        {
            0xB99A594C07EA9308ULL, 0xB8F38BA02043FDA3ULL, 0xD9AA3C17A6255B58ULL, 0x3B409F479AA88539ULL, 
            0x61AFDC5B1BE3960FULL, 0x32A249C209EF6376ULL, 0x1D4C987992D9329FULL, 0x83DA4EBAB9212F4FULL, 
            0x5D5FC592B9A60421ULL, 0x1A20B7E89F2E1960ULL, 0x4F1C8EC74C1E947FULL, 0x4DF605E145D83ACEULL, 
            0xEA59FCB0FF5B31F6ULL, 0xC793A03AD6A996D5ULL, 0xCE688FA7BB03821AULL, 0xA0D39C4E71E4A225ULL, 
            0x953DC700732236C7ULL, 0xC3F2154265A6745AULL, 0x3E4D03DB72368EBFULL, 0xEDEF67EAA852038EULL, 
            0xCD0C34C52818A29AULL, 0x9FCD4B4A50D31AE5ULL, 0x584F0390C02384C4ULL, 0xCBFD35E2E375A357ULL, 
            0xF4543DCAE81FB220ULL, 0x7124007C582718DAULL, 0x322200172C48F046ULL, 0xAA458588B67AA65EULL, 
            0xBFE98D9CA16540B1ULL, 0x4002DB3DEEE924C1ULL, 0xDE3C83D2CA1CE065ULL, 0xD3F3B1D0944C4952ULL
        }
    },
    {
        {
            0xFE80A1C49FF8BEA4ULL, 0xFAAD2D75AD2DCCB6ULL, 0xB59B5989B6BA7CB1ULL, 0x8DEEC3CBBAD49446ULL, 
            0x4F4EE8EED87E390CULL, 0xFE80A51F43EA064FULL, 0x10CBCF7C2F7CA751ULL, 0x4A2A8CA1C8D1F2F0ULL, 
            0xEDA1CC9A8D3A4ABDULL, 0x4FD59271EC4A8C44ULL, 0xE133084C3E50A343ULL, 0x3412EB71101877FBULL, 
            0x00F9917F6430C5B6ULL, 0x5DDCA85AC2AE05C4ULL, 0x9CA045F523AD8C18ULL, 0x0AE7AB03E37B378EULL, 
            0x63848DF3CA3FC29DULL, 0xCBA74D16A9640639ULL, 0xB1C9D67082A5C21CULL, 0xA078E7F3FE077FE5ULL, 
            0x1080282491069B5CULL, 0x13A503F4423A82D8ULL, 0xE2481A9A5107E0F1ULL, 0x4E37B8A195145DFDULL, 
            0xAEC3C108DDEC14BAULL, 0x753AEA9DAD20870EULL, 0x58ED70191F01AA83ULL, 0xA79FF9F92A0B1EC1ULL, 
            0x8F2B603E3BAF3A08ULL, 0x9D49BD99E8ACDCE5ULL, 0xBD274563E9297E1FULL, 0xBFC701C74B75B4B6ULL
        },
        {
            0x4D70DFAE2699D6FAULL, 0x9161C90A6BB9B8A8ULL, 0x6F832346B10839A2ULL, 0x644187A3A3A0DC6CULL, 
            0x94F535555A16F968ULL, 0xEF72CAB0FC05BC1FULL, 0xE1C57596F5A2288FULL, 0x3BC818F5C69A8BFAULL, 
            0xF594D956487CA287ULL, 0x0D0DEE39FFC5BFE1ULL, 0xDDAAF4B50449C0E8ULL, 0x4D456035143E4F24ULL, 
            0xE917CA430C6A7E8CULL, 0x9DDD9DD442521856ULL, 0xF7C4833857B8E28CULL, 0xA3DF3DC13FEBD254ULL, 
            0xEC4801A9252CD8EDULL, 0xE0951D0E2AF2472BULL, 0x6CE806F7B565A695ULL, 0x4498BFFD9CED16B3ULL, 
            0x3C27D41C20AC4636ULL, 0x38DB027AFBED9511ULL, 0x9D2C0278F9303396ULL, 0x228509A3EAF5B04EULL, 
            0x1B299A4DF79CBDD7ULL, 0x3C0C160FBF44E437ULL, 0x89BF52F390502443ULL, 0xD7395EEF95F5D3CCULL, 
            0x6C1F79BAA53EE45DULL, 0x83B00CED3E007948ULL, 0x9BD285D8C550A0BBULL, 0xE2965DE20454DE22ULL
        },
        {
            0x1B3057EE3B35F6FAULL, 0x38A22F0E4D3ABBECULL, 0x22A4857BE04385DDULL, 0xA14D3B51D3D3A10FULL, 
            0x3C06A895D65D7653ULL, 0x64AAAAF2DD956238ULL, 0x30D95A684D43869FULL, 0x2C4F6DF8126C723FULL, 
            0x43A98BC43BAEF41EULL, 0x3D2D886934D8DFCDULL, 0xF458DD83C0165BD0ULL, 0xE3F0C36887F0754AULL, 
            0xC748749F3DD5493CULL, 0xD28B31BBC2ABE7F9ULL, 0x5770A21FA59BEB41ULL, 0xBE011BFC62FF7ADEULL, 
            0xD49A9C5CB82C280AULL, 0x3C98072D674F98FCULL, 0x0061CEAF5F94EA0FULL, 0x6835440B3B9983F2ULL, 
            0x1A88C6D5BBEA7C69ULL, 0x7D5CDEF7BF7C89FEULL, 0xF5B632E147979A13ULL, 0x81EB97DF8B07B42EULL, 
            0xC1A9DF150678C5C5ULL, 0xDF8A4A8DA43BBB9DULL, 0x3B90EAE765FDB47FULL, 0x377AA3A501490F1CULL, 
            0xF0864AA31868B855ULL, 0x20EA86AF455381E6ULL, 0x9ACEE87707AF9E09ULL, 0x0F37C97FA03738B8ULL
        },
        {
            0x8731E3BFBE5EEF65ULL, 0x5E910584B95A38D0ULL, 0xEC981A98CA30C46AULL, 0xFFB36C7D978A6FEFULL, 
            0x912FA39A72EF5E3CULL, 0x3F1F6FBA0A45D1E6ULL, 0x94EEBDC2558C5467ULL, 0xB472CB5CD3A7B61BULL, 
            0x8D3DF93F61F75523ULL, 0x6CFEBCCF556718AAULL, 0xE79F4085D1CBE23FULL, 0x8336FEE1502F0BD0ULL, 
            0x36BF836098983D4CULL, 0x6E01E8F3028C9DA1ULL, 0xE4DBDFDE548086B2ULL, 0xCDFE9AF38ABD6C29ULL, 
            0xBB40693CCCA2C462ULL, 0xEB18475D5EC32D73ULL, 0xA48AC7E44D1221E7ULL, 0x92ADD3B5BFD85CEFULL, 
            0xF62731D746FB308FULL, 0x0D04AA0B173852EFULL, 0x88D244D6186C50B3ULL, 0xB26427AB7063CCE6ULL, 
            0xCD569EE6245A46A3ULL, 0x37574F384BB44C75ULL, 0xB89C2C846437D7AAULL, 0x49255BB80A6CD928ULL, 
            0x0BD999650C92F946ULL, 0x98E6F3053A3D3BDAULL, 0x86A22F9EB443940FULL, 0xF37140743F05F740ULL
        },
        {
            0x3E688C43334E6535ULL, 0x011A1E8205A0BC48ULL, 0xE041EED4FE4E7C1EULL, 0xA4C08BC20D164A5BULL, 
            0x70386879F7875D21ULL, 0xA3924B46FCFF864DULL, 0x01177DF865149460ULL, 0x3ED5E1DB357F0409ULL, 
            0x1F8CE35E1164E680ULL, 0xD2FCB4E04A41D505ULL, 0x485C32ED2C9F196FULL, 0xBF4F9223BB2423D1ULL, 
            0x2AC6D66868521D23ULL, 0x7898B5663283123FULL, 0xFD602F3728D497F0ULL, 0x9F6C5F62AD6E3AB3ULL, 
            0x3650088E3BA6835EULL, 0x16D63CB463D5E4A8ULL, 0x80009C13E117BDBBULL, 0x4D7E2DA604F23B37ULL, 
            0x2D21E58545D3FC40ULL, 0xC280182A633C5BFDULL, 0x37E6895E87C18FD8ULL, 0x79449C8EF84D8017ULL, 
            0xCB06341AE0A60B57ULL, 0x838849E711C03958ULL, 0x0A17C9CD35C3DB57ULL, 0xE86624821076987AULL, 
            0x6948EF9D64764D75ULL, 0xAAEB57970A8E8D42ULL, 0x4BD8983CCBA97796ULL, 0x49E56C470427C07DULL
        },
        {
            0x964AA407F4D6B71EULL, 0x3E74C0BCB5D1C050ULL, 0x48A07B97466B303FULL, 0xC1B6DE1C19CA49B6ULL, 
            0x89FB47798AD01737ULL, 0x3BCC549C3FE98A2CULL, 0xBF7347EBA09D5930ULL, 0xEF6F26C46D36CF0CULL, 
            0xA55CA5D9A25D8B68ULL, 0xA8FEDD4B923C50FBULL, 0xED45901F4000CB58ULL, 0x7CD317F0873B6064ULL, 
            0x1C0A2AA2FCE87493ULL, 0xE663CB7449FA9466ULL, 0xC5CB58DBA7F15C81ULL, 0x747BDF69E91CEDF8ULL, 
            0xBF28999CC5939D2EULL, 0xEE7546A1276135CEULL, 0x19FE224A66E3A31AULL, 0x72BCA85AB423749EULL, 
            0xC14F7B175D011C3AULL, 0x1742BFFDAC334B34ULL, 0x3D9A9A5261FA67DAULL, 0x837BF0A8C3E8BF98ULL, 
            0x7940DC1639B9F33EULL, 0x361C8B4B2CFC19B9ULL, 0x6D4BB33F22E0D226ULL, 0x39B36D18689B2DCCULL, 
            0xB3EDEC2BD4CF4330ULL, 0x8892C39981F9DF31ULL, 0x9E17616977F3419EULL, 0xC7B726070CE18D0CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseBConstants = {
    0x7F69E941BE19B3F4ULL,
    0xE907D5E395AEDD51ULL,
    0x18F2F1EEC08EB8DFULL,
    0x7F69E941BE19B3F4ULL,
    0xE907D5E395AEDD51ULL,
    0x18F2F1EEC08EB8DFULL,
    0x6DAA8B5A3FE1227CULL,
    0x1464F3B517D18051ULL,
    0xCD,
    0x37,
    0xE7,
    0xD3,
    0x5C,
    0xDF,
    0x5F,
    0x4E
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseCSalts = {
    {
        {
            0xC12246510C0A72FCULL, 0xB6CAE7E0095791F6ULL, 0x059F7F7B2776D591ULL, 0xDDFC3BDEBB202AB1ULL, 
            0x984A1AAAD51A0C2DULL, 0xAF0B57C280FDE9D0ULL, 0x59065F5CE017C1AEULL, 0x59B15C59F9A8B37EULL, 
            0x85E1BED3F07EBA74ULL, 0xFD308DF5C4C8ACC0ULL, 0xDF68C37AC3FA8F79ULL, 0xEBFA3A48D803F70DULL, 
            0x8A099C2D61DFF944ULL, 0x8B151A5CA137BA31ULL, 0x8CA0E509D30B781DULL, 0x7EC5B4BC96B39B4EULL, 
            0x705659FF8A9D7686ULL, 0xECF8797B8B256947ULL, 0x240A49EA1EEDD31DULL, 0xE9B5FE3C2B7D6BEFULL, 
            0x22800EFA498ECB2DULL, 0x1DBB56B65E40E7EFULL, 0x47634A7287E81F1AULL, 0x06519CF5B60E3325ULL, 
            0xA0AB9F6D439EFB9BULL, 0xD30AB0493987C1B2ULL, 0x317C3E0C3AC6034AULL, 0x271313F92035B1D9ULL, 
            0xCA609F91CAE05373ULL, 0x6D0D43A366DDEFC1ULL, 0xBB6AA4F3CE220FDEULL, 0xDB8B149407940A66ULL
        },
        {
            0xCF1EF72B7D8C3B95ULL, 0x59A5671D6A6B80CDULL, 0xD30A16517A61CE4DULL, 0x99813D18F6A4A87BULL, 
            0xD6EE0FF16FEFE2BCULL, 0x3DD2F0DDF0CFF382ULL, 0x17259998C66C0F51ULL, 0xE1F17A70097AAC70ULL, 
            0x917F2E675F48410CULL, 0x9938D418F79B229CULL, 0x2FB14E80B1F1FB4DULL, 0x8B9DBC1BC7D1EBC1ULL, 
            0x8A2E9F0FC7EBB06BULL, 0xDDE299E94629473EULL, 0xB7ADF02418D6BBB1ULL, 0x03384E3F83D7B766ULL, 
            0x571645D8A5AFEFA6ULL, 0x72A9B79B86EEAD5EULL, 0x3A5FF676A85E3F08ULL, 0x4D700D79AA67EEEAULL, 
            0xCB6C9C4B6E927088ULL, 0xA382F985F4237873ULL, 0x28DF8193F2F5D472ULL, 0x12603F8A4314D195ULL, 
            0xA98FFE9474654DB0ULL, 0xF27694724D0AB470ULL, 0x7CC44FB2D849ED98ULL, 0x32AEF51D0717B6F3ULL, 
            0xC37F68747942F408ULL, 0x3A1566E747F4F118ULL, 0x3891F5BA70592A28ULL, 0x6F68418E65086127ULL
        },
        {
            0x739B9771FA748605ULL, 0xB4FDFDCA50D9FD62ULL, 0x71AB564A4AC1FFD4ULL, 0x8ADF3BBE727BC0C8ULL, 
            0x50DC5A7903DA6F78ULL, 0xF7A46465DE92629AULL, 0x14C43C22CE85D21BULL, 0x088425FE66C33422ULL, 
            0x8966BFAA34FAEF28ULL, 0x4F9824D4ED4EF754ULL, 0x950FD4120CEEF8F5ULL, 0x8764082EDF12C265ULL, 
            0x6427C9F506858B86ULL, 0xEB158A8DB2F887C2ULL, 0xF4CC9C8A5D23BE2BULL, 0x88DF0ABD6978FA37ULL, 
            0x28CBF399A3E4D0EFULL, 0x925ABA16E31BF089ULL, 0x61405ACF59A69710ULL, 0xAF106A443D5F1519ULL, 
            0x339493A179A41BD3ULL, 0x5F60939988791F19ULL, 0x14D7C90E5DC00772ULL, 0x68AB652780F8980FULL, 
            0x28476E1D1BFC7F86ULL, 0x2A87179A43BDB9F8ULL, 0xF5EEC1CF53AF3031ULL, 0xE672D91354578CCCULL, 
            0x151E760D44B08311ULL, 0x6B74B99CD7BBFD6EULL, 0x0F629FA150820948ULL, 0xCE1C6C17EACDF324ULL
        },
        {
            0x430835DB774DCBB0ULL, 0xBDA0A91C69CF68D5ULL, 0xACF5894D0A42925EULL, 0xB149A97C379AC156ULL, 
            0x11172295BCB5B7EEULL, 0x6D6F7C354D0C1A97ULL, 0x53C2245354F96F67ULL, 0xE5AC46593AE47672ULL, 
            0x790EB38A2FD00DAEULL, 0x0A178A480B1C899EULL, 0x43F469313971B8ACULL, 0xD1E5E6573A197D5FULL, 
            0x571964407C431E7CULL, 0xAD1634EFE46EAEC4ULL, 0x1AA3442BC2D8DFE8ULL, 0xAA701A187D0A7831ULL, 
            0x326970A1801C75F1ULL, 0xCF4238D1F0A687BFULL, 0x0A0A58768E5114D3ULL, 0x3D0ECDACC27A8A6AULL, 
            0x182A72AE58075E92ULL, 0xF81D5B4B5D73C022ULL, 0x323CEA496361C597ULL, 0x891E37726127C9DAULL, 
            0xF2FEB9DD0A708AADULL, 0x792BD23672FF1D7DULL, 0x001D44FE3E7FB8A6ULL, 0xF6333CC0B2403CD4ULL, 
            0x0367134DF38C0FE7ULL, 0x88D0D82F44B898A1ULL, 0x800E1F5FBC028067ULL, 0xB212FD1C10675747ULL
        },
        {
            0xF82586BAEAE3C971ULL, 0x726DCC3D394263D0ULL, 0x2D5179DD83B38F25ULL, 0x5770225E7D1E7854ULL, 
            0xD84BF3583992FEADULL, 0xA908F2A2A7B94917ULL, 0x5A6D47E06A414B3DULL, 0x16C551C3C6090E6FULL, 
            0x07EA8A77852DB6A5ULL, 0xC3AF6FE82CC9AD45ULL, 0x7EFC69A17661EF2CULL, 0x0702C113A5DE49B4ULL, 
            0x81F9404F19AC9173ULL, 0xB96F245347669525ULL, 0x9E728896E4616326ULL, 0xC979BC292DF5ECB5ULL, 
            0x6EB622FBB5586536ULL, 0x809DB8D5404CECECULL, 0x3B4F520E9EEA73CBULL, 0xFFA89BB7423950E7ULL, 
            0x6285806CF8154098ULL, 0x14112909E01FF3DBULL, 0x97133EC784DFBC1FULL, 0x0836A57678A217A6ULL, 
            0x0B6946CC949FC4B6ULL, 0xC8E18A09F1C3A738ULL, 0x2A03ED37F61C0BE5ULL, 0x2F7811848B6F840BULL, 
            0x18D8ACFB6D363EB4ULL, 0x87ABE4CBC60F0891ULL, 0x8A6853AFCC2E229BULL, 0x0F362CF857C8B86AULL
        },
        {
            0x16D23289720E30ACULL, 0xEC96D5EA353F75ECULL, 0xFBDB3432CE417C24ULL, 0xA206A5D699932F67ULL, 
            0xB369608FDFAAB2CFULL, 0xB1ECCD9565F4F5B2ULL, 0x800D8BE48395BC7AULL, 0xA287EED2B73E6E48ULL, 
            0x52BC3E42E414E889ULL, 0x7AE7E755BB328CDAULL, 0x82BF3906425F06EAULL, 0xA04E9E15BEE4D4ACULL, 
            0x5E1E8C099C157EDBULL, 0xD8D5575B3EB77D5FULL, 0x0C399DB43B6E5630ULL, 0x4D7482B73E38258FULL, 
            0xDE0877E837319833ULL, 0x89444D8E2BCED3C4ULL, 0x3DE365ABBF76695AULL, 0x4079E868BBDDAE98ULL, 
            0x0667641F07C71A94ULL, 0x11FD11E3595EAED7ULL, 0x3A9F9A6540D964F3ULL, 0x01AAD3F5B0E7E263ULL, 
            0x6953A334CA154821ULL, 0xED1805E1202A7BECULL, 0xE1D6AE34B5006C98ULL, 0x3DBD897D5CA97583ULL, 
            0xD8D96F8E59D88F26ULL, 0x87E7F9F837F2F6EBULL, 0xEBDED0E26365DFC2ULL, 0x000485120CF8CBA0ULL
        }
    },
    {
        {
            0xB95E18E6DF7F92AEULL, 0x981B909169EBFA38ULL, 0xD78150B55271073BULL, 0xF6AD9BFA6E26E258ULL, 
            0x896308FE3CD58D5DULL, 0x03F23607D87E1610ULL, 0x7FA6DD3BA472B215ULL, 0x1C76681F35F18806ULL, 
            0xD06C42B1A02BD5C6ULL, 0x3D8B9452C967F1AEULL, 0xC60CCE900015F9C6ULL, 0x5F65063F13A4AA6AULL, 
            0x23D9F75A6CCC6CD0ULL, 0x4B5881302104FB18ULL, 0x2F89BA2667D4E4BDULL, 0x58C2D1A7E3AFDA76ULL, 
            0x73F8250312B24F5EULL, 0x080426B326184C97ULL, 0xB16F2A9FA4D27BCDULL, 0x6542E47F06D21388ULL, 
            0x8284250DA366A025ULL, 0x457535702E7A96A5ULL, 0xC553DD04AB2E31DBULL, 0xD5B8B8B1CDBB2950ULL, 
            0x04B3532C37702C27ULL, 0x0579A547BC8F7A15ULL, 0x257135A0AD80C4F4ULL, 0xA6F34866AD699CE4ULL, 
            0xCDF582CAB719AF97ULL, 0xF975C6C29FF96A64ULL, 0x5E92662B91F320FEULL, 0x0E06BEFBACBF8E28ULL
        },
        {
            0x93801709E3B6A119ULL, 0xC705A4504F428C00ULL, 0x8D0A670365997D96ULL, 0x21E429874CA3E0BCULL, 
            0x6812813C9A943BF6ULL, 0xCAEC4D328A1D2F61ULL, 0x4A89CBA0ABF793D3ULL, 0xEDED52EDA6E497A4ULL, 
            0x43D27922DE9857E6ULL, 0x95530785468A02A5ULL, 0xB68875F65AD90F9CULL, 0x4F5D15B0A485F3CAULL, 
            0x02E51C64C802A0A2ULL, 0x4EF5FDCF70D9B764ULL, 0xDCDA76D9A6B217FFULL, 0xD425DFF2CF8244DBULL, 
            0x183D0DF8624A81D3ULL, 0xF4EF43DD565FC9FDULL, 0x5CF4DFC9D3239CF8ULL, 0x0E36D99FA5D07FF5ULL, 
            0x07EC17A52C9F8C8FULL, 0xB88526095497B755ULL, 0x09C4A42809F60D81ULL, 0xD4EB286A74415105ULL, 
            0x5602D75F89E081EAULL, 0x8A32E92D9FF68D5DULL, 0x7F5586912D060BAEULL, 0xE57CA8976A1CAAADULL, 
            0xA25F58FA4A174B94ULL, 0xFE88C7F11AC17225ULL, 0x09E8E13E843BE6AAULL, 0xDE791CD202C70497ULL
        },
        {
            0xB6E0055800B00EC2ULL, 0x5F760FCCC98A29DEULL, 0x8B72E40C37314D6DULL, 0xE852CAA95DDF33CCULL, 
            0xD23E638408ACAA67ULL, 0x007BA4CD3E024133ULL, 0x031B2CAD5ACC5869ULL, 0xEB1A89F5FACA761AULL, 
            0xCA1164A349032EF8ULL, 0xD1F3838A7AEF4AF3ULL, 0x8D53E97241543DA1ULL, 0x90F114B8D5029819ULL, 
            0x5174176448971526ULL, 0xAC9E228588BAF103ULL, 0x51C7C098F7CECC2DULL, 0x0873A8CC43A39F0EULL, 
            0x8ADF6724E0449C19ULL, 0xD5EA2AB64CEFE858ULL, 0x5AA3A5EF2E9500F8ULL, 0x9E5D72D12AE577FCULL, 
            0xA6CD85099FA19384ULL, 0xE40B3FAD2429D3B4ULL, 0xC3C91BC17AFE83A5ULL, 0x80D40A1C033FF5F9ULL, 
            0xD00E8AB3B2DCAB99ULL, 0xB081D272FF330523ULL, 0x8A5BD7E86FF537A2ULL, 0xC5EB6ED26BF57A46ULL, 
            0xC02F586C460233ECULL, 0x0839329A3DDA3864ULL, 0xB7102CF0FFD74C18ULL, 0x4281DB40DE252E74ULL
        },
        {
            0x2D182F6052C907B4ULL, 0xA3AC472BCF1B7A10ULL, 0xE3408936D5E1A208ULL, 0x989EAB9CF99C89B0ULL, 
            0xBD35E59D10D984AFULL, 0xD450A2C815A94A68ULL, 0x4579628E4AC1E9A1ULL, 0x0B840DEBA90E174FULL, 
            0xCBBB8E68A1B3BFDFULL, 0x13C2D327C580819EULL, 0xE2605F430459508BULL, 0xD8E4B2996009C3E0ULL, 
            0xCFD16422C7BE7D09ULL, 0xA5280E2DF348B95AULL, 0x169779E3D1CD3250ULL, 0x5D8C69F71C78AE03ULL, 
            0x5ECB2C3B6E20CE6BULL, 0x791CDF795B98BDC3ULL, 0xBC7AA6353006A920ULL, 0xA034DB315F7C00CCULL, 
            0xFA76396759EF6EC2ULL, 0x92D8F9AABB39990AULL, 0x98B18C8DC9A450AFULL, 0xD3F474BFD914F002ULL, 
            0xE7CEC90F799A0C78ULL, 0xFBF02151F284F7C3ULL, 0x8411BA5D81A4B620ULL, 0x42F7F081BE3322F8ULL, 
            0x42B5A42E3F453695ULL, 0xA2EE8634932159ABULL, 0x106E468AEBCD4FD6ULL, 0xAB4FBE087B849331ULL
        },
        {
            0x7A53A9D51A75D4A9ULL, 0xE908B0CE95A7C4EAULL, 0xCF0D34E6DE54142EULL, 0x2915F884AE383CC4ULL, 
            0xC9AF6107118E97D4ULL, 0x3B1AF066F02A19B8ULL, 0x0E44E01243DB8BE5ULL, 0xD91ED263B2136091ULL, 
            0x0BCBC93B1AAF1AA0ULL, 0xA51908C62C089860ULL, 0x087B733AF301A652ULL, 0x358EE6637AA57E81ULL, 
            0xDA844D02EC3FBCB7ULL, 0xB0CCCBEC5BCFC21CULL, 0x2B5A1A0B919C2B71ULL, 0x1EB2E1527759B2C6ULL, 
            0x601BD5C780D6EC31ULL, 0x8B02B748FF1AC82EULL, 0xFA91107E3E5946B5ULL, 0x3BCA0843A8B4E672ULL, 
            0xDF34725AF4BBE630ULL, 0x2C1AFD9B551D9561ULL, 0x0C517186ADAD133FULL, 0x23DB90373DF02A5EULL, 
            0xA00AC94CEC893479ULL, 0xD93D4C54A7ECAAFBULL, 0xA294A51F16AAAD22ULL, 0xE2FC71EFCADBEC09ULL, 
            0xA8D8769E53B26832ULL, 0xCB4B1EAFB1B40465ULL, 0x9CB4997F3B74C529ULL, 0x0D9900593CCE6250ULL
        },
        {
            0xC405BBBDB166D4FDULL, 0x9DF4ABE2020D34FCULL, 0x8F09597785A91A08ULL, 0x0DD4153402C20B61ULL, 
            0x1638414A9062DC29ULL, 0xE5D3C3284BD2C8E0ULL, 0x6D16904309295BC2ULL, 0x8D3922457770CBCFULL, 
            0x6BFAD5D9AD38030FULL, 0x6515603C7AEA2932ULL, 0x29FADE4358D413EAULL, 0xBF8AF178C908E119ULL, 
            0xF7EE1E64BE2916FCULL, 0xB867B6ADCBF28E13ULL, 0xEB2FCABA1A6204C1ULL, 0xBC948F31570A2011ULL, 
            0xEB0CF5C8831724D6ULL, 0x91F2DE85B1F697BFULL, 0x0987CBE9C401AE05ULL, 0x0AC8FE507D60755FULL, 
            0xAA6E8A4BB66791FDULL, 0x8CE842B711B24625ULL, 0x85B50BEB398A8E5FULL, 0x18C9F1800360409FULL, 
            0x0713A3114AB7B4A5ULL, 0xD3446355C10EA30FULL, 0xA9B383336ECFA76EULL, 0xCDB6F762B799C0DBULL, 
            0xBE506B7DE23D280AULL, 0x5E5D3E34CA4D0A04ULL, 0xFEE0F6054B298247ULL, 0x14657163935098FBULL
        }
    },
    {
        {
            0x99786A2DAAD34C95ULL, 0xBD4A13DD33545329ULL, 0x66127A4F7DBC53ADULL, 0x852603418C36B70EULL, 
            0x3F6916FE697C70C1ULL, 0x91368B8BDE6E847FULL, 0x179FC26FFF943DE0ULL, 0xC4205F4FCE250E19ULL, 
            0x5C237D027FA7D7F5ULL, 0xB48D9D7BE86020D2ULL, 0xE69ADD1562D1FCC0ULL, 0xA8B217BAB902B241ULL, 
            0x4F101716AD7F2C2AULL, 0x048FCE2682DBD0AFULL, 0x0FF6F5C1F7DC25D3ULL, 0x03654C5E3C6A78DBULL, 
            0xC3A0B10965943295ULL, 0xE7401297964CD738ULL, 0x303CEDDCDED12E7EULL, 0x54AC216D6E7D8A19ULL, 
            0xA58F702D44B4A352ULL, 0x03098C7D5DB7C3BFULL, 0x9D6657D4BBBE6DEBULL, 0x90807C71CB8E0202ULL, 
            0x44CB1F1EE4722E21ULL, 0x56440492170D0185ULL, 0x53339B953C607895ULL, 0x4332DE183579C3DFULL, 
            0x6BD66A2A742E60AAULL, 0x9835B5A093461EDDULL, 0xB07AAD825FE1A9B2ULL, 0xA401982CDA32D7B9ULL
        },
        {
            0xDC61F06F19F84B25ULL, 0xEC576738A8642F4FULL, 0x964DB3D0968DFA4BULL, 0xCB278DAC7D33AD4DULL, 
            0x713EE2CFEA553E49ULL, 0x1393F58B3D83C554ULL, 0xB8696516D65998DCULL, 0x093DA98A027C8698ULL, 
            0x3D1B23C9A9CBE216ULL, 0xE6FD99B03FAAEFEFULL, 0xBA702DEC692D4B29ULL, 0xD0097E597B08BE97ULL, 
            0xE4813A3AB17C7018ULL, 0xD56849EF9780482CULL, 0x1774C4583C707269ULL, 0x7B9B5F7FD590605BULL, 
            0x0980148D3559EC2BULL, 0x31BB598FF41EB187ULL, 0xDC0F3EB7FB333A76ULL, 0x423430A0C7E142C9ULL, 
            0x3A85909285AB8FF1ULL, 0x82B6C14E4285115CULL, 0x08291BCE46EAD34AULL, 0x0E8F16FA1C9327CEULL, 
            0xA491FE5C3BF41FD2ULL, 0x11EB8BD3D18FABFBULL, 0x152950C53BCCF9A8ULL, 0x30D6445017F4FCA1ULL, 
            0x31B81A8CDD35117AULL, 0x683A5F708B3C255EULL, 0x2DFED2EB1D4E6325ULL, 0xE9A94093A0FC0FFAULL
        },
        {
            0xA476BFE16036A767ULL, 0x071E013468AF49D1ULL, 0xF8E6039E77878928ULL, 0x0ABB29B1AF6290BCULL, 
            0xB9C2050ED6C25FE7ULL, 0x12FF8781BC25A842ULL, 0x546925DB4423AC8FULL, 0x4DD3DE45BEFCC00BULL, 
            0xF4FB9EF98152408FULL, 0xB9FDB431E5EBED56ULL, 0x59F7F371BB502F2AULL, 0xC5DD757A68341859ULL, 
            0x956527C7B95BC7D0ULL, 0x61BF62539376AE62ULL, 0xA75A2655CCEABFDEULL, 0x05324EE20EF15188ULL, 
            0x38FE846DDEEEB615ULL, 0x95799DAB210F92C2ULL, 0x2E39A61AD6310352ULL, 0x904E66CA0C6631E7ULL, 
            0x38B0B3F8DD1D84F9ULL, 0x650961A5281A0E99ULL, 0x802C856D5C4E96E5ULL, 0x63A61A566DD13B57ULL, 
            0x13A01E4717F52E8EULL, 0x9F683BB8641641AAULL, 0xD45F43D7E51234C5ULL, 0x454C502977921475ULL, 
            0x0F811A07C36375E6ULL, 0x2D48DDCDC301C8D9ULL, 0xCE876D07F03EB497ULL, 0x99C2BC3D5E66A752ULL
        },
        {
            0x8D1636FB12C872D9ULL, 0x0CE97792E14E7A20ULL, 0x3F2BEBE33F5CC9EEULL, 0xD3D5026FB0114A0AULL, 
            0xCA35418FFF6202CBULL, 0x26BA573499C0A57EULL, 0xAE09F66862E27C6FULL, 0xB992DCE7154E4C08ULL, 
            0xEB40CAF5096725A8ULL, 0x217822DACF172FB2ULL, 0xFC0C31F49B030270ULL, 0x7FBF2E6505394B9CULL, 
            0x47CC1679616BD127ULL, 0x47A84E659376AE27ULL, 0x048DE1E98DACAD12ULL, 0xBD7227FAFFC78694ULL, 
            0x3581064FB95E4EBFULL, 0x02CDF6019F16930EULL, 0xDAC030DDB983CADAULL, 0x12B6931FC31D272AULL, 
            0xFB08FF3DD0870373ULL, 0x1D9FD5367764DDEBULL, 0x25A9E9D9242725D6ULL, 0x89AC7FC428A2F884ULL, 
            0x375DF61D3F8E885AULL, 0x31105D40F495ECCBULL, 0x964829117DD1F79EULL, 0x1966C98E63EC1CF9ULL, 
            0x572A1B0FD191DF8AULL, 0x2B3025484F988D0EULL, 0x763D6F7E99C10FC7ULL, 0xD7ECDDF933C6881FULL
        },
        {
            0xFD222216B51B56ABULL, 0x75E6BC17A4C8399EULL, 0xC6168BC87F4CC1A9ULL, 0xF38A6A8E455D5F69ULL, 
            0x513EBDBC62EA9299ULL, 0xFAAEF5DDD3AB5FE4ULL, 0xF22FAE21D6A01FA5ULL, 0xB1F276A0C69B994BULL, 
            0x1B20E97FAF0888FFULL, 0x06FAB99D38B3E6C2ULL, 0xAAE256205E3B02F1ULL, 0xA64BC337B5981181ULL, 
            0x71917C595BB0FD83ULL, 0x98274F25F7D46C36ULL, 0x097130CA5C1E5698ULL, 0x36AF30588141205CULL, 
            0x6E2F62F0EA7B372AULL, 0xC15879C9062B1DDAULL, 0x6F92D922BAF8BC42ULL, 0xDF953AB21AE6CEA6ULL, 
            0x37191247882EDB48ULL, 0x40D76C7DDDDFB0FEULL, 0x0A99FA1E2F45C238ULL, 0x982A676C5D913F53ULL, 
            0x57B06CE2377F07BFULL, 0x9F53D572E42E74A2ULL, 0x627A4767B6D9A385ULL, 0x81B0D7A64CD4E7BFULL, 
            0x29856D0DA232C6FAULL, 0xFFE1DFD796641DEEULL, 0x22AE345F69FE1C57ULL, 0x511012C1FE8E11E1ULL
        },
        {
            0x320BE94F62070857ULL, 0x1D2C8D9FAA5AC5E4ULL, 0x9CD009D996E13882ULL, 0x9267682BDC38CB67ULL, 
            0xEFB87654A3EAD261ULL, 0x260EE740CE115D45ULL, 0x4FC9A23A63DB2588ULL, 0x690A18EDDB52EB4CULL, 
            0x78A68A698B1B9521ULL, 0x3758EA90F9084B99ULL, 0x7B5092E11FCA956CULL, 0x81D1AE705B75B344ULL, 
            0x7796E73A32B5B396ULL, 0x8FF6A6A41BB0C4C1ULL, 0x5B244D6F8521225CULL, 0x287F9C2C5649C9CCULL, 
            0xD7593B3AD50F5E4AULL, 0x0D5975D669FA8251ULL, 0x41AD5DAC2FE31E00ULL, 0x9BD57E5AB2FC4E9EULL, 
            0x43F739B1855EAB5BULL, 0x48410A81AEDD9AA1ULL, 0xF1ED6D2DFED0F841ULL, 0x820712C69B2EEA62ULL, 
            0x29CB8152330CA4CFULL, 0x2CF85DF442901F8DULL, 0xE17538367300313EULL, 0x6F75A74DA36061C4ULL, 
            0x5005F89153D7EA19ULL, 0x2A647AA7D62FC658ULL, 0xD49E8E08E959B9DDULL, 0xC4E600F6A955BD76ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseCConstants = {
    0x9038D24AB60DB390ULL,
    0xC8400A68AFB2B288ULL,
    0xB0B2826487BAD968ULL,
    0x9038D24AB60DB390ULL,
    0xC8400A68AFB2B288ULL,
    0xB0B2826487BAD968ULL,
    0x35C55AAEEA333ACEULL,
    0x4EFEC19CAB203026ULL,
    0x56,
    0xF8,
    0x88,
    0xF2,
    0x27,
    0x6B,
    0x02,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseDSalts = {
    {
        {
            0x7244E89A98F2F34AULL, 0xB5E79C29C016E3FAULL, 0x824CF6461686592EULL, 0xF9336D74B7727DADULL, 
            0xDF3BC8B52559A3E1ULL, 0x99CD7C8F03748634ULL, 0x758356ADE6BEE044ULL, 0x88474A039CF279B0ULL, 
            0x0BD5B67CAF7CC1F7ULL, 0x7B3DDBB285D101B2ULL, 0xEF67857AC745313BULL, 0xE904899AE5D21510ULL, 
            0x07348FAEFF3FB6EDULL, 0x6D52552897414D8AULL, 0x382A92DC7E4E706CULL, 0x2675563B521EA84CULL, 
            0x888E43ACF5EBC80BULL, 0x241936F82E90A5A0ULL, 0x3BE756D692662C6BULL, 0x8BB02CB0D1AEE375ULL, 
            0x092428C3383BEBABULL, 0xB7FE12AD025ECB85ULL, 0xFCEC137C1612A48AULL, 0x6E41E78AC462EAFEULL, 
            0xA867B1ACEF7AF607ULL, 0x8F6F2A5F6FAE29F3ULL, 0xE890AD65FF8E5460ULL, 0x52F29957277D37E7ULL, 
            0xB148F03C1F44923EULL, 0xEBA5698BAA422A00ULL, 0x0429CC98C3598D6EULL, 0x1F5E8F8F5BEFF92BULL
        },
        {
            0x8A272F3A63A4B307ULL, 0x5FED0ECF2E7793C9ULL, 0x8B7A6DE2022255CEULL, 0x999A10EA4A499825ULL, 
            0xD627E4331FD6D2FFULL, 0xAD878CD47BA54000ULL, 0x55A96FFC9040A30FULL, 0x963813A42EFA2539ULL, 
            0xEA0C38F1415C8CE5ULL, 0xB65B1ED3EE9CE6CDULL, 0x1E62ED04D9F356F4ULL, 0xB7D1560DE2B2A7ECULL, 
            0xC9D9B20CEF103A0FULL, 0xD23FAF7D9897A8ABULL, 0xB20786AD01600A50ULL, 0x95AB914A8F92B303ULL, 
            0x6233F466E47D5863ULL, 0xE34B6F74D93A9F13ULL, 0x5CE9502639BA090FULL, 0xB8C6FFD8D15B9E64ULL, 
            0xACA68E14E5C56E9DULL, 0x3FCBC43B53322160ULL, 0x4293C995FCDD7941ULL, 0x13E8B4E25E1E37B9ULL, 
            0xBFA6027634846633ULL, 0x597CF8F0FA3A8A49ULL, 0x8CE7E779ABEB88BDULL, 0xB6C7F674DB9F1B79ULL, 
            0x38EADACB3911E867ULL, 0xE9CC87DA2F2F248BULL, 0xFE5C71A9BA52CA0FULL, 0x90735249684B1DAFULL
        },
        {
            0xA905F74049B03B38ULL, 0x3C31AFDD279657F1ULL, 0xDD5663E1C3D3D0ECULL, 0x784A82A32F59D219ULL, 
            0x4CFABCB3D39FDC4EULL, 0x16E136D8A4B2DD1DULL, 0xBA896F27A5C1A406ULL, 0x506AFF8623543A5DULL, 
            0xFBA2B240C2BC3FCDULL, 0x568E123E9109325DULL, 0xE6FB48B4074D8E89ULL, 0xF9EE68AABEE114B3ULL, 
            0xC56B2CD6F924CE06ULL, 0xB53A8A30F20E1B2AULL, 0x8142C0730D7933AAULL, 0x3025E3D4D9AFF0C1ULL, 
            0xB04F24E948A0BE56ULL, 0x059C516D963A8252ULL, 0xF5467454175C3E01ULL, 0x2C637C35F7503546ULL, 
            0xDF6197F7485DF9CAULL, 0xBAF8F7A940A0E77BULL, 0x869193E055BE6A49ULL, 0xE2A277B13C861F7CULL, 
            0x71E91FF5CF2B9FA8ULL, 0x77F46CBEACA67031ULL, 0x7744C5077F4D8671ULL, 0x9B3BEFC10B9D22FCULL, 
            0xDEEE8CB48032A408ULL, 0x80934CDABEBCAD16ULL, 0x9D30948ABAD939BBULL, 0xAD3190A690A73E4EULL
        },
        {
            0xDEAF293E9F7D1A73ULL, 0x650432F2C70AC587ULL, 0xF6F8832611FB5553ULL, 0x5E59D21028FF4027ULL, 
            0x34FBBD4B2F957C26ULL, 0x33C9C55B836F067AULL, 0xB298E133AB451218ULL, 0x19592339C66D8B26ULL, 
            0x146ABC3F4E42EC7CULL, 0xF8E86D41CA4A72C4ULL, 0x00FE8EFAC84C0B57ULL, 0x80D9D41450847376ULL, 
            0x3337A42CB8FD2CE5ULL, 0x7E7265DDE6CF732CULL, 0x72703C6C8B760397ULL, 0xC6EBD66A0AC2AB71ULL, 
            0x26E494BBDD3B1442ULL, 0x1CF24E16762E3907ULL, 0xA803F8FB4A6B99A1ULL, 0x831FE6E933A95A5CULL, 
            0xBFD6FF41F177C1A2ULL, 0xCAC35B25AAFC2E5CULL, 0xD869698DD91AF90DULL, 0xFA2AB1B53FA1B689ULL, 
            0xC43730A2D6F93A27ULL, 0x61D13B42A07FC27EULL, 0x512A7EBFEC065D10ULL, 0x90420ED4D83EBF5CULL, 
            0x5EE4194BE286BD78ULL, 0x5A10F561036244C1ULL, 0x353DCC06E290800EULL, 0xF182FF5C539DB23FULL
        },
        {
            0x2891C98E17C447B9ULL, 0x6702E337D3008A18ULL, 0x7F6B2DF0051529BEULL, 0x60F9DF66F8D20BE8ULL, 
            0x6FB4F29F36BB0ED5ULL, 0xB467FF1AD062E83CULL, 0x27F452CF330F6902ULL, 0xAB45FE382AEF65A8ULL, 
            0xD7933BA664FDD41DULL, 0x69C97282EDD9FFF2ULL, 0x417FCE586C3CE294ULL, 0xF362D136A7F20A8AULL, 
            0x763F73473FFD01BCULL, 0xC8A7EEC49F02B77BULL, 0x1E90B10B31E4E81BULL, 0x339E958D17BC56FCULL, 
            0xC5A3948138460E7CULL, 0xFA97354DD5E925E7ULL, 0x5F3BA285BB4A4D8BULL, 0x458E2E33F4DE6D3AULL, 
            0x33065502300245BAULL, 0xC56A3E1F84DCFF63ULL, 0x269104A89F8D54A8ULL, 0xA12927B96C1CEFF9ULL, 
            0xC81B43E54C26A847ULL, 0x8F659B26B9570A36ULL, 0xA25DB39C3AB068CCULL, 0x21D51D7E7AE95AE6ULL, 
            0xA0A136B7D98442E0ULL, 0xB2CBDB2CA1F8F740ULL, 0x22AC3E7ECD9D6A42ULL, 0xCB530AD4F7522F7FULL
        },
        {
            0xF54486F8FAE0EC09ULL, 0x8B87127BA4D21DF2ULL, 0x2CDEFF242CD8F19CULL, 0xC0402F16533C461DULL, 
            0x056282F915BB4D14ULL, 0x5E354C0C8C234463ULL, 0x910635C27EB5F7CCULL, 0x69EAC9DE913FD2CCULL, 
            0xD734D13C9474BBD4ULL, 0x68CA9B393E1C0D68ULL, 0x40E43C968EE62116ULL, 0x5EE147D574518967ULL, 
            0x8B6F4F9E6B2C6C72ULL, 0x5B220BE118DE4C97ULL, 0x51D81117E1EA691BULL, 0x2BAB65A1554C5297ULL, 
            0x321602485E7E8D4DULL, 0x67C53F27A490B28EULL, 0x4350944BE7F50061ULL, 0xB6F884D056BEC2C2ULL, 
            0x60D0268B5079AE40ULL, 0x5C428CA03EC5D065ULL, 0x8E71DAD6D0379F25ULL, 0xDBC049E7F661A00EULL, 
            0xE5F07FAD4F88F4A1ULL, 0xE43E5741EC971559ULL, 0xBB46C17D0124B5E1ULL, 0xFF2555FEA29015F7ULL, 
            0xD8141552C55080CCULL, 0x2702B3863D50FB87ULL, 0xD5BEA9C0901840A3ULL, 0x870C4A68EE4810C4ULL
        }
    },
    {
        {
            0x8C656058BCD79C54ULL, 0x291DE7CFA6703171ULL, 0xE518EECB4521B512ULL, 0xC52D29A5DB7AB852ULL, 
            0xC454947C582468A2ULL, 0x44A82CB0A103ACD0ULL, 0xD393AA1349F0A1F5ULL, 0x20C80AFCDC205078ULL, 
            0x6488E66A299FE93BULL, 0xC1E2E89ADABCBD47ULL, 0x956C9EF2A612B70EULL, 0xEFFF929CF93038DCULL, 
            0xD358968A28CF36ECULL, 0xDF851082F967DCD4ULL, 0xC6C49BFAB849A24CULL, 0xFB70F3F68BAEF230ULL, 
            0xB82A090206D34CACULL, 0x74928066086BC4CEULL, 0x1D6E5D3427583B42ULL, 0xB2601AE429B34022ULL, 
            0x65CF0E76AAC269EFULL, 0x1F53479CC895B86EULL, 0xD7115B7D96BDC51AULL, 0x18BB8C5FFD46E303ULL, 
            0xDA64883C9895FCB6ULL, 0x624BD96F479AA3E4ULL, 0xA23B6963D37A7830ULL, 0x3B42B8FFD8F43111ULL, 
            0x3D11453DD45D37F4ULL, 0xCB3BD1D596E0391AULL, 0x5AC5163F1E94FFEBULL, 0x8D31A8D3DD6FAF8FULL
        },
        {
            0x3D4D0CB2C5C15B1BULL, 0xD8F4FCF42E1C392EULL, 0xE7633BA17DBA2D40ULL, 0xFDAEE05F1873C51CULL, 
            0xA6E9482319AFC362ULL, 0x0FBD34DD0BC33640ULL, 0xA767E5F2601AC232ULL, 0x3830DF1ED5712D68ULL, 
            0x798C2F7B43B58B79ULL, 0xE6C3F6C5493380DFULL, 0x0DEE540DFC0FF216ULL, 0x94668CF88450ACFEULL, 
            0xFA6E0FCDD3DC1EE6ULL, 0xC3A252E949BCBDBCULL, 0x128CE41CFADF9F57ULL, 0xC46987CE9E386484ULL, 
            0xD716CB5F3E05DE4BULL, 0x1AED26C7C1D15873ULL, 0x812D768F8FD37CC8ULL, 0xF650DB23255452ABULL, 
            0xAFC55AEF4D6C12D6ULL, 0x88DF4AA3E5E2CA8CULL, 0xE2D2CB308CC60405ULL, 0xA14976E2B908912CULL, 
            0x00F6CCAFCD4FA364ULL, 0xCFF61D0CFD23BD16ULL, 0x7CDA2CE1A53A7922ULL, 0x581F78B4F775632FULL, 
            0xD2C496E2CA0AA5F5ULL, 0x8DB7958BC8784A6DULL, 0x182BA96928368562ULL, 0x2F4D6984FD1AED0CULL
        },
        {
            0xCA79C0E4B1A6422BULL, 0x472F0A186E94A0C2ULL, 0x3C1662F4A6B84275ULL, 0x507C258357374C29ULL, 
            0x5FF2ADCE7EE46FCCULL, 0x5C99631E7F21E679ULL, 0x820C5111F736958FULL, 0xCD9E8D42D3770A1FULL, 
            0xFA9239A5D04CC27BULL, 0x8B808215EF634BD0ULL, 0x4CE045FF97AEF9DCULL, 0xB4645428E8E273C5ULL, 
            0xB5A9CCA03E8A2EF2ULL, 0x9AA267D0CBF3967AULL, 0x44E0AD551B46CAB4ULL, 0x11C16D49BA3005DAULL, 
            0x06A86A7B2EE2E0DAULL, 0x905A9A0C9ED75909ULL, 0xE79875FF419FBE4CULL, 0xB2723012F5B150EEULL, 
            0xDB3909DF56811E3AULL, 0xC4B6EE206841A369ULL, 0x6B8BDA321609E8F1ULL, 0x85EB19A17F68D979ULL, 
            0xE65AA98326CD4C40ULL, 0xA0988E0643F077E4ULL, 0x9EB54FC4C0DF8D54ULL, 0x7969BC9EBBD1C5E0ULL, 
            0x5A6023A5077491B2ULL, 0x840D5285C4C7616BULL, 0x44539578AF71F878ULL, 0x3AE251843CFA35C5ULL
        },
        {
            0xE57F161931C075C6ULL, 0xC34788C7BEDE3F53ULL, 0xE51ED22D1DE1ABF0ULL, 0x4FFEE8C2556FDDD5ULL, 
            0x581F7BB129532E5EULL, 0x86232ECC1F31821AULL, 0xF9E83E93DB1F76B3ULL, 0xDD5E711278AE5086ULL, 
            0x41335B021F8AD636ULL, 0x75470F4B18D29A98ULL, 0xFFE2736A45B5E225ULL, 0xA074BAC63CE21214ULL, 
            0x3529425922CC90EBULL, 0x77F9989981670F72ULL, 0x2CDAB6CFDC05DCB2ULL, 0xA64C658519013CB4ULL, 
            0x9DADA1EF10A98282ULL, 0xA5764B2059165010ULL, 0x0882D625A749CA0BULL, 0x1CF5583F1BDB7A02ULL, 
            0x2F334CC318ADC7B7ULL, 0xF4D11B363E75987EULL, 0x85C8D0E772ACECCEULL, 0x49FCD0B76F8374F3ULL, 
            0x62F2828E7B88B23CULL, 0x2CEAA1FC11F871A7ULL, 0xDDE3A65593FCA0F3ULL, 0xF252276E18988F9CULL, 
            0xB62C168E4C75BB48ULL, 0xE7C4DF5FAB50CEA1ULL, 0x8BF2411A84696CF5ULL, 0xD6028972D5917746ULL
        },
        {
            0xD8B654C8C2B86218ULL, 0x9EE637B5E807CB7DULL, 0x359F580A02805492ULL, 0xF1AB15D1DD649E7AULL, 
            0x2A58CF6D1AC6097BULL, 0x3C2858DF435D4A39ULL, 0x7F3987435DEA93D1ULL, 0xFB2CCF08C97F994CULL, 
            0x65B0EF97B8B64A3AULL, 0x0D4550230B986027ULL, 0x8D06529A29117C27ULL, 0x1B6F3680870A052DULL, 
            0x995B72D33A9B491AULL, 0xD53A1D596B198AFCULL, 0xC006C3931AAA7694ULL, 0xEC7BAF1F11AC4913ULL, 
            0x9217ED60338F3BC8ULL, 0x63B93203885989D9ULL, 0xCFABB5D71EEF05F1ULL, 0x31A4D535A1CF0C51ULL, 
            0x3666B115D9D12B3EULL, 0xA90C6E9FA880500BULL, 0x7FB092B4CAD65BAAULL, 0x72661879ACB1D7ACULL, 
            0xB7166EE52804C241ULL, 0x5687A8D2D1B08BEFULL, 0x272C6FB59564AF94ULL, 0x7381FBAA27C9E5F8ULL, 
            0x11B4707D785CC41EULL, 0x007484A9F0E0AD28ULL, 0xBF7F465904EE55C5ULL, 0xBCEA6D4CE752F34DULL
        },
        {
            0xA8FBE1A253EDE7B1ULL, 0xCC2D39C3AF8F00F0ULL, 0xF730674161914154ULL, 0xA25CB5B4227D92E0ULL, 
            0x60B6F4587696A015ULL, 0x4F265E410EA036B5ULL, 0xFED4B60AE9FB4C50ULL, 0xF39D06D6FD98A99AULL, 
            0x9AFD45C78C1E8C7EULL, 0x860E4642A21ED631ULL, 0x40CFD319B63D2786ULL, 0x7CA6ADFF70F61C7BULL, 
            0xA55013E79B5C21B8ULL, 0x8CFFDA9F4BA8F111ULL, 0x82D169EB01077398ULL, 0x4B17DB977291805EULL, 
            0xFAD415CEE84F443DULL, 0xC4D4AE6C5FD247B3ULL, 0xE57E203E74D41EBBULL, 0x6321ACD1DECE8F3DULL, 
            0x0D65D1B10A2F02D2ULL, 0xB17F572DFC748488ULL, 0x9146B3B310FF8892ULL, 0x56C669FBBE629AD5ULL, 
            0xE3E49F3FBFD97ED3ULL, 0xB6DE04D2DC14CE0BULL, 0x383324C32C6BB956ULL, 0x4F5E6E5925132EC9ULL, 
            0xF0E4CBD2387F3A1EULL, 0x9C72B989DB1DFD4AULL, 0x9C65370BC0A0FE6AULL, 0x9EF37A182848298BULL
        }
    },
    {
        {
            0x5DD7E3DDD08F90D2ULL, 0xFA05A7CB89B82B4BULL, 0xE0606CA4112FAD39ULL, 0x33D37632FB6FE398ULL, 
            0x8BFE446B11365872ULL, 0x9DB71FD3FD6B9ED0ULL, 0x1821CBFC365D2BB6ULL, 0xF12AB65616A05719ULL, 
            0xE8AF311BD534BC28ULL, 0x373E584B24B117A6ULL, 0xD5589DAD7507F5F4ULL, 0x7AC33E5E8E2DDDE7ULL, 
            0x73AD838893A4080CULL, 0x6AC3FFAD87F1CDB4ULL, 0x17CBDF2934AFE1E6ULL, 0xBB1F868440E8E5A0ULL, 
            0x4D1339006EFF3249ULL, 0x7890531C7FC331FEULL, 0xFA4D228DC57429EBULL, 0x324D61408422C1B8ULL, 
            0x950576BD820D60E7ULL, 0xBFF67661EA21B7A2ULL, 0x1A180666FFFCC860ULL, 0x6EDB08F1818CDF6EULL, 
            0x57F93F6267FD4553ULL, 0x136833F6010EBCEBULL, 0xBBCCAEBC89D74A41ULL, 0xEF6BB1B38966A2B4ULL, 
            0x76CC3B2CB1F04712ULL, 0x623234DD2C2D39C8ULL, 0xB4E11E6C056D87D5ULL, 0xBDCAED829C5E6479ULL
        },
        {
            0xB374D37792D2949DULL, 0x00322B959D85FC4FULL, 0xD7C58D589B19DB72ULL, 0x44DA9F743091FA56ULL, 
            0x5E8293C3834EED7CULL, 0xAB75D1284B75BD7AULL, 0xC7F40582B479F542ULL, 0x3B4873A5BD705E4BULL, 
            0xC3ECD4953435B3C1ULL, 0x54F209E4B638DB45ULL, 0x860C95E259CFCEB8ULL, 0x53CF7AEE010F6D6FULL, 
            0x352104A165A63F88ULL, 0x0706D665802D7A00ULL, 0xEA6502B1BE362423ULL, 0xF4A018864620A947ULL, 
            0x87A19DE418A3FCE2ULL, 0x7CC8C0A49350CCE6ULL, 0x45E565AD852311DBULL, 0x773C8DC32786D183ULL, 
            0xF71E1AEF98DDFFD9ULL, 0xF0ED335FCEE7616CULL, 0x537D77F1E7810EFFULL, 0xA061B3BBF354D6E6ULL, 
            0xE91FD212A94B0437ULL, 0x33C1C3071746D06BULL, 0x849254C1A47E72E9ULL, 0x156FF1F5C7370EDEULL, 
            0x89E1D0F9CEF2B519ULL, 0xD813309B2FDE2F6FULL, 0xB7001306FA050620ULL, 0x858D1BE444089756ULL
        },
        {
            0x04BBF572D36E08C3ULL, 0x4C079BA223B3F1F6ULL, 0xADA565056A1FB775ULL, 0xC7F138D50BB3FB9FULL, 
            0xA6453942AAE9E392ULL, 0x3A08C3E708EFF853ULL, 0xE44EFF8AE40D3B7CULL, 0xDF8DCD8E99BA27F4ULL, 
            0x10FB5E4C532FE286ULL, 0xF562CBFA5D37E3E8ULL, 0x9A128B220549581BULL, 0x2446B551CCE34865ULL, 
            0xE6499EA21C4A3AE5ULL, 0x0CBB99573534DE55ULL, 0x7ECD039144CAC286ULL, 0x5C1B1B00FB18C6C5ULL, 
            0x7BA3B87C3CB462FAULL, 0x09994D088048BCEEULL, 0x4F36FD70C39567BFULL, 0x6ADE1A165E0C0A19ULL, 
            0x510F4607D6278448ULL, 0xC7902DA8FB3CFC0CULL, 0x5F25ED11ABE9E19EULL, 0x85822ACA1BC3749BULL, 
            0x0361C981D3571450ULL, 0xDCC429DEC9070607ULL, 0xEC5B11268785EDCAULL, 0xE8E2DDB285D3CEF5ULL, 
            0x48920A5A9B8A97D7ULL, 0xB90B5342F206907DULL, 0x2D567FB25F26CA3EULL, 0x23535B0E34E0698FULL
        },
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
            0x6277F11B65A5A5ECULL, 0x3347B3890029B159ULL, 0x61C9FA0179B53591ULL, 0x01A481E619986932ULL, 
            0x76EC8DF171B905DBULL, 0x4132B9D14C8E0DA0ULL, 0xB46E42511F679A4AULL, 0x978298B6F9C4FE90ULL, 
            0x5ADF52F0FB40A375ULL, 0xEC8E848A901C2B06ULL, 0x2DA0F866C5142DEBULL, 0xB7728781F8A55FD4ULL, 
            0x352107106F9A95E7ULL, 0x91908529677657BBULL, 0x3A139B02200A0E56ULL, 0x3CC144C54BA5DDA1ULL, 
            0x9D304C31D196647AULL, 0x4E2FFAEF89A52ED3ULL, 0x97F1172628B64F46ULL, 0xEF326F53B488A422ULL, 
            0xB1119CDBFF5CE3F7ULL, 0x8FD54F1724E0A0E1ULL, 0x158FE7F49D0EC515ULL, 0xB0EFF77D6A9968CBULL, 
            0x4930A30C0E6436C6ULL, 0xC95AEA3FCF02ABD7ULL, 0xBA1F129F12DF9130ULL, 0xFF1A0B2173E84427ULL, 
            0xC8F7A356CDD366A3ULL, 0x804A9DA5F1C11229ULL, 0x98CA7CD6A3CA91F3ULL, 0xF5083F0768DD6CC3ULL
        },
        {
            0xC6C3710068FB529EULL, 0x6E247630A601679FULL, 0x72BE20643C5ED08EULL, 0xC9017063ACE613CCULL, 
            0x8F3A3CF1106E5B4CULL, 0xD17E9DD85B426A4CULL, 0xCC94A6DFFA439243ULL, 0x10EF5CC67C322089ULL, 
            0x03B8A8732BA2C138ULL, 0x6FF385566A104E94ULL, 0x869077117008D49CULL, 0x10E0E1C7C9CCB90BULL, 
            0x4F01D439AC6B87DDULL, 0xCC5431F43C28AE5FULL, 0x95D24FBDD8B96A49ULL, 0x76FF484108EA3A2AULL, 
            0x3800EBC098FB45D6ULL, 0xA3A39E3A1E823EBBULL, 0xB91883FC6BB173E2ULL, 0xEF0E73A57721F028ULL, 
            0x6A0A67444F99FA3BULL, 0x304803456A6859A2ULL, 0x2F1FB882E91A1994ULL, 0xB5BD3CDDF82C2E98ULL, 
            0xBF24D31F19BF0F60ULL, 0x0E2B76348EDD61E0ULL, 0x2C7A395A2954EF40ULL, 0x26B09DDF1831F933ULL, 
            0x894B4B7ABBAE615EULL, 0xE58C6DF19E7410EFULL, 0xD8645A2E9EF327C5ULL, 0x63E3E67721103326ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseDConstants = {
    0xC0A003B15DA6F86EULL,
    0x385BC16B2F7C2473ULL,
    0xB9FB611077EDCED9ULL,
    0xC0A003B15DA6F86EULL,
    0x385BC16B2F7C2473ULL,
    0xB9FB611077EDCED9ULL,
    0x45B8439A29714E42ULL,
    0x7A3855B87A529C0EULL,
    0xAF,
    0x48,
    0xD1,
    0xA9,
    0xD9,
    0x6F,
    0x48,
    0x32
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseESalts = {
    {
        {
            0x18D59D47B8D762E0ULL, 0xC57D4C237C99A6D7ULL, 0xE9B84C3D46100373ULL, 0xF2A3BC88BC522C38ULL, 
            0x305E403C9F663F5DULL, 0x0626E616CA2E484FULL, 0xC3F89DF9C08C81DAULL, 0xA2E370A17BB921B4ULL, 
            0x8CFA3BB1310556A9ULL, 0xA75122C9E9F875BEULL, 0x4A2BF6F60A460FC5ULL, 0x1B9806BC7700882DULL, 
            0xF1AF5B0DED595667ULL, 0xF09D7E9C9ACD1E95ULL, 0xFF4294A13C3FA8A1ULL, 0x14274FDEFEA204F8ULL, 
            0xFC78C29626262B48ULL, 0x9EBA3256A97121B1ULL, 0x28F9CF5A0F2AD745ULL, 0xFE0AE3E952A0E80CULL, 
            0x43827400C8EB827FULL, 0x4C92FD574806EC7DULL, 0x14FB3D75E1087018ULL, 0x2C5E736CA1354DCBULL, 
            0xB2CF0ABD23E1FFCEULL, 0x2EE539F8CA945CA9ULL, 0x3DFD9289DA2F712EULL, 0x9A8AF353E3607F02ULL, 
            0x82EB7E2E08284FCDULL, 0x6DF2AB0F8B18D08BULL, 0x6103A1739CF44CC9ULL, 0x0B65BB3BB49C8F4DULL
        },
        {
            0x3F5DCC5626BA0CC2ULL, 0x5BC36D260205CBC7ULL, 0x88DFE400DE743B5DULL, 0xD8FF6D0283F39691ULL, 
            0x42FD6FDA52ED758CULL, 0x10F5F5790175EE0DULL, 0x9D31CB7F8639B87EULL, 0x2850BE37F435A47DULL, 
            0x0CFE413FAB0BBD25ULL, 0x325D69B881217A7EULL, 0x7E285844C3FCFAA5ULL, 0xA2A3AC853DA20D41ULL, 
            0x1FDE1CE27CC87217ULL, 0x8FD927F9F00BE33DULL, 0xA2031F189D5215A3ULL, 0xF272D6DBF34763CAULL, 
            0x0B5B87B73E16E508ULL, 0x1C9E1AA4EAFC05EFULL, 0xC8AD1F9421C7B920ULL, 0x70204A8E6C4E435DULL, 
            0xB5BB01DFA2DF4C59ULL, 0x28F8C82B59832565ULL, 0xB6670278E9233606ULL, 0x912B46FAFE4F396FULL, 
            0xD6EF7DAF068206EAULL, 0xFC7D42CE58565847ULL, 0xF727E64611EA94D1ULL, 0xB42CDA6E8167A45EULL, 
            0x86586F6916140F9EULL, 0xE36FCEE1110D032FULL, 0x17F3DDC51AB87196ULL, 0x3D670BDA6DD16570ULL
        },
        {
            0x04E578ECB682A17BULL, 0x91B3C9FB01F1BD78ULL, 0x8F25AFC160ADA508ULL, 0x0FC2659A3097DF3CULL, 
            0x46B54A159949EEE6ULL, 0xAC913D37CAD97F02ULL, 0xF56AF2E8F25E5EF4ULL, 0x91CEC037C1B86465ULL, 
            0xC3AF46D051CBE4A2ULL, 0xFA07031B4B7DDDD1ULL, 0x468A10327ED8D356ULL, 0x20ACAD761E215462ULL, 
            0xB8701A576DC65DF8ULL, 0x5D424EE4376E3E52ULL, 0x99A64FE530B5F81DULL, 0x7094E92C7CCC214BULL, 
            0x44D13BD441F33EF2ULL, 0x587CDD5BEAC89783ULL, 0x48DA50686195490EULL, 0x28DD0DB366B1F637ULL, 
            0x60995493C9105C6DULL, 0x255ECDC873FBDE60ULL, 0xAE41130CFF16CD14ULL, 0x5098D8DAEDCEF132ULL, 
            0x6B6D027F80500556ULL, 0x5EEB131C1E9B4F69ULL, 0xCB747BC0743CC33FULL, 0x9B93B5DFD7B9931BULL, 
            0xF76D95C9FB6B433CULL, 0x99B4F238C0A503A7ULL, 0x22DFA3F8C69F1C30ULL, 0xE09CD952068A0A11ULL
        },
        {
            0xB361423BF28952A2ULL, 0x2AAA5850082515A4ULL, 0x1589119F460A779AULL, 0xB9D29416BC3A1873ULL, 
            0x74C24CCD8576CA37ULL, 0xC5BA16C0E4B1D09CULL, 0xB7A9A8C08663FC77ULL, 0x13BA31BB5AA6C851ULL, 
            0x3F4146ACA75F834FULL, 0x8001BBE544A767CBULL, 0x8BD54896C61B3C10ULL, 0x9BCE87B86D13C17FULL, 
            0x724C91D9DE33EDE3ULL, 0xAF46E10FDFAB5B78ULL, 0x643F86476C6CFD8CULL, 0xF19FD78B839F6223ULL, 
            0x7F5EB9AEDB0F31E1ULL, 0xBF936FD1C50D1883ULL, 0xC2F031A54A31967FULL, 0xAEFA87DBEDFD0A4FULL, 
            0x84465DBFCD2B3E03ULL, 0xBA56311690D3BFE3ULL, 0x1DF4FE692309CF69ULL, 0xC24B356558A15E97ULL, 
            0x57915FDD4095B7C4ULL, 0xD23795968168C407ULL, 0x21D8F6D958C35DC5ULL, 0x57D2E9C16D16C7DBULL, 
            0x9F18AC437DB9BAFDULL, 0xEA02AC13370F3B53ULL, 0x0AD3DE2F74C3B9CEULL, 0x3031DB4AFC78391DULL
        },
        {
            0x147AF8F5920876B5ULL, 0xB7549611BDFF94F2ULL, 0x399A6F394639DA1CULL, 0x94CE880259285302ULL, 
            0xA433FC3E4D35C24BULL, 0x901D945F81CAA213ULL, 0xD51398A92581F61BULL, 0x286B3A7234A902A5ULL, 
            0xE45EF91E2F363EE7ULL, 0xF1EF313B03712F16ULL, 0x6F0641B332EE6A65ULL, 0x04363A53E01F62D7ULL, 
            0x513C18FC90F00A2CULL, 0x969ED687D7CE9343ULL, 0x8723CD129A81BA5AULL, 0x120AB110EBC547F3ULL, 
            0x878D619BF356B057ULL, 0x5AC5C6FCDE55FB9CULL, 0x6EA99459B213F125ULL, 0xE94BFB0BBA829297ULL, 
            0x7C80BEAD2C14C87BULL, 0xA1D792F7CEA84D97ULL, 0x7F307DC690C73A0CULL, 0x8FF1544CC3E3FFACULL, 
            0x524ED8512F14F8F9ULL, 0xC05833D4E46D15E6ULL, 0x5A774D14D45A2301ULL, 0x6ECCFDEE5A2D55E6ULL, 
            0x5E281788DB07351AULL, 0x78753892631CCA68ULL, 0x232298FCE5AEF608ULL, 0x693821D5DE5C7C10ULL
        },
        {
            0x9FBB24D89487A634ULL, 0xFFA5D2323AEAC504ULL, 0x7380B32FE8681A2FULL, 0x471844BA7BDCBB25ULL, 
            0xA58CD95995C39BBEULL, 0x86D96487BBB17B7FULL, 0xCF30E4FC59504342ULL, 0xB08B93F35FD410A1ULL, 
            0x8E54939A16E27DF6ULL, 0x1A286F27BCE360F0ULL, 0x4A73DDA398D82136ULL, 0x814930D2B23878E7ULL, 
            0xC5E7B04F2EE4655EULL, 0xF0F7C048B2054BD4ULL, 0x8BF9668C4C2E1575ULL, 0x314D10E5C0356682ULL, 
            0x978105F64274EA3DULL, 0x38A30F78AA9BFED9ULL, 0x4BB4372306D4B7DCULL, 0x49D2971C91A8593EULL, 
            0x9F068B96F6D19D20ULL, 0xD1149B4C51006680ULL, 0x58EDE756CC5727FEULL, 0x25494248136BC9D1ULL, 
            0xF69C992F15E0C4F7ULL, 0x9B45F8BAED779273ULL, 0x057B659D9269677EULL, 0x9A0E3C348AED197EULL, 
            0x436BF94782989D8BULL, 0x065F019F096A1148ULL, 0x6B644E3770A68D11ULL, 0x744A73CB6B8C6483ULL
        }
    },
    {
        {
            0x0AA13EA25498945CULL, 0x0650F459B0F23DB5ULL, 0x1ADBEDA67943913EULL, 0x9D295D61CC9F5B4AULL, 
            0x8AD18B7755F8EEC0ULL, 0x04CD749CF76E4A9FULL, 0x4780FCD695DD9DBBULL, 0x209688C77C5AD6A5ULL, 
            0x8A14D948115A86E0ULL, 0x798AE73C8C04ED90ULL, 0xC019FE0A2A476887ULL, 0x28DEDB826AE9249BULL, 
            0x288D0B95778D7D41ULL, 0x565D13EC5EA16DD4ULL, 0x6F54D87B31C825E5ULL, 0x43DA63D8F807E1C8ULL, 
            0xB5F609DC5F880D6FULL, 0x86F8F9CCFCF11A92ULL, 0x9B39438747077222ULL, 0x82653FCC1CB95EDCULL, 
            0x91D5600989DC3DBEULL, 0x639BB447D363B3B5ULL, 0x1A11BEC1C965EEAFULL, 0x8FCF25C124126E6BULL, 
            0x088BB05950222136ULL, 0x009E308D9220A20EULL, 0x6BFCB17DCE153DF0ULL, 0xCC52F13A35721350ULL, 
            0x4597072DF03A1D4FULL, 0x0639E84391913E6EULL, 0xC86098C7A92DF702ULL, 0xE836D292D40F87B5ULL
        },
        {
            0x52D2B15929D7DF9DULL, 0x3523BE0ED6A44E35ULL, 0x0B39F1A0A45BEF9FULL, 0xB40ED4D627A742A1ULL, 
            0x88A969367A3702C8ULL, 0x74C7A737329E3544ULL, 0x5B92BC7CA88E4613ULL, 0x2F72C97B8B789681ULL, 
            0xE96A993B6FEC3810ULL, 0x7DAAFC83C1D13514ULL, 0xA9254F36823BC73AULL, 0x0B1C36FB7A5BCEE2ULL, 
            0x95416D60B77628EEULL, 0x55866208F156C27AULL, 0xDEEC15A66316DF6FULL, 0x8014C08D091F22ABULL, 
            0x9E420AADD6C1BE14ULL, 0x72A381E34F524CA2ULL, 0xDF142CA8561539F4ULL, 0x04E7F1780CDE5FC3ULL, 
            0xF1D793051BA8F6D0ULL, 0xE21947C24D2B2B0DULL, 0x441D004913B9EBB6ULL, 0x95D16F5DA8B824F9ULL, 
            0x2E9520738C68319FULL, 0xE3D60277FF3CDABDULL, 0xCA8A73ABAF3A9C78ULL, 0x831BDE290CE38B1CULL, 
            0xF33A2097A832C72CULL, 0xE244AB1E7A1BC2E6ULL, 0xBDEBD6079798F348ULL, 0x51B38418BB3BCD30ULL
        },
        {
            0x5D31DFFBE0CBBB49ULL, 0xB4D5A850D91E29CAULL, 0x45EB3CD47ED67841ULL, 0xBE81457D2FD109A7ULL, 
            0xD9883B273377A55FULL, 0x739DCD7C4A1A3190ULL, 0x02A9416032A7184DULL, 0x83D611645E8E6EEFULL, 
            0x6B66623E4A87FA5BULL, 0x47A60CF379D51153ULL, 0x27761FB07AD8FECAULL, 0xC39C9FAB7F26734BULL, 
            0x52CB9CD220ACA467ULL, 0x9C4E8670F545E67AULL, 0x06263CEA30751426ULL, 0x8DE14FCD3EA4B1EBULL, 
            0xF79D2F5F09746F68ULL, 0xBA8D9BF7B8FF11A5ULL, 0x8E0F888F48D79122ULL, 0x1EF67DB2A87C78ECULL, 
            0x9918495960CFD42AULL, 0x0CBD594D138197E5ULL, 0xEBCEDFA66FC6E105ULL, 0xAE6E3E62920E5FF3ULL, 
            0x399824DF794E887BULL, 0x316DB5878DF796D7ULL, 0x4CB86FE02131AD62ULL, 0x95A0CCDD5394145DULL, 
            0xB3DBC06A52609D89ULL, 0x028EED871172FDE6ULL, 0x24C97AF307F575A6ULL, 0xC75E3698EC2F932DULL
        },
        {
            0x49FADEF086E100F4ULL, 0xE868463A292BFE58ULL, 0x27BA544926EBFA35ULL, 0x0583A5BBD94E9626ULL, 
            0x0EB7FE650D15AEF3ULL, 0x980C089F3803FEC0ULL, 0xFDADB186798083D9ULL, 0xBEE93175521B0CE2ULL, 
            0x06FFC304FFB20A9CULL, 0xA7ABF7F1F3FD4A6BULL, 0x428C1A8D9E2502E7ULL, 0xCC349665B0150E52ULL, 
            0x4078943DE333DB66ULL, 0x251F5E2C1AE105C5ULL, 0xA862AC00087227E4ULL, 0x2D80E14D3F697D0AULL, 
            0x09B5E7BFAD1AF424ULL, 0x36DD20603E19FD43ULL, 0x593FBA2E617368F1ULL, 0x222EAB7D7B97D3EBULL, 
            0x2E90A00DEF7412C8ULL, 0x829BB1687F8A0EA2ULL, 0x2B95C557939DDE83ULL, 0xD39FA7B4F0142DC7ULL, 
            0x75F470E5C3DC3D72ULL, 0x285B94D494CB20D0ULL, 0xA5A3E85AEC694904ULL, 0x0FE7C6F4CE2BC78DULL, 
            0xA4DA5007F2496BD5ULL, 0xE2A9F58BFF1D56A0ULL, 0xCA9E5FA752277C50ULL, 0xD7C0425F1134C9D3ULL
        },
        {
            0x76E6CCE7ABFE521EULL, 0xDFF828D0FC1E6B33ULL, 0x7E93FA408199072BULL, 0x6841E9497A51ABF5ULL, 
            0x95D87C86C6D31BBBULL, 0x7510E5B351D8670DULL, 0xF4E1B021AC631EF0ULL, 0xEB40D42EA8C0E446ULL, 
            0x78EC2AC4B8CF4378ULL, 0xCBB1903A403EA7BBULL, 0x1ADB63242F820155ULL, 0xC0C4228E55902404ULL, 
            0xDC69639677D3F149ULL, 0xAFE7ABF1C5DB7FF9ULL, 0x36EA97E9F203823EULL, 0x220866C0779817F5ULL, 
            0xF298A5CC1193B5DDULL, 0xA7BAD826F90A23EDULL, 0x9533C78B277D56C0ULL, 0x3AABCF8DBB4125F1ULL, 
            0xEB08EA7F28448A53ULL, 0x590C51245DBD710BULL, 0x7B2056D277F1671BULL, 0xC526C23927F2155CULL, 
            0x089D13B60AA4D3DCULL, 0xA03574F787832D5FULL, 0xA81430D4560EABC8ULL, 0xF35B9E1A8C203E0FULL, 
            0xD6CF5A54ADC347D3ULL, 0xED76FF62B9E3E2D9ULL, 0x428859FB5A9CA15DULL, 0x640C9866DFE63B95ULL
        },
        {
            0xCFF5D77171967809ULL, 0x6D533B39F8398523ULL, 0x11DECC6EA49EE8D0ULL, 0x4056987D79C2430BULL, 
            0xE5002F5848B6D64CULL, 0x9B57E88C05CFCCD1ULL, 0x739DFD989A85FB18ULL, 0xE37937888BB35581ULL, 
            0x4510D54A4C1CC375ULL, 0x95CE692FA0DB21E1ULL, 0xD9BF65CE03B45D9DULL, 0xD0B6EAF80A66FCB3ULL, 
            0x186495DA0949857AULL, 0x29405AE137F54438ULL, 0xE93E691890CCD299ULL, 0x8D13A57D64B5CBECULL, 
            0xC8AD7DFB359F06BCULL, 0xAE3E9A77DD83D22EULL, 0xFDC97607B6C034F8ULL, 0x8FF87EF6CB1D9022ULL, 
            0x4D3D2941B88F2BA5ULL, 0x19FE5364E1B1E882ULL, 0x3C52BEF2EE9F3ABBULL, 0x8798EAAC12355957ULL, 
            0x5932846534284CDAULL, 0x9DE0B2BBC4B59C67ULL, 0xDCF29552F9575956ULL, 0xAA783F75800DD727ULL, 
            0xCA9B713DFD3ECFC7ULL, 0x6DD5B335902B8CBDULL, 0x49622A26CAF4AAF8ULL, 0x274DF05B4DD62923ULL
        }
    },
    {
        {
            0xF46ED1D8B9E6992CULL, 0x8719014866C56849ULL, 0x78473BBF5C778C6FULL, 0xE0C2B4E5348F2704ULL, 
            0xDA21D148F0D848BDULL, 0xD54B6AB5619CBCFBULL, 0x66673508993019D2ULL, 0x35E32A45775ADD13ULL, 
            0xD62350F4E7F1CF78ULL, 0xCEBE62E96D4E10FAULL, 0xD6CA839E08F7B76EULL, 0xE17F41A712B0D96CULL, 
            0x6CF5321EA820C12FULL, 0x2DEB44D5FEA2314BULL, 0x5659FC178FDAFB49ULL, 0x956A1745C4FAE851ULL, 
            0x7ECE7974E5398024ULL, 0xBD0EE3492031F0E8ULL, 0x10E70F21E50547A5ULL, 0x6F82B1F11FAA4E2DULL, 
            0x33E92C6A41E3100DULL, 0xBA079F5E9D7BE64FULL, 0x804C63CA227C60D0ULL, 0x469C079E30CB5A89ULL, 
            0x0894DA4B850F636AULL, 0xD4FB993F865DEE99ULL, 0xDBAFB452EE3A5D0FULL, 0xD6A30DFD6A906E9CULL, 
            0x3B70E85BCB788FC1ULL, 0xE4FB26F007803946ULL, 0x88FB9206BAC3ADEAULL, 0x2F23F60A0AEE630EULL
        },
        {
            0xC59D6607DAB656EAULL, 0x19D1760BBEFF9FF6ULL, 0x78B7003D5E498672ULL, 0x6981180FCF614077ULL, 
            0x0A2AB13BDD340DD7ULL, 0x58890D4F20978BC7ULL, 0x2859DE5339BD7C18ULL, 0xB2D07E1A054CB27BULL, 
            0x0C9CBEBC8901F194ULL, 0x569416EFF602D9F4ULL, 0x08F502F047E5600EULL, 0x7DD1A7A4255DDF11ULL, 
            0x4131D3E2BDF0C731ULL, 0x7900308B3BD25740ULL, 0x25884E3560A645ABULL, 0xC1E5625B5F9C133CULL, 
            0xCE005ABDE5E7B16EULL, 0xC4D9BDC232E64A03ULL, 0x56B85462C9212248ULL, 0x4413DE961565C02EULL, 
            0x7194882FEC8A29D5ULL, 0xCD9DEA37D6F8B0BFULL, 0x3E48E6F2114DEFF8ULL, 0x4F3A39B926D6DEF5ULL, 
            0xF286FFEBF52409CCULL, 0x8B5670948D4A5388ULL, 0xB13E267CE329ABB5ULL, 0xF7AB4DB35491F7D1ULL, 
            0xDA20F4AC96B468CEULL, 0xA205B56A9F7DF134ULL, 0x1C489F1868632DEBULL, 0x7FBEA39AD8F69AA4ULL
        },
        {
            0x1CDB5B99602361B7ULL, 0xF61D93A5921F2F0AULL, 0x4473569B1F28C23AULL, 0xE703FBE3E2D2AF48ULL, 
            0xB98DB6660F674F3BULL, 0xC79F780C0DC6043BULL, 0xC3E3159244A6E8B1ULL, 0xEC2DE44AE3BF6612ULL, 
            0x560B9F54232ABD73ULL, 0x8D1F558403AEDBC0ULL, 0x2BDFD17EED2B0178ULL, 0x12D28FF9373FF8F2ULL, 
            0x5D363E007606C19BULL, 0x7A5DB045E2E1111AULL, 0x61A7A0323233D946ULL, 0x27663D5BB4852DEDULL, 
            0x9736752E3349E9E9ULL, 0x80B2378DF9A2CD69ULL, 0xDB9A0094E16D4667ULL, 0xE1EF0AD336D1916DULL, 
            0x1E47E672B550E70BULL, 0xC2F838AE1344D7F7ULL, 0x22A4A19082848764ULL, 0x5D9CBFCDEF9946A0ULL, 
            0x63FA81F887F75CE1ULL, 0x940DAD7AD9DD693CULL, 0x8BC3A8719860DE41ULL, 0xC000329814C418B6ULL, 
            0x3B1CB1FE57CAD338ULL, 0xF7C2909E3376037DULL, 0x78D4279768436AE6ULL, 0x81CA9C84177DD4E9ULL
        },
        {
            0xAF63572D8984370EULL, 0xE08152BE182B650DULL, 0x1160A504264ECF40ULL, 0x255727025D670007ULL, 
            0x6CC636AD294C46A6ULL, 0x910A736A9AC29519ULL, 0x94888C8E237A4C19ULL, 0x66B18F8F0E1D1C05ULL, 
            0xC4033F370AA6C9A9ULL, 0xA12805E2DFE6D059ULL, 0xE11A2A68999EEAC3ULL, 0x6B3EC7A47C3097E6ULL, 
            0x86B64A804AAA46C0ULL, 0x0E9FB732E157F5D4ULL, 0x87AD58EC9B4CFD3AULL, 0xA281FAE0AAE7E8CAULL, 
            0xEF86FE5D22F1E29BULL, 0xAB0DE0F3D1224A1CULL, 0x4A76AD63EFECEC53ULL, 0x92D77EED00824DF6ULL, 
            0x1299C80A11154706ULL, 0x064C27636CB27F78ULL, 0x018EE8FF9681CAD8ULL, 0x079183083C3F2B06ULL, 
            0x546EBEA09EFC613DULL, 0x969FEC6C2C472CC6ULL, 0x840A03F6796469A5ULL, 0xA4BD1900EE60A8E6ULL, 
            0x998F3218EDB9C887ULL, 0x2F1D7ACA57524F3AULL, 0x2FAEA02AD54EC1EBULL, 0xBE9EE6E367B1CA78ULL
        },
        {
            0x9A9726F407C49707ULL, 0xFFCAF08EFC7746D8ULL, 0x1B4108DA039C9052ULL, 0xE1EEDBD3A77E1AF7ULL, 
            0x57345A547531ED85ULL, 0x2F24DCF441827875ULL, 0x5EB513F2BE0E13EBULL, 0xFA86D4C316871F33ULL, 
            0x8220F1C748357A5BULL, 0x31DACB6AB02A7D5AULL, 0xCB4AE2A676EE9A09ULL, 0x50BF4E2271120FFDULL, 
            0x737E8F69348619DDULL, 0x617EB12D7454D8CBULL, 0xC19FE32B8F8127B3ULL, 0x74D879C3BAA448D5ULL, 
            0xAA74867D47521D54ULL, 0xE19674BAB6B53AAEULL, 0x569477E74D64539BULL, 0x8249E88566151119ULL, 
            0x34459F4798ADE254ULL, 0xDEE7336837F56BB6ULL, 0xAAE9769A2B6CA7FBULL, 0x660AAFBB6034D812ULL, 
            0xF262DF317FF4898FULL, 0x8BBA7AD06B3A492DULL, 0xCDAB77748944492FULL, 0x82B60CEA163A57A1ULL, 
            0xC1CA9C588A377E43ULL, 0xDA983DEBB0C64B44ULL, 0x591CEAA66BBF5CC0ULL, 0x854558C76F141B64ULL
        },
        {
            0xDC14C00E13B628B5ULL, 0xDF4F38AC43E67D73ULL, 0x706A0313CF535CCCULL, 0xE440DECDA760954DULL, 
            0xD9A5B206B50BF9B1ULL, 0xE706841BCD11D541ULL, 0x59FDAA4D6FDC829CULL, 0x597E8BABA03ECB26ULL, 
            0x7F83A74DA279C80EULL, 0xCB3C068A6DFAA016ULL, 0x98B99DE729DEC84FULL, 0x5575FC1A48237DE2ULL, 
            0xDE07F76F049D5E2CULL, 0xD1921211F2A4F558ULL, 0x3E2C488F741CD8FBULL, 0xC06F55E698BC6B47ULL, 
            0xF0358A77027C0EE3ULL, 0xA8BB1AC933596994ULL, 0xAB87D9BD0E8CB82CULL, 0x3EA61FAB612C3E54ULL, 
            0xDA7E32ADBF766ADAULL, 0x82AB3CCD580BCD64ULL, 0xD644F7695BFDB610ULL, 0xC7776E5CAA759B7FULL, 
            0x8B90065B8DEF605EULL, 0x4813B451364CD9DEULL, 0x287581C20AD01D3AULL, 0xA03ED45A1CB48EA1ULL, 
            0x65BB9BF1456DAFBFULL, 0xC147D42CF50A42B2ULL, 0xBD2A40EEB7D8F8A3ULL, 0xEA9FFE1569A6E235ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseEConstants = {
    0xCF12442BF1393F7CULL,
    0xABD2E404CE584A18ULL,
    0x5BA061F28EC4D5FCULL,
    0xCF12442BF1393F7CULL,
    0xABD2E404CE584A18ULL,
    0x5BA061F28EC4D5FCULL,
    0x5063AB7301803505ULL,
    0x09AEEC2D8EF5F508ULL,
    0x69,
    0x6A,
    0x5C,
    0x8F,
    0x81,
    0x51,
    0x1E,
    0xB1
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseFSalts = {
    {
        {
            0x51C62334DE186F27ULL, 0x9AFA0FC537773A1EULL, 0x523BC79DAB39F3CEULL, 0xD85016047A4C195FULL, 
            0x6BABC5FEF99A0EA4ULL, 0x642CCCA12EDDB110ULL, 0xD9B4B36644A15500ULL, 0x58D4D1735AA5262BULL, 
            0x3B5C9E5DB62D1FBFULL, 0x02C78938A4C5C276ULL, 0xED0B02A4018151AAULL, 0x9CD93C18A8CC5119ULL, 
            0x35499AE0E6E494F0ULL, 0xE7465B8755BF185DULL, 0xD1507122B7FCE1F4ULL, 0x7C9A64C636D95CE0ULL, 
            0x6A5E672340BAE367ULL, 0xFDE568BC56642AB3ULL, 0x9F9846E60A294BF2ULL, 0x55F887BE412141F8ULL, 
            0x278A15D035CFB3DDULL, 0xFC425AB008C5F41FULL, 0xD96B9EE54D6FEAC2ULL, 0x1B53CD4CEDB940A8ULL, 
            0xAF8B149229BE000AULL, 0x5A3DFEBF8723B144ULL, 0x7008CF78441FBABBULL, 0xF84F79F41F96C405ULL, 
            0x696D2CC575F04A98ULL, 0x28DD758180C3AA4EULL, 0xFBBE1BD8C60FF88FULL, 0xF33F6396B25CF181ULL
        },
        {
            0x78E7C2265881DE85ULL, 0x7BC8D2E70AA504B3ULL, 0x1C75EDBCA1864722ULL, 0xA725D5822059EFE3ULL, 
            0x0F931DE509920DCCULL, 0xC7EF77D92BE763E3ULL, 0x1D73E6F522001C83ULL, 0xD561E129F777EA4EULL, 
            0x887CD998CEDF3B3FULL, 0xD16DBF450A2B5E5AULL, 0xF310838460521435ULL, 0x005642376736998EULL, 
            0x65D184798406E47CULL, 0xE1A6AE9DBCB3B9B2ULL, 0x98AB0F439D1ABAD3ULL, 0x2C5D00ADB08D8E7DULL, 
            0x55B69F8F6A466ACAULL, 0x063E80177C8BCA7BULL, 0xF69B4E3CB3C9B336ULL, 0xD78FDFA639E5FFCAULL, 
            0xFF0E504ADB6DCFD3ULL, 0x0E62991888274788ULL, 0xC5C281BD65070591ULL, 0x9841ACFA13875069ULL, 
            0xDBB174B21BFBF3F8ULL, 0xBB3AFF859AD9096FULL, 0x5D18F2523D0F6C9EULL, 0x0385C8A08FE91F12ULL, 
            0x209ABA63E922B8EAULL, 0x042635CC822CC7AAULL, 0x40FA361C9941D699ULL, 0xA709AFEE6A81DB67ULL
        },
        {
            0xDB8D1085EF3BAA00ULL, 0x7F3C07809A0D37FEULL, 0x0A52FC4AF042DC30ULL, 0x62D4ED314D1F0403ULL, 
            0x984D83A1D3D27BADULL, 0xC570260638FF5296ULL, 0xE87E83E1CB79FBD8ULL, 0xB3E946B85E16995BULL, 
            0x3875A9081754965FULL, 0xC413AB7ED0A5F22AULL, 0x4EAB566AE04EEF59ULL, 0x80D42CCB59CCBE18ULL, 
            0x268CF370CE2EF43EULL, 0xD4320D3B6954C915ULL, 0x7341D735E06F72B6ULL, 0x1901BFE5B151719AULL, 
            0xA70DA9CCA1AF1A65ULL, 0xC0C0E68BA8B147EDULL, 0x69C131C7944CA818ULL, 0xC2C5393F7B294829ULL, 
            0x7B6FBABFB0D60364ULL, 0xD42275031F2FF61EULL, 0x5315AE39A0FEFABFULL, 0x625A0A8A82E55FDAULL, 
            0x39F0FD6B2CE91E8DULL, 0xDB5E15081E36A7FFULL, 0x219D6E6CCDA53AEEULL, 0x7592C4CC570F8978ULL, 
            0x4B76B032F2E10943ULL, 0x2C5999564A9B7284ULL, 0x2FAC0D546B8C26A5ULL, 0xCEFDEA6261AD8B82ULL
        },
        {
            0x30B084A8E9ACB0E3ULL, 0x88414F653DE1C1A8ULL, 0xE774BFB85AD97F9BULL, 0xB4132F6A1BE43318ULL, 
            0xF4F3589A99E3A05FULL, 0x4898675A751BB4EDULL, 0xA3D67A36FCA6DEA5ULL, 0x2552F293FE924FEDULL, 
            0xE457D5EBC3FD9712ULL, 0xE7D7EF8233963D6EULL, 0x56C1D83A65210116ULL, 0xE7B785482D2B6FBFULL, 
            0x3339FADF1367D114ULL, 0xE11BF93F12275746ULL, 0xBA0F091433A457BBULL, 0x4FFAEFB542D236A8ULL, 
            0x8045D6A4F2932CC7ULL, 0xCC28E582AD490623ULL, 0x87FAE959160D15A3ULL, 0xE8237768FFB57CBDULL, 
            0x73EC0A8EFEFF372AULL, 0xD51DAE4BD3D951ABULL, 0x451E1D19D68861E5ULL, 0x27EEC191229DAD70ULL, 
            0x4F0DC73CAA37F50BULL, 0x9C423EE80B5B6911ULL, 0xF0F0C5AC8E9B7F62ULL, 0x587162F29A94397DULL, 
            0x2754E3B3BE7F77B3ULL, 0x2D205588EA9A6122ULL, 0x659BF10535DD6A6FULL, 0x64287919583FB84DULL
        },
        {
            0xB9BB498BC900FD18ULL, 0x0A32CF5A5D81A0E6ULL, 0xE027FC8D4F65F35CULL, 0x5BDE9C7F9D7D2453ULL, 
            0xB56AA798F80764DDULL, 0xA3F85F972EB9F9FCULL, 0x16A72008981504B1ULL, 0xEC0B5896D5C34577ULL, 
            0xEFBFE1324D9CC926ULL, 0x98FB5CF6CCDC99B6ULL, 0xD7017D850F21D917ULL, 0x1983D64D289838AFULL, 
            0xB715FAEEB08BB36BULL, 0x678B97D35966B222ULL, 0x1BB8E2FE75FBE534ULL, 0xB13DE75364B66299ULL, 
            0xA254C8A139922100ULL, 0xD0092515F4E6B315ULL, 0x6801735B8ACB61E3ULL, 0xB45F7AD5F45D3298ULL, 
            0x0B0C77803AD0FA50ULL, 0x5DA6DA7A3280AAE8ULL, 0x154FC2F6A6D3E235ULL, 0xD6F07009FF90A856ULL, 
            0x91B33DF7189249EEULL, 0x528E7CF0C913C759ULL, 0x58294FDEA53394ACULL, 0x3B3ABDCC60668E5AULL, 
            0x4D8FD5834A7CDFA9ULL, 0x18939C3CC67398EFULL, 0xB4E0009F2FBBF92DULL, 0xA4C1C0043DE826C3ULL
        },
        {
            0x5530C73B330B5F39ULL, 0x3E19D18313EE8B2AULL, 0xD5B593AF7780C93BULL, 0x39DDAC73F5258B09ULL, 
            0x75277A3CCD479EC8ULL, 0x5927551DC14447A4ULL, 0xE4E0AB8848D717BBULL, 0x7A3137CEB45453FCULL, 
            0xC4BB158A3A95E8DAULL, 0xBE0EA7FCD9D46FD1ULL, 0x5CFC063252A54B7EULL, 0x9D9A3C1B166BAE49ULL, 
            0x9225A8713C731E4BULL, 0xB4E1949CD4D61C32ULL, 0xC527A3DAA4DC03B0ULL, 0x552928075AC13191ULL, 
            0xD188746A50E975DFULL, 0x2AFBA81E331BF442ULL, 0x2AFC2ADBC8D916ADULL, 0x6EACADA0D9AD9789ULL, 
            0x01BE46BAB7083D19ULL, 0x76B11D8701C85F4DULL, 0xD2E95DD9C8D3CD49ULL, 0x81C3C46CE2B2A88FULL, 
            0x12E2D07575B5D78BULL, 0x4A9FFFBD6F11CD27ULL, 0x3685B9F36D15DFE3ULL, 0x9BF5037DE377F734ULL, 
            0x3447BC97480E308CULL, 0x68FE72A15E7BDF44ULL, 0xFB5630EDDECC8CDEULL, 0xD6B23F6DE4495F0BULL
        }
    },
    {
        {
            0x2F3A54899CAEE124ULL, 0x18C2325F053E87D8ULL, 0x3E9B370FEA348A1EULL, 0x786448518AC69D71ULL, 
            0xFE097D21B05A7F99ULL, 0xE2A2BC54594AC640ULL, 0x903BA1D3F9AC3D5EULL, 0x9A2913EF888E588EULL, 
            0x70D691130EFCE59CULL, 0x70AF50FA8F87CE76ULL, 0x1D98500153604DC2ULL, 0x78C678182BD2FC06ULL, 
            0xE1513C884EC30800ULL, 0x7FBD1F3FFB18361CULL, 0xC91322039E27CF3FULL, 0x97E514A7BA0FE7D2ULL, 
            0xC6DBBC9F88F440F5ULL, 0x59E347444F266606ULL, 0xBCD19DA1FB8C2A0FULL, 0x0626ECA217F16A17ULL, 
            0x7D13445409DD4EFAULL, 0xD7BEAC9909F4C429ULL, 0x68EBAE194475451EULL, 0x9DED99A05C729C5DULL, 
            0xE23C05038B2808AAULL, 0xC21D7138924D7B2EULL, 0x06954D3FFFF782B4ULL, 0xF6341A56611A1BEAULL, 
            0xEF511702F06185DCULL, 0xF05C76F989F52432ULL, 0x546D77B97D767784ULL, 0x0D1A1DCAFCD1682BULL
        },
        {
            0xA0D13B15CA20DE9FULL, 0xA2F170D1A15690BEULL, 0x7EAC6FAD4FEF70D0ULL, 0x827D6244AAFA4FEAULL, 
            0x8DEE724D7B333938ULL, 0x534ED1DB7D6922FFULL, 0xBDEC2CC2C5A897EEULL, 0x1574B8E89D541A56ULL, 
            0x517A1E7D2B3B1959ULL, 0xA0963A0E842A67B2ULL, 0x94634961ED10DE3DULL, 0x5198FF3965B34F0AULL, 
            0x902EA80127453F85ULL, 0x1A22E3925A37D101ULL, 0x92C8BC963651E821ULL, 0x68534EB1E8172367ULL, 
            0xB5462E8DC82B9F3FULL, 0xC8A4A6EBC9CC2947ULL, 0x623DD24AB98C069FULL, 0x67C5D4C30642FD32ULL, 
            0x42B30406978708F6ULL, 0x226CFBF4DFF27E6CULL, 0xB1BEB6B71433106CULL, 0x976A02820EB13B6DULL, 
            0xF2CA349FFF356D7EULL, 0x62C05300290898A4ULL, 0x211BD169F4A076A7ULL, 0x03013D7262BEF129ULL, 
            0x92086A43F4475F0BULL, 0x325AD2CD54F4F01DULL, 0x15A23669D3505F02ULL, 0x8A6A3C32EEA1F81CULL
        },
        {
            0xA9DC12FBCF0D7385ULL, 0x73B6D3A4F8AFA890ULL, 0xAAC239BEDCBA4247ULL, 0xE2CE485D96C58824ULL, 
            0xB5F7699588AD7867ULL, 0x8C7AD4EC8D2F7793ULL, 0x13EFC1DB0793923CULL, 0x62F4EA24114218D3ULL, 
            0xB7A23477D8B7B03CULL, 0x6EAE7A35B9C9DDECULL, 0x0CFBD5D375B3E858ULL, 0x65D4409A063091E3ULL, 
            0xE79AB8E26C47B061ULL, 0xF90377794BD0E9BCULL, 0x44D190CE6A46BA1CULL, 0x9BC70FB959ECDAD4ULL, 
            0x0D38AA5CA0EB855AULL, 0x4A0DCCD0ECF014C2ULL, 0x87F4629970353746ULL, 0x0896947ED9A62E52ULL, 
            0x98AF6AE2D98F37EBULL, 0xAF0433E7DFD1A90EULL, 0x813D2280F92E5946ULL, 0x733770F573F0CFDBULL, 
            0xE28F1979689A84E0ULL, 0xC3BBC01A5C6B6FFAULL, 0x5878DBEA4FD35564ULL, 0x55CBE8B2A4E857DFULL, 
            0x559AB3C7665FE8C9ULL, 0x46C7EAACA908BB34ULL, 0xF7A88E6A47A80E3BULL, 0x2EF6A8E7BEE6F225ULL
        },
        {
            0x269ABF83624C73B3ULL, 0xEF0BF31C1C0EE6BBULL, 0xB8BB431CDAF2CF3FULL, 0x79FD6F26C720256BULL, 
            0x4F099C6EA813AFB4ULL, 0x82DE353282B960B1ULL, 0x54DB5919F930B776ULL, 0x2E0817D1705BCBD4ULL, 
            0x0A2531FDF6D72425ULL, 0xC19F77A90AD9E9F3ULL, 0xC35B603D44B2C9B2ULL, 0xA9DFE6A0907587E3ULL, 
            0xFDACEBAE6CE09815ULL, 0xD7F691C003BA9D2BULL, 0x34A3A39ED517FE11ULL, 0xF8A09DF4F52FF713ULL, 
            0x7D676DEA28A79D47ULL, 0x711CFFAD982027CCULL, 0x0B8B9BA255310DD6ULL, 0xF3A59B77EE5D70FBULL, 
            0x76B869D29A8E22C6ULL, 0x1DECBF0EF896BB28ULL, 0x9EFDF242C7D8A1F2ULL, 0x202F38CFC6EBB640ULL, 
            0xDE15A0B9686B8A88ULL, 0x3FF2712A395AA859ULL, 0x4BC04BC15591E93DULL, 0x3B9E24D9CA376A95ULL, 
            0xFC25F4B7DF634E83ULL, 0xE843F012B09248D7ULL, 0x6B22758B0FEB0618ULL, 0xB19EE541F809DE9FULL
        },
        {
            0x719869661B00FAE2ULL, 0xC17D6E6C893CFDCBULL, 0xDCAA3C70ECA8789FULL, 0xBF416E302182C256ULL, 
            0x712DECF07AF8D490ULL, 0xE3C345827C4A8C70ULL, 0x1294D7D66C0384B6ULL, 0xFB63CEBC6FFB428CULL, 
            0x6A90FFAF8D215298ULL, 0xAF43E6FC7DF88753ULL, 0x63E3B9468CDD3C09ULL, 0xA32D442472613828ULL, 
            0xAFB0339FB3A62025ULL, 0x919C01C443904265ULL, 0xDCDD5BB77BDC19F8ULL, 0x1BED16EE273AF3BAULL, 
            0xC2658C228213E18CULL, 0xED68C16178CA4A28ULL, 0xC2466017930AE3FDULL, 0x960E2585FD0B1878ULL, 
            0x1485EC11D3A82877ULL, 0xAB76988F0656C978ULL, 0xBD3E0208216F095BULL, 0xF7513A1F26784EE0ULL, 
            0xD640E99EC9476D63ULL, 0xD123169831655A61ULL, 0x9D812E764B40F2E4ULL, 0x1053E4DE64D50A4CULL, 
            0x42C01192A6DA6C3EULL, 0x1465DF26F7F83D37ULL, 0xA03B52B250B1870AULL, 0x6BECC9AF478B7483ULL
        },
        {
            0xCBAFCAA1D9D0A4E7ULL, 0x4A665CB95E0651DCULL, 0x4C671E4A7CB9C8BAULL, 0x472CEE3687177B1FULL, 
            0xB39B6DE9F868AC19ULL, 0xE34BD3AB4FBB4B67ULL, 0x6E20CB185089CABEULL, 0xC9364761E332F2C9ULL, 
            0xC95D0AD4DB5655A0ULL, 0x7841383917506708ULL, 0xA63B6D26C089BC66ULL, 0xE2353769D9426D0DULL, 
            0xEAA7B47B89BF9130ULL, 0x915AE349BBA62383ULL, 0x753DB8F067B4B562ULL, 0x8C1F5E32C7B58C56ULL, 
            0x68B7001A9DD911C4ULL, 0x35E9F2623305A272ULL, 0x35BAB094231450DCULL, 0xC8E5193554283245ULL, 
            0xF984FC02620E25A3ULL, 0x3A23A57C0B26879EULL, 0x7813D22C54E5303BULL, 0xFA9D64E556F0FE1BULL, 
            0x1C63E9621C2A86DFULL, 0x35CE42A6D656DBCCULL, 0xE8B8D6F02BD859EFULL, 0x2BFCB14419E80F88ULL, 
            0x139A8F052CE48279ULL, 0x6E3D755899E6B23EULL, 0x00018F9E4E2BC8AFULL, 0xB7B8FC0E10F36DA9ULL
        }
    },
    {
        {
            0xDF764AD72A53D25CULL, 0x4A21168AC0A0CEB1ULL, 0x9F463B20CAF69470ULL, 0xDE50534642E0F040ULL, 
            0x4E30D2C9BE12E633ULL, 0x8CD8013D5CE85EE5ULL, 0x38F21A76AAAB3876ULL, 0x722977253DEDD746ULL, 
            0x5B9522E1C02869F9ULL, 0x4A4626CE0613DD49ULL, 0xA7E6CDEA585D6B5BULL, 0x550617E98165F207ULL, 
            0xAFC1DF095E3FA398ULL, 0x03C68042A1E516C4ULL, 0x4DA638D9B3574D55ULL, 0x3A6EFD552C296A42ULL, 
            0x7E8B30996F4CCF1BULL, 0x15F629AE1B2043C8ULL, 0x523743A2DD0A6A38ULL, 0xBF90BC9E69461735ULL, 
            0xDBA120F054A58D6EULL, 0x7FD21CAAEA657DE9ULL, 0xBA708F172D4C4CB3ULL, 0x3D121E20055EA38CULL, 
            0x40669B8564B0A3D0ULL, 0x18126328EA0B7299ULL, 0x0D9C8320ADA3C538ULL, 0xE396E3280A1BB706ULL, 
            0x503FF1E7F697C86EULL, 0x707A0C1741C53603ULL, 0xA51D032B612633C5ULL, 0x295D0BAE7EB58964ULL
        },
        {
            0xE9C877933F2C2224ULL, 0x5C7859AA57F15DB8ULL, 0x5E4450CC7E085362ULL, 0x61E2921EBD89B523ULL, 
            0x9940B222EF3B9763ULL, 0xB1B4E8C2D2975FA7ULL, 0x3CFB0CBD3A0DCC01ULL, 0x91F9B574EEE1C070ULL, 
            0xD4EF3A90525E8EE7ULL, 0xC8D5F128B81C43A8ULL, 0xBF4A8EBBEFD74F9DULL, 0xBAF3CA11F464A590ULL, 
            0x32B9F9546064EAE8ULL, 0x037B2CC29ACEF268ULL, 0x5CC436DA1048DD0FULL, 0x90DEE1F13BD36F39ULL, 
            0xB5CA0270A9B2C708ULL, 0x61FEA7BA913772A4ULL, 0x9F6B0C8F416E0ED8ULL, 0x9A28560104A1287DULL, 
            0xEF18722C363432B3ULL, 0x24F3FAE7C0AE684CULL, 0xFB082A2ECBD97FE9ULL, 0x441860BE7CC5AFCDULL, 
            0x9BB230F3B41322CFULL, 0x3240E6381D352FAFULL, 0xE2C618AAD7B910D0ULL, 0xDA597BD55B85E623ULL, 
            0x81DBEA55B7D6D170ULL, 0x1DA4122507C37DAFULL, 0x306042DF27F1BC09ULL, 0x89266ADF52D1C4D1ULL
        },
        {
            0x7B345568B24DC693ULL, 0x06373E1356A3B36DULL, 0xF8A4A6040241B75AULL, 0x719820897D45A2BBULL, 
            0x1A69D4EF639EEBF3ULL, 0xA90393E5F7F6F7EDULL, 0x5F455FA70BE036BFULL, 0x3AB162B8777B8689ULL, 
            0x2B1D429ADBB3B4DDULL, 0x1C9AF9CD5FE5CD2FULL, 0x826DA3AA9EB9C5DDULL, 0xC97FE13A1245E707ULL, 
            0xA17F923320F404B0ULL, 0xB6EEC08C758EC4C4ULL, 0x17196BEE8616A662ULL, 0x7704ADD6B4E1AE56ULL, 
            0xD3624DF6631A9192ULL, 0xD8B71B939D1A79F3ULL, 0x20FD0F6A08755597ULL, 0x10B04F4AD0DD3445ULL, 
            0x5F3CCBC49EFEA860ULL, 0xAE80FB3760305686ULL, 0xE8C6EB31E50F0C3DULL, 0xC0BDF857A4F43E98ULL, 
            0xD122E857CB5F69D3ULL, 0xF9A80C11655FB39EULL, 0x369BE064077E8950ULL, 0xD1C409D114DF35BAULL, 
            0x1CB209EE062CCAA8ULL, 0x4FFD9DFF1BEB810BULL, 0xAB38136264366FFAULL, 0x4F443A09F2F439AFULL
        },
        {
            0xCA1082053924BF5CULL, 0x66A94C3A5926F0C4ULL, 0x987B851C12AD930FULL, 0x6207E817E46EA8D7ULL, 
            0x1763860B17BD43E0ULL, 0xFDC8EE9D3D8B13D1ULL, 0x5620CF307971D627ULL, 0xB4F48629929E741DULL, 
            0xFF5AA4183B368131ULL, 0x59A99B971F992AA3ULL, 0xEFDF4E417A3DD12BULL, 0x3D9326CBC4993DF6ULL, 
            0x7C98B8675DB756C6ULL, 0x74A2671666595F2BULL, 0xC662EFF79F7486E6ULL, 0xEA07C8E7D344E9FAULL, 
            0x2D1A35110D73C635ULL, 0x8C76DD4A67611B7FULL, 0x5608277B1C5B1869ULL, 0x958B289625372BD7ULL, 
            0xC3C0A18017169DF3ULL, 0xF3B0FED765DF9BD9ULL, 0xBAD49D557FEFF1FDULL, 0xA9D4242841A691EAULL, 
            0x56F4D5BB6E953D76ULL, 0xB6B434ED6154AFF4ULL, 0x9636240247CA5CFBULL, 0x00D1659D2994F783ULL, 
            0x3407B614AA532466ULL, 0x3AD497E6EE3550B9ULL, 0xE086E227347723F8ULL, 0x80121BA3200C1355ULL
        },
        {
            0x11B09C89E50E7585ULL, 0x6A09D778F1D65C46ULL, 0x13AE3D252A7B3B7BULL, 0x6034E233541020A4ULL, 
            0x78001DE7E042EA74ULL, 0x80F6CCF0BC320C8DULL, 0xCBFDFE8D0E847CCEULL, 0x95DF3018EA9EE8FEULL, 
            0x12E9E65AE8CAB847ULL, 0xE4590D2AA097442EULL, 0x9AC14C4DD36009EDULL, 0x0049FAB7A550997BULL, 
            0x9851B94A7C03EC40ULL, 0xCB5B28FA2AFF4007ULL, 0x13B4720A167CC41AULL, 0x15FE5DAE26EA50C8ULL, 
            0x3044C7E29532B383ULL, 0x6342C31E701CB7A7ULL, 0x343BC46C16D15376ULL, 0xCB90D43DEB0327B4ULL, 
            0x685490448C70D24FULL, 0x90FEDA64FE2212F5ULL, 0x357D047510E5B674ULL, 0x200B1EF57706F24AULL, 
            0xC22A95023416C7E4ULL, 0xBD962ED6CC48CE23ULL, 0x0BD9C5F999F944BAULL, 0x2E5A55BE18A94FDFULL, 
            0x88A2FA64C8A75FC2ULL, 0xA7CEA6D54D201BACULL, 0x3B51F268FAEE7DB3ULL, 0xF9B5E3A86A42E99AULL
        },
        {
            0xEA26880F4A6606A2ULL, 0xEFE6F26D45458831ULL, 0x38C1233B2BCF3097ULL, 0xBE6832F0B0D5FDE7ULL, 
            0x2D8A5546D812AD13ULL, 0x10B60DD68ED011DBULL, 0x357B43430A59D0ADULL, 0x6D1C667C8AE596BFULL, 
            0x67CAF6E36DBCA634ULL, 0x7D14E1A1DA781C16ULL, 0x00B26F5BDDD1081BULL, 0x8B59A2F6050AFB94ULL, 
            0x8FB3F26C8A2EC275ULL, 0x65A2A147BA47BAA8ULL, 0x283167B9E8FD51B0ULL, 0x84AAAC3FB0FD5D4FULL, 
            0x5E6105278D66F99BULL, 0xE3A9AEA3F948F30DULL, 0xF122EC6191711B77ULL, 0xDB769981711803F8ULL, 
            0x08D2230E84A77D9DULL, 0x46B2E9540587620DULL, 0x58D82AA1B87DC1A0ULL, 0x63CCE016FE946663ULL, 
            0xB11B3C5837D7C5EDULL, 0x67B4FF4273138B76ULL, 0x5A8D0CFFF6DF2D6FULL, 0x12646494F56AA842ULL, 
            0xDE36ECA4F719A58CULL, 0x87410B022B8211B5ULL, 0xD7F0B36BD0463FFFULL, 0x53CD879CB264CAC4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseFConstants = {
    0xAF6DF21A5CD8DA37ULL,
    0xC5AC838732D05427ULL,
    0x12486BAF0F201B47ULL,
    0xAF6DF21A5CD8DA37ULL,
    0xC5AC838732D05427ULL,
    0x12486BAF0F201B47ULL,
    0xDB2DDB2E29638F17ULL,
    0x9BC57D20FF5DCA11ULL,
    0xAC,
    0xA7,
    0xBA,
    0xFD,
    0xD7,
    0x79,
    0xD1,
    0x6B
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseGSalts = {
    {
        {
            0x67104B608FF061D9ULL, 0x445D1427D20108B2ULL, 0x1F6D5B5F2BE1EC63ULL, 0x686F1E122C7C3F67ULL, 
            0x9C0F5BADAC4EAE97ULL, 0x1E7176E73C206374ULL, 0x185498C85855012AULL, 0x74F7D84CDC3E2FDDULL, 
            0x1B43279D2593FDC5ULL, 0xDC02CAD37A68652EULL, 0xC38262500C558DA3ULL, 0x25D0130A32C5A455ULL, 
            0x8623012B2E0BDEEFULL, 0x09466E21395019C8ULL, 0xD160C9E79EDFD44BULL, 0xB937719DE8ECE81FULL, 
            0xAFF25135205C4324ULL, 0xC22BB2F9521745C1ULL, 0x0873559E0A3883AAULL, 0x6F145984C4F2D7B6ULL, 
            0x90F6D538FD860031ULL, 0xCEAB974358B6C0A4ULL, 0x68D0D422543A8FD4ULL, 0x0C4F66FE9D8465BFULL, 
            0x93DACED8F57C801CULL, 0xAA3F24C8CC96ECBEULL, 0x00094AD12C9E7196ULL, 0x56DCB0EB4B055D52ULL, 
            0x61ADBAF197259440ULL, 0x0ADC39DE4409E5B0ULL, 0x745A29167A5F6BEBULL, 0x55B14FB6938A48DEULL
        },
        {
            0x58B9251B39813D21ULL, 0x0F949DB689121CF8ULL, 0xC397D56A4CF01ECAULL, 0xF1C0140E2CD1EE81ULL, 
            0xF4F5DC2B2136BEECULL, 0x63CC50FBC96A46F4ULL, 0x46BCBF8A7ABE2742ULL, 0xBFA5689990D0C6E0ULL, 
            0x3161776BCC897347ULL, 0x9F22C540E821714FULL, 0x595ECA5D3832B5A6ULL, 0xB3AA604F04836E51ULL, 
            0x0ABDE9D7A92E4C91ULL, 0xAFC4F4BAF9CA176CULL, 0x381CF7CAD03E1028ULL, 0x8B9759F8910FD464ULL, 
            0xB383EBBF487BE1EDULL, 0x190321A0AB07F198ULL, 0xEF6CEC21AD58418DULL, 0x570380B63E883F0EULL, 
            0x3EF22C2691942DCFULL, 0xE43808C5BEFB33E7ULL, 0x0978F492E23726B2ULL, 0xA74FED57E1058A45ULL, 
            0xD670AD28769CE734ULL, 0x659833D8FE171EDAULL, 0xB300407A65336641ULL, 0xAD470980C2B52A04ULL, 
            0x17C465A443B7EAD1ULL, 0xB7F15EC12A42BB30ULL, 0x23F2A619D0D50427ULL, 0x442B601E7B60B0B9ULL
        },
        {
            0x9EBB6F4B70312729ULL, 0xDC89F9057A9C6D83ULL, 0x583491FFB5A1E1D6ULL, 0x90E182DDF4982EB3ULL, 
            0x3071C8A566E22D00ULL, 0x23D06BB979E650C2ULL, 0xBE1F7CB62EA8BCF9ULL, 0x09E10EFB98180852ULL, 
            0xBF815D4EBD104BFFULL, 0x6DB25DEB0C583166ULL, 0xA34BBE3FDCE6DA55ULL, 0x525267174914CB96ULL, 
            0x36F8910AA8F923E9ULL, 0x9179DB71CE54F962ULL, 0x82BA285FA7238544ULL, 0x5B83550DDFA37A29ULL, 
            0x54E09D36245F2329ULL, 0x0E4BC67424EBD717ULL, 0x63179CFFEE558092ULL, 0x9805EE6619AAED35ULL, 
            0x8BA1CCF23442966EULL, 0xC7CB39137B452368ULL, 0xBB55D0D614950B79ULL, 0x4D15A1B6CD859AB1ULL, 
            0x17BFFC588CD8C58CULL, 0xFDF22DEE6101907EULL, 0xF1D8B27AD18F8219ULL, 0x13B8F15EFD95DB79ULL, 
            0x73C9EF892BF87D79ULL, 0xB2F9F8B520BAFB82ULL, 0x1A629F392CF81B63ULL, 0xDC7C78E828566848ULL
        },
        {
            0x4C0061DE5B65C72CULL, 0x0F3B525C87D81E00ULL, 0x4169F4D4FAE0ABC4ULL, 0x4E9FA79525E312F3ULL, 
            0x1C4B1A48E9CDE1BFULL, 0x74E6D5922E9B1EABULL, 0xD87E163458647C5CULL, 0x7397717019DCE2F9ULL, 
            0xDE828D33E7D41D3FULL, 0x4CE03FE443FB13A8ULL, 0xD5D9CF415DDEEFB7ULL, 0x51C0DF9B000E3472ULL, 
            0x6278FDDDF8258904ULL, 0xFC3D8C1585387DD3ULL, 0xC539DA4F8B24C81CULL, 0xD156011874C2F1E1ULL, 
            0x572498EBCAB93643ULL, 0x08F56954B0E247D1ULL, 0xCBE1C35C4F2C3879ULL, 0xFB6FFDC8D40826D5ULL, 
            0x6F029DB9D11229E7ULL, 0xE0DA77698958A920ULL, 0xF7E3D4D7FC84FE7CULL, 0xC47C839373595E4AULL, 
            0xE638BA3796AACF5CULL, 0xF7E75BD69819CC9BULL, 0xBBA3B84FEB58C68CULL, 0x8D72516597474264ULL, 
            0x3377B024FE377E29ULL, 0x61ADAD6F351BDD66ULL, 0x0E24E8E7CF3ABBB2ULL, 0x32A848CE765F6098ULL
        },
        {
            0x75FE504B0E3813DFULL, 0x01F5AE3EBA883789ULL, 0xEA41F818E3F899F7ULL, 0x204E17A6631034F4ULL, 
            0x93A853A437EB83E4ULL, 0x888A427C4BEE58C5ULL, 0xEB986D2DDA7BCC4DULL, 0x3D3F930BDFE74E9FULL, 
            0xC13DD85D9A71B3EAULL, 0x04A301E92250B1E1ULL, 0xDE04AC5FC7AF0BD5ULL, 0x0E23C8CB7D444E2EULL, 
            0x41B3997D90C4DBFCULL, 0x164BF4230888B3A5ULL, 0x6AF3256B85F5AB5AULL, 0xA51E1F68427432D9ULL, 
            0x7464955DD9EB2CA0ULL, 0x94A8584CFF60617AULL, 0x18423CC6DF0C9753ULL, 0x778A0B569D39DC34ULL, 
            0xECBA54BF1471FC45ULL, 0x4963E00C4959A078ULL, 0xAFD97F6664035796ULL, 0xECCC6B92715420E2ULL, 
            0x3772A16732B6BDEAULL, 0x2259B37D39BEC070ULL, 0x1153F611D01E7558ULL, 0x018D3BA0530AB0EDULL, 
            0x8E83ABC55D88CD05ULL, 0xF98BADF6FEBD51ACULL, 0x7637309328DF3B32ULL, 0x1BE7F25A381C4D82ULL
        },
        {
            0xBD7F3DD170DCB974ULL, 0x1FA28FDB789FC214ULL, 0xFF9637DA135E7C8DULL, 0x1147C9A0E96381D0ULL, 
            0xCCAE3BC601C2DA0EULL, 0xEAC48E0C751BE8FDULL, 0x148C6EA674F4A69FULL, 0x58F80275819A0F30ULL, 
            0x9D030B02DEBC59B7ULL, 0xD1CE04D36EC95D68ULL, 0xA2882784F6BBBCB1ULL, 0x87A5359F398801C8ULL, 
            0x490EB0B9F3A4F365ULL, 0x91BB92422B804A10ULL, 0xFE4DDBEF098C527DULL, 0xD13035CDCE3EDB08ULL, 
            0x5A6D9812210DF442ULL, 0x7CF7D89DB6525E1EULL, 0x4891D71B6BA1795CULL, 0x1BF947C707922738ULL, 
            0xE233E9EB93BFD733ULL, 0xB144E929E4842C7FULL, 0x4AB9863458160A52ULL, 0x9FB98ACD170D8094ULL, 
            0x7F7668D07CEFF7FFULL, 0x6DFB71BB2936524BULL, 0x507D1A7F9A3B7018ULL, 0xEC4902E2E8675248ULL, 
            0x0264DF37DB76B6DAULL, 0xD1B07A8230BB7A9AULL, 0x6661525AD2F685CCULL, 0x8EF22B10B1F0491CULL
        }
    },
    {
        {
            0xED3EEC5EF05B8859ULL, 0x20F0FD6391C9D051ULL, 0x878FA56E39C72427ULL, 0xC2C0070FE0A61BB8ULL, 
            0x8EDC82D43EA9B42BULL, 0xDFDF299E48A4309EULL, 0xDEF2B097272D174AULL, 0x4C3A3806A1226EAFULL, 
            0x3CF3425DD1A1C866ULL, 0x2922105383C6CA72ULL, 0xFE809C42EABD2561ULL, 0x639928090ADB6D8FULL, 
            0xD7D6832A370C5129ULL, 0x31537DFC24B75AB9ULL, 0x9096E2C7E211CDACULL, 0x184BC10B52A41126ULL, 
            0x330D050F85611C18ULL, 0x7B5EA75C9B93240BULL, 0x7FAD43DAFF683314ULL, 0x94142EFE0199B39EULL, 
            0xC4127E89CAF8F72BULL, 0xA6DBDDD34D2D1A84ULL, 0xBF77A3992A560310ULL, 0x296A49CB6467168BULL, 
            0x3D981CA941039E16ULL, 0x7C4D14FA2AB4B77AULL, 0x48F35122119BCAF8ULL, 0x08939A3E0E12520BULL, 
            0x49DFB2F9ACBBACFAULL, 0x098A39772A4066D5ULL, 0x03F237BBBF95A4B8ULL, 0x88AE022E3C443621ULL
        },
        {
            0xBA5C40A99477451DULL, 0x2BB8EF9A9F0370CEULL, 0x8E050C350B7042A8ULL, 0x21FEC980B5140D7DULL, 
            0xCFEA8ED1D3260BACULL, 0x54950D1B4AB89A44ULL, 0x3F96DF460C8787F0ULL, 0xC9287BB8320DDD1AULL, 
            0x98955EEAB939E454ULL, 0x1A95CF114FE166D0ULL, 0x7A8D4C2DBC6C4046ULL, 0x893BEDC2BD4E7BDCULL, 
            0x21591E7D88244ABDULL, 0x8023DBD5BA3BFD61ULL, 0xE670307964D12057ULL, 0xE37B62EB80A7C25FULL, 
            0xC90BC94F23531E1AULL, 0x6AE9461FB3144510ULL, 0xF9BAFD0D4C8E8C73ULL, 0x7E2A504CE7029EC5ULL, 
            0x2235C89FC82268FBULL, 0x970ADB793E1E00D8ULL, 0x3089FC10F2DDEB74ULL, 0x4BA7190777E57F84ULL, 
            0x9ED4195F261AA069ULL, 0xDE94E4821019998BULL, 0x4493F32EE415ECCAULL, 0xF37D99CB9A7B861BULL, 
            0x78A3257516863E18ULL, 0xA771949283E0DE41ULL, 0x028443671EF83932ULL, 0x132BBCDAC4D7BE70ULL
        },
        {
            0xCFB5E6AFBDB9D8DFULL, 0x35A83F4AAF23A4C8ULL, 0x04958CE971127870ULL, 0x65CD9C497733F3D9ULL, 
            0x4D4D5F56ED59439CULL, 0x8B6100B24FA56AF2ULL, 0x0015634700DDEFF9ULL, 0xE1C343D3A07C27FAULL, 
            0x3ECC38334082AEE5ULL, 0xA0F441305B0C64D2ULL, 0x2D11B636A4F39971ULL, 0x73C916BED8E2C65BULL, 
            0xB40E1581ABCE976BULL, 0x2105693370A58458ULL, 0xF1D8A0C4ED0FDDA6ULL, 0xCCF4EE4C97D93E80ULL, 
            0xFBE7C144289AC1DEULL, 0xB81A51E363560783ULL, 0xEEA81A82166EDC37ULL, 0x2E88D953F9F61E29ULL, 
            0x85427780B2CBF3A2ULL, 0x758BF340F5045A3EULL, 0x3AA7C62BC4C579DCULL, 0xF2B62A5C2446F420ULL, 
            0xFAEDAA3605AD5C2AULL, 0xC270C56A1A6220C2ULL, 0xED9D9E56488CDE44ULL, 0x0E4050CFE6B777C9ULL, 
            0xEA2691C676ED65A0ULL, 0xB2DA41610D464B28ULL, 0xD1E56D2D7D3C63EBULL, 0xB87B6DDDC2B90CCDULL
        },
        {
            0x99EF1FEDAFF8B249ULL, 0x2EE18828EFF23B58ULL, 0x11FE3D2ACFE4F1C3ULL, 0x20E865058437F173ULL, 
            0x25C3CC7058B26BF6ULL, 0xA400F90B0C1285CBULL, 0xB066231A68AEF331ULL, 0x52AB85EBA7F92CF8ULL, 
            0xA6625CBEA8175783ULL, 0x77CE9AFB97EB592FULL, 0x8E11C1C94D9F68F9ULL, 0xFC7DB44CEB29EEC1ULL, 
            0x3DD0740999EA15EFULL, 0x1C8438654F2A3D90ULL, 0x645B76AB819BE020ULL, 0xBB61E8BF57824465ULL, 
            0x5952D39988A2B172ULL, 0x9133ED14DB53BEAEULL, 0xF666E6991522BD61ULL, 0xC3B9E87B2BE35373ULL, 
            0x6692DF455C9845F3ULL, 0x9782DA8A902812E0ULL, 0xCE7886DBB4B2D277ULL, 0xCA0081D38CF4961EULL, 
            0xEF0A1E76E07601BAULL, 0x8D7A419C70725FB2ULL, 0x9CD5792EA7ECD372ULL, 0xD595733044E728A0ULL, 
            0x4EF474B9E40F7CFFULL, 0x6E244D9C9E21DABEULL, 0xB483EE197B79EC49ULL, 0xA3088DCE36A3787EULL
        },
        {
            0x3579CA6162809A53ULL, 0x563A125722A3733EULL, 0x451FDDBAA2C81A5DULL, 0x69F972B06784A205ULL, 
            0xF42721187FB50380ULL, 0x709CDE8AF620B949ULL, 0xBBDDA06F1D3BB489ULL, 0xD9FBC7F0252FC842ULL, 
            0xE118C81B451537B3ULL, 0xC883CD02315A89E3ULL, 0xEECE83FD3DCCE72EULL, 0xEB69D8737B59C695ULL, 
            0x55F540AC279D1D7CULL, 0x82224EE4D22D26C1ULL, 0x0279B70F86C26417ULL, 0x8652A4687A478897ULL, 
            0x14360FC9413F8200ULL, 0xE00AF5785D879284ULL, 0xFDFFC59F36A3BFFCULL, 0xCF81E0AC97ECB155ULL, 
            0x4EA890D5B71D789EULL, 0x679C3D9F6CABEDF3ULL, 0xB39580034E2E1A37ULL, 0x0E28D7A1792AC001ULL, 
            0xD20654B087869E29ULL, 0x9298B08C3EA258ABULL, 0x7BAE7F6992730310ULL, 0xBD09D9231A8199F0ULL, 
            0xA310560CE3B8C2E1ULL, 0xD8B1A444C6D40D8DULL, 0x30CF1FD9C9BF90D9ULL, 0xEA32F5E849EAF8C5ULL
        },
        {
            0xD35EDA1B506456F8ULL, 0x5393582A35AD0A57ULL, 0x583F3F8744963E0DULL, 0xEED4F9AA6763CAAAULL, 
            0xC03ADF7183079249ULL, 0x1DF4ECBFE8AA3278ULL, 0x8BADE495752D8C45ULL, 0xA8187717BF777DD6ULL, 
            0xAB68DBA3E71FBE6DULL, 0xF37CEE91E39936CAULL, 0x8CCC05AB41DDFE12ULL, 0xA18F963FA9FBDDB5ULL, 
            0x295E72AE1646E7F1ULL, 0x81CBDC5B27D298B9ULL, 0x1B725CD9B3A7B53BULL, 0x925C5F2502C8A5B8ULL, 
            0xC3D5F49B808685D0ULL, 0xA714F27833BAF19CULL, 0xA976207F5CC8A374ULL, 0x8497C5AC434A3EB8ULL, 
            0xA9F5668E45902ECCULL, 0x1B5859E64D09A54EULL, 0xD454BE109DAE732AULL, 0x1F0BE4C76DDA44E1ULL, 
            0x03A16764B59333DDULL, 0x85DE3939A28FC853ULL, 0xA2DA007F466A29AEULL, 0x8D955484DE596599ULL, 
            0x621BC2EDD735A8EEULL, 0xFD6AA15ACDF59A65ULL, 0x8387EF2BFC505623ULL, 0x0B56B10F24FF2BB2ULL
        }
    },
    {
        {
            0x66BD5E1D4C58B609ULL, 0x2D8AA7DE66BFD8DBULL, 0xB210CCDACA48401EULL, 0x63BD0612A5B28B82ULL, 
            0x5A340D69067772A8ULL, 0xF908902F405F7880ULL, 0xAC0837FB04D68555ULL, 0x97FD870C88914513ULL, 
            0x9924F62201F3A5A3ULL, 0xBAF0736C88EB2381ULL, 0x9B9B1CC37F23BF5FULL, 0x73EC124713E5B408ULL, 
            0x461E8B631027154BULL, 0xD32A70E31F1CBD30ULL, 0xE94A7F3D6FBA9C5EULL, 0x0C50878C24AD14A6ULL, 
            0xDE3C37CD9EA69AE7ULL, 0x513CD261C179DE4AULL, 0x1AD6F56CB1E10022ULL, 0x06EA18AB0F504EC7ULL, 
            0x146F0FE27AE3FCF9ULL, 0x7C05F61AEDEE9BE4ULL, 0xED945C66BEDBF690ULL, 0x4B5E4B86EF525FE0ULL, 
            0x55366ED8F8816137ULL, 0x852982651F653E59ULL, 0xD718C5D30DCEF81AULL, 0x6E937DC4AE2728B9ULL, 
            0x7B44B4B6C127BA74ULL, 0xD6B6DBAEBF279BE1ULL, 0x2C2BD5CA03E79471ULL, 0x612E992ADE1D0655ULL
        },
        {
            0x83DBBEDE1B0C6A71ULL, 0x35A60F6A7D72D958ULL, 0x6E11F269813BC8F7ULL, 0x771D05D9D908AFA1ULL, 
            0x204A87E772B00461ULL, 0xED1991D5685E206CULL, 0x63F96035154B4EB1ULL, 0x9E90622C674BAD03ULL, 
            0xD014A00CCC3F983AULL, 0xFA138F8906FAE6E3ULL, 0xE9983F17733838A9ULL, 0x501C855F6BFDAE1CULL, 
            0x40336E5A7FFE8912ULL, 0xBE6C73B277F78738ULL, 0x0B15500A78F11009ULL, 0xFA1D03DA5E6B7D32ULL, 
            0x82638A8555025E39ULL, 0x136B173DC9FB6337ULL, 0x42A847CE57E6CFFBULL, 0x2D531AC4338FD9C6ULL, 
            0x05268BBDBC5CD659ULL, 0x1923D4FFA26C5E86ULL, 0x86611A81F4467FBEULL, 0x2AFC6098D2EA9203ULL, 
            0x245C38FB3C6FA478ULL, 0x71863E206D31985FULL, 0x1B859D9E8A522E1DULL, 0x624A8F727D67B7C3ULL, 
            0x9981CDC0A56C56BAULL, 0x8E507CF876B01C9AULL, 0xF3E1A1D483738EFFULL, 0xD2EC3207ADD5DB1DULL
        },
        {
            0x118DCE97A0D65F2CULL, 0xDA94F29421E874A8ULL, 0xC8E4D39179C027C8ULL, 0xADFEB811EF547935ULL, 
            0x502D0D3623735C5CULL, 0x9C348F9DE3B9EEEFULL, 0xEBE29FE92DB7FE78ULL, 0x010842EE09674175ULL, 
            0x899894A69A2DEF10ULL, 0x2850F814F706D56BULL, 0x822BA2F0DAB10375ULL, 0xC41024B05C79B801ULL, 
            0x75F5170E1E520E43ULL, 0x332F79B5821E0796ULL, 0xDF1D51EA5C3361EAULL, 0x307173759AC2AB31ULL, 
            0xDD16DFA3264DD740ULL, 0x0174AE616727B47BULL, 0xC0A5C6B87A15B98FULL, 0x3DB091189A06A9D6ULL, 
            0x1E8799036D94A113ULL, 0x933A71D48E862D21ULL, 0x609CE98C2984C055ULL, 0xDD1DF63DF2934BE1ULL, 
            0xBF438E70A671A774ULL, 0x56B7146869212DDAULL, 0x316CFED7036F530EULL, 0xD4DF073FD555811BULL, 
            0x74DC73FACA8B899FULL, 0xB1CC76AF3AF907ABULL, 0x0F7D60E41455AB37ULL, 0x5ADB707C15FEFD93ULL
        },
        {
            0xAE1BCA464D3AE709ULL, 0xDD61B949BB9B9728ULL, 0xC576E94C1BE16185ULL, 0xDF8F0ED5AAB3C7DCULL, 
            0x2DC4A649A9B3B656ULL, 0x519719E845977400ULL, 0xC43A809F3603CD9FULL, 0x912BA0FFF1AAA991ULL, 
            0x35522FBB349B1A61ULL, 0x551065C8D87C6E4AULL, 0x8D323371A38B1DC9ULL, 0x17F9294705B9E9ABULL, 
            0x853C5910DCA1492EULL, 0x74D5D665104BF0EBULL, 0xD2AB4FB416491832ULL, 0xFD487E384266419CULL, 
            0x0ADDFA2714CBF2F2ULL, 0x71D85B9A819EA75CULL, 0x85B8AD799DA82CB6ULL, 0xF7EA3BA11404D353ULL, 
            0xA30EEE047604028FULL, 0x45862F2601CA25E7ULL, 0x09A9279877987714ULL, 0x6A23F6430F600FA0ULL, 
            0xBFFD4A865237F6C6ULL, 0x61A860CC9CC6E54DULL, 0x1A51029604A46B99ULL, 0x92D95933E7B079A8ULL, 
            0x645210C0358FBBC7ULL, 0xF56C12F4590D6D7FULL, 0x7486C75AF063891DULL, 0xEE788EFB3A3F6DC1ULL
        },
        {
            0x1AD17473F75ABDB5ULL, 0x8F972553A2A2F453ULL, 0xB3C3F4074AB315B1ULL, 0x5A1379AC1FAB6D46ULL, 
            0x310EFA9D24D55FE8ULL, 0x2843135FD8CBA2A0ULL, 0x41721EDC66675C27ULL, 0x315FB678DC2AE0B3ULL, 
            0xC3A1A7C77D4EB72BULL, 0x3F379DBDE9233480ULL, 0xA0A5DA3492E1FEECULL, 0xD74BF2192D5D5BC8ULL, 
            0xF8F6ED49B042B79CULL, 0x5C8A8B60E14B947AULL, 0x59DBA070FCD60D0AULL, 0xAF4BEAFA18B300F4ULL, 
            0x9A7FA21A412B59F8ULL, 0xD3194664ADADFBF1ULL, 0xAFF57A04C50D78B0ULL, 0xFB1604C8A6337E1CULL, 
            0xB9C1ECBE02217AF7ULL, 0x7C2145EF9A7D151CULL, 0x074C72D214F7641DULL, 0x77C3278D94523A26ULL, 
            0xACA32979451848BBULL, 0x90333F34CBDD5B9EULL, 0xED71DBD558E0F3D1ULL, 0x942C6DF0B5E2FF31ULL, 
            0x95B6865DE190E107ULL, 0xF7542A31EDDEFE17ULL, 0xC8EB3CF1020D854BULL, 0x40408E96CA558583ULL
        },
        {
            0x088B3B148292BBA8ULL, 0x4628FE0440C0572CULL, 0x33FE18CE67B7CD7BULL, 0x514945605B1E54A4ULL, 
            0x8D95907C7D6D92C0ULL, 0xB4296D107222272CULL, 0x7380E08D3A797AC9ULL, 0x4F3241177E8B5F86ULL, 
            0x893DB12608C28E59ULL, 0xF478823284BFB617ULL, 0x9940997C8FA5D418ULL, 0x9F74310A8F596869ULL, 
            0x82E308DD13A80555ULL, 0xD33633FBBE0A959EULL, 0xCDE7033BFAA6E389ULL, 0x1E39DA79AAD4304CULL, 
            0x1E26080CA8B4C744ULL, 0x1572E42520716236ULL, 0x89D8E2524909BDAFULL, 0x6C645692C68DFF13ULL, 
            0x09949C391213DE6AULL, 0x73462DD123D12FDAULL, 0x53CAF133ABA612A5ULL, 0xABBD757E2EBEF950ULL, 
            0x314F87D7B6A47AB9ULL, 0x2665F4E9308B284DULL, 0x276B006E1FF34A67ULL, 0xE83D3DFB3F7B655FULL, 
            0x00EC5E4696C7283DULL, 0xC6EB43DA5F953366ULL, 0x00AC8D14923E66B2ULL, 0x21E948CA2460A521ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseGConstants = {
    0xBC3600C63FE15E79ULL,
    0xC0D7948256014783ULL,
    0x584DE06CAC5FD026ULL,
    0xBC3600C63FE15E79ULL,
    0xC0D7948256014783ULL,
    0x584DE06CAC5FD026ULL,
    0x596C35B36D29C2EEULL,
    0xECC7A65C01B9DCD1ULL,
    0xA2,
    0xDF,
    0x9C,
    0xE2,
    0xA8,
    0x1F,
    0xE8,
    0xAC
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseHSalts = {
    {
        {
            0xFD5170220D051153ULL, 0x270FC71EF919D961ULL, 0x06AB7530993456F4ULL, 0x2415CE4A0B6667A0ULL, 
            0x8E6B55426FA49873ULL, 0xA3C93F13ECC0FFDBULL, 0xCD75EB196E112CC1ULL, 0x46E0B4F6D478A7B2ULL, 
            0xB87295D3EB152AE2ULL, 0x748E6F2B2B047EBCULL, 0x72448131D127D05CULL, 0x9A093443A5960613ULL, 
            0x0C0F8B7EB034E146ULL, 0x417007476D13B86DULL, 0xF6C40A9D1BF4416EULL, 0xF819854264067826ULL, 
            0x7C4D0D3C0D08C836ULL, 0xC6A6A7679A38CEE2ULL, 0x942D0B5E498456E2ULL, 0xACA01282BD4BEAC4ULL, 
            0x71250B2545CD6BE6ULL, 0x3ADF3FD28110AAF2ULL, 0x55E7A40D289B7E68ULL, 0x1634F692D58FA661ULL, 
            0x841D0500B96DA053ULL, 0x644D4D42FA9B562FULL, 0xA92E943D8D33B7B4ULL, 0xBD0A8E0B4EF3BE76ULL, 
            0x20CBB49E8AD85825ULL, 0xC4762414507149BEULL, 0xE289B5170BF40F19ULL, 0x47F92766373BDB9BULL
        },
        {
            0x8E3D339B95E000A9ULL, 0xA5E5231BF91A5170ULL, 0xB7B5A41B47A4FD0DULL, 0x3B57E26271F3F9B8ULL, 
            0x3850002748684AE4ULL, 0xF4BBFB338FE8795EULL, 0x80745FC1D25B0DCAULL, 0xC535848E85AA82F1ULL, 
            0x53EBCEAD0CE9B2D7ULL, 0x57D676A2CFB23A73ULL, 0x625E4A551EBE0E50ULL, 0xDB49C22DA76C2EB3ULL, 
            0x214EAE8630683C60ULL, 0x9390FC57C66DAA93ULL, 0xF1CBA5122647BA58ULL, 0x451060D73D095E69ULL, 
            0x4C304AF170A99169ULL, 0x8887D3AC1D39FFD3ULL, 0x20AECCFABFDFFB23ULL, 0x95811D5BB3C1E1FBULL, 
            0xE51616A8AB1BB6F1ULL, 0x4DE95E4584EE74FDULL, 0xFF7786E64B56D0FDULL, 0x8813FA7630CAB87EULL, 
            0xF75BC43A5030873EULL, 0xD92BF06140BC5ADFULL, 0xFC1F47C31354C965ULL, 0x9A3F874E305EB42EULL, 
            0x7BDD9FBB3B324B30ULL, 0x4645A0E2F38A6B42ULL, 0x6AE2630029473B68ULL, 0x60E5EB1E82FD1855ULL
        },
        {
            0x273DCDD8FBB5CA96ULL, 0x32807F26DD5D1A89ULL, 0xD0EB264C312BF951ULL, 0x24AF84D2992A3423ULL, 
            0x66C5FA8EAE4EC7FAULL, 0xD48A8FFB6889D79EULL, 0xDCE82287D18EB3A3ULL, 0xFC4274A2499DF1E2ULL, 
            0x992E3083B1B8E1E0ULL, 0x600A403519784A0AULL, 0x97DA45ECBF471358ULL, 0xF6A3EAC7A3288163ULL, 
            0x64912AB3791CF126ULL, 0x6DAFDFFB67CD8CC3ULL, 0xCF80BB288DE7AB91ULL, 0x33853D401F81EAFFULL, 
            0x3D2AAF64E9EA5241ULL, 0xF0F68206C4FB68A9ULL, 0x81B9AF1F367D40DEULL, 0xAD41A3198375992FULL, 
            0x56189C8FA0E10294ULL, 0x310444C290201942ULL, 0x6EDFECD686880FB1ULL, 0x6A18025416963240ULL, 
            0x4780691359E645FDULL, 0x65F28540056186F6ULL, 0x2CC97BF2C45D899BULL, 0x2400DF6D22A54F17ULL, 
            0xE489A185B75164D2ULL, 0xBD02594E55712317ULL, 0xB11BEEC7EA20C647ULL, 0x41FA5882D6B943E4ULL
        },
        {
            0xF81B0C721AF54F9DULL, 0xE923AEA911EB71D2ULL, 0x5855066F298E3DFBULL, 0xE0D43062C0F8C753ULL, 
            0xE312BD41E9F7D430ULL, 0x3266BA4F2AC1397AULL, 0xC9726F189A7AD691ULL, 0xE693AFA1AA3333ACULL, 
            0x5E6BCE3EE12C126BULL, 0x971C0A6B1657542EULL, 0x63504EBA33F7D56DULL, 0xE50E7FDFDE6402A8ULL, 
            0xCFD18DFC196842B5ULL, 0x0FC6E1BE6C796780ULL, 0xC49FD1A24EDD2488ULL, 0x688C81F36DED8D37ULL, 
            0x1312BC3CB22546CCULL, 0x5948E90890A0B162ULL, 0x65675592B50C3C7BULL, 0x6E340CA7F1F9C3EDULL, 
            0x2FDB3AFD28A9226CULL, 0x11788494AA96D4ABULL, 0x67910FB1F690663DULL, 0x4CD4AA18CAA4FDF2ULL, 
            0x45ADCF053A762531ULL, 0x191AE709F00C4D53ULL, 0xB6AFB69BD5FC2091ULL, 0x6668372C29B924EDULL, 
            0xDCF46CEB865FBF3FULL, 0x800B3F60203BD10FULL, 0x109AF3D1065BD7E8ULL, 0xDF94F0DC1838782FULL
        },
        {
            0xDB07D634A44798E6ULL, 0x31BE98532276A297ULL, 0xEF994F7482ED3A28ULL, 0x93F8497EBAC20FCFULL, 
            0xADDB0B35DE5D3E20ULL, 0xBAA928CB1123F405ULL, 0xEDBF8ABBBCEA5D70ULL, 0x4CD47F965C396B13ULL, 
            0x416713AFEFD9177DULL, 0x5FD1BE2220BA5197ULL, 0x7BDF7B1BBD4C9688ULL, 0x0E3F97131245C329ULL, 
            0xCF8982C3E492468FULL, 0x537140398E781AD5ULL, 0xBB0139C1D0E7AE4FULL, 0x9A8C210694E823C6ULL, 
            0x73ED1A075D586FBCULL, 0xB700E9E3A822C1A7ULL, 0x04B7CA11EA64F8E4ULL, 0x011360103E5E0AC6ULL, 
            0x495D37F136058AEEULL, 0x7ACDD003195FBC00ULL, 0x0123074FEE17FC93ULL, 0x05DC3A0F90096DAAULL, 
            0x542EE680AC6D8CFEULL, 0x51F937AF12435E68ULL, 0x5251E8D52A837AB7ULL, 0x8BC2A595ED8E4827ULL, 
            0xB0233982BCC84524ULL, 0xE19BEED5EFBDFD85ULL, 0x7334FD407D63ED5DULL, 0x44BA75A77CB26229ULL
        },
        {
            0x12C64916DF30F90EULL, 0x22EBBA70304CF52BULL, 0x485318498B30EDE9ULL, 0x73DCBBAD1CE2F343ULL, 
            0xAD0D371C43A8B203ULL, 0x00FC43FA9874BE71ULL, 0x94BB3E569161DAEDULL, 0x700EADE3FCFC96E2ULL, 
            0x060F880683BFE6FEULL, 0x826896DC7301E7E7ULL, 0x0099408F169037BEULL, 0x99A54C180AC29B66ULL, 
            0xB02FB5B649D8778BULL, 0x3CD5551D65796ECFULL, 0x822489E9EBB649FEULL, 0x989E975900246A64ULL, 
            0x5E75DA4247EBEE2CULL, 0xC580745261D35EFEULL, 0x9E17B3C2CB368924ULL, 0x2BADF8076A55540BULL, 
            0xCC149A370F4FD71CULL, 0xDECC36541E02F118ULL, 0x2E690FB3CE28AFA0ULL, 0x37FE72C29A145A1EULL, 
            0xDF6319620967EC4BULL, 0xA81CD0618D0F87D6ULL, 0xD200F3D84D8DB07CULL, 0x5AE8AA0C8E1B29BAULL, 
            0x75FF76D73A2AA092ULL, 0x4CAFE84BBDB043A4ULL, 0xE718D06D743C97B8ULL, 0x1F6F4425FC381EBDULL
        }
    },
    {
        {
            0x6502E3FCE5B87BADULL, 0x5B38C231F27F618CULL, 0xF5A3F3A2F0D0CDB5ULL, 0x1B2B7E2F69FFCF3FULL, 
            0x2C990F434D832D19ULL, 0xA0319E44C3CE5F82ULL, 0x6B986F624A203D9CULL, 0xD4C5AF09897F14FDULL, 
            0xCC14A9E2F4BAD2F6ULL, 0x2952848C58C0E5CDULL, 0xE7F9FA2624D32EB9ULL, 0xC4D93ECC6C502738ULL, 
            0xC3E0E63E1A7638D3ULL, 0xDD092CE5DF015277ULL, 0x0759CDF31518BECDULL, 0x9736E041DB3C2774ULL, 
            0x4F8998A459192788ULL, 0x3A1F51BE3E5CB9B7ULL, 0x6689A7C0B866B0FBULL, 0xBBED31AB6C7D587EULL, 
            0x71DBCC16C021FA94ULL, 0x78C6DAC4F10B8EC7ULL, 0x97C7DC5B34620B58ULL, 0xD0979B4487F8FFC2ULL, 
            0xF33B402818C54CA5ULL, 0xCAE4B7F45AF0CBB2ULL, 0xFCA3D4A3DEE1C423ULL, 0x3412B2D0A63BE9CAULL, 
            0x5E77AEC818F9FEC1ULL, 0x387CBD90B14C7EA6ULL, 0x89CC5EED3254B492ULL, 0xA47996CE46944B0FULL
        },
        {
            0xF7574CAEDFDE8266ULL, 0x0C82838B3863C373ULL, 0x3B7512C1E3552F39ULL, 0xA6397DC90798E456ULL, 
            0xD2C2938D1D1D6457ULL, 0x122BEC21B2A0408BULL, 0x7E0338B37EA66EEDULL, 0xD4C9428E6CA6A217ULL, 
            0x3861218D37F1FC49ULL, 0x85A40DEBF32B2653ULL, 0x5297F806CC8CEC27ULL, 0xFAFA021A3D089A9AULL, 
            0x537F63A1EE805FF0ULL, 0x2BA08EF95E9A6EB9ULL, 0xD97CA151F85C0FEAULL, 0x24509D57480C7C3AULL, 
            0xEBF01F703CE93573ULL, 0x5392A9D08774FFF9ULL, 0x6726E6B0EE99FCEAULL, 0x37B947E19C842584ULL, 
            0xF68466121BDFF937ULL, 0xE4A49161C2C9D70EULL, 0x607DC300F40EABFAULL, 0x96DC3273A48FE4F5ULL, 
            0xD565D3E241A9999EULL, 0x1867CC3D30135A1EULL, 0x530A7408CF22923BULL, 0x605DD58F895409A0ULL, 
            0xFEFADA6CA9F957F4ULL, 0x7E4D1D46A1458619ULL, 0x97509B9175ABBF78ULL, 0xE87652AA46517344ULL
        },
        {
            0xACEEAFCB0065938EULL, 0xBD3DEEDF65046567ULL, 0xC1E9118EB7869622ULL, 0xFD89C6858CC75F8CULL, 
            0xFCBE1000FE4C6003ULL, 0x06BE1D214E524C82ULL, 0xA034A8FE17612414ULL, 0x83354041B919523FULL, 
            0xAE7D1C487769EA67ULL, 0xE4EEC245CBD01317ULL, 0x52CF033B3CF72AAFULL, 0xB995F7563E0CDC30ULL, 
            0x0393698C767DBDA6ULL, 0x51266200D3FEBC9DULL, 0xF08CE374ADA7C4B6ULL, 0xBD9F2D150224AC4AULL, 
            0x9219F704007571C1ULL, 0x4F216D918CC5289EULL, 0x621D79C20C302818ULL, 0x0EAA8BD179DF9F6BULL, 
            0x2ABBD542591D9C94ULL, 0xB644DEA0D0E4DD8DULL, 0xCC9F0D33DAED18FEULL, 0x875476EE958C9E2BULL, 
            0xCDC51186C672F388ULL, 0x9B6CCC45495516ADULL, 0x760BBF3D36C71E30ULL, 0x19B1C4CF71F364A5ULL, 
            0xA1634F5A6C9C49DBULL, 0x4FE83001319337E7ULL, 0x9F7D0D368DA41DD2ULL, 0xDE0825D773DCCA8EULL
        },
        {
            0x7F2FBACF618D34D6ULL, 0xE4E01B9D1C3B9D3DULL, 0xC7C1A164A73A67E5ULL, 0x7329321EA045A811ULL, 
            0x5E8DFF5D66497033ULL, 0x201E9F3A44F3ACA1ULL, 0xEA105550C4DB94A9ULL, 0xB80C82DB3515E3E2ULL, 
            0xDCB556683F8FF093ULL, 0x5B8805248A5BE2D4ULL, 0xF9C98A5E14DAAB1AULL, 0x863002C945895715ULL, 
            0xCFD849C260FD1693ULL, 0xFC59F4A83CCD1093ULL, 0x8B6EAC3699B5D2D8ULL, 0x6B60036A93109C8BULL, 
            0x9BC93B6C6E074705ULL, 0xB7F06CE08DF29A34ULL, 0x83D57B065CFF9CFFULL, 0x6AD4B3FF3B6DE710ULL, 
            0x5D86C8FDDD595D6CULL, 0x23E9C8847447FCC3ULL, 0x441EDD687ADC3D30ULL, 0x168C6B2250CDDE18ULL, 
            0x0641B6F5CAFF81F5ULL, 0x654041C310175433ULL, 0xA8E2CAA44125A705ULL, 0x39A740E393CB8CD1ULL, 
            0x30607D6EF497B030ULL, 0xBAE1218DCFFE2588ULL, 0x99328968BA46E2DAULL, 0xC6C473D4A7714FFAULL
        },
        {
            0x1880B1A8CFA9123FULL, 0xA65E2410C89D0901ULL, 0xDF5EE384A071382EULL, 0xB9457BB9F6EBA511ULL, 
            0xBAAED350129C7220ULL, 0xCB4089B48997C74AULL, 0x1319C003266E0D08ULL, 0xAED460F5B53FC570ULL, 
            0xB91E89ED5375EAB6ULL, 0x430D4F4082E48AD9ULL, 0xB1DF5928671DB0CBULL, 0xB57B3D03B9B277EBULL, 
            0x04A21A66C1C37AF8ULL, 0xF6E36EA07C713979ULL, 0x946F0041FDAFBDEFULL, 0xC6050E3BB6A6F7FAULL, 
            0xD077121D9DECB300ULL, 0xAAAC63618A35E274ULL, 0xE551FF835571097BULL, 0x7DE45053D0E508D9ULL, 
            0xD0140760AD3E0B93ULL, 0xBC2BC49D7723243FULL, 0x94AF72CD3AB45261ULL, 0x6B1F8E3D276F6FA0ULL, 
            0x8CC1687143BFB65EULL, 0x78943EA10E99727FULL, 0x7C6EFA81F9372653ULL, 0x562883CD7BC3B7ACULL, 
            0x3C7E1D577AAC4E78ULL, 0xA75872B8FA2ED173ULL, 0x143088F9780286BBULL, 0x4AD3E443644AD4EEULL
        },
        {
            0x644F6386D5D0E4BFULL, 0xE12B000FAE245664ULL, 0x3C540BB3F09C6094ULL, 0x34840E97C3EB784CULL, 
            0x03551A403E98CF0EULL, 0x035DF521D641B73FULL, 0x596E066718E3FF91ULL, 0x27643575ED9A3238ULL, 
            0x9B42501AC3CA3D1FULL, 0xD3E5639E1EA5A708ULL, 0x8307A23207F677F5ULL, 0xB1D5B726DCC63E98ULL, 
            0x5FF659AD3B0F6F14ULL, 0xB7107452498F55C2ULL, 0x262EB57D38031807ULL, 0x48D1191374C86816ULL, 
            0xF03743A414509D70ULL, 0xC497C9A463A8C5B3ULL, 0xD61857BC5640020DULL, 0xB79E13461D56CD86ULL, 
            0xADF2B784EF67AD54ULL, 0x7BB3060492EB2457ULL, 0x0959934C79C61C30ULL, 0xA53B821EA7665BFAULL, 
            0x21EBFB6ADF77E1B6ULL, 0x711F286F3F3E4B81ULL, 0x27D552FFF2448C63ULL, 0x15A240423C75A965ULL, 
            0xDE67C929468CD98FULL, 0xFCABD808D492B015ULL, 0x402807FD6BAA46C3ULL, 0x53C278B8DB8704AAULL
        }
    },
    {
        {
            0x25429D975ECB2697ULL, 0x65B8BE4A3C8868BFULL, 0x3465E1C2DFD8CAA1ULL, 0x7E2D04A97A082AA3ULL, 
            0x73B2B8BC10304CDAULL, 0xCC1C96306CBEDC8CULL, 0x3208BFB0370C08CCULL, 0x440C1F665A5EFD77ULL, 
            0x4EBFFC9BB136D2B4ULL, 0x09667E9EA9ADCEF8ULL, 0xBAE66036C4C27F41ULL, 0x0C8D262B77CA11BDULL, 
            0xFC9A7DD2217D53E4ULL, 0x6BAE28F5F73E97B0ULL, 0x43475D537C79521AULL, 0x2E7483772462405AULL, 
            0x00DF8EC99222AD42ULL, 0x00B87ECF0AEA2EADULL, 0x4C343BB97A07F6F9ULL, 0x13A3C4A6851B5502ULL, 
            0x9871651A9045CF3BULL, 0x28C07000F4D90D65ULL, 0x47E5210C8BD633FCULL, 0xAF06D2C6AF58BE03ULL, 
            0x75A504A1BF881F0EULL, 0x1A6E7D23B0E55C09ULL, 0xA50530E560FA598FULL, 0xBE61B0FFFAA95EBDULL, 
            0x249189BFAFBDA605ULL, 0x75B78D372A615BC6ULL, 0x5D9924C199989395ULL, 0x2B8FE88EA3ADDAEEULL
        },
        {
            0x60CEC862B08A7489ULL, 0x201D0BE1CCB0D504ULL, 0x0DF3DA859AD43E22ULL, 0xAB4EAC57CA20016EULL, 
            0xDE751850915ADCA0ULL, 0x82D38F8814913DA7ULL, 0x5933B7A4D5D05F82ULL, 0x2E25005B631B8516ULL, 
            0xEFD7B1A20CE966F7ULL, 0x5467720E51030EEFULL, 0x31618B5202C50C07ULL, 0x49EB74E763CCD942ULL, 
            0xB5B35A2AD556BD29ULL, 0x74420AB352A35DD8ULL, 0x2AB21C27349F480DULL, 0xC0413B6D259137B8ULL, 
            0xEFEFCAC4DFC8ED07ULL, 0x74233F83A315FC23ULL, 0xE7CBB2FC24CCFBC0ULL, 0xC944A6C1A7B0F8D8ULL, 
            0x5164923A5769B990ULL, 0x4F4F1408DBCF5631ULL, 0x7C29BCC2D3ECA9DFULL, 0xCAC27E894DFBAB0EULL, 
            0xB1250CDB744EF3EFULL, 0xD3088C1C8069569DULL, 0x438727B7D3A795C2ULL, 0x11EC5C6D5B3213D0ULL, 
            0xE7E813C50AD67CDFULL, 0x61D8191D96C9D87DULL, 0xDC4AEF207EDE922AULL, 0xC7F1F40D9DEC443BULL
        },
        {
            0xD1C9E0F85069C5A1ULL, 0x49F5F7A0A4A3F68BULL, 0x816E33A6C791FF05ULL, 0x3451F0249093E501ULL, 
            0xA3A6B3E19D9E5D40ULL, 0x6D411932294A157BULL, 0xC1BB4BC84678D503ULL, 0x784C2ABF8CD86439ULL, 
            0x33CEFB1989D23BCDULL, 0xD1E85F97AC2AD467ULL, 0xCB6D375FF62E6133ULL, 0x8CB9B488600DB639ULL, 
            0x0C0703646827B4F8ULL, 0x8A1DBAD0B4845A08ULL, 0x3C7C1094C7784931ULL, 0x0DEC88B2ABAAE1C7ULL, 
            0x7B5D52995429F9DAULL, 0x106485455F6667E2ULL, 0x1B753DAD15B3A2B6ULL, 0x553AA9FF4456D743ULL, 
            0xBE3438E26EC997FBULL, 0xD90D79876F0537E5ULL, 0xE593B2583B307D4FULL, 0xC100CA3B62420B29ULL, 
            0x63E7B9DFD84612D4ULL, 0x418781E629113F9BULL, 0xBBDE789726F69FF7ULL, 0x957143E82D0D5802ULL, 
            0x70C0931D5D2F26CFULL, 0x54EA23AA411EAAAAULL, 0x872C0841243E379BULL, 0xD8C24EDE0F76AC86ULL
        },
        {
            0x38CA6924DF550973ULL, 0xEA0FCA50DEE08F4EULL, 0x123BE35F302E3B4BULL, 0x5D03F5543B8FAB23ULL, 
            0xF49DDAE3B0E69C12ULL, 0xE3300DC9495A5D92ULL, 0x7020483B17314EA0ULL, 0xF899D1779D5F07FEULL, 
            0x65CBFC32C2A1BD4EULL, 0x033D9C2B5BE36C7EULL, 0xF722A31776312224ULL, 0x480648C629D1CCA9ULL, 
            0x1C87C5E47BEA5971ULL, 0x956312C67E0E9B30ULL, 0x97F42CF89EC6B9D1ULL, 0x733C5E13B181F625ULL, 
            0x98FC6850662DF9FAULL, 0x04BE5D8858E552EDULL, 0x10CF4486AFD8EDA1ULL, 0x462CCCFCF20B2EB6ULL, 
            0x26C25809364C0770ULL, 0x98EC7A6452222EF4ULL, 0xECCC09440EB02E0AULL, 0xA424DFE07A0EE76EULL, 
            0x62C3D79ED45469A8ULL, 0x435EBF609721E562ULL, 0xD880065D73E49893ULL, 0xD13889D854351911ULL, 
            0xD133CC93364F0022ULL, 0x10D13A5A05660A43ULL, 0x264A4767BA1D66C8ULL, 0xE4A8467E85DE22CCULL
        },
        {
            0xCFCC175D2E321731ULL, 0x28C4889D1D3FD214ULL, 0x58EE712F5B8081FEULL, 0x5322ECCA1423EF8DULL, 
            0x15FE0B777906AFB5ULL, 0x65DC727DA2EB4986ULL, 0xAAF3A19CF8D84286ULL, 0x2EFE5FA873985420ULL, 
            0x1B93257CB70E39F3ULL, 0xC6473897FFE98025ULL, 0x3BAF48BC34594EC2ULL, 0x1EB8A6AB8F78E7F3ULL, 
            0x2451B3D86E3F64F1ULL, 0xF3A03392E44846DEULL, 0xBDA029A9D143B263ULL, 0x7BAB250136078088ULL, 
            0x9A859792306B75C3ULL, 0x41AE9CDC2D560EEFULL, 0xAB81B88D3CABC618ULL, 0x107A9CDDEE3F990BULL, 
            0x64090338F39BC893ULL, 0x0CF51CBFA6D2E852ULL, 0x6F00544ED978C667ULL, 0xEB6EE37088212EE2ULL, 
            0xF9F1569323F35F4AULL, 0x3F174E2E74A9C8AFULL, 0xA7F39BA8CB8BAEE3ULL, 0x6B31A1B09F99A597ULL, 
            0x6FAC2062CB57184DULL, 0x43F47093BE55477BULL, 0xFF71EAC3F1D7A891ULL, 0x5A6EBDDCFC27C227ULL
        },
        {
            0x2734130B47F637E0ULL, 0x38DFC1E1858F708DULL, 0x8D0A95B4067C6431ULL, 0x51A5912F3A834EF2ULL, 
            0xE9F111EECF33AA81ULL, 0xDC21CB64954F5D4CULL, 0xEB8FB47C6FC2D7C0ULL, 0xBDEDCCA6A3438BE2ULL, 
            0x5D156A3A0CAFDA97ULL, 0x2AEA97A78B63EC9DULL, 0xEA8C9602AEDCC71AULL, 0xDA0C7D08AF9A5CBAULL, 
            0xAACE87C8F833D480ULL, 0x9B84599F34874A11ULL, 0x0B3B3F209EB191B2ULL, 0x67C7DEED6ED28CE6ULL, 
            0x8411C8B8C55864D9ULL, 0x2858626A53754EDFULL, 0x99C025FF825835BAULL, 0x86C75097815DA7B4ULL, 
            0xD522AC34E41E82EDULL, 0xBBCC770FA4FB6404ULL, 0x81E2B7EE6CA649FBULL, 0xD75F54D136C3E583ULL, 
            0x75CD4EF46D57796DULL, 0x9700B10032561EABULL, 0xF6DC221BF8745E80ULL, 0x3D6CBBFA538765EBULL, 
            0x06DBD9F47CC02BDFULL, 0x0F0D4BF00C9B0EC8ULL, 0x11550747D5D838D0ULL, 0xF642CBF536CDEE8BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseHConstants = {
    0x38352E7993653D33ULL,
    0x79B1FA4EA25D6454ULL,
    0x1AC9C87C690138D4ULL,
    0x38352E7993653D33ULL,
    0x79B1FA4EA25D6454ULL,
    0x1AC9C87C690138D4ULL,
    0x65A64249305442ABULL,
    0x8D44A9C61F07C89AULL,
    0x1B,
    0xDF,
    0x78,
    0xC1,
    0xA3,
    0xA9,
    0xF7,
    0x99
};

