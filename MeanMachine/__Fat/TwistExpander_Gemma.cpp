#include "TwistExpander_Gemma.hpp"
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

TwistExpander_Gemma::TwistExpander_Gemma()
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

void TwistExpander_Gemma::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xBE1E467A459E2CCEULL; std::uint64_t aIngress = 0xD1A22CBF1D8E7730ULL; std::uint64_t aCarry = 0x8541C0113CD75159ULL;

    std::uint64_t aWandererA = 0xA09E776C4260A5BAULL; std::uint64_t aWandererB = 0x88769A88D4C66C35ULL; std::uint64_t aWandererC = 0xF9B08691DFE5C0F3ULL; std::uint64_t aWandererD = 0xC26F71FC86133097ULL;
    std::uint64_t aWandererE = 0xF4C679622DF0823AULL; std::uint64_t aWandererF = 0xD73D25B668FA2B4CULL; std::uint64_t aWandererG = 0xE52ED66458EE900CULL; std::uint64_t aWandererH = 0x9B4BE8CACB18EF32ULL;
    std::uint64_t aWandererI = 0xB38256DCFE095741ULL; std::uint64_t aWandererJ = 0xC8E6C5E0EE9C6727ULL; std::uint64_t aWandererK = 0xB23BFA9462A0FBAFULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9520515003486549948U;
        aCarry = 16420163941673766532U;
        aWandererA = 13659215176950175352U;
        aWandererB = 15802345287828346867U;
        aWandererC = 12221952182400170773U;
        aWandererD = 16466880480539273048U;
        aWandererE = 9613012898184207350U;
        aWandererF = 13912314523914488023U;
        aWandererG = 16577293861426448746U;
        aWandererH = 11972576989836266210U;
        aWandererI = 9872937687150953842U;
        aWandererJ = 16911766147393989341U;
        aWandererK = 10922312535046380507U;
    TwistExpander_Gemma_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Gemma_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Gemma_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Gemma_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Gemma::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xACF513E149819E66ULL; std::uint64_t aIngress = 0x9AF276DD7255AE58ULL; std::uint64_t aCarry = 0xCE6757020F4476C4ULL;

    std::uint64_t aWandererA = 0xB2A572B839936D1AULL; std::uint64_t aWandererB = 0xB6C9E41A4C9EA3F5ULL; std::uint64_t aWandererC = 0xCACCE9A13305D833ULL; std::uint64_t aWandererD = 0xF86FFFDAC9BE16D5ULL;
    std::uint64_t aWandererE = 0xF379929174D6572AULL; std::uint64_t aWandererF = 0xD274E0ACC2783FD9ULL; std::uint64_t aWandererG = 0x95B7971C195F3C17ULL; std::uint64_t aWandererH = 0xB8AA15D67A0BF7D0ULL;
    std::uint64_t aWandererI = 0xE03CB2598CEC8856ULL; std::uint64_t aWandererJ = 0xC75F381D64C1B4CFULL; std::uint64_t aWandererK = 0x99096157125AECDCULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14701780266027352675U;
        aCarry = 13158631046085438703U;
        aWandererA = 17770779587681053039U;
        aWandererB = 15231135681628698099U;
        aWandererC = 12975813673038890831U;
        aWandererD = 11815503762589951409U;
        aWandererE = 9988961592053866000U;
        aWandererF = 12388188374676266482U;
        aWandererG = 15839716418645523450U;
        aWandererH = 14538225726348568322U;
        aWandererI = 17001834989034911104U;
        aWandererJ = 11604902382249049307U;
        aWandererK = 14348308360265971439U;
    TwistExpander_Gemma_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Gemma_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Gemma_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Gemma::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xF1FB53ADA0AA827AULL;
    std::uint64_t aIngress = 0xF8332D5E28139276ULL;
    std::uint64_t aCarry = 0xFCDCCAFAF3D8DED0ULL;

    std::uint64_t aWandererA = 0x885222AFEAF9F231ULL;
    std::uint64_t aWandererB = 0xD530E6E1BD078D9DULL;
    std::uint64_t aWandererC = 0xE9613DC58C29801AULL;
    std::uint64_t aWandererD = 0xDAB4F5EC03CC549AULL;
    std::uint64_t aWandererE = 0xABC6FB5CFE8D60F2ULL;
    std::uint64_t aWandererF = 0xA6BEFF4BB1D5735DULL;
    std::uint64_t aWandererG = 0xAC85C73782C8FBB4ULL;
    std::uint64_t aWandererH = 0xFC1D82DEA32162E5ULL;
    std::uint64_t aWandererI = 0xE059562B635210A8ULL;
    std::uint64_t aWandererJ = 0xA4C52C18DD8BCFB7ULL;
    std::uint64_t aWandererK = 0xDAF92107167D181BULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneC, 1);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneC, 5);
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
    TwistExpander_Gemma_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
    TwistExpander_Gemma_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Gemma_Arx::Seed_I(pWorkSpace,
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

        TwistSquash::SquashA(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Gemma_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 28 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1791 / 1984 (90.27%)
// Total distance from earlier candidates: 49088
void TwistExpander_Gemma::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 266U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1205U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1361U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1524U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 220U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 882U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1112U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 150U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 445U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 647U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 890U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1697U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 641U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1791U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 199U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1230U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1327U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1277U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1892U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 675U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 911U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1000U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1632U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 167U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 581U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1406U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 263U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1562U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1533U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 961U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1403U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 178U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 223U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1302U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1652U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1066U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 480U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1291U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2029U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 500U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 217U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 324U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 30U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1615U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 376U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 93U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 433U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 583U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 56U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1834U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 201U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 844U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 985U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2001U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1371U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1736U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1765U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 261U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1481U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 94U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 468U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1730U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1175U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 861U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1309U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1032U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 720U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1979U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1800U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 694U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1752U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 404U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1712U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 852U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1622U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 162U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1935U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 367U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 238U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 176U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1011U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 23U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1118U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1219U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 654U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1686U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1837U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1295U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1126U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1913U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1489U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 621U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 503U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1228U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 449U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1236U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 169U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1267U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1400U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 745U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1284U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1774U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 974U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2023U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 670U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 691U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1373U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 65U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2008U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 650U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 631U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1759U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 764U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 461U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 345U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 585U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 714U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 309U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 157U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1434U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1354U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2009U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 950U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 973U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Gemma::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8660387B348FC6CDULL; std::uint64_t aIngress = 0xF45F1BB1B2DDD07FULL; std::uint64_t aCarry = 0xBCE504DC161D057AULL;

    std::uint64_t aWandererA = 0xCA0B90A76C992FD1ULL; std::uint64_t aWandererB = 0x994E426BB5B6C747ULL; std::uint64_t aWandererC = 0xBC155C48C2EC5F0CULL; std::uint64_t aWandererD = 0xB619A320A5ABA892ULL;
    std::uint64_t aWandererE = 0x891C8D219D6939D3ULL; std::uint64_t aWandererF = 0x9C435D07AF23E477ULL; std::uint64_t aWandererG = 0xC04FCC9E1E7A6863ULL; std::uint64_t aWandererH = 0xAF02ABC2D2CB6540ULL;
    std::uint64_t aWandererI = 0xD71B6180F9B930FAULL; std::uint64_t aWandererJ = 0xB021B6DCB78DBAB4ULL; std::uint64_t aWandererK = 0xCF85965846F3016AULL;

    // [seed]
        aPrevious = 12253446061087129360U;
        aCarry = 13647510148866647922U;
        aWandererA = 9897473652213476896U;
        aWandererB = 14457503969279762330U;
        aWandererC = 10650457663264652848U;
        aWandererD = 10905479211433170524U;
        aWandererE = 17305937927310641842U;
        aWandererF = 13348791351040231577U;
        aWandererG = 16224716987729473649U;
        aWandererH = 15531895370994242676U;
        aWandererI = 12704467923485710842U;
        aWandererJ = 11009436342137479235U;
        aWandererK = 9794416033502933358U;
    TwistExpander_Gemma_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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
    TwistExpander_Gemma_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Gemma_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Gemma_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 28 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14621; nearest pair: 476 / 674
void TwistExpander_Gemma::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7973U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2924U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1031U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4638U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 962U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 520U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 851U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 689U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5101U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1041U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 729U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4078U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4103U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 788U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 344U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8060U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 352U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1943U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 782U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 957U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 427U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 915U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1706U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 297U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 351U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1657U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1508U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1748U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 201U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 437U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 286U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1103U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 131U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1494U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 92U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 863U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 28 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14620; nearest pair: 468 / 674
void TwistExpander_Gemma::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3911U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7349U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5784U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6131U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5550U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4001U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4143U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4471U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4017U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4553U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4279U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4244U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3122U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2765U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 710U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6109U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1267U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 43U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 548U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1818U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1143U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 666U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1890U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1124U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 63U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 373U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 732U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1029U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 779U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1275U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 607U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1869U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1210U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1997U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 891U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseASalts = {
    {
        {
            0xDC846424983C04EFULL, 0x30FEFC32DB38F109ULL, 0xA4F4DC6738AC8970ULL, 0x15E30AAA4A341BC8ULL, 
            0xE4685BEC18F58CC4ULL, 0xC25FBDF437991246ULL, 0xAB90B8C4494E5163ULL, 0xF800521761F06471ULL, 
            0xA7F32141E3B1D638ULL, 0xA804A6724CDA43E1ULL, 0x5B79A881F420AD60ULL, 0x12FAA73DCC91BCF9ULL, 
            0xED15C8CEBFF873D4ULL, 0xAC4747EF8683B829ULL, 0x2032A65ED8860AC4ULL, 0x5A47C7A3B0BC2B90ULL, 
            0xDA4CBA4455540D59ULL, 0xA9A059284AFEA13EULL, 0xE295FB55C4704939ULL, 0x92CAFFEA56C29DBBULL, 
            0x4A79A43959A99778ULL, 0x700C955FC5C14002ULL, 0xE877065F83F5EE74ULL, 0x0428C7A39E1FDF6CULL, 
            0xD611E912E53E81D3ULL, 0x51D91746FCD32F5FULL, 0xB8BC5ED3386EA811ULL, 0xEC420399A491FC83ULL, 
            0xEB6F416B4045EE56ULL, 0x6B22B6C3C7D5C5D5ULL, 0x802C9FFABD19267AULL, 0x4647E50B953CBBFEULL
        },
        {
            0x3EEF779728511322ULL, 0x5989D47E53690A6AULL, 0x4481AA07ABBA4915ULL, 0x8EB55E587D11B40CULL, 
            0x413D370510C0FB8AULL, 0xAECF1DB85ABD5E76ULL, 0x5B1D3DD40B89F028ULL, 0x7F5A54A861D026FBULL, 
            0x6A33B56D15C29003ULL, 0x8720437BB8193940ULL, 0x566CED83B89DD355ULL, 0x1A912BD8C2A15EE6ULL, 
            0x0552A7141FFEA23AULL, 0xBF7EDA846D2A7913ULL, 0x14248F5A6F2E5380ULL, 0x2CA79B27652B9760ULL, 
            0xC6CAD4C477264752ULL, 0xEC85D7B0AF2356F7ULL, 0x56C9E1A26CDBC159ULL, 0x567C6E759712FCCCULL, 
            0xAD7A0BF524C488C8ULL, 0x0A7DB108D7ADE29EULL, 0x53CB9C36F811C388ULL, 0x553844F95C39F77EULL, 
            0xF892F70A065D6B2DULL, 0xD0C9611032B8FDD9ULL, 0xB295F8541D399E84ULL, 0x4118765602E24AB7ULL, 
            0xA47EDD9ACF5753BAULL, 0x3EDCFA787A2D7294ULL, 0xA3D3DDACEC678767ULL, 0xBD4AF7A30472B465ULL
        },
        {
            0xF900A1BCBEE7906DULL, 0xBBB033A0745C8BC3ULL, 0xD6D28989B8872261ULL, 0x66B33BB39ED48782ULL, 
            0x1E64AAE0A51E21A8ULL, 0xAEE033034A82317BULL, 0xE331839E91C25454ULL, 0xB67D854F6428AC9BULL, 
            0x6DBF4DB606A71BD7ULL, 0x0522046911A9E771ULL, 0x4EC7EE027E779DB2ULL, 0xBEF3ADD80D82535CULL, 
            0x3E5BAA9D92081AD1ULL, 0x76BA114125CCF8FEULL, 0xC051ACA968C81425ULL, 0xC4B8851BB35162F4ULL, 
            0xA723A589016BF0EEULL, 0x93F5D8CB1AF0B5B5ULL, 0x24847A40C9900D11ULL, 0x6B57244D88E92AEAULL, 
            0x8209F072DD0C1D7CULL, 0x03B52733E5527ADFULL, 0xFA420BD6178E8AD0ULL, 0xD6F162A7777C9E39ULL, 
            0x7CBD0125101F1314ULL, 0x75C7EEF5A4BBE040ULL, 0x88158AB9317EB210ULL, 0x0A1311FF4998131DULL, 
            0x4015BD3B11690B40ULL, 0x6FB14EDD9906B75BULL, 0xB64E7988577F64B1ULL, 0x10B2041A4C4EF40BULL
        },
        {
            0x91B6B29E8174650AULL, 0x80B32A72A6AC4776ULL, 0xC249846E71F5A124ULL, 0x8FC85A096011CE22ULL, 
            0xBF24AC58982446ACULL, 0x8F7066837625BC92ULL, 0x8D86AFB9450A308FULL, 0x601E442DE4004D7CULL, 
            0x990ADDC5A8917796ULL, 0x61F186F9A78D2BDEULL, 0x16BCBD16A11DCD7EULL, 0x1EF67F8C219377B8ULL, 
            0x2B38A44BFCD1A9FDULL, 0x65D33866ED1A9143ULL, 0x592BEA1C9CE0A424ULL, 0x655B32603D85A7A2ULL, 
            0x05328503430FFCFDULL, 0xDF40048FF1FD7F40ULL, 0xFA3A380726974CF3ULL, 0x9DD207985B4B5AC7ULL, 
            0x919BBADE3DE60E2EULL, 0xE96D95EA9D560EF1ULL, 0x62681125896BE9FEULL, 0x5919D082287663D9ULL, 
            0x3090E348D4107A9EULL, 0x72E52C2E916BEB5AULL, 0xD3DFDED0866E6FCCULL, 0x9DD250AAB668E1AAULL, 
            0x10DAC68DBD6826E5ULL, 0x2247FA11F84B64B6ULL, 0xAF0F722774A10772ULL, 0xAF52A7D5426C9C95ULL
        },
        {
            0xE08D85B4F6715F6FULL, 0x645D6E95019BC207ULL, 0x69CDE5578407038BULL, 0xDD256DEF4E4667DCULL, 
            0x47498F66951BFD15ULL, 0x4E18B7DB7DB52D8AULL, 0x401749506EF51916ULL, 0xF2399875F210E82BULL, 
            0x065A14F57191D99CULL, 0xD87E30DB61907203ULL, 0x6F7D546AFA8AE513ULL, 0x4B1BBE25913AC720ULL, 
            0x6AE40CFDCCCE8228ULL, 0xECCF7CDF64490411ULL, 0x3BC4FE91F35001A0ULL, 0x62C091F7C3754AC9ULL, 
            0xDE79C3F6EFF9BE75ULL, 0x9A43AFBFA7E79F6DULL, 0x8E97B263FC7077A2ULL, 0x4C470895575858FAULL, 
            0x0833BD3952502BD7ULL, 0xA2FC2212F9D26493ULL, 0xB1062DEB70893BAFULL, 0x6B443B439D82032FULL, 
            0x1BECB057616962E5ULL, 0xE6D0DA6238B13EECULL, 0xB12ED03B36F139D8ULL, 0x8AC64F321B199507ULL, 
            0x594E1963EDEFE62DULL, 0x44AF2F1013DFA089ULL, 0xB98D86BACC4BABF3ULL, 0x7B1B8EE882C90337ULL
        },
        {
            0x9DF3B702EF133436ULL, 0xC5477C4BF46CBB29ULL, 0x202ED2548DC4BDD0ULL, 0x202D25E35E488C0CULL, 
            0xAA217C0B0172B46BULL, 0x21E2576031FB6B60ULL, 0x08B89E0F3CFF17BCULL, 0xB025E60C9E42B689ULL, 
            0xAC554C935B126B8AULL, 0x7DF0B1E3C0B8320FULL, 0x1D96B25291D70689ULL, 0x9C3CD855266F3FCAULL, 
            0xB00BBDAE77F77E6CULL, 0x9830A43AFC0C2056ULL, 0x870993CEE4B09B5AULL, 0xC43E937F74A21866ULL, 
            0xDE2F247BCCF77373ULL, 0xF5CB152CADBD9A2FULL, 0x48F10E98383D788CULL, 0xE0829197687B75D5ULL, 
            0x67944C5132DB4C41ULL, 0x27A7A712D9EDD17AULL, 0x557EC7764A266E43ULL, 0xD4CCE5A7CFAC8DEEULL, 
            0x8E03802E552A434BULL, 0x74D2EAD802BFE684ULL, 0x00B2A90AA4B7EC94ULL, 0x47A719B077588EC5ULL, 
            0x635F4D8DF876A86BULL, 0x4D7CBBEB5DACB047ULL, 0x699E38A3252812F3ULL, 0xFFB49D34D1ABD5B9ULL
        }
    },
    {
        {
            0xE890471C275E0A9EULL, 0x085897B8AF6FF737ULL, 0x409F1E5A63BC5DFCULL, 0x9DC5B175B8722657ULL, 
            0x8E5EFD21BB690E03ULL, 0x5E2CF64157548BC2ULL, 0xBAFC3EC34A09AF8EULL, 0x257C691D1E05906DULL, 
            0x06C7BBA679B1380DULL, 0xDCF6C14E1F66FFA8ULL, 0xEBF71B26208F94A5ULL, 0x345CEEAC213AFE2CULL, 
            0x430DE39864DE70F4ULL, 0x710E82B7884221D3ULL, 0x50BCAB3861A4ECC4ULL, 0xB2FD523016013424ULL, 
            0xE27F5370D2133828ULL, 0x64B4291A7CAD2583ULL, 0xBB40D2F0F7260C87ULL, 0x4AB05D6CDE0D7A8AULL, 
            0xD02F7F05593EAD45ULL, 0x4EA926A771EB2E02ULL, 0xEEAF8312ECE91B84ULL, 0xF10D529E9808E253ULL, 
            0x9530292D339878D2ULL, 0x2F1AA19CDDD3CA3FULL, 0x726803B5E6A908E3ULL, 0x5EB2B6B5841C8F90ULL, 
            0xF5DEF6DC0AFCA79AULL, 0x7B767652DE08AC62ULL, 0xD44897933E6C1892ULL, 0xF18F5D0102F08DB5ULL
        },
        {
            0x3BD2DD91CA8DC327ULL, 0x00A33009B34A2D4AULL, 0x1B4598F2F0DFAA18ULL, 0x79A3D141971480E5ULL, 
            0xCD8974C013BF1602ULL, 0xBC858ECE89063D9FULL, 0xAC7A82B228B26857ULL, 0x7059014BDF257FAFULL, 
            0x3BA095AB8FD9DCD4ULL, 0xC6BA26FB8CE58DE5ULL, 0xC197F02A9BE79FB8ULL, 0x3927C7F2BBE60B82ULL, 
            0x2A3CF7090F13304AULL, 0x209A3D0FA2598E8CULL, 0x123FEE187BCFB17CULL, 0xE69FC1AC3E4C330DULL, 
            0x397A9CAE8108A3FFULL, 0x177CCAA4B5A72459ULL, 0xCCFE79FA586436C8ULL, 0x342B01FBB4C964FDULL, 
            0xB93BC4BEA29FDCA6ULL, 0x3CC0E7AB16556CBBULL, 0x3E4659AB18D61057ULL, 0xEFB4AA0EFD39FC80ULL, 
            0x4D438F2FA99F0789ULL, 0x07817C479D241C8CULL, 0xB5D943B0E13799DEULL, 0xF6CA785A44E5DFAFULL, 
            0x8E78290E74B08BAFULL, 0x92E4012E64B95B4AULL, 0xB3BAC1E6DDAE3DB8ULL, 0xFC4A0EE0713368DFULL
        },
        {
            0x1AD05722B4E02E55ULL, 0x1BF33B1D01BA094EULL, 0x57FDF721E2FDE96AULL, 0x5168DA3BAA845A89ULL, 
            0x6F7C53CBC444E9E8ULL, 0x058B9BE9AB041D27ULL, 0xF0B7905FD6D5A829ULL, 0xEAB5571AFAB2F214ULL, 
            0x41E919224F30B604ULL, 0xCBA76D470C77BAB8ULL, 0xF613EF3AA9CE49C4ULL, 0xBB40A85F856FF21EULL, 
            0x492798E6B4119E85ULL, 0x8803CB2A575FB7A1ULL, 0xC162E24F499EC570ULL, 0x69507F8C4C4747EEULL, 
            0x3B72E9191168205CULL, 0x3CE8D68EBB0B7613ULL, 0x7A60BD30089B58F1ULL, 0xE2AD17900554286CULL, 
            0x0145346769401370ULL, 0x63F6258AFD38DCAFULL, 0x7483FAE0E152C164ULL, 0x36C203D5009598EFULL, 
            0x014E41459D3D8CC2ULL, 0x24263ACE08E93BCEULL, 0xA21437F86556B7D6ULL, 0x79F8907452017A42ULL, 
            0xB5B0CA016A804838ULL, 0xB8E22A1314A4D78FULL, 0x2C56D33052BF0A28ULL, 0xC4712CA3EEAFBD03ULL
        },
        {
            0x148A6B887E17FDACULL, 0x9C37D85198CD2445ULL, 0xE485BAB378CEBC01ULL, 0x9AE1580AF740D1E5ULL, 
            0x25FB3FE160CBAFA1ULL, 0x970AC1A6C224EEBEULL, 0x0A6D53300907A787ULL, 0xAA8B0505B2C70113ULL, 
            0x3B73E9CA93D49BC6ULL, 0x4CE5148DDBF89122ULL, 0xB430AD6F836CB85FULL, 0xB697FA6AA1943CB1ULL, 
            0x436C4CF4C3BAF74BULL, 0xF4BC3EC40CF6BFF8ULL, 0x8B13D43080F86BA5ULL, 0xCBC840DD46899AD5ULL, 
            0x1EBDF4D538BA069EULL, 0xC97510CE7AC352A4ULL, 0x622B9342A4402E61ULL, 0x3366B3067D834F6DULL, 
            0xE6B15D251804E715ULL, 0x277A07CB66AC91AFULL, 0x41E581C72C278494ULL, 0x18D6B4A24C7EAB56ULL, 
            0x7750FEF6514CBD7CULL, 0x8D41D61DFC3F2290ULL, 0xAE7A644A36782B05ULL, 0x5DF9EE9A2322FF45ULL, 
            0x329E7EF811F0921EULL, 0xF72F91A6719262D0ULL, 0x4261C02875AD86F4ULL, 0x61F49438F5A434F2ULL
        },
        {
            0x58B8BBE551BA8486ULL, 0xB4B95CC5A95C3DD0ULL, 0x3A6FC602A8D8AAE2ULL, 0x7C55B8050C58FCCDULL, 
            0xB84F3C80EFEB86A6ULL, 0x151D5671D748EAFAULL, 0xACDCB1E06CE39F82ULL, 0xC54EEE79E474FFA3ULL, 
            0x438324CE1597514FULL, 0x50E880EBD2CB4BF8ULL, 0x6D827DDCF9701C0CULL, 0x3440A3DE775A548BULL, 
            0x0908589F10857E29ULL, 0xD7D2AED614527639ULL, 0xB0B5A10EE8D6D574ULL, 0x315083AC6F324545ULL, 
            0xD7624BDAF56814DCULL, 0x194AD728CCA35CB9ULL, 0x66D363E2A505E099ULL, 0xFBA33BAC153BB978ULL, 
            0xC85990AA1195B68AULL, 0xB6AF5E53C8D80950ULL, 0xD459B4D64BAA9EF2ULL, 0xB628E1A573231055ULL, 
            0x65BF0B073538EF09ULL, 0x54AD8EFEF6614F85ULL, 0xE09B7E9337DDC57CULL, 0x9DF8E4017BDB6AA6ULL, 
            0xA35DCC8474C7CF3AULL, 0x14A9D1FC239692CDULL, 0x5ABECF1E57E911D9ULL, 0x30D2C78D3E65AA0DULL
        },
        {
            0x3E88D61BB4F287E4ULL, 0x9DCE2BE66765BE6CULL, 0xC284DB7EA24A254BULL, 0xF558AF32A2D4AA44ULL, 
            0xA2C8B68F57D76C73ULL, 0x4220B68414CB0C27ULL, 0xFB9F99D9A3B8DCC0ULL, 0x7A0FBA1DFBF63B36ULL, 
            0xA9E5F27539444099ULL, 0xC514E6CC7EC1A7A7ULL, 0x214F2BDD8EFBE46CULL, 0xB4709AECDFC460AEULL, 
            0xC493E12E98139811ULL, 0x3D2A3A3A0004ED61ULL, 0x5AAAD2D1DEDDD00FULL, 0xB2EFB94D34306C9BULL, 
            0x3BB7A7FFB56B04F9ULL, 0x295351228B9D29CEULL, 0xA584E5F0F675F365ULL, 0x157EB3417DD7E55FULL, 
            0xC8A3DD3531AEFCE3ULL, 0xB4296DB08EED3672ULL, 0x529640F5FF41588DULL, 0x83E5E7EF5EBE0B32ULL, 
            0x3DC762457756050BULL, 0x0659C82E12E8EC64ULL, 0xA330C97E69AAF6C7ULL, 0x0FBB68E6C7E33066ULL, 
            0x269305FF97E5A18DULL, 0x93A471C94B6CA53AULL, 0xC23D6EF80F998B2FULL, 0x976FD58C35C6B544ULL
        }
    },
    {
        {
            0x19749ABAC4836F82ULL, 0x23D8F5A0BF9E5033ULL, 0x0EE430FFF4E95DBFULL, 0x10E04ACAFFCBB3F0ULL, 
            0xBDDB91AA1086EAEFULL, 0x73C55992C1935AA3ULL, 0x4F978A5ED37AB6E6ULL, 0x788C5888093A0113ULL, 
            0xCD62D8D98953776CULL, 0xE1F483A9312402CDULL, 0x8EBD2091D99D5300ULL, 0xF42C9F9CFA8AB19BULL, 
            0xFE7430E6E6F3EB47ULL, 0x4EA0D52665529BB2ULL, 0x09F1C59DC66599DDULL, 0xA2011F5EA416A6E8ULL, 
            0xBBA90E68574785C2ULL, 0x7DFCBB5CCD49EA3AULL, 0x77BDD37A9E3B3A9FULL, 0x9136576B615D8F6DULL, 
            0x96250B3D689B34FCULL, 0xEC3B3037AC643BB0ULL, 0xC71D230691CA7DEBULL, 0x9D8D7C0C9A807396ULL, 
            0x7205231BAAE96D05ULL, 0x7EC270FF36739EF1ULL, 0x6A67E10B94312B3DULL, 0xA4C57DB14E24F969ULL, 
            0x489880616D051F02ULL, 0x5EDD53953F25DF8BULL, 0x25DA289AE1C18FF2ULL, 0x24F39F6366AEF956ULL
        },
        {
            0x3CAC1F705A71B2F7ULL, 0xAA65DCD47C82B853ULL, 0xFE549E4F3BCA59C7ULL, 0xDCDBC427136AE223ULL, 
            0x78EC3936449B2E9AULL, 0x5B52851224842973ULL, 0xCA2E53864A853652ULL, 0x0C830612D3E37902ULL, 
            0x852624E9D1F79247ULL, 0x5C20EA23A55CF047ULL, 0xABFE0FF7FBB14B14ULL, 0x79DABED86E4CF166ULL, 
            0x4FE42C083EA75E36ULL, 0xCE2A5471523ECA2DULL, 0x929661DB512832C3ULL, 0x55E0E3E299CE3FB7ULL, 
            0xD9DE841E441B2AB9ULL, 0x35198929CFED0175ULL, 0x57C4FA7A1E5FF55AULL, 0xFCBF146F48247460ULL, 
            0x8A985018598774EEULL, 0x85F491836FE85071ULL, 0x15DACBCE7B0FE620ULL, 0x362B50CD907B9719ULL, 
            0x633A90D380092269ULL, 0xA60BB7A12E0460ACULL, 0x8A9AB1542AB94C99ULL, 0xFA91DB9EFE567CE1ULL, 
            0xD616991371AF5C0FULL, 0xCEC7253151E2282AULL, 0xC0462325E1DB0CD4ULL, 0x06D405B658719D0BULL
        },
        {
            0x0DB1A4A12905AC71ULL, 0x55539B086A71784EULL, 0xA9934ABF3C72FDB6ULL, 0x15C56EBF203255ACULL, 
            0x7A794FBE1F27B91AULL, 0xE339D699CAB2F808ULL, 0x42028290576ACD11ULL, 0x6E618057D2223B63ULL, 
            0x80FEDF88874AB898ULL, 0x08C401F7B7E9B77BULL, 0xAFBAB2080EE4445AULL, 0xDC8BFD214FF49284ULL, 
            0x4031DF0770997181ULL, 0x8651E40FB1083D1AULL, 0xE388FDE2905E043EULL, 0x6D60CD82070E643DULL, 
            0x159CFFB359826B7DULL, 0x5E5A459A1675206BULL, 0x8BDFF5D6F0A591D2ULL, 0x94443D224A28F531ULL, 
            0x1546549FA3E3DC8EULL, 0x97308DF5633FE9ADULL, 0x51EDD58597FAC07EULL, 0x1DEC4FBD4319F488ULL, 
            0x215530DB5FBB4678ULL, 0xA70FF54DCA4A237FULL, 0x8FE14476CA09A4B9ULL, 0x78F056FA36F799A3ULL, 
            0xD095DE94EF5D5FA2ULL, 0x955168F74A34DBCCULL, 0x35BDAB028646E065ULL, 0xB221CD2A5F03AA86ULL
        },
        {
            0x9CD28C00737C43DCULL, 0x13E2DE0A7E1B2F49ULL, 0x4236121950484DC9ULL, 0x9751A29BFC710BFCULL, 
            0x26563653ED2776E1ULL, 0xE9EB27EEFA0F3299ULL, 0xEE4B327F90D6FBE0ULL, 0xE0423282BB61BE0BULL, 
            0x3FB05CA883F88D17ULL, 0x77AF92B8E28BC70CULL, 0x0B4BBB576DA1CC99ULL, 0x4122074CBA8194ACULL, 
            0xAA70355999FC0A70ULL, 0x4997C0CD0704D2ADULL, 0xBD9CD3EC1A21F7CDULL, 0x54A187517F11B5C1ULL, 
            0x81644E9C44429A89ULL, 0x4DA86FB1957EC80CULL, 0x0FE9707A02F7F49BULL, 0x8090EEB3AC252F0BULL, 
            0x49C1CA53A98D308CULL, 0x3F2D986F51B1180FULL, 0x26BDFE2B3CACE1DEULL, 0xB5C7E119C9AA5EE0ULL, 
            0x03594DABA9400824ULL, 0x745AC28441EDC897ULL, 0xF6885717167F76C6ULL, 0x8ECE2CCD5F336DD0ULL, 
            0xB7C3F216C5F9AE43ULL, 0x1E32F4707E80B869ULL, 0xE2D9E324A9D21DFDULL, 0x89EDC9E1BE8719F7ULL
        },
        {
            0x3F69E607559080A6ULL, 0xE5F2AB83E873DAF8ULL, 0x6030D87A9237CE25ULL, 0x6685A2833DE7EED8ULL, 
            0xD5263BE74E81E777ULL, 0xDB382549A96636B8ULL, 0x30667F517F41B11EULL, 0x2464071831075BB7ULL, 
            0xC6472C4ECCCFB8D5ULL, 0xF806418EBCAD3016ULL, 0x5EF2034810C2108EULL, 0xDEEB2B29E94D494EULL, 
            0x404FA2E11345847DULL, 0x05D1932012FD4A28ULL, 0xA188EA94444E7B9CULL, 0x3BD676896A19B84CULL, 
            0xD3D1D4309D58F21DULL, 0xF229770C4D64E3FEULL, 0xD6D6C9B2A871811DULL, 0x9E8B67A9B7C90EEDULL, 
            0xF6AE3AE15023C7F9ULL, 0x1F4EC48935A5E25CULL, 0x02EAE9E24E299D7DULL, 0x0C01ABCADBB360F4ULL, 
            0xB25577088806D108ULL, 0xD3B209E27BFF4926ULL, 0x2B3BCE8E3BC886BBULL, 0xC2D0FDD786B49B48ULL, 
            0x8CDC25A396D22D5BULL, 0x970ED1F0088BCD59ULL, 0xA30F2B54395A6525ULL, 0xEB7121F1E9466EF9ULL
        },
        {
            0xBC98BB9E3704469FULL, 0x226EB6F30A099371ULL, 0xDEF418206C69C6BBULL, 0x6374E5EF462C066FULL, 
            0x843D6C1FA366DBC7ULL, 0x7F8FF0A981C44654ULL, 0x1B910EB5E9FF5F32ULL, 0xBA5BA8EF65E35ED4ULL, 
            0x7EC1E45359DC8746ULL, 0x923444F0972DA0A6ULL, 0xC542BE3710B0181DULL, 0x7C0B07168630FDC2ULL, 
            0x78818B3B8E3D28C9ULL, 0x12C36AD1C2FCBC9EULL, 0x629B67B0EDD85E80ULL, 0x4719C8AA971966ECULL, 
            0xDD57289CFAF0DB1CULL, 0xA9320B39B391F68BULL, 0x7A734E814FA4C5C3ULL, 0x43B39C7991CE4E1FULL, 
            0xB3B6F821B3102C51ULL, 0x31002204CCC7D1C9ULL, 0x5C82CCBBE55D5DE1ULL, 0xDF7C063C30C21A45ULL, 
            0xC66ECB83D89A77FFULL, 0x6FC7B02C85CAD33DULL, 0xD3E8DD97837F65ECULL, 0x5063FFBE6C936B76ULL, 
            0x25829A87B6E2BA8EULL, 0x118947103DA2798BULL, 0xA50AA73410F4851FULL, 0xA7E53E198F0CBBF2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseAConstants = {
    0x0AAC1D7BE7D39EF7ULL,
    0x184385254D34E672ULL,
    0x2A980706604166F8ULL,
    0x0AAC1D7BE7D39EF7ULL,
    0x184385254D34E672ULL,
    0x2A980706604166F8ULL,
    0x70B668DAFECEC2CFULL,
    0xD7FD39C18D7A17E5ULL,
    0x7D,
    0x93,
    0x26,
    0xA0,
    0xD2,
    0x20,
    0x95,
    0x9B
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseBSalts = {
    {
        {
            0x512F0AC067E928ECULL, 0x56D6F5EA91D5D492ULL, 0x7BDA88426DCE2239ULL, 0x028D9F685D74DC2AULL, 
            0xD551D6766F776676ULL, 0x11794EA8257EF854ULL, 0x353DFE14C99882DDULL, 0x84D50F7193EE3195ULL, 
            0xD3184DA3578CBD38ULL, 0x88B9198951AC2C1DULL, 0xBEF0A9C7E06ABAB2ULL, 0x8F20B30784BE8090ULL, 
            0x6C4915A2F9AF9666ULL, 0x6687AE72804199A1ULL, 0xE5BF9EE03DE04328ULL, 0xDEBF8730DB546A79ULL, 
            0x2DE793772C9D0D7AULL, 0xE54E369EF7B1FC27ULL, 0xA46539B1728190EEULL, 0x51665E3AD58781FDULL, 
            0x34AD146A04057034ULL, 0x85BD2442CEAAD4FEULL, 0x3822CD208C268C8CULL, 0xCC02F70E7C5DFF56ULL, 
            0x9F28359FA96E5033ULL, 0xA804025DD6B8D5A7ULL, 0xD31232D5CFFE00C4ULL, 0x98CEA41E905ED245ULL, 
            0xF54A0F8637ADAC62ULL, 0xB30F89E4A541EAE3ULL, 0x6D925E4B93141D92ULL, 0x23F9F06FE81CE03CULL
        },
        {
            0x8FB0AF08B4632666ULL, 0xACA9A914C7F55EBAULL, 0xB4032B8403BFD8EAULL, 0xE1DE23405DF099FBULL, 
            0x7DCB1647519A8955ULL, 0xE1B56750BA64D3D1ULL, 0x4C692062F617E1EFULL, 0xF439AEEE329E4EFCULL, 
            0x9A29B0F474BBEF55ULL, 0x6B7709EA515A91A7ULL, 0xDFDDCF9D417A0EC9ULL, 0xCF3D0D8D539B1849ULL, 
            0xAD7C26DF2BE0EB21ULL, 0xAACAAF20F94D6A06ULL, 0xC2AA94C939F51B88ULL, 0x55988C06F3EE7550ULL, 
            0x24BD20FE8521791AULL, 0xE24EA346DCF31D6EULL, 0x8678EFF243E3BAB3ULL, 0xE68CD31803DCB922ULL, 
            0x53ED0881C756E4FDULL, 0x5EE4282FC7CFB2DFULL, 0xD2CF8D2852CFEACDULL, 0x5ECFA33211566408ULL, 
            0xB80870EF3B36E381ULL, 0x3904A45C3202234DULL, 0xEDDB270DD272417BULL, 0x6DA2BB948C8D698BULL, 
            0x9A13564C8A46D2BEULL, 0x32D099083DC0BBDDULL, 0x9D18344392B5A981ULL, 0x789B17BDF4478EBBULL
        },
        {
            0x0BF0FC32CF7AF4F6ULL, 0xEB863A9709756B6DULL, 0xA7C2BED9DE53E859ULL, 0xA24185156B0C4E9EULL, 
            0x6DDEEB75995158C8ULL, 0x90A5DE90ECFD0822ULL, 0xD3DCD88C483BEF0AULL, 0x85018B0071E7F265ULL, 
            0x2B7B1DDD6EAB08F0ULL, 0xEC338EBC5EAD4423ULL, 0x0AAD3E281E023F23ULL, 0xE31F8D19537357FBULL, 
            0xFC299897D05BB924ULL, 0x6876952147756AF3ULL, 0x8229E872F1DC50AFULL, 0x4837B6FA9B687229ULL, 
            0x863F96DF05096BDBULL, 0x0528D298EFB7D54BULL, 0xEAB5DEA39EDA64E5ULL, 0xD475B7D86F40CBFCULL, 
            0x36D39317BDEE9C21ULL, 0xA772D460CB4C748EULL, 0x6273AD056DB50357ULL, 0xE4ACCFA62CB004B8ULL, 
            0xCF1206B23A26171CULL, 0x8E607B929AB18020ULL, 0x88E8E0A6FFA507DFULL, 0xA5AE049D25282F7FULL, 
            0x0B2EB3D32E826977ULL, 0x3C11F1372C7AD768ULL, 0x0F3F9974A5D4F501ULL, 0x2069CFE89FF1D7E7ULL
        },
        {
            0x5067ABF208168BD8ULL, 0xE7F696621EDD8DD8ULL, 0xEE90FE8B26EE0DDDULL, 0x9619F0DEF54D2FB9ULL, 
            0x996368CAD1213190ULL, 0xA5A77D5336163F81ULL, 0x4216284E7982AD7DULL, 0x1A706DAB3D19C112ULL, 
            0xAF6EB33F5E3018EEULL, 0x41F1EE88E505E605ULL, 0x25C62752B1734254ULL, 0x1CC479010A05D1F7ULL, 
            0x821E80DD83AA72E4ULL, 0x29250485291ACA2DULL, 0x3B3ED744699110BBULL, 0xC0F870AA058E5924ULL, 
            0x68EB2084FAE2F5A7ULL, 0xF53A243FB7E6FB1CULL, 0xCD9C4E889383DC2EULL, 0xDE7542E2B2C962D3ULL, 
            0x9ACFDF55FB0D8CDAULL, 0xF76A3644C3A007D8ULL, 0x6BE3C994B95918F6ULL, 0x88BC9487947C1EA7ULL, 
            0xDA2C7C85F3BA472CULL, 0xEF8770DC314BA64AULL, 0xB84DACD42B470EDBULL, 0x35E3B0645F3E2C70ULL, 
            0x1D873E8D57F53841ULL, 0xA6C57592B69B7D98ULL, 0x0F316C31DB048086ULL, 0x28F2DC7544207F2DULL
        },
        {
            0xE1980297198649B4ULL, 0xC2790996D3A83434ULL, 0x6EC88D43D329247AULL, 0x82E529E4D988AC54ULL, 
            0x0C14E213164B719BULL, 0x8D3EB87219103623ULL, 0x9C5FD722154D1D7CULL, 0x01478C30D2E95480ULL, 
            0x591E010230D2393BULL, 0x48ED142D38A2D0C1ULL, 0xBEFA40A1159EA0FDULL, 0xD4B9B517C1B9EC24ULL, 
            0x537DC4A5046FD311ULL, 0xB996363B66B1E487ULL, 0xAE59C8C4FA1FFF6AULL, 0x236F5A9DCE309F2CULL, 
            0xF5150EF9E00EEB09ULL, 0x13C64703355DCAD8ULL, 0x3304B48730F3212EULL, 0xE3A95352B42CD630ULL, 
            0x336639E4D2802394ULL, 0xA53AC26311A64CE9ULL, 0x31F6F1FD132C68DAULL, 0x0323B22AB83DAB35ULL, 
            0xC6725709B30482AFULL, 0x5D65437C4BE442DBULL, 0xB0032470D6AE6FF0ULL, 0x00975C90693193C5ULL, 
            0xD8B7A0DA7E024FD2ULL, 0x3F26F575993F6DD9ULL, 0x84639666B5FDDEEEULL, 0x4F539B94187F706AULL
        },
        {
            0x89A59F323A0EF302ULL, 0x9D9E0C6942F74AE1ULL, 0x3EAECEDF7DF7AE73ULL, 0x0B981E653EBC1E27ULL, 
            0x5E1AD1D8C0DA62FAULL, 0x402949AB9E9F8723ULL, 0x64C4BEB60CFF407CULL, 0xE786B9F14AFBE050ULL, 
            0x361CE4AB3B5772D1ULL, 0x9CF0B0CEFCEE6AE3ULL, 0xE34692BAC708E907ULL, 0xFB1A0C67B3259304ULL, 
            0x42E387CB8294AE62ULL, 0xD4502975F58DB5B7ULL, 0x20DB3790EDE87281ULL, 0xF911650D40C6A245ULL, 
            0xC9944E6E509C6D0EULL, 0x096EBD3E6F0BED0BULL, 0x80A55ECC0B4F2604ULL, 0x73AE9C8960B8F57BULL, 
            0x16F028A6A49DA024ULL, 0xF62F62B891863E92ULL, 0x6D484550BF68D5F2ULL, 0xFEEECCF319C3ACE0ULL, 
            0x75AEF8D1DDC8050CULL, 0xA79AEB88BDB8E168ULL, 0x83C28C1A9DFEFE90ULL, 0x4CC01CBF964BB94BULL, 
            0x9D2E4B709CF42383ULL, 0xC58F6BB4105C220DULL, 0x2515028E49903E56ULL, 0x7BC567F6F0E00EF3ULL
        }
    },
    {
        {
            0xC7284D2E6F3C9F0EULL, 0xFD4C883F398490C6ULL, 0x530C824E8AF8CDAFULL, 0x67D0CD1C637CE760ULL, 
            0x06947647935490E5ULL, 0x0DA317DBA7C93F92ULL, 0x4417BE459DE6B3F0ULL, 0x4CDBF894A0336A86ULL, 
            0x426E86D430E74258ULL, 0x0F271C3A6EB3B076ULL, 0x6BE8C4560BA4F760ULL, 0xFEC37DD6477C3CECULL, 
            0xA5C359F913DA724BULL, 0x845CD36638181EE0ULL, 0x5AD3BCC062840C0FULL, 0x734523EF2DEEEA35ULL, 
            0x678CB5BF374FC154ULL, 0xBFEA525B8A30F380ULL, 0xB731903C0445A70CULL, 0xD942D6CF40928218ULL, 
            0x514A72433A14FF34ULL, 0xDD7587F8E3DC3F82ULL, 0xC5518AE8D63582FFULL, 0xDD6D07D25D6EC80EULL, 
            0x85C4BAD3BA9DD454ULL, 0xF81C073101DD235AULL, 0x6670E4805DE77243ULL, 0x4F49A85F1A803871ULL, 
            0x71DF74F20D96827BULL, 0x2387D2D3973B7F2EULL, 0xEADE5DEA44B311F1ULL, 0x79916F931C793FE6ULL
        },
        {
            0x5F87F7292CC7E30FULL, 0x173B21EF43B2BD22ULL, 0xB74CBA37C177148BULL, 0x49E6B8407B809B2FULL, 
            0xC86EEC49E4A7910DULL, 0x6C27F69129E98817ULL, 0xC458523EE1CB6481ULL, 0xA1F2757FC9FD1405ULL, 
            0xB51C18F2016F7628ULL, 0x2A9AD3186DCC0392ULL, 0x842382DBDD2C4C97ULL, 0x6CC71A666A347327ULL, 
            0xD6E36A279C20E8AAULL, 0xAC3FD49870C60AEAULL, 0x4741A056C77C9103ULL, 0x08F76E67E50CAD15ULL, 
            0x5D5E7A2339A71CB3ULL, 0x61C8F8491572D867ULL, 0x62E3F735F90B5202ULL, 0x46561B8E87F05E96ULL, 
            0x5A6F63BBF7B094F9ULL, 0x21DC11048E172E39ULL, 0x295C6A67EFDBE59DULL, 0x70C954454F31C91DULL, 
            0xC64AAE81CA356171ULL, 0x287702232DB0F70DULL, 0x23DF2D98087D57D2ULL, 0x53F9E260FE4F7CBAULL, 
            0x1D3D7DAC66E96344ULL, 0x76441B960EE478E9ULL, 0xBEC95C0AB9B2D74DULL, 0xD55EE15A28E6F9E4ULL
        },
        {
            0x9BBB178F3D58CF6AULL, 0x300E1C8A49CD9BE1ULL, 0x6399F30A4B058DC7ULL, 0x8C44AC99DE490C32ULL, 
            0xFBDB3FD812EA2673ULL, 0xEDC6CF0BBF390FDBULL, 0xFA1098606917360FULL, 0xB2FD02A5B033568BULL, 
            0x10B2398BD91F0965ULL, 0x167D018C8588172FULL, 0xB8CFD92264FFF0DCULL, 0xB2512AEB725B7597ULL, 
            0x3D88BFFA91AF53CFULL, 0x892027C81D0C073AULL, 0xA5E2415896539E09ULL, 0x7149E1B53BBA4F3DULL, 
            0xC4D503CF6EF62F10ULL, 0x0D44F131C242D151ULL, 0x1979332F3B20044DULL, 0xFABE996F6EF54FCEULL, 
            0xD5762632FF01F625ULL, 0xE748D48E0FC31255ULL, 0x44C823EE089A06AAULL, 0xAE8730842D84A533ULL, 
            0x8C13514F11BE9164ULL, 0xB6E496931665FE25ULL, 0x8E53A2B61362F564ULL, 0x51107A3E18FF5A88ULL, 
            0x30AF00985E22D366ULL, 0xB6B79C4733608A78ULL, 0xE83E1B7DED795AA8ULL, 0xEC1F036A83919DA3ULL
        },
        {
            0xB62B4CD37B42374AULL, 0xE4B12E6E804992FDULL, 0xFE9D2CD9EB5068E9ULL, 0x087F29C479246966ULL, 
            0x4265380664080233ULL, 0x2D40FCD61C27C47FULL, 0xD8FBD800BECEB2CFULL, 0xF0928FDF4E63FF4BULL, 
            0xB7DCD7FF8339D610ULL, 0x47A81EFB2EC616BBULL, 0xDB1E4749F3F4EE1DULL, 0x4A547FEFE8A89B8BULL, 
            0x8DA33B26CD87C982ULL, 0x5BF95E352E978A4DULL, 0x11D4094C6E679E78ULL, 0x84ED2CCCC7AF3482ULL, 
            0x79135CC454A93FBEULL, 0xC6E10D981995A8BDULL, 0xC451D196409C328BULL, 0xEBC1073D1C063592ULL, 
            0x8C27B8B9FC3BE64EULL, 0xD62CCDC9D4851BB2ULL, 0xD675B0F703C1D295ULL, 0x89506847200412A5ULL, 
            0x687E8112A0BC319FULL, 0xAF289020C8BCE583ULL, 0x1D6930984741FDECULL, 0xF74D62501A59BF53ULL, 
            0xB93F17562A92FC9CULL, 0xF2FDACD620CA3FA2ULL, 0xF9A31E747FAC75ACULL, 0x1FD2E2BE01FAEA6DULL
        },
        {
            0x95F55C21E8159335ULL, 0x55200224B06C1A16ULL, 0xEA178467B6B31AC8ULL, 0x6E66D4D2FC80D9D0ULL, 
            0x0FFE50CEA419EAC0ULL, 0xD965E9E31F3AE473ULL, 0x6A355AF7EEE3400FULL, 0x7808331516A13993ULL, 
            0x6D99BB55339A068FULL, 0x67FF0EEFAF742F9CULL, 0xFABF35B87CA8C64EULL, 0xA15A2D875A4E01DDULL, 
            0xC212198307439227ULL, 0x5D32CB607B248DFDULL, 0x6B63A359DABBF0A5ULL, 0x5185CCAE2A00F6ECULL, 
            0x31D5A4A8E5B1CB52ULL, 0x1C1CE580200DC175ULL, 0x6C91007B109B48B7ULL, 0x85B0A6260A2012DBULL, 
            0x1C59B213A4B0A132ULL, 0x5226CF5E65E44610ULL, 0xFEFA9802EA3EE444ULL, 0xE76A7E3E77BB9EF6ULL, 
            0x05575AB6DE7EB211ULL, 0xBB504178AD83E0BBULL, 0x57D415ADBFC9A2F7ULL, 0x54F73DB590847E9CULL, 
            0x0256BDAEC0F73F7AULL, 0x64F0673B858B8451ULL, 0x3B03CDFC59B259D4ULL, 0xCCCAC50E0BB29F17ULL
        },
        {
            0xDF91101FAB9427DFULL, 0x94DDD2A43B745B11ULL, 0xB7B05A8584E2D458ULL, 0x3C906AFF049C6FE7ULL, 
            0xED8AA9A8A6C7271DULL, 0x4B6FA4DE804F8B1CULL, 0xA83CA9C91705D8B9ULL, 0xC6F67A151E27D46DULL, 
            0xB27BD6C0492289EAULL, 0x3DEAD804096C5611ULL, 0xDD810C8BBBD06ECDULL, 0x6668795683A2B3E5ULL, 
            0x27E3901C44A11BBCULL, 0x9B4F1287BC05F56FULL, 0x5767F2EEA4DA280DULL, 0xAA422F22764DFEDBULL, 
            0xBC4ED7B9AFFE5824ULL, 0xB97CF513B24E2985ULL, 0xFAF019BB18CCDBBDULL, 0xDF05019BB951561EULL, 
            0x244B58A05BB62050ULL, 0xFFDE7C01ED8A8BBBULL, 0x410DB0C30B2A9C7AULL, 0xBD3F1C98C72AE225ULL, 
            0xAD8D9A20BF9F4DA3ULL, 0x48F7501E9B2B0F97ULL, 0x6DB5F0D32E9E3074ULL, 0x30E470FF0163CDD3ULL, 
            0x41FF1CDB13A3259BULL, 0xA646ABD9F928BC8EULL, 0xAB299CD9543198A0ULL, 0x52AAC76C787F0886ULL
        }
    },
    {
        {
            0x8C73C780793AA897ULL, 0x559692BCFF686E42ULL, 0x911EA88C728DBCE9ULL, 0xEBD58CF707D28B07ULL, 
            0x4ACE716DDFD5EED3ULL, 0x71E0DEDC37B56CA1ULL, 0xEA7A7884D9578D70ULL, 0xE706660DC167375AULL, 
            0xC02586B63FACD118ULL, 0xA38F8B097CD79E58ULL, 0x10D68C0E89F5190BULL, 0x59750B4BFDC98007ULL, 
            0x8CBDF744259B3BD9ULL, 0x50E05653E6B44A81ULL, 0x856AB0BED344C909ULL, 0x6C9DF2D18DAF3B22ULL, 
            0xAF23166A742DE5C8ULL, 0x1F9D01E542A36A7AULL, 0xB021F18FF8ABC3B0ULL, 0xB55935A37E9E46C5ULL, 
            0xEE11CDC1FE9E3BD0ULL, 0xE11E2E75A54F02BFULL, 0xB685A1A77762BF56ULL, 0x314CF6F1A5F2CEDEULL, 
            0xDA5CC6474FB2ADFFULL, 0x373AF8BCF3DFF73AULL, 0x23DB7396AE14405AULL, 0xD7AA6F6B31B85BC8ULL, 
            0x36FF001CA1E4F358ULL, 0x8EF2F0EDC1A03C0CULL, 0xDEF83C5CD03244DBULL, 0xB7662FE922ED3D6BULL
        },
        {
            0x7F1CA30723EB0349ULL, 0xF19959556797466DULL, 0x2993D8E795322C1CULL, 0x4BB3D11889A1ECB7ULL, 
            0xE97E5DA764D4C4E0ULL, 0xDEF58B1DF88BF315ULL, 0xFBE6C68FA800353BULL, 0x5981B67D04D36EDEULL, 
            0x30F90193430024FAULL, 0x187571A9F3E69BE8ULL, 0xDB09116F363D4385ULL, 0x0AEAA09066B5D3CCULL, 
            0x80CE034A4A45A70AULL, 0x217520D7F08A6E01ULL, 0x0B2AAB49A257EEBBULL, 0x1BDFFC3FBE4E6A40ULL, 
            0x06563DC97036D248ULL, 0x2A255F3FF035CC1DULL, 0xFB2086922AE08A09ULL, 0xD5165FACB966275BULL, 
            0x27553ECF48310FE6ULL, 0xB3CD44A1CBD20B50ULL, 0x778A9535AE860392ULL, 0x1C5005B797B9FCDBULL, 
            0x07BF6C639FC773E6ULL, 0xB78DBBBFD01701D6ULL, 0x4B7526EC8E5C2629ULL, 0x6101D9117866BD9DULL, 
            0x15CCADBC84C6380FULL, 0x39FE600F95DEE350ULL, 0xB91C29FDC5DA0FFDULL, 0x98DD7FE9277BF45EULL
        },
        {
            0x155F251BFA15502DULL, 0x4C0EE9591C4D17C2ULL, 0x8A27DA20265CC6EBULL, 0x1DBE9DED18959498ULL, 
            0x6545E83E6C143D31ULL, 0x025F409A99282680ULL, 0x497FF5DFE3D70D73ULL, 0xED207A0371CFD35DULL, 
            0x9839EAC4C9BF91B3ULL, 0x43C134EE63FECF0BULL, 0xAC912F63D21CC118ULL, 0xBE25539F9B5EF0A8ULL, 
            0xC21B90592735532EULL, 0x4736146E6F0C6E06ULL, 0x9E059FA8E3090150ULL, 0xC85277B4D0CB04A1ULL, 
            0xBFBA07DFBB79180CULL, 0xB7A4E475EE37E013ULL, 0xE5C980F95A4C8A8AULL, 0x5EA47D184348DEE3ULL, 
            0xD891516250268B92ULL, 0xF75D2ED2A7136033ULL, 0x53D544DA76DEC251ULL, 0x890A51F6F735CD2BULL, 
            0xE213D4562A24EB57ULL, 0x054D5908E9E31FF7ULL, 0xA9CB002B2CA15AA0ULL, 0x1C45363313919ED7ULL, 
            0x3CD48B26E4277449ULL, 0xAADD4FFB8867182BULL, 0x53668FC98B48E189ULL, 0x5F1D459F7A6F820AULL
        },
        {
            0x56A10FFAFC3089B5ULL, 0x24F91D73EC998388ULL, 0x70CE91C45B616456ULL, 0xC8A8F230CB1B7C5BULL, 
            0xAE0E63D76CFE9548ULL, 0x583D01C6E34ED7A6ULL, 0xB6C74D5977E053D4ULL, 0x1FEAC72F3B40AC64ULL, 
            0x5AD29ADC09B2364AULL, 0xECABD25E17893E67ULL, 0x7B5413B66FC3862DULL, 0x5FCCBF237E65CE8DULL, 
            0x85739F08AAB04190ULL, 0xD6AC3683AF4F2CA8ULL, 0x13D361E6A6BF062EULL, 0xFCD16613A2CDCA29ULL, 
            0x47D2F44F1D2597BAULL, 0x081E740217D7DDAFULL, 0x9F5CE5E8223B821AULL, 0x5642984A0AE9F53AULL, 
            0xB3537ECB731958B7ULL, 0x5B41D56F07006B02ULL, 0x26D6FD69828FAD52ULL, 0xC2FA7B82B982E660ULL, 
            0x782BF46942AACB44ULL, 0xBC84598541D173BCULL, 0xD0576D12FED79D56ULL, 0x2D985E879F55F427ULL, 
            0x7F02DC4C37B92D21ULL, 0x44BA08E540CEC82BULL, 0xB71FED0BD5189FC5ULL, 0x3D0AA5EC41B9771BULL
        },
        {
            0xFFD642D9D0A8D776ULL, 0x0C03641017A0A796ULL, 0xCC8543C620A5B205ULL, 0xAB13CA7E1FCA62EAULL, 
            0x63A35D45240D6C59ULL, 0x399FD60CDA16E7A4ULL, 0x80EBE8474EB0FE7FULL, 0xC27D994E0144EA64ULL, 
            0x6D79661175185FE0ULL, 0x6F595436C9D7DB10ULL, 0xB8DF6483AD0331B6ULL, 0x23080630DCECA3F8ULL, 
            0xF31FA4BDA4D46A24ULL, 0x21BBCC05E1C9DD93ULL, 0x26558A9AE90BA708ULL, 0xADEC95A0610E34C4ULL, 
            0x7F5C8AA08D6A8DB8ULL, 0x4F7E579C1D156C5CULL, 0x9CA40F0E7D949908ULL, 0x7034C787AE5CE189ULL, 
            0x9CEC939945C7C519ULL, 0xFCF24A177096796DULL, 0x1F884CBF519AA26AULL, 0x623107C86E52A1EAULL, 
            0x4888595B13FD21C0ULL, 0xBB441DCBC0267E54ULL, 0xD91C7836A245F6CAULL, 0xDA6E084F9D48C238ULL, 
            0xB6EE4F605A0E2C15ULL, 0x6D242F6A7D8CF4BAULL, 0x81875ADB1872D30BULL, 0x771DB0C0292A9EADULL
        },
        {
            0x3E4A5D77FC95A76FULL, 0x44804D2F5126181CULL, 0xE0BD39057ACD8A5CULL, 0xA0B38392029A8238ULL, 
            0x77B48449AEFBC58DULL, 0x2FFC9C4841FA3064ULL, 0xABFBC62E02F25F19ULL, 0x0EA3E473B9F5D58BULL, 
            0xE9509EAED6DC245DULL, 0xC7FAA9CCC2450BA8ULL, 0x2479B43E6D495B95ULL, 0xD1E6D06E9186E513ULL, 
            0xCB491BA342DE24FEULL, 0x113D347F34B055F8ULL, 0xE03D0DE13C2875E6ULL, 0x031E749A0F1BB236ULL, 
            0x512B207E57195C09ULL, 0xC98DF9EDFD9C6F39ULL, 0x6EBC09BE29FA353EULL, 0xD6BD553117CFF0CFULL, 
            0xCC85D089C8467EB3ULL, 0x9643A0AE741F0058ULL, 0x06E8CADAACA4EC38ULL, 0x8123F1564ACD841CULL, 
            0x8331A761EB1E50E3ULL, 0xF159A6287C2773DDULL, 0x71EB942B484DD1F3ULL, 0xF4E3F62661F14FD8ULL, 
            0x0E43D5D547841367ULL, 0x20B5FFC89D03A2DDULL, 0x0BBD3EBEAC99921CULL, 0x363EC5DC83E2BDA1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseBConstants = {
    0xEDF12F09767C7B3AULL,
    0x8636F62A6E43E933ULL,
    0x55E0A747AC5F143FULL,
    0xEDF12F09767C7B3AULL,
    0x8636F62A6E43E933ULL,
    0x55E0A747AC5F143FULL,
    0xF90246EBC5A351FAULL,
    0xA18ECE9D4DB1ABFCULL,
    0x85,
    0x54,
    0x10,
    0xF4,
    0xF3,
    0x6F,
    0x1D,
    0x3B
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseCSalts = {
    {
        {
            0xAB7AE631BA6C1560ULL, 0xEBF332EC586879D5ULL, 0xA0CC34A4562EC5F4ULL, 0x339819870028C813ULL, 
            0x34B02464C6F1067EULL, 0xFC58C58C3099ED1FULL, 0x02F6AF0E124AC53AULL, 0x6CC70ABEDBD862A0ULL, 
            0xBC5B96CE6355D927ULL, 0xEB3088FBA8B74777ULL, 0xFA088161E6C3BA0BULL, 0xB0CF8E34D0898B7DULL, 
            0x437F6A0EAF974218ULL, 0x420D1DB5364A63E0ULL, 0x967A0268FC146046ULL, 0x1C067648FB365D1BULL, 
            0xB2FC48B580E35CB3ULL, 0x6A9A750A986EB270ULL, 0x142D69D23BEE06F4ULL, 0xA71FF51E8B3B0915ULL, 
            0x620ED0A245C01303ULL, 0x4C4394B7CE88BE19ULL, 0x19441B038D549B0FULL, 0xF38B91D7A4A09E6CULL, 
            0x4CC3CF2428FA9866ULL, 0x92059584EE917B90ULL, 0xCCAC61A23E765120ULL, 0x5EAB9D92DDAB6CC7ULL, 
            0x26C23C3CB3E8E7F7ULL, 0x8A353F05F1894817ULL, 0xC288C36FCF75647BULL, 0xBC268F49C51974D7ULL
        },
        {
            0xE167679AEF011346ULL, 0x30D5965235E4784FULL, 0xF97F1324AFE7FD6CULL, 0x2CC25DF4D47C6649ULL, 
            0xB65036A13509212DULL, 0xAE617E0CF4A90AFFULL, 0x4C48E664EADB16C1ULL, 0x3C34B16926576A35ULL, 
            0x7C522C55E99ECF65ULL, 0x4447A0E053CAF274ULL, 0x524ADE3017CFB27DULL, 0x8371264BF805AEC0ULL, 
            0x831C77945E8AFC80ULL, 0xE285AD59816D86BBULL, 0x6B605EFBD5CE3275ULL, 0xBC63E80F313B8D3EULL, 
            0xE67EFCA9427EE707ULL, 0xAE7159E6F930093BULL, 0x0065364E64F37D2FULL, 0xD2BAE12BE27F6504ULL, 
            0xDDC8DAE69F55ED7DULL, 0x40E0FF19C6DB7D24ULL, 0x2622DF5BCB220322ULL, 0xBBF8A61DB7362AD8ULL, 
            0xBD898B46EBD41E91ULL, 0xF3F4992146E72203ULL, 0xDA938DBE7A06C831ULL, 0xFFA16E2B87756F58ULL, 
            0x3F9681458021EE6AULL, 0x7604FF12DA7195CDULL, 0xEBD6434E37D0840FULL, 0xB4321E18DDFA531EULL
        },
        {
            0xF09FB3832C3B64B9ULL, 0x033D61ED8E786857ULL, 0x6F52330BAFAA89DFULL, 0xBA184FCA3D6845BFULL, 
            0xE01863995B01D79FULL, 0xC7717A0AE81BF79CULL, 0x8355E41FB52F011EULL, 0xE7F9C7F6581EB616ULL, 
            0x6381C2F27132D300ULL, 0x0C63C42B804B5C7EULL, 0x58B49B6D444312ABULL, 0x3FB70635A8ECD29DULL, 
            0x5CD866FD8DA77CEDULL, 0x54AF415DC6C889C6ULL, 0xA5563D792130CCFCULL, 0xE242806915D5D9FAULL, 
            0x7EFEE7001BE34E53ULL, 0x69A46B2B7758E282ULL, 0x228756FCB163B124ULL, 0x122D1FA78B540D49ULL, 
            0x50245F69B96C7406ULL, 0x40B1D687CA82896DULL, 0x72E1ED5AC3A7D5CFULL, 0xCC49FF38EC6070AAULL, 
            0x96EAC58A97DD36DAULL, 0x823967A1DC89D9A4ULL, 0xE5B25238DE67D039ULL, 0x73E8120F9D531801ULL, 
            0x70E77E5CF2B18226ULL, 0xC84C8B1FB52ABDE1ULL, 0xB56768D7A3E91429ULL, 0xB2A1B77320C96209ULL
        },
        {
            0x2D05BE1D3C4AE4F9ULL, 0x500979C5358B54CAULL, 0xB26F6F222EE6B967ULL, 0x8ADEB2A224D512DFULL, 
            0x872FEE0D84D2FB28ULL, 0x65AABD72A02F77B7ULL, 0x23B788C76AEB56AAULL, 0xEE9481385163D7DEULL, 
            0xBBE55F9962F57E48ULL, 0x504F07319CD4129AULL, 0xBBE3A20A9C484425ULL, 0x706EC9302D409FD1ULL, 
            0xEABBB1ECECC8BECDULL, 0xA38B96D0E30972E4ULL, 0xAAB246A44D56D46EULL, 0xFF3E5D175F137E04ULL, 
            0x819EB983F4A5B890ULL, 0x1A4782193E736DE0ULL, 0xD9C116F61FC8B54CULL, 0x09A57256D074D1DEULL, 
            0x3544C58C45241E5EULL, 0x02A0F456A201E116ULL, 0x3433304262EADF6FULL, 0xC51DAF9EAB22D0CBULL, 
            0x0F469FB4FAE83B35ULL, 0x2AD0D5DBBED95E33ULL, 0x5AFBB0287B400A33ULL, 0x0FB310F5614289A4ULL, 
            0xEDCC97CB1E510351ULL, 0xB0628481D104A676ULL, 0x93875275E798EE60ULL, 0x9EB5AAF480FC23E0ULL
        },
        {
            0xB68AA988F81A4F62ULL, 0xEA00EBC10E551B06ULL, 0x880A112CB99F1364ULL, 0x89D5CCFEB3CE32C4ULL, 
            0x8091AAFA4E6E9941ULL, 0x02D80261B2BE13AEULL, 0x0C0DF77607290D1FULL, 0x84E469C3BD1D28FDULL, 
            0x49A2BA4C1EFD1EF5ULL, 0x774E9AB76A1C3B57ULL, 0x5DC8999F233EF54DULL, 0xCC7B1F7D14E40FCEULL, 
            0xC2ABA7808A7BB1B7ULL, 0x25C56DBCCAD7746AULL, 0x971D40D8CCC3503CULL, 0xB3377D8F4E11CD30ULL, 
            0x73AEF8D60199F3DBULL, 0x632B2D403ED49E5FULL, 0x1BC5EE705299FB9CULL, 0x93CF89B02F92DAA5ULL, 
            0x6D379384ABDA69F4ULL, 0x703504C107572391ULL, 0x5A38BBC2D85CE0A2ULL, 0x3CB50A306B3D182FULL, 
            0xEBDA3CD466E846BEULL, 0x2375D9F446C268FAULL, 0xB5B3F8C2BE1AB428ULL, 0x5C7205430319961DULL, 
            0x6D390D0D6792D23AULL, 0xA72EB47B91643884ULL, 0x021E1248C06CC265ULL, 0xFA9D0F151201CC89ULL
        },
        {
            0x619846614679B034ULL, 0xD368D80ECC34634BULL, 0xFCA6D8C71E268C1CULL, 0x06C519471F23B0D7ULL, 
            0x6A854D204B4B1921ULL, 0x762244CE2CB65AF6ULL, 0xFF5130026580F6A0ULL, 0x0EECC386EECBE977ULL, 
            0xF0EA6DA17EE06E61ULL, 0x8015C56CA20D425CULL, 0xED00281AB6D37EBCULL, 0x10C542F725B88B3EULL, 
            0xC87F557233C8D57FULL, 0x1E6AA5E3F2E48462ULL, 0x07D1029567D6382CULL, 0xE4071BB6707F6D6CULL, 
            0x5CB4EECE2F3DA78EULL, 0x38B6C0BE34B23D17ULL, 0xBCDC788A93CCE126ULL, 0x9E90D5ECCBCA8EE7ULL, 
            0xB9EF3D9AB8D7634EULL, 0x8EDB428F8A6A0CA1ULL, 0x3789156561A5554DULL, 0xABEFE0F2D9C74CF3ULL, 
            0x5757CD44859279AEULL, 0x413F3DD505949D0BULL, 0x36CF09AA0DA99E74ULL, 0x41939380E78DBA12ULL, 
            0x4633A8E5405E0C1EULL, 0x67DA9E3A9B947E34ULL, 0xCFCDBB26DC913953ULL, 0x7EB3CE54235E0624ULL
        }
    },
    {
        {
            0x89B2CCEF5E54B090ULL, 0x36980284845F2EF1ULL, 0x99E640B9D65E77CDULL, 0x3A9EBBD82D3EF282ULL, 
            0xB120456FA0B20A85ULL, 0x5FC8D54B2AC71BD1ULL, 0x6BB2F9ECCBCBAD30ULL, 0x19AF22BDAF529C3AULL, 
            0x35DD91C58BDAB271ULL, 0x6291E2DEF11DCCC2ULL, 0xF554168235D998D7ULL, 0x439579D95BFC4D26ULL, 
            0x9989F04A8FD5F8ADULL, 0xCE10D2267B690997ULL, 0x340E076B32B4E791ULL, 0x9977959FB41409A0ULL, 
            0xB487348B6233B85EULL, 0x4B1ABFC00C867E1EULL, 0x48AE4958E6A06839ULL, 0x14A6975760DDD7E5ULL, 
            0x8158B95241C7D8DCULL, 0xA374834B4E9BE9A8ULL, 0xF64CF38A9F99F7B5ULL, 0x69321299099D1D8FULL, 
            0x9BB57615767FC9C7ULL, 0xCE11642BB19D2420ULL, 0x539358EE3A521D90ULL, 0x28997D6DFEAEBC16ULL, 
            0xE597163807D1B0A0ULL, 0x3974817443DDBAFAULL, 0xBA4BE40960AB7C4AULL, 0xD1E081731F89A721ULL
        },
        {
            0xB74F27E3EB3E0D37ULL, 0x0341BCF4732347E0ULL, 0x15BB2BE0F33B53CEULL, 0xFA27F27AB3A370A5ULL, 
            0xF2FABC886DC3384FULL, 0x0A80AD7E76093A5AULL, 0xE51BEFA78F5B0C86ULL, 0x1CACF428F9B480E0ULL, 
            0x2D92C41CCDEDDA50ULL, 0x9FEFCBD322B0F5ABULL, 0xD8561125F1177B82ULL, 0xEB1ACA9B1CDD940BULL, 
            0x1ED630DF6CDFF803ULL, 0xAFED671619A120B5ULL, 0xD833762D92E612E4ULL, 0xF7CA27B0B9770229ULL, 
            0xFF01371A9D805A40ULL, 0x3B5099DDF73FE191ULL, 0x4B57839B1EB104FBULL, 0x5F0821725891C8B7ULL, 
            0xFAB5D1A679517BB2ULL, 0xB2123077360F359BULL, 0x12C28D07379354D8ULL, 0xD4E1D272A1BDA0A7ULL, 
            0xB146480D3113B9D7ULL, 0xF69CAD63956A5B44ULL, 0xF45433D98A266D82ULL, 0x461518DAEF69A03DULL, 
            0x55BC26C48E6BA68CULL, 0xF4FFDD22870FF5BBULL, 0x914BDDFF598D0CF8ULL, 0xA18F9F57606FAD5BULL
        },
        {
            0xD4F879497C84FE87ULL, 0x2025B38EF1855CDAULL, 0xAECCE2B97E1FDB4EULL, 0x84E61BBEAC815269ULL, 
            0xFB926CDF00A89BFAULL, 0x6AC9B8F8E4D85E09ULL, 0x169F2E139975425FULL, 0x8CAAB0D69C2FE333ULL, 
            0x00D571306FB6FB46ULL, 0xE3FC71A605766CF8ULL, 0xF5B496874B6A59BAULL, 0xC15C830DED172CB2ULL, 
            0x0F32EA41668B31B5ULL, 0x9C1AAC79D51B5BCCULL, 0x52E2FEDB45A6121AULL, 0xB097EB74BF6011E0ULL, 
            0x46F7A493CD708482ULL, 0x1B22C59DE94EFB75ULL, 0xAB4B4B4DEE531C54ULL, 0x8F77A3965E83D6BBULL, 
            0x58161FB97AC75E17ULL, 0xA6CD8FDB22347587ULL, 0x154E33F753CAAD5CULL, 0xBE7AE4D85645356BULL, 
            0xBB98888665643FE3ULL, 0x760E6D696DD04DC8ULL, 0x4C8AE96194476427ULL, 0x82C40D2F7B399750ULL, 
            0xD91767722CE8BF0CULL, 0xF477B98F60647B0BULL, 0x93EE1D00EDF55CD3ULL, 0xBF8F1C0281A9179FULL
        },
        {
            0x44EEF3A6DAB77E7FULL, 0xBDB46FD0A1AF0239ULL, 0xFC52998CBD82C487ULL, 0xD433026BD1F0BA37ULL, 
            0xF5C922F0B8F1F483ULL, 0x00AE6E989E6D6587ULL, 0x5E4EE0372AD61491ULL, 0x4E84084534C634A6ULL, 
            0x9D0F7F2B72C1DE6BULL, 0xBD6CBAAFF5FDDF65ULL, 0xFA249EA9CC8C548DULL, 0xB7FA370682F5D429ULL, 
            0x446FCB9F844F3377ULL, 0x23F11331E400A8F0ULL, 0xBBE7695677236C17ULL, 0xDE292319624B24CAULL, 
            0xF0D2FA9AB0A940C3ULL, 0x5516B2C6C72117BFULL, 0xF0C04297F89F0588ULL, 0xCC172E537056CA73ULL, 
            0x89CA8021077E3DD8ULL, 0x9C6637DC2062CB59ULL, 0x69408FF3DC774E70ULL, 0xE826DBF1DA428349ULL, 
            0xEBCDF10471982EA1ULL, 0xEB4BF970BC412BC9ULL, 0x676502905883A353ULL, 0xF771A508ECDAD339ULL, 
            0x8F16EF772730651CULL, 0x6319AA113F292B26ULL, 0x8DE26DBAF9100766ULL, 0x826ECC042B4A6AE1ULL
        },
        {
            0x2C217817C5B23488ULL, 0x02447F5DE76C2BB9ULL, 0x4BB344BA6B2A5E3FULL, 0x0B8AB53DAB016586ULL, 
            0xADC801A1265F76D4ULL, 0x5840CC953E9ABECCULL, 0x4E499149DB92A91BULL, 0x66022E7A746D69CFULL, 
            0x74FB7DD80625E8DAULL, 0x7A1C0CFB0DF72CD9ULL, 0xA7EDDA107074B3EDULL, 0xF5340E033E957FF5ULL, 
            0xB177C0CD9666947BULL, 0x4BC33EC9639B6AAAULL, 0x97F445CDB8C52867ULL, 0x4B3884B0E82BA5A3ULL, 
            0x946A7A75508528F7ULL, 0x60C62758074614ACULL, 0x76E4C2C825428884ULL, 0x440269DA819DBD26ULL, 
            0x2EAF0658C1E9B831ULL, 0xEB4F41245988380EULL, 0xE273903C37C83553ULL, 0xD3FD199F3589BE03ULL, 
            0x03411F5E906B2F1EULL, 0x68277485501DC6BFULL, 0xAD83E1830BC27BAFULL, 0xA1350A0C2ECC2658ULL, 
            0x0A7E52A09F44D238ULL, 0xF6D7468EF6B2135BULL, 0x02B600B7A831162CULL, 0x58055B915FFB1935ULL
        },
        {
            0x5CA211A954465544ULL, 0xD4C26FA7E32F13B2ULL, 0xE0C82D22696FCD03ULL, 0x016D3329B68EE9FAULL, 
            0xCE69CD498314D876ULL, 0x17A8E2F9A87D1FF5ULL, 0x205DC1AE4351B929ULL, 0x4A899FB9E137FBE3ULL, 
            0xA1E78C450485CE07ULL, 0xED22ADF698CAEFEFULL, 0x832C164EC79776C8ULL, 0xD7126CE8CDE944FAULL, 
            0xCAB94EDA7479CF9BULL, 0x241008011DB1F397ULL, 0x912A3EE68DB49B7EULL, 0xAA8CC83469778D15ULL, 
            0x431AA13A35D85780ULL, 0xD188C889DCAEAF78ULL, 0x28B284BC5A74ACA1ULL, 0xEB6D7049397804A0ULL, 
            0x72CFFC5114CE5F31ULL, 0x62340B9F07CFE891ULL, 0xB9DF409310A72A87ULL, 0xB427FFE90F9B805CULL, 
            0xC432CEFCF025FE64ULL, 0x95F80B40FA0C60ADULL, 0xBC773889E08B4F62ULL, 0x4C3E84DC7E905F9CULL, 
            0x1BFBD0B2456A001BULL, 0xEEF021F1DD120C71ULL, 0xF744E6BB6375618FULL, 0xC32113B20A9488C1ULL
        }
    },
    {
        {
            0xC598EF3DA85FD8A8ULL, 0x9C5A35F144582D9AULL, 0xC9D1FE254882A5CEULL, 0x812CCEC24E957588ULL, 
            0x807E9B380E721848ULL, 0x1A1895F6FEC21160ULL, 0x333EA135572433C8ULL, 0xACD4CC533D02B43CULL, 
            0x07221396B175DF4EULL, 0x499845F0C3650C70ULL, 0x80F8CD47E5DB10FAULL, 0x6C9BDE407AF06190ULL, 
            0xE2FC6C5E60CAB93DULL, 0x7ECF6B84D36ED0B1ULL, 0x69997055EF6F33FAULL, 0x33EB4E1A765696BDULL, 
            0x67F78041115BA45EULL, 0x18DA6CB358EA121AULL, 0x6767E5B69B70AB48ULL, 0xFE1E59D545B1EE3AULL, 
            0x1E229AEEAA8C3DEDULL, 0x8D587343A55C87E3ULL, 0x3CB6300636052029ULL, 0xD98EF8797D88487EULL, 
            0xD8DD955554FE9878ULL, 0x38FDA506FD7BA548ULL, 0xAFD54E3115D646CCULL, 0x2264470A21C2117FULL, 
            0xAAD05E868B32C1BCULL, 0x0005049F1951946CULL, 0x28E8415589D3ED35ULL, 0x476D0992CE896E0AULL
        },
        {
            0x46967DFABF975194ULL, 0xF53972B4F4285666ULL, 0xB3706DA2F715AEACULL, 0xEE1C320E6F02CDE1ULL, 
            0x45816BE97C74639FULL, 0x3C89024043BBE401ULL, 0x9D9A8687EECE15B6ULL, 0xE4B6C1E1F439783BULL, 
            0x9D4B19DB2B4ADB12ULL, 0x346522CFC5535070ULL, 0x2AE03DB06612D0D4ULL, 0xEF2DB58D6586DADDULL, 
            0x8CF04107F12FB4C3ULL, 0x2868BD61D4200334ULL, 0x8ABF14D500200888ULL, 0xD6B7886D2BCD2F8FULL, 
            0x0B5785B30A5FA0CFULL, 0xF8AE0E32592584FFULL, 0x7AA60D59841607C3ULL, 0x128376459E1C7E8DULL, 
            0x15B231776D6E9AF7ULL, 0x2361D2C613B86250ULL, 0xC6322DAA07A6C2ADULL, 0x326D9BEADFCBA13EULL, 
            0x70A5C9C6109A0DE1ULL, 0x498D30C6821A9B77ULL, 0x12AED95EDE0E0BD0ULL, 0x5999E9E32560B637ULL, 
            0x669852E7758775F2ULL, 0x6864FF0B0B681FEAULL, 0x3D50644F283A1EAFULL, 0xEF9DBEDB7AB6A0A4ULL
        },
        {
            0xCB2B9AF0C7F7BF7EULL, 0x04E40F2103821FF8ULL, 0xBEFE8472A89EF995ULL, 0xD072FEA6CDE5EEAFULL, 
            0x009A73DFF229BD67ULL, 0xDBBD6EF6A61E8D93ULL, 0x4EB05F8A550EBB95ULL, 0x9A4816B7F1C102F6ULL, 
            0x9E2CD03161C6BDD1ULL, 0x6239CA08B9F1F557ULL, 0xB88D4D9E3E4F92CFULL, 0xC5B9CF91D45ACF79ULL, 
            0xD8F869FCD57E7257ULL, 0xBEBEFE2BCD2227B1ULL, 0xD9D548B24C367EFCULL, 0x347B4B89202ACC09ULL, 
            0xBE2F5E720A66AABBULL, 0x598DB96C450A8052ULL, 0x62F4821FDAC2A822ULL, 0x8FD8DDB63EA7FBB1ULL, 
            0xB710E1BB917420C3ULL, 0x453D50E0289D066DULL, 0xDD32E38CCD2FFC59ULL, 0xBD0FD1B1A69C314FULL, 
            0xB4F4CC54D43DB24AULL, 0xCB0808F7AEFF5E3BULL, 0x51301EF86A9AF458ULL, 0x141814151BC8B47CULL, 
            0x093CFD48A24B3CCFULL, 0x407B30B49636E4E6ULL, 0x53635FCFF3814B24ULL, 0x9E5BB398E4156C7AULL
        },
        {
            0x26D9AB5AB42656ECULL, 0x933E7B9D448CA053ULL, 0x37A16C41051D6040ULL, 0x6F6B854B774F32CCULL, 
            0xFA78F5E4D5507176ULL, 0xEA1E6C709BE1BF52ULL, 0x9A07019D22A18FDBULL, 0x9A279A9D0DD8A1E1ULL, 
            0x4620B77A9114D152ULL, 0x9AA48BF89B45F2E6ULL, 0xF4EF38E6EA7691E6ULL, 0x36590C08E3E1EB12ULL, 
            0xA0CD252C92A6A83CULL, 0x71B6A88EB0BA2B32ULL, 0x3F8048C73A394CD7ULL, 0xCC0666E4C78E3170ULL, 
            0x7FECAB1300650773ULL, 0x33CC4B099DA7613EULL, 0x3D88AC9101FF7473ULL, 0x259823E53FCF3E78ULL, 
            0x5202054CE3A1C1DBULL, 0x58801E506E1B6153ULL, 0x50B667741E7BED9BULL, 0x30485513B10B544AULL, 
            0xF9C88331B65BA04DULL, 0xFC8ED1573938EC54ULL, 0x18CB09A66C77E8E5ULL, 0x6B18A7898D2CCD68ULL, 
            0x2218A0584EDF4BA8ULL, 0x096E423FBC27E97CULL, 0x8B8CE6839AF3BD40ULL, 0xA5AD9F57EA5F7301ULL
        },
        {
            0x7B6EA75B255C1FD1ULL, 0xF7CAEC61B635AD5CULL, 0xEA40E42D5F60D321ULL, 0x665CEE200CE341CEULL, 
            0x099FC61AF2675493ULL, 0x5928DD2EC09932B4ULL, 0xDB804732D9168C9AULL, 0x82FCE60F68CF1D0BULL, 
            0x814ED22382FAC305ULL, 0xF6F1BF90D80CB8D8ULL, 0x602D46506A1FB059ULL, 0xC7B51B4D1C2397A3ULL, 
            0x7999F9BF851CB2A3ULL, 0x8F1B8F78AD69FB22ULL, 0x70DFB1C347F09621ULL, 0xD7659E4E869BF48AULL, 
            0xB633A6CA1B9D7DB7ULL, 0x45BED1A7FEBE5E5CULL, 0xCCD59C4C34533837ULL, 0x6D9096EB210E50CDULL, 
            0xDDB0D223FE9AF8A6ULL, 0x104505E5FFE6986DULL, 0xD9EC13729261D80FULL, 0x18F091D076CA58ADULL, 
            0x3597C7F77C01140BULL, 0xE96751C1CE7C1B79ULL, 0xD743841E0645F188ULL, 0xD5ED515E2156D7B0ULL, 
            0xFEA34CF038233AD3ULL, 0xB4E51D79BA65172EULL, 0xEC5CF5BBD608461CULL, 0x79DF4956824F74DBULL
        },
        {
            0x2F17D83E0EE40A11ULL, 0x316FCFC69BEF67F3ULL, 0x6AF03455084DBD8AULL, 0xEBC10520CEA6AD6FULL, 
            0xD2E6E5F1F7F46344ULL, 0x2F9D5B13A6A43FF8ULL, 0xF578C05ECACBD617ULL, 0xDF4B08DDDF86BFE9ULL, 
            0x451E4C620CA20827ULL, 0xF989710FBF610256ULL, 0x6978BEE7142C3A4BULL, 0xF073D54252E63CABULL, 
            0xA63258AA5BDE61E8ULL, 0x3EEC3EB5C32B11F8ULL, 0x40934C166745DE42ULL, 0xFE30B5BBC86BA964ULL, 
            0xE53EAE06A0CB5522ULL, 0xFA1BF634D8638720ULL, 0xCEF11CD45D2AF4E2ULL, 0x9E9AFF8F0385CD9FULL, 
            0x2892D8E7E74AA6A4ULL, 0xE383FCA7340B3BB5ULL, 0xEA337E532C84695DULL, 0xA46039B708B27988ULL, 
            0x1A9A1F85F21B4798ULL, 0x89248B7D7EC2E311ULL, 0x15641BBB827EBBA0ULL, 0x6C20DE25931E7CF5ULL, 
            0xDBB364C051CD7094ULL, 0x7BF3E6CCEB6F0418ULL, 0x2304729F07DCE37EULL, 0x9EBF944DCB0A49B3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseCConstants = {
    0x3CA8B1C33D6E50B2ULL,
    0x5019524B2769E282ULL,
    0x68861AA39598FDD7ULL,
    0x3CA8B1C33D6E50B2ULL,
    0x5019524B2769E282ULL,
    0x68861AA39598FDD7ULL,
    0x4E83DB6145332AC4ULL,
    0x9D9E7397CBB6BFCAULL,
    0x5F,
    0x07,
    0xF7,
    0xB0,
    0xC4,
    0xF5,
    0xA6,
    0x8C
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseDSalts = {
    {
        {
            0xA4DDF588F07F861AULL, 0x03F121A9C1E730C5ULL, 0xB744F9237731B37FULL, 0x15AA5E56C1543D23ULL, 
            0xA02839CB419F4017ULL, 0xA38966C1334DA237ULL, 0xA8EF308357AA143EULL, 0x23B5BA6589DF47BBULL, 
            0x9CBF0DE9A6382845ULL, 0xCDC47466656729B8ULL, 0xC97752875FD79DA8ULL, 0xB25D88F704DE85EFULL, 
            0x926DBDA1A8DC9869ULL, 0x1258297CA29CA645ULL, 0xB536B6DD41FCF5E3ULL, 0x4A4D766F7734C0DFULL, 
            0x57DEE16B721E751DULL, 0xD3737A3E456C7037ULL, 0xE89F4C392420A9A6ULL, 0x88C588B8CAFC9E9AULL, 
            0x02DB98A1FB6A0FCDULL, 0x7998681A425DF9F3ULL, 0xCA1A126EFAEEECFAULL, 0x5A1B9F0E15909D70ULL, 
            0x08F937852F155274ULL, 0xC874E9E9568837C6ULL, 0x4DBB9ECEB77465DDULL, 0x4F84EB2B41D6BA06ULL, 
            0x1A1DD119934C22C9ULL, 0x2B0AD73BA69962BBULL, 0x4D4ADFAB15F1B230ULL, 0xA71C054556705F2BULL
        },
        {
            0x71C503897C094D31ULL, 0x491DF28E7857D06DULL, 0xB6D5B758C0B6D043ULL, 0x348B292A19DE2E05ULL, 
            0x106ED0114C08A1D9ULL, 0xA48B116B2D093136ULL, 0xC4FC410AEBFB1F20ULL, 0x2F828AD1CBBC4752ULL, 
            0xE6539E88BB563AADULL, 0x532ECBDB688A4F11ULL, 0x3FE612EA211CD968ULL, 0x3884824836E66AE2ULL, 
            0x4630462689B4ED43ULL, 0x7987B357C32F9A0CULL, 0x0088C6234507102FULL, 0x81A69AB8E4122BF0ULL, 
            0xFEE81401FB1ACE79ULL, 0xD838D08472B7C4EFULL, 0xE04B42389796A045ULL, 0x8D212B0500DC03DDULL, 
            0xFDDF963E48292AA9ULL, 0x8BEA4F81863A0D24ULL, 0xDD416B48DC4BAF6CULL, 0x8080616DA4BCE73CULL, 
            0x73A7B7E2575FF2B2ULL, 0x7C8410DCE00A7246ULL, 0xC8014DC442D527DDULL, 0xA480458E862DBBF1ULL, 
            0xC399C3FBD40A7AD3ULL, 0x2D3C042BB743D5BEULL, 0x7BAFAE42E503AB53ULL, 0x3CCDA98650F4A86AULL
        },
        {
            0xFC7760213111ECE9ULL, 0x27EA2498C85FCB19ULL, 0x90FE7F65CB0899B4ULL, 0x3768A620A461ADA1ULL, 
            0xDD8EE2EBABEF1BE4ULL, 0x51BF79B57D1FF62CULL, 0xC88D5368F7D287FBULL, 0x12C2A0B280F95B76ULL, 
            0x9431F5BCB8CC2CE9ULL, 0x64428F32C7171735ULL, 0xB4BE060FC3B25A5BULL, 0xE05DC969524A4C47ULL, 
            0x5D13FC0D2888C462ULL, 0xDD400A33120A11C5ULL, 0xE77552A9C485814BULL, 0xBB517FE923ECF678ULL, 
            0xB15EA0A648E8C98FULL, 0x959ED7FE56641AD5ULL, 0x57620668A28AFAF7ULL, 0x2637DD5E21520D8AULL, 
            0xF1E42825E059DFE3ULL, 0xCEEBD57E64428FF8ULL, 0x7EB0FDA3DD27DD59ULL, 0xEFFA4B5E33C6575AULL, 
            0xEAC262056A862049ULL, 0x28D84882C24716C1ULL, 0x86DB5EB664FCB5FFULL, 0x2A7B87A57F637A4DULL, 
            0x58FFFF60212480A8ULL, 0x37C1288386DD6A77ULL, 0xF0A76E800AAADC55ULL, 0xC45ED3B58504E585ULL
        },
        {
            0xBB2696DCB8267508ULL, 0x5EA4363DA2B3FB34ULL, 0x60AD8EE71E53516CULL, 0xCAB151DF32D6426BULL, 
            0x4F7AF20A36DF3225ULL, 0x4A2C23797BAC1CB6ULL, 0xD429D1F8A6A4435DULL, 0x789A1E7847053D8EULL, 
            0xEA58C078EA31297FULL, 0x5DC36CD71EBF48D4ULL, 0x6B4CCC6BB20ED7BBULL, 0xC2A98AB173C930D4ULL, 
            0x27C83FD66586B611ULL, 0xE3B1F51B2636D291ULL, 0xFFC5E17BBDA8F311ULL, 0xA653E5F539136EB1ULL, 
            0xF0C31B08D9442287ULL, 0x82693C43A6AC01F1ULL, 0x15D0C8747B25F232ULL, 0xA82B570C1B96CD88ULL, 
            0x47906F679E65253AULL, 0x926E4564BE5CA705ULL, 0x9CBDA74EF1A92CC4ULL, 0x9D203D8D00CF2D71ULL, 
            0x563AB6E48E614FB9ULL, 0xB408FC6CBAA394B3ULL, 0xD98A32D1E7C6D8DDULL, 0x851A3E59AEA9E852ULL, 
            0x3802396110836C3EULL, 0x63F97BE0B1ABF4D0ULL, 0x31CE9D3A71914F3FULL, 0xA55FB12F0D6F2261ULL
        },
        {
            0x07A0C12B374443E7ULL, 0xDCD24FB28929CAB9ULL, 0xBEDDC47B5E2D6389ULL, 0x2D177239F47E0825ULL, 
            0x87D1687202FFC89DULL, 0x518B1A92259DC76BULL, 0x235FFEC4EE43C11AULL, 0x180D4035C2D0A664ULL, 
            0x6FCFA1FD17D48266ULL, 0x8F016B4598B04C64ULL, 0xE7FB57C49906F76CULL, 0x8138D099E9CC6939ULL, 
            0x500387F8D76E9742ULL, 0x4D6B17FC9C0A35FDULL, 0x65AB5ECEDE8843AAULL, 0x46CBC9661474E561ULL, 
            0x50402AA3736D2F9CULL, 0xBC35F379C78CB7E4ULL, 0xC6ABCFBC5F6D09B6ULL, 0xDE47AF5AA2B137B0ULL, 
            0x5C1722FF2E5E314BULL, 0xFA237FE22FAED5DEULL, 0x9EA91F5D6FC2C309ULL, 0x734735CCBC2086B3ULL, 
            0x1D497CF510A55FB2ULL, 0x2AF8A0BD56192406ULL, 0x07F2E01C5229F4F5ULL, 0xD612924FDBE81B9CULL, 
            0x2B97C65BC9F00F06ULL, 0x73121A328779E342ULL, 0x0FF3ABB9DD58924BULL, 0xB7AEDB67D9B36692ULL
        },
        {
            0xFB132958FA455F88ULL, 0x43D7BCA439C693EFULL, 0x1660B44BE64364F8ULL, 0x8E7C9954482593C4ULL, 
            0x49E105C18899C2B9ULL, 0xADD502C5913FF267ULL, 0xA171190B0ADF1844ULL, 0xD86D1CAB6CE7521FULL, 
            0x6A189997A1FD82F6ULL, 0x3595804DA1AD8BC3ULL, 0xB4FEA6E1EA06553DULL, 0x4D79960B44BEFAA9ULL, 
            0x7125D5F6E4A58D50ULL, 0x83173BFA048F9D0BULL, 0xB6FC2A2EDDA81B12ULL, 0xE5501ACF745B4C66ULL, 
            0x5FFDDA67C59FE48CULL, 0x8288C38CD032885FULL, 0x4B040491C2920A1FULL, 0xE399A8AE708D10CFULL, 
            0xD250ED8DC2B3C504ULL, 0xA1156D6E2F39A372ULL, 0xC701E57F6F093B95ULL, 0x5FCB350A4AF70613ULL, 
            0x73F78CC859DA36EDULL, 0x6247A41E0B9858BEULL, 0x6254BE3BAC8459D5ULL, 0xC408829C9A1D1C5BULL, 
            0xE4823616A790BC87ULL, 0xDCEF5BF06D27B47AULL, 0x45EEF015C59F8DD5ULL, 0x564AF42758D1EC47ULL
        }
    },
    {
        {
            0x32A36F8555823FF4ULL, 0xFCB76C5C747FF59EULL, 0x960319CE9F9952F4ULL, 0x0D6941A6437EA0CBULL, 
            0x731FD950A5A39E2DULL, 0x2329FB604D284E77ULL, 0x86D45F46E12F5098ULL, 0xB5758EB7C0D22127ULL, 
            0x42AE43AF8D3AA99CULL, 0x27591B695CEA6A10ULL, 0x044AB74AB9EE742EULL, 0x8871D990AE6C5F06ULL, 
            0xEAC342BF248151DDULL, 0xB9C2F01AEE890BF8ULL, 0xD276F20EC891C776ULL, 0x1B018EDB1A8AFD8CULL, 
            0x66E0A32922275536ULL, 0xA4B761494FC950C0ULL, 0xEB20C20FD0A6D40AULL, 0x265AD8CEC5A3A4BDULL, 
            0xE0532EAF9E9665D1ULL, 0x8AA02CD3F5278935ULL, 0x87587980C342B3BFULL, 0x10DA847F40BF5C87ULL, 
            0x4DE546D89E178AE6ULL, 0x7229126D39734E38ULL, 0xE137376BDCDD8506ULL, 0xEB26D28623C84CDEULL, 
            0x4724F91CFED0798AULL, 0x6F6DB1E4903B7DB6ULL, 0x594DA7D054936764ULL, 0x14CD92C53B11189AULL
        },
        {
            0xFDEC7D423AD1CF6BULL, 0x3D34D872962919C4ULL, 0xD6FC5CD7CD0A8AB1ULL, 0xDC731FE4939ECA9FULL, 
            0xCE2121AFDD4D4583ULL, 0x4C6AB5DFBD386F1FULL, 0xC2636865CAEFCF62ULL, 0x19BF4D067727FB39ULL, 
            0x21997BE24264F534ULL, 0xDFE023CEC452EB09ULL, 0x3593753B189094F2ULL, 0x7A86557144670E5CULL, 
            0x05C4FC0F9AE954CBULL, 0xD5447502C8AC0427ULL, 0x15B41E746ED560C4ULL, 0x6CF968BD92EBCBA9ULL, 
            0xFC53506A9D82C073ULL, 0x976D28C36445C111ULL, 0xB9D7E11E6E279C9EULL, 0x91B1D6DE19BF5C46ULL, 
            0x49ABA0963B658115ULL, 0x07C05D984B606DCDULL, 0x9A2BC3088B33EFF8ULL, 0xA428866D866A4CF2ULL, 
            0xC451669670B7019BULL, 0xF3A1FFA0904B31A5ULL, 0x6B483CDDF3DCB25CULL, 0xFE92E9352D971F90ULL, 
            0x397DB6B11630F7E0ULL, 0x812695F4E5C89AFAULL, 0x3846A42D45E7C2C7ULL, 0x8E6DC81D9093BD4CULL
        },
        {
            0x23DE2EEC41E3603DULL, 0x11A493CCA5B6E163ULL, 0x27AF0F4B5F5433EAULL, 0x592D065B1FD889A7ULL, 
            0x33012EEDAAED7C38ULL, 0xF1C972616E31346BULL, 0x6A260A4A9704F68FULL, 0x7611D0D206F8D691ULL, 
            0x4F5E929A90D8F012ULL, 0xDF9AC9AB45EACB8EULL, 0x629C0B65BD20D427ULL, 0xF0ACD965C9DF9800ULL, 
            0x1A892FAB968442F7ULL, 0x97D30C762FAAE694ULL, 0xC04EFC47E46A85BEULL, 0x166ADEEB2B0804AEULL, 
            0xFCC2F3E358A839C8ULL, 0x0E1FF013DFD9FAB0ULL, 0x49EA40C8945B4413ULL, 0x897A1CCAD2C83290ULL, 
            0x670186F8185C6C58ULL, 0x487A84A5CFEA54AAULL, 0x35D0DB1CAC63888AULL, 0x9AAE3861348FAA63ULL, 
            0xFA6B18C62F72CFC5ULL, 0x01205A64C362C86FULL, 0xBD51F936FB6DE74CULL, 0xD56DE027276E2209ULL, 
            0x3FDA000A2974B107ULL, 0x7CC183F9684E9FFCULL, 0xD5C6099486E5E8C9ULL, 0xF9E561B38A092706ULL
        },
        {
            0xF4095DA9054AD2E1ULL, 0x46345F0C44C7AC0BULL, 0xB83B9681D9E947D6ULL, 0x7E43B9CDAE88CBFAULL, 
            0xB5115994643341F2ULL, 0xFD8235B80A1C151CULL, 0x1066A9F82495AFCAULL, 0x1B4D5F274D4A4E8CULL, 
            0x688826479E4F7905ULL, 0xC395544466CB5EB7ULL, 0xC2130CBB299A8F1BULL, 0x98F906C17AA8E438ULL, 
            0xFC835D5ED6A3A008ULL, 0xB5FC45F0C8CC6F12ULL, 0x9C4F0255DA479732ULL, 0xF6A06F4B8B22F16BULL, 
            0xBE50AE60E93274A2ULL, 0xF6126B236CD7C7DAULL, 0xB7DFDFBBF1B35C4AULL, 0xD97A38946C8D7786ULL, 
            0x2B44CEBF21C599F9ULL, 0xE2DAF8FAFA2696C5ULL, 0x550449EA41B51031ULL, 0x0BA61826A6989538ULL, 
            0x95D2BD99C655C030ULL, 0xBDD2A30B10C48FA4ULL, 0x30AC4E33BA2A8060ULL, 0xCE94CEA7202FFA68ULL, 
            0xD4A90341C8A96E2DULL, 0x5D6589FB825A8A55ULL, 0x237B34D5B4C74124ULL, 0xD0E3B628713F8136ULL
        },
        {
            0x25D398A2652EFE60ULL, 0x23B14B931156370EULL, 0xB687897F1188485BULL, 0x18711120AA02E786ULL, 
            0xF32FAB470BCBB003ULL, 0x4C3086E235E61540ULL, 0x38054384DCD1FF22ULL, 0x76E025C20B4FD81DULL, 
            0x7F9AE929DC509AB3ULL, 0xC3E4F13376F78A43ULL, 0x5C27AC69F44A0148ULL, 0x83D2A44D9BA8D6DFULL, 
            0xAC0368E7600DE7D3ULL, 0x46FB399E5549F968ULL, 0x7DEE54B345E37C8AULL, 0x05FB2A58DC4FE7EBULL, 
            0x33EDD9A08DAB86ADULL, 0x97E7574B70027D8BULL, 0x28A624C9101DEA90ULL, 0xC6A9AE29F2028900ULL, 
            0xA31A36DA0F370B32ULL, 0x77F8C0F5BDDA497CULL, 0x67C35A5EF9082A07ULL, 0xECB54606C0B1807FULL, 
            0x1E8015A793360B87ULL, 0xC7EAB8067992748DULL, 0xD9DA99BE593BC869ULL, 0xB4630E611D12A6DFULL, 
            0x6AC21EF3FCADA3F5ULL, 0xA9B574A89C7DC90AULL, 0xF7CC03EEAA3BE73BULL, 0x656B3A8CA0436C67ULL
        },
        {
            0xAAA9F015DA1937B9ULL, 0xA5277099930FF806ULL, 0xE94043CA3C209CB2ULL, 0xC6E44725231F7EDDULL, 
            0x01EABBE381A4577DULL, 0xE74D848B580E9DECULL, 0x26FEEC164C3F8289ULL, 0xAE6C5C6C7E11BDF3ULL, 
            0x2E4B1BCB6892F9F9ULL, 0xC62E04B17B487F66ULL, 0x56E96BA5A1349487ULL, 0x65EF01170BA8C094ULL, 
            0xA84A305F785E0B7BULL, 0x35B1C9A23F514951ULL, 0x93EA4A1988228B40ULL, 0x144003CB1950F6C1ULL, 
            0xDC968B7DEA361829ULL, 0xC1399C6997CBACB0ULL, 0x9936407B1E6AF9F8ULL, 0x5A365789E2977D6DULL, 
            0xA6A06EE2EBE58352ULL, 0xDFE4863C99B39099ULL, 0x0953D476064FD7FDULL, 0xEE0640CCAF8EB520ULL, 
            0x47758CD2D4990C99ULL, 0xAD3A0DE1EDF3FE59ULL, 0xB7B7C6585DD607D5ULL, 0x8A99AED65A39C888ULL, 
            0xB4F4577CC903E600ULL, 0xF69AEEB834135FF5ULL, 0xDD3182E84FE0AAA1ULL, 0xC1E7E54E649E9EC7ULL
        }
    },
    {
        {
            0xAEF616E92E353B3AULL, 0xDD24C6C20160C9BCULL, 0xD8DA26862097B22DULL, 0x4EFBBF0AEA74A109ULL, 
            0x72907D35A810F7F8ULL, 0x7323AEEC2ECAE5FDULL, 0x7BFADD8261AC354EULL, 0xDEF120E267F63D87ULL, 
            0x848A4090B137E890ULL, 0x231A01BC30570EFCULL, 0x53E335DAB02C3F34ULL, 0x69E0713D5042BF98ULL, 
            0x0B7FCCEEA9F7F7F9ULL, 0x92A0B2E5E835ABFEULL, 0x686ECC6EC6C8C9EFULL, 0x5A840925F9BB7687ULL, 
            0x4771E488E58DF80DULL, 0x27E5719F26D9FFF9ULL, 0x954E9B90F4322655ULL, 0x1A24E5494ADAB9D5ULL, 
            0xBB6FE0BE44449C42ULL, 0x1CE20AE23B832674ULL, 0x8ABDA6696458ADD2ULL, 0xAF3FFCBD78EEF22AULL, 
            0x71B1AA8FC9AD4C4CULL, 0x8A85F8A08330CCE5ULL, 0xCC18E5424173F436ULL, 0x20EDFA0C0D5A735BULL, 
            0x5B1A5F6D5537E3AAULL, 0xF635AF74C3499B2CULL, 0xA22D1B53B98D9FDAULL, 0xAD0ED90A56822838ULL
        },
        {
            0x5A1914B7464D4BE2ULL, 0x4631E4C5196AFCE9ULL, 0xABCE5318CE1EFB15ULL, 0x7EE6077815BE14ACULL, 
            0x9ADAC7618E33E41CULL, 0xA403550371BAE54DULL, 0x1CAFB3EBFBF42881ULL, 0xF43C2B5A6D579DB6ULL, 
            0xCCD1D06E5019B1B8ULL, 0x451B098D9C469F48ULL, 0x830C6C87DB7B4CE6ULL, 0x3DCF798477F49DF6ULL, 
            0x3D77D490448116CEULL, 0x39AFE6EE6B51DDDCULL, 0x282D1F1369E8928FULL, 0x01ADF8793FC8D051ULL, 
            0xCCA263796049E802ULL, 0xBE7358749C7F8AE8ULL, 0xA8B3302E3A3812A5ULL, 0xDBDC98FB59F14490ULL, 
            0x2C90FA0B98A3DBCCULL, 0x330D86F516434B3BULL, 0x63AC2BEA4DE1DF1DULL, 0xE7AA3FCC3D523543ULL, 
            0x5B65ACAA9C93D9E5ULL, 0xE4531D98F8E7EFEDULL, 0x4A1AD3F34B59F451ULL, 0x3D314D8980FBB35EULL, 
            0x36D21D15EAD30173ULL, 0x2B04674AD59544AAULL, 0x323581941DB977D4ULL, 0xAC06CE7C77B18FABULL
        },
        {
            0x7531F1B377E005FCULL, 0x44CFD684E29745DBULL, 0xE002CE95BEB5575CULL, 0x2CA3011487CC0B45ULL, 
            0x48FF198E987722B5ULL, 0x463BB3AC7D69CC58ULL, 0x567F88049EDEAB09ULL, 0x1B4D19B31D891E22ULL, 
            0xFBC90F49F0EA8C78ULL, 0xE2F171EA518F7283ULL, 0x8A525F01B4DF9153ULL, 0x1C735546146EAC82ULL, 
            0xEB42240EDC873EB9ULL, 0xC47A4FECA7B4D1BCULL, 0x3B54CD82811EA526ULL, 0x108347A754D70982ULL, 
            0xB7ABA3F897A396A8ULL, 0xE8D6D1A5A5B50614ULL, 0x7FB400ADA3DADDEDULL, 0x9DFCC52DAA897B78ULL, 
            0x7B5242914842AE67ULL, 0x745D33EFDB3924EFULL, 0xE083955470FB713FULL, 0x21C01CF2E61B514EULL, 
            0x36FDF99E9DEF577FULL, 0x97809E8963044476ULL, 0x72D21BCD7F5162F7ULL, 0x1BAE942B9EEB7FC3ULL, 
            0xAF2F63663A718DC6ULL, 0x02C4E3E0FB21CE79ULL, 0x30C58DA00183C3F6ULL, 0xBDCFF3C2D118BE6DULL
        },
        {
            0x962144F836FA1E3FULL, 0x60DE952274C26D50ULL, 0xC07CDCA7A47C45C2ULL, 0xCB7429E137A9E2B3ULL, 
            0xD5719E30A9B2C8A4ULL, 0xAFFA27B89DF5B284ULL, 0xBA121A654E3F79FEULL, 0xF9746027A0406D23ULL, 
            0x5AB4098FB0559884ULL, 0x2E5AAD1C24CFA5B1ULL, 0x4E61CB51F4A40E23ULL, 0x2A2A2AF7340F26C6ULL, 
            0xC9DEED57B6024529ULL, 0xAFF8743191B14A3EULL, 0xDB2B6DCF2CB858D7ULL, 0xA3BB7214FE7D4F07ULL, 
            0x7BE6DFC7E61B0B10ULL, 0x76B35D0CAFFEE6F9ULL, 0x3D1A8A01726E80C0ULL, 0xBEE0DFBA43459E18ULL, 
            0x8728A973225D8A8CULL, 0x068F14D5B3F00D8DULL, 0xFEB62B863CEBC914ULL, 0x78A2348FFA4EC491ULL, 
            0xB29A8EC2308087A4ULL, 0x04262F43F9014B97ULL, 0x43FFD07841013804ULL, 0x26A3643617EE5B4AULL, 
            0x37265AAD12CE50FCULL, 0xD90525D51820C429ULL, 0x1003A61BD788CF2AULL, 0xA9209585B296C1F0ULL
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
        },
        {
            0x19B6B0D5F52F45F7ULL, 0xE3DB3F63E5526433ULL, 0x16AAC3DA278E4219ULL, 0xBCE5AE11628E1EE4ULL, 
            0xDCED303FF7D91FB7ULL, 0x6877A3C4CA4C7848ULL, 0x3C855D965BBFEFBDULL, 0x17573BF06218E8EBULL, 
            0x6EB589E828876B64ULL, 0x5770E53F8004FBE9ULL, 0xE57FB092EDF3E187ULL, 0x0D7419553D4BE243ULL, 
            0x206BF5C9FA284F73ULL, 0x4B868DC3ECB0E84FULL, 0xE511F208D97C4ACAULL, 0xAD9D0A369D9FDAA2ULL, 
            0x0B45D99DC4647CD7ULL, 0x2E0A0E073184C89DULL, 0x47DBAF45BB038BD7ULL, 0xE1D02D22590D7DA1ULL, 
            0x26216EC2B1CDDF9EULL, 0x2418FA07DBEC2064ULL, 0xD2DB406DF0C83F85ULL, 0xB5D7399E089E6432ULL, 
            0xD696C5D626A2BF9AULL, 0xD41FC8E9DEB5B2BEULL, 0x52AC361E958554F2ULL, 0xE1CE38FB943F2CF5ULL, 
            0xE959C2563EB5CFA7ULL, 0x0BE3E0A2BAC6E75BULL, 0xB9C9CFC8B2A096C7ULL, 0xE147490F461074E3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseDConstants = {
    0x567BBAA94555ACA6ULL,
    0xA07D9E9F7851F4C5ULL,
    0x2DE3EE1D50E6B7CCULL,
    0x567BBAA94555ACA6ULL,
    0xA07D9E9F7851F4C5ULL,
    0x2DE3EE1D50E6B7CCULL,
    0x271D44B9FAC0C9D6ULL,
    0x870ED6993E795B7FULL,
    0xAE,
    0xC8,
    0x9C,
    0x3F,
    0x25,
    0x70,
    0xE7,
    0x06
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseESalts = {
    {
        {
            0x8B92615D198581DDULL, 0xFD5C447AE89AB393ULL, 0xA14EEAB7D550182DULL, 0x1E77916FC7C44BDFULL, 
            0x74EA079E981FB435ULL, 0xC8B19AFAB788E173ULL, 0x0284668DB653BC00ULL, 0xEBDA5AD9386822A8ULL, 
            0xBCCD0AC757BC6026ULL, 0x3355E574019E6CAEULL, 0x4038AC132919727DULL, 0xB97A35A65107BD55ULL, 
            0xF4F7DB897FB0020CULL, 0xD2A25D272E5A4248ULL, 0xD0CF948128EEAB6EULL, 0x8450A9AC5D66BDF1ULL, 
            0xF0900DC0409CF91EULL, 0x5A752FBB9D9B3CB1ULL, 0x4E0D6AA213F0202FULL, 0x7A529C98CA81F9B4ULL, 
            0x92B70BFC90F1F662ULL, 0xC4D951CE416428B0ULL, 0x5796765B8AFE1FEDULL, 0x12A0E2485D531FBFULL, 
            0x02C96EFD80EBFEAFULL, 0x7FC12D7C4FB58975ULL, 0x031C461392543FA1ULL, 0x13F58D11E2E7475FULL, 
            0x9615DDEE4E777112ULL, 0x44429FEEE4E10860ULL, 0xA92F7DE86228436AULL, 0x4AA86B451D69A13AULL
        },
        {
            0x16F29D2319EF6A20ULL, 0x0C02D17F386DDAF8ULL, 0x4FD2C32A854313F5ULL, 0x87CAE2C19DF2324FULL, 
            0x7864DD8DC6971BF4ULL, 0x427012012A92758AULL, 0xBFFF16EF36F822B8ULL, 0x1DBC78B78FB21D93ULL, 
            0x4F57D061CFFD8C89ULL, 0x9AA8062F1F9B383EULL, 0x31C13204B89CA4F5ULL, 0xC1EF5D68B4BA7554ULL, 
            0xC125633D36ACD8BBULL, 0xD629DC1BE50348BAULL, 0x0BB718A7770DCCC9ULL, 0xBFA36802A0A07BADULL, 
            0x825C18A2645DD121ULL, 0xA6D041FDBF6C5A8EULL, 0xDB4EA3185E857244ULL, 0x256FDAD5C68119FBULL, 
            0xF87E2FC026E29A43ULL, 0x2ED81DA16D4F9BC6ULL, 0xC46F2DBFED55D685ULL, 0x0D96E0AEE66ACDC0ULL, 
            0x8E5E3ABC4F29B314ULL, 0x0DD4E7ED089C6268ULL, 0x8EEBB51EF0DED341ULL, 0x26F0E788F3ACF0D4ULL, 
            0x21053EFB1FAF3936ULL, 0xD6E31C68506E84FDULL, 0x8BDAF5099FCBB4AFULL, 0x36D6CB3AFED480EFULL
        },
        {
            0xABCAB61599AF3A17ULL, 0x1ACA72EB00012D39ULL, 0xDC5D22826F8DB7F0ULL, 0x25ED09CF1B2D8B8BULL, 
            0x56F99988A9B9B04BULL, 0x270816F9D41D44CEULL, 0x282D460F6B904FEFULL, 0x3C6A1E0CC6F2E5E0ULL, 
            0x2D6030202455A4E0ULL, 0x63007EBEEAA554E9ULL, 0xE7187D8B80FFA257ULL, 0xC6EA31F5FF4209ACULL, 
            0x7EF90DB146ED8234ULL, 0x1D9DE23EB817668BULL, 0x5079DAF275BFD7E7ULL, 0x79C8175326226F49ULL, 
            0x450C1E8FE2CA0565ULL, 0x76CBA08E2C73DF66ULL, 0xCA6B68BF433CA610ULL, 0xB1EA0E653D02FDFFULL, 
            0x6FC5072D0B88D468ULL, 0xF025E572A4192973ULL, 0xD2EEFE2318AD2C53ULL, 0x569A187727F12C68ULL, 
            0x85C71C2ED880A6E9ULL, 0x4D3F7411583DD55FULL, 0x756EBBB845D8F4C6ULL, 0x788694A1CF9D23EFULL, 
            0x982E29E2EB93D1D0ULL, 0xC2746A3421445BE0ULL, 0xAC22DED954E7923CULL, 0xFE0C9033A5CB54C0ULL
        },
        {
            0xEC1AFD1606D61173ULL, 0x14C50679845E92BBULL, 0xBC8428771181E642ULL, 0xCD604C688CCA9E43ULL, 
            0xF0D64337775BA0ABULL, 0xCD0157DC068398B2ULL, 0xB66CB3C0674EE450ULL, 0x1B58ED0CD9743555ULL, 
            0xDC91D62915BA653BULL, 0x0EA501ECD4314D88ULL, 0x3A1310038A2B5CD9ULL, 0xE77A5325ED625714ULL, 
            0xC31630D0F297E00DULL, 0x2BD8951A61ACC276ULL, 0x98338ABC2C7D84AFULL, 0xF1646F88C1796328ULL, 
            0x8BC90CE0AD864EAEULL, 0x2643B15A244B3DAAULL, 0xB44DEF17BECB8A3FULL, 0x1D340F4AEE647A5FULL, 
            0xF6788E0BA7F9EE9AULL, 0x291DF012B812CD89ULL, 0xE86EE6660B3421B0ULL, 0xD8CD9D1583A3557CULL, 
            0x58871299DF520925ULL, 0xBC8F0A40F2E4392CULL, 0x92A562CC50567562ULL, 0x1F07A09B761AD832ULL, 
            0xF284E6E7CD564CF2ULL, 0x79E270D67D9E7D7FULL, 0x50FA7CDC4C8E608EULL, 0x3AB6CC315D638292ULL
        },
        {
            0xFB7F187BF368BE8DULL, 0x151C3E09D2CC5A9DULL, 0xA6CF780D9AD6696EULL, 0x98BB8785CC143883ULL, 
            0x45950F44C3A96243ULL, 0x4D698C10931BC343ULL, 0x17CE46555CACC933ULL, 0xFC86803D8253B2A3ULL, 
            0x2FABCB02B2A3B93DULL, 0x3B016FE02FD47427ULL, 0x5371ED88D7230F57ULL, 0x590CF747334C6FF1ULL, 
            0x0C453FE9607259BCULL, 0x8FA4B1A34456E82AULL, 0x3DB9E6545D5218E2ULL, 0xE03F39400FA8F94BULL, 
            0x1F9CFA4FB4849BBAULL, 0xBFDD07FE2F19002CULL, 0xA9A6E1775F7E2E97ULL, 0x004AAA690F5B4B6FULL, 
            0x89D5F194D808E10BULL, 0xA893E871F707D022ULL, 0x2E281F91F8419887ULL, 0xB1FD4534FF0C4669ULL, 
            0x633D95396AF38EB0ULL, 0xCA43BCCEE85E2175ULL, 0xE9703BEBAD4AA417ULL, 0xF7A263706A42FBBAULL, 
            0x02A19BD9A766307EULL, 0x662B256379A696C2ULL, 0xD71FA612F7972DBFULL, 0x25A403DECF34DCA3ULL
        },
        {
            0xA9B74A1F0A7449D1ULL, 0xA23C79C010D2F6CFULL, 0x72A18C4DC38C8029ULL, 0x685EF2C802D2147EULL, 
            0x2A7C20C06CFF4956ULL, 0xD8D5D12E05BA4ABEULL, 0x0CC3A35B089A49AAULL, 0x752C560147F229D2ULL, 
            0x2964632EB0EA704FULL, 0x24C19BF2E0544ACCULL, 0xAD99B5B623AB1DFCULL, 0xA1B724435D8F2913ULL, 
            0x85771B4DEA03EF20ULL, 0xAAC2D8FF43DFEB1EULL, 0x9F579B57C771B6C5ULL, 0xABD4B4E14638A750ULL, 
            0x64459E4FF7759D0AULL, 0x47C38BD47794D285ULL, 0x22B658D9F8A2D15BULL, 0x288BCDAD50695BD1ULL, 
            0x13650F5E4646BD79ULL, 0x06017A072256C001ULL, 0x6F51FAA64197A754ULL, 0xD042B26D23E7D3C2ULL, 
            0xE7F83C849D2CA75AULL, 0x8E05074D3157D75BULL, 0x63277B4F2E91EA8BULL, 0x43F2C126A1D4CF12ULL, 
            0x97C1FB0BD5317BA3ULL, 0x8FF3C8E9E8E46039ULL, 0x3A834E9738ADF557ULL, 0x00C8F6217B23065AULL
        }
    },
    {
        {
            0x24CF8B39189A1A6EULL, 0x5319E994267D4944ULL, 0x9D0BE2CA9E6D5BEFULL, 0x7F1151DA79525DF2ULL, 
            0xB5DA8D1AAD8147EFULL, 0xADF96EB307BEB2D3ULL, 0x7C9EB2C4C43B03D3ULL, 0x3BD31A55CB313B3CULL, 
            0x9A9AED922FBDD0BDULL, 0xCA31F3878C6D87E4ULL, 0x63FDB8DC8245D4B7ULL, 0x0A769FB5D92DC22FULL, 
            0xDB53DBDAAFD81286ULL, 0x62E412B5149A297FULL, 0x7D75053FC57FC85CULL, 0x5459C698765E5B3DULL, 
            0xDCC48C12D3DE55DDULL, 0xC5253B30CD82FF42ULL, 0x4D8F98F06A0188CAULL, 0x6F5FF9BCD3A1214FULL, 
            0x9B3F0F7681047D9CULL, 0x4CD40B744BA56ED9ULL, 0xE3F7AF1A909C1498ULL, 0xC9E1B7757AE0A1CCULL, 
            0x1A0CF3BD2D1BB410ULL, 0xBD6405A8628E41B0ULL, 0x02A4E003C3DC5C47ULL, 0xFB96C953209B3E29ULL, 
            0x7EA803D0D0400768ULL, 0xDBBD93B162CA9C12ULL, 0xB8B16BB037C2AF1CULL, 0x98D64A5EA4410A42ULL
        },
        {
            0x6BA790AF72C3CD77ULL, 0x7DDEFE87865823C8ULL, 0xF55A6117CF250347ULL, 0x0DCD645FDC6D96CAULL, 
            0x993810DCD31D4834ULL, 0x66E1792D6FB8C120ULL, 0x8F893B53422D17BAULL, 0x7970CCA898438DE1ULL, 
            0x044DDD61B4DA5DBEULL, 0x57C05FC9C676E17CULL, 0x5ACA698344A819CFULL, 0x73A93AA2027B86ACULL, 
            0x16FBE4A255B0CAD3ULL, 0x14B6ECD3B9D83519ULL, 0xAB0802B3017DDFF7ULL, 0xA6840D16046E4BBEULL, 
            0xC86BC6BB015942CFULL, 0x27E11EE56EB5017FULL, 0xCF0BC552A2FFC732ULL, 0x1B307722123C119BULL, 
            0xA219272A0D3A27C3ULL, 0x1E37F05179DA5B8EULL, 0x0D16A9E711E15346ULL, 0xE63C276256740B13ULL, 
            0xA67ADA521A6DCA8BULL, 0x37CDE5B44BD4DC77ULL, 0x197C98EC904DF14FULL, 0xB9D6C3172B99CEB3ULL, 
            0x11A030567925C900ULL, 0x6098029378407A89ULL, 0x7F9CD4DFA1BC968BULL, 0x6780D8DE89707172ULL
        },
        {
            0x9BDDCBC31EF98FC8ULL, 0x91F69857F4BAD679ULL, 0x1444B19B0428AD0BULL, 0x1CC63820CDFDCF61ULL, 
            0x217BCD3B4FB6F510ULL, 0xE3E6AF44761027C7ULL, 0x41FDFE0A9DB9D3F0ULL, 0xDEAE9ABA26C414CDULL, 
            0xEE21E1C2DA428070ULL, 0xE2545A12C7E083FBULL, 0x4B32C6EE673C60BEULL, 0x93A75463CEF79A8FULL, 
            0xDFFA61321A88D106ULL, 0x0F47FBA43CDCBF7DULL, 0xBA6998CD13F539C3ULL, 0x74B38EEDB47A0749ULL, 
            0xACCA9B7522AC353FULL, 0x51BDF3AD31D5F468ULL, 0x1AFC87919A6E61A4ULL, 0x09F9DBFBC82170C6ULL, 
            0x5D2075DD367F4FDAULL, 0xDE8CE648DF627227ULL, 0x3A1192D32E612A5BULL, 0x60C705DAA9E6EE30ULL, 
            0x599D765FAA0367F3ULL, 0xC5E35760F1C02391ULL, 0x6C9DA5CCE812A74BULL, 0xEBA3D374DC860169ULL, 
            0x051F2A8322099E7DULL, 0x003F438A7D16AF84ULL, 0x8490F44397EFF272ULL, 0x1D3BABBCC99DADA8ULL
        },
        {
            0xA6BEF6F51E80A4A9ULL, 0x4B2000DCA9B31B5AULL, 0xE1F1F2E73BC6FE84ULL, 0xFF9F327BE754DFE8ULL, 
            0xD849365D956B5EACULL, 0xD2EB76D203B4571CULL, 0x02E9B5224A5D39F3ULL, 0xFF4D557AFB9610BDULL, 
            0x18298A41ACB0AEB0ULL, 0x6107EABB269CE016ULL, 0x6234BB6EC5022568ULL, 0xAF3A464392F60123ULL, 
            0x615CCCF924F3EC73ULL, 0x082DE9AC9C27D1CCULL, 0x30EB4BA62062D208ULL, 0x9D729746A5459C47ULL, 
            0xA1D368B10A6EE4F4ULL, 0x167F80316019A3A0ULL, 0x14D45CA528E8B5C3ULL, 0xF5BFD8BF2344406AULL, 
            0x3555CF7BD91BA8C0ULL, 0xE59A2B1A8A04166DULL, 0xDF113621DFE01E29ULL, 0xEE3AA2EBFC58770AULL, 
            0x1EA94EE08F0929AAULL, 0x0A5FD55631ADFC89ULL, 0x2CBECD5C746FDC8FULL, 0x1840D068F6B011B2ULL, 
            0x4F1C0E0A1D614CA1ULL, 0xA0A71400B7E58EA4ULL, 0x362C44D65D8E4C14ULL, 0x61C622E1D565C795ULL
        },
        {
            0x0F355436E28FA127ULL, 0x8E0464F029C9B99EULL, 0x42B99D6DC724366DULL, 0x709AF04F1F00D719ULL, 
            0x95862A2E91DC52FDULL, 0x9BE67C7053A21DD2ULL, 0xF9E70AF073238C64ULL, 0xF12FFA97F1EF2BFBULL, 
            0x9B162B9171AD61E4ULL, 0xD11EA377193A7CB6ULL, 0xA599EAB09129CC9EULL, 0x94D221685745546EULL, 
            0x050DF7DA651CF6A5ULL, 0xA9E1B99E0D38CE20ULL, 0xBFB9DACEF9D21ECCULL, 0x4604A822997D2071ULL, 
            0x9A3AEEB294837AA5ULL, 0x22792B9E760C592DULL, 0x1ACC09B99C2222F4ULL, 0x505E807225D465FCULL, 
            0xB265EC82BE12FE05ULL, 0xC410FF540E1264A0ULL, 0x025C80EF367E8540ULL, 0x88C6A34082FE80E8ULL, 
            0x56FCC22B238C09D2ULL, 0x49C5AA56BDAA7510ULL, 0x6ACA580D4C1B9A86ULL, 0xE9AB04D52BC1C999ULL, 
            0x4308DC4681A1771AULL, 0x984C6117CAD16488ULL, 0xE6E2D5A47448F0EAULL, 0x2A4752D9C9324F23ULL
        },
        {
            0x846D87305B23F4FFULL, 0x1F1417A34994A64CULL, 0xDAA91DCDFCA510F9ULL, 0x6536E9A5E7AEFC1BULL, 
            0xC5310C776DCFFC0EULL, 0xFD77C114E4C63FFEULL, 0xAD7598DF0A00A8DDULL, 0x8B3822E44A12B4B9ULL, 
            0xD3042576F94779ACULL, 0xFBBA21DE4651DA98ULL, 0x7E5E8186E616E599ULL, 0xC022EF3F8B7BDA41ULL, 
            0x5AE377505D1C3CE5ULL, 0x2E5B91EC34EF029EULL, 0xE8A5A8B4B013AD48ULL, 0xD6953782B0799EAFULL, 
            0x4F7B6DFAD0DD5081ULL, 0x6B75C97EFAE69526ULL, 0xE35F36EF1842305CULL, 0x95AC3B091F419B17ULL, 
            0xB42CA10AC1D42B75ULL, 0xD54BD997809D7CE5ULL, 0x6DDCF2BDC37FF9B9ULL, 0xC6127DD83AB98332ULL, 
            0x3760FA3F6624520AULL, 0x6809E236D85AE7E2ULL, 0x403D59C06280436EULL, 0x908CB8FF7A588682ULL, 
            0x03C64CD532C8107AULL, 0xC87CC1621833B6EBULL, 0xB3D07ACDDC48A1D5ULL, 0x121B060EE9A08893ULL
        }
    },
    {
        {
            0x0F3956DF8E691F60ULL, 0x0214D88739813AD9ULL, 0x935D79245EA108AFULL, 0x23F5331F0798CD3EULL, 
            0x9AFB757C7F720C98ULL, 0xAD601D000BD9BEF6ULL, 0xFC69B3160FF91E52ULL, 0x17886193B0339F72ULL, 
            0x55208A5B32497282ULL, 0x9F798A1E6247EABDULL, 0xD7796B3413DC5813ULL, 0xEE2D5A576F2B49BFULL, 
            0x701D75714EA3A42CULL, 0x2BD05374EBB26131ULL, 0x6ECEB911415847BCULL, 0xB166CE3A11279BD3ULL, 
            0xF8A1C8481B0F3D55ULL, 0x965846F399FDB9A7ULL, 0x64C491ED509657A5ULL, 0x311F6EC08C375656ULL, 
            0xF17A823A502007AEULL, 0x105CE7E687E801ECULL, 0x55F72F10785E76C2ULL, 0xDF4C2829C218D5ACULL, 
            0x12CCA89ADB36C586ULL, 0x8F52D166EA4FCA04ULL, 0x0CC3A779140781C6ULL, 0x85ECE71ADA8FB1D8ULL, 
            0xA7BF9FB8F3032D28ULL, 0x9D4758F89B5797A9ULL, 0x6FEFD1DBF8BC699BULL, 0xFE9CF395D53E59BFULL
        },
        {
            0xE4FB6AE4008A0688ULL, 0xD1742CF28B2AE2B2ULL, 0xE5771CA3DB7A8970ULL, 0x6017E8B824579CE1ULL, 
            0xC38F16C96217857AULL, 0xD7BD7F643CE7CA16ULL, 0xFF0622D3CCA12537ULL, 0xBD0C8F4A969964B8ULL, 
            0xC4FE6497A48ECEF9ULL, 0xFD0DC92255F8AD3DULL, 0xD32060695A481FBCULL, 0x64CCAEE4E95A04CBULL, 
            0x0358D5621599E339ULL, 0xAEBDB0CD5DE06A3EULL, 0xD227E312E4D28642ULL, 0x10F9C60322AF3936ULL, 
            0xE84F23E21C22324DULL, 0x36F5EA0A5D3DBDB9ULL, 0x8855494215D9C52CULL, 0x7636C2BF9D012D8CULL, 
            0x6670BB0C47BA8BF9ULL, 0xE0FB4846511B5749ULL, 0x7E6CE0E64F4ADC22ULL, 0x41603E9B43126403ULL, 
            0xCF2D80B8D352BBC4ULL, 0x240CEBB919908065ULL, 0x54CA560DFA38DA26ULL, 0x015A35E6267A7FDAULL, 
            0x4E058B13F1445946ULL, 0x4A867018534DFB72ULL, 0x4D7D8D26CBD51ABFULL, 0xBC2CC7AB6C73952AULL
        },
        {
            0xB54D3E25ED3A4606ULL, 0x87C796FA3E338C9CULL, 0xBE351D4D32F91D9EULL, 0xF67575F1312E8612ULL, 
            0x56C1D228C6D45F09ULL, 0x44EA2E21D40B3808ULL, 0x5A4DA563130160FAULL, 0x98712D39BC54EBE3ULL, 
            0xE13E2EA0A0C31E5AULL, 0xC52B191A8036C1BDULL, 0xEC35C2A175A9647BULL, 0x4A62FEF2C12D1519ULL, 
            0xA42DC11BC4BBB919ULL, 0x36BA6BD687CBD631ULL, 0x6BEA1BDC61A444BEULL, 0x5C44AF36DC0EC212ULL, 
            0xE41286872408F743ULL, 0x72CCD07A00D40EB3ULL, 0x4D2D5F3684BDF837ULL, 0xF357F254C3441AB3ULL, 
            0x616C01508851E7E7ULL, 0xA1C6DBDA7563FD30ULL, 0xF26813E7D17EA1D4ULL, 0x2C600D5ED2D015F4ULL, 
            0xF769FCDBCED667A0ULL, 0x429240991BBAD795ULL, 0x97293D403AE1C87DULL, 0xBF04D6896B94C0C3ULL, 
            0x7FDAA31967DAA40CULL, 0x0172D063FCE9CCC9ULL, 0x7863C49B05EA1F59ULL, 0x706B3A22A1D5F229ULL
        },
        {
            0xF6B27DC1F4BDE221ULL, 0xEC8C1C2C8D9A83C5ULL, 0xF7BC7A40B8E92C6FULL, 0x715BC5CADDA594E1ULL, 
            0x61C478C3EE21DD2DULL, 0x7F90DE3280AC4A3CULL, 0xB0166EBDD512464BULL, 0x7538AC87A3887609ULL, 
            0x90472B218CDBEB9BULL, 0x903E3AB3F4461662ULL, 0xF1E569C6096AA94AULL, 0xAF81C4725AAC1D9BULL, 
            0xB2C1E68981F7B2A8ULL, 0x17A69D9A431F0FAAULL, 0x2604126CB817B32DULL, 0xE1745DCAB50B79FFULL, 
            0xC57921C4752BBE99ULL, 0xCF84B3E98FD64127ULL, 0x79ED32440C315281ULL, 0x68384200725AAF5DULL, 
            0xD98515D2B1A971A0ULL, 0xCE9A9406631D1BE9ULL, 0x8EAA16B377111AEFULL, 0xB894DFD8C4E8156FULL, 
            0x42B8F84CB24570EDULL, 0x6EF006822BF05345ULL, 0x9ED381A367F3E42DULL, 0xF55C027DF6477E81ULL, 
            0x1883B1595C6FFA89ULL, 0xCD051207C3B48FE4ULL, 0x64657EF2B57C1F00ULL, 0x61DD66256D6346F4ULL
        },
        {
            0x65E1D3A02BEAD010ULL, 0xCAB768B3B0F6733FULL, 0xBB68316C4A0DBB61ULL, 0x84B68FBCED25F738ULL, 
            0x2E56696D5D2DC2AEULL, 0xF083A65BCA643DE3ULL, 0xE53CDABDC7808599ULL, 0x078FEA04AE6D3A97ULL, 
            0x0681239299FFA79AULL, 0xC6B40294E92D2C44ULL, 0xB0F92FEC22AED7B3ULL, 0xCBEC9258F8517424ULL, 
            0x33D8D03118B1E3DFULL, 0xFF0A8AA99FF9872CULL, 0xC239C99A47F6DF5DULL, 0x8C3157BD79C09D9DULL, 
            0x9565E65D831E593BULL, 0x0DED37C3F028AA9AULL, 0x94ED482540912B2AULL, 0xA5AC1C1161B52BAAULL, 
            0xEA05E63F53799419ULL, 0x2B2CD183F6E4738CULL, 0x2242F600AB15CB13ULL, 0x8D11A392F7CA9E96ULL, 
            0x22148A6F20F51F21ULL, 0x441036AB046D9C28ULL, 0x96A24F773619007CULL, 0xAB7BDAF9CEA1215FULL, 
            0xD2DA58905EAC33B5ULL, 0xB01B11C825BE6FA2ULL, 0x9BDD97B025DD0F42ULL, 0x1086F8D5227CF349ULL
        },
        {
            0x02E96C09A1C31668ULL, 0x4DBFE25539D168DDULL, 0xA78D8D35C944CF3DULL, 0xB66A1AF26333A6A4ULL, 
            0x9CFC5DB9FA5308F4ULL, 0xCC132652A4E6660CULL, 0xAF415712EF34EEEFULL, 0x6CC620467D0374C5ULL, 
            0xA050E09354094C79ULL, 0x9AE91C05EED8B288ULL, 0x36E1130ADD162F64ULL, 0xEBB9E88E68D81E37ULL, 
            0x5E63FB853F14959BULL, 0xC18ADDAA58CCFEDAULL, 0x2985DB8B4854E78BULL, 0x5CBEA4C6C2E32A1EULL, 
            0x898D3E04AF4DD850ULL, 0xA0251E0BFAC8662FULL, 0xCCBC136009534420ULL, 0x804E3C3F6F320F91ULL, 
            0xAF15FA27BFB57557ULL, 0x14BBE634B9D2258EULL, 0x399807564AE054F7ULL, 0xBAE289E8D0E32360ULL, 
            0xE1D868CEDBBE4A59ULL, 0xA6D814BA17423F62ULL, 0x1E4CE076A203926DULL, 0x65804836961E9FCBULL, 
            0x53A03F82D415A3A0ULL, 0xFA5A6EA8D10098CBULL, 0x37FCBC88E3EA875FULL, 0xF8B2D2361A3FF46DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseEConstants = {
    0xC230B0FEF7620848ULL,
    0xB0CCAB7C5937A62DULL,
    0xDD023C20578C88B7ULL,
    0xC230B0FEF7620848ULL,
    0xB0CCAB7C5937A62DULL,
    0xDD023C20578C88B7ULL,
    0x6ED83ABC4B10E790ULL,
    0xA5242F612ED535EAULL,
    0x74,
    0xC2,
    0x77,
    0xC4,
    0x77,
    0x57,
    0x76,
    0xC0
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseFSalts = {
    {
        {
            0x64B9E8630278AC8AULL, 0x68541811972546D0ULL, 0x700D926ED14FED76ULL, 0x3E25DEBDC30C2B36ULL, 
            0xCEE193F1C24D3961ULL, 0x73819A179C0CCB5BULL, 0xE6F53607F0BFA85CULL, 0x4DD77031226DE2CEULL, 
            0x4C9B2539163A4183ULL, 0x41CF7EE423555D34ULL, 0x786987B284A4288FULL, 0x7F5A451DCC52CEABULL, 
            0x99270546E990251FULL, 0x8141185E9C825231ULL, 0xBC4A1FAA10DA0007ULL, 0x8F257E3B41954074ULL, 
            0xEECFE3D520F0BE22ULL, 0x507030E9C3467717ULL, 0x30FAF7A7BB3E19FCULL, 0xF148DD02B1C1ACD3ULL, 
            0xFF242D8BF38BBBAEULL, 0x62ED6F80AA4B0953ULL, 0xA52B53F8AB485DC2ULL, 0x35CD74B8C057F2D9ULL, 
            0x0DA10F2AE6DF12A6ULL, 0x9F6B59ED06BE0832ULL, 0x57AEBC8A3F60D164ULL, 0x744C5BDB94A37E9DULL, 
            0xF42911DF63B50091ULL, 0x340C23627DBDBBB7ULL, 0xEA31EFAC47E16103ULL, 0xBDAF5C2CE9901C73ULL
        },
        {
            0x7FDCE5FC29FD4C3DULL, 0x4DCDDB89E274048AULL, 0x02E15C72F0EB666EULL, 0x7187DD1A88A48321ULL, 
            0xB84935626DAE2F32ULL, 0x3715CBA57AC691EEULL, 0xB3562DA4B5A6D655ULL, 0xA879679079A3C427ULL, 
            0x982FBF8782C2D3CCULL, 0x933855CFD8EB8106ULL, 0x5A1E6CA00309511AULL, 0x621D11BBA32826D9ULL, 
            0xAFF59D769C14AFA9ULL, 0x700063F4A654E0ECULL, 0x9966F8D561396C3BULL, 0x25F0AB9856FA33C7ULL, 
            0xF717830029CD5586ULL, 0x1B6F21CBF9125F10ULL, 0xC12BFF4644EB2FF0ULL, 0x0164CC3F9D787395ULL, 
            0x85E4BA80835642A1ULL, 0xD8D2C9BBBB79728CULL, 0x5FDB6DCA951FF12BULL, 0x17047F6731AD4529ULL, 
            0xD367B481E36AFC3CULL, 0xA504770C59026736ULL, 0x5F2A473D5DD32C97ULL, 0x5B3AC85EBB76DEE6ULL, 
            0xACCF1A957009F4BDULL, 0x0E7CA7D22F7B8119ULL, 0x4B6DCAD0CA0BEC3FULL, 0x302218858F03E5BDULL
        },
        {
            0x8E280141FBE4CB0BULL, 0xA94AD4F7BE6AF6DEULL, 0x03043CA0A1E39970ULL, 0x2BDD3285778D94B6ULL, 
            0xAE561897C51A6B74ULL, 0xD793A0CAB2E98A26ULL, 0xCBB84158EB180D65ULL, 0x59790137A24F83E2ULL, 
            0xDD485A1A563FFD33ULL, 0x966337B364BF205EULL, 0x3C992E4DB85CED2DULL, 0x6BB2C1771A99CAD1ULL, 
            0xABA4988525352B37ULL, 0x813D88C32470CD65ULL, 0xAC1AEB74B9BC0DD0ULL, 0x11773E2B94712BF8ULL, 
            0x316AC9490224911AULL, 0xD206928E85BF6A4FULL, 0x7F7A993772571244ULL, 0x2A1BAD5C9D6AC27EULL, 
            0xAAD4AFEF85404B17ULL, 0xAA6533AFD5DAE13BULL, 0x4AA76CBF75117D5DULL, 0xADEECC6313DB7F13ULL, 
            0xDC279FC037C599FDULL, 0x8E2E9EEC7C9AB1E4ULL, 0xBA0FB37734830F8FULL, 0xA4A4821A0654BE69ULL, 
            0xF02704AA0784EBBEULL, 0xD8E75D202459BB58ULL, 0x206706ADB6E1C713ULL, 0xD8506B4EF7EFC87AULL
        },
        {
            0x135C5FEF68733CAFULL, 0xCC309FA35E962B3DULL, 0xD3BCF919DEDFAC4AULL, 0x7EC388D5E6A3331CULL, 
            0x2D9FA1AB3B3802BAULL, 0x39C0274C282124BFULL, 0x5D3CF3A785DA4627ULL, 0x93A959922A35F002ULL, 
            0x6282605D37D19FBEULL, 0xF00A0CBB51EEE7C1ULL, 0x9134569E10849093ULL, 0x03503C7B2026ADB4ULL, 
            0x44A4BC68511F6602ULL, 0xC804F909B4B17A0FULL, 0xA3D6ADA9E7F381E2ULL, 0xAA6A470DD5A144EFULL, 
            0x0E64BAC23E65C18EULL, 0xBD67FA0CB17E5DA9ULL, 0xD2D8160C340BF29FULL, 0xF275C7BD82A0BF8DULL, 
            0x676D56610FFCAD67ULL, 0x0BDA25C8DBF5DE2EULL, 0xFB8BFC24E99914FFULL, 0x08D52E78F42E0589ULL, 
            0x3E4612E6B9004F68ULL, 0x83CDF996C7F12FB5ULL, 0xE9E44E6C32C6A29BULL, 0xA8ECA0971DB5A9E8ULL, 
            0x943F30B158B8F4AAULL, 0x8C93066D5166FBC8ULL, 0x1D46E9E3DCFBA2EBULL, 0xC0EF7661A88FF27FULL
        },
        {
            0x13A83861AFCB0F8EULL, 0xBEB3DBFF7DB41B67ULL, 0x73DFD974223D4A31ULL, 0x74869D10DBDFC875ULL, 
            0xDB06938B8D684B5DULL, 0xFF3B40A2A9266424ULL, 0x4F802FD7B5E2D67DULL, 0x698DB946D86C9A8EULL, 
            0xB6CEFD8079B3F09EULL, 0x44B63E3DBC29EF98ULL, 0xB2B87B9BE38A5E66ULL, 0x0883ACCADD7AB8F6ULL, 
            0xD1F22D6991CBEB58ULL, 0xDC0803C43268B66CULL, 0xF51461072CEFAB1FULL, 0x750C5752B1496F83ULL, 
            0x535DA1D36ACDB7CDULL, 0xB086B555EC48BED0ULL, 0x3C264792CF611155ULL, 0xBF104B6EA9B90225ULL, 
            0x9517FE3D39D59080ULL, 0x1629527972AE2B2FULL, 0x0D8B0536000A521CULL, 0x9E9534ED84E9779CULL, 
            0x0EF76E9E61671BF9ULL, 0x7C036D81467964D3ULL, 0x7C95A76E8495939DULL, 0xEB144218CFBBE0A0ULL, 
            0x1F2FE1F1C7AD4704ULL, 0x8CCB2E3DAA1930CBULL, 0x7C6520DF48CCDE8CULL, 0xBD2E878B6D259DAEULL
        },
        {
            0xF37BA0C670915AF0ULL, 0x8169F802EBE668A9ULL, 0xF78156572BC2964AULL, 0xF9C2772B9BCC874CULL, 
            0x3CE4C9951A115612ULL, 0xDB87F66DEC6E4879ULL, 0x7452A5E4CB6C5A25ULL, 0x40C89655EDBB4ED5ULL, 
            0x82A2CAB794F011F3ULL, 0x732E1C4829EB5BFFULL, 0x0951EDF66A132FE1ULL, 0xB013FED951EB240EULL, 
            0x60EDDDAC33E245F0ULL, 0x24E1F811D399D177ULL, 0x319900EFF52F3E85ULL, 0xF5C5CE1BADA53B0EULL, 
            0x1995E97B537173A4ULL, 0x30D156CA63CB757AULL, 0x02DE8A5E35C51AC0ULL, 0x399F2FA3BD90D446ULL, 
            0x4A65F58DDDBF28C5ULL, 0x29D4D294F351B4DFULL, 0x1427466B55989EDBULL, 0x6D0AC41728C5F63AULL, 
            0x5CE4495BDE821E23ULL, 0x720097FE028EA86EULL, 0xE3C8B98CAAA4599EULL, 0xE80585BD18D0DBE2ULL, 
            0x3993E1DE3B5D559EULL, 0x1327AA3FA296BD24ULL, 0xD394D1B077B8962EULL, 0xBF2D906EB8FEF148ULL
        }
    },
    {
        {
            0xA035E6991727DB58ULL, 0x345542C6B0A41A37ULL, 0xB778C515C81D7747ULL, 0xBC8D03682B136761ULL, 
            0xAF269B3D98421922ULL, 0xF153BE4D6F91D250ULL, 0xE583734AF6D8CF7FULL, 0x12D2AEC0BB70CC33ULL, 
            0x5FAC560CFBD5147CULL, 0x7922D86E2DDAD42EULL, 0x7DAA71DC31A84DF6ULL, 0x5C8938B776AC0BE9ULL, 
            0xABA9E4A167F81D00ULL, 0x81764984E7A5E7BAULL, 0x682A61F00A8739DFULL, 0x9230198BA291E6BAULL, 
            0x99B2DFD94370F182ULL, 0x3252E1F9D141578EULL, 0x7A585BB3B9F4937EULL, 0x40B4B721551408C7ULL, 
            0x1CE9BFA10FE3CE47ULL, 0x579A59992A6ABF65ULL, 0xE2C48241E71454CAULL, 0x5CD541699A9BBBC3ULL, 
            0x4C096303D31EA2E1ULL, 0x26B3271DFCDA79FFULL, 0x087EE4B7F50AFC6AULL, 0x2660EEF489A15CECULL, 
            0xE6D8CBBFDF392BA6ULL, 0x10A7AE6214762E41ULL, 0x782BB664412C7DBFULL, 0xB85950C2CFF81171ULL
        },
        {
            0xE58FF40B7ABA9D4AULL, 0xAC921767A26A1EC6ULL, 0xD13095364751C0A5ULL, 0xA92C01792F635C0EULL, 
            0x78983B2FBB2F99A4ULL, 0xFECF2BE4D4A304BAULL, 0x8BDF8796298FF9D6ULL, 0x4418A294315B8997ULL, 
            0x3D2D2FF7BCA9D06AULL, 0xB83F07C48767E0F7ULL, 0xACC2EE806BB2DA11ULL, 0x01933615DB0EE21DULL, 
            0x411AB89D5CA1503CULL, 0x0FC9E05EC7ADDF2CULL, 0x7C6598F44D9B875EULL, 0x90A52699726002A4ULL, 
            0xFCECEBF792341AF0ULL, 0xAC4EB4A1B08518CFULL, 0x9210288DD79E3E5DULL, 0x184BB71B7AAA1C6FULL, 
            0x32B2B579F94630E9ULL, 0x297C743E9C4A21B9ULL, 0x7EBD6C4447FFE74AULL, 0xA79AC241B351B23FULL, 
            0x631945490192569CULL, 0xB65D4AC103C83056ULL, 0xF4DB0C9861A98A07ULL, 0x549C4AE0F8822815ULL, 
            0x6D495E9ADCAA9528ULL, 0xED6ED03CC5914F6EULL, 0x4F4BF6D1C0700230ULL, 0x117FFFE4BEDCBD0DULL
        },
        {
            0x3311FAD37AF4C3D3ULL, 0x79978C0D409DB781ULL, 0xAF04C1D384C169A2ULL, 0x6E73371CB544B88CULL, 
            0xD81BD3E92B12099FULL, 0x1FD20AC7B575B897ULL, 0x3B23FED7EAAAA635ULL, 0x1CC9F4CF90C9BE04ULL, 
            0xB34D6FD7E34130C0ULL, 0xDF7438D8ABBC1219ULL, 0xF6EDC35BDA9BAF02ULL, 0xECAE61E688B6BB5EULL, 
            0x8C86086BFA836874ULL, 0xD4F609971F25A83AULL, 0x62319CDA2DE01627ULL, 0x49DD88C5604A7CDDULL, 
            0x574E3EE5208ED8E9ULL, 0x97A122422C3FBFF5ULL, 0x0CE0E32D3E31426BULL, 0x34D40B84F1FE6D66ULL, 
            0xFAEAEA2C41CFF493ULL, 0x1846BC8194D1129EULL, 0x050D4AFDBD543F9CULL, 0xF766A6A31E0717FAULL, 
            0x1846624833148F00ULL, 0x8DBFA0C2AD0F239EULL, 0x2F897F32C41F8623ULL, 0x04BDF764CE653D12ULL, 
            0x3B83797B35CB0107ULL, 0xFF4063D6A3EF4CBDULL, 0xD15B38F98475BA9DULL, 0xFD31E9A93F7D47D1ULL
        },
        {
            0x4922495B1F365476ULL, 0xCEC68FDAD031AD7DULL, 0x1EA3E33BB4AA2150ULL, 0x004C37BD19720E2AULL, 
            0x56B93216DE187926ULL, 0x370C242D88A7E050ULL, 0x248731DA0412527BULL, 0xBFB9477656858C45ULL, 
            0x315C75A67C6EA8A9ULL, 0xB3B317AEAF0CD667ULL, 0x0F589B57EF3733E0ULL, 0xBB5F1FBE2D23E7E6ULL, 
            0xFB7220B97DAF098FULL, 0x586F2CAC68A6D714ULL, 0x5C41D41BE85614C4ULL, 0x22D81CEFDFD81CF2ULL, 
            0xD0BADC3F0768DF79ULL, 0xF4BADA7E8FC97740ULL, 0x9F560403040E9C0BULL, 0x3592A83E0A46E8D1ULL, 
            0xD7F81EECAD9C1EC1ULL, 0x7018D0AA52D751E4ULL, 0x67B1B9705B59BFF6ULL, 0xD63E93C188CC6B24ULL, 
            0xDBF73481D1927F70ULL, 0xEAAFFE4B2E7AF39AULL, 0xDA28C8C58E8487DAULL, 0xC7ECA31216DA9765ULL, 
            0x58ABBF8D1855998AULL, 0xED54DFC31317BB64ULL, 0xEED16B5D4A871B8DULL, 0x4D75D352F070AE65ULL
        },
        {
            0xD73F4B912C6501B1ULL, 0xD6C2A7E14F9AB745ULL, 0x8BB05CCC3C98613BULL, 0xAA4A02A691DA85FEULL, 
            0x61345EFF738C00ECULL, 0x7962601BAED01BA7ULL, 0x749E4F41AEC4F74DULL, 0xAABF1D90430F5481ULL, 
            0xECCFBE415993236DULL, 0x52B9A0A8E0449076ULL, 0x9C75F5636E0BFF84ULL, 0xABC9251E1CDBC4FFULL, 
            0x92463C26CDE8A44BULL, 0x26362CC5D51D4339ULL, 0x8F49D14D1E4EC404ULL, 0xFAE76F2FEC377811ULL, 
            0xC7AFABFDA4978347ULL, 0xE4194FEA980DE291ULL, 0x38FD76D6B9BB6511ULL, 0x6F0880DB30E9B182ULL, 
            0x9A07FDFCF1124AE3ULL, 0x4C1C313A0BBFD59DULL, 0xE1F04B022B2EAB44ULL, 0xB5D23CA15EC7053DULL, 
            0x2D64FF4BD3BAC1E3ULL, 0x29802FBB3E82C73DULL, 0x9F6CF91361199B3FULL, 0x86C897610941E013ULL, 
            0x05F812B9120D4EE9ULL, 0x313E73A59E9ADC69ULL, 0x205A6A53BB699ADFULL, 0xFA99D5BD88816207ULL
        },
        {
            0x3BCB6920CF5B596CULL, 0x8F43BD4BE58DECE9ULL, 0xEE40A4A0FD57987AULL, 0xE3B53522DA4991F5ULL, 
            0x0FAD41964374AD57ULL, 0xEA57FF8091B9B9CFULL, 0x5247E13B6B9BEE2BULL, 0x5C983673E0F4A1E6ULL, 
            0x1E8BB4875B9389A7ULL, 0x9ABC0397AE383FE7ULL, 0xF421DA9AEFCD2092ULL, 0xE5D14B8A3D2ADBA5ULL, 
            0xDC2697370CB2FC88ULL, 0x22893DB6EBCB6B00ULL, 0x176CA2D78B626C3FULL, 0x92FFDA7F7A689B88ULL, 
            0xD238E67CE75D7A78ULL, 0x7C5AA483D2A219DCULL, 0xBFB1749591E3DA0AULL, 0x8637EA5EA0B6FD01ULL, 
            0x0A44B7DB66CE21ECULL, 0x2D68CB58455F5E5BULL, 0x7E78CD48AD999817ULL, 0x2D99E35FB2876FDDULL, 
            0xB73ECE74D3F56881ULL, 0x8EC2240A930DC6CBULL, 0xA2F72C5BE50DEF72ULL, 0xF479B61F4B1C84A2ULL, 
            0xAF64363AB078AD0AULL, 0xE787B6A60A4816CBULL, 0x9C48E1DC5E3B5AF2ULL, 0xAEABA19C91D8E2C9ULL
        }
    },
    {
        {
            0xA1ECD748B37C4CCAULL, 0x33A152EAF5150276ULL, 0xF3C5A3433E70761AULL, 0x31EC28DFC0A12DFFULL, 
            0x6D640BEF1EE849C9ULL, 0xC16AE9460E0AB2C9ULL, 0x2D84C751AC86628DULL, 0xB3CBBF602EF768E4ULL, 
            0x05D859EE6DA99F9FULL, 0x56CA2ECEC22C2DAFULL, 0x1060C680E65B4B12ULL, 0xB769EC6E7AC55645ULL, 
            0x18F2DD7211406037ULL, 0xF55C4583BCD564EAULL, 0xC9220F8C45F9F81DULL, 0x6AF8BD1A015DA5DBULL, 
            0x2DEDC2D15018B89DULL, 0x6943F479FC7FB8A4ULL, 0xD9EF3DBF8D1E63C6ULL, 0x6770E57D01ED65DBULL, 
            0x7A814CA56F3BAB61ULL, 0x88B1E2168221DDE4ULL, 0x995C26935301550CULL, 0x35E8213639624A94ULL, 
            0xF1CACCBF24E24AE5ULL, 0x98461180E8181B6EULL, 0xB0898ABDA51721C4ULL, 0xA74F526C9550348AULL, 
            0xD171A97234111EDCULL, 0x0CD87D20A9AC6FF0ULL, 0x6B2553C9CA9A8E1EULL, 0x728F8B7B82F2E314ULL
        },
        {
            0xA0BEA1406947C9C7ULL, 0x2E15E56A2E9635D8ULL, 0xF26751407BE5BBD0ULL, 0x664A69AA45A2FF95ULL, 
            0xE58EE9D988251ECBULL, 0x1C626553A875F642ULL, 0xB762CCBD1638487AULL, 0x6BCA645CAB478DE5ULL, 
            0x9E7E461AE5C82E19ULL, 0x5454AA2F83AA49A1ULL, 0xB0EBD50955F71AF4ULL, 0x6835C6B05075DEEEULL, 
            0xA235EE49FF683806ULL, 0x27062E4C69563FCAULL, 0x2DA5115DCA3402E3ULL, 0x4AB7026E7A36B169ULL, 
            0x3CC787558EAE711CULL, 0x19482677B7CC6BC4ULL, 0xE94AFA2D1F041F30ULL, 0xAEAE25E57215EBFEULL, 
            0xD7CDF85FE0F8C986ULL, 0x90414B0E4EE8C9F2ULL, 0xE8F79E5E09BEC7A3ULL, 0xD2769AAD362BAA36ULL, 
            0xE5B2F42EB99556DCULL, 0xDFE7F2B555574D0DULL, 0xE5597F2FD9D66D20ULL, 0xDF659A06D0C9C0E3ULL, 
            0x53E0CDFD2B716E6FULL, 0xA7DB28B45A749028ULL, 0xD9B8DD42EFF1B30FULL, 0xF540F9273FA2D05FULL
        },
        {
            0x4933E8031B152E24ULL, 0x46A2D79E321DE369ULL, 0x68817BC9E55D0145ULL, 0x97702C953ADB0009ULL, 
            0x53782F8DD668674AULL, 0x25D2BDE1EF9E1F02ULL, 0x7288148E48AD126EULL, 0xB6CAA41C313D7641ULL, 
            0x1408BA299F5B5929ULL, 0x9ECEAB00910C5DAFULL, 0x638403A836E103E4ULL, 0xF6CC78B36E233E9FULL, 
            0x4AD9CAC577A00BDFULL, 0x45883F8333900DCCULL, 0x1E3FFC479A831920ULL, 0xAFFC920DD7C5F4EDULL, 
            0x6A67829F26292840ULL, 0xE1FA5DC9263B4AADULL, 0x767AC50FD8D53D3CULL, 0x2D15BF6422EBFE3CULL, 
            0x3121F397DC63193DULL, 0x939F98296A153F06ULL, 0xDC059382751FB383ULL, 0x8D886E40CA0F0EB2ULL, 
            0x0CFE100C29292AB6ULL, 0x9C1033246BADCB00ULL, 0xC23219BAFFEC4B82ULL, 0x82B905B383C2142CULL, 
            0x1C8C15312823A017ULL, 0xDC703591C5BED3A8ULL, 0x49EAA62727051A96ULL, 0xB6893AAB4DB7EC5BULL
        },
        {
            0x5966095F2CA99D44ULL, 0x53600D320EB8D7A2ULL, 0x0BF3B325263110D8ULL, 0x24387FAEE8F6217DULL, 
            0x396AB60A160CC7B2ULL, 0x0AD44D152EE242D3ULL, 0xB1C3A69F6E199032ULL, 0x70CFBD829F401192ULL, 
            0x5560E64EE4BA8C61ULL, 0xCC903F384F45506FULL, 0xC90281A4503BEACFULL, 0x88E4709A3A91B1F2ULL, 
            0x12BF4DF6EE63DBA0ULL, 0xD818D65487DAD4BDULL, 0x13468784A8C8C307ULL, 0x52A8555CBC0D2BF4ULL, 
            0x8252BE68DDF077D9ULL, 0xD1B23676549AB091ULL, 0x880862CE49149EC8ULL, 0x81D2338BD9C78F35ULL, 
            0xA2F44412E0EA2489ULL, 0xBFB653A1346C4234ULL, 0x9247D1C6BFCD0020ULL, 0xE50F83AAC405F709ULL, 
            0xEE91881FB0DB8B8FULL, 0x1D8F0BF8A65405B7ULL, 0x507676E188E3FB87ULL, 0x787D52058BE8E4AFULL, 
            0x0ADCFB109207E0E8ULL, 0x03C8CA95BE84015FULL, 0x117A32DCDF86CB6AULL, 0x25D65C1AAB734404ULL
        },
        {
            0x7CC7D9FC92E4EFFAULL, 0x4AF4882653A7EB0FULL, 0xF3A6E8896BB53688ULL, 0xE0FB0CF816000766ULL, 
            0xFDC393569C7E767BULL, 0xDA2C73C373975EAEULL, 0x2CF98662F98ED075ULL, 0x247FD752BEE60768ULL, 
            0x02EF159E3E497061ULL, 0x5534EE0F1BB95C7DULL, 0x41FEA531C91B4019ULL, 0x2285B3650007A39EULL, 
            0xBD8B58442BB45282ULL, 0xE2FFD0C852E49E83ULL, 0x913D12907C6BFB8DULL, 0x179F2DA4440F5B90ULL, 
            0x84C71BB004B95168ULL, 0xFD33DF4D8B39348EULL, 0xA38F7D88BB18CB38ULL, 0x376FD471DE8DACF3ULL, 
            0x83449AFCBEB41A9CULL, 0x21BD0C49400FFB2FULL, 0xF61E58EF6657D4ADULL, 0x0E8573087FE94437ULL, 
            0x79E9FF15578EAD74ULL, 0xAA9E2F20F20C0535ULL, 0x078078F8BD5052EEULL, 0x24BD19FB7E76D7BAULL, 
            0x5E1C2FDC6DAB73A8ULL, 0xC28EEF561B122884ULL, 0x35353F09C5CF1C75ULL, 0xEDC632C344A98522ULL
        },
        {
            0x8D8F868304670C88ULL, 0x5A8DCE0A4F70BE04ULL, 0x60B8CF7471E6AD8CULL, 0xABB6016DCC58B124ULL, 
            0x4E3090972DC7E7F6ULL, 0x16793B75D6D2B66BULL, 0x48D03AF9F1FE70A3ULL, 0x5B6C57DD3450A530ULL, 
            0x31F8832E725689CDULL, 0x8A9639D41D13DAF0ULL, 0x1426761F696487BFULL, 0x761D5C82F8137258ULL, 
            0xDC329321F762CCACULL, 0xFA0A4C75E0C7C2EDULL, 0x85D07D7C1AFDF508ULL, 0xC745D81436EA60A9ULL, 
            0x87F4EE3FD2125148ULL, 0x336C6630F885A756ULL, 0x5ACC64B8C9EB21B9ULL, 0xE87298A8D4A17CDBULL, 
            0x270860FDEF6BF1A4ULL, 0xCEDAE043D413CE76ULL, 0x8E7C88AB6D998988ULL, 0x6F97E42BD06FC995ULL, 
            0xDC96756338EFA86EULL, 0x152CEA4EC8366281ULL, 0x39C7D91565D82F32ULL, 0x6384FB4FB3012E86ULL, 
            0x54203EE51FFD46BFULL, 0x9B599FE78AE17691ULL, 0x614BCB73971E06DAULL, 0x182840B6C3DB634BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseFConstants = {
    0xAC92652A7DF7BFE8ULL,
    0x78BC942D0A012DF3ULL,
    0x1192D63115A9FA02ULL,
    0xAC92652A7DF7BFE8ULL,
    0x78BC942D0A012DF3ULL,
    0x1192D63115A9FA02ULL,
    0xC80F412A699C5D32ULL,
    0x5FDD219F2EBB53B5ULL,
    0x28,
    0x52,
    0x92,
    0xF5,
    0x75,
    0x07,
    0x36,
    0x55
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseGSalts = {
    {
        {
            0x4BD00304E7A96EE5ULL, 0x6835BF15CC3E7A8BULL, 0xB56271994305BF60ULL, 0xF3C83E1CBA4F7F2AULL, 
            0x0759EEEBF030F511ULL, 0x310C0187854BECC5ULL, 0x6B20FF42F36C4B74ULL, 0x5CEB7D4DFB42DD38ULL, 
            0xD72B6D12194B3539ULL, 0x37FD7E0E1BF77F70ULL, 0xD9B71BC2A636D120ULL, 0xD811F2075A29A957ULL, 
            0x5684012071B6E5BBULL, 0x5B0E6DF20E42312AULL, 0x0ED3DFEB37E47646ULL, 0xF3B6C84248A08957ULL, 
            0x3DACDD3C0F3952EAULL, 0x6A04CA1C677388B0ULL, 0x6E279513A949568FULL, 0x0ED030B6E65D3FD0ULL, 
            0x8F5F0566A5BB4ADEULL, 0x4DC24284FB6D3A89ULL, 0xF504C34A6906BEEDULL, 0x256B02D467719309ULL, 
            0x826A52E9F27872D2ULL, 0x5783E82A5A3C4F00ULL, 0x68FA4C845DEF42ABULL, 0x339C2C05BE402D3BULL, 
            0x0A5E81623D4D0D12ULL, 0xC7476DD2C6A850FCULL, 0xCE5CF391E482F6CCULL, 0xD949628E37FE38DCULL
        },
        {
            0x94DE4BEA38E0A5E6ULL, 0xC83B5E049153C501ULL, 0xEC2384514E151819ULL, 0x0BBA0FD1A985F3BDULL, 
            0x8805BB85CD52CDBDULL, 0x751617D92D1049DFULL, 0x5EA0B937ADFEC761ULL, 0xD387F68C2460DDA2ULL, 
            0xCB878DB42F68A7C2ULL, 0xCBDF10A9C3644FC0ULL, 0x2058F830EE109A05ULL, 0xBD5A792D229EB553ULL, 
            0xA39FAE9C81512697ULL, 0xC0B80BEB7319D9CBULL, 0x213D02EA37142684ULL, 0x21327D3CCD464F5BULL, 
            0x4E5FC7540A89496BULL, 0xF8343778A83B0695ULL, 0x6B58D7391F6FE331ULL, 0xD9A452A23354C2AAULL, 
            0x18D1CB22ED564ACAULL, 0x7F3D6F40CD23EF64ULL, 0x7B252640E6F87820ULL, 0x8DE51AFBD793DE4FULL, 
            0xE106FB6EB87A14D0ULL, 0x334EE6AD6E95F296ULL, 0x75FD7FB1718461E9ULL, 0xC32DCCC4B12C7A3BULL, 
            0x9EE87600C0254AB1ULL, 0xFA4A2B1C2DA3BD44ULL, 0xD1BD7E0FFD48769AULL, 0xAE16BFBD432BE2E8ULL
        },
        {
            0x085E7A20FA70F11EULL, 0x1F7AF775A984FF9AULL, 0x5F8242139D9824EFULL, 0x1793FB2FA5E5C990ULL, 
            0x1FB28D7C85CE9026ULL, 0x734B44B265F7CC61ULL, 0x37C3A235B7368598ULL, 0x8F4585BBBEC86845ULL, 
            0x5CF8B0D40E90515AULL, 0x6DDEB501032FCDFAULL, 0xCB0D99A6D7891A5BULL, 0x7AA14B9D07D52A22ULL, 
            0xA44AD390C66869D1ULL, 0xFB95E84BB1BDA555ULL, 0x65EF643E49E8538DULL, 0xFE75469B1470E569ULL, 
            0x5F5C5D1A343909DDULL, 0xB123EF49FF83B8D5ULL, 0x82E4584ADB01CA3AULL, 0xDA3616915AACEF1FULL, 
            0xEA7B85D41A3770D4ULL, 0x65066056AF4C75C3ULL, 0x1807995B2E4EBDFFULL, 0x6723EA9462F9D2CBULL, 
            0xF2E249F9DCA9B33CULL, 0x56A95C697F78555FULL, 0xCC0B025897A63DE1ULL, 0xCAF3D0BC59B48D67ULL, 
            0xD45EA208AABB7483ULL, 0x208AD21AD2B84021ULL, 0xF11DCFD752F140C0ULL, 0xD4BA557C2D154EDFULL
        },
        {
            0xDB6E759B3480A937ULL, 0x6649C824790C097AULL, 0x5B525721BBF7BE60ULL, 0x9547626058E97871ULL, 
            0x3AD715F34C6E620BULL, 0x8482C3BCE35A9344ULL, 0xA361BF1D53EE9732ULL, 0xC5DE8C02D66766C5ULL, 
            0x5B940FBCA0857310ULL, 0xB86022F998076A5EULL, 0x68275B634EBBB79CULL, 0x608F12E8CE03389CULL, 
            0xBBD6CF6A8836E634ULL, 0x022E0C64AF60F699ULL, 0x65694780FE9F189EULL, 0xE163C06F10949367ULL, 
            0x580467FD312F57F4ULL, 0xB3F040BF3CCE9621ULL, 0x90EB2DF7AFBCB79CULL, 0x059A17502730E774ULL, 
            0x67651EAC3667B580ULL, 0x8360FC66D1777B35ULL, 0xF5E720CEDA51A455ULL, 0x54AE428DE4B13852ULL, 
            0x80849CF4CEC58474ULL, 0xB4088BBA38305113ULL, 0x7E3F9CDD90FA8D31ULL, 0x3D4943CEC413CBCBULL, 
            0xE07E74E21396BAF7ULL, 0xC91DE988214BE190ULL, 0xFD030C66CEFBC2A0ULL, 0x9127B43C011CAB0FULL
        },
        {
            0xF14C1A6C45C6CE3BULL, 0x24E593A7F41B71A4ULL, 0x0F6B4E5F90DB5707ULL, 0x1218157F7FEC2445ULL, 
            0x337E05309F59D15AULL, 0x206D5D54C5A54C62ULL, 0x0078BCB0A918BC62ULL, 0x0ED071A59593392AULL, 
            0x464FE90A4C8994E6ULL, 0xDD81B43EF78669C0ULL, 0xC0F91AD74A5566D0ULL, 0x9DC2A74DF6CBB18AULL, 
            0x6936889125379EFBULL, 0x0517193112BA1008ULL, 0xDAD59493470B7354ULL, 0xA4A5850E51986414ULL, 
            0xC1F8B99E1680B21EULL, 0xB585ABCFF2617DCBULL, 0x423154D09758B838ULL, 0xA98B99BCB9CD5C4CULL, 
            0x613A3E887A5ACB62ULL, 0x4608497477EFEE88ULL, 0x430CF5D032EDCFA2ULL, 0x91B14E65E07B6AE4ULL, 
            0xC4E3513B2C4101D4ULL, 0x10E46B4645D7A32CULL, 0x66FEAE68DB8DA052ULL, 0x889FC63308557311ULL, 
            0x34C4EB0E9C3DEFFAULL, 0x7B68A70E7BFC1397ULL, 0xDD4C59AB01FFA32EULL, 0xD2F91474E16ED2FEULL
        },
        {
            0xC7ADCDFA46F25889ULL, 0xDE6CA2B6372E353BULL, 0x1C63C70AC06A3F12ULL, 0x73878820ADFEC9EDULL, 
            0xB6EF23E89D6D6EB7ULL, 0x42007515D32D2B7AULL, 0x8567AF91D0670C42ULL, 0xA744C1FF43FB70FDULL, 
            0x709855B5E3C184D9ULL, 0x6F247275232B5B77ULL, 0x6F9F96268DDDEF9EULL, 0x75C21EF689784B70ULL, 
            0x79ADAE768FA59AC0ULL, 0x2A59737212FB5326ULL, 0x46B1CD7ADEBB11BDULL, 0x0D8317E499A068BCULL, 
            0x0342E65A0A0FB9B9ULL, 0xF681EEA8AA5C6A91ULL, 0xD1C228D00E5A04ACULL, 0x544138350126001BULL, 
            0x1A4E050656D06C11ULL, 0x6C7A02E13C5981ECULL, 0x6B24FF5C06646201ULL, 0x1F4263E1285A1FBBULL, 
            0x5B5818A3136F61E4ULL, 0x1CCD8B34B14AE9F2ULL, 0x36211F6850E8024CULL, 0x44F6D9D8AE3E2FA8ULL, 
            0xC364670612BD6A44ULL, 0xB41F57C30806C760ULL, 0xFDB682F48172E898ULL, 0x542AA93DE15DCD3EULL
        }
    },
    {
        {
            0x407E28F1FF0FD23DULL, 0x8749ACBC3E7AAFADULL, 0x7AA9512285AB7F26ULL, 0xA928E22AB20D98A7ULL, 
            0xC78C8999D1791161ULL, 0x2DDA2897BC6020A0ULL, 0x716891CA80B2BA7BULL, 0x5551B0946D31F00DULL, 
            0x5FF1E99B397117C8ULL, 0x93266C7B7DBFD984ULL, 0xAE8993042863135BULL, 0x493E486D24A4AB37ULL, 
            0xE53F5E2C680D4739ULL, 0xDBCDE7ED68A9767AULL, 0x3B7B8B3C51CA3CAAULL, 0xE7028F3EE3A01AA6ULL, 
            0x3360A6FA0F387D99ULL, 0x2B56CFDB22BA30A9ULL, 0xE468A05E342EE2E4ULL, 0x742B051D130B3B86ULL, 
            0x7D36BAF5AB1496F1ULL, 0x9E6739D879687416ULL, 0x89944DC315A00B6CULL, 0x0974528B1B72E736ULL, 
            0x2DB05D84E2719C78ULL, 0x93465670443D8735ULL, 0xD69CA721D7ED1D05ULL, 0x308AAC2426810FFDULL, 
            0xA790E58AAC3399AFULL, 0xF2B98514D45AD64EULL, 0xF7A4D20A5E03880CULL, 0xFCBE70F032CE80D7ULL
        },
        {
            0x3CC6862571026FB1ULL, 0xFBE15F09C6319D6BULL, 0x52EE3AC26B72BC43ULL, 0x6F7DB189B7974272ULL, 
            0x65A2C4B28A43374DULL, 0xC126061E1AEEB0F7ULL, 0x57761C75F5882698ULL, 0xDDEF9E627FDFFAC9ULL, 
            0x6317F8D5583EEFAEULL, 0xEC0F9ED88034E318ULL, 0xF8C36FBA0422F3E1ULL, 0x9D8B02715C8C9C3BULL, 
            0x27355108DE867547ULL, 0x4B94B7B016A333F6ULL, 0x46CD4A3677963F0BULL, 0x780B8EE362B006F4ULL, 
            0xAA1500C0A75797ECULL, 0xC9BDA6CBF2D87EF9ULL, 0xD53F79083CBEC2E2ULL, 0x0646358B9B5E4DA9ULL, 
            0x4A70A9049A42435EULL, 0x772838C6FD6F7E99ULL, 0x5489524DA3EDCFF8ULL, 0x6B82A438B90B517FULL, 
            0x3B74834816E206A8ULL, 0xC5B927ECD28090D5ULL, 0xB903D3440F9A4D65ULL, 0xBAF3D2E9BBD716C5ULL, 
            0x87FD0A171910E247ULL, 0x5C89272C62F8F531ULL, 0x1742A7AA2956DBC3ULL, 0x1F56276CDFE165CAULL
        },
        {
            0xF6C2DCA96BC7A042ULL, 0xC049C63D048B225CULL, 0xA010905AE88AB881ULL, 0x7A0DD8AEA93AE960ULL, 
            0xB4216F47020E84ABULL, 0xEB5ABD026C1C5FBFULL, 0xD50F2010B4D9824DULL, 0x93198F4017C78AD5ULL, 
            0x0445B4696511D3FBULL, 0x0E4F85CA46000345ULL, 0x0504C0FB452750A4ULL, 0x3424F6656FB08A8CULL, 
            0x289B4C37796E66B7ULL, 0xD3A046E99A89DE00ULL, 0x3EDB375F5BB24539ULL, 0x1EC6E6840B1C6E39ULL, 
            0x9580F7362E144FAAULL, 0xF7143837EC4C35B7ULL, 0xA041E9DC016B4039ULL, 0x01BE9A3BDEBDEDB5ULL, 
            0x516DED15155BF54DULL, 0x2100FDCC3A98E771ULL, 0xE61347E6029ED925ULL, 0xC1BE8792C40FE579ULL, 
            0xADB2E8543378C48DULL, 0xAC91D0C212E44A55ULL, 0x22B3C9C780847A81ULL, 0x869BCDDAB5FC628FULL, 
            0x63CB8385DDC5476BULL, 0xE612E9A70FBCAB4AULL, 0xF6F400A6A28636C6ULL, 0x74FC165231F21D37ULL
        },
        {
            0xF65A31FAA2B48DDCULL, 0x67E094DD67BDFFF7ULL, 0xF67DC54B2C6EDD89ULL, 0x802308B479A5C0E5ULL, 
            0x92EE795784751994ULL, 0xDA3EE4F41B4C3E64ULL, 0x1BFAF2D772FAE5E2ULL, 0x4D80D97762355606ULL, 
            0xDF3FE875F5221CFEULL, 0x3A84BC37A3F32237ULL, 0x35B595A2504B2C1DULL, 0x1F7F612A80C3254BULL, 
            0xCE608DBE19F95531ULL, 0xA33B867171FE1EF3ULL, 0x4674AA9568267311ULL, 0xDC8FA75A05A58A89ULL, 
            0x31EDA6A9AA36FD30ULL, 0xE5D623B2EADD3FBCULL, 0x4E42016F8EBFAB9FULL, 0x00C3892911335AB8ULL, 
            0x23434A1CAAFFF8A7ULL, 0xC3498E7C25F17A14ULL, 0x1A4BB8E784F62AEAULL, 0x0E64282F9E8BA29AULL, 
            0xD104D0380D9EC057ULL, 0x46489F301647E14EULL, 0x732DA9F05A44C010ULL, 0xDE1CFE07BD4CA67CULL, 
            0x79301E9F43475850ULL, 0x3543CE3EC063D9E8ULL, 0xFDC139DA084144B9ULL, 0x494CA27E73F1479CULL
        },
        {
            0xB67D788ACAA7D6A2ULL, 0x50D03C66B398ECEFULL, 0x8096782948A18B5AULL, 0xF84CAB27EFE0D0D2ULL, 
            0xA7F2452C03A0E649ULL, 0xDE21CA3BCDEE0315ULL, 0x7F83BB04627CB0D1ULL, 0xDF22776E7942DBBBULL, 
            0x90F7C9C4C312F6EAULL, 0x0B6679730A313272ULL, 0xD53BAF8A06DD321FULL, 0x341D707EFABEC78FULL, 
            0x5BFD5EC6CADBEA88ULL, 0x245DC81A5EDBEAD8ULL, 0x2638236A1702285FULL, 0x004193B1BC364EDBULL, 
            0x65E479BDAAA10632ULL, 0x7D88517420AAF0BAULL, 0xBDAE875A068BB2C6ULL, 0xA43CBF1EFD074951ULL, 
            0xA76A6EFC610C548FULL, 0x88B506CF8D2A5551ULL, 0x1E154E3AB3D5BF4FULL, 0x0D51853EAC8A39D2ULL, 
            0x9453CF58300FEFC1ULL, 0xFBA0591ADBEE3667ULL, 0xA43EF4018158723BULL, 0xC7AD95822544FDF3ULL, 
            0x0B83DA500FC4739EULL, 0x32D96AE5914A91B1ULL, 0x634457E451F7A5FBULL, 0xC6632366C6CEFD5BULL
        },
        {
            0xFAE77C0F5479F748ULL, 0x6419D2D6D0683DE4ULL, 0x17D9677C24835D20ULL, 0xE9657902ECD6C353ULL, 
            0x0F9B34ED8B40C8C4ULL, 0x83B868FFD8C3FFF5ULL, 0xCD6933DA4755959EULL, 0x07BA0F0A87F2DF0EULL, 
            0x21E373D69B49CBB2ULL, 0x7D8A86ED21F0C705ULL, 0xFA1CD686DFECDE14ULL, 0x99BBED79BAC5B490ULL, 
            0xAA2486EA31464E62ULL, 0xA297E409D116EC43ULL, 0x2A8C7C94C53C702AULL, 0x524176C8B18172AFULL, 
            0x5C52ABAED58C5C14ULL, 0x8CC69D94A540B364ULL, 0xA09274E7A94D80BBULL, 0x4E2E45BF97FAC310ULL, 
            0xA8E99F3918A247B0ULL, 0xAA97B45B925DD1CDULL, 0x4A09B77EEFA8A47DULL, 0x0FCE56E985214F20ULL, 
            0xF21D1D76C9FE7374ULL, 0xB5A4D5A43FD8EA5FULL, 0xDF9B2F4F3D6FACB8ULL, 0x88BD901AF1DA3D97ULL, 
            0xB12AE6C601EEB49BULL, 0xB99A8EA5707AD19DULL, 0xDE346805D72AE331ULL, 0xDE5AC8AF91823555ULL
        }
    },
    {
        {
            0x9DCF36C30BADC454ULL, 0x10B08A5E3CFEC10CULL, 0x12CBB6D3DFA070A8ULL, 0xE6ABA8A540366818ULL, 
            0xD2C8D24A5E376FD4ULL, 0xE78FF31EF74000BBULL, 0x567A027054FDAB1AULL, 0xAC795858373390C7ULL, 
            0x35DA7E82DF5CAD5CULL, 0x6476FEBB8137E62DULL, 0x816C81808FDB01D3ULL, 0x85AAD8F66394AD98ULL, 
            0x5FED5BA66939187DULL, 0x4A631FDA0764C15EULL, 0x8F1769E12D61AD61ULL, 0x02D99D53766CA7A2ULL, 
            0xB6C65CE08CC95347ULL, 0xB86125671BDB2D7AULL, 0xCA838D9E88082CA2ULL, 0x2A174F422EB12E3CULL, 
            0x44219E30734426C5ULL, 0x241E181BAA28AB6FULL, 0x1DF453129C79CA2FULL, 0x0BEF2BFE2584C454ULL, 
            0xE271BB3FBC3F04FCULL, 0x0FB7481B27B7C5EAULL, 0x9131DCBAA6B0BDFDULL, 0xC5F43CFE6B766B52ULL, 
            0x66B6EE15F3144AFDULL, 0xF97F6E99B86D8536ULL, 0x71BB458CA196193BULL, 0xD3AE425F3BE11F48ULL
        },
        {
            0xA0FD64A39B2374DCULL, 0x0A13F553BB42DAACULL, 0x295D38BF1D5D4007ULL, 0xF76C380F816C6FFBULL, 
            0x7943C1E2E51B92D5ULL, 0xEB63E9AD18504565ULL, 0xBBCED1578A5085D9ULL, 0x2ABA91D411DA1D6EULL, 
            0x9A027F3BC2235E19ULL, 0x6924DACC095DCBF6ULL, 0x4522E6CFF4D61AA5ULL, 0x53A8EC4B16D7185DULL, 
            0xD5D9567EF2338802ULL, 0xFB8B706D31E067EAULL, 0xB8739937E531A7FDULL, 0x5D057F3945FF1587ULL, 
            0x3D3DDFA5813B78BCULL, 0xF46768275912163EULL, 0x663F868497DF8C37ULL, 0x701878AEB49747C2ULL, 
            0x7004477776D275BFULL, 0x33832DB4171AF814ULL, 0x4CC5FBF752121DE6ULL, 0xFD3C9337720CD9E6ULL, 
            0x86B51AC718D1C67FULL, 0x730C0B77FAE18995ULL, 0x3B119EA454C9F599ULL, 0xCF7DBB0A00B63E00ULL, 
            0x869B77853134D192ULL, 0xE562BE618E6FCCB1ULL, 0xFB98A88D174449EFULL, 0xDB45F4221B6DF221ULL
        },
        {
            0x595AFB324C2168FAULL, 0x07776A5EA5555D26ULL, 0x42807066A57A5D19ULL, 0x3E446B2CF7F755B4ULL, 
            0x8E34350B3984CF2DULL, 0xBFBB5CFC57128841ULL, 0xF61E293D4F56D9E7ULL, 0x754E4F058018D527ULL, 
            0x3D4118BC249BBB8CULL, 0x8F36DCDCF2EE5996ULL, 0xC868D800E92A88FBULL, 0xE4AAE2630F376C57ULL, 
            0x1F1961E61FACA911ULL, 0x748C78A9CC91F01DULL, 0x8137A4795FE75F88ULL, 0xE25F8168A344D40CULL, 
            0xA2A84ED95DDCA9FEULL, 0x80EF2395662093EBULL, 0x21A9F7F3863E0E00ULL, 0xB5063C0D0DA11693ULL, 
            0x40382592BD2E6C77ULL, 0xF452EAD1A0321928ULL, 0xDB4E9D5E6C9BF9BBULL, 0x0158AAF30D1C872BULL, 
            0x173AD124D1F53E2FULL, 0xAC1DA6028C89623AULL, 0x817EBA7E72999F10ULL, 0xFF6200FB74898B12ULL, 
            0x967C225C4702B1A4ULL, 0x60A8D1E5ED68FCD8ULL, 0xB3C9DDA19B4139D4ULL, 0x7EB0E6C2696E8BE8ULL
        },
        {
            0x0888B34038003248ULL, 0xD24BD69FF10F8601ULL, 0xBB0A70374E58DD21ULL, 0x9ABBB9A0ED4D5DC5ULL, 
            0x5954424D80569E8CULL, 0x7674A8E1FED67DC5ULL, 0xB71FE2BA9BEEF89DULL, 0xEFA40A40C6C65964ULL, 
            0x5FCCF523EA33DE8DULL, 0x347851D914246608ULL, 0x11A7B41B0D71F8F0ULL, 0x075391CE0F43F66EULL, 
            0x2F07B0476F34C6D9ULL, 0x8A5B6A0FC479107CULL, 0xCBFA8EBF1F58BE50ULL, 0xEDA662EF4B9C4B72ULL, 
            0xDE9EFC4194E90677ULL, 0xD8AB0ACE8D8F53AEULL, 0x9229DB7AD13881D1ULL, 0xB77DE4CC0F4B6C51ULL, 
            0xA4725EBE4E27A206ULL, 0x3800E2324ACC80B8ULL, 0xAB46EE458BA7F77BULL, 0xA82D2393D922B0D8ULL, 
            0xBD9F1625486B31ADULL, 0x2DDA948AB135CA39ULL, 0xA83B839FDB660C73ULL, 0xEE8C648152C28E09ULL, 
            0xB0388C7A05FCC82EULL, 0x4358755A2B12E6AFULL, 0x8150DE3E4F8C1E03ULL, 0x374EF63401198E48ULL
        },
        {
            0x1DAA30216F4D85FEULL, 0xB61F4D5C4BF6209CULL, 0xC5F89B995F1A2666ULL, 0x8A76BE35E80FE0FFULL, 
            0x767ECF4C6958CD63ULL, 0xD911383F05F6AC80ULL, 0x616797BB7CABAE02ULL, 0x57A8C32CBE270841ULL, 
            0xF9C1DAA71287D2C5ULL, 0xBC0593F85382CD0DULL, 0x9E08E29E6ECC3594ULL, 0x41D7D6A5CC12D356ULL, 
            0x90C599DF32CFE388ULL, 0x390FE46DA1BA28B6ULL, 0x5293B07E7264D60AULL, 0xD7501C413432904EULL, 
            0x8FBD9BB60E7CAD5DULL, 0x031475A1A7AEFACEULL, 0x8B378B99F23A46CEULL, 0x45B5F53B343084F4ULL, 
            0x6C518B821C945026ULL, 0x20D19290D1E5193BULL, 0xA5CE9C413B7D2D9CULL, 0x5676A48DE1D4FA58ULL, 
            0x30B55FE22A247007ULL, 0x0AD6376932CDFD02ULL, 0x1D684C2E1F184185ULL, 0x6D87782D52538717ULL, 
            0x597C1AC537E0215AULL, 0x22F90B6976A8B20BULL, 0x1A5A9C049AD7A156ULL, 0xEF4FFEFEE2BBFAB9ULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseGConstants = {
    0xCB826A1CF802BFCDULL,
    0x841E19A39C682B3EULL,
    0x0B4BFCBB515887A0ULL,
    0xCB826A1CF802BFCDULL,
    0x841E19A39C682B3EULL,
    0x0B4BFCBB515887A0ULL,
    0xFF7909880B068264ULL,
    0xD47FFC51E5BEFBBCULL,
    0xF1,
    0x21,
    0x3F,
    0xC2,
    0xAB,
    0x87,
    0xC3,
    0x8C
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseHSalts = {
    {
        {
            0xBA0C5F51DB34B3B3ULL, 0x86661906B42CC51BULL, 0xBCE093E82C6F5F8FULL, 0x924B579139F427C6ULL, 
            0x49E1835386158729ULL, 0x210B3031A53197ADULL, 0xA30A022EFB7DA8F8ULL, 0x8DAC819C31C23D99ULL, 
            0x07962CC236B54FA0ULL, 0x756707E33F492547ULL, 0xA2BF8531B9DBA349ULL, 0xD2A1AC7DF2FF60F9ULL, 
            0xD4FD9D322950915CULL, 0x094A2CFEEE7B698AULL, 0x96DE7AFC4DD3FE24ULL, 0xF3A95D940AAC0B2AULL, 
            0x284D3C6660369ED3ULL, 0xF8B885317A51D2A8ULL, 0xB866616B94457A9AULL, 0x15AA7688663FC2E4ULL, 
            0xDDE0AD751364C6CCULL, 0xA421BBB05B5BAE49ULL, 0x36BB0BF4C5993FE5ULL, 0x50D6E87694710D49ULL, 
            0x72032D5E7F9D5FADULL, 0x516642E1C803B58CULL, 0x2D8A3A9C81E321F4ULL, 0xD8888881974AE73EULL, 
            0x5B583E975E2FD3E2ULL, 0x528F22DF0375E22EULL, 0xDACEBD907DF5D395ULL, 0x33C1AE5A2880071CULL
        },
        {
            0x8127ACA3E4551C44ULL, 0x38DBB271C31A3F0CULL, 0x0BF4A6035604C655ULL, 0x36EA2DCD271C1C00ULL, 
            0xDEFA2B14E428FFB0ULL, 0x3439026B97EF70DFULL, 0xE9F1EBA42AD09386ULL, 0x1F9B357E090A7AFDULL, 
            0xC938EB11B1A79CCAULL, 0x02FB5FE81ABA5C1CULL, 0x3BA6B2F5E0B6BAF4ULL, 0x699FF298AF16F8D7ULL, 
            0x850D6FE85D89B5A9ULL, 0xDC392C09A0389ECBULL, 0xB32CC08F9AE1C7C6ULL, 0xCA52C4FD9D1F8D3FULL, 
            0x72626613BF61A3FBULL, 0x278E183891B13F6EULL, 0xEF2CAB300B39FAE8ULL, 0xD324890F8E3B2EA1ULL, 
            0x1C31CF63D3023BE1ULL, 0xC3E2FDAA644393C0ULL, 0xAE32AFB6345303D3ULL, 0xBE16F930F189016EULL, 
            0x34932FFC16088FD0ULL, 0x9220C933EC48BAAAULL, 0x29C394630E8E1575ULL, 0x117AF58361FEA71EULL, 
            0x40474047A03517FFULL, 0x57A6280C4323AF50ULL, 0x71A2F9FA5C6C571CULL, 0x49E746C8B266A5E0ULL
        },
        {
            0x3973157020BD6119ULL, 0xB6BAAF085DFD5916ULL, 0x1E584DF925368435ULL, 0x56416F6FDCD7590AULL, 
            0xB3B28E80C17D2308ULL, 0xA0264908BC6B9893ULL, 0x5AC93396E33BE312ULL, 0x31602C71F7C4D48AULL, 
            0x4F997320722B8C13ULL, 0xF55E639FEFC4590FULL, 0xA90F0297BC18D840ULL, 0x369E735226062BE9ULL, 
            0xDE5C0DE6D4085A21ULL, 0x3C3D77B435FFE25DULL, 0x5DDDBFDDB4732D8FULL, 0xD0A913A5F37FB1CBULL, 
            0xFC72E8F2CA556C3AULL, 0x119597E7FC514808ULL, 0xA2B37B18DE846375ULL, 0x8CC33781A581066BULL, 
            0xE5B6A25A1E2666ABULL, 0x3E879451D1449DB4ULL, 0x80A0FF3DB11A7252ULL, 0xE685373426AABDD4ULL, 
            0x21859EC27811E3C7ULL, 0xD84806452691A48EULL, 0xA50097E6E6DF3FCEULL, 0xAF6DA9519E1AD674ULL, 
            0x203888A309297291ULL, 0xB98AF25B6B4791E4ULL, 0x2C4746F58D30AF0DULL, 0xA62A7C5CB867FB69ULL
        },
        {
            0x1A353490C2263601ULL, 0x86B912A7528AA9FFULL, 0x0415E98C465C1002ULL, 0xFF3904B82B63DB61ULL, 
            0xF384997A55AC3591ULL, 0xA4DF8F40793C94EFULL, 0xE7B667FBB404C8AFULL, 0x794577102DCE4552ULL, 
            0x6EE1EE18371E7AE2ULL, 0xD2B5E4F66F20EA97ULL, 0x04CD7251FC2FD81DULL, 0xAC6812F3A2402990ULL, 
            0x2D2A94E6826B9AAAULL, 0xCA11229D7F7AF503ULL, 0x401182BCE9C68781ULL, 0xA7A4640BC75CF482ULL, 
            0xC277D270319F5785ULL, 0xCC01BED70FB6F75CULL, 0xC06D16650483FA8DULL, 0xB3A9983EE101EFEBULL, 
            0x95AEF449C7759FBFULL, 0x833D7C50DFB9177AULL, 0x2D8E7913DD39BC83ULL, 0xF944C737340191F6ULL, 
            0x28FA1A37A91EDE07ULL, 0x566C50DAE9B9D854ULL, 0x547A2873478D417BULL, 0xA04F6ECC51F847D5ULL, 
            0x12AAA695A5141D13ULL, 0x295357F59006043DULL, 0x38739564050FC6ECULL, 0xDAA6912BAF2A5EA9ULL
        },
        {
            0x24FC24F6B4677C23ULL, 0x27E5265DDB924A9FULL, 0x980CB313739EB89DULL, 0x157C0298084356C5ULL, 
            0x8718DF99DAA7B41EULL, 0xB3354BAB2A55704EULL, 0x083F49BC1D9B6671ULL, 0x09E38311029A9EFDULL, 
            0x3D40D3229B9AC32FULL, 0x95ED3DBF1F067E7CULL, 0x998F3F32B99FB8B8ULL, 0xD6F45E2E2C987D63ULL, 
            0x246F485295A1889DULL, 0x8E90EE6C56B95E2FULL, 0x620DFF1F0B6B516EULL, 0xA4F569F1C174FDF6ULL, 
            0x6197741651C8672BULL, 0x678862603553D2D4ULL, 0xAA9C47F4C3678383ULL, 0xE4D7194C9EEB7CCAULL, 
            0x53D7DD8865FA695EULL, 0x7AAFA378956F22ECULL, 0xAF21F1705943F260ULL, 0x347D8A65D8524455ULL, 
            0x2DD4EB0ABFD61AADULL, 0xD36ED2BD34C70A66ULL, 0xC46BECDEEAFEEC69ULL, 0x9FFBBEB48413FD03ULL, 
            0x52FD5656F75EA3EAULL, 0xB88292B669E252BCULL, 0xB1992C7C9FED8B37ULL, 0x62AEE814FA3CAD63ULL
        },
        {
            0x900C3D2957EAC448ULL, 0x33DDB88FA5DDA97CULL, 0xCBDC1426EDD50701ULL, 0x406797F3A686AD5BULL, 
            0xE435896C619E5589ULL, 0x032D739D31F59AECULL, 0xBD9F4186359DB6E8ULL, 0xD617439AFABE9932ULL, 
            0xA04C67FC4E8D56C0ULL, 0x98512C9AE607EDBDULL, 0x2EF48DECE14EF59CULL, 0xA697AB05A9052E8EULL, 
            0x7ADC3702D9AA3B3CULL, 0x10D24E0ABEC631E7ULL, 0xC744F2755B8A9F1FULL, 0x1BD3BDC92478B763ULL, 
            0x7ADE4C2AACD9DA80ULL, 0xFDF94933741815CAULL, 0x0A7DCD8C9B5C8642ULL, 0xCC6D024453430F8FULL, 
            0x62E3F6A6E588B264ULL, 0x162260387C9670ABULL, 0x4930103388C6A786ULL, 0x390BAEF4F33DCD91ULL, 
            0x524A8BE9AF684FECULL, 0xDFBB680F415BEA2FULL, 0xFCFB546FE4FAEDEFULL, 0x02718542642A42D1ULL, 
            0x23B1CE21DDD32A59ULL, 0x87171C4FB8DD9E44ULL, 0x532F43EC6F684855ULL, 0x2861FFB2233AB6C0ULL
        }
    },
    {
        {
            0xABDF82027F73A26EULL, 0xF336FB99049D8D44ULL, 0x0358E1317CE52819ULL, 0xC9781CB969BF477FULL, 
            0x5954FCC7A3CF37E3ULL, 0xB0C239A13E7CDC6FULL, 0xCF4B6FEF76DF1BDEULL, 0x237D067B78F89A6BULL, 
            0xFFDE721FF9E3E0E7ULL, 0x76FF51A811DE5E40ULL, 0x45E79EBE93DD1413ULL, 0x4310CEA64F49D9D5ULL, 
            0xA7AC987429A0AAD4ULL, 0xA9A68679039646A9ULL, 0x8C9CA4395B0EEFA8ULL, 0x6B978CA9CC4E4A8AULL, 
            0x8DDBCB036ADF06C9ULL, 0x1034EECBB8E6CE60ULL, 0x3A72A3CDEF5CAE31ULL, 0xF05B4423B5AB0161ULL, 
            0x8543D545BFBCC7ABULL, 0xF8E1E685022E8922ULL, 0x0F22ADFDC73A76CFULL, 0xA261AB5475469995ULL, 
            0x303384E77364A3BAULL, 0x6050263CD1A8FDE4ULL, 0x9FF360B561E0CA17ULL, 0xE76FFAE8A7078208ULL, 
            0x0D4D7764D7A04923ULL, 0x8E76F5F6C0C1CBC1ULL, 0x7753B5626FC005C4ULL, 0x0DC04DFDC00947ADULL
        },
        {
            0x5A0798E2D417E788ULL, 0xDF0D1BBAF01418F8ULL, 0xEFD903C483180AB0ULL, 0x1CE68A5739A4A7A9ULL, 
            0xBFB6D15734F577FFULL, 0xA24DB6A79B2E9F41ULL, 0xCF9A23F06B11CF20ULL, 0x24FD90821CDECA3DULL, 
            0x231AA49ED211A126ULL, 0x807456DF76768C71ULL, 0x0FACE76FA75AC934ULL, 0xA24FDEC4B01D9401ULL, 
            0x5CCE53FE1B9DF950ULL, 0x3061D390C9A0172DULL, 0x4107AF16073C76E7ULL, 0xAC791E9A94BDA68DULL, 
            0x7BE321DFE6EE8753ULL, 0xC36E44CFCE281A3BULL, 0xDD4023B15C76F347ULL, 0x91B4F706EEA99BAFULL, 
            0x943D77B143D6087BULL, 0x733A6615D938D736ULL, 0xB855FE63C7D78F9FULL, 0x2810581544F6D87BULL, 
            0x91C73BC1315551BBULL, 0xBEBDF786CAC0050CULL, 0xBE27C106E99BBA89ULL, 0x0FCC7BBECDE0557CULL, 
            0xBAA8B6556F7FFE64ULL, 0xD9C1E2888F379765ULL, 0xE3EF0217ACAE1933ULL, 0x2D14BE46C2C02A2AULL
        },
        {
            0x3A9B9F994B7B882AULL, 0xFDC67EF75E59B868ULL, 0x31026E376A8962E7ULL, 0x78569C5D4BE9DFDEULL, 
            0xC31BF694C0ABB808ULL, 0xA43D3A2474F03880ULL, 0xB3DC83905C494D64ULL, 0x36B5224EB6983582ULL, 
            0x28C3976BA5574D47ULL, 0xC7BE9EC48440CADBULL, 0x43C8231F3AAF7696ULL, 0x4C89D49FC8C5B378ULL, 
            0xAA57F7B0568CC487ULL, 0xC1AB0BB959B8D9BAULL, 0x362AB5BBCE8A80CBULL, 0x0E8DC999B6FB56D7ULL, 
            0xDD725CB670B7547DULL, 0x7B10DF51BDF15A8EULL, 0x12941C29B71ADD08ULL, 0x60B99F4704762468ULL, 
            0x52EDCC457918F9D9ULL, 0xD36762DD3107A6EAULL, 0xF9051303AEBD6077ULL, 0xF5B87A60A6B1820CULL, 
            0x0E58CD2E611732A1ULL, 0x253D0B794211E2FAULL, 0x42BF51A29A6C889BULL, 0xE98FFB986E02FF2CULL, 
            0xF810A5AE9F12AEAFULL, 0x8DC29FF90FC31700ULL, 0xD8BF95CDF72BBD36ULL, 0xB53241D5D677C618ULL
        },
        {
            0xD33BB51A00334919ULL, 0xEC8AFD30A3B89947ULL, 0x232139AB04902ABFULL, 0xD6974CE3E2B26F89ULL, 
            0x90CC7707A313AD9AULL, 0xF15C155AE76430B9ULL, 0xC31E5446FE92B818ULL, 0x30EC2E6E40D1A039ULL, 
            0xDEB803DAB2C70ADEULL, 0xC84C79772C58058AULL, 0x85FDDC26A7E0B29DULL, 0x79865F1DAFDD48C4ULL, 
            0xC328122539BD7EC4ULL, 0xE322A8937F61D1BAULL, 0x273A1E03B4487E21ULL, 0x9A02042631E8EA8BULL, 
            0x8BD0C3B2083F85E5ULL, 0x75B8A823EC125FE1ULL, 0x124F1AFF3E034725ULL, 0x87054E758DAD8DAFULL, 
            0x54F1CC2C846CB40EULL, 0x15C000ED8D958BE5ULL, 0x2265AD9F717F1AD5ULL, 0x6FACF278CA72C298ULL, 
            0xD46803867B72692AULL, 0x8E169F792E073A95ULL, 0x2D748AF0A682C18DULL, 0xCC69ECA772204CF7ULL, 
            0x376EFC734C710592ULL, 0xA7E16306B0771A35ULL, 0x98639826A5D48DDEULL, 0xAD787A3F31EEB3B2ULL
        },
        {
            0x3AD0507FEF08EBE7ULL, 0x0A816FD948D49F29ULL, 0x2412E580A0666F70ULL, 0xD488C593042E9D7EULL, 
            0x47D98D3FCD08B225ULL, 0x49A5ED3671DCB61DULL, 0x2C7987E9D336CA65ULL, 0x4C94F89E81EFB948ULL, 
            0x1FD3818075267031ULL, 0x8083FE0049D459A1ULL, 0x4F0494012106022AULL, 0xBA77980D0C6C5E52ULL, 
            0xF7059D8DB4597BD7ULL, 0x1BB6BA5FD852F4E4ULL, 0x88F4F2EC8B4D6EE9ULL, 0xF42538179471C5FCULL, 
            0x60E209EC2EA35A7FULL, 0x780CC9AE8BE37DD7ULL, 0x4EBEAC82599A006CULL, 0x38ACDE4D6A5EDDF9ULL, 
            0x911F887ECF3947C7ULL, 0x9F9B1C87D4913D70ULL, 0xB9BBE1201BB3AA80ULL, 0x35AE79FA3BA382CBULL, 
            0xA192A20431DBBCFCULL, 0x3DB6E469B9A3C7CCULL, 0x9B07FDFC9ACEC1CEULL, 0x70AF268CA20C31A1ULL, 
            0x88F3B55B6DFC1C10ULL, 0xAF1338F1DDBD9B96ULL, 0xCAA804444753001DULL, 0xEF1BF685D9C7BC10ULL
        },
        {
            0xD09FC32471B05743ULL, 0x7E34E34CD554B434ULL, 0x192455DA0A0DCA55ULL, 0x7F49EBF7A3360080ULL, 
            0x173DB486A5E529B6ULL, 0x24019015BC92C3F1ULL, 0xF53B407E9B704482ULL, 0x74BC068B2D544D96ULL, 
            0xAAC9D9434BADD84BULL, 0x5A7A932C60B8E9A8ULL, 0x1AAD5455C36F3E9DULL, 0xA7E274AEB39F807DULL, 
            0xF0F1712F19053FF4ULL, 0x333775F4B8CEC93BULL, 0x589C18171ED2469AULL, 0x9215BE8E4BA6F2CBULL, 
            0xF7A565BE3C4A5AC5ULL, 0xB5A4AE41C7EE506EULL, 0xED47D2DB68D557A3ULL, 0x52BA255B3A034294ULL, 
            0xFE02D31299776689ULL, 0x7EF86DF9F99BEA74ULL, 0xE6B103841D2874B3ULL, 0x00C5D5017CC87DD4ULL, 
            0xE30742E90BCEA0C6ULL, 0x7D53E8B60A880276ULL, 0x8378715960E81AAFULL, 0xD49EAEF5D6D0EA6AULL, 
            0x3285CBF239D089EAULL, 0x24BB559B1519E557ULL, 0x49AD314201C92D8EULL, 0xCBF38A8839C6DF90ULL
        }
    },
    {
        {
            0xEDDD77AC3FBFE9ADULL, 0xE33241F1A8999436ULL, 0xA8DCEC0620B04BECULL, 0xD99C827BA75CCBA8ULL, 
            0xCEB86B8247CF91CFULL, 0x3E2543960BD6D6A1ULL, 0x6832E63A5587846EULL, 0x1C65B5D33D8EF613ULL, 
            0x7B6A6047404D6BC1ULL, 0xDCF768E14D070DD7ULL, 0xDB8432F77C28CE02ULL, 0x9C68CA05EABC151EULL, 
            0x4753B6389C02E8E6ULL, 0xDFCF8B6229E72716ULL, 0x05895027BCCB298AULL, 0x95543C5ABE03B26DULL, 
            0x7C9BA688970BBE8FULL, 0xE9B502A460E82A38ULL, 0x5ADFD39C35046155ULL, 0x2818EE5786102495ULL, 
            0xE044262B64E58B46ULL, 0x27C1547C1797A92CULL, 0x6C6891373448A0BDULL, 0x64D47DA90C171E4DULL, 
            0x68C49B02C82C7611ULL, 0xE919CEF35BBB8571ULL, 0xC8977ED029531165ULL, 0xBA30DBAFAC2EB001ULL, 
            0x64F7390D67B69C41ULL, 0xC4E103DD8B948C6DULL, 0x0D0B1CD8AA9D06F6ULL, 0x46F6F18671464585ULL
        },
        {
            0x21CC26C191F06BC2ULL, 0x9E07D2B762A9D2C9ULL, 0x1F5585BAE9B55C19ULL, 0x349EE1CD97451201ULL, 
            0x827D2868BB3E28B8ULL, 0x76579D33B1CF8C5AULL, 0xFA06D3A4AE9213BFULL, 0xFEAD8C335103F702ULL, 
            0xCB26B8E6D72AA054ULL, 0x4F1443FC5418177DULL, 0xED96E98FE2057DA0ULL, 0xAA32E5984D86B248ULL, 
            0xECA1368114D33EBBULL, 0x2AC211A49A23ECE0ULL, 0x9D06830251B8447FULL, 0xB9E77B487A8D5E0EULL, 
            0x82132C358C231F12ULL, 0x024C675890B1EEC0ULL, 0x247081E2C18BE18BULL, 0x9A780D4C29EDC9F4ULL, 
            0xF34355DAB9504246ULL, 0xABF404B476C93E73ULL, 0x564171678DBD194BULL, 0x8D3F2CE39354DE82ULL, 
            0x6BBEBBAF479CD547ULL, 0x4D30529DD6D27824ULL, 0x8686311B5F8C27E3ULL, 0x23637741AEC1D431ULL, 
            0x8933DD1E8A48216FULL, 0x7BA711A1D71FB8C7ULL, 0xB68B159A97A39BC4ULL, 0xA3BAD9D537F920D9ULL
        },
        {
            0xBAB0236F2DD41826ULL, 0x89E185541AEDB125ULL, 0x85748A6B4BBC73F3ULL, 0x35EDDB8D4A2C0850ULL, 
            0xFD3F1411B870E67AULL, 0xC30A2B0149EDFC86ULL, 0x9C11FE2311C22FE9ULL, 0x23C861AE10E158C1ULL, 
            0x02365CBDB991F2ABULL, 0x1EAF79DF858EF6CAULL, 0x5007E324195FC7D8ULL, 0xA1A9FBEEC9C802D7ULL, 
            0x7FF9FFC9DBC7ED16ULL, 0xD6272E05FD56FB6DULL, 0x5BF8DBC9FCB55C64ULL, 0x378D535780F555A3ULL, 
            0x19694D4B83419DD4ULL, 0x2A9BBE2F638A2730ULL, 0xD1EA9DEAB99EFDF4ULL, 0xC454474E00847492ULL, 
            0xDB1E5C248C4B25A8ULL, 0x6CE088619E8E55CBULL, 0xBD0DF1F53053E97CULL, 0xCADB321176D617E9ULL, 
            0xD41CFA4F50699AB6ULL, 0x32765A8D516EB5A1ULL, 0xEA5683E02C43C50AULL, 0x3BA465C8DD458620ULL, 
            0x25BD3D9D331EDA1AULL, 0x4F8DF07A070A8A27ULL, 0x20AFA39F04648FDAULL, 0x2CA1DE752653E608ULL
        },
        {
            0x5426772D531FA682ULL, 0x61D3AD612E40A16FULL, 0xB2CF3C96523BB292ULL, 0xB0937DFB3A842100ULL, 
            0xEA51B73E57C1684FULL, 0x9D80C911A9ADF851ULL, 0xF2C5B96D72809AAAULL, 0xDD383A0502786763ULL, 
            0x7BEF71C812974CB0ULL, 0x1D55C9933D659300ULL, 0x54B618A775977610ULL, 0x4862C3893E51F203ULL, 
            0x5BD0618275157A96ULL, 0xF1C72D0A145D4131ULL, 0xB767D47B14758E70ULL, 0x28E128D6B81425F7ULL, 
            0x53105489F8C7228EULL, 0x7FB5BF5DED40A749ULL, 0xFE1C5EB9680A23A0ULL, 0x0BA968B182D9EFD1ULL, 
            0xA1EAE5F651190092ULL, 0x3882AEFB2C33B525ULL, 0x19E36527D764B71DULL, 0x0A86DA0896FBF905ULL, 
            0x0090E227B786047AULL, 0xD804580E66B953DFULL, 0xAE0693F0F757BFA9ULL, 0x24F9B9A09EBB79A2ULL, 
            0xFD4F961C7080D742ULL, 0xF18DC5290D0A5C62ULL, 0xE1F2CA70572CE9EEULL, 0xF84D3401C64C25EBULL
        },
        {
            0xA29B8EE6E50351FDULL, 0x3EC1A772BAEFF88BULL, 0xE4960BE407664F9AULL, 0x399A5976F98C63D2ULL, 
            0xD6DC5B75A57C43BBULL, 0x33BD3D4508D3B688ULL, 0x59AB747AC5EB76EFULL, 0x43D766E8E87E5E2DULL, 
            0xE7B4FAA7E0D77FD4ULL, 0x6593910FFA210BC7ULL, 0x5FF81188225B30DEULL, 0xBAD8A5D16C633769ULL, 
            0xA34E0E724F9B8AB6ULL, 0x601D582B8A69C93EULL, 0x598DA4499B2BA676ULL, 0xC6D4F1013E82F7A7ULL, 
            0xF1D0482D0FD546CFULL, 0xB841CBA81567A70DULL, 0x01797083A46544D3ULL, 0x61792B1408280DFAULL, 
            0x54FBBEBD2575E698ULL, 0xAABDEA3923EC9F5DULL, 0x9B70633A66142C86ULL, 0x7739E675CA594622ULL, 
            0x779F5B876876FE57ULL, 0xFD5F968E77E2EC2BULL, 0x3B1DC5B0B639C8DDULL, 0x0313686121DF33DEULL, 
            0xE9E1B7412879FB37ULL, 0x960DCBC2E8165CEEULL, 0x0F589F5605C35A6EULL, 0x53D47DAA5968F257ULL
        },
        {
            0x4821434EC469AD0AULL, 0x4EBFB3B89878FBC8ULL, 0x19DC0CF9C0B17F94ULL, 0x28DC53A902E4FD47ULL, 
            0x5A55FEEB1A9EB2EEULL, 0x917A65BF2E87BAFBULL, 0xA9DA8AD04DFE43DBULL, 0x86B46AED52C04A12ULL, 
            0x0C80AF788E98826AULL, 0x9BBEA27E75D188AFULL, 0xADB214CBADDCD800ULL, 0xFE566C35F2A241FEULL, 
            0xF5F5BAF7945C068BULL, 0xAD4A6CB028C449C4ULL, 0xE630E3F1D8A773EAULL, 0x66A8FC73F1696646ULL, 
            0x8F0198495E601F1DULL, 0x90861B502A87F183ULL, 0x153971F4CAE666BCULL, 0xEE581D0CD52BDCBEULL, 
            0xA6DE9621F0C0C902ULL, 0x1EE00D06D47707D0ULL, 0xFBD4FB868144DB8CULL, 0x8B9A4397DA059ACAULL, 
            0xAF7809E678BC4FCAULL, 0xF8A4C00D8AB5A711ULL, 0xF2CD2C606B68B055ULL, 0x7B7CD5FC015A8411ULL, 
            0xAC06163504C16165ULL, 0xBC37F06EE6EB71C4ULL, 0x579AD180589DB007ULL, 0xC133B7667492B724ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseHConstants = {
    0x58BC7F4534EE74BFULL,
    0xDA85C5805496104BULL,
    0x2584691017F2C784ULL,
    0x58BC7F4534EE74BFULL,
    0xDA85C5805496104BULL,
    0x2584691017F2C784ULL,
    0x1AA30876FB138A08ULL,
    0xA41957480D8FE795ULL,
    0xB2,
    0xC9,
    0xC9,
    0xE8,
    0xF6,
    0x36,
    0xE8,
    0xF8
};

