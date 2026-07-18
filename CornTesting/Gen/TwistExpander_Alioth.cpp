#include "TwistExpander_Alioth.hpp"
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

TwistExpander_Alioth::TwistExpander_Alioth()
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

void TwistExpander_Alioth::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD4AE3DEC6D5F944CULL; std::uint64_t aIngress = 0xD8246B941D4FA2B6ULL; std::uint64_t aCarry = 0xA6ED26990AB86D69ULL;

    std::uint64_t aWandererA = 0xEBD359AD1DC39C06ULL; std::uint64_t aWandererB = 0x9A4BFA7ADB3E2A2AULL; std::uint64_t aWandererC = 0xA0CAFDF14F7A6582ULL; std::uint64_t aWandererD = 0xE943FFA53ADEEBACULL;
    std::uint64_t aWandererE = 0x9807E96282BD9E2AULL; std::uint64_t aWandererF = 0xF682DE2DB19BA3BDULL; std::uint64_t aWandererG = 0xDBE95825B1AC62F1ULL; std::uint64_t aWandererH = 0xCBF5FD01F50703F2ULL;
    std::uint64_t aWandererI = 0xA1AE82357424D297ULL; std::uint64_t aWandererJ = 0x9A33EAD3875C6793ULL; std::uint64_t aWandererK = 0xD089FB1FC8D9A40CULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18336852622648061582U;
        aCarry = 14811621705555346689U;
        aWandererA = 16101144066889852671U;
        aWandererB = 9979297460323027984U;
        aWandererC = 10274732281740568627U;
        aWandererD = 12809847558674762563U;
        aWandererE = 14945822271661171937U;
        aWandererF = 16254066134242086383U;
        aWandererG = 16978453404173880593U;
        aWandererH = 14031065677124562817U;
        aWandererI = 12475099514059225887U;
        aWandererJ = 15639729937387301187U;
        aWandererK = 14038763068441929500U;
    TwistExpander_Alioth_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alioth::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE55EA3F57980D974ULL; std::uint64_t aIngress = 0xB17E3BFAA020387DULL; std::uint64_t aCarry = 0xDDAD17E3219201A3ULL;

    std::uint64_t aWandererA = 0xCAB1CF8E4C27ED2DULL; std::uint64_t aWandererB = 0xB9BADF02CA9766A2ULL; std::uint64_t aWandererC = 0x8226D58DCC4116C0ULL; std::uint64_t aWandererD = 0xF878D524851CF233ULL;
    std::uint64_t aWandererE = 0xB963605D445D68E1ULL; std::uint64_t aWandererF = 0xAFCAC6EA373F721CULL; std::uint64_t aWandererG = 0xE1DB91E486C37A2AULL; std::uint64_t aWandererH = 0xAA1B8DE4CD76B128ULL;
    std::uint64_t aWandererI = 0x861971E8E6C5FC3BULL; std::uint64_t aWandererJ = 0x9D7FE7D68E506D31ULL; std::uint64_t aWandererK = 0xDBD10538953B31F1ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13217496404631743273U;
        aCarry = 15117308884834021122U;
        aWandererA = 13329391662616994510U;
        aWandererB = 12893027728068356923U;
        aWandererC = 16904919470185160017U;
        aWandererD = 18067595196506838527U;
        aWandererE = 10460795108961529057U;
        aWandererF = 14917160023252007513U;
        aWandererG = 17887277950216527509U;
        aWandererH = 9799452146283216195U;
        aWandererI = 12681106872626052435U;
        aWandererJ = 10335185555247751815U;
        aWandererK = 12676030661181513160U;
    TwistExpander_Alioth_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alioth::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8C4BF6CA27650C9CULL;
    std::uint64_t aIngress = 0x9A685926572214C9ULL;
    std::uint64_t aCarry = 0xFEF481A8D069F97AULL;

    std::uint64_t aWandererA = 0xB7581D8A016824C0ULL;
    std::uint64_t aWandererB = 0xEA605F9898459AB5ULL;
    std::uint64_t aWandererC = 0xF546C91EBB7344ADULL;
    std::uint64_t aWandererD = 0xFC0D383D01F88700ULL;
    std::uint64_t aWandererE = 0x8B14A781AB425561ULL;
    std::uint64_t aWandererF = 0xF068B7FFF2101787ULL;
    std::uint64_t aWandererG = 0x9AB0594B70BDE5A4ULL;
    std::uint64_t aWandererH = 0x971FE2BFAA5DE23BULL;
    std::uint64_t aWandererI = 0xEB37EB749E3AB8EAULL;
    std::uint64_t aWandererJ = 0xB64D815CCB6470BFULL;
    std::uint64_t aWandererK = 0xFC86424738006A9FULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    TwistExpander_Alioth_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alioth_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Alioth_Arx::GROW_B(pWorkSpace,
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

// SmartSquash candidate 4 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 5784
void TwistExpander_Alioth::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1269U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1632U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1260U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1257U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1986U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1076U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1163U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 103U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 481U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1678U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1889U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1178U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 968U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1290U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 294U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 547U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1997U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 604U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1442U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1202U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 819U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 426U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1161U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1846U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 847U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 95U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1463U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 284U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 272U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 745U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1321U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 93U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 119U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 166U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2043U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 938U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1443U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 177U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1961U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1843U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 35U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1930U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1944U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1804U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 724U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 439U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1069U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 496U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 195U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 171U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 676U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1588U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 299U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 348U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1228U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1374U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1049U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1263U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1019U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 837U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 89U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1308U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1686U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1708U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 234U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1423U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 24U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1625U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1281U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 421U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1165U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1475U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1794U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2008U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1343U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 514U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1735U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1419U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1008U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1646U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1104U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1552U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 495U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1424U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1648U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 902U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2035U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1820U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1914U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 388U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 255U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1013U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 962U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1129U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1368U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 443U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1855U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 323U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1573U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 785U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 727U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 15U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1491U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2024U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 530U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 58U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1471U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 424U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 864U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 553U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 373U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1866U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1001U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1919U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 159U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 524U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1342U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1810U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 537U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1516U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 633U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 970U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 681U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1941U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Alioth::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9A23212A23E095FEULL; std::uint64_t aIngress = 0xA04C3C3E1B40157EULL; std::uint64_t aCarry = 0xA4653DB7C079CA95ULL;

    std::uint64_t aWandererA = 0xA852B6090D9691A5ULL; std::uint64_t aWandererB = 0xF64DFC32E29CF810ULL; std::uint64_t aWandererC = 0x9EF7744025962A1BULL; std::uint64_t aWandererD = 0xA860FBB75F1A2BB8ULL;
    std::uint64_t aWandererE = 0xEFB24C824742CE31ULL; std::uint64_t aWandererF = 0xDE23B39F7E4242C1ULL; std::uint64_t aWandererG = 0xB74ACD6AC2DC336EULL; std::uint64_t aWandererH = 0xCE67F869DCBE4A57ULL;
    std::uint64_t aWandererI = 0xD367D8101759F9D5ULL; std::uint64_t aWandererJ = 0x8CFADA2CC190BF00ULL; std::uint64_t aWandererK = 0xA74FDE19DF072087ULL;

    // [seed]
        aPrevious = 12205587171865409423U;
        aCarry = 11702104261533508426U;
        aWandererA = 17605557843693840264U;
        aWandererB = 9941247953643550913U;
        aWandererC = 10253680669261046048U;
        aWandererD = 10727133184522350264U;
        aWandererE = 9893153682960243728U;
        aWandererF = 16747449239943794895U;
        aWandererG = 13214938998639698979U;
        aWandererH = 11134488598226187892U;
        aWandererI = 17245866804064231833U;
        aWandererJ = 11468639033387897145U;
        aWandererK = 14426310617704806706U;
    TwistExpander_Alioth_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Alioth_Arx::GROW_A(pWorkSpace,
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
    TwistExpander_Alioth_Arx::GROW_B(pWorkSpace,
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

// GrowA candidate 4 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1791; nearest pair: 588 / 674
void TwistExpander_Alioth::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4770U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3601U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6004U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 389U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1513U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 238U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4764U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1719U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1484U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 111U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2543U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3639U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2318U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1547U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5692U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5446U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 407U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 705U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 77U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1405U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1567U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 872U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 482U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 46U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1838U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 221U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1801U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 314U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1101U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2034U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1464U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1489U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1120U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 744U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1666U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 4 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1796; nearest pair: 590 / 674
void TwistExpander_Alioth::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6491U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5506U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4648U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7452U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3419U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5489U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7068U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4200U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3554U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2276U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6744U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3361U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6519U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4991U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1161U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1130U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 355U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1335U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1252U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 176U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1713U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1358U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1701U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 116U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1360U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1463U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 559U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1765U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1551U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1317U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 467U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 284U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1105U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 359U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 283U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseASalts = {
    {
        {
            0x828290444256D2A4ULL, 0x6874CA24B8BFF8D4ULL, 0x150B8A31C159F545ULL, 0x8393F48E8367FFF7ULL, 
            0xA9E40A9FBA15BEDDULL, 0x3A7C753DCEAD960CULL, 0x58DF5298A831E831ULL, 0x5C1F8253A2E28634ULL, 
            0x80F28C962A788EA8ULL, 0x74878C66B421429DULL, 0x0C3D6EBC86E6C8E9ULL, 0xC6D1A99CDC26445FULL, 
            0xB8532D2B420EA9A6ULL, 0x0AB7470B2FBB7BDDULL, 0x8FC0C9C22649B421ULL, 0x591FBCFCA46A77DEULL, 
            0x0E7C18F481647A0DULL, 0x297B1EFBE8292405ULL, 0x4DF20BA3A18F9ADDULL, 0x97E82C27A3394257ULL, 
            0x5B0DA51280A348BEULL, 0xBBB0783B643C3DD3ULL, 0x9230AC976236E89EULL, 0xCE870132CD26C229ULL, 
            0x23B407EB1849DAA8ULL, 0x01C25E22C16DD76AULL, 0xC57FC24173FDA378ULL, 0xD9D976C57AEF45E1ULL, 
            0xFC02A0DD5D763C45ULL, 0xDBC8733A03D655B7ULL, 0xB4186ADD5CDAF4DCULL, 0x8161585422EF8EE6ULL
        },
        {
            0x49B94E854DCE055AULL, 0x76EB93292A6B99DFULL, 0x10E06F1240FAAFAEULL, 0x373B3D194E938656ULL, 
            0x2C110AD4D23FB36CULL, 0x89FFFA5A239C41C4ULL, 0x9D413EE9FC56722CULL, 0x069BEEBDD39F5351ULL, 
            0xEEA9D6E41BF7DE18ULL, 0x1E896DBC4D1E38ABULL, 0x464336DE19C1C828ULL, 0x38508A427AA8845DULL, 
            0x7B5158D3D93CE6E7ULL, 0xDF4FF342D8D7FC27ULL, 0x77E5F358FA30DCA1ULL, 0xF643EB6038700F7FULL, 
            0xDEA4252358860958ULL, 0x31F1D442D90FDD7CULL, 0xD1FF064139008289ULL, 0x873979D691728B30ULL, 
            0x84257A58FF3B08E0ULL, 0xB0FFA143001A82ADULL, 0x46F924FC89557AB9ULL, 0x62853319A6CC7FA9ULL, 
            0x05B0FA3529E57BC3ULL, 0xD4508E59CC76F12AULL, 0xDB0BE067FBF737A8ULL, 0x27786F4EDC5EE232ULL, 
            0x81A5897F2D03899AULL, 0x691FB66CF09BC892ULL, 0xAFA2189E1D17D44CULL, 0x5854FA14A642E4CDULL
        },
        {
            0x4CFEEA2F668B4D82ULL, 0x0BCFFCC1646849FAULL, 0x1A37F441420C1217ULL, 0xB7AFCD5FDF6D6737ULL, 
            0x8E50788A20CCD41BULL, 0x2E8ACC6DC69482B2ULL, 0x0DE7D95DEE5CB30DULL, 0x9668BA2B1189D59AULL, 
            0xEBB739AAB9730A35ULL, 0x4B9C3377C8E460A1ULL, 0x3CACC328EA427F57ULL, 0xC80D578CDB6C3348ULL, 
            0xE85D8159162776ECULL, 0xC0F9A25F9B1B7A77ULL, 0x61C61BE1EACFB330ULL, 0x390C5FF3E1B10625ULL, 
            0xC63109CCC18B231FULL, 0xECA8D294F30CA63CULL, 0xB15A4C3263921A4CULL, 0x86BC7F5643EF2C70ULL, 
            0x441024B24ACF54E8ULL, 0xA1424D8696A15F26ULL, 0x3083E8E7433541D4ULL, 0x7D8F1F4B647C8159ULL, 
            0x90A6F9F7FC853CF4ULL, 0x4B5904BF12770548ULL, 0x6E424B7FA88384C7ULL, 0xE0FC0C213F213A99ULL, 
            0xC41D7AADC87FD525ULL, 0x4E6C37F2FABBD9E1ULL, 0xDB85A818D2017A5EULL, 0x71D472350A0D5EF6ULL
        },
        {
            0xAD9A769173904933ULL, 0x3F3BB8843AE97D9FULL, 0x7942283C76B8E464ULL, 0xE66A09C406AC56E8ULL, 
            0xDA50AA920066B74EULL, 0x066720A664010190ULL, 0x95F9B9B31EC0D5EAULL, 0xB60B89C74C49B953ULL, 
            0x9BC2E6DE7274B99DULL, 0x2CA638AB98BF9E72ULL, 0x63CBF9517BCE5ADCULL, 0x821F23380C2D38EEULL, 
            0xF66AE79F2734C8AAULL, 0x3B46406B75B39AFCULL, 0x43BF6E09C92879A0ULL, 0x59377F029C0F3631ULL, 
            0x83E34FC18C8254D8ULL, 0xCA771BCA5FCB103DULL, 0x95DC70245B590541ULL, 0xC06E8869FF947E24ULL, 
            0x9F8167A90AB550B2ULL, 0x6AC5A5DBF6E9B5DAULL, 0xD84309CFEF9C29ACULL, 0x45D7F1F8BD0CB467ULL, 
            0x50333EFD6F2DAA3CULL, 0xBBA668BFD66FC69FULL, 0x63453803E2B8805CULL, 0xD5AD1E27DFA7EE89ULL, 
            0xE07ACC51C5D91920ULL, 0xAA2AE37885B56ECAULL, 0x00796ACF8F3D570EULL, 0xF0C088C08687DD6EULL
        },
        {
            0xEE92DC25C5121DAEULL, 0x2CF8B3E373C37B37ULL, 0x74E0D09E1E603F63ULL, 0xC4CAEF108C7613F4ULL, 
            0x80DDB845F906C5EAULL, 0xFA56C6BDEBB26376ULL, 0x7CC56FC6122BE362ULL, 0x5FD86333AF37268FULL, 
            0x14A89B576C2C85B3ULL, 0x4E5D5B6158561F4FULL, 0xD211A5552B8CE5E2ULL, 0x53B1A5AEC47C4E37ULL, 
            0xE5D7788941ED6242ULL, 0xB7066BB55FB157E5ULL, 0xD2E70B74E5AC3DC0ULL, 0x5A37D5EEE262078BULL, 
            0x55C94F415AC9CCF1ULL, 0x58E624E69465100FULL, 0xC4909FD3F5D97769ULL, 0x762D494F6521BEC3ULL, 
            0xE242EC53DE3E75E2ULL, 0xEDD57690D29D1A43ULL, 0x9FFE2E5B74084AC9ULL, 0xFB1E9D4617C86B42ULL, 
            0x03CE7E852E2679D4ULL, 0x41267EBA176353B6ULL, 0x829C36375A108A27ULL, 0x6BFCDFEB8FB8146CULL, 
            0x36C6043FA118CCDBULL, 0x02AB55D4BE002BA7ULL, 0x9FA30D0C4ABE6652ULL, 0x0697DFF0F75F64A3ULL
        },
        {
            0xBF62AE8AC3FBF9C3ULL, 0x8E18DAC80CD413D6ULL, 0x2495D51FC97D697EULL, 0x599513CCA251CB11ULL, 
            0xC088B78A0558E239ULL, 0xF1B5C80E741F30C2ULL, 0x8DD675488DD496BCULL, 0x76B27AED663AD115ULL, 
            0x0167FDAEAFA2DE93ULL, 0x7D491D20FEC4F68BULL, 0xE614EE553B8454C9ULL, 0x8239B6B22440E56BULL, 
            0xDFD2AC00B9995E3EULL, 0x7446ECC1AD153ECFULL, 0xF3110A74301269FCULL, 0xD5DCAE87EBB6CC7FULL, 
            0xC24AFB4162963B96ULL, 0x9477801469AD2C12ULL, 0x043D59CF7E816CAEULL, 0x9B9040BA14BDFB66ULL, 
            0x5649031FF6CD53D6ULL, 0xA39D96DCA22C0D16ULL, 0xE52F9EFE2F98FE63ULL, 0xBF5FC2EAE8CA2B74ULL, 
            0xB4A4BEEEB66105EDULL, 0x1C7EC8F88EC8B94AULL, 0xC8852038677DC2DEULL, 0x6DFA28E084A2637AULL, 
            0x09DE19826E4D93BBULL, 0x81F5E11CF66C454DULL, 0xF140DB5AD0C7DB27ULL, 0x5DAA3CE54DD67FA5ULL
        }
    },
    {
        {
            0xAB2F0A97BC8E483DULL, 0xA719376E8A52163BULL, 0x9BDFC8FE91D729BBULL, 0x4E60FE1715AC2C74ULL, 
            0x1B1EDD2CED497DD8ULL, 0x7618A5D61FDA786CULL, 0x0E7F66836FAE2F81ULL, 0x5AFBE5A205FD249EULL, 
            0xE1AF3A8008F32AD3ULL, 0x7B2C892C849B0FDAULL, 0x8D53E24FBD500DACULL, 0x7A2EE15BCC6EA1C0ULL, 
            0x1EF0A0DAEBA2FE9FULL, 0x0B1EFF7232CEFC07ULL, 0x6DD3CCF1DED50552ULL, 0x588C9158CD99D99FULL, 
            0x916A18BA1A7DA52FULL, 0x6027748D60F9B918ULL, 0xAE8DAE81E214D305ULL, 0x830C65A432658C59ULL, 
            0x66F0FD83A4BD7CA6ULL, 0x603B21D20A2B452CULL, 0x1E50DD232E0769A2ULL, 0x3AE44F099FD91705ULL, 
            0xF6CAA73CFF506A7EULL, 0x400D94148D076F1FULL, 0x0364435373E37A92ULL, 0x4A8807DF712C3B57ULL, 
            0x65CB228836A0A5ABULL, 0x00746C770FBF9B69ULL, 0x4D965EEF46315B68ULL, 0xB914666F968EE7D6ULL
        },
        {
            0xE5F813D8DC49DC14ULL, 0x09743D4D6D5961EFULL, 0xCC53180F5DDB8F39ULL, 0xEB3485647046F0C9ULL, 
            0x3225A29801A5B6F7ULL, 0x7A0EB5D8FAD77C6CULL, 0xF25B831AA4CBECE3ULL, 0x28C383864FFFDC2BULL, 
            0x89981D3B60323AC4ULL, 0xA8CC6E8DA52F3C1FULL, 0x27EFC9F388BAD2A2ULL, 0x2B8EEC969C727814ULL, 
            0x609867A64E11C2D9ULL, 0xFACBABD1FA0EB365ULL, 0x1181FDF4B0186192ULL, 0x1D85C734A67F2F64ULL, 
            0x1C190AC8C0B216CCULL, 0x31D0CEF726A35CFFULL, 0x0271ECB2CDB6BCFCULL, 0x75678032983E765FULL, 
            0x3DDB2F3FB4950AA4ULL, 0x719E687308C5E88EULL, 0xCF04B33AC1B95DF2ULL, 0xD4B1B0F21DB83A81ULL, 
            0x91E41BF14A68C6FDULL, 0xE04BF6D2ECA2189FULL, 0x78EE1B0B587987C3ULL, 0x36F0816AFF53A2E6ULL, 
            0x1457DD37D9950B95ULL, 0x7CD5F8A13CC93841ULL, 0xC45F97294FAF511FULL, 0xB86B535F9EA5D9E2ULL
        },
        {
            0x68B457784483B11EULL, 0x46C56603EB05B033ULL, 0x7CA83A747B40BCB4ULL, 0x146C621F5930345BULL, 
            0x015777A48C4409B2ULL, 0x61054983547F83C0ULL, 0x39777922F4AB6EFAULL, 0x3A1BD01C01BB275CULL, 
            0xAB2E70D7614AE4ECULL, 0x3EDB4F0EA4650504ULL, 0xBBB82BACB09A9C97ULL, 0xB66825119D96E52FULL, 
            0x150B12FBC9007D85ULL, 0xBB3053701359E3ABULL, 0x4B40C9311DD0CD79ULL, 0xE46001497876CDF2ULL, 
            0x650DD44F8CF66158ULL, 0xD1A98A97C05014C4ULL, 0x78A0D12515272C9DULL, 0x774AD541E61DC78BULL, 
            0xABA3172CBDD6CE35ULL, 0xF09437E35499139CULL, 0xFF27C65CB9037BF9ULL, 0xE985C80AA10BAE96ULL, 
            0x1EC3DE06CA71040FULL, 0x95BCD956113AA8A4ULL, 0x1964B439E2BF0EBCULL, 0x50E71952833A0BF9ULL, 
            0xF2F8D1D5C62C22D0ULL, 0x059BBD135920DC36ULL, 0xD97E18A98B54F414ULL, 0x3A1B2CDC13A9463DULL
        },
        {
            0x1D60591B0995B9B1ULL, 0x1D6F1EDF4A205DF0ULL, 0x6E9118809012A9BBULL, 0x43FDF786D84091A5ULL, 
            0xB8F193A30FBC7FCAULL, 0xBE8A3106FAE99346ULL, 0xD4AAA9160199A6EDULL, 0x6929DD95A9540186ULL, 
            0xD6658EDFD1F60EA0ULL, 0x719C331D5202A8D3ULL, 0xDC1E118B4E49E0C6ULL, 0x2E45D03EC6D3C25AULL, 
            0x95ACEF75A9F6C4E2ULL, 0x2E6BDF78AFC00955ULL, 0xBFA1398306FF65C2ULL, 0xA3CD0E2645437B9AULL, 
            0x4EDB3D72A34F350BULL, 0xC6CFCDDA08DD2AD8ULL, 0x065196D75BE83F2EULL, 0xC8515167E25B45BCULL, 
            0xA2CB55FBAA681C8FULL, 0x2B9BC9C23FBEAE36ULL, 0x051F8E8CAD8C85FAULL, 0x96148DCFC57394C2ULL, 
            0xEF3F4BCD5E1C2BABULL, 0x731A5989A39BD40AULL, 0x70FB32D725C1FF24ULL, 0x142957ED910F399CULL, 
            0xA7FEA6B5BFC1E408ULL, 0x221B83AB84F70953ULL, 0xB8BC6B2D443A722EULL, 0x76DD1C19977D97F4ULL
        },
        {
            0x4D0D90A13D85A429ULL, 0x86A3D2E11A3471E1ULL, 0xAAFBB618FB27A6DCULL, 0x53AEEE5E2321175CULL, 
            0x6381FAE52A9A6057ULL, 0x33D99EF7154B7B1EULL, 0x7BE2AB16F41B6B66ULL, 0xB1D944EE46444750ULL, 
            0x324E477548EAC0E2ULL, 0x65C748F66CC047C1ULL, 0x3D2BFBDB46F59EE4ULL, 0x570F82FE2088DBC7ULL, 
            0xAAC3A59273752BA8ULL, 0x3A354FBE0F87BAAFULL, 0x745F40BB9756A6D3ULL, 0xB7A0B536C6B18E8FULL, 
            0x0EE20308C286EDB1ULL, 0xB21A8666CAA19752ULL, 0x4F2EA973F92D1CE7ULL, 0xF071243DA10812E6ULL, 
            0x243CF9E3D9775FF5ULL, 0x84DB296C26523400ULL, 0x290CC48694D45B67ULL, 0xBB6DAB2A1DC4EA27ULL, 
            0x20B30EDC62E06751ULL, 0xC2984B22DE5CD189ULL, 0x65C3A1C096E4228FULL, 0xD055E36BE4938CC0ULL, 
            0xAA3FBDA7471A1F22ULL, 0x98154AF11AEC3A87ULL, 0x9AAA3C969D30CC47ULL, 0xE4D49EEAAF9D51E5ULL
        },
        {
            0x6AFF7D68ADD9597FULL, 0x0292855D57921C9BULL, 0x45C1A93145701412ULL, 0x5CCBF8896C1A9252ULL, 
            0x7D0DBE8A32AFB6BFULL, 0xB7EE11DAFBA61A6BULL, 0xF5E183C6F4B8230FULL, 0x8742D5802BE75D21ULL, 
            0x602DA35417E6B7BDULL, 0x67BB80243D415368ULL, 0xB210774C014F5323ULL, 0xD2D70F00EEE86D4AULL, 
            0x160DB7F9CE49D11BULL, 0xE09EE2A164F29882ULL, 0x3403AF0186A809A8ULL, 0xDB7C87E549046891ULL, 
            0x82CA4491D4614240ULL, 0x640A8B5C49D109C0ULL, 0xF2538A8799913E02ULL, 0x6A169EBCFB65A189ULL, 
            0x8DCF339737EE1269ULL, 0xE41B94D3577B6D38ULL, 0x3D0D6479F7B4C2C0ULL, 0x5FA7E09A3CD42843ULL, 
            0xACD4AB1ED079841BULL, 0x327A64B5956D1765ULL, 0x3196238A8F54A7F5ULL, 0x69F1BA76E55B69A9ULL, 
            0x436991D73F8B9E2AULL, 0xD230D9CEB9E9353AULL, 0xA0EC896AFD278D77ULL, 0x6D2244F6460B0C39ULL
        }
    },
    {
        {
            0xF580C4A9B0D51809ULL, 0x0ECFC13C6DBF8234ULL, 0xD8853258D4AEA1F6ULL, 0xCE923D254CC9DC3DULL, 
            0x6B7A7CBFEAF63308ULL, 0x23D6A78BFA69C547ULL, 0x28941398CC2B5DC8ULL, 0xFC46828CA34ED6B6ULL, 
            0xE224EF1D6A76FDCAULL, 0x2682318050403557ULL, 0x5038D1773952AD2CULL, 0x88AB187782B7FF25ULL, 
            0xFF2343D1E074AE2EULL, 0x96771FB1A7741020ULL, 0xF2D950E9D34704A7ULL, 0x33D614450360CB32ULL, 
            0x789BE56E0B36DBABULL, 0x8840CD6B2878A63EULL, 0xE78C3AF3025F2FEBULL, 0x2D4DD04073622752ULL, 
            0x4E4E42C19B35C19AULL, 0x4072FD76931E3526ULL, 0x6760D75262C850A5ULL, 0x82BBBDAE86E1007DULL, 
            0x972923A6B9019400ULL, 0x43682EA46059A799ULL, 0x7927B88345D2E52CULL, 0x11F9BEE8717963F3ULL, 
            0x6B177A97BCFBA931ULL, 0x851A1E4A5C049B23ULL, 0xEEA3A415E0B9D539ULL, 0xD5C2F37657D89002ULL
        },
        {
            0xF02E26A4F9B7D748ULL, 0x248761261C69F87EULL, 0xE3EA0B3F41166F22ULL, 0x2AC630B47EE35902ULL, 
            0x2720404CA7F570A1ULL, 0xFB7FAF130D733E35ULL, 0x62C6892205D0D0C7ULL, 0x65DF628E7C92A5DFULL, 
            0x5D10D56EDB9F441BULL, 0x1719B8EDC8D15098ULL, 0x8BABD6E20AD73029ULL, 0xA5E417E177D47F65ULL, 
            0xC7D4A58395ACE48CULL, 0xDBDB16086B2CDBD0ULL, 0x3F584434171DE173ULL, 0xEE972464E008B425ULL, 
            0x4D6193B159B4D407ULL, 0x79923D83D8A89F2AULL, 0x175E3A5807DA6E1AULL, 0xCC1CDB6C7C54F692ULL, 
            0x11755167BDAE8C92ULL, 0x64A73847E153DBD7ULL, 0x0A2288405F9B1265ULL, 0x220132EA5F4D4994ULL, 
            0x0BD9B3F7BD65C659ULL, 0x4CBFD6E08A1C8CACULL, 0x9BA0D6A2FF773A9FULL, 0xE86FBBD77188A107ULL, 
            0xF1B60F10E7D810FDULL, 0xA784663C38AEDC3AULL, 0x098C4772FD0087CFULL, 0xBF197E5DAFE444A1ULL
        },
        {
            0x016502BE8ED56020ULL, 0xEA070DE151194E94ULL, 0x276278D8E47B98ACULL, 0x05A26B0ECD95BB9FULL, 
            0xECE0805D67D765C0ULL, 0x0A290DB338CF9424ULL, 0x455C6BEFF8D8070CULL, 0x2BCEDAD384F57AFBULL, 
            0x258BD6F460D0F86AULL, 0xA194BB50FEA763EFULL, 0xF66471FFFC66F6CDULL, 0x520E882F6C9749BCULL, 
            0xA145D004236B713EULL, 0x6129B7352F583B27ULL, 0x11893F358F10A6B7ULL, 0x6E7A8B2F1406D73EULL, 
            0x8A51A3B3747637FBULL, 0x591B95FB7C7DFE09ULL, 0x89D2E3DDC419AD6EULL, 0xC81976C3F871CF44ULL, 
            0x3080EC22F2203A37ULL, 0xBE67EE933955F875ULL, 0xD8D4978453997F89ULL, 0x40A22B82799A61EEULL, 
            0xA359D4C2A95D55B5ULL, 0xBB92EC2D515BD123ULL, 0xCDDC203016F5B1B6ULL, 0xB27C46F3C978E84DULL, 
            0xB1EC29F826A143D7ULL, 0xA0C1F081F0ADCBA8ULL, 0x1DD92992E042D63DULL, 0x06F520297097CED8ULL
        },
        {
            0x5A89348A3967895FULL, 0x561059B60D7286DAULL, 0x863FA94BF147196DULL, 0xF52162B5B6339F7CULL, 
            0xA905A603072D2943ULL, 0x02592AD4C86A4EFEULL, 0x8226F054249E27D9ULL, 0x18E9763A33EADBE3ULL, 
            0x3563A8E3A9C4E478ULL, 0xFCCFB125726E6CB3ULL, 0x512D85BFB18BC8DBULL, 0xCA45D6BE43AE1467ULL, 
            0xDA3EDC1DD07806C6ULL, 0x1355BC7E73E20565ULL, 0xD74CA9C603EE66F4ULL, 0x63DE1CCFF2FCE2FBULL, 
            0x5A29FDCDD6553FEDULL, 0xAF62A3649773AD43ULL, 0xA37877150EAEF6BCULL, 0x3EFA212795A6AEAFULL, 
            0x8563DAE2A3FB0F03ULL, 0xBB53CE533CA84683ULL, 0x16E4A0A53100F96BULL, 0x9852FEF4F8C257E3ULL, 
            0x97AEEA8275901563ULL, 0x9C313006A4DEF940ULL, 0xAC9DB771015E4281ULL, 0x537FC2A9FB48A446ULL, 
            0xEB72BFB6C05137D6ULL, 0xEA1C6F7B03252575ULL, 0x069D6E6A8C4CD517ULL, 0x68107344DAE332BDULL
        },
        {
            0x71926E9DC3386ACCULL, 0xE1E8573F9F38F9D1ULL, 0x791CE56999F469FDULL, 0x5C158C0525C95C35ULL, 
            0x1D04CBF87B1E29C0ULL, 0x49C275123EE7BF4EULL, 0x7BBC92F1BE942B44ULL, 0x12C921DD7A065C8FULL, 
            0xD66E3E47B5A81919ULL, 0xE46452B7F7774B44ULL, 0x11CD7A128EF0DA9EULL, 0xFE5522D6B360E82FULL, 
            0x53C9657573E8FBB6ULL, 0x29EE488FF0EDBE86ULL, 0x82EFD73FFE58982DULL, 0x42C6B70AB23373EFULL, 
            0x501CA72A314EE775ULL, 0x3252CA45EE6FBB2BULL, 0xB752B5B995061A96ULL, 0xE41BB28B3E8960D5ULL, 
            0xD5CB2FAC80B30781ULL, 0xB6C6D3D0121A27E5ULL, 0x8DC0258499383641ULL, 0x9DF693767AB4D422ULL, 
            0xF6966E742043FCE9ULL, 0xEC357A3C0434B7E0ULL, 0x7571268852FAD361ULL, 0xE41A6507D03F0547ULL, 
            0xAAF450473503D0CCULL, 0x962C4113D11FA809ULL, 0xC52FCB86AFC56936ULL, 0x4A7B152364BD0D75ULL
        },
        {
            0xF32FF898ADA4A838ULL, 0x743EA369D9DC3002ULL, 0xBFB1EEC6884AABFFULL, 0xC20E7C007E89074BULL, 
            0x37DBE9BAA739946DULL, 0xBEF5DD15DA9E7058ULL, 0x007D081C9E3F7629ULL, 0xEF61DE6B32A38688ULL, 
            0xADBD172B6799D4F0ULL, 0x4ECF0570D164C651ULL, 0x6BF167508E82999BULL, 0x214BC5BFC65C05E2ULL, 
            0xDA8B329B4E6AE3B2ULL, 0x3F20BC1E0738DE31ULL, 0x9BDEB99501C0FB8AULL, 0x60C3B929B8FEC05BULL, 
            0x843D0AD570DCEAC4ULL, 0xC8FDB00374AA0F7FULL, 0x156E7213806AB5F4ULL, 0xE97C2ADDE07E532AULL, 
            0xA26027CD75EDB915ULL, 0xE509131280E7CCF1ULL, 0x36E4E8EA94F087A8ULL, 0x1F62CF5EDE05A0DFULL, 
            0x0541DF5DB172E01CULL, 0xA95CE891E2EDFF07ULL, 0x4C1F093D7E2B3A0EULL, 0xC586F970B2BF76D3ULL, 
            0x83EFF7EEA33815D2ULL, 0xA79D94FA81E2C2C3ULL, 0x11C919C5663B9D28ULL, 0x944F47A5A59EF0FEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseAConstants = {
    0x631DDAE5BF486BD8ULL,
    0xEBFB699E6DB932D0ULL,
    0x7CCFB4A8F029166DULL,
    0x631DDAE5BF486BD8ULL,
    0xEBFB699E6DB932D0ULL,
    0x7CCFB4A8F029166DULL,
    0xD7D7A77CF3DAD325ULL,
    0x13F639C31ECAE08CULL,
    0x1E,
    0xDC,
    0x76,
    0xB7,
    0x2D,
    0x40,
    0xAB,
    0x9D
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseBSalts = {
    {
        {
            0x3F13A26CBE73BFE7ULL, 0x115A3E745220AEBFULL, 0x32310A0407112F0FULL, 0x58457D03347F1D2EULL, 
            0x5CBC387080FBD292ULL, 0xBF70B77D594ABAA8ULL, 0xBEEBF85BF1CA94BBULL, 0xA19D67455FF7652DULL, 
            0x514E98549FE5D341ULL, 0x8E85D91F11D9783FULL, 0x90E46A26D75A3C13ULL, 0x7D1E0DBE9CB156A9ULL, 
            0x0F98B5D82B54AD3CULL, 0x0E9C8B2F33884D5CULL, 0xD9BFB74AB7A9FCDEULL, 0x2E8D09810B5F1D38ULL, 
            0x452A819734FFD199ULL, 0xE1C8B3E695E1A14FULL, 0xB6A0840E57D18A20ULL, 0x35484074765BCE4AULL, 
            0xECDC1C0BB6624F67ULL, 0x9F7A074A14D1C188ULL, 0x0CC9199D865C98C5ULL, 0xBFCBA5FFF9D4B608ULL, 
            0x1CF308D841335811ULL, 0xC03E6194447ACECDULL, 0x7C8B31A522634F66ULL, 0x25040F3D3F7CA4F4ULL, 
            0x24260BAF40D7F40AULL, 0x30123F1A8EFCB400ULL, 0xD42F2A3E133A19DDULL, 0xB55E4D169AFA4A25ULL
        },
        {
            0x1E2DCC4DED312CF8ULL, 0x2476AF0EA545CCCEULL, 0xF3D5E1061B26D298ULL, 0xFCDB57107B8EDD39ULL, 
            0x08B28099F19DF72EULL, 0x74EACF93C76B5879ULL, 0x9BD237F5DBD14CD2ULL, 0x9A019D0BB255A1A4ULL, 
            0x827989AE5B5B1AFAULL, 0x6EC99EF7CD6AA49DULL, 0xE272FD56B4F6EEB9ULL, 0xF54FC76526450EE0ULL, 
            0x991359E49DA49D1EULL, 0x921D826876E324E4ULL, 0x097675A6867511E5ULL, 0xAE3566DC801C731DULL, 
            0x14E36D302E84BE8BULL, 0xA4FF7393EA5220B6ULL, 0xBE7B014EAB23CDD0ULL, 0x2AD0CFED03636B3FULL, 
            0x1D82F94AF1DA728DULL, 0xFBA8432A0FAF0A79ULL, 0x7B6A3902AFA43CDDULL, 0x3D19BDB63F8C1546ULL, 
            0x538AFE9D499EC7BFULL, 0x2A41382F76581D21ULL, 0x191AE8EE0D8F42DDULL, 0x65C65ADCC9A99E73ULL, 
            0x051071C0C340212FULL, 0xB4942F0F19A11CEAULL, 0xA795DEDE1D1D0227ULL, 0x0B1A4A803195CDF4ULL
        },
        {
            0x04CCFC578809A35DULL, 0xB7DB725D464647BEULL, 0x2F310CD03B350D2FULL, 0x33792ABD17C2F92BULL, 
            0xF4210D9412F30E84ULL, 0xBA38676BAC2E97B5ULL, 0xA0A26B12E5D60F48ULL, 0xF423900A1B2671E4ULL, 
            0x7D4A802071202269ULL, 0xC056A2A65585C40EULL, 0x52B348B154AD6AADULL, 0xF1F159DD1E7EDF98ULL, 
            0xF7BDD743F430F59DULL, 0x782D104FF8A3A0AAULL, 0x0A556AAFF8E13EFFULL, 0x59A16735A2D684C2ULL, 
            0x1FE4B7A8A561BCEFULL, 0xAB7D119DFC49551AULL, 0x31A85D6D34F5EA12ULL, 0xADCDE221DCC90B79ULL, 
            0x1C424FA77AE6EA3AULL, 0x31DCCD7687B66E23ULL, 0xC9219ACA3A128517ULL, 0x3A68B5387983200AULL, 
            0x03D343FF20131A50ULL, 0x80E11734937EA0F8ULL, 0x11B775D838E57B75ULL, 0x135F738AADF746FEULL, 
            0xF15214E7DFCDB5C2ULL, 0xF232C0DBDC04F01EULL, 0x243F1DA46D9D3235ULL, 0xFA205C60B40472A9ULL
        },
        {
            0x85CA9A670343E527ULL, 0x1FE7CC50077A5ACBULL, 0x724F94DD51A0DC8DULL, 0x48F6BF0D0ED80D21ULL, 
            0xCC6321AE6729185EULL, 0xCE728C1B8DC1FD94ULL, 0xF1E2EC4AB5066C25ULL, 0x84BF2A137743682AULL, 
            0x386BC27AAA4B90CAULL, 0xEA320849770CDA67ULL, 0x46F26195BADD92C2ULL, 0x09E28AF7189FBAF0ULL, 
            0x443765C5CA598B1DULL, 0x0FF6E595A80CA23FULL, 0xEE188482E0AB3577ULL, 0xB34982F503116A9FULL, 
            0x442FD73DC43112A6ULL, 0x1766AE2B09075AFEULL, 0x64B88C4CE97EBC18ULL, 0x30D0F7A44E08343DULL, 
            0x3103A93941B6785AULL, 0x6158F4858F510541ULL, 0xB0FB95FC5A348418ULL, 0x813C80B8F77F3524ULL, 
            0x90D4287CDC3EB422ULL, 0x32C535DC7261B55FULL, 0xCEF6A3AB19C5B523ULL, 0x9CFCA2986540574AULL, 
            0x094EFCFEC33AF16CULL, 0x495DC98EBEF83F66ULL, 0xE15B8B24EC6AEACBULL, 0x2E43EDE57DEECBBFULL
        },
        {
            0xC3A971F420483213ULL, 0x0035C68CA9E425ADULL, 0x58B3865DB2EB6254ULL, 0xB495DE13CC9E0EA9ULL, 
            0x7A2EFEE9604A0BD4ULL, 0xDCD07A14C2ABA10CULL, 0x4FF524DD6133FA49ULL, 0x2867647540D609D2ULL, 
            0x2A29EBC423447DFCULL, 0xD136381022E2F045ULL, 0xAD03FDEC46BA620FULL, 0x7F9EBF3A8C7394B0ULL, 
            0x37B0620EABE2F876ULL, 0xEE1D77D7C38A8B6AULL, 0x5E1D7A60AE09D358ULL, 0x32086220E9D58407ULL, 
            0x102F8146EBE33F9DULL, 0xE67B936D9AE5F5EEULL, 0xC46CE15BF98AC367ULL, 0x756C68231101CD8DULL, 
            0x09E73B0F6EFDC9F7ULL, 0x1FEB9A802C23B75DULL, 0xBE5985706B5D39D6ULL, 0x1E4A67F78CD2BB94ULL, 
            0x52628A41BF87B049ULL, 0x5F841E7F121560DFULL, 0xDA3A4CEB6C94898DULL, 0x8CB6929999E91D23ULL, 
            0x611F34614D1A482DULL, 0xFAA860F63605EB0CULL, 0x90EEFAC69EA350CAULL, 0x2B1E5FF20869C95DULL
        },
        {
            0x94DBE1169B774F5FULL, 0x0C7DB379EE9F6734ULL, 0xF8D15880410FC734ULL, 0xA7D9C3D05D146429ULL, 
            0x9767D19E1F7E213FULL, 0xED16AAEAF403423CULL, 0xDD646408EB972EF3ULL, 0x42B3B50B219013FEULL, 
            0xE0E79CBCE68B23C6ULL, 0x0F93E0E0EA64187CULL, 0x303095175262D2BFULL, 0x96CF1CC9000D5F26ULL, 
            0xFE3E8BE3BDC6149CULL, 0xAB7087E804E7F6D3ULL, 0xD3C3E4FB89D7BDA1ULL, 0x3D22DF294A354F70ULL, 
            0xFC20DE1A1F759598ULL, 0x57F7265B66A9C3A3ULL, 0x4A99326DE53FD624ULL, 0xB4966E8CEE5F42B5ULL, 
            0x35C5BD8938A8598EULL, 0x5D468BC4835C543DULL, 0x3C4E3E8AADC2C2D6ULL, 0xD51B333401187CD2ULL, 
            0xAA3824D3FED86EA3ULL, 0xF17FEC7A337EBFE8ULL, 0x7FE860E88B170FB1ULL, 0xBC51FBF79B277490ULL, 
            0x4C9D27867E5EA009ULL, 0xF5C314DD487945A5ULL, 0x20604FBD7025DA1AULL, 0xACD35F4126364CE4ULL
        }
    },
    {
        {
            0x5E93D67B88C43527ULL, 0x64BAE1171DA9BD1BULL, 0x253305EC67965C6BULL, 0xCB064AB65EF7689EULL, 
            0xA5BAA0039785BFDAULL, 0x0217358E1A63EE04ULL, 0x3453FCF9F168EB4AULL, 0x236F04B91E2A4180ULL, 
            0x7EDE98B7FDBA2214ULL, 0xC09454BD2413BB05ULL, 0xDDF34D1976491D44ULL, 0x284FBACD35D79AF2ULL, 
            0x4FAC9206E4247B1BULL, 0x84F3B017915AE0C6ULL, 0x06889554596FCB7BULL, 0x424241124DF83011ULL, 
            0x4635F7036ACEC861ULL, 0xF1B8B2A354BD5076ULL, 0x480A35F007D29BADULL, 0x4E3B2882A7FD5FD6ULL, 
            0xA52F2FBD64156B97ULL, 0xDD5D1D2841DD7A74ULL, 0xE4287A8AED0B5D6AULL, 0x020F73ECFC6E3B7EULL, 
            0x599379AFF84AA9FBULL, 0x05196637F6301E89ULL, 0x3F367AF663460DF7ULL, 0x5FB0BC050266BAA0ULL, 
            0x790EC3EAA1C766E5ULL, 0x9FF333C33317EE86ULL, 0xC628F34A476DD0F7ULL, 0x36D02FD9AA2EAE4BULL
        },
        {
            0xC8B69529B3724C7CULL, 0x78406470F8042FE6ULL, 0xF60CED0CE3906625ULL, 0xAD40FD5B20C2267DULL, 
            0xF2C1C5ADCC460170ULL, 0x594A3B293C0CF497ULL, 0x255CD5DB4B34C66CULL, 0xA0F9DADA380EA292ULL, 
            0x6860DB64486841B3ULL, 0x1E9E0E684BDAD38CULL, 0x1D93C580B41B0CE3ULL, 0xB99D3DF2DBB7A8CDULL, 
            0xE2B7D54453A026D2ULL, 0x72000CBABDC88F38ULL, 0x8F577A451FDBB836ULL, 0x4A85ACC0D833351BULL, 
            0xFA55321D67057374ULL, 0x22E9891E3121D140ULL, 0xAB8AEB10C7B0CD5AULL, 0xDBCEE1787555B64DULL, 
            0x9F0C1D1AE3E5082AULL, 0x59741A42A29EA88EULL, 0x41F0CBC6050991F2ULL, 0xA06AB2C23C47ACBDULL, 
            0x2B67D408A92AD25FULL, 0xACB7BA128424EA4BULL, 0x553C79E634124E49ULL, 0xDCE3ABC96A89B399ULL, 
            0x0AC0812A523601B4ULL, 0x9BF6D90A1071F1DDULL, 0xDFD991344830F34BULL, 0x0D17A225B5133509ULL
        },
        {
            0xC6D40EE800CD3391ULL, 0x9281FC380D4AE8A7ULL, 0x1B0DAA305FC40041ULL, 0x2FA9BFED157CC23CULL, 
            0x0D01760FFABC5C6CULL, 0x9CC3B7DF3B0A66C3ULL, 0xF61CF3B62F8A3DAAULL, 0x1B52FAF790E9E27AULL, 
            0x304E2D16DB58721AULL, 0xF9722EC91487941DULL, 0xAF8BE334F4A3E9E4ULL, 0xA3618BFE0835AA4AULL, 
            0xBBD9CAFA0537054FULL, 0x1F6CDFAC001F4E73ULL, 0x8479887BC798B285ULL, 0x97EC5C372682CA90ULL, 
            0x3F0A75E4741DA785ULL, 0xBD49D696AD2D5004ULL, 0x6F955DF595BA21F9ULL, 0xF4C53C879655A5E8ULL, 
            0xDCC3D04C2FF02EA8ULL, 0x6AE572B053E4D7DEULL, 0x7010D89952A909E5ULL, 0x2EA83731395FEBCDULL, 
            0x7142BDFCBC7EEAD3ULL, 0x29E4B5AAC35107EEULL, 0xF4B12A1C5A2DC560ULL, 0xDD73ACED341A73DBULL, 
            0x76B289C98AF437D9ULL, 0xC7BD49CB1D8069FAULL, 0xBD612767930ACC2CULL, 0x25C47334EFC0D88DULL
        },
        {
            0x1DA4F6F4E45D8FF8ULL, 0xEBB33020E0D8AEB6ULL, 0xBD93552C5095023AULL, 0x66BAD4488061F3BEULL, 
            0x57074A82E322B386ULL, 0xBBB42DD387555A12ULL, 0xEBAC4CA6230A6BACULL, 0x03CAF2E2F5AC59D5ULL, 
            0x3F9B65EF0FEA13CAULL, 0x555C1923C1DAF87BULL, 0xF94142EF40192A8CULL, 0xB134E2C918C08BD9ULL, 
            0x3C77D1DD25D38E1BULL, 0xE78A826400F4F162ULL, 0xEFAD42116869F181ULL, 0x7DED59D7AEBF3855ULL, 
            0x0AEE6FD50167C04BULL, 0x8092367E44CE0D61ULL, 0x73C031A70EEE6271ULL, 0x44CC684AA532383AULL, 
            0x819A0D2702129AECULL, 0x311CD30480B6E022ULL, 0x2DE76D7767BBCC10ULL, 0xFACC4A821EFDDA05ULL, 
            0xB51CB6F199651126ULL, 0xE88C66D0DEC6D02AULL, 0xD04C1D9C160507E9ULL, 0x7249EBDF4AE93542ULL, 
            0x75D4F64341E0BBB3ULL, 0xA91582ADE4F5C89CULL, 0xD75EDE1A38245E39ULL, 0xB7197F483DDFFA57ULL
        },
        {
            0x86EDD7789FB4C2C8ULL, 0xC82C6BF9C91A1B95ULL, 0x5DCAF9920E673FFFULL, 0xF26228550F9905E3ULL, 
            0x75A5B2CF84DFCCABULL, 0x79905B8C6D101A8EULL, 0x70EE39C8AFF00387ULL, 0x301947ABF7C4F920ULL, 
            0xD604974EC402321DULL, 0x114633519A7EADE9ULL, 0x4B9AD7089EEEED62ULL, 0xDB525829629570F3ULL, 
            0x82875CD2762CBFC6ULL, 0x05494E82791D3E1FULL, 0x16F0AEC686ADADDCULL, 0x390E7E515FD7E3DEULL, 
            0xA165DB8E060985E5ULL, 0xEC3C371055D57DDEULL, 0xD9BEA5CC8808AEBAULL, 0x40951E7079BCA3D5ULL, 
            0x96B0F147AF3E7C57ULL, 0x74D1E3CCB627162BULL, 0x3DE6466ABD2743E8ULL, 0x357F85256A512A9DULL, 
            0x525B082892939CADULL, 0xB3A561623C342587ULL, 0xCAB3EF00F78248B4ULL, 0xE8D922871F65F4CCULL, 
            0x05A3489BAD079063ULL, 0xA3AD62729AF77007ULL, 0x2CB652B3C5FD03D3ULL, 0x074F198FE10C0D58ULL
        },
        {
            0x999545D23DCC72E8ULL, 0xFE1A568E94ED3E1AULL, 0x5A801A92CA74FBEEULL, 0x7F4996B0AB00B73FULL, 
            0x1B2B0565493323C2ULL, 0x991843839830D5E6ULL, 0x55C8EA8DC908C1D3ULL, 0x1FD1EC32D7797F66ULL, 
            0x0709D6ABB67F5BFBULL, 0xAEDF9B1699B96B3BULL, 0x8FF9FC34CFE98968ULL, 0xA535E1D5653907ADULL, 
            0x4C4E28F8DF204AECULL, 0x69493EC59FE5C452ULL, 0xEC55DC9501256E93ULL, 0xDA90F965804A2ABEULL, 
            0x7A151EDC767C1F67ULL, 0x7B0B47DFF998CDB7ULL, 0x84F4E435D34CA014ULL, 0x8FEDC628F0847594ULL, 
            0x73DFD05C9AE0C190ULL, 0xAE8F41DE764B7430ULL, 0x13C286D4862E9FA0ULL, 0x501F7F120931B14AULL, 
            0x4C482B5E27574BACULL, 0x5E74A36B488FFF13ULL, 0xC9A1C47D97E2D263ULL, 0xF53BE9550285E283ULL, 
            0x2D5E30E498740841ULL, 0xEEEFD77D7AEB9AE6ULL, 0x459C485D206B11C4ULL, 0x3077DFB699B7773FULL
        }
    },
    {
        {
            0x6E710F6F9768B6ADULL, 0xB97268532548BAE3ULL, 0xCCF9C8613FBBC2FBULL, 0x91DAC8B70CA1F190ULL, 
            0xBC148EE640786A98ULL, 0xA7E00604B236963DULL, 0xD0A118DD2D7F21DEULL, 0xC165F24D14FCDDABULL, 
            0x2EBD8591B1DC54F7ULL, 0x3A645F08354BCEA1ULL, 0x108F3D3C3DECF39EULL, 0xA1032F629500531EULL, 
            0x11768A2C11F61EEAULL, 0x9EFC6658285F5810ULL, 0xAF0339FBB61E45F8ULL, 0x4F4C4C7B2D0FB0F4ULL, 
            0xA5181946EB97553DULL, 0x0DEDB51D0ADA4222ULL, 0x42F93751BFBBBAD5ULL, 0x61F6344F9D65EBF7ULL, 
            0x6683637B95752D24ULL, 0xB37D583C7EEB3B3DULL, 0x26733CE960D9F5A4ULL, 0x2D26856E3D43459BULL, 
            0xD0C39A6E865C132CULL, 0x7964D73BCC5DD614ULL, 0x3F5A7A84C8F806B1ULL, 0xEC0134FCE25B8F0BULL, 
            0x3748A4D6FE7E6795ULL, 0xF6189EEE4A8AFABCULL, 0xFE5040718977B171ULL, 0xFB9E7A534CB14EA6ULL
        },
        {
            0x8FCE1E454CD2DC10ULL, 0x3AE8AF6BCA24F652ULL, 0x2D4960B314DF1237ULL, 0x32572DC0F1AAAC00ULL, 
            0x8729CE2719CA9EC9ULL, 0xF697D38B7F99E52FULL, 0x3785B1DCF4146F51ULL, 0x798BD824AC7E3B12ULL, 
            0x0FC7CDD26E9BB107ULL, 0xED3D2631F80D7A5CULL, 0xA3D0AF46E9FF08E7ULL, 0x9EF1A72585055D70ULL, 
            0x3F44323CE74BB95FULL, 0x352A106AD950D729ULL, 0xC07563F3A584D068ULL, 0xB80781E833DB6677ULL, 
            0xA03386AD590047A1ULL, 0xBA7DC9FDDBF94B6AULL, 0x3B59B569279C07F2ULL, 0x4BC3A80EF658323AULL, 
            0xBA6C3C4E72D0CA8EULL, 0x863C4F27DF429C5AULL, 0x7215CC8274E6E170ULL, 0xA0B3B96BA2B2FB3BULL, 
            0x2E503A521E961EC7ULL, 0x277E8063BAAB8424ULL, 0xAE7CFFA343725F79ULL, 0xBDB9B91B025F24C9ULL, 
            0x657A873E464207D3ULL, 0x2AF46063E33C1D3FULL, 0x0147475F97A0AD58ULL, 0x9712D06CBFEF0CD0ULL
        },
        {
            0xF5069B4ECFC3A7E9ULL, 0x09401B959F20A042ULL, 0x284AD9E71DE006F4ULL, 0xE94C21E44D30A1B2ULL, 
            0xF262B98D18EE81A5ULL, 0x2F52B5F7D3FB5BAEULL, 0xB4C6C9F2A3C6A77EULL, 0xC361865F8304E807ULL, 
            0xB0DF3FB018F825AEULL, 0x27790653EFDC982BULL, 0xF415B3A11D7E416BULL, 0x8C8264ACC88ACCB9ULL, 
            0x54AC765AB191AAC3ULL, 0xEE1394065854F760ULL, 0x57FCA92BC1801C9BULL, 0xD11FB353A1EEFB6BULL, 
            0x482E972B5B706C97ULL, 0x2C9EA826B8F48D98ULL, 0x48A502D0C428A246ULL, 0xD74ADB2AC1264B08ULL, 
            0xAF85A0B324D4A998ULL, 0x690E74BE8152B6B1ULL, 0x2455D0587691815FULL, 0xDFCB7091A391B3CDULL, 
            0xD0BA490BF8362B0CULL, 0x530CF46DD986D8CCULL, 0x81C7CD8E6B61F7CDULL, 0x292AE2AE131AC3FFULL, 
            0xCB9B7E4994B4B4C1ULL, 0x869E6483F64B0196ULL, 0x1A9F92F4EACB056FULL, 0x421194389E6618ABULL
        },
        {
            0x0F44E3B9658D76F9ULL, 0x308EB9C0B83323FEULL, 0x63FF4639F1470858ULL, 0xD30CBC89CC3354B3ULL, 
            0x0619E41CEE7E54E9ULL, 0xA3428172EFF499F9ULL, 0x0B7DB37E40EF0C6BULL, 0xE0637B40B4558663ULL, 
            0x84FB617B96D89732ULL, 0xF6D6C6633E1716A9ULL, 0x9776C49D659E2CDEULL, 0x1787587DC37375DBULL, 
            0xAC685477D262DBEFULL, 0x6631E9BC6BC6E083ULL, 0x5049928A1EC0582BULL, 0xEE25D87616085A99ULL, 
            0xB415FA48E87AC6D2ULL, 0x37DFB48FC9E3F351ULL, 0x5C201068235C5B9EULL, 0x09E5BE08EA53D6C1ULL, 
            0x27963FD7952B79F7ULL, 0xB2687292A3B58D35ULL, 0xDAD4E7E06533F0EEULL, 0x374BA363F7B9E5A1ULL, 
            0xB1C36D5F3E715C91ULL, 0x6217F6F0C926316AULL, 0x0364E138E155A041ULL, 0x49525EB64C757612ULL, 
            0x47D735AFD95CBFB6ULL, 0x268A57AECCE0F94FULL, 0x3A3B557081A32E74ULL, 0x7783E0B8683F7543ULL
        },
        {
            0x00D2569BA2D6EF37ULL, 0x75A2615621E8C2C2ULL, 0xAB62FE9690F0B78FULL, 0x46ADE98C9AADFA20ULL, 
            0x13FF82E85F6B63D0ULL, 0x79E749C0E5EB69D0ULL, 0x0A9CA2B343A48FB5ULL, 0x89EE300F94CD17F4ULL, 
            0xA0AF344EFE6C889FULL, 0x89811ED343696E44ULL, 0xC431EB5D684E983AULL, 0x06FA53A1DD4CB99FULL, 
            0xD22ED0161D82C0C4ULL, 0xE64E21C89D8DABE3ULL, 0xAE80108082A17721ULL, 0x95B115083C3EBFADULL, 
            0xF6C4D9BE580382EFULL, 0x99B1AA7692ABF23EULL, 0x3195ACA067793C67ULL, 0x9E8AA13291E8E5CCULL, 
            0x9133AAA846A9AFA4ULL, 0x291C4FE503851DEFULL, 0x8C14884AF7DD663CULL, 0x87A04732416DCEA8ULL, 
            0x8692F7D5CD764D57ULL, 0xA53B07DEB15AF3B8ULL, 0x7EC893ACE66BD340ULL, 0x992A46DAEE051379ULL, 
            0x67EB0B8F15E93D99ULL, 0x5D46527217BD8014ULL, 0x14D9DEBD4D91DF74ULL, 0x21CC20595450BB60ULL
        },
        {
            0x378BC6998657294BULL, 0x52176040F3A5E4A9ULL, 0x2A51ACA366501B19ULL, 0xA19AF28687E5E2A5ULL, 
            0xF53C7D403CF1C0F9ULL, 0xDB86073E1ABFCF4FULL, 0xF986DF817F0DE62DULL, 0xFD27BA0AFCA9E383ULL, 
            0x337057FD139F48F7ULL, 0x8E8483EB95039355ULL, 0xE9BA3051CD44E8B3ULL, 0x88F687776A235FB8ULL, 
            0x6E0AFFC37D3BCACCULL, 0x8BC8951C253A6AD1ULL, 0xB5E4B5D338A98F31ULL, 0x9B9CF86B84A423ECULL, 
            0xA48A8F1A6B38E147ULL, 0x0AADEBFA30249094ULL, 0x2ADC84928714AA47ULL, 0x379BC4FB1E0A2DBCULL, 
            0xEAA28565CF0C4551ULL, 0x6D676E1CB6AA037AULL, 0xB3A5CFDF8A442790ULL, 0x1C87A86AF7E1364FULL, 
            0x967AA0D7F29F28FFULL, 0x49661FF719D7CD4FULL, 0x419984ACF582E0C4ULL, 0x5D890802F2CC47C4ULL, 
            0x57476B4267E02376ULL, 0x07ADCBEA4C3B5D08ULL, 0x7BC88FEE2EBC2E6FULL, 0xE3C9BF9C0DB748A6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseBConstants = {
    0x851E63A855E9AB1CULL,
    0x2A88A7E7D5DE009AULL,
    0x5C43CE0DCF48D2C3ULL,
    0x851E63A855E9AB1CULL,
    0x2A88A7E7D5DE009AULL,
    0x5C43CE0DCF48D2C3ULL,
    0xB2E646E21CFB4B27ULL,
    0xA1E78BD05A28B711ULL,
    0xCB,
    0x21,
    0x3E,
    0xE1,
    0xFA,
    0x3F,
    0x7F,
    0x84
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseCSalts = {
    {
        {
            0x328444EC4D3158DAULL, 0x90A6CCDC7C5E2014ULL, 0x9F6BBC66FECA04A6ULL, 0x6B5CA98CD904E5E4ULL, 
            0x7FBD7EA7B3B210E8ULL, 0x7576E77763D665C4ULL, 0xF7461299E24A1803ULL, 0xD38F28DD6244185BULL, 
            0x9C0168C7F469B103ULL, 0x99A98565D2A51EA7ULL, 0x88267602632BD2A1ULL, 0x14F022678E6A3BE6ULL, 
            0x1AFCAA92A7F1DA04ULL, 0x80A21FF937E5D98BULL, 0xA612A9EEA55EA1B2ULL, 0x37F6EE48CC87BDC8ULL, 
            0xF9DA4B9E7C1213DDULL, 0x396975FB814480A1ULL, 0x7FD018F2F5E241D5ULL, 0xB4ABD74EF438D2C9ULL, 
            0x17413B47EBE42D5BULL, 0x1DF1E39DBEE0B205ULL, 0x9356E953327568AFULL, 0xC898F0A145D32D54ULL, 
            0xBEE2A2CF46FD42ABULL, 0x9CCB5F6102787D4DULL, 0xB20AD3D493738801ULL, 0x18BF37893DA6DB23ULL, 
            0xB6C33E0E9823F5BAULL, 0x456AA7AFE7762BADULL, 0xCA656F97020A924CULL, 0x42A754C30690D169ULL
        },
        {
            0x685FC5CB290C5925ULL, 0x4995F86522DDD6B7ULL, 0xF15E4EE4E33C72A0ULL, 0x9060CD4FE5A7D0C2ULL, 
            0xA7B7A47264B38797ULL, 0xD46B62558F1E135CULL, 0x37195076B2E5B3FFULL, 0x61EACE1B8A6AFBEDULL, 
            0x08CE5285E1FB8F82ULL, 0x9D276F8F1B0AC302ULL, 0x7EDBA55D2AC7D73BULL, 0x6E31BA0C0F732959ULL, 
            0xE569988959EF9150ULL, 0x82CCAE5BECFC3537ULL, 0x259C2DC4C2778C82ULL, 0xCA10646F44FF2B03ULL, 
            0xC22CFD8C4D0A8094ULL, 0xEA959CC9DD2A6A94ULL, 0x6828935035C728E7ULL, 0x2AEA8820DA7B0D77ULL, 
            0x731FC77464E8CB61ULL, 0x335B165CAEB74414ULL, 0xB613155480F97C57ULL, 0x800674ED4D4054C9ULL, 
            0xD3B058EDD749AEBDULL, 0x73C5679D7B4D46C9ULL, 0xB8A80713B381595EULL, 0xD627882996AC4423ULL, 
            0xA1A6D05768778A1BULL, 0xCB66257681E2B08CULL, 0x1E0A786470CF008BULL, 0x3495E06F4C0FE784ULL
        },
        {
            0xC9A24EA926B5ADD8ULL, 0x4E38405046B07BC2ULL, 0xBC7B0772D0E7F7CEULL, 0x43EC629DDF2CE962ULL, 
            0x709C19EBC736F906ULL, 0x6DB112837AB5B8EFULL, 0xACC893E401ECDD81ULL, 0x66E5ECA6D44232CDULL, 
            0x746CF55D411D625FULL, 0xC7EBB7E3D5820DA0ULL, 0xA3520F6C6A9FD262ULL, 0x9AC965E94249E569ULL, 
            0x0A16EA89C5B10E0EULL, 0xAAAD118BA193734EULL, 0x7544B18B73C3EC52ULL, 0xB697965C77F84AADULL, 
            0x8FA1067E36D4EDE4ULL, 0xF8A33875560A8A96ULL, 0x1D00E2042D08B587ULL, 0x74EFE001DEF4C5F6ULL, 
            0x216DF8F50A744FE0ULL, 0xBFDE98C5E9DEAEFAULL, 0xC11E19AE8400E505ULL, 0x70896F08A0CADD16ULL, 
            0x401751A15F132802ULL, 0x449EF643F02207EDULL, 0x213F6160A73F5BB2ULL, 0x4A8A8474285F7C7CULL, 
            0x5902641D8C8CBDA8ULL, 0xCABDB1564216EF43ULL, 0x5A0F018D7BD5B2E6ULL, 0x162753AAD15C720EULL
        },
        {
            0xDA6DDA610E567414ULL, 0xF34B65F0DAAD1E9FULL, 0x13E6D2FF786F2A49ULL, 0x3755D12345A50685ULL, 
            0x74E74809249F4003ULL, 0xD0F1D38EFD194C85ULL, 0x908D772E0892CD03ULL, 0xD0EA960AA6F06F6EULL, 
            0x13E413A0C2352959ULL, 0x50FB9CCB313DD8D0ULL, 0x3CE5513F8E485374ULL, 0x53E5FCC73C98AB2FULL, 
            0x7F44DD308A723719ULL, 0xB476DC0DDC14AD3FULL, 0xB8AF75BC563E9527ULL, 0x90ADF82258B5BCB5ULL, 
            0x2B85D7A86BEE68D5ULL, 0x33A3377ECF9370F1ULL, 0x9E5296B3E5E53C35ULL, 0x5131C3CFBC0D5BB3ULL, 
            0xC25C0470EE02000EULL, 0x6C4C638DE70BE1FEULL, 0xAD100E46625BC611ULL, 0x75A1BFA3CECFDA39ULL, 
            0xAD37B6D9EDFE961CULL, 0x1479004C9FC72BC5ULL, 0xAA580D0EE243C316ULL, 0x3FF70EA9559A647CULL, 
            0x2A9F4BDDDB5B9035ULL, 0x0F71AB0F5405F236ULL, 0x3B3F532414F5A728ULL, 0xE3FA5C67CA5B3A51ULL
        },
        {
            0xB61BADB2680D76FAULL, 0x42D9FB3305802A88ULL, 0xD007E443A8EB5946ULL, 0xDEA3FDF1B56776F1ULL, 
            0x2CB43C2D523C475FULL, 0xA707EF7263283FA0ULL, 0xC7FDE7CD6241F033ULL, 0x0D3D766A8CC13E33ULL, 
            0x73C7E4E942901EE3ULL, 0x1BC64181FEB7C2E9ULL, 0xF59FB1732038FF8BULL, 0x3FB26CA205B49371ULL, 
            0xE1035A5CE223BC9CULL, 0x17B05B1A1EAEB715ULL, 0xF43392F5058FFC39ULL, 0x984DD606A5D3F4ACULL, 
            0x3B8D98C1DE517A66ULL, 0xA40CAA081E572294ULL, 0xC6107CE1FFDD4170ULL, 0xCF9D7B569EBE8168ULL, 
            0x34430E7F4900951EULL, 0xAC58D84C15888041ULL, 0x3CCCB4ED0BED94BBULL, 0x6EBA49FF452E1219ULL, 
            0x7FBD7AF9C59E7F4CULL, 0x7A5061A88AC98A53ULL, 0x0411E6A923309096ULL, 0xE12C2FAE59A50892ULL, 
            0x53C7EE98D99A6522ULL, 0x2A35F834E81B11E7ULL, 0xA785F1D3F985E709ULL, 0xFC1CB0DCCBD52E50ULL
        },
        {
            0x71487482788C56A3ULL, 0x6CE26D42C05C0E22ULL, 0xDF8E49F568112710ULL, 0xF396297E218CAA35ULL, 
            0x1E808585F3887259ULL, 0xEDC2DD81EFE87E0BULL, 0x0AA6B60016057B75ULL, 0x488E2DF5F8F479D1ULL, 
            0x25CD99220B8A9845ULL, 0xC2CDD039D5405134ULL, 0x3BAF8E7FFF9F8A33ULL, 0x1F70618EE8F3C1BFULL, 
            0x6903E0301F75CE80ULL, 0x92EF05004C2C47B4ULL, 0xAF4FF0659B294004ULL, 0xE1173239A0902A46ULL, 
            0x5665D007F6C725B5ULL, 0x222147A85F9028FFULL, 0x36C533FF7BAE0D3EULL, 0x8792CFA7E707FE29ULL, 
            0x1095C8B4D36BE6C1ULL, 0x7B3ED1E8A4A7E20FULL, 0x6189AB9A446B7738ULL, 0x7CE0806C77AD354EULL, 
            0x8A098BFC7D6F54CAULL, 0x54F924E46DEF16DBULL, 0x4B294DE012C87EE4ULL, 0x2D1ACF71D3277ADEULL, 
            0x211E93FE5272634DULL, 0xD9352983E1E8DA7AULL, 0x8A415D7C2033DCD4ULL, 0xF9BA3655F28F3740ULL
        }
    },
    {
        {
            0xCD55AEAD314DA2E9ULL, 0x3F9FABAA79A3050EULL, 0xC21C7A5658A3BD50ULL, 0x081612FD2A4A3091ULL, 
            0x1CEE6C5FF65B784DULL, 0x694C92D5C0DC42C8ULL, 0xC9B26F7D36B89530ULL, 0x2EF2E3F0C3D44625ULL, 
            0x83257DEB1247B70BULL, 0xB5D1E0B0643B6228ULL, 0x0DE38600D99DB283ULL, 0xBB9E5EECC3152BD1ULL, 
            0x80B0C8CE44E42B0EULL, 0xD7FF9BE5BB63425BULL, 0x9DD1D7D75321DD1EULL, 0x493FB361A4B11D8CULL, 
            0x099598DD08E87536ULL, 0x95948B8F5B6C915EULL, 0xBB72BB098262E5A5ULL, 0x7321CDE634A01DC9ULL, 
            0xA4795A4B819ABD03ULL, 0x41670D4413D95FCBULL, 0xF37849504DBF4A9EULL, 0x658CD7E8DBB5F43BULL, 
            0x369742E7D80A4AFDULL, 0x26938C6372023D41ULL, 0x28766D924DFF727AULL, 0x1BE6DB6D7A434C7FULL, 
            0xAE6117846D751F07ULL, 0xACF3EA4EEE4AD530ULL, 0xDDA4F963D8800F2EULL, 0x42E3E6A4C48DC475ULL
        },
        {
            0x22650C6A08856F20ULL, 0x37270DE4A8EF03CEULL, 0x297BFCCE99C7199AULL, 0x72A9F34F20E6F6B5ULL, 
            0x250F27472DE32D22ULL, 0x8B4704E25FFEECC8ULL, 0x698EFBAAD2FD55A1ULL, 0x177A285D2367B013ULL, 
            0x309BDD4BAA61F149ULL, 0x002004731AD5EECAULL, 0xE1478E806FDF2EFDULL, 0x025E329EBC48C871ULL, 
            0xC64C8CEC418E0D3CULL, 0x3AB5BB334A1A2FD5ULL, 0x015D5C9674DCEB88ULL, 0x8A08882104BF3E60ULL, 
            0x6DC8AA344707A08AULL, 0x6B6CDAF6BAD3DDF3ULL, 0x1C268B728A083603ULL, 0xEDE6D8D5CA0E7A0DULL, 
            0xAB42B7C2D7F193AEULL, 0x6976B4BC1EA235D6ULL, 0x3A47F8E8DFFD7C4AULL, 0x98ED919E9DD87999ULL, 
            0x006469B489737B7DULL, 0x771ADFABBC348158ULL, 0xC745794EF446DCB8ULL, 0x3BCD010E82E1FA6EULL, 
            0x971EE946990541E5ULL, 0xFE53AE7584E945BFULL, 0xD50FD157FF688D6BULL, 0x94FD85E598EA4A87ULL
        },
        {
            0x0FD40D7F3EA6DFBEULL, 0x5E989ED0A05DE418ULL, 0x14229A05375CB265ULL, 0xC1F73CBD15B13EAAULL, 
            0x2AB63E7C0267995DULL, 0x5CCA60A4B230C08BULL, 0x1B9829D4D4976713ULL, 0x5A043054E047D055ULL, 
            0xC04324530A9E0C74ULL, 0xCF7FE1B6A353A51FULL, 0xC9C263CF9BA5A240ULL, 0x602C058B797C816BULL, 
            0x0DB5042509E879A8ULL, 0x054B9294172E07C4ULL, 0xF68E2825B422D71FULL, 0xAD0955F4C110AC36ULL, 
            0x3A14674978FF4ACEULL, 0x40B92BE1CBBD5C77ULL, 0x2E6FB6C2F31DCBA0ULL, 0xEBBBA101B04DEC07ULL, 
            0x82BBB6ED1F5438A6ULL, 0x6F868AC38C95F7F9ULL, 0x415959020F17A1AEULL, 0xCBB082128FC5F1FCULL, 
            0x5B6A2EFDAF90E229ULL, 0xA94B0E83149B3FD3ULL, 0x0A06A4FB626CE8D9ULL, 0x9E5F5818C5AA1552ULL, 
            0x588A80657F24062EULL, 0x62D7C00090D723F8ULL, 0x9B6285203A43D18FULL, 0x85C84C1FC0BD3677ULL
        },
        {
            0x2CEAD96BF2806BB9ULL, 0x08A63499AF64CBC9ULL, 0xBBD42ED68ADCE128ULL, 0xD8F60CA887C3F569ULL, 
            0x92643026FBEFB073ULL, 0x7F274E99D0776C91ULL, 0x517888D5DBF9258FULL, 0x4C3B693FF4352E3EULL, 
            0xC6329602CEF0A186ULL, 0xD173C358AC093E06ULL, 0xE6459D50789FCD99ULL, 0x36DD44D6B57BA8DBULL, 
            0x9B1420394EDE44AFULL, 0x6F2E5A90FED230AFULL, 0xFD41BBCBF7BB4894ULL, 0x0A495980448CB8DFULL, 
            0x1D614A4B6C5CD0AAULL, 0x21CBCFA2CF82AD53ULL, 0xB807E30503F91C7CULL, 0x2B4D35B4C52504C0ULL, 
            0xCCA637418491AFFCULL, 0x00AA8A107D195C56ULL, 0x6F08AAD9852FB783ULL, 0x472BA89876941C50ULL, 
            0x87525AF8DB13E5FFULL, 0xD838CE0937B95BD1ULL, 0x2DA34476CCA00118ULL, 0xBFD4F845C1AE1146ULL, 
            0x2CD7A6A49037FDA8ULL, 0xE0BE558678E6AEB6ULL, 0xBFD2A0C698D5A28DULL, 0xDD22936CB41633C9ULL
        },
        {
            0x127FAA953093FA26ULL, 0xC06FF01423870DE8ULL, 0xF3D6E338AE650A58ULL, 0x7D5BB2C6D6CDEB28ULL, 
            0x3FD57E7A108DD707ULL, 0x1EE43AEAB4039538ULL, 0x58B3EA7C36186540ULL, 0xE2DD51D17BE6495FULL, 
            0xFA1B5A0BDFCED801ULL, 0xA021B455B35D9118ULL, 0xA6EA6209FC3ADC57ULL, 0x8C87392828C78492ULL, 
            0xC134AF42544B5C17ULL, 0x17C18391EA120601ULL, 0x7A03EBD7966027B7ULL, 0xFF0109501430C545ULL, 
            0x4C5E68FCC52178FAULL, 0x6BC69AFC1B5F20BEULL, 0xD8A4B4718DFF7ABEULL, 0xBC8DD31E36D333E4ULL, 
            0x9296DA37437599E4ULL, 0xBAC4DDEAB77F4B82ULL, 0xCD94B1797AE21656ULL, 0x333EB4597018AFBBULL, 
            0x44ED73E0271DEAE1ULL, 0x12364054C661FB3DULL, 0x907BEFE5ECDC48EEULL, 0xCA7E1F43DC187B52ULL, 
            0x3C684E89940C3DD1ULL, 0xA0C2968682E0CC81ULL, 0x29A2E9DDE1372FEDULL, 0x917AB142427D05DAULL
        },
        {
            0x0802AE91A28633BCULL, 0xE989C7CE85CFC672ULL, 0x9ADFECC0FD85899DULL, 0xFCF7B742A443A235ULL, 
            0x75A4AB07626AD76BULL, 0x34116C4799A7EFA2ULL, 0x303A58C92DFBC92FULL, 0x79662F7D87172D65ULL, 
            0x70FB0B50F7CCC9A0ULL, 0xDC9069844BDF67E0ULL, 0xB2CFA38915B64D93ULL, 0x970D9AD47EAA3D58ULL, 
            0xB3BA102B0D5D9476ULL, 0xE890335D1C6F1CF5ULL, 0x555CEC991AEB8B96ULL, 0xC740F967AF77D6D4ULL, 
            0x0FC9EBA1A2CD87F6ULL, 0xF63E44BB6DA1D8F0ULL, 0x50D8917B1A730B1FULL, 0x94B30C5C9423D679ULL, 
            0xE8B40AE16675CA22ULL, 0xACE4CB23BA2C6FC8ULL, 0x6E59FBE81BC03068ULL, 0xD821B6C112BE17D0ULL, 
            0x4056725F6FE52BDCULL, 0xA84F491C036D5422ULL, 0xF0C3159FF00371E5ULL, 0x6A14C7BC11A15748ULL, 
            0xCC1A34D5645521DDULL, 0xB9587D924448C2DCULL, 0x729917FAD00ECEB7ULL, 0xCE73B689CB3C433CULL
        }
    },
    {
        {
            0x9939CD9B77E179EDULL, 0x92166DE9C4CE7762ULL, 0x99272532F6CABB13ULL, 0x05769CA79888A775ULL, 
            0xFBEF6E6F28F0C883ULL, 0x22BB65224111116BULL, 0x63F2EFD3F3BBCFD0ULL, 0xF66D2C8BA76498EBULL, 
            0xB7B8F9B7622634A5ULL, 0x51479F2ADBDDDF71ULL, 0x089A1F7625CB973BULL, 0xF0309B6C9A74E16CULL, 
            0xD54C0B4171BDDA87ULL, 0x424698694B050879ULL, 0xB9818DC84782DFFDULL, 0x63FF094F04AAF7FDULL, 
            0xFB24A24080D06B5EULL, 0x593EE87BFC8ED423ULL, 0xE86A7928ECEF90FBULL, 0x283445F0CF8C870FULL, 
            0x054D75A566E6B042ULL, 0x9D908564F0EEAB48ULL, 0x0E98241BBB9582D6ULL, 0x96F7EEDD7301F6E4ULL, 
            0x528533C4ED7EC5D0ULL, 0x750E60E1308AC48EULL, 0x721DF0B787B043F4ULL, 0xA1AF8BB27D0DE44DULL, 
            0x3627A422DBBF4FB5ULL, 0x9480493EE1217DCFULL, 0x56A5D64CB0A207F0ULL, 0xCFD23EF0BAF5F326ULL
        },
        {
            0x87F94259EFE1D100ULL, 0x4E7C58556AA5D9D4ULL, 0x4C20C93D688AB66CULL, 0x3EEB467B7096D957ULL, 
            0x777047D5F83F4FD3ULL, 0xD1AED9140C0A1CA5ULL, 0xF1890C43043DBA32ULL, 0xDF0FAE83BEB6573BULL, 
            0xB4C6D2F1CE9B13B8ULL, 0xF0A1992B576D70E2ULL, 0xAEC20A9ABF435E0BULL, 0xFF139861942074F4ULL, 
            0xED0996C8F0AEE309ULL, 0x14CF1C91137FF859ULL, 0x660A3F5D0AF3F9AAULL, 0x5522176563A47583ULL, 
            0x94B276A73EFB6FDFULL, 0x3507171A42729DF7ULL, 0x4B25658B5E2F9BF3ULL, 0xE89AB9C11DA47094ULL, 
            0xDA8510DD21B5C80FULL, 0x78CA47A674E6FBD8ULL, 0x6E4254883071FCABULL, 0xC2FD0A768DB80C29ULL, 
            0xBD3990B22930534FULL, 0xD7659264A5408708ULL, 0xC28FBD41A2B6B76EULL, 0xE95E4BEDB769AB99ULL, 
            0x089F3870A174BFF2ULL, 0x0257E0F29049FAF8ULL, 0xA4B4CE76357857B0ULL, 0xD61241404261E300ULL
        },
        {
            0x1B078B9DF527AB13ULL, 0xC1EAD3AA3CCFDB65ULL, 0x98C902B5DA7CE406ULL, 0xA8F573BFF45EB72BULL, 
            0xA56A5716FC396DEFULL, 0xA8C47A4137E9DD6FULL, 0xF73C1BE5335D57EAULL, 0x0EFE17AF43E60C18ULL, 
            0xFBE9BEE09F72488EULL, 0x6F6A6E5255F77421ULL, 0x2D88994611C71F06ULL, 0xE64F59372CED808AULL, 
            0x54036C8CE1CD34C2ULL, 0x11ABE00A65BD22BEULL, 0x999B65E5E92C9B38ULL, 0x7BE554761B0E1C37ULL, 
            0x84475D844A25D2ECULL, 0xFB47ACD8946E80D7ULL, 0xD44C7690E895F922ULL, 0xEF7B81BFB83DB901ULL, 
            0x46FBD67859427C89ULL, 0x77AA5272793E5417ULL, 0x92165B878462F21CULL, 0xE7623248E1B03798ULL, 
            0x7B829B92520E8C11ULL, 0x85F71C8E3D15447BULL, 0xC0F0EB8438F88EEAULL, 0xA32AD4406E79D5E6ULL, 
            0x17AC4F4B8D5ECAF5ULL, 0xF032F826FC370601ULL, 0xD895C196B08F478FULL, 0xFE15DC7AD2249F5EULL
        },
        {
            0x25FAD3742E41A186ULL, 0x7622417006D3CAEDULL, 0x1C859597C9CB879FULL, 0xB1F62A3750CFE4B6ULL, 
            0xCEA59A99D2796D92ULL, 0xF0D9AD64E254B4E2ULL, 0x8BAA5FE0F9E7B7DCULL, 0xB44D3E58F1A0BE44ULL, 
            0x6AB473DABDDF2DE7ULL, 0x9EE3F6E67A70BC0AULL, 0xF2F609B38ABA70FCULL, 0x2399ADD3F5C25F80ULL, 
            0x1C46641BB117B5A1ULL, 0x86FFB5673D861429ULL, 0xDF8D0124AEF5EE15ULL, 0x2C6D5C740584DBADULL, 
            0x3761E1FD3CBFF75BULL, 0xD5FAF35CBE0F4171ULL, 0xECE421C6DBDE9C8AULL, 0xC66E9047585A91DFULL, 
            0xE11462FE142A1AE7ULL, 0x19BC6F29C8B09712ULL, 0xAB57AF2B0F596DBFULL, 0xB83B72C3A91FA281ULL, 
            0xF20A4413CED94B93ULL, 0x2C08950CAB191781ULL, 0x4AD6FB352AE6F542ULL, 0x51F8CC8A75DE07C0ULL, 
            0x2139FB8F5836CFEDULL, 0xACE3A25A48B144E9ULL, 0x4D5AA6421C09C718ULL, 0x9DF75D9A8A94F778ULL
        },
        {
            0xCB8F1112FA0B3823ULL, 0x9F6F8AA0956451D7ULL, 0x21FEC959F4EC86E7ULL, 0x183B8753A18A39A3ULL, 
            0x7068DFA5EF20A29EULL, 0x4943000F4CC8B8BAULL, 0x40FDCE84F80F7A16ULL, 0x74E8052480C0F98BULL, 
            0xDDA89329E4167A2FULL, 0x44A021E25356E0A8ULL, 0x4089761EFA96CA68ULL, 0x49C9142B3B9DFF1BULL, 
            0x797E165877EEAF4BULL, 0x1646257A16BEE01FULL, 0x8E0F72139E626FD5ULL, 0x1CC8563C3695CE9CULL, 
            0x80231304A6FD0078ULL, 0xCA4981F80735FE24ULL, 0x59F1564463FACDD2ULL, 0x2DE170ED1456AE73ULL, 
            0x07C9EF4B49B0E771ULL, 0xFF2D32AC666E356DULL, 0xFA2A14AF162BB38CULL, 0x20F9521FC85BB487ULL, 
            0xF8884CF5CEB4CC29ULL, 0x12CF133D7F56CC85ULL, 0x8FD3E342D6E98E61ULL, 0x324AEAD209ABBB79ULL, 
            0xB980F289A605DD9FULL, 0xF73348040F174A7BULL, 0x69509A78986D371BULL, 0xEB3E63A67A063455ULL
        },
        {
            0xCD7299030416E28EULL, 0x595513475E227CAEULL, 0xBB24CCFD3607871DULL, 0xE4D033E4F402B2FDULL, 
            0xEDD69259BE41192EULL, 0xBFE741AC083779C1ULL, 0xCB1632539F1B5B30ULL, 0xFCB9CF573E0CE52DULL, 
            0x54289146645680D0ULL, 0xA854AD0FA7931F58ULL, 0xD2423865526655E2ULL, 0xEBE6208E4ED0E488ULL, 
            0x19F4B7F26BF39A98ULL, 0x1AD1171213C65105ULL, 0x9D05523E3B64D068ULL, 0xB374725F0C0E7D49ULL, 
            0xF92948D13E4808BCULL, 0x5A9C8414C8CD0C8EULL, 0xB37C8832DF767479ULL, 0x1CF729713A15468AULL, 
            0xEE0D75F1625BF1C3ULL, 0x99A6D6DF2F5D3E50ULL, 0x39068A12D49258B1ULL, 0x094849E3CB51E670ULL, 
            0xA19460A7D64652E5ULL, 0xD1CD7CFD4498C318ULL, 0x4A34B94E80BEBE7DULL, 0x39828F18237ECD74ULL, 
            0x19B7F2AABCD7D052ULL, 0xA1A29B3AE5A598C5ULL, 0x2EAE28FF8E4F697BULL, 0x2103372E5A7C6696ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseCConstants = {
    0x5B8AA507EC3C572CULL,
    0xD79318EBACBEA778ULL,
    0xABB8C0C6EBE30957ULL,
    0x5B8AA507EC3C572CULL,
    0xD79318EBACBEA778ULL,
    0xABB8C0C6EBE30957ULL,
    0x577648BB1566F996ULL,
    0x3A921E1BAC5749CAULL,
    0xCE,
    0xC5,
    0x59,
    0x4A,
    0x29,
    0x40,
    0x49,
    0x99
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseDSalts = {
    {
        {
            0xC3D20BF391C36046ULL, 0x686B251E09D0BAE2ULL, 0x5BF8A46F34567FC7ULL, 0x444547B4E4085CE2ULL, 
            0x76749D3BC112887BULL, 0x57EAE700E42FD882ULL, 0xB39C73D2C69287B3ULL, 0xA082B9550E1A74FBULL, 
            0x96953AEFBF010A7DULL, 0xFA18C59DD4A5C9BCULL, 0x0F1106CA28876945ULL, 0xA74267B23978A974ULL, 
            0x208442B5FB587CA8ULL, 0xF27592A55819BAABULL, 0xC8498EC75B7C4C07ULL, 0x0456A3378CF1C529ULL, 
            0x77C5464EF098F023ULL, 0xD93D16478C41AE2FULL, 0x57F80C186C4410E4ULL, 0xB534D3F8C26C7200ULL, 
            0x09C8AF14ABAB6A6DULL, 0xAC42F618231DA4DBULL, 0x303E69FF129771D5ULL, 0x54648DAD21C60D30ULL, 
            0x0E59CEF6B3CB42E2ULL, 0xE1EE5C34916AC079ULL, 0x8325C80ABD259707ULL, 0x817CC192C76B40EDULL, 
            0xA75F38FACE68D04BULL, 0xD24BB7BB0228A1F3ULL, 0xE5AFB3DFB7254AF2ULL, 0x6925C70D66335BF0ULL
        },
        {
            0xBA4637F5BF56E595ULL, 0x02A2A96C29D49FA2ULL, 0xEC21900E92B9EB85ULL, 0x31CEBBE8EF2EF82BULL, 
            0x3A5F799AF70140A0ULL, 0x5F887B729965290DULL, 0x161346EA7796F45EULL, 0xC4CEE456B61DDE41ULL, 
            0x97A072816A1635A9ULL, 0xD27FF319C6F89AB9ULL, 0xB20DCD6C58EDE9D0ULL, 0x5D6EF9FF66C244DCULL, 
            0x674AD4A67321306CULL, 0x986F40A0B0570959ULL, 0x569E43337067E4A3ULL, 0xBBC99BE5F6764A9AULL, 
            0x51678F21BF6B5ECCULL, 0x920CA44FF0F96154ULL, 0x14D6DC0100CDEE54ULL, 0x90CAF96CD0FD548AULL, 
            0x5FF31D47A7DED352ULL, 0xC94F1856A882BDF3ULL, 0x68C1FAE7D44F75C7ULL, 0xCBFBDF4665BAEFBCULL, 
            0xFFE2CECEA147B094ULL, 0xF4563F237C8CDCE4ULL, 0xB3169675AC06EDB5ULL, 0x5AD8551A1438386FULL, 
            0xFE20D69015C604CFULL, 0x215770EA10EF376FULL, 0x2945ECC883C7F2F0ULL, 0xE57A75C99F89E664ULL
        },
        {
            0x4A647D9D48D95B4FULL, 0xF7896A9F4C46E040ULL, 0xC7E76E4664EC202CULL, 0x91EC5CB76D98DF1DULL, 
            0xF551835AE725E55AULL, 0xBFB6713C688FB347ULL, 0xF763FFC49F5E813DULL, 0x754B60C88E6400D6ULL, 
            0x11609553E7A669ECULL, 0xA977104DDEBC3C1AULL, 0x67E8B86E47CE975EULL, 0x4F74643646CE6AC3ULL, 
            0xEDB43B51E980C8F0ULL, 0x0B9359CE618AE423ULL, 0xB6FF64591EF5AEB8ULL, 0x65374D1F96CFCDE1ULL, 
            0xC621596123341535ULL, 0x4556C2138BC91546ULL, 0xB8966B5C9B40A70BULL, 0x05EA0A4BB4187027ULL, 
            0x352C1684A25CC073ULL, 0x54FC35A74BE85CEAULL, 0xEBBEAAC1C7F202ABULL, 0xEA2FE774BFFF482AULL, 
            0x58885B29B58CCFF4ULL, 0xB6F2383B03349ABCULL, 0xDC314E0437D2E6C6ULL, 0x3FBF8C848DFA132CULL, 
            0x79AFC3EA94DB600DULL, 0x42B1613A769CD90EULL, 0x28BC73C8F4296A89ULL, 0x7DF9784AEA333F87ULL
        },
        {
            0x24F9996B71B2D965ULL, 0x5A04F59B60B96C55ULL, 0xD069619867205364ULL, 0x5CFA124A3483B3A9ULL, 
            0x8A9B74FD354AF64AULL, 0x27C82FC515B445E5ULL, 0x7AC65D6E15C87D4AULL, 0x8453E2A450233F67ULL, 
            0x368EAE4D43925E0AULL, 0x1594AD7856D18529ULL, 0xB32D666962624CE4ULL, 0x2E9305B21EA1D64AULL, 
            0xCE623356A519582EULL, 0x92163E6EFBF182CEULL, 0x67D6AEE4B4DBA4FBULL, 0x5827DBF1CACFD24CULL, 
            0xD01BB756AD090A5EULL, 0xE3EEA79FD0794315ULL, 0xDD5DA4D94F908BF5ULL, 0x15637FCC2FEEF27EULL, 
            0xAB0F6C59C2DE51B6ULL, 0xFE687640A49A2831ULL, 0x3289C9D187B7788BULL, 0x8B1C0C8F331062EBULL, 
            0xB1767A221CA762E0ULL, 0x89C12E76FB874A32ULL, 0xDB394342AA6BDCF8ULL, 0x28FE563F6251AE51ULL, 
            0x85D0F2C264008A22ULL, 0xF69DCC173B78C304ULL, 0xA922087BFAC3B02BULL, 0x21D99C36B80A0E6FULL
        },
        {
            0x27B8A6CA3FF12C54ULL, 0x17D745A962E17C75ULL, 0x120B2F89BCECDDF3ULL, 0x085BEA619CD87146ULL, 
            0xE1B2171D591857BFULL, 0xC58C43CC9B6776B7ULL, 0x4014CA696780F728ULL, 0x0C5E6439E828B908ULL, 
            0x8411267A85EBB3A0ULL, 0xF3DB288BF08916B5ULL, 0xD1733A77CBF327F6ULL, 0x882C2BCCFF7A4D25ULL, 
            0xE83E1C2FC7F536F1ULL, 0x113DB983337F2006ULL, 0xC9D25F2FDD0DADFCULL, 0x4A1B4C3E3645B4FFULL, 
            0xC78CF13F956A5844ULL, 0xF1561D642B6C33BFULL, 0x8FBA8AFAC3F628FDULL, 0x30272E5D88A413EEULL, 
            0xEF6469C9C37B7679ULL, 0xBB41F15EFB7AE789ULL, 0xF5C4CBAAEA7F68CCULL, 0x6362BF3656FE9D51ULL, 
            0x40A30188598D446AULL, 0xE0CF63165F977835ULL, 0xEBC1C921A8B23BA7ULL, 0x531525B85695720AULL, 
            0x0D7B577827D56BB6ULL, 0x3B59298E825A8E50ULL, 0x85A87A76EF8C972CULL, 0xFDA0F4E995580691ULL
        },
        {
            0x29D2E5C0CB5A7452ULL, 0x307016497159EBA1ULL, 0xE6EA3599AD920093ULL, 0x8604E10914CB5F84ULL, 
            0x0B3C6F36FC0646DFULL, 0x69987A0F34672EAAULL, 0xC622073E7435BA02ULL, 0xE1ECFE7621E89821ULL, 
            0x1EFDCD0898ED9B22ULL, 0x72CC50E482C4F956ULL, 0x07E2CA0E01FAD83DULL, 0xD6E2E75E95319263ULL, 
            0x20551721492EEA63ULL, 0xE4AF2D673B5A99E9ULL, 0xEB8467996868D537ULL, 0x94BA1ACDDD08BFC4ULL, 
            0x37FF3057EF24A322ULL, 0x9690A9669BB11E81ULL, 0x1167226372B2F1AAULL, 0x3CA90402F18BC36AULL, 
            0xD2ABA9507529F652ULL, 0x02410BDA554A4E3FULL, 0x21007181DF5F1479ULL, 0xF69E3AFEF7CAA8D2ULL, 
            0x51C29EA022730980ULL, 0x06E6C0FAE1B4131CULL, 0xE196D1537AF39A75ULL, 0x37854383C5748811ULL, 
            0xF86433E2BBBC76A2ULL, 0xC500C1877502FD2BULL, 0x7848831492ED98D9ULL, 0xCC61C8F7C19852EFULL
        }
    },
    {
        {
            0x5A426A5224942433ULL, 0x9B3989A2554B32F9ULL, 0x9793AD4841F3FCFFULL, 0x7599C7798222D881ULL, 
            0xA553E7DEDCF798D6ULL, 0x65C30AFED2E05F00ULL, 0xE07021E3443D172BULL, 0xC357DF6D6BF9FCF6ULL, 
            0xC104F37139536786ULL, 0x958C52C28B9D6298ULL, 0x920791E6DFD1525AULL, 0x5EA0DF26BF3A024DULL, 
            0x27CDCFAFBF29F0D4ULL, 0x4DE6020F6E73B746ULL, 0x8426331E4AC9D389ULL, 0xDBA7B3B9D490F379ULL, 
            0x1A61854F380C0B18ULL, 0x2A51AF23F5935D36ULL, 0x7308DBF5E02DB2FBULL, 0xB2BD48148907F7E1ULL, 
            0xDF4317E8EC41772AULL, 0xCBCCAB157C907280ULL, 0xDB7CEBC87DA653A3ULL, 0x63BB7C6F75807CF2ULL, 
            0xB412E90C31379EC6ULL, 0x1B7703335CBDF558ULL, 0x50A62E13455963F6ULL, 0x0749C12D9A4EC1A2ULL, 
            0x5F51F60A2A3EDC89ULL, 0x6BF9C1E110300540ULL, 0xC7BF18D00DC56974ULL, 0xA719BA92F35D34A6ULL
        },
        {
            0x207898BCF8C9AE27ULL, 0x6324AD70A0F028D8ULL, 0x434FEA100F946CA5ULL, 0x4EEC638C9974211DULL, 
            0xF6636AAD96812787ULL, 0x2FEABB0FA164C160ULL, 0xF834B2DAC1A0A967ULL, 0x65169DAF20420266ULL, 
            0xF25F60A0A90A7ABBULL, 0x1DFA61E5370D8B55ULL, 0xB69B5E57985C84CAULL, 0x01CB51743AA86B47ULL, 
            0x6B61CC1365D5535DULL, 0x480CB7608448973FULL, 0xCC6462B252FA776EULL, 0x5F9C84940E25026BULL, 
            0xBB511E81BEACCE2CULL, 0xDAF1AF61C47B5408ULL, 0xFEB2DBB4CF113DB2ULL, 0xFCBB8219EB42B8FEULL, 
            0x54455ED79AACE340ULL, 0x42A3BD7059CEF691ULL, 0xD420FD10C09C612FULL, 0xCF54A7E3ACBEFAA0ULL, 
            0x108E62E39DBAB1EFULL, 0x7AF8D8CA472FA506ULL, 0x74121BBAA1AFC61FULL, 0xC92D37C521CEF480ULL, 
            0x974615E4AFA1B862ULL, 0xA0FA187AB9B321ABULL, 0x1C2A1190F294DDADULL, 0xD1335DA029F05C4BULL
        },
        {
            0xC9A31A12C7C77FE3ULL, 0xAE57DDB8ACB29F5AULL, 0x7AAA09C6E3F0D21DULL, 0x5DD28C84E7B83E7EULL, 
            0x2015ECD67412EFCEULL, 0x584CF83D632B016FULL, 0xDA6770378B2310EFULL, 0x4A8854AE182EA00EULL, 
            0x964A504983E7F20FULL, 0x1A6CAAC37A174AB4ULL, 0xD4C524DA841F50FEULL, 0xCDF9006325B41CE8ULL, 
            0xE2B2917BB24651A0ULL, 0x5A8295E846D62E84ULL, 0x23EC77637A09C333ULL, 0xB10B70735930C85AULL, 
            0xA636B4ED06422DC3ULL, 0xD284C7727874E0BFULL, 0xAE7B5F64BD7B369EULL, 0xDD18F6024676AA50ULL, 
            0x08144630421346E4ULL, 0x78542DE9FCE0287BULL, 0x997164EF170B10E9ULL, 0xDF09453B93832395ULL, 
            0x7FF65191E3054950ULL, 0x3D693AB008850F4CULL, 0xBF1329C6E08A3F7FULL, 0xB84393F56336C770ULL, 
            0x097F8752D1F9AF4BULL, 0x20FF295B39B8F7CCULL, 0x9C7AA34EC992CE53ULL, 0xF4927E79F4632EBDULL
        },
        {
            0x2A787EF99934706AULL, 0x177D5754F679D457ULL, 0xF3C6B188518D1961ULL, 0x4CACDC04818EAD79ULL, 
            0x51D30309647AA616ULL, 0x6EEA8E61EDDEE18CULL, 0x56AA9BB538531F81ULL, 0x99243C3242A6A975ULL, 
            0x6025BF43C98123D6ULL, 0x8CBECD34478AFC5CULL, 0x5099EEBE474BF415ULL, 0xB8EA74008865E9E1ULL, 
            0xC80CB52B53DD7619ULL, 0x9D8ACD232E999C93ULL, 0x403103208BC7F8E6ULL, 0x2B32B84B8B8CB2BBULL, 
            0x31D566B8BCD84477ULL, 0xD49A81BEE7A66692ULL, 0xCADCB25669FCA7B7ULL, 0x4A510288B19C8A98ULL, 
            0x5501806C1DD7457DULL, 0xF5EB8E93729BABC2ULL, 0x4275CE4E14A0080DULL, 0x09EC8EF67B62EF6EULL, 
            0x10AB89537AA9AA89ULL, 0x62B7CD79E84A5A73ULL, 0xAD98CCBF5CDA1C7BULL, 0x3F64760628CC2C28ULL, 
            0xDC950E155A358332ULL, 0x90BB96779CB8A88CULL, 0x731853426DCBABD8ULL, 0xE072DCD914E09970ULL
        },
        {
            0xAFFA510C24573ACAULL, 0xB939442B2734C4DAULL, 0x48F8143FECFB541AULL, 0x4D887BF2F80580ABULL, 
            0x727719AE95CEBCBAULL, 0x78716757F14F9E19ULL, 0x247DFEF78E00B44FULL, 0xE1966AA3ACDED5FFULL, 
            0xCFE96EAD8D2810D5ULL, 0xFDB3373DBE40B58FULL, 0x599B4E2BBEA500B5ULL, 0x1A4768D1E8A61143ULL, 
            0x03E023DB31B55DF3ULL, 0x9055D70F1C51D73CULL, 0xBBCDB810A25EC572ULL, 0xD5A6FA282B0C63B3ULL, 
            0x337523F3DF5D215EULL, 0xA258ADD808C93EE2ULL, 0xC4E1E5F8CDCF0229ULL, 0x7737B71DAE65D3CBULL, 
            0x435E4269AA74078DULL, 0x57E6E002F4A021C4ULL, 0x0A7F7F62BF72CE3AULL, 0x77C0CD845ECC58C8ULL, 
            0x65A406D4EBEF213CULL, 0x97A18DB3BF0DFD04ULL, 0xEF7732076866C9B7ULL, 0x668883B60D57BB06ULL, 
            0x990520436D55BAD3ULL, 0x2D05233C48EDC07CULL, 0xE79AC5946126CEC9ULL, 0x015ED8F88B178963ULL
        },
        {
            0x4A566700EA412116ULL, 0xA369B8C0AE310CF7ULL, 0xF3259BDBB07616EFULL, 0xF843D551B652834CULL, 
            0x266708B7758FA4B3ULL, 0x826161C0F3F45DABULL, 0x7481A1249DED3978ULL, 0x08D2041093694E02ULL, 
            0xCA4268FC193F2BFEULL, 0x31BFEC44AA9DBF46ULL, 0xA65B5E3B4ABDCAA0ULL, 0x839C1954072C3E72ULL, 
            0x1885D4FB40233893ULL, 0x38FEF8B75030DE7FULL, 0xF3784C8B4C1D2109ULL, 0xA8A226A74B5D3979ULL, 
            0xA98FA67091573AE2ULL, 0x1787434BE53CD17AULL, 0xF2E2EE9692CEC162ULL, 0xDEC9684F6F7CB1D3ULL, 
            0x790C1A6BCB1137ABULL, 0x87DA01D4DCF334C4ULL, 0x450E729F2BF8F7C4ULL, 0xFD4C9DB4EEDE8237ULL, 
            0xA19817F6F1E8C1F8ULL, 0x67D533EC6C40B082ULL, 0x69108724F88D5BC0ULL, 0xF75468837FF7F7B1ULL, 
            0x3CE9F562C6F6A8C5ULL, 0xBA477754E0187032ULL, 0xD0279627045CA254ULL, 0xD844E2742E2AFBCBULL
        }
    },
    {
        {
            0x292D679DE4BE1E8BULL, 0x783DE27AB038BD0CULL, 0x84F9D3225AA078E3ULL, 0xBCED2C75FFD0A06CULL, 
            0xDDA7F64BFCAAFF93ULL, 0x57FFF5B729A98E48ULL, 0x08439DC6B375313FULL, 0x16719C774C2163A0ULL, 
            0xDD4A5527200FC946ULL, 0xD57431B0BAAC5068ULL, 0xF824229F4F4A62E6ULL, 0xF0AF9D2BC0EBC9F9ULL, 
            0xE6DD57F0FEFEB95EULL, 0xA3949ADC30EE20C7ULL, 0x0D0F5FE297A1AFB9ULL, 0x23F502270EDCFC4EULL, 
            0x560BFF08A25B6B95ULL, 0x246F159520E7E615ULL, 0x272E8969080C4905ULL, 0x58633D7D4C8AAD00ULL, 
            0xCC5208A2D30BCC36ULL, 0xD73AE20FAC528721ULL, 0x583AEE43C0A67F6CULL, 0x9A4C5ADF98EE0528ULL, 
            0xBBE46759AD3C3B79ULL, 0x3C77C400C285FC60ULL, 0xFE1F9E7852B98159ULL, 0xD2CCC401225F510AULL, 
            0x720BFBEDD9C014CBULL, 0x3E413054CC5568E8ULL, 0x237A81FB028576DAULL, 0x4A2D9104443F008DULL
        },
        {
            0x8D49669FC06E763CULL, 0x37B7B591E16D9472ULL, 0xA2CE38DA26A5A214ULL, 0xDBE1C6F1A20FA5E4ULL, 
            0x9CA291A4875B150EULL, 0x5C6AB3FD216FDF8CULL, 0x919D19EA46F11D0FULL, 0xF0C398BA438EC81CULL, 
            0xAE9975ECA7ADC733ULL, 0xE9FF1C5EAE89AB2BULL, 0x29A414C5163F67B5ULL, 0x851413EEC067B33EULL, 
            0xE4FD1DB63FD7CEFBULL, 0xC6917F8A4DC8B862ULL, 0x7188F81368628794ULL, 0x4E24F843EEE2E2ECULL, 
            0xB064AD3109EA487FULL, 0x829B5BEE8BE4ACDAULL, 0x0DD6D89EA95C715AULL, 0x474F2152F82E882DULL, 
            0x10B87D6932AB4822ULL, 0x464C198DD6510330ULL, 0xB1FD632AE8869A04ULL, 0x554106BEA8812F2CULL, 
            0x929650A7277F4970ULL, 0x24CB2040D27C02FCULL, 0x689C0BF97C1E0023ULL, 0x93BA32E023B2654BULL, 
            0x84A5D6598A0FEA39ULL, 0x60DCB1CEB335E3DAULL, 0x2CB15BBE772F92E9ULL, 0xA7C83E9760059158ULL
        },
        {
            0x3357D37EB28BC494ULL, 0xD4EDCA783E08C642ULL, 0x2AC3DE185288D242ULL, 0x5C6D30D04D31F627ULL, 
            0x17B8FEDA91B8DB27ULL, 0x10E8C6CF4A0EBABEULL, 0x75C6E26330CF0AA0ULL, 0x55CBB3F8A6D06B5BULL, 
            0x5EDB3BDE753AB96EULL, 0xD13A6BFBE998BE6EULL, 0x27E5482ED8E71774ULL, 0xE9FD157751431E97ULL, 
            0xF70C4F8A7B6A4636ULL, 0x12034328826DE63BULL, 0xD542D3A7E0D03BBFULL, 0x472C50277C6F4516ULL, 
            0xA635542C79A26B32ULL, 0x52BDFA99DF4CCBADULL, 0x0B30CF83D5E2D625ULL, 0xF9EE22FB496EA851ULL, 
            0x5D32FF7EDE0E27CEULL, 0xD7D559A0FA3B36EEULL, 0xC7EEE5555BF1763FULL, 0xA987CDDE6B54E6A0ULL, 
            0x57FF04C834525F5BULL, 0xAD53BB9FA1DFDCE0ULL, 0x1B09A1142BC8767EULL, 0xE7630F313D562991ULL, 
            0x855A33E65661EA64ULL, 0x09A95C758521E162ULL, 0xDFBAFC8B00F92CB5ULL, 0x3FE6949A8453CB50ULL
        },
        {
            0x1FE914BE4751ECE5ULL, 0x26D09CEE82550DF8ULL, 0x243D6DCAB74BA149ULL, 0x2BA639515A7A5DFAULL, 
            0x24C55D3AAC798A9CULL, 0x53EE1A9C6B4378B4ULL, 0xA630E9A5F15691ECULL, 0x5772C3F2D5140CA8ULL, 
            0x4A35D5581120BB3EULL, 0x877AF52D4FEC0BA1ULL, 0x281A2B0DB72D8C54ULL, 0x588DB6536C270B15ULL, 
            0x399FF3909C32CED3ULL, 0x3E6925E159B064EEULL, 0x2B3487F16592E772ULL, 0x019A09CAC70C3C09ULL, 
            0x5EEC247B8A276FAEULL, 0x8E1357F0F33CFB67ULL, 0x03128014E25E3BD1ULL, 0x35E08460B2B726EBULL, 
            0x6C42191F19888F77ULL, 0x0E7C8131DEB84B18ULL, 0x6CFEE78BE1602E72ULL, 0x5180C51B45E0139BULL, 
            0x45CF481AAC428AD9ULL, 0xAD919E51D5F207A7ULL, 0xEF18F8B5F89C3920ULL, 0xEF68A8068A6CDE82ULL, 
            0xB2ECA57A6B12848FULL, 0xDE94F8F57B8E45F7ULL, 0x60F7202D1CE969D2ULL, 0xB2C0F5F8B2FD45E1ULL
        },
        {
            0x11FA3A532AF894DEULL, 0x1CB6C3014A19EB0CULL, 0x95AD733D10A392D3ULL, 0xB7942149A1633088ULL, 
            0x106938B2F0157A83ULL, 0x027CBBF54CD30BF6ULL, 0x3E53D2F402D05B85ULL, 0x9372F53B1E2BFF95ULL, 
            0x50DBF76FD5BDBA99ULL, 0x2C0AC08380DA2A54ULL, 0xC317FC587EE99CA7ULL, 0xE9D1C3D0498E693FULL, 
            0xC1F6B38C100949B5ULL, 0xD286EFBED1E5CE13ULL, 0x5DCE9C0E4F67D09EULL, 0x515198C14742849FULL, 
            0x630FB272522BC2DBULL, 0xEC5806A461E5061EULL, 0x96BFCD066FBC83DDULL, 0x728AA9E937AEB535ULL, 
            0x13D4CA3BD0DBD621ULL, 0x538E31021F934E91ULL, 0xC21F2E13A7B11F05ULL, 0xE9D4178F8BC9E4EAULL, 
            0xF003D465A264F6B7ULL, 0x42C58E754428F84BULL, 0xF5ACF7552C7069F1ULL, 0x2CB8412C62968041ULL, 
            0xDC467708779316A8ULL, 0xCBE37CD31CEC8D8BULL, 0x4FA777B7CADAC59EULL, 0x84CB0B0B6F08535FULL
        },
        {
            0x75A0FCB4AE33C43CULL, 0xE92609DD76AFC5DCULL, 0xBD49AC75F3D91C7BULL, 0x8E69F7B90FFB371CULL, 
            0x65F6A4718C1FF39EULL, 0x902B516E466605E2ULL, 0xC0DAA04D9A4F6027ULL, 0xFFEF0063CD6B853BULL, 
            0xC25CF26A057EB93DULL, 0xEDBAE161CF76BF6BULL, 0xEF2DF7355DF0715CULL, 0xF7D31B1854D94F27ULL, 
            0x43A51DC50260234EULL, 0xFDCC41B723ECBBDDULL, 0x68442BD7484800F9ULL, 0x47EA5425490CE822ULL, 
            0xB83796C0C2463A63ULL, 0x20CCCA3B782FA6E2ULL, 0x4913998E092560F5ULL, 0x097D458D89100400ULL, 
            0xDF8E461E57D1049BULL, 0x87F0885E366B065CULL, 0xDA53868F747B0222ULL, 0xF9D9451DBF414C22ULL, 
            0x3FF9EE7CA209E6BDULL, 0xAFA57D73CCF65B69ULL, 0x74A528AF3DE7724BULL, 0x9651A7090AB91FDAULL, 
            0xD5482A2A2E90300FULL, 0x146AF0EC589C74D5ULL, 0xD30743B54A2CCF9FULL, 0x329CC314890CD3E4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseDConstants = {
    0x3C21EA7CB318B48AULL,
    0xDF7C2F35DD59AA07ULL,
    0x0673646EC63B1F37ULL,
    0x3C21EA7CB318B48AULL,
    0xDF7C2F35DD59AA07ULL,
    0x0673646EC63B1F37ULL,
    0x3E1081AA0E89BCADULL,
    0x1AF7BADD64FB14F4ULL,
    0x9A,
    0xA4,
    0x9A,
    0x76,
    0x51,
    0x37,
    0xA8,
    0x11
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseESalts = {
    {
        {
            0x0210CF9AAC695FEDULL, 0xFCA60BAA29045198ULL, 0x48CC55EC1A3D23E9ULL, 0xC8C9A2DBEED907DFULL, 
            0xE20BAAE73D4B972AULL, 0x9B3EF9D36C122EE4ULL, 0x67CA99637B93E3A0ULL, 0x1229C9C9DF7A0838ULL, 
            0xCB32507E7B679957ULL, 0xAA9314BBF18823EDULL, 0x42710159DD4E0A17ULL, 0x90F75201652DB079ULL, 
            0xBF88A9595955157FULL, 0x25594145BBD69623ULL, 0x765EA8E8675C8A83ULL, 0xF0BB8EB49D541DDCULL, 
            0xF40114F891F3F2AAULL, 0xC69B939E189056F8ULL, 0x3A134D6626E84B3EULL, 0xB7B5B2C56F8D411FULL, 
            0x72C127274FD07E7AULL, 0x75C9F5629EA0B904ULL, 0x9FE1345FF61D9470ULL, 0x4931E0E76541E546ULL, 
            0x4CB0BF2076C9C65AULL, 0x1E0BAEDF01495E2AULL, 0x84D1366DC84017D8ULL, 0x5D61E93C4291920FULL, 
            0xDF306B5B24EC6A9DULL, 0x619FB0E4B7830A14ULL, 0x3AAC7E310AE183A1ULL, 0xCC89422C2D0C6F9AULL
        },
        {
            0xA3FB047F7D0B5342ULL, 0x0C414EE856910E91ULL, 0x6C9410AB7736B933ULL, 0x8525215707D4F742ULL, 
            0xD6E215F778D3E0DDULL, 0xBC1F79E5E617C84FULL, 0xA9931C1724D66B7AULL, 0x2A28AB2633D02B42ULL, 
            0xBB5672D820F8BF0EULL, 0x7C3E41C410F5B674ULL, 0xF55D918B15AC40F3ULL, 0xC3003077DA672292ULL, 
            0x708C957B853DCE9BULL, 0xB8E3E4E11E2B4D90ULL, 0x17D47B3B53E35B43ULL, 0xD0D83863A7C5B852ULL, 
            0xAD386F3081526EA1ULL, 0x19D393D01DD5D861ULL, 0xA59FD4827C291650ULL, 0xE7A66FAF8A6621E1ULL, 
            0x258506AA5F42A771ULL, 0xA0C97FF2D7BEEFB3ULL, 0xDAB4EFD32191D9F8ULL, 0x68735060F69BEED8ULL, 
            0x775B2F2D224A42D9ULL, 0x3219044CF315F19DULL, 0x43C8FEEE50620843ULL, 0x7F8EAD0DBBB916E0ULL, 
            0x6F60CD5D8929361FULL, 0x6009DB964072A8DEULL, 0xDFB008188E03031AULL, 0x9DADA6568FAEE295ULL
        },
        {
            0x5C10D3FC04DD2D29ULL, 0x6194F8A4A24ABBEAULL, 0x3713B64D18E07695ULL, 0x2D8095ACC142D62AULL, 
            0x3633A610E282C125ULL, 0xAD1562BEBEF809CAULL, 0x7F4B49406CEA460AULL, 0x8B43627A99B9F27DULL, 
            0xED7862FB61FD2172ULL, 0x7EC62D472E9D50A8ULL, 0x488A5723DFA6DF88ULL, 0xA9C42F69653597F4ULL, 
            0xEC52C39907473ED6ULL, 0x7AEB60E5BEB66E82ULL, 0xAF68ED96E1A75750ULL, 0x917196B704946002ULL, 
            0x1D487D957DE18A27ULL, 0x849350B9A3B7865BULL, 0xA5CB9F874C8BD64AULL, 0x1F6FD94127831655ULL, 
            0xC54E43FDD102EEEAULL, 0xB40566FD9ADA3E3DULL, 0x66E1AC702FF94260ULL, 0xE8B40628F27FE006ULL, 
            0x5584771E499CA7A1ULL, 0xE4E8963FBD6BF6F6ULL, 0x1C914EA4EEDF49FAULL, 0x137FB57B649A5AB6ULL, 
            0x5BB38B985A4B5A14ULL, 0x817723457A5D5997ULL, 0x69A189025F8113E0ULL, 0xE6808104416C22C1ULL
        },
        {
            0xEAE8349B119C63CCULL, 0x5CAE24AA1BC52AD7ULL, 0x1AD78FD48FDA5D88ULL, 0xEF865140BD76794CULL, 
            0x48EE73BA06541958ULL, 0x4CFE8825B1D421AFULL, 0xE029D222AD3F8B2FULL, 0x5AC7DF4CDF41BEFDULL, 
            0xFABBB86649505EE3ULL, 0x8B2CE0FFF752438FULL, 0x2705DE9682499E96ULL, 0x3ADBD4EFA42248D4ULL, 
            0x12D83F81A2902428ULL, 0x61E1191324436CECULL, 0x540E5C4147DD6F7AULL, 0x6EF58547708215C0ULL, 
            0xF460D2EDD27B52E5ULL, 0xFB361AE9822E54ECULL, 0x4D7E1F5FA69218D4ULL, 0x90D1C75D045F5C39ULL, 
            0xEFDC0552D5D37570ULL, 0x817395047C7364B1ULL, 0x18FB140E06056112ULL, 0x165B57EA6780BE47ULL, 
            0x68240E7C157A8CCDULL, 0xB8301532C43F27D5ULL, 0xD65E7EAE1BC0EE86ULL, 0x9DAED5FDCC8A2650ULL, 
            0x2918F31B86214D87ULL, 0xFE8B6450D69058FFULL, 0x211AA5AD64D09034ULL, 0x0F13D969CB8AADC0ULL
        },
        {
            0x44F2BCE90982DD5CULL, 0x40AE12564AA39FE5ULL, 0x47E39B9374B62131ULL, 0x6EC7B11DEE33C7CDULL, 
            0xD99857FBFFCEBBDAULL, 0xC69DD9708156CF7CULL, 0x6B955851CC94A4C4ULL, 0x7D4574A1B3B4E43FULL, 
            0xD43CD9281232179DULL, 0x3D9A1ECFF5703761ULL, 0x9041F8823727E7F0ULL, 0x498A1E490A572393ULL, 
            0x3AFC09C8856D777BULL, 0x090E7F2CA1788831ULL, 0xF21CBF0CA3BAC0ACULL, 0x144BE094345501BEULL, 
            0x721CAD6F4AB7439CULL, 0x16D40478D77603A9ULL, 0xE2559B4FCAC73667ULL, 0x70FF9A81AA6E5D19ULL, 
            0x4B0A1507C9B06B37ULL, 0xBA32A0089086BB7BULL, 0xA513CC5C7FAA376FULL, 0x34A1DD44E36D9C1DULL, 
            0x6F9EA9D0D61CD3EDULL, 0xA0E28EFBDC5A0728ULL, 0x50E18B495D9E7BD2ULL, 0x739D8363033878B3ULL, 
            0x7B5A03164E87114DULL, 0x70E31B6FC8AB5CB3ULL, 0x0BF11C496208B4C5ULL, 0x074D7BA9A0623ADAULL
        },
        {
            0x84E618EE0666B4F7ULL, 0xA4CE9523B8BA52B2ULL, 0x45B7F78D94998D57ULL, 0x83C4F9F5363665D3ULL, 
            0x7123C15A6C3CB7B6ULL, 0x00DCA3EDB04F48F8ULL, 0x3FC64D64E98DB192ULL, 0x991ABA0709CA5EC5ULL, 
            0x14D24AA2BDB8F495ULL, 0x29B597F2168D8F7AULL, 0xDCBF10EFB3ECB338ULL, 0xCA82A1DD007D1746ULL, 
            0xFEB82871C6C5DB59ULL, 0x2B96630216C2AB0FULL, 0xB82D5E6DE697F853ULL, 0x7F8EB3941DEEDB85ULL, 
            0x916702F3845B1FCCULL, 0x4499C68ECD649AC6ULL, 0x7ACAFFFB2B7B8B52ULL, 0xE697B4395CC3B4C2ULL, 
            0x4787605BE6BAF51DULL, 0xEE8A5095B63B36BBULL, 0x545DBB4BD5617CB7ULL, 0x616990519F009B76ULL, 
            0xFEBFB5887B8466E1ULL, 0x14043ECBA1489D33ULL, 0xB51B286DDE0EFE05ULL, 0x6FAFE256FC97C336ULL, 
            0x22730C2C5DFCC3F7ULL, 0x99FBE32D85E6BFF2ULL, 0xCC5D480FC3F74F10ULL, 0x328D514A9754FFFEULL
        }
    },
    {
        {
            0xF6F14F9F7064A412ULL, 0x15F807CC58AC2F6BULL, 0xA96F40E6F58C6E17ULL, 0x27B34BA34145DB86ULL, 
            0x5588C903ED55397BULL, 0xB3B0EA8C7920A780ULL, 0x51462EFF5D641137ULL, 0xEADAF33F18347240ULL, 
            0x3E9624270663D376ULL, 0x8D11C8AE44C78359ULL, 0x44612D005E78FEB1ULL, 0xA940BEBE92E53D0DULL, 
            0x543D86D60B7C16E6ULL, 0xC7D37F564C2AC83DULL, 0xF95FD59DE386D5E0ULL, 0x12BF98EF56A9CBD6ULL, 
            0x4E594C8EC61CCB40ULL, 0xDAE6D48667CD9BA7ULL, 0x6315E0A1A04E238FULL, 0xC1E343C57D265EE8ULL, 
            0xA7BD60EF9D85333EULL, 0x2D85BEB1983DE972ULL, 0x50F0B45B2A64DDF2ULL, 0x57E3BC52AACD6B60ULL, 
            0xECA302B30290CCE5ULL, 0x98CF0C4199D359DEULL, 0xF9A3DFCF20994B2EULL, 0x84A708B5D6024ECAULL, 
            0x6420311A79513035ULL, 0xD1D98E2EBB7E92B5ULL, 0xF8EF2D3C8762FC84ULL, 0x118CA88D46F5CB99ULL
        },
        {
            0x094D334EEC9E7196ULL, 0x68A0CDF2E133E886ULL, 0x3B510565DB4028F1ULL, 0x34886546EE8B527FULL, 
            0xDFE2836B27655B58ULL, 0xC458AA80E53BBF47ULL, 0x3A580181EDFC4FD7ULL, 0xB83C181FE7F4E709ULL, 
            0x167754D28E75F1BBULL, 0x6C07E3FCE57E87F3ULL, 0xAB3DC700F77DA69DULL, 0x59C5148B34495D6FULL, 
            0x07C73BB36519FBEEULL, 0x5500C69376F42859ULL, 0x95D15B90FA3280C9ULL, 0x1D11BF1DC9D44B8FULL, 
            0x8DA8FA6DF57FDEDFULL, 0xFA9D673501E35688ULL, 0x612125F007997604ULL, 0xDB9575F597AF1ED1ULL, 
            0x051B4C732EFC3F7CULL, 0xDCF1175F2A7E4282ULL, 0x5FDC232F5012A779ULL, 0xEEB23697A3A80391ULL, 
            0x8760AEFE718088D6ULL, 0xA0ECA1C31345B63EULL, 0x5F2878AC615D024CULL, 0x82135B2613005B72ULL, 
            0xF874ABBD3A207DADULL, 0x175B6F71AC17BB03ULL, 0x57CE783D622F3F7DULL, 0xA3683A57AFEEA3F5ULL
        },
        {
            0xE615BF757B7C864AULL, 0xFEBF5E3AFAED48DEULL, 0x100989478E06FF55ULL, 0x23A54E24D755493FULL, 
            0xAA6DBC3048A8C5ECULL, 0x408205C2A1236E0AULL, 0x1795C0FF8030787FULL, 0xC0BDFA493A280CE9ULL, 
            0xD140DA103E127F77ULL, 0xD843E0BB01AECAEBULL, 0xFA376212562D3457ULL, 0x958E36144BD23A6CULL, 
            0x0F377E57F88F1242ULL, 0xC358DF1C35A62A4DULL, 0x18A5769A5E255BFFULL, 0x1EF6C693007E36EDULL, 
            0xE4AD4DE43347FE87ULL, 0xDD0675DD59D085C1ULL, 0x72F0D77C2BAFA681ULL, 0x5D84E0DEE4297EE1ULL, 
            0xDBEF497A7906B29EULL, 0x557E4F54EBC67F21ULL, 0x5075258FCC2A9C9CULL, 0x79675A6A91C1D23AULL, 
            0x09DE74A0822C5AC1ULL, 0xC6EE309F52F4A1AAULL, 0xBDF1F205047AAB8DULL, 0x64E2ED753175393AULL, 
            0x0F385D4184F9F9F3ULL, 0xF7827055CD6C3F7CULL, 0x24121D46C5B8CFF1ULL, 0x7C0D8D5461CB9ED8ULL
        },
        {
            0x0F13D1E52742AB8CULL, 0xA0BE548F3207DA4CULL, 0xED379147435E2977ULL, 0xCB8239061A81C3C3ULL, 
            0xFB81E15385D04BB0ULL, 0xB1F5DE3DA005A88AULL, 0x02B1E5A06DAC9E1FULL, 0x7C62179C1A65EEE9ULL, 
            0x23E29BEB65628D0BULL, 0x490EEDD20E3DB802ULL, 0x521C9B5761039F2AULL, 0x00E890AE331CB045ULL, 
            0x728617567547EBABULL, 0x5392F28D6CB22B84ULL, 0x3DB0C957BDE04DFFULL, 0x5FA2B33713B3DCA6ULL, 
            0xA553A268CBDF8DD6ULL, 0xF539856E62FB46AFULL, 0x2329C430E1ABE8EBULL, 0xE40FBE3E539B3F4EULL, 
            0x8139A7E7CC6FF7C8ULL, 0xD78027C8C45B529DULL, 0x8074C60A6E90C83CULL, 0x800B98B384B5ACE0ULL, 
            0x000638C434640821ULL, 0xBC422E6F36429C55ULL, 0xB2A00A2B9B1D4086ULL, 0x89B62E57758B2964ULL, 
            0x3C837412D733AD9EULL, 0xA622B3F88EA3CDE7ULL, 0x088FE62128279652ULL, 0xA48F03C814DF9B28ULL
        },
        {
            0x13E95349F53FFBABULL, 0x91C3299EE7508802ULL, 0x2A9C502F68455019ULL, 0x5DDD7024D0DB9837ULL, 
            0x175CE84E8E267152ULL, 0xF65EA1CF7FD9D12FULL, 0xCD496D92CDDC2062ULL, 0xDF38FC57C9B5B5FAULL, 
            0xA6557CE7E9F0CE04ULL, 0x2ECE507892C59D46ULL, 0xBB160ED0841D0996ULL, 0x384705AEC66D6807ULL, 
            0x45F6554114513709ULL, 0x849D48B07D92506CULL, 0x12F16D4A43CB9726ULL, 0x10AB793A836C7B56ULL, 
            0x6F4C6DE205C784E9ULL, 0xF6A874FB4F6D63EFULL, 0xE96FFEE2A501C85CULL, 0x91D1EABA49534372ULL, 
            0x7D0FDB4499F084ABULL, 0xD85304F843BB4033ULL, 0x517FAEC0974D1333ULL, 0xDABBD3D595212397ULL, 
            0x09B42E1ACC4D4533ULL, 0x014D520B63879415ULL, 0x52B99CD5BD610A76ULL, 0xEE32DCCAF8637DA8ULL, 
            0xC10BAB7E34BB378FULL, 0xAD99DA3E1B717F24ULL, 0x16C8B50012F2E8E2ULL, 0xAFC7250B9AD498F6ULL
        },
        {
            0xD08E49A405FEB273ULL, 0x56170F83F9CAB3C3ULL, 0xD1459A92271D95F4ULL, 0x0E4B66E96AA16B34ULL, 
            0x82E8476805FF2C42ULL, 0xB977169DFE29069DULL, 0x4456AE0C422BD3D3ULL, 0x9E8B47378F4282C9ULL, 
            0xD237763DE86A0F67ULL, 0xB06279A2117114FBULL, 0x8F10C16377E0CD3BULL, 0x5568C97384CF7C86ULL, 
            0xDC2BB2DF9B2EAF6DULL, 0xB17356B461E8569CULL, 0x3B4F48BCA4A44E69ULL, 0xDC4CE44CF5E86D53ULL, 
            0xEE9F2E066D2A052CULL, 0xB0CEC5130A73F147ULL, 0x9ED52CA53389EDD0ULL, 0x74B4B37DBD2F1D8BULL, 
            0xCBD55E48997BBFD9ULL, 0xE4C3E56511E077A9ULL, 0xBA685049F2C37B15ULL, 0x112E9C10CEB834EFULL, 
            0x5B1E1851B27A0D4BULL, 0x46C0FAD534830ECCULL, 0x0F2E2646EBF18AF1ULL, 0xE4EFDE3473D5BD05ULL, 
            0xA9F96FB1B1D8D8D8ULL, 0x9F65E85E03A4624CULL, 0x4B6FF668A6423581ULL, 0xAC5C050F9BB661E8ULL
        }
    },
    {
        {
            0xCCA638DE80B2BB0BULL, 0xDC962BF0E9854CE0ULL, 0xD8124DFC7853DE92ULL, 0x5B0B742ED1DABFB0ULL, 
            0x1BB36CEA830794C5ULL, 0x1637D5C0CF15B530ULL, 0x07B30D382F86E40FULL, 0x67D91D4737EC847EULL, 
            0x45C718170500B5ADULL, 0x635F882EC3C731A6ULL, 0x16F8E256765CE010ULL, 0x0F160633EFC8F353ULL, 
            0x819E1AD8B842870EULL, 0xB52EB2B3EEC7FDCEULL, 0x7A838C586ADC79DCULL, 0x29A8D642B32D15ECULL, 
            0x398D157CFF9C4705ULL, 0x6BD9763773B9FEE0ULL, 0xCDF5252F8FDA5B2BULL, 0x4BF4D31A40B618BDULL, 
            0xFF976F4DD38BEC9DULL, 0x7E018621D3DD48DCULL, 0x60419F439629A791ULL, 0xC287B1CC6030F32AULL, 
            0x659EAF06007D3E5DULL, 0xB5ED4EB251404D40ULL, 0xD8EB0EA9975CA805ULL, 0xB9B83F49630C46F5ULL, 
            0xB6F6EEC3B7DA276BULL, 0x09C5E46CC402C049ULL, 0x394C29823B23D22EULL, 0xAE3186D804026115ULL
        },
        {
            0x7AD68BF2A151E860ULL, 0xE232FFB3BFC577BEULL, 0xD52276A3BCBDD10FULL, 0x3B693A6A9515698EULL, 
            0x52A72F364789012EULL, 0xCFA9E24A92135BA6ULL, 0x38D2A965ED3A1C6BULL, 0xD2D10C4D8AFA6E9BULL, 
            0x687FC496B8EC2F0BULL, 0x8B9AE18DFA246F68ULL, 0x559F3A504C9E0A9EULL, 0xFB731E15ABF1ED26ULL, 
            0xA558288B8C6189C7ULL, 0x1A65EA81806A0539ULL, 0x08BF428EA1B75075ULL, 0x6585F460E6B5643FULL, 
            0x603013954AA68A52ULL, 0x831EA5B8E6D235F7ULL, 0x87E1083119B4A977ULL, 0xC000E02C10E8BF3FULL, 
            0xB26DA68039F67528ULL, 0x537635A680FA62F7ULL, 0xFFEF4197FF6FE843ULL, 0x7E275594CCC2BD7DULL, 
            0x8E791BB042C74DD4ULL, 0xC556AE3413142EACULL, 0x65072894301DDA1CULL, 0xCA98CE8007486C42ULL, 
            0xAA51A76BB32149CCULL, 0x310425DDE5CCC087ULL, 0x12B34D1FE692AB28ULL, 0xE71A0758CD94DDF6ULL
        },
        {
            0x0240BEEA49F90D8BULL, 0xA9CD1B79151BBC14ULL, 0x1DB103349A898F21ULL, 0x6E9E4D8C7C747910ULL, 
            0x3D68645B90A2E750ULL, 0xBBC4B795CC075662ULL, 0x2A5643239F27DC70ULL, 0x61B977853EE402E9ULL, 
            0xBD43854EBF00B0AFULL, 0x835C4F6A55749024ULL, 0x24A0AC79F9FD09A9ULL, 0x1B1724E299E0633DULL, 
            0xD7B6185FFD7449E0ULL, 0x3BE88A797645ADFCULL, 0xB8964104B8E9CB00ULL, 0xF1303034C174650FULL, 
            0x3380D14570F5F309ULL, 0x45FE2182D0AC9691ULL, 0x2C4C6786299B5648ULL, 0x4E96A3182FFE3DA4ULL, 
            0x87DE1F4D098E268AULL, 0x8E6FD7594721DD71ULL, 0x7C03B8011E14E531ULL, 0x60932CF3B6D8FE8FULL, 
            0xDE32970B2C8938D8ULL, 0xDD5450FC14F186E2ULL, 0x16839EC90C1487DEULL, 0x39756CDA968EBBDCULL, 
            0x0A1A71599AC77515ULL, 0xAC5582CAE3A573DAULL, 0x0E3AC98CB7616DA2ULL, 0xC8B855D4DA755DCAULL
        },
        {
            0x03C5C9B63427A03DULL, 0x7896835F44A78CA6ULL, 0x7A6565CA10ACDFFCULL, 0x84AB297F482D1F7DULL, 
            0x65C45B37768E8D91ULL, 0x4D7962246102ECC3ULL, 0x6A521278238A3F5EULL, 0x9CF673396C1F659DULL, 
            0x4D2E5AFA2C531ECCULL, 0x0F00244B0759AAEBULL, 0xA3DFD37DF0C26F36ULL, 0x7F5F1A9A5A0877D5ULL, 
            0x1CF2B7CD46EFFE99ULL, 0x7C1C4B37F1E122A5ULL, 0x3675B2E504A93C06ULL, 0xEBA7B15DC19F9DDDULL, 
            0x6B54FA71FC21D190ULL, 0x393A499FF64D537BULL, 0xF49563EFF9BF266CULL, 0x15630E761DAB49A4ULL, 
            0x0687444BC9BBE517ULL, 0xF6FE45AAFC951353ULL, 0xFCB315CEEDA62ACFULL, 0x89249515D7A8AA89ULL, 
            0xB7D47D377B431B42ULL, 0xEE335D0AEBAB1721ULL, 0x2BE84BADB5CB70CAULL, 0x6A3E437ECB002D93ULL, 
            0xCE28AFFF1CBDE61EULL, 0xE13121106FAC528DULL, 0xE60414280D564229ULL, 0x26E50D6DA9B4D7A3ULL
        },
        {
            0x10EE0DFBB9A31722ULL, 0x5F2E478D216C89A8ULL, 0x72898797A5B32D2EULL, 0xD2647E3FC50B7205ULL, 
            0x98CA3209C8D09D84ULL, 0xBB941B4082C44D1CULL, 0xEF83014ABC404A1CULL, 0x3776D4827ABF13C9ULL, 
            0x6B8BA872DFD2B1D2ULL, 0x989F1B8A38DDBA8AULL, 0x5DE4956008966B73ULL, 0xB296BEA8BB152E0FULL, 
            0x462F028C0C6CDF3AULL, 0x5AB53FC109E04D64ULL, 0x29565CBE4FB1287FULL, 0x9C1DE6B94BE34CFFULL, 
            0x1A77203A2447EA2FULL, 0x69D1A084FED7BFD4ULL, 0xA7E3346F7626C331ULL, 0x317F42EC68CBC66FULL, 
            0xDB85A498798E199DULL, 0x338C83440C1F514EULL, 0xCB904FCC2168EDFDULL, 0x20BC74B94EE3C51BULL, 
            0x9D23F269D26A0AE3ULL, 0x5E5A49001E30AEE1ULL, 0x4A7DAEE74894049BULL, 0xDC0B5C593F683977ULL, 
            0xF9E32C1BCF0E517BULL, 0xB521FC6903FCEB7EULL, 0xB16A024A889E73C8ULL, 0x3147E3A82B2DF136ULL
        },
        {
            0x8D864E02E70078DFULL, 0x04A46D5E971012B9ULL, 0xFC7C172C4C4AB4C6ULL, 0x6D5A1AD62E58936CULL, 
            0x1C3E429F837B5E8DULL, 0x8652A660573DAE65ULL, 0x76439781D6BCA54CULL, 0xDA688A13E3A5ECE3ULL, 
            0x289134EEBA580713ULL, 0x78366B7839B5E8E6ULL, 0x1F5EDCBB698243F2ULL, 0x2F91CE645940867EULL, 
            0x4B68AC297C76B845ULL, 0x816C6D7FFFC6EEDFULL, 0x99A9F1B9CF0B905AULL, 0x56C1EE045728A9CDULL, 
            0x026A514E71B66DECULL, 0xCCC4F28D96DF28BEULL, 0x7626ECE0A564F606ULL, 0x8269CECFDEDF8FA7ULL, 
            0x269A427B623BAE07ULL, 0xCC5C39BCBBD1E1C1ULL, 0xC4F82503702BE7A7ULL, 0x407EC8CA25DF54FEULL, 
            0x871B1159D626B282ULL, 0xDFD840CC99785F67ULL, 0x2833E26A58E8BB5DULL, 0xEF380A9DEA217A5BULL, 
            0xD75340AF59BCEFD7ULL, 0x0FA2DA132BB01B6BULL, 0x251FE1A49C25CC4FULL, 0x110A30BE2AA0D2F8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseEConstants = {
    0xDB5B24CBB1E32D4EULL,
    0x3F120234141667A0ULL,
    0x0259F12DE8E1379AULL,
    0xDB5B24CBB1E32D4EULL,
    0x3F120234141667A0ULL,
    0x0259F12DE8E1379AULL,
    0x8B9C29F4D26CF0FFULL,
    0xC413940B1F038E6AULL,
    0x88,
    0x70,
    0xE4,
    0x0B,
    0x78,
    0x69,
    0x55,
    0x6F
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseFSalts = {
    {
        {
            0x3E57E5824A766E08ULL, 0xEC8580C151CEEADBULL, 0xEAD9DD46291C32E8ULL, 0x77160495799578DAULL, 
            0xF98BF9486B62FCD9ULL, 0x9E4E2D12E53652B4ULL, 0x8240E59DB01A3A71ULL, 0x5D5BA244E3D4D081ULL, 
            0x24A7DAAD65646F46ULL, 0x4B097C90A37DEE2CULL, 0x0525BC6123DEDE2BULL, 0x8EF71BB144ADAF53ULL, 
            0x597248B0245927B7ULL, 0xCD396CF37FE2B9C1ULL, 0x94C728DB4EC6C6F3ULL, 0x2B01F8CC0C53449EULL, 
            0xEB83A3B09DB260F8ULL, 0x54270BB4FCD52B6CULL, 0xDAF5340065093E85ULL, 0xF741FBC11FEB5DA9ULL, 
            0xDF2534CA35790482ULL, 0xA38322750F264029ULL, 0x8A270B92767E27EEULL, 0xD2414953764EB9AFULL, 
            0x1CE2AB9F6B7C0242ULL, 0x518F149279133DC2ULL, 0x89AAB1B091BCB434ULL, 0x95968F70D961F55DULL, 
            0xCAC0B84AE8FD64A4ULL, 0x728747D611CDCBEEULL, 0xE6090969860B4A3BULL, 0xA272F7E68453BB85ULL
        },
        {
            0x9D980DE1E2897B41ULL, 0x69B4AA6AE5C6EE72ULL, 0x181D83D584DAB8A3ULL, 0xABBCB5AD2BA061D5ULL, 
            0x03109B0BC72210ADULL, 0x87E88C0A2FE2F147ULL, 0x3CB888A1A0B38807ULL, 0x978E2BB70604D6CAULL, 
            0xD515018C9B6888B9ULL, 0x2AF704A761509E6FULL, 0x7696FF39C46B035EULL, 0xEC9A7E278D2A916EULL, 
            0x2CCA9ED46254CF41ULL, 0x2C4D765D762AD51FULL, 0xCC4ED77DA5CF75E7ULL, 0x4F2DBA5610678DCEULL, 
            0x5CD33D083EE63861ULL, 0xEE3FF51F664F0032ULL, 0x30D006DDF0142B5FULL, 0x3258856FADC02E19ULL, 
            0x244D85F747A1209DULL, 0xAD8BBB228C2DD08AULL, 0xCDEDC0562A8790FEULL, 0xD296910C62FBD788ULL, 
            0x7934EBCA0CC75C1FULL, 0x2FC2B7F40618ADF7ULL, 0x774F922377C6400BULL, 0x84A8009340A2675FULL, 
            0x4E38DAFD02150FB4ULL, 0x2AB75573B4E767C3ULL, 0x305B9731D8C3C1FAULL, 0x6B413204B9ACFE51ULL
        },
        {
            0x5018605771CD3DE8ULL, 0xAE4FABBAC46E389EULL, 0x9BD967640D572C8CULL, 0x8F12CE384E65C33BULL, 
            0xBB58FF789BBFBA17ULL, 0x4426491A68CBAA4FULL, 0xFA1ADDCF3737D990ULL, 0x12001E34A2A13293ULL, 
            0x710B65B488EB765AULL, 0x0BE79A2955DB2E8DULL, 0x1B91B3EF0183EE2DULL, 0xACA8DE0DC1C18838ULL, 
            0x55FF2CCA8F6031BCULL, 0x5D710DB9903716ADULL, 0xBB244F1D32048735ULL, 0x85204E97BD993AF8ULL, 
            0xC5B8DE8B1F91ECFDULL, 0x89FDF6675566C0B3ULL, 0x67C4909E669B1A99ULL, 0xBADD7AD22686ADE1ULL, 
            0x7DFF1B71751188EAULL, 0x31D5E3B00EBF79CBULL, 0x32469555E2D18841ULL, 0x01E14E7B83D415B7ULL, 
            0xDEB4AB1DBF4A2A3DULL, 0x761D49435BF757F0ULL, 0xE572DCB23E01E120ULL, 0x69F9EE75DC61945FULL, 
            0xA29A4A32FB9E19ACULL, 0x5DF6A01F22943582ULL, 0x80A55CC83CD2A92FULL, 0x954CCA7A8425F6B6ULL
        },
        {
            0x270DA12A18AC44ACULL, 0x24039908B430CB3AULL, 0xCC89ECC42F0DD361ULL, 0x1A90387E77895F49ULL, 
            0x6D8A6549BE0490A9ULL, 0xF1A0A957F1E202EDULL, 0x0F184747A4933AFFULL, 0xF8C0DF33F8F1ECFDULL, 
            0xBAB025B13A7DB50DULL, 0x4C7CD5893B6C823FULL, 0x414C46B419F3BBFBULL, 0xBAF274A3BC6C61CEULL, 
            0x3258B18FA91168D4ULL, 0xC53E185D4176CA21ULL, 0xFF30C53A1B42513EULL, 0x710EED96BB50944CULL, 
            0x2D74071F76BF579BULL, 0x84C63834DF3EF377ULL, 0xA91B8F24A2908693ULL, 0xBD96170B8102D01FULL, 
            0xBAE40DF727B4D9F6ULL, 0xAFFB7871EF4D40FDULL, 0xCFDC0D820AA834B1ULL, 0x87B53F39A556EE0CULL, 
            0x221A086D8B6F330CULL, 0x9CFA40B0985C4320ULL, 0x3374B9727224682BULL, 0x62C395750D396519ULL, 
            0x51121C9FEAAB7EF3ULL, 0x469348B7457A4368ULL, 0x5DD54A2F86325124ULL, 0x4AF06DC7870C3029ULL
        },
        {
            0xAC4855371D568F16ULL, 0xCF229648CC1C717CULL, 0x03631D6697ED1BDDULL, 0x9D071E7697F2C8EDULL, 
            0xF44513F85B848CEDULL, 0xABF7D82CDFDC9A0FULL, 0xC261838FBBBCEFB2ULL, 0x0AC229988888B37BULL, 
            0xCCE5E031228A55E5ULL, 0x11D6D76ED3CB9C69ULL, 0x07D3578725D6ED3CULL, 0x10F3AB6A1B722F0CULL, 
            0x423CBA97C27439D7ULL, 0xF959B9D591AD6F0AULL, 0xFC4E60769EFCC0F0ULL, 0x35188330B1754F87ULL, 
            0x24B55C12C61902E7ULL, 0x9067550FFFF0C8D5ULL, 0x50EEC1E53ACC09E4ULL, 0x2FFE94B5A809F034ULL, 
            0x95039306B43D8A12ULL, 0x787BB637EF29BC08ULL, 0x5C134350FB935449ULL, 0xFB695748970D4B26ULL, 
            0x71AE1376180EAF89ULL, 0xA4DCECC492D77FC3ULL, 0x277DFA1572AA733EULL, 0xA0E34F7FA93A65FAULL, 
            0xD747E8546C856317ULL, 0x26CAED3D405387CCULL, 0x5B9F4B3EE42CF8ABULL, 0x0D9AEDBFED41D658ULL
        },
        {
            0x7426413A6ED2DB1CULL, 0x55742369B16D8096ULL, 0x59FFEFF140743C53ULL, 0x6E5BAFFC0CBF5B4FULL, 
            0xFC51103A2DA2AF90ULL, 0xBC2B595F471A8579ULL, 0x1B2F3626930AC859ULL, 0x553528EBDF4B3F9CULL, 
            0xD566A0824C8C8B0CULL, 0x6C9331939A0A9205ULL, 0xC38C0E618026750EULL, 0x5284C74B49BAAB01ULL, 
            0x79D6608344987E4CULL, 0xF97AA9AFA38B9453ULL, 0xF40A361B9E2D65BFULL, 0xAEA762EA30F646EEULL, 
            0x26F388863C75F351ULL, 0x76EA9115773A4FAFULL, 0x8C74C6FB6C85723AULL, 0x276F128DF90B6026ULL, 
            0xE4CC17A52F95D384ULL, 0x42DCCE3B567C5082ULL, 0x92C2D3DE5AB8B245ULL, 0x630AE1F0EFC20117ULL, 
            0x89019B29FC68BDDCULL, 0xF4524E0DBB8E4A31ULL, 0xB6487C4348BE8D16ULL, 0x6F0533BB99506835ULL, 
            0x5ECD7A9EAC1BA3C7ULL, 0x76902D47C7E0955CULL, 0x8C79F44E96D9C740ULL, 0x1FAFD2A3B2FAA33FULL
        }
    },
    {
        {
            0x8B98BA8AD87F0BCEULL, 0x83BB57E0C1A793ACULL, 0xABE9D81D4D72D4AEULL, 0xABDCBC8DEF385FD3ULL, 
            0xE4A263C66D156024ULL, 0x37BA7AEE98D8B486ULL, 0x29FC17F072E86DCEULL, 0x73B59394C8C5015FULL, 
            0x35B9A819B41E1FBFULL, 0xBACB0D3127243281ULL, 0x544BC575F40F0D3DULL, 0x115E271A967CE140ULL, 
            0xD5B3E24FB59DEF65ULL, 0x938F7E67AB736B28ULL, 0xD4B4683B3B9570B6ULL, 0xB080B00CAB752C79ULL, 
            0x6FA76740F97497ABULL, 0x9D042754E99CE370ULL, 0xBC3B39228F80648BULL, 0xC4C35F3712872D39ULL, 
            0xD1F5FCE6F4D9F869ULL, 0x4FF316502E1FF8BBULL, 0x166CFA0919AE6B1FULL, 0x90D9846F72C54619ULL, 
            0x2A4873B02FDDABADULL, 0x88C0BA49D36690B7ULL, 0xDC1DEDF5AA74A265ULL, 0x6BEDCAE00CA727EBULL, 
            0x7DF2745591AF69A3ULL, 0x935565094FB748F0ULL, 0x8A9FE4C669A639BDULL, 0x02D2D3E814DA9E4DULL
        },
        {
            0xE984ACE48A0BADC4ULL, 0x22538078DD271336ULL, 0xA98FA9A0B49B66DBULL, 0xC423EB1CB805C48DULL, 
            0x30D2E5854A203788ULL, 0x7BF8BAFE9E54AE30ULL, 0x5EAC55C9B23CE256ULL, 0xDC34A96B97CE72FBULL, 
            0x54C211B1C3B2055CULL, 0xF90CC704F883C329ULL, 0xEE78CAEB957BF63AULL, 0x81B7CB143D2DE22DULL, 
            0x16BCF18016EF01C8ULL, 0x3AF5D878E37C310FULL, 0xABB3F11D39E95708ULL, 0xD021820FA1AD5B26ULL, 
            0xFB96AD469F575F83ULL, 0x1DDC045D188EBB11ULL, 0x37C434A056A16362ULL, 0xE3A35648345E2D1DULL, 
            0x672CAA5DF51F5E25ULL, 0xAEDE753836B61E48ULL, 0xD1620BE4AD0F4315ULL, 0xDD3A40F50BD8251AULL, 
            0x744DA50DF4CBE8B1ULL, 0x998BE26072407421ULL, 0x0CA778158C5D7254ULL, 0xFBB62253E522F1C7ULL, 
            0x24350B66564D8016ULL, 0x5121038D29120C96ULL, 0xFC62735BC84E8EC4ULL, 0x88F63DD159642F39ULL
        },
        {
            0x0245C458D020EC73ULL, 0x8E6CAB3539FE3C38ULL, 0x5C36A11964C20F73ULL, 0x070F05785AADEA06ULL, 
            0x39FCB7435F58E99AULL, 0x70378A687C79EEE8ULL, 0x95E022A01E7EAE4AULL, 0x825099D0CF92C9EFULL, 
            0x314F5E6C2095C3AEULL, 0x14948326AEC393EEULL, 0x636E320F86717B5AULL, 0x0E504D138991BDEDULL, 
            0xF7FC70741B37585CULL, 0xF30A6FB7BF6A2A34ULL, 0x175690E1556AA316ULL, 0xD6BAE3CE6E65A7A5ULL, 
            0xCF1952A808E35569ULL, 0x28CAE4AFBADF6D39ULL, 0xCA8D178B23D195FDULL, 0x355E82CB5868B29CULL, 
            0x281A0792C501177AULL, 0x6E3FE3AF286F46B5ULL, 0xD51E2DEC67C74FBBULL, 0x575F34BE86CA76C6ULL, 
            0xE3142675D3D758FCULL, 0x01D64904D53A4A73ULL, 0xCC83FEAC8BE2E9FCULL, 0xF936F574B329E763ULL, 
            0xE876C7CE449B5EC9ULL, 0x8274E84D31908EA2ULL, 0x5C8600C7D4DD0D70ULL, 0xFD3EE4E1F111F664ULL
        },
        {
            0xBABD8B7D89ECC8ADULL, 0x8C38EEB6193413A3ULL, 0x4AED9ECD22F89548ULL, 0x5088596F68B482E6ULL, 
            0x4C61E33C893B9C51ULL, 0xB4D7DCAACF71F240ULL, 0x05B55674C88497BBULL, 0x9C548C37E528EAC0ULL, 
            0xE3B7F162E16BE63DULL, 0xABCCF38AD7D4E9CBULL, 0x5ECE7037F7244985ULL, 0x87E03DA605550096ULL, 
            0x9FFC64988491C7E0ULL, 0x848BAE030CFE90B5ULL, 0x99CC4FDF4F7D2F64ULL, 0x4CCBC7004DBD44D9ULL, 
            0x36CECF03972C756EULL, 0x488C3E0C5E0E23B9ULL, 0x114B4A5EFF39F35EULL, 0x0F9C42F86E3595A6ULL, 
            0x20AEAF7FBA18D577ULL, 0x5790ED5FF308C25CULL, 0xF1531FFD4ED979D2ULL, 0x2C69EE294C1F0C76ULL, 
            0x1B093C87D99261CCULL, 0xECF35DEAECC234DBULL, 0xA1704FC493D19FBCULL, 0x34DEFD04EB84923AULL, 
            0x1E470B3A0082B506ULL, 0x14471349B89FCFF2ULL, 0xF354303F938FA79FULL, 0xE626735969A5243BULL
        },
        {
            0x95625E3D3E31A945ULL, 0xCE93ED81A0A50AE7ULL, 0x86243F36BC0EB9B0ULL, 0x82AA594D3604661EULL, 
            0x90A0A453127675BEULL, 0xD62559093D7746E1ULL, 0x2029CD545DA2AB16ULL, 0x0FCC4E57C7D7C3F1ULL, 
            0x660837CA1467B11FULL, 0xC2D1604FD7D5BEBEULL, 0xB124176EAA8734CDULL, 0x73B4E2C932D39B6FULL, 
            0xF9E12DB2390EE302ULL, 0x2251973FE7E76E8AULL, 0x518A11F094CBF01CULL, 0x2142165678B5B0BCULL, 
            0x5365BF25E59A6B8BULL, 0xC58EB8CED762166CULL, 0x89B4581901AB9B0EULL, 0x51B761D072269693ULL, 
            0x2ED0CDB25C4DEB4EULL, 0xC6C102002E4848F3ULL, 0x186B7799F96BB772ULL, 0x10A7670AA2CF3045ULL, 
            0x13A199B57AC959D5ULL, 0x449359F3FE7ED03AULL, 0x90C4CCCD90081B84ULL, 0xA7C0D1716F5739DBULL, 
            0xBE7C2AC282760D10ULL, 0x945A7EC088F9CDC1ULL, 0x950D7087FF161DE1ULL, 0x13B96685AAE67F9CULL
        },
        {
            0x4FCF216EC66D497AULL, 0x7D29D2DE164D80BEULL, 0xF0F684748F79406DULL, 0xF1A84B6190E2098EULL, 
            0xF6A41830DA87AF14ULL, 0x98FEE1CAB679280CULL, 0x9C20E34E6CC859B7ULL, 0x089ABAE1086395CDULL, 
            0x042C4BB053EF8A36ULL, 0x1E5F1B125C3D4D81ULL, 0x85DB9D6483438982ULL, 0xC5490EBC8B81B724ULL, 
            0xD33010079C7BCFCFULL, 0xE0D81292830824E4ULL, 0xA8CEE936CC2D0F32ULL, 0xDC88DD0091B4F9F8ULL, 
            0xC4D29F10FB475047ULL, 0xA596F08FC16C7B73ULL, 0xA01C16405329B7E7ULL, 0x60BFEBACA0622883ULL, 
            0xEC5C87B8E517217CULL, 0xD1092E6ACC46D6E0ULL, 0xFE91E3E59E48A2C5ULL, 0x7478C262C6CEF578ULL, 
            0xC79B4916EE120C4AULL, 0xF372C7CE0FB85BD9ULL, 0x4AA7ABF84F7A3D78ULL, 0x2BB40101A4374ED1ULL, 
            0x06E68908C2A7C0CBULL, 0xB7D4963A2C5CD78EULL, 0x0152C5EC92C32EBAULL, 0xBD56606396140CFCULL
        }
    },
    {
        {
            0xE6A35739CD2FFCD5ULL, 0x8E74D60D6C2548F3ULL, 0xA0C700DB0431D3A9ULL, 0x4A1F6CC3D7CA3164ULL, 
            0xACCF7DE2D36F29F4ULL, 0x0E100B5B80B64A53ULL, 0x21D5DB6B74DFEDD3ULL, 0xEAC84A1D4FA0144CULL, 
            0x0FBB1B3B758EDC9EULL, 0x102039783642DA2CULL, 0x7818C3ACE813C187ULL, 0x53927C8A5016F84BULL, 
            0x27F965C3501A84D4ULL, 0x4D5A02AC6F238548ULL, 0x5810210ED449E580ULL, 0x234C280F167AD7BAULL, 
            0x0044D2516FE43F91ULL, 0x1DDC8176F73B034EULL, 0x95FE5AF8105495D5ULL, 0x6BCEBFDD443D94FAULL, 
            0x501D7ECAFD20778CULL, 0x63D4EE038FAC5AD7ULL, 0x9594DD2A90913124ULL, 0xC632F23CE75515ACULL, 
            0xD425AFE55349BE8EULL, 0xBE41C439295339F7ULL, 0xF416ACFE44B93F1AULL, 0xE33AC60FC89792F7ULL, 
            0x39D4E032A3E1DB6EULL, 0x6AB77429DD418905ULL, 0xDAC9BF966FA050F4ULL, 0x293287C3F1E4EEF5ULL
        },
        {
            0xF66EAE258B9CCB94ULL, 0xC4B247F6AF9BF66DULL, 0xE138265224A17126ULL, 0x65A598F8F939CC7EULL, 
            0xF8695EEA9F9C6FA1ULL, 0x8EC0644843D7FDA4ULL, 0x97F7052753EB76ACULL, 0x0A3B4289A432FC64ULL, 
            0x4DAC6F6FA9458BACULL, 0x009AA6A33D12444BULL, 0xC8376837E4A025A7ULL, 0x1D1D8475E9821E92ULL, 
            0xABBAFE7C9EC15DFFULL, 0x2C9A716056E6F3BAULL, 0x29A8D1EB9223C2AFULL, 0x2A53958FF2C824F1ULL, 
            0x65F3659F660BB51AULL, 0x3620E4AAB3A3CE7EULL, 0x8C5905DFCB9EAECBULL, 0x5606447A2E42E3D4ULL, 
            0x112630F74CF6682AULL, 0xF0C709E453A2CE95ULL, 0x73E34085C8C6D864ULL, 0xD0F553B207849F12ULL, 
            0x42BFD27D8E713C35ULL, 0x4C9D0B27B75F2AE8ULL, 0x0D3E22301DFFAEF1ULL, 0x4C95BCF12383DBE1ULL, 
            0xEF516B59C1F81EE0ULL, 0x2D2AD8F0161AF505ULL, 0xA84486E317853069ULL, 0x881D566BA20743CAULL
        },
        {
            0xD8067D89E0BAB92FULL, 0x4B5524CE8F18DCACULL, 0x3DC1BF73CC0C9D30ULL, 0x5B393009EE937E69ULL, 
            0xA367A7B54FC1773AULL, 0x1740199F03AABB69ULL, 0xF29B4AA5D6651D6AULL, 0xDCEB9617FD9AE3D4ULL, 
            0x4A18655EF37EDCC8ULL, 0xAF9196E0B1704769ULL, 0x4549A4CBFAB322FEULL, 0x41F5E68055F09D1EULL, 
            0x76AE1EC273C59E4AULL, 0x360FBD530681D9B6ULL, 0x2B2DA015C397735DULL, 0x4512441250736085ULL, 
            0x7F79F2CCC137D522ULL, 0x29251CD90A1D1753ULL, 0x62251C885453F4D4ULL, 0x7769B4A4041AC116ULL, 
            0xA66BFC376B558B23ULL, 0xFC5031E669B7D7C2ULL, 0x6EE6C1046EAB7C0BULL, 0x89EF86AE26AEFE4BULL, 
            0x6586B236B471F891ULL, 0x8AB0C4F34EA51EE6ULL, 0x6379F22E5B9C5336ULL, 0x21F1C7A8D5DD34C6ULL, 
            0x5928AA2EF84F4D4CULL, 0x4D54C951875A4526ULL, 0xDDCA71C6EF884E5AULL, 0x98CE40FB62D900E9ULL
        },
        {
            0x3324AF42232D4FAFULL, 0xE785F8F2F011E911ULL, 0x609D995C6FB624A0ULL, 0x8E6BFEE8BC3FB797ULL, 
            0xDB39B44610776E7BULL, 0xA6CED9570351FCD5ULL, 0x022466EC597D6EA2ULL, 0xD15A17A948D227B8ULL, 
            0x63CCDBF5AD372A5CULL, 0x36C6F242D318EC0BULL, 0xB5AF717B35AC4D76ULL, 0xEB12C4FEB6A7259DULL, 
            0xB73D9D175FF8BE55ULL, 0x087011EC64F623A6ULL, 0x332585B3DFCC411BULL, 0xBD9107AD94865672ULL, 
            0xEEF7F4F569CBD5F5ULL, 0x9AEE1E868B9C6C42ULL, 0x0866CA1B1C72733AULL, 0xDCF311AA51023F15ULL, 
            0x66E8E52E5EAF8A67ULL, 0xE971EE429DFF294BULL, 0xE08A8A932071BB4DULL, 0x8243A9629057A2C5ULL, 
            0x58C7DAE1533EC39AULL, 0x6ED0A22FBF7AE8F7ULL, 0x35297ADBC6F8A853ULL, 0x4952AFA2D967ADF6ULL, 
            0xFADB0E188D1D51D4ULL, 0x03165AEC72C95F49ULL, 0x1F410E4C37C2C56AULL, 0xDB73388CCB6416D6ULL
        },
        {
            0xFB5FFD6E58AAE2D7ULL, 0xDB047952A5161BE4ULL, 0xCF8090BFA019F375ULL, 0xC10B81EADDA48453ULL, 
            0xAE7236687D9FCCAEULL, 0x3EB287094FB92198ULL, 0xF73123E60A51AA48ULL, 0x2B380B9820E0EC4EULL, 
            0x4A08A02505C3C507ULL, 0x4B27B40260EA6588ULL, 0x3CE13EF633F45273ULL, 0x65BF54C5DAF764BEULL, 
            0xC4A3B17769DABFB6ULL, 0xAA2E6693FAD8173CULL, 0xB5A13DFCEEA62A02ULL, 0xB2D11DCB206121C0ULL, 
            0x671E06C8E206ECB5ULL, 0xC03AFF973A3DA1D5ULL, 0xB763892977EB333EULL, 0x89C031FA59B12021ULL, 
            0xE84CD0D56E024B4DULL, 0x9BDE7BEE58DCADBFULL, 0xE964CB5B884316B5ULL, 0x399A418B36450D28ULL, 
            0x2E3FEB3E41A33773ULL, 0xC1B507FD496A7959ULL, 0x36D375192209A6BAULL, 0x7C513E4D6D2841D3ULL, 
            0x7A3078F8AD620C78ULL, 0x3DE39C6F97307F27ULL, 0x89F37E09D5A283ABULL, 0x5CFC37A529FF0AD6ULL
        },
        {
            0x342F6C188948253CULL, 0x1C216B8A03B7F7EDULL, 0x79C81D08F50E1594ULL, 0x3DD96921EA17FA4AULL, 
            0x60512B5BA1D5C2C6ULL, 0x2719BC9815A0B7F9ULL, 0xC1FDAC81DC53E408ULL, 0xDACDF73404B9E4BFULL, 
            0xB310BA6887F261E0ULL, 0xE37454538BF087C9ULL, 0xCA70B45D7557D815ULL, 0x17B77F37A67D3C6DULL, 
            0xC177E7AE1704B0ABULL, 0x6BA9E036C15013AAULL, 0x9158173F09075E51ULL, 0xFD396D9DCBB68994ULL, 
            0x9514111012DC4EC4ULL, 0x7154CCBBDE6E44FAULL, 0x85C1DE1838DA5285ULL, 0x7DA308BDF779D33FULL, 
            0xAE94C10779AFF62BULL, 0xEA2E27A80582ACBFULL, 0x3E9A24EC3E1D69BBULL, 0xA1D2DEFC49A521F9ULL, 
            0x0850E22916A6750BULL, 0x64B91407B240FED9ULL, 0xD3C944A7D8C74224ULL, 0xAC3988F673FE26A4ULL, 
            0x4BFF477E67E3E5D5ULL, 0xFD8C327ABFAC84DEULL, 0xD21FB76F95B06EF8ULL, 0x0B083D1213E935F3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseFConstants = {
    0x51D2095ACAC6D36BULL,
    0x0580F0D49F12D8D0ULL,
    0x77ABD2F5DE1EF7DBULL,
    0x51D2095ACAC6D36BULL,
    0x0580F0D49F12D8D0ULL,
    0x77ABD2F5DE1EF7DBULL,
    0x4464E7F089E96BDDULL,
    0x2B45FB041D884FA9ULL,
    0xF0,
    0x19,
    0x65,
    0x2F,
    0xA6,
    0xE8,
    0xBA,
    0xF2
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseGSalts = {
    {
        {
            0x4B8CE3D3EEB5AB0BULL, 0x25FE284F7FF8DF64ULL, 0x7420FDE376F4BC44ULL, 0xB2A961908D7A585AULL, 
            0x30ADE185B2A329ABULL, 0xA98CBC11AD2F3AE0ULL, 0x4B88536DC72C0329ULL, 0x6BE636E8D084FF34ULL, 
            0xB268FABFEFCAB376ULL, 0xDFF0C26C7982BEA2ULL, 0x68911867120EDE13ULL, 0x8A3B78E9CA6FF7F9ULL, 
            0x6E55D9140A9523B0ULL, 0x1DF66856656B5D55ULL, 0x0C949E1D0BE433BCULL, 0x5E349FD49F012F06ULL, 
            0x3BBF43164E70281FULL, 0xBBFC4FCF0286EABDULL, 0xC830BBCB34FA4D09ULL, 0xE514729F4D85A564ULL, 
            0x5EB4E071394ED5AAULL, 0x4CF50A5326B10060ULL, 0x2254265C329C2801ULL, 0xCD69C62691A5EC8AULL, 
            0x9C7C25548B6BCDD5ULL, 0xB8821E7A2EBB5724ULL, 0x5A6EA856870D06BEULL, 0x9D417B1FAE048B78ULL, 
            0xB127E0DA9126B669ULL, 0x34CBDABA9F45D103ULL, 0x95ED585D05A6FE9DULL, 0x891608112E262700ULL
        },
        {
            0x93E1FA62DE4E7336ULL, 0xBF89EFE63DCC51CAULL, 0x92905D9E5169AA87ULL, 0x0C3AC6B562AEB438ULL, 
            0xF0715203C2716F71ULL, 0x9E7F952DB82496BBULL, 0x74616E83DF55410AULL, 0x8B3D099B262E2385ULL, 
            0x9A1E1D12F1F3144BULL, 0xD1E83C72CABEA099ULL, 0xB4A2730BA038DD8FULL, 0x218513FBD289E093ULL, 
            0x2BABA715D34DC852ULL, 0x23DC891E495D7880ULL, 0xD6DD301323562CC3ULL, 0x2A7545113D927125ULL, 
            0x72A41387FAC51CFAULL, 0xBE9B86635D77EC8AULL, 0x85BBB3A3462A2D50ULL, 0x817EA97001F83CACULL, 
            0xDBA75748832D1C3BULL, 0x6377D93A3EA8C540ULL, 0xC8BD3C55EF22A108ULL, 0xE3378DCE651E9AFDULL, 
            0x09EADE04381153DCULL, 0x1F2E952E1DB02D58ULL, 0xA0958C2A3CF5174BULL, 0x9EAB3B91D2B7B82EULL, 
            0x5C5187CF718934DFULL, 0xD2EC193C9BDDF2B8ULL, 0x76A94685A3CCC90EULL, 0x0AA8C863C69F8CA7ULL
        },
        {
            0x33A1A94C98DA79ADULL, 0x41ACCFAD7A1605F4ULL, 0xD5C057CFDF20607AULL, 0x7042A5983763CCEFULL, 
            0x4ADD88F45E3A1129ULL, 0x17D75D71BAED5341ULL, 0x24DA3092563C51F0ULL, 0x7B9A579EC0E6D5BBULL, 
            0x98A5ED55FA29E3A1ULL, 0x28FBCD6D526BF7D2ULL, 0xAA7B7C1B0B46DA43ULL, 0xAFE4327800359255ULL, 
            0x281A0468F9118638ULL, 0x85F2E8097DCDDB66ULL, 0x7287CA44D38E2639ULL, 0xBA5064994617A5D9ULL, 
            0x58BF51CDF5E1DB83ULL, 0x20E88B6E5634304DULL, 0x2B581B4C629E39DAULL, 0x97A825EEFE66849EULL, 
            0xB721E1ABF532D1AAULL, 0x7F6ED8D4A4AC97E1ULL, 0xFE6CFA6FDF3C4AE2ULL, 0x28A430E779507EE5ULL, 
            0x2FF4F13DF84940D1ULL, 0x7C42CAD97CB52856ULL, 0x652F7CED19B52E02ULL, 0x59780D5D2A62D8EAULL, 
            0x51818F8BBEF43820ULL, 0x9744A551C2D816CFULL, 0x032152004F011561ULL, 0x47909725E3337749ULL
        },
        {
            0xD173862EE30FD0FAULL, 0xD4CA94444ECCE3F3ULL, 0xEF2B520EF1892159ULL, 0xA18D5257B455A50BULL, 
            0x861B9A757B7CA6A6ULL, 0x2EDD0118D0A94B9DULL, 0x9685719E51915ED2ULL, 0xB69230B0A78A3583ULL, 
            0x12E52EB361FBB66BULL, 0x3A462E5499D4A792ULL, 0x9A36918DD4529ADDULL, 0x0928F7E67BB7A4D0ULL, 
            0x28B57294A392F838ULL, 0x722E1BA01A42D9DAULL, 0x7B7B0D189A063195ULL, 0x064F5BF74195C52EULL, 
            0xDAD59903A3A87309ULL, 0x15FCEC9258B456C2ULL, 0x05A8D93A64B2F5BEULL, 0x4D1A9C80BBFF4CA9ULL, 
            0x240857F5E6B39BD7ULL, 0x4604202B408C1B6AULL, 0xDE2168DC9FDB967DULL, 0x441762034CC009AEULL, 
            0xD1A4FCFCC95C4EC5ULL, 0x938D7BA79F0364E4ULL, 0xB9C2B6D61B1833A8ULL, 0x41DE8E3C3A027F58ULL, 
            0xCD6D3983D4BBA9B2ULL, 0x02868B62E522EFFDULL, 0x192B3C71AAF90DBDULL, 0x805D6FA0C3DD8609ULL
        },
        {
            0x0C00D33CBAA4B47BULL, 0xC752C44B677FF871ULL, 0xCF412A39B22F1AC0ULL, 0x140F142F350F697FULL, 
            0x19F9A111FFF51C2AULL, 0x2D287D35C1FD14AEULL, 0xF044804FE557CDA2ULL, 0x505CE8CA8A46FED5ULL, 
            0xAC13E510C32A6418ULL, 0x3F940A3894532479ULL, 0x664EFAC8E650ECCCULL, 0x853E91C611D8D7A2ULL, 
            0x04F3DC3E024FAA92ULL, 0x4582DB376F479F5BULL, 0x091BD6C94E3F0D7EULL, 0x9D8128A5D3ACB0E1ULL, 
            0x3B3784E091485FA0ULL, 0xC2575425FC10BC9DULL, 0xBE3B83B21F23B3C3ULL, 0x6CD12256E019E1A6ULL, 
            0x0850F5897D00BA1FULL, 0x014EC9D5C981AB6EULL, 0x9E8A5561F24EE045ULL, 0xB0C064EDEB9F97B9ULL, 
            0x91ECD3950EE1B58FULL, 0xD22047CDFA952131ULL, 0x52EBFE6044E94F23ULL, 0x8799CEC30997A7CFULL, 
            0x3335709DC56C82BDULL, 0xADD440E7680D07D3ULL, 0x0B67FDD6B10BD08EULL, 0x1241B8723ECDA5B5ULL
        },
        {
            0xA078A8D1E5F7DF45ULL, 0x963FB2B8250AD223ULL, 0x5B68CD41997C5641ULL, 0xDF05F4AAE07F7BDBULL, 
            0x6691308DE8718330ULL, 0xA10F28A27F485AABULL, 0xB0924E29ECC97A30ULL, 0x5DD3117EFDBABDB6ULL, 
            0xCA8E56C3156E4305ULL, 0xBE8D20C40F1A42BBULL, 0x6025F73F1E0FF7C0ULL, 0xEFF4C10A070D0A7FULL, 
            0xCD94473AA56AC061ULL, 0x30E029AEB3FAF9C8ULL, 0x8C1233CB54244B24ULL, 0x5E53789CCFCD6EA6ULL, 
            0xA103F0F324A7375CULL, 0x2A3DC159AB2257F9ULL, 0xE2D7CD1FF914A26BULL, 0x3EB6FF296ADF59FCULL, 
            0xE8EEE354316B7132ULL, 0xE1967823FD8885DEULL, 0x50C2AB93FB28E663ULL, 0xB00662C36D4B25C1ULL, 
            0xD5090355E232B80BULL, 0xB0FEA13051F2D901ULL, 0xE5C115784A790102ULL, 0x933F95E5D7F643BFULL, 
            0x0B72BCEDCCB3B45EULL, 0x2B8C63817464CC89ULL, 0x20C86B34AAEBD89DULL, 0x3AF2C450D0504AE7ULL
        }
    },
    {
        {
            0x320C99E048EF0703ULL, 0xEB078F1438240358ULL, 0x068C0FC42D055D80ULL, 0x5BCF62FD9E771443ULL, 
            0x4DC87C47D34473F8ULL, 0x0337E1CB4214525BULL, 0x9CAED5C497F97F94ULL, 0xB7682AE4EAF940F9ULL, 
            0xC6035D478E9B2A10ULL, 0xDFA2C53AE1F3F30BULL, 0xAA1B3FA9128DE765ULL, 0x0196AD6EE1F1BDD9ULL, 
            0x58A368F6F34200C8ULL, 0x6EC0A181880EA484ULL, 0x0A5071BBF080FBC3ULL, 0x2C4237B65BA5D1EEULL, 
            0xAFED6B1B0FC0C41DULL, 0xEC4311AE5D4D9A4EULL, 0xD6023EF6311B147DULL, 0x403D83278C7CD1ACULL, 
            0xC71352668800FF8BULL, 0x4B6C2F95B2FFC4E7ULL, 0xA5597A96E591F63BULL, 0x87AA5455CAECDEF0ULL, 
            0x9DE0B77FCB72D215ULL, 0xEA3C8D187CBF06C1ULL, 0x8BD74E398DAB49A3ULL, 0x1BED5EBDBC2EBB0AULL, 
            0x9CDEFD925060B24FULL, 0x4E4FD198514D93FBULL, 0x61B50069E2BCEFEFULL, 0xD949A6E82D12AD34ULL
        },
        {
            0xDA704082B023F850ULL, 0xDE9A491724EE742AULL, 0xC6DD59C8956821C3ULL, 0x7FBCA674B78E2404ULL, 
            0xE143DC9F7AE6389DULL, 0x3DB3BB076F1BE630ULL, 0xE48239E4575B9D7EULL, 0xA17C1E82E28230F8ULL, 
            0x5EBCB2773632E4CEULL, 0x6D945DC575A9B792ULL, 0x90939A028455EA84ULL, 0xC7EFE841044F4FBDULL, 
            0x959A9605A96ABF8CULL, 0x8E5B1BD3E8E1CDE9ULL, 0x08034C72A254B305ULL, 0xD21303531CD44EC2ULL, 
            0x5770981070185EE5ULL, 0x2C0455F83FBA8F5CULL, 0x7AB90E0F91DD1187ULL, 0x8FBE67DA7A4B8DE4ULL, 
            0x9E2B80CBC0BC9790ULL, 0x65F5C4EC027012E0ULL, 0x9B0F9951C75F9BD9ULL, 0x0B0799559CB6931DULL, 
            0xDFB4279D41935699ULL, 0xB07AA0B2A5092032ULL, 0xE31965480DFCD1D8ULL, 0x1F75512AEC593B55ULL, 
            0xF546AAE4F5DE623FULL, 0xDDB0F6E283D01E4CULL, 0xE4FA572CA1E8F497ULL, 0xD0AB1CA5A61DD43EULL
        },
        {
            0x829E99CEB72F7C3FULL, 0xC8E1A67AA8B69064ULL, 0x933B4B99AA940547ULL, 0xC36DE88F736E1D68ULL, 
            0x32C1CFDF9A8C270FULL, 0x6FDF519F36F78AF3ULL, 0x1A45BB0AFA1C83E1ULL, 0x149E590A44975F27ULL, 
            0xBAED7B03394320F8ULL, 0x023B36AB65F2080CULL, 0x6434C5638F4DE30DULL, 0x80B67951CAA0CE8DULL, 
            0x1B81607697E544B0ULL, 0x7DB3FFCED3ACD0EEULL, 0xED97909BD8FE4D52ULL, 0x6736A3D64786BD8BULL, 
            0xA0077C731B9834DDULL, 0xE17E8E705BFD2311ULL, 0xFC3CC4985D17EEAFULL, 0x06F6781DD0C9ECD1ULL, 
            0x847248CD6AD92162ULL, 0x940975EA52DA1FA8ULL, 0xF654CE99CB06FA9FULL, 0x9F0F53845B389F10ULL, 
            0x2C819CFCBD4841A7ULL, 0xF87656265BE19C14ULL, 0x4ED203601C80A6E4ULL, 0x6F194BA49594760EULL, 
            0x84A6B5EE198024A5ULL, 0x4F64C8802C0C3BE4ULL, 0x14DEEFAF01BFFEEDULL, 0x8878AD25381C6AF0ULL
        },
        {
            0x5DA0F2979805793FULL, 0x2886A5C7367D260FULL, 0x8BBB5073EF6AC01BULL, 0x34E266B2D64C7D5EULL, 
            0x14A3574B49F362E2ULL, 0xD7C144176BA1A145ULL, 0x0B46EF91EE75DFF3ULL, 0xCF077C45DFDA7121ULL, 
            0x18002B82B584FB56ULL, 0x48FC7ED910E553A6ULL, 0x49FCF6B861F52E11ULL, 0x3B47EE09BE53B0BFULL, 
            0xA39A5F6A356DD553ULL, 0x52E4CA8DD018F178ULL, 0xBB38266EDC752BB0ULL, 0xB223EA424120C07BULL, 
            0xDECB01F7CC9F4A0DULL, 0xE5C39D0954B4882CULL, 0x7075060A2415C7CDULL, 0x09250708F1727C91ULL, 
            0x0327909600135BDBULL, 0x11E974935AAEA9F6ULL, 0x3D53CE811F140DF9ULL, 0xA0E32E54EB830820ULL, 
            0xED2C3FA954228350ULL, 0x290BA6D7D593045FULL, 0xCE157786A3AF6294ULL, 0x111DB7C9A6D2A46AULL, 
            0xD9E2FADA9A1F93C4ULL, 0x90AC44A65D5F874FULL, 0x9D45E046542E758DULL, 0xA8AE0E41EFF85D9FULL
        },
        {
            0x520D109422DA3028ULL, 0x4A5601A07861D100ULL, 0x0985969292BB596FULL, 0x9958FFBF96F47BBFULL, 
            0xF449D6611C6C32E5ULL, 0x97F33DFD89E3FFE8ULL, 0xF37E524064797746ULL, 0x37257DB85DB0D933ULL, 
            0x13607E75773B4F6FULL, 0x7445E9A06F760E0AULL, 0xFA9F42CACBAA09D8ULL, 0xB903A777911B65A7ULL, 
            0x0C85FE5AFC57D978ULL, 0x8752DB818325DD38ULL, 0xDC8DEA2F9A7E3F6FULL, 0xE614BE80A185B89CULL, 
            0x1B027F85CBDF59F6ULL, 0x66D4EC558C7DF092ULL, 0xBE6D0F33436E3ECAULL, 0x711A149463501938ULL, 
            0x0A18271C9ED7F57AULL, 0x5071F3F7AA47E931ULL, 0x33D2FC8D7A96BD09ULL, 0x8036321A158ABE4AULL, 
            0x1CBA535F82C2A372ULL, 0x499B2CE7E126ED24ULL, 0xAA3775F216D3A2ECULL, 0x9D2EE7FEF60774D7ULL, 
            0x775A71199F611E2AULL, 0x07884B4CC11A40F8ULL, 0x86268C47A03F2728ULL, 0x97179AEA4B7A685EULL
        },
        {
            0x864A3F9E3EB19417ULL, 0xB88E17EB8386E6FBULL, 0x5611A400F8920A79ULL, 0x532DEA63012167C9ULL, 
            0x3F5162C4287F1371ULL, 0x02C90F4719A882EFULL, 0xB728A00483049E36ULL, 0x0875E6ACFA432A72ULL, 
            0xE7F5C7459C8D32B2ULL, 0xD4653DD248EFBAA2ULL, 0xCE50003811B89FEBULL, 0x81DBC90A457869A7ULL, 
            0x19929DAC94EDF716ULL, 0xA713FCC641F33203ULL, 0x9F69EFF52B81A9F9ULL, 0x0ABB34F1BE31A821ULL, 
            0x5628DB0214D8C6C6ULL, 0xD6D22780E5A3EBE9ULL, 0xF798AB74E1B7E535ULL, 0xCB7141CB3354F765ULL, 
            0xFBF89AE777997C43ULL, 0xC082BEF0F1F6E25BULL, 0x6CBFF713F390C251ULL, 0xF22B441A3F5FB4B6ULL, 
            0x77FD298F37F7D06BULL, 0x482E8FE537ACCD5CULL, 0x750FDF2D64921073ULL, 0x6CD2A3610D4750ECULL, 
            0x232EB87F210DB277ULL, 0xD731C83FB37CA596ULL, 0x6D1D7B061E9F9FFEULL, 0xFF38B0397207B4DEULL
        }
    },
    {
        {
            0x92E4CD558351174DULL, 0xF4B9202985607229ULL, 0x75B27C041CBA88D6ULL, 0xC0ED8B6A784D1710ULL, 
            0x8413954C7E4CC537ULL, 0x60292977EC0A929FULL, 0x41EB9FC13FFBB4F4ULL, 0xE81BC7632527B6E3ULL, 
            0x4CBE2AAD8732662AULL, 0xB8E82AFA6AD7BE30ULL, 0x9077885DA16CD70AULL, 0xD124135DC9293109ULL, 
            0xE62C913582F2BE6DULL, 0x5A425773B76B0AC5ULL, 0xA1C1C563D3AB3CA0ULL, 0x1FA78519EB158189ULL, 
            0x0E7E7312373BD640ULL, 0x45686F9C60FB0C35ULL, 0xF75EC2941E6735ACULL, 0xB790B5BEBE7E4371ULL, 
            0x5787826168299B40ULL, 0xF2B86EBF7839F61FULL, 0x2B707AC7AD7F1E5CULL, 0x1156E84FD3015B70ULL, 
            0x6294F33636125B42ULL, 0x0B9C7D2E80D5DFBFULL, 0xC5602C43F3EC7C29ULL, 0x79C2A178D7B168FFULL, 
            0x231340DAB00F9A39ULL, 0xE71EDBAD5CA66EF0ULL, 0x2578E1683B7C974EULL, 0xFD149F43D8E9AB1DULL
        },
        {
            0x29E5F000C4E169BEULL, 0x2437494CAE9AC0E7ULL, 0x83A379C36CE97507ULL, 0x093CD8806AA54ADCULL, 
            0x0A48702C284EEDBDULL, 0xA2E2D68CF44A705CULL, 0xDF344CB417063209ULL, 0x44B06BF63C98246AULL, 
            0x7D8854875B28F3D5ULL, 0xF3D7BCDB1C7F19D2ULL, 0xE58011840D3DADA9ULL, 0x6ACB7D45942EE46AULL, 
            0x066E025918C045E1ULL, 0x5D786FCFCDEB209DULL, 0x6AD32E94964401F8ULL, 0x55CD3F24BE63835CULL, 
            0xABC14F23834DF8FCULL, 0xF39A99CB1C07D462ULL, 0x126D8E2A0DE35BCDULL, 0xB21E81A4FFBF96D4ULL, 
            0xE7CF2EBDFA6B2FEBULL, 0x467D3B7130BB269EULL, 0x40921C454B827624ULL, 0x68949D87F0CDB48DULL, 
            0xCC6F3EA9CD489E2BULL, 0x8CA4D3AAA03FB18FULL, 0x0C4B7A39BE4A994AULL, 0xFEACDDA67DD65E8CULL, 
            0xBC048E13CC0BBC93ULL, 0x7EEDA26574FF2014ULL, 0xB98F98D1E2C65C43ULL, 0x93C794F9987A9C9DULL
        },
        {
            0xE1FFB27BDC714956ULL, 0xC46C58F7D229E5F7ULL, 0xD88CE41A797AC3E2ULL, 0x7850CF75FB862E6FULL, 
            0x0EBA9DBB3670E874ULL, 0xD680913B3B67D300ULL, 0x40D7F41081D52634ULL, 0xB3EF30E9D2CB8B48ULL, 
            0x0EE9E96DB520CF71ULL, 0x53B28F0C4003D9A4ULL, 0x0BEC55C389FE15E8ULL, 0x2C800D4212639888ULL, 
            0x598524DC0DC8B77AULL, 0xCD38618C2FBFB4F7ULL, 0x02CB74FF1D2A5447ULL, 0x860D5F747C6D50FBULL, 
            0x7F5B8D35F736652BULL, 0xEEBC2CAEBE0EBD52ULL, 0x3A055057599A47DAULL, 0x87BD3A222234DEA0ULL, 
            0xDC922C9350F2EA2CULL, 0x4F1BC85363B922D9ULL, 0x680F234AB2F7380AULL, 0xAAB935547975535EULL, 
            0xBD6D2F637C72D9D7ULL, 0xA02D0A82B164A98DULL, 0x4B260FDC840CCA18ULL, 0x1D735FB1B2894E10ULL, 
            0xF53E66173F4C68CBULL, 0x8AE5343A378802EDULL, 0x1FBD4A7B5DD2DD85ULL, 0xD71ED431EEFB28FEULL
        },
        {
            0x72C84D16348C705FULL, 0xB667A3CBB43E23BAULL, 0x83B34BFB1D9E04F6ULL, 0xBD56E8338799DF52ULL, 
            0x45175BB4C632A908ULL, 0xFCD3D984F9EC333CULL, 0x0BAA2D38A6A2F7ACULL, 0x5827C50AADD670D8ULL, 
            0xA947101E7642D971ULL, 0x12C23A10DC5AE64DULL, 0x3A7A0BD19F715C8AULL, 0x8324BF1539573C29ULL, 
            0xEF08E6A48B4C4E55ULL, 0x8AE71E3E1DEA2FCCULL, 0x3668CA30769AE222ULL, 0xF803B77478AA6D91ULL, 
            0xBAD8AD7693BC38F2ULL, 0x54C8923B4E0AE770ULL, 0x2237738AD3512E9AULL, 0xD2368BADC4935BF1ULL, 
            0xAD4414EDD784CF37ULL, 0x8E9BC85ABF19050EULL, 0xCA81152B8285E84FULL, 0x0326519B48A3EBF7ULL, 
            0xDC61319A6D4BB9FAULL, 0x63E2F104565A5EC0ULL, 0xB874DF52B3440544ULL, 0xC5369DAF05DCF081ULL, 
            0xAD4F151838A5BE35ULL, 0xB13641DAB73D2F37ULL, 0x86CD825703039B67ULL, 0x9F8802BD4C37B9A9ULL
        },
        {
            0x5F2EA357D2DCD321ULL, 0xB0ED49C56610849FULL, 0x942DA4BAF00D56EEULL, 0xC7B05265F58AD10FULL, 
            0x1A6AC8674F22ECD9ULL, 0x0B5F9A14FE59ABFBULL, 0xF87C79A11F28FCC8ULL, 0x9B97C0C79426E81BULL, 
            0x3BC4A80E3769D341ULL, 0x009C68C5C116E9C2ULL, 0x7BBDBF3D4B08ECDBULL, 0x8C994641706C5865ULL, 
            0x4EE8104EDC0C6B40ULL, 0x112BACAEEC0E5424ULL, 0xCFBEA5D22E9E6CCCULL, 0x8A017D06F322F0A5ULL, 
            0xA5EA3967079E58F3ULL, 0xDAF5FA04C2E176DAULL, 0xFCE10E5E5ADFAFC7ULL, 0x43AC17DA885DF6B1ULL, 
            0x34047A87BECA5048ULL, 0xE8C11903D9D8723CULL, 0x129A2CE5849AB370ULL, 0xFB86C4D81F8F2608ULL, 
            0xA39EFB23CD55C63BULL, 0xA2E5839442CA1322ULL, 0xB6A4C8FD21E67A09ULL, 0x114DD39FD81992CAULL, 
            0x987596C3E9433392ULL, 0x211862DF54CCD683ULL, 0xA72248BFF9C11A34ULL, 0xA2BD5D52C4D3883EULL
        },
        {
            0xF2C1A3AA5A9870B3ULL, 0xFC77DE754C258917ULL, 0x9D43441BCB8ABD41ULL, 0xCD997B9AEE889D08ULL, 
            0xFC016C72BBD49E68ULL, 0x1D3128EF7B29C0D3ULL, 0x2C4F0F34401E2A14ULL, 0xAA5ACA6136A1F364ULL, 
            0x2A59DC00335BA8BBULL, 0xCE75BA88BC7FEAEDULL, 0x722AD02EEBE06095ULL, 0x6E41A0D0B0FB1546ULL, 
            0x5BB33FB83570AA36ULL, 0x4C7252858C2AEFB6ULL, 0x0D16DB824E0352FEULL, 0x127AEF2C0F15B942ULL, 
            0x1490B0F4C36E18A6ULL, 0xD7300C81E796AB33ULL, 0x221D31B0CDEC1763ULL, 0xAC29E3BB3DC0A7E2ULL, 
            0xA46797FEC5418AB2ULL, 0x61A5A39037E2A004ULL, 0x56E0EAC5718F1E78ULL, 0x7C313DFA2A0386D4ULL, 
            0x2DB9089A0EC57C60ULL, 0x6640D15E2BF30C8BULL, 0x9E6AACAB99D7BBC4ULL, 0xEAFC3BEEACB9B023ULL, 
            0x1AEE136239D7C016ULL, 0x8065E660E20C5E94ULL, 0x708E411C80E993FBULL, 0x71BE3B388D90B49BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseGConstants = {
    0x6EEAE2265E600BC6ULL,
    0x9FB4F47A7A927409ULL,
    0x76CC6D84B65BB07DULL,
    0x6EEAE2265E600BC6ULL,
    0x9FB4F47A7A927409ULL,
    0x76CC6D84B65BB07DULL,
    0xD065BDB8764CAFDAULL,
    0x33910F2153447632ULL,
    0x47,
    0x21,
    0x70,
    0xDF,
    0xC7,
    0x7B,
    0xAD,
    0x33
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseHSalts = {
    {
        {
            0x21D0E991B771BC4AULL, 0x2EF96524C4691774ULL, 0xB5CB7837B5840C5BULL, 0x473505ECB6FF046BULL, 
            0xEC2ED5E934090B03ULL, 0x4A0DB0C0AE296418ULL, 0xF26A14810447D335ULL, 0xCEB6080C6FD8F7F4ULL, 
            0xD16924E2041B6C9FULL, 0x0059853EF0A27B9AULL, 0x1A9012CAEDBCE40CULL, 0x7CDF206DD9A79BA7ULL, 
            0x8D61BB78DF776DA1ULL, 0xA59FBC9F9B41ADB1ULL, 0xCC2D347CB0F288A4ULL, 0x7DCB7FE6CA578DA1ULL, 
            0x247C8914B4189EA5ULL, 0xE76D5057BC6C6CB8ULL, 0xA8C6420721DFA138ULL, 0x32B1A156AE36FD1FULL, 
            0x24DB9E46DF9E5032ULL, 0xE6451614E90E4747ULL, 0xABD8503906B553C5ULL, 0x6E567183245035C3ULL, 
            0xDB2B822823DA155FULL, 0x342C4F182B51DCA8ULL, 0x3347DF811FE8255FULL, 0xFACB569949965C8FULL, 
            0xF3D94A9A31DBA7A7ULL, 0x18161FCD3052B527ULL, 0xF38E09B74675A418ULL, 0x82B2585A7278D1C4ULL
        },
        {
            0xABDB50438F08AEDCULL, 0xB6C17AC3C1603060ULL, 0xD7577C32775190D5ULL, 0x309E6D7C288CA688ULL, 
            0x53B823A2D229C315ULL, 0x9AC32DAA6672F8FDULL, 0x78357918B75112A0ULL, 0x8A1F73AAB5D6FB10ULL, 
            0x9E8CAA8DF8E15F2BULL, 0x161950EC82135E1CULL, 0x6BC643F4961DC143ULL, 0x586A341C6E0CF639ULL, 
            0x9C98C86F6CF222DCULL, 0x2AC44B5135F289D1ULL, 0x97C6C6DF609E764AULL, 0x8006D47F9EE2947DULL, 
            0xEEA48B05699701DDULL, 0x76CE08548ABD8890ULL, 0x3981BB95EDA38FE2ULL, 0xB4C9C8157594EF5AULL, 
            0x3FF2610458118AE9ULL, 0xB10F7DF66752F7CAULL, 0xFEFC05CCCF167B12ULL, 0x0FC66FF72BBA83A5ULL, 
            0x0F17FD3993ABD478ULL, 0x525FA9D56F43018CULL, 0x4CCB03F7D0B1FB1AULL, 0x1D7A67C8865ED957ULL, 
            0x9A76DA86DF213E0DULL, 0xA1DB3BBC1C61FDABULL, 0x107F211210B092C1ULL, 0xAA5FC1E0BB066F3AULL
        },
        {
            0x137DC8CD2342445CULL, 0x5E15EA5B31550B81ULL, 0x3C3978161F050B24ULL, 0xC9E8DEFC753AC39AULL, 
            0xA823A9B0ED91CC4CULL, 0x74019A4DCB0C4E18ULL, 0xD4D34A7A611A83FAULL, 0xE72D34A3667D7C2DULL, 
            0xCB7AFEA835CBC7BFULL, 0x9C21DCC0B2E4E5D4ULL, 0xF53507014C062D11ULL, 0x3CDD4FCEBE79E79FULL, 
            0x6122CB3B728214EAULL, 0xE057D61F86A255ABULL, 0xE1D3B3BDAA8F73FCULL, 0x913E727C6813DDDFULL, 
            0x6F861D7E8FA83182ULL, 0x194C347E59B6640EULL, 0x1C1EF1222224D9EDULL, 0xDF999E80EBDDE4B4ULL, 
            0x2EC813E014246D68ULL, 0x41E40426F95D25C3ULL, 0xBE3405D158F6CB46ULL, 0xBB210C77F62491DCULL, 
            0x8450A45550020FD3ULL, 0xD54B182531357216ULL, 0xA042F03FB20CBCAEULL, 0xC0E1049E2473DFB2ULL, 
            0x4837D9D2D9D560FCULL, 0x0F0469A9EF1E41E4ULL, 0xB70130547223624FULL, 0x6921516650E99D10ULL
        },
        {
            0x4AFF76FAF91AE452ULL, 0x98A3A1B90F116BFFULL, 0x3453D4A2399B9484ULL, 0x393B62B54476843AULL, 
            0x02ADE1F7608A6C96ULL, 0xD091AA2E4D2F70E2ULL, 0x05B816E068986B82ULL, 0xDCD09EF6A0B3666BULL, 
            0xEAFF77864CF6040BULL, 0xB7DAEF170E3CF4C6ULL, 0x8B5481D11CA3D97AULL, 0x9504E7CDE5B7546BULL, 
            0x905DC2F9753D28ABULL, 0xF9721798EF029B55ULL, 0x3D1BF41AC9A7CB19ULL, 0xED417B3A67446583ULL, 
            0x6925BC8DC0A4F02CULL, 0x2A15029DE938BE05ULL, 0xF4D6089FC12D7EE3ULL, 0x733C0E5BF66CFDBEULL, 
            0xFAD7758E727F3C7CULL, 0x2C337A45662059A3ULL, 0xA8866A9CA7F92B5BULL, 0x4E5987210CCD7A4AULL, 
            0x624DC0FBE1885101ULL, 0xF6D84A153DD6AFBBULL, 0x5B3434720A971DE5ULL, 0x8E311F01A14B434EULL, 
            0xA1DA81B41A6A6E8AULL, 0x95549A15B707FF26ULL, 0x9E639ACB98485AB3ULL, 0x0AB463DA2D7365D8ULL
        },
        {
            0x06B1AB9C2F93C2B5ULL, 0x8B3F3AC5CBBEA551ULL, 0xEA134AAC8E48A0A9ULL, 0xAC192464D9D072E8ULL, 
            0xDCA0F28AC7755EFEULL, 0x3FBDBE32D1E56F9DULL, 0xA34ED582DE212948ULL, 0x35ABCC148DCFD28BULL, 
            0xB8A8C5682DFC12AFULL, 0xB5847F040051096DULL, 0x38E49A57719C1490ULL, 0x7EBE5B5DA578B3DEULL, 
            0x6EAAA7276A41BFBBULL, 0x1315688373C606DDULL, 0x52A860DE4708B66FULL, 0x4F18CB2580C53596ULL, 
            0x48F3FEC81E5C507EULL, 0x3673EA8CDAE580DAULL, 0xEC315A0384EBC219ULL, 0xA458E49E8E7524ECULL, 
            0x2B6D6138D5FE762FULL, 0x4CCD79943FC203D2ULL, 0xFF20BA06F5E93BA3ULL, 0x18DE27CA6C013809ULL, 
            0x14AED46477927CF0ULL, 0xA40EAB46A4E3FDC7ULL, 0xBAAABB5EABD691B8ULL, 0x4C88C826B40359D6ULL, 
            0xCED21462DC110A9BULL, 0x8A9A8E4F5E4ED798ULL, 0x022AF5F98F3CFA20ULL, 0xF8383AB82BE25C4EULL
        },
        {
            0x007B49366A71D6B4ULL, 0xD555B27876439801ULL, 0xA3070328341C1F27ULL, 0x9A1C8092ADD95C8DULL, 
            0xAC9C98B58C930D8CULL, 0x62C16F448CE3673DULL, 0x2727ECDE5114AAD2ULL, 0xF8C27D1B27F66C41ULL, 
            0x220DDDC7224E6695ULL, 0xACB667368660CC81ULL, 0xBFE91BF1F48B3AE4ULL, 0xD4B254119A724320ULL, 
            0x497AB7A70FBF090AULL, 0xE19A9D630FA63BB5ULL, 0x8DCD4660305144A2ULL, 0x67B69FC208094CF6ULL, 
            0x6BC169314E03C0E4ULL, 0xCFD6F2C17854FFB0ULL, 0xFEE7CE5965106909ULL, 0x989D2B76A54A26D9ULL, 
            0x75F2D9A1BBCD260EULL, 0x9F0880F0501F916DULL, 0x550BFFF14001EBBFULL, 0xB2D7FDA287C4D2B4ULL, 
            0x853BDE0547DF87E0ULL, 0xBF7C0D9066A3D22CULL, 0xBD55AE534EF254D6ULL, 0xCA487B5E729A005EULL, 
            0xF16F379F4FCC0E2AULL, 0xE49A51645B147757ULL, 0x7970A64ADC966E88ULL, 0x92262F865F8EFA6FULL
        }
    },
    {
        {
            0x79D0660D9A365494ULL, 0xD97C8423D6E66E20ULL, 0x0D1100304F20F546ULL, 0x8DE2C196CE188E85ULL, 
            0xD2E444AF7DA9F63FULL, 0x7FB192535D9220B7ULL, 0x3DCAD3CDB74D7747ULL, 0x49D6BA831AA1EB97ULL, 
            0xBD76B006AD91309FULL, 0xB979F659862889B8ULL, 0x37623AE2F99CB45DULL, 0xCE8DB14D10683374ULL, 
            0x9E3077A5BC6AF1DDULL, 0x520598916A94B7B8ULL, 0x0226C9A0D1ECEF66ULL, 0x8491F5B6907530F3ULL, 
            0x382B954900F06B0BULL, 0x842D911960D54890ULL, 0xC6CDFE44066E6AADULL, 0x4FCEB9F86AA30FB9ULL, 
            0xB51EB55AC9097F40ULL, 0x01ED03415ACC9E08ULL, 0xA8A76E38EEB15A72ULL, 0xB2F9446D9780CAD5ULL, 
            0xD77383B8D5EAC21BULL, 0x320DF6793634E4F6ULL, 0x99681727A8D9C6DDULL, 0x3B0830743F9FCBE3ULL, 
            0x356E92D2F2F849E4ULL, 0xD34A0CBDBC6D3DD8ULL, 0xB35B8F1A3DA37DDDULL, 0x02E583488E78B98EULL
        },
        {
            0x02007A3FA7C88BA1ULL, 0x7A010DEA4D937601ULL, 0x12DBB976E3BF9C16ULL, 0x89AB2A26210AA5D9ULL, 
            0x444C3F52EAA09DBAULL, 0x58F6E0805210EED2ULL, 0x3185EABD6DA2E285ULL, 0x4104FAAD4FBFCA26ULL, 
            0x4AF33B5EA7733128ULL, 0x35291A41596111B4ULL, 0x6F99CE449D0701F0ULL, 0x76D2C4BD9C682DBAULL, 
            0x0EBCF8B34084D8A9ULL, 0xCC3C5A1E7AF88784ULL, 0x75EBB5B618B59071ULL, 0x352A4E0269D78881ULL, 
            0x20075F703C5EFD6EULL, 0x67A5D02771621779ULL, 0xCEF630009F600C32ULL, 0xEDAE1CFD66A2FA13ULL, 
            0x964FF831FB18E4D4ULL, 0xAE61DE960F0BC340ULL, 0x2BE7AA52C2953028ULL, 0x62125D219660F8B4ULL, 
            0x58F5EB0AF73F8C6CULL, 0xB89E26E7E3DC8017ULL, 0xBE51E0B0EE953FF5ULL, 0xB3CD654FA0808D29ULL, 
            0xB7B06A7C56C62D4DULL, 0xC6A888CAC6F1ADA6ULL, 0x7C4000FD51B260E9ULL, 0x85E4F59A8FBDFACBULL
        },
        {
            0xB4E1076A8D47F3AFULL, 0x2E3CE70D75E725CDULL, 0xB06457D267533E37ULL, 0x25DA68B504C5FA35ULL, 
            0xF6A9EBDDB50784E1ULL, 0xA8B89F8C0EA65E99ULL, 0xB24720D5208564C5ULL, 0x82896C6A32015604ULL, 
            0xF4BE040D3A78D41AULL, 0xE4D7425299FE844DULL, 0xF3C17DF30029B809ULL, 0xEF8769E38D5934AAULL, 
            0x1A6A2FF8F57C53E5ULL, 0x122CD6B3E1093B72ULL, 0xF4C808D13F02679AULL, 0xC0EE46E3EDB13899ULL, 
            0xA6698FE71AAA5522ULL, 0x3DE8A7E75BB343F3ULL, 0x6986D6F808D5457DULL, 0xA57F9B5838FB3F1EULL, 
            0x8C9BDD1CD56F542FULL, 0xD365CAAAD237676AULL, 0x13C605612644F13DULL, 0x04AA6BD4A294BC68ULL, 
            0x139349F9B3E6FFEEULL, 0x0C5F0D4BE76EA992ULL, 0x87D4B117F348302CULL, 0x84F926BB2754A633ULL, 
            0x13853EA9F4D1FB17ULL, 0x59ACD087E7AAC93BULL, 0xB2DD81C5B6A859AAULL, 0xE57CAA32A1E41257ULL
        },
        {
            0xDAA662D6408069D0ULL, 0xA0394B7AD0CECFEAULL, 0x594A6DE05514A999ULL, 0x891F9D4A806BE19CULL, 
            0x6C4D70FE745F63CEULL, 0x19E32C1BF458BA93ULL, 0x125EABCB040115CCULL, 0x7FB5B5F97F9748A4ULL, 
            0xC9EE69B7B06525ABULL, 0xE8BBCEF2A637FDD7ULL, 0x311574D81D4A15F3ULL, 0x5B2838B32D09C3E2ULL, 
            0x714EE631862180D3ULL, 0x55F0F8D6532AE5F8ULL, 0x7A175711B0555A5FULL, 0xA4697B9F694A8E9DULL, 
            0x9D0FA629D40979E5ULL, 0xCA6846CF06B7AC57ULL, 0xD9E57AB263968BBCULL, 0x4D20925A4849E047ULL, 
            0x903EF197472EAC84ULL, 0x73D77D7D4227626BULL, 0x7DD6D61A1539D64BULL, 0xFE56668B4F7AC56BULL, 
            0xA90D885BB0DA7CB1ULL, 0x3A88E415AD811258ULL, 0xC7269C487114BA21ULL, 0x71AFBFC0149D81FCULL, 
            0x74509F9220CA7398ULL, 0xD1B5E33E339EC686ULL, 0xC0052C1102E104D8ULL, 0x05907F505420B1EFULL
        },
        {
            0x70758A3DA307C3A2ULL, 0x479041A9320205C8ULL, 0x0FC1052340161A24ULL, 0x17BEA6A5D4FDCFC6ULL, 
            0x1B03BABD4863E5E6ULL, 0x52E3A2D30417E2E5ULL, 0x50B48F478B00CAE4ULL, 0x0FB4186488B44F34ULL, 
            0x92F7074201157F22ULL, 0xFFCBEFD925913329ULL, 0x3020956B0F7CBC8BULL, 0x49A952325DD59638ULL, 
            0xA5F62599597D2B16ULL, 0x6F9603F3E7355E8AULL, 0xC875AC4241EB4ED9ULL, 0xCCC500B88455D934ULL, 
            0x735897D4615D4A5FULL, 0xBD65DC6E2F88F2A1ULL, 0x828E048DB03CED67ULL, 0xFC8CA2FCBC531623ULL, 
            0x3D4F3F57EE35AB0AULL, 0xD1C49E7C90ABEB38ULL, 0x56F902C4BBB5A34FULL, 0xA0730812944043D2ULL, 
            0x16A1FF9FB1642B23ULL, 0x28ECDA29B54BA08EULL, 0x31D002B32B108029ULL, 0x774094C6ACAC89A1ULL, 
            0x7151CAEA3ED25DABULL, 0x723A367A6100765CULL, 0xDC28799612E4C9E1ULL, 0x6D097ABE13BAE989ULL
        },
        {
            0xD9B6EFA5251DCBDDULL, 0x424359B0294AA711ULL, 0x37D6676773870723ULL, 0x71138F43CEC4F35FULL, 
            0x54D6F903F6315749ULL, 0x5AD25C9CF42F1485ULL, 0x326A7CDB5C08E6A3ULL, 0x6B005DB9F629EA7EULL, 
            0x90D86D3F84783939ULL, 0x5CF6052187BC4C83ULL, 0x3C766E638F06695EULL, 0xED237EB658063A33ULL, 
            0x5BD2DA61EE83F505ULL, 0x49B5F0818239ED77ULL, 0x24783D0880B6099EULL, 0xD0A8B96BC82FA3CDULL, 
            0xE9A478DFD9B0F0CEULL, 0xEB13C3AF3438798DULL, 0xE661D7BD5CED16ECULL, 0x0034FFD142B55A5FULL, 
            0x24436DFCE19E4945ULL, 0x72B6BD17F44A589DULL, 0x0D843F34BC0B58E5ULL, 0x5AF68971FD90D157ULL, 
            0xC0FFCD7826A400F8ULL, 0x622F2FA14CBEC685ULL, 0xD8BBD251B8996259ULL, 0x7C34BC96BAE0415BULL, 
            0x5F30A294873A471AULL, 0x1338AD8E451B09F7ULL, 0xC128731ED364F305ULL, 0x2A66FD2480EA7790ULL
        }
    },
    {
        {
            0xA5E0B36016692F16ULL, 0x8B57F1C9DD1AE7D5ULL, 0xDA08AB6FCCEC58E4ULL, 0xA8324625A92E97ECULL, 
            0xEE3320EA8E06E59FULL, 0xBCFA37D4AA77DC74ULL, 0x18676ECB05F39AB2ULL, 0x2F53C47E5F6CBB4DULL, 
            0xAFC18182DA2715B6ULL, 0x6E44D01C67E2DFF3ULL, 0xE3EBD07D43F0AAA0ULL, 0xB384D50CE0AFC842ULL, 
            0x764F599908D5FC4AULL, 0x3BE2E7FAE4AEE6C1ULL, 0x6B23937C3BD05006ULL, 0x9DF1B4310399B6CFULL, 
            0xA7B01E4FBE0A1139ULL, 0x0A2E95B8AB289B65ULL, 0xE1830AD83A48672FULL, 0x61A2627846F2423FULL, 
            0x3090EF1EC9ED5E01ULL, 0x84EEB3A0F9037977ULL, 0x0AFAB8979C776C10ULL, 0xAF3F4242A9EA730FULL, 
            0x87F6E43BCD511EDEULL, 0xAD57F923E9107D78ULL, 0x185FF541341249CAULL, 0x785013287C7AAA89ULL, 
            0x3DF77C4F873B9467ULL, 0x1C91B00AC3CE77B2ULL, 0x95631DA7DA792A5BULL, 0x31BB9BD61D7ACA59ULL
        },
        {
            0x5029DD612054C883ULL, 0xB53598B456629D58ULL, 0x103A699341595FDBULL, 0xC5D2B8558D62AB9CULL, 
            0xDAE4C938A86BCEFBULL, 0x520064BD0A63B167ULL, 0xFE4F45115F289CF8ULL, 0xD30CB5961A7E1139ULL, 
            0x0F247C1081362FA3ULL, 0x7445D202514DE378ULL, 0x3623B37DAB37CC10ULL, 0x21161C231C451EAEULL, 
            0x03AE0357F4962340ULL, 0x030298D669A607C5ULL, 0xED16BF884D470E40ULL, 0xD0DD8E6CE3718D06ULL, 
            0x9E3CF621EEB59594ULL, 0x701D1CF76CD2111DULL, 0x236961141C510116ULL, 0x88259B74845FD6ACULL, 
            0x836EF5CA7F8C2187ULL, 0x2CBFC1120BDE0EFAULL, 0x854D526E5A18399EULL, 0xD65A6C6B43D5FE1BULL, 
            0x3F7CCFD409D833B3ULL, 0x44A5CAA7639B54B3ULL, 0xFD605E1EC38C6D29ULL, 0x3D96BEF190D7E626ULL, 
            0x897FB7EA338C8BD5ULL, 0x9854E75502D90459ULL, 0x7E2AA965DDA3903AULL, 0x66B503932D981D29ULL
        },
        {
            0x261C770B46DE6D37ULL, 0xA0A112D1432E8314ULL, 0x5DE0764E58E8008EULL, 0xD035D8D6577CE763ULL, 
            0xEFA4CF31404B192DULL, 0x97864BFE6D96D06DULL, 0xF838AB7BD6F321F7ULL, 0x7F599AC5CA17A21BULL, 
            0x194CEF97D55480F2ULL, 0x44B026645FEC3449ULL, 0xE26E38E321868231ULL, 0x36BFC539F26C7265ULL, 
            0x7C8A978D29177965ULL, 0x3F743CE0180219FFULL, 0x49D741D67E883735ULL, 0xDF44572E45D9BFADULL, 
            0x4E76363A6D8D14CBULL, 0x8C3013F5B9023460ULL, 0x075C281644C03201ULL, 0x4468D655F8A39A01ULL, 
            0x2ACCF7B9AC8C7F53ULL, 0x52C66E019DC17301ULL, 0x00648A41E955A998ULL, 0xD75C6C96ADFE0A6FULL, 
            0x74C6880C7273084EULL, 0x621751D5D9D5CC11ULL, 0x2CDF213DB166AB28ULL, 0xFADA2DDF63A80D85ULL, 
            0x10622F72D48F3495ULL, 0x063B260FFC76B24FULL, 0x33B335349BBE1E80ULL, 0xDAAFFB620BBBE86AULL
        },
        {
            0x2FEC7B19777B4CBFULL, 0x2219ED5A924A8DFDULL, 0x34A9E096F78EFCA1ULL, 0xD2DFCDA09AB6CDA8ULL, 
            0xFBE54D0994C632AEULL, 0x94F1E227D94FF340ULL, 0xD3D8199A742D9E69ULL, 0x02F88DFA7C621FA4ULL, 
            0x3EEC9C21168AF355ULL, 0xC6036851997FAE29ULL, 0x20DA70A009A719C0ULL, 0x232344E36005C3B8ULL, 
            0xDDD7B03B89CD7DF0ULL, 0x72A46C86B39EAD83ULL, 0x5FBAF5C31B13C05FULL, 0xE5A890E38D99251AULL, 
            0xA51DAA35560DAA25ULL, 0xA90FEEDC15C57AD4ULL, 0x8519953F0C556542ULL, 0x452D5EA32AAFB9A8ULL, 
            0xD82049B2FB7B212FULL, 0xEC62059EC6B261E4ULL, 0x7F0B87DCFFA008F7ULL, 0x8F5AA6247CC05358ULL, 
            0x95EF9F38D21BA34FULL, 0xFB47F5069F7EE1DDULL, 0x75649D7CA8AD487AULL, 0xD62FB78C97179BCEULL, 
            0x62A40DA4410E3B03ULL, 0xDECBC1286DBA63C2ULL, 0x3FDAE1F026FD1D09ULL, 0xF909C5AEF3CD10DEULL
        },
        {
            0x57DFED474E67A831ULL, 0x0B941FB577576722ULL, 0xEEED382C1BA025D0ULL, 0xC458A8936C885B8AULL, 
            0x94CC685E02580BA1ULL, 0x04997573ACA2F1E8ULL, 0x974AD17240E90C41ULL, 0x1042D653BAA6093BULL, 
            0x4D3D931328CAD963ULL, 0x54C56C12344C35A9ULL, 0xEB4754E701A3B60AULL, 0xF70016C31348A894ULL, 
            0xEC4B068C831C276BULL, 0x5D0BC8C4D040F6ADULL, 0x48FA580605F351E4ULL, 0xA67B0EA3EB8E74A6ULL, 
            0x973325024205559EULL, 0x0DD6EDE4CD93B053ULL, 0xDAE4AFBA98A10EA6ULL, 0x1B60A1A97B48395EULL, 
            0xD57213895A4D1418ULL, 0x1D6E437F646770A8ULL, 0xCAD8B17F5C926B7BULL, 0xFE900823677389E1ULL, 
            0x0A1F87EA4E98E5A8ULL, 0xAEF4BEDB11E9AA80ULL, 0x43E2024BF8F3BAD5ULL, 0x5BB67154F932C1D2ULL, 
            0xF81507EDE3CF76DEULL, 0x07F770F16B8F70A1ULL, 0x6E79CAB7FE781EDCULL, 0x159A45CABBD4A0BBULL
        },
        {
            0xF16268AE9AE9A66EULL, 0xCE813E3D2BB21087ULL, 0x9D379C9293D5259EULL, 0xBD4E9C8E6DE548D4ULL, 
            0x4FBA641ABAB9E4BDULL, 0xA83B48DA4C3B43A1ULL, 0x1BD23C44389A420CULL, 0x35E048560003A819ULL, 
            0x1B466A52CFFECCEAULL, 0x1007FA24CCA47439ULL, 0x2BE70DC386019748ULL, 0xBF954E8D51F1E248ULL, 
            0x5D1EAFA30E53C321ULL, 0xC4AD437D0E93AEE7ULL, 0x590FD5E911FD1030ULL, 0xB8D8DA605EFDA33CULL, 
            0xA700D0758803642EULL, 0xB66A8B085A53907FULL, 0xDA7D4279080149CBULL, 0x106912CCE85B9E35ULL, 
            0x54FE93197E462ABFULL, 0x7550E4FD78487F84ULL, 0xEBFAEA9F26E9B098ULL, 0x3063B25BF8762539ULL, 
            0x6978526520DA79D9ULL, 0x2C91B426ABF08C1FULL, 0x239D5C2E66FD48E8ULL, 0x5D7E97E28A450E6DULL, 
            0x02366A348CB8FB35ULL, 0x8BD2430B49645A69ULL, 0x5F007C5CDD7117AAULL, 0x2DF10B2F9C4F3E2AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseHConstants = {
    0x56648B0C1A3E740AULL,
    0x8C19E3CF87CDCF57ULL,
    0xE2DE238AF668321DULL,
    0x56648B0C1A3E740AULL,
    0x8C19E3CF87CDCF57ULL,
    0xE2DE238AF668321DULL,
    0x84ADB59A2A1DD1A0ULL,
    0x57763A52C9567C3AULL,
    0x6A,
    0xE1,
    0x11,
    0x1A,
    0xC2,
    0x0A,
    0x1A,
    0xD6
};

