#include "TwistExpander_Achernar.hpp"
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

TwistExpander_Achernar::TwistExpander_Achernar()
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

void TwistExpander_Achernar::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC7916DD2120DB2B1ULL; std::uint64_t aIngress = 0xF1C36FCC889198FDULL; std::uint64_t aCarry = 0xD26A1B41D84EC81AULL;

    std::uint64_t aWandererA = 0x9F07540C17962CBEULL; std::uint64_t aWandererB = 0xA49605C28E0F45BEULL; std::uint64_t aWandererC = 0x979E2DE29EC808B4ULL; std::uint64_t aWandererD = 0xF6336BD2A58C3A39ULL;
    std::uint64_t aWandererE = 0xE2A1CB5C708CE51DULL; std::uint64_t aWandererF = 0x944FA32FC35AE94EULL; std::uint64_t aWandererG = 0xA84405B78C5FB419ULL; std::uint64_t aWandererH = 0xA4AA78F4E4CF81C7ULL;
    std::uint64_t aWandererI = 0x996CB1A3C16910F7ULL; std::uint64_t aWandererJ = 0x86BBCA86DA006C2EULL; std::uint64_t aWandererK = 0x901F4459C313F6F6ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10963423333175257542U;
        aCarry = 16828524045222393419U;
        aWandererA = 14807914014242852353U;
        aWandererB = 18212084758020263490U;
        aWandererC = 16854984600595510077U;
        aWandererD = 14159410734062829440U;
        aWandererE = 9475430713616060444U;
        aWandererF = 14722958416186966939U;
        aWandererG = 17247058322839368470U;
        aWandererH = 12937056306482640619U;
        aWandererI = 18036608194486239455U;
        aWandererJ = 15268756498903914325U;
        aWandererK = 13727021311645567091U;
    TwistExpander_Achernar_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Achernar::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB2DE6A43A29AF1DFULL; std::uint64_t aIngress = 0xC0140EA692C8566AULL; std::uint64_t aCarry = 0x84EA3E33D9F1D1DCULL;

    std::uint64_t aWandererA = 0x86855411B125C904ULL; std::uint64_t aWandererB = 0x89F2C2B5677DD311ULL; std::uint64_t aWandererC = 0xD936FD3AD7A5E0C4ULL; std::uint64_t aWandererD = 0xD5E357BD0B019AFCULL;
    std::uint64_t aWandererE = 0x84CEBEF0B7A119AAULL; std::uint64_t aWandererF = 0xFD08EC3BEBF79D36ULL; std::uint64_t aWandererG = 0xF1EEE2FEE43C4497ULL; std::uint64_t aWandererH = 0xB1EE9E65F75FB914ULL;
    std::uint64_t aWandererI = 0xE2024C651030C257ULL; std::uint64_t aWandererJ = 0x8AC497285AA51CD2ULL; std::uint64_t aWandererK = 0xCBE0759C5C53FA19ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12311759683424714473U;
        aCarry = 12152083815085743196U;
        aWandererA = 15106569429415986806U;
        aWandererB = 14956582074627967166U;
        aWandererC = 16466508760052316830U;
        aWandererD = 16859443083477539319U;
        aWandererE = 14224177260642191523U;
        aWandererF = 17361779099151655679U;
        aWandererG = 12997767542536055883U;
        aWandererH = 14109551598323237325U;
        aWandererI = 15129375088236607213U;
        aWandererJ = 13345382427320615867U;
        aWandererK = 16161426186306292952U;
    TwistExpander_Achernar_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Achernar::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xEAF355B117230662ULL;
    std::uint64_t aIngress = 0x82193FD036A0BFAFULL;
    std::uint64_t aCarry = 0xDAD6E6274CC340FDULL;

    std::uint64_t aWandererA = 0x90ACDC4C3F25F296ULL;
    std::uint64_t aWandererB = 0x959066B0830226ABULL;
    std::uint64_t aWandererC = 0x97BFDD3F4EB3DA66ULL;
    std::uint64_t aWandererD = 0xB110CC0EC7F62E67ULL;
    std::uint64_t aWandererE = 0x992685D4AEA6A061ULL;
    std::uint64_t aWandererF = 0xC7E50DFE0192DD2CULL;
    std::uint64_t aWandererG = 0xFAD52F6507DDA409ULL;
    std::uint64_t aWandererH = 0xDFE1ADC8B43465A9ULL;
    std::uint64_t aWandererI = 0xFB98C97EB8D83486ULL;
    std::uint64_t aWandererJ = 0x884B0E4416272D7EULL;
    std::uint64_t aWandererK = 0x82E39EAE634429F6ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Achernar_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 1 of 33
