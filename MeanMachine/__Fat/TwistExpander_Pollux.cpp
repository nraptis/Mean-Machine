#include "TwistExpander_Pollux.hpp"
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

TwistExpander_Pollux::TwistExpander_Pollux()
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

void TwistExpander_Pollux::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8F3788D190F0FFAAULL; std::uint64_t aIngress = 0xF9E4533EE71B3B9FULL; std::uint64_t aCarry = 0xA050A1EEEF8E62ADULL;

    std::uint64_t aWandererA = 0x920A0E0BF0FD2F97ULL; std::uint64_t aWandererB = 0x80714D320213509BULL; std::uint64_t aWandererC = 0xECEBFB2A83588644ULL; std::uint64_t aWandererD = 0x875CF9FF10CAF47AULL;
    std::uint64_t aWandererE = 0xFB5A7B985354EBB0ULL; std::uint64_t aWandererF = 0xD2505F801475F5CFULL; std::uint64_t aWandererG = 0xA5DD145CE65BEC2DULL; std::uint64_t aWandererH = 0xF7DF178770E88E92ULL;
    std::uint64_t aWandererI = 0xBA9FB7F91D20671AULL; std::uint64_t aWandererJ = 0xD7B7FCDE868078DDULL; std::uint64_t aWandererK = 0x8B67123FF5043E3AULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13821191758188801950U;
        aCarry = 11912925077527654693U;
        aWandererA = 15050785036782085301U;
        aWandererB = 11318015069114702591U;
        aWandererC = 10054897550116333242U;
        aWandererD = 9530981015300390036U;
        aWandererE = 11746068670879064077U;
        aWandererF = 15770535393506779834U;
        aWandererG = 17637738388518574803U;
        aWandererH = 16628126921308139239U;
        aWandererI = 11914415529337475841U;
        aWandererJ = 18043055755582837940U;
        aWandererK = 14199899874206668642U;
    TwistExpander_Pollux_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Pollux::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD559A2CFCF97DA89ULL; std::uint64_t aIngress = 0xF6915EA5EE8AEE44ULL; std::uint64_t aCarry = 0x99A8396A86305AE8ULL;

    std::uint64_t aWandererA = 0xD42D96E5111B2F76ULL; std::uint64_t aWandererB = 0xB3329280C7A2E97EULL; std::uint64_t aWandererC = 0xDB9B89E6107C29BAULL; std::uint64_t aWandererD = 0xFF905D1E58624652ULL;
    std::uint64_t aWandererE = 0xEC6C1F52967468DEULL; std::uint64_t aWandererF = 0x994626A1AAC8BFDBULL; std::uint64_t aWandererG = 0xF99FC65E81CBF043ULL; std::uint64_t aWandererH = 0x804C966043D14D36ULL;
    std::uint64_t aWandererI = 0xC90D880C8C57584DULL; std::uint64_t aWandererJ = 0xECE3CA4B8A898C0DULL; std::uint64_t aWandererK = 0xA946C38AC2832E6DULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15225471084775123717U;
        aCarry = 14840629036174638517U;
        aWandererA = 12674664540303024470U;
        aWandererB = 14033718968460968277U;
        aWandererC = 13409162532514731014U;
        aWandererD = 18304416661537615164U;
        aWandererE = 17730704841526713719U;
        aWandererF = 17415508299446351538U;
        aWandererG = 13099102018454192272U;
        aWandererH = 16273372283996801496U;
        aWandererI = 15845457151172322503U;
        aWandererJ = 12058999031985163284U;
        aWandererK = 11209947116947705778U;
    TwistExpander_Pollux_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Pollux::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE255E8A8B9BC931BULL;
    std::uint64_t aIngress = 0x9CFA991DE8386A64ULL;
    std::uint64_t aCarry = 0xFC352EA3FD58C44CULL;

    std::uint64_t aWandererA = 0x813D4EC97C2DAB90ULL;
    std::uint64_t aWandererB = 0x922052C9003321B3ULL;
    std::uint64_t aWandererC = 0xCBDC25F473487F06ULL;
    std::uint64_t aWandererD = 0xCA9A7268537DB926ULL;
    std::uint64_t aWandererE = 0xC0C8F68D62167A1BULL;
    std::uint64_t aWandererF = 0xC7B397AD8822B381ULL;
    std::uint64_t aWandererG = 0xC490605BEC581573ULL;
    std::uint64_t aWandererH = 0x8663E9CDB1AFE32CULL;
    std::uint64_t aWandererI = 0xC56DB29196208D66ULL;
    std::uint64_t aWandererJ = 0x8A14E3AF28157DC6ULL;
    std::uint64_t aWandererK = 0xAA05D6ABB2660202ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
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
    TwistExpander_Pollux_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Pollux_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Pollux_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Pollux_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 25 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 43600
void TwistExpander_Pollux::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1350U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1160U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 818U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1402U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 638U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 220U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1918U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1634U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 353U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 465U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1851U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1661U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 919U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2043U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1921U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1401U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2004U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2002U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1074U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1032U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 84U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1965U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1110U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1223U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1477U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1546U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1608U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 974U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 142U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1815U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1330U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 448U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 522U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1705U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 216U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 498U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1678U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 531U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 841U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 430U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1776U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 106U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 422U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 314U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2033U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1760U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 880U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 459U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1525U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 932U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1308U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1994U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 307U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 409U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1777U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1593U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1906U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1513U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1860U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1363U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 126U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1369U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1329U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1589U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1392U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1257U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1111U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1558U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 56U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 143U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1342U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 631U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 612U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 262U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1028U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1426U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1202U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1644U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 539U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 204U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 920U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 178U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 69U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1475U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 481U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1394U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1648U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 441U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1795U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 927U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 338U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1789U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 467U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1125U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 402U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1154U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1838U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 18U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1850U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 910U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1012U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 302U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 212U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1341U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 179U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1638U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 672U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1943U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1382U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1218U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 233U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 187U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 16U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 715U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 80U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1238U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1255U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 989U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1079U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 916U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Pollux::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCB5187F3265F7F79ULL; std::uint64_t aIngress = 0xCAFA0FC42B4D3E34ULL; std::uint64_t aCarry = 0x93FCDA5F60083B51ULL;

    std::uint64_t aWandererA = 0xA7D8C3A7D0F40747ULL; std::uint64_t aWandererB = 0x8610DD00980074CCULL; std::uint64_t aWandererC = 0x95B91594ECC7B194ULL; std::uint64_t aWandererD = 0xEF39DBD256F38FC0ULL;
    std::uint64_t aWandererE = 0xB68FE386EFAE98D4ULL; std::uint64_t aWandererF = 0xBE6D3D9D1DE4C765ULL; std::uint64_t aWandererG = 0xE61B9C044A7FD4BBULL; std::uint64_t aWandererH = 0xC80678D167C0F6B9ULL;
    std::uint64_t aWandererI = 0xE0CE47BA7B676BFCULL; std::uint64_t aWandererJ = 0xE7E23812625593BDULL; std::uint64_t aWandererK = 0xF6DBD17D5EAE3866ULL;

    // [seed]
        aPrevious = 12373479522363129163U;
        aCarry = 14860792696284944456U;
        aWandererA = 14149442315741510678U;
        aWandererB = 15457722607138202553U;
        aWandererC = 11520964055318047229U;
        aWandererD = 15116140685999674640U;
        aWandererE = 14579273989729254539U;
        aWandererF = 15437123776675655683U;
        aWandererG = 10455936475540446342U;
        aWandererH = 14812056162147600162U;
        aWandererI = 9287780070667085642U;
        aWandererJ = 15029794203461625531U;
        aWandererK = 9362350900728122250U;
    TwistExpander_Pollux_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Pollux_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Pollux_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 25 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13011; nearest pair: 492 / 674
