#include "TwistExpander_Capella.hpp"
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

TwistExpander_Capella::TwistExpander_Capella()
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

void TwistExpander_Capella::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE89A863A020DEEABULL; std::uint64_t aIngress = 0xED4076A6E0C71973ULL; std::uint64_t aCarry = 0xFD348EF437AF6459ULL;

    std::uint64_t aWandererA = 0x9C3B2537A2B060AFULL; std::uint64_t aWandererB = 0xF55F3E33F5C23E31ULL; std::uint64_t aWandererC = 0xC62E153B82B575EBULL; std::uint64_t aWandererD = 0xED73B7C1C348FE7CULL;
    std::uint64_t aWandererE = 0x96E87CA3652EF934ULL; std::uint64_t aWandererF = 0xBD9358437EC83ECEULL; std::uint64_t aWandererG = 0xE645A752EB5B6F9AULL; std::uint64_t aWandererH = 0xF16486F0449796BEULL;
    std::uint64_t aWandererI = 0xA68C1DEFA11A904EULL; std::uint64_t aWandererJ = 0xDDD27F466B8B4651ULL; std::uint64_t aWandererK = 0xC8A365310876DC9EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16652721216461423905U;
        aCarry = 17254677116691637437U;
        aWandererA = 17037758106314892360U;
        aWandererB = 18158086565690171662U;
        aWandererC = 13524081033902392637U;
        aWandererD = 9438482601356742969U;
        aWandererE = 9694594746501094542U;
        aWandererF = 13799641705248787975U;
        aWandererG = 14066165249598898078U;
        aWandererH = 13462425008581457682U;
        aWandererI = 14914021930632352776U;
        aWandererJ = 12871583995384069410U;
        aWandererK = 12860599951958735440U;
    TwistExpander_Capella_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Capella::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x856ED8FA4D00675FULL; std::uint64_t aIngress = 0xD5B0D096C6B599B5ULL; std::uint64_t aCarry = 0xD7ADB771EF44F3A8ULL;

    std::uint64_t aWandererA = 0xBAFF504A38FED19FULL; std::uint64_t aWandererB = 0xC66C4E2A250F8A8DULL; std::uint64_t aWandererC = 0xA52CF550F24DD655ULL; std::uint64_t aWandererD = 0xC2C75F6E0168C3A1ULL;
    std::uint64_t aWandererE = 0xF997BD90C9E45127ULL; std::uint64_t aWandererF = 0xCCE35F662C6F9EA5ULL; std::uint64_t aWandererG = 0x91B6122C42BF0A54ULL; std::uint64_t aWandererH = 0xAD14A893369A2250ULL;
    std::uint64_t aWandererI = 0xEF3D6652201A93F0ULL; std::uint64_t aWandererJ = 0x8CE8BD954AEECC75ULL; std::uint64_t aWandererK = 0xFEE00ACFDD70661DULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16831712855756965719U;
        aCarry = 11075117810866891620U;
        aWandererA = 15059853055181529444U;
        aWandererB = 10425048544160767646U;
        aWandererC = 16722871813295133431U;
        aWandererD = 18434403369332793116U;
        aWandererE = 15543234029926307066U;
        aWandererF = 13863648342200666112U;
        aWandererG = 10163612508095710737U;
        aWandererH = 9555881573218000214U;
        aWandererI = 14718516830429274202U;
        aWandererJ = 16967092434011691877U;
        aWandererK = 15862926813789843538U;
    TwistExpander_Capella_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Capella::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xF7B3C3EEF7FE35BEULL;
    std::uint64_t aIngress = 0x867F54EAA034E526ULL;
    std::uint64_t aCarry = 0xDE57F75D399440C0ULL;

    std::uint64_t aWandererA = 0xF22B5F58DBE76020ULL;
    std::uint64_t aWandererB = 0xEB5C000DCD2F8359ULL;
    std::uint64_t aWandererC = 0xF35DD6B608044014ULL;
    std::uint64_t aWandererD = 0x9C651BC7580CD61DULL;
    std::uint64_t aWandererE = 0x990B6184526C6B73ULL;
    std::uint64_t aWandererF = 0xEAE0B9B526F5CBADULL;
    std::uint64_t aWandererG = 0xD4C7F10A3F3B40AEULL;
    std::uint64_t aWandererH = 0xFB79FE32CB3AF161ULL;
    std::uint64_t aWandererI = 0xE04DF8D8A2F35696ULL;
    std::uint64_t aWandererJ = 0xFB87D752DFC7A926ULL;
    std::uint64_t aWandererK = 0xB494819AD9C0FF78ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Capella_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    TwistExpander_Capella_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Capella_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Capella_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Capella_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 15 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1839 / 1984 (92.69%)
// Total distance from earlier candidates: 25994
void TwistExpander_Capella::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 689U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1446U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 89U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 382U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 489U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 90U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 485U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 792U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 734U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1133U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 237U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1939U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1197U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1722U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1273U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 782U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1472U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1272U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1746U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1002U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1410U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 790U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1311U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 830U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1080U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 343U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1607U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1908U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 909U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1052U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1642U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1457U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 899U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1636U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1759U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 356U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 838U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1173U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1285U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1999U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1290U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 583U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1116U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 926U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1293U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 867U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1716U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1810U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1209U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1563U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 660U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 320U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1011U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1032U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 201U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 454U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1841U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1053U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1334U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 592U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 745U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 317U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 603U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1162U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 338U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1165U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1309U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1409U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1983U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1614U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1632U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1301U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1282U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 548U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 400U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1143U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 874U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 477U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1134U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1694U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 329U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 319U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 618U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1203U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 475U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 394U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 255U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1786U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 535U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1506U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1164U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 978U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 955U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 632U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 799U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 479U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1646U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 980U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1010U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 458U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1861U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 691U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 93U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1418U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 366U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1241U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1073U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 368U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1520U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 789U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 566U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 35U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 755U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1448U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 560U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 823U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 259U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1579U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 798U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1121U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1963U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1443U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 159U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 630U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 564U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Capella::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB4904FF73AA484FDULL; std::uint64_t aIngress = 0xD36EA168D4A17755ULL; std::uint64_t aCarry = 0xFF35B8F548FB3609ULL;

    std::uint64_t aWandererA = 0xBEDA4047ED5CBC2AULL; std::uint64_t aWandererB = 0x89AFE1AF1A7F85DDULL; std::uint64_t aWandererC = 0xA21BE21964D929B1ULL; std::uint64_t aWandererD = 0x90270D00852F3B28ULL;
    std::uint64_t aWandererE = 0xE1C2EE8E32E2CA64ULL; std::uint64_t aWandererF = 0xC61BF563D79B57C2ULL; std::uint64_t aWandererG = 0xB0FBB748A1F6F0E3ULL; std::uint64_t aWandererH = 0xBC4F1D9AE5412EC9ULL;
    std::uint64_t aWandererI = 0xA70CD2B4B43AEA7BULL; std::uint64_t aWandererJ = 0x99D6F3EBD108FBD2ULL; std::uint64_t aWandererK = 0x8E8473DC9394DB7AULL;

    // [seed]
        aPrevious = 11038164128489650804U;
        aCarry = 11889795326246723160U;
        aWandererA = 11186956565137022153U;
        aWandererB = 14214966899299610947U;
        aWandererC = 12971633570749858905U;
        aWandererD = 17581744837453143161U;
        aWandererE = 12703071181397842751U;
        aWandererF = 12557083580201014304U;
        aWandererG = 9779202641613267227U;
        aWandererH = 14675781766356953986U;
        aWandererI = 14372541677903490385U;
        aWandererJ = 10710050096946527368U;
        aWandererK = 14390313810011805707U;
    TwistExpander_Capella_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Capella_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Capella_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Capella_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 15 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7671; nearest pair: 470 / 674