// Exploration cases: 50000000
// Diversity score: baseline candidate (no earlier family member)
void TwistExpander_Achernar::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 768U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 341U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 171U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 622U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 490U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 34U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1763U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 352U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 728U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1079U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1136U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 404U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 279U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1040U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 300U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 324U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1327U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 504U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1819U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 563U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 608U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1267U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1081U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 566U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1034U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 379U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 88U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1601U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 316U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 860U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1827U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1983U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 252U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 181U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 578U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1029U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1265U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 542U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1502U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 321U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 583U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 519U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1052U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1043U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1158U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 470U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 630U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 539U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1342U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 162U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 734U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1118U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1567U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1416U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 418U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1391U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1481U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1960U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 307U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1985U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 467U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1552U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 59U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1197U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 902U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1340U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 282U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1099U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1086U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1798U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1613U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 291U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 804U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 845U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1055U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1931U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 713U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 754U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1706U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 656U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 485U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 632U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1329U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1240U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 991U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1644U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1821U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 547U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1679U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1672U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1367U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 878U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1349U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 236U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 229U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 971U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1886U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 326U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 850U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1557U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1955U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 137U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 785U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1637U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1970U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 91U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1302U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1636U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 935U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1630U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1958U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1686U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 419U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 892U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 8U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 899U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 471U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 791U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1562U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 993U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1114U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 797U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Achernar::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDF51BEDEC34E741BULL; std::uint64_t aIngress = 0xE41CCB9D2B34E974ULL; std::uint64_t aCarry = 0xCC403F65F399F362ULL;

    std::uint64_t aWandererA = 0xD310D0B3F1DA8931ULL; std::uint64_t aWandererB = 0xF80D0F2C1490ADD3ULL; std::uint64_t aWandererC = 0x8F0D523F03185925ULL; std::uint64_t aWandererD = 0x9CB2A64BB17ADB51ULL;
    std::uint64_t aWandererE = 0xECEC929B4BCF308FULL; std::uint64_t aWandererF = 0xDDA9D0AE278C451FULL; std::uint64_t aWandererG = 0x9BD298B4535B28B8ULL; std::uint64_t aWandererH = 0x8F6E5F015C5D6B0FULL;
    std::uint64_t aWandererI = 0xD29B8041340CB5BAULL; std::uint64_t aWandererJ = 0xED7AC0C4AA0F98ACULL; std::uint64_t aWandererK = 0xC477A826E3C63D31ULL;

    // [seed]
        aPrevious = 13055019905379348823U;
        aCarry = 16920414160693589999U;
        aWandererA = 14274481136090533767U;
        aWandererB = 12999730438772047766U;
        aWandererC = 10066007685892128534U;
        aWandererD = 10860260760087261114U;
        aWandererE = 12526085691458291920U;
        aWandererF = 16111702410048823372U;
        aWandererG = 15949087186435884153U;
        aWandererH = 17913948946819649937U;
        aWandererI = 16196959331375622165U;
        aWandererJ = 17543103586772443599U;
        aWandererK = 15982058933561650088U;
    TwistExpander_Achernar_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Achernar_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_G(pWorkSpace,
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
        TwistSquash::SquashA(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Achernar_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 1 of 33
// Exploration cases: 50000000
// Total structural distance: baseline candidate
void TwistExpander_Achernar::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1255U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6354U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1878U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2148U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6739U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1069U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3370U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1422U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5071U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 560U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3627U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5330U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 753U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5731U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6626U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3580U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 387U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 286U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1985U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1114U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1071U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 316U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 767U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 517U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 659U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1807U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 507U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1109U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 96U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1030U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 485U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1346U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 966U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 1 of 33
// Exploration cases: 50000000
// Total structural distance: baseline candidate
void TwistExpander_Achernar::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1199U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 704U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5970U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3590U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 63U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6818U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7190U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7332U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7148U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3049U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2557U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1609U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4023U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6964U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7875U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1082U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 757U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1378U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1274U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 383U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1568U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 884U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1857U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 429U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1763U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1137U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 504U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1868U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1046U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 448U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 480U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 667U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 947U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 345U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseASalts = {
    {
        {
            0x5E8B181AAFE10617ULL, 0x4F16D28347873F54ULL, 0xB179BCE0A758C767ULL, 0xF4717F6D6D9F01F0ULL, 
            0x7D379600FA945D87ULL, 0x8099D1B5CE59D613ULL, 0x956DF209DD27AF2AULL, 0xC9DC2DA76F477D92ULL, 
            0x84FC94C5C4C16321ULL, 0xF6893A4E2BFA7A7BULL, 0x7A2FBFEF06A426DAULL, 0x5DEE1F1AAA7A04B8ULL, 
            0xB569B683956C10DCULL, 0x777D8F55284B21A7ULL, 0x0776DAEC2B05DABEULL, 0x6C7D738F4B2C82F6ULL, 
            0x84E5302B6DD1CE38ULL, 0xD74A52B3686594BDULL, 0xBEDCB1F382429C36ULL, 0x93E4D94C4C61B2C1ULL, 
            0x7EEED51BC9DA041AULL, 0x2673E86F2ED435E5ULL, 0xBAA0C7CCC84E0909ULL, 0xAB05C0404FC3EB63ULL, 
            0xEC1CAF9FED3B55D8ULL, 0xEA2C2FB57C2E1BA1ULL, 0x6EEE6063945F3D12ULL, 0x09FBFE22C81461CEULL, 
            0x2C5B0FE7762F7D21ULL, 0x9025832770358227ULL, 0x31A8DA0D51037AA9ULL, 0x68F3217F2842C8F8ULL
        },
        {
            0xB4A0F70065CAA0B9ULL, 0x04647FA1AAE37EADULL, 0xDA8353CB18A6AF4DULL, 0xAB78448AC2FD42D6ULL, 
            0xA58BDC8C5DA26537ULL, 0xCBA66C9E3162CECFULL, 0x550717D40D669281ULL, 0x7E192FE0C50215C0ULL, 
            0xC9D207AB7CFC1D57ULL, 0xEBA3200043EE1376ULL, 0x98633EE90FA9F979ULL, 0x09027224232FF81BULL, 
            0xB9CF52A87B5598CAULL, 0xE16DD09638451A09ULL, 0x80F6B9889CE24440ULL, 0x4F437A83DA5F8480ULL, 
            0xDD47EA7C552509A0ULL, 0x2E463B75763738F6ULL, 0x46324E0918C6B1D6ULL, 0x1CCBDA02A5E61C1EULL, 
            0x5272BFCF5A62A55EULL, 0x75C5B315F0646A4CULL, 0x3F7DEF60FBC7DDBCULL, 0x1E6D8DB3B98E96D9ULL, 
            0x76F8350948CFE27AULL, 0x7EBE1F2AABE2AB0CULL, 0x282A90A0F92A8677ULL, 0xD3BA74B3BA83E341ULL, 
            0xF06F953D2DF9BDCBULL, 0x559057675E636925ULL, 0xF2B4DAAFD72B576AULL, 0x6681A1ABB5500E84ULL
        },
        {
            0x8AC4A8CC40D2C5ECULL, 0x0F519B6DFC682261ULL, 0x4B06736D2BAF8174ULL, 0x192A0051C27FA4ADULL, 
            0x457692FCFCEE1C2EULL, 0xF0B390F50BE6D383ULL, 0x8B761099EEEA62FDULL, 0x6EDD63A27E1982E8ULL, 
            0xB38B21CB37AA08CEULL, 0x4467122644FF3DA7ULL, 0xE2C947F8B4E6B21BULL, 0xDBA030A90958D4CAULL, 
            0x89805943D0183A7FULL, 0x604CEA75E49A6885ULL, 0x4AC82632BDDB8EE9ULL, 0xE099C662B019B490ULL, 
            0xC5148A45CBC9F2A4ULL, 0xF92FB7BE5D2297C3ULL, 0xF673FA484A182810ULL, 0x3FC3FFAA6A66D1B6ULL, 
            0xFA6B029A040CE894ULL, 0x30B61E469CD54ADDULL, 0xFA9A9628FB5E0C6CULL, 0xD3D995D158039948ULL, 
            0xA227BE75F4FA42F0ULL, 0xAF8E6F295220BD8FULL, 0x693D572B71A611B3ULL, 0xA2DB3D7E413414B2ULL, 
            0x113AA95D4B9D7C63ULL, 0x58E007E9CC3CFD01ULL, 0x4EB9CA1F502D38FEULL, 0x5BA8DC93EC793667ULL
        },
        {
            0xAAF51205DAB746ADULL, 0xEFBE14DFF7830043ULL, 0x8F36CE703F69BDD9ULL, 0xBB02D2B3DC36B017ULL, 
            0x3A70BADCEEFCEAF7ULL, 0x7DDCE1E52ADDBEE7ULL, 0x26737292378C2DD1ULL, 0x08870299453A0365ULL, 
            0x156E845A805D0FBEULL, 0x8FD3CC83832BDF6DULL, 0x6CA5D8B62DAC64C0ULL, 0x4A69DB55FF48D9DAULL, 
            0x3A1AC2D8CC558A00ULL, 0x6663FB24AE8B0595ULL, 0xB01DA2CF4F4139C7ULL, 0xD075D5B5667B3D9DULL, 
            0x0D1C2B6C009B8BF2ULL, 0xDA693A400D938C5DULL, 0xB20580DDB356133FULL, 0x292EAE01FD125542ULL, 
            0x1822248F80726B70ULL, 0xD4C87FC4278EA02EULL, 0x5ECBE7963894C391ULL, 0x7521322A8683AA39ULL, 
            0x7D2045568CD5CF79ULL, 0x3B4D929C0FD2E30DULL, 0xB32D95A89D88CB40ULL, 0x9BDDBB0AA48E9989ULL, 
            0xBBB799EE45E2DF93ULL, 0x63380FBE43E626BAULL, 0xD5CD1BF09A2E75E9ULL, 0x9A4049906AB97ECDULL
        },
        {
            0x27165753E97AEC43ULL, 0xB4A4241D95F15573ULL, 0xF18AF5826692E944ULL, 0x77EF1773FA92A77DULL, 
            0xE9CA24BBF3B91010ULL, 0x32EA0F525963C9DCULL, 0xDE312F6F5D64FD25ULL, 0x5BA054DF662785A6ULL, 
            0x5097D5D9B1C4CAB5ULL, 0x99D3343B65EF4F0FULL, 0x997B5D92A0373E8CULL, 0x455080A49E0984E4ULL, 
            0x77316E846D847354ULL, 0x773D45A1189C7C90ULL, 0xCA0687D30B6C5B14ULL, 0xD50ED1A65A451DEAULL, 
            0x477926154EDB4844ULL, 0x37C6B241A005CFD6ULL, 0x0B24E0A33320B0DFULL, 0x2F63A8EA0D72528FULL, 
            0x54FA3AA2968E3961ULL, 0x31FFFE9DB868A813ULL, 0x55371BB5DA5476D2ULL, 0xC0129114D84B354DULL, 
            0xAA6C49A072B0514BULL, 0x2F9A62CCF63B5BE2ULL, 0xC73BC5BABB22AF65ULL, 0x9C654CC8CD0DE936ULL, 
            0x54ECFD77A1261348ULL, 0x2743D6399CF2E03EULL, 0x9DFD0CA1C56737FAULL, 0xA4351E9FFBD744A9ULL
        },
        {
            0xF7D5281010DC7AAFULL, 0x2F5AC4ED000343E2ULL, 0xD1A890D59D18C0C2ULL, 0x8DEF3CF69325323FULL, 
            0xEAA539A5BFA47196ULL, 0xD1A3A544FA8C286FULL, 0x7DFE14C35366283EULL, 0x510043F1572A2ADCULL, 
            0xDA4691A0532E0963ULL, 0xC54C4D93F77EB030ULL, 0xCC34F20A0A14C9E7ULL, 0x2B9DB14E9267BB0AULL, 
            0x789A43AEC8CD8ED1ULL, 0x46ED1EF7CE9EB06CULL, 0x3338278622F1F1CAULL, 0xB70F940139330082ULL, 
            0x173239EA3200DBD9ULL, 0xE0A6BF05ECCDFFA4ULL, 0x5165368996479B7EULL, 0x5A4BBC7569CA464EULL, 
            0xBE77D0F296DDE988ULL, 0x6E7D516BE999FB96ULL, 0x48D6F5F16D4351F7ULL, 0xD59779C156530C3EULL, 
            0xBD256EE5C25E1899ULL, 0xF1D2E475517A07F8ULL, 0x1C6A1ED251721B17ULL, 0xD8FC2FE430B4B23FULL, 
            0x7CD5534BE32631EFULL, 0xB096FFBBBDDC9408ULL, 0xE516CA252EE121F6ULL, 0x0F2C7246F2FB0799ULL
        }
    },
    {
        {
            0x3FBC54BFFD451BC9ULL, 0xBE5929E6026889DEULL, 0x2510B702BEA50E10ULL, 0x107D50CB5A3E8162ULL, 
            0x419DACF69AFF1BE9ULL, 0x714F2B09DAE310D6ULL, 0x7C09ECBA986296BDULL, 0xD3C6659EA6E4D792ULL, 
            0x8E7A0107817DD6DFULL, 0x73F9CFFA09F1FFC6ULL, 0x247B402A12A07CD8ULL, 0x3B74288FC425C691ULL, 
            0xA7AD09ED8BE33388ULL, 0x4B1D60588A9E228BULL, 0x00FA71B62AC372BDULL, 0x345A5DD3055B4495ULL, 
            0xC429DCFEA2CB41D6ULL, 0x594C59FACD967CDCULL, 0x1C4355F99A8F8CF0ULL, 0xA9D26691F0486D95ULL, 
            0x85B8B53364180FFFULL, 0x4E038B6D46475200ULL, 0x5FAEAAEAC6F2C394ULL, 0x4E9A7B02EB1AACF9ULL, 
            0x8834899CEFC4D535ULL, 0xAD0AAC240052CDB7ULL, 0xFA75AB4821386FD8ULL, 0x58D4B48F5965A64FULL, 
            0x6317834857EEE93BULL, 0x1FD110D40284A595ULL, 0x52B2987C36837775ULL, 0x4AB3CBEB17AB6D1BULL
        },
        {
            0xFF7BAC61B588AE1DULL, 0x916DCD99AEEDF3E2ULL, 0xD483952AD7861D7EULL, 0x136130E092F28514ULL, 
            0xFB8F9666AC180B86ULL, 0x1FB855CFD07BFEB7ULL, 0x2D5FAFBAE3C691DFULL, 0x6C9D498945BF7FB8ULL, 
            0xA8435D1E7A80842FULL, 0x11469606F6943F74ULL, 0x0F176C651DC71566ULL, 0xD2FD7FB991387601ULL, 
            0x7666BA9F01F56E32ULL, 0x0F592F9172D0963BULL, 0x56758AA769C74067ULL, 0x7AAFF21B43113195ULL, 
            0xC9AD24BD291CF53BULL, 0x63F8045E9E260752ULL, 0x79660E747E1C7B51ULL, 0x19639F1FA2A0352DULL, 
            0x3967C37A33773507ULL, 0xE61028F1CD662973ULL, 0xE21269A58A1A5CC7ULL, 0x1A4AF48FFB0C634FULL, 
            0x0156CC3F1B168370ULL, 0xEE5E3F164188F666ULL, 0x9A96B75EE9E2223DULL, 0x23E1D70CB0330928ULL, 
            0x5B3D35C9B532CF97ULL, 0xD98E5C0B0F184D29ULL, 0x4B6D0B7531834B81ULL, 0x2BF1461C0D65B7B5ULL
        },
        {
            0xFC64082590C2E713ULL, 0x398F25AA1788D27AULL, 0x80B442768FB957CCULL, 0x204A075BECC3B7A7ULL, 
            0x40D332502424515AULL, 0xF35F84AB54A482F5ULL, 0xB3BF22483A270955ULL, 0xF88803FBE48A7DA4ULL, 
            0x3DDFD033AAD147EBULL, 0x6666CA13EB6C4FFFULL, 0x1C86E10B9EB32F88ULL, 0x277C41DEB4F968F7ULL, 
            0xA0483A0011BA7D2AULL, 0x04CC5977CC4A9279ULL, 0xD137A6F32E048C5BULL, 0x06519D9477DC7186ULL, 
            0x1712D28D147EBA27ULL, 0xE6BF2D54161E26E0ULL, 0x97A4A1B67AC98C0CULL, 0x2C2A8D60B82D6F0AULL, 
            0x607917E2EC937CAEULL, 0x9736673E32780099ULL, 0x57AC2BF6B82C4505ULL, 0x492F25A5E76B6AD7ULL, 
            0xABC859871A23255AULL, 0xA5DC9882605BF952ULL, 0x385AFD214A284C2DULL, 0xFFF1E3D6AF1936CBULL, 
            0x97029A92504E8BF0ULL, 0x5274AB5DE38B538BULL, 0xE162C519490615D2ULL, 0x062E9BE3E7396FC6ULL
        },
        {
            0x20FEED323C2C4CF5ULL, 0xE285930062090F69ULL, 0x58DF32FCBBCC84A0ULL, 0x8D81E554EE5A73AAULL, 
            0x4A5BC8260D2A91DDULL, 0x10E093E5F5A36520ULL, 0x6B325823FB027DA3ULL, 0xB6E41C32CD7888DBULL, 
            0xA46133F314C434D1ULL, 0xE0C7B36F45D264B6ULL, 0xDE7B385B912E1A52ULL, 0xFCA2A426BB849AE0ULL, 
            0xAEE7BB3195F5F4CEULL, 0x5998FF5C6C164E02ULL, 0xBBCBB0EB9B5DB050ULL, 0x40E5A5CD34D3FDC0ULL, 
            0xC0C37CEBC2EC1103ULL, 0xDBC9F98128A5F1DCULL, 0xF4D2FA6B614F9212ULL, 0xBA9B6A1BC785C6B5ULL, 
            0xAF97E208494F58F4ULL, 0xB988510ACE5AC4E2ULL, 0x869C1410480CB0B1ULL, 0xF5AD9332CC678EB5ULL, 
            0x5D76328DA4BE0863ULL, 0x05A7BD432E51D268ULL, 0x957634F0B59B3F7BULL, 0x1FD1745D53CFB6D8ULL, 
            0xDC1ED0D785BEB12FULL, 0x6FB0F90A62F8D190ULL, 0xD500053E58029970ULL, 0x699227FE08B2259FULL
        },
        {
            0x53D12F267A4DDD8AULL, 0xDE386DAB398B8E80ULL, 0x73DB54124992A993ULL, 0xFC19CABFC60EBEFFULL, 
            0x01D647E5976249B8ULL, 0xE8495CB27CFDCAE2ULL, 0x011735C955D683C1ULL, 0x3E503E885668E654ULL, 
            0x755115BAD4C8D75CULL, 0x1C272D859716B89EULL, 0x65F823B11FBB6C46ULL, 0x1CEF35768CDA5849ULL, 
            0x35FF2174366ACC5EULL, 0x7D20E8957D8FF732ULL, 0x483A19EDD497B065ULL, 0x4BB20DA65BB92529ULL, 
            0xF56D03DA47FE657CULL, 0xE13C2A7DAD743B21ULL, 0xBE81751FC8AE7945ULL, 0x7374683B71F32FA9ULL, 
            0xE5A81FBA81C90B50ULL, 0xD118F3327604F332ULL, 0xB6BFB74C075D41B4ULL, 0xFDEA74B8CEA9177BULL, 
            0xBB8D61EA3B08FEA6ULL, 0x5877CCF5C773EE67ULL, 0x4F5A8BBEA5985861ULL, 0xAD14B9E5260432F2ULL, 
            0x51CEDC5ED6769455ULL, 0x7D0AA68C7D5E0D90ULL, 0x789C26D8F857CE50ULL, 0x30ACF3FBF6D9A485ULL
        },
        {
            0x4C5DB7E6B25751B0ULL, 0x439C58DA39B0D54BULL, 0x4A00CDD3332ACC67ULL, 0x446E373933E9A798ULL, 
            0xA57E5D53D23E00A0ULL, 0xFF6EA1C85D1F4947ULL, 0xEC49AB49DF0F3231ULL, 0x599063FD4B7394B4ULL, 
            0x37A12DA6C4BE0402ULL, 0x1E40A3AB0CDABAD8ULL, 0xC6CFB0B56200F945ULL, 0x050A998252F53C1EULL, 
            0x998BE6C7D885602BULL, 0x1B70738CF4D3D1CCULL, 0xAFB3DA5850A4AADBULL, 0xAD2F88E7E1E88BBFULL, 
            0xE52BBE1111B8A63EULL, 0xF549CCCAFD784099ULL, 0x45AC3FD8FC4F9705ULL, 0x0587296EBE0E908DULL, 
            0xB54F155CC09B1569ULL, 0x79420A1FCC8D79D5ULL, 0xB1D76AD71E78CAB2ULL, 0xE721BDFBA552730CULL, 
            0x36208551C4F5BFEFULL, 0xC63E3556C247E964ULL, 0xFCF4956E8FCC0307ULL, 0x425EE83791C294E8ULL, 
            0x4D084227A6AC41FFULL, 0xC045CB620D91DA53ULL, 0x7E08076D0E2D6C29ULL, 0x19312077E2618680ULL
        }
    },
    {
        {
            0x2A71299A77EC4D18ULL, 0xF7679F5C61DA6CB2ULL, 0x1A495017289C0ABEULL, 0x2B45445A57CF757AULL, 
            0x657FD4E704C13D1BULL, 0x7E60CDE469CEE2C3ULL, 0x6ABA2FA1ECDBA789ULL, 0x9AD722479EC3F634ULL, 
            0xA7ED98AFB0313489ULL, 0xE232A12F070849E2ULL, 0xBCF31423B6FE61ECULL, 0x1D82155D8723F7C3ULL, 
            0x58AF535BEF5E0804ULL, 0x338DA12792CB5843ULL, 0x59A3205F949B4AE4ULL, 0xA99EB5873F2A6C29ULL, 
            0xF4448C53D506943EULL, 0xC9072700DB40F0A1ULL, 0xA02972DF020A11F9ULL, 0x240945B0526ACA48ULL, 
            0xA3E1A4E900C817A6ULL, 0x58E9A05BFCAD6BD3ULL, 0x0B355E99BC15E225ULL, 0xEF5D3AEF4C9D9BAAULL, 
            0x7675BB6AAFFC630BULL, 0x6239406F8C0AE682ULL, 0xA6F01B39083B3593ULL, 0x958BD90793D4BCE1ULL, 
            0x6CF16BE91DDAEC59ULL, 0xC08F3D98AE7B1A54ULL, 0x4398D1F4CE6DA3B0ULL, 0x7C7CBD8CB6598CACULL
        },
        {
            0x8CAB8424F84659CCULL, 0xD7572505CECBCF81ULL, 0x82BF1B3796981137ULL, 0x28C32991B903D2DCULL, 
            0xC2AA9B791AB0F453ULL, 0x172659B3E414CC5AULL, 0x7DB4CB280149D98CULL, 0x24AEB040222F6B9DULL, 
            0x5F29342A96CC4325ULL, 0x650DA19E08353100ULL, 0xFD2B1828E7700763ULL, 0xC2693AF2A1646609ULL, 
            0x5C2BB1FDF7BBF98CULL, 0xAE6F7D76E02D6A21ULL, 0x1352C175F840466DULL, 0xA0647A002280A19DULL, 
            0xB981F402C83854DDULL, 0xE964D62C732C3FC5ULL, 0x843A90373A7F4041ULL, 0xEE8E6D205C4E3AFEULL, 
            0x3A2560717C32ED09ULL, 0xC47521D09A8D7A39ULL, 0x5895394A77A3AADBULL, 0xB88CEAA85D4D9DD1ULL, 
            0x2DA1E62809292E17ULL, 0xEF6AC28B8CF5AD90ULL, 0x013D449CD0722491ULL, 0xABAAD700CAB82C7EULL, 
            0xD10922810FF0C350ULL, 0x72B7E9F1777AC260ULL, 0x2C4A76B5479FAB0EULL, 0xA2F1E0A18BBC3E6AULL
        },
        {
            0xE5E07607C56FA5DDULL, 0x9A7BE808BE35BD02ULL, 0xBEC8753986EF7C0FULL, 0x9E7002C38E98AE2EULL, 
            0x5733F7947991EBCBULL, 0x886D648CDB8E8E64ULL, 0x05DE76A6BEE7CDEBULL, 0x774B52AC77855EE7ULL, 
            0xEDF9A64FD383374AULL, 0x1257F260C80B1045ULL, 0x730E6FCA52F1EF01ULL, 0x4CAC1904F7F2777FULL, 
            0xE15C8C2817CFC11AULL, 0x8BDAADDDB8F9C4D0ULL, 0x616B104F6D6A565BULL, 0xC9FDC11A54C71909ULL, 
            0x30816D826AE1731BULL, 0x82D00F59CD3AAD6AULL, 0xF40F6A40AD977206ULL, 0xB9AAEEB0EB300A45ULL, 
            0x4B4D7730A597B848ULL, 0xD96E001F3E73210CULL, 0xE2C22A468519B806ULL, 0x1C8D74B9C697F68FULL, 
            0x298A3C21A884C290ULL, 0xF764F04A5B0F769BULL, 0x5210A58EFC3B5F0BULL, 0x83B63991D5419880ULL, 
            0xE64D4FE0E479D0B0ULL, 0x0749D1624E13E652ULL, 0x8F3273BDFEE76082ULL, 0x2F4D00FF123FE1AAULL
        },
        {
            0xBEE7CCCE84A5B8C9ULL, 0xF1A1462D72C70897ULL, 0xA79CB04F9D88858EULL, 0x62B53EA51A4B1DACULL, 
            0x89473C8FBD02FF85ULL, 0xF502D2A2C3AF66DFULL, 0x24991B277E7E4F90ULL, 0xC7E0326934023619ULL, 
            0xD783D873046B5E94ULL, 0x0F4C5C2E0E46373AULL, 0x8D39538174A08E35ULL, 0x18C402F53FB2BDDDULL, 
            0xAD0FC09D405E5E22ULL, 0x0DBDCABD4E10EE1FULL, 0xFFFA4E36C9FF10B5ULL, 0x6C1110FA22691375ULL, 
            0x240C6AA9BCD9A2DDULL, 0x90F8E9348938B5A8ULL, 0x31EAD004A1F5E23DULL, 0xFB5377C3957F1AF2ULL, 
            0xB101F62ABA4AD5A7ULL, 0xD573CDC29C9A382DULL, 0x8F05B61308DB8585ULL, 0x24DBC6E377E8E716ULL, 
            0x7FFBF525CB8C4FACULL, 0x816958F6BF000496ULL, 0xD11B1FDBCCDDC757ULL, 0x7005021F401BBC6BULL, 
            0xB0B7A1482E72C0BEULL, 0x36D8AFC4DA28E0A5ULL, 0xB7EABDAF6E1F85CEULL, 0x69D279A773489FD1ULL
        },
        {
            0xDC7A7A738B37304AULL, 0x16BD50AAE9C9074FULL, 0x7077B0FD345C0228ULL, 0x8D02A9DB71FC1630ULL, 
            0xD96A760C0A3B13B9ULL, 0x785E18A4E0F49158ULL, 0x65337FE20F907C16ULL, 0xFC6B7B4760C857E6ULL, 
            0x3C0485249A1C3D46ULL, 0x820A5D65BF902ECCULL, 0x13B050CB93A84BECULL, 0xA9A1DDE53EADFDB9ULL, 
            0x9AA2232C337BECF6ULL, 0x3248338DD440D094ULL, 0x9F20D8465A0ED8F3ULL, 0x69E89D8A3C7CBF8FULL, 
            0x573BB0B44E4298B3ULL, 0x4DD34BD9594F00B0ULL, 0x537A90C0EE72C4B0ULL, 0xAF734E9B9EC5FE28ULL, 
            0x571099DF4BC59A8FULL, 0x52810BC26B18B4E0ULL, 0xD9E4C26C24B70540ULL, 0xA3BAD29C6A9F045CULL, 
            0x1262311ABE0032F6ULL, 0xDA4DDAA714D91116ULL, 0x730686DAE68C99E3ULL, 0x5DC5F874773DC6A0ULL, 
            0x677E992803717608ULL, 0xFAA31DE1827D2B8AULL, 0x5D6E590D33A16557ULL, 0x9AB136A4E87B4A00ULL
        },
        {
            0x7B5C11808584F763ULL, 0xD0A4BBA32290FA96ULL, 0x6D2827BB2D37B7A7ULL, 0x523BF285BAC37DCEULL, 
            0x2DE4A87256A49125ULL, 0x228C84B47CF73A09ULL, 0xDDD51610C1365F38ULL, 0x922D939BBEE94B3DULL, 
            0xD20B3D162CC1E05CULL, 0x1BEE70CCEE95867AULL, 0x9A970CE16705E4A3ULL, 0xC311928448160C0EULL, 
            0x05B35369451C80B6ULL, 0x2F578740F56C57AEULL, 0xD2C499A68A285808ULL, 0xCFEACCED0F4A21D8ULL, 
            0x65D2AC0294B18A74ULL, 0xE3CE0B9FDC0A79FCULL, 0x35BD96BF8E9DD39DULL, 0x476BB88A7E722765ULL, 
            0xD0CE2CFAD769A8AEULL, 0xF2FBD7D995CD2D68ULL, 0xA8AA9AE68EC83E7CULL, 0xE3CB02245CD5D447ULL, 
            0x93A060D78D0C49C1ULL, 0xFC916DF8C3CA526DULL, 0x8B5FE1DE0F434D29ULL, 0x45204C0070D6E8CFULL, 
            0xD77DBE0B6ECF79F9ULL, 0x1B0251D271EBBDB8ULL, 0x22E447124C0DCC2BULL, 0x8938C24EB7B1EC3CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseAConstants = {
    0x4351DD972A4B7F74ULL,
    0x154E06FF6509611CULL,
    0x6036C65EE0C91834ULL,
    0x4351DD972A4B7F74ULL,
    0x154E06FF6509611CULL,
    0x6036C65EE0C91834ULL,
    0x36C996AC1CE10138ULL,
    0x8D8C3D42A20A799EULL,
    0x95,
    0x07,
    0xCE,
    0x63,
    0xEB,
    0x98,
    0x5B,
    0x04
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseBSalts = {
    {
        {
            0x3B55887BE7BDEF3FULL, 0x5F428DF9B575DD6BULL, 0x7E6AB9A2CAEC4E67ULL, 0x3FE95C214330658DULL, 
            0x1D2D776D7CF49108ULL, 0x9D4A2C74D748EC8AULL, 0x3C52E671995FA510ULL, 0x2288408E1606B146ULL, 
            0x7A26DAEF6DDA6CEFULL, 0x65ED74BE8E2381D5ULL, 0x1FA325F48FECAE60ULL, 0x4F9533B218FBF1FEULL, 
            0x9A2299EDDBB81A79ULL, 0x5DB67727BB869BBDULL, 0x6DC346F734BCCA18ULL, 0xDA39DD619A22DDCDULL, 
            0x7C137D2024A31710ULL, 0x6CFFDA0921BE33C4ULL, 0x1110FBCC68662137ULL, 0xD50C168E28E1510DULL, 
            0xBDAF2ED05718854DULL, 0x1274D710D413AFECULL, 0x171A7DB219EFE38EULL, 0x72CC78C79426795CULL, 
            0xEA45E47E54C066E8ULL, 0xDF461ECF1019D4D2ULL, 0x870029043A9F8F06ULL, 0x5D88CEC37253013AULL, 
            0x351E27F2F074067FULL, 0x7822FE1B56B95447ULL, 0x9C1E107D36A88876ULL, 0x3188DAC653E79CACULL
        },
        {
            0x11987BE428DF54F3ULL, 0xD22C7C9F60E658BAULL, 0x20E2C5392E28A717ULL, 0x1048A59FDDC97084ULL, 
            0xAA6F0C1F7ADA9BDBULL, 0x60011D2F09F3511DULL, 0xF46FBCF7497EB323ULL, 0x3D9D40A04458DD37ULL, 
            0x332FC02E947EA135ULL, 0xDA2E936D10C6E5D3ULL, 0x23408A6C95021A94ULL, 0x63FFE6D4F90FC679ULL, 
            0x19D9DAFF96409B8EULL, 0x67429BF3445AE620ULL, 0x16E7F3E122584813ULL, 0xBF62F92CA375A0ADULL, 
            0xAD7713C3107750EDULL, 0xDA992A974E86C91FULL, 0xD01AE3554D57CF42ULL, 0x05FF73B9BFAA131CULL, 
            0x230D6999F11DD003ULL, 0x35EC739F850D0698ULL, 0x5511F2C9A44DCABEULL, 0x61A3ABF658126228ULL, 
            0x23C1751F490AD4FDULL, 0x7DDDCD6624E0CF6CULL, 0xC6CE49F11D23979FULL, 0xC679F91F1751C80FULL, 
            0x349162E072ED21E8ULL, 0x0C624A7F32300BF5ULL, 0xB25DAA531B99F4C0ULL, 0x6B34E36E9D0FF063ULL
        },
        {
            0x84E8D719493AF8EAULL, 0x3F6F60C7D056D26AULL, 0x7A94B8C0A6C5FEF9ULL, 0x2FFEF61E118AB070ULL, 
            0x40C39F1DFB456C79ULL, 0x3A63DC87D841A525ULL, 0x338064F216CFB5CEULL, 0xA3A27FBF778684C9ULL, 
            0x168183EDB9CC37A6ULL, 0x833E914D83059BCBULL, 0x66A44321544DB688ULL, 0x27128332790CC42AULL, 
            0xB954B2C8A039CF85ULL, 0x22BFF4CCA943115CULL, 0xFC13874C73974DC6ULL, 0xD32EC893826D849BULL, 
            0x2A3303BBAF8D030FULL, 0x51F6091F0D7759EEULL, 0x5F874A277192940BULL, 0xC1572C752C510073ULL, 
            0xD78F599278E7FE40ULL, 0x93826DEA80A85261ULL, 0x373625C0F078C49BULL, 0xB2B995E2E90A8BE0ULL, 
            0x0E8906996F313E4FULL, 0x4F7D87D31BB412FCULL, 0x910CA536317077E6ULL, 0xE014E08B37D0DE0DULL, 
            0xF6B1D69324013869ULL, 0x67CABB9EB5FCE053ULL, 0x93A41EA25E12834CULL, 0xE7B68B82DED5D083ULL
        },
        {
            0xF867EB564E402D15ULL, 0x4294417378C3F168ULL, 0x07280E03D6AF920BULL, 0x1AC1D860D0D5BE60ULL, 
            0xDCC69A65CFB90178ULL, 0x63B10351E7AB17C0ULL, 0xDAB4DDE202EB1E58ULL, 0xF62ED3153886C459ULL, 
            0x78AF244F7A34A046ULL, 0x41B0D267E21435D8ULL, 0xECBA1B5D169123F6ULL, 0x95FAB25E420CF549ULL, 
            0x9FCEA186822C6077ULL, 0xE6B56C6F63F4B1D3ULL, 0xC9534FA123294EDBULL, 0xCC6B487F6042C9C6ULL, 
            0xCCBBAECECD4BD2E0ULL, 0xAA23DC16762A82B1ULL, 0x52E084B3E41C444CULL, 0xD18C50BF28BEAD97ULL, 
            0x112EF2ECE78E5B44ULL, 0x62C745868FB69F2CULL, 0xC5553C5F7E7243C3ULL, 0x04DF1F583C731C91ULL, 
            0xB7F10DFD79A66097ULL, 0xC49AECA624352C84ULL, 0xBB50C56A78DDE225ULL, 0x320C703E59A0067CULL, 
            0xB21631B927E84E60ULL, 0x6F5CF7800AC471CDULL, 0x64EC81EBAFCC32BEULL, 0x2FD03776E2387C1DULL
        },
        {
            0xC996FC4A41239696ULL, 0x9A8B0AC14781DF92ULL, 0x6062332F42431906ULL, 0x8A943826121EC2CAULL, 
            0xA1B0CB4B4BC8E0F0ULL, 0xFA633FD5997C56F8ULL, 0x2DE544E45B01B337ULL, 0x305BAC405894A3CCULL, 
            0x8466ACD3BE2005CCULL, 0x46BD254509FB09EBULL, 0xA37B1E8ED238C417ULL, 0xAA66F4C4B19F6470ULL, 
            0x20C7A9C55BE595FEULL, 0x39C83ADCC6597983ULL, 0xBE2BD32D98F70AF7ULL, 0x45B1F23DDE6B3693ULL, 
            0xA1049102DE188C13ULL, 0x75D07B53765F22B4ULL, 0x97BC0BE31D128320ULL, 0xB4AAC6F060BF6B57ULL, 
            0xDC55493227CC4134ULL, 0x6BFBC4548CD9F1A4ULL, 0x51E659EE1A15A1BAULL, 0xD97931B6F8E18965ULL, 
            0x292FAECE62B5C07BULL, 0xB8C5CC6395F14DC6ULL, 0x2AA961C203017228ULL, 0x87FEAE09E13CE252ULL, 
            0xB4CC1680D88CD72CULL, 0xCF1B72DA4C17CEFDULL, 0x8B284CB31C132DB2ULL, 0xD8F215956511B688ULL
        },
        {
            0x38E02FF3BBE86CA6ULL, 0x27395559559A7ED2ULL, 0x93A4721053478186ULL, 0x3E7B6A2928E215C0ULL, 
            0x95CCB72E35FB75EAULL, 0xDD479B4A6D585DD0ULL, 0x2E05120CBE3FD20EULL, 0x7F521D3CEA8EFB7BULL, 
            0xD5E21EF191325EA2ULL, 0x9B63F13A0FDF9EA8ULL, 0xDD464E765D1A5EE5ULL, 0x596EA99D5F73C215ULL, 
            0x5261844A5555A432ULL, 0x82418CEB2BB55C6FULL, 0xA125531BE86EE3E2ULL, 0xD2ED01CC08FDF881ULL, 
            0xA634CE11AC776CE2ULL, 0xF6F2DB99B8A3344AULL, 0xC03B8E65BF7D7C6FULL, 0xD629AB05E06EA85BULL, 
            0x8DF349741B00386BULL, 0xBB7A9C42D8247EF9ULL, 0x6D2D474165E44827ULL, 0xF7BB7ED903129588ULL, 
            0xE8B99706CE14980AULL, 0xC682F4B46AA19DE5ULL, 0x2AB23EF9B6699A43ULL, 0x65762FFC73F67FD5ULL, 
            0xE88C0BC204CBA3A0ULL, 0x8C801EAEFDFF79F8ULL, 0x2D16FFA14D930EFEULL, 0x7B4D43E5FAC87B05ULL
        }
    },
    {
        {
            0x6B2FDB080725F4E9ULL, 0x8FE941222158E856ULL, 0x619F2256B3376E12ULL, 0x8C1D7FDD7FB86817ULL, 
            0x4539CD78C05DABEDULL, 0xCAF927D950CDA8A4ULL, 0x9DEDB6E8DC0BC1B1ULL, 0x17CCBC1514EB071FULL, 
            0x2E1D32003AC416C6ULL, 0x7186CDAF1922EC31ULL, 0xB179B6433B54D5A0ULL, 0xDA6E9BDF4A266006ULL, 
            0x28BB3114EF9F094BULL, 0x927A4387082AF7CDULL, 0xCD34E7BD07D0BD65ULL, 0x72CB4CD6C108BE70ULL, 
            0xF9489928A75112CFULL, 0xFC3ECD6C641922A9ULL, 0x6B57E29E3C350B98ULL, 0x20949DE61336855EULL, 
            0x5653EAAB6704EA96ULL, 0x1674CC514EB5736CULL, 0x044EDA906C799B3FULL, 0x7255027997ED0C63ULL, 
            0xD43322837F05C632ULL, 0x44A1EF1A7D7DA0A3ULL, 0x5C7859260A90BA61ULL, 0x798EBC558F36F6DFULL, 
            0x0813EBB545D802D9ULL, 0x1509184DF45B8035ULL, 0x91AC99AE431D1B58ULL, 0x0F1CB0CD71C9541CULL
        },
        {
            0xAFCB36922C55E6E5ULL, 0xE5D56A3ED90C1D4CULL, 0x1D6EA2896A4E1D4FULL, 0xBFB511CBB1337E52ULL, 
            0xECDC1E85DFF3D176ULL, 0xCA757029B6BDF910ULL, 0x962B3D5637233971ULL, 0x94AE8CAE03868571ULL, 
            0xD141A0A50AAC8ADEULL, 0x449494BA634A1397ULL, 0x933758DBF392FE15ULL, 0x2C42CC8CBC427C91ULL, 
            0x7A16FB808D51FE2FULL, 0x6FFC321094F0CE56ULL, 0xCF018FD6B77A61D6ULL, 0xD334F0ED4410F6D0ULL, 
            0x91C14F1B10E374C1ULL, 0x4F9195BC40FDA25DULL, 0x9488EFFB0CFA9AAEULL, 0x1B116F56C8363B8AULL, 
            0x266D45B66B5589C5ULL, 0xA2A8DAB14451AFDEULL, 0x33B9F25809904995ULL, 0x3A9499174EB4B952ULL, 
            0x3EF45A64574A31AEULL, 0x34A67DC551A845D4ULL, 0x9564EDF34D3C2CAEULL, 0x687750068B42D346ULL, 
            0x5E96FEC4DBF38F3FULL, 0xA84B14374D0F8E98ULL, 0xD733B8395888393EULL, 0x140691C381B98ED9ULL
        },
        {
            0xC32A46258C55C170ULL, 0x8EA86F43C312C0C6ULL, 0x6E31AB865E3E1FDDULL, 0x1FB8C94D02ECE5E0ULL, 
            0xAE8DAA9DAB02B2A7ULL, 0x0B8A7BCF87FA47A0ULL, 0xDE06CDE0464873D8ULL, 0xF9F5095A8D5DB877ULL, 
            0x516125E9B3E0DB31ULL, 0xE4C8EA85DBD4CD36ULL, 0xDB867BD01DF2DB7EULL, 0xC7479B0C4DDE447BULL, 
            0xC6417E2A8EB2E07EULL, 0x44A72CBF51F4E7BCULL, 0x90B75FA72BAE7FC8ULL, 0x7D14CE6DF4214A60ULL, 
            0x8364555820C36A99ULL, 0xEC3355C6EA019D59ULL, 0xDB415DD4B6046826ULL, 0x88FF83928994ADE0ULL, 
            0x01F211DB7FFDF87DULL, 0x0FEEF771E4573CE2ULL, 0xDB3C5096FC596291ULL, 0x4DA4C609C59100A5ULL, 
            0x328D804256FA60EEULL, 0x8F11DF38A558D231ULL, 0xEFB8555E72856AD2ULL, 0x43A1A7278865591DULL, 
            0xF5988165D8204CF7ULL, 0x77C363D156DD0BE6ULL, 0xD7110EC8DE3F7ACAULL, 0xCDA3F29D2D61693EULL
        },
        {
            0x1520EE32B3C39273ULL, 0x4C0FC1A2A679F4A7ULL, 0xDA331C525E4D29B8ULL, 0x2EB1B1E06A0FBD21ULL, 
            0xA4C024B3B3D7CA03ULL, 0xF0EAF6DAD8C5DE41ULL, 0x3A5A742D6F1BB289ULL, 0xCC95FEBD49A47117ULL, 
            0xDFC721A42C1E6301ULL, 0xCEC45C26343930DBULL, 0x1D02FDFD7033DBB6ULL, 0xDF0F2E88DF50CE33ULL, 
            0x7C759BEC7E0AE424ULL, 0xDFC827620AEFD7CEULL, 0xDF8CEECB8146AC66ULL, 0x039B77F24CFC912FULL, 
            0x4E956E556A170FE9ULL, 0x5FF719A67FC776BDULL, 0xD25BED68B9518FF9ULL, 0xB8F906FDC88E927DULL, 
            0xDE726C7AE53FBBC2ULL, 0xCD39217AAD4A4E72ULL, 0x9B6311E765176B2CULL, 0xB9443EC80C3A8AFEULL, 
            0xB6E8474C6B3C071AULL, 0xD7DCB87070C8274BULL, 0x786160B5239B9CACULL, 0x94D30CB9C3BE3B16ULL, 
            0xECA49A69C773907BULL, 0x9E4B981DB4B6DD6DULL, 0x9DE7E0309D18AB5DULL, 0x83EE1ED66CC6441BULL
        },
        {
            0x41D438401E10AB6BULL, 0x81D598537E80FED5ULL, 0xBADF89515304FC65ULL, 0x867BE2983CE7C869ULL, 
            0x23C4C828E902A3F1ULL, 0xF6D7223E88DDC765ULL, 0x1388DD79D896B24BULL, 0x367C28F876CE8015ULL, 
            0xA3C76DC9B8214219ULL, 0x355FFEC8C9C4DFD2ULL, 0x4F8AE39D6EAB3695ULL, 0x2FFBE579B81B0F3BULL, 
            0x1841B185ADA5E06BULL, 0xD35BF0DFE3C15F86ULL, 0x65BCE51EBD129BD0ULL, 0x279AE68A315FE7F0ULL, 
            0xA4752B2101E9A2EEULL, 0x95E50CE4B4B6B71BULL, 0x06392D831EB638AAULL, 0xFD23845558ECDD9FULL, 
            0x58F78C9F061B270CULL, 0x1F0E1DF23D4FDB68ULL, 0xF333069A1B093800ULL, 0xD594DA044B185382ULL, 
            0x3B360D4533319171ULL, 0x55D58FF89CD53243ULL, 0xE7C8F78D9BA7284AULL, 0x1C820A1085FF1C0DULL, 
            0x20D44C971FFCEA49ULL, 0x157A936C2B05D21AULL, 0x5C85DB8DA37E028BULL, 0xE2F3DB1FA9A0C2FFULL
        },
        {
            0x65B93C058D8AAD32ULL, 0x8F4ECB8129BFE4B4ULL, 0xD81C39842AA48B67ULL, 0x1C6F95F2E14DEB00ULL, 
            0x091F12E0856CBAA1ULL, 0x816FE9BA39FD1E09ULL, 0x0597EA5C77D26573ULL, 0x10590F5E8DD913E9ULL, 
            0x363E0A19A4DA5E55ULL, 0x1E9E7CB0FB4E0C2DULL, 0x60F2236812DEDF77ULL, 0x381EEC848683C115ULL, 
            0x2CC6AEA88F7B6441ULL, 0x126769361D707336ULL, 0x5FE7C6925EA71732ULL, 0x3A340A890AD0528BULL, 
            0x95CC172C54D1568FULL, 0x0922D7ACAF5C66BBULL, 0xA4606A5E17566BCBULL, 0xB3686ED881115CD3ULL, 
            0x533934952B6112A7ULL, 0x452488868D026D13ULL, 0x8DAEA66EE65820D5ULL, 0x5126E4A055ECB6DEULL, 
            0x78E84706C4F8B732ULL, 0x72E5F8DDD400D446ULL, 0xEE6E70996CD6B05EULL, 0x95670801902C7900ULL, 
            0x210ADEF711D13681ULL, 0x2BB7064EF0DE8441ULL, 0xBA46D0D23FD755AEULL, 0x88AD9D23A3D0240FULL
        }
    },
    {
        {
            0x410E534D3A4E2636ULL, 0xB8B9B992362E063BULL, 0x83CEB1940E78F8BEULL, 0x03DA496FC256861FULL, 
            0x30B1E9F8FF12932BULL, 0xDCDBBFE59B4E45AFULL, 0x39A50938B2765B0AULL, 0xC3A189ECAA52D2FEULL, 
            0x0AD3F4B672AE0208ULL, 0x4602F177F31981CFULL, 0xE833AE902A99A6BAULL, 0xE1BC1F6C515DB376ULL, 
            0x587D9D9CE62A6DD9ULL, 0x1F00A061477FCFB8ULL, 0xFA89BF58851A53C4ULL, 0x1B6131BCD6BDD811ULL, 
            0xAB1AFAAE5CB321CAULL, 0xEE79D1C9E5DDBEC1ULL, 0xF62BB6F82237A16FULL, 0x44C62F0DA464B1F8ULL, 
            0x57CA80244DA4D9DBULL, 0x526C322963626A5DULL, 0x079B466787E90C31ULL, 0xBAA5F5F713666F03ULL, 
            0x06A6A65EDF67C6E7ULL, 0xB3BF1511ABCC17A9ULL, 0x124D9A2216DDEE3BULL, 0xBF922A8C2B1BA794ULL, 
            0x3A7BBD786B128D82ULL, 0xCB79DE071EC7CAA1ULL, 0xEFAF6A18F6B5958DULL, 0xD5173B656895CB7BULL
        },
        {
            0x78FA2A72B59ED6E4ULL, 0xB5367DE878FA92C2ULL, 0x16DD25E582DA2DDFULL, 0xACE3D06911CDEDCCULL, 
            0x9D1467A9AF76E93CULL, 0x67F7B12E31392005ULL, 0xE7CF70D823C59B97ULL, 0x70C21B10DFDC4BF5ULL, 
            0xD961D57CF8340213ULL, 0x433F4E30B48E5B03ULL, 0x4E88CFCDAE23570AULL, 0xC213CA8703AF4F80ULL, 
            0x012974038FEFC990ULL, 0x1E9D377D83400534ULL, 0xAAE27E41DFED368CULL, 0x99CC42E45D6AC4DBULL, 
            0x3B4278879A3A43C9ULL, 0xFF6109EFF19A1A8DULL, 0xF07D42602B88FC21ULL, 0xC2D91C674D447D34ULL, 
            0x10628D4142F438E4ULL, 0xE48BDBFC07DD214BULL, 0x10A63D5565A35EF3ULL, 0xC1146EEB69793BFFULL, 
            0x8E9AC493D178F3AFULL, 0xE8E78DECC6878AC1ULL, 0xD15AE494B3863968ULL, 0x9548490D17DE4187ULL, 
            0xA665B5571CB91522ULL, 0x93121F0AB7503F22ULL, 0x4C0A8A639F16FF56ULL, 0x059BAF4DAEFDBD04ULL
        },
        {
            0xDDF5533A351D3456ULL, 0xA4B61ACB0D6C90D2ULL, 0x0AEA31B7E9102F19ULL, 0x0D12526A1389C456ULL, 
            0x29194E32F9E79B31ULL, 0x8B1A23FE2815B2B9ULL, 0x3DF9D5C4B2552D7EULL, 0xC2107482F13F75C1ULL, 
            0xFD51C5507FCC6B51ULL, 0x46C63E088CFBFD4AULL, 0xADAAB9FB2AD514FDULL, 0x5BC890D4D3729CA6ULL, 
            0x64FEBCD53FE3324BULL, 0x1ACC04ED95F6881DULL, 0x6A203B5EA496B7E2ULL, 0x9CE9A5698541D774ULL, 
            0x27E0666A67D0E30AULL, 0xCE98E82969962022ULL, 0xC3D06114F407DB37ULL, 0x1EA57FD45FA7648FULL, 
            0xC61D549679FA2DFCULL, 0xE51DA00DEBA311B0ULL, 0x278997146CF27B0DULL, 0xA436F2DB51F5208CULL, 
            0x6BF9CA75297F3EFBULL, 0xB1454609C4E65771ULL, 0xA905375B6123E6AAULL, 0xE65E5FBEB9A4F663ULL, 
            0x37701C76ED2F82B4ULL, 0xB0A2A728E222AD86ULL, 0x03F3A443C75C39C3ULL, 0x218F6A0518E4BBB6ULL
        },
        {
            0xC9E90E7A88503536ULL, 0x83F57BED33E007EEULL, 0x4291069471EC6B5EULL, 0xBA30491014BB0F93ULL, 
            0xA0841B6069098F82ULL, 0x132B7CFCBA7F0A1DULL, 0xA34AB913847433BAULL, 0x75114FE59FE463B3ULL, 
            0x21D7E1E1D2B2EDCFULL, 0x7A216E7A2161CC55ULL, 0xA18C875011B660CAULL, 0x348ED032851C2F69ULL, 
            0xCFE05367D65AA282ULL, 0x8069DFCD2AD5A2DDULL, 0x842D3EC8B39C0F9EULL, 0xFF9A6B734A345503ULL, 
            0xE8AEBBAA978C6D79ULL, 0x821AB178A0F948F6ULL, 0x726E0109F9E602BDULL, 0x2427B9F87B56609CULL, 
            0xDFC3D5550C60B329ULL, 0x0A43D1C272CE8679ULL, 0xB9F3F5C215E2A497ULL, 0xDA383B5FCE715998ULL, 
            0xB3A9872FFC125093ULL, 0x8A3C64A58C030FEBULL, 0xF08F3D299C21AF99ULL, 0x94E554B8A9408653ULL, 
            0x24FD18C0AB0644E1ULL, 0x692311B04C89DAFCULL, 0xB693370486E38F2FULL, 0x658048C87CA815C7ULL
        },
        {
            0x3C4FAB736BC9F6A6ULL, 0x880227BEB1418A3CULL, 0x8F30C77B601F907FULL, 0x7F0352C4092F62E0ULL, 
            0xECEA74C0ABCC7166ULL, 0x824B75FEBF406D59ULL, 0xE08ED9CDB3FB5F87ULL, 0xD5CF3844A69DEE7FULL, 
            0x754B319E3EB16B60ULL, 0x7D86E9E879176E49ULL, 0x7530639CBF888BD7ULL, 0x5F491368203DF72CULL, 
            0xDDB116C306537FA7ULL, 0x2DA7D684CABCED1EULL, 0xC48F2547EBB89669ULL, 0x4F7873A1E914CFF2ULL, 
            0xE58AA09A495D286AULL, 0x592F38093661B95BULL, 0x36A5E7D66C5EBBB9ULL, 0x39B28B7E003A54D8ULL, 
            0x797085F53D9A67F6ULL, 0x70AC43AD7A965603ULL, 0xDA80A4B60E67EA5FULL, 0x3D7E148A0CADA8C6ULL, 
            0xDA34B4A267FA617EULL, 0x186E7F48B3BF961FULL, 0x55F95882242486D0ULL, 0xE0A233ACCF28E956ULL, 
            0xC0D6D45487FD9A77ULL, 0x5BB51F536A5B48B1ULL, 0xD1777180FA65B71AULL, 0x29A05ED6C51282A6ULL
        },
        {
            0x5042CCB7D8CB900AULL, 0x6314444E99676EB1ULL, 0xCDB054FFAB5656AFULL, 0x18D92BD2B76BE5D6ULL, 
            0x64DC03F9A4B0E6B8ULL, 0xC4E6C0736BC1829CULL, 0xBA16F04AB72E35F3ULL, 0x44318ABE55B06F30ULL, 
            0x2939E946E2F2F683ULL, 0x7EDA2A3C7705A7EFULL, 0x86AF288F96E0212FULL, 0x0CCD2B4FF5E802D5ULL, 
            0xAF9E120503ECE0FAULL, 0xC0BA7FCBE4F460B2ULL, 0xAF4BF827387B17FBULL, 0xAF2BC62982558CB2ULL, 
            0xF7B0F1F8B821368CULL, 0x077BACF5E31098FCULL, 0x7387C982AC304EE6ULL, 0x2ACFC12859C73A0EULL, 
            0x1E353C594519E3FCULL, 0x5A80D158009AA0B6ULL, 0x584F8B18122AB132ULL, 0xAA767A05670A04F0ULL, 
            0x7959DFFBB3A95FA9ULL, 0xBD0FB2C41E97BB60ULL, 0x31F42C1605F8224FULL, 0xACE72B14313158D6ULL, 
            0x353C6B54B9815DFBULL, 0xF050670BC79E6FAAULL, 0xBFCCA1FDC5BE6022ULL, 0x1BD89B8FFCAB1740ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseBConstants = {
    0x29B6A7643FA88220ULL,
    0x182200788A1A070DULL,
    0x1DC508BEB292C18AULL,
    0x29B6A7643FA88220ULL,
    0x182200788A1A070DULL,
    0x1DC508BEB292C18AULL,
    0x7ACDB9CD6FD99F2EULL,
    0x1C2B177CAD6ED210ULL,
    0x8D,
    0xDB,
    0x1B,
    0x5E,
    0xBD,
    0xA1,
    0x78,
    0x5D
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseCSalts = {
    {
        {
            0xB239CCDE6FD0D30BULL, 0x2C71229C98FB6B66ULL, 0x2FA493E1825D1599ULL, 0xC16B2496E930643FULL, 
            0xE9D3FE3A33647DEDULL, 0x3ECC2DFD265AB799ULL, 0xC97A022DDA781ADEULL, 0x88EACDC2EA4C4D04ULL, 
            0xBA994548B5101B53ULL, 0x41308A7B6FDFFDEAULL, 0x123FB882AF04BB82ULL, 0xD8B2070F557E37B8ULL, 
            0x6D9B44D988CBE952ULL, 0xF5CAF9E835018626ULL, 0x247486C47D976F48ULL, 0xFEBACE7BD4D07EC6ULL, 
            0xFEB7A37D5A29B139ULL, 0xF41CF4D0DF8C5784ULL, 0x8CBAB6BD9867627BULL, 0x3E79010A485087EEULL, 
            0xC6AE309FDD6883DBULL, 0x291F84AD585C1B99ULL, 0xD8F010FA674B3F4FULL, 0x2C14D9B05EB1DD26ULL, 
            0xB912FFCF70BDBC92ULL, 0x0AB00C694509F7D9ULL, 0xB0E87AA5EE104DF5ULL, 0x00AB4F3D5E2D7F49ULL, 
            0x33620B94BCA8BA6CULL, 0xE94725048652474FULL, 0x80199DD9D2AEDA3FULL, 0x1EE318968FEC5167ULL
        },
        {
            0x20885EE73534174BULL, 0x46056866B9EDC60FULL, 0xF1F4BCF064E8B424ULL, 0x6230D79FE98AEA20ULL, 
            0xF9171FA35FBFA643ULL, 0x5DFE6F4DF614E161ULL, 0x0361D62C9385C011ULL, 0x6B3D225F61CFE859ULL, 
            0xE9A2BC1D72783A08ULL, 0x05CC23911F4E5E5AULL, 0x718A524AFD764F8AULL, 0xBFC3A1B2189BF9B9ULL, 
            0x0A16F80D3B782EC4ULL, 0xAA56A0846E0C680BULL, 0xCDE6D5D7DADD1AD4ULL, 0xE58062FBF45E6786ULL, 
            0x102629D77C19AC9DULL, 0x33CA862E1D91402AULL, 0x0E949E4CB0084CEEULL, 0xAEE84F0397E60483ULL, 
            0x66C9CBDE8EDDF777ULL, 0x0CB2193820C93163ULL, 0x59AD3DC6D7A79465ULL, 0xA14D641C1A119419ULL, 
            0x8B737A4F8B522C0DULL, 0xB701F1D14E21B012ULL, 0x3110CD86E7671E2AULL, 0xCC10C439B0EE6D6AULL, 
            0xD6B1C1E045916E39ULL, 0x98967835010C8D6CULL, 0x836FF95C29C5B0ECULL, 0x6C5C85C2B2CBE2CAULL
        },
        {
            0xE6F82A929679154FULL, 0x63CC3E7DE9872D77ULL, 0x304870B8C1F676BDULL, 0x7677B52B6E45222FULL, 
            0x3779B8103DAC80A4ULL, 0x3F96CD6D9E670126ULL, 0xDBC4B50CACE9CD62ULL, 0x335F65FADFA863E0ULL, 
            0x2409DD3DE0374A41ULL, 0xF6C07D7CA05B813FULL, 0x16D332FCEB83A602ULL, 0xB10E8DCC65FE6D5BULL, 
            0x17B05F4C4095A064ULL, 0xD8AF8E47E14F0E36ULL, 0x89E1E8490DC30257ULL, 0x0413CFF0BB29F6C1ULL, 
            0x1EFAB2E2FA59FC4FULL, 0x1DE8E7957F098056ULL, 0x78DD6B8F59F35A72ULL, 0xCBC90566F75723B2ULL, 
            0x021AC9CBE85CC247ULL, 0x3635B0088E80A4D7ULL, 0xC017E120AC332DB6ULL, 0x7BE241D585BE1991ULL, 
            0xDC2B4A02FC1AAB9DULL, 0x2846D9249F8A0B33ULL, 0x9264637666645074ULL, 0xEA614D5870DB6D78ULL, 
            0x7A29E8C11230C73AULL, 0x725FD745BEA51FA2ULL, 0x743F36B9EF6C9625ULL, 0x3B541368B4ECA515ULL
        },
        {
            0x9E39853295016961ULL, 0x10EA2D85FD912C20ULL, 0xD1E36FAC3523A59DULL, 0x5741A0447825C37EULL, 
            0x8F07BDF6B1083DADULL, 0x6C0E2878DEEC80DEULL, 0x916928F31EAE8474ULL, 0xDFABFE5CA993BCA5ULL, 
            0x2D8ED2B0D3CCB6CFULL, 0x942ACACC3C23AD14ULL, 0x004D082F1A6FECC2ULL, 0x36D4CA0944A3E9E2ULL, 
            0xD3A1E23A08B8FA26ULL, 0x2F489A1F786FE498ULL, 0x738409A1E2341FC0ULL, 0x3845E0D4D23B395FULL, 
            0x430462291106ECE9ULL, 0x7E40F1BF0623D976ULL, 0x7E5F665B43D0C6F2ULL, 0x92580327F829A09CULL, 
            0x714C1491A21EDD97ULL, 0x7DC062303F6884F4ULL, 0x80A03B69428545D4ULL, 0x99EB05C978230181ULL, 
            0x131A47299F43D3B4ULL, 0xD061FF82F6CACF2AULL, 0x1B14495578ECF979ULL, 0x2A1C1144890D3A41ULL, 
            0x3DD3CB59C6EDCCC1ULL, 0x7EA078C8E1B95079ULL, 0x120E3517F19A5357ULL, 0x6374B6A26F403CB1ULL
        },
        {
            0xE83D46227C8085D4ULL, 0xB98E1E23F185217DULL, 0x52CD99C2E03C7157ULL, 0xC72897CDFF4EDB69ULL, 
            0xF33E355B00D49A4EULL, 0x744B259E83A4865FULL, 0xD708B440B8F189A0ULL, 0x3271B1F15AC8E98DULL, 
            0x3A8CE9F217D93C4BULL, 0x6735772BFD94CE30ULL, 0x5B27B101D00C7F35ULL, 0xB686A75DE23E8AD0ULL, 
            0xE7729E640F53D3E6ULL, 0x4892EBFF37C418D7ULL, 0x2EE0F385F0AEB6BFULL, 0xC5B6F8CACC0729E7ULL, 
            0x6EA572247522E569ULL, 0xC19BEFDB0367C9B5ULL, 0xBC15EAF1524F6568ULL, 0x08A700BD86466158ULL, 
            0xFF211A81C9D972B2ULL, 0xCC0E14C5A3448E5CULL, 0x92531D8C861295BDULL, 0x4EBFF0D892BA765CULL, 
            0xC1861E078A898831ULL, 0x684B6EB0334F7720ULL, 0xF4E9DE33B177DB59ULL, 0x982F124D165F1223ULL, 
            0x2D9DFA1B58AC4593ULL, 0x557060B3E5C722ABULL, 0xCA3317C5B61211F0ULL, 0xD346A42551BCE912ULL
        },
        {
            0x1188B5E2944F3E63ULL, 0xE70A479459D6F036ULL, 0x70BE953C876EBF33ULL, 0xD475EF82CE96C705ULL, 
            0xB1B6083C184484E7ULL, 0x3AF7C20C62DBB2CEULL, 0xBE0D36D0426B9F47ULL, 0x86144E0CAE86DA3BULL, 
            0x4808B9EAB9C83B4CULL, 0xB867D0C4C4D01271ULL, 0xAF0CF51F5C542C8EULL, 0xE7C409F1F797E9B9ULL, 
            0xC38EA8C6FB360C51ULL, 0xB6079798E078B866ULL, 0x5BE4E094C6DE1BB8ULL, 0x0A385A6652DA1916ULL, 
            0xEA49759F03CF46F9ULL, 0x03180E63D1B65272ULL, 0x05C65AAE7E726303ULL, 0xFEADCB30C52BC720ULL, 
            0xD611584C991D876DULL, 0x0BDAD1CF428857ECULL, 0x63B6F9B7A28C4BEDULL, 0x1A69DB2BE1CFF155ULL, 
            0x7AE79EFD6C334B30ULL, 0x2D9F8D215C588996ULL, 0xD1B90A03D1D12F9AULL, 0xDDD6B92CB61EF06EULL, 
            0x49AE8C3DF60DF1C5ULL, 0xA7D65447CDD6F450ULL, 0x5AA91125F839ED14ULL, 0x16189AA4A2D91113ULL
        }
    },
    {
        {
            0x48F82C04857EB680ULL, 0xEE228F7F6EB83FC8ULL, 0x972FAAFFA3F5CC8DULL, 0x9EB293C9B85E1BA7ULL, 
            0x8F027D2CEE5C2B54ULL, 0x207E3290ED27A4B4ULL, 0x648F45D5E760B5A1ULL, 0x63FB118571072C2EULL, 
            0x3CD34D2076733D60ULL, 0x37D7111775ACD682ULL, 0x1459E1AA20108130ULL, 0x27D56DC4D701815CULL, 
            0x9882941AD37113CFULL, 0x3AB1F486DBF36F8EULL, 0xF41AE874F6C67D3AULL, 0xF74E44BEF790AD58ULL, 
            0xDB9F3DC6A499FC8DULL, 0xF48A8D8B9BA27FFDULL, 0x6673C85206A4F45CULL, 0xB3E1C28EB1F6E58AULL, 
            0x9D7151013EDEB4A9ULL, 0xEDC80CD3EAE58136ULL, 0xF64C709B1429B599ULL, 0xCF73031F06DB6A07ULL, 
            0xD662B58A3A819B89ULL, 0xD32DF304563C9DC2ULL, 0xBCA6288C4B26285AULL, 0xF2E0916CE385695EULL, 
            0xCDC2DCBBE47E3C58ULL, 0x2068F7F0882BB6F4ULL, 0xA44F26C22731EA5AULL, 0x32E32583D6862DE4ULL
        },
        {
            0x549B008F0CBA7FD7ULL, 0x0B6B366DC410B452ULL, 0x8F5EFCCA0A1E6D52ULL, 0xA1EBBDBA276AD548ULL, 
            0x7DB8E29D50380797ULL, 0x4FFBE7133A36659DULL, 0x306A003AB588C20EULL, 0x1333765A03AC1AABULL, 
            0xEFD06E5E52B87F7AULL, 0x023C3B7D5A55AF06ULL, 0x6A4F6363733C6A9EULL, 0x310299E2CAC978B4ULL, 
            0x1D20BC9F7BF09FC2ULL, 0xF45C320215A5B6ECULL, 0x7EF6B4D4C81E9284ULL, 0xDFA1FAC7AF9565F2ULL, 
            0x0169B81046F663FBULL, 0xEC8E73DE21609BF3ULL, 0x951A817519EE554CULL, 0xF27FD12E7EE7CAF1ULL, 
            0xEDB84A0C153C65ECULL, 0xECE1E9EB14476D39ULL, 0xB65843C5CCA5D8F0ULL, 0x1A96DB9B3BE20C84ULL, 
            0xE8DD413B54174F03ULL, 0x0D063FE7CC4C452FULL, 0xA82BDFCBA0938353ULL, 0x01BBF02238F5671AULL, 
            0x5DFA520AEDAD2038ULL, 0x6F590D889E0F8FB4ULL, 0x6235840E96623BFEULL, 0x8BABB05E66044B90ULL
        },
        {
            0xCCF28338DC741CB9ULL, 0x0FCDB41CAB3901B9ULL, 0x6BEE0153CF841B73ULL, 0xF4F7E09EE82D5446ULL, 
            0x6CED92DE6AF8B438ULL, 0xA44B739E73D27486ULL, 0xAACF441CB2CC9FBDULL, 0xD16D2C475710E68CULL, 
            0xC981A2B9F66A865AULL, 0x4EC6A5125CD2D85AULL, 0x64883D392069BE82ULL, 0x64AF226CD3B49F8AULL, 
            0xBF6CF3CE5F94480CULL, 0xA44FADAE6CF4DAD5ULL, 0x6DE7989ABDAD9520ULL, 0xB2229C429A4C2A4EULL, 
            0xCF5627D01F00A1F7ULL, 0x03882F346AE3349EULL, 0xDDA6ACB2A1F92CDCULL, 0x0FBF53C28F392962ULL, 
            0x4CCD366C0E418950ULL, 0x7C4DBDC05AC2C7DCULL, 0xA20D9347E9C83772ULL, 0x5C0BBFB92D18D88CULL, 
            0x776869CA12B70611ULL, 0xF02BBA9205541BA4ULL, 0x9DC1123BA9D21E86ULL, 0x7E3B98E7FC968452ULL, 
            0x6C453D33024AD413ULL, 0xB822638794DCB603ULL, 0x9FCA5D09F478FE21ULL, 0xE0A2FF39BD0BF841ULL
        },
        {
            0xD6EFC8B2E5AAFE95ULL, 0xB193C761F7BC38A7ULL, 0x5F71DD1656D63E38ULL, 0x36299EFDEEE9D6ABULL, 
            0xF40B0DF6A3084CBEULL, 0xCDEF31C6C86A1ABEULL, 0x7591D7FD2527F0ABULL, 0x86588F5870C28462ULL, 
            0x7D091A60A448F791ULL, 0x00BBCD7E0B634997ULL, 0xD84B6C866C936F7DULL, 0xCB8B0B6387FD1A41ULL, 
            0xD23A173F0C2A059EULL, 0x70BD20690AAF467DULL, 0x3A6865081BA50F87ULL, 0xDCBCF26A66F635D4ULL, 
            0x2E51C26AAE9ED9A3ULL, 0xC02C444DA29A7F49ULL, 0xCFC23F068C75A7B2ULL, 0x6430FCB4A0984F8CULL, 
            0xFCB3BB8447DB2CDFULL, 0xD555D4EB86E5E4E4ULL, 0xE4B6C8AA6E1C5C4AULL, 0xF57D84F3843FE23EULL, 
            0x660D944273D4866CULL, 0x8A522DA0D6EB837BULL, 0x8BF46F72FFFE36A0ULL, 0xBA947353ED241263ULL, 
            0x3D6999E908EFD93DULL, 0xD0477DAD7CA00F0BULL, 0xC3C8C0275801E2C7ULL, 0x40D228A3CC67B7DEULL
        },
        {
            0x2B492D387464A102ULL, 0x033644720E128722ULL, 0x2D7343821B0452CEULL, 0x11685C000C0F74ECULL, 
            0x91DDC612504254C1ULL, 0xC6930F01B5D001C3ULL, 0x141B192A1F32E299ULL, 0x7A6AA6491A9D56B7ULL, 
            0x697113112C7DBC27ULL, 0x77E65057AA86CFBDULL, 0x3F7D1DC29FA4AD06ULL, 0x5B8D0ED6067D41D3ULL, 
            0x089A5CF0B31F8571ULL, 0x16A593CCA5574B74ULL, 0x18535111BFC2EE55ULL, 0x9306C2D9C8297547ULL, 
            0xAF6C7FB11A24E1AEULL, 0x238BCAF27A53845BULL, 0x421B437684377B29ULL, 0x0F8A350D18114C2CULL, 
            0xAF0CB769A89C361FULL, 0x5E0075D47FAADED2ULL, 0xDF2F4ED5E8DC72E1ULL, 0x4C8B3F035B28750FULL, 
            0x4BA2351C2484E60DULL, 0x7D4A63A8E4564B67ULL, 0x6CDEB3162D3C7CB3ULL, 0xADB8373E0BA9A2AFULL, 
            0x5E743B6A7DE33B60ULL, 0x303C45C907D97ED3ULL, 0x6B75D8B8ACDF9B98ULL, 0x68C2D268BC041231ULL
        },
        {
            0x1CEE7BC098144467ULL, 0xD6AD3EC0786A4EDDULL, 0xC77CA10835EB0E35ULL, 0x91986664056280D4ULL, 
            0xE29F73BEFF193958ULL, 0xA754C70566EBA34EULL, 0x73305AEB7B2BB67CULL, 0xE158A0DAD66BF135ULL, 
            0x23465B7D82B30B74ULL, 0x7E07A6B986C9AFAEULL, 0xF43C752702F250C8ULL, 0x407E2022B76CC210ULL, 
            0xD4990EE19ED2D87AULL, 0xAF676F6B63D45F82ULL, 0x702DC5360C028165ULL, 0xE17A562FA9873A8DULL, 
            0x6BA91CE31F05CFEDULL, 0x6939BF90250A134FULL, 0xB79D905DF02A10FAULL, 0x69AB6A2BD84D8212ULL, 
            0x14EE4FD987858B7AULL, 0xDF54D12D4DF5A423ULL, 0xBA625854EAC657D2ULL, 0x5AD2A7CC86769B5AULL, 
            0x7FB6CB2E72546B47ULL, 0xB6592FB505C91138ULL, 0xD1834F425FC37B26ULL, 0x2A38F5593D9FF210ULL, 
            0x4C53F527E897756EULL, 0x2302D4C6792CB3CFULL, 0xAF693FAE6B949C36ULL, 0x537E7EA63FA73748ULL
        }
    },
    {
        {
            0xBB0B7C8F2A573443ULL, 0x1008D82536C744DCULL, 0x82F1B47B334F309EULL, 0xE4B849990EB5EF64ULL, 
            0xEF7E351F06AE9E67ULL, 0xF15787367157A97FULL, 0x3D0FA1DE8EFF0D68ULL, 0xC51B339B4F721757ULL, 
            0xDEF9BCA393F9778CULL, 0xB69FE3726C40BF5BULL, 0x2F459E1517580A5FULL, 0xBFB8C248B281D9FAULL, 
            0x9677A3388869304CULL, 0x498C7B17B6F99F6FULL, 0xD1E31F0AEFF63519ULL, 0x97446E000F09D602ULL, 
            0xB3B09E0AE5C29048ULL, 0x28F21A4C398FC1F6ULL, 0x97FA88B527E3CDE2ULL, 0x47E06C766937B68BULL, 
            0xB11BA4E9386D0667ULL, 0xD12AC988EDD41620ULL, 0x87900A76D5C21323ULL, 0x3EDC7BDB2E0C9868ULL, 
            0x312CADDD1FDDC0D6ULL, 0xC69E219F29E24BD8ULL, 0x952B668344A933A1ULL, 0xA9EC32404FE6CE04ULL, 
            0x1B522884FD47E371ULL, 0xF11D243EE9763EB8ULL, 0x544965DA53332226ULL, 0xD2BF6B469434AF05ULL
        },
        {
            0xEEEA28C83D500B30ULL, 0x19377A2D3B3D098AULL, 0xB458B5523F5DFB44ULL, 0x0D8B19ADADB8DDC5ULL, 
            0xF577EB453BD94CACULL, 0xB8707942549BBEF0ULL, 0x4F37B146C7BFD489ULL, 0x5FC0BEB71D155BE9ULL, 
            0xAB2001AE2562F734ULL, 0xEE3190B2172CA2E1ULL, 0xEAC3DC38AE565728ULL, 0x1186231D04084210ULL, 
            0xCC107EBDAAED6C46ULL, 0x779FE1FBF3B765E4ULL, 0x788D5698613BB64AULL, 0xE97BD2842ABE8AEAULL, 
            0x18CDC8F9875E2E83ULL, 0xE7C7121D2FF04B3AULL, 0xB367AB5E1064F18DULL, 0x77E7A8A4F0B4E514ULL, 
            0x20D66C431539BA3BULL, 0x1FAF5F44842E5ECCULL, 0xC25A8E276901B802ULL, 0xD639C0F9140747DAULL, 
            0x0E1138DFCC256169ULL, 0x21A1EC46401ADAC2ULL, 0x90DD54715B9F7567ULL, 0x0EF8EA88D38DEF03ULL, 
            0x3318D775FEAF1FAAULL, 0xEB36D69A0E7195FFULL, 0x347040FBB62F69DAULL, 0xB00DB6D9B4D79D50ULL
        },
        {
            0x10F76BE6712AFA26ULL, 0x97D43CB4A5237035ULL, 0x00E04F5715991096ULL, 0x4B51E21408AA7B73ULL, 
            0xE143E24301AF6E8EULL, 0xF081DEDA53B95091ULL, 0x628268F0001D5F7DULL, 0x12FECF0DC45CA0E8ULL, 
            0x70A02D659F1B888AULL, 0x12BFF541AE3DD6A2ULL, 0x0FF88D89BC0CC4D1ULL, 0x0ACFB348C5964EE5ULL, 
            0x3563D2F38DAA00D0ULL, 0xA6DE88E6CBE5525FULL, 0xC699829DF5001C93ULL, 0x5AD940AF2F5AE8D3ULL, 
            0xC34A0B7BA308314DULL, 0xB2CC7B5CE04E618BULL, 0xDAADAACCA4512266ULL, 0x2ADD203D0E810FE7ULL, 
            0x528E42C112076217ULL, 0xD012C835071AA880ULL, 0x657697A957A36563ULL, 0x906FD123075AB6DAULL, 
            0x7E8950465D43DE50ULL, 0xBB8DD599E17B86FEULL, 0x01C0419598C21D1FULL, 0x9974762BF79F93C3ULL, 
            0x2EA604DFF69F37D8ULL, 0xCF484DE004ACC99CULL, 0x73A611E2EB2585ACULL, 0x84731168A8CD2020ULL
        },
        {
            0x0BB8A672078369C5ULL, 0xA757AD50F367AFB1ULL, 0x269907AF95210D19ULL, 0xF4772C10C844FF76ULL, 
            0x943BCEAF3D391AB7ULL, 0x74BDED71104C4A10ULL, 0xF8F8CBFCF16F66DBULL, 0x19609820C1FE8926ULL, 
            0x9BC3C026EB5F12D2ULL, 0xD1EA62ED129ECEBDULL, 0x0CE95842A4A6ECA1ULL, 0x3EB115C9CF9DEDF9ULL, 
            0xF8F2519E7B73E32CULL, 0xBC26774E06E53C3AULL, 0x85E4743E8DF9AC9BULL, 0xD7DD68387FA73B6FULL, 
            0xFCEF1E4530423939ULL, 0xB7E0F1A13D0C25E9ULL, 0x3C51339E7A2B52E7ULL, 0x0F5D97E25B2284A7ULL, 
            0x479D409C9DAF5ECEULL, 0xC3E5F43425B6859DULL, 0x02D6B5C4107053E3ULL, 0xE6868BF8600877B2ULL, 
            0x01ECB7045A881244ULL, 0x6BBED55EA0781462ULL, 0xC19F2BD2582EFD15ULL, 0x2A8A3F5E07202F6AULL, 
            0x083F03E8B7F94B84ULL, 0x21ECC9A6FECE3AAFULL, 0x8938863B86E3ABF7ULL, 0x6BF695D7ECFE19E5ULL
        },
        {
            0xC5AFDF170682DEDDULL, 0x0E716E1F8A1F35BDULL, 0x790B60C082740EEFULL, 0x701A4DC24E7029B1ULL, 
            0x6EC0F6A94BB9293EULL, 0xB4AF7F86ABE436B9ULL, 0x5713965C1F9DCD8DULL, 0x0F6FEC96E9B58E1EULL, 
            0x311405DDD7E07BA2ULL, 0xDDF818E1E29A31FCULL, 0xF425CDA199771AB4ULL, 0xEE297CF56280DCEDULL, 
            0x3D3B00EDC06CFE8EULL, 0xAFB497BA5A7172F1ULL, 0xA360214BF0B7D40FULL, 0x6D6D3DAC04D86698ULL, 
            0x00DE7DAA8A455622ULL, 0xBA8B1269716AAD4EULL, 0xC7AD368A13947043ULL, 0x532F4BB098324DAAULL, 
            0x7B0D5F0865BF9986ULL, 0xAB3714BCAD0D5678ULL, 0x51A1ACB2AF96F0CFULL, 0x2D2EA91A4CF2A29AULL, 
            0x1E07CED3A306159BULL, 0x2F3F2FA7619D15BDULL, 0x1738EC1E52C01E52ULL, 0xC1E3C6945BBC3699ULL, 
            0xFFC233F4F3DC8636ULL, 0x8FFCEDA9E02CE981ULL, 0x480D373D0C1290D9ULL, 0xA555BE31E63673F0ULL
        },
        {
            0xC9D6E5C8E77402AAULL, 0x18DD6D83CBA1173AULL, 0x0075CECE227F958FULL, 0x54A5CA332A3DFB86ULL, 
            0x21DDCF57FF8F3AFAULL, 0x226FBCEF67A2FDFDULL, 0xD9600A9BA0BDA5A1ULL, 0x2140CC9A7555978CULL, 
            0xAECD8E8C8213361FULL, 0xB0F559220E9323A0ULL, 0x987E988CDF5F500AULL, 0xF0994149E8C25FAEULL, 
            0x5FAD7351667EC932ULL, 0x44BADC22F92F0BBAULL, 0x4777697AD234D74CULL, 0x68CBA74C5DA37D40ULL, 
            0xBAD88FB679432E7AULL, 0x720120FD8B0CDF21ULL, 0x4E7B175E9C4AFFD3ULL, 0x2716BCF705850311ULL, 
            0xD003895E06F0D32BULL, 0xF5C8209106C108F4ULL, 0x5D50B5D246C89806ULL, 0xBF22201C2EC8472BULL, 
            0x8F791468AD487532ULL, 0xF695E7136A47290CULL, 0xD65F7A500E63B052ULL, 0xB52D010E3720FC55ULL, 
            0xBDCC50C9EDC576E8ULL, 0xF2C12AA531268C8AULL, 0xA35DBA422E39D6BDULL, 0x5F018E838EED0154ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseCConstants = {
    0x8ECCF1D3A5E4BD71ULL,
    0x58D91B8FFFE17B92ULL,
    0x58F77C3787E52DAAULL,
    0x8ECCF1D3A5E4BD71ULL,
    0x58D91B8FFFE17B92ULL,
    0x58F77C3787E52DAAULL,
    0xB605CA32758073EAULL,
    0xA12A9FF64B713622ULL,
    0xD1,
    0x4C,
    0xE7,
    0xF1,
    0x14,
    0xC6,
    0xAF,
    0x5A
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseDSalts = {
    {
        {
            0xEB96847EE3661A57ULL, 0x02107C56A19DCD54ULL, 0x9D9B97D72180A35DULL, 0x6D1E73084DE54252ULL, 
            0xADA08FC649B5616AULL, 0x58B1CE1AEFA2613BULL, 0x29CE50E6D41672CDULL, 0x8AD04A18378A41D8ULL, 
            0x6D6F07D1368A4A12ULL, 0x683258FFC5EA1342ULL, 0x86D2B614C669A42DULL, 0x0E7F99839D5AA890ULL, 
            0x0B783587A9BEBA4BULL, 0xF39922E958C3F33FULL, 0xE92313DFC5E77726ULL, 0xECB486C4B9FD995BULL, 
            0xB7D2C6908457D588ULL, 0x6A73021FF63F1BC8ULL, 0xCE06AD55212C0607ULL, 0x37F2462425A273F8ULL, 
            0x7302E88313850664ULL, 0xB6AA7FBF09EC61ECULL, 0x40CDDAA107F5589CULL, 0x3F2F6FE07A545C11ULL, 
            0xDC38E5A632083FB4ULL, 0x30ECF05D2A72D866ULL, 0x292E1467426757E8ULL, 0xDC37D07F0864506CULL, 
            0xF8467EB0DE50105DULL, 0x8DED42E3FF314CFAULL, 0x988BEDFBBD5CE715ULL, 0xCA89967D29827605ULL
        },
        {
            0x55B5296A09744047ULL, 0xBB861796792B93D7ULL, 0xC0322CB970300962ULL, 0xCBB42CBCD773AF9EULL, 
            0x89DF023DB7AD9714ULL, 0xCB6DEFE33B962779ULL, 0x2DB6A2907134E3DEULL, 0xBC2FCACCF6C5E014ULL, 
            0xBE02A8392E79A56EULL, 0x05C8E1270C06CD42ULL, 0x3DC86D3BEB33A20DULL, 0x831D94EBC1B1F7F3ULL, 
            0x5DFFD5DD84477E4EULL, 0x407B4D42FE5F93E6ULL, 0x13FADBD2AE03F099ULL, 0x8B73BE9BF9281BEAULL, 
            0x6D72F07AA7BC1AD0ULL, 0x6552CCF575043BF3ULL, 0x3FC3BAEED3D2525DULL, 0xDC7DA88EDA5828A1ULL, 
            0x5890439705A9905BULL, 0x4B93A34F834C86C4ULL, 0x375B707F95C1A4A5ULL, 0xA9834A13073F90E2ULL, 
            0x6BFC8636CE1810C9ULL, 0x9154C21187483A48ULL, 0x17C587F71B24FF42ULL, 0x6DFE7A4B90F6C884ULL, 
            0x46D8A5C366C31989ULL, 0x09D43A68054CDDAAULL, 0x2653B12F4EEAB8FCULL, 0x77CBE2861A08329EULL
        },
        {
            0x6D29A6DB26F7016FULL, 0x4EEFD917972AC64EULL, 0x29B93286AB71E094ULL, 0x90959084204E0CEFULL, 
            0x5B5D72264A524934ULL, 0x9166D24BC04A542BULL, 0x059BF3EEB08201DFULL, 0x72783BF64B478854ULL, 
            0x6EC583D047FA72CBULL, 0xF6245F680E2974CAULL, 0xB59A058CC53297A3ULL, 0x7DD921D1FCED9D7DULL, 
            0x404E90A230E33B13ULL, 0xEE8B932AF217350FULL, 0x39B229F4563A4413ULL, 0x49F414818773BAB8ULL, 
            0x0336668A6B320685ULL, 0x887670F3C4830501ULL, 0x59A48EDD1350AFAFULL, 0xC236A34C02967D08ULL, 
            0x98BE35628875F067ULL, 0xE81CEC67A8657011ULL, 0x768E9DF6D25563DBULL, 0xDD1FA3BC194D42BBULL, 
            0x8A7FA9CC4728DB02ULL, 0xCA53D9A9FEB2D269ULL, 0x913355FD24A28276ULL, 0x69A748F4B6B2D6D4ULL, 
            0xCB141B6CF962ED60ULL, 0xB453F6420269B941ULL, 0xACD22F5CE9C907A3ULL, 0xE6933E26A0CDD041ULL
        },
        {
            0xE41F2A7CEA9A2345ULL, 0x80306E6815055A03ULL, 0xDD2AD23D965F5037ULL, 0x4E88763B3B71F5D1ULL, 
            0x7D4E01CA2B533960ULL, 0x2808D4E7EEAD163FULL, 0x24A8CB6D884A12D6ULL, 0x05985D1DD1DF1E1CULL, 
            0xD7333D97D9ACB272ULL, 0xBD32A86A68EE4147ULL, 0x48FF1EF42CCA93C2ULL, 0x2AE8818E0CC63022ULL, 
            0x738A7021B30595AAULL, 0x1769C5971641F924ULL, 0x3C71C07B15C08527ULL, 0x5A0D1E484C4F106CULL, 
            0x329651FE06FC680AULL, 0x76C48C438F04BB4AULL, 0xFC46D73832FE2292ULL, 0x82E9B7FD05E629F1ULL, 
            0x9BA6B0EED01134B2ULL, 0x36D8F61EFC65C340ULL, 0x1134328FFC3A0203ULL, 0xA92815E5884289F4ULL, 
            0xA5A0890305F69445ULL, 0x71374ACF24457830ULL, 0xCB0A3C399FDFAAFDULL, 0xD8D668751AAE4F6FULL, 
            0xB5503B23A7615F3AULL, 0xD561FA58AEF276F6ULL, 0x530546C488EB1D2EULL, 0x2868676AB467FB7FULL
        },
        {
            0x2FFEDA016327CF32ULL, 0xCB44A2E38CA55FE4ULL, 0xC424E23FA5CCC83EULL, 0xEA68CC4083552113ULL, 
            0x4FB7C00E436A8F3FULL, 0x7CD8C7C2E3CDB509ULL, 0xBFB269CB0A08F142ULL, 0x0E9AE556D350D793ULL, 
            0x248557996A306537ULL, 0x33023F4AFFA266CFULL, 0x84B7A60F6AEF9EEBULL, 0x6B086E31CA9F5766ULL, 
            0x08E5BFA69EDCB822ULL, 0x75290B1B4C7D3051ULL, 0xB11A9087EDB1FD66ULL, 0xBE08DD3A249DD247ULL, 
            0x48E33A7D0DC8995BULL, 0x1E0982D09D2010F6ULL, 0x420C0E54955C308BULL, 0x4F6760050B1B0358ULL, 
            0xF64E638D77A6881FULL, 0x28BA00ECD16CB18DULL, 0x66079FD12C2E4771ULL, 0x3945E65AC0631C81ULL, 
            0xB1C0AF8640A8EDFDULL, 0xFEFED8D46E8715CFULL, 0x5CFAF8C3851904FDULL, 0x4AF44022DEE202D6ULL, 
            0x9B76394F4D660DA0ULL, 0xDA20AFF5AB2A27D6ULL, 0x7D42615CB5C4F658ULL, 0x5F02F54B32FD4F3FULL
        },
        {
            0xC66D57DD194F40FDULL, 0x7C9006076D343F21ULL, 0xE2F2102A9A7C9568ULL, 0x7A4029286C265BB0ULL, 
            0xFA7E9ED67292C6CAULL, 0x68E1C433B7733734ULL, 0x6B0AACBB4BC40995ULL, 0x6D3FFA0385CFF78FULL, 
            0x83E5E9458089478BULL, 0x573A7AACD8C4415FULL, 0xC0A43F0967637B24ULL, 0xF9F59712DAB09237ULL, 
            0xE57C2BEF83E9DB73ULL, 0x075C95D699D73CF3ULL, 0x2A54C6178B70237DULL, 0xC04B994FFB236165ULL, 
            0x35A1E9B99C053BBDULL, 0xC5FBD9088C95E292ULL, 0xCAA7267E309A3AC5ULL, 0x1CCB9BE93FA52BF1ULL, 
            0xFD8E4E4EC227E290ULL, 0x8CB573D4F3EF875CULL, 0x4A9A06DB889CA1C1ULL, 0xF05A6F5CF3E2BC6FULL, 
            0x07827F1C2331AF41ULL, 0x236CDB94B913F378ULL, 0xA3EFB398EB786723ULL, 0x3EAB07E4A9148B67ULL, 
            0x1490AD0755B051E4ULL, 0x642EF387247F5B9CULL, 0xB1F3FA1BDDBA9AB9ULL, 0x45FDCDA962A0FE16ULL
        }
    },
    {
        {
            0xF662C999BFAC8982ULL, 0x65EFE34CED8C38ACULL, 0x611A0E4C1697083FULL, 0xE4140790538CA440ULL, 
            0x12861279B1FD79D6ULL, 0x5DAB818625CE7C9AULL, 0x17672C6253C07B90ULL, 0x92881EF95B791B9BULL, 
            0x4C4F21F024913D11ULL, 0x72CFD92E8E22008EULL, 0xD55A5D3D947A4C30ULL, 0x0B2908B430DF5B88ULL, 
            0xC0856E196A627940ULL, 0xBCA9542046149E0CULL, 0x1FBFD451E7936EE8ULL, 0x1A0536B92ECFF8E2ULL, 
            0xCF46C9FF1466892DULL, 0xFDC7A86DB6117C2EULL, 0xEF51D2CEDCFB7761ULL, 0x1AA196BFC93AA8F9ULL, 
            0xB640AFE2AAB135FDULL, 0x8E707D55CA73921DULL, 0xC43B4E1C092AE2BBULL, 0xDC708D4CFAE3A68BULL, 
            0xC0EAF277058EA32EULL, 0x032EB086F4976027ULL, 0x23B205AE122DD330ULL, 0xF733DF3D89C6B3B4ULL, 
            0x2D0B3856D5B3666CULL, 0x8D3A839746E47C18ULL, 0x903B10656096D4DEULL, 0x6E784AF94ABE61D7ULL
        },
        {
            0xDEBE50ECBBAAE10FULL, 0x477F6CE4198ED42FULL, 0x756D0666E6633F69ULL, 0x9C892A63ACAA72FEULL, 
            0xDD8DA81B73EF4100ULL, 0xBE029B3F7A3B0A65ULL, 0x88BDE6881E8B56DAULL, 0x832EC6DA225E4A40ULL, 
            0x154CADB771DAA86BULL, 0xDA8056E2E89354E2ULL, 0xDDDA6E5496C03CF5ULL, 0x9EE98A76B859F610ULL, 
            0x0E4E7A0ECAE65099ULL, 0x8B81A86DAF8B38FFULL, 0x86EDAE8A9AB09870ULL, 0xD03AE536DF292C70ULL, 
            0x6E9E60B49C6AEDF0ULL, 0xF5EA9927EF6530FFULL, 0x95786D17A82A2C3DULL, 0x330FB8B395D23C36ULL, 
            0x33721807EFDCC437ULL, 0x1FDFF9E02659D374ULL, 0xF140083E9CD0A153ULL, 0xCE732BEB0F58AC32ULL, 
            0x30624D0D0747B576ULL, 0x4076E7CAE4356BD7ULL, 0xB7D35189407E5A71ULL, 0x2CBA31FE78BAC656ULL, 
            0x78145DF4BF10D751ULL, 0x168208228160B166ULL, 0x6963AD8F2A6A9DF7ULL, 0xD62C2612C949CAA8ULL
        },
        {
            0xE81D14EF3D56BD97ULL, 0x81404CCCFA8CDADAULL, 0x7F0D11644DB22D53ULL, 0x97CB4BF706BBE48BULL, 
            0x5A36A1E1D7753C05ULL, 0x25E7D41D5446CEEEULL, 0x002248EEDA8B7B77ULL, 0xD07EE2635AF8247EULL, 
            0x8F6FB9FC980B2454ULL, 0x2F745B038E906B08ULL, 0x03E50E0C66CE211AULL, 0x2DAED135F128525DULL, 
            0xECEA5C1D099E1539ULL, 0x0DB4D66C160B40C7ULL, 0xD9D9B37FEC37EB32ULL, 0xB4192CE815092A66ULL, 
            0x210D16216F7DF026ULL, 0x21D72E687EA63912ULL, 0xB5F8430BF22C63F1ULL, 0xFC07416B5B3C4C49ULL, 
            0x5FCE0852F96B6F05ULL, 0xC84388917D20EC9BULL, 0x735A86AACFDB6850ULL, 0x1F5CCE103C82EF89ULL, 
            0x9632D8F2F5F83BF3ULL, 0x1D4C5C2C09457AC9ULL, 0xFF617FC1C2819C89ULL, 0xBDAFD97E9AD8BEBAULL, 
            0x1DC3106256FDA918ULL, 0x1AA68B6B209E855BULL, 0xCEF8085267A77472ULL, 0x0C021FA3A18D842BULL
        },
        {
            0x47B00D1C9E582DA8ULL, 0x355F921FA36BBDEDULL, 0x4E8D1EDA699D3B27ULL, 0x06927DDB638F7815ULL, 
            0xB093DC3100B48BD2ULL, 0xBBF28923E2FCDC92ULL, 0xB8B5B8256AF8548FULL, 0xDEB94834305E50BCULL, 
            0x34B57DF9E5B2B7C1ULL, 0x12E85729B138BF1CULL, 0x8A579B7510B56D93ULL, 0x808DA67D82DFAAE7ULL, 
            0x775C98BE7F44A864ULL, 0xB37540F7D9C357C4ULL, 0xDAE9A0307E0F6483ULL, 0xE8F544296B0ABE9AULL, 
            0xC1EC9016E4D96937ULL, 0xA0C54A127EF12560ULL, 0x31962319960E3355ULL, 0xCF7FB0DBE3A77096ULL, 
            0xCB03A4485BEA9EA3ULL, 0xB0F73554132E1A3EULL, 0x32F987FECFD75DBDULL, 0xCDC1BB5F21BBD7F0ULL, 
            0x88461F800F103BB1ULL, 0x1E19A201E9999AB4ULL, 0x2209D8EA1CC262E5ULL, 0x8A531E99E8444A21ULL, 
            0xAA2D5463C10838FBULL, 0x2A6FC1852ED2A5E5ULL, 0x26A9BEFA0B72F5A2ULL, 0x3BA08A5C31884977ULL
        },
        {
            0xAFFA902460EB84CFULL, 0xBE63795738A01F5AULL, 0xDDD79F88A9A95FFEULL, 0x20770362DE4356C1ULL, 
            0x8937B64B901218E8ULL, 0x35289D083316DAA0ULL, 0xB7D0FA9D0E692A6EULL, 0xA0EA10C16CD5E984ULL, 
            0xF6809A6D671513A9ULL, 0x7424973B8B672E34ULL, 0x51571EED6B06D994ULL, 0xDB8F2683209158C5ULL, 
            0x5DBCCAA6AE5F17EDULL, 0xCBE5090970D3D132ULL, 0x26AE7F26116039DAULL, 0x87CB258F3E0E7DF5ULL, 
            0x3217067A7917788DULL, 0xD9D9AED5CCEA3FC7ULL, 0xA3AA0045FFDC2EB7ULL, 0xD5321F5B73D5961BULL, 
            0x755ABF95260ECC71ULL, 0xA7A0BD14011A755BULL, 0x35ED1263C90C1FAFULL, 0xEF2E98AFFECA5B8AULL, 
            0x15AF87668200D324ULL, 0x39CDF7CF735E96C6ULL, 0x0147A96D012BF13FULL, 0x72E4564F201257A9ULL, 
            0x592EE98C21EE2691ULL, 0xF2F748DFF25F5197ULL, 0xB4B03EA7F546A1EEULL, 0x417E76FA85DE9A7DULL
        },
        {
            0x4F25A063BDCCDFE4ULL, 0x7D6ACD79FD976B88ULL, 0x0844C92C7723105EULL, 0x4E0DBE95B33E177EULL, 
            0xC5D60A7278B47734ULL, 0xF4B6CF2863AED7E7ULL, 0x11FAF6DF0984AA30ULL, 0x1E51A21A7415424DULL, 
            0x5AC7013477C1C4BAULL, 0x56DFB9D7EDB0C0C5ULL, 0xF8A1268D5268A980ULL, 0xEFE2BD7D763C158BULL, 
            0xEB04551D2B1ECAA7ULL, 0xA346C0A2B3E09D9CULL, 0x97798B396FC56671ULL, 0x3F12FCC5F67EE42AULL, 
            0x20F106D5647F2C44ULL, 0xA1229CB392FB1791ULL, 0xA4ECC2B03622B88FULL, 0xDDFA849321542BBAULL, 
            0xC77B1A59172DBC9CULL, 0x069EF584BF131F8CULL, 0x0449C43FAB7707FDULL, 0xF9BC4364EF3FFE82ULL, 
            0x0D21D38AB13BFC63ULL, 0x3B978B81FD5DC8E0ULL, 0xD4A13B0A38F2DFE9ULL, 0xAA6A9978F78B3035ULL, 
            0x7AD283C668E5CE02ULL, 0xF7A568092746EC50ULL, 0xB671787650C6235CULL, 0xC826897A34629120ULL
        }
    },
    {
        {
            0xED383157EA194C56ULL, 0xA3FDE5851E464DD2ULL, 0x3E1C8588E5D07A94ULL, 0x0F6D9CA42649E3F3ULL, 
            0x77D166BB6C575A38ULL, 0x441AE245075D4E91ULL, 0xE3C13DB649A103FAULL, 0x6F428F181A9E4D21ULL, 
            0xE105D896A9244F70ULL, 0xBC5B250D03057B19ULL, 0x5E3934EB589795E8ULL, 0x424CE365FFA9327EULL, 
            0xD624F0412FCB30CAULL, 0x08DD2636EE79B767ULL, 0x54E824085B030FB0ULL, 0x7F8BC204095AA1A6ULL, 
            0xD03DE681110FF37BULL, 0xDA0D7234A5FA6CCEULL, 0x3947FC1A342257CFULL, 0x278943F755BE2F79ULL, 
            0x4F07419CCB9E2B79ULL, 0xE430482050A72188ULL, 0x98B68E97FE1DBBF4ULL, 0xAB2C26ACE0A34489ULL, 
            0x9D5472067A68BCC8ULL, 0x3A2730B0FE3F57A2ULL, 0xF18FCBCAA0A04AAEULL, 0x602EA3E8FF4AEBDEULL, 
            0x9E64F843516665EAULL, 0x10DF3D5EFF2DAF2AULL, 0x9D3B7F52830BA378ULL, 0xEC01CBAE310DE4B4ULL
        },
        {
            0x55AFF75E6485695EULL, 0x72A615C9BC15BE64ULL, 0xD928B2E6A4E55C15ULL, 0x7F97B787981EF894ULL, 
            0xDDA233259F775E5BULL, 0x79FB6B23C407FD56ULL, 0x007A6DEFE5105681ULL, 0x959BA46A37B53345ULL, 
            0x99BFCEA47D5B8F79ULL, 0xB5DCAD19ADD1BA80ULL, 0x53870FA1CAD2551BULL, 0xFC256F699764A47FULL, 
            0x849DA1DF450F6F29ULL, 0xCA518A3D4D2EE5B8ULL, 0xB85B052795A1948DULL, 0xC110F04A531BC4C3ULL, 
            0x1950C43AD92C38E0ULL, 0x8BE73CBB800DC358ULL, 0x29DBF88E92549206ULL, 0x1231D7F7152788A0ULL, 
            0x151D7F755227DF4EULL, 0x271B5B80770DC1DFULL, 0x00D480C48036A58CULL, 0xE7D7931EBE43F3E2ULL, 
            0xD99230A42BA19BE8ULL, 0x42315D41D59C5CE3ULL, 0x2EAA700A5FE941B7ULL, 0xDD00E53C06E43EBBULL, 
            0x7F08642F885D0242ULL, 0x82F2D252DF023117ULL, 0xD2AF1E6F50BBEDA2ULL, 0x42DD8948D5A9126AULL
        },
        {
            0xF859844808040F5DULL, 0xE637F7F7DD44BC87ULL, 0x63372E20A76C5AE7ULL, 0x242F0D46EA1A2EDFULL, 
            0xC8565891AAC81A22ULL, 0x4B797A4051E91DAFULL, 0x6CF351A032FE7AE4ULL, 0x9625A811FC456687ULL, 
            0x45FA188A86322AE7ULL, 0x789534BB6565D4F3ULL, 0x6A561C130F8ADFA4ULL, 0x247303423AAEEEA6ULL, 
            0x2EF83DA29D0D4319ULL, 0x07C3F726277B7CEFULL, 0x524A0CA6ABF50D0EULL, 0x0FC0350B4257CAADULL, 
            0x0FEA2E9EF994AB55ULL, 0xE64434EA4053C9F4ULL, 0x29173FEA643692AFULL, 0x742B2021D70324E0ULL, 
            0x9EEAB36FA6EA3F83ULL, 0xFF446EAA726C3F3CULL, 0xF6587AEDBB1D8F6EULL, 0xF25AC7A274915371ULL, 
            0x32B7E613348D127DULL, 0x9EB81D939EC64895ULL, 0x549AE5128C60B075ULL, 0x209E214EEA4B93A7ULL, 
            0x70FC01692956329DULL, 0x03D5CF463FC29510ULL, 0xF4A85250745B5DDAULL, 0x52B583A4E1F17D10ULL
        },
        {
            0x3F1786B565D4AC82ULL, 0xAE73FB293505D073ULL, 0x910F9CF6CA9A50B4ULL, 0x6A96BAFFA32EC836ULL, 
            0xD22A6933D85D3D3DULL, 0x500C41A394500C52ULL, 0x3F8B69736146892FULL, 0x51F563EA875D5B40ULL, 
            0xDAD8F84816D392D3ULL, 0x941C369D7122705CULL, 0x26769DB0EECDC16AULL, 0xF63A7CDB3147C2DDULL, 
            0x437DD98076931D39ULL, 0x9BC444E04B452CD4ULL, 0x32BB5B02DB2CEBC1ULL, 0x70B3D85E18102EF4ULL, 
            0x16F252D128072D60ULL, 0x13CC8D92B748C73EULL, 0xFBD7D7B0E6B0E26DULL, 0x9352E4703F692D17ULL, 
            0x59EF771212FB8B27ULL, 0x6C467E14D6CAC01FULL, 0x21942E1D3D1A699FULL, 0xF227E8DD9F208DABULL, 
            0x5584AFEE433E754BULL, 0x064CDD0C18A26E66ULL, 0x2B1FCBA91F03AED7ULL, 0xB07FBFCFFD509AC1ULL, 
            0x14AFADC54C0C8968ULL, 0x874FF96E58223B29ULL, 0x95971CBC4C41BDD0ULL, 0xEF6AD729F0526449ULL
        },
        {
            0xBAD7B0B8E113B7B6ULL, 0xDFBCDB233A2FA859ULL, 0x66449DC43B027842ULL, 0x82A30BC6C86C84B4ULL, 
            0x7EB9F6A306E4E9C4ULL, 0x29A27935C263B682ULL, 0x8543FC85E110B680ULL, 0x5A65AD6BBE1755EBULL, 
            0x50029B3255E767E1ULL, 0xF4205C8A49991D1FULL, 0xBF1457CA1C4FAB68ULL, 0x811BB42216B10F38ULL, 
            0xE2D0E450E5394A63ULL, 0xDFBD909BB8E36E1EULL, 0x4741187A104EABDFULL, 0x11ED76C2B143DA47ULL, 
            0xC09799D876A774A2ULL, 0xB522E6338BDCBFCCULL, 0x9D2C2D8D5844FC34ULL, 0x32182F4A498F8D3BULL, 
            0x52E99672CF58E4F1ULL, 0x7CE35CCFB3924C82ULL, 0x6B012571AA8AE9BFULL, 0x98BB61D439A30ACFULL, 
            0xE0D49B8CE7013361ULL, 0x14D1FB56CA29997BULL, 0x1EF1BEDC6AE3B853ULL, 0xD7D0AB8EAD2E0EB2ULL, 
            0xD3BB2FEBA0A41E96ULL, 0xF75B6798FCC9A6CAULL, 0xA90BB36A9D92F77AULL, 0x31582EC87B8A9F01ULL
        },
        {
            0x3C26003D42F9486BULL, 0x286C7BF36096D884ULL, 0x05D1EB6717ECB806ULL, 0x9F0A45C06B647171ULL, 
            0x5AEE26A88A2FE603ULL, 0x7E6761F84FC186E9ULL, 0x90CF7E0C83A7B212ULL, 0x96D8D8E58037666FULL, 
            0xCB5052B123098448ULL, 0xB072B945C66FDD47ULL, 0x78424D727C2E1D36ULL, 0xF0926D45920B8750ULL, 
            0xC119767482F22044ULL, 0xE33DE00B24B3CCD2ULL, 0xB169A3010ADC9285ULL, 0x66280E276B92268BULL, 
            0x9191BB9946B71023ULL, 0xD9D7BB5BD902EBD4ULL, 0x5B58C87D5C7EE99BULL, 0x63918DB2B0DDC488ULL, 
            0xECDDB4EE54D9EC63ULL, 0xE9F01DE39B973C58ULL, 0xA59DD217C7559621ULL, 0xD2925A7CEFFF287EULL, 
            0x7DA4FB9DA269A574ULL, 0x95A74C6C7B51037AULL, 0x486CADCC59A68FEBULL, 0x3E7D10738222EA44ULL, 
            0x8A9F1FABA2A30BBDULL, 0xC8A0BB650B230600ULL, 0x0CE5CF942BEC2C76ULL, 0xF02BA71823A6BFDCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseDConstants = {
    0xFF4E9050302C098FULL,
    0xC24DC824291C38E5ULL,
    0xE274CD71A0216309ULL,
    0xFF4E9050302C098FULL,
    0xC24DC824291C38E5ULL,
    0xE274CD71A0216309ULL,
    0x684944B63D3326B3ULL,
    0xF2BD34123044087CULL,
    0x13,
    0xF4,
    0xDB,
    0x68,
    0xA6,
    0x14,
    0x65,
    0x16
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseESalts = {
    {
        {
            0xE2B048754E64C5B7ULL, 0x3DAC8C4163377B3DULL, 0x7C5B10AA84AAD44AULL, 0xD153571D9FB0048BULL, 
            0xAF368500836EF700ULL, 0xD776D608FE9EF520ULL, 0x87ED073ADFAF007EULL, 0xD88495C38518CD6CULL, 
            0x4DBAF0FAF3D7B18EULL, 0x605434F99EEE49C9ULL, 0xB513CAC92CCBB690ULL, 0x30B91EF25CDB0621ULL, 
            0x23D82E32EC577056ULL, 0xBD8536A51896397FULL, 0xBE9AA399BC92A349ULL, 0xC06A0E6940E61BF6ULL, 
            0x9F749286E4A2EBACULL, 0x86C8E81449121D60ULL, 0x34DF8A93B2EFC579ULL, 0x258DFBF41F8E7B03ULL, 
            0x1B4945DEE8C1DB3AULL, 0xA0798EB289F968ABULL, 0x925AA90904EE60BFULL, 0xD24AC70BE62572CDULL, 
            0x379D85728EFF999CULL, 0x16DFB43050FAE0FEULL, 0x550D01C79DA660D0ULL, 0xC01576F85B9F227FULL, 
            0x31A7CE73D777F725ULL, 0xFDF1A504054B0B7AULL, 0xAFBAC7D6D4DB4615ULL, 0xA4A82B5C2C459EDFULL
        },
        {
            0xC4AD24C50EFC90F6ULL, 0x5455E0C553C471D6ULL, 0x4F58AFC6F0C4FD82ULL, 0x61E577E7C7D469F7ULL, 
            0x698C521058A679AFULL, 0xBE6B26A7980B809DULL, 0xB1EF2AB5F3A3F82FULL, 0x8A96EC189F80F8DCULL, 
            0x3CEBEB1B227EE60DULL, 0xF535679891B02A4AULL, 0xDBE2D8E54FCAFAA0ULL, 0x0E869EEB1DE31811ULL, 
            0x48F42E34DE9CABBFULL, 0x22F21D7ADB3CA713ULL, 0x7710C18366CC7ACBULL, 0x3A4D6C4B68303DB1ULL, 
            0x55984D1764CB25E7ULL, 0x815AF0C2001B6438ULL, 0x5B208300BF6B74E8ULL, 0x62547D9EB3EF12ADULL, 
            0xD5D53DCCB93D9FBEULL, 0x993904728EDFA8C6ULL, 0xEAA9846B623A1328ULL, 0x865CFAE35297AC28ULL, 
            0xBA8F9B992D484F92ULL, 0x43701FDD8FCF38D5ULL, 0x95581B5F2AD17CFEULL, 0xB5560C422A5728CBULL, 
            0x5A0428A5832F70D0ULL, 0x40702158D9899E6FULL, 0x96CD004236FF5ACDULL, 0x6DD69329109D0ACBULL
        },
        {
            0x33696CBDA04E003AULL, 0x0D675D6F084094D9ULL, 0xCFFB7DA22EFF853FULL, 0xECBA151BCE247CD1ULL, 
            0x727FA3A0FFA360E4ULL, 0x2E86128612AFF181ULL, 0x33DE5A8B5E1F52E6ULL, 0x9B64B254C00B2A9EULL, 
            0x77D5AB7C217E81DBULL, 0x33919B8F0E682031ULL, 0xFA3EA694BBB7369FULL, 0xFD0CBFDCCE583407ULL, 
            0xA7AA62FDFD9642DBULL, 0x0D56F950D722AC38ULL, 0xBEA25B5117E32D2AULL, 0x289E9B146CF720F4ULL, 
            0xC6409807AC30BC73ULL, 0xE02228EB059F09BDULL, 0xA606C4F55F9A66B4ULL, 0x1A5F737851CB7259ULL, 
            0x31A806D9E986A0DCULL, 0x0AF6BC2AAC4BD9E7ULL, 0x79FD00E3FB49CBE6ULL, 0x568100BB8A94045DULL, 
            0x2FF9C88A3AB24D67ULL, 0xFD67D382C2B3C088ULL, 0xFE39BD6AB9593077ULL, 0x465DE73E25F8516BULL, 
            0x066CC88346BAD51DULL, 0xF72C657D9B40F6A8ULL, 0xB2D32D27B34FAB07ULL, 0x21F06A76AD65603DULL
        },
        {
            0xF8614B4DBCB25F3DULL, 0x16FDBAA1570961D6ULL, 0x445B0E25EF44F164ULL, 0x2A1B09A1A9C36FD8ULL, 
            0x09E4092D6CA5638CULL, 0x9B148C461ABA4571ULL, 0xB93ECF40EEB5DFF5ULL, 0x5FCD899EC6329585ULL, 
            0x7F5E5C729A0158D1ULL, 0x8454C950FD37B899ULL, 0x4D492123BDA2268BULL, 0xAC33BED2AD190EDCULL, 
            0xA2C17C45B23CC63FULL, 0x4C79FE720BE7FD6DULL, 0xE288586DAAB6FE40ULL, 0x0DB5DCE6E408B0FEULL, 
            0x0F1F7E2E0C0EB55AULL, 0xDA83D0AFDE582285ULL, 0xC938EA7F892FFC87ULL, 0x2B6B1482BC3B394FULL, 
            0x08105C8AB79811A4ULL, 0xA361882C38200142ULL, 0x2DF8B4F638ADF735ULL, 0x811F8324B74A3A8DULL, 
            0x78613B230F1BE975ULL, 0x312716906304559CULL, 0xE7EF1E61DB13A814ULL, 0x82C94DFD4C7C4F03ULL, 
            0x6C0674D158E12268ULL, 0x320AAF66F94AF7C1ULL, 0xB0944D8FF5F916B1ULL, 0xC5A9A5B155B95786ULL
        },
        {
            0x7CD086E373D0A237ULL, 0x06190FD908CE371AULL, 0xB7CB30624C09A276ULL, 0x14A54302BDDF7ED3ULL, 
            0x58EEBDDA37158659ULL, 0xF499186C91B8997EULL, 0xE8BCF8E89A70F158ULL, 0x9DDEE3282C77F356ULL, 
            0x912BF31A9AE94721ULL, 0xA7877D4C7C2CB60AULL, 0xA34DAE4F84B6A03BULL, 0x70E92A7673587808ULL, 
            0x8DFD8BFE71B650B3ULL, 0x5D36EA3D891DAA6CULL, 0xFD32EF3C9C81B2FFULL, 0xFD5A0B188B490766ULL, 
            0xA99479B4EAA3919EULL, 0xE6AC73C5F957B871ULL, 0xCA48F756D00ED7B4ULL, 0x9ED1EF53E7E6932FULL, 
            0xDD06DAAD16937A9EULL, 0x6532DF44DAA80CABULL, 0x97FCF3440DBCD748ULL, 0xB8CFDF5C83D48807ULL, 
            0xE7A720CEEDB76467ULL, 0xC5C08926B8E3B1E3ULL, 0xEA4D0823D25D373EULL, 0xA756DC944A9D60FAULL, 
            0x863C2CCA76EE7A04ULL, 0x42075A98CD9D6D6AULL, 0x92F6F640A209F4EBULL, 0x551614AB22A47E32ULL
        },
        {
            0xC7284D2E6F3C9F0EULL, 0xFD4C883F398490C6ULL, 0x530C824E8AF8CDAFULL, 0x67D0CD1C637CE760ULL, 
            0x06947647935490E5ULL, 0x0DA317DBA7C93F92ULL, 0x4417BE459DE6B3F0ULL, 0x4CDBF894A0336A86ULL, 
            0x426E86D430E74258ULL, 0x0F271C3A6EB3B076ULL, 0x6BE8C4560BA4F760ULL, 0xFEC37DD6477C3CECULL, 
            0xA5C359F913DA724BULL, 0x845CD36638181EE0ULL, 0x5AD3BCC062840C0FULL, 0x734523EF2DEEEA35ULL, 
            0x678CB5BF374FC154ULL, 0xBFEA525B8A30F380ULL, 0xB731903C0445A70CULL, 0xD942D6CF40928218ULL, 
            0x514A72433A14FF34ULL, 0xDD7587F8E3DC3F82ULL, 0xC5518AE8D63582FFULL, 0xDD6D07D25D6EC80EULL, 
            0x85C4BAD3BA9DD454ULL, 0xF81C073101DD235AULL, 0x6670E4805DE77243ULL, 0x4F49A85F1A803871ULL, 
            0x71DF74F20D96827BULL, 0x2387D2D3973B7F2EULL, 0xEADE5DEA44B311F1ULL, 0x79916F931C793FE6ULL
        }
    },
    {
        {
            0x321B54982D00C756ULL, 0x13617DE30633BCEEULL, 0x0ABC9100BEED4F7BULL, 0x670EF1ABBF3DCA82ULL, 
            0x86824EF66FEFCF2BULL, 0xD3126DCD9D24B707ULL, 0xC11FDF361C4E1214ULL, 0xE3D9100394F04D82ULL, 
            0xE4E10F5A56DCD608ULL, 0x11837B0391199787ULL, 0x7579744CAE4A9A5FULL, 0x744448B37265D196ULL, 
            0x79AA34101FEB8440ULL, 0x8373512EC8AC70C5ULL, 0xF9BFBAF5FE8B22DAULL, 0xBAB7C83667D4182EULL, 
            0x81C91B1B2A076C38ULL, 0xBCEF4E0E6843C3D3ULL, 0x46DF9473F913570EULL, 0x18FE41A2E0852512ULL, 
            0x1D284EC4E1E33A77ULL, 0x8AE10E1ADE86EB6BULL, 0x601D96AF77945741ULL, 0x0A62E78B91320339ULL, 
            0x3FF4D24EFDCBDE40ULL, 0xA943B100D0142687ULL, 0xC8870BD1A25BE023ULL, 0x60248D4742627521ULL, 
            0xE804BA43AC9F40FAULL, 0xEF5806768A769BC9ULL, 0xF4930DAFDE6F5088ULL, 0x6A332E9BD9CEB4FBULL
        },
        {
            0x05B841E303DF9AC1ULL, 0xF2355EECF4D31519ULL, 0xD1B45E3A984DCB19ULL, 0x9B692F9C53FCC5DBULL, 
            0x7CD611D70DC70AC8ULL, 0xE915291C9B5A8750ULL, 0x518CA24110A74594ULL, 0x6453113E0522B9B4ULL, 
            0x7F5FE25E1C8D2C5BULL, 0x4408B2F64737EBF2ULL, 0xA8D7E0AA313B8648ULL, 0x0232EA5F9560005FULL, 
            0xFB5E1FD27B5ED7ACULL, 0x1ECDFD5607DF358BULL, 0x9CC3DAD0B743FED3ULL, 0x81E9CBCC1ED257FBULL, 
            0x509AE3AE539ED980ULL, 0x27418B5A8D1D1E34ULL, 0xDE3F60B58C55DB43ULL, 0xD5368ED8B38724B6ULL, 
            0xBE3BDA1DF5E96D0CULL, 0xCE4D3463E9B96939ULL, 0xE27AE54C01BAD1EBULL, 0xFF1F69345D071229ULL, 
            0x030AF586A33AD4DFULL, 0xFD4381E2689F929EULL, 0x59F4BE83665AAD85ULL, 0x2B5E7BF5720C630DULL, 
            0x0FC6699A434C97D7ULL, 0x344E8791008A1868ULL, 0x40F606FF45309343ULL, 0xED723107456BF5D5ULL
        },
        {
            0xE790E4A99AAFC8A3ULL, 0x595CF591E4EEC46CULL, 0xCA1ED6FA8CC3747FULL, 0x38D61A7AB651C9B1ULL, 
            0x65494DC0303B0CF0ULL, 0xF8451E3235A9E231ULL, 0x183166485B0D8DA9ULL, 0xCB1C98C50DC1F928ULL, 
            0x131668F400FD2DCBULL, 0x78B9266DF79A0AC5ULL, 0x38B8D3D55801267DULL, 0xAB90A36A87E2428AULL, 
            0x16BB9F9C62CD615AULL, 0x6F25B8BBFB6731D1ULL, 0xD9D859E670C9C6A1ULL, 0x050BAED7EADFD681ULL, 
            0xCBDA10992DE54380ULL, 0xFC258ADA7F5C292EULL, 0xA9D288B452BAF89CULL, 0x1A7A6932C9250365ULL, 
            0x1DD8C1CA6CA9F489ULL, 0xDDC17D0666463328ULL, 0x3973503607A91869ULL, 0xCAFC709C164F3493ULL, 
            0x2A1891F5B481BBEDULL, 0x903EE672CA13A121ULL, 0x3F85F53ADECB464AULL, 0x70E703A63F147BE4ULL, 
            0xF35A919BF63C366DULL, 0xC22610F878FCE0C5ULL, 0xDE70280683F50DF5ULL, 0xDFF9C0E45BC7DCD5ULL
        },
        {
            0x976DC2659702B8C6ULL, 0xBD60F0CAE4DF5A7AULL, 0x715A4A0BB366C58DULL, 0x1224BF81319698DFULL, 
            0x706104E8EF4035BFULL, 0xC9B8326E5A9D55ADULL, 0x12BA1CA2CB803C26ULL, 0x49F44DBFC19B7511ULL, 
            0x0C0DEC077CCCD36BULL, 0x8994DBDB71EFE4FDULL, 0x0E58E00E1DBF120BULL, 0x70FA75A3553BB68CULL, 
            0x45337321D0B613C2ULL, 0x38A9562DB1F02941ULL, 0xDEA0C3FF548C6DBFULL, 0xADD927EB841A8142ULL, 
            0xA53F1C099A640FB3ULL, 0x154235D9060F15B3ULL, 0x54ECB54AFC4AE3CCULL, 0x130DE16A1DB86905ULL, 
            0x2DE2142BF582901CULL, 0xB71CE6C43207A7C4ULL, 0x5C253916EB024E2AULL, 0xF34D1D1C203C1A7FULL, 
            0xEA7576D1AD1EB5CDULL, 0x425B129E230815CAULL, 0x82EDA16EF96EA90AULL, 0x32CE748094B87BB1ULL, 
            0x0AC59F3D08208AC5ULL, 0xB252C5EA999C246FULL, 0x2977AD55241FFDBCULL, 0xEEBE74FB519215EAULL
        },
        {
            0xA8F0B51627818F2EULL, 0x35B360CB50EEAEDFULL, 0xE3B6D2497E3B9D7DULL, 0x4719266089072099ULL, 
            0x118AEBC1A0F836ECULL, 0xD52283DAFA17180EULL, 0x8C39AB0B01F3E23EULL, 0x3BCAAE2BF89CFF6CULL, 
            0xF5BD829F2265CDFDULL, 0x924E1C7B193D9B65ULL, 0x032728FED8B9DE7EULL, 0xC564CA9880A723A5ULL, 
            0xA02A959778099F81ULL, 0x4926A43F351A8EF2ULL, 0xDB7567010CBB125AULL, 0xF40E3599FF2757E4ULL, 
            0x14C12AD4A257A229ULL, 0x7800FF6E50235D73ULL, 0xD3387A83826E59E0ULL, 0x2843F16B04421D39ULL, 
            0x524EECB94E96C677ULL, 0xDC198C09DBB9B1F8ULL, 0x435E868EBE8B4095ULL, 0xFE9BB05B9A453CD3ULL, 
            0x4590B12A83EAE33BULL, 0xBC5343029D93F390ULL, 0xAE048B69BE8CF569ULL, 0x3CA8B1C33D6E50B2ULL, 
            0x16BC8423BAF9AC90ULL, 0xE01DE9FEED98FE72ULL, 0xBDD4AD1985818D9DULL, 0x49F6A71200CADE80ULL
        },
        {
            0x5B11043423641B9FULL, 0x944FD13783B9406AULL, 0x5DB425A06C653AE3ULL, 0x432AE719CCB04481ULL, 
            0xED51EA6307D12489ULL, 0x6E674DD62FA89AD8ULL, 0x4223CFAE0918C25AULL, 0x33E4B9785D75BAFBULL, 
            0x270693726EE83915ULL, 0xE7701B9DC4ACC8F7ULL, 0xC8292CC0D8C7225DULL, 0xC61A0661EF7EF6FEULL, 
            0xE83EF981BA8EEC6CULL, 0xCF18E5EAC9361969ULL, 0xDAF9B56F843DECC5ULL, 0xFC0A1554E9717525ULL, 
            0x7A9029224230C342ULL, 0x54E6472A6A84C3E9ULL, 0x90F6EE898EEBAC7EULL, 0x0D9E4B9837C53124ULL, 
            0x4F77E297E2157E8CULL, 0xF484E8C5DB604F7AULL, 0x3C7A759E9F3C3D0CULL, 0xBF363E9062113C6EULL, 
            0x53757871CF93EB92ULL, 0x500B312CC20D7BE5ULL, 0xDB68D9220EE6BEBCULL, 0x33AECC44F1607DC4ULL, 
            0x9459A0794C24E308ULL, 0xD7B862073876CF87ULL, 0x828A28B27A6FA22EULL, 0x6D1F1B2E7E4CA192ULL
        }
    },
    {
        {
            0xA7ABA1CF2007E0A0ULL, 0x469C56F744C34173ULL, 0x0C8E2919B0186E5EULL, 0x04549AE373AA0E69ULL, 
            0x0E9FBFAF9CF380BEULL, 0x75BA7FB4AC06F1D0ULL, 0x4CA941C00A6FD4E6ULL, 0xE3888EBD93B8FAEAULL, 
            0xCC822486F59CA9E5ULL, 0x163CE4BBAF1B3F58ULL, 0x5C017B9E2D05B732ULL, 0x36EBD2BDD6717BFAULL, 
            0x0A30A6CB812BD265ULL, 0x135E12EE69BDF326ULL, 0x1343834FC8CDD44DULL, 0xCDCC4B3FE3455376ULL, 
            0x3BC48402DC8534F0ULL, 0x71749CB7F6C73678ULL, 0xF7C704D3987B393BULL, 0xB01AAA01A0D115DBULL, 
            0xE2144648F44AEC28ULL, 0x0F52DBE2988B4BD4ULL, 0x64FA5F603B6B9BC3ULL, 0x795C3F2FACAB624AULL, 
            0x0CA46816D4310AA5ULL, 0xD91738596DDD36B0ULL, 0x8BDDB84084FF753DULL, 0x76767A24D79463DDULL, 
            0xFFBF0BBA33B2FB61ULL, 0x53CAD60440CC891CULL, 0x04BC646FE4D8223BULL, 0x45151CBB16A294E7ULL
        },
        {
            0x699E4EA42F4D5CD6ULL, 0xDDAB76E8EA972713ULL, 0x1EB504EC123FCFA5ULL, 0x65F6E177F8200028ULL, 
            0xFBA5ADC5A4A09497ULL, 0x411D809917EFE43AULL, 0xFD52F2FF4986F7FAULL, 0x417C43900F7E576EULL, 
            0x889022B3887513FEULL, 0x493022BC60E956E7ULL, 0x074595AE13FE1F24ULL, 0xD2F45AA9EC99A2D1ULL, 
            0xBC2888355A1E1D4DULL, 0x854792BBEC48813DULL, 0xF7A5EDAAAE8B1DA3ULL, 0x9FED1C2EE8A3A737ULL, 
            0x9369AD983788E6BDULL, 0xECC7EF69893B6B47ULL, 0xFB05638716BBFFD8ULL, 0xB0120D1C3964F03AULL, 
            0xBB69A47A958935A3ULL, 0xEA53903C0AF6BF6EULL, 0x3324152EC4C9F950ULL, 0x7F6CB8799C762AD8ULL, 
            0x33D10BA21E4D26B1ULL, 0xC7DA131270840C0AULL, 0xA350F93BBE9AE4DFULL, 0x47FFB9AD1894B24BULL, 
            0xFF9A7BBAFC25C061ULL, 0x5C9CAE4427688006ULL, 0xD33EBFDFFA3BB621ULL, 0xDCEBFA80C2766471ULL
        },
        {
            0xBB24B9BF82A0B3CDULL, 0x07836E2B935A54B8ULL, 0x1FB9451A5A42B18CULL, 0x6401E3765A3542E4ULL, 
            0xC21922D0F31E7E21ULL, 0x4E888B120B0FE644ULL, 0x66A1B48F92185F62ULL, 0xBC26623DA316EF1AULL, 
            0x9F05751CF4976B9EULL, 0x6EBCEE34D5DB3354ULL, 0xA405E8AD64814AD7ULL, 0xACB5CA3DDC04C7A6ULL, 
            0x989D674DC57AEA5BULL, 0x6BA9191B204C887BULL, 0xEAA778C43C6AE1F6ULL, 0x021C0015D154CD93ULL, 
            0x02F1B33A68F4ECD3ULL, 0x83449A8E16C1530BULL, 0xE8CFD4CF97DD8250ULL, 0x112F342F5E999E7CULL, 
            0xC661A5BFD814AB04ULL, 0x71F98853305D37DCULL, 0x1E845A0DEDA090ECULL, 0xAEBCA6AF593BB13BULL, 
            0xB54FCEA9E8070040ULL, 0xA36F843BCDAFF6A5ULL, 0xAED5968A4D7DA251ULL, 0xF556FA12671CD1ECULL, 
            0x789E7575D037CFFBULL, 0x4C799CEA282F87B6ULL, 0xD275322F1344F9A7ULL, 0x8EEC1EE51F4EFF66ULL
        },
        {
            0x3F872126253374C5ULL, 0xCFD5346C82AC7462ULL, 0xC79E20AE08CBDF1DULL, 0x8C0909DE61E592DAULL, 
            0x884E887C3343C597ULL, 0x2D40DB898CB38A93ULL, 0xF25DE8DAEB7D925BULL, 0x73B28E1E7B00B5FCULL, 
            0x71810CA0042BEFB3ULL, 0x882578256C777189ULL, 0x2358B07AC857C8A5ULL, 0xAE8FFED0DB8C86C1ULL, 
            0x51AA89297E79B829ULL, 0xB2984637F8A2C8ABULL, 0x1E3FAEF35DC29C62ULL, 0xBE38B20B95E89F68ULL, 
            0xFE5057499CAC5585ULL, 0xB977E6008CF4DDB3ULL, 0x69D789AB0042D69CULL, 0xB82B8DFEFB39264FULL, 
            0x3296AD28A02D2C6CULL, 0x097B384410BAF3D3ULL, 0x50D7F63663A722D1ULL, 0x891E8C7BE7B8E4E7ULL, 
            0x1983EA27A10B19D4ULL, 0x14B184D02CE5F64EULL, 0x0550A7AAA2AA24CEULL, 0xEF6E253E31460645ULL, 
            0x5EF71843A3596E0AULL, 0xC2AB467A3E7061DAULL, 0xDFED29A8A104074BULL, 0xA9FE37E3E54C9FABULL
        },
        {
            0xC141137345CFE625ULL, 0x19B2AF1CDB98BDEFULL, 0x808AC86DDE2E77F6ULL, 0x9D392EE528C5A705ULL, 
            0xB9828B143460D5CCULL, 0x71F5796C3ABF81F4ULL, 0xF64C87106CE713C8ULL, 0xCEA54306FB690622ULL, 
            0x19A7C9CFE9B6A9B2ULL, 0x1864CC8A433E9327ULL, 0x4B35C4B58410E6FFULL, 0x25D46EA18045CFD0ULL, 
            0xDCDAE605C2109DC8ULL, 0x46290393AAAF7CB6ULL, 0xBED5BC5890E43CB3ULL, 0xB72C9FE0626DA83AULL, 
            0x5EEE14255386935CULL, 0x9A207B4DD26449DFULL, 0x313A1F9480762556ULL, 0xF6C28410ACBF9937ULL, 
            0x477F05D1750E7260ULL, 0xBFFE4C4929A2DBC3ULL, 0xB38068D3B1E8AAD9ULL, 0xF50F3EE715A420FFULL, 
            0x37B398A21B8C783AULL, 0xCBBA8CEB73AC5187ULL, 0xC4A25B27C70F18A1ULL, 0x2AF0616EB254DF8FULL, 
            0x1002A584D8422098ULL, 0xE408D4C8BB9D8A87ULL, 0xD1CCF47F35D13456ULL, 0xED7DBBC041D97260ULL
        },
        {
            0x5E0C19770F68C01DULL, 0x285E56E914132228ULL, 0xE591541D4E60E009ULL, 0x6E1600DC5C8BA81FULL, 
            0x98C35B32D667360FULL, 0x3E3183FFD69B2475ULL, 0xDF12FD553C4CC195ULL, 0x8F6F743AD90BFA57ULL, 
            0x5A898AE0C2261805ULL, 0xC4F6A147C16037EEULL, 0x6E2E00C4945BD0E0ULL, 0x5C25EB5B7F863E34ULL, 
            0x1570681BB34A11B6ULL, 0x2A44911C09CE8628ULL, 0x0D545CF77C3F7D13ULL, 0x8C3D12AC7EF42D5AULL, 
            0xA8DAE5513E4C5B67ULL, 0xF133AFA194AFECE8ULL, 0x2F8102C8CC2820F4ULL, 0xBC61FE7207093FA4ULL, 
            0x030ABF71C053EB25ULL, 0x19FE7297717D14E3ULL, 0x311F10D20F300C8AULL, 0x03AD6ECA15C765CCULL, 
            0x27AD5D00EE3F176DULL, 0x92606A2594BB6DACULL, 0x0B8C8F6B078948D2ULL, 0xF71CB40AC520162DULL, 
            0x51DE5219A2DD0F00ULL, 0x2AC754BB9E3EDDACULL, 0x9B41977EAB863A02ULL, 0xEF3C32B63F528F8DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseEConstants = {
    0xA7256BCFA8C51072ULL,
    0x602BC415B7312C7EULL,
    0xBAC7B2389BBD6AF9ULL,
    0xA7256BCFA8C51072ULL,
    0x602BC415B7312C7EULL,
    0xBAC7B2389BBD6AF9ULL,
    0x400BF3DA99C0CFE7ULL,
    0x32AC0C83B7F6E5C3ULL,
    0xD0,
    0x54,
    0xBA,
    0x4B,
    0x0E,
    0x4A,
    0x48,
    0x6A
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseFSalts = {
    {
        {
            0xD0D6C13E92228575ULL, 0x1E46E26F874560AAULL, 0x0D49C811554BD814ULL, 0xE1BA8421014D5D5BULL, 
            0x256755D927A955BCULL, 0xF0743E56697E8E40ULL, 0x66E35668B0F609F0ULL, 0x9A48044E798CBC53ULL, 
            0x8966BB132F0EF2B4ULL, 0xFAE4B32096BB72C7ULL, 0xDDEA106D9C15EE54ULL, 0x404137ABAE8CE882ULL, 
            0xB693EED7BFD1624FULL, 0x2E4EBE94346DFE6CULL, 0x1BADC218E53C1E48ULL, 0xE432D4B64C5C3AEAULL, 
            0xA7617305152D3959ULL, 0xA980373CD6C3CC3AULL, 0x5273F26A2217D05BULL, 0x25BCC313043D3FB8ULL, 
            0x037F5A64AAD8B62DULL, 0xA51C1DD5291BB0A2ULL, 0x721F273CC28B0E0DULL, 0x62C74EDA919E4358ULL, 
            0x46D95650952B16C9ULL, 0x14FA46C8D7B308AEULL, 0xE486CCDA65D8BE42ULL, 0xE512EC8EA357466CULL, 
            0x86EED8235D37D6D0ULL, 0x96FAC8E10A1FE2E4ULL, 0xB0BCF215CD6012F0ULL, 0x4F7AA5ADCCEB9D98ULL
        },
        {
            0x9430BCCEEF05419DULL, 0xC18016D46AAE7E9CULL, 0x40C48F0A2FB91C7AULL, 0xA3C52D931E0B1B82ULL, 
            0xA7CABC04C41259F9ULL, 0xB1AA68B468ECA68CULL, 0xBEDDFD31DDD59CB7ULL, 0x1966F04963654423ULL, 
            0x6FCBAD4874BC70C6ULL, 0xDD3C93D9DDD9E5A0ULL, 0x01295C52EC55136FULL, 0xBBCC926A797DF2C2ULL, 
            0xC6BB5941C227436FULL, 0xA6B87CA75D1DAE76ULL, 0x96B214E29D90C5B8ULL, 0xB14F3ED2D87C1FD4ULL, 
            0x69A4EF7D60941954ULL, 0xE35E4B05854A9B99ULL, 0xC69DE176632F5EB3ULL, 0x836F6C77E8FF795DULL, 
            0xC40FA37A77CEA55FULL, 0xFB9BF703FCB91AC4ULL, 0x244C92B0B775038EULL, 0xCD927937315D372AULL, 
            0xFC4044A3924ED567ULL, 0x4CE27A819D921121ULL, 0x43B57AF80ED2ACF4ULL, 0x1D9F1C854B9098E6ULL, 
            0xC7DE094728EBD84DULL, 0x3BB0FFDEA7810A23ULL, 0x2D56689A948E2C55ULL, 0x967E3BD28C93B246ULL
        },
        {
            0x6BCBA7F9F22A4501ULL, 0xC659032884FD0DE1ULL, 0xB91200BC10FD9BEBULL, 0x31EDF15B6B611CBCULL, 
            0x3067F5A792378EA8ULL, 0x5F00D4DD6880197BULL, 0x64B0DB324358B081ULL, 0xF2FC8A91BB91FDB9ULL, 
            0xC01808F5153C212CULL, 0x088A3721F5D63C36ULL, 0xAB9810CDE84D4216ULL, 0xD97C430E934B052FULL, 
            0x549853843777F909ULL, 0xFEA7CD5FA3E4E39AULL, 0x9E8C2DAF1A9A9B10ULL, 0xCF8CBF8E197A61DEULL, 
            0x7D758569DCAD1352ULL, 0x9CADC917D3F526A1ULL, 0x827A18D73526AE18ULL, 0xADDA2EDD63723E2DULL, 
            0x0DB5BA7E7600A1E0ULL, 0xBAB9BDCC90CC4B58ULL, 0xECDF44CDEFCC43EBULL, 0x89F67C222B1BD524ULL, 
            0x723B3679F0324E5EULL, 0x04A0E2F0EB865C96ULL, 0x897F1367D9A17ED0ULL, 0x2EA89559EC683A8CULL, 
            0x91DE9980DDE552E5ULL, 0xD9C74B451B16A0A6ULL, 0xEA83E89746943432ULL, 0xD3BBAA81F8892217ULL
        },
        {
            0xD9D0C3163F3B4BE5ULL, 0x90E982CE45F2DDA1ULL, 0x7A6276E1DC806CE3ULL, 0x8A89467062A41BA0ULL, 
            0xC6E7DED69275FCE7ULL, 0x2E0DE19E0D967B40ULL, 0x8E363A01DEB192A9ULL, 0x07A30294717AEF09ULL, 
            0x7D4F51E80319E410ULL, 0x58B40CFE60E39ABBULL, 0xBBA6C3CDA07892CBULL, 0x7E89A1B26578AB93ULL, 
            0xC6E9CACC78D0229AULL, 0xF058FE4CC73588DCULL, 0x25CA2E90395764FFULL, 0x9E0A27BF10098940ULL, 
            0x31C23D07239D2712ULL, 0xD3BE1C3BEAB27DE7ULL, 0xCFC3D3E67970B06BULL, 0xF7F729947438A587ULL, 
            0x5CA91FB9D76AE749ULL, 0xBA54A3CE3E9D2F3BULL, 0x0EE7E7DBCB7DD057ULL, 0x7056485590311467ULL, 
            0xC78B15BF6C885366ULL, 0x12C0D8FE6D738B97ULL, 0x98DC6B84BDA73763ULL, 0x43637C28FC1DAD2CULL, 
            0x081F5D0344D211BFULL, 0x490A0D7551599ED9ULL, 0xB9BCDB3AC9911CA4ULL, 0x419973BD9124E026ULL
        },
        {
            0x98DEC45661BD33E7ULL, 0xD123EA6F14AE16B4ULL, 0x49EDF1D0C6C712DEULL, 0x386DC24D01EA0D68ULL, 
            0x255764935070FF6FULL, 0xD7D65E22BA348D03ULL, 0xAC4AF2F0F0654377ULL, 0xE9A2CBBB27150121ULL, 
            0x4D5516836CE12286ULL, 0x066F64BAC1227953ULL, 0xD9C3EC6709AB3885ULL, 0xE59E4A38D145FD2BULL, 
            0xEFEFB72A3F7F00E2ULL, 0x320C1DE79EA2DD5FULL, 0x12D0E31937C6DC56ULL, 0xD409DF6D0573788AULL, 
            0x37EEC3CD229CB2AFULL, 0x08EB9145E5B2D377ULL, 0x9ED4BA6ADC935B5EULL, 0x879DEA134F4BDE6EULL, 
            0x3C5D6D76CAA14FD0ULL, 0x028F145CE5A09D32ULL, 0xEA4605111E30F70FULL, 0x1E2D58C552FF9D32ULL, 
            0x5E95FCAB417E4B51ULL, 0xEFE9C69767F08F44ULL, 0x32E0CA291F112EF4ULL, 0xC68EB83B57BD8027ULL, 
            0x0A20D1027AE13AC7ULL, 0xCB4A5429FEA25CFFULL, 0x9AA8F660BE8C4511ULL, 0xCD56F90EAE9ADE2BULL
        },
        {
            0x2B491E5B47FE1AF1ULL, 0x1AFEC4EF0B35C234ULL, 0xF3733998CA2F4B4FULL, 0x65715AF31A286C30ULL, 
            0x3E4EBFB428202FC1ULL, 0x10A894F691389FD7ULL, 0x6DF2CA64E0A336D6ULL, 0x0BCC103138FC9457ULL, 
            0x9A0080B47CCD28C2ULL, 0x73158462AFC8291EULL, 0xC9B4B6F60DEFC44CULL, 0xFD5FF23E5393F794ULL, 
            0xBE4524708C3E2E55ULL, 0xFFAC9C1942460625ULL, 0x4555478B65EF274BULL, 0xFE8519582BB8DD5DULL, 
            0x22D4D9540A94E260ULL, 0x8606EA0B6BC94F9AULL, 0x5DE09887CA6B9E88ULL, 0x2AF2976301DC7A68ULL, 
            0x3FF13EE8596AF529ULL, 0x4F420B67E8DCD4BAULL, 0xD524AFF983DBF1AFULL, 0x43597693E2C650C1ULL, 
            0xCB954928E7C79B9BULL, 0xC1BA122E33DE42EFULL, 0x3D19A9CAC07D9C60ULL, 0x9F073C3E11A32860ULL, 
            0x26B7F2B5C212C110ULL, 0x43392BBB903F0D4CULL, 0x5C25369E01531FAAULL, 0xE62ABEB1F4E80654ULL
        }
    },
    {
        {
            0xB357F79773A05BD1ULL, 0x17461BEF3991D300ULL, 0xED0AC828FFA210B6ULL, 0xA1674EB05583499CULL, 
            0x2703B00387606489ULL, 0xA32791AE04BB6058ULL, 0x12022D29E252AEB0ULL, 0x8902127D13ED3EF0ULL, 
            0xDBFBEAF30F83B77AULL, 0xFE6C71B36296D278ULL, 0x6927892BAFF5514BULL, 0x6160F2E458EE1F16ULL, 
            0x20C103A7F2AF703BULL, 0x7A80B69473CE6EE8ULL, 0x9D9F0ED0C9648A6DULL, 0x9DBF9BA72162BFB5ULL, 
            0x3B2391724E19DB27ULL, 0x810E29A78B3C2131ULL, 0xF3D14E3E91847150ULL, 0x7C053F7D00186BABULL, 
            0xABB04B4B4B50B428ULL, 0xAA601E3145978848ULL, 0xAD7DD8969C895A79ULL, 0xC9056775336761ABULL, 
            0x61665F53137AA297ULL, 0x322EA4520F7BB986ULL, 0x838E55BC904940ADULL, 0xED1F5791A79BCCEDULL, 
            0x2CDA0A774C227343ULL, 0x13B5E50813702A9CULL, 0x7B621287D1EE429CULL, 0xF78A665A058913D1ULL
        },
        {
            0xF3C8C78DF2DE312FULL, 0x037B1AEF4C32E81DULL, 0x2C015A396B9699EDULL, 0x7B9AE69B9BAB0F54ULL, 
            0x8BD1943EE4C70DE2ULL, 0xB010B0C65CEFA1FCULL, 0x63823195782347CFULL, 0xA761942507678759ULL, 
            0x39E075D88E0CB6D3ULL, 0xFF847EFAA4870CFEULL, 0x279955FFE837CE24ULL, 0x05CAF2FCF96CC664ULL, 
            0xFDF0F1EE18117171ULL, 0xE2946B166FBD1BF5ULL, 0x7A81115972D8C771ULL, 0x6104A8662F41AD6AULL, 
            0xBDEB35C389CF58A5ULL, 0x1AB9E166F694D213ULL, 0xD517092A9FFBCAFEULL, 0xE003A7C97FD7892DULL, 
            0xAED50F96B9D254F6ULL, 0x8B54ADDD6B4BE23FULL, 0xE3AD3252B3F489B2ULL, 0x293B2820A3C1EC0CULL, 
            0xA60622475722C68CULL, 0x7D8ACFA01033B6FAULL, 0x8699744B56229024ULL, 0x6AA61933A94AA9D0ULL, 
            0xAF7B45B02C4D9819ULL, 0x71DDF75BC5DDDD85ULL, 0x8B727A4136A2B352ULL, 0xD87CB895E739C3D9ULL
        },
        {
            0xC5FC07C4C52C9AC5ULL, 0x074EE9A5CA3F3ECCULL, 0x7D614076FE7D7399ULL, 0x4FDBD3D0AE5EF732ULL, 
            0x3A2ADEB2E3C96C9BULL, 0xD2461A8AB4708711ULL, 0x79F76860310D506EULL, 0x4525645830723ABFULL, 
            0xA28D726AF9E017FDULL, 0x9D3D63FE2C7D31D3ULL, 0x6C8E483DC63F964AULL, 0x7923140D265189DAULL, 
            0xBC050F9649C0E39AULL, 0xB9395091152AD245ULL, 0x9E4DAD1F5D304C9BULL, 0x4BDE44A856A599B3ULL, 
            0xCC7ED3E9EE792FE0ULL, 0x50EAC82FE37C402DULL, 0xDF4C3B8DC5380F82ULL, 0x373DD2DB506C6610ULL, 
            0x4B1E35760BCEDDFDULL, 0x004E2B6017DC15A6ULL, 0x2594BC673AE9D4FCULL, 0x5F6FE490B6997BE3ULL, 
            0xD9D51B48776AF2A1ULL, 0x2600896F83F66701ULL, 0x36F51F09B1438B4DULL, 0xF9A5B3B5EB4A3A9CULL, 
            0x4192227EEA5EB1FDULL, 0x0A030DAD0BF7A23FULL, 0x195240D5B67F859DULL, 0x630F291EA361A5D1ULL
        },
        {
            0x1BB32C403B31F2B4ULL, 0xD889530F1327A233ULL, 0x9CA3EEA44FFC5CBFULL, 0xF5E7A3F849D4CF59ULL, 
            0x35452FFDE2C2F12FULL, 0x3A5B993FD1FBF528ULL, 0x572F372F424ED16BULL, 0x36519BB00CE410C4ULL, 
            0xE1BB59E4987BDD26ULL, 0x31F4B4A1C15F81B1ULL, 0x6B824955260FC811ULL, 0xA5DB362F36564638ULL, 
            0xCAF4FDEA3DF8F18DULL, 0xD26E1006D041E76FULL, 0xD2797E72C7AD1791ULL, 0x77CAE95E1A869A76ULL, 
            0x23B70EE666F6F97EULL, 0xBB584655B9AADE5AULL, 0xCFCBEF991D8CA17AULL, 0x2554C539EF11FFDEULL, 
            0x24E4A5CA4662A67DULL, 0xC9552203B19AEADFULL, 0x0808EE4FBB6AF763ULL, 0x2A8B09D1678A85A8ULL, 
            0xFC9BD789D61E44F5ULL, 0x70320BDD66BFECA2ULL, 0xBA3A3850C6448567ULL, 0xA6F70AA17CB84CA5ULL, 
            0xFE436456BADF0A18ULL, 0xB6FE209EB471DA23ULL, 0x9C2D83D0EA932634ULL, 0x77BBC9282A772923ULL
        },
        {
            0xAFBF0643748EB2C9ULL, 0x53C3DE62E03DF0B6ULL, 0xCA174E1B53C6CC2CULL, 0x6B835C934DA9B26AULL, 
            0x17993B0E4C6AF87EULL, 0x82BF5BE7B99B0071ULL, 0xE10E24E0817B3AAFULL, 0x847FBAB9695EB6DBULL, 
            0xCC2F723230F01C81ULL, 0x5C614DD2B12A8656ULL, 0x6ACE329E8D006630ULL, 0x70B9E7BE55993D3EULL, 
            0xB97506FBA813F17AULL, 0x4D228DE1FFDB58EFULL, 0x272F0393932B5A0DULL, 0x5397C876DB8D2C44ULL, 
            0xFF846D890DAC4671ULL, 0xA78880FE3680340FULL, 0x0EE6C57472F51785ULL, 0xE6D88CAAAE43BF87ULL, 
            0xACD9E3DB5A5157EBULL, 0x6329CD2162196689ULL, 0x1CCB722074673498ULL, 0x4E36CEA5A8BCDFF2ULL, 
            0x9C98023D2D24E3AAULL, 0xE099ABBCDF974A91ULL, 0x88EB3CFA3BE89E21ULL, 0xD83B9214A9A2034FULL, 
            0x4044CA3CA0A14CB4ULL, 0x2F6458AF3DFAE662ULL, 0x3753E14BB0D3F806ULL, 0xB0A94EF9AEEF0B1BULL
        },
        {
            0xA7259CD588681C71ULL, 0x3A5650ABA6FB568AULL, 0xDD7055C793CD2912ULL, 0x79DA5374FB1E6712ULL, 
            0x0564E0A8FE6EA68BULL, 0xF7D5B7E38FCFA305ULL, 0xE39DC556CD93AB37ULL, 0x93E349A64CEA1036ULL, 
            0xD0A2ECF0DD8D5CA1ULL, 0xFC1C7E3BAF1660A2ULL, 0x8CECCBAE0229CC7EULL, 0xB65D439BC3C29429ULL, 
            0x577E3D72A3ED4BBAULL, 0x1DF89D96BCC8AB95ULL, 0x00667C562B0FD4F9ULL, 0xD800731AB3FC7D3AULL, 
            0x0E0D35767A96DB21ULL, 0xE1B9955D248618E6ULL, 0x05C0ED4D84F7356CULL, 0x51C21E57E2D10505ULL, 
            0xCD2F86A4FC5DE9A4ULL, 0x28534C15EF35B6CCULL, 0xB2EF7985F61FAF16ULL, 0x1A582A308A6F47B3ULL, 
            0xAAB7B981F20F3EB7ULL, 0x81B94977AB37E44DULL, 0xC9745E5A62D0C394ULL, 0x9188A589CDCF2DB3ULL, 
            0xB1603D1667D341D2ULL, 0xA732E43796191F50ULL, 0x2747B91B84DA69F1ULL, 0x4EF06476667FD5BDULL
        }
    },
    {
        {
            0x1D12E0F6960E8533ULL, 0x3762CE6B71D3F82BULL, 0xDDB5517F2A967839ULL, 0x6C3709B9D6618674ULL, 
            0x9A6B93FE4C6A218FULL, 0x9DBD55DBBD74255CULL, 0x92592352F9943296ULL, 0x057EBB97FC64DB80ULL, 
            0xCFBF66E6ED529A27ULL, 0xF7036319CAD7C4A0ULL, 0xCCF4C13C8D2161ECULL, 0x303AC2454A70A494ULL, 
            0x32BB53DEC467ED0EULL, 0xAAAC07C3AF9C564BULL, 0x1E3E757710A78A8AULL, 0xFC3651FE06692693ULL, 
            0x34C2790C73D9A900ULL, 0x695C1BA3C0B631F9ULL, 0xCDEF1EDAF60B86ADULL, 0xA06AE2E9EB76D5F4ULL, 
            0x86851924AD11F6E9ULL, 0x84E1A6BB2A6BB24FULL, 0xB42C1E93C8CAE811ULL, 0x80B42E1DE749B520ULL, 
            0x59C445A20BD6D4ACULL, 0x01D1F914258274DBULL, 0x9D8459F9277BB07FULL, 0x6E1BC737BB4448F3ULL, 
            0x3FA9F40AF217258AULL, 0x235DBF2FF3D3B2F5ULL, 0x9477698BF0D5E74EULL, 0x3AC3CF85B3031BF0ULL
        },
        {
            0xF17B627258EDF133ULL, 0xE2F60B477D131109ULL, 0xCD7984ACB45380AEULL, 0x805389D450EE5B42ULL, 
            0x21F7F8DDE8243E03ULL, 0x17D3FFD52CA106D7ULL, 0x867035E9F9B3E3E1ULL, 0x41A303B1D6CB9983ULL, 
            0x2E990D810F98A519ULL, 0x5457EE4915C1AF62ULL, 0x9B181BFD5611F552ULL, 0xE9E80A29D27BD44CULL, 
            0x756A0FB67125C5BAULL, 0xFB3F5567938D1470ULL, 0x537F9A347F6E633EULL, 0x238AF50CA412569BULL, 
            0x1647100C3E372DFDULL, 0x7FBBB702A9C23AC6ULL, 0xCF023929159C8FEDULL, 0x080B3B37B10307F8ULL, 
            0xB65BFFCD614E6711ULL, 0x307CF413924AD604ULL, 0x199F3478D7030D90ULL, 0x5952B8A305C3EFF0ULL, 
            0xFF31FC64569DA40DULL, 0x3F35B544C6939804ULL, 0xA6B4A65A65BFC635ULL, 0xF05277D32E278142ULL, 
            0x53FAEE1EDFFDBD53ULL, 0xA076581A31D5F472ULL, 0xAE2B334F25071075ULL, 0xEF1DD6ECBF15C1E2ULL
        },
        {
            0x9C72EDBBD73AE580ULL, 0x29DF1A47661DF31BULL, 0x01F3DDC221690CF8ULL, 0xA2E3986146E475DFULL, 
            0x3F4F4B3CC9C6A6D6ULL, 0x24ECA7C3AB56006AULL, 0xCAE703559BCDC70CULL, 0x3C690B4394F89C34ULL, 
            0x4A2496A481001385ULL, 0x94C0DBFF2F3626FFULL, 0xB9E0963E884C67E6ULL, 0x3C37F6D1743F8384ULL, 
            0x972600CC8B55426CULL, 0x2CF82577F8CB893CULL, 0x32A553CBCB9B4B7DULL, 0x6E702F676F8E7916ULL, 
            0xD22E40042AE840B2ULL, 0x3ADE4ABA3C974470ULL, 0x750091448D0085C6ULL, 0xE204981554FDD8CCULL, 
            0x22FDD66038CB7A03ULL, 0xF91A1934AFC80ACCULL, 0x8498C07EFF1E7E8EULL, 0x133420D169148714ULL, 
            0x667CD1E8E3D5FD80ULL, 0xB9C3C4CA2DBDB957ULL, 0x37AECF8BC73753CDULL, 0x94863B0D4D806EC9ULL, 
            0xA8072D1FD045F653ULL, 0x83595E5589555AAEULL, 0xEE8CACE83CF6FCACULL, 0xA48EBE6BF0BD1C40ULL
        },
        {
            0x33C35057AAD11896ULL, 0x2CB20BB9698D7C82ULL, 0x148E3B9FB570C4ADULL, 0x9569EF627E56FF8AULL, 
            0x4D9124BBEE25F552ULL, 0x3CF8C52637D8866DULL, 0x2F88C7F06ECE7BEEULL, 0x892E4E9BD01BDED7ULL, 
            0x958B3A678112548EULL, 0x17FC300FE4059308ULL, 0x3FB5FFC1ECD6728FULL, 0xABDD006709601B80ULL, 
            0x2AE992461B13D59AULL, 0x755B4E9A0E9E8604ULL, 0x8DF35758665A1612ULL, 0x2DA80048BAF29907ULL, 
            0xD65E3026353F9148ULL, 0x2842751B4F5482D3ULL, 0x6E395BEA42E7A979ULL, 0xE2E223C6201D049EULL, 
            0x21FFAE8C09E1995EULL, 0xAAFF4B45EB72C13AULL, 0x82DA67D2DCA804FEULL, 0xA86F8DDC15D5200FULL, 
            0xF30ECF77791F23B9ULL, 0x2730F8C243C46C6EULL, 0x668B64049A60A9A3ULL, 0x9B71981C7E40DF96ULL, 
            0xC62FE96DCCC37BB4ULL, 0x951903FEB80A6E5FULL, 0x35CA725F37D50F2DULL, 0x136A1D8256BC06CDULL
        },
        {
            0x9A6144D7F5EDD573ULL, 0x472B9534F7530A85ULL, 0x425356B60C9E2CE4ULL, 0x2D9BC882B52F444AULL, 
            0x901CAC21C70D6DC4ULL, 0x30B82101E3DA1A40ULL, 0x747D1E864CDA651CULL, 0x1841630F034A2F16ULL, 
            0x4C47F8553083472BULL, 0x2A32F9DC905B912AULL, 0xD7E7E3DA70252C8EULL, 0xF8F8C7E1F4B5AECEULL, 
            0x10ADF134B3B5A7CDULL, 0xF531D1CBD9D499E3ULL, 0xB378AEFFF82C86E1ULL, 0xD6C7D668F3D2ECF2ULL, 
            0xDF8A93EE53F0E3BCULL, 0x91FE697D420EC93DULL, 0x091FBF92DE6BB91AULL, 0x713DBE4E0F5584A2ULL, 
            0xC4C71C1977808EB4ULL, 0xB184D8DE4862ED34ULL, 0xDE673F997859A2ABULL, 0xF6967E2482E8AC3FULL, 
            0xC255CD82778F6437ULL, 0xB676D09FA72C0C45ULL, 0xCDBFA19D9C77C3A6ULL, 0xFC08F36365AFB15DULL, 
            0x74394580CBE7F9D0ULL, 0xB23A4FDE38B6F97BULL, 0x8850D66048412EFFULL, 0x80BD28470580B62AULL
        },
        {
            0xE00EDF26C4979338ULL, 0xAB6B3D89DA033BCBULL, 0xC6CF5719326E207FULL, 0x3F55D3A079E469E2ULL, 
            0x73266384F3F7859DULL, 0xB844884776EA0CAAULL, 0xFB4B6D6DC4D8B5AFULL, 0x56C6123E1B7E3B78ULL, 
            0x735B6882D05ADC84ULL, 0xB6789018EEC0CB2EULL, 0x9E2959D24C8FF730ULL, 0x53D3021229DA8607ULL, 
            0x2079E1896D561AE1ULL, 0x6D4D774A65D9CCF7ULL, 0xB5BC008960E6B5CDULL, 0x0020132E5F202802ULL, 
            0xE9181D2EA1BFD4D3ULL, 0xE5BA823A684DD4B9ULL, 0x47B57EE02D685D0AULL, 0x94EA2B0A9784420FULL, 
            0x844F1BE19FF32801ULL, 0x6A945C617F7F8D7BULL, 0x924EB8F19069D15BULL, 0xB5532761E3152F91ULL, 
            0x652B444E2F75B2ECULL, 0x28CBBF350C6A5059ULL, 0x857349CFCF790460ULL, 0xA75EF5C2C66E8632ULL, 
            0x58BF18E5C82E49DFULL, 0x39C3C507B6FD17DFULL, 0x4D2CAE5FE8AC710EULL, 0xAACF47E83B96394DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseFConstants = {
    0x571E06063D7698B8ULL,
    0x7261CB4293D6B13AULL,
    0xB7CE55A2A5F31153ULL,
    0x571E06063D7698B8ULL,
    0x7261CB4293D6B13AULL,
    0xB7CE55A2A5F31153ULL,
    0x1568B6F900AF7447ULL,
    0xE712CA9E1C8B041FULL,
    0x52,
    0x0F,
    0x31,
    0x71,
    0x9E,
    0x3B,
    0x08,
    0xC3
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseGSalts = {
    {
        {
            0x13C9C2994FC833E0ULL, 0x0FECB8AF85418BA1ULL, 0x3D83641A1398186EULL, 0x2E49F97162DA07EAULL, 
            0x4949F798C668A8E3ULL, 0xEBF52AFD06A23533ULL, 0x76C3307B84BAE655ULL, 0x6069ED4E9CA25257ULL, 
            0xC013F3472AEDA0E7ULL, 0x6FFCFF91C42441D3ULL, 0x081E23C25E3F2509ULL, 0xB0A39076612CC9DDULL, 
            0x0863CA61B233E162ULL, 0x4665AE15F6994D28ULL, 0xF5A835100D796B0CULL, 0x8FBFE26319935931ULL, 
            0x7F053AD750BFA6AAULL, 0x99F2AAACAEEDA849ULL, 0xF1BC94198DDCC958ULL, 0x8EC6763744CE05E6ULL, 
            0xC29F32D4495E70B7ULL, 0xEF2B7B426931FE69ULL, 0xC5026FC999D2255FULL, 0xF0C4625AE6B149D3ULL, 
            0x77D0CB3A6B15A283ULL, 0x0A1348FBE5F2D9D1ULL, 0x826C85570832D60CULL, 0x924E291DC696567FULL, 
            0xF066DDE8D520A735ULL, 0x1207357ED03B8437ULL, 0x2387A1C546ABB482ULL, 0x87A8DC2367430062ULL
        },
        {
            0x35028E8A9BE4B0FCULL, 0x8DC8CFE285940520ULL, 0xA63B5B79F4513391ULL, 0xBB069C0727BDCC9FULL, 
            0x3972C61910185FC4ULL, 0x0F8779B3185D0D9BULL, 0x11330287061BDA4DULL, 0x26F7BF93C7CF545EULL, 
            0x0BDDD924E4E1AA60ULL, 0xF34F13BE4722F780ULL, 0x550100E9D569A7DCULL, 0x8C0244BDEFB58998ULL, 
            0x2C95298F8F24204FULL, 0xD3BB5B9BBBB1735BULL, 0xACB92F709AD16749ULL, 0x5DA7EC6B9AC7C0EFULL, 
            0x268DA1479DD35B4CULL, 0x37029B968B75962CULL, 0x1755748B393816BEULL, 0xAAB05CA6C41AE301ULL, 
            0x1739A1BFF82B6A5AULL, 0x3A5BC3AC2E3BF825ULL, 0xF93B961EEB223225ULL, 0x36205927A264F4D3ULL, 
            0x1C1D64BFF5DBB963ULL, 0xF9F7E7003ED9942EULL, 0xB3352D910101F048ULL, 0xF0457880E2131D0EULL, 
            0xCA1C2DDA8D01CBB2ULL, 0x80A356285C1D5627ULL, 0xA854D2D924DA9D21ULL, 0x693A153D5D40A1A9ULL
        },
        {
            0x1A8A3D3B54FCB5F2ULL, 0xCFAD412A74667907ULL, 0xBD67FE7F943C562BULL, 0x553872A815D0CF26ULL, 
            0xC39A8E93D2B6EE7DULL, 0x62B7B8C4586247FFULL, 0x8C6981A69CC1BF32ULL, 0xD71FEAF2C985009AULL, 
            0x5338D581D7731753ULL, 0x26B26462A06FC0DBULL, 0x4659C0DBC7012E1CULL, 0xFCD8AFD4EE0005E8ULL, 
            0x893AA61757A2E973ULL, 0x384CC35B9672F477ULL, 0xEF88ECED80CD50CFULL, 0x075B028FE9B0ECE0ULL, 
            0x1FBBC4223C41D4A3ULL, 0xC4F3C8357C5BE0E8ULL, 0xF4BB814996CF59ABULL, 0x920D868672A8E55FULL, 
            0x6EB778F88448D4B5ULL, 0x9EA039978C7672BAULL, 0x1C24C974C3B5DD11ULL, 0x44A3D6645CCD4217ULL, 
            0x3E59CEE0BC8F1E74ULL, 0x8C8006D2EBC866BBULL, 0x4A22B0723FC6891CULL, 0x0BBFCEE5A8C0C247ULL, 
            0xF2C2E2123BE05A27ULL, 0xD17DF79150E6C658ULL, 0x1CB897B1E1AD6ACBULL, 0x8E1FF19CBB9D7619ULL
        },
        {
            0xDC846EBF62F42FB3ULL, 0xAC69728E54C40B66ULL, 0xE9170D39BCED76B9ULL, 0x7D739BE4C0527927ULL, 
            0x204043A96951860BULL, 0x0F0AD17A047F3294ULL, 0x0A2E9A86D32242B9ULL, 0x10D11A6B4FD6E90AULL, 
            0x040578E532550D8FULL, 0x6240C5D272456A3FULL, 0xE4BC6A33EE88483FULL, 0x45BFF725442F11D5ULL, 
            0x806AC1268DE82ACDULL, 0x08511CD42B17950FULL, 0x9F042421FF93F162ULL, 0xFC380365981C81FFULL, 
            0x1E93E0D10F6B8809ULL, 0xC9F8352F75FA7B9DULL, 0x97E3B538FCC7E12FULL, 0xC732FAEF742400BCULL, 
            0xE6C773ABF935BFC6ULL, 0x904EDE42802DCC40ULL, 0xFCBB7F5B7BDB28A8ULL, 0xF090EEC079032FA7ULL, 
            0xD240A2B50A442C56ULL, 0x63939CAE3D2EF9A4ULL, 0x04D15FB353B6FFB1ULL, 0x6932CECEB1302A50ULL, 
            0xCCA6E738D79E46B7ULL, 0x6758D1CB75569BD6ULL, 0xC590E4B92A0A29D9ULL, 0xD27B9609F2670A62ULL
        },
        {
            0x8FF0485CFC191B21ULL, 0x799E0206A478C43FULL, 0x946EC2F1C4A62C50ULL, 0x75FA382DF6FEBF68ULL, 
            0x775808978023EF11ULL, 0x2A773C5D1EFC1321ULL, 0x198F255A62D26C96ULL, 0x0CBC92B177F97A15ULL, 
            0x2FCDC1745A70D1ACULL, 0xBB8E43973CA96A1CULL, 0xE5881CC4E81F2963ULL, 0xB17B3D014ED16276ULL, 
            0xDDA3AA049F225841ULL, 0x4306FAAC39FBF8C8ULL, 0x6E1DD3C1B923FACFULL, 0xA7FD70B90BE6656EULL, 
            0xDAF1B26605B59D7FULL, 0xDE0FF4952E737809ULL, 0xE58F49DD7D18D90CULL, 0x0268B684C71F9F26ULL, 
            0x7997A780714C4AA8ULL, 0x01D0587BD9324130ULL, 0x5335E49A6AF9E3D3ULL, 0x78A51BA9017C68E5ULL, 
            0x5593DD2DB773F75AULL, 0x93DE54C3B72A11B8ULL, 0xD5CAF516F2D7C647ULL, 0x411496CCABA6B96CULL, 
            0xA1783C9FEE7F4DA0ULL, 0xA2C047B9F2CB2241ULL, 0x3280F4A72A3A8B1CULL, 0x15EB382DF05B7044ULL
        },
        {
            0xA50C4A36BE11CB37ULL, 0x71D3A81434DD2F51ULL, 0xC707B7AD71FA3E92ULL, 0x9DCA9AB0764794FBULL, 
            0xE045A7755F0160E5ULL, 0xE2D125557D137784ULL, 0x8357F6AA032F7DB1ULL, 0x9809471F0D290B42ULL, 
            0xC1DB255756DB548DULL, 0x6BAB1966FC93F6E7ULL, 0xEFB924258028AC45ULL, 0xC827220F27DF4FD5ULL, 
            0x20CEEF87509AF8C7ULL, 0x11E3EBC474D59E32ULL, 0xB0822DAA8C8B4F57ULL, 0x026595811F6DE67DULL, 
            0x296F02364EA2526CULL, 0x78CDBE7B904AD2E5ULL, 0xF24F8DE15D4F4217ULL, 0xC5845584E716BB75ULL, 
            0x5761F7E62386BC65ULL, 0x76D2C6D43FC3A87EULL, 0xBFF105D2AC4E6FD3ULL, 0x2A44D388CAC23DE2ULL, 
            0x9C9F661A67FC35B0ULL, 0x50E08CFDF9504D6EULL, 0x7A9E1954CFD6695FULL, 0x3407127033D64FDEULL, 
            0x522727D57CF79F65ULL, 0x5A9ED77529031B50ULL, 0xE7FC28C6782C24F2ULL, 0xCA557D8E184AA81FULL
        }
    },
    {
        {
            0xCCFB5BF8B9CECBEBULL, 0x0B876D4FE44F4EE2ULL, 0x78BC575B5F1B02F8ULL, 0xBB583331DD0FAA71ULL, 
            0x9BE7B38AA470CD11ULL, 0xE009D37D8376A981ULL, 0xAC5197A46964AE66ULL, 0xA2F6649BF25132F9ULL, 
            0x7312C186AD384F23ULL, 0x00AD20D992C7FC83ULL, 0xA2E83CC5B3C35C02ULL, 0xD836F21BCB2DA0F5ULL, 
            0xE5A664F14F38F03BULL, 0x2E88D6DB4A5E928CULL, 0xAF9A758C04CD558AULL, 0x16152415D2A884B9ULL, 
            0xB8311EE754F4BDADULL, 0x289A04113F252C7BULL, 0x6CB57855B3D7621DULL, 0x4A6405BA2223BA19ULL, 
            0xCC788C639458C435ULL, 0x2B196EE6F478DE9AULL, 0x0D86F255739E34FDULL, 0x72A73F7F03AE2B70ULL, 
            0x6B5A3F3795E10B23ULL, 0xC3437EEF6F747063ULL, 0x08B63283F1FA60D4ULL, 0x876C13AFCA078C62ULL, 
            0x830EE6EF6314F9ACULL, 0xE06CB1E6BD2F40E0ULL, 0x28A1314958B67058ULL, 0xA5F5AB581C78FCC5ULL
        },
        {
            0xCB3BD20A53CE0C27ULL, 0x8E01640E50C63A58ULL, 0xC92C5BA8259861DEULL, 0xBA8282CABD8858C1ULL, 
            0xBB0A28947E4F3FF7ULL, 0x34FFCEC50BDB904DULL, 0x179A41AA057048C9ULL, 0x23F387EAECA3B15CULL, 
            0xA6DF99400FEB3358ULL, 0x197040266EBE2964ULL, 0xEEA71923E7F339D2ULL, 0xA7258DF884B14C47ULL, 
            0x16B287351FBD56ABULL, 0xCDA0E8952462C07EULL, 0x352567D49BC6DBC4ULL, 0x8F729EDAFFA57524ULL, 
            0xBEF9979EA6DFB98CULL, 0x7634E3633E4D7D42ULL, 0x3B266600B76FC6FCULL, 0xAE438F3E0755E475ULL, 
            0xC0EACF23B3DDDF3EULL, 0x710806E2BFD9B583ULL, 0x4FC190B22619ACFCULL, 0x772753B610A89E8CULL, 
            0x7E8A5CF6278D04CCULL, 0x58102F8E9F5E94DFULL, 0x8C9E80C51DD75159ULL, 0x8E5476EB6BB5E04CULL, 
            0xF3C4FAB1849D0550ULL, 0x7F15C220E3D86EBAULL, 0x2797BAAD984556D6ULL, 0x58F04AA067E670EBULL
        },
        {
            0x1B27281458B9BDB8ULL, 0xC1DC2DBC2021E204ULL, 0xBBB3F26F17988466ULL, 0x5F7E54E11D7ACAB0ULL, 
            0x2C89450399A6FDC0ULL, 0xDC795FEB3683CA7DULL, 0x656924B9DB5F8421ULL, 0x73FE939881287A29ULL, 
            0x385C4591173A52B6ULL, 0x5EFF2B1A62BD4D9AULL, 0x42A10BB86DF46DB9ULL, 0x8F34E0E1C5282FACULL, 
            0x88C576D745B6AAA8ULL, 0x9B1F62CCA1348D3EULL, 0x54D7AEF5760CB90EULL, 0x1F9EE6CFC843DAE5ULL, 
            0x9552610ED6C4A663ULL, 0x368C581242A2195CULL, 0xD60802E9BDEC048AULL, 0x0F51BB9A5B5C6B90ULL, 
            0x7BBFF64F80E0CD0AULL, 0xB050CB789B8FB3A9ULL, 0xC589BEF1F49AE693ULL, 0x48596AC50D538625ULL, 
            0x420525701B3F4852ULL, 0xF2BC4BD44598A5E3ULL, 0x793E4067E3A9D1E4ULL, 0x2396E0956945190CULL, 
            0xD99E51079DEB441FULL, 0xED171BA7660DA129ULL, 0xF4920763A11893F8ULL, 0x0D854259E463BF38ULL
        },
        {
            0x247EF82725360208ULL, 0xAD310D45D0FFF1EEULL, 0x0A0896DEACB04E32ULL, 0xF14733CB8051E094ULL, 
            0x6E0CEB8DD9BEB233ULL, 0x6FF152DD411E1F04ULL, 0xBC6583D394D02921ULL, 0xECC7FD9F118EB5DAULL, 
            0xE963520B373A4E38ULL, 0x8902E5B390589B6EULL, 0x4EDE0AE4DF835945ULL, 0x8E36D9EA60FE99E8ULL, 
            0xAA92CE0CE7E9F8C7ULL, 0x610EB876990748D8ULL, 0xC29557DA8C6BA365ULL, 0x36109BA86E9736B0ULL, 
            0xB08AC962ECE90819ULL, 0x94E5653E45905118ULL, 0x090EA78A807A9736ULL, 0x95E9C20E3759E76DULL, 
            0x256CCE6B32D0BA1BULL, 0x49823DF1DA5A87C5ULL, 0xE7D3CC97A0CB5AF0ULL, 0xB94A88CF8919FAA8ULL, 
            0xAEE992DBD00F04D5ULL, 0x5ECB4D62280D981FULL, 0xB583D270B584514AULL, 0xD07F690D1307E0CCULL, 
            0x8E55DB33D5E64A8AULL, 0x80A200755690E994ULL, 0x9B0AFEFE291C9BC3ULL, 0xB53F5C7CBBB03658ULL
        },
        {
            0xD3840F71EDD95457ULL, 0x9620E54C90171885ULL, 0x922FAFFD41476BF3ULL, 0x4E6FF92A07923C4DULL, 
            0x2FD12BC46F07D8C3ULL, 0x8FA920DAE0EAABD2ULL, 0x238C8C4EEEF4C3D1ULL, 0xE1B12A8778EBA2D7ULL, 
            0xCDB4E17ACA627822ULL, 0x3F34A1DDAAF67843ULL, 0x393EAA1FF4D72D64ULL, 0xBC78DF59B955290FULL, 
            0xF806D7A1188AF3A7ULL, 0xF189310315F1DE06ULL, 0x0C7CE23EA0D8D2A3ULL, 0x76D95426FAE36B16ULL, 
            0x4B55702397850C01ULL, 0xC0725148624A00B0ULL, 0x14A4D15C4FD7E91BULL, 0x6D2F2E99B28744EBULL, 
            0x18009D7643EC6B90ULL, 0x7B385ACFD3FC94C3ULL, 0x5A844AF9FBB8A651ULL, 0xF701812834BF3939ULL, 
            0x10F12A71B2BB694BULL, 0xFDB575933875A603ULL, 0x0A02AC94D668E412ULL, 0xB2CBC88F4CBED620ULL, 
            0x3243305FD6BD4251ULL, 0xF9BF1D60FB41F20FULL, 0xB39308452ECEAA48ULL, 0x5FA7780738CB1898ULL
        },
        {
            0x4B3CF511705966D3ULL, 0xE0386DA42603F3E9ULL, 0xD8E4BFE49ECA5CCDULL, 0xD088A50006639E6CULL, 
            0x0655E337058FEBA0ULL, 0xB99A45DB6466723CULL, 0x4D1F80203CA92160ULL, 0xCE9341CAA187D2D7ULL, 
            0xE09D2F0B5376993DULL, 0x91A6B3E9E2E76FADULL, 0xB7FE12BCF156225EULL, 0x5CF0F6C43A621C02ULL, 
            0x6BB0DA8928868C93ULL, 0xCB2181D7A76E3D27ULL, 0x9A60384B7E37EEF6ULL, 0x967ED1EA095C2B36ULL, 
            0xD40A11E4985A73ABULL, 0xA7163ABF439711FEULL, 0x34700CD8B7E1B052ULL, 0x161FA60F7AFCFEA7ULL, 
            0xE4C4C75AEFA566ADULL, 0x233DE529DB8CE4CFULL, 0xEF2673502B1E16FFULL, 0xDF2E126D534A6884ULL, 
            0x75B806CD46AC0D72ULL, 0x76CDB5B031D3AD4DULL, 0xD02BDAE4E41EDEE7ULL, 0x1171B77C029E20C3ULL, 
            0xE93DBAD9AAD145ACULL, 0xD30879F6699BC264ULL, 0x4E02432E9E4EC846ULL, 0x78B10D6E0F93CD3CULL
        }
    },
    {
        {
            0x68588C48B1C396FDULL, 0x6719E8B1D7126A6FULL, 0xE6B87FEFB59AC7E1ULL, 0x9B054BE2BEC32E9EULL, 
            0x51CD7CC06400FD46ULL, 0x424E24D5B032C20AULL, 0x17F85402ED97236BULL, 0x526A0367C42CFCB8ULL, 
            0x561DF97CC951B61FULL, 0xBF871D37727EC65FULL, 0xD30CE5919CF483B8ULL, 0xC7C2D22795E499CCULL, 
            0x4698E8BF86BD2674ULL, 0x4851DF8DB3EAE805ULL, 0x35866A6E12C99CBFULL, 0x67C1E120C7012AEAULL, 
            0xEBF09435D2E7F81CULL, 0x527AD6E1D95BA710ULL, 0xD293B9B72DA2DA6AULL, 0x6CF5795533AD7684ULL, 
            0x13D1D3A9D3DC481DULL, 0xD50F19EEEA000960ULL, 0x072D7E3AF4E57B58ULL, 0xB40B5B207FE2C17FULL, 
            0x5970B713D2E48783ULL, 0x454167230E45079DULL, 0xDD2F01B3A91631CAULL, 0x60F6041A1E4E515CULL, 
            0xEB39423F0C7BA99CULL, 0x5B515663DDBC6096ULL, 0xD021DF18CC0083A1ULL, 0x35E696CBB95FCF4AULL
        },
        {
            0xF6DDBCA3E954C053ULL, 0x6BF58F748F2D7E9BULL, 0xEC437471B94912B8ULL, 0x88561E659BF9E483ULL, 
            0xD473E85A037E9835ULL, 0xA0D3045DF22AB7FBULL, 0xD7077330236FB232ULL, 0xCE76E49028CDA92CULL, 
            0xA44911F8116C5D7CULL, 0xA08F79C495ED764BULL, 0x0C9FEB14BF3776C1ULL, 0xF059A9378ABA8371ULL, 
            0xC5B66492D71B645FULL, 0x246AB7697A47CFA8ULL, 0x3C891879532497EAULL, 0xBC85DC35F8F801FCULL, 
            0xC9C0E2D3BA04EE3CULL, 0x1E0355DEA13D5207ULL, 0x5B5945CA52AAB4ACULL, 0xD7D4CFC60970BE08ULL, 
            0x9D67ED345DEF3D0DULL, 0xC3C08069C7DF7ADDULL, 0x2B05C5F658AE480EULL, 0x6B36B5FA4E324134ULL, 
            0x1153222E8AF6B0D7ULL, 0xBDADFCF752400D8DULL, 0x9C9AC5A0DD0B6119ULL, 0x24D2388297B2E00EULL, 
            0x440F23652B0598C4ULL, 0x44467C3440DC6358ULL, 0xA097425EB6564415ULL, 0x0FA1FBD7122FF301ULL
        },
        {
            0x58D8B341C8837306ULL, 0xBD6F9F8DFFE88C0EULL, 0xFEA77B760C5D117EULL, 0xAC570657293107D9ULL, 
            0xA854A2E0AB4C3A40ULL, 0x2A6041E78C60CF7DULL, 0xE25E87491375D439ULL, 0x54B0E1C6764611F6ULL, 
            0x1F1A9E6A910C3DFAULL, 0x410404FB086F9697ULL, 0xE962261EE45150F1ULL, 0x0BC958D55BDF06B2ULL, 
            0x74777AE5FA79CFA2ULL, 0xEDBD438C8312F24CULL, 0x4986858FCD396F66ULL, 0xC90C8837733B39AEULL, 
            0x262E16D265D46273ULL, 0x90C2A30C018FF601ULL, 0xEF2F97D990EE4863ULL, 0xFF5811D42E9AFBFBULL, 
            0x63D0F4EEC20D3CB9ULL, 0xE9D72C47C65A29F2ULL, 0xA7FF57B8BE393F2FULL, 0x2EB42ED326DF885BULL, 
            0x37EB63744290F4F2ULL, 0xD293A7F1FCFA7939ULL, 0xD8BB9D34321E56B4ULL, 0xB9DA8713E1D65C43ULL, 
            0x105DC0B82D4891A7ULL, 0xB2B372F5617D22D9ULL, 0xB9DA490AEADBF80AULL, 0xE8A62721193C666CULL
        },
        {
            0x4D79F606A2AADAD7ULL, 0x80A9A83BB2315607ULL, 0x00E003528921105DULL, 0xFD1D3F127602DD12ULL, 
            0x1FC55E9CE3DB0B45ULL, 0x4252C327CEDC246EULL, 0x428FCAE567B61110ULL, 0x00FE41F534FBADD4ULL, 
            0x6DF41C14D7869216ULL, 0x943FAF50F4F91746ULL, 0x8534C7675057F365ULL, 0x20B80936C83F3ABFULL, 
            0x61686533632D627BULL, 0xDAE785E8E61A2C2BULL, 0xF0154DBA989C6550ULL, 0xF1E1CAF318CBF161ULL, 
            0xAFAB6A2CAD6358D9ULL, 0xA639A25E5F8F3D50ULL, 0xC2A2D790A7013CABULL, 0xCC26BBF28F24CD73ULL, 
            0xB571227FD0C0B035ULL, 0x16300FC286B90597ULL, 0x0F24C7589CDBDD95ULL, 0xDB0B1B39E747AD12ULL, 
            0xD7D3EFB972FA7554ULL, 0x8955D6CE3163A39BULL, 0x2FD18025A2C59901ULL, 0x87A55FAC51BEC300ULL, 
            0xC9C29D8E309716BEULL, 0xE7A69E294CF8AB0EULL, 0x783AB4DA3D8F345FULL, 0x69A60907877B15EAULL
        },
        {
            0xD070862ECA35B539ULL, 0x3C04BCE0E34199F5ULL, 0x4B1C88BAB66049D7ULL, 0x202ED6D2D6ACB238ULL, 
            0x965E3FC04300B365ULL, 0xE8C6D233815449AEULL, 0x725090C6251AE4B8ULL, 0x942D637218A38A68ULL, 
            0x637DCC03887B9E96ULL, 0xD33477DEBF13871BULL, 0x25E0B0077ECDFD25ULL, 0x103361462983381EULL, 
            0x4165287F1D19A1F5ULL, 0x05485E1797C607C4ULL, 0x99A3BEFE29A42E66ULL, 0xF521E884A391A099ULL, 
            0xC81CD1C35E38B72EULL, 0xC82EA4C3EF14DF6BULL, 0x5EA7B0C4EC746599ULL, 0xA2C2CCB6EBAFA162ULL, 
            0xDBDB23C1EA0E6E10ULL, 0x843F66E30B74884EULL, 0xE47B393B65D2CA92ULL, 0xC452D6B31FAF7767ULL, 
            0x654FB27F58D5006FULL, 0xF892F8DF9F10493AULL, 0x4A4F29F7227F40EEULL, 0x0249125FCA549CB4ULL, 
            0x79A4870ACB3CCE36ULL, 0x002BF1DE7179ABFDULL, 0x2EAF2C0844DC3C11ULL, 0x5D0F3F9C8FD74DC9ULL
        },
        {
            0x393B870C3DBFAB73ULL, 0x5F067AA346DB8BCDULL, 0xA23ED060CE9EB072ULL, 0xFD36E21DAE1E1A26ULL, 
            0x1E1137C42193616AULL, 0xF5EDDE04D000E020ULL, 0xF9A3CAE2F64AB7D4ULL, 0xC754F67CEF4E00BDULL, 
            0x12D97D5CCC70C586ULL, 0xA35A4CFD230E24D8ULL, 0xA62B9F1E883A6F2AULL, 0x81BEBFE4EE8FC3C1ULL, 
            0xB72560E256882C6DULL, 0xA9179FF964B063B8ULL, 0xF534F40E2D101CEEULL, 0xECF3443597BA2DA0ULL, 
            0x2606EFBEFCFB18CEULL, 0xA1D49A2A14A2F30BULL, 0x96A22CDEE69A2D7CULL, 0xBAAD3664BDFB3A31ULL, 
            0xC971C37DD43FD1A1ULL, 0xA99AD5E1B2E5B903ULL, 0xAEA083144D5CA9CBULL, 0xD7FAA84FB4D73B56ULL, 
            0x0D1582BA6EB11F1AULL, 0x21F6C9111B633FA7ULL, 0x47FD8F2E5703F9E4ULL, 0x4EEC82B1B3E77C48ULL, 
            0x1C12C3A07CBE2B3FULL, 0xC9FD8F007776E6B3ULL, 0x768EF93C2CBB4082ULL, 0x8BB992F177153388ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseGConstants = {
    0x4332A41B334F4DFBULL,
    0xCBB6C1E09BA53030ULL,
    0x5EBFD205BE66D904ULL,
    0x4332A41B334F4DFBULL,
    0xCBB6C1E09BA53030ULL,
    0x5EBFD205BE66D904ULL,
    0x1AAEF188DF97F53DULL,
    0x266F2316E032218EULL,
    0x0B,
    0x67,
    0xD3,
    0x29,
    0xD1,
    0x68,
    0x67,
    0xB9
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseHSalts = {
    {
        {
            0x7272932379DCF229ULL, 0x8E41E3916F331179ULL, 0x90DDC8B2BE6472DFULL, 0x20FDABCD1D2D3334ULL, 
            0xF39131E599B070BFULL, 0xD3BFA54D6C6D554FULL, 0xC7278698C5ACDF2FULL, 0x96690403DBAB9B84ULL, 
            0x4CCD6C91BE7A2B78ULL, 0xAD6A6A897AD14A27ULL, 0x56B958D0A4B008EDULL, 0xB96AB18E14306345ULL, 
            0x47E789C878C286A5ULL, 0x1F811BF00CEF5624ULL, 0xCAB5DF67ADCEB542ULL, 0x8733E4633058908EULL, 
            0x1D6E852EF1DB86CCULL, 0x0E37552E2E996FCFULL, 0x0ABB549994985936ULL, 0x4879050B9CDFF24AULL, 
            0x299B47F0BAD01EA1ULL, 0x1F652FFD0E45FE86ULL, 0xF7DCF742160A7CBAULL, 0x44F4593159785AEFULL, 
            0x3F3A515486D80847ULL, 0x6B8DCD96FCB8C0F5ULL, 0xA983CAF75B438A01ULL, 0x5353620455B1C20BULL, 
            0x6CD9FF12B26F8124ULL, 0xB346D9F9310A3B81ULL, 0x4CF162FE58520045ULL, 0x47F283BE77F32E93ULL
        },
        {
            0x5ADE95C16B8A5F4FULL, 0xCE60E90B5A2E911DULL, 0x41B3723D1B3A58CCULL, 0x7B8257A88271345AULL, 
            0xB9A9E66F4A31B3E6ULL, 0x21F8776B2C38537FULL, 0xFCFF52DB6CDA63FBULL, 0x24D597D35F70F90CULL, 
            0x37DA322B4A68751AULL, 0x5C05064AB1E74130ULL, 0xBD9D91B837FFB0ADULL, 0x9CFE17F5D4607CF4ULL, 
            0x12AC42BE7C91A203ULL, 0x67C8273371C72950ULL, 0xD9CF3AEFE7B6B7C6ULL, 0xFACC776290D5FC45ULL, 
            0xFE3C9E0719A5AEB1ULL, 0x546B23C9A4598BA2ULL, 0x9ABD10D0B5C4209EULL, 0x67B04DB48F6FE055ULL, 
            0xAAC8DE65AF0E5AF2ULL, 0x08AB9861AF5796C5ULL, 0x245C525D21431583ULL, 0x2C133DE859E8F6AEULL, 
            0xE674EBAFC0BC0E4EULL, 0xE86E5F783DA75F22ULL, 0x3148926D2EF1FAA5ULL, 0x5609A03E2F86D662ULL, 
            0x9B70D6285A8B7622ULL, 0x1AA742F698A6959EULL, 0xEE05A2AEA5124F85ULL, 0x3B1C263E1A51DD7EULL
        },
        {
            0x4A776510E8FA2CFCULL, 0x5F721D46078F6902ULL, 0x4109E3CB600D7F21ULL, 0xBCCE01F80A98951DULL, 
            0xB0C6559E651DF88DULL, 0x96996E4D9812DE2FULL, 0x1FC97C5515E8A3B0ULL, 0x5AB9F4C8DBED9F64ULL, 
            0x4428745C182442FFULL, 0x2166886A4CBEEDE7ULL, 0x90A2B9699D83B8EBULL, 0xE884C72AF40CBAD1ULL, 
            0xB8623E67E6F55E1FULL, 0xDAC2D2017D9D4D05ULL, 0x7CE2163F32B3A810ULL, 0x83227275100EF1B0ULL, 
            0xA6DA64CB3B420C36ULL, 0x983A3ABA9619DC07ULL, 0x723391EAD6DE6C3DULL, 0x1972EBDBCCA21C36ULL, 
            0xB6245A5BA9DF03DEULL, 0x665EDD6B2F941BC8ULL, 0xCF209A792D36D248ULL, 0xC19CE884BBD4CB79ULL, 
            0x419E98C433082182ULL, 0xB605ADDDACD30A9DULL, 0x52656B2B4965CA88ULL, 0xFDDF62440B18B92AULL, 
            0x3ABA787AB095E28FULL, 0x7A50D8C13219EB77ULL, 0xBDA7E42C6FD33DFEULL, 0x82DE1418DFB6BD33ULL
        },
        {
            0x0FE363E25FBC879BULL, 0x3E603236ECFD1E3AULL, 0x30D117817C941805ULL, 0xAF6F74196946A0A6ULL, 
            0x2329F3EB8D4A8B27ULL, 0x6ADB489DE4DEAA93ULL, 0x77D20BF01C10B376ULL, 0x8B3D57841FE93086ULL, 
            0x5323327859FD8715ULL, 0x72648FE89621D7B7ULL, 0xD34A8A42F8ABA755ULL, 0x31F93565BE861BB6ULL, 
            0x06B301F73FB2A165ULL, 0x5979521065A24888ULL, 0x2D6765FF3B7359E2ULL, 0xD7A92787A25AFA64ULL, 
            0xE98BAE3AA7B3B729ULL, 0x470BD33E902D6319ULL, 0x3509F84516BC31DBULL, 0xB2E04E090ED1B4B1ULL, 
            0x752D127BCD996725ULL, 0xB20AEAB6FBD28E1CULL, 0xC1111E8ED1818833ULL, 0x9D1309B3C104C44BULL, 
            0x56BFE3108C1F9E53ULL, 0xC172F047B67FCE69ULL, 0x048E5E3CCB13CB33ULL, 0x1A41E4550F2B62BEULL, 
            0x5CD2A26DCB25672AULL, 0x99D132F9AD49DA19ULL, 0xC0220571EDB962FBULL, 0xEAFFF17A2B6D76DBULL
        },
        {
            0xD344052EC1D18D3DULL, 0x07F2D11283075245ULL, 0x90A4BB261F984B16ULL, 0xE952704A4B596B21ULL, 
            0x19981B2059ADF5D5ULL, 0xEF4E772942EE2116ULL, 0xF62E4A003106499DULL, 0x4606C21FD3D2DBDDULL, 
            0x3EE73EF26ED81357ULL, 0x220017C8D33AB1B9ULL, 0x07032834481A846DULL, 0x6CE3D9A85DEB6B68ULL, 
            0x465966665A2548C6ULL, 0xDCDE68D9C7D2CE60ULL, 0xBE6B77E7B1F607F5ULL, 0xB7E4659AD6B8B7DBULL, 
            0xA8FF4C2417187EA0ULL, 0x5D561DBAC53DAD00ULL, 0x8DD352B56605BCB1ULL, 0xD09B9A42BB37D35FULL, 
            0xBE90113CFC312934ULL, 0x4A00CA3D9DBA5128ULL, 0x32B2AC3C3BA4454AULL, 0x9A63F16234EF3625ULL, 
            0x0DEBE541D7499892ULL, 0x9897E853EBAFD1BBULL, 0x62002BBCC9B2C01BULL, 0x29898AB8036507D5ULL, 
            0x655929A9D686F6E9ULL, 0x46AA4B951C7EBA26ULL, 0x7A188603D63C2DFBULL, 0xCFF8839642057D96ULL
        },
        {
            0x82126D859C35A6EEULL, 0x3399359D58FF6B72ULL, 0x2F719FB9D5BC8EFEULL, 0x9413D0BD2E2691D3ULL, 
            0x4320003F85487E76ULL, 0xA2A2827CE582CFC8ULL, 0x96DE005ED30543B2ULL, 0xB94C726F1244D559ULL, 
            0xE12C92C82458D7FAULL, 0x31AA68A04BF3A478ULL, 0x96E454F4AE819B10ULL, 0x05275653C86F2DB8ULL, 
            0xD5D9EECD5A8E64E1ULL, 0x508C5583086DF0BAULL, 0x08486A426C096A46ULL, 0xBCAD5E6C88BF7427ULL, 
            0x06696C69B6FF60F6ULL, 0xA2B80AB056DACB6DULL, 0xB3E923987488777CULL, 0xAD5967093820AB2BULL, 
            0xB62448ECB84D9A73ULL, 0xE9DC48BB506A1A0EULL, 0xD6B59B9E15C10CDBULL, 0x5E31D3A8BD8AD9E7ULL, 
            0x8CADA1F3BEC28D38ULL, 0x9E44E63734DA950EULL, 0x9C05EA4C77715152ULL, 0x3F7D34B66FC1E4ADULL, 
            0x053BC033D9A9B337ULL, 0x08C146881E2DD440ULL, 0xDEBC0CD63352DD53ULL, 0x285F263ED96C76D9ULL
        }
    },
    {
        {
            0x4B11DBF24153C95AULL, 0x956A21B1F497837BULL, 0x5F58A114F183FEEEULL, 0x92330247E7E06F0FULL, 
            0xEB848A1AA6D16C7CULL, 0xAD6E08800FDABEAFULL, 0x760A7CA4E7CA06ADULL, 0x9805F6802A26EDDDULL, 
            0x543A732EC8305209ULL, 0xA46B829E5D1B4D5CULL, 0x6CEC3AF2C6267C7CULL, 0x8EE9CCC984AA25DAULL, 
            0xBA5AFDDCA896E29AULL, 0x30163C73AABB9C10ULL, 0x101D0CFEB26CCE0CULL, 0x38C3C1F21E403ACFULL, 
            0x8677E36BD6981C98ULL, 0x7DD6369D03602D6AULL, 0x7E00C707ABB48707ULL, 0x56FBC14BD4E2537BULL, 
            0xDBACA1A9FDBBF9B7ULL, 0xD07735ED78A8CDFAULL, 0x5EC16A6E20D2417EULL, 0x977726628F1E0614ULL, 
            0x1573E579A8AC4AC9ULL, 0x40D12F6F30157B92ULL, 0xDF555D8E6CED0394ULL, 0x3242CD4963C3992DULL, 
            0x02DCA7E43E957A47ULL, 0xDF8C0C9F6146B108ULL, 0x158C5A962F92DE4BULL, 0x8730AEE5A712AA4EULL
        },
        {
            0x951B6725180E1B7FULL, 0xB5862CBA2516F8E5ULL, 0x3756F4C9346D4DF8ULL, 0xDCF2F5CA5F538784ULL, 
            0xF5C09EC933B27E83ULL, 0x30C6293F8F160A4DULL, 0xF9BA5534D166A79AULL, 0xC24131F983136287ULL, 
            0xCA1AB1AAC1DA8ACEULL, 0x8CC2D7C7E28915BBULL, 0x91EDE81D2BFFE8BCULL, 0x28FFF97751242DA4ULL, 
            0x2D6942FC9EA0EF49ULL, 0xA814B5A48E83D6F6ULL, 0xC4C5DA92FFFF1BE3ULL, 0xD93C012BC8AB19CBULL, 
            0x82E61AE27400DABFULL, 0x2A147C9FBF52C4DAULL, 0xA2BB312974C41E01ULL, 0x2D93766C26DFE62DULL, 
            0x7D45744C09A3FD4CULL, 0xBCD2E1A50AEC570DULL, 0x2ADC1FAAB1D8F449ULL, 0x714A3545AB02370AULL, 
            0x2B6923FCD1BD39D5ULL, 0xB36AFC43D6B9C859ULL, 0x1B03196548010ED6ULL, 0x74F5BC1F3EE3801DULL, 
            0x5544C53496369310ULL, 0x43F7FA665BFEE844ULL, 0x3D71289E74143C97ULL, 0xBF31E602C38C34CDULL
        },
        {
            0x52437C0C0052CF1CULL, 0xE49BD88E446AD55AULL, 0x9CF8D8C4EB05DFE8ULL, 0x3A41F1ACDEA932ACULL, 
            0xC24CDC1FE5E17FA5ULL, 0x5D00BDA75A0716F8ULL, 0x0BEBA4B6E5431966ULL, 0xEF3F4F09454E2119ULL, 
            0x8D985571705C2B6FULL, 0x9537D37CFE2AC9C1ULL, 0xA57A7AF787EEFE15ULL, 0x4415D352B40FB02FULL, 
            0xC3C759B21C809B47ULL, 0xBFC9175C31769DF7ULL, 0xE127BB55093DC861ULL, 0x66981B5751017DF6ULL, 
            0x5C2506AD4901FBD9ULL, 0x9424497680875BCBULL, 0x533EEBB06F309E08ULL, 0x46CDB10115987731ULL, 
            0x654F23BE01B4672EULL, 0x802D6AAF372941F7ULL, 0xE3F8549F3803A67FULL, 0x7F103AA52B47B773ULL, 
            0x4E405CBF65DA41C1ULL, 0xD8B2358442450C00ULL, 0x9B3E335EFA6EF067ULL, 0x824D771A473763B6ULL, 
            0xBDBF1F3E0EF96735ULL, 0x9DE0D25B8FC6E2C8ULL, 0x0864CFFCCFE5DBFAULL, 0x6B3C5D0F74311761ULL
        },
        {
            0x851D8BC20FBECF1CULL, 0xAE06CBEA9B9B82C8ULL, 0x580FB60B7EC470CFULL, 0x40B6639892D31464ULL, 
            0xAB0EB459443C8FE1ULL, 0x67ABC8A625E30AB5ULL, 0x9CA19F91C654F597ULL, 0xC67174368098B092ULL, 
            0x85E9292BADD77427ULL, 0xB36085C15860EC91ULL, 0x58F0BD6C129B1B12ULL, 0x148D96E048419389ULL, 
            0xFFFCA0AFFAB838C1ULL, 0x8F0A18924FDB62BAULL, 0x32FE09BCEFE3500FULL, 0x3733C808EA06C173ULL, 
            0x1B8E15B0DDC9501BULL, 0xE3DE680E22533211ULL, 0xC5B336F70831948AULL, 0xFDE9C3DA2E88CCF6ULL, 
            0x57E946FCE666CC6BULL, 0x7288AF3AE3BC0375ULL, 0x24020C41ECC74A77ULL, 0x39B7B02031F959B8ULL, 
            0x69FA242F1AB9B058ULL, 0x5D966D5A58FB2E7BULL, 0xD2FCAE7E361CC8A2ULL, 0xC1290DDAF8F83DACULL, 
            0xF98CD2A0CADBDE4AULL, 0x07CB460BFEAEC97BULL, 0x771E36AAE634B9E3ULL, 0x67749A12D00C6D1BULL
        },
        {
            0x62A9475A1846C8FBULL, 0x95A3E76E3314E8F4ULL, 0x1497A1971A74F9DEULL, 0x4B81BE5B1EECBE8DULL, 
            0xAF0998F3EF4E6DD3ULL, 0x84E4E8D9E8E4B2C3ULL, 0x960AA7ED3B84E52BULL, 0xF21DFD47A6C4EA8EULL, 
            0x2FD0669E9CC828C3ULL, 0x4D39B15D8899881AULL, 0x4062F6FBBE036346ULL, 0x8F1A30FF50D9917DULL, 
            0xFA932323F3E6639BULL, 0x6B8CCFE71184B5A9ULL, 0x912073904D05B93BULL, 0xC0530EB307C75F28ULL, 
            0x85327F0A6ED315E2ULL, 0x9097AB4B05A9F8B1ULL, 0x26249EB2AAFEB242ULL, 0x4425C405D551D3F9ULL, 
            0x33B9A556CC79913DULL, 0x09495B7C75293662ULL, 0x6A6F57EAD9F4E4FBULL, 0x3D41016174577F7DULL, 
            0x7048A1ECE8B93406ULL, 0xC67210001DC8D75CULL, 0x10B7F0A742238F9EULL, 0x0FD176345B8A5EBAULL, 
            0x5A634DFE3CB5AD8CULL, 0x8C7A21DD19BFF1C6ULL, 0x0AACD5121DC8E6C2ULL, 0x943350E6D3C8E0B8ULL
        },
        {
            0x1FD0FBF2BCF6B062ULL, 0xF5B7375DBFACCEA9ULL, 0x9796B9D316009E44ULL, 0x0EBB8CE72D83CE5EULL, 
            0xAC81888591B0BC20ULL, 0x659C2BE43D8EACD7ULL, 0x413D262BF7F5E0AEULL, 0xC5F01D3DCFC5BF43ULL, 
            0xBCE0A21A329D7C2EULL, 0xAA9E052EB8AB16A0ULL, 0x09B3B964BC1C131AULL, 0x71ECA5BFCF670721ULL, 
            0xAB01957EA63F5689ULL, 0x42C3F157E535EFD1ULL, 0x4E06C9209FF1AEFAULL, 0x201C98F684333DA6ULL, 
            0xF9F080AA0D2C1EB8ULL, 0xF31DE96DFD0F72AFULL, 0x48D4BBBDF0D9DD59ULL, 0xD79E9D392536CC68ULL, 
            0xE84EAAF00E5E2ED6ULL, 0x75BCBF3D4A8A37CDULL, 0x45481E40CC911C7BULL, 0x63069807319A53A9ULL, 
            0xC19EA7C1FADFA4D4ULL, 0x566169A1311288C7ULL, 0xBDA9E76CCEABE62FULL, 0x81D89B40FC675258ULL, 
            0x52CF59EACF81B26FULL, 0x4D029A6EC96B8E2AULL, 0xD8C7286C4E6FA86BULL, 0xDE495F65EDF3C966ULL
        }
    },
    {
        {
            0x0FB952E3F811EBD7ULL, 0xA48417C3D9EA442DULL, 0xF62E279DDE049B17ULL, 0x8F19710DF1F9FC71ULL, 
            0x32BB024E294B9954ULL, 0x762530D5AC444B7AULL, 0x1EF4B053FBA99C4BULL, 0xA0DF9CFE97F3426EULL, 
            0x31D7BC1F71BEC2B9ULL, 0xC1C7DF593E6209CDULL, 0xFB03F31437DBD119ULL, 0xE0078285F2656C3AULL, 
            0x43D2EA1626E21556ULL, 0x7E1F33CD772FF7E5ULL, 0x3CD5E4117C103233ULL, 0x7CDFCABF54C494BEULL, 
            0x18B1801658324AB7ULL, 0x0EA049F1855B6808ULL, 0xB1E5DEAA76A9C7DDULL, 0x669E562207A2392EULL, 
            0xE46F276A6FAAC6A6ULL, 0xD340E5CC397341EBULL, 0x8972847F574E4B82ULL, 0xA15ECC9EB2C237B5ULL, 
            0xCCDB8D3A1176F29FULL, 0x43085693F882CCBFULL, 0xF139CA8BE26F31DCULL, 0x55E8F6DBDAEEA5F6ULL, 
            0x2F6A70348898AFA5ULL, 0x278366CF20D13C81ULL, 0x139F54E09BA2B7C7ULL, 0xC4F2F6CF12A9855FULL
        },
        {
            0xB38C98504D805635ULL, 0x46B56E839434FCF6ULL, 0x835C4071A3363FABULL, 0x82CAF6CC17C360FDULL, 
            0xF8A6982574D95760ULL, 0x24979947E8B632C2ULL, 0x9C0E98BC1E67377EULL, 0xC3E6D457BE625F93ULL, 
            0xB9C4B893CDA2A8E2ULL, 0x5E3775E338C85C42ULL, 0x8E18809941082B54ULL, 0x65A48437F68A9865ULL, 
            0x216CE6EB500ADF38ULL, 0xAD6C6E2082EE3785ULL, 0xC5E885A735F5AAFCULL, 0xACAD89B16971F0D5ULL, 
            0xA72234263BCE78DAULL, 0xF378E7B6186C230DULL, 0x1429FE119E2E1606ULL, 0xFABDE4FD9EFB17DEULL, 
            0xBD3DAFAE8C34A63BULL, 0x17A060302EC9E200ULL, 0x6AC61B124CABF649ULL, 0x4CFC59EAB28B531EULL, 
            0xD291DFC749BB6B64ULL, 0x3F0AF5C7D75DE51EULL, 0x54FCBB627FDDC196ULL, 0x7BA7482A4D062708ULL, 
            0x5004434D8F07CFEAULL, 0x03461D1F047BC726ULL, 0xD0CBC80EE81FA733ULL, 0x71A1E8E24D7FF8BFULL
        },
        {
            0xFFCD6D1CCD0CBDA2ULL, 0x5886CD1C172E9BA8ULL, 0x678C0C0197ABF44AULL, 0xA95113E02CBC1403ULL, 
            0xA9613E8DBC4E47FDULL, 0x520D71488037F822ULL, 0x32BF83DF244FCC4FULL, 0x9665072C4BDE2E20ULL, 
            0x3C382DC4CCE5235BULL, 0x99952C5F57ACD199ULL, 0xC77C729A66C73098ULL, 0x0C1D010884900980ULL, 
            0xCD0DB444B6EEFC62ULL, 0x7983FEAE7165FB7FULL, 0x998B9004A7C6026CULL, 0x0776F37AC34183F9ULL, 
            0xB856386CD0BF3B96ULL, 0xDBFD214E93C8F507ULL, 0x3E474B80C6B96118ULL, 0xA293F018A7149613ULL, 
            0x14FC9A81A67576BEULL, 0x42C9D436790F8D05ULL, 0x8BAF2E2AD359BF72ULL, 0x2D7A0351DF4B7BF6ULL, 
            0xC55AF73F9BBDFED2ULL, 0xBCACB27E1EE01287ULL, 0x5BF29C189D187201ULL, 0x4CD41815FEC87C61ULL, 
            0xDEAC46EB6A3686D4ULL, 0xA78C34FC13B6E9AFULL, 0x3279140D2702DBB7ULL, 0xF07E84AA82E26825ULL
        },
        {
            0x3021D2439A373DE2ULL, 0x26C69F1D3A1F9690ULL, 0xDC2410FC893D9870ULL, 0x59B7A0E17B1F7B61ULL, 
            0x4067B6F31904ABC8ULL, 0x145066005AB78FA1ULL, 0x2D8D293EE5D75C3FULL, 0x4C7F1045A71C2A99ULL, 
            0xE7B10185E47210CCULL, 0xF96F8034588F0357ULL, 0x36E348CD6995A908ULL, 0x537547601FE28E90ULL, 
            0xD00C00C9D2E6FA18ULL, 0xF06E2DA203645FE0ULL, 0xF1E8DA90B814D00DULL, 0x788B624D99FB80F2ULL, 
            0x4854F19AF977D116ULL, 0x99B7BEE106E47B23ULL, 0xD83BE14BE84635C5ULL, 0x11779CE6FC791374ULL, 
            0x7777112D489ED19BULL, 0x1DBDCDE5FD4C36ADULL, 0xE5152AB70A716815ULL, 0xD221F569D6B81695ULL, 
            0xA2801A60B685C7E2ULL, 0x9E610720C269CE3EULL, 0xAE4F488B4B6BCEC0ULL, 0x7C929D6861D04B7DULL, 
            0x1C17555B82B98A92ULL, 0xFA88F44D904DD491ULL, 0x347F1EBFFECA2E44ULL, 0x40DC6CACAA6E6681ULL
        },
        {
            0x4C2E255B3ECA1D9AULL, 0x69582CACB8E615D0ULL, 0x835EA47E3D940FD5ULL, 0xA047BE1A91F1AC5FULL, 
            0xB4F83AE88EF2432FULL, 0x3D3ABD2F8A278FC3ULL, 0x104A1CC8071C4A24ULL, 0xAD69F2AA7D12730EULL, 
            0x465378C825CD1B4AULL, 0x1B8ABF0ACA061F47ULL, 0xD1B7C0DDBDBE908CULL, 0x8030477D4E1C6903ULL, 
            0x81E0C42365C0110EULL, 0x028F742F5C3CA53BULL, 0xB509067C356901FBULL, 0x120AEFB22A26C97CULL, 
            0x5450228C83117976ULL, 0x49E59DF964DFF9A6ULL, 0x1C90FCD1822F03CDULL, 0x3EE000305C9BC570ULL, 
            0x5192458B42E1C54EULL, 0x22596511723CCFABULL, 0x23A4E05E8799156CULL, 0x73687B70E9835CB8ULL, 
            0x2DB086E05BADADA0ULL, 0x2022071DB26B780FULL, 0x954708C20CA66597ULL, 0xCB392654C2321F0DULL, 
            0x2E8757CA94F2E955ULL, 0xDE033786C274B7A6ULL, 0x992C66B6ABC412AEULL, 0x98B0FD0D5E30E7E9ULL
        },
        {
            0x7E97779BA2F2DB03ULL, 0xAF4B705F4F270B93ULL, 0x1A042EDD6A885D1CULL, 0xD4ABDD4311B5EB77ULL, 
            0x7C3F5535CF1A8614ULL, 0xEF2800F90757F629ULL, 0x6B1987372AA1ECB4ULL, 0x86F70EF5D81BAFE8ULL, 
            0x84868017687E1415ULL, 0xBA13F125C5BADC8AULL, 0x677B42DAB1C494E2ULL, 0x96F4AEA08277333CULL, 
            0x01DD286CC6DC418EULL, 0x5CEABB3BDCE2A7D9ULL, 0x057ED3EEDEC71B40ULL, 0xE4FA6BE218FD3C61ULL, 
            0x0AD983C90927F5B3ULL, 0x27C353E9E3F14707ULL, 0xDDE2CE83FB045743ULL, 0x826546F6DFFD4234ULL, 
            0xEC358D5A29118D48ULL, 0xD0111752C909E023ULL, 0xDB6CBAB453B9AF33ULL, 0x64515DCFAA528789ULL, 
            0xE8D84F11AEFA0814ULL, 0x50475153A8A88394ULL, 0xCC0B47502BC9DE98ULL, 0x432A71C239016803ULL, 
            0xA9571DD7D56D8844ULL, 0x3D2E1DB6F342C05CULL, 0xF442DF18CB7CF2D8ULL, 0xA48A2BF2E0E1E0F4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseHConstants = {
    0x04111A83E03ECBE6ULL,
    0xE990192A8F11EE9CULL,
    0x54DACF9216BABB1CULL,
    0x04111A83E03ECBE6ULL,
    0xE990192A8F11EE9CULL,
    0x54DACF9216BABB1CULL,
    0x1B2AE26281B2999AULL,
    0xFB2F1A112A2BF740ULL,
    0x3A,
    0x7F,
    0xD7,
    0x71,
    0x65,
    0xDA,
    0xF4,
    0x0E
};

