#include "TwistExpander_Altair.hpp"
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

TwistExpander_Altair::TwistExpander_Altair()
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

void TwistExpander_Altair::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB38231EB829E9B00ULL; std::uint64_t aIngress = 0xED7C135D48251407ULL; std::uint64_t aCarry = 0xDFF0E0C1EE9A2537ULL;

    std::uint64_t aWandererA = 0x92588796174525F2ULL; std::uint64_t aWandererB = 0xF448A2CCAAB5505DULL; std::uint64_t aWandererC = 0xC196419065B20405ULL; std::uint64_t aWandererD = 0x9D2A05067A1AD01FULL;
    std::uint64_t aWandererE = 0xB87A7A05C5539B25ULL; std::uint64_t aWandererF = 0x906BC17389BC7D9CULL; std::uint64_t aWandererG = 0x90C31A01B72EA320ULL; std::uint64_t aWandererH = 0xCF965D29955F4495ULL;
    std::uint64_t aWandererI = 0x9E76D6E73AB9114FULL; std::uint64_t aWandererJ = 0xE56EBB216E27C2B4ULL; std::uint64_t aWandererK = 0xE25171ADEF00034DULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14081077945360326588U;
        aCarry = 10795097220591389998U;
        aWandererA = 16100364356447369727U;
        aWandererB = 9623243869475188254U;
        aWandererC = 16990368464417761817U;
        aWandererD = 16850911973743975032U;
        aWandererE = 11897285931028909249U;
        aWandererF = 12401766869656033971U;
        aWandererG = 12766351129000010775U;
        aWandererH = 15876547113967593025U;
        aWandererI = 11497373370345709932U;
        aWandererJ = 14047049041069661867U;
        aWandererK = 9655852102230858493U;
    TwistExpander_Altair_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Altair::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x86BF91B443F3EEF9ULL; std::uint64_t aIngress = 0xAA26103B6182E862ULL; std::uint64_t aCarry = 0xFA9F8CC0BDB3B35AULL;

    std::uint64_t aWandererA = 0xF3B1428A74DBFE4AULL; std::uint64_t aWandererB = 0xD3700FDB290F10ECULL; std::uint64_t aWandererC = 0xFCFB5C35AFDDE09AULL; std::uint64_t aWandererD = 0xE2155AB9357A6678ULL;
    std::uint64_t aWandererE = 0x90B63886C3F8F64FULL; std::uint64_t aWandererF = 0xE657442F5420DEB3ULL; std::uint64_t aWandererG = 0xB70067DF57547CCDULL; std::uint64_t aWandererH = 0xAA54F7315E9E6BFFULL;
    std::uint64_t aWandererI = 0xA5EB9176D04D998EULL; std::uint64_t aWandererJ = 0xD5C7CF1286343444ULL; std::uint64_t aWandererK = 0xC616E53C6B6DE117ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16163718377372899324U;
        aCarry = 10461195775713858054U;
        aWandererA = 14956527500270779311U;
        aWandererB = 15187989327233664554U;
        aWandererC = 11712451760505809695U;
        aWandererD = 12047524289821921323U;
        aWandererE = 12368484718730765313U;
        aWandererF = 17144516683175642071U;
        aWandererG = 17336746508501595645U;
        aWandererH = 9717532391382808599U;
        aWandererI = 12768539232539906617U;
        aWandererJ = 12554631810404004628U;
        aWandererK = 10203534895536215005U;
    TwistExpander_Altair_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Altair::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x88886089580F6514ULL;
    std::uint64_t aIngress = 0x876F3B7C720A2D12ULL;
    std::uint64_t aCarry = 0x908227D061495FA3ULL;

    std::uint64_t aWandererA = 0xDB08205D5060C5B4ULL;
    std::uint64_t aWandererB = 0xE5A6BF0CFDD12168ULL;
    std::uint64_t aWandererC = 0xD2A28E22C115DC7BULL;
    std::uint64_t aWandererD = 0xD2F845AC2BE554CDULL;
    std::uint64_t aWandererE = 0xF49C69DC6F1AECF5ULL;
    std::uint64_t aWandererF = 0xB0F35442A0ECD666ULL;
    std::uint64_t aWandererG = 0x90306B85C2A145D2ULL;
    std::uint64_t aWandererH = 0xD8A14DD907DF585BULL;
    std::uint64_t aWandererI = 0xC60286F04FB43083ULL;
    std::uint64_t aWandererJ = 0x8D034F738353BF97ULL;
    std::uint64_t aWandererK = 0xFBEF38CEBA559ADFULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneA, 0);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneA, 4);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    TwistExpander_Altair_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
    TwistExpander_Altair_Arx::Seed_I(pWorkSpace,
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

        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Altair_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 7 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1907 / 1984 (96.12%)
// Total distance from earlier candidates: 11500
void TwistExpander_Altair::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 774U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1152U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 6U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 214U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 22U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 815U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 348U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 152U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1799U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1905U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1537U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1950U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 61U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 903U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 294U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 659U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 458U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1209U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1859U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1841U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1512U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 344U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1349U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1806U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 427U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1960U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 870U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1882U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1378U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1729U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1921U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1891U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 830U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1395U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 573U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 844U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1666U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1901U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2004U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2021U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1610U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1320U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1480U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 856U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 179U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1375U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1500U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1791U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 324U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 491U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1504U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1444U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1890U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1619U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1774U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1103U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 772U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 163U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1290U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1548U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1056U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1064U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 861U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 103U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1226U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1095U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 528U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1834U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1802U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 100U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1182U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1853U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 829U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1586U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 476U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 223U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1098U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 594U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1592U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1337U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1959U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1354U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1223U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1762U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1838U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 920U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 667U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1380U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1297U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1926U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1957U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 259U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 828U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1085U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 153U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1401U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1481U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 229U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 518U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 392U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 10U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 149U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 320U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1598U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 59U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 788U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1331U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 743U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 700U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1302U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 675U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1516U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1125U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 524U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 766U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 511U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1162U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 181U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1596U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Altair::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA02C3ADBB9FB99C3ULL; std::uint64_t aIngress = 0xD4D9F1104CD82AD7ULL; std::uint64_t aCarry = 0x924D185536B920DEULL;

    std::uint64_t aWandererA = 0xB08C66E9E384E806ULL; std::uint64_t aWandererB = 0xCE863ED9E69812B8ULL; std::uint64_t aWandererC = 0xE6573B59CE9806D8ULL; std::uint64_t aWandererD = 0xEC9C654B33808026ULL;
    std::uint64_t aWandererE = 0xF5A6D47DA06FA0DAULL; std::uint64_t aWandererF = 0xF7405E3E2651CDAAULL; std::uint64_t aWandererG = 0xA61CBE1EE27DC813ULL; std::uint64_t aWandererH = 0xBA07EF74583F6FB1ULL;
    std::uint64_t aWandererI = 0xAFA4DB972B82F19FULL; std::uint64_t aWandererJ = 0xED81F1452B072AEFULL; std::uint64_t aWandererK = 0x9419D1504A242D5EULL;

    // [seed]
        aPrevious = 11432689373067368001U;
        aCarry = 16119301469779848511U;
        aWandererA = 15887026436974271091U;
        aWandererB = 15382238849448301135U;
        aWandererC = 17690855629079492314U;
        aWandererD = 13112070557475352803U;
        aWandererE = 16327858179136940900U;
        aWandererF = 14051247355782603289U;
        aWandererG = 15020805228051478435U;
        aWandererH = 11064957834059432739U;
        aWandererI = 10551654830142562270U;
        aWandererJ = 10823151514343828821U;
        aWandererK = 11225764151844343826U;
    TwistExpander_Altair_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    TwistExpander_Altair_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 7 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3392; nearest pair: 494 / 674
void TwistExpander_Altair::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 570U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4651U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3096U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2468U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6679U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2344U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7514U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 888U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 166U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3361U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 392U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6730U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6144U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4854U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3513U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2916U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 261U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 249U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1926U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1625U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1004U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1636U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 824U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 972U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1898U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 923U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 595U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 932U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1079U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 791U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 413U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 95U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 634U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 926U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1901U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 7 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3387; nearest pair: 514 / 674
void TwistExpander_Altair::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6189U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4912U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2313U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5001U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3421U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4157U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6697U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 747U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 927U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3126U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7403U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3680U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4311U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6723U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 924U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 600U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1369U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1934U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 669U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 959U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 147U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1632U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1857U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 584U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 937U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 853U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 904U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 710U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 157U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 960U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 80U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1992U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1851U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 136U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Altair::kPhaseASalts = {
    {
        {
            0x75D8A80EBEA8A697ULL, 0x9351C3046642267BULL, 0xBC6B169677A1D60EULL, 0xE8E3533C89101FB0ULL, 
            0x0BEB4927F2816A17ULL, 0xCA0A2749986B3941ULL, 0xB20A1DA11940A4C6ULL, 0xE52029FBCC506D7EULL, 
            0x29DE223A82BF306FULL, 0xA82B66C3B8D620BAULL, 0x98B79EABB9E41890ULL, 0x8B6B7C51F435B52FULL, 
            0xE44D3EE8241928CEULL, 0x2DDE2E322C7680B8ULL, 0xCD9AB20EE74005ACULL, 0x99EED8238DCEC2C3ULL, 
            0x9E663D8130758350ULL, 0x5D6F118D204303D4ULL, 0xFDC545FFB449D6A6ULL, 0x6D55D13996C962D0ULL, 
            0x048FB8E8D4C9BA11ULL, 0x74E02C8F8A5381ABULL, 0x1B36AC22086B68F8ULL, 0x5920D001936A04B2ULL, 
            0x68C8B0CD4B8935C9ULL, 0xEEC69453783815A1ULL, 0x265836200DDECDA8ULL, 0xD06AE08210D755DEULL, 
            0xAC0FC4E22F34066FULL, 0x7126D68145D8ABBBULL, 0xD1E4CD76367D839EULL, 0xD36ADFF51E6C2A62ULL
        },
        {
            0x5DD6ADEFFDFA0FDAULL, 0xD776CCC8305F1893ULL, 0x5E377E3ACB43A083ULL, 0xC595ED39963FB7DBULL, 
            0x1919FCC310A90A8BULL, 0x50FFC5E8E0367DFEULL, 0x3902E9F64753C35CULL, 0x33C809F7A194E439ULL, 
            0x92E1B6D3047B4382ULL, 0x62377ACE26D03A3EULL, 0x07A3933975904355ULL, 0x965016165CC9300BULL, 
            0x55C32E6F93836328ULL, 0x60276A197B534A6DULL, 0x21EB8DFBEB3C1024ULL, 0xDD24A0FAF19273FEULL, 
            0xCE0D795A65C32001ULL, 0x1798FD0F30CDC1A8ULL, 0x8BECA6CC2DC79961ULL, 0x676898429759EDE2ULL, 
            0xC9988DA66AD97B36ULL, 0x6C80695D23FBBF8DULL, 0x700C387180245036ULL, 0x71D2551F4C20BAA5ULL, 
            0xE3C4BDC22E286B79ULL, 0xF17AC09A7FA15F72ULL, 0xD351D42F3B481C68ULL, 0x6E3626D0FE10273BULL, 
            0xB9F49D9E9265B23EULL, 0x22DA42F73704EFF6ULL, 0xC0DFE26C7BC29835ULL, 0xCECCF7BC3E6852F5ULL
        },
        {
            0x84D69B942F80FCFFULL, 0x06BFEC2292511C4EULL, 0x8AA3637E2D607BCFULL, 0x2154261D44E024E7ULL, 
            0x1AE39A822F745981ULL, 0x4CFF4063FAA6D6D6ULL, 0x91A7ADA47BE31141ULL, 0x4B025380351A5E17ULL, 
            0x687E6F77C83C5410ULL, 0x19F3292CB7709B4EULL, 0xDD681E864547396FULL, 0x9A934A8C3F0C216AULL, 
            0xC7C6E3272E6CC742ULL, 0x6FD8779223CB694AULL, 0x11C0F29969EE7988ULL, 0x5A32AF40618A32CBULL, 
            0xB090740F8E99BD1DULL, 0x648FE72E1D46F258ULL, 0x1DEF861040D9ABC8ULL, 0x19FF8338E614536AULL, 
            0x3E6218C5055ECA60ULL, 0x285DFB76CAA141D2ULL, 0x888634EDED0B8A55ULL, 0x4D27EB777BED57E2ULL, 
            0x12573DFA8640B531ULL, 0x2DEDD5BE6D15824DULL, 0x10AA1BEBF0EFDE21ULL, 0xD11C5FA88E373B6BULL, 
            0x879FCBFA250C0CDAULL, 0x3B1666391A88D503ULL, 0x13C84D605C8E9F7DULL, 0xFB0AD5D96E41D04AULL
        },
        {
            0x8AA5E82D6CA2F803ULL, 0xD0C165DB54CCB19AULL, 0x932A6ED487273974ULL, 0x6D1F7835A994C783ULL, 
            0x324C441C2FEB16D0ULL, 0xA0DF35D2A4F26998ULL, 0x4FCD56900DD09302ULL, 0x07E136BD36F0A27EULL, 
            0xB04383383E227FD2ULL, 0x2996CC0037065537ULL, 0x5D85FD20EEAC9BFAULL, 0xD763DE7005395D27ULL, 
            0x6EAA79A7A541AF7CULL, 0xD6E81BAEAD3CDCB5ULL, 0x8B1531ACD8CE5881ULL, 0x7F9E65A55166E29CULL, 
            0xAE49FAD469FC076FULL, 0x8D5AF52BFB03777CULL, 0x2F6BE278810877DDULL, 0x24ED9A9B3F1D9944ULL, 
            0x919D9590BC794DA2ULL, 0xAA39262202CC548EULL, 0x6BAF5752C86F1F38ULL, 0x6436B62BE6758C4DULL, 
            0xB6172DD72036FD57ULL, 0x485383BEA96350B0ULL, 0xC0989F5EECED4E5BULL, 0xF3A6E2B176ACED9DULL, 
            0x825B245526053B90ULL, 0xC23D151B23FC9B28ULL, 0x7E73E1BBE9B73ADCULL, 0x444A4478C597BCB6ULL
        },
        {
            0x603CE06477DF1872ULL, 0x6F865730D44D1E70ULL, 0xEF1A8C7F2DF5F869ULL, 0x13BAFEFD210DC359ULL, 
            0xAC0049DC594FCFA7ULL, 0x9C54DBF929E9B720ULL, 0x770DF378AE2F0957ULL, 0x028793E3F3A8E116ULL, 
            0xACB7CA498ED88D95ULL, 0x01534400C78A29F0ULL, 0xD30FA9EA11DD1C67ULL, 0xB774E3717016F5C4ULL, 
            0xC24081474BEAEEC1ULL, 0xFBD98DA1525ADE7AULL, 0x2B1F4B236A69BA07ULL, 0x732E04BDA787A271ULL, 
            0x32579B87DA1890E0ULL, 0x4C32A01CF3E377EDULL, 0x9C9527344895321CULL, 0xE34117953D67C7CEULL, 
            0x16A2ABFF8A3528FEULL, 0xC6F64FE585529628ULL, 0x2230F20C4B070E58ULL, 0x6C87B4F544AEB5F4ULL, 
            0x988A6CDA89AEA931ULL, 0xAD47FA288B14B118ULL, 0xBE39EB61ADBDCF47ULL, 0xD594886741C7820DULL, 
            0x1D148F42BE60FAD5ULL, 0x4674066098990D23ULL, 0x5A1298570BA33217ULL, 0xDAE9B845F0380430ULL
        },
        {
            0xD574E4152CE9B86FULL, 0x505842706DB83E4DULL, 0xDE6F08BBEBD12F56ULL, 0x3D682262233BFBC0ULL, 
            0xAF65631191AF352FULL, 0x53F6AA1B1D132EE8ULL, 0x82837DD55E3DAF79ULL, 0xC2E238F7DEF6B244ULL, 
            0xCF1815CEE4F8B6FEULL, 0x0F1C44DED8BA3AC0ULL, 0x1F085D852A094D09ULL, 0xA84C317745C155EEULL, 
            0xC903530D11B46795ULL, 0xFF6191E1CC893ADDULL, 0x934A4AD959A30C1CULL, 0x9B133CB0CF06A188ULL, 
            0x5754E5A8ABD2CD2BULL, 0xE9D5603C17202076ULL, 0xE55C18E254B9F4F8ULL, 0xE68C48D13F7835D2ULL, 
            0x4439B8D39D5F770CULL, 0x326F1A0CBF2B97D3ULL, 0x9A9EDFB04391B8DAULL, 0x7072E9786BD44ECEULL, 
            0x65445B9D6494217BULL, 0x0957EB7E9EA971DDULL, 0xFFC56BDA56051EE4ULL, 0x4699BCE031482E5FULL, 
            0x81A4259B7383886FULL, 0xD7FF210AC95A8D39ULL, 0x919C3E6B10CD760AULL, 0xBF90446A4C2DDADBULL
        }
    },
    {
        {
            0xF9E2F10C0F39B2EAULL, 0x529ABCAFA9F48D50ULL, 0x317FD1DB375545C7ULL, 0xE12DD2A667C77812ULL, 
            0x5543F4566F550410ULL, 0x94529E31559C839FULL, 0xBB6D6453DFF9ECF6ULL, 0x2B33C18666934146ULL, 
            0x31898AA24F7010E8ULL, 0x1E83CAE9D0F861F4ULL, 0x704D7B71234CCF6DULL, 0x1E5F24D0EEAB4B05ULL, 
            0x47E4D6B514DED5DEULL, 0x9C85FB55D5453268ULL, 0xD3FE89A5752BA9F8ULL, 0xE734B81676058A03ULL, 
            0xD2EF9881C45C37C6ULL, 0x26909678D4C00E69ULL, 0xC2E2C2378E14DC4DULL, 0xB964D60419286220ULL, 
            0xF354BEABB391D73DULL, 0xDD0FC752E47DE5A7ULL, 0xB398245ED2466F8FULL, 0xE7B91260A3F0D0F2ULL, 
            0x97472D6BE7580601ULL, 0x8CE8E28B1E74A415ULL, 0xD297CD1782875383ULL, 0x26C47928FC178E7BULL, 
            0xF379BA190D9E57B9ULL, 0x0E401784ABCD948CULL, 0x12EDD1B87F8D39FEULL, 0xFDFB39B0703FE085ULL
        },
        {
            0x078D989742E4E25EULL, 0xD6A1F29CF4A50851ULL, 0xD185C050AEDB4223ULL, 0x1D0B045F2D5DD7D2ULL, 
            0xF439D04C4BE7B9C7ULL, 0x3E04C0983C62AE34ULL, 0xC15173AD55806928ULL, 0x97FCCD21ED75541EULL, 
            0xD93F0089C808620AULL, 0xC3CEC485BDCE9C59ULL, 0x8FCF030F9246A7A0ULL, 0xE81F43DD95A285C1ULL, 
            0x39FFBEF021716E38ULL, 0x041F85533CCBA146ULL, 0xE676CC048D49416AULL, 0x9FECE783BA459B39ULL, 
            0xB70DA2493D5C8F97ULL, 0x8A663DEBEC2346DEULL, 0x0173FD0C99EFE9EEULL, 0x1D7881CAB245AA59ULL, 
            0x2001D3C66C22F072ULL, 0x4B10AB2309F68052ULL, 0xA381959E4AC6CA66ULL, 0xA8DF8F49A51C0B4AULL, 
            0xEF73788E630B22B1ULL, 0xAA0501E25C6D7450ULL, 0x011528811C880DBEULL, 0xD4215E6FE3DEDB15ULL, 
            0x05C0DC37B0B60401ULL, 0x64EE2065FD3671B0ULL, 0x77D874D04AA7B4B1ULL, 0x801E212E3A5425DAULL
        },
        {
            0x4B769AD5D5593976ULL, 0x0B0E987FA935FCD6ULL, 0x15AE08884554797EULL, 0x1A0D19B0132843B2ULL, 
            0xA2D3EA6C409A8949ULL, 0xADA4D156AA94CC54ULL, 0x89F4F55CCAE7958AULL, 0x04ABDFF55726E599ULL, 
            0x776781E9CB0F9E11ULL, 0x7BF3029984AF560CULL, 0xC1726E3776C19378ULL, 0xF0B77C7463E973C4ULL, 
            0x75649B55E4257907ULL, 0xE1DF3A8B955A74C2ULL, 0xD6DF3A088BE773DEULL, 0x08EB65B1BAA788E6ULL, 
            0x0743E284540F8520ULL, 0x3805346322C0C7FDULL, 0xFFA441C8C8591E65ULL, 0x6EF742DB1A7C139DULL, 
            0x92C2C7214290247CULL, 0xEFA865DB051974EFULL, 0xA6975FC10D3894BAULL, 0x1C159BD94C63D323ULL, 
            0xDEFE34DE65ADCD64ULL, 0x15F6820E2BCAAB3BULL, 0xA61671BFFC6885A6ULL, 0x28029E7B6A2EAFBCULL, 
            0x6D9A99DEC71A9DAAULL, 0x47D22FCBFBCD6ECFULL, 0xC38914794DE8A45DULL, 0x224C15C796B0E0C1ULL
        },
        {
            0x179BBBC7BB9F530FULL, 0x3E71328B9B0034D7ULL, 0x30650D6AD34D4446ULL, 0x0F9621C15D069943ULL, 
            0x0519BAC6FAE670DEULL, 0xD39CA5C2CAE393CDULL, 0xBAA299E1DB9E99A2ULL, 0x0CE9CA7224CD18DFULL, 
            0xAF119148086F292CULL, 0x9B5FC358328F53B8ULL, 0x3808690DEAA91E8BULL, 0x86AC9826B50DA300ULL, 
            0x28ADA619F7EB8EA8ULL, 0x38CA5BAAB9641340ULL, 0x86C678C72DF76195ULL, 0xE73F7C82BE95D614ULL, 
            0xB022AA66BF0A1B7AULL, 0x129AD0730CE54CDCULL, 0xA099C181D55AEDB5ULL, 0x45C61EDAF4EF01ACULL, 
            0xAC7DD04D3529F739ULL, 0x326884FF7B9D50EBULL, 0xDEF753FBE0127246ULL, 0x16412D5191DA101FULL, 
            0xDF32BB5E53CE3EF1ULL, 0x9304F5C1642740D0ULL, 0xD06FC445DEF68D9BULL, 0xA42FA88D085E743AULL, 
            0x8BEC0736BC60F6B1ULL, 0xDF871B89940B0555ULL, 0xF70180B22DEF61B6ULL, 0x29D6BE24666C6D22ULL
        },
        {
            0xF50EE151C5F1665EULL, 0x63EBAA35698ADAB3ULL, 0xA828D9FC5C204452ULL, 0x3D17DC5954240F5CULL, 
            0x884562F46D33611FULL, 0xE716027E14DB1B87ULL, 0x42B4C5142A524583ULL, 0x68414C4F49B56A4DULL, 
            0x9945D01B90D0D5A5ULL, 0xB74B4DB1E960F8B0ULL, 0x4BA8EFBCC9A48ED5ULL, 0x344D8D3540C6C42FULL, 
            0xCA6D2B945DAB5C3FULL, 0x75EEB6D035BE8CACULL, 0x5AF6F00EA1530C47ULL, 0x59E5B9B49E0A2841ULL, 
            0x14242EC11216F18FULL, 0x5D79B01B201D52CDULL, 0x4A79AE8B7EA4C8B9ULL, 0xC81BB466AF588C4DULL, 
            0x140970AF7E954A7DULL, 0x5C45A2A4B4A95E44ULL, 0x3EF53F4C1ECCE29EULL, 0xCAF220825217F9F6ULL, 
            0x21BBAF37C98077C4ULL, 0xCD20C50E561BABD2ULL, 0x5F46E7541A492C55ULL, 0xBC8467630EE116D0ULL, 
            0xE4A75EBB00C84846ULL, 0x7C320D87219E687DULL, 0x331EA96EA460DF98ULL, 0xF04437D382FFF6BDULL
        },
        {
            0xA03BF5DB08ECDEA4ULL, 0xDACAA8002BAF49D4ULL, 0x3908D7FE3B2F8159ULL, 0x6958802C043541B7ULL, 
            0x303AA26F0520C18AULL, 0x17D62E381B92F7DDULL, 0x394B32B199BA9D95ULL, 0x37FCC1B3FE3F6131ULL, 
            0x60DB1A3AF2B61944ULL, 0x7905C9A22F2D11BEULL, 0x7C4BAFF918A09D1FULL, 0x911100E0D3F4027FULL, 
            0x284AAB930CD323BFULL, 0x2EA076D67E0345B8ULL, 0x7D9D2C65721CE821ULL, 0x910435AAE1CE2DC3ULL, 
            0xAAE353A33E54C809ULL, 0x96535E9B3B9D120CULL, 0x51D8FF823E7CE573ULL, 0x2691BCA160323B49ULL, 
            0xBDED5B08685D07A7ULL, 0xCDBD958CAE42CF46ULL, 0x845958CC2C66964FULL, 0xC89894F50BACFB20ULL, 
            0x5E1A402576A8A6D5ULL, 0x48330DF357E58690ULL, 0xF2D550F2C8E86160ULL, 0xABDDAF3899AFDDFAULL, 
            0x39DEC4C3307C08D7ULL, 0x0084EDB197E38D76ULL, 0x964A01901A68EE95ULL, 0x5CAD62AF7AB77177ULL
        }
    },
    {
        {
            0x1D6ECA1BB2E5BAF7ULL, 0x99DAA7F763737E14ULL, 0xD5A017022421E9D9ULL, 0xEAF602160C3DD71BULL, 
            0x001AE9FF25D27D93ULL, 0x3F9026F6EC0182CEULL, 0x59F78F6643F4CA89ULL, 0x9E6C7C82427A23C6ULL, 
            0x18826E87328B672AULL, 0xAA3075C8FA6A4737ULL, 0x4488E38A61863A77ULL, 0x70F1BB860A875F0CULL, 
            0x04F52D9A94AF0E30ULL, 0x24E783BACBA8F38DULL, 0x35094DF995E156CDULL, 0x8AB4D3E98830CAD2ULL, 
            0x52B64A38D5782910ULL, 0x334C9D83DDE20002ULL, 0xB186CE5D37A4987DULL, 0x6489347E9626E6E7ULL, 
            0xCBB9F58693761A39ULL, 0x95C9FE4BDBF122E3ULL, 0xBE56C693A4556417ULL, 0x2C8783FE770BD26DULL, 
            0x93B091BB9ACE0633ULL, 0x12A36F034C426BACULL, 0x0DF749143015F6D8ULL, 0xB79F856E51460A2BULL, 
            0x3E97F7ED05F06995ULL, 0xEFD727D41F2043C2ULL, 0x487F9A76E54CF169ULL, 0x14599D8253132AA4ULL
        },
        {
            0x8825920A2DCA30FFULL, 0x60ED7CBFE50763EFULL, 0x0C829AA3488ECAE1ULL, 0x3B287EB3E496594DULL, 
            0x4BEB56EA68363B82ULL, 0xC64145BA27F87C7EULL, 0xEE6E43B6CD9699D2ULL, 0x182406811DE8306FULL, 
            0xF8BD68D3ACBB6A73ULL, 0xEDD7AEA349EB8C58ULL, 0x8F6093E3EFE1E4F6ULL, 0x7ED3C502F0ECEC7DULL, 
            0x72134FC44368E47EULL, 0x7B9F3B0D3B98D1BAULL, 0x8E1B9A29707790A2ULL, 0xC8940D029983A6B9ULL, 
            0x6026FC422B4D7941ULL, 0x2FC9B30E7ECC9333ULL, 0x5B4E861E702C04F5ULL, 0x7EF91E22AF705FC7ULL, 
            0x89E877FBD8615C58ULL, 0x48F77E48E3E3ACE0ULL, 0x3228BBA89BA7F39BULL, 0x05D1FCD2E394BF13ULL, 
            0xF7504B79A80D3C1BULL, 0x6E4A71365196CB07ULL, 0x74B88996132CC274ULL, 0x629D5DB690A18F2BULL, 
            0xF9214242EC7C4350ULL, 0xCD2D3A980364FD14ULL, 0xDEA132AF389206C2ULL, 0x66FDA5FB033B268DULL
        },
        {
            0x521058C2D0EE78F9ULL, 0x473FA9171EEEEA8CULL, 0xF46C755EF7BA5253ULL, 0xBB764EF43E4737D7ULL, 
            0x101910316A49808FULL, 0x9BCE8FCFBA99D7EEULL, 0xAB2EC24749CA2601ULL, 0xF494C15E7D0E6602ULL, 
            0x4352F4FF2AD8BB42ULL, 0xEF02C59E36D3B464ULL, 0xA43103B236E59485ULL, 0xD1C3125CC7C60A31ULL, 
            0x1500B2A82BAD01DBULL, 0xD058B3701E5E85BFULL, 0xA94082CA9F2F386BULL, 0x849BF7CE04DEED37ULL, 
            0xC0882B3AE4400D7EULL, 0x37AF4E853E439149ULL, 0x0CD29984B5BAA437ULL, 0x6E49E6B4373E04EEULL, 
            0x41CCA2542D9E1896ULL, 0xC5FF7BF79BE9E4D7ULL, 0x1B93E637F0AB4D56ULL, 0x4A7C61CBA1A5DD2BULL, 
            0xBAD00D4B9B8A4D61ULL, 0xDA972442B9B2802CULL, 0x8F0C4AA119F0BD8DULL, 0x16D4726645A471B2ULL, 
            0x63BCF85DC936B3B1ULL, 0xF5B4CC18A2DAA0ECULL, 0xFD3BEA96E294A25BULL, 0x0EB938A107BE03A1ULL
        },
        {
            0xF1536D1AA19AEED1ULL, 0x377F29FC2551C612ULL, 0xF9CB786FFD788FA2ULL, 0x3F49EBFA8F0EEE33ULL, 
            0x62890CD97010B8D6ULL, 0xB96B56537BC2F6D3ULL, 0xA6BEC2E8EC8408E5ULL, 0x84ED7E4BCF00E506ULL, 
            0x5B28A082D9100AC5ULL, 0xDDC0454DD0B765FAULL, 0x755A3F467FC1A8FAULL, 0x6310E477E1907762ULL, 
            0x3BC835EE33B81335ULL, 0xADEF987DE3A2EDF7ULL, 0x03AE1A1A66690BD0ULL, 0xB5B4ADCB2FE6777EULL, 
            0x4CE4249C9D7DBD02ULL, 0x9EDFFD2F2BA0D9EEULL, 0xD0445560FF01A124ULL, 0xBE9A30C5CA02F3AEULL, 
            0x2F3A1BAB225E4C95ULL, 0x3EF2D8AD1DC9AE51ULL, 0xCE55B64F597CE602ULL, 0x1A21D00285CD1646ULL, 
            0x682E739567E2DBDDULL, 0xCBEF226D3FAAD533ULL, 0x5CB29DBCFA4E4DEBULL, 0x5A896E78B26ADC18ULL, 
            0x88960234C411BD8FULL, 0x49796072585BDEEAULL, 0xF0BCFF44F2C4F314ULL, 0x8EB616483A2157A6ULL
        },
        {
            0x15934E929AA91E17ULL, 0x2586226370EE976CULL, 0xD391629E1B74E3D4ULL, 0x10DBBFC5C5E5D273ULL, 
            0xFA6988CB526D3585ULL, 0x5EDE78C42A0569A0ULL, 0xA5321E201C6893FAULL, 0x2C61128993476554ULL, 
            0x374BA3FCC95EE773ULL, 0x7D3D981DF35685F9ULL, 0x7841D807C9EAAEEAULL, 0x362B5F3F078CEFF2ULL, 
            0xEF8B395B7081E779ULL, 0x72EB5ED889B52965ULL, 0x2F7CB7CB6261884AULL, 0x7F370A0ADF9F65FCULL, 
            0xE8BCBBB3B04AFB90ULL, 0xE188BE222BADB0DFULL, 0x8D9D42936E0DF117ULL, 0x763F4A58D4A7CFB0ULL, 
            0xC45E1E1F5AB0F92EULL, 0x66DDA870BEAFAAEFULL, 0x5B0D83BBEDC136BCULL, 0xD934A5DAA9FC37B7ULL, 
            0xFED8904DDF6A30E1ULL, 0x82716299099B3912ULL, 0xED2658AFE0A812E8ULL, 0x069ACC0CEF451069ULL, 
            0x64668823E0A74CD4ULL, 0x9815BCDFA94047E6ULL, 0xDF59F52E07821AA6ULL, 0x9F9F2EFFD9D5E065ULL
        },
        {
            0x7F9301EEBA2F4EEFULL, 0x511E30B2B0899C21ULL, 0x76AD1580AEE7AEE5ULL, 0xBAB8DB7156749723ULL, 
            0x51FC80F24B0D84BAULL, 0xFE4CDD40321D3A7BULL, 0x1024D11772CC4CBBULL, 0x87DF0ABCC9CCA29AULL, 
            0xDF59693FB6D18010ULL, 0xA387145A16E40EF3ULL, 0xEFF19BA4A94CA807ULL, 0xFBB8C684F64B398FULL, 
            0x69B0241E1C00C47CULL, 0x605C9351B17CB63CULL, 0x1C39E9F97C180C61ULL, 0x9B1815598BABE1B7ULL, 
            0x9485C1F586378049ULL, 0x1DEA2C826AACCE3FULL, 0xAAC85617DCCA2707ULL, 0xC80D1D8973EF1CAFULL, 
            0xAC5B9FD60374389CULL, 0xDC09F85A96DA6E98ULL, 0xCD866AA6FA341BD8ULL, 0x378D73165ED55675ULL, 
            0xED51E08618056C97ULL, 0xCDEF341E5D7DF620ULL, 0x67136B02D9ED5F55ULL, 0xE02C508418F8D269ULL, 
            0x58BFAB83CC20A5D2ULL, 0xB6651AB531371E50ULL, 0x83111A07EAB194AAULL, 0xA5B3308E6ABBAB63ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseAConstants = {
    0x8122357FF69FE2E2ULL,
    0x066EFF99119E4FD7ULL,
    0xC102DFE8169967F8ULL,
    0x8122357FF69FE2E2ULL,
    0x066EFF99119E4FD7ULL,
    0xC102DFE8169967F8ULL,
    0x3BCA04C0F285C82BULL,
    0xD22F396B1747A72EULL,
    0x9D,
    0x8A,
    0xC5,
    0xB5,
    0xDE,
    0xF9,
    0x65,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseBSalts = {
    {
        {
            0x701BE4878AB82994ULL, 0x882E3294E98D3274ULL, 0xEE7E1A37B1219052ULL, 0xFC6ECE9E7808E4EEULL, 
            0x69BBBA96025B38C5ULL, 0x23C11500880D7D74ULL, 0xCF6E224C93796C25ULL, 0xF28F297522076A66ULL, 
            0xE996F10D3ACFDB43ULL, 0xBBBD552D2F6108E1ULL, 0x2E136EEB8F027D3FULL, 0xBE6EE0F410297C3BULL, 
            0xED49AC1A4E381231ULL, 0xC58D65CBA1C9D000ULL, 0xF9657101BF668E8AULL, 0x89348F19728300EEULL, 
            0x7E298E3D38ACDD67ULL, 0xC84A33E4F4286EA8ULL, 0xB9BDF99C54995E2CULL, 0xB137B737A77354DCULL, 
            0xEA0E75FC007691DAULL, 0xBB762D742883E1B6ULL, 0x856856B3BE0435B8ULL, 0x78141EF5150BDA01ULL, 
            0x8ADC35527F46CF16ULL, 0xA1B7AB5A02371B6AULL, 0x8E99DAED70612F07ULL, 0x38C5C3D78EB35039ULL, 
            0xDB8D9BD44D786EC6ULL, 0x4D6AA845307CE483ULL, 0x9DB12F1114F84286ULL, 0x8620DD136FF41EEEULL
        },
        {
            0xDA94ACA9C0D39921ULL, 0xA0B9EB692121FF6BULL, 0x32FD0D91611ABBDAULL, 0x077134759B734D91ULL, 
            0x9F0F13C4585FE15CULL, 0x0AAD07B11ECC3D73ULL, 0x204CA3D3DB474A34ULL, 0x836380D7897C5FBBULL, 
            0x7601C29049C814BBULL, 0xD1223373BB7E3F2DULL, 0x54EF12B0AA15A291ULL, 0x0ED50B6CE877B218ULL, 
            0x331957FFB1D59B9AULL, 0x939A436CC2F333AAULL, 0x3F4626271638BDF2ULL, 0x2ABCB55F261025DFULL, 
            0x881A503BEE4CB94FULL, 0xE3E8D7C34C805EC6ULL, 0x2C9BC01A803B95AEULL, 0x971F4FFAB3ECA73EULL, 
            0xB8B61395C574B015ULL, 0x98EA842DABD0B991ULL, 0xDC813B6661941FCBULL, 0x125DFA996843011FULL, 
            0xEA1477AE470C7A0DULL, 0x5E8F4D094EB7AB3EULL, 0xA42AC5151E98B184ULL, 0xA57718FF5E890B20ULL, 
            0xE1486A44259E6045ULL, 0xD73552AD89BE7831ULL, 0xC6934E955C9CA692ULL, 0x51E70EF4ADCE5BDCULL
        },
        {
            0x46028449DC93AEAAULL, 0x4E18DF7FC1359274ULL, 0x038A415D5E5AFE96ULL, 0x3EEAA698006C3295ULL, 
            0xCB7D766EE684D1C7ULL, 0xFE86C16C138E29BEULL, 0x4CD8B30F9C016E2EULL, 0xD77C7AC0BE6A1FA0ULL, 
            0x2627A5800DE183D4ULL, 0x8B4AED6B83F5092CULL, 0x74B89D247B19BC3AULL, 0xD71B3CEBB747CB70ULL, 
            0xC3129711261490F5ULL, 0xC682147F7ECCE533ULL, 0xB07BE6C3E7C9484AULL, 0xAA476FF5256BEE58ULL, 
            0x9E5B1DA66A4BD43BULL, 0x197691C9CA4AB333ULL, 0x068141F0EB24A2B5ULL, 0x2B15EFC03310C89DULL, 
            0x5E72176181099DE0ULL, 0xD136665997B15820ULL, 0xE3C23E35F31B56ABULL, 0x7D7BB25E0F10F8FCULL, 
            0x955D3F5F9DB2DCCDULL, 0x7B18DA930EB51E0CULL, 0x3CA12A8AE354F97BULL, 0x97A8D8A3C29A6198ULL, 
            0xC85E74B70F69C5A7ULL, 0x76D49508EA4F133FULL, 0xE740B8078A4BEB0AULL, 0xFDFCAEEC9C8593B3ULL
        },
        {
            0xBF36CEE29E06D818ULL, 0xF9A4DC5831500C7FULL, 0x38E889A713C45176ULL, 0x40E5D9A26CFD4360ULL, 
            0x188A9AE498CA9CACULL, 0xF1B452FB438E40C1ULL, 0x51CBD26ECF6B63E3ULL, 0x5C58973AF7277527ULL, 
            0x06C2A3B698C9BED8ULL, 0x6C7BF333DDEC45D0ULL, 0x9D6CF55B2473EFF9ULL, 0x6A4316172D866D58ULL, 
            0xDD384A48C7431502ULL, 0xF274019E877CA647ULL, 0x700AF52037F3B1CFULL, 0x896B682ABE13ECFFULL, 
            0xC7B83C7D8FA01F3AULL, 0xC983F1D69ED33871ULL, 0x0DB9883255B20BFBULL, 0x9E7189F6149743D8ULL, 
            0x7CD974DF56A1D3FAULL, 0x539DDA066657C955ULL, 0x8327968439E3D85AULL, 0x4741E386AEAFC272ULL, 
            0x35738D5357F2209CULL, 0x0A1DF5E6E38C6736ULL, 0x6D33B23C3758BE2EULL, 0x642477B240E365D5ULL, 
            0xA162785A1EAA2177ULL, 0x400F6DFE770A143DULL, 0x608C0B5A6C7D3963ULL, 0xC5B9D896788FCD4BULL
        },
        {
            0x49BDCB551720C9C8ULL, 0x6E8E35C69A3E1C44ULL, 0x3F2348FB7374183CULL, 0xE9361AFC2EE3DC44ULL, 
            0xEC84813BF1453A43ULL, 0x98709732D3A7C452ULL, 0xCEA2DD3A5DE8505BULL, 0x50887119FE70192AULL, 
            0x90A37BC3F28579F4ULL, 0xAFCAD75A5A79E3B5ULL, 0x4540852CFBD1B33BULL, 0x99827917EE4859F2ULL, 
            0x83A07B150C5EA2E6ULL, 0x7A26F9C924BF2D4AULL, 0xA18D6444E82F5CEDULL, 0xF35A5716DA5A88B2ULL, 
            0xAE923930881DB962ULL, 0x08BCC1ABF07740ABULL, 0x997E820D85ECF87EULL, 0xB161D7C7FD365929ULL, 
            0x02C39526E858B1FEULL, 0x5E7AC29F9F719993ULL, 0x675051CB83B8861BULL, 0xB8EB02BDFA4FF875ULL, 
            0x9F4748A73D3D7CB6ULL, 0xECE8A399A66ACBC5ULL, 0xD9D7956B9FE6FBCEULL, 0xAC1EE1E5443876A8ULL, 
            0x09F75C795A06958BULL, 0xE14486795020E802ULL, 0x620ACB706AD08F7AULL, 0xF63257310DF37BE3ULL
        },
        {
            0xB59D6A3AF3F958B1ULL, 0x25E77A4BE2E83D93ULL, 0x9F336A32D9744DBEULL, 0xBFD248DB5971E3BAULL, 
            0xA79A15AD6C6D69E6ULL, 0xAABEB69D1A2C0434ULL, 0x891E7218C0663C8BULL, 0x922C5BCCD1C253C1ULL, 
            0x88E2417BCF7CF331ULL, 0x40C9C82E29452BA3ULL, 0x9D0FA31BFE6B1132ULL, 0x5B65DECEEAF06031ULL, 
            0xC8143928D525019AULL, 0x0E0B8BD36A7C87DBULL, 0x392FDB3CE3C0C789ULL, 0x1412718910D41EAEULL, 
            0x4BDF7CFDBDFC7D28ULL, 0x8A7ED05A2F65BCEFULL, 0xB8DC482D2A2AF888ULL, 0xA9A430FD2D22FFA1ULL, 
            0x173D9EAD47161432ULL, 0x4E99E810353AAE00ULL, 0xD670E55F5E96F5E4ULL, 0xA7E00EE945F40083ULL, 
            0x714019831D0E706BULL, 0xF5F05B74B8E72D89ULL, 0x6767D3036206AC4EULL, 0x866B68700F06AA8FULL, 
            0x69E25104DFFB6ACDULL, 0xB92CF8B608A93CBCULL, 0x30E6A4CEABF84BEAULL, 0x519451D6FE515A71ULL
        }
    },
    {
        {
            0x8B36B7C59ACE195CULL, 0x97631937D9FEB979ULL, 0xC877814D2756A396ULL, 0xD9F4A4CB61D84833ULL, 
            0x734179CEF3947C61ULL, 0x8FCAED86E5919642ULL, 0x5DDB21B3AB63E067ULL, 0xE4A20869920EC7A4ULL, 
            0x106E676EAD8E5245ULL, 0xFFE17ECA54CF97BEULL, 0x208F3FD9936B83DDULL, 0xE949AD7519966F73ULL, 
            0x40BF5A1FB7BFCF5BULL, 0x5B07B1AAE3CC1A96ULL, 0xC068E0955F2F59B6ULL, 0x5BC33141F4A6563DULL, 
            0xFE002F0F2C7AC275ULL, 0xECF178AB2D9E2B48ULL, 0xD7CDF64972A2531CULL, 0x24DAC972FF92A5ECULL, 
            0xD4F38D9D6DBCF7D6ULL, 0x32EAB304835DE4EDULL, 0x7EBF3AF066B86558ULL, 0x038A9ABF293F0409ULL, 
            0xDABB9A5D6D09D8E5ULL, 0x4C82343F27F1A720ULL, 0x9BCC9DB4DFAF4243ULL, 0x8D7734533AD90442ULL, 
            0xA3D77702D5F0901BULL, 0xD8613578B9A3D266ULL, 0x9F217110ACA76C24ULL, 0x74A10907978378E9ULL
        },
        {
            0xF586B6766941A216ULL, 0x5EE6B41EFBDD2C20ULL, 0x90D46515E98A0323ULL, 0x19D39808EAE28AA5ULL, 
            0xB6F62F401FBA00E3ULL, 0xAAF6DE672D512224ULL, 0x8A8A19949B156185ULL, 0x7D2DE40B9FB78FBDULL, 
            0x47191EEE78224A6FULL, 0x3B415E371A7886BBULL, 0x6FDFCC5545E5E17AULL, 0x4EF1FC64B1EB5FE2ULL, 
            0xD991F098ABA842E0ULL, 0xFA3AF0D88F4BE616ULL, 0xA75DB4E824286340ULL, 0x533A9B34C71A2D75ULL, 
            0xD8B32D6EB12BE0EAULL, 0x6C491CC92CE2B99AULL, 0x03DC04C311ADB770ULL, 0xF121B6DC195B21E8ULL, 
            0x241A7457C8EE32DAULL, 0x94FE94BD11FFD6F5ULL, 0xAC7F0AB57E82BD6EULL, 0x4DD0CC99E9AAFCE1ULL, 
            0xEFF7810948F0D285ULL, 0x2B4AEADC34872340ULL, 0x6E4241C87B3EC5B3ULL, 0x862CB2330074B9A2ULL, 
            0x5B569B329B0A79DDULL, 0x82F5BF60E42A87D6ULL, 0x84ED15A1A723B331ULL, 0x9360A29AD9D8E98AULL
        },
        {
            0x69327C13E364C7F2ULL, 0x76324AA40F468D9DULL, 0x1C94DB8BC974D160ULL, 0xAE1821743C1E7F9CULL, 
            0x584BA54EF72E2E6AULL, 0x5550E030476F3C47ULL, 0x91E5E2467AE72D40ULL, 0x9CBCB1DC0C394F09ULL, 
            0x530273EEC06D3649ULL, 0x52D1220F10902326ULL, 0x7D325CE6DF0CDD81ULL, 0x35AEDBA9A77AABE5ULL, 
            0x6120CBBC38133F21ULL, 0xBA0564CAD2E5EDD2ULL, 0xA7257B12A2E9C525ULL, 0xCBDB0F58EB142BADULL, 
            0xBC280CC972CD2735ULL, 0x55B59C101130BC1DULL, 0x42368AE74DCB916EULL, 0xC6A9D3F255FB6C08ULL, 
            0xF346E294F4BEBAD0ULL, 0x2A8E786C3598CEE8ULL, 0xC8E58FB8126521C2ULL, 0xE8FEF507E2FAE497ULL, 
            0xF61B0C535FDB38ADULL, 0xA27ADF6A621D1C6EULL, 0x62B3204A918EBB05ULL, 0x8C42C1E5540B074CULL, 
            0xDB85F776A4C43504ULL, 0x01B0308C97F223B3ULL, 0x8F1986A81982A76FULL, 0x2E19AF3845E48A42ULL
        },
        {
            0x3E764D94A7246D25ULL, 0x5F01CF3B3C9B6446ULL, 0x3C7221C719D78EF5ULL, 0x2E88922AFAE51AF3ULL, 
            0x9B043A475BC89D56ULL, 0x3E1F2FEE1C894207ULL, 0xE7E89C32465361F9ULL, 0xF410D1F065F5FABEULL, 
            0x1FCB3F76E16F9B80ULL, 0xB681DBAB38FBEE0DULL, 0x07EBD6CB8995869FULL, 0xDC60184A29B93085ULL, 
            0x6AE1F92572C994E8ULL, 0x49CD3903E3ED4DC1ULL, 0x91B8A0C3E81C55CFULL, 0x574C9141D0145A56ULL, 
            0x1DED0128AC3286F6ULL, 0xE76253F936AAFFCBULL, 0x9C97BB9B1C77694CULL, 0x9FDC05FE13B464EEULL, 
            0xCECA876E1977EA55ULL, 0x677F456BCC38C3A6ULL, 0x4D027E14920C3F95ULL, 0xF1BE769EF958FC77ULL, 
            0xB33473AC29F99F9EULL, 0xE003EC442F40992AULL, 0x25386E1479EDD665ULL, 0x880A79114B46436DULL, 
            0x214C196D651FA5F3ULL, 0x0B71B5D96E6FA289ULL, 0x69BDC5652F036072ULL, 0x143984825AF49F62ULL
        },
        {
            0x1753D32D8BCC578FULL, 0xC5CCA9B1CA8139DEULL, 0x7DDDB289B579E846ULL, 0x025EDE38997D7B4DULL, 
            0x2C0BFF0407F49240ULL, 0x6BD2F86F8F86319EULL, 0xAB4F9DE1461E9591ULL, 0x81CB005C208EFB1CULL, 
            0x33C9E24C4B26DCD2ULL, 0xAA585A33E72B50B6ULL, 0x83AA5F89ABD2F34CULL, 0xD3AFBAEA6A058DD4ULL, 
            0x088E4A850B61E22EULL, 0x33691E486594E245ULL, 0x8E6879F3CB9C5151ULL, 0x1A979456BDC9D53AULL, 
            0xC8CBD5E455E343FCULL, 0x0C2F4E6FDE36D53DULL, 0x2BFFF765854C21C4ULL, 0xC997563C6C2F24DDULL, 
            0x733FCAE89B2C01E1ULL, 0x841E0728D0A899E2ULL, 0x4CAB9C8AEB028805ULL, 0x8B9C8C84DFBA54EAULL, 
            0xF93D81CF82BCBE35ULL, 0xA0E3F7C09EA15939ULL, 0x640AD097F3224EFEULL, 0xF595AB5D56C3A616ULL, 
            0xA5F6B2038311A491ULL, 0x98F5A0C50FB921C7ULL, 0xA577DA6A7A96E2ACULL, 0x31D872F00CB7E907ULL
        },
        {
            0x5413142B830FA525ULL, 0x02EE85DFFA6995B4ULL, 0x0FE4B9D391AA61F0ULL, 0x02628842DCB365BDULL, 
            0x09FABACCA96C9067ULL, 0x6562B9367E3BB1FCULL, 0x68681B046B6192B0ULL, 0x790AD847D682A312ULL, 
            0x32566D5579133032ULL, 0xF95A11C68381E3EDULL, 0xF8186E09E9CE3B3AULL, 0xEFB597F39EC059CCULL, 
            0x04222C6501498480ULL, 0xDB44566E199DBC95ULL, 0x59C8CCEAF905A935ULL, 0xFCFAAF89ED32E9D9ULL, 
            0x8CC98C2D8F970522ULL, 0x6CDF78BC4519F983ULL, 0xEE5F48EB87B43342ULL, 0x017D9FB39FBDC342ULL, 
            0xACAB55BE2A46593CULL, 0x1714C5BD4E14148AULL, 0x61B95DAB6236D89AULL, 0x89212D8281CD260CULL, 
            0xAA13B9E766FF1B7AULL, 0xFE9ED7CD8BDA02A0ULL, 0xCE10CD90D1124B54ULL, 0xF3A400897430EAE7ULL, 
            0x22E67B46E78B49CDULL, 0xF5CD8987988936F9ULL, 0xE7F9182F096A4562ULL, 0x15E04AB337D4DE21ULL
        }
    },
    {
        {
            0xC47E228F755753EAULL, 0x340D10A93E9D24C2ULL, 0x1985163549F84AAEULL, 0x9853FBB8CCA7FF8DULL, 
            0xFAC31D55656E72E4ULL, 0xE120A831DE0ED4BBULL, 0xEC3251B20AAD4F68ULL, 0xCF23A0F89B183BF8ULL, 
            0xE46FDD47C827352CULL, 0xC36D8F91904F0FDDULL, 0x1B1C0CAB7D22A65FULL, 0x97AF9D82988D227DULL, 
            0x10B923B5153996B8ULL, 0x7BB63C14320AA7C2ULL, 0x455D8764B8AD8AEDULL, 0x6E092DDBA50EB47EULL, 
            0x6681738EB8188716ULL, 0x0B951CF27021A81EULL, 0x22448AB7D7D7485BULL, 0xC0AE733D9398A7C4ULL, 
            0xC85EFB8B92071F98ULL, 0xC375980B26076685ULL, 0x8ED1382C33CAA980ULL, 0x69607ACE599983E7ULL, 
            0xE5BC90B40E829A15ULL, 0xA1C990E0B72B5E84ULL, 0x4CB4B474B3D09126ULL, 0xE88580E22AFE6443ULL, 
            0x72B3F46B789337C9ULL, 0xF53732898A6783C7ULL, 0xAB525DE92EC925B4ULL, 0x4F8084F97FE19732ULL
        },
        {
            0xB2EFF6DBACF12EDCULL, 0x4881F73DCFDE52C3ULL, 0x6E0249E8C0826753ULL, 0x0FE8466ECCB58804ULL, 
            0x246CE4205749BA66ULL, 0x076E9CF3B09D512EULL, 0xAD29C441E353AC0FULL, 0x894DADE6F753A06FULL, 
            0x1BA8BC38EF260D5BULL, 0xA4F869E1D9B0FDF8ULL, 0xE0A1D5403280AB86ULL, 0x207917E4AA359474ULL, 
            0xE286C2A64D46A9B9ULL, 0x73EAF7FD3164C351ULL, 0xA179833C3C8D0F64ULL, 0x99DA5769BCC08DFAULL, 
            0xD8297B3DB8AD68ECULL, 0x30B3DFB4510CEA3FULL, 0xBF6F6ED00A34D24EULL, 0xBDACDACD57444244ULL, 
            0x134E7887CC0D2193ULL, 0x128CB49883DCF3F9ULL, 0xC2858AA2B4DA2FF7ULL, 0x0DAA7EBCD89E5BFBULL, 
            0xD6CB512EE82891C2ULL, 0x05A753AB167A087DULL, 0xE441B378CA4DB630ULL, 0x403367F454B18795ULL, 
            0xE6C546DF5244391EULL, 0x49241814EE4A699DULL, 0x98DE9981EC9A4CA3ULL, 0xC219FCF68CE8ED79ULL
        },
        {
            0x138159524B7DDAC8ULL, 0xE153D028038DE579ULL, 0x2D6A5A41885883F2ULL, 0x8614E2E55EAA4E7CULL, 
            0xDB94F22D0B6B5178ULL, 0x27FD5B15CE047E02ULL, 0x8C662A49D490B68DULL, 0x6F006FEE104B2D9EULL, 
            0xF341AE2B38791358ULL, 0xB5C49ADA9823A1BAULL, 0x57083ACD6C0689CEULL, 0xE7BABD728912429DULL, 
            0x82A36C982444D19DULL, 0xA5324380FE37A9ECULL, 0x36A930029C4460D5ULL, 0xD396699F5D8585FCULL, 
            0xC15DC22956EC66E1ULL, 0xE6A47FF6718E5C4DULL, 0x713B1616161E6D11ULL, 0xDDCDAF947FDAFF98ULL, 
            0x77A5DE21D7B4E85EULL, 0xFDC6C9E3999F14BDULL, 0x5AD6CF31256D61EBULL, 0x2B01FB202A0180E2ULL, 
            0x47E7FA9961B90E1CULL, 0x57B077783C465594ULL, 0x97B80A58E092692CULL, 0xACA5BDEF7B2465CCULL, 
            0x39DC457D9875878EULL, 0xBDC62598FEAAE16FULL, 0xEF5E6D3B6891778DULL, 0xFF0B9410FCED2C5CULL
        },
        {
            0x7538FCB3EA9D0581ULL, 0x0AD906DCCF89E5D6ULL, 0x2213F051EE741F8AULL, 0xA7B5966919B71DAEULL, 
            0x894E0B3F789710A6ULL, 0x58BD0D9EF8379002ULL, 0x510C2A9A2A45DFD0ULL, 0x210934495071DC69ULL, 
            0x7B23140080F5BDDDULL, 0x68E7C862881C25DEULL, 0x25BD7244143953B5ULL, 0xFA934EE0698FD417ULL, 
            0x07B1587AA2DE86E8ULL, 0x8BF1A65F453DC55DULL, 0x3122D7C6DC661EFBULL, 0x6C7A0BF58E0DAC81ULL, 
            0xDB1D7BB1D52A609DULL, 0xDBB6B2E48568FB56ULL, 0xF9ECB363FE6FAFEBULL, 0xE43D2D9AA83663B1ULL, 
            0x252620E1822AB287ULL, 0x2150A01009AF3090ULL, 0x8733C901A165B828ULL, 0x33D65A6E1F769FE0ULL, 
            0x75A06F095F184A95ULL, 0x12F16EAE91394713ULL, 0xEB198117A40255CFULL, 0x32F9C93293FC47EBULL, 
            0x1D6A4DC26F46C1A5ULL, 0xC5F3B64E5D83EE59ULL, 0xB8F56250DD3DF233ULL, 0x0C7C5F5C32522D13ULL
        },
        {
            0x6B1CF1AF6D8AA717ULL, 0xFC6E3D2D5D878CE4ULL, 0x28BB605F4D86B8D2ULL, 0x81DB022249997D84ULL, 
            0x6739FCC73810A7B3ULL, 0xFE8A96C680041A24ULL, 0x67381CDD72104340ULL, 0x78ED0528AB01CF90ULL, 
            0xC4B7A0E0EF3394F7ULL, 0x235D371FF5DCFA41ULL, 0x3CBFFEAFEBBCD00DULL, 0x8AE36F9F27391E64ULL, 
            0xDFB935616BE14A76ULL, 0xBF93BE15BB949439ULL, 0x44CEB2519397C2A4ULL, 0x757E44EB1B16D073ULL, 
            0xBF00C5596551882AULL, 0xE9800CB10C7F4EE2ULL, 0x877795BF82243890ULL, 0xC395318B2B20AAFDULL, 
            0x8559A606AB413AEEULL, 0x4B5BB3B735E4407BULL, 0xD11CB1F7C4A7CC27ULL, 0x049663B3BAC82714ULL, 
            0x17AEC2D5F73AE259ULL, 0x7753212F10781E3CULL, 0x526B85E009B19D68ULL, 0x7A4B55F27CE9DD78ULL, 
            0xDE5321514AA6353EULL, 0xBC09D8FEF7097D06ULL, 0x6EEDD5645E0A4B8CULL, 0xF86A0347176B0626ULL
        },
        {
            0x0D3EB0394F80E923ULL, 0xF3FB0B11F52965C0ULL, 0x876CF4ADACA00C51ULL, 0x95B0838E5FECD049ULL, 
            0x5CBA1572500E163CULL, 0x70B550DFB971AB42ULL, 0xE8C910C8D075849CULL, 0xDDE110896A465E9AULL, 
            0x57219E8EE900AEFEULL, 0x7CF97241D5241661ULL, 0x47E2FB7097BFA78BULL, 0xA85D9D8EA79DC2D1ULL, 
            0xF4D830833052B7C0ULL, 0x4B6D3F0C20671C70ULL, 0x27F115D1D070E2E8ULL, 0x1AA4DB152AFF32FDULL, 
            0x072B9D3AF1A7ECD9ULL, 0x2BFE6D3480149ADBULL, 0x48FD2A3693595F49ULL, 0x2C70B4CAB29EFFADULL, 
            0xA8AB23329C4EFFDDULL, 0x8AE34F9D9108F41FULL, 0x9CED150FA99A3580ULL, 0x79D7F4618D034536ULL, 
            0xD9312432A1429FBCULL, 0xDE8A3FAEBAE7D5ABULL, 0xE9ED81DEBFC7AFD1ULL, 0x1208A9C6AA433D09ULL, 
            0xBB5A20DBAC4E6A20ULL, 0xBEF444D1D0081C7BULL, 0x025B3B13111AC39BULL, 0xB90378A3CB2163C4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseBConstants = {
    0xF3DFFDA382931DBDULL,
    0xF9A668CE23B74614ULL,
    0xC462CF3841E4EFACULL,
    0xF3DFFDA382931DBDULL,
    0xF9A668CE23B74614ULL,
    0xC462CF3841E4EFACULL,
    0xBA5514136FE8D55CULL,
    0x6E34F046FCAC536CULL,
    0x19,
    0x3E,
    0xE8,
    0x08,
    0xE3,
    0x07,
    0x9A,
    0x68
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseCSalts = {
    {
        {
            0x9EE602FF772C73B2ULL, 0xA3D77BF888071758ULL, 0xBD59E6CD1E994C2DULL, 0xAFE69454A07D1883ULL, 
            0x578890E53EBADB80ULL, 0x95C2BFBD814026FBULL, 0x022CBB1A807C00B2ULL, 0x90CB78EA3A858CC3ULL, 
            0x1C05635FF1342772ULL, 0x8F78C234A4C8B1BAULL, 0x74648984946EF18DULL, 0xA49415CD26952C53ULL, 
            0x61C00DEEC2468BA3ULL, 0x181EE4794484155CULL, 0x59B5A1A96D4D8C67ULL, 0xAFC3959BC5AB734EULL, 
            0xAC6A1C5674E03065ULL, 0x8CEE5BBE92C89477ULL, 0x4AFAD1447F15B33FULL, 0xEB53258AE5FD1738ULL, 
            0x67A4922C67A73824ULL, 0xC224F68F51125C33ULL, 0xA20CE66E5F60142EULL, 0x582CAD92F0B55699ULL, 
            0x39D9D6FE7E4C0E30ULL, 0x4EE9259C679AF482ULL, 0x47020DB791C59198ULL, 0xA9BD84E30911CC07ULL, 
            0x56919E4541C32795ULL, 0x9F5751CA93652E1BULL, 0xA018A1D2CF44ABA6ULL, 0xA92C97A4031ED494ULL
        },
        {
            0x359E7113426BBE93ULL, 0xF0EA2B1A10211474ULL, 0x0CB092415363B807ULL, 0xE4E02A75A734EB37ULL, 
            0x65E1A1F34D8013ADULL, 0x04162ACEC28ACDE3ULL, 0x6A0102B64EB8E455ULL, 0xF1FC8F32313FAF4EULL, 
            0x269D6947B5A5BE35ULL, 0x6D85EC1B213C7CD5ULL, 0xB09E7BB0C8E71215ULL, 0x73554F28AB442FA2ULL, 
            0xCD57304A974A0E59ULL, 0x6265F0CD03659270ULL, 0x9898247E2BBB4933ULL, 0x2296EE94E65EC767ULL, 
            0xC9F53C7601E23E17ULL, 0xFB38C4B1F7CF8BCBULL, 0x95821B1DFB9CD18CULL, 0xBFED84AA12079EB1ULL, 
            0x3BF3630855F977DAULL, 0xDB2766E0B7CAEFDBULL, 0xC996E6F0C5BC0FE3ULL, 0x6F951156D2EC4D7BULL, 
            0x47AABC91D82289B0ULL, 0x3776F16C7A9E11B4ULL, 0xD71A2C455B3092A2ULL, 0xE4AD868A8F0616CAULL, 
            0x1A818CEC93AD9E9AULL, 0xA098768716268B12ULL, 0xC24EFB5A0B5C250BULL, 0xDE6A19B04E3122AAULL
        },
        {
            0x1E537792DC38A671ULL, 0x9E01C1001A056A3EULL, 0x1DE2DCA6F599E68FULL, 0x72E5B5591744D3BFULL, 
            0x3DAC1B18032928C0ULL, 0x051305F3AB4151E2ULL, 0xFC50D68B24F3C99BULL, 0xDBC9479355F7B472ULL, 
            0x8512E33ED55D01F1ULL, 0x1F8BFCC6D1080DD8ULL, 0x2760846B043CAE0AULL, 0x0E5104B9AC3229ADULL, 
            0x9A961FBDC0EFA1D0ULL, 0xD674EA7622EC7A85ULL, 0x60F38F89BAF0591FULL, 0xB0E99CA141360A8AULL, 
            0xDBB7F9EDE234C6EFULL, 0x137E126C761F08EAULL, 0xD35ABB7F75EE49AEULL, 0x8895984D06730A12ULL, 
            0x47460095C3C0EF35ULL, 0x64B4CC3D75F8B38DULL, 0x71C0EDEEF370F25FULL, 0x15F79EE84986E908ULL, 
            0x1F95F2C2634D32FAULL, 0xA21A64A0057D5489ULL, 0x42DC9F4FB3F9524DULL, 0x8EFFE0E7C744E824ULL, 
            0xECE0FE64C52BA86DULL, 0xB7B1DBC152C1C7B6ULL, 0x90B1635F02EFA74AULL, 0x7EDD580705A313FCULL
        },
        {
            0xC499CC350AC6D97AULL, 0xD65D46DFB2CA6672ULL, 0x93E7052D1D5E816AULL, 0xFBAD635F40000880ULL, 
            0xB4017DB3292FC56EULL, 0x50661BA84D03AB11ULL, 0x5ED780C82B7120E3ULL, 0xC07DEB01C7F11BB7ULL, 
            0x627D78A5BD5A40C0ULL, 0x3589D817553E7AD8ULL, 0x17DCB2565E32395AULL, 0x7299D061AF25D57EULL, 
            0x1929A8455D421C2BULL, 0x2656F751E2713A06ULL, 0xF174A596E9A0AA0DULL, 0x4D7E59FC1278631CULL, 
            0xC36BAC221ED10A28ULL, 0x01C0DF4FDB8E1076ULL, 0x982B0318B22A3DC0ULL, 0x0FC2B4ACC9DA2ACEULL, 
            0x5190145A8C240477ULL, 0x9C81656FB09D56EEULL, 0x2B55694F12A4FA76ULL, 0x3CD26CF072FB4618ULL, 
            0x34CAEE3F6EA45D99ULL, 0x93DBBA4CDC8C89C5ULL, 0x02B7F17206E8061AULL, 0x8E822E5580B4D714ULL, 
            0x42B9175E3296EA00ULL, 0xC0C4B3C6B4827C41ULL, 0xCBED8A1538C740E0ULL, 0xA3CFD00F71ABD217ULL
        },
        {
            0x94281EEBC99A2841ULL, 0x6682B0D09024CB44ULL, 0x5C55DF5CA1DF2318ULL, 0xB679E02FDAA3D28BULL, 
            0x6B368C20CB3111EAULL, 0x30ECF323CD8B81B6ULL, 0xC4922758A5F38848ULL, 0xA7ECA7115B8F4D5EULL, 
            0x9A38FEDC85B1DE73ULL, 0x7D44CEEB551D4416ULL, 0xF842869E971FC83BULL, 0x2C5BFDC65A17F920ULL, 
            0x3E215F287F5AE4DBULL, 0x90A10B2704AF704DULL, 0x3B76E3A4DC6C8786ULL, 0x755C121B5E3C25CCULL, 
            0xD1EDAC3D5EC12127ULL, 0x7D15C13D166208F4ULL, 0x1580E24561468E6CULL, 0x06E22A22EAE5EB2EULL, 
            0x98930D8FE0613FA9ULL, 0xD65AAC42B8DF2617ULL, 0x4F310763F40AAA19ULL, 0x9688CD478786177DULL, 
            0xB4345663580AE10BULL, 0xC282CDF49F62DB11ULL, 0x44E6785FB480FDFBULL, 0xB5F386DC0AFF2CD2ULL, 
            0xEFF0BB9B14C2104EULL, 0xCCF6288366BC13FEULL, 0xF592B949051E50FCULL, 0xEC088011E9C515DBULL
        },
        {
            0x55B2CD2ABA2CD567ULL, 0x6E14F8C2B443C4D4ULL, 0x25AD1604741D463DULL, 0x314BB0FCA55A035AULL, 
            0xB8BAC1BD4C203FC3ULL, 0x0AB4E4C306E5855AULL, 0x741F736B1485902FULL, 0xC754F27024D4C7DFULL, 
            0x675B2A720A562858ULL, 0xA0EF4B936A03C2B4ULL, 0xC2D4512562C59BDFULL, 0x5E8032E5DE9D639CULL, 
            0xCD70510DF39E45C5ULL, 0xF2F307EE8C1A5A20ULL, 0xAF8400F550FBA42DULL, 0x49EAE2A335ED07BFULL, 
            0x5A05C15586BF9D61ULL, 0x27DFF8F8F5A9412AULL, 0xCCD4D08C05F43D22ULL, 0x8F2A382987344B82ULL, 
            0x5C7BA4A9F86867C3ULL, 0x85A3BDFEDFCE7D8BULL, 0x902E07A680DDF9D3ULL, 0x3E3E3421E3A089DDULL, 
            0x1504C58A6F17F118ULL, 0xDBC0418136DD8D95ULL, 0x60B2DFD56338E8FCULL, 0x1654369A91600B79ULL, 
            0xF8F272D57C43C2DDULL, 0xDA5EA16859783E10ULL, 0xA0D31AC90227B0F0ULL, 0x922C59C79FC7E695ULL
        }
    },
    {
        {
            0x5D060172AF9D7C4CULL, 0x44AC36808EB3291BULL, 0xCA1093D95C88E19AULL, 0x0CF3526453470045ULL, 
            0x55184F7AA0136535ULL, 0x1D5CC2EDFD0B6CC8ULL, 0x6867EE6097F0F0D1ULL, 0x3F71C290E8013638ULL, 
            0x97F4496BB26935F8ULL, 0xEC6EFF6F94766B6BULL, 0x65FC3D5492114D7CULL, 0xADFA2FB955F4CAD5ULL, 
            0x01A8D16B14B9D537ULL, 0x7E40C0CA9A90F0F5ULL, 0x0CAE48FC7BA32020ULL, 0x1E3D975F713FEC71ULL, 
            0x6A49C32DCA0EB9CEULL, 0xE58A8908239D7E1EULL, 0x8DEAAC234B5F1096ULL, 0x2828308F889C64CEULL, 
            0x36721B594C53FF05ULL, 0xD11B36A528CEE842ULL, 0xC89872A5A4AB7568ULL, 0x2CED87F3F2074EB6ULL, 
            0x73506D6B5569D717ULL, 0x482B22B91CEB92EBULL, 0x105EF26B15902E3CULL, 0x53CBCCB557326624ULL, 
            0xAD55DFB53C247EA3ULL, 0x97341813016B3543ULL, 0x039A3C4776E02106ULL, 0xAB0F4EE38ED74588ULL
        },
        {
            0x2B2E0B79527FF2ADULL, 0xE04499C045425760ULL, 0xFEA3DF3220581242ULL, 0x92F6CD144B6AAC1FULL, 
            0x0089D4D64C75F844ULL, 0xDFDDAF969156A650ULL, 0xEEF7D80CBD4E6143ULL, 0x004F37F0DAB2E6F2ULL, 
            0x5FBD4FC751A751A5ULL, 0x1187148BE4DC3C8EULL, 0x964D374FFB94C9BDULL, 0x45E602257B83FC57ULL, 
            0xDE8E601AC4B45CC8ULL, 0xCD455AAE54EEE4EEULL, 0x23CC5FC174453250ULL, 0x61D76BD382B3B205ULL, 
            0x90FBA9C0522459B6ULL, 0x3DA628308F9A8472ULL, 0xA2F6CE31939F3176ULL, 0xE74590B40944F317ULL, 
            0x2B35B2B6AD266628ULL, 0xD5BA948CD367A21EULL, 0xC61F28BCCB3ABCC0ULL, 0x3B5FD3F0F10D94B8ULL, 
            0x9A10BEC913EEBEBEULL, 0x5F7D63F149317F09ULL, 0x814602B1E43423C5ULL, 0xC5100E29F5340EAAULL, 
            0x6EA8CA74E283FB58ULL, 0x92D9DFA44C059CB1ULL, 0xAB8F87A10637365AULL, 0xA1C3F8D684CF8198ULL
        },
        {
            0x793D4CD157C26189ULL, 0x52CBA48F6F98D019ULL, 0x8C81C35422929A2BULL, 0xC94290D06325E4AAULL, 
            0x17F7D4FAF9EF497EULL, 0x9BFE85A9DF31BAF5ULL, 0x14EA3CC91CBA9443ULL, 0x276A122ED4E43390ULL, 
            0x7A418B22F9DD0A01ULL, 0x88EB6E68B831CBA9ULL, 0xE786B1AABF6C3883ULL, 0x6B1EE15E4E451F47ULL, 
            0x7F87EC24AF1B3F4AULL, 0xC18E9F24597A7EC8ULL, 0xF383DA0D3FA1C9AEULL, 0xBF8994AC75630DB8ULL, 
            0xB99C46F4A3AF3AFFULL, 0xB56A54A79C49FE47ULL, 0xB47D5A137404AB22ULL, 0xE5D8951E76FD960FULL, 
            0x027D6D4EF1843064ULL, 0x3DB5FBC6048FC605ULL, 0x91FE42993A539A2FULL, 0xCF2B34BFA7AA4E2CULL, 
            0xB788B5DB8BDE5EDDULL, 0x08E0C15A16B5706AULL, 0x7AA9050A195A1C91ULL, 0xC2E74DC023937A54ULL, 
            0x38458DC532C7E688ULL, 0x7B3EE5C2BA2ED14CULL, 0x3234CD421BB686D4ULL, 0x12FAECB5F5220D24ULL
        },
        {
            0x9ACE36A5445851EAULL, 0x88D7D7EEC9DA688AULL, 0x18ABC15A58AB6A54ULL, 0xD8C60E9981693E9EULL, 
            0x620FCBECB8E18D74ULL, 0x482337420BA2DF5EULL, 0x60D235A6D9A3D176ULL, 0xE8334E75D71E6FEAULL, 
            0x195A0AE8BF8BA338ULL, 0xD54DFD915BD891F6ULL, 0xF0F04EF9DC64B04FULL, 0x7055984E3CA1CB3FULL, 
            0x506D2523B67BC821ULL, 0xA89F0E6AB41B501CULL, 0xB796BE2D002C028FULL, 0xE4EC0D0D37356780ULL, 
            0x6657E4FCF36556AEULL, 0xC9A56268C598FFEDULL, 0x461B86DC75BB84BDULL, 0x18A33ECBD45B8D25ULL, 
            0xA859C27ED52224ABULL, 0x3BA5FCC325299DA9ULL, 0x86BC2D7A673770CBULL, 0x37AEBF292E5504E9ULL, 
            0x6F7CF6EAF793E6CAULL, 0x253BF2BABB4CD435ULL, 0x6DC5A9B89751143EULL, 0xBB94807476936F25ULL, 
            0x309C5987D3972AA7ULL, 0x919E65355CFF3FF7ULL, 0x242031C5E9F63641ULL, 0xE4EB572D9F792979ULL
        },
        {
            0xCA6B121D282F07B0ULL, 0x6956DB611CB55135ULL, 0x5409F0BB9D92A2B8ULL, 0x498432DA2DC960E8ULL, 
            0x9BD57BBC0E8816BCULL, 0x57CA42DDDF0B24AEULL, 0xD66CAB68CFF92118ULL, 0xD4A10B29365AF66CULL, 
            0x5428BF7F5EFB277DULL, 0x0F2DAF811129B296ULL, 0x4C1EC6D56C9FCAE8ULL, 0xF2D69594C1824715ULL, 
            0x4389939B5311B143ULL, 0x79D747A5D0C6B8C1ULL, 0x4285DB574EFAFAD1ULL, 0xC7B4793A5E7C68C6ULL, 
            0x43CA9575BA0C5413ULL, 0x01213FDF64AC03AFULL, 0x25E34C97314956B9ULL, 0xCB658E32F1DCD49BULL, 
            0x43330EA198B0FA2CULL, 0xD8F6B6267779448AULL, 0x28DFC49F41126E94ULL, 0x836CFEC3DA36B276ULL, 
            0x8A899B99DC1D3BCAULL, 0xE3772F6C4FDB2DCCULL, 0x2D8356F3A6CA0A55ULL, 0xA58489CB143ED708ULL, 
            0x82A7021C42CF9DBAULL, 0xB9B5D0A89988AC14ULL, 0xF06FEB5B5A25377AULL, 0x90F8B9DC68E15861ULL
        },
        {
            0xC65872C1C5E02771ULL, 0x750E00E253AA19F1ULL, 0xA99F2AEA696781DAULL, 0x0F96698AA5E30E61ULL, 
            0x286FEE19A3BBF443ULL, 0x8980258693C029D6ULL, 0x5C3E1B47ACD19028ULL, 0x0EEDF27FCEBD735DULL, 
            0xF26BD9FAE99A8E2FULL, 0x66179B91388BD486ULL, 0x322C7CEF01C49D45ULL, 0x0298CE6AD250B7B9ULL, 
            0x245769BB9B38B981ULL, 0x750F898B990C5DF3ULL, 0x8494787243715A67ULL, 0x4BE6BEAAD40D6F73ULL, 
            0x1B97B62145E0EEB6ULL, 0xD1094E9C4CDFB9F1ULL, 0x7654342E01779A20ULL, 0x1A34C2745372F86BULL, 
            0xFE95F900577B2715ULL, 0xB0384E991B2734E7ULL, 0xC9ED3F157493F4A3ULL, 0x407B9AD3AADA445FULL, 
            0x693AF9E3506974EBULL, 0x8A07D014A7947CCDULL, 0x6A7B5A018309CECAULL, 0x34195E6EBB48D897ULL, 
            0x9D72EA264E58E969ULL, 0x1F064A80BF1287DCULL, 0x09C2FA684193EA71ULL, 0x2E5CB5CD6F5EEA81ULL
        }
    },
    {
        {
            0xBCD2BECD88B88E6EULL, 0x0E9022695B5F0787ULL, 0x2F650ED42FBBAB84ULL, 0x3D072D4557B727D6ULL, 
            0xE7E47263F79045D4ULL, 0xCED26D2266561636ULL, 0xC6F665AAAA41F168ULL, 0x8C219E47824E0C7BULL, 
            0x7A3771E98D4556C9ULL, 0xA20686C91583FF4BULL, 0xA40FDED07B4648BFULL, 0xC1E16F7F173C31B3ULL, 
            0x267D53A3F092E62DULL, 0x4E8AE75707E2A385ULL, 0x7DC36F7FA1F6C772ULL, 0x43451CC6EEC92CA1ULL, 
            0x33B6C607EF7F8B45ULL, 0xC8C04A06CF2D302CULL, 0x256E934BEE9B70A8ULL, 0x7D8A0557DD00EDE7ULL, 
            0xBB863DB540A0F17FULL, 0xFF178A5343CA745CULL, 0x23DEE5A719164F0FULL, 0xBC6783A92C0B0DA5ULL, 
            0x3571C315E7C5629BULL, 0x23134FF2FB656216ULL, 0x3B57DC76D04225F3ULL, 0x180ED67E11CBFC64ULL, 
            0x829904512647CA91ULL, 0xD522AD3F3F28F7D7ULL, 0x3380B7F56A2FBFEBULL, 0xD493F96DFC7825FAULL
        },
        {
            0xE683B0C934FCFBA9ULL, 0x6123A4E32BBF8852ULL, 0x50D43681C49AFA9DULL, 0xAB449A723B30FFA5ULL, 
            0x0067AAD213A996E6ULL, 0x15C242926392EC37ULL, 0x65735B042EF335C2ULL, 0x1E1216846C8311B9ULL, 
            0x8ECDEBF3D37C38B9ULL, 0x8C7CC17F3CE2AA55ULL, 0x1F7A37BBB75EC8E5ULL, 0x2EF9AC78865DBE6FULL, 
            0x1621F5C1961C9B45ULL, 0xAE8FB4310126F5CEULL, 0xEE53137D1CE5B41AULL, 0xC822357EC5E79424ULL, 
            0xD3CF7F1C105F4A01ULL, 0xD52412ACA29979BCULL, 0xE69EF1D17F33384CULL, 0xE6C12458C4C528AAULL, 
            0x5D8D9C99326ADFEEULL, 0x7CA5FE2B398BA9C5ULL, 0xF4575BD98C93DE62ULL, 0xFCB59CE024053A94ULL, 
            0xB834EB7A22A89BBDULL, 0xDDB25E85FDC36184ULL, 0x1CE378838B08399EULL, 0x812FDB489BEC5981ULL, 
            0x6087397DD0D5BC5CULL, 0x2D74726D26478113ULL, 0x6A738E7E46323320ULL, 0xB4698FCB6A200C46ULL
        },
        {
            0x76FB6489E00D8122ULL, 0xDC305777312D6CC8ULL, 0x6F4872898A751501ULL, 0xE7F025B2C2518441ULL, 
            0x627CDCE01D6538A2ULL, 0x4E122A585446AFBCULL, 0x117F39BC6146917FULL, 0xD8D95A9780711674ULL, 
            0xE65640269D2A8260ULL, 0xE6264B41DB570765ULL, 0x035184587503310DULL, 0x9D2AAFBA34673A28ULL, 
            0x493054F5F4D23A3EULL, 0x89CCD9E24B8E8946ULL, 0xE94B2710FF8E4C03ULL, 0xDA13D4BC3344C299ULL, 
            0x7FD2C2D1FA04D243ULL, 0xAC2F5143359A4275ULL, 0x35E0611E592C9C5CULL, 0x7E6C20A041891B63ULL, 
            0x290D98B943C20C0DULL, 0x3EF07322924C0DB9ULL, 0xD96F115BA7BDF92FULL, 0x129733F243F47A33ULL, 
            0x465D15B4850F4E0DULL, 0x139FFED1DBE05E71ULL, 0x5A1D50E2F0DB90B2ULL, 0x99A3A31EEBDF4D89ULL, 
            0x0C8B4CD3B5570335ULL, 0x16030488B6DBA34BULL, 0x1935DE27244619AEULL, 0x2B0DED293458F901ULL
        },
        {
            0x7D9727F3F9C61422ULL, 0x1B542408D2FAE8BCULL, 0xD58D8204A6188911ULL, 0x21709589983C1212ULL, 
            0x542F81A3B03BA00DULL, 0xECBCFA24F614EB31ULL, 0xEE09C4723F5DAC4AULL, 0xBD22276418C611A6ULL, 
            0x794A0AF20D63CC0BULL, 0x5E8CE28F0C96E4EBULL, 0x0827BEB5EC1E2B0FULL, 0x95088A2B01527FFDULL, 
            0x78377A83B57AEB15ULL, 0x5D99B2AFD9BA5F89ULL, 0xE3663543ED3BB1B5ULL, 0xCCE5FE7EE33F1CA9ULL, 
            0x0D5871E85253CB5EULL, 0xCF40DCBAA9672115ULL, 0x6DC9DC36F5EA29E7ULL, 0x0DF6E6892375CA0CULL, 
            0x5F0F4724EF3DA1FFULL, 0x0DB6A4994A1AF09DULL, 0xBEAFE1A430389170ULL, 0x15CCA11593DE14B2ULL, 
            0xF73016E1A9935B5CULL, 0x749FA8DBCD79A177ULL, 0xAFF0878F53F5AD0AULL, 0xD0CBBA934B023D59ULL, 
            0x95C9AB95B51FFADBULL, 0xECC74DFEAE4E83FEULL, 0xCCEEC48FD379447AULL, 0xB9CC0A3A0F1FCE61ULL
        },
        {
            0x328026299BF35AC3ULL, 0x1730F4377CEC3A8EULL, 0x5E136DC78F9304E1ULL, 0x1830C5768080232AULL, 
            0x87EB3F157FEEA8E0ULL, 0x5996EEDF1D4E1813ULL, 0xCB73B922ED54035AULL, 0x81437305FDD6403EULL, 
            0x939FD5E275C0C275ULL, 0x89C2B84F943691D9ULL, 0x4430092DE1995407ULL, 0xDBFBED853878105BULL, 
            0x27934FE2EA229946ULL, 0x231EF1D6E7D81A37ULL, 0x13A6698B53FEC7AFULL, 0xA3CD5FB9A4E0A3C4ULL, 
            0xB7E01839D77EDD30ULL, 0xD8279431180369A3ULL, 0x0531C8AA485FF43FULL, 0xB1ADBCDBFE08F94DULL, 
            0x9BA4CC0BD0161D26ULL, 0x463C1E9D9567E02BULL, 0x666D28BB1711E001ULL, 0x88906C0DB6035E80ULL, 
            0x23F47EBF4713D252ULL, 0xBC6B5CAB902D3403ULL, 0x220EF033DA319B92ULL, 0x7B04EBD2D4DF76C6ULL, 
            0xC98424EF914FD531ULL, 0x659AC0FB94893167ULL, 0x7759DDF29F1ADB1BULL, 0x00E39293BA6BCC7DULL
        },
        {
            0x353F968866EB9912ULL, 0xD059A4B6C796D512ULL, 0x230A1BC52066B4F6ULL, 0xC02D2708674495D6ULL, 
            0xCD0FFDD6435EA31BULL, 0xB200F0269E81E9FDULL, 0xB715E94D3F5F21F5ULL, 0xBF24170A8F51A9E3ULL, 
            0x875E69B0D1F3833DULL, 0x6DFF9F16621AC6E5ULL, 0x9F59EC8A21706D21ULL, 0xA208BE2935258F5CULL, 
            0x3103ACBF32EDDA24ULL, 0xBC3301BA86CB5860ULL, 0xE9B02B0F1731FA27ULL, 0xE914A83AB90D2A60ULL, 
            0x7D04AE9911F47AC7ULL, 0xF44FBCE0D6C59D3DULL, 0x4C3F5AFD3F630180ULL, 0x13DD2CC40579FFB7ULL, 
            0x879A8905A1C1B94FULL, 0x452193C9FCDA276FULL, 0xB75CB428A7A7EC8BULL, 0xD7267AC2CE735AFBULL, 
            0x7AD019746A1F02C9ULL, 0x211C982BBB8239D9ULL, 0x84E60BD7030F3018ULL, 0x1F46F452D225B6B8ULL, 
            0x48803C3F14EFF70EULL, 0xB5FD394A50BE90DAULL, 0x321C581B98BFE87EULL, 0x323D68E017CB0C47ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseCConstants = {
    0x1B12A937BB158AF2ULL,
    0x6D298BD2E64E813CULL,
    0x721FF4CB3FF3B401ULL,
    0x1B12A937BB158AF2ULL,
    0x6D298BD2E64E813CULL,
    0x721FF4CB3FF3B401ULL,
    0x6046F9DBEE3AA85DULL,
    0x1726D0B18A316F8EULL,
    0x92,
    0xAE,
    0x78,
    0x9B,
    0x83,
    0x11,
    0xAD,
    0xF5
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseDSalts = {
    {
        {
            0x3A82451319D9CEC9ULL, 0x9F92945F879E1583ULL, 0x44B08D3E7DF1194DULL, 0xB546F4C051C6DAE8ULL, 
            0x2E2D760A77BB6AB4ULL, 0x410DA34A6D243B2DULL, 0x22742138ECB2E7B3ULL, 0xC9CD15AA28E53615ULL, 
            0x12B61E92B4F35B80ULL, 0xAA3F715CE92590FEULL, 0x0E6F8F5B185E6BA5ULL, 0x6867DEC3AF5E99E4ULL, 
            0x7D9D2A3910042B59ULL, 0xC8EAF210F0A1DAACULL, 0x90BBE20E23541441ULL, 0xC4C25C44184BB9E3ULL, 
            0xB8920903CB30375AULL, 0xC2284ED287FD5DDEULL, 0x59FB8B7ACE6B42F3ULL, 0x5D51048DFF6428C4ULL, 
            0xFC68B56368BBE270ULL, 0xD61627668CA643C0ULL, 0x71CC7C87C65D72E1ULL, 0xD0BE5AE1B4EC3BC6ULL, 
            0x3C832C53DBD74246ULL, 0xEAFA897B3B7CB3E4ULL, 0x6F070E2459262955ULL, 0x2AB2D633638EFCC5ULL, 
            0x79CEF9579632F66BULL, 0x1A6972241C81147EULL, 0x61425C46364DC91BULL, 0xDCF8FB6C22F83DE7ULL
        },
        {
            0x0458510ED3E8F73BULL, 0x217425F8240B4FD5ULL, 0xD3315C5E345DC34BULL, 0x75384D481AB1CCDDULL, 
            0x0B6794ED3CC73FDBULL, 0x8A9F22DCF00A5C1BULL, 0x7AB6E2D82CC85F7FULL, 0xC2EE40567E60C840ULL, 
            0x9077A64731A7410EULL, 0xF606443A17FE0A9FULL, 0xE80F0A8E696CEECDULL, 0xA0151B3C1BD50F70ULL, 
            0xDFCEC6FAA603184CULL, 0x0D9A412B4E9ECAD7ULL, 0x40B6C43F5455BB18ULL, 0x800FB980E24D995FULL, 
            0xFA56B996833CDE68ULL, 0xDF37AC341F91F5B8ULL, 0xAC566FDE3D02C3E7ULL, 0x98FBD12C741A94C3ULL, 
            0x0AE741A59F2BEDFFULL, 0xEC5BDFF6E822780CULL, 0x6960D34382250F5EULL, 0xF66F953B0149AF3BULL, 
            0x5EC973DFC27A90B7ULL, 0xCE57D0092C674BD8ULL, 0x08070305EA7C0D21ULL, 0x39F477B37C27FEC2ULL, 
            0xEFD82C8A37718B3DULL, 0xA6DCCF17A99AB73BULL, 0x3764B79E5FA07898ULL, 0x74F794DF4F089EF8ULL
        },
        {
            0xD12F4509C4B46266ULL, 0x760C84292BA5E41BULL, 0xC07DAAED9E75D46CULL, 0x497FB593310E3611ULL, 
            0x661E137D4E1E9895ULL, 0xFDE64320EFF2CE77ULL, 0xC8F3B5ED0C1BE72DULL, 0x0579A4DF3B3C6E18ULL, 
            0x12D91CBD246917ADULL, 0x07DD047E80C2B208ULL, 0x3329D2F5F3545431ULL, 0xC51B2352344DF819ULL, 
            0x8791003116624E4BULL, 0xF516D21F8369FB6CULL, 0x42C38F095D534E45ULL, 0xC6FB73602D9C57B3ULL, 
            0x02071ECAB3A5B338ULL, 0x95BCFD2459AE8B82ULL, 0x193D416CE968ABC4ULL, 0x042E0DDC37D1E3DBULL, 
            0x9DCCD5652C3F662DULL, 0x1CF4B1851B855CD7ULL, 0x068C27821AD431FDULL, 0xCFF1F923388934ACULL, 
            0x3F237CC751DC58ECULL, 0x13A2C0B3121245B8ULL, 0x1FCEA70A84C55C9CULL, 0x95BCDA555F2AD98FULL, 
            0x77AAD9D4C15AB2BBULL, 0xD39A7875F4CF0D25ULL, 0x7FC4FFC1F6274D55ULL, 0xE5DB75054AAE7879ULL
        },
        {
            0x398F81505E898A18ULL, 0x8463096B224B5217ULL, 0xD0B6FC1A401B0577ULL, 0x696BFA92722C4237ULL, 
            0x8FAF798ED7051F12ULL, 0x4F57BCCF8374E577ULL, 0x892D14E9A5472FABULL, 0xE9904FE08B71059EULL, 
            0x5574938BD500F0D2ULL, 0xFFCB35E16B10EE44ULL, 0x315B5B30C7F89B57ULL, 0xDE2124B33F33A367ULL, 
            0xAFEFFAE5B02DC3C1ULL, 0x9113531799B7AC7AULL, 0x5B761F3F2E32C180ULL, 0xD1288299BF022D8DULL, 
            0xA8780D7A5966666FULL, 0x9115BDE2535D4562ULL, 0x20E039D16A02F793ULL, 0xF742757345D600E1ULL, 
            0x1992A91433331F0AULL, 0xF3CB4B04C7E18BA5ULL, 0x78F61A1038642491ULL, 0x1EB80579D0FB0493ULL, 
            0xE9616A35CC6A63A8ULL, 0xA8FE0B04C291A5E5ULL, 0xE649CA23BA215A09ULL, 0xF451A3D02AF4FA3BULL, 
            0x93E4493292A9D89EULL, 0x4AA15594018AB260ULL, 0xA35865EAB5039F2EULL, 0x7A8913CC2B12BFC6ULL
        },
        {
            0xFDFC15ACA38C00EBULL, 0x45B5FBD192253B32ULL, 0xED1A797754A51614ULL, 0xF420BB6CFB6AC2CCULL, 
            0x071255D1BC025AD6ULL, 0xE959F0934BE3F783ULL, 0xC1AEAC3988BCF051ULL, 0x1D6EF562555DF43EULL, 
            0x9663C36EAB7E218DULL, 0x57B0220103A3D709ULL, 0xD0BD3A506828E6FBULL, 0x22A8C6A7EBAAB181ULL, 
            0x210FD8FEF8F4DB77ULL, 0x4B1905B635D11969ULL, 0x35B08889D77DB8C6ULL, 0x8C99DCA9DA8FC3CFULL, 
            0x684B87E31DA111ADULL, 0x4E8BEC112FEFA480ULL, 0xFA16C5D4F2F5D54FULL, 0x9ADAB766BC68B306ULL, 
            0x63DE4A106B8943C2ULL, 0x184E46AA0C5EE4ACULL, 0x592A5C710E1EC2CFULL, 0x3AEAEBB1D7EEC189ULL, 
            0xD770ABDCC195516EULL, 0xC3BB37301549DA92ULL, 0xF9C2CA72838B5C25ULL, 0x43016B3C6BBF78DAULL, 
            0x72B4E66C682B376CULL, 0x3A589DAE4DAAB217ULL, 0x920DE0365ECDB3C2ULL, 0xA11FF99492464272ULL
        },
        {
            0x15D199CFD4B4A706ULL, 0xCF80809A37BFB7D2ULL, 0x4FFEF3AD9AE6E120ULL, 0x24EC8C3D7FE09DBEULL, 
            0xB286914B1EFB7BB9ULL, 0x343059CDD6AF24C8ULL, 0x55F01A73B38A4101ULL, 0x79227D2BEDB22439ULL, 
            0xE1BE44678B6A4553ULL, 0x30D892AC25B34D40ULL, 0xE5E5D7E0B3D9DBA3ULL, 0x99A0DCEA09BE4BE9ULL, 
            0x57216427A78F2591ULL, 0x51F9698090E78822ULL, 0xDDC580CF15F61863ULL, 0x3CC60999BA8CB8E8ULL, 
            0x6B15885000C2FA97ULL, 0xD74A853F78FA4CB4ULL, 0xC6C479AC6DF2448DULL, 0x7A777B9326B7525AULL, 
            0xDB687398E3D04864ULL, 0xF08AA78B869F5AB6ULL, 0x77BADA1A11176FB0ULL, 0x8DB2BDFB88FF5A8FULL, 
            0xDFDF02B1C4666755ULL, 0xB9F61DBF363CF386ULL, 0x520147718E141D62ULL, 0x4C01AD3BD62EB5DCULL, 
            0x3C31C8C0CBA7C5B0ULL, 0xAFA7ADA50AD2D921ULL, 0xB2552139BF90C348ULL, 0x8F6F9BF7DDFF37E4ULL
        }
    },
    {
        {
            0x587BDD6B938A37A1ULL, 0x7B0738F437105D28ULL, 0x2E8761FD2035E949ULL, 0xDD934EDE33103FEFULL, 
            0x48A510F62629EDD7ULL, 0x70B1D1AA3910E9D0ULL, 0x0B26B5184F4698CFULL, 0x5923CBDFCF44A6F2ULL, 
            0xF2082651FDF898FFULL, 0x38CF7EF1CF83C74DULL, 0x7084DF46849D721AULL, 0x34568CA54793CFABULL, 
            0xBCF9BC0098A9E3A0ULL, 0xBC08D6FFEFFAEC1AULL, 0x7C6A4245F59BCA4EULL, 0x15CC243B8B559613ULL, 
            0x497A31CADD1E1C84ULL, 0xB98091305E8B0F84ULL, 0x30745293F7B14CD0ULL, 0x123EDC0252CBABB3ULL, 
            0x3DB4BCBA943C0D2DULL, 0x1108F7215FBB8A53ULL, 0x0D8AD942158FF7B5ULL, 0x3B21136AB36EC7D6ULL, 
            0x046AC564547A6EF4ULL, 0x15322CBEB2692B50ULL, 0x9FD85BC5C5F606D2ULL, 0x569DBF6361DDB591ULL, 
            0x3F189ED677E74B13ULL, 0xB59686FB51E09ED8ULL, 0xEF215A6BB201B3ABULL, 0x19D2C9BDB699123DULL
        },
        {
            0x5F97EA224B1A0DA4ULL, 0x6FC75F26351AA14AULL, 0xF9BC515287C7D8DDULL, 0xC4B6AE906CF1977AULL, 
            0x8CFE4B9009FC8780ULL, 0x465A8AA8D259AD82ULL, 0xD4A7C431CC5BB467ULL, 0xF585565F803AB923ULL, 
            0x0F859FCAF58FC55DULL, 0x9D4B0AF9B2F7FF5DULL, 0x11886E63288EEEAEULL, 0x019F0E5D7EBA06B0ULL, 
            0x8D38348FAFF2993EULL, 0x04B02B3C0B316EE8ULL, 0xB67487015119CD48ULL, 0x6B849C353361E864ULL, 
            0xB448D610145224E8ULL, 0x2455DA50F326FF5AULL, 0x3C545D6C37D706D5ULL, 0x1ECB6B01B9D1361BULL, 
            0x8C3DC58443E5C5E0ULL, 0x13DBDC31407097FEULL, 0xC8749C35658FFB2DULL, 0x33A0D7D20E3EB566ULL, 
            0x9ACC0ED965C4852BULL, 0xC707E51C01F7C984ULL, 0x1CEFB422C4E54DC3ULL, 0xB9807640F80CF922ULL, 
            0xED1BC85A173388A6ULL, 0xA4DC3A2651949337ULL, 0xC43E8BB9C48218E3ULL, 0x46C1BD6F4997EFCCULL
        },
        {
            0x652046668C23CA20ULL, 0xB5748165F78CEE67ULL, 0x33A93E0CC659807EULL, 0xE468CEF37ADC33A5ULL, 
            0x86D03493E0C4F621ULL, 0xDBD48F76BFD6915EULL, 0xD45342F7A4906283ULL, 0x453C44A26E7CE4F2ULL, 
            0xD5CE1159E9DFCB1AULL, 0xF673B3C72C3289EAULL, 0x84A92C1F13BF5EE0ULL, 0x5D9104C6ABD634DEULL, 
            0x1C2F9C374CE832AAULL, 0xBDB3A2E29D5B01EAULL, 0x04E9ECE8E43D03C6ULL, 0xBC3198080C00A749ULL, 
            0x392D3D6D8CB555D2ULL, 0x668C3145FF046BF0ULL, 0xA143D388A1E3950AULL, 0x30F92749E5E620A0ULL, 
            0x45F94B71BCF27460ULL, 0xD9224D9F3EADB86EULL, 0xCD08983534CC776BULL, 0x623F24DDF97D8BADULL, 
            0xE43CF0BF65ECD0C1ULL, 0xC1E9730880F15A5DULL, 0xE7E9420BA99A8562ULL, 0x8D2B2B0C5B4D24A3ULL, 
            0xA6FF3BFDD1AE5BD1ULL, 0x396CFDFC23AD7705ULL, 0x85C1FF9A17494BA0ULL, 0x4EA02BFDEB43BB97ULL
        },
        {
            0xE41D6558C2DBA628ULL, 0xF7905BBA7F5C3FDAULL, 0xC9A74E2AA0EB58E8ULL, 0xDB68C2D3AC0446C3ULL, 
            0x46BBFA4526EF06DAULL, 0x821BCB0A77F4E963ULL, 0xB70C24B52198949BULL, 0x9CE73E7EBDE29624ULL, 
            0xF5B47EC3EE588669ULL, 0x71F5D25B5D03B08CULL, 0x59846C5BD1F16AA4ULL, 0xBC864635CEC276F9ULL, 
            0xDE395533689372A2ULL, 0x7C3CD42DA6EAD59DULL, 0x527C163EFE675F25ULL, 0x643123F90D6C92A9ULL, 
            0xE3122FC917D1D511ULL, 0x0DEBC851EAFF05A1ULL, 0x62BC647A893AEBD5ULL, 0xC3265C9609116813ULL, 
            0xFB67323E9945BF7CULL, 0x55A3F16980AAE14BULL, 0xA0648791F53FDDC5ULL, 0xD7F50AD11D7EE0ABULL, 
            0x7DA1AE17B42E96E8ULL, 0xC6BE9B88C55C9289ULL, 0xADBB72BD3B7807ECULL, 0x8FDF8958E255069BULL, 
            0xB3B4F1C4E7BDB91EULL, 0x8D9EF37BFBF5A30BULL, 0x98B2A43F744AD1C4ULL, 0x285049745A73FF8FULL
        },
        {
            0x79D14D6561D80A42ULL, 0xD1C0E42D3FF71F95ULL, 0x8D9D5BF1F7095B50ULL, 0x9C5CAA0810300817ULL, 
            0xFBF601F1AA788093ULL, 0x2E6F11EAC42F7DC7ULL, 0xD2BBE6A8BC1F68B8ULL, 0xA8C60819442979AAULL, 
            0x1998714D465A169CULL, 0x952B66362EB6C7A2ULL, 0x2205125CB9743768ULL, 0x299AEA654D7FD625ULL, 
            0x46D59BF9CA148171ULL, 0xF3B8642610067423ULL, 0xA25965B00BFA4343ULL, 0x3054F2174406601AULL, 
            0x7830A8AD2629B461ULL, 0x5A8B1E2FDBFAE85AULL, 0xD33D5849F270F4BBULL, 0x54C6568C8336B651ULL, 
            0x4E9B92FEF3F60110ULL, 0xDBFD853ABC60C644ULL, 0xB8BC4D5ABBA07023ULL, 0x5D0168CDAFF0A6ACULL, 
            0x98DA778CE2C23588ULL, 0xA794B8411BE49CDCULL, 0xC375701D5D6AA95AULL, 0x4F157B76DC2A94FFULL, 
            0xA7832AC3BDF0B907ULL, 0xBC8295CCFC323A9CULL, 0x984CEAD7E79C3A9AULL, 0xB4B23AF03EA48E60ULL
        },
        {
            0x11DD0356DF8BA2F0ULL, 0x729DE4DC178A726FULL, 0x4E95A47F8A1DAF2DULL, 0x00238B9F32E86ED4ULL, 
            0xA4643FCD981D9359ULL, 0xD37C3C273F49E1A9ULL, 0xEA970D521C5549FDULL, 0x79DB9AC9E837CA37ULL, 
            0x16C155E0EE123609ULL, 0xED6FE1ADBD5BD5FCULL, 0x8C2B0EBF67B98420ULL, 0xE2825472A3BAF96CULL, 
            0x8E81709771ACEF13ULL, 0xE8B937EABBECF0C8ULL, 0xD8559C728F69BB61ULL, 0x534F8059B4EAA0ACULL, 
            0x4CE1322FF8E2985DULL, 0x8AF965A74A0D673AULL, 0x35B20EF3C1D3BA09ULL, 0x56FE51A01CF34BCCULL, 
            0xF8D3DF28157D2171ULL, 0x8A413EAB27620F4DULL, 0x4F6819E31A24D821ULL, 0x863B712773E3376EULL, 
            0xE04584EE71B11DD6ULL, 0x7B07C869665F19B5ULL, 0x93ACD8AF6366CBA4ULL, 0x26B27E144FB0EB94ULL, 
            0x2B4BC2D278D798B2ULL, 0x9DAFEA7156FF95C3ULL, 0xF0B67C306EFEA27AULL, 0xA8DDFCECD1A21A47ULL
        }
    },
    {
        {
            0x368B41B41E43DC26ULL, 0xFF7B1194F1092F8CULL, 0x1882EAD09C712572ULL, 0x024EFF4A9F1D748EULL, 
            0x89ABF2500E1EBE13ULL, 0x270B8798A4C3EE57ULL, 0x952E15E07563E2EFULL, 0xCDD932C89732BEB0ULL, 
            0xA3F1F6825F346B8FULL, 0x460B9903C7198B17ULL, 0x62118BA811999A49ULL, 0x665C85D16BD1202DULL, 
            0xFA5B7018F208B2B2ULL, 0xF4A400E85EF68A83ULL, 0xEA1C470C2DCE62FFULL, 0x12343BC6BB598975ULL, 
            0xEDDF8B189E7D2EC7ULL, 0xBA4FDC265B812C8FULL, 0xDB7DABF191AE176CULL, 0xA9E0A17531612FFBULL, 
            0x88644429375D6C22ULL, 0x97B806544413D291ULL, 0x13177182307FCDBDULL, 0x9304983D31ED1ED9ULL, 
            0xD71BBB63984E6661ULL, 0xCB119D8DA37E8272ULL, 0x7F9B68FED91688ECULL, 0x54685D3EC17C23C3ULL, 
            0xC4ADCBDE3B6CBFEBULL, 0x883725A1849B254EULL, 0xD2B7FFC7F002E4E9ULL, 0x7FA49C0377FD4467ULL
        },
        {
            0x98C223A276262BDAULL, 0x2025645D155C1BB9ULL, 0xEBC893EBBBE10015ULL, 0xCD82BCD5E6A8ECC4ULL, 
            0xDAE9F11DA6089D97ULL, 0x7CC1607E277E5380ULL, 0x1A9854EA57095116ULL, 0x0506FFD9E2F55436ULL, 
            0xF8EE79AC4EF553BFULL, 0xEFEE75A0DBD12117ULL, 0x86B2CFEEA5264C36ULL, 0x1982163834FB6426ULL, 
            0xC40B5A7B1BF1E366ULL, 0x406C4EAA8787E028ULL, 0x80E403FE67EFF7EBULL, 0x79D71C57598B2708ULL, 
            0x223DBF79F84EFCDCULL, 0x8F7005FAAF9C6855ULL, 0x1971C3524EBEE09FULL, 0x5AD505E9224972B3ULL, 
            0x2FC6F9DE0823D52FULL, 0x257186E00AA719B4ULL, 0x2EF7C73EFE46121CULL, 0x15C1188AF9BC1850ULL, 
            0xA7E6EB22E0A675DFULL, 0x3CEC36E913AC0E7EULL, 0x92999E9A00DF0F5CULL, 0x03C0396433C6F0F9ULL, 
            0xB49DDE8693887458ULL, 0x56DE9DBD9B4BBEFAULL, 0xC7FF08355B9A3E7CULL, 0xFF7D31BF7A0702F4ULL
        },
        {
            0x23A926F4D8873000ULL, 0x375955F431C07694ULL, 0xE064A432355DAB08ULL, 0x19F3AA597B556471ULL, 
            0x45D1B9070579ACDFULL, 0xB751A54A21052BECULL, 0x769C3E56BE2C5555ULL, 0xD890CD6B2BDDC58BULL, 
            0xE5D0CDB558DAAE31ULL, 0xCB266395AEAEB5CFULL, 0x7D4CE3587CCB5879ULL, 0x54DD38FCBF366C08ULL, 
            0xFD10DD2343C41AEEULL, 0xCF01230904D5E976ULL, 0xD76FF70C63ED0423ULL, 0xCAF40F7066B1BB2AULL, 
            0xE5A22DC25BBB59A5ULL, 0xFCC4C3A99D02CFD6ULL, 0xE06040398DA53040ULL, 0x2703BBBD0EC7CC09ULL, 
            0xCA1A580B136BDCF4ULL, 0x2C5E42461AB82425ULL, 0x4A79E31B61B9D568ULL, 0x983ADA4452531DFCULL, 
            0x38406B3A08BFAE6AULL, 0xC825704D50179BC8ULL, 0x14951DF0FA97C365ULL, 0x15464F0A22A467B4ULL, 
            0xAAC381D3AA5D1923ULL, 0x888BE263C0DA4330ULL, 0x19A8A60AA7D17E41ULL, 0xEFFD144105069734ULL
        },
        {
            0xC00E52B3CDE0394DULL, 0x5C460CD330F1D991ULL, 0x1B30A4EAA8BF91A3ULL, 0x79AC18DE813F7B0FULL, 
            0x3958F68D06EAF4C2ULL, 0xE79E39D5C00C90F8ULL, 0xE1F1D4A4BC2377E2ULL, 0x78ECBF3FAF05EF68ULL, 
            0xBA8D7E959329DE18ULL, 0x7E9BAA991CEB7F4BULL, 0xD810E8E0CE33E227ULL, 0x06C0225A80775F2EULL, 
            0x7C203064B929A019ULL, 0xF6102984B2661100ULL, 0x8E5F4D6AC86BC8C8ULL, 0xFFD1D68A601EF2F3ULL, 
            0xA2687DB26A61273DULL, 0x1ACADC6C6735806FULL, 0x7E400A96D951DD43ULL, 0xF87A22A0E79FFA5DULL, 
            0x1C1D1AD1EEB518ECULL, 0x9C337ED4DB54ABA6ULL, 0xC1BF8C9AA927BB66ULL, 0x51E5A9F48A6B3E80ULL, 
            0x4F66F5B32D5C2AF7ULL, 0x4341BFB06B03B0FCULL, 0x3B6EEEE0863DC026ULL, 0x1FF641B61913CB07ULL, 
            0xFC3C2224DD497864ULL, 0x3AB68F731878A23FULL, 0x5EC75B7A22105507ULL, 0x83C9A8CCA2316960ULL
        },
        {
            0x91A88113562F8995ULL, 0x530D0D1AF743AF6AULL, 0x2862467BCEBB072EULL, 0x55A205C5CA048AC6ULL, 
            0xD92F90F1531F7377ULL, 0x98EFD613FC317267ULL, 0xC9D15A27A6B077D1ULL, 0xB67C5338B3D86218ULL, 
            0xB1A064574F460F65ULL, 0x2BDCB4655982D557ULL, 0x6DFC005FF968436BULL, 0x8F9AA2B651E04C5AULL, 
            0xD5849A8712CC942DULL, 0xFC46FC6232852613ULL, 0x32AC0CD82DA8D5C0ULL, 0x00AA5D6F87F5BFC2ULL, 
            0x64EBFB8E6FFD9A77ULL, 0xAA420EC8C21524F1ULL, 0x2029B09023D852CEULL, 0x4E76DAC88D6EC576ULL, 
            0x4C44DE248EADF004ULL, 0x9E8D957CAEE3F5EDULL, 0xE3419105192E0ED8ULL, 0xB46F5ECFD8D2E4C4ULL, 
            0x0FD01FD2A8ADD174ULL, 0xA854E72C57BA1AE1ULL, 0xC97B02AA245B91ADULL, 0x54CD5330A8776D44ULL, 
            0x89A4D7120E352421ULL, 0x3AE837C172BE69BFULL, 0x0948CC5C5A358622ULL, 0x4EB3CF37BD74E959ULL
        },
        {
            0x47D8716F619D20E3ULL, 0x6C3B03ABFFE32F77ULL, 0x6714084D3F960962ULL, 0xCCAD3374B1E07AC2ULL, 
            0x41044558ADCFA789ULL, 0x6F700036AD543C00ULL, 0x16C937D2D5E8768BULL, 0xC5AC60F393537AE0ULL, 
            0x1040050B0E60CDB9ULL, 0x5E1495CD015491D3ULL, 0x7B25F722CE17CEB8ULL, 0xBFA1C3C703908D72ULL, 
            0x86FE6D42B7FA4DC5ULL, 0x8791A6C19881579BULL, 0xEAF153D2D0D991FFULL, 0xD49B56663687105BULL, 
            0x7D1E40BCF4D8AE6AULL, 0xBC5A31BA771CDE98ULL, 0xAF261F47F6ACBD88ULL, 0x0E3378F075197757ULL, 
            0xCE2234707AEA79B0ULL, 0x0AFA004E3CE8BA2AULL, 0xF9E3DE5F17E097DFULL, 0x857C66E27866D810ULL, 
            0xE7566027771807E2ULL, 0xE55693DA8E828116ULL, 0x95611810AC189042ULL, 0xEC14F4AB91B45E39ULL, 
            0xB94CFF3B31481389ULL, 0x60089619E2B6D35EULL, 0x55B5030644EFE7CFULL, 0xA92777EB594100EAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseDConstants = {
    0x2A4CE9E9A8D86798ULL,
    0xD80D39FED48EEFA6ULL,
    0xF97875113F2A5100ULL,
    0x2A4CE9E9A8D86798ULL,
    0xD80D39FED48EEFA6ULL,
    0xF97875113F2A5100ULL,
    0x954B60B4C8806F51ULL,
    0xA79B316277E9A5E0ULL,
    0x70,
    0x0A,
    0x6B,
    0xC1,
    0xE7,
    0xF6,
    0x10,
    0x93
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseESalts = {
    {
        {
            0x3E24C1E9FC2E6AF2ULL, 0xB0D2E388277DB8B8ULL, 0x04A807472BD498A1ULL, 0x69A540A898797938ULL, 
            0xCE6AC9479EFC50A4ULL, 0x8327819B8DFAFCA3ULL, 0xCAC2150C18A3A906ULL, 0x30F05756FF84FB5CULL, 
            0x18B7F515FE905B2BULL, 0xEF8E288BF9701958ULL, 0x01E4BEFF3611C73CULL, 0x776EFA8ED9CA6BE1ULL, 
            0x5C4A1801FBBEF2B1ULL, 0x4BB4A20C976212E0ULL, 0xA779F27BB556679BULL, 0x2ABF6A5FB015142CULL, 
            0x05D6462F3F581656ULL, 0x718D0558120F6BB2ULL, 0x638C1AC295D51CF0ULL, 0x32E5A6AC532F4CD8ULL, 
            0xF43FD0E2C4F645C9ULL, 0x46432CC670D555BFULL, 0x4EF2733652E84485ULL, 0x620332CCE2A2A188ULL, 
            0x8A77857BEB714E32ULL, 0x475302133AC1F527ULL, 0xEB1FE0E5082B6756ULL, 0x451056ECDE480E6EULL, 
            0xC3B830592FD658E9ULL, 0x73DE59F7D4B30450ULL, 0x38D405AEF65B088BULL, 0x8DA1E3CD7B03DF61ULL
        },
        {
            0xFBDA141F9B235ACCULL, 0x43EEDED4681EA948ULL, 0x738BCC2012E3CB8DULL, 0x3F3002CC186D2C6CULL, 
            0xFE596EBA5F82392EULL, 0xC699C4E6D48F7130ULL, 0x1B79FED82A96A6AEULL, 0xBC896B3029FF97F6ULL, 
            0x8026341CBE9DB91AULL, 0xB0F34B813FDD004EULL, 0x38D5122D378E4FFEULL, 0xDCD784FB1EC4CD68ULL, 
            0x6AA129C91151E6C4ULL, 0xF567C90B95449FCDULL, 0xBEA6BD8E3BDE9DE3ULL, 0xD1A7EE2F5E15345EULL, 
            0x5EA122374E39E4E6ULL, 0x1CCD4038548B7C96ULL, 0x17807A58F0ECFECEULL, 0x309151F57A12228EULL, 
            0x1C8B24BE44C59646ULL, 0x37E3175D1DCFCE64ULL, 0xE2A68AC2B954FCA8ULL, 0x63BF170D759D7D28ULL, 
            0x1A2D3F1184BCA36EULL, 0x99B7E6924B8906E9ULL, 0xBC9FA689DEEA46C7ULL, 0x6CCA6E6234E01520ULL, 
            0x233AA6ADD5075207ULL, 0x904D02FFD7682767ULL, 0xA936EEB53A9DAAF7ULL, 0x328C4EE53E4992DDULL
        },
        {
            0x90DAE508B6BF1022ULL, 0x5594A40BC9A0AC01ULL, 0x31D557B9E1CA80C4ULL, 0x604A4BCF5006DC20ULL, 
            0x90794DF2BE878239ULL, 0xD7BA3E3956F42A7DULL, 0x4E4699BD20CE1EC3ULL, 0x10961CFE91A55B3AULL, 
            0x2379D933524CCC99ULL, 0xCC0BC3E00BE2AA95ULL, 0x024D80CA35722D54ULL, 0x29D3FC6BE3B3622CULL, 
            0xD5CF4E2A0EF95CBBULL, 0x92655D171F09A2C6ULL, 0xAA0657DB601B0D1DULL, 0x2FAF818DA4FB4E66ULL, 
            0x7629BEB80064D7F7ULL, 0x3690551342FC01FCULL, 0x86C3A8E5F6D8CFD8ULL, 0xEDEA27981530ED30ULL, 
            0x839E107BC3B0E3B3ULL, 0xB8989F0D8D946415ULL, 0xD6234C3954203A85ULL, 0xABA268C90AC50B13ULL, 
            0x2984D4E5BDBD8865ULL, 0x5A9EEF96B25883C1ULL, 0xC848F0E82239FAFEULL, 0x0176592C69408351ULL, 
            0xE500D528D5D39346ULL, 0x1A6CF85C580C53C7ULL, 0x9DC557E2023CA6F1ULL, 0x842A74FDCEB3CBF5ULL
        },
        {
            0x919474521B62027FULL, 0xF8B1EFF14F3C09E9ULL, 0x3D1C1FDF61131BA0ULL, 0x45B77A938C6DA37EULL, 
            0xD8AF491DB44AA5FAULL, 0x329CCCE7D6F41154ULL, 0x37B516028E9E0467ULL, 0xA53A6FA34D6C953AULL, 
            0xDA5C42CB2CA00C53ULL, 0x1472F3335A530DA6ULL, 0xF610C30635DB71ADULL, 0xCC1F35106B930E14ULL, 
            0x62F10F8A5DE1FC3EULL, 0xAC9F4CD47D192DE6ULL, 0x997772BBB45EFBB4ULL, 0x6056C91FA107F5C4ULL, 
            0xF15669DA20C04156ULL, 0x7033EC225F8F6FFFULL, 0xC977D5435E60D504ULL, 0xC8823B8930CA79C0ULL, 
            0x5C0F883C713CA124ULL, 0xAA56F1D1F920DAF0ULL, 0x70579D5FB72E8C5DULL, 0xA48DCFEC4FA4D46EULL, 
            0x4AB3292FD200950EULL, 0x80BC89C88CA6376EULL, 0xB9889BE5A04C3D5AULL, 0x4672619401F8A0CCULL, 
            0xE3388940FB7819F7ULL, 0xF18483E6B4A9BEDAULL, 0x78D60E3816542385ULL, 0xE64C9217B3773EF6ULL
        },
        {
            0x29EFD1E79EA89E3CULL, 0x632F8792E57AA106ULL, 0xFF6B475304548F4FULL, 0x8B8CA7DCD1DACA57ULL, 
            0xD551B8831CF46FF2ULL, 0x3447D124E33457E8ULL, 0xC46F014F42008E0AULL, 0x89506B2F38C4F7F5ULL, 
            0xD057F032C70C9C35ULL, 0x5D66A2FC768B3992ULL, 0x7774B6630F03CDD5ULL, 0x0B2210101F7AF999ULL, 
            0x2CDDE8EBB113ED72ULL, 0x05F97C32ED9B3BDBULL, 0x13D83A37D011EB56ULL, 0x5BF33EB0BE53E964ULL, 
            0x2ED858CD53E96DFBULL, 0x494BC0E4BA22E3C0ULL, 0xE5C141D89C26E205ULL, 0x53C2E325758F0A61ULL, 
            0x4C4227B419797395ULL, 0x1B011823721B5334ULL, 0xA7DF7055D12D95F0ULL, 0x5835EFAEFDE2CC18ULL, 
            0x852366D10E54D9DBULL, 0x3457A9B51DFBEC80ULL, 0xB341F8F49371028CULL, 0x0D41BC486308F8B7ULL, 
            0xF0614157EE0EB691ULL, 0xBD5987F4A20090DBULL, 0x1735168AD3B729EEULL, 0x0A09994DA3CC6202ULL
        },
        {
            0xC66AA70A40E17BB5ULL, 0x2F4BBAC593BB2F2BULL, 0x783D463803146388ULL, 0xC66D0F9AA23A2572ULL, 
            0xF4CC772C4D802C5BULL, 0x246516042C7CC793ULL, 0xDF63E78A71E94485ULL, 0x29E81BC04A028B88ULL, 
            0x6C263044D0D4BA49ULL, 0xDD218B99C9D31D6CULL, 0x120F8FDF83857578ULL, 0x03F4EF7C2D5BBBB6ULL, 
            0xC752C3BDC76A4423ULL, 0xE52643D6A56D2FDDULL, 0xA62DBD3813166301ULL, 0x8F919831132243D6ULL, 
            0x811A3CFAC9BD85F0ULL, 0xFA32BC4ACDF18623ULL, 0x2CF3CFC7E7149768ULL, 0xEC58EFD9F93C69CEULL, 
            0x1839420507699A17ULL, 0x96743FE91484B12FULL, 0xDAEDB465D6EE377FULL, 0xCAA743F1A84F619DULL, 
            0x378D692AB753ADDCULL, 0x7BCE2AC8035BFF62ULL, 0x72E0C0714D4002ACULL, 0x6FF50D3620CB9512ULL, 
            0x7BEC5FB289614DD2ULL, 0x8F5D360422E8B47DULL, 0x23E2AC58A9C84AF4ULL, 0x764F45B3441D559EULL
        }
    },
    {
        {
            0xB69DC95FB9288C53ULL, 0x760F84A828DEBD1DULL, 0xD9A6ADD30A2F8A22ULL, 0xE961ABD80A75A55FULL, 
            0x24555C69941EA6C4ULL, 0x41E211D6D3E244D5ULL, 0x7CAF5CE37E0F0640ULL, 0x99235314CF6349E4ULL, 
            0x53D8EFE34EC9CCCDULL, 0xED216CE5FAEBDB54ULL, 0x1249305FD044AA19ULL, 0x094C4849D1ABB184ULL, 
            0x1278341ADC9595A6ULL, 0x85C8B38603230143ULL, 0xFA6AAA52DE770A3BULL, 0x4E9ADC7B7E84D434ULL, 
            0xF5FB89645E7EA0BCULL, 0xC3B95774ACB46C90ULL, 0x63DD02FEDF2C34D4ULL, 0x3B6E96D1343551E0ULL, 
            0x9A542CCE2E2780D5ULL, 0x4DE8188A1741C8DFULL, 0x3840BE7D77F9EB38ULL, 0x1EAECC827ED6FA1BULL, 
            0x10C733E046C50720ULL, 0x51A68BCC9CBEC6E5ULL, 0x5DCCBEED28A78D77ULL, 0x7D30DFA5DA6EE6BFULL, 
            0xF4D3F1CD587474E1ULL, 0xC37EA82B9AF71600ULL, 0x753A29FFFBCA6604ULL, 0x6AF9AB8DDA79F899ULL
        },
        {
            0x70AE765BEA7F1782ULL, 0x92F77CB69E96532DULL, 0xD65BEC8BE0DD73F3ULL, 0x968FEA23D9DF45F3ULL, 
            0xF2B425FF1D3F7CD7ULL, 0xB3AD91E772C2F6C2ULL, 0xF884A478A6E9AE14ULL, 0xA7E61BF854E3C46BULL, 
            0xD69D6050BA4D1B39ULL, 0x630CF6FE12D792F0ULL, 0x148837FDF2EE5DBEULL, 0x6D819DFF467291ADULL, 
            0x034CC75E931AC083ULL, 0x0710D45C47367356ULL, 0xF42F480F503ED64CULL, 0xC6DD7526E1B96963ULL, 
            0xE4C8927DDEB14CA3ULL, 0xE9DE7E0D3EFAFBDBULL, 0x63BD1186FA727991ULL, 0xB71F9C96E13B9C95ULL, 
            0xE8A6992017916769ULL, 0xE4D3CB9138AEB731ULL, 0xFD87CF317EB35BABULL, 0x4145DB7DFEC69C9CULL, 
            0x244446C31B3E8FE8ULL, 0xBB61320B5D0D4520ULL, 0x80F29A17064F9BD2ULL, 0x8D13786C6D4A79D9ULL, 
            0xDD1E726089419632ULL, 0xA94E80ECCA97761DULL, 0x1712EF6853427890ULL, 0x5D9B140CED63A9D3ULL
        },
        {
            0x117F0C0C8558131CULL, 0xFCCB2AA7E09D5DBAULL, 0x4909556CEE2672A3ULL, 0x3B83D3E0FE07FB69ULL, 
            0xC8B6CE7E41490B80ULL, 0x1CD94A2C81C24122ULL, 0x5EED3CB0A09C7404ULL, 0xDE26A9343FC65EA9ULL, 
            0x7D28B351DD481C2BULL, 0x5124A7F1F7023FEEULL, 0x0700EBFC2071595EULL, 0x92EED9E71CF33A14ULL, 
            0xEEB625193CD57DEEULL, 0xFB251436C6B26376ULL, 0x6EBD5D5F8C1F5AE7ULL, 0xF82842AFA01C45A3ULL, 
            0x92860AE29B92BFA0ULL, 0x0B5E382347DD990FULL, 0xF50D978CD270422FULL, 0x146146FDB3D79D20ULL, 
            0x006099EC0446F99CULL, 0x0363A30785B8965FULL, 0xD5BE6BA3BAF9096FULL, 0xC0D995D8CA97A97EULL, 
            0xFA2A8A9461B15C61ULL, 0xC3BE7AA784745FDFULL, 0xB9E32FE8ADC20510ULL, 0x26159867B2A5EE8CULL, 
            0xF48DB62F2B197363ULL, 0x03B381F498D1F72BULL, 0x67A605BD4B08A6D6ULL, 0x2B3AB608DB7668F3ULL
        },
        {
            0x5F4B2981E11B4790ULL, 0x8C66791071580375ULL, 0xC19FB9956A40546FULL, 0x79F676C573958A70ULL, 
            0x2077F8E46BC8B4B8ULL, 0xF5D08D62C4A64044ULL, 0xD9379FEBECBCF547ULL, 0x7B55E54F3D0D75ACULL, 
            0x44C74D08A2313437ULL, 0xC4294DC10FCD3593ULL, 0x79E54CCEB54C6E98ULL, 0x5D9201D4F1898E47ULL, 
            0xBBB71DE739BCC9E9ULL, 0xE0640736FA033130ULL, 0x8F45ACD5FF30A92DULL, 0x3B8EFBC7DA8EFB14ULL, 
            0xD9B9847E8F2D4BDAULL, 0xF38745006ABA11E5ULL, 0xFCADE0E1DF7823F9ULL, 0x05599A604C0AD1E3ULL, 
            0xAA4D09DA4FF592DCULL, 0x232A2BD0F69E218EULL, 0xBD038324A6C00832ULL, 0xE7683C4484F4EB51ULL, 
            0xF6146BDBA84DB298ULL, 0xA4FF79BCC6C0331BULL, 0x5681598EB7154278ULL, 0x4C413DE47E664FBAULL, 
            0x204A17EEAC0F1E4DULL, 0x7ABDFC92ACF95D84ULL, 0xC0AC1A6BE1D45B92ULL, 0x321E020F37DDE33AULL
        },
        {
            0x5588E800AD2DB0BBULL, 0xDA31020E281F541EULL, 0x0E4F9DCD4C6CB322ULL, 0x862A54C275F15D71ULL, 
            0xA0958E6B3EF54989ULL, 0xE22E6C4A497148DDULL, 0xAD96C96FB857FB54ULL, 0x33E84F957412C85CULL, 
            0x9846365CBFEF2D58ULL, 0x6D9E19E89BD1348CULL, 0xED34C97CD450F3BDULL, 0xA341C734AA7378ABULL, 
            0x2C8C2DEBDE0F9222ULL, 0x6DCF90B3A3AB8425ULL, 0x723EA178C59F857FULL, 0xCAF08C3B49E5394CULL, 
            0x2CF447D1497BD6ACULL, 0x981A0919F04F2C98ULL, 0x9DDDCB1A7B18254DULL, 0xF7E03CD97625DAF8ULL, 
            0xA364F23736480288ULL, 0x37456CBE5C95BB6CULL, 0xBA618206E5A538C2ULL, 0xB8DC4527C4ED777AULL, 
            0x86DC1C69F3230061ULL, 0x034A851DF577C260ULL, 0xD883721A38FEF5A6ULL, 0x6D86217751CB1BF9ULL, 
            0x307A9D245BF7B607ULL, 0x5BBD46BEF9C0D07FULL, 0x9E2C25B7CDE2C034ULL, 0x0E10993CB2164892ULL
        },
        {
            0x9D596EC0B86734A1ULL, 0xA9A956B6E9A9646CULL, 0xC9ADBAC08763C193ULL, 0x0E9A916468369C97ULL, 
            0x1F7024BD33B4FDB9ULL, 0xCF85A45FE09265B4ULL, 0xDF48FB070A683E24ULL, 0x068011F8EB8F79A6ULL, 
            0xE841B645D53ECB5EULL, 0x27CF80716D10B3A9ULL, 0xEF1D6ECF9C08A18BULL, 0x7889757B02F0C368ULL, 
            0xA4B125C3CB76F390ULL, 0x154B66F70342D6DEULL, 0x381CED4DE25E7FCBULL, 0x64C25AB61DD9E760ULL, 
            0x79767C7E6858411DULL, 0x1057A882CC2A6808ULL, 0x62817BB2B0B64C11ULL, 0xF69E3E40689605EBULL, 
            0x19B576150B2FC638ULL, 0x81A122F352D5E29CULL, 0x4F8406548E715E48ULL, 0xAD1D52C5CD31ED96ULL, 
            0xB2AB6276CEEFE0DAULL, 0x63F1A721A787B9B4ULL, 0x5F8824428A9FC825ULL, 0xBA1CEA4010BD635EULL, 
            0x56CAB59450E516DAULL, 0x1176F7D03D879E86ULL, 0xF918ACDDE2C0AA4EULL, 0xCBB8ABAE0D144659ULL
        }
    },
    {
        {
            0x1A82259521825A0AULL, 0x3F80F7C4729CD150ULL, 0xA390B92D6FE50549ULL, 0x5F6ADC362D345590ULL, 
            0x0BBB6ECC8E79664DULL, 0x1249D5A9C37D2FC7ULL, 0x490FBCCE620F8ADDULL, 0xFA0AB6D84086A62EULL, 
            0x22E9CC669CB482EEULL, 0xE6BCCEBCFC0C706AULL, 0xDFE409C6D49EB54CULL, 0x23B17C28D56B5E88ULL, 
            0x6A36A8EC2053F419ULL, 0x83AE3F86A3FBF6BBULL, 0x3C1C76D5F68E0BB9ULL, 0xE37700BDE1233B5AULL, 
            0x53F66B2F16810080ULL, 0xFB8A444111659CC6ULL, 0x6A4D7ECDA7E677ABULL, 0xF41A24281FD8A375ULL, 
            0x3003942748EA111BULL, 0x4E324C9B9A492CC4ULL, 0xC3306D0BC6B6C49CULL, 0xCB4792C22EBE05D5ULL, 
            0x1915289C87160160ULL, 0x0739E5807BFDE872ULL, 0x1FCB4C9A6B89A94AULL, 0x8348087E6D79BD52ULL, 
            0xCE2FE84EA9DFF7B6ULL, 0xA403E0FDF8EEF097ULL, 0x1767597B7EB89A8AULL, 0x1B3FA515F9CA061AULL
        },
        {
            0x675A19F6DBBA3635ULL, 0xA1DD116FD027EE51ULL, 0x4E872618980E9A0FULL, 0x1012E9BDE6051C5EULL, 
            0x0AB8E8B9DE979FA1ULL, 0x15B105E0488229D9ULL, 0xFA43601F144ABC0BULL, 0xE48C7D0FA0DC0256ULL, 
            0xB9B94D39A04DE5FCULL, 0xE2B05016C60BC993ULL, 0xA5CB83D00465F09BULL, 0xFC0E52AAB574D7AFULL, 
            0x0FA486282DEE668BULL, 0xE9B7972A2674BA0DULL, 0x0EA4C1043B598BE7ULL, 0xDCCF82146AE3BE6CULL, 
            0x49F20E84208C8749ULL, 0x341FC54E541D6ECCULL, 0x5AF2383BE8DF0E2FULL, 0xF483322165F78F57ULL, 
            0x822DA3178192E766ULL, 0xFDADCE7ED8B58B84ULL, 0xBDC2EED2C99CC835ULL, 0x88FBE15E74ADFE3EULL, 
            0xCCC0BDD5782607BCULL, 0xD10F6BAB7704B73EULL, 0x38EEAA962668DEACULL, 0x1585EBF87F46B809ULL, 
            0x9BB6A4DA4961962AULL, 0x32888654AEB52FDAULL, 0x8DFB062B0D7D7888ULL, 0x3B4F8267408EE2D5ULL
        },
        {
            0x3FA9F735F748E784ULL, 0x6DEEECDF8136B169ULL, 0xE483AA3F58C8DFDAULL, 0x22C095400149CE77ULL, 
            0x8F1048CBF0AEA2DCULL, 0xE9126774C429922CULL, 0xBA6AA5479C6F0086ULL, 0x845DEF6E437F9FB4ULL, 
            0xB6B1B8605A6C02CAULL, 0xB5278B9B89E5D06BULL, 0x20013795A0E55941ULL, 0xA01DBDAFB39C1731ULL, 
            0x211382801E2B146EULL, 0xF0727DB8B3710BB6ULL, 0x1E02F9E02835EE87ULL, 0xBE3DB7A8521B0D41ULL, 
            0x6F5A30CF27EBA5DDULL, 0xB5069AB4DE761478ULL, 0xC8B603FAB27F68E1ULL, 0xA77863582FDFB589ULL, 
            0x084044A404DC8192ULL, 0xE206E91272143E1BULL, 0x5CBEBDE340C49FE4ULL, 0x7D1569C663DBE71BULL, 
            0x5EBCCE6E5943E5DDULL, 0x38ECCF2CE14FFD20ULL, 0x19F1989503533928ULL, 0x5B3A953C166CEC4AULL, 
            0x30616F1DBC8B6D34ULL, 0x47959A5A7E3862B2ULL, 0xE8042A4B845B1548ULL, 0xB441033A277D95A6ULL
        },
        {
            0x59F71C93D710B523ULL, 0x65B222CAD462FE55ULL, 0x373F9A928E7ABDEAULL, 0xA0374277C5C93233ULL, 
            0xE02F8AA2EC1C9899ULL, 0xC2C0D4F89098C102ULL, 0xF6AB37E1E0530DE9ULL, 0x1B0F9C7F3B679FACULL, 
            0x52036B5EA1094CADULL, 0xF89852B137F4886AULL, 0xBD5B6F4DE621189BULL, 0x9414C81CAAC9843BULL, 
            0x753D293F76855C19ULL, 0xB0FBEFE074E643BCULL, 0xB72362E9F66FBA36ULL, 0xAA23C50167D24EDEULL, 
            0xF150942180091C37ULL, 0x1F593621DC219893ULL, 0xAA78C6C8D0EEA460ULL, 0xFC09971EFBBC9881ULL, 
            0xDBDBB667A44138DFULL, 0xAA2F5ADC2A50DA57ULL, 0xE95EADE55137DDDDULL, 0x0D329263CDD7B350ULL, 
            0xFFC9EABB089B3B62ULL, 0xAB0306B0972227BEULL, 0x47C85BBD10AA742EULL, 0xEB484E032FA97D32ULL, 
            0xDFA83C55C3AFC5A3ULL, 0xF5E229D6BA7F7795ULL, 0x7655AC3B90CEADADULL, 0xC169E711C43CCFE8ULL
        },
        {
            0x0AA312141C1C60C5ULL, 0x0FF6D5BBD1217945ULL, 0x1585F1DAF2D23554ULL, 0x6B77BB922AB6AE84ULL, 
            0xE464F1372F4235D5ULL, 0x7705D7B4BE1742ACULL, 0xCAFD51BFD1725561ULL, 0xCF78787D207F34E3ULL, 
            0x488ED5ADCB9AB0BEULL, 0x53287E5504E873CAULL, 0x56CE84AC39D23C15ULL, 0x50EC9F7BDDB435B9ULL, 
            0x339B9CAA2A5274D6ULL, 0x4EFC69716B075024ULL, 0x0517EFD7A27CBD93ULL, 0xB3B7202C456803CBULL, 
            0xF91C5C9F13F9063BULL, 0xC852E78BEB39F1B4ULL, 0x8503FEB14BBC864EULL, 0x2A4BA4F1BE81A32AULL, 
            0xE5CCC1094586D40AULL, 0x1738C4E2CDA2853CULL, 0x88B7621A9F3615F4ULL, 0x17164C2D749CE728ULL, 
            0xF2BC398D4B43B005ULL, 0xEA91B6B19C02ECDDULL, 0x2CAABC21DB833658ULL, 0xEDAC22D92F51CA0CULL, 
            0xE6F7CEF67EF5FF77ULL, 0x4E1D938514234F80ULL, 0x4853DC442F539FF3ULL, 0x3EC489DFDB482021ULL
        },
        {
            0x92AAEFF72C08E722ULL, 0xF736E1DFFF4209BCULL, 0x2D990BC70A901777ULL, 0x77F6F1A1D211F8A4ULL, 
            0xC58399C3A995D94BULL, 0xD3D92CC66B06363BULL, 0x6B23C7096A31377CULL, 0xAA14BD90B09A160BULL, 
            0xEB8B617724FE71FAULL, 0xC728E65F5D8E69CAULL, 0xDA799B0BE3CB31E4ULL, 0x5B4D9CB4882257D1ULL, 
            0xF059DE8D410B86B3ULL, 0x16556064CD9B7C7BULL, 0x7AAF6F40A5DE7CC9ULL, 0x0E792A241BB3A58BULL, 
            0x291816852385E299ULL, 0x67CB0FF930E32C49ULL, 0xF60CE41C887BFFCDULL, 0x9232755E56612E1DULL, 
            0xA5C68885438080D8ULL, 0xE89520732F26A6C5ULL, 0x5AB91B7A34F6EF16ULL, 0x9884F28B9FDDB481ULL, 
            0x1C0095E2E7C3DCF1ULL, 0xBB525B7835FB4E19ULL, 0x25EBED3594DAA9DDULL, 0xCD0C46201AD7205AULL, 
            0xAEA063FC3D3F25FBULL, 0xEDBB4458F683B75DULL, 0x478026980CBE841CULL, 0xAE32CD04A6155F4EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseEConstants = {
    0xB2A21932F4E70722ULL,
    0xFF5E92DAC003A403ULL,
    0x5CA5287F1DE5109CULL,
    0xB2A21932F4E70722ULL,
    0xFF5E92DAC003A403ULL,
    0x5CA5287F1DE5109CULL,
    0x04A3E29B4075ACFEULL,
    0x859C75BABF961B24ULL,
    0x01,
    0x28,
    0x55,
    0x88,
    0x1F,
    0x5C,
    0x8A,
    0x5B
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseFSalts = {
    {
        {
            0xBA8C39A501F47480ULL, 0x47F05D7A5CB17F09ULL, 0x2508D2F1A734EB7DULL, 0xA129DC00F39409ABULL, 
            0x4B0E051D35E7375AULL, 0x0368D783189F12DBULL, 0xEB6F6EDCA3AD92B0ULL, 0xB4903CCDD3836CBFULL, 
            0x0F8B13E83F5811A8ULL, 0xC521EAC96CE3C213ULL, 0x430E1A24E2A8A38AULL, 0xED0C45788D9E985AULL, 
            0x2EE9083D1019F7CFULL, 0xCF8E2D77472D5A28ULL, 0xF199E9944818C4C8ULL, 0xDE1B30887BF5CBF8ULL, 
            0x2A8818ED12B0FCECULL, 0x0B6CA98D52DCCECCULL, 0x24F980995A23690DULL, 0x03B46115DAC1F4F4ULL, 
            0x0A4464784D498331ULL, 0xA627002952E431D5ULL, 0x9995545DF3C52539ULL, 0x832804A77ADB24FFULL, 
            0x3F6C5847DF8820CBULL, 0x999E205626490460ULL, 0x5DA16E63DCF155C2ULL, 0x18A9B3BB8788D2B3ULL, 
            0xCC21219E7A2DF45CULL, 0x6FF93DA86F065330ULL, 0xFB92D9328E08CF86ULL, 0xA9F0BA89CB67DFC1ULL
        },
        {
            0x775893839843C2F2ULL, 0x9FE023FDACB4A428ULL, 0x50CC4D03AA4A03A4ULL, 0x89C557A7A4EE8534ULL, 
            0x5F71E1ECC54916DFULL, 0x8166CC6FA9D4DC68ULL, 0x27473FD2C80A60C1ULL, 0xFD983EAAAF1176CDULL, 
            0xF5B39A63390EFD43ULL, 0xEA79F49723A42230ULL, 0x952059E5012B8A25ULL, 0x96EFB6B760714477ULL, 
            0x2BA17DCE043430DDULL, 0x4E2EEC61FAD38E91ULL, 0xC14147E096486DECULL, 0x481AE786FDC12470ULL, 
            0xE12B08A0A196572DULL, 0xE22BB55B27D06213ULL, 0xC19E2629B1B72039ULL, 0x02E535F1B22DEF46ULL, 
            0x4E6501401645580DULL, 0x14DDFF54AC485734ULL, 0x8157F54C0C07257EULL, 0x2B4369C684440716ULL, 
            0x4639ACC1B753BCD9ULL, 0x8B967AFA4914D542ULL, 0x6555E63DA714DFC8ULL, 0xD70C830278B386DAULL, 
            0x3936A8D2EC9409B1ULL, 0xAAFB46FD5FBBA5C0ULL, 0x519726D3C98195E0ULL, 0x98DFA2429F13AB05ULL
        },
        {
            0x025637A3B0D2E84AULL, 0x9BF6945EB636F48BULL, 0xFCEFE20E65B97E5AULL, 0x40B0B9068765B7E4ULL, 
            0x4640AC25C2745B0DULL, 0x6575A5279E3462B1ULL, 0x91C7F8F0CAC9A205ULL, 0x2FBC8B614AD8B74EULL, 
            0xA222B41621FFC27BULL, 0x2EBC27E725910B0DULL, 0xA5766314535CE331ULL, 0x4A928B6DEE65CC0DULL, 
            0x444A0FC279507259ULL, 0x4CFC7D0B23374BC3ULL, 0xBB540EEC0A7B0D7EULL, 0x894CD7EC0057ACACULL, 
            0x546949C75ACABA32ULL, 0x51C74372CAA522F1ULL, 0xADC0831966ECA010ULL, 0x70D7D847F5C06004ULL, 
            0x161F1B25601B589BULL, 0x6519B2920858415DULL, 0x562FCE16AB29A1CEULL, 0x04384F466474BA62ULL, 
            0x287DC40F5E78E380ULL, 0x1E6E69DF9EA54BA0ULL, 0xB2F38CB3A2DFC465ULL, 0xDE06D7357AC977CAULL, 
            0xDA6CA9DA2987115CULL, 0xDCD2C4322E90BB26ULL, 0x245365B54C416590ULL, 0xE35DF4E00763C9BAULL
        },
        {
            0x0A74F5AF800437DAULL, 0x71873CAFC0013547ULL, 0x8C1F9D9CF6157ADDULL, 0x8E25BE10A6843D05ULL, 
            0xC1824494156D2DC1ULL, 0x9194A284519650ADULL, 0x46861FD257A67D5AULL, 0x044C0CD8ABE4C1F8ULL, 
            0x17F82CA7C24E18BCULL, 0x67F5103CA1ED9E67ULL, 0xC2E64537958EDA4EULL, 0x7EAD57027F4AF628ULL, 
            0x1E6FE52D814620DEULL, 0xE8BF60B1E8B9B064ULL, 0x2A47C5719063DF12ULL, 0x6ACAD06CCDC0384DULL, 
            0x783A373EDCD90C3AULL, 0x55792D2472E73127ULL, 0xDD826F5EAC053A5EULL, 0xDAC202E3A3CFA38DULL, 
            0xEAE2FF3BA8D8914EULL, 0x8396FF5A35AE78A7ULL, 0x15BA3C38018DDFF3ULL, 0x4896B0E46812A41CULL, 
            0x9B4AC007481A5A54ULL, 0x2FE3A55AF67CB6BDULL, 0xDD8290BE3B95893AULL, 0x58879BFDC5380692ULL, 
            0x7739AB3572F2D6FAULL, 0x608AABA2021F1960ULL, 0xBE3A398B13F97815ULL, 0x76E7E31D2D40CF9BULL
        },
        {
            0xC95EC2B97E27DAD6ULL, 0x5F035B42FCB841ECULL, 0x6FAFE4B92CA17293ULL, 0xD8ABE1074B6F6D83ULL, 
            0xF0CFF8B8FF1904C9ULL, 0x06A9CAA5B13BCD4EULL, 0x5E5636BCE496B9F7ULL, 0x3B077CCA5C47944BULL, 
            0xFE6A7107843F7C90ULL, 0x428D8FADC004B570ULL, 0x92CE57AA2F9C7B84ULL, 0x165489AEFA941DDAULL, 
            0xC8332E9369B87B2AULL, 0x2622DB3007B4DA67ULL, 0xC56C12BF3D162E8FULL, 0x21CA62C980ECEC6FULL, 
            0x76FF40579BA7CD59ULL, 0x866ECB2928000552ULL, 0x6F9AAFD1F04AC71BULL, 0x7CF71D9C1F2095DDULL, 
            0x67063ADA538A9B3EULL, 0x03180A505EE50D41ULL, 0x09891E65ABAB0DA3ULL, 0x0493CA074E90F29FULL, 
            0x95BAE9D99B06C7D0ULL, 0x70CDE82E5FEACB9CULL, 0x3F72FFBA5B6A3603ULL, 0x65543B00F6C0DCC6ULL, 
            0x79174DD0455D970CULL, 0x1A30A2DB769508A4ULL, 0xF28FB02B31103F95ULL, 0x9C0C0B6C1D1A2E5AULL
        },
        {
            0xA3DFDB07590BAD9DULL, 0x9802801B3572364DULL, 0x319047AD1551EE6BULL, 0x88E3BF068EC4A173ULL, 
            0xB7FF8B93B40E302FULL, 0x948DE8D01E84BB4EULL, 0xCA74382DF6D45282ULL, 0xAF4C9147F5070746ULL, 
            0x3A8403C18A36827DULL, 0xD4EEB2F91D018333ULL, 0x90CA2D852DEA0587ULL, 0xCDE83933E888D75BULL, 
            0xE006BE5D3765FFDCULL, 0x5DA707F03E734F97ULL, 0xB8DDB47AC8F8343EULL, 0x68008A3EEA132F63ULL, 
            0xEDD90D4A3E024573ULL, 0xEDDFD6EE49442C5DULL, 0x6C618D68383EE759ULL, 0xA5E48E9A840734A6ULL, 
            0x4C0BEF56E4053982ULL, 0xF022BA5AE100271FULL, 0x5BEA6CBAD3EFE28FULL, 0xC33FFC9424DA76BCULL, 
            0x9E4A67AE71F4F4ADULL, 0x9F2225AE4CF51884ULL, 0xDA004D81CB070423ULL, 0x0878E910E3486059ULL, 
            0x10890E7F8140BFCAULL, 0x536065338C72938CULL, 0x609985E58F3F2303ULL, 0x461C412A2B344DCCULL
        }
    },
    {
        {
            0x55825C0E0A6ECE18ULL, 0x8B977A7733366805ULL, 0x2817CBE367B1A206ULL, 0x226A7B59425E0E32ULL, 
            0x34075E07AC264D92ULL, 0x543B1C1FDADF382FULL, 0x72109224DEF66CD2ULL, 0x939B6FFD714FA73FULL, 
            0x182857007E055823ULL, 0xAE3CCA75C1EC4605ULL, 0xDBD4DDD72EB8432FULL, 0x25C91BF568F06A33ULL, 
            0x06FE629331A2005AULL, 0x81B7DE5A55323503ULL, 0x7D4D1CA5A1F765A0ULL, 0xFD4D1B6B73D2328AULL, 
            0x327402910E19768AULL, 0x16BFB0E694F43A9DULL, 0x4FD2E50F635EC80BULL, 0xA8CEFA9EB3CBD442ULL, 
            0x641A3FAFF9BD5AF6ULL, 0x162F2C1DBBABCEB1ULL, 0x0B31AD5A561653E6ULL, 0x1C48B57FE2363302ULL, 
            0xAB96B0B6167E07C3ULL, 0xB5FC5C28F7F9CC1FULL, 0x7BC809D66DBEC3F0ULL, 0x9BB11CE8E0983A7DULL, 
            0xAA925E8FDD92D4A0ULL, 0x27A03BDBAEB9180CULL, 0xABBEB7B740D775CCULL, 0x67AE8A0641EB0D4CULL
        },
        {
            0x89C1281025CB4BE3ULL, 0xCC984B15BC4DE78DULL, 0x378B11348E0899D3ULL, 0x2603819BA1CC8D20ULL, 
            0x14E0613E7E199274ULL, 0xAFCF4EB23C6AB4EEULL, 0xE7579C9EF8BD5C17ULL, 0x1AF91EFC1BC23F61ULL, 
            0xC2700A8A67C50179ULL, 0xD9B7648404FDCE5CULL, 0x10674833EBBF21BEULL, 0x4A1318F2F21BF20BULL, 
            0x1F684ED80DC70207ULL, 0x9C21C48FA28698A3ULL, 0xE832247862FD8989ULL, 0x46BD4023861B8D9FULL, 
            0x621B18C75757ED91ULL, 0x3874683ED3BA6FF0ULL, 0x46382FDFB9C99FA2ULL, 0x1BE0EDEB49839F62ULL, 
            0xA819561A8AEE79DAULL, 0x92C2E7DD323198B1ULL, 0x8956007FCD1B7911ULL, 0x5D578AF9CE8663C7ULL, 
            0x60572F4D2B9FA887ULL, 0xE596AACCEC8D8ED5ULL, 0x08F1B6B873DBCDDBULL, 0xED69C440FF444ED9ULL, 
            0x55C7AC0705576D01ULL, 0xE8F06075A1622D41ULL, 0x8799B2D730B06657ULL, 0x31819137CBB910EDULL
        },
        {
            0x582EBD1CA980DCDBULL, 0xAC519ECFC9E3C126ULL, 0x25F0938577F028ECULL, 0x4460114AA093E547ULL, 
            0x5E2AE1A350EA5B5EULL, 0x808589B499CD3A4DULL, 0x79BB2CB408892C25ULL, 0x95015D71D04040D1ULL, 
            0x9FABC7DBAF573C1EULL, 0x3FC7D18D1BBC289EULL, 0x5BA2242E2183A4B8ULL, 0x04A26F72ED70FE58ULL, 
            0x58C88AB70A7BD180ULL, 0x46086EB89E5F5399ULL, 0x48D7EF096EFF7272ULL, 0xA1565D04B83F5B04ULL, 
            0x3B70F58A36A32161ULL, 0x6A3014B6FA4F9C38ULL, 0x50BF639C16796CEAULL, 0x01F6BF30965B36FAULL, 
            0x836FEA7F30607990ULL, 0xC8FCD7B213512AC4ULL, 0x54450920D9D12586ULL, 0xCD5DB89247CC1B8EULL, 
            0xEDED181299F60669ULL, 0x383A97B51CE30B62ULL, 0xBC56BC8B335B3DDCULL, 0x9C8D7F0285B0F263ULL, 
            0x40036A510412A89EULL, 0xA06A2B1910FB830AULL, 0x2E457E5EA74BDB98ULL, 0xCF439EC55D1C124DULL
        },
        {
            0xF6D509F4C936C557ULL, 0xF630A005FA2CB2F2ULL, 0xB8E9B671E0D91F71ULL, 0x0DB679041925AA85ULL, 
            0xE75E202B6690725CULL, 0x4FDEED24F1D433C7ULL, 0x1E0D805659B48010ULL, 0xA6AB3789C4B3477DULL, 
            0x9096279582FD15B3ULL, 0xCC7D900BC88E6E68ULL, 0xF1DF2D46A420E861ULL, 0x7614C00136C22EC3ULL, 
            0xE38858CD67D60BF4ULL, 0x54B2E253B0D1CD88ULL, 0x78056E4114C37AD2ULL, 0x751D2A3EF2DAAC8AULL, 
            0x1CCA30FAABD01D0DULL, 0xE636471339C39428ULL, 0xFB884549D8B3A4EDULL, 0xA57A85DDA97879D0ULL, 
            0x80F4F77469400D91ULL, 0x8BDAB3790FB4970DULL, 0x4266C718D830BA71ULL, 0xDC7984A95BC9CE7AULL, 
            0x106DCDA984FB6251ULL, 0x830BE49C439E4980ULL, 0xABF960E63EC0D3A9ULL, 0x1B76CE8BEA35C00CULL, 
            0x7B5CD171DB4F338DULL, 0x1C367B419C8D1779ULL, 0xD22A0212AE9956BCULL, 0xF23CAD8212C13522ULL
        },
        {
            0x8C3E809AB1B509D1ULL, 0xDF3C9D3E10067968ULL, 0x0DE96802FF3D626DULL, 0xDB64DCAE1075B982ULL, 
            0x1A8668221863A8EAULL, 0x2FDDCEC9301D165AULL, 0xA4DB544B5C56A5DEULL, 0x71BD76D4BCE34A71ULL, 
            0x32B6E582FC246136ULL, 0x558A238D876E59EAULL, 0x870093E610305E95ULL, 0xEDACBBDC94C0A61BULL, 
            0x640CB582D704D6CFULL, 0xE3A8E77C8DB2218FULL, 0xC650FB7F9F37B573ULL, 0xF5C77FDA6483BB58ULL, 
            0xA0D3EB73852DEA0EULL, 0x965F876F2889496FULL, 0xD0A3515A08FFFC00ULL, 0x342CED9418FD8FB6ULL, 
            0x9C942F706AD40932ULL, 0x8FBAE8B96127BE02ULL, 0x8F14C529ED74C3BAULL, 0xC2A772B5B1AAAF05ULL, 
            0x690B541F6FE767CFULL, 0x1C29D81E919B6FCAULL, 0xF2277132BF9B23D8ULL, 0x7C9DF619DA414EA3ULL, 
            0xA87E45BA71204B9FULL, 0xD62A8FBB7ADE5429ULL, 0xDC526AF9773679BDULL, 0x397855F6B7B799FCULL
        },
        {
            0xB3B11D08F3EA66AFULL, 0x70AB2C16F8E25EA5ULL, 0x793CDC4489DA87DAULL, 0x28800D6D276F933FULL, 
            0x3E13CE686FBDACB7ULL, 0xDF229830CC9763C4ULL, 0xFD55032288BAB7EAULL, 0xF719DB1259AA16F3ULL, 
            0x5055CDC72286EAF6ULL, 0xFD026FBC8779CE0DULL, 0x841D812F036C2E79ULL, 0xAB448BCD3B320952ULL, 
            0x2F7FD9888C5D3202ULL, 0x357122C31DDEAD31ULL, 0xD79C9AA04C31E67BULL, 0x1E8B0F938F8080B7ULL, 
            0xECA76C542796A5ADULL, 0x44086249E2BA13EAULL, 0x0A8A09F7074DECF2ULL, 0x3B75FE4E590F2682ULL, 
            0x50DEF00AA27FB2CEULL, 0x670E41FCE269D5B1ULL, 0xCCAED8B3F094BD2FULL, 0x6EBA311FE62F4DCFULL, 
            0x4625416090712934ULL, 0x851510187A83509FULL, 0xBA35E8E975AB07E7ULL, 0xDF5E88B9E8376620ULL, 
            0x5614CEF2E826B756ULL, 0x38EF0F91674F722AULL, 0x97F10E8BA908A720ULL, 0x30ABD797B9BE2FBAULL
        }
    },
    {
        {
            0xCBCB64A4B8DB15D4ULL, 0xF95777D3320B3215ULL, 0xD98CBCE9BB25FDDFULL, 0xA8ABB4D0DD877950ULL, 
            0xFFA4FA8B44EFCABDULL, 0x519D54D1E5F6782DULL, 0xA4B93167412390D6ULL, 0xA8229EA4685B887EULL, 
            0x6E757895FFA11626ULL, 0x8933407098A6ABC1ULL, 0xA684B60F2769E74FULL, 0x71FCF1A29DD2CAD0ULL, 
            0x559674EB4A7E3885ULL, 0x1C62BDD1B1381E41ULL, 0x7D20FE2B839856B2ULL, 0xDB3C841B0FFEB73CULL, 
            0x68946345F59D54D2ULL, 0xE2727FEB5C83C2B3ULL, 0x7E80A129BD30475FULL, 0xF4E58F284E6D4B02ULL, 
            0x1F1F477D47944ED3ULL, 0x93EE52C373280579ULL, 0x0E400E00834A4B82ULL, 0xB247305FE07069BBULL, 
            0x7EDD6BD12C104528ULL, 0x0C104EB69D8E8226ULL, 0x70E5778DE104ECE5ULL, 0x3D52DE036D4CA108ULL, 
            0x4336BCD62CDBD84FULL, 0x3018FA06972CFB62ULL, 0x7DC4563B376419D5ULL, 0x59B203CEB223077FULL
        },
        {
            0x9728245ED426D509ULL, 0x17EC2D095938F6B0ULL, 0x1E6C3EFC25DE3635ULL, 0x7CE1D23F07E8FE96ULL, 
            0xE4743B5847AB3161ULL, 0x4C4AA5AD613A90FDULL, 0x9723C4AEA60E0CCDULL, 0x5CD7E13AB0683380ULL, 
            0xD2A5D16BA8BED9E8ULL, 0x2DA5939B51C2A931ULL, 0x0EF6402BF96ADFB9ULL, 0xEECE63CA019E47F2ULL, 
            0x539A30351E57E7CFULL, 0x18211061FF77B665ULL, 0xE0F0BD71958E3F7BULL, 0x9F67D4DB8525283DULL, 
            0xC655A70B13F42358ULL, 0x668049E1ED7BE593ULL, 0xC391B8D8AA900265ULL, 0xA6CF18DEB947857EULL, 
            0x6B7CF959FD9A9871ULL, 0xA1BCE46EDE35CBAAULL, 0xD4B5970A9C254F31ULL, 0x8AF20C70E35C9833ULL, 
            0xCF4BA0F22A12FAE6ULL, 0xB3EC64D75B4F1FA4ULL, 0x7A0C1FBBDA5A70FCULL, 0x8826B6FD8988C75FULL, 
            0xE5DB68D5FDD6F4DCULL, 0xEF15717E45CA1583ULL, 0xED2543FCE114E3CAULL, 0x10BC3C4310A1D14DULL
        },
        {
            0xD8490B68C0E5F8E3ULL, 0x402A1A9A1BE1F5F9ULL, 0x0ED0223C35E9FD4EULL, 0xA9F91A60B3C7595AULL, 
            0xAA22534856E15D38ULL, 0xB250AE909936C613ULL, 0xC9C25A1EBB8AF8F8ULL, 0xBC5FDE5E2A307564ULL, 
            0x25486310B015E2BEULL, 0x01F12F69C3CCD111ULL, 0xFF6A62CFEF0E43BFULL, 0xE77407EF942250B1ULL, 
            0x9CD4552301DAE091ULL, 0x5350C0C1DD83173CULL, 0xC768EB25EEEC034BULL, 0x6B99EAA4CFAE53AAULL, 
            0xA4569A00BC394476ULL, 0x9EFAC3A6CF30AF8CULL, 0x2A75813D69ADFDCEULL, 0xFB9D71669380076FULL, 
            0x4BC0D0A8560B1A72ULL, 0x88B27D7284C4855FULL, 0xBCD22F1EA4B63A4BULL, 0x308F993438699176ULL, 
            0x93E878B33BCFE454ULL, 0x5427D73FD8152855ULL, 0xD4085A3D2692E2CBULL, 0x77208166D6B1BB4FULL, 
            0xC953E560B3076738ULL, 0x04BBC0B5C2444723ULL, 0xC6EAA34BC95D5CBDULL, 0xF6C307DC237E8D61ULL
        },
        {
            0x3FE7A358FDAFE451ULL, 0xED893BF36B472CF7ULL, 0x4893373870ADB579ULL, 0x69786AB79DEACB07ULL, 
            0xD8FC76270EA29CA3ULL, 0x94712107E7A846FDULL, 0xCBBBE4F215E0D935ULL, 0xE53276EFFDF15AF4ULL, 
            0x0258EE6D2828FA30ULL, 0x1F67E332A2A89DEDULL, 0xF2D592B91DA12551ULL, 0xE452AE1B63D03809ULL, 
            0xD9F2BF96C41B32C1ULL, 0x220573A29BEBA2ECULL, 0xA310377FA2DA5C90ULL, 0x0812F1B5A22D70CBULL, 
            0xB1E25ED44EED3AFEULL, 0xBB44898ECAABE22BULL, 0xA42A0998F3473EFCULL, 0xBF2F9F3025BE0DF4ULL, 
            0x917873DC8A1F9C64ULL, 0x8647B7E9689083B8ULL, 0x5EF480910E9D6E5AULL, 0x84CBE6C94D1A82B9ULL, 
            0x202EBF8F4869ABB5ULL, 0x15603802CEC96FF8ULL, 0xEA69ADD1D8B56482ULL, 0x569CC9B9C68BCC89ULL, 
            0x37B3862D82E4DEF0ULL, 0xFC4F6037C2DF896EULL, 0x4603C48686C21C10ULL, 0x396E443201FC5A5BULL
        },
        {
            0x3E0FF5CD0A976D84ULL, 0x6FD15E7D9127186AULL, 0x352A138042C40F55ULL, 0x202A80F94E9C501AULL, 
            0xFD0E846A9D3833A5ULL, 0xC9DB82E328CDF4C1ULL, 0x0DBED53DC15B1E90ULL, 0x920E6B737F3279C5ULL, 
            0x27D49B83F185FDFBULL, 0x2B55A47F10D1F79DULL, 0x01E1AA082047AB18ULL, 0x974B63DA20CC546BULL, 
            0xF31164C343C5DDDDULL, 0xF5B0E09834467E07ULL, 0x0DA9A1832FAEB9F9ULL, 0x43AE7F6FE725D1F9ULL, 
            0x0F06F53973C364A5ULL, 0x52394CEDD862EF84ULL, 0xEF7E5400FA1AA11BULL, 0x26374FCE199452F4ULL, 
            0xC9604BE7B4ED8579ULL, 0x34B5EBBA96CB95BFULL, 0xA65108354495FE6DULL, 0xEE6CAB06637EBD9CULL, 
            0x395D29E755B06E14ULL, 0x923C9411BC225317ULL, 0xB3143D660E9CE68CULL, 0xCC2005EC179AD52AULL, 
            0x8B9F6E764EC541DFULL, 0x14F1B59E8B12B42BULL, 0x91A336C87185B65CULL, 0x2D1664E035DC20ABULL
        },
        {
            0x14FA9DE98717848BULL, 0x0E1C2E2A04040BDFULL, 0xC60C2205B791D1A5ULL, 0xBF3E10083CD205C4ULL, 
            0xC2B7A53020CE4D39ULL, 0x4F23A44655AE5BAFULL, 0x6DD5FD9C83299F9DULL, 0xC234E4E38460485EULL, 
            0xD571C01C32B17611ULL, 0x5DD9C728AF7CE603ULL, 0x55B82D9A59BB9A57ULL, 0x97C596FFDED8793EULL, 
            0xBF34C517FFA65CF0ULL, 0x6AD9305CDEECE092ULL, 0xC719556C94781D92ULL, 0x77C233F874437E8AULL, 
            0x7523F1A6E7CFCDE8ULL, 0xE2585841B68C4B33ULL, 0x0142B46CC7B7E308ULL, 0x79810A2DFAA3954DULL, 
            0xBFAEDAE756C214B6ULL, 0x346D5ED13068715EULL, 0xE62F09659EBD2057ULL, 0x70E0E006CA1B6C5EULL, 
            0xEEAF48C6B89D8E8DULL, 0xE6A275098B9E092BULL, 0x78BFF5E0C6088B09ULL, 0x4B91D6FEC97A3CC9ULL, 
            0x569DECD2BC987816ULL, 0xE358611A941C6A24ULL, 0x455650D9FC11F70AULL, 0x3836BAA4A9039460ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseFConstants = {
    0xD410D57021FC7440ULL,
    0xBBA862FB2FBCDBECULL,
    0x852215357DA6B640ULL,
    0xD410D57021FC7440ULL,
    0xBBA862FB2FBCDBECULL,
    0x852215357DA6B640ULL,
    0x4557144AB0095D71ULL,
    0x2212BAE5533C0624ULL,
    0x8F,
    0x3D,
    0x77,
    0x08,
    0x8C,
    0x60,
    0xEE,
    0xCF
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseGSalts = {
    {
        {
            0x64FF5006597E388EULL, 0x9767F760AFC76F59ULL, 0xE5108BF920C155B1ULL, 0xF20C6908DBFE3A60ULL, 
            0x19DA6842C6A3A7F9ULL, 0x81579BA0272032E4ULL, 0x79625D11718A3E5AULL, 0xDACAC7A20B9DDFAEULL, 
            0x105C46D8F8E70D4EULL, 0x8D91754BF7BFF48BULL, 0x474AE528B2A0215CULL, 0x493E94B02E24E762ULL, 
            0xE79387CADB216B65ULL, 0x68800D7C0DC58D0BULL, 0x4270C09D684FF343ULL, 0x4929C147B1D5AA12ULL, 
            0x6DB04FA9742E5F83ULL, 0x5A653D608BAF94A0ULL, 0x3C0F41CD7846F2E0ULL, 0x5378FB7FCCA4D0ABULL, 
            0x3687068FB44B35AFULL, 0x96AA847430B8E548ULL, 0xAF60EF27ECC5B00AULL, 0x0E1C8D3529DCBD9FULL, 
            0x4B30AA46AF70354FULL, 0x0A91DB7B04F201C0ULL, 0x477BE4C5619F8AB5ULL, 0x29CD54CDB877AE41ULL, 
            0x4840300C127AD2E8ULL, 0xF34277CEDEBC67ADULL, 0xCA3FD9EDB6A21240ULL, 0x399115D2010D6095ULL
        },
        {
            0x3D7C95CE0F02D15DULL, 0x7EEA40D60687E305ULL, 0xA8DA2CBFE0F4FE13ULL, 0x7B5BE711195DA679ULL, 
            0xF64595914B12CB41ULL, 0xD66491C9DC0D9731ULL, 0x0974FC111F267084ULL, 0x5901A066A32E633BULL, 
            0x95011A761AEC6C85ULL, 0x6749FD6E7E7AB4A0ULL, 0x055CEDBA26721618ULL, 0x95425CDDE6899708ULL, 
            0x0E61F2A780FE00FFULL, 0xC9900A0E653D9AC4ULL, 0x5E27144BAF19362EULL, 0x8B27AE543B8C7E7FULL, 
            0x3B35EDAD99AB5901ULL, 0x67D9703C633FA114ULL, 0xBB12AFF7F85494DDULL, 0xAA5013B789DE300EULL, 
            0x4FD62637D9593962ULL, 0x0356A0EC15D11E9AULL, 0x89307B14228AFD72ULL, 0xF4DAEC513523DF8CULL, 
            0xBF60A4FD2DA0C027ULL, 0xD3E1A7264345B6E2ULL, 0x3CFC30A8D88D49BDULL, 0x40ECB4BEA9022D7FULL, 
            0x9254D880019C3F19ULL, 0x88976666F453BFE0ULL, 0x76EB537E03C8D68AULL, 0x122CC1299EA53826ULL
        },
        {
            0x77928F9FFB46BC7EULL, 0x758D16E96397ACF4ULL, 0x6EE3D4DFA30F7E2BULL, 0x9D68ADD781675CBAULL, 
            0x151060A18A7117CBULL, 0x9D7E08C7589444B7ULL, 0xA0869FFA74D6BDE5ULL, 0x4D6A76D429307141ULL, 
            0x8916FF7B7C729022ULL, 0xDFAB5A1C99B2DA50ULL, 0x52A3B94155355939ULL, 0x5F836DEFE0D10DBAULL, 
            0xAFC4B5262262FCF6ULL, 0xA9033A7666AD32C9ULL, 0x55560CE973D21706ULL, 0xC49B396C0840AC78ULL, 
            0x8E9EB7F5824B6A83ULL, 0x1CA44820DDE73B46ULL, 0xED556DF4B916A60FULL, 0x017036737971AF0FULL, 
            0x86B0C4519E935913ULL, 0xCDF0168DD0192FA8ULL, 0x1BCD92B0B2D30125ULL, 0x4244368F4095F7BFULL, 
            0xB90792D04E13B3C3ULL, 0xE337E03EBF12ED73ULL, 0xC8D3A9C6EE332213ULL, 0xAC2D5B622F8E24E9ULL, 
            0x2BBCEC6F7CC1C1B8ULL, 0x0A0B138056C74299ULL, 0x1E9EAD2117887EEFULL, 0x12262F86F300EBB2ULL
        },
        {
            0x1BBC821912AC4DD3ULL, 0x545FF94403BA9A2DULL, 0x17E5C9634D548173ULL, 0x465CB3BE743EEDFEULL, 
            0xC201F301C4383A98ULL, 0x33484D941D13E2F7ULL, 0x8AA65850DFE3D2CEULL, 0xFADFC988221113AAULL, 
            0xB007C156F1320C00ULL, 0x9982D5AFEAF7E17CULL, 0xF065563ABA7CBEB2ULL, 0xC8E00E091E35EA2BULL, 
            0xC10C2BA40055D089ULL, 0x0591906FBDFDFA7AULL, 0x9B8EF1E92564A69FULL, 0x221EC9816BAE5ADFULL, 
            0x0B96D59C8C50AAF4ULL, 0x9325A986BEF6D337ULL, 0xBF954850024663B2ULL, 0x55D652ADBEB6204CULL, 
            0xE7CB1AA9ED9D554BULL, 0xA708DEE0B1352060ULL, 0x103F2EA047A089A4ULL, 0x1CA40C5F09E25D96ULL, 
            0xB18E6AD9B798769FULL, 0x764E247B60836B81ULL, 0xF3C5F7AF758FB8A8ULL, 0x73B4C23ED4FF9585ULL, 
            0x9D2E2EA95304F701ULL, 0x4D6535F986CAA1A2ULL, 0x799B37F9CADB29EDULL, 0xFDA0C93E1EBDFA13ULL
        },
        {
            0x7634D9CF022EC893ULL, 0x48306899C9936F73ULL, 0xAAF46DBDF146FF4EULL, 0x5641A6732391B001ULL, 
            0xB95874AB60B397A3ULL, 0x2D4B67FAA67C6C21ULL, 0xFFCC12F2E4FB50B0ULL, 0x4154ABA517BB93C0ULL, 
            0x5F105F241067F137ULL, 0xB57335613E6EF709ULL, 0xFDA2E4B6682CC610ULL, 0xD3E10AC78AE4038CULL, 
            0x49E49520CE4CB554ULL, 0xD36A32E6E4627D44ULL, 0xF366C46D35848C66ULL, 0xA637D9BCE4E81C9CULL, 
            0x80ED2F9900B09ACAULL, 0x72F5FD339C009AB5ULL, 0x8EA661DAE6E1AFA9ULL, 0x5ACABF41666B93ACULL, 
            0x9351C53912EF5EA9ULL, 0x92282DF86238FA6DULL, 0x0860BB95199BBD3EULL, 0x1C707904C7166C9EULL, 
            0xFD0BFCCD8E19732BULL, 0x471A3286C78B3E3AULL, 0x2F06A47289E68137ULL, 0x62C02C4BA6BEC92AULL, 
            0x4084F477EB086646ULL, 0x594C0D0F52CFBAA5ULL, 0x46E16735EFE706F7ULL, 0x9CEBCCF5B767D17EULL
        },
        {
            0x857BCB60D26C9F2EULL, 0x3E36BE53D9955FE1ULL, 0x1C5899B2BA94E121ULL, 0x26DB25021488E5DCULL, 
            0x524AFA4D20A325EAULL, 0xDD0F67764EA4026CULL, 0xFE5FE1B57A30B4F5ULL, 0x7F92A28A7F3940F4ULL, 
            0x4F29F73021D53515ULL, 0x653B172FFE67F8A0ULL, 0xDE73126FF4D8EA6FULL, 0x7794AB2C0B041BFCULL, 
            0xFB6A88743ADC6789ULL, 0xD5292234D4B448D1ULL, 0x9D872B08D97DCF83ULL, 0xB269B0931B146FADULL, 
            0xA4783FD6F1F9570EULL, 0x2BCA067B0248E696ULL, 0xE0CBD3151FDD4314ULL, 0x8750FAEF1A5D45E3ULL, 
            0x1D1042AE2E78036CULL, 0x8AF9A79235FFFA6FULL, 0xE91309887816E7C2ULL, 0xAC15C2153B6A69A4ULL, 
            0x813B8C351B5B73A1ULL, 0x24E82A7A1F6CCC67ULL, 0x6AABD58D9F85C330ULL, 0x4C498E7C5D87CFC2ULL, 
            0x6CD2503DC2E5C6CAULL, 0x7C4456D3068AD20FULL, 0xFF8C09917D721045ULL, 0x9B8633D22DB406A5ULL
        }
    },
    {
        {
            0xE5CA8845327E1692ULL, 0x31371A24D2577ADAULL, 0x225AA5B2F35EECC4ULL, 0x9D6D3693CB4F6ECFULL, 
            0x7974C6218A240C93ULL, 0x959034E921CB0B5AULL, 0x36BB75FE86F188F7ULL, 0x375537D0F6ED12CFULL, 
            0xB57F89227EAB3BB1ULL, 0xD6FAEB01FC097D57ULL, 0xA7D3618DDF65E973ULL, 0x0ABCFF6F4C443A78ULL, 
            0x8857C0DDEB335D8BULL, 0x5215157A78F5EF2EULL, 0xB946C25725CD757BULL, 0xBD13862BE39E429EULL, 
            0xE6E09A5B59AB18F3ULL, 0xDB7B4DD29851612DULL, 0xB09A6F9D1D9627C9ULL, 0x369BC29A1689BB32ULL, 
            0x32EF4973BE7D7B73ULL, 0xD270E0E652974EDCULL, 0x78751F93BAF9B6AFULL, 0x5631ACF6260ADF79ULL, 
            0x721786956C3C0A53ULL, 0xF02B552E723CDF50ULL, 0xED350F4F429EF49CULL, 0x00CE17C896AE7FD2ULL, 
            0xECCE3EDE0325BA74ULL, 0x974111C9FFB5FC72ULL, 0x9E0354D5398EF4BEULL, 0xF9B310BB4DB35757ULL
        },
        {
            0xA8475001908A6691ULL, 0x8946AA741EA9C8CFULL, 0xA4EE70285E32D9B1ULL, 0x56E261D9357E967DULL, 
            0x78C961572D8F1852ULL, 0xB002F96A1877F582ULL, 0xF57429D66382E7BAULL, 0xD0F89437788FCB38ULL, 
            0x8A22E4A4208D01E4ULL, 0x03ABB1D6B615637FULL, 0xF39726CD0D456551ULL, 0x47E72D50BD8BAFCEULL, 
            0xB7AA2E9A265AA4E5ULL, 0x02E061E8A960D9CDULL, 0x976211321E5CB370ULL, 0x27374826E554781CULL, 
            0xBAECBB0E50DC8CDDULL, 0xB6AD0430E42FDE6EULL, 0xF428D3B109414285ULL, 0xD375AFD4AE848259ULL, 
            0x67B4F0A22DE495A9ULL, 0x4EECD39563270DDEULL, 0x7FC2FDE0CE2294BEULL, 0x4E87C242B3FCF584ULL, 
            0x2340F5E880AA7950ULL, 0x0C4BE7AAFD7D2CB3ULL, 0x6DC5E22E3FFA9B7CULL, 0x1B2BB1C127BECCA3ULL, 
            0xE7EE9FE04B096551ULL, 0x70C36E46427E48F4ULL, 0xB725AD39CDB2C159ULL, 0x303F11E1C6FD3202ULL
        },
        {
            0xBAD784D08CC1A432ULL, 0x523AE66914167231ULL, 0x3169063CEC1C0B8AULL, 0x460B2B6DDAA7A348ULL, 
            0xDD7996DDA4C63074ULL, 0xF4239E451B5FE8D2ULL, 0x37E1734B1F5CED54ULL, 0xD6276D57E286E154ULL, 
            0x8D66D73646ABB648ULL, 0x3ED7FD4684BBC779ULL, 0x9153CDFAAE4E1B50ULL, 0x306A7C83823FE485ULL, 
            0xDE11215FEDCF8C8DULL, 0x281FA748F3C2B85BULL, 0xAD166AD856DA92F3ULL, 0xA78ACA9FF027F712ULL, 
            0xEC0CFF7F4FF09FEEULL, 0x93389408FB2EC64EULL, 0xDD479E75AE3EEC5EULL, 0xE4C38F51270F6F18ULL, 
            0x5F824C75E7FD7DE1ULL, 0x8F382AFEB3FC26C9ULL, 0x52AA3EB6878C2982ULL, 0x085FCF0D92EC89F7ULL, 
            0xE63590123F958425ULL, 0x5DF90D18917B7724ULL, 0x67F17BD3B5D87D37ULL, 0xEE42CAEE27656E5EULL, 
            0x3B963C5ED0BAD741ULL, 0x4A72010A46D77871ULL, 0x76543F04391ED7ACULL, 0x1EAFCFAB0AD722B8ULL
        },
        {
            0x6F35E36A5E4027E7ULL, 0xDDCBD5E08BA48E25ULL, 0x3BE7A4A87FEF02C8ULL, 0xAAFE145B4609227CULL, 
            0xBF5BD52C0DC84442ULL, 0x2EC3079E0BE436ECULL, 0xCC9F9CC3C170D00AULL, 0x5D6F5DF50580D1D6ULL, 
            0x7DF68C6F8C1FC3FAULL, 0xE7C911A716D7C28BULL, 0x492AA683471DD375ULL, 0xD879AE8BCE503955ULL, 
            0x36E765CA362D0C41ULL, 0x3C48FA32F7F9552BULL, 0x11D43E70BB40269BULL, 0xE71FB66D74304E93ULL, 
            0xACC980C87B4EDFAFULL, 0x5CEA3DDB2EC5F560ULL, 0x1247518A2C6B7273ULL, 0xC85852A8E46CF98FULL, 
            0x9476178944E51EB7ULL, 0xCAB616AD57EC71EFULL, 0x3EF0D9B7328BB8A4ULL, 0x2E196A09F4F5F46EULL, 
            0x7331599D4B010373ULL, 0x0CC7F9B44C0292B4ULL, 0x6AEF8C5EE379654EULL, 0x7891FD35690D067DULL, 
            0x0D346BCDAD7088BDULL, 0xBE326434390FC2C8ULL, 0x58098E00842B8553ULL, 0xAB642C4FDDC92BA1ULL
        },
        {
            0x6F4559E5A957AB65ULL, 0xE7D64F1CC019B570ULL, 0x01F61719F1CFB238ULL, 0x33697A861E9CA890ULL, 
            0xA4A7A7AF29AF9790ULL, 0x395487E4462F5BBBULL, 0x08191915D682D32DULL, 0xF0B17BC18B02BE00ULL, 
            0xFB2331E676E461C6ULL, 0x3E8A6DFDF0C82442ULL, 0x88C833EA91D15016ULL, 0xD125AF03AE0D8ACAULL, 
            0x4B1058BDD45CB390ULL, 0xABCCCE54CF5F95B1ULL, 0xFE1DB1B1DFEE6DE5ULL, 0x6E49EC383061D95CULL, 
            0x333985D6167446DCULL, 0x694BDF3865155B27ULL, 0x2CAC9E363D605554ULL, 0x7DC7A3696431F75DULL, 
            0x948502098F8DB95CULL, 0xE1D6FA67D468EA14ULL, 0xF1378B429CB14586ULL, 0xB6094296E5245956ULL, 
            0x6F8C485E3253E6A5ULL, 0x27770D72D2C53D0CULL, 0x28C5B805E9403AF1ULL, 0xC612982D62CA35D5ULL, 
            0xD0ABD6662B901C8BULL, 0x97832107F03E81F6ULL, 0x284A8EC20FD9A8D8ULL, 0xB1AFAA186A190FC1ULL
        },
        {
            0x3B4D75ED870BB0FAULL, 0xD0E4118C8B6E6EB6ULL, 0x988EECAEC6FD2B2BULL, 0xFFEB1F25A73A185CULL, 
            0x3C2B303C51456648ULL, 0xCA47FABFCCC82EDDULL, 0xAE5A7CD1E861BD50ULL, 0xCCCA6C9DDA1F880DULL, 
            0xA19A562A8267E5DAULL, 0x7CF3F51053F8F122ULL, 0xD0A3543413743603ULL, 0xDA9E60B44F5A39F6ULL, 
            0x23A556B2ECBE7583ULL, 0xB2F04CE5937AFC52ULL, 0x9BDCFFD66D477B08ULL, 0x49896A1932B27965ULL, 
            0x4CCF5F224E169C56ULL, 0x1C255CDACD99C480ULL, 0xD82C34345DC6AEB5ULL, 0x1FA24862E866CBC9ULL, 
            0x829C3EDA51D542ECULL, 0xD83E46918133FA4CULL, 0x09BDFF700352A4B2ULL, 0xB637E0935082F39CULL, 
            0xEED71BF3BCB7B8CFULL, 0x4D934A9B61D49A99ULL, 0x595B396B2ACF2E20ULL, 0x0C0B2A46966D5238ULL, 
            0x9604C6C7A37FB08DULL, 0xA6953ED6CD251617ULL, 0x0F2014E18E7F4191ULL, 0xB145D41BFE728C55ULL
        }
    },
    {
        {
            0x6E4798A01F3B25A0ULL, 0x2B65F40CDD80A671ULL, 0xC530D0BC23224ECAULL, 0x6F70C144BC6A67E1ULL, 
            0xBDD8722A964CFB2AULL, 0x15F95E006A2F915AULL, 0x450084A519A655E1ULL, 0xC97047684DE7C224ULL, 
            0xCB385F5F34FFB37AULL, 0x91FFC63CCD796999ULL, 0xCFA0DC098089A2A3ULL, 0x9712DED9ED185BD1ULL, 
            0x03E9A17BAAF4C25DULL, 0xD670C8B608627A8AULL, 0x975273CC34D56981ULL, 0x0F8716845887ECE9ULL, 
            0xD967A937C12E1D7FULL, 0xEF54F00667DEE122ULL, 0x0A7D61425FD5CA6AULL, 0x7A25D52F09F89A57ULL, 
            0x5B122E6201FB881CULL, 0x4AE5A65BACEB8724ULL, 0x766F83F88E17E0B3ULL, 0x3A060187B7057244ULL, 
            0xFD91445D60AF51C4ULL, 0x461DF4408F0AEA29ULL, 0xE22E8E6AA37F8DE3ULL, 0x78FBC404D31B8454ULL, 
            0x242F94B44775819CULL, 0x0DBE934DD9583E07ULL, 0xEE1F82D7780797E8ULL, 0x9E59425198624C3FULL
        },
        {
            0x84BE968D191908A8ULL, 0x5112F54703B5DCF0ULL, 0xF0B2ECC7038FBC71ULL, 0x2F398C11DB7E6E0CULL, 
            0x1F5670264FF56EC3ULL, 0x3FFF575E1628E30CULL, 0x6702BC8C8FA0AE0CULL, 0x8BC6CFE4DFB74F22ULL, 
            0x40B3C0CD1BB3D9DEULL, 0x2B3A50A91692D6B2ULL, 0x2B01DC38ED1A8632ULL, 0xBB0FB991D72FF1EFULL, 
            0x69D711FECC0DA6A0ULL, 0xF2A5CC97A97D457AULL, 0x36D28019707CBD03ULL, 0xBD0BB2AC89DF994DULL, 
            0x856EEA9A83150AE4ULL, 0x43B289BE15147396ULL, 0xA392D84BBC2990E7ULL, 0x2E68CC1D40DBB412ULL, 
            0x586357CF62B94EA6ULL, 0x6711B24EA5E99BE9ULL, 0x4F81F7EFD1927C39ULL, 0x38D1FB30CA42D00DULL, 
            0x97F80458132CB4ADULL, 0x2E6D1D3F885F222AULL, 0xB8B62E873ABA2953ULL, 0xF62ABC0F898F082FULL, 
            0x44BCD0631FFF7E03ULL, 0xC67CD32FD68849D4ULL, 0x3C75650952BA643AULL, 0x126E4FF66D772513ULL
        },
        {
            0x4F85C61E5DA7E369ULL, 0xF153634EF5BA3A76ULL, 0x529DEE4794B54C61ULL, 0x0BF1750075EF5370ULL, 
            0xDC181877BA20E22BULL, 0xA7C55929CD2232E6ULL, 0x44A28DDCDE46155DULL, 0x493F7F263C089EF9ULL, 
            0xB1E7B04B5EFA4DA2ULL, 0xF78C192EF8EF7C31ULL, 0xD76A1B4C8EE7CF56ULL, 0x96CCCEBC9878D608ULL, 
            0x48A6106DE7566E2BULL, 0x57359934E22C9DBDULL, 0xED5CF5E1C986C4CBULL, 0x18E9A9D4C00D293BULL, 
            0x00982070D2D8418FULL, 0x77E61570C302E51BULL, 0x7FBEC46AF7E9D018ULL, 0xE74B9894D1836367ULL, 
            0x4333E9C19945526BULL, 0xFA17380E34610E31ULL, 0xDB65BD63A06E63A1ULL, 0x9AA20D75778E49E0ULL, 
            0xD01CC09D6B54E7A1ULL, 0xF2953A675D38D0DBULL, 0x375B3CD0769D6B12ULL, 0x4F4E4D7519D1E7F3ULL, 
            0xEEB1A53EC8B77798ULL, 0x74CAC7DEC87C1C96ULL, 0x3832230EE445248AULL, 0xEA96FCC81931ACF8ULL
        },
        {
            0x5337600A414E6CC4ULL, 0x1BAFC3AE2C8C470FULL, 0xD00A7BE2BA7E1184ULL, 0xCB6BB17BE6AD0BC1ULL, 
            0x7BB26AD34D626BFFULL, 0x5E2E18ADFBAE6C53ULL, 0x54D5B5AFF8046596ULL, 0xB2CE1BDD9BE7F176ULL, 
            0x3C3513C8698E6EC7ULL, 0x7194A2A771DEDDACULL, 0xCAAFC7A266B21298ULL, 0xCF76C173223F12B4ULL, 
            0xE2ACBB0F35B976E0ULL, 0x57AD4724F2C72E29ULL, 0x6FB7A6D704786DB3ULL, 0x5963D33609CB4BA6ULL, 
            0x5BD50437E4BE6C1BULL, 0xD53CC4794AC6671EULL, 0x9FA4BF0B3284E259ULL, 0xDDBD689667ABE2F1ULL, 
            0x192A6C1C79AF2110ULL, 0x85693ABEDF0F1A0CULL, 0x696492A0A499BA66ULL, 0x233FD5522DCBA67CULL, 
            0x16F0EE73B13BAA22ULL, 0x500FCF15260DDE3CULL, 0x2705788040D80DFAULL, 0x21931846F632B89FULL, 
            0x6CEAD29EBA8A2254ULL, 0x821991348B2CFBD0ULL, 0xF656F542F18B7B8AULL, 0x3081FAFC87C10C21ULL
        },
        {
            0xBB2DEEAE5C725056ULL, 0xB23857B991730B31ULL, 0x5EA73CDEDBA62B3DULL, 0xD54D4F64E506F657ULL, 
            0x48BF95A66F0643FDULL, 0x16666F7FB755ECCFULL, 0xA0B087837DE15485ULL, 0x2310DDCBE766ECE8ULL, 
            0x3CE063A2C04E4032ULL, 0xA642148AFE9F3FB6ULL, 0x7FC0C226008A2089ULL, 0xF5C08DB66AF546F4ULL, 
            0x1F76C8DFBF3D9891ULL, 0xF97FFB48E08355C1ULL, 0xC2456D91B9B5BC0DULL, 0x98F3B49602486B19ULL, 
            0x1B3D597DE1E51038ULL, 0x56EE2B10500AFA88ULL, 0xC535AC0FE737A86FULL, 0xA70FE56C2EA80F2EULL, 
            0xE2D0086649C27EE7ULL, 0xEF0CFFB8ABBDBD7EULL, 0x2D659B29F04E65EFULL, 0x7875AB4AF265087DULL, 
            0xEF20B21765868711ULL, 0x60CC635A9D6AFEB5ULL, 0xE6F8ABD162ED318CULL, 0xC80050C206076082ULL, 
            0xDDDD12A6EB3D8527ULL, 0xD4766D14591A39C0ULL, 0x8242D472C94CBAC6ULL, 0x57824CBFE484577AULL
        },
        {
            0x7EC3F4C7134A88E5ULL, 0x9747DCD48C81BCF4ULL, 0x67C2E3C13F068189ULL, 0xDAF434823472DA0FULL, 
            0xC690185DC86BB426ULL, 0x666869974A5403E7ULL, 0x01811C2DCFBA11E6ULL, 0x347D9DE5B1F02FEEULL, 
            0x4E35FCDD2C0BB734ULL, 0xFD79BE2B470549A8ULL, 0xC2C0CFE51DD45F58ULL, 0x17BF5BE2B87244CEULL, 
            0xE8FDCDBB75A916CCULL, 0x389DFF9C69A8AA61ULL, 0x774BF3836881A3BFULL, 0x083CF4A4B6E31179ULL, 
            0xFF88F555644BA743ULL, 0x15F83D836A2D874AULL, 0xD59FCA8029265CB9ULL, 0xB9F877762E5473A3ULL, 
            0xE420EB113BC1E22FULL, 0x1BD1FB7AD4D3351CULL, 0x5A7E288F472E2DC3ULL, 0x5610016D2BAA72C2ULL, 
            0x7096530FDA9FDAB0ULL, 0xDB513AD2599DC5C2ULL, 0xA41BD1725BCF4683ULL, 0xAF4E4C47875AB3C8ULL, 
            0xFD54404E74330B82ULL, 0x80293BF33FBE2609ULL, 0x5A52FDE3569BF884ULL, 0x7906CEBC1FA37564ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseGConstants = {
    0x87214874686CC031ULL,
    0x5AE1332CF366BE18ULL,
    0x4E27CB01A2F87A5FULL,
    0x87214874686CC031ULL,
    0x5AE1332CF366BE18ULL,
    0x4E27CB01A2F87A5FULL,
    0x72F9573D7AE34274ULL,
    0x0F88E3D05CE6B1EDULL,
    0x83,
    0x88,
    0xFE,
    0x26,
    0x3D,
    0x31,
    0x0C,
    0x40
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseHSalts = {
    {
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
            0x7671AD6C2BEB9A6AULL, 0x3DA18BB1A08EB8D3ULL, 0xEBD93D196B5660FCULL, 0x40C8937D9A394FADULL, 
            0xD3D91C9FA40481D4ULL, 0xAF8AAFD05C656408ULL, 0x6165BDA2D887CDD9ULL, 0x8A9C47AEE19BAC3DULL, 
            0xE36FF577BDD979F9ULL, 0x5684B41FCF54DDD8ULL, 0xA097121F62D45ADBULL, 0x1B16AC3739020FB4ULL, 
            0x83E0C50F3DCA7E08ULL, 0x883FD054F84455B6ULL, 0x4D59E3C8675844F3ULL, 0x51AF2595DA64A44AULL, 
            0x2AAF30178A101867ULL, 0x48990EE49C33B86AULL, 0x4B53925F2B475488ULL, 0x04ACDA71848CB928ULL, 
            0x2327CFF922D03ABDULL, 0xF33E17DD692ADAD6ULL, 0xAEAAF4AFFA12B340ULL, 0x065CCE27F2B45A42ULL, 
            0x434EE5D10BCB3406ULL, 0x624EC6B02A8C2B1FULL, 0xEA4EFFC8D5CEDB88ULL, 0x0EEE3562823BF7A5ULL, 
            0x4529010988AF9261ULL, 0xE7AF07D64F762E42ULL, 0xDF756713CC1AA659ULL, 0x7868FA0AF0F96EEBULL
        },
        {
            0x06263C1BEE34133AULL, 0x7F867E20E00C7827ULL, 0xF85DF037C0420020ULL, 0xF798FB48C50D987EULL, 
            0xF3CACD4C85C1C0D2ULL, 0xCF29567E99F43BC9ULL, 0x74A26BCA360DDA93ULL, 0xD3137D93A9950515ULL, 
            0xE17EEF5514F32E6AULL, 0x57961D7A96D84432ULL, 0xE2C52DF29DD8771BULL, 0x7ACEA4003F180206ULL, 
            0xD80F1BB40980DCFDULL, 0x61FA578F8AA6CF56ULL, 0x5C1A0CBC613117D1ULL, 0xC6132DA38FFEB452ULL, 
            0x50F253383F61C602ULL, 0xD76369EAB4E8D4F2ULL, 0xCF943AF8BAD54FBDULL, 0x5C0FBB67141843E3ULL, 
            0x8FC381A231BB2908ULL, 0xBA3FF878963329E9ULL, 0xD661B435F9345267ULL, 0x905CA3367D35F813ULL, 
            0x56A5DEF29781097DULL, 0x2C8819027E1CB179ULL, 0xEE2164E072AA7393ULL, 0x08A8AA5B1B16E295ULL, 
            0x37A8FE0B09ACD737ULL, 0x0D801D6BF099A2B0ULL, 0xF9E8CC2792F46085ULL, 0x74D1144E1C84CE49ULL
        },
        {
            0x476A05EDBF539E56ULL, 0xFF9CA18FCBBD953BULL, 0x5D9DDC5C8D907097ULL, 0xA8931E627DDF85A5ULL, 
            0x7FCFBA745606162EULL, 0x07501AADF9E1E3C2ULL, 0x2F64E6D5E350B309ULL, 0xBD60D631059CBED0ULL, 
            0xDA9ADC6A4ED77681ULL, 0xFD5BAA888F8DCCDEULL, 0xCE65D0D88237BC14ULL, 0x12BC9D4B2A49B3B4ULL, 
            0x214C3D2DBD727F94ULL, 0xEE1ECBC0F7E3BAB2ULL, 0x94266AC4F7A5E965ULL, 0x08F559BEEAB2CD31ULL, 
            0xF61D3079B8B5F30EULL, 0x3658468FCDBE623EULL, 0xED21F48D35D1978DULL, 0x09300E47A6B77271ULL, 
            0x3649195241939D4CULL, 0x0765C3E8C9BD36FAULL, 0x7A95EF5D474BAAE8ULL, 0x94F43A640D5B8E7DULL, 
            0x290B30DE253652ACULL, 0xB707938783365F59ULL, 0x6076E66AC876425AULL, 0x3BE2ECF9EBFEF77BULL, 
            0x133158E11C838458ULL, 0x316991A2E32DDCE6ULL, 0x63A139CE15A0EB0AULL, 0x514D791503908639ULL
        },
        {
            0x809A3454F58F5A84ULL, 0x88E19113522A8863ULL, 0x59381E5B4F5FF63DULL, 0x9086AB53110C53FAULL, 
            0x71D05DDE75E35363ULL, 0x6BAFA128EBDD5F30ULL, 0xB631C2C19B90AF9AULL, 0xC6F41C7AF6E18198ULL, 
            0x74FB9F95A6C2CE95ULL, 0x41889877A7D77977ULL, 0xA8B92CD7FD90472DULL, 0x2477D05410A27FEBULL, 
            0x0D812F70D7270BE8ULL, 0x0B69FCFBE287009CULL, 0xE627C47FF288F78AULL, 0x1101D8950F127C31ULL, 
            0x90B6F2EC5A8A34F2ULL, 0xAEDA12B5C102D033ULL, 0x084430B31EC709BAULL, 0x8A637B504DC97A3AULL, 
            0x1F3FF696B0A3A2DDULL, 0x4AFFFB3B4840D637ULL, 0xB874B9E36D488145ULL, 0x853CF778B6FF2024ULL, 
            0x9F12F0D08070F4BCULL, 0x413DAE78473B4F55ULL, 0xA6B5E756ADBA6CB0ULL, 0x739E7099CF709A4DULL, 
            0x2FFDEA963F57F84AULL, 0x3C7994A3157A5CE3ULL, 0x065D637F5959C1B8ULL, 0xEF9E01A0B45BED20ULL
        },
        {
            0xF7769E1E57396549ULL, 0xE7E4797056CCBB27ULL, 0x7251478E91C97E27ULL, 0xCBA14E40B7814021ULL, 
            0x7DF1439285A17314ULL, 0xADAB98107B42AEA7ULL, 0x43E4CB3F4FAADAD0ULL, 0xEA32AD1EE4FBC202ULL, 
            0x5F7DB37D80090DC0ULL, 0x9ECD586CFCFFE6AAULL, 0x6916BD1A8064CFE4ULL, 0xE5E75EBFD31D39AEULL, 
            0xEA82355361DCFAD4ULL, 0xF4AA5D9076C2B97DULL, 0xA4D87F02334A9A80ULL, 0xDFBF9BDFAFE7B058ULL, 
            0x2F32BE91120F8727ULL, 0xA8A95DB31E33D2AAULL, 0x1C99C4AE4046EE9AULL, 0x0FB0535DBED75595ULL, 
            0xABC2F7BC1F400F0FULL, 0x2D9E9897CDA5DC60ULL, 0xEF00775B3C35CAE6ULL, 0xDAC3A21473A1FA4EULL, 
            0x37315209B51DF600ULL, 0x8E219F00018546DCULL, 0x115935452F013169ULL, 0x1D7CE3CFBDDE2529ULL, 
            0x3901FA890E0E9E23ULL, 0x4B0AD4AAA2830171ULL, 0x5147EB2E335A0FFFULL, 0x379F09D58E1466A6ULL
        }
    },
    {
        {
            0x8268484FE58F15ADULL, 0xA7C7B647E3C669AEULL, 0x7ADCA2CD7608F89FULL, 0x46D04717FFBF67E6ULL, 
            0x2B372FBB5DF14E38ULL, 0x8EE3DB891B34B8FBULL, 0x1E73D7A0CD91B305ULL, 0xDA060CF86433AA56ULL, 
            0x1815F58BB09C70B5ULL, 0x353F36BF29894CD1ULL, 0xDE1BB0E19C30BE54ULL, 0x2AF6D1D64C56A9BFULL, 
            0xD837DF76D47C064AULL, 0x1626B6FA56A8E71CULL, 0x8F0CA0060B37CE73ULL, 0x62CE79064249467BULL, 
            0xAAE63549C7563911ULL, 0x176CD9639E2BABFFULL, 0xCA579B9F8D7584FDULL, 0x6BC4C5FBD94E9216ULL, 
            0xBB3F430D80BDEAA6ULL, 0xDE20940915F748AAULL, 0x0C2BB9D7130B73A7ULL, 0x7250040EE0FA94D3ULL, 
            0xB8A4483F7E68A534ULL, 0xD80DEFBEC369303DULL, 0xB08DCFF6673509B5ULL, 0x20E3AD8B3D99271DULL, 
            0x9357DE864EEAF82BULL, 0x386E3EF187D65AD2ULL, 0x7CD500049A79C2F5ULL, 0x9738FA1D70A772F5ULL
        },
        {
            0x7AA20FD63BF4EF24ULL, 0xEF797D9090E51E51ULL, 0x24CCC5802AB680DDULL, 0xACEC86A6A256C4E5ULL, 
            0xBD1DCEAE22EED666ULL, 0x435A71A767329CDCULL, 0x617BB616E78BBDF0ULL, 0xE725BC6D9CE30798ULL, 
            0x12C9F0B1612EB586ULL, 0x4293E786FF9B68A2ULL, 0xC826635040F2F052ULL, 0xF82ED3F6D82A4DAAULL, 
            0x8DDAED84DF52F9E2ULL, 0xF31D26B3D9DB8BD1ULL, 0x6E2E04EB5378630FULL, 0x51F14DBCF69507DDULL, 
            0x9FA7659340FC5520ULL, 0xEB44A037383B181AULL, 0x6609E441857E306EULL, 0x7F8864872E7B81ADULL, 
            0xEA51552EAF9B9DCBULL, 0xEF9CD7B348B06D8FULL, 0xDDBFE21546BE0996ULL, 0xF2B82034A462289AULL, 
            0x9C3B92F7DE35C0C5ULL, 0x6635C987EA1382CDULL, 0x7DCBEB0B2168EF7DULL, 0x379F4D898A8F9E28ULL, 
            0x718E41506510D259ULL, 0x45436380F0EFC622ULL, 0x2E215C3265337CFEULL, 0xDE5FAB8B7E041EAEULL
        },
        {
            0xDE8F3D75C12EE1B6ULL, 0xFAD79E4E544C5A68ULL, 0x6D5B0D9D7DC36A95ULL, 0x166021BCB078F205ULL, 
            0x5980C86D40E1D40DULL, 0xFCADAD13C466D21FULL, 0x700BB1CC51786D8AULL, 0x0D7DC29F3541F606ULL, 
            0x9002852DE6F9AFB9ULL, 0xB3BEBFE30FE48D09ULL, 0xCA9A202DE64B7CB2ULL, 0xF6ED1B98ADE5A545ULL, 
            0x3DAA884E7FFE8F0CULL, 0x047DB4048157A602ULL, 0x87A997F6E6A8A6B5ULL, 0x2E9AC66F8CDAA42FULL, 
            0x361294CB59C4544EULL, 0x790A0346A361EAB4ULL, 0xC010B3DA8D4AAD83ULL, 0x66F8F62E42EFCE81ULL, 
            0x65E660D3B81257F7ULL, 0x1CC98AEAD03ED247ULL, 0xEE9B5A043D41F84CULL, 0x43EEA13F27FB2666ULL, 
            0x1C372B3A2324B34FULL, 0x963265EEB877FAEAULL, 0x889600C03E60E02EULL, 0x674DC61809C96FB5ULL, 
            0xBA06290796842771ULL, 0xB96F37D6FBBB77F4ULL, 0x97C61D715E03CC4FULL, 0x32E10265EA10E20FULL
        },
        {
            0xBF4E5C71BFE1B4BBULL, 0xA64E091CEE24720DULL, 0xE4AFFDF8D9693D06ULL, 0x76D8FA16BB2A8E59ULL, 
            0x19FAB8D5FC91F458ULL, 0xE8C88DEF9C969961ULL, 0x9E9DF0CB6BB75E14ULL, 0x0923139080371247ULL, 
            0x6CD47F8FF147EB82ULL, 0xFF8F982B79CD76BFULL, 0x28659336E4C32088ULL, 0x8B0AF8C6EBD0067FULL, 
            0x4B83E88F88FC27C4ULL, 0x3CF659DDD9B87880ULL, 0x3006C63A65C22A5AULL, 0xBECAD253063192E3ULL, 
            0xDE6421A352E2E97FULL, 0xB60056D332E91B32ULL, 0x24B1F83EF60FEDFAULL, 0x4ADE56B9B126A6A9ULL, 
            0xD8543965F0768AFAULL, 0x50DA7DE13A479B9BULL, 0xD9DAED4C75EB4044ULL, 0xDD3E5C7DF2BAEDDEULL, 
            0xDEE8788A618EDF09ULL, 0xBC0EC268E7DDBDBBULL, 0xCB9C34AC563CFD6CULL, 0x5547990741143047ULL, 
            0x57FA2F72CB8E7B64ULL, 0xA8C7C6B024EEE67AULL, 0x23A1E94D62DF4E8DULL, 0xEEA99C5DEDF1BEF4ULL
        },
        {
            0x028FB0AD8DC52E68ULL, 0x3618279DE491A8C9ULL, 0xD7405BFC8939DCB8ULL, 0x04135EE2526E72F0ULL, 
            0x4FD55B77E835ABF2ULL, 0x8A70CE9A71CE331AULL, 0xCDE2C18B77F9CC35ULL, 0x315E0DD7D04F8CEEULL, 
            0xD7D010AE3F5F5D82ULL, 0x5A7C0F979CF1434EULL, 0xF2B1093FF2306A9BULL, 0x06B63D9308C47C87ULL, 
            0xBFAFAABAA4566C42ULL, 0x83620FDDE8A733B3ULL, 0x4BB511C7CF03FBF4ULL, 0xAD09A06A61F6AA5BULL, 
            0x65DABF63E827E77AULL, 0x8630F9AA921AE05AULL, 0xB48953FF43D94141ULL, 0x1E96F6617D22B514ULL, 
            0xF63F07BAC1D61FBFULL, 0x88032AD850C4EE1FULL, 0xED895A2E142DEF96ULL, 0xFB5D706C5131F8AEULL, 
            0x668819219F3D6842ULL, 0x95D4631B10FF81E4ULL, 0x9044C3C408E2DDE0ULL, 0x03613C616E457ECFULL, 
            0x11981202B0526761ULL, 0x12135809800AEC33ULL, 0x416BC481E83C4A2FULL, 0xBFFFDAFD200B9C18ULL
        },
        {
            0x34888215645DBD97ULL, 0xF5DC7EE02DD27C8AULL, 0x27DBE7DFEACC172BULL, 0x4A80D2F63F5BC405ULL, 
            0xC5F8984284C04DB0ULL, 0x6515069573971ABCULL, 0x8DAB9938DEE71C44ULL, 0x4CE5DEC586145E95ULL, 
            0xAE5553C26E522B62ULL, 0xB263445F8ECE1F89ULL, 0xB8207ED11153066BULL, 0xAD0A109B2E04B2C6ULL, 
            0xD0E6636E796956ECULL, 0x92650CB268F4D2EAULL, 0xAF96546802BDFFF5ULL, 0x9B1ED57F19643B36ULL, 
            0xABF5EE219012C59FULL, 0x81065641970C4354ULL, 0x08C469213DE147E2ULL, 0x47E96DB8FA30AECCULL, 
            0x95D797BE6A2EC288ULL, 0x8C7A89D619B590C8ULL, 0x2088EE9D605847EEULL, 0x5FE574C86126F846ULL, 
            0xA9D81E8BB3FFA0C3ULL, 0xB9EDF438031463D7ULL, 0xB3C119187FD9184FULL, 0xCB28945B0A37931BULL, 
            0x3AD38D48BAAE2D7AULL, 0xD74B4C1D2CC4664AULL, 0x84DB16D4CD284BD9ULL, 0xC70E401E05E0B286ULL
        }
    },
    {
        {
            0xAD8A2611990452DCULL, 0xC9198F92FE0845D6ULL, 0x009E74DA13790330ULL, 0xB55940E919FB0820ULL, 
            0xAAFD24E2C8AA4363ULL, 0x357E6D3161395438ULL, 0x848B115768EAEA52ULL, 0x52865E198A36D02EULL, 
            0x836ACB919A93F6C6ULL, 0x0849F2FB16AED72AULL, 0xC8B1238429D24D05ULL, 0x66C2F4DCF767C74AULL, 
            0x74B7022188F27535ULL, 0x4A9D1424EA059343ULL, 0x67D0CC1679EA8D3DULL, 0x015CAA652092E643ULL, 
            0x602BA69A6B317526ULL, 0x984983099D5350C1ULL, 0xB55F2EE4367140A1ULL, 0xE8EFDF92C3B50EF7ULL, 
            0x3F672DF583748F74ULL, 0x936A1ACC5EEEDBB5ULL, 0x76C5690085C2F27DULL, 0x8D9DB3C398CB30FEULL, 
            0x4BE885B0D67D8D78ULL, 0xCA6D35894125A1D5ULL, 0xF593932AD9E7E3EBULL, 0x826F314DAA699786ULL, 
            0x5978B98F5F101190ULL, 0xA09EF195716F2702ULL, 0x184797C1F4115051ULL, 0xF8A13264559FF119ULL
        },
        {
            0xE98FFD32C253E362ULL, 0xF0D5DC67769171F2ULL, 0x2370314C0EFC7072ULL, 0x893F83D9E667A700ULL, 
            0x74557180AA6862C5ULL, 0xE05D412E184B23A7ULL, 0x2492B2D13AAFF1D2ULL, 0x4EFD5C21C6376BA0ULL, 
            0xC91B0F9DC3DF4D27ULL, 0x7534AD0969588884ULL, 0x67801004FA53B519ULL, 0x3D79FB445DC180F5ULL, 
            0xF1BFE9656306830AULL, 0xF41D149AEA7A2F18ULL, 0x7A83425224400041ULL, 0x9AC576FC27516AFCULL, 
            0x60E04BC5C0E299DAULL, 0xF6ECFE755F2DDA6DULL, 0x16AC9E45A71B7EBEULL, 0xBBABD11EEF8A937BULL, 
            0x022E46C04AE74DAAULL, 0x1166E2E367945C31ULL, 0x0E278278B3DA1877ULL, 0xEBD0426694C6A6DAULL, 
            0x4AED0B04446508C8ULL, 0x29DDCF805461A3B5ULL, 0x5575028799AA3D65ULL, 0x04974F58CBF8C6DAULL, 
            0x75A655CD986D5610ULL, 0x576B9BAF11484ADAULL, 0xD6BAF8CCD8773114ULL, 0x18BE5917D5C486B4ULL
        },
        {
            0xBC8BBF26020EEBC0ULL, 0x64AA1A52E77091C0ULL, 0x2E7190A224B2A3BEULL, 0x9842A086CFC8E43BULL, 
            0x078C418CA79E4A22ULL, 0x6C63DAA533BFC78BULL, 0x26F4CA9F165D0203ULL, 0xB445F12A31636208ULL, 
            0x6F241EF71813B550ULL, 0x7C0A6574E9BC43BAULL, 0x563F8203AD714823ULL, 0xBEBACAE97B43BC13ULL, 
            0x2D0F529390D7E5F4ULL, 0xBD5F4E08360D759DULL, 0x4E9DBB08A7EDD25EULL, 0x655FE2BFB6CAD909ULL, 
            0x657698160146ACEFULL, 0xD08EEDC50080DB69ULL, 0xF762673671530BFEULL, 0x7DFBC4AA3C9D9321ULL, 
            0xDB521EF48D70DBE8ULL, 0xC2ABD15DD1810553ULL, 0xAB18C1B0D7E51272ULL, 0xF7D6CFF8E8596242ULL, 
            0xED4B04441D3F2894ULL, 0xAAA549C4B76DACF6ULL, 0xD119F416DDEA8E1CULL, 0x9B76E7A9E3A1F35FULL, 
            0xFE5A17F5BA4CA2BEULL, 0xB23A4B308E40803AULL, 0xEBA63758CB8C3BCDULL, 0x7CB9FFFBCAF50DE8ULL
        },
        {
            0x2A5314B082D308AEULL, 0x1986511E4E0A8F64ULL, 0xCE41FB9A4D5089EDULL, 0x859AFAB718677A25ULL, 
            0x1B7AAA3279A1AA29ULL, 0x7E7439507712832EULL, 0xDE487FA0828E818EULL, 0xDC1FA0F06C8B279FULL, 
            0x462C9BA08DB852D0ULL, 0x4BCE748CAB548EC2ULL, 0x797D953654C98E77ULL, 0x2D435F31026A6DEDULL, 
            0xC95E607F84058CB6ULL, 0x49235BFAB5D4C56AULL, 0x0891081FB5187F08ULL, 0xAC3BB34EE3AADD8FULL, 
            0x93421F652CBBE61EULL, 0xAB117A0D09C8D493ULL, 0x979B28470658B9E6ULL, 0x79C6DAE5382BB88DULL, 
            0x3116FFC574370DB1ULL, 0x5C01265BDDCF620DULL, 0xC9C9BF65C837216FULL, 0x72AFC21959F96D9DULL, 
            0x02C22F183EEEBC84ULL, 0xE7857058B5FF6EDAULL, 0x07238BBDF48E4960ULL, 0x5B95C4938F8C3447ULL, 
            0x19D5C4457EF99DBAULL, 0x76A41C5CF665170EULL, 0x6353367C0A347D63ULL, 0xAB4F1E92AAF12454ULL
        },
        {
            0xB47D07C28D327F61ULL, 0x00B8CF613B19DCA6ULL, 0x407F54F2F369AE25ULL, 0xF5D5D79652531849ULL, 
            0xC9FB0B484573FFCEULL, 0x717A0886426E99AEULL, 0xC37FD72E50EC96BDULL, 0x7B19E3BF5B6FE091ULL, 
            0x148DD5476721BFF5ULL, 0x464897CBE85C4BDCULL, 0x380EF6C04EC1195EULL, 0xA0C93096368B6A33ULL, 
            0xBD7DBB0BD140DEDBULL, 0xE317BB9BB8BB5330ULL, 0x26AD06271FCE6434ULL, 0xFE69C4AB277BAEBAULL, 
            0x8BC1BC27C4F489BDULL, 0x1E055EEB1AEF41A9ULL, 0xC28A00F29D64751DULL, 0xD30E174F5031A95BULL, 
            0x3D2D5C0196CAF973ULL, 0x39590099E1D792CCULL, 0x5326777E78567027ULL, 0xFC6008789C193BB7ULL, 
            0xABEACF9CCCEEB69DULL, 0x5DDDA7EC9E3DF92FULL, 0xA99463EF2A683C7EULL, 0xC2F0FC66F144663AULL, 
            0xA8D95283A43F6EF7ULL, 0x0D34ADDF835D7990ULL, 0x489D12AB41C99472ULL, 0x6544230AED14ADBBULL
        },
        {
            0xFE1414B224F8B967ULL, 0x92B2CBEB81201F57ULL, 0x3C92801D3AD0F07FULL, 0x0E5929C0CD65EBABULL, 
            0x1E3059D9D134D797ULL, 0x9E211C1EC0EF42F8ULL, 0x27894D8275194D94ULL, 0x18B236D41ED39BC7ULL, 
            0x1A44FED9CE584EA5ULL, 0x1D0651B5E416018AULL, 0xD79F3CB30CC4F2B6ULL, 0xD621D7067182709FULL, 
            0x243BCB9B3FA6F013ULL, 0xF7A2CCB2E4376BD4ULL, 0xBCFE456100DCE9F4ULL, 0x9B9983F09D3BBE5FULL, 
            0x7FC9EE9596D5117AULL, 0x2901B0589E918187ULL, 0xE8D17549278DC678ULL, 0x77B4E300018A7E4DULL, 
            0x7BCFB04BF01840BFULL, 0x9E725C9B2FD31A3BULL, 0x0CE8445D740FF0ACULL, 0x498A7DEBE090C4B0ULL, 
            0x8D16250FB8DA450BULL, 0x4C903C9F6E8C5B22ULL, 0x5AE06990BE0C7087ULL, 0xAFEFF47CE7E2C530ULL, 
            0x44E4722920D340B8ULL, 0x0BB8F6DF1A374732ULL, 0x6D17606AE4422CECULL, 0x428F12E5B1496239ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseHConstants = {
    0x48A5074AE22855D5ULL,
    0xB1228A0A6388120EULL,
    0xC27109D9682869C1ULL,
    0x48A5074AE22855D5ULL,
    0xB1228A0A6388120EULL,
    0xC27109D9682869C1ULL,
    0x6608A3A5327FC6D7ULL,
    0x5D640FEC95F36488ULL,
    0x7F,
    0x63,
    0xA9,
    0xA3,
    0x89,
    0x56,
    0x41,
    0x69
};

