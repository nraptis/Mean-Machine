#include "TwistExpander_Bellatrix.hpp"
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

TwistExpander_Bellatrix::TwistExpander_Bellatrix()
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

void TwistExpander_Bellatrix::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA5A8683BB5D56C66ULL; std::uint64_t aIngress = 0x842F787DC07CF8E9ULL; std::uint64_t aCarry = 0xE3AFF992801B6273ULL;

    std::uint64_t aWandererA = 0xB94B03740B140A57ULL; std::uint64_t aWandererB = 0xB339678C0C699A25ULL; std::uint64_t aWandererC = 0xE6A40BBC207FE91FULL; std::uint64_t aWandererD = 0xA962A7F84F6256F3ULL;
    std::uint64_t aWandererE = 0xCB14CF9871E19389ULL; std::uint64_t aWandererF = 0xCA050CC4B89F4C3EULL; std::uint64_t aWandererG = 0xF17B4BD931F10E23ULL; std::uint64_t aWandererH = 0xC7DEB8190D5E24C0ULL;
    std::uint64_t aWandererI = 0x9605C316A3A27123ULL; std::uint64_t aWandererJ = 0x82D5896782ED5E94ULL; std::uint64_t aWandererK = 0xAED448E94B125AC8ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9264987746907881351U;
        aCarry = 15214826527492390237U;
        aWandererA = 9740690218147349152U;
        aWandererB = 10849678743074997719U;
        aWandererC = 9935769516791697366U;
        aWandererD = 9706104240218878199U;
        aWandererE = 9750528955816648455U;
        aWandererF = 15605013369797064651U;
        aWandererG = 17537980959313761457U;
        aWandererH = 15524373364615826501U;
        aWandererI = 13392304419744787232U;
        aWandererJ = 11758790175174373633U;
        aWandererK = 10622012175779883252U;
    TwistExpander_Bellatrix_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Bellatrix::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x82E0D6DBCC25F2D9ULL; std::uint64_t aIngress = 0xDEB8076C90280FA5ULL; std::uint64_t aCarry = 0xC99CC2FA1F06014DULL;

    std::uint64_t aWandererA = 0x8E2B409786CB2116ULL; std::uint64_t aWandererB = 0xC646731DDBF1EFFAULL; std::uint64_t aWandererC = 0xF5A1418B8E8BF716ULL; std::uint64_t aWandererD = 0xB26CF490E22E91F6ULL;
    std::uint64_t aWandererE = 0xEB20F5D225B0386BULL; std::uint64_t aWandererF = 0xD604B94732FC3155ULL; std::uint64_t aWandererG = 0xF6A3489A3D0ECAEFULL; std::uint64_t aWandererH = 0xA0EC3468D9637594ULL;
    std::uint64_t aWandererI = 0xC07C2C105F2D29BCULL; std::uint64_t aWandererJ = 0xAFB2A29038DC7374ULL; std::uint64_t aWandererK = 0xC6D56C1B23A6B05DULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18093680611917141528U;
        aCarry = 11960077491843733468U;
        aWandererA = 11764237845467096170U;
        aWandererB = 18180017006607154008U;
        aWandererC = 15621675201916592241U;
        aWandererD = 10715884224076102411U;
        aWandererE = 9397759601827596245U;
        aWandererF = 13941246979570458475U;
        aWandererG = 17575521351156390370U;
        aWandererH = 11170549038087269579U;
        aWandererI = 10694515650416473314U;
        aWandererJ = 17192786590195883162U;
        aWandererK = 16698854446680693201U;
    TwistExpander_Bellatrix_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Bellatrix::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xAEB6FD3C99F3F45AULL;
    std::uint64_t aIngress = 0xB9046D4FEEB44762ULL;
    std::uint64_t aCarry = 0xDC18D3DEB1480AFFULL;

    std::uint64_t aWandererA = 0xB432D0267870835DULL;
    std::uint64_t aWandererB = 0xAF847E26AF8D0930ULL;
    std::uint64_t aWandererC = 0xA272FBFA0797F7C8ULL;
    std::uint64_t aWandererD = 0xB1548FA3FA4D9E1FULL;
    std::uint64_t aWandererE = 0xF20BFAD84627DC0DULL;
    std::uint64_t aWandererF = 0xFB88718EE6DA82FEULL;
    std::uint64_t aWandererG = 0x9F453FC07B8CDD96ULL;
    std::uint64_t aWandererH = 0xDA7AB47C4A98B669ULL;
    std::uint64_t aWandererI = 0xB987A1C5260A2A2EULL;
    std::uint64_t aWandererJ = 0x87C86B3626996D76ULL;
    std::uint64_t aWandererK = 0xBA6106F2BE89144DULL;

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
    TwistExpander_Bellatrix_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    TwistExpander_Bellatrix_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Bellatrix_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 12 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1843 / 1984 (92.89%)
// Total distance from earlier candidates: 20380
void TwistExpander_Bellatrix::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1454U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 722U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 53U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1721U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 553U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 386U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 771U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 301U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1188U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 613U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1031U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 667U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1567U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1877U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1870U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 919U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 834U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1648U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1228U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1075U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1842U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1731U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1014U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1506U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 498U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 533U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1271U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1573U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 347U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 931U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 658U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 121U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1805U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1835U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 285U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 409U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1611U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2008U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2038U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1300U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2006U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 636U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 543U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 221U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 698U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 304U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 723U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 213U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 801U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 746U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 524U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1905U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1087U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 714U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 282U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1116U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 315U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 820U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1239U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 378U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 699U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 306U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1264U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1655U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 681U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1465U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1155U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1684U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1777U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1400U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1078U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1330U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1561U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1207U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 747U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 674U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1129U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 923U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1284U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1873U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1347U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1210U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 900U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1186U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1413U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1528U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1762U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 387U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1675U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 256U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1468U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 204U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 314U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 442U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1510U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 108U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1941U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1579U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 244U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1521U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1003U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 991U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1404U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1047U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 694U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 176U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 202U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 738U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 847U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1349U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1410U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1879U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1190U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1543U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1568U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1301U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 494U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1308U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 61U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1786U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 226U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 808U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 586U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1246U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1297U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Bellatrix::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE3780BFC8D9C6025ULL; std::uint64_t aIngress = 0xBB42AF23CC3D7885ULL; std::uint64_t aCarry = 0x82DC40FBB715DDD0ULL;

    std::uint64_t aWandererA = 0xB1E117DF0CAC5BA1ULL; std::uint64_t aWandererB = 0xE8DAFE892C2E64A8ULL; std::uint64_t aWandererC = 0xCE36FBA10CA5E4C9ULL; std::uint64_t aWandererD = 0x9357333A9BACB1B4ULL;
    std::uint64_t aWandererE = 0xC10DE3B45D9C59AFULL; std::uint64_t aWandererF = 0xA992755E0ADD1AA7ULL; std::uint64_t aWandererG = 0x97C2CAD46EE21E3AULL; std::uint64_t aWandererH = 0xD0E65C80978F72B0ULL;
    std::uint64_t aWandererI = 0xAF8493A7D93E1C71ULL; std::uint64_t aWandererJ = 0xDA17E077892BF263ULL; std::uint64_t aWandererK = 0x9BC9960449402F33ULL;

    // [seed]
        aPrevious = 14899610885667512365U;
        aCarry = 11359488435100366953U;
        aWandererA = 17304967828907054338U;
        aWandererB = 14307597561831732695U;
        aWandererC = 14207873721529694269U;
        aWandererD = 17136989803877570161U;
        aWandererE = 9468072714242373283U;
        aWandererF = 17585301963529917381U;
        aWandererG = 11138572522031336149U;
        aWandererH = 11916056453882036676U;
        aWandererI = 17865704469230161205U;
        aWandererJ = 18112411894101218521U;
        aWandererK = 17630840783573601262U;
    TwistExpander_Bellatrix_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Bellatrix_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 12 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6069; nearest pair: 493 / 674