void TwistExpander_Pollux::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5659U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5986U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1041U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7139U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 108U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7544U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1333U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5795U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4231U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6522U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6590U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1490U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6492U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3712U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7420U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1088U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 874U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1588U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1054U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 278U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1472U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 878U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1177U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2038U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1183U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 60U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1490U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 355U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1949U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 259U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1818U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1294U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1772U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1648U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 25 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13023; nearest pair: 484 / 674
void TwistExpander_Pollux::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1410U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1227U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2668U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5970U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1534U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7969U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4985U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5489U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3577U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4088U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1307U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6338U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5500U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6229U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7096U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1136U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 660U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 978U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1237U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1187U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 492U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1077U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 926U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1380U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1620U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1386U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1078U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1567U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1719U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 725U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1665U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1659U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1784U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1220U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 2037U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseASalts = {
    {
        {
            0x8AB22A46EA3D77E9ULL, 0xAF5409E3311613F6ULL, 0xBF2D1E42D7447189ULL, 0xEC21268AC83D2919ULL, 
            0x3BADF8E83EA5C5C0ULL, 0x7AE8A1D3A67BC64AULL, 0x3C2853260B821A49ULL, 0x7A55C4DBFB988219ULL, 
            0x7C7772AEAE8681B2ULL, 0x2E21DCA33EA61650ULL, 0x04B1EFF849D6430FULL, 0x228F2F9E63AF8B0AULL, 
            0x6950EE1E919D44ACULL, 0x0D1449E2C622C886ULL, 0x3605860C4BC035E2ULL, 0x98C00D07C0908CE8ULL, 
            0x4B4D36ADEBA99D82ULL, 0xCF0ABC5BBCC4EB31ULL, 0x683783AD4F633BC6ULL, 0x71468CEC1C984B31ULL, 
            0x39F83DC4C5BD6C11ULL, 0x1EA12B4F1721E346ULL, 0xB99C043FC330824FULL, 0xE3EFD6E63C7F9386ULL, 
            0xBC932EBC84518419ULL, 0x8D471E1C5A8B1DB4ULL, 0x7F7DCE2E8D4AD36BULL, 0xC8E526FFA9B5B8F9ULL, 
            0x9EEAC8054BBB555AULL, 0xA8331886FBC0869FULL, 0x7EBAFD8EABAF3AEFULL, 0xFB949E402E68BEEAULL
        },
        {
            0x00510D8E1D1C7E41ULL, 0xC1C37240A2B0B378ULL, 0x14B52FF4ECBD4F91ULL, 0xAE6CEF2C43583AE2ULL, 
            0xE0F59AF58264CB40ULL, 0x1E37412334A5FD33ULL, 0xEB48860CB86B812CULL, 0x5F59369FB4015114ULL, 
            0x6C384569806005ABULL, 0xA184771B2965DF14ULL, 0xD982E2BEB35F6F90ULL, 0xBBE0AFC1A0487DCEULL, 
            0x50A3A5261B02822DULL, 0xCDDAEFAEA814F008ULL, 0xB8246844319148DFULL, 0x4E46FE1B66F027A5ULL, 
            0x18A943AE7454D924ULL, 0x355373DADF0AF98FULL, 0x2E5DCE5F5A4B8F1DULL, 0x0B48F70521334626ULL, 
            0x04816A4963858933ULL, 0x4286BD71AD8C2EDDULL, 0xEB8D431C16B015DDULL, 0x56833E073FE3C598ULL, 
            0xE3552C3DFEB28919ULL, 0x94EE00D461D72B59ULL, 0x6B66C132F58B374DULL, 0x88ED27F094F8B9BEULL, 
            0xAA1B3A3D37077D6CULL, 0x738B57D986469C07ULL, 0xCBA15E1A56E01E86ULL, 0x09B16FA57271F388ULL
        },
        {
            0xF50C5DEB28E5D61EULL, 0xBA7D6DF4352B1795ULL, 0x932017B52CE9E426ULL, 0xDF022A162F543CF9ULL, 
            0x74AABB2123C02673ULL, 0x5ED6192C74AFF0B3ULL, 0x76D3B600B0ED8FCDULL, 0xF87912293CEE8937ULL, 
            0xB3290D8B510A5209ULL, 0x3DE42A31390F7C24ULL, 0xE1912EBDBD8F27BAULL, 0x8C080CD917A7A97AULL, 
            0x640A9E888840F138ULL, 0x54C04CE1C86464EDULL, 0xA58626F26D3CFF86ULL, 0xB5B501E575D8579DULL, 
            0x6F4E7CBFA1583475ULL, 0x368A4CDCF180AA38ULL, 0x61F5DCE012687D35ULL, 0x245BC70537E891AFULL, 
            0xAFD16AE924F591DFULL, 0x6411CDE953631CC1ULL, 0x08BFE82500996EF5ULL, 0x93671B80304B0C6DULL, 
            0xDC590300A8B9A7C8ULL, 0x61024C2DC7B51750ULL, 0xBB15AF763341584FULL, 0x1D010212B4BABF34ULL, 
            0x3481ECDC9194AF28ULL, 0xD5F71EB0194A6437ULL, 0x9DBE78622FD178C0ULL, 0xA1A44952CC2FA5F7ULL
        },
        {
            0x7910E533AAAAE1BAULL, 0xFAFA0A5E5651C3D2ULL, 0x5A3AE9C718747ADCULL, 0x2F11AB20E5CF448DULL, 
            0x787D62DCE1B8171AULL, 0x4BB1007A9DA07579ULL, 0xB5D618AEA0E55F5DULL, 0x687FE2556A4E6A71ULL, 
            0x800CCD3DC1C867DCULL, 0x82F2AFE73A38A78BULL, 0x5E614500E2ADE860ULL, 0x6F2A9BF53F340817ULL, 
            0x41F3239D7594DB16ULL, 0x8AA99E320733A9E1ULL, 0x49C82A6F63A3FAE5ULL, 0x8EBF9F9B5555940CULL, 
            0x824F5A1B950EE05DULL, 0x271FE4085256E23BULL, 0xBF90A5893EBCCA66ULL, 0xFC8C549BA354FDEFULL, 
            0xDA395D0E10A0E6D2ULL, 0x620B6691B43F47CBULL, 0x2CB1C2C7D92A89EAULL, 0x0477234EC0AB8C72ULL, 
            0xAB1997220A9551C1ULL, 0x6B8F850554971F2CULL, 0x918F228748E74588ULL, 0xE9A387A870A45EDAULL, 
            0xCF1F1538AB4803F2ULL, 0xEF383D99C43CA3CFULL, 0x641856F5CF258A09ULL, 0x06DCA0D65FA9C993ULL
        },
        {
            0x9042A7AA0BE4BD2CULL, 0x8D0789BEBAD86EF1ULL, 0xCFC167AF9D5F2ADDULL, 0x037F89EC6881DD25ULL, 
            0xF4CEACD75E172B84ULL, 0x6858E93A49758393ULL, 0xB21B49DC60C67CAAULL, 0xF30025F47D791231ULL, 
            0x62DCC18CFEB67F6CULL, 0x5A0646522CEA904FULL, 0x72A7E7E9B1F36F5DULL, 0x5189548F1BC3D70DULL, 
            0x8C82BC6917495ECFULL, 0xDAE49AE74D321179ULL, 0x003A0821F94F9CA1ULL, 0x49700E0CEAEB29BCULL, 
            0x16B8D23E7C05B03CULL, 0x7501CD09E6394420ULL, 0x9147F66A416ADAFCULL, 0x99CA0CAB7CF2AA56ULL, 
            0x0074DFE1C3702386ULL, 0x9029A50DF630076AULL, 0x2D52588987EBD93EULL, 0xC62F4C4B47E070A2ULL, 
            0x40E0F0339A36B6C0ULL, 0x472AE8749A3965D7ULL, 0x40C9832FDA63903DULL, 0x77B3153AAC50980CULL, 
            0x59AF483B6462C772ULL, 0x026B83D4612F07D1ULL, 0x15463096922D4A6CULL, 0xACFF33298FF80CB5ULL
        },
        {
            0x6E26BE0EA5D9BEB1ULL, 0xF30A740F8DBEB9D8ULL, 0xCFFF93C236CC798FULL, 0xE7BC3A92AAC7E78BULL, 
            0x6502304012654ED5ULL, 0x44423C3F38236285ULL, 0xC1FB901FC8859548ULL, 0x3B55272DD497A8F4ULL, 
            0xBF92008480BB9676ULL, 0xB24153D0ED2E70F1ULL, 0x406D9F6CE1CE349BULL, 0x1CE483D235F00111ULL, 
            0xDB3A08EA708A21E9ULL, 0xA383007D18AD01BCULL, 0x377153E4C7B17143ULL, 0x836F8F33785334F1ULL, 
            0xF863CAB30B1CF217ULL, 0x636EB203792C0D90ULL, 0x6B9310BD1AC4F8ABULL, 0x0E40E993E1773C4CULL, 
            0x00749E7DA335AEB4ULL, 0xB421C73AB5634B25ULL, 0x082DAFDF47607C62ULL, 0x0D7DE09F21831D04ULL, 
            0x3F6D7227EB289897ULL, 0x2D4BCC995A982D38ULL, 0xE4ED3E7668831506ULL, 0xEFBCBE591D5CCE95ULL, 
            0x28CAE68010E81760ULL, 0x8CED9A30C20FC02CULL, 0x4093358B55D78197ULL, 0x6E84B5A2B28BD43BULL
        }
    },
    {
        {
            0x62CD16F586EFD888ULL, 0xF28DACFDBCE8F413ULL, 0xE81E7D3317ABCA1BULL, 0xEBDD8A355DA15462ULL, 
            0x76F332B896A4AA8EULL, 0xC89D95054C417F22ULL, 0x5275C32EB7D86108ULL, 0xFA2BBB165A8F626CULL, 
            0x404E549AF223C767ULL, 0x9472AB7F695FE2FDULL, 0x39884F5D6413B152ULL, 0xDD221F3303F5B575ULL, 
            0x738DB95974FEDC67ULL, 0x93798EBA4D871E25ULL, 0x6BC236BF4E4D3C07ULL, 0x10A1A72F25D7831FULL, 
            0x74FA5577B4832198ULL, 0x0D901AA28BF16132ULL, 0xC49091815C33894BULL, 0xF4A184CABC237BFEULL, 
            0x5B4B7EBF7561D2B5ULL, 0x48AAE1E91E71B7E5ULL, 0xFE31363D71F91147ULL, 0xA39DBD9FF52EA192ULL, 
            0x6A1872EABD24CA23ULL, 0x3A9CACFFE766F39CULL, 0xB00DAEDCB4B18978ULL, 0x52D982ACB871D08AULL, 
            0x580C8D16FDAB7EE7ULL, 0xCFA0066E2B9E4F72ULL, 0x7057D8C5B61B3D94ULL, 0xBC5B86A9707D1A2AULL
        },
        {
            0xD9A424F5A210D535ULL, 0x4658C1CE23C04834ULL, 0x32BF65026EBD2F1EULL, 0x4C2F621EC871C8B8ULL, 
            0x7A265808440C42D3ULL, 0x294CD66B5F54720CULL, 0x2CB661277C5865F9ULL, 0x130638265FF73A44ULL, 
            0x901081E4A1AA3C2CULL, 0x47B4B81D0BF82F75ULL, 0xD88BDA5D45BD93CBULL, 0x06774C9D81B83B70ULL, 
            0xB0AD643CCC27BAA4ULL, 0xC271D2CA8301E7A0ULL, 0xA9E0E7E21234E5ECULL, 0xA7CB161DE9CB74C9ULL, 
            0xE8F2D814DB9AFC58ULL, 0x32922F2CCA19FBFDULL, 0xD8D5AA499F397146ULL, 0x67E81B33BA67A1E0ULL, 
            0xE5F72E542B2BDC5DULL, 0xAFD27672BBFE4FD7ULL, 0x931BD40C612CC0C4ULL, 0x3FAB13F468A501CBULL, 
            0x793945A2EA04C96FULL, 0x8A43F17B28422469ULL, 0x2DD9E2225DEEA6ABULL, 0xF9B5FFA6C7440B00ULL, 
            0xF6BC529F03864D12ULL, 0xBBA4E4450D969935ULL, 0x2353283B753587ECULL, 0xB4046FBD7F1DE916ULL
        },
        {
            0xA8BA5D630C34FE99ULL, 0xA7652C24D74FFB79ULL, 0x5B81438513F00051ULL, 0xADA7D5466D5AE1E8ULL, 
            0xD2CB938A24AF4B16ULL, 0xEFC55709AB82A165ULL, 0xEF02A738250E92C4ULL, 0xDF6BBFA05D585BBDULL, 
            0x1C3434D3C924DBCEULL, 0x371C2044E470676DULL, 0x9B88C251BFEA3383ULL, 0x742C4EFCE4A5340AULL, 
            0xB894626CAC1011B2ULL, 0x24238C0628339456ULL, 0x62E902AB899423CAULL, 0xC40764C84D89A405ULL, 
            0xBE010673F3F56A13ULL, 0xE08D36DC8143A231ULL, 0x2345153E37739731ULL, 0xDF891DBB25BD5BADULL, 
            0xE33850BF660ADCEDULL, 0x7A13F7F62CC11516ULL, 0xD081A296C92294BBULL, 0x260165E00A350F23ULL, 
            0xE0CD6AF0A3D3CBD2ULL, 0x1F4B2B4B1238EB26ULL, 0x6317EEC5DF32EBB7ULL, 0x3512225A162FA899ULL, 
            0x28E115E6E4E7D03FULL, 0xB8CFC381043BE56CULL, 0x477F9D40F9DEE6B2ULL, 0xC2CD7D9E1A36753AULL
        },
        {
            0xFFC10494AE46CF33ULL, 0xA1D1384CD1027E20ULL, 0x12F093F1DDCA6E34ULL, 0xCC80872335F6CEA2ULL, 
            0x9D5DF733CD015436ULL, 0xE7CEC7E2D62DFBC5ULL, 0x24F46554B9D6983DULL, 0x3D3D8B5D4B9A5F13ULL, 
            0x1E9AE57AC26A019CULL, 0xB1039DB5E4F16632ULL, 0x17F120C802AD16A3ULL, 0x23E3EA6B635F67AAULL, 
            0x5E729078A2C54ACEULL, 0xC0AEE9DD22B86561ULL, 0x82CDE5EDF49C1015ULL, 0xA49B6BDD2C693FDDULL, 
            0xB652B3CF8937D125ULL, 0x8156EC3D8CD88633ULL, 0x144F9F12749D6B8FULL, 0x442AF1FFA0D7A5CCULL, 
            0xE172A7AEB719ECAAULL, 0x5A62EAB01FC47545ULL, 0x75640DD14D4A8124ULL, 0x2349A97656B50AAEULL, 
            0x92F0BBE14A31729DULL, 0x0CCFBF84492BC19FULL, 0xC6C06497A15C73FBULL, 0x3D644A3E29BB62FBULL, 
            0x3FC10D3F301EE672ULL, 0xE843C4D22F0CD62DULL, 0xDCA31DCE753AA099ULL, 0x69D085F372E70F86ULL
        },
        {
            0x673E38AAF345D916ULL, 0xC8FC8F57B85EAB91ULL, 0xFFC833ACE5A53AF5ULL, 0xEF1C705A91D1AB80ULL, 
            0xF70DC82D196E715FULL, 0x3F7545307D3995DDULL, 0xE1AC39D0151D315FULL, 0xFC332C529A36AED9ULL, 
            0xE3A666014387D289ULL, 0xFBECDD4D49D4C62DULL, 0x67B39EC5DCF1CF6FULL, 0x6BDEE5763580BE90ULL, 
            0xC693DF38C7EB2BF3ULL, 0x429ACC746F208568ULL, 0xA4EE0634BB1438FFULL, 0x935D609FF41B05AFULL, 
            0xDFD7A0A6D2C4348AULL, 0x1B0623A9EE51D464ULL, 0x4B48E0D70F9E5783ULL, 0x6905247E68492847ULL, 
            0x41A4B76DC224A260ULL, 0x9E8335E4E4EF1D7AULL, 0x27A0D5A42DFE68D4ULL, 0xBD434939AC535014ULL, 
            0x6D373CF118385154ULL, 0x0F318FDAB29CE720ULL, 0x4E4C552679D55609ULL, 0xC2811F76796ABE3FULL, 
            0x7C806768F7982B6CULL, 0x2FA965973E625B0EULL, 0x9CF32FD73F95D661ULL, 0x4365690643487F5BULL
        },
        {
            0x705FD53865D62ADDULL, 0x56B2CD11128D8A60ULL, 0x640D745D58D36BA6ULL, 0x44309C2256646CBAULL, 
            0x3F0B6606D57A29CBULL, 0xEEFC0782E84F162DULL, 0x13B8C9F98380ABFFULL, 0x7AB48A6941AED1D3ULL, 
            0xFD6601AC779460D6ULL, 0x63441DA97BCF07C0ULL, 0x52CADAD5674B4769ULL, 0xF78F31B8DD0666ABULL, 
            0x51D4795A029FF745ULL, 0x7EF8DE937CD1DE5CULL, 0xEA62D9DA92BB6AD2ULL, 0x8EF1ED4CCC6253A5ULL, 
            0xFAD83794DF38BC7DULL, 0x3ED3A124EF45534FULL, 0x682F0A514D01E3D1ULL, 0x937DD09A8339898BULL, 
            0x254F6C7757A24258ULL, 0xEC0AEC763D148EC0ULL, 0x285D959D85F91F89ULL, 0x728C1E5575BCCB68ULL, 
            0xB6335734C17B2D91ULL, 0x0C8930C90431172CULL, 0xB7A1937BC6D539EAULL, 0x386167D171F12C58ULL, 
            0xEB181B56D3CD25AEULL, 0x05E37DE3525A3075ULL, 0xB48E85123BD7C7E2ULL, 0xD0D6887DDF96BE94ULL
        }
    },
    {
        {
            0x9862998045636A39ULL, 0x2FD703FF8D9BF903ULL, 0x23D754DBBE009CC1ULL, 0x84E06011EBE923C0ULL, 
            0x3899916E281DC773ULL, 0x262DE33CA90D3DA4ULL, 0x91673D459946B0F1ULL, 0xB07DED37E3EDDBC7ULL, 
            0xB30432F695966FBAULL, 0xD7C41A333ED5BD42ULL, 0xA14149D6B82F118CULL, 0xC24C00AA9DC0F4C6ULL, 
            0x7C23AE43EAA7F3C5ULL, 0x56391B2B2A1300EFULL, 0xF96FC3D2CADAA12CULL, 0x3E4421E1D3486177ULL, 
            0x38CFD62808F625A7ULL, 0x1EE485127EFEE838ULL, 0x3EC7A0BAA836AAE8ULL, 0xF733C8752B933D4AULL, 
            0x7F7BAD4191FF0970ULL, 0xD35BDC1855ED3437ULL, 0x9B0E97B514500827ULL, 0xBF9A8F1216077243ULL, 
            0xC555B20584EE8C41ULL, 0x7113FAA24EB04497ULL, 0xA7C8E123EDC0AE10ULL, 0x6E6021FDC515CA4AULL, 
            0x10D495F54FC46474ULL, 0xB1C9797AFCCA4321ULL, 0x6E409C227EB7BAB3ULL, 0x72C597D76FEAA905ULL
        },
        {
            0x5CE2B7797BB27C1EULL, 0xEE92FF67CA07E7C3ULL, 0x6028C2C728BB5FFAULL, 0x46510B90DFD1F444ULL, 
            0xA823505FACA5E365ULL, 0xEB68F4F69B89676FULL, 0x6DCA08C20F14511CULL, 0x5F678FEB67F82C73ULL, 
            0xDA14B9BBFC68DAFCULL, 0xA662853C0976C2CCULL, 0xFBD860B81462D36CULL, 0x1B09F11FCB8338A5ULL, 
            0x089A5866A268B322ULL, 0x838BB53532F100C1ULL, 0x8A79261AD2A229B8ULL, 0x73ECF0DB58CEE5D8ULL, 
            0x4FF46CC3EA15F74FULL, 0x67C919B741D01F5CULL, 0x26A7BEFA70ADF7A4ULL, 0xBE09671FB64CD549ULL, 
            0x0803298995FF5BE9ULL, 0x6DD63CE4371F02E7ULL, 0x8AE2D682802C5B45ULL, 0x95D04A5EE9A762DBULL, 
            0xE836AB4371D56211ULL, 0xDE4D51D6CF778379ULL, 0x67831E1FBF01395DULL, 0xDFFB305565E06AF0ULL, 
            0x0309FFC36A117304ULL, 0x2DFD37F07916EFBCULL, 0x7763756FCCAC32D7ULL, 0x905450B32C046AA5ULL
        },
        {
            0xE3732FF9EF7262F8ULL, 0xCDFF609C48D3D5D4ULL, 0xBD5306C395E698DFULL, 0x69E57E40613CA7A2ULL, 
            0x509DB5AAFE950076ULL, 0xFB93EB1B76DA491CULL, 0xBE68F817AAFA9C0FULL, 0x07E4D0E2195AC04BULL, 
            0xB9412A5B35E8E6BFULL, 0xB35CA8B9D883EC28ULL, 0x45AAD6A48B26230DULL, 0x4C3EED42DF239AD4ULL, 
            0x9AF5E59E245FA906ULL, 0x685319CF60AB1B0AULL, 0x9CBA84EB6AB9FEFBULL, 0xD3475CD3C64170D1ULL, 
            0x2A9E5F61D24F9EDBULL, 0xB44388E269141810ULL, 0x8C1DBDEC84F41CB3ULL, 0x065F1F6F3209FCD2ULL, 
            0x920A28F01200031FULL, 0x67864E764A84195EULL, 0x68E19717275736DCULL, 0x09941253ACF091B2ULL, 
            0x75CDF43CF650A6CFULL, 0x47227DD54395B62CULL, 0x484840CF836E03CEULL, 0xFBD1DDC43753A2F3ULL, 
            0x0366C01FA18987A1ULL, 0x5E3601756B52CF8CULL, 0x785B9BFB4290E654ULL, 0xF0A6B44EB1C75AFEULL
        },
        {
            0x26AD966F51AF8A34ULL, 0xD727686AE6BE03D7ULL, 0xA1455FF205F2B8C5ULL, 0xC8703BC4E0512AD3ULL, 
            0x8136A9072549541BULL, 0xC831E716F3A56806ULL, 0xE958BB01F6740D9DULL, 0x2C56474C92DCF16CULL, 
            0xF69F9A3A5C7E139CULL, 0x7C32DE75D15D6592ULL, 0x198DFDD03BD3484FULL, 0x501E6A51B1EA2D03ULL, 
            0x28E5BA2201F21D60ULL, 0xAD6D866B604D2BA1ULL, 0xEEE4A811B3A30415ULL, 0x1E475C54CA71B5CEULL, 
            0x0C29B5D5F6A82E18ULL, 0x5A1890BD4D480D4AULL, 0xA7401011E17B5747ULL, 0xC256877326928046ULL, 
            0xFD093E727AD0A100ULL, 0xBB275001F75E9907ULL, 0x0B5B7662E8FD3064ULL, 0xD4D7EF32A0B85021ULL, 
            0xE41475106BEFA89EULL, 0x2A66AD0CA5934091ULL, 0xDC3E4DFC0683AE11ULL, 0x2A25D0FCE779F2ECULL, 
            0xE1B09C79209D1083ULL, 0x7B4B8EE69FAA0CFAULL, 0x70A33ACC0E695672ULL, 0xAD707823F65B51A5ULL
        },
        {
            0x6983C6DB8EE1CDD3ULL, 0x9A7D617557862BB4ULL, 0x6B866125FFA1B6F6ULL, 0x0A6EB8E85EABE0A5ULL, 
            0x87BA5A421299EB42ULL, 0xA0EDBEA1D3A63883ULL, 0x5B465D366C7CF9E2ULL, 0x84FE842BE2E79B06ULL, 
            0x62B34051E0C24F92ULL, 0xD692D6D76F6424ECULL, 0x3AF32866D5FB3F75ULL, 0x47331DDBBD93852EULL, 
            0x45107AC42AC32249ULL, 0x64AED96ABC981C1AULL, 0xB9316C7A24CC5CF2ULL, 0x09E9010F5BFD80D8ULL, 
            0x4890881453370CA0ULL, 0x234FC7B8D66E03F7ULL, 0x31D2F06D3F748078ULL, 0x564031DD775AF1B9ULL, 
            0x2E0D929878500D03ULL, 0x22CA9490FA553B22ULL, 0xCE46E5D547E9BFDEULL, 0xE6894B9A2169888CULL, 
            0x6CB8F51D3767324CULL, 0x6C8F68BE9083C437ULL, 0x4AE971C6D237357EULL, 0x59E5D19501DFBD97ULL, 
            0x3C6159E80D2FB9B3ULL, 0x8972832B86B65A19ULL, 0x02CF9AB19232D7DAULL, 0xC7518D59467D1C4AULL
        },
        {
            0xC53CD76CCCAB7FCBULL, 0x8182B4D9053BA30EULL, 0x2BA06DC576F039BDULL, 0x2BA2CA86819786B8ULL, 
            0xEB73654547DA73BCULL, 0x9639ABDE7F4B17BBULL, 0xF832849097DEB20CULL, 0x190E6A18C530F840ULL, 
            0x578F640839E5ACDAULL, 0xEFB9647E6FDB87BEULL, 0x882C872CB1C3B11AULL, 0x0B9A5AA3FFA151D3ULL, 
            0xCFA70B38C3C2C323ULL, 0xDEF92683D3C78DA3ULL, 0xBFA678914E183B6BULL, 0xA8BA85E9D20FE16BULL, 
            0x7FAB407E9B7D2D01ULL, 0x5C2A2114E924FDBFULL, 0x7818A3279CB5D9C5ULL, 0x38BCCDE5142EF270ULL, 
            0xEC3C987F0086D03CULL, 0xE6B91E8E06B9392BULL, 0xFF7FD12677866474ULL, 0xF5A600EC26442F94ULL, 
            0x8C5D4C487B707FB8ULL, 0xAB29C803FFCBBEE1ULL, 0xCB4767DF4A09D82EULL, 0xB87E95284447BA98ULL, 
            0xF0AF3C86D81A70ACULL, 0x22B872D8FFAA32A2ULL, 0x3C49845EA4272044ULL, 0x58A883C3ABD5D0F7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseAConstants = {
    0x30FA156C6972D710ULL,
    0xB93D6B79BA508F71ULL,
    0x298D8A09716C0E98ULL,
    0x30FA156C6972D710ULL,
    0xB93D6B79BA508F71ULL,
    0x298D8A09716C0E98ULL,
    0xDD7CA5F52465542EULL,
    0x062FF6CA8097A7D5ULL,
    0xF7,
    0x6F,
    0xA0,
    0x11,
    0x06,
    0xDD,
    0x0A,
    0xC1
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseBSalts = {
    {
        {
            0x52D92446D36963DEULL, 0xBF91E77E3094BCE6ULL, 0x01E1EC576D3B83DFULL, 0x6110AC3BF910FADAULL, 
            0x9A638DDEEA6A5BDBULL, 0x0EDE960911B04AC4ULL, 0xCF226B1768E3C8A1ULL, 0x38E33E8B14FCB88BULL, 
            0xBB5A73CA6058428BULL, 0x6B011B8BE331EA47ULL, 0x239208B331A51C25ULL, 0x7559D3F5B6E6EE86ULL, 
            0x4ACF6FB84901F80BULL, 0xA5A093F62F9527FEULL, 0xA36992C440DB6C68ULL, 0xC2CC8F1B81D2D297ULL, 
            0xD554AD9A114066CCULL, 0xDCFFDE142BF6F3DDULL, 0xE67193469492939DULL, 0x0124DD6C453AD120ULL, 
            0xA2CE3FE8C1433362ULL, 0xEE455651496B9183ULL, 0xE6AB4717AF9D0D79ULL, 0x887BA0AB5380945EULL, 
            0x2168592DD3AE1466ULL, 0xAD35DF809E1D2639ULL, 0xE38F602A806D71DAULL, 0xFA9855228C8FF97AULL, 
            0xA86A9382C45EA64FULL, 0x49F9AD7C7323202CULL, 0xA028D52A4DA1FA00ULL, 0x52659355EEAD9E10ULL
        },
        {
            0x9CF161F2048B1CF5ULL, 0x17276295FD45AE16ULL, 0x9BD2A44ED21A5C5CULL, 0x10081CF45C6FFDBBULL, 
            0xC4DC2668C0249BBDULL, 0x216B853DD9286535ULL, 0xA5BDDE1A54120514ULL, 0xDD2BE0DDE3E19112ULL, 
            0x595207CFFB24B0BCULL, 0x0E0DF0F7588976D8ULL, 0xB4707685B1261CB4ULL, 0x7F2A7EDAB6F2551BULL, 
            0xB63DBC345F8D999FULL, 0xFEF3AADC885A3555ULL, 0xBE4BF09E94B46907ULL, 0xC56A35E9DD6C2F3CULL, 
            0xFEB848CB75EE8417ULL, 0xF9CE723B500AEFAEULL, 0x1F1AFCAFAF5E0D7AULL, 0xD34A3FB5F8A7ED4AULL, 
            0x337E17D1B0A45DE3ULL, 0x51C1BD44387C8378ULL, 0x2A97C1C8E5A1FFAAULL, 0x5BC7A1E0EA4AD989ULL, 
            0xBA50CF14EC74F8DEULL, 0xAAE17ABE7C9B70B3ULL, 0x379E1E1302D1EF6AULL, 0x75BD5E952DEE5AD3ULL, 
            0x260188DC2D72E09CULL, 0x14C381EFE5DC9A03ULL, 0x933AB8943071D799ULL, 0x19E66DA203583826ULL
        },
        {
            0x48DDEEE55D0AD603ULL, 0x2316A8863C70DA24ULL, 0x2FACB1C191446750ULL, 0xBE971A643542C3F4ULL, 
            0xCB93743623A9B47DULL, 0xFAFDE661E89BF758ULL, 0xAD962046E47AA8F7ULL, 0x08381B045490A218ULL, 
            0x0161AB39CA4073DBULL, 0x74F9472260C6CE64ULL, 0x4D766B899285868AULL, 0x9FF5BEF9D260EF45ULL, 
            0xCA91E554142279F3ULL, 0xD3CAB09266A00D73ULL, 0x480D53FD56C40A4CULL, 0x547E71EFB84C67DDULL, 
            0xDE7EBA7431B68DD4ULL, 0x26F5B6EDA46E5CBEULL, 0x8148DAD4D1754614ULL, 0x30843FC1D083B390ULL, 
            0x9A728E57C8DB814BULL, 0x9AFE2149678E7DA1ULL, 0xD63CC54AAA080F12ULL, 0xCF7E3A89B2A9C2B6ULL, 
            0x795638B7287F6A2EULL, 0x1710989E3C1D261AULL, 0xDF171C3DAC629C24ULL, 0xC916E89C5D63DA04ULL, 
            0xE66EF42DD16E1E42ULL, 0x6BB1969A1AA66B6EULL, 0x18375D73AD39F398ULL, 0xEAEDF7010720A392ULL
        },
        {
            0x8E1C5E69D3DD2FC7ULL, 0xA9A379AC2721460AULL, 0x3652C9D52DBAD8EFULL, 0xFA4349632D64B74EULL, 
            0xD7F58E81DB65D4EEULL, 0x96FB71A705A9B202ULL, 0xAE6A49814A7AE9C1ULL, 0xDDDB90255C785035ULL, 
            0x5584936C593A8A9FULL, 0x8664E345FA368219ULL, 0xC289097AEB13D8CDULL, 0x184AA952D4F3350DULL, 
            0x016674A0DED58389ULL, 0x751FF1109DF88D34ULL, 0xA857BCBA2CAAD726ULL, 0x02110B7E92BADFD2ULL, 
            0x19018D7E7CC4E9FBULL, 0xFA1848EF471F4859ULL, 0x13E21A4F892E32A9ULL, 0x369885B60C5DFFAFULL, 
            0xE1F91AF2E3DDC0FDULL, 0xBC24820144AD6620ULL, 0x8DD8E8A2309488D5ULL, 0x7EE0F8A402CCE7ECULL, 
            0x7345A3B155D862B6ULL, 0x0E5C9B9CE1F15939ULL, 0x1E6660A8FED1C7AEULL, 0xF7A5AE38F1C30FFAULL, 
            0xE4E1AF9FB4E4A896ULL, 0xC78095D819C63490ULL, 0x9A1858CCCCEBCE46ULL, 0xF4403CE4287292D1ULL
        },
        {
            0x952951F6386DDAE7ULL, 0xDA5DDC63C8501E4AULL, 0x517EA7E1492C1CFBULL, 0x718B3212923F3AE5ULL, 
            0xCF00657FFDDD1204ULL, 0x60188D3395C3F4EFULL, 0x678585E47DDF7B42ULL, 0xB6CF315360C516CDULL, 
            0xA98C582AA4FE145BULL, 0x45E5ECF6EF05E6BFULL, 0x737B32352DA48E22ULL, 0x907715777504BBACULL, 
            0x9D1DC43DA4DB0924ULL, 0x7A4CEC31213969D3ULL, 0xAE7960783DC6A16FULL, 0x49A9624711AEEF7FULL, 
            0x224A7F130EF0D2E9ULL, 0x7437985807B77A70ULL, 0x515F30C82D2E3DBAULL, 0xA8512A0B2598B713ULL, 
            0x94B4E5ABA792D541ULL, 0x9338C920A5594727ULL, 0xD803222E563509E0ULL, 0xE7D0F98F3715FB64ULL, 
            0xA1ED75C32C061753ULL, 0xA7C56692F35DE839ULL, 0xCA6A212B22C167BBULL, 0x536442D63C488CE3ULL, 
            0x76EF0BB55313A162ULL, 0x2F09616DD6FE82C8ULL, 0x04A0050EB6BCA348ULL, 0xCFD5CB57B056BDB5ULL
        },
        {
            0xF87650C4B7B79854ULL, 0x4D566BA3235DD4A8ULL, 0x104A52BE39C02247ULL, 0x89A4C18B36F09B1FULL, 
            0x23FC850FCD30BF7FULL, 0x50260182EA496EE7ULL, 0x516E270340CF6843ULL, 0xE340B30F1038FDCCULL, 
            0xEBF68BD7C19773F6ULL, 0x4DB948E90FC35215ULL, 0xED090CD094C92B3DULL, 0x3874E7F922C9F8D4ULL, 
            0xE03A76CF21425115ULL, 0x56F959F44965AF10ULL, 0x275226A4511C73BFULL, 0x20735DD4E2F1038FULL, 
            0xA0FE1F44C4C7C8D1ULL, 0x4264484904B08626ULL, 0xC90C8671A2E5ACFFULL, 0xDDA4F609CAAFE235ULL, 
            0xD74B1213A50F9742ULL, 0x180ACD7C2750D0C8ULL, 0x2ADC23F8A1D388F6ULL, 0xEAB440D89F2D2B0BULL, 
            0x7E7276810469FF4AULL, 0x1E5EC12C5E331D62ULL, 0x1E3A7123B2345B40ULL, 0xAADD549870E8B0EDULL, 
            0x4772D7736D5985A2ULL, 0x1E3ED6EB53338783ULL, 0xA2BCC775087A37E2ULL, 0xC2D51367E30567F1ULL
        }
    },
    {
        {
            0x055DF1015EF45E4BULL, 0x0C234F8A723C8533ULL, 0x763D0517AF942A6BULL, 0x9F6B6FC8130C526DULL, 
            0x2EE4082D16AA2678ULL, 0x323914D762F282F2ULL, 0x272A340D61963572ULL, 0xAA81E7AD735DFED2ULL, 
            0xE222924823AFB5D5ULL, 0xB6D966B6198EE20AULL, 0xEF498B774074D7AAULL, 0xC7F871AF4A088EAAULL, 
            0x0E4E4E508A69EFF0ULL, 0xFABD5D17E7A1BC6DULL, 0x8A0C527C7A509AECULL, 0xA1C3E95F131A5E22ULL, 
            0x5B1FB23AE7D9B625ULL, 0x5817D33AFAB05071ULL, 0x47C605994CB06FCAULL, 0x938B1024D83AA1BEULL, 
            0xAE33EBCAC910CFE8ULL, 0xC5616760E07B18F0ULL, 0x9D8BD393B6A5715BULL, 0x9C87112CC03F13D3ULL, 
            0x5B250A7F32C454A5ULL, 0x18600D05597AE597ULL, 0x31B9613D195026AEULL, 0x8867714FEE903659ULL, 
            0x54CCE1FACC1D922AULL, 0x1E11E2FB37B5A0E1ULL, 0xB6D6F1DC37DF0DB5ULL, 0xCB85DC2660C3FD33ULL
        },
        {
            0x5FC3629664D87D81ULL, 0x43E6427352C2B8EAULL, 0x1E7EA032C4FAF8E7ULL, 0xB2BCD8217B2F476AULL, 
            0x0569A158C16844D4ULL, 0xE3C455FBBBB90E86ULL, 0xB9BCED643E8DADC5ULL, 0x4EA07F06B566E31AULL, 
            0x50E2E5D619D9A40EULL, 0x9CBF43B7E9BE240FULL, 0xBA9C75AF19789B63ULL, 0xB61ED08B685DB5EEULL, 
            0x324E4F78DF54CF53ULL, 0xF56A1F49D5002EE6ULL, 0xB25F3DE8676323B5ULL, 0x19DCC7D4241A5E9DULL, 
            0xDB7A78A4679725C4ULL, 0x54C54AF6B4617B34ULL, 0x4F298C761DFD64A8ULL, 0x317AA31C13C847C4ULL, 
            0x943D52BA025FEC13ULL, 0x30110794DDCF0A8EULL, 0x414588C0DC49CEC9ULL, 0xDC3CE4F70B763C32ULL, 
            0x16ED214AF5E68BC4ULL, 0xFBDC1892EDF2D836ULL, 0x6B87C143DC0BDA99ULL, 0x05913B3954192A3BULL, 
            0xC55E4E2A5FB2E263ULL, 0x0844160D1696F268ULL, 0xEFD5782F1D7EB862ULL, 0x6E65044AFBB16403ULL
        },
        {
            0x388308698F3746FFULL, 0xC51128082AFA6894ULL, 0x3F7ED7CFBCBA3B7EULL, 0xCFC1F69050F9FF11ULL, 
            0xCE75C93229C83B75ULL, 0x62B132D03997DCEDULL, 0xE6234B691211FB5CULL, 0xC43F826E74231DF2ULL, 
            0x0DD187918DED1755ULL, 0xBFC68125A98D9687ULL, 0x9900CC26B1EAEA50ULL, 0x14AEBFA1808E176CULL, 
            0x80AB06EEB66A8B2EULL, 0x275B96A24BDBCB51ULL, 0x2F868A109A9E18F2ULL, 0x4733CF22C0EE3DA4ULL, 
            0x7FB7556D007E23B0ULL, 0x31233956DDA19F23ULL, 0x4B30F858680C1CC4ULL, 0x2459CBDA8611108AULL, 
            0x796C98E02EDEC178ULL, 0x24130480AB4A5C8BULL, 0xE78D3F63612B4E69ULL, 0xBC9DF22BF0EA505FULL, 
            0x4FD4D79980C7DBEAULL, 0xBF2FC61C33FEE111ULL, 0x63D510489E2644A9ULL, 0xECE5BD69D72BD09FULL, 
            0x6E3336972393DB62ULL, 0xDF5DC184EE2CB388ULL, 0x20236CF5548B6459ULL, 0x4A09675B99082028ULL
        },
        {
            0x0364736C5E86D8BDULL, 0x42B203667002538AULL, 0x49838C0DBDC57E77ULL, 0x897865CF80568998ULL, 
            0x5635B30983A5C423ULL, 0x9822E9B1D319C7E0ULL, 0x141B783D8BBC903CULL, 0x982BA4F5E4CF46AAULL, 
            0xB01D3533F2C49ACEULL, 0x5F9D7DCF87A23FE3ULL, 0x2CCB836F643D3484ULL, 0x1012647A5C7FB7A9ULL, 
            0x32CFF838BD4432E1ULL, 0x28C8BDBC7D04C731ULL, 0xBCC5FDE9C15E2DB8ULL, 0x648A451307CEFCC1ULL, 
            0x0E9B8EE620CD6F60ULL, 0xC27FC3B9798D7B77ULL, 0x9C3706078E2705AAULL, 0x18D733B74C65560FULL, 
            0xE7A1384592F24269ULL, 0x36CB0316D8B72B11ULL, 0x5F439DDCB30655D5ULL, 0xA90252CABB3324B5ULL, 
            0x812423864DE67CB9ULL, 0x6A59328A05968219ULL, 0x5CC577869B679495ULL, 0xCBB971E9E4EDCE69ULL, 
            0x3A8E3551B3B642ADULL, 0x8421E8470104BEC8ULL, 0xCC15AE7DDDDD5636ULL, 0xACB58B00A9776517ULL
        },
        {
            0x2FDD91BE3892B42FULL, 0xCB66BD83F33501E9ULL, 0xCBBCB28619071515ULL, 0x9C614678AAA2907FULL, 
            0x82BA993596AD4A77ULL, 0xC79E8E964450A475ULL, 0x6ED65FDC7AC9A87FULL, 0x8C585F50A29058BEULL, 
            0x9DACB86190DCFDC3ULL, 0xB9BB89BF3FF764C3ULL, 0x80620E4EE3D02603ULL, 0x71C351825D97B964ULL, 
            0x5B06825027CA5CE6ULL, 0xB74A256C92CA8CCFULL, 0x35588D5140015F28ULL, 0xCF626840B4563496ULL, 
            0x5E7AA279450BFCCDULL, 0x553FCAB343416F60ULL, 0x9B668BE0BF51CE4DULL, 0x41E878134E5FB9A9ULL, 
            0xBFD6CD28C23CB09BULL, 0x003CD0666192324DULL, 0x318671D893DE18B5ULL, 0xFE7F2EB3155F06D2ULL, 
            0x39CB2343038E9418ULL, 0xEF5B09691CDB89EBULL, 0x14E0A566D9F4A225ULL, 0x61BB03FADE6D867BULL, 
            0x49499716A115529AULL, 0xEE8445D31F1277A0ULL, 0x5F28BB756BB4824FULL, 0x261AFF7D46BDB842ULL
        },
        {
            0x008682FEB4CE6FD2ULL, 0xC44DD87A2A13A72EULL, 0x104C09700E72F898ULL, 0x48F3E8B87B2A87F8ULL, 
            0x1DFB71F807144195ULL, 0x5B377979A27E7F79ULL, 0x7573A0BAFC566AC9ULL, 0xB21655D3613E5ED5ULL, 
            0xF2EF7B00F9CB7657ULL, 0x31A534162AF250C0ULL, 0x32D1A68EF12537AAULL, 0x348B4C4BC0447FFEULL, 
            0xFA02E30562E3E2CCULL, 0xD16AE64164A3C209ULL, 0x5C0B0722ABC39B41ULL, 0x1494115FCFFD9ECCULL, 
            0x95C181FA6C64646FULL, 0xDBDFDF6CC9923CACULL, 0x94367C16A89696C6ULL, 0x3782CB9E4390D250ULL, 
            0x2F1612EE3E79361BULL, 0x97E8A673862E81F5ULL, 0x35839929B7A940E3ULL, 0xAEDAADA55E5E9FC3ULL, 
            0x24E31ED367C0F48BULL, 0x4C60FDC9DD93546EULL, 0x66FB26453164411CULL, 0xF5862462F5B35EABULL, 
            0x5CF603F2905302FBULL, 0xC7C46D03F2BB144CULL, 0xA54FF6DB699D8B34ULL, 0xC648D99328766C4BULL
        }
    },
    {
        {
            0x517D5DF1112F0CF1ULL, 0xF2F1AAF12C996C86ULL, 0xEFBF1CED265C5752ULL, 0xCED8E2315367E1C3ULL, 
            0xE482255B09A795C6ULL, 0x765BF60EBDC0B208ULL, 0x3707BE61FD385B6AULL, 0x7C4F674C5154B992ULL, 
            0x2706922A054F9E8EULL, 0x700C165B7A4AFC2FULL, 0x04C410A4DCBEA100ULL, 0xC29FE14B59B51BDBULL, 
            0x0C54A945D0C5294CULL, 0xCF10A1A4FA2DA85BULL, 0x7F77E1D03791F35DULL, 0xD60414AF9DEEA265ULL, 
            0xADA05ABD20CDC817ULL, 0xE7D32DB80262C0F4ULL, 0x949E5B44084B6AB2ULL, 0xF17AD0BE283B8417ULL, 
            0x820B46934D2F1255ULL, 0x371062B03734C2F5ULL, 0x6AB089D7F1A0AF8BULL, 0x7AD5FFFB509AAC18ULL, 
            0xAFEA8D8B3359E36BULL, 0xB9125008251CCE47ULL, 0x029689E554071CB3ULL, 0xE5C6AD91599F0AA5ULL, 
            0x6508452D30393250ULL, 0x497857F4A147506FULL, 0xA22DA3B8C4AB4A41ULL, 0x648B186AC225A563ULL
        },
        {
            0xD2FEE4000CAA63B1ULL, 0x522185C1FA412900ULL, 0x999D14C30BFD3CA2ULL, 0x5F003DC433EFD1CAULL, 
            0x02734395583F7971ULL, 0x0696E8F5D6FFB7A3ULL, 0x5936ADDB4A975B66ULL, 0x0A570737C6F8DA22ULL, 
            0x31B4A6D4811A8D5FULL, 0x0B6D3D6C793B5F67ULL, 0xE323F3052720160DULL, 0x233CDFD91D5262FCULL, 
            0xD4B11FF7D89E0816ULL, 0xD0BD35ED32E72F43ULL, 0xE0FF7B5B05447D58ULL, 0x2445A74BDF44723BULL, 
            0x671746118D007F70ULL, 0x91C42329B5814597ULL, 0x8F32CD65D2C4E4B6ULL, 0x18EF6CB0C9FE0DA6ULL, 
            0x6F58CEE0A8169604ULL, 0xFCA41720AED5720EULL, 0x8E56E4D767710639ULL, 0xEDBACA23A627B150ULL, 
            0x511716E7FEBA6834ULL, 0x872C8E9257E04812ULL, 0xEEF6F48ADF5446D9ULL, 0xEFFB9E6E227DEF46ULL, 
            0x3ABF3B0BFC98E991ULL, 0x76CE53F8522EEE11ULL, 0xE7C14F8924377715ULL, 0x9E1EA831559B0EC9ULL
        },
        {
            0x289EBA6CBD8D2B6CULL, 0xAB2D0EE755F262ABULL, 0xB73510D0E873DDBBULL, 0xBA99FA8DB7456694ULL, 
            0xEEE17D7CAD13B7F1ULL, 0x653A12A607F9A220ULL, 0xAED6491B69994EF5ULL, 0xF086CE0C689661F6ULL, 
            0xF99643F112DD2B93ULL, 0x49BDE19ADD4ADB3CULL, 0x60E5D321B1406A72ULL, 0xF5B0489720080FE5ULL, 
            0x76EBF2D85EBDB23AULL, 0x0907A4EDE6F0991AULL, 0x3B7E7F4C277683ECULL, 0x9ED384DD9F4EF584ULL, 
            0xA86D28A1BA5B60F4ULL, 0x22BEEE59D7CECEF1ULL, 0xDF5DFCB2883F9A13ULL, 0xC27A19B8202084C6ULL, 
            0x86FEFF4D5B35631EULL, 0x4905CF2C1ABD9C11ULL, 0x8E56704D5972673EULL, 0x6AD8F96D07FC7BA7ULL, 
            0x9DF625055797C449ULL, 0x70B9013D5DC8F410ULL, 0x3B75FE7609284AE8ULL, 0x0EA301C717B52055ULL, 
            0x692F6622296375D4ULL, 0x678CD969EBC8943BULL, 0x0D1F8ED42C6ABE0AULL, 0x8E1FAE0A9FC345EEULL
        },
        {
            0x56FD04B9162B8879ULL, 0x151B4DA107ACA7F8ULL, 0xFCB884B6C0D63035ULL, 0x89040C5406E9E597ULL, 
            0x6C4F3E9FF6FA58C8ULL, 0xA888DCB4AEABF2D7ULL, 0xABC2343E0AD74051ULL, 0x2EAE8C35FB14D240ULL, 
            0x1FCEB5E87542AFD6ULL, 0x8460A7AC97169245ULL, 0x253315B77BCDBD81ULL, 0x3BC18C3F595148F8ULL, 
            0x8A9E8B55455D66C2ULL, 0x70B2B48036EAE4BCULL, 0xA5179283A4EB4AA4ULL, 0xF11B513679634AEDULL, 
            0xEFAAF811EC480F2BULL, 0x67EC6F5554B44D44ULL, 0x92423AEB90137DCDULL, 0x53CD5C77352D7A2BULL, 
            0x506C7136EF92B5FDULL, 0x99440F1E04918600ULL, 0xA434CF4ADDC2EB04ULL, 0x6FA0559CA510328BULL, 
            0x69DC0EFD134582C0ULL, 0x39515D33963835B9ULL, 0x8BABC09666C49833ULL, 0xFE45DB59DF8301ECULL, 
            0x547ABB4C196C4675ULL, 0x45EBBE47AB2CAE3BULL, 0x8AC69FADDFC15263ULL, 0xCBD84DFD60BC19AFULL
        },
        {
            0x1528F159E76DC497ULL, 0xFB71D4C31AD2E2C8ULL, 0xAECB6E3F6C0AB2B6ULL, 0x5BF7682DC674AEBDULL, 
            0x1023089ECB47714CULL, 0x2AD7C01C002880FAULL, 0x48ECC8544D8D533CULL, 0xF0B03DAF414DADB7ULL, 
            0x7427D721888995A3ULL, 0x68ABE00DD66B93C8ULL, 0x6BCFBF124CC6FEC4ULL, 0xDE69022EBBF60305ULL, 
            0x18056F9B80C0BB46ULL, 0x7062A1600DD316E0ULL, 0x40336E88EC4F5C2DULL, 0x8D02467903F3AD39ULL, 
            0x8394908FBC674454ULL, 0x200A8E17C4FC7566ULL, 0x3073F74655555BC8ULL, 0x5DC338C90318C61CULL, 
            0x8590360BCE62B240ULL, 0xFE458E59A683ADDDULL, 0x94B0F904E7CD1979ULL, 0x56BFBDD377AAF06BULL, 
            0x61F1BEBAF380A945ULL, 0xDF79D630AC835B7BULL, 0xA35478C04E061CD3ULL, 0x05C5B0F00C09880EULL, 
            0x53DAEC7215C40EADULL, 0xE7AB95A5C9423438ULL, 0x77B43F9C8745D237ULL, 0xE59DC44046D9DF00ULL
        },
        {
            0xCE7EFA997311B100ULL, 0xFF485763B79681A8ULL, 0xBCEFE7EF6BB98742ULL, 0x14598936D5648751ULL, 
            0xF10892F4D5577E53ULL, 0x2067BA1156D243A6ULL, 0x2FA6FED036B80AF3ULL, 0x7E731213BBEFAA21ULL, 
            0xF4487ED0FB916290ULL, 0x26868A6C3491E10DULL, 0xBAEA3792B7A51FAAULL, 0x1F73CE14A97BCB52ULL, 
            0x30C3C130F3405DE6ULL, 0x040F151E06BC9A42ULL, 0x26883B9C352FE681ULL, 0xA7058C52C7DA2387ULL, 
            0xE3FA95BF82733EAAULL, 0x4A912E1516E5EDDDULL, 0xC16666DC84563A16ULL, 0x856BDD908BEA6B7DULL, 
            0x693DA2A6118867F4ULL, 0x3EE3580084EFC7C9ULL, 0x703305A0CBEECDF2ULL, 0xC27351C97930940BULL, 
            0x375493A22D71803EULL, 0x81EB3342BE00BF1EULL, 0x21AE77A3A4FFDCEFULL, 0xC300E8EDC1103CEFULL, 
            0x902DDF58486F7719ULL, 0xA91D45FBB3A8DD3DULL, 0xAEEAAEFFA37D3295ULL, 0xF66274829DDCD55FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseBConstants = {
    0x0E47F51C5509D825ULL,
    0x2726A70053BEBB7AULL,
    0xC925A28D2B01FCBDULL,
    0x0E47F51C5509D825ULL,
    0x2726A70053BEBB7AULL,
    0xC925A28D2B01FCBDULL,
    0xF0ED5E465C6FA3EAULL,
    0x03530AC8817123ADULL,
    0x8D,
    0x7A,
    0xD3,
    0x61,
    0xE7,
    0x8E,
    0x7C,
    0x7B
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseCSalts = {
    {
        {
            0xC63E1B10817CD8B0ULL, 0x76CC1B349EA0EAC2ULL, 0x62F2EB127E0979E5ULL, 0x843DEED3F153C439ULL, 
            0x8E4377A6973C67D2ULL, 0x8B895DBD8C5EDA78ULL, 0x2F5D5CA9674497B3ULL, 0x2E14A54B98B04B73ULL, 
            0x207BA9FC87868E6EULL, 0x4C18C7F8D8A3FC2FULL, 0x7A3C3642A68BCCAAULL, 0x8C50E5C060186614ULL, 
            0x797EE32733377116ULL, 0x3B1A6EF0DDA7542DULL, 0x311029DA982BC344ULL, 0x319CEF7F2AA5B714ULL, 
            0xD038D1E897EB0C7BULL, 0x39D76D19ED298DACULL, 0x1BAC6E00B4315675ULL, 0xBCC3275DFB13D125ULL, 
            0x6D65AFCEB7BE7022ULL, 0x47E3DFC5642CFE24ULL, 0xE570ED091F0A2C48ULL, 0xF722E9BDBE64A47CULL, 
            0xCA630C82C4D469CBULL, 0x0ED93EC958BBCE1EULL, 0x1B1F015355EF9FD1ULL, 0x9110BECE388F2286ULL, 
            0xE38508913DCE8A24ULL, 0x5091C3FBA2289507ULL, 0x788B976B20ADD055ULL, 0xD6BB5E19B1DCA03BULL
        },
        {
            0x9458508D7A9152CBULL, 0x316A036293B4D485ULL, 0xC133A88F5C27C640ULL, 0x1014071158154953ULL, 
            0x0580C1404471DC4BULL, 0xD0956F570CE883B1ULL, 0x924D835A2571CF3DULL, 0x32FCF4EFE5C84FAAULL, 
            0xBCB2E014C68414A6ULL, 0x6AD99ADDE1B9E110ULL, 0x25558E95B01FFB8AULL, 0x66F7DF32240CD38AULL, 
            0x25A8E11E053E1865ULL, 0xD8F097968B14704BULL, 0x8D8F8DB880CFA752ULL, 0x20D37773ACA1B588ULL, 
            0x3BE025F7995C576BULL, 0x81AC917159628AF3ULL, 0xA2E1133394BB0462ULL, 0xE8792904ED859662ULL, 
            0x59CE47C046DF7B11ULL, 0xABA632ACFD2C2F8EULL, 0x0793B261202016C9ULL, 0x848F4A2C4E88A6C9ULL, 
            0x72AB73934F425245ULL, 0xC4939C56A7A869FEULL, 0xF4EB612D9E8921E4ULL, 0x0D02972CD11F9681ULL, 
            0xB2B4C2C9DF1B4A40ULL, 0x3A3663610AC32B9DULL, 0x3C1F4ACB87476FA3ULL, 0xA215A1B2B99DDE61ULL
        },
        {
            0x0F7E872E5A99CC03ULL, 0xE786C1BFDD77511FULL, 0x3C40203067536382ULL, 0x6BBB71455E1FA2B9ULL, 
            0x08830FFAC03E9C5EULL, 0x1297800CBBC341CEULL, 0x9F3B6BB850DD238BULL, 0xAC7DC1F103561099ULL, 
            0x09B7CF8337822E93ULL, 0x983B8E71C0C28619ULL, 0x95D1EBC028AF4544ULL, 0xE9EDAD5E6202ADFCULL, 
            0x5D860AD70E8A3C23ULL, 0xF86E491C2352DA1BULL, 0x9B293CEDA58FCA80ULL, 0xFB1D8062BE9790F1ULL, 
            0x8BA627F06F4BAB68ULL, 0x8BD94686F84192BBULL, 0x1E0D4C3C86871A1CULL, 0xA2AD340590757431ULL, 
            0x81BDF7532C4E4AF3ULL, 0xD5794F29DBA392F1ULL, 0xD289D4132F404B5CULL, 0xA6EC5377897AA441ULL, 
            0xDE293A66FA3369A5ULL, 0xAEE421431162DAF7ULL, 0x5BB61BD1C63798C6ULL, 0x4835DF87F22F09BCULL, 
            0x815A7C55921083E3ULL, 0xC2692C258486851AULL, 0xB233458C08955CF2ULL, 0xFD7D3C9B2C70A9A6ULL
        },
        {
            0xF24A2555F8C28587ULL, 0x091BB54677BA4452ULL, 0x1E5FF45D7DFABDDAULL, 0x289A71919F4E2328ULL, 
            0x1442155996A4F8EAULL, 0x738E9E8FCDAAC498ULL, 0xF53ECFD3B3AF43B2ULL, 0x7EE596DDC9D2731EULL, 
            0x84469EEE74EF7432ULL, 0x1A531DEE7CAE14B8ULL, 0x909EE6805BCE7078ULL, 0x67989E2A026462FEULL, 
            0xCD9ACD2D27CC1D86ULL, 0x41B18D7F8B167DA6ULL, 0x42057C8D0D649A8DULL, 0x30F6363C168AC4F7ULL, 
            0xF24831D635AFFB8CULL, 0x95D2DF67210A6A69ULL, 0xDD39284E17ACEDA9ULL, 0x307A3DD0213E4E04ULL, 
            0x874B4617E8607B26ULL, 0xA3BA8EEF3334CC90ULL, 0x734CE89D62E41422ULL, 0xC1CD4EDA40D9EDEDULL, 
            0xC675C5A3ACDFBEE0ULL, 0xCFF4D47859798CB2ULL, 0x1D470058E32C5C00ULL, 0xC310589B622EBCC5ULL, 
            0xF9D49D3EC9503145ULL, 0x70343FDA2E1E50DEULL, 0xC1E09D04E17850CCULL, 0x44D34736AA13FE16ULL
        },
        {
            0xF9274CC1D2C5C68AULL, 0x87EB33D5EDD60FAFULL, 0x224E0E0E46164F4DULL, 0xE25E1582E173DE52ULL, 
            0x8F44ABE30CA0E223ULL, 0xA0243E2F98DA500CULL, 0x9B9243785570ADE5ULL, 0xD9260DC5637AAC18ULL, 
            0x500376B5F8C99067ULL, 0x079CC6E59B614F9FULL, 0xC49180DBF5F55D74ULL, 0xA70357FC21EF58A2ULL, 
            0xD0ACD20B917F8BBFULL, 0x2147B30F7DD1A035ULL, 0xC6EC4D526BCA7CA5ULL, 0x322211F9A15BF9FEULL, 
            0xFA3DD7EA83AEA473ULL, 0xA5C22C8DE024A2E9ULL, 0x92F0CFF018F8A6AEULL, 0x6E3CDBDA3188DCF9ULL, 
            0x6B8FF2CE6C638B6CULL, 0xC15AEFB2B70FCD37ULL, 0x21BEEB03B42BC356ULL, 0x25D54F352CFCB249ULL, 
            0xCF96B695E87D62F8ULL, 0x55664A4084857EC9ULL, 0x7866E664D950FC2EULL, 0xBC6A847EEBD95DE8ULL, 
            0xBAB31F0EE57B8734ULL, 0xF383A4AF14443E5BULL, 0x6A4FBFA7A98729A2ULL, 0x0FBD8CB5C0B01AFDULL
        },
        {
            0x7AE3EFBE09F2FD4BULL, 0x2F753BCF17200D8EULL, 0xF8959426AA75CA20ULL, 0xDE1CD94778ABD741ULL, 
            0x7EA7DD6ADB1B3D60ULL, 0x28FEAE363F029AE3ULL, 0xBA102D25769DF7C7ULL, 0x4A97AC191411A8F0ULL, 
            0xBD996D19542E21DFULL, 0x1AD5FE036CF110C5ULL, 0x2C96A4F14B175BBDULL, 0x61896F459D516DCFULL, 
            0xF57E508A5C3429CDULL, 0x498654223679FE79ULL, 0x7F962C5F4EF161D2ULL, 0x14C7507CFB2C1D1BULL, 
            0x00217F2CB5C94CDCULL, 0x12365B20A470CDE8ULL, 0x92EAD302C2368213ULL, 0xAA88000C78514775ULL, 
            0x8D6C1D7E49D72FD3ULL, 0x9E21FA881241B255ULL, 0x0C6621E51AAE1E4AULL, 0x3FEDE8E79F25DC74ULL, 
            0x890E3BB5262098B9ULL, 0x1DE3081796C1E628ULL, 0xECC29D6E182CE248ULL, 0x45CB985987891B93ULL, 
            0x7D73A707BD08F8D3ULL, 0x21930760D4633101ULL, 0x8E188760F205F653ULL, 0xC2C5EE6D923F940AULL
        }
    },
    {
        {
            0x88CA3C45EFF6EF90ULL, 0xF82971D53C4B54EEULL, 0x07C474CB4D36C227ULL, 0x669E7222E4B1BCF4ULL, 
            0xA8823836676789DFULL, 0xB34E522077FF9CECULL, 0xF55FDC2553855669ULL, 0x526B1DAA54C40E8FULL, 
            0xB86072707633C6F7ULL, 0x29AC11684325CDD5ULL, 0xD289FFF494F118E2ULL, 0x1DBC28ABE80F627BULL, 
            0xE1AD874D866EF6E4ULL, 0xF77377C13B41CBFEULL, 0xF67AC53A9F182744ULL, 0xB18D7C719149C3E3ULL, 
            0x8B9A512AD1C01252ULL, 0x5DC650C292DACADDULL, 0xCF3C3B68FA5078A3ULL, 0x4CAD121F6CE6D728ULL, 
            0x8B9F6FE9DFE732B2ULL, 0x9D4E532FAC4382D6ULL, 0x87768B3EACEBC29BULL, 0xC8977BCAA204CF2EULL, 
            0x419C0BE24A50215DULL, 0x40A65D3FD93503A4ULL, 0x2057CEC54836E533ULL, 0x4EC9559C1E4A9F23ULL, 
            0xC0789D8F4CDA2641ULL, 0x3C4A79EDCACDDC90ULL, 0x76B02B64692BEB58ULL, 0x449B25EC3CB25B0AULL
        },
        {
            0xD57F96DFFBF53B2DULL, 0x3A9B87FF990F619CULL, 0x0B5DDEC07DF50082ULL, 0x32EA2E11CEE6274BULL, 
            0x7AFB1933639BB956ULL, 0xE0B04CDB95B52098ULL, 0x966200ED15EE321DULL, 0x367C0A6E9B6FDC7AULL, 
            0xF1E5B23661832EDFULL, 0xE7C0583125697622ULL, 0xB7E729FEF9574D22ULL, 0x69EE782211663420ULL, 
            0x4A204140BF29874FULL, 0x370B938CD7BD45BBULL, 0x19C0F8746BA805DFULL, 0x22ADF75C80FCFD38ULL, 
            0x47B8E85994FBD093ULL, 0xBAB443AFCF575DF0ULL, 0x472C9E19E169A5E0ULL, 0x2A23A108DEB83FE6ULL, 
            0xA056C38F74AFAA18ULL, 0xFE6786C3411033BEULL, 0xD51EB59ACD663600ULL, 0x4A3B0EB0959212FBULL, 
            0xD4A51DA6D2DCACB3ULL, 0xE0DEB1F95546E72DULL, 0x9E6E790FBE815776ULL, 0xF5D5769FE0E0BBD3ULL, 
            0x9D8DF2976DA19446ULL, 0x92546A673B22E7EEULL, 0xBB60814274241561ULL, 0x62635377B0B6F562ULL
        },
        {
            0x5E3CA035A210C694ULL, 0x7CC13A0CF9421242ULL, 0x030649FAE85B0DBEULL, 0x2542B2635E4DA027ULL, 
            0x6EE2C126E33503F1ULL, 0x5573ED61960A752CULL, 0xC271C6FBEE4721DBULL, 0x3A2AF7C01176E773ULL, 
            0x2F282F66D8CFDF31ULL, 0xFBF6B2105B06FD4CULL, 0x360231E6E30D4DADULL, 0xA897CC33BCCF35F1ULL, 
            0x1743DF8125D75872ULL, 0x5B42E5C360465ADDULL, 0x428AAF894E3054F1ULL, 0x81B02768C2300C80ULL, 
            0xF5E111FDB7ADCA5EULL, 0x2A50FF69E025627FULL, 0xA38CF543C3FED1FCULL, 0x2DAE2440FF122C6BULL, 
            0x3F5EE7CEC6543567ULL, 0xB8D086F31CC1424AULL, 0x4B6664855CC9372FULL, 0x0E5121302AD32A1CULL, 
            0x456C063690F10FA6ULL, 0xE18DE49BFED83023ULL, 0x0478A92F91A30313ULL, 0x813EA00529C0DC17ULL, 
            0xC5FCE34C5C20D03FULL, 0x530608319451C58AULL, 0x867E531CD71CFEB7ULL, 0xFBB82882C12B1438ULL
        },
        {
            0x3B08763107F143A7ULL, 0x30029639B01F1CEDULL, 0xF8753851BDA401E4ULL, 0xD0E97F57F7741876ULL, 
            0xEE3DA7EA8EAA4FE4ULL, 0xEE28F3170C0A1DB3ULL, 0xAA752AC81C2F61ACULL, 0xA2874FDAEA25F3C1ULL, 
            0xCAFBC4D249BC35AAULL, 0x4039D7C853E99511ULL, 0x3F8F2AC1221E779CULL, 0xC1310F9AC89BEAC1ULL, 
            0x31AF96E28B5A2A5FULL, 0x747B17E65386A2FFULL, 0xB86DAD5736F32C3BULL, 0xB85C3CA34102F639ULL, 
            0x5FD1833931A917F7ULL, 0x3BB9598B1C1E4B99ULL, 0x24B98E775BE9FAC9ULL, 0x98CF3677A75A9117ULL, 
            0xDE64587EA0F8F70FULL, 0xAE64F04AAA518038ULL, 0x7CF90B6F7D6DDC1CULL, 0xB7F358FA7D369C13ULL, 
            0x4F85772AA4296F52ULL, 0x36C17FFA729EAA79ULL, 0x6CDE517F320159EAULL, 0x418AAA6838658084ULL, 
            0x995407CE1CAAB134ULL, 0xFE2BDEEAF683615FULL, 0x2A235F21F65567A5ULL, 0x26F2AB869BEFC1C0ULL
        },
        {
            0x52017CCF46C4A478ULL, 0xDF05455A42EC159CULL, 0xAE384D93FE4A80C8ULL, 0x7D1BC749DCC319FCULL, 
            0x6A52890F56D065DBULL, 0xB3EA615AA243F798ULL, 0xE77459CC6C5CA575ULL, 0xE7FE91ED8461F0D2ULL, 
            0x5C38B516805A6F54ULL, 0x4AADAF568CA2586EULL, 0x59D2D1E77E08F4E4ULL, 0x01F9A10F7A87B63DULL, 
            0x0DF472F2B8B9B12DULL, 0xCCD21F51111CAC41ULL, 0x8CB2B19A5A611342ULL, 0x624BEE9EEAD945D1ULL, 
            0xA9B30C70F23FDE87ULL, 0xB383C5D2D6374956ULL, 0xA7AB6319A174CC20ULL, 0xEC17DCC6E45C569AULL, 
            0xBD639AFCAD3A086CULL, 0x2E84A2DAE17F7D7CULL, 0xF2AA840B8D1C8D4BULL, 0xFECD3E26129BF1C7ULL, 
            0x316A16EB3B4A6C53ULL, 0x08EF8C0EABDC51C8ULL, 0xF81C1F034E565B7FULL, 0x3DF88E9A5D8CB946ULL, 
            0xDCB6272810A0F2C8ULL, 0xB85484829D302622ULL, 0x436B7B2BC9A6F77BULL, 0x59BCB4E4D71C373DULL
        },
        {
            0xB740C782408C2AD1ULL, 0x77D05389B812819EULL, 0x66A1470EA972C25DULL, 0x841A1D272FB6E2C0ULL, 
            0x053F83F85C71DA98ULL, 0x66D79F259902C3C7ULL, 0xE21714057D7A7952ULL, 0xF56C2F8C14AF2A42ULL, 
            0x54774C94C2FF18E6ULL, 0x310914112ECF6678ULL, 0x26C61BF6838D2D52ULL, 0xB01B9239E671A344ULL, 
            0xD9425A5C31C12E01ULL, 0x1C0E0D4C5CFD0FC1ULL, 0xD7091B129886D127ULL, 0x4D73F22F05C42921ULL, 
            0xF5D52A2277E04822ULL, 0xBA9210902AA8868BULL, 0xA9F8BC888D065055ULL, 0x190721D0C8EF9FD8ULL, 
            0x866305634687889BULL, 0x7BA37F3CE173CCE3ULL, 0xC2DCA74EBD5C2C4AULL, 0xD2AAC761CCB9329CULL, 
            0x8FA68B2E8AF0C232ULL, 0xA609AD558717E5E9ULL, 0x4394FA2297637112ULL, 0x6D68AA3AC73DCE85ULL, 
            0x9B490C5757390EE8ULL, 0xECC8E8FE11931834ULL, 0x7FDFDC141786EC79ULL, 0x310A1220E12E5ADEULL
        }
    },
    {
        {
            0x6054C32CDFF53601ULL, 0x9A072BA8220C2233ULL, 0x613EEB65D07BA3A2ULL, 0x104ACCA531984D03ULL, 
            0x715920AD321FFBD1ULL, 0x97FD30A1E077C040ULL, 0x6EAB568F190A2836ULL, 0x70E0BBDD079E87C5ULL, 
            0x37E781755335458CULL, 0xACA6D0267BAF3CF4ULL, 0x0F8635A737228728ULL, 0x311638AAAC808BC2ULL, 
            0xF7197493984B9E76ULL, 0xCFA59CD48FF824CCULL, 0x567A97FAE09D9AEDULL, 0xAD2CBCB6FA8F883CULL, 
            0xB7BB9F8C6C2C368BULL, 0xD06DE81D700E9692ULL, 0x17B1121096DD913AULL, 0x7782F3F5F987B71CULL, 
            0xC647EDA4810966F2ULL, 0x2DF87C55CCE6200DULL, 0xD3BDFFDF29DF2535ULL, 0xA98D67B929A80DAFULL, 
            0x4C73B237D24D531BULL, 0x22B1BCFC31284524ULL, 0xC595DBB72FE599A7ULL, 0x0A4F9F4A4C7D9B74ULL, 
            0x5FC170DE5F8959EDULL, 0x469B00C178A2900AULL, 0xD7624BAF86CD994AULL, 0x18CC6C3CBF2CE752ULL
        },
        {
            0x94427AB2370E2371ULL, 0xA2811E3A79FC41FEULL, 0x179DDBA3C7A63CB0ULL, 0xFB2868EA1AFC9902ULL, 
            0xD4B11CADDE7B3320ULL, 0x28B01A68CB7D141AULL, 0x9E62354C613CD1FDULL, 0xD3AEFFFDB2BA6C3EULL, 
            0xCC31CAEAF15C2116ULL, 0x94FE9718969A2AB7ULL, 0xC027CDC207449515ULL, 0x256E879D55714772ULL, 
            0xACFEF25DF7E52BCFULL, 0x42FA0E59686E9985ULL, 0xE17EC9869F7CF465ULL, 0x3BBD23CD411601F3ULL, 
            0x42EA2C3B1676BBADULL, 0x1FBF79F51515C81AULL, 0xEDFACCD07D82D2C4ULL, 0xD68D1A98C2E9F4ECULL, 
            0x2F4F215ECF469C8CULL, 0xA8120AC7753EF7B1ULL, 0xCF0E2EBEA5FE2B0EULL, 0x36F605ADCB269715ULL, 
            0x033FE2C583137347ULL, 0x8342DFB5AAE5449CULL, 0xBE0D238CC3091372ULL, 0x89BD77983C1E1240ULL, 
            0x48CA35AE47E4824DULL, 0x72DF93C6BB28F4DAULL, 0xEDC6DC747C4A85A7ULL, 0x24B526AC7103B60BULL
        },
        {
            0xF55819D464B28302ULL, 0x1EA9F7FC4EA86055ULL, 0xBDCF814FEF69FE59ULL, 0xA0C546A0C418F4B8ULL, 
            0x3A23544BB4E1DC23ULL, 0x8ACCCA0BA6FDD327ULL, 0x55C973E4A6CC674CULL, 0xDDD8258DF7758949ULL, 
            0x24119DC9BD9647C4ULL, 0x7F52EF96465E328DULL, 0x1BDC330F5924539EULL, 0x6AB5323B89A11DCAULL, 
            0xA0D2BA742B6A7304ULL, 0xA209BFBD27119A16ULL, 0x642A82BAB50B1B38ULL, 0xAC644191B956D4A6ULL, 
            0xABAC7BE9E9BB29F9ULL, 0x9D376E2EB7EAAE99ULL, 0x4B7BADD987803473ULL, 0xAAA71D373BCA020FULL, 
            0x77F9858EE1DE4B39ULL, 0x9AAB5E146240587AULL, 0xF552B2236B53BDAEULL, 0x1CE3E036108E3217ULL, 
            0xCF48E87185788640ULL, 0x5067D2C970ECE846ULL, 0x07B9FDD545F56782ULL, 0xA62B48C7F50ACAEEULL, 
            0x1048EFA74A4EE248ULL, 0xAB565F934115DAF2ULL, 0xD40FBB5A117CA147ULL, 0x4311F48AEDF9EC1BULL
        },
        {
            0x380DE6B872F56259ULL, 0x7E90A2A6DE5D5339ULL, 0x2A594F6936ECF78FULL, 0x4A68A3804E10717AULL, 
            0xE1052A0834AF7060ULL, 0xBD96AC9BDD4B9C3CULL, 0xA621FB4D345DAC4FULL, 0x692D19D9A81A2FD8ULL, 
            0xB68E5B11DAE86AD5ULL, 0x20388B75CECA9953ULL, 0xFD583C0A4297C6E8ULL, 0x6882DD04597F5A37ULL, 
            0x8777020235A08C97ULL, 0xAD02813C59F4AC17ULL, 0xC1183DDF5AEACE04ULL, 0x1BE2A3D2A19322A8ULL, 
            0xA405B12F3CA6CA32ULL, 0x63E3CDD93C48449DULL, 0xED779EBAD9EAAD15ULL, 0x50236E06494F5BCCULL, 
            0xDAC1DA0693427174ULL, 0x3DEBBD0268221830ULL, 0x228B8B8C2583E39FULL, 0x89F144948D983C2DULL, 
            0x9685D7CEE3CF024CULL, 0x0BA9B371AF7646FDULL, 0x6D2AF31C9ACE68CAULL, 0xB21625E8D0B69D25ULL, 
            0x0A6477BA1AA3FA6BULL, 0x3ABC37EB4774D8AAULL, 0xA2B195AC798553FBULL, 0xE3D390AE39AB99ACULL
        },
        {
            0xAA8C414D4F84BBB0ULL, 0xAF448D472C9ACF80ULL, 0x09DF96CF074053F9ULL, 0x4D67826A3474C8FCULL, 
            0x9415CA8B07EE6265ULL, 0xFA7A60EACA4F3AE8ULL, 0xC70BFDDCC953D994ULL, 0xC03E5E629348319EULL, 
            0xDFCECF1928E4BF5FULL, 0xBA56E65240744F91ULL, 0x34D6007100CB8FD6ULL, 0xCC28F872E34B44DBULL, 
            0xF9679538DB7CFFA4ULL, 0x15C01244261B62BEULL, 0x992E8B8C0D868ACEULL, 0x82A56CC3B5ABA2EBULL, 
            0x8AC7635CEF89C622ULL, 0x309842FC3D398B08ULL, 0xC9D35899D9C95F31ULL, 0x7EBC310509BFE718ULL, 
            0xBAF8F209B3324FADULL, 0xA01A0A7272073E62ULL, 0xA19F5D762DDAD641ULL, 0xE08958B75DEDA6C3ULL, 
            0x096FC617298798A8ULL, 0xDF6CA8120C5CBB89ULL, 0x244641E1FA41C4E4ULL, 0xA8627A2D831A1C6FULL, 
            0x14F2FFEF43762F3AULL, 0x2E77B247304C7439ULL, 0x482134590E2C12F7ULL, 0xE06B823FF2258403ULL
        },
        {
            0x2AED5A5C1876C1F9ULL, 0xF71B42AACD7E301DULL, 0xAA4EC97E3DCBA8B3ULL, 0xA0F5C33B8B858E8AULL, 
            0xA839648B0D00D9BFULL, 0x66936444052C47A3ULL, 0x8B77F1787D9C71FCULL, 0x7A4A2B043AA19844ULL, 
            0x10E4AD985B1CAF3FULL, 0x180B3D205FBD6138ULL, 0xBBA1191E6C59B48BULL, 0xD082C0ECB2288D8FULL, 
            0x02BAB3690EF000CAULL, 0xD484371554B82824ULL, 0x701DCA33DBF9B95FULL, 0x6FD1B18696CEB121ULL, 
            0x0C9E6087DD85FEB0ULL, 0x2A06E559B7FB60DAULL, 0xB7BC305255FD17B1ULL, 0xD9C1858F77E9ACA2ULL, 
            0x32DD8DFBAECCD8F0ULL, 0xD7C6E00DF08C0C3CULL, 0xDD66A7301A1AB6C3ULL, 0x8F81FF12AB4B0139ULL, 
            0x3A0D62499FB36CBCULL, 0x42303A3606A893ABULL, 0xD0B7B718FA3B7780ULL, 0xDA538F042B032FF9ULL, 
            0x449464BAD85F34A7ULL, 0x00C5B23C3AC94E5AULL, 0x6AEDD13F147F7CCFULL, 0x723610B5F285C17EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseCConstants = {
    0x1233E1A07BBA1ACEULL,
    0xAA13FD608848FE22ULL,
    0xD572865F227B38AFULL,
    0x1233E1A07BBA1ACEULL,
    0xAA13FD608848FE22ULL,
    0xD572865F227B38AFULL,
    0x21D5890EFEEACD0FULL,
    0x0B30D9D2E4453869ULL,
    0xA5,
    0x93,
    0x4E,
    0x82,
    0xDD,
    0xBE,
    0x52,
    0x3A
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseDSalts = {
    {
        {
            0x96CDD22710AED3FFULL, 0x6E2A199FF25E8424ULL, 0x5F3EE8E870095875ULL, 0x3337BE30258A73E1ULL, 
            0x9CB950E7D4E20AE2ULL, 0xEE8EF3544B02DAF1ULL, 0x1C334156D07F504AULL, 0x3024EBCB79A040DEULL, 
            0x6E8D63C7156ED4C9ULL, 0xC2FE41CDB9AC6F3FULL, 0x10B47691E1F584BBULL, 0x23804B6CA3C8ABC9ULL, 
            0x9FED0CE583D3FFAFULL, 0x17AE0AC1E18FD5A2ULL, 0xAF3461452942B4AFULL, 0x49826C75C56480A8ULL, 
            0x050397EDD23B6F85ULL, 0x1DECDFC3315C3F19ULL, 0xEFF4B43B6D2563B4ULL, 0xA545E4DC392C3763ULL, 
            0xD8F2550A79B2B43CULL, 0xD0CF74448DE99DBAULL, 0x1FCD45B3DB7BCFBFULL, 0xEC873D9806CAC169ULL, 
            0x9DC7EF84457E80D6ULL, 0xB33952CB93C14A92ULL, 0x052C5366F42C9D79ULL, 0x98040A7106DF0081ULL, 
            0x5E0C2F8CF1E76A0BULL, 0x7DCB13AF4C814D59ULL, 0xAF17F3AF0A80BF1FULL, 0x2748A2F839B4C11EULL
        },
        {
            0x648B783997CBECEDULL, 0xC036124DB609A19FULL, 0xAF1BBAFEF7E35AB9ULL, 0xD7FFBA6FD3AFDB81ULL, 
            0x645E1971F6691AC2ULL, 0x92E256EB6F785253ULL, 0x32B026E6DA68AEEBULL, 0xBE86A6F5A2A62C75ULL, 
            0x74E4BBE07B1C1F49ULL, 0x4ECF634DAB96E50DULL, 0x9AC3721E64DFAA10ULL, 0x046F695CA8294E12ULL, 
            0xC2CA5CDC8CD30990ULL, 0x2E003060A6EE2B19ULL, 0x74814493543759A6ULL, 0xFE6CF4E39A37CF79ULL, 
            0x794D72C63785B9F7ULL, 0x7667220547B8C7A8ULL, 0x5531FF8108F3C637ULL, 0x629C7679391AF8C8ULL, 
            0xFBF665F3408FD3BAULL, 0x5BA8DCB4FFC994AEULL, 0x3026E619A4C4DD9DULL, 0x06550825A41CAFAFULL, 
            0x13EEA8494C602762ULL, 0xAC579936A31D2A61ULL, 0x7B7B974EECF8D3F9ULL, 0xFB19593EBC9D2CC8ULL, 
            0xE3B4B252767826C0ULL, 0xE4BBCF705D5CB638ULL, 0x9CFEC87ED1142858ULL, 0xF7FB4AAB21CA5D60ULL
        },
        {
            0xE23292997B516238ULL, 0x3C98A70ACCD644A2ULL, 0xEA5CCF76EC4B34A7ULL, 0xB7EE6B0F91462E52ULL, 
            0x891C4AD5EC689F94ULL, 0x8BAFEDE97C004957ULL, 0x8578F7961E1B20C0ULL, 0x213330051732FAACULL, 
            0xC3F71E2406DB0030ULL, 0xD06467D68CE3B246ULL, 0x7C1CF64A92153AA7ULL, 0xC5A8E7E9A19769FCULL, 
            0x1A21B42A858963CBULL, 0x078A153CCBD2A5D3ULL, 0x39AEB98181AA9E38ULL, 0x4D2D3BC61C5288E7ULL, 
            0xD16C6894A8F9EE58ULL, 0x15D2BDA8AEF68271ULL, 0x2CD6E5F80E6969E7ULL, 0x21C850FD36B22886ULL, 
            0x190DA360911D5B08ULL, 0xF815F22D097EB904ULL, 0xE843C1D6E68A0F49ULL, 0x872FB909440B8B4FULL, 
            0x69E708F6EA81DC46ULL, 0x49045DF871DBBB7FULL, 0xCC25F2E3503B955BULL, 0x34D84A111974C6BDULL, 
            0xDC80BA6CD1669638ULL, 0x390C1A092F252C48ULL, 0x85504A061857D77AULL, 0xCBB02858D44C682BULL
        },
        {
            0xE16F0892C8E2EC59ULL, 0x4D6F843E90991D50ULL, 0x5A23512185532C25ULL, 0x6625B540102D8F73ULL, 
            0x9E17FCE74CEDB41BULL, 0xE68C98F39F64CEC8ULL, 0xF15F97F54126346EULL, 0x686C6B6888515953ULL, 
            0xD694DC140BA3E6C7ULL, 0xAA308E942C138465ULL, 0x0D24C4E5CB7ED79AULL, 0xCEBB467B963A0D37ULL, 
            0x48AACF9F7742756AULL, 0x009B44EE497A20B9ULL, 0xF539643737697E40ULL, 0x0DBF5886584877A6ULL, 
            0x256AEF129BFE893CULL, 0x8A935DC2802CD6E7ULL, 0x9EE87F3DEA303A1AULL, 0x1FA0C945432745F8ULL, 
            0x4CF647F7E68B418EULL, 0xBC03E98A9AB93D5FULL, 0xA0A48BB9C6D9CE02ULL, 0xAE1CC9C1FDE2A3DEULL, 
            0x364CC03E909107C2ULL, 0xACA874ED09CA3F0CULL, 0x0C1CDD6802A98344ULL, 0x9E93C152767EC135ULL, 
            0xF0ECD54AC7D661FFULL, 0xE093C6E74A9765BEULL, 0x3C194923EE636E87ULL, 0x2FFBB8AC8A550D02ULL
        },
        {
            0xE745B947AC73A44AULL, 0x3B41266186140113ULL, 0x9BD83F435ADF44DAULL, 0x8582BB26A2B8E347ULL, 
            0xFCB3199A4C8BA4A0ULL, 0x3BF3556C783070F3ULL, 0x0F14C9C3B0AED841ULL, 0xCB88D9590C32353AULL, 
            0xE5D34A93D0A003A4ULL, 0x1A68F3EB14F3F5F4ULL, 0x191E1D95709DEFF0ULL, 0x06746B9E1D2F6F41ULL, 
            0xAB9EA3B62803F24AULL, 0x8608705737FDD9BDULL, 0x7914FD1652C0272DULL, 0xBFEB0E64F4C666EDULL, 
            0xCD89D017799C72A8ULL, 0x9AEC08DA2821F484ULL, 0xF434554B74C228DAULL, 0x84A4C0C893730739ULL, 
            0xB7F0CAA121F2FF5AULL, 0xA7CDA461DA4E151BULL, 0xCEF290AC8802B432ULL, 0xA42E18D0D2582954ULL, 
            0x4B7D66EA5258A695ULL, 0x5E240E139948B6BEULL, 0x0385282A427C69F0ULL, 0xE8BC8EEC6056C032ULL, 
            0x0F90DDF1511C482FULL, 0xFDE6BE084231AD69ULL, 0x9726E4538AA978AFULL, 0x1227FC17E517D9E2ULL
        },
        {
            0x513BC5B21A7D9BDCULL, 0xB10D6CEC3F449A4BULL, 0x78DAB28C4E3E1954ULL, 0x6D34DA9F0BD08F3DULL, 
            0x5E86D025546972F1ULL, 0x63F72099CEA71365ULL, 0x68C30B26513262C7ULL, 0xDB4768BC6F395CDDULL, 
            0x24396C00B070ABF2ULL, 0x0B54ACC49D758AD4ULL, 0x762463FEAB4EC348ULL, 0xA4A29B741C00178BULL, 
            0x16A47C2CB56E52AFULL, 0xB5616DDA185D5087ULL, 0xB8A320CB96A176CEULL, 0x7D822B2E99FFC34CULL, 
            0x6D497DB3772BB250ULL, 0x1E2A3D02D86C33F0ULL, 0xDF7CC404CA78BE72ULL, 0xCE7DD69C19CAF24EULL, 
            0x11B7F2F9275A4F26ULL, 0xFBF2CD72FDEDD15FULL, 0xB042F7112C03F988ULL, 0xD6E46819F398A2C7ULL, 
            0xF7841BA7900E56C6ULL, 0x6790E6FC461DA2CAULL, 0xB0442B75D2FA9115ULL, 0x90F3FA487BD79972ULL, 
            0x4D232439BA5EDA75ULL, 0x9B5547930F22E965ULL, 0x19022ECB402AC6B4ULL, 0x6CE847B68D4752BDULL
        }
    },
    {
        {
            0xFEEE5986450BF2D7ULL, 0x7CDD67134D32E3A9ULL, 0x6659AD4C2ED78787ULL, 0xE2C8AB033981083FULL, 
            0x8D42D21D60F50300ULL, 0xD5DE7E909EB210B3ULL, 0x211AB1151375425EULL, 0x5ACFB42E41888D21ULL, 
            0xCFF03AA47623DFB6ULL, 0xEE157671F70554C9ULL, 0x98CFDE7992D72C75ULL, 0xB4D9D4F0BD7A8791ULL, 
            0xEC42BE272860369DULL, 0x41C40B260A050B11ULL, 0x785D96EA3638EF1EULL, 0x12BBF54EC0C57A20ULL, 
            0x365A081911FC376FULL, 0x536228690F5879AAULL, 0x2795B72EF1A04EF8ULL, 0x7755852E2F5F8C39ULL, 
            0x8F0E12F9C7BBFFFFULL, 0x1405385E593754CDULL, 0x95AD8480FCF1965AULL, 0x0C8BE8FFF7A8C07BULL, 
            0x50BA053A11C46679ULL, 0x539C97683D2287A8ULL, 0x0247CCDB6D1E5A6FULL, 0x5FB8A02CD21B2ECEULL, 
            0x30418F64B483B381ULL, 0x5050329A27C9B1C1ULL, 0xB3CE784D40DC6CC9ULL, 0x945B27631D6975C6ULL
        },
        {
            0xC65422A2D5CEE224ULL, 0xC3388528938937CBULL, 0x6BAA04457C025B2BULL, 0x18528FD8014D0F5AULL, 
            0x729771903EEF6AADULL, 0x015A01FEAE3987B3ULL, 0xC994E93C0DEC488CULL, 0x3686554026902D82ULL, 
            0x98D833E24DD980F9ULL, 0x8516DCEC52F57375ULL, 0xCA4E98F043B39A0DULL, 0x910D986B64798040ULL, 
            0x9B665644B23B6024ULL, 0xFC96336B8EDED686ULL, 0xD14CE3DCA80C728BULL, 0x22B1A8D596AF5AF6ULL, 
            0x56E7969458EAE962ULL, 0xDCC8296F524CBC91ULL, 0x0865C92ABE574B14ULL, 0x0994425A604C750BULL, 
            0xBFBDCD9BC7400EBFULL, 0x2A69E1B7F7D3E19AULL, 0x98EE41ED3DE4A051ULL, 0x9E6B4632DF0C8693ULL, 
            0x7315CF0BA0DBAF03ULL, 0x2DF0FDEF7D8A666BULL, 0x529358AB7E308681ULL, 0x03D80298804DB65BULL, 
            0x091D615D3677A0FAULL, 0x55B78D2526208C0BULL, 0xE5D1854EF9D4245CULL, 0xF4EA4B55963B7332ULL
        },
        {
            0xBBDEB6F76FBE9B13ULL, 0xFC04EB86A88F47FDULL, 0x6F776D530CA5CF1DULL, 0xAC221B465CD32B5EULL, 
            0x293F7FFCE3F60133ULL, 0xA1CC2AEEF992193BULL, 0x2F4A8EE498535AD9ULL, 0x1CC269F8ED2B1F35ULL, 
            0xA89681169F8C983AULL, 0xE8CE3327B2146333ULL, 0x31E51CBB756B79EEULL, 0x8CB1F30EA7FA3205ULL, 
            0xA3312AB352A27F1AULL, 0xF0CAE0E7D44D42CAULL, 0x380E3674716740DEULL, 0x90D98910CAD0D88DULL, 
            0x327C1FC678AC5913ULL, 0x8693D2D5C93BC7D1ULL, 0x401980F7FA713B20ULL, 0x9BBC12B2535E6DF1ULL, 
            0xAEF828D47FB24B79ULL, 0xBC0E134377719114ULL, 0xDA26B659726E080FULL, 0x135872380DC78B88ULL, 
            0xDFE267389B517BB6ULL, 0x39C165F21F8AC269ULL, 0x6787257B13FBEDB4ULL, 0x209CEA0BC12F6C21ULL, 
            0x868A6B2A3EFD54B5ULL, 0xB1271CD639BE085AULL, 0x12A4C3F4810C296BULL, 0xF3E0C071763E0636ULL
        },
        {
            0x3D8E00A4FC356113ULL, 0xE57F2B699BD6DDC4ULL, 0xF7169D7A9FF8E716ULL, 0xC497E44198137829ULL, 
            0x402326921EF6C425ULL, 0xB2F33AC8D368017CULL, 0xEDEA6A4F3A619618ULL, 0x7A01EE987A49A628ULL, 
            0x8CA3FF5DD1492765ULL, 0xFA0D1BB964E1ABE6ULL, 0x03981B2391F2C69FULL, 0x66EABAB77FD86A52ULL, 
            0xFFBEBABE453C5C5AULL, 0x86558458DAA1A87FULL, 0x105814F7D99C4528ULL, 0x37D05A8BF2B0E527ULL, 
            0x9A63B8E56B1D45C4ULL, 0x0C878543CA12F286ULL, 0x1E2D4AE8BBD75DE9ULL, 0x11F4243AB60CB9FEULL, 
            0x0F98F9C4FB0941DFULL, 0x68EC841588DE3262ULL, 0xC26BB68D357AC44DULL, 0xBD654A77B24C8522ULL, 
            0x3674EA3106D50C45ULL, 0x9F1780AB53454C52ULL, 0xEA4B551A1393238FULL, 0x7F190F0988011FCCULL, 
            0xAC4BEF5DF17183ADULL, 0xB9281F6B135488CEULL, 0x4B25FE30C2074879ULL, 0x2B4BB70695C78219ULL
        },
        {
            0xE84AA2FD25BEB53AULL, 0x211DB77E9B1EDD8BULL, 0x74E803E9F43FBAB7ULL, 0x9E57C1F12DDF636BULL, 
            0x3AEFD5E82F498377ULL, 0x1210733BC73E82EDULL, 0x3AB1D9BB75BFED01ULL, 0x0D808C24B7514188ULL, 
            0xAF02BDFD15CA977BULL, 0xA7BFB8BC43CFAA68ULL, 0xC095154A3A725280ULL, 0x1A525C202D581B89ULL, 
            0x249ACA190EE8E4F5ULL, 0x1F14D1504949325DULL, 0x10A16DF292CD66E6ULL, 0x447363F8AA79F5F8ULL, 
            0x7023F81C3C6B095BULL, 0x3B83A72CE8B33D60ULL, 0xED2BF42D771FCEC3ULL, 0xFEAF49DF8392FBF1ULL, 
            0xC5590B16BD655FC4ULL, 0x8E1E652482A0DB96ULL, 0xE90B5D4B98C74712ULL, 0x43A7474E03053EF8ULL, 
            0xE8AA54F1D60B828AULL, 0x8E1F9E6D82C5BD69ULL, 0xA9675F645D8E0BF0ULL, 0x3AA5C563792B9BDEULL, 
            0x46B025C38BB51148ULL, 0xA943A4730A206739ULL, 0x9B41C260872A4617ULL, 0x023FC40DA93B521CULL
        },
        {
            0x7F0ADC54C623B87EULL, 0xC6D707098433315BULL, 0x155812FF4FFEEB67ULL, 0x5EF80BC4250364B6ULL, 
            0x9CEE2A9AD7FD9E11ULL, 0x357DB3334F64E47BULL, 0xB890AB1859097C3FULL, 0x4A876B01257E9ECBULL, 
            0x9AB2C69B6FDDF27CULL, 0xED1DA16D3FCC66AEULL, 0x41AD5293AD23DD8EULL, 0x5B6570BCB623B4E9ULL, 
            0x66BD3114865609E6ULL, 0xC9DB7F26E078A838ULL, 0x19B65E97A62F5ABBULL, 0x03214FCB660F351BULL, 
            0x0B601AC6F23F39E6ULL, 0x0395614EFF6C3D90ULL, 0xEBEEA26E739CA87AULL, 0x909CCD8BAE5AA4DBULL, 
            0xC02FC30254C5E4C5ULL, 0x97AB51448A9EE1DCULL, 0x4598BB080E338BD8ULL, 0x977397F7CA83B879ULL, 
            0x1D8B7B6F4EC7A20FULL, 0x74AD4BB570DD4B5AULL, 0xEB204934143F4BCCULL, 0xB66749AD90353F10ULL, 
            0x2AE2AFE2349B9021ULL, 0xACF3D0B48982F682ULL, 0xF52B515F00E6E708ULL, 0x77B990D0C333065EULL
        }
    },
    {
        {
            0x59A044789D08B04FULL, 0x0817946C5418B260ULL, 0xACEA747AE7D68D24ULL, 0x2AB106AB90887E95ULL, 
            0x68A9D0F63AE49824ULL, 0xC3F8AE65C62454E8ULL, 0xDE4BFC54805C4527ULL, 0xC969EED716DEBB93ULL, 
            0x2DF00A584A9CA38CULL, 0x0AB9305BB0E7C575ULL, 0x0290F7C66930BE16ULL, 0x66DCB4E7AEB22BDEULL, 
            0x489AD3E79B5910EFULL, 0x96170AD1F554C025ULL, 0x95D6C9EE033FCC9BULL, 0xA4965A1106BF931AULL, 
            0x1A7935C4EE96B975ULL, 0xADAEF358BC66185FULL, 0x6C5DB63B843D1C01ULL, 0xBF44BC64726B1DDAULL, 
            0x0C1E47C69E8D15FDULL, 0x194D3C2827E65071ULL, 0xA019D0CEC0F45B15ULL, 0x6878F7629EC9E952ULL, 
            0x23602FFAF6FB7349ULL, 0xAF8A2FC26D66B71AULL, 0xA3DD3409BECFA123ULL, 0xB75D69CAE98CDE51ULL, 
            0xB1B3EA5ABEA22EFBULL, 0x45F8DA6AC7FDBA9BULL, 0x09A13B683CC9B67AULL, 0x46191525A6CC083BULL
        },
        {
            0x002E0EE38972FFBDULL, 0xA0A20E1802783DEEULL, 0x487EEECACB1ACC1EULL, 0xFF8C0C3B510901FDULL, 
            0xE7659B5253337F41ULL, 0xF93BC42B684100B6ULL, 0x36666FC524AC998BULL, 0x9C86371366C0FF8EULL, 
            0x849DF9E9A9B91288ULL, 0x99C5860A2EF9A95DULL, 0x666065F98FDD930AULL, 0xB7FA37E7FD43A5E2ULL, 
            0x6321369B3F9492F0ULL, 0x1AF5AFB89E0A7E00ULL, 0x684B08B83F8212E4ULL, 0xCA7784A69435338FULL, 
            0xF21FE7EB9DD33D32ULL, 0x4A2AB0137EF658FCULL, 0x175F084AF0E35B46ULL, 0x9B9A3359A8E5556CULL, 
            0x52E30C91C33E9778ULL, 0xB4C0E1CE7649C1B0ULL, 0xDD7AAA9F8FBCB792ULL, 0x2B6611AE037F1C96ULL, 
            0x8304854BB548FF52ULL, 0xBDB6D79E5D4D80C5ULL, 0xC98B1D07590AB6B2ULL, 0xB82F17E6D834B54CULL, 
            0x2FD9921B874EA4CDULL, 0xCC244C59B07CA75AULL, 0xCE3BD73859765D47ULL, 0xBCCDBB72BF8AD94FULL
        },
        {
            0x4C39DA276E8E5CAEULL, 0xE504208FE4A9B8D7ULL, 0xC35114358A2CC74DULL, 0x6742342A118226C8ULL, 
            0x2CE5726BB4A33B11ULL, 0x0F339C9E4BA5B82AULL, 0x7D348442E7396A44ULL, 0x56A3DE6335E66D3FULL, 
            0xDAB4E2BA3285C4E5ULL, 0x18D47B9B0D661FF5ULL, 0xDCCED6FFE9335F04ULL, 0xEBA5BA9AEDD7973EULL, 
            0x4FF6F3880046D6B2ULL, 0x22519D4DD65EAF0DULL, 0x45C50A3AD2E2FCC2ULL, 0xEAF70C05CE360B87ULL, 
            0x137FDDF4B5232114ULL, 0xD26B5C22BC48CEE4ULL, 0xCE4B302B54061CE3ULL, 0x956D39CE026AE85FULL, 
            0xF32D26D929D23321ULL, 0x820E5D9D2685EB06ULL, 0xB7DD74DE0BF858EEULL, 0x9E8EAADEE63EBB32ULL, 
            0x421733931D4182D7ULL, 0x33F74ADC1B95A478ULL, 0x4FC3AA96DFA3E3C3ULL, 0x913CDDBDF24FC14DULL, 
            0xC729F6AAAC405BA4ULL, 0x638D85EBBFF668ECULL, 0xDC00B183064304E7ULL, 0xB6559798B9624E4BULL
        },
        {
            0x5A2F3261DF378DD1ULL, 0xCA739DB4288E5321ULL, 0x166DA9185492641BULL, 0xC49A2074B03AF86DULL, 
            0xD274221E7F12B78EULL, 0xBD587FCDF6FEA42CULL, 0x9B8DB279BC9BFDB2ULL, 0x5790E9933EE0BDEBULL, 
            0x657765C4DD1153C6ULL, 0xC8CCC3DB0C2D8D3BULL, 0x79F2FAE892C05665ULL, 0x6F8DA422F54DE1C8ULL, 
            0x43AEA111A17062E5ULL, 0xC73FABB895061908ULL, 0x91A25171D16AD6F2ULL, 0x405389DF326EB174ULL, 
            0x7A9E4C22815341B7ULL, 0x58684A2D95BD7EEAULL, 0xA7139A80B98052CDULL, 0x92A5C1A50306880DULL, 
            0x46FCAECB8D85D1C3ULL, 0xC96B0DBFB627FF49ULL, 0x8BB6712BFD258165ULL, 0xF764175A700E0347ULL, 
            0xAAB34986AF8735CAULL, 0x945A8BBECA793286ULL, 0x931E5E5E01777D8BULL, 0x41D06471C7F9CB53ULL, 
            0xBA3CE57827B47B9CULL, 0xDF1BF4DFDDCFEE10ULL, 0x9DAD837829C45117ULL, 0x3CFABA3C24A1F1E5ULL
        },
        {
            0x98A161A4CB6117E8ULL, 0x484BA78C79B5B336ULL, 0x528F32FF681B4045ULL, 0x8319990554C9FC68ULL, 
            0xB50AE2C4EC120662ULL, 0x1D5B9168B4F5C03DULL, 0xEB7025B004FC235AULL, 0x68905BE6346986D2ULL, 
            0x56F8BB2D48C5E9FCULL, 0xAFA3BC7B204864A2ULL, 0x08AD388019CD4580ULL, 0x13D25F1F8A403A92ULL, 
            0x34E1CBEA5350EA4AULL, 0x425775A79620ECCDULL, 0xD5A79F999EDCE7A0ULL, 0x3FE37FDC35E935D2ULL, 
            0xE865F6DA401F7609ULL, 0x31A4CC51E5E0E0BFULL, 0xBE0672C87D651ACBULL, 0xFEF6091DF6D0EA72ULL, 
            0x93607E54175BAE5BULL, 0x3CD891DDB0071383ULL, 0x14D5C392742AF313ULL, 0xE2E97A748F8D7BFAULL, 
            0xDB4675E6DD551326ULL, 0x0E299D03627BBE6BULL, 0x5628743EBE1CF31BULL, 0x6426D337EA4114FAULL, 
            0xEFC1D2F84BBB6428ULL, 0xC96B009CAB90B6B1ULL, 0x425B349C0E7EBA23ULL, 0x8627D23D24CE0443ULL
        },
        {
            0x7700C5F7B8224A69ULL, 0xB2AC9C2E00313180ULL, 0xBA7E147D09E23B4AULL, 0x5359587101CF52ADULL, 
            0x399D9E838CC037DAULL, 0x90785D51C2ECC766ULL, 0x265FF72DAFB95F50ULL, 0x5331CFAAD6585E4EULL, 
            0xAC3B31D6116C7B3DULL, 0x745306AB6FC6C6D8ULL, 0x1B7CB2753E1034CAULL, 0xD1F5A6E1786B84A8ULL, 
            0x6C476602F1D2C3D1ULL, 0x04100AEC9C3DAEC4ULL, 0xE982578658907913ULL, 0x05693086C3F9A00EULL, 
            0x8DC261FDA7BECC08ULL, 0x4F0114ED2BF3296DULL, 0x470DE1F6D1E6B347ULL, 0xBF33E9E7DF3C025AULL, 
            0xE273AAA108DE1CFFULL, 0xB2DF2F4733062924ULL, 0x5121CC2C480BE4F3ULL, 0xF445DE508E58A09AULL, 
            0xBE60795F1C0EE3C7ULL, 0x0C39A83D78A2F95AULL, 0x26F3EAAA9901A764ULL, 0x900CD758F31CB221ULL, 
            0xE6FCA7057B14D12CULL, 0x5D1AE61239B4F1D2ULL, 0xE00FD561B09679EDULL, 0x6EA7F7DF4FAC0A47ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseDConstants = {
    0xA52DB6ABE8CCB324ULL,
    0xC11A2C369466C504ULL,
    0x4A8DAEC693E2756DULL,
    0xA52DB6ABE8CCB324ULL,
    0xC11A2C369466C504ULL,
    0x4A8DAEC693E2756DULL,
    0xD26A7DC687A82E3EULL,
    0xEEC44AB0C83B4CEEULL,
    0x04,
    0xCE,
    0x97,
    0xB8,
    0xEC,
    0x60,
    0x36,
    0x4E
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseESalts = {
    {
        {
            0x5ECF4BA761D6436EULL, 0x203F18FE2F9A1C17ULL, 0xD1DB1E7CC0560110ULL, 0x5746747D01959D67ULL, 
            0x4CD6747E41C20B73ULL, 0x9FC58F5B9C98D181ULL, 0x8F2FA60E5C698DFFULL, 0x2F5B6D9657001142ULL, 
            0x2AA343EE9224D2D4ULL, 0xBBE6021DE06274DEULL, 0x437E64F369FFE85CULL, 0xE0545F399C5F43D3ULL, 
            0x7B8FBA687A5ABE9CULL, 0x63423B76EB2B512AULL, 0x93FE86C780CD18E8ULL, 0x391144C867BBBB6FULL, 
            0x2B46B4AED2A555A6ULL, 0xB0E78797C42E1BC3ULL, 0xA1BAE54DB7368DECULL, 0x28C59D6C7B623459ULL, 
            0xD4224D50901F49DAULL, 0x03869B6BE869E751ULL, 0x5615349306C1097EULL, 0x0A19EBADCDE9DCE1ULL, 
            0x0C230A6BB2959DDBULL, 0x1074AC389EAFB8EFULL, 0xBC36D274757965ADULL, 0x1F993C9371249C71ULL, 
            0x30462F36205A4A6BULL, 0x2321A170EC57136EULL, 0xE26E3F2DD5EF2C52ULL, 0x173C4C2AEFB08C5AULL
        },
        {
            0x3B1615D4ED60C511ULL, 0xA93CAFF897FA3DC4ULL, 0xD2E5D6353679AEFAULL, 0x023EF64347FC397CULL, 
            0xFBFC823EEF4AB070ULL, 0x0CBDB237CF9D515CULL, 0xA7CEEC54ABBF57E3ULL, 0x9335CF0F1AFAF7B2ULL, 
            0x8359374D2C099ECBULL, 0xF0C3339B3C9CF42FULL, 0x892257004475AC10ULL, 0x9E655FDF082959A9ULL, 
            0xEB66732182E46635ULL, 0xE8D20504BE1CF213ULL, 0xB9B79393D5AF918DULL, 0xEEA1CC2A26011A00ULL, 
            0x6AA0999A82C5FDF5ULL, 0x86FE709FB64B4C39ULL, 0xC8381CD9B891E7C0ULL, 0xB8C7046868471591ULL, 
            0xD937FBEF4E347F24ULL, 0x442CCAB154586458ULL, 0x48CFB3BEA6F9E993ULL, 0xE83704A73784C243ULL, 
            0xA05D330F01F651E8ULL, 0xA650403DA68652C3ULL, 0x42A59FA1FE7CA335ULL, 0xC0C0D4F02816176AULL, 
            0x3FB0685206FB8780ULL, 0x684B4DBF68C01214ULL, 0x396DBB5A65651CCEULL, 0x7004E3D300CA7F91ULL
        },
        {
            0x0544F4040BFB8A39ULL, 0x3D75A5F6BA9EDD72ULL, 0xFF054215D177CC9EULL, 0x7D6E2550005CFBC5ULL, 
            0x5FF1AF0877E95F68ULL, 0x3B08A7E3688A9812ULL, 0x9880C63E7E4ED571ULL, 0x10FDE6B35F900470ULL, 
            0xB4E36FA630A158F3ULL, 0xE3BD4194C88FCB05ULL, 0x986C4E2F59824E77ULL, 0x6EC774A24DFA4172ULL, 
            0xADE1CB0AE6EE50F8ULL, 0x83AE3D37BBA71BD9ULL, 0x1A0CA27EAEAD7891ULL, 0xED674BB65349FC0CULL, 
            0x92DA1F3B2E11A4ADULL, 0x95EF1591D8878BC9ULL, 0x36009A9D4AE4B8EBULL, 0x1061CE352EF0D66EULL, 
            0x63F40C2EFD4926BDULL, 0x64274917E9F8FD3EULL, 0xB8E45867B49DF3F9ULL, 0x6EB892362D972780ULL, 
            0x62DD04E31E220775ULL, 0x322D14764B4DE764ULL, 0x26D0D59B46FA5533ULL, 0x483D7AEC916D55F8ULL, 
            0x333E0FE6A0226E4CULL, 0xDBC1FC9939B51263ULL, 0xB5C0725D91A3EE63ULL, 0x268089FF1FB94DEBULL
        },
        {
            0xDC2CA7923D9CFD75ULL, 0xA6153FA3B41EB69FULL, 0x77D53512E25AF51BULL, 0x415154FEE1FBA50CULL, 
            0x6692589C318B7965ULL, 0x7735F507E7DAE6BEULL, 0xE0A43CBB11C34B18ULL, 0x6561BFEA6B265A14ULL, 
            0xD74A4B281AA7FF12ULL, 0x5360011AC58E4ED2ULL, 0x0F73F442A4A178BBULL, 0x83038E4211652A47ULL, 
            0xC379E666611A0E19ULL, 0xC318D3CD29D546AEULL, 0x276B5CC904484B87ULL, 0xB92F7E56D2C0A078ULL, 
            0xE1650757485318C4ULL, 0xA8486520AEE4E803ULL, 0xF6A5B7C8DD2812E1ULL, 0x07E1E435544F819FULL, 
            0x4DBD89A83C8CD875ULL, 0x3272E7D44A7CC649ULL, 0xB3ED3B37EFF10100ULL, 0x456298921826C258ULL, 
            0xEED089BFFD36726AULL, 0xE1D6FF8767DA776CULL, 0xA3A35BA8BDAE2148ULL, 0x19DAA59927FA00DEULL, 
            0x100408AA27E6AB5CULL, 0x0B36F21E372E87DEULL, 0xFE08A7456DA78A1EULL, 0x2C0194E51F5C063BULL
        },
        {
            0xDF091E547C45BFD6ULL, 0x841145513FAA2F65ULL, 0x3979D13D5CB26248ULL, 0x83376869D3CA8022ULL, 
            0x961CA9BA3ABE7891ULL, 0x83B9F56DFFD5FF6CULL, 0x5EEBB703A8175BD7ULL, 0xAAD2B951D95AAF11ULL, 
            0x96B1D52534030517ULL, 0xC74762D3B9341295ULL, 0xCD6C8A5D67323D5EULL, 0x81A461A86280DA26ULL, 
            0xE0691F66A65FA2E6ULL, 0x4FFA5D56034B8692ULL, 0xCF84511AA66B8E93ULL, 0x656CF1F9D6B5DCF3ULL, 
            0x22966F991630A890ULL, 0x562A9D9A07A0A24CULL, 0x4CB484389F782575ULL, 0xAE362854A5262CDCULL, 
            0xE521D8612679517BULL, 0xEDAF76E8A066B986ULL, 0x0EC8171C96A20A87ULL, 0x9D583FFCA6BB3326ULL, 
            0xB202E548C63EADE8ULL, 0x3912F867CFABC878ULL, 0x65507F58D45E765CULL, 0xB2BD21ED9DCA547DULL, 
            0x02A1B7D0EC7C0A82ULL, 0x18D81E78560A8C3FULL, 0x6B3EC5FF527F9EA8ULL, 0xF25B5E20B8F33D14ULL
        },
        {
            0xCB11C33B88E30CE4ULL, 0x9731C9C99583BE3CULL, 0x1E8D26EE6BBC22EDULL, 0x0EF3AEE0244ABB2DULL, 
            0x6E5A2C40A4B62D36ULL, 0x2F25775505989D83ULL, 0x0B8F09A4FEE589FFULL, 0xF02FE4579C4ED473ULL, 
            0x1627AED7A8DE9E5CULL, 0xB732C7DD11FCC7EDULL, 0xCE068FC216FB1F7CULL, 0x050FD0B07AAA596DULL, 
            0x7AA12C341A465C8BULL, 0x3B855A40DB0A7716ULL, 0x22A083AAFC58FCE4ULL, 0xCBAB1A892ABC5302ULL, 
            0x52A9468A115FAF9FULL, 0x3D58A971CB369FDDULL, 0x93AF2513799657B2ULL, 0xB1DCA760CD813315ULL, 
            0xFD41831B4DE88C8BULL, 0xEC1D3A3AE23ABFFAULL, 0x7A6CF1D339351CC3ULL, 0xC9F94F8FD436CC61ULL, 
            0x1ABA7C33B1D41008ULL, 0xC932CFEC3B92A0FAULL, 0xA2C4C25D7A6CBDB0ULL, 0xF2F40DE6A34B0B47ULL, 
            0xF68072610BD797B0ULL, 0xF8E7F2935E5090E4ULL, 0xE4864052B05D41BDULL, 0x0B5EE915A92D2758ULL
        }
    },
    {
        {
            0x8255DB3B6449D3F0ULL, 0xB3478F691B2DB354ULL, 0x862129A73F7E9BC5ULL, 0xABE5467A60E3CF39ULL, 
            0xCC33F79CC04E04ECULL, 0xD62A58126B11BDC9ULL, 0x3F37114ED731DB8FULL, 0xF92474ADC174888EULL, 
            0xB707872D269DB9C8ULL, 0x94F020C35DB4D728ULL, 0x7985A5682B54D00EULL, 0xB0D7F0BD161978BBULL, 
            0x8459DCE72DADB222ULL, 0xAD52257918C63FAAULL, 0x3C8E44A3091CD561ULL, 0x2B3306C1D24407EFULL, 
            0x25C800A091F6CAE9ULL, 0x993235F6C8CA6600ULL, 0xED00E6B0D1B07902ULL, 0x7DA5FD28825009F6ULL, 
            0xC59B3736790F7A23ULL, 0x48302DBC60D6D796ULL, 0x165BEDDE336E7228ULL, 0x0FEEB2E2548C4559ULL, 
            0x89848A071C5D0326ULL, 0xD820A3F07FFDD6ECULL, 0xD13409978584482EULL, 0x3131AE813B35B4C3ULL, 
            0xB74F7463277786C4ULL, 0x495F6B23A8C112CBULL, 0xA472D95DCD06C714ULL, 0xE11A2F87181797CAULL
        },
        {
            0x75A9F9A20C1AD532ULL, 0xCEFF5B2C9F7732A3ULL, 0x19157F52F911F73FULL, 0x7294143BE9574C61ULL, 
            0x49A5B4FC15D537E7ULL, 0x2C7C743E63EF3542ULL, 0xD95150508FBE149BULL, 0x9AF5A550BEACD3BAULL, 
            0xC9816A267260D5ECULL, 0x6A261747058136D4ULL, 0x13FC6F3132BBDC39ULL, 0x395425FDEC85FA50ULL, 
            0x93DBE2D2FCCD7CBAULL, 0xBAF8FD3D2144339BULL, 0xE1E80C29D6569277ULL, 0x04C68B8F83681A82ULL, 
            0xD86465FB4018E91DULL, 0xB54F5EE7C9C7ED8FULL, 0x209EC48ECD97BA99ULL, 0xB159D127E5B3597EULL, 
            0xD4ADBE21A6098BF8ULL, 0x27BA51D23BD5B41BULL, 0x2EC35AEC7228CEA4ULL, 0xC8791EFC67D8D2D1ULL, 
            0x57982404C45A8A93ULL, 0x9F876955C6477CCAULL, 0xBA15BE2F7A572292ULL, 0x4B9996F7F8B7DCFCULL, 
            0xA8541858364F98F8ULL, 0x562349C8E51855F1ULL, 0x2CD711E223FF6123ULL, 0x04AA3A878A929C5CULL
        },
        {
            0x5414B9B4BB2929A2ULL, 0xE4E1F1008684B2A5ULL, 0xA5512E84227919C0ULL, 0x492D4AA74CB36A4DULL, 
            0x9E46286A7F9A651DULL, 0x6D7B3ED406CEC162ULL, 0x18C8C702FF52B57EULL, 0x5FF645F48E182D70ULL, 
            0x3EC99CF992CAB6B6ULL, 0x410EB9AFAF6C06F7ULL, 0x4D1783DA9240B9CBULL, 0xF4E0DEE2590DCFE6ULL, 
            0x59A6D91BDA2885F0ULL, 0x618A0DFB300ED6D6ULL, 0x6AC2C43038E6B7F2ULL, 0x9F03AE0F218EDEE9ULL, 
            0x109CB737F6811098ULL, 0x896B1A47C0997B24ULL, 0x663DB310D1EBDEBBULL, 0xE19C7219335D39C5ULL, 
            0x8A024D495E672872ULL, 0x473E76FA035FA5C4ULL, 0x3E11CDB1BBBF0782ULL, 0x3E0420C122CB0FC6ULL, 
            0xE212A86C0E19806BULL, 0xC2C9E17BD4E9A328ULL, 0xE1FD125806C21B41ULL, 0x2F1CFFEDAE0F8D81ULL, 
            0xBD33BE56AEE45A0CULL, 0x811FB4F9B393871DULL, 0x8045A1A53E9E920DULL, 0xE48AA826DAD1FDECULL
        },
        {
            0xC870F86012CF9ADAULL, 0x1D1188B431734683ULL, 0x3A5864AB0B424A24ULL, 0x9A185B48F78D6C73ULL, 
            0x9E9674214CA5BDF2ULL, 0xC10B8C78A9D5B10DULL, 0x1284B7C352D03A98ULL, 0x4D4E57012CBFF3F9ULL, 
            0x6E70F571C72DC2C4ULL, 0xFD3855502DD9C432ULL, 0xF2BFFBFADB4C7F59ULL, 0xEEFE66B0059D4194ULL, 
            0x6B66AD886B985E53ULL, 0xE2F86E60F6C91636ULL, 0xB2B3329040BFA6B2ULL, 0xCC58F0ED9E6F2C4BULL, 
            0x979488B18D59003AULL, 0x8476A2AF1E954285ULL, 0x22EAA47C279165EFULL, 0xF4634761D8D7E207ULL, 
            0x0E36A8A609561E9BULL, 0xD683259FA400CEA4ULL, 0xC9B388DA86D124AFULL, 0xF6C8F8B5F8BF1DDBULL, 
            0xEB86264C1F138BF9ULL, 0x9765F0891A861A7AULL, 0x40DC6E99608AF162ULL, 0x7DDB524CCA2CF01BULL, 
            0x797D57C4700AF203ULL, 0x26C741DB91935DFFULL, 0x35DE96FB2C2108BCULL, 0xD680174C133D1949ULL
        },
        {
            0x6469A19C2FAAC527ULL, 0x8CB9ECD0968CE73CULL, 0xC9FB48DC351D9763ULL, 0x2D017CA7972C2C20ULL, 
            0xBE5D6C25DF293148ULL, 0xFACCB3FA31C3B0D7ULL, 0xC1E1F5C22B17838EULL, 0x0306963491E7750EULL, 
            0x83D671EFAA96A6C6ULL, 0xBA4FB53C9C0D29EBULL, 0xB78B8D23B0F43DE7ULL, 0x979AE3A9575F9EF4ULL, 
            0xBE9804237054C60DULL, 0x9544BDE7CFF92C3AULL, 0x6D37233BF493CC2BULL, 0xF29FA986684ADF45ULL, 
            0x4B486407885104A2ULL, 0xD782BD093C4CC595ULL, 0x63DFECF90EA22CDBULL, 0xD38D0FA3781379ABULL, 
            0x8AE4871D5A322BDFULL, 0x2F785C80971F619DULL, 0x1B75ED2495B0D7E1ULL, 0xCE79F834F675767EULL, 
            0x0157B42DDF47A637ULL, 0x7A41F36732747A0CULL, 0x52B6F5910EA7A3A2ULL, 0xBC421965BCFC04CEULL, 
            0x84C8B83333D7A4BEULL, 0xA4B4621B5C04010BULL, 0x9EC228CAEE741B0EULL, 0xDEA31785B2C2AA4FULL
        },
        {
            0x143F2D971AE2F9DBULL, 0x5DC321586F9F52A8ULL, 0xCD0997227746763FULL, 0xB7A29D1A5CAE7AB4ULL, 
            0x818F5524C07108C2ULL, 0x97E2008DEA93AC15ULL, 0x88FCA1828F45C078ULL, 0x8853D7D771DEB206ULL, 
            0xEF01CD60A61B1770ULL, 0x984A218913FC2F2DULL, 0x67EE51D92A9AE03DULL, 0xD04B6E1E72B1BD63ULL, 
            0x2E8F86B1B025EA10ULL, 0x90EB4129BB1EA74FULL, 0x75D1D10B752EEE50ULL, 0x8AEA6749AE0DDB43ULL, 
            0x6F64AF731D9CF670ULL, 0xCCF1DD5A9BBE8A85ULL, 0x991E5609A9961D09ULL, 0x5982EA9B373F3192ULL, 
            0x4AE32AE14CF44DA1ULL, 0x9BCE3A75B5834187ULL, 0x3E33335E3EEA1434ULL, 0xD5A5B60DE1F53089ULL, 
            0xE65F5A6EBA06A011ULL, 0xAC31E12759B4E8FEULL, 0x13F1BF9EAA8AC133ULL, 0x04C201D4897882DDULL, 
            0xC9DCB34A1602BA70ULL, 0x9692CBA21E096AABULL, 0x07A582A81D56D961ULL, 0x96C5B397E9E37661ULL
        }
    },
    {
        {
            0xC219A88BEC68332FULL, 0xBD78E4CB848D4FD6ULL, 0xFFBF2C55E2D9CF28ULL, 0xFA5FB0DF2AB84DFFULL, 
            0x191030036E430A19ULL, 0x557E2451047BCAF1ULL, 0x223993B4B8FC95CEULL, 0xE4F401E579A3DBA1ULL, 
            0xC23EB70FCE451332ULL, 0x251D741F1BE37B33ULL, 0xA38BBCB01B47BA56ULL, 0x36C54DC840858250ULL, 
            0x20B247A8B6CB22D6ULL, 0xA59F89634A50C375ULL, 0xD9F243137FBA2364ULL, 0xF04100829D0C6AE3ULL, 
            0xBC1F246E78B4AD9BULL, 0xD463E4E48EE5A8E9ULL, 0x30724391259B7D9BULL, 0xF5FD3A92EC08BF39ULL, 
            0xE24F8502A8A01C91ULL, 0xDE66101EA7B80AE6ULL, 0x1607F37671662D2DULL, 0xCB5335EC73F7A4B4ULL, 
            0xEAC6B0DFD53B50E3ULL, 0x8253D161F1B0DD68ULL, 0x521B325B5AECC368ULL, 0xD84FDACF8CE99DE2ULL, 
            0x7740B38761237334ULL, 0xDB0DE8FDE0A6BABEULL, 0x5FC964F864BA7BD3ULL, 0x6B24738F7E3A761EULL
        },
        {
            0xE87AACA5B9AA8092ULL, 0x1AB5B9D640B53BD4ULL, 0xF2CD086B90CA7A16ULL, 0x46B63543899466CAULL, 
            0xC8EA8BA59CD8C2E1ULL, 0x52A610FAB1FCCE38ULL, 0x201B2A80A01752ECULL, 0xC4A3CEE4AB18B9B7ULL, 
            0xFFD293614081FF7CULL, 0xC18AE49D3AD9077CULL, 0xDF608204362CD95BULL, 0xD00D21A418BF9F5DULL, 
            0x5F720AE9C6C2BBF3ULL, 0xC8F78FAE7F4BE951ULL, 0xA1FD14F38984C325ULL, 0x4974B3481B1FFAC8ULL, 
            0xB3492E8DE72C4AD2ULL, 0x29365C8825EBD4C4ULL, 0x5BF0CB1BF1D49ADDULL, 0x6967987BEAE84A76ULL, 
            0xD05DBE644C619FE5ULL, 0xF68421910CA57BC8ULL, 0xD74573EEAC1D91D9ULL, 0xA8CD5068760B3CC1ULL, 
            0x120584EBEC6FBD32ULL, 0xCE38130CC961A0E6ULL, 0xF6A033004B2FB74DULL, 0x3171E3DDA22A732BULL, 
            0xA94D8EB2ACF7B5DEULL, 0x070447AAFBA709A6ULL, 0x55AB932D490E2130ULL, 0xFC03D536E2237488ULL
        },
        {
            0xF037BBEFC6617B09ULL, 0xDEE7167642D4A657ULL, 0xE55FDAFD69F5C9C9ULL, 0xDEF4ED268B7ADB21ULL, 
            0x0D54F8D446B2C62FULL, 0x7F157E4B3895B2C0ULL, 0x9608495C48F74113ULL, 0xBEC5FCEA3E9C28F8ULL, 
            0xC859EC3C75FCD0C5ULL, 0xD42680F0D3470CB1ULL, 0x525F8E7FFF09B036ULL, 0x6917DA58257414C8ULL, 
            0x8806660094980115ULL, 0x8B2E94FCD48DAE15ULL, 0x0959CBB65435E250ULL, 0xFC1079BD993889E8ULL, 
            0x9C878399BFE7F667ULL, 0x07563C51E1D46EB0ULL, 0x37ED0AD91D51DC5FULL, 0x4B46F67A6F982E96ULL, 
            0x3048A4CB16A51A90ULL, 0xE755CD5E6D4678F7ULL, 0x37FF0E3C2339348AULL, 0x5DD4127A09BD5472ULL, 
            0x1632D542E8303B01ULL, 0xE1E4522B0FCBA7C7ULL, 0x9DCD1D8AC81A9478ULL, 0x47399CB85E69C7DEULL, 
            0xC145AC8D83DA4DD1ULL, 0x74613F4E873E03A2ULL, 0x91246C11894697C2ULL, 0x5B5EFEA46B806A0CULL
        },
        {
            0xD1CA9E34A4F50399ULL, 0xA746F4E777B4B252ULL, 0xADD2606D7DDF2CE8ULL, 0xA3C48C9A4D33F82DULL, 
            0x8160D8C37B9095AEULL, 0x3C09E347A1BC91C3ULL, 0x826B95606291CF70ULL, 0x6D47FE9053AAD46AULL, 
            0x4DDB8C200E4008A8ULL, 0x9FC30062E47FF5AFULL, 0x0E2FFAFE32E6B989ULL, 0x2CA192F443671987ULL, 
            0x0E7554359892EE15ULL, 0x2807E84C9F52A1E6ULL, 0xA359E3B22298DFFDULL, 0x22E0586494540129ULL, 
            0x5683CBB0E62C18F9ULL, 0xB23C2B9A373D5DB6ULL, 0x07CF1B64EC010C70ULL, 0xB684EF4C26744DDBULL, 
            0x4D1ADDFB49A2DEFCULL, 0x5204FDA84F8617FCULL, 0xEF77FA782C78E4D7ULL, 0xCB577E8212B1F57CULL, 
            0xC4DBCAD37C473894ULL, 0xCF77D022A80D6085ULL, 0xA7873A09F212A4D2ULL, 0x96D9F049A028F5D1ULL, 
            0xBC8B71EC202CC5E9ULL, 0x659ACB28362F7EE4ULL, 0x7134257DAC602843ULL, 0x4B9127A60C6F4D69ULL
        },
        {
            0x13F03C07DCA02451ULL, 0xA579C930718F957FULL, 0x0C1D482453A75882ULL, 0x92525F15ED0E87ACULL, 
            0x2C572ACD9F537595ULL, 0x15FE6D2D3AB63774ULL, 0x9EDE24B4D9D5D1B2ULL, 0xAFE67B1136DD86ADULL, 
            0x243C12ABF377DBB7ULL, 0x5BDD2994C54D1358ULL, 0x03D17F12603C85DFULL, 0x8BE460EAB5C670C7ULL, 
            0x3BA771E9D2C31D48ULL, 0x4B6930AD484F7B84ULL, 0xC88DBDD857F40C42ULL, 0x215C0DBC06874AB5ULL, 
            0xCB305C9A5D25C3C0ULL, 0x35253651E9756C2FULL, 0x8DE0A3DD6F1786C7ULL, 0x78D2941D433E6DB8ULL, 
            0xCEEDB24F84E6D07EULL, 0x7DA25A284A447A39ULL, 0xDA51EE0A1CBF8104ULL, 0xBBE75C59108601FDULL, 
            0x50F0CE252750D393ULL, 0x9CF3A3D5268E03D1ULL, 0x6BBBFE516BB8392DULL, 0x14B89A0CD883B746ULL, 
            0x3DBF0A976A339CA0ULL, 0xD02FD379F9CA1ECAULL, 0xCFF70E8873301024ULL, 0xF358429431B1E35DULL
        },
        {
            0xAEF8752DEF06965BULL, 0x1A3FE6C510CEC9B8ULL, 0x554EECAE9E906107ULL, 0x6CD1B38DBAAEEBD5ULL, 
            0x7B203888200D981FULL, 0x9FE8FEF935815606ULL, 0x85EE467D392B2C00ULL, 0xE2DC82631F8BD8C9ULL, 
            0xA716105890CEBBA7ULL, 0xD4AA0D274B54A0C9ULL, 0x83844CD115595ED0ULL, 0xF21DBFEDC97BBEAEULL, 
            0xB45143D09FEA5D24ULL, 0x8F3DB0992D85F238ULL, 0x74840D37BEFB1560ULL, 0x70815194412DF1F4ULL, 
            0xAC5736DB8D0A199EULL, 0xE375D274ED39593AULL, 0xA37E056A22D10D1AULL, 0xFE6266011AF06902ULL, 
            0xF6A51633C65DE0CCULL, 0x399A29BF6BBDF03CULL, 0x52042A694D3358E2ULL, 0xA604E7F7059488DDULL, 
            0x6992545B932A9A52ULL, 0xDBEACAA569CE4D69ULL, 0x249153E0B5806091ULL, 0xD135BF9E0A8C6965ULL, 
            0xDA9A29AC1848ED8DULL, 0xFC408BAECC6F71CAULL, 0x8781CB556213AF18ULL, 0xF417C33C174FE7C9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseEConstants = {
    0x534CA9DFDBC644E4ULL,
    0x6ADD4D6B8336F076ULL,
    0xED05C8FE6EF7A36AULL,
    0x534CA9DFDBC644E4ULL,
    0x6ADD4D6B8336F076ULL,
    0xED05C8FE6EF7A36AULL,
    0xDF3459AED577B200ULL,
    0x50EEA4CD300C0A39ULL,
    0xBD,
    0x21,
    0xC6,
    0x98,
    0xDE,
    0xB6,
    0x3D,
    0x45
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseFSalts = {
    {
        {
            0xEE98FDE21414FF5CULL, 0x2606FD202C10E802ULL, 0xB464C1F122DC8469ULL, 0x437E317B7E36B346ULL, 
            0xC4C32CE22EEDC42DULL, 0xBD7BF8AB98B93D75ULL, 0x4BDD8550851139DDULL, 0x4F2697C479E94426ULL, 
            0xB3D8295B7A7B6AE0ULL, 0x1419ED8107685D5CULL, 0x3EB0A5F9F20A8901ULL, 0xED77EF9E52E14F03ULL, 
            0x17DC3A28F571284BULL, 0xA4AEECF82FA5F5CCULL, 0xA76EF1A0039C917AULL, 0x1ED99D1B734AFE8CULL, 
            0xE3B3F616F3152FBEULL, 0x290E372F69972001ULL, 0xFD749A09F9DB6914ULL, 0x96CBECF49AC99BA3ULL, 
            0x737BE629EA8DA0CAULL, 0xB0C6E45D9DA8DD47ULL, 0x5A0AB99FEB4D1EBFULL, 0x9772D1CF70BD3039ULL, 
            0x09018A0FF9BC6E51ULL, 0xDD88F0AB9E5847E3ULL, 0x93C74D2F7C689699ULL, 0x06D5F89E89C6DF82ULL, 
            0x2149B86E1A58A091ULL, 0x5D425F15385E84CFULL, 0x8884B4BC099CDE77ULL, 0x52FE12F69EE74FEBULL
        },
        {
            0x8726A4A7CB0120F7ULL, 0x8DDAE042CCA3EAEFULL, 0xDB5F66F47D06F9F9ULL, 0x410CB3E353ED64BDULL, 
            0x03243F2A300CACB1ULL, 0x3EC2F6E572B9039CULL, 0x7D534964843FBF41ULL, 0x624655C11186AC2FULL, 
            0x4DB5802363636BF3ULL, 0xA77E2EDDFF5CFB17ULL, 0xC837D54862CE999FULL, 0x0B40C9006B9E9585ULL, 
            0xCA82695FF026776FULL, 0x614EC8F0917C6D33ULL, 0x744BC6BC203949E0ULL, 0x5A01FD8D7C2E8C5DULL, 
            0xE42A3929124A1011ULL, 0xD2EDAF7C24120AA9ULL, 0x84504490A51C1199ULL, 0x1283885E31942D13ULL, 
            0x424F9E83C2161559ULL, 0xFFD599D86B2A0A02ULL, 0x8DB56D05C23CD9D3ULL, 0xEA36F5F9BBD3C3DCULL, 
            0x7E46A3C3FD578B12ULL, 0xE7F9979A59E36931ULL, 0x5934F41D2E8B5481ULL, 0xE54DF2EB84D6D2C3ULL, 
            0xD9288B3F483BFFEDULL, 0xA26AADAB134EDD30ULL, 0xC6B127A95322C75AULL, 0xE2A9E36FB092736EULL
        },
        {
            0xB0FA5C75E695BB92ULL, 0x25D5272A92614BC7ULL, 0xE5756E6B2922642EULL, 0x2DB16E22E4445501ULL, 
            0x8F7A9EF6F31C5ECBULL, 0xF97676D0140C6568ULL, 0x0BF2F6087F5CDA91ULL, 0x3457F2C52F4D2D6CULL, 
            0xE00D20E8AA414250ULL, 0x1914E8711F063944ULL, 0x3BB9773FF485BCC3ULL, 0xA16878482ED29862ULL, 
            0xE1D0DE25750A1588ULL, 0x1FBE7E657921E136ULL, 0x7F18AAA10E9C2A82ULL, 0xE3A6E7A8EA157D20ULL, 
            0x9F632304211CBAE8ULL, 0x863BF0E75590E997ULL, 0x1687C4F4CD0AE9CFULL, 0x92D3894133245A1DULL, 
            0xC97A25E4B0E933A0ULL, 0xC2742E7EEFAF52AFULL, 0xFE221855BB07A27CULL, 0x37EDA452A81F07A6ULL, 
            0xB39ACF6F3A353DB3ULL, 0x473FDCC1AD4CB50AULL, 0x281D4257D7A84914ULL, 0xFE7EF09CE063359EULL, 
            0x54E3E2B570CF33BAULL, 0x375C157D8560A5CAULL, 0xFE032F5FE5197BFDULL, 0xF9DBC5D8CA91008CULL
        },
        {
            0xFD9276FB4359A1BFULL, 0x27280C1B12F6AC30ULL, 0x259AC3FF4CE3BB24ULL, 0x5586312F8B9FFF28ULL, 
            0xECF58201939AD73BULL, 0x2BA9184356940C22ULL, 0x5E6F64E9D2A1BAE4ULL, 0xA4FB59FDE4AA1FE2ULL, 
            0xE209C0810377B350ULL, 0xDCC7723DF2623654ULL, 0x5FD9B174C9EFE867ULL, 0x2E3F738589DE60DEULL, 
            0x8009F2CD2D902D60ULL, 0xAFD4568C863E9027ULL, 0xA01C41E9DD283750ULL, 0xAAEF118F47ADAB8EULL, 
            0x7F583BC386755C80ULL, 0xDE3090BBA04298F6ULL, 0xE96A7711EE97F97CULL, 0x5FBE9B5A976C54EDULL, 
            0x46F416814EA1314BULL, 0x42C5C86FC91579E2ULL, 0x027D87DEC27062F5ULL, 0xE9028427B6634944ULL, 
            0x511AEE08AE734811ULL, 0x6E8B30819D8F697BULL, 0x1E914BF6CD75460AULL, 0xEA6243CD1DF1A0DBULL, 
            0xB0F402450881A88CULL, 0x2D2E393E3733E8FFULL, 0x39CEC075D926612FULL, 0xD77A962B5B736166ULL
        },
        {
            0xAF75B6D0760353FDULL, 0x56FBFE4E9EA5556FULL, 0x3FC85C1A3906BA11ULL, 0xBADCEC5D753FE457ULL, 
            0x73B47B305C7520ACULL, 0x8D781493526D54F5ULL, 0xED9D4BDF1616874AULL, 0x5545D9E81D3BD89FULL, 
            0xCD126002B7FC99EEULL, 0x61051CE464F60F72ULL, 0x667503EAE324E5E3ULL, 0xFD2D18E756F1891CULL, 
            0xE05116ADA2405C06ULL, 0x6598354D22B8D470ULL, 0x590ADB7A06FF97D3ULL, 0x7538DE3E59F8F5E3ULL, 
            0x2EDC2B24FCC06E2EULL, 0xDC5B4CE5D0B8FD30ULL, 0x16DE7902755B6ACBULL, 0xCF9017E10287A793ULL, 
            0xF60674588A391048ULL, 0x90C07AE6FC8700F2ULL, 0x90BFD58D6201B916ULL, 0x25BFA74504D89B6DULL, 
            0x669F3362C6FC4CC8ULL, 0x200963867A5686E7ULL, 0x6AF9394CA0CAC18AULL, 0x0729B414FB3285FAULL, 
            0xB289D69259B42233ULL, 0xF459E2BD5D059016ULL, 0x87A801A9ECC4E7D6ULL, 0x804649D217F6875CULL
        },
        {
            0x99FF7D1CC8F51A0DULL, 0x0D1BDBF5C4A3ACFAULL, 0xCEE5C6DCD74E0161ULL, 0x4B4E69735DB269CEULL, 
            0x8D12410770561EE9ULL, 0x29134FDE0CDC1361ULL, 0x350730BD4B328962ULL, 0x248315CA21DE9F3AULL, 
            0x61CD859518CD1A9CULL, 0x90EF591FE17996A9ULL, 0xEF5523EB539C9B40ULL, 0x640CF6931CC3D83DULL, 
            0x579AD049E9863CF3ULL, 0x9A5DFAA611022EF9ULL, 0x9BB039BA841E34A7ULL, 0xECD6554F43804323ULL, 
            0x0EF08BC4435DF550ULL, 0x812F3FAFF75EBEF2ULL, 0x13362596BD10CF8DULL, 0xFDE811F1A36CB035ULL, 
            0x4EC9D47023B536E2ULL, 0xEA5BA98026BB09EBULL, 0x49AF69EB14A72D9CULL, 0x16134B13C0704926ULL, 
            0x6C8B895E7423AB00ULL, 0xD1434A2BCAF0D6A0ULL, 0x92DCC867F0C03BA0ULL, 0xDA1EA804A86E7D79ULL, 
            0x1F3BCEF3F41E8914ULL, 0xC306503D62310689ULL, 0x65D8F156468D7A80ULL, 0x3E6B391BE4F84901ULL
        }
    },
    {
        {
            0x389622CFE95009BCULL, 0xD97E764830180DB0ULL, 0x345D3AA5ADEE0C67ULL, 0x7BE0B50CC25D87A1ULL, 
            0xF89241835750E964ULL, 0x7B6B48ED57878DA7ULL, 0xEAFAB9CA4836C27BULL, 0x4122BF2AEBF5310AULL, 
            0x795C2B35CC26052DULL, 0x2EFE912F025456A7ULL, 0x4A6AE081108EC443ULL, 0x9B653F2486CB10EDULL, 
            0x2B90E67E104E63CDULL, 0xA114784A3DE8972FULL, 0x2B6E6E447010BCFEULL, 0x906205CEF09F95DDULL, 
            0xA0245AD122B1CC8DULL, 0x7EE572BD460260BDULL, 0x1A8AE44BD1104DDAULL, 0xF1093811FF5C8877ULL, 
            0x4A389AD1D82741A9ULL, 0x9E0EB5E60907B3CCULL, 0x8E3958022F813C7CULL, 0xB86A5384ABCC4CF1ULL, 
            0xB3CDA9F6E843958AULL, 0x5F91673920CE5563ULL, 0x80DB113AE858C6B9ULL, 0xA13B2E8A71794DC4ULL, 
            0x673FAE60AF1BECACULL, 0x36145898CC6ECDFCULL, 0x1B1E9F05261E2617ULL, 0x1F5DAA227207CAC5ULL
        },
        {
            0x1D95649AFD8E9CEBULL, 0xBE4DD005C543F2D9ULL, 0xDE7862D3B213F2A9ULL, 0x71789E0F554F8319ULL, 
            0xC56636881B2D6C7AULL, 0xF120789BEE4E1BC7ULL, 0xBADC82BF4C1943DFULL, 0x8EB54B4BCF06F566ULL, 
            0xEF659EC0782BF81AULL, 0x20CD45B3A7D9382DULL, 0x16A1FCE98B4D2172ULL, 0x09C957AF98692CE1ULL, 
            0x120FC25DD99851BDULL, 0x2D2455B74DB04624ULL, 0xFC8CB7813DE8D169ULL, 0xF44A56C1ACD12F39ULL, 
            0xAC8CF7F501EA6DBAULL, 0x5F5253B4B54F7088ULL, 0xC4BB729411D795E9ULL, 0x930F8D79E016B6E0ULL, 
            0x5ADF7A7A3D689544ULL, 0x9254A54AB3D3A913ULL, 0xC934646E19800CCEULL, 0x0106F58E4715B369ULL, 
            0x567F21680F93E7A8ULL, 0x8AF35B9D72FEA50DULL, 0x48E024299784FC30ULL, 0xCF738E910FF610EEULL, 
            0x5E0F8E749B6B29CCULL, 0x2488A2E3F163802BULL, 0x49C289D63F78FE6FULL, 0x94FF58B5743508F6ULL
        },
        {
            0x4EA847062940A8E5ULL, 0xF57B08F8547B4439ULL, 0xF0CF9AC729500D04ULL, 0xEC9F7A75E90061C4ULL, 
            0x4DF81ED785B2B408ULL, 0x0873256CA07756E5ULL, 0x8205F5CB9D24D008ULL, 0xAAFEAED85C0F43C6ULL, 
            0x6989BECE84A5EB27ULL, 0xAE27A3D347194816ULL, 0x2C48BCC004F84859ULL, 0xC55174FA46AF4BB1ULL, 
            0x3321E223350FD95BULL, 0x1615ABA10FAD6412ULL, 0x6A17F481544011B2ULL, 0x92E4B5521E9D9DCCULL, 
            0xD29D2C00DCD97943ULL, 0x7FBB885623F323B4ULL, 0xF341FE2596D2D74AULL, 0x8F83A0A958A8C17DULL, 
            0xB2BBC3AE8974E464ULL, 0xF5991E9D3771459FULL, 0x01CC3E64DA728ED1ULL, 0x48BB7939B08A14C7ULL, 
            0x0768E3D16C4AB6E9ULL, 0xD600EFF7AF29A106ULL, 0xD68568149718FD64ULL, 0x72C86C028D8FCF04ULL, 
            0x05745744339EAB7EULL, 0x119E6781E3BF0BC5ULL, 0x11AD52910B18034DULL, 0xCB475F0FF222B7A4ULL
        },
        {
            0x93C838D9338CE6B3ULL, 0x0DBDCB3C74E3685EULL, 0x175B537A526CC1E7ULL, 0x107E84A3B1EB9603ULL, 
            0xF8EFB78FAF9C1037ULL, 0x9068B5301446C685ULL, 0x6DA7C961D52FA6ABULL, 0x76DDA39136A52D39ULL, 
            0x029BBDC11F799CB8ULL, 0x1FE018167DE943A9ULL, 0x60FFF83F51F2CBFEULL, 0xB48E40A634C95F1EULL, 
            0x19CC54D004385560ULL, 0xFEC7B129F5FD7C90ULL, 0x716717E57BD46DD1ULL, 0x0299B1138A06ECD7ULL, 
            0xE901125EAAC9C1A8ULL, 0x92FD9FCE7405279BULL, 0x89AE71C1E6521D6FULL, 0xB8D34CD3DE36D4DDULL, 
            0xD4014DBD72FC704AULL, 0x42DAFE2DA61A820DULL, 0x9C7D4FE659257858ULL, 0x573996E6DAF1E55DULL, 
            0x22609FDB1FA8F6CEULL, 0x392DE755EE43682FULL, 0x903F665F5328934DULL, 0x463684C894C90F18ULL, 
            0xBB651820209D42D1ULL, 0x5B3C66C35B4CB869ULL, 0xA4365B923F1E06E2ULL, 0xBFAA15674B7457DAULL
        },
        {
            0xADCA1088568ED5E3ULL, 0xC66F61BF70BC0AA3ULL, 0x13C54DC458969056ULL, 0xE5D04724B5470619ULL, 
            0xB795E89221267C33ULL, 0x8E76BAC1ED715C27ULL, 0x01CE67F3B517742DULL, 0x534AB0043C63B96AULL, 
            0xDF0CE149121F43E7ULL, 0xF5A6E031ABE75299ULL, 0x1AF06C0DA81BB15FULL, 0xE169A7E40CC4AD0EULL, 
            0x32BC23A95C928E5AULL, 0xD82C9BDF948DC36AULL, 0x4491FDA2D18EDA5CULL, 0xAEEC59524CA1DC39ULL, 
            0x9A63DADFEDE87AD3ULL, 0x82CE27F10F01648CULL, 0xC706563F19445918ULL, 0x99C0C4188093D1FDULL, 
            0x44C96F8169D94D31ULL, 0x2AF6254D75A27C4BULL, 0x8029154BDF9E790BULL, 0x8101C99528C11259ULL, 
            0xCCBF57D94BF5A409ULL, 0x0EB9E0CC99993563ULL, 0xAB0B9B82AFE2BBAFULL, 0x7D7F59DDBABBB6E7ULL, 
            0xC5DE1918371D63F6ULL, 0xA62D6F2E54D88914ULL, 0x251AF273013C0D2EULL, 0x6ED325F5DFD0E82AULL
        },
        {
            0xEF7A1BD55DDC8F58ULL, 0x2C6D36F7CC078D25ULL, 0x4D080D9B42897E3EULL, 0x57A8E9095CFA60EFULL, 
            0x69FD3E3E22A5BA06ULL, 0xD5A58B6B3A399139ULL, 0x162F616BAD3FBE52ULL, 0xF97CC5FFE74FC7D6ULL, 
            0xFC2CF83A98A870A2ULL, 0xA41DCBEA00A0CC19ULL, 0x0951C2782438932AULL, 0x4B48A72121135D19ULL, 
            0x89E24EEB9598DA65ULL, 0x4595E71586FCC9D0ULL, 0x7149BC991121CC49ULL, 0xA4C332802163CEECULL, 
            0x66F9E55C29D0FA45ULL, 0xFCE29F05F194F90BULL, 0x0AC81D2CD5E6065CULL, 0xB4A844FF66E6D6EAULL, 
            0x2D217F3A9BAB1BB5ULL, 0xC3CC107288588BCBULL, 0x515619782352AFA2ULL, 0xE906136C4F249055ULL, 
            0x7197BB6C3B951F7CULL, 0xD44AF4A271507A6AULL, 0x0B10821F6B191DF0ULL, 0x130E86279645D6A1ULL, 
            0x2F007C6D79319EB2ULL, 0xA4778A0F93E30856ULL, 0x59CD3D34E91709F5ULL, 0x490D44CE5ABD8A73ULL
        }
    },
    {
        {
            0x8130FF996EE4CE7CULL, 0x7BAB79C455BD68F2ULL, 0xF2B991392E5FA738ULL, 0x79A96761AEE7E7D1ULL, 
            0xC3C7CA5E184D3335ULL, 0xE7D7A40DCB086A6CULL, 0x193054D88C2D0F82ULL, 0xE7667277D14CFF6EULL, 
            0x547DC7AD20FAA6FEULL, 0xC6026BD1C2697A25ULL, 0x603C77B806AEA339ULL, 0xB2BA488E19C3B23DULL, 
            0xB07D848AC33B5CF0ULL, 0xD33EB73EDCB8937FULL, 0xF7C19389C3312D0FULL, 0x42E7F017A2B14D8CULL, 
            0x9CA366FB9E882166ULL, 0xA2941CC067E5F073ULL, 0x4114750576132424ULL, 0xDAD69EC445772B2BULL, 
            0xED980E9C0500E6E4ULL, 0x223B18A15A65C4B7ULL, 0xE16A595766D8BAD8ULL, 0x535A4D941504E89BULL, 
            0x6971C69C147ECA00ULL, 0x7D0BE4BD5A2AF4E9ULL, 0x2DFEE69B920894DAULL, 0x39678A07FE321B52ULL, 
            0xE12A50840A8FF585ULL, 0xC840871AC5E27B40ULL, 0x6FB6B84878029C1DULL, 0x311F470C20BA9014ULL
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
            0x8B12F828B6080247ULL, 0xEF29A5F381A79089ULL, 0x6B90DEDC06652B85ULL, 0x43FBC16E0A13B599ULL, 
            0xF9A84B0C38662809ULL, 0x14B8D3861BBEAAFEULL, 0x689D1ADEBEDB96CAULL, 0xB2C4B5054B6BBCBDULL, 
            0x83E952F43261936CULL, 0x71CA797192AD98B9ULL, 0x3883E894F02F6843ULL, 0x8461DBC4B55FC347ULL, 
            0xFF2F0BDA60DC59ECULL, 0x5555141DC5A1F50CULL, 0x3F2AEC191B3ED640ULL, 0xEFA71832EFBE8DAAULL, 
            0x9AEDF86AA737321DULL, 0x3CD34DE85253A7FCULL, 0x07652090284AF076ULL, 0x479CB34D77810C67ULL, 
            0xF7651AC61615D5B1ULL, 0xEC93AAEBD8D3D9D2ULL, 0xCBD0B953525F7BF3ULL, 0x5D3FF70B911CC29FULL, 
            0xF82C342697C8360DULL, 0xF726594D043B9825ULL, 0xB02830106F1D0252ULL, 0x76A0DF4A129AEB1FULL, 
            0x9CFC48CD9F316D8DULL, 0x3EC4EC5D68BEB3A4ULL, 0x611881011195CC53ULL, 0x00FB67103FF57829ULL
        },
        {
            0x115358D932BFB5B4ULL, 0xF1A6E2AB1D36D44CULL, 0xE791716BA2EACC43ULL, 0x48D7C6CE77914D0DULL, 
            0xEF3189D135457BB3ULL, 0x670CF7AFD4AE8C81ULL, 0x0CC7AD9ABE3DD6C1ULL, 0xFDC2C678D07FAE7EULL, 
            0x471883DD1B23CAC3ULL, 0x27294BE2E658BE5DULL, 0x1B7855E8725EB241ULL, 0x702026655B641CF2ULL, 
            0x3B45CF4515C38447ULL, 0xB416FC7A0321F3E3ULL, 0xD3FA97AE07092C5AULL, 0x15BE16F281B48D6CULL, 
            0xAB47DFB7FBA005CFULL, 0x1DCCF5EC99E79BD6ULL, 0xBCC60A6356213F29ULL, 0xD40DB38A07BE4622ULL, 
            0x46859CD43ABDA60DULL, 0x4F4D76118008C996ULL, 0x24A1F43CA57D8189ULL, 0x21B64E4EB9D5AB34ULL, 
            0xEDC6CDADD6C0D7E5ULL, 0x5BC9D844F6F50653ULL, 0x2000E2B75FB309BDULL, 0x3DA5F75ED7842E6CULL, 
            0xE183D6A2AF08671FULL, 0xD1F66E655E6CB07DULL, 0x235834E804DEC9C9ULL, 0xE9EAF1644C659A05ULL
        },
        {
            0x957E9FE7925932D4ULL, 0x9CF10C50598F7BC0ULL, 0xC67A416F2739A440ULL, 0xB2CC60CE6523B40DULL, 
            0xA8844298D6D096CDULL, 0x7AECC5516237447CULL, 0xC03A01E771D582AFULL, 0xF0BECCF5B3125391ULL, 
            0x3508F18B2877A147ULL, 0x7EA4DA28536A6A56ULL, 0x0527119334AAC504ULL, 0x3711B7A1DFF46FDEULL, 
            0x1EF49D621696D78DULL, 0xA8D8374E525CBFD8ULL, 0xBB12AC5917CC5B9BULL, 0xBF42A9B80F3B4F44ULL, 
            0x4F2F76E62F0530DDULL, 0xC98601B11D8B1B61ULL, 0x85DF9B11C18FF5E9ULL, 0x8664B682E52C16FBULL, 
            0xB8261B5A1C9631E6ULL, 0xD80401A674A431A4ULL, 0xCDE11926B75A6CACULL, 0x3852E7829D1567DCULL, 
            0xFF3FF1941890F5DDULL, 0xE09E3B1F41B217E1ULL, 0x8ABD0A79E6C936CDULL, 0x0BE1E2B1AA40F569ULL, 
            0xB950E15BEB7D180EULL, 0xD0371456D3B40BADULL, 0x6873BC74B37195DAULL, 0x30F692122A12E54FULL
        },
        {
            0x115232F73B314E79ULL, 0x45DC62B8D88D0F27ULL, 0x1C3F97024B9F61A1ULL, 0x03BABD4DA9EDBFEAULL, 
            0x1AA129A95D203F12ULL, 0x79857DD626A02B82ULL, 0x5CBF2247373638B1ULL, 0xE62C3C7E75E4736BULL, 
            0x6E2AA9C09E317B41ULL, 0xAAB69272705B6C10ULL, 0xE71B3E12941C4D02ULL, 0x5392B2DF059EC75AULL, 
            0x35418A18417A6105ULL, 0x71609908AA8DCFC0ULL, 0xED99591DA3D5DC02ULL, 0x75923FB4462E3466ULL, 
            0xC8327AA641E118B1ULL, 0x52DA61101C022EB3ULL, 0x725C64132D828E43ULL, 0xD961082E1FA6EE4FULL, 
            0x8B1DD850118CC81CULL, 0x0117CAB0086BDBD1ULL, 0xC8672ACDB7198274ULL, 0xAED9BE2F442B91A5ULL, 
            0x1827111256121A66ULL, 0xF188379A46FF6C0FULL, 0xF9F631B1EEE9BBA3ULL, 0x3F04EA665929D3E3ULL, 
            0x29A916FA136855F7ULL, 0x700CB3F0588DDBF8ULL, 0xE3275D8D7502EDF3ULL, 0x1081B361DCE7D831ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseFConstants = {
    0x400DDC6A6AE98C5AULL,
    0x3CFF957C19E59780ULL,
    0xBD3F91D505FAC177ULL,
    0x400DDC6A6AE98C5AULL,
    0x3CFF957C19E59780ULL,
    0xBD3F91D505FAC177ULL,
    0x006E52C3A2EF0A9BULL,
    0xD76658FE0D633F5BULL,
    0xAD,
    0x2C,
    0xD9,
    0x87,
    0x82,
    0xEA,
    0xFC,
    0x34
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseGSalts = {
    {
        {
            0xEF3D3A28A15BCEC1ULL, 0x4A8F38F3EA2311FAULL, 0xBDA4144FCA8DF55BULL, 0xE8DC17417ADF4580ULL, 
            0x449DCB9527115AB8ULL, 0x2C94CB498D648E50ULL, 0x80E4A157B63A43C9ULL, 0x9CF9F483FA4A38ADULL, 
            0xC6EA8FB890ADF6D3ULL, 0x48DA85325A11CFCBULL, 0xC4CAA16E22E4967BULL, 0x0607387D763A6794ULL, 
            0xA35BD40BC6D4C165ULL, 0xE9AF29323BBA39A3ULL, 0x34798E81F9D1707AULL, 0xE96A6F42D35B029EULL, 
            0xBF4A4F8D151464E1ULL, 0x5E8ADF48B32BF629ULL, 0xC4E1139C9E379199ULL, 0x060F7DBC7DCA44A5ULL, 
            0x9AABD168E4002B52ULL, 0xB1A8D6782DB578ADULL, 0xA848D1842A87EEDEULL, 0xFD8532CB15101341ULL, 
            0x55F15A6A046FC5C7ULL, 0xD0180F236CBDD6B4ULL, 0x7ED9DCC4AD4B550CULL, 0x2B7F82E664235BD8ULL, 
            0x586B1786565174C1ULL, 0xA9892E417DCAC5AAULL, 0xE68EEAE7FBDA0391ULL, 0xD525FB69023AFDA9ULL
        },
        {
            0xA7ED8DFFFEB3D5E1ULL, 0xD11E271F709A8221ULL, 0xE43F8B554EB62F40ULL, 0x2A0D247E72BDA29DULL, 
            0x32FE01CBF21EBC37ULL, 0x7BE197D62576E3AEULL, 0x647B7B32CC959852ULL, 0x1828113C9CD3C4DFULL, 
            0x5EC2D94F2C0AAD98ULL, 0xFCDF97B8BE2793ADULL, 0x22F66D03C355BD83ULL, 0x5E48AF5B8B9866CAULL, 
            0xDA82F4D2F8788048ULL, 0x72643DAF398CDDD0ULL, 0x40E0AF0F1112585CULL, 0x1017DC183EEEE5C1ULL, 
            0xD3725A6CBAB6652AULL, 0x2C88B3D52A823EFFULL, 0x5AD795DB6019AAD9ULL, 0x94604BBD0E09FD80ULL, 
            0x3A6110379C93C694ULL, 0x4D05106B7A406174ULL, 0xA92357784753730EULL, 0x7F5CD13F0C38FADEULL, 
            0xE49D8C092C4959E0ULL, 0xD45BBAFA823F0FE1ULL, 0xD1D550F86339B02CULL, 0x6EFB352B0C948707ULL, 
            0x58C029827851F70CULL, 0x57DB4942F64E2B57ULL, 0x5102D0635B9DFF0BULL, 0xEDB26A0174C2EC8FULL
        },
        {
            0x5D8D03A11ADFAB79ULL, 0xDD09641E0C6B04BBULL, 0x104B155F5AEE3463ULL, 0xEC37C8CF4F8E765BULL, 
            0x60FF5F340F5CD63BULL, 0xEF423626B4661D9EULL, 0xADAC1AD36A919037ULL, 0xA3A4D2561E2ECAC1ULL, 
            0x800B7F8DF2E579B1ULL, 0x9111D97B77238C41ULL, 0xBD680370DE315C9BULL, 0x46F2D1A663CCB6B4ULL, 
            0x7B985A6433B81365ULL, 0x60C232850A51C212ULL, 0xFD56CC1A5A804C8AULL, 0xB40CEFC66908F444ULL, 
            0x05940D74FE354712ULL, 0x058BE6BEE31596A5ULL, 0x9D4752E40DA10C29ULL, 0x93081708276D8136ULL, 
            0xA8E513F8E5656810ULL, 0xCBA03A1F93AFAC37ULL, 0xA4C126E37E26E706ULL, 0xFF61EA7E130DE8F7ULL, 
            0xAB45E054569FA31BULL, 0xD16F7CFDCD72BC46ULL, 0x20440110D02FF1C2ULL, 0xA9E6E9BDE4AF3DC0ULL, 
            0x61193AF21A94869BULL, 0x8FA3E8797924DD6CULL, 0xB91846309733FCF6ULL, 0x9BE73CE7AFE5FF38ULL
        },
        {
            0x1B59B8997EDC35BAULL, 0xC70F5ECAD18A19AAULL, 0x2EB004A58C5085DDULL, 0x778E4DFEE585CD82ULL, 
            0x4D2A5431D1B2DC9DULL, 0xCC45C4D9E00AF70CULL, 0xF303C201022E91D7ULL, 0xD4EF289AE1A03EBFULL, 
            0x201CCF1C00F29266ULL, 0x59600B551B14FFD4ULL, 0x26B35736869EEB70ULL, 0xC8CEC8257AE8B379ULL, 
            0xE7AC1366D3BB230EULL, 0x84B4B840C99412ABULL, 0xAAAAB16BFE845CD5ULL, 0x81ABEA84334EFEE2ULL, 
            0xE0AC47520D084C15ULL, 0xF9370EE3E0B59F73ULL, 0x5CDFDA3373B7EF16ULL, 0x134533E818A1C1B6ULL, 
            0x6605AF2EF67389E7ULL, 0xAB58A2267DAE27FDULL, 0x0E197BD89B46B02AULL, 0xEB2AEBC54948C401ULL, 
            0xD32F448888E81EB4ULL, 0x54F038FCADCEBD29ULL, 0xA28B3D6B12DB5B0FULL, 0xF2723B5E5C0DB8E1ULL, 
            0xA2CE25D6F282B660ULL, 0x87390B7C33BA7D3DULL, 0x972800FBA44B2DA0ULL, 0x27B25F33018A2DE2ULL
        },
        {
            0x21A4E52A81AC50E4ULL, 0x8649D4539139D8E4ULL, 0xB1CF8001F16A4F39ULL, 0x41DA71E7A656E69FULL, 
            0x542D3656DBE10F17ULL, 0x2A7D720A7494DB58ULL, 0x993993F74F2BE0BDULL, 0x871476971C1D8C5EULL, 
            0x9905C4B1F7BB13E0ULL, 0x7E43FBB16D35F38EULL, 0x30C78746B9B694C7ULL, 0xA39C43859C5557EEULL, 
            0x5D1EC26848F52B78ULL, 0x00A2CC6134BA5ACFULL, 0x6806685F42893B8CULL, 0xC639C8F3159A33BCULL, 
            0x9194DA50137C65CDULL, 0x2A81E8BE8E4AD8B9ULL, 0x9CC7D8D45543AF9EULL, 0x9DB6CD7501D7EF18ULL, 
            0xE04D9C250AFC84C8ULL, 0x6402046937BEF6E6ULL, 0x7D1D409C15D0C1EEULL, 0xAB92E769FA960331ULL, 
            0x739AE23407E50A0AULL, 0x79DD0AFD5210C5B6ULL, 0x1D602B243B9C10CAULL, 0x85805AB7A5DDBA4DULL, 
            0x5F5D5C7EDDC4A573ULL, 0xE333B41841F3FDDAULL, 0xDB459FA52A8016F6ULL, 0x0BD29F01E42EF42EULL
        },
        {
            0x778C9FA8A9F0999CULL, 0x27A7E2EB2599BAD2ULL, 0xB180790032555C5EULL, 0xC7E93EF47962E253ULL, 
            0x842B5D5CC32D6814ULL, 0xC00A9A70994837D6ULL, 0x400A77D44D32B332ULL, 0x4364EC69DD1232B7ULL, 
            0x1906E64A1326D23FULL, 0xA2DEC4FC10F6D3C8ULL, 0x6520C7B11B69C392ULL, 0xEB442FFE8C75BA90ULL, 
            0x1F23744E4228A6AFULL, 0x7D2CA7D77C45EFD3ULL, 0x33D89EEC3EEBDB9EULL, 0x2A08CA6E4445A66BULL, 
            0x4FCB0EB664A1ADA8ULL, 0x11712D755980C7A7ULL, 0xF643F5563A6AD02BULL, 0xB6835DEB4C84E13FULL, 
            0x39E6F31A407C8B4AULL, 0x615AE9856C4859E8ULL, 0x873BE7DCE8036BDCULL, 0x60500D3F13B352B5ULL, 
            0xFBB65B5D4F369A7DULL, 0x8F395E8E562707B0ULL, 0x75F6A109156E2D32ULL, 0xC62664044C672CCAULL, 
            0xE662102135037A66ULL, 0x442FC5616B0AB695ULL, 0xD095272F928B2770ULL, 0xCC9231B149AC0A4DULL
        }
    },
    {
        {
            0xAE6077CAE62B4FE0ULL, 0xE24A559DA899069CULL, 0x700154925EE531A4ULL, 0xBCD475A359484113ULL, 
            0x92CB2A32FA01A6ACULL, 0x49C488F888FAB2AAULL, 0x6818BBCF2BCA3DCBULL, 0xFB5C1E9E14C2D256ULL, 
            0x00A5D4614863A91EULL, 0x0B4FD72CE23C6966ULL, 0x603045394EEF56F0ULL, 0xE318FE1A3BC53CAAULL, 
            0xCEC96591EF8A2543ULL, 0x0A55814807EE5B5EULL, 0x3F4231ED64B1D605ULL, 0x8AD04EC5A2A681BCULL, 
            0x0080A9A79B3BC316ULL, 0x9C0FE1049550C2A2ULL, 0x05B74F3C70479D27ULL, 0x4C0878B96813DA1AULL, 
            0xE1336EEFCA1230E4ULL, 0xAB7F86BBBC510932ULL, 0xAA7CF56AAFFDD25CULL, 0x6665CDCA0D0B8879ULL, 
            0x2078C80212B096BCULL, 0xEDC1B000EC625C0CULL, 0x6923BE917624F0B0ULL, 0xDE42ACA46C1832B8ULL, 
            0xA2E3C092B0D82C05ULL, 0xF56BEC7B528FCA6EULL, 0x70CF067E01149925ULL, 0xB0232E8F71B77B44ULL
        },
        {
            0x78447B2270EBC583ULL, 0xD06E336F1D5C5343ULL, 0xB3E22986F96DA0F6ULL, 0xFE5C01344DEF8AE9ULL, 
            0x3271EEF1DA7533C0ULL, 0x920526F3BC7658AAULL, 0x35410B1C1E408A84ULL, 0xD189018EDBF5BA15ULL, 
            0xC6B5DA321D636718ULL, 0xA95E0FFC7E013D55ULL, 0x8AF10B891893AD10ULL, 0xF05AD84EBD36EC53ULL, 
            0xC1D38216D52DAD20ULL, 0xC3746BFD23AC7A60ULL, 0xE092C1A7C3109E99ULL, 0x867E2F2DCA2B79CEULL, 
            0xC19A9631323BA3D3ULL, 0x6FA047A71518AB3AULL, 0xB278416206FE6B8DULL, 0xAA929852684A01F0ULL, 
            0x09DB11BD5CFEBF4AULL, 0xDB4F1FC0B02E45CCULL, 0x3A4D52CD1ECA5A26ULL, 0xF9A0D8A2F8FB7B7BULL, 
            0xB66ABFE3AA5760ABULL, 0x37530B57E081A24CULL, 0x10D14F48A58CAA48ULL, 0xE0D7267C14C6F8F9ULL, 
            0xC34202ECBFFC9323ULL, 0x9543BAA9EC158862ULL, 0xA8C4A02BE33F7ADAULL, 0xD9F50B37DCDA4FBAULL
        },
        {
            0x6159AD673E7541B0ULL, 0x023722F57090D12BULL, 0xC3C37C5BA9E7C5B7ULL, 0x04DC64B4D713B558ULL, 
            0xBC21FAA987796634ULL, 0x2A3E641F734C2318ULL, 0x73A531611188F0DEULL, 0x3E9A0D0CB11C5950ULL, 
            0xDD36CF536A67ACA0ULL, 0x4047DF52E8E255C8ULL, 0xAE8BE12CD17C2F34ULL, 0xCB1B999FC4D5C759ULL, 
            0xD4ED7369C10C45F7ULL, 0x701278B54F19B086ULL, 0xF6D66B3E13CD4D2EULL, 0x7446211660479740ULL, 
            0x9D347DECBC736896ULL, 0xEC397F7824667F3BULL, 0xEA854CD86E24D27AULL, 0x10EFFCCFF53619F0ULL, 
            0xD995BB0280905CB8ULL, 0xB9EE5FECAE8D6016ULL, 0xBC52B577D9E61F33ULL, 0xD93217BBFA9BE996ULL, 
            0xAA8E1EC0C4E6746AULL, 0x5EA8190B25EAAD96ULL, 0xF87FEC30BB0FF7D2ULL, 0x34C809743440966FULL, 
            0xCBB0D091B7BC7926ULL, 0xE126FBA095BE71D4ULL, 0xC31AEAA2775510AAULL, 0xA6B4AFF08D74084EULL
        },
        {
            0x1841F28F06AE3D3BULL, 0x94644A83580D6478ULL, 0x00346E9F5F92CE53ULL, 0x9213444DB8604D1BULL, 
            0x2EED38F6BE11A89EULL, 0x14ECAD07968F01A4ULL, 0x1D38A7FAF5A1C05CULL, 0xC5F6A8F106159FA0ULL, 
            0xA4A6A39266458202ULL, 0x4A2D5552C0ABC8C7ULL, 0x66EE3338DA956D82ULL, 0x29B5F7106E7F6FEAULL, 
            0x9C8443C9FBA5ACBBULL, 0xBE2FA2AE4DDBF7D0ULL, 0x78368CBF5BE9937EULL, 0xC53F3235209992A8ULL, 
            0x5DBA7F4449E35A49ULL, 0x974FADCE61E01F79ULL, 0x1268421BFBBC5B97ULL, 0xEB8F9DF08FEF9C16ULL, 
            0x8E9D0EF62C98F7A2ULL, 0xF1C9F37FE18E6115ULL, 0xD1622D81D7060195ULL, 0xF1D3BA5F5A2ABAD8ULL, 
            0xA43F486293A78804ULL, 0xEF52122122D92A3EULL, 0x6B047E8AAD236DEDULL, 0x5CDC262816B82D51ULL, 
            0xB60667A569C497ECULL, 0xF6630AB745AE474DULL, 0xB0D50025BA5D8798ULL, 0xE77BE33EA337B354ULL
        },
        {
            0x87FE56D1F7B3547BULL, 0xA98FD5841177521AULL, 0xBBA408663762469BULL, 0xE33AB453DDCA2DF5ULL, 
            0x284AE4A52B3148F4ULL, 0xCC3A99F7F4B5427CULL, 0xC7C9171D59589900ULL, 0x1569FA7F57F808BDULL, 
            0xB5D0A50AA0ED7728ULL, 0xF157E011ADC98400ULL, 0xA233CF2D2C17139DULL, 0xB5615C1DBF8C7ED6ULL, 
            0x455E5C59EFB07974ULL, 0xD41C1A69FD48C14FULL, 0x2E8EC05C360E5592ULL, 0x3917A224E6C79CB3ULL, 
            0x8FB5CC46DD2B194DULL, 0x518250CF89D15374ULL, 0xFE30C24F2B89FAA5ULL, 0xBAD25B13D937A8CEULL, 
            0x396C9D43BB00B8F3ULL, 0x3AEA84254EBC1726ULL, 0x44C196B1535D21E4ULL, 0x32F124AACCE37DB4ULL, 
            0x0FCF41D5EDDCD947ULL, 0x7C2BBE9061894A44ULL, 0xFE3FE4B1D4ADE3EEULL, 0xF2076430483E6827ULL, 
            0x5EF4ED34BEFE4674ULL, 0x2F94C5B8ACD5FD0AULL, 0xD650DF27911CD46BULL, 0xA492F2763AC01450ULL
        },
        {
            0x39D253C231B77DEAULL, 0x660B24C8C8B9BCB4ULL, 0x4A2BBEE0996575E2ULL, 0x9D92770C8BDFC45AULL, 
            0xDDFB4C246E1E12EEULL, 0x7F2FA2250CC785A3ULL, 0xB0A9B7F57D8D58BCULL, 0x2A258E98A35895DFULL, 
            0x89D5FB16B052DEC1ULL, 0x5487F5A0EBDBABDFULL, 0xC5F0D1CC99DE36D6ULL, 0x1A839B9D23FCE54FULL, 
            0x807E4F4DE015536EULL, 0xC6298F4485785038ULL, 0x49D76F0D453F365CULL, 0x49654659A1B39DEFULL, 
            0x2CF76FF405A83235ULL, 0xAB16FF776A68D1F4ULL, 0x67FE6428A1509253ULL, 0x8F3D7DB45B9D27E7ULL, 
            0x2BD6D57254A993C5ULL, 0x6CE961EBDF77058AULL, 0x6B21FDC3BF9A77BAULL, 0x6F33952C433A32D9ULL, 
            0xD636653079989701ULL, 0x41C2F15F38FC11FBULL, 0xD91412DA88A95620ULL, 0x8B7178E61912714FULL, 
            0xE85660AA9176A365ULL, 0xF114B36AD4AEF97EULL, 0x0428FB6774077088ULL, 0x241AC953D6AB7629ULL
        }
    },
    {
        {
            0x7A7CC5B75698FAA7ULL, 0xF8F71797A66C69DBULL, 0x59372E6D5D35E9FEULL, 0xA3EFA1378AAA666EULL, 
            0x13D508B35547E268ULL, 0xEF635863AC005007ULL, 0x003DC21F8B7AC16AULL, 0x6A8B664C83F85335ULL, 
            0xA54FD96D62D52939ULL, 0x6CCA964ACAD3B0E4ULL, 0xC30D31B1B98960F7ULL, 0x00052D3183A18AC3ULL, 
            0xFBB2747F8B0C3A92ULL, 0xF42BC64FD597F2E9ULL, 0xECA9786A52EE006FULL, 0xDBB19D1E051F4BB9ULL, 
            0xB8D69AE4D20D2A80ULL, 0xA84D2EE7DDF776A8ULL, 0x03C73E0CB64555BFULL, 0x3651AB64E38A3A4DULL, 
            0x87B03A658BA27520ULL, 0x9E8D4A560437F040ULL, 0x750EADA7EA6F4335ULL, 0x492EBD0040189D15ULL, 
            0xBB444C91A1D8D975ULL, 0x9A5B18665E1BED6FULL, 0x0E43D0E6E9598270ULL, 0x7A5560EB1940C669ULL, 
            0x09F8FF88699FE801ULL, 0x7EF0FB7CA4918CADULL, 0x733A1B1DE373DE15ULL, 0xF1AE46CBBE33B41CULL
        },
        {
            0x341C03B9D5049504ULL, 0x0B9C446BF4BC8927ULL, 0xAD23D9027F2CD56EULL, 0xC6D1587672943841ULL, 
            0xF6DF126E17643CC9ULL, 0x4AE889DE890CFF3DULL, 0x79DEA0DCAA149D4DULL, 0xDC66378FB876C52FULL, 
            0x619499109B36ED0AULL, 0x0F4D9611C55AD7A5ULL, 0x43DB7AB2273B010AULL, 0x42E039153A03E1F2ULL, 
            0xC4B3493971FFBA81ULL, 0x6E57247EEB5CA0EDULL, 0xDC5A1439C32F54CFULL, 0xDBF9BD26A36BAD57ULL, 
            0x99BE91662D651716ULL, 0x4E681CA881332BAEULL, 0x7EFD74502B9D7F72ULL, 0x6EAEFB57C2C4B105ULL, 
            0x169EA9B9B67E631FULL, 0xD752CD19B2E83F30ULL, 0x48FA746B232D47FCULL, 0xA8602A09199408D5ULL, 
            0xC6C35B14FDF9D34CULL, 0x76232A7DAF3DE64AULL, 0x72F94F69A99068B9ULL, 0x10FDF97A816D309EULL, 
            0x09202F88491BEF04ULL, 0x57A499ADF3A587F8ULL, 0xEAEEF15884B12FADULL, 0xFF4B9F766E79DEC3ULL
        },
        {
            0xDA2FE3487486156BULL, 0x8E714B9192D509CFULL, 0x34C00693F10D1E75ULL, 0x21F5DD02FC59B9DEULL, 
            0x2836CC7BAA01389EULL, 0xA038D7A6A13EAB67ULL, 0x333619A1D0AC91D7ULL, 0xC34DC6B52AF09B33ULL, 
            0x629EEC4CAA52668FULL, 0x51296622D5C888F3ULL, 0x64B9B2A45BC41C9FULL, 0x39D49F892143CEBCULL, 
            0xE65A5E4E000B8E64ULL, 0x9E547708E1DF02F1ULL, 0xCF108C7F5C1B8111ULL, 0xB78939D35B534AD1ULL, 
            0x28409274CAA8DEA1ULL, 0x02F730565DFA7437ULL, 0x8E398B80BE1CA718ULL, 0xBB7CB0A287A0A047ULL, 
            0x5D2B457CC255913BULL, 0x7F2F2DFCA500AC1AULL, 0x559A0473C6CF6C09ULL, 0x957FD7F24DEA18D6ULL, 
            0x2E13EE830AD54622ULL, 0xF71D892415904CB6ULL, 0xEACEB902EBEEA9DEULL, 0x520EC7207E1EE540ULL, 
            0xB1F80005935C0951ULL, 0x5AFEC04E6D193CEBULL, 0x26AADEFCB95CCD0DULL, 0x52906F1BA2159E4CULL
        },
        {
            0xABD1865F7538A6D4ULL, 0x2C4CA3B0A9047268ULL, 0xE5FC38893A94C826ULL, 0x66EA8FD343734C29ULL, 
            0x0190A6885411FAAAULL, 0x6EEB09E8CE637047ULL, 0x1463F80FDF5EC7B4ULL, 0xCC8ECE5AC0373CC1ULL, 
            0xC757ED87E6B12ADBULL, 0x11C2DBA4A7E55A37ULL, 0x306DFDE4234948DDULL, 0x377937F343083920ULL, 
            0xF0D201512E4F556FULL, 0x94EB12FBD983B657ULL, 0x491DB2FAFEC25A00ULL, 0xCC617A9790127E85ULL, 
            0xF21347D7B9A86461ULL, 0xA655B0771AC0CBFCULL, 0x45D1746AFA6C41D3ULL, 0x2862D7D2BBB12D94ULL, 
            0xA10BBAFCCB956AE0ULL, 0x1EB3D9E2511DD9A7ULL, 0x562DE1E18F7D8FF0ULL, 0xA01C1F7B4A5B4518ULL, 
            0xB37DFB4D23FC7E92ULL, 0x33FF6C170504FFC7ULL, 0x221269436AC84334ULL, 0x700C7B6F1A441251ULL, 
            0x9A6AA1E2E84BE4BBULL, 0x76A17D8DB060909DULL, 0x5F393A9B2BC1372FULL, 0xC71373655E88C99BULL
        },
        {
            0x9EDA7D9BE987821BULL, 0xD10ACFAB6F002BCAULL, 0x98AD400BF705C030ULL, 0xB242D7AB360D0591ULL, 
            0x02A749E479632C1EULL, 0xAAF3D1659719372BULL, 0x7164D38504003F13ULL, 0x368F999EE4AE084EULL, 
            0xBB18325DE41054EFULL, 0xAAE0647563EA2CDBULL, 0x38F8EFFAB507C180ULL, 0x5D6209494478B189ULL, 
            0xBCC189DAA1D2BB28ULL, 0x815C4B061604EBDEULL, 0x4A5E87FEF39CF5EEULL, 0xD649CC83408ED1B6ULL, 
            0xE7FCE0A3163F01E9ULL, 0x2174D2898F50FBDEULL, 0x033CD953BB6A8594ULL, 0x7D197C9D59E1293DULL, 
            0xE8F9D0605E6566AEULL, 0xC240E22D4C715ADCULL, 0x068BBC5D0EC665A6ULL, 0x720D46348C434937ULL, 
            0x27B1CC3BC5C8FCCCULL, 0x682DCC94BBC2B988ULL, 0x786B744E43AA3B6AULL, 0xC4F93DDE69AE2B12ULL, 
            0x253FAC90EAE73AE5ULL, 0xEB05DCC64FE22BD7ULL, 0xB4C81BFE2CB859F2ULL, 0x1FAD3EC36BF36574ULL
        },
        {
            0xCFE326DC489FDAA8ULL, 0xDD5401C2E868243FULL, 0x13BCC03F3CA6259CULL, 0xB5B6B330458834CFULL, 
            0xB5219EF95F18C446ULL, 0x071658240B23363EULL, 0xBD35BF140AD8885AULL, 0xEE8037563F64EB48ULL, 
            0x075516C3C9F5776BULL, 0x265D9C76AEDE3A00ULL, 0x88EDC2EC9BF25094ULL, 0xE959CB6D4145876EULL, 
            0xD51FA2C5C5506D2CULL, 0x26466481F3125480ULL, 0x817C43E1E02F5580ULL, 0x834903E4CCF1E531ULL, 
            0x8D630BC86BB88E01ULL, 0x0576CAFB6CC1E3D0ULL, 0x2E55E1F6711D3BDFULL, 0xDE58B21B617B0D66ULL, 
            0xB9B3D57C03A168B2ULL, 0xD2889C47B5783555ULL, 0x51D93F041D0DEAAFULL, 0x01DC2B354B71E2CCULL, 
            0xA2C59FE8C9C02BC0ULL, 0x46828BC58ADD2EC4ULL, 0x8A69CFCEC6556ECFULL, 0x5D430DDCAA3D7656ULL, 
            0x2D01EC2D50284F48ULL, 0x2CA5D5953F84F265ULL, 0xD739036BAFE727D7ULL, 0x4C43C7144E704862ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseGConstants = {
    0x07F489B4EFE1BBE4ULL,
    0xE2DCD847E6EA5DFDULL,
    0xA4BC1C786285F484ULL,
    0x07F489B4EFE1BBE4ULL,
    0xE2DCD847E6EA5DFDULL,
    0xA4BC1C786285F484ULL,
    0x5C80C3F1ED6C6DF1ULL,
    0x66251E37D326B587ULL,
    0xA9,
    0xDA,
    0xCC,
    0xEE,
    0x4E,
    0x60,
    0xE7,
    0xAB
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseHSalts = {
    {
        {
            0x80BAEC1A1B4BDCDFULL, 0x9237A13543C7712AULL, 0x50A665B0E4E77725ULL, 0x7488BBF2D6B60D45ULL, 
            0x6AC1507419AD8DBFULL, 0xDD4A8F68BBF7650DULL, 0xADB5A9811C450430ULL, 0xC5463052506AF242ULL, 
            0xA59C08388FE922BAULL, 0x40CCA1FAADDB85D7ULL, 0x10569B8AA074BFF7ULL, 0x7F134C845EE1E2F8ULL, 
            0x5B83835BCB4F0901ULL, 0xFABCE35ADBF7A815ULL, 0xD8D973013B9316E7ULL, 0x11152998A53B963BULL, 
            0x4D3D929840554130ULL, 0xA0E70FB8D8BEE659ULL, 0x20410C1D682BADC7ULL, 0xD4D461038E951B07ULL, 
            0x194F16F566486287ULL, 0xD71F865F857F5297ULL, 0x9269F69019610B02ULL, 0x89A6B8F31F0ED02CULL, 
            0xDEBEE9386D6391C9ULL, 0xFEAC88D1D73C3F21ULL, 0x494FD170274D55B6ULL, 0xE44E8BDFF1355B65ULL, 
            0xCE86779E7FEFF308ULL, 0xAE77EDEC95FFF12DULL, 0x7168145EBD5256E7ULL, 0x40E2548B5A6F4AB6ULL
        },
        {
            0x8B9A7CA4E26A875AULL, 0x93F56AA1C9C35E11ULL, 0x25BB0F96BBC21F53ULL, 0xC6004A87BF7251EFULL, 
            0x7582FBD91E71CF4DULL, 0x7DC600640227451EULL, 0x62778BC984E4E145ULL, 0x008E661ACA6C2F9BULL, 
            0xD66870306A8D049EULL, 0x198F5E1774FFA9A3ULL, 0xDEAA6FAD29E0CFD4ULL, 0xD4808CE3C4491B57ULL, 
            0x885B62C537712E6AULL, 0xECFAEC54FD1E4110ULL, 0xDF1DA42C5A30E0FDULL, 0x159E0F9597697747ULL, 
            0x182E9EAE875F96F5ULL, 0x8EA55DC7938064B3ULL, 0x81E1D5F894117B48ULL, 0x8D72C0E5DCC95FDAULL, 
            0xBA09AF8E51B83340ULL, 0x2C66C6DEB8078580ULL, 0x92933FD7A0FA48DDULL, 0xFBDCCB413D84A0D8ULL, 
            0x88C68BFAC6F99FB1ULL, 0xB93DA607B33AF60BULL, 0xBAD753C912D57FECULL, 0xB38C96588A1D1186ULL, 
            0xBEDC6DA45C6554FAULL, 0xE7BA922DD92BA33DULL, 0xA5C47230AD50AD1FULL, 0xC45153EFE9AFCA76ULL
        },
        {
            0xB4CFB7D4B985E676ULL, 0x0D28B5846D3F8D6FULL, 0xB9958DFF5BD137AEULL, 0xBBCB48D06A647951ULL, 
            0xB9B4B8A71914A019ULL, 0x65F32471732C4411ULL, 0x385B7DA5837D4E69ULL, 0x1202EDEB4D4B27DAULL, 
            0x39D0D4732FF81390ULL, 0xB102E62C5FCB059EULL, 0x3FED2BA3DC98B45AULL, 0x02082056BB5C2587ULL, 
            0x86C1DB9B6C67E0C7ULL, 0xB8FE7FE9F6113851ULL, 0x5D7E01E9A076A5ACULL, 0xA799807280635B65ULL, 
            0xFFCE0174070CD569ULL, 0xEBF76ADE09F74247ULL, 0xAACBC151773539A7ULL, 0x6CE32968F7EFA66EULL, 
            0xDCC528E0D9F1A7F9ULL, 0xA861336FDDC716DEULL, 0xEE4E8645576CE6F6ULL, 0xE24BF934F884BDB1ULL, 
            0x954BC07D2E0F0C26ULL, 0x4543D85A809101C7ULL, 0x5D0B7EB411C36976ULL, 0xA89689F08BE1564EULL, 
            0xF114E4DB1DFBFFABULL, 0x9A41518E1BB4A006ULL, 0x3522CCB3102E7C17ULL, 0x7E28E130F88B01C1ULL
        },
        {
            0xF4797D59AF726A75ULL, 0xD38854188483F5DDULL, 0x97037D70DF5F948EULL, 0x72B06382EE4E4748ULL, 
            0xF781CBB52AA0FFD4ULL, 0x11747A807FD41ADEULL, 0x8DE3367630B15478ULL, 0xCF5F71CCF8977EE8ULL, 
            0x6EC29D11668F6A20ULL, 0x7F70992F75541F54ULL, 0x0EDE7F6A32509F64ULL, 0xCE229ECCB9C806E1ULL, 
            0x85C721C44B619702ULL, 0x9B9659F45C05293CULL, 0xEB9FA94D1B713BC6ULL, 0x652219DE9CDA8A08ULL, 
            0xACC8D5EE99898B05ULL, 0xE2BF61E16833F1EDULL, 0xD051E3E7120546B2ULL, 0xD8A7499183A186E7ULL, 
            0x6D84526889E811BDULL, 0x7903388056F87639ULL, 0x75BE21D6E2FFAED0ULL, 0x414B624C5BD9B8B1ULL, 
            0x16538A2F7F60CAF7ULL, 0x18FF41A946B515DBULL, 0x5E60BE542B94D0C8ULL, 0x65557ADFE3058AF6ULL, 
            0x467B7009D448C4E2ULL, 0x848D498141081938ULL, 0x86C4E0AC1E29B9ADULL, 0x048B4872FE3CBE7CULL
        },
        {
            0xA89A00460CD0A0A6ULL, 0xDB294C90C7251A19ULL, 0x3EDA4588CFC05E40ULL, 0x97677A131171E46EULL, 
            0x4A346D35C1821D80ULL, 0x713B73FFF562982BULL, 0x8EE5B5E699A69C8AULL, 0x9CA914E080B48B67ULL, 
            0xC182B0D1A608A984ULL, 0x8028116EB5EB93C5ULL, 0x26A5EEED9DD540C9ULL, 0xEFD822DD50D2F4CBULL, 
            0x19863E97594BC39DULL, 0x989C07153EF249E2ULL, 0x39D076385A5402BFULL, 0x83B0C9D6D77EE6BEULL, 
            0x9AD2148FE0E7EF25ULL, 0xE7FF0CCE77D7BB56ULL, 0x26D38C6C9999915CULL, 0x9E2A315CA925AADBULL, 
            0x9AE2C4A6BC58440CULL, 0x5364B965B57AD49CULL, 0x06C83DDFBA0D7727ULL, 0x5F9A63CDC38325F8ULL, 
            0xA25EED78403506A9ULL, 0xF27AE8EC1C7FBEAEULL, 0x428528AA6BDDA835ULL, 0xAA667B7800C21FE8ULL, 
            0xD29046BEFBA8F3DDULL, 0xBE7407C812E5AA11ULL, 0x2C6E28B4A2427130ULL, 0x6165BBB70045C168ULL
        },
        {
            0x318431546DCB03DBULL, 0x9510D1BAC3C67EA0ULL, 0x000565873B9BC9CFULL, 0x8C529145092FCF80ULL, 
            0x6C786C938FC9B8B3ULL, 0x32D01A01961A5894ULL, 0xB99D1BFDB6227DE5ULL, 0x09CECBFE4CEB0655ULL, 
            0xEBDF66AFF971B112ULL, 0x81EF5E6DDDC1DE51ULL, 0x83F9699345411210ULL, 0xAD77BD08975CA081ULL, 
            0xCD19990EDA81A5EAULL, 0x06D6D30AE10ACB3BULL, 0xB2956EA840EF2280ULL, 0xFE829BE3EC75D259ULL, 
            0xE2CBEEE21B90C883ULL, 0x1470914AEB441818ULL, 0x1803FF5E4BF14949ULL, 0x1AF498DA0E4C6613ULL, 
            0x5C2255B8C0CA171CULL, 0x7966A63928DA2076ULL, 0x837633A57F9C2210ULL, 0x44F3723E680B99F3ULL, 
            0xB958C9FFB041780DULL, 0xCA3C552C319ED38AULL, 0x770BF1935C421600ULL, 0xB03295970919BB45ULL, 
            0x2910CB67050F743AULL, 0x92F88E43ADFD597CULL, 0x73F67D1CB1561D79ULL, 0xA24DE54DDDDF01CBULL
        }
    },
    {
        {
            0x4ECC0CDBFEAD4D00ULL, 0xB6F9E8E93DA36605ULL, 0x4E22026848D5E2CDULL, 0x67F40B22DE84DB47ULL, 
            0x605A7AD63F923AAAULL, 0x8B87B702E6693E28ULL, 0x3FD6F49D16F9810EULL, 0x58D47C2DF4A82FFDULL, 
            0x14A7002351AC7243ULL, 0x04180085B9926D89ULL, 0x09619C9DE68293B0ULL, 0x4F37599F30B75777ULL, 
            0xAD290EEBC87E2864ULL, 0x52FEF0F226C3C3D8ULL, 0x2DC091FF165A0B8AULL, 0x45DDD18F9E7BE030ULL, 
            0x79362D15970728CBULL, 0x7DAD262516A6B392ULL, 0xEACC94172FE6EA15ULL, 0x7C3926ADC0907C85ULL, 
            0x8B3D33473288D8B2ULL, 0x269F8841BAFB78BCULL, 0x507728B29CA73FF5ULL, 0x8443140156F681E1ULL, 
            0xC4C51E703FC94F79ULL, 0x469BE740EF771457ULL, 0xB7B017461052D41FULL, 0xFACFEAD8182DFF69ULL, 
            0xAA4079DF536E6223ULL, 0x4E6034DA82D256C1ULL, 0x5B40F79316A7F5F8ULL, 0xD5B0BB2A3F68C74FULL
        },
        {
            0x094B4F52FB00014AULL, 0x20650A00EB8EF073ULL, 0xD0C1484A28ECC5E5ULL, 0xBB1E59E921BA9E8EULL, 
            0x4B2C0ABDCBCEFDEAULL, 0x5540650837581A4DULL, 0x1C3E9BC60BB12477ULL, 0x8E12EFD596270508ULL, 
            0x015FAB7250A7C111ULL, 0x568BDDE7CE555C7CULL, 0x8ACB8FD184142111ULL, 0x0CCC4B75470A9167ULL, 
            0x98C2FC7F87C8D7A9ULL, 0xB9D4C1025AB30B11ULL, 0x076132403FB05830ULL, 0x18A0379DED96337AULL, 
            0xEB418BB5FF50A2EBULL, 0xA36302741695232CULL, 0x67ACA27BF813ABD2ULL, 0xCF3AD59A6B9B84BEULL, 
            0x3564F0F3450AD7A3ULL, 0x6FA135864613DADDULL, 0x5FC769F64E01C0F6ULL, 0x832368DB7DD81505ULL, 
            0xD181E152303E8043ULL, 0x7A177F20AC374ABFULL, 0x81E511CE1EFBDA1AULL, 0x5EC9E6CF76701812ULL, 
            0x9019CFD8B7B1F665ULL, 0x04F296866FE9883BULL, 0x02130B59E6621EBFULL, 0xCC11A6A941D91733ULL
        },
        {
            0x67E06093F3A118A4ULL, 0xFB3E1BEE7463E11CULL, 0x52CB8E79E063E801ULL, 0xDE654BF8E59272E5ULL, 
            0x06B675EA714E0BCDULL, 0xB873592932FBC277ULL, 0xF1A504A826631E24ULL, 0x48B689D44533F186ULL, 
            0x9ADD37A53DB0E4D5ULL, 0x3B3DFF051DD6F658ULL, 0x7F2789018D9AA2B9ULL, 0x5CFB49A4BEC2DEA9ULL, 
            0x752EFB899A878137ULL, 0x1ADAB0B94C3D468CULL, 0x2E5AA4274E5900F2ULL, 0x46852429442D80AFULL, 
            0x0F323E048E9F62CFULL, 0x7BC0201489EFE338ULL, 0x34573684763109B2ULL, 0x92307F21D9149A0DULL, 
            0xE8D78101D4557A72ULL, 0x6C4D75389E3F9DF6ULL, 0x7F70B20A3481BDC9ULL, 0x1AF0BDAA145CBE0BULL, 
            0x805C4DF492F0CE7FULL, 0x062640B87BB692C2ULL, 0x7C7BDC9158199A05ULL, 0xADACD068DD14C21FULL, 
            0x1210911258119FEEULL, 0x34EE89ED58B67B2AULL, 0x4312CAFC76213FC1ULL, 0x1D274BF7D4F678A2ULL
        },
        {
            0x6D0F512B15B3F138ULL, 0x2B89B84EF45A3012ULL, 0x16AA2AB1C1AF8159ULL, 0xF6FA94A519DF0B7BULL, 
            0x730040BCA363D3F2ULL, 0xE0E6448A274CF5A3ULL, 0x357A009A0AF04133ULL, 0xD2E7BFBADC9F943FULL, 
            0x3C056D8672313782ULL, 0xB1B7C558EEF2D439ULL, 0xDFBF8A29A2370EC4ULL, 0x9B5A1CFDD582AEC0ULL, 
            0xDAAFA5935F682B6BULL, 0x1C5024E4CF6980B5ULL, 0x5051DB2594D452C8ULL, 0xF68194656C0FFB49ULL, 
            0xF61A752A193A11E6ULL, 0x64ABA249A906E896ULL, 0x43BDDA86DF3D5A9CULL, 0xEC52439D8308F082ULL, 
            0x577E7DC1B3CAC6B8ULL, 0x47EE6D9D30749743ULL, 0x7147C25609ACB94AULL, 0x627E641CB39E8D24ULL, 
            0x00AB359E9A3AB7A4ULL, 0x74710D3FB8F76AC7ULL, 0x19030A76770FD4F3ULL, 0x930789FDE6F5D3B7ULL, 
            0xB47CB33A262E8E0AULL, 0x7D74288188E4B21DULL, 0xC07824478CF12BDAULL, 0xBB999A49092BF724ULL
        },
        {
            0xE565A4A088F4A1E5ULL, 0xAE33A8D565704139ULL, 0x355D3693B10AF1EEULL, 0xE8445CB37160E41EULL, 
            0xE0480E67F27F454CULL, 0xF4F6AD7926D5745AULL, 0x1065A053F651078AULL, 0xA593CA7D1F30200FULL, 
            0xAD8E03C1C63F7FEFULL, 0x551D352571B96F2AULL, 0xB0DE24622E60096AULL, 0x5BA75C1C8F841D87ULL, 
            0x33136A831FBD65F6ULL, 0x3A2152156E5925EFULL, 0x39B1D71623682B62ULL, 0x67E8F5F482E9B2B4ULL, 
            0x53FFF0DDEBE90863ULL, 0x4AEFB0DE4D24DE44ULL, 0x53E26A7DFAB9C188ULL, 0x476655B2D7E28DF5ULL, 
            0xE71F590C63D8C944ULL, 0x2A8A606608FCCC11ULL, 0x6E625C1EFC2E69C5ULL, 0x1DF53A49FC50F296ULL, 
            0x64E67F4F433516CFULL, 0x6FB8662C22326682ULL, 0x7E470CDDF5485DF8ULL, 0x01FCC7947030D099ULL, 
            0x9599A6E5845C859DULL, 0xBFFDDE38CEC37577ULL, 0xBB219BBBB76F3859ULL, 0x7D7DB0BF434477ABULL
        },
        {
            0x5C257889F29870FBULL, 0xFA6040152A486686ULL, 0x2A54F5BB08C79555ULL, 0xAA0B509EDFDA32A6ULL, 
            0x4368D901B78F7EBBULL, 0xB585BEA9F49A6522ULL, 0x1F0C573176338CA4ULL, 0xEBE7419749B22AB9ULL, 
            0xD15A4C3AE89E17FEULL, 0x625A8A57C02B61C5ULL, 0x0228EC2B1FAC57DBULL, 0xFBF4B643A5D204B8ULL, 
            0xEC251F29B247545EULL, 0xAD99A16688F8AFA1ULL, 0x7928F62D0955D554ULL, 0x5E000B60306A0BB9ULL, 
            0xE5C27C2EC9803249ULL, 0x6E95DC9887DDDE39ULL, 0xD31CFA8F475538FFULL, 0x281BF8D8A1191D25ULL, 
            0xA586BDC6F7D679B0ULL, 0xF935A1A43D56CD74ULL, 0xC0F80ABD9BC60C2AULL, 0xBBC1057AE6970D73ULL, 
            0x7E2466E0B4AEC582ULL, 0xD615646BEE0B23DBULL, 0xCB4FE8D0BD6948DDULL, 0xBBEE24D0E5B5A9A4ULL, 
            0x1C9D9D94C4A8C086ULL, 0x41918A47F4AC28A1ULL, 0xC077C0955C04FCC7ULL, 0xD6B4091AA8D63F6BULL
        }
    },
    {
        {
            0x0963E840A34351A0ULL, 0x84A368270FD6C5A6ULL, 0x6F38469CFCB7C4C7ULL, 0x3362F754B321017BULL, 
            0x5FF4CA127CA532B4ULL, 0x9EAED8F1C1E4A512ULL, 0x4BE5252C7EDD2FCEULL, 0x92A3FBEE570A1322ULL, 
            0x3F82192B9B7D68B6ULL, 0x0661BDD2282E5C1EULL, 0xFFCB4F573AAF4C28ULL, 0xC494D18386CC2180ULL, 
            0x324F74E2EB73894AULL, 0x9B80A110607E793EULL, 0xCE4271CF5480BF1AULL, 0x6F2F08326FAD3C27ULL, 
            0x195DC7E2ED93EA4EULL, 0xD552A9067C1C1068ULL, 0x6FC2168107B821F8ULL, 0xEB34F426FA5A80CDULL, 
            0x60D69C2CABC16650ULL, 0xC3096CA4653FDC63ULL, 0x7BDA9BDB9AF312ADULL, 0xA77053DD1C2811F7ULL, 
            0xCDFC27ACA8F6127CULL, 0xDE6093241DAED3A8ULL, 0xDF21DFAAA364A0FFULL, 0xE5F81F8688D15908ULL, 
            0x68EDFD30737F45E3ULL, 0xA1DD3521ABC1CB31ULL, 0xA0E50BA95322F0EFULL, 0x22F09247EC4E44A7ULL
        },
        {
            0x590F5DDDFCCE82ADULL, 0x88A0FCEB08E68AF2ULL, 0x54CC3A040B427DF0ULL, 0xB8AB8364A0D16B42ULL, 
            0x2E63E4BF74E17964ULL, 0xBF45F2FB7F5963EFULL, 0x3534B3C1B247CC1BULL, 0xCBD6DFB37A589A40ULL, 
            0x53890666A880BB7EULL, 0x4695C774758F5202ULL, 0x6414C662FA464085ULL, 0xCE9C23A3CD3D4029ULL, 
            0x029B26B284A7CD2EULL, 0x21D52EF4DB4A5818ULL, 0x18ED09D43690064AULL, 0x6C53CD122B650128ULL, 
            0x7A7D1A5FB58579D5ULL, 0x390986772A9F2186ULL, 0x23936B77C6BD0D4CULL, 0x82BE41814B3708F3ULL, 
            0xD4E638B2E1D9F743ULL, 0xF9A8E9B8B8C02EE0ULL, 0x7CE5F1FB8CAAC008ULL, 0xCE362887346C5E8AULL, 
            0xC132B35628E83296ULL, 0x91B187977E54E7C7ULL, 0xD2028334ED9721B2ULL, 0x9B56FE7258E9A3B1ULL, 
            0xF5675306EAAD91E5ULL, 0xC648C655D54CE6A2ULL, 0x6BAE2EB34021B4D8ULL, 0x61DD52F1A607547AULL
        },
        {
            0x406849BA4DD38A9CULL, 0xEE577C4DB3A37AEEULL, 0xC886E349ED5CA19BULL, 0x3980E3861171A855ULL, 
            0x84705A6466927CFEULL, 0xEC2F1C52F3030B5FULL, 0xC0CCCA52F0B15B2BULL, 0x3FE4EBE71CEDC6A3ULL, 
            0xDA4E8564A181D2E1ULL, 0x1AB5AF49F0FB56E6ULL, 0x1E85AF3420D1AAA2ULL, 0xDB30E8FCBE4591ABULL, 
            0xA0783095AE4E403BULL, 0x3BAF8BB8D11F1763ULL, 0x4D36F2ABD8C59E7DULL, 0x935087654EC2565BULL, 
            0xF60C5EF5CC56E65AULL, 0x2F73FAA3DC6D460CULL, 0x7819A44215F4EDD1ULL, 0x4943D50109A815D0ULL, 
            0xFDC01C8479B0D64AULL, 0x0633989B7F1471B3ULL, 0xF8B4BEE86B9C2016ULL, 0x5DCB22D067032E99ULL, 
            0xD9BE84CE37BA5889ULL, 0xC2BA600B76E9E0BAULL, 0xF0BA223EF1E7A17EULL, 0xDA0500D627003958ULL, 
            0x41748BBDDB83D30CULL, 0x52C808D5BF4E7630ULL, 0xB301796EBB549C58ULL, 0x7EC042A273D9894BULL
        },
        {
            0x838EC48337AA5703ULL, 0xFFAC556BA07D87D8ULL, 0x88DDEEC9B02991DBULL, 0x8AC0B7EFAC1B2940ULL, 
            0x0EB9832328AC4A23ULL, 0x07638B8AC98FA469ULL, 0x7EC4DA2D68F8B99FULL, 0xEBECB0ED036B3240ULL, 
            0x0CC5867E8FE35804ULL, 0xD55503CE72BCFCF0ULL, 0x8392DF2391DD3A20ULL, 0x212E278B2AA679CBULL, 
            0x3DFAB1A1A5719D63ULL, 0x278B58288BBB49C4ULL, 0x8BD0BCC756F52282ULL, 0xA21783E7474053E5ULL, 
            0xDAA1F6F9DAAB0C1EULL, 0xC6AFA0EE3503602BULL, 0xC83062C5F8450E40ULL, 0x21E8F1BEB0784A17ULL, 
            0x6F82213BC88E0010ULL, 0x433FFFFA76F53139ULL, 0xBEFCC7F159B688EDULL, 0x97A1AE65FF0FAF78ULL, 
            0xBDD00726C76009ECULL, 0x2D3ACC99AEBEA393ULL, 0xEB5BCE10B9733A9CULL, 0x8B89876D358403AAULL, 
            0xD2C44EB9D368038CULL, 0xA9A07C63E5CBBF27ULL, 0xD49263C581EC7734ULL, 0xD8D4904A7DF17FA9ULL
        },
        {
            0xD108CE09250DD8C6ULL, 0xC55CF00276438212ULL, 0xE3709FAC613D1A06ULL, 0x164B8441A90E54F1ULL, 
            0x0691DA53BEBB4F3AULL, 0x8B4A7E93FAEDFC6DULL, 0xB04B09FFA7A4B17FULL, 0xE043A6E4F45C7201ULL, 
            0x5E56BA50804DBCECULL, 0xA65377452865E59EULL, 0x6AC9B749C11BFCD1ULL, 0x9DC26E388F345CA6ULL, 
            0x188EDB374FA8F624ULL, 0xC07F322163BB2657ULL, 0x99523C8B5707A998ULL, 0xFBEA2528DA0C16FAULL, 
            0xCD51014206BAE2B8ULL, 0xD7EF9730DB57524CULL, 0x5ED5F1A667E3295AULL, 0xE07219AD06F2B55DULL, 
            0xF5FC86DFB7BE7A10ULL, 0x35F87407CEC430FFULL, 0xE00A956A8EA1916DULL, 0xB2DBA0FC9395DFEBULL, 
            0xE0E2F505CC71687AULL, 0x13300BD63A26D6B1ULL, 0xFDAE8D31CCB10509ULL, 0x8A1D86359805E2E3ULL, 
            0xA1F601997A2678A2ULL, 0x22536B5A070CAF2AULL, 0x96D395AD5C7C4512ULL, 0x31C755E00C37EF27ULL
        },
        {
            0x86D986EB2558E1A1ULL, 0xBA258DAC09DF6F7FULL, 0xB295105B2209AEF1ULL, 0x30FC38174DE23714ULL, 
            0x12DC34FF94F64AFFULL, 0xD70F112BF06CA4C7ULL, 0x373203BD7A1D5D1FULL, 0xE1869CD2060779E1ULL, 
            0x91866335FA65DC22ULL, 0x871DC4605FA12EF5ULL, 0xD1966A40FAA1C1F6ULL, 0x9396545979526F17ULL, 
            0x6817A841B0A74E69ULL, 0x880EBC95D884ACCEULL, 0x548B3579E8DC1D77ULL, 0x2DDEC91DB4506F60ULL, 
            0xEBB718447E36C984ULL, 0xECD3114EF3EA3AEAULL, 0x8D0A030FA4856853ULL, 0x0C91DBB19815E462ULL, 
            0x8322206C2035056EULL, 0xE715620CF62F3C8BULL, 0xCD813ABAE6889546ULL, 0x0CD5015294B43A49ULL, 
            0x02519B3193EC6969ULL, 0xD0526FC135B90446ULL, 0x9FD81B797A8B2260ULL, 0x7C64C75D18F63416ULL, 
            0x62DBD0AF3DAC5E8FULL, 0xBD37266F3BA251B5ULL, 0x245995539151AC84ULL, 0xF516B0DE84BBA771ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseHConstants = {
    0x2372177028A57E8FULL,
    0x9F72E730517DD1B5ULL,
    0x9F1A7E2CE15A5CBEULL,
    0x2372177028A57E8FULL,
    0x9F72E730517DD1B5ULL,
    0x9F1A7E2CE15A5CBEULL,
    0x755E424FABCEC94EULL,
    0x5B520EF443875E9FULL,
    0xA5,
    0x95,
    0xC3,
    0x73,
    0x34,
    0x3E,
    0x1A,
    0x3A
};

