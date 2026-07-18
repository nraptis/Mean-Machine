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
    std::uint64_t aPrevious = 0xB9153FE5869C4720ULL; std::uint64_t aIngress = 0xE22676BC743130BBULL; std::uint64_t aCarry = 0xDB545E02C79B3C29ULL;

    std::uint64_t aWandererA = 0xC9815CE1AA004730ULL; std::uint64_t aWandererB = 0xEC4B6928AA8A15FAULL; std::uint64_t aWandererC = 0x82200CA0878D5B30ULL; std::uint64_t aWandererD = 0xD6180D9A0C7E6A80ULL;
    std::uint64_t aWandererE = 0xE605B923CD0AAD41ULL; std::uint64_t aWandererF = 0xD712567ABAA9D6C3ULL; std::uint64_t aWandererG = 0xEC2372543708C1EBULL; std::uint64_t aWandererH = 0xD125C47AF713D38CULL;
    std::uint64_t aWandererI = 0xAAC208264C8A6B73ULL; std::uint64_t aWandererJ = 0xD7EA8C0CC23A92A2ULL; std::uint64_t aWandererK = 0xD8B09D0FAF2EEEBEULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14879838549291063083U;
        aCarry = 16550692736985663411U;
        aWandererA = 15894915723455815015U;
        aWandererB = 15926404454431042148U;
        aWandererC = 9670369431912457653U;
        aWandererD = 10474620975428062486U;
        aWandererE = 9910602734050676605U;
        aWandererF = 16880036622609626862U;
        aWandererG = 17914274905510661758U;
        aWandererH = 17533053147408452319U;
        aWandererI = 18278252098338111151U;
        aWandererJ = 13237879826483681563U;
        aWandererK = 14903685598682061306U;
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
    std::uint64_t aPrevious = 0xD2C6CDC7377C8FEFULL; std::uint64_t aIngress = 0xE0E6037D5AAC8981ULL; std::uint64_t aCarry = 0xC7202B9873FC8E9CULL;

    std::uint64_t aWandererA = 0xB003D4D4D8EAA503ULL; std::uint64_t aWandererB = 0xFD6ACCF47A50FC93ULL; std::uint64_t aWandererC = 0xBB0DE0A06C764186ULL; std::uint64_t aWandererD = 0xBC1CE2E4C8C3F364ULL;
    std::uint64_t aWandererE = 0x97C10E083BAF1DB8ULL; std::uint64_t aWandererF = 0x9870850234E38905ULL; std::uint64_t aWandererG = 0xC49C21D069261FD8ULL; std::uint64_t aWandererH = 0xAECFDB9D4A544748ULL;
    std::uint64_t aWandererI = 0x8AA1397C389C22F0ULL; std::uint64_t aWandererJ = 0x832CAC564F20962FULL; std::uint64_t aWandererK = 0x88CD45928148448BULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17909538906739967794U;
        aCarry = 16461448089314645189U;
        aWandererA = 16007836212683031600U;
        aWandererB = 15893622906003867484U;
        aWandererC = 10584789605307672842U;
        aWandererD = 14344873268881515494U;
        aWandererE = 14640746261971114620U;
        aWandererF = 10690231331109783285U;
        aWandererG = 11633845674522784986U;
        aWandererH = 16790571723655668474U;
        aWandererI = 11351098343476451955U;
        aWandererJ = 9505392546379809265U;
        aWandererK = 11585032433036949532U;
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
    std::uint64_t aPrevious = 0xB40212EA650EFAAEULL;
    std::uint64_t aIngress = 0xDE24A0777AAE675BULL;
    std::uint64_t aCarry = 0xB15246B23C2EE500ULL;

    std::uint64_t aWandererA = 0xA3F644F516CECA81ULL;
    std::uint64_t aWandererB = 0x8D6307A4FAF80893ULL;
    std::uint64_t aWandererC = 0xF4363D954156C6BAULL;
    std::uint64_t aWandererD = 0xE2716BA5E2BF5576ULL;
    std::uint64_t aWandererE = 0xB038DB5C612BA029ULL;
    std::uint64_t aWandererF = 0x8D27E44EB612959BULL;
    std::uint64_t aWandererG = 0xE6FBCA95ACEE55A2ULL;
    std::uint64_t aWandererH = 0x98942CBDF0DB1CA5ULL;
    std::uint64_t aWandererI = 0xB4E51B606A2265A4ULL;
    std::uint64_t aWandererJ = 0xA7787150A39116DEULL;
    std::uint64_t aWandererK = 0xC69B79720448F263ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneB, 3);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneB, 7);
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    std::uint64_t aPrevious = 0xBFA3F1B51C83AE45ULL; std::uint64_t aIngress = 0xA2BA398FDEAB32A5ULL; std::uint64_t aCarry = 0xBCD7938DF652B810ULL;

    std::uint64_t aWandererA = 0x866A517AD69471D2ULL; std::uint64_t aWandererB = 0xDA57D11AE9D18B7AULL; std::uint64_t aWandererC = 0xC01F618851D5A458ULL; std::uint64_t aWandererD = 0xBE2F0CCFA9D7B085ULL;
    std::uint64_t aWandererE = 0xBA26B853205CE4B1ULL; std::uint64_t aWandererF = 0xCFB5FF12864C5ADFULL; std::uint64_t aWandererG = 0x8718DA01B37284D0ULL; std::uint64_t aWandererH = 0xDDD36127A8A27E8CULL;
    std::uint64_t aWandererI = 0xF748D9FC744610DDULL; std::uint64_t aWandererJ = 0xA695870F6CA23C63ULL; std::uint64_t aWandererK = 0x90DE8B798E907BD9ULL;

    // [seed]
        aPrevious = 15321550196187787343U;
        aCarry = 14244514888409249446U;
        aWandererA = 14159072584356352512U;
        aWandererB = 13511862662553675843U;
        aWandererC = 17109374848088574821U;
        aWandererD = 17405420048967761766U;
        aWandererE = 15453665605199935278U;
        aWandererF = 13239751105061444704U;
        aWandererG = 18285517456609909100U;
        aWandererH = 14382919511887695003U;
        aWandererI = 14733984281463078230U;
        aWandererJ = 17643172272982397426U;
        aWandererK = 10704330091715513949U;
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
            0x0410CAB355EA0BD7ULL, 0x928601B86ABD1C9EULL, 0xAA0003049399FF97ULL, 0xD98BEA0EE9798520ULL, 
            0xF5491A235977BB28ULL, 0x0A0031BC011E7BF0ULL, 0x24136F4004325D1BULL, 0xE413F4970A2C4D92ULL, 
            0xB6DBE0A680889122ULL, 0xBED387580B39DC74ULL, 0xCA95D4C291C87B3DULL, 0x248FD8E785831A5FULL, 
            0x7B3D1C01435ADB8FULL, 0x8936E7F23AF800B5ULL, 0x844797A41686F527ULL, 0xBFE88F5424185FFDULL, 
            0x7B1DC6517DB4D186ULL, 0x49B984C0B9D05D1BULL, 0x89F3FCB600B4701DULL, 0xC9B555C375B0024CULL, 
            0x351C5BFDF7CF2AFCULL, 0x0B36443C5611CE17ULL, 0xB883602A4AB4EB4AULL, 0xFA5571A8A376318EULL, 
            0x52100A6B358DD9B5ULL, 0x5B8A243604A7CCA6ULL, 0xD9C54DD367868E49ULL, 0xCF7BBD4BA439E34AULL, 
            0x322F50C6AA3D8395ULL, 0xD0186E60DE015848ULL, 0xD6AD3F47F014F1F7ULL, 0x3EDB2D66345E801EULL
        },
        {
            0x97A23A29DB5EA9B3ULL, 0xECEAF02EBCC40F2CULL, 0x640E5C2E9FE4251BULL, 0x5A1823517C45F850ULL, 
            0x14C81F6CDA3583F0ULL, 0x505FE0E7A4EFCE48ULL, 0xE0E1701CCBFCFD03ULL, 0x606D0CFD9663F2B6ULL, 
            0xFAAF3563FD32FE56ULL, 0x383B025F7AE04698ULL, 0x2D3D4066417FB97DULL, 0x6C08E40ED21701D9ULL, 
            0x3D4AF78813CAD0C1ULL, 0x5ABD4AD0AD93E4C5ULL, 0x6371376735C19900ULL, 0x26CEF388E166D95EULL, 
            0x08DD13B9F2EBF7BAULL, 0x79151054D1C67424ULL, 0x4AD236399A23D82EULL, 0x83BF44C555A3C71CULL, 
            0x590A772F56959504ULL, 0xF4E2C59500819892ULL, 0xA79CB8F62803BDDBULL, 0x56706D328F929783ULL, 
            0x1AD02B41650DDCE3ULL, 0x0AA50D922D4C6EFFULL, 0x548AFC3AF1EF2A4DULL, 0xBB437D89DB335E3DULL, 
            0xDA45AE473C69BB03ULL, 0xFB90110EA904D991ULL, 0xC6C9C2D0A9B6260FULL, 0x8D4F410CF6F12E18ULL
        },
        {
            0x7B2A31151BC69EF3ULL, 0x3D15AA84B958BE76ULL, 0x678FE20A491A3D56ULL, 0x36DCC5E4DBAC6F89ULL, 
            0x2B4A601ED98E5908ULL, 0xCE315FB08FEA7C4BULL, 0xFB5D210FF0598608ULL, 0xB80FA8ED7A42B8A0ULL, 
            0xD0D9CB155A663B92ULL, 0x6461CFFCF7F3194BULL, 0x21524B622EE561EBULL, 0x3CFC51EFFC29D2D2ULL, 
            0xE89D087F849236CAULL, 0xB459833B14A7DB3EULL, 0x4C3BA4F83355AF4EULL, 0x9786AA7A65EF1894ULL, 
            0x41645BC4564C92C7ULL, 0xC77FD8106F6D9D5CULL, 0x5FF9E7CDE31CD360ULL, 0xA9D0AB74DDF7C400ULL, 
            0x95BCE518F016CEA0ULL, 0x75257B517476AAECULL, 0x9EE7ED293465FE0AULL, 0xAF9B7F1DB4F4E127ULL, 
            0x0E4C975D7EE5608AULL, 0xB45191BBAAAE85D9ULL, 0x48605D641CA93A92ULL, 0x376B3EE892733320ULL, 
            0xFA71FA0CC8D33E4CULL, 0xF8BD967134D09239ULL, 0x55A9DAFAAAB10EE5ULL, 0x06BD0C08566678D2ULL
        },
        {
            0xAA3D86D1B1282A8BULL, 0xA07B9CDDECDA05D4ULL, 0x1CE3D867C72E72C1ULL, 0xB4156E57D8A7E9B9ULL, 
            0x744A6B731DF3ACEEULL, 0xB3ACFBE5599AEFC4ULL, 0xD226C2BDBE537D20ULL, 0x2D800FAF23244B1AULL, 
            0x4FCAA8E3D54A6963ULL, 0x2F6A637E5EA33C87ULL, 0xCB9D1976392F0979ULL, 0x0C27ACCCBC16A333ULL, 
            0xDF974D0ED9182C16ULL, 0xB9C6EA8831F4533AULL, 0xA42D269C4C6E7081ULL, 0xA10D283B8D687AFCULL, 
            0x547290CC889D0143ULL, 0xB0285240A1D6193CULL, 0x96AC51C8D270D0D5ULL, 0xAD4EABCFF48E6440ULL, 
            0x51424433E5E8CB14ULL, 0xCF15794FE0127FCFULL, 0x71D5D0B7D8FC1AB0ULL, 0xADFD33E03CD366F7ULL, 
            0x32214ADC029518D3ULL, 0x55B8D757FC609E6FULL, 0xBDE8D1D869F0A1E6ULL, 0x3CAAC8487B431C7AULL, 
            0x93694CD31D9C6BADULL, 0xAB3DFE556E5DCE85ULL, 0x869E7850BA9D9EECULL, 0xB5758973BCF77638ULL
        },
        {
            0x6573CD73CEAF0101ULL, 0x9A1F7792BF687C65ULL, 0x3A9962A0A87AF7D3ULL, 0x047E6C566C25075CULL, 
            0x4608F2B25A7CD1ADULL, 0x5721FFBF80F78F60ULL, 0xA12B878ECB925FF3ULL, 0xBAE68A2B7C2D0D98ULL, 
            0x42C380A84994623EULL, 0x7B6605A876DCBD26ULL, 0xC229DF091E0A8E5FULL, 0x812BB578D2414E6EULL, 
            0x4571EA920F08CD9EULL, 0x7C3C0D5F229880A3ULL, 0x20D40B0792FDED06ULL, 0x0CE26327121D7023ULL, 
            0xA8F66D0E2536163EULL, 0x42810DF7CC91309DULL, 0xA574EB50B09FCA40ULL, 0xA8DC72674B485DDEULL, 
            0x14A3DD7EDFCD40FEULL, 0x414B14292F00C442ULL, 0x3B319926D1A50447ULL, 0x8F718D9491B5B493ULL, 
            0xF6569EF25EA688DFULL, 0x93414B77C97D4CCBULL, 0x0BB3A260E6E7E4A2ULL, 0x76A0368A240C8298ULL, 
            0x574B161CC76EE7A2ULL, 0xAB5033706425D6A9ULL, 0x077549FAA03EB0BCULL, 0x8613B1B948F2DBC3ULL
        },
        {
            0x3941E1527AC895DDULL, 0x72AE6A775A17CF7FULL, 0x65117E15AD07DB63ULL, 0x96B41BAEF8D6C728ULL, 
            0x2B7F5338AB50960AULL, 0xB3297C1EF8FAA173ULL, 0xB52F77D1023B980AULL, 0xC19EB5432AC142B0ULL, 
            0x0B0B16E9CE462D37ULL, 0x4BD3EE03F84D6605ULL, 0x5B204208C6246F22ULL, 0xC76AB84E932DFD93ULL, 
            0x564DE57C6F6F310DULL, 0x66453A4645159888ULL, 0x0D29ACD129530AB9ULL, 0xB30BB62927C794C2ULL, 
            0x317AAE42B767CD05ULL, 0x2EF81A8CFD732E44ULL, 0x30998A8CF7CE0446ULL, 0x872266AD022C8C47ULL, 
            0x84963E5F4C8F12E0ULL, 0xD0CAEA0B569091ADULL, 0x1A6EA4C36D744765ULL, 0x0FEBD51DF56DF2DDULL, 
            0xA52BDE46B4C880B1ULL, 0x4BDCF94555F3F7FEULL, 0xA4CE087871D23AE0ULL, 0x6128F9C0CDBAEF6CULL, 
            0x4BAA69A7D0535163ULL, 0x502AEA204202F309ULL, 0x84231BE3BD5A2339ULL, 0xF068E619DD7CF950ULL
        }
    },
    {
        {
            0x83F86EB6FAA01202ULL, 0x2A5FE8F1F7A2A324ULL, 0x8911213AA02FE635ULL, 0xFA03802A0B58CD23ULL, 
            0x7C8182DE0E6E8418ULL, 0x53CBDFFE85A6A915ULL, 0x13C5272B9F74F8E0ULL, 0x06D68BF082D6CFA8ULL, 
            0x145601EE77A80C03ULL, 0x8A547B2D07E533A0ULL, 0xA1D8C73F55FB6D04ULL, 0x72410DA17C294D47ULL, 
            0xFF2347C6A8D53BBDULL, 0x9FB65D92BD4D3149ULL, 0x70D4B95CA379AC84ULL, 0xBD7241FDD07AA684ULL, 
            0xE95283135C39255CULL, 0xC30EB36048DFB788ULL, 0xA63AB15ABD4B4C7CULL, 0xA245CA86324F3B8DULL, 
            0xCAB57B5C5015BD3CULL, 0x8FEA8AAFF8DFED0EULL, 0xB28856E13C22111BULL, 0x6AB4197A9BE7CAB2ULL, 
            0x57BEABD53F608AADULL, 0x3F5BA34C7E8BDCA7ULL, 0xD36FBD3D3C0EBC25ULL, 0x135E47FE6997B0A9ULL, 
            0xBA0588DBCC5FE8C0ULL, 0x7BA22F44B479A9FFULL, 0xD06EB418A39476BEULL, 0x92D06A49AF022B39ULL
        },
        {
            0xF1227F9F72D7F9F0ULL, 0x40CB2939E8CAADC6ULL, 0xABABD17F47625D92ULL, 0x16B970CFDFB1DA53ULL, 
            0x837A4E52A8D04B76ULL, 0x08A7C7A2C7332CDCULL, 0x409CD6A53039034CULL, 0x3A35ECCD435C7A7EULL, 
            0x4D8C3714C33D498EULL, 0xD4E6472DFD70F94AULL, 0x90B8727016B58843ULL, 0x3F7D4808E84A5602ULL, 
            0x71AA78322B097D8BULL, 0x0066C57E9EFE9A43ULL, 0x014AA7DFAAFA92D5ULL, 0x7480D4D22C12FD48ULL, 
            0x906DD64C16226453ULL, 0xBEB75AE353F53ED0ULL, 0xCB2A6B1C170F0636ULL, 0x74A2B81F5813E1ECULL, 
            0xE35D97F94F9A5F7DULL, 0x12606EF30C869071ULL, 0x53A9389D27C098A5ULL, 0xA9C34B84F4DC45F8ULL, 
            0x3B1424F41BC01AFBULL, 0xB4753ECA78B353FFULL, 0x8ACF5CD6548B19E2ULL, 0x9E45ACB2C38AA4B5ULL, 
            0xD94AC6316F8C2023ULL, 0x330B022106B423D3ULL, 0xE633D11BAFFF331BULL, 0xC2A79E3F35D4C2D6ULL
        },
        {
            0x2ABFDE33E82B0332ULL, 0x7307C16708C335BEULL, 0x6A56EBE69B595E1EULL, 0x5B2BE131C2894415ULL, 
            0xD6E7521B8EAB42C2ULL, 0x718822E317D0FE64ULL, 0x0ED393A3B8CF4D9CULL, 0xFDB22CD78FB61C72ULL, 
            0xE86EACAFF2C781FCULL, 0xE21690E32FADE589ULL, 0x2B528450AEB5ACDFULL, 0xB215772D5C1ECF8DULL, 
            0x8C1D2623D4F05D4FULL, 0xD3D1A6D8CD271106ULL, 0x62C8878BCA98E693ULL, 0x7B514C63B92FA522ULL, 
            0x88565322EB7E63EBULL, 0x5A4D8808AF2D27B7ULL, 0xBA4364B0ECD9330BULL, 0x89DE13C0F1E90892ULL, 
            0x36600AC58558118EULL, 0xCB3A680C22A04349ULL, 0xC48A59B3C33941FFULL, 0x25CDA99D1CB22F64ULL, 
            0xDBDF423812ED0149ULL, 0xF5B6C6E28133D90DULL, 0xF7E575FA8922B3CCULL, 0x30CAC4FDDCB9CBB5ULL, 
            0x16406086F3F256AEULL, 0xD702CC957DC53E32ULL, 0x0E30B52E6EC47F17ULL, 0xA13AE6E677364394ULL
        },
        {
            0xA346869F70D189CAULL, 0x9E45B86B1F266DABULL, 0xFC3584A246411CF8ULL, 0xC030C1BBBEAF4571ULL, 
            0xE5102ED2B895D0ABULL, 0xB1AA45112EB62F52ULL, 0xEA29AD9AD9EEF1DFULL, 0x10E46151388216A7ULL, 
            0x6C1D5B1988ECBBC3ULL, 0x1C8948945D8C70C3ULL, 0x13483A04B1226E1BULL, 0xC3F54EA054F50EF3ULL, 
            0xFC2E52B94C6FA929ULL, 0x3B54D6C959569A95ULL, 0x779875A62CA747E3ULL, 0x30E7F009D9F5121AULL, 
            0x7D7957F7C50F32E0ULL, 0xFFF81FB92F74C2C7ULL, 0xE53588EB388475F0ULL, 0x0F9A378CD6C99011ULL, 
            0x1B95C3A5665DEA1FULL, 0x813BF82926BA1A39ULL, 0xFBF3709277263180ULL, 0xC9EDC13064027F0DULL, 
            0x98DC7767BACDFCFCULL, 0x0DB34191825D647FULL, 0x099CCEF508ECC947ULL, 0xE852301710487598ULL, 
            0x87CA085F5244AC19ULL, 0x276F5BC647A5FCFAULL, 0xCF401E4310555452ULL, 0x9565685D931DC14AULL
        },
        {
            0x199489FF15337BA0ULL, 0xE1903A75D4B56236ULL, 0xC040DCAEF07601FAULL, 0xA85BDD8A3EDBEF6CULL, 
            0xE7607A6EEE29E4A0ULL, 0x975C1925B6C31714ULL, 0x5D5DEDB8D8E81B86ULL, 0x329E146FD5D695A9ULL, 
            0x42763CC322DD7CCCULL, 0x04AD9D8598262264ULL, 0xC6335051DAC085D0ULL, 0xF9904B8EDAFF6264ULL, 
            0xBC2D3E6B684B099BULL, 0x9CC3262A32D751A2ULL, 0x339AEE5F321A4CEEULL, 0x749F13DAA38AA47EULL, 
            0x0A9D334CC40383F3ULL, 0x9D362857E73CFC81ULL, 0x915E8AAF9D6B840DULL, 0xC75EF350883FCF38ULL, 
            0xCB5235285F3B351EULL, 0x6A0DCA5EC2B97E82ULL, 0xCB6FDA7B367C42BCULL, 0x6F3D58D18B756560ULL, 
            0x87DD3CEBCC170FB7ULL, 0xD45FC07D6C2DB959ULL, 0x93D5210BAD9641C9ULL, 0xD2B4CD7AEADB07FBULL, 
            0x9ED452FC6FA0A60CULL, 0x7921BA3062854684ULL, 0x25F4F40A4B628E6AULL, 0xFB43DE8EB52A5B2AULL
        },
        {
            0x730F3BA5AB27CEB8ULL, 0x629394BAB5A4BB8EULL, 0x242A6BA0FE7C2740ULL, 0x2E30B71E2460595FULL, 
            0x8790FD5738BB764BULL, 0xB2C83A1493D0988BULL, 0x32082F94958F27B2ULL, 0x691EA509A80BC9F3ULL, 
            0x6EABD32C8C0064E7ULL, 0x6ECED3BDE299EDD5ULL, 0x062B7A2850055CE9ULL, 0xF6C9FE4E3815F4DDULL, 
            0xC18DCC6ED0012BDDULL, 0xE5AA7807F9CBB1A2ULL, 0xE73521CF1F2F45D4ULL, 0x291A26B3C1D02C01ULL, 
            0x8588CA1A7996156EULL, 0xDBF66A94741B5AB0ULL, 0x581444440DEAF019ULL, 0x016EB08CD0C69206ULL, 
            0x89E63A63EDDD8574ULL, 0xBCB0C27B50036684ULL, 0xAA3E9E4B289EE01CULL, 0x02816A093972491EULL, 
            0x42E49F89CE0B0497ULL, 0x641096FDEC9ABD76ULL, 0x550CD37C68361079ULL, 0x4D9ACB983352236EULL, 
            0x95DCE593333113FCULL, 0x1F61BC162C740AD4ULL, 0x64216CBE80FD6C59ULL, 0x11613826D2543370ULL
        }
    },
    {
        {
            0xE1F52DF59B573636ULL, 0x28864DC30FA7E74DULL, 0x8232012350E2E14CULL, 0x7D91DC5903D04DC5ULL, 
            0x8C5828109672FA18ULL, 0x726026217CE7E6C0ULL, 0x1DF856A43CFC94E9ULL, 0x071023DE5504BB69ULL, 
            0x423C8D88A60F5EA3ULL, 0x4CF10DD6E74D9733ULL, 0xE7C4FE6E984B6699ULL, 0xA68AEFE405DBB009ULL, 
            0x4DD3745F7B270AF4ULL, 0x5ED43F53436FABEAULL, 0x9322DF1C19A9026CULL, 0x34FF59C3C3A0E830ULL, 
            0x221C922C46951459ULL, 0x87493E6E750A4704ULL, 0xC1B7944DE6CCB816ULL, 0x86232C30C7C5D6BBULL, 
            0xE44B2EDDDECA1167ULL, 0x415913A61818ECB5ULL, 0x62542300F8B6E02FULL, 0x8B303D6EE8849754ULL, 
            0x88E73750CC0C8465ULL, 0x694A277CF0537CCFULL, 0xF2C34F57B6AB1318ULL, 0xBA2488913AA25B5DULL, 
            0x1684226E019C6459ULL, 0x0067F1C625587AACULL, 0x0008C18B66092C4FULL, 0xA3A2D95AD91162D4ULL
        },
        {
            0x9BC4A5E668CB0DB4ULL, 0xE4D39B48E6EA6CA3ULL, 0x3B844CA897772DFDULL, 0xC256D6B3C7F92A4EULL, 
            0x8EED6D327DD59310ULL, 0x6AC906ADD625D6A4ULL, 0xB0D1D084CB88E888ULL, 0x6BF6AC060B882754ULL, 
            0x1DF6B45627885B32ULL, 0xB6CF94292CE6FF45ULL, 0x20B7102F869DF263ULL, 0x358A9BAB2EBBD86CULL, 
            0xB4582D1B38DACFFAULL, 0xF815F0CCAED76268ULL, 0x08D39AAFF7380ABEULL, 0x58A4FEE0DA17404FULL, 
            0xE4BBE9F41ADAB501ULL, 0x8B0BCE06E99F7C07ULL, 0x3DA1BF3C2797F5F6ULL, 0xC44671E1644276F4ULL, 
            0x436373DF8CBDC6B6ULL, 0xD0A02D94D2DB8D41ULL, 0x99B552EAD1B20967ULL, 0xBC1F5C52C98581DFULL, 
            0x23DF9CD2C8FFC0BEULL, 0xFBA0704A366AFA74ULL, 0x86D62F279B78C2E8ULL, 0x28145B2DB9FC4032ULL, 
            0x29A2B600E6238EF4ULL, 0x3FB7F0C19D010480ULL, 0xE068A0324E8060D3ULL, 0xBB485F63B83C9D73ULL
        },
        {
            0xD1E904CF89097F5CULL, 0x6FA6DAF7A3725FB2ULL, 0x1B6F6655E8259008ULL, 0xD186089C89DB574DULL, 
            0x54DC540E1A0C8073ULL, 0x63FE1D39987B4FAEULL, 0xA33E0E1B677F23B1ULL, 0x28D4BEE211332EECULL, 
            0xF2DC320033EFB16EULL, 0xC6243AEDAB27446CULL, 0xACD808C335F4D329ULL, 0xF7F9DC9002D3B435ULL, 
            0xEBDD26F025B9C75BULL, 0xC1F7C92D8CBC8215ULL, 0x96D9008F0D702E4CULL, 0x73CB99A8A01BE686ULL, 
            0xD1AA5EC1A4D0C3B7ULL, 0x1448EBB3C0A02D35ULL, 0x763D5EDD11FF8172ULL, 0xD25F9E7AE8F22EC5ULL, 
            0x1104F3A7BF48ED0DULL, 0x269399C0C5DF3A94ULL, 0x5C6F26C65B19AD50ULL, 0xCBEBF6FB7EE68991ULL, 
            0x2AD73B7157F65780ULL, 0x9A5216500A35D21AULL, 0xE7A56DE2BF469A2EULL, 0xD402FE4F2A0539FEULL, 
            0xB2162390F0A99278ULL, 0x35E4A3E0482AE055ULL, 0xDE3033517BE36079ULL, 0x77C08905E8AE1C9CULL
        },
        {
            0x303A338DA5F89978ULL, 0x7B2B18449EC3610AULL, 0x183CCF9EC433CC7EULL, 0x477D28E250BD1ED2ULL, 
            0x5E41D23FD9B8C6D2ULL, 0x80AFA34DB23052D8ULL, 0x6E1DD05B1D06DE3DULL, 0x71347945F13D0D0BULL, 
            0xD2112F2B6F966B31ULL, 0x4B4FAA29215CC06AULL, 0xF1363386C20D9F91ULL, 0x3D420578B6352F63ULL, 
            0x692641CBABB7E52BULL, 0x9816CC35C3FA49C4ULL, 0xB1BC1E0ED0FAB045ULL, 0x331D91ECC9ECDEA0ULL, 
            0xD513140608965380ULL, 0x00A277AC13CBC37FULL, 0xCAF179E65E6F8E9CULL, 0x207FC74FA9726603ULL, 
            0x98A557562DDF50C7ULL, 0x912849359CA28808ULL, 0x05796398EBE349A5ULL, 0xF79A751DB95B1C31ULL, 
            0x51201940D1818DF2ULL, 0xEC527A8CF459A7CAULL, 0x9B2D4B8A966CF22FULL, 0xE964379872ED18DDULL, 
            0xC62F5990B91EEAE2ULL, 0x6D0C9B7F27C0EF00ULL, 0x02AF825F2FED9D76ULL, 0x334BF33A5900EB2DULL
        },
        {
            0x9A49B6C3518EE966ULL, 0x08030585C06E1827ULL, 0xFF3D65A68A23D0DFULL, 0x3CF78CC10FAFA08EULL, 
            0x1BDF3796C99CFE1AULL, 0x5685AB6658E9B36CULL, 0xB3265407813CA24DULL, 0x29EC54B342BE79CEULL, 
            0x52B2393FB29A1463ULL, 0xF82637EEA48A6744ULL, 0x2E5958241B28CD0EULL, 0xF94A9E8D90BAE2A3ULL, 
            0xB36E366DE9B27CA1ULL, 0x699029932FF409A7ULL, 0xC1659E854992669FULL, 0x0021F76CF19B0F7CULL, 
            0x0681B624C4558D7BULL, 0x384E9A858465E510ULL, 0x76DF9CC814CC4BB6ULL, 0x82AF3CBAE7DB99E6ULL, 
            0xC01CFDBABB38F3CCULL, 0x262224A9687BC355ULL, 0x4D65375B8E7D136CULL, 0x57E1B6BBC9A5AD4AULL, 
            0x7BF53CDA59DA675DULL, 0xC71B1935D236CAC7ULL, 0x932B1D9AAFFD3650ULL, 0x32532612DE163756ULL, 
            0xC560D24610DD62B2ULL, 0x3C3CC411298BA694ULL, 0x5418580D62D6FF14ULL, 0x9DC33A5C18C45E3BULL
        },
        {
            0x5A7B97A560615F8EULL, 0x4DE5CCEDCD4B3D2BULL, 0xE64A985ADF182857ULL, 0x81AF6267487EBDCFULL, 
            0xD52B8F0D6F2D2AEAULL, 0x31813B29781FBEE5ULL, 0x33C8C083E26FF177ULL, 0xCB9F417FEADE960AULL, 
            0x23018A04A9E0E29EULL, 0x28D0B486EFA38D29ULL, 0x15FDCE6685D5C703ULL, 0x4D1984E23D392C69ULL, 
            0xD13C3C01E64D5693ULL, 0x5DC983C8AF2D5FEEULL, 0x80F4411735AC0552ULL, 0xF483036D9D862670ULL, 
            0x236EBAC5D5D5B68AULL, 0x077FBB560CB0A742ULL, 0x6819FA3E6A4B6923ULL, 0xC303A019E96ED450ULL, 
            0xE60E39364EE974AAULL, 0x4AD0C97FB5CBFC72ULL, 0x17311999963694C1ULL, 0xBD51A63706C3C3CCULL, 
            0xF116C47FD3654BA6ULL, 0xB1FBE2F969C95C1EULL, 0x5DFA495AA2BC7160ULL, 0xE2E7051C866A1BC1ULL, 
            0x6E8F8F090B2E28B3ULL, 0x223D3647EA5603DFULL, 0x4AFDAECF4E07A0A2ULL, 0x337DD4553277408CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseAConstants = {
    0x132470348033E168ULL,
    0x2B20D5D9EB162CFCULL,
    0x6603B8EE6B86E7BAULL,
    0x132470348033E168ULL,
    0x2B20D5D9EB162CFCULL,
    0x6603B8EE6B86E7BAULL,
    0xBE213B12C6AEE154ULL,
    0xD733558CD455DC3EULL,
    0x9C,
    0x5D,
    0x8D,
    0x72,
    0xF8,
    0xFB,
    0xE3,
    0x92
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseBSalts = {
    {
        {
            0x378719CE5ED71E16ULL, 0xA837ADE7D0780756ULL, 0x830A5FD282412C9EULL, 0x160844C2B4BDB33CULL, 
            0x66F02D7DEA75411EULL, 0xD5BD59FADC3307C3ULL, 0xAA0773DDA38B5437ULL, 0x1CA6185F47A76E55ULL, 
            0xAC7D38849A942986ULL, 0x32436FB396FE8139ULL, 0x8458FE5439E2F457ULL, 0xB9D231C3B41F8412ULL, 
            0x875B22B790C80AF2ULL, 0x6D5ADB95989FFC97ULL, 0xC781FD8B1C821715ULL, 0x5A02B3248511AE53ULL, 
            0xF903AD7CF16A4DBBULL, 0x376BFC7A5052CC9EULL, 0x9FA0E79735AFDE85ULL, 0x33D6D06B67EF7B65ULL, 
            0x37B6A52D8BDD4C71ULL, 0x313BB9F7F3F042FAULL, 0x582A5952078E1420ULL, 0xD176F51E0A91EB7AULL, 
            0x443AEEF3A7457E1CULL, 0xF67DE31C3A69E5F0ULL, 0xF6DA0452E941EB1FULL, 0xC92130E3294E150AULL, 
            0x4A65EAB188A4E27BULL, 0x2C1B60EBA5027592ULL, 0x8E32F1A2B1C7CFA0ULL, 0x3C3CC46D3E3AAD4BULL
        },
        {
            0x7A9A98281006DEB5ULL, 0x59CB06F81B9AE285ULL, 0xBBA0A4638C96461BULL, 0x18B106D58747FE3BULL, 
            0xFB8B0DB0F0D3347EULL, 0xEB2D64F957B0547FULL, 0x2A7649BA5BBB82BFULL, 0x6DF913878A4BA174ULL, 
            0x8A9713A30E234BBDULL, 0xF7379ED33D08B652ULL, 0x33069E16EC55518BULL, 0x619B7627F1C3F102ULL, 
            0xFFB752FF73D007F7ULL, 0xBC4CCACF314F20ADULL, 0x84C5CDC42E8308B3ULL, 0x3E7E25899F7E5DFAULL, 
            0x3C9685D984C2BBE9ULL, 0xCECC685E499E2F53ULL, 0x264DA8C025CB8D52ULL, 0x6812745A825BD95BULL, 
            0x19464079FE052001ULL, 0x3399B0A08B4E58D4ULL, 0x90DD07DE7F151C70ULL, 0xCFDF6D00532FD392ULL, 
            0x314566D57B7CC7FCULL, 0x054691A62424C873ULL, 0x4F8ED6DF52CADC02ULL, 0x1B76A92CD0B390B8ULL, 
            0xB7D480AC763F7B53ULL, 0x9216F73C9ABB4286ULL, 0x68561393DCD037DBULL, 0xDF14B09E37A581D2ULL
        },
        {
            0x1D72C922A2834EA3ULL, 0xA33F729B2A701528ULL, 0x780A10F922A64055ULL, 0x3DC92EAF982E550EULL, 
            0x4578F879E4E5D631ULL, 0x9C6B81A6681FC9BBULL, 0x0FA9709E52AC31A6ULL, 0x07906F2949286A23ULL, 
            0x92723C5BF29C4B9DULL, 0x7F03279F279BDECCULL, 0x26A57457B1001E6EULL, 0x97CEA6DA962DF69AULL, 
            0x94D680BBDC8A9022ULL, 0x5E55951551865077ULL, 0xFBA849D5A3FEBEF7ULL, 0x0BD54287C8FAC948ULL, 
            0xAB0170A35F03FD4EULL, 0x07864AE70B4CCBC1ULL, 0xFF668F0AD07331DDULL, 0xC00D8F8F54120332ULL, 
            0xB13AA3B6E74C12FFULL, 0x7174FE2DEA2D1670ULL, 0xC348B6F597314D59ULL, 0x69294A72F59046A9ULL, 
            0x26AD2D5E9825CB9EULL, 0x278CB70095885738ULL, 0x28DAC27DCB5496A0ULL, 0xCC3ECBCBCD177CC8ULL, 
            0x81436ADF5F6F5631ULL, 0xBAD846F0B992765DULL, 0xC9EF9CB3CF2088DDULL, 0x762CA6DC4842D652ULL
        },
        {
            0x9B57BCF17C8DCEA7ULL, 0x53D2E7A6F0E427D1ULL, 0x76DE7A198C6BA3BAULL, 0xC515AF283C152A3DULL, 
            0xF9DBA8C84C57D6C6ULL, 0xB3A7CAB769FA6E4BULL, 0xB90D8DDCE1181366ULL, 0x697F4293DB6CD269ULL, 
            0x091D4A3FBDC8BE20ULL, 0xA839E934AF6AE860ULL, 0x4CF1779B57DA90EBULL, 0xA5E2A3FC6E9737FAULL, 
            0x73F498FB6923F97FULL, 0x48CEC2B3609A9EE2ULL, 0x3545A225C7A7F9B1ULL, 0x21AACCFE3AA15837ULL, 
            0x4C7398A8E2745D5EULL, 0x55E37260971CB474ULL, 0x2CCCDBC3C100E0DDULL, 0x01F34B99E3F5DA74ULL, 
            0xF861C634F84D825AULL, 0xD570269AEE76855BULL, 0x06BFC38546AA1D53ULL, 0x7B4D243368A8B6FBULL, 
            0x50566DFE6AF69B6CULL, 0x8C0A9FD014F08360ULL, 0x5DED4EB685AF4EB5ULL, 0xBE017810E08D3D02ULL, 
            0xB5634BE6EA48B656ULL, 0x25C2D2BD9588BDD0ULL, 0x128D843EC218B44BULL, 0x977C9CB76018E82AULL
        },
        {
            0x79BBF6E791A24DE1ULL, 0xF3E97E3B8219CE74ULL, 0xAFD29B0DCCDA3F60ULL, 0x2EDB2605EA98D3DAULL, 
            0xDE84D78D22B68746ULL, 0x3A9E1DAD4764FEDBULL, 0x0DEBD535B9F77FD0ULL, 0xAA1FF8A6E60C6838ULL, 
            0xDF54A61275244D81ULL, 0x5286943518F57DA4ULL, 0x03EDEFB671FD7F33ULL, 0x636FECD6B192298FULL, 
            0xD7C0DEB9FFA102F0ULL, 0x023F0F83BA573C92ULL, 0x26B5B942C9020FE6ULL, 0xB6D64AEA8F30052AULL, 
            0x3862AE00B8B44C96ULL, 0xC0860018BCAD7804ULL, 0x6EF7BBA621BBFFFEULL, 0x5D978AC8247663C7ULL, 
            0xBD9B4CCD80A9BF3EULL, 0x142F3BA83080B1EFULL, 0x30A68A490C1F32CEULL, 0x27D1AE06DDE83F2AULL, 
            0x8DFCDA3A37235516ULL, 0x2D3284DF7170CC51ULL, 0x71A75FB257FD7FF5ULL, 0x557F005437D08C41ULL, 
            0x4A7F3A524A88DB29ULL, 0xCDBFA11B66B4140AULL, 0x3935F075A423A617ULL, 0xB528768AD5D6AC55ULL
        },
        {
            0xD91D525FF44AAE49ULL, 0x297437D05EA5E09BULL, 0x4B7544B99EB80ED4ULL, 0xBB62AB6731197546ULL, 
            0x880533427AC44225ULL, 0xC7C5081EE2386FEEULL, 0xDB3B8A57CEC10610ULL, 0x1C6E0F66157724AEULL, 
            0xCD48528D5C9CF9D0ULL, 0x2A074E767971B046ULL, 0x19CD78094BA73134ULL, 0x0493960F5C2A134EULL, 
            0x3AF29DC74C1B3DC5ULL, 0x8C0C614447FEAD4CULL, 0xC599ADC8736D2798ULL, 0x8C663DB9D051F8F5ULL, 
            0x881E94274D7E69CCULL, 0xFA484210673C92A4ULL, 0x9523FA0B31CAAC71ULL, 0xD6FBAE1A4DF632CFULL, 
            0x3E278B2F8A569522ULL, 0x5B0D8D1B6E0F41A2ULL, 0xC5C97BC3EA98A842ULL, 0x258493C7DA183D54ULL, 
            0x63CA9C979E8F755CULL, 0x0FFDB8E75B76F885ULL, 0x08E99D71992E29D1ULL, 0xBC9947D01312A44BULL, 
            0x3B342ADBF56A78A4ULL, 0xC2D9D3E506ECA5F0ULL, 0x27848823E8F5918EULL, 0xEAA03A4A8A4290F4ULL
        }
    },
    {
        {
            0xF273628528B4A031ULL, 0xEC54EAF46E795ED2ULL, 0x88A8E6E7598C1EF3ULL, 0x03D957C11B8B6EF0ULL, 
            0xC5A83EB3B58906D0ULL, 0xD6EA63F09753BFA8ULL, 0x768DB2272586EA40ULL, 0x85C09F116CBE58A2ULL, 
            0xF7497B9D505B200EULL, 0x25A6E6EE1E7BC1F9ULL, 0xE6C832651B827064ULL, 0xCCDC1DE43480A8E3ULL, 
            0x16D9CA9767187F90ULL, 0x28E0AB4C90B2829AULL, 0x13DC4BCE7F53E68DULL, 0x6D388EDC78657F80ULL, 
            0x19917EEE0E8C3191ULL, 0x1E003D9CDD517E87ULL, 0x431C8AFAB688F2D1ULL, 0x88D9A09AEC94DC00ULL, 
            0x9ADA77415E2F9DB7ULL, 0xAC70C86A96457DC8ULL, 0x32BDEED00BAA6DF6ULL, 0xC26734A6CEAFD4C3ULL, 
            0xC808B3274911C958ULL, 0x876BCFB66B6234D1ULL, 0x5EDE73DA01C6416BULL, 0xD0B460A8E077B215ULL, 
            0x8E959812CF2AC405ULL, 0xB039C493BB52A41FULL, 0x42430FFD8F5C8845ULL, 0x4332CEF716B097C3ULL
        },
        {
            0x3DEA8A301B7F2A31ULL, 0xE0659FC1B9AE5AE2ULL, 0x629E18746027D191ULL, 0xE45BCE4C73AD18EFULL, 
            0xC394568FAB43D395ULL, 0xE538718BAF6986DBULL, 0xB26F10AD90BEA5E4ULL, 0xC2F5F5F2ECE85C8AULL, 
            0x18B77612E201E520ULL, 0x2848B641E9073B8AULL, 0xC97AAE9FB80F44ACULL, 0xE12E8E56ACCE5D38ULL, 
            0x21BFBFAA0B00EB3EULL, 0xC9CCEF4154E709A9ULL, 0xBA79A941451D76C2ULL, 0xECCBE6B9A773353FULL, 
            0x72C9F7BC3C7EDE62ULL, 0xBAD3CAFF3202F0E6ULL, 0xD960442DBFFCA648ULL, 0xFC3E511562F4DEE3ULL, 
            0x78A151CF8861F33FULL, 0x85E83DF4C0C91423ULL, 0x9896C9E552FDDF79ULL, 0xF88B6B9D5BBAD832ULL, 
            0x27C8463F69AD17D5ULL, 0xF14FEF64E8966E09ULL, 0xC844C2B543275C76ULL, 0x604B105A5CEDA00AULL, 
            0xF9BE1742CA36FAB0ULL, 0x4603ABD1C7747BF0ULL, 0xAD19BAD7486B3E80ULL, 0x808413D84C5298E6ULL
        },
        {
            0x02C119E885B7C517ULL, 0xF750703199BFA49CULL, 0xA814098319221AF8ULL, 0xD68F99B2C542CA24ULL, 
            0x0E33EC7CDF879455ULL, 0x4F9E38FD59C173ABULL, 0x77251D7093D9D51BULL, 0x92F80321B2F6EBF7ULL, 
            0xA75F55C50B09750EULL, 0x0D613DD02C916BD9ULL, 0x432D3DF0C1E7806DULL, 0xCD3309B5CCDEFA58ULL, 
            0xF3AF7F76F8F0765DULL, 0xDBDAEDCF372C7912ULL, 0xED428E7DE293066EULL, 0xE93C53A20FB8325EULL, 
            0xBDA580E6FBE19D21ULL, 0xECB4069B08EDF6B0ULL, 0x46C996368F7D47F5ULL, 0x78CC1DA6AC1BEA8CULL, 
            0x9F2CC388B7B881E8ULL, 0x35F8ABE7410FFC82ULL, 0x33F161A95DB49AD1ULL, 0xC1D9D9604A8AB7BFULL, 
            0xC3AF6B9E368C5B6FULL, 0x0A398609E228A383ULL, 0xC2B0A1B1406F5A10ULL, 0x3FF755743E927A96ULL, 
            0x6AD5367F72E891D4ULL, 0x696DB8464BEC0CCBULL, 0x5C6FDB85C720F82FULL, 0x980DD434B654E2C1ULL
        },
        {
            0x51C395890D321DD8ULL, 0x9883B180A9E5E176ULL, 0xCEAFD5DB22A7AF28ULL, 0x411E40B24D673307ULL, 
            0x09F7967A82353298ULL, 0x68CCCD3946A749A4ULL, 0x07CFD026A5E507B0ULL, 0x19197DCBC38D8F79ULL, 
            0x58222251B37A31EDULL, 0xC347ABED5ED49244ULL, 0xED45F38924537CD7ULL, 0xC59D2FC1A835DCF5ULL, 
            0x19BD06242551BB15ULL, 0xD3FAB3C31B28A195ULL, 0x4EFF7AD53847D71EULL, 0xD6AD22C29003560EULL, 
            0x8D8AB8810F9CDC85ULL, 0x84561F2E6DAE3E16ULL, 0x73F24E1B26C94D97ULL, 0xEE7A509C793E395CULL, 
            0xB279F667126F0532ULL, 0x1B36F37B822EEC2AULL, 0x420016A6E67DD917ULL, 0x3473FE974F25A3C2ULL, 
            0x9AB3EB1D9EC61673ULL, 0x946C20305EE371D7ULL, 0xEB9D3B69A42320C6ULL, 0x6D506028C96BFF1CULL, 
            0x581E3BDEC9163636ULL, 0x3AFC80FC322CFE0CULL, 0x53CC6C40DAFC8AA5ULL, 0x3CD075BAF3D78D61ULL
        },
        {
            0x6281F683A244833FULL, 0x6B2D2F2088B2B325ULL, 0xF7AB40D16AA182BAULL, 0x48F8915DF34E67C9ULL, 
            0x0520579BA7286F1BULL, 0x6AB32E8F18279FF3ULL, 0xC6DF66819D784A9BULL, 0x002C771DD7DAFE0EULL, 
            0x79D1C952FAED6021ULL, 0xE5437088D9746BEDULL, 0x40EDB8C8CCB2840AULL, 0xC2CB46121FD3A35AULL, 
            0xF1D97D6FF9E8F6D8ULL, 0x0F60D9618B068F9DULL, 0x87AF94E32DF41868ULL, 0x283A4C166448CB35ULL, 
            0xDB68E9CC62B70669ULL, 0x3BBECF7F60A4E709ULL, 0x0182493865D8C10BULL, 0xE7033A934DEE7547ULL, 
            0x3B6697BEF4D548D1ULL, 0x59EA6C3A4684D54BULL, 0x8C4BBC2ABFB2B3B1ULL, 0xB8AF1766A845DB7AULL, 
            0x026A3E649AE01462ULL, 0x7830A7A5AB83489BULL, 0x267AECA93D2E28E7ULL, 0x258448EF9E9AE5E5ULL, 
            0x8CA62B9F4522F103ULL, 0xBC952E7BBC03766AULL, 0x77899E95B2FC5D36ULL, 0xC70B36FD9940C15AULL
        },
        {
            0xD427E0025FE8FC1BULL, 0x5DD17A9C9CC3E431ULL, 0x864F167393B5A62EULL, 0xCB2F15DB5F98597FULL, 
            0xD789D20D44622C02ULL, 0x65C1A1B7C519116AULL, 0x19CB52A5B068F9D9ULL, 0x493F119FA58E3784ULL, 
            0x0A162078296362ACULL, 0xF615BDC088763FE6ULL, 0xD55E5FDD4F0C5300ULL, 0x4C3338E246D8EEF7ULL, 
            0xD295E1B9738D22CCULL, 0xE4AA3CB22620C81EULL, 0x90C15B57A08EB002ULL, 0xE3570ED6961B47ABULL, 
            0xB1EEBC775DE405D1ULL, 0x97172257D9C733FAULL, 0xBB309701FA4DF894ULL, 0x20E22D908A9A193CULL, 
            0xE3DC2C2C3A9E4606ULL, 0xCCED52590C186E66ULL, 0x8BB81C80E4929A9CULL, 0x83BAD51B163275C9ULL, 
            0xFA0DA0CEBC71BE82ULL, 0x7A963DD83E436674ULL, 0x96EFF630A723C2FCULL, 0x7CB197F9E089DD9FULL, 
            0x2533ADA6FE36D2E8ULL, 0xF59692D29404E747ULL, 0x47DC0E18D00078C3ULL, 0xFA367C7F2EF2BED9ULL
        }
    },
    {
        {
            0x3A0EE325D2E6E311ULL, 0x09DC8ECC7952404BULL, 0x854D935FC3B16968ULL, 0x71872037AFBF0CC5ULL, 
            0x20A1014F32411406ULL, 0xCDD1F67434847922ULL, 0xC3805A976E26F28AULL, 0xB596129ACEF4E1AFULL, 
            0x4E13D15149291449ULL, 0x2AB72B28EE8FFB1EULL, 0x45E5459783EBA036ULL, 0xBB94B782FBF6AA10ULL, 
            0x4966F2BF4316FD46ULL, 0xE5A5EBD380580ECEULL, 0x91D9BE0403DBB4DDULL, 0xC0818E98AA141EC5ULL, 
            0x5C85894D5C0CBD71ULL, 0x611A627277F944EBULL, 0x8A929799F1A80AABULL, 0xA01108AA1EA9E6ABULL, 
            0xD1013DCCC8A0D217ULL, 0xD0F8E42EF4EFDAEEULL, 0xF35C9B14745307C6ULL, 0xC0030997709FB07CULL, 
            0x97237BD3AC85CBF7ULL, 0xFDD377D2CC7ECCB9ULL, 0x0A73A09A26E3B58EULL, 0x7ED7D6FA26239265ULL, 
            0xE8107A43E4DFB330ULL, 0xB155E933A9CF2F4CULL, 0xC8AEEE3F2A430545ULL, 0x6241CE0B6F3537B3ULL
        },
        {
            0xAF219B532A2D1840ULL, 0xA05F4C1C6769E265ULL, 0x541E8DFBFD557F51ULL, 0xE92A1AE0E07D0E34ULL, 
            0x99BDC38D6552FF3BULL, 0x5E4582DC1C08E9A7ULL, 0x65872CC38B13BB9FULL, 0x9B7B7260D1A0988EULL, 
            0xCEA67E8D3E45C957ULL, 0xAF0520275058EFD5ULL, 0xE016CE5AE7591EDCULL, 0xFA1D5D9EFBB48DDEULL, 
            0x7B8CE708C039BA15ULL, 0x9A9A9BCD518FAF9BULL, 0xFE4F9AFF6C9AD7E6ULL, 0x59649B516F45A60CULL, 
            0x666EC18A1785C753ULL, 0xE34FB86363674401ULL, 0xFBA32F06ABE6906BULL, 0x86EC89918E4B6CA7ULL, 
            0xDFFF6A37BA002DC8ULL, 0x700FC683631D5B2FULL, 0xF7D6EE44F7277397ULL, 0xB31D6584D092D38AULL, 
            0x437BE2BCADD54F6DULL, 0xCD2DFB37CD3E426EULL, 0xE09F90369B413E0FULL, 0xA1EA22097D480CA4ULL, 
            0xF4CF481F3765A4A1ULL, 0x28AB3736B1D23668ULL, 0xD63DDA07B1E9FF34ULL, 0x4079D13F31346CE0ULL
        },
        {
            0x40E576CAB0B9EE9EULL, 0xE2B4ABE4057D8BD4ULL, 0xEAEEAFDB0804EB7FULL, 0x8FD4584106CDBB51ULL, 
            0x83359A8EF7D8CD11ULL, 0xB2A849B5639A1A5CULL, 0x19AEE0019CE386E4ULL, 0xB144086395E70EB2ULL, 
            0xCC908FEE1EE4E091ULL, 0x43680D1BBCC804DDULL, 0xA90CA1632F9FAB8FULL, 0x773E3C1EC65F6C80ULL, 
            0xD4E38D79D28AE04FULL, 0x5147823B07A6DA58ULL, 0xD445D94ABEED6458ULL, 0x7C94C21B8A1B72E7ULL, 
            0x8F115241DF814452ULL, 0xD684CC6635FF6960ULL, 0xF4D74CD82823CAAEULL, 0x986B6E95EA6167CBULL, 
            0x66D1F4ECF862A6FCULL, 0xE55BD0C30B7C1019ULL, 0x8F0E1B7E98DFD058ULL, 0xB99712090679FD43ULL, 
            0xE46A9C208352F849ULL, 0xA3BD87CA8B9CF9FDULL, 0xC65477EE71963888ULL, 0xF50E1067D81498E6ULL, 
            0x4B0DA10B27DBF0D6ULL, 0xFA53183DC85E8A5CULL, 0xDE52CFEAD2F1B7FBULL, 0x70D0AB0AC4306864ULL
        },
        {
            0x3D588A7841DC5DB1ULL, 0x3026AE84D33E59D7ULL, 0x269D1607ECB40949ULL, 0x62D326D14D6B91F7ULL, 
            0x74C21CDC06A2CFF5ULL, 0x98D06C6E56987458ULL, 0x509101EB35AEF6BAULL, 0x6B005012BD7CCAD7ULL, 
            0x45CF22D0631D0107ULL, 0xCD73F618B10DBD9BULL, 0xF8AC880CDF0787DEULL, 0xC62AE0A69374BA20ULL, 
            0x61F7C0ADC555F5F3ULL, 0x63162988CA82DD1DULL, 0x1F565686C143827DULL, 0x7E5592B119A75B14ULL, 
            0x19903C99B190CA03ULL, 0xF54AC93E312187EFULL, 0xD3CED9829AEEEF9AULL, 0xCF8469F739F4CF2FULL, 
            0x4B8F41E19C512C25ULL, 0x3852145A999C47FBULL, 0x2F22975A0A511617ULL, 0x2CBA39F904493181ULL, 
            0x30BE799F0768411CULL, 0x88C522D2653FB69CULL, 0x01702B6EAA737450ULL, 0xA2D29773AE9458D0ULL, 
            0x1D98EABD0DBDC98FULL, 0xB4D7C6004E7DE199ULL, 0x1ACEEFF0DAA32DE0ULL, 0xD31947B049E96F67ULL
        },
        {
            0xD1B980DE518125D8ULL, 0xFE89B4490A8EBB64ULL, 0xFC0436FB53EB139DULL, 0x717973683B87565DULL, 
            0xE659A677862040FFULL, 0xC6283B30CDC6F0D5ULL, 0xB09582D290108553ULL, 0x2C3418D8E6718F21ULL, 
            0x7CA7734E6937DE5AULL, 0x67948DCE0D672A85ULL, 0x42DD8C57E9F078DAULL, 0x5CD7E63AF1738AC7ULL, 
            0x491AB11AA30068DEULL, 0x70C12C73A42CDC24ULL, 0x392D8393A5F02A68ULL, 0xA67D4E572AE1B38DULL, 
            0xBA564C69E76849A0ULL, 0x1C49DF8DA2422E07ULL, 0xFD8DF11A2DD3D65CULL, 0xEC2C7CD582C93401ULL, 
            0x35E62BFA2549C7ADULL, 0x0E6C74917065F10CULL, 0xDF7AF98A98764C70ULL, 0xC25C4CF1B4426005ULL, 
            0x34ABA720847E151BULL, 0x8D3B32C2B9A95435ULL, 0x9D138F2E7F0DC29EULL, 0x60999EA76FB50A2BULL, 
            0x5E552C236EEA2256ULL, 0xAADA9F35BD4F141FULL, 0xA360CA5C3198F395ULL, 0xE98D5C09C32B469DULL
        },
        {
            0xADEF4F83E8D157E2ULL, 0xA876B26E5DFB41AFULL, 0x11557E736C100D57ULL, 0x5C8CAC9BF13F41F3ULL, 
            0x24E2B39108173C21ULL, 0x0768ADB5AB5E5E4FULL, 0x3AB5AFFCEF5B2A7BULL, 0x2839D018419CF464ULL, 
            0x8F175AA517CD52CEULL, 0xBA824EE455218751ULL, 0xA272C2B73A2BCCF8ULL, 0xA1BD3E5DA13E6407ULL, 
            0xDD31E0563F194AEAULL, 0x4C0E771639328BD7ULL, 0x35A356257A2BDC4CULL, 0x56BF21E95ED96291ULL, 
            0x8553468EEB041021ULL, 0xB94505AB2FADB00CULL, 0x1A7F59D9CA0FD609ULL, 0x85FCFA042BC84546ULL, 
            0x225363C8D0F8ABC0ULL, 0x8B99EE75C4F6A879ULL, 0x4ADCF3068F18A1EFULL, 0xE84E8C4E0D08E8A0ULL, 
            0xEB5EED25921DD4CCULL, 0xB9E189B888700E9EULL, 0x5A8A9EC0DBFA45E9ULL, 0x083F6677BA69D5C9ULL, 
            0x93A314570C42531EULL, 0xAE5B5624F71DA77AULL, 0x6E8B06D0CE42264DULL, 0xA731FE9DAC6006EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseBConstants = {
    0xFF69B84F839B51D3ULL,
    0xADB66BA1ACD634A1ULL,
    0x360B40BA8C08FF35ULL,
    0xFF69B84F839B51D3ULL,
    0xADB66BA1ACD634A1ULL,
    0x360B40BA8C08FF35ULL,
    0x751F75099C5F2630ULL,
    0x822F6644AAC6D1F8ULL,
    0xC9,
    0x1A,
    0x80,
    0x7E,
    0x3E,
    0x60,
    0x38,
    0x23
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseCSalts = {
    {
        {
            0xFE6663B207ABCCEFULL, 0x786857196CDC5288ULL, 0xC3BD267C11EB1BD1ULL, 0x1B1DD8027F4BA83AULL, 
            0x2094AE527B575D15ULL, 0x41D43880D15F564FULL, 0x75F5352AD059B8EDULL, 0x886AB4D1801312A4ULL, 
            0xE887196603EB0CB5ULL, 0xE5742CD8432DE88EULL, 0x7A27C94359D4C51FULL, 0xDC76553C6DCD7CE8ULL, 
            0xEDA68B6CB46BAF5BULL, 0x5F5215A440F96031ULL, 0xAF4B75F0329E4E25ULL, 0x8CD1E4A291B25C73ULL, 
            0xB0EA59997539DAB2ULL, 0xA35EE695657D0D62ULL, 0xF3B925715FC7B520ULL, 0x124C2914AE0085FEULL, 
            0xCD923C711B1BCE85ULL, 0x68F6BA53AA9A5990ULL, 0xCEDB627B26CB52AFULL, 0x0361FCCFC82FC695ULL, 
            0xA7D2D9C85EACE55EULL, 0xDC80926D951B2F20ULL, 0xF6B13FCA520ACE41ULL, 0x8DF36D15BEC5D781ULL, 
            0xCA0A698DFE1EB7A3ULL, 0xDE158AEBE02031DCULL, 0x9E39EE9CEFAAAD50ULL, 0xE1621A6F3F937B4EULL
        },
        {
            0xE5D3C99F8DD92756ULL, 0x160F8F7C92D3A8F8ULL, 0x042CB5C178F441E9ULL, 0x1D5F6ACE42CFA051ULL, 
            0xE4E3DB88C7E0D236ULL, 0xB003397722E31BCEULL, 0xEF965CBC27E94F6AULL, 0x5F6A521929B0C6A5ULL, 
            0x5F3DF22626CD35E5ULL, 0xB801CBC0F911E628ULL, 0x3AC4ABDED1525F58ULL, 0xA1F5DEB3ECCCA542ULL, 
            0xA5B4E312F1F163C7ULL, 0x160E6AC46158FEF4ULL, 0xBF37FFA5D0A40F89ULL, 0x47E827F688715B57ULL, 
            0xC40F2E2D6D39D4DCULL, 0xACCE2D79577A3EA6ULL, 0x1328E92462D967C6ULL, 0xA09C6095350294B7ULL, 
            0x6DFD38BA401A5A5CULL, 0xF14D4A95AC9D0312ULL, 0x188705D69B120D42ULL, 0xD4680A72386E64F6ULL, 
            0x3193A89B5C6A3BB6ULL, 0xB77C1E0EC9B2FC8FULL, 0xFC173F1D8AE514EEULL, 0xF0AB3AC6D1F05188ULL, 
            0xDE2B3B20907A749DULL, 0x6016365EBAFB6FD9ULL, 0x73BF830E16AEF421ULL, 0x6230D2B67141400CULL
        },
        {
            0x4332BEBCD8B07848ULL, 0x8A7F0760566834A6ULL, 0x464464A540ABAE54ULL, 0xE5FB2F23D40E7747ULL, 
            0x0B153114A634973BULL, 0x84CC6B658953BD9BULL, 0x909E053C1908E66FULL, 0xB3F43CA91833EFDEULL, 
            0x91A7B96E2130F00BULL, 0xCCA3A127705592A6ULL, 0x7663F2953D7FD857ULL, 0x5B83C6C1C64AEB91ULL, 
            0xD73E4B3FEFA4BA0AULL, 0x45AE9398D542954CULL, 0x9B910ED9F07D038AULL, 0x6EB2E2E2403FA52BULL, 
            0xEE8F280963D310F5ULL, 0xF62F3D3BBDF53EDDULL, 0x86BADBCE475511A6ULL, 0x156CFC60E897F73BULL, 
            0xBD292AB80A89A89CULL, 0x39424C46E10D007AULL, 0x038346CD6FE58060ULL, 0xE5BCA42B62BF003DULL, 
            0x0C78D3ACA2E76728ULL, 0xF781E5D1D0DAF2F2ULL, 0xD50185CE32D40D51ULL, 0x79C21F1C2D9376E8ULL, 
            0x184683D2FB4583C2ULL, 0x76444AF2A8E4DAE2ULL, 0x6E19CCA6D66C0965ULL, 0x0E935B7022DDB6DEULL
        },
        {
            0x4CF846A7123279E5ULL, 0x5D8B79EA0379BB29ULL, 0x26A700ACCB20659EULL, 0x6C5C13319A104337ULL, 
            0x0EF9F5840BB0B4D5ULL, 0x62E69A256F955F9FULL, 0x0022A7B1643F8904ULL, 0x56FB363BB6042CE8ULL, 
            0x3E19950B46220EEEULL, 0xF941F999141FD037ULL, 0x1EBA58082DF284EBULL, 0xD69C49DE2597175EULL, 
            0xDFBB720E0821357EULL, 0x726AC3E87EAC7879ULL, 0xC2AA882F57447628ULL, 0xC8D76E469823A8C9ULL, 
            0x5564227A29935F96ULL, 0x0B6222420CECF070ULL, 0xB161E38D2A004CB3ULL, 0xCD0BABC29BBC9F41ULL, 
            0x8DAFFADE3D7D121CULL, 0xDDFFBA0D612E6F34ULL, 0x170817DB527A5EDCULL, 0xE138735BCECC7053ULL, 
            0xE008465281EE2FECULL, 0xC9B5C7791A841E51ULL, 0xA886B3A8E1395044ULL, 0x679FF9ACE785185AULL, 
            0xAF447E7292F6E6A5ULL, 0x12738A8F27B75EB7ULL, 0x1F15FD40A0451423ULL, 0xDD6492554C3F4EE0ULL
        },
        {
            0x8391ECCC9B3F8A50ULL, 0xF7952791E77C8C10ULL, 0x47447E5C30E389BAULL, 0x38BE262CB49A4610ULL, 
            0x26A19E9B6D532649ULL, 0x8E8AFCA3A3F4A716ULL, 0x8F25586BFDDE63E0ULL, 0xE4351ECD9E9A9C48ULL, 
            0x80777AE9FEECF508ULL, 0x64C414700DF599C1ULL, 0x4D83A9531CDFF1D6ULL, 0x36C33EFBF932EBCCULL, 
            0xDA5B5B3EC3C88D7DULL, 0xFE55F5800F40848FULL, 0x75B9C05C84020093ULL, 0x5C2CAEACC1F71294ULL, 
            0xDC3A6AE343DFA965ULL, 0x5C179D6E085A4C61ULL, 0x52C08D8C9F6BE072ULL, 0x87FF6CAA63CA178AULL, 
            0x3D0A3E7E33B2A096ULL, 0x111B7B1AE158AE54ULL, 0x4BA9A1732A6796C6ULL, 0xB12132EC269C0490ULL, 
            0xFBC79C7CEE643398ULL, 0x073F173424E5C0CCULL, 0xD78A8C2E5B2F3F7CULL, 0x16ADDDB9A20A6379ULL, 
            0x38F5C708A95CFD68ULL, 0x469807B3A264B012ULL, 0xB812893058B35773ULL, 0x4E041429A5D443ACULL
        },
        {
            0x4D717B04206FCB25ULL, 0x1D94829A39087C86ULL, 0x3E90CFEBBF107DA3ULL, 0xBE354C27E5D57DF8ULL, 
            0xA0FFFC3343333F6EULL, 0x27CEF1AD601E9BAEULL, 0xC08D3A90BFD22F4FULL, 0x8EF2A5C956B66AD9ULL, 
            0x495F3164AFDE6000ULL, 0x3F28F3E15E0E88C2ULL, 0xDF3CAABC773F3276ULL, 0x6BEF89B2E09074BAULL, 
            0x7333935AC96969C7ULL, 0x08B2D6C633C49609ULL, 0x9049A72F1E7ED948ULL, 0xF91C9F36F9F9758AULL, 
            0x214D8054CB521227ULL, 0x82092A251A0C2BBEULL, 0xB79829A5D063934AULL, 0x002D366784848114ULL, 
            0x6765233CF34E6DFEULL, 0x6AFBBE7AFFEAD8ADULL, 0xA5F482F9EAD30CA8ULL, 0xA496FB06C60305D6ULL, 
            0x26DF11FAA35225BFULL, 0x13612AA66F768041ULL, 0x958BD89315CB8F3AULL, 0xCB9378EC1C968C95ULL, 
            0xC4909ABFCDD2E8C2ULL, 0xEE102034F13E4C3EULL, 0x7D47D3E96BA43577ULL, 0xC74555CE15CD2D84ULL
        }
    },
    {
        {
            0xB0C513EFD86254A7ULL, 0x3B6783FCDEE26E01ULL, 0xF6CAC159F0FB07FCULL, 0x6BE146087DFBAA98ULL, 
            0x61F3F820C1D527ABULL, 0x0428742B85835676ULL, 0x4786CCC384BF100BULL, 0x4C74767008DD4A73ULL, 
            0x97152CE901DA5EB2ULL, 0x00F5ADAE154AC503ULL, 0x8DADB3779ABBF9A6ULL, 0x80359CDD654D0906ULL, 
            0x7AA88165D9665185ULL, 0x89B3B283FB3616C6ULL, 0x75C764CF7671FFDDULL, 0xF284C275CD810A01ULL, 
            0xF611F40DECF643AEULL, 0xDE3746D7455BCEA1ULL, 0xE48B3B8C90C381AAULL, 0xC92D7F87C4822C9EULL, 
            0x0F16650558CB482AULL, 0xCBBE3F5F1663C404ULL, 0x3FA0822C547B30F0ULL, 0xB5473C9D8175CB8EULL, 
            0xAC51A8179BC3114AULL, 0x6A39A5CAAB8B27B0ULL, 0x2DC02BF60DCDA604ULL, 0xD57023DFBA1D972CULL, 
            0xE5ACCAEE44D9D2A9ULL, 0xDF5A1BCB56D4408CULL, 0x13B84A2EC97F0F6FULL, 0x3D56EC4392D043F4ULL
        },
        {
            0x30DD40D6A35D9CE3ULL, 0xFEB8131E8CB855F4ULL, 0x05905C036964BF46ULL, 0x405C6A8878976070ULL, 
            0x2E6B151A80E476B6ULL, 0xCA402D9A50CB477BULL, 0x1905CA35D0031392ULL, 0x9AAF51A2D487AD97ULL, 
            0x4CF19CFC51618346ULL, 0x759FA2D24C9DE5E8ULL, 0x281571FF4F0DDB9EULL, 0x5A808E3270CEC8CBULL, 
            0x2DE5F59DA423ADBAULL, 0x597CD7A27F3AF079ULL, 0xFD2E28571078E7D8ULL, 0x41E1BD34814E9221ULL, 
            0xD705BA28E5BB27FBULL, 0xEB4C6A39B70340F4ULL, 0x27FEB01385F55441ULL, 0x5383463709286A84ULL, 
            0xD2C6BF46B4897CE4ULL, 0x12AE8731C90F898FULL, 0x752E2F8476B3CF8EULL, 0x464BB0D3C6234090ULL, 
            0xD36E7A8130324B53ULL, 0xFB614C402DFF3107ULL, 0x1EAE2AD233CF6677ULL, 0xDACD11AA918B8E68ULL, 
            0xC74508FA68D57F95ULL, 0x3D1BE5886D6BBAAEULL, 0x1314ED5EE3F512E8ULL, 0x5DE3D1B97617BA8EULL
        },
        {
            0xCF07D775F2DD1E1AULL, 0x8FE3D1732A04CC76ULL, 0xBEC5AC2FECBF6465ULL, 0x8726B076D907FA8CULL, 
            0x988A94B4AC1C25EDULL, 0x9868EAF6FBBEF243ULL, 0xA2C5525288652507ULL, 0x90CA1A358107E02EULL, 
            0xAD0B429391F090D7ULL, 0xF2DEA766FB5D6024ULL, 0xD39FAA02158F9D2FULL, 0xA964480E724B7A3AULL, 
            0xDAF184B69CDDE6CAULL, 0x320CFF693A2F1A2EULL, 0xE6340532093537AAULL, 0xABE95478451980C7ULL, 
            0x5E93F864B951150EULL, 0x230C244B38DCD116ULL, 0x25BF021D5B76B19DULL, 0x86B3DEB4F80038E5ULL, 
            0xD5FC2AD122CA1F36ULL, 0xD62AA629BF6B90E2ULL, 0x129E3B080F9D4FA9ULL, 0x32731211A467AA17ULL, 
            0x945EDDA5ABD805A9ULL, 0xD117AC675E2308B0ULL, 0x9A2D67C09DB5479CULL, 0xAD2C35D90BB96016ULL, 
            0xDE6AD1FA02EEBB6AULL, 0x274D12DBE3D0594FULL, 0xB2A0B41FB9C91EAEULL, 0x59F4D4883D313CEFULL
        },
        {
            0xA3843613359A99ABULL, 0xB7344E26C4FFA8CDULL, 0x9A69C74C1DED5372ULL, 0x174D7A2049529D5BULL, 
            0x841D77AEF359E7E6ULL, 0xA03E1FF0E4E8AB74ULL, 0x944BB26AAFEF5D6FULL, 0x4DDC0A89ABDFA0C5ULL, 
            0x4AEB01F93EF56620ULL, 0xAE878AE90D1EB237ULL, 0xD81EBD4BA17E770EULL, 0x74029E0680C4BE97ULL, 
            0x072F49A37693F61BULL, 0x7765F1BE5AA68A8BULL, 0x2C9A1E87C923F6B4ULL, 0x54AB6660048ABDC2ULL, 
            0x25C446BEEF6ED945ULL, 0xF556CBB3FC0ECB9EULL, 0x4BE39E5102DD4F90ULL, 0x68E3156622E5248DULL, 
            0x856144414C1CB468ULL, 0x994CCF16B7C89873ULL, 0x0D00370DD088CE47ULL, 0x674DB55231AE62B1ULL, 
            0xF3C493AA719A347DULL, 0xF9BD0A1FCD8E02CDULL, 0xA87CA2953D0E1217ULL, 0x2C01627C2FF0CBF0ULL, 
            0x501A9EDD4904E3D7ULL, 0x4A054F99C81BDAE0ULL, 0x4E0D032D5435016CULL, 0x6B841EB725201673ULL
        },
        {
            0xA80F08F5B37C019CULL, 0x47B397E9EEE27EC3ULL, 0x25729F862A1F939FULL, 0x380B48F5CF6C7CA4ULL, 
            0xF2D907F99B9D36CDULL, 0xFFEA9CF1671779B5ULL, 0xB645B6FB8661C023ULL, 0xD14FE3622349BD82ULL, 
            0x440EEC8BF61633FBULL, 0xAC4525379BB97B1BULL, 0x3DCF8BC0932329F8ULL, 0xC8AD40C4D884394CULL, 
            0xAE24350710D20B79ULL, 0x724DABE49AF4A5F5ULL, 0xBA200856E826B741ULL, 0x3E9E43F75CD0A59BULL, 
            0x93AA07FB403E0CE4ULL, 0x751395DA44A488C5ULL, 0x968809F7ADAC20FDULL, 0x46E3F32A1079BC76ULL, 
            0xE8474D819B03E29FULL, 0xC83B68DD09390A19ULL, 0x7C2A96C2E704144AULL, 0x20204160B7385799ULL, 
            0xAE76CCD1B1EFB9CDULL, 0x83E5DB4F50DDA47DULL, 0x53830CF5BCED9596ULL, 0x457B9873170CB3C5ULL, 
            0xB137FB81BF839A89ULL, 0x9781B3B30068BC98ULL, 0x19F7AE13AE6BAB57ULL, 0x56808E01D09A3A2EULL
        },
        {
            0xF52AF0A9CCE4CDEAULL, 0xC60A37CCE79C29C6ULL, 0x1A0D50C3D52EB147ULL, 0x89822A23351AA781ULL, 
            0x483A755A8FB8EF3DULL, 0x0B0692CD551ED00DULL, 0x704EFF3A4203D486ULL, 0x783B6D02E55ECF26ULL, 
            0xE048252B9E37EF45ULL, 0x98A4AB58B6A040EDULL, 0xD3850DD963CF36D7ULL, 0x3B13AC2523740F9FULL, 
            0x7631505C43E36C8CULL, 0x471EA5385947ACB8ULL, 0x6312C4F1C6B36674ULL, 0x7503BCBFC8B5613AULL, 
            0x2B73D68BF4A9A2C5ULL, 0xBD3C30EB95BBA12EULL, 0xDE9EB55F20F690C3ULL, 0xACF4F2C0B1D2F0F8ULL, 
            0xF1B8E53C8E81316EULL, 0x733F0F8AE866C8B9ULL, 0x36BAF2DE76D2CB84ULL, 0x7B9F78DD5D2D68BEULL, 
            0xC493ED14B33FF502ULL, 0x8DF6090AA34C6CF1ULL, 0xC19BA2FD9A62DE47ULL, 0x416E4BA12380E664ULL, 
            0x45192BACA9283763ULL, 0x6C9594C8B897AEE9ULL, 0xCAFBB86C667A54ADULL, 0x35E8CF2012B1592FULL
        }
    },
    {
        {
            0xB52BC9BFA57908D8ULL, 0xFF12CC73462A0FDFULL, 0x83303F51E322518DULL, 0xCE50A73391D79D83ULL, 
            0x25EF96DDF3B3C8D1ULL, 0xC586DA79C26165A5ULL, 0x45B438E9BEE953CBULL, 0x638D53A7509320D3ULL, 
            0xA15006EE46842EE8ULL, 0x21E943CD3225358FULL, 0xBEA57B6247582342ULL, 0x81E656F214C14A05ULL, 
            0x2E18754EA33D5708ULL, 0x59ACC5F7FE689C67ULL, 0xCBE8E2972B02BAD1ULL, 0x201BAE31B9B72CDDULL, 
            0xF1B640439494167DULL, 0xC56BF1ACDD519E6CULL, 0xEE1F6C83EAC3F3F9ULL, 0xC06E02C2EE320FF9ULL, 
            0x2FD65E9493F48B44ULL, 0xAE56A85C4BEE1669ULL, 0xCF65FF298AA67572ULL, 0xEAA8C6666E315653ULL, 
            0x24AB6DAF4F331B2DULL, 0x9572F84401A2593FULL, 0x695C6504FADC3BCEULL, 0xAC45FBC0CD4C3B82ULL, 
            0xF288AC694BF9DA66ULL, 0x7795BE83F97CF6BCULL, 0x3E938A20E011E0B2ULL, 0x5090F45E844706F1ULL
        },
        {
            0x983233C969B4C61EULL, 0x06A5D118F052AFFBULL, 0x37327DFD5D8470D2ULL, 0x6DA3633AD45B0617ULL, 
            0x3C9DA28F4199C03BULL, 0x84AE6096843C950DULL, 0xA0827ECBB8858978ULL, 0x999BFC1C95620F3BULL, 
            0x69E73AE3861A0F62ULL, 0x42B8F2EB579517E2ULL, 0x1205F8B808E1B6A2ULL, 0x13F98C35086C89ABULL, 
            0xC03C5995740277F5ULL, 0x54240582DCBE3019ULL, 0xEF2B53E1A3359A8BULL, 0x4851E93E3080C200ULL, 
            0x1044490D81ED18E3ULL, 0xD2550079BA4C836DULL, 0x8AC643BD1C00824BULL, 0x5189D99F3CD245EBULL, 
            0xBEB99F1FB47D2302ULL, 0xA3E9527A9D101E9DULL, 0x35770C2C01EFD827ULL, 0x3FA2701A6DF53BB2ULL, 
            0x7F08C8FD347F07D0ULL, 0xFE12DFA027B7EED8ULL, 0x500C94592E7DD930ULL, 0xBE96828D04728CE5ULL, 
            0x638B1F36BC3B2BA7ULL, 0xAAEADA571856D655ULL, 0x29709FE835C5BA9EULL, 0x3BA069B13D95B6BBULL
        },
        {
            0xF1606A45F7E788A3ULL, 0xB25224CADED79DE1ULL, 0x16A7096560D13E8DULL, 0x5D5D6DDCF226D50EULL, 
            0xED892AFA8E3A0C10ULL, 0x53B0D67B7486E4DCULL, 0xBCC7A75D46DCBC1AULL, 0x1CB98BC063C1D59BULL, 
            0xF66FF1F53EE3B727ULL, 0xF1056388F13CA3B6ULL, 0x71D0E327C7067EC2ULL, 0x524883D222BCA199ULL, 
            0xFF5D4BD5BFB4B0EAULL, 0xD426E5212128FDC9ULL, 0xC536DDE26504919BULL, 0x09437B5F633105D5ULL, 
            0x44E445922DD02319ULL, 0x9969794F8047F48FULL, 0xC652232E9D36F346ULL, 0x89A4CB008FE7B1A8ULL, 
            0xBEC8B0BD19AC4C23ULL, 0x30E17DEA221F1022ULL, 0x938C1F504C87F980ULL, 0xC679607AD868CEF0ULL, 
            0x5AA704096099FDF1ULL, 0x98C217D494B2047DULL, 0xEF69D0FAC91B314CULL, 0xF9C7252357F42205ULL, 
            0x25CF47D7B01BFE32ULL, 0xE1DE30EB17947313ULL, 0xEDD4D2C89A71EC91ULL, 0x4C0135B076AB34ECULL
        },
        {
            0x40A41FB38AE712A2ULL, 0x44DC1D2418A5FE68ULL, 0xCC6C71D032C0A608ULL, 0xF189EE9223E3804CULL, 
            0xB238DBCED4F90501ULL, 0xB1A7910575239FC2ULL, 0xCE8BD8A3BF7BB6D1ULL, 0x4629CE222184461BULL, 
            0x689577013D5AA12CULL, 0xF9C2C15F4E5AE018ULL, 0xF1B796F763D210EFULL, 0xF778883CBADE0732ULL, 
            0x601625A6997DE52FULL, 0xF58F9B3E1A0DEAC8ULL, 0xD8CF654F54A28D48ULL, 0x3AFC9132D5DB9842ULL, 
            0xFC515BC248EE5473ULL, 0x912BC70908D333B7ULL, 0x6E4DDCEDD71B5193ULL, 0xB126845F29936A8AULL, 
            0xAA1B6F24290F7F85ULL, 0x2E684B3C407A135EULL, 0x64C27D47EEEC7A45ULL, 0xEB4834F6DB547F5BULL, 
            0x0EEA9B34ACFCBEB3ULL, 0x77177A00104A79B6ULL, 0xEEDF2F0BC9FBA109ULL, 0x3418DFD28B487C7CULL, 
            0x0C76E3EC2D7505F3ULL, 0xB941341AD946D7DFULL, 0x7676C1723ADFDD33ULL, 0xD990E5452BE8D53CULL
        },
        {
            0x3A2F4B6158533CF9ULL, 0x13869489D7CBEB1BULL, 0xC57523BBBCA4CEEFULL, 0x6334D0C33B414186ULL, 
            0x92A810A6DE07E11AULL, 0x23D3595894D68001ULL, 0xCB70E466EA65290CULL, 0x7F6DC6DCA1FFF83EULL, 
            0xB6155C103B456B0BULL, 0x713101E2AA4F7B63ULL, 0xB3A12BCDC3E2F551ULL, 0x6094CC704B8C6BD9ULL, 
            0x354FA7C2C283F88BULL, 0xCA5E8B4A364D6E7DULL, 0x1551D6A9C38B908CULL, 0xB41916C584F0F6FBULL, 
            0x511FF2AB4871D1DCULL, 0x3EA001D9AFFDFF7AULL, 0xDD81C573495032E3ULL, 0xD2C07CB4DAC10AE2ULL, 
            0x0B97C4156D717E96ULL, 0xA7ABC05E7081F3F7ULL, 0x0A019C8201D28845ULL, 0xCD4F41FB5827B0C3ULL, 
            0xE80F04F3D81C4C5EULL, 0x42971BA067AE321AULL, 0xEA485F8C51575604ULL, 0xF17AD71F7A31ECFBULL, 
            0xC421328E0838ADDAULL, 0xD09BA8A6759699D5ULL, 0xD55391F4B3C25B29ULL, 0x9D89CD58B184FBADULL
        },
        {
            0x00DAC97E0124F921ULL, 0x4073378834F8A757ULL, 0x9A3A947BFDDA162AULL, 0x97D76EF7156F6728ULL, 
            0x8273B7E3BA88AC70ULL, 0x3064D21EC0A3E0F4ULL, 0xC79E622B9ED378BBULL, 0x74C354645783B869ULL, 
            0x830989D8E4358630ULL, 0xAAA1263B899F18E1ULL, 0x9087ABDBBB1B57A8ULL, 0x9FE41ED1635E846EULL, 
            0x99F50AF9F726874FULL, 0xCDEBCE97B5186709ULL, 0x6791B90F7E1A8FB3ULL, 0x1A05533DD052678BULL, 
            0xFD26460603D6E2BEULL, 0x849A85688AC71191ULL, 0x01859C664EC08D13ULL, 0x92AF3E49FBE4DF91ULL, 
            0x663BCA4D089E15F9ULL, 0x3BCE2580652B405FULL, 0xAF0AE70AB00AF7D8ULL, 0x1E6E14ED2987403CULL, 
            0x9ECA56733B3E396EULL, 0x4B15ED6032055C49ULL, 0xE46E33439F328455ULL, 0xB35B6D85EB2D0182ULL, 
            0x9608CF57EF3384BDULL, 0xF32EBE9E92D4CCD4ULL, 0x3D9BA71DF2E8E4B8ULL, 0x7CCAA2D08C16AC33ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseCConstants = {
    0x6FCCD376AB10E16FULL,
    0xD90090A76E3105A4ULL,
    0xAAD2E6CF4FE02332ULL,
    0x6FCCD376AB10E16FULL,
    0xD90090A76E3105A4ULL,
    0xAAD2E6CF4FE02332ULL,
    0x15B54B76C0D7AD66ULL,
    0xDE7BDBD98E517AA2ULL,
    0xB7,
    0x6E,
    0x83,
    0xF3,
    0x5C,
    0x90,
    0x3A,
    0x66
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseDSalts = {
    {
        {
            0xB1BC8B19DA7C7FDAULL, 0x5CA424B9DEAEF25CULL, 0x14EFB1F8259DCB46ULL, 0x066700F3FC19DEFCULL, 
            0x31E17B7B2B8FD7A2ULL, 0x687DFD152E30D190ULL, 0xFD20F051B8298E5CULL, 0x2914D573EDE3F9E0ULL, 
            0xE3EB2E8D975BBCF8ULL, 0x556587CF3990406EULL, 0xA17A99B40E8C7F17ULL, 0x19FFF316B319A829ULL, 
            0xCC35AC824A85C88CULL, 0xEF6BA14D532AAF8EULL, 0xE0BA2BBE471822CDULL, 0x49F8DF30704466B0ULL, 
            0x0DFB0257B9F9AB29ULL, 0xEA3D1D5FABBB4709ULL, 0x80F6886347D701B8ULL, 0x7ABF2FE915120678ULL, 
            0xF66A8953CCE5BD32ULL, 0xC3A5798A1210CA4CULL, 0x57A4E8925DE95529ULL, 0x40724EE6CCF27FDCULL, 
            0x296D3F9BF814383CULL, 0xA284BD9B4C5B916EULL, 0xE7F36FF73987D103ULL, 0x8177E02C9A50707DULL, 
            0x8847159FAD6840F2ULL, 0x0E86C67636D5AAB3ULL, 0x6FCDA5C4EE06914CULL, 0x476523B1728D6521ULL
        },
        {
            0xD18C1139C2E0E61BULL, 0x45EE2058272CA7ECULL, 0xFEAEAE663426B1A5ULL, 0xF02BC91363A586D8ULL, 
            0xA02341A162D6D26CULL, 0xEB907B3496F0EAACULL, 0xE7450D4A4E8D002BULL, 0xF04B5811EF8837DAULL, 
            0x4697DE65191DAAB7ULL, 0x78F1BF7F5147F47FULL, 0x7FA1FF05403CE0BDULL, 0x38DD2851E31F4116ULL, 
            0x595FE74B624B41A6ULL, 0xA97EE2AF2B7644B2ULL, 0x868C758FD7CA64A6ULL, 0xB8FAD53FEE358B63ULL, 
            0x78EA7EDF88B31BF0ULL, 0x4A5918E0F7243008ULL, 0x51C5EEB77EE11FC4ULL, 0xCF3EDFC97DFF34DCULL, 
            0x9D7CC012DCF2D01DULL, 0xBC919B6C02F0DEACULL, 0x89E26477A57F35D6ULL, 0xF306ADA974F220E4ULL, 
            0xFC9B890966C1DECEULL, 0x86119321141FCBB8ULL, 0x65231E0727A22ED9ULL, 0x2AFA437B32FF06EAULL, 
            0xDF887C9FF1329218ULL, 0xD9F3768931A728E1ULL, 0xC94C12EBA81D08EDULL, 0xE98A8A127EE2F613ULL
        },
        {
            0xBD20272C842B32DFULL, 0x3DA3A1EC334DB4CAULL, 0x266909322F6EB7A8ULL, 0x62EC351BCF85F48FULL, 
            0x72183C2612976056ULL, 0xB940D7DAC529D187ULL, 0x12C57BD9346F6F73ULL, 0x4442C6CABC2783E2ULL, 
            0x6FBC370A2B351874ULL, 0xB01FA2C89382454AULL, 0xF4D6E714E724D832ULL, 0x9BA5F5CB73EA381FULL, 
            0xE50542AF1B40650AULL, 0x4F86D8D79AAB934AULL, 0xB9E68FA470BB52CEULL, 0xC447E5769E4FFE0AULL, 
            0x22D7D84349672152ULL, 0xAB07EC9971718387ULL, 0x4A5667577A3867C8ULL, 0xBEA1CC584669726AULL, 
            0xB8AF0B9FA4870437ULL, 0x2564FF2E0DBA10BBULL, 0xB377385FF7162649ULL, 0xD6571B46F2DD54B1ULL, 
            0x30F4CC9258D50503ULL, 0xA9F0F73BBF8B5ED2ULL, 0x4E9EDC3C45BCCD62ULL, 0x61D0E4CD1ED19014ULL, 
            0x83F8CFCC1BA71906ULL, 0x17D6EEE5BC8EA0D2ULL, 0xF179A9C9B6743C5FULL, 0x99C1D93A1B94DAABULL
        },
        {
            0x9F12DF61FA570B10ULL, 0x90FCF8F9233FC83AULL, 0x995B1F1BBD8A7145ULL, 0x059EE5D53C5362EBULL, 
            0x56446DF953C33473ULL, 0x994375F8C34463A2ULL, 0x9EC63A098FB1AE72ULL, 0xE861BFA564C190F8ULL, 
            0x61B189801BE0B5C2ULL, 0x067741E12CEB3CC0ULL, 0x9F6EBF162757D6C9ULL, 0x0B740383A473A7C0ULL, 
            0xCE0DC31F2585DBE3ULL, 0x40656AA761BDD59CULL, 0x130AC4F842829E72ULL, 0x2B43483EA157F62CULL, 
            0xBBDBB7F889C93E06ULL, 0xDDA77C6C00DAFC72ULL, 0x0B5AF6061712064FULL, 0x29B407455D72668DULL, 
            0x92FFDDC206E50CBEULL, 0x2D582CF125DF1D2DULL, 0x74405CBE45EDCBDBULL, 0xE44A562C460F8C9FULL, 
            0x6CE1D3424AB42551ULL, 0xB8CF0EF213BA9BD1ULL, 0x4DF7104566B79DC0ULL, 0x68A15AE0541D1B95ULL, 
            0x22EAFFEB2F73309DULL, 0x6B8679B2ECA54180ULL, 0x27A9873CED7A9008ULL, 0x87DADD3BED6B6ACAULL
        },
        {
            0x21DEE248D4A22E58ULL, 0x7AED23CE43CEEA08ULL, 0x15F7D47055DCBB89ULL, 0xB3BD54557CDA5AC4ULL, 
            0xEBF9B6BB182B3D99ULL, 0x5F63FA993AAC9F7BULL, 0x6477E3BF102921AEULL, 0x8BF9517336A56830ULL, 
            0x94E40030BC2A303FULL, 0x907AEEC3B40262ABULL, 0x2205820B31B7AC9EULL, 0x7F9ADEE888986353ULL, 
            0x52DFC08D20606C36ULL, 0xFA0815DF159B7077ULL, 0x90B24475DAD5FB50ULL, 0x7016DA4A171E64DDULL, 
            0x373E77BA23137AA5ULL, 0x444588CC80C8BF08ULL, 0xB7362ADAB82D4C9FULL, 0x2E7E9AEF80761AF6ULL, 
            0xB7BC09D95D99B616ULL, 0x6E5407C6E89C6AACULL, 0xDAEE301F7FA0729DULL, 0x335AE6C663AD9DB2ULL, 
            0x9610CE691CF24CB1ULL, 0x88EA1DA5898D3E2EULL, 0x34206705CA32AD64ULL, 0x11053A8EFB96A79DULL, 
            0xD2F9085EFD9ACF06ULL, 0xEDC16FFC40631C13ULL, 0x3C159DE83993BA3DULL, 0xAC2400BFDF3A53CCULL
        },
        {
            0x7463F8A871154E8FULL, 0x91B2DA2B9F9F5842ULL, 0xCEFFB6744656EE11ULL, 0xE689277A3A86AC0EULL, 
            0xB56893B826AE842BULL, 0x2B96507A14E47658ULL, 0xAC636DF677DC9EE0ULL, 0xAE4448839D7EEE26ULL, 
            0xCE9EA89EB9774E12ULL, 0xF52F82837C705FF9ULL, 0xC67382D6C21C9BDFULL, 0x6A4E1EE8E38E1C9CULL, 
            0x08387689B8010D3CULL, 0xED54AAD14CE0D3D0ULL, 0x8C78F3D0B92F8F30ULL, 0x499514A925AE4AD6ULL, 
            0x62636C2051BC310CULL, 0xF9392CDA98E8ABD7ULL, 0x0840E8996B56438FULL, 0xC645777302CA15F3ULL, 
            0xFC6CAC40442B0FE6ULL, 0x2925725CFFA9E1EFULL, 0x2600B323BA050A11ULL, 0x80287DD6B31CC882ULL, 
            0x94B29EB8ACE68667ULL, 0x10D7BA4B70776ED3ULL, 0x2A6B476DC8CAF9BBULL, 0x1B6D54EAC7B1BC21ULL, 
            0xC052ABAF72A79C61ULL, 0xEF764C9E47A3A8BDULL, 0xC206024C694E53FFULL, 0x9741B1FC941B17ABULL
        }
    },
    {
        {
            0x94D679BC4BF03DF3ULL, 0xA30198BFEE20FA1FULL, 0x6234EA997F38C785ULL, 0x464ED5FB7256DE98ULL, 
            0xE6CA11329F0567F5ULL, 0x6E6B10F0BB44DF8BULL, 0xC23AA820DD436F43ULL, 0x647FEA41E6436B22ULL, 
            0xD5B31FE91012553DULL, 0x16118E0B7994E1DFULL, 0xEFDCD74BD67EA8E3ULL, 0x78F3B373872B1803ULL, 
            0xDA8A806BA465D4DEULL, 0xFF90CD2809CB93CCULL, 0xE216B1A247253C15ULL, 0xDD4E66F0340341F0ULL, 
            0x2A55646EB8430BE4ULL, 0x9BC7ECB7C6774741ULL, 0xA62C2CD24F4C24BDULL, 0xFB01F5A51C223231ULL, 
            0x39C9CF4552F6898CULL, 0x950D6E1D1F836BB5ULL, 0xEA188CE34F35EB95ULL, 0xC9E67E41C12CF0A8ULL, 
            0x3F46905877371FAFULL, 0x1644F1D3E956C6D1ULL, 0xFEB8AFBD9297ACFFULL, 0xFCA22DB016013509ULL, 
            0x0A04764B4DC3C169ULL, 0xC1CE77B2C720E2B1ULL, 0x6620A82810970C3BULL, 0xEC644554F973853DULL
        },
        {
            0xA4993849209B1D0FULL, 0xD17790F64D6FD585ULL, 0xE236FBE32AEBD44CULL, 0xF11260D932C56C20ULL, 
            0xCD150EFC4490903FULL, 0xC0A17F39F48CF1B5ULL, 0x59B6BBB80226388AULL, 0x1D4A525C4415E924ULL, 
            0x034F1CCC95CCAC1BULL, 0x5F5A5A92062E44B4ULL, 0xA29A82452582FF20ULL, 0x916ED7C762FFAD3FULL, 
            0xFDC705ED850D1FE4ULL, 0x0DE87634FC89E071ULL, 0x58EBCFB21F5FDA86ULL, 0x66552E7F522BF7C0ULL, 
            0x0A50B96913047199ULL, 0xFDD8CF03C88C44FDULL, 0xC6A7F3183C5F0CF0ULL, 0x462537258B3AA974ULL, 
            0xFAC9D78EDDB505E9ULL, 0xEEC70F7EA70DBE44ULL, 0x5FDB6240813E3401ULL, 0x99851581D070ADF6ULL, 
            0x7DF6A1869F556944ULL, 0xECC15F637BBE0D10ULL, 0x02039FC7D84EF1DEULL, 0xD9858B222C931EFAULL, 
            0xEE0707EC997D2D56ULL, 0x140784AD2CE61C96ULL, 0xDB25F1C5FF019277ULL, 0xE713A234E66CBCB9ULL
        },
        {
            0x720430AE1C86F6AAULL, 0xB2EC60EBC0C6B158ULL, 0xDF1280C39309234CULL, 0x7B1C4C1AA6ACE688ULL, 
            0xA48420C128804EF4ULL, 0x8FC8B1B70A4E2FAFULL, 0xD2FBCDD55D826BBCULL, 0x7FF0911306926864ULL, 
            0xFCF17916C53AD633ULL, 0x65BD24F655B40E79ULL, 0x642C9406F9CED18BULL, 0x5C542AB89E14C601ULL, 
            0xD575FC1C4DE4C560ULL, 0xF02A2BD659B5FEB9ULL, 0xE26F53A1564AE948ULL, 0x9A4BE65DD23D3C60ULL, 
            0x085BF9ECC581BE3FULL, 0x61E53E9CD5B20896ULL, 0xBA45E00F9B7E0522ULL, 0x6EBD87F374B59AF4ULL, 
            0x3F4236E3CA37A4ADULL, 0x1E240004120B6835ULL, 0x2465AB5DBAB79FF4ULL, 0xA6D4969F637FBC3BULL, 
            0x3CC53C02D49E7E24ULL, 0x18E11E6E97C7EC61ULL, 0x0DFA5BF5D855343AULL, 0xF2471EB5CEE1A9D6ULL, 
            0xC68EA382D64244DEULL, 0x885F99486D5B8B2BULL, 0x22DDC50EF519EEA2ULL, 0x25FF1D8860930A11ULL
        },
        {
            0xEAD3F2A697694CF2ULL, 0xD5CAFA4B72355922ULL, 0x10554166E3D9C7FEULL, 0xF11853E0134F15B9ULL, 
            0x3B2D472EB7F95B5FULL, 0x33AF9EE445227B53ULL, 0xC30C03A911178CD7ULL, 0x0D2B6B82713353F5ULL, 
            0x675D5348C004AC3BULL, 0x7A7E2BEF000FD4E5ULL, 0x651ED61C67F66DFFULL, 0x141450D3E03D56B6ULL, 
            0x9A38A30FFC3C26BBULL, 0x03FB143A5CB0F718ULL, 0x35142FFB2289E981ULL, 0x010198C911879B0FULL, 
            0x947BFA77E793BAECULL, 0x67A163FA8CB03387ULL, 0x474F2F0AD6462E25ULL, 0x5FDAF6BDC64045BAULL, 
            0x2B0FE937B14F99D4ULL, 0xBFE013A50B663BC4ULL, 0x0B3ECF6C828D1394ULL, 0xF1650D113BE73EB8ULL, 
            0x02C6D2C4147E8C0EULL, 0x5558DCB5C20CADF3ULL, 0x0E1595164E4076A4ULL, 0xA2A99D72521FAD09ULL, 
            0x6CEEEB51211E5F02ULL, 0x4066A5A21F75D837ULL, 0x9FBB4CE3A9FA2F3FULL, 0x30530CA2B38BE12FULL
        },
        {
            0x5899CA927FF85A12ULL, 0xEEF914E8A0F73F4FULL, 0xDD5D3FF367A34515ULL, 0x82BB7A74038DF019ULL, 
            0x6B86E57CB2692753ULL, 0x00D249E200940759ULL, 0x4706979C9B68B887ULL, 0x33AE3F32151B8867ULL, 
            0xA3A56D707A0AC230ULL, 0x38C4F191B58A76E7ULL, 0xAF2919F2B904AC06ULL, 0x29639D32D2599F83ULL, 
            0xD784251EF8738399ULL, 0x560D9558D698BB5CULL, 0xB7E00786596ECDEFULL, 0xDFE2D43F78D304A0ULL, 
            0x08E6DF9513AFB51BULL, 0xE0826E776C599B1CULL, 0xC158BC2325BC5ECDULL, 0x38F6A45CBB7090FBULL, 
            0x04D626A37F991702ULL, 0x0E056B91E8CA0F92ULL, 0xD3107127E18AECE7ULL, 0x03F0B0E88D98F1AFULL, 
            0x874BA18E84C63CC2ULL, 0x05B3C495F109D008ULL, 0xB502FB35125C8C0EULL, 0xC4B204A595D1E96DULL, 
            0x98C8B6D894D881D8ULL, 0xB2003FB6D9442942ULL, 0xF7966A74B6B84F1AULL, 0x0D5F2EBCDF31B35DULL
        },
        {
            0xCBFF6B891029565CULL, 0x2C6D22374184D4A0ULL, 0x3C85B6ED6AF4E7A8ULL, 0xD1E974F447AB1C2FULL, 
            0xD09673326C0D42DFULL, 0xD79055AB83EE26DBULL, 0x284A348AB7508A4CULL, 0x63E473CC0185E2C2ULL, 
            0x54547A933F786124ULL, 0x32CD9C8D37C3046BULL, 0x7F86FDC90C0770B9ULL, 0x5B4E2B3992521E7BULL, 
            0x26D2E24FD9B3774CULL, 0x16CC53B04D0E9F80ULL, 0x1D03D10A33DE53FCULL, 0xEB9568F93FBCB398ULL, 
            0xDB4ACB199E983753ULL, 0xAC5F613B68186DCFULL, 0xF80E8F7ECA4EF315ULL, 0xE4A237C47D869AECULL, 
            0x0BB729F28BA03408ULL, 0x455AAFFF83E29CFCULL, 0x5D1768502074FE9FULL, 0xC84A2A1FE27DBA63ULL, 
            0x6050E527CF6FC95AULL, 0xF1C579494C55B75CULL, 0xFD9CA9605C48F871ULL, 0xE260E0F5B54CD2AFULL, 
            0x28C265C9346D091CULL, 0x4C738D1C2C2E194BULL, 0x8504654EC69803E8ULL, 0xFD6BDDAC62342361ULL
        }
    },
    {
        {
            0x90C447B78148CAA6ULL, 0xEAFF408B29D44DA1ULL, 0xEAA99409892CB399ULL, 0xBFD4A3955F61B63EULL, 
            0xDB80B360C0C24952ULL, 0x8AD42A12C41BA1DDULL, 0x1A3499BC7025F64FULL, 0x63369620B654B22EULL, 
            0x3CE6294EC54A637AULL, 0x4F2C570EC3B66D5DULL, 0xBCC0D242CB35677DULL, 0x99BD939B81320E10ULL, 
            0x724192DB6B87B71BULL, 0x61999BDF39CA9D1CULL, 0x98307EC76E98EB70ULL, 0xEA3899CB896CBCA6ULL, 
            0x97D4FA61B68210EDULL, 0x1B1F69978C9A511CULL, 0xCEE702E123F014E6ULL, 0x4C75E6189F5DA1CFULL, 
            0x57AC2143F0270D01ULL, 0x2B706B060F23584EULL, 0x5C0F0FF36EB9DF7CULL, 0x72D87B284EDD2F1AULL, 
            0xF4CBE843BA8DCF17ULL, 0x01EB6D00C61B471DULL, 0x78342CEFDA761217ULL, 0xC51604C99A334F45ULL, 
            0x3881E3B1BD5953D9ULL, 0x389486F20783E560ULL, 0x35F0FC0DA8561A97ULL, 0x28CD7195DF1060B8ULL
        },
        {
            0xA94001107910CAB2ULL, 0x7B2E0E7985FC49C8ULL, 0x488761D74EE30B7CULL, 0x567635F1FA4E83D8ULL, 
            0xAE9337A4AF0EA696ULL, 0x74098C9885D5D165ULL, 0x5342B6A1C4E8B4DDULL, 0x67FC54DAEBA72EC7ULL, 
            0xA6D511B1BA94F9D1ULL, 0x75D8914C3D6630CAULL, 0x2F8B931498DF1C00ULL, 0xD0E7F12B2C78D8E7ULL, 
            0xBF19DE999AFD63EFULL, 0xCFBFAD10A3B592EBULL, 0xF93E899AD7492A05ULL, 0x8404B45BC1678D80ULL, 
            0xC36115885CBA5DF3ULL, 0x299BBCB96AA71B91ULL, 0x8A592DF05B1A0F98ULL, 0x8B2FA52AA3F30802ULL, 
            0xAF9D72CB6765610CULL, 0x9C5BE951E75C8327ULL, 0x4EC5CED791F4B984ULL, 0x08C6F2EC6D72719FULL, 
            0xDFD30B585D9B47A8ULL, 0x8A3A1557FFC20985ULL, 0x1BB26EC6615E5CA5ULL, 0xBB97C91F97DAE8AFULL, 
            0xBD63F03698E4FCBEULL, 0x391B23FFD69F1411ULL, 0x17A85FF7F1A42A5FULL, 0xDD3C154247A4C721ULL
        },
        {
            0x454F44A6A7EB3922ULL, 0x4381D30F9DE05D95ULL, 0xCBEA7EC21332E042ULL, 0x6C1CF15B6403DCECULL, 
            0x5316100FB592A710ULL, 0x3A04756219CB061CULL, 0xB3BAB97C0BAB4DAFULL, 0x3E9E8A347BEB5899ULL, 
            0x411F617C6A39FE09ULL, 0xA0A4FE05C7CD9461ULL, 0xCC19152B9730D672ULL, 0xE590A5C35EF9CA8DULL, 
            0xE84FA088FB9B9473ULL, 0x2E7D989BEAFC2BF0ULL, 0x5136842C40793A1DULL, 0x9A5AAE23F835BB15ULL, 
            0x06A5F22C63EF127BULL, 0x41745318C2F59D51ULL, 0x8A6D24EC431B8547ULL, 0xE3CF3E1DD5F696BAULL, 
            0x39FA6C9A8DBD71DAULL, 0x1D1896A6FCF6CF87ULL, 0xDD34B21A6F85D3D9ULL, 0x43F397B5B16D17ABULL, 
            0xC195207863D66318ULL, 0xB2B3E1560778BBCFULL, 0xFA99CB7D5F931C97ULL, 0x0FA7C941B71B3423ULL, 
            0xAB7CDE23B59BED26ULL, 0x953A101714E723BEULL, 0xE5BE6C1CAE556A7CULL, 0x118F3D8964CB94C1ULL
        },
        {
            0x5EF857AC0D611747ULL, 0x73E39AB6D2528D4BULL, 0x3B64602E193422FDULL, 0x7D8E75BE42063A4AULL, 
            0x19932859067CC30CULL, 0x10634C731613E3DEULL, 0x8B9CBC154B2FE4C3ULL, 0x6739BEF89BA68A98ULL, 
            0x50DC7A4B03C314F2ULL, 0xFB8857BADB0FB920ULL, 0x069B10022B8479F8ULL, 0xF63B4613813E81D9ULL, 
            0x061F147036A70DCCULL, 0x354BB9456A648DFAULL, 0x62806495A3711239ULL, 0x99E0F8E2D29C9196ULL, 
            0x2997EF59E4A719AEULL, 0x9ECCC41F061368E3ULL, 0x19D98549FB94BDAFULL, 0xA4129104C32DD250ULL, 
            0xC8DB281D88117AE2ULL, 0x7E3F8010EB034EF6ULL, 0x4238843EE8736F96ULL, 0x251C9FA83549FC52ULL, 
            0x08380DE6CECABF57ULL, 0xA9C4C680273F5ECEULL, 0x52669FE8FE50005AULL, 0xF0961DFE69C71974ULL, 
            0xF3FE341448D8BC96ULL, 0x44E9EC93A0C10813ULL, 0x1A22A34448FBCB52ULL, 0x99643F1B2FE3E17EULL
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
            0x2730C9146632A44EULL, 0x8678621E299A26D5ULL, 0x2D5D161C76291FC3ULL, 0xDF825FEB7724781AULL, 
            0xC71CB4CAAAAF6852ULL, 0x131767855963A72EULL, 0xB57006CD1FF69B95ULL, 0x1ADBC80D48977486ULL, 
            0xEAEEAE0DEF89820DULL, 0xAEAF4B3E016A2070ULL, 0xB13A7BBAAAE96021ULL, 0x72B73DB51F57E259ULL, 
            0xC299ACB9C80E5B3BULL, 0x444A564785479570ULL, 0x19E43B93A08D0826ULL, 0xE5BDCFA486AC0B6AULL, 
            0x44E54CEEC2F70F3FULL, 0x2D9A8473B6A6CD32ULL, 0x0A540A049385BB15ULL, 0x804084F01CE0F9C3ULL, 
            0xDB4807C82825D69DULL, 0xDED45EE537996439ULL, 0xFEB9D1DCD5D0330AULL, 0x633398C1EEFBF164ULL, 
            0xB98AACBE90EA1E3BULL, 0x06B2518D45CD97F0ULL, 0xABE21927E76D903CULL, 0x10EE14D849358CA1ULL, 
            0x82C30325590EE2FCULL, 0x36E1820D6E456990ULL, 0x9B3FE38EBFAFA36BULL, 0x2C1C088EEA67D2D5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseDConstants = {
    0x4E96E3266000D771ULL,
    0x27E246ED16BAAD5CULL,
    0x1BA6A72AA03F9C34ULL,
    0x4E96E3266000D771ULL,
    0x27E246ED16BAAD5CULL,
    0x1BA6A72AA03F9C34ULL,
    0x2087F97E55B93F00ULL,
    0x5B40DD355B692EB7ULL,
    0x1C,
    0x17,
    0xE5,
    0xDE,
    0x0D,
    0x4A,
    0xBC,
    0xB1
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseESalts = {
    {
        {
            0xF5A5598FCF92E247ULL, 0xBB729035F0A5FF56ULL, 0xB6CF367ACAA7D1D6ULL, 0x630DB3A7A2C5881CULL, 
            0x3C13741DB5325BCAULL, 0x415E89A9FE0DDE5AULL, 0xE7595C46D3D5F6F6ULL, 0x68452867891F0E7AULL, 
            0x26248096734BA507ULL, 0x0A6802B8E4DF10CDULL, 0xA7C3949B445314A1ULL, 0xE60D0C33D2A34A38ULL, 
            0x5AE23FB1573B2D4AULL, 0x393AE12DEFD45CBDULL, 0xDD445527652205EBULL, 0xAFC826FF33D77617ULL, 
            0x4DA708520885B488ULL, 0xC313FCB85A320C23ULL, 0xC11D588063276960ULL, 0x9DE5DAC065926422ULL, 
            0xCBC9616BB0D45233ULL, 0x3CD4AD3910F5DFAFULL, 0xDAC9694965C8611DULL, 0x857C910F94B1FFFDULL, 
            0xFA69D6EAFC55E31FULL, 0x8BF6C4B55DAEDCEAULL, 0xDE730B2BA74154C8ULL, 0xAF98572913323100ULL, 
            0xAC118DE3BAEC8E61ULL, 0x670C729FB0ADD676ULL, 0x0BA218B55A13CF76ULL, 0x039FE0DC6F53A65BULL
        },
        {
            0x6FE3C01F5B3EA0B9ULL, 0x2FAA3B8444D51B63ULL, 0x26EBCFF0D1A87A9AULL, 0xEE6FC9078A300D95ULL, 
            0x15BF6FAD9339E52DULL, 0xA5B9D4D48D2F8797ULL, 0x239989F90217E500ULL, 0x9C1D2E4DBF747DC6ULL, 
            0x8BDC4104851419FFULL, 0xFA9F24AD1B320AA5ULL, 0x6077599FBA30FE76ULL, 0xA90992D32BE20648ULL, 
            0x52128B0161AE9980ULL, 0x6766BB64CFB2E1F1ULL, 0x94C716C2E9404BD2ULL, 0x12CC00B76D158E54ULL, 
            0xA431E1D5FCB100E9ULL, 0xD131525A7D7F02D0ULL, 0xFD1CEF48890F2F5AULL, 0xBFC8A67046DD7D87ULL, 
            0xA094689AEF6FDC00ULL, 0x1F30FF2E9EB9D28FULL, 0xB9A2989534F5E30BULL, 0x7B9F838B44099EA0ULL, 
            0x18282B4426B9905EULL, 0x445497061A0BA745ULL, 0x46C2BA3B1E9F2002ULL, 0xD27F80EDFE2B8C0CULL, 
            0x9E076040282074BDULL, 0xCE8BFF8C75327431ULL, 0x60F3AEDFB239FE95ULL, 0x779B8CD0A1CAB764ULL
        },
        {
            0x1034A64E9AD73DE9ULL, 0xEC08F6F3240DC25CULL, 0xCC453F2E24473F1FULL, 0x87ECE0BF2C61A7F3ULL, 
            0x3EF012E9760DE6B6ULL, 0x57DAF4687D19ACA8ULL, 0x5A020B92C855771EULL, 0xE53CF8C52613655DULL, 
            0x8F2FA0BD648735B9ULL, 0x52FB5E00826218F6ULL, 0x9EB68B3642618475ULL, 0xAC4984C2CD193460ULL, 
            0x86A51B9282879584ULL, 0x6E3DF3F5FC81E1E7ULL, 0x90F6A393D20D38C2ULL, 0x80D2E75952FE9974ULL, 
            0x490615400892B463ULL, 0x789049C8DF54CFECULL, 0x37272B03DD608398ULL, 0x33B811BB3C46B663ULL, 
            0x8112CC5FB33268E2ULL, 0xF1BFDBB8F087C8DBULL, 0xD7C57242D7FDAEA9ULL, 0x713EAB232AC65847ULL, 
            0x9F285F147E38EF4EULL, 0xDC239E0599B902D4ULL, 0x4806CF96D7DB8FF5ULL, 0xACC3B94CEAE8434CULL, 
            0x9F7D8E3A30FCB999ULL, 0x5378E5F400F17716ULL, 0x2531E1CC2BDD08F0ULL, 0xFFB92D8DECCFF14BULL
        },
        {
            0x76BCF758849C62C1ULL, 0xD0B11BCD80DB1A70ULL, 0xAAF544C5C9063584ULL, 0xC577728C1E1F6DA4ULL, 
            0x4434D742C66F4529ULL, 0xEF49E149EF883682ULL, 0xF4D5068CCAB368DBULL, 0x523C656F7DF8A980ULL, 
            0x2DC3D45EE4A2092AULL, 0xD103AD4A612814EAULL, 0xB5FCEED123990273ULL, 0x849F23EBF23C72EEULL, 
            0xD578DFF51D347B78ULL, 0x9A344C14B0756354ULL, 0xBCDEAD69E5D5EB2BULL, 0x2114304E11527FB4ULL, 
            0x9C962CD744561227ULL, 0x13767A4CFB59E881ULL, 0x288E77676EA353DAULL, 0x227DBA72B0A56F48ULL, 
            0x8608DCC51EC61D15ULL, 0x1A1C9DC07BA68FEEULL, 0x479B10F05EB1D177ULL, 0x95B8B75D80D91541ULL, 
            0x808ED577EB528D0BULL, 0xCA9595AB03261EE9ULL, 0x4AFDC43C9306A855ULL, 0xE1C4842F89C66549ULL, 
            0x7B357A4ABBD2AA3BULL, 0x8C4BDA12E7104D26ULL, 0x6908A1329A2305E8ULL, 0x15A46EFB66B7FB7FULL
        },
        {
            0x3F7170F6EA6D3E13ULL, 0xC15DD153BAFD7CCFULL, 0x8E96196F77414CA6ULL, 0x7DEB07F671F9EE02ULL, 
            0xA500A94F13EA88CFULL, 0x052536702CE301A2ULL, 0x4765B0440713D369ULL, 0xEBE33CA7D5B2A346ULL, 
            0x5832A295C1CE9CD3ULL, 0x378B1A94CB4E0C04ULL, 0xEEA2E18013F8FC84ULL, 0x9DD994916EB3E891ULL, 
            0x30075C6B564859C5ULL, 0x543A300DF1FC4CD5ULL, 0x0841DAF85A357631ULL, 0xAB35D37B2BE52661ULL, 
            0x4BD836FE1F03D408ULL, 0x6576A8B8B4E10BA1ULL, 0x63EADA0EA095CAFFULL, 0xF5DD3E333F105656ULL, 
            0x98A26546CE6A32EAULL, 0x9AE1CAD9DE2DEAA1ULL, 0xF4C4CDFA6EB16A83ULL, 0x329B1C2156A62DF2ULL, 
            0x84E1D351EF616517ULL, 0x47499E6A5BA8CE53ULL, 0x674AB61B1EFB61B8ULL, 0x9078E9C573B17BAEULL, 
            0xEE42DC6CEDF3EB07ULL, 0x7AA19D7A11361D55ULL, 0x211017E179BA43AFULL, 0x9860A98E31E73060ULL
        },
        {
            0x6054C32CDFF53601ULL, 0x9A072BA8220C2233ULL, 0x613EEB65D07BA3A2ULL, 0x104ACCA531984D03ULL, 
            0x715920AD321FFBD1ULL, 0x97FD30A1E077C040ULL, 0x6EAB568F190A2836ULL, 0x70E0BBDD079E87C5ULL, 
            0x37E781755335458CULL, 0xACA6D0267BAF3CF4ULL, 0x0F8635A737228728ULL, 0x311638AAAC808BC2ULL, 
            0xF7197493984B9E76ULL, 0xCFA59CD48FF824CCULL, 0x567A97FAE09D9AEDULL, 0xAD2CBCB6FA8F883CULL, 
            0xB7BB9F8C6C2C368BULL, 0xD06DE81D700E9692ULL, 0x17B1121096DD913AULL, 0x7782F3F5F987B71CULL, 
            0xC647EDA4810966F2ULL, 0x2DF87C55CCE6200DULL, 0xD3BDFFDF29DF2535ULL, 0xA98D67B929A80DAFULL, 
            0x4C73B237D24D531BULL, 0x22B1BCFC31284524ULL, 0xC595DBB72FE599A7ULL, 0x0A4F9F4A4C7D9B74ULL, 
            0x5FC170DE5F8959EDULL, 0x469B00C178A2900AULL, 0xD7624BAF86CD994AULL, 0x18CC6C3CBF2CE752ULL
        }
    },
    {
        {
            0x348D0C441BAE06A8ULL, 0x57A022DB6740FCB8ULL, 0x085492A070626850ULL, 0xDF7738AD8A1230E8ULL, 
            0x3049E7D0D39A3DB4ULL, 0x58E0F861D6FC66CFULL, 0x7F72AF2B248DE9E8ULL, 0xE679CBFB51DD5EE8ULL, 
            0x01DC655519EC6D91ULL, 0x26CD0A32EB27FAF5ULL, 0xDFE51BA05DFB6293ULL, 0xADD7C075BF3651F4ULL, 
            0xEDF2EE3C4CC41EFFULL, 0x6B37032DB1C624F7ULL, 0xA1CEFE971F1F5F9DULL, 0x5D8010EFF787F144ULL, 
            0xD19C9D8715C05942ULL, 0xD324919D86BFC33FULL, 0x8EF9A28A9F3FC9C8ULL, 0x48D96BC0AD541D56ULL, 
            0xCEE008C8847DAB99ULL, 0x14CF2304EFD74E3FULL, 0x29097996B6BF53ACULL, 0x4DF5DA638A646F07ULL, 
            0x9F82F438E3E7FED3ULL, 0xAE3BC79B1614A66EULL, 0x43DE07FEC56678B2ULL, 0x436B996B3C709BF9ULL, 
            0xDAB17DD3F6F19D56ULL, 0x9B6B5988294B16B1ULL, 0x8668EEC1B768FF34ULL, 0x78440E949A2B92C1ULL
        },
        {
            0x559FE9F885DF3228ULL, 0x5DEF7A899814EEC3ULL, 0x8FB6E2BE944F1BE8ULL, 0xAC94E17A376EF053ULL, 
            0xEF22AD1D521572A4ULL, 0xC0CFFA4FB4945522ULL, 0x69B9CC9C02E6B653ULL, 0xB668B736ABA0566FULL, 
            0x2A91D255B35D9475ULL, 0x7DB9DFC04418FEFDULL, 0xDB66791B05065FC7ULL, 0xA8601719A85BCFA5ULL, 
            0x2802BF030017CA7DULL, 0x4EC118588B65D36EULL, 0x4E832A3485A7BABCULL, 0xA13D2E5E81DFC0D5ULL, 
            0xB1161218B7F319FDULL, 0xF0ED5E465C6FA3EAULL, 0xB049FC32E37B5777ULL, 0xDF9CCFCF5DB5DED7ULL, 
            0xCF9A9E50A75E5780ULL, 0x2EBF908055629C4BULL, 0x14D5E9D6A5256464ULL, 0x2C574246D21B3B78ULL, 
            0x49B4044547A9B989ULL, 0x1F4A73F23BC60F9EULL, 0x927180FBCB83B4C9ULL, 0x67A6EA041D3CAFBDULL, 
            0x1D55E6C0CD37A707ULL, 0x7EC3CFE62CF2E3D2ULL, 0x4B7AEF94A79A1B95ULL, 0xDDEAB9D8A4CC9293ULL
        },
        {
            0x038637B9D612A56EULL, 0x2E7DC8FA06765905ULL, 0x8018AB8D2FE880D9ULL, 0x9E5B1BA0CF66427BULL, 
            0x05713D68913BA411ULL, 0xABCED4CB082237A1ULL, 0x3D2524ED032B1604ULL, 0x19F01093FC9C0DD8ULL, 
            0x9E5FA425D63E921AULL, 0xFAED777CCBFE769BULL, 0x1713025DFCDF113DULL, 0x0AC63B8CC4B75BA6ULL, 
            0x0BFEBCF157377D64ULL, 0xF33EA4F77324815DULL, 0x2C12D4D9007840BBULL, 0x2E19705976511E11ULL, 
            0x71C129737BCA1982ULL, 0x577CE609732EF584ULL, 0x4E8341CAB55D5BF9ULL, 0x9BA18BD8C88FCCFAULL, 
            0x1C345EC400E77510ULL, 0x7BA0D2A4F6C83677ULL, 0xE5C067723A4D6571ULL, 0xDD7C17A24F1815BAULL, 
            0x0B91D349F6DAF3EFULL, 0x6EEB983735BC2054ULL, 0xD200A3E7D145E2C5ULL, 0x8638CD74FD8FCB0FULL, 
            0xA1AADBC7B5360C98ULL, 0xF4F0703E1C976BE0ULL, 0xF4B88D73851AF2DAULL, 0xF7E59F08449851F7ULL
        },
        {
            0x2DF4B0EEB9D456F5ULL, 0xEBF9047C4699EB54ULL, 0x118C6828A744FA59ULL, 0x604D64A905E014BAULL, 
            0xFAD43A4ABEA2668EULL, 0x51D76224FA38BC12ULL, 0x6E6D72402B8ECB07ULL, 0x8B0B845FA6F4DDDFULL, 
            0x1F85162422BA9BEBULL, 0x23029C0644D0DA0FULL, 0x1D9260D11711CC6FULL, 0xEA8AEAB58D5FE926ULL, 
            0xD5795019ADAA5A49ULL, 0x50C2B0C8F73DA08CULL, 0x39C3097EEF353357ULL, 0x327734B3E848183FULL, 
            0x856BAA94FD06C9A1ULL, 0x0C91B6785EF479DFULL, 0xAC477CA6060CE3D8ULL, 0x21B855D5B0289DD0ULL, 
            0x3C8C83D6EC926EB5ULL, 0x21E3890314FE7E93ULL, 0x277D9F79190E840EULL, 0x7076D3CA1F041DDAULL, 
            0x980BEF505D940268ULL, 0x1D23710EC49625D9ULL, 0x647195E1015F3400ULL, 0x1408A966C285737FULL, 
            0xFA876BD22FFE7948ULL, 0xA1E8D11C7CC0BFC2ULL, 0xBC82876E6C5070BBULL, 0x56EBE42911DAEA74ULL
        },
        {
            0x031F88CB40CD81B9ULL, 0x692CCA6BBFA733A1ULL, 0xC7791F13FAFB18E2ULL, 0xE9A29CA1905FE3B6ULL, 
            0xE2D384CFB6EEF0A4ULL, 0x89CED3BBFCF69FADULL, 0x0A0B482F5EA84612ULL, 0xA88C31A3C8428613ULL, 
            0xACD692AD3CE1C1A5ULL, 0x7DFD34A64E6AC86DULL, 0xBE57D6BD60B02E02ULL, 0x25968695BA05BFA1ULL, 
            0xB755E01AFDC83DF3ULL, 0xACA904811CE3F476ULL, 0xE0FA314B7CB56B89ULL, 0xB259A5272E4F970BULL, 
            0xA5881CE098174177ULL, 0xDC4626BF76D9D4D4ULL, 0x4E8EF1BD8A6B249FULL, 0xB66B035FF8A4E185ULL, 
            0x6C1827C5BB188641ULL, 0xBABE34E28CB95CC6ULL, 0x969CB273E04730F3ULL, 0xBE3E91C8CD6AB0B8ULL, 
            0x7EE299CD1085E3B5ULL, 0x7C29B77838338129ULL, 0x83F71A5600B0E0BCULL, 0x270617F5F260631BULL, 
            0x804BDF20E1EA6EF0ULL, 0x04E030BE1EC073BCULL, 0xA417033B609245C6ULL, 0x32637889375F5064ULL
        },
        {
            0x279D3ED8C92108E2ULL, 0xF0DDB65D718D6AC2ULL, 0x69B2F84270319E5DULL, 0xE370129174FD9300ULL, 
            0xE066699295ACF948ULL, 0xA669AE94D5B33A40ULL, 0xC3F6EA3244B7C269ULL, 0xCD4BF414B2E7617BULL, 
            0x04A8340AE692BCE4ULL, 0xDCF2B1277BDC00A4ULL, 0x856C6CD3A26DF8D2ULL, 0xD87C01D63F3F2AB1ULL, 
            0xFE8C26E852B6A254ULL, 0xAD4B4BCC726B7AA1ULL, 0x3FC8A9F96830C8A0ULL, 0x94E18A8427D68CDFULL, 
            0x831B7776A61E3401ULL, 0x92569017F6FCA073ULL, 0x75F39EC0009146DCULL, 0xB9C1A3B5BE3E7A58ULL, 
            0xFF3BAD1522739ADEULL, 0x131915A600E33C64ULL, 0x4F3410954F705B57ULL, 0x0A73AA95AAF4E8F7ULL, 
            0x2C3E6EE970C50ACCULL, 0xD8D0838A9289F17AULL, 0xEC89E80767CA5B43ULL, 0x74B194D5A92251F7ULL, 
            0x22FA0732A08B9E02ULL, 0x5E13D4A6B562A036ULL, 0xC5D0D117255E99B3ULL, 0x0E51C0D01D82932FULL
        }
    },
    {
        {
            0x3FE2F02D20D6590BULL, 0xEFC390980A001BFAULL, 0x794310A3D24712DCULL, 0x7AAE3B350B9311A5ULL, 
            0xAF0EBA6CCAAF7246ULL, 0x110DC924EE5E5C7FULL, 0xCD8D1C7CD9FDE7E8ULL, 0x55A4BE89EAEB008AULL, 
            0xFA2D25CB9EE640B7ULL, 0x4CB559AADDDB69CBULL, 0xE65520806E5C3162ULL, 0x4DA0C920193B1129ULL, 
            0x521843F6A12A56D9ULL, 0xCBA3700F3B1EAC21ULL, 0xCF8ABC9DEA700763ULL, 0xBBC655133487D854ULL, 
            0x33DFDF9BC0B37E05ULL, 0x69C496E8023FA5F8ULL, 0xEF92AA492E049E0EULL, 0xE725D20F30A374FBULL, 
            0xFB4E65AC0C7727B2ULL, 0xF0E87A68D7324343ULL, 0xF8AE694904A85216ULL, 0xC6F2850CB87ADB22ULL, 
            0x74E3721290B3DBFBULL, 0xB5057DBD27C221CBULL, 0x3D8D8E6D15066311ULL, 0xECFC833DF6BBA586ULL, 
            0x66A15B348D93BEF5ULL, 0xF80A9BCFC0BB29B0ULL, 0x12563188F6BC29EBULL, 0xE4D228E8FE6EA9A5ULL
        },
        {
            0x3152A589512CB3E3ULL, 0x382833657B251F95ULL, 0x6901B1A5A8D1A9CCULL, 0xE5A17877F876466FULL, 
            0x45E95F42A4E10712ULL, 0xB6D4FE0E04042697ULL, 0x9073D568E07B70C3ULL, 0xF1EB95BF6D82DA49ULL, 
            0x8EBD87440A6A7562ULL, 0xC1F62BA65EABDE7CULL, 0xDEE4FA5D20E1A1C5ULL, 0x62C47D867C8DC3BDULL, 
            0xD83B5C6178BAC68DULL, 0xFADDAA7D3D832153ULL, 0x2451F406ACE06A75ULL, 0xDB909293164D4BCEULL, 
            0x9DAEA0C5A3DA2D81ULL, 0x47B6B45FF51B2062ULL, 0x11F6CCCEFCBB78FBULL, 0x97503C0EBE70FB2EULL, 
            0x839FAB37A139974BULL, 0xBF3844F8E0D084F4ULL, 0x642ABF6607573A3DULL, 0xFB062D2A166E4022ULL, 
            0x59D443890A2A881FULL, 0xF3965C5C476DF332ULL, 0xC12B61F51404F862ULL, 0x6CCF49E72FBBC5A3ULL, 
            0x2CA2F5DA20EA2A08ULL, 0x4329C393C23052F8ULL, 0x5CF2C60B98AA5913ULL, 0x20D9E31B575A201DULL
        },
        {
            0x72F37D802CB02FCCULL, 0x53FDADAEA21C3E58ULL, 0xF4EFFD1749DB42A9ULL, 0xEC3CFA2715759ACAULL, 
            0xAA2BAC0092E425DDULL, 0xD49557C8DA6AFB8EULL, 0xBE03B1AADB7B8787ULL, 0x0192B07DB2C7499AULL, 
            0xEE6BF249914C0F27ULL, 0x501A973828BA0D12ULL, 0x5AFE16AE49C042C5ULL, 0x35EDE629D86330D8ULL, 
            0xE9E266AE8E869EDDULL, 0xC540AA588D5C6912ULL, 0x8CDC70150308CDF1ULL, 0xDC180CBF5885924BULL, 
            0x92647F8A4A3A8E67ULL, 0x47E9C453CED749BAULL, 0x99779B3E4E8E0027ULL, 0xC90E6E7F9B622095ULL, 
            0xFCC9F2ABE7F4368AULL, 0xE487103AD497D2B4ULL, 0x9BCBA9128DDC373FULL, 0x69BB6119CE8B6375ULL, 
            0x085EDDD560D40805ULL, 0x38EC1B3491CE4A16ULL, 0xA5530D2B51D8A2CCULL, 0x1198010108B1D080ULL, 
            0x4521B05F6F6F1E23ULL, 0x15EFB08F4DF2916FULL, 0x7BF1C436DAE17DABULL, 0x7CF50578C7B3047DULL
        },
        {
            0x62DAED7B75B33215ULL, 0x7A0169D5E6E3F995ULL, 0x98623AD6023AF20EULL, 0xD7886C6E32EB2808ULL, 
            0x5F40362CC6A3647CULL, 0x6266208AC1EEDDF1ULL, 0xFCABB030E0D9DB4CULL, 0x276ADE5020C3D1A6ULL, 
            0xD7C5DB69975C1154ULL, 0x938515B922C812FDULL, 0xDB7BCF4312045F12ULL, 0x1A71673FA2E42B1AULL, 
            0x4A863E1077504705ULL, 0xB2DB45914243BAF1ULL, 0x8EF3F4D1BC22FD92ULL, 0x2FE430DF355425E0ULL, 
            0x835C769407EDDF8DULL, 0xA39668011E3FDEFCULL, 0x1B69A2F82B75F7C7ULL, 0x323F2A5740C55BDBULL, 
            0x1E374A2C13110479ULL, 0x6BC64D25D33AB206ULL, 0x7655DCA2C8D20788ULL, 0x29D672514386EF12ULL, 
            0xFC0C5B057AEC8C43ULL, 0x0895C7088EAE8A72ULL, 0x494CA8BA90DC12E3ULL, 0x18908A5AF7D95889ULL, 
            0x2B4303ED83F5128CULL, 0xB7CE711DD0C3B374ULL, 0x72AF36C895D71219ULL, 0xE5B931FC435394F3ULL
        },
        {
            0xA35DBC36DCBD8149ULL, 0x723A6392FA64DCA1ULL, 0x15ED06C05B27594BULL, 0xD63A97C6DF6DDACAULL, 
            0x5D6E754F104627A6ULL, 0x706560C13DE888D2ULL, 0x2225105E6D766A40ULL, 0xE10FA16B0CE36E87ULL, 
            0x8513C208E17DFE59ULL, 0x9BCE1030AFD9D124ULL, 0x2E03BEB9EFD2D0A9ULL, 0x279F4E1DF3F8879DULL, 
            0x26EBAAD1597D3098ULL, 0x344DCAE3A1DE4CCBULL, 0x6D7350032C09B224ULL, 0x3165388C38989629ULL, 
            0x25EA01C5224D4A4AULL, 0xE34312315590EA44ULL, 0x4B4792083512D0D6ULL, 0xA9905B7C97169919ULL, 
            0x2C2C01C4FD719750ULL, 0xD6A8BC9AAF195CA3ULL, 0x79F0064577BE4BA1ULL, 0x89D9ECE8B6D63CC2ULL, 
            0x65AA4D4E834F53BCULL, 0xFA0B73DC5692B28DULL, 0x3C609E05D75FF729ULL, 0xE9EA88E695BCBCB7ULL, 
            0x8D26E3643849C2D8ULL, 0xEF9915B0E1C990CAULL, 0x9D9B85ED3ED9C138ULL, 0xFB36E81BF10AEE65ULL
        },
        {
            0x458375B049703FB3ULL, 0x5DAA80CFB2556B33ULL, 0x0B17AB518FB1D646ULL, 0xA898444731384CA7ULL, 
            0x277EEED951DC9606ULL, 0x6E3E1E21ECBCBE5DULL, 0xE66C5FD5A42A072CULL, 0xC32BFE49C975DF48ULL, 
            0x4A6CA6B3EB998339ULL, 0x36F1888A6DA08D7FULL, 0xECCC79B0CA9FE1D2ULL, 0x6F73C4654ED80848ULL, 
            0xB3F9F706BD1D1099ULL, 0xFCA149E998A1B2C2ULL, 0xAE6E791231A472E9ULL, 0x7EEBE844BA9206CFULL, 
            0xD8C40428629B5A9BULL, 0x986831903A72FF3CULL, 0xBB25A29BD010F3F1ULL, 0x350009851750AE27ULL, 
            0x3F5709EFBE2C0C8EULL, 0xB43E0AE3A9DDE399ULL, 0xD1D1143911996FCDULL, 0x1ABACA96AE811CEFULL, 
            0x0321D77D929124F5ULL, 0xB34344547ABF0959ULL, 0x78191F27BF2DB12EULL, 0x647ED1F4401D5480ULL, 
            0xB64C9FE55F21A661ULL, 0x514C0F878ACDE723ULL, 0xA3A61920FE5D2B5AULL, 0x8EE6D6581D76AB71ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseEConstants = {
    0xCA4CD7EA70BE9532ULL,
    0x4CD37336F7466918ULL,
    0x995133AE158E79CFULL,
    0xCA4CD7EA70BE9532ULL,
    0x4CD37336F7466918ULL,
    0x995133AE158E79CFULL,
    0xE4263F1BCCFA8074ULL,
    0x77CE5C8F04010700ULL,
    0x66,
    0x44,
    0xD3,
    0xE5,
    0x2F,
    0x49,
    0x51,
    0x1B
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseFSalts = {
    {
        {
            0xCD7C101ACF752619ULL, 0x662B4304B75B2B8DULL, 0x835BF8214DEF3FF2ULL, 0xCA70B4F9777E45F9ULL, 
            0x4CAB09AC4A659F0EULL, 0x928E4AFD5356A175ULL, 0xA3C93749C9284E35ULL, 0xEBE092F088992916ULL, 
            0x31B294E1184F3414ULL, 0x8D13B5FB82E294E4ULL, 0xE32868970BFD703FULL, 0xD2886E88ABE7D0BFULL, 
            0x018970C5D7480F6CULL, 0x901399D67E19F5CCULL, 0xA63EDEB72308788DULL, 0x7AA8B8DF7E6FECF4ULL, 
            0x3F3B57CEB047E9FCULL, 0x1544BF6320CD959DULL, 0x0B0E9345AA3C0C66ULL, 0x5A497BEE4C9E9C62ULL, 
            0x7E1EC8C46680D6A1ULL, 0x03B4779DBF8C1745ULL, 0xD2C845F4F19902D4ULL, 0xEC4CD87CAF61D1E0ULL, 
            0x635D32845ED39609ULL, 0x1FE3F9483B2B09B0ULL, 0x98FE52022F6DFEA9ULL, 0x2A64BB87AD228CE8ULL, 
            0x3DE13C31725240D1ULL, 0x3D3C5D3E85DB974CULL, 0x232457DFF1D24F07ULL, 0xB1A0DE0A1A891AA1ULL
        },
        {
            0x2015EAECD2A6C155ULL, 0x094E1EFCB634263BULL, 0x7557C81C5B3D5FBDULL, 0x91DCF5211A96B7CDULL, 
            0xBB0EF0DED61FBDBEULL, 0xB705A9CF458408B3ULL, 0xD2FA9108AB689AADULL, 0x727BE842FABF07C2ULL, 
            0x2E6872DD1A554B7BULL, 0x4CB379D6DF534C59ULL, 0xCB51C8F813A288E1ULL, 0xBC77CDA729106BE0ULL, 
            0x55E5ECE210F62B9FULL, 0xD4504BA8DD5AA1EFULL, 0x622A7334D6F985A1ULL, 0xA2811B8D8C61D7B6ULL, 
            0xCC7B9B98844DB160ULL, 0x8776E79F53E5BBC0ULL, 0x957A6D3EAB9EB6F1ULL, 0x8EAC4ACE3A32BD04ULL, 
            0x3C1DA0FCF5CADC2BULL, 0xBBB70BA76AD13980ULL, 0x74421216FE716B9EULL, 0xCD56B145B660E727ULL, 
            0x5A5A1D5EF41611F8ULL, 0x18EC0921548C6FCAULL, 0x96B10ED000A74D11ULL, 0x5F6BB195BC54296BULL, 
            0xEBF35BE9A4275902ULL, 0xC9F353D3082A7568ULL, 0x669EB713B19CA2BBULL, 0x15DC0356E3F3DBBCULL
        },
        {
            0x5C0C9564B461B4F2ULL, 0xC7D40841EF06489BULL, 0x8286E7DA2486DF28ULL, 0x525328D0D80FF399ULL, 
            0x2B8CD86F3B5E1087ULL, 0x11EA8181714FC04CULL, 0x51F33527FB26D211ULL, 0x40D6503461081048ULL, 
            0x3E6E2FD7C7D3856EULL, 0xDE210D11DB4842AAULL, 0x59B859FC0B7B52C0ULL, 0x86514FA94D1075F2ULL, 
            0x8A01151F464AC334ULL, 0xB8B94D29575D19AEULL, 0xCF32495873700D3CULL, 0xA6E641F10DE1BFB1ULL, 
            0xA96603F2D33915BBULL, 0xCE7A29D5A5049029ULL, 0x339E28B68D7A7AF2ULL, 0x1D70580348F30797ULL, 
            0x2045A2248CCC3F99ULL, 0xFB41C5B516D2163EULL, 0xDC1656BC0BCD77E6ULL, 0x2155E2DA2276E7B3ULL, 
            0x984D17133DDC0ACFULL, 0x937AAB9596F2941AULL, 0x32656DE15118F889ULL, 0x27EAD3052EBD82F2ULL, 
            0xF424C69371C80A8CULL, 0xD71E2D91D0936279ULL, 0x41ACFEE541DDC86FULL, 0x7FF05A41295041E7ULL
        },
        {
            0xC1197ABD46E1A552ULL, 0x3029C5585DFEB5CCULL, 0x54B2A0ACA5BE8BBDULL, 0x1B97EA5B080B0799ULL, 
            0x30B7418474FF40B3ULL, 0xECA472927A52ED41ULL, 0x82776CACE4FD032DULL, 0x64B364BCBCC5A876ULL, 
            0x69F37B17A7E42784ULL, 0x96BB942B211ACA40ULL, 0x65C7164E1FC89B23ULL, 0x75456AEB6CCF3452ULL, 
            0x6FFBCFBFC523D99AULL, 0xA2F18C7B8CFE1149ULL, 0xEA2507ADFC4E053EULL, 0x2C19117503836AE6ULL, 
            0x9AF7B137AF815DFAULL, 0x8718980F993BCD52ULL, 0x8941EAD2DE22D8EDULL, 0x80439FF294904EC1ULL, 
            0x51C7991E1CFE9639ULL, 0x40985833ABC12528ULL, 0x232A81B47EB24CD2ULL, 0x151346BFE8B62479ULL, 
            0x3708929D99D20ACEULL, 0x1C59FE4403C35FF7ULL, 0x07931BD6FDA2E087ULL, 0xC2A4316F85AD0DFCULL, 
            0x8E68DE072899776DULL, 0xDBC70D0049FDEFADULL, 0xFED31BEA3686A09CULL, 0xDF8061ADDBC0F6FBULL
        },
        {
            0xFF65BE58CDB4C457ULL, 0xF2D2C56913F312D5ULL, 0xCECE78344FEF497BULL, 0x4C375790417B7465ULL, 
            0xE5FE23911C39C7C9ULL, 0x9C226E7E5FA502CDULL, 0xCC727557A6456DF7ULL, 0x90E94B92B28863B4ULL, 
            0x7585425FE0CACCF2ULL, 0xF4203A3DD2843449ULL, 0x6EA997F9ACF5437BULL, 0xC8511B9709EA476EULL, 
            0x7850A651D2DA4942ULL, 0x64BB3F1D038F32D1ULL, 0xFEC0343331D019B7ULL, 0x0C2604EEE9A057CFULL, 
            0xB1E9E79D64D5572DULL, 0x1EDCB61823A0CA54ULL, 0xE0D22783DB8CF671ULL, 0xB0DAEF52D7592404ULL, 
            0xEE3D876E2D642593ULL, 0x6D47A081A83E2F02ULL, 0xD73411C962B23699ULL, 0x58740D3C2A5DF943ULL, 
            0xB1E7AED5C7DB8AE6ULL, 0x7D854C0A7FF6D8A6ULL, 0xBB5C9BA3279BC8A6ULL, 0x4EBF2FBAD0B082C6ULL, 
            0x686825134DF0FF08ULL, 0x7B86521C1BE12B16ULL, 0x11E39119F8460CFFULL, 0xA550A4B8536679E2ULL
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
        }
    },
    {
        {
            0x60486E24E44AB325ULL, 0x81288FE36CFB5D2FULL, 0x19ADC1D7AEB5FC2EULL, 0x0C9EAA701AE59CA0ULL, 
            0x74EF0F7737611EF7ULL, 0x7989119FC3890D21ULL, 0x325396061A17C5DAULL, 0x6E702411B6762CDAULL, 
            0x975575061EA652DBULL, 0xE3E82667D44D931AULL, 0xD3C1F82373501C5DULL, 0x4EB49E5F6EF4C1A2ULL, 
            0xF9FB1527549EE392ULL, 0x652C5CE94FDEC8F8ULL, 0xDD6EBD687C90EC19ULL, 0x0D36F219F7922852ULL, 
            0x3E33E8DA2EBED850ULL, 0x5B5C2A65E332BF49ULL, 0x81E802B8291CB1C6ULL, 0xF57D6CA464AF06A4ULL, 
            0x84AB21325CEF6251ULL, 0x84B71AB83146BC68ULL, 0x18029BB3028CC4C7ULL, 0xADB9B58034EBB9CFULL, 
            0x5F16700300F62142ULL, 0x7C274A534F1E0B75ULL, 0x64862C6693797886ULL, 0xCBE2E09632F036E1ULL, 
            0xD85F298794176438ULL, 0x8D85C17719123FDCULL, 0xCC643E6C32B631C6ULL, 0xAD627CD502F7B1D5ULL
        },
        {
            0xF3DC215BCAC0D26FULL, 0x14369494A800A9FDULL, 0x5093C951D42ABC3EULL, 0xCDD7DBA1812C79E1ULL, 
            0x89B71DB05D7DE71EULL, 0xCCAF802B0368EFECULL, 0x0B7C86B492CE462DULL, 0x681F9A67B8BF014AULL, 
            0xD33E76EB9B9F2D6BULL, 0x0475010AC4EC0734ULL, 0x4F141E4016504E89ULL, 0x1A15A2F0114A9A56ULL, 
            0xF46EA08CA5CF7F59ULL, 0xD7881D787747A650ULL, 0x0B4FE44553A14D95ULL, 0xDB8ACB6AEA0D8E96ULL, 
            0x7C0D950B1A21182AULL, 0x0050D7FF967D4D0AULL, 0xDA942FF6C6343DF5ULL, 0xAE26F5CF34F63A88ULL, 
            0xE5CA11065A7900A9ULL, 0x421FC3878FEE36EBULL, 0x0E3E9CE547689BF0ULL, 0x53695F39BBDB4907ULL, 
            0xAE6799E13CE97F08ULL, 0x4371698F0719F012ULL, 0xF8C1D9BBC1280BF1ULL, 0x808D34C4B484831EULL, 
            0x6F135185764A466FULL, 0xA9740479B8AF7A7BULL, 0x67647BACAFAAA80AULL, 0xDEF584C8D454B657ULL
        },
        {
            0x8D73CEB00F1A6B28ULL, 0xE04F120AFF40230CULL, 0x1AD8CD30601246C0ULL, 0x2310D57BEE1B37CBULL, 
            0xF7A8C20BDC797D53ULL, 0x04D6DA95BC6E9574ULL, 0x952EE0EF8DA1FFF4ULL, 0x5AC1AF7DAE6B02B4ULL, 
            0x2D7FDFC2A7BE601FULL, 0xB840B7A9B54BA020ULL, 0x50F719470FD218D9ULL, 0x095F4D0177AEDF6EULL, 
            0xA48C16F20B451796ULL, 0xC20A3D8174C473AEULL, 0xF1087DDD3FF02AEFULL, 0xA372F85BA906C6F2ULL, 
            0xA698B99F819C9066ULL, 0x340B4B1D628B9998ULL, 0x0A3C482081AC09BAULL, 0x0D799677138A9CE6ULL, 
            0xA64750512BA69EE4ULL, 0xEAD19BB491618D06ULL, 0x4F6D864A9AC5E8CDULL, 0xF3293AEE248A604CULL, 
            0xB07EB37EFD70150AULL, 0xFBD9B8165F79A476ULL, 0x16FDA397B2184E1EULL, 0x4C2AE913B9D53F0AULL, 
            0xDD21B93DA5D99667ULL, 0x88B0DE1FC3A340FFULL, 0xF1EE122D504D109AULL, 0x14A6094E00C773B5ULL
        },
        {
            0x80837B96EE10D091ULL, 0x824732BC0F6E983DULL, 0xFE7565B0BF8E27D3ULL, 0x4B31340DC704BA18ULL, 
            0x76E03893CB14B2CEULL, 0x7367D2F8931DDF3DULL, 0x800403766DBA259BULL, 0xE9DCCC565E922869ULL, 
            0x609D81BA1901CC20ULL, 0xF280D2A95FE0DE0FULL, 0x30079843304587B7ULL, 0xDFABC02736334B5BULL, 
            0x1E95D23F4D95F7B6ULL, 0x956B4852A4974894ULL, 0xD674B92DB18FEC29ULL, 0xF1418D646F772EBCULL, 
            0x0ED77D47D34A637BULL, 0xA50B1F254F8BEEAFULL, 0x12283A2FEE90A07AULL, 0xB0FD27CC73D4E639ULL, 
            0x32C9320556681419ULL, 0xC6288FB5E726311FULL, 0x1F85383813532327ULL, 0x6D35B1D4EA0219EAULL, 
            0x5E37F921C8512EDDULL, 0x993A5D7A2E8A4372ULL, 0x76EF86FB8F5CE0BFULL, 0x26F71907C8B175B9ULL, 
            0x8B3489DDFA676F7CULL, 0x240AE01508A4F128ULL, 0x4385E30B5050CFE8ULL, 0x8C7A806F903EE500ULL
        },
        {
            0xBFDFF2A34926C0C0ULL, 0x2F25D15F47EC9029ULL, 0xA2A1A47F91D87FDBULL, 0x7EC1B7DCA3985A60ULL, 
            0x4C8CD2A8975CF8E4ULL, 0x26ABB8844D222DBAULL, 0x0E681C0289675D58ULL, 0x29E108743A79FAB2ULL, 
            0x960B8BB23AE930C2ULL, 0x5C3A14393C0F35ABULL, 0xCBA88A5647983F90ULL, 0x1796E2721ACBBB24ULL, 
            0x7B6CA9DDC1C34F8DULL, 0x3725458A397D0225ULL, 0x950324EDD277B461ULL, 0x45825615CD69B6F7ULL, 
            0x4647CA82D821C90FULL, 0x06548335AC7845C9ULL, 0xE029AC1BAAC39563ULL, 0xBB6E2CE6F85DD69BULL, 
            0xB7BF156587CC8116ULL, 0xB6A4A0CA8E6BDB70ULL, 0xFD85A1322676EC4AULL, 0x452810CC2AB45557ULL, 
            0x8F570FA645DA3F06ULL, 0x279DFAB6EAF6AE25ULL, 0x088F19BBA3EC5B3AULL, 0x6A7B047CCEE3DF02ULL, 
            0x31F80B7C19AD05E1ULL, 0xA3C0AA3ECC1DC083ULL, 0x772B4B38768C51F9ULL, 0x3D366E6194242466ULL
        },
        {
            0xC81D620892219BADULL, 0x5D6F094C6A93D528ULL, 0xFA6C0E29AD59A2D5ULL, 0xF4B96CFD7206E2FEULL, 
            0xCD350E0001DF303CULL, 0x7689D8458D67FE0AULL, 0x6AE4E36615D1BAAFULL, 0x31C24434CF1305CBULL, 
            0x3BA024EAB23BEE75ULL, 0x6236DAD9A1752099ULL, 0x71BCD7A3B2DAEC6FULL, 0xBBDADB13ECF2B420ULL, 
            0xBCA1D166F13B43CAULL, 0xFE29E185175B9395ULL, 0xDDAAA770B622B9CCULL, 0x7972F1E2F14A767EULL, 
            0x8D8C538AB5A97E48ULL, 0x9BB0C528CC7AF518ULL, 0x0CD2605738A4B2D6ULL, 0xCE8BB9FC1A076147ULL, 
            0xB130110432C23B42ULL, 0x174272C85EC88EB4ULL, 0xAF98ED65FCED07AEULL, 0xA60C1B5DEFEE5C67ULL, 
            0x1F55060691D9E754ULL, 0xC14F3BD8A7D5FBCEULL, 0x2C76516E991761F3ULL, 0x1D38F68FE5BA66D2ULL, 
            0x655542DFEF3BD05EULL, 0x30EF40E1B0154EE3ULL, 0x3EE354446299FCB4ULL, 0x4DFC25A9C802466EULL
        }
    },
    {
        {
            0x199D7542F834B23CULL, 0x637FDDC15B6CAB14ULL, 0x5703798BD0E3611CULL, 0x0D6BBCA870FC1275ULL, 
            0x42B268CF97D0BB6DULL, 0x7C62074BED1D0414ULL, 0xBB4803F2B7F18708ULL, 0xF409FAA4D70E201CULL, 
            0x4400F3566527F4B7ULL, 0x9040C572DDB18776ULL, 0x5D333635B1C152A1ULL, 0xDC714667D2A94C8EULL, 
            0x5B3C45DE25BE165DULL, 0x10D6200C264A67C4ULL, 0xB4B1694A82E499FFULL, 0x6D9488BE79E05255ULL, 
            0xB24C43EBC5614E7DULL, 0x0E3D166EF86E170FULL, 0x0F4EE813997EE8A3ULL, 0xBEA61809A209B6FAULL, 
            0x5CA2C39635B7D51FULL, 0x34F71A0DFAC9836AULL, 0x84FF7D09FF2B0C99ULL, 0x2C0BD64E665D90E5ULL, 
            0xF6BCC234FE2D7B25ULL, 0xEA08AE5E5DD33E21ULL, 0xD04B1E4D62B07EDEULL, 0x214CFB6E26ED03F9ULL, 
            0x4FABA475D0DADAEFULL, 0xD07FCA2A523ECF5FULL, 0xA638A5E76B0AB19CULL, 0xF73A3E6F3D287B48ULL
        },
        {
            0x6A808AF33C1349FDULL, 0x4F6EC2874DA8D181ULL, 0x0AFC9984F6D24DDFULL, 0x7CA59725E7430DF0ULL, 
            0x4E46609ABD866F53ULL, 0x4992D0DDAA9C671EULL, 0x5F29C7C64AA86914ULL, 0x7E46996B98D5A75FULL, 
            0xC80CBD53C1A683F8ULL, 0xC7E4930DD5FEA203ULL, 0x967C5B804380566AULL, 0x8403FAF60060A430ULL, 
            0x42825F6EF5C9C4EDULL, 0x3FED9F5185A67A47ULL, 0x714965F95F1D3BC0ULL, 0x9F81B7A42E2497CBULL, 
            0x8174E38E6EA142D8ULL, 0x6BB8EB7E48B87747ULL, 0xB17BC1DA06BD915FULL, 0x3F1654C60FAE45ACULL, 
            0x7BBE9F51E277B52DULL, 0xE9514C8D72B3017AULL, 0xDD6E396BB20AF1FFULL, 0xEF627742EBEFD2C4ULL, 
            0x0B367304C9CCE49DULL, 0x1DD841D09D7CC05CULL, 0x525FFD2167F9AF0FULL, 0x83FD09EFFF218473ULL, 
            0x5B7762CA27619898ULL, 0xCD14B687E5F87EE3ULL, 0x0035BFC01702182CULL, 0x60DD5776CC367D21ULL
        },
        {
            0xA72E2B413672A1D6ULL, 0x2623BEE523A77C53ULL, 0x426DF59A89F02F36ULL, 0xFE4E0AB99052D760ULL, 
            0x6C2FE2BC9AE11995ULL, 0xC0CA982470D30082ULL, 0x23900FB2968AF60BULL, 0xB96B63E046A70693ULL, 
            0x4026DBEE9591B6BAULL, 0xA122A6C57331B5CDULL, 0x95E30F33A892D5E4ULL, 0xB3FA3EE990A16240ULL, 
            0xB2140D32FF4622AEULL, 0xF69A0A0368994316ULL, 0xA6FA7DE16BC8C4C0ULL, 0xB6D20584AED75411ULL, 
            0x879458628DF5B3EDULL, 0x946A6E4BA32D3E3CULL, 0x40C1A3BEAEE60476ULL, 0xED8CD968BE745291ULL, 
            0x478027412384B0FDULL, 0x32F8A925D67679DEULL, 0x57521EEE7807E65BULL, 0xF8D26D5412ED0528ULL, 
            0x9EC811883F4D1828ULL, 0xEA12959F1C0F953FULL, 0xCEF80B5695E77A81ULL, 0x92522D0B9910DC99ULL, 
            0x2B45168F3FAE5FF6ULL, 0x2C0AC5F7D1496785ULL, 0x71421FB94A5410BFULL, 0x151BAFBAF2F4F9A0ULL
        },
        {
            0x8DEA855F1F5976C6ULL, 0x700535CA67BCD4D6ULL, 0x2F2A4A452A4584D1ULL, 0xF32A191AF7FE985EULL, 
            0xF9EE316BC47016EDULL, 0x2BB7CCA95B86D474ULL, 0x9CE07C28E16BD5B5ULL, 0xEACAF2A9E1C7B574ULL, 
            0x1EACE0E420C34B87ULL, 0x955104DEAAF85F19ULL, 0xCE6078DA044FD00CULL, 0x8255D68DC17A2C29ULL, 
            0x134E817497703FF5ULL, 0x40B5D0BFFBB23080ULL, 0x77BDA0376E46656CULL, 0xEA4043ECFB372B30ULL, 
            0xE27F627214D25F9EULL, 0x7A07839AC00B050BULL, 0x3D509B2D0ABAB2ACULL, 0x821BD10499AA0F3DULL, 
            0x5E013AFA33BF76AEULL, 0x82BE393F1A214C51ULL, 0x9AB3D7BE5B1A5DE8ULL, 0xC4FABB506A855F86ULL, 
            0x9D72312BE65EC6F5ULL, 0xE6DF21F319D3B3DCULL, 0xBDB6BD124F4789CDULL, 0x1766E3377A236A1BULL, 
            0x2064C73EB8E70AADULL, 0x9BFE43E0C1C60DBFULL, 0x150DF1D430DCC546ULL, 0xDA01546969579BECULL
        },
        {
            0x3FF5AA61B473E61CULL, 0xA8D2EDDB89267776ULL, 0xB2CEBCE02E8B7C96ULL, 0x0208461C8411AE72ULL, 
            0xA347E59BBE5BC2EAULL, 0xD4167D6B16E7FDBEULL, 0xD07AB1E195D08894ULL, 0x211DDBFFB56FC3F2ULL, 
            0x22228F3A190B71A7ULL, 0xF34E91E3F9D2B5A5ULL, 0x8AAF218585B86E2DULL, 0xCB36907410A92754ULL, 
            0x8ADD0E802210366EULL, 0x03300F2C0F80CB15ULL, 0x1551943A9DA9633FULL, 0xDD6B37B6E827C79CULL, 
            0x75A447552EC0BA83ULL, 0x1EE06F328B9A4419ULL, 0xA728DDD83A26B0F1ULL, 0xFD42A095E95AC190ULL, 
            0x730191C0B52514CAULL, 0x0A8FBF8B1582AB66ULL, 0x0FBF27EF6EF12206ULL, 0xD9292F1BE1340199ULL, 
            0x876CF8DF8CE7E7A6ULL, 0x3D722550D1A2D3C3ULL, 0x45AD6BC18DAE4F59ULL, 0x6F372D3D2E53399AULL, 
            0x58203651FC61ABCFULL, 0x33D5AB67851FE9BBULL, 0x5B6C35A563A2A0FDULL, 0x67E6B2FB0BDE3306ULL
        },
        {
            0xD301CAEF55072BECULL, 0xA0A8D5AD249E96A0ULL, 0x9982B5F8E7FB4290ULL, 0x52168F1E101D5C88ULL, 
            0x5C415557722B698CULL, 0xFCBF258700C2FBE6ULL, 0x383A307E7FB9D90EULL, 0xDE812B293BE8E0D4ULL, 
            0xD12C5FE3B0B36B4AULL, 0xC48DB0C08DE2308BULL, 0xE62280DEBAD9F44BULL, 0x39DF59E26DD99B92ULL, 
            0x131005BE36E7F214ULL, 0x7CF18619F4737E2FULL, 0x87FD333E3C4084BFULL, 0xD5B42C7E4BD3E02DULL, 
            0x980257649BF8A864ULL, 0x1D733D18F83D2EC8ULL, 0x83184A62F75D2946ULL, 0x8D83954624D1E85FULL, 
            0x58FD69E9D1CC6DF3ULL, 0x17A5C3FA91F10BE9ULL, 0x2279B2B3B7895216ULL, 0x3B54B251CE54384EULL, 
            0xF74C1442AAB2145BULL, 0xF3BD27219AA12EA7ULL, 0xB5C456C63B5F8C77ULL, 0x9FBBDFA4806E129EULL, 
            0x90DF66849FEDC754ULL, 0x304CA621005DAC08ULL, 0xC943F99EE7B750B1ULL, 0xA7CA7C24C8B749FEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseFConstants = {
    0xC8F670610646BB31ULL,
    0x5741AC5F105E930AULL,
    0xEECACE1393528854ULL,
    0xC8F670610646BB31ULL,
    0x5741AC5F105E930AULL,
    0xEECACE1393528854ULL,
    0xEE90867C9DA1636DULL,
    0xCCC148D29CFC9209ULL,
    0x99,
    0x5C,
    0xCE,
    0xEF,
    0x92,
    0x54,
    0xBE,
    0xE8
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseGSalts = {
    {
        {
            0x2950D2EBB3A6C5FCULL, 0x4CEDCE07F0876374ULL, 0xB52A58B9EC4B4463ULL, 0x7D9C3C87CE79747EULL, 
            0x187A41DA65AFAFB2ULL, 0xF7B82A9C590D586FULL, 0xFB253605B5994957ULL, 0x08D543FDC56A46EFULL, 
            0x3B5AB9C51B2021E2ULL, 0x2A9342B2BBB5599BULL, 0x1FCC92D04E3C0D11ULL, 0x2D58B1BF586571FEULL, 
            0xC434EA7D359E3908ULL, 0xC82B049A6AA1E14EULL, 0x5718EDA48C45C7AEULL, 0x4C87455C056FA8B0ULL, 
            0xA8A34CA44D0AA13AULL, 0x08E8F7301F4FF094ULL, 0xDAE033F6471B87D6ULL, 0xDEF91C1EA2056A2FULL, 
            0xA478DA20A24C7905ULL, 0xAE9846EF1E5CF439ULL, 0x99366694C35EE1D6ULL, 0xD2037AD4DA82D03DULL, 
            0xA26A69B272912233ULL, 0xB8058CF8B1F049C0ULL, 0x547629BEB74A654AULL, 0x325795BB28464CE3ULL, 
            0x04FB8AF54A934FA4ULL, 0x960FD06096170087ULL, 0x384CB88D1E9BAD74ULL, 0xCFF66AB7026DF94DULL
        },
        {
            0x0C8ECD92B11EB352ULL, 0x90DF51105DE96600ULL, 0xB7CC1DCFAD0C6AD6ULL, 0x1E006416421E9633ULL, 
            0xDAC96AC3F2BFE6AEULL, 0xA3EC750B08E38528ULL, 0xFD288D0C0E78CD69ULL, 0x41AB9EB1162C8314ULL, 
            0x7D41731669142AEDULL, 0x07AE223C4420AB07ULL, 0x0442ECB9BE816BF8ULL, 0x24DE192BC0F3FB5DULL, 
            0x2CB19AE9343BF47DULL, 0xBEB17E60DAF8D28EULL, 0xBAC7E88F3654823FULL, 0x7390F8C3C87E45EDULL, 
            0xB1F1D5F64D23288EULL, 0x2957C00D71402C78ULL, 0x7799CFF3C0CC7F10ULL, 0x9F24E02597E8CA05ULL, 
            0xE51430EFA48B4F2AULL, 0xA17EC86A13D7BEEEULL, 0xE5DB6714C1037CEBULL, 0x15C2DA493CC59C48ULL, 
            0xDB655F3C9D7D8E30ULL, 0xE177B8C46F583A9BULL, 0xAEF1255ADB25BF7FULL, 0x8BB0902B796E6C82ULL, 
            0x013BD2C25EA743DAULL, 0x405B5FC7D949F7A2ULL, 0xA0AAE9CE52275F9FULL, 0x7D2D2C5C78B54607ULL
        },
        {
            0xBAB603F2D7233E46ULL, 0xCFCF63E5DD47497CULL, 0x2073114E80DBEC29ULL, 0xC15EC697B5BBC9F5ULL, 
            0x7CC0E025D79DA56EULL, 0xA9569C7A735302E8ULL, 0x410812F30467F3BCULL, 0x7C9E77A659254349ULL, 
            0xD91ED1C16BF64F5FULL, 0x117986F926C401C5ULL, 0x1E23A17220FEFFF6ULL, 0x0B4083BBE8EE1ACEULL, 
            0x7507E6B867D6B670ULL, 0xDE86B2FC732E9D74ULL, 0x7DF8DA9EB241E3ACULL, 0xE22832D14C22B55BULL, 
            0x61B28692211DB926ULL, 0xD132A7B81661E5DFULL, 0x8911112F1E634AD9ULL, 0x7759BF30EBF06D19ULL, 
            0x40E4C85547AFDD09ULL, 0x84412880E8730AC5ULL, 0x9FD61C46A115C615ULL, 0xA784252DBF893389ULL, 
            0x8D8D4CEBF8D17655ULL, 0x04A404C6C89AC918ULL, 0x0F563F422F1CFC23ULL, 0x49D9B6318C5A15EFULL, 
            0x1C2B7041E0E0A5C0ULL, 0xC011A7F6F54FA667ULL, 0xC37F4228EEB83029ULL, 0x5425A787C0AFAD17ULL
        },
        {
            0xF1F8BF666BA631D4ULL, 0x6F07755B1F62ED8CULL, 0xB3420A83126FE903ULL, 0x3A329CEE2BABFD52ULL, 
            0x0A77472D1BC059A4ULL, 0x2527F3916F05B4DCULL, 0xD7D79A3AEF8005E1ULL, 0x703A0245509096ADULL, 
            0x8F788E769F4ACE48ULL, 0x02E6DBF13CA42DD8ULL, 0xB245E0FA11831C78ULL, 0x062112ABA33E181CULL, 
            0x68581B5C7BDB6AFEULL, 0x3DE5F9E24CEDC3C3ULL, 0xE1CF446DEBBB7BDCULL, 0xF5B1FFBC20177547ULL, 
            0xB3625EBD8F6A7DEEULL, 0x4BA847D343AA6348ULL, 0x604BF75B54214F58ULL, 0xCD14BB01B6C12F48ULL, 
            0x57DD53BF0EFB3BBAULL, 0x6957C92006119852ULL, 0x51033B8DB6C4B6F2ULL, 0xB587E3A3294A5DC6ULL, 
            0x0BDF846C8BDD7151ULL, 0x43D739A8B75BC55EULL, 0x01DE45A84F2BD48EULL, 0xC1976A126DBE8D47ULL, 
            0x2EDA65206A2E3F88ULL, 0x97F9350D957BF25CULL, 0xA247ED8DC3178BEAULL, 0x8035172913D8C50DULL
        },
        {
            0xE5DC6935831A1A6BULL, 0x340BA021480A6456ULL, 0xEDC41895E1B96A81ULL, 0x2328EFD9AB4D4782ULL, 
            0x9F617D8D60BE878CULL, 0x2B2E2CCDD0EA7FB9ULL, 0x3A469C99E055C55EULL, 0x3D91A523C7012B3DULL, 
            0x787743E443D73803ULL, 0x4AEE6D701E58368DULL, 0x084A8F8E49133082ULL, 0x52DAA0BBB68FE8AAULL, 
            0x7746D7D9E89E40F7ULL, 0x7DE6A0A9F84CC1D3ULL, 0xC27D9209E3ECE2E4ULL, 0x8DA4967DB24E926FULL, 
            0xD9942B5AF3627C63ULL, 0x8A5E58C7FFE7ED72ULL, 0x321B332A44E10497ULL, 0x5329B278E92A55ADULL, 
            0x08026FCABDF3C455ULL, 0x59D46E08070D56B7ULL, 0xD31835FDD15C8EC0ULL, 0x5A4501222793CCF0ULL, 
            0xD664D4B97FDBC2EFULL, 0x068E66935C98BD8AULL, 0x08C43358358B36DCULL, 0x8290D43DAE93CA4FULL, 
            0xD237BED3564E88C3ULL, 0x1BBB607820E2AB36ULL, 0x2E0115216A27935FULL, 0xCFC162C6DD1D3572ULL
        },
        {
            0x9BCD70A1320B5BD6ULL, 0xAD6C70D2E0E1F01EULL, 0x26BD21C9D99F4C52ULL, 0x26272B46314DAF15ULL, 
            0x2EB3E42AB19E0AC0ULL, 0x4F4E3FC8E6F996ECULL, 0xE55EF0139E0530BFULL, 0x3E545F96F60889B9ULL, 
            0xC4F764950BD65701ULL, 0xC3BFD8932EAB5526ULL, 0x70795E40EA03C759ULL, 0x0459FCD62A786836ULL, 
            0x4DE902AAF984A092ULL, 0x334FC1A844D7E254ULL, 0x02279A0231A50424ULL, 0x3DD5381C90969266ULL, 
            0x657BDFA811A1D1CFULL, 0x5496360401A8642EULL, 0x0961CEE2B3996E5EULL, 0x42070F761FDA0614ULL, 
            0x96CFD14BB0F46287ULL, 0xF7CF11B634240AF8ULL, 0x81C36CED989F79A5ULL, 0xE79118ACE890D8AEULL, 
            0x1A366659019584A2ULL, 0x2B2B134371586C82ULL, 0xD489D8E682F363ADULL, 0xA2A6D926770A15E3ULL, 
            0xF07F545CB51C0DACULL, 0xF8D04331E74F0DEFULL, 0x7B344BE40A0F0557ULL, 0x3DE9BA24B3970487ULL
        }
    },
    {
        {
            0x777E047AFD62EC5CULL, 0xD18F735978CBC97FULL, 0x75BC56E6716A7B3FULL, 0xD91CC221F9AED357ULL, 
            0xD20864D22B27AC4DULL, 0x34D9CA77150A6232ULL, 0x2910EE07E8B4716AULL, 0x940F10BDD5029D9EULL, 
            0x5B2DFF79A2D010F8ULL, 0x07D9730E4D186DBFULL, 0x22EFDC0130471F8FULL, 0xFFE822E959725F7AULL, 
            0x7449DA3E9D57F72AULL, 0xC3E997D134D48BDEULL, 0x222F5E50F09FE9B9ULL, 0x86B32D9A91DF32CBULL, 
            0x66F713C030626013ULL, 0xDCE3BFB99853FFE6ULL, 0x2546B379271E253CULL, 0x35717F62F81AEBF5ULL, 
            0xE95ADABF1C970A06ULL, 0x8B9AADF7658C0D2FULL, 0xCBACEDD5CCD25EC5ULL, 0x477CCEAFE7AACD22ULL, 
            0xBD344A13A083E8C4ULL, 0xC0DA179773321CE6ULL, 0x6D941D4C560E952CULL, 0x3983A142056251F6ULL, 
            0xCB985F20C88E975FULL, 0x2A61DC65F8CBC91EULL, 0xCB3DE5ADEE563FC8ULL, 0xC737D6C4266CC11AULL
        },
        {
            0xACBEF58B3FA73BA7ULL, 0xD308D233C7B596DDULL, 0x643D8B6146BBA9ADULL, 0x4FE41C19EEEA2BFAULL, 
            0x8F55AB517024A139ULL, 0x9EE85A981BB4C391ULL, 0xB27D8BF3B66EEEBBULL, 0xBE3B094931D55B73ULL, 
            0xDE92D76E330CEC64ULL, 0xD742CBFD1433B436ULL, 0xF7EE3D48689F6923ULL, 0xB9CBFF266B62ABB5ULL, 
            0x7B71D7A96D1AD79CULL, 0x3AC14C3D013BE99AULL, 0xEFE306FD7148DDE8ULL, 0x533CCE53875C1FE5ULL, 
            0x0188360E010575B8ULL, 0x91259D604E1CBF02ULL, 0x0C4F97C385E4BD6BULL, 0xAED4A86C78374C6AULL, 
            0xDD645C711FC0242AULL, 0x8683F1871E7E10F5ULL, 0x6147797F7111CCF3ULL, 0x34F520B6DE1B2D46ULL, 
            0xB9116882769FFB58ULL, 0x3EB55E01E9BB6878ULL, 0x440099F248FEDB8DULL, 0x9A75A2C3C9C788D9ULL, 
            0x1C8E688EE0B3A7AAULL, 0xBA2428007A5FFAF5ULL, 0x099F70EE72B569EBULL, 0x8CC4EAFC05DEEDC5ULL
        },
        {
            0xF48D92B0672F13B3ULL, 0x3DA8B8EA19C90BB8ULL, 0x3B862049A8707B2FULL, 0xD4685B8F572D83F8ULL, 
            0xDBAEEC5FB44DBE11ULL, 0x4F8AF9B04E23A2C0ULL, 0x038531205900046BULL, 0x83FBB24BD7CF5ACEULL, 
            0xE321ECF123F45828ULL, 0xDC1E77980B4C066AULL, 0xD120D651A21F418CULL, 0x3B57508CABA8C11CULL, 
            0x1A378BCEBAE8254FULL, 0x01B1289363C9B4D9ULL, 0xAE7A701BD800C899ULL, 0x2E8F487C726D742CULL, 
            0xA2D75039B84B8D4FULL, 0x2CBDABD55F3748C9ULL, 0x710CA3EB8E6D40BAULL, 0x3D9912BBAFAF93E4ULL, 
            0xE63E3A822D6A050EULL, 0x9FE6A0EBED16117BULL, 0xE15929E764080C4AULL, 0xC2129E2FDF0D02D7ULL, 
            0x18D376E0D9094707ULL, 0x192C2E18EAE1482CULL, 0x95DA75BD091A9B58ULL, 0x9F15ADAB8B7A09FAULL, 
            0x1EE3B45888854922ULL, 0x126BCBB605FB03A1ULL, 0xD9415406FC71F142ULL, 0x1E4AC0930F6DD473ULL
        },
        {
            0x52C0177E78B582C5ULL, 0xA509E93610417D36ULL, 0x652198987AB06626ULL, 0x221C3611D6E3E947ULL, 
            0xF3F33049B6D49C17ULL, 0xCD33946E53140931ULL, 0x3D709729D1EEA60EULL, 0xDA34E20E7144EA5BULL, 
            0x1452BD8586F39FAFULL, 0x70B10B988921013CULL, 0xA8C3C2D9ABBBF903ULL, 0xD3E8137680113C92ULL, 
            0xD0EAD637BDAA1150ULL, 0x1B34B10934EE4D3BULL, 0xDB3B182BA6F217F2ULL, 0x73505051EF260DFEULL, 
            0x67E1A444710238ACULL, 0x783DC2DD40D6C957ULL, 0x87345DEF2B0A99F8ULL, 0xDD6DB30E91E4A525ULL, 
            0x84A04D96A739EE26ULL, 0xF426637399F2B9AEULL, 0xB7359D990666D43AULL, 0xDCB828A3E154CD3EULL, 
            0x61C2721E60ABF8D6ULL, 0x8D0BAC96B1960425ULL, 0xDE0C09F5B64E2B87ULL, 0x0418B9935C892CC3ULL, 
            0x6081F1576DD5114AULL, 0x598217DC73040A54ULL, 0x91998CB603C377E1ULL, 0x7C693405FD3A0234ULL
        },
        {
            0x0F4BEECB31C1D157ULL, 0x27E05119287512B1ULL, 0x25EB191ABB10D787ULL, 0xD9B68D1C4D26979BULL, 
            0xEBE85F58EA2FF827ULL, 0x5DB6DD9582CA844CULL, 0xEEA84C70391B4E83ULL, 0x5519500CB207ADDBULL, 
            0x291B46777B155137ULL, 0x587CF8AE7629B0A7ULL, 0x6044C9D6790477E6ULL, 0x2F650F596C5032B4ULL, 
            0xF012426BB39B4927ULL, 0xF3C44127DDA433AEULL, 0x3771E515D4F05E94ULL, 0x193438B81340FBBEULL, 
            0x800EA6BBABDD690AULL, 0x284059F02D3038C6ULL, 0x2186271EF664CBBEULL, 0xF94CF00C4D7D56D1ULL, 
            0x8F868BDCD0C34086ULL, 0x4F8737BA6A4AD46CULL, 0x471EEDBF4FB24655ULL, 0xE82B1074586956E6ULL, 
            0x1F829C39FD63FFF6ULL, 0x821E684BFC155283ULL, 0x11EA50A6C00456BFULL, 0x26E6D75B5FBD7E71ULL, 
            0x0D575D50D91DBF1BULL, 0x5DAFD433340E131BULL, 0x80FE2AD2B7BA62BDULL, 0x9040F96F16C134DEULL
        },
        {
            0xC55D5197B6297052ULL, 0xF0B1A1F5670005C5ULL, 0x4AE8ED364D37CBECULL, 0xBE1D7547475C6C18ULL, 
            0x1715DACBA1B10C05ULL, 0x2A838AEA52BC2293ULL, 0x34E82465CFF31390ULL, 0x1EA731E8805F6B30ULL, 
            0x3F051D584AA39D72ULL, 0x4805F5AD1982F4C5ULL, 0xFB50D7108E429E1AULL, 0x9004D8A6603A92EFULL, 
            0xEF21572F9C950709ULL, 0xFA808FA974B9268BULL, 0x638E8BF417FBEF44ULL, 0xB575E315140FAB6EULL, 
            0x3BC2656C1BF91E9FULL, 0x8CCE61D9B62E4F60ULL, 0x18FE73D2C975003CULL, 0xD3236525BAD84D57ULL, 
            0x8893FE0C5012021CULL, 0x0002C2BE5136986AULL, 0xA8B2C46D4F728AE2ULL, 0xF600DFA9AADB3E0AULL, 
            0x52FAEB1B7A7B9D4AULL, 0x00B8D389B009478CULL, 0x13BDAB9405B770EBULL, 0xD3EB17AE1916D6FCULL, 
            0x6D4857F122535D46ULL, 0x2D71E61AC3093454ULL, 0x16B7907173042B81ULL, 0x6C782917FE3FC309ULL
        }
    },
    {
        {
            0x684FE4EBBA5420A8ULL, 0xBC9C4A3D4C42F400ULL, 0x7F957F6080A4579AULL, 0xCF473BACDA6EE3ACULL, 
            0xE799370B59D8051DULL, 0xFF1BA4AB6FB8A8DEULL, 0x77C612AFA3CBF990ULL, 0xA5F7FD9E74E1B152ULL, 
            0x374A10E79B29364CULL, 0x64B60D8DEEDF83AEULL, 0x5051ED979CC3B423ULL, 0xFE145224850E64EEULL, 
            0x457F73248541DB37ULL, 0x6B9F37A28670D204ULL, 0x14C9AD8B2097C05CULL, 0x25766C49CC0C4A73ULL, 
            0xD0E91FCDB30B3B21ULL, 0x9872217A2ED7ACD5ULL, 0x3E5EA1905FA0BAB1ULL, 0x705F43565C543954ULL, 
            0x09D6A0A24D58F34CULL, 0xE00C7C3B27907327ULL, 0x85F24C5F37B9BC25ULL, 0xFED355619C3249F2ULL, 
            0x1EF8B8AADDFD463FULL, 0x0B150855A5E17701ULL, 0x40AF836A4FDF9A3FULL, 0x27FED94BDEDDA82EULL, 
            0x0DB3B3E5C5F3EE88ULL, 0xC6E42F6CE73D1C15ULL, 0x93DEA8AC395C5BF9ULL, 0xABFCF85D7CF584D2ULL
        },
        {
            0x3D2F28E37EFA8491ULL, 0x3522E8E7254F15F4ULL, 0x9D2B322BF6B86A39ULL, 0xE01F535AF48B33B6ULL, 
            0xE826F874CA7B2F6FULL, 0xF4D1603BF046F560ULL, 0x75025E0CBAC1A9EAULL, 0xD0C830ECABE06B90ULL, 
            0xC35755297C51AD5AULL, 0x84258C7BC1DB47B2ULL, 0xB3F9AFA4F1C1627FULL, 0x51235AFBC09313A7ULL, 
            0x5D259AFC82591F68ULL, 0xCFEE4D6DB0A2A71DULL, 0x8D174A5F769A891BULL, 0x6820D667549D7D16ULL, 
            0x50EF210CDAFE00C9ULL, 0xDBAE145752E6CA3EULL, 0xAC2D67717BC1DE30ULL, 0xBC6B6251BA2669A5ULL, 
            0x31F67CB86AFA33B5ULL, 0x5E66889E54BE0456ULL, 0xEF54B8DDED94CF96ULL, 0xAD99781EF11EF22EULL, 
            0x40157DAC62B61865ULL, 0x26F22A0F152962B8ULL, 0x76A70A3BCD6288EBULL, 0x3718E6F325C1DD1EULL, 
            0xA26F62E4D3BF0ED3ULL, 0xA118587F2034FECEULL, 0x5D2905B320100752ULL, 0x79CC2FF18AF3A2E5ULL
        },
        {
            0x782A0606E4AA8FBFULL, 0x78D09D84FB006304ULL, 0x538A631642CAC90CULL, 0x5CC9564028664BCBULL, 
            0x7C0735FB558ED8B0ULL, 0xA8717737939BA28EULL, 0xE953CEF18DB0514EULL, 0xFC5B344B533DC9C5ULL, 
            0x0F81DAA7DD180DAEULL, 0x59E209C1196F0E71ULL, 0xD08B841A4F74DD14ULL, 0x74BA60BC0E4EFCE9ULL, 
            0x52B7CFDE1EDBC339ULL, 0xC4FB717E88AFA7A3ULL, 0x7517B4F89F8BA059ULL, 0xEB382D66026717DBULL, 
            0x92F9A6EB123DB617ULL, 0xEFC0E68F2648DB0BULL, 0xF4FE6D4A3ACF7BA8ULL, 0x0FAB8A06527EC924ULL, 
            0x2F1670530F91550AULL, 0x4B53EFD4495F8F48ULL, 0x69D5DF5637F743E1ULL, 0x1AC6661702E6C344ULL, 
            0x438743F3766A102BULL, 0x679433745963763CULL, 0x1CC3CBAC51843236ULL, 0xD19D2A443F772FECULL, 
            0x512B5576CDC3AA92ULL, 0x2B3529B4AC573522ULL, 0x4558E4F28825071EULL, 0x7F3B8459E31364ECULL
        },
        {
            0x42572AF9D6893F57ULL, 0x6A858156EACE733CULL, 0xDC5BE3D518114AE9ULL, 0xF1740E731490ABC6ULL, 
            0x801730D0488185D5ULL, 0x716EC255EFD2ADB4ULL, 0x26C0AC98B0E5BD92ULL, 0xB0D5F46C3444F793ULL, 
            0x31C87F4FC97690C6ULL, 0xEBCF71A2B46F2DDCULL, 0x82A3109A21E3F01CULL, 0x968C26F15BA077C4ULL, 
            0x1C7A63F38D9C5246ULL, 0x6662979A8F83CBBAULL, 0x278A964582CD6D2FULL, 0x22C0700665D030B9ULL, 
            0x17FEB6C4FC3DD3A5ULL, 0x2E04E0A18B093BC4ULL, 0x8FEF6AB41C3B49CCULL, 0xD50A998A9F1B36BBULL, 
            0x33F9B469BAF9CB77ULL, 0x41CD49C03EEB14A6ULL, 0x624E607A009E25BCULL, 0xBACD7A515F7128E8ULL, 
            0x07B676D0AA1FA0D0ULL, 0x5DA43A9694440AA8ULL, 0xDCE2E70F047AA1C3ULL, 0x16677A0110C1D32EULL, 
            0x66F08F05A84369E6ULL, 0x038715090C7D3A8FULL, 0x4E1C54BEB8C90C04ULL, 0x5C10C2DD42301A73ULL
        },
        {
            0xA09FF0A0D250F5C6ULL, 0x6B47CBEF973D128BULL, 0xEF08339F930FEFACULL, 0x65C285C83C8E0AACULL, 
            0x1FD85EC5F0335888ULL, 0xD230F3B1ED0424D2ULL, 0xC5BC0EB0F07DFCE7ULL, 0x2F6EFD776CF62F20ULL, 
            0x2FA27948618456F5ULL, 0xA312CB6C64E9E6F6ULL, 0x1A4648CA7436E2F5ULL, 0xE5F1A0A67D9AF86DULL, 
            0x7D23E12F2998B10AULL, 0x122EB15BD3308DA6ULL, 0x67538BC34520FB40ULL, 0x9014157083068BF1ULL, 
            0x982DBA0382395939ULL, 0x9347D041E4A2FC30ULL, 0x98EA6C0DD3B12DE3ULL, 0x044DB7C6367DC8F2ULL, 
            0x17DDE06238819273ULL, 0x33D5E7F00FE877B4ULL, 0x8568AD7C4CA11DE0ULL, 0xF23EDA0A22F0C1ADULL, 
            0xD18BFA208CC91101ULL, 0x9E9B5F1F9B08150FULL, 0x2A092244DF3726ADULL, 0x8E03D138D95FDEEBULL, 
            0x327F45E02F4E98ECULL, 0xAC0FB74D8D97C91CULL, 0x2017DD0A7A5A1FA8ULL, 0x57A679E890F4BD22ULL
        },
        {
            0x21C141296177EF64ULL, 0x7A0495E36CEDF3E8ULL, 0x2090470AD27485A1ULL, 0x897A9ECBF0C4A03AULL, 
            0x7DAD514A60F9A42FULL, 0x6427FA9DA439AF2AULL, 0x1219561507A69642ULL, 0x004C7CB0C31929E4ULL, 
            0xDF60D7C81A675410ULL, 0xBB00C54399CDC8F9ULL, 0x90894A5B4D088C4DULL, 0xE8375004828DDC3AULL, 
            0x904C79FADF02067CULL, 0x5CC33ED1D82031A9ULL, 0x47DF010CFE4A5214ULL, 0x39796218CB713769ULL, 
            0x89DEAA66D9E32669ULL, 0xE4393911EC4FFE95ULL, 0x5D3B43314F471031ULL, 0x6388B84C894761D1ULL, 
            0x9870DDB25E2B0901ULL, 0x134DA9BC8AE21620ULL, 0x2C6CE552E4529653ULL, 0x357F4F78C40F6C84ULL, 
            0xE9FBBDC8A3A089BDULL, 0x4492C0142B500E46ULL, 0x83E55993016ADDA7ULL, 0xC22F6867B2ECD600ULL, 
            0x02156CF80A7AFA14ULL, 0x6173A9E31E56E886ULL, 0x924540E3DE2B36EFULL, 0x88B8AC1058F15336ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseGConstants = {
    0xB5490700F9E0BEA8ULL,
    0x09593A2A1ADC2A44ULL,
    0x560B06907A80479AULL,
    0xB5490700F9E0BEA8ULL,
    0x09593A2A1ADC2A44ULL,
    0x560B06907A80479AULL,
    0x2D36D1C07D27923CULL,
    0xA6FB1F4D1CB469BCULL,
    0xC4,
    0x77,
    0x57,
    0xAD,
    0xC7,
    0x51,
    0x61,
    0x53
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseHSalts = {
    {
        {
            0x5EE5088698912561ULL, 0x7D7C76ED894AAC23ULL, 0x533AA59980EAD1B3ULL, 0xFD4019638A950EF8ULL, 
            0x8AED86F0C0DCF36BULL, 0x8F8F28E1F68C0416ULL, 0x79973E7B5E9DE615ULL, 0x20612F8868764CD1ULL, 
            0xB46D17C11D17FCD2ULL, 0x0EFFD3BFB587BA98ULL, 0x2F00D88B8FE6D69DULL, 0x1715416FDD2FD0D4ULL, 
            0xB0F83DB8137FF3DAULL, 0xA4718558BF7E51FDULL, 0x8846277CEBAFE8BAULL, 0x88EF6E2991488AF1ULL, 
            0xCD1BDA5331B98CD1ULL, 0x5F0FCB42C976DF52ULL, 0x82E3D9275F1DC58BULL, 0x10314A423B3BF8C6ULL, 
            0xBD44EE915F35EA64ULL, 0x3FBCCEEEB57E61B5ULL, 0x7F7053BE1D54E98FULL, 0xC471EF2EA09421CDULL, 
            0x9C38210EE636558CULL, 0x720BE3880F460567ULL, 0x72E55C5A899166C3ULL, 0x4A31A2CCABD967DEULL, 
            0x4206C6FFA980D04EULL, 0xD8D48F9E16D283BCULL, 0x543571A6508F9803ULL, 0x72A768CA2DAB1C2FULL
        },
        {
            0x0D1F70C0F2691149ULL, 0x8CCFEF409CE2B925ULL, 0x29B23B99CDBFDD69ULL, 0xAD32AC2CF984447CULL, 
            0x0E488D364D572934ULL, 0x8F2365CD7220B67DULL, 0x02C2DB0C47746316ULL, 0xCE56232EE10F6639ULL, 
            0x1276F505C949E008ULL, 0xDE2551357DD3F397ULL, 0xE12DF76C27B2C92FULL, 0x794D7297ADADF2F4ULL, 
            0xBEC91CE252E5F088ULL, 0x92081018AE1470E1ULL, 0x45A16F11D568DA0EULL, 0x73FC8B686EA7B63DULL, 
            0xE1E729BB85FC9AB0ULL, 0x6C6EEA58DA7C1C08ULL, 0x8264234A9D009D7BULL, 0x349EC3201F05968DULL, 
            0xE65AD9AB3951D17AULL, 0x4206D135D1EBE03DULL, 0xD35964AAB05A3635ULL, 0x06E2CE7046662C55ULL, 
            0xACBCD93A2FD162E9ULL, 0xE7BDED6EE08A9FA3ULL, 0xAF207A2B321FA8B5ULL, 0xCC893BE14BB60E61ULL, 
            0x30996FB2FBAB805DULL, 0x2CC6A97F728820E4ULL, 0x9DF92F18B8B04EB0ULL, 0xAE0DD8F354C774FFULL
        },
        {
            0x29649D5EF9800B16ULL, 0xF8D4E4F2A1E5F278ULL, 0x0D41BADBF293AFC4ULL, 0x187FB8DD893141E9ULL, 
            0x25D31EE052C37017ULL, 0x270A50E459AAA399ULL, 0x05B1102194F07350ULL, 0xDDCCC569E8B30AEDULL, 
            0x33F6F9EFBE2D0BCCULL, 0xBE8E23C4A25A2C86ULL, 0x3D2719FC693F6C41ULL, 0x4BA46673D40B07DCULL, 
            0x4EE8DF6349D2C353ULL, 0x94701CA992DD225FULL, 0xB651E19DD1C38BB4ULL, 0x5D84A6280DB7DDFFULL, 
            0xD3A7C434F3957239ULL, 0xB9AFD63F63EFFC8DULL, 0xCFCB8B473D55CE6DULL, 0xD6376CE6FCA21383ULL, 
            0xE682FDC99581D07BULL, 0x3BB3E61A5E21D04DULL, 0xA75B31506E7579B1ULL, 0x32B1632A8428A234ULL, 
            0x6A0C4D327D197D5FULL, 0x652B1B14E49D8544ULL, 0x5CB8EC19F35E7C44ULL, 0xE3978391F024D0BBULL, 
            0x31AE9AC9F469BE71ULL, 0x86A9192437C76DF8ULL, 0xDF4A2C99C436AB5DULL, 0xFE1289B872ABB3EFULL
        },
        {
            0x9DD6861EADDD15E1ULL, 0x3EE9E793A948812AULL, 0x3A193EFE47D20AD9ULL, 0x74E138116CD4A255ULL, 
            0x4E2D044F111007F7ULL, 0x3D8C2408C9683596ULL, 0x4D572EA725BE8C99ULL, 0xB4E763332C3F3C56ULL, 
            0x2A2DA55809EE7BD0ULL, 0x1350D8FEDE358FA4ULL, 0xE6779BB5F0A2454FULL, 0xE37DE829E6593B14ULL, 
            0xC9908BA58C1E9F33ULL, 0xEB0086427A300E23ULL, 0x693EC140AA597AA2ULL, 0x006B5432677DFE2DULL, 
            0xC95FAE3115C0A8A3ULL, 0x651837BD51A751B6ULL, 0xAB25F6B1F784D067ULL, 0x7F8B9B61A2290F68ULL, 
            0x0792B5E43F670727ULL, 0xD5598E59A02B215BULL, 0xD8714B8EBFADA275ULL, 0xC3A6FD140C5A31A7ULL, 
            0xEC534E72203136A6ULL, 0x680E984D4800120AULL, 0x8EE53F3225914E5BULL, 0xB22F181C15CF28E3ULL, 
            0xAC693EEC5E9B865CULL, 0xB85D2B1E60AC62B6ULL, 0x70ED97EEF424DE9DULL, 0x62CA9F69829B2FFAULL
        },
        {
            0xD4657DB3E96BC258ULL, 0xAB2F1333A2CD1D0FULL, 0x54D2A2B3EA54260CULL, 0x6FA09D4C81489AB9ULL, 
            0x917DE6F55838304CULL, 0x104817D1BBB53D16ULL, 0x52107B32E5C831C0ULL, 0xEE6AA2774533D462ULL, 
            0x3C0A3F7912B37FFFULL, 0x010F75C09F454886ULL, 0x5F700798C3C09E54ULL, 0xC556A1DB603B71D0ULL, 
            0x804373C340192276ULL, 0xCE93546CA8C29700ULL, 0x0D95E537198EE68FULL, 0x587137FF5733A716ULL, 
            0x5345BEF79E563DDDULL, 0x21FD28E81BFF6C8EULL, 0xFE3761E4E9C58773ULL, 0xBA71656EF85A2452ULL, 
            0x3895CDB74951A502ULL, 0x7C4D79493FE433A3ULL, 0xAF86BA1CC6C1D265ULL, 0x3F2159768ED7677DULL, 
            0xD28BC6FE0E7FAB62ULL, 0xD780C21C0B20C52FULL, 0xC132228F1DF9587FULL, 0x69884EFCDDDC90B8ULL, 
            0xEEE46212D361ACA7ULL, 0x3986BABD020915FBULL, 0x2843BBFA1C64246BULL, 0x2C263FBA1CAC4512ULL
        },
        {
            0x53BFAB8C21742E55ULL, 0x8925541983E39B4FULL, 0xF73EE4D5DF64EBE1ULL, 0x78C07193B354C18FULL, 
            0xE1191F2F7AFB18CEULL, 0x3291381ECE9791A7ULL, 0x5C4857EA365237A8ULL, 0x0ADCF168E880F893ULL, 
            0x40EDD1894D76E62DULL, 0x24F102C1BA1ED0ACULL, 0xAF2F99329F1932F5ULL, 0x2B8B9CAA4D5A8B34ULL, 
            0x5F426A8B88DD7E80ULL, 0xC60D1CCEF8648BF5ULL, 0x5F7D9EA51E7A30FCULL, 0xBCC03470BD01D0C2ULL, 
            0x95F230DB6D029CF9ULL, 0x83C2BF6A81EEB0B9ULL, 0xB373E9073F0338CAULL, 0x9DD4962674BABB28ULL, 
            0x4E961C68D817DE7FULL, 0x93286BE19C2DDD5AULL, 0x1B4AD38BCC554ECDULL, 0xB850CC67E49D967AULL, 
            0x3B6F1F82E1150CC0ULL, 0x6E1D07723FC2C4C6ULL, 0x82D87EA2F4670347ULL, 0xC810F310B67CB37BULL, 
            0x3FA7A78821ABA80EULL, 0x0A054DD3D2CCBAA2ULL, 0x054BA9C9B5643240ULL, 0xD34CB14BAFFA1A6EULL
        }
    },
    {
        {
            0xC375432A22D55FBBULL, 0xA8B0C70C770F27F5ULL, 0x8FBD13C92BD6EF1FULL, 0x6C1807CDAECD234CULL, 
            0x8E486DE2DBFF3FA7ULL, 0xC22E57B53B728DDEULL, 0x8D20B256EC3A79E9ULL, 0x4633CA6A4775494EULL, 
            0xBE044D28DAB997A2ULL, 0x25A3ADEFB6F88048ULL, 0xE511C893AB17F10BULL, 0x3751130B5B79E4D1ULL, 
            0x6254B1C1CF5BFD9FULL, 0x1BEC390A08F1C4E7ULL, 0x2B1AE2429D301ABCULL, 0x120DE58B5AA018F9ULL, 
            0xFCB2A86E8FC550F5ULL, 0xB326836F64534A19ULL, 0x0F02B891CD3579CCULL, 0xBF148F9498791158ULL, 
            0xA08FE248770F7F89ULL, 0x461DB03CB3903A1AULL, 0x37BB3095F13669D2ULL, 0x203DFB4D705707C8ULL, 
            0x3370081FBE9520EDULL, 0x8A2CCBEE798FF7A7ULL, 0xE3DE1357DBA53E78ULL, 0xA8A3DD1742C3F453ULL, 
            0xB0F57FAF32A14265ULL, 0x39FD0871BA83EEBCULL, 0xA076B41E51935F29ULL, 0xDE1606F50DEB4DBCULL
        },
        {
            0xFC2C7C9F7605E062ULL, 0x58E68ED49B73FE00ULL, 0xDD9E06750620B903ULL, 0x1161E03B86DD42F4ULL, 
            0x7FE1B2C7B6F11D73ULL, 0x0488DB1B78CB7323ULL, 0x9DA0708DBF79B91AULL, 0x01C223B6C8DF3936ULL, 
            0x78A5FC6B962EA200ULL, 0x0ADD699C09634D3DULL, 0x1EABA39BDD2C4D36ULL, 0x1FDCFEBBDFE7F945ULL, 
            0xCEB6134119116D63ULL, 0x5A536E3853CD80FAULL, 0x8E48474133B5FB50ULL, 0x5BAF11827C0B0AE0ULL, 
            0x8056198A6A5CFCCAULL, 0x8EECE49D055F4EBFULL, 0x2E3D0F67DB65ABFCULL, 0x3077ECB6ED142E14ULL, 
            0x2E84954E672DF15CULL, 0xB373E3042608C721ULL, 0x6DBABD3699E7B225ULL, 0xFE921DD7E2AA9697ULL, 
            0xFAE204E7C9F1FC17ULL, 0x7E315695AAC02763ULL, 0xD742FBC95E6E970DULL, 0x704E5FCE8FC789C0ULL, 
            0x9C5C25A5A8F40D1EULL, 0x09BDCAE7962CBEF3ULL, 0xBE0713091F14C848ULL, 0xD4B543F893D754EAULL
        },
        {
            0x5E8C2C7017A25777ULL, 0x26A676D1E0DEF5FEULL, 0xAF1310B4191DBE88ULL, 0x12919F3DABEAF900ULL, 
            0x2C00DD72D611AA92ULL, 0x82821852241D0FF2ULL, 0x0CC24C54BA6E7823ULL, 0x7468339F75237934ULL, 
            0xE96FDF0AAB7FFF1EULL, 0x4B1D35A25B3BE06EULL, 0x98C5827A631BEF83ULL, 0x11A919E3AD8CA062ULL, 
            0xC0734812780370EDULL, 0x928DD1869C1AFA3BULL, 0x47791CA474AB3AE7ULL, 0x53B8D69A25663BE2ULL, 
            0xCAE0AE1E04233ADCULL, 0x44D301C1D2BCF135ULL, 0xDD6984D379E559D7ULL, 0xA66BE7260B8EE3C6ULL, 
            0xDB945A41D73855BBULL, 0x3159B92F7C1D7CACULL, 0xC9C0DD21E03F6082ULL, 0x1A804ADE1D390EA8ULL, 
            0xD9FE9B15B9F3FBEFULL, 0x4205B483E515B84BULL, 0x3B5CD2057A84AA3EULL, 0x79B4EF1E82E54006ULL, 
            0x367ED5A84114B7C0ULL, 0x708D43F19B489AA6ULL, 0xB34EF38521755C22ULL, 0xE232EE68E8A8725EULL
        },
        {
            0x8DEBC83C7D3D747FULL, 0x49CA59FBF877D807ULL, 0x8922007783580BDFULL, 0x414A71146E392A1FULL, 
            0x4547A716B527E95BULL, 0x9A99F35CDAC4B973ULL, 0x86700F10A9F36BACULL, 0x1637672739674694ULL, 
            0x153D151C486D743AULL, 0x70E1B2FA1A986AEBULL, 0x6805D321CF87F4BCULL, 0x9A34303F1E906CDFULL, 
            0x6B3113827C7F2563ULL, 0x2BC549536D4DD3D7ULL, 0x97C19F9DBA09239CULL, 0xAB949A68105A2BF8ULL, 
            0xE421726AAABF96BAULL, 0x79274570E1C3FC6EULL, 0x34D205DCF9B364A5ULL, 0x1F25FB9D4B816E67ULL, 
            0xF1AB2C7836C2F2C3ULL, 0x031B42B67A0ED98FULL, 0x6122C32A15D969B1ULL, 0xCC57257AABB95649ULL, 
            0x0DB0D02F1B738921ULL, 0x62A289484747AD91ULL, 0x568B3F63CAAF0414ULL, 0xB7AEBB8A5DB63B7FULL, 
            0x6BAD478ACCCCB97AULL, 0xC73F9CEA516CF699ULL, 0x5ACCB7C73423C3E7ULL, 0x49E4F19CD8A8257EULL
        },
        {
            0x3CAAF270358B74A5ULL, 0xFA8E9D594C05C57DULL, 0x493A6E4154C47F52ULL, 0x0F3A7B67822D3DA0ULL, 
            0x7FE3EA7DAE484D3EULL, 0x46A3AC87A77C5145ULL, 0x4EB8A0E7EE926ECAULL, 0x7C6AD80AA93CFAC0ULL, 
            0x559FC385B2486463ULL, 0xEFF336D973AFF642ULL, 0x684D55AFA96D10F1ULL, 0x4D0C0D4C40509B9CULL, 
            0xD0B999D7BD95B20DULL, 0xC3B279BD3EA547D8ULL, 0x02E0F304B6ED8A01ULL, 0xCFD6F9F3C44DB92AULL, 
            0xDA2C99D5392F436DULL, 0xC8CAFB5766E1B9B0ULL, 0xBA30EC941FCF001CULL, 0x9E422F217170E3A8ULL, 
            0x4C670C7F146CA2FAULL, 0xD6D8398FC0A6651AULL, 0x126C7051B64F34D7ULL, 0x4777F3571E279C45ULL, 
            0x2ABFA212150A2E53ULL, 0x266C92ECCB639BEEULL, 0x23956E738188E364ULL, 0x372AE0C1E4DB17DAULL, 
            0xBF14EAF110B15742ULL, 0x4964CF9226EB4878ULL, 0xF4CBEF643D5E2338ULL, 0x7835FC5556BBE39CULL
        },
        {
            0x6AB97F81BF4907F0ULL, 0x0E55A46E0DEF2C47ULL, 0x0AC4CB8EB9C2BE99ULL, 0xF6F98C12B96CF5DFULL, 
            0xF94EAB10CD11E70AULL, 0x105573163ABC125CULL, 0xCFE69CD0E8D4A543ULL, 0xA77EDF27533F1C3AULL, 
            0x58E64A050B651718ULL, 0xE1E74CF78E402CD5ULL, 0x1BA009A4C584DFEEULL, 0x2B37547A33EA968EULL, 
            0x410A58D104865320ULL, 0x4BAF3CF2AFF24DAAULL, 0x237294C9981A0725ULL, 0xE9047D35E0C2636DULL, 
            0x39849A5D3932FAE4ULL, 0xD7AB57A9A2986BD8ULL, 0xACC10354588FBA6DULL, 0xE514216D9BDF8CC2ULL, 
            0x6E412E4BAB97EF34ULL, 0xD2B1796E6492B6A8ULL, 0x53DA26ED4B179C4AULL, 0x3DDBE0904C2C1E2DULL, 
            0x9400628CD2D8E53FULL, 0xF8BDDB828EC83D55ULL, 0x509A9F2CB3347933ULL, 0xD45B7B472A5324B8ULL, 
            0xF05D37E29129E430ULL, 0xC051EA9CDB85275EULL, 0x19F086273847935BULL, 0x44FA39C02BC1331CULL
        }
    },
    {
        {
            0xF8C93415BE80BDE6ULL, 0xDCE67B071547BEC3ULL, 0xD6C7B91F9D27D4BDULL, 0x5AD72840D55D1924ULL, 
            0xFEB72D6425C9B345ULL, 0xA7940A3CB3FB19D8ULL, 0x3044713D2F87DD5DULL, 0xC60C8E5BAF3AC37FULL, 
            0xE286C028963ABB3EULL, 0xAD23B310B32F0600ULL, 0x47263B6570B0FB69ULL, 0x68B32F50916F9693ULL, 
            0xB3EF1C50130BF090ULL, 0xF84215DB4A07C8FAULL, 0x211A48F354EB1353ULL, 0x51D3455F99A217A3ULL, 
            0x3137F841B0B02BB9ULL, 0xADC4814D112F23E7ULL, 0x17A9EAC581585334ULL, 0xB35230D8C236FD03ULL, 
            0x2E1F5168E45F1C3BULL, 0x4F24E57E78C7EF2CULL, 0x8AC4F0D1341B18E2ULL, 0xC8BB2DE18847185BULL, 
            0xA1C4A60029A5A1E0ULL, 0x81A7BF79368F18E9ULL, 0x96F2D30404C75ACAULL, 0x4B930B1DA9510833ULL, 
            0x759630BB7CDBBE8FULL, 0xD741A811C8077DF1ULL, 0xF76304454A0C6605ULL, 0xC9E7CF9463367653ULL
        },
        {
            0x4EE8583463B99358ULL, 0xE56B3C80E5D5C218ULL, 0x99C4E5CCA7122F85ULL, 0x6135DC652A704050ULL, 
            0xAC0A217911EF50F3ULL, 0x674AD9E8BE0C949AULL, 0x57EC2435134F460DULL, 0xE7A29B2EDB0F9CBCULL, 
            0xF57BE7665C9E43A5ULL, 0xA1B931C2279D053DULL, 0xA3300E2206330E8FULL, 0x170FE26B3A386144ULL, 
            0x5A5AD87546BDFCA3ULL, 0xA0824240308E3B48ULL, 0xFCE3D58055BB82F1ULL, 0x2BDFADD855A1A57CULL, 
            0x0693686E469AB91BULL, 0xF71E149922E8B3DDULL, 0xEDC4165181C60F6CULL, 0x0BA970F7A6EC368BULL, 
            0x5AA3EA3B455B25B2ULL, 0xD44C968316129533ULL, 0x4F1096F9683C012CULL, 0x62C43085A3F79FC7ULL, 
            0x152AAAF7215B71B6ULL, 0x580998E138AF707CULL, 0x02053246AEFF4249ULL, 0x3F69E077864D5B1DULL, 
            0xE3FC8A25E982591FULL, 0xB4FE7773F2D12552ULL, 0x94D21476F3CE2F33ULL, 0xB3358007E7D58F10ULL
        },
        {
            0x2D5F8A8B3C6E2C2AULL, 0x65592C2E53011FD1ULL, 0xBEB6D9BFD79D107FULL, 0x25DC0EEB01FAD546ULL, 
            0x3C8D7C7BB02263BDULL, 0xE1398871129CEE79ULL, 0x8632D6A57B7B4982ULL, 0x132006C383282F7FULL, 
            0x13B0BBDF4D292599ULL, 0x20EEDFD5D8D5DD54ULL, 0xCF4BCA5F10FCBECEULL, 0xAB9E77887BDE5555ULL, 
            0xFDF7E4EA7F9C9B3CULL, 0xA585F1113FE540D2ULL, 0xEAAB960BA446A41BULL, 0xB574CAD9AF29009DULL, 
            0xA89E1613A6FD0DF5ULL, 0xD5FFA81A4C45CA0BULL, 0x787D053394C0F2A2ULL, 0x2DBE7295E2B38BCDULL, 
            0xE2CE71BE83FDE6BFULL, 0x29675FB8AB0E6C31ULL, 0x6A8B3B7218016286ULL, 0x4A140850B21CA87DULL, 
            0xE89262FE02DC1FB4ULL, 0x6418A059E3BC2837ULL, 0x497E38482DA356B5ULL, 0xB8C1C9A9776CA888ULL, 
            0x401B34458F1F8217ULL, 0x264A7423904F635EULL, 0x9887459CBB7BD5ACULL, 0x8189413B30C01881ULL
        },
        {
            0x9C18D559849643C6ULL, 0x2A201471535231B4ULL, 0x67D30102B628EDBEULL, 0x54E1F9AE85D6918EULL, 
            0x12AD5A8CC9618FDCULL, 0xF35D94AFFD247F72ULL, 0x101DD2454E810EE1ULL, 0x159C7C10E5DC438DULL, 
            0x6EE9CF77C1FF972EULL, 0xA33A3A4E1176149BULL, 0x4321C6003985B569ULL, 0xEAD44FBFBC8EC480ULL, 
            0x0B5DDF708006864EULL, 0x486C81F10B8D9E8CULL, 0xFC94FAACF644E171ULL, 0x46F04C922FAB1A81ULL, 
            0x9DA2E099CEB04CEBULL, 0xE16C6119668776BCULL, 0xA1CCA7B1D4741F83ULL, 0x4CC6BE96355D1BF1ULL, 
            0xC9E245BDF50244EBULL, 0x11E2E79064D091A4ULL, 0x816400F099BACF34ULL, 0xA2CC9BC6965ED2F2ULL, 
            0x60005179E9823666ULL, 0xC4E5B1C682631A38ULL, 0x26273318A026AE98ULL, 0x1459D7D5F7CFC5F5ULL, 
            0x54A441D58359CA3AULL, 0x9E32FA32B4EAFF6DULL, 0x9CE0BDCA8DCAD2A6ULL, 0x78E46C84C1D00B09ULL
        },
        {
            0x9DA47A8D5B3E175FULL, 0x3630F0ED83828081ULL, 0xBF435883C95A2760ULL, 0xFB236627CFD78EB2ULL, 
            0x38B9BC14BE2B5D07ULL, 0xC199591173FEEEC5ULL, 0x5FBF12CF17E57854ULL, 0x33BEBC47E060383AULL, 
            0x94CD33FAD987F837ULL, 0xAFDB428A18CC30ACULL, 0x6C061967CDAE51D9ULL, 0xCAFD3854AF3BE921ULL, 
            0x957E02B9234955E9ULL, 0xC903608CA91D4DC1ULL, 0x19A4EDC9C05BEC6AULL, 0x3A604805D51BD86BULL, 
            0x1FC824C226F33D07ULL, 0x6239F9963BB30D0DULL, 0xE13CAC0581A260DAULL, 0x40A1909048E55F86ULL, 
            0xBDDF8230363DDDFEULL, 0x50AB823547473296ULL, 0x905DCD35BBB8B6CCULL, 0xA368C17649AECF27ULL, 
            0x8E50F9BB15D11C12ULL, 0xF215B48F549AC22DULL, 0xAB5853F29C737953ULL, 0xBE8A3467927C3919ULL, 
            0x635AF832A28E4ED3ULL, 0x8CD26ED1DCCCF98FULL, 0x2B6E7765BC32EA14ULL, 0x1AB96C292F2DF1E2ULL
        },
        {
            0xE3EDAEE5C83B1571ULL, 0xC3B8AC6A87CF5472ULL, 0x888AE17227E6156CULL, 0x029BC7805A27FD4BULL, 
            0x07E06DDE57449B8EULL, 0x3A85F9D131563D70ULL, 0xE5E399A94C4B1D3CULL, 0x2DA4D97018A83A4BULL, 
            0x3DAF2BB32BC8A068ULL, 0xEE919012A87421AAULL, 0x091A6B76FD358F6BULL, 0x96C7E6BB4D102A6CULL, 
            0x17AD7791CA193379ULL, 0xB5F48DD66DBC9E46ULL, 0x1B79DB4201751FC7ULL, 0xB52DECFA81E56741ULL, 
            0x34D27F592A19EE63ULL, 0x28658CBA0EC4A674ULL, 0xB4DFA18C99D65A58ULL, 0x563F5CB3B02454D8ULL, 
            0x478E8F65C030509AULL, 0xE07AF207C109F19EULL, 0x1AA478E955A90E90ULL, 0x333E1A6C70E7F28BULL, 
            0x261047AD6A04CE27ULL, 0x35BA9617C1E2ACD8ULL, 0x7E9EA9CCE7A8C64CULL, 0xB402C87163C8AE72ULL, 
            0x680A51DB2ADDE0F0ULL, 0x8862C0CA17A70E30ULL, 0x381EA32E7D45D5BFULL, 0x1C19BBE5F7CA5680ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseHConstants = {
    0x5BAF33B0B11BD728ULL,
    0x5F0985CD3C198C9CULL,
    0x9C67F9CF97FBD598ULL,
    0x5BAF33B0B11BD728ULL,
    0x5F0985CD3C198C9CULL,
    0x9C67F9CF97FBD598ULL,
    0x014D6D710F74EE2FULL,
    0xC9AB2CF101FC42ADULL,
    0x06,
    0x4F,
    0xD3,
    0xA4,
    0xE8,
    0x5C,
    0xBF,
    0x7D
};