void TwistExpander_Bellatrix::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 403U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 0U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 961U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3865U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3891U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7227U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 609U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6823U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5440U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7087U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5935U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7548U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1041U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2868U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3311U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6670U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 491U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 379U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 313U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1013U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 946U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 948U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 110U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 368U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1431U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 374U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1183U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1319U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1980U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 446U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 524U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 317U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1445U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1258U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 894U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1890U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 12 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6074; nearest pair: 515 / 674
void TwistExpander_Bellatrix::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7378U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3083U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7580U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2814U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4881U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3901U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6392U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2800U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7853U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1476U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4132U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6171U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2754U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5639U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7225U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6775U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 422U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1337U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 27U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 356U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 498U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1967U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1332U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 683U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 257U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1943U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1223U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 51U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 962U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 707U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1191U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 588U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1580U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 409U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1285U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 2004U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseASalts = {
    {
        {
            0x98E0BF90AB677275ULL, 0xBBAD84BF355349ADULL, 0x935A2CED55BE8CB5ULL, 0xC63C616EC5A6994EULL, 
            0x296F0418B05AAE54ULL, 0x4B8C9F628B4E4ED3ULL, 0xA6B73E788BE64C77ULL, 0xC2729C8FF3B6F8DEULL, 
            0x87F64B1DF183CF11ULL, 0xE808882E679EFFE6ULL, 0x0EE63D3BDF443A5BULL, 0xD8E600F93D5387A2ULL, 
            0x318D9A3E9C91621FULL, 0x5555C629EE8E5F51ULL, 0x4BAE9243E8005C0CULL, 0x74D7726A7AB62503ULL, 
            0xE644F410032D241DULL, 0x3345896FBF123DA4ULL, 0xD521D9FACC761BE3ULL, 0xA5A8CE10C0484070ULL, 
            0x12FD44EC09E52DF6ULL, 0xE91EE398DAA5C1B6ULL, 0x32494832C5165764ULL, 0xFB52CF854262F6DCULL, 
            0xE31B3295BD1F99FEULL, 0xBD79C8BCBE353545ULL, 0x1984D20ACB34DB57ULL, 0x72E74F14D698F966ULL, 
            0xC181B9FC50E3F57DULL, 0xF25D9F3DAA7195D5ULL, 0x04379E61CB731FF2ULL, 0x32E0A39B45F98E39ULL
        },
        {
            0xD8BA60BE87F142B4ULL, 0x5A2E085D7CA87E5AULL, 0x951F0EBD274137C7ULL, 0x06643A50F060050BULL, 
            0xD37036843B17D956ULL, 0xC4323A795C5B894EULL, 0xB7925A4DCA30AE5DULL, 0x0638A2CDD0EE43FCULL, 
            0x75024454CBC292B9ULL, 0x83E38D84E21BEBDCULL, 0x1B1159F2C22BF438ULL, 0x02C6D631AEDDCF90ULL, 
            0x861A8BFD73488077ULL, 0x98BFB47287AEE9F2ULL, 0x2590E5C699C1345BULL, 0x84E19B8C92CB48F6ULL, 
            0xB592CD360ABDEFDDULL, 0xB12AC43B9B2BB090ULL, 0x09735865F30B8E6BULL, 0xB038EA3A7B774FDDULL, 
            0x5F358DBEC8166056ULL, 0xB48829FF07894188ULL, 0x9FEC255A9C949AA3ULL, 0xC4D96179138AD024ULL, 
            0xEB8DFF85FBE1175EULL, 0x3A785EA0815A41E1ULL, 0xF8EE683BEE027AA9ULL, 0x21ED2D7A76A7DE2AULL, 
            0x77C8ABA800729EABULL, 0xBFC69CF80F86D33BULL, 0xCE3DE4D6D8599908ULL, 0xCE69929324A7F196ULL
        },
        {
            0x5A1DF485CCCC546BULL, 0x8CE4AF8FE26EF9CBULL, 0xB9AE146FABA8A3D0ULL, 0x38A1B1CB414D5FEEULL, 
            0x26D3877DFC436F55ULL, 0xD5E65D41619C23E3ULL, 0x43B31D2BC5365BF6ULL, 0x29C92A06F575332DULL, 
            0x9380F1B07A638F17ULL, 0x8D828103A825C47BULL, 0xE3C00E3D6904C11FULL, 0x617E419B12ADC55BULL, 
            0x89A7117212C030AAULL, 0x06CAAC9A692A87ADULL, 0xC170D1D0957C4BE4ULL, 0xF22A58F24B7AF994ULL, 
            0xA6293F7086950451ULL, 0xA95FA9379EBB6755ULL, 0xD4A3895C6EFA92B9ULL, 0x956167B08039DAD0ULL, 
            0x21DF2EF264C6B92AULL, 0xA6548DD6786AB9C0ULL, 0x4F5D0267A4B43AE4ULL, 0x08665A26CA11FD89ULL, 
            0x0F96DD68396104ACULL, 0x7E9A7B338657FE87ULL, 0xCA14870ED136AA0DULL, 0x0662FF6E88C897DBULL, 
            0x667B40DB033C8CC1ULL, 0xC9D4428C80492B04ULL, 0x7F75BC0D4F8C993CULL, 0x6BCC20A1499B8B35ULL
        },
        {
            0x820CA85A508A31A1ULL, 0x4F7B241E49A0C358ULL, 0x9052DD278D7B3765ULL, 0x0EDA702746003FE1ULL, 
            0xC96B5BAEB769AEA0ULL, 0xB65FFA347042B927ULL, 0xFB9DE3AE782F2DB2ULL, 0x53A146F7A3743F27ULL, 
            0x9F3459DCC7039832ULL, 0x0A8C4192E6EA3E3DULL, 0x5F0F5ACE0B660EBFULL, 0x9F01A748DD00EEA1ULL, 
            0x9C39FF97578C65A3ULL, 0x60F20D65A11637C1ULL, 0x0C50FA2A9F9FA630ULL, 0x11F09C60AD063D41ULL, 
            0x8944CD86624CD082ULL, 0x845A6EBA2A8DB6B3ULL, 0xFFDFAFE2B1851D36ULL, 0x89C3A90C4435FB73ULL, 
            0xE4F49F0B739709ECULL, 0xBEB1CAD5ECAFB53DULL, 0x220B06BAAEC3ED8AULL, 0x8914816D9D5168C0ULL, 
            0x77DA9823CDFEB0E3ULL, 0x3D8ADEBE06D69ACFULL, 0x778D49B878B4DCDBULL, 0x5C59A845CC8DA23BULL, 
            0x373BEE4A519F281FULL, 0x0B68A0EE36E5125DULL, 0xDE75E9EA70D1F8ABULL, 0xFD4DF60FD2194DA3ULL
        },
        {
            0x7B12C45E8F4DA053ULL, 0xE4910AC2B743DB74ULL, 0x09C096ADF41CA35FULL, 0xAEAD2F21E3C86233ULL, 
            0x9486E6AEC0BDA697ULL, 0xACD9FFB19DDCDE75ULL, 0x79AB40B3724083A6ULL, 0xD7F1CC1A3E6BDBCDULL, 
            0x43566939064EC963ULL, 0x726883D3EF624838ULL, 0xC7BF68C5EB48581EULL, 0xDFB994ABAED4CB01ULL, 
            0x9FC013A8EE2C370BULL, 0x112E0126EF77EEC3ULL, 0x23B2E90AF4A2D86EULL, 0x57C4020A33F80E9BULL, 
            0xBB571EAFE30E5E4BULL, 0x2EF4C7B4593DD549ULL, 0x317C280C076FCE17ULL, 0x19132B93E1521151ULL, 
            0x3D9C54737610CEC1ULL, 0x89408488C9F624CFULL, 0x50DCE08F747FE0A9ULL, 0x90A2A7C2C98213B1ULL, 
            0xF485E90A746116F7ULL, 0x4C72F761EF7D7CACULL, 0x37258C3DB8652F61ULL, 0x6E725E0200534F7EULL, 
            0xBE54E5A1938A12ABULL, 0x34A58FD2AFEC5560ULL, 0x81DA44B7D29A7015ULL, 0xFE8B4B3BF04268CCULL
        },
        {
            0xB99A8EC2E8678F52ULL, 0x524E2232820E731DULL, 0x1B7F9A56FA40A29CULL, 0x67780C0D639A955DULL, 
            0x03367CAA84584B6CULL, 0x63CFF3BCB0696110ULL, 0xE6BEA294567CD289ULL, 0x3D420C735FCB7D8EULL, 
            0xC26C911B28665EF8ULL, 0xA5F8C57D7D8C2A19ULL, 0xC742644FFA82493BULL, 0x3C2E71A52289FF8CULL, 
            0xFB114352B3C946F0ULL, 0x9984E2F11DA2A13CULL, 0x7DC30BAE0A9FCE4BULL, 0xE2F18784905D7AD3ULL, 
            0xA77B7F43F7FE8BB3ULL, 0x6A56ACE6278217DDULL, 0x137B83682EFB3CCFULL, 0xA10661A016369C55ULL, 
            0xD91A1BA585283415ULL, 0x12DD22E4D94C042CULL, 0x6A54BF968D5D2A3AULL, 0xE245E3460B31034EULL, 
            0x61C9E62920B1ABE2ULL, 0xB708377D7E5D37C3ULL, 0x3167587A3B642A7BULL, 0xDF4BE6DF1ACE8863ULL, 
            0xDD2CED64B8137E7AULL, 0xCD4AE6BA4E96C11FULL, 0xCD8A48188A02480FULL, 0xE621A3E12DD686BDULL
        }
    },
    {
        {
            0xFD79BEF6403E4DF8ULL, 0xCBC21EDDC4151C41ULL, 0xE4AD3E33D3B5B8EAULL, 0xFC663A346D7434C2ULL, 
            0x2AFE5E797C7B264DULL, 0xD0F75FD070CF224FULL, 0xD3FFF2D966395CCFULL, 0xE3C3326B2611A58FULL, 
            0x29F3A0FE8A112C6BULL, 0x6F25CB4A89CFEC15ULL, 0x5A19EBB32C8A947AULL, 0x73CBEB20ACE5E503ULL, 
            0x415045273515D00DULL, 0xC72E4C5DD489774CULL, 0xECCCEABFE84406CCULL, 0xFA122AD63E3C7179ULL, 
            0x9BD4FA70441BE4D8ULL, 0xC505314B91A43F8FULL, 0xB3470F69A52FC5ECULL, 0xF1053BD355E0B45EULL, 
            0xCA0A90D530A537B3ULL, 0xFCE1D20FAD84AEFCULL, 0x036591D0AE0149C7ULL, 0x4E5CF0D6F0183CA2ULL, 
            0x9B5D8C2E417C2662ULL, 0x5EC51BE07C9978C0ULL, 0x690357B648238C90ULL, 0x472E2DA33C196FB8ULL, 
            0x2AE8C00C9283CDE4ULL, 0x8AA98D99875C2E09ULL, 0x988372091F7B8D86ULL, 0x82E07AB79E14D8C3ULL
        },
        {
            0x69DB2F247879072BULL, 0xCB76979767DC71CFULL, 0x8040AAFAA9C70FDAULL, 0x2A70C1FF0BE03F15ULL, 
            0xF7082969E051C1C8ULL, 0x0FC5665DFC68E806ULL, 0x0C9E5442EAD21F85ULL, 0x0F1A83643640DCF5ULL, 
            0x3BC31519E46A2E9DULL, 0x92E8F4C9958710D6ULL, 0x3BBD5F94D5F07453ULL, 0x9CFDC1467826E40FULL, 
            0x1441EF2E9F2DBA27ULL, 0xADCA334CFA39DAC4ULL, 0x251122D9C6D962E9ULL, 0xA92635CCBF70F2ECULL, 
            0x14D715615D0C5BFEULL, 0xF9E39203CAB169CFULL, 0x1E7AD44347858795ULL, 0xB9B60F6F9422303FULL, 
            0xCEAA98FD477FD12FULL, 0x6CF5707DF488BD21ULL, 0x41F77D85BB88CAC5ULL, 0x959A9A8CD2153A0DULL, 
            0x3B6E09C83F043B8CULL, 0xF7F1562535C01B9BULL, 0x501CB072F4419EE3ULL, 0x4704E7F790DB7F5BULL, 
            0x7BF9E3FF56B78207ULL, 0xE477DE37F8BBA155ULL, 0x5D441D0B225E4FEBULL, 0x5AE0433C508FD544ULL
        },
        {
            0xCFD14DB56EBCA7F3ULL, 0x820A900FE3F97F54ULL, 0xD57DEBB399242DE4ULL, 0x6397A2F64EB42768ULL, 
            0xE6B931551E13F53AULL, 0x8BE348F5098EC784ULL, 0x81E2E42B24378AB2ULL, 0x4E7000F120CBD34BULL, 
            0xD19046D4A7B4EF99ULL, 0xFBFC1E97592D0176ULL, 0x64B3DB9F85BB99A4ULL, 0x74021DC717121320ULL, 
            0x5895C3A8BC4D159EULL, 0xE7E651ABD03A8A6EULL, 0x058D74B13716463CULL, 0x163B4D3F8A1B3151ULL, 
            0xAE70D8FAB54E74E9ULL, 0x40DDA3A97F5FE3ECULL, 0xEEAC1B2F6D3EEB25ULL, 0xA1AA9D6040FBB641ULL, 
            0x1D8726B8888928A0ULL, 0x6DED5E3820121617ULL, 0x3A67D6608C84470CULL, 0x670E5ECC9D9781B9ULL, 
            0x88B31AAE2E9410A1ULL, 0x1FF37B7ED74BB9DDULL, 0x6B9AA76573B3FE1AULL, 0xDF5200323C8D7416ULL, 
            0x15F8308641CF8FE3ULL, 0x4911116A49644A25ULL, 0xB717976713268E68ULL, 0x179534E120C3727EULL
        },
        {
            0x8A3DDD7E03C07FE8ULL, 0x4539F01580BA28A0ULL, 0x4CEEA4195C43C3CFULL, 0x478BC1611C39D5E7ULL, 
            0x740266C0463D35FCULL, 0x2FDD32E93646F44FULL, 0xA136317DF0115996ULL, 0x690C45432BCA88C2ULL, 
            0x44C0A1B7011FC4B3ULL, 0x7760E379ACB90856ULL, 0xE9D814A7C06F992BULL, 0x001CC417D2EC47AFULL, 
            0xCB593E94CD486AE2ULL, 0xD20CFBEEAB92D6E6ULL, 0x953A885D4087EF04ULL, 0x938D021340F054F0ULL, 
            0x940E18CC99F21AB3ULL, 0x10ECC0C73B94ED20ULL, 0x3470F16BE7A4B914ULL, 0x9A48D03D4A6A32A9ULL, 
            0x880CB498C12703DBULL, 0x063775FAC6837DC1ULL, 0xA55806526A5A6211ULL, 0x8CFB9E554789F980ULL, 
            0xA025D347617E2027ULL, 0x1BFD54AB43EA73F3ULL, 0xC6E20ED3A66D6A75ULL, 0x04AB2CEEC9CBA13EULL, 
            0xF4677AB6D1081387ULL, 0x3E3D30A2C1187E23ULL, 0x7A493CA9EAF47298ULL, 0xC54062651D5DB1D3ULL
        },
        {
            0x937EB635700A82DCULL, 0xEF5DFFAAEA89F92CULL, 0xC322C34186545501ULL, 0x165ABBB495094FD7ULL, 
            0x28ED3C08D2CD20C4ULL, 0x9EBC12969DEA757AULL, 0xB62DA3EB067AC62DULL, 0xAF0CBD236C8F3A9DULL, 
            0x7D08F795486360CEULL, 0xF8C40CBEAA406DC9ULL, 0x1270C88644A6999BULL, 0xF58692A399A118E9ULL, 
            0x8381B796DC6D90FDULL, 0xE390C6AE9F7CD986ULL, 0x1C347B4779568FA6ULL, 0x49859044C9ED000BULL, 
            0xB99F0142A5C23553ULL, 0xACC0161CF85E68F1ULL, 0xAEBF499097BA590FULL, 0x61DE2CD1AF26A8E1ULL, 
            0xCB46EB29C34A1E1EULL, 0x9859B4DBC3821F39ULL, 0xA7D2FDE98B30D091ULL, 0x08A4CE20F24E64FBULL, 
            0x9F7717B6D9478429ULL, 0xF754E32266CB08B1ULL, 0x1D057FE6B5F746CCULL, 0x329F2FD6775F9AA0ULL, 
            0x55366F65A9D25EE4ULL, 0xC20FA602F6778598ULL, 0x561E7EEBE83F4CF3ULL, 0x8F8766DD95124CC2ULL
        },
        {
            0xC6CD2683BF40421DULL, 0x2A03C883AB64FB8BULL, 0xAE5A77488E13289BULL, 0xA9FBFA5FBBE1B94AULL, 
            0xD159F5573DD8DFA2ULL, 0xD91201D19E692703ULL, 0xBA1B4323D491B886ULL, 0x6402B3FEAC8FDF23ULL, 
            0x10F3B0705587C635ULL, 0x0336F4AFAA9C05D4ULL, 0xC4AA4B8839269891ULL, 0x1E55E174E0F3BD78ULL, 
            0xC1BC3583150C07FFULL, 0x31E6148D357A91E5ULL, 0xBB964A44CA12874BULL, 0xB470AFDC11C8755DULL, 
            0x0740614A1E51F361ULL, 0x48BC1C5F20F4AE6EULL, 0x2E7EF6E680D716A2ULL, 0x537EE21B6279CB38ULL, 
            0xD6BE99F3CDBC00EAULL, 0xD0B2D7358BE0B259ULL, 0xDEEDECC4DB37861FULL, 0xE012EDC13A84393BULL, 
            0xD100FB88785944ABULL, 0x85E895ADF2CF6C16ULL, 0x47C372585778E05AULL, 0xCF63536749ADDBAFULL, 
            0x29ED61E253C3811EULL, 0xA07FA639CA07EF8CULL, 0x48BC5BEFBAD4253DULL, 0x987DEB5C0D8F1D60ULL
        }
    },
    {
        {
            0xA01E7FD97E7D4D23ULL, 0x942A2062CE7481C2ULL, 0x3B2F19A525EDF135ULL, 0x6C60B55FF71CD448ULL, 
            0xA4111A30201E8FD0ULL, 0xEE3E1F584A9ECB36ULL, 0x28A446BB2F9CFCF7ULL, 0x0EFAE9181AC28421ULL, 
            0xD2659E6AD71AD131ULL, 0x7DAA0A5BA8F37975ULL, 0x61DA0DB61258BDC3ULL, 0x16DA34462252873FULL, 
            0xD85D685051547690ULL, 0xCF0B49DD472EA4F2ULL, 0x7A7F714E4D36488DULL, 0x336198E63F76476BULL, 
            0x0E685E890F81ED18ULL, 0xF2F43DBE6AE90585ULL, 0x289A5D26EF2748B8ULL, 0x5AB3D5452ACDB2ABULL, 
            0x70998D1CBA63FF27ULL, 0x6D06C762747C3D4FULL, 0x9CD2F385A1BC580DULL, 0x8DA4446CF4F96B14ULL, 
            0xAE6A378153C09618ULL, 0xBAB54458F5E088D4ULL, 0x93E132DF6A139E34ULL, 0xAAD9B42AEA420EFAULL, 
            0x6369F78BD5539124ULL, 0xB5BDD70857F76C34ULL, 0xEF079CD3D30206A2ULL, 0xEE8E7C6680C4C09BULL
        },
        {
            0x75A4D2572AFCEE8EULL, 0x97AEC151DBE976F8ULL, 0x2EA7903D9625FC63ULL, 0x405847C177F839E3ULL, 
            0x0CBF02283A948742ULL, 0xAC82C2DA7C0AC99DULL, 0x5FD4736E47A1BCF4ULL, 0x2AAAEC5E04F2A6B9ULL, 
            0x9B2234274C18B2C4ULL, 0x2FB7FB9B8DD92445ULL, 0xA55D13CD51ED10A5ULL, 0x3E0173534898CDE3ULL, 
            0x7C483EF043DB7E69ULL, 0xC5E9C72B9BE5C783ULL, 0xBC54E05C51BAE961ULL, 0xAA4FCDBC8F6F5369ULL, 
            0xDFD41C90A00FADC3ULL, 0x8F17DCA1930DCFEAULL, 0xA93DAB1386AEA314ULL, 0x334A788D1515DC46ULL, 
            0x945BEAC1DCA3E095ULL, 0x3EBD8B662F2CD76EULL, 0x0878764FD06325F9ULL, 0xA4AA95DDD0875631ULL, 
            0x7F75E21854D5A5A6ULL, 0x98E128780B21CA97ULL, 0x37FBD0D4855644BBULL, 0xFA3F9D4EBB291F7CULL, 
            0xAD8DD97A14AC6055ULL, 0x72A4EDF3489F8692ULL, 0xB0DCE1C199F606E9ULL, 0x556C6C99D199DD04ULL
        },
        {
            0xA8E6750A1345AC86ULL, 0x066F0BA0388D681DULL, 0x908C5C616770B2B8ULL, 0x3FB9A23F0CEDBB78ULL, 
            0x01C7DDCEE00C3963ULL, 0xFDF09F997D86010CULL, 0x15B2E71C10366B32ULL, 0xFFF79CA64A077DE0ULL, 
            0x8A2B69B12812B8A5ULL, 0xBBF08F60BB756952ULL, 0x310FA1A2E347DDAAULL, 0xFDE49374218BB49FULL, 
            0x8CA7D2B092511154ULL, 0x99467BE8084D3EE4ULL, 0x720A24FDB2B61D58ULL, 0xCEFC66FA1ABF9D72ULL, 
            0x32834AB0C7EE06A7ULL, 0x330271708A89277AULL, 0x37F5F004D5FF16ACULL, 0xE2DFF4ED275F0101ULL, 
            0x571CF3C2C7DCEC51ULL, 0x082582618C505C9BULL, 0x23281689A45E53EBULL, 0xD3327505C01C250EULL, 
            0x1B66C9D337D35664ULL, 0xCFFAFB4593C5DA74ULL, 0xC22531BA58EC7AFCULL, 0x6407596C49F83285ULL, 
            0xE2AC95B6C5E3F059ULL, 0x53F5CF15541C9C6DULL, 0xB53A4318BB2E522DULL, 0xE918DC37A232997EULL
        },
        {
            0x5590ACB1116A5464ULL, 0xAFF272A26793800EULL, 0x960CD4CE8E9F96E3ULL, 0xE629B6B1F0B9D7D7ULL, 
            0xBC87431A01F0AEA3ULL, 0xA0DCD7A7E8AFFA44ULL, 0x4C38437FA5C34384ULL, 0x3A21DBC66783906AULL, 
            0x93C28A28528D999EULL, 0x2E1F36C47A7079FDULL, 0xEC0CB393F2DB8790ULL, 0x8E922180DCC9D436ULL, 
            0x8C1268E7FC017431ULL, 0x73F62A5B9AFAE922ULL, 0xA02B2CF3ABC2BE74ULL, 0xE5C4FE19C0586DEEULL, 
            0xBBD089130B9A9C02ULL, 0x0FD7E266ACA1D38BULL, 0x8702D9E22C3870D3ULL, 0xC967277F61EFE9C8ULL, 
            0x6F265737EB80B59EULL, 0x9B96AD8944A061E4ULL, 0x368401F149BE721DULL, 0x7E537AE6E1C8E06BULL, 
            0x9696FE84C02A0BB6ULL, 0x17B0B7B7E3BE5A8CULL, 0xFF1919D38B87F1F8ULL, 0xD1645D7706C94DDEULL, 
            0x38861EAC4CEBD4EBULL, 0x2FF257DAF988B818ULL, 0x3BEBDF22D9FCAF44ULL, 0x99E59421EC80D6E7ULL
        },
        {
            0x3B6CE6D15F925094ULL, 0x6B02F29D6E6E98C4ULL, 0x8652D0551D0AA10EULL, 0xE7281215F991D29CULL, 
            0x7B841DDF8AE510D7ULL, 0x3931AE6C60EDEC8CULL, 0x87368D51F1B593E8ULL, 0xF31F579DF8935856ULL, 
            0x88577EE229D49DA3ULL, 0x57CB307E55394CB9ULL, 0x7D7410972C3C7F91ULL, 0xCDB4EA1DDEBC01DAULL, 
            0x66561AA6B6799011ULL, 0xD6171D6A95ED1B40ULL, 0xBB52D15FF1B387B9ULL, 0xCAB250EE039B29B6ULL, 
            0x06CE1206A01B6706ULL, 0x4FD87212F5B83648ULL, 0x5A1B8EF7E6A7B079ULL, 0x7EBB18BF500B2256ULL, 
            0x9B41494AE80C6CD6ULL, 0xF916FFE55C373C7CULL, 0xFDB5C7B529D2992AULL, 0x3E7BD5DE186EE03AULL, 
            0xA2B9459CD72BF8B7ULL, 0x502302892EDDAC46ULL, 0x18F053308AC85BF8ULL, 0xC605D468007773A8ULL, 
            0x8A1847A93AB7EDC1ULL, 0x1C3A12E027F2CD62ULL, 0x586C729492D9697EULL, 0xB684FD9CC632D816ULL
        },
        {
            0xF52B94453E4BA3E7ULL, 0x3154F231DE522BFAULL, 0x4C8BDB80458DC8ABULL, 0xB9D44B8803B333C2ULL, 
            0x6298E5C2A4D9F691ULL, 0xF4010C2866FF78E0ULL, 0x241A6F0C523C28CBULL, 0x7A5B4159D983EDABULL, 
            0x2CC3203D9A05CF27ULL, 0xE9AE143D6E23DB94ULL, 0x5306CF6B11E8A5B8ULL, 0x3F7439D1088CE0FFULL, 
            0x32AFF110EF480C79ULL, 0x8B07422B63787E4BULL, 0xA31E03642E18E7A0ULL, 0x5B00BA59B68EF71FULL, 
            0x6B3E375B41816622ULL, 0x28AF51250AB02DA7ULL, 0x3CAD7C7B1261F226ULL, 0x671F7EFE0B3F766FULL, 
            0x10AC40B1CA371907ULL, 0x64B03D55D8D26E5CULL, 0xFBED63301E56A24CULL, 0xBF5FBFB055175BCBULL, 
            0x87F02232ED819DA6ULL, 0xCDFE1FC362F1B595ULL, 0x8FF24E6D0B1EBFA0ULL, 0xE3930196EE081CC7ULL, 
            0x317BABAA9AA99ACBULL, 0x7DD1C5464025064BULL, 0x7D4A31A16A3FF18AULL, 0x98B1071CB5A2E2DBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseAConstants = {
    0x421277AE7BA74EB9ULL,
    0xEB8C32E0EFD319EDULL,
    0xD586CB8A7F1C7F3CULL,
    0x421277AE7BA74EB9ULL,
    0xEB8C32E0EFD319EDULL,
    0xD586CB8A7F1C7F3CULL,
    0xD9F7F76E2C18A1ADULL,
    0x2CD7C1F2D3633545ULL,
    0x5B,
    0xAE,
    0x8C,
    0xE4,
    0x94,
    0x26,
    0x0F,
    0x0D
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseBSalts = {
    {
        {
            0xBCC1C8BD27C8856AULL, 0xB6B146FB6F6EC981ULL, 0x5597E148550DCA74ULL, 0x30272313EEFD6BDEULL, 
            0xC11D73FAB2CD2F88ULL, 0x6EF5CD3142CB68CBULL, 0xBDD064B2A1D2683FULL, 0x7FD642E14EE98C07ULL, 
            0x013E6CB80FF4C4C2ULL, 0x8B1C7F404550FC7FULL, 0xC227EB5A2F91B656ULL, 0xEFA0CC1BBBA42C71ULL, 
            0x1EC08D2E0C8FC4B9ULL, 0x03361ABC23570FB3ULL, 0x91534514AEA55256ULL, 0xDFE829065BB14D65ULL, 
            0x9FDD065FC5982D33ULL, 0xEF0B2FA13ECA0A65ULL, 0x81E8CAA26D33FE96ULL, 0x492CA86D71BB940DULL, 
            0xFB6E5ABC707E6F30ULL, 0xB993DE7C9CFC6B8FULL, 0xFD522BA6969B5027ULL, 0xA2A05EB0E1780757ULL, 
            0xFF406E37016BA3A2ULL, 0xDA71A142DFB0A4C2ULL, 0xC9680700CCD5B4DDULL, 0xD12C4EFB4CF77D35ULL, 
            0x7669D416B47F14E5ULL, 0x5F00D445B40D957CULL, 0x991DEEAD0E2BC62CULL, 0x494F2F8DF41B4A09ULL
        },
        {
            0x76B3D390DD45C44CULL, 0x1B93CDAAD0FD6ACBULL, 0x0A35ECF5F4BD237BULL, 0xB14C3E873E5BE007ULL, 
            0xFAA8943AB5A3FD00ULL, 0x289CDCF62EC78A74ULL, 0x05E4AA76C2957964ULL, 0xBF79105B6EC709BDULL, 
            0xD566EA17A277E218ULL, 0x5FDF9EB80432A5BFULL, 0x567F713EFB7B6402ULL, 0xC1F52184723A713FULL, 
            0x0F80D5CBA280F46CULL, 0x94E4A0C636401A2DULL, 0x04776ADC472C12CEULL, 0xCF82807E618E03E4ULL, 
            0xC147CEB0CA120C6AULL, 0x1E9ADA12CAA6ECBBULL, 0xAB6FB0CD4961882BULL, 0x19CD47FBE06557BEULL, 
            0xA4DC67F58BE1C3C2ULL, 0x11CF49B291269FC7ULL, 0xA7FDD34CB684FE7EULL, 0x8BF58D9A7277B199ULL, 
            0xF5AF72626D38C5C7ULL, 0x4FC789013535F014ULL, 0x966958D7716FF035ULL, 0x5638D7A0E774ABE9ULL, 
            0xB212CCD2568B8106ULL, 0xE30DF8AEA4BE27E2ULL, 0xE8CBF0E7BCBDDE70ULL, 0x64F373E9A09BF0A7ULL
        },
        {
            0xA9DB6B085150AC81ULL, 0x93D6F88AAF48AA75ULL, 0x6A81C895C431EC73ULL, 0x54BCEAEDA2E0E6D5ULL, 
            0xD7ABE44CA76BF5A8ULL, 0x298E581BC6C1D190ULL, 0x65224EC6D0CF3E5EULL, 0x4F185426986AABB8ULL, 
            0x81B078F8CA3EDCB0ULL, 0x40B3254F9F4A33BAULL, 0x1D25C74689EB8585ULL, 0xFB5033AE7C46E97AULL, 
            0x65B10A86BD5E96B6ULL, 0x37035A74ED7AFE40ULL, 0x2C56E30DB00718F2ULL, 0x5384CE736EFA49F6ULL, 
            0x43D5351080D9852CULL, 0xCF3FBF79B5ADEF39ULL, 0x8A760449347C34BAULL, 0x390080380A7C0BA7ULL, 
            0xB9FDC3A420303F92ULL, 0x78C64B6FA1ADDFE5ULL, 0xC9AB39B2D4870CB1ULL, 0x1C57C13C17B76096ULL, 
            0x878903802D86D0DAULL, 0x2966C2AFCBC18E82ULL, 0xAB7AD18CB4D5539DULL, 0xBDD508D70A3FC6C9ULL, 
            0x2262327A86A10BDCULL, 0x5A0E5767060C2142ULL, 0x877B04A93285CCA3ULL, 0xC6ED14BAC05364B9ULL
        },
        {
            0xDC5621793B6CE204ULL, 0x8835484B8D962907ULL, 0x7EDFE180D43B2406ULL, 0xBB74FBE461CF8222ULL, 
            0x78F0D32E033576A2ULL, 0xD4D35AFE12B4365DULL, 0xB3ED2E18FF4EE489ULL, 0x311D2F2A9F28611BULL, 
            0x5A7C567EDBCE9265ULL, 0xA6FEEBE662A0D252ULL, 0x0A021EB4BEA7130DULL, 0x74DFE0AF5C23140FULL, 
            0x7722C4172AA77A5EULL, 0xBFE50DEF6CC35F99ULL, 0x8DC9CDDE622DCC69ULL, 0x25CE4ACD2FE9F1C4ULL, 
            0x80B73DB692858D1DULL, 0x104226148D33FC8BULL, 0xC5C73B95CADA9A7CULL, 0x053199831A6C76E6ULL, 
            0x3F2A3425E5ED568DULL, 0x9AE99145EB79A529ULL, 0x68A5CCD40AA7D822ULL, 0x2286BD7B2CD7D90AULL, 
            0xDF28AC7DF68F7DEAULL, 0xAB7C6C00B79DDD00ULL, 0xF4A168D7FFFF09A9ULL, 0x03A58D01F8EE27D4ULL, 
            0x61C18715CB74E8A7ULL, 0x4E66F3E20217B7A5ULL, 0xCCACFA0D649FA5F5ULL, 0x08CB0DEDAC0F642FULL
        },
        {
            0xD28706FE13A85251ULL, 0x13CD42BC28F46999ULL, 0xBF2C81DF32375E1BULL, 0x4D6F93EB28BD0718ULL, 
            0x14DCE18EEFF1ECFAULL, 0x808A617226E52DC6ULL, 0x4AA0F8988D9133D8ULL, 0x2AB4B8DA8A49A706ULL, 
            0x47AE37067BFCD991ULL, 0x27AF791CBB4E3B1FULL, 0xB66FF99CB2D8F32FULL, 0x56693D1E5B29307CULL, 
            0xC087FF4FB3A8F6C4ULL, 0x08F6C15D8C6A2CEFULL, 0xD61B1A89C4A0843EULL, 0xC73BA8FB5945FF60ULL, 
            0xA9D3A7F17E5BDB38ULL, 0x91443771064F3C1BULL, 0x4FC3723A7866E411ULL, 0xCE3DD9491F0BFFAEULL, 
            0x7C6C928BA353BB09ULL, 0xA2766B78511AE478ULL, 0x6F84CF7029E31AF3ULL, 0x16E5F0D55078F609ULL, 
            0xFB6BF9C2EB2D655EULL, 0x5030DB9626CCE124ULL, 0xEDF0DDB2F5C0D8A8ULL, 0x39A55A6D0949292CULL, 
            0x7F72A3235AF13FE8ULL, 0x513689568A2DCC58ULL, 0xFE461A50CB7E130EULL, 0xCDA2257A31DC1763ULL
        },
        {
            0x1417355544585E62ULL, 0x6DE70D59697A74D6ULL, 0x0175B3E444DD81A6ULL, 0xF8B94EB28BF3F371ULL, 
            0x6E288C1AA4C2EE30ULL, 0xE2FB6A998FA92D14ULL, 0xA7A0406D299AEE58ULL, 0xD20A7D47D1A12F14ULL, 
            0xD4443163C5DFAC58ULL, 0xFBBDD0966AF9DE59ULL, 0x636A4AECFFC60F73ULL, 0xE4552C5DD340993BULL, 
            0x8C3353EA71556A1CULL, 0x1AE2947C2305B9F6ULL, 0x640FD9708CA4847DULL, 0x48E429496CDD7BEEULL, 
            0x9A772919260ACEF3ULL, 0xB22D4FA701271F43ULL, 0xF088BEF017BD34B1ULL, 0x168B3A368E071E3FULL, 
            0xA883EAF3CF28B94BULL, 0xCCFB448CA89BEF85ULL, 0x481E23DF9E921559ULL, 0x04EA7749B34DDFF4ULL, 
            0x05C59F0EFC8B6928ULL, 0xAAEF7BB6AEAF6053ULL, 0x09DF41EA2069FC30ULL, 0x5CFF9D5C94B7FB1EULL, 
            0x7E0C8C2D7FAD23F7ULL, 0x1D38805C42A60002ULL, 0xD515D21B8D3CE772ULL, 0x0E944886D4C657E4ULL
        }
    },
    {
        {
            0x967E2DCDCA86D802ULL, 0xDA215798D302D8D7ULL, 0x9A238314A1054F12ULL, 0xCA26B362C0B9C35DULL, 
            0x4CDB3C4BD24B29C0ULL, 0xEA4C2FCF1719CEBCULL, 0x75885D14BF377C91ULL, 0x93C5619A91EBAA92ULL, 
            0x1654F0E6ED46B51DULL, 0xE1C25DCF5A3F9A7FULL, 0x71EBD48E5ADE7AB8ULL, 0x260782F420298716ULL, 
            0x1EE84C7B8A6BB062ULL, 0x5728C557782F4339ULL, 0xBED3B361F4FEADB8ULL, 0x8ADDF9CD652CF663ULL, 
            0x707D8C8576B0ACC9ULL, 0x39CB3F740B02A1CAULL, 0x5AF62F08C17705CCULL, 0xBEA3B028E02824A5ULL, 
            0xD04BC09C99058538ULL, 0xA0B4A6A6327B89F8ULL, 0xCF5CC7BEF597F3BAULL, 0x077781D2723D5C11ULL, 
            0x1C51CC2F86A461FCULL, 0xCE6503BBCB349B32ULL, 0xB1A7742E26540903ULL, 0x602FEDD0E945A80BULL, 
            0x58923BFD69B7AEC8ULL, 0x9758EE3DC0B5820CULL, 0x9E8EF83166988940ULL, 0xEB4B2B920C1AA8CEULL
        },
        {
            0x3B4460C4ABF41642ULL, 0x2C587368A0887823ULL, 0x024275590527B20DULL, 0x4F19A8E5B028319CULL, 
            0x34807AF1D92ED446ULL, 0x257DFF7FA6AF2F32ULL, 0x467C335077073FC3ULL, 0x1B2A12873C4096C9ULL, 
            0xF95E3D47750CF531ULL, 0x18721D3B28CEA827ULL, 0x32DAE008897E9D10ULL, 0x4FDF48A0608A205AULL, 
            0x30CECC072006E1D2ULL, 0xAECA06F73DF691C4ULL, 0xA0F3970D619BCC36ULL, 0x5A7D7B6ADB8CC9F4ULL, 
            0x8DFF3594D7F4D74AULL, 0x6CB88F625DAF4E05ULL, 0x40E1055E0FC9FB71ULL, 0xBD4BA1A1BF8F46D7ULL, 
            0x4FB5399DD693CDB5ULL, 0x0544819125DB95E6ULL, 0xDF6AF47900839573ULL, 0x6ACED16A41DF795AULL, 
            0x0E0E6F5BB99869E2ULL, 0x030D544D8A860441ULL, 0x7DE05A13B49CF38AULL, 0xA71A4AF6258E1BC9ULL, 
            0x94118141D210BCE1ULL, 0x029C70DA797BEA0EULL, 0x6212A8267ABA6270ULL, 0xEF606FB1CD323F9BULL
        },
        {
            0xD0C7CF9DB67F22A1ULL, 0x473FE84845D72823ULL, 0xB4C9D70B2D5FC90FULL, 0xBA8E3B1FFE1A198FULL, 
            0x69C00C14709EAE31ULL, 0x1043074517D615C6ULL, 0xFE38B0F1F703D83AULL, 0x73EBAC7FA44EA8DAULL, 
            0x9DDF0637A0ADC6B4ULL, 0x2697B8639352F32DULL, 0xADFCA2D43A315747ULL, 0xE7B5EF8FA7FC2169ULL, 
            0xF08E66CDD232EB0EULL, 0xE3717047656528ADULL, 0x1421E39050AD615BULL, 0x24AE4CE49ACAFC2EULL, 
            0x51C75CE97695D37EULL, 0xEDDC487AEB48C573ULL, 0x803E4E7F26B16EECULL, 0xEFEF4806B9D07214ULL, 
            0xF2E75C9CF321EE59ULL, 0x10283F1C01D9614CULL, 0x4D7859EA40AF618BULL, 0xB7AA294473757E40ULL, 
            0x0A3B7ECAEBE27496ULL, 0x3A34466D4854203DULL, 0x8A652637174B4B44ULL, 0x420C92CA4B52F2C7ULL, 
            0x8A9B63366634F1E6ULL, 0x47B9466DDADAB8C4ULL, 0x0F05B894DE3CE672ULL, 0xEC2A25B4C5934A90ULL
        },
        {
            0xAAE7849671A39627ULL, 0x55C635F969B54D46ULL, 0x559CAE6FCF7F9C88ULL, 0xDFA67B8FEBE946C7ULL, 
            0x170BFD231693C907ULL, 0x96B0BDBEE86BFF53ULL, 0x51C9452A7A2B2AEAULL, 0x9A44E75920BCE986ULL, 
            0x86CB964F31B0511FULL, 0xE724E17C73F1E7B8ULL, 0x94E940F1BC605DC4ULL, 0xA8A3278E29324E9AULL, 
            0xDD67A68ABAB73997ULL, 0xCBD92DCDEF3FA191ULL, 0xF3DF076BFB8FC3ACULL, 0x59BF1747F7B6E309ULL, 
            0xBF640195E2BFAF8DULL, 0xD32D9212B5DAB5EBULL, 0x57FD0EFC31CBFBDDULL, 0x27CE4FC809734ADAULL, 
            0x5A9C6058C3DD16F5ULL, 0x3466E995669A1739ULL, 0xF505403E42990A35ULL, 0xCB247418310EFB80ULL, 
            0xE33B8145970BFE94ULL, 0xD1AB6F360DD03C12ULL, 0x0B5E1C090267247AULL, 0xC30D5F75F0E0A5DAULL, 
            0x088CD500A0654888ULL, 0x8DF9E769C3726FEEULL, 0x455FDDF28CC86DEFULL, 0x9E6980A20F0448DDULL
        },
        {
            0xEF97955E8ACE148CULL, 0xFF7F17849DD93493ULL, 0x572DE26FF297A4E9ULL, 0xBED3F3EE3E8C2EB1ULL, 
            0xAA6AB7FD84E64306ULL, 0x067DC957619677BEULL, 0x219D669ADE3EF68BULL, 0x265B46CA5BA4A4A0ULL, 
            0x5A55B069B77E7BC6ULL, 0x444E8073221A167AULL, 0x87880711C94EF407ULL, 0xB426465BC72DA281ULL, 
            0x3F39DF688AEB8522ULL, 0x33367E57C976DA0EULL, 0xDB9ED76BC9F88C2DULL, 0x26982DACDC9C077CULL, 
            0x99498F7C61F848CCULL, 0xFB17723482CC51CEULL, 0x013DF9102441101BULL, 0xF2D71ACBEAE1F2D3ULL, 
            0xC7FF58CDC9072EBEULL, 0xC3F474664D6CFBA3ULL, 0x3469E69850FEC0FDULL, 0x4ABDC072D2FFB1C5ULL, 
            0x9E4644E5E398F5D0ULL, 0xB4130AAAB43A4913ULL, 0xB1279D16ADD3BF2AULL, 0x51B92DDD2FB3D6D8ULL, 
            0xDBABD9B27F3A7D74ULL, 0xF7E09B23A7B539A1ULL, 0x84C0464BDB6B0D03ULL, 0xD9C2F8FF6BFD0FE2ULL
        },
        {
            0xEDA1ABB6C4F80ADFULL, 0xD74C1893E09F4A10ULL, 0x3D3532AB220A82DEULL, 0x34E092564A07F114ULL, 
            0xB35678CB3684ED1FULL, 0xA3F399A6F9F076E4ULL, 0x1D2B970BCC16C366ULL, 0xD7194FD099BA25F4ULL, 
            0x686BD8E5E5645C79ULL, 0x9EF2F649D950801AULL, 0xC4857CB3E31B8DA6ULL, 0xAFA1C15E9A30A73DULL, 
            0xB3A4D76883D07612ULL, 0xBF199D8EEFC6C8E1ULL, 0xF106279A492B605DULL, 0x7A3C8DB39BA207A8ULL, 
            0x57B00D62AB443924ULL, 0x253E0AB85CC6AFB4ULL, 0xE093527590D5A100ULL, 0x44998D1EFFFDCB50ULL, 
            0xDA86D659ABFFC366ULL, 0x863D505B30712C31ULL, 0x516A2F59B844D730ULL, 0x397D70104D988764ULL, 
            0x529A5E2D5FFE9973ULL, 0x5D3BE36188E0945DULL, 0x05A0B854704F5499ULL, 0xA6214E6AF6BEAFC6ULL, 
            0x0603E9AD38E92C3EULL, 0x08C23FC148EF8016ULL, 0x6738B16AB8F1DC37ULL, 0x2797028AB69F4E80ULL
        }
    },
    {
        {
            0x371A7C481571BB0AULL, 0x7B1F9074CB900838ULL, 0x0F8F214BBBC49BABULL, 0xF67E037693F3A58BULL, 
            0xCC6583FDBF1D2BF0ULL, 0xA8D69D7AEDB404D5ULL, 0x4B9AA179E90AE7CEULL, 0x43195BAEEF779648ULL, 
            0xB72EF4DBF672B714ULL, 0x31DAE2AB1F8561B1ULL, 0xFA191C9EA467F797ULL, 0x5A8AD4DA7F876D4DULL, 
            0x9488EC3F96701B81ULL, 0x57540FA81B06812CULL, 0x7F1074E03E3210F8ULL, 0x2689CFB703FA5643ULL, 
            0x838E8C506B2D34AFULL, 0x5701D7119105D19AULL, 0x8A6DA89C8A7F5F0DULL, 0x26902451FB58B557ULL, 
            0x861179A7F3A68379ULL, 0x1C4F5868EA05004AULL, 0x0959DD2597427CBFULL, 0xDE6EAAF6B4FF6228ULL, 
            0xE4CE627439172375ULL, 0xB76E2874D865B64CULL, 0x8EF78F6ADB7080DEULL, 0x847AB0CA4BDF03CBULL, 
            0x94AC0CE128F6A3C1ULL, 0xF1C9B111A1056206ULL, 0x0B69798AD4E06921ULL, 0x32FBB49D88C113E7ULL
        },
        {
            0xD5F19A181A9D3E2BULL, 0x181B1203ED2BDD31ULL, 0xD387FD4CD199B920ULL, 0x572F202C16F719D8ULL, 
            0x356C19366AE14699ULL, 0x8571CDF11AA3FBADULL, 0x6542316CEC0B159FULL, 0xD42EB44A5CBC5803ULL, 
            0x793D392B2A037FF7ULL, 0x4DEBA2DDEAF23837ULL, 0x28B419F72A829255ULL, 0x5089CE1984D3F699ULL, 
            0x590E47A648ACECCFULL, 0xDF2F3A15DDEA6814ULL, 0x0324BBE9DDC42096ULL, 0xEBB1361D56F57D3AULL, 
            0x41A6306D614B622EULL, 0x4FE5105FAD53C740ULL, 0x7890C99BC6C63989ULL, 0xC397A023964BEB47ULL, 
            0x0BBA088A16B0FF84ULL, 0x9CF9053D3C649209ULL, 0x9AB7D0FB7904E4B6ULL, 0x3C22DF5E49F1A4D5ULL, 
            0x5083CD254A3832ECULL, 0xCFDD4B975D1275F7ULL, 0x47073CCD0AEC3BB6ULL, 0xA0475DA2380B78F7ULL, 
            0x1E73DD02B12E5BD9ULL, 0x03855356142B5094ULL, 0x663E80775F131878ULL, 0x04E796CD96D53B23ULL
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
            0xF106C21297B5217CULL, 0xF19C3C1FB023BC01ULL, 0x46A6FF17E3062559ULL, 0x2928BF47ABF85944ULL, 
            0xD23FE14E7B8D7C6BULL, 0xDEB2CAC201D92840ULL, 0x5323B4BC272FEE9AULL, 0xB6C2092CA4C22943ULL, 
            0xE7A400361752E114ULL, 0x925BA1016AA13039ULL, 0xF732A8580C138601ULL, 0x44CEECB6B8287FF7ULL, 
            0x48066F145541FEF5ULL, 0x442E77460B45B0CEULL, 0xB32D3D6E3EF9F78BULL, 0xD243FB28F70460F9ULL, 
            0x2632C88E39D88AEEULL, 0xB2F49E20C9ADDCBDULL, 0x61D85297802B8DFDULL, 0x5AD1CF3E4A0BF398ULL, 
            0x35DE43D071DC6698ULL, 0xE70A4C797194B789ULL, 0x74C8F357809926BCULL, 0x68A05D7CC9540B30ULL, 
            0x541786E0929EE580ULL, 0x09108110E0F7FA27ULL, 0x034E1D901DB3416FULL, 0xA98D279EA27DE62CULL, 
            0xA58F8F5C693E0F20ULL, 0xA3526D38275A1196ULL, 0xD915B9E020A90014ULL, 0xB3DD9ADE75B4386BULL
        },
        {
            0x134A8E7CF84C80C3ULL, 0x8B67CB6A183579CAULL, 0x52137B9EDA7FA62DULL, 0x4AAF35C98401515CULL, 
            0x7E5165FFEE3BF615ULL, 0x3E33FB31E0B1F068ULL, 0xAE6C76867DA4C342ULL, 0xCC226FFB91A0C5B4ULL, 
            0xE6F532868F528E27ULL, 0xAD7CC3AB4DBBAE9FULL, 0x0A2090601E825F74ULL, 0xD61A41DBAB12A3F1ULL, 
            0x89E64FB506C3FE68ULL, 0xA3FC52712032E10BULL, 0x912CFC1AE0381E41ULL, 0xEAB81B585883F840ULL, 
            0x8DC50C9DDDE8EB3AULL, 0x4A5846E3D1D7F081ULL, 0x2C7C11E0A31DBBB5ULL, 0xA2DB857A7DE95D06ULL, 
            0x8A10A432377ABEFBULL, 0xF18785A65D0309DFULL, 0xF27995791FD7707FULL, 0xF7DA53AC0F5A1EADULL, 
            0xA264656427E777A6ULL, 0x4CAB9FD89A267551ULL, 0xB348DCC533959E4CULL, 0x787265FA8AF3B9ACULL, 
            0x4D27B9C1B1DDC76AULL, 0x6E4CA7A87FCB3759ULL, 0x139A4A69F377F198ULL, 0x388D3A2229F72B0CULL
        },
        {
            0xBFA1036ACB68536AULL, 0xE1099894DEDB1704ULL, 0x8D54056D86E9EBA2ULL, 0xFFB4D3AD2770CF16ULL, 
            0x8486AE4F93A0710AULL, 0x9F18980FA0882449ULL, 0x909D8471A5585760ULL, 0x9805299DF53AE136ULL, 
            0xA01288AFBD006208ULL, 0xC142D05BCFDC6805ULL, 0x6B83C412660D3408ULL, 0x9177A6CAA6682E24ULL, 
            0x4DDE90AF3B66D802ULL, 0xA678F9FC7AD5E5ADULL, 0x1F052BBE2E784DEFULL, 0x235EE872FC47CEECULL, 
            0xFDBF47E6C67C0F78ULL, 0xE913CA3FC2905957ULL, 0x8CB7C1A0428DE268ULL, 0x7B966A49544B94FFULL, 
            0x4A59361F1037F53AULL, 0x695CC9EF5AA792AAULL, 0x53A78F7D8E447683ULL, 0x592142AAB72DB809ULL, 
            0x61CCD4BD168ABB28ULL, 0xE41145D6AF68D823ULL, 0x4A586A9DCE93ACA9ULL, 0x903ED63175998B5AULL, 
            0x09B919C7CC746EC4ULL, 0x06244B2813FB5107ULL, 0x70474A26E1E97B65ULL, 0xDEE42C17027E251DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseBConstants = {
    0x0BF133A3E95E31D4ULL,
    0x7DB264C36FCE2CE1ULL,
    0xF6EC8AC01544CDBEULL,
    0x0BF133A3E95E31D4ULL,
    0x7DB264C36FCE2CE1ULL,
    0xF6EC8AC01544CDBEULL,
    0xCF19224CE5A2943BULL,
    0x334A72405CC2A09DULL,
    0xA5,
    0xAC,
    0x49,
    0x45,
    0x74,
    0x04,
    0x35,
    0x9A
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseCSalts = {
    {
        {
            0x42DE83F77969E779ULL, 0xF4C4424A35BA24DCULL, 0xB9766F96145B0CF2ULL, 0x6DAA5C754C5DCD95ULL, 
            0xBE7A7D985BDE1E9AULL, 0x7C6E39B8ED67E023ULL, 0x999D455E262FDAC8ULL, 0x6D7152B194826277ULL, 
            0xA7BB457BDEFE5E43ULL, 0xF662EF32D1A50BE2ULL, 0xC102C08256110177ULL, 0xD23C0FE66ECBF221ULL, 
            0xAD2AD93FBDFD1D17ULL, 0x9E17EDB8DE826F9FULL, 0x50A54FE56111067CULL, 0x1FAE5F6BD2E7092DULL, 
            0x47143B9E2286CC18ULL, 0x46E174A2B597ADF2ULL, 0xE3172C553379F289ULL, 0x45BE6CBD19FBD14EULL, 
            0xB877B1A32BB6FB7AULL, 0xC7600DDED16C5F2BULL, 0x4887D070D2ED01CCULL, 0xF269C91C50CAB08BULL, 
            0xDE52405AA5898F15ULL, 0x3AE0BF0874117DEBULL, 0xAB17A96726078781ULL, 0x7B9F64AA4264BBD5ULL, 
            0x4C86F367DDA63699ULL, 0xC77C7CD185B4BBACULL, 0x256810C7D2B32979ULL, 0x327B0307220F31DFULL
        },
        {
            0xDEF39FE81CBACC49ULL, 0xC95AAF727B3FBEFBULL, 0x15DD8DE8DFF3662DULL, 0x7B9CC20F2ED943DFULL, 
            0x507B8F668292E124ULL, 0xBB8473C2477BA019ULL, 0xE8652C36F70AE700ULL, 0x997AEA16B8E15914ULL, 
            0x1BB87B813B67A9A5ULL, 0x739E75D77FF44DC6ULL, 0xBA256CF4DEF370C6ULL, 0x75964D1578D23B18ULL, 
            0x041E4DBF8143313CULL, 0xDEA4A5DDFF517DDCULL, 0xEE90C7FEAD659BA8ULL, 0xACF2D21E16E4FF28ULL, 
            0x4807E5FCB69A110FULL, 0x563B5D0BE9F62EEDULL, 0x6C8394AFA5B691B0ULL, 0xDDA5DC3346102344ULL, 
            0x4FF8EEC247722E5DULL, 0xAA7C3B6ADED2551AULL, 0xDB3CF952CB83FEF2ULL, 0xB56E9C41025D1DFFULL, 
            0x12DECD3144F25FA5ULL, 0x0D0B7ABC39E755FEULL, 0x126D6CA933934F45ULL, 0xE63711672D49838CULL, 
            0x48DF886781BC9026ULL, 0x2F94D37B3EDBBF83ULL, 0xE1401D34589C6AF4ULL, 0xCEA56DDA32E9E2CDULL
        },
        {
            0x8CCF28E520C1A5D6ULL, 0x27D9824624523819ULL, 0xAF2B192B776EE39BULL, 0x75F4C48C3D3272A5ULL, 
            0xAF4729B5E56787D6ULL, 0x32B203A846C69A48ULL, 0x24F9D0DE46748C4CULL, 0xBC136CECD9538E40ULL, 
            0x4DF5F2F67C5B009CULL, 0xF0932EC82ED39CAAULL, 0xABDD784E545938AEULL, 0xC2E47590F3649EEBULL, 
            0x2923D1A58A432574ULL, 0xDAD49635254D77E5ULL, 0xD02E42AFA8EF415EULL, 0x982A695801ADD894ULL, 
            0x335ADD1152A6706DULL, 0x632D36CFCB3E74CAULL, 0xF7C70F185A04C5F5ULL, 0xBCA0B1FBC0BC31DFULL, 
            0x168D3A9CE31C397CULL, 0xF5AD3702259CF86FULL, 0xBB812A35393D0A07ULL, 0x501B0CC8415A5691ULL, 
            0xB00CAA98E5C81970ULL, 0xC14AA9455C52952FULL, 0x684D38CBC78A3060ULL, 0xE5F4E5E9817FA6FBULL, 
            0x7D19168264BC941AULL, 0xC148AEADC3960EB8ULL, 0x9D704782C0D51CE0ULL, 0x80BF809F4E1CBF18ULL
        },
        {
            0xAADB780C7A3D5726ULL, 0x908DD17A23EBD8A8ULL, 0xB952AA3F40D97D00ULL, 0xD5D4E95223FDA3D7ULL, 
            0x13693FB5F59341D9ULL, 0xF7355449EA3B55B7ULL, 0x5A06F91D751BC63CULL, 0xC44D6FD27E1BD9B7ULL, 
            0x41A607EB0CDE9806ULL, 0x163F5AD609C269E4ULL, 0xCDC9E8697C76E1D7ULL, 0x2A159289770F6E9DULL, 
            0x3C9B2299A4D2C219ULL, 0x1F91B8D01677BDDCULL, 0xDDCF082CDFA28A4CULL, 0x46AAACF5C45677DAULL, 
            0xC092415D103DA9F5ULL, 0xE2525FF4EE76F517ULL, 0x872459075C17F2C4ULL, 0xC054BDD6B725AA6AULL, 
            0x33FA1F242EDE4D2AULL, 0x2866FB35C4EBEDD3ULL, 0x21015FA8CAB4B3E6ULL, 0x9EC6DEF68240765BULL, 
            0x9BC84035D5B85E71ULL, 0x010618C619A5404CULL, 0x0E2B7C81619F7CE5ULL, 0x97AA348BE3328B2FULL, 
            0xCFF29C9CAF6FFF9FULL, 0x21AF2098423F7AA0ULL, 0xEFEC01A375D25063ULL, 0x1F34A23F9B3057FDULL
        },
        {
            0xED37E4852FA80B04ULL, 0xF423973666FFAF46ULL, 0xC0FD5E55A2077DAAULL, 0xE31CEBDDC6832B41ULL, 
            0x7202BE5B8B3AC76AULL, 0xB037CC7C714A06C6ULL, 0x7A5859E2FB53CF47ULL, 0x2CE772B0A63952B8ULL, 
            0x8B38CD06BB0F63D4ULL, 0x5EA9DD2DC5254A75ULL, 0xD8468D7BEB543A15ULL, 0xEFE3A7CF7218488AULL, 
            0xD22392489E91801BULL, 0x2D7E5F8D93D34DD9ULL, 0xBB621F17E2CD6983ULL, 0x2D27D0D34F498199ULL, 
            0xFCB6CC2F0228AD6AULL, 0x1BD50DE5E7B68404ULL, 0x4233FD07127B2383ULL, 0x4DE24709FBB555B2ULL, 
            0x5FF7E0E7FDA63E4DULL, 0xE971C1DBDEA3DA1FULL, 0xD27DC4963AD4866FULL, 0x8816F4A93FA60112ULL, 
            0xE52FB1D330C3AE94ULL, 0x16733F0BA179FB50ULL, 0xD35E286B1A370CD5ULL, 0xBFF615C0A6285B4AULL, 
            0x2D26314BC1EB77AAULL, 0x1FDB2FDD8A8D9E19ULL, 0x1D43AD9E08485C83ULL, 0x411DA354CF0A3A61ULL
        },
        {
            0x535C98F35351C10EULL, 0xB6AEC379201A95F1ULL, 0x1E9F0C5D0F2E5AB6ULL, 0xBDEABA1E8DD28352ULL, 
            0x237A359903EBCD0FULL, 0x653B23F044790F33ULL, 0xF6AA9D2536F3593DULL, 0x86186D068F5073FBULL, 
            0x354BA7390A8A4AFBULL, 0x941B01D7387DA008ULL, 0x39532D971FA2217FULL, 0x9EF7B2FB9D8D073BULL, 
            0x7EC35D2561AFB151ULL, 0x1B0CA823BF9F7616ULL, 0x682761AD7D886E1EULL, 0x68BEB609C7D7636DULL, 
            0xACDD03DE65DD9CBBULL, 0xA609543C6ADA57BCULL, 0x9AE9FF7B3B1840C1ULL, 0x97696D7D9C62AC7EULL, 
            0x7E1AC4AF26F13CE3ULL, 0x365BFEBDE2CF621AULL, 0xA8C9D082509847C0ULL, 0xE22888736DF66320ULL, 
            0x9434618C7F15DFE3ULL, 0x59EF01BC73D9B3D6ULL, 0x0A4E9A245C36F64EULL, 0x68E8C0B000096D1AULL, 
            0x7C0D98F0FA3E12B9ULL, 0xE497DCD3DF3B9184ULL, 0x224136631664C6F9ULL, 0xE1C251098435BEC0ULL
        }
    },
    {
        {
            0xEB3DA639CC7C3DC3ULL, 0x7B956013F8890D03ULL, 0x54E068FA3C782309ULL, 0x811FF485C3977628ULL, 
            0x85C8A8B3E5C4C3C6ULL, 0x30AEB79991008047ULL, 0x6A3E97434C94E052ULL, 0xC6AC0D8215F7FA53ULL, 
            0x329CE59E64EC55DBULL, 0x90DBFC21D78FF790ULL, 0xFEEBD99567401DD9ULL, 0x0E2B6B314FE7F6F8ULL, 
            0x7AD195CA287BE605ULL, 0xA2F0AEE60043EB0FULL, 0x2B4B0F5C7FC0A084ULL, 0x24F5BCA16BDF64D0ULL, 
            0xF5826299944DEEA0ULL, 0x27F74BFCE879C7DBULL, 0x9F46D74AC9483514ULL, 0x48CE5226242B1989ULL, 
            0x7A49FC13918BDBEEULL, 0x28F3F12CCCE7B707ULL, 0xAE2D0F1B727AC640ULL, 0x8B2E70425A7B8878ULL, 
            0x7DA981684DB45E0FULL, 0xB26337BF88161C95ULL, 0x36BC072B8DA5BDF4ULL, 0x881B2C97BF95EFDFULL, 
            0x8A3B36B95CFEA6D6ULL, 0xB7BBCE411E2998D0ULL, 0x71C79E8599EA50E8ULL, 0xEF237E2E0B76CBCBULL
        },
        {
            0xF129B488BF4A5DC5ULL, 0xAF2D629ECF31FB94ULL, 0x6DE7EC2C8943BC11ULL, 0x89EF289861EEA3D3ULL, 
            0x33BFB423C3E1205BULL, 0xD974AD8DBD5C9D4FULL, 0xA2A7443C03458A18ULL, 0xA2B9455BDC7F417EULL, 
            0x2AC63505627CF285ULL, 0xEBF00B0C870220CFULL, 0x79947BFBD634F50BULL, 0xDCF10FE35CBDBCD5ULL, 
            0xF58D80392757B3D5ULL, 0x6744FF7EB6E67E47ULL, 0xCE3329A38857DD06ULL, 0x83DBC194F74E5EA2ULL, 
            0x5306FA34EE16CF59ULL, 0xD11DFC0DCA92A69DULL, 0x257285324B3B83B8ULL, 0x83FB37415D932BB5ULL, 
            0xF8ABEFEEC7554738ULL, 0x7630C92552E27B46ULL, 0x35B9C3427A1894E3ULL, 0xF716C834582DAA9CULL, 
            0xFD584D53B34CCD62ULL, 0x33C0ED85B61DD0D8ULL, 0x039B232F31E30315ULL, 0xBFCE4F7BB9AC3E4CULL, 
            0x4F925E0DEF2C1CB5ULL, 0xC98D866FE1954FE3ULL, 0xCF29AA09686B7FCDULL, 0xE4D4D100DD74BAF5ULL
        },
        {
            0x0C017B99DDCF0DBDULL, 0xC0FC9395A46BFBE3ULL, 0x659CC1D70E45476CULL, 0x0677E6C8D3E98100ULL, 
            0xEC12ADACE3E0D854ULL, 0xC086FD0C077336AEULL, 0x6AB85268B9C88E3FULL, 0x0E8FD6D7BCAF1E93ULL, 
            0x2A78CEDB7E59EFB1ULL, 0x9499A475C9930954ULL, 0x61E0E4277DF9F7B5ULL, 0x2FA8053A1F8DB5D1ULL, 
            0x19E731F4E6F15F67ULL, 0xD5CA15E0FCE2A789ULL, 0x577E4E6B6BEBC4B0ULL, 0xE95577D6C23D4CB0ULL, 
            0x1EF227978F2F1C4FULL, 0x10465F5FDC323556ULL, 0x7A3F602ECCDB8347ULL, 0x965DEF5C210368EBULL, 
            0xE40994BBDF562E8DULL, 0x661023B3EAD65E0DULL, 0x66BFD8B488541133ULL, 0x6CB8722376CB00AAULL, 
            0xAE433D53759C329BULL, 0x7BF97E0AEDA19968ULL, 0xB7CFD1426B58C997ULL, 0xBEC2CC55FDB21A76ULL, 
            0xEA9EA35A2F9D97ABULL, 0x2BAA226BF36C8B94ULL, 0xAC7AD862F403F7C8ULL, 0xDEB5CA3CF2F17288ULL
        },
        {
            0x58083D6D9E392A46ULL, 0x00B14BE52BDA6FD6ULL, 0x17ED34E6A460E79DULL, 0x9207839473463E20ULL, 
            0x1BC36552E61115E9ULL, 0x2CB95FDB37A56D86ULL, 0xA3C79F433A4F3233ULL, 0x56A0E8022C2C0C02ULL, 
            0xFFF371AC4BEB9C7DULL, 0xA935CBA61D042173ULL, 0xE1BC1B972FF8689BULL, 0x3EA937A7C5401D59ULL, 
            0x0D36FCE8C0D2212CULL, 0x2F90E9AAE0316035ULL, 0x044755B2126854ACULL, 0xE334911667F0BF83ULL, 
            0xE19B99590B4A2F91ULL, 0x3A784A3F7A87DC99ULL, 0xC1C20E58F4AE6EA8ULL, 0x801D38FED34E7E5DULL, 
            0x8F5FD164C3398FB7ULL, 0x3484E07DAD74B296ULL, 0x5D59934F18408620ULL, 0x1E25718CE39EC1D8ULL, 
            0xD1292CD02A696DB3ULL, 0x530062401544B423ULL, 0xC405984A0D62DB23ULL, 0x14ADC234AA2E9ADBULL, 
            0x3CEB38CD09F25252ULL, 0x73801465449F5CE8ULL, 0xDED38656BD55FBB1ULL, 0x15C5F7425A4A093EULL
        },
        {
            0x793008935F500414ULL, 0x09AF53E8265D040CULL, 0x29A1F2B8F59AE695ULL, 0xA0E5DE24869732A1ULL, 
            0x0D321806EEDF3D59ULL, 0x5E41D8967F52C5C3ULL, 0xF36FEB42C81958CBULL, 0xB6B397716D42759AULL, 
            0x5D809C9A2B64CE47ULL, 0xFAA772A56816A901ULL, 0x3030456056ADAAE7ULL, 0xBB4558F2DFD588ACULL, 
            0x889E226701E6D72EULL, 0x63F8262CC56F2FEDULL, 0xD2A493EAD3EBC20CULL, 0x66B9F1E6B1727963ULL, 
            0xE765B51381F5CDEAULL, 0x2937C5FED2408C6DULL, 0xFE1D1C7E2AED18ABULL, 0xF1925DB6F96EB9F5ULL, 
            0xC74A45B42E228E51ULL, 0xA95D179DDEDC1DF0ULL, 0x422C3A1EA8DB1E95ULL, 0xB0516C96E3FDF00EULL, 
            0xE9C80BA8C70B9BACULL, 0xFBA9F0D49C47DD2DULL, 0xA901D08C3684C465ULL, 0x76008B9C407E6615ULL, 
            0x933B2BA48216E070ULL, 0x5D02BED55C780D21ULL, 0x603AC44E3DFFCEE6ULL, 0x7FDDE91439A08E72ULL
        },
        {
            0xD5D7B725A0FF9576ULL, 0x83113BA4B7464EFEULL, 0xA258161B6792E65DULL, 0xD5ED6AEAC5139CAFULL, 
            0xFA5BEC46C790C901ULL, 0xF9A2C98E18BB323DULL, 0xA2D64DC8CB11E403ULL, 0xB2AA35C40749D8FCULL, 
            0xE9534946445E19A9ULL, 0x707D6F1B24F02F0DULL, 0xA713A934E0F89249ULL, 0x9BA0E22A6D40E11CULL, 
            0xE962DF0160E8266EULL, 0x8B615318884DB4C5ULL, 0x38993BDEBBA6A4CCULL, 0xAA833ABEA2E09E8AULL, 
            0xCCEC704C31662629ULL, 0x4880150CD28C42BCULL, 0x3F61FA9BF99A3184ULL, 0xC42C64385E970D07ULL, 
            0x03225CDF1F69FD30ULL, 0x1BBC8E639EB5E51CULL, 0x600C34EF69CD27B6ULL, 0x00F35464C4B0A215ULL, 
            0x5D1AEBF878D9415CULL, 0xC13913821091EE22ULL, 0xDBFADCB438667851ULL, 0x845DDFB38ABEB4F9ULL, 
            0x36B9DB29C49F4FBDULL, 0xDBF5B55A2E5AD8EFULL, 0x7395EB2D7923C142ULL, 0x782FC2A0080F14DDULL
        }
    },
    {
        {
            0x603306060A8B2873ULL, 0x333ABB34B48F5A52ULL, 0xD7313E196842CAC6ULL, 0x6129BEB486F53485ULL, 
            0xE756A13CF6B8FC78ULL, 0xB2B288ED2754A26FULL, 0xE2DB176E52706CBDULL, 0xC6074D35D2D1D5EDULL, 
            0x6B1A1CDD15EFFA08ULL, 0x70FBB2B9F968787DULL, 0x6A137C1C200DB8ABULL, 0x2CAF6ECB5780FB32ULL, 
            0xFD1DCA697E7E1038ULL, 0xB0CE6AACF03402AAULL, 0x159D984B52430199ULL, 0x1227F5868A549059ULL, 
            0xE5D449E4FC99FF18ULL, 0x4D8C93AA36733C61ULL, 0xFBCF5F777309F45FULL, 0x51DB7AAD1233CDF3ULL, 
            0x0B92BFCA630B0D4AULL, 0x9655121E2E4F6D0EULL, 0x31E1DFE06CF2E991ULL, 0x038A3BD8BF16FE2AULL, 
            0x6F65BF630B9D70F9ULL, 0x695D13310B53D773ULL, 0x5114FC494B8A6EA5ULL, 0xF132AB9E032B3716ULL, 
            0xAACE259A1CCDDD9EULL, 0x89849696B49AC18AULL, 0x9189002954FAB8C7ULL, 0x8A4596F98E496676ULL
        },
        {
            0xD7F1CC31AF648EDCULL, 0xF4DD8AA3F166A75BULL, 0xE122EC80AD7E9420ULL, 0xD158D4A1051077EFULL, 
            0x87B8BA449023CEE0ULL, 0x7A24F816F14A4556ULL, 0x7BC9BC03EB8FB812ULL, 0xE8A82B9F4C87C6F1ULL, 
            0x1025E5CF1D520E05ULL, 0x18406F9247EA2E1DULL, 0xBD207655C2323AFDULL, 0x0BCB314A098FAF8AULL, 
            0xAEF59FE49F658BBBULL, 0x282D85F230EA689CULL, 0x30CE782CB59CBBE0ULL, 0x129E971867A703E5ULL, 
            0x285A8600969473F3ULL, 0xAE23C1ED995B6026ULL, 0xAEBD5667CC02412BULL, 0xC01B661086ADBA10ULL, 
            0x3691DE3B151CB23DULL, 0xBD72A0455A431EC9ULL, 0xD99F77637DC3957DULL, 0x7D3AB53B7B720B2CULL, 
            0xFDDCD5C4BDEE9FBDULL, 0x137301736EC4C5BEULL, 0xBB1364C7606ABCDEULL, 0x6A324CBA582C4B9FULL, 
            0x21EB4AE2188836FDULL, 0x27BC6597D5B5B60BULL, 0x0CA39A326B2C20BDULL, 0x974C82A6B4267E8CULL
        },
        {
            0x90704FA127441152ULL, 0xCB33B72960AE94EDULL, 0x95DEC7F763B2ECF3ULL, 0x107AAEA873F4B57FULL, 
            0x6FD5F752190F71CAULL, 0x3E9632379A5F268CULL, 0x45F313722D412C3EULL, 0x107BCC0778107D36ULL, 
            0x9FF9A3A73EC5D5C7ULL, 0x583CBA9DDB32C611ULL, 0x21198213D25133F6ULL, 0x052791B39B7D71D0ULL, 
            0x74566393DDE5C3BBULL, 0xB3C99E0A38FB4EB2ULL, 0xB84B2F78BF76D29EULL, 0x1FD18EFCD961EF53ULL, 
            0x17B44810852171DCULL, 0x22495AA67D3BB04FULL, 0x3C2713324E877162ULL, 0xEB9208534045FF6FULL, 
            0x61314A426338F288ULL, 0xCCA44C7538199837ULL, 0x9F6CB1594CBCD4A9ULL, 0x3A433773DBE91584ULL, 
            0x67390EE206D8C72CULL, 0x00BB572ED02436B1ULL, 0x7FC6BD21250F4DD6ULL, 0x12A9825012FAF3BCULL, 
            0xE130AFF36DE53419ULL, 0xD8C20B3EC0AABA6EULL, 0xAF6E3A68ED0C2EB9ULL, 0x2182ABB80CC1DD99ULL
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
            0xE7D16B8B1A5F760BULL, 0x8F68D21636DF461CULL, 0x3E5A7B823217406DULL, 0x46C67387F6526B18ULL, 
            0x8776F9BE98E19BC7ULL, 0x782B382C135FDF35ULL, 0x800944FC19313F16ULL, 0xB014BAD8402FEE3DULL, 
            0xAE1D7B27631CD76BULL, 0x66AF1E0B4F09FD93ULL, 0x1EF947FCD1EBDCCAULL, 0x8F16890F3B6F9B13ULL, 
            0x9A2BAC33E4E0952AULL, 0xA1B60BEC1AB0E9BFULL, 0xEB063AB454C10CADULL, 0xF15F3659EE8737D5ULL, 
            0x6684A3F63EA97B13ULL, 0x56975F69BC977FF2ULL, 0xA98172D5E780AFFCULL, 0xE064FA0C35C483BDULL, 
            0xAED7F149793284A4ULL, 0xDF27BA6A91B892ECULL, 0x88933500BB90664CULL, 0xF3F8C5AD285D3DD4ULL, 
            0xF1DB50AF498F1F0CULL, 0xF84ECE1D3751D1FEULL, 0xCDEE7EA0D8EB3910ULL, 0x8A9CBFE770FC29B4ULL, 
            0xDA7A73D6660BBBE4ULL, 0xB4E760C84193BD91ULL, 0xB1D8F70803BD7DAAULL, 0xC545FF2FEADAC2B1ULL
        },
        {
            0x5BC4E75841189618ULL, 0x7195D09B3C43CF95ULL, 0x86C2164A7A21C667ULL, 0x53AF1AA75436FB13ULL, 
            0x942ECBD1F06C508DULL, 0xE1624444C5F84C19ULL, 0x672E45905D415832ULL, 0xBCF0CE530C0C872BULL, 
            0x67E504BFF19A609CULL, 0x49EFE9731E334BCAULL, 0x3BAB4C1107EA521DULL, 0x72AFC6EE797C1A8FULL, 
            0x6D402054C7762362ULL, 0x21CC78EED943E2B9ULL, 0x52CC6580277EF0DBULL, 0xF8479F0555AC455EULL, 
            0xF74F664A23F7725AULL, 0x7E40EB00E721F396ULL, 0xA557B303BC7A9123ULL, 0x156BD3A8A5D1EDA3ULL, 
            0xBFABDA655FE8E163ULL, 0x40F624151FABBBA1ULL, 0xF3F20B361981F82DULL, 0x65A8193A80C0AAA6ULL, 
            0x7E399536EA2CF995ULL, 0x00D5D97217E7EC14ULL, 0xC3536FBB73AEC22EULL, 0xD10D2399CCA4C101ULL, 
            0xB2CA9636E667DCF2ULL, 0xFD2D2D41FDFC43E7ULL, 0xB59EEC5314884C52ULL, 0x9A68719956F2FCDFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseCConstants = {
    0x5B76BEED7C31A7E6ULL,
    0xC67DA6A31D748E07ULL,
    0x9E14D3F56B9007F8ULL,
    0x5B76BEED7C31A7E6ULL,
    0xC67DA6A31D748E07ULL,
    0x9E14D3F56B9007F8ULL,
    0xD1BB6AA1AD4E67E7ULL,
    0x977F8F9B0E07765BULL,
    0x02,
    0x42,
    0x0B,
    0x10,
    0x23,
    0x1B,
    0xB8,
    0x8B
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseDSalts = {
    {
        {
            0xFBA4A5C3FAC86B7BULL, 0x5C6D6D18A35315CEULL, 0x5242B78F20FD7076ULL, 0xE70E15B575C8E08BULL, 
            0x6DBD787E123E4482ULL, 0xC355F47FA0EFDAACULL, 0x89DEF9200B284926ULL, 0x245743C3114000F9ULL, 
            0x470567DC5FDF076DULL, 0x6EB8B8C40E82515FULL, 0xF94F1D0A1E4E94CBULL, 0xF7DC857FC38D6E72ULL, 
            0x01B40E2FC892602CULL, 0xD033750586B698F6ULL, 0x883220735A980ADAULL, 0x46766A46345AC63DULL, 
            0x2C0BF729605C6F54ULL, 0x7B4E107968E98AFEULL, 0x4EF12E2EB7A74E41ULL, 0x3A8A272103022F51ULL, 
            0xE628EAD7E54058E0ULL, 0x39A8753E94C843CFULL, 0x9530CC854EA16DF0ULL, 0x1275C9D48C374AFFULL, 
            0xFE76C336BA9D444EULL, 0x4642CC523706C224ULL, 0x1E08F68BC0819EB9ULL, 0xEEF40AF0C4284F24ULL, 
            0xE649C6F2894E4645ULL, 0x5A03E4814BCE2C99ULL, 0x893D109311251F5BULL, 0x7D86D645D06FF040ULL
        },
        {
            0xED0BB17C1E886425ULL, 0x158EC84A43ECC1D0ULL, 0xEB9E56165E6E2EF6ULL, 0xFE8818C12DFCE930ULL, 
            0xABFC983BF9EC38C7ULL, 0x260E52B2A4D8EA59ULL, 0xBC4BC8299D97F983ULL, 0x82E975D0AF74B8B0ULL, 
            0xB6EDC1EA96134B0BULL, 0x0B05A01EAE76946DULL, 0x6F6A7E60F196E225ULL, 0xF1EFD6C029B264C7ULL, 
            0xDDF4DC2B3A37993BULL, 0x3A2243A7DB973096ULL, 0xB1EFD0BF1210E1B2ULL, 0xCF5AEF0E57F3B5BBULL, 
            0x34EA1DE751FCE3BAULL, 0xE71A09BEEEB706A5ULL, 0xE57318E509C5A4EDULL, 0xFF323B104564F959ULL, 
            0x01079868B56F4DCAULL, 0x1D3F2D241D89A8BFULL, 0xE936781088622817ULL, 0x6EF33887FFF410A9ULL, 
            0x76CD3379DB5C5F1FULL, 0x3DCBB1F0C28005BDULL, 0x2AF4CC2E3147620FULL, 0x90CA3750D820EBA9ULL, 
            0x7548EE90000F3212ULL, 0xBE4C7A90B93B5022ULL, 0x367619543E3F8093ULL, 0x2DE8A95F7DF359B8ULL
        },
        {
            0x42FA3D5EC6D1707CULL, 0x6106C4D7A0BC74E2ULL, 0x437410E98095C496ULL, 0xBAA58F181838D6ABULL, 
            0x61415D9BF623E673ULL, 0x4211AAC69A71E405ULL, 0x7B16450E9E85BE88ULL, 0xEA6EE887714DBE8CULL, 
            0x25C6DF836DE7D2D9ULL, 0xC777CF33ADC9F99FULL, 0x8B917A1218F97B4AULL, 0xA01CA093F842150CULL, 
            0xE62B151D97A17197ULL, 0x4EC981626CE443C8ULL, 0x0BF3FC5049F5378FULL, 0x70E1B8447C735B34ULL, 
            0xAF2F18F1783241BEULL, 0xC990279DADFB549FULL, 0x070FD0C9563DEB30ULL, 0x30CE9F208AFEDBB3ULL, 
            0xC0D6F7273D50412AULL, 0x0A2DD14B01EBA9EAULL, 0x31DA1C2A8FDF49B0ULL, 0x464FC676797163FDULL, 
            0xFC661F42AED3BE7AULL, 0x15D795A8B3B5A88BULL, 0xB69249016505D6B4ULL, 0xFF2448E5CCD1ECCCULL, 
            0x675A54882ABBF423ULL, 0x10D5F56EED47BE8FULL, 0x2D0FCDC3406FFD7EULL, 0xD47030CBB9963671ULL
        },
        {
            0x0CAD889A19BD5B98ULL, 0xF7F6C799C02F5024ULL, 0xA537E74DA5746C4EULL, 0x4C44008A275A2903ULL, 
            0x0B93A04D2E92A1D2ULL, 0x6A3D06F76D7791CEULL, 0xE6E71EF6CBB59424ULL, 0x60DAB4C6D1A7121CULL, 
            0x882651EAD1850A29ULL, 0xC79A0C7A52657B4DULL, 0x62951389867657B2ULL, 0x05008AB9CFD3C803ULL, 
            0x9354E6D1BA4A04DAULL, 0x341997A6E0663138ULL, 0xAE043BFC45728241ULL, 0x2649299A1B63CE0BULL, 
            0x54374FBC16FEE0DEULL, 0x8660D7E610CCF91FULL, 0xE036FC0E76539B78ULL, 0x07E97A8B174EC620ULL, 
            0x5D4E4089FB6C8D9AULL, 0xD154AFFB05C4D384ULL, 0xF2C266007FA91F69ULL, 0x500057CA2BFF8D88ULL, 
            0xD15DD3B9D81094A0ULL, 0x9AFC642FC4EF2B33ULL, 0x0186BF2EC4C7774DULL, 0x71F7CBBCE6759C98ULL, 
            0x18D0C65CEA8CDF60ULL, 0xAFF04681B5865DBFULL, 0x481A7AFEB437561CULL, 0xBEA7AE477D0A629DULL
        },
        {
            0x6CEAFF1AE249C935ULL, 0x6C230D708023E794ULL, 0xE7C1D77915F46C72ULL, 0x2F0B798BD501B2B4ULL, 
            0x56B38213839AFD60ULL, 0x28587461AEE03FEFULL, 0x940F4686741CA828ULL, 0x7C70F51B4F2A0A01ULL, 
            0xB93457FA295D9530ULL, 0x97092198862D2F72ULL, 0x3FEB789D4DC0791AULL, 0x6C85700CD28F7F98ULL, 
            0x92C8224F81CC8867ULL, 0xF4DAFA6840F79C20ULL, 0xE60532A2DED1ED71ULL, 0xA6F846ECA95DC1A1ULL, 
            0x7BB34AFA66646C39ULL, 0x4492611FA234A307ULL, 0x49C1196308795E1AULL, 0xD54F8EBF6805F75DULL, 
            0xE28A8F28D9C2B174ULL, 0xC049A174A2D47C23ULL, 0x1D15B87AB9926EF9ULL, 0xE4375D746BFBC8AAULL, 
            0x1914B7EDE2A86124ULL, 0x4FFEFC03D38443DCULL, 0x0F76C03692FE3A32ULL, 0xC7CECBB7290F9835ULL, 
            0xAC78E2296C63A588ULL, 0xF16CCA4BDEC63BD9ULL, 0x28430B185D3AD899ULL, 0xFA26CE9F763A0127ULL
        },
        {
            0x1DB4B098E68D1B13ULL, 0x56ABE9FA2309B7BEULL, 0x19E18251EB7ECFB9ULL, 0xAF499C19B1E0EBB4ULL, 
            0x73E4547016163424ULL, 0x5FEAF114716803BFULL, 0x34CFF8D683F7DF03ULL, 0x3362F0C88EB79050ULL, 
            0x8182CF8852A32C68ULL, 0xBEB32514E7CF88F4ULL, 0xBE4763B6CE499891ULL, 0xDD09B9ADAF7948EDULL, 
            0x6A18CF7B8E14D756ULL, 0x26556B787E93C9E7ULL, 0x1E6C1F03B7A22A24ULL, 0x3D2831B27243BD4DULL, 
            0x30F0B36334052E2EULL, 0xDD48B42FD4BD17BDULL, 0x170736F43DB15024ULL, 0x8F3873F70A627110ULL, 
            0x26C1C9388302B66AULL, 0xAABC9463FE9862CAULL, 0x6DC2CED01D690E78ULL, 0xBECD56CAC0186251ULL, 
            0x08EAAE11E425952CULL, 0xEABD9AE6794CE8A0ULL, 0x8C75D4D8D0692762ULL, 0xD4F106CC9E1B0545ULL, 
            0x74E915CFB97AD1E4ULL, 0x413D83634001289FULL, 0x99077A670A55F57EULL, 0x3E9CA0A9B27F2C40ULL
        }
    },
    {
        {
            0x494355CA1A91DDC7ULL, 0xC07330BE9E84B7BEULL, 0x9A3ADD4B9E3F67ABULL, 0x97115F7FC2042A95ULL, 
            0xA015C637A574B02CULL, 0x08940BF79FFDE60CULL, 0x988BB85F93F460EDULL, 0x5C40E11762C6AAE4ULL, 
            0x409BE7552AD421E3ULL, 0x3844BDAF50D77F32ULL, 0x2DBECF306F886B08ULL, 0x276F004541AE32E8ULL, 
            0x5B113756400306C3ULL, 0x0B95914171CCCAB7ULL, 0x5BBB0A1D7E1D1B03ULL, 0x6AF0F9C27092A10CULL, 
            0x055C74E2A299AE47ULL, 0xFE23BDD945A12335ULL, 0x3B42F1DE771F0BC3ULL, 0x6FAD86C699C0AECFULL, 
            0xC53BCC81E49F37F1ULL, 0x6C409A6C2B184D59ULL, 0x62EC8F2A2FFDF449ULL, 0x832502B9C9295026ULL, 
            0x465A4816C3B23A6EULL, 0x084973245037058FULL, 0xF6909B8E49820C54ULL, 0xDB3E8C7B14277506ULL, 
            0x7E5172EE5392ACEBULL, 0xC512130422CA17B2ULL, 0x9F1126E96C4E14CAULL, 0x3017288017F0198FULL
        },
        {
            0xA50805154F2E76E7ULL, 0x2037015B01960194ULL, 0x0820A333AEF36F6BULL, 0x629DB424DC4E0222ULL, 
            0x8FDF04FE65E78059ULL, 0x09E63762A3A86FABULL, 0x0A65E28F4CE9A1D9ULL, 0xC4DCA8353BE09A71ULL, 
            0xE0E4E6E2511A4887ULL, 0x94E37A14EE475866ULL, 0x5C355655F923E444ULL, 0xC6FD3ABDBC435A4BULL, 
            0x8757104746F2EA8AULL, 0xC267F094762DEB23ULL, 0x078C39699D82AC19ULL, 0xD5884A95902A1285ULL, 
            0x189935B2E73F8D05ULL, 0xA329AA6481D58AA8ULL, 0x89B091505753CC78ULL, 0x4340E9CF12214227ULL, 
            0x4EE55A8973AE2CD7ULL, 0xA1896E286742B48DULL, 0xDEA610FD8AB47ECEULL, 0xC69D93278DA294C1ULL, 
            0xB2ED51AFC9FBC96EULL, 0xFACA9873ED3C137DULL, 0x6DE04D134CFE5C84ULL, 0x75CE14B14ADDA9E7ULL, 
            0x4C812A0DE78C0B3FULL, 0x54EF8763549D860EULL, 0xEC1F433A1A4E88B6ULL, 0xACEFD16AE4C071E2ULL
        },
        {
            0x780E2CFE14583E9BULL, 0xAD977837A759E1E6ULL, 0xAB2C4BAAADD44611ULL, 0x1E7A442A547618B0ULL, 
            0xE5B380361F29B913ULL, 0xAD7058CAA869CBE7ULL, 0x3D70918BB59671F9ULL, 0x72C5D4D52CD7C10FULL, 
            0x1CE525AAC7BFD8B8ULL, 0xEDCA96B85C3AC763ULL, 0x0C55E1032336C945ULL, 0x03CF1F56C1928500ULL, 
            0xB2F8E902F1F6AFB9ULL, 0x6078C9274D24270DULL, 0xBEFC7D921405B554ULL, 0xC2763565E66B2500ULL, 
            0x43299B73E6A963A2ULL, 0x5B16C9CCF1A2B3FBULL, 0xD9EC7A8F64A10BACULL, 0x9A8A623B2777C02EULL, 
            0x1C46167CC0A9EBC4ULL, 0xC58BB376E25D5885ULL, 0x53367AF2F9815B9BULL, 0xD60938316ABC426BULL, 
            0x232B8AD300B434B9ULL, 0xB1A9298C39AC5449ULL, 0xC7889BDFF3C9C744ULL, 0x5662626B54C33B37ULL, 
            0x9DA078435545445AULL, 0xCA9E97C3F1D594B0ULL, 0xB0CEA5F5A373E576ULL, 0xE4CB75AA72298BC7ULL
        },
        {
            0x0D336DE5A17B3E9DULL, 0xB9D3AB9CD0D06452ULL, 0x8DC520F83FCF904BULL, 0x42E05C95C7A2C497ULL, 
            0x861DDB3011ED2D24ULL, 0xA85C2C10A3828B85ULL, 0x3321B73A9D64839DULL, 0x5ABE3F407B5B450AULL, 
            0xE3A9F55E8C106175ULL, 0x3DB4ECBCAA1B169BULL, 0xF8091327E0ED6419ULL, 0x470299DDCE47EFAEULL, 
            0x120F3ACBCFE7CCECULL, 0xC747781E4B82091BULL, 0x315081AE9F762E40ULL, 0x2394C12B5F6BBEACULL, 
            0x5745030E58B59C3DULL, 0xA81C8D3544198E2FULL, 0xAD88C52E61180253ULL, 0xA52932D5E90B8B1EULL, 
            0x1B77EBB2DF949A87ULL, 0xC3202B35657DC4E3ULL, 0xFFA620C8ACCDFA44ULL, 0x626F6645AD890193ULL, 
            0x09AF9DACE7275F5BULL, 0xEE3EB1443D0778F3ULL, 0x7CD942F66C18E318ULL, 0xFAE6152BC2911783ULL, 
            0xEE6FA8914AD6D58EULL, 0xBF64BAD24480D2DEULL, 0x7F84863DDE2961FFULL, 0xDF553DEEB11D9364ULL
        },
        {
            0x85AD5BAEF8A45326ULL, 0x7ECEFF615E202A7FULL, 0xB9E8E9C41B4828A6ULL, 0x73F53F6C55CFAA75ULL, 
            0xED088DE034089070ULL, 0x4A40DBC4DB2A792AULL, 0x1FD05AE17CC2C7C4ULL, 0x783B65D33F512182ULL, 
            0x1B5D3CA58BF39BE7ULL, 0x3548A37010665BF0ULL, 0x9917B5D03FB7FC80ULL, 0x30969CA08C408A05ULL, 
            0x45936BC4B2D46665ULL, 0xF6D72A79C267D85DULL, 0x82B91D974C1D31D2ULL, 0x5A1717FE8925348DULL, 
            0xE7838D6D2F451522ULL, 0x58AC028A88187AEBULL, 0x3898131FFF3CDECDULL, 0xF0F5557FE0EB7A7EULL, 
            0x75AD06FF00176114ULL, 0x9B44D8743F1A3F27ULL, 0xD43211A32EB6853CULL, 0xFDF6CC5BF4CBA1E8ULL, 
            0x869C25DB4BCD1260ULL, 0xE0FDC1F16A6F9662ULL, 0xFFEC307BECCDE25CULL, 0x8E330592E7FA4DABULL, 
            0x167CE4DFDE2796AFULL, 0xB22BE6B2D8622EB8ULL, 0x23030EE6643AE717ULL, 0x2CC65A9C8AACD82BULL
        },
        {
            0xCB199364B27DDC97ULL, 0x31DFBB739AAB4307ULL, 0x07BD72CB5732EF49ULL, 0x6969ED63C251EE22ULL, 
            0xB3635DBC510C19F6ULL, 0x4B31D41562DC7D2FULL, 0x5CA743F66279EF8FULL, 0x55730715310CBA99ULL, 
            0x3DCAD3A208F4D889ULL, 0x554C94DB15FFCE72ULL, 0xC3B5850F91575FE3ULL, 0xFE572B07C84B825BULL, 
            0x1AA179CE8873DEB2ULL, 0x88F6A5D948CCAE9FULL, 0x6286A426F1932EDCULL, 0x4B87ABCBAFBA8A0AULL, 
            0x86DCA54110177BC6ULL, 0x4126B381AE8BF87FULL, 0x6196A913FAA679B6ULL, 0xC779A5BA63E15EEFULL, 
            0xC68A6E4D7F999CF0ULL, 0x94BF210C48EC5D4DULL, 0xF476EB266707154DULL, 0x0597BEC5DD790387ULL, 
            0x7580B3071EC27AFCULL, 0x29E97FE9F3855E47ULL, 0x07044EFBFEA1301BULL, 0x059D51427206F321ULL, 
            0x49D69F3B9244041EULL, 0x3B331CBB16741746ULL, 0x45880598604A2C22ULL, 0xEB07426614DDE547ULL
        }
    },
    {
        {
            0x4E6FD35AE18F018AULL, 0x0E7CDC33CAD908AAULL, 0x339AD2D6D4A7ECA0ULL, 0xADD9855F6DAAF05EULL, 
            0x6241695D568E8D08ULL, 0x217ACC9077174E79ULL, 0xB9BC47F5A1E284C9ULL, 0xC92B89E2B553AE7BULL, 
            0x5010B460C131138BULL, 0x9A8FC951F86CA797ULL, 0x4B2CB4A87534C787ULL, 0x9B6D4D00FDDA7F7AULL, 
            0xEED2A12991A767FCULL, 0xA175EDF43F96DB4BULL, 0x5BA0CA4A5CA397E8ULL, 0xBB8B36DBFA528BE8ULL, 
            0x884E84D5D90930A5ULL, 0x359049C40EA4591FULL, 0xED2FD23674471291ULL, 0x6CCB279D7CCC094DULL, 
            0x848B3FF81C1062DDULL, 0x5FB40DE76D160F4EULL, 0x4CA425CCC7737FBAULL, 0xFCB9664DAF30985CULL, 
            0xF12B519AB62299CCULL, 0x3BB4A1DEB797A38DULL, 0x8AA0FD7A2DC46C47ULL, 0x54B9B851CAA7029AULL, 
            0x6A6285F93299C74BULL, 0x9EB5A34BFBE37BFBULL, 0xEE597AA5F21AC634ULL, 0xD120D7D8429BF37DULL
        },
        {
            0x7916A04EE124C7EFULL, 0xA411F1E75C7FA73CULL, 0x900015C375EA3217ULL, 0x2588D0EDAB2A4FF1ULL, 
            0x48ECADBA2F87795FULL, 0x0F2FE9EEF8F53035ULL, 0x89C8C8132959CF1DULL, 0x2A3684F458830118ULL, 
            0x99CBA72B1308915FULL, 0xF023F5A8718919D3ULL, 0xC21941AE9A52BADFULL, 0xA1FBCD1869C4F55DULL, 
            0x314AFA4C4A7D124DULL, 0xA0040C8D725E7131ULL, 0x4C51A812B3032B8AULL, 0xBACF2AA0761CE50BULL, 
            0x134BE1C40343C130ULL, 0x3F771362FB7C9AB7ULL, 0x04682045B3F511EFULL, 0x6ECE53B9696D599DULL, 
            0x2B2E6C148AC502B6ULL, 0x1BC9C7C43830AA0CULL, 0x378864577DAFA1D2ULL, 0x3CEB06C835C8AA43ULL, 
            0x14EA4121340DD32AULL, 0x373EDDF180BA70F7ULL, 0x55CE6BB86AD5E851ULL, 0x5482F2F092DE341DULL, 
            0x6C5A3A148A4B5E01ULL, 0x366877EE2EA2194DULL, 0xB1FDF18D513A4AFAULL, 0xCED924A31E4D68E6ULL
        },
        {
            0x2B304923C97F7DDEULL, 0x15870ECC74037441ULL, 0x236CE0B8670C9535ULL, 0xD98413D4803343A7ULL, 
            0xF7BCA6EDFEA48DCEULL, 0xC892E12743340D79ULL, 0x43F017E45AEB5CDDULL, 0xEF2905B81CE615DAULL, 
            0x447742F314D4F11DULL, 0x1094CD221F81E1A2ULL, 0xA4B67DFFD7758841ULL, 0xD50F3249C0EEAEE0ULL, 
            0x7B36C9B0EBFB8CF7ULL, 0x1C9F8F39C40D28CEULL, 0x32700ED01FE347AFULL, 0xBFF81D0264CDDFC0ULL, 
            0xE9956671E396D4DDULL, 0x64AE7B2D93C64ACBULL, 0x8FF729C08F13FA77ULL, 0x9CC4855AF917B77CULL, 
            0xB80214C220B70D26ULL, 0x717EA66F5E993A0FULL, 0x8B40238343147875ULL, 0x07A953AD1B4B0A58ULL, 
            0xD3D1367BD4E67D27ULL, 0x255C03AE49C0242AULL, 0x4406BB58303E9BBEULL, 0xA59E6EC779B6E35EULL, 
            0x0BAD782742557EE0ULL, 0x5F14EB1D1D3005D8ULL, 0xFA4CC27000C416EDULL, 0x4FF57D46016F7E64ULL
        },
        {
            0x5FCACF6AE9488907ULL, 0xC6FED2002269DB4CULL, 0x7060BC7003210F4BULL, 0x881126ABB3258C2FULL, 
            0x23CFAFDE70A7D79CULL, 0x51C9A9E6CD3A0EFFULL, 0x25E711709A4976F6ULL, 0x2ADBBEBA27030DD8ULL, 
            0x6E1CE79C6A639793ULL, 0xF4F57E59D0F32787ULL, 0xF42F77C83184EB4BULL, 0xD239414422D894F3ULL, 
            0xE0C1F7ABC674F24DULL, 0x8F5A5C10296B0A8EULL, 0x602E2B2927CEEDEEULL, 0x8BF3A6D6EF5A2627ULL, 
            0x86451CE4813B82DBULL, 0x6FA314E34FA5A986ULL, 0x52DBCC8F432009F0ULL, 0x84F14093C9008437ULL, 
            0xAAC1F6E6AC9783D8ULL, 0x82CA28A6EDCD5C5CULL, 0x9E569DAAA39C93F1ULL, 0xBD8670B2064F9126ULL, 
            0x62D09028502A0878ULL, 0xF7A8BB37FCB3C6BBULL, 0xB44473BAC440D2B6ULL, 0x3E7CD7E8516EC2C6ULL, 
            0xAEFBF795CB20F6E3ULL, 0xA6DE6B9C4096ECECULL, 0x5E1A15F8B3EB6AE1ULL, 0x9AA4E88ECAC827F8ULL
        },
        {
            0x86E94379787E2A2EULL, 0x1E958C1F465B21EDULL, 0xC0DC31D393547A25ULL, 0x2532591A9E744871ULL, 
            0x18EE99E207A721D8ULL, 0x827CA524811CAFF2ULL, 0x0E2030BFFBA52CFAULL, 0x76E9D3F3FB6C6C60ULL, 
            0xDD674D2C956756D3ULL, 0xC8C53AD18A0B1294ULL, 0x92CD29D099617E88ULL, 0x89DB680DB9D34DA7ULL, 
            0x8F2AF0FCABA73B59ULL, 0xA315CEE6EAB54970ULL, 0x24953228B12CA598ULL, 0x8150F32DA8CB65EFULL, 
            0xD09CF7EB598E6221ULL, 0x85D444F3051C023FULL, 0x5BD9745A8F08B27CULL, 0xCCF5DB5936AFF7FEULL, 
            0xB5B8D63C53E48FC5ULL, 0x839A657B93CDDDABULL, 0x8BF83DF9A7773FEDULL, 0xEB3A66902247BBF3ULL, 
            0x781BCC77B9F6227FULL, 0x507575A1582654C6ULL, 0x52A68BEE86C52044ULL, 0xC431C032AFE0AE65ULL, 
            0x1F2B1627A9FEE964ULL, 0xB9014856BE867A28ULL, 0x65D546B903A16BFBULL, 0x7708FF4A88A90C58ULL
        },
        {
            0xA2051838FF34AF5DULL, 0x094EBEDD178003BCULL, 0x598039E0F2A44583ULL, 0x7FE51B0335CAF34FULL, 
            0xCB07C0A6ACFE181FULL, 0x91B2EBF03C0AAB77ULL, 0x5A069C4D88A5CAE6ULL, 0xD431848F31C17185ULL, 
            0xC94A4DD12086DB8DULL, 0xE349FE05D86A7EB5ULL, 0x04ACFA3BB686D935ULL, 0xFA4FA02A6459467CULL, 
            0xE1AF7B9FA9807A98ULL, 0xB145CD7336B637BEULL, 0x3C3C0F1DF75B2512ULL, 0xDECA227FBDDB01D0ULL, 
            0xF57EDD0D29BDC051ULL, 0xA24DE3FE4E7C700AULL, 0x93DEDBE360D89569ULL, 0x9AA98A7BF424C15FULL, 
            0xC9215762BAF005E3ULL, 0xFD6B48EEBF1FD739ULL, 0x5BBEF28357A5DD84ULL, 0x10D4A64F621B5F1CULL, 
            0x9F647C7242A746FAULL, 0xD74EEE0A21D50EC0ULL, 0x4138EBBCA1FD500CULL, 0x8D8D974F23B8C70BULL, 
            0xB4B3B202D8FCF8FCULL, 0xE89D05A83E238598ULL, 0x984DFB3250B5F054ULL, 0xFC125BE24C50EFCAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseDConstants = {
    0x3AC2D80FDCFB64DCULL,
    0x5745EAF6BFFB1E2BULL,
    0xD777B1FDF744E8D6ULL,
    0x3AC2D80FDCFB64DCULL,
    0x5745EAF6BFFB1E2BULL,
    0xD777B1FDF744E8D6ULL,
    0x35686D19D803E8F4ULL,
    0x56F94352B3B49D90ULL,
    0xF1,
    0x66,
    0x0D,
    0x95,
    0xF7,
    0xBB,
    0xBB,
    0xD4
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseESalts = {
    {
        {
            0xBFAC3A37CB3E011BULL, 0x8E015943A311CD49ULL, 0x480A3BB287A7F254ULL, 0x3D1C2434FC6B098DULL, 
            0xADB56F8112AA289CULL, 0x7A6FF68ED9F3DB53ULL, 0xB813DAB570142248ULL, 0xF1CFC0EDEF60D799ULL, 
            0x9C3ECA9A87344A66ULL, 0x63DC1B5BAB85AE59ULL, 0xD6F0E9C6699D9CBFULL, 0xC74936A12E22E104ULL, 
            0x0ACA33DCD64EF4A2ULL, 0x2F6747D746D8EC09ULL, 0xB88049F99601E27DULL, 0xB4CC2A0F2A0F3F2CULL, 
            0x7CF435E120A6F3D5ULL, 0x8D14B593616528B5ULL, 0x29334A3D47085EC4ULL, 0x9211E7293448F7CEULL, 
            0x759E43CABC9664F0ULL, 0x6AEFC07C6B80942AULL, 0x998D5417ED09ABC9ULL, 0x9439680119E8FAE4ULL, 
            0x00EC986242AC4571ULL, 0xA7600B8638634F59ULL, 0x7872C7312F0CE8E6ULL, 0xF21EDBDB00042EC4ULL, 
            0xCAB59B6CB38812D4ULL, 0x04D2166E170E70AFULL, 0x0680C608B525D327ULL, 0xEE6BDD25C2C55822ULL
        },
        {
            0x51437588703B6D63ULL, 0x3576FD3E165DE3C9ULL, 0xC212373A916C8039ULL, 0x99B358BA87CC81B3ULL, 
            0x8110DF8F8DC6A79EULL, 0xBBF69DAD71D096A0ULL, 0x1F74D37FAC2CB22BULL, 0xCEEEDEF4A728903CULL, 
            0xCF96C64BCABF5DB9ULL, 0x1834D56BD7BA90CAULL, 0xF181E86C4F9EAD02ULL, 0x7AB0EB306F1552C9ULL, 
            0x33CD9343729B0DDCULL, 0x877F60370D715CA8ULL, 0x6EE3402D364B7E49ULL, 0x3ACEC300E4853A11ULL, 
            0xE8373BAD9DB00963ULL, 0x363AC1AB8E6EB0A7ULL, 0x7CBE6D591FF1BC54ULL, 0x5B9B3133CCB2D73AULL, 
            0x359A88E0E9A098D7ULL, 0x37D9DA144FA321C5ULL, 0x56611118BCE5DC47ULL, 0x3314FF108873AA83ULL, 
            0xE016CA6C30080A47ULL, 0x5EFD42FFC6DFED0BULL, 0xBDFAAE0792CC415AULL, 0x877D6E52B7D18FDAULL, 
            0xAD9B1036CAE21E21ULL, 0x166D20E06A8E6F87ULL, 0x0784C54F6C718E51ULL, 0xFE60009ADE84576EULL
        },
        {
            0xB1A6F2D34C54AED0ULL, 0x0EFD107577940AA0ULL, 0x7CEEC77121689DDCULL, 0x39A86CD69182768CULL, 
            0xBB44C6A9F9503052ULL, 0x243DCACFB8360D1CULL, 0x996514DE3EDA5F91ULL, 0x8777FFAA96659423ULL, 
            0x85E252A4EE72AB43ULL, 0x89B2D28CF0451807ULL, 0x1DFFF1A0B8574359ULL, 0x33F8698420326D3FULL, 
            0xFB72E04A9C20397DULL, 0xB6D0577C39ECBFA6ULL, 0x942C3F015AA42847ULL, 0x400A86C594D5B380ULL, 
            0x5ED6002DACBE0CF6ULL, 0xDF84DDAA24950065ULL, 0x0FCE10CB4F1C3D94ULL, 0xA142B91C3478C3CCULL, 
            0xA006CE7846B57998ULL, 0xBE21BB96992012F5ULL, 0x9FF99E3F226E105DULL, 0x9A1D9D0AF79CA7EBULL, 
            0x809D741463F47B9BULL, 0x1BD558CEE28A9570ULL, 0xCA9464634E9CC9ACULL, 0xAAA3D9BA5B052D8DULL, 
            0xD105D09C9A7787A6ULL, 0xB1A056B96BD8C48EULL, 0x3FD9ECD7DC713B36ULL, 0x6368571A4348EA5EULL
        },
        {
            0xE9BBC7CD8B5A8751ULL, 0x8CC40F4C4C44CBC0ULL, 0x58D1E679E1B1E1C2ULL, 0xB03B86F337990BB9ULL, 
            0x4DAB1D6C0AF9EF4FULL, 0xE1FEA029054D3BD7ULL, 0x7070ED4D113D0EA3ULL, 0xE92CD20BD0478E7BULL, 
            0x5AE5B5931FD88C55ULL, 0xBD10A86C2090EF81ULL, 0xD381F53092EDAD8EULL, 0xBEF643CC0332426EULL, 
            0x332DCDBEF6DABE30ULL, 0xC764731209E1434AULL, 0xA0B6CD5701DCCABEULL, 0x36B703981B0563A0ULL, 
            0x7051E2929CB90EA1ULL, 0x7A845FC135951550ULL, 0x34D4298604684607ULL, 0xF0A4788B6AF341BDULL, 
            0x19C05D95E84778D9ULL, 0x46858B349F89C6F5ULL, 0xAE98AEDAAB57F18AULL, 0x5AB04A802517870EULL, 
            0xD0E3191057F37E1FULL, 0xB18D3FC4DFDED190ULL, 0xEB79B92169993A80ULL, 0x5BD13408940E8D28ULL, 
            0x4FB513054ADF0429ULL, 0x9167182FC5A05B55ULL, 0xF28A03C03436ABD1ULL, 0x9EDC007E6C698AA3ULL
        },
        {
            0x72B829EF4718EA25ULL, 0xAD19DECBE2C5B888ULL, 0xBF9B9FE29A9BF66FULL, 0xDC0EB877732889AEULL, 
            0x6913346E561CE9DBULL, 0x4C5BC9AD4B7708BCULL, 0xEE190A6F76C1A4DBULL, 0x33F2C53F93460CE0ULL, 
            0x0F849A7AF7803168ULL, 0x171A6E70A4772ABEULL, 0xB592A3EAF5EFF1FAULL, 0x7F33702CECC6CA3CULL, 
            0xDC8558077F76E670ULL, 0x4FE7EC5B75FF16FDULL, 0xF461A0534C5951F0ULL, 0x0BAF32F6FAB5B505ULL, 
            0xFB7C52340F854F8AULL, 0x5C92C92DBFAE5DAEULL, 0x379B353F19B3D517ULL, 0x52C0296928045FDAULL, 
            0x1B6E51E9E94B7EE4ULL, 0xB66314033ADFC1EDULL, 0x540779FFF537DCAEULL, 0x13133DD0B7E35F14ULL, 
            0xFBD7BEEA6003370CULL, 0x47E7A42B8CBE5360ULL, 0xC1E209082FE407C5ULL, 0xF2871EA4E2441C5FULL, 
            0x19E6EC3A9EFF4884ULL, 0xB9CC84AD63789D81ULL, 0x7D876AC47FA8F087ULL, 0x0DA95B54AB545EBEULL
        },
        {
            0x0D17B3AE1FBA624CULL, 0x414D697C265C4F51ULL, 0xA13BD17C9DD45340ULL, 0x4B44FF37EC570CB3ULL, 
            0xBB1408A5EDBCB5FBULL, 0xFB9465CEE693DB25ULL, 0xF51DC849A260B7B3ULL, 0x7ECF11FCD384071DULL, 
            0x23CA225F79C78D94ULL, 0x02C8E52596C5C7B1ULL, 0xD5A9471BFD34E5A6ULL, 0x8F23AC5970D6810BULL, 
            0x5BFDF5A840C13642ULL, 0xB244114747ED9559ULL, 0xAA2903DB8697F9BFULL, 0x77AD0E3187506823ULL, 
            0x43EDEB5E04D452C8ULL, 0xFDDF6E1CECCB2690ULL, 0x5F21AE9D56DA5E50ULL, 0x85A244FB597E376AULL, 
            0x1FAE09E3DDFD9198ULL, 0xF250EC48FDA83143ULL, 0x2D655AD32F8AF8CEULL, 0x98669F8158933DF2ULL, 
            0x594365587EBB7D9FULL, 0x7DF2D226EA7B6C59ULL, 0xC68E09CB45A65122ULL, 0xAB80793868200CF8ULL, 
            0x5D24C6BDB728E2F2ULL, 0xBFB822B057CF618FULL, 0x03B5D3B8A31633DCULL, 0xE39B8723FF739BEEULL
        }
    },
    {
        {
            0xB369D23A26EEB2C6ULL, 0xF5FC3A205E5B67D1ULL, 0xDAE43470E61268C5ULL, 0x303421CEA577F232ULL, 
            0x454AA4F9F2FDB864ULL, 0x739FA58CA8015040ULL, 0x87B4DB6F6DF63B3EULL, 0x87697FD036EE460DULL, 
            0x21EDF4043CBF25ECULL, 0xE917B492AAAECE4DULL, 0x99B479B790D97940ULL, 0x0705105B31932537ULL, 
            0x206713865DA20681ULL, 0xE3B900B1B949403BULL, 0xAAD947AEDE489781ULL, 0x5D7B1448FE3C2E27ULL, 
            0xDB742E20C9659EAAULL, 0x74ED78848CB3EF5DULL, 0x68BB97A7FBD721F7ULL, 0xC714F147196D6F18ULL, 
            0xE574F46B3B7523EDULL, 0x91EDE36A4DD552CEULL, 0xF031FFBB8BD4689CULL, 0xFDABA4E94E03304DULL, 
            0x80862470A24320C0ULL, 0x731D6358CAD6E2CCULL, 0xB94F24EFFE58D8B3ULL, 0xAAB4FD4A5C6481C2ULL, 
            0x214CCFC13B778CA6ULL, 0xDBA9A6F4E756A6FFULL, 0xC5553B4778158F73ULL, 0x61F9585A02873D5FULL
        },
        {
            0xE9D40C59C706A9B1ULL, 0x29DF381F5451577CULL, 0x7193ECD76A666D38ULL, 0x69806D7FDD7584C9ULL, 
            0xF33743E5E7098E47ULL, 0x7E001CB75B4EF0D0ULL, 0xCA4A78F9348761A2ULL, 0xADC76F352DE67896ULL, 
            0x39679B7EC9241B3CULL, 0x368A5E05B60A559DULL, 0x1C27F32599CC6E92ULL, 0x83E1211D63AA9EB3ULL, 
            0xA17F18C6754051D0ULL, 0x3AE4F05E6DE4D64EULL, 0x753F6F8BD481A772ULL, 0x7CCB01E8859CDAA7ULL, 
            0x7D699C57F631BF50ULL, 0xC0281C3FA5E5D56EULL, 0xD2167A24CA916944ULL, 0xC4C74EBF0D890E74ULL, 
            0x5CFD628E8DA10CDEULL, 0x0B3B8595827D87B4ULL, 0x7B79DD83163D2903ULL, 0x49C9C1BF5E13CEACULL, 
            0x86B56A5DE75A2491ULL, 0x5A4FF4AA0D4E49D2ULL, 0x3D19F088EE552045ULL, 0x13F7FDF252FCB511ULL, 
            0xE317E0CF197B4B98ULL, 0x57C4C92039C65922ULL, 0x693BEEBA88478EC8ULL, 0x959A6BF31D931019ULL
        },
        {
            0xFE68B521347DF42CULL, 0x5B0BBBA1767158AFULL, 0x28FC0BF0C86E5B36ULL, 0x4269E6D340963954ULL, 
            0xDA47A7676DA9F473ULL, 0xF921832B0A1A4C0EULL, 0x205F404D1CA57DF4ULL, 0xC0090FE43FE62726ULL, 
            0x62E17AD04B3FD5A7ULL, 0xAC5BAE0BC7025761ULL, 0xDD87288B939140EDULL, 0xEC103975F3CFD317ULL, 
            0x2F8104DB568E6127ULL, 0x74E8B633DA9C7415ULL, 0x274A8C0DFC109A96ULL, 0x7220041ACFE9B779ULL, 
            0xCD307B078C5AA96DULL, 0x6EECA57FA40A102BULL, 0x9793972E198B9A1FULL, 0x865785520713BFB1ULL, 
            0x7881B36C06A1F498ULL, 0x548B702CAF833F88ULL, 0x501BE73104DFF76EULL, 0x27A4335E02B56DAEULL, 
            0x1331C8F612BC3C5EULL, 0x30A0B26EAC2DCF53ULL, 0xF1AD8CA00C9B50A6ULL, 0x989338FB38846AB4ULL, 
            0x004995695B9FF8B1ULL, 0x5C36278B1CFF78C4ULL, 0xB87C9BD8D3CC92C2ULL, 0xB0EA5647884E0FEDULL
        },
        {
            0x8086CC241D958890ULL, 0x3A013C37391915E9ULL, 0x8004EE6A4BFE0B42ULL, 0xDA24FC86D80C3D7EULL, 
            0xC633E19A84CC34E3ULL, 0xDD4CEABE9B5989DDULL, 0x1EFB0EF44CEA19D4ULL, 0xA679D3200FAF4C24ULL, 
            0xC970B30FC84CA309ULL, 0x134D8EBC8CE81922ULL, 0x660ED31587123493ULL, 0x8483EA121F7DCE54ULL, 
            0x5268155C6714CF23ULL, 0x4F2853834DFDD445ULL, 0xEF1C539E252F42D8ULL, 0x23C2346C4D5DBE05ULL, 
            0x2157D21E5EC27A3BULL, 0xA1DC84CC85AAD950ULL, 0x0F1E600BDBE8F027ULL, 0xFBB552F0E2F42B8BULL, 
            0x1C73033A75F8F472ULL, 0x16C874B0919CE6D4ULL, 0x4080A9E3C94F78D2ULL, 0x2D1FA673356B1FFBULL, 
            0x2D418C1DB3241D08ULL, 0x2D4A41B0AB8D5655ULL, 0x7A6542443805D1CAULL, 0x8FC74B82EC281232ULL, 
            0xD549E9DA7E098943ULL, 0x8C7D27E04EEE38BBULL, 0x42CDF7D64D314F4AULL, 0x8585E0249F6E2071ULL
        },
        {
            0xA62C7A39128BBFDFULL, 0x5A675FF1AA84AB81ULL, 0xC0263B43CBB7F01DULL, 0x4E9DCF2E079BC534ULL, 
            0x7472CF75B592880FULL, 0xC8EC02D55051CE12ULL, 0x1C44FFB386DCDB54ULL, 0x545ECCA6B3E14AF4ULL, 
            0x208456D64C2294D3ULL, 0x6833308B35B826ADULL, 0xEC3C8027F025D438ULL, 0x8AE498DF9C64131EULL, 
            0xE36EBD1E8BE71483ULL, 0x35F85577B7562534ULL, 0x627A11912037E122ULL, 0xD15FF7E0A3EED136ULL, 
            0x1EF6141192712EE9ULL, 0xE630F580C57E7491ULL, 0x3A1E67D901B324DDULL, 0x5470CDB0301E829BULL, 
            0xE770FFFB58F9B427ULL, 0x7556E929FFC849BFULL, 0x2680724B152C25A4ULL, 0x2381C1CD0DD4C997ULL, 
            0x6615B67E2A0F7A56ULL, 0x23C0BD9E17583642ULL, 0xBDF0765F75CDC2B3ULL, 0xB53AC9F292ACDF51ULL, 
            0x25EF207FCCF059BEULL, 0x0DD983C4D46BFAB3ULL, 0xF8EABDAFC9F7CB39ULL, 0xD031CA4FCD34E7C2ULL
        },
        {
            0x716814E6099154C1ULL, 0x92CAE35AD2E69AC5ULL, 0x1BA8C8D20A9CE19FULL, 0xD3F7EE79C80BD19FULL, 
            0xD1EAEFD53EF0DFCFULL, 0x9E761584D9F6DCCFULL, 0x6025CA93E3F78BA2ULL, 0x84BD1DC94808EBADULL, 
            0xCC12274B095C0E3FULL, 0xA5386542F4FE4E99ULL, 0x0F3341CC6CFEEC63ULL, 0xA0BAA77EFCB64472ULL, 
            0x08D9A8A6057AB697ULL, 0xCF3210F695D2805EULL, 0xC494A1C8AB179039ULL, 0x9F095DA1F0BF977FULL, 
            0x4FAEA0A5B0125FBEULL, 0xB78B1D9738E0B44CULL, 0xD3FCE31A0DFEDBE7ULL, 0x84CFFFDB98556DAEULL, 
            0xA292F3A65B6BE01FULL, 0x1B7FC3FE251F2037ULL, 0x76CE82205C898610ULL, 0x4DAD36628ABE7479ULL, 
            0xBD92A69624F431E3ULL, 0x0320B66A51D40E23ULL, 0x789301815CFC1D7FULL, 0xFBFDF21F58CAF3DDULL, 
            0x3F056E4DE349DBF6ULL, 0x21581D249364C965ULL, 0x0735A192CDA251A5ULL, 0x4FB270972C13FA4CULL
        }
    },
    {
        {
            0xFECF89D516596D7CULL, 0xB3DF496D4EFB0C97ULL, 0xFAA7DFA99F05F65CULL, 0x08346B200D9DE5EBULL, 
            0x3E39FBABA30683C1ULL, 0x543716C8BB1BDB16ULL, 0x26ED1F3EA5828BCCULL, 0xCF1B92B7CC55C2F2ULL, 
            0xFDF0518DD69F8E9DULL, 0x8E6F3E01BD826BF0ULL, 0xBBD6C10011B8DFF5ULL, 0x4C771BD752B0F8C4ULL, 
            0xF40D79A34DEE6F9DULL, 0x1118D0D3B949CDFEULL, 0xE93739BCE1504498ULL, 0xEB5D8EA75F8320A5ULL, 
            0x5413864789726175ULL, 0x041384A78C804D9CULL, 0xF654555FE34BEF64ULL, 0xE32A09FFD0AAD642ULL, 
            0x26875C0B739B199BULL, 0x2924964A26B2D0C3ULL, 0x00373B692425539BULL, 0xA43271430093C491ULL, 
            0x1DB303148EDEF3C8ULL, 0x5609A467D3DEDA39ULL, 0x2DE4CE72AE5F95D0ULL, 0x418772B1616EBF94ULL, 
            0x641FF11B9F0D819AULL, 0x2D4605053C9FF938ULL, 0x34BBA06645F5424AULL, 0x26EF210986E4851CULL
        },
        {
            0x64F80DD34B524715ULL, 0x926BB4A54127D740ULL, 0x7287EF703B5C1206ULL, 0x87056FFB832EBB7DULL, 
            0x571C4AAB6B0BA0FBULL, 0x731B6B785E29A839ULL, 0x10CF9D1F5244F747ULL, 0x79C23F15708A0149ULL, 
            0x494CEE51236613EDULL, 0x1EDAF4B114D2064BULL, 0x1AE51A3D06FB00BEULL, 0x1FE91AC157272552ULL, 
            0x8891772BB0BD9C27ULL, 0xB15A7EBEEB6CFB22ULL, 0xF36AAF6E79070BD2ULL, 0xC816780D0FC6AD08ULL, 
            0xB602CFD1EE7A4BA9ULL, 0xE23EDA4C00AE2BCCULL, 0x8ADAAEC01976F5FCULL, 0x7E36510A5497E4A0ULL, 
            0x5D79393BEBA7E452ULL, 0xAF99E0E74AB36565ULL, 0x51422C1AEC983C16ULL, 0x3C4A58E2881B4085ULL, 
            0xF335B68FF9CA9CF0ULL, 0x287ACFEE1159615DULL, 0xB36446BB34CA0F97ULL, 0x6D5AEEBBD9F2CA6BULL, 
            0xD0F5EE6CD3E149A5ULL, 0xD25FB55B9EE2072BULL, 0x8039CC33204E6DC1ULL, 0xAB1BB2708FE5BE4CULL
        },
        {
            0xEA22930F65E64EFBULL, 0x8FFCCE7EA03B36B4ULL, 0x0B5FE5F04CA61D4DULL, 0x463D8F00627BE42EULL, 
            0x6E87B713C9EA5053ULL, 0xAD6799364D7D0204ULL, 0x16B1D9F4C5B280A3ULL, 0x8DC712DFAF550EB8ULL, 
            0x5D2632A4506C36D5ULL, 0x0FD37F1E09F11CA1ULL, 0x200CBE4ADB79623DULL, 0x0BEF30F098104648ULL, 
            0x48A7FCA511577E25ULL, 0xCEDED8B9127744F4ULL, 0xD51A99C43D3C4D0DULL, 0xCE8014E1C26A9B08ULL, 
            0x5F62B677C2B596D4ULL, 0x1B2773B875AA849EULL, 0x66A5306F1D8904CCULL, 0x0D6AA66D79973843ULL, 
            0x5227480984BAF3EFULL, 0xC2E2AA1F2DC13DD3ULL, 0x0AE525E6116A0B3AULL, 0x1C308C36AA36B032ULL, 
            0x0461F8FA2C349B45ULL, 0x6155974AE66588EAULL, 0x5982A1A5012C594CULL, 0x23CA2F8B616690D6ULL, 
            0xBE4164B571503FFFULL, 0x74CB646633A9FF1AULL, 0x80EBDD7880037825ULL, 0xC950233288443E94ULL
        },
        {
            0x8A2C8E9F06ABC466ULL, 0xE0327EDA8E94C8A3ULL, 0x4B81C0B3A02298C7ULL, 0xAB1A3D2EFF1ECCCEULL, 
            0xA10B885850054836ULL, 0x0076D6F2013A358FULL, 0x879CB0260583BFA2ULL, 0x281EE0BDF6F937D4ULL, 
            0x63B7516F4E79FD7CULL, 0xE1ED95B50A3BF484ULL, 0x98E68DB46CBB353BULL, 0x8B6C3E447F9E1E94ULL, 
            0x2FB80BD152476513ULL, 0xA29F9BF95BCCDF4BULL, 0x3B1871C13059E3EFULL, 0x53FC08B2E73287A8ULL, 
            0x07619089B09F1C93ULL, 0xD04C886F4E695DC3ULL, 0x051B0C975084942CULL, 0xFE4197D34CF09879ULL, 
            0x6FE9298D01CCDB14ULL, 0xD2558EC62E1738F3ULL, 0x87440D5689A96CFFULL, 0x2ED0DD673091B900ULL, 
            0xFE1201BD0C786B45ULL, 0x53162772CF543BB5ULL, 0x7CD3F4DA80112A70ULL, 0x924684082608F634ULL, 
            0x8ADC6C7709A765B0ULL, 0x7E952172C382D782ULL, 0xC4CAD98951C31B93ULL, 0x20DB9918AF8504A0ULL
        },
        {
            0xFA145A1A34B974D4ULL, 0x5D68B4AC34888740ULL, 0x0908C0C236051FB0ULL, 0xF13AD21C5A3C69B5ULL, 
            0x6525AC7D2A20FD1FULL, 0x6A9DB983F46CF2D3ULL, 0x70860D506CD17AB4ULL, 0xDEEA02AECA325FACULL, 
            0xFA48613673D5F117ULL, 0x0E5CDD193D5A61A0ULL, 0xABE35E8CDA40F823ULL, 0xBE1BAD1D2D9039EEULL, 
            0x9E0773EE66A478B5ULL, 0x0D9DDCFE72E178AEULL, 0xB41282F8288A957BULL, 0x348EA3AC25F9482BULL, 
            0x0168D739B5F0C513ULL, 0x74EA3B819A3D7A61ULL, 0x4B6563415C29127BULL, 0x1A3473D325D86BEBULL, 
            0x9301C89B23809EE6ULL, 0x52C7301ABAF07340ULL, 0x561F1F089FC0399FULL, 0x70C0C20700CD5EF7ULL, 
            0xF9667E9EE5B1B05FULL, 0x895E997DA50FDFE6ULL, 0x504B5557106D7A21ULL, 0x3FA509C77D7673F4ULL, 
            0xDA3DB5E8311A32E8ULL, 0xA33997640FE93DE8ULL, 0x9F979F23B9A58AF8ULL, 0x6B20F6D46027534AULL
        },
        {
            0x5DF0245FC063B1E7ULL, 0x37C60F4814FA4E22ULL, 0x08703644A826CEE7ULL, 0x4EACA48C215958FDULL, 
            0x4BBBBA98E68E4CEBULL, 0x53FC18CF7CA77E97ULL, 0x9CC82CE085653D53ULL, 0x3716E2B131C64487ULL, 
            0x93D628C212C629E2ULL, 0x196DA07DEFFC3D81ULL, 0x72FEDC67000F2470ULL, 0x2A89BC5FF88E22CAULL, 
            0x177BC7464208CFB6ULL, 0x2294595E787BDD71ULL, 0x07F9F2C770F75199ULL, 0x49A19A77ACB928C0ULL, 
            0xF1F91DEC8E8F604DULL, 0x51E772D9A69AB2DFULL, 0xEC2DF49562054569ULL, 0xA6396FCC9493A03AULL, 
            0x900369436AA06ED7ULL, 0xEE62289D3DED7FC3ULL, 0xC03A7136ECF2B95AULL, 0x9290EEC5C492275EULL, 
            0x9DDEB44DD4E6CC93ULL, 0x8ED8094DD2D2A787ULL, 0x2BB372E87A434252ULL, 0xD818AC384332F3FCULL, 
            0xC0417DAF8066A89CULL, 0xB3FEBDA1F980D155ULL, 0xA9681E4860C7F09FULL, 0x998AAAA4FF4E9555ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseEConstants = {
    0xA31B0E2ECE478D1EULL,
    0x5F955958EA9F6DF9ULL,
    0x8479735BDC8A6F29ULL,
    0xA31B0E2ECE478D1EULL,
    0x5F955958EA9F6DF9ULL,
    0x8479735BDC8A6F29ULL,
    0x927E8E94F5809327ULL,
    0xC6A2A1AA257D767FULL,
    0xBF,
    0x7F,
    0xBE,
    0xCC,
    0x26,
    0xA7,
    0xA1,
    0x9D
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseFSalts = {
    {
        {
            0xBFCA807A77AFB4EFULL, 0xC61B340CDE2ADF9AULL, 0xE6C6F99F1BB71790ULL, 0x3F9EDEA15665C1B0ULL, 
            0x2F75331240C0F2E2ULL, 0x76E0E5B0B58F9B4AULL, 0x6052F8C913E35FF4ULL, 0x69C04DD75361B984ULL, 
            0x72195DA339EFEEBEULL, 0x83D91106545C8792ULL, 0xB7054118FD78DF58ULL, 0xDB63472AA74C7272ULL, 
            0x4FB8036682BBA705ULL, 0xB69B7A78039F9BD8ULL, 0x78C02C790FE09CAEULL, 0x11350B140E89E911ULL, 
            0x3CA99B4061BE20C0ULL, 0x4A50368BD20F3F17ULL, 0x9CA2E756BE214775ULL, 0xE9870FDAE167D843ULL, 
            0xEFF83D478C5AD465ULL, 0x21AD236BD79A19E6ULL, 0x9E5C0F6D60EA24AEULL, 0x2949A9075E31DF0AULL, 
            0xBAE182C1197D2540ULL, 0xF02D52BFDCCE4371ULL, 0x610A80B67589DB1DULL, 0x46F01E74223C269CULL, 
            0xE6446559D9746BD7ULL, 0x7F06FB38CC7944A3ULL, 0x258F29943C9BEA01ULL, 0xDEA4B8E2EF48DF1CULL
        },
        {
            0x1534C9034B3563A1ULL, 0xDE7C8D5FCE7FC682ULL, 0x480E280C28940E49ULL, 0xBDBA850CADA681CAULL, 
            0x50AF585834ADB71DULL, 0xF33F57C344FF9055ULL, 0xE0B2466AC4A9F00CULL, 0xA5BC9BC92A46B51DULL, 
            0xE65976727F61D1B5ULL, 0x59A29E01B63956ECULL, 0x8AA6BDB60764B490ULL, 0x695E6586F88AE7D1ULL, 
            0xCC3A3718866842ECULL, 0x693522907A2769E3ULL, 0x1C83B183D0084299ULL, 0x4356C3C4BAB461A7ULL, 
            0x87BA5A3B40C717E4ULL, 0x838914FC0601FB1AULL, 0x3BBA384869D9F8EFULL, 0x2898B38CFAC9FBF6ULL, 
            0x8B47D6783FB618ACULL, 0x30E6C90E91225E78ULL, 0xCCE6BED37B71D88EULL, 0x121648170463F2CEULL, 
            0x0E46B715B3B3A2CFULL, 0x6A5DA78598F62E76ULL, 0xA6A83010D9469685ULL, 0xF2EB5485F4747ADFULL, 
            0x36E6B7D9A3F55D94ULL, 0xC30E10D771C5AF7AULL, 0x94F3EBDDFB5CFA62ULL, 0x9A4F21896D849E82ULL
        },
        {
            0x666989EE140C557EULL, 0xB4294B928CE14BB9ULL, 0x0702E4FB9FCB007AULL, 0xD8D38A04FCCAC406ULL, 
            0x91B0332E1E80D69BULL, 0xE8766C0505429398ULL, 0x44702B502D7FEC99ULL, 0x5F698FC9B52ACA5DULL, 
            0x0A75A336733C454EULL, 0xED99B897BF4DCC92ULL, 0x6298BD4F9443CEFAULL, 0xB1900740E3B152D3ULL, 
            0x1AA83F331B7D9AD4ULL, 0xC5011D5523C8B533ULL, 0x5DFED7F47E483A81ULL, 0x8F43C2AD6FC1B879ULL, 
            0x012A105D030BD8DAULL, 0xE54EF155F907F96DULL, 0x9ACDDEC7024A66C5ULL, 0x92992DA1F713FC26ULL, 
            0x0BDB4F3DFE8F22E4ULL, 0x9EA9D2949C7DDABFULL, 0xD6242A8F8E63E95AULL, 0x95C69B2EDE1A25E3ULL, 
            0x3C6B1D59794985B1ULL, 0x1B6FC98FBE94CBB8ULL, 0x64B6398C451CD06CULL, 0x3E301834D57ADC3FULL, 
            0x613875BD637E2510ULL, 0x553D3D32B9AAA6C4ULL, 0xD6C2635A9905F706ULL, 0x24186BB746458F1EULL
        },
        {
            0x91049BCF4E9368D1ULL, 0x4ADC85CA0902F34EULL, 0x630367C7600A8891ULL, 0x73B2E40A5920DA9BULL, 
            0x1A45D2337EF634BCULL, 0xEA3FDE961C842BE7ULL, 0xBE3F2A375E3C32A0ULL, 0x003434D834E2D8BEULL, 
            0xAD4F4A0231224356ULL, 0x3544CAB36FAAF889ULL, 0xFB105238B31583D6ULL, 0x11820132D9A860BCULL, 
            0x7A3D02A0E69C30BAULL, 0x9B59ABC52E7BF0EBULL, 0x0B85920E0FC91980ULL, 0xED6FA31FB0C85078ULL, 
            0x89F37D4502E21970ULL, 0xBDD508691E400913ULL, 0xBEDD156FD6790803ULL, 0xEBB2F20D2681B8D7ULL, 
            0x733AA795211C6905ULL, 0x1C995A2EA73564E6ULL, 0x63E3F44E109249F1ULL, 0x2384E06F7D479DFEULL, 
            0x0259C2B1DFCD8A90ULL, 0x7480F6B0AE0F827EULL, 0x1B4F6DAD2D41AC67ULL, 0x961DB98058068E7CULL, 
            0x3F4588ADBC6A130BULL, 0x33D0564BD642914CULL, 0x4F619AC893B261ABULL, 0x7785F9048D0A880CULL
        },
        {
            0xA00431BD7154DB96ULL, 0x7AB6E197DF19CE25ULL, 0x6ACE120714DDBAD6ULL, 0x23C5C6F84DD1D350ULL, 
            0x683FAC4FE0396358ULL, 0x0F328D42BE98B73DULL, 0x94581B8AB9486D00ULL, 0x10854C5782E98333ULL, 
            0xF9651573C4C17D94ULL, 0x8B429BE5D4D9F4D8ULL, 0x1D933D2B4A87B64DULL, 0xDC0BDB20D59DA9EAULL, 
            0x4627E93E88D840EDULL, 0x175ED64AB7A7B475ULL, 0x882AE3DE0172F379ULL, 0x266A3D4EFB0A7128ULL, 
            0x5AEC4DCCA8D872FAULL, 0x839810A3ECE1AD70ULL, 0x17304A43A3A37EC0ULL, 0x05E1B9217E4A640CULL, 
            0x18BC4A1F9D910689ULL, 0x7019CA6CA2D633F4ULL, 0x57D758959F602B4EULL, 0xB62FEFFF10807C47ULL, 
            0x61A5644D06E8CB0DULL, 0x7F96244769437193ULL, 0x6B08B7EBF1BD1767ULL, 0x9A84E656E3260612ULL, 
            0x32069809778220DFULL, 0xA4FA7143571D4535ULL, 0x1BDF70BA25719E28ULL, 0x7383512966346863ULL
        },
        {
            0xE3770F964CF3E605ULL, 0x085727A7B473E99AULL, 0x17723B11232173E4ULL, 0x8662B4E399F34AB5ULL, 
            0x8D7ED675F37883BEULL, 0xF808DD92F0695C4DULL, 0x1BFBED68CD6884D0ULL, 0x1DD7603EE6D3DE90ULL, 
            0x4F7047B814A4DFE8ULL, 0x10E9F7A37DBAFCBAULL, 0x834A823D739A18CAULL, 0x3EF3BDDC4C74E847ULL, 
            0xC9AD5767AE6FFF2FULL, 0xEEEF587CF1C3268EULL, 0x1B93CD3FC28488F1ULL, 0x6E3E1B15C415B5E3ULL, 
            0xE8B102ECF2CAAAD6ULL, 0x480609A44E81D6EAULL, 0xCCDC7CCA84CA53F8ULL, 0xFB31D2D148463D51ULL, 
            0x55ECC43BB784F92FULL, 0x47DD95185A8431D7ULL, 0x7D985D2115D999B5ULL, 0xD607E22A39568F03ULL, 
            0x6C66B9CDD6A93041ULL, 0x14F0F3166D00718DULL, 0x715A86240258FBBBULL, 0x75EBB2D037EB2448ULL, 
            0x329D0A32F10628F4ULL, 0xE2D7F237AEE211CEULL, 0x06AA91CD43FD79A6ULL, 0x5ACD7C196446BA9EULL
        }
    },
    {
        {
            0xFDCC7D4267ABDDD0ULL, 0xDC4E5B7F5865D5ACULL, 0x10262D6ECD15AA8BULL, 0xD9C8FA41DE22C046ULL, 
            0x0B38689D0750B3E8ULL, 0xF282E5414FC20244ULL, 0x659778500DC2DE25ULL, 0xEEA07114A0FD57E4ULL, 
            0x52867754C9AFDFBBULL, 0x85AA4D6FFFC519D6ULL, 0xFF3F6DD162B34206ULL, 0x6E6EBFEA63A6EAF1ULL, 
            0x6967B5F0912CA82BULL, 0x1436F39ADFBE5DA1ULL, 0x02D9A86F79679FD3ULL, 0x6D2F88DB1E1EE07CULL, 
            0x24B678C44DCBF8D5ULL, 0x8D6E2B42646C3BE1ULL, 0x27CEE440518C8C46ULL, 0x91405ED7070F7917ULL, 
            0xF4532C0636AD330FULL, 0xABEE0F733A0CFE1AULL, 0x8542DC794B44F4A3ULL, 0xB8C8D6E92505780DULL, 
            0x5ABC2207EB2F4018ULL, 0xA0B991245D1E6046ULL, 0x243CE1CDC908AE2DULL, 0xC3E32EF14EF14E16ULL, 
            0x8E089F7596A32EBEULL, 0xFBD333982E3AD048ULL, 0xF7087CC40BFC18D4ULL, 0x69CC09B3AEE93686ULL
        },
        {
            0x2B7D6B8CABD28F1FULL, 0x53F86138165EF243ULL, 0xB43E96B7BE7A6357ULL, 0x55017C1745E25051ULL, 
            0xEC93C6C3E5DD3C82ULL, 0xAC1CF34934CC64EEULL, 0xCB756C5F307B5BA3ULL, 0xCCD676C92207879BULL, 
            0xC9DE705702848343ULL, 0x62654DE3CAA8CF1DULL, 0x589CD454A07E8C84ULL, 0x3AD2BA98465B58DEULL, 
            0xBFC9422DF92B1B20ULL, 0x7A9ED41C012507ACULL, 0x6BD1B3F2863F3EADULL, 0x813A91AF1D0C3091ULL, 
            0x650BB5CC5F6D3C82ULL, 0xA12F075D2098EAB2ULL, 0x4C980774B4D1BF59ULL, 0x7D5617957B0DB57AULL, 
            0x038A07810BFAC932ULL, 0x1C61F58BAF3A405FULL, 0x2A8C9E3F48B98240ULL, 0x47744CAC9283FE84ULL, 
            0x330EC872C87A0C6CULL, 0xFBC5E19266276375ULL, 0xBF11107D498C94C2ULL, 0xA77F0BCE1B88218DULL, 
            0x7A0B3970D38A9429ULL, 0x3F1F420460E09112ULL, 0xD69862A7DEF4F8A2ULL, 0x8D05F9164E13B345ULL
        },
        {
            0x1D473F7F2EBFC132ULL, 0xA144A80996125ECCULL, 0xBBF1A5A580E27216ULL, 0x003B5CC779E3801BULL, 
            0x74D6EEF5E7AC27B5ULL, 0x6BB2CE73AB0BA61CULL, 0x24CB2B6866213E98ULL, 0x3B95A422296B30CCULL, 
            0x9E87F09B31F50B6BULL, 0x82BB53D8A8EBAB90ULL, 0xF1A9B24FB0A5EE1DULL, 0x52EBA495A0F7D97DULL, 
            0x2C1AB93B6CF840B0ULL, 0x86EF097024BF9DF9ULL, 0xE2FF401FE4CF81C0ULL, 0x2A7380592BD392D0ULL, 
            0x36354863C8957711ULL, 0x2F8D9080E483C425ULL, 0x5D11A7B86C19528DULL, 0x12263D4BC2F86066ULL, 
            0x3E344F4BBFB44AB3ULL, 0xA864332F84DD09EEULL, 0x634D3A9F11C1DBA5ULL, 0x832B1F62B4D6B919ULL, 
            0x02DC63CF817EA4A7ULL, 0x62AFBD9C68552473ULL, 0xDA505A4A2BED2605ULL, 0x5128C46E64A2A131ULL, 
            0x91A4E86EE227337CULL, 0x041C855B395D0734ULL, 0x39A1D76D2D541930ULL, 0x0587434D01774A13ULL
        },
        {
            0x389249BD96B00FD4ULL, 0xD48BD7A795A68B3BULL, 0x3437317DD06609B5ULL, 0xBCDB000B2E909242ULL, 
            0x2FD6BA63A007074DULL, 0x8D2CC74B5352889EULL, 0x3607B270B2A9E80EULL, 0xBC077959073FADD5ULL, 
            0x5EF09483B938D2F1ULL, 0xF78D288EB5E96AA7ULL, 0xF9EEE080D6EBEE6EULL, 0x284D6B4ABBCD7A4FULL, 
            0xBB6F1D8F3064116FULL, 0x6BB140CEB4F2F795ULL, 0x1B229154A42C2A75ULL, 0xE672ED751EDD2ECFULL, 
            0x0DE168E2069B83C7ULL, 0xF66AEB946818B44FULL, 0xE15E19382D92126DULL, 0xD8552318BE9F0036ULL, 
            0x75D84F728B820E45ULL, 0x977C67880B71D52DULL, 0x18967C2BABE953FAULL, 0x0CF72B70D20158DCULL, 
            0x9E586ED8F0A98F45ULL, 0xD46A960708044D81ULL, 0xA958B8D63032612BULL, 0x216D68F16BCF7608ULL, 
            0xE587D1DB939F534BULL, 0x2F387875829FB28DULL, 0xCF15B90B2408F4CEULL, 0x745530568AFB78F9ULL
        },
        {
            0x2A6762E3C0F93DFBULL, 0xE45ACF30DA585875ULL, 0x533169253A9B423AULL, 0x9E2C76018B5DC539ULL, 
            0xFBB14A0C0A9ABFB6ULL, 0x45254EEE7F70A53CULL, 0x0717BDC3D45DCF4DULL, 0xD719A5228D46FEBFULL, 
            0xD15045600DBDB367ULL, 0x2EE76BA29E554D00ULL, 0x909F783262141ED4ULL, 0xE0CD2F8FEF7DDF9CULL, 
            0x3C79BB05CFDD7F0CULL, 0x7C6638066FF3B34EULL, 0xE4DA84EBF358871DULL, 0x691F661D49C203B8ULL, 
            0x74A8A5BE1ECCE6E3ULL, 0x9B017641356BAEE1ULL, 0xB46DA648D3559D83ULL, 0xE669B08D7821D470ULL, 
            0xE88DF8FB4C01A917ULL, 0x5A2ED593995499A4ULL, 0x5A8B6B4050BFA460ULL, 0x6B7AAE898B3095C5ULL, 
            0xB7857EA373E08919ULL, 0x09EDFBE30E26805BULL, 0x6697A5772F7D9027ULL, 0x3E7FBDF1A64FCF05ULL, 
            0x75485003A52653F4ULL, 0xD97DE63285D81D12ULL, 0xCA4FA2FD97ECB4F1ULL, 0x6BD1B6151FAD4991ULL
        },
        {
            0x84207C0548F16433ULL, 0x0AB016352F692A1EULL, 0xA13FD7311EE2D118ULL, 0xD5CE5BC104E7D505ULL, 
            0xDFEC3DE12E985C85ULL, 0xB3669F66A26CC523ULL, 0xE3FCB339CD4DDDBFULL, 0xAAD9C6E079A9858BULL, 
            0xCAB41177835B5E18ULL, 0x8B37445C35FF80FAULL, 0x6B3A2C23B2777C7FULL, 0x0F7DE1D383E33BB0ULL, 
            0x2CA75407B6DD0BC2ULL, 0x8CFAA78DF3E6C8FBULL, 0x4709048454B311E3ULL, 0x39D34D1727C5F4F1ULL, 
            0x0047F3D03B0EC1FCULL, 0xF308AD4F5245B8DDULL, 0x38E86C30976ACF89ULL, 0x28CCFF0C688CE2D9ULL, 
            0x3695D0327D3B0D76ULL, 0x430D68EA9BF6FECFULL, 0x5727C77FA3A07D03ULL, 0x1AA14C77FC483D1AULL, 
            0xFE0E42B841E576A9ULL, 0xE5D700D9BB7B8624ULL, 0x05C11DE981FDEC6FULL, 0xCD4C43BBA3041571ULL, 
            0x7750C18DF1FFDAD0ULL, 0xDB13BBB4955D6DFAULL, 0x642C843B79BAAFA3ULL, 0x917E236F2D00C4A3ULL
        }
    },
    {
        {
            0xA777E80E1F9DDFC0ULL, 0xC6959169323E102FULL, 0x57C818A0BD387ABCULL, 0x9540AFB7C479124AULL, 
            0xE27EC2A99E15B2FDULL, 0xFF96A29D05C8B55FULL, 0x4250B353EC37E269ULL, 0x91CF8A595522F5CFULL, 
            0xAE12F43B4A199E78ULL, 0x0A5A46E2C3CCD674ULL, 0x1DAD4B15D57A9691ULL, 0x852167601FB0E669ULL, 
            0x3CD6A2BA9716E6AFULL, 0xC84E774526B40CE3ULL, 0xFDAD24DE728C7FA1ULL, 0x980B1297E25A4C65ULL, 
            0xD36E24D80FA44FBDULL, 0x296F921F5C16FC6EULL, 0x74ECB1C32A6DA45DULL, 0xB3E13DAF448EBD78ULL, 
            0x59018E830D2678BDULL, 0x0C3E6F42F7E942CAULL, 0x11FAE14D353BB2D7ULL, 0xF2A5C58AB55FA37BULL, 
            0xAC20C84FF33CF45FULL, 0xE7CD0A759A9481C1ULL, 0x56EDBBACDA55531EULL, 0xBEAB5CF8816D7D7FULL, 
            0x1C712DA52EB82850ULL, 0xDFD1012F6708E78AULL, 0xD745E9720B31BEFCULL, 0x43AA36A64437505CULL
        },
        {
            0x1E24FF3C45FDCA49ULL, 0xB75C3FEFDFA937F3ULL, 0x21404B3890DAFE42ULL, 0x693A7D5AA27F335BULL, 
            0xB0184D70D661A779ULL, 0x2AB4CE8843E92E5BULL, 0xA96DFED48AFCAE96ULL, 0xC2A967115E9748C1ULL, 
            0x3921837CDCADA029ULL, 0x347570F6CFF1BF75ULL, 0xDA27D919DAD7D332ULL, 0x45565F56157E4ECFULL, 
            0x60509F9AD5F96781ULL, 0xB3E06DCB77A2808DULL, 0x12180CD1135F97C1ULL, 0xB31E0D662ED0B2F0ULL, 
            0x6D2899C93F11E2A4ULL, 0x68CC4A84F3AE4FDBULL, 0xBBEAA629248EBEC0ULL, 0x577B77EF065A7FBDULL, 
            0x2FA4D34525D6859AULL, 0x52672129DAD40E02ULL, 0xABBA27D538908100ULL, 0x77D29D1B2E2AC1A2ULL, 
            0xAD0ED06A12F6BF8DULL, 0xE053794C17060CF7ULL, 0x4272EB5D8B0B6F44ULL, 0x48BD5F626AF9D97CULL, 
            0x25A3DC528DCE7655ULL, 0xD380F80AFB96EE9AULL, 0x8A864DDEEC908571ULL, 0x3BF523A8FD8D87A9ULL
        },
        {
            0x74CBB9903BAE0763ULL, 0xF97CE705E1AE271EULL, 0x245DB97381622FA3ULL, 0x5C2EF7510BA23808ULL, 
            0x21A762DBF769E605ULL, 0x245CE0F13D007EE6ULL, 0xC5D3DDD4DE444D65ULL, 0x2EB3A315345718B6ULL, 
            0xD442F76F9C52A97BULL, 0x662B6006329ACB59ULL, 0xBF33B0586DB46828ULL, 0x1AE789AC8D15D411ULL, 
            0xD040404796A3248CULL, 0xD09FE3A21163E35AULL, 0x93A044D7D5876D04ULL, 0xB7140A57023A04CCULL, 
            0xB66F181231DAAAD2ULL, 0x176604936A2E819FULL, 0x24D3154C391E2E5DULL, 0xA0C6BEAFB02C62AEULL, 
            0x1F0A54526BED842DULL, 0xD955585CDA3CF1DAULL, 0x35022B58E2525583ULL, 0x3498A5822A92B875ULL, 
            0xE6D422A5422EEFADULL, 0x18C2CC51A2CC1B47ULL, 0xF7BEFC16EE98E47AULL, 0xF596E6F6E97CCDE0ULL, 
            0xFEA3002FC633A129ULL, 0x146C9E12C94F87B9ULL, 0x27C264C1204F895AULL, 0x910FC95DC5857A47ULL
        },
        {
            0x92528AA12D2EDBF3ULL, 0x1417E84EF20333D6ULL, 0x0E1C5FE7E0E039C2ULL, 0x75082A1343C9ED1FULL, 
            0x3F27798FF93239C9ULL, 0xF32BF2F5CB79E049ULL, 0x1EE92B74B56F2698ULL, 0x84330A11E1D5F6EFULL, 
            0xB45DDAB20C0E14EDULL, 0xD98FEA86F1C433D1ULL, 0x5D45132DA5DED67EULL, 0xD2CB747C76FA9E46ULL, 
            0x8B0AA86FFA3433C6ULL, 0x9A9BC119B0EC29F0ULL, 0x98314E5481391FB9ULL, 0x0D7C8AF42070C876ULL, 
            0x3EAB21ABE4E2AF79ULL, 0x6EFAF9B1CA799760ULL, 0x84676934A06CA3ADULL, 0xAED04703C1A7269FULL, 
            0x8ADAEA989A15D147ULL, 0x2A6E1AA23A5ACD8DULL, 0xD7EA03CDF2C986C7ULL, 0x389407FD3DC4B83FULL, 
            0x5600BA7410CC5E23ULL, 0xF653CC5EB222A6F0ULL, 0x57272279590E6003ULL, 0x37B89C3BA146544AULL, 
            0xDF09870147557F74ULL, 0x1FE492BE9F58D057ULL, 0x435DE6042E9F886DULL, 0x76E970D1D765C1C5ULL
        },
        {
            0x8AE10029D81B0D12ULL, 0x40E34776CA17D3F3ULL, 0x558741B5F61A504FULL, 0xA11A0C87B4BB8E4BULL, 
            0x911960C96F560545ULL, 0x4E28031378BFA219ULL, 0xA771252ED67E0219ULL, 0x717682D4E5074AFCULL, 
            0x6E993534491EF6FCULL, 0x1290A4B122F58ECAULL, 0x9B8AD50CA7026055ULL, 0x1169FA7FF5D6E692ULL, 
            0x4E1BDDA1C1B7937EULL, 0x8B59F00D20C0FF55ULL, 0xCC3635DC1B9891D2ULL, 0xC4BD4396131CDF0FULL, 
            0x9BE44A7D16684611ULL, 0x188FA46B4704E2E8ULL, 0xE1D17D46F8458870ULL, 0x5D4C6FEB0231B796ULL, 
            0xC229CA62C063A6F3ULL, 0xB5E95273F2787AF6ULL, 0xE68378D436E24E78ULL, 0xE24D3FA2F5CE200DULL, 
            0x0C5A6E1CF553B5B0ULL, 0x169E7BC9E758AA32ULL, 0x8DB08F8BAEFD9ECBULL, 0xE1476CCD3A3F8000ULL, 
            0xCC96D147D6A798FFULL, 0x6A2D5F44EF96A3E6ULL, 0x37E9D228AD30DF79ULL, 0xC1C5D584C7631548ULL
        },
        {
            0x7BF24C979BBA17F8ULL, 0xFDE01E1CEF41E381ULL, 0xA1806E5D3E4C05BAULL, 0xBCFCB522B0E037CCULL, 
            0x1413BCBBDE214400ULL, 0x4BDBFC0598A0B0C9ULL, 0xCA93276E8EE1589FULL, 0xCBB1DC0E994A9292ULL, 
            0xA17B790F909F61D3ULL, 0x9D5E67828C7AD674ULL, 0x2A7D77E15829A0E2ULL, 0x6D76180C7B06830BULL, 
            0xD528D4BF5D68FA66ULL, 0x69055499C4C5E4D3ULL, 0x21A05EDAA2F82B6AULL, 0x711F4C4C907A64D3ULL, 
            0x469F33ED2A533C68ULL, 0xBECDBE2A17C45C74ULL, 0x653A1458C11BEEA2ULL, 0xEB5BA18A733DFF8DULL, 
            0x1F1C86A4B3477786ULL, 0xB6A428E60699F4E2ULL, 0x0CDF98B3733A5D92ULL, 0xFF87BE6CE858C65DULL, 
            0x57F956964B0D00C0ULL, 0x03820639CF64D975ULL, 0x8A118FA8B3643F94ULL, 0x331AE215EF3A3ACCULL, 
            0x5D8E34DE9881350CULL, 0xC24D137772DA6E23ULL, 0xC96CA45C9ED3B4FCULL, 0x334726D87BF393A4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseFConstants = {
    0x22245F137F8CA65FULL,
    0xCD2D5BE8D77BB2C7ULL,
    0xEAC98090145943D4ULL,
    0x22245F137F8CA65FULL,
    0xCD2D5BE8D77BB2C7ULL,
    0xEAC98090145943D4ULL,
    0xF7E3565AF2C366A4ULL,
    0xC7D4FACFB45324AFULL,
    0xE1,
    0x75,
    0xEA,
    0xC2,
    0xE3,
    0x8E,
    0x05,
    0xA7
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseGSalts = {
    {
        {
            0xD8D8AF60BF4F8EA6ULL, 0x59097441ADAA5DA2ULL, 0x0981EAEFDB762AE7ULL, 0xE8AF48EC34558298ULL, 
            0xA4924ACF0DA366EDULL, 0x45D02578E41DB3D2ULL, 0x36286B1CA1C62589ULL, 0x29E670BCD5E13B60ULL, 
            0xD301E60B627BE48EULL, 0x8792612936FA35A3ULL, 0xF419B7B7F222B663ULL, 0x6FD4A52A1908C6D5ULL, 
            0x4B160524BB3466DFULL, 0xB191CA4CD4E7CB33ULL, 0xC3629C046742096BULL, 0x557A605C339CB4D2ULL, 
            0xC06A140DA0013454ULL, 0x1034F91B177BF8DFULL, 0xFB761D6A9AE666ACULL, 0x2B8EF739CAE0587DULL, 
            0x2B71AB2C77668DFDULL, 0x6C417B6869D02542ULL, 0xDD058CF75ED1B232ULL, 0x27AD2E38EF5A3D13ULL, 
            0x58F18C8C3006AFEBULL, 0x3F5A0EE5EFD320E7ULL, 0xE43731A1FC8B8FABULL, 0x1BB98F57E35AE3B5ULL, 
            0x98063CA6125BFB5CULL, 0x879789A8BA348281ULL, 0xFA40EADEDE397825ULL, 0xCE9046A642BE4B2CULL
        },
        {
            0x7FACF43822C7C2C0ULL, 0x2F3C82DD537E7A68ULL, 0xEFC495855BE65B29ULL, 0x61CD7C0699935F41ULL, 
            0xA1187691547CB153ULL, 0x32B9BCEF30766648ULL, 0x1483E9147F9E03AAULL, 0x816A401C06C3BE70ULL, 
            0x2FA96976ADB3E4E8ULL, 0x0DA0439251D36D46ULL, 0x18AA151E491B2A97ULL, 0xE964FE2F03B79A6BULL, 
            0x5A6D018C427B3EBAULL, 0x029C1C8E96A2E80CULL, 0x0DE39CCD7CC20B75ULL, 0x31971F91C573F49FULL, 
            0x68B069F3E6B18CBBULL, 0xF77A736AE6377538ULL, 0x45286940BF2ED7AFULL, 0x0BC422E19E9482B1ULL, 
            0x630EAA7CEA8BDAC4ULL, 0x93060B41D76494FBULL, 0xB6FF3DF6B8CC7988ULL, 0x912F5858C56AE04EULL, 
            0xFF980B13DCC715A5ULL, 0x11DFD49330BA97A9ULL, 0x8E4D655F3EAD8D10ULL, 0xADE4B8BCED4B5A7BULL, 
            0x384BF1F0E1696E81ULL, 0x57B6663D1175E3CFULL, 0x345F42C6E3BCE16BULL, 0xA21B1243588AA007ULL
        },
        {
            0x1F96D87D6275E3CFULL, 0x6B59051CC69CE73AULL, 0x1620401FC71B614EULL, 0x88759F4BA7732E14ULL, 
            0x7B943431EA1B0D02ULL, 0x5562791F5BD770FEULL, 0xF72FFBB9A7233D93ULL, 0x19050DAB64F65A55ULL, 
            0x8B78F3C3D7C39F97ULL, 0x76430FAEA83D67E2ULL, 0xDDFCF275CE49FDB6ULL, 0xC6789079952A570FULL, 
            0x5A99FF4F385B269EULL, 0x9624B3D328B53155ULL, 0xBBB26201FA23BA71ULL, 0x6866FBDA83A1E6E5ULL, 
            0x7352604DB203100DULL, 0x6207C9A3DCAD2CA9ULL, 0x718D2E13BD04F810ULL, 0xBF59C3FC7F84BBC2ULL, 
            0x784E28024C8BF13EULL, 0x9D1D0452815FCB85ULL, 0x712E59AF79949668ULL, 0x39805AB8239F81B4ULL, 
            0xC90EA80971D6E7FFULL, 0x6198C703C1485648ULL, 0x3076778724D9FB9EULL, 0xC611CAC8CC974DECULL, 
            0x37611734DEBEEFFEULL, 0x1D8DF0DD6889C309ULL, 0xAD3E335A808575DDULL, 0x46810F020BBD7E42ULL
        },
        {
            0x317AAE74FADBCA75ULL, 0x1B4468B4564C728FULL, 0xAF9DEA8A04B9E797ULL, 0xC21723E7B98F3697ULL, 
            0x02140845FCE2F31DULL, 0x79FDAA05F15C7764ULL, 0x72F17E492B56267CULL, 0x1A3796B78432B685ULL, 
            0xD92D28BA7A94EC55ULL, 0x29F94650E1CD0E80ULL, 0x550EAF9A7D45610EULL, 0xF8C54CD295DAEC32ULL, 
            0x1FD24883F9944C89ULL, 0xC156E2FB420E4BF8ULL, 0x7BCDAF207AEAE3D4ULL, 0x15B911F96EC8D44CULL, 
            0x7ADA0671865968CEULL, 0xADDD1C635E4392BDULL, 0x73175B6CF2326F1CULL, 0x4D7578EE30114A8DULL, 
            0x4FAC6081E764254DULL, 0x8F9A6A46F024D674ULL, 0xE542D7DF023745C0ULL, 0x5E72DDEE1C521BA7ULL, 
            0xF1F6B0ED17D00BBBULL, 0x46BA6913CFF2D362ULL, 0x8168D94BD2BDF6C0ULL, 0x311F4B362E1135AEULL, 
            0x2258E191C3CEB9DCULL, 0xDE5E97E5E36B8018ULL, 0x4C5C2F2FBEAC958FULL, 0xD051B0460E34344EULL
        },
        {
            0x7DD78FF55C1486A0ULL, 0xBBB1C288B407FA49ULL, 0x80EF474BE414154CULL, 0xD22F32315DC17C1FULL, 
            0x1A3ACC95B70AFC28ULL, 0x6B700615F6E99437ULL, 0xA7B4BD883C46B05DULL, 0xE58658FDDADF5F75ULL, 
            0xF17248974BD166FDULL, 0xC9F6932AA1093BCAULL, 0xCDFEB657D137D210ULL, 0xBF0536E81C71A01AULL, 
            0x7B90BD0BB8DED38BULL, 0xF115DB4CEE41CA3CULL, 0x9E03055D250F2864ULL, 0xB775EEAF084DC65CULL, 
            0x0050DA964B6FDD62ULL, 0xE4237D08D9F7B2C6ULL, 0xE58D002218303999ULL, 0x03F60DA375846858ULL, 
            0xBF15BA501FF7EC02ULL, 0x02CCEC6F156434E5ULL, 0x2C04979AE0D67B07ULL, 0xEFE7E7205F28A9F1ULL, 
            0x9EFE8D580B8D4091ULL, 0xAB3785BF014EDEB4ULL, 0xC21A299AB27EB309ULL, 0x965BC25E15C9CD9AULL, 
            0x02AAD288CC7DFC2DULL, 0x9C16CEE68849E0D9ULL, 0x446187465E842B0CULL, 0x5BD8F9BDE7D093BCULL
        },
        {
            0xB4276662BF7047EAULL, 0x96E87350A354BEB0ULL, 0x7E408F7E56D68F90ULL, 0x35F1A79595008A94ULL, 
            0x8BA2E9D70046268CULL, 0xEDF28A1F9C31BBE3ULL, 0x36C51A2004F4909FULL, 0x5762025A1ED8B0BFULL, 
            0x6E6BA515693391ECULL, 0x3955008B1F09EB3AULL, 0x8912D8F930AC3F5EULL, 0x0E4D7F96B6B11670ULL, 
            0xCEE6FEAA16EF4589ULL, 0x2122EAA700480FD0ULL, 0xEB450D9EDD48CD34ULL, 0xD750B5DD864DDED0ULL, 
            0x0360517C1818E3A5ULL, 0xA1BEB7C9B99B5DABULL, 0x9A178A145EE647DFULL, 0x7579D635AAAA7BD4ULL, 
            0xB29E3E6458BFA10DULL, 0x54803D4C2DA601E2ULL, 0x194821230F45A4FEULL, 0xEEB5E71BC9E1986EULL, 
            0xE6396B555EF90312ULL, 0x558F7B6A8BCEFC89ULL, 0xFA7F40307BEA11CDULL, 0xB88EC81DD355C942ULL, 
            0xB5DFC4C83C480078ULL, 0x34F17D1EC9951107ULL, 0xC600D5B53C33B87BULL, 0x22A39DDA60E1290BULL
        }
    },
    {
        {
            0x32E9B4430FFCBE30ULL, 0x3127706AFCF51696ULL, 0x7456677378C6B846ULL, 0xA965D6D7F2562930ULL, 
            0xF9531DEE667CA1C0ULL, 0x3CAA9DFDBF587F78ULL, 0x8F693B0E00CE3C21ULL, 0xA32E2FD4A9019AB1ULL, 
            0xDFDC54535D4FA2CCULL, 0xA107777EF973630DULL, 0xBBF085129726A432ULL, 0x99372F42F31EBA65ULL, 
            0xC263B4B0DA7D0C15ULL, 0x4274EF03C9601009ULL, 0xE26FF66E59DAAD31ULL, 0x28C33B87F8E3CDBAULL, 
            0x06264ADD411F00C4ULL, 0xD3470AFF8F85F5C5ULL, 0x62D9D751FA30244AULL, 0x95AE259D0C18809DULL, 
            0xFC3ABA1BE18ADE44ULL, 0xD36B61CFC57BF1D2ULL, 0xEB29AF21314EE89AULL, 0x38712DEF574AB83EULL, 
            0x0EA81F1B862074EAULL, 0x6A6CE799E61BD1F2ULL, 0x2D99106706B611CBULL, 0xC62C4E1734FBE2A7ULL, 
            0x8E36EB562679D05EULL, 0x346326A923B2D63CULL, 0xBD69DCB17B90BA5CULL, 0x67B9F7574881683DULL
        },
        {
            0x23CEE34D6D7F1CF3ULL, 0xFCD5BA086E8DD53BULL, 0x5F0157A764A47B78ULL, 0x109BE806B86B064AULL, 
            0xE07839A3CAEA63F2ULL, 0xA4B5F8D19F2FF202ULL, 0x3094AEEFBEFF1EC0ULL, 0xD3B6A09E71126A14ULL, 
            0xB886D00B8FBFF8BDULL, 0x9AE25039B348E6B1ULL, 0x4EA572C2B80867C1ULL, 0x3AFFF64D8E3A2B9FULL, 
            0xD5B2FCD95DD88C29ULL, 0x6A193D4721C76292ULL, 0xB8C247F846458216ULL, 0xC0BC95EEA899FA82ULL, 
            0xA6AA4F399E0E04FEULL, 0x132C9FABCD53760BULL, 0xC22F663F57315322ULL, 0x481F0886F7D330DAULL, 
            0x825A70E18A58EF93ULL, 0xEC07660933DFB3A8ULL, 0x9C5ABFB92896B681ULL, 0x4DE75C49AAF8AD3CULL, 
            0xFE689110988C5B17ULL, 0x21F5419E9D34942DULL, 0x959C6CA09561527FULL, 0x4D6604DCD190CBA7ULL, 
            0x9BC2B97B43CA3AD1ULL, 0x77514AFF1AD3F99DULL, 0x32A68175A96C950DULL, 0xABC6B23BC387AE57ULL
        },
        {
            0x00BFA438EF6F6F81ULL, 0x90A0D714B6983CBDULL, 0xFF2574A9FA8D4564ULL, 0xDAC643C838879623ULL, 
            0x95B5656C280B6DE5ULL, 0xAAED7D283A24AA8EULL, 0x7FC139A9C727A51CULL, 0x392B3DC85E9BD7D1ULL, 
            0xFBA6F0957C1C7E3FULL, 0x7C91C04C0214D313ULL, 0xD04B7145CA2A3BCEULL, 0x2DD68A3428C11641ULL, 
            0x088035A7EECE31D0ULL, 0x0D2633CF760DE3E5ULL, 0xBCDD9C6E6DF76FC4ULL, 0x600004505BAAA291ULL, 
            0xBC379DAD71277C41ULL, 0xCBBC939967558E24ULL, 0x50E61CE01AF212D1ULL, 0xDE1BEAE58C1F4C9EULL, 
            0x2DD3472906E59838ULL, 0x4CD972D71EDDB2F6ULL, 0x9C0173BA2843C85CULL, 0x436E6D2F03F8C83CULL, 
            0xA78F9D90C6BAD01AULL, 0x10F43E77C58AD85EULL, 0x593A436463D72FBBULL, 0x493FAA34CE7BBC5DULL, 
            0xFE9E04F756151A6CULL, 0x46EF04EE90B4C905ULL, 0x9E3AC50143041384ULL, 0x8375A7B56E473D77ULL
        },
        {
            0x65596E2D17884C84ULL, 0x0D30155264106C65ULL, 0x90CC1A9EB6AF7FDBULL, 0xE4AD90EF9B9B1E3DULL, 
            0x7AF856FE6A7A82DCULL, 0x8B14D3280102EA29ULL, 0x5BA573D92B8CEE63ULL, 0xC225D097D6EC71E8ULL, 
            0x44797C5BCA8B6C64ULL, 0xF14298A654201984ULL, 0x01FB6DAB9EEEC2B6ULL, 0x5FFFAE8BCF88767BULL, 
            0xE385DEC501AF355DULL, 0xD89F8EECE935055FULL, 0xF0F53922FDECB30AULL, 0x7EA02971BFA3C9AEULL, 
            0xEDC020DC43F4E059ULL, 0x47072A4C3D982E19ULL, 0xF76AC80301076B58ULL, 0x0509C37F4B464368ULL, 
            0xA01ED99F38EDCB52ULL, 0x324CD9A680C78ADFULL, 0x4CE43FF24BB07829ULL, 0x4A5184CBC09D5CFCULL, 
            0xE04461F4C1CCC9C1ULL, 0x0B37476143CC459EULL, 0x61035B2B6B5725D6ULL, 0x64A9AF87CC5562E5ULL, 
            0x3013B9891A1BFC09ULL, 0xA7DC04EEB4A446A3ULL, 0x38C961276C562B8AULL, 0xCA10190C1581B7B1ULL
        },
        {
            0x514F398B2F98D46BULL, 0xF266B4A26837A5B8ULL, 0x3B6995043BE87185ULL, 0x6A59976A803F1FE4ULL, 
            0x87640C48771D35FDULL, 0xDD450B8EBF486935ULL, 0x1F19F75D0F24313BULL, 0xFB34D611E871FD0AULL, 
            0x71B85819EFF96316ULL, 0xA3139AE5E95F75DBULL, 0xE6DD70061756CEDDULL, 0xA1874D997A7B24C9ULL, 
            0xC5B71291E49F86BAULL, 0x4B11A8A0E5F0D1ACULL, 0x6BAE725EDAC4A6E9ULL, 0x03D31D0764B11C3AULL, 
            0x7DF819DD1525B26DULL, 0x8D331E354096F9D9ULL, 0x9FC4FB721766632BULL, 0xF5D43EEDA726B48CULL, 
            0xFA463DF9B3CA5F03ULL, 0x31E909FDB84DC169ULL, 0x79A3CDB6E6D7376DULL, 0xB145213FC6624412ULL, 
            0x11106122CB42FA79ULL, 0xEFD8FBB45833A6D0ULL, 0xED64FCF0D3621524ULL, 0xFA61836CF95241F7ULL, 
            0x0D6BB81657D2E5CFULL, 0xDDF242EC102DA218ULL, 0xFACCEFF887F97E2AULL, 0x053BB34B7FCC5188ULL
        },
        {
            0x6D7E6039A5F9F702ULL, 0x24ACABDE71584DD1ULL, 0xA452185F167FCA1EULL, 0x3C38BE4C8048D03FULL, 
            0x064634CA97B7DC37ULL, 0x2282CE3097353204ULL, 0xB93F98A1C3958D0DULL, 0x57AF20C46CCFD70DULL, 
            0x53476EF936E45AFCULL, 0x29FDA0A01B68DB40ULL, 0xE3F3C1D7DF981A69ULL, 0x1BD37E05A1F71496ULL, 
            0xF01EE4FFCE5F544AULL, 0x3B1124EC42AD2E9DULL, 0xC08016836FB99491ULL, 0xE923A9BAEB173334ULL, 
            0x9C0CDB5EF0C4E6E3ULL, 0x0C74A1D5731EDB0DULL, 0xE71140F696F06773ULL, 0x2A53F3EFD2101EE7ULL, 
            0x6B45A97B011C8E59ULL, 0xA9348B0961689579ULL, 0x1657355CD2CB3423ULL, 0xBF3C5C4FCD78BD8AULL, 
            0x77C5203181488230ULL, 0x8F1934FD705B83B7ULL, 0xF24CF3A05E37E5B4ULL, 0x2B2E878725210992ULL, 
            0xAD2E9332B4AD3132ULL, 0x494F45738FAE016AULL, 0xB09A07065585D195ULL, 0xCEF096B542CCE74EULL
        }
    },
    {
        {
            0x154E31D0127E055AULL, 0x0291A6ECBF9FA7D4ULL, 0x517FB8236A62783BULL, 0x3CA8161FBFEBC7AFULL, 
            0xA32994B649AEEE3AULL, 0x1C3C98A04673F6B4ULL, 0x61683E26AD928ADCULL, 0xEA8DD0E726FA1871ULL, 
            0xD27624CAE0E4B520ULL, 0xF7A247F7607D1782ULL, 0xFB9ED88FE0742464ULL, 0x1C5DE595BB4ABDA9ULL, 
            0x5DDC942E6910195EULL, 0x7A76537452FDE105ULL, 0x601BF80962D44BE3ULL, 0xC2DAD71757A9328FULL, 
            0xDB0DD8E345036283ULL, 0x4125C8ABC42B1F3AULL, 0x87AB2BA38B1FD0D0ULL, 0x7D18D86CA03530C0ULL, 
            0xF3A78248BD23C888ULL, 0x85B5EB49203F4F68ULL, 0x4F8D338130660595ULL, 0x15CB1E04B9FC4317ULL, 
            0x3C4266E539EB1D3BULL, 0xBA274A541E4BC404ULL, 0xC070AF1D35214648ULL, 0xFCC0133F7FC5B3E5ULL, 
            0x512EEE5904F8B4D4ULL, 0x774B95C1DC6FA290ULL, 0x8992B12EF58000B8ULL, 0x6786F04B9656AB93ULL
        },
        {
            0x8A2C0C76D3869ACFULL, 0x33468591625583AAULL, 0x2AD97DEDAC81B6C2ULL, 0xEBCCE8A243643071ULL, 
            0xF047C2A69A435773ULL, 0xBCF025683EB42057ULL, 0x218D41A6D687E3CAULL, 0x5F2D1925059BA282ULL, 
            0x342FAC2BC5D83DA7ULL, 0x99F3665E6B6FD022ULL, 0x3BCB9E509C261C31ULL, 0xB8C1362B2117EEC9ULL, 
            0x019CE41ECCDAB378ULL, 0x57F4A9C2A9BFA99AULL, 0x69662B4F559019FBULL, 0x3EE61A5238F823D7ULL, 
            0xB4FBB732CF9A58C4ULL, 0x17A88C93D9623EE6ULL, 0xFCCC117D62B65676ULL, 0x41E1B32BDC635241ULL, 
            0x744DDD289EA46F7DULL, 0xD728E707F49E6FA9ULL, 0x13D30AD571C06F57ULL, 0x6BE871BD835941A9ULL, 
            0xA3200F5B06545D4AULL, 0x7362BD7BA0285058ULL, 0xFBBD9FC812AF9C11ULL, 0xDB1C5F6439A4D3A8ULL, 
            0xC69D3C49092FB905ULL, 0xB159B4F2D192548EULL, 0x4552548AF930DFA7ULL, 0xF0EDB19A32D0F227ULL
        },
        {
            0xE9668EBDF9FACD37ULL, 0x5A532695EC6B407CULL, 0x56AD04D35F965E44ULL, 0xD37E7B6A28FB4AFCULL, 
            0x3514D193DBD79312ULL, 0x85F915EDD561320AULL, 0xA752BA9EC8892812ULL, 0x299167A6120385CAULL, 
            0x35F14C3AE04BBBD0ULL, 0x57DDC933FE9A23DFULL, 0x625194951AB0AAC1ULL, 0xE3CF7E4CA515D1FCULL, 
            0x2E07D4914E206FB3ULL, 0x66E68AA259348DB4ULL, 0x2BEDA93CB935C96EULL, 0x5B4204617F4731BBULL, 
            0x3DEEDDE5A0CD394FULL, 0x50F7B57D9FC4AF6BULL, 0xD3171DA6EC275D38ULL, 0x2AA2937093E9866EULL, 
            0x3989979210FCAAF5ULL, 0xE7BCA89C88E10743ULL, 0xE2316FD576BD2E30ULL, 0x83CD784FBFA739E8ULL, 
            0xF40186229AE82B7CULL, 0x863783C0621BC0CEULL, 0xF793ADAB7B11A3E3ULL, 0xFFBA9F5F2757FE85ULL, 
            0x3A744BAA61A934D8ULL, 0x8ADF17DE3774B7B8ULL, 0x40A9E8B2717FCC40ULL, 0xE8602A1E5E41F980ULL
        },
        {
            0x22878B49D1D522FFULL, 0x6BC155B683F134E5ULL, 0x3B34CFC44898C3CDULL, 0x5433F3BC65F9BBAAULL, 
            0xF03F45BCC9F3FA8AULL, 0x9F69908A18011651ULL, 0x6EFB980E68D2BCBEULL, 0xC6BA3FC715075046ULL, 
            0xD0FCE254E56D6ED1ULL, 0x0AA0BB1059B85AABULL, 0x4DBF0F087EB6E2F0ULL, 0xEFF8EF50A7BF3309ULL, 
            0x14C4064F0414B8FAULL, 0x6F37D5D6BBF30529ULL, 0x26E23EA9D53FF31EULL, 0xC9AFE008D9B547DEULL, 
            0xEE5F5E1C5799C23AULL, 0x91E7257CF17AFC0CULL, 0x355C7060B2FDB2B1ULL, 0xCC9A7D7949484C36ULL, 
            0x6F6F96306F30719DULL, 0x293CF0CE52D38B39ULL, 0xF62398A014CE9151ULL, 0x3CA4CA8BD2D70EFFULL, 
            0xD9482429B820BC4FULL, 0x62E9A49C6A41F2E6ULL, 0xB6EE1CDAB17A8A3AULL, 0x6D44A00F62344EA4ULL, 
            0xE7C94E166BD6FE9FULL, 0xBF76885F656AAD64ULL, 0x8AF348FAE056B43AULL, 0x73F2BB0AF119EC31ULL
        },
        {
            0x1D11062D41B20BB2ULL, 0xBEC34004FB19AB4AULL, 0xB2826A77CC1B7D78ULL, 0x5B00899AB9624B61ULL, 
            0x9427AE74BDAE5E35ULL, 0x1DDA6B44F876673DULL, 0xAEE2D84CF61A5A0CULL, 0x719647EC080273D4ULL, 
            0xE2B1A6E4C6583A14ULL, 0x17C62C3C78AD1404ULL, 0x71DA8E41389A1C61ULL, 0x1D693FD90C577772ULL, 
            0xBBAE18D6529DFA3DULL, 0x1BC40129AC8C817BULL, 0x0D619F9210BDD984ULL, 0x1C2DF7C558C08A4BULL, 
            0x23F594B081B6727AULL, 0x26A18862ED73A752ULL, 0x0A8A293ACFF8981FULL, 0xB220B1A187793560ULL, 
            0x2A845D7324F08780ULL, 0xD90D4EBCFEBACCABULL, 0x2132B5D1C969983DULL, 0xD1847FE4E15932BDULL, 
            0xAC2A87FDAAC6C31AULL, 0xBB5B85815E377F63ULL, 0x2EB06E17C6849DA0ULL, 0x4B6F02A47AA85A42ULL, 
            0x48136705FEDE477AULL, 0x99148972C977049CULL, 0xFAC38469A6521F36ULL, 0xDBA37335304DA22CULL
        },
        {
            0xEBE396602DE67354ULL, 0xE725E216926056C6ULL, 0x8B4C7D79FDD71811ULL, 0x921D838484DFABB4ULL, 
            0x16ABE1F3053718B0ULL, 0x57B2C7B352CC5B39ULL, 0x828936B5133491EDULL, 0xE64170AD280D8BC2ULL, 
            0xC350DE13601270D7ULL, 0x3CC2A07F4AB4F764ULL, 0x6A11313CE70CA965ULL, 0x7A71E46377D60EE9ULL, 
            0xE5036C947B874BA7ULL, 0x0C5915E2CBB3FED5ULL, 0x0BAD0D946006DFE6ULL, 0xD5274BEBAB8BEFBBULL, 
            0x3040969402718879ULL, 0x4D00D8B172EFAEC9ULL, 0x5669ACF0F020AB99ULL, 0x7D747F8A58ECF24BULL, 
            0x8225ACF34DFA6DCDULL, 0x521D5261359CF1BEULL, 0x2456026BBB86C1C7ULL, 0xCC42156B0FD4F517ULL, 
            0x799634CD8B863324ULL, 0xCFEFCA8AC57C38E9ULL, 0x50C34E87662D774AULL, 0x4157E186C7470C8CULL, 
            0x0A4F4048254A6210ULL, 0xA3432C4508DDD3E2ULL, 0x94A16019A4301E75ULL, 0xCFCF0689304D7403ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseGConstants = {
    0x9F42C8194FE7EE19ULL,
    0x01A3AC631C57B402ULL,
    0xD4C06C76B1A715D3ULL,
    0x9F42C8194FE7EE19ULL,
    0x01A3AC631C57B402ULL,
    0xD4C06C76B1A715D3ULL,
    0x5A9EE7FFEE160B77ULL,
    0x80DA2EDD94A4D8ADULL,
    0x0F,
    0x85,
    0x81,
    0x54,
    0x06,
    0x80,
    0xF3,
    0xEA
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseHSalts = {
    {
        {
            0xD6FB5794E8D1F17FULL, 0x7CCD5191A2518CC4ULL, 0xB5A3640908B62CBDULL, 0x0F6E2528EAE36DB7ULL, 
            0xB118059C4CADE347ULL, 0x24C8DE80EDA18019ULL, 0x739244E05BAA9348ULL, 0x902D168BBCEB4931ULL, 
            0x342D4824539DAB3FULL, 0x319F2CADC6C19DB8ULL, 0xE0478035A2019655ULL, 0x9A4128E386021219ULL, 
            0x2D067C63EB772AA8ULL, 0xC2A37CE6EC028E7AULL, 0xF8E241ED8837981BULL, 0xAA590D0225D0F827ULL, 
            0x70C0966020D2858BULL, 0x892381EB1243E2EAULL, 0xE57AE0A245095E02ULL, 0x37B73BDE5170411FULL, 
            0xEDAC10096839B4D1ULL, 0x47CB75A8E4C596A0ULL, 0xB07C6840BA51A4C8ULL, 0xF9D64842DE019A99ULL, 
            0x794B62BDA049614BULL, 0xC399022B972C8C7BULL, 0x74EDF3B54E580C69ULL, 0x9848027FACD15F02ULL, 
            0x91CA6D2930A044D4ULL, 0xDC55DD5284A5B91BULL, 0xDE370D86549FEE54ULL, 0xF120AE89538C0009ULL
        },
        {
            0x377E89E0AC4F84AEULL, 0x6707EA3B0DB6C1D1ULL, 0xF61842FE0D58EBD3ULL, 0x7D98650F4EF5CB96ULL, 
            0xA8FC4688899D0710ULL, 0xD4BB16214A90A1BFULL, 0x8DBB72AD6BA6A570ULL, 0x9D4157157C3B70BDULL, 
            0x14718F8E9277D1B6ULL, 0xF3C8A591546FD4CBULL, 0x3C6565BA530338A2ULL, 0x53D678460CF9CFADULL, 
            0x518FA66B7FD32954ULL, 0x5EAB34538375D594ULL, 0x7CAE89E398EF3577ULL, 0xD337001CC0719A2CULL, 
            0xDB330768777FCC68ULL, 0xE1F4280A0C5D0F07ULL, 0xBD4049BBC4D9A8C6ULL, 0xB4912E7BAB84F4C7ULL, 
            0x81C7F84163EFCBB4ULL, 0xB75062116B791EACULL, 0xFB662F84D1FB698EULL, 0x28E702465979CB06ULL, 
            0x520B536F0DD3C8F0ULL, 0xB7A31AAE187F05BBULL, 0x2B8EFBFCBF8A2B55ULL, 0x97674B39D473DFE1ULL, 
            0xDB2502A4BA1C19FEULL, 0x830E167E70750B29ULL, 0x0EE10E3E5ABC0FE6ULL, 0x1491F913DBBEE97AULL
        },
        {
            0x307FA9881A581055ULL, 0x812041B2FCB99304ULL, 0x52406E05B7F160A4ULL, 0x8DBECC4AB8E8A108ULL, 
            0x8B08FF27F3A8E0F9ULL, 0x994E4E5F934AC641ULL, 0xCD606C000B7E3BF1ULL, 0xA7A1A8D192B57F8EULL, 
            0xFE3EE87754C1FC72ULL, 0xD96C885BD88B713DULL, 0xFC51F7BE593AC721ULL, 0xE60279A8230FD9FCULL, 
            0xD974445E74A983B5ULL, 0x499E6330E6C9BF6EULL, 0xCEC4FFC82A150740ULL, 0xE8FBD813EA99D1F0ULL, 
            0x082A9BEF8ADCF3BBULL, 0x43DD8BDEC51766C4ULL, 0x44721771BF13B23BULL, 0x74BA633CF43C76B6ULL, 
            0x6D6495F5415DA758ULL, 0x15A4B9D7C9B89271ULL, 0x451240DB01AAB4B1ULL, 0x126EB8C19E3DA7ABULL, 
            0x2627D5B1EC4E4AB9ULL, 0x29875C972D2A2CA3ULL, 0xEEA993ECD51E594AULL, 0xB9EDDEA626277599ULL, 
            0xADAD546436F171BBULL, 0xAB99E7C69937A2B1ULL, 0x511CCBE84AC47EBCULL, 0x836973824A7B7B51ULL
        },
        {
            0xAFFE93260A82897CULL, 0x07F51E6F3E075841ULL, 0x1BC0309E9D56B738ULL, 0xCD124F8E3F4B7566ULL, 
            0x76104621479822E1ULL, 0x95EA94E5F270B7A7ULL, 0x9419AC4F5B5602C1ULL, 0x5A1D2A283276FCAAULL, 
            0xB0357FDCAF302DAEULL, 0xB4B8A23B9611881CULL, 0xB3BE99E3334DE189ULL, 0x769274D81940D99CULL, 
            0x1BD0D216EA268EB2ULL, 0x94E0686E7D5EDDD4ULL, 0x3AE0DAD5A6932C21ULL, 0xCFF32BB710083703ULL, 
            0x9432F591A3BB1F7DULL, 0x59787B6705DC1633ULL, 0x4CED0F6EA63840B2ULL, 0x0E9C6038FC99D470ULL, 
            0xD1B91597397C0017ULL, 0xD3F59B4DFFBF3660ULL, 0x97B0A1E9956E00C0ULL, 0xC8F6BA7BD972D22EULL, 
            0x63D38710B17BC438ULL, 0x7C5A36450FDC26E3ULL, 0x2147799922469C79ULL, 0x21A807D42308B9FDULL, 
            0xAF8CF2A6EA72E9A8ULL, 0x6DE06FEBD43FA554ULL, 0x429B19074EA1D5EAULL, 0x56F9EBA94D7A8FE3ULL
        },
        {
            0x4F9B8A1F9A696DEAULL, 0x8838A6A8EA0142ECULL, 0xFAD34AC7E5FC8C39ULL, 0x02601FDABB506F0AULL, 
            0xD20D0041B271A35AULL, 0x99AF24935CD87DB7ULL, 0x6A646BF87362B845ULL, 0xF865076860DCBCDDULL, 
            0x2B5F9D2FEBDD09DFULL, 0x173422655505D3FCULL, 0x0B94968AA3F0E43EULL, 0x8DBA4709D3D6E5F7ULL, 
            0xB48C2062143CE62FULL, 0xB19FC7C86D38E40BULL, 0x9220F97B230E5068ULL, 0x0B6CEAD7BF1A5687ULL, 
            0xC26D5B9657C18083ULL, 0xE397B86C09E0972FULL, 0x0540832B499A7278ULL, 0x44C0A0025E015E13ULL, 
            0x93B24ABBFB970464ULL, 0xD48B64E1B5CB17AAULL, 0x0F7485221C79247CULL, 0x03CCE5FAEFFEF0B7ULL, 
            0xFC557B01D0CA891AULL, 0xCBB72DA16C760EDCULL, 0xB8792CB0B0C5AB34ULL, 0x648044E4797F29D2ULL, 
            0x0EFA7DF4707F07A0ULL, 0xAEFB5442750A5DBBULL, 0x5AA00C0B4689AEE2ULL, 0xD952F509213A4C5CULL
        },
        {
            0x09F631AC3D2CE44AULL, 0xC8A8C6480667F667ULL, 0x41FB99624B10FAFBULL, 0xAAF8A4023FDCD813ULL, 
            0xC9110964A3916815ULL, 0xAA4FA96B4FDC4BE2ULL, 0xDD33098BC3EBC36FULL, 0x1B1CFCA8E6FA82F6ULL, 
            0xF194ED81EBF83AE5ULL, 0x6D79C4C04881DC56ULL, 0x945D7D11CADF5352ULL, 0x025825AA2A3F000BULL, 
            0x4734FA4A3EF39A18ULL, 0xD43A72FF2B1035A1ULL, 0x7665691AE04118D2ULL, 0xCE8E973A072E0531ULL, 
            0x671A10F4D6AF9D52ULL, 0x666A266524FBE78FULL, 0xC0FDA4BC147455B1ULL, 0x466CF3E872049D42ULL, 
            0xD987B9C63400C83CULL, 0x030538AB225DEC0FULL, 0x69CADB3C8E2BC79FULL, 0x0D0DA2C08318E013ULL, 
            0x1E789B469AFA4F3CULL, 0x8CAFF4F48D134F0DULL, 0x204EEB325A40DCEEULL, 0x3640A9EB055B7BA0ULL, 
            0x47DA64660DB87A8CULL, 0xB87E7A93A280C97BULL, 0x313488187BF7F662ULL, 0x7B854A9AB04E396EULL
        }
    },
    {
        {
            0x56F0E1D2036C6A6FULL, 0x59473944905024DEULL, 0x8BE1B954EA85E59EULL, 0x3D96B579D469CA71ULL, 
            0x5F9BDB57ADE76A9AULL, 0x9AE3DC3EC5722A7EULL, 0xDFF8F71DEDEAB6FDULL, 0x77075643795102FAULL, 
            0x8584908D86A94C23ULL, 0x3B282A2D7DBFF2DBULL, 0x30DA40E3A5DABD7CULL, 0x1FDD3558169A6970ULL, 
            0x546EFAE095E2E799ULL, 0xEB9F53C740AC2317ULL, 0xEDD54FB6D51E895FULL, 0x4213E0A724CD4EE2ULL, 
            0xA9CF47E79B5E7541ULL, 0x52DD75DE4B7B9C5FULL, 0x3305913B38BE44A3ULL, 0xE01CB6CF851AC1BBULL, 
            0xEF37CB78BDD69A2CULL, 0xF544421C7EF11DB5ULL, 0xAF9FEEE6BA636F7BULL, 0x9742891C2A795381ULL, 
            0xF8F9F63D984C6CE0ULL, 0x32998F147F66CCA9ULL, 0x2E0003D89594258FULL, 0xF649BF37A2F57569ULL, 
            0xAFDBC2BCE79B8396ULL, 0x404209E72DB315F2ULL, 0x08A746207377523BULL, 0xA98D07479AE03FD7ULL
        },
        {
            0x2710995B34F9AD30ULL, 0xED8A773CEA5C196FULL, 0xE01B7C7825B24828ULL, 0xAD3BABE38675B36CULL, 
            0x5AEB06F6EA2C2AF2ULL, 0xDF7776FCE41CCFBCULL, 0xAD9F212EEA3A1B19ULL, 0xD5A1ED4039C1F523ULL, 
            0x7D435F9892AC7427ULL, 0x1D6C2855088EF03DULL, 0xE0175CC39DD2EBE5ULL, 0xAF16542DE4FCDC80ULL, 
            0x6159DD795552154CULL, 0x2266F11D20E6312DULL, 0x19324AE5FE15EC05ULL, 0xDA59329A8992393BULL, 
            0xB3FCA24FC9673A9FULL, 0xBF7F83A96AD0FE1FULL, 0x78747A7F56174591ULL, 0x2209C692E5D81EE0ULL, 
            0x7D1CF47555AFA190ULL, 0xACD4C0CE9AACAE9EULL, 0xE0CA4A587DAAA25DULL, 0xC77ADDAF844036CFULL, 
            0xF38A26945A9DED9BULL, 0xA25E25AEBBEF89BBULL, 0xFF6B585AE72F6A9DULL, 0x283CA0E298C7A2F1ULL, 
            0x1AF6B490CEEB2A2DULL, 0x19B5058ABEAF66D9ULL, 0x658D544765D82BD1ULL, 0xDD46D88B7DCDD910ULL
        },
        {
            0xDDCFE3DD97FAA5FFULL, 0x2A268200C295D35EULL, 0xC165EFAC79755FC5ULL, 0x1F994D6257EEC16FULL, 
            0x1B7F33EA55F0437CULL, 0xC394609621B00977ULL, 0x359D89122AAD7CEFULL, 0x35D3E1B1EF41EDE8ULL, 
            0x2B7548951067998CULL, 0xF29816188819EB06ULL, 0x6148059F04A5903BULL, 0x76AE0AF7BF8F2555ULL, 
            0xC2014A1BC9A1C499ULL, 0x6EB1011A914BC438ULL, 0x68A38BE6DFA1A2AAULL, 0x3E093A710BBC6EF5ULL, 
            0xECA05AEB837B9D92ULL, 0x89E37BEAD9C11A61ULL, 0x3024847ECE9F8FC1ULL, 0x7730901055591BFCULL, 
            0x98C7B710E58B6957ULL, 0x6AE43D78001123A8ULL, 0x87E56D8743C9891EULL, 0xC01B6F6F5E21D1DDULL, 
            0xCB880F0EE5DE3A1CULL, 0xC0CECD69B38C3948ULL, 0x43BA3CE2F3723ED5ULL, 0x0639D82AA0D91EC1ULL, 
            0x5C4ED98FD3F7179BULL, 0x565E6785AF9D8A29ULL, 0xD67D0D92ECDC83E2ULL, 0x7260CA5A58A7CB95ULL
        },
        {
            0x8E62BF1210418AF2ULL, 0x016005531EC5E5A6ULL, 0xC46F7263E38ADEB3ULL, 0xCD9559BF45707DF1ULL, 
            0x6C593F6F50B45FCCULL, 0x0219C2F95D283231ULL, 0x602E71B4F9E07846ULL, 0x94EA8E491913D3D6ULL, 
            0xE4A7D3D8A8A4FF95ULL, 0x518F8C4804A7090BULL, 0x46E3CFEC1F8668A7ULL, 0xCA114FC6EC59E1C9ULL, 
            0x5891142F30B0A06DULL, 0x5D94BA4E93B1CE1EULL, 0x0800953C471C6AE5ULL, 0x8782D93FE104AFD7ULL, 
            0xAEA3EBC87169BAF5ULL, 0x27CF420FA3832CDDULL, 0xFD916B5852FA6ECAULL, 0x3DF8043E82AF6D50ULL, 
            0xAAF7ADB0031DDA1DULL, 0xA1F41129A1824B80ULL, 0x564A0DCC9D02C5B8ULL, 0x4A32847068736A26ULL, 
            0x7172AA4F8E853AF4ULL, 0x95E32195F423AE68ULL, 0x9D52F5DD0524B341ULL, 0xC6AD401CA1705E41ULL, 
            0x97E246FF0CC2AE18ULL, 0x8B35B8F3F701F4A6ULL, 0x3192AAACB07BF602ULL, 0x84B4B1824175A1D6ULL
        },
        {
            0xD9972B34FDD68D95ULL, 0x7F5260099E651E05ULL, 0xED37A35382585041ULL, 0x23A1BC2AF04B62D5ULL, 
            0x820C28E98695A31EULL, 0x5B5E651640BC6AD0ULL, 0x2319DDE7B8465C39ULL, 0x0752D90DC9E61895ULL, 
            0x8A6897AEF876D6EDULL, 0xEBC4836F93DCC744ULL, 0xD94D93F6C391746CULL, 0xF74494D89126705FULL, 
            0x53CDEB26B4AFFD4EULL, 0x50DCF3345DBEA100ULL, 0x3BBA4935554269D0ULL, 0x00D445F9E6C309CAULL, 
            0xB41C5FFCA91A529EULL, 0xEBF686860DE30ACBULL, 0x0E63497842030619ULL, 0xD712FD23FE6C391BULL, 
            0x47554E822BEDE197ULL, 0x9A7B35C5C052F400ULL, 0x664B751728FF1C54ULL, 0xB8EFF1EC9B2ED6D1ULL, 
            0xDB9F6220D532EE7DULL, 0xD39BA2A880BB54B7ULL, 0x452CDB760F1A0661ULL, 0x78EEE5825C8E555AULL, 
            0xA0D2B1AC7203CBA7ULL, 0x334BE2193A5CC30EULL, 0xA0A1E3B6DAED52CFULL, 0x8C8F1F88AB40D8BAULL
        },
        {
            0x044BB8F99FDBDF58ULL, 0x2997EEA5E2F122A8ULL, 0x77FEFAB10FF23E74ULL, 0x7EE757221C041ED4ULL, 
            0xA2D4E965F3AB6CFCULL, 0x06732852A31C3826ULL, 0x3B1A33B3B3D27F76ULL, 0x2A4A0F9977456741ULL, 
            0x9886F91D29391C47ULL, 0xA4F5375EB6AA1B65ULL, 0x6DE1C6269FD6AAEBULL, 0xA21B3D6CD9F9696AULL, 
            0x7363B02D47F316ABULL, 0x86221EFE3C49BF7CULL, 0xBE294FBB9CE32C12ULL, 0xDABDC89E357D8D0CULL, 
            0xDB17A65797DD2960ULL, 0x6D384DED82A16569ULL, 0xAB814C4014562AD8ULL, 0xC0175CDC2E2937EDULL, 
            0x9E7C1F9705A513FDULL, 0xB59A81AA626729DAULL, 0xC66BBDBAEEE9E199ULL, 0xECF372568617AEEDULL, 
            0xCCC18B853724B0D0ULL, 0x0532D5C01AE3E066ULL, 0x1AD88136A7FDE779ULL, 0x348D03489DB72269ULL, 
            0x865E18EC9D5CD796ULL, 0x4CB6B827BE46855EULL, 0x0191DCBB0C86F15BULL, 0x6F27E8886BB8F96CULL
        }
    },
    {
        {
            0x7B96339C016848A5ULL, 0xBECF616F38F97888ULL, 0x6B1CABEB7B552026ULL, 0x1FAF2A048D8252A2ULL, 
            0x926D3458F5DA9791ULL, 0x65484CE2928A30C2ULL, 0x5819C13AF11520CEULL, 0x1BF483CA624F89CCULL, 
            0xD078928AB00CB6DFULL, 0x84C2F96081E8EAD1ULL, 0x1D15725168043614ULL, 0x2F26FEC65E275803ULL, 
            0x98B82240A1EF6340ULL, 0x96AF06B2C27ECEF0ULL, 0x55A4A08B4893A8D3ULL, 0xF01D797695968727ULL, 
            0xC21C618D28F08B2DULL, 0x6CC13BD2D5CD3A3CULL, 0xAEF626B181F83935ULL, 0x698831D223A14D9AULL, 
            0xAC6001A82AC755F8ULL, 0x95297108C38C5038ULL, 0x47E5534DC79BAD25ULL, 0xCCAB121A2A96FBA7ULL, 
            0xBED9FC3E715C2898ULL, 0x4523385353096499ULL, 0xDD29785F2C81D11DULL, 0x501FFBB4B7684E59ULL, 
            0x88AAF050205DB2D2ULL, 0x2BA5974CCBA4108EULL, 0xA060D92A93CFEA70ULL, 0xD1E8F042D9CD4EB1ULL
        },
        {
            0x74EFE2B70B8AB1A0ULL, 0xC0F93BAA65C311FEULL, 0xA6C5E2A87C7D7585ULL, 0xA886CBDE3F278FC7ULL, 
            0x3E7ED406C469B2EEULL, 0x7BE8CA83CDBA8217ULL, 0x13D4254F025985D5ULL, 0x805C5754688A061EULL, 
            0x4529A81F480BD766ULL, 0x16AF0AC8E57C495FULL, 0xC348445C77B06BA1ULL, 0xE8111A29B190440EULL, 
            0x938E7AC25EFDCB25ULL, 0x50188F5D0DE777BAULL, 0x611F29F0584CAB73ULL, 0x3FD3A46199BBAF37ULL, 
            0x551E83B9BB95080EULL, 0xB5ECC633F85CFF5FULL, 0x9FDF8300EDC7399AULL, 0x8E58DBD2C5B4C83DULL, 
            0x0FB5C2B16914E6FAULL, 0xBCB63A2A5BC94DADULL, 0xFFCF0D143B1FC9D2ULL, 0x41696C0EBFCC7C09ULL, 
            0xC1136C746B505205ULL, 0x5EAE3C072401D60BULL, 0xA3D84EA564B39F83ULL, 0x36237D0EF43F0CD9ULL, 
            0x0CE9F674DA5DCFB2ULL, 0x4A569F992B61638AULL, 0xD2D95940D772A8D1ULL, 0x10CF111BAF031D92ULL
        },
        {
            0x1ABC6F50CD0CA090ULL, 0x54B9777596442762ULL, 0xDE62135F0E635000ULL, 0xAE55101085C101E8ULL, 
            0x650947D477E400CFULL, 0x81B945A866F1E20CULL, 0x161BD9F5E6D7B0F8ULL, 0xAF7307FAB975EF10ULL, 
            0xAEFD910B32A6A520ULL, 0x06F214BC56AEC000ULL, 0xD3B41BBF8F6DC434ULL, 0xEC069F6F286B0609ULL, 
            0x1EFB88DE18FE89DEULL, 0xF3AFF51DE9F671AEULL, 0x7F386DC2EAB61BE8ULL, 0x62AEA6C2CED7DA59ULL, 
            0xBECF808F74064160ULL, 0x9A53B106E770BEEFULL, 0x250C9FB03CBFD4F8ULL, 0xC0AAC2975EEB381DULL, 
            0x4801564F0EBCFB26ULL, 0xE978B6C159177D88ULL, 0xFC9C9303E7A335B5ULL, 0xFEE2FA09708B3CD1ULL, 
            0x0263BE1C1C7F140CULL, 0x4E84CA2C3EF9073AULL, 0x3BCBD29C598E42D2ULL, 0x6E2D05CADAD69B27ULL, 
            0x447F0AFBD4D65FF8ULL, 0xEEB1EA8F4345C467ULL, 0x69DC41F70898EE7FULL, 0x8A5D273F66DC076CULL
        },
        {
            0xA0F237B747A78154ULL, 0x66B7B2A2CE13C919ULL, 0x75D34AD09F14896BULL, 0x6D32049608486158ULL, 
            0xEA91CF13DF0D2375ULL, 0xFBB48A81742B7E36ULL, 0x1160FF1B08850CC8ULL, 0xC6B1DC752D6EA215ULL, 
            0xC71E1C3E71915BB8ULL, 0x08F1E3F8A2CB81F2ULL, 0xB38AE8CEAF9351B4ULL, 0xC56BD2866481ED1BULL, 
            0xF86B32542E1CA38AULL, 0x8E7E19DA07BD95A7ULL, 0xAFD8C7DEE8DA93B7ULL, 0x698A0553EEB618D2ULL, 
            0x37F6951AFB959A76ULL, 0x236E79F6E47B8E74ULL, 0x00126130E29D3DA9ULL, 0x8EBFAC4629261242ULL, 
            0x314CAA4917C4A2F2ULL, 0x87CB2BA3AC83F95FULL, 0x430D97E9C3148B46ULL, 0x71F26BDBE9A9FDF9ULL, 
            0x2C87BDA669CA91ACULL, 0xFFD554520C0B7BD4ULL, 0xE25F51AC7E66EE5DULL, 0x60C63CD082800F69ULL, 
            0x845D94BC24A1EB2DULL, 0x1F88E4A28380326CULL, 0x5F9C22C4007BF6ADULL, 0xCA518DAB087CDC31ULL
        },
        {
            0x736643B408D8F1EFULL, 0x60DE0381FE98B443ULL, 0x41A11F7F69365EAEULL, 0x376556F3EE596336ULL, 
            0x78110DC794A9936EULL, 0xA4232FA6A1200FEBULL, 0x58FD29588996099FULL, 0x84374F47C600A7AEULL, 
            0x7E8E10C30B37898FULL, 0xCD68E4C150186071ULL, 0x0ACDAF765FA47C2BULL, 0xE38B852A31B31C99ULL, 
            0x1FB8ACEBC3203B06ULL, 0x6B1DDF69CACB282CULL, 0x657CA1CE976305CEULL, 0x6200028C72800B10ULL, 
            0x4B3F46BF10D42C83ULL, 0x43FB9BA15D40491BULL, 0x4AA77912AD065F0EULL, 0xB74D937A62C11CDCULL, 
            0xA9671FFD27BB1607ULL, 0x44D577D1E9EA8C85ULL, 0xA78C3A854B71B0B5ULL, 0x0CD7585D02A8E723ULL, 
            0xEA108C729BBEC719ULL, 0xB57AF62713F980EFULL, 0x517543A662BBFE38ULL, 0x2E8BC7931DFA2609ULL, 
            0xD54B0E452ACA5F90ULL, 0x038726DBEF2ADF91ULL, 0xC369EA89A2171E76ULL, 0x5C80AF77BC0DD6A2ULL
        },
        {
            0x9296573EFCE2924FULL, 0x1F0B5C6898BE6BE2ULL, 0x3F963EE1F1B7319DULL, 0x8720F743F9504172ULL, 
            0x321BC9331CF3CCF0ULL, 0x42DF1DCCCC272FC2ULL, 0xBFD4A9960D3CC2FDULL, 0x6E33CB6D0F195845ULL, 
            0x3E4E2446FE5B28D8ULL, 0xC4FBD7425CEB63BEULL, 0x675638F6C5E12278ULL, 0x4113A54ACE689323ULL, 
            0x49556C23F25639A3ULL, 0x2F3B91081EA8C736ULL, 0x9E7CBF7981C03920ULL, 0xC6EECDD964E987E9ULL, 
            0x2C30617CE9218A5BULL, 0xB2D75C055DACC351ULL, 0xF697337DF709D681ULL, 0x52BF687393A1FFB7ULL, 
            0x88A58895B1DAC5ADULL, 0x4CF291BDB69FC1D7ULL, 0xC76EFE261EB6473CULL, 0x62C2983491DA3F73ULL, 
            0x31C804C52E4B7DD8ULL, 0xD7B9F32C82739978ULL, 0xC72CD572B05DE499ULL, 0x9106FD31104EF164ULL, 
            0xA5C55EF5E26927F6ULL, 0x7B18D61D2CC64628ULL, 0xFF179C7547C00157ULL, 0x43712B73AF95353AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseHConstants = {
    0x8C633C780AC4CBE7ULL,
    0xBDE3BB1104128B38ULL,
    0x6A90BD287CCA9439ULL,
    0x8C633C780AC4CBE7ULL,
    0xBDE3BB1104128B38ULL,
    0x6A90BD287CCA9439ULL,
    0x253D7D8364CCF01BULL,
    0x3F77809ED8822D64ULL,
    0xBC,
    0xD1,
    0x4D,
    0x23,
    0x65,
    0x5D,
    0x0E,
    0xEA
};

