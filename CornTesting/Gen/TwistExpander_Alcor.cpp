#include "TwistExpander_Alcor.hpp"
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

TwistExpander_Alcor::TwistExpander_Alcor()
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

void TwistExpander_Alcor::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x93D23CDA0B7CEAAAULL; std::uint64_t aIngress = 0xA70CA2294D6AF68AULL; std::uint64_t aCarry = 0x9504C0632D1D9015ULL;

    std::uint64_t aWandererA = 0xB4A8FFA1CA0F6BF7ULL; std::uint64_t aWandererB = 0xA153563B8D3423F1ULL; std::uint64_t aWandererC = 0xAE38B05C4EA16986ULL; std::uint64_t aWandererD = 0x8D88C299DB430289ULL;
    std::uint64_t aWandererE = 0xE4E4E32EFCD293F5ULL; std::uint64_t aWandererF = 0xF58E84CC29A436FBULL; std::uint64_t aWandererG = 0xA6DBE8B8EEB4EC76ULL; std::uint64_t aWandererH = 0xB8CEEE51FE5CEBBFULL;
    std::uint64_t aWandererI = 0xE2146B7B3A4615CDULL; std::uint64_t aWandererJ = 0xFC65552179B0E0B6ULL; std::uint64_t aWandererK = 0xD1BD8F2F4C477015ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11115430778747737844U;
        aCarry = 17612699032022845446U;
        aWandererA = 15599314784639264078U;
        aWandererB = 15666978270990302069U;
        aWandererC = 15464031155672726436U;
        aWandererD = 15792069712249558742U;
        aWandererE = 10367197546385629495U;
        aWandererF = 11694453748910144933U;
        aWandererG = 11660328545531911626U;
        aWandererH = 17926993324684668484U;
        aWandererI = 10681674246333843483U;
        aWandererJ = 17121004573419076312U;
        aWandererK = 11611844428382266037U;
    TwistExpander_Alcor_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alcor::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x90FDA79289B9B2D7ULL; std::uint64_t aIngress = 0xD1E4E635117FCEF4ULL; std::uint64_t aCarry = 0x82913728A55C2712ULL;

    std::uint64_t aWandererA = 0xA4198E3DF82AE73AULL; std::uint64_t aWandererB = 0x9FA95C8908E97827ULL; std::uint64_t aWandererC = 0xEEEF74032E09DEE4ULL; std::uint64_t aWandererD = 0x8446A320CB866080ULL;
    std::uint64_t aWandererE = 0xAE088F8B753ABE9DULL; std::uint64_t aWandererF = 0xA5F6E75844B2B80AULL; std::uint64_t aWandererG = 0xD1534D687F7801FFULL; std::uint64_t aWandererH = 0x9FB895CAABF39CBFULL;
    std::uint64_t aWandererI = 0xC6850E2F9B53040DULL; std::uint64_t aWandererJ = 0xF60B582C75346D82ULL; std::uint64_t aWandererK = 0xCA1C4B7138D2D045ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12374762157339803573U;
        aCarry = 12627199027882501434U;
        aWandererA = 10961924503079838913U;
        aWandererB = 14813189614210445630U;
        aWandererC = 16166543088744535985U;
        aWandererD = 17822681312200111351U;
        aWandererE = 12919652580590577404U;
        aWandererF = 10874355790150100563U;
        aWandererG = 12068603436247619667U;
        aWandererH = 12909532265497892957U;
        aWandererI = 14878075447506924705U;
        aWandererJ = 11029805989385076143U;
        aWandererK = 13162306617410426267U;
    TwistExpander_Alcor_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alcor::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xAC4CFB96E550488CULL;
    std::uint64_t aIngress = 0x8FA8FE2243E668EFULL;
    std::uint64_t aCarry = 0x8014E55054D4A6F4ULL;

    std::uint64_t aWandererA = 0xE00E3D5BA3CA9A8AULL;
    std::uint64_t aWandererB = 0xFF13A7BB174A92CFULL;
    std::uint64_t aWandererC = 0xA0E7C56F24F0F9C1ULL;
    std::uint64_t aWandererD = 0xF7F21A71C8471C4EULL;
    std::uint64_t aWandererE = 0xAFEDDA4F6D76DB95ULL;
    std::uint64_t aWandererF = 0xA32AB7D8FEF8D1FAULL;
    std::uint64_t aWandererG = 0x826233636DDD2B68ULL;
    std::uint64_t aWandererH = 0xD306CD9F1DB3DFD3ULL;
    std::uint64_t aWandererI = 0x8417D67DB2B830DDULL;
    std::uint64_t aWandererJ = 0xC2AD08B00CFB5DC5ULL;
    std::uint64_t aWandererK = 0xC08265B13F1B8A29ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneD, 1);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneA, 2);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneD, 5);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneA, 6);
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
    TwistExpander_Alcor_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alcor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 2 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1984 / 1984 (100.00%)
// Total distance from earlier candidates: 1984
void TwistExpander_Alcor::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 537U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1767U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1861U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1189U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 737U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1700U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 259U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1200U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 265U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 963U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 886U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1204U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 659U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 258U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1962U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 881U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2019U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 151U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 364U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 443U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1671U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 382U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1479U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 70U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1640U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1560U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 189U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1156U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 353U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 216U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1256U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 207U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 252U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 964U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 127U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1511U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 106U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1718U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1046U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1845U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 110U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1183U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1148U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1555U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1457U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1045U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1322U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2001U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 310U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 182U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 552U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1279U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 149U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 621U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1764U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 371U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 892U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 904U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 300U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1092U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2007U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1919U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1871U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1102U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1518U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1190U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1401U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1644U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1543U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 268U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2012U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 487U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1463U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 667U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1386U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1281U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 405U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 358U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1661U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1307U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 475U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1503U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1813U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1465U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 379U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 617U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 742U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 84U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 453U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 430U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 256U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1215U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 501U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 681U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1416U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 247U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1645U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1321U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1989U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 772U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1730U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 120U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 288U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1227U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 735U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 434U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 188U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1313U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1449U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 424U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1488U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1562U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1612U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1990U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1170U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2044U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1029U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 826U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 20U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 952U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 73U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Alcor::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD1D56FA3A85E14A3ULL; std::uint64_t aIngress = 0xB63263FCC3FFE0F8ULL; std::uint64_t aCarry = 0xC6E2F4B8EF53CD7CULL;

    std::uint64_t aWandererA = 0xE3AA652CDF014E87ULL; std::uint64_t aWandererB = 0xC9C0EBD0932AC1D2ULL; std::uint64_t aWandererC = 0xFF82A0A31FF32F6FULL; std::uint64_t aWandererD = 0xB50507E42C6C6485ULL;
    std::uint64_t aWandererE = 0x928B0B5DFA388854ULL; std::uint64_t aWandererF = 0xFB102CB173711F61ULL; std::uint64_t aWandererG = 0xE4781763A16DD4BFULL; std::uint64_t aWandererH = 0xB7C30937E17772F7ULL;
    std::uint64_t aWandererI = 0xC334AF2747F2ED7FULL; std::uint64_t aWandererJ = 0xD7D392C6DF8A7A82ULL; std::uint64_t aWandererK = 0xF738D79A3079F52AULL;

    // [seed]
        aPrevious = 12067749474054421622U;
        aCarry = 14791113872435763811U;
        aWandererA = 16900747330244292007U;
        aWandererB = 14985508366968190867U;
        aWandererC = 14581119991486866789U;
        aWandererD = 16539473116328786034U;
        aWandererE = 10541123982562968525U;
        aWandererF = 12844936198419363600U;
        aWandererG = 10839251178720021283U;
        aWandererH = 14888707998076898537U;
        aWandererI = 18392705684486227563U;
        aWandererJ = 15601171814431532589U;
        aWandererK = 15181939537520086327U;
    TwistExpander_Alcor_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alcor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 2 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 668; nearest pair: 668 / 674
