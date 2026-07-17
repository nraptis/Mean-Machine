#include "TwistExpander_Polaris.hpp"
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

TwistExpander_Polaris::TwistExpander_Polaris()
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

void TwistExpander_Polaris::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x94D46AD254B9441CULL; std::uint64_t aIngress = 0x9152AF8F3B2C744DULL; std::uint64_t aCarry = 0xBBB05090656E68BDULL;

    std::uint64_t aWandererA = 0xE613D1BC8ED70C51ULL; std::uint64_t aWandererB = 0xE3A51B0B01ADBA29ULL; std::uint64_t aWandererC = 0xA5BE61C688B1BD2BULL; std::uint64_t aWandererD = 0xE1C0EEDDE8DF0E89ULL;
    std::uint64_t aWandererE = 0xC0D6E9F1FA7A1617ULL; std::uint64_t aWandererF = 0xC9F1DA19057A1DD6ULL; std::uint64_t aWandererG = 0xCF437B9E876D157FULL; std::uint64_t aWandererH = 0xAB047557E77DF016ULL;
    std::uint64_t aWandererI = 0xF3B57DF95BC3A227ULL; std::uint64_t aWandererJ = 0xBD874784179743DCULL; std::uint64_t aWandererK = 0xE53A0AC9C81828D2ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11266998293562529374U;
        aCarry = 10758846365663270193U;
        aWandererA = 12162719102729806855U;
        aWandererB = 11991137637689780122U;
        aWandererC = 18308299900532576722U;
        aWandererD = 12003907084312754303U;
        aWandererE = 13563933113654868807U;
        aWandererF = 9276415845920281805U;
        aWandererG = 18218499177149142884U;
        aWandererH = 18010231810336184332U;
        aWandererI = 13905537743931863965U;
        aWandererJ = 15154928142182657348U;
        aWandererK = 13014746360968568205U;
    TwistExpander_Polaris_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Polaris_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Polaris_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Polaris_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Polaris::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x815526B816FC38BFULL; std::uint64_t aIngress = 0xDC6076E5E822499BULL; std::uint64_t aCarry = 0xC4ACE3DEABA5C306ULL;

    std::uint64_t aWandererA = 0xB737A7591B33BDA5ULL; std::uint64_t aWandererB = 0xBF759AE76D3B7F03ULL; std::uint64_t aWandererC = 0xEB332445C62976F9ULL; std::uint64_t aWandererD = 0xE3E64EAD27D390EBULL;
    std::uint64_t aWandererE = 0xAA35EC4FDE0AE308ULL; std::uint64_t aWandererF = 0xFF2B825C64731D12ULL; std::uint64_t aWandererG = 0x891C1FB1E8B525EDULL; std::uint64_t aWandererH = 0x9D3D3F1CCE90E3A9ULL;
    std::uint64_t aWandererI = 0xF94616CA21812F17ULL; std::uint64_t aWandererJ = 0xC1F26BE7B6CC58A7ULL; std::uint64_t aWandererK = 0xCEA2105764F932AEULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14608397367813932769U;
        aCarry = 14231652797365184778U;
        aWandererA = 11690891722056419717U;
        aWandererB = 15666927806669724523U;
        aWandererC = 12203717353066217512U;
        aWandererD = 15550157895100290452U;
        aWandererE = 13054810315569926792U;
        aWandererF = 15424139216435501293U;
        aWandererG = 12012718851099888944U;
        aWandererH = 9578913991320960813U;
        aWandererI = 17598836475550704099U;
        aWandererJ = 18010984611818500831U;
        aWandererK = 16136585744879901649U;
    TwistExpander_Polaris_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Polaris_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Polaris_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Polaris_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Polaris::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC41A6961DA648960ULL;
    std::uint64_t aIngress = 0xB3F8DE667BC76377ULL;
    std::uint64_t aCarry = 0xA5AC71E25AE1D2E0ULL;

    std::uint64_t aWandererA = 0xA7E6A9715B465225ULL;
    std::uint64_t aWandererB = 0xD6A43ABC6F898DE9ULL;
    std::uint64_t aWandererC = 0xEFB1A12A979BFC4FULL;
    std::uint64_t aWandererD = 0xE3B135A8DF008ADEULL;
    std::uint64_t aWandererE = 0xE9F2D53FB91CA5CAULL;
    std::uint64_t aWandererF = 0xE91E9944F2162DE6ULL;
    std::uint64_t aWandererG = 0xEF23422524A7BD16ULL;
    std::uint64_t aWandererH = 0xBDDB65A115651B87ULL;
    std::uint64_t aWandererI = 0x8D578ABB6572D741ULL;
    std::uint64_t aWandererJ = 0xF821C426F161322BULL;
    std::uint64_t aWandererK = 0xA3B5E7BBDF571D8AULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
    TwistExpander_Polaris_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Polaris_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Polaris_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 24 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1797 / 1984 (90.57%)
// Total distance from earlier candidates: 41917
void TwistExpander_Polaris::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1808U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1784U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 623U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 150U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 55U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1453U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 223U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 96U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1503U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1006U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1840U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 987U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1160U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 856U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1841U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1490U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1839U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1057U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1332U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 428U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1040U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1732U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1065U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 604U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1626U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 249U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 391U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 602U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1072U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 903U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 864U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 110U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1760U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 823U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 585U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1789U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1786U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1452U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1356U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1417U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1662U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 912U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1673U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 685U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 134U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1881U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1103U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 141U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1900U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1089U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1445U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 752U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1134U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1326U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1785U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1552U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 649U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 50U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 343U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 932U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 105U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1515U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1776U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 835U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1175U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1435U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 943U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1002U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 37U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1740U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1337U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1773U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1754U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 59U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1207U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1652U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 577U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 802U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1208U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 704U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1525U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 341U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 999U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1385U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1656U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 434U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1718U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1766U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 751U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 863U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 282U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1595U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1292U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1602U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 502U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1867U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 989U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 840U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1847U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1947U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 709U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 841U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 195U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1338U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1457U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1030U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1961U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 957U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1560U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1333U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1657U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2047U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 837U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1140U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1700U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1196U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1423U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 166U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1170U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 389U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 799U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 839U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1205U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 797U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 440U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1168U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 315U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Polaris::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB38C03B38144D1BBULL; std::uint64_t aIngress = 0x9BD3BB88676D8B31ULL; std::uint64_t aCarry = 0xF9AFA9E399BF54A5ULL;

    std::uint64_t aWandererA = 0xDB34FDD4DBBD2085ULL; std::uint64_t aWandererB = 0xF54DD2C7A65AB59FULL; std::uint64_t aWandererC = 0xE7566B2FD3CAE297ULL; std::uint64_t aWandererD = 0xF4B4A00B7E17A42BULL;
    std::uint64_t aWandererE = 0xE09EFD2ED3B05298ULL; std::uint64_t aWandererF = 0xDCACE8008FF7BA91ULL; std::uint64_t aWandererG = 0xBB480C796ECEFB1AULL; std::uint64_t aWandererH = 0xA1C80F6BE3CC81BFULL;
    std::uint64_t aWandererI = 0xA4939F6E17013444ULL; std::uint64_t aWandererJ = 0xAEF52244E63ED0C6ULL; std::uint64_t aWandererK = 0xE60A6592D6061F5FULL;

    // [seed]
        aPrevious = 17927717054819852573U;
        aCarry = 12989292052448328015U;
        aWandererA = 9632816106176570498U;
        aWandererB = 13416099811020315595U;
        aWandererC = 12432912447699812905U;
        aWandererD = 16886553675093731790U;
        aWandererE = 17747537404136613127U;
        aWandererF = 14293275159742234493U;
        aWandererG = 16361627952277050433U;
        aWandererH = 16848617090651065548U;
        aWandererI = 17587636141201278213U;
        aWandererJ = 13042975097484282665U;
        aWandererK = 10573848045787697896U;
    TwistExpander_Polaris_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Polaris_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Polaris_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Polaris_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Polaris_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 24 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 12498; nearest pair: 474 / 674