void TwistExpander_Capella::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 195U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2083U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5606U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6914U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3602U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3035U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5589U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 157U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1066U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2230U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6951U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5306U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3181U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5274U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2260U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5045U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 406U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 995U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 588U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 468U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1238U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 383U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1141U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 710U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1851U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1731U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1654U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1781U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 538U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 908U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1221U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1134U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1289U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 2043U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1034U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 15 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7668; nearest pair: 481 / 674
void TwistExpander_Capella::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1869U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2845U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6848U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5352U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4550U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2089U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5183U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 928U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6838U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2628U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6842U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5853U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6180U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7636U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7881U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1242U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 453U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 646U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1645U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1267U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1868U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 864U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 55U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 491U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1844U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1213U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 462U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 105U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1699U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 737U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 342U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 288U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 926U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1789U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 519U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Capella::kPhaseASalts = {
    {
        {
            0x5313BEA168986161ULL, 0x5216622DA1335A21ULL, 0x12BF6D9EA57B1898ULL, 0xB004E911EF9667A1ULL, 
            0xA4087E4DDE0D9861ULL, 0xB30E7ADCEB94706AULL, 0x26E43FE5422F7E5AULL, 0xD506D67ECAD5BB3DULL, 
            0x56BD2F30821B6E97ULL, 0x6F69E4C630678E09ULL, 0x2832392776BDC7B4ULL, 0x3382728D23371BAAULL, 
            0xF53E5AC6407D49DEULL, 0x9E225ADA8562A5ABULL, 0xD3130039FC733796ULL, 0xD1134DB50F6D301AULL, 
            0x60155646179D139FULL, 0x05BDB5C7D7BF9672ULL, 0x932A9845D463FB2AULL, 0x4CC9B8846D2A80B0ULL, 
            0x089EF77A8E39CD7AULL, 0x070F38F0A6F482B9ULL, 0xFE6D93524199930EULL, 0xB95A034A1F716AA2ULL, 
            0xC9F2C7F4C119709DULL, 0x1C6ECA64833F1C7EULL, 0xBDE78C5AD17AF024ULL, 0xC04CA9A990711600ULL, 
            0xB293E8D9643F8F28ULL, 0x2F183FF48ADF7016ULL, 0x10F75C440E40A5ADULL, 0x2D2A2B46074F5A0DULL
        },
        {
            0x8C8C1088EF6A427AULL, 0xBC70F1010FF8076FULL, 0x26862E86AFA4D070ULL, 0xAAA3BA9FEF6EA95EULL, 
            0x9EA1FADE3537C431ULL, 0x049A8C2E079A2D84ULL, 0xF7246E1E3038D8D4ULL, 0xDB3842836EEB9F94ULL, 
            0x19E2495B11EF7248ULL, 0xA8203933FCF082B4ULL, 0x307E1C6CA6744036ULL, 0xA2997E8D8B344697ULL, 
            0x897F4B235D97D774ULL, 0x921D4A8CE6EB35ECULL, 0x77FEE0CF73F2A586ULL, 0xA7A3707A3D392B6EULL, 
            0xC8A42569D9C1054CULL, 0x38A0341FD9DC5124ULL, 0x00A9C1CD4DDA9E5CULL, 0xA00904A41E13BBADULL, 
            0x37D99846714F4AACULL, 0x9A27E0481840EEBCULL, 0x3BA4ACFF666C7F80ULL, 0x3EF93B52F9B35EDFULL, 
            0xB1A1B5130EAD558FULL, 0xD36FD7F1F58D95B1ULL, 0x98B88E1CCF2D87FFULL, 0x3D6B683AAC73222CULL, 
            0xA12D12A91D4E3E21ULL, 0x872D5A4F5A2A5459ULL, 0x5BE9033B63A31EBDULL, 0xEDAE9EEE3ECDF585ULL
        },
        {
            0x3DD3FBA2E445CB09ULL, 0xC1A5B90BAF76978EULL, 0xA55408C0646905D0ULL, 0xB5B4E0485A9BEFA5ULL, 
            0x3171021C4570995DULL, 0x221F58253AAD39E8ULL, 0x1B8E1C287E30AD4DULL, 0xD644E19CD5200F12ULL, 
            0x0152639F75758652ULL, 0x655267D45C47AE2DULL, 0xAB58560855353CCCULL, 0x6B0818259CB5BCBCULL, 
            0xDAF49090F0DA9710ULL, 0x9224DFE5145F2425ULL, 0x45A0FA42ED568B36ULL, 0xEBF55394980B0334ULL, 
            0x52E0087711FD960EULL, 0xA19F51663A1AE3EBULL, 0x11DCEB4513B9F6C4ULL, 0x041A66C4F778DD07ULL, 
            0x26E0A2EA2EA1813BULL, 0x6EED7A4E03C55EDBULL, 0xE96F2F23A6AA1D2AULL, 0x4F953974AA335845ULL, 
            0x9E2056B2E25385A3ULL, 0xA78ECC10DDB00EBBULL, 0x4821A58F50AEA650ULL, 0x86527AB4B2C57CF0ULL, 
            0xF3908253ED97B19EULL, 0x47A640617B4A22A4ULL, 0x52ED7E41166C43DBULL, 0x2794156A04790E72ULL
        },
        {
            0xEE0A7B10ED56487BULL, 0x9FF0FC292E83C969ULL, 0x19AE03216F7BD9D5ULL, 0xD27E995EB9A04880ULL, 
            0x19C0F39D46E4F08CULL, 0x08B43694A8C4B12AULL, 0x88572A7E73A1E203ULL, 0xA98C2085A6C1A160ULL, 
            0xC687216E74344886ULL, 0x615CC6B8819EFCE5ULL, 0xB030AE1622C45D65ULL, 0xC3BB5FCB1B0A2486ULL, 
            0x46ED55AC5122B8FBULL, 0xB1AE8F8FBF4FA33BULL, 0xD3683642C458992FULL, 0x4391AA7AEB92C676ULL, 
            0x1078169F3D749141ULL, 0xA197BEC4C290B0D2ULL, 0xB2A17E97D3572DD9ULL, 0x559E9DB343D72484ULL, 
            0xD60C07840D80C865ULL, 0xEAD2B4E48872BA44ULL, 0x2DB8F5A5635E2B3AULL, 0xCFF80CBA51C348E6ULL, 
            0x06DC341513D9541BULL, 0x10E24D745D38EB89ULL, 0x01ABE5AD516064A5ULL, 0x6CC21C352EC4ABC1ULL, 
            0x92A1AD28970DFA90ULL, 0x5F3B2DC5CD889DF5ULL, 0xA71881F1E5B236FBULL, 0x4CB1FE4EA8756AB8ULL
        },
        {
            0x9976BF16848EFDEEULL, 0xAD1A40228D87D55BULL, 0xAE370B0EB659FC51ULL, 0x11C4CB10A0DEF8CBULL, 
            0xA7D2817AC72EC64DULL, 0xB654DB627EFF30AAULL, 0x16F13884586F67E8ULL, 0x51E4E528A2067912ULL, 
            0x1FA8623B1EC9BB86ULL, 0xF19098888DCDB793ULL, 0x64D4D9897B8A2301ULL, 0x3C24B7FF60E5AFBEULL, 
            0xEBF07A048DB07CEFULL, 0x1926E81B9E788C68ULL, 0x301A83CB1975484CULL, 0x47220FA476E55B59ULL, 
            0x4BDD8B0FD0498AF4ULL, 0x7F5278E147963F55ULL, 0x28B9C614719FBF7BULL, 0x0071FE90A1BBF794ULL, 
            0xCD59F72298CF58FDULL, 0xED792CA32169D79CULL, 0xFD14575EB4F911F1ULL, 0x42A2A554CDA5BC10ULL, 
            0xD412AB9BDE82C5BAULL, 0xA255A1F8148CE5D2ULL, 0x4AA03EC9CA580E93ULL, 0x40CBBACEBED4E130ULL, 
            0x7B8116571016249CULL, 0x3D5E2B342458063BULL, 0xB20FD3D155EE4016ULL, 0x0995BBF205507168ULL
        },
        {
            0xB71EC9E23505F76DULL, 0x439485EE44017CD5ULL, 0x5370DF7C355173ECULL, 0xA3934EBD7E7476EEULL, 
            0x801CF81A794494B9ULL, 0x2895CA6A40DCB1D1ULL, 0xB19DB85FB23A78FBULL, 0x13D00ABC6FCDFE17ULL, 
            0xAB0B7FE445CA5B09ULL, 0x24535084EB977B3CULL, 0x0F3DAB5AB610AD82ULL, 0x9AC8C43AEB1110B8ULL, 
            0x8A85BC53209DE574ULL, 0xC10DA4E57362A6CFULL, 0xDD303061BB428A4DULL, 0x0DA18829009C40DDULL, 
            0xC959E2D72D02536CULL, 0xA6FF0A075807BDCAULL, 0xB0BF8BAA0AD32B15ULL, 0xD79EBD86751188CBULL, 
            0xDE1CCEB996CADA67ULL, 0xF869F720397C14CBULL, 0xD184F568A15DCC74ULL, 0x2BE526AD52C0D2DDULL, 
            0xC1E46C2314BCCF1AULL, 0xC6AC14575FF0075EULL, 0xC19DD2EF283356FDULL, 0x87C0F3723BA763F2ULL, 
            0x29F3A1400C53CD95ULL, 0x16AE41ECA9A91610ULL, 0xA3058400B3D4BCFDULL, 0x5B2F1FB343E21B5EULL
        }
    },
    {
        {
            0x8FA50BE6DFF7EFA1ULL, 0xC835B8B39CFF6BE1ULL, 0x10618FB6E936D389ULL, 0x77CB5254D66C747EULL, 
            0x6A40522C7FE8D2F0ULL, 0x5BB1BC6BF4CC89E0ULL, 0x639C760146D3E2A5ULL, 0x15FC70E2FBF1143CULL, 
            0xDBD60E1F603F99CBULL, 0x78CB4A7C1D63C07DULL, 0x991C231891FD26CEULL, 0xCAACCB7F7CD4DDFAULL, 
            0xC6E6AB1D7D6F41F1ULL, 0x9A99811790A6A4FEULL, 0x92F3792880CBA89CULL, 0x8BE968338BE28B29ULL, 
            0x03B5E2E74C84033FULL, 0xF4B0D45F8976D09EULL, 0x5BA91908316A11A4ULL, 0x655659081A352664ULL, 
            0x09FFAF244EE2AE7DULL, 0x310EA23C1D25C3D1ULL, 0x5245FEDEF23B2374ULL, 0xD33587893EB29B79ULL, 
            0xAF9160C44202AF8BULL, 0xCE39DC2D8A2267E1ULL, 0xEE2FB9AAE4B46EF9ULL, 0xD3B502AFED6ECD31ULL, 
            0x5BC80863659B0777ULL, 0xA8E5B56185DED304ULL, 0x84D73519566225FFULL, 0xB1A912EE8745E151ULL
        },
        {
            0x94193B8FC3F85C78ULL, 0x3FDE8A4BF1D34F65ULL, 0x96A6B213F4E0A779ULL, 0xEC7DC2C4848BC06FULL, 
            0x0DD492A14A953C68ULL, 0x433164913D3AE75EULL, 0xE9F77C28B9AE7E15ULL, 0x413090913830F0C3ULL, 
            0xFD2089DCE8763724ULL, 0x0B53481B4D7E7BF5ULL, 0x8194EE789AC9C442ULL, 0x9DBF333145DCF9A6ULL, 
            0x61811F8981AA43EAULL, 0x53BF47E19DFD2C69ULL, 0xA9012CA7B9A7B912ULL, 0xDC69F4A511CFEFA7ULL, 
            0x55EC68E233A7A163ULL, 0xFCA3BCAB60F13979ULL, 0x6B971D567A670EDCULL, 0xEDE7F32596CF71E6ULL, 
            0x29DED8AB82C64CA4ULL, 0xE19A716394DA9568ULL, 0x3482D67DF9B87B0DULL, 0xE60C9285C7947BB3ULL, 
            0x77627325198F1E9DULL, 0xCA2BBEC0D961636CULL, 0xA254FE9144CD1756ULL, 0x29DB6B0B3F5FC8A2ULL, 
            0x2F3C82D1F4EB500FULL, 0xA2F4A4F7FF77CF95ULL, 0x9210B04741D9C907ULL, 0x865CA6975FEB1E22ULL
        },
        {
            0xA05DD64E1EE4FFE2ULL, 0x5DD559D27547187AULL, 0x4359B9AA9EC575D0ULL, 0x34844A5F0BBACAD0ULL, 
            0xA8872F87A23401D7ULL, 0x1986D7EA289299ACULL, 0x7A7549A57766766DULL, 0x8B3C309068377AFEULL, 
            0xB9DFBE357872516FULL, 0xC6B6FAD1920ACEFBULL, 0x647BC52213D87989ULL, 0xE23D9C0E58DF3B2BULL, 
            0x8B7476EE89B20F9AULL, 0x1C6200A9C96A368FULL, 0xE284AC6FF8E9873AULL, 0xBABAA712810D31B0ULL, 
            0xA6EB261376F931FDULL, 0xB8A800DF30CB9BACULL, 0x8D95C04C1B2AC127ULL, 0x2AD1A80CDB1DCB4CULL, 
            0x0B5FCBFDBFA52AD2ULL, 0xD26C295749CFEDFAULL, 0x91287E95B8350938ULL, 0x21E44426F988CE54ULL, 
            0xE82C5D0098335EA6ULL, 0xB0B4D14372131D48ULL, 0x4E52B2D95471CC06ULL, 0x7B18D26F63162281ULL, 
            0x279FFC2515B9D296ULL, 0x21FF6DB0EA010902ULL, 0x313C54D7577D7471ULL, 0x29DFB4D9E1666481ULL
        },
        {
            0xB464C774B02F58B3ULL, 0x4136A960F53EC93CULL, 0x5FC35AD32934E6CEULL, 0x895D59207EC112FDULL, 
            0xA2643B07B384BEAAULL, 0xF26625CC44E8FF21ULL, 0xCBAE648FB2316355ULL, 0x42B13FF69FF74EBCULL, 
            0x478C4384B0F2E29BULL, 0xB6BAE422850CC23BULL, 0x56325CD8CD5C1576ULL, 0x1404888713BC7AEDULL, 
            0xB648AC7D46477566ULL, 0xEC3EF66F4AD30B77ULL, 0x8EE341BBE517320DULL, 0xF0B7144079D1E108ULL, 
            0x92F1DE4EBD10FB1EULL, 0x87BA9B908BF8500FULL, 0xAB2C8DB0CDACCA90ULL, 0x27179C2F0F111DD5ULL, 
            0x5B4572C2C3D67A5FULL, 0xB07BB067CFAFAAFFULL, 0x26A1A89311E701AEULL, 0x9711EFB4C6CA490AULL, 
            0x57DDA0ADA885D9E0ULL, 0x9775A9F5B4619889ULL, 0x249774BFBE43CBD5ULL, 0x8C24F1EC818B6776ULL, 
            0xB30ECB64450B9F20ULL, 0x2DEDF71653BCEB62ULL, 0x64C5FA1A04629478ULL, 0xDC0027051EFB7B18ULL
        },
        {
            0xCA9059D967502EC2ULL, 0x050D0AD4B6E9B44FULL, 0x7312372A1B332C79ULL, 0x5BD136BBDB10580EULL, 
            0x181C10C0C81CA7CAULL, 0xA8D63446154A75D1ULL, 0x7D69687346BC1504ULL, 0xFD4E932519411BCAULL, 
            0xA5861307DD2BBA88ULL, 0xC76316E952A06669ULL, 0xD9154251D23F4BADULL, 0xE1C951ADC0143A21ULL, 
            0xD6EB79F8B5A1D3BFULL, 0xB840D197920370A7ULL, 0x42E06C5BFF890528ULL, 0xCE94E424244E20A3ULL, 
            0x148FBE8BEC465CB7ULL, 0x124E20F9F3A2FC33ULL, 0xDB517CB50123E494ULL, 0x97B23C6D77261373ULL, 
            0xD182FA33C9672D07ULL, 0x75A2BCF3BE385A84ULL, 0xEB6557B2CB952154ULL, 0x4B29A80184D42C5CULL, 
            0xC226964F23A40708ULL, 0xC915D549D2910A30ULL, 0x1F72C55FA0E1FE1BULL, 0xA27CF17523C50E84ULL, 
            0xC3E999A221FE3F5AULL, 0x697F1FCBCEA8E2FEULL, 0x075CAAA5AC666C5DULL, 0x848393B64C980F1FULL
        },
        {
            0x2D8C7DE317D50FBDULL, 0x3EBE66873AF0087FULL, 0x5B014AB353FFF77FULL, 0x0BDFD4706EC58A22ULL, 
            0x5E870DAB37E71D2FULL, 0xCA28F5B9F1451315ULL, 0xC2AC1BB57F586D12ULL, 0x2706B6DC50F17A70ULL, 
            0x80657DAB9F130997ULL, 0xF6A47847BB320631ULL, 0x4682FD01041C6AFFULL, 0x89236AE4C6D1BD7AULL, 
            0x846F0683F1BFE3F8ULL, 0x4A48526A0B0B157CULL, 0x110DF8868009C7AEULL, 0xED1C1EC92A778F8FULL, 
            0x2442BC54CC65B50EULL, 0x819F7A02410FA52EULL, 0x1F5157860FFD3683ULL, 0x1FE708CB682B3AF8ULL, 
            0xDB9D2B0DA25FA8C6ULL, 0x55590C1FC341EA26ULL, 0x024E15C67234B347ULL, 0x07CB86205CAA4A66ULL, 
            0xFC19356FB082DBB3ULL, 0x03F89E5727BA9133ULL, 0xEF6B2B5796172AA2ULL, 0xEC1BD9485387AAF4ULL, 
            0x819A7495BDC85870ULL, 0x0C4D8B12F1E88094ULL, 0x5ED062B993BBB862ULL, 0xC6C16D417C9F7665ULL
        }
    },
    {
        {
            0xEF6DB263968864AEULL, 0xF0111253D5896255ULL, 0x7FD67AD7170C09CCULL, 0x2D0DD0526070C698ULL, 
            0x3AF97E6C485A6EB4ULL, 0x69ADD14622E1CB1EULL, 0x2AF46991CC2E5752ULL, 0x3745505ED0A5FACCULL, 
            0x3B86A96F48F20EA7ULL, 0xAA979FBC8A18D2EBULL, 0xD1F1DE67F7036E1CULL, 0xA7DDFD877210B573ULL, 
            0x7B5F2551CBFFECE1ULL, 0xEBB0C1D06EDB569EULL, 0x25F4153CE108C273ULL, 0xF520E70DFA51A03AULL, 
            0xE31876474FC3C9A9ULL, 0x8A3B7C0BBFD187CEULL, 0x62C135BE77FF71F0ULL, 0xC20F2A945F68FFD5ULL, 
            0x31ED0B3A0A2230B9ULL, 0xF62B98CCCCDB55CCULL, 0xAE26274509D7C8CDULL, 0xA87CD36CD853AE65ULL, 
            0xEDA1816DB3B3170FULL, 0x9FD1D5CD9621D26AULL, 0xCEAB5B0FE1E7AEBEULL, 0xCE516696E1EBCA2BULL, 
            0x02E9B3E0AFF2D5C8ULL, 0x9EE7B3EEF5C89933ULL, 0xC71EC2E8DDE8F88FULL, 0x7596A4939392A1CFULL
        },
        {
            0x4C811B2948CF138CULL, 0xA7478CD42873152AULL, 0x7BDC592761E175CBULL, 0xC5DAABE86BBCF08EULL, 
            0x3A9382D4F6785DD1ULL, 0xAC528D4D4F472197ULL, 0x0B354A9969E3E49CULL, 0xBD3353806A7C46B2ULL, 
            0x0AD3F0F59A5DAB69ULL, 0x10AD4072BA9EE1F9ULL, 0x670E425491C15629ULL, 0xD69362D25E00AA8EULL, 
            0x03261520FD7B88D9ULL, 0x0F7381E63CD24544ULL, 0x4B70E597E916131AULL, 0x6A8A0A659C42E074ULL, 
            0x9087E80BD4EE9A95ULL, 0xA389D29B890D190AULL, 0xC677B00712704863ULL, 0xC548733E34B1E99DULL, 
            0x0104EF7CC5AA4BD1ULL, 0x80F40CE1A9BA3735ULL, 0xA53E89669CFD3B33ULL, 0x4D073D20E8134F28ULL, 
            0x6A1A9805CFDE7CE9ULL, 0x2AA2A6EF9EA6DE04ULL, 0x83D0EEA0135E104BULL, 0x6FBCA21E11BB6A96ULL, 
            0x49ED6CB8CB35E4C6ULL, 0x2A2FED64F6581BF1ULL, 0xF7C45CCC4C4AB82DULL, 0x89DCBD7265E0244AULL
        },
        {
            0x57F0C7F0C1034486ULL, 0x98DFD60F8A8C99B5ULL, 0xB92A69D00F223399ULL, 0x5FEA6AFECA2EE556ULL, 
            0x4AE21447A8B4012CULL, 0x03A9C8F8C556E64DULL, 0x76CCB306340F881DULL, 0x4114C3487CC36959ULL, 
            0x1F38479283DB9C35ULL, 0x5D2E862FD63BA5F3ULL, 0x41F5FD701B6F2323ULL, 0x3A46F2E639D19002ULL, 
            0xF26F7F7FAEF077B9ULL, 0x297CB6ECE5B0A95BULL, 0x0E7F0F46030D72EDULL, 0x219A0D07015BB315ULL, 
            0x4DAE26BB938F79D8ULL, 0xECCEF12AFDB54527ULL, 0x4A59EF2F6737CC14ULL, 0x5A5DCE3B0AC947BBULL, 
            0xF6C5CC83D4C959CAULL, 0xC160AFB703B9F4D1ULL, 0xC6823899B4EA7D18ULL, 0xF13B4EF594D5755CULL, 
            0x8C31010726E3F29BULL, 0x870BDCBD6E682D37ULL, 0x469E82F9D4A01873ULL, 0xB1CAA12866229A81ULL, 
            0x017BCD863F08D8C3ULL, 0x29E756D9FBF767D3ULL, 0x29BE6BF30D443720ULL, 0x4FB32FD757138964ULL
        },
        {
            0xB65EB45E2EF0C2E3ULL, 0x2168A3F89CBF10BDULL, 0x41DBCAD4649111B6ULL, 0xF19EBD38CF9DE357ULL, 
            0x635A3A7A3D06159FULL, 0xBEDBE69A0440A1CEULL, 0x17115894E088D970ULL, 0xF3AF3A4CF0EB914FULL, 
            0xA5BE916C3CA0AF9BULL, 0xA5F774B96B8EC7E6ULL, 0xD3DE3B185CFD4B05ULL, 0x578D9E904DEC3764ULL, 
            0x9DC8E9D0F34EDBF8ULL, 0xABC797B77C1DE7D1ULL, 0x53DF1614DA07967AULL, 0x08D0D9E4ACE82DBBULL, 
            0xCE06FBB21C797252ULL, 0x2BA1AB3D450F4A54ULL, 0xD21E62A40CC05ED4ULL, 0x8CE3A2FC45278BC5ULL, 
            0x966AF3BDDD5ABA29ULL, 0x6CE00CF71A4291CCULL, 0x19F616E2C60C5A0DULL, 0xEEA3CA85F078190AULL, 
            0x08C286AA183EEED6ULL, 0x61C2C91BCA4F310DULL, 0xC68DD46C74F3429EULL, 0x19EF6BB02613A744ULL, 
            0xF07C24849433E561ULL, 0xEDC37A683F3A2FE7ULL, 0x843F97172177475AULL, 0x7748AAC11EAA647DULL
        },
        {
            0xF7346B7338F00D0FULL, 0xE565A5A46BEB51AFULL, 0xB1CBCB3103AA9433ULL, 0xE82F4B8E3E55BC3CULL, 
            0x5EDC397FF86885FDULL, 0xB633AD05379A1ABDULL, 0x519C234E4AECEE04ULL, 0x90DF9073E489F2E4ULL, 
            0x835F969E296455D6ULL, 0xADE3EEB59860274EULL, 0x67C128A40AD58005ULL, 0x42FB5BBB45587445ULL, 
            0x2AB54A5D8559E9F7ULL, 0xE73CA536C01AFCBDULL, 0x530B6FC9A273E5CBULL, 0xFC921D9AC2BF3B64ULL, 
            0x78326287F9283EAEULL, 0x6BA394CADA8CB4FEULL, 0xAB38F763BE2E294CULL, 0xB675D234F7D2A014ULL, 
            0xB15F9FAF87E93B61ULL, 0xA031896C5D310BE2ULL, 0x2131316BD1D7D5FDULL, 0xE2AF3647AB3CC141ULL, 
            0x66293C6DB203CF89ULL, 0xDE23DAF599C9201FULL, 0x9504C748A43A11E2ULL, 0xF6E4D0ECDB3E1A3AULL, 
            0x938A91ABCBD8139AULL, 0xF2DBBB42D63544B1ULL, 0xB30A41FD177C5887ULL, 0x3F2A037F2F6268CBULL
        },
        {
            0xFB8FBE07A1C05958ULL, 0x32DF367BAA1F516FULL, 0xCAD189988D1B1815ULL, 0x13B355A399910A50ULL, 
            0xCD7A3E3409443A9CULL, 0x0196E333274DE400ULL, 0x60F4A6D7C901555DULL, 0xB45B07797B667080ULL, 
            0x1FC7B0BEA8D94997ULL, 0x9FC00474AACC91B2ULL, 0x2B90470343C02C04ULL, 0x0EDCBCC7634B9530ULL, 
            0x6B11128413D4692BULL, 0xED7B0C4FD0DAD942ULL, 0xF7BC012DD894C548ULL, 0xA60F79B41117DFD3ULL, 
            0x59DF42EBD9C0D9F1ULL, 0xCC90A29691A05CE0ULL, 0x09F5876425F721D7ULL, 0x766FC99E678C5008ULL, 
            0xBA1A519B1EF1F85DULL, 0xB21A860257B9AE3AULL, 0x001B941E1F136847ULL, 0x31007436D43954ACULL, 
            0x452762271F2A937BULL, 0x4D3939725E34AEC2ULL, 0x6FEB82ACE2C57C04ULL, 0x881F999522CFD324ULL, 
            0x6CEAADC6FB38416FULL, 0xE979714EAD1BC9B9ULL, 0xC91E09871DBD9150ULL, 0xA2D4D81DBE0EBE28ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseAConstants = {
    0x69A7099425B5F98FULL,
    0xD8E566244066E35EULL,
    0xF951D1AA1654EB04ULL,
    0x69A7099425B5F98FULL,
    0xD8E566244066E35EULL,
    0xF951D1AA1654EB04ULL,
    0x9B955D6A1338A342ULL,
    0x3FA4DC379E210606ULL,
    0xBC,
    0xB3,
    0x55,
    0xD6,
    0xF1,
    0xE5,
    0xB0,
    0x4C
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseBSalts = {
    {
        {
            0xD06B31F2AC49FC79ULL, 0xD7BBFAA58033560DULL, 0xA0C989B7265EDACAULL, 0x4D24D24720C6C591ULL, 
            0x4643B7C99475B1ECULL, 0x6327B3585846E3B1ULL, 0x321E082F1041E766ULL, 0x8F34CECA79FFEF81ULL, 
            0xF7EA67F702492634ULL, 0x3BAD00636DEB94D7ULL, 0x113E6A370FB4AD99ULL, 0x7D63EF49A36865B8ULL, 
            0x94D7CE91355A1F05ULL, 0x7497B80A67D8AD7CULL, 0x2E5BCCEAC108BA9AULL, 0x70DF02FD75462CF9ULL, 
            0x703AF80750089941ULL, 0xC2007253CFB570FFULL, 0x0C39B7B6087A399DULL, 0x3B5301C947D14E7CULL, 
            0x62AC206761B05FBCULL, 0xA9F2ABC2474496E7ULL, 0x13631B8B85B52156ULL, 0xDA5F6524491B7989ULL, 
            0x333835B6B6F0F19DULL, 0x34B8623E424FAFFDULL, 0x35E325B9069B0A0DULL, 0x1763F83BD3184957ULL, 
            0x27504F7A8EEED654ULL, 0xEEC36FEEBC6CAA54ULL, 0xE7552FBFC96A4CF2ULL, 0x5CB3BBEC8F4BECC6ULL
        },
        {
            0x50DF1079354D3978ULL, 0xD160FB2A1EEB9E3FULL, 0x7518DFBAB2BA9B16ULL, 0x919E13A8002CCFC5ULL, 
            0xB5412BDBF9FC0C1DULL, 0xC5BF2A0C8A368792ULL, 0x42DACF2CA5526E2EULL, 0x8634B4163A88C94BULL, 
            0xF2D1E537017743E6ULL, 0x1D1D8E5307DF1D30ULL, 0x7ECD67AB5C4D6568ULL, 0x6C2CF8E791406A41ULL, 
            0xB9D786E647136B96ULL, 0x9CDEAFEC4C203676ULL, 0xBE1C712A8D8C0B3CULL, 0xA4125BFCC22E593DULL, 
            0xAE7CC78676FBB283ULL, 0x5C5D653A688B9DC1ULL, 0x2AE14C15091A942FULL, 0xAAF726BFFEE766A1ULL, 
            0xCA4D8F89F27CE4E7ULL, 0x7A9BC64FB3886131ULL, 0x1D3DB9AE08920D93ULL, 0x6810E0F51F4EF377ULL, 
            0x931F067B01C28837ULL, 0x0710E15F66928317ULL, 0xD2B14894EEB78DF7ULL, 0xFB724024078F74C7ULL, 
            0xDFE32D0FA725A893ULL, 0xBDDF365A185CF13AULL, 0xB9E4A2F9A64E3839ULL, 0x6B5D67969D9234BDULL
        },
        {
            0x09F1B1431AF98295ULL, 0x7D64D4F1AFDC5554ULL, 0xDCD3C332BD46FE17ULL, 0x230AF345646CF7E5ULL, 
            0xD1884858BFA3E289ULL, 0xE5E41D58C7A81D6BULL, 0xDC02B7E078DA820EULL, 0xC076020C2D2F8AD3ULL, 
            0x1DDB38BCA2FF8CB3ULL, 0xB66DF8CEFB504F51ULL, 0x7D602918D941A154ULL, 0x5234175AD80E5E22ULL, 
            0x62E70F1629A914FFULL, 0x60EB89E190B6C64FULL, 0xEA3436E27C2BFB29ULL, 0xE126FD29B56447C5ULL, 
            0x64B433776BD0B8A5ULL, 0xC7D772B337DD85FDULL, 0xC4420F4EF9E5C0BEULL, 0xB676EC9B989CD312ULL, 
            0xEEA5CC0FB825831BULL, 0xB87F95C4F96CBA95ULL, 0x4736D27989092475ULL, 0x05CD7975F050A818ULL, 
            0x16AA1F20C7B19472ULL, 0x17639FD30D30286EULL, 0xDA2285CC30781D42ULL, 0x37A0A3FBE8866152ULL, 
            0x43CD2D8A3F6A06CDULL, 0x2D5A429CCA6FB3DBULL, 0x466EED4353B2B334ULL, 0x9FFB7909F7BCEE25ULL
        },
        {
            0x4111077B370918CCULL, 0x3BCFF6A1825253B1ULL, 0xBC211B9890F6C473ULL, 0xB25D0DA4681C60C6ULL, 
            0x63A87F7C7595E827ULL, 0x0567C96B9896B9BEULL, 0x51E8BBB13264D395ULL, 0x4C19B65C8DD3D7D1ULL, 
            0xFDB1FAC1CFAA3993ULL, 0x4D1167D4962C7639ULL, 0x75AD8D2BB06B8BB5ULL, 0x6DE6BA7FE51301BEULL, 
            0x49FA6C28889AEEF6ULL, 0x360BE69A3B975333ULL, 0x9796767808D1028AULL, 0x15BD00E2AD66A8CFULL, 
            0xDC9FED53AC851305ULL, 0x2EFD25E7C74E7930ULL, 0x998E92E656DF27CAULL, 0xBBAC66DA1689A156ULL, 
            0x76249BA1F2243ECDULL, 0xFD7F14B7BB52BD6EULL, 0x6E195184865B95EAULL, 0x74978DC294D84833ULL, 
            0x873A81FC6C55521FULL, 0x3725EB176C6F038BULL, 0x3FDEC01007002BB9ULL, 0x2147E884DCED27F1ULL, 
            0x0C8A621B8173FD73ULL, 0x52DF7B1C2E2820C3ULL, 0x86F7B97D240E05B3ULL, 0x0916977DCA571D46ULL
        },
        {
            0x89DA626EDDA3043CULL, 0xFCB5A1E7FEBA3824ULL, 0x9490FC5BD2ACC5A9ULL, 0xC9685A1701CB5319ULL, 
            0x0A5496408274431FULL, 0x43CF9A0CCA3FC774ULL, 0xE53E7B3F3B9EB599ULL, 0x7ABD32B997AC3DD0ULL, 
            0xC4837D28C1194DE2ULL, 0xCA602A5DF41452B4ULL, 0x33CB4227C27060F3ULL, 0x3E4B98EDBC2B2812ULL, 
            0xC54FB61301476975ULL, 0x165C9346435F98AFULL, 0xA3A76C554F7FC7DEULL, 0xBBD1EE2DBDAFB862ULL, 
            0x6AA006205852FFF9ULL, 0xC9171ACA2311B69AULL, 0x624EA5D1F252C12AULL, 0xD89D8B23A35AE0CFULL, 
            0xF27EF1E79AE87420ULL, 0x1EAFFEF1B607AD3BULL, 0xEC1051DEA029C5A9ULL, 0x08D505D383DF9912ULL, 
            0x0AA9D3CABEAE7663ULL, 0x10BBD8569BF8E369ULL, 0xDCB7EA2CC8ED2041ULL, 0xDBF37AAFE1CD4B7BULL, 
            0x1C3384233BF848E0ULL, 0x0F4800CE065FD3D3ULL, 0x7486FA9BCDC264A5ULL, 0x6EC0E338A57BFF50ULL
        },
        {
            0x66964E67155B2136ULL, 0x0403C75AB97A96BBULL, 0x6BF7CAFBF188294EULL, 0xC647A28939046D27ULL, 
            0x59EC34BEE1E7DDD0ULL, 0x1089F4F61E92A4F9ULL, 0x7A8BA828357DA287ULL, 0x32C1EE1579915E61ULL, 
            0x22454CB3B1D831AEULL, 0x8BC7A8EDD71054B5ULL, 0xD519D06A0E9C8E97ULL, 0x913EC94B352DCB8EULL, 
            0xFC8AF2F9EDA6C904ULL, 0xE07767A88B95A531ULL, 0x880BA6F5DFEB7E9EULL, 0x00E714C0ECF64295ULL, 
            0x498132B4ADE3D62AULL, 0x7017332F0955D498ULL, 0x6495BF1C62F70195ULL, 0xE1E8C6C977A3BF19ULL, 
            0x9842712E6514766FULL, 0xC809D4E637944956ULL, 0xD30973C2E203375EULL, 0x46BD85AF8C53E195ULL, 
            0xB1AE1938E123D8B3ULL, 0x186A3967E15054FFULL, 0xD515985C4A8695BBULL, 0xB165A59176731B89ULL, 
            0xDD681691B9D98BF9ULL, 0xB556A7C73F3AFE4CULL, 0xC2FBDD3E47847D99ULL, 0x9CBAF5813D24F6D2ULL
        }
    },
    {
        {
            0x83FB45A381F31FCDULL, 0x1DE097E7EFFE2167ULL, 0xE6A8A6C57A38C979ULL, 0x9EE3701AE80A0BD4ULL, 
            0x77A6079C61D141E3ULL, 0x0F60D511EF32363AULL, 0xC42432BFD5490E4EULL, 0x2CB777EB1E9CACE8ULL, 
            0xC4BB4FC1C955D481ULL, 0x8AE0EAF754F11893ULL, 0xE3305ACBEEE4696EULL, 0x28477BA654D15CACULL, 
            0xB6CC52FDF341800EULL, 0x3447CBADC6A75997ULL, 0xD196F9F43BF2CF10ULL, 0xDB8DCF75A574D585ULL, 
            0x8C92E2E8CF69C0BDULL, 0x70D60AA54A3B57C3ULL, 0xEA3E639C0F5880B6ULL, 0xD004186E26A5787FULL, 
            0x786A9C4AE9B67A65ULL, 0x3DAD65C9060B596CULL, 0x9DBAB8CAEFC496BFULL, 0xE3946CC3C2B17A99ULL, 
            0x95DCC686C139C403ULL, 0xDEBB190DCD61C55FULL, 0x8BF71EF46243E343ULL, 0x864350CB4F3BF41FULL, 
            0x6C7361D61B6506D8ULL, 0xD957083317124CF9ULL, 0xCA50FA27E6344250ULL, 0x0D40F4CD8752C3E9ULL
        },
        {
            0x3A2E280D2A0AE803ULL, 0xDC39B1A5DDAAE879ULL, 0x4FE1C1D8D8299EF7ULL, 0x88E3C96C13F496CDULL, 
            0x0B9ADB43BE272683ULL, 0x3F564FD3997BED7BULL, 0xD055F3B6070E3C93ULL, 0x43A893973CEE7BAEULL, 
            0xF3C28606596D7BD0ULL, 0x5E8DFD7D30B9A831ULL, 0x72388F23B0D28B84ULL, 0x96BE20184BE2CBEDULL, 
            0x1EB6D97D8D1FC4B9ULL, 0xF1287C6071952D4FULL, 0xEEF0C97A6A5007AAULL, 0xF3E2301EB78A4630ULL, 
            0x842BA3AB299A7F1BULL, 0xD2B4685F1971720EULL, 0x7E92876F0535EBC2ULL, 0x4339AB75410DA088ULL, 
            0xE05A7A606AE0672EULL, 0x966D9D62AE1A0D67ULL, 0xFF7F79D7D805C62AULL, 0xFED517EDDD054CCBULL, 
            0xF7D4AB09D242162AULL, 0x402914E8B31CD7A5ULL, 0x25FEE09E53E174C4ULL, 0xDAD909C5899E4AC8ULL, 
            0x984AE69DF9D8AE8BULL, 0xEA90A0A3A2C1E20DULL, 0xB8648E88272146FCULL, 0x1C7D7788B7487B6BULL
        },
        {
            0x0897FB931545F6DFULL, 0xD83ACB92BD144B56ULL, 0xB4666699861AF01EULL, 0xE8874ADBE3802766ULL, 
            0x6B2D85FF26450AA7ULL, 0x2A42CFCCB71A5316ULL, 0xD2E262FC34D25C6CULL, 0xB9858C63D0AFE901ULL, 
            0x447478D95BE151C7ULL, 0xA30EA31FF09DC654ULL, 0x5347DBA3C4667C18ULL, 0x0107EDBDA23C49FFULL, 
            0x24AEA770C8BBF2B6ULL, 0x7FCE70C552658AFEULL, 0x5043A5268E7AF0F9ULL, 0x45237327A78B19D2ULL, 
            0x9D73F6F9D33883AAULL, 0xA141A9FE31376433ULL, 0x62B0BE5D7DB9C05AULL, 0x77F4518C3D1FBEDDULL, 
            0xEAC00EF97E79022DULL, 0x69DF7EF82E5709E6ULL, 0x42096C1EC0FBA7E0ULL, 0x137E20EE0B527DE3ULL, 
            0xC92E54D9EEFF595BULL, 0x5A9E841FED5D7910ULL, 0x9CD419ED2389F13FULL, 0x740BD286C04583B8ULL, 
            0x5449BDBE08D131EAULL, 0xDDF9B7FB6CDE88A6ULL, 0x583C5D9CE13214C6ULL, 0xC9399D6986AFE9C7ULL
        },
        {
            0xF1ABBFE61E5FAFA1ULL, 0xFB31D398E8DBA33DULL, 0x9360BDBD8E8B56AFULL, 0x33E04E11DF8ACB8FULL, 
            0x508FA072D6C4D59FULL, 0x6E6C20006E879DF8ULL, 0xAF11449E5DDC5467ULL, 0xA3F2B08B8EA25074ULL, 
            0x91B4A420EFA1105DULL, 0x4730C9B9BD5B3148ULL, 0xB465C1A78BDA56ECULL, 0xD05F95FD94BC6610ULL, 
            0x4A73CA220A01316DULL, 0x5623C7F5B06430A4ULL, 0x9C7D3F6A99DA43B1ULL, 0x9D8025CFDBA8A56AULL, 
            0xDB46510DA28454DEULL, 0xB2CCAD83DC0015AFULL, 0x25720217D8547D20ULL, 0x9948D5DF5C60D980ULL, 
            0x30D2A7970BBF8D88ULL, 0xC36A7AAFB9AFBECCULL, 0xE94EF3C59FCB307CULL, 0x8110E523425C26F1ULL, 
            0x6D8B2F20C9E9D572ULL, 0x92093E2045228721ULL, 0x4AB0AA2906D3B849ULL, 0x9D85E00E2296A256ULL, 
            0xFE478C42CB1F8BE0ULL, 0x80DF6F4B6D3545F1ULL, 0x22200321B928D8BDULL, 0x5F30B6119CEC52E7ULL
        },
        {
            0x12FEF0E608199EE2ULL, 0xDE8EABC0037CDCBDULL, 0xCEA670BF2CEAC0B5ULL, 0x48391C0ABC761427ULL, 
            0xFC1DECEC683A02A0ULL, 0xF31726EBA4E8F8F4ULL, 0x51BA2699649A0049ULL, 0xF84C1440AC726441ULL, 
            0xA28D9F6BE7161746ULL, 0x9A2A17E37CB9C729ULL, 0xBA0BDB71FB1EF320ULL, 0x1D5EE9177045FC4EULL, 
            0x2BECFD3C4A5E7BBCULL, 0x73C1D71218FD9AB3ULL, 0x7E0F7DEDEA99B4C1ULL, 0x973109BDAB612B0EULL, 
            0xB5B86F8FAC36669AULL, 0x1BE5E1E3159AEA41ULL, 0x6FBEF7F9A092B880ULL, 0x6FBB65D9C779B515ULL, 
            0xAF7A1F6E595D7B2CULL, 0x2523AC6E3A2B8081ULL, 0x7C0C096C2B3302CEULL, 0xBD34758F1EE0500AULL, 
            0x447E06F85B43D455ULL, 0x7D88E364B32477A2ULL, 0x46F0C60998F3E72AULL, 0x68051291C057DA02ULL, 
            0x26ACC11E358E2700ULL, 0x28A82EEB47C354FCULL, 0x3DB84ACB12162F3BULL, 0xEECFA3EAEC18C2A1ULL
        },
        {
            0x6B8C33F3DD93228CULL, 0xA7625B3BC44814F8ULL, 0x64F3ED5ADAB7E5CCULL, 0xC06CCA14A9592B29ULL, 
            0x15F3774C8BD24572ULL, 0xEFB2061A4A23B741ULL, 0x14C67FE1F7EE0F2AULL, 0x64A02A3507F1EA89ULL, 
            0x33CFF68986634318ULL, 0xDFB4B4C5EED06FB8ULL, 0x363A6B6720770167ULL, 0x6A9C238040E5E4BFULL, 
            0x9B83440874FE9108ULL, 0x42EAC29F53F768C1ULL, 0xC519C5D01442D78CULL, 0x25E5F2AD7ED259A6ULL, 
            0x3423B0B124188D53ULL, 0x9EF9154B38E32C55ULL, 0x11A0489518B8F5E7ULL, 0x256006413A509508ULL, 
            0xB9BEA6B973D46E98ULL, 0x859470D0C86D596AULL, 0xB95BB89659CF88A9ULL, 0xABB76D2DBA79781EULL, 
            0x21C75A9FBA0D83CDULL, 0xDC13532D94E5398DULL, 0xB0EE5183A8579E89ULL, 0x61C4A1214364F059ULL, 
            0x8052B0126E60D7DEULL, 0xA63BF4317113D583ULL, 0x135A855AFF3060FDULL, 0xB0879029160CF244ULL
        }
    },
    {
        {
            0x3C86421D489B933AULL, 0x7377A9689BB3070FULL, 0x6FFBAA0F9AED2477ULL, 0xBF08A84D9F527623ULL, 
            0x8E0B7D2D23F53E3FULL, 0x3C38D8447878DC2CULL, 0xB068EFE1B268C19FULL, 0x8FF75E27DA79BD69ULL, 
            0x93962B9F007441D2ULL, 0x287735C0ACEB063BULL, 0x8CB750E94453DBE3ULL, 0x4D2C1F0B0B3DA68FULL, 
            0x61BDBC07EA042B09ULL, 0x55A089D79F9F9DCBULL, 0x4F66F4EDB0C98420ULL, 0xA133085E429E623EULL, 
            0xF93D287559B18FB8ULL, 0x667BBAB34A1F4965ULL, 0x111C594421B7D2BEULL, 0x174917DB1CE54A5FULL, 
            0xD03118CABEC63ACFULL, 0x53D4FE54F131F5B8ULL, 0x6EDAFDA77931CAECULL, 0x254F31AD5A94F288ULL, 
            0xCDA2F2277E718094ULL, 0x12A3DB3C0ACD1685ULL, 0xDDC07244D70A12DFULL, 0x0E19579C34BCB37BULL, 
            0x65A4177B2B19CE1FULL, 0x51D286B9BCBED7CAULL, 0x91553C4EDC1D9A64ULL, 0x60DA8AB07F3EF16EULL
        },
        {
            0x7C3B0873C80AC017ULL, 0x5B34CAA00B526885ULL, 0x44BAE0F91300C6E7ULL, 0xF7DE19C1DEF491D9ULL, 
            0x687024399A27C31CULL, 0x17C4C35445362738ULL, 0x9A6CA56F979F39C4ULL, 0x358685CA64779806ULL, 
            0x3A51035FF6F314B4ULL, 0xB3667ECEDF250272ULL, 0x6185F2FAA789DAC8ULL, 0x921C21874D3A4CD7ULL, 
            0xC58C1BB0F63D0CC8ULL, 0xEA8D5E1CA6D0E3A2ULL, 0xEEA8FCFFEE6CAA3AULL, 0xA082D79047098A27ULL, 
            0x5A37114AAEC05EC9ULL, 0xFD1427EA2633A87FULL, 0x6C0646D324BF7EF7ULL, 0xA56C9284A0D09901ULL, 
            0x996EC577DD600550ULL, 0x5B033B727FD57762ULL, 0x35F50C8DF2BB8DD9ULL, 0xBFF9F968BF906EF8ULL, 
            0x722E67992BCF7438ULL, 0x353EA083A77A02B3ULL, 0xBAD0B403206698BFULL, 0x6E48271A0B31E706ULL, 
            0x4FFBD4F0350505CCULL, 0x8DE99024DD6636B8ULL, 0xB2EF995FFEE4AD9BULL, 0xA00976D0E05B892CULL
        },
        {
            0xA2E2F483AD063ED3ULL, 0x9F9BCB143CAA3C20ULL, 0x76FF42C60AB3E58EULL, 0x394CA85C7FDE4CC5ULL, 
            0xA14E5FD52E9CA7A7ULL, 0x7F14AA9448DDD9A1ULL, 0xD865E21B6DCF084CULL, 0x9D718A8D9F9FA7FDULL, 
            0xA7083BD18D9E63F7ULL, 0x45FD5D1B7067A661ULL, 0x5C65B07CECDD7FAAULL, 0xD5D647BA4922A801ULL, 
            0xCB7FFC50BFEA5893ULL, 0xFBC96CE672EC2886ULL, 0xB13269CB20573907ULL, 0x599EF4D88C9D52D2ULL, 
            0x78128DAAA4D26D45ULL, 0xBD37114035A3435FULL, 0xF94CA44A5EFACA42ULL, 0x712484644ED8AB44ULL, 
            0x61DB48CF3F909412ULL, 0x0C92E6D30827BDAAULL, 0xF9180309B6938BD2ULL, 0x00E34CC02595B292ULL, 
            0x364C69D9F3B6C86FULL, 0xAF5C006687554BFDULL, 0x10523C817156920EULL, 0xCFC3A97AF1B143B3ULL, 
            0xA534FB4D4F37DED9ULL, 0x59C81060ECB83A43ULL, 0x96DB17D1770E4B9DULL, 0xB35157D8BD757F58ULL
        },
        {
            0x06DD9736341FA2CFULL, 0xF43364B0107C95BAULL, 0x4E3C4BA7027A1C34ULL, 0x782E473B9857EEBBULL, 
            0x9B876832257B448AULL, 0x58A7D4AAE58838EBULL, 0x70A5A02CFA432F09ULL, 0xECE61D47680155BBULL, 
            0xBBBFC6E7BD7CA09EULL, 0x42080257A9322329ULL, 0x29004D13730801BFULL, 0xEEF3DBE61E2F6DA0ULL, 
            0x4C4B3C70920A3291ULL, 0xCA4B9DC050F9280CULL, 0x0C2A0FCAB580582EULL, 0xD4A0721CBDA76393ULL, 
            0xC322C1185ADCAEB3ULL, 0xACC973FB47C069FBULL, 0x7153377664D8A237ULL, 0xBCA50AFF4C340497ULL, 
            0x07C23AE3951ADD56ULL, 0x455159C06165A423ULL, 0x7C780B5E2ECAB69AULL, 0xCDDAF6BE070CC3F1ULL, 
            0xFD669DFB1056E447ULL, 0x87335BE9D7F79D90ULL, 0x36E7EE74995CA213ULL, 0xAD47D8B7ACE92929ULL, 
            0xDCE126B33EA03E27ULL, 0xEEED4F20BD2872ACULL, 0xEF47B4C52C7A7D72ULL, 0xFE6C6C841866F93FULL
        },
        {
            0x7F15F54EE1E580C3ULL, 0x806E9C8D8D2B6009ULL, 0x319F076D9A037015ULL, 0xAA0E6E7D95AFEF68ULL, 
            0x2B2C8E751533959AULL, 0xCAAA8784D6493141ULL, 0x02A6FDEBD4CA5F51ULL, 0xD623F0AE861E9EE6ULL, 
            0x6350486B6B45492AULL, 0xA06BF42D3B3A7181ULL, 0x11FD201488FC7676ULL, 0x3391566F4E1A8B5FULL, 
            0x786D9C3D1E17181DULL, 0xCA074D2871FA09A1ULL, 0x180CC5A221F0A522ULL, 0x78C652234CEB8148ULL, 
            0xDD888D5F95E8343BULL, 0xB0D00F9B11F4A4D8ULL, 0xE13DA7058B21609BULL, 0xA76FE3CA1E53687BULL, 
            0x75E4520CD36CBFD9ULL, 0x8B1BD7F2CD0A1D61ULL, 0x63FCFBFC298D955DULL, 0x18708FAA14F5DEA3ULL, 
            0x1F193380CA6B1E79ULL, 0xB539F33E68145C69ULL, 0xB7EAE98CBB7F5BC2ULL, 0x1CF4FBFDB3080771ULL, 
            0x8B0866BD8D70B97BULL, 0x5EB909F201123B59ULL, 0x35B90628BA2DA7ADULL, 0x5E77F3693CF893B6ULL
        },
        {
            0x9611CDC11B158CBCULL, 0x4AB488ACF0070E8BULL, 0x1686CCA115BAC219ULL, 0x8A48988CE7C49573ULL, 
            0x41EC40A405827367ULL, 0x0D99E4D09A370D6BULL, 0x76F81181AB15A4B0ULL, 0xFD3C88D2508AA7C3ULL, 
            0x3C1E949AB17228D9ULL, 0x907C2EBE38435867ULL, 0x671A3763B34D17AFULL, 0x8B49E6361A16B402ULL, 
            0x79A7635CAE3E7653ULL, 0x377620CA0676FB8FULL, 0x2F5E7E4FFA5E1313ULL, 0x66164269F7BF63F2ULL, 
            0x73C5F7C48EE5168CULL, 0xDB9A0C027DF2D0D8ULL, 0xF48FFE7D9EE7DC61ULL, 0x722237EB12688AD3ULL, 
            0xA15481BD91DD8C0CULL, 0xE7408791608BEE4AULL, 0xBC422F6D14620E75ULL, 0xCC8ED2E618E723FDULL, 
            0x8D205679B06A304AULL, 0x9266DEC9D62874B4ULL, 0x042ECFC8B02CA996ULL, 0x699856944AAD6E12ULL, 
            0x001755C7B742188DULL, 0x5726161C88787014ULL, 0x7B60045C35990BD9ULL, 0x10A1851F02711A4FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseBConstants = {
    0x61F41FDB06046A88ULL,
    0x0E90CAEEAC072224ULL,
    0xD350A71174FDCD57ULL,
    0x61F41FDB06046A88ULL,
    0x0E90CAEEAC072224ULL,
    0xD350A71174FDCD57ULL,
    0xA8EFB5D6663B7DE0ULL,
    0xE12EDA62E7AC0D21ULL,
    0x53,
    0x89,
    0x84,
    0x09,
    0x50,
    0x93,
    0x1B,
    0x8D
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseCSalts = {
    {
        {
            0x2DF9AB655BBCA61FULL, 0x2688C2437C1DA32DULL, 0x48F534129570B8FBULL, 0x59435E41EB99A799ULL, 
            0xE23A30B691300341ULL, 0xEB41244ABD0C6A6BULL, 0x392F77EA407FAD06ULL, 0xB40E42D2B8D990BEULL, 
            0xDC3179472E43A243ULL, 0xBA418E84BF73C2BCULL, 0xDCE7EF632FD03460ULL, 0xCAA6734CBFC4BB7CULL, 
            0xF82498C17BC1D245ULL, 0x4BD105EDAD2F1AEDULL, 0x4B37C1A9E6CDA6D9ULL, 0xBF6D689B421DF243ULL, 
            0x0F23774C306A3188ULL, 0x9D418E778E36B943ULL, 0x321B30714C8E16B3ULL, 0xA7CB4FA109B023D6ULL, 
            0xB6D90A4A83E74193ULL, 0xBC3116EB67912C86ULL, 0x722032F56AE62587ULL, 0x5237D8DA9B49A105ULL, 
            0x2CD87000553B30DAULL, 0x49353D31AACABD0AULL, 0xD83F84C7C5DAE36BULL, 0xE8915CF842D0CCBCULL, 
            0xEC8072C52AC36718ULL, 0x1508E0C74A6C14AFULL, 0xA1D65FA22314BB15ULL, 0xDCFF3434F5569925ULL
        },
        {
            0x71595A4FF9F896F9ULL, 0x899EEFC616641E49ULL, 0x1A051D3C1903E181ULL, 0x5CA6F01164A61DA6ULL, 
            0xE17FDEC32560D26EULL, 0x9934296EBBEDED14ULL, 0x8FEF5047D3F20624ULL, 0x2E8018DCCAC057BEULL, 
            0xE75A97082A8191B0ULL, 0xEC49E1BEE582F69EULL, 0xC4608B6688EAEFC6ULL, 0x329F05DAA9B5AF15ULL, 
            0x295BA9BA0EC8BCEFULL, 0xA317E1136D6545A3ULL, 0x452DB85AEA1D543AULL, 0x1623AF1FFAECB2FCULL, 
            0x8342A91DD0622187ULL, 0xFBFFFAF84AC2853AULL, 0xBCD04E1D67E5B8D5ULL, 0xC71BBC1FA7E42479ULL, 
            0x0C70054CFD70D89EULL, 0xC992CF6DEAA9CD50ULL, 0x762B1972C9581AC6ULL, 0x8A36350B137B7D94ULL, 
            0xED283E6296C8A5BAULL, 0xABE6C2ADB1C77D0FULL, 0xC9A20C86A998823BULL, 0x062EEEA48A57AC90ULL, 
            0xEAF44982E8D02E65ULL, 0x80A819ECF2D978A4ULL, 0x027B4D6E132F2971ULL, 0xE4DDAE3317A301B4ULL
        },
        {
            0x2BBE7B8F0D1BEA18ULL, 0x495537D586CEC92DULL, 0xF5FEF4FD04E53B5AULL, 0xEEFD315FF28117DDULL, 
            0x7BA31D4849DF9084ULL, 0xB4E274EFA07F6E6AULL, 0x70C641576881553BULL, 0x9F5FB8CAD01CFBF8ULL, 
            0x66DF760B45B762ECULL, 0x1A2F56AF2C0FE609ULL, 0x8CA37D23D01A3B6EULL, 0x869E3D66907CD506ULL, 
            0x7C0A2E39606C8C32ULL, 0xFE76FF1100746751ULL, 0x2DEA1AD13F3DF349ULL, 0xB48889F0CB069EB3ULL, 
            0x36F2EFB932D01091ULL, 0x76BC8CC845CD7423ULL, 0xE3891F3F0B89495EULL, 0x8A9EB9E28AA5E857ULL, 
            0x0C2CED9D4F1DE3CEULL, 0xABE0C85E4EE38A44ULL, 0x3952C68091F914ACULL, 0xC8D2B84D49641509ULL, 
            0x53FC9AE28DE4FE8CULL, 0x22969DB40DEFD030ULL, 0xB6F2A78A163EA18CULL, 0xC3BDD12C0D43D88AULL, 
            0x0DD6EB8300665712ULL, 0xFBECF6D14579AFE4ULL, 0x4A79080D42284CCDULL, 0xB6B75DEFA77D5116ULL
        },
        {
            0x5CE40AD19DF24BF9ULL, 0x637FB6A14D4908AFULL, 0xB736520A56DA6768ULL, 0x311BB67A65A8EFA3ULL, 
            0x73A4185A75A5FFBDULL, 0x59542626B67F9544ULL, 0xA0220C6B0C5AE54EULL, 0x82D1A2B95F87A536ULL, 
            0xA69D2A64F9E0D936ULL, 0x4CA4FB636C25F5D6ULL, 0xE1D5395D7A4DB5C5ULL, 0x91E9956D7B531FA7ULL, 
            0xEB4423E724DCBC29ULL, 0x3C093F01D565F6CFULL, 0xBDE6CAB62A34713DULL, 0x7ADEE1E6AFC1ABCCULL, 
            0x5DE820DCED8C7BE0ULL, 0xD584F64EC4EFD1F8ULL, 0x3E407A68F1F6A79AULL, 0xA878496D2B52C023ULL, 
            0x3D24330CB654BCFEULL, 0x2369FADEA5AAFA6AULL, 0xDCC1CDAD26B711BAULL, 0xFE5FA62D64E04268ULL, 
            0x227D290CF77335A2ULL, 0x0AAD15D0FCD9E7F6ULL, 0x87BB8996015DF832ULL, 0xFD8CB2F9717F93D5ULL, 
            0xFAA16F89FB6B6D1EULL, 0xCB50255758228B8FULL, 0xCC17A4026ED96FD0ULL, 0x06CB0781C278E0CDULL
        },
        {
            0xBEFCCA385F1150C9ULL, 0xB4FF22DC8A61CB1DULL, 0xBAD0336FD049CEEBULL, 0x6DFD37108CF90747ULL, 
            0x914BD792B0B275E4ULL, 0xED7FB7E4AD0EA9B6ULL, 0x55F3C79EA6F603E9ULL, 0x14AC63AAE2615998ULL, 
            0x383DAC901A759A82ULL, 0x62A74E5B89BB05D2ULL, 0xE8BA25A8C602DEF3ULL, 0x5257FA1A27258EA5ULL, 
            0x7EE2165C1BAF0C3EULL, 0x9A6DD00947DA55C0ULL, 0x6FF3FF92605002B7ULL, 0x98AF7A509C37663AULL, 
            0xD345BE4FE925920DULL, 0xF451FF141B461D1AULL, 0xD0652F1BD767B781ULL, 0xBBEEFF558ED40576ULL, 
            0x94E1DE94DC7B7316ULL, 0x3C7D4422CF984E4DULL, 0x308BDD24B4D4086FULL, 0x4990DFE5971AD282ULL, 
            0x3A90E97DAEA9609AULL, 0x5A12BE928A107E20ULL, 0xF3E7353E53FC0263ULL, 0x4B5D4F2CA3B0FD09ULL, 
            0x0D05CA733FA37421ULL, 0xCE0FD9FF0931DBF1ULL, 0x335AB6F3D9FC0911ULL, 0xE1B562ACAC1C3072ULL
        },
        {
            0x14B60BFF2E9A1163ULL, 0xCE7A2157E11A0BB8ULL, 0x8E58B5419107691FULL, 0xA5F35D9AB8B82D19ULL, 
            0x602E553BCB31D33EULL, 0xEC1B257658F1A73BULL, 0xB00BFEF2FCCDDD71ULL, 0xC56EDD9FF06251BFULL, 
            0x1E18AA708D181B02ULL, 0x5868B46F982C6655ULL, 0xABE31C2305148959ULL, 0x3A6F83DCC7E5D052ULL, 
            0xEC12B1A5268D53A3ULL, 0x1A423B2C21B65484ULL, 0x9DC1A75238650F37ULL, 0x1D6F7141FD2E4AA4ULL, 
            0xBAC4C24C752929BAULL, 0x22BC0C778FA849BFULL, 0xF93B186D5B821BD2ULL, 0xE63AF8D7BBF0136CULL, 
            0x35FCD4CE13818F7AULL, 0xCF3B4EACCB9804E3ULL, 0x7B803F473A18A1F1ULL, 0xAE86B23B02F61181ULL, 
            0xCB40642E7F32496EULL, 0xB8CFE4B6CBF10B1FULL, 0xBD3E9A017991EC88ULL, 0x6127F81CE74F9292ULL, 
            0xFA5F023CABD0D6E9ULL, 0x87F72CCE84393026ULL, 0x450C734206A53221ULL, 0xED28FC06F7F3B339ULL
        }
    },
    {
        {
            0x30360FFEDBE64EBAULL, 0x9A944AA704ECD854ULL, 0x59E6357B1661E90DULL, 0xA7125B4D3180CF4FULL, 
            0x46047A1A4DFA1E44ULL, 0x719AB941508D23A8ULL, 0x55E24425F166838FULL, 0xABFF73CDDB0CD057ULL, 
            0xA007B696AACB37BAULL, 0x7E3E27E803CFC688ULL, 0xA9BCE19F0C2AEE81ULL, 0x3FF7F2F18435EA79ULL, 
            0x615D580254D95773ULL, 0x4C71B972E81A7F9EULL, 0xCA19B5E175733AFFULL, 0x1272DBEEBC539862ULL, 
            0xF203E1AD85A94BF2ULL, 0x228BF88E24FB3A46ULL, 0x7E9CD7D9690ADBE7ULL, 0x560414A5EDEA2470ULL, 
            0x7E469001F203A0DAULL, 0xC448C3D6783FBF71ULL, 0xD5400F62022EB929ULL, 0xCC32F853262CDF40ULL, 
            0x42E063153D8A2A9AULL, 0xEAA9A344647C742CULL, 0x9DA8A5DAEA9FDF4CULL, 0xF339435B750234ABULL, 
            0xD0F881F310A001E2ULL, 0x6A9B96B6524105D9ULL, 0xF0A120E00AAD0336ULL, 0xEE68A77892FA9773ULL
        },
        {
            0x59CE8E0F9249D47BULL, 0xB90C1714963B27DBULL, 0x5314191F97ABE709ULL, 0x32A4BDD55CA896D5ULL, 
            0xA0592F03D6DC803AULL, 0xAF79819E9F10FDC3ULL, 0x95177DFB9BB18BF1ULL, 0xFC9170E6F00A8511ULL, 
            0x26B0931E3C90EB9FULL, 0x124AF3C9A53D6E32ULL, 0x4B3B875A28446A14ULL, 0x2AFC51590F12AE14ULL, 
            0x84766D0BA4D8D279ULL, 0x6F5E9EF1CC63C86DULL, 0xE4E0A3DBA69D1242ULL, 0xC79B67744445D299ULL, 
            0xEADE588D203C83F9ULL, 0x841A588A24B90519ULL, 0xF1A10D9F07751DCDULL, 0x5779A88F50849390ULL, 
            0x4E91F6690E5674DAULL, 0x2229D9EBA549F32EULL, 0x0453816166D09864ULL, 0xEEDE79BFC3003260ULL, 
            0x1A5BF22E439621BDULL, 0x4B5EE9525AA3750FULL, 0x2203575E72179B5CULL, 0x6639A5B5C3E0AF62ULL, 
            0xD56F3C2F3111C51AULL, 0xE140924D719605A6ULL, 0x038693AE28F3CF8EULL, 0xBB634A791034C2FAULL
        },
        {
            0xFAA6AED5D333DC28ULL, 0x4F32363C37C88F81ULL, 0x6D128BDC895AFEFEULL, 0xA4CCFD1F1DAE7972ULL, 
            0x0DA1160FB42DE641ULL, 0x9F253AA38A3F86AAULL, 0x3B13C7E92155E327ULL, 0x790FA45B5499C658ULL, 
            0xFBBDC9033822BA33ULL, 0x8DC9C599FC220A41ULL, 0x85E25006A19D9F38ULL, 0x7B0E4C073A4027A8ULL, 
            0x1ABB58B6CA48F097ULL, 0xDB0DA9B4A6DFE3BDULL, 0x814C1F8040CC8B6CULL, 0x5C75E81198A78A08ULL, 
            0xF9EA7D1EB9F11F9FULL, 0x0E474DEED9F090C5ULL, 0xC75260C921EF540EULL, 0x6E32EFE9DDDE190DULL, 
            0x500A26FBF4266A55ULL, 0xEB5039105EA222B1ULL, 0x1E90251ABF11F3A4ULL, 0x7615F736B1D7A537ULL, 
            0x8B7A68F278E3A34BULL, 0x3E6394B2C56D69BDULL, 0xE7A687CF2EB2ADF2ULL, 0x23C10973546A6F0AULL, 
            0x06753CFE7AE0A880ULL, 0x14308F4501433A32ULL, 0x7F9F450F17A719FBULL, 0x8D04281BC60CECA4ULL
        },
        {
            0xC14854DE9081695EULL, 0xEB0434DF99E1F436ULL, 0x575BB2D98002742EULL, 0x9F3B266D23F37F2EULL, 
            0x9255A18486177FBFULL, 0x083632038C63053EULL, 0xDEAD5F8EABC50538ULL, 0xCD87B3859CDCDB35ULL, 
            0x9EC244AAAC0C14F5ULL, 0xA843E3D55155E812ULL, 0x1334B072E47411E2ULL, 0x3DE36AA74DB003ECULL, 
            0x2BB28851AFE02EDCULL, 0x1D37D9B6646DBB3FULL, 0x0AC4FF24C98B24F3ULL, 0x77A19492B5156990ULL, 
            0xED39D798709DE64DULL, 0xEABF6F743FD2382CULL, 0x47612BC83A328D92ULL, 0xEB224B58759F5757ULL, 
            0x667C666430DC339CULL, 0x378D06EC8BD94EA4ULL, 0xA1ED6C1B03493048ULL, 0xF0EE78256E0A591CULL, 
            0x5340145B9D7535F6ULL, 0xC30A1E24F73C1A14ULL, 0xA8EA13E8D0C8EE9FULL, 0xB2F739BEE5CD2949ULL, 
            0x3A9E907CBA8EDF78ULL, 0x43E1EB64A5694C3AULL, 0x83D972A3BED5C890ULL, 0xF64B54FADB6EFF8EULL
        },
        {
            0xF7A33CD8F827A17FULL, 0x069262DCED90072FULL, 0xBDC0DB26623AEC61ULL, 0xF64CA4D5ECAB94E7ULL, 
            0x77CB49211CED5FDEULL, 0x2E93BCF4FD227325ULL, 0xFC3DBC15F6045FC0ULL, 0x9CAB10D0823061A8ULL, 
            0xD3CC23F2E1FF3165ULL, 0x0F13B0CF2D2B9AADULL, 0x5DC3791180A7D4ABULL, 0x1401F2D6FD839076ULL, 
            0xDEDB6FFB8A06CA02ULL, 0x5B60CDA04EA98076ULL, 0x3B3D4E9A1CCC5C93ULL, 0x7DE7B82C4B31325AULL, 
            0xBC3459726E2A60B5ULL, 0x58E5AE42E05E5A29ULL, 0xDC24F5626D3578D8ULL, 0x0DDBA4AD2526D049ULL, 
            0x7B30FEE631EE1251ULL, 0xA59ECB83FE0DD6F0ULL, 0xDF9A8214ADDE08E1ULL, 0x47A2DC84985CB6A5ULL, 
            0x2BCB028CA8BB8374ULL, 0xC768B7AC02641377ULL, 0x7707C45E32E18ECEULL, 0x61A957FE2054B3E9ULL, 
            0x9ED1C1A68F1B1737ULL, 0xE3405CAC3B7A06D5ULL, 0xB5ECDC22CD63DFB0ULL, 0xE157A352CB61B6E6ULL
        },
        {
            0xBB181AB9025047BAULL, 0x22F0828D79378556ULL, 0x46481594E133E714ULL, 0x9B98C905882668BEULL, 
            0xA9CC35CC64DC4BB9ULL, 0xAD97FE740F9C07EDULL, 0xB37F2C5862A88F0FULL, 0xEF6582916478A42EULL, 
            0x9C1B1828633381E1ULL, 0xFA41EFFC410EA33DULL, 0xEAC8371549937649ULL, 0x2014308F51449C1BULL, 
            0xA86338BD6A63A5CFULL, 0xE4435C701612554BULL, 0xBF3AD8F46D933BD6ULL, 0x6ADA01C85F45572DULL, 
            0xE0442ED1D99C31DAULL, 0xA7ADB4BC62BED4E1ULL, 0x932C62EC8767DB14ULL, 0xBB476A380A766CACULL, 
            0x4C4919180E3F15C0ULL, 0x1CC557D47663A271ULL, 0x4538DE38C512F1BEULL, 0x410FBF7092EB01ACULL, 
            0xBF6395699B4BCED5ULL, 0x1DAFD145DAA8DD0EULL, 0xA8099BBAE09B786CULL, 0xC38B2DB13E385971ULL, 
            0xD7EAEDFAA6B27BECULL, 0x20CDA6DAC833A6CFULL, 0x252DA8CF5E928FB6ULL, 0x7500EFEFF2FC95BBULL
        }
    },
    {
        {
            0x1F00CC85D9416189ULL, 0x63361858C7F68830ULL, 0xB7056353E56AD453ULL, 0x5E261CB701C249C5ULL, 
            0x06CC9D26570C7CBFULL, 0xA723AA2D7E04FBE9ULL, 0x4A6CECC0E93DA354ULL, 0xC1982D1D0DA048FBULL, 
            0x4B36CB25069B91E4ULL, 0xD88C57DC7376983CULL, 0x1689003043697D20ULL, 0x503332FC3DFE7B3BULL, 
            0xDC6B5C98DF6E033CULL, 0xC812FA0124E528ACULL, 0x4D913E695C2E4EA2ULL, 0x4F1F6B3CAA609549ULL, 
            0xB41FD9C2C62BF03EULL, 0x84BFF885176AEACDULL, 0xAD0B3A5CAE44A925ULL, 0xB64D97A20E8ADD97ULL, 
            0x6782323B4AE7FF25ULL, 0xACC51B756C898D87ULL, 0xF679F07DA67E39D1ULL, 0xB26C79C7FEB82BFDULL, 
            0xD8F3EB0C8C81A2D5ULL, 0x94A288091B755468ULL, 0x22EACFE2EA7F850BULL, 0xB4DF70F679D24C69ULL, 
            0x78D6DBA64A2FD59DULL, 0x922640E1C4EB3610ULL, 0x114BB681EB01CABFULL, 0x50596FCFCBADCCA7ULL
        },
        {
            0x2503018E42BD6EEDULL, 0x0E51E0E19017FBB8ULL, 0x380309F1DEBC6916ULL, 0x178481AE3A238DF6ULL, 
            0xBB123EAEB48C4253ULL, 0x7B5E332A240B2C24ULL, 0x811C5D064B6C8FF6ULL, 0xAE6E33AEC3821FCAULL, 
            0x343DFA767E806EFFULL, 0x029872FB6D607654ULL, 0xC4E26DE6533529CCULL, 0x469601D9452C0320ULL, 
            0x052BB5525E90B95DULL, 0xEBC8FE4635FB8127ULL, 0xFE28F48E9413F3DDULL, 0xAFB11838C1DCE34BULL, 
            0xE257DDF92DBEF2C9ULL, 0xA514B41510BD6E02ULL, 0x38D790703E010C2EULL, 0x87F1DC93DF6DCD16ULL, 
            0xB8D7181BB28DE6CCULL, 0xF93A850115686EA7ULL, 0x6F0791C5F2A26BC5ULL, 0x766AC398584DAB79ULL, 
            0x107EB63FEFF794DAULL, 0x3B2745BC66DF20C8ULL, 0xD4632961214CC763ULL, 0xC5A5C29FFE3ABF59ULL, 
            0x3D3F73A68DD5B7C1ULL, 0x6E4380A821FB2E7CULL, 0x769F04A47636F90FULL, 0x185B1338011D41E9ULL
        },
        {
            0x52984B14D7DB3446ULL, 0xBDEE08239F4353F3ULL, 0x52CDD6A5D7FB283DULL, 0xD7F9445F68FF946AULL, 
            0x22A53BA2A5CD60E4ULL, 0xA79B9439C9BBA835ULL, 0x241E8EA3891297CFULL, 0xC76676D24273D0E0ULL, 
            0x68CC587E9AB928F0ULL, 0xA381E66510E3852BULL, 0xA09DE4C124F872A5ULL, 0xF006F4FFBB72D857ULL, 
            0x7C20A30124DFB74EULL, 0xDFA8FBA172C2F58DULL, 0xE701256CF72BA56EULL, 0xBD72EFB86314B848ULL, 
            0xAFDBA114A36B56FAULL, 0x5C3EF87FFC07CFFCULL, 0x2074EABB3BBF0C5EULL, 0x564F8643F4568BF1ULL, 
            0x0A012317A692B591ULL, 0x9F94C60E6270DD2EULL, 0xBFE2835DF16B0E19ULL, 0x809E459A0A48E72EULL, 
            0x5851DC540F5C818DULL, 0xDD0F9144EBF82524ULL, 0x988729AA10CA9696ULL, 0xAC33920F0480AB40ULL, 
            0x778BA7CEDEE7D029ULL, 0xCC63C3DE0205B2B8ULL, 0x87C2C7355C284541ULL, 0x468AC1F54D0934EDULL
        },
        {
            0xE41C7CA591A5A251ULL, 0xB66A59CD4A777726ULL, 0xDACAC1774E4B39FEULL, 0xB8139FC7A4FC1DDCULL, 
            0x236C70A0579F186CULL, 0xF2430B5402B7FE0DULL, 0x52E011DF39C74549ULL, 0x8AB1872907F6574DULL, 
            0x3C1C97D9041AC33BULL, 0x57261BFD0CE1EFDCULL, 0xA896E4051833515DULL, 0x12D75211E406DA40ULL, 
            0xE3096D477A9E8DA9ULL, 0x11319ED741A84B8AULL, 0xC483C378714C7053ULL, 0xFE3BCA1638894415ULL, 
            0x98AC2CA1E48DE1E7ULL, 0xD6F4BEE756249D56ULL, 0x686EDADBCBA64FA9ULL, 0xCC8117F1C910009FULL, 
            0x46868FEA4D21DB00ULL, 0x1671A1D2E775B27FULL, 0x8C4ADD467AE903D8ULL, 0xB6F947F88027C8C2ULL, 
            0xCABD31D08C749FC9ULL, 0xDA1001B70DDF1769ULL, 0x8F77EC48DB6B1219ULL, 0x155F9E2003BAFEA4ULL, 
            0xE6E3F2145C5342C1ULL, 0xCAE2777C4033E256ULL, 0x65EE643327C3FE9AULL, 0x44EE6DC7922A5596ULL
        },
        {
            0x677CFAF754D8EE9AULL, 0xD1E0A45AA0DD1392ULL, 0x26F28D2748B43BB3ULL, 0xC881F9E3E0FA3B0EULL, 
            0x7C038122A1CC4C38ULL, 0x2D556ECE9AEA2C2DULL, 0x06EC53334E11910DULL, 0xEFC13BD1C561AF23ULL, 
            0x9C76F3FE0A681DA0ULL, 0x16F5F9490CC950F2ULL, 0x1051BD90EDBCE78EULL, 0x98A16827F06042C8ULL, 
            0xACEC2CFE29919F19ULL, 0x75B4A252F0468EEFULL, 0x69C5D9F6CC32D4A8ULL, 0xFE2A2A136B8172B0ULL, 
            0xFE2E6537203630DAULL, 0x986FA28BD4235913ULL, 0x01E61DC3D5B252AFULL, 0x59BB11BFA93A8223ULL, 
            0x85983964BAAAF5ECULL, 0xBA4C0A00A63E1834ULL, 0x8B5A8BFB87B88E24ULL, 0xDAAAE1211D035DA3ULL, 
            0x004C2F04A95D8127ULL, 0x839EDECA02204D0BULL, 0xA315B4F1AE525C07ULL, 0xA9E4B7C8ED55937AULL, 
            0xF13D0DB21F00CE20ULL, 0xEC0AD5BA445103ECULL, 0xB72242BC324012C6ULL, 0xD148F7B1994E94D7ULL
        },
        {
            0x8D86907D3A43C611ULL, 0x08070C3E6296E4B4ULL, 0xB7B48154CB5A811AULL, 0x452BD5A2B604F4EDULL, 
            0xD26D846E5CAE41CDULL, 0xC4C08769BC922260ULL, 0x743F9786796692FFULL, 0x991F3F8777379A1DULL, 
            0xDEE45ACFDBBF324EULL, 0x933D53FDD83374BEULL, 0x378161EED20F4EFDULL, 0xEFB13749B664E5E9ULL, 
            0x76931054A25F83CEULL, 0x6445EBBB1DD3667CULL, 0x774FB063A6E66835ULL, 0xF78A34816C8D0D67ULL, 
            0x8DC42271736A8740ULL, 0x9051D1456F21E50BULL, 0xDDBA1A1B48DC241EULL, 0xB6240FDD422BBB4CULL, 
            0xC9DAA80337C92E4FULL, 0xA280663FF45CEF4BULL, 0x42F9BFC7BEF4A5C3ULL, 0x7119E673A4E94DF2ULL, 
            0x8AE800668012CE23ULL, 0x8DB3E1106C7F4AF3ULL, 0xE2CE036123663BFEULL, 0x7996DA7861074963ULL, 
            0x92C2F7391194CF4FULL, 0x49B96EA3EE04646FULL, 0x565C3D9053072389ULL, 0x0671A8EF664E0F5BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseCConstants = {
    0x7F533DF6AD302922ULL,
    0xA047242121753693ULL,
    0xBCB5DCB17ECB790EULL,
    0x7F533DF6AD302922ULL,
    0xA047242121753693ULL,
    0xBCB5DCB17ECB790EULL,
    0xD7C9166EC2E725ABULL,
    0xD6B3E31909B7DF31ULL,
    0x11,
    0x4E,
    0xE8,
    0xD3,
    0xCB,
    0x67,
    0x27,
    0x1F
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseDSalts = {
    {
        {
            0x5407366C9E769A3FULL, 0xC33517CD38387980ULL, 0xE2D14A3C829A2C6CULL, 0x1077D4A61E0A5388ULL, 
            0xCBFB9DAE9705F349ULL, 0x4236BF36444A7CC8ULL, 0xA7A6437DFBDD296DULL, 0x5AFF992AE07F4FA3ULL, 
            0x3BD3B1E6F3D74DEEULL, 0x590C893656506B43ULL, 0x48E244E26A73B987ULL, 0x1850C5CBE733FF47ULL, 
            0xA6C539C7405AAFD0ULL, 0xE3D25FDEEED10595ULL, 0x0D464610B5C8D675ULL, 0x1F6145AE08B85B86ULL, 
            0xD90D057C835747EFULL, 0x81C0C4E17B5B935BULL, 0x100FC86100058404ULL, 0x963C5B6C620CA6AFULL, 
            0x64B0C3C54D6F4CDFULL, 0xADDF5FE5E50FF1EDULL, 0x49E3808AC9378AC4ULL, 0xA470715B5D310C57ULL, 
            0x1AD39EB6993CDC72ULL, 0x62571CD8EB5CDB8DULL, 0x3E27FA3D7F466D9FULL, 0x84D7598732F8FC64ULL, 
            0x1D821B4D8BAB7260ULL, 0xB91381C66D4F4AC9ULL, 0xD5134F224B63FA3FULL, 0x2FC685749E313381ULL
        },
        {
            0x44B2B14F5ACCBBF3ULL, 0x76E9113EB064E8F7ULL, 0xD3E49E5765E68231ULL, 0xD4BCE8F091AE8729ULL, 
            0x2E8BBA47C79B7D61ULL, 0x6DD476B8C2560495ULL, 0x8612AD6446641A5AULL, 0x239AED1C7AC9E5B1ULL, 
            0x8C9F19E9871CE0C0ULL, 0xDB7182CBF1FA65B1ULL, 0x638A4930F91AE49AULL, 0x3259B59303D931F8ULL, 
            0x9C03C854BDB4C1F6ULL, 0xA0B51B44D6CB897AULL, 0x4B28B868DF40AD58ULL, 0x2CD729BAA0533735ULL, 
            0x25062BBD0E7A66B6ULL, 0xB17F59E30B35B8B1ULL, 0xF1B24970D74FD8DDULL, 0x34E0EB439B9F939CULL, 
            0xBB91C97A3E0034ECULL, 0x1B75BF7FFB1D51A5ULL, 0xB3FF5EEB46E5B875ULL, 0x335CA1860108B59CULL, 
            0x660C222279224E6FULL, 0x02F2406B8058FDA0ULL, 0xB64CB7DDD2CD3DCBULL, 0xE02E3301DEFDE621ULL, 
            0x1400D6985E29297FULL, 0xF68E4532A0353F80ULL, 0x54D9DB2B9FE1A80DULL, 0x5BA21149538CA2CFULL
        },
        {
            0x50E04CEBC04937F2ULL, 0xEE9E447895574FA9ULL, 0x362F6AEE5D843EE6ULL, 0x16491F34A351CB73ULL, 
            0x57DAEC16CF378774ULL, 0xA604043B0C01AA81ULL, 0x494B195D93D9DD1FULL, 0x00C8C0397660219CULL, 
            0x0A85DEEE9CF7C357ULL, 0x7C276BD1B24FEE95ULL, 0xAFDC5F58DEFC1F4AULL, 0xE9EEEC63E62EC3C0ULL, 
            0x5C6CE5C1849536A7ULL, 0x62A47DD7F84C3A9EULL, 0x4E30AA6911EB2CA8ULL, 0xAE4408EBB4947EA1ULL, 
            0x0D3E564F8F0C50E1ULL, 0xC56E7274AF8E03C5ULL, 0x03B89657A70F1F60ULL, 0xF5E82E3FE1B30BCAULL, 
            0x4C5130FC381BFD45ULL, 0x1D2B6439B69184EBULL, 0x551B9A71360DD3DBULL, 0x96DDC98A3FF1BDB1ULL, 
            0x73B732F5C1F6C8ADULL, 0x4A0E015C794AEC7AULL, 0x9565B1810F48F6B3ULL, 0xBCE26F05F17DAC61ULL, 
            0x4841F9C4F37D9864ULL, 0xB1C8DD4F82DA49DFULL, 0x2906C5B9DA059DDAULL, 0x92ADFAF6C30EB707ULL
        },
        {
            0x10605F2A4E7E44ECULL, 0x3C7429B8909453B0ULL, 0x47A9881F7CC4B654ULL, 0xF0B43FC2B536AA27ULL, 
            0xEA2D4AD44541DDA3ULL, 0xA28F0027EA2F2FE0ULL, 0xFFC617CFB677705DULL, 0x135A981DF846B7B8ULL, 
            0x37A98583592F483CULL, 0x6848D499FE53A268ULL, 0x96477D54A40FDE2FULL, 0x068E5B58B9BC4432ULL, 
            0xBEA5C0FBF9DCAE80ULL, 0x97D6087537787FBAULL, 0x39ABC6BF5B7E1FF9ULL, 0x2DF720F7C699EAF2ULL, 
            0x131D68664A6C54A4ULL, 0x0C58C7D3BB0BAC7CULL, 0xE5EC61377748076FULL, 0x42AA1CB555D25554ULL, 
            0x8A69A277FEFC1A10ULL, 0x99FBA57CB9703857ULL, 0x6DE2F29A7BB30230ULL, 0x8836707D17DB18ECULL, 
            0xB3360C91412817C4ULL, 0x05513F8D3140BBE0ULL, 0x026D13A1C5C83860ULL, 0x24666DE562365110ULL, 
            0x1E44086E8D31A710ULL, 0xA26948E0AED2CDB3ULL, 0xD9579029A68261C7ULL, 0x4A0A2D965BCC082DULL
        },
        {
            0x06CBD4F7EAD0DA9CULL, 0x619E6A05C57DBD4FULL, 0x068BC9CD7BD09F26ULL, 0x4F9896D86D958585ULL, 
            0xEA89133273DCE6B3ULL, 0xB87DD0D792EB6DCFULL, 0xAA637919D98448E0ULL, 0x8C05F8D2B0D6EEEAULL, 
            0x53300EB9D906BCE1ULL, 0xD8605B8636CABD89ULL, 0x250BBBB1AC752D93ULL, 0xA542ABAB56077C6BULL, 
            0x393AAF882E797556ULL, 0x04A8DA2A9D8167E0ULL, 0x237BDCC09C7339BCULL, 0x2059EE4AD772C3D8ULL, 
            0x4694FF18808E747AULL, 0x4340137B68C27594ULL, 0x30EF8E986F081E20ULL, 0xC0C81EFCA5EA98B4ULL, 
            0xD252D65F079AE92DULL, 0x31D2AEDF557A042DULL, 0xA2C339189178A870ULL, 0x64A19073A5332370ULL, 
            0x870F8A10BD25C332ULL, 0x1CFCAE1B84A5E384ULL, 0x2353822E3595C095ULL, 0x730A9B9CEF362DDCULL, 
            0x6D29D959F5023A18ULL, 0x09F72566580E4BCCULL, 0xD7C23E160ABCC6B6ULL, 0x433C7EA12F7BE840ULL
        },
        {
            0xDE5185FDDD82D014ULL, 0xF8D0A58558182D04ULL, 0x49D564331289B638ULL, 0xE36CE8BB4A2ECF4EULL, 
            0xAA2ECD1F32DAF12BULL, 0x4A6B433B0DB9477BULL, 0x2F66A944CDF723C7ULL, 0x310B2A9F83EFE716ULL, 
            0xBB4EF2EF48102CF2ULL, 0x7AD9389E08C001F4ULL, 0x3887010D6C095BBFULL, 0xE2DF564D46057CC8ULL, 
            0x662C0DE3F6FA68C0ULL, 0x06475CBDB94A02C4ULL, 0xCAEAA47322C6D2B0ULL, 0xDA350FADDCD7C678ULL, 
            0x5DBC2F3D252A03F2ULL, 0x9EEC6A857A364F4FULL, 0x7F8052A9E65CBB05ULL, 0xC8BBA9C9D5EF65F9ULL, 
            0x6196553EAD5A99B1ULL, 0xC018E72F82938F20ULL, 0x4125B8D71AAD943FULL, 0x815F0A22036D8227ULL, 
            0xC7859080165FD64BULL, 0xAEBCCCE72A99588DULL, 0x73198549C59F57BDULL, 0x66AB944F2C387532ULL, 
            0x2B4694D00D783753ULL, 0x86B5A03EDFE31C88ULL, 0x70BE02D545446F8AULL, 0x181024B5A0295FC6ULL
        }
    },
    {
        {
            0x35BB689016CB5663ULL, 0xCBD220B93D953E61ULL, 0xC16BCDE1C37B2D8EULL, 0x2FC9B0B2E9A2CF5DULL, 
            0xEDD000C5768FCBDCULL, 0xA09C2E47324C8EF3ULL, 0x0CAEA7164E6CF76BULL, 0x5A4FA346D0760241ULL, 
            0x762EB100A30C02CAULL, 0x35B724CE4DFA3FFDULL, 0x32FC6EEA49AAAF39ULL, 0x1732795ECDEADBA5ULL, 
            0x91EEB36FD66FFA7BULL, 0x392FF37FE08C5D5BULL, 0x24B7137B44F51854ULL, 0x33C1BC8A52C6BEF6ULL, 
            0x0DB6484DFF43FE49ULL, 0xEC5C2D15885E7AD0ULL, 0x16D731D195707C38ULL, 0xBAC81C2CFAD43838ULL, 
            0x8BF4BC2C6A918390ULL, 0x1288724788B36079ULL, 0x2D272FD442014698ULL, 0x663EA11A958F7266ULL, 
            0x340534225601E158ULL, 0x5D68D1102B63F562ULL, 0xDDBF0F3888860CB1ULL, 0xBE4433EBF06F4DE3ULL, 
            0x2BD04C82A183D8F1ULL, 0xAE3D62576522DF42ULL, 0xC428AFC5839F39D8ULL, 0x245ECD9C92EFE5E9ULL
        },
        {
            0x44D535F2BD196AB7ULL, 0xD40E5899EAE98ED2ULL, 0xBB2A7AB474EF92D7ULL, 0xA162AC81ADB0C248ULL, 
            0xBE0D8E6314644178ULL, 0xBFEC213DA8E92B51ULL, 0x6940C89C731A4B77ULL, 0x3FA2D0C4E2B01082ULL, 
            0x353F3F7095A38749ULL, 0x305D6B19F530A793ULL, 0xFAAC088B2AD7CC9FULL, 0x50603E2DFDC66169ULL, 
            0x26FE84017B5B13C9ULL, 0x67C76F9F8FF7FE16ULL, 0xED441DD447154909ULL, 0x9E215B26472EDAF1ULL, 
            0xA7C55620A15B952BULL, 0x9C14777C11B1031EULL, 0x0B06273C4AED71F4ULL, 0x549209FE1DB6A697ULL, 
            0x2E5891CD2A94F8F5ULL, 0x0F87391311304535ULL, 0x1DC42DC8E8D87DE9ULL, 0x4E11C7474E84916BULL, 
            0x216C36792164CBC7ULL, 0x6E8E0C1D83836A55ULL, 0x53F3E0501A306D51ULL, 0x872FFA8C056A607EULL, 
            0x9D221A0B3566B152ULL, 0xF2DF7BE726CDCD50ULL, 0x313A49992A189165ULL, 0xBBE1D9CDEF773F55ULL
        },
        {
            0x13D1B5970FB7B246ULL, 0x9EF56E02D19DBCCFULL, 0x16DBF19A274980D3ULL, 0xF7B666DFB292ABBAULL, 
            0x833D623F1DF23206ULL, 0xA1337BD118479AEBULL, 0x8E1D73D5D39E7050ULL, 0x5FAB017E6D454524ULL, 
            0x90C1BFEF2502A3D1ULL, 0x7CAC96A28FFB6AE3ULL, 0xDEE0F817A32585FBULL, 0x936CE1C5E6A5BD3EULL, 
            0x071EB3E47C7CCED6ULL, 0x3324C4644C2DD27DULL, 0xB1C3A2DF20CCC36FULL, 0x5D0C26D23BFD60CFULL, 
            0xE1013971C9C3EB2FULL, 0xC80ABD20BD727751ULL, 0xF38742AEB255311EULL, 0xCA4FD3A1A369F371ULL, 
            0x265120E00DDD4AC4ULL, 0x74FA21B7FF2B7D5AULL, 0xD3F4544923E59445ULL, 0xF2A8EAE2D434885FULL, 
            0xCC1C11A13D9C09E4ULL, 0x69C201B5575B4871ULL, 0x5BB8E818F70FAF7FULL, 0xFBFC0ABEC6E3DF16ULL, 
            0x2E8D019C6710B852ULL, 0xD5D8E31D5A0BF861ULL, 0x1334015CA13B08F6ULL, 0x95C9C62E34062538ULL
        },
        {
            0xF238606296620511ULL, 0x8740D2A3A68862E8ULL, 0x2AF943F077921F4DULL, 0x908F1EA1F3C2E49DULL, 
            0x7B2D19E1377AB6D9ULL, 0xE3E766F46191FFC5ULL, 0xD9765E791B448F5FULL, 0x5906E5AA20A52B72ULL, 
            0x63CCE8C5341AB978ULL, 0x1D685FDBE5842FB8ULL, 0x157DE115327D5753ULL, 0xBCF62665714FC019ULL, 
            0xC9033BB3990F0521ULL, 0xCF1A444F9EFF96FFULL, 0xFF9B0905EC198B7FULL, 0x27DE917AF25D21E3ULL, 
            0x47FB0316CF0A1CA6ULL, 0x35073399563531B9ULL, 0x611237F47212E21FULL, 0x03B13D4391AB817FULL, 
            0xF0B13C78ECE1963AULL, 0x603C34D643099312ULL, 0x087E52C0C1EC0E41ULL, 0xC724D2BF46308FDDULL, 
            0x7BF6EB3A9B223D0AULL, 0x76D44E26BB077F10ULL, 0xB3299A7F1A14ECE0ULL, 0x01257391FE701341ULL, 
            0xBBB6E19F6EE90308ULL, 0xCD218A295A0D2451ULL, 0xB2D87785E92352E0ULL, 0xEF86C8F00C3F2376ULL
        },
        {
            0xD8DA16740A4BCF40ULL, 0x18DFDD7C1FCB42E5ULL, 0xDCB0BDBA23B7B0C1ULL, 0x1C13D41A70157FFAULL, 
            0xA736E1BDA20FB695ULL, 0x8DB4A6DC6AEEDBD3ULL, 0x6C31478507C5F206ULL, 0xF12CBFBF3D5282BEULL, 
            0x9FAF24EB03C38121ULL, 0x069A91BF64AA3988ULL, 0x93DBA3551DD68376ULL, 0xB715287D35631EAFULL, 
            0x58ADEEC7FC2DF4E6ULL, 0x1E1FE7D83D440020ULL, 0xBF4EEEC70606CA08ULL, 0xEFA321E67A157248ULL, 
            0xEADE4B228286D633ULL, 0xC69A3609A3073926ULL, 0xEE8A31B488EC87EBULL, 0x5751A2ED5FD22472ULL, 
            0x675B71AF78394AE6ULL, 0x9830FBA3A0E09537ULL, 0x3797A9827719790FULL, 0x5E600C6DC84D7FC6ULL, 
            0x8486C594443EE329ULL, 0x71571BC59AC2AC5CULL, 0x7D6F73937D215FA9ULL, 0xE8D2AE8796CEA4A4ULL, 
            0xBAF1079263089BD3ULL, 0x05D7AD344E2A1BB1ULL, 0x7DE50D7DC8274C92ULL, 0x3C867BA4F9C06E01ULL
        },
        {
            0xAB34694ABB272770ULL, 0xD06095A427B04A9EULL, 0xCF8A3C9AE5EB5AB1ULL, 0x48C272BF514E2759ULL, 
            0x37DE9149C1731AC8ULL, 0x797E9C71F58686A6ULL, 0x059E1BB1D15BC571ULL, 0xC21D9FA56658CBB6ULL, 
            0x630194E423AFDDA2ULL, 0x3B8A6B95ACC0FB22ULL, 0xC382C44403EF85E3ULL, 0x67573644F771764DULL, 
            0x5F88C028FE501F9CULL, 0x0895F6069BAB0046ULL, 0x4CBC894620C9C327ULL, 0xE14080DDE2F92466ULL, 
            0xB15B908B5633EDFDULL, 0xFAD3CA06490A5F39ULL, 0xE3C0B864BCCC168CULL, 0x78B97CC88A901AF5ULL, 
            0xB6F48525EFC46CA0ULL, 0x974F81768FFE058AULL, 0x5DD79F33D155F72DULL, 0x190769035B7CA9AAULL, 
            0xC2DEC89CDD52ACA4ULL, 0xDD6AB535C832D5CBULL, 0x38217A12533BA5E3ULL, 0xFDD6F400AE9219E2ULL, 
            0x2DE586E452002D34ULL, 0xC8DAA2FF5CFDD7D8ULL, 0x5BF2D3CEDCA29FEEULL, 0x4BE948FA2BA3F379ULL
        }
    },
    {
        {
            0xD8C50E289486A9E9ULL, 0x81553B4CAF5453C8ULL, 0x09912DE068C56E8BULL, 0x1D322A212DC8B9BDULL, 
            0x797DF7A496F431ECULL, 0x047B1A8CEBF99A2DULL, 0xAB6D94E1B635A6DBULL, 0x5C6431553046E9C3ULL, 
            0x9B135C5D2D1171ABULL, 0xDACA7F4D9217A7EAULL, 0xCDDE35D085747FF0ULL, 0xF628895FCB4BC96AULL, 
            0x2B790EE0880636DEULL, 0x3EEEF838B6B1C88AULL, 0xC07A5B9D0581A025ULL, 0xEA3D8C509C359185ULL, 
            0xD89450E6F8911551ULL, 0x3F5ABC302E2A08E2ULL, 0x0DB67DB15311DEBAULL, 0x21331ED44E1076E2ULL, 
            0x214903B2BC27715CULL, 0x75A2DA86A826E7C5ULL, 0xBC3AE7D4033B7A16ULL, 0xD0E3AF322AEC388FULL, 
            0xE4D7A854D055B9DBULL, 0xD121C2E271A26D81ULL, 0xFE94BBB5DBA90928ULL, 0x72CC3ED52A0535BBULL, 
            0x81AD386438A918A8ULL, 0x1DE23F2D2E0E1E4CULL, 0x8D65BFB4BBFB04C7ULL, 0x2F8400EAC7EFC7EDULL
        },
        {
            0xA866D09C8BBC5888ULL, 0xDF081160ACF8ED26ULL, 0xDB5FDE59A57E50C0ULL, 0x3C43FBC510E0D505ULL, 
            0xAA1065747F5E769EULL, 0x875C45BDF23AB4E2ULL, 0x8F74F23BD3979F43ULL, 0x52D8EC98669ECE2CULL, 
            0x24FFB793B97798AFULL, 0x86674D5BBEBEC3A7ULL, 0x1BBF929FBE3773F6ULL, 0x24AF9769AAFC42D9ULL, 
            0x81853638E588DE0FULL, 0x257D67449CC7D447ULL, 0x5595430BA0A9D44FULL, 0x98941DEB98A7DC7BULL, 
            0x1671BFE46FBF69CAULL, 0x1C9072BB8C23DABCULL, 0xD99990B1F3EB7914ULL, 0xCB5A007C31A2AA88ULL, 
            0x9EF2C64FEE72AF97ULL, 0x68C993CD0601B316ULL, 0x0770682F81BBC45CULL, 0x26899F64225B3BF4ULL, 
            0xF9890E68114020C1ULL, 0x967713CE47CDA46AULL, 0x333B646661296774ULL, 0x054D7FEDF89A446FULL, 
            0x5BC65F1B22094FCCULL, 0xD88336717FEB3847ULL, 0x9AC4A4FBAD358154ULL, 0x6F23621711A8B543ULL
        },
        {
            0x408225CBF98D1951ULL, 0x822D04C21D5EB37CULL, 0x0EEEE67D39AF162FULL, 0x3DBE945043140D34ULL, 
            0xE301D3CB21CB500FULL, 0xA4A7F65D42EE96D1ULL, 0x27FFEC54569A0116ULL, 0x905C3315B2D6CD60ULL, 
            0x2592324B71B03E28ULL, 0x9EE4E1C4CBCD4D30ULL, 0xB15AA8831E17AA53ULL, 0xB5D595D3662D675BULL, 
            0x2412B537662D4E6AULL, 0x8F1D3447624D7D99ULL, 0x385E6BFF20505C90ULL, 0x7CA279654E155CFFULL, 
            0x4CD07BFB9A67293EULL, 0x92190A6CC64F13B0ULL, 0xBAD07B4961188511ULL, 0xA95B663B1A27DFFEULL, 
            0x57546E8AD5CF3CDDULL, 0x8BF0DD1C934CF050ULL, 0x245B57CFFAB700A3ULL, 0xD70A6A5183FB7BE3ULL, 
            0x668B48D7B1F8B648ULL, 0x489DEE61B83A236EULL, 0x884B9CB47A4791E3ULL, 0xDB3348308AEA2147ULL, 
            0x3EE7BA58B09902A0ULL, 0xACC7BC57F7822446ULL, 0xFA9CC2FA07FAA914ULL, 0x60485AC70257E94CULL
        },
        {
            0x78722801132B2889ULL, 0x2B1A416D7A1FB6ABULL, 0x1195E32938A1BF6FULL, 0xA4B8C3ADD535C104ULL, 
            0x1CAD4C1FCD70C3B5ULL, 0x35956F223F62CA09ULL, 0x6DC1AAFA5F9F23D0ULL, 0x6998E2817E5E7A23ULL, 
            0x33DC78E6A87B3DA7ULL, 0x1D4120EACABD7E70ULL, 0x483C12FC524920CEULL, 0x7155A81BA5E6297BULL, 
            0x39027BB3F92CBD9CULL, 0x8505FE0C2F737900ULL, 0x0B736C04A77D90F0ULL, 0xEBC8471764B3A8DEULL, 
            0x65207B92EB84B7E4ULL, 0xF9C17B6CF4DB94E9ULL, 0xE9CC753D8225AFA1ULL, 0x0817B0C447514888ULL, 
            0x3A7F44A44581478DULL, 0xC8F52D795416AAE5ULL, 0xABC1BE2A4ADD5377ULL, 0x0B86B84D074468A7ULL, 
            0x2B4A02019C6D26F7ULL, 0x9722BFE9E3B0AA8AULL, 0x9FDC6C4E0521000CULL, 0x6E9EE444C6A3591CULL, 
            0xD04D66E1159ACB66ULL, 0x6D9F1DA1B17A5279ULL, 0x1D90F74F635C2DF3ULL, 0x79F4D6EDB487694AULL
        },
        {
            0x3C2594BFE6A22270ULL, 0x25CE4C37C5822973ULL, 0x9EAB1E67BA180F1BULL, 0x1D65EA11B4F7CFBEULL, 
            0x4AF637199C36A563ULL, 0x7ABAC101790A5218ULL, 0x795EDB18BB3F5D6CULL, 0xC14A49D620AEB25FULL, 
            0x0E6B42474FEB96A5ULL, 0x67399030F0F4FBD4ULL, 0x332A251B2300E9C1ULL, 0x70C0179A10E7381DULL, 
            0x474F4A28ABF9D29DULL, 0x680E1CE13E6FC202ULL, 0x328AFB55A71E8C0BULL, 0x7CC186A415768A1BULL, 
            0x1CF6D9174C9852B4ULL, 0x302912695EF3B5EEULL, 0xDD909694FF1E3A8CULL, 0xE70623C630DD4220ULL, 
            0xEE315C05045B2DEBULL, 0x8904A79E1C8CC791ULL, 0x2A74F901F34AA1C5ULL, 0x71E6BEE0C42FF72EULL, 
            0x50D2B0050A70709AULL, 0x4C65A6B208B770A7ULL, 0xB99504E69A5F35D6ULL, 0x443F76C3C51CA6D6ULL, 
            0x528D8F463B885B8EULL, 0xDCF295D2DC495F87ULL, 0xFD41C8A37DB1BC5FULL, 0xA0A1CF3C6B229370ULL
        },
        {
            0x98BA944B1BBDC372ULL, 0x775FC4199F96AB6EULL, 0x34B66670836F04EDULL, 0x27F3D9BB2A3BB320ULL, 
            0xE2566F8FEB2F75D0ULL, 0x98785351D93133E8ULL, 0x8DD4E681D1610CBEULL, 0x1FBB47C9DD36F1E5ULL, 
            0x9B19EFB1E1C0362AULL, 0x59324F74F36BF723ULL, 0xC8B491A6E7FB3C03ULL, 0x12228AD8E5BD6AC4ULL, 
            0x9928D51FA217C5A2ULL, 0xBF6ECE8045124C61ULL, 0x1E4FF1841B5C0449ULL, 0xECF042CB9E7FF44CULL, 
            0xCDF6ACB34983CBBFULL, 0x09F3B5BFCA97AAE7ULL, 0x1FD60A2ED6D0DA49ULL, 0xF67AA3F5C915D5E2ULL, 
            0x93B0D557D2D386D8ULL, 0x9ADF3AC6FE8AC537ULL, 0xC19E2F1AF65624DCULL, 0x28B4CE7B7A800BDCULL, 
            0xBFB8C878A22627A9ULL, 0x62277B4F85C161BAULL, 0xD80FBEFB102E60E6ULL, 0x8BF14A1B093C6B3BULL, 
            0x5A8E24FF538DADFDULL, 0x834662189D0350D4ULL, 0x7E6CFD730155AF44ULL, 0xE6A4C91F25216104ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseDConstants = {
    0xA4DF92B748C485CEULL,
    0x62AB207BB6C971A1ULL,
    0x7A474EFAC60EF129ULL,
    0xA4DF92B748C485CEULL,
    0x62AB207BB6C971A1ULL,
    0x7A474EFAC60EF129ULL,
    0x9A9CE0E5FB526388ULL,
    0x00EC81A2403B8F14ULL,
    0x55,
    0x68,
    0x9A,
    0xD9,
    0x47,
    0x4F,
    0x6C,
    0x6E
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseESalts = {
    {
        {
            0x78F32F1BFE3A7F13ULL, 0xADDC8C5D1698ABF7ULL, 0xB4BBD57542C08825ULL, 0xEB448607EE603502ULL, 
            0x24E22F64BE1D0824ULL, 0xE56BEEF352467DBCULL, 0x3B589FD6CB02BA25ULL, 0x40A1812CF56C3E88ULL, 
            0x9CE6A4F4D827EEF7ULL, 0x8D4CA5FC747377E1ULL, 0xF9CF6AA11B05352EULL, 0xFB97D7A74CB64AB2ULL, 
            0xAA46B8A9803DCE1FULL, 0xED390F4F646D66C5ULL, 0xED2834E62F1B7DACULL, 0xAF27B9572D61122AULL, 
            0x0FEB380F80424A77ULL, 0xA1C6239A191FDFA2ULL, 0x91B6CC4E20CFC633ULL, 0x57AA546F1921D55EULL, 
            0x96D212C181E88472ULL, 0x40C2B833228427B6ULL, 0xFCA48E42F59877A8ULL, 0x828734588F57563CULL, 
            0x2F288D2A6A7FCA62ULL, 0x5A639133D739F198ULL, 0xACD26439FB298400ULL, 0x768C0BC2D8D24F9DULL, 
            0x772DE7FF080B3EEAULL, 0x3B08F8F5772ADD05ULL, 0xB09AE1EC1B69B672ULL, 0xFEB890540A256F42ULL
        },
        {
            0x946E690645B0CE4AULL, 0xF3B40C37DA180B41ULL, 0x55CEFAE1890D1276ULL, 0x5A55EAD7FBB8A274ULL, 
            0xED064E498E2C9C8CULL, 0x63D55851673F9C68ULL, 0x71E51968D02B08F8ULL, 0x140BA065F5DFEB9FULL, 
            0x5F95848BADAB70BBULL, 0xF502617272754A8DULL, 0x871B0724DFB686A7ULL, 0xE4B3AE2C66DBF70DULL, 
            0x0058F16BEC36DD6FULL, 0xCA3EDF23E8F0D566ULL, 0x0D2F7C007AE013FDULL, 0xA09A20D0B868B8F1ULL, 
            0xD5C3E94727B2B2EBULL, 0x11BC8A8889868EF7ULL, 0x962220DF9FE67040ULL, 0x831FD0F316ED1A9CULL, 
            0x55791BF3D78427C1ULL, 0xD03B3F24223279B7ULL, 0xF65CD2D18E2BE228ULL, 0xC32174C43EC35372ULL, 
            0x07DCE4065AF14AB5ULL, 0x8F8D67A5DBE8621AULL, 0xE12914B39C01B7C4ULL, 0xA2E708A99272EF68ULL, 
            0x7756AE5DB9E5948EULL, 0xC955FCE13374F706ULL, 0xC601F3E7F6318182ULL, 0x548BA1AD20A2CE74ULL
        },
        {
            0x8F317B8EDDE31B84ULL, 0xF7EDF3BCC850BBC9ULL, 0xB2887E31909D8114ULL, 0xBED2789CD4C40EADULL, 
            0x10B68F4A0C79948BULL, 0x49A20571FA4A85F5ULL, 0x5D54E26585DD026DULL, 0x4BBEA5138BDABB73ULL, 
            0xEDF2FAC6A4C205D7ULL, 0x7A65196D0FC8262AULL, 0x55FFCD32504DF65EULL, 0xD553235202DA4240ULL, 
            0x37CCE949FB896750ULL, 0x0916C0256BA4B1A9ULL, 0x8152B61793621237ULL, 0x22E8EB4EA6520151ULL, 
            0x9C94CC59CE18FAFEULL, 0xA950A619E2351312ULL, 0x397CE493E3822767ULL, 0x8A49AA40A502DFE7ULL, 
            0x517B272B2DC5E03EULL, 0x42E3A7469D570BF9ULL, 0x665A8CE7C9BE6896ULL, 0xDD96120AB27599F1ULL, 
            0x752C62BAA4262F72ULL, 0xCEA4027A4B4FF3AFULL, 0x28A46B595413158AULL, 0xDB2877B8CAAB4F09ULL, 
            0x37D343FC2BE33278ULL, 0xE0D0013C413ACDAAULL, 0xE9AA0A7CC2974A26ULL, 0x09803F169C836D3FULL
        },
        {
            0x86018FFCFDF39DAAULL, 0x470DBA3DAF35A719ULL, 0xF4F034723D7E917FULL, 0x83071C54BC181419ULL, 
            0x3F4BD838C15ADF0CULL, 0x16D7760D7FCE7F7FULL, 0x7BF5D48BABFEF64DULL, 0xF6CA84B43A400554ULL, 
            0x14430B4A49AC1A5AULL, 0xBB4A3F877AFB68D6ULL, 0xCEFA7A0D5AF85830ULL, 0xC64C63F742C3B6A9ULL, 
            0xAF7BA0239DA01ECFULL, 0xFBE10A10C741372FULL, 0x90535E2BB6E9E69AULL, 0x433034088ABC992EULL, 
            0xBF5EBC055F14049CULL, 0xAFFDD123714BBB08ULL, 0x44E842CC393D4D88ULL, 0x38439DAB7ED71B1EULL, 
            0x0943D95C7CACB9E2ULL, 0xC02D89E9075874D4ULL, 0x822A2CD19936830AULL, 0x6E0518A972190655ULL, 
            0xD8992FECB6CA9F94ULL, 0x698639B2720DB706ULL, 0x0FDE29A64201439AULL, 0x9282CB3B8CFF0B8BULL, 
            0x6621EBB8AFD352D6ULL, 0xDC1F3761B80EA16FULL, 0x19F14210722B7D0EULL, 0x9DAEA0C8F9A8B94DULL
        },
        {
            0x92813D7BC88253B4ULL, 0x5E453D1007D586C6ULL, 0x8BB3D838EBF02924ULL, 0xB0ADC5D01CB9AC8FULL, 
            0x46AB195C0F43CB01ULL, 0x6B4CEB175CC932BEULL, 0x454ED42296FB23BAULL, 0x4A71877AD5F444ECULL, 
            0x1B2CB355FAD1A3FBULL, 0xF62C35F346AADBBBULL, 0x205F98C5F0CB46D3ULL, 0x334055E86D54502DULL, 
            0xE62C97EDC86B66DCULL, 0xE7421C8FDB649312ULL, 0x9529764767E337C6ULL, 0xBE34FD358FC2EDF5ULL, 
            0x292FC3E9A4AC9EA0ULL, 0x585D64FC87E74E53ULL, 0x406ADB1DDF3B6643ULL, 0xC0B96A9A1A79640FULL, 
            0x59E40604A79FEF03ULL, 0x0926022345A9C19AULL, 0x2912BB999D60BD74ULL, 0x8056510E05EC7B9CULL, 
            0xC8D9FB3AC41B7548ULL, 0x20DD2AD2A65A47AAULL, 0xC5ED20044215D6D5ULL, 0x2C84E6869E25F7A5ULL, 
            0xDBFA5F53BFE9D426ULL, 0x7E72896F45F48A19ULL, 0x586766B6099C0FD7ULL, 0x97F32E83636A3CA4ULL
        },
        {
            0x41EDD3A5BBA3D265ULL, 0x2396C6E84BDEB8A6ULL, 0x4DF3F34769875B3CULL, 0xC7A6085F5F9A2C25ULL, 
            0x0FD31A29FDF46302ULL, 0xFC4D39DBAD96A2F4ULL, 0x3C803760FDD22A0EULL, 0xCD833B7E99B491DAULL, 
            0xD3A67DBA999530D4ULL, 0x75ECDAA5FEAB119BULL, 0xAC87DF4E8F0DF6EBULL, 0xB74EF2FB7CBE4D76ULL, 
            0x4239A65DB0C0C1ACULL, 0x81D2975742961578ULL, 0x30FA6B6CB93722BBULL, 0xC757751943F7AC49ULL, 
            0x1A5297EDF63E7566ULL, 0x6F9BB1D4E0738AE7ULL, 0xE75BB3F678553C77ULL, 0x81EEC9120BC4A20BULL, 
            0x1037E6C1C0C28F9DULL, 0x4F6630E94E31EACAULL, 0x01DA1B33B3FAE506ULL, 0x0BEE383C6D00D116ULL, 
            0xF87C9505081903D3ULL, 0x2BCC7C5FA9E015DFULL, 0x0880983CB14F5964ULL, 0x4558FFE4A77F6782ULL, 
            0x736BF7EC9F7BF452ULL, 0x954E6E8A7D2DD7B0ULL, 0x79AE722CBA00E45FULL, 0xB6021D051228C134ULL
        }
    },
    {
        {
            0xED38D42B713DD9BFULL, 0x600AE5C48E24C304ULL, 0x1213F2AF2EDBA68BULL, 0xA120754A60368465ULL, 
            0x64AC9238F00F6905ULL, 0x76D55E1452B0CB35ULL, 0x56C0FC7353C32084ULL, 0x7E8159D15BE14BA9ULL, 
            0x79998350BA4241B3ULL, 0xBBECF82C723340ECULL, 0x705B20BA389F6375ULL, 0xD8752C64436E1B60ULL, 
            0x1FC6F8D26C7744F9ULL, 0x4786D82912C2D5D9ULL, 0x10F8591F6C47B871ULL, 0xF5DB1831AFD86382ULL, 
            0x73A69058719D1594ULL, 0x8676A6705D7B9747ULL, 0x5054D85DA9EDCEA8ULL, 0xEA3BF423B82944BFULL, 
            0x075D1747A7F9EC01ULL, 0x07CDAB2726401B16ULL, 0xA6965BB2BDAB6AACULL, 0xA9A42A4E12400ECAULL, 
            0x32468C8E7973E708ULL, 0x19B5A7941B08B77AULL, 0x92A8F3ED5CC6D900ULL, 0xD9DED0102BA1138BULL, 
            0xA03A887D0C06FAC9ULL, 0x27B78E93513B2B1CULL, 0x2D41684E44439976ULL, 0xB1E3CB5FE7F191C7ULL
        },
        {
            0x4306E6BEB2EEAB26ULL, 0x8122357FF69FE2E2ULL, 0xA200B5D3B147D1DBULL, 0xD627C24C483C0E96ULL, 
            0x961E460CF11973FDULL, 0x0042F2BD004322E2ULL, 0xB2942935ED6C34FFULL, 0xFB08CC7CEEDE4D94ULL, 
            0xCECC70CE33447074ULL, 0xD1C96DFE7BA8B746ULL, 0x073CDCDFE0BCD341ULL, 0x33BE68B2439EC139ULL, 
            0xDC62B44B064F1152ULL, 0x50580E0BB0E44499ULL, 0x3692DFDFEEF75F3BULL, 0x71A8CA3CE072DE0FULL, 
            0x1E178279219FB7EEULL, 0x466B51B1644B4D39ULL, 0xBD02741A232AB996ULL, 0xA499E9AF1308CE18ULL, 
            0x169BEADA67BE1E30ULL, 0xB18A54DACD9E1367ULL, 0xE48E377969366240ULL, 0x9BD0364423866CF8ULL, 
            0x081F820CF899978DULL, 0x273FF3B4FA69C0BBULL, 0x93E9E8F9D8D09D4EULL, 0xB599044ACC225239ULL, 
            0x35ECACB5C23C8B9CULL, 0xFA8690446A9E75B5ULL, 0xC8C8D683824BE0B8ULL, 0x3A371CCB732CC9C1ULL
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
            0xAF253AC91C8D678DULL, 0xDF938E23821FDD69ULL, 0x206F6E1FD2B083C9ULL, 0x1AB6A760904D2185ULL, 
            0xFD2EFA9341E3DE5DULL, 0x8ACE3D9425545FACULL, 0xC4A4C2F8C062ECD4ULL, 0x8C03616575BB6F74ULL, 
            0x8CE6D36440DB568FULL, 0x23E5AD24A55C5B99ULL, 0x61901D60B145952DULL, 0x135E2BACEE2B7B07ULL, 
            0x41B8A487262B7B86ULL, 0xF626D24DA518C7B8ULL, 0x00FFD7E2BB92C468ULL, 0x864A6A220783A67AULL, 
            0x5FFD37E5832EB4C9ULL, 0x1FEDB56DEA500E70ULL, 0xC3133698344DD5A7ULL, 0xA98204433E4A570EULL, 
            0xC9676453BF2454A3ULL, 0xFF1109D89A2CB93DULL, 0x31AB0DC8560D6637ULL, 0x07A364172DBB24EDULL, 
            0x46EB54B8D1F5606FULL, 0xF3278074DDAC8DDFULL, 0xC28FAD68CD51591BULL, 0xD1B62016D7A7781FULL, 
            0x46074969F1AD726EULL, 0xE4D6463AF64BA89AULL, 0x4B79BFA25A134F57ULL, 0x955C4A7013EFBD94ULL
        },
        {
            0x04741243DE1D3E95ULL, 0xDE2E4738C5AC558AULL, 0xDA22D6EFDDC1DE23ULL, 0x6ACA60FE0746F165ULL, 
            0x911A723AD229A1EAULL, 0x0067C589863A613EULL, 0xBBB747148C08F1F7ULL, 0x7DDBC397765614DCULL, 
            0xDC9DCE16B855EA5EULL, 0xDF63C249BBA41FFEULL, 0xE6FFF9A6C969661BULL, 0x9CB6E5F62EA2320CULL, 
            0x4E1E0803E70E1354ULL, 0x843872402EE6A815ULL, 0x85609C223306171BULL, 0xA8CFB23FE4DAAB2AULL, 
            0x9CAB29CE2913D531ULL, 0x04183E374EF9F009ULL, 0xF89EECADCD96D53BULL, 0x3D2F6FCA0AC7AB17ULL, 
            0x5B6814C2180B9729ULL, 0xFC57900B9A9B6B76ULL, 0x90749B28B244E51BULL, 0xDC54CA33B76399A0ULL, 
            0x79D7ADDADF4750ECULL, 0x38E36A472302EDEAULL, 0x7E909680264E954AULL, 0x8BF004C826A46E59ULL, 
            0xE9EAC3647E49E472ULL, 0xE3FEAA73F5AB5DF9ULL, 0xEDEAF98212754A93ULL, 0xCE31F4E5D4CDA560ULL
        },
        {
            0xCD4B37EEF65FD0B6ULL, 0x3481D4294972C106ULL, 0xFAFA4FEE6EADAD77ULL, 0xBD10DD5812433CEEULL, 
            0x31762D11CACF99D9ULL, 0x5A07070A44DE2405ULL, 0x5A20FC3A277F31A7ULL, 0x53B4D7FC7AE6DD36ULL, 
            0x486DF5137A649E3BULL, 0x01F7FF63A58A2D71ULL, 0xEB0D7DA0DBB925F3ULL, 0xC5A79D05682EF9ABULL, 
            0xF152A7D341FE8ECDULL, 0x6AD07FB38DD03B53ULL, 0xF9430FF122A11213ULL, 0xBDFC4B79D5139964ULL, 
            0x0A5821AFFC927C03ULL, 0x4A575896EA1350C9ULL, 0x22D5223BABE105FAULL, 0x52780A23CAD0D0BCULL, 
            0x833EAC687EAC5175ULL, 0xE03A9B0A34B40396ULL, 0x2EA8271F6CB83D44ULL, 0x293D6FA03ED7AB90ULL, 
            0xE6CA182B10214AD4ULL, 0x1803B5B477B7E6C9ULL, 0x3EF08626C50B9DBBULL, 0xF5A8696B6E81C110ULL, 
            0x6DD82F72B0F62C64ULL, 0xEEF8F3E6AFA19CF3ULL, 0x49574C4D01738A3DULL, 0xA6D8BB77E9F022F8ULL
        }
    },
    {
        {
            0xAE965B66BCC1AE69ULL, 0xCBB01F90C7395AF4ULL, 0xA3689E05DA46D13BULL, 0x24D48FFFB32C4B2DULL, 
            0x8CFE3CBBA4B562B8ULL, 0xD58BC2631C3B4FB7ULL, 0x103D67F8859702F3ULL, 0x6B3345537BA268C7ULL, 
            0xF02755D646689158ULL, 0x1E05B1A1A0775C17ULL, 0x911EBD7D7B54CDD4ULL, 0xE956291C878CA8E4ULL, 
            0x6ADCAF60F46B5522ULL, 0x4AC4D755FE38B6BDULL, 0x3FAD774BF51F9BEBULL, 0x7CE3DCEB9F4DEB0DULL, 
            0x12963CE1060AAE07ULL, 0x03AD16E53892F7D3ULL, 0x82A31708784CDDE0ULL, 0x68E428B6BEF444CEULL, 
            0xD0E30ACCF0B3FCBBULL, 0x87B1EB62633A5BE8ULL, 0x1F0670670525BF3EULL, 0x24FB1A057E9327D9ULL, 
            0x5901349A729D592FULL, 0x0647B1D22AAE691FULL, 0xF979FEB80FA634FAULL, 0x6B53161DDB904A33ULL, 
            0x3060458431D0DA43ULL, 0xBB32F0234CE9380AULL, 0x521D6ED92D98BED3ULL, 0x1E7103534D9A6935ULL
        },
        {
            0xCADD32F29E6A07D1ULL, 0x102256BCA1261B8AULL, 0x1F68883FEBD2FDC0ULL, 0x56711B508493CF3BULL, 
            0x114701D0D0EAE286ULL, 0x70EF2CD6D74ABDEAULL, 0xDE8C5DCB68E6E422ULL, 0x7086B13A3DDFDBECULL, 
            0x144BE5F62D7F59E4ULL, 0x71BE9D21372F8C71ULL, 0x2B9127D406348782ULL, 0xCE7FE032989224C2ULL, 
            0x371A77934D4A52EAULL, 0xB90ECEE8A3C98043ULL, 0x585F4CDADF62A602ULL, 0x8EE2484F53C91C1FULL, 
            0x0E2FCE4C71A6A18AULL, 0x39075171AD864A03ULL, 0x643E8C2A0DA52F1EULL, 0x3518EEE5949FC7E9ULL, 
            0x4FF0AE7D345EADE3ULL, 0xD529A5F027D56C53ULL, 0x97B621A00F08D638ULL, 0x112820CC368D492EULL, 
            0xB04D1A57579F4799ULL, 0x92B6318CC7F28F1AULL, 0xB4AF854CBD228D7AULL, 0xC40A95A119881A4EULL, 
            0xB96D97598A52EE73ULL, 0x894AB6FCB543ADF3ULL, 0x5659751D18E4063EULL, 0xC80E1E71D3F91004ULL
        },
        {
            0x1D4B7C6BA7752E54ULL, 0xA92729A7D39AAD66ULL, 0xDCAC562EAC887094ULL, 0x61340DA579070CABULL, 
            0x25E86F78BEFDF994ULL, 0x4E2DB73F8CAF9F5CULL, 0x1FAE7EC2FEAD45B6ULL, 0xD9AD0CE84F54AD23ULL, 
            0x54B62DF90191E43AULL, 0x772D85E8CC94B0DAULL, 0xD9900A55F2369C46ULL, 0x745A2B37773CBF4EULL, 
            0x822B650CDAA800EEULL, 0x2945BBEE81B5EDCCULL, 0x81A3E47C8329F982ULL, 0xA05CADB981D9A921ULL, 
            0x1CEFA14089903867ULL, 0x3FCB754D068987ABULL, 0xCE77C005B580C898ULL, 0x61A19A55E1F10512ULL, 
            0x4683858D1F080F3EULL, 0xFB39223F1019D5BCULL, 0xBE81EAB896D6E7D2ULL, 0x51A3161ADFFFF5F2ULL, 
            0x85B75C7F7B90BAEDULL, 0x1EFC8B507668DFD2ULL, 0x8485DDBB2CC00AEAULL, 0x41E19245F35A65DAULL, 
            0xFE328771A2285800ULL, 0xA5B34FCA89295F07ULL, 0x7B284D111E7CFB2AULL, 0x0044605487559C32ULL
        },
        {
            0xFF0FC2EEFE991E45ULL, 0x9335E4C6C21A6D73ULL, 0xD405C7904AA610CBULL, 0x1A69DC15E18CCA09ULL, 
            0xFD5A1ACDFD16DA2AULL, 0x1461BB0BCCB3F8EDULL, 0x9DB447206C595412ULL, 0xABD9551B3B0AEDECULL, 
            0xCA460F3F5141B59EULL, 0x012C9CEF3C722FBAULL, 0xB8A8ACD43C1D6F7EULL, 0x94E9137531C0AF35ULL, 
            0x686308BBC2D3B1D1ULL, 0x2E1F8BAA4C682A93ULL, 0x729BBEA8E8187BECULL, 0x7C5675CA394F5891ULL, 
            0x148FFAC70CFF83B0ULL, 0xAB5A8248121557A2ULL, 0x6191D2FDDEE1AF6EULL, 0xEDB116803A2991D9ULL, 
            0x0BDE936E3137DC5BULL, 0x0BDAC1506DF9FAD7ULL, 0x65A73607C399CC0CULL, 0x53F794446FA66167ULL, 
            0x90BFEC50C2FD37EFULL, 0x633A8050616FA2BBULL, 0xF0877DAD138C0484ULL, 0x57EE6C0666106088ULL, 
            0x9A4BA002DACA0590ULL, 0x6A6E8B5936629B95ULL, 0xD4C47020327B7975ULL, 0x593EA82A84B23255ULL
        },
        {
            0xE9C55F08DCB18AF5ULL, 0x3BDAF4497C4C655AULL, 0xCF03CCD20A507E70ULL, 0xF5C6B0BA14DB46D5ULL, 
            0x6F7FBAC9A6AADB57ULL, 0x13E5FEDCB1B3FFA2ULL, 0x994AF2094CACD5CDULL, 0x60D776AFF6202BB3ULL, 
            0xE2FB32ABF9FC1ECDULL, 0xC8F28B3C1790CF96ULL, 0x46363DF7376EAEC8ULL, 0xAC2DA660481D6522ULL, 
            0x6A1E231F2E6440CEULL, 0x7F36BE87DA7F9554ULL, 0xC9EFABF79D176301ULL, 0x1F268C9E71F7D44FULL, 
            0x1D82BF98F48D6995ULL, 0xCEDBCD7316882804ULL, 0x53C0F0A8CA269F5FULL, 0xD2D7532EAC88F140ULL, 
            0xCA5996E83D3847D3ULL, 0x364B0025A1264608ULL, 0x53E3C4639FB9114FULL, 0xE421B5CD0F733293ULL, 
            0xCEEF961F26F79824ULL, 0x1C1B938F381EACB1ULL, 0x00367BD4E5D0119EULL, 0x7C8F1759B36BC80BULL, 
            0xD1B45ABA6C5E76BCULL, 0x4E0C527535DD1E85ULL, 0x3E6245AC4E29502AULL, 0xB0C5D2161B220E70ULL
        },
        {
            0x0E03B2533EAB67C4ULL, 0x1F2121E1C3B3867AULL, 0xCC07B0605CEDF0AAULL, 0x07013FEEEE950944ULL, 
            0x69EF061E41475818ULL, 0xA1A0A71BC8081B53ULL, 0x4820BADE132742C8ULL, 0x1F4C13B66C7B72B5ULL, 
            0x08110895A505157DULL, 0xFB28EB3E4023F0C9ULL, 0xBDE09C3C43996D8BULL, 0x4CA3B170C6111E01ULL, 
            0x661C746797271FF7ULL, 0x3A5F6E9C67B40A02ULL, 0x0E63CD72BB1F5C7CULL, 0xEE940A9133F00335ULL, 
            0xC8293F106091895CULL, 0x112B3AC66668FA31ULL, 0x6AD1D3BEB82B41DFULL, 0xDF49F0135A8C17D8ULL, 
            0x60682F182CFAF9D9ULL, 0xBC539FD0F3A8C510ULL, 0xF97C8E2193F3B8C9ULL, 0x2728FB3774A123C5ULL, 
            0x0ADABF251CEC13A5ULL, 0xFC928AA577771B73ULL, 0x0A5675CA10209F36ULL, 0xB9F930C82D7491ABULL, 
            0xDFFEE8A2909BE488ULL, 0x15536596125E3DD6ULL, 0x4AF2BBC8231C604EULL, 0xDC257194814DA00FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseEConstants = {
    0x3531919C6DAA1DFBULL,
    0x9E43C434A3033C8DULL,
    0x873EAC9E744CBBB8ULL,
    0x3531919C6DAA1DFBULL,
    0x9E43C434A3033C8DULL,
    0x873EAC9E744CBBB8ULL,
    0x89CC54B28085AE37ULL,
    0x3E9EBA47A3CCCBD4ULL,
    0x63,
    0x4D,
    0xC2,
    0x81,
    0x8D,
    0xA3,
    0xEA,
    0x35
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseFSalts = {
    {
        {
            0x898A12459061A8D0ULL, 0x46E411121EB25415ULL, 0xF7D50B578974F932ULL, 0xF156874D4D5095E7ULL, 
            0x115F878CD5FBE4A2ULL, 0xB149EFEEB447CBB4ULL, 0xFCB4F27071784C3CULL, 0x312DD2C5B47AF0EDULL, 
            0x6E5808792417DBF2ULL, 0x6833935BD89B4F64ULL, 0xFAED7BB64FE165F7ULL, 0xB37A648413A9859BULL, 
            0xD2C010D193B4C561ULL, 0x17FE9BE37E99DC7BULL, 0x6001BABDA5E1ED81ULL, 0xA470A9453236D3A2ULL, 
            0xDB78D80896B5D123ULL, 0x01EC93E8A451B6BFULL, 0xC84F92A7F8C6550EULL, 0xEE0557351DE51D5BULL, 
            0xCCC48A1834463E43ULL, 0x96F7657C49EFE412ULL, 0x68BB4C53665477CEULL, 0xFB174AE63BE7AFFDULL, 
            0x792FB135517D8096ULL, 0x9314508EFD038301ULL, 0xEF7A45008D9E7225ULL, 0xCAA83DD835157703ULL, 
            0x7BFDC83BCCB04235ULL, 0x5320AC9F3DB89D16ULL, 0x3189A1E6FB716ECAULL, 0x102C247440240574ULL
        },
        {
            0xD1A04499411EC8CBULL, 0x807E8E81BF773F3FULL, 0x5BC1FFFC7FBB9B13ULL, 0x933B83F9256B25F6ULL, 
            0x1532F662EE5C354BULL, 0x3C5E59451E777697ULL, 0x5747E98B488CBEB5ULL, 0x71DEA9E655D628E8ULL, 
            0x9F865FB351B52C7EULL, 0x917D975E770B7EA9ULL, 0xD14ADF6C63E95168ULL, 0x2F749312C2562B38ULL, 
            0xD9D21B90BBF8E5E9ULL, 0x6773520B1159B851ULL, 0x6DBDDE099DC34D5DULL, 0x45EB1E7BEF71E7C1ULL, 
            0x8BEAB53570E1744AULL, 0x908CBCC2AEBD017BULL, 0x50B3B3773D5B08C8ULL, 0x358D65597C4682F3ULL, 
            0x89DFF7BE2A19DE1DULL, 0x221CF89B89AF63AFULL, 0x970F822ED5943F72ULL, 0x3C243CAC121D5718ULL, 
            0x8C46D7B1D6EC14A5ULL, 0x80A398C88C09B0DDULL, 0x3DBAB616AD162CFDULL, 0x33193369395E777DULL, 
            0x677B2D4D94F6C893ULL, 0xCF739AC71157F139ULL, 0x71FD9278AA18224CULL, 0x26DDDA09B63279F5ULL
        },
        {
            0x02495522290CEE9DULL, 0x16B0A0195F9EE6ACULL, 0xA20CFADF75AE02B7ULL, 0x503B5A5C45275E03ULL, 
            0x91E5CECFC489E76CULL, 0x3E08355DA14C135DULL, 0x1120794855304DA3ULL, 0xB01C34FC69435ECEULL, 
            0xBA79827FC8D2B70BULL, 0x316482B3BB96F2C8ULL, 0x139897CF00CAF9B3ULL, 0x4BB196AA040CC199ULL, 
            0xE30B83DE1841CA88ULL, 0xF0206FF5C78DA7BEULL, 0xD2A8E10C988E8F2CULL, 0xE5FCC8EFC516055DULL, 
            0x88AA7246442B708CULL, 0xD3642F6C5AA9E37DULL, 0xE66A28CC75EE23AEULL, 0x4BEAA1C7C408F7FBULL, 
            0x03B95F064796CB63ULL, 0x65A6222A14B0BD14ULL, 0xD002999E0A8F307FULL, 0xE6CE9C237CC3DAE1ULL, 
            0x1DF7FDCFBFE79412ULL, 0xC593823F88F4E2B8ULL, 0xCA484D96BF6FD041ULL, 0x523EF6DF1EA669A5ULL, 
            0x76A2B4C271CF895DULL, 0x0A1D9F6C5E483DA4ULL, 0x8324EBF6AFE8C833ULL, 0xFB7DBC3236CAF27EULL
        },
        {
            0x7B9AAB9C90664842ULL, 0xE01579A439F7A60DULL, 0xE2EAAFF87EE3C7D6ULL, 0x5074D60482395FAFULL, 
            0x6B17C9C99E7DD136ULL, 0xB22AB14364BCAB35ULL, 0x5CF097A19FAED1DFULL, 0x1DCC2B690BE28ED1ULL, 
            0xF5C260797B800223ULL, 0x4625D025C6CEAD4EULL, 0xD0E2DA5277C31158ULL, 0x5B5E3BDFF0301213ULL, 
            0x78C3A7706B7996B2ULL, 0x6B6C0E5191AC0CB3ULL, 0xBB719C2529520842ULL, 0xB68F81BA19B69056ULL, 
            0xF9738C499A358A36ULL, 0x27D732E4B9B99180ULL, 0x34BFEB90F7118DEFULL, 0xF84B6CB89498ED82ULL, 
            0x85FEEB80B5BA5AB3ULL, 0xF80C938068CDAAABULL, 0x3B3D531A3D298CA7ULL, 0x3E371DC1CDEE3EAFULL, 
            0x00B2A39BC14F529BULL, 0xB8DF53CCFA920D25ULL, 0xE3539845A81B8162ULL, 0x051E0A57A939B34DULL, 
            0x86C5014CEA5A7BB4ULL, 0x1373CA9D6F4C0B65ULL, 0x29957C96C426B2D4ULL, 0x6D131E71C4654456ULL
        },
        {
            0x1B4F3429FC91C98DULL, 0x2CC857DE2EEDDCCDULL, 0x7A0B2842698AAD5DULL, 0x1A86B68607974617ULL, 
            0x44D9BB20318127E5ULL, 0xC286C98B2622A592ULL, 0x6C5C2BE1FAAD8E68ULL, 0x15C1BDB98DCC0EE4ULL, 
            0x75B8B3E843347FF0ULL, 0xDBEC8B8835FF2CF4ULL, 0xF26236917C066155ULL, 0x41D03E3AD222C6BFULL, 
            0x73F85AB4EEBBDEEBULL, 0x621E58CFE4D48F45ULL, 0x00983F5487B1BDB0ULL, 0x191935C5CC95F508ULL, 
            0xB1E4AAF34ED7F479ULL, 0x1CB669C91F29B7A9ULL, 0x0011477AE891D895ULL, 0xB450AFFCB43F200AULL, 
            0x19B0061CBCAB1AF5ULL, 0x3102544374D39BDAULL, 0x3D7258C38D300D9BULL, 0xEC8F0436071C30A1ULL, 
            0xADD1BD43237B2A83ULL, 0x87660F817A4FDB34ULL, 0x0D4367B312AA8215ULL, 0xF9663944D1F1E2B6ULL, 
            0x4C8A8724925F345CULL, 0x42553E3DCAD9BF6FULL, 0x2C3DCA30AF980A29ULL, 0xC0EB7416B44325B9ULL
        },
        {
            0x6BAD8D7783B681B3ULL, 0xF57C9655CDEFD0AEULL, 0x2B3CF9190359C9E1ULL, 0x4DB75C6342F39350ULL, 
            0xE2DF241BBA3EF370ULL, 0xFAD4FB8E3AD8E176ULL, 0x5780F399155BB7E5ULL, 0x0CCAEFE3827684EFULL, 
            0x7BF3D7423F7DEBE1ULL, 0x4811EE4EE661D777ULL, 0x21B864668BDCB383ULL, 0x645A962AD32CB5E3ULL, 
            0x51ECA80013AEDDA3ULL, 0x99A41FA747FE3CECULL, 0xD559F44F0634CF2EULL, 0x65B16D6BDF5F4406ULL, 
            0xAD7D3F0FE1C72273ULL, 0x7E77131A8A9513D6ULL, 0x62A1F2384D734A06ULL, 0xB4D164013C2A4503ULL, 
            0xB4D7B20FA64FFC15ULL, 0xE07300FE8DEBE719ULL, 0x4CF02944D67D4AC8ULL, 0xEE915AF57338A0D9ULL, 
            0x4F971590716A3081ULL, 0x2E063BB377D09B65ULL, 0xF985EFA2DF3E17E0ULL, 0xF4747DAC0159E183ULL, 
            0x55158C6FDE54BC3BULL, 0x475F04ECF6440DABULL, 0xB6E666C44DC971FFULL, 0x61C12ED887D887E9ULL
        }
    },
    {
        {
            0x92248FE3B31705F6ULL, 0x3EC57A6807EBD89AULL, 0xA62430C8837A1D80ULL, 0x296EAB4E58B38A50ULL, 
            0x6C481D9C0E7A17CBULL, 0x349D0088CEF43481ULL, 0x831409BEE75AD2C5ULL, 0x50BECBDAE1EF8AA2ULL, 
            0x6ADFF7DF716523DFULL, 0xE6D1B58051A2C917ULL, 0x0375381A8402DCD4ULL, 0x785D0D1208A6B083ULL, 
            0x7B1EE4D6ADAC9D40ULL, 0xBCA7DF235BC096BEULL, 0xA67CE26A1E58FDA0ULL, 0x10858EB017830219ULL, 
            0x4A007F85A1E03804ULL, 0xC769FE7E0A123D28ULL, 0xC8B5FFB7EDB839C7ULL, 0xBAA419EEF7B5EBE2ULL, 
            0xF66A0C7FAD10BADAULL, 0x623EBE445DD67E07ULL, 0xEF592B1FA1F679BFULL, 0x4C0572634F7652C1ULL, 
            0xFAB0AD17F51DAA3FULL, 0xCD55A7921AC93A1BULL, 0x7FE9F6F9CF9701F1ULL, 0xC88A985711D33F3CULL, 
            0x127BA3A28DCC73F7ULL, 0x200BDBC3E4679A4FULL, 0xE8B4C3895CB0AFD1ULL, 0x117CF6B105067764ULL
        },
        {
            0xA386A6D2730C04B0ULL, 0x25451DC624BEB566ULL, 0x4469953B46091033ULL, 0x8A2E74E888720196ULL, 
            0x9A90F8EA1B05C3A2ULL, 0xFBDBDCAD6A2EA921ULL, 0x236028D62A01953DULL, 0x70678216D632D6FCULL, 
            0xB28D84B3A25A2204ULL, 0x1AE12C2CFB5D6CA3ULL, 0x812B27785075BC1BULL, 0x3544C0D7840EED41ULL, 
            0x5866D2D0A998C22BULL, 0x6028265F4B07C603ULL, 0x9695B28A52B43B22ULL, 0x558309E93C479B56ULL, 
            0x6A684C39CF54A457ULL, 0xCFCCE945CFB42EC0ULL, 0x3B024A85E6D1B2A6ULL, 0x9F931B19BB23A797ULL, 
            0x278577E8E4DDF9D4ULL, 0x3272D86FD6D14F65ULL, 0xBE6232B62213955CULL, 0xC7F040F5664F7518ULL, 
            0xF1A553CE7767C5D0ULL, 0x02A9F631023CC9EAULL, 0x0567660F452535DCULL, 0x898B65E20A58AF83ULL, 
            0x8E188F7051FF4183ULL, 0x4B1A4CA4F58CC77AULL, 0x244E26C0BFD9859EULL, 0x9B9CFBDA7217B6BAULL
        },
        {
            0x3F5AFEF3D3E14DFCULL, 0xCF657A34709C88E0ULL, 0xC1ABF35EBAA04C6AULL, 0xB4D89128E194C9D8ULL, 
            0xFE20A6FB6B35A635ULL, 0x3767286C7C6BBD63ULL, 0x2A395D7027E2266FULL, 0x7B5DCFB8F50F5744ULL, 
            0x70897C713D8A0F69ULL, 0x6DBF689C10FF2304ULL, 0x676089A4B302B5FEULL, 0x70A2050C152E6052ULL, 
            0xDFAD9465EA6F8075ULL, 0x2698FFBD6472A662ULL, 0x138CC5A0F7C08D9EULL, 0xD3F5ED58D15DD8FBULL, 
            0x918EBC2C6AD45416ULL, 0x95942FF59E884B58ULL, 0xB69B88A0B062B012ULL, 0x3D69E501796131C9ULL, 
            0x0349E8225BB5532DULL, 0x1F4750FF0F9C6E87ULL, 0x9AE00A160B17B472ULL, 0x7892FFD27222C8A7ULL, 
            0xD6D5EDFF970787A2ULL, 0x78F0345E53DA4769ULL, 0x43361F43F5F88487ULL, 0xE1D17E0F15F0C255ULL, 
            0x378A7F2B20ED5A65ULL, 0x55746D91CC55FCB7ULL, 0xA529B3E01639F4ADULL, 0x0E20EBD18A7EE46AULL
        },
        {
            0x9B93A3FB5ED9EB82ULL, 0x97760D2E43DB2E74ULL, 0x6086744B0A64F607ULL, 0xB45DD52F218936B9ULL, 
            0x8A032A37D2409F9EULL, 0xB092ED9DDF99CEB8ULL, 0x9C4D59DE887E9EEBULL, 0x753048C9AE857A41ULL, 
            0x62FB4D2F3F7E5EBDULL, 0x81FED72C3B162418ULL, 0xF5BCDFCBB9B66D85ULL, 0x80186BB5D2E01530ULL, 
            0xB6F095EA094C735DULL, 0xA0C13DC30E3136B0ULL, 0x03963B8227A0E120ULL, 0xA5FBB08FD5525DBAULL, 
            0x2B471BA30575B121ULL, 0x9878CC16E349B64EULL, 0xE21B0F179CACA0A0ULL, 0x2A5AFEA5A7FB9D5FULL, 
            0xC8CBB73568BE92A1ULL, 0xCA6E3F066DF4E45CULL, 0x29D30FF6E6264B3FULL, 0x0C4A91CA6594CF10ULL, 
            0x1169064F43E26458ULL, 0x68AB47A20EEEB58FULL, 0x9502F671CDD0E0EFULL, 0xD12972AE3BBE59B6ULL, 
            0xC45D7AB03ED1DCECULL, 0xB5E46C4502D13A28ULL, 0xEE6E998EDD26E862ULL, 0xA8B2F0B9D427AD65ULL
        },
        {
            0x03385BD4AED614FAULL, 0x60671A2068D3F573ULL, 0xBE128AA130F96A4BULL, 0x396B979E6A33B769ULL, 
            0xC1092345681157D8ULL, 0xDA978A26E72BDFCCULL, 0x5844F9B2387AE341ULL, 0x41C25293DE4ACF68ULL, 
            0xEA4E57CC22C5EF19ULL, 0x5BABBE3D96260FFCULL, 0x38F361DC0B0DD8B0ULL, 0x65EE6E65CE0F6753ULL, 
            0x57A4503AEB3833FCULL, 0x4970D9F388CAEA62ULL, 0xC87D3FB586446388ULL, 0xF63B967F461F91A9ULL, 
            0xE872277EBE6DEBD4ULL, 0x9F5F881D44DFED58ULL, 0x44AA2C1C575CE3E4ULL, 0x7EC006881B208FE0ULL, 
            0xC65598512E39DE09ULL, 0x3AF2732CB419DE4AULL, 0x5CE33B94B39FBA3CULL, 0xD160C407018D23B4ULL, 
            0x10BF991BAB45217EULL, 0xB030CCC185E2BBB7ULL, 0xCA43CB42F41685EAULL, 0xFB841D42D7C01CFAULL, 
            0xEFAD02006DAC7D61ULL, 0x95418BCECDEDC25BULL, 0x7CE9224676D67839ULL, 0x9FF9A532D8C9DC19ULL
        },
        {
            0xD3BBEB132F8DBB0AULL, 0xE0E1F67013EA5E03ULL, 0x8046E850A62D62CEULL, 0x7D17C4E211C0E6D9ULL, 
            0x42557DBE2B929E49ULL, 0x1FEBDF4C99798E2CULL, 0xC5F33C266D25F777ULL, 0x889B96050DE32868ULL, 
            0x81E6F765757F2334ULL, 0x88979BC610325D55ULL, 0x3E864676535A4237ULL, 0x02DABD392E302A31ULL, 
            0x0C1344336A4518DDULL, 0xEB85890153FC1A5CULL, 0x5175C9C3911F955AULL, 0xDB0C5BBEA769F8D6ULL, 
            0x4A7AE95D522EDE50ULL, 0x8B466503B4D1A5F8ULL, 0x307C59D0300CD673ULL, 0x471546CFE8D46A0EULL, 
            0xCB9DE32C925340FDULL, 0x2E213FF4D8CF706EULL, 0xFA84CC0EAA67125AULL, 0xBBA20714C0DD5CE6ULL, 
            0xDE91D3162F56D9FDULL, 0x95C831BA4B939668ULL, 0xDAD686C4EB7706F5ULL, 0x38F3A6F0D75D0585ULL, 
            0x1A94D4E69D6A47A7ULL, 0xF86CC7077AF3A8CCULL, 0x7BE7425A3EAE82CFULL, 0xF022367DCA67A5FEULL
        }
    },
    {
        {
            0xB5379E5B6AC0D5B3ULL, 0x870429BC25047541ULL, 0x3968C7D46FA696E2ULL, 0x214F289318BE89BFULL, 
            0x6639B99DFC960699ULL, 0x2FC4D28115BBD512ULL, 0x7855DAEDFD7D15EFULL, 0x3280CDFDBF571E6BULL, 
            0x3A0880D7576B1229ULL, 0x23B307F424552CAFULL, 0x4A8C2EACA8FD4AF0ULL, 0x8CEB7CB9EF184CA1ULL, 
            0xA595EA332A0D2D44ULL, 0xB722AF3F2F0C7B9FULL, 0x8CB6F4F649B2AD52ULL, 0x1304773B747EDE49ULL, 
            0x8ADFD6B7D5C95BF8ULL, 0x12A81904457BD9C4ULL, 0x619D47152D2C5A38ULL, 0x6C844D44FF4B14C5ULL, 
            0xAEFFBFA6D1E842F0ULL, 0xB0DB1A4A97C6894AULL, 0x4740F4D91613949BULL, 0x2C88A3F30EA1EFC3ULL, 
            0xCE57521365E84206ULL, 0x3B3C62FDDF83B753ULL, 0xDFDFA955C7EB1D9FULL, 0xF5F9C6F053CFEF2CULL, 
            0xF322468F19479875ULL, 0x0086C97272B44F67ULL, 0x9C88678D9A2BEB45ULL, 0x5DA6DC2808DEE652ULL
        },
        {
            0x5003D596AE56A1C9ULL, 0x811455689A1A7314ULL, 0xB7B4EDC2A1A00C34ULL, 0xB1E50AE3B8CE75D8ULL, 
            0x6ED84A9F6C6E56A7ULL, 0xE6FBDE8323099284ULL, 0xA4A98A3003C84FABULL, 0x00ECB1EA5FF5C5B0ULL, 
            0xADB0CBA657E9EE19ULL, 0x28BFD9D612ACED24ULL, 0x32ACBA2B5F338A9DULL, 0xF79C1C653E540C0AULL, 
            0x4AF482458C43AF8AULL, 0xA344DFC7DAB6A20FULL, 0x1DBE02BAF68B5238ULL, 0x2576D9D5D84AE835ULL, 
            0xDBFB2329B83AD832ULL, 0x920BD56740D98284ULL, 0x5298E34FC2B4D8FEULL, 0xEE0DDB59E5CFBAB6ULL, 
            0x8C046B4BF613C952ULL, 0xE16E097607CE563FULL, 0x87A5336BA7B14A18ULL, 0x0FF34F752B09DFB0ULL, 
            0xFF88A619A0EA114BULL, 0x46688DD48ED3FB25ULL, 0x5B596C30490C75C0ULL, 0x5AEE679B06755BC7ULL, 
            0xC4A22CF4BCF21953ULL, 0xCE7335070AE24009ULL, 0x5A73F697C7A0E4BDULL, 0x551BEB093F7B3394ULL
        },
        {
            0x33309F62C57ADA21ULL, 0x9FD108B987C668FEULL, 0x4BCB0F035269C709ULL, 0x92D59B9B41A643A1ULL, 
            0x799214C868C7C169ULL, 0x7801347C4BB914CAULL, 0x0A07D13FD90DE84FULL, 0x19499E3067F495C5ULL, 
            0xF057C626903D75E0ULL, 0x8608AFF52B8CAF45ULL, 0x45921B42E6372854ULL, 0x21DB31295D0AFC79ULL, 
            0xCD71F739AE1D7485ULL, 0x54943F69A39217D2ULL, 0xDDF7A0F0787D500CULL, 0x0A0D85853088B189ULL, 
            0xACF8E77DE0BF2E82ULL, 0x0694094010C77001ULL, 0x7EE595D5725A48FBULL, 0x0ACDBB32FEFE2B38ULL, 
            0xC089653F096B6F15ULL, 0x6437717AF116BD7AULL, 0xB5B6B06066761B5EULL, 0xE6D63DC87E4517CDULL, 
            0xB726FF067D477E2DULL, 0xB7446F2981404716ULL, 0xFE11DB06B9ADA68AULL, 0x014171CAEF259D71ULL, 
            0x69864F6960F4CBB3ULL, 0xD5C328CB4E5AA28AULL, 0x21B8DBAC1D98873BULL, 0x6CC50922B36877D3ULL
        },
        {
            0xB49BC9AB86CBF716ULL, 0x1CAD937362DFFF6BULL, 0x98FD078E0211334CULL, 0xE8A41A7A2B0A84D8ULL, 
            0x82FF95E62F41046AULL, 0x8AEF49622B3AA6E2ULL, 0xD6B6978E7E927C5AULL, 0x335EA4D6D35E685FULL, 
            0x105E7E855ED9D8F3ULL, 0x4DE9849B07B8A5FDULL, 0xAD50DF633CC4B5D3ULL, 0x329902E5676566E9ULL, 
            0x4051EFA0DD54809EULL, 0x10CBF0A264F4B1B5ULL, 0x277B75C4F61ABBC0ULL, 0x082ADDB88198309FULL, 
            0xBA5316A7D6108DC9ULL, 0x18DF3A6D7488FA24ULL, 0x8EB637E89752AFECULL, 0xCF50F61E8EC9CA03ULL, 
            0x4052AC561F34F728ULL, 0x466248D086400E40ULL, 0xC9FF0E2E14680C7DULL, 0xB49E1C01546728FBULL, 
            0xE3ED68D79F00AE49ULL, 0xAE100AA1027794F3ULL, 0x11E8DF639060CEAFULL, 0xCC342B2BE81FC0CFULL, 
            0xFCDE473EE354CC68ULL, 0x39E8BFB23488BD39ULL, 0x7C26EB7F55C1A853ULL, 0xC1261DFE276C756BULL
        },
        {
            0x3ED4861AA75F0F6FULL, 0x9D8918B2DE974376ULL, 0xCBA1F15BAB5AB465ULL, 0x42CCD3155E44DE24ULL, 
            0xA89273B97EC7EB45ULL, 0x2BE6F8CFF83C9BAEULL, 0x6CA9303A522FE885ULL, 0xCB9638D885F4F21DULL, 
            0xEEB2FA19B02A0E1EULL, 0x23BE8AAED3983640ULL, 0xFE87794E1242C597ULL, 0x13209369826CFAD9ULL, 
            0x70BBB7BAC7033246ULL, 0x41781AD0824361E7ULL, 0xC4388C7F63938E9EULL, 0x2A81FB08699C83A5ULL, 
            0x8DA4F90D1AA3EB79ULL, 0xEB3723875B0439CDULL, 0x66DD9F69964ADE98ULL, 0x8C526F54D7376B2CULL, 
            0x491494F20F5E74F7ULL, 0xD79F5EB23F8BEA2DULL, 0x01BF7E6BAFDC1D19ULL, 0xA5D01BFC557BE792ULL, 
            0x1B1F97A753841E16ULL, 0x3D5048DAB336CDC3ULL, 0x6556EFE36326D953ULL, 0x5CA6F6603041083FULL, 
            0x2DC5D5BC92371269ULL, 0xF56F980D8C6BBD92ULL, 0x956939A1EFE7F539ULL, 0x026B42A396A7DCE7ULL
        },
        {
            0xCBCB9B6E20B08589ULL, 0x6A0BA4B27A0093FAULL, 0x687736FD51C815B5ULL, 0x1CA3E2EF9137E2E0ULL, 
            0xE4BCEE0AF49DD55BULL, 0x7D26F5A254EE7A10ULL, 0xB9313E4D4D2ABEACULL, 0xDD6895D3ED9E0D2BULL, 
            0x17C44036D536738FULL, 0xAEC978CA54B1667DULL, 0x7FBEBB7728636386ULL, 0x6D563111329CFDC3ULL, 
            0x45CD3B787C4B2AABULL, 0x8CDBDB3CB5AA7A16ULL, 0xB4C30BCC5211E1D5ULL, 0x4F55D627B594A2A9ULL, 
            0xD38D84F46433EE9AULL, 0xB15E45AE6BCE9A87ULL, 0xADE10010FBA4F71DULL, 0x23E314F1C1B88FA6ULL, 
            0x290D2599C4454331ULL, 0xD1E58E76A8822CB9ULL, 0x8E6AC25ED7ED7E14ULL, 0x449A605926EF5082ULL, 
            0xE5EBCEE8F56ED92EULL, 0x2C0F3CADFC75EDFFULL, 0x88BC93AC7029BEB4ULL, 0x954CDDEB6B06C9BAULL, 
            0xFD2D8F42CD5B7D23ULL, 0x7FA388AD96383776ULL, 0xC4031B78B34DB545ULL, 0xBB30B5F4C6279089ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseFConstants = {
    0xB07DE155DB2DDC0DULL,
    0x3939AF651640D1E2ULL,
    0x1439325BB978F230ULL,
    0xB07DE155DB2DDC0DULL,
    0x3939AF651640D1E2ULL,
    0x1439325BB978F230ULL,
    0xD8A5AB1A720DF2F9ULL,
    0xC2A768C940BCD696ULL,
    0xAD,
    0x10,
    0x03,
    0x66,
    0xCB,
    0x71,
    0x3C,
    0x0E
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseGSalts = {
    {
        {
            0x3644BE2BEC9E7C7DULL, 0xED18D0AB7614A14EULL, 0x010560CB53B78B4BULL, 0x9D7829669BA9383AULL, 
            0x736C9CB6F5837EECULL, 0x6F01EF1BEDAD436EULL, 0x8692B5BCFB9998EDULL, 0xC2C7E573BF36969AULL, 
            0xEA63B9242A1D8397ULL, 0xF9737DB8915E7A08ULL, 0x46BBDE24B4F18F42ULL, 0x4C8A754F3D8CD126ULL, 
            0x36D3B1A65A774811ULL, 0x2C2782A487A83960ULL, 0xF13ED3A87B8BD4BBULL, 0xD2161DB02FA45C13ULL, 
            0x0C0ACAB0A305038BULL, 0xE8244A605E616555ULL, 0xB9BFC2BE276E17A6ULL, 0x3B0C15F789471FC1ULL, 
            0x2DD05496A14987AFULL, 0x2438B967B0824996ULL, 0x64C1E30A5FCDA280ULL, 0xC1D56EBC8B2FF80CULL, 
            0x0E2ADE00B3A303DEULL, 0xD0403B2B1F70CEABULL, 0x19E50810AA428461ULL, 0x28AAB0F83F6D2C07ULL, 
            0xCE783189F8200CA2ULL, 0xBB5631EE1554E7A5ULL, 0x3A18E25F617F9491ULL, 0x3A7037BB83985FEDULL
        },
        {
            0x06A61568EA961E57ULL, 0x17AE98A1A8086977ULL, 0xD9A53A8BF881984EULL, 0xFFCC6C7B271D1089ULL, 
            0xF48F09CB825D14BEULL, 0x2F7B687175D48B3CULL, 0x96DFF8C9FD33F717ULL, 0x318F78A045A88561ULL, 
            0xDE2E7DBCFD4C245BULL, 0x505B0D658A3391D1ULL, 0xA109A2D0EF66AA13ULL, 0x7ABE3D4D3529684EULL, 
            0x060D7044B36CF87CULL, 0xE0623DAB0AE2C8A0ULL, 0xEC4905D523908DC7ULL, 0xEA876E693699313BULL, 
            0x8FD4674AF05F08F7ULL, 0x80261CEA09C07247ULL, 0xB2DB206AC1FB0398ULL, 0x219F08119537E11CULL, 
            0xA36C59084D46FED5ULL, 0x1F8B9E4D89B57A8DULL, 0x2FEFDBC0BAF32C68ULL, 0x2100320DCE04C085ULL, 
            0x3070BCB0218C3380ULL, 0xBD65128C59CF5400ULL, 0xDAAF36CE77B363E2ULL, 0x30EE8205012A8A4DULL, 
            0x66DB80D09F4AFA23ULL, 0xC9E48FD3D9D9D427ULL, 0x1916F9441FB46EF6ULL, 0xF3D665F1C82A6138ULL
        },
        {
            0x45AFDC97DA122ACBULL, 0x2DA876E18E33A26FULL, 0x573043F3190CD1CBULL, 0x492944553CE4E9CCULL, 
            0x0C7668FD5B999629ULL, 0x982C61EAF2A404F1ULL, 0x5D2C24D988F46DDBULL, 0x925DB16D35D45450ULL, 
            0xF87082CBA1BAE571ULL, 0x668730B9DFB7CC9BULL, 0x1ACF03E4B262ED0AULL, 0x7E7400D8D2FCA317ULL, 
            0x9D1F687AA49CD732ULL, 0x48FB9AEE0B56E114ULL, 0x493E0CA39CA16F4CULL, 0xF30B0C4A66D8FC00ULL, 
            0x54EFFC14225FAEF8ULL, 0x27DE663DEE45C12FULL, 0x76FAD72E05572C90ULL, 0x548B575FA4DEA53DULL, 
            0xAA56907A755F398EULL, 0x8332069DC8843EA1ULL, 0xA3E3F64B9549CF48ULL, 0x6A66CD7FDB6CE871ULL, 
            0x4822B76BB6C37E9BULL, 0x6AD5E77A671DA499ULL, 0xF96769812C19DA87ULL, 0x4A21ED7386128DE4ULL, 
            0x1AA59928E282F01CULL, 0x69E3445D4A0E6DAEULL, 0xD67B5E4135B3B49DULL, 0xDAB7D03A66491065ULL
        },
        {
            0x6E5C2920ED5B2554ULL, 0xAB694461B5AA6093ULL, 0x099AB6F55D5F5D41ULL, 0xAD17FFF90CC76C28ULL, 
            0x225CA44376E4E4C0ULL, 0xAE34A050683671DEULL, 0xF820A12F8551DD56ULL, 0xF339AA160E1FAC2CULL, 
            0x5EFDD682FFC41430ULL, 0x192073A36C3CCFEDULL, 0xCAFA158E7552135AULL, 0x560603D27BB5BBE3ULL, 
            0xF35A48191BE3AD3AULL, 0x809609CE4E9C3173ULL, 0xC249EA7EB4916B30ULL, 0x000BF5C21A4797E6ULL, 
            0x1E7320B91D3D659CULL, 0xD5CE4CF96A4F8964ULL, 0x61D344BAD239633FULL, 0x68231EB8B42E342FULL, 
            0xB6AE0292C584BD3FULL, 0xD0655B2785460218ULL, 0x1FC0CFB763653A78ULL, 0xAF8177B2A2DF5EB8ULL, 
            0x00127CB3AD7BBF60ULL, 0x45999AF5E81A45E9ULL, 0xE263E2B70C9A4DC6ULL, 0x7A7BA25D78959B7CULL, 
            0x5867B0E24DF7FCDEULL, 0xF1F8C176C529A664ULL, 0x4DCB9B26694E2395ULL, 0x3069523227C71961ULL
        },
        {
            0x714E2B524CA798B4ULL, 0x0480EA77316A30B4ULL, 0x9B626FEF51F14AC1ULL, 0xE2640E0542E89ADBULL, 
            0xE4959341D1958466ULL, 0x06FFB49AE91A494CULL, 0x60E0B86FB5615E58ULL, 0xA3AC19ABF13E1409ULL, 
            0x55F2193C1BDE7F2EULL, 0x14FEE98552491437ULL, 0x03930CADDF904DC7ULL, 0x460CEC9C93201591ULL, 
            0xAEDD8475A9D0CFE1ULL, 0x0F38C5BF8D7B4909ULL, 0x1D1AD214E25FC22FULL, 0x0765047EE2BB1184ULL, 
            0xA6B14C85ABE5B9ADULL, 0xA2CEBBA853EFFF56ULL, 0xC500964762EF2FE9ULL, 0xBA5CBEB0AF12E169ULL, 
            0x0E85EED1E73DDC86ULL, 0x0E3350CFFA8AD433ULL, 0xB1FB28C25E43F7ABULL, 0x838A1CF75E836A3EULL, 
            0x096136E18E5471ADULL, 0x072EBA10CF7C3D83ULL, 0x379F67980693A688ULL, 0x73438BF797CFF1AEULL, 
            0xB6E970AEFB3CE76AULL, 0x9DEF0F74E1E85760ULL, 0x33376F9AD071B56BULL, 0xD53F089DE1360C95ULL
        },
        {
            0xA2515E02148A0255ULL, 0x75D6069D8149493BULL, 0x2383E381B0136BFAULL, 0x52B07AAF4AAF032EULL, 
            0x4BA4E85F358E5BD7ULL, 0x853AB3E02F8043F4ULL, 0x2933E7CB147A4179ULL, 0x57B1C4E9FC5E4D7FULL, 
            0x6254D7A3ADB50FEFULL, 0x9032BA2A4F20D386ULL, 0x39A4D2D75125F673ULL, 0x50954EB7CD4BAA3CULL, 
            0xC937DE66A419B6A3ULL, 0xCAD0709691ECBFADULL, 0x1FB485AD1A324DAFULL, 0x20CEFB12521EA97BULL, 
            0x11D7EE071E458E35ULL, 0xA3792117E9B44608ULL, 0xBB23616BCDD2ABEFULL, 0x67240A3F35DF5F22ULL, 
            0x9FE00A26B39C9C2CULL, 0x07C576EF46134829ULL, 0x8B488C1D2C764BCCULL, 0x9EF85996C7839F27ULL, 
            0x1692A6574B0855FBULL, 0x38A96390C10BD2FAULL, 0x211781116C44722CULL, 0x5C9BABB1886C6000ULL, 
            0x92A150E10340293DULL, 0xCFE7759FC6E09AACULL, 0xCF569A44E76AF4C2ULL, 0x6C3E36FFFA491111ULL
        }
    },
    {
        {
            0x1FB0D66D9094916BULL, 0xD2ECDA9129BA6860ULL, 0x448D1EDCADC07BC7ULL, 0x916D62FCBA989F28ULL, 
            0xB0AC88C8F3127B5DULL, 0xC5530C936C423954ULL, 0x0A24D1D163F4D789ULL, 0x575D9F0730472C1DULL, 
            0xF0D214794347F44BULL, 0x59DFD74E9CFB76F7ULL, 0xD102790B2EE4A698ULL, 0x05448930F0DF5EB2ULL, 
            0x288B6D406CC07041ULL, 0x58ED6CE491CA749DULL, 0xED4B0BB049F48DA8ULL, 0xBB1D86ACE7F23FD3ULL, 
            0x9E5970BE12C5040FULL, 0xB7868A106BD86ADDULL, 0x81052D6F7F4C32CAULL, 0x523053AC1C6E6895ULL, 
            0x98410E8B7575AA22ULL, 0x76D2C3D529E61C0BULL, 0xCB98F7ABB741D0C7ULL, 0x620C814A93E29FF7ULL, 
            0x9C8766677958CEBBULL, 0x3E3587F8D361F488ULL, 0xF3075C8BFCD2B481ULL, 0x48CD71165F6D20B4ULL, 
            0xB44C91733068E981ULL, 0x40F32E9CE0241DFDULL, 0x238F80D035A355F8ULL, 0xC8FE6AD984079826ULL
        },
        {
            0xFC6AE3292F7955FCULL, 0xCB951A59DEA01DADULL, 0xBE72A9A2164643B8ULL, 0x57B65F1D5811FEBBULL, 
            0x17509F5461CEBEF7ULL, 0x3CB35F5FB7590884ULL, 0x03DAA5A07D03D24BULL, 0xD150FB8B9051EDB7ULL, 
            0xF94B898EA637905AULL, 0xAD212F58F929B703ULL, 0xCC857A4AD1D1FB2FULL, 0xE28B122E06C94BBFULL, 
            0x4D784C3AB65CB44DULL, 0x4D5CB45705FA0D90ULL, 0xE7BB8DE4957E4596ULL, 0x755FBE81F96D05A3ULL, 
            0xC3E6E7A8DEE77914ULL, 0x61FAE0B022E78E65ULL, 0xD7CE58F5DD823884ULL, 0x0D558CD10B6496F0ULL, 
            0x00C5F46B9555B63AULL, 0xABF3F4B787ADB3A5ULL, 0xC3DBC0A987D50DBDULL, 0x50EF317904851BA7ULL, 
            0x8F885012A58A7043ULL, 0xA1B8C9288915F035ULL, 0x0747745825619509ULL, 0xA2749FF38CB433D0ULL, 
            0xD34D0D066EF210D3ULL, 0xFC7C89F6F95A6DD9ULL, 0x318E5825EC86E92EULL, 0x88CA5E56119D7626ULL
        },
        {
            0xA0D511C6EDEF2154ULL, 0x5BB27857FC8C8D46ULL, 0x759F3F38680325FAULL, 0xFB405FB14BB611E1ULL, 
            0xA89B6741AF223CFFULL, 0xFD075FA49B2BA24CULL, 0x71DA026DA1FF5672ULL, 0xDEC527D474435D6DULL, 
            0x1D333D5267E0B053ULL, 0xF43BB01D8A860BBCULL, 0xFCCCCA221B99F7BBULL, 0x0D354510DB4F5446ULL, 
            0xFE8DA34EB2A767E2ULL, 0x0B08AC290B061BE5ULL, 0x7488F68134D58A4CULL, 0xBAC9C2C535A66A8CULL, 
            0x02420CBFF145FB47ULL, 0x89A7E36EC938E609ULL, 0xAEF9D6F77471EA09ULL, 0x728167A76F08949DULL, 
            0x7863AB8669F2B2CFULL, 0xF8C9250C89DC7D92ULL, 0x92CE77DAAAB0CC93ULL, 0x3F39729477DD8F67ULL, 
            0x56C905F98C5F5BF2ULL, 0x521886E74051247CULL, 0x0BF842213E74458AULL, 0xC9AD143D50DC17DAULL, 
            0x02E540AF05599808ULL, 0x0A28538FC8A542D9ULL, 0x486EA878DA753D38ULL, 0x1D94D0417CBFEEAEULL
        },
        {
            0xC3F6955DF074C72BULL, 0x8D85E5EFC3991302ULL, 0x3B23680E325D3722ULL, 0x6344015BAE358695ULL, 
            0xBD4117CCC3998339ULL, 0x7B0F28CBB2D033EDULL, 0xD3F950F6DDE712BCULL, 0x1A8BF9F46DB79871ULL, 
            0x9B43D5FD53C340E7ULL, 0x656C333249DA7C24ULL, 0x3DAB92EB485F53AEULL, 0xF91F5F1043B0FCEAULL, 
            0x50878FE42CB0516DULL, 0x47CD84D5227B7316ULL, 0xEFEA0C0A0865B70FULL, 0xD856EB4D411AB68CULL, 
            0xADFDC71C95A5A87CULL, 0x0B0CF5B65CEAC597ULL, 0xED5BCF9E8C4C180EULL, 0xF8AE426BB0FC1653ULL, 
            0x1232191BF41253E2ULL, 0x22573F0726EF5FA1ULL, 0xBC823CA5B09CF53DULL, 0x83E3FDE2FCE56651ULL, 
            0xE30E44CB7EB09AA5ULL, 0x4ED0C0BDB3B9C600ULL, 0x501C6241AA84D035ULL, 0xD2921BFADA69D383ULL, 
            0xE549824E5CAEB5B4ULL, 0xF29B1E4001A02C68ULL, 0x76B3207B9AF6589CULL, 0xB2135404F350BD4BULL
        },
        {
            0xA163AA4028ECA152ULL, 0xA77CF6B32B504F5CULL, 0x17C3420A4813709CULL, 0xE1257AED2504C1ADULL, 
            0xD46C939350ECC2C5ULL, 0x2AAF4EC3F980DCAEULL, 0x4668E2A54F3BFECFULL, 0x1A2032F0F6CE246BULL, 
            0x7FB5B18E570F7C91ULL, 0xC33F49A54DF19942ULL, 0x0705D578270EF9AFULL, 0xB32C3FCC148C738DULL, 
            0x6A7C7AE4933A4813ULL, 0x9B80A1EC11C4F063ULL, 0xB13515D187801AB3ULL, 0xEE0127C03E9F760DULL, 
            0xB5460792DF0B6BE3ULL, 0x43253CBA56EABC66ULL, 0xA8CC94FB68C7D190ULL, 0x9972495A033AEF9EULL, 
            0x49F5C46C2590453CULL, 0x30BC86A5098BD10FULL, 0x3766B52E42DF7500ULL, 0x671A3EFCAD474A4FULL, 
            0xC3600E37C2CE20CFULL, 0x0845968DB938172AULL, 0xA667A1BC108E222CULL, 0x5F7302EBBF27C292ULL, 
            0x29791C18DB79E8B7ULL, 0xD947A73F37DD8AEEULL, 0x4FE830FF9DBBDA3DULL, 0xEAE425F4FBCFC925ULL
        },
        {
            0xE885B488EEE41DEDULL, 0xF081FDAC615BC2F0ULL, 0xFC70AAA0D4891787ULL, 0xBA41E9A3CE744E4FULL, 
            0xC01781B0590096B6ULL, 0xE6FCBA0F592255BEULL, 0x06EC2947124D6D2FULL, 0x35B97FF61FCD0636ULL, 
            0x5181A7647EC2EC75ULL, 0x2DA545ECD236D751ULL, 0x9545812A70F97017ULL, 0x220F7F9F72CDA6E5ULL, 
            0xDCBCC025554317CFULL, 0x78EF6E7E5EA8911DULL, 0xDF014F3B5EFB0CD5ULL, 0x0EBAC0BD6349E7E5ULL, 
            0xEEC365BC34007533ULL, 0x9DCF01592294EAA2ULL, 0xAA70725D60FCE937ULL, 0xC74CE9F8B27CD318ULL, 
            0xFAA7779DB52CCAC1ULL, 0x7E01A978B1711D83ULL, 0xCD6A28AEB3DE9CBCULL, 0x4926467964CF9E1BULL, 
            0x16916DA32442DE5DULL, 0xC03842B56D8C24FFULL, 0x7DF26399B1ECFC67ULL, 0xC12B9BDCC60569A6ULL, 
            0xB6CC65D1EF8DF5CCULL, 0x00016362A9E6B261ULL, 0x10645723CD132C57ULL, 0x665CC645CB60BC39ULL
        }
    },
    {
        {
            0xA1C6DC1FE1087F63ULL, 0x71D41223F302AF4CULL, 0x21D116DF6B520888ULL, 0x689947C0EA7C8D09ULL, 
            0xF3A9E677FBA1966CULL, 0xAF8C87C6099BE47EULL, 0x6BF1B4EF353AECC0ULL, 0xAAC6D7D79D5386C2ULL, 
            0x07FE957C1D12E478ULL, 0x073AA6A13C8ECD8FULL, 0x7CDD800BFDAD168BULL, 0x5D055CADC2DCAA27ULL, 
            0x3524F8F4AB8DCD07ULL, 0x74B56FB99ABEA3F5ULL, 0x4BB0F4732EFAA39BULL, 0x27163718E6E87B5EULL, 
            0x7F2A2B035C1DAC51ULL, 0x787EE693A839DB9DULL, 0x325CEAFB84CCB33FULL, 0xF77ED8F7D7604DB1ULL, 
            0xDFDF7E1F5E6E83C0ULL, 0xA14B4C8C7237362DULL, 0xCD10530C196F91FAULL, 0xE71518F3CD3281B9ULL, 
            0x406CD4FBA7787D33ULL, 0x2F78D22B5313A20CULL, 0x49D4827BC56A3D99ULL, 0x68CBD998C8D72081ULL, 
            0xE462A6CF8906B058ULL, 0xC2F053A58A7D1756ULL, 0xFDFFCEACF4673629ULL, 0x070F8DFBB772E0E9ULL
        },
        {
            0xEFE145B8D9F67F51ULL, 0x26480715C7B214F3ULL, 0xB1D25BA866173EA2ULL, 0x1A23B6940F725ED1ULL, 
            0x19A71E031872DFB5ULL, 0x0CBE3DB6C60A51C0ULL, 0x92E65D0BABE0A9B5ULL, 0xFC859F6C806BB227ULL, 
            0xA5EA6F6D3F4458D9ULL, 0x7FC375CCD2092ACFULL, 0xE3402EC93C318756ULL, 0xCC216240C1AD4015ULL, 
            0x94F7184B8D445855ULL, 0x069D41FC689535F2ULL, 0x45050DB8984449EDULL, 0x0B207F69083F5F7BULL, 
            0x862C73EEDBC9F73FULL, 0x903C2A1A22D5FAF3ULL, 0x5EA533FEFF393B9CULL, 0x427DE42F6D6BD816ULL, 
            0x8F2F1451D930C73FULL, 0x759F3759147EB787ULL, 0x14EB1C3FD6BC1BE4ULL, 0xEB6300C2CBC9D52AULL, 
            0x1192E372DE8E98DBULL, 0xAE44A9A42C1FBD6AULL, 0xF90ACBD08F6773B6ULL, 0xF7922068109F02D4ULL, 
            0x1EC4EE18A8874C1EULL, 0xC064E8FA48669EF4ULL, 0xA77536A35F8E6C12ULL, 0x1F8143BEFB1590C3ULL
        },
        {
            0xB83F72CCE4E2AB4BULL, 0x883F54B9C63E1083ULL, 0xF64F18377A7DF933ULL, 0xC5F5171B36D3FC28ULL, 
            0x4A3A8B16E8811094ULL, 0x99D392944A6CB06DULL, 0x1B7AC30247F0AC75ULL, 0xD3EB9A6A65A4743FULL, 
            0xB0438465EE764006ULL, 0x12C60096578BC928ULL, 0xBFF70D66DFE71123ULL, 0x33EA2534FC174A8EULL, 
            0xCACFF0FE8070B83CULL, 0xE55D1999FEF7AD40ULL, 0xF6A340509A3A013CULL, 0x942A6B7754BF9A02ULL, 
            0x69E98C421EEA698EULL, 0x857F3645F5094EF2ULL, 0xF37689015EFCF580ULL, 0xC33A790684A663BEULL, 
            0x7EB42CBA6FD86C89ULL, 0xA54FCA03BFF90B34ULL, 0x9CF3C36F9FF737BBULL, 0xCBB6C920C905DF81ULL, 
            0xF56859F71B350EBAULL, 0x2178E54BFBCA2821ULL, 0xF54CBA9795A000CFULL, 0x50DAA035434F7FE1ULL, 
            0xCEF60393EA31A07EULL, 0x6F79C64FFE9AF48CULL, 0x8DD0E0F78D9247A9ULL, 0x5762D4E96EE062E5ULL
        },
        {
            0x0CB3164A8004EFD8ULL, 0x4A7A13355FE2DC30ULL, 0x15C3E9B0D894979AULL, 0x970578DC50482F9DULL, 
            0xCD3CD8EB9C671345ULL, 0xB0FE85E89CA1E954ULL, 0x8D2E73D339C5DA7DULL, 0x8E1BB0D8ABD7AFA0ULL, 
            0xDAD9757C1EDEB8E7ULL, 0xDC9B0F29208756F9ULL, 0xB97F9B789F634F96ULL, 0x1510DACFACFBD4E9ULL, 
            0x128E52A5CCCA76FEULL, 0x9BAE54A66F8745CFULL, 0xF2DB6145D9F2E7CFULL, 0xED3153FBF0F164E7ULL, 
            0xF3234376570C1BB0ULL, 0xDE81B3CCF189D5CFULL, 0xF305A2B9FDA26829ULL, 0x50111F683609B5B3ULL, 
            0x241249A0D64703CBULL, 0x8468818C9844835BULL, 0xF6A824EACC2104DBULL, 0x9ADAF3309CCFFEA3ULL, 
            0x698E535B5E7CDD11ULL, 0xB11310D93EF1F910ULL, 0x41EDB994B85CFD42ULL, 0xF1C6EE3C8999B3C2ULL, 
            0xDDCE55FDB25A2026ULL, 0xF9E9C7AF011C122FULL, 0xF773A26D23D7E000ULL, 0xCB21A92EA32A0CFCULL
        },
        {
            0x44FE9C516F41B66EULL, 0xD889FDB8F01CB7BDULL, 0xA32070ACA7EEC69AULL, 0xD9D4040B63DA36CFULL, 
            0xCD137984CEEA74D3ULL, 0xE202BBDC561221B4ULL, 0x3934BC6BA9E785D0ULL, 0x7ACF0AF717074325ULL, 
            0x2CD52574D7C54E2BULL, 0x3B628CAF6F108CCEULL, 0xB9BF303E1971BC32ULL, 0xD507959CC292E2C2ULL, 
            0xAE8240B0A887FF13ULL, 0xE14A0CFC48E8B817ULL, 0x441139B89D4A0861ULL, 0x39DB0EA54743040FULL, 
            0x9F64772F20FAACD4ULL, 0x745A758384A0D03EULL, 0xF5B1E5FA06841ADFULL, 0x30A09BF85BA936D6ULL, 
            0x2015A8BC826D4BADULL, 0x82F694F43C0DB0FDULL, 0xF8D9311421ABA911ULL, 0x3B1976C03082836BULL, 
            0x12E95723BC6A2DC3ULL, 0x02CC53913D8C9BF7ULL, 0x9FF641B398F7B9D4ULL, 0x4CC363CE3A24728BULL, 
            0x8D511B4C3B8DF2A6ULL, 0x9BB1CD2F778E542DULL, 0x893E667A432412ECULL, 0x6D374BD056234415ULL
        },
        {
            0x6C4BFE466B7ED98EULL, 0xCFFC9CE60D0A5039ULL, 0x3A1DD08586921DFBULL, 0xCE386C803D3EB097ULL, 
            0xF8AD12D07FF7B4A9ULL, 0x6639BAAD8AECD449ULL, 0x269EAC9067B234C0ULL, 0xA7D5723DEA4E60D9ULL, 
            0x1AF44019623EF173ULL, 0x26B3BFC6071435DEULL, 0xC90C39AA3BFA155CULL, 0xA73D74FBFE61C2F1ULL, 
            0x1137B7EBD0173B0DULL, 0x53C8BB49FB8B7924ULL, 0xFC2C371DEE5049B4ULL, 0x1F5DF8069DCE30BFULL, 
            0x7F3346CB9F6B2208ULL, 0xBEFE6E29CA2193F4ULL, 0x7FA498A2D8190D1AULL, 0x84478FBD67BAF849ULL, 
            0x0FE1A31FCC68D626ULL, 0x11B2685728B60FD1ULL, 0xCBF751BAB181D30DULL, 0x33C620B77DD0AFD4ULL, 
            0xB2713FC06872DB88ULL, 0x27BFC1DBE29365AFULL, 0xE0C491530869E888ULL, 0xAFE1467F4368A93BULL, 
            0x6D661F6D621B74C5ULL, 0x96007C9934FC5853ULL, 0xE76B1C555F7454F7ULL, 0x2CC1CBB326FBBCA7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseGConstants = {
    0xB5ADDA7C49EB6477ULL,
    0xA7E832563CAA723EULL,
    0x00390D353AE33510ULL,
    0xB5ADDA7C49EB6477ULL,
    0xA7E832563CAA723EULL,
    0x00390D353AE33510ULL,
    0x7045C513C660D550ULL,
    0xA77AAE3CA0710CFEULL,
    0x7A,
    0xFA,
    0xDF,
    0x4C,
    0x0C,
    0x2A,
    0xF6,
    0xCC
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseHSalts = {
    {
        {
            0x8355EC579A1290D6ULL, 0x18193638672FCF76ULL, 0xC65E636DE93CCE5BULL, 0x0BC69617B495B8F4ULL, 
            0xE29301603E3B3876ULL, 0x3A072C1042A48A8AULL, 0x9B472ABEB53E295CULL, 0xA820342351F65933ULL, 
            0x84ECF4229DF99C05ULL, 0x4831000A0F10CE6AULL, 0xC6A7BD3F7D508DADULL, 0xDE3427EDCDFCDC6CULL, 
            0x3B1F92C2E558700AULL, 0xD44C0DA3C7A44969ULL, 0xF390CE21AA2265D3ULL, 0x0996A4635C48C3A3ULL, 
            0x4C6077D2E8424BE9ULL, 0x06A9518DDB9B42F1ULL, 0x72009C1A3B7D4F83ULL, 0x2B607C3A19E81F4EULL, 
            0x11C947660ADB85F8ULL, 0x0CB950D5206C00D8ULL, 0x224487D4B24C4790ULL, 0x7C560A1989B70CC3ULL, 
            0x0C16B80A6739B5ECULL, 0x2148CFABA7214B04ULL, 0xFCC760F8ABBC5E03ULL, 0x79B7470723B29D01ULL, 
            0xF17ABBA1B6BD768BULL, 0x6C87350DB7E5A840ULL, 0xFF4694C0754968D1ULL, 0x0B3AB7D365B366F3ULL
        },
        {
            0x475C18C49975AA9BULL, 0x16111730555C8804ULL, 0xB48E22D768E21C95ULL, 0xEAFF4E65F0A776B4ULL, 
            0xC7536AD7811E098DULL, 0x186E9E8BDE5ED465ULL, 0xEEBA6DC4DC436A9DULL, 0x5560E09D04F9F36EULL, 
            0x37D819A26678C36EULL, 0xEC677C6CACF9439AULL, 0x2B751570D360E485ULL, 0x8DFBD3F24309F8FCULL, 
            0x2C9D177EB7BAFED7ULL, 0x93C4AA54A33F26D3ULL, 0x1CD30BEB9618F052ULL, 0x5BE7B16E10FE2D8EULL, 
            0xED88E7F73CBD7FB2ULL, 0xD40666E0A57F447CULL, 0xD822AC2D95F66FCAULL, 0x8CDC33F36E05B528ULL, 
            0xE0F5E893B5FB0319ULL, 0xD50B907D9709B6B3ULL, 0x618DD96ED0024331ULL, 0x1A50F1554ECFBADAULL, 
            0x4AA322ED6A583680ULL, 0x95E42C30CD53EFF5ULL, 0x6ABE552B36131D16ULL, 0xDA581F474709D507ULL, 
            0x40693CFEAD14ABE0ULL, 0x1FFCFE5E243CB44FULL, 0x7B6421976322F61DULL, 0x94A9721DA3C43709ULL
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
            0x2BE515E603006B20ULL, 0x191B679D263E2578ULL, 0x02D7D3DEC2CF46B7ULL, 0x259CEB34A77E50C9ULL, 
            0x7CAAA17930EAA668ULL, 0xE8618998609D331EULL, 0xFE6D9010300F1BC4ULL, 0x30BE6E3ED69ED233ULL, 
            0xF5751AEBA22B0631ULL, 0x9F9A3AE93E2BD491ULL, 0x527B055BDCFA0A8FULL, 0x12EF2EB5646F8D70ULL, 
            0xA8431ADDC1471891ULL, 0x35FD3634953AD1EBULL, 0x47AEF61B98B2EC66ULL, 0x591EF1B791AC82FCULL, 
            0x0CE9A5B262387D48ULL, 0x38241AE57C27937EULL, 0xCB089DAC9998A70EULL, 0x54E137CB0A51DA18ULL, 
            0x892C5F4D04C685FEULL, 0x9FF580481E8D3BB1ULL, 0xD92BE6B504344E7CULL, 0x270E36CBD488F815ULL, 
            0xEF4D1C2CB153EBACULL, 0xE7F958C575AFCBA5ULL, 0x53615A55BC6A3E2CULL, 0x2A00D63BACEBBAF2ULL, 
            0x9EFF7D991F44162AULL, 0x001A9C2886682AD0ULL, 0xCCE5ADD652A23E2EULL, 0x9E51F1AA27E0C567ULL
        },
        {
            0x0F66556D367B7954ULL, 0x429EE28DE29278DFULL, 0x20B5F0B51D5B706FULL, 0xC102DFE8169967F8ULL, 
            0xB648D1EC173D735AULL, 0x8AB15053EC5B3CECULL, 0x27BF302DFD6CEF93ULL, 0x66279345662C9299ULL, 
            0xEFD3AE4E883DFE65ULL, 0x0F1EE37825AB1CE0ULL, 0xC781C820AC9B48EAULL, 0xBC7382F007504604ULL, 
            0x6B770BC081EB4EC3ULL, 0xF312CAF7511ED578ULL, 0x890705C0FC52624DULL, 0x5D519AFB0DCD4405ULL, 
            0x92E76634565270BCULL, 0xBCD556CC57F3A124ULL, 0xD9A8E18AFF84CDE9ULL, 0x3B2EEF948E1E56E8ULL, 
            0x9DD39D3C969D206EULL, 0x7C7473429782F40AULL, 0xC37AEF59086EB593ULL, 0xAE1EF8469C682D72ULL, 
            0x2B789C7B295AB6A5ULL, 0x1ADF6316BDEE1A28ULL, 0xB3EF1B19624342BAULL, 0x0B1B6DF847E7B285ULL, 
            0x0086AF1DD4040CD0ULL, 0x29CE81AA1FDEA0A9ULL, 0xEBE07A5C23507D58ULL, 0xBF98CB4D2A889CD7ULL
        },
        {
            0x83F5E38BB1E9B178ULL, 0xCBAF44E19CCB16E5ULL, 0x9B637843F2841AFAULL, 0x006AC1BE8FBB8206ULL, 
            0x9E7D1694A1E6252EULL, 0xDA8DFFE54B44A90CULL, 0xCD64F17732688AE8ULL, 0x4733605363CC8EBAULL, 
            0x2B4C753C041CF1E5ULL, 0x89800069ABAD53FEULL, 0x1FF74A2008F9782DULL, 0xCECD7D7B0F47CB8FULL, 
            0x9750D30BFBFA2571ULL, 0x146736AA5D21EC78ULL, 0x6EA6F8C8BB9BE6C8ULL, 0x13D51C1172877853ULL, 
            0xA49D559688743645ULL, 0x1753E801A34B4190ULL, 0xAE91FD1EEAFAE868ULL, 0x5F79B82586B4BF90ULL, 
            0x4E22FEBB91635689ULL, 0xCB70FF6BCE30EF6EULL, 0xB914131A16E5601BULL, 0x3003740AFF954B4EULL, 
            0xC14ACD3E554A48E1ULL, 0x10B066426991216DULL, 0x2AC2A17916D08F48ULL, 0x9715DC0FE9AB23C9ULL, 
            0x24D8E3599A766A78ULL, 0x6BC180E055B9ACE7ULL, 0xF2982AA463C017C2ULL, 0xDE54CB26FE17F608ULL
        }
    },
    {
        {
            0x42B91188312EB693ULL, 0xB57DCA747BC0CEB4ULL, 0x56D4C6BFC5640B47ULL, 0xF0BB65F9C96FDAC2ULL, 
            0x0F38B83D730AA250ULL, 0x1CF35D4DD0026D27ULL, 0xBB029C007038004AULL, 0xEC4D1A84711D27CAULL, 
            0xC7D5E321B4765C54ULL, 0x9A13194541EA01EEULL, 0x73834AB2EB1271B0ULL, 0xD846DC21BDDF0E4DULL, 
            0x6361A69525D378A5ULL, 0x20BC1402E222CA63ULL, 0xF57BEF32507B03F8ULL, 0x839C4590CC2D9FE8ULL, 
            0x20E891C600BB09F7ULL, 0xE0BF2DC5EAD64278ULL, 0x71A42664451F5DA5ULL, 0xEA2BC19CDE2DE802ULL, 
            0x6E57CB8665ACAEE6ULL, 0xFF8000D3DE17E123ULL, 0x20BDE3DA08D34FBBULL, 0x5448A268E27F0E0BULL, 
            0xE3F6F96ADC7E9B33ULL, 0xCAA133A017D60E24ULL, 0x2B7631BFC1E94523ULL, 0xD968EC5931EA5F23ULL, 
            0x98F8408FF0E540F8ULL, 0x06D8F036E8CBDC3EULL, 0x89E98B923338C95CULL, 0x80DDA5F314847365ULL
        },
        {
            0xCFDF652CB83B7D23ULL, 0xC39523BD0C403EB7ULL, 0x5161E62FB5A58C96ULL, 0xA3A7C69875832F2CULL, 
            0x44B8F57ABCAB8C01ULL, 0x8F6A673A0A5CB71CULL, 0xBAD0678BAC0B25ABULL, 0xC5CA0AB28C38E712ULL, 
            0xFB17DBA9B440155CULL, 0x06CEF72B600F7214ULL, 0xD3A2C46A94012150ULL, 0xAEA22D57F87B2B5FULL, 
            0xB45B00BCA660F195ULL, 0xABFA334D2AD46B30ULL, 0x5B6E16CD87B2E5F0ULL, 0x65BFFF6229A0120FULL, 
            0x2C6C85BB28D9AC0CULL, 0x76B587688376A9CFULL, 0x6BFE8A99FD1407E0ULL, 0x66800001FF17A3B9ULL, 
            0x54AD6D476E32D7E0ULL, 0x2121E205A902CCC8ULL, 0xEDFE9A0F5FE41D24ULL, 0x819AF3720F27C585ULL, 
            0x07162E4AB3C8D32DULL, 0xE4040ED5D7558289ULL, 0x76C43E178035CAC1ULL, 0x126286C8AB31C157ULL, 
            0x7BE72D58089F442BULL, 0xA95CF39E29804E0CULL, 0xC38CE542D43D1605ULL, 0x86C65D5497BB6878ULL
        },
        {
            0xFA54DB2838D4EBD5ULL, 0x8DFA3FD460AEC8CFULL, 0xB30AF7B0E761CFA5ULL, 0x6B6F1246723989AAULL, 
            0x97F398EFAD46205DULL, 0x1DE3FB7C60B1B51EULL, 0x9360DFF7A96B6595ULL, 0xE2DFD30CC5ACF36DULL, 
            0x251B1CC79A03C76CULL, 0x22B1C047BEF2E10BULL, 0xFE49F67DF4EA9505ULL, 0x1E4A82B026FB445AULL, 
            0xA2286F136BDC31EBULL, 0xECA1AD02EF798831ULL, 0x68EA8EFE523BDE0DULL, 0xB3FD741BC8315225ULL, 
            0xD12A2A57B9DCFE98ULL, 0xDE868B53A346D3EAULL, 0xFE0DC1D6F841610CULL, 0xB25D132F5CBCB6D9ULL, 
            0x7A5ECFE10A3E1EEFULL, 0xB8DBE786D3AB1E45ULL, 0x130EC7DF7CE7FC51ULL, 0x1BCA8E21CCA1D942ULL, 
            0x9D69469C1037DE3CULL, 0x4AE2E4421A709CCDULL, 0xEDB56ED227C03597ULL, 0x6575F1223FD9D380ULL, 
            0x8D972F4A66AD688AULL, 0x1A50308D7BD5AF95ULL, 0xDDEE35CE617DA9A2ULL, 0x6A6BD6024731856BULL
        },
        {
            0x44A1D3D160BBA838ULL, 0xAE52C23EB911E3DFULL, 0x806007EB39FC4A1DULL, 0xE4682C111C76F9FCULL, 
            0xC680EA69B1FBB761ULL, 0xBF80AD06F930BFE2ULL, 0x25B62873838850C2ULL, 0xE9B07011D368BECCULL, 
            0x53F8CDCD5814103CULL, 0xB9F24C208312DD62ULL, 0xB7F822ED7BFEEAE6ULL, 0xE511A5C80D6E33F7ULL, 
            0xF8FB73592B381A73ULL, 0xDC62E8F07182DE74ULL, 0x1D50EC2542FC9499ULL, 0xE4941844CBFCACF2ULL, 
            0x51FB37C995583778ULL, 0x32D9613796E32C61ULL, 0xD6FDD0A06ACBA7DAULL, 0xEC301EE376E784FFULL, 
            0x58EC44F02D0CAE6BULL, 0xBC4624019C81FF06ULL, 0xD79BE5DA810C6E3FULL, 0xE2DB265ECF8F18C5ULL, 
            0x085B6A1AD89EB407ULL, 0xAF3F6E3BBA30ABEBULL, 0x3BE235F6B39A2443ULL, 0x1A814FDF986308F7ULL, 
            0x3DB337D9288799B2ULL, 0x09B22341A2D35EABULL, 0x05F8AEA94E32552EULL, 0x061DCA8505B2A1C9ULL
        },
        {
            0x73ADBE5AF9BB80A1ULL, 0xB7CCA43767D6D696ULL, 0x5CA833B1E7599D82ULL, 0x14A9FBCEDD8457BCULL, 
            0xA1F579C957247552ULL, 0x98F4EA643ADEF8CFULL, 0x8B65278BDC2DAE61ULL, 0xA325FFB82B075754ULL, 
            0xEA4E9CFFECD13182ULL, 0x505A03A96E3B88B1ULL, 0x805979F232662032ULL, 0x05F8E5DB7504BCE0ULL, 
            0x019735A2CFC9258BULL, 0x79C57186D94A1FE3ULL, 0x0A71EBE9FD0FF513ULL, 0x04EEC3347E475C92ULL, 
            0x3447BF541364A874ULL, 0x3D10C04E1837F147ULL, 0x283389EDB4787F04ULL, 0x22B971FEBC195FF5ULL, 
            0xCA61FD53756759B4ULL, 0x03F107A4A4CE080CULL, 0xA76A75C00586628CULL, 0x975943A78648A1B1ULL, 
            0x842967A360C6B466ULL, 0xA01B8824E904AAB2ULL, 0xC7E3DB0CB39072C7ULL, 0x9F62167947FA6D57ULL, 
            0x6A167CF51AB5F3CAULL, 0x8FD82BE8F467545AULL, 0x69D532C61A7EC1B9ULL, 0x6794E4A3E7EDD845ULL
        },
        {
            0xABE39F746A70F4D2ULL, 0x14BF4AF4719D0778ULL, 0x2641A8DE7688FFE6ULL, 0xB3C07BAFA8CD387CULL, 
            0x8C60EA5FBE0B9C89ULL, 0xBA645DFB1A924419ULL, 0x4AF7F8AC060ED842ULL, 0xEAB85F6B514E4D9EULL, 
            0x9809E25B617C8DD2ULL, 0x3127330CB3B6F538ULL, 0x5E8B5E01ADBABD3AULL, 0xC38F9A8745C9E636ULL, 
            0x791A5C1B77B3DCF3ULL, 0x0DC1C8BCA778E2E1ULL, 0xEF71BFCF40E04F38ULL, 0xE4F0012038EBE69DULL, 
            0xBED9BA1C68927BEDULL, 0x301D6C879CF688A1ULL, 0x279796E85DB5E121ULL, 0xA7920C1D3E638D77ULL, 
            0x2182F50176E921CBULL, 0xEF2C7E9754B7D548ULL, 0xBCA62CFE00BAE388ULL, 0xAC46E521EA4573B6ULL, 
            0x602B5B8BFDCB95F2ULL, 0x78D23A26EEF7D7B2ULL, 0xED046FDF8AD6D302ULL, 0x749B2A9684C9DE49ULL, 
            0x09B97BBBE1CFDAC5ULL, 0xD32CCAC7D8970445ULL, 0x3636B77953EA20B4ULL, 0x725ED9C675ECC08BULL
        }
    },
    {
        {
            0x8114F6732FDD5096ULL, 0x43B31B29E3406E8EULL, 0x0D55247AE70936D4ULL, 0xF9CF8C0AAA03E947ULL, 
            0xE8E3A5476FFC6430ULL, 0x074FCADCA1F8BDABULL, 0x96A13D76A435016DULL, 0x42C895EB73B9BCD8ULL, 
            0xCBA8CA9B193B1450ULL, 0xCB8A5C48B648F9C7ULL, 0xE116A761C71D048BULL, 0xDE3D21C0276D65A0ULL, 
            0xCCEA28CAC754F2E6ULL, 0xA4D21BD9C65197ACULL, 0x20A905C12EBE0317ULL, 0x900943D3A440FE19ULL, 
            0x03A492AC40DB1888ULL, 0x6096A8A7DFF08347ULL, 0x3AEB40496D610DCDULL, 0xC42D8A18D47DE4D1ULL, 
            0xD366415B16695EFCULL, 0xB77F082CE30C8C75ULL, 0xED7DACD3B8AB9D1FULL, 0x5DDA690170E35159ULL, 
            0x6235D90843F07076ULL, 0x3090FB8F4C24040BULL, 0xA40103D7148AAEDFULL, 0x2C2F78004406D3DAULL, 
            0x828CC77894A3351AULL, 0x01C2A7BED532EDADULL, 0x9CACEF4F8EDCE4B5ULL, 0xEBA248CB25FA2F41ULL
        },
        {
            0x113819B0D7109557ULL, 0x2A16E0A9258EB31BULL, 0x885C73309C46C8A8ULL, 0xDE203C3EDB24ACBDULL, 
            0x3A663BD603C898EAULL, 0x12BC3337F4B5DBFDULL, 0xF1D125494DE9636EULL, 0x3168DBE377AAB6C7ULL, 
            0x01131CC1AEB662F4ULL, 0x0B5C12649593003BULL, 0x898DE4961288B70CULL, 0x4603E60BE95CF421ULL, 
            0x69AC004CD41E120EULL, 0xC0C1D3FC2D002C19ULL, 0x18294CF3887FB804ULL, 0x2D0680AF37844131ULL, 
            0x15AD1D8BF9957480ULL, 0x7C91EE0F4824B63EULL, 0xE699E216ACB99792ULL, 0xF0C47160CF4E3026ULL, 
            0x7759B8B4E47E4A63ULL, 0x0C6F6AE75D07F72EULL, 0xA6648E9894BBF20CULL, 0xAD202FE3C99AA642ULL, 
            0x50CE1D6A27E894C0ULL, 0x45DD159AA0CBA63DULL, 0x924ED8A56BC8232CULL, 0x16C0B612587FB072ULL, 
            0x901A591F0178733FULL, 0x4ECC63D161189242ULL, 0x14FEA21CF76ED9E2ULL, 0x30E706B7268676D0ULL
        },
        {
            0xEACFA7DAF7BEA32AULL, 0xED2FE179A3850184ULL, 0x662428B90CA3B0E0ULL, 0xDB7432D2C0F7D5F3ULL, 
            0x555CB84E611AF4D3ULL, 0xE25DEE72EF267B30ULL, 0xF22851B95C4B4451ULL, 0x9736A990790B2809ULL, 
            0xFA6E45601A4B6657ULL, 0x4C3FA9D506B8A572ULL, 0x9FDEC6B3955764C3ULL, 0x206CEBC70CE443D8ULL, 
            0xFD4D7E9023ADE794ULL, 0xC996CA99AC693C43ULL, 0xB1172669D59ED5E8ULL, 0x791F9DD333651936ULL, 
            0xA29CB3DA44AACA5CULL, 0x041BD777DF5986E0ULL, 0x14E018156DFE73ECULL, 0x124A0CBED21A0191ULL, 
            0x65BCBEBB897BF793ULL, 0x9D8A3AC7054F2A20ULL, 0x7360C5E8305648DEULL, 0x08E24418C4B8DC85ULL, 
            0xED45BD7D0785764FULL, 0x9B0FCE264E282D89ULL, 0x18ED39583B870BDBULL, 0xE2F9AD8CB86D02AEULL, 
            0x072B070452BBD57CULL, 0xFCDD157FDB5B0FC2ULL, 0x01AEAFAB3085FC31ULL, 0x77C3FDF1F739161DULL
        },
        {
            0xBFDFC6C16202E9B3ULL, 0xC34ECE3294333F29ULL, 0xE44424D68F4FA5ABULL, 0xF9567F26DAFDA46CULL, 
            0xE2295AF8E2B40C14ULL, 0xA2AEB5E1E27183B4ULL, 0x300D8F928472A002ULL, 0x5B0A40EA2F4DE5C9ULL, 
            0x8614160E6CB9A423ULL, 0xBF64CBF9F0EBD791ULL, 0x8087821FF3D7B9B3ULL, 0xA03C679F89287FE5ULL, 
            0xA7505E1235D3C098ULL, 0x2B809B38A3F7F3C6ULL, 0x84FA97473665F2C2ULL, 0x3D1FC7AE5A66ACCAULL, 
            0xD6A0344079E88971ULL, 0x90C0509396C48CC7ULL, 0x3719DDEC1DA856C8ULL, 0x7183E17DB2931885ULL, 
            0x0F175851140601E8ULL, 0x30A90E0EE9C58C55ULL, 0xCE48698EE5B53377ULL, 0x4D2DCA6524EE95A5ULL, 
            0xEC7FD405761B6B97ULL, 0x2D9A0BC395B1C273ULL, 0x4D2407A5C7894F69ULL, 0x167095A71EB4C177ULL, 
            0x4F030E3FFE006716ULL, 0xBD52FEFF50680FA8ULL, 0xF877E07F98B428E8ULL, 0x152B35DEFE69F143ULL
        },
        {
            0xC548CF6B88C56739ULL, 0x8E4552579948E3D8ULL, 0xC801E722DB9205B4ULL, 0x2D977AF314E43D42ULL, 
            0x8377AEC99A055F05ULL, 0x560EFED3F8C85F7CULL, 0x7B63E20007690B2EULL, 0xD5D35C038250FD4BULL, 
            0x122F8A98687E9EBAULL, 0xCCAF5096E728E20DULL, 0xC1F8B051181D8935ULL, 0x2A8932291EECE633ULL, 
            0x1B5A6474557E3508ULL, 0x37D8038F4C9F4652ULL, 0x389CF4F8F7FEE734ULL, 0xDD48E71A4E810DEDULL, 
            0x3842C98EE249A415ULL, 0xF5DE337B45947335ULL, 0x0E533D2576C586B0ULL, 0xEF0306BFFD8731D2ULL, 
            0x8A80997EBC4FBF0BULL, 0x5A605E09C6976746ULL, 0x064DF806DD7B7EB1ULL, 0xF66FC6956084B7E9ULL, 
            0xCB9675172D6CC84FULL, 0x10D87F0FC3337AB1ULL, 0x087C7DD70F734113ULL, 0x0177F47EF630F9EAULL, 
            0xC0A1951D6EB9293FULL, 0x32CAA6F50F6F7068ULL, 0x50EEC08FB5987A50ULL, 0x38C64BEBA1446354ULL
        },
        {
            0xB50740E1CEA2741EULL, 0x3AEDBF67E7E01AB6ULL, 0xE619CFD0BBC1F35AULL, 0x353F0245CFD72B8CULL, 
            0xFF312DC742CBA196ULL, 0x2822C2609B4A9C4DULL, 0x09D95C2E1579BFF3ULL, 0x24405A6DB8C04304ULL, 
            0xAD72A082995984D8ULL, 0x3214236FE12E4462ULL, 0x07F0D23A41AF5439ULL, 0xCEAB4DE3A70B755BULL, 
            0xCA476A3F835E1561ULL, 0x966477CE36B298ABULL, 0xDCDCFD6E1A8B5398ULL, 0x04A027A06946025EULL, 
            0x4AA4272918772848ULL, 0xD5501D1B07019BADULL, 0xC2610592C22616C7ULL, 0xD319742C86248A19ULL, 
            0x797A002AB0B9B5B2ULL, 0x8DF0C122E436A29BULL, 0x072A2E3244FD840BULL, 0x9F0FBACFB947D0DBULL, 
            0xFAEA56B9D9AD536AULL, 0x1E408037087A7D2DULL, 0x1013DB8558389442ULL, 0x18B920C08449C86AULL, 
            0xE44FEB89E8BDF85CULL, 0xB83D5859B64D9367ULL, 0xE07408178CD7222EULL, 0x3B387C3950F42D1AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseHConstants = {
    0x72537FAD866A8CEAULL,
    0x95C3DCB200746941ULL,
    0x480CB87A5B7CD6B4ULL,
    0x72537FAD866A8CEAULL,
    0x95C3DCB200746941ULL,
    0x480CB87A5B7CD6B4ULL,
    0x52C1C2626780CA32ULL,
    0xD092E7790C54DB56ULL,
    0x25,
    0x63,
    0xF3,
    0xC8,
    0x26,
    0x55,
    0x27,
    0xCC
};