void TwistExpander_Alcor::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1356U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4136U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5634U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2086U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5543U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2646U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 556U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 244U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3214U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2349U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1621U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2369U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3220U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 751U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2491U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 549U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 988U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 570U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1687U) & W_KEY1);
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
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1717U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1520U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1588U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1058U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 351U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1352U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1922U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 965U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 77U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 704U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 310U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 566U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1569U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 839U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 2 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 667; nearest pair: 667 / 674
void TwistExpander_Alcor::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3519U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4364U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 307U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3755U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3395U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7722U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6033U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2085U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6548U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 347U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5988U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6233U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6958U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1234U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 497U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3976U) & S_QUARTER1);
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
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1024U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 243U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 435U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1282U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 148U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 258U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 665U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1097U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 142U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 424U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1387U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1337U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 611U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1609U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 195U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1836U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1116U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 906U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1894U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 781U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseASalts = {
    {
        {
            0xC55AA67056287D2FULL, 0x7E6B44885FEADD42ULL, 0xD0DB8652BF63EA5FULL, 0xE52E779662800B1EULL, 
            0x12F4BB9016CCC2E7ULL, 0x0E0D9E7746FC17A7ULL, 0x5F8A36F6FCF28FF5ULL, 0x5922D9D78CBBE544ULL, 
            0x21FA1A4E530F3821ULL, 0x36ACDF6FAEF2B3ABULL, 0x135E66673A11948BULL, 0xC95119E1D1204594ULL, 
            0xEAFB31B16EDCD789ULL, 0xF4C4D31600AFC186ULL, 0xD263526371ACA118ULL, 0x24EE11670DE42A3DULL, 
            0x11794B90B4B050E6ULL, 0x862DC648DF7ABEC5ULL, 0xF34FCDD91AEE5357ULL, 0x51185FF68FA78508ULL, 
            0x2FBC73301AFCA5BFULL, 0x383AD8B2DE364054ULL, 0x79466E0066147F21ULL, 0x7581A7EB957F9784ULL, 
            0x1A1DD792BCD51C22ULL, 0x7519E4A6CCD5F8B5ULL, 0xD72AF8C5F806B4B7ULL, 0xBC37D819A399D081ULL, 
            0x32CF88244B07DE3EULL, 0x8D2882CA13C4B425ULL, 0x72E608A15BF40D93ULL, 0xC37008D129B89E8CULL
        },
        {
            0xD9ABEC225D1EC3C1ULL, 0x85F0FE6473781C9DULL, 0x0DB0A8D7D6EA4D11ULL, 0x5FD42611A26B337BULL, 
            0x6404A9435ECEFE79ULL, 0xE3B0B5CBA02A2F92ULL, 0x565116171AE3FBF9ULL, 0x31979E9B1E38A3C4ULL, 
            0xD59A8C5AC69D45A2ULL, 0x747D6FE5C7FC612BULL, 0x05945DFEFD433755ULL, 0xE89F44182E4F7C74ULL, 
            0x606600B3C699AE39ULL, 0xD0163A8A24E3C7CFULL, 0xD5EEA13AD81FCF56ULL, 0x184A00846F02F66EULL, 
            0x16AD99E5EBF6DE1CULL, 0xF419173F7B44E6D3ULL, 0x4CF39AA1524BC025ULL, 0x25C3E61472DAE22FULL, 
            0x0AADA00E0043528EULL, 0x64E77A5E6FEDDCA6ULL, 0xD74FFE5E80E081B6ULL, 0xA4B18FC5432E430DULL, 
            0xB7EFCFD1C8C43A32ULL, 0x2AFAC60C7B7355B4ULL, 0x0B6942ADAB7B0F06ULL, 0x9552DCCBFAB29A70ULL, 
            0xE8572C15BB4A1C3BULL, 0xD3561F592392C3A0ULL, 0xAB207CD94EF3550EULL, 0x243E7EA36A9C170CULL
        },
        {
            0x0D511B6509827009ULL, 0x5448D2723FBEFE55ULL, 0xAD81B5F363879F29ULL, 0x1DC43AC9C6682C66ULL, 
            0x726B29FD0C50F5A1ULL, 0xBA978FB2267D9537ULL, 0x142B23340D87D77DULL, 0x7FD976DAB2B790A9ULL, 
            0xE355A240C800BAE6ULL, 0xAC99D089AF66E067ULL, 0x5696E1196BD37D4BULL, 0x63D17F4DE41A73D5ULL, 
            0x2DAC523A1E73394EULL, 0xA8C96FF6005E8FDAULL, 0x94C7F390A6A40BC3ULL, 0x769EB0FDCAA3F738ULL, 
            0xF06244431EBDFD0EULL, 0x3B862D6968BE5BD7ULL, 0xA4E9FE5070B6B2F5ULL, 0xAB16AA34D34EB336ULL, 
            0x9327DF8056B80FCAULL, 0xAB0229BF6BCBBB01ULL, 0x7827855833A02EF6ULL, 0x75C654A4A5EAB750ULL, 
            0xBF5D1E40766720CDULL, 0xFE3B9EB5DC06E00BULL, 0x105B8191DC0A2B22ULL, 0xB54B73C1EEF2D4C2ULL, 
            0x0B209428E51B0F3EULL, 0x8A08DB1E491CBECEULL, 0xEEEE1490FD8E84D3ULL, 0x5977D57187E3086DULL
        },
        {
            0x19AB93D94ECB11C2ULL, 0xF4CC9881E4AEB4E6ULL, 0x017C206403234502ULL, 0xB898CFF76724C23FULL, 
            0x5D62DC0E4B900E9FULL, 0xEA921E12A108C5A2ULL, 0xF018A2FC77E1AE4EULL, 0x6C772FF0E92B2349ULL, 
            0x4750A22618085570ULL, 0x4C074F773F9F21B4ULL, 0xE597231EC98B8F58ULL, 0xB9446863E27D177EULL, 
            0xAC216523316BFEB8ULL, 0xA5028A9C91833E4FULL, 0x6521CD28C7623ADAULL, 0x9A122D5286E45B7CULL, 
            0x4DEA6884FBAC9F62ULL, 0x004595A45522D658ULL, 0x1EB6F69898E29624ULL, 0xB6FD2CCA5CDEF8E6ULL, 
            0x568A752CD0D49E53ULL, 0xD06EBCD28F061140ULL, 0xCA969060AFD97C4CULL, 0x4C847F8C9ABFF420ULL, 
            0x6BD824797EBF2F68ULL, 0x85281573A3E99F56ULL, 0x7B451885346A366CULL, 0x8121DEFC2B0E47C7ULL, 
            0x2CB0C8BDBB47BB13ULL, 0xB0BD65457C6C4FAFULL, 0x0349745E37BA6856ULL, 0xE990CB70053B8ABEULL
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
            0x49C713091E2C4DC4ULL, 0xD6D6771206ECC2C0ULL, 0x849E73AED415424BULL, 0x23B8C6202966B40EULL, 
            0xAA2495843D3DA6FBULL, 0x052B34AB234C8D56ULL, 0x648F3BD831D21E0BULL, 0x9E86FBAF79E067B0ULL, 
            0x6AA4DD16F0FC31EFULL, 0x80F5954D2673BFB7ULL, 0xE9E35D197009D804ULL, 0xC42E32ED9D6689CAULL, 
            0x27B799849E74A7DEULL, 0xEC90C2DBD51F595EULL, 0xE449874FBA9A17CEULL, 0x63E438EE4AA78384ULL, 
            0x01DEB06AC1A9EE2CULL, 0xE38702A8771FABD0ULL, 0xEB1637E2409EC72FULL, 0x5A96EC472A6FE0D9ULL, 
            0x8C7DA4E764853BBFULL, 0x4BCC3CA4ECE754E7ULL, 0x1052AFEC1DBCB453ULL, 0xC4939AC1D508A08BULL, 
            0x053EE0DB61BB9DF9ULL, 0xF4A1348DABFE06A7ULL, 0x967B5DA926B3F0E1ULL, 0xCDFD3E1570CFFCDCULL, 
            0x866571FB424BBA59ULL, 0x9C5B1E4F840DC50EULL, 0x1C8D758482CD80A6ULL, 0x0FFA60199F15EA4DULL
        }
    },
    {
        {
            0xBF970B1BC8227D0AULL, 0x449389C579A16E16ULL, 0x891E1BB840D29847ULL, 0xF82D703170772C31ULL, 
            0x5177B2FC5C1D22CFULL, 0xC25A586112D04E4DULL, 0x9306E8565E8FAA9FULL, 0xE48268EBC74FB780ULL, 
            0xF9AAC00F5AB62FD3ULL, 0x5EB87DF1E544D3B4ULL, 0xC6F5C286E126D732ULL, 0x968CE0616225A5CCULL, 
            0xAC1FEFBB33C666ACULL, 0x3CBAAB566288A257ULL, 0x55DFC90DD2335855ULL, 0xDC0BDEA296C633B1ULL, 
            0x529F801FFD918F18ULL, 0x99DFB3606F495BF7ULL, 0x33EF8A7C2B816D0FULL, 0x2179BBE9467ED782ULL, 
            0x8388AF2C47299230ULL, 0xED175A89B56AEB3AULL, 0x07182B800D2802DAULL, 0x11CB0CA5E289BD22ULL, 
            0xD012CAF49671D16BULL, 0xDE743DF33890F568ULL, 0xEA5E0052C69EF1A8ULL, 0xFC597F9869F7F6EAULL, 
            0x0A0F79AFC659FA64ULL, 0x91082D3525DE5267ULL, 0x3311B38E59C7887BULL, 0xF96D4CCCB9F2E01CULL
        },
        {
            0xE90B7655489D65DBULL, 0x6166482F95BE3CC0ULL, 0x79ADEB3BCB8E416CULL, 0x85C57DF8B04067F0ULL, 
            0xFD23DBB71E53228EULL, 0x26C81C4FA2445793ULL, 0x317B48C04476222EULL, 0x7077E9D859B2A125ULL, 
            0x5D7861C19E141575ULL, 0xFB24F55C1E122530ULL, 0xA3C0154ECB98B161ULL, 0x394CB4CF781AEF84ULL, 
            0xBE717C29FC3FD098ULL, 0x7CAA80AC8FDBFA8EULL, 0x97143E23F381A119ULL, 0xD3CD71297CD9439FULL, 
            0xEFA133C1E9BD397DULL, 0x8A5C692544BDE1CEULL, 0xAFC75E634B071C6AULL, 0x171BF97A31D51BB6ULL, 
            0x9E4B4F41F46B03C6ULL, 0x24B8A249ECBE9EFCULL, 0x40922327D1C44C0AULL, 0xD93743C2032D4361ULL, 
            0xE09D7EA587161BEEULL, 0x75D5A025548B9FD3ULL, 0x626944C292B7F468ULL, 0x4F21D774599481D6ULL, 
            0x66BEFA4451B6AE14ULL, 0x224AAFAFA65C493AULL, 0x36DA31E49AD791D0ULL, 0xE7C79D2FD70CC722ULL
        },
        {
            0x61427F97AF35883DULL, 0xE086542055010481ULL, 0xB649386A97C098C7ULL, 0x67A977F80D5F2602ULL, 
            0x2F41E4BF649B9531ULL, 0x42840EDAAE98CCFEULL, 0x68CBCAC1C27C280DULL, 0x1C82AD9B6A45AEC0ULL, 
            0x589CFCEC5349B989ULL, 0xB968F07372C009B8ULL, 0x3661A58645C2409EULL, 0x2A6389528D58D031ULL, 
            0x44E9F08AB6B9DD1AULL, 0xB575611FF4707F9DULL, 0x486B5DA9557539BAULL, 0x90D786C639D79038ULL, 
            0x02219D4C117DED75ULL, 0xAF8EAB12E9F88D18ULL, 0x54592D29680971B7ULL, 0x64DFC6917B1F9DD4ULL, 
            0x1CB0D9EF13177741ULL, 0x1D3FA58C6B780A8EULL, 0x98033D5A3F0AB6BBULL, 0xD542AF6457CAB4ABULL, 
            0x57F0B9F5F0A047E8ULL, 0x236A6CCF7BC065E2ULL, 0x015537BB0C5565C2ULL, 0x6410C37ACF36EF0CULL, 
            0x126F42821257860CULL, 0xC50127874A93702AULL, 0x72010BD47C1DCC7BULL, 0xCB0AFBC9A783F090ULL
        },
        {
            0x6C9937E66C3DD9F3ULL, 0x25113454E43574B3ULL, 0x32A6AF728EE40480ULL, 0xBAA3C3FBA356CA91ULL, 
            0x2696BC2D78CBB503ULL, 0xBAA2926E322A3418ULL, 0x35A9B3B3C70B1CEDULL, 0xFF4BF65DC1D4EC21ULL, 
            0x1D4125FA153498C3ULL, 0x040B92E0386A7EAAULL, 0x9E6A460AC71EEEA8ULL, 0xD160ABE487AC2AE0ULL, 
            0x6B45718FD0CA7FFEULL, 0xDEC1C5067640226FULL, 0xD76D3141E9A6DDA0ULL, 0x3DF9C00FC575ABF1ULL, 
            0x08BD77315BB9C049ULL, 0xCA1AE2EB74CDCD32ULL, 0x2AD0356EDD985594ULL, 0x3665B41034F89118ULL, 
            0xC567A96617BBD85CULL, 0x15D6406C97485D35ULL, 0x78227F44DD0A3CABULL, 0xF8EC09F427CC94E5ULL, 
            0x348C0F1DF3E89121ULL, 0xC54CCD9C9E3EAFE6ULL, 0xD24CD2808D1AB3EFULL, 0xF42CD827234F79CEULL, 
            0xB4244CC5999AF07FULL, 0xF856F81859DBD713ULL, 0x8FA3C811EB1B7EE9ULL, 0x6643C13E4739847AULL
        },
        {
            0x1B99593FD2EF10BAULL, 0x9D08B9B79591B993ULL, 0xA5CAC4B69B11CBDCULL, 0x7560F70233C7A6BFULL, 
            0xC23953CBFCE860D2ULL, 0x8799BAD1A24DC776ULL, 0xB1FCA9033E684D1EULL, 0xADB1B50ACAAE4720ULL, 
            0xCC51548B47B54006ULL, 0xE1F2B62F632294EAULL, 0xAF4C0F57DA614F6AULL, 0x4BDEDEB5A2A82074ULL, 
            0x78D61D6195CBA09CULL, 0x6D583DAA26A72835ULL, 0xCED90B67D02D2CA9ULL, 0x00EBA2A21CCCA046ULL, 
            0xF6E2C0CE7DBCC0F2ULL, 0x2E76D72909B66FF2ULL, 0xC85CE31FBF0C572FULL, 0xB224F76DDE8EC734ULL, 
            0x6C7D756F9400FF5BULL, 0xA6D9443AC4DF6673ULL, 0xF34B342F48D84BFEULL, 0xA5CEDCD498995FA8ULL, 
            0xDD1C8D9D491E045FULL, 0x55B3ACF9AA5E227FULL, 0xFA4A7C093A4664AAULL, 0xD7167DE49B4FC2F8ULL, 
            0x81ED99D4967A20F2ULL, 0xDAFC78FE29F57CB2ULL, 0xAD3F35D7D5B3DFC3ULL, 0x64BBB3FAFF7D2413ULL
        },
        {
            0xA6F98FED3A8274C3ULL, 0x89DE80A06330D0B9ULL, 0x63D93CC88F8B7AEDULL, 0x5BF29857FC97309EULL, 
            0x9C8D99877E18BF6FULL, 0xC8F5DCF3508A046DULL, 0x59F51F05AD59B392ULL, 0x108D416DD8B4CEEEULL, 
            0x4FC77D055474ABCFULL, 0x30EC1D09029B8623ULL, 0x2294A505B1798E9DULL, 0x9E9DD64C027D1870ULL, 
            0xE0C2F54CB0354896ULL, 0x9967F573917A1A82ULL, 0x203087CBB1B9270DULL, 0x5A39ED555568F4DFULL, 
            0x43EC137221951817ULL, 0x0DC4148CC7D5577DULL, 0x31855BFCC43A90C7ULL, 0xECF17FB76799A8B8ULL, 
            0x7F71EDAEFBB8048FULL, 0xC2800FF076B919EDULL, 0xD61A221839FF9DE8ULL, 0xB9ACA259597BCC60ULL, 
            0xE135643671A26FC7ULL, 0x2F34E764409DD5A6ULL, 0xF6EFF7AFD513CAFAULL, 0xC3838E9FFE8C71C1ULL, 
            0xD18B1A91FDA219C4ULL, 0x764117E7BD5547C2ULL, 0x5986BD667D41EDE0ULL, 0xA73ACB6369456845ULL
        }
    },
    {
        {
            0xC072E990ED2B59C9ULL, 0x570653444FF56E88ULL, 0x9BA6B18C93459541ULL, 0xA6316EB5085F316AULL, 
            0xB1A286B9AB944D97ULL, 0x5EBA3C05ED43C1F2ULL, 0x4957C1BA19FDBE7BULL, 0x7F7557C88209EC73ULL, 
            0x8B6888B53686F0B2ULL, 0x4CF41ED0BDC82DDDULL, 0xC25963BFD3C9C804ULL, 0x49631687B6C8F765ULL, 
            0x79B99FBB08F53901ULL, 0xD8F29F8BD1963FEAULL, 0x398C8C24C69CA1EDULL, 0x21FDFA0981995DE5ULL, 
            0xD6A7D0FF8866541DULL, 0xB5BE0239614BAF2CULL, 0x36BD3454C703CE8FULL, 0xA624A206BF390BBDULL, 
            0x8E3BB491E0A92844ULL, 0x00BE2632F972560BULL, 0x3EAB2529BBE69F85ULL, 0xFC2D2E4D6A12DA53ULL, 
            0x7F62DDAD2250F653ULL, 0x2298AF1D1A0AFDE8ULL, 0xFDED7E39920FA04AULL, 0xCB0627567ECB508FULL, 
            0x8655EB4BCB8B14FEULL, 0x7DEF6A4F84082819ULL, 0xE4C9B5D7AD797FE1ULL, 0x2FED14587DAAEA37ULL
        },
        {
            0x94D50A417F80E190ULL, 0x2575134950949754ULL, 0x94F82E57C84C6204ULL, 0xD249DB868EC4C3FEULL, 
            0x6D955A6264D802ACULL, 0x642CAE1954D7BAD2ULL, 0x6AD35824D466FD4FULL, 0xF80B43814CDD08CCULL, 
            0x9B1D9EA72BEB9C1EULL, 0x580897ECF1240990ULL, 0x3746BE5C020CB2DDULL, 0x7DBB15E7E57863DCULL, 
            0x41D3CBE862EB56C4ULL, 0xABB3BF17717E2A03ULL, 0xE5A3A7F679DB0FC0ULL, 0x687D8F49BFDFE8B8ULL, 
            0x94E0B01A197C1362ULL, 0xEBF8BC8FC8DE3A7AULL, 0x10575E0C1BB3210AULL, 0xE870F49A6A33AD39ULL, 
            0x28B142611EDFCF1CULL, 0xB5FA8BF575DD424AULL, 0x68D96583F7AB24F1ULL, 0xBFA5942FFDF415A5ULL, 
            0xB9D6520E04F5CEB4ULL, 0x12B250C3CAA7B924ULL, 0xA85DACCB740BBE99ULL, 0x5D8843A8B494B431ULL, 
            0x617045362579B910ULL, 0xFE7F25A50B20F38BULL, 0x7A211852A8B17C73ULL, 0xE28122F9219B82FEULL
        },
        {
            0x3D96CC29384CC087ULL, 0x3EC756F6072286D7ULL, 0xBBAB5004520C0F7CULL, 0x6ECFA943AFA62961ULL, 
            0x55FD9724F0FD29F6ULL, 0x8557617F00191911ULL, 0x31F12DBB1FA8A3ECULL, 0xCE15D48392730E88ULL, 
            0xDEECC50D8D73C569ULL, 0xC80A45DAE7987312ULL, 0xBCB2B124E1E43BC5ULL, 0x40A3C9752A6C5F8CULL, 
            0x5C394AFAC630A30AULL, 0x3E60525FEC6064E3ULL, 0x9CDAB474E28B09F1ULL, 0x641269E7B606EF78ULL, 
            0x9ACD85F8776420FDULL, 0xB452E1D164889A3FULL, 0xA61DFECB226B574DULL, 0x4E012CA8C76B8335ULL, 
            0x29BE7023F91C75C7ULL, 0x309725064D91A4C2ULL, 0xA9D0F967A8C8630DULL, 0x178146B6255B9FC6ULL, 
            0x7EE23953BE5BF722ULL, 0x5B497EC537CBE151ULL, 0x0CE12C3020A0A931ULL, 0x2F6E0EB956278418ULL, 
            0x64D98ED60A994989ULL, 0xFEAE9F5318508DDEULL, 0x4A53861FA61A3A90ULL, 0x852DA5E471BCB308ULL
        },
        {
            0x0512B55AEF1D7AEFULL, 0xD8F4E7BE9B2AFC0DULL, 0x40F878F238D936CBULL, 0x29E8FE435D4D52E4ULL, 
            0xC1DB4A0A54ED3B64ULL, 0x6116A4273B224A06ULL, 0x83B199D3E52542BDULL, 0x84AF9198F186D048ULL, 
            0x665CCFF2D7E57AB5ULL, 0xEF2DD2213475CDFCULL, 0xE6C778A2321BACF4ULL, 0x93699BE0D8C7255DULL, 
            0xF94D6A326AC193C4ULL, 0x5B2A8F0D7D062C7EULL, 0x8F646A30D537AA45ULL, 0x78065C4DD97D2D98ULL, 
            0xC9D68860D1CB6ADFULL, 0x66A2019EE25E222FULL, 0x3CBA9E3403D671D9ULL, 0x721C0053B5585971ULL, 
            0x2383F1862C225E44ULL, 0x6B78DEBF46A6C08BULL, 0x01D013B9E5551BAEULL, 0x62C53C6239C638FDULL, 
            0xBDE7628E22A06A90ULL, 0x3D67BE4C657CC300ULL, 0xCFEB77D98897CC62ULL, 0xBDE8A7218FFF634AULL, 
            0x73DC663CA60E4246ULL, 0x0F83B0BDA544AEB2ULL, 0xE805B5B0F6C04274ULL, 0x5DE1880FD724A4F5ULL
        },
        {
            0x2793D996B409C773ULL, 0xFAD79777639C07D0ULL, 0x1815E71EB21B71B0ULL, 0x3927F600EA53829DULL, 
            0x7B36D9E0679E5CD0ULL, 0xC74EC227DE634723ULL, 0x9A99616CD1E937FDULL, 0xBCB920EC2CDFC8FEULL, 
            0xEF03839063C5A93DULL, 0x148020070262429AULL, 0x07431594A974FDC2ULL, 0x2B01145DBB227381ULL, 
            0x06CF063D58AB340CULL, 0xE70A720052F1FDA4ULL, 0x212634940BBDA9CBULL, 0xC57ED4A81DA4E96FULL, 
            0x65BE0BA13401493DULL, 0x1D06ECA0EA123DAAULL, 0xF4E4ACAE2F5256C5ULL, 0x3950EA66E8CDD6C2ULL, 
            0x6E004FDFFD5478C2ULL, 0xD67C34B576170742ULL, 0x4F7385BB258C22C1ULL, 0x6A7B914B6D557D29ULL, 
            0xC464C10D8A79A9ACULL, 0x42B8F2FF50EF9ED6ULL, 0x4C4CF68E6C559F05ULL, 0x073708DC670DEEFDULL, 
            0xE6D6BF96EE8CD4D6ULL, 0x27FB050BD2922CD7ULL, 0x11396C4031B74DCFULL, 0xB484527140BF0DE4ULL
        },
        {
            0xFEAB485B9848CDADULL, 0xF461B46B68891B47ULL, 0xFE0DCB5BE03DF168ULL, 0x5578B1A72F67D397ULL, 
            0xBFC5237EF9C7A859ULL, 0xFD9F9ABA0CDC7A45ULL, 0x54F56858280713FEULL, 0x842AB5368DA5D249ULL, 
            0x6655903DD669DC27ULL, 0xAA6B3A90BA53179BULL, 0x2D259BEFA979C67FULL, 0x06537713B5E75FD6ULL, 
            0x85DFEA36BA52352DULL, 0x1A7447F43815BEADULL, 0xCEB68C80C4B70E88ULL, 0xB8D064F5C7F2B9F9ULL, 
            0xE1D8665391FCCAC8ULL, 0x7E22F3D28785D419ULL, 0x99B021373E39FB9CULL, 0xF415B981B30A5D17ULL, 
            0x29CBB99D54FF838CULL, 0xCF0249738A9C0628ULL, 0xD7BBA4C2E0D421DAULL, 0xEB285AC08FB81DDDULL, 
            0xCEF306DFE4D0C880ULL, 0xE49E7C60C5743AB9ULL, 0xC08F43F72B5EEE6CULL, 0x42ABB8E89806D864ULL, 
            0xD41D4106742BF6B4ULL, 0x29DD860270BAE983ULL, 0x4761ACC7DAB88F26ULL, 0x225ACC59B6DE0280ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseAConstants = {
    0xD1015DE850999614ULL,
    0x9322C7C7DDB39184ULL,
    0xC37E13E83D0DD397ULL,
    0xD1015DE850999614ULL,
    0x9322C7C7DDB39184ULL,
    0xC37E13E83D0DD397ULL,
    0x798A9D7ACF00F556ULL,
    0xFD376913982C7A33ULL,
    0x9F,
    0xB5,
    0x29,
    0x1D,
    0xC7,
    0x9C,
    0xCC,
    0x69
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseBSalts = {
    {
        {
            0xD0D59E01053135FAULL, 0x7AE1873D7C14D663ULL, 0x6A0AA4E9EEA8E7F8ULL, 0x2BDA33BC71F2AAB5ULL, 
            0xE301C31A7AF3CBA9ULL, 0xF875BE97AE26383CULL, 0x3072A60C67650CA9ULL, 0x47C15B2D8DB03CB6ULL, 
            0x8C69DD6ECF41AEDEULL, 0xA869147462EC745EULL, 0xE345CA30D974E320ULL, 0xBC875633484241FBULL, 
            0x6F5AB62CD39142D0ULL, 0x1E90C29BA78E82CAULL, 0xED90DF2A90661B7CULL, 0x25FF80957ADA9B40ULL, 
            0xE7DDD4B3ED3A7390ULL, 0x4FEA7CFBD0119D55ULL, 0xD84B9EA75B3741CCULL, 0xD59C2CC0BE632128ULL, 
            0x5A4000BAD009A04BULL, 0xDED9C7DD7F51726FULL, 0x79B410750CF8A603ULL, 0xD812A22A9A060AF4ULL, 
            0xEC25D9B9D7D37DE7ULL, 0x247C1DC3EC2D2451ULL, 0xE7D8D3D54C998D94ULL, 0x91D841EC4CB5890BULL, 
            0xEF4C53DBAA6C8654ULL, 0x5FA5E8572F44363FULL, 0x638EBB601E14893BULL, 0x8C18DCB9A0300E2AULL
        },
        {
            0xA7AD4AA141D258C2ULL, 0x4A79C500C9C17E6FULL, 0xACAAEF8EA6867C32ULL, 0x853C9D7DBFC597EAULL, 
            0x7A7F9B3349359DDCULL, 0x6CC5A0DE22E1E893ULL, 0x0AC14ED545E35F16ULL, 0x3DAE64B6CED84234ULL, 
            0x8C889654CBC99F10ULL, 0x9C66A16018CCC6BDULL, 0xE9DDFDEFC904FDACULL, 0x1932AE7A82508A40ULL, 
            0xA25E0CCCDBBD9B77ULL, 0x1951EE0F8F70BE29ULL, 0xB94A8D0724950BE6ULL, 0xDAA37B6C9A68727EULL, 
            0xA3086675060BC5FBULL, 0xCB367ADE8E717F51ULL, 0xE7C472C2D34F3577ULL, 0x78FB98366B477EC3ULL, 
            0x1F47BF8676307B35ULL, 0xA6CA9D58A8613097ULL, 0x18F2317AFC3E6ACCULL, 0x50BE69C1786A971CULL, 
            0x70BC41F23542B532ULL, 0xDA29DE77F4635408ULL, 0x5E7AC25301156D1DULL, 0x02531AAE41516E94ULL, 
            0xA2D84E9166F75D74ULL, 0xFC05C662D88D3E82ULL, 0x5A49D55BCC862814ULL, 0x3E73136DCABD9DA0ULL
        },
        {
            0x0AEAC0649A4A90A7ULL, 0x3653DED114B8C37CULL, 0xFB150FA0058B83FFULL, 0x2AA6C07861AB9A03ULL, 
            0x80860F6F90E51A2BULL, 0xE8B90D12E0248EEEULL, 0x2B206F5146C42C23ULL, 0x99D685607817D570ULL, 
            0x6B6ED9FAF1D54D1FULL, 0x3CFFEEFD351FD5F3ULL, 0x1E55B96AF648E63CULL, 0x161FE6011BAB309FULL, 
            0x0CE6BD327A8B00DBULL, 0x7BE6855495452AD5ULL, 0xC3CAADCF5DEBC12EULL, 0x8AF00655BE098996ULL, 
            0x9E2086C8869ACAD5ULL, 0x96E3FAEBE1E168CAULL, 0xC1D43FB0E1882617ULL, 0x7983358BE662DF74ULL, 
            0x32D4020ACB2077BAULL, 0x35BBA549BBB860DCULL, 0x5851C8B8E3E0BC57ULL, 0x7BA822EF30E53306ULL, 
            0x2EEAC1AC5C9D085AULL, 0xB3331C69BD72885DULL, 0xF8C0CF24420BF4C0ULL, 0xC8E1072FEEA131EEULL, 
            0xE26822AF58AB1CE7ULL, 0xB3A8A43C01092262ULL, 0xAEBFD8D2555ECF16ULL, 0xA132FADD4C5B414BULL
        },
        {
            0x0F56540418507221ULL, 0xB8AE5B495E66F88CULL, 0xDAED6B8F2AA7E2F7ULL, 0x836435DF14FAF106ULL, 
            0x0E0BEBBCA6805FB5ULL, 0x170A665EF92FB2F6ULL, 0xB2BEF6ECA7448801ULL, 0xAD3B960CB30ABEC9ULL, 
            0x193DF1CA51813321ULL, 0xA36DBA61DE9063B3ULL, 0x1FFB2FBB533E803CULL, 0x9F54A35F9BFF7227ULL, 
            0xEEE3594EBC31B055ULL, 0x4392ACE39D8F6186ULL, 0xA7FEA3790D55A87EULL, 0x1486AEA002BDDFA2ULL, 
            0x930B444908A6527AULL, 0x7FC737DB41D9B40BULL, 0x1AAEB34C8A31A85CULL, 0x0B6089E868ED1F65ULL, 
            0x9AEE167D47AB227EULL, 0x7C1A238542D3E6CCULL, 0xB6D9CF385F0CB41BULL, 0xF43F4EC701311C2EULL, 
            0xAAAE3DFEC1E80B75ULL, 0x3BA9F0A3B3A32693ULL, 0xF28C36DD80291B46ULL, 0x73AFFE54954748C0ULL, 
            0x453BA63FB1E99401ULL, 0x07A44DF707983936ULL, 0x01F9F641AED94A6CULL, 0x0C094DC2ABB138B4ULL
        },
        {
            0xACBDD2D2E7B85048ULL, 0xCD94879B1EA864DEULL, 0x4175D719171AA069ULL, 0xDF5FD72C2A9991A0ULL, 
            0xE0BF46C250154444ULL, 0x1ACB7F5F90FAD133ULL, 0xA11B1619D32559AEULL, 0xF6CBDDD06722EEBDULL, 
            0x05CD020B0C3F6D67ULL, 0x15C34F916CC7AE10ULL, 0xCF84C94256FF3EE6ULL, 0xAE7BBE3465B82B50ULL, 
            0x76032F7C82EC2B6CULL, 0xC5AAE4A18F488DB6ULL, 0x20AFEC6E65BCF9D1ULL, 0xDE783132E3C3933EULL, 
            0x073D3EE6B0B91E1EULL, 0x19AD8E64E3BEC332ULL, 0xBCCEB423404B2E8BULL, 0x64374622C1A1D7BAULL, 
            0x03397D5840E6A67FULL, 0xA15E34966DBF5204ULL, 0x9C06B2A9E34A350EULL, 0x98B17B1E81E97719ULL, 
            0x6680F4DD711173AEULL, 0xDF786DC7D31BB096ULL, 0xE31AA50B19DF04B2ULL, 0xAB7B8F049524EFE8ULL, 
            0xD40A4AA57B79412BULL, 0xAC4159CA82D552CEULL, 0xBA6DDB01826AB3F3ULL, 0x47B145A0430C03A5ULL
        },
        {
            0xE65AA1FA86F33ECBULL, 0x5F53F749356E9DB8ULL, 0xBC602DDDCAC61A8FULL, 0x174F1F9A93C47DFBULL, 
            0x325E26CB3BB4A6FBULL, 0x3EF141DB37142A27ULL, 0x2E0A5D76B85971EFULL, 0x801481572EB33263ULL, 
            0xB08E805A2C0BD7B6ULL, 0x7294724D4F67810DULL, 0x72EF9DAF5C452040ULL, 0x6D2F40B93EEA42E9ULL, 
            0x0056EBE911AC7476ULL, 0xFED126AE3293D3CAULL, 0x44CFE3C8EAB1B762ULL, 0xF4BC090196407CACULL, 
            0xB96049953CFB060DULL, 0x36293EACD7D29FB4ULL, 0x8F1E2329A667132FULL, 0x67F9179CD43ED332ULL, 
            0x05A2008AA3485419ULL, 0xD7F2B75BF0B3D95FULL, 0x18E8FAE349FAA083ULL, 0x7314A7BE0CA0F3F1ULL, 
            0x7FFEDBA28948F49AULL, 0x26C817376E40C47BULL, 0x7FDB7FDAE14798DBULL, 0xC3A667F4105811B4ULL, 
            0xCDDEF3BAACA98F54ULL, 0x781C978E72DF17EDULL, 0x433C087209D3CC05ULL, 0x532997D806D4BE59ULL
        }
    },
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
            0xE98E88DEE391F07FULL, 0x41AF44B89E2233E3ULL, 0xA29E9AAE1C7739ADULL, 0xE47D095027358A5EULL, 
            0xD9E16D3B59E1315CULL, 0x90B2C29CCF07660FULL, 0xA92761291C8E806CULL, 0x3F8B58B979AAFE2FULL, 
            0xC1ABAFC58047375DULL, 0x4CD161CFD211B6ADULL, 0x9DCC2D750A7DB0B7ULL, 0x10783AF4F1FAA4ACULL, 
            0xAF09F514566993CCULL, 0x1957695BC4333E39ULL, 0x1AB09C6C99C2F461ULL, 0x792A5B4E8E36C820ULL, 
            0x38B39DAD9813316DULL, 0x82941F1BB2A27092ULL, 0x8B4D0B42512CFAC9ULL, 0x042DB00779E0F1A5ULL, 
            0x4B5BEA027BCC5766ULL, 0x503616CC710D7833ULL, 0x7FDAAEB5818E933AULL, 0xE38F145445BDB23EULL, 
            0x302BCB2A5510237BULL, 0xE6740F0339F7F8DFULL, 0x1E2810770C755323ULL, 0x230E1522B65C669EULL, 
            0x7F80DBA836602BE7ULL, 0xFE150BDBEA1C83E4ULL, 0x4ECF941802EC0A76ULL, 0xC003755998B182FEULL
        },
        {
            0xEDD96B8678A5A4E4ULL, 0x7B94A4E01A798298ULL, 0x0C8DB843D2CE0BBFULL, 0x0B98FA7E9597540EULL, 
            0xEE49059C040C8726ULL, 0x776DDF16F3B36326ULL, 0xFA7B566F53E76183ULL, 0x15793FFF59B725E8ULL, 
            0xF328EF6631799D5AULL, 0x21924A50487AFC08ULL, 0xAE31A62A0D99BF6CULL, 0xC88B1496792826B6ULL, 
            0xCB8A836F59CBE001ULL, 0xC5FBA160E90B2BDBULL, 0x604166FEBC7FF962ULL, 0x1374BA15FB0BF54BULL, 
            0x0DF82FB5ED93D137ULL, 0x624FED764308625FULL, 0x612BC94F1A59E896ULL, 0x535B950CAA173D82ULL, 
            0x791DA5DA40EA83C3ULL, 0x860B0D568CD9D6A4ULL, 0xBBD25DB1F29560DEULL, 0xF4B01ED78270D177ULL, 
            0x387CEFBF1B39A0B2ULL, 0x0250C49C7357CBBEULL, 0xB28AF1A3B2440825ULL, 0xB3DAE340D3248447ULL, 
            0xF303E8FF5774A14BULL, 0xE868D83BF5887500ULL, 0x1F1C14FC372088B2ULL, 0x9CD3B425327CF41FULL
        },
        {
            0xD534FBF2FBD58131ULL, 0xA14861AD0F34CD61ULL, 0xD2411F61B74CEB48ULL, 0xC9BA6093A36C309CULL, 
            0xF3F2BF4E8CC6E744ULL, 0x349F13B7564A9DC9ULL, 0x8DA763E03A37D7E6ULL, 0xD1BC8F663373FAE0ULL, 
            0x2EE48F6E338037D1ULL, 0xD9D8472C8D175D91ULL, 0x7A2F14874EDE96D4ULL, 0x7B0CEDD9F933DBF0ULL, 
            0x9A164160AE2CB5BCULL, 0x239BB046FBE13C47ULL, 0x913031346BAF2E55ULL, 0x2C32C2BF740FC4F8ULL, 
            0xD34A4BFF17EDF696ULL, 0x406C78E282FB810CULL, 0x61F396297D57FD27ULL, 0x412885EF80CEACD9ULL, 
            0x88999C64BD960811ULL, 0x29AE62F53C1EC58DULL, 0x122FD29B1D1116EDULL, 0x2F66E7F153A7AE76ULL, 
            0xE65CE0C7ED67DADDULL, 0x6FB57120A7A8506EULL, 0x7EE121D6A9C32857ULL, 0x93624A1AD39EF334ULL, 
            0x15BF562F7CA28511ULL, 0xFBD2BCF928FDFF68ULL, 0xDC1B6921FFEAD7BEULL, 0x0BA4652B3D9B8912ULL
        },
        {
            0x85AA4852B8DB4755ULL, 0x2AC7A36D4469AE11ULL, 0xEEC5A78C87FA3948ULL, 0xC34AA01FF9A4C548ULL, 
            0xFA2B7C900A191DB2ULL, 0x52342A7F85A04927ULL, 0xDB40DA3CC2D42B12ULL, 0xDC2A673762B38E19ULL, 
            0x54E8B398D9EF087AULL, 0xB68318694B9B9AEDULL, 0xCF7A062709A733ACULL, 0x1954C28331EC7351ULL, 
            0xAD16E7A919D33AC6ULL, 0x72E28B4DC9EE9824ULL, 0xD2DE247A21E7638AULL, 0xE28D214268AE4FFAULL, 
            0xC798DDDA5813E3D0ULL, 0x39C7F8E394C14158ULL, 0xFEFF432A8604302EULL, 0xE702314E03851F46ULL, 
            0x9571497DB027D4F2ULL, 0xB6CAB2C76BEE92C8ULL, 0x1F6B806F60FC23CEULL, 0x01A1CA295B4C0564ULL, 
            0x36769EA88552EA06ULL, 0xC2E8507DC326D325ULL, 0xB3E084382371E886ULL, 0xD8506B36F3DB39B9ULL, 
            0xFFA22BDD26CC9039ULL, 0x271861B09D90B93DULL, 0x3EBCF7C971BC3ADCULL, 0x3E0CE1ADD52912A3ULL
        },
        {
            0xBD687789EB5A8DE1ULL, 0xC04730B071ABBC74ULL, 0x3C34E1E77A31025BULL, 0x1C2541B73D0E33DAULL, 
            0xDDBD6C8596433384ULL, 0xED74AF1DA39DAC9EULL, 0x9F9807F92520997EULL, 0xD051F8C28686D6D8ULL, 
            0xF92859912D0C3D27ULL, 0x39A0D84BDD110CE0ULL, 0xDA4138AFCE17BEAFULL, 0x84C5A1B87A7C01D3ULL, 
            0x08488EC1783B5944ULL, 0xC5150FC5B6EB9222ULL, 0xFFF51C87CCDBAE8CULL, 0xA650595B0BC8D0EFULL, 
            0x7902CB91DFCC0492ULL, 0x38482930E5DB12D3ULL, 0x106C154079E335F2ULL, 0x40ADD327FE798E59ULL, 
            0xEF589C3601B2ED45ULL, 0xD95B9E341D3AA4E0ULL, 0x81395B5AC09A6C1FULL, 0xE4D527366A3B57C2ULL, 
            0x755F62671F317B2EULL, 0x611F06B8C7E5B7E6ULL, 0xC6FCCA63803F2754ULL, 0x97A71A8F51B15994ULL, 
            0x35921AA43164DAF6ULL, 0x99F71EC5CA4C8547ULL, 0xA6A59041B97F4B4BULL, 0x64665D556FD9D184ULL
        }
    },
    {
        {
            0x5F54ACB2D39E78EDULL, 0x6C8873B13687CD4AULL, 0x5D804280BB977F7EULL, 0xA402F1866A2EF938ULL, 
            0xD6BCC65D11B4A3FCULL, 0x750EAEC19859A769ULL, 0xC9D4280F8BE5C246ULL, 0x9499F4752CD1345AULL, 
            0x02FF46C00CC4BD3BULL, 0x412DBF3DA41A64CCULL, 0xD5EF069DDBFD16D1ULL, 0x204F10FB567A5CCAULL, 
            0xB636468723FD455BULL, 0x9623D20B04504874ULL, 0x7E0DA7F1064DEC46ULL, 0x984CAE8324F24A3AULL, 
            0x6DBF5A4CF421CF68ULL, 0xE2271BB06D69FD8FULL, 0x65E792333D70F338ULL, 0xD32E02A0F2448EC1ULL, 
            0x3F235366B6674836ULL, 0xEDB1439D954FF0AEULL, 0xAE05DF99D63816A4ULL, 0x27457D5A382CF077ULL, 
            0x41729447F6969A85ULL, 0x01830F482FD6BBBEULL, 0x341A25AF4D9CE9F7ULL, 0x7AB9FC7C778CFCADULL, 
            0x9DB8581FE898A47FULL, 0x8EDC9AFD0D105A97ULL, 0x32C2AF7DDDE70636ULL, 0xF877770ED6709816ULL
        },
        {
            0xD2B285D67A825F85ULL, 0x711D4DDB0FDFF159ULL, 0xF240FB376EDFFE9EULL, 0xCAA923336B9E4398ULL, 
            0x854B7DC29F76E082ULL, 0x537ADC809D5163BCULL, 0x54D7723A8D18BAAFULL, 0x0814E01253E4CFABULL, 
            0x6A0C83CD6C6226CCULL, 0x6889FD12C8978A35ULL, 0x3383AE3F53EAAD86ULL, 0x4AA24CC1F5844DF3ULL, 
            0x7859D5E453646CBEULL, 0xA59B869507C7AB6CULL, 0xF101515701C7C92DULL, 0x3F47E2D92B3C0A65ULL, 
            0xBF4069CDDCF5D5BDULL, 0x7D628D4A27AC8768ULL, 0x5BBE1D19408648FEULL, 0xCF46C24EDF7A2EA9ULL, 
            0x7FB983BAF09325FDULL, 0xBEA0255FB5639F18ULL, 0x007B424A49C94522ULL, 0x118091E9E558CC44ULL, 
            0x5DA22173511910CFULL, 0xCF3031F93C03C24BULL, 0x121E962B9BF24ADCULL, 0xA2BC3A1B6B6B3B48ULL, 
            0xEBDF850BFF4D1104ULL, 0x9F80DDE3799A76BAULL, 0x1A2FBF433F695157ULL, 0xEF533EB13EA3559DULL
        },
        {
            0xF9E9693143C39774ULL, 0xCA5D08BB765FAD27ULL, 0x5FADEAD7D4E85FE1ULL, 0xF762733B010374EDULL, 
            0x09D2F30F715B955CULL, 0x45FE0C1AEB15B905ULL, 0x6156349BB2D3D61EULL, 0x18389C3F13DE2B16ULL, 
            0x37CF0787B44EA551ULL, 0x2662308A181B055EULL, 0x8797274668EB8D35ULL, 0x766D8473B21A10C9ULL, 
            0x26930140E6E5CC6FULL, 0x70109D1F9E9032F0ULL, 0x3CF98A10D697D33EULL, 0xC2055DBAAC9EBEACULL, 
            0x722FD317FE6179EAULL, 0x5A529A787A13BF41ULL, 0x6E22AB016A979537ULL, 0x46B742C354283E3FULL, 
            0xB5399619F8DCED42ULL, 0xF3B1A98DB5FD010CULL, 0x907C4C29E39B6C79ULL, 0xDEAA3F2F5E7D6F07ULL, 
            0xAEADFAFD12C707CAULL, 0x9D5272FC4D9588B6ULL, 0x5B47B0F21C6DADA0ULL, 0x2BD8F280E53D1E71ULL, 
            0x40CE9BDB10AF58B9ULL, 0x4730054CAF75AEC7ULL, 0x782E007C2A5F5C86ULL, 0x29DE003238A48202ULL
        },
        {
            0xFE9E093C5799157AULL, 0xE7C8440F6E1464CFULL, 0x00A5351E6CF5099CULL, 0xF8FE1F68DED42B50ULL, 
            0x8233B0404F0EA4F6ULL, 0x5DBD073951CDFDBAULL, 0xC57ECE7CE663E5A8ULL, 0xD3EB27547EF54BABULL, 
            0x04483974593A0AC0ULL, 0x578942DF5D53A436ULL, 0x5C0A52217FB9D8DCULL, 0xC30FCC180271F3BDULL, 
            0x8FA5C6EFF0D55F44ULL, 0x23C7D16DF8B75839ULL, 0x8CEFB02E1AFCE465ULL, 0x43DBEF722EAD74B5ULL, 
            0x631DAB8DB51AAAA3ULL, 0x2DD36C0B55B981D6ULL, 0xF95A6F8C8DB9A407ULL, 0x23E029BD6602FD41ULL, 
            0xE1E0288DC7FA86A7ULL, 0xB24006F7F3F5DEA6ULL, 0x7145B41731D69FABULL, 0x782C7A6D7B6FED14ULL, 
            0x302EF39E1D5130DEULL, 0x6906DE0E8D4D0F4FULL, 0x6FAE165067CF7C28ULL, 0x57BDAC6A5FB12566ULL, 
            0x0D341DF6184166E4ULL, 0x73592F8AADE17A94ULL, 0xA9CF9AD882731420ULL, 0x19ED2ACB035FB83EULL
        },
        {
            0xB1773A35B19DE0F2ULL, 0x36D3C195C997A8A1ULL, 0xA6E856EAD3A15F4AULL, 0x65CC6BE2A6B7FF29ULL, 
            0xBBFB6A14878C1A0FULL, 0x565104D96109B11BULL, 0x9837B65E5C6BB6A9ULL, 0x1CDE86808209096DULL, 
            0x4867172F5D3F1D65ULL, 0xEE1C17DDF4E3E54AULL, 0x15A554F915F50575ULL, 0x0C2FB6EF1E6BC7F0ULL, 
            0x05932377A4C92D29ULL, 0xE6B3F414F28AF3C3ULL, 0x7ECDBE83160B5C1CULL, 0x3F5F52DDB105D650ULL, 
            0x92F93B64D5BD0CDDULL, 0x960F86F3EC4C2B85ULL, 0xED19F2D2F885F2FFULL, 0x3B5F799CB8C7DB76ULL, 
            0x36B4E20E4152EEF7ULL, 0x65F77199A1657F40ULL, 0x68EBF4FB11894648ULL, 0x07516B93B509E895ULL, 
            0x990A98A66B359C8EULL, 0x0ED576CB80B55232ULL, 0x7748BED9E2C033B4ULL, 0xBEBBB3614894060EULL, 
            0x9333D6CC2A12DBEDULL, 0x222693449A85F158ULL, 0x260ECCB815AEE97DULL, 0xC3EA3793C3624668ULL
        },
        {
            0xD578FB8F0CC9E0BAULL, 0x6EB6541D534826CEULL, 0x01AB470D99E6F385ULL, 0xE73958C1049E73F2ULL, 
            0x0D242F99946D7916ULL, 0x7C461944822F458DULL, 0xFA4FD0B9E483FEF0ULL, 0x281C3E12E6514387ULL, 
            0x5435ABA100675340ULL, 0xC25F561973F614FEULL, 0x32A0A565295BAC2AULL, 0x47E7C79004431E2AULL, 
            0x655266FB30DDA3CDULL, 0xD599B57AB0132E1CULL, 0x91E972FF13401FA8ULL, 0x077C037D8421DEB2ULL, 
            0xEE042FE9F7CAC9CFULL, 0x5FC10836329F8BA6ULL, 0xBDF936A5A83BD6E2ULL, 0x1B56B62511FE89D6ULL, 
            0x30D12DEA8BBC087EULL, 0x00E77B8EC7438A33ULL, 0xB7D2ED75DB27F91AULL, 0xB4EE36AE3416C2E0ULL, 
            0x11E7927B8398D713ULL, 0x4E0083385D17BBDBULL, 0x04AE369C21F02B1DULL, 0x3377598E5EF49555ULL, 
            0x08CF346EB2EF94F1ULL, 0x89D84484F6590660ULL, 0x24E8F51742DEC5E1ULL, 0x8755D6F225C0B483ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseBConstants = {
    0xED657C81EDE17118ULL,
    0x3ECFA53ADDA05446ULL,
    0x8C5B817A6DDF95B1ULL,
    0xED657C81EDE17118ULL,
    0x3ECFA53ADDA05446ULL,
    0x8C5B817A6DDF95B1ULL,
    0x06E72C26267B2263ULL,
    0x5DDEE955ED3814A2ULL,
    0x8B,
    0xA7,
    0x96,
    0xA6,
    0x54,
    0x6D,
    0xD3,
    0xF0
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseCSalts = {
    {
        {
            0x4CE6E00DC95AF1EEULL, 0xDFB2677F8C7C3F75ULL, 0x08DC7D77730AAD7CULL, 0x3AF8A16389592EC1ULL, 
            0x48A7B43A504C478AULL, 0xC48329C8640A5637ULL, 0xD801EB8AB8358609ULL, 0x7CF9A441B61B9ED3ULL, 
            0x4587DD2F99866AC4ULL, 0xCE1333EC3AA2F45FULL, 0xF8D0157425D32CB8ULL, 0xE5190650921BAAAEULL, 
            0x7F8794127E3CD5D2ULL, 0x04564F18809526E9ULL, 0x0E2CAD53F44CA8FDULL, 0xF9D29544C440FC51ULL, 
            0x5458BA314A3E44E8ULL, 0x18818E3B8198EA6EULL, 0x1412C455B86791CBULL, 0x572B81AD86F039B8ULL, 
            0x19EFADFD8BF9FB44ULL, 0xA33A38F588B5C2C3ULL, 0x0BF8219E102339DBULL, 0x1CE8EEDAA1B6A195ULL, 
            0xA2EA37D5E9F770E9ULL, 0x4BC5702F2ACC88CEULL, 0xE34A6ACB3BBB497CULL, 0xEC707286870E6F4EULL, 
            0xB640ADFF74D8E4A7ULL, 0x51270A608578524EULL, 0xCE7C6D53BEE864DCULL, 0x8AB372A94C1F4DC3ULL
        },
        {
            0xC3639736D372BF1BULL, 0xAD6DF6F42EAE88A9ULL, 0xEF3CE1EB3214F3CDULL, 0x9BE3F4E721A73BDAULL, 
            0x6FF57C0BC3D2AEFCULL, 0x0EFAA25F0F2C60F0ULL, 0xB45E19C1FAFA70DAULL, 0xCF7D30943C6FC16CULL, 
            0x33BA8E05EEC77E23ULL, 0xE5C969BA030B1A22ULL, 0x516FD753A3C09D8CULL, 0x9BE9D2535ED418A4ULL, 
            0xAA4A59E93C44F1A9ULL, 0x7B61BE470DC211BFULL, 0xEAD7A7B253948DE4ULL, 0x5DFD7A8B58FC76A9ULL, 
            0x311ABEB8C7F51D7DULL, 0x6CC93940DB9E159AULL, 0xDCA9109A96EF3646ULL, 0xC1F8F46DE446F654ULL, 
            0x2D8C14AFC0034412ULL, 0x0D2C93FCFDDC182CULL, 0x0FD8D1F4030978A9ULL, 0x35D56B68F476F654ULL, 
            0x8BBE23931F2A2ECEULL, 0xFABC0399BD987406ULL, 0x1A637C9583051278ULL, 0x5457912773124744ULL, 
            0xDDCF852D08AA6B3AULL, 0x305487942F0256C4ULL, 0xF066CA1D0B53D754ULL, 0xF13530934EEF15B2ULL
        },
        {
            0xDC2C4973FC1EA11DULL, 0xE1C961DE1F5365A4ULL, 0x087FD8BDE45BA005ULL, 0xC471EA9FDA7DAE1FULL, 
            0xFB0F7D2BE07A59F3ULL, 0x763B96D7DA0B95A1ULL, 0xCDAA167205CADDC3ULL, 0x4883F65AF6743A48ULL, 
            0xB1F7C1E3B2FC5DACULL, 0xEE388AB1B0F6930FULL, 0x5C971598C89819D9ULL, 0x65018398AEEB77D3ULL, 
            0xA203DA2202B4D505ULL, 0x72BDD07B1BD29999ULL, 0xE1489AE5FBFFE665ULL, 0x5D31AF8A6D92D929ULL, 
            0x76AE6E5CAA6B3FDCULL, 0xF8F94C14D95DC034ULL, 0x6C5942D67E247083ULL, 0x0C4E5D032BC12E70ULL, 
            0xD5431B50BC3FB5ECULL, 0xDCD3DC6DC61F2F5AULL, 0xE02DD9A94480C996ULL, 0x970F44DE768B868FULL, 
            0x5DE24A0993CAC000ULL, 0x1C058FB44074264FULL, 0x2F9F8C7D98DC7872ULL, 0x7A4D9BE712D4D5FDULL, 
            0x1FF7707F71C75B4FULL, 0x7BC70099A25233E3ULL, 0x7564016E1D56BE32ULL, 0x3268790F4D4FE33BULL
        },
        {
            0xD0E674240E3D8284ULL, 0xE0C509161CB54886ULL, 0x035423058E8458AFULL, 0xFB2D4E5139860D83ULL, 
            0x10F7618465FBBE67ULL, 0x0C4E21E57DDBF482ULL, 0x7559BBC8BB55CED1ULL, 0xE1CF9D3D3F596F34ULL, 
            0x3362C99B0D8FCB21ULL, 0xE02730B2F962CEBCULL, 0x0B22306FE73F5412ULL, 0x1C34B4BE878DC77BULL, 
            0xCD45ED3695BB64AFULL, 0x6B3604E95932CF10ULL, 0x2258E8F9FD6182EEULL, 0x9BF876EC3FE2728FULL, 
            0xB13911342011D171ULL, 0xACB9B09F3C3061B4ULL, 0xEDF03308647F52FBULL, 0x7D5FD42685C3EBEDULL, 
            0x410696260A1339C2ULL, 0x7DAD63E33C90F155ULL, 0xCAD7FAE1D447A665ULL, 0x31D536C1BB6CE463ULL, 
            0x45EAA0B2B577DDFEULL, 0x29DF80BB682D85DBULL, 0x3334C164409D74D4ULL, 0x334EE57A63F9FAB3ULL, 
            0x492F3691651A87EFULL, 0xBDF98C01160A7AD1ULL, 0x413CC82AD77A3B9EULL, 0x2DA65FC6E6149149ULL
        },
        {
            0x2A4D894063B1F8B9ULL, 0xDFCE0914CE237B24ULL, 0x8B5DA8D6A18F64AAULL, 0xEBF8BCB32D3C0C14ULL, 
            0xC3721E7633B1CD19ULL, 0x4F916C71969CE92EULL, 0x866D2F09D87067EFULL, 0x834E762959FE4EE6ULL, 
            0xF569200E37CE9E08ULL, 0x612ED7AFC865A16AULL, 0x6CEE5BB706EAEF5BULL, 0xB920822C75DFF3E3ULL, 
            0xD71F7744664725ABULL, 0x9BB498D59BC45662ULL, 0x76CBC3755A692D5EULL, 0xDDD52393FF461FC4ULL, 
            0x4C80384A7B22F1BDULL, 0x5A205B7D33E30852ULL, 0x5CCB9E11D927C55DULL, 0xDA3F959777CD533FULL, 
            0xC26B030BB6DB820CULL, 0x84878F6219437EEFULL, 0x062536BAFB2F0DEEULL, 0xCF3475B257189C5AULL, 
            0x50E1C89A05701A78ULL, 0xCFC3200A8F263012ULL, 0x94FAABC0419CC63CULL, 0xB15A42B34C068EF5ULL, 
            0x2D5047C0FBB437EAULL, 0x924538065EB4CFDCULL, 0x8842A0B03AC0D12AULL, 0x1A615D1124CAE01FULL
        },
        {
            0xFC4EE076DE8D1ECFULL, 0xD01F69D8918EA343ULL, 0xBDAA2CAD137058F0ULL, 0xACEB9D7FB2282F08ULL, 
            0x2A344F35FF66DDCCULL, 0x1AF6DE06F2422CB3ULL, 0x0386C9DC13B309D8ULL, 0xC8655994F5C7D655ULL, 
            0xE73A6B9A5980B4D9ULL, 0x567F5F4F3CED82A8ULL, 0x5A9F329F7D2B576AULL, 0xCB5EB8AEF7DB2CF8ULL, 
            0xF77559F751E380F0ULL, 0x5FF56ED9BC21B38CULL, 0x2787C7EF90C5141EULL, 0x91A82A419017CA1FULL, 
            0xCF9F9D9A6FBF4601ULL, 0xB756322E52753AA6ULL, 0x7576707AC5625EB5ULL, 0xD261F45C1A9BF69FULL, 
            0xC469B1FA644B7FF1ULL, 0xB0A9366B2DA28F73ULL, 0x447E8800D9FD9FE2ULL, 0xA194970225D58D73ULL, 
            0x4EF7BC362CF682BCULL, 0x05D78F0F27CB3926ULL, 0x15B8898880FF57C9ULL, 0xA413CF26BA0FCF9AULL, 
            0x4A2B448BAA3E0962ULL, 0x049B8B1EA8E0B96DULL, 0x0AF3D02461A74BB3ULL, 0xD26B43EACD325ABCULL
        }
    },
    {
        {
            0x05CCDD93AFB46325ULL, 0x5865E3AE90D73EC6ULL, 0xB4ECC25F58BC5A62ULL, 0x2D4ED5028BCFC78DULL, 
            0x7BCF5A7867A23B74ULL, 0x09F9B69958C18010ULL, 0x59F08284BE9A8BA6ULL, 0x01EE5C4308F99AA0ULL, 
            0x7DEB1DBCE7DC77B8ULL, 0x2D8B87D3CE3FD409ULL, 0xBE8AD4C44F6E0C82ULL, 0x759F2A7D14E5739DULL, 
            0xE8510A5341D1E797ULL, 0xA3C3DE5FF002B548ULL, 0x966A1120D9FE9180ULL, 0x8F49FE57680F9FBBULL, 
            0x620584D7CFDEDFD7ULL, 0x1EE1661440D32DCDULL, 0xD006A39EC07BD55DULL, 0x1E198F0476D3D4D2ULL, 
            0x0428021E146C6E27ULL, 0x8067F27A53C5BA9EULL, 0x7B39830CD649D52FULL, 0xDD21E8F9C51F1AD8ULL, 
            0x0AAC17D0D64919C8ULL, 0x08D215CB16706943ULL, 0xD168C06970D2AFC7ULL, 0x6EC3EEF9857ABCA3ULL, 
            0x89C7D1E05D3044C9ULL, 0xE75A912058E7B23EULL, 0xA73EC0FADF726D03ULL, 0x2065EDCA45116350ULL
        },
        {
            0xB2A922CCF76F9606ULL, 0xE9D72F133A57E038ULL, 0x423D842048F55A30ULL, 0x4D01B981FD0617B9ULL, 
            0xA4DCD75D0C6D64E9ULL, 0x9F6D8EFBD258D290ULL, 0x9DC8EF84BC755AD4ULL, 0x10803531EFA700A6ULL, 
            0xA3781EDEA0DC1576ULL, 0x49823C8170D0FE64ULL, 0xD1D8AFEB2BAA128EULL, 0x219DB7DEE52460F9ULL, 
            0xB31591973BE9E91BULL, 0x20D27EB71510AC73ULL, 0xF630857002D0E3F7ULL, 0x78A1DB4677ED19B7ULL, 
            0x0134691D11893016ULL, 0x974A6E0E91A1BC50ULL, 0x64EFD69B2FA7B680ULL, 0x088FB2E2E1A173B8ULL, 
            0x82505E530DE4E745ULL, 0x60D4409C5CAB1289ULL, 0x82FB379B171CE89EULL, 0xAB93157FB6A5F9A8ULL, 
            0xA9EBEA62051F8C89ULL, 0xC414F94A8547AE68ULL, 0xE91B3AB73BCE9FADULL, 0xD17CC6EDA36B242EULL, 
            0x2D3CAFB65D0C27CEULL, 0xDF840BD91BCCA5B8ULL, 0xBB385651533C0858ULL, 0xD555C52CA054B888ULL
        },
        {
            0xFD28793066D95EFCULL, 0x1B5D07DBFCA2706EULL, 0x39FF7B9327E8DE63ULL, 0x69D3CFEA1DFA5B62ULL, 
            0x1E7C994C9D7D2746ULL, 0xAB5F770E8673F8FFULL, 0xE61457981BA1B565ULL, 0x621D2DF718352490ULL, 
            0x02C9EC6E3F62F424ULL, 0x8A2BCE8182C6046FULL, 0x5EB3CA38B078401BULL, 0x7A2F30B560D7BFB4ULL, 
            0xA3017DB070F6B40FULL, 0x270FBE4FC6B313AAULL, 0x1137DF96B5017442ULL, 0x01A53D7C9E8FB660ULL, 
            0x314959917335AF45ULL, 0x831268FFD7A8CD8EULL, 0xB618302F58B513A5ULL, 0x97D3977681EFE80CULL, 
            0x848ED179A9DACCE2ULL, 0x176CB3169185FEA4ULL, 0x5589C7232BE5B8ADULL, 0x8F631DA49225A0E4ULL, 
            0xC8A0A3DBD0D8D37CULL, 0x060180BFC3A6C87BULL, 0x46E4CE5964D48FA1ULL, 0xFBEA3372714083FFULL, 
            0xFCA24B2296E3A660ULL, 0xFB5A17B79ECA8513ULL, 0x517F5D615B2417D4ULL, 0xBD49E513B858176FULL
        },
        {
            0xD9D2B122076B7502ULL, 0x1D0844C8E8308F1AULL, 0xD39713CD209E124AULL, 0xFB4FB1CE64733FBFULL, 
            0x0FD4D0C8BC8C3D3DULL, 0x265CBE67BD94B53FULL, 0x7C2E18D9B638D156ULL, 0xA3053B2EE194607AULL, 
            0xCAAB4F27E58C9B5DULL, 0x406AF287474A4898ULL, 0x449EA70357949550ULL, 0x9782A9342A9770ECULL, 
            0x38B402BD3CA67D5AULL, 0xF160F8B5B3D0E3D0ULL, 0x1C916359BFDA4299ULL, 0xE32DF17AC60EC75BULL, 
            0x7BDFC418864A0243ULL, 0x73956C7A7400916CULL, 0x0977D51E2371116CULL, 0x38B3B0FEC07B74D5ULL, 
            0xBFAF21920EB5ABEDULL, 0x41D1BF0923DFD27FULL, 0x70BF936A553CF6F7ULL, 0x72AF3797C9599024ULL, 
            0xDFCCC3CF217A4F5AULL, 0xE24AD08B0131471FULL, 0x56607770369F045CULL, 0xE907D8F3E0A37DD7ULL, 
            0x30D2FD5969D17AFCULL, 0xCD87F7D47E09EC77ULL, 0xDA57ADDADD4476F6ULL, 0x210308E2F7A7C327ULL
        },
        {
            0x369B2E2913B0A22BULL, 0xE120499FCE495BADULL, 0x3A716F265BBF0611ULL, 0x9FE3BB89CE5B25F3ULL, 
            0x3DD53DB170FC7374ULL, 0xBB94CE0E2D414EAEULL, 0x6CD31074855F8E90ULL, 0xF9624C9CC3D36CF7ULL, 
            0xC1D6A229EFC66409ULL, 0x28F201BF645D69B4ULL, 0xDD247B2BFD2A837BULL, 0x1A3AF776B71BCAD6ULL, 
            0x057C8AC8519D988FULL, 0x827D92E7F0C1046FULL, 0xB28E5FA6658F3329ULL, 0x8BB2EE75CEC73726ULL, 
            0xE0C28366C18A8D98ULL, 0xB84C279D644BAFF2ULL, 0x74406BE4A1994E6DULL, 0x1F0495D3424DFE32ULL, 
            0x4DDAAD683B30BEADULL, 0x06CBE7DAF0ECEA06ULL, 0xBB1DA8256D865A1CULL, 0xBCA565487A2F5EE0ULL, 
            0x63614C189257B3C3ULL, 0xC9EB8191E3C50FD4ULL, 0xA5D8991D186B7F3BULL, 0xF925185D68FB5F33ULL, 
            0x3771974EF58023D5ULL, 0xEA4694BA90DFEB80ULL, 0x009792AD8DFC07D6ULL, 0xEE3258E808503FEEULL
        },
        {
            0x4A727D1C81D897CCULL, 0x0592E75F552056E1ULL, 0xD87BEC9A28782318ULL, 0x648D0BE8F237AC15ULL, 
            0xCA633FDCFB1565BAULL, 0xC41BC21C19A62BDFULL, 0x785DF7AF04A1B8E3ULL, 0x93108F223BEFA44EULL, 
            0x392DB6F7A8C29C36ULL, 0x52383E5139883E59ULL, 0x358512ABDB23EEDBULL, 0x36F3BAB4FDAA09F5ULL, 
            0xAE6845A95E42864DULL, 0x6B0913D8953108B7ULL, 0x904A680958171FD7ULL, 0xE28EDAB071759723ULL, 
            0xCDD080CD206E43CCULL, 0xBF879FAAB03BA68AULL, 0xF4F3BAA61FB76730ULL, 0x24E2579702543BDCULL, 
            0xD33A14586C46F907ULL, 0x5143B8F1ED4C84F2ULL, 0xBF2AF160A4BCCDA1ULL, 0xC4AEB23BEE4E131FULL, 
            0x3D92E81D9EE853DCULL, 0x8D949B51BABBB055ULL, 0x9EF000C29733C167ULL, 0xC5D3D5631362C5F0ULL, 
            0xC31D6D951253DC1FULL, 0xFF8DC0320AD143B2ULL, 0x0830FA3E3E745B40ULL, 0x705F7D761E754BC4ULL
        }
    },
    {
        {
            0x55B9CB914282D944ULL, 0xC412CB3A3D7E576BULL, 0xA6A3FF2AC6FDC265ULL, 0xD54905D6CAA849F5ULL, 
            0xB6055E08F233ABD5ULL, 0x50647AA78CB56002ULL, 0x5B7DD913B94ACDC2ULL, 0x063D23F47F965AE1ULL, 
            0x87B41824AF8615F5ULL, 0x37D55664C4A89149ULL, 0x6373DDC8CC86250BULL, 0xC046D4A02005423AULL, 
            0xF4ABAF71AE01854AULL, 0xA8C9A3EB56038315ULL, 0x1AB19BCB12B1ED28ULL, 0xD6DBDB28A9F0F9E2ULL, 
            0x525543EDF4C995B1ULL, 0x56C08C8A9DFA12D1ULL, 0x22F8A6844818D7C7ULL, 0x6801AD57D6A99757ULL, 
            0xE14B3C6C01ECA9E3ULL, 0x89D64BF623EBD309ULL, 0x8FE1F22EC66DB16FULL, 0xD86F2323B86800FFULL, 
            0x7CA0259F23101335ULL, 0x004D0F5B25C4BE19ULL, 0x5D322FE14A452D0DULL, 0xAB03E037AD642B84ULL, 
            0x0F7316E53AF3EEF4ULL, 0xF291795BBB0C7BA0ULL, 0xF4A2C2B2810FB414ULL, 0xD2750F4891D396E8ULL
        },
        {
            0x624BE93E744E6810ULL, 0xC3BA7418F8892639ULL, 0x6883DE023C4C10D2ULL, 0xA08225D01573829EULL, 
            0x26335ABBAB1A9DD6ULL, 0x16776B2C36531709ULL, 0x7CB19BC961F6EC5AULL, 0x37B7D552FC006D48ULL, 
            0xBC4C5B427F41BF1DULL, 0xC75538500CBEE5E4ULL, 0x7C1F9D4B1CB46380ULL, 0x31736DEA33ED46AEULL, 
            0xFE01DF8500B023C0ULL, 0x1805815C87DEA99FULL, 0xB9BA8C443FAC7677ULL, 0x517E2E05F478B2CCULL, 
            0x955A22538F884EB0ULL, 0xB1D2F67D96B3647CULL, 0xC4878323584E2BE2ULL, 0x11F97C9ED629DE5EULL, 
            0x98DC7CA971A71D8AULL, 0x6667B17CEAAEB02CULL, 0x42962F322B6EDC69ULL, 0x2F57F556DFADC8E1ULL, 
            0x4FFAE3A1F49DDB36ULL, 0xBA6492DAA60CC080ULL, 0xCEB9F4527B7AC336ULL, 0x63D8E79D2A563D6EULL, 
            0x0A5A152409B42E62ULL, 0xBF47A983FAFB91C1ULL, 0x1F1C3812B7021091ULL, 0xB1D30E2C615557A9ULL
        },
        {
            0x111CC7F9179D966BULL, 0x56CE6ECADE879236ULL, 0x385778722D6DDF3CULL, 0x9F654D7E158D5B72ULL, 
            0xD4812736349B59CEULL, 0x99AFAE09B1E2645AULL, 0x630EED1E1AAB8F9BULL, 0xEE1DA9F412413B47ULL, 
            0x185990B351E0CAAAULL, 0x8A1F79449AB2D8F1ULL, 0xB953552F50FECB04ULL, 0xBC352F8ABFF8EBB6ULL, 
            0x7495E6166DCB1BEEULL, 0x2C225422A399ADC7ULL, 0x2201264FEFF82F29ULL, 0x9426172474752E4CULL, 
            0x04F2E07B6C3575AAULL, 0x4265DD2B08669FB1ULL, 0xD7DCB8C63465E332ULL, 0x9D4FCBC8BF1B1C8AULL, 
            0xD0310210FBC289C7ULL, 0x263FFA1AC7ECE60BULL, 0xB88EEC441C1AB7BFULL, 0x1D7828ACBEF5E035ULL, 
            0x41A21C12F7B35217ULL, 0x1641EA3507DD9A43ULL, 0x75F0F375DE073C3BULL, 0x03E6249EA07B20D6ULL, 
            0x396027DB697B092FULL, 0x489F2428A5620A58ULL, 0x929AEF30446EF03DULL, 0x5B76267C841258DAULL
        },
        {
            0xDDA1C900C3AAB8F5ULL, 0x856204174796E787ULL, 0xAB3643EB68E09002ULL, 0x61D86D31C1C7D03FULL, 
            0x7A198DA28CA60DACULL, 0x72974B78E2702C18ULL, 0xC1B58BB8EA022B01ULL, 0x4B1E05117FFD7877ULL, 
            0xB04DC2DF7E166BFAULL, 0x0ABDD5A520D0EB0FULL, 0x9510C3494D7EBF73ULL, 0x002A37A84B0C4245ULL, 
            0x53678A8AE157E8B9ULL, 0x7665A86947C4ADE8ULL, 0x919DA0C0BC757EBBULL, 0x8AB7EE75068499CAULL, 
            0x3D4E015F6C93871BULL, 0x52B1B55E28D8F17AULL, 0x31014FFD8A8F34BDULL, 0xEFC438EA415F343CULL, 
            0x0C2E4B8C579A0279ULL, 0xEED1458C72013AE9ULL, 0x7FB691A54AB4F0C5ULL, 0xA147843DEC7BE756ULL, 
            0x30B1306F93EAF619ULL, 0x6110AF5ADDA183D5ULL, 0x209C674EE6971B17ULL, 0x71127340085649EEULL, 
            0xF3AC46292E14AF9FULL, 0x620C716F7D0BED61ULL, 0x3E1685A37D3FA1FDULL, 0xA54252A85846F92DULL
        },
        {
            0xB1787B0E1C7E333AULL, 0x32500E9F51784AE0ULL, 0x12D3E7A06DCACF45ULL, 0x4D2A87DBD8CFA7E8ULL, 
            0xCB4115B881A34944ULL, 0x332E73D92F528A74ULL, 0x196C007ECF06ED66ULL, 0x12FD84409EEAB830ULL, 
            0xCA980470923B12B9ULL, 0x6E19C305C5674756ULL, 0xA650611DF201FCB4ULL, 0x3AD2C2B8F8594562ULL, 
            0x4C67D22BD17A520DULL, 0xEF3F13D150AE862CULL, 0xBE77AC6B28F55090ULL, 0xA4288DD33EE60AB0ULL, 
            0xB7F444222D9735EBULL, 0x937860F7A575F874ULL, 0xAD74C6A0D4065BB1ULL, 0x2442A4AA23828A50ULL, 
            0x813793C3724F32E6ULL, 0x8A8D3C6C0F89C644ULL, 0x77B94BDD9855AD22ULL, 0xE599CA2CBD538C48ULL, 
            0xDF46BA4BC511B77AULL, 0xC4717B350BF71BCDULL, 0x461FA9B25C5550D7ULL, 0x62950BDF35A9C0A3ULL, 
            0x72144B4BB6CF6BC2ULL, 0xF95C7F0D1CA12685ULL, 0x09F712940DB6EE5EULL, 0x67EF768E6C3E3C1AULL
        },
        {
            0xA8C54D9B734BF43DULL, 0x658B55558018276EULL, 0x21A35AA80620296DULL, 0xE8237B7EB4B2A5A0ULL, 
            0x7099E9AF67B89DE4ULL, 0xEF19D0CE5CCD4EDFULL, 0x654CEA152F45B23CULL, 0x96471BC1F846BA77ULL, 
            0x2009EF7B5784FE13ULL, 0x20393B82F2E82D7DULL, 0x116B1128EA07700FULL, 0xE39328E15DA4AD9AULL, 
            0x942902549C298AA3ULL, 0x5CF5049E8A786E7FULL, 0x7F1EEF5AD10A8076ULL, 0xA61883A25FE764B2ULL, 
            0x96CF1C6B07BB51DFULL, 0xF5DE7CD26F473B72ULL, 0x3E561098DB0D96D6ULL, 0xEFC15B10BEC457E6ULL, 
            0x845CA9896B039F22ULL, 0xA46B53C4DFB6704FULL, 0x86050437C149ECA5ULL, 0x282643F5081AF077ULL, 
            0xA37EB1ADDFD319A7ULL, 0x564FC88E3E63EE58ULL, 0xACF8BACC8D2E3746ULL, 0xC0EA3D122D30B644ULL, 
            0x574FBC9A0F27D16AULL, 0x3A16A31F11F4C3CBULL, 0xFE22083CBCDEF8F0ULL, 0x6F0A4FFC750F9EA3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseCConstants = {
    0x111A9000C64E2C1DULL,
    0x06DC9573BE3048D2ULL,
    0x391901097DF682B2ULL,
    0x111A9000C64E2C1DULL,
    0x06DC9573BE3048D2ULL,
    0x391901097DF682B2ULL,
    0x0C7C71021EFD428FULL,
    0x58FA2F1830064DD3ULL,
    0xA6,
    0xB5,
    0x1A,
    0x1A,
    0x20,
    0x35,
    0x31,
    0xE5
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseDSalts = {
    {
        {
            0x0D408002621B299FULL, 0x9FB165541CADAAC3ULL, 0x795AFC243073D7DBULL, 0x3FFC05FC2E7FC074ULL, 
            0x8726B85CA7D81844ULL, 0x7A08CF847D7F54DFULL, 0x51752BDD590F1EBAULL, 0x64351054F7EDC745ULL, 
            0x7DFBF80458ADDABDULL, 0xA53434ED0EAA9714ULL, 0xB3CE931F91BFFAF0ULL, 0x0A78959A8B30CD15ULL, 
            0xC0DF89C9A99965B0ULL, 0x73401668A2BD1BFCULL, 0xBF172260B937C957ULL, 0x77403A7F4383CC2CULL, 
            0x1EE16BBFF896D8E7ULL, 0x07BD7D830A040985ULL, 0x7315B974E88F1797ULL, 0xD193022095BF407BULL, 
            0xDADD2DE87DCBC74EULL, 0x89EE0E561DB62334ULL, 0x8932CBB9CB8FBE10ULL, 0x229F0E5FC19A43EBULL, 
            0x5CB0DFD4EFB6EC5AULL, 0xBA31DB131873F19CULL, 0x207F08029D2FD9ABULL, 0xFA27C8D60C389784ULL, 
            0x689C3A20914FC4F6ULL, 0xA40076A4021C2D3CULL, 0xD3FAAED24F6F50B2ULL, 0xC24836EFFF8A14E7ULL
        },
        {
            0x51D5119E117D57EBULL, 0x5B22FF97AA181E58ULL, 0x3E5FF40D063F424EULL, 0x82B9F59E861642BAULL, 
            0x719F949E54396E30ULL, 0x13B368896475F3F9ULL, 0x66CB7A0AF14BE4ACULL, 0x7824164C33C1EED7ULL, 
            0x06698575EF1D245BULL, 0x80BA89E1F081C8EDULL, 0x568B9D2FD8DD53CCULL, 0x5579108152FE2B1BULL, 
            0xDFE02A3A38427D37ULL, 0xB6D90E850AE381C2ULL, 0xE465807C944DC428ULL, 0x9889B8322F9F0439ULL, 
            0xEDC0F0D38C63C08AULL, 0xEA205CA296B569FCULL, 0xA0228EFCAFDE1626ULL, 0xC5231ACAE93A1A55ULL, 
            0xB1E10DC8A97ECC10ULL, 0xD9B34B0D632B8D75ULL, 0x38B6699C4C4B7130ULL, 0x3BEBFFCC9E9D6F20ULL, 
            0xD78B6EEEAC3D0908ULL, 0x982BE66E891A2AD2ULL, 0xEE10401C8D6FFAADULL, 0x02FB0B50485A14B6ULL, 
            0x7008B46D38C69E09ULL, 0xD3EB0C7C1A268B8CULL, 0x8E908DB343A61728ULL, 0x14B1241A36277855ULL
        },
        {
            0x24645578EA58E31DULL, 0xF9235524F6BDD1C6ULL, 0x168FBBC3EF5E19F0ULL, 0x7A8FF525F5E26C14ULL, 
            0x42429FA97D11DA74ULL, 0x935D523F4E472A43ULL, 0x5E8F583BB34E4911ULL, 0xE9BA6BA18369EEC8ULL, 
            0x6C4A38CC19E03353ULL, 0xC955F67EBF65BE3CULL, 0x4C4FFCAF55FB90DBULL, 0xB5DA1BB652B983E0ULL, 
            0x176C2B9ACD7AA4F7ULL, 0x72A40BB410B73146ULL, 0xCCB8B5ECA940B65CULL, 0xAE3393F8A1C7CCEAULL, 
            0xF1BB69DE6A4E1788ULL, 0x1AED830CB6669B67ULL, 0xC4AA0C9E28349EE9ULL, 0x5913E30A8E573F96ULL, 
            0xD11EEF5124F8DC0CULL, 0x77BFC3C818B0E9DFULL, 0xBB77427921F23E85ULL, 0x5B73B1EFD1AFF87DULL, 
            0xFCFA1C891B5F43E0ULL, 0xAE64707F51F5D8CCULL, 0x702C80183E564B11ULL, 0x493C59947FCA6C10ULL, 
            0xB68D3A49EEB30C15ULL, 0x71EBF3894A2B1E56ULL, 0xF881732BB98B6C83ULL, 0x595E6BC2E943BF1DULL
        },
        {
            0xE068C928C2A8A4BEULL, 0x3D9152BBF0818FA9ULL, 0x2BA9ECC9718ED6D5ULL, 0xEE1D77821866EAEBULL, 
            0x446071D7B244117DULL, 0x33038A75F60B566BULL, 0x163D4418087A56A7ULL, 0x6AC50D914B263002ULL, 
            0x6E39A4ADA65CBD7FULL, 0x82D0A592B3624D2EULL, 0xCF7ABD933BF5F5D1ULL, 0x9C768C9373007E42ULL, 
            0xA8D5CDE702328D78ULL, 0x16EA03505D645018ULL, 0x3B97C293CD8632E6ULL, 0xC39A3999E91281DBULL, 
            0x5849A344C76DCF0EULL, 0x59EB6F517BB857DFULL, 0xFFADCD9D51039257ULL, 0x0708EED45769FC73ULL, 
            0x8B2E17B47D4A2148ULL, 0x8F1CD825C4CD9FE1ULL, 0xD23D072C6FA66C82ULL, 0x15DABE37F378B258ULL, 
            0x2C4AB762DF8C1135ULL, 0x5EC07ECC2A55678CULL, 0x9297A6DAA30F8C0BULL, 0x8FDB87DBF1BEFAB6ULL, 
            0xC8A73DAC1668107BULL, 0x6FE1EBD04963F6FBULL, 0xC6C5C1953C7A2EC7ULL, 0x59D229D836DE1BEDULL
        },
        {
            0x1F57A58F2CD40EECULL, 0xDDDF491CADB41DEBULL, 0xFDDC1243C2BD8F5EULL, 0x0D7FA53A40D7B32DULL, 
            0xAFB0B0E6C6C66821ULL, 0x9B4024DC35C0505FULL, 0x3E56964B546DBFCDULL, 0xBE4710E167ABC32BULL, 
            0xE9231D23551491A7ULL, 0x01DA15A1868C3173ULL, 0x35850528DDC0D39CULL, 0x9C79AEBB41A5BA3EULL, 
            0xE51FF723597C0D54ULL, 0xE8EAADB2D6D3A9E3ULL, 0x41F6ADD20D860307ULL, 0x4F672501BBFE6184ULL, 
            0x89391B9873BAB515ULL, 0x07D2F87D33814A0FULL, 0x8C2977F0A338DC0EULL, 0x5EBDE0486FB81B4AULL, 
            0xEA94847DD730A465ULL, 0x82EB1AEB90C3B836ULL, 0x62A7713CAADCD17EULL, 0x77A346D3BD39368AULL, 
            0x217EB5A029D979B8ULL, 0xD39993377495E988ULL, 0x71E8DD36CC41CE31ULL, 0x258D4819ED168681ULL, 
            0x80DA7A00F67EEE4BULL, 0x614962727589A0D0ULL, 0x45DFBBE8624681A1ULL, 0x82EA3A94767323FBULL
        },
        {
            0x960F858C6742073CULL, 0x30B9771B12C8DC20ULL, 0x7028FC2C76AC8201ULL, 0xCDE481E547B7E17CULL, 
            0x724F1DCBD2F8BA62ULL, 0x14B8623991E11E94ULL, 0xBF5A44BBADD9FD3FULL, 0x961E0A35FBE6AEEFULL, 
            0x6F118AAFB3EFB9DAULL, 0x502FF6877A4D03F6ULL, 0xDDBD4A55A6F12249ULL, 0x9015686D6BC6001DULL, 
            0xD38FF23D1C2B9243ULL, 0xB1E21CC5DED351B8ULL, 0x1779350945495421ULL, 0x1C8BCD40339C21E5ULL, 
            0x3B7BC10A5EF1DCA7ULL, 0xD427289AB591D740ULL, 0x95537C69689B654FULL, 0x5485405903CEB585ULL, 
            0x13E264A8790673A6ULL, 0x80573D3FA726BA99ULL, 0x9FCA019C7A88B0F0ULL, 0x3BDA37D8372EB4FAULL, 
            0xF2BD499983419E2CULL, 0x60075F6BDD36D3C6ULL, 0x105CE2365B806173ULL, 0x4A293518DAE01387ULL, 
            0xA6941C2AFC2CCA61ULL, 0xDBA2FF8E13EAAB3EULL, 0x8E6D38BE801CA234ULL, 0x143123EB5BF5AABDULL
        }
    },
    {
        {
            0xC16424B35B392FB0ULL, 0x5C1EE2A642BB13F5ULL, 0xFE7BF1FEE6CEDF15ULL, 0x8EE410CF6E7B7A20ULL, 
            0x521F738B77062B7CULL, 0x24792D95FE12F0E3ULL, 0x5F67938BBE838CEDULL, 0x21621872521A15B7ULL, 
            0x1A4637F3325EA90AULL, 0xF3C9E638725741E0ULL, 0xB7BAD0349715A231ULL, 0x07B26CE128F9090CULL, 
            0xC72B25D2E9407B98ULL, 0x3C0A2691C8EAACEDULL, 0x1569A8BD279E3B29ULL, 0x31FF00B946BEB58DULL, 
            0xD278F30D400CEEE8ULL, 0x31C8E52C39E4BAB2ULL, 0x7A5014D592FBF79FULL, 0x592EE8D2D0CAAA5CULL, 
            0x459FB567BC8AD7A3ULL, 0x7CA5CA847B4EA8F0ULL, 0xF3E29F0BCE20E4D8ULL, 0xBA757B944B36FB78ULL, 
            0x05371691C337A201ULL, 0x97636755C7AF2682ULL, 0xC163CFB40CE07600ULL, 0xA7731CFF67A5E822ULL, 
            0x6F4BDA02C61A1E4BULL, 0xBAEC87758466610FULL, 0x3BB5646725170333ULL, 0x08F17918F2C3E23AULL
        },
        {
            0x7EED4A24ACA07AA5ULL, 0xF91D722394F5544DULL, 0x4FCF24D3CD46BECAULL, 0xEB9AEEE31EBD88DDULL, 
            0x63AD310625C90AB2ULL, 0x23FEFD10A263B1FEULL, 0xA2D3B259321826B4ULL, 0xFA505B5693544F7EULL, 
            0xB2FF9AF241223AACULL, 0x9704DBBBC2B6398DULL, 0x9389661A029FE9A6ULL, 0x629A03CF5EECA64AULL, 
            0x0EECB16EFA532D9CULL, 0x2DB5266076DE81CAULL, 0x4E176C8124E91B5FULL, 0x71231EFCBED46C2BULL, 
            0x160D051B1FC63757ULL, 0x721F51AE4FDB0D5BULL, 0xD3F0F9FAD89010DCULL, 0x62DC0894476AD6FCULL, 
            0x4F4192756E1E5871ULL, 0x11C9C12AF8D3F65AULL, 0x5EAAB098C0DEB13FULL, 0x5802B5D8F4940C5FULL, 
            0xE07E106125B6F346ULL, 0x67D570DDBDCEADCAULL, 0xB5DE0FF5DD45186AULL, 0x5734B4402C9E3544ULL, 
            0x73844913659D62F0ULL, 0xF04221AF32AB8ADEULL, 0xEF6F9AEF1ABCA565ULL, 0xD6774C6A848A59EFULL
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
            0x3BE04C6DE30B7C4CULL, 0xB044344708A11CA5ULL, 0xC43A27C7D5BC2635ULL, 0x22456E8D7850652DULL, 
            0x8CE2DFDA67293A48ULL, 0xC1A3391360283FC2ULL, 0xF124BE8270D4D1CCULL, 0x89D6D8968847C7D7ULL, 
            0xC80725EBC3FFF065ULL, 0xB2503D90EBFA56CFULL, 0xFE9EE3E17460E327ULL, 0xAEF922BA9CED69BEULL, 
            0xE71D1A33AE4DB0B7ULL, 0xE70CE4732515544DULL, 0x5B918D6494E75F14ULL, 0x2D811B7130F07933ULL, 
            0xE535F518D81D1D8BULL, 0xB60F9C52ECDD94C9ULL, 0x33E9DD4069E1B0ADULL, 0x7604D2C22E2C227AULL, 
            0xD930BA4C6C0C6E87ULL, 0x5868FFF598F34EC7ULL, 0x0EC7380B43D2B9C9ULL, 0xC63014F5926F6DCAULL, 
            0xD1FB14893BB14D43ULL, 0x73604B64A291F433ULL, 0xFD6B7C88EA0EB80EULL, 0x480E8D2F44FB646CULL, 
            0x23DBCA95DFB3AE5FULL, 0x6A45968A3F61996DULL, 0xB8E3494BC23D74B4ULL, 0xD256C56A29B668FCULL
        },
        {
            0x510853EB8227C06BULL, 0xA88B0EF7B7A3CBF0ULL, 0xC7A7A1B36FF74FE6ULL, 0xC2EC995981B9A9C6ULL, 
            0x7578912327958B65ULL, 0x43F9B1542ECA0131ULL, 0x032E3C7AE43B2037ULL, 0xB5CACF18A1371A10ULL, 
            0xD03728358F5ADA6AULL, 0x3C95BCC14C5A706FULL, 0x3C93D8A0D2E02387ULL, 0xD79DD449472959E9ULL, 
            0x29C2C78C8E695F6EULL, 0x5D82B21992B36A4EULL, 0xE17AC6FABA6B6449ULL, 0x3B9B28D5023FB61DULL, 
            0x6BFBB0D71E9BE121ULL, 0x731E45B453DB4C85ULL, 0xED7E5462FDA050CFULL, 0x1B24CA8F0C94166FULL, 
            0xAE50130EFA15E0F7ULL, 0xE23554AA0003827AULL, 0x51C3D7E845865ACDULL, 0x6D7F44C2202F212EULL, 
            0x6AE8B2F6595BEB71ULL, 0x932FC4EEEB4EE62FULL, 0x96D97741337BEBDAULL, 0xD3DBCE299C0D5D32ULL, 
            0x10C349BCC1DB0501ULL, 0x3CFBCC0864976EAFULL, 0xF50AFC08ECDF87D5ULL, 0x27C23416364BB045ULL
        },
        {
            0x22203CD30A0DF4B6ULL, 0x5AB4BFF3E897257FULL, 0xE12F5CC69470032BULL, 0x71781687E3330605ULL, 
            0x7F4C658DF5AD9BA0ULL, 0x155613B5A8803F97ULL, 0x8E386F7E6115DF18ULL, 0x625FE17744FCFDF6ULL, 
            0xFD77F7AA9B9234A1ULL, 0xD35B87BB0F07FA49ULL, 0x58DA9579098E4480ULL, 0x4C67905DE2E375A5ULL, 
            0x7AEB8098F2FFE974ULL, 0x48F4A1BEA96BA3ACULL, 0x0E33319E7DD4837BULL, 0xD0FB688409734144ULL, 
            0x4409824B8DF32D1EULL, 0xD04EF5F7B2AE1263ULL, 0xA25C885EACDC4562ULL, 0x669F0F7D9272950BULL, 
            0xF63F9086B2F3C52BULL, 0x8C15D85349160979ULL, 0x743CEFB81B4CB70BULL, 0xBD1C618C73CE4204ULL, 
            0xF627D63C788EE4E4ULL, 0x6CB38BAFB6956C12ULL, 0x2960C8EF9356CC75ULL, 0x536F32EA6F49FA6CULL, 
            0x2F8B7E90E45F98B7ULL, 0x52A778BB6EAB8C58ULL, 0x93E8390E2E0FD0E5ULL, 0x68B448472B37CCC1ULL
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
            0xB90B382782D620C9ULL, 0xEDE2CF1223255BCEULL, 0x1D7C51633571B06FULL, 0x05A4273090F66244ULL, 
            0x464A2F0E9F8F7C5FULL, 0xFDC764375EE5066BULL, 0xB9C4BD356EBD9D34ULL, 0xABAAA5A54F2E1B5AULL, 
            0x974A1FF94F391B86ULL, 0xDE38BADE5354DD72ULL, 0x934B31540CE69699ULL, 0x28D48520DAC5F8D6ULL, 
            0xC676E695E2A0DEF7ULL, 0x8CB96C2301543161ULL, 0x0ABEF1746CB9E3B2ULL, 0x8096DD5A6D7A92D5ULL, 
            0x1B74D6BB73596B52ULL, 0xFB82BADF4EB262C3ULL, 0x0B5BABE8517FBA25ULL, 0x03FD0E684B5DE9EEULL, 
            0x65CE7C3C143741BFULL, 0x90571FF7C6983FE5ULL, 0x2E636A55086D8E6BULL, 0xAD1E098885973397ULL, 
            0x5C0B9F2638EFD82FULL, 0x1B6DD843C175990CULL, 0x4482515D820A8224ULL, 0x76432D07CB73CAE6ULL, 
            0xF1FC6F793504CD61ULL, 0xBFD2170BAD1C8CE4ULL, 0xF7368FC08A04B287ULL, 0xEF8FA59BCAEB7136ULL
        },
        {
            0x5D9887B0F02555CBULL, 0xFD192E136679B2CAULL, 0x489638CAC47EAA8DULL, 0x9B3615D78CDC47E7ULL, 
            0x96D295663A42063DULL, 0x7C1C3F0178FE33A6ULL, 0x968CBD68D4B9404DULL, 0x3D2400F71F6D69D0ULL, 
            0x0EDE2095DAB0F307ULL, 0x4CE055A0FDFD32B3ULL, 0xCD8008DC74F285D8ULL, 0x007D2F20BF1B4AC0ULL, 
            0xC667EEADEBE30862ULL, 0x00C0FDE044707B9AULL, 0xB710636217B5FC08ULL, 0xE6CC582FB0B0ECBEULL, 
            0x8DE8ABC0019CF9A7ULL, 0x3D2B8413F8EE6227ULL, 0x9E54AB44A71BD92EULL, 0x5A60D9EE2A92FEE3ULL, 
            0x16D7378FF3AEA793ULL, 0x8EFC6B38A88137B1ULL, 0x85A62CA1685A3139ULL, 0x4472E73A367EA8E9ULL, 
            0x902A19A410CD361CULL, 0x3FB3CDBF502C0A00ULL, 0x0C89FFC534DFB45AULL, 0xF46334C48AC04537ULL, 
            0x804D5F675F317A23ULL, 0xAFF22F331B232A11ULL, 0xF39FF259FDA95C5EULL, 0x15954E2F2BAAFE73ULL
        },
        {
            0x76761594BA83BC5BULL, 0x5B335C6965E36D30ULL, 0xB739FADDE7870BBDULL, 0x720DAFE992D938F5ULL, 
            0xFD2DBDDD6BE549F3ULL, 0x1B81A600F93ECACCULL, 0x0197623911812FDCULL, 0xB7E2347FD5C20D32ULL, 
            0x6B9DF51F904CCD45ULL, 0xA086ABCA4B8CB3E3ULL, 0xF3BA84128456655DULL, 0x302AA9F0945D379DULL, 
            0x2AD70D94CA5C15D8ULL, 0xFC06111A410DD747ULL, 0xFA61191C9FD6E0A0ULL, 0x34AAF7C190C58D00ULL, 
            0x39D964C11A05284BULL, 0x149A0D57D0B1846AULL, 0xFA1869AA65C0CD3EULL, 0xC94092D1B476EFE5ULL, 
            0x63792FB49DF21C80ULL, 0x1A4829519447D35BULL, 0xE656332B887A6325ULL, 0x0BE01B6F57E39F00ULL, 
            0x7D1AA338FA7E0118ULL, 0x08D05E6BCDE471B9ULL, 0x17E8D80D908B5802ULL, 0xADA31F4D3EB92B68ULL, 
            0xDD3A080E833B5F95ULL, 0x2A1ECEECD8EB18F4ULL, 0xCA3B8E2D7531750FULL, 0x8949865FCAD1C4EEULL
        },
        {
            0x6B95AEB7B8B30171ULL, 0xEFA3EC61F0654A64ULL, 0x6CFF23A54EAFC8F7ULL, 0x61CCFC060513E730ULL, 
            0xA0823352E21BEAE2ULL, 0x9F6FD5E5D01247A4ULL, 0x53DF78FF97429812ULL, 0x183F9CF5FC3BF8BAULL, 
            0x0EF2232423C79813ULL, 0xC12268DE044AB681ULL, 0x781F85889908A8ACULL, 0xFC6F4CCF78D2F691ULL, 
            0xB5F9D3206302073CULL, 0xE8EEA32D8D652B2DULL, 0x6504D4F8B040D9F7ULL, 0xD433CF2C635AB18EULL, 
            0xAE888DC2EC93CE9FULL, 0x965A4E91D4E6DDB5ULL, 0xE2FB5C3CC867101CULL, 0x92B70AD509967717ULL, 
            0x1844D8FAD2BE1811ULL, 0x4C483EDBB72CED01ULL, 0x0BC9A3F14012E7B2ULL, 0x2FA65CEB68C7FFA6ULL, 
            0x3E0BF41F79CCCD49ULL, 0x0E040B8DEC0EB332ULL, 0x7634D80D56C179A4ULL, 0x732745284B1BC130ULL, 
            0x641DE1EFB7C3A365ULL, 0xDE21EFF3DC64B510ULL, 0x49FC25FAEDBFC5D9ULL, 0x7D2D95459E8311DCULL
        },
        {
            0xA61F647C8D0D5305ULL, 0xC30F4429CA6D593CULL, 0x7582C0DEA39A6182ULL, 0x16EDD3C8495D0512ULL, 
            0x121CF1672B124E9EULL, 0xB08D54B1357DFF63ULL, 0x59C4B56045F3C4D0ULL, 0xD32FC54EBFF0A0C6ULL, 
            0xE7FBC863C1D13CC7ULL, 0x31CEF61EF476F5DCULL, 0xBCDA464708B58EE2ULL, 0x605782D882D5BC13ULL, 
            0x343B77888C9DC2EAULL, 0x8283737CDBFBB5C1ULL, 0xCF4DC9DD4FD15DA2ULL, 0xBBC8A95C326ACC37ULL, 
            0x6BA74D950C8CBE5BULL, 0x2A2390E49DF05C51ULL, 0xD83ED2EF4B470F86ULL, 0xEA4E3A068594C1A1ULL, 
            0x8C4A533E28C1665FULL, 0x943C81405B899CBEULL, 0x7FC68781393B5ACEULL, 0x1ACBA4B538C21B7DULL, 
            0xFDBCE5D3FD2B6184ULL, 0x2FAD462CCDC0A690ULL, 0x6955D6F795AFDAD3ULL, 0xA53763DBCE5AC812ULL, 
            0x2BB6B777C122447AULL, 0x995895FFED2B3C63ULL, 0xE6F18F176E11CA91ULL, 0xAB9BA80D64D1954BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseDConstants = {
    0x3C6C00CD5A496CD7ULL,
    0x6968BCB2A87E51C2ULL,
    0x98BA3485E97F8B92ULL,
    0x3C6C00CD5A496CD7ULL,
    0x6968BCB2A87E51C2ULL,
    0x98BA3485E97F8B92ULL,
    0xB2DA2B3B06E9E261ULL,
    0xE2C751E6468DFF59ULL,
    0x0D,
    0x35,
    0xE5,
    0xE1,
    0x77,
    0xE9,
    0x2A,
    0x78
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseESalts = {
    {
        {
            0x7A7F7B0FE30C0648ULL, 0x92D969B3DE29D00CULL, 0x8051403F896926E1ULL, 0xEB4A02F63A431163ULL, 
            0xDD2DE3F07F516526ULL, 0x21B346A8DFEF5DD3ULL, 0xA3F25AFFA3A6EF46ULL, 0x6F976FAAC594DE84ULL, 
            0x11883F7AE738E74EULL, 0x7E17B075CB526698ULL, 0xA51BF47383EC9258ULL, 0xAA93D390F79E9CE2ULL, 
            0x32D8ECBBBC1E0EE7ULL, 0xB7746D2A24E69FF6ULL, 0xD5EB13C39F9F7FB7ULL, 0x40B850EBDEEB513CULL, 
            0x3AA0DBDFAB98AF4FULL, 0xFAC46CFBC9D39DCBULL, 0xE4206B18E465C85FULL, 0xA0D56CD77FE5A2D7ULL, 
            0x097E318A36C622F9ULL, 0x2037B32001FA528FULL, 0xA768EAB7A7614D63ULL, 0x4E9BA46D043E80ABULL, 
            0x585FF7E8DDE646C9ULL, 0xCDB93038711824FEULL, 0x0F72E189386FF975ULL, 0xEF834D3E8B825E29ULL, 
            0x1C459161F5064260ULL, 0xF8EEF995DE02B02EULL, 0x4CEF5221B913617EULL, 0xB8B46F06B5A77205ULL
        },
        {
            0xC57A9F7E710E9BBEULL, 0x21B763ADF88A6EB6ULL, 0x0FB3686A15830402ULL, 0x44B8215C4967926BULL, 
            0x7FF86512A3C83970ULL, 0xCFA2FDF8F85C0E1EULL, 0x45F5336C5850201FULL, 0x4833C8EA087B10F2ULL, 
            0x5F9E9C0460F3706FULL, 0x78E7CD26F4FEFB4CULL, 0x9E9AA7D8BC1F9B29ULL, 0x2852192AAB96CAD1ULL, 
            0xFCB34480F055D478ULL, 0x9296BF6EEF9ED457ULL, 0x2A6ACB6B94F9ECD7ULL, 0x4D1F7E29E489F1D5ULL, 
            0xD98F5192620D81FCULL, 0xB25FC585FE3F9CA3ULL, 0x0198D8122FEAFF9AULL, 0x5CCD18993A546B76ULL, 
            0x2DC27E3E4A368B0EULL, 0xB9A230870B33D25EULL, 0x74588442B719388AULL, 0x42BBA4093967E9A8ULL, 
            0xA4349D3BFB0B83A6ULL, 0x459E7368597153BBULL, 0x1F9912EFF4030532ULL, 0xD858269166E2C813ULL, 
            0x1184EB172FF2CC3FULL, 0xC1FCAD586B42111FULL, 0xA920AD38C9A9BEC2ULL, 0xAF6F80D33D62B010ULL
        },
        {
            0x082DA8A070B2E0B2ULL, 0x21BD9EB041C490ECULL, 0xF3CAD2DAA061EE20ULL, 0x1F7ED35D8A44749DULL, 
            0x9C4DD090483B3B92ULL, 0x84A80B37B6951845ULL, 0x9D8806C493591829ULL, 0xC1C232327C8E3926ULL, 
            0x2C08295184E58FDBULL, 0x1BB77FC2FC744EFDULL, 0x873395BB64E00DBCULL, 0x73BCE5854271F3C4ULL, 
            0x858452A07FF6D466ULL, 0xAAD5EF81EE29273AULL, 0x4478BAB6C529CB0DULL, 0x28EDDB744201F0CFULL, 
            0xCF488AAAA11BF91CULL, 0x0C48218618C8378AULL, 0x699D60A8658A1FECULL, 0x6CC4452F8EE37E27ULL, 
            0x4861E26231F61363ULL, 0x51B29A6B28B45904ULL, 0x796D51086B4CE2B3ULL, 0xD6EDD4B23795168FULL, 
            0x908E1A69D60A44DBULL, 0xC85956CDA27C5314ULL, 0x183A99F1236A57FCULL, 0x755E9B97DA808B8EULL, 
            0xA0CF1D266249581BULL, 0xD374C5633AF333ABULL, 0x00A32018CD138F6FULL, 0x41B58316B73598FEULL
        },
        {
            0xD1303D40B89E5DC0ULL, 0x7D5FE89C48AA4582ULL, 0xD520F050692929D2ULL, 0x4A64E417E1AA3349ULL, 
            0x5CC0C6269EE2A19AULL, 0x85993E3F288967B9ULL, 0x4E8AC9C03F771BB5ULL, 0xFCC0DB6BADB9EAB5ULL, 
            0xBFA97CDCADAE3128ULL, 0x9778E2A86B773F76ULL, 0x716268B80442EB47ULL, 0x3D1C65B7D3E160B2ULL, 
            0xF247CEF17B67176AULL, 0x637A0A05E0E3C2EBULL, 0x45F17C8BDE049903ULL, 0x5FBD2ABC6D5849D9ULL, 
            0x901B0B3DB333E853ULL, 0x6748F684D8FFE7ABULL, 0xBA36868C0E7D8F9AULL, 0x44E087917E93F6E5ULL, 
            0x7D46451C9F98CB72ULL, 0x31AC63AE591E3B90ULL, 0x4A1A5E865A0D3901ULL, 0x1BC64C5C562E67DCULL, 
            0x52527EE615A9F20BULL, 0x89C43F9C2AA26C35ULL, 0x670531C66719EB3FULL, 0x703BA7647AF48A32ULL, 
            0x72B175D00C07FE1CULL, 0x39278224B8B70AF7ULL, 0xC3DD384D6E02E335ULL, 0x108862C1A3556B14ULL
        },
        {
            0x8B1623BE1DF71E5BULL, 0x646DDA3FB06BC5F5ULL, 0xDCEBD2FCD0CAB2F3ULL, 0x7371EB47B1FAA0D1ULL, 
            0x1DBB40594AF204D8ULL, 0x2A566CB6B0DBB3BAULL, 0x288946DAEDECB8C0ULL, 0x5370170B8F724D3EULL, 
            0x3B869E98743406D5ULL, 0x1890C65A808DB80AULL, 0xD3DB2F3C3BB528DDULL, 0xBC0C76437D5EE83FULL, 
            0x2C48C7868535ABABULL, 0xCD520BA5DFEBAE4CULL, 0x6C5B9910E3E7DC90ULL, 0x451D328063D29504ULL, 
            0x113B6003C6E0D854ULL, 0x84D5BBCF092A90F7ULL, 0x80037B6FCCE3DD0DULL, 0xE102EBC96429DAAFULL, 
            0x9CF2061282981E40ULL, 0x20CFE10D337B5041ULL, 0xB271ED56388937C9ULL, 0xD5BA804D88044367ULL, 
            0xB54B64E828C48678ULL, 0xA14A956A7D99FA4CULL, 0x4AC03C3FA709168DULL, 0xC54ED20E8A37D35BULL, 
            0xE26E66BC88CCDED7ULL, 0xA1189AF1603029CDULL, 0x477F2F7B88B91290ULL, 0xF260AACEC21C61AAULL
        },
        {
            0x4622F264735B83F9ULL, 0x93318D5096145316ULL, 0xE40B90882EC8125EULL, 0x81584552ACF9D07BULL, 
            0xD67BB7A41708CB68ULL, 0xE6EA3938934374B8ULL, 0xE2294F65156837A6ULL, 0x70B3ACCA36BBAF24ULL, 
            0x06BEF4583475C80AULL, 0x2C441949084F73A4ULL, 0x9B0DFFF7DD89DA47ULL, 0x3C46F04400ACB746ULL, 
            0x0CBB0955DC37024BULL, 0xA6D3D691ECD4BE6FULL, 0x14345079F1358520ULL, 0x6F3D1E75902FC1F8ULL, 
            0xC3EE461FC3E5D12EULL, 0x54ED88FEFB0D5CDAULL, 0xE9693C1ADB57C9E9ULL, 0x1E9D4B75B3E7A1C5ULL, 
            0xFE2E68B51FBC294EULL, 0x86E47CD776956A7EULL, 0x0672626EFE9E8054ULL, 0x9B1C53ECCF1F9F01ULL, 
            0x746CAAEE4964176FULL, 0x3302A088CE722E39ULL, 0xDFB284890251B8D4ULL, 0x9B729B9F6C5A8B3AULL, 
            0x942EEA7977326442ULL, 0xEBAACDFD1C98A748ULL, 0x6F2E15167E2D8483ULL, 0xF93ECBF4A58A9316ULL
        }
    },
    {
        {
            0xA6348DD2A1967628ULL, 0x9BFB49D78AC9E8E1ULL, 0x5A61CEB5EC29ECFEULL, 0x9DCDD1FACC3EF50EULL, 
            0x5D0092A8FFB62A3CULL, 0x64A9B37BBBBE1A55ULL, 0x21E00D841721D887ULL, 0x1DF3DC1D5A3F6335ULL, 
            0xE530605D71E84060ULL, 0xFB9204D2A309104BULL, 0x8C72240C2408185DULL, 0x7E1D7A2BCC426942ULL, 
            0xFC426D7A386F44EDULL, 0x1AB5716F7BF87039ULL, 0x96039DDF30BC737AULL, 0x4AF93DBCE181B9E6ULL, 
            0x7ADABC8C0D738BE4ULL, 0xF9882E415762D511ULL, 0xB54D9441099BA15DULL, 0x550610AA2718EEC3ULL, 
            0xC52AD58F85D3F992ULL, 0xD8D4A783C68B6577ULL, 0x22E8BA750387B65EULL, 0x13C6CE192D4C1DBEULL, 
            0x6E0F3CA9D91895CFULL, 0xAC117453A406F1ACULL, 0x28913B2A8C82CA12ULL, 0x5A0149D9A99B8BAEULL, 
            0x8E684D6D4B4B6028ULL, 0xECCB056902BF183CULL, 0xE2B1E2BB48E2B65FULL, 0xCA4048EC3C7DEDA2ULL
        },
        {
            0x0458FDA8A213F8F0ULL, 0x54B1B5F2AEA0AAF1ULL, 0x99DF53DC12754DC2ULL, 0x900CEEF4270DFECAULL, 
            0xD1425AD0DCEB60BCULL, 0xE78791EBBFD93074ULL, 0x4C5D7F1049C869E4ULL, 0x5EA4A6A5B0315D2BULL, 
            0x4D75ECF2EE246EFFULL, 0x4FADBD37F72C6657ULL, 0xE891531F2FBBC0A8ULL, 0x4D0153257C7005FFULL, 
            0xE2E1EC9CDD219A50ULL, 0xEC756BF04B5196F0ULL, 0x312D8B012D34AD6DULL, 0x028C1D8623B3C28AULL, 
            0xDEC01057D227DD5DULL, 0x904D7D9243E55E59ULL, 0x88E3D9978B0BD5B3ULL, 0x3D6854A15C274452ULL, 
            0x2887E2DD8D580605ULL, 0x796B1EDB44BF86CBULL, 0x2EA1B6D1F270DAC3ULL, 0x31A96B481FB8C614ULL, 
            0xE7DB77ECECF076BDULL, 0xE1C1ACD68E2A11F8ULL, 0xB65648674CD8269DULL, 0x87580E6CE9DD0149ULL, 
            0x65C5EDCC8F624CF5ULL, 0xE2586C7476B0BE89ULL, 0x26521D5E80439427ULL, 0x8235C02FB2C8394BULL
        },
        {
            0x6A88CEFCF5CF409AULL, 0xBB86137EB95ACDDFULL, 0x03E2065A29156A2CULL, 0xC0E56F7CA0EE776EULL, 
            0xDDCBC3ACA750CFCFULL, 0x30D2BA638EDB9A99ULL, 0xBEE9E9FD34207E80ULL, 0x3AEB1881167DEEFBULL, 
            0x2329296EEE37FC35ULL, 0xF4C747950BD08B4AULL, 0x944A5C3F5812B4DBULL, 0xF127FF7D9121CCBEULL, 
            0xA5CB068E902E513EULL, 0x3AD5114AF703448AULL, 0x77063E15FF48181FULL, 0x603F39EB90B01554ULL, 
            0xAB46CC3B20462846ULL, 0x789B4ADC6A75D080ULL, 0x7EBEEB2232CE5B56ULL, 0x224EF4626E95CE70ULL, 
            0x898927C1F352A7C0ULL, 0xD763EF4BD5F8BB03ULL, 0x204829B44A1D22CEULL, 0xE9768A49843D12A6ULL, 
            0xB0AB8BD0D3129CB9ULL, 0xCF683BC60802FA3AULL, 0xE9672CA4F10F5C93ULL, 0xE2E6DE1E6E281636ULL, 
            0x5E4C699F724D1BE2ULL, 0x48F756C062462802ULL, 0x128AB3697F053B8CULL, 0x955DE52DBC5B5999ULL
        },
        {
            0x5D5450060DE89C1DULL, 0x4A420F05A5A01675ULL, 0xABB3C184C3C6F103ULL, 0x12E5A938620D210CULL, 
            0x8CA7251096DD4C92ULL, 0xAA62676F65ACF5A4ULL, 0xF8AB5F56EF9570A9ULL, 0x90EAE445D0828D87ULL, 
            0x525C5D0DA88DCBD3ULL, 0xA0FE1035170C1D20ULL, 0xE8C5574676A46B38ULL, 0xCCA9A09291D78383ULL, 
            0x522C258056AC4BBBULL, 0x2A18490EEE8B5C2FULL, 0x9F4BDC82CFCCABDBULL, 0xB32C15B5F891147BULL, 
            0x7026E9F10BE622C4ULL, 0x0F7893AB9A6ACECCULL, 0x558BE885DEA23008ULL, 0x92C19C8375CD852DULL, 
            0xA121633EFFBD228CULL, 0x333121DEE72C222FULL, 0x28C5CC54F8DB72F4ULL, 0x9F6F2A4DD0CEC22DULL, 
            0x69F9EF5AFBBE7059ULL, 0xE1269A0307943DC2ULL, 0xDE077BF94F763AD6ULL, 0x725DC467FBD85FC3ULL, 
            0xABFA0B47344364C3ULL, 0x59D1F6CA405F13A3ULL, 0xAB742160A91D93BCULL, 0x92207F6429DE777CULL
        },
        {
            0xC9D3CEA5BC59E20AULL, 0x931217EC42D404A0ULL, 0x0DD41A84553AC080ULL, 0xB9C24B8BD079E20DULL, 
            0xE6574511A3E56A4AULL, 0x124D1E29D83490F8ULL, 0xFD1C041F3BFE33D3ULL, 0x67E2D113412805D9ULL, 
            0x063F384576D36946ULL, 0xC12122A008B9DCFAULL, 0x162A74720BEBAA0FULL, 0xF9F946017B942C11ULL, 
            0x363E7D98B47AF704ULL, 0xB4BBCBDAABF0E428ULL, 0x01219CC71D32F838ULL, 0x085EC4B5A49B4F30ULL, 
            0x5713F31E5F231800ULL, 0xBF56BC5541D617A3ULL, 0x07BCD03979CDBF3CULL, 0xE0E898E3BEBDD334ULL, 
            0xC791D3466345426FULL, 0x2F1B4C90B751802CULL, 0x7DBA19C0D313A836ULL, 0x994F2F7D57FABE95ULL, 
            0x9F3D683C84912CEDULL, 0x67A5FC80AD2385CEULL, 0x54C8DDC7F25F6CF4ULL, 0x8D6F9E4C8C180EAFULL, 
            0x77EDDC298BA4EC0DULL, 0x15CF6E23BE4E400EULL, 0x1B80FAE941583956ULL, 0x21B55ACBF2AC664CULL
        },
        {
            0x32F2AD5FA1ABCE66ULL, 0xB4DA0B01C7E89D4CULL, 0xA6378879DD06707EULL, 0xC3ED358918357C1FULL, 
            0xF82E3D50CDF2B76DULL, 0x5BE65DCC26E229EDULL, 0x38D22C3831E7D8DEULL, 0x677D726AC1498989ULL, 
            0x405B4E4F2EEC2603ULL, 0x24F7893C69588697ULL, 0x8027FEB10DB6B1BCULL, 0x956C7B06C8027E96ULL, 
            0xBAEFB52546948906ULL, 0xBFE29B7F1E57DB02ULL, 0x36BEE0378D197274ULL, 0x05240533BAE4A21EULL, 
            0xE7390E7FBC2DC242ULL, 0x64E185BF114C4A24ULL, 0x417541D7B028BCF7ULL, 0x1F920146CB7734F4ULL, 
            0x25E1539CB3C32DB7ULL, 0x92C9E4A2D544CBAFULL, 0xF2DB2EE73F3CD92DULL, 0xA3274FB22667D4CAULL, 
            0xD64FAFA025E0A49DULL, 0x102F7BC76B4DF8BEULL, 0x6FC310AF5EE6D7D6ULL, 0xF38D3A688E2A8EC6ULL, 
            0x00EE25EF6742DB13ULL, 0xF74A3DD5BCE502E6ULL, 0x22082C2BDD33551BULL, 0x0CE0409B4AB7D97AULL
        }
    },
    {
        {
            0xA83465F6645D462CULL, 0x5A9147FC2AC22317ULL, 0x84E0F412CB3ED845ULL, 0x25C9EE04D1A139C0ULL, 
            0xE5DD224B6C4D6CCBULL, 0x1D9C56C0CDC38618ULL, 0xD278EB7FA50D2CEAULL, 0xC8D176F9FC7390F6ULL, 
            0x3047AD730A2F165FULL, 0xC7AF0985B4A50076ULL, 0x0B748824AA3BE27BULL, 0xA8C75DE88DE8BE80ULL, 
            0x17FEA98270E9FD2BULL, 0x199BE29E9BA25D25ULL, 0x86627BB0150F2EBFULL, 0xA591E215BE43DE79ULL, 
            0x743E1CD6C1911349ULL, 0xEA216F679DBFACAFULL, 0x4517B6D9F519C524ULL, 0x9CB400B3EBEB92F3ULL, 
            0x839A86FAF942E2D5ULL, 0x47BA4A5BAE1AB7D8ULL, 0x8C0E9EA39BFEB6C3ULL, 0x6930F97277ABEBD1ULL, 
            0x83FFFF4E0CA2E372ULL, 0x3CCE5F14075DC04CULL, 0xA46602E882724D26ULL, 0xFB11F30F05F2D932ULL, 
            0x4DE36A0EAAA49517ULL, 0xC79A06C956950E66ULL, 0x2E1CB43EA84B62A0ULL, 0xD8FAD6E4DF9661B0ULL
        },
        {
            0x3893AB0110B378AFULL, 0x4DCAAA19AFB5B45AULL, 0x38BD82CD09F9172DULL, 0xAD2AA1588482ABC2ULL, 
            0xCA3FA51D884AD814ULL, 0x3070695AD8D41C37ULL, 0x1C8930C715FDE9ABULL, 0x3FFFD418D63698E3ULL, 
            0x7A5EE344E3DB66E9ULL, 0x4B970F1C75B91989ULL, 0x33CC1B5B86410C5CULL, 0xC71C1843C196F1F6ULL, 
            0x7C3AE710B6A322F8ULL, 0xBEFB6D1B9E2DD60BULL, 0xE2704D9837F7A045ULL, 0xE48C10906B6B15A3ULL, 
            0xF6EBEAC60702CF03ULL, 0xB87754A889D5951DULL, 0x2C71ADA004E9B9A2ULL, 0x065273BDDF353AFDULL, 
            0xDCA18BF8E12CDA0BULL, 0xF964B6ACAA96C8D9ULL, 0xA389412402ABEFA4ULL, 0x64F68B76EB49C5B1ULL, 
            0x72DADDCAA695FC91ULL, 0x54D5739B2A20F6A4ULL, 0xEEAB374247A33771ULL, 0x37EF00AFEEB0F85CULL, 
            0x204A3B5FD9C008B7ULL, 0x7C92DC010E0B0710ULL, 0x5CF17672C5E7D7FFULL, 0xB416BD57D2DE73C3ULL
        },
        {
            0x7903E97A17AFEE79ULL, 0xEC51E309D1F004EDULL, 0xCD39ECE293BEB612ULL, 0x0EDCB9E32123DF02ULL, 
            0x852A1929DA52940AULL, 0x6959F40A88ABF5B2ULL, 0x19D25CB86080F193ULL, 0x690BED159FB7E65AULL, 
            0x24BD037A10D2A93AULL, 0xD0EC2AF598393782ULL, 0xB0E59B97D77384BBULL, 0xDF555F2D1B85F049ULL, 
            0x382446F7623CEFECULL, 0x4D4DDF4ABA385A44ULL, 0xF52A8E10B81426B2ULL, 0xF3B9392259014F26ULL, 
            0xF339367EF4E8CA43ULL, 0x1DC93AF9A8EDDCFFULL, 0x9CB6E43E56C047E1ULL, 0x479630AF1F4860B2ULL, 
            0x5BAC91F654C8D15AULL, 0x4F45A9CCEA9465B9ULL, 0xEC138E03FC67DB7CULL, 0x40ED432929916A21ULL, 
            0xD1AF295EAADB3281ULL, 0x6363CDF91DBBE909ULL, 0x424EEB63DB6C93C3ULL, 0x22A8BC75667604C0ULL, 
            0x3EE83F01361A6D66ULL, 0xB6734686CB580EBDULL, 0x5333075AA30EF36BULL, 0xEC9DA464725A4F93ULL
        },
        {
            0x76AEB17E2EA48AC6ULL, 0x1244F4B08B5CF450ULL, 0x8D74AE372D12CDA5ULL, 0x7B7C4B468676FC94ULL, 
            0x225E9CA5BD89C2BAULL, 0x29EA0A22BB19ACF7ULL, 0xDF0E6F5C47D05EEEULL, 0xAFC5B73924747E4DULL, 
            0x372F90DEAADA864BULL, 0x5D9030AD38FEBA67ULL, 0x15441FFCD265BAB0ULL, 0x34FB0B5C84AFC800ULL, 
            0x22F065C9B66ADB25ULL, 0x5071CE5014194139ULL, 0x27C4F9616FAEDF37ULL, 0x49FF13011FB1C5F5ULL, 
            0x2FBFD8FAEFDF1DEBULL, 0x8E30C6C0CA249253ULL, 0x74C513381E71EE8EULL, 0x29CBD4290500F3ABULL, 
            0x417D44D8C96720C0ULL, 0x30757798851EDE45ULL, 0x7A36CB2DEE17DDD8ULL, 0x450E0525310AB2B8ULL, 
            0x1471974E15BC526DULL, 0x595230ABB0873738ULL, 0x5EB9B93DB7BDEFEDULL, 0xE2A20AD0E06BD15DULL, 
            0x3EEC5E3EBFBCFDA3ULL, 0x0B51FA695E6A0DABULL, 0xAF82612E96316F8CULL, 0x9E12CC84016248CEULL
        },
        {
            0xDA5ACEFBB90B6A39ULL, 0x15CDB7EE42102D3BULL, 0x20073CD1EB1ED93FULL, 0x0E9CC91A27CF24A3ULL, 
            0x6156FE6D7B508235ULL, 0xF98D8E15CB2059A9ULL, 0x45E60D374084CB50ULL, 0x1CC96F86BCB6BD02ULL, 
            0xE79EE69AF304CFDBULL, 0x3B8D00A298CF5FDBULL, 0xCC4CBDD608FBCF8EULL, 0xF043781C002F475AULL, 
            0x1BDBDF659792E9E3ULL, 0x8007C6EB9AD80F41ULL, 0x5392F23F26156CC8ULL, 0x78D3AA9A0A578C89ULL, 
            0xA4380D44BB3682AAULL, 0xB95D3658367ED075ULL, 0x2871C29F38EFB345ULL, 0x7A2D47189E9D7E62ULL, 
            0xE1F91880213CA508ULL, 0x31BB177C5709866DULL, 0x0F01F8F4432083D5ULL, 0xEE0A18F0A117BF56ULL, 
            0x4C659150EF12A583ULL, 0xACFB9772F62B3539ULL, 0xAA005C2C0F8F0D87ULL, 0xCD0BE5442EEB05A0ULL, 
            0xB9BA1B955CBF92DEULL, 0xEC1429054D18BF68ULL, 0xBA901F1DEC375032ULL, 0x2B4FB429FC51222BULL
        },
        {
            0x5CF772DE2086B169ULL, 0x6E9AB5D903426220ULL, 0x0FFF34ABC506C781ULL, 0xC49B97BF97D9E7E6ULL, 
            0x96D91CDAE34E9926ULL, 0x69E264FB5AA98F64ULL, 0xC1F941A37A541EC3ULL, 0x1109C86AF3F60CCEULL, 
            0x515D10AE7A1EBE60ULL, 0x8196DF8434F789D0ULL, 0x432F3FBDF60813CCULL, 0xB040803311DA2017ULL, 
            0xAEEEDFFE2B4F0141ULL, 0xE42D10F2A5D09E36ULL, 0x29D016563A33D6D0ULL, 0x784C23ECDAC06AC4ULL, 
            0xF9668D722F4EC309ULL, 0x4136B518CB210CF4ULL, 0x0AB7C64CC69A4BD9ULL, 0x10051A75F1324F9AULL, 
            0xEB49EDCD501506AAULL, 0x2D27043E81F9070DULL, 0xDD53CC764CEFC9D8ULL, 0xCEC18288FBA19C03ULL, 
            0xEBCDD5C0AC3AB0B2ULL, 0xB637F9AB360924DAULL, 0xA24BFB10E242A412ULL, 0xE072A102CE1C3A7FULL, 
            0x2A25E714F57B8BDAULL, 0x9855451520C6FAECULL, 0x501D9EF4D8967FA8ULL, 0x8A5AF7C02E8DB286ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseEConstants = {
    0xC54DDB3544A481FEULL,
    0xE78E7A204F99BDD9ULL,
    0xD28A18A58166C044ULL,
    0xC54DDB3544A481FEULL,
    0xE78E7A204F99BDD9ULL,
    0xD28A18A58166C044ULL,
    0x96EEE3DB7BE9219CULL,
    0xE271D28726301C9FULL,
    0x04,
    0x2C,
    0x97,
    0xB8,
    0xE2,
    0xC4,
    0x20,
    0x4F
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseFSalts = {
    {
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
            0x1466761D9CA6461AULL, 0x3EA1DC9C354C1762ULL, 0xB27FE5DB467D4A90ULL, 0xF9C4E0DA406CD96CULL, 
            0x5E3B34F0630EE496ULL, 0x12648A3332FD1DF5ULL, 0x05AAA08A89E08648ULL, 0x26DC2CAEEB3D7D85ULL, 
            0xB14A19BA71BD1BCEULL, 0xD82CC4D7A43378FFULL, 0x30294BA4DB07F89DULL, 0x1087C47A707A9CCFULL, 
            0x17448D5CE40EF899ULL, 0x1FEB91FCCE1DEB69ULL, 0x24DAA9C54E179412ULL, 0x9A2A9DB9537E4671ULL, 
            0xBCF5B11779C30B4DULL, 0x666A4910B8989EFDULL, 0xCA9A6122AA6640E5ULL, 0xF1CCEEF904452117ULL, 
            0x9DCBD85B454A0D07ULL, 0x2CA8D11BEFD9894DULL, 0x04189EF7485EB531ULL, 0x1331E8C2A9FF6FCDULL, 
            0x91178EEE24C9F220ULL, 0x90357A36F7EABD0DULL, 0xFCDA1376F096FB43ULL, 0x91FC32FB60D363C4ULL, 
            0x722FFC7E057C9D8AULL, 0x453196AD0A97E50AULL, 0x0F1303C715A3ECC0ULL, 0x597E4919CF150379ULL
        },
        {
            0x41CCCEEEF755A9FCULL, 0x73E906449161D306ULL, 0xDF274EE8D6A72701ULL, 0x89C00A4FD186AD11ULL, 
            0x1EB387F8B9DA893CULL, 0xEF9854F843AFE61FULL, 0x86072EA7FD18A4B8ULL, 0x4B850E85F04F69BFULL, 
            0x7ACFDD0C74A51A37ULL, 0xFB2ED01D60C792EFULL, 0xE2C35779AB91A1C6ULL, 0xD1F201473C0CD7A6ULL, 
            0x3194936CE6A9CF09ULL, 0x74CB3748C22D74CAULL, 0xFE5205DBCB942746ULL, 0x8686F419BF404B8AULL, 
            0x208FFB38BEC0704CULL, 0xEE5307BEE6A43F04ULL, 0x1C0B2261493643FBULL, 0x312C6BA9C3D1D54FULL, 
            0x51CB219B3F5B2301ULL, 0x1E0C51E5E374A0FEULL, 0x64155A8025C7004BULL, 0x884AE5595A5AB435ULL, 
            0xE7067EDC18C345A0ULL, 0xCD5D8A2039D87109ULL, 0xE16A9448194DC710ULL, 0x581BB79359FB3C54ULL, 
            0xE7FD6FA64265514BULL, 0x4B8DB8A8DA6797FEULL, 0xD727177F9CE3176BULL, 0x5141389FA774B889ULL
        },
        {
            0x0E366F980A845B23ULL, 0x03C491DCBE2CE9DDULL, 0xE73970E4F1718EB5ULL, 0xA87AD90099A022E4ULL, 
            0xC918BF90D989776FULL, 0x1F87F65C58B71806ULL, 0xBAE4BBCCA4082988ULL, 0x2236E12405CC94D2ULL, 
            0x35617FCA2802D133ULL, 0xFE3C5916FC8F056AULL, 0x4D07CF5F7EABDABBULL, 0xF473971CD058F0E5ULL, 
            0x4BF040A003564AD2ULL, 0x4493623E4823F0DEULL, 0x3E48BB730417A740ULL, 0xB4CF5652213DC25AULL, 
            0x61044B94172165F2ULL, 0xE076FBA1FEEC9ABEULL, 0xEF77BE3A27A84775ULL, 0xDFF8188BB9CE2B34ULL, 
            0x8961EFB1EE962BDAULL, 0xD6F9CB5F4265FBD7ULL, 0x0AAFBF371877D7FDULL, 0x2593EB23D3CAB3D4ULL, 
            0xFA86633DA383AF3AULL, 0x5CB5AEE6BF4DB60DULL, 0xD1F5D7B7E312C184ULL, 0x510B0CBA88D95672ULL, 
            0x3795D21C9D9151E7ULL, 0x9EC3E5198FFD41B8ULL, 0x52B478EB39B871CBULL, 0xEDD1FEDCB2E2605EULL
        },
        {
            0xB8B3D749EA227CDAULL, 0xCD8EF631CF14E240ULL, 0x45F32A58405B8FF6ULL, 0xD2899FB2AA4B7149ULL, 
            0x78BF4EA60EEA2EF1ULL, 0x03F88505C360AD23ULL, 0x018939E93EE684D6ULL, 0xE72ECF08FC8DC17BULL, 
            0x143509067367730FULL, 0x7637B0892BD62C02ULL, 0xB5C573B286C29D9DULL, 0x114C6062EB5BDAD1ULL, 
            0xBDF7F0DD0D70E8F0ULL, 0xE3695F6D76ADEF19ULL, 0x49BF17963F3A0B2CULL, 0xF2B875237AD6CA97ULL, 
            0x9DBF89DD79617067ULL, 0xCF549643A05AD338ULL, 0xB087E6424D74A2A5ULL, 0x827465838B55948DULL, 
            0xC8E3566297F97412ULL, 0xE22CA8EEF8E63415ULL, 0xE133E920A6392EFDULL, 0xCFDC2A4F03F136B7ULL, 
            0x1C0A85D239C3FDB0ULL, 0x2DE28B3E00CB3FEEULL, 0x4074A8D8E7E7AAACULL, 0x39D51277B888F2D7ULL, 
            0xCCFFA82117E742EEULL, 0x10BEA0F23A8AE481ULL, 0x9B0AE743401A2363ULL, 0x07A8120978A06003ULL
        },
        {
            0xADD8FDC257CF562DULL, 0x37915053F870BCF3ULL, 0x7F7D14F2C3BEF959ULL, 0xF256D705DE3CC3BFULL, 
            0x2CCDB12330911521ULL, 0x70E2E5805D44FD1EULL, 0x5508677CA5C57520ULL, 0xCC4235E2F87C9BC9ULL, 
            0xE16367704FA186B5ULL, 0xE2D85D368BD6261FULL, 0xAFB3807D21635A45ULL, 0x659F3E064350A65BULL, 
            0xFE9730A6EB719EB2ULL, 0x8AAD2C126F6A9F57ULL, 0xA2384056F2CC6DEEULL, 0xCCD95B1A6B63E03BULL, 
            0xA712F248458D5C6EULL, 0x8827F62AC50A3C77ULL, 0xBB7951ABDF1BA76EULL, 0x3925C2B5460EB9D5ULL, 
            0x0B5C30444A8D4AF4ULL, 0xC11753ECCAF47010ULL, 0xB76263990E6222E3ULL, 0xE024A50E09DD43DBULL, 
            0x21AB92D3B2205A28ULL, 0x0B38ACEC3F700EC4ULL, 0xC222E30A634E98F6ULL, 0x563E208E00655486ULL, 
            0x21A7408229A02114ULL, 0xAD71B1D82DFDA1ECULL, 0x4892C06CC59DC34AULL, 0xE3FBD82795AB5EF9ULL
        }
    },
    {
        {
            0x1FF31A969168B26EULL, 0x23CB4C2425F8131AULL, 0xC9C5885736E9A666ULL, 0x39611265A69ECD5EULL, 
            0xA0DFF8683890D029ULL, 0x82C744B1EBECDFC6ULL, 0x8AE6D6F0C2DBA988ULL, 0x986E08AE14810087ULL, 
            0x4D9CBFEEA1396324ULL, 0xAD2030F643DC1A34ULL, 0xB191F148B737FF52ULL, 0x708C630C41F262A4ULL, 
            0x38958FDED810D742ULL, 0xCE30BDCF722D6EB0ULL, 0xE8778CA01C25A4CDULL, 0xFF4AD54CDC46A23EULL, 
            0x020DD13C3D8D8261ULL, 0xB85591C3E3FDDBE7ULL, 0xDAFDB7DE1DBC205CULL, 0xFB043A3E96D80D9FULL, 
            0xF2D0AEECA13290D4ULL, 0x5F0E907B68F70194ULL, 0x385D04518889070EULL, 0xCA5FC9C7E3BA2679ULL, 
            0x4F121959A61C944DULL, 0xB988B49917B2CE4AULL, 0x0D3526138C471B1FULL, 0x74F39AB4620EDC3FULL, 
            0x8DD81171DD7A6833ULL, 0x339ADD7572658534ULL, 0x1828927A54042E4FULL, 0xAC8DF238F0049F2FULL
        },
        {
            0xD9615DACAF55E5D9ULL, 0x98F855082504A62DULL, 0x4630D13702D995C4ULL, 0xE9EF9C4CE85B3D9BULL, 
            0x3CE0193565A0619AULL, 0xE07B4B339ADF9D63ULL, 0x6A59EA6BA35D435EULL, 0x3F214D42E2AD897FULL, 
            0xDC5218A3B67EAA09ULL, 0x7910D0F55195E2E7ULL, 0xAD4E6F19DAE0ED50ULL, 0xC57A287F1FEBECB8ULL, 
            0x3FFFAD96413BFDC0ULL, 0xD5A777443EA9CC98ULL, 0xFA8ABC049E09104DULL, 0xA1DF938B3C499E20ULL, 
            0xB2693F475CAC8A10ULL, 0xEC5E6448B265783BULL, 0xEAF1425B9810FE18ULL, 0x322882D8FAE6D40FULL, 
            0xEBD3447E5BFF23E3ULL, 0xE405C61E183008C8ULL, 0x66A25AB5E1EA35DBULL, 0xDF71CC40A4798E7CULL, 
            0xEEE257FF88D176B5ULL, 0x1DC0AD9F040E797EULL, 0x82E44F377095E6C7ULL, 0xCA9416FDDCCA388BULL, 
            0xEC342EA141321BE6ULL, 0x0DF7E232DF128402ULL, 0x1EBB02AAC3B654D7ULL, 0xC6E7FB0FF5C0AE45ULL
        },
        {
            0xFFEE3EE0C14F3572ULL, 0x95E6840A5FBEB98AULL, 0x941EB19612785033ULL, 0xAC270F8A68555760ULL, 
            0xFD219FE7244F859CULL, 0xDC3981AAA0D47D41ULL, 0xF6A94C2276B0B7F0ULL, 0x779F6F2980E1A0BDULL, 
            0x3840AE3C437957EFULL, 0x91B8BDC54C78C9C6ULL, 0x69DF62D2CB5DD67FULL, 0x5AEFC1C51ECB1BB9ULL, 
            0x32C452DC05E0A0D3ULL, 0x5AC7A6AA360470E8ULL, 0xDCD06A2C8699EA83ULL, 0x348CA7C5EE2B24D1ULL, 
            0x1FB23D673DBD93F2ULL, 0x978D299FB1281D77ULL, 0xD6EA41FD4FA347ABULL, 0x367151088B06B0C6ULL, 
            0xDE86979E3D7A3DF2ULL, 0xB933862EE461EE57ULL, 0x0914BFC001884779ULL, 0x549D19579A982AF0ULL, 
            0x642F6B4494361C4BULL, 0xA1227F0A8C5F55FCULL, 0x7235C90515054498ULL, 0xE12638D59CCABB85ULL, 
            0xE74A766438F42D47ULL, 0x4E7765B7A7935B63ULL, 0x82C56B95F1C379CBULL, 0x99E152A77A3D1E4AULL
        },
        {
            0xA5AA96BDB7F0E769ULL, 0x33DC9E77274CDC39ULL, 0xCEA731413930ED63ULL, 0xA402110B283961B1ULL, 
            0x7D4F9C2BE86A32DAULL, 0x822E788A82C806C9ULL, 0xD72F2B499748DE24ULL, 0xC31326D35AE2B9E3ULL, 
            0x343B76FBA91298F4ULL, 0x7B6FBFCE0DFCA076ULL, 0x790EFF8A6CFCC128ULL, 0x115611B39FDAEAC8ULL, 
            0x8E8C49510D684A68ULL, 0x4847958835BEA80EULL, 0xB1FBB6DB30E22430ULL, 0x27A00824EC0457EBULL, 
            0x60D16E93EDEBFF84ULL, 0xAFBAB89B8BFAC62CULL, 0xE30A866A47A65FADULL, 0xC87FFB99D5D533F2ULL, 
            0x1B450231B995FD75ULL, 0xF30D5DFB7F3B71C0ULL, 0x95739E803C3DC701ULL, 0x6FFED17822366333ULL, 
            0x548D324A75AF4BCBULL, 0x57A7199F8FE4ED96ULL, 0xD83C40EC6F10FFC7ULL, 0xCFEEC91D19C80D22ULL, 
            0x9E27445711601849ULL, 0xB987CD557A9E57F4ULL, 0x9FB8631C8F2569E0ULL, 0xA2017C0045F3BA5CULL
        },
        {
            0xE49B7D68FB615175ULL, 0x46C8DBEA2A5918BAULL, 0xDD9D60F9BD38B0D1ULL, 0xECDCE81FAB40A950ULL, 
            0xD90E40D34C2ADB1FULL, 0x848C4CB01105B6CBULL, 0x1832A588103D920DULL, 0x383FE1E9F451D2D7ULL, 
            0xAC270CD3F400045CULL, 0xAA9B07980E21BAC9ULL, 0xBACD443B1F9177A1ULL, 0xB05D9E226593D39EULL, 
            0x134261752BBDD23FULL, 0x59E283B9766E004AULL, 0x2BAA392D7EB46A49ULL, 0x1C4BE366F93C4581ULL, 
            0xFCAE6E311E8C514CULL, 0xCAE602FB97342C8FULL, 0x8AE1FD3835910A23ULL, 0x9BB2ADB51865AA16ULL, 
            0x94234E31E0C12D57ULL, 0xE914942F7EA20185ULL, 0x2714BEFAFE0CB2A6ULL, 0x61D137FA5BD1FF9FULL, 
            0x55EEBC274841E643ULL, 0xDBC42B3ABB302DA5ULL, 0x14F69DD1DE8CFD2AULL, 0xBCF2CF95D00C914AULL, 
            0x75160403B125DBAEULL, 0x61A8179F499508C7ULL, 0xABEEF4F9676C986BULL, 0x02EAB9B326141090ULL
        },
        {
            0xBD2C681C700995C4ULL, 0x4B61F2B930C87B08ULL, 0x7B7585E7180EE24FULL, 0xD246AE3151B19E12ULL, 
            0xAE21B08F3B7125E2ULL, 0xDD62D1BD1A97B855ULL, 0x9B3ECE47ECFD80D6ULL, 0x1ACC7E19121F03D6ULL, 
            0x53C3143AD06BDC9BULL, 0x4D1059A88D61576DULL, 0xD36C47416AC03BAEULL, 0x8C8AEF15F52EE7B6ULL, 
            0x81C85A2B046AD60AULL, 0xC80A02CC00D5A6F9ULL, 0xAFF2E756FC6FFA4EULL, 0x63B40D42CFAA6945ULL, 
            0x8FBEF05F77BED43BULL, 0x11B22A452E71401BULL, 0x0F2F283582E5C48BULL, 0x2023B89C04010D73ULL, 
            0x5DFC82F0D5C18D76ULL, 0x12FA5FD3CCD9ACD8ULL, 0xB2D9110C7D605B0CULL, 0x7102CFDED92562CEULL, 
            0x42547A97FBBAC1F4ULL, 0x1F84B6AC14C5F01DULL, 0xA86C8CCF53589B8FULL, 0x51A29434233196F7ULL, 
            0xCD33B313C40286DDULL, 0x76ABA74279A5218AULL, 0xE5D8C7644D27A01FULL, 0xA4E1CFC33A8FBB37ULL
        }
    },
    {
        {
            0xD5E4AFFE33B78AE4ULL, 0x4DD62B5E2AB1F767ULL, 0xD351900D134BD07EULL, 0x86AD7ECADC6BFE4BULL, 
            0xAD29C1EEB8F6A5B2ULL, 0x0C72F83CD1431408ULL, 0xDAEBFD2E9F78B5CDULL, 0x0ECBDC2C80CE30B7ULL, 
            0xC6F04A57B8D9C3B9ULL, 0x340EAD03295E9302ULL, 0x2B84868C04B60969ULL, 0xEA60F488CE61EBA1ULL, 
            0xD7234E6C659FC3CAULL, 0x6138D884C9E86DE9ULL, 0xEDEFAE64C4E8438AULL, 0x0CD971F4440FD0B3ULL, 
            0x78DE529B7DC918BDULL, 0x55F1FE594B36157CULL, 0x93DDFAD2C390FA10ULL, 0x0356CAE9F66BE8B4ULL, 
            0x0C54A99EC8488CFBULL, 0x24BD6910B0542F4CULL, 0x2804DF2237E4C721ULL, 0x00E264A395047807ULL, 
            0x2F41D54CEDB6C27AULL, 0x6DF63FE8CCA8B6CBULL, 0xA6B3BFBD96FFF2AFULL, 0x1EAC5D343994A70FULL, 
            0xB91B16FEC12E069AULL, 0xB4358AC7B491C306ULL, 0xFD8AD1CBD5C53089ULL, 0xF24FDB1025F2F819ULL
        },
        {
            0xA1E9B8DBA169E61EULL, 0x3A9E33E65797AE5BULL, 0x80BFDD3D1F9BDD44ULL, 0x608415F726064206ULL, 
            0xBA3F970BA21F5E11ULL, 0x6D32286CBF251257ULL, 0xB933AF508ADA7211ULL, 0x4E45E3E79B2EE69AULL, 
            0x12A6E06B997C254FULL, 0x45F566F5E0E46F96ULL, 0xA67BB296DCC972BDULL, 0x22992E6A6BFCC633ULL, 
            0x7BD13E8B20712CD6ULL, 0x2275C6BEB936C9F8ULL, 0x169024F516FF4C79ULL, 0x62EB6CA73CE0FE2CULL, 
            0xA4011429E973BB6CULL, 0xA75624DAA11B5377ULL, 0x1DA392F9AEDB7447ULL, 0xF2D59DDFB20AE7BAULL, 
            0x5AF8B1FC44C60B42ULL, 0x8C78FA8FB10B00EAULL, 0x67FBCEF7038B16EFULL, 0xD2C778728B04958CULL, 
            0x74095CCCF64FE6E9ULL, 0x70A9A9F15DE81F70ULL, 0x8B4225C6B375A8F9ULL, 0xE3123E242E07EB5DULL, 
            0x57522755681E901AULL, 0xB199F141A70F1397ULL, 0x011D6F7C5CFAF515ULL, 0x544B23DA7B29E811ULL
        },
        {
            0x5733CD32C05769F5ULL, 0x53A2D0B5F033BB9DULL, 0x13840EEA9CE318A6ULL, 0x104BAF901E6A93F7ULL, 
            0x50C4A3C729A12649ULL, 0x14592F2762ABA4E1ULL, 0x45B1ACB2635BA9E8ULL, 0xB81A20DC198D18F8ULL, 
            0x2834EEF35435F628ULL, 0xB0921623F6A29672ULL, 0x310470BD90737946ULL, 0x9BA8120AEA05F1B0ULL, 
            0x3FCFE6351314FD86ULL, 0x96541531CD3213DCULL, 0x63FD5926DD3614C5ULL, 0x39C2657AB7E5C080ULL, 
            0xB3B593767015AA80ULL, 0x858EBD2D95932D34ULL, 0xFFFEE355CECFA914ULL, 0xCF3C0FF859901F49ULL, 
            0x23AC90B3F98DB7DAULL, 0x555ADEA7E0021AADULL, 0xAB840C4E0BF9326AULL, 0xFC192A0270E6710AULL, 
            0x6DF68B996840DFD9ULL, 0x89F638040E73F260ULL, 0x2830D1660112298EULL, 0x93F0BEEF8DDE154EULL, 
            0x426AD991F9A9151CULL, 0xE603C5DF46624D3EULL, 0x4DEE7D3722DCF1E5ULL, 0xF4F8F827EF221F1AULL
        },
        {
            0x80C645CD87487F66ULL, 0x18549F396F635077ULL, 0x1A2A52229395ED91ULL, 0xDECE0CCC9C5C3FCAULL, 
            0x8BD3AB1613AC7AAFULL, 0xC7FCD47D9721B91EULL, 0xE4BCFD03D1DF6FC6ULL, 0x891628812B973CF7ULL, 
            0x235007F660815FA6ULL, 0xE71A5B12694C61F4ULL, 0x1B84DCB9CC1A11C8ULL, 0xB934401DAE7AB6B1ULL, 
            0xF1BADBE92B67ACD1ULL, 0x7AB13168C7C57E11ULL, 0x2D2597E5415873AEULL, 0x770523718307F666ULL, 
            0xAB8496D002D2749BULL, 0x36B097F0DBB6C538ULL, 0x98ED0E9D5C561679ULL, 0x432B8F9E61601DCFULL, 
            0xD1267F965D9DFDCDULL, 0x3F5722F9CFBF84C0ULL, 0x00AF8E48AB9180AEULL, 0xB982FF33692D1B3AULL, 
            0x8F95A93D2C046ACFULL, 0xD682E8F0645B4F52ULL, 0x8FE0069D836865EBULL, 0x20C29A6507007B1DULL, 
            0xE8710CF8A3EEFEDEULL, 0x50A88AC79D1E580FULL, 0x033989352E991546ULL, 0x057EEFA888ADA786ULL
        },
        {
            0x4B931F4ADD4D3D29ULL, 0xB373CC661D857422ULL, 0x57EC18521BEDF31AULL, 0xBB0F116CF8C86E43ULL, 
            0xADC0C39E554E4C52ULL, 0x61945EE861E553DCULL, 0xC73FAE8DAC43FF8CULL, 0x4C37535DAACFA7DAULL, 
            0xFDE81F6642F012D0ULL, 0xCA9C7526E31B246DULL, 0x787EB114BBF85CBDULL, 0xBCBD2AC817AC35E6ULL, 
            0x4A80B2A357254547ULL, 0x5A70EE5190CE45E7ULL, 0x2F80F8BD2AFD052FULL, 0xDA147A6BDE1A7AD0ULL, 
            0xF136A2F3CE9797D5ULL, 0x0FE2470392D802F8ULL, 0xE34660161E5335BAULL, 0xAFDEB2BAA5B54D3CULL, 
            0x38CCF756FC4A42DDULL, 0xDEBC945CFE6195DDULL, 0x18FF5EA29C929EB4ULL, 0x866E77667D1D2B70ULL, 
            0xD656474E17D791E9ULL, 0xC42D634A94392A92ULL, 0x1E51CF5965C3AA73ULL, 0x6967AE1B3F902E49ULL, 
            0x3A5078A5A7478FB8ULL, 0x6AB5D9B68FBD4FDDULL, 0x8AB1C710EDC308BDULL, 0x7158006FF450A3EEULL
        },
        {
            0x7718BB817D6045CCULL, 0x3F8AE8D7586B936FULL, 0x3494C31248F8C0D6ULL, 0x34EE33803BD37CEAULL, 
            0x31C7216EE0939977ULL, 0xD1A157020EBD77F6ULL, 0x93942CA9B3C360DAULL, 0xC1C72BB7A6D8471BULL, 
            0xD3CB21F6BF2CC246ULL, 0x0F5325D29E9797F0ULL, 0x3D64F818C5B76416ULL, 0xEC6423F56FC7E017ULL, 
            0xE1D677B5DED17974ULL, 0xD54556C434F5E749ULL, 0x1DA17018D93C50C5ULL, 0x3FFD3487DC9C7B5EULL, 
            0xF0AAEB20B2823FB9ULL, 0x72D323F8025EE8E2ULL, 0x31A6EAC01201148BULL, 0x90B2735889D4D073ULL, 
            0x7A43066D1B3F799AULL, 0x8C16855AB59C89C8ULL, 0xF0EED34DFE4BA406ULL, 0x7476332A791E3CF9ULL, 
            0x10EC81358DE896E4ULL, 0x210890B7B377F337ULL, 0xF1486450FAEE7E47ULL, 0x85370B48768B529EULL, 
            0xF0636367BA7281EDULL, 0x668C4E7AAE2199FEULL, 0x195060877CFF943EULL, 0x8274DD9774B4AF07ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseFConstants = {
    0x7E46F0083687D5B8ULL,
    0x47C3A3D4B1188B66ULL,
    0x13F743D12E771E04ULL,
    0x7E46F0083687D5B8ULL,
    0x47C3A3D4B1188B66ULL,
    0x13F743D12E771E04ULL,
    0x887937DAD00FE8CBULL,
    0x9CFBC9F55604CCE9ULL,
    0xC7,
    0x48,
    0xB2,
    0x8D,
    0x2D,
    0x0A,
    0x0C,
    0x10
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseGSalts = {
    {
        {
            0x846D51769BB73E42ULL, 0x586A4C6448FC6D8BULL, 0x2F31B55C640B71FEULL, 0xFF4920130D98CF13ULL, 
            0xFE2BF098FE5C88D2ULL, 0xF99B3BEBBBFF2D30ULL, 0x404546E98E9CDAC3ULL, 0xF73D824ACA069D56ULL, 
            0x0C6D312DD23FCFE9ULL, 0xF57502C975B54B77ULL, 0x376B861AA731B65BULL, 0xE09FFA48910E4904ULL, 
            0xEB6541B32AFC7B29ULL, 0xFE7D846562CD2B6FULL, 0xDA63A077AD7A6C6FULL, 0xEED90917BCDCCE63ULL, 
            0x211D1FAC61D7A64FULL, 0x143DCE80194CCA64ULL, 0x2C1086D51F5EF034ULL, 0x1515125F263D3E7EULL, 
            0x16AEE9EA63C76E6AULL, 0x0F56E76A69463E43ULL, 0xD50C81E3864618D8ULL, 0xC5A2477E1341C4C6ULL, 
            0xDF6DE09BE4DDF821ULL, 0xB4E6C044EF49A55EULL, 0x1F90888AAB51A1C1ULL, 0xA4F1AF13D280CBBFULL, 
            0x1A1ACBEF16CC0D69ULL, 0x1714C398E9D07268ULL, 0x71706823F1472099ULL, 0xB05A46A84EC7896BULL
        },
        {
            0x3354AE351C172E8AULL, 0xFD82C99FA799A0B8ULL, 0xD5604C14706193B8ULL, 0x9B76DF4A5D50B706ULL, 
            0xD4E183A288B577F8ULL, 0x1E7A6AE3A96C0148ULL, 0x80AFD40DB99D1EF5ULL, 0x3B0897DD56138EB2ULL, 
            0xE19911420713DA33ULL, 0xCABF82CBF1487B9CULL, 0xD8BB28B416AB195FULL, 0x5E27FB94AAA93CCFULL, 
            0x2997DB1B3746B9E9ULL, 0x86A724D3B26223EAULL, 0x7E0A9BB6A9E0B7C3ULL, 0x3868274B9480B0F7ULL, 
            0xEFA8CF6AC336D887ULL, 0xF469C62971FA28F9ULL, 0x71B8E6E8C0158732ULL, 0x129476FED7A8E312ULL, 
            0x4CEE15ABF68AFB22ULL, 0x6EAFFD2A6CF30542ULL, 0xD3C515ACB4E98B04ULL, 0x0DF5C78AFC2693F6ULL, 
            0xCA6B206422A17F0DULL, 0xC0119A5B533C6C3CULL, 0xFF57B380EA652540ULL, 0x3A8FD9BF8BEEB20BULL, 
            0x3E88FD8F7992C052ULL, 0x8FA6E2F4782523BCULL, 0x765B548D4E5F537FULL, 0x8DCDD4A9A3DFBE40ULL
        },
        {
            0x5469C07F88450D01ULL, 0xB8E8EAAB02F385F9ULL, 0x44DDA214ADD9AFD1ULL, 0xD50FD28B724F397EULL, 
            0xC8295010B03805C1ULL, 0xD6BA02BFC6F1FC07ULL, 0x45B2CF816E884913ULL, 0x401ED430359B44A9ULL, 
            0xCA419A181A1F81B7ULL, 0x5795E368B9FE5EEDULL, 0x504FB767D98394ECULL, 0x0014B013A41FAA69ULL, 
            0xB9C104298F693486ULL, 0x3C69F6F95860934AULL, 0x1A9457DC43137603ULL, 0x3D5BBFB305D2B017ULL, 
            0x4E512787BE74468CULL, 0xCCE959F45EF4D54CULL, 0x9011BDE439C6B23FULL, 0x70884A15CF5B23E3ULL, 
            0xD09C99E746D9854EULL, 0xBD60B8A7E91EE71FULL, 0xCE409AD985E708ECULL, 0x66E80664919626B2ULL, 
            0x2CBCE73C786D3A3AULL, 0x6BE60893303E9024ULL, 0x501309762F5A5D6CULL, 0x1DBA846C598D5A37ULL, 
            0x0E6FD5E5F1A02975ULL, 0x85F56ED306370A96ULL, 0x255F16C7C5CBF1B9ULL, 0x02C0B8105141AD18ULL
        },
        {
            0x17E3720CBCFA8AEBULL, 0x64E355A95F96000AULL, 0xC08C48863E800470ULL, 0xBC0C13FBC3F259D7ULL, 
            0x58D6C4D5110126ACULL, 0xC9F07751E492CCA1ULL, 0xFB4DC7D14A4C0D2DULL, 0x1A05B1CD98C088A7ULL, 
            0x6A1D0242D72A0F66ULL, 0x58C63A2F4824535DULL, 0xC6F8DE1453DF42CDULL, 0x3884215EAD9943D7ULL, 
            0xF97693E4DEB277DDULL, 0x3D74D5654943B579ULL, 0xACA36AF741A49295ULL, 0xA80DA8256D4F126EULL, 
            0xA022CFE6856A4967ULL, 0x73FDEE2D525C0EE9ULL, 0x44C1A026C765E431ULL, 0x07B50DC02067F191ULL, 
            0xBEE518E1E3DEA41EULL, 0x0CFA2D01059C7834ULL, 0xE6628C7558BC43ABULL, 0xBBF192A1073A461AULL, 
            0x06A052A84D695958ULL, 0x50F54AA0E7553652ULL, 0x773E25817B8EAE94ULL, 0x2DA722B4CEA4FA3DULL, 
            0xFD8AFC8D0A71D97CULL, 0x540D10AF1FC4827BULL, 0x337111764F141C19ULL, 0x894E6C83379D3ABDULL
        },
        {
            0x65AD66FC3D298ED8ULL, 0x198163FF1B6B235AULL, 0x069C1B83526B0AFEULL, 0xC2FA63DD7AED5AEAULL, 
            0x7F7688982B02E165ULL, 0x9688498A3DBA772EULL, 0xB68811CA74ECDB7EULL, 0xBA0A58A4708616D8ULL, 
            0x2B3E3BFC5662E97EULL, 0xCB64FD44B1AA6DD6ULL, 0xE46FAF117776AD59ULL, 0xDF1115599D20F6F2ULL, 
            0x377E9208F3B28192ULL, 0xD7CC8615377A3C44ULL, 0xDABAE49DBB0D59CDULL, 0x6443817E0E3703DAULL, 
            0x3AB005F24ADE9BCBULL, 0x4AFF1AA43215582EULL, 0xDE95F3FB4357F5F2ULL, 0x0F9AF8856B269CB6ULL, 
            0x7FAC4341CFE66C06ULL, 0xA38352242A5A4945ULL, 0x6C7399D40CC6CFB4ULL, 0x6949441B107B4413ULL, 
            0x7390F41F1B4A400BULL, 0x87A5F79C29930467ULL, 0x0153BC42F9168F37ULL, 0x40F946556FCD45FFULL, 
            0xADBC8C58D54CF18AULL, 0xFF0179D9807E5665ULL, 0x74F1A9386B2E1A17ULL, 0x76631122C64E8517ULL
        },
        {
            0x51DE1E43A9CD3683ULL, 0x21DA5064132B294FULL, 0x19438CBAC8D5CDFEULL, 0x571FD67E4673ACC7ULL, 
            0xD015ADBBBBF78834ULL, 0x3F066CECDB73231BULL, 0x7F935ABCB8E1D7C6ULL, 0x703FCF75A2C59B1DULL, 
            0x25A2C8EFE5EA8B33ULL, 0x023CED08327F65F1ULL, 0xF12A36222D9FA95DULL, 0x8618273D3F5EF1BEULL, 
            0xAF25E11DA540E8CAULL, 0x0718FD7A9042EAB5ULL, 0xADF293EA90D435C6ULL, 0x1A37C94B0736A15FULL, 
            0x5DAC262EC4240098ULL, 0x033939B62BD3E91EULL, 0xCA04628B9E5C164FULL, 0xA43893621DE36804ULL, 
            0x492DDA8FE6950AC7ULL, 0x68B1DDB924B33C52ULL, 0xD75A24E160F6D10BULL, 0x973A996D9F5A7D32ULL, 
            0x20E5DBBA6374D381ULL, 0x760DE8042A3BD37AULL, 0x5A2D38A98945B126ULL, 0x2A25E14CAF39244BULL, 
            0xD910E89B689344D3ULL, 0xA7E9A6D42FBD4745ULL, 0xBE52B06FF9541F53ULL, 0xE485324AE0A8D8C0ULL
        }
    },
    {
        {
            0x9A39FCCA61E2A7A0ULL, 0xD3852B7533051F1EULL, 0x2429D1534E377C94ULL, 0x4932FCF2E22D4A01ULL, 
            0xB29FC3F191BAD603ULL, 0x8DA5BCADB4B4D1A5ULL, 0xFC4BD4C60A27BB16ULL, 0x87DD829C12F394C3ULL, 
            0x1839AB77F8080E52ULL, 0xC19E0BFFFA73C477ULL, 0x4555BDB601E7812FULL, 0xCCA109C909B48F58ULL, 
            0xB930DD2E01FBA3BFULL, 0x6D47DA22FBBA67ABULL, 0x7D769A13332CBC78ULL, 0x80BC46CD23986CAFULL, 
            0xAB14076FA3B6D28CULL, 0x56C475B81C1C80F8ULL, 0x3D65404B244A3E6FULL, 0x9215732F958CAC1AULL, 
            0xD419ABB051D5B075ULL, 0x6B3CC35799F10DFAULL, 0x35A1892BA3FE6192ULL, 0x924624154B3A1D96ULL, 
            0xBCBAC59A39CF7903ULL, 0x03AF14B7E9BF0432ULL, 0xC587C7F75F65945BULL, 0xD8F782110D8E8B8BULL, 
            0x30AD7C808C41D57BULL, 0x14B7015FAB5438E1ULL, 0xCDDBB82BBC17D0E8ULL, 0x2A9C81E40589B4FDULL
        },
        {
            0x643EEB17E40FF2FBULL, 0xA19E70239D90E7EAULL, 0x412981D88743A40BULL, 0xA9EB5450CC72CD0CULL, 
            0x91295589F52B9140ULL, 0x45875AE5610A2AF6ULL, 0x99AA8623D9C42C6DULL, 0x9BE7A798C4A433B5ULL, 
            0xD3BA3FBEF297B826ULL, 0xD2081C03DBC757EFULL, 0x952FFA1389FE58C5ULL, 0xDF195275F30949B5ULL, 
            0xECC1F396BA0AF996ULL, 0xBA9E6451CF761002ULL, 0x2BD77CBACC8A84A5ULL, 0x8F01763726040B8AULL, 
            0xE543327F20C3F732ULL, 0x356399A34AC49C4CULL, 0xF388292B00CA0E50ULL, 0xAB35F4C02625E0B4ULL, 
            0xB8BF758E4F29CE29ULL, 0x459145EAA5BA2829ULL, 0xE3E41185F671DC58ULL, 0xA5268CC67A5B5DFBULL, 
            0xF46CC0202FF04A94ULL, 0xE174106B1C1F1457ULL, 0xB39CE5DA9EE73138ULL, 0x21A5C0A26A9330EFULL, 
            0x2A00F0B2890257A8ULL, 0xDF381A014B0D2B6AULL, 0x269B8CD4FFA23E2BULL, 0x33C89E7B07A18C00ULL
        },
        {
            0x1DE7B7113D7A44B0ULL, 0xCFAB004B0EFCAF97ULL, 0xA93B1AE9AAC529D7ULL, 0xD61B320094DF319FULL, 
            0xAEF9E9EA8CFEE5A9ULL, 0x2B6E1297485C54D6ULL, 0xFC52E5C04AD0FFE6ULL, 0xC7464E3A9ECA9941ULL, 
            0x70F8689DFC11FC05ULL, 0x2F8AE8C709013837ULL, 0xE57656B7F44BCE2EULL, 0xA49F1956D85732E0ULL, 
            0x1DAA8845877C185AULL, 0xF1D16D0FCB27BD3FULL, 0x2ADF1155902F077DULL, 0x62CAADF288DABCD8ULL, 
            0xF788CBAF12A9B16CULL, 0xC287720DA47A8700ULL, 0x76E6A6A149FA3D21ULL, 0x48F15B70E2F7E811ULL, 
            0xC743FB1C7F5B3914ULL, 0x0C5D274D5B082084ULL, 0x9F0E201CAB9DA0BBULL, 0xBF2BDF6118D43DD0ULL, 
            0x799225932DF94712ULL, 0xD3E37A0A115E5729ULL, 0x331CC116D3EED0A4ULL, 0x8B4D621C1DC3597FULL, 
            0xDBBDBF1D9B6E371FULL, 0xAA3765701DAC0D4BULL, 0x86934C228D1BA548ULL, 0x151B261450D65C43ULL
        },
        {
            0x4409800524793DB2ULL, 0x0AAC1D7BE7D39EF7ULL, 0xB6192605B14F8EB4ULL, 0x00983F6000512B7BULL, 
            0xD7FC4132D883CE8FULL, 0x30B95996DC8E1212ULL, 0xF4B7E11877BDD956ULL, 0x3A3E1105199B3F85ULL, 
            0x0486F3ECF2F5535BULL, 0x8664FC73C39DC0E6ULL, 0xC9E837F231F1526BULL, 0xDAC37C56E76D0BDAULL, 
            0x639204B4058B4840ULL, 0xBDF26FAE99A99939ULL, 0xCF368C9EF0DA5EA2ULL, 0x55F7D9FADC88D595ULL, 
            0x116B266CE5FED940ULL, 0x5585B6FB43C35C78ULL, 0xA68FA713D9E63646ULL, 0xAD25652A06DA1B53ULL, 
            0xB3BE09933C87ED1AULL, 0x495615973E73FCBEULL, 0x6DD060ABDC65450FULL, 0x301A986EDCAE0B4CULL, 
            0x0F799A63D35BA827ULL, 0x35F934351611F146ULL, 0x1FB4EC02B48790AEULL, 0x66DC969DF0DF3C47ULL, 
            0xFE7BBF48B924CEECULL, 0xC63ABBC23044A992ULL, 0xD0E4A1F736F6CF2BULL, 0x48ADA999E8993680ULL
        },
        {
            0x1A34986FD40AD064ULL, 0x8175D9C403C41D31ULL, 0x7F9017491826D91AULL, 0x7074FC3F8101D419ULL, 
            0x011CF47D7C0FD0D5ULL, 0x666AF856FC2DA628ULL, 0xA106F3017FD40C7EULL, 0x5E9137DAC5F5FF1AULL, 
            0x889E1231DF0B4339ULL, 0x60C1EA0365A1D68FULL, 0x3B85BABFD23C69B4ULL, 0x4520F958665D4DA4ULL, 
            0xA4E953E7B2EE07DCULL, 0x9A3D80254988968EULL, 0x4868A1A13B2F221DULL, 0xBCF311AE040E1FE6ULL, 
            0xC0BBE135911CCE0EULL, 0x593130EBB00DEB74ULL, 0x5434F889433FAAC0ULL, 0x6AC3566967E8C77FULL, 
            0x3D8C138315B1AEABULL, 0xA240DE3990CE6F02ULL, 0x4C827CFED3C0EE97ULL, 0x22B44E64180AAE2AULL, 
            0xB90F0BD580A75CBAULL, 0x5204958677C2FF9EULL, 0x799C72BAFBB973B8ULL, 0x2F0055B6AE957176ULL, 
            0x0D9CF8F0FE9AD341ULL, 0xA49811FF9F69209FULL, 0xD15B16523E3CA35EULL, 0x6203B76B431EE0C2ULL
        },
        {
            0xB0BDE05DC819AADEULL, 0x74AE2E818C9D2C12ULL, 0xCBFED247E91D78E6ULL, 0x40E3DB263583E902ULL, 
            0x12401D5FE3CAD455ULL, 0x247199801EE730F1ULL, 0xF973B34D04CA4B31ULL, 0x1A56F0AC210EB881ULL, 
            0x0B8D9A20E1BDC463ULL, 0xE4A1FC0121CF277DULL, 0x2A7E0D1DB9B4E17AULL, 0x1DA5B7AFF56D0C3BULL, 
            0xDAC6B1BD4E2D7AD7ULL, 0x32B256526B49FE74ULL, 0x4814BB3180FEC345ULL, 0x10B3C790736AD24BULL, 
            0x6221C52D4C8B0ED1ULL, 0xEBE4A32D2A701580ULL, 0x70FA773F59EBB7ECULL, 0x684EA2467C9CA023ULL, 
            0x9C5994FF05F9C02EULL, 0x52A3F429C9785FAAULL, 0x2D51F5D48E6003B3ULL, 0x0EC72929EF45696AULL, 
            0xF424E50A7E6C71D7ULL, 0xE3E34C3B796A24C9ULL, 0x784F88946E678B7AULL, 0x1675A43683E659AEULL, 
            0x54516CEFCCC52C47ULL, 0x25BBB67FFABF1E63ULL, 0xDCF5DB9B7B4F5C03ULL, 0xE276AE247A74849DULL
        }
    },
    {
        {
            0xB8833D8321548C33ULL, 0xBCEDFC0F5BF29DDDULL, 0x2EAA8681CDB836C6ULL, 0xBFF8F534B147D823ULL, 
            0xC841B879352F4063ULL, 0x50C73E2616D4553CULL, 0xC9A209C68AF1FF05ULL, 0x9A9FDC2DC06E6816ULL, 
            0x478DB0B13000396AULL, 0x44123E4ADC1E0071ULL, 0x90081EFBF6577701ULL, 0x9AFF58A6C1085283ULL, 
            0x77E53820F8FA7DF1ULL, 0x339B2304AD5E267DULL, 0x95C65B411DEBC2EFULL, 0xDFAC2D5097F81B42ULL, 
            0x4D5D8FF3FECEEA33ULL, 0x4D51FFB2869439F4ULL, 0xD064C0F0D742372EULL, 0xED87EB927925A5F8ULL, 
            0xBAC0FD1A9E8F89F3ULL, 0xBD37B603F9FBC56FULL, 0x418871444EE72AA6ULL, 0xF48EACDAACC1E162ULL, 
            0xFE2360AEAE7E1518ULL, 0x4ACBD2BBF8EF1C55ULL, 0x21A1D3D8E163C1EEULL, 0xA1242C8C0AD58F5BULL, 
            0x44235DEF1BF59EF8ULL, 0x74F341ED0C065447ULL, 0x981A49AD72916256ULL, 0x4C71FB81CE495FD2ULL
        },
        {
            0x2851B17E36315427ULL, 0xABEBF000D88664CDULL, 0xC3F2EFBE8839B89CULL, 0x183524693340280AULL, 
            0xEE5B5AA4821B1914ULL, 0xB5329744905A9A9CULL, 0x394BF525BCCC8AF3ULL, 0xD0383A41AB83A2E3ULL, 
            0x87E87DFDDDED9292ULL, 0x8223A190B149B460ULL, 0x0435638B9B716A3AULL, 0x964C38CB37089463ULL, 
            0xB1A29223FFB27475ULL, 0x188C6A0624B29275ULL, 0x66F090C6BE9287CFULL, 0xF1D93A97E5FEC0EEULL, 
            0xC20048FA36B054ADULL, 0x31C93082C1ACEAF7ULL, 0x8A1CE816BD0E2E93ULL, 0x6A32D7BF56A24D25ULL, 
            0x81B947EDBDF64579ULL, 0xB624138A8C8CEC5AULL, 0x9D8CB2325D082A2CULL, 0xA35987F3FE64777EULL, 
            0xF29E17F7480FA94AULL, 0x828BF5B4CC0E5F9FULL, 0x41455DB70BE6F3EEULL, 0x720AAC70E373A144ULL, 
            0x0F79C3FFDFA947FFULL, 0xB5603D6840F26E15ULL, 0xBDB6D7C9E842D726ULL, 0x5DA60C935F517577ULL
        },
        {
            0xEF6E064D72767850ULL, 0xAF4DE24A1D9B2B33ULL, 0x177FBE05DE91705CULL, 0x6F501D64308604EAULL, 
            0x7F381BCF191AD436ULL, 0x65EF1FD6CA5FF890ULL, 0xBEF14F80ED811498ULL, 0xF6DA5ABB7AC398D5ULL, 
            0x2A733026CA41A500ULL, 0xFD5B1408194761B4ULL, 0xA0EFC0DD3C3969EAULL, 0xA57CC29A57392AE2ULL, 
            0x9836EB387CFB8D8DULL, 0xE5DE035EF5B7D0BBULL, 0xA87CD55FB245633CULL, 0xF187E370FAECBD11ULL, 
            0x28141A55E3E3C750ULL, 0xBCCA183358530961ULL, 0x6A145117B9BA7A6BULL, 0xC0CE6E6DCF04B805ULL, 
            0xCCD1924CEE952D9DULL, 0x1EF07165150E1A0FULL, 0x9386DCD22F934520ULL, 0x753364AA79964F5FULL, 
            0x8555037B1C6FB5DCULL, 0x92C0ED1A8A2C8222ULL, 0x335C4858D06EBA7DULL, 0x2226720466517FD0ULL, 
            0x2DBE5C4B093E6738ULL, 0x162B13429068DFAFULL, 0x89914509D2E7002CULL, 0xEC80701FCFDFA54EULL
        },
        {
            0x0AA2435A9B1A8863ULL, 0x852B2443BA181BEEULL, 0xA31F6A3163D799E8ULL, 0x94E12014E805F72FULL, 
            0x6B3E8BF9893787B2ULL, 0xBCA2F838782DA7C9ULL, 0x2C61E903CAA0072EULL, 0xBAAFEFA8E7C8A4E8ULL, 
            0xA13A59CB98A27FF9ULL, 0x7339EFA08B6930FCULL, 0xAD1FCFA2626C8034ULL, 0x817408FFBDE870AAULL, 
            0x0FF188664E324EF2ULL, 0xDE5D124942CDCF18ULL, 0xB5C7AFDB5D71B71FULL, 0x88D0412CE78A217CULL, 
            0x85C5FBA279497922ULL, 0x8231C52A5D48A62EULL, 0xFEE27F91A7DF3204ULL, 0xCC3F7B78E34EF44FULL, 
            0xAD947AADDF2A9C34ULL, 0xCC2550B8BDA44A1BULL, 0x253C5358B52A6909ULL, 0xA14FAA6BDF5B63BEULL, 
            0x0A4243378568A2DCULL, 0x55F49F53E8428B0DULL, 0x867337AF2B38A018ULL, 0x27FB5E09EEE07ED2ULL, 
            0x7DCD55FA87F0D47CULL, 0x1B8534EB8011A2A0ULL, 0x30B55DAD1F536A39ULL, 0x4636E4B3A8F7109CULL
        },
        {
            0xFBD5A425FBE05EB9ULL, 0x74F30C5F191340E2ULL, 0x5E0347B6222A3A00ULL, 0x628A23A849635CBCULL, 
            0x72886ED85CEB52BAULL, 0x86120B1039FC9FA2ULL, 0x73FE25E6EC2D5089ULL, 0xDB26E25DD5B35ADFULL, 
            0xEEA7F4BE5C950D2AULL, 0x47FD122961AB4478ULL, 0x07845556A2287221ULL, 0x7B7D9C2671EA1FD2ULL, 
            0xA9C0BAEB6D4302F8ULL, 0x86F418C4121664A2ULL, 0xB5B92C075D437121ULL, 0x8A7E9662BA7C44FBULL, 
            0x8CFD450A31A8A9BCULL, 0xFF2180DCA1AB6FE3ULL, 0x82AC34D23F940BA3ULL, 0x1421BF739C80BDFEULL, 
            0xDEB859521D39011DULL, 0xC1DA0E1F28918EDAULL, 0xECD776A830ACDF0DULL, 0x1F03B09601FD263FULL, 
            0x628C3FCD49A6BA65ULL, 0xB9EA72FF855163CCULL, 0x8F8A163AA98BB7E6ULL, 0x492B41E727019A13ULL, 
            0x1B6DC77B7552F398ULL, 0x9FEB384B95794E74ULL, 0x875040D2A3B95D40ULL, 0xFC8752E15A873270ULL
        },
        {
            0x1E36B8E90FCBEBE9ULL, 0x3CE866412937C29DULL, 0xCA7B70575D30E3E7ULL, 0x878CC97887597FF5ULL, 
            0xEE9B25D08838042FULL, 0x3AA303134503C181ULL, 0x5DEB032ED56732F2ULL, 0xB1604E6557B3A65BULL, 
            0xDC6968EA68D32F1FULL, 0x4EF1E1BB4BF28824ULL, 0xFA706374E81CECDCULL, 0x17BF22F34B1932E4ULL, 
            0xDCEF908BBBC3D5E6ULL, 0x361D9355081D782EULL, 0xB4E2A4A8287221F1ULL, 0xECCD2038DF426B2BULL, 
            0xBE761D4B1D6EAA5FULL, 0x7D99D1EB9331C9B8ULL, 0xE6FEDBC09E32C629ULL, 0x3C6AE74F4E87CD5CULL, 
            0x05D11DF7B957DA24ULL, 0x775F64C2A5FA1B37ULL, 0xE3BF59B746DAE935ULL, 0xAEECBB187C7621DEULL, 
            0x678EF05ADF5A1FEBULL, 0x2CB2BB3B6AF7A9C9ULL, 0x7645F729DCBC6E05ULL, 0x2C4F78B575088E32ULL, 
            0x3476F5AC89B1E300ULL, 0xF3A6F767A76599B0ULL, 0x3F64E124C1433C1BULL, 0x4123E752044D6C5EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseGConstants = {
    0x4C0A54742760D486ULL,
    0x3CA916C2C78B80A1ULL,
    0x2F260A2A808EBE2AULL,
    0x4C0A54742760D486ULL,
    0x3CA916C2C78B80A1ULL,
    0x2F260A2A808EBE2AULL,
    0xB102E18BFA5CA6A2ULL,
    0x7735D241CC95C986ULL,
    0xAF,
    0xC4,
    0xC1,
    0x60,
    0xE5,
    0xB9,
    0x6F,
    0xFF
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseHSalts = {
    {
        {
            0x82FEBF9F848183D1ULL, 0x0A371002687F1784ULL, 0xF573F34F439452C9ULL, 0x3D56904429941E2CULL, 
            0xC60E815CCADA40A3ULL, 0x78721E2B72C2E388ULL, 0xE96ED0FEE60E74D4ULL, 0x63785AC45C5ADA9DULL, 
            0x60D80A97058F3187ULL, 0x24B19FFA5108D2EAULL, 0xEAD46CFB71891582ULL, 0x7860DFFE0FBF4761ULL, 
            0xAD36FDC352E23DA9ULL, 0x22F0EE7F216EBD36ULL, 0x6A59741AD3C217C5ULL, 0x7D01BB54FBD5A428ULL, 
            0x676C6AD03404557DULL, 0xE3B3334E357A4FD0ULL, 0x88F75BE15647853EULL, 0x44D9EEB06C204D39ULL, 
            0x0EB46A55C768D258ULL, 0xB3DCB1313EFFEB1AULL, 0x6C6B54601B2882F5ULL, 0xAFC35BCDA4E63906ULL, 
            0xE8EC402AF6227E6DULL, 0x7A5FCB782694E241ULL, 0x6CD5CB441E77D5E0ULL, 0x962DDB7E94E6A1C5ULL, 
            0xDCB8ECD11A61E0D1ULL, 0xC91040B07FFC636BULL, 0xFA1B7B091F7D51BAULL, 0x25E7C193659A72B5ULL
        },
        {
            0xC35E371E7436369CULL, 0xEB5D74AB4D8D3BB7ULL, 0xB48DD87528659341ULL, 0xEDC82B6057CB2217ULL, 
            0x8C0CBE2FFA697BFCULL, 0x31A90EB47E406C59ULL, 0x01D01E40833F3BFCULL, 0xA4C5FD54E70CF97AULL, 
            0xB4E3837FDF38B480ULL, 0x540EB8420398094BULL, 0x125DE95B42AEE572ULL, 0xCCD8A3F2E7A75CEEULL, 
            0x6FEE5C60838DC3D5ULL, 0xC7229582AFE361C7ULL, 0xD099F05733A268FAULL, 0x0A59A1AF863E7E81ULL, 
            0xC5CCB0DFB0BA5456ULL, 0xBF952258FB1C1C2CULL, 0xFA67A8E407283210ULL, 0xBDA8B8684FD30C28ULL, 
            0xD7B078081CF5EB13ULL, 0x9E1D47889FFFEA7AULL, 0x5E9AB0EC95A69E8BULL, 0xD2831E26449C9759ULL, 
            0xAC718DFA5C4C5DBCULL, 0x1D29E02FE143D1A0ULL, 0xA2C6348D61A91A67ULL, 0x687A232827890101ULL, 
            0x511796D4C9515040ULL, 0x8CCF0670889B2953ULL, 0xD2066BDA1264A434ULL, 0xFB8225B9139EED9DULL
        },
        {
            0x754A23A39094EAD6ULL, 0xC07534CC7E1E64C4ULL, 0x8B60767DA2302008ULL, 0xEF10455491D9F7D6ULL, 
            0x171C93AF82378CB9ULL, 0x418A0B221AB2AF0EULL, 0x20420EDDD11497B2ULL, 0x6B77F4200A494E0DULL, 
            0xC19BC919C59C2350ULL, 0x16639DC694C79EC1ULL, 0x688FD858B655D87DULL, 0x6C2E12F05FCBC9F4ULL, 
            0x68155663008B6E52ULL, 0x729D0A045EB19EEFULL, 0xBEC9A5BD92DAC280ULL, 0x83DA4A97C2287526ULL, 
            0x8F2062971F67B1E5ULL, 0x8B75A07BB54A872CULL, 0xAE7D230517619FB5ULL, 0x4F3C4566C3076F29ULL, 
            0x82BD99BFE5DB0F6CULL, 0x7DF848E087F1F0A9ULL, 0xBE511207F6494B8AULL, 0xFE364BA7270D9F9CULL, 
            0x53F598E4914C1A5AULL, 0xC3511A04993B9446ULL, 0x483A037BD64D51BCULL, 0x88389BA1906A749CULL, 
            0xAF3296E2306472EBULL, 0xA82399E070353F8EULL, 0xE5A71A0B9504CB8EULL, 0x6CDF3F773A508B13ULL
        },
        {
            0x5672625BEDB68B57ULL, 0x8E5F0A4BD486B877ULL, 0x98EEAD21C683298BULL, 0x9676D10A3CB2DEB1ULL, 
            0x53EA3BE0C91560D5ULL, 0x62F4A8977253F58EULL, 0xB14A8BEEAA9F1596ULL, 0xF30EA22320B8EA01ULL, 
            0xBC235D40AB638E81ULL, 0x822FDB14AA85CBB2ULL, 0x722A2434EEA71DCAULL, 0x0A7A07152D991077ULL, 
            0xF1890B4AE1812389ULL, 0x5998FE5CB623DB48ULL, 0x20E8BF5E332B6706ULL, 0x29C32167EFA91304ULL, 
            0x9182173552D3BC09ULL, 0xF07AB5BA3804E67FULL, 0x2CA762FA90C1F320ULL, 0x08843A5C3A98B68BULL, 
            0x56709C4C4DC744BEULL, 0x7A68574789716B47ULL, 0xE7D8840A9334394DULL, 0xF4C425481A6572AFULL, 
            0x8055C38352902C6BULL, 0x1198CEAC3DE0C864ULL, 0x4527AF0451C4FACDULL, 0xE0FBD77183A35C33ULL, 
            0x2830BC36C7B185DFULL, 0xA115A72C0CA25C81ULL, 0x0618309F642A426CULL, 0x7261F70361F045EEULL
        },
        {
            0xA8E44C69611C3AFDULL, 0x4C4D2200F6DFA2ECULL, 0x8901A9764F1751DFULL, 0xA72A8654078D131DULL, 
            0x4C2D2089367A5AD7ULL, 0x97B7AFDAB3A89169ULL, 0x051735DDA9138248ULL, 0x3227FC8D02B6F50FULL, 
            0x7E25A1C3972C110FULL, 0xC280B366D30CB327ULL, 0xD26858D63B493EAEULL, 0x0B546FA7D4631E18ULL, 
            0x9DC799861A02E919ULL, 0xC148E31505F1238FULL, 0xDAF4B69A6BC5BCF0ULL, 0x4C9B47BB76FE0A78ULL, 
            0x92C9A96C57F7AE56ULL, 0x83A0B8EF2EBA7A88ULL, 0x760819F752A0EB37ULL, 0xF498D2431EAFCF51ULL, 
            0xA67238B64C128C9AULL, 0xD08C4C710B4436DBULL, 0xB244D702B315122AULL, 0x11D9E70D172EAE04ULL, 
            0x0DDEF34209F58FEEULL, 0x8FDEE0E3A20A1CB9ULL, 0x422E60294A9E8C8AULL, 0x7F2612CFD851BE87ULL, 
            0x3FB40593F30CACA2ULL, 0x83766C1B79E76717ULL, 0x7365FDF100FF93C2ULL, 0x1769503B96E4C28BULL
        },
        {
            0xB807789B8940CD86ULL, 0x0C1B085D9FE1C2B6ULL, 0x15FE9FA02C6E448FULL, 0xA94943F5645B3E5FULL, 
            0xF6EE3125C6A71246ULL, 0xD418731A40692D80ULL, 0xE92198AA68136BF5ULL, 0x1C48F223AFC161FFULL, 
            0x1CDFEED645D62DE3ULL, 0xED1ADA2105F8D74BULL, 0xDFC81B8752F79952ULL, 0x04BD3468197DE187ULL, 
            0x393A68F8D42E01E3ULL, 0x85DD56CED929F476ULL, 0xFCA20B5186DBAC01ULL, 0x293D384CAC782873ULL, 
            0x5DC6EBE13AAA8275ULL, 0x5D035C93958F9BC2ULL, 0x8229FB6B25818F2FULL, 0x0A1FFAB79E158023ULL, 
            0xB2B2D64B5D4E5BBEULL, 0x8020FEC26D174DAAULL, 0xBB80012FBD1688E7ULL, 0x7FABEB36FCFB1B53ULL, 
            0xB2F52B78A13EA4BEULL, 0x6A937E7FD698E311ULL, 0x04810E67F09C478EULL, 0xD25F98D4E4D8A3FFULL, 
            0xC866FBD7D36A38A8ULL, 0x43BE614E902F202CULL, 0x22E75A76ADA9FD43ULL, 0x7E53C172CD8CE0D1ULL
        }
    },
    {
        {
            0xE234FF8DEB2DE44AULL, 0xFEF87E50B13E050FULL, 0x8CD84D05440858ACULL, 0xEDE71B710E2F57B9ULL, 
            0xC6EE68E545EF6018ULL, 0x0B27A8716F76B69FULL, 0x2A13E25B79C2708AULL, 0x13798ED617192345ULL, 
            0xF03754DE141BDC8AULL, 0xF2666357C11183C5ULL, 0xF3AA8F85DCBB0C60ULL, 0x151CD6F7F4BA99D4ULL, 
            0xF993E2C1677AA0B9ULL, 0xD2B9BE8E1455B011ULL, 0xFAAFE3926143BF24ULL, 0x39515A0941EA64D6ULL, 
            0x1F4ACDCFDB1CD940ULL, 0x20F9256DB2698F60ULL, 0x4CAAE3CC35B9C07BULL, 0x0D163C3EB3E418A0ULL, 
            0x978E88482FCA354FULL, 0x159B293F1539B4A6ULL, 0xE24F3F2916A8FAC0ULL, 0x031F8B92D43F8F21ULL, 
            0xC6218FC0CEB4042BULL, 0x180FE1D4CA75C1D2ULL, 0xEBDCC99B43B62CA4ULL, 0xAF52D2E3CBA6D0B4ULL, 
            0x293C48ADE762FAE5ULL, 0x2C193064A1299195ULL, 0x9B756C7E0001B8C2ULL, 0x52A2D605D637AC22ULL
        },
        {
            0x412557426784A6A2ULL, 0x3E1947005D41DF71ULL, 0x2784B74D142C10EBULL, 0x582B2558CF56D0AEULL, 
            0x6AD3280D98F11AB0ULL, 0x86210725538A0A68ULL, 0xD356BC18AB508D94ULL, 0xDE26E523D34C46EBULL, 
            0x2E6DE3472E59C6C0ULL, 0xC1A8BC05CBFE7C41ULL, 0xAD0E6D6F4785A7F0ULL, 0xEA771FFFDCEBDCECULL, 
            0xC08640156FBB30D2ULL, 0x9B836B0CB045D2F8ULL, 0x052A094FEFE5FFA5ULL, 0x4F3C67F22F08EDA8ULL, 
            0x9C05CFF9DCD9B56BULL, 0xF74AB6D759C94CA4ULL, 0xC6D2186F04619612ULL, 0x8EAC31E06601976BULL, 
            0x0B969EDFDA437A8EULL, 0xBA566C06BAE25FCFULL, 0x105B66ABEE2036CBULL, 0x63C450F25497CA91ULL, 
            0x7785EE0EC751A7A1ULL, 0xA55140F26D7A3879ULL, 0xAC9DEA0D77647A97ULL, 0xDD203C79C4387134ULL, 
            0xEA5FDAD9F1455AC4ULL, 0x4860BB14DB3557DDULL, 0xB7DC2E99BA0D49D0ULL, 0xAD1330335E637044ULL
        },
        {
            0x6A0687E0280973F1ULL, 0x1CFFD68F60477D26ULL, 0x15D0F434B4A308D0ULL, 0xE8A7C230542D74C6ULL, 
            0x84E9634BADCDC0E8ULL, 0xE8195ED54BEB5CE2ULL, 0xC0EEDDE2757A3FA0ULL, 0x38A14DD92E2329E6ULL, 
            0x785BD1FA97BAD542ULL, 0x0DE92266B34850DBULL, 0x02B9C87F41B7C7E9ULL, 0x21FCCB44A5919A61ULL, 
            0x74718569D20548D1ULL, 0xF7B649413AA011FBULL, 0xD3ABABCB6CFD1B06ULL, 0x50E779B001F590FEULL, 
            0x38D0A02A3A4994C6ULL, 0x54F68CEE27B39F43ULL, 0xAA6C2D26C8BFBD8DULL, 0x5B5EFC6610E9252DULL, 
            0xB5CE8473B5FC48D1ULL, 0xE6699A0456950EBCULL, 0x7A59B219D110BF4FULL, 0x26C5F3E86704D4DAULL, 
            0x3E3E07BF461DC490ULL, 0x4BE24AD7C31D258EULL, 0x0AE5E8B27E577F02ULL, 0x5966AE72311C9A6FULL, 
            0x658C45CCD26DB9A7ULL, 0x4D2E0B030C9FFFCCULL, 0x3443EC651A0DB709ULL, 0x46050AC2549C518FULL
        },
        {
            0x85290F5584432DFDULL, 0x844CFB0B5C7A25C5ULL, 0xAB0761C53D740B91ULL, 0x73219C193B58A1E7ULL, 
            0x3EC6A5D34C4DBBE4ULL, 0xAC1D34CB7D5CC84BULL, 0x76D7D8C83D066E98ULL, 0x16FA456F56DBDFA6ULL, 
            0x61B863722F5DFBC8ULL, 0x943FFA12C05637ADULL, 0xCEB660C2BA552535ULL, 0x42F96DF30AFAA9DDULL, 
            0x19DA6F8772AB0328ULL, 0x99B355D62B73481CULL, 0xB939D3CF565FB461ULL, 0x0F74623D4E540644ULL, 
            0x659C7FDF7A328621ULL, 0x277A0BFDCCD71669ULL, 0x8A47913FC9A2D1D5ULL, 0x37FC58DFD621EDD4ULL, 
            0x0858098B32D12DA0ULL, 0x1D28E5299BF0E1ADULL, 0x286301B284661780ULL, 0x942EFF10A80B0952ULL, 
            0x1EB16B46ECE27ADEULL, 0xE38B30EDE99E7CAEULL, 0x755CA474D58107DAULL, 0x3332973294FCA5F6ULL, 
            0x780170B1A0CFFFE0ULL, 0x0B3D76F5811F7775ULL, 0x90CEA6E233088C77ULL, 0x0FEA62932D38CB5AULL
        },
        {
            0x919D066D1AC0774DULL, 0xD2C9C4D021BE2305ULL, 0x74FE6411797AFED3ULL, 0x24F9CBC07520DE1FULL, 
            0xC985A1F615AF3C8FULL, 0xD2D71070F8F10C7FULL, 0x9F13EC7331FF6718ULL, 0xC0BE23D8E1A341D6ULL, 
            0x747A695D8A079EDFULL, 0x905ECDEE4E6E2A00ULL, 0x0E71CDBCB4216442ULL, 0x6B10100ABC175BF7ULL, 
            0xD3756D03EAC8E357ULL, 0xD02CABB57C748AF8ULL, 0x8741CF262F003E3EULL, 0xB4D4140343D407F2ULL, 
            0x53CC7B143133467FULL, 0xA29F9D7F0B562F3FULL, 0x5BD28780961C898FULL, 0xABF72AA0ADC03882ULL, 
            0xB1F12620797BF44BULL, 0x99EB53011FE061F4ULL, 0x4E9A3F9C43B1404EULL, 0x0ACA7546AEFD3EF2ULL, 
            0x6FAD5C7414BF379BULL, 0x2EF53BE49DF709B4ULL, 0xF6A5CA63AFC08090ULL, 0x1402D040016A9A6AULL, 
            0x4381D3E1BF703798ULL, 0x149FCECABB1522CEULL, 0x8FA87F9AEAC6FCADULL, 0xDDC76D21F8671FC8ULL
        },
        {
            0x087008C40CCE1A9EULL, 0x8DF23828855DE806ULL, 0xC57643F2670B279BULL, 0x02840C017195F9D0ULL, 
            0xED2521EE69E65CC5ULL, 0x7E7F5D1A25831E10ULL, 0x11A5600EF3A217A6ULL, 0x5ED266B42DE404B8ULL, 
            0xAB2FF7BBA5765C09ULL, 0xD353A857769525FAULL, 0x33A8B274D3A403D7ULL, 0x2C1963CC58D81F66ULL, 
            0x91E0265BBAA5C0BAULL, 0xF8B6B21768F8D86DULL, 0x7767CF2A8E7C7EB0ULL, 0x244B0A43BB44D39FULL, 
            0x84C5A5FA8FBAC1C8ULL, 0x7DB6F120EE9042DAULL, 0x2CADC99739AB6288ULL, 0xE3194E701522C1E9ULL, 
            0xE4DA576C770F07EAULL, 0xF932561D46DB14FFULL, 0x3D75539891621E2AULL, 0x165906920B39DF2FULL, 
            0x9DC92AF56AAE9347ULL, 0x727CEA519302ECF9ULL, 0x0A34A05A41723E9DULL, 0x77B7D1E7986AB697ULL, 
            0x238C50310C678D85ULL, 0xDEA90C932BFD2BB7ULL, 0x1D8B07E55A78DB0BULL, 0xE867CB1B92EEBCF0ULL
        }
    },
    {
        {
            0xB415450B6FCF0A8AULL, 0xDF2B4F0563C27382ULL, 0x3090BD5A072138ECULL, 0x598482FF91CA63AAULL, 
            0x90485F46B093EA5BULL, 0x930D8EDF0317A213ULL, 0x06F40821DC6C79CCULL, 0x1941BBF4250C6935ULL, 
            0xA912B7448DDC3234ULL, 0x8F0D7A042A396524ULL, 0x36E13A4401DD22CCULL, 0xFCF91C4DE74894FDULL, 
            0xF886671CECDF5F4AULL, 0xC9EC190516E18565ULL, 0x07EE0DB37687B8F4ULL, 0x6139D2040AD3CA98ULL, 
            0x33424A6CDE6C8EBAULL, 0xC04EDAE372D6C5A3ULL, 0x8AECAA8149B3500FULL, 0x5F5582647D8993F9ULL, 
            0xD10DD8C218FBE9C6ULL, 0x2F9A6FB7F22BD2DDULL, 0xFC3265CFB27D80B8ULL, 0x0EE1ECFA24E1A024ULL, 
            0xA9BFAF02AEF347B8ULL, 0xD759078789E618A7ULL, 0xFD1855A43B329A4AULL, 0x59D53C0126CE91F7ULL, 
            0x22A037D85E91A551ULL, 0xC66AB0925E14AD0FULL, 0x323B1492A65E4453ULL, 0x6C33D48527FAE1CDULL
        },
        {
            0xE309AE927E28C197ULL, 0xAA789BDD22B57400ULL, 0x2E2A0378FD8CF35AULL, 0x71C9292F5E3B9BAEULL, 
            0x9E73F346E0E01737ULL, 0x43F216F22AD66527ULL, 0x011F415EAD22BD3EULL, 0xF0F8F282F3865BD9ULL, 
            0x4101EE9762147A0EULL, 0x2A25383F178C519EULL, 0x019D0A8D2B45EB40ULL, 0x1006855D96FB2483ULL, 
            0x759849C71042F1B5ULL, 0xD2E66B0FD44ED0C6ULL, 0x3F3E5A0A6783A055ULL, 0x6280B3480128AB9DULL, 
            0x2C8CD18EB7B82A5DULL, 0x0A7A16152EA23030ULL, 0xD5C1FB3E731E814CULL, 0x2A62FAAC6026C239ULL, 
            0x754354AFB4F8BBC1ULL, 0x956F45CDFE6DAAA2ULL, 0xBDFB1A6FFF6735EEULL, 0xEAB3340197CB7ACFULL, 
            0x7311117813175844ULL, 0xE431E1858C058C91ULL, 0xEBCBB94305A5BC1DULL, 0xBB9FDC189784EBD0ULL, 
            0x408065C495732F1FULL, 0x4C928C798E36ADA3ULL, 0xECC078819A4F3887ULL, 0x276CC8AEB31AE229ULL
        },
        {
            0x74ABBCC79A231718ULL, 0x7F9F32AF8885B651ULL, 0x5945443DC2DDB9CAULL, 0x738E4D3C4D7655F2ULL, 
            0x4095D2BA788B655FULL, 0x79A412C45F945FCCULL, 0x80DACD7CCAF6C339ULL, 0x8B994A39D44358F1ULL, 
            0xFF875DC4080595B5ULL, 0xECD11645A0D9AB03ULL, 0x8D6475194A022897ULL, 0x71F25FEF79C4C2AEULL, 
            0x44086704E87A234AULL, 0x3969E0CCDA47234FULL, 0x4E4EB6984FFAF60AULL, 0x66BD447225A19A8CULL, 
            0x33E0AB39F11CC81EULL, 0xDC71E7D8ADF8749CULL, 0x17546CFEE1D11A8BULL, 0xAFB86168CA502392ULL, 
            0xB8D860C535229239ULL, 0xD45BCEE78D67B27AULL, 0xCC663FA037132538ULL, 0xD6AB5461D43995EAULL, 
            0x3DA18BC595FB1E1EULL, 0x0220D5F51582EC79ULL, 0xBC012D6ACCC2AB30ULL, 0xBB54655BA209E84EULL, 
            0x3A60C6307C8F91DFULL, 0x9B07B5AB44251276ULL, 0x3CEBE9A8CE890FCFULL, 0x895D3E2F47DB818AULL
        },
        {
            0x7B1F86ACAC1BFF29ULL, 0x27C2CEE3170D42C3ULL, 0x2510B2A65B0954BBULL, 0x45ADF53BDE47DAC2ULL, 
            0x42AEA1553E28C17BULL, 0x619F64D0919FC461ULL, 0x4C4F6DB752151E75ULL, 0xDD3ECFF0720D61C1ULL, 
            0x9DF8828C38CD365CULL, 0x6655A451A3965A39ULL, 0x72C9D29EF6006F95ULL, 0xE73104B89D8DFDEDULL, 
            0xAA90A8B09BACDCE6ULL, 0x35A71F7E19B62EBBULL, 0x44F8A1495F3456EBULL, 0x3D76B9AFA120A442ULL, 
            0x6B14CC9875DE4D16ULL, 0x8510A340C9E255C3ULL, 0xAC8251664C848D3FULL, 0xDFC5F69BAD536C18ULL, 
            0x2FB064BD50445963ULL, 0x88243A2A192D8C74ULL, 0xE6A3537FE60B3183ULL, 0x71696F270CD3EF77ULL, 
            0x699844797ADCDDC1ULL, 0xBE5B0685A7216BE3ULL, 0x5F114986E7EEB77DULL, 0x7217388C168FF7C6ULL, 
            0x4C939649F964AD13ULL, 0x410E81241AABFD4AULL, 0x77ECABD44DAE0519ULL, 0x4227EA6BB356350BULL
        },
        {
            0xBBC00F9CF33DD583ULL, 0x9D7809F79A58D368ULL, 0xD1FB100158AABDD2ULL, 0xC8F66D0AABFB75ABULL, 
            0xAF86E69D3F716DADULL, 0xFC2BBCB71A236D1CULL, 0x2DD2EEFBE950A791ULL, 0x66B4EA4047FEC48AULL, 
            0xB47573542AE405D7ULL, 0xAFF5A6D599F53FD4ULL, 0x811A4D8918C9F5B1ULL, 0xF142552B2A8DAD8AULL, 
            0x1D0DDA9EA8241427ULL, 0xBE6C0414D5CECB81ULL, 0x3E3FC9C14D374CC8ULL, 0x38E1F5668C77A21BULL, 
            0x4E881B47B9CA51D2ULL, 0xE1B359B3F949E47FULL, 0x07DD39B1FEC36601ULL, 0x86AA7EA75785CE94ULL, 
            0x2E3B26BDDEABC95CULL, 0x6FB91834D8E17D71ULL, 0x238EF2603EA2229AULL, 0x4E6F20630B06EE3DULL, 
            0xC1E3B23F691C62E6ULL, 0x092DAFE4CFEF91FEULL, 0x69661799529286BDULL, 0xE8F78554B0FE48E2ULL, 
            0xE1C4E2769F4D1A27ULL, 0xCA4817C37CC485B4ULL, 0x4E2C0FD13DB18FD3ULL, 0x6526A86BFC5D88B7ULL
        },
        {
            0x0EC9F82E204877AEULL, 0x8E8D34CE13E9562FULL, 0xA55A078ABD9EF0D7ULL, 0x85192C277141F352ULL, 
            0xED889350250B45FCULL, 0xC4B7962F96D45920ULL, 0x62843A8892205B1EULL, 0xACE0F5BE2D523C9CULL, 
            0x3E3D14AD3DAFE26AULL, 0xEC567B274D7716B5ULL, 0x7A4A427274602A1CULL, 0x2EA2DD387ABE583DULL, 
            0xE1DF99DEC3FF0901ULL, 0xA6EDA230E7D66212ULL, 0x7E727998A3FEC3C0ULL, 0xBACB58F1806908FEULL, 
            0x72CBEB42B0B0DB3EULL, 0x3D13A0CAA59BB0EAULL, 0xCBE1595BFC73A1EAULL, 0x9E48D3D8ED196378ULL, 
            0xB4D10B190C8965BFULL, 0x618F146C63D3B023ULL, 0xCF06CB1DCD2BE84CULL, 0xA4D49BCB7297EDCAULL, 
            0xC71D653B4C9E3E23ULL, 0x2A523E76438F5E47ULL, 0x577ADDC60C82A7DBULL, 0x6CB6E775E039317DULL, 
            0x403039E26AF997C4ULL, 0xB5742E51FCF0C38CULL, 0xB8E4B0395ED06245ULL, 0xF7EEE704E4DC58BEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseHConstants = {
    0xE0AE179ADC2FFB88ULL,
    0x8CD0AD2AB94A1D8CULL,
    0x313A5E0726399835ULL,
    0xE0AE179ADC2FFB88ULL,
    0x8CD0AD2AB94A1D8CULL,
    0x313A5E0726399835ULL,
    0x9F0C1720FD71341BULL,
    0x6A5D844EF5A0A8AFULL,
    0x44,
    0x49,
    0xDE,
    0x7D,
    0x5A,
    0xBF,
    0x63,
    0x43
};

