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
    std::uint64_t aPrevious = 0xCD5762AB0CA1D38BULL; std::uint64_t aIngress = 0xEACA729F94A2C62DULL; std::uint64_t aCarry = 0x9E647A666362E91BULL;

    std::uint64_t aWandererA = 0x9210CC4751E61F23ULL; std::uint64_t aWandererB = 0x8982141CEA117BF0ULL; std::uint64_t aWandererC = 0xAFA3EFD373CC122EULL; std::uint64_t aWandererD = 0xF41450BE4E0D99D7ULL;
    std::uint64_t aWandererE = 0x94D3259ACF7535BCULL; std::uint64_t aWandererF = 0x913CFA2B7654247EULL; std::uint64_t aWandererG = 0xEBC3E3EBE2D7F4F5ULL; std::uint64_t aWandererH = 0xE8A788AAEFE737AFULL;
    std::uint64_t aWandererI = 0xF776EF6115050B51ULL; std::uint64_t aWandererJ = 0xFEFEDE0D76F2894AULL; std::uint64_t aWandererK = 0x8033CC4BBF3F8E11ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16264623167553344136U;
        aCarry = 15318035619971585586U;
        aWandererA = 15083323815371759486U;
        aWandererB = 15840620607542230713U;
        aWandererC = 11016850891087274930U;
        aWandererD = 13845163806749852474U;
        aWandererE = 12389877264419711193U;
        aWandererF = 14349689901385200378U;
        aWandererG = 10750617441966811329U;
        aWandererH = 14216276074527241886U;
        aWandererI = 16952787419391577666U;
        aWandererJ = 12618731662422917267U;
        aWandererK = 15344762942684207422U;
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
    std::uint64_t aPrevious = 0xCE2DC1C04C2A012EULL; std::uint64_t aIngress = 0xD39F318537C1B494ULL; std::uint64_t aCarry = 0x9811A124E1E300E9ULL;

    std::uint64_t aWandererA = 0xCD65488AC652534EULL; std::uint64_t aWandererB = 0xF428BAB900D64806ULL; std::uint64_t aWandererC = 0xF760FA1867201DD1ULL; std::uint64_t aWandererD = 0xB172BC0237A13343ULL;
    std::uint64_t aWandererE = 0xCE5C4EF81C34D606ULL; std::uint64_t aWandererF = 0xCBFAF5973D62DCE9ULL; std::uint64_t aWandererG = 0xDE24A9F708F1A979ULL; std::uint64_t aWandererH = 0xC427F6393DA59A95ULL;
    std::uint64_t aWandererI = 0xA5D70E2B5E54DB60ULL; std::uint64_t aWandererJ = 0xEE75DCF19198121EULL; std::uint64_t aWandererK = 0xE64CB21C0D9B294EULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10618729936096151328U;
        aCarry = 12771130408672949307U;
        aWandererA = 15512184387192239928U;
        aWandererB = 17958722568353942658U;
        aWandererC = 12414442723687080708U;
        aWandererD = 9704355421869312066U;
        aWandererE = 14492417015973121442U;
        aWandererF = 13841160432775704608U;
        aWandererG = 11800890776423736285U;
        aWandererH = 11598741758638081760U;
        aWandererI = 16397239981682914915U;
        aWandererJ = 13657710365417472417U;
        aWandererK = 13758852732657705522U;
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
    std::uint64_t aPrevious = 0xD3E4E5F00A03A1A7ULL;
    std::uint64_t aIngress = 0xC7BB2FCC8A08E3FDULL;
    std::uint64_t aCarry = 0xFBD0457A7ED74BABULL;

    std::uint64_t aWandererA = 0x9FC1F3C8DFA32AD2ULL;
    std::uint64_t aWandererB = 0xC1BEB9DAD336B87FULL;
    std::uint64_t aWandererC = 0xAB9023477A51A8B4ULL;
    std::uint64_t aWandererD = 0xFC25995155C47C32ULL;
    std::uint64_t aWandererE = 0xDCC15550EF510BE2ULL;
    std::uint64_t aWandererF = 0xA04853C0BA5E3B45ULL;
    std::uint64_t aWandererG = 0x9EC85E51A24DF253ULL;
    std::uint64_t aWandererH = 0xE93FAD6444AE7B87ULL;
    std::uint64_t aWandererI = 0xFFDC143FD1877222ULL;
    std::uint64_t aWandererJ = 0x97EC9AACAA3151E7ULL;
    std::uint64_t aWandererK = 0xB0A687B6A6CAF837ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneC, 2);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneD, 3);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneC, 6);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneD, 7);
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
    std::uint64_t aPrevious = 0xDE76D4FD89DB431AULL; std::uint64_t aIngress = 0xA08C75B238AC9B2BULL; std::uint64_t aCarry = 0x96E7370E723F0053ULL;

    std::uint64_t aWandererA = 0xF1434D244DABE518ULL; std::uint64_t aWandererB = 0xF5FC6D6226C5B15DULL; std::uint64_t aWandererC = 0x8548848DF5753AABULL; std::uint64_t aWandererD = 0xD628E9BBC61F1254ULL;
    std::uint64_t aWandererE = 0xDE1E53A14E46BC60ULL; std::uint64_t aWandererF = 0xC051A1970DF6F48BULL; std::uint64_t aWandererG = 0xBDA1F69D6AF60937ULL; std::uint64_t aWandererH = 0x88E02DA13BB0AA34ULL;
    std::uint64_t aWandererI = 0xE687D63D5C6A5368ULL; std::uint64_t aWandererJ = 0xE6160F5670EDE047ULL; std::uint64_t aWandererK = 0xF65FA9602A120C09ULL;

    // [seed]
        aPrevious = 9953953096039496677U;
        aCarry = 10556135635764834647U;
        aWandererA = 15569323299426919450U;
        aWandererB = 11267134197956357869U;
        aWandererC = 13796885296882530198U;
        aWandererD = 12802083420837870715U;
        aWandererE = 13607188350294004358U;
        aWandererF = 17675878377535696558U;
        aWandererG = 14024632044517304974U;
        aWandererH = 17315958044505325869U;
        aWandererI = 12299137772460661158U;
        aWandererJ = 15380024195349597180U;
        aWandererK = 10782148917515478882U;
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
        TwistSquash::SquashA(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
            0xD70145E16E0FACA2ULL, 0xC1C344E0A10CDD3CULL, 0x408A5DF4E9C69F4AULL, 0x6DEF8DE698BA3754ULL, 
            0x566C0E7ACD5A7C58ULL, 0xE71089B0E421B97DULL, 0x68FC7515D32EDBF1ULL, 0x077AB27F7F2FDAE6ULL, 
            0x4A654ECE9148D42CULL, 0xA82246C5B569EE9CULL, 0xAB72BB8DE6CF3BE3ULL, 0x8BB6FC404FE4964FULL, 
            0xE97F0547709E7255ULL, 0xAB5674656695CB44ULL, 0xA946A6675C4EB2A5ULL, 0x059203FC8CE93276ULL, 
            0x813348B8736C5752ULL, 0x17E5F142696EB2B4ULL, 0xD72D1D95E379036CULL, 0x0C2626CB89F67EA3ULL, 
            0x00E62303B92B2DC1ULL, 0xF2BCFEE5A9B267E0ULL, 0x7F4388E5CEA31443ULL, 0x3B5A1FF0C7E41EA9ULL, 
            0x3432B0BA2224CBE2ULL, 0x6A89D6A814C3D671ULL, 0xE73ACF6D783E5744ULL, 0xE16C75BCC7117AF4ULL, 
            0xB583100EEB10C032ULL, 0x80A2C135C549B189ULL, 0xBF0C5DDBE5DFD760ULL, 0x6B3CAF5FF76809D8ULL
        },
        {
            0x26EFEA9C15CAB6F2ULL, 0xA71B6D336CB4D5CAULL, 0x2B551A3B54F74548ULL, 0x65370EB581479F64ULL, 
            0x40EAA4D2FE95E252ULL, 0x34800F12A11C8008ULL, 0x1D7A48FCF73BF4E7ULL, 0x395CB984DDC5A31DULL, 
            0x9BC05010E75B8AABULL, 0x82FC3FE5B053F61EULL, 0x60D476A7783ADBDBULL, 0x8B810FF9D329F865ULL, 
            0x11836B7F73EE8676ULL, 0xA41B8AC2B68A0076ULL, 0x21C7E824CB8424B2ULL, 0x293BA7552BC0E849ULL, 
            0xA8F9F7017453DBE4ULL, 0x57DEE828D8AB77DBULL, 0x549E76A2234F308CULL, 0x78AF574F651604B9ULL, 
            0x858EFDE8A2F3D858ULL, 0x0FBE6C336C9C531DULL, 0x56D54A8183E216BFULL, 0xEB248004C8BE52A6ULL, 
            0x100E28AB7B053BBAULL, 0x6AD93B7871497D77ULL, 0xEBACC1F71837E491ULL, 0x87A27251D53C9E56ULL, 
            0xFAFF5E93BF03A912ULL, 0x54F545440C32016CULL, 0x8B03522FA1FF0694ULL, 0xA6D8F429911301F4ULL
        },
        {
            0x469AE4DC244144FCULL, 0x0525FC9DE4032EAFULL, 0x6B554C3AA205914CULL, 0x647BFECD61446F44ULL, 
            0xFC267194222ECABCULL, 0xA892AB15E70DA8B6ULL, 0x0F596E5C1C9BD032ULL, 0x743C304B50456530ULL, 
            0xE32999DE69AB7BCFULL, 0x37A9E9FB3A43A9D7ULL, 0x59C0C715A0626A8AULL, 0xC002FB00A1C1C041ULL, 
            0x0CC519A0246546A2ULL, 0xD4F7F7E671706FF1ULL, 0x64138C4A95375B1BULL, 0xED3DD1AAEF7BC7DEULL, 
            0x50F894E2D9186531ULL, 0xC7EB314A9D8DDBA3ULL, 0xD2970CE7D0BE2FEEULL, 0x6A254A9B14573E09ULL, 
            0x7A3FA360F6BCB0EEULL, 0x0A12AC6D3A1F8507ULL, 0x4F6FF64B6F9087CCULL, 0x501141D11136FFFBULL, 
            0xE86F1678E3B8455AULL, 0x1EAD5DEE81A026F7ULL, 0xE5FA8B7A6B737CE9ULL, 0xA413E4C6A42A00C7ULL, 
            0x0DC2541A2FD6FA40ULL, 0x6495F6FCE9B54E0AULL, 0xC69472B3701A9EC6ULL, 0x2981347FB9DD0FDDULL
        },
        {
            0xB97CCD57EFAA5F67ULL, 0x70723A5088B3DA89ULL, 0x5248838EAB25D263ULL, 0x55692EEBCD3BB5A1ULL, 
            0xAA778D69AD64ABE6ULL, 0xAA5B24D2ECB9C596ULL, 0xD0BFB0BA10FCE3BFULL, 0xB51B631FEBAEDB6FULL, 
            0x84FF7F62784F7D7CULL, 0xD6D7621DF2341347ULL, 0xA5B32A5516B70AFAULL, 0x57D10E1717D13E9BULL, 
            0x7B8A2D6AE0248E94ULL, 0x15FB98D7A6069F89ULL, 0x23C7F0DD50C1FB29ULL, 0xB345D74DE300B60CULL, 
            0x1F7A304B9AAD6165ULL, 0xA51334D312FBBAC4ULL, 0x2E51CFE152475E7BULL, 0xC3A06A58F2E4D301ULL, 
            0xC8450DA917863861ULL, 0x39B69BDF5F5D9AA8ULL, 0x8960DFFB4CCF7B3AULL, 0xD69702281B013295ULL, 
            0xC05C606D9C2B27EBULL, 0x357556B9CB3738F3ULL, 0x45BA0ACF57A84D7FULL, 0xD866BE33A7577E92ULL, 
            0x2844CB927301D7FAULL, 0x3382AFC4B9948A1EULL, 0xEF7E1D40985CC2C3ULL, 0xC4CE4BFD44C69EA6ULL
        },
        {
            0xEF050C8C18C4DC32ULL, 0x53730091ECB917F2ULL, 0x5CCE26C73DB40214ULL, 0xD2D585AB15E1132FULL, 
            0xF77589B7807D41E3ULL, 0xCA49370B91714C48ULL, 0xA2422E74FE7DAF7FULL, 0xDEB97DF10A052EECULL, 
            0x339766E10BAB2F22ULL, 0x6F75A156ADAFD126ULL, 0x0C054CE7CBE054F0ULL, 0x77840E43873D59FCULL, 
            0xC81F3E386F95B513ULL, 0xD0590728F9D3169FULL, 0x48C7AEB88FAADBF9ULL, 0xBB4B99ABC1AF6351ULL, 
            0xC67DD81851394C60ULL, 0x07C2F1945A321BD7ULL, 0x6F4265D9FAE015B1ULL, 0x6798977547DC80D1ULL, 
            0x5B873639421C22A0ULL, 0xC641B9C8E881DE9CULL, 0xCA7A0F9CB7403B42ULL, 0xA90CEB4D96AA8BC4ULL, 
            0x2947056B7A1CE037ULL, 0x3F019A1756F8657DULL, 0x5267738B0CE6AB49ULL, 0x7C330F51D1649590ULL, 
            0x6B136075679508FAULL, 0x58CDDA4317FD13E3ULL, 0xC9E9BE1431AE47E2ULL, 0x1D8F2A5306DDC73FULL
        },
        {
            0xA4DDEF215BBBFF7AULL, 0xD30008B36E52FB15ULL, 0x9DEFE67F34E7E944ULL, 0x08680021A3DBDACDULL, 
            0x59E81305DACBFEBFULL, 0x0BEC42870E98C387ULL, 0x131FFF74EA88A29CULL, 0x498D345E737B5EFEULL, 
            0x8880F01CE741C55CULL, 0x589799A43F2F9BD7ULL, 0x0E1E49C93600B486ULL, 0xEB6A82E6A4E0FC52ULL, 
            0x527DDD9C1BD11A15ULL, 0x1E18766775B55B75ULL, 0x2B6521694F7E768CULL, 0xE961DBE17F2CF0AAULL, 
            0xB1B519D0E77B8B4FULL, 0xE6728D06CA50866BULL, 0xDAC45BEB519E8B9CULL, 0x1C7719DE33AA6AEEULL, 
            0xC03B8948A49F5281ULL, 0x6C98E93DC506D5D2ULL, 0xB7C0BF262D03F98AULL, 0xB2093A4CA9667BEBULL, 
            0x239171DA32EB408CULL, 0x491D8A79EE7C89A8ULL, 0xBADCE8BC69322507ULL, 0x67B849C27190968DULL, 
            0xB3B2F7D4AE5ED5BCULL, 0xC8CCE42672B028A0ULL, 0xECDCB7A8DBC947FDULL, 0x3D7ADC8E464686F1ULL
        }
    },
    {
        {
            0xE4046E01F1307C40ULL, 0x435D785E91735293ULL, 0x4C2252B984C0DD55ULL, 0xA3D9A9CCB3F20374ULL, 
            0xEACE162F122E5AE6ULL, 0x72A393C3A86398D3ULL, 0xC6F429CD2EBFD36AULL, 0x7A127E5CB3AB9B66ULL, 
            0x89EC57598FFA3FD4ULL, 0x15609FB7F4628322ULL, 0x007AA0E559FF813BULL, 0x2565912FA3A09FA8ULL, 
            0x3664C887947E6025ULL, 0x127EF07320DB49EEULL, 0xCCBA5AB9AACB8EE6ULL, 0xC805B31E4308BFFBULL, 
            0x9ACED96244A84479ULL, 0xFBF0FEAD125870EAULL, 0x0FC4A23C9370F239ULL, 0x3A34502B566DB517ULL, 
            0x534AC05728E64986ULL, 0x7244661AF532A386ULL, 0xB8193EF1588A84A3ULL, 0x91A7C98B6E59EED7ULL, 
            0xD56E7A04A4DA6757ULL, 0xB0C1B1F3F93F81D9ULL, 0x100519B4E747A93BULL, 0x2C1939107E3DA41BULL, 
            0x47AD80B291771CB8ULL, 0xDAF66E5C2FBC66E3ULL, 0x3BFDF7F440AA4006ULL, 0xAFE307B3C3664F73ULL
        },
        {
            0x87C64D8DB7FD3DF6ULL, 0x05CCE99EEDE35BE1ULL, 0x0ADE3CEB5E5C36EFULL, 0xA8B8FC016E391135ULL, 
            0x564F37F812978BEDULL, 0x22912F9F55D70174ULL, 0x0527C70D9C89CBC3ULL, 0x374CCA2B3616A0CDULL, 
            0xFF9CA9DE7DE57F3CULL, 0x4FB6409C5B7D0122ULL, 0x33B171CA7EFE572EULL, 0x85563D20DEA727DAULL, 
            0x2EEA41C2E18FB903ULL, 0x7448454442B6542EULL, 0x18802492AF33D639ULL, 0x30D820C0F21356A9ULL, 
            0x2E98820E2CF10F6EULL, 0x7AAB39BF373AACB7ULL, 0xA8AD8D06275E64A7ULL, 0xA69605006B6804ECULL, 
            0x8DA9F4A4E008D5A0ULL, 0xCB61BE54AFE19656ULL, 0x17D0C24425B843BAULL, 0x74A92ABABD16B683ULL, 
            0x889C9DDB4AC7205FULL, 0x4208BD36DCEC1E21ULL, 0x12C5EEA71FB361D4ULL, 0xAF151B26FB5B0FB1ULL, 
            0x734AB1E3B910D8A6ULL, 0x11E80A266A28B5A7ULL, 0x4BC92D45CE3A3057ULL, 0x56C9937883A7A0E2ULL
        },
        {
            0x3728AF2E8DBBD178ULL, 0xAA04E438B4687A06ULL, 0xE12CA333C522A000ULL, 0x8931008C8A4B58DEULL, 
            0xBBFCC0E951FBDB25ULL, 0xA9E3C79D2AA1F0CFULL, 0xAFA1B993A680578CULL, 0x6EFF82BA2C96114DULL, 
            0xDD3A21CDFE11CE13ULL, 0x3AA49F75289A8E75ULL, 0x1F310192B01DB903ULL, 0xA17DD1FF9F240FEBULL, 
            0x9FCD254B63DCEAE2ULL, 0xC0E15AE5164573B2ULL, 0xFA547FE8919CB4FCULL, 0x97C1252F4619676EULL, 
            0x4782F17BE572A91EULL, 0x22AB2B6A171B2712ULL, 0x03F19AF5B1D5A56EULL, 0xB953BD6D4D95C2DEULL, 
            0xE11626EABC53D346ULL, 0xF392EFDC8FD221B3ULL, 0xF6A2FFC2D22543E0ULL, 0xB8A9E982BE284600ULL, 
            0x400B1B5DF392386AULL, 0x2783D1D5CF119A84ULL, 0x6BE7633A132A2C50ULL, 0xFBB773002B06CCB7ULL, 
            0xB395788B50A906BBULL, 0x9A36AF0BEA7E2221ULL, 0xBF188509B18F8087ULL, 0x87818CB72C95EDEFULL
        },
        {
            0xC2E9915D59E3A8FEULL, 0x5E6BA28FA413B706ULL, 0xCC00C65ACB3C001DULL, 0x8C26EBEE27389717ULL, 
            0x0FFE919A7956DAEEULL, 0x003F95D017607AD2ULL, 0xC52D3FCAFD47288FULL, 0x9C392A08B89CC8D9ULL, 
            0xF201A2A1AA9F55ECULL, 0xE0A1F9EF017AE2E4ULL, 0x0891C85E7F5E8D71ULL, 0x335C1F8AE67234C6ULL, 
            0xEA6808F00A2DFC95ULL, 0x12844D0E60F477A3ULL, 0x1AB9F40BFE83BA12ULL, 0x4B554538C20059ECULL, 
            0x0C4AF3EBFF3FF859ULL, 0x06921F7BBF8B0EFEULL, 0x0BFA0391F84E58CAULL, 0x0A1998219E2AE418ULL, 
            0x3EA391180CEFF0D3ULL, 0xE0C009BD8E69BC89ULL, 0x878135A4318992F7ULL, 0x30AE43FA646ED3E8ULL, 
            0xB8334D275CA11678ULL, 0xBA06972F5EF13F7DULL, 0xC1CD455008904808ULL, 0x9C3A3617C9846FCDULL, 
            0x93CB1081B88D4646ULL, 0x2CBEE748B0944EC9ULL, 0x705ECC563A75531AULL, 0xA409D515452A2A8BULL
        },
        {
            0xBB09D261A148AB06ULL, 0xB70B988E3B7C0C96ULL, 0x74A2455FC3EE5227ULL, 0x5FE945553C38F522ULL, 
            0x4777FC26F69276FBULL, 0xA673CA99E37381B7ULL, 0xF0027A6A6611F5F4ULL, 0x9084A2C25B7DDD02ULL, 
            0x1A3ADCAAF6EDB57AULL, 0x7CA74C699F9FAA44ULL, 0xAABE70BCD56B8341ULL, 0x5DEAF258CECC4284ULL, 
            0xA90D9D9033C9750CULL, 0x715B683A09B0B9B7ULL, 0x89F44BE7E5157108ULL, 0x1F6B19802AB157F8ULL, 
            0x621C4BA8073CF9DBULL, 0x1EAA250C9E350709ULL, 0xA137E49304E69CEFULL, 0xCB47D59EE56DDC37ULL, 
            0x7CE1266DD420CE02ULL, 0x6CB561A40FF3DFC3ULL, 0x8F859351D8AD02E4ULL, 0x7E171E0D66CF0A62ULL, 
            0xEF5E0E056EDC01D0ULL, 0x7FFEE26556D05C0DULL, 0xC1A2E98035C2772CULL, 0x7CB6EF3093EB5C48ULL, 
            0x8A575664BCE92C31ULL, 0xD9271D7C491F9FDDULL, 0xDC7159CC23203430ULL, 0x89812886D32DFC81ULL
        },
        {
            0xBCCA3A1B913B6DB2ULL, 0x000D19DA6FCAA8D6ULL, 0x429B7D6013685C6CULL, 0x32C615400041D1DBULL, 
            0x326A5DDCF749EFDFULL, 0xE14FF8D6FB0211A8ULL, 0xF4C17945BAD7787CULL, 0x4500550CBB7E9046ULL, 
            0xF3DACBF2A005D053ULL, 0xAD05E5F87E4289BEULL, 0x3056C05E1B967B75ULL, 0xBFA046F6A794245CULL, 
            0x6AED0901D1C299E3ULL, 0x782EDB5950500521ULL, 0x6D6A892F1C9A695FULL, 0x90CB1D94BFCD8001ULL, 
            0xE137873204909512ULL, 0x7798F8A63A1C3A90ULL, 0x8FD35D1F0885BD8AULL, 0x4933DFC325F1EDC5ULL, 
            0x31EBFF32CD614046ULL, 0xD631ED2D7506CB14ULL, 0xB9F2F8DFADC63223ULL, 0x60C18DFF013A3787ULL, 
            0xBB70F7892FB3637BULL, 0x2500CBD75B224479ULL, 0x33379EDA6A426C6EULL, 0xD714AD193487711CULL, 
            0xB73D35066123EACFULL, 0x809A5B563FF5DD53ULL, 0x96D6A8281DAC09BBULL, 0xA2F33EDD4B1A18F2ULL
        }
    },
    {
        {
            0x4CADDD2C012F83FFULL, 0x8EF5C4C600AED4DBULL, 0x552C65B6D7831C4AULL, 0x6B393689635DDFCBULL, 
            0x6C394B7B1EE9B9B4ULL, 0xB92EF8557E5209D5ULL, 0xA1D961843116C347ULL, 0x4BA147C3644672FCULL, 
            0x829991A0939D4890ULL, 0x39536153E61C3D86ULL, 0x49E9E89C6E000918ULL, 0xE76000C78C03F929ULL, 
            0xEDA91893DCF7791DULL, 0xE8611C868124621CULL, 0x901C915E394BC000ULL, 0x65E39983A1F06C0DULL, 
            0x57FDAE28910C8AF7ULL, 0x7633EB96C439A504ULL, 0xC19F1775CFCD2565ULL, 0x32396534805CFF4AULL, 
            0x976723B8D7185A6BULL, 0xFC10B05FC83133BBULL, 0x940A6D5D210EEACAULL, 0xBE0505501D089AAAULL, 
            0x3EC6974594BF321EULL, 0xCF97E0ED463622D0ULL, 0x0155ED3A638CA56CULL, 0x531D6BA96C88A6ABULL, 
            0x6668C6A670B3402EULL, 0xE27FE4D28BF034E4ULL, 0x166C155390BFADBCULL, 0x572401AAD48A0BC1ULL
        },
        {
            0xFFDC00FD00E33F09ULL, 0x911DE2379F41E7A1ULL, 0x8AE868A215580A88ULL, 0x4057D46A867A81FFULL, 
            0xE3067E14ED7B19F9ULL, 0xF6FC5F6E658C71D7ULL, 0xD3E91542BCA09967ULL, 0x82D15F69A1CCC456ULL, 
            0xC8FBEF702B2A05B4ULL, 0xC5168918DCAA732FULL, 0xD8C4E81980DE4C74ULL, 0x34D3A8195736F6E7ULL, 
            0x32820EDBAF99D38DULL, 0x446C2A9A75725FBAULL, 0xBF5D235BBFDF74B2ULL, 0xA1FF7C8ED5111B41ULL, 
            0x27E90098F59A9AECULL, 0x090F37DE0D9B8197ULL, 0xE6F01E66984FD2F0ULL, 0xAE8A1D529E8C3E70ULL, 
            0xDB35D24B4AED3EAFULL, 0x1CC8D120503A4A69ULL, 0x4AB345B3EE4EA15BULL, 0xE4BBECA86F1E48FCULL, 
            0xAFD2893DFE1CDF10ULL, 0xF1C41F51A30C5CB6ULL, 0xAD8AC8BE32AB872CULL, 0x995C34C0DC10DDCFULL, 
            0x584435CD776A56E8ULL, 0x0D9FE3D14CAE64CDULL, 0x351B575C5719BCE5ULL, 0xFF6F446606514F90ULL
        },
        {
            0x1E858CFB848956F5ULL, 0x811AC0D3C9296432ULL, 0x258BCC1BFCE6FC63ULL, 0x9028C2B13A23B477ULL, 
            0x6135C5B7210084F4ULL, 0xA11DCB3B0EBE7C1BULL, 0x5972573AF685867DULL, 0x611928DD2BAE9B38ULL, 
            0x08AC8612DEC9C090ULL, 0x866569FB3F033C4BULL, 0x22236D296D44D037ULL, 0x6B0437418CDD28A3ULL, 
            0x03466CBAA9D582BAULL, 0x00E5C2585CBC9FEEULL, 0xA6B8BB128E92C4FAULL, 0x1E1066CE60A9C640ULL, 
            0x2D50E2F69C03FE03ULL, 0x372E75BB773B2B52ULL, 0xD065BDB8764CAFDAULL, 0x058EE37E23ECD1B6ULL, 
            0x38EB8D47455EDBF1ULL, 0xDCC7A64385906D0DULL, 0xC0D2A345C854AA6DULL, 0xE0F201DCECCC9165ULL, 
            0xA808B1D1D10E92C3ULL, 0xEDD5DBF354A76B3BULL, 0x7C37F154CCFCB5A9ULL, 0xFAB5ED300D6685D2ULL, 
            0x2B40CB1AC17C93B7ULL, 0x9A68E1B32AE5BE85ULL, 0x2F7B0F92EFFF8192ULL, 0x2A45528CCBF40728ULL
        },
        {
            0xF4B5C59558611AB4ULL, 0x34E52A026715D0AAULL, 0x06697C23CE03838EULL, 0xBD68F911076DCE37ULL, 
            0x654A5C0D23FD0CCDULL, 0xE191311567184920ULL, 0xE4EB92E6E61B2C13ULL, 0x004D3E28127AA355ULL, 
            0xA599A6932128DEFAULL, 0x1F49E587B0739A8BULL, 0x5F60CF727CD86059ULL, 0xF01D49B1B468557AULL, 
            0x72D16FFF9EA0E2A5ULL, 0xD6C02B84D89CABD2ULL, 0x37348D28EF624D53ULL, 0xD5C9113049FD9B77ULL, 
            0xCFF664A09300512FULL, 0xC6DBCD3DD7A6A6E1ULL, 0x2C9F38B2305509CEULL, 0xC1A8D63CBC2DCBCEULL, 
            0x7BCFD8516D8A202AULL, 0x45E8830AC3433F05ULL, 0x4BE20EE05802D5E5ULL, 0xCC70300AFC0ADC75ULL, 
            0xF6E2B96AB7F8C65AULL, 0x0465B56A6AE46314ULL, 0x0EF40C491DF9A9CEULL, 0x2C37BD6BAF670B31ULL, 
            0xCA6876D7EB59421DULL, 0xC2C440C79FB57F50ULL, 0xC6A0528C8E028959ULL, 0x7EFC05818553E960ULL
        },
        {
            0xEB90124494BAFBE8ULL, 0x59A4E6EE7EE3AA93ULL, 0x720975E2F9961971ULL, 0x7F6F420AF4502123ULL, 
            0x965DDC7474DACCDDULL, 0x59AFD69FC0E1AE44ULL, 0xF8970CFAC0D1D186ULL, 0xA38CE72FF1FE791BULL, 
            0xE4D376B8DF92C379ULL, 0x85F1AF4B7FA82B33ULL, 0xE68459D5848BD501ULL, 0x5A0F15B66A99B22EULL, 
            0x2CCA4049343C51ADULL, 0xA7201BDFF5967A29ULL, 0xF1B0E5586F420E82ULL, 0x0A06909E3986AE15ULL, 
            0x7F322385F9DB0566ULL, 0x044C968AB86075C5ULL, 0x23847CB796698027ULL, 0xED2D8CD7BF2FEE36ULL, 
            0x5ED34F6040A96E25ULL, 0xFF9524DFCC026A81ULL, 0x0FCEAFD5EB499B46ULL, 0x12CF7B577D8C99E3ULL, 
            0x222A46BD72916776ULL, 0xD6799A7AF82797DAULL, 0x9B5F3E75E9E78069ULL, 0xACF6FD836869B0DAULL, 
            0xDDD5DBB7681410BBULL, 0x1622AA00E007DBCCULL, 0x5ABC79F88F5EB4CAULL, 0x349482ACEC6DE12DULL
        },
        {
            0x30522B2379EF79CEULL, 0xF9AC0B7345674A01ULL, 0xA7391D475E3B8B37ULL, 0x2E3B71062A042EFEULL, 
            0x18C7D93D09EE7A67ULL, 0xBC580839BB5674FBULL, 0x06CC852FEF77F863ULL, 0xDDC39CA4A3D21B97ULL, 
            0x4088BEEC10057215ULL, 0xAF84F3441665A3E5ULL, 0x1273FE3E5FB63FD8ULL, 0xE753A16D61C1A5D6ULL, 
            0x160D02C43A171F5AULL, 0x5541BBBF29CD4C83ULL, 0x79EEB20F98452388ULL, 0x2208CE6D9DF893B9ULL, 
            0x3E3602D69217E606ULL, 0x611E541C2DFC60E9ULL, 0xB8D8E1354A48489CULL, 0xA396D4565239F90DULL, 
            0x4CA26BF845E98E88ULL, 0x558A909138FC8D61ULL, 0xF0FE7824207A94D4ULL, 0x79F907A792BB0CAEULL, 
            0x0C0D1774AE76B62CULL, 0xDE4D2BDCE6B45C59ULL, 0x96304F71665F0218ULL, 0x431EFECF92D8B871ULL, 
            0x74958E627BCED7BAULL, 0xF8EBE2E620346451ULL, 0x1DCB117A4B847F51ULL, 0x190150FF4B2D56AFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseAConstants = {
    0xDD0BE3812B65B2ECULL,
    0x2A0EB4FEEE429103ULL,
    0x2A9EF878EDC9F8A0ULL,
    0xDD0BE3812B65B2ECULL,
    0x2A0EB4FEEE429103ULL,
    0x2A9EF878EDC9F8A0ULL,
    0x5D193DBCE6A1137EULL,
    0x94D21453CF011264ULL,
    0x61,
    0xBC,
    0xCF,
    0x2A,
    0xDD,
    0xB6,
    0xB4,
    0x82
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseBSalts = {
    {
        {
            0x9F0C000A70F1D182ULL, 0x83F14FBE9435AB0FULL, 0x1D8CF3D2B8579646ULL, 0xF9F3ED0DD4A4504FULL, 
            0x4D119D47F5BDB457ULL, 0x4F32133A9CF8A6B9ULL, 0xD8BE20A68859F256ULL, 0x61EEF1EA67445A9FULL, 
            0x98AB59C067F960D3ULL, 0xAA18C04C6F4E1477ULL, 0xEEFB1D56AB6BAB92ULL, 0xD5CB48807211DE4FULL, 
            0x60C484CC05810ABAULL, 0xFD5F73C50A61D43AULL, 0xA884EB145514A35AULL, 0xE7CD5A0BBB41CB0DULL, 
            0x8FD314658C1D6DB6ULL, 0x9942D89626A8A9E1ULL, 0xDE125908AA73185AULL, 0xCBA1CF1C3D5C1845ULL, 
            0x22A7543FF1D62B36ULL, 0x66F5F62D59BD3B49ULL, 0x4B4A58FCDD2ADFA8ULL, 0x99581C258B93B4D0ULL, 
            0xF6E5A66390514B77ULL, 0x4B7728ED97621B04ULL, 0x18A3D94A93839F0EULL, 0x09378697FD1DD7D4ULL, 
            0x0A13ECD922A8F020ULL, 0x60D2F2FC19F039F1ULL, 0x53FCDD85F71FC2F2ULL, 0xBA41BFE41F607F40ULL
        },
        {
            0x39F4513BBAEA07A6ULL, 0xE85954E8EAF3A64CULL, 0x2282904C490414C0ULL, 0xCF656888882D8569ULL, 
            0x15E4FAC2EDF2339CULL, 0x3B3A5E0B0E91D123ULL, 0x86BE4D4BB0184D43ULL, 0x2FAFC7E483350AB4ULL, 
            0x2970D404E84F616BULL, 0xE39909039BA64DC1ULL, 0xB3D070190CEEA40BULL, 0x44B446327661B1A7ULL, 
            0xA2ED37FBD50C5C2CULL, 0x7C4D7FC89A0655EAULL, 0x9E54ECE38B1371EBULL, 0xDD5424E5CA972025ULL, 
            0x3A59548FF21AF05DULL, 0x9B87E34C5AC917ACULL, 0x92858CEDCA9F97BBULL, 0x4641142EA0D7F91CULL, 
            0xEADABF3CD2DDD3EDULL, 0xE31B951ADB6A785AULL, 0xBEC6E17C70562949ULL, 0x7C3DDAD6C7A7FE3BULL, 
            0x8CF40687B9D76988ULL, 0x8E11D2AE49B07D04ULL, 0x2195D73C8C5D8AA8ULL, 0x3ADE2BF385678598ULL, 
            0xE89A71F593DF9A23ULL, 0x6F34B5B2FDC41BCCULL, 0x417F411B39446343ULL, 0xE0415E80674920DDULL
        },
        {
            0xE0F46BA774327F57ULL, 0xB3104C3162DB66CAULL, 0x3908E201018156E8ULL, 0x233B927AE3A3CE56ULL, 
            0x0E032281FC842557ULL, 0x584E8F5687F7D173ULL, 0x229F5CE8214DD975ULL, 0x18C7A1698B27AAF0ULL, 
            0xCFAC57ABF9CB50EBULL, 0xF796AB7B7C1D35FAULL, 0x56BCEB0BD755F125ULL, 0xCE2FBB8CC9853E31ULL, 
            0x98F80329E62D978AULL, 0xC56D0061D87CC793ULL, 0x4FE096BCDE8EEFD0ULL, 0x1A772E710C8B5B13ULL, 
            0x499C7CC69B05F87BULL, 0x1D21FF80FD3AF202ULL, 0x25868F987DDA2162ULL, 0xB32E2DA7AE9FF090ULL, 
            0x6DA5C6CBC6D1780FULL, 0x811B34A7B3866252ULL, 0x1066A70487CFA415ULL, 0x68D4431DD730C257ULL, 
            0x020E57030B934E83ULL, 0x181EC520A39E6121ULL, 0xD8552FE6178E3F58ULL, 0x07BCBCCD70C2CB4AULL, 
            0x72EF0D9493D2574FULL, 0x669C23B12617DDAAULL, 0xF64AF61AFB59DA02ULL, 0x35C64C09853781C9ULL
        },
        {
            0xF4507ABFCB0022ACULL, 0x82299CCDF1DCA2A6ULL, 0x95C5E6BFDBA0C679ULL, 0xBDF6A60855777EA0ULL, 
            0xB5589D7C27A3C44AULL, 0x254A8B6EC18C5079ULL, 0x215299F4DB20CA37ULL, 0xDE8D23C9D0E9F2D4ULL, 
            0xDE447FED17DE77B5ULL, 0xA0BF2884A7106F40ULL, 0xC50DBCA699950DAFULL, 0xABDBCC2576B08D12ULL, 
            0x808CDDAC923F2BACULL, 0xF502ED7A47B579B0ULL, 0x52FC9D1FA0F24866ULL, 0x0EFE562A7BD054D1ULL, 
            0xF34CDCC934D928ECULL, 0x009DB1EF4FC5B8A9ULL, 0xF80B379B96B92E85ULL, 0x0F2D9A47AC252C26ULL, 
            0xC970A7CD29E07352ULL, 0x2BB761A23E98E35AULL, 0xC68E0A19ED9D39EDULL, 0xEE383A0D20513A60ULL, 
            0xF2EB4934E9CD67A4ULL, 0x37C04000861BFB3AULL, 0xD770B2817D3F6794ULL, 0x1F74DC999165C861ULL, 
            0x65BB30182168DB5BULL, 0x5FB18EB5BCC09C75ULL, 0x063D2004ABC148DBULL, 0x02D69495B5B02817ULL
        },
        {
            0xAE6B94145B6BC9B4ULL, 0xDF89665531D0B756ULL, 0xB53896EBA4D40953ULL, 0x9C16211A9AF3A8E3ULL, 
            0x6897C861F8346F5BULL, 0xB236A359226D72E9ULL, 0x7C85F05B9BA984FFULL, 0x52152BA5B57A49C6ULL, 
            0x469C45C511096BADULL, 0x2661883E0E7BDE96ULL, 0xF8F948ECB34F08ECULL, 0x077E762936D04803ULL, 
            0xA0A4C347769903D5ULL, 0x7E1F71526EBC82A6ULL, 0xE1594E777AEDB601ULL, 0x43160F31EEF54954ULL, 
            0x5CA64C77FD368C7AULL, 0x70B60864F7AB45B0ULL, 0x934D64C4C5C01124ULL, 0x7D1C2C6B96990884ULL, 
            0xDEEFBA9C348DBD0EULL, 0xD5ED80F3020E8C33ULL, 0xD17AC8AF1EB16214ULL, 0x085C603FEBF6F292ULL, 
            0x45ABA37D78379C46ULL, 0xB81D721A690DBFC2ULL, 0x1BD6B56CBCA440E8ULL, 0x39197F8CA7491E7CULL, 
            0x56CC4522D53316BFULL, 0x10DB105C315C7383ULL, 0xEF14DA1435E0C3E3ULL, 0xC3FDAC5E22504C50ULL
        },
        {
            0x609685419A6D2152ULL, 0xE298D592BC4A52EDULL, 0x76219B74B0E81325ULL, 0xAA45DFC3A5842B3EULL, 
            0xF72A4107C955C942ULL, 0x813B88B1AB7B27C0ULL, 0x878E944504D03D80ULL, 0x7B3E7124457E98EAULL, 
            0x0C33FC4CE1E31DBEULL, 0xCFA3EA45513D6643ULL, 0x73863E002F6CE331ULL, 0xBD7F3B7727091E51ULL, 
            0x90F95A86CE8EE752ULL, 0x36FED846113DE658ULL, 0x537A8DF85A8E536AULL, 0xFE6DB8DBDC97ABF9ULL, 
            0x75AE458EC15C481EULL, 0x52E21918566136F7ULL, 0xE86BAA66CA745474ULL, 0xB39C67E0F8B5C1FBULL, 
            0x68B1B593D4874BB6ULL, 0x1F06A195190512CAULL, 0x2D5BC51D8B0E4236ULL, 0x481D540092A7AB5AULL, 
            0xCF40A3AA945020CFULL, 0x9ED457630F39D5F6ULL, 0x77723FE2626C147FULL, 0xE56732E194AA8809ULL, 
            0xD94267DE6E3B3E97ULL, 0x8A7CB90BFD7DFA54ULL, 0x80211429BB9DFC1EULL, 0xDEFEC44948F0603EULL
        }
    },
    {
        {
            0xEB483AE74ADD0B90ULL, 0x81635145EF556B7EULL, 0xFCBC549AA992C0EAULL, 0xAC902ED619B713A9ULL, 
            0xA2EB0DE7865EF63CULL, 0x80273EECB6D15FA1ULL, 0xA59458D1C7DC9825ULL, 0x3BA8BEB31777CA98ULL, 
            0x2BB8D0EDADBBE3D4ULL, 0xD07E1E6D684059A6ULL, 0x8CFEC8501D778131ULL, 0x3F944C7A43F13F1EULL, 
            0x305C3438A3B31E60ULL, 0xEBCF9D578DDC53C3ULL, 0xCFE838266B132F0DULL, 0x725FD590B9CD99CBULL, 
            0xC47877C131C636EAULL, 0x37C5ECD6C8D740C3ULL, 0xB5F878FFB2C555D6ULL, 0x3824241E7482B80AULL, 
            0xAAC5B8210CB3818BULL, 0x82703372C25E54E8ULL, 0x7219DB38593C33FFULL, 0xE2BB1DEDCC2C40F7ULL, 
            0xFA67AEFCE0AACFD0ULL, 0x63201D56E2C15A51ULL, 0x07978D3529083074ULL, 0x506527F63D0B3050ULL, 
            0x9575F357C787F0ABULL, 0xAA13BDCCF9E77BCFULL, 0x02BA532EF34A2E60ULL, 0x950DB764B38EADB3ULL
        },
        {
            0x736D1133B8E0F4D8ULL, 0x8BE9864CD9276471ULL, 0x72F80B890806310CULL, 0xD0D3CF326D608B17ULL, 
            0x14C50503EF37C233ULL, 0x25E9428299F343B4ULL, 0xC458BA1BBAE9CCF4ULL, 0x22F67AC31AF133F5ULL, 
            0xECB4C9A1DAF616EFULL, 0x6B0B30328500B45AULL, 0x3E9009FF91C7F9F5ULL, 0xF901416D60FF0595ULL, 
            0xCB42F7F5EDD90409ULL, 0x3FD3B8CFE6156EB7ULL, 0x204479F876C36E2BULL, 0x80B9068B493BC438ULL, 
            0x2D296D486EDC13A8ULL, 0xCEC276273CC2C6A7ULL, 0xAD2C5217E292F35FULL, 0x3CE3D975ADBCC8D2ULL, 
            0x332A6BB2CFF50FFFULL, 0x2233BF474D4849A6ULL, 0x19A1FBA11BE81FEEULL, 0x7E7CDCC2F1DD534AULL, 
            0xC17439CFC92F497AULL, 0x25D085A0C9C64BBCULL, 0xCAC0303F686D4CC2ULL, 0x6995FFDA2325E7DBULL, 
            0xD90DA14B992ED032ULL, 0x234FFB244194F4F2ULL, 0x40FBFB55075497A5ULL, 0x210621020621F781ULL
        },
        {
            0x524A08B707486732ULL, 0x0859D980A5F1E502ULL, 0xAA08ABB970137611ULL, 0x0E3585E6352C5A0CULL, 
            0x4EF887487475BF6DULL, 0x10B7B803D1D70D99ULL, 0xEB75F81C4E8DA23EULL, 0x8217258A4D3849D0ULL, 
            0x59ECE9758F8BAB6FULL, 0x9185B11B09E319FFULL, 0xDC225B13906D6E32ULL, 0xB6F275EB7E14D1DCULL, 
            0x8688D6E2B164D85BULL, 0x4AC7DCCC86F1058DULL, 0xA258CDD0680B9582ULL, 0x7099DE90EEBE15C7ULL, 
            0xC65D2942440C9155ULL, 0x04D9ABF149128A07ULL, 0x7947762EFE5C72C9ULL, 0xFBCDDB4663C81595ULL, 
            0xAE6B59DDFC173890ULL, 0xDC521C056B013D49ULL, 0xDEC9BA4DAB8DF0BDULL, 0x0153D36C6E009BE3ULL, 
            0x998524BC9309A862ULL, 0xB25472FDAEC578D5ULL, 0xA0F182A5FA2328DFULL, 0x5709AF27858B567CULL, 
            0xDD03ABC3FB32A6ADULL, 0x4F53DB35B257D415ULL, 0xEB3FD4048E5F6C8EULL, 0xCD92A446BCC62740ULL
        },
        {
            0x70EB8DB98ED8FD6AULL, 0x10D03222394E0066ULL, 0x8E236DFA5D4BC567ULL, 0xEF087248D3815182ULL, 
            0xBF177D716EF3158DULL, 0xB78C5B3BAD1A5E46ULL, 0x0213D97E28CADA6DULL, 0x92657D3C5880D9B0ULL, 
            0xDF4C113668BA96D7ULL, 0x7D64B4A262025BF0ULL, 0xCD5615D0141195DBULL, 0xEE8058779AB1272DULL, 
            0xDDE45277B7F72D2DULL, 0xAF7F38BBB44F861AULL, 0x7846F67FFB8DAF6BULL, 0x0DB8513D90DF900DULL, 
            0xC2BD219565FF3A64ULL, 0xA44D562D83151B1EULL, 0xAF89F41F60F3A71CULL, 0x113250ED414A9393ULL, 
            0x8809E2588738E34DULL, 0x0BFD15710634F098ULL, 0x8082865A27C6AC29ULL, 0xC6DDEA91515CF9B5ULL, 
            0x1C7F93FDCB43A705ULL, 0x753D6C234078E6FCULL, 0xB742FE9857846B78ULL, 0x62113C668C8ECD1AULL, 
            0x897F03FF54589A8CULL, 0x6A38669EBEE60EA9ULL, 0xDDE56A11A0E7393DULL, 0xDF510BF242FAC21FULL
        },
        {
            0x42A13FDD1DED0026ULL, 0xAD76E6917E80F369ULL, 0x4F9DFAC53C1007C2ULL, 0x59354CA5C61070C2ULL, 
            0xD9F2D8EFEE90A689ULL, 0x048FE005D2FA9E1DULL, 0xDCE45637F1A61D91ULL, 0xBD7CBD94EAA0A77BULL, 
            0xEF87A3E3995E4D9DULL, 0x206E514FDB1D0CCEULL, 0xBCB281423735D25AULL, 0x1E53F6C95FABC728ULL, 
            0x174991917E57A692ULL, 0x557E7420738BAB5BULL, 0x8E728C593ADE45C8ULL, 0xC892DDB05873DCB7ULL, 
            0xC5813D0F4A21C077ULL, 0xA2FC397777624B7AULL, 0x20FCEBAAF49ACBEDULL, 0xF39E7C0AB5DB7BDCULL, 
            0xD3AF775E8E2C869CULL, 0xB1351685030A7962ULL, 0xCCB1C6CC6667A1EBULL, 0xB38A8418BE93C320ULL, 
            0xC466924E840BC5ABULL, 0x5C30FE3641619859ULL, 0xDBBD93F155543B43ULL, 0xB31FA3336248EB4FULL, 
            0xBBF43A53E624DFB7ULL, 0x09A1C8380ED3EA93ULL, 0x8A29B7EC1024ABBEULL, 0x1D1CA59677A373FCULL
        },
        {
            0xCB3AD9A8CB8379C1ULL, 0x47DC3A675BD201DBULL, 0xC506FC05A105DD6AULL, 0xDC97B9C2F1139CE1ULL, 
            0xC121384C627D1E82ULL, 0x2056E89249F598A5ULL, 0x5A4920BD05BA88F9ULL, 0xA965A635DAB155F2ULL, 
            0xA95CD8EBDF34434BULL, 0x1693EBD2899688BEULL, 0xD9E78C2D9AA74470ULL, 0x39CEFA6ED5873191ULL, 
            0xF7B7A114A0A1374FULL, 0x1DF7992C1BB4AD50ULL, 0x9FDEAEB659065AB5ULL, 0x62B807B58CFAE40DULL, 
            0x35582D2A592EC7C6ULL, 0xBD1EF5B3EE8625D1ULL, 0x0AA5A8730A33AEBBULL, 0x6907516B28C00408ULL, 
            0x4487CA902BA56658ULL, 0xF0A444A09ADA88B2ULL, 0x290874E6C60E2234ULL, 0xF2D57688A323897BULL, 
            0x38C9DE71E19523D4ULL, 0x1AA622032AFE9D09ULL, 0x0E54A6DD4915F9B3ULL, 0x66CA80277E76B179ULL, 
            0x698D1D25757EEA36ULL, 0x414AF4D05F7B23F7ULL, 0xC553EC1C96D82EABULL, 0x334EB9F682CC2458ULL
        }
    },
    {
        {
            0x0276840F9553A0D7ULL, 0xAAA146CB026F5AECULL, 0x900A5B427A668D57ULL, 0x6EC72E8171B3462FULL, 
            0x61BD2B441DEA3718ULL, 0x6067184C8DAD3EE2ULL, 0x00FB90A58254F9C6ULL, 0x4E56FA914E83C036ULL, 
            0x7A6E34B03BB88C1DULL, 0x7F5ACA652A76D4DFULL, 0x6D02852527E7D329ULL, 0x36B3362B1B1D4B56ULL, 
            0x2A2EDBD2F5E32527ULL, 0x243FE86A0F879A9FULL, 0x823CA084CF0CACD4ULL, 0x2A67628E5849FEF1ULL, 
            0xC80B5043D6B28326ULL, 0x0694204A74E6C22EULL, 0x76EDB8649143F79DULL, 0xCBF6C7D0EA6E7D91ULL, 
            0x69334D9EBA52B843ULL, 0xFD644042820BB317ULL, 0x1080DFD591499BAEULL, 0xDA2E0D39CD386B2BULL, 
            0x0E9DC3668D507B94ULL, 0x3905FB160E891C27ULL, 0xB8336428D5B1F3E3ULL, 0x66DD9F33F3E14F29ULL, 
            0x91D0A4BC886FD227ULL, 0x46D8116A766684B4ULL, 0x0A02EEDD4518485AULL, 0x70C8027930CF4B51ULL
        },
        {
            0xCC425284AC26D175ULL, 0x19C6B052DC399F0EULL, 0xC6323DDC3C4B2567ULL, 0xEE3FB21583CA2449ULL, 
            0x02ADD4E665C456DAULL, 0x0D15148991C56B05ULL, 0x502441E80815D6F4ULL, 0x3AE9423ADBB541FCULL, 
            0x49EFC259811B069BULL, 0xDC2D446B53EE8AACULL, 0x122F9EFF1F34B519ULL, 0xF9D570BD4CAB68E3ULL, 
            0x0FBB9C003E2E1D8CULL, 0x254A2A7045250474ULL, 0xF39621567196F09BULL, 0x9E20716278E9B39BULL, 
            0xEC4BBBE62EFE256AULL, 0x5D43CF646A0C7CDCULL, 0x33F13AB99C3DAC9CULL, 0x874E02DC9468DDBDULL, 
            0x9DF0B46A1B598848ULL, 0x4CEFB3EC2ACBCC0EULL, 0x3070AC9AC62FF176ULL, 0x8A15F43F15D5A8E2ULL, 
            0xE52C53C9E0D3A6C6ULL, 0xBD4062C00EE2A4A9ULL, 0xEAA7EC9D6FB35E8BULL, 0x9520AE589654E9B5ULL, 
            0x1CC45A7F3BB17390ULL, 0x145CF1E19E8B37D1ULL, 0x69FFAC1B60AAC86EULL, 0xFDC36E419D11C44DULL
        },
        {
            0x99B51BAE9AB2E42EULL, 0xD19A03F344641069ULL, 0x04E219FD3413316FULL, 0x67E01591F9562D67ULL, 
            0x5F31B4C07FDD4533ULL, 0xE590D2249F31D8DFULL, 0x4A9D7B12CBB370AFULL, 0xFE433937A1CD9CD9ULL, 
            0x6F384D40DFB1C6FFULL, 0x5C9945C25EA61834ULL, 0x410137AD4F525658ULL, 0x40A3C18D8341317CULL, 
            0xCB70AB5608C7D775ULL, 0x22DF78375CA6C026ULL, 0x65C85495DB9AA9ACULL, 0xDDE671E1A911DAE3ULL, 
            0xF1B78B76695D8976ULL, 0x731AF62ADD1639E3ULL, 0xA53C353D47E1AC5AULL, 0xA349C6872E542779ULL, 
            0x4437B02037D1A3E0ULL, 0x4B5EBE593E78A507ULL, 0xF4C0718581E01101ULL, 0xC0ABB40A34E85412ULL, 
            0x0E9CBD1E174C02E5ULL, 0x9598705CF9FB2E66ULL, 0x0C13E3CF7D2A9B77ULL, 0xC1AD454CD6CADE6BULL, 
            0xC23993F328DA9A87ULL, 0x658A017A3A8240D6ULL, 0x47ED8201F7A0FEC2ULL, 0x2499A23354098D06ULL
        },
        {
            0x27D67BA8F6170105ULL, 0xB7E21B5ED7E31C31ULL, 0xEB795A574A529978ULL, 0x6559E295EFE91888ULL, 
            0x85B2724268AE28FEULL, 0x2C8BAF093E387CCAULL, 0xBCFA6DF34698176EULL, 0x5C593D04DB9474C6ULL, 
            0xE2C7486730EAC4F7ULL, 0x7ABE62DB9916B3FEULL, 0xA444A60EDBB9A3AEULL, 0x1ACC49335765E17FULL, 
            0x5BE2F934384B8481ULL, 0x08FED08CEFA6F6C4ULL, 0x4A72C106C7185BA7ULL, 0xBE530AE9B249255EULL, 
            0x330A3B547A861EA0ULL, 0x6E8E1A0BBC7475F8ULL, 0xC7EE71E51BB4F097ULL, 0xCA5AA76CB55BE113ULL, 
            0x0817261D24942CA0ULL, 0x9D4CAD833D9C5FA8ULL, 0xD7B6301B57B2B522ULL, 0x0C34E9AB053F1B8BULL, 
            0xD38E3D7A8991085DULL, 0xEFFB7973183E7C13ULL, 0xB88686A1D8E8485BULL, 0xAA06316219EA0864ULL, 
            0x917E2E6C5B92EF0AULL, 0x138E46525B5C4472ULL, 0xBDC6862933880FFFULL, 0x8A11438ED2884C54ULL
        },
        {
            0xFD3D8100B9A4B22BULL, 0x2B4647FD13E77F07ULL, 0xD75E91CA4BD3AA61ULL, 0x76D3FEB99341FE5AULL, 
            0xE4F7F6057D0D2E48ULL, 0x293925C941DBDC65ULL, 0x311D46789A9967C3ULL, 0xFF569A6DBCE601CFULL, 
            0x4A05B59B68CEE690ULL, 0xF0C6D764F0D15056ULL, 0x7603E96BF7A1D4D1ULL, 0x10524FF3C5C7E148ULL, 
            0x9274CAF34CF6EF06ULL, 0xA4E289AFD3F3D207ULL, 0x364538D3321F7898ULL, 0x3EF5B815A5CCED57ULL, 
            0xA8FE027551EF1850ULL, 0x5140056D685B4696ULL, 0xC92A0C28165263BCULL, 0x38AE66FAC1C38714ULL, 
            0x5D5A7A57BCB5DA25ULL, 0xFC44C509429929AEULL, 0x2DA614F2F75F2AA6ULL, 0xCA155598C7462F99ULL, 
            0x2F5829607344F6A3ULL, 0x674394870778DF2DULL, 0x9AB359D9A6B18908ULL, 0x427D979B40B9BD14ULL, 
            0x51734C6513C69188ULL, 0x433F36DA62FCC5C4ULL, 0xED19EAC69F303171ULL, 0x32DBC2D02FFCC678ULL
        },
        {
            0xB9F4CD36BB916182ULL, 0xB1F8626FB823F74AULL, 0x75A23B84F82720A7ULL, 0x728BB0680FB703CCULL, 
            0xE06D9B7B556EB15AULL, 0x50B0DE14D87FF159ULL, 0x867183B1F169184FULL, 0x1E8180F4A6E4DA62ULL, 
            0x118099EBABDA78F8ULL, 0xDEA2501EE5815108ULL, 0xFEF6F6BD8DCF9027ULL, 0x8F690A637623E391ULL, 
            0x1ECF4963B3727772ULL, 0x33B201973E912256ULL, 0x9549725C456BD87BULL, 0x2D8BFBF6266115E0ULL, 
            0x676F08D0421DA05FULL, 0x0AF920482367EEC1ULL, 0x85B2C1CD8387DD87ULL, 0xCEA5D6567DFA25A8ULL, 
            0x6E5849B60A3B43D9ULL, 0x12378E7033E0ECC6ULL, 0xA0791A0230E37104ULL, 0x875A1E78DBA8D173ULL, 
            0x2BD45EE425896407ULL, 0xE600286A1C71FDC3ULL, 0x9007AEBBDC032625ULL, 0xDC4B7E1F461D6FF3ULL, 
            0xDB026CAF5BE5B3B3ULL, 0x1BDC80B7C2917ACAULL, 0xE931975823286F07ULL, 0x6460AD951CB9D5C0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseBConstants = {
    0x3A28CB57D78FC89EULL,
    0x60D631B5CFD65C21ULL,
    0x1777E4904A461020ULL,
    0x3A28CB57D78FC89EULL,
    0x60D631B5CFD65C21ULL,
    0x1777E4904A461020ULL,
    0xA7794C232B89EF3CULL,
    0x7455F2E46C78E163ULL,
    0x0C,
    0x83,
    0xA0,
    0x46,
    0xB9,
    0x4F,
    0xF3,
    0x57
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseCSalts = {
    {
        {
            0x27AC43E1DFB6A8A6ULL, 0x524407E8CDC2FFFDULL, 0x525997D8DF968DA0ULL, 0x09FB1813E2004A41ULL, 
            0xEEE3E682D6F1A4A4ULL, 0x8B87B2D58703BAF4ULL, 0xACB3ECCF34564629ULL, 0xD91DE40E0DDE0AC0ULL, 
            0xE10BA4C6B36F2DC3ULL, 0x4588096B855D4AAAULL, 0x0BA1530533658903ULL, 0x7667CEE562BF5EFBULL, 
            0xF8D5D00C87F6633FULL, 0x8E8ED7F2ABE324F8ULL, 0x529A0764E3A4D320ULL, 0x421CACE5012F94C4ULL, 
            0x0D9B494ED3A45C3EULL, 0xB85F107D7CEBDFBFULL, 0x1F80D19503B6ABE1ULL, 0xF06FA49638B2DE86ULL, 
            0xB30B79973E63C68FULL, 0x3488CD7DB661B286ULL, 0xB54430A09F4029ABULL, 0xAF3086CD1954F6D8ULL, 
            0x3512B36C54C987FDULL, 0x86F0F013188F6CD9ULL, 0x2D3453B485F8C463ULL, 0xE32381CB455F654AULL, 
            0x6C3AE41C4A540D01ULL, 0xBABDE6E928F22CF7ULL, 0x906985C486D0E450ULL, 0x2848E974C7C56A04ULL
        },
        {
            0x6E942FB969AA30CCULL, 0xE2F50826B89D2D36ULL, 0x75811580D59F36C6ULL, 0xDA9E5A2B4B702A0EULL, 
            0x414205520A936A21ULL, 0xB2B70E4A82D127DCULL, 0xC66B7DC7242702E2ULL, 0x4E089415D14E1C5BULL, 
            0xFCF5D7AEC86E7089ULL, 0x117411CF8CD7355AULL, 0x63F2AC5DA9A7AC17ULL, 0xE1D0AB600C8E6D1AULL, 
            0x0D49C722A43D9BEAULL, 0xC65737D393B57EFEULL, 0x5E08810319D2FF11ULL, 0x0F8BC9BF557359D9ULL, 
            0xAD55E58B35B21F76ULL, 0x9ABC20DD66EB0AA8ULL, 0x462472E3A03CBC04ULL, 0x249C041EE11303C9ULL, 
            0xA46636BF048BA6B0ULL, 0xEEC4A482896C119DULL, 0x0024BEB5E67524BFULL, 0x90D117FF19DCFD49ULL, 
            0x0BD64959CFE7EFBDULL, 0x3DF05EFBBEC6F3D2ULL, 0xDECE63DF24F80ED2ULL, 0x5DE766C74F4D19F2ULL, 
            0x9FDA36437EEDFE54ULL, 0x548CC2D2DC3C6CA4ULL, 0x4D7AEF979C187709ULL, 0x71A9B095A936A052ULL
        },
        {
            0x446AA326B6643DAFULL, 0xEB51864C99F4233CULL, 0xEA8660AE7CF88D13ULL, 0x611B932D208C5BC0ULL, 
            0xF92C48452718FB72ULL, 0x4B691FB5F27A3910ULL, 0x55148FD8C8C4AC1EULL, 0x104B0DDA81532C17ULL, 
            0x3ED2FE706BFC1C18ULL, 0xA40FC406B9FEA61FULL, 0x3E42DB58CC2BC262ULL, 0x1496ECD1813A4539ULL, 
            0x549C376FDD53E088ULL, 0x5B1DFA28DB5109F0ULL, 0xE874F04AB1AD6E44ULL, 0x30B9DDD06C898D21ULL, 
            0x9612C88764A65DE6ULL, 0xA5B9DEED69473F54ULL, 0x1EF09F44809E8D3AULL, 0x8C4AF09542E1E809ULL, 
            0x6E1F1456C5B609D4ULL, 0x1F4EFCCC58573795ULL, 0xD8F69F3E9CEB3330ULL, 0x7459211113A6CF38ULL, 
            0xF10699AD90B2DA86ULL, 0x504DAE6702BC86F6ULL, 0x2E9C7DE1561B0D2FULL, 0x0530725B490CC173ULL, 
            0x1C64034DF02E1927ULL, 0x4C75108FE2385009ULL, 0x0FAC7E20269D50EBULL, 0x2E4F13E65854823FULL
        },
        {
            0xFEDC79E22AA9E245ULL, 0x3552CC45208D3ADAULL, 0xE71DF48BCD5FE242ULL, 0x470DA9DA4BE14C81ULL, 
            0x0A483A58553AB3E4ULL, 0x4C001AC1227874A9ULL, 0x748B5AB5AA97D220ULL, 0x246CF060D46FF8C9ULL, 
            0xD6AB8C8E5F81D20AULL, 0x55649F7558C04EA6ULL, 0x2BA6B72A10BED847ULL, 0x5E4C52999F952F2CULL, 
            0xB34F49BA32E6249DULL, 0x9E3ADEBCE0A8ADDBULL, 0x7E977B703D06DC7AULL, 0x48650788F0271023ULL, 
            0x87DED20BEFB9FD3AULL, 0x1C6E58FB896A39E9ULL, 0x20A3D5C9976B2B69ULL, 0xBC33A2FFCB8E2E31ULL, 
            0x6F660549A4E2230CULL, 0xAACD9ED0EF7E27A6ULL, 0xE10251C0440F96F9ULL, 0x12161B48B421DE09ULL, 
            0xCED40F322F6035DCULL, 0xFE7C49A9D321FD4EULL, 0x665AC9DAB4FCD5A5ULL, 0xCC072C2EAE2AD69FULL, 
            0x353E62A4C917DC2EULL, 0xFB1790D76070CE57ULL, 0xAA3204931CFAA481ULL, 0x25407E9874BBF6C3ULL
        },
        {
            0xA32058121A7A2BA8ULL, 0x367E15CA112E8716ULL, 0x76DDF5702E59B75AULL, 0xB79CBCA4E4651C9FULL, 
            0xBDCAFE08F12E253FULL, 0x866C0DD5FBA791FDULL, 0xCC179CEDCB97E063ULL, 0xB94DD2F681FC1ABFULL, 
            0x31E711997F8C3DE0ULL, 0x24D7478ABA4DB6CAULL, 0x52BDBA7EA2FAE591ULL, 0xB7BA4B73E57C9196ULL, 
            0x51D9B4FFDFB1B30CULL, 0x6D7122F0CB5CC7AAULL, 0xA7D1566874B6F15DULL, 0x763791B70FA97DD7ULL, 
            0xED4D1A6CD4FCE3BDULL, 0xD2FF69DA575E1D83ULL, 0x883DEC5523E5C102ULL, 0x390723185452BD57ULL, 
            0xC245CBE39D950AF9ULL, 0x114EB719DFF0AC2BULL, 0xBCFCEF97DC4A1115ULL, 0x73AA99937CB8ACE1ULL, 
            0x69174BA3B377EADCULL, 0x36EDE4ED35E0457AULL, 0xA3A9147933FA88E2ULL, 0x5E400893C7188BD8ULL, 
            0x39A85998B1EF5E53ULL, 0xA634CF8892A12D73ULL, 0x4B7A22DF6E0A957EULL, 0xF0943EAD4E93BFE6ULL
        },
        {
            0xED5CCC339C6125B5ULL, 0x4BBD00A909D44A58ULL, 0xD0838D9262E8E651ULL, 0xD73E6AF46294198EULL, 
            0xF0F713EE09F1B176ULL, 0xDAB41BAFF8035556ULL, 0xEE67265302D5AE3CULL, 0xC18561B0DA72D6E9ULL, 
            0xB0B3FE6AE8002F47ULL, 0x2BD8C2B0310957E2ULL, 0xBDD081DDEF7DFC44ULL, 0x4F06E5FFCF6AF924ULL, 
            0xECF76BE5CD43758AULL, 0x1D088435C6D0A7A9ULL, 0x734CC35C6DEEEE03ULL, 0xA38EFE755EDCCB9EULL, 
            0x2D86B482BA21BC2FULL, 0xEDF0B661E49BBDF1ULL, 0x5BBC53DAFB917806ULL, 0x1664EB90CF4DB536ULL, 
            0x0F7E180F1D00D159ULL, 0x37772E5D7259A8E3ULL, 0xC93C121599948A55ULL, 0xFFC255C86D608034ULL, 
            0x8FDEEF9CFB77DC4CULL, 0x5368FC7DE314F26CULL, 0xF218CF486A3C1A6DULL, 0x36B2D54A608CB94AULL, 
            0x538EADDAFDEF2E54ULL, 0x88EBD0F2184598C0ULL, 0x6E0DB195393FA2F3ULL, 0x9B113338EA80F870ULL
        }
    },
    {
        {
            0x9F51D929F8C81429ULL, 0x8776CFC21512257FULL, 0x513986D1D02C47A4ULL, 0x310B49B71FD2148BULL, 
            0xF75CBA82A4274B7DULL, 0xAE009E14F8576380ULL, 0xA0F8DA6F562EC6F2ULL, 0x4C4D44DBA45D54F9ULL, 
            0x871BEF24FE1F0F12ULL, 0xA396909BE940E07AULL, 0xFB97AECDC2703826ULL, 0x3BD14A9B42DADF34ULL, 
            0xE8B9943AB323A037ULL, 0x9A1760FA9AE62078ULL, 0x9944526DA23B906EULL, 0xE51CC0BCEDAF6AC8ULL, 
            0x793D304F256C0B16ULL, 0x929E83E674D4572DULL, 0x696DA2C933DF16C2ULL, 0xD4E35241209AC10CULL, 
            0xD8F2792CDC5FA6CCULL, 0x985B2D07B1586718ULL, 0x369920DFD511FEA7ULL, 0x5A7FA243E380CB4FULL, 
            0xA6951D1B4390AD85ULL, 0xF5E49551CA317D51ULL, 0x0F376C66F3686DA8ULL, 0x857E91FC33BCC815ULL, 
            0xC885CD3C018DCE1AULL, 0x8F04A71A07D1706BULL, 0x85EE656D19BBB30BULL, 0xD4B1E14FC9E58D90ULL
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
            0xAFB5291AC957D101ULL, 0x3F6F83A3990B8C9DULL, 0xF07BC190411F1EE4ULL, 0x482E25D27E99891AULL, 
            0x6E6CCAF4F7C69B19ULL, 0x99872E3F4CE394FAULL, 0x90FFFAE5E468FE15ULL, 0xAD81437E6749D60FULL, 
            0xE7F0A3DDF7EDC898ULL, 0x111B5360BBDB69EAULL, 0xBC6993AEAABBB44EULL, 0xAC1F7F8BB840624BULL, 
            0x61C7AF7C8EDAEFD1ULL, 0xDF020F32560AD8F6ULL, 0xB7E6B9F7C25156B1ULL, 0x7395671992AA061BULL, 
            0x41BD5BB2FE09CA06ULL, 0xD71E2F998B014012ULL, 0x1890B28F926BE48AULL, 0x1F3AD1808821B8BEULL, 
            0xCE377E4E774F5609ULL, 0x365B721E6AD11393ULL, 0x21207290D02043F1ULL, 0x8AAB81ED8EB1A1BDULL, 
            0x4EDC624426D8EC65ULL, 0x287781A5BBD79A35ULL, 0x425B8F10DA66A834ULL, 0x536FE7DAB36E1681ULL, 
            0xFBD0AC6B0D1EC6D9ULL, 0xB64FBB96F2134C52ULL, 0x606321E6B88CC5CDULL, 0x8EF6C84F59079182ULL
        },
        {
            0x44FA38009415A609ULL, 0x600DA2E1F620CF4FULL, 0xDFD5B6C53DD81D90ULL, 0x1F94027CD1B1F55CULL, 
            0x1D16EB1D0A248810ULL, 0x423469DB77283021ULL, 0x09AB2E0F3CF105A4ULL, 0x5DB99E29170CF584ULL, 
            0x358F51EDBCFAF583ULL, 0xAA8D85A9E0F41508ULL, 0x9252B762722FE782ULL, 0x140404128C7C1FADULL, 
            0x7DE52B312D2205F8ULL, 0x315E20A6E06A1647ULL, 0xA47C0CB42D5779BFULL, 0x4993E84EC9042D41ULL, 
            0x556EA19CAB8DD5BFULL, 0x2DE64319A807C435ULL, 0x30ED7D93D13272C8ULL, 0x0BAFD21F9FDEE96EULL, 
            0x8D967B757409EE78ULL, 0xBB893EF2675E8EECULL, 0x8C3C96B88719CBDFULL, 0xC09B5C4EDC792474ULL, 
            0xB6D08FA9D542BCDEULL, 0xB01DACEB7D4EA698ULL, 0x1CE18CB8AD7A4972ULL, 0x2B2F66B9133D8C33ULL, 
            0x45D62535C2B3BCE8ULL, 0xBDAC5ADE2DBCF0CFULL, 0x57880A7678CD1314ULL, 0x47EA2C9560AF6CD9ULL
        },
        {
            0x8B79C1517894AA01ULL, 0x6A798B89A5660ACAULL, 0x10474611AD9BA406ULL, 0xC0E359700710DD12ULL, 
            0xBB6C0759C2EF5F76ULL, 0x221C4FC0459F826DULL, 0x4C598CBFDA068028ULL, 0xBEB719EAFBD1A752ULL, 
            0xA0C3DA37C19AC391ULL, 0xDC9A13FF8EF6CD7CULL, 0x17D22ACAE45A9AC8ULL, 0x5B889296B416CBACULL, 
            0x9D10DB50B1B70DB8ULL, 0x9997828428A9E3F2ULL, 0xB7813B9758E29C54ULL, 0x6A8FED003B28A7E7ULL, 
            0x1FFECB6E1DC8DE72ULL, 0x68DA544E685C7114ULL, 0x7F912A9ECEEF9F96ULL, 0xAB91B78C9D5F70DCULL, 
            0x7381A832223DE784ULL, 0x3284CB6B75250EC4ULL, 0x9B02BFA362D4A85CULL, 0x8B4CC7ECD43FC7A1ULL, 
            0xE15DC29F807AF6E6ULL, 0xD7E074DE4B096984ULL, 0x09E6046F05ACB896ULL, 0x7DD4514AF827D6A4ULL, 
            0x9864F81CE7520733ULL, 0xAC303CC2F8BEC359ULL, 0xD0B980315B004274ULL, 0x50FE8C1001F7D9E9ULL
        },
        {
            0xEF9ABDF45F4C8AE0ULL, 0xCB5215E14068C7D5ULL, 0x70EF82055D8E0391ULL, 0x1CEA2D551583FD0DULL, 
            0x0D8D4445B7B5B0D6ULL, 0x84CAF562CEE1894BULL, 0xAF07DC1D5950311FULL, 0x4E2E3F7AD6178637ULL, 
            0xDA5FF3DB40075161ULL, 0x06004A36D4D35A5EULL, 0xAA8A39210C0039F4ULL, 0xBE597619494C36C4ULL, 
            0xD54697854DFEF476ULL, 0x7934EF69F85F30B2ULL, 0xB6D55B7DDC22EE15ULL, 0xF0C3AABD231EFB1AULL, 
            0xA5E914208054ED1DULL, 0x43DB7BCAB7FFF545ULL, 0xB6FF7F4E5644C41DULL, 0x64CBD2377B536412ULL, 
            0x0CEA4B12AE97E1C6ULL, 0xF2E0532C0A98B60AULL, 0xD7DEC2624556D1A5ULL, 0x682E1D11CF5DE5DEULL, 
            0xB2547CDB02027817ULL, 0xDE358566A081E262ULL, 0x86BFE812F23B49BEULL, 0x5FC67DE325E0E928ULL, 
            0x61CBBC300C60C74DULL, 0x632567D86EE8B805ULL, 0xE4B3C29F33FA464FULL, 0x4FCFD62D8F0BD2A0ULL
        }
    },
    {
        {
            0x16F38DE944203B04ULL, 0xF319B9E97C9A152DULL, 0x673B8E0FBDABAB3DULL, 0x96B28C0FBFE7D4E7ULL, 
            0x964453E2BB43F021ULL, 0x777C32591D18C75DULL, 0x778EB4E7378398D6ULL, 0x7769A1898044DF98ULL, 
            0xC83E02BCBA75BB4EULL, 0x583614EEBA3668B5ULL, 0xB3100FBF7BE78189ULL, 0xB5F6D31E0C9BFF5FULL, 
            0x0EBE2938C42533E0ULL, 0xAFD8919E758AD033ULL, 0x188033FE53E9C4AFULL, 0xE25C1B92D7BC6982ULL, 
            0xDC3DB08E7EFE7D4EULL, 0x05B32537104EBB9CULL, 0x0A0B68447FE868DEULL, 0xF5562C933A58B896ULL, 
            0x44A623278942EF3FULL, 0x1546B37BD24AF513ULL, 0xFC7D0EE851DAFAADULL, 0x46B66FEBA846BF1FULL, 
            0x46A7AEB850BB1358ULL, 0xC000AD28F4D3A80CULL, 0xED38AE3A0575D2EFULL, 0xBBB01792E8FE303BULL, 
            0x08867E3A00E0247CULL, 0x0816F1B95292C571ULL, 0x895DF9915F7427C4ULL, 0x145E7D2C8174F4E0ULL
        },
        {
            0xED58974D60D45363ULL, 0xCEE6A6A0B23781B3ULL, 0xE34AC8FFAA15988AULL, 0x1FA59D382F9670DAULL, 
            0x443C037A62EC2ED7ULL, 0x98AFB428731AA620ULL, 0xF1DF1AD8A6782748ULL, 0x0996060C698D8D57ULL, 
            0x9D074EB05BDB2C78ULL, 0xB57BA74056CEC54EULL, 0x141B2F35EBA5A792ULL, 0xFB6F6217EFF25023ULL, 
            0x0C205255AADB9692ULL, 0x9DFE2F82C4C0BADCULL, 0xC0566F852CA496F7ULL, 0xD2B3E77D68B856B0ULL, 
            0x5D6E5405A59CF60EULL, 0x208BA5A7CD5B65DFULL, 0x588A71EA5D8FF35EULL, 0x0D13769C089EAAC5ULL, 
            0x0178F40CC7AC9B54ULL, 0x7BC637BD4B116DCBULL, 0xDB06ACEDD5EC9429ULL, 0x41167D4236D824D3ULL, 
            0xCFE79D9FB3060719ULL, 0x0472057C7EC0187CULL, 0x74658F8C5007D066ULL, 0x35C3FBE5FBE417C7ULL, 
            0xB999A7936F58CC91ULL, 0xE1E775C0776C690DULL, 0x124A86B6609AC70EULL, 0x3F2A5EDB2BA9FE9BULL
        },
        {
            0xF98A4AB82C49362AULL, 0xD576F39051A51E87ULL, 0xB05FAE7F0BF066AFULL, 0x6AD59023EE0C392DULL, 
            0xEA9E7E0F9F928064ULL, 0x52CFF766C92BF84FULL, 0xA08FFE5A4CBCC5B6ULL, 0x9D6A0B4C6D813736ULL, 
            0x8A74834D000006AEULL, 0x9FB7A2658FADBAB5ULL, 0x5DBB5853BF2E8DFBULL, 0xF80EBBB5AECAB6D2ULL, 
            0x5F0B27CBDAA44982ULL, 0xF307362B81ABD94DULL, 0x9E21ADB0CEC8B603ULL, 0x296C766992E6317EULL, 
            0x36491D3992FA5F39ULL, 0x0FEF5FBD22E5DA1AULL, 0xCB8590A6B3289D10ULL, 0x51FFD7E5B612BC6BULL, 
            0xC29EE9933900022BULL, 0x53CD43EE48FAE4C6ULL, 0xCE831F7EA2BB859BULL, 0x30C607CB1687C732ULL, 
            0x973236515731A115ULL, 0x19A59F5D29B26E34ULL, 0xA5BFB3CDC385F22DULL, 0x690808A5CF5517AEULL, 
            0x5522BEC1D4B9D6CBULL, 0xD44C623489311953ULL, 0xA53A1D47F8440EB1ULL, 0xAB40050A818295AFULL
        },
        {
            0x2CFCB08151EFF894ULL, 0xFEE524C8A5B4FFC3ULL, 0x86B8BE1DBDDE1448ULL, 0x1B64142E948B79E0ULL, 
            0xCA49769FE606F80AULL, 0x48BE7030461F16B9ULL, 0x65382BE002A56669ULL, 0x9AF9DFE66D96FC28ULL, 
            0x6A15C29B083D04EBULL, 0xA618534AA53A5066ULL, 0xB46AEBD4243AACC5ULL, 0xBB23B6C491CA8173ULL, 
            0x7646EE55F1F9306AULL, 0xE38FA6D8F7D09651ULL, 0xA12575AAF27F894CULL, 0xDB245C5E84D9A857ULL, 
            0xA9A1490DCB4273EBULL, 0x1E3DA2E1DB8C7D36ULL, 0x3FB72DCFEA020FCCULL, 0xE4A36C9E6BAD59F2ULL, 
            0x7CDAD1E2E2905621ULL, 0xB5A67963B63BFE5BULL, 0x3BB080BD31322E3FULL, 0xBD73712DD1188169ULL, 
            0xB8B9798FFF7AB732ULL, 0x10888B2FDEA1AF0DULL, 0x05BB369568702EE6ULL, 0x31EFF5DEB9936708ULL, 
            0x0BFCA1FC705BBE4AULL, 0xE5B2FD2DDB3562C1ULL, 0x4A17C4C1EE8C762AULL, 0x438578DB7F3FA76BULL
        },
        {
            0x34D85949A7B58F3BULL, 0xC452FF6BF069E62BULL, 0x50C69302CB13A963ULL, 0x523947CCF6FAA086ULL, 
            0x0247C2D93DC243CFULL, 0x85188CC98794BDE0ULL, 0x70DD7BCD4C9D84F9ULL, 0x2C49E1090912A081ULL, 
            0x580973379C8F9AC7ULL, 0xFC3EAD9292EEFE14ULL, 0x7B747B8A00FCEACCULL, 0x65873E5EEDC5F37FULL, 
            0xBEE42E9EE0DB310AULL, 0xA4194DE2C487DA9CULL, 0x6F81CC5253CABF2CULL, 0xDDFF6FAF10B8F32CULL, 
            0x6DE5314D8E8C18CEULL, 0x8DBC1F53423C3909ULL, 0xDCDBA8C939787B43ULL, 0x42961775BC8C9DB1ULL, 
            0x1EFE95F4C55821F1ULL, 0xDDDECF0B5162D509ULL, 0x18DE34CB2115201DULL, 0xA1D02B96C0FB52D2ULL, 
            0x13C60209B999F679ULL, 0x8C23E9BB9FA4C864ULL, 0xAF7239D44ED3E0C6ULL, 0x0DA11D26524ABF00ULL, 
            0xB657D0094767CFCDULL, 0xF986D44363751D2CULL, 0xE6164D2675824277ULL, 0xE03BF3F73C093B3AULL
        },
        {
            0x551BFFE55C3A0DF1ULL, 0xE88366585FCA167EULL, 0xCCAB280F09F28BA9ULL, 0xA1DF0B90BFDCE5C5ULL, 
            0xB0CDFB5438B260BFULL, 0x107685E2966B16A8ULL, 0x2DA8C59AC97B198DULL, 0x61317DB48AEBC32DULL, 
            0xA7E8B41106891E94ULL, 0xB9697F116DB13042ULL, 0x2703432994186E1AULL, 0xF9D076BE4B4C73EAULL, 
            0x0CAFF3F0F8B3010AULL, 0x46A565A53F0D98FCULL, 0x59EA4D9DC09DAC08ULL, 0x94FB7D74D760AD1AULL, 
            0x7E534A9FA95F68AFULL, 0x342E1BDA5A309BF4ULL, 0xE5306EBC2433DC95ULL, 0x037866A8D51D340CULL, 
            0x5D7DB3E43B33BFD6ULL, 0x2AD0A3BED9404764ULL, 0x69BF8E3484AA1C8AULL, 0xC9D610B7D27F39E9ULL, 
            0xADC5C5DDF6BAA772ULL, 0x263E447531DFF5F2ULL, 0x1DB13F899825D14AULL, 0x37378FFD794398C4ULL, 
            0x6A988A21B60F04B1ULL, 0x190FC3AAAF469C7DULL, 0x4CB2FA8C93C5FF17ULL, 0x2CCA441F09F529AEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseCConstants = {
    0x75BEA890320FF096ULL,
    0x9A547C08B0C95A9FULL,
    0x19EA9B69F5DA2475ULL,
    0x75BEA890320FF096ULL,
    0x9A547C08B0C95A9FULL,
    0x19EA9B69F5DA2475ULL,
    0x114E61FE8F5BA7B9ULL,
    0x71B11DEA8FF0DB9AULL,
    0x55,
    0x5D,
    0x72,
    0x52,
    0x27,
    0x9E,
    0xFA,
    0x2A
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseDSalts = {
    {
        {
            0xEC12BB776CAB10F2ULL, 0xF28275DF099B7488ULL, 0x62B52DCC37D2629AULL, 0x9CFE8C995112C99CULL, 
            0x195D0644C773666CULL, 0x9A0225D47DF9AD0FULL, 0xB87CDCCA50855927ULL, 0x02C570EB148F4F57ULL, 
            0x46BCEB3A74F2E552ULL, 0x89405B0F37B7DE85ULL, 0xE9BA45A7E8D718B9ULL, 0x608E2F6D684CEB79ULL, 
            0xCD1AEF10D5D7F7F3ULL, 0xB6D8AEB060B2E9C2ULL, 0xD83127AC4256C5FFULL, 0x91382D36194B2018ULL, 
            0x7E1850CFEE46D063ULL, 0xABC65CD99DB14F0BULL, 0xD7CCEDB04433F867ULL, 0xC1A3961798FF9DC9ULL, 
            0x482A117DD8FD99DDULL, 0x1992EBD6E9F56A65ULL, 0xCDFD1DA66A7C4094ULL, 0xD88495B76F841ABAULL, 
            0xB0859A56C5AA55A8ULL, 0x2A1592E7B972B3F3ULL, 0xFA9497DFC6FB92E5ULL, 0x375BBFBBCA5314D3ULL, 
            0xBCB2C1CDB8C1222BULL, 0xC10F446EBAA31A44ULL, 0x095633191B1FC480ULL, 0xAB875D8B3E7EB3ACULL
        },
        {
            0x4FE5D2E9580835D6ULL, 0x8A66664E45B55C3BULL, 0xA60075AA8AB19785ULL, 0xA89204ECF8622D52ULL, 
            0x581DA0138CE50888ULL, 0x60B3F1D58B9CC7D3ULL, 0x054AD46A12D036F5ULL, 0x4EBF199B4276B6FAULL, 
            0xD76A636203B22FE0ULL, 0xCEBFDF06D4F1D811ULL, 0xAE7A8616C471F102ULL, 0x19ED33E4B0C20BC4ULL, 
            0x2BC66CBBBC69AAB3ULL, 0x0C339057F75463A0ULL, 0xAE8AF838DC4D4BFAULL, 0xE5652FE7C28E5A05ULL, 
            0xD7A7D6ECB21CC708ULL, 0x86887810BA91316AULL, 0x66EB512454AECDECULL, 0x5D047FDB434919C8ULL, 
            0x3BA8D04E0B4F43EAULL, 0xC5BE02B2106886F3ULL, 0xF9EED0D522A09EB2ULL, 0xC0ABC2531B631790ULL, 
            0x2326A043BE3F18ADULL, 0xA17533BC1EB56472ULL, 0x25B1CEE05A7FFC90ULL, 0x749DA3AE1CE1528EULL, 
            0xB573A12B4038C876ULL, 0x7765C423A4FD4E68ULL, 0x5540C7A74B3DD301ULL, 0x562EA0D252EB53ABULL
        },
        {
            0x5928FB670748AC07ULL, 0xC100E5F8FFB51081ULL, 0x1814B3CCA11BE95DULL, 0x7C8E83B98D4AAA53ULL, 
            0xD75DAEB158B201C3ULL, 0x7AD8057D90C0829BULL, 0xE286AF5146D895F0ULL, 0x6593F0D156FE4535ULL, 
            0x1C15041068DE9A24ULL, 0x266D3E6FD5FA7545ULL, 0xAD2A9386A0870B21ULL, 0xD6F955A3ED14A87DULL, 
            0x0DF05381154363D7ULL, 0x687C6473E2722003ULL, 0x202EBEA0690FE2B3ULL, 0xE9E368DC1A16F61BULL, 
            0xA98DFE007B789B00ULL, 0x4DD9DAEE1B7394F3ULL, 0xEEC6A1A79DD9AB11ULL, 0x5F5747B196EF6D51ULL, 
            0x1297B02B6D590AA3ULL, 0xD1858F18219EC943ULL, 0x3E27B10546EAB637ULL, 0x9EA5CCEA97F0D5CAULL, 
            0x314E80FCAE4A3344ULL, 0x2F2B580E0F917FD6ULL, 0xBB5E2AC8FAAAD159ULL, 0x492DE1E2531F2190ULL, 
            0xE03DE2460E976DA8ULL, 0x6587FFEC4E538E41ULL, 0x8F3383452CA6E602ULL, 0xCEC22048A49B0DD9ULL
        },
        {
            0x604D67FBFDD86988ULL, 0x3F782E73F3840D1FULL, 0x0F7A9E6178F48309ULL, 0xCDDAA480845F0FF2ULL, 
            0x0D570114D2FA12C1ULL, 0x804B8CCD2220D05EULL, 0x75A31427BA92630AULL, 0x6DB2162D680FB387ULL, 
            0x9AE7025A6A827136ULL, 0xB411416B250995C1ULL, 0x04BF782C2259653FULL, 0x8354C47DF1F9F882ULL, 
            0x4C1A4B8232A4346AULL, 0xBC4249D507749A63ULL, 0x59F3E1A145768AE5ULL, 0x85023907D37F3FD6ULL, 
            0xC7E824BACB634DA2ULL, 0xF9CE9C1C1E69B3EEULL, 0x8617F46D16A401FAULL, 0x31768DFDD4961421ULL, 
            0x058D5B775B43171EULL, 0x8274740ABA40B2C1ULL, 0x1F567F75FB054590ULL, 0x31B90652EFFC38F4ULL, 
            0x5F155CC362BF8EFDULL, 0x998A0EB0A21372CBULL, 0xFF1748622A20DAEAULL, 0x2DED07D2F5D49F85ULL, 
            0x5DB5C9F2A69F93DEULL, 0x08FBBB031C0D9C0AULL, 0x64B3884B28FDB7C9ULL, 0x827D8C102729B811ULL
        },
        {
            0x4030E3AD05CECF12ULL, 0x55FEA95DF4C271ABULL, 0x8D6866DCE48C6751ULL, 0xF88694ACDEFB69E9ULL, 
            0xFF8C9747DEE2C8D6ULL, 0x3055BD20AE43430AULL, 0xB1DECDC165E44B7DULL, 0x6461D9CD7B0EA36FULL, 
            0xC421572B3BA7CE2BULL, 0xD4995508E70002CAULL, 0x60C0BBAB89AF2361ULL, 0x59C8B1C4A9915B50ULL, 
            0x3B87B1F5493C6437ULL, 0xEB97A76B251DA7F0ULL, 0x9EBA32426B00C15CULL, 0xBAC8316566F288FCULL, 
            0x7173161669A58726ULL, 0xBF0097414A525B05ULL, 0xB4AB4A0F75E6695BULL, 0x594B70BC37BAA55EULL, 
            0xD4FA8260E6AFC875ULL, 0x47B620EF3290A560ULL, 0x8BF97A1A8E264DBAULL, 0x1222BD21EFA37E2AULL, 
            0x89F521B08CB951FFULL, 0x55FBDB152872316CULL, 0x955C4FD4F08A2CC2ULL, 0x3377371E5FFAE51BULL, 
            0xA411E4E3915F6CE0ULL, 0x4ED110DAD5A11326ULL, 0x73B64FAA414623BFULL, 0x14F84527FB6D0C02ULL
        },
        {
            0x8EE61CBC1A5BAE3EULL, 0x9D171A1FF18A38B3ULL, 0xD03CE9AC410C9AA5ULL, 0x436CE007D7AF0C99ULL, 
            0x56BDA897FC44DD6EULL, 0xA778A767C9D9BA25ULL, 0x24AB20667159EACDULL, 0x4CE756A9A136919DULL, 
            0x3E99F4E15AD0B660ULL, 0x67DF4E14276742EDULL, 0x25FF5B6C6CE546FBULL, 0xC55901B67E6ED105ULL, 
            0x6F5E92BD4B015209ULL, 0x88390936ECD40A23ULL, 0xE6F6F856EB308DD5ULL, 0xAF22A381B07549A0ULL, 
            0x56D017E52406B7A0ULL, 0x1ED813E4AC75DC66ULL, 0x158653437AD2BDF0ULL, 0xDC865C3015F4A077ULL, 
            0x11F4C17252355F95ULL, 0xB054CBEA7FBD09C5ULL, 0x3165A7D764E4A966ULL, 0x9943C8FDEC39F568ULL, 
            0x1B0B08FC50F8FEADULL, 0x7C70E89E6B0DE174ULL, 0x6963D92DC296BF8CULL, 0xF7E0C300F9FDD358ULL, 
            0x14C1416804B9309DULL, 0x1938F5D84F53E4A9ULL, 0x7110F0C197CF5344ULL, 0xE68813E3D73E0310ULL
        }
    },
    {
        {
            0xA6B621AC52D2D543ULL, 0x21B3F67BDA228645ULL, 0x71CEDC89E87D04E0ULL, 0xFCD76D2C1F9A2112ULL, 
            0x3D04120577A733D4ULL, 0x3D197B6C83B8C0A3ULL, 0xFB82C4567E67C8B9ULL, 0x6016EC2D8E42B203ULL, 
            0xF06F2B60F44D0692ULL, 0x91C8BAF5B4044E4CULL, 0xCB37797BCC9A6151ULL, 0xC8FE9B9CB665B98FULL, 
            0x7B9E6D0DF038109BULL, 0x4FB9DB1F2CD09512ULL, 0x6E9ECDBBF5300C9EULL, 0xAD6CF65F39C4F45AULL, 
            0x8FD3CD525EAA093BULL, 0x2DE8856E8413B79CULL, 0x6C52ED7B6FC32F7EULL, 0x44F99AA33D685B69ULL, 
            0x00597733D8045CFDULL, 0x99E71501FD670C0AULL, 0x92B5F33DD4756CE9ULL, 0xC7812C8FBAE9FF0AULL, 
            0x06AC9FB3EDA4391EULL, 0xF0B9BC1E37878A07ULL, 0xA9473F771C864A34ULL, 0x25080EC53B78C3F6ULL, 
            0x2AD5B7D79DDE3EB2ULL, 0xF4EF0CFBFF9056BAULL, 0xAF5C9AF733EE17B3ULL, 0x03851FAD79EBAD2BULL
        },
        {
            0xE2ABDB59DA7B0013ULL, 0xF34AF3BAA92A94A9ULL, 0x2EC7924A0F127F93ULL, 0xE4C5315E64979432ULL, 
            0xEA17B2E782FD7F9AULL, 0x3C87B5618464D8BEULL, 0x457101FADF4E584FULL, 0x3E79F359B7C27D52ULL, 
            0x8AA8882E33E86F08ULL, 0x11876D2D6B232C08ULL, 0x9EE7865DFDFC7045ULL, 0x7B7E795AF9896773ULL, 
            0xFBD676106652DDDCULL, 0xF4EEFEC8CCF5D241ULL, 0x961E556133E4555CULL, 0x8C2BB8D33B121181ULL, 
            0x976CCC4AC566E02AULL, 0x745EE8CCA3A87EE7ULL, 0x55282F93A3456C89ULL, 0x187D72C856E1089DULL, 
            0xA5D7D2D6C6D2F39BULL, 0xBAEA36AB4353C3F2ULL, 0x899D11EDA1D25334ULL, 0x2389663DDC9D7711ULL, 
            0xDFF24260A06C1E6BULL, 0x895919E1CBA49B69ULL, 0xF3EE804376299B0FULL, 0xAB28CEC199016BF5ULL, 
            0xAB4A406E1B85B37AULL, 0xC23714290390BCFFULL, 0x51EACFC07C2E5837ULL, 0x5BABB2F0D8613EF8ULL
        },
        {
            0xED1E58A93760E47AULL, 0x38BAE4383719218EULL, 0xCA0AF52EA05CCDEDULL, 0x04D9821DE6CA4DBEULL, 
            0x325CF338E44F39CCULL, 0x158CBDF899BD9A67ULL, 0xB127E1C03B79783DULL, 0x6C2E7EA97CB371F1ULL, 
            0xC3CE31B336470D44ULL, 0xE55C21895C5971E1ULL, 0x425E4CD1AF27A3F8ULL, 0xBD386A825D5DC9FEULL, 
            0x09DFE5AFE7513B38ULL, 0x2B599C196C9AA726ULL, 0xFD9BB79D1B044CC1ULL, 0xDC55A38E45EC02FEULL, 
            0x2FBEE8F3F1A67CB6ULL, 0xFFE8E9336E2B8D5CULL, 0x3991EAA3A8DF6E6DULL, 0xFC1AE444F49EE539ULL, 
            0x97E484210111D3D9ULL, 0xD2EA2214EBF06A0BULL, 0xE909BD2AF04B3891ULL, 0x67D9E3F03028F7CDULL, 
            0x914C50A669F9E6B8ULL, 0x472718A54BD3D84DULL, 0x494471B320C75C8EULL, 0x70408A19A3B067C8ULL, 
            0xF795DF696D0E02B8ULL, 0x423FAB83704BA793ULL, 0xA7EE51E31AACF218ULL, 0x983CA2BB8D3B5816ULL
        },
        {
            0x88BD9E2048D7AF95ULL, 0x53AFC9F8C2EE42B0ULL, 0xB0B2783B23284FCBULL, 0x289C1E8DCE0AA40AULL, 
            0xEB47C0633490D7D6ULL, 0x409511AEDE6EE7C7ULL, 0x8AAD17F5B05BCE1EULL, 0xEA98F6D8E6281E0FULL, 
            0x51BA039DC43F072DULL, 0xF449D2432C09A04AULL, 0x0BD263BFFDBED07EULL, 0x46DB4AC27D9D4035ULL, 
            0xB84E6A599D79999AULL, 0xADB5C398FFA3FA3FULL, 0x386510EA79ED3887ULL, 0xB291205DCC1156FBULL, 
            0xE45F6B47BA962ECEULL, 0x3CB6F34C0E4C8505ULL, 0xA0016AEF2556B01BULL, 0xE0AB4BC89E04A4D0ULL, 
            0x25F3FFD8DD1831BDULL, 0x2FD0BE54EE2E6A3BULL, 0x3E9DBB5144DB3645ULL, 0x6684957D43147925ULL, 
            0xE51D8E68C64D9D2BULL, 0xDD8BE1AF819D0757ULL, 0xD6D3B2619C3FFBD6ULL, 0x693A3BB1A372A88BULL, 
            0x88BEAA71EB827BA0ULL, 0xF5736524125130D4ULL, 0xA5C3CF2BF78C35B9ULL, 0x4428BFF0A5127EFEULL
        },
        {
            0xAB81F2014B61B572ULL, 0x7F47928B0FE6E4DDULL, 0x13C6F84B2E953C1FULL, 0x4720DA3429D40004ULL, 
            0x6EB562D3266708E7ULL, 0xBAE5B71E49CE9E6FULL, 0xECE2EEDA7460C35CULL, 0x436BB718BDDC6BD4ULL, 
            0x38105D36158522ABULL, 0x2328F2A7E9C66143ULL, 0xA5FC4FA91400777DULL, 0x5EE1F8240461299DULL, 
            0xF99341D2FDBB58F3ULL, 0xCA46AED8859F0DAFULL, 0xA2691A21671F08C1ULL, 0x788CB77AA15C28C6ULL, 
            0x32643ABBE41EB662ULL, 0x8C540723DAD5911DULL, 0x3A5F806814C22AE8ULL, 0x6AC1BF6D50DD56D0ULL, 
            0x061EA44E5B7B1420ULL, 0x19B63A86EE6B1F14ULL, 0x7138349A50132341ULL, 0xAE9B1B7E6704BC5FULL, 
            0xFFB5CF3C3F3D9001ULL, 0xAFEF8F3D9EE5D682ULL, 0x6B13197165EF1275ULL, 0x0E23FCC0C14FBE96ULL, 
            0x6D0B7DC2FE865FCCULL, 0xCEFAC552655193FBULL, 0xFF370BE6135C6207ULL, 0x7C6F946A4D339C25ULL
        },
        {
            0xE4ACB053C07A1707ULL, 0x3C19434515106B57ULL, 0xEE61CADAF2C3B19BULL, 0xB20FCD7E64E45F3AULL, 
            0x8F9492FEE1139E76ULL, 0x932826FEEAE75051ULL, 0x3485310CEF8C0C9FULL, 0x93A4B5BFE92704D2ULL, 
            0xCABE7C6611588569ULL, 0x2F9EBA05DE8B7325ULL, 0xFAB9A6C6D2CEE4C4ULL, 0xEF946820D49D3428ULL, 
            0xAB7F6EE51B0EEAC9ULL, 0x009BBFDFEA319A0AULL, 0x60249F3F49AA623EULL, 0xB235EFEED608ECD0ULL, 
            0x650831C30C866A90ULL, 0x635B2BABC1470BC9ULL, 0xDA328716E37C55ADULL, 0x183948349B5566B4ULL, 
            0x69570AA401498824ULL, 0x78FB321F63432880ULL, 0x5FEBC24692EB8BA7ULL, 0xB2B3F4AB709B16C6ULL, 
            0x64F4C123FC9907E7ULL, 0x248228177F297B05ULL, 0xE736D12DF4ECD370ULL, 0x10A9267FEFA250A2ULL, 
            0x891A055CBE8A7817ULL, 0xB85E041E2D3B6B43ULL, 0x77A98D9E29C6875DULL, 0x7921A2B36EAAA492ULL
        }
    },
    {
        {
            0x5423291B56563DD8ULL, 0xC3066C0C8C8166FDULL, 0x8B71404E067B0BE2ULL, 0x0050E2F2BA0566DFULL, 
            0xB90DB13778295953ULL, 0x2330FCC7FAE9579BULL, 0x817BB5B5F8238D01ULL, 0x42472DE672191B15ULL, 
            0x292FEC54727DA383ULL, 0x3FCB00C6F1D1D272ULL, 0xF92F9F8BD39F2092ULL, 0x2B1A8650E9C90639ULL, 
            0xDB7149F17A968BE9ULL, 0x882D3651C83EEE3AULL, 0x58E4258DC79D0A72ULL, 0x759F460F1FCB833DULL, 
            0x9048373A8B75A29DULL, 0xF5C3CCB293270CE5ULL, 0x1D88DA17086ED9CAULL, 0x2862621E45C7F4F0ULL, 
            0x2622EFDF4E0F6904ULL, 0xBF1B22E473845434ULL, 0x8057C5FC52094EAAULL, 0x5FE3E5AB4D7F85D2ULL, 
            0x27DA14491B97752BULL, 0x1F72F73B15A9E842ULL, 0x76E8CC0A92AA9BA8ULL, 0xEF05AB6F722AFCCAULL, 
            0x1304587177D2752AULL, 0xB51F041E8A9E86F0ULL, 0x343C57A401B186C6ULL, 0xB3219CC0C1DDB495ULL
        },
        {
            0xA46DC03EEBEF618CULL, 0xE6CD2FF0B7A62A0FULL, 0xBA5AC4F2AA15166FULL, 0x26811597C8AC4BC6ULL, 
            0x11DB3DEDAC1428D5ULL, 0x0F784D1AB41C5E57ULL, 0x52925A66F5FF3A90ULL, 0x52FA8F176483499AULL, 
            0xDFE556F692161E92ULL, 0x308A28B626AB6FE5ULL, 0x49323AED30F10A96ULL, 0xFC58A5D38B4CE19AULL, 
            0x4A6202C3DE91AC9DULL, 0x8E8B8F20D26CA3A9ULL, 0x006B22D8E1A44445ULL, 0x187EC691CAA2C35EULL, 
            0xE8575A7E226C95CCULL, 0x84C173A14DD5C84BULL, 0x6BC1E5A4FD2ADABAULL, 0x17F76734B6E0DAB3ULL, 
            0x5A65019CD3891A4BULL, 0xBE31B5F3CA7B96B4ULL, 0xF6A83979BCA294FCULL, 0x922ACE65D4FC928FULL, 
            0x7A2E626D8424D7E7ULL, 0xC6F9DF38E7E0ADB0ULL, 0xB7D224F2EDE06774ULL, 0xD1AB039BC3D5175BULL, 
            0x01D4BC9406F16762ULL, 0x0388B51FE6CF9D2CULL, 0x6AD28CF7233C3A88ULL, 0xE087F91F3280E557ULL
        },
        {
            0x7EDBD47B2E5AC826ULL, 0x4EB35894BA7383C6ULL, 0x2D4625541DC7F6EFULL, 0x5E3212F53E6B6B81ULL, 
            0xC3A210A4E7DC5AB0ULL, 0x434C111EA00F6665ULL, 0x56A6E3463F94B56CULL, 0xAE47F02F98591B04ULL, 
            0xE8C5975F62084AD6ULL, 0x800D54D08E9E862BULL, 0x9EA711D54FB7852CULL, 0xCA6172CE9B1425A2ULL, 
            0x4A8EE20698F808B4ULL, 0xFFF90FB336053061ULL, 0x215F0A2883E252DBULL, 0xC805122D0DD9019CULL, 
            0x051BE02400B50D4FULL, 0xF1B0CCEC958396DFULL, 0x8D88AC376B9197DFULL, 0x8FAFF187BD43F412ULL, 
            0x27F2B26DF5B6577CULL, 0x10D33CF1C31145D2ULL, 0xA7CD6A54952F33FFULL, 0x30924D0A90D1C3BDULL, 
            0x2978528DFEF1DCA8ULL, 0x7EF6FC9B1381BC89ULL, 0x1601371C3B5C0E95ULL, 0x2321667CCB72CAEAULL, 
            0x2FAF13EEE5280C0BULL, 0xEC30CD120FF950ADULL, 0x19A8FBC732EA7426ULL, 0xDF5EC6BE692E0C40ULL
        },
        {
            0x082DA0377DBD28A2ULL, 0x6B86D8A7929ED431ULL, 0x963F29491A5125FAULL, 0x83525DBEFB8CD593ULL, 
            0x2DEFAA8B696B9B5EULL, 0x7B0283D7995960F1ULL, 0x93C4D6243C139C8FULL, 0xBED4E9A93AB6680AULL, 
            0xB0E665534585E990ULL, 0x51C1409BF227009CULL, 0x0016454E6608E8E7ULL, 0x3452433A6B6C9403ULL, 
            0x1652E50355728474ULL, 0x24B0BEEC43A0BB43ULL, 0x5277BF99EC99D3D8ULL, 0xC3C9A3467C9782C6ULL, 
            0x1282EB6E4641A52FULL, 0xA3B03306FF9050FBULL, 0x0210ECB9D0C7F651ULL, 0xC0A0E6ADF2AA16FFULL, 
            0xCAA775032A010BFEULL, 0x8450C1BB8704EBA7ULL, 0x98C43BBC724BE1ECULL, 0x4922C5B34C580E0CULL, 
            0x374370F780BDC749ULL, 0x202532BBADD92674ULL, 0x1441B1A376EBCD69ULL, 0x9FC5A6DA8A6B528AULL, 
            0x86FFB0C07C002052ULL, 0xB38490456A2E27F0ULL, 0x3DC38C9C512BFAC0ULL, 0xD0DF358AA0A51414ULL
        },
        {
            0x283DE7FA635BCDEEULL, 0x9839E162C88A2551ULL, 0xD35DCF624EE50641ULL, 0xD0BAD4D832218DEEULL, 
            0x44D2AA0188FF4411ULL, 0x295D1F2D563DD3E0ULL, 0xE26C658E83EE4CACULL, 0x1376019E5FE648A9ULL, 
            0x02DEE61A90EDFE54ULL, 0xCC6FACDDE80A8919ULL, 0x017AD8CD684ED490ULL, 0x7086E743E3F742E4ULL, 
            0xA9CD1A45AF45232AULL, 0xDD651122B79F359EULL, 0x4249940D08967E34ULL, 0xBCE7F336EC929281ULL, 
            0xBFC0E3D5354543E5ULL, 0x7C85A0B5773F0032ULL, 0xC100FE095FCA94AEULL, 0x02D41EDE33120156ULL, 
            0xAC82D8051336B82CULL, 0x6916B193B99ABA48ULL, 0x466EA52B61869264ULL, 0xF952EDCF25F3D595ULL, 
            0xA5EEDEA708B51FBAULL, 0x179C9B47D53BF91FULL, 0x00AE1D16A32AEB90ULL, 0xBF2243113AA6B1DAULL, 
            0x047A464D2A662ADDULL, 0x861835C030B334ABULL, 0x7BC079543D7055A4ULL, 0xF93334F721F86B45ULL
        },
        {
            0xFDA926C9F898E30BULL, 0x640AC8BD1F0C616BULL, 0x9C70773B7E64264AULL, 0x89235F770761D4F4ULL, 
            0x07F2F98ED38EBA4CULL, 0x0CA1DB63B40459A8ULL, 0x19A635960C4C7474ULL, 0x07C58E538034AEB4ULL, 
            0x3EE481D945390FA4ULL, 0x0B86CCA32B3128A1ULL, 0x67266D6B9CDB7FB2ULL, 0x10142D9680E8EE37ULL, 
            0xAA3F2B8B1C4C885FULL, 0xCBA53452FBAD18B7ULL, 0x93EF58BB947A9EF5ULL, 0x4A0D2CFAD26E5A82ULL, 
            0xC75EA1315DDFA991ULL, 0x9143CD32C92922F1ULL, 0x10DF966E225D720CULL, 0xEA55CD3110DA78AEULL, 
            0x6491D50A7F295019ULL, 0x732FC65B6AD14F34ULL, 0x504E62F4B603279AULL, 0xFBFD38684DA416C4ULL, 
            0x725484B0D75B81C0ULL, 0x0D1AB1F382461BD8ULL, 0x55E23E446E83AD7DULL, 0x8CF76A13303C53ECULL, 
            0xD1ACCBE7F32F2413ULL, 0x0C011DDDE2DEB748ULL, 0x1411EF739025D33FULL, 0x38E316A2F404B7C7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseDConstants = {
    0x1166C026955D95D4ULL,
    0x39C81D19CF24DF0CULL,
    0x778B261FAC775BF4ULL,
    0x1166C026955D95D4ULL,
    0x39C81D19CF24DF0CULL,
    0x778B261FAC775BF4ULL,
    0xEB74340281636071ULL,
    0xD51B7D446AFC89EFULL,
    0xE8,
    0xAD,
    0xA0,
    0xD1,
    0x7D,
    0xDA,
    0x30,
    0x48
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseESalts = {
    {
        {
            0x6D427D1993DAF378ULL, 0x489CBED9794F6F9EULL, 0x6067A322C64E3A30ULL, 0xA0538C66A9C95EACULL, 
            0x3E612D73E9ECA8B4ULL, 0xE3018FE1AA6BB43AULL, 0xEDBD197B5E39C929ULL, 0x9FF4C4EFE934DF14ULL, 
            0x89FC7BDF4AA07C06ULL, 0x20C1DE8859B6F252ULL, 0xDAEA7655C04F1684ULL, 0xC51A4475AD4F77BEULL, 
            0x2F0182F3327D303FULL, 0x66D7ABB5EA106644ULL, 0x9BBFAD5EE4A5F331ULL, 0xF25C89EF18B4CEC8ULL, 
            0xAF7B6C21827BFD9CULL, 0xF8A7185F99F2697AULL, 0xA72860F5D4AF7F3DULL, 0xE0E8B539A40C253FULL, 
            0xF20B4322F078E4C6ULL, 0x6FEC8EE00B5E3FB8ULL, 0x0F03C53D32E3050AULL, 0x707557CDB272DBE0ULL, 
            0xDF3D1F6AEBD44544ULL, 0x02D1137FFC12B492ULL, 0xE8761F8CD3F53ABDULL, 0x8AEC507CE754C264ULL, 
            0xE653B043206119D3ULL, 0x95FE9113CE25ED8FULL, 0xF662394829C92600ULL, 0xD08BF383B3CCA9D2ULL
        },
        {
            0xA0BA9991F1774300ULL, 0x5E5565E6DA465BA3ULL, 0xA488AE9354B6E0D4ULL, 0xC399E0AB93348AF0ULL, 
            0x3363BC409EA253DCULL, 0x1D0A0E65E19AA8E9ULL, 0xCB73F5DEAC0A2405ULL, 0xFCC36DD99B4BCA19ULL, 
            0xFE05BD8850AF9317ULL, 0x8A28C859E8AC66D6ULL, 0x0FD5682C25871E73ULL, 0xECD8FBCA45BCB523ULL, 
            0x7A2E85F05F094736ULL, 0xD9C13DCDB4035445ULL, 0x5A52C3B8C372A9ABULL, 0x21CD9B391D96011CULL, 
            0xB01A854BB525B611ULL, 0x1FB7F736E25153F8ULL, 0x1462D19198766583ULL, 0x5D6DCF0F88A6E321ULL, 
            0x2E799F951CB1ECB9ULL, 0x26C3BB199AE8A04DULL, 0x21009747CC0F806BULL, 0x41F8265F9A898E3BULL, 
            0x273F123A42E3CDF6ULL, 0xD82A4DC6BCA46337ULL, 0xE672DD682C3F0684ULL, 0x79C952BEC549459AULL, 
            0xA184FDF5841610F6ULL, 0x6B7002AF2DD209A0ULL, 0x021FD2BD0C23FDF2ULL, 0x8EBF1BF60CB2B2CBULL
        },
        {
            0x4D23693A558DF1B5ULL, 0x3CC1AE9BD65DBC8EULL, 0x35BD9F04817EE6C6ULL, 0xA71A86DD58C04546ULL, 
            0xD7A19527535746D0ULL, 0x7D3EA2900D61C93EULL, 0x5DA335680A8E6845ULL, 0x9F4803F5340FE012ULL, 
            0xDDA890ACB13E9D7AULL, 0x3D44B55B299F686AULL, 0x5C9C53D16FDE0847ULL, 0xBAD18AFA3F9E6580ULL, 
            0xE3520651360B2777ULL, 0xFC54C73A0B1DA8E5ULL, 0xB5BE429F6002051BULL, 0x8D9CD23CBD584C9AULL, 
            0x005532DA6C434164ULL, 0x664219FE39E6DD8DULL, 0xFDC797366B419AF9ULL, 0x428DBC0D7DFF39F9ULL, 
            0x37024CFA14407623ULL, 0xBF0E5FB8ADFB4D23ULL, 0x9DC0FEBCDD246C57ULL, 0xA503B61C7C43A1B9ULL, 
            0x8661E3C2F86F6496ULL, 0xCD76C92B35A87A8CULL, 0x46D26415A7A62DFCULL, 0xC46266DF009D8ACBULL, 
            0x19D7738F36B69F98ULL, 0xEEBAD8CB683AA3B0ULL, 0xE95E138E13A8C259ULL, 0xA194C8133C5A12A3ULL
        },
        {
            0x688422BF4B574080ULL, 0xBA7D6ABE6C77FC3FULL, 0x15F442D2325B0D01ULL, 0x2C4D3E78427B466AULL, 
            0xC1B9BCFD65CB64B7ULL, 0x36C96F4899B37896ULL, 0xEF8B1E439DFADF1FULL, 0x49BB9E1690C2EFAEULL, 
            0x377C72F9990BF0FFULL, 0xFCE57BE5E3F1A374ULL, 0x1AD26671A46B4CAEULL, 0x3BBE6AC97D77285CULL, 
            0x80F5F872E1DAC441ULL, 0xA32F426183D38559ULL, 0xAFCE85F14AD506F0ULL, 0x3449339541631E71ULL, 
            0xCEE8E0C6534B8CFDULL, 0x678DD00D3ECD3CC7ULL, 0x0BF17C0DB39356AAULL, 0xEB2AB455D55A0B17ULL, 
            0xBECCF1A9973CA617ULL, 0xC838364755347470ULL, 0xF85B80C95E1B77CCULL, 0x66B660500C7F7395ULL, 
            0x67818C71CD53B75CULL, 0x3064774E5368DD78ULL, 0x81A33CF3D365A686ULL, 0xC34BD1EB9C8F4626ULL, 
            0xF110F6E7EFB868E9ULL, 0x4C9B46629F1E4EABULL, 0x470AF3B91E6CC1AEULL, 0x44C03F8EBF000E58ULL
        },
        {
            0xBAC05AA4C7AAADE6ULL, 0x1A6BACC0333951EEULL, 0xCB111BE58438E971ULL, 0x6B7F60A82D57AC51ULL, 
            0x429C9559B8CA6640ULL, 0x3B0FD58C7DA687D4ULL, 0x7D10E63CD94C69F2ULL, 0xA13D002730966F66ULL, 
            0xE730A55BEB91C33EULL, 0x4FC49A41866E4D88ULL, 0xDE600B3F0D65557DULL, 0xE43817DF322E4E90ULL, 
            0x96D271C67B041896ULL, 0x39DA480C330EA1BFULL, 0xA2056C8109411DF2ULL, 0x8CD0B003DCC28547ULL, 
            0x62A3179F75F8E1D5ULL, 0xD8CD0A2EEC9939D2ULL, 0x991AD7D1A56C36AFULL, 0x77402077AF07396AULL, 
            0x99CE26E10E5DDC1AULL, 0x69F104183D13C078ULL, 0x9099DC19780FE827ULL, 0x863B03480B17878CULL, 
            0x787594EBD2CD6FDEULL, 0x2B274346E1FF2D48ULL, 0xEC3FE0A676EF1CB8ULL, 0xBC6D2D45ABCAD0A5ULL, 
            0x573BB56D39A1581AULL, 0x9AB03D36544595ADULL, 0x991A003A75F77CAFULL, 0x7622F59F00D3026EULL
        },
        {
            0x163FD9EEA174EC1CULL, 0xF434B451A2942F3FULL, 0x56EEDB9EF4C45290ULL, 0x641349ABFCB0512CULL, 
            0xCC39E92EB37E4DD5ULL, 0x5FB82837E7162B6BULL, 0x3AF98A0064E53A27ULL, 0x0E08D3FBDA9D4E6AULL, 
            0xB23A094BDEBAA30DULL, 0x28D54A39265A4031ULL, 0x226C165984DF8381ULL, 0x7ECBDC2DDC1CF2B5ULL, 
            0x70BBE0BDE8542D9CULL, 0xB643258258E842F8ULL, 0x8CC44658C1DDC554ULL, 0xD65F47435DFF5021ULL, 
            0x6E3E0B1EE59346A7ULL, 0xFEDBF0C1E2C38549ULL, 0x2772EC4236704B37ULL, 0x62B17BC1388074F8ULL, 
            0x853C805CF24BC51CULL, 0xA3951B2DB48F1A41ULL, 0xDC9E5CCB430D0C43ULL, 0x28B4BCFBD480CE86ULL, 
            0x6EF97835F4666F6AULL, 0xCE360677AAF6CA08ULL, 0xB4A1B6D34D7284FAULL, 0x1F781B114BE6952EULL, 
            0xE8317F4EFDCC801DULL, 0xCF8E368A9D9DF407ULL, 0xFAA545A91EE1CDC4ULL, 0xC8F05292C7AA4131ULL
        }
    },
    {
        {
            0xCD9B21B18130A98DULL, 0x88DBDF7318BA59AFULL, 0xCDD75186079684CDULL, 0xC231B8CD3A87847FULL, 
            0x7B76FD1C9DD6B4D8ULL, 0x76DE8C4FAE27C06EULL, 0xF077DE05B90C0C46ULL, 0x5797896771AA6FD6ULL, 
            0x91230FCA3B3B5B48ULL, 0xF7EC3EEC9BC018CFULL, 0x376A94ABA14E881CULL, 0x4659277E329D54D0ULL, 
            0xB379FC4C4AE42CEFULL, 0x4A9FF49308072C1DULL, 0xABEE73D43B471596ULL, 0xEBA57C59B3BA9DEDULL, 
            0xD085A713ED1D9A20ULL, 0x4C68580F4E40429BULL, 0x165A4BB1856A14A2ULL, 0x754A119DB4845080ULL, 
            0x9B9BE2F4158A756BULL, 0x6B88C9B4FCB2E5A9ULL, 0xB9C430076DF74A15ULL, 0x9BDE6F77524F71E7ULL, 
            0x374C8253ECA82847ULL, 0x6650AA4F5E118AFCULL, 0xC6A6AD33398BF333ULL, 0x5F11941BADC062D7ULL, 
            0xD830B9C36DDF5B34ULL, 0xEC27D5C08245747FULL, 0x88D340763EFBE01DULL, 0xAF903EF64903A58FULL
        },
        {
            0xE4A83F1585E500FAULL, 0x3B2669EF0E1CA738ULL, 0x21080BC9F21D1EA2ULL, 0xF9F0B41238727B91ULL, 
            0x8D14D3051563C498ULL, 0x5F824713E5C56108ULL, 0xD14ED930C61F9406ULL, 0x066D2DBBE545E156ULL, 
            0x57DD0744830503AFULL, 0x9FA3A9FBA9328A8CULL, 0x535F6D3C53DEA9B9ULL, 0x08E5D655636CBE54ULL, 
            0xAF82906209E92B19ULL, 0x0A2084F91ACE2083ULL, 0x1EAE16B61979B74AULL, 0x76D5B2EBD048F973ULL, 
            0x43D14E730F8C2B29ULL, 0x2E4B61A9E90250A1ULL, 0xCA541947EF514B4FULL, 0xEA7B58FDE6F963AAULL, 
            0x2087E3F2A9D96C8CULL, 0xD7B40390ACE45C76ULL, 0x70E8BF7DAA0F4156ULL, 0x51CFFE6DF0CD9DEAULL, 
            0x03DEE3456B29CEE9ULL, 0x4266CB64F9A56FFAULL, 0xDD2431A8BCA0122EULL, 0x9AF3EDFCE60F7C43ULL, 
            0x8B05FECA9A6C2495ULL, 0x865D51E934961BFDULL, 0xD2F2026C326FCBACULL, 0x91482CAD31AE67BDULL
        },
        {
            0x1E06FDF227DFC596ULL, 0x16EB44B04EE4A4DFULL, 0x585001DD5319F136ULL, 0x05ADE1C22EF310D2ULL, 
            0xB357A0FA2F120412ULL, 0x4E44229C84A05EC4ULL, 0x2C19E3231EC108C1ULL, 0xD949EBE68D5688F7ULL, 
            0x34CF62339B720A7BULL, 0x18F8F5BE7D25395FULL, 0x959D40F86004613AULL, 0xE88C8E3FB0EB29B7ULL, 
            0x933B99B612A4C464ULL, 0xF0355E1BDAE1AF7CULL, 0xB243EB52F61A219CULL, 0xCC5C74AD407C0DF2ULL, 
            0xD918A91630016ECCULL, 0x91BA0E34543EA8C9ULL, 0x207264C7DFF6840FULL, 0xB09CC3F620ED6DCBULL, 
            0xBF07ED512FEEAC83ULL, 0xC11E9650350A8406ULL, 0x747984E9FA86C59BULL, 0x1EC7BA472E5765E2ULL, 
            0x414AC5AAB48CE758ULL, 0xEB7A3BDEE57128F5ULL, 0x0845756065C08049ULL, 0xE4276404633F0DF4ULL, 
            0xD65B403F9CC7334DULL, 0x235388DCC6913C27ULL, 0xD83EE18059335682ULL, 0xE6F6146EF8BC391CULL
        },
        {
            0x4AA51369F519A84DULL, 0x9FB51D101C803C11ULL, 0x48B85248A824B3A9ULL, 0x79EA6A454C8C3145ULL, 
            0xDE445C306F4A08C3ULL, 0x9C6E58E727225576ULL, 0xCB1742AA11EC5842ULL, 0xAF7DDD704CDE30EEULL, 
            0x118F60B3D6D77DE4ULL, 0x95D9BE22CB2ABE5CULL, 0xDE3F612818AC7E0BULL, 0x1D8BD140099C052FULL, 
            0x8575B54CA30D2A90ULL, 0xD09587FC5BE79E01ULL, 0x68CAD9A7E9D2D46EULL, 0x69EFEDDD0970058FULL, 
            0x14F6A21C453EA710ULL, 0x1138F21C71D8BCB9ULL, 0x3DC6602DC0F09552ULL, 0x77E6FA88981C8702ULL, 
            0x7224DF154EDBFF91ULL, 0xFB7D0CD47C67F585ULL, 0x1237592D236AAC4AULL, 0xCB12075DC5A6CBD7ULL, 
            0xD51ECB06818CC957ULL, 0xE1224558E99104F9ULL, 0x58635468E07525C2ULL, 0x2AB1C1D584C55F54ULL, 
            0x57BA22013FB638C5ULL, 0xA072240264672681ULL, 0xD3D46E9D5CA3B2D2ULL, 0x14C8B7F540A8628EULL
        },
        {
            0x2AB8AC6A80B93F83ULL, 0xF697B8CC50E1EE94ULL, 0x31B027102E11C1B4ULL, 0xDFD3EC5CDAB2FCCAULL, 
            0x00164A1461D2EE1FULL, 0x145257BC6472C8CDULL, 0x3B041D9AA9F7EE29ULL, 0xBD4465E8D255E9EAULL, 
            0x1137AD4390A866ADULL, 0xD187681F715905E8ULL, 0x13A8C0EC442F5D8AULL, 0xA0D705BCC073CC1AULL, 
            0x1491530CC0806C75ULL, 0x708D98022DA9474BULL, 0x78E4469AF5B89C9EULL, 0xB3D645C7B526F25DULL, 
            0x2ABF31F53507A2C3ULL, 0x78062F0CB3E7B7FBULL, 0x6C16F6BCF41563E7ULL, 0x9D0125DB9D66A430ULL, 
            0x633D2841E5B27FC5ULL, 0x4AC0B937770BD756ULL, 0x997563F88C87ABA2ULL, 0x5EBCBB1D9904546EULL, 
            0xBCB6C665673B0BD8ULL, 0x2BC7BE80C2C04812ULL, 0x7CADBDC968071052ULL, 0x9E8B03B7239151ACULL, 
            0x1B0C44855DDBCB85ULL, 0x9AE27FA524949B7DULL, 0x15A69E4CEAEB75BFULL, 0x13C80EAB7026674BULL
        },
        {
            0x2800D7BCDFA5DA7BULL, 0xB6188832F667A24FULL, 0xDE24087F87E49670ULL, 0xFF3BDED516343C6FULL, 
            0x8B208EF645BF8B7AULL, 0xA1A2805547B206FAULL, 0xEFF2F23617F2D07DULL, 0x42C1EA797B350128ULL, 
            0x0E4ABD1C06508D16ULL, 0x0CFDD404678E7B9BULL, 0xBC56B1FB0297DC59ULL, 0xBD6524E7E701DEACULL, 
            0xD7AFAED30D738239ULL, 0x00AC112D1F6FB303ULL, 0x226D843F2656B451ULL, 0x5FB2D49719EC9288ULL, 
            0x8C091FA53AA7A7E0ULL, 0x1639E7948B52A9CFULL, 0xF3D942D08A8BEE54ULL, 0xC9EC1057C2335253ULL, 
            0xDE3065ED85B96C7FULL, 0x54A346AAFDA210FAULL, 0x3B2269E9700D81D4ULL, 0xB1ED8D77A79CD0BBULL, 
            0xDE2BDF44C9B1AA53ULL, 0x3DFFF41920D4A48AULL, 0x19564FB5C90335DEULL, 0x58E807A70F8C0A64ULL, 
            0xE75335BA848A3422ULL, 0x0353568F26E205CAULL, 0x9F8FF72685A52988ULL, 0xB73172F8A857185AULL
        }
    },
    {
        {
            0x1AE5B89D833CD29AULL, 0xEA19D0AA9A728900ULL, 0xB10AAC2DA70ECB95ULL, 0x78F00D9F51B38808ULL, 
            0xDCCC8574EE731AE3ULL, 0x8AACFFD0B05BEA79ULL, 0x695DCB180FBE850CULL, 0xFD633DF8413B99DBULL, 
            0x1DC1F6062DF23C11ULL, 0xF9697048C2DAF7A4ULL, 0xD018F1BB2C3232C7ULL, 0x923133380ACC52C8ULL, 
            0x92D1B8191F0EDBA2ULL, 0x64B4CBD4DE964153ULL, 0xAB27B5A59BD67F85ULL, 0x9B685B5034AB7A26ULL, 
            0xF0B752582CE9267AULL, 0xE923418EE972F949ULL, 0x22EE01EA114F10EDULL, 0xC8240BA46DCF006CULL, 
            0xD9ADE63D36DBC5AEULL, 0x2F5E2F13F50DF22CULL, 0x0A204F945E4CC507ULL, 0x2AD17FF7FF3BBBD2ULL, 
            0xADABF0E65D88CCC0ULL, 0xB1925B4CD726E842ULL, 0x02B65C891FC99F85ULL, 0xBBC93D8819C29FF9ULL, 
            0xD76836216F92EDF1ULL, 0x4963C8246481C313ULL, 0x47F764ADE1B12B62ULL, 0x902EA6C80F56163DULL
        },
        {
            0xBCF4110F2E9CC4D3ULL, 0x94B9BF182899A68FULL, 0x7C4393DF7C060397ULL, 0xA31A28EC1929CDA5ULL, 
            0xABD3BD1E3FA3CD7CULL, 0xBDB0A89B8B3113E7ULL, 0x225CC78BA9701A10ULL, 0x959D85D2DEA11FF6ULL, 
            0x4122ACFE85D465D6ULL, 0xC124E370FCB4B873ULL, 0x2791B1E73AAAEBBDULL, 0xC34F1EA70E0A5D77ULL, 
            0x2D1EEBCC19CE95E4ULL, 0xFEA030CB698DBDDFULL, 0xBA8F5A0E32105B64ULL, 0x56ED528236AFF116ULL, 
            0x97EC0035106CEF92ULL, 0x1CD8B42AE78A9E09ULL, 0xA33C98C45CA0C053ULL, 0xF6A42CB23AC079CDULL, 
            0xDBED1684D00982A1ULL, 0x8EE15B153651CC80ULL, 0x895EE8481CCE244AULL, 0x95DD23571AE27181ULL, 
            0x4DC3FA4F9B24A23AULL, 0x4BDF3D44C2C3C236ULL, 0xCAE29B2797A3A593ULL, 0x653B2D578F40EC51ULL, 
            0xA745A805A815CF52ULL, 0xB75FC42B8EC8F595ULL, 0xE79D51A540E512AFULL, 0xA4B69AAD2DD3A947ULL
        },
        {
            0x0F04C30BA8CC8E21ULL, 0x028551D27049DD5EULL, 0x2F15258B28146D95ULL, 0x066E4CA07B65D35DULL, 
            0x5B90832A698723F8ULL, 0x9B154321D39D259AULL, 0x5FFCEEEDDF8C44CBULL, 0x97DC0BA70B22876FULL, 
            0xC1FF0A8C06D403F1ULL, 0x11BA13A6EDA0CFA0ULL, 0xCFE4C8089016996DULL, 0x57EE8D471017ECEDULL, 
            0xB06756611D6A2055ULL, 0xC75A2BAB49914541ULL, 0x9E68BAC080A98632ULL, 0x2EBE7342F86B150FULL, 
            0x8A62D7E05ED0F4B5ULL, 0x2C17A525E5B2A797ULL, 0x69FB69B8D524FA5DULL, 0x6E370F127AB25575ULL, 
            0x015B700AAD9B9A9CULL, 0x47714A8D3F24330EULL, 0x94D35AE053A4086EULL, 0x067C2777631ACF65ULL, 
            0xD8F3FE40E12337E3ULL, 0xEECF616696D56EC0ULL, 0x8A447216E2483E48ULL, 0x0EA695223DD5EC9EULL, 
            0xA4D34496D2EB04BDULL, 0xCEAB9232FBECF635ULL, 0xE5C6C25818C716E7ULL, 0x742C01C809A39885ULL
        },
        {
            0xA3759ED373C87F3AULL, 0xDF99DD055C7BB643ULL, 0x9F6AC775C64CF63FULL, 0xFE88439AFA059D56ULL, 
            0xDF246DCA420628DDULL, 0x5A2D2F8A68229C8DULL, 0x0237DD67CF04CB40ULL, 0xF4643F8D62EE0FFDULL, 
            0x7328F81EE6C6799CULL, 0x45FE01462937BC59ULL, 0xFAE7D3C8DFB82613ULL, 0x91E634CD7FE433CFULL, 
            0xB6D3F40BE14551C9ULL, 0x5F8B48EC8A9B4C2FULL, 0x6893473F03189227ULL, 0x2422B4A292D77473ULL, 
            0x1E914E6F2A412CC5ULL, 0x1BEF72A7279C00B4ULL, 0x29F974AFABEB7A98ULL, 0xECDE06340FA22FD1ULL, 
            0x1F05D78C07DEA919ULL, 0x7371C57800F1AAE1ULL, 0x458969D581962E12ULL, 0x4A121D44BD7D2ECAULL, 
            0xE8E444D9D721EB8EULL, 0x2115907C80DFF31CULL, 0xA7805CB1D93C785BULL, 0x65A309EB0C50D891ULL, 
            0x661B8D252D8CE0F0ULL, 0x6E622EAB078CA50AULL, 0xF9F254F3EEA9F3DEULL, 0xC0D87B47A78064B3ULL
        },
        {
            0x1ACB5554EE033177ULL, 0x3602F88B027A4296ULL, 0x7010B3B69E2C0966ULL, 0x1E3161F59F45E4B7ULL, 
            0xAA7268FB7EE193E6ULL, 0x5B1560CB4992743CULL, 0xD8D079D42D449966ULL, 0x0A5F93303A0E31E5ULL, 
            0x7087DD4B93C85201ULL, 0x78F222B3390BC247ULL, 0x91C7C3470BFB1301ULL, 0x0C60F71E5A172120ULL, 
            0xC691BB7F5387E849ULL, 0xD2BEB87779E093E3ULL, 0x9A629300595A3E2CULL, 0x79F08C63C75DADE0ULL, 
            0x4E597651B62ED2D3ULL, 0xE514010317DD64C3ULL, 0x0076048981221DBAULL, 0xBA0ECF226C7637F3ULL, 
            0x112527D7A7B02175ULL, 0x1AE907C5FE6AC71AULL, 0x12BABB7DB929D18EULL, 0x7D32163898581174ULL, 
            0x83FBD87BB74C0A54ULL, 0x959EB5B71791FB17ULL, 0x0D189FA643581FB9ULL, 0xF0A69F640C0A267EULL, 
            0x4CAD77AFFE8AA64CULL, 0x6DF081D303E5A752ULL, 0x2A430622609F99A8ULL, 0xA3ACE1F29D9C0AB1ULL
        },
        {
            0x8709F63AC0917474ULL, 0x63A571E8C065C407ULL, 0xE35B8AA4E7158F5EULL, 0x3B6BF483848E4778ULL, 
            0x8A557C529F11438CULL, 0xBB3979FE78EDFE25ULL, 0x3ADCD534B63BAE7FULL, 0x943FE32188FAB241ULL, 
            0x694F62C47919D874ULL, 0x5350B1FD121E0834ULL, 0xBE8597C7FAFB7547ULL, 0xEFE1F4941074D720ULL, 
            0x82D653B6D90056C4ULL, 0x2110479C2918D56EULL, 0x7B66C486382686AEULL, 0x53AA14227ED3E86CULL, 
            0xC4A450D4A7434ACBULL, 0x119F995FAB74122CULL, 0x9B302D26DB0EBB66ULL, 0x4325C61B5D5183A2ULL, 
            0x4F84EED831BA34E7ULL, 0x3BE375EBA13D4ED5ULL, 0x0390ABB32229BDEEULL, 0x43EDB2C317EC72AAULL, 
            0xBA90BA6FBE9DB157ULL, 0x07A856CA06666594ULL, 0xAE6C74603032CDE2ULL, 0x5400CC3D472FF26AULL, 
            0x9BEB7CFDCEED5F7DULL, 0xDCD89A8BE43699FFULL, 0x1EB0CF618905C5A1ULL, 0x3119F6194764B8D0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseEConstants = {
    0x467EEACE50E4A946ULL,
    0xFD8820C6B5924C4BULL,
    0x9601547E1CC0611DULL,
    0x467EEACE50E4A946ULL,
    0xFD8820C6B5924C4BULL,
    0x9601547E1CC0611DULL,
    0x93B5C138E9D2E844ULL,
    0xB1D31D8F4E26FAFEULL,
    0x7E,
    0x8E,
    0xAE,
    0xB8,
    0x48,
    0x19,
    0xE7,
    0xA1
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseFSalts = {
    {
        {
            0xFD401B2047C8B203ULL, 0xB23693CEAD1A1823ULL, 0xD1D2177B2ABC5A2AULL, 0x2397D97D710D434FULL, 
            0x14D5B7E5AC946E1DULL, 0x76FE60477D1D223DULL, 0xFF4E9EE52097842EULL, 0x71D6978BE89CD16CULL, 
            0xD9B1CC77D2C201ABULL, 0x6F3A49CE174C1405ULL, 0x852FEAEB65F2BD35ULL, 0x680C11DB3FFE8DF2ULL, 
            0x4D78F6AA36D433B0ULL, 0x4C299A61E1A74AA1ULL, 0x4EC6BA610B0FEE27ULL, 0xD1BF0813DEAC9633ULL, 
            0x2729558A4B9E19FEULL, 0xBA8BB3941DFC8544ULL, 0x62532789C9B3F573ULL, 0xE83EDC033460AAE1ULL, 
            0x352FF619D9F52672ULL, 0x87BCCCF352C630DFULL, 0x74515ED74C816AF8ULL, 0xE8A0E0DB7FA4FD12ULL, 
            0x2F92617B01138C00ULL, 0x97400E1FE86F28E7ULL, 0x1925ACA6B8048144ULL, 0x4E7E5EB6CE58C4E2ULL, 
            0xC8F9378CE20622A1ULL, 0xE18196974436FF7DULL, 0x585E1BEE55BF3B54ULL, 0xD1E9A96084EAB2F4ULL
        },
        {
            0xD4643A1023485C86ULL, 0x0F6F3D80ECBDF9CCULL, 0x574AFF466FA4FD6DULL, 0x9E6CFC051561592BULL, 
            0x4135D223D567CCEDULL, 0xBF38CF1A9F22E29DULL, 0x3047949B48077936ULL, 0x5E1D8E3FA2896D0DULL, 
            0x3A8EE78645199CD1ULL, 0xB5DC62164783F27DULL, 0x3514547F996C8733ULL, 0xA6335976CC3E6E01ULL, 
            0x8331152AE0A38CF0ULL, 0x17E14800C5E4EE8CULL, 0xF2A6F2E11AE89F14ULL, 0x03F51661A6FF5FEBULL, 
            0x0E4727CEAC6C6817ULL, 0x43CCE73FE1A543E9ULL, 0xA19AE57A70C7387EULL, 0x91370D182DA1045AULL, 
            0xFDB866C286DF9B82ULL, 0x3A394C85D76DEB7CULL, 0x7DE5AAB86918D904ULL, 0x1A4E3747D0288CFAULL, 
            0xE9E4E94433BB59F5ULL, 0x9ED1DD963D5D3A66ULL, 0xFF36FB36804DB326ULL, 0x1061F0C16BBD47DDULL, 
            0xBE7748B6737DCB04ULL, 0x3577D1BC8285A34CULL, 0xE983BC0FE8ABFD0AULL, 0x359A7044EB41796FULL
        },
        {
            0x62EAB01D365D6387ULL, 0x66D9AE34072DA52CULL, 0x117C254FA4A52A80ULL, 0xAC4B62E3DD3EC948ULL, 
            0x6F4925D3977C4AC7ULL, 0xFB23CAB8F4BAA692ULL, 0x0890F8D68F65538CULL, 0x7AFD45518BEABC49ULL, 
            0xC58DD75005BC04A6ULL, 0xAED49AC8C77ED6A5ULL, 0x3FEC00D155A1829BULL, 0xBB27E11FB36D8245ULL, 
            0x4ED792781BF89194ULL, 0x38A7AFBA7ACDDB85ULL, 0xA572CC7BD87421BDULL, 0x45BCAFCCDE10CE19ULL, 
            0xA13CF57B46CB7582ULL, 0x7F183F929C9EC22DULL, 0xB11D601EF529C073ULL, 0xEB817F7241107EE3ULL, 
            0xC6AFB82095390829ULL, 0x4DF12BA916B55DC1ULL, 0xA05C2B3B1800B53BULL, 0xD3191E25BA2FFDFCULL, 
            0x6C8081937A908C1CULL, 0x7ABF21FDA0C6D7C9ULL, 0x2705F2596B4C4CA8ULL, 0xF9D2398B20EABC6BULL, 
            0x972CFE2A21A5EC31ULL, 0x19FE536BEF890E8DULL, 0xBCC99A3175D6BBEBULL, 0xD541446EB6991C65ULL
        },
        {
            0xFB798A6573E4D7A4ULL, 0x613BB255336BFD8CULL, 0x8101858A5B3D67D7ULL, 0x4174544C7FDA218EULL, 
            0x5D035C7EF9E85DB2ULL, 0x69FC370AB527A5F1ULL, 0x3F8E3525CE782450ULL, 0x2F95F28D8EC29129ULL, 
            0x88F6DB956E809199ULL, 0x1F1401241DB564B9ULL, 0xCA7E17366E8948BDULL, 0x067011005BCB8763ULL, 
            0xA705C4505C79E084ULL, 0x4E7EBB13A74DE10CULL, 0x1650E39248653CFBULL, 0x430B22FD03A52261ULL, 
            0x879FF97B1508F5E8ULL, 0xEA125FACD86E2236ULL, 0x582CDD438C594A70ULL, 0x9D7DB56400F25CF4ULL, 
            0xD4C663A633CC495CULL, 0xE29EFA4DADBBAA62ULL, 0x97481C59FFA3A528ULL, 0x787A860BB45A9234ULL, 
            0x36E14EA4B22CAB91ULL, 0x7B266B1F4FF5C6A4ULL, 0x3A4851F72C757D90ULL, 0x8714A5A405EC5458ULL, 
            0xA81F145B053C96B4ULL, 0xE29F0D0ED47A2167ULL, 0x5DED41491B6CC88BULL, 0xE74692E15E3C6EBFULL
        },
        {
            0xEADAD92B8277E9C6ULL, 0xC55E4355B3F2DECFULL, 0x2F3952DDF085282BULL, 0xBD34C8947F6AC874ULL, 
            0x2FACFD3A797CC68BULL, 0x5CC23F304F8AEAEEULL, 0xB1780CCF0B01F82BULL, 0xDFBDD9B2C21F4812ULL, 
            0xCB9CF78005488860ULL, 0xB500B383E33D23F5ULL, 0xE9FE3A0B2F3BD248ULL, 0x271B26517B137390ULL, 
            0x992FFB00022D7243ULL, 0x62159B2A105978DBULL, 0xC5F3D8DE9F4506F4ULL, 0xB2306ACDD2B023C3ULL, 
            0xB25283A9EB1C9726ULL, 0x9C407F3921B3B940ULL, 0x1E511CC4DB85B067ULL, 0xA74AE3288FF3B195ULL, 
            0xAC516A281F9EB8BEULL, 0xFA0CAF66D94D0F48ULL, 0x89530E7A261901A1ULL, 0xC0A5DCD349490D63ULL, 
            0xE6B2DDF2FB2C809CULL, 0xD33A9D8C1F247090ULL, 0x40801DD0D344E8BBULL, 0xFD863F7177B577EEULL, 
            0xA3A15049AD977954ULL, 0x4A3A5FA3874A6A8EULL, 0x250D53D46D9F83A7ULL, 0x5187E44B160463ACULL
        },
        {
            0x81D871DCD3EF251FULL, 0xF2DA29E6A6A2A423ULL, 0x88CDF2AF35AD2931ULL, 0xDC2EF7F2E9FFFC1CULL, 
            0x4720AFB22271377BULL, 0x473B002037D6077AULL, 0x9F475BD7F45F1E60ULL, 0x0CE3477A5422E119ULL, 
            0x2A9ADEE2CCAC7DECULL, 0x5FED27A4337969C3ULL, 0xD906CF39EFAABCEBULL, 0xAC56DB322B182026ULL, 
            0x919D6EC465047414ULL, 0x1B89C76D8FE9ED75ULL, 0x815EAE655B005966ULL, 0x6EC3B8E35CC8E315ULL, 
            0x522DF5A9F5D336E7ULL, 0xAC69A1CE367D3A57ULL, 0xC28AF9F32C4ED2EEULL, 0x61E38B1C1129C36AULL, 
            0x7AF6BEFBF5A18956ULL, 0x33402DFBD7AB712FULL, 0x9B4094A57FB49A36ULL, 0x8BCD899E9D2EA476ULL, 
            0xD5C683D97F46FD17ULL, 0x5D40A1D919A9CCF0ULL, 0x021D075BB5BFD409ULL, 0xCA0F7CC4CB4A3161ULL, 
            0x6CC74C23C42414FDULL, 0x576D80343744DD8FULL, 0x464D352618F271C2ULL, 0x4A166C7342502A03ULL
        }
    },
    {
        {
            0x9518675E5502783DULL, 0x3CD3458288EEA510ULL, 0x1837D51672E92986ULL, 0x90A81CFC0CAE5FBFULL, 
            0x0250AC09BA1148C6ULL, 0x4CB27EB9760E9218ULL, 0x9C2E6E53487DFCCAULL, 0x414F9920AEE1E110ULL, 
            0xBCC52C19DBF49F47ULL, 0xF7B93C0CC785943CULL, 0x8257ECEFB97964FEULL, 0x5E879D7B4E1F9392ULL, 
            0x0BDC35FD0974F4E5ULL, 0xEA10F7834E8860BAULL, 0x1328CE0222CABB66ULL, 0x51B9B41DED859E0DULL, 
            0x82C74E209F78ACCCULL, 0x786A46A977FBDAD8ULL, 0x5C7D81B1CAA22BBAULL, 0xA362A945E37AE155ULL, 
            0x49E3FCB43FDBF0FBULL, 0xB81D955EB93AAEE4ULL, 0xE3A261D853AEFCEDULL, 0xBB1FC38B45E6AB0AULL, 
            0xF306E4F1ED3C27A6ULL, 0x8D996553E5787B2EULL, 0x0DDC5F19A6C483D4ULL, 0x7903AF6CAC1F1F87ULL, 
            0xA7A27406455CCA7AULL, 0x4072D8872812D1CCULL, 0x4339FC6C6C5886A6ULL, 0x7F09C7F635AB4CC7ULL
        },
        {
            0x9A84EC7620B49497ULL, 0xEC60910EA26F885BULL, 0x17A5E56204B35086ULL, 0x364F831B238E442EULL, 
            0x3A67012806E13187ULL, 0x64A7BA0E57984DAFULL, 0x0118C692CABEA07CULL, 0xC812962C82D325D8ULL, 
            0x24FF478540BAD966ULL, 0xD0E983799614B5CDULL, 0xAB28575B95665F1AULL, 0x87B5E71619A8C833ULL, 
            0x6EF5827F022CED7EULL, 0x5ED0F1EA6BFBDF59ULL, 0x2A6AA9AF90F56723ULL, 0xAA93B44FE1D960A3ULL, 
            0xB265D20687BC11ABULL, 0xA70B1BBB8DBCB53BULL, 0xEA921BD1ADAE9E60ULL, 0x252830AC9799D9A8ULL, 
            0x96A9051C4C72DB2CULL, 0x34E0810A21D85E32ULL, 0x7E4A8B986604677CULL, 0x6CC42E675542B2D3ULL, 
            0x7D1F72AEFF6D4D36ULL, 0x7EA83899D043E2E4ULL, 0xD040ECF68E940E54ULL, 0xF522CA7A210BF50DULL, 
            0xA0F7B9DDE1FDD656ULL, 0x5B8A1E627557A7D4ULL, 0x5B5759AB8ADD3359ULL, 0xEF8162C3103B2B2AULL
        },
        {
            0xBE96849F4416D1EAULL, 0xAB4EDB86AAB2B9EEULL, 0x99E84A892A280B29ULL, 0x2E345AC8BC0E553AULL, 
            0xB06CB9A4762C780AULL, 0xC6311862DC8F9D77ULL, 0xEDCFAA0111D6B13AULL, 0x60D55F4D8D70B2C3ULL, 
            0x2D3231403A55E402ULL, 0xC7FF9AF0EBC52A42ULL, 0xBFF3BCA363FE21F1ULL, 0xF953DD529B1BC320ULL, 
            0x32B02C3F25EF4423ULL, 0x7FA5EEC084CA6C25ULL, 0x73C5B1DA9D5B2F2EULL, 0xA5926EFA08800F34ULL, 
            0x2C277E7A0EB54AEBULL, 0x2FF371E2DBDB2A3CULL, 0x017208E314B30480ULL, 0x34A71DC67DC36E29ULL, 
            0xD01DB67CE06E9C6AULL, 0xF3F2B45F0F47E491ULL, 0xD5961E33CE920D2FULL, 0x5C215B685D575FEFULL, 
            0xFF2F51C4C65D6E3BULL, 0xA55EC078F0767CD1ULL, 0xD51163CA2017093BULL, 0x9A663EA09725CF52ULL, 
            0x096C691942E0477BULL, 0xB959D046881DC526ULL, 0x7E332A3E56B82E00ULL, 0x4D8E08A875BE3CE9ULL
        },
        {
            0xA1D2EA477ECE0AAFULL, 0x970AEB11B285B3E2ULL, 0x012176D9663E5F33ULL, 0xDDB3D9214F78D805ULL, 
            0x2916591D0B27EEBEULL, 0xA87036146F95E97DULL, 0x07C428C81EFD9B06ULL, 0x5DFD00304FC1D038ULL, 
            0x73069EF4AF3E43EBULL, 0x52FAE49CBB7B1519ULL, 0x81130FFBE56320E6ULL, 0xAF5A98CE12226B02ULL, 
            0x324149AF862AA84EULL, 0x8EA248CAC427C5C0ULL, 0xCBB39E9C00EE63FFULL, 0xC18AF9E01029D366ULL, 
            0x9410D135B16C4954ULL, 0xE23E6D320A749CF6ULL, 0x95DBEEB738416CA8ULL, 0x7469236736E714BEULL, 
            0x5BA3B5C09D529740ULL, 0x29D0014F89C8C759ULL, 0x4412BD3A42E27C04ULL, 0xE247E62F0455C7EEULL, 
            0xBA54746D927BB69EULL, 0xE704B6DD732F8C90ULL, 0xCA0BAAC076C13CC4ULL, 0xE53156ED1B3078B9ULL, 
            0x6BB81A447082F598ULL, 0x3B26DC0EFB4ED99FULL, 0xD1D8159AA3C3E234ULL, 0x8316344A14E19A85ULL
        },
        {
            0x62B6F79D72DF75B4ULL, 0xF0CEEC56A278696EULL, 0x651F63853F179D3FULL, 0xA635ED8536FF9F30ULL, 
            0x718E971C02B7A639ULL, 0x187BD90AA32359E9ULL, 0xF37F34A9C510095BULL, 0xDD4CFE326E1A0393ULL, 
            0xCCD70A976EF126C3ULL, 0xACB28AA0C38509C0ULL, 0xC124966786D2C7ACULL, 0x1B73EC6BAE5041F5ULL, 
            0x87B95A6173D3062DULL, 0x8ED993E7B8F666D2ULL, 0x7B5C21E75E2F1565ULL, 0x2F111F0AE2B560C2ULL, 
            0xD8618CB4A96E3722ULL, 0x2F7DADE7248C94E9ULL, 0x689D1499AB405591ULL, 0x53E06E9823A298B4ULL, 
            0xA5944A2374F00E12ULL, 0x5BC2F84AEF780B82ULL, 0xB9682476FF878C18ULL, 0x615B92EDC8F42555ULL, 
            0xE26DA630340A1698ULL, 0xB56EFF6F8D25E4F9ULL, 0x1AB2FF1E8651EAF5ULL, 0x43D399EF49453260ULL, 
            0x8600185F703DB5CAULL, 0xAB372B5D0B98E516ULL, 0x9DB4F348C5B67442ULL, 0x98E7D333AB46BA15ULL
        },
        {
            0xBB32BE9CE883F09CULL, 0xAA5A0B91BA30B9C5ULL, 0xEDEBC3E5397206B4ULL, 0x99A2183CE9E646D6ULL, 
            0xD035C088E683540CULL, 0x98688BC801BB5677ULL, 0x3B6249767BCB4247ULL, 0x3D9DDCB1A68937D1ULL, 
            0xF2B8380AE49A37C7ULL, 0x1849BB0920052EFEULL, 0xBD7B9161C98DCC07ULL, 0x3437F73D02F653AEULL, 
            0xC7D175B695381681ULL, 0xBF201127A01CAB70ULL, 0xFDA8DFCCB7BF81DAULL, 0x499137D9BFFF9D8AULL, 
            0x4246B79D753FB950ULL, 0x698EA18899744342ULL, 0x6DB9CF85BD7ABD58ULL, 0x09FD6B93997281E3ULL, 
            0xEC834A3F8A117F1FULL, 0xEEA1C0613046C70EULL, 0xE563C85391581DCBULL, 0xEAE1B6002164BA25ULL, 
            0xB16BC67FEFE9C4FFULL, 0x62CD0AC6BAA8C7FBULL, 0xFEDBC4453904042DULL, 0x41CD675BC393CD4DULL, 
            0xEB6448915114F41EULL, 0x1EDB69778079B1ECULL, 0xA405AE2DAAE9BAB2ULL, 0xF8BC7070A62B5B1EULL
        }
    },
    {
        {
            0x2133AEE10E8552ADULL, 0x2A6FE003CD04EF98ULL, 0xB73302F1C514D8BFULL, 0x69A4809897DA116BULL, 
            0xC9E0C559F4332BD8ULL, 0xAF69D294694F7F96ULL, 0xD88020CD5645CB0EULL, 0xE7A0D4234947E3CBULL, 
            0x7BDAE23A4F994BCAULL, 0xCD6A089331779849ULL, 0x9B05CD3B2196CD14ULL, 0x68FBC9724E947C24ULL, 
            0x429E8C4EA80656E2ULL, 0x9E0A16E1BADC6B38ULL, 0xDC5F41D95E03FA92ULL, 0x46552F6A143E9BE7ULL, 
            0x7A6FB7F5E55316CDULL, 0xCBF92361D67156E3ULL, 0x6D630C16C3D4E11CULL, 0x66448B71D03513C2ULL, 
            0x3BDAD85F836CF74CULL, 0x20356D4B730128A2ULL, 0x71B1F200278AA0D2ULL, 0xA7F618E9D4E8BA8BULL, 
            0x301702BCEB0ED830ULL, 0xD33E4B8B39C6AA54ULL, 0xB26298A54307D05FULL, 0xF6543AF2BB80C623ULL, 
            0x2E9C2929A4E5EF11ULL, 0xF9C3D1B7894B20C8ULL, 0xB0AC4CB59A2F1618ULL, 0x5F7FFA3FA2F7BFE8ULL
        },
        {
            0xEC26626056E67EADULL, 0x2B0B086D10C81CBCULL, 0x8D0D5332391B3114ULL, 0xEF1FA404F906C733ULL, 
            0xC5C393D23A2DB96DULL, 0x3E9C348676EBB5B8ULL, 0x51F9788794051B86ULL, 0xC5FA57817482723DULL, 
            0xF4AD9DE6ED597858ULL, 0xC266482AE5B38C99ULL, 0x1DD72A1A63AA7A29ULL, 0x0560D656D2B23614ULL, 
            0x5FBD90D2A339C6A9ULL, 0x22BCDD401C59B173ULL, 0x8D250E2D643B57AEULL, 0xD49D9BD0C6D55C62ULL, 
            0xD0BD7D65B675E4D6ULL, 0xBC41999D2B79BD17ULL, 0xABFE090BF3E2F997ULL, 0x945309606720D100ULL, 
            0x7AE264141563A4B0ULL, 0x1FD3A4BD8BD93EE0ULL, 0xE21EABD4DDCEB81AULL, 0x4516C807854038ADULL, 
            0xC944DC4CE44CB73BULL, 0xA7BBE3A7B6BB1B55ULL, 0x673D58FF462B90BBULL, 0x94712472597CF91DULL, 
            0x3812E7144194D88AULL, 0xB70FBE665D22FFD2ULL, 0x634518CE3D0EBCB7ULL, 0x1C2A3C07FCB0DC10ULL
        },
        {
            0x93436F70A5456CCEULL, 0x7FC4638D4F0FECD6ULL, 0x2458D27F89F094EFULL, 0xAEFCFBA735C07005ULL, 
            0x5C98A2F6D3EA6C6AULL, 0xD1BC7CE00F04EC67ULL, 0x2497BAA646021DA0ULL, 0x828E51074F7F3D8CULL, 
            0xD233F0825F7D1186ULL, 0x6FD16A3AFCDEDEB6ULL, 0x00095E244E3F2D35ULL, 0xCA57BC2DBD8DAF06ULL, 
            0x19566DBC3D8A8020ULL, 0xE697B80E65CFD176ULL, 0x146415E84B9AC1B4ULL, 0xFF21A78307C795C4ULL, 
            0x665DAE0B2AAAFF30ULL, 0x3A932BDB5B3F9EBFULL, 0xFD90FA204EA66AB7ULL, 0x6FE8B98226B0CF4BULL, 
            0xEC88EAE259E69703ULL, 0x983ED5A20599ABABULL, 0x1FEF7F9E071CCC6FULL, 0x9E694C6D5D9DC42CULL, 
            0xA4BC42ABD224BC63ULL, 0xEB2E57F00E8EA7E4ULL, 0xECF539357C73870EULL, 0x73C6F8F9C8E448ECULL, 
            0x896AF9180869A0C9ULL, 0x7B54AEA66AE6CCBAULL, 0xD93A4F48609F3413ULL, 0x1401F66991BA5F37ULL
        },
        {
            0x5D4FF3BC22EA14E2ULL, 0xA1773F526030A15EULL, 0x952260094C276551ULL, 0xA839A3B26C71E9EAULL, 
            0xC52461BB6CB526FEULL, 0x7B79B06EC63172B4ULL, 0xF44A101A8F1E9FECULL, 0x5DC722C3CC0C881CULL, 
            0xE760E0F6E44F09F0ULL, 0xD51D1AD4D7C42042ULL, 0x0C2F8F9E66019433ULL, 0x9C31D8ED7BC8A344ULL, 
            0xE1CCFF3F5E3B57C8ULL, 0x4A87C65E76EA84F1ULL, 0x4D8B4CC6E04C94ECULL, 0x204083F150D7906AULL, 
            0x6892A03A713CEF93ULL, 0x1DFECCE9D6763CD2ULL, 0xF323F48C49BB441DULL, 0xC031A2B8BDA7E8DAULL, 
            0x0D0AFB2E3B42B9C5ULL, 0x479F131AC3B432C1ULL, 0x879496C1AD34BE86ULL, 0x662F8CCC2E774AC8ULL, 
            0xBA72CD38E5C2675AULL, 0xE7A342E5ED3FBA04ULL, 0xAF8CB7391615BFF3ULL, 0xF2DE4D3AFCE7C93DULL, 
            0x3ADFCB42F2D116EDULL, 0x643188C6805561EBULL, 0x98C9712D6FD0A7BFULL, 0x6490C005736E5F41ULL
        },
        {
            0x945249143939B5FDULL, 0x9AAE72E62A7AF658ULL, 0xBED6C3A50E2B4076ULL, 0x8D4E4327EC27D2BEULL, 
            0x04616C6EDBCB9292ULL, 0x2083168CD14F3162ULL, 0x67DE979B4A402C15ULL, 0x35C111A6577074BEULL, 
            0xBBE70E6BA0569B50ULL, 0x4874B13238DFAF48ULL, 0x902A1BB591376E4FULL, 0x16550F413103A4C6ULL, 
            0xB09B3CD7EB5735B1ULL, 0x5D61A6D6FED7C6F0ULL, 0xD84F0DBE3B502D1EULL, 0xCA4887EBD20D4EB3ULL, 
            0xBBE2E76845A69992ULL, 0x87AC10316AC22A8EULL, 0xE48A4F0C53F6660DULL, 0x610834BEE868B119ULL, 
            0xAEA5DDD9E7D0ED6CULL, 0xBBF7ACE76FDD903CULL, 0x2334F88614CCD624ULL, 0xDE8D9A71F1BD21BFULL, 
            0xED4CB53FCA4F5156ULL, 0x71B8F9821C48AECBULL, 0xBDCA0F5A6B6EB632ULL, 0xD0C93B88C1A9809CULL, 
            0xC508BE91A8312233ULL, 0xD3803B960C75722CULL, 0x977744E73273EE66ULL, 0x0C8BDA06E722F81CULL
        },
        {
            0x01A3A74677701B3BULL, 0x83BFCBC4EDA7A0A7ULL, 0x51522D0B368A7C81ULL, 0x0D17D0D1F32CB70DULL, 
            0x0AC15BA58D2F2B6DULL, 0xB7C3D2C885EDCDC1ULL, 0xA2E5F58028887DFEULL, 0x6EE26DA13A0013A1ULL, 
            0xFEDC92D47F8CEDF7ULL, 0xC997EF46127A045FULL, 0x029C0EF695765A11ULL, 0xEBB70CB72A0A6FB0ULL, 
            0x892B27E60B5FE780ULL, 0x3320C979C62EA952ULL, 0xDEBBA29668731F5AULL, 0xE19F39C7D2F0BCD0ULL, 
            0x2287FDF3F9A0DCC7ULL, 0xF3466D6978751269ULL, 0xCAFD48A792D35430ULL, 0xDDDD5589227F683BULL, 
            0xD70DE7DB077F6754ULL, 0xF26CACE92C1CE87DULL, 0xC931537F64D7CA3CULL, 0x821892B803334A95ULL, 
            0xDC23B171C418E876ULL, 0x2A39AFE666E40A66ULL, 0x1081C994A1CE39D2ULL, 0x07E3A869C3CF9767ULL, 
            0xF47A15A216F4E75FULL, 0xA77A28CAE7EE458CULL, 0x4C862F98D4EE63B3ULL, 0x6B0932453454CC76ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseFConstants = {
    0xD36A10BB87629B30ULL,
    0x6305224AE6719DD1ULL,
    0x1735625D019C5BCEULL,
    0xD36A10BB87629B30ULL,
    0x6305224AE6719DD1ULL,
    0x1735625D019C5BCEULL,
    0x7A7543644ADEC732ULL,
    0x89FAB9B8201A0D9AULL,
    0x07,
    0x97,
    0x86,
    0xF1,
    0x67,
    0x9C,
    0x6F,
    0xF4
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseGSalts = {
    {
        {
            0x20D063054067D835ULL, 0x015142A48E848552ULL, 0xEA1669B5E4244748ULL, 0x8C5064A582302DA7ULL, 
            0x1D0C5A7326D15432ULL, 0xD8C1E7272B219B96ULL, 0xDA202B9B0779A893ULL, 0x0DE21FC81BF7EC35ULL, 
            0x173907F09DFF1D28ULL, 0x5BA37D4A032E24C9ULL, 0x45FA85181F171783ULL, 0x902AC401303349D2ULL, 
            0xFCEF65C8C1154B17ULL, 0x0D8A2BCD30A3F484ULL, 0xB13985E88C0DD6FCULL, 0x0530705A64A01BD8ULL, 
            0xEA7B402F0385B4BBULL, 0x33C254504FD131E3ULL, 0x202047B45764178CULL, 0xCBDFC57152568703ULL, 
            0xCAFD085EDD767DA1ULL, 0x05CC62A89306B439ULL, 0x7A477EC703B360C9ULL, 0xD151FBDAAA4322F8ULL, 
            0x9D5939D0D185316BULL, 0x7A3EDE8A3FA77593ULL, 0x172B716A6E87B46BULL, 0xAB07EB75A5DCDB51ULL, 
            0xD2721A209611381FULL, 0x0BA50C59886DFC83ULL, 0x1B9FE1D8A7A47EC6ULL, 0xAE89F4231703E54DULL
        },
        {
            0x1DEAEE34E99346FDULL, 0x17A32712E1C95B21ULL, 0xA7FA2D9340DE89E0ULL, 0xA7ECE5C489301E81ULL, 
            0x90779622E904860DULL, 0x88BB113A523EF825ULL, 0x1701C33F4316F30CULL, 0xE7E5F9788FC4EA85ULL, 
            0x9CA209CDBF038700ULL, 0x45A4A2C811AC4AEBULL, 0x420C2BF8380EB4D7ULL, 0x7EED81952486B1D6ULL, 
            0x2F099364E2B29336ULL, 0xBC96F51CE1000182ULL, 0x94B5392EAFF35CFFULL, 0xE70B61817FAF4771ULL, 
            0x91DFE32BF0BFA0D4ULL, 0x44B484F17E45DBECULL, 0xA20068A10F4C60DCULL, 0x0E3F892AE486449FULL, 
            0x66E4654CEF6B8E15ULL, 0xD646CEAC388756ABULL, 0xA4D43C11D4F82304ULL, 0xE8FB27627C80A143ULL, 
            0xE3F63FEB15E0284CULL, 0x33A4D9A8203B12ECULL, 0xECE4A9E365CA48FBULL, 0x6E062B30A7FF0FC8ULL, 
            0x43A93D3786DC83D0ULL, 0xBD5F2E17FD509605ULL, 0xBE604244BDBBD9C9ULL, 0x3C537A04DF1D24A7ULL
        },
        {
            0x43DA4277F58A0E72ULL, 0x5C0C7A9BD250D503ULL, 0x40889BC6537C22D9ULL, 0x14710F81A09B9374ULL, 
            0xF6A5512CCB7C8CCFULL, 0xAC72CECF7A2712CCULL, 0x8CF31EA5104B911EULL, 0x1F9C1A6C6BC1567FULL, 
            0x99205E363DD43435ULL, 0x86F00F5BBD22D1B6ULL, 0xC346D73AA9988167ULL, 0x399AA2305A7A2DB7ULL, 
            0x7A82F50EA97CBFB0ULL, 0x1A8116EEB1F7AA7BULL, 0xC7876780EE415BA4ULL, 0x6D9EBEC7672A75BAULL, 
            0xEFDE0AC3AD1DBDEFULL, 0x43C14A9C08D093C3ULL, 0xB40628A6A61577F8ULL, 0xF7AC858D82317FCAULL, 
            0xDFB3F0FC766818CBULL, 0xC649DCBB1EF87A7CULL, 0xD77FEE308EDAC8F4ULL, 0xAC955BBA0024622FULL, 
            0xB751C88354C28D45ULL, 0xE41795B435C9398BULL, 0x6C8286B201AE78CFULL, 0x272391E03E53250DULL, 
            0x971D079BF2A3EFE1ULL, 0x4AE917BB85F80018ULL, 0x70D75EC7CACCA0A7ULL, 0x98EB9D646CCB3563ULL
        },
        {
            0x1E88299531E27DFDULL, 0x504EDEDF624897E2ULL, 0xFA8DF59E80717485ULL, 0x3D99F118F80FA7B0ULL, 
            0x54AFB9FB0E82A13FULL, 0x0C82E3503BF0A421ULL, 0x0276084AC56631CCULL, 0xCC8FE6B34B329059ULL, 
            0xDB43C12FC11D2012ULL, 0xC2B78516535A8EEFULL, 0x4A57BC41E533BB73ULL, 0x13E8335A6436DA28ULL, 
            0xE23875AB1D13CE66ULL, 0x567BB25CDBB1C3B1ULL, 0x1146D85554E76F03ULL, 0xDEABDE4C900DB6C0ULL, 
            0xBE1AFAB1C8C37AE3ULL, 0xE00A231F012B0171ULL, 0xB0AAC86117A17E94ULL, 0x09A88BF787AB77B4ULL, 
            0x842A1786EEDFC3D6ULL, 0x5D5A6DD3C9E9B08EULL, 0x98FBA07E2B946C40ULL, 0x06DEA2AAB02A8B16ULL, 
            0x965611EDD213B101ULL, 0x9ABCFEED081A48B9ULL, 0x685E8753B9850CFCULL, 0x1B13E17A608B644CULL, 
            0xB17916F7BE41A210ULL, 0x9D73643BEE9293A4ULL, 0xF87250EB4B9B14BBULL, 0x078942616E5D40E1ULL
        },
        {
            0xC80546CB6A12D66BULL, 0x56933DC04D673D42ULL, 0xF26C6C8D8AEC792FULL, 0x9F657505932F35C9ULL, 
            0xB62E8FBF202073A2ULL, 0xA5B88115399929BFULL, 0xC7190AC591424ECAULL, 0xC22BDDAF7FD49CE0ULL, 
            0xC9527C6F53AF61BCULL, 0xCDF049F7716E838BULL, 0x1FD1B3BD9F5D57C2ULL, 0x467628E6411E72DAULL, 
            0x85DB79D3FDEF2422ULL, 0xDF774DBA9EBEF90CULL, 0x82E9C3BEAA1F0520ULL, 0x4411100DFEA9DE56ULL, 
            0x0F9F468B1C94849DULL, 0x32328F20621FDB30ULL, 0x5C31E3670D33FD1FULL, 0x26B52E59A056587EULL, 
            0x08C318029CC59A75ULL, 0xB24E878288AAA877ULL, 0x94112A704A98D24CULL, 0xA41CCB74B64C33BFULL, 
            0x3851310F78A79F26ULL, 0x94E899FFB7B691D3ULL, 0x2886B50060CAA6DFULL, 0xE628FF1C25920291ULL, 
            0x630D54DC4B4ED5B7ULL, 0xB3198D370261BD30ULL, 0xB4734CFEC9E7126BULL, 0xB511A40102CF9D21ULL
        },
        {
            0xCC7688238D02C6E0ULL, 0x4F0482C2209C01D9ULL, 0xAA5ABC55759FA5C0ULL, 0xDF6439D1B3F480F6ULL, 
            0x8D0FE61DABF78691ULL, 0x73F18087C084B23BULL, 0x4DA297550566601CULL, 0x569E04EA9B0062F3ULL, 
            0x2A42563B2CBC7D78ULL, 0xBA082A2416AB7441ULL, 0x159D879087E4360BULL, 0x150E34C198AB4276ULL, 
            0x580987831511C5E1ULL, 0xF3233FAED3F028A7ULL, 0x9BE3CD852A5E7AD2ULL, 0xC20561B547F9A0DCULL, 
            0xA5783C97547F880FULL, 0x0F5D28D8D9BF1AD6ULL, 0xE44B184CD0E96874ULL, 0x66DED6348CF46CAEULL, 
            0xDDDA513E78EE5518ULL, 0x6E3F3DE805565E76ULL, 0x2B6B8705C8F2459DULL, 0x054273610DDD7048ULL, 
            0x8B04449C0928EB03ULL, 0x6DE34EA61B3D4CF4ULL, 0x3E303373A4CF409BULL, 0x3C2858C0F06EBCECULL, 
            0x881F96DC60B3A236ULL, 0xA5C6B892FA9ADD67ULL, 0x933273B5A269EF19ULL, 0x20437B3E5BD354A0ULL
        }
    },
    {
        {
            0x7F954EBF27A2B279ULL, 0x48358D4AD87A8668ULL, 0x6D9358396269DC46ULL, 0xF0A6FAF1954A48AAULL, 
            0x3A5EAF5823645451ULL, 0xE14F6DAFC6848868ULL, 0x5F64DEAC6DC68936ULL, 0xC5F9D239FD5960A1ULL, 
            0x87B78DF3CCFD7E5DULL, 0xC83F898F9282C588ULL, 0x1E2A724B409DB7FFULL, 0x5D38B1AD2EEC5EEFULL, 
            0xAD6A7EFD0281D857ULL, 0x9795696A60534850ULL, 0x4B7E8F78AAA4C4F3ULL, 0x48EF234882643516ULL, 
            0x3A26312CDDA0EE4EULL, 0x602BF4BF4855C057ULL, 0x6106BA6B62BF60C8ULL, 0x219BC9C5AFED8B05ULL, 
            0x044927C90BF4FB8AULL, 0xD6C6259C9739D4E9ULL, 0x5F3124BBCFF39C8DULL, 0xDDA8D22292280768ULL, 
            0xEEB4ABDD13DD9D87ULL, 0x17621F01F89672A0ULL, 0xA8C7AEFF7CC843F7ULL, 0x380D0D78ADD97B06ULL, 
            0x907E00000A95BAFCULL, 0xA7C6E7352CAEBBD4ULL, 0x8BF615E3B6107B18ULL, 0x7A18F8D260F63A46ULL
        },
        {
            0x1C47D08588D2A9E6ULL, 0xD987423DE4704344ULL, 0x5CC0EFDEDD5BF1C1ULL, 0x1828FF06E58B4126ULL, 
            0xAFF0E9319507E6ADULL, 0x99DE38A67FC654D6ULL, 0xB4EAC3D10E2768D8ULL, 0x74385BE90D44B270ULL, 
            0x0E8A7B707237A8DBULL, 0xCF541F41C712138DULL, 0x266862CDA12E5E50ULL, 0x98F45FABBDF23F02ULL, 
            0xCC2E3956A3F5A34FULL, 0xD59421F042EEC2E0ULL, 0xDA0086745FDA3933ULL, 0x6F57C7454F752E8CULL, 
            0x87483FA0C05CAE6BULL, 0xA7A7EDD2A22248B2ULL, 0x0DE8261D8349A86EULL, 0x75A857E6D86C032CULL, 
            0x273B9D6F0DF94120ULL, 0x72B627C9663F17F7ULL, 0x1532A026FE4F1FF2ULL, 0x9ABA3D83E4E6A24EULL, 
            0x50C3AFA913BCC111ULL, 0x66C507F501E440F8ULL, 0x3458A47F499FE42BULL, 0xD7A0FD5E93088858ULL, 
            0x8793D4902D887044ULL, 0xFE41DB3B5809AE31ULL, 0x6AA54C3F2E6D6E7CULL, 0xC94A92EB7CE75321ULL
        },
        {
            0x61C9338FB6EC4AB0ULL, 0x61F133442E759913ULL, 0xD707F97A80821689ULL, 0xFE9BB83D068C42CBULL, 
            0xE5AA7E07871AC02BULL, 0x2C74BC58D7F68836ULL, 0x1453A819CEC2B8DEULL, 0xD4E947055BF8EC31ULL, 
            0xA8404C50B1888179ULL, 0x616D754AAA2D5C6DULL, 0x2EADA60F802B1129ULL, 0xCA62DE960D6A03DEULL, 
            0xDE60C04C07AD6AABULL, 0x2803BC0B3568F7B4ULL, 0x0F0D94988D7EC810ULL, 0xD0D9499EF5DFABF0ULL, 
            0x5BD5FD6E0CD672A5ULL, 0xC4794EE45B1B3C0CULL, 0xEA0740F53F5DB2AAULL, 0x0A2587D3ED197849ULL, 
            0xA3C1AE9FF649DB38ULL, 0x9A9F2C308AF069B3ULL, 0x9F0B8B553FD7189EULL, 0xFEC4F1B89A89A297ULL, 
            0x2E9AEB466DF25888ULL, 0xE5CF47AF269DF3C2ULL, 0x959EE89AE086B5F9ULL, 0xC37E5363B58801F8ULL, 
            0x89A41AA0A37F46ADULL, 0xC3BB990835CB45AFULL, 0xE2F012862FCB8562ULL, 0xFAA6BD3F9FE23B70ULL
        },
        {
            0x3D9A443C17A840B6ULL, 0x5F7068384C33CB8DULL, 0x31D8AB8ACE816FCBULL, 0x9839AC4680166639ULL, 
            0x2DEE01EC3E0DC4F5ULL, 0xFC5308AE900D0A81ULL, 0x82D6495C027B18FCULL, 0x2522FC9B8232CB4FULL, 
            0x06260A45428CECC8ULL, 0x5EC9673D8F839B81ULL, 0x6A7A2856690441F4ULL, 0x680CA116E4D31FDDULL, 
            0x4B7A54FFB9CC1930ULL, 0x6230C21C678B37F8ULL, 0x8FE7DCBDC9386673ULL, 0x6A14F154D32F6A48ULL, 
            0x4FE4C2401CB81080ULL, 0xCC7025F5F25208EDULL, 0x1E6C5F9411475ED9ULL, 0x8199F202BF51C976ULL, 
            0x1D72A32B33B243BAULL, 0x9D6388CAF335E532ULL, 0xA86F1A1B0BEDD0D0ULL, 0xA6AEDF3275D75227ULL, 
            0x38E7D65E1C214B05ULL, 0x5265E89EB24A142FULL, 0xB5BDE2B511921DF1ULL, 0x53632D87FBEB1684ULL, 
            0x7EBEF05A3306F583ULL, 0xFA9C9F51EA46E727ULL, 0x14CD15D733F68C42ULL, 0x9C72326515F1611DULL
        },
        {
            0x5F53BD9E7EE145CAULL, 0xB1D95F643C301D27ULL, 0x987BA280482271BAULL, 0xE32A029E0732E221ULL, 
            0xF3EBEB3E566B075BULL, 0x7B44CC7EB2BF4F66ULL, 0x083F1C41A83D17FAULL, 0xCB36BB649096381FULL, 
            0x61F303F64A784770ULL, 0xF9B2F77136D54CCEULL, 0xE1E7444C17CAB127ULL, 0xE74D4EF9963B5A34ULL, 
            0x736945313E56134AULL, 0xB6142202DA616C8EULL, 0xD329B1A019CC6D3BULL, 0xF5D13E86FCCA6B90ULL, 
            0x7B4258848E8471DFULL, 0x5A1AA506428B5508ULL, 0x5D8C2F9A8BBB05D9ULL, 0xC10FFC61FAEAB02AULL, 
            0xADF22B22B62D85EFULL, 0x58B8BBEE8FE57546ULL, 0x555770FB5B5F6420ULL, 0xDCB011227C70F642ULL, 
            0xE6B3C6603BCA772EULL, 0x909FDC498F720F5AULL, 0x8E1DB9C4475FCCCEULL, 0xE98D0C5193B0E964ULL, 
            0x3675560968D89F55ULL, 0x964DF0E3BC8CC052ULL, 0x080A7DBB91DAADE0ULL, 0x933F095DDEE5EB4DULL
        },
        {
            0xAEC066363333B318ULL, 0xDB5F686DD22723CEULL, 0x237E704F5255795AULL, 0x6CE6C9B7C6B5CB56ULL, 
            0x48895FDA15518652ULL, 0x3486F71EBB2CC280ULL, 0x737034A5886E31DCULL, 0x9C30E4A9D0970162ULL, 
            0x4EC21548CA0F7124ULL, 0x523BDDB73256A638ULL, 0xD7FA18CDFF2AAB4EULL, 0x537DA25192CD82FCULL, 
            0xE13BCE13A5FE9592ULL, 0x319E1A1995DA66BBULL, 0x6D328A2314457742ULL, 0xE30A1A8756B4868FULL, 
            0x5482E0F6677965ECULL, 0x6081E2CB9C5BF5BAULL, 0x01D71AFD8B68A9FFULL, 0x88FBCBF7C8AE6BC9ULL, 
            0x0A193081EF246F99ULL, 0xC1CA08FB265900A9ULL, 0xAAA97B7678927B7FULL, 0xD29D75D764C6D24AULL, 
            0xE0EDE3E895D82D51ULL, 0x571B8D9421B9FB28ULL, 0x9E7EA4A87BFF7D91ULL, 0xBE507A96CF4FA7A6ULL, 
            0x52E57B1524B6F804ULL, 0x132B7615F379386CULL, 0x74545E44C3977C8FULL, 0x251AF57F5FC7336EULL
        }
    },
    {
        {
            0x56CE8A546171B18BULL, 0x70059C0FD70794FDULL, 0x4CBE5167A9417582ULL, 0xB1DBDCFD582BA0CCULL, 
            0xCF662FEADE4FA8CFULL, 0x019DF8D21E433B50ULL, 0x0792EC1D50730B33ULL, 0x4CDF8DE9E299368CULL, 
            0xADDFE478636184AEULL, 0x6C87936B65E9A2F0ULL, 0xD2CEFBB672CE02F6ULL, 0x859B5642FACCD72CULL, 
            0x76EC001A6A770BFCULL, 0xE6BDC129ADC46155ULL, 0x318752E4445F9731ULL, 0xFD1F5D6C2C4291A7ULL, 
            0xD4EA9D7D811611BEULL, 0x7FEC2A09B3CCC0B7ULL, 0xC40E5B02FDDCF92AULL, 0x62335B0941C7866BULL, 
            0x4231401E1ED9DC91ULL, 0xE7C3675BE9BB9941ULL, 0xEEA6C857EFBE65F8ULL, 0xA3B66CB10F483F53ULL, 
            0x4EB5090F45D7B5FCULL, 0x4F1AE005B0014654ULL, 0x1983BC3C2163AE7BULL, 0x610FDCDEFC9779F3ULL, 
            0xCCB8EE5ABA9B2809ULL, 0x5799299282492371ULL, 0x9EB271D6052CBD5EULL, 0xB76674BC267D3C6DULL
        },
        {
            0x2B40CB5C812EB8CFULL, 0x8C8B68E91B7850DDULL, 0x3FC0FE1A3F8532AEULL, 0x1777F56D3447ABAAULL, 
            0xEC8036CCDEF2D8C4ULL, 0xD42A9147D6ED134FULL, 0xCD2513011894E1B9ULL, 0xF1AD3381275EC6B1ULL, 
            0xA332335FA483A745ULL, 0x0FE54009B797C724ULL, 0x85258419C08784BDULL, 0x42E470EE892E7383ULL, 
            0x2B5F7CBB330FE908ULL, 0x53D4123E5DF6DC52ULL, 0xAB0EB868C20548C1ULL, 0xA244B92D6E8CF348ULL, 
            0x97FBDD104A8020C6ULL, 0x914D19BB0EAA23E0ULL, 0x5F80F6419E9AF2EDULL, 0x8FEB7D722964222BULL, 
            0x5C7FA3FD4A0A8D93ULL, 0xB328359975D85B4FULL, 0xC377AC098813A477ULL, 0x1B254EE5D87DA8AEULL, 
            0xD812C98A78BB3D42ULL, 0x882E5B66A9D3DAA1ULL, 0x2C2166A775B66063ULL, 0x7D295829ACE5354FULL, 
            0x5DE5913C3184FABBULL, 0xE7070900DB968753ULL, 0xAC5EC2F406DDFB39ULL, 0x191BF4BE5B628E02ULL
        },
        {
            0xEDBD1E975D568E3CULL, 0xEFC5B4AF6218D35CULL, 0xA68B6B9E6A721DC0ULL, 0x4CBF2F4132DC4CA8ULL, 
            0x57822D2B96EADFEBULL, 0xE40F7FD12DBE6961ULL, 0x7B1B92CD426A0AB9ULL, 0xA9C96B368956EA01ULL, 
            0x037143308B9B2F1EULL, 0x406B872C79843919ULL, 0x44B917FE1D97E683ULL, 0xF3379937C50089F8ULL, 
            0x201936F7CDB86017ULL, 0x1AABFCB80E0ECBE2ULL, 0xC3D737FA495F49D5ULL, 0xEBD209739E50BE18ULL, 
            0xAEB0D0C48D3ED6F5ULL, 0xCCD8E4D29DCCB104ULL, 0xFEF57EE8FE70A742ULL, 0x977B4603A0C2401DULL, 
            0x2F639B3C009A9265ULL, 0x5E72EF6D210756F5ULL, 0xAEFFDBA840A0057CULL, 0xB7E9E93AAEBC3B07ULL, 
            0x0D408A37BD685A1FULL, 0x3783FB0405889746ULL, 0xD94EEB2A73D2C443ULL, 0x40A26B178FEA02E0ULL, 
            0x49C4C8CCCFF684E7ULL, 0x6C27101CA5192803ULL, 0xC6AD80E16DBFD205ULL, 0xC0888740A0C3D84EULL
        },
        {
            0xC87B99ABE74A7952ULL, 0x1693C2127D1B198AULL, 0x79EEE47F9D79EE22ULL, 0xCF86847AA42F98F9ULL, 
            0x8078AF23C3269DB2ULL, 0x5C07BDAA8BB73C60ULL, 0xF67F2E0D8A611DF4ULL, 0x7976723C1FD81B9AULL, 
            0xB5CDE7277653CE92ULL, 0x05FF90C9A423D69EULL, 0xE57A216D7D47D565ULL, 0x26F5BC91B5D4552AULL, 
            0x730C70EC60AEC491ULL, 0x4526F9882B89B4B9ULL, 0x57D238AAB9A0B353ULL, 0xE91D5136DF4DC223ULL, 
            0x4C860C3EE9C0E237ULL, 0xD558C7A26722C34CULL, 0xE3D32B624227AA61ULL, 0xBDFB3C8D7E4C8ACAULL, 
            0x635654FDA8038E0AULL, 0xD56E70EADF27ECD8ULL, 0x023AF2E1EC565B79ULL, 0x6069A9992E75CBA5ULL, 
            0xCD4BFE1B3E66A8DCULL, 0xA377A990393A632BULL, 0x548EE6E8F7D79A70ULL, 0x231B0EE8854D935FULL, 
            0xD70B91331A793FCEULL, 0x96F930654EC87FCEULL, 0x273BDD4ED51F8221ULL, 0xC9B88EFCE533C5F0ULL
        },
        {
            0x3F3F93ECA7624B51ULL, 0xA2D0DDEEEDFBA8BAULL, 0x90D482D0C531BB5EULL, 0x09E0024AB676B8ACULL, 
            0xC1075F46E9975097ULL, 0xC0CDF52379978398ULL, 0x0563FC2196C87FCBULL, 0xCDF539ACA6B3FF19ULL, 
            0xE193871E67BEB448ULL, 0xD626149E49715A16ULL, 0xC64CBA64971A21EDULL, 0x6984A40535E92F96ULL, 
            0xD444ABACA432FDC0ULL, 0x430D7E94189130D7ULL, 0x2A93C2C1B258C7AAULL, 0x147F4BD43D12EBC6ULL, 
            0x58407302C67D30E8ULL, 0x30672B117B410AD2ULL, 0x74990707E096A146ULL, 0x5BABA72249487D80ULL, 
            0x43E3F63EE3755011ULL, 0xB390A9CD56295212ULL, 0xE03C0343A6E1C43FULL, 0xA6D2AD5D1A4A552CULL, 
            0x793B319D03C0E1DCULL, 0x2D936885C4F415AFULL, 0x830E7E8FC8F1D320ULL, 0xBD13444EFE01444BULL, 
            0x632D810315129AB9ULL, 0xEFD3E1BF9D9E998FULL, 0xD2A455F7613C9859ULL, 0xB4CD19FDB5F855F5ULL
        },
        {
            0xA102FB02A2D6E2ACULL, 0x60644B00EEF200D8ULL, 0xA9A09630EBDD9426ULL, 0x50AFEA983FDC5EE0ULL, 
            0x083C881B146D1C2CULL, 0xB4D9280813DD2EC1ULL, 0xA2201DA15FF48166ULL, 0xFDB9E532361C0A0FULL, 
            0x0C9F76B606F29A9DULL, 0xA7E60A8E37ABCD28ULL, 0x5F3F28C088A0763FULL, 0xD405D84C2A45B37FULL, 
            0xC4C27AA96E7DB6AAULL, 0x5EF0B7BEDDABE63BULL, 0x333B8CB847B81719ULL, 0xF6309E7F16FD3063ULL, 
            0x94BD4415B0A35704ULL, 0x46BD696C53AE4A7BULL, 0x283D4951B65A7E78ULL, 0x6C12207FAF666323ULL, 
            0x5E0EC6A9384733A3ULL, 0xD9311C5B3C16DB16ULL, 0x80CB06EBE5CB5232ULL, 0x98ED30084738F3A5ULL, 
            0xD8E947D787FE875CULL, 0x0E0DCB66A1B95AEDULL, 0x6819F9591AB51DD7ULL, 0x0F6AC469B58B8363ULL, 
            0x6F0F29FF867AD2EFULL, 0x8619FCF9C63742A8ULL, 0x2FFF29DC271B0357ULL, 0xB6951BDF411DDCCDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseGConstants = {
    0xF43C7F3528AD705FULL,
    0xA164C9866A395769ULL,
    0xD92E300B93A038C3ULL,
    0xF43C7F3528AD705FULL,
    0xA164C9866A395769ULL,
    0xD92E300B93A038C3ULL,
    0x51B56DC734C29E59ULL,
    0x596AD845EA1D2D27ULL,
    0xAD,
    0x0E,
    0x84,
    0xCE,
    0x1C,
    0x91,
    0x58,
    0x5E
};

const TwistDomainSaltSet TwistExpander_Sirius::kPhaseHSalts = {
    {
        {
            0xF04A7BDF459626F4ULL, 0x246DEC6B2C6A1CECULL, 0xDFF6DEDAC0EEF03CULL, 0xC42A248C927CC554ULL, 
            0x2B400B013F85D6D2ULL, 0x7A1DB0C810EFFE73ULL, 0xF31F5AE701B265BBULL, 0xB6E79119C210BD55ULL, 
            0xF45532BFC72BCB81ULL, 0x121593895AA79BC3ULL, 0x9D9F3C1578F3AF8AULL, 0x71B228BF39BC2643ULL, 
            0x8A88A0DD05B8D289ULL, 0xEA102297137552D3ULL, 0x43A32FB77627E482ULL, 0x2A4C8E3F0A7C1CBBULL, 
            0x4F9662104FC0F353ULL, 0x4E03DDCF8B239451ULL, 0xFBC4388019774EB3ULL, 0x3F801ACE15E3A2B4ULL, 
            0x0EBC5EF704423E00ULL, 0xD9C072B7FF72CEB6ULL, 0x06A84D8BB660C646ULL, 0xA557748106E3E3E1ULL, 
            0xE7AA3732C96A0BEFULL, 0xFA0D982844BF2381ULL, 0x107315705C354EC9ULL, 0xC7A66204657A2740ULL, 
            0x649168DEA3E9A036ULL, 0x52E634CDF5D08170ULL, 0xDA08FE7E51DF4EDFULL, 0x596AF241EEBE6DEDULL
        },
        {
            0xF271853BADAD8F72ULL, 0x44F8468B089FF6A8ULL, 0x8D706EB2B0E2F8C3ULL, 0x556FE8971808D3C0ULL, 
            0xBEBABF1B1B3C4F11ULL, 0xB258214E35F89221ULL, 0x347E16790A5ABDA9ULL, 0x9A38A95750584F33ULL, 
            0x7340B14A0D0BD3DEULL, 0x31E5EDE51485826CULL, 0xD39AE605ABEC38F2ULL, 0x40C0C2A9943ECBC1ULL, 
            0xF2C227941422D458ULL, 0xC11B4F193FCCF1C7ULL, 0x95186412113D3FA2ULL, 0x99930B0BC000A9C3ULL, 
            0x3B3EBA5925B05B5BULL, 0x433360CA988EA643ULL, 0xBEA31591AE3FBED4ULL, 0x346E7F5DC6BD5061ULL, 
            0x83505907B092943AULL, 0x261AAD18EE6EB39DULL, 0x9545679465D9D42DULL, 0xD76775FCC5335EB3ULL, 
            0xECB183E4AC665AC6ULL, 0x7E1FC5A3A166A3C4ULL, 0x671566E577F687F4ULL, 0x60F6AE83BADACA64ULL, 
            0x84EE0C6B7E755915ULL, 0x250651DB394B69A2ULL, 0xE17799618A485339ULL, 0xD2B9326E2CF259AEULL
        },
        {
            0xA3E61ECB15C4C582ULL, 0x31A323CEDBE0C797ULL, 0xDF60F9A281B0DC8AULL, 0xD8E449187C11702AULL, 
            0x13CF669CA041285FULL, 0x61B8ABCD35CF3D55ULL, 0x3E1589729A548921ULL, 0x99327601D5C8C48DULL, 
            0xB5743519C09055AEULL, 0x1545C97495E28981ULL, 0x900B289F532F33A7ULL, 0x6556280CF6CEFA7EULL, 
            0xEFF56538928F1C7DULL, 0xA83CFED7CF7C257FULL, 0xB20702BBC9CDAFAEULL, 0x4E26CD4C938D35CEULL, 
            0x99F896FCC97D993CULL, 0x343244E192AC5B1EULL, 0x6F9ECD044CEC4CDBULL, 0xD659E44587C7ACC9ULL, 
            0xCE1D12538E3A5C8FULL, 0x5554574D0F3B2FF7ULL, 0xCC2E02A9B186F63AULL, 0x1953FE89759328D1ULL, 
            0x9DBA7D579441F1DFULL, 0x8CB304B8FBFB5E92ULL, 0x8C37F26B206568EBULL, 0x1AE3580569EA8854ULL, 
            0xA31A7A944EA8195AULL, 0x8271222CC216B517ULL, 0x83FB2217EBB36E0AULL, 0x9556D5C04F40CFA6ULL
        },
        {
            0xF758322621D15B75ULL, 0x1061D620834AC7F5ULL, 0x4898887B7213B743ULL, 0x20968C131D9B0F72ULL, 
            0x07344D07BFC33D72ULL, 0x373BC2E2E543BBC7ULL, 0x00B0260011AF75B6ULL, 0x4E7B94F13EFBF701ULL, 
            0x5BA648F30402534CULL, 0x3C836BEA97539CD2ULL, 0xCE417D721D175985ULL, 0xC34F0766775FAD26ULL, 
            0x19E5284373641647ULL, 0xA1C2DFC83BA0AFDDULL, 0x7542FFB66C2972ABULL, 0x515C115569A7B844ULL, 
            0x1EBA8F0EA0180E05ULL, 0x5C2ABBF86BCAA399ULL, 0x527FB749EF5B98C3ULL, 0x643D044D6599FAF8ULL, 
            0xB2F742E779C62CF7ULL, 0x1C8081054945A69FULL, 0xC4CAAFD5E7DFFE61ULL, 0x9F3D0C8CAEDAACABULL, 
            0xB7EFC814FF6F68B1ULL, 0xF55C339D62A72490ULL, 0x0D803800D86270ECULL, 0x7AEE4870B002A0AFULL, 
            0x980BA38524CA68CAULL, 0x64D97137AE540627ULL, 0x1C91323CCAB3FE80ULL, 0x564EE2C72F3D4CBAULL
        },
        {
            0x025B1A11755F61B3ULL, 0xD2E461B2F98C797DULL, 0x7293D89E804CB86FULL, 0x07BC969432D48F56ULL, 
            0x6E2D9FAE05CCAAC2ULL, 0x12544BC6BAA6F605ULL, 0x1B273032F388ABB2ULL, 0x453A6F8A5D15F40CULL, 
            0x571AF259527BE36EULL, 0x5A2432103C3B614FULL, 0x14BF29FF17EB4FE7ULL, 0x5C681C42DEC0B017ULL, 
            0x8E76864C863B056DULL, 0xED2D138D70C2063DULL, 0x9604B9FB1FF48610ULL, 0x697A59BDADBB69F3ULL, 
            0x603E4E23B977E707ULL, 0xAA9A4E230BC218FCULL, 0xD56E1F49866CF0A8ULL, 0x1C0574EAA71BE38FULL, 
            0xB7F10233AE903825ULL, 0x924F6F4190084F07ULL, 0x7C00750A13207F94ULL, 0x873CD49665154060ULL, 
            0x0B956EAFAB68648EULL, 0x6CA59258042106B5ULL, 0x3A04F2EB05BCFE7BULL, 0x3B2801536311DE71ULL, 
            0x8153437E6A72291BULL, 0x292ABD6607EDA256ULL, 0x65E06B2237D65F5DULL, 0xCEFF5B0FAC9328E6ULL
        },
        {
            0xE469C752FAB898CEULL, 0xD7C59D38F65A9EFEULL, 0xFE717FAAC044155AULL, 0xEE7FDEC8C060DA79ULL, 
            0x90BD130BDAC52249ULL, 0xA96E81B9BBE1AD18ULL, 0x33D6228A479C4061ULL, 0x831855406A085665ULL, 
            0xE3D7EABBAA6A4FB0ULL, 0x86C97C7E1BA09D72ULL, 0x91A45247F3107F24ULL, 0xA6B2BC68722C38AEULL, 
            0xFF713D93259356ADULL, 0x4ECD80638E3193EDULL, 0x8F2BECF90257D2DEULL, 0xA161567A5119A36BULL, 
            0xBD36C116760A7C91ULL, 0x85A538A69E5B7A94ULL, 0xA0522F7B3C7D2CB4ULL, 0x6B23BA51BA2ED002ULL, 
            0x2C596B3E7771F064ULL, 0xCED3CE65B5F66917ULL, 0x65D3AD74D9B3A0ADULL, 0x645BF8C55936AB08ULL, 
            0x6C6C20B6142E23CEULL, 0x1E07A13EAC6D9C9DULL, 0xB821C6CA02134562ULL, 0x282F82E4A43ACC7AULL, 
            0x04D66A5859B57F4DULL, 0x7E96759B24814503ULL, 0x093666B83E460BAFULL, 0x6A937B5AB2BA14BFULL
        }
    },
    {
        {
            0xFB40575F34834AFFULL, 0x7E56195E3F012794ULL, 0x7C0070624ED595D1ULL, 0x551CF908B4C5D375ULL, 
            0xC6FEC266A0E0A30FULL, 0xFFB139FB05F7F26CULL, 0xDDFEDE3FAA8AA2DFULL, 0x10EBFA1C684E5182ULL, 
            0xED7496B6BF6642DDULL, 0xE6F14BFF2395F01CULL, 0xE3FF7030B909387AULL, 0x906E28C08A087819ULL, 
            0x33774347A305668BULL, 0x3518D34CC46154C7ULL, 0x82C4E20BA52370BAULL, 0x7A790FD44375095FULL, 
            0xED137BF23D2FF4FBULL, 0x4A1A04EA10DEE75FULL, 0x5864C9A2993C112DULL, 0x12ACA65FC6080C2FULL, 
            0x73267B1CBBC5C9A6ULL, 0xFB2F7A326CFA7FA4ULL, 0x61D3E024114C1647ULL, 0xA5766743AE2D95ADULL, 
            0xAC74F1F16E897786ULL, 0x0C23264FDC6ED339ULL, 0x04A674F92A0E1470ULL, 0x8E34DB659A5D7D16ULL, 
            0x1DF031C1038FD235ULL, 0xA2AAC90DF9CB0ADEULL, 0x72659E0353620791ULL, 0x318576EE2E31E049ULL
        },
        {
            0x05761D9CE1F35E94ULL, 0xFF6ACB7899071B7BULL, 0xD3858E32196AA997ULL, 0xBAA1CEE43005A79DULL, 
            0x19DAD35A6F80055FULL, 0xE8263FEE342FCA02ULL, 0x491B4B7CA3122360ULL, 0x4CF3A881B17C9EA5ULL, 
            0x3B4E38B450A68D85ULL, 0x82FECEA0466EFAD3ULL, 0x3EF8DEADBC3CC711ULL, 0x49337E6971CAF94BULL, 
            0x7AC3B38C03C9C018ULL, 0x4F2AB77DBD52950BULL, 0x4E74BA054D22FD73ULL, 0xD8BCC5F559D15C12ULL, 
            0xB7D29684189D62DDULL, 0x6E3E4FDC4670AAC8ULL, 0xBD6AFE2961640ADDULL, 0x1B904EEBCFB75DFBULL, 
            0x4262B09D12F16348ULL, 0x47E6189443CB9317ULL, 0x80F14F7B258EFA18ULL, 0x562E46074A76FC7AULL, 
            0x56BE833E95CE2885ULL, 0xF2C7A76AD9911B3FULL, 0xA2F4D5277B0A0063ULL, 0x1E122870D45E90C1ULL, 
            0x1AAADD121E4D666AULL, 0xAB2013A6A6395DB1ULL, 0x029F8CA00E00545EULL, 0x3741525DD3022206ULL
        },
        {
            0x834E20D2D0CED64CULL, 0x6AF3D84D0BF0F022ULL, 0xA03327300FC555D0ULL, 0xF60E051DC90B514FULL, 
            0x012DB2E25A0C375DULL, 0x38B2ECCCD5E7C91DULL, 0xCB439AA11291E4A6ULL, 0xD6504E6334C5B49CULL, 
            0xB688C7EC6920333CULL, 0x9D41DDCF0E6003A7ULL, 0xAE3BA6F9F320FCA0ULL, 0x45D07BADB4D53189ULL, 
            0xCB44E7743DC291AFULL, 0xC25BA0E389269505ULL, 0xA68414E68961855AULL, 0x1C3267633EDB8FF6ULL, 
            0x41E57D2C187C1AABULL, 0x6539FC69D0557057ULL, 0xC9E794151952C54EULL, 0x3B8DC9C3835819AEULL, 
            0x7DB136013AF7C039ULL, 0xCA4CD7EA70BE9532ULL, 0xA262F2144CEC7D56ULL, 0xF024C3493C4B70C2ULL, 
            0x586735C40270F044ULL, 0x4C3DA0CA1CAC6AB6ULL, 0x09428A4C2FAF675FULL, 0x061025ED1F75739BULL, 
            0xB58D24ECF7CBCE5AULL, 0x079A20A34934358CULL, 0xB4B0D873959C7486ULL, 0x827ABC399541A46BULL
        },
        {
            0xF606D2C1BB6911FCULL, 0xEB92F0152BBA78C8ULL, 0x46CBC42E128593ACULL, 0x103653ADFCF3852AULL, 
            0xEA946EAC53E7D820ULL, 0x1C2574B5BD4F21CDULL, 0x2ADB6A15FA66C1BBULL, 0x1C7F94E1B9EB4089ULL, 
            0xE7F53F7E67BE0B92ULL, 0x114FBE8ADA95BA2AULL, 0x17AAA62F0192CA34ULL, 0xCE59704A3ED48D20ULL, 
            0xD64C6192B85193E9ULL, 0x183F8F8F6F4886CAULL, 0xCD4E001499460FB4ULL, 0x09EFDC747B7C731BULL, 
            0x30767A4EA58E8A0BULL, 0xD7829873F0CFB95AULL, 0xB4B2D5E814F65792ULL, 0x1CB0ECE58355B97FULL, 
            0x1A2CEC8BE8D29891ULL, 0x77EE822C8EE96E0BULL, 0x09BC6883E6833A8DULL, 0x54F2423461D8D1A2ULL, 
            0x2DD804AA79FBABF5ULL, 0x99EF364811979A5DULL, 0xEDA5E465DC26B82AULL, 0xD46996106A85FFABULL, 
            0xF6A4FEAEC476905CULL, 0xA61EB612879CB458ULL, 0xC250EC0523FD2590ULL, 0x5136295F3113A47CULL
        },
        {
            0x8C576837522150BDULL, 0x734BDACD24101D94ULL, 0x8D4EFE91FCD160D6ULL, 0x1E247DEA47AEB20AULL, 
            0xAC57D6B71A429DC4ULL, 0x1CBC623910D4E35BULL, 0xB3886882FE752FB3ULL, 0x82EEA1C4A8C6843CULL, 
            0xD9CADF451B817930ULL, 0x591F37AF946FFC77ULL, 0x7BF7B58E25F2DA8AULL, 0x138CD3E73BFAFE09ULL, 
            0xAB0E6B05E81D2E7BULL, 0x6E0390CD48A39E89ULL, 0xD1C926CB78C6DE90ULL, 0xE2CF9645EDBA29A2ULL, 
            0xE87F372EE7EDDC89ULL, 0x7F1A82FC2D614152ULL, 0xA66C1C3EB680F763ULL, 0x205C4405C8926608ULL, 
            0x3C4E9DFD4E26BD55ULL, 0xD0E55D5E9601EF66ULL, 0x088E309B308904EBULL, 0xE7F99785DA06E2D9ULL, 
            0x3DA15E46D138AAC9ULL, 0x8A0386EFA100675AULL, 0x4399B7083DD85EBAULL, 0xE77AFAE2376EA630ULL, 
            0xF5710662B57473B9ULL, 0x2DE6C80DBAB353F5ULL, 0x7AE706559BEE7B3FULL, 0xAE5DB5FB3B9B768BULL
        },
        {
            0xC7A74EB4EC6FFB1DULL, 0xDBC4C88313B68957ULL, 0x51CA90865C980A87ULL, 0xC749B30B270C9736ULL, 
            0xCE084D8FE6FAF27EULL, 0x1C71AC15855CA055ULL, 0xB2A86909FEA0D7E0ULL, 0x7D0DFEC5AA263CAFULL, 
            0x6B9DF729CBDEF44CULL, 0x98FE78E0764B13C4ULL, 0x001ED2C57D7930DBULL, 0x233D01842A8C9B26ULL, 
            0x0BE2BED3E2275C06ULL, 0xBBF5D14A4699C2D8ULL, 0xADD08A150CA62A6FULL, 0x0473E1E990DFD7B7ULL, 
            0x960D21DEB5239CEDULL, 0xD11E3A4555952718ULL, 0x346EBC9041C41ACFULL, 0xB697230BEF8301E5ULL, 
            0x96847791CDEA2B84ULL, 0xFA581AC033DCF050ULL, 0xF045B990271E1103ULL, 0x4CF799C5AC80DC12ULL, 
            0xAFB13957731B1BF7ULL, 0x428C295AA24B2E7BULL, 0x1926B8567DBD7636ULL, 0xC382E33C65CDFF42ULL, 
            0x8E2BEDB68B97B71EULL, 0x8DFDC03675056F9BULL, 0x864F813F89E059D3ULL, 0x3C42194AEDFE1809ULL
        }
    },
    {
        {
            0xD7DBBCBBEA993DDCULL, 0x42F7E0B5D8D5312CULL, 0x50B99C20C62135CBULL, 0x3D4F01574FEC88F9ULL, 
            0x261D5A55DBD3DF15ULL, 0x3BA463EA9C8991B4ULL, 0x81D4E0827D2D42D2ULL, 0x32FF00D3044BDE34ULL, 
            0x226B2A74FEF60D38ULL, 0x3169DDBA31C2FC42ULL, 0x84BEF8C90FBF383BULL, 0x32168376F4346507ULL, 
            0x1907D08C6A938C17ULL, 0xB898CE456C88968EULL, 0x3AA757AFC4ED39AEULL, 0xE5DCC72962839120ULL, 
            0xE27A33F1F5A0CE84ULL, 0x481AF41DFC7104DEULL, 0xEC2E0AA934CB46ECULL, 0x815AD0A434E17C52ULL, 
            0x919C831EBA27376FULL, 0x28451926DF4306D3ULL, 0xEE6D1D4FC14D5DFCULL, 0x41CF59992A51AD8DULL, 
            0xDFDEDD38B7185123ULL, 0x96346926C4F67B68ULL, 0xAC50053C9C4147FAULL, 0xB6CAD4C76F83E530ULL, 
            0x2CD85E3D61CBADB2ULL, 0xC0C0CB08790FC63CULL, 0x99713FC77C2E6AD5ULL, 0xDC04FA71636A849DULL
        },
        {
            0x77D6BAF25BFF39F7ULL, 0x10B5729377E8BA6BULL, 0xAE8C24E3E2BC618CULL, 0x8697EA99937FF3FFULL, 
            0xB8869287E2E2EE70ULL, 0x2598CC23DEEC3C68ULL, 0xF0FAA2E58D66201DULL, 0xD93D1BA281E4DCF2ULL, 
            0x86D248FFE7E26331ULL, 0x933A31743CC18B1DULL, 0xC0C2A4D32192C29CULL, 0x5DDAB718652FB741ULL, 
            0xAC34ADBE79AE7431ULL, 0xF3BE1B4AF531BC6FULL, 0x1E667965FCF3C51EULL, 0x5BBCD3002BB89589ULL, 
            0xCF82C0EF13E949EAULL, 0x6B8038FC24733E6CULL, 0x252D3B14DE2A51ADULL, 0x56E1190C7E2743DBULL, 
            0x8158065CDD721CF2ULL, 0x92E79C1140F43837ULL, 0x6744E9655B8FA45DULL, 0x65A22D24E4DFD3E2ULL, 
            0x5E014F52648D32EFULL, 0x7269FFE2D7C226DFULL, 0xDF7B9DF14B37462CULL, 0x2C75F719CF05D8A8ULL, 
            0xA567013C9B446E31ULL, 0xE301641D36AC94B2ULL, 0x81F58FE9F40ABC8BULL, 0x9CA01281B48CC213ULL
        },
        {
            0x19EABF0A65316CDBULL, 0x2F80B16C15DF0481ULL, 0x440CF976CCABA60AULL, 0xAA3812DB8E4D1E07ULL, 
            0x5D4100BFC512437DULL, 0x9C8CC78DF7A3DA30ULL, 0x24750BB315C2E962ULL, 0x5975C51B1F20A180ULL, 
            0x3B0DEBCD2CCD5579ULL, 0xC7098327922B9CC9ULL, 0x05C36DAC6E502EAFULL, 0x94F8BF7FFB2CFC84ULL, 
            0x1E7FD08315E10355ULL, 0x1D490BA9E49B4F03ULL, 0xE016EEBEAC7424A4ULL, 0x1470FFCAD80D872AULL, 
            0x994F6908315A645EULL, 0x2AE2FA232BB3E6E0ULL, 0x10FB71311BDBC890ULL, 0x371C652BD2818F86ULL, 
            0x1AB7D85F42664585ULL, 0xF60DDE3ADA0C73B9ULL, 0xB63C0BF039445499ULL, 0x454BCB5F66A9929EULL, 
            0x198DE03D1CFF9068ULL, 0x795D228C25CFBCA4ULL, 0x12CABB3978CF3476ULL, 0xCC8B52A176EDC2BDULL, 
            0xB635580298E1E545ULL, 0x116DED12F324D21FULL, 0x821F0ABCB7CC5CD8ULL, 0x10C298631C682D9AULL
        },
        {
            0x702445600FD3DFA9ULL, 0x4446F2A101E4F5F1ULL, 0xCDE1589163A2718AULL, 0x8B0369D813DF7E09ULL, 
            0x116E8698D09EBB39ULL, 0x2D2022AED1DB7F70ULL, 0x239668E07FD31154ULL, 0x0C0CDA97BD87713DULL, 
            0x986C611A0DE4DA90ULL, 0xE4D15CA17B72D1D6ULL, 0x045612344031DEADULL, 0xDBA384AA872429A1ULL, 
            0x96AED9E02DCA0710ULL, 0xCC14261C2AA6F577ULL, 0x3F40993EB56B7706ULL, 0x11901B036C3E3C22ULL, 
            0x85474986A521612CULL, 0xBC479C82B6E5E558ULL, 0xE105EAF4B91F7763ULL, 0x68C8C8BDF29D8C05ULL, 
            0x38F2ACE9040B6E7DULL, 0x263232047DCB3A33ULL, 0xC9684FB808099768ULL, 0xF94E6591A6912964ULL, 
            0x17D550349A6CDCDCULL, 0xBBBC9AF499027344ULL, 0xCDBB683EB8B99675ULL, 0x3231983A53C9A4E9ULL, 
            0x5C22FD3ABE78F120ULL, 0x697EAD341C9B91F3ULL, 0xD21BE0710EFFC12FULL, 0x127A710B9045DC4CULL
        },
        {
            0x7677B32DB58FFF95ULL, 0x79216A0B87BB7800ULL, 0x77800994250F68E2ULL, 0x0DDE009F77FF59A8ULL, 
            0x292A6084633804A1ULL, 0xC7CD5A2C2A2738EDULL, 0x495AE618C4B123A8ULL, 0xB2CB68C635C0AA00ULL, 
            0xBF20D211778E6F32ULL, 0x67FAAE747674C7E5ULL, 0x6A1E58B2FB75D559ULL, 0x66A30854222BE032ULL, 
            0xADBF10AF047339DBULL, 0x602A89CA1ABB67B8ULL, 0xC72C95CB85FF37DEULL, 0x3BECCD5A32AAB27CULL, 
            0x599C9C964BB2C138ULL, 0x00EFE3043948EFF3ULL, 0xBC677E5397C48963ULL, 0xA8861122E4AB6EE9ULL, 
            0xF09CE90794BBA087ULL, 0x0C437598BD4BE865ULL, 0xC3F680DD09E0224DULL, 0x70F39BA3AA932AAEULL, 
            0x46C85DCAFA024F57ULL, 0x165050192500608EULL, 0x6A5207E67B5BCCD6ULL, 0xF58114FAE9238550ULL, 
            0xEE9D3296FF9422C4ULL, 0x36DC2358F5D7D967ULL, 0x045876B63E553AA1ULL, 0x78945F5BD7DCF834ULL
        },
        {
            0xD82AA55EBF376793ULL, 0xCEDB25F75273DBF2ULL, 0x2291265DDC377219ULL, 0xF3FF0515A07E2F40ULL, 
            0x9C0177DC05B719B2ULL, 0xC9EC9DDAFDE8B80CULL, 0x0A7E7486E384DDA5ULL, 0x59A0053D4D59B0BEULL, 
            0x1C2B4A0B6A5C4E94ULL, 0x84D303AE3A301C5CULL, 0x668A425939776AA0ULL, 0x2B265F533CE26B77ULL, 
            0x77417F6829085767ULL, 0x00896EC46571D602ULL, 0xCC0D39C20932A10BULL, 0x980326E1CD732617ULL, 
            0x786B99963908D726ULL, 0xCD67B657A61407A2ULL, 0x1B16F16E917194A1ULL, 0x72A3341CFA5FBE5FULL, 
            0xC2131DB3C46312E8ULL, 0x33842715D608AB1EULL, 0x2C272BB11755465BULL, 0xF297F9C351F53B67ULL, 
            0x5CFEA28D60966410ULL, 0xC8E5F0BCA830D505ULL, 0x1936AD561E8157ADULL, 0xA0D3316C0A98AE04ULL, 
            0xF64831A0A4DCBDD6ULL, 0x5B89091B5D230A3BULL, 0xAC5F183E6FEA9DE1ULL, 0x94EEA1929333620AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Sirius::kPhaseHConstants = {
    0x938265098B2C7133ULL,
    0xC22CE18B2D3CBC4DULL,
    0xB5C4933924E437FAULL,
    0x938265098B2C7133ULL,
    0xC22CE18B2D3CBC4DULL,
    0xB5C4933924E437FAULL,
    0x98A0420CB6A1DC97ULL,
    0x1C278DF9633C6F46ULL,
    0x4F,
    0xC1,
    0x73,
    0xB3,
    0x3C,
    0xE8,
    0x81,
    0x6D
};