void TwistExpander_Polaris::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1803U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4376U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4602U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 462U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2968U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5048U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2559U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5192U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4766U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4205U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5272U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8076U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 306U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3495U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1050U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3502U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1154U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 993U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 29U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & W_KEY1);
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
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2013U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 375U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1503U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1517U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1317U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 620U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1533U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1309U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1607U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1551U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 786U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1420U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1123U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1224U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1686U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1596U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 24 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 12495; nearest pair: 469 / 674
void TwistExpander_Polaris::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4173U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1024U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4771U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3566U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7873U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3249U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4819U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7525U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7900U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4253U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2349U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4450U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3629U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 580U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 434U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1840U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 699U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 180U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 812U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1668U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1662U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 0U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1479U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 566U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 156U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1429U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1973U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 136U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 626U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1130U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1971U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 440U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 50U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1715U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 260U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseASalts = {
    {
        {
            0xBAB837748C0861F8ULL, 0x75DEEEC27F6F614CULL, 0xA3DC8E8699C3E39EULL, 0xDD86FF79D6F9BE39ULL, 
            0xB95569DF4E80FC45ULL, 0x65AAA5EC842844E1ULL, 0xCA5943A3ED7EC5F2ULL, 0x2DA4F770496B3CD7ULL, 
            0x85B78502042E23C7ULL, 0xE1F60451B406D37FULL, 0x9F1B5163CBF6FDA2ULL, 0x499A458A8E83114EULL, 
            0x73A64CE128C8F121ULL, 0xB6B2AC46B8A87C1FULL, 0x74E2ED1204BB6DF2ULL, 0x6CDA924835E64AADULL, 
            0x00ABE75AD3717FE8ULL, 0xEB013EB1D7379BF8ULL, 0x1053C61C4D9D59B8ULL, 0xBA34CA244BC0E286ULL, 
            0x26BC6A66B343DFE1ULL, 0x4B7D34A489649909ULL, 0x4ECE924845F7C936ULL, 0x1C9D4A8CB466F983ULL, 
            0xA79A09D4BB756A47ULL, 0x6167135D23454E44ULL, 0x4C6108A7F34B2325ULL, 0x99D69820BD19FF1BULL, 
            0xB7A25328B3AE7570ULL, 0xF4FE99B75B16B741ULL, 0xE0F51E1D1513DCEFULL, 0xD7D8BBA271B65BBBULL
        },
        {
            0x33F72A5A478EC6FBULL, 0xAEAB1E20AB16AC1FULL, 0x7EBCEE0B602FE9E8ULL, 0xB2AB5E539FEC1914ULL, 
            0x57A42CC875AAF130ULL, 0xA08CC0ECAEC6DE12ULL, 0x57784DF7E08DC8ACULL, 0x8E6E0673AEFDBB14ULL, 
            0x83C3BBA5C3FD6CA1ULL, 0x831A8CBE4E294515ULL, 0xC32E6AEA426D6832ULL, 0x9C7AD592B7919624ULL, 
            0xC1258B7B66D73B62ULL, 0x47E3D4731ED64FF7ULL, 0x615ADC7AEF0751D5ULL, 0x821E9B92AAA700ECULL, 
            0x316C6407F9BD0354ULL, 0x6A46DA1C26D61615ULL, 0xBA90E9AF40A2E183ULL, 0xFD34656E5B1D12A3ULL, 
            0xB3DCB5B93AC8F43EULL, 0x26B9D71AC5D7CA1DULL, 0x3B49F9619FDBDB49ULL, 0xA57965D5F4190597ULL, 
            0x44CA66EFCEBAF96BULL, 0x7B352BC4C771488BULL, 0xDDD2CE7082498F84ULL, 0x171EB77007B44A35ULL, 
            0x6CCDB6AF6F16DE3DULL, 0xEB72B8B6467C22C7ULL, 0xF45FCAB0C6D9CD88ULL, 0x50C6C859B535A45BULL
        },
        {
            0x246D9BAA5E8827D3ULL, 0xBBB140CC8D3546EFULL, 0x8D4CEE64466C7502ULL, 0xA310023133B8F249ULL, 
            0x3B69927D5AA3658EULL, 0xF2B196836DF6BC34ULL, 0x520CD1129C88B577ULL, 0x57A495FD7F315CD6ULL, 
            0x02AC255C868290F9ULL, 0x5BC00A0306ED9BD3ULL, 0xBB6EFB7A4D41BF4BULL, 0x05BBEFA1DFE2603DULL, 
            0x53862D647848AC02ULL, 0x8A6180B183594F6BULL, 0xDBFCB0CC2CB4C320ULL, 0x5265D46F2A3BC4C2ULL, 
            0x25963BB67FFAB45FULL, 0x1E54A0C8AC2B3127ULL, 0x9B37B92DAC755E08ULL, 0x58D1D184BCC4201FULL, 
            0x910C7B27FF7A6416ULL, 0x0FDADF75C3F62F88ULL, 0xAC774185A84285B7ULL, 0xFC5E983A46C2583CULL, 
            0x3BAD84B65504EBA0ULL, 0xFEF208967489F9F4ULL, 0x4956FA93336360E2ULL, 0x6DF702CA6FF60399ULL, 
            0x0C64B63DF67E37F6ULL, 0x3E42847BC17D28C2ULL, 0x70D5EFF2797F3C65ULL, 0xBF9986B5C3E02514ULL
        },
        {
            0xF5694CCC2305673AULL, 0x4E48F6C3D6BD464DULL, 0x77813C422A6DD36AULL, 0xED58F4DACCC0F012ULL, 
            0x0B6002A9FB68E857ULL, 0x4BC31008CCDA6E99ULL, 0xA1C9D1F6E877394DULL, 0xAB502F9A8B321DE8ULL, 
            0x58AF6607757D397FULL, 0x9D0B47ECA85EF09BULL, 0x20038386EBEC16C6ULL, 0xA13E12A2842ADC07ULL, 
            0x4A28731842CB56B7ULL, 0x86E046AA7DF5B5B2ULL, 0x7DD96C90D23DC0ADULL, 0xE90FF01FE4CC8A96ULL, 
            0x2834B762D931FA41ULL, 0x71538913F675C7A2ULL, 0xC115DA567A5FB8DFULL, 0x37C9D85D7C3EC785ULL, 
            0xC201BB289B0702E0ULL, 0xEF02A9532401FC34ULL, 0x50F66E1ADA991A3FULL, 0x05F61478217B895DULL, 
            0xE226D243C022F8F8ULL, 0x3F1384E9D51A51B7ULL, 0x7140C4F9542DDEFAULL, 0x8046FF8BED5838C7ULL, 
            0xC54E37754C7F8BE4ULL, 0x71C410FBFCF2E8D6ULL, 0x629792BCC584F2A0ULL, 0x575BFE29CD90CB1DULL
        },
        {
            0xA88FF77D0377C8CDULL, 0x8A1ECDBD22802210ULL, 0x611AA6FCB59210E8ULL, 0xEBACDC6AD51D3981ULL, 
            0x9EF26E28B62EC8D3ULL, 0x9B01185F7A6919F8ULL, 0x9D499AD273FF9699ULL, 0x166D65F216F5A6D0ULL, 
            0x1884D1172CA99D05ULL, 0x168D16D98E11831BULL, 0x167B6EC44DB1F16DULL, 0xC93B8C4EA5A40DD4ULL, 
            0xE7A39EC92F8FF680ULL, 0xCB821D02EADA4341ULL, 0x15D8E78DAA28C09DULL, 0x3DC37741675D717AULL, 
            0x6FE5588039F95ED4ULL, 0x516ED111D4402367ULL, 0x44A36C93D81F212BULL, 0x24261FFC2BFD20BDULL, 
            0xBCCFE7625DA0A255ULL, 0x4459693D84E7E016ULL, 0xF5CA57DAA8CBB30CULL, 0x67A7AC23846B82B1ULL, 
            0xA8C06AF23753BCBBULL, 0x1AD40D3FD16A420CULL, 0x1723CBCCB8655F69ULL, 0x5AA2F0F2B299425AULL, 
            0x4F946CFC719B8281ULL, 0x4BE8D0DAB93F4D54ULL, 0xF6850A3BB9785D35ULL, 0x11BF92A6429CBEB9ULL
        },
        {
            0xC6E5B5E2989688B7ULL, 0xCB1A8CF348819EF4ULL, 0xCC2661223AFA7D3DULL, 0xA5D690865C747D58ULL, 
            0xFC5D80991ED5E463ULL, 0x0DE162D568EDD512ULL, 0x9B383A7FDB5DBAF4ULL, 0x9619EF899EE66E4CULL, 
            0x2082FA45896345DFULL, 0x155067FF38D6DDE6ULL, 0xD5EF20653C79BE62ULL, 0x1B6DB83388190219ULL, 
            0xFC12D0F78EF483D4ULL, 0x96A176688FE271CEULL, 0xA3C879EA8E5B1162ULL, 0x79425417170639FCULL, 
            0x5BC568081431E8B0ULL, 0x7791DA6E00C81379ULL, 0xEC7A07C5DF2B08CDULL, 0xD6DA4B77C1D69C71ULL, 
            0xD3572490F79C7900ULL, 0xFA406273907D0EBBULL, 0xB137DE132A913B15ULL, 0x34CD111195B6D23BULL, 
            0xFF10F92CED4FDE85ULL, 0x2D7CD47241FE0A5BULL, 0xD76069D228ACF888ULL, 0xFE8659A5E2751C99ULL, 
            0x8BF20BD712B9A0DBULL, 0xADEF2561CB076AA2ULL, 0x5CAF4487AEBB495AULL, 0x2C3B782DBDC2E478ULL
        }
    },
    {
        {
            0x31C8DC16809F9DC0ULL, 0x84C67B1905203BE0ULL, 0x34493BADC5577360ULL, 0x688B81515D593A0AULL, 
            0x718714899AE65F94ULL, 0x6CF462A5C706EBD2ULL, 0x5C0FF4696F389F15ULL, 0x85D45D7FE0286F01ULL, 
            0x33A4B1777F980CDDULL, 0x8271BE0125DAF448ULL, 0xA22FD26D9B779D61ULL, 0xA55BDE04EA509DB6ULL, 
            0xF8CA334B0D6A5E45ULL, 0x71BD3A8D09EDF002ULL, 0x9F8880CBE9061AFEULL, 0x01D2B2B0FF701C99ULL, 
            0x84408F15FE808D4FULL, 0x395948DC2C569AE5ULL, 0x067C04171B574C0DULL, 0x7049322A056AEC27ULL, 
            0x5C3500BA7D86B921ULL, 0x817F2962E8A87100ULL, 0xE08EB6A65499FF25ULL, 0xAF5446EABB4682CDULL, 
            0xBA802291F52281F9ULL, 0x883A487D07A6C2B6ULL, 0x463529B6A5A1CD2CULL, 0xCEF296A21996242FULL, 
            0xA0C56DFEAE822412ULL, 0x765F6A647AB01B94ULL, 0x533EF36F75C79839ULL, 0x00C159992D7F70DDULL
        },
        {
            0xAF51A1EBF5A19048ULL, 0x54B559261703AF9FULL, 0xCDEEE2459783FBF2ULL, 0x2D8C484A70CC822EULL, 
            0xF3BED88A16B2B026ULL, 0x4E5B95AD9D03555EULL, 0x0657AD0544103DD5ULL, 0xBB91A3E6E863466AULL, 
            0x32F6AAC59752A757ULL, 0xCC386E2F699F5DD0ULL, 0x8F4CFD53EE0AB70EULL, 0x6C1DC7B52AF2078FULL, 
            0xCC42195A5D979E4DULL, 0x40F35AB369A26758ULL, 0xC22C6E7EE73848ABULL, 0x27AAE6E5AAFEF58DULL, 
            0xB3F8B4FCE7794138ULL, 0x8FAE8ADF7801F891ULL, 0x3DC448A64E5FAEAFULL, 0xDCEF76EF014B6DC6ULL, 
            0x753496EF6D06A483ULL, 0x055CD44AD683FB5CULL, 0xF3C7223C37102FB9ULL, 0x43F790C56701F058ULL, 
            0xA57BAA03EFCA9543ULL, 0x0D38B839F2D7C1E4ULL, 0x06F8BE9A2EAD7112ULL, 0x0C97CA1907AB7A88ULL, 
            0xDDB6DE6C7A83E9D5ULL, 0x0CB46BD9887FA41AULL, 0x156BF5898942CBDBULL, 0x6A7A2DA73DAB1519ULL
        },
        {
            0x03905B3BC5D08F0CULL, 0x4F949269DDF81FC7ULL, 0xF8EAF1B6EF313A0AULL, 0x13BE509615DF9F08ULL, 
            0xC58624AFF069CD02ULL, 0xEC860DD52C2B256CULL, 0x3C8585AFC39D0624ULL, 0x80E4BC3A78EDF2F2ULL, 
            0x34872E31AF042809ULL, 0xDD2EFBB10B376BA1ULL, 0x0488AEB8FFD89594ULL, 0x9E32ABA1A3AA6312ULL, 
            0xAA14042D0E3B2646ULL, 0x129FFEC44C80DFB5ULL, 0xF70896BFFCDA7B13ULL, 0xBB3F6EACA4B996FFULL, 
            0xE27AC10A7C03C1B6ULL, 0xCEB19E49D48D7FCBULL, 0x07A7598C19A787B6ULL, 0xD5B76500C4D24D43ULL, 
            0xD82EB16490DEBADFULL, 0x5A91BF02D264567BULL, 0x4D66636CEA7B269EULL, 0x82F98CC550348F02ULL, 
            0x21412F6CB7DDFB22ULL, 0x5728A2F164A8B113ULL, 0xEF2D188AAAE774A6ULL, 0x6666DF07D4A48A7DULL, 
            0x16F8028000303858ULL, 0xB8D8C475D60DDACBULL, 0xF5E8D2FB5A93EB1EULL, 0x8EF7DC0706031D21ULL
        },
        {
            0xC557DFD1B2746D02ULL, 0x578C1C332E3698E4ULL, 0x4CB2FCE5557434CEULL, 0x1A04B72E67797A84ULL, 
            0x8F7A9330712F849EULL, 0xED4A82D7C2984377ULL, 0x81BF2343E12B9690ULL, 0xA8827CF7B76C5233ULL, 
            0xF6705ECCFC1DD981ULL, 0x0C09A9C374980439ULL, 0xFF866F3FA6D44EDFULL, 0x65DAF6E5F6016C65ULL, 
            0x93BC2C168A4CDEA3ULL, 0xD79BBE5F71302569ULL, 0x1A97A6645ACEA54BULL, 0xE9F32EDDA27E3C4BULL, 
            0x85DB52B127346D08ULL, 0x1CBCE7F46FC9BC32ULL, 0x7B3701E1AA03DF5BULL, 0xBA80AE9A9D74EAB3ULL, 
            0xDC7CD182BC5DBBABULL, 0x7CC53BAE876D7576ULL, 0x245E37F379CCDA09ULL, 0x7A53AC8E351F7CE0ULL, 
            0x2146FBE8F9469131ULL, 0x7436FA68B9E7C5F5ULL, 0x48784F531F0E3879ULL, 0x7ACBC885733ADF32ULL, 
            0x6A37075C6497BAABULL, 0x5FE85243E8B7E155ULL, 0x22F5DCEAC0450439ULL, 0xEE708F8ACDF6D1B5ULL
        },
        {
            0x9BF366E0B29BE452ULL, 0x6933F4DF23DFD429ULL, 0xEF625A89A3C9A157ULL, 0xB16F6D646E15BB93ULL, 
            0xEF565EEA43D0B0C2ULL, 0x3EEA0057B19C509CULL, 0xADAE5804F738A932ULL, 0x21E50281959BFBCBULL, 
            0x3B1B9DDA56F9AAD7ULL, 0x024153534817A0EFULL, 0x2E022DDDC128B480ULL, 0xA482A6D3E5E7EF34ULL, 
            0x1A4198B1C85882D5ULL, 0x2ED7A2B8822C6F00ULL, 0xA97630CC2BF207B9ULL, 0x24D958A41DEC37C8ULL, 
            0xA18A85DE1BC75248ULL, 0x3A0CAA56D6EF5D02ULL, 0x428372B27772D757ULL, 0xC2520A2B97121094ULL, 
            0x2CD52CC0CC8FBCC4ULL, 0xD7E28F14272D3171ULL, 0x49383B0A0EF25AD2ULL, 0x46256FC6D7CE43B6ULL, 
            0xB41CF767284B2D28ULL, 0xCD142F1C311D3F13ULL, 0xE991F9B7B7BE5595ULL, 0xF5870BECD7570AA3ULL, 
            0xC5EAD73F3507CF3BULL, 0xCD41CBA990921C14ULL, 0x802260503400D953ULL, 0x889DA28C6EF32733ULL
        },
        {
            0xAD01E423B56ACAD1ULL, 0x706F149394BBF2A1ULL, 0xF691CFDED2B99006ULL, 0xB36D9BA2F62A1BB0ULL, 
            0x71B1B202D20F8554ULL, 0x58BD15849C1AE5C0ULL, 0x92AA84E6FB6EAB4EULL, 0x8A0DE158DD383A1AULL, 
            0xB320DAA05CEA784DULL, 0x06B216256A150840ULL, 0x243279370EEC1E50ULL, 0x2A6FB42191FBB380ULL, 
            0x07C75CAD5D5B437CULL, 0x217791319C0B48A1ULL, 0x09FDE3064AD9378DULL, 0x949EC39440D62AC4ULL, 
            0xB91A02D65E2CF891ULL, 0x2E538986E68432E8ULL, 0x35D12FE77B8F0D88ULL, 0x2E4B1801CAC1FF1FULL, 
            0x7490D7F081E14005ULL, 0x12DCB0BDDEA79B80ULL, 0xE7676E7F5CD99759ULL, 0xEDCE94CDB8077CB8ULL, 
            0x66D13C369DD88D22ULL, 0x3F50099426D00B6AULL, 0x675D15D4E4C770EEULL, 0x9F3E5816815AF14FULL, 
            0xB3DE72719F3DAC80ULL, 0xB0AE2469AD62F45FULL, 0x4719730AD3DA7EF1ULL, 0x1D00439585B50BC7ULL
        }
    },
    {
        {
            0x72595DBD2A9485DEULL, 0xE4509989AE96DE36ULL, 0xE2BD5367026455F5ULL, 0x2C71E3F1D4D79DA7ULL, 
            0x1519830727EE6D9FULL, 0xBB44CD0860CFADD3ULL, 0x646EF4B13764FB52ULL, 0xF73642CDFCC4D013ULL, 
            0x54501F4F35467BC3ULL, 0x6D54EF314D1F2DF3ULL, 0xEC5BDFD4D72AE042ULL, 0x5B49E4C076CDB23BULL, 
            0xA27CA7E116E91029ULL, 0x4223CAB5150F18FAULL, 0x286B62ED8E0D087CULL, 0x665AFCAFD9DF8975ULL, 
            0x406E5019DA546893ULL, 0x000984BC30C03EB5ULL, 0xA97B4BE2FD6D2A98ULL, 0xBBC488E75EDA4329ULL, 
            0x8962BF4950A4CE77ULL, 0xFB25AA03B1286C18ULL, 0x90720EEDFDBBD2C8ULL, 0xE2C8A3C51C0B8AC8ULL, 
            0xBED3D214EDD80C8DULL, 0x857CFCB500C30FFEULL, 0x80403813124306CCULL, 0xE6A885FE279F00ACULL, 
            0x60B2B6FA9217F30FULL, 0xCACAC8BD93333035ULL, 0x048C3BEAFDAADDD1ULL, 0x5A3FE22B09F0A2D4ULL
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
            0xA31A736031BCE4F8ULL, 0x517C290DE5C58FE0ULL, 0xEE85BAA1EE4E1996ULL, 0xDFA069C150933634ULL, 
            0x63D0AB005F71BDDEULL, 0x3F2F0523E469EC4FULL, 0x1EFBD63907F7C4ABULL, 0xB42EC9DC8A444338ULL, 
            0x3C256C60FBBA0E82ULL, 0x05FED94D622F019AULL, 0x5F0373A661E3497FULL, 0x140E51DCB0FF7089ULL, 
            0xC70A930477CEDFB0ULL, 0x82AEE62116D25A8CULL, 0x1BEBD32D45CF8BC7ULL, 0xF3F9865D1CAC4994ULL, 
            0x48E6D671C5EA754EULL, 0xC652D29A614D4870ULL, 0xAA8AEE273C28D00AULL, 0xB0DD213C6547E510ULL, 
            0x20A85702BB22A8F0ULL, 0x7C65DE5340E65540ULL, 0xE7D0325FCF27E45AULL, 0xFD7CBED8018108CAULL, 
            0xABE8D012AC16EFE4ULL, 0x0B62997CEB3D162EULL, 0x0375916E9EA47C9CULL, 0x6DD11B7016439145ULL, 
            0x1DA40F3BFD8ED07EULL, 0x1028E7C237C4CC64ULL, 0x18D52043725C10F1ULL, 0x5847E3EA3DDF17C9ULL
        },
        {
            0x2D77E57A610A0E88ULL, 0x6130A1FC1B40D8D1ULL, 0x2AB230F14DE409F3ULL, 0x948E014C1B23BADFULL, 
            0xD0C398833FD22803ULL, 0xF5A53646F1566394ULL, 0xA2AE62DA58EAE009ULL, 0xCC3B997D0B3D5204ULL, 
            0xAF5976AC3597E492ULL, 0xB81C56EBB35ED16EULL, 0x59C48D70AA325275ULL, 0xC01F8EE2239D1C8BULL, 
            0x10790127D30712BFULL, 0x410ED7AA7D37781BULL, 0xDB44B1AF37810E15ULL, 0x4C203EA38BE6FD3AULL, 
            0x5A7D6B723ED725F0ULL, 0x0E533FC821A39C77ULL, 0xB70D24F66FEA1393ULL, 0xF7711495B0E85534ULL, 
            0x4F69CF1DC10C1C6DULL, 0x7EB9A645A28BCD13ULL, 0x1E219EDF090E86A0ULL, 0x92F0DBF43A4F79A7ULL, 
            0x3D1B87EE1AB11B5AULL, 0x968582B04DD71667ULL, 0x3BAC26542A0A965CULL, 0xE6CA89272B95AE9BULL, 
            0x0011ED7F0441B8A3ULL, 0x24B8D494D885DF6CULL, 0xF848D4FD1FFECA9FULL, 0x2F8A86196858A8F1ULL
        },
        {
            0xA3C40333A6C0FCFEULL, 0x76E0FDD60A88A61EULL, 0xF6BA297276C09DA9ULL, 0xE810227EC9BE91A7ULL, 
            0xE938A7617EEB675DULL, 0xB73A198B0F15B5B9ULL, 0x07B0099B00A50D2CULL, 0xD0CA55F2C384695CULL, 
            0x8733CB3E8C03431CULL, 0x8A314D6D6DC18997ULL, 0x4ECFE48B08652530ULL, 0xE6C57528579AFB78ULL, 
            0x1D3EF819836F7E5AULL, 0x0E7AD8BCBDF1F85BULL, 0x3DBDEF36E009EE9EULL, 0x4852DAF349EB8E39ULL, 
            0x02C7C5984298FE78ULL, 0x9B2B6FE23707A107ULL, 0x5110649673B37EC6ULL, 0x82470BC33AC8BADEULL, 
            0x1FFDFE3AB4DC3501ULL, 0xC17E550E4777DA5FULL, 0x917670D64DACBF92ULL, 0x1A477C58655E15C8ULL, 
            0x6C1238DCC300331FULL, 0xA34F6064D46BD5FEULL, 0xB8460575A9A0D9FEULL, 0x4459B244E3CAF4D0ULL, 
            0x3D261CBAC369E019ULL, 0xCD3AB67BABD91F4FULL, 0x54C295BC8496C9FCULL, 0xF120BFA2E3DEC667ULL
        },
        {
            0x5685F9477B4C781EULL, 0x17F15D3F941A8C48ULL, 0x489786C414E47F72ULL, 0x8164DC39DAF747AEULL, 
            0x14BD11EF03E924F2ULL, 0xEE793CAB2CEE835FULL, 0xCE13A6EF88827635ULL, 0xBA6FE55A342D2364ULL, 
            0x2A0B9B379EA56469ULL, 0x15137CA8ABB8AEE0ULL, 0xA2A6E0544BF3489EULL, 0x6CAE6EB2D3960A6BULL, 
            0x04174C3B1A020B31ULL, 0xF494CDB72D7F8861ULL, 0x257CD4EC867E0B3AULL, 0x7A93C5E347D9E047ULL, 
            0x3A922FA2E6B10505ULL, 0x554396DD2F8DB3A4ULL, 0x9CF5C1F8E9D85828ULL, 0xD2880EEBE34B9C5EULL, 
            0xFCA5FA30F526A1CCULL, 0xC36479E81E7E26A0ULL, 0xE377339AF0084B5BULL, 0xC5C08A0D2D216115ULL, 
            0xFD451C71C9EFE65CULL, 0x3D201A7D6AC9B30BULL, 0xDFD804A738FAA063ULL, 0xEB198F71691408DFULL, 
            0x843BEA88680BC759ULL, 0x15C4ACD89EB92758ULL, 0x0EB818AEA4849DE4ULL, 0x9D3663B76FEFE7FDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseAConstants = {
    0xAD19DECBE2C5B888ULL,
    0x3913B9CA057CCD06ULL,
    0x2F43E980E421DA4DULL,
    0xAD19DECBE2C5B888ULL,
    0x3913B9CA057CCD06ULL,
    0x2F43E980E421DA4DULL,
    0x47B5ECA037588AF7ULL,
    0xC86CF1C10921A934ULL,
    0xC3,
    0xCF,
    0x99,
    0xBB,
    0x01,
    0x20,
    0x1A,
    0xDB
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseBSalts = {
    {
        {
            0xC4D87C55D507D639ULL, 0x63E68B016B3DA930ULL, 0x4882DA85F2042AF5ULL, 0x3A7277DFC947478AULL, 
            0x6ABD0A86ACD55138ULL, 0x46D94265C4DC18C0ULL, 0xE8D6350B00368FB7ULL, 0xA7DA60FC2839673BULL, 
            0xBFDF2345B855144BULL, 0x2E6D74F61892E761ULL, 0x2266C96AD58FFF18ULL, 0xEC21831FD55B7BA2ULL, 
            0xF00A436A5B39D832ULL, 0x93B333CD8F24BA89ULL, 0x851FEB7DDF1EE101ULL, 0xEA0C0C58AC4BF3FCULL, 
            0x9A576694D0A64ED3ULL, 0x40A4D041DEA46B10ULL, 0xF5159EB41EE74A1CULL, 0x1687C2202C9BB5A0ULL, 
            0x4F883D9F17839387ULL, 0x4C385FD87C4D47B4ULL, 0xEC71EE7999895AC4ULL, 0xE4FCADE5F5A1BA3AULL, 
            0x827954492B5289E1ULL, 0x684CA84BE225F4B0ULL, 0xF5B5045A48D64B74ULL, 0x4EC08CD46EDD0324ULL, 
            0x03D1352133C93FBCULL, 0x559809214F32728EULL, 0xCA2FEE248BA2BBBEULL, 0xDD12903C3C990C68ULL
        },
        {
            0x03B0626F66AA1579ULL, 0x50AF91FAF05C684AULL, 0x5326B1B0CA046B2FULL, 0x330656983B8094F5ULL, 
            0x054661E79F101FADULL, 0x7C493C34F6081D45ULL, 0x616EBDBEAB362510ULL, 0x2E263F376D8E5CADULL, 
            0x73F82B46FAEE86F2ULL, 0xFE149B2D35C0A261ULL, 0xA778F0030F56A3AAULL, 0x763651D040468DBFULL, 
            0xA306F25219102878ULL, 0x2405316CA35C61B9ULL, 0x0A686C6E8E4DA774ULL, 0x4312558324A08E9CULL, 
            0x9EAE0D426F08C3C0ULL, 0x9B6828A71966FAC8ULL, 0x687FEDA69342B20AULL, 0x40650065FDAA8859ULL, 
            0x2B6D13DFA1790C47ULL, 0x17DC3E66791C7FAFULL, 0x174197003F05749EULL, 0x413582F581767546ULL, 
            0xDAF2D5BF843F8EEFULL, 0x16F7F8E8374C769BULL, 0x3BBB379CDEEBED02ULL, 0xA3C4E587DC34A952ULL, 
            0xCF0BC848A8983F08ULL, 0xCB5BFC6CD1803106ULL, 0x0034070894916F32ULL, 0x6037EEE7AFF31F78ULL
        },
        {
            0x1C3950106B37CDE1ULL, 0xF6D52CC6D9131DFDULL, 0x1E073E5979DA8F00ULL, 0x9EC929958546BB72ULL, 
            0xFA97EBF99857874BULL, 0x7522178FF8290CBDULL, 0xEDE616AF999F3E23ULL, 0x8AC6326ED40706E5ULL, 
            0x0DD66593A51FB0E4ULL, 0x4D95E300C18EDD47ULL, 0xC2B74FE9F7C91BBBULL, 0xE95CFE21A9556718ULL, 
            0x568E0986960C1570ULL, 0xEC301A37B195750BULL, 0x6FD69D7904E251F6ULL, 0xE0F3C124EC909EEFULL, 
            0x2B2BFD3139A4986BULL, 0x6DE7842BED001E2BULL, 0x240EEDEB30A3817EULL, 0xA2254664705E19D5ULL, 
            0x8D17ED1D08BEB890ULL, 0x36E4C2F53DE3CAB0ULL, 0xD9808BD161FD70FCULL, 0xD4770D528038BC89ULL, 
            0x96C68D81672B1483ULL, 0x13E21A1CEB62AC36ULL, 0x940F0A92F888187FULL, 0x2E0EE8334F21FD13ULL, 
            0x6098452D3D278156ULL, 0xC80E77CDD8939A0CULL, 0x2C3EE2947BBC195BULL, 0x5A0FDCD02F1481CCULL
        },
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
            0x412EA82A0125001BULL, 0xDC33368D915BC0C0ULL, 0xB6E50D1F88E1575DULL, 0xAC048CEFEA50EEA3ULL, 
            0x5915142693A21C10ULL, 0x07EA26AF1EABADC7ULL, 0x1FFC86C6AED4C557ULL, 0x5E26587C16D3C986ULL, 
            0x984B4199F5A0A154ULL, 0x0BF7F525146F221DULL, 0x78C455C5BAB5FC1FULL, 0xF20519710B728460ULL, 
            0x863C2FE70D32AC90ULL, 0x9479726E404A06C7ULL, 0x16BD58F6BC37EEE4ULL, 0x0604C0E9E3296022ULL, 
            0x93B4403BE4BD11E8ULL, 0xD4504888F36107CFULL, 0xDB4468F0051C27ECULL, 0xE6C76246D9DBFC04ULL, 
            0xC2236AE2CF3A1A95ULL, 0x3BA375DD87333D70ULL, 0xC40EFA1268919799ULL, 0xD99A6BCC57B3F133ULL, 
            0xA4B542882B4C90E4ULL, 0xCDAA6307291AC3FBULL, 0xC25269D0D30D49F1ULL, 0xD41548986A64E7BDULL, 
            0x2E96C026F58703B3ULL, 0x7680C927F2C06CA1ULL, 0x310FDFC239F2A3FEULL, 0xDD417275E1475E5DULL
        },
        {
            0x5A9BE5454FACB7E0ULL, 0xA24D9E3D250674ABULL, 0x7C2330AFBA0AA406ULL, 0x753B051499A72357ULL, 
            0xDAEC46D69DB90C5AULL, 0xF0BEC19D1782F6ABULL, 0x30CB45CEF8E36EA7ULL, 0x2D14CBE309651274ULL, 
            0x35FAA2F666F7D491ULL, 0x4C92E9804FEFF442ULL, 0xF1A70DE2F0336070ULL, 0x64BFDEECDD413226ULL, 
            0x6F2E4FB2D24D2342ULL, 0xC42E8582AB26F246ULL, 0xB90826AD511B798BULL, 0xC628CB5518ED54C4ULL, 
            0xCDC31F32B7CF159AULL, 0x64B09A7E502F0322ULL, 0x5D9C9B3151D5E638ULL, 0xA73B41A0029A7EC4ULL, 
            0x1E6F0B3375109015ULL, 0x6F3B62947F6E78AAULL, 0x3CB6B60BD200B80CULL, 0x198E5F93AEED72A2ULL, 
            0xAE4457DBF8FE879AULL, 0x43C9F7A5019A4003ULL, 0xDA32E6EF42AB3170ULL, 0x7AA2E85DE47BADEEULL, 
            0x06F7317B2A66643AULL, 0x1C42F70DF392D403ULL, 0xF812E55CF2E2C8EDULL, 0x38247EAA9862E92FULL
        }
    },
    {
        {
            0xD65BCD9B60AE4BE7ULL, 0xC02B648D4560D821ULL, 0xD7784118A8F40B86ULL, 0x142F279AEE06EDC3ULL, 
            0xDC7B0AD28231A8A2ULL, 0x4DFAF471D8E4CFE2ULL, 0x1F137851833AF1AFULL, 0x69A050A4FD13DDF9ULL, 
            0xA6EB442D2476F712ULL, 0x1A12B631432F48ABULL, 0x5EF3756747CC3E17ULL, 0x3BD02D9BA96A87FCULL, 
            0x9E6653907198400DULL, 0x48D7E073D1009094ULL, 0xA72EA30D57F804C3ULL, 0xAE114EA16F60D911ULL, 
            0x1239722083DBF4EBULL, 0x891CCAA685445315ULL, 0x90B5EB2CC3267DBDULL, 0x15DAEB287C891CF2ULL, 
            0xFCB15A6ABE9D33EEULL, 0x81C45556ADBE8009ULL, 0x4827BE9AACB59184ULL, 0x3273B3B548A05B04ULL, 
            0x833D52E9F395B374ULL, 0xE82DCFF92399EACDULL, 0xAC3CFB1B8013C783ULL, 0xB7E3A1E506B8746DULL, 
            0x2C43F81C6120FE90ULL, 0x4C6990EBBCE6F48DULL, 0x93381B1A77C1146FULL, 0xE7605F963DBFA15BULL
        },
        {
            0x633BD8E747E732FEULL, 0xA68A212B99C51CE1ULL, 0x225353ADB6840D19ULL, 0x2091C317105A9A09ULL, 
            0x74B4BB36675ADC90ULL, 0x8131AC02A1FE95D6ULL, 0x072671ABE7DA07B0ULL, 0xF135E28995F991F7ULL, 
            0x763CFE47B95E7E45ULL, 0x6C5E14E50FC130D0ULL, 0xD0D1DEE655C158B4ULL, 0x9A672E923ECAC08DULL, 
            0xAC50D25A1E32923DULL, 0xBBA619E9869B1E4FULL, 0xFCE64179479E0B29ULL, 0x1F26B97D880D07B2ULL, 
            0x907F14B18F53BD16ULL, 0xF9C8CE069529B6FBULL, 0xC26196DAB58195AFULL, 0xCB2B142F38C4C041ULL, 
            0x1821A21BC82D5D1CULL, 0x4F2B4A17C32F2E73ULL, 0x4028FEAB235710C9ULL, 0x9A6FDD26F7AC200CULL, 
            0x877C44BEE0A7A94DULL, 0x74F59538D5C9A1F5ULL, 0xC2A743DAEEB6A6B7ULL, 0x406CFC4F5B52FAC8ULL, 
            0xCC52721F07ED599BULL, 0x0BF8947EFF8EF02DULL, 0x672403E9AC712287ULL, 0xDD6796F63189C658ULL
        },
        {
            0x7348E83B2CE26A2CULL, 0x63A41DE7803DAA59ULL, 0x66060239E7693C23ULL, 0x9C9595BC186FB62FULL, 
            0xB97962BA68805833ULL, 0xF3B5A2F0192AEF2AULL, 0xC97BBA85F9A117F8ULL, 0x26297F87D77DEC3AULL, 
            0xBA05FE3303B94E26ULL, 0x5B3236C8D1FEBC7EULL, 0x2A4161442D64C7A1ULL, 0xCF29D4AFFFA834E4ULL, 
            0x0AFE7043713C1A1BULL, 0xAFE1505D189471C6ULL, 0xF85DF3AB31A10EC6ULL, 0x19C0CC562462ADF2ULL, 
            0x367E24687B1FAB2FULL, 0x5CF6B1E09B1716EDULL, 0x8DE993F448CF93F5ULL, 0x2000A06F7F4AF81DULL, 
            0x37172AB585C49362ULL, 0x0FF21DB9918146E5ULL, 0x937F06AD58D03DEBULL, 0xC526B868D60E15FDULL, 
            0x54D08E2EFA6FA240ULL, 0xEEB54486DF112E0AULL, 0x606E642B3DC6B77BULL, 0x36C0D6E45BAD2646ULL, 
            0x5B813C31AB463EA7ULL, 0x4CBF0FFEA0009D84ULL, 0x7E45C150371ADA95ULL, 0x81B2FCB03D7331A2ULL
        },
        {
            0xD8C6F4EEEB7D82C9ULL, 0x235057F0BC21D879ULL, 0x55F2BA585AE87AA0ULL, 0xF199AA32C2FF9BB0ULL, 
            0x8A8F76DE86B27FA0ULL, 0x9589535445B921FFULL, 0xDC3ACC0A15B7A518ULL, 0x17381ED0276D5302ULL, 
            0xCEF3DEC6F6EA863FULL, 0xDD511F3EDC7F5300ULL, 0x550F0C5F50C29B36ULL, 0x567C6D73F67C2AC6ULL, 
            0x8186099D7958EBEDULL, 0x76E853B4B09AA7C1ULL, 0xCDAB51BF92FBA2B3ULL, 0x1861AD874EF90EC6ULL, 
            0xA5462C27E6FF917BULL, 0xB0A2DCA864E3E26FULL, 0xF993FCCC4C54F6BCULL, 0x2DC782FEDC128D25ULL, 
            0xC3C8CCD54382C545ULL, 0xAB5A3670B23815A5ULL, 0x65542E838B097305ULL, 0x511245FA1CF383CBULL, 
            0x09F77966D332BCD8ULL, 0x2E586C13CE29F99CULL, 0x94F59BC32A14C0A4ULL, 0xE4C4C0B3898E0AE2ULL, 
            0x59B728CEB5EA5F9EULL, 0x009774BC580C992CULL, 0x84B57E32C8F1C276ULL, 0x8593D4B9D432B641ULL
        },
        {
            0xD12FCE3C8994AF03ULL, 0xA77945ADB3D88DC8ULL, 0xACB6C07EE1E03F69ULL, 0x0C1204E51C908BD0ULL, 
            0x1C15A855825B7027ULL, 0x2FD0235EFA4D4F32ULL, 0x82A9B0D68D50E036ULL, 0x99A24EB831646338ULL, 
            0xA2BA6A25BA4344F6ULL, 0x814CF54EDEBD1CCEULL, 0xECC21F6571FCCD80ULL, 0x119B9E6A6ED6016EULL, 
            0x9743B4E1B2CE0B6BULL, 0x83F092544F45844AULL, 0xB8F8105DFCC2A207ULL, 0x3C41B12833205090ULL, 
            0x9A85A53CF9F55CE4ULL, 0x248B6A5CE80606BDULL, 0x736F1C9EF15272D0ULL, 0x9E4079E884D9DBC9ULL, 
            0x40CF7A3A91957E67ULL, 0x4F48E56A40ECA1F2ULL, 0x5ADB998E813F05E3ULL, 0x45EEA741326A6F30ULL, 
            0xD2D05C09F491DC29ULL, 0x26B74858EEB06FBEULL, 0x1A8A281BA16CBA26ULL, 0xE0E7B86AAFC2654FULL, 
            0x21AE18D518125E0AULL, 0x41176C3C78DC4A33ULL, 0x6E7F8037DAF2D965ULL, 0x9F47168173412F66ULL
        },
        {
            0xBF1E5E001D0C15B6ULL, 0x0628A47F44567D50ULL, 0x330D9B537BBC68FFULL, 0x61029DAC1CA705FFULL, 
            0x1B75D01A0C885D9EULL, 0xA1ACCCA3F038676BULL, 0xC107D292CB4ACFD9ULL, 0x63F28B16C76D442BULL, 
            0x963588F7C3F007F3ULL, 0x6B4BB264D816C559ULL, 0x6516D85CA54E450EULL, 0xA319125ED18B7A10ULL, 
            0x36858216364A8F96ULL, 0xC5F7F2D2206A7ED9ULL, 0xBAC76423042C1B27ULL, 0xAF9EDB4E4502F73EULL, 
            0x4799457202DC44DDULL, 0xDFBA2C526D75C725ULL, 0xDD08E35E34094D67ULL, 0x9E37C83AD8AFEB3AULL, 
            0xDBA9B890F60B8023ULL, 0x431058065B3CBD39ULL, 0x040E5ACC2CDB6B29ULL, 0xBF47D7D7D13FBE71ULL, 
            0xE09024CD48212C32ULL, 0x09608652CE990159ULL, 0xA3393321D23037B4ULL, 0x168E803EB2F47225ULL, 
            0x7873FBCA1AC200B7ULL, 0xDCC0DA6C726F33F8ULL, 0x1022ABC64AC121FDULL, 0x4CF578E05964AA06ULL
        }
    },
    {
        {
            0x87481FFD387E86CBULL, 0x3E2D177DD1863AD6ULL, 0x8024E0030178DDAAULL, 0x09AA4E2B9BE6D4FBULL, 
            0x91C3703973B8481FULL, 0xFDE82A1F67625CB5ULL, 0x9084F4079B1C4814ULL, 0x6F604E2BC5579295ULL, 
            0xDEFAD6B5B0780852ULL, 0x425504F967988AA5ULL, 0xBB60BC72C0664CF4ULL, 0x689813B796FE2C11ULL, 
            0xEC6F6BFFD183E01DULL, 0xED0BAFED94FFB71DULL, 0x853F0FEF03C3C9FBULL, 0xF4F1AEC44C7A99BDULL, 
            0x22C1DDCFF70CE9DFULL, 0x3E156132ECCF8C6FULL, 0x5E669AD63126250AULL, 0xD2F2A74840C764B2ULL, 
            0xBE33D7B01F9B9669ULL, 0xAC702B3005B3E56DULL, 0x1D800A67392A1DF0ULL, 0x3561D0E8996025F0ULL, 
            0x9DC944551A4AC613ULL, 0x432C57FBFE530CD0ULL, 0x62441D52D163D732ULL, 0x498404CED797FC1CULL, 
            0xCFE1473CCF5BDE37ULL, 0xB5C2536058170186ULL, 0xA5D9EFC68C6F0FFEULL, 0x154B17202C42B849ULL
        },
        {
            0x80D57C624E65FC22ULL, 0xEEB4D7E2AB24D01FULL, 0x0919D5E22F261D7DULL, 0xE6690CD19804D5ACULL, 
            0xC4BE1E9C0FBE1D4CULL, 0x1A4D636004B9F0F6ULL, 0x13B12586915EC6DBULL, 0x3D0D4763205A8AB9ULL, 
            0xD21FABA646292E7EULL, 0x53A7BC7D26441906ULL, 0xB108DF28F9651E37ULL, 0x1F8601541C6A842EULL, 
            0x3F54DA64E3995F85ULL, 0xB20E13E1996F0EF6ULL, 0x2D4946DED38363ACULL, 0x28B9106E539968DFULL, 
            0xDACBCCF06BBC27DAULL, 0xF113B2411788877DULL, 0xDFA38DC96BEEAEA2ULL, 0x3C31AB07038F03DAULL, 
            0x83E172BA2A9A067EULL, 0x87AADC4E462FB2C6ULL, 0x76CFE11FAC693795ULL, 0x7939CAB39ABAA8CBULL, 
            0x0806E7EBB1B7B56AULL, 0x8BB9A826C2A09CB5ULL, 0xB0DF094BDE7EF824ULL, 0xF3346309F2CFF53DULL, 
            0x811D67D1226B2C09ULL, 0xF816BA92BABEAE49ULL, 0x3CA3B747E3C64968ULL, 0xACD5FE36CBE61288ULL
        },
        {
            0xB42842B4E145C929ULL, 0x9A52C1AC81882A41ULL, 0x0E312985B3E60A7CULL, 0xF3DB2EEF3B216E3FULL, 
            0xF5FE9A1F7764621AULL, 0x9ADA0E8981839AD2ULL, 0x1A4A1981AFDEB8FDULL, 0x631DAD6BA514FF9EULL, 
            0x366675E9E9AC8DFAULL, 0xA15AF4EB29F6737FULL, 0x2B32BA2837118479ULL, 0xABD64401BA6D206AULL, 
            0x19CBD8AF725EE21FULL, 0x3AFD98D507C1528FULL, 0xBCAA6189E883133FULL, 0x49D0684813C6435DULL, 
            0xE555C3BE0E7AC499ULL, 0xDF1454C1E97813A5ULL, 0x89E8B64528E719AFULL, 0xC6C0D0E1E897B8EDULL, 
            0x732DB7A45377D07CULL, 0x6A1E50A93F23E497ULL, 0x95D71D25FD725DCBULL, 0x47AECF94BADFEBC2ULL, 
            0x1DE80FDAB0DB2E87ULL, 0xE4F0479E863CEF5AULL, 0x55E782AF8C9F6818ULL, 0x2CD9B372B6DDE926ULL, 
            0x378BE7D6A7F254BBULL, 0xEE258B45377DFF6FULL, 0xB4E03780EF30B0BCULL, 0x8348CB83CA77B7A5ULL
        },
        {
            0x89DDEFD1C8BEE383ULL, 0xB5CC6597CCB8FBFBULL, 0x53CF0B7DF508EF98ULL, 0x6E227B22395A76BCULL, 
            0x71BA5C5FA248690AULL, 0x88A37C1A72DE1F55ULL, 0xC4239F8BE6211699ULL, 0x92207564C3C5D73EULL, 
            0xBF8D17FDBD78D649ULL, 0xED14A203D55D1897ULL, 0x13013A4900755E3DULL, 0x53B47118A5F690B2ULL, 
            0xF8355DF111B55DD0ULL, 0xE05D317CD943FCC6ULL, 0xFFE6D5A07BDEB370ULL, 0x879C22BEE9F2AE87ULL, 
            0xB897DFA0C6B02DF1ULL, 0xFC88B2BB8E23F4FAULL, 0xE44D9B57CB955045ULL, 0x4FD6BD236E0E0839ULL, 
            0x1E4323EA8DE5E77CULL, 0x84C5C8FDFF5F96E3ULL, 0x48EF64D90C65AF1EULL, 0xABF0098FE4145EFBULL, 
            0x4C88D71E68608BCCULL, 0xC371D2C1AE45AB15ULL, 0x096975EE1E387BD1ULL, 0xC4085E47757A0893ULL, 
            0x744BA5F6663AF288ULL, 0x7364A5284322159FULL, 0x6191CC63F35EDF6FULL, 0xF70A7A33F127BF4BULL
        },
        {
            0x7C59F919A7DF991AULL, 0xAA8493D3B7AF600DULL, 0x1E9CD84EA7534DAAULL, 0xA623468EE97F196CULL, 
            0x2EDA7311DDFD6DDFULL, 0x57426CA82A9DAED5ULL, 0x3255A206D7A13688ULL, 0x2ADE3BE154F1317FULL, 
            0xB4819412C7358984ULL, 0xB5874B5EFF94B7B4ULL, 0x751B951247E3E2B9ULL, 0x5E60F1F3214F5B97ULL, 
            0x8DAC9FB6212239EEULL, 0xAC07247CEB885E13ULL, 0x20ECB0E465861C58ULL, 0x3B3594B491A19827ULL, 
            0x34A42C71F06BEE2DULL, 0xDAF67B5E7A32D449ULL, 0x62BA51375115B25BULL, 0x13280C3B412135C5ULL, 
            0x2BBF697901B73B40ULL, 0x469A83AB7CFDF777ULL, 0xCAD5F946C5C3B014ULL, 0xC2DE4F73F96DFA35ULL, 
            0x65783EF73A2F6E08ULL, 0x280D329DA61B6A5DULL, 0xA7FD798A4F1A7349ULL, 0x8D790E23307D4149ULL, 
            0x426383934443C1ACULL, 0x015CD90F8EB463BFULL, 0xF2ECBF4A272DAE30ULL, 0x650D1C02290FF272ULL
        },
        {
            0x6461986DC4EB9B48ULL, 0xE19F2A5B6B78254AULL, 0xD2926DCE202BA1B7ULL, 0xD34359C0CC4D8F5BULL, 
            0xC331DA3487A8190EULL, 0x2A4EC9211C304117ULL, 0xE5DE295D2D97D702ULL, 0xCBB58D51CCCA9A95ULL, 
            0x2B238555F0471179ULL, 0x7312E0982CD7BBB3ULL, 0x7CC59EC486AE6CF1ULL, 0xC843D4C59CAE562CULL, 
            0xB7F09DA856E5B00CULL, 0x078B2B3115197AB1ULL, 0xD479BE53726BA2E1ULL, 0x8F56446FFE936A96ULL, 
            0x6A7F2B241B9866C2ULL, 0x2CB5F637E20F8468ULL, 0xF575A43C5537B6F0ULL, 0x752BAE11AD573B01ULL, 
            0x06F73CE9349A69F6ULL, 0xFCB24AE84D87B2E8ULL, 0x4610B6D2224F1F65ULL, 0xB63B4E2D6393D07EULL, 
            0xB7A55CF9DFC0C497ULL, 0xDDCC8406B46EDA26ULL, 0xD1EEF7EDF817416EULL, 0x781D55233396BCF9ULL, 
            0xBFA023C5C5962145ULL, 0x007DA44D6B44B349ULL, 0xA2BF06F84EEB4110ULL, 0x294941192D6A6CD0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseBConstants = {
    0x350C6A09B5C3370FULL,
    0xB0852101E305ED57ULL,
    0x7A506AE140DF079BULL,
    0x350C6A09B5C3370FULL,
    0xB0852101E305ED57ULL,
    0x7A506AE140DF079BULL,
    0x11E405B53FCCA042ULL,
    0xCFEE637618DEDC10ULL,
    0x35,
    0x3D,
    0x2B,
    0xDD,
    0x6B,
    0xBC,
    0xC4,
    0xDC
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseCSalts = {
    {
        {
            0xF0FDCE2B11ED7710ULL, 0x097DEE989688D686ULL, 0x9552CBC92FBFDA58ULL, 0xB13569BFA72C209FULL, 
            0x24B11BA26B9A5AF5ULL, 0x728E5417E54E3DD0ULL, 0x78216F3C336E1CFAULL, 0xE351B582AECEE3C2ULL, 
            0xF05BF7B49BEE5C3CULL, 0xFBEBF0A7612211B3ULL, 0x32D175ECB4FF6C2BULL, 0x3C495A5EE8D98A5DULL, 
            0xC1BFDDB2FA97753EULL, 0x28DAE9CAE4046506ULL, 0xD2B950CD0B8079A7ULL, 0x098900992D9F31D6ULL, 
            0xAAA0AC1A66FAA9F9ULL, 0x7EBC8E7E35BFC3C5ULL, 0xE7101FCBDB501413ULL, 0xC2483C7301C59B88ULL, 
            0xC50B83D012296917ULL, 0xA3BD140382A5D45BULL, 0xB3615B0AD7610D6BULL, 0x47A980DEA1652E47ULL, 
            0xB298EF0C2445BA39ULL, 0xFA3CAFC7372A1616ULL, 0x6F4AF4A52C72F2EEULL, 0x7F964ECFEE06CD8FULL, 
            0x203EE8195A2AA1D7ULL, 0xF6270FCFCE7B329CULL, 0xCC9D5461A8695F20ULL, 0xBD419F8E37DC1BBBULL
        },
        {
            0xF1B1FD0140C03E18ULL, 0xD3E3696F444F0B3EULL, 0x1057B8CF21406F81ULL, 0xC8D2B15CF6B6429BULL, 
            0x3CEB57D6589F23C9ULL, 0xC478882917375307ULL, 0x1B68BEAED45ABE60ULL, 0x880A1640883C40DEULL, 
            0x9B15B75AD5FBA99BULL, 0xBED0C70B3E1114C9ULL, 0x8899F037C34180DBULL, 0xE406DE0952E801D3ULL, 
            0x6BE44D2828451045ULL, 0x6D0C486083EAFC8CULL, 0xF4E1EED064059B71ULL, 0x5E72570342BBB3ECULL, 
            0xD7FF6FDD521005ACULL, 0x9F09E71D5B60E102ULL, 0x8404EAD4562B0DCCULL, 0x76D1546AF33E6903ULL, 
            0xA4C254DD313D7F01ULL, 0x168CD12AF88C83CFULL, 0x66C1BB4591ECFFC8ULL, 0x65852F1A3BF52C36ULL, 
            0xAFA682E6A436BA0EULL, 0x3FF13186AE42F924ULL, 0x5C4FA05AF21ECB4BULL, 0x696272C4B1925394ULL, 
            0x3991C262904CC4E5ULL, 0x8ABE161BE52B826CULL, 0x1CFCBE3F4F6DD36BULL, 0xE2FB408900486F57ULL
        },
        {
            0xD9E4206E7C770CD3ULL, 0xCB659F24248B1CA2ULL, 0x569CD07A37AFEFDFULL, 0xB225163655811C0DULL, 
            0x897098952F618C25ULL, 0x593FC07D49250348ULL, 0xF983A9A5EE86FDA9ULL, 0xDB26B5E466258656ULL, 
            0xBA68EC42BE125FD8ULL, 0xC1CB217A59ED2444ULL, 0x2575E42C3A0E3758ULL, 0xEA58C2911FE45B3DULL, 
            0x0ED8DED98B1A2D45ULL, 0x4DA379D4FD666D69ULL, 0xA35AD0724B637468ULL, 0x819A4E29E2C5511AULL, 
            0xC73056A9CFD449F6ULL, 0x51BEA011CDCB40ECULL, 0xB75B6A3A0CF8A15CULL, 0x8112C94459220FF1ULL, 
            0x95B49D843E89D7ABULL, 0x9E7A1B78D4F0B7F0ULL, 0xB658E5215152A046ULL, 0x875CA63CF4F04A8DULL, 
            0xADA0996906F38FB4ULL, 0xC4EC8B8568F4C880ULL, 0x788C2C28E8C0E3BFULL, 0x5EBFAA09091A7DE4ULL, 
            0x1BA4BF34A6C0DB29ULL, 0x7977DA552BE1D0F9ULL, 0x9B5547693ED1147DULL, 0xDF6ADFB8FFC539D2ULL
        },
        {
            0x9D3923CDA5330514ULL, 0x5176C116B4029E20ULL, 0xF072BA31E220C66EULL, 0xDC3DC4F88CDA1341ULL, 
            0x76EA80E6EBD165DCULL, 0x76138FF875D9F1A2ULL, 0x6D822C49C3A20086ULL, 0x47A58C6BB9005C85ULL, 
            0x82B223254A087A08ULL, 0xE13DB2CB21215AFCULL, 0x8F63519EA940330FULL, 0xB89E11E54C21884EULL, 
            0xF908FDF8AC04789AULL, 0x1C8CDEC45B70D7A4ULL, 0xCD4B4EE47292DB94ULL, 0xF267DBFAE840D237ULL, 
            0x0338B784530DC179ULL, 0xA79E88978DC1187AULL, 0xCC12CF097761AD6EULL, 0xBE9CF22BA017E84BULL, 
            0xC84F9C0B8C4EC35FULL, 0x4F3F366D95D786B5ULL, 0xCBF9D4DA9A5C9CDAULL, 0x705C5623D0DA9E06ULL, 
            0xF661CF9F04CFCC98ULL, 0x43CC5692E7F702BBULL, 0x342A068A042C6316ULL, 0x077CC3B97FBEC204ULL, 
            0x7F1EF4BED80EF09EULL, 0x0FF6A5C8497110CFULL, 0x78F4E544050030DFULL, 0xA15D577F81940BA0ULL
        },
        {
            0x3FCA0DF7453CCB3AULL, 0x49A483EB3838E737ULL, 0x9DBCD14F10E0927BULL, 0x7840AD0A830686B9ULL, 
            0xC6F5E07346533FE9ULL, 0xE0F4966A753EB7BDULL, 0x6E768C8688E117B6ULL, 0x2EF2C0CAFE50632AULL, 
            0x657215E9ED51B97BULL, 0x1D4A970DFEB75F53ULL, 0xE1F901EC47097DB9ULL, 0x9D36F69B08EDAB00ULL, 
            0x2365A9AD6CEFBFEDULL, 0xA079FA1AC5681A8DULL, 0xF170CD5B893C8964ULL, 0xB5628A7CDC595743ULL, 
            0xFD3673D71615AE08ULL, 0xF3F1319E59AF7CD3ULL, 0xD42C6178146C0102ULL, 0xE6B479F7058EADBCULL, 
            0x2090FBD25AA428A3ULL, 0x4A2C0738062196B9ULL, 0xBB5EACDAB7999559ULL, 0xDE16F9C4359FD5B9ULL, 
            0xD32CA75C6F5EB800ULL, 0x1BABD859CC49245AULL, 0x2F88E3967B089D75ULL, 0x649297AC7A162508ULL, 
            0xE5ACBAA4E400BC40ULL, 0xFA30EF1243DC36E5ULL, 0x4952B7CBC7612EA1ULL, 0x6FF01AD5A50AC606ULL
        },
        {
            0x78ED69C77141E757ULL, 0x5DCFB7095334D55FULL, 0x024DBAC7F2305148ULL, 0x53E668EA3FFA1633ULL, 
            0xD5CE96A9B9E7D005ULL, 0x6DBE3B383E01BD55ULL, 0xDB11FBA7F842542DULL, 0xE7F986C6A032EC58ULL, 
            0x4023825C1E4E096EULL, 0x49A2286CD71DA3F3ULL, 0x3B0F76DBB16970BCULL, 0x4DEF8CD99EF45521ULL, 
            0x89ADCA7788066AB1ULL, 0x22D9172AFFA0B3B1ULL, 0x84383D1216DDAA60ULL, 0x74E08F4DABC2D361ULL, 
            0xBCA95417741F23B8ULL, 0x12AE6106B931627CULL, 0x538C3786410AAA2AULL, 0x58A31619FBEAC86EULL, 
            0x5A12C5108E8B16CFULL, 0xDE34B4D06ED51EF6ULL, 0xE1049464376192C3ULL, 0x5A9EE1D0980AD654ULL, 
            0x1610CBE71BD769CEULL, 0x693FD2C35601CC2CULL, 0xC5ABD8C589BD340CULL, 0xC7C5B9CA7DF524F1ULL, 
            0x3BEF06C536F2D774ULL, 0xE321118A00E8F87EULL, 0x47148536899CF915ULL, 0xBC5996EED34FA07CULL
        }
    },
    {
        {
            0xBE159630E7953862ULL, 0x452A218F49C7A25BULL, 0x1A00328EFEF9CA4AULL, 0xB85816764C779B00ULL, 
            0xBC90B7B2DE3C85DAULL, 0x3FF89822ED7D4224ULL, 0x2BB6FD6F323F6F2DULL, 0x75503BDA6FFFD17FULL, 
            0xE53DA471CAB0B690ULL, 0x856B61EB49B8C24AULL, 0xB02FE9FB9B14BAE6ULL, 0x33A436DF9CF16668ULL, 
            0x59A3C419E5E23651ULL, 0x1D0CD8961AE3BB1AULL, 0x66BC4C6E125FAE5CULL, 0x50E323ECB894F2C4ULL, 
            0xB2C8B5D6B9508C12ULL, 0x86DE9263F5408491ULL, 0x166F599E210AEEE8ULL, 0xE7FB011B2A9EB5C1ULL, 
            0xAADE865E50344C18ULL, 0x1B734870EE1C2C41ULL, 0xD7E4C7048D5F0087ULL, 0xEE8706982BA564ECULL, 
            0xC964C8772BA99484ULL, 0xEDAD82027AF4C80CULL, 0xB4867FDA3398B4E4ULL, 0x639FE41BF9590E8FULL, 
            0x4AA12E158D7BF6F4ULL, 0xF9D5CA9DB9355B49ULL, 0x9F23EA035A571B08ULL, 0x456AFA2954294300ULL
        },
        {
            0x8B2725E37A36437BULL, 0x53667F8BF300BA56ULL, 0x8BD042E15C6B37E0ULL, 0xF92FA23E0F3D43DCULL, 
            0xA734EF452A58DCDEULL, 0xA186B0DEAD107357ULL, 0x6B40684C368EC64DULL, 0x52962190E147295EULL, 
            0xE2C4C509FBC96D6CULL, 0x2630C17D950868DBULL, 0x1439C44FCC72A16DULL, 0x4E2DCF1B251A16AFULL, 
            0xC531F5F0BA98C730ULL, 0xC67C668566216DFCULL, 0x76A128C0923CB113ULL, 0xAB13EAA10B0C41BFULL, 
            0xF37D898FF63520B6ULL, 0xF9E0CA91D5FA68E4ULL, 0x5D413485431AEB67ULL, 0xC77D104D11FCBB37ULL, 
            0x806F31B2147FD38FULL, 0xF127FB6B1C610914ULL, 0xF2C5867D586CF2D6ULL, 0xF0ACC3B4566C5274ULL, 
            0xAFBBBCD236F73E51ULL, 0x2AEE79B71DF053D4ULL, 0x642853730B4C4F67ULL, 0x45D5A0DA786AB5F4ULL, 
            0x525D80CE5C047417ULL, 0x2A7AD3370EFD908DULL, 0x999089932E5CDF32ULL, 0xD2BD3B59A2B6E67EULL
        },
        {
            0xAFFCF6AFA259DAB6ULL, 0xF3CA8E4ACAF98D95ULL, 0x510F309F2660DB03ULL, 0x9C8C103508F464D9ULL, 
            0xE2DB3E96B873E417ULL, 0xBCC8E2551F3AB04DULL, 0x3B2B42AFC0CA843CULL, 0x46B5113DD4EB7410ULL, 
            0x400925B90DF59545ULL, 0xBC00394A3D89B8EFULL, 0x54E09F75EE6CD478ULL, 0x05D2F07A8B6C6AEAULL, 
            0x2F4E1F15B66A213CULL, 0xEB88A4ABFEC4BA37ULL, 0x7AADA5E99F336F87ULL, 0xF02D7BB3577F3504ULL, 
            0x68A5F796FEF8355FULL, 0xC1D7CF41D7AEC9EFULL, 0x9A957F35B65E8E1AULL, 0xC74B361100B73676ULL, 
            0xB26363E3A45D2A74ULL, 0x5CABB85ACFD6187EULL, 0xEE1D03DBA8F0E93EULL, 0xE16C8BE2FABA5304ULL, 
            0x248AD861718663B8ULL, 0x8E6547E42220016AULL, 0x2A8223B10D24A24BULL, 0xF17042FE2DF3DF8EULL, 
            0x9A0CC9B32B04B032ULL, 0x571611825DCBE3B0ULL, 0xF66BDB829A5B6B95ULL, 0x96B866D2881DF8FCULL
        },
        {
            0x4221EF61EB624BB8ULL, 0xA9E04B2C558124ECULL, 0x764ABA31E7BAF9A4ULL, 0xE20AA1972974D120ULL, 
            0x48463B200D28548DULL, 0x540C8E71D21BD4C1ULL, 0x0957A6C14C6E9CAAULL, 0xA0A6D378EA3D20E4ULL, 
            0xEBABAE071B3CBADBULL, 0xF234DDE09EF00D2AULL, 0x5567EE8A53445A3FULL, 0xBDDD4DD1DA1C598FULL, 
            0xF1B825A69685643BULL, 0xBD023D478F0DF482ULL, 0x657A6FAFD5012A1DULL, 0xF64BF3935BFF4BD2ULL, 
            0x20F8CFA1C0AEDE7CULL, 0x67147A68F787A5ADULL, 0xAD61748073E14E89ULL, 0x697AD18EC6AF9B7DULL, 
            0xAD327DAAB37B8AE9ULL, 0x98085CB557DD0C6DULL, 0xFC54A21D252588F5ULL, 0xB850353180C96532ULL, 
            0x5CB89FBC823CB220ULL, 0xE59D2C847C63CB85ULL, 0xCD03033D83035061ULL, 0x97817ABF239969D8ULL, 
            0xA65EA6A5F868A887ULL, 0x0520DFED4924F58DULL, 0x9651DDACF2A2D9AEULL, 0xC7D90E4A9E9758DEULL
        },
        {
            0x46BAD1ADEB4C0B25ULL, 0x050E4E23AC4D951FULL, 0xB506154F3FFBBCFAULL, 0xC7C665A9419FFC71ULL, 
            0xF68685732E2BD93CULL, 0x9E9BBB32A5B18ABFULL, 0xBC04A9257661D4E4ULL, 0x441456D3E3103C4FULL, 
            0xDF7C19CCF11633CBULL, 0xF1363BA309F404CBULL, 0xFA1B6F5C6BB6D7ECULL, 0x608EFF74E4FD64B3ULL, 
            0xE801FABE1DCFE807ULL, 0xBC8AA4D3769CBDFFULL, 0x9F5FB56FB555C840ULL, 0xC6D1D74BE8F0F7C2ULL, 
            0x58FC0F4DF27EFAACULL, 0xC011FFE8C0538823ULL, 0xEF492CCFDA05AA74ULL, 0x27C331DE3C33942FULL, 
            0x53A793BFBB501974ULL, 0xC09A600819D6E14BULL, 0x89FB8FACDC27567FULL, 0x563B7B5B4CD345AEULL, 
            0xFA2737F1D3FCCA14ULL, 0x74708B8F0993417FULL, 0xDFBCF6442E21D282ULL, 0x4460FDB089AAAE6CULL, 
            0xB00C3D0127005F2AULL, 0x0934FB359E169E08ULL, 0xF5169578A81A6AC7ULL, 0x894FA2D98C697159ULL
        },
        {
            0xD073D2709B443B32ULL, 0x9CDD0D9D76163B8CULL, 0x42AA860D49654E18ULL, 0x8499E01B8A2F00A9ULL, 
            0x07B90258DD9A35B2ULL, 0xBB9D873F7C4C8AA9ULL, 0x2A5AC3E2F72FD726ULL, 0x2F332EF76169BE57ULL, 
            0x5D0FA2E7C8A6888AULL, 0xB2700CA7D27A5473ULL, 0xDE459CAE0CDA6823ULL, 0x1102D56D3192F34DULL, 
            0x17DD86A3F49FDB25ULL, 0x7F43BE062E05E7EBULL, 0x7277845D4E0C389EULL, 0xFEC0BFF801771968ULL, 
            0x84B9162B7EE492A8ULL, 0x64C65891D3CBCA67ULL, 0x07BCB17FB804D1A9ULL, 0x01887611A2F9CE6BULL, 
            0x0F14C993130280A1ULL, 0x3278DE97695E16BAULL, 0xA88F53C83599A24DULL, 0xA8F637F2411E043BULL, 
            0xA8EC7F0268D5B9F1ULL, 0x2C9258C335834E1AULL, 0x414F9D24CC326EAFULL, 0x8A527499C0B62169ULL, 
            0x34574E7EB037B676ULL, 0xB6B50BF37C39BCF5ULL, 0x6913ACC774BD014FULL, 0x8F8245C54642F734ULL
        }
    },
    {
        {
            0xB7949ADAC13DE39AULL, 0x0BBBF4154F095E1EULL, 0xB441F396FF876C71ULL, 0xF7D7446E4473D8C9ULL, 
            0xF6A010A75667E098ULL, 0x582D5F6B901B9E75ULL, 0x0FFA61911108379BULL, 0x7F7B67F3003949A8ULL, 
            0x9FBCF022059B60AEULL, 0x59B9E1D56E203F99ULL, 0x322C79A7CF756E56ULL, 0x3DCFE7C880B5208AULL, 
            0xD6122EF5D105609BULL, 0xAE759A138373A5D3ULL, 0xA2792D3D51849C85ULL, 0x69C6974751B5F4F1ULL, 
            0x41FC9BDFAF1C3E5CULL, 0xA49B57B7BCF710A6ULL, 0x7570A5049F4092FDULL, 0xBA852A1A35B0D2C4ULL, 
            0x3215B5B8EF804FACULL, 0x8A85BA8AB5866E63ULL, 0xD07D4A9223E0AF89ULL, 0x3271681C1A539099ULL, 
            0x1A114986556A4665ULL, 0xBF2D034431064FC9ULL, 0xFC9D05CF7F270019ULL, 0xA4B6001E01E75AD8ULL, 
            0x2F570C60F37F12E4ULL, 0x4B20BCD2032B3243ULL, 0x0997888C2BADDE3DULL, 0x661A4384538F6ABDULL
        },
        {
            0xCDA29898E693DB61ULL, 0x9515D3C2A2AAF598ULL, 0x42BE1CB951639834ULL, 0x9D0AF851AF825CB7ULL, 
            0x8E6A3D6E892004F5ULL, 0x0F128B202DA06CC4ULL, 0x063B7DB77952DD34ULL, 0x70C9BB5ED42E2457ULL, 
            0xDBC40F05B5DCB806ULL, 0xA6458E2337D122A2ULL, 0x5F9D13661F0FAD93ULL, 0xAFEB4A2F737BB691ULL, 
            0x80291AEA3D12E48BULL, 0x4077523C7167BF3BULL, 0x6F981C40374557B7ULL, 0x40DD2B97078FB84BULL, 
            0x773EDB52717EBAC4ULL, 0x4413A7CF679BCB20ULL, 0x4BAB8409543F85DDULL, 0xEF74E1D93456F03AULL, 
            0xB5234CB075599DBCULL, 0x5D835AF4CF955F9FULL, 0x9FFDAD4EA9EDD861ULL, 0xFF93A3C82F3AA276ULL, 
            0x63D4B4E7153D8582ULL, 0xCFB0EAE4D9380A60ULL, 0x9A585F5354770360ULL, 0x57A73C102D37C109ULL, 
            0x2FF4FBD545091310ULL, 0xAA440DF34448B708ULL, 0x9F8413597760D163ULL, 0x7CAA0D279D38A318ULL
        },
        {
            0x6DC11928F0DBE39BULL, 0xAF34149335C803B0ULL, 0xF4ED1E2E31F06998ULL, 0xA432891848A4EA7EULL, 
            0x30220D9DD8D668F0ULL, 0x9D8AA68C5C99956BULL, 0x3C7888D5D82986BFULL, 0x6EB803FD6034D605ULL, 
            0x48A7D2CE4081B523ULL, 0x10C756C3F6E0D0D8ULL, 0x27762B59E50FD889ULL, 0xEC9CCA4E10758581ULL, 
            0xD9BCB994A409D410ULL, 0x0A0AC1B377969297ULL, 0x9D8238295FEBB857ULL, 0xE36B45C896003CA0ULL, 
            0xF804E8B1D80AF025ULL, 0x7AE10A6ED5D2A6B7ULL, 0x43A6FDF30E699DA0ULL, 0x556B0CEB0B402A1AULL, 
            0x44B331EA4D57DF43ULL, 0xC5F4C2AF73243907ULL, 0x8ACD049FDA7987E8ULL, 0xD4544418CA7DC642ULL, 
            0x2DDBCAEBA9264F90ULL, 0xB88E51CD3E792797ULL, 0x4F193A23964B00FCULL, 0xE005D91A9BC30B56ULL, 
            0x3004D94A631D616CULL, 0xBA108E810C340CF3ULL, 0x94E03FDF0E1A6815ULL, 0xE8EDE88F8FE28579ULL
        },
        {
            0x8618B3E0E112EFC1ULL, 0x2AA7B180133AF4ACULL, 0x2DA52F9E3593E661ULL, 0x7E9E3D96EDE9EEAFULL, 
            0x293CADBC60CAC399ULL, 0xD94969EE32446197ULL, 0x6D4C4523390163F1ULL, 0xDCC5543DBBD5554DULL, 
            0x12826E36CFCFF542ULL, 0x7677F99068BB3588ULL, 0x78D8777045BEB781ULL, 0x193AC9450E91DB17ULL, 
            0x576D5B36EC941B48ULL, 0x5DB9A4013E8A956BULL, 0xAD30BEBB9BBB6157ULL, 0x41E6177C84637E00ULL, 
            0x334D93E0D65C6F3EULL, 0xD4BCEA038A89FA69ULL, 0x2E0A6536187C9F4DULL, 0xE4BF6F4AB77AA8B0ULL, 
            0xD96F66CCD7451C69ULL, 0x4D0DDA307F2C3851ULL, 0x17A54FA675463D54ULL, 0x155CA21D1E76635CULL, 
            0x4247364955D2E35FULL, 0x886F555A0DCAA9ACULL, 0x28D3D8B09E885D7EULL, 0x974F8EBC872801F7ULL, 
            0x53796A7FD1346D87ULL, 0xE5DAD0E000905522ULL, 0x0C418C9A1DD5DCEBULL, 0x6709E05DC693B321ULL
        },
        {
            0x240C75D434E95DC1ULL, 0x58792C891A3CC5D6ULL, 0x631B814C203F2C23ULL, 0x439BD0AD7DAC5549ULL, 
            0xFA49DDFC626499D7ULL, 0x9D6F015C3C67C166ULL, 0x27163BDCD7EFCC3EULL, 0xB633AA959AB0E148ULL, 
            0x93B9C8EA69E01DF9ULL, 0x857025803B67942AULL, 0xD33ECD2EFA538B6CULL, 0x73898DC111820F6AULL, 
            0x1072CD11BEA8FEACULL, 0x8546C1E7A1A6213BULL, 0x8102F78502B59650ULL, 0x453D290477105199ULL, 
            0x73C487627E5D4315ULL, 0xB069759E4A595A25ULL, 0xCC78956383F36539ULL, 0xA1ECB91CE4AC9556ULL, 
            0x25B1AB26F325A3F4ULL, 0x74EBDFB8465E4212ULL, 0xF21D0F114D410255ULL, 0xE1F0E35F717BDB17ULL, 
            0x6A1EDDAFCA8068EAULL, 0x61214BD2F5AF2721ULL, 0xEEB6E3F442341950ULL, 0xAD1FDCE1712B7D6CULL, 
            0x89A2F89190D92C23ULL, 0x168946949B7443B2ULL, 0xD58495C2EA1524D5ULL, 0xF8F21AB986322430ULL
        },
        {
            0x6125768164B34972ULL, 0xA554F741859DECB5ULL, 0x68F2312EA827D7F0ULL, 0x41D9F7442D7DE766ULL, 
            0x24585548F6C326FCULL, 0x652F4CEB04C402CCULL, 0xD3C3B512A4B65151ULL, 0x43C61431D42A4396ULL, 
            0x3E7D62D8FA37210CULL, 0x475A4B22A3607848ULL, 0xE9DBC95CF2BA3C2EULL, 0xC33EFD92BBF25D41ULL, 
            0x1C11025523863FEAULL, 0x9D7AD6FE89A97620ULL, 0xB1EEFD6C21E4FEE3ULL, 0x60F6BD04CC116130ULL, 
            0x985CEAE51A155FB9ULL, 0xE4D3BECA3B0F2923ULL, 0x83D1AA79541DC219ULL, 0x9EB558AB4CE0A54DULL, 
            0xA2DF05AE0EE85A01ULL, 0x32FD33FC7D90D78EULL, 0x81E2B66485C34E9EULL, 0xAB3B76C25631A62EULL, 
            0x44A6FC88DCCE8CCCULL, 0x1E53483A4BCACC57ULL, 0xF18E81A37236E17AULL, 0x44E39343C1DF2F2EULL, 
            0xF30E45EFACDE3433ULL, 0xFF347BB315D4ABA6ULL, 0xBBA802A286375EFDULL, 0xA5E0F88FCD8E12F8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseCConstants = {
    0xFA13B4F66711ECCCULL,
    0x9350945BD777DCE2ULL,
    0x0D693F599D435D85ULL,
    0xFA13B4F66711ECCCULL,
    0x9350945BD777DCE2ULL,
    0x0D693F599D435D85ULL,
    0x30C8CD27E71EDD41ULL,
    0xAF2F144F78C4EF51ULL,
    0x59,
    0xCE,
    0x41,
    0x94,
    0x63,
    0xFA,
    0xAD,
    0x47
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseDSalts = {
    {
        {
            0xF96164B22E0A5158ULL, 0xD7A72B62C4550C60ULL, 0xF4F7D4AC1190B7FFULL, 0x136F0A2CA26ECE14ULL, 
            0x42BB53E1973403F0ULL, 0xCC079867D3B9F393ULL, 0x9D7BD55060AE19F5ULL, 0x798D07C8CBC87A60ULL, 
            0xE2B87F4D5F5783EAULL, 0xF772F6D37A37FEA1ULL, 0xF1777BEBEB9B01F7ULL, 0xB630D51E4FFA3A0FULL, 
            0xD935E3272D2093ADULL, 0x98A3102A9A946B02ULL, 0x822DBAEC94820D41ULL, 0x5891D7D6042225D6ULL, 
            0x8E7E0A43E827E2EEULL, 0x8BAABCA4BA4BA9BCULL, 0xCBF84208E5998F6CULL, 0x27B2278ACBADBF4EULL, 
            0x587F0B5D73B7FC42ULL, 0xDE78AF3FD06B963DULL, 0x33C031BE6858FBDCULL, 0x58E0EE094A039A4BULL, 
            0xA7E5A8D75A8DED9BULL, 0xF56C171EE973550AULL, 0x1592C79CFAA0C988ULL, 0x00C9DDB5C04C1F14ULL, 
            0x8424A6157D61BECFULL, 0xF63EB758FB995549ULL, 0xD21DEE4E50212EB1ULL, 0x1F859411592B0CB4ULL
        },
        {
            0x85C70CDB46C4D58DULL, 0x085A75CE6CC9CDBCULL, 0xC3C4DF19AB69036DULL, 0x722A09F11934BB65ULL, 
            0xADFF011D9F4A05A9ULL, 0xB4FB9B8752259F94ULL, 0x0FD5B0F98813B47EULL, 0xC831AC5FCEBD781FULL, 
            0xF08CB9D245148071ULL, 0xC50D368DD0FCFC61ULL, 0x7FCF21D1B1E41B22ULL, 0x14B1D851F780F233ULL, 
            0x4D74A47EEF9101CDULL, 0x90042A14CD529CE6ULL, 0x6D7C03694618FE50ULL, 0x71118DCBCFD96A2DULL, 
            0xCAAE25807EDC3535ULL, 0xFD13465CD07975EBULL, 0xB5336E6BC3055B00ULL, 0x1E0A058DFE3E48C1ULL, 
            0xDFCB9E63E512669CULL, 0x62D91E263C60EE77ULL, 0x3AD23F7F133EB365ULL, 0xD59E5436EB254E33ULL, 
            0x9FA9FA278904A9A8ULL, 0x2375AD4D520390E0ULL, 0x4E987098AD1903EBULL, 0x657BDB323D835495ULL, 
            0xAE0A0A6BE90EA2B0ULL, 0xBD14D5781F320E76ULL, 0x7E6CA7F938269835ULL, 0xB9A745866830704BULL
        },
        {
            0x88717A14C1537678ULL, 0xEDB4CC0B8B9EE968ULL, 0xED61576E4E1FA607ULL, 0x644ED78802E15562ULL, 
            0x6368DF049A6694F3ULL, 0x30A605C50E778427ULL, 0x84EBD4FF2E20E55BULL, 0xC320D2C0CD223F14ULL, 
            0xDF955FC0BF060B71ULL, 0x0CACDFF84D98D54AULL, 0xC634FFFB4ED87B05ULL, 0x943A8131CAE3DE35ULL, 
            0xF152E9DF8877FA65ULL, 0xA5503AA9D43AA38EULL, 0xBE0B5C3284CEAFDAULL, 0x3CB0A63C4F4E0DB6ULL, 
            0x4486D2588B5E49B1ULL, 0xE035909221B88C91ULL, 0x9DF313E4DA8FC58CULL, 0xC08A1A5A18B18274ULL, 
            0x5D5625EA14B32527ULL, 0x32D1C4CD09481072ULL, 0x1FFD7F6C29BE4899ULL, 0xA409D52029C2CC83ULL, 
            0x39C98A2631948B24ULL, 0xCAF1146F68FEEBD9ULL, 0xD9C8C5833E81C2E9ULL, 0x77ED41A342A0D1BDULL, 
            0x7732011552C9046FULL, 0x7E71DB5884DACDB9ULL, 0x117B6508FF05ACC8ULL, 0x0D38C8AB4E435A16ULL
        },
        {
            0x5D146B9C0FB90921ULL, 0x5FA9CD20D4029288ULL, 0xF1E1E1EC4D4A4919ULL, 0x8892EFA5AFC222D1ULL, 
            0x669092B49ECEBEF0ULL, 0xF08F9BBFFA275D14ULL, 0xFE365DB71C589741ULL, 0x48882EDBA3665219ULL, 
            0x01943019B5B11CEAULL, 0x3A99737ACB64A41AULL, 0xEEA7AD116DA465DFULL, 0xC11EEF397D26F27FULL, 
            0x31CF1C71266D1F64ULL, 0x33DA3512D6B666A8ULL, 0x097DB7CE92C0FB39ULL, 0x8B58C939DD884BFAULL, 
            0xA6EC9505027A0C0AULL, 0xBE4C546C96DF7A3CULL, 0x770FFE4B32BA6CADULL, 0xF51962E8C513D187ULL, 
            0xCA0D1923A885E47BULL, 0xDD8030FC580437E6ULL, 0x7D5CFB1681B83798ULL, 0x9032A909CE0F219CULL, 
            0x0D633BA751F4F46EULL, 0x5FA0C9FF2ECDD2A1ULL, 0x8190F94343641879ULL, 0xCACD76C828CFD8F9ULL, 
            0xBEFAD41CB999B948ULL, 0xDD75184A319D0A36ULL, 0xB1EBDB4857F37A43ULL, 0x086749202053D3EBULL
        },
        {
            0x4CD0739DCBB39C21ULL, 0xAC350685A9440721ULL, 0x0FF6421BF0FC7EDDULL, 0x4417B23D81DA24A0ULL, 
            0x7D5C6A785F41EBF6ULL, 0x99EF0EEC8D5A7065ULL, 0x03FA278B2B6EBEC4ULL, 0xD5197B3921EBE68DULL, 
            0xDDA8F0131FA3896FULL, 0x55FD7D512AADF505ULL, 0xFAAC489C974B0A21ULL, 0x9C02B05498D3E36FULL, 
            0x21726EAD7E193ABFULL, 0x6A68F598F22A180AULL, 0x8A31900F4E5FD208ULL, 0xE3EAE770251E0D82ULL, 
            0x2A414BDCFBF352BAULL, 0x11F75178FD0EFA68ULL, 0xCC41ADBA55739280ULL, 0x747B1D96E7CAAB89ULL, 
            0xAF8B93F0171DCB33ULL, 0xCC2FA144305B461BULL, 0x9D45AE51818EBB81ULL, 0x8832F6BA061E45A4ULL, 
            0xAC4DB7E50C3D3BF5ULL, 0x8CB844862C55C3E1ULL, 0x6E8257390A34709AULL, 0xD70B3B66C376798EULL, 
            0xB6C3DC16C762D11BULL, 0xD50ECB4348F46B4FULL, 0x8C33DC994DB0FF19ULL, 0x25FF6C8D74D2C793ULL
        },
        {
            0x5C3E4A37F28E684DULL, 0xCB8DBF101C3068A3ULL, 0x492340C8D1E1BE73ULL, 0xF21F2AF728FB9CBFULL, 
            0x32CD613696D6DF9BULL, 0xBB5956E0532B507DULL, 0x3368497FD7262282ULL, 0x03A355433186F753ULL, 
            0xE8878E3ADF5E55C0ULL, 0x70125A4CD9947686ULL, 0x5E9F6280B037857CULL, 0xDEB0B60C970A8DE5ULL, 
            0x0417822B83265A06ULL, 0xEEB6ABD44C176325ULL, 0x5906A5F8A9B07F54ULL, 0x621AB080E653C5AFULL, 
            0x95368583CD814EDDULL, 0x78D4FA388655CC9FULL, 0x67826EC7C37C8C9BULL, 0x134A3E4EE641E463ULL, 
            0xC049C61DA45291B6ULL, 0xC0A95FE23767A9F4ULL, 0x36065E436DD956AEULL, 0x5147A9868D9C4A7FULL, 
            0x550BBA32AB49D912ULL, 0xEF086AAF1FA192CBULL, 0x2AB0BA0DA895B78DULL, 0x711F68496BE636CDULL, 
            0x3E59C5F04C0E979DULL, 0x1BC2ABD5D64C8E26ULL, 0x4998F1A97A4ABD6DULL, 0x61167709005FA69DULL
        }
    },
    {
        {
            0xBE2A30929B447A35ULL, 0xF944FF957DCF4B61ULL, 0x0A3B14B5AD654701ULL, 0x48D82C160EA5DE5FULL, 
            0x64F3388188D74982ULL, 0x94F9D32D856201F8ULL, 0xDD6161D15FEA7D18ULL, 0x927705867B84D73BULL, 
            0xA225C7BCF9AF4CE2ULL, 0x2DFD94FD79127491ULL, 0x96DB568E18A74C96ULL, 0x60B369FE8A3D5C66ULL, 
            0x3B2C66111E64AA2EULL, 0xD6985F338B03D4F9ULL, 0xA4C7189A0E8B6B27ULL, 0x6CA99ECE6C7E6EE9ULL, 
            0x8A3E3C93F85E1A2BULL, 0x74205B1AD5539149ULL, 0xE80B8032E48CD5B0ULL, 0x071B6AF2448109BAULL, 
            0x9593F52A9F9AAC51ULL, 0xBED19F864F090853ULL, 0xD614F814865EFEA3ULL, 0x52F178E74A1E09AAULL, 
            0x80DEA7CF8494B834ULL, 0x9A941195A6AF44DDULL, 0xC063314FC4261095ULL, 0x91369E8BF1796D5BULL, 
            0xC54CAAABCE1D171BULL, 0x1BD47E706A6EB852ULL, 0x949C67483927084BULL, 0x9B6245FB816D6E8AULL
        },
        {
            0x342FF86AE33D5192ULL, 0xE0CD43E3EFAA627EULL, 0x7497C2E4C9625AF6ULL, 0x6806A8C3DC3F2CDBULL, 
            0xD966C97FE4F358C2ULL, 0x04998C51FA891D06ULL, 0xBA76CE076F8420A7ULL, 0xA2E4C8D502D612F8ULL, 
            0xDDC25619AF32B2F4ULL, 0x2B3C582C5A02BBA6ULL, 0x98AD0AF102E062F4ULL, 0x823C97907D1A0386ULL, 
            0x997890B28D284460ULL, 0x93DE7E94B34BD348ULL, 0xE7F08A6580BD9B67ULL, 0x7C15750C0DD745E6ULL, 
            0x4C0F08811433E409ULL, 0xF47D421D96BDA642ULL, 0x34275E735FC53AECULL, 0xDB63727B6CFD909CULL, 
            0x628DB7E4C2CB3B9CULL, 0x7FA0C51653FEB179ULL, 0x9A6B9AEB23EBE43EULL, 0xA3F759AB1C4CB54EULL, 
            0x8A136D1F83A05FAAULL, 0xEFB8CD8A067F5D2EULL, 0xAD928272112174B8ULL, 0x836D8501EAB2618DULL, 
            0xDA9A335B4935C082ULL, 0xED7790D63C6B517DULL, 0xA3D300580AD97C8AULL, 0x3077B760EB2649D8ULL
        },
        {
            0x843B5DA0E832A765ULL, 0xC394D765A0D05C5EULL, 0xA358F4400B344A14ULL, 0x68EE1D6A0ED773E4ULL, 
            0xD272B7266D9C7567ULL, 0x0FEB5B83AEA79CE6ULL, 0x66AD26FDB146721EULL, 0x58C336A5232C7C25ULL, 
            0x208B45B14F8BA0E8ULL, 0xAD01804DDA6AF3D0ULL, 0xAE508E371E875882ULL, 0x3A9F7620CE72B617ULL, 
            0x49F36E28A98A0902ULL, 0xBCFB45F310872FDAULL, 0x04DF90BCB23EB432ULL, 0x3484CE809D07DB80ULL, 
            0x7309FCC3F5692B72ULL, 0x9E357F251D8DFEF1ULL, 0x199E6BD6E496BC64ULL, 0x3F21FCBF918BBFD8ULL, 
            0x7C2480B5529F2C37ULL, 0x8DE9CB8B24961C0CULL, 0x9D7D8D5488385915ULL, 0x4A9817DC26260557ULL, 
            0x017C2DE663B34A92ULL, 0xD953E8F0970E72ABULL, 0x644B455160B4DA0DULL, 0x3AC78C6835C69FEAULL, 
            0xF5EDCDDDEE5BD35BULL, 0xA971C1B7D442B75FULL, 0xB47D7455AE058C28ULL, 0x76226B9D55513268ULL
        },
        {
            0x0CCA9ADD3AEE6F62ULL, 0x28BAE890578B9D8BULL, 0xD38C78316A3AAD6FULL, 0x3468DBC52B6F472CULL, 
            0x5A7419FB50EF21D1ULL, 0x2F53EE196F1010E1ULL, 0x72A660D405E221F1ULL, 0x49ADEEE8AB9B7452ULL, 
            0x04798BB0AD8383B6ULL, 0xD7F72280A2585632ULL, 0x0F4AD13A74D8F9CEULL, 0x46E7CBB68EA0898BULL, 
            0x348203078508BBDAULL, 0xA6831616A9DB2D26ULL, 0x95B049413DBDEC51ULL, 0x54A67A17446F70CCULL, 
            0x18BEAB295EC6ACBCULL, 0xC426744A5ED2C038ULL, 0x556775DC819297FAULL, 0x68083449949FB51EULL, 
            0x93FBB2FAB60F8D09ULL, 0xFFDBB1F85DF66027ULL, 0xCC868B69A53F358BULL, 0xADCE129EEABDDAC0ULL, 
            0x577CDD97CDA25FF1ULL, 0x28CCE382C789BE14ULL, 0x2B0AB088899EB5AAULL, 0x6F8AB7BB6F995B3BULL, 
            0x4EFE4C72903B5E9EULL, 0xFC698BFD863A1D47ULL, 0x06933918F4DBC9FCULL, 0x4978E8A39D87D15EULL
        },
        {
            0x3FB2EEC4635F23D4ULL, 0xE337A233030E9B01ULL, 0x6F0EC1920AC24766ULL, 0x4F228EA0869E2A13ULL, 
            0x3A267B32ADCD248CULL, 0xB74CD2B518A47A8AULL, 0xFC542B82AD57BDBBULL, 0xE271769756F08D70ULL, 
            0xC8783A9083401D03ULL, 0x002972034B52E253ULL, 0x59DD220DD5F16235ULL, 0x55602E46EA3283F6ULL, 
            0x2B6D0426FB570800ULL, 0xE7305D463F387D04ULL, 0xC63721EADE5EF660ULL, 0x3A58F6F56927A023ULL, 
            0xFB772BDDE5B18657ULL, 0x18D8B100B066E472ULL, 0xF0A8CAFA3369AE3FULL, 0x4298C97731246AE2ULL, 
            0xC76CDA304CA37452ULL, 0xF38F630989C3BAE1ULL, 0x8578C64F8ED7AE8AULL, 0xA2ADED1908DC3FBDULL, 
            0x5605AA1399E7B09FULL, 0x9640152780F669F9ULL, 0x1DF34219D1220C4BULL, 0x54F8A38FDF5E8676ULL, 
            0xE95E67642DFC32FDULL, 0xC9F39CD1B66FB759ULL, 0xFDF0F7F05FF9B0C1ULL, 0x5452AAD276B46AE1ULL
        },
        {
            0x8ED506DC9A3CFBB4ULL, 0x0CD81D875B569BF1ULL, 0x69F6C94711FF8992ULL, 0xE12735593DAF1E40ULL, 
            0x5388515BA4581F06ULL, 0x320AB28FD687ACDBULL, 0xA065B8ECC998A29DULL, 0x74CA3355A6B2DB23ULL, 
            0x7720918CCE0EB0EEULL, 0x3AB1463DE64C7CE5ULL, 0x701CA47989E8B7A8ULL, 0x82855F56BD7A770BULL, 
            0xAE892FE992BC4D43ULL, 0x65DBBF98B9717D21ULL, 0x1C9D2D5494C16490ULL, 0x6FA15AA24F25F814ULL, 
            0xFCA76CF54EDFED50ULL, 0x4946AA97C16F684DULL, 0xC2695F06EAD3D492ULL, 0x5B8A4526D727D25EULL, 
            0x07A2619FE5A60551ULL, 0x4202112E8E3800B1ULL, 0x9FCC4058B958D798ULL, 0x0C3B6D24C5DF0DD6ULL, 
            0x8AE839846740EFFEULL, 0xA8452658F6B47944ULL, 0x1FC9D9473808CBBFULL, 0x7325AE573F53711AULL, 
            0xE0F36FBB7990B5C0ULL, 0xBD46F86993B949E2ULL, 0x6C9AF9677B7B1713ULL, 0x9C29BC9E254E9388ULL
        }
    },
    {
        {
            0x0239BA2D88DA13E6ULL, 0x885E80AEC86A7C25ULL, 0xC150667F75C21105ULL, 0x886E61BA9D7E29B3ULL, 
            0x8E9DE638962F5C2BULL, 0x095DD2A44589368AULL, 0x79E9905B009872A1ULL, 0x294A147BA7237134ULL, 
            0xE99CCD6E7816C557ULL, 0x20950E7D8F2CBB65ULL, 0x521851865C17743DULL, 0x7D3FB2EC849CAF5DULL, 
            0xC5751C144DF788A9ULL, 0x36ABE8CBCCA1F343ULL, 0xA748CB9775DDB6DEULL, 0xF86A708074B60D08ULL, 
            0xE9AEB4512DF475A2ULL, 0x3F7EAF852F2C6524ULL, 0x62BA967030DE79CFULL, 0x4D7BDC5E673B9B34ULL, 
            0x2EC8EA5C7E583982ULL, 0xFBE4F128E669683FULL, 0x76CDCC289845C07DULL, 0xF5E17C5A67DBE111ULL, 
            0xDADCF6CC747565CEULL, 0x86318821CDC2DD1DULL, 0x5D03763F1856F759ULL, 0x7CB89E76DD020DB4ULL, 
            0xF6C175C1B38AE2E1ULL, 0x404262AF58444586ULL, 0x9CC78EC473CE6395ULL, 0xC0DC570FA0CC0F07ULL
        },
        {
            0x6959EA3D63768094ULL, 0x9321FF2F6277EC27ULL, 0x856CBF38E52EAE90ULL, 0xB8B0899148843576ULL, 
            0xDEB90DD80EDAE8EEULL, 0x95E3794711384F7FULL, 0x7FE319FAA6F7A9CDULL, 0x826C73E1F2EC285DULL, 
            0x36BBD4A0D5BF1393ULL, 0xA9C3D0147572BA99ULL, 0xE6FEF11E52DF6FA2ULL, 0x162244136D343195ULL, 
            0x21D0DBB8527FD227ULL, 0x0B83BA13E949C6A2ULL, 0xEFA3862943195AC2ULL, 0x7E37B9D78F17268EULL, 
            0x6C1AF2CE81D1256FULL, 0x6AD2E28B0817D8E0ULL, 0xDB736083C78A0C41ULL, 0x7FA4CA514B08A568ULL, 
            0x2B39725667BB3CFBULL, 0x7C4682637C35243CULL, 0xCFEC909D4130FAE9ULL, 0x6A1486856741BF18ULL, 
            0xAD64A087C7D9E81AULL, 0xA048E233303BA27CULL, 0x38A43A1644AEE4B6ULL, 0x5ED47F56F80B67BFULL, 
            0x3FC0C1B64CB31288ULL, 0xC0BBA0D452DB14A9ULL, 0xF9B7D3EFBDE62422ULL, 0x37C682641DC49B87ULL
        },
        {
            0x65C27CB19FFD2E96ULL, 0x2E838C8421A45A93ULL, 0x7B8C8686D501EC2FULL, 0x823C2D90A8A50180ULL, 
            0xBA73BD87C0AA2537ULL, 0x9736759F7043DC9CULL, 0x3106E2087B195F21ULL, 0xEE3E14BF763B3DBBULL, 
            0xA427CC78863FF8F0ULL, 0xD17D593A3D4FE563ULL, 0x1208DA5B7A9286DFULL, 0xC2B22DF1F581DD6DULL, 
            0xEC0FA94AAF8837D5ULL, 0xEE39166CD3684FBAULL, 0xF8E25459DB7DDE64ULL, 0xB4714211AB6C89B4ULL, 
            0x4E999894174605E6ULL, 0xE973BF33FB43701CULL, 0xCE8F9EDE3A7EDE69ULL, 0xCD3A66F645873491ULL, 
            0x502436EA9A76E39AULL, 0x64E67DE7C6EE0434ULL, 0xD125DD3E94E114D3ULL, 0x95887221BF3B29FDULL, 
            0xE5CCC7F98BBAB884ULL, 0xD72008D44494580FULL, 0x5481ABF23B0AAC62ULL, 0xD509521A8FBFFF33ULL, 
            0x9733E787CE032ED1ULL, 0xFE63A525251393DDULL, 0x98DF25F83B182801ULL, 0x7FFF8C8AD80DB9B8ULL
        },
        {
            0x5B62E37D6E02FA66ULL, 0x200ABEF1196E0D33ULL, 0xA5C6FB760FAA89F8ULL, 0x5A8A5049CA92BF63ULL, 
            0xD535A332F03AE791ULL, 0x7BC1A1FCE288E4D1ULL, 0x006E3EBF3B0A99D8ULL, 0x2501585724B0F782ULL, 
            0xEDD33DEA78B5B7F3ULL, 0xD7AF29A19263F8E4ULL, 0xACB6DD55E7FC43C3ULL, 0x1A688E6A1F3FF47DULL, 
            0x54FFE1EA55866325ULL, 0x285BDDF3C41C8E64ULL, 0x9EF757C65D81FDFFULL, 0x8423E632CE3C7B75ULL, 
            0x70CB85CA0580C332ULL, 0x9001BACCDBB61CC7ULL, 0xBF6E7B97B1FC321AULL, 0x2924C5179A59B19AULL, 
            0x2F48C8B3D8F5947EULL, 0x104A1E3BEDF448A1ULL, 0x687BFA116CB37B8FULL, 0xEE56A3C5A21B3E0BULL, 
            0x1A1861686FE27821ULL, 0xB8DC716DF036F15AULL, 0xD43FE74CAD5DBB4BULL, 0x0F78BE5B7C37CD3DULL, 
            0xEEAECF7E22ADB085ULL, 0xA7DAD7F416069CC0ULL, 0xD225E983E35B5DCBULL, 0x44D7E3DDCBCA2B35ULL
        },
        {
            0x218DC53FFBDAF0EFULL, 0x50406A6DE5E0016DULL, 0xF5BBB8539357B290ULL, 0xC5D6F4F9558A9380ULL, 
            0x395A82456E1C1B4AULL, 0xA0ECFB3F2681D07BULL, 0xBB506A5CF35C6537ULL, 0x5CE13CC52C03590BULL, 
            0x33914DB1621DB210ULL, 0xA3C9BEC4A41BBF89ULL, 0xE734D82A8CE79D0CULL, 0xB3A7DC8582E71E2AULL, 
            0xC87107598BB97501ULL, 0x85DB9F5E0B254D31ULL, 0x3A2CE3D315504A6CULL, 0xBC6EE203CA148D32ULL, 
            0x826E8FA90268FF8CULL, 0x69EA4B9101125C5DULL, 0x0BAE4BF7B6334743ULL, 0x0CFE20737591CE8AULL, 
            0x6B3769AA95BBDB39ULL, 0x0AB41C9FB75BD212ULL, 0xAB227CA0C690014FULL, 0x6A43E9A0F5815C8AULL, 
            0x13C98B5CBB77D1FEULL, 0xB9131B19808855CFULL, 0xD5842FF790BC4700ULL, 0x44517D99B3F1CFC4ULL, 
            0xE45C5907B2470106ULL, 0xAA0529AFC73F30F8ULL, 0x1AAE3F4AD5274045ULL, 0xC48D9EEF272AE181ULL
        },
        {
            0xCEAACBA857909DE0ULL, 0x52C63462D90EB41AULL, 0xF4D230FB00A9566DULL, 0x06DE5572CCB136DAULL, 
            0x63D61448610E0272ULL, 0x8155BD98C7CAE992ULL, 0xAD3F7B0DF922C7DBULL, 0x896E1CCA4575FB05ULL, 
            0xF36A28B0472C8E9BULL, 0x6DB1FC14F360ED37ULL, 0x867CCA5F10B51775ULL, 0x074CE095A35019F5ULL, 
            0xA1573E25E670F6E5ULL, 0x275569CF213A4D6BULL, 0x28D7B5F15C0DD4B7ULL, 0xB7AD91359D6E8BD6ULL, 
            0xB371F05F9BD2876FULL, 0xF1B5FF94BC8D4ADCULL, 0xEB2FAC9911E95FF2ULL, 0xC2D6940E0B0C6703ULL, 
            0xE67C5FEBC8361BEAULL, 0xEAD23FE4606BCF4AULL, 0x3D26F089F69DCB96ULL, 0xD96C886603A28B96ULL, 
            0x0E84D6259DCF88D5ULL, 0xB87F3BFEC285C8C4ULL, 0x869824C0F5136EB3ULL, 0x66EE18AB39F3BBAAULL, 
            0x4D7DD88A01509F10ULL, 0x4D733E1020C8C4DEULL, 0xCFDE09DD1131E629ULL, 0x97DF883FE7EFEA9DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseDConstants = {
    0x553DE8F423E3B100ULL,
    0xAD0613AF79F1CD67ULL,
    0xAC625F2BA4DD5CBCULL,
    0x553DE8F423E3B100ULL,
    0xAD0613AF79F1CD67ULL,
    0xAC625F2BA4DD5CBCULL,
    0xE8111A29B190440EULL,
    0xDB2E9D99B792D06DULL,
    0x1D,
    0x3F,
    0x17,
    0xDC,
    0xE6,
    0xFB,
    0xED,
    0xB5
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseESalts = {
    {
        {
            0xF6D4933FC3BD9BC9ULL, 0x62D2A075352D51DEULL, 0x7E62EFADE776038EULL, 0xD7687AAF0131DE45ULL, 
            0x83C124D208A48EB4ULL, 0x0C4576C99CA7A3F9ULL, 0xE4348FE6F16EB8BAULL, 0xB5523A08453A30E2ULL, 
            0x613D8094443D6EC2ULL, 0x9E4BD1F471F44966ULL, 0x2A924FEFBBE24FDBULL, 0x647196FBCE43232BULL, 
            0x24C554FA32A4AF15ULL, 0xC6E55086A9FB66A7ULL, 0x836C1E14FC47BBBCULL, 0xB60B43C636625E99ULL, 
            0xA9235F0A5F20B2C1ULL, 0x029C377C58E95488ULL, 0xE3BEE14242AAEB16ULL, 0x207BD67D16A198D8ULL, 
            0x0700E9D60ADF57A6ULL, 0x66DBBD4851B92D5EULL, 0xAB086DA636078EDEULL, 0x90CAA04B5D405000ULL, 
            0x3067079DE1B3BCB9ULL, 0x1EED41AF15215DADULL, 0x020BEB6015DCF4D3ULL, 0x7AA2DD4ADE4CD773ULL, 
            0xCDE6ADCA7CCEA798ULL, 0x3056900F5ECC7306ULL, 0x6DF680CF7BCE8BA3ULL, 0x23ADAD9AD52BFF9FULL
        },
        {
            0xA1E8BAEA0EBA0BE4ULL, 0x609A4A6662651235ULL, 0xB4009E2CA204B553ULL, 0xC624DB93EEECF40DULL, 
            0xE0C17877263B22C7ULL, 0x43F4D56207F15716ULL, 0xD275DA9800C57BC5ULL, 0x316E90CE651B63AFULL, 
            0x1B03880490E77394ULL, 0xAF597948356F282FULL, 0x4641F0A1DA1EA60FULL, 0x1B6EA96FFD22E9E6ULL, 
            0xB0D055C7A328E706ULL, 0xD3717D42AF2CD433ULL, 0x35295FE398539775ULL, 0xA06CB1683CEE76AEULL, 
            0xF1B6EB3C53BF951FULL, 0x2FF20857D4F00215ULL, 0x7C0AF4D52F7CE1CAULL, 0x86A94BFE3391EC01ULL, 
            0xBC195B5C8B637BCDULL, 0xB0B26BB0CAE03AD9ULL, 0x87ED30B4293E66EAULL, 0x5F36428D16FCCA27ULL, 
            0x3842B59A423A2418ULL, 0x93A482299612A3D9ULL, 0xAC503D020897F649ULL, 0xB2281D9F123EF013ULL, 
            0x009FD5F01027C924ULL, 0x185329C2D65C69FBULL, 0xDDE3C8E5BA9AC8A1ULL, 0x8AAEB9976E5783ABULL
        },
        {
            0x16CA0119133DE985ULL, 0x820D57B8A3C204F9ULL, 0x31249615EE5FD1CFULL, 0x11660D41F65AD620ULL, 
            0x81348A62FF549ACEULL, 0x935BD57F64CB4C88ULL, 0x2C6F5E7D10EC88AFULL, 0x16FCE02D91ED6CA3ULL, 
            0xDDC2DB0EA2280412ULL, 0x6C4C956CBB48D8ABULL, 0xC1CEDC94F50440F6ULL, 0x82113D1EE0D32EEBULL, 
            0x3D85E8A58230DFB5ULL, 0xE623C653F58EA6F4ULL, 0xB063C2BB4DA8D752ULL, 0xD3207BF26F5A4C50ULL, 
            0x258774C9C459F4F4ULL, 0x2A041F3AF8E2750BULL, 0x6C94E935D2454F04ULL, 0x5A2F1831879947FCULL, 
            0x0821F0878747C571ULL, 0xDC1F3CB0B48ED118ULL, 0x7BC490707D245526ULL, 0x2DAB84DBBAA7AB6BULL, 
            0xE4D2BCB15105766FULL, 0xDC06D797380DED07ULL, 0xCE8B14197E4D43E8ULL, 0x5E9A49ED4982BA5CULL, 
            0x86A02A323EC4B924ULL, 0xE0D20163C19A54B6ULL, 0x611ADA44F6E3A265ULL, 0x0F3332C39D2808EDULL
        },
        {
            0x36DF78F085F63737ULL, 0x2E5A3CF79E76C81DULL, 0x50C0B69EB8015693ULL, 0xC4964672B3B2E1FBULL, 
            0xE8ED920D63772CBFULL, 0x3F4B67B54791691EULL, 0xA2A1AAEA60DF9380ULL, 0x6407C7F7358C2BECULL, 
            0x159BF86134D9D602ULL, 0x569CCE556070C451ULL, 0x3DD0C4EAE1D7AFAEULL, 0xF249A123B1B04BC7ULL, 
            0x283D533D0C62B7FCULL, 0x20B6D99F23B1B806ULL, 0xA534325BBF04F3D7ULL, 0x4F5BA51584E9CF16ULL, 
            0x295BB07B9B6FEF31ULL, 0x0E60C21EA7F42223ULL, 0xAA72DAAA7D5D8B0AULL, 0x7CE12C65637ECEA9ULL, 
            0x59B871B809C49E90ULL, 0x65F42B195B467F85ULL, 0xC4192491788A2F1BULL, 0xFB513124BE2CCE25ULL, 
            0x9A4F92F5A2802B04ULL, 0x379B157DCC56BFFEULL, 0x1DC1FB745CEE19DCULL, 0x89B3066D6D3E9B61ULL, 
            0xC921482DB7A24047ULL, 0x108E7B63E57AA194ULL, 0x15D37F5F06A67FADULL, 0x913B07D1FE28FECAULL
        },
        {
            0xA9A134030C13ECCEULL, 0x8391F792E7296124ULL, 0x0944A2886024DCCDULL, 0x4AFD26F302E745ADULL, 
            0x15B7299CE4FEC4B8ULL, 0xA1BC46758C09C05CULL, 0xB86FD1A60E9D484BULL, 0xA92E3D83BBA84C98ULL, 
            0x563F75A11D7B5A1EULL, 0x303071858E1484AFULL, 0x57B737CAC9B72E8AULL, 0x7E060BAAD71979C3ULL, 
            0xB41EDA1EF9989C02ULL, 0x333B65764AE8025CULL, 0x935CF6B5D5C9814BULL, 0x68EE7F408EDC8D55ULL, 
            0xD98AF15D19AC011EULL, 0x9FD8E2D3166A9F59ULL, 0x8BF57D3EABB56A73ULL, 0x38BA32423C964B16ULL, 
            0x138E2F23ABEC2182ULL, 0xCF931708590B3C34ULL, 0xE58AB8E1EEBE69E2ULL, 0xAF22E01B04BD65E7ULL, 
            0xF757FFD93E063457ULL, 0x67D6B2A97DCAB41CULL, 0x197FE1775191DFEFULL, 0xF4CF0EA34D91781CULL, 
            0xB1E491A1E347DCDCULL, 0x9A975AD23FE0F2A1ULL, 0x3F04F64CA26B71C0ULL, 0xD8141124E1A87906ULL
        },
        {
            0x9D5F7CC18E7CD00CULL, 0x8FF8201BDF3A9CA2ULL, 0x8428591C4C989301ULL, 0x421EC2A99FB2B05CULL, 
            0xB68BB4ED0F443844ULL, 0x3E594EC82628E7A0ULL, 0x34174EF2F89D7FDFULL, 0x28074BB23D1A4E2AULL, 
            0x4485FF466E64CE5CULL, 0x463CB822DE5BFA5AULL, 0x5249985942E0C80CULL, 0xBE0EA0177B0A5F7EULL, 
            0xF8FB4E6C93F48E70ULL, 0x1DD9C81613606A26ULL, 0x313CAC18DC7E6C9EULL, 0xC8A46805DF94111AULL, 
            0x0B39E03C93C07840ULL, 0x0843B73EF7513DAFULL, 0x317F92CFE9A129E8ULL, 0x1E2B43F1EB891293ULL, 
            0x5CA8126E2FB05F39ULL, 0xC4232F51B82F8A7DULL, 0xFF05CA709E0A65E7ULL, 0x6B73A0BC0183C340ULL, 
            0x1B960043B9B56F7EULL, 0x01D88E5792569D97ULL, 0xEB65DB36CB186252ULL, 0x97DF5B43B4E254DAULL, 
            0xB67370685EA6255FULL, 0x62E5296D4CA6A9ECULL, 0xCC804E15BEBCF3CEULL, 0x7D923076FE11C75EULL
        }
    },
    {
        {
            0x4AFBC7E18EF2B7FAULL, 0x69D8B81336704843ULL, 0x6189BE1CFA9E0528ULL, 0xC4D74CA779F5AD17ULL, 
            0x91DC026452B0EB32ULL, 0x3BCE7186409A6860ULL, 0x8688F6800F329929ULL, 0x04AC7175B7E24D59ULL, 
            0x4FCC3A8905697497ULL, 0xB788000CABC4F1D8ULL, 0x44665C3D2F3C2858ULL, 0xD09EE59EF2A73C68ULL, 
            0xE80BBF23ACD33BD6ULL, 0x290DEAC00C7F9565ULL, 0xB9A92E674EE27146ULL, 0xD14DA60A28A5B83EULL, 
            0x9DC66CE80BB1F414ULL, 0x95C0A43D387988CCULL, 0x925EAFD777440E81ULL, 0x880681CD32A667C1ULL, 
            0x849C535F91F7DD5BULL, 0xD38DDCF493A4C8F0ULL, 0xBAE659CB8FE67BE3ULL, 0x6F70E7F97BED8F50ULL, 
            0x4D2088AD8C06A9F3ULL, 0x4AC1A5FE2BD661B3ULL, 0xAA0357CFEB6EFDA6ULL, 0xCE36BFC7315498FFULL, 
            0xE7C9C55567D52144ULL, 0x5FEF654589584B9FULL, 0xDCB22E9C7DA0ABA1ULL, 0xECB700C26D811AABULL
        },
        {
            0x35AD284E851397C3ULL, 0x5F898ED10C96C4ACULL, 0x159A6D00CC718F9AULL, 0xED0709C76AEEC263ULL, 
            0xBFEAABE9B6F87B4CULL, 0x51B42962635E740FULL, 0xFB2214F320E04FD6ULL, 0xE4A4C6465F1C8449ULL, 
            0x31552CA2E78990D4ULL, 0xE2AE10809E443497ULL, 0x9A9E00DBDEAD51D1ULL, 0x344E665EEB0C9828ULL, 
            0xE2F389434F1F4D06ULL, 0xA60D43F08C99001BULL, 0x6B74578E705818B3ULL, 0xFF3386D7777EF245ULL, 
            0x71D03368A194BC8CULL, 0x2EB096CEFB15A99CULL, 0x5ED3D973B38C9E7BULL, 0xF7B896FCAC62B238ULL, 
            0x211E79E0FED47CCEULL, 0xE4D7723E2E952760ULL, 0x2AAD3CB510DBD57FULL, 0xE9B503C29D6BEF57ULL, 
            0x184BFC30A87C04C6ULL, 0xEC7E1DF5CBFBB4E6ULL, 0x8C9F392EE4A0307DULL, 0x4F1AEE1E1E6EFE8AULL, 
            0x3B48497061A5294EULL, 0x0549AF8EECC95FF7ULL, 0x3ACA1D0858A73BF9ULL, 0x04783D52566053B2ULL
        },
        {
            0xD014B07AE41738D9ULL, 0x712CB027665A5C49ULL, 0x0D26A64EE34E10C9ULL, 0xDDBAED7F90B35FDFULL, 
            0x240449B97FCFF4CDULL, 0x7A8195D159F3876BULL, 0x13F34F5F9766C174ULL, 0xA52EA9E50E78BE6EULL, 
            0x6F2E7C0D9B5330BBULL, 0x1636B771A368F901ULL, 0x5C00DBB6516605B9ULL, 0xE35F337775044718ULL, 
            0xB643C5751BBC483DULL, 0x43D825B947F1EA61ULL, 0x581200615EAA07E6ULL, 0xD579DC565D1CF81FULL, 
            0x5FF712F516353AEFULL, 0xE01522F6C9483D3FULL, 0x64B730C071DCDA39ULL, 0x0632AD2B82C8D3F2ULL, 
            0xD10A8EA6B09776F0ULL, 0xF7CE668619736EB7ULL, 0x587C1E515CA32243ULL, 0xBD9234AC8D590FFAULL, 
            0x9B9570053F8B2879ULL, 0x5A8D24F5045ECAB1ULL, 0x68BB87813E9BB62EULL, 0xB5897633F7A3421EULL, 
            0x8D9F9A5F4E379B88ULL, 0x3AEBAD522D7B8936ULL, 0x02529EDD1923A779ULL, 0x49B92D1EC9C42CDDULL
        },
        {
            0xBB01F5E22869B39AULL, 0x6D161C1EDED6A15EULL, 0xDA55F2BAEBEA250BULL, 0x44C3D3597587BDC8ULL, 
            0x3B2CF5E44779D9F4ULL, 0x107FA0FE1854419CULL, 0xCFE79369EE2A4468ULL, 0x1FBD23A81E2A32FFULL, 
            0x94A410D5A13F5A79ULL, 0xCB81824D59AE4F75ULL, 0xFD62AC5DBE3704A9ULL, 0x2B4A45E22F7E63EAULL, 
            0xE3C829789BDF7310ULL, 0x26493D86368092B3ULL, 0x9FDDB9D0E71453D7ULL, 0xDCED75FD364DDFCBULL, 
            0xFF6DC3888565793BULL, 0xE79FCF3E7AECC7B8ULL, 0xF5AAD7E6EFED1148ULL, 0x47D938E841CEF1F2ULL, 
            0x1D0C598F5878FF9AULL, 0x23A4F94AFA743F4DULL, 0xDD4F1E0055EE5D98ULL, 0x3AC26045F6D252C8ULL, 
            0x9D561985907F4C5AULL, 0x084797440054AA4BULL, 0xEBE478ADBC401BAEULL, 0xFD1A76C7FCFE4F7DULL, 
            0xAA74239F2B47D52CULL, 0x9B7A9D72FDCCBB3FULL, 0xF2180BFC3D61AAB1ULL, 0x1ED34A0743D9F095ULL
        },
        {
            0x01E77851C45FF191ULL, 0x08593DC6A2292603ULL, 0x41C26A9266BABEF7ULL, 0x641CA750AB532772ULL, 
            0xAE88CF04F32EDAFAULL, 0x26F927C9BB4BBC49ULL, 0xAE4E66EC81CBD2FEULL, 0x930FFD3300414203ULL, 
            0x39E004BA7CB0E6ACULL, 0xE378B720F93C62CAULL, 0x66082DC0842BDF73ULL, 0xDF9CF8E3ED401B4DULL, 
            0xC354FB2EC53910A3ULL, 0x800C8C42FFE5ABD3ULL, 0x2DF057A4B60D6666ULL, 0x923024BFDEB68718ULL, 
            0x3F79908E3D04DD40ULL, 0x8B32302C80E75039ULL, 0xCC151A132E1B00E4ULL, 0xF9B39634467FB7C1ULL, 
            0xF93FAA1BA59D3F14ULL, 0xC5B8A1FFE6813207ULL, 0xC4CD1AD52E28A925ULL, 0x0C256E4D14FCE7CCULL, 
            0xEDF9ABCC80F93767ULL, 0xCC3B81A31066DF8EULL, 0x24BB7586E8419989ULL, 0x9CEB29D0B1BD234CULL, 
            0xF7AB4448401DC9ECULL, 0xAD4822FF52CCCC28ULL, 0x218ECC90E4C62EBBULL, 0x26BA9313C30C2515ULL
        },
        {
            0x1C3337364ED1D193ULL, 0x92AF314E6904C3CBULL, 0x48EBD8DBE72BCC2EULL, 0x1C1BC82F8DE2767DULL, 
            0xADC6AB25E651E95BULL, 0x3874C2F95A0FCFF9ULL, 0x171B23AAEFE6DBFAULL, 0xBE68B87D41214E1DULL, 
            0x4DE63F308C237844ULL, 0xDBD226F057E27F1EULL, 0x023D5E783A5DA893ULL, 0x30B1391FB8AB0D77ULL, 
            0x57C6CA9064950464ULL, 0xA8883855771EB3E3ULL, 0xE1DD9CEA7D800051ULL, 0xDF65EBC7AB622FEAULL, 
            0xABE95969D83E908AULL, 0x3DEB43016CB1F727ULL, 0x80EB83B45B6F0E0BULL, 0xDA661DDDC1764FF1ULL, 
            0x5E094E169DF69CD8ULL, 0x350EBF2B7CDD05DBULL, 0xFC10811413DDBB69ULL, 0x08188E16C2586513ULL, 
            0x873DDC0D6FA4D31FULL, 0xF4F08A25DE008624ULL, 0x6C401239AD416CB2ULL, 0xCE0D29B9FBDD9E99ULL, 
            0xE05D127CE86B8243ULL, 0x9DFFDF50042D16B7ULL, 0x69BF05514081F450ULL, 0x80D90FA10C7C8C45ULL
        }
    },
    {
        {
            0xC10260C1E665D68CULL, 0xC703FA931BE1B19AULL, 0x25938DF8EEB1054DULL, 0xD9011B6B44A011ECULL, 
            0x81B2260111C760D3ULL, 0x54002385F20ED094ULL, 0x2FF355D2A728E5DBULL, 0x16B42E5803630013ULL, 
            0xA47DAAE7323C7F62ULL, 0x4FED6263F9C345DDULL, 0x3F01A8B69FEF9434ULL, 0xFE8052B980442B8DULL, 
            0x6A104A02DEF4A822ULL, 0x148516E94FE0DAD0ULL, 0x3951B77F56D07A85ULL, 0xE6A17B8FA5C27E48ULL, 
            0x0A87BF6F4AD6157CULL, 0xE2E8EAEE447E6E32ULL, 0x1B8FA2ACC03424EDULL, 0xE52672BB8B522988ULL, 
            0xEE615872EB681FC2ULL, 0xBDFF3FFCACEA616BULL, 0x72B9169A21F4FB01ULL, 0x90C5C526F85B9115ULL, 
            0x0625D1F45082BA81ULL, 0x30B7622410D7C42DULL, 0x58FA987E7F2D5454ULL, 0x84A62854D1F0616FULL, 
            0x8218B22C290DDE51ULL, 0x065AF8DC4415BDEBULL, 0xAEE2EEC5426A0B20ULL, 0x0F247CCDD9C3F33BULL
        },
        {
            0x631B88D4678E3C2EULL, 0xA046E37FE548D85CULL, 0x4C6948761D881914ULL, 0x07EEB9F375FB9A5DULL, 
            0xB5BF41C3D980C8D6ULL, 0x22A72A7542778871ULL, 0x7374C78799670A74ULL, 0xDB842AA04680A69CULL, 
            0x3C95E212DF7E4330ULL, 0xB802635B551D5BD5ULL, 0x00E8196408B131E1ULL, 0x6CC5C9335B1AD31AULL, 
            0xC7662C9DF511B292ULL, 0xF2EFA5FD7D175B0CULL, 0x21462AA1531B83C3ULL, 0x3AD03CB89091B029ULL, 
            0xB4F224BEE8CB18DEULL, 0xAD28E6CC312E270DULL, 0xD71AEAB6AA01DDDBULL, 0xE40B8B4BD314A781ULL, 
            0x7CD5B1DC54FFF7AAULL, 0xDDAA1B9727F2BB83ULL, 0xF0F415777232DA10ULL, 0x3D3170AC139CEC83ULL, 
            0x9E4BFF2AEC0B6634ULL, 0x895DA0BE05B949E2ULL, 0x964FD4D7755DEC3EULL, 0x12E182B888277F3DULL, 
            0x71505331FAC8D9A1ULL, 0x387A43BB48A46D41ULL, 0xA0AB8FB8C91F7356ULL, 0x25FE0E11CFC5FD4FULL
        },
        {
            0xB062DB74FEAD88E1ULL, 0xEA2105032EA4D1AAULL, 0xAA69A5B996A6DBBCULL, 0xBB181E8CF1B5EEDCULL, 
            0x2AFD9D70F4D5E79DULL, 0xDE3D338447C20969ULL, 0xAD5C405F37B086A6ULL, 0xE6C21BDAB3B7AC44ULL, 
            0x766413F4DDCF1E36ULL, 0x1367A101D73EC6F0ULL, 0x9F2DF5AA3E645213ULL, 0x2E1A2FE9DAB9C222ULL, 
            0xD6A6BF5D9508D86FULL, 0xC0CA115A7C170665ULL, 0x512263C58BA88476ULL, 0xB90DD55790846CCEULL, 
            0x307096C26E1F50B2ULL, 0x959D6C2FC967552CULL, 0xDFB09048BC26DD58ULL, 0xB9273DDB7C5FC84EULL, 
            0xCB4744D9E657CBC8ULL, 0xDACE5C77D92F6153ULL, 0x9B11069C3137BE07ULL, 0x86CD06E9646EE6C1ULL, 
            0xB8DF23090E8863D6ULL, 0x5B7B34A481E17DB1ULL, 0xB5058B0AAB95E11FULL, 0x7D1F2DDAB6E3104AULL, 
            0x86C499A3CF826E4FULL, 0x0D585F63C46394ECULL, 0x2B6C61F8278C1858ULL, 0x8E39A88B9D64E1AFULL
        },
        {
            0xAF165635B7D1423CULL, 0x000B25E930BD279BULL, 0x520984033AEF90FEULL, 0xE8AABFCEAF224F8BULL, 
            0xE67215B3E2E1C095ULL, 0x010F2EC29AAE6F3AULL, 0x3051B78B84AE5411ULL, 0x6FAD4CC5219EFEB1ULL, 
            0x27EFE3A12FA65BBEULL, 0x045C9430613F8B81ULL, 0x69E8BE2F766BD462ULL, 0xD39A5D6625541EB2ULL, 
            0xE82951EC0A7F1292ULL, 0x6CB3116AF8610EADULL, 0x8D9BD6BDA52C4847ULL, 0xAA5C4AA46FCFC71AULL, 
            0xFAE113B9E87B1A6AULL, 0x99AD68FA1D49D232ULL, 0xD57A117C7080F626ULL, 0xFA86EE35DEA68566ULL, 
            0x08535BD9C5484829ULL, 0x0690F386271BF0ADULL, 0xB31B9724F0D7B319ULL, 0x772B6D0A396FCEC0ULL, 
            0xCC44F0A72C27C8C2ULL, 0x5378C04EBD0BC811ULL, 0xF96BB2A5124048E9ULL, 0x712285229BD09976ULL, 
            0xD43A511EEF2F33FFULL, 0xCBCB76A30F36866EULL, 0x3853ADE7982F4E02ULL, 0xE44E053D9E6C6114ULL
        },
        {
            0x14DC6C5B4BAAE2E0ULL, 0x751B059E53EC2D6EULL, 0x932BF4193874F1B7ULL, 0x20F24E40A20DD1C1ULL, 
            0xC40D2893AC23C10DULL, 0x5F98D616CC5B6E90ULL, 0x2A78F0371331AF21ULL, 0x954A10F52E8A6B76ULL, 
            0xA0014E65B1A9AA6CULL, 0x39BD53FB9701C617ULL, 0x715AF2EADA1DCFD5ULL, 0xF1759BB4A37CBCE8ULL, 
            0x40EE9651D99EF9DDULL, 0x674FB3CA1C06AFFAULL, 0xA4D6DE59BD769BFDULL, 0xEF1E5F44F8F3F7A0ULL, 
            0x0A760BA1957FD86FULL, 0xDFE446B7A30921A9ULL, 0x85B3FB8E21AF5073ULL, 0x6A62A02B9739BE36ULL, 
            0xFFC87BE9506980DEULL, 0xC75809870E2F7A9CULL, 0xDC347DF5B69BFDF8ULL, 0xA9EEE1A4DECD6301ULL, 
            0x80F79A6B2B98A52EULL, 0x001734FF82B3549EULL, 0x0FDCF4DD87D686ECULL, 0xD8A29F69FEB7C809ULL, 
            0x60482A21882B4389ULL, 0xE88C26C108660877ULL, 0x889E49772B8A0AECULL, 0x073E39FAF95567E3ULL
        },
        {
            0x79F701390C7DAC0BULL, 0x0F175F60DBBD242EULL, 0x968F4CEFF3C1AA3EULL, 0x90412C4F3766CCCFULL, 
            0x7D8A1FECC7923F7CULL, 0x626A09CCBFDF6512ULL, 0x0B8790FF3AEBF860ULL, 0xE78E82DDCE0AC6C0ULL, 
            0xEECA8C660143C5A8ULL, 0xB0469BA89BA7216BULL, 0x7D365E343345C957ULL, 0x723EC4B8362B96AAULL, 
            0xCCD8CADF19A51A0EULL, 0xECC6BC37465906CCULL, 0x38265D6E2ED62AC3ULL, 0xB9B7647762C5D23CULL, 
            0x50C66F15D6F0D770ULL, 0x3886584E81204FA6ULL, 0xC0A3F5882BBE21BDULL, 0x5B5F614505FB59A0ULL, 
            0x9B5ED8A243D5B63CULL, 0x7D7D14C204832B9DULL, 0x60A0FD8D45BFF0D2ULL, 0x477FE39BC698BE8FULL, 
            0xEE68CD295C551DABULL, 0x894F4FB896724BE6ULL, 0x41D0E859D0BF1C60ULL, 0x204C68BC08860B4DULL, 
            0x90A28D1A842FD6BBULL, 0xBED872B296ADC17FULL, 0x1DC9C75DDE42D266ULL, 0x0DEDF406A5C63DE9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseEConstants = {
    0xC46F4D3E16D3D2C3ULL,
    0x70A5033E23B889CFULL,
    0xA15BF33407B6FBE9ULL,
    0xC46F4D3E16D3D2C3ULL,
    0x70A5033E23B889CFULL,
    0xA15BF33407B6FBE9ULL,
    0x406901347CD94504ULL,
    0x0289003169DD6F73ULL,
    0xB9,
    0xB8,
    0xC9,
    0x30,
    0x3D,
    0x1C,
    0x2B,
    0xEC
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseFSalts = {
    {
        {
            0x07541D00B744DFC3ULL, 0xC730A6BB07C45B0AULL, 0x84442062988D1648ULL, 0x9E890E0699FEA554ULL, 
            0x351E43C66A625454ULL, 0x14724E4583ED179FULL, 0x744850CF11CD19ECULL, 0x58DD207A2D116A67ULL, 
            0xF3E5312B8457C1D2ULL, 0x7AD6B6FD016C55FBULL, 0x9CB541E531257304ULL, 0x62138A6FDFDB1157ULL, 
            0x37EDC09BCA26BAD1ULL, 0x772009E27DF858EFULL, 0x5FA5AB81B22A7CDAULL, 0xB98BAA35ED41F983ULL, 
            0xEE21DD163BFCD50BULL, 0xC395C4983C87EE94ULL, 0x752D3FBA7B9A48ECULL, 0xD947753993D68620ULL, 
            0x600888B7F585B796ULL, 0x331338672B1FA51EULL, 0xA4AF10995E5913A4ULL, 0x551FBFD7AD6851F7ULL, 
            0xBC8FADAA38AF0749ULL, 0x1B25EC8BD1C174B6ULL, 0xDE52B55EEB051C21ULL, 0xE4F89123A222C28CULL, 
            0x29627920B192E840ULL, 0xC33CF9611484A8AFULL, 0x92EB63449B793007ULL, 0xF2D5A06FBE9D681BULL
        },
        {
            0xE49742E8C98A5B39ULL, 0x68152DE86A593C5CULL, 0x788FE4B8A9C75D05ULL, 0x917D3FC8B456F02BULL, 
            0xC91CF36BBFBBAC36ULL, 0x73552D5898E2BBD0ULL, 0xFCE122E4496528B9ULL, 0xD9C68C8D2655AD62ULL, 
            0xD7E1B6395A1931B0ULL, 0xBCD7A79E0B978102ULL, 0x620E77D552591405ULL, 0x75186C0A854B1A89ULL, 
            0x979B4C826B10AF09ULL, 0x39874B816630AB07ULL, 0xEE1BF5F81C5C0FE6ULL, 0x04101844BF7F492FULL, 
            0xB14867443A170196ULL, 0xF8C8135F049AB524ULL, 0x5B865DCDD701B665ULL, 0xCEEFC903EFF19D3BULL, 
            0xDB6FB2120D92F30EULL, 0xEBBBF1D5227134D9ULL, 0xADB3ED51D718D23FULL, 0x943E61971B4A1505ULL, 
            0x60479E369F29EDDBULL, 0xC3C841D7DCFDE561ULL, 0xF2EC38B6C1BC748BULL, 0x5EDE69410DB909C8ULL, 
            0x60C226DB5A965FEDULL, 0x20450B34A3F3E8FFULL, 0x8FCF7DAD56A6A455ULL, 0x938270B0BC2D9B36ULL
        },
        {
            0x5700E758E8F3476BULL, 0x4DCA81D1A8F32152ULL, 0x533ABDC886D0C062ULL, 0x0733EFEB46AFF804ULL, 
            0x65CB7551DF6F5658ULL, 0x73584EA0CBB8F77CULL, 0x2A86D382C678E014ULL, 0xBB8E24DD665E9DFEULL, 
            0x6C56658E8E8FC790ULL, 0x107075A58ED89A77ULL, 0x0B15C526F9A58089ULL, 0x8DA159D296156293ULL, 
            0x88667399FB2F6732ULL, 0xB7A4F3C15AE08C66ULL, 0x5F1BDBBE1E67B8E1ULL, 0x9F173B97265331CDULL, 
            0x5315DA4161BB745EULL, 0xA6E4E6369A4F40CEULL, 0x43D583DE7275BEEFULL, 0x071716F3228544D4ULL, 
            0xCCB90351A0E8B33BULL, 0x3E8819F15FFC89B9ULL, 0x506BEA349DD2D4A9ULL, 0xC8B757077F0CD0CCULL, 
            0xD8709D5898DCCF52ULL, 0x00FBEC77815AE956ULL, 0xF89674F375BC7C1FULL, 0xC27BB155975F5A57ULL, 
            0x2469AD763A34B48FULL, 0xCCE055C736369EBFULL, 0x30C7C940CBC8E580ULL, 0x1AF063EA651BEE5BULL
        },
        {
            0x68EB1E1C4D9D932DULL, 0xF37E54EAF4C04FF6ULL, 0x6C5352356EF9E8C3ULL, 0x002DF565C16D891AULL, 
            0x6BAB830EA450AC7FULL, 0x18566ED8E01635D0ULL, 0x3A86820F6282C5CDULL, 0x1E0FCFF92AD435F3ULL, 
            0x55A414FD6192F7EAULL, 0xA90E8F633F792998ULL, 0x362A5C27846E7838ULL, 0x65EF30AC91CF87E6ULL, 
            0xAA902DB976DCECDAULL, 0x3CDD348C0BFBC0E9ULL, 0xBD862A7C25DB56BAULL, 0x62D1846D20435646ULL, 
            0x53D27DB152ABF706ULL, 0x4E4B6FEEA1E20B1BULL, 0x92A65FF018ED5C47ULL, 0x19837A33A3C24478ULL, 
            0x65F57444A129CE0BULL, 0xD08E2E5356F57ED9ULL, 0x1AD6A37DCD9F17FFULL, 0x5836E8DCCA7B0FAFULL, 
            0xD2F8164047CF5332ULL, 0xF1D750920F1ED4E2ULL, 0xFC1285B827EEF172ULL, 0xAE6C21F6C64B55F1ULL, 
            0xEC0352653E911571ULL, 0xA8EE110850DDA29CULL, 0xA8B0EECD5CF4B2FBULL, 0xF34D14AB23B227BCULL
        },
        {
            0x83290461643C0DE6ULL, 0xD0E5B06C194CF6F9ULL, 0x3938DD2745D70445ULL, 0xBB668794EFBD485EULL, 
            0x8B3ED615A4DB32C8ULL, 0x8A6D3D48879A30F6ULL, 0xCCD0C32D4CB9A785ULL, 0x4838040AC7829687ULL, 
            0x4BE57C7FCB22A3A9ULL, 0x66E6851C0DD28C96ULL, 0x4D7A22E412D75374ULL, 0x15C8438B53173916ULL, 
            0x37C2919CFA2DFB5AULL, 0x787E645DC915FEB0ULL, 0xF75B806BB06D5241ULL, 0xC23C9EE84C6B2C91ULL, 
            0x9E852DB5FE9B686FULL, 0xBE3D202011C891AAULL, 0xEB45847594E3A541ULL, 0x3B94D89F2E82CCDEULL, 
            0x1BAE561AF2A00EB1ULL, 0x06703E7B9E91CD8EULL, 0x905B3E552E6A7655ULL, 0x8FAAA11BF89EE935ULL, 
            0x194D0528F24C00A8ULL, 0x32D070F8464D1047ULL, 0x87503D8165864007ULL, 0xD5C0DFAC2677A5DCULL, 
            0xD981CAE5D7F9B647ULL, 0x4CDCB3D203EBD345ULL, 0xC072955695CC75BAULL, 0x99593AFF258EE167ULL
        },
        {
            0x35C0D7EB46572901ULL, 0x4308CA3728D366B5ULL, 0x9F4F389F59DAFF4BULL, 0x3588B1A90492ED51ULL, 
            0xA96CEB5F8B93587CULL, 0x34BE943D2697796DULL, 0x1A59E0CF3893B3AAULL, 0x75854A27F0ACF7EEULL, 
            0xD983176FC6497FBBULL, 0xF7289BDA4639CB5BULL, 0x842091661CE50F56ULL, 0x6E20E87A361030ABULL, 
            0xA525E2A19DE8FDC4ULL, 0xBC18A5B2888BE67FULL, 0x5E9EC84D8B142992ULL, 0xB4547B06E8789BFCULL, 
            0xA485B9EE411F4888ULL, 0x6C8CCD6D345352C9ULL, 0x564E0DC3CD8EBBDBULL, 0x03D719752BF1DE23ULL, 
            0x9446C133DC44E489ULL, 0x41B24D121F700464ULL, 0xA6054D56F9846961ULL, 0x7B274F31A3280B6DULL, 
            0x7148E4D63DCA1DC8ULL, 0x40CD5DBD82438E57ULL, 0x624681415FE7AA55ULL, 0xC9B661178903E885ULL, 
            0xB97DBF8FB906E90CULL, 0xD676DE63E9ED0396ULL, 0xF2BCB8C461DCC933ULL, 0x1ACD6967A1612A1DULL
        }
    },
    {
        {
            0x8DD3E958D7F6273BULL, 0x5EA631AD09CE3432ULL, 0xF4959BABE6A49E67ULL, 0x982CF043F5337506ULL, 
            0x5971DDDAC20976C4ULL, 0x4F222465BEE8CBE4ULL, 0xF877043279517D6EULL, 0xEAEE6BED34AB1ACBULL, 
            0x822C3DAE059053FFULL, 0xA760FDA00BD37FF2ULL, 0xE1E76EFC07503722ULL, 0x5F6DDE332C0E3D85ULL, 
            0xED6252D396E05795ULL, 0x53775E7EBE04BD46ULL, 0x1A1DDD3EBCD8CD0EULL, 0xCC86F8E8F6ADBCA4ULL, 
            0xEB0D35BEBF76EABAULL, 0x45F44E3F69072F97ULL, 0x5D34729E0A5C8DADULL, 0x45E444A04FE20A39ULL, 
            0x7F01BC01190D08EFULL, 0xAC417DD23305A0EEULL, 0x1E021902203F4F6AULL, 0xC8D3CB64FDDE17DFULL, 
            0xAEB5B6FE7E2FCB69ULL, 0x6C46DD476251B9E3ULL, 0x81AE0E6F1224450FULL, 0xDE6154C614AA1C45ULL, 
            0x6706CFF2709598A2ULL, 0x83ACB583DEF9D440ULL, 0xDC0B9BD2F385C2A9ULL, 0x90F2251CF9305417ULL
        },
        {
            0xA6846FB4355AF3ABULL, 0x40E8EA2A1C0C2227ULL, 0x6DDD2ADFCA1F4380ULL, 0x12BEA71D63988689ULL, 
            0xE043FC39BD7274D6ULL, 0x195B687EF2FCE46DULL, 0x3882EB08C111BDD3ULL, 0x9014C693CF3372B9ULL, 
            0xE0FAB99DD443EBCBULL, 0xFF35CCE823139FFCULL, 0x153DE1219AB96D28ULL, 0xCC1ED07D93823B8FULL, 
            0x580BBFB69BADEA77ULL, 0x4B5433BF837853DAULL, 0xA586CEDFB9E5938EULL, 0xC4A88487671EB421ULL, 
            0xF0129036189F9BD5ULL, 0xADCBF9D89009448AULL, 0x2A84D1548A041E47ULL, 0x22A07289D4E136D5ULL, 
            0x72D10004F612126CULL, 0x506F2BA937F408ABULL, 0x243CA4FCDB2FE927ULL, 0x2BE79659D54A4D75ULL, 
            0x985DAF1CE8911235ULL, 0x899327931B0F6B7CULL, 0xE14E897A159CFD19ULL, 0xFC55F1B834A2578DULL, 
            0xFC4815E2CE45A3EBULL, 0xCD9B0586783303AFULL, 0xDDE175DA79E9A6B4ULL, 0x6774B37EBE1582E9ULL
        },
        {
            0x17956DCE7EE676C1ULL, 0xA567211C55F2D55CULL, 0x4B129BAE6153C982ULL, 0x71D50FAF690EA986ULL, 
            0xBE1E8583CB39A2C2ULL, 0xE8A9926B51591922ULL, 0x4D56EBBE50A6BBE4ULL, 0xFC43B8ED3E46C396ULL, 
            0xDAC05DFB50F9C51AULL, 0x8BDE1BC088946290ULL, 0x293A392ACBB0275EULL, 0xB30799DC4FA2C2B2ULL, 
            0xC191D6538D1A7944ULL, 0x49A72FDF5A1613FAULL, 0xFCD7AED5BF8574A9ULL, 0xE44BD1FDCECFFB40ULL, 
            0x9153AB708E06BDC7ULL, 0xAF3F2E4738BF3949ULL, 0x8EAF61355F8D5942ULL, 0xFEF8A4664449672BULL, 
            0x72AC72858DEE860FULL, 0xAAD0171D2BEF36F4ULL, 0x73991A26292FCD5BULL, 0x836594781E0F9CD5ULL, 
            0x92BA5611AE36053CULL, 0x6B9255E17E0DEBC0ULL, 0x0EE422D2BBB8AF47ULL, 0x75A632B5AB46F47DULL, 
            0x04E3D79DB65465C5ULL, 0x96D775CFEDE9F8C1ULL, 0x0103207F2BBC448EULL, 0x97DF73EAFC95A1FAULL
        },
        {
            0xFA99C51453492BB0ULL, 0x1D25E9FC2EF0D159ULL, 0xC1EED56607E98646ULL, 0x012C5DC09264DA1FULL, 
            0xD857EF32F5A57739ULL, 0xF3A0236A2CF1DC49ULL, 0x9A5E576C65D2144AULL, 0x65F552AC22B57373ULL, 
            0x053E9C5D30AAB83CULL, 0x1C2347060E82D40EULL, 0x81CBADA9BA51E683ULL, 0x0A5C1C0DAA1BFEC9ULL, 
            0x97996D1C267DF0D6ULL, 0x39DA104492794FCCULL, 0x4C9D5BEE5FFD4AC5ULL, 0xF34EB278D08CBBD9ULL, 
            0x0739149C1893BC73ULL, 0x62108DAECBFC4E08ULL, 0x7E898AB7E02EE7A0ULL, 0xB1C23EC3657505D3ULL, 
            0x7FA10A028F0E42AFULL, 0x87283EA96665B616ULL, 0x1CED3D2485704C81ULL, 0x75E48E1E03A182C3ULL, 
            0x0A814A895876B48CULL, 0xCE79F703B742A454ULL, 0x67F25D03F3D944A1ULL, 0x1D9E3BCACF7BAA8FULL, 
            0xDAD26581DCB08806ULL, 0xB0A45E8777809C79ULL, 0x5BA535690B60ACB2ULL, 0xA85E5F66F8EABF6BULL
        },
        {
            0x9A507D3F9ABD8FBAULL, 0xED069F5CCD765B76ULL, 0x6AD5089E53BE3CFBULL, 0xD7F6041E0E3A38DFULL, 
            0x5CCF9D25B7A889DFULL, 0x9A5B51369DEF2F85ULL, 0x5BF50F0EFE9E2E2DULL, 0x5DAF52B3DA42CD4EULL, 
            0x4817A9B22248366BULL, 0x6FDB018F5684801CULL, 0x19A7D54B946E5D8EULL, 0x766FCE21CD714F08ULL, 
            0xC1FF2A8FE9511DB1ULL, 0x5003352AA406EB24ULL, 0x25297D89BC68B732ULL, 0x68D6FEAC85E45AD9ULL, 
            0x463A684C64B1CFF2ULL, 0xB999C00BCC39BEF7ULL, 0xC711F52A01B43003ULL, 0xAF844FCCFBC0ED3DULL, 
            0x12535CDD7581C1A8ULL, 0xDFCB4FCE41789C8DULL, 0x380B734C1B2715F9ULL, 0xB33E0851F16C4A3EULL, 
            0x9C4C6CBC539FE9C9ULL, 0x4829ED7E56D0BA4CULL, 0x06D6BAE968331EDEULL, 0xF64DEFA5E77C1F25ULL, 
            0xE09D541E1831B327ULL, 0xFE52C5DDD3F762EDULL, 0xB7166EC77DE92C34ULL, 0x7892AC489412605EULL
        },
        {
            0x0300977A70C13647ULL, 0x2B99C67D6FF504F3ULL, 0x3E2A2EBF1FD27575ULL, 0xEFF42A1641049952ULL, 
            0x6E8BEAD87974729FULL, 0xDF853068DE447768ULL, 0x86544C924EFBC0A6ULL, 0xC05AF33B8B30A20DULL, 
            0x04DBC16482D5F362ULL, 0x767818EBC8FC3779ULL, 0x139647367479710FULL, 0xF0782643976B4000ULL, 
            0x79738E93C472983DULL, 0xAC5F1B9A3D4DFA6BULL, 0x79294EB5B87F2E37ULL, 0xD96FF980BB9AEF3CULL, 
            0x08AE2FBD065B791CULL, 0xBEF0384DF5E2CDA5ULL, 0xD49BEA2C30649AF8ULL, 0xA3A92D5ECA39423FULL, 
            0xB066A3F0487C409CULL, 0xA9B5DA03C4E4F7C5ULL, 0x2D994518419FF839ULL, 0xE875324EC53B4DA5ULL, 
            0x24FE98F9FCEA99C1ULL, 0x6A747625610BE6F9ULL, 0x02EF821078F3540EULL, 0xF35ECC1ABA37C48CULL, 
            0xC3E49CFBD615C647ULL, 0xB21B2F3DE4AC64AFULL, 0xAB3228CAF85EA2DFULL, 0x9152DBE89B6D34CFULL
        }
    },
    {
        {
            0x11634120371ED339ULL, 0x24889B93A6BC98FEULL, 0x0C3085888556C3A5ULL, 0x3FF9991BDF5FEE0DULL, 
            0x881642DCCC05EB1EULL, 0xF7D0310A8AB7FFDFULL, 0x0F0BEE66BAF89AD6ULL, 0x282E7060DA493B7EULL, 
            0x15D140B1944E570BULL, 0x2AE18D363F72DD34ULL, 0x8063DC043BF0133FULL, 0x5EDFC3767D80B6AEULL, 
            0x00876A4553F0E343ULL, 0x279C8CD4E549BF8CULL, 0x60E7C5E1D31DCC76ULL, 0xFD0E492526A0F0AFULL, 
            0x26A73C20114FF2A5ULL, 0x8F26BDB7653FEF36ULL, 0xD380C068DBDADA8FULL, 0xF03D81BC5500B201ULL, 
            0x9F1A63DB9ED5CD60ULL, 0x64F6B3493BAC9D86ULL, 0x79B2621C9EBA9773ULL, 0xDEE20F6D722930FBULL, 
            0x097EF1D75DDD7981ULL, 0x9B53F05A92C9E49DULL, 0xEB0C991FB9516374ULL, 0x30AED0DEC8CDF8D1ULL, 
            0xCCD383B54FD01A76ULL, 0x4F7F7D21D68BB07DULL, 0xF4CF88AC912338D0ULL, 0x05E4039907BF4690ULL
        },
        {
            0x05538298B8AD68E2ULL, 0xC8CED58DA2CB4FE3ULL, 0x258C61C6D3DE02CEULL, 0x3C40D4A9866574C0ULL, 
            0x08913A492BDD5F88ULL, 0x07633E941A31E4AEULL, 0xC424D7D7CCB96EFAULL, 0xB22E74FDFE27E1ACULL, 
            0x69C23BE0E7CECC29ULL, 0x66A9EFA19F787F1CULL, 0x64FD5FF05D368AB6ULL, 0xE704AC0E6822055EULL, 
            0xDB167A4E529B29A9ULL, 0x11D5171B41024D07ULL, 0xA257BA456B66FDCEULL, 0xE95A926F89EF5EDBULL, 
            0x958B4BAEFA66B38EULL, 0xECF416D9706CE310ULL, 0xFC966D6FD5CAD1CFULL, 0x6C63FEAE144AB041ULL, 
            0x328CEC25C45D1AF7ULL, 0x156999FA82B1FCD7ULL, 0x1433BCAC935D7780ULL, 0x4A5E4DB79DD93158ULL, 
            0xD62EAB507633FA76ULL, 0xB567C612134A3960ULL, 0x3571A32A6D542E44ULL, 0xACCC3C56C9936183ULL, 
            0x68DACEAA366CA330ULL, 0x48E2A62C6E654319ULL, 0xD53660D58C5B3222ULL, 0xA5235259ACE9B660ULL
        },
        {
            0x53C7944CD5198C67ULL, 0xE65F05676B0DE862ULL, 0xCB8BABBDF9B6B606ULL, 0x2C60C60AA2E67799ULL, 
            0xE1674FE0CCD4B73BULL, 0x4AB971C50CBF94AFULL, 0x4789CC97B4B7FCB1ULL, 0x211C4626C27F5086ULL, 
            0x490406D11D49931FULL, 0x4F63678CA1C5CAC9ULL, 0x759E6E5106EC8859ULL, 0x7F21457FBC26CE10ULL, 
            0xAE24349124245938ULL, 0x6C92B90A90DBEAE8ULL, 0x6F92FCDE5A886F15ULL, 0x49016D0A65132F26ULL, 
            0x7543A4C23FF104CAULL, 0x6596E2954967EEC4ULL, 0x717743AFDFF3F0CDULL, 0x860F27A78A79B260ULL, 
            0x0A261C14CC8B2C1FULL, 0x8FB58EFB41F28196ULL, 0xDB883CD416EC039DULL, 0x482D1E35C273EDACULL, 
            0xE0F1E85617DA6984ULL, 0x299F5E8353E8B37FULL, 0x5F20AC48D7FA51B0ULL, 0xFD5BF5B8A75B5E92ULL, 
            0xA8FAB5E916F461A5ULL, 0xED8E275871F80EF7ULL, 0x9E132606869390CDULL, 0x976F78443F1980D6ULL
        },
        {
            0xCC4DE9221618BD4CULL, 0xBCF0333246139665ULL, 0x3BD65F1D826069B4ULL, 0x26D04762894E3F34ULL, 
            0x3CB6CE0DA7464676ULL, 0xBFEF6ECAA6498F8EULL, 0x0367A6C371826536ULL, 0x11B7E170F37AE21EULL, 
            0x5C6E939BD2E971D8ULL, 0x14278D48677111AAULL, 0x1FAFEAB24A8DAC08ULL, 0xFE0E5EF8D0DE56BFULL, 
            0x77068BB6739F9BA1ULL, 0x5159C0FE5A6A24C0ULL, 0x011FEA6231FC5E3DULL, 0x01B26981B2B4B5D1ULL, 
            0x245074FB79CE7691ULL, 0x792C0514F682B390ULL, 0x2524C61491DF3383ULL, 0x677AED7AAFCD2A97ULL, 
            0x51357B21149455CDULL, 0x58E6554C02A980E4ULL, 0xA0BF1BACBD6ABC5AULL, 0x8BAAB419AD53884AULL, 
            0x7524E21D4A94A67BULL, 0xCA004BBBEF4DB1EFULL, 0x7C565C8D2C3B88D6ULL, 0xCE702AC9F563B158ULL, 
            0x31924F5B8FFA9E35ULL, 0x315F4FEC807DB500ULL, 0x4CF3BE1735B6B920ULL, 0x553F6B1579DC7110ULL
        },
        {
            0x9EB2522B1EB46D02ULL, 0x623C2CEFC312974EULL, 0x40215F7502D9390AULL, 0xFB8E53441E798BFAULL, 
            0x7DEFDA6C17D25784ULL, 0x9805FA502E4DA2BEULL, 0xC90C5A671D08ED5EULL, 0xC2BCA638C3779D46ULL, 
            0x3BFA438F7CD401D4ULL, 0xEFAD18ACC6C8ED0EULL, 0xBC4BC97860909DF6ULL, 0x19A88A709C968FD0ULL, 
            0x1FC86B5E092973F2ULL, 0x0A594A8D07F77A3EULL, 0x0B1AFA4947603DA3ULL, 0xC2CAC5534A03525EULL, 
            0x9BD5F9F816DEB516ULL, 0x0AE169A4344FA029ULL, 0xC44513582577876AULL, 0xB2E7A7CCF2AF47A8ULL, 
            0xC2381F5D529A6F61ULL, 0x2013667053D608F1ULL, 0xE1994BAEA986F403ULL, 0x606DFC6489CCCA5EULL, 
            0x92343F2363CFC852ULL, 0x70CA90B3F5733EA4ULL, 0x101FDB9561085B9CULL, 0x335554A75576C7E3ULL, 
            0x8BFD76E415F8AC00ULL, 0x8096EC4AC4A4EF87ULL, 0x41E23140ED063FEFULL, 0xA6BBCCDD22F91E2DULL
        },
        {
            0x3783D42C9A70EEFFULL, 0x5A26DC9919FFB159ULL, 0x08B049946EE13C26ULL, 0xF0F347AD332FB5E1ULL, 
            0xDDA9E23D8C7261F8ULL, 0xDE61AB8FF9F4929CULL, 0xB9BFCB3CD41BF2BEULL, 0x2795D7636F517DD0ULL, 
            0x972C9E4FC7BFCE84ULL, 0x1F48CBA19481EE5EULL, 0xE90D184EB780348BULL, 0x83783242F7EB3363ULL, 
            0xBF590E0C4CAB5E55ULL, 0x9C47C0B7091CF628ULL, 0x86F8E27DF1DF3B63ULL, 0x0422FD17BCC20B6EULL, 
            0xB511BB4D476D0691ULL, 0x681B837D4382A3FEULL, 0x95E862B03B48E724ULL, 0xCD97BA60DE08F16BULL, 
            0xE6C0549AA3E7DF3CULL, 0x04DA0BC5B79F7D08ULL, 0x860390EFAD36C8A6ULL, 0x396CE794CC1EE2B9ULL, 
            0x4B6F2F4AA30FDF9EULL, 0x2B8FC3A66FDE8BDDULL, 0xCC291A0D6DFE1923ULL, 0xEB19B58961C721A4ULL, 
            0x379A4E9F4619531BULL, 0xAFE33650DCA635EEULL, 0x68BB816C7EA2DFCAULL, 0x3227D5C7CA2B09BFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseFConstants = {
    0x6DF194B9351D0A79ULL,
    0x9521DD07B2F05D01ULL,
    0x428D39BD1C5173C7ULL,
    0x6DF194B9351D0A79ULL,
    0x9521DD07B2F05D01ULL,
    0x428D39BD1C5173C7ULL,
    0x6D8C3481F887C8C1ULL,
    0xD607E59120B1E37DULL,
    0xA6,
    0xA7,
    0x2C,
    0x9B,
    0x1A,
    0x7C,
    0x43,
    0x46
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseGSalts = {
    {
        {
            0x17C27577F16B409FULL, 0x3F1990AA30C01B2DULL, 0xC20EDCB0E40AE4A0ULL, 0x80315752FBF848E8ULL, 
            0x3506D9E99078D86CULL, 0x61F2ECFDD2ECBA65ULL, 0xFD6DC8760FBB4F67ULL, 0x881EC4C0CC1495C0ULL, 
            0xEB7CD15F0A67D78CULL, 0x8CAA96C42D44B182ULL, 0xB552CA3C92756D44ULL, 0xB9103997EC49CCA7ULL, 
            0xD57EC07B137D73E7ULL, 0x2F64D4F11308B3D1ULL, 0x24430CCBFF6EB0F9ULL, 0x77F0D8F7B7F68E1BULL, 
            0x6DE67057EE9F7154ULL, 0x5679EC9C559A2BCBULL, 0x66404C599F8A08C4ULL, 0x3E04FAF756EFBD74ULL, 
            0x678AAF357AE2091EULL, 0xF051CECF950BA426ULL, 0x4D7B61E7392FF93DULL, 0x2EEF3111ADD3397AULL, 
            0x372600783296DAE9ULL, 0x5C417B418A9CD95AULL, 0x985E006ECEE46DC8ULL, 0x06EB5651CBB7BC9CULL, 
            0x322101118ABEB5CFULL, 0x0ED30DEAAF45FE12ULL, 0xDDAE89184C9D4EAFULL, 0x43E4CF1EBA6FDE82ULL
        },
        {
            0xFFDD4C48BE4B987AULL, 0x6DA748633C365FFEULL, 0x2B8777BC39F46749ULL, 0xAFE1CC947AB84576ULL, 
            0xCFBA8E63CCFEB406ULL, 0x736639975A50C69DULL, 0x38034B1CFE5166AEULL, 0xAFAAAC48D26DE54DULL, 
            0x0F253412C7DDD617ULL, 0x7DF5B7741431767AULL, 0x1DF4703C8DD60203ULL, 0x095F901E5B1A765BULL, 
            0x09254693C8214871ULL, 0xEA6FB05FAB53A3D8ULL, 0x89C113F2F67B2684ULL, 0x7320CB0DEBAB7630ULL, 
            0xD9F794A0907E1CC6ULL, 0x5E982A64E8D786DCULL, 0xD4D05EB80A2BDD7BULL, 0xD09566BF89899711ULL, 
            0xEA3D590F9D394DE1ULL, 0x12030F767BFEC2D5ULL, 0x7A670EC02D6D2014ULL, 0x59AA003DBBBAEE8CULL, 
            0xAEDBFDCBFBCA5D69ULL, 0x1CC5E3BBAFBCBB19ULL, 0x8471E19B679D63DCULL, 0x58DF7C4D19E160E8ULL, 
            0xB4B071B53A258875ULL, 0x86BAF0A1161B9DDDULL, 0xD59F74994D0AB19DULL, 0x344C5BF844EF6E5DULL
        },
        {
            0x45721695296B965DULL, 0x3A7AE6D7656421D9ULL, 0x648828C826BB21F1ULL, 0xB64ED5ACDAC48EEDULL, 
            0xB840FF2434061F22ULL, 0x085324EACE88C015ULL, 0x4CEA9B4794DC26CAULL, 0xB684FBBF89389189ULL, 
            0xC4E4FAD6E8B1A3AAULL, 0xEF362F1B91C21B1DULL, 0xDE261B440F92BAA0ULL, 0xBD93CBF1649A8083ULL, 
            0x82E51468CCCA81C0ULL, 0xC0ECC4FCD79A5E66ULL, 0x511EC2A0CED28526ULL, 0xA0D21131E9CBC42EULL, 
            0xC1D0B4ED39B2E0A2ULL, 0xC992580E341D37D6ULL, 0xFDF3D8530C6ADD5EULL, 0x95C020599A7ABC50ULL, 
            0x685D5801E5A99450ULL, 0x0592CD9F133ABAE0ULL, 0xB507AAFF89F20B2AULL, 0xF5E6BDD416A41E9FULL, 
            0xC08569A7ACE20494ULL, 0x24FE1A160F5E50D4ULL, 0xF20E24470EBB0FA9ULL, 0x8D45DEC0BBB93B70ULL, 
            0x478701509565C1A3ULL, 0x98956A9B297253CBULL, 0xD2BE96AF6F869CDEULL, 0x7E8EE03CDDCDC2CAULL
        },
        {
            0xCAD8D0117144EA87ULL, 0x1AF3FCB15D2B6A5EULL, 0x32861766C84CDAEAULL, 0x9A3EA8A0CEDD9188ULL, 
            0x98D4EA9DB4EFDAABULL, 0x7993A41EC3B2346DULL, 0xD423E6A921BE1648ULL, 0x21822DC5678C9FAEULL, 
            0x731836B3BD065F37ULL, 0x6B91085330C3D97BULL, 0xC0B317FC419316B6ULL, 0xD1E2D80D080933CBULL, 
            0xF8589E2F67937C90ULL, 0x747923371BC27456ULL, 0xF9C79191BFAB8316ULL, 0xCCCFE39A296EE9D2ULL, 
            0xDB618F978EDCC3FAULL, 0x67E36CE183736B09ULL, 0x5F4EA8B1C803DF3DULL, 0x1C96EF2E47BC4AEBULL, 
            0x0614526084140DDDULL, 0x8ED844205DC9392FULL, 0x650B6E65B0872261ULL, 0x17DEC65A4826C4ACULL, 
            0x8B9210F0281CB8DAULL, 0x3651A9AB1AFD1970ULL, 0xAE3EFB3D85231F7FULL, 0x0CF1DDB633989DF5ULL, 
            0x29FF141E56F5FF7CULL, 0xF54E52C390BEB870ULL, 0x3513FB77265DAF85ULL, 0x207D6FAF784E56C3ULL
        },
        {
            0x5D5FEF14F8E43DA5ULL, 0x24972AB9FCB0F6DDULL, 0xE56D041F635C07DDULL, 0xBBCABDDCAE89A7C8ULL, 
            0x13E048A1F107C6FFULL, 0xB7A7D7350D7D6EAEULL, 0x113D77E251AA4AD6ULL, 0x0AAB8458E9432E17ULL, 
            0xD21AF2405FA4FAC8ULL, 0x9895E321B72027CBULL, 0xF014869F1810EA20ULL, 0xB5D182B0B4FF958BULL, 
            0x0CFFA3BEADA2455FULL, 0x35AFCEA000298EF8ULL, 0xF7B9C7A8A6EA910AULL, 0x3A59152BCF4804CBULL, 
            0x13580DF85E579BB6ULL, 0x8BC8B063897F88D3ULL, 0x8E5879512A644D07ULL, 0x67E5584A6DED4CDBULL, 
            0xAB38AD2AD631E7DEULL, 0x6A9CE781C308B6FCULL, 0x0065D6C4730D98DAULL, 0x383610431CBB1437ULL, 
            0xFF6A87167905B73FULL, 0xD80C6FEC466959E5ULL, 0x2B65B2B89EBB760CULL, 0x8255C3B421931B4EULL, 
            0xCBF59A655E67DDD1ULL, 0x620D58353A4B8355ULL, 0x0A47474ECF421EDFULL, 0x97DC34A412489387ULL
        },
        {
            0x9B466EDB6EBF3F92ULL, 0x9BEF4F0F923C7663ULL, 0x64755D587281BD6AULL, 0xC15881E6C6E20DD9ULL, 
            0xB7908A2616AB7723ULL, 0x36F0B545453F17B0ULL, 0x3EDA3546E4D351E1ULL, 0x7ABB5B3232DF62DEULL, 
            0xE09CA1750A31917DULL, 0xE0AD711D6FE6F757ULL, 0xE0444FCFBB36E72CULL, 0x1E0E2D649EAB9848ULL, 
            0x230DB0366C3F06B6ULL, 0x5EEEC2169C4F9A57ULL, 0x6E3A440115858790ULL, 0x8598FC74B8EB7C46ULL, 
            0x7A6951FDA9DEC266ULL, 0xA41C390E07E30966ULL, 0x296A88F2CE5D16E4ULL, 0x9EA2E7E33542C7ABULL, 
            0x205E8C6BDD916409ULL, 0x59115C1960565A65ULL, 0xD5C055FC5DE81AC6ULL, 0x25AFBDD46124CE40ULL, 
            0x49E259346DB47A7EULL, 0x4F54D0B64D5E90B8ULL, 0x61F1C58521BCFD8DULL, 0x7E3FA61E0992C28CULL, 
            0x7B1EE95D0BC65A8EULL, 0x7FB975D6E46027B2ULL, 0x43ED1D01DEBE70B1ULL, 0x9549A7B05284569BULL
        }
    },
    {
        {
            0x50FCC965332289DFULL, 0xC8ED785683521E80ULL, 0x6DC710929E34B8EDULL, 0xE399C488F3E298A1ULL, 
            0xBC1BAA0B6303F2E0ULL, 0xD77DA1DDC2CA8A41ULL, 0x499DF29315FE095DULL, 0x3CC8A5BE8339CF60ULL, 
            0x7EBAAE5FFBCEB555ULL, 0x34605ABFF80D73DBULL, 0x819D8D3E787F3BFAULL, 0x99C920A55A36DEB7ULL, 
            0x0C44EFD8B8719401ULL, 0x4228CFFE9727DE6EULL, 0x8B41932E5FA6759FULL, 0x0555E9DF026AEEF5ULL, 
            0x42064BD08D64FE33ULL, 0xBAB2505FDBF005C5ULL, 0xC86EA4CF357B1F9CULL, 0xF2D248E436E84F5BULL, 
            0xEF76D4ACEF47781CULL, 0xD86E6A508180975EULL, 0x1E53CB854108B126ULL, 0x8C38FF30B1706642ULL, 
            0xDF830115E11BA622ULL, 0x5D67CDBF86B81359ULL, 0x4DA438D45A0DA6FCULL, 0x8936FB4BC20762DAULL, 
            0x94CAADEFE350FD6AULL, 0x2D4D2AF81B36004BULL, 0x8FE542C3E9DA1BCDULL, 0xAA027160109F2D1FULL
        },
        {
            0xF31D58270963F426ULL, 0xECC0D86E1E43CA90ULL, 0x9462637ED08DA49AULL, 0xEBDDCABFBBBAFC09ULL, 
            0xEBA23AA8E446390AULL, 0xD896374C99FB1CCBULL, 0xF84D72A4EBE018D9ULL, 0x2F78C459BD0BFF17ULL, 
            0x48AFC2A43B5EF681ULL, 0x69B3044F8D50050BULL, 0xF6E3E5D83DED4EB9ULL, 0x849C5264D8A59138ULL, 
            0x8F13CB49038A030CULL, 0x89DA6E443A6F7C80ULL, 0x58526696F19C6968ULL, 0x56290F2DA85C98A5ULL, 
            0x0EE4AAE30CF03AA2ULL, 0x4A2719EDCE9A3831ULL, 0xDD88321BDE4F80A8ULL, 0xA0EA72B465A32C7CULL, 
            0x09AD069FEE1A3315ULL, 0xEE16871210733A07ULL, 0x70561FF9D85D2078ULL, 0x9A25120972811AD4ULL, 
            0x14EE37AA61A8FD2CULL, 0xA2B0BF50DE34782CULL, 0x519DC282F7A0CDE7ULL, 0x2B0227816D8EA5AEULL, 
            0x73D4941E1043F50CULL, 0xF49860BFB2A38D6EULL, 0x1DC766AD6FF0A68DULL, 0x9EB1076A01724B4AULL
        },
        {
            0x9FD4F442F645531AULL, 0x73EF858ADCA7083CULL, 0x8FFBF574ED94F43FULL, 0x1A48C69A8C4837E3ULL, 
            0x2ACC5D2198A8389CULL, 0x8F8E9A11276A82C0ULL, 0x08783E3CBBA21591ULL, 0x694D56F718F5D0E2ULL, 
            0x6496C5A25ADE7549ULL, 0xBB92402F7B5BB2EBULL, 0xAE7BD1D10A8725B6ULL, 0xF2E79A869E2F5E80ULL, 
            0x5687BED1D5C1162AULL, 0xD715353CF62D5781ULL, 0xB5C7FE884622770AULL, 0x19C98805425F1872ULL, 
            0xA395E5BB56E87A11ULL, 0xF303BD42ACC8EE4FULL, 0x39E202BBFB242BD1ULL, 0x4C56C5CDEA818563ULL, 
            0xA12826D02A5EB79BULL, 0xE7823E87CADE7F56ULL, 0x2DEE33874083EF2AULL, 0xDE7DAA074A47E654ULL, 
            0x5AEA8A8121E0A48DULL, 0x562D7CDEE390E107ULL, 0xFCB0FE618EC6CDD4ULL, 0x8CDA09D4946F4398ULL, 
            0x983752CC033E0C5BULL, 0x8C436D6AE3AF6182ULL, 0x02C885EBEA37105FULL, 0x58D7D5C437601497ULL
        },
        {
            0x1689111AEC14AD02ULL, 0x3DF8A0501F9ADBF8ULL, 0x0DFE2FE31ADCE126ULL, 0x17798FC1BF85D4A0ULL, 
            0xC18582C77DBB7B47ULL, 0x4B953B6410626B56ULL, 0x936C745C17E6495AULL, 0x70153959B0377166ULL, 
            0xF41E7C6E16E10404ULL, 0x7CC1F2ACB70E26E8ULL, 0xE896BBC8EC8AFF2BULL, 0x4C46569BC298D31CULL, 
            0x0EA3DB19F4CDA3A9ULL, 0xE62B3516F8A1E595ULL, 0x759FB03CB104CCD3ULL, 0xB61DFDC8197E0621ULL, 
            0xF065ACFC774E8A38ULL, 0x3010E311257F8F19ULL, 0xD86932A96F4A952AULL, 0x19EA5057EC7AD2A7ULL, 
            0x3F9FD1A14019CEF4ULL, 0xB0ADE2E842A50CDBULL, 0x22D3DFF38D99A6E4ULL, 0x5EA9846B56CFD7A8ULL, 
            0xD2074066C1C23D65ULL, 0xD8B7A57BFF278370ULL, 0x765855A1D61D1FFBULL, 0x3AD50A89A1C94D1CULL, 
            0x926137748CC69C2EULL, 0xB6841540EF5FF666ULL, 0xE9EAB179666F2740ULL, 0xC9780E1717FB719DULL
        },
        {
            0x26B40307499F0D0DULL, 0x99DEAB28FEFA7390ULL, 0x2E92E752D19670AFULL, 0xB2F9AF044EDBC0D9ULL, 
            0x1695F423C53431FDULL, 0x06549EA27A23E1DEULL, 0xC1F82D762A8465A7ULL, 0x2C360E203C60DBF4ULL, 
            0x7F4782362509A7B6ULL, 0xA8D4C68DA0DA2C31ULL, 0x1162E7CE9AD33571ULL, 0x4C19BF8AF26E7CDAULL, 
            0x4CFF195F94D6D8F7ULL, 0x95D2BD071A890848ULL, 0x90BC5CA727CCD82BULL, 0x07E20540A328F4CBULL, 
            0xC1A0DF862E768560ULL, 0x830777B5459530E7ULL, 0x3140924970092FBDULL, 0x4138185D2F12B7C4ULL, 
            0xC61FE3A237BC4A91ULL, 0xA49D54C8002D9663ULL, 0xE781C667429D08A5ULL, 0xEE5784BA977AE894ULL, 
            0x864E6CEABF36B990ULL, 0xE19398E22F130DCDULL, 0xBE11CBD2234F8BA1ULL, 0xADAE8A0B3C4A0C11ULL, 
            0x4F2896790723BA9CULL, 0xF5BEFCDF55749152ULL, 0x674C6CCC1109FC43ULL, 0xA1C813A4C5D4D3C1ULL
        },
        {
            0xF24549419E460728ULL, 0xB79A44920B1701F8ULL, 0xB7B5E28358CB007CULL, 0x0F4683AE29A299A8ULL, 
            0xE876BAFD2B6374DEULL, 0xB5C35323D0E33682ULL, 0x5A70FA8F31A053D2ULL, 0x08FF049F9E1E29F2ULL, 
            0x232A9B994546E8BCULL, 0x9299EA56AAC675CAULL, 0xD85D2F71927A1FA4ULL, 0x66CABF4334C2D2BCULL, 
            0xDD7C70C591763BECULL, 0xACF00B412B8C8C8FULL, 0x6B69A4B5AC676945ULL, 0xFB6A8C9BC31F534AULL, 
            0xA340A67CCFDA9FC6ULL, 0x225A754E93B13189ULL, 0x4D62E59FCCE6A74BULL, 0x6759BCF8C729F18AULL, 
            0x9DE030136D703ED5ULL, 0x9BD35FA131592E1EULL, 0x60D29460F6AD6520ULL, 0x2DC58F0CD55E3157ULL, 
            0xDD76840503B1E421ULL, 0xDEEBB319E21AADF3ULL, 0xAAAD02E0B34607EAULL, 0x87242E6DB5D28A0FULL, 
            0xEE2C965B0547E680ULL, 0xC4D65978219EED54ULL, 0x3B9C2679365CECEDULL, 0xBC9FF3FF54158943ULL
        }
    },
    {
        {
            0xC63005727FCECA3DULL, 0x9296BC346B33136CULL, 0x72D04F2D5D43D88AULL, 0x8E6152F4D1350EDBULL, 
            0x3C38385F7613AFBDULL, 0x9B0968356DF1DF2FULL, 0xEF5D8E3258507843ULL, 0xE770DCC40478ED10ULL, 
            0x98932A858F599B9CULL, 0xAD6DBDAECE7E0230ULL, 0x090C2C70EEA7F099ULL, 0x260A2F896748207FULL, 
            0x0B4297133EB2D917ULL, 0xFA109AF9D49C63EAULL, 0x1886CBC834D1E2D2ULL, 0x7F2255D79D1464FFULL, 
            0x6479E3C6F63388E3ULL, 0x8111ECF70EDE1B18ULL, 0x91F413363C949A44ULL, 0x1CEAC6C2BC1C48B6ULL, 
            0x706E088F25D16B60ULL, 0xFB68D9D45D1C58BFULL, 0x11EE205B10743C0BULL, 0xE8C5383A7A57C88DULL, 
            0x0BF6F44FB8FAF4A9ULL, 0x6C4F32BCCDC71598ULL, 0xA4A98FD5A6E9B4BAULL, 0x10BCD3D2EAF0041EULL, 
            0x8FCC6664EDFE100CULL, 0x42A80D9B1CBB704CULL, 0x69A8CCDBDD75043CULL, 0xEEA5FB7BCC358793ULL
        },
        {
            0x75E7D75D2054628AULL, 0x247F6C644FDB7A84ULL, 0x432E8DE21BAA08BEULL, 0x208A0ECDBF48B6BDULL, 
            0xFCE1E002FAE16AF7ULL, 0xCDD3BE1FEA588D25ULL, 0x794129C40DBAB4E5ULL, 0x11090947FD7E747DULL, 
            0xCEBDE3A5ADB6AD07ULL, 0x9AB742A833CEBF9CULL, 0x835B5AA090752DFAULL, 0xCD1CD944BC3E439CULL, 
            0xDDDB4608C47F2CDAULL, 0x87E4A7D7D0BA2003ULL, 0x3F500945D62AD305ULL, 0xE79C31A24B266840ULL, 
            0x97627453330DD63FULL, 0x2D937C4447800C16ULL, 0xEAC941B3E0535FF3ULL, 0x652206C675870132ULL, 
            0x3651FC39A0B63585ULL, 0x54E404EFED7D08E5ULL, 0xF4E0E4C262BCC7DEULL, 0xF45B8C0876E2F6D8ULL, 
            0x4271075DAC9240F4ULL, 0x6F95E24040AF5EB3ULL, 0x587456BFEB007800ULL, 0x3C062F9CF238ED87ULL, 
            0x4878A88F8173490FULL, 0x2AE71AA35A486CE2ULL, 0xC8D73B3C46591288ULL, 0x19CB787185802B3AULL
        },
        {
            0x4D004A370BE9F1C8ULL, 0x92387797BE9E5688ULL, 0xFC0B98F33BE9723CULL, 0x94958CE7563A4765ULL, 
            0x9D4D25917A282DF0ULL, 0x05E200B0D1564D8AULL, 0x8EC0AB590AD6857BULL, 0x3D82A46938B079D3ULL, 
            0xECA79A80873ABD40ULL, 0xFD71F25F052F532FULL, 0x3FD6B623C7664A08ULL, 0xEE67CB8385D9CDBFULL, 
            0x8127C6076DB4F942ULL, 0x6947F8F620CB36C9ULL, 0xE1C18765E53F045DULL, 0x9C75833CAA2A771DULL, 
            0xF4429D965BDC609BULL, 0x90BE7C3B8DC6D48CULL, 0xB435E97A7BBC91F2ULL, 0x1F41C8F6DD10B5BBULL, 
            0x2C61069BC5AA0526ULL, 0xCAF05FC14E74AA63ULL, 0x6CE56F0724700FDCULL, 0x12BA17D4D10CB06DULL, 
            0x0A28C0552902BA17ULL, 0xE4991C2EB15BA736ULL, 0x079C3FF096726C53ULL, 0xCE00D3FE9FDEC101ULL, 
            0x4CE2E13FA032047BULL, 0x3F40D15795A0B318ULL, 0x641FA05DCFC33B3AULL, 0x8157F45051061799ULL
        },
        {
            0x0CB71BF15ACD6A89ULL, 0x39AB22570525D69DULL, 0xA40D9F0859DF8478ULL, 0x9EA8F15FF8E4C820ULL, 
            0x1EA6066683A1E9BBULL, 0x64F4975FCAE23641ULL, 0x6D5D2CC82A2D3597ULL, 0x7178465855341B66ULL, 
            0x89D3324757DC403CULL, 0x0FACAF04DF52350FULL, 0x18A679D296B01B9FULL, 0x0F78EEB68891E420ULL, 
            0xAF84ACA7BED401A3ULL, 0x704B012A76545E5CULL, 0xFA6FC615FBFF2E51ULL, 0xA20DBE11421D1D28ULL, 
            0x1F55EA1550ACF0C0ULL, 0x25295C6040EEEE01ULL, 0x246897ADEB923EFAULL, 0x2266FDCB69D98236ULL, 
            0xC2075466B2AA702CULL, 0xFF04DE1A79BC0C63ULL, 0x62DFE20DC16990DCULL, 0x80346372409897F3ULL, 
            0xE5D44B27F2756839ULL, 0x60CC459518A41F8FULL, 0x7518B84AAA517665ULL, 0x1C620260198BE184ULL, 
            0xCC623B28900EB30CULL, 0xCDEC5C56D4566236ULL, 0x799B521768A1F9BBULL, 0xAC3C96825E2784CBULL
        },
        {
            0x913125C4D271B26AULL, 0x449F05BC0A798F57ULL, 0xA5EBEB74934F6ED4ULL, 0xD4A5C6DC2A309270ULL, 
            0xFDF8B3F41DAC94ADULL, 0x2277542A8375AFDEULL, 0x228575604A453E2AULL, 0x4B3AC3CA7B7A3683ULL, 
            0x0A5EC6EC0899E4B2ULL, 0xFFABDED07F51D101ULL, 0x1513D5EA55FADEA3ULL, 0xE8407112668208FFULL, 
            0x2D87E9156B9F4AB8ULL, 0xD65906FE672D6021ULL, 0x84271C592D37CAE8ULL, 0xCA44D2BBDEE5B1ADULL, 
            0x4DCC99BA4207DCA8ULL, 0x3C7026898F83CCB1ULL, 0x66D760A2AF1A83D3ULL, 0x85F77CBAA8558056ULL, 
            0x58F32D950500279DULL, 0xE716147441AB1C4FULL, 0x40E0B2EC75FC5858ULL, 0x00624FE8E9DC4E45ULL, 
            0x786146FDAD00BF9DULL, 0x8B267C9C4772C79DULL, 0x97C7D5CFCB6248C6ULL, 0x425EDEA20336A00CULL, 
            0xCE3215FA45FEF885ULL, 0x4D914AEE3E605E58ULL, 0xA63BEBE1CE08D3C5ULL, 0x7860CFC04219B060ULL
        },
        {
            0x061C0091FB96A1F4ULL, 0xB8B6D66EB3F093CFULL, 0x5709B95C494D9109ULL, 0x080B53518D09C903ULL, 
            0x6EE809FD841A9095ULL, 0x3B7B60D339E066ECULL, 0xDD917EAA39406372ULL, 0xD77F81A13A8012D2ULL, 
            0x63C31749FF65874EULL, 0xF030FA89C7C2E9D2ULL, 0x027B4B713CE66595ULL, 0x4FE39313CEAACE00ULL, 
            0xEC95D33CCA786E60ULL, 0x2CF122EB1125176FULL, 0x9B59CCF5E736229BULL, 0x3100DDB19BF77799ULL, 
            0x978E8B191BF66237ULL, 0x0C2CA559EB78C307ULL, 0x285DBA8E413EAA36ULL, 0x33BE6B59A93D33F7ULL, 
            0xC4900AA8861A397AULL, 0x04BAE57CA8DFB448ULL, 0x681202F013804EF5ULL, 0x0835A61D66386764ULL, 
            0x3907DCA46F8F08B3ULL, 0xD2540117BCF96BEBULL, 0xAEED0507E85375FFULL, 0x7B6EABA69B936814ULL, 
            0xDB8930C63F0FB2E4ULL, 0x62152F7BEA1EF477ULL, 0xACE27DF6E3CFFB01ULL, 0x67035E9247FCF058ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseGConstants = {
    0x2286A3CEADCED5ADULL,
    0x4DA708520885B488ULL,
    0x884AE86E9982BC03ULL,
    0x2286A3CEADCED5ADULL,
    0x4DA708520885B488ULL,
    0x884AE86E9982BC03ULL,
    0xD0AFA7549DC92540ULL,
    0x8B4B549B3F6CD980ULL,
    0x40,
    0xF7,
    0xF8,
    0xC1,
    0xAA,
    0xC5,
    0xB3,
    0x5C
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseHSalts = {
    {
        {
            0xE86CAF8958E6F607ULL, 0x251E9433D941787BULL, 0xC4905A87E8B1F0ABULL, 0x7AB3FFA970F60462ULL, 
            0xEB7011D758045086ULL, 0x3B85A55A300C9CDBULL, 0xBD127E91595F24D3ULL, 0xB59276470071D8EEULL, 
            0xE8795BB7A7F0F08DULL, 0x48B152AE9890460DULL, 0xB24EFC88E46CAE97ULL, 0x43B0335EB551C2C6ULL, 
            0xA2194B1850894399ULL, 0x1A30B7AAAF3DA8A9ULL, 0x164F662BAE90F4AEULL, 0xC41BAB997519327FULL, 
            0x73FAEBD23AA97952ULL, 0xFA95361927317F7CULL, 0x7CA1A25DA658AC62ULL, 0x67D4F9DBA5A202F3ULL, 
            0xC16D1758BF1259E5ULL, 0xAB8BEE6B4FEB7C9AULL, 0x2E82C44540B45F2EULL, 0x05322DD0AFE4617CULL, 
            0xAF38D184D722FED9ULL, 0x0D8B9CB3D3A52B03ULL, 0x35E25D57E4EA63B4ULL, 0x0CB2A1BE35F51AABULL, 
            0xD6F9B0F687600F26ULL, 0x92492E612DABD2B4ULL, 0xBF600FF311AC4768ULL, 0x168A8D978AB0B6C4ULL
        },
        {
            0x761B5134C732D8FFULL, 0xCE6114E62CDD2745ULL, 0x92271C977716E91FULL, 0xE8974F794FA8A603ULL, 
            0xBCFF4B10883C055AULL, 0xE3A3E0ED7453D0CAULL, 0x836754C6787E1748ULL, 0xC8AD37589D9A67A9ULL, 
            0x2D4F5631607E0C94ULL, 0x121E0161F3B0F714ULL, 0x3217EC1EC3A1F0A0ULL, 0x1733F96B449F52C0ULL, 
            0xAC573157CA330930ULL, 0x085B4C6E72E78245ULL, 0x1849AFFC6ED1BA2DULL, 0x5D5573A2A1EBDC17ULL, 
            0xE70F359A07615FB7ULL, 0x1933B4C0896098A9ULL, 0x2269866A1147A824ULL, 0xD3A41B750884014AULL, 
            0x67B04101CA1699ECULL, 0x75E02DF1F34F5562ULL, 0xB280FF3DB4BBA4F1ULL, 0x5DBBC2743AC289B4ULL, 
            0x928C663EB7F2A28BULL, 0x2EE84AABC1F43AA1ULL, 0xF1687BFF4D585B85ULL, 0x55BD42FFF871DF5BULL, 
            0x70E558F257929745ULL, 0xDCC9CCEBD523156AULL, 0x3396BF7C425B117BULL, 0x644674AC044A5E33ULL
        },
        {
            0xEDC5AD39F8607A2FULL, 0x80D34A23FFED9C8DULL, 0x1217B69B1078527BULL, 0x88547C51714BE855ULL, 
            0x6EA47B1796F796ADULL, 0x89EC8BCD678F9FC4ULL, 0x15FF2DFE09D74390ULL, 0xF59FC12166BD50B7ULL, 
            0xDA89FA1E0D2FE6CBULL, 0xA5A53CD65E327973ULL, 0x4EDA71134EA09C33ULL, 0x1FCD03176E182B5BULL, 
            0x06E9732A1227BB91ULL, 0x11553197D7971006ULL, 0x561958097C6106E5ULL, 0x2424EF8100B3294FULL, 
            0xC487056D6109A65FULL, 0xA2511715983E0B2AULL, 0x042ECEF190E0BA1EULL, 0x78C6869FAB3E548AULL, 
            0x4A1F906864CA8CB2ULL, 0x3E3AAD6575079279ULL, 0x6D3B14965460D8F8ULL, 0xAA15753CBF3D1F49ULL, 
            0x7839B19F6AE5611CULL, 0xDB4E6FC943245EC8ULL, 0x1B7395D526423A53ULL, 0xEEA8542F31891DD6ULL, 
            0x1CEA0FC53FA4422CULL, 0xCAA24A70F0FD0F95ULL, 0x5B765105BA5E0293ULL, 0x8DAD69F9D94D2136ULL
        },
        {
            0x0C24BD1C3E2A87DCULL, 0xE07EB56ECE9555C2ULL, 0x583B7FE20294C9E9ULL, 0x4CA4DB9D2AF049AEULL, 
            0xB56F74557A65FA22ULL, 0x04FECD9C67E5856DULL, 0x738B400E98AB35EDULL, 0x2935EE50838D8571ULL, 
            0x5ADBA3D7B5A497D2ULL, 0x117A9B8F89CBEB26ULL, 0x16401F58E533A686ULL, 0xD674A1C9329D44CDULL, 
            0xE356E02D3098623DULL, 0x227D4E543A370156ULL, 0x027E0EA35500D6C8ULL, 0x592722512AFA1A21ULL, 
            0xEF0A3195F03D8A94ULL, 0x6459D7C058B3937EULL, 0xEB196F7CE02A87B5ULL, 0x13D50CC577799092ULL, 
            0x7DFB1987C899F712ULL, 0x4EACAC525F347065ULL, 0x8D70DFBA0404CF41ULL, 0xE77889179BB55EDDULL, 
            0xEECFF7A8FC52DA69ULL, 0x54715620FFA81F66ULL, 0x801346EDCF5FF680ULL, 0xFEA3DEC7F9B8F0FBULL, 
            0x7EB9737A14D72631ULL, 0xEF044ABBDCDFD944ULL, 0x812987330D6E630AULL, 0x5B9AD70EC33B1276ULL
        },
        {
            0x06A1CC869A333567ULL, 0x224F339459469F6FULL, 0xB782422350978C22ULL, 0x21C4828A12EDAA7EULL, 
            0xB8A56C20A2545615ULL, 0x694E32E614D8EBC0ULL, 0x6BE48D2A0AA0A139ULL, 0x4E3096FFC183ED78ULL, 
            0xE0BC18EC6BB4EF95ULL, 0xF58D83469904834DULL, 0x5C7D6FC3F350A8AEULL, 0xF86408B95F04520DULL, 
            0x8F3B56107479F9E5ULL, 0xF00D44365012AB88ULL, 0x317C20608DA22F41ULL, 0x199A46C03D62FBDBULL, 
            0x928976B898157AAEULL, 0x10444019DB31C62AULL, 0xF7346A0810EA062FULL, 0x0956F53B34E13022ULL, 
            0xE4ECC064EF45CF87ULL, 0xDE824FA9B9EB0B80ULL, 0xC8EA837C60619455ULL, 0x1C2EE0F45DA4FCB2ULL, 
            0xE507BF63050EA7CAULL, 0x2FAA4AF0A399D366ULL, 0x763449F48CABBE27ULL, 0xB5825638BC6A2AC3ULL, 
            0x67518A9CF16D3242ULL, 0x4407716DC48F0A4DULL, 0x5A308D45D5352469ULL, 0xE75B198070AFC580ULL
        },
        {
            0x1B3A1FBB69718471ULL, 0x4442038142F2CB03ULL, 0x8FB62FDB65755A63ULL, 0xC246B7AF9D1CA5A7ULL, 
            0x12CDA3096735ED69ULL, 0xFD5FA09FB6AF3EBAULL, 0x237806687E542348ULL, 0x1CDF427A193072E3ULL, 
            0xE59BF9E3F3CEDA6CULL, 0xBEF6057D08634100ULL, 0x46B042143AE1718FULL, 0xCA8B8B0FB0B251E8ULL, 
            0xE161723DF101CED5ULL, 0xB1C41AD592A7C567ULL, 0x867FF15DD16FF760ULL, 0x1861AE1C51076898ULL, 
            0xFB7F0948F774C233ULL, 0x0D5C8B6E9C9B11F3ULL, 0xC104733B66E6F927ULL, 0x4641E3777C56D346ULL, 
            0x43C9E8F5D57DCA46ULL, 0xD28F569EF74BE7CDULL, 0xE1FC2208AEE11332ULL, 0x748BA7DFB360C0A2ULL, 
            0xC30FD6F42B9BEDD7ULL, 0xB1A9452C9954AA64ULL, 0x3181C76F9B700778ULL, 0xC73D39A7997BEFFEULL, 
            0x7E506D6E9CA10CFFULL, 0xB85519170EBC055FULL, 0x5077A3556742FC83ULL, 0x7CBC6538D0F0D109ULL
        }
    },
    {
        {
            0xC2EEBC73C9B850A1ULL, 0xA64F7070276F3EC8ULL, 0x6A618A2AB28CB76BULL, 0xD527CD40E93BB4C9ULL, 
            0xBCF0E2D5FDC78230ULL, 0x3B05B8B37B45498DULL, 0xF829F1BB79E15CE2ULL, 0x98A988A261583075ULL, 
            0x7E44CABBFEC398FCULL, 0x8D99FB4199CE80C9ULL, 0xE790975034393A7CULL, 0x4893AA8BCEC0E68AULL, 
            0xD40CF208E5F25E40ULL, 0x32C404FAA941F1CBULL, 0x5B9C573A69E48A3DULL, 0xE3DC671A2DBCEF71ULL, 
            0x3001272E4D85E9D3ULL, 0xED077DE097EC23A9ULL, 0x96C4B1B93D804CC6ULL, 0xC26A2F381384FE6EULL, 
            0xA5E4292C32780254ULL, 0x5A2895B07872A711ULL, 0x26DFF77AF3F2FCAAULL, 0xBE44D29896C56ED6ULL, 
            0x0E5E19C9DABF5DE9ULL, 0xDECC3BC7FB3D0DDAULL, 0x1C8B1DF805978B1AULL, 0xC7D4315C71D460CFULL, 
            0xA6CB5EC9B8D621D4ULL, 0x86393157C6CD77BDULL, 0xB705189797D1D42CULL, 0xDBF118BBA4A36942ULL
        },
        {
            0x3A452686BAF57F1EULL, 0x9FF14CE24EFFDDFFULL, 0x37132CC6B825B4AAULL, 0x74CA85B4AC12B0FAULL, 
            0xDE6C59F7D189981FULL, 0xF25F1CE0A7390745ULL, 0xECA633363D19D175ULL, 0x9A6AE2E839E98290ULL, 
            0xF0E3058B9083DA63ULL, 0x8E4AE9E75366FF42ULL, 0xCC6ED7764D59E37EULL, 0x1BB837933A5C9B44ULL, 
            0x105A1AAA909FA6C6ULL, 0xD9AB335FB0D25ADFULL, 0xEDDD247BD7CCA27AULL, 0x8E12B1456E8169A2ULL, 
            0xCE4D6F6BC444082FULL, 0x35088CB284D1E98DULL, 0xA5C17AFA15D733BFULL, 0xEAD4FAD2524B580DULL, 
            0xA5C882B1D3A3FAE1ULL, 0x8A6EDC2FEF7D0AE8ULL, 0x514FCB36C583F9D2ULL, 0x7CF2C9152B634F18ULL, 
            0xA6B2E3E7D2C36D44ULL, 0x660A1504A7057E0BULL, 0xF5780AAD214E519CULL, 0x24AD6565F005C8C6ULL, 
            0x7BEAD1922ABF871BULL, 0x8B136734434571F4ULL, 0xF92BDE286AB642FDULL, 0xF9BDEA546766CE39ULL
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
            0xB195F8BE88323BBBULL, 0x8F3F4378C7DAB318ULL, 0xA262426F94B63B17ULL, 0x27B3889A531A1F13ULL, 
            0x4E045AFCC88BECB1ULL, 0x11ED8B8EF1B79252ULL, 0x150F7506648EA1A3ULL, 0x4D7C37305E3C7BBEULL, 
            0x3FC8FA6FDBDCDD63ULL, 0x040C67C06770057FULL, 0x44A0086B4779912EULL, 0xFD57AA04D3D95610ULL, 
            0x405BD66506E5FA22ULL, 0x6B618CFB8BA80803ULL, 0xDF0406C060CA341BULL, 0x73B6F56AABB2C867ULL, 
            0x1A6FE8134C1BC417ULL, 0xFFE96F6CCEC60F18ULL, 0x445FDBD7692C8698ULL, 0xE2FEC9F5BC313561ULL, 
            0xE987B0508F8348D6ULL, 0x08CDF8B2664485E4ULL, 0x65DEAD3852DE0717ULL, 0xFBD3D13DE33101FBULL, 
            0x5A227B7E10560F97ULL, 0x9F316C41454EB572ULL, 0xBD10195C0129431AULL, 0xA0D65C5B5668755BULL, 
            0xD536B0BD13E2C8F5ULL, 0xEDF73DD97430E853ULL, 0xAE6244621D2089CBULL, 0x718CA5E56D6B1345ULL
        },
        {
            0xE5FEACF8FA5543ECULL, 0xEF1D29EA7CFE204BULL, 0x525A523895F08C39ULL, 0x934924ADC373BDC3ULL, 
            0x51D3ACE0CB345FE7ULL, 0xC9ED8DF62EBBE995ULL, 0x0759BB46532FDC82ULL, 0xBC86284EE8134E26ULL, 
            0xF8C59EBEC17889A0ULL, 0x66125A584F2DFCE5ULL, 0x0D794A702D06A177ULL, 0xC69AC55B41B34A11ULL, 
            0x2DD7DADE582B11A2ULL, 0xF7712FB9BB2170F6ULL, 0x8E726736C23137D2ULL, 0x689EB62904133BA7ULL, 
            0x5A97451E76B05AD2ULL, 0xB1E719F53A0D7E9CULL, 0x741BD0BC76294773ULL, 0xE418E782DEBF1276ULL, 
            0x5E9400BA21961123ULL, 0x06787B086FE6EE28ULL, 0x6B33B8BB176C221DULL, 0xF8D6AF9D6B5EB5C5ULL, 
            0x43FFD3C3AAF36852ULL, 0x5B574AD3CC6211FEULL, 0x0AEE10545FA11F3AULL, 0x5FBEA411E023F1AEULL, 
            0x945F354B89912AC6ULL, 0x3BE77C4279E18DB8ULL, 0x86C46CFF8C96C67EULL, 0xBBB3E070092BD0B8ULL
        },
        {
            0x287FF460FE68783CULL, 0x2C61E27BBF759D08ULL, 0xBB2335EB57C8BF88ULL, 0x86A9CE85D7A26AEEULL, 
            0x0D506EFC548FBFDDULL, 0xC8AC7830E4CD039FULL, 0x3AE94225D344CA9DULL, 0x4646B340BD2F4829ULL, 
            0x55A763874BDC52F0ULL, 0x8BD18B0942CC54D4ULL, 0xFB3B9F094FA6C1BAULL, 0x97EFC30D78E91B6AULL, 
            0xA0588F063E10CDB7ULL, 0x3CF1B38ED250DE66ULL, 0x0B74914433FAEF21ULL, 0x3632E99FFF233EEAULL, 
            0xC6AEA7A84D1C8F0FULL, 0x216E239CCC88F13FULL, 0x643A2CC5885CBC9FULL, 0xAACBBC78509EBA88ULL, 
            0x2F6D9E4F54A88AD3ULL, 0x25730F7A120048C2ULL, 0xC3A404677797BFA2ULL, 0x2B27E3D45D78B569ULL, 
            0x845E3F6948FE1BEBULL, 0xB76FE09918F62B60ULL, 0x22378919B41ACF96ULL, 0x60A9DB1946F93661ULL, 
            0xCF63AB21B50DE857ULL, 0x4E22037AFDFE221CULL, 0x1F264E176CE6EBF7ULL, 0x6F5A6EC86E88261AULL
        }
    },
    {
        {
            0xAE3884F2A4E6835DULL, 0x6A65E61236DADDA2ULL, 0x9FEA1ED8E83FD4FFULL, 0xF0FBEF50894C783BULL, 
            0x99C712FDB3CEF031ULL, 0x0B97DBCDCB06212AULL, 0xAE59303E7EB1E039ULL, 0x1B092991C76BEAD7ULL, 
            0x196F84CE384EC83BULL, 0x62F2CD8580F7D7B0ULL, 0x545B8BC698396D7CULL, 0xF9A4141850D134C9ULL, 
            0xBFF1E8CD819E24DDULL, 0x1D46A4C94C7D3AA8ULL, 0x3861366D1BB0897AULL, 0x3CA5E42793E01FBFULL, 
            0x6C4622B2E83E997DULL, 0x9EA9F20D91762FF8ULL, 0xCBB9A420208690F0ULL, 0x2D476FD5114EAA1DULL, 
            0x84B159AF2EC52852ULL, 0x3607FA10F2CD77A7ULL, 0x28737BF69F4B3121ULL, 0xB4841B187E9505FBULL, 
            0x50513121CB0862AAULL, 0x5EEC1467A99B7351ULL, 0x6C5545597E9779AAULL, 0x0677930F15BC8CD1ULL, 
            0xF48B8A52BEC06DAFULL, 0xFA291FFC1F3B99D2ULL, 0x4DA6AE8142542D8CULL, 0xD7CBAEEE45268823ULL
        },
        {
            0x2EA46688A12D5827ULL, 0x12A47E0A31BB93C7ULL, 0x32746EB220EE45B6ULL, 0xAD25FEFD1BF6589FULL, 
            0x4F0551488AD5EC23ULL, 0x2FC1EFDE439C2678ULL, 0x68715BA151361D6AULL, 0x77750C54829AD81FULL, 
            0xBE29DC60569ABEB1ULL, 0xE37D48C34FF23AE0ULL, 0x59A36FDD94CE73E1ULL, 0x23907094B3205EB0ULL, 
            0x349427F4317B5803ULL, 0x6A793F16527E129BULL, 0x07261009B93BB88BULL, 0x7181EE02A30A34B8ULL, 
            0x085ED547F8555C53ULL, 0xE8D9923DA56C80B4ULL, 0xA6C6902BFBD43601ULL, 0xCEA287BA61D59F4BULL, 
            0xFA499EDA7575E16BULL, 0x319C1BF0A689BCB9ULL, 0xE70BBE88B598389AULL, 0x8640CBDEC26E498EULL, 
            0xA4DC84368CB49208ULL, 0xB478C8943AD1BF4EULL, 0x1B681BC6D30D4002ULL, 0x51239799AE225E2BULL, 
            0x84C3633D5BF8315FULL, 0xD154646CD14888F8ULL, 0xECE64F684D1A180FULL, 0x6FFFA1C50467E332ULL
        },
        {
            0x78D07165EBD0A0D9ULL, 0x7CE9FAF4643CF77DULL, 0xC2CF92D306A2995AULL, 0x45E610EE5E16CAF1ULL, 
            0x3EC245C015C11FC9ULL, 0x61515009532E92E5ULL, 0x1F2CD7573C34F610ULL, 0x7208E0C1DF3B121BULL, 
            0xC60FE09D6EBEE0F1ULL, 0x8435C959CD05763EULL, 0x6A63BD0E895CD5F4ULL, 0x929AB51A1A052AC4ULL, 
            0xE9C5CEA00081EA52ULL, 0xAC3BC39A5056984AULL, 0x016AC697969DB32BULL, 0x1D741C48F0532D6BULL, 
            0x04CB7DCC5721A41AULL, 0x8D1D242219D3DF47ULL, 0x4830C65C19B554D4ULL, 0x40332C18466B86DBULL, 
            0x9CCDBA320F896EFBULL, 0x3BAD7AFFC90DB15FULL, 0xE640D5CE9BEF47ABULL, 0x9BFA4D71194628FAULL, 
            0xC4613A351955A1EFULL, 0xDBCE872116467505ULL, 0xE0FF39F1EEC6D03DULL, 0x9A4D991CBDA5B4BBULL, 
            0x26EDE0B6E2936C19ULL, 0xAC8E2D3CA0BBE396ULL, 0x256B0600B0B62C5CULL, 0x2783346362A72ADDULL
        },
        {
            0x2BC1E164A7E3565CULL, 0x34E63F344856CB10ULL, 0xA1498E74D99309D9ULL, 0x11FF1C28BD2EDA46ULL, 
            0x869E8F908618A6D1ULL, 0x0AC713592DBBAF44ULL, 0x46301EB61118AF81ULL, 0x4BEFDAE7E909B1E5ULL, 
            0x16AF651EF0AF705FULL, 0xC3794BDBC1042A93ULL, 0x42632EAAB956EF49ULL, 0xD5B212D2C78ECBB0ULL, 
            0x22F03711792D284EULL, 0xC3B1EC3270C60238ULL, 0x682E98D788FBB466ULL, 0x766E024BC13EFBB0ULL, 
            0x593A8F8DB3703C80ULL, 0xF60A70B6DE9C2DFEULL, 0x05E2C57FB6A51DD9ULL, 0xCC924043A6C5D248ULL, 
            0xFCDBFE1DA57929EBULL, 0x26BAB5C080BC30CCULL, 0x48F270FA27AEF914ULL, 0x61F1036144380300ULL, 
            0xADB287B0FB165941ULL, 0x1304C8A5093BBCB0ULL, 0x864875743E5951E9ULL, 0xBBE7D0FB40B75D39ULL, 
            0x0657723C3B444838ULL, 0xA69677E656B6AAE6ULL, 0x6F67CA8EBFE75652ULL, 0x12721FD5D54C86C7ULL
        },
        {
            0x33A08D1F38F1425CULL, 0x974151510DF53BB5ULL, 0x28F45A1695CD4AE4ULL, 0x8F15C01F0595CBFDULL, 
            0xED6601CCC594153EULL, 0x04407C14D1CFF57DULL, 0x8AB83AEE722CC543ULL, 0x5E8F708D424E122BULL, 
            0xAA018B50E4E6A449ULL, 0x805A1AAEC4B79BA0ULL, 0x3088236FA52E2752ULL, 0x231C40160CD13A07ULL, 
            0xDC9467CE3B3893C0ULL, 0xA4645AD135C877DAULL, 0x9B97234B86563C2CULL, 0xA31BB4359094A64FULL, 
            0xAF2163358C9700C4ULL, 0xDD3F2FD0885DA639ULL, 0x89CEEBA1714331B4ULL, 0xE63BA7D398C40C90ULL, 
            0x2B55384C4019DBC5ULL, 0xFFB1A209AC618671ULL, 0xD5611AACAD71A595ULL, 0x029E4DDBA39AB8E2ULL, 
            0x584708DF9F727C4AULL, 0x5063A05D05A86BE7ULL, 0x53AB53EE59643A07ULL, 0x6727E1F001C31B9FULL, 
            0x963FBFA48BEF9078ULL, 0xC7576A8DBCAD6C17ULL, 0x2D8FBDA044324790ULL, 0x457DAD8804EE0E7BULL
        },
        {
            0x0E46E4A7BFBCA6A4ULL, 0x34056A371494A007ULL, 0x860084E724EC829BULL, 0x97AEAD489DC91DE2ULL, 
            0x0C172402CABA96FAULL, 0x079F7624D0B10036ULL, 0x5EE0DB550AADA1D5ULL, 0xDD53D4A212F410DEULL, 
            0x5C439AB8C5089AF4ULL, 0x701783E1E4B14E78ULL, 0x26DB3C98336F9E32ULL, 0xB35E03DA45A3CA57ULL, 
            0x0E2D8E8A4CF679EBULL, 0x64FB95AFB01CDF27ULL, 0x4128324862E086BDULL, 0x04AB62339D764F44ULL, 
            0xF614C15542A279CBULL, 0xFB08A7CFB6A13E9AULL, 0x88F4AC3324677A01ULL, 0xD8FCFE7DBE08FE7AULL, 
            0xB53EA1F88DE0CCA9ULL, 0x697260CDF9A6D62CULL, 0xE02AA10F39798838ULL, 0x205E6CF43C96513AULL, 
            0xA090240E3C945C38ULL, 0x47C1334673ACFC14ULL, 0xDE6B5E4476AAA0CBULL, 0x4F8FAABCB47EE9B0ULL, 
            0x68CDC4868DF212FFULL, 0x6453DB508868879CULL, 0x2E7854CE9DA56C99ULL, 0x9EB85A21B7D803A3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseHConstants = {
    0x5BD951823813A11EULL,
    0xB9AB092DAD57DDACULL,
    0x311898ABA329142DULL,
    0x5BD951823813A11EULL,
    0xB9AB092DAD57DDACULL,
    0x311898ABA329142DULL,
    0xF195AE50054C3585ULL,
    0xADFEA496A857F828ULL,
    0xAF,
    0x23,
    0xBE,
    0x01,
    0x0C,
    0x38,
    0xB8,
    0x7F
};

