#include "TwistExpander_Mirfak.hpp"
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

TwistExpander_Mirfak::TwistExpander_Mirfak()
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

void TwistExpander_Mirfak::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x83D527917AEC7239ULL; std::uint64_t aIngress = 0xD0607C2E7D647561ULL; std::uint64_t aCarry = 0x8ADB2E85F102BE42ULL;

    std::uint64_t aWandererA = 0xA3F0802028081CE2ULL; std::uint64_t aWandererB = 0xF751610FC83036CDULL; std::uint64_t aWandererC = 0xEE48B9C3F1768307ULL; std::uint64_t aWandererD = 0xBF547EC02D2ADF8FULL;
    std::uint64_t aWandererE = 0xC9E4BC41756E9E21ULL; std::uint64_t aWandererF = 0x9D7CBEDDBB221EDDULL; std::uint64_t aWandererG = 0xC1A6C5DAE0AAFCD4ULL; std::uint64_t aWandererH = 0x8CAED861FF52FF97ULL;
    std::uint64_t aWandererI = 0xC1F55B711A87BD08ULL; std::uint64_t aWandererJ = 0xA8148CCCA56B4133ULL; std::uint64_t aWandererK = 0xAADBC7F4C3E21CA5ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11764787422484594991U;
        aCarry = 15464111021510223537U;
        aWandererA = 15721043354303548345U;
        aWandererB = 16973400645609525881U;
        aWandererC = 11678590331680517224U;
        aWandererD = 13350583461571352963U;
        aWandererE = 14424157591564716258U;
        aWandererF = 14405537213630921679U;
        aWandererG = 10766087756320037330U;
        aWandererH = 16254640072625806141U;
        aWandererI = 17920664026362269937U;
        aWandererJ = 15923743484957444896U;
        aWandererK = 12091966609764173930U;
    TwistExpander_Mirfak_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mirfak::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA0393191375F467AULL; std::uint64_t aIngress = 0x8DF434A143FB0E41ULL; std::uint64_t aCarry = 0xC85DAB85C2671269ULL;

    std::uint64_t aWandererA = 0x900615642644A635ULL; std::uint64_t aWandererB = 0xE31EBBC70A81376EULL; std::uint64_t aWandererC = 0xCE57C8F4204BAF8AULL; std::uint64_t aWandererD = 0xFB79A381F725CEEEULL;
    std::uint64_t aWandererE = 0x8DB76FB17ED89847ULL; std::uint64_t aWandererF = 0xA9F2CE712F2B7D40ULL; std::uint64_t aWandererG = 0xE102464CBE9E2CDAULL; std::uint64_t aWandererH = 0xC6D9BA5B65F61C91ULL;
    std::uint64_t aWandererI = 0xBB0E986E7C693963ULL; std::uint64_t aWandererJ = 0x8D55F1799703146DULL; std::uint64_t aWandererK = 0xE035F8D74DE4C479ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17193358889207505528U;
        aCarry = 15957333467865642106U;
        aWandererA = 15346087363279602451U;
        aWandererB = 13944582924577113283U;
        aWandererC = 10634256126920182225U;
        aWandererD = 10974579456373885223U;
        aWandererE = 10236976767146568099U;
        aWandererF = 15331903265665245117U;
        aWandererG = 15064805383122822541U;
        aWandererH = 13089857252373863511U;
        aWandererI = 14337310405706194523U;
        aWandererJ = 13975232228233691155U;
        aWandererK = 16593343199483436102U;
    TwistExpander_Mirfak_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mirfak::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xEE73A881A9F2A27AULL;
    std::uint64_t aIngress = 0xFCD5C978B0A43697ULL;
    std::uint64_t aCarry = 0xA137EE74E08CC407ULL;

    std::uint64_t aWandererA = 0x8F9956F231857E28ULL;
    std::uint64_t aWandererB = 0xA23AADE15D41A0A5ULL;
    std::uint64_t aWandererC = 0xE9D6A5FBA48C257FULL;
    std::uint64_t aWandererD = 0xD8BD43DAE24FE84AULL;
    std::uint64_t aWandererE = 0xD5D701331BD0274EULL;
    std::uint64_t aWandererF = 0xFF3ECF9629E465C1ULL;
    std::uint64_t aWandererG = 0xC5ACF2E02626800DULL;
    std::uint64_t aWandererH = 0xFFFDDF1222C2499DULL;
    std::uint64_t aWandererI = 0xC7A7564EAB61E38FULL;
    std::uint64_t aWandererJ = 0x955BF285DD54732EULL;
    std::uint64_t aWandererK = 0xBCB3E4EEFC2D16D5ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
    TwistExpander_Mirfak_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mirfak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 21 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1798 / 1984 (90.62%)
// Total distance from earlier candidates: 36343
void TwistExpander_Mirfak::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 944U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1911U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1515U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1836U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1223U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1426U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1037U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1888U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 221U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1395U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 467U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 310U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 619U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 97U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1745U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1076U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 865U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 202U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 572U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 873U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1581U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 481U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1473U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1207U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1128U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1176U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 997U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 294U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 428U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 36U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1633U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 427U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 260U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1520U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1992U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1238U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 413U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 995U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 914U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1375U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1743U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1151U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 899U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1208U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1610U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 402U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 492U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1511U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 455U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1756U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1362U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 626U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 457U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 681U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 262U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1152U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1704U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1272U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1053U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 87U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1889U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 269U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1539U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1498U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1587U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 192U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1179U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 911U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1999U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1019U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 963U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 458U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 94U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1247U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1826U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1482U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1726U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1624U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1732U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 883U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1246U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 996U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1317U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1590U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1927U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1599U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 781U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 225U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1941U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1026U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1399U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 633U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1486U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 757U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1064U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1640U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 15U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Mirfak::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDB7FC13DD3E8864CULL; std::uint64_t aIngress = 0xCBE6244FD239E313ULL; std::uint64_t aCarry = 0xE6CF9F3FE71DBC06ULL;

    std::uint64_t aWandererA = 0xC33624421FD879E7ULL; std::uint64_t aWandererB = 0xAE7DC0AB865F2904ULL; std::uint64_t aWandererC = 0x872B82E6E566F964ULL; std::uint64_t aWandererD = 0xA50FFE23EE96D263ULL;
    std::uint64_t aWandererE = 0xFB8DEAC7814DF218ULL; std::uint64_t aWandererF = 0xE6D49F64D58B0E54ULL; std::uint64_t aWandererG = 0xBBA6CA2BB543F712ULL; std::uint64_t aWandererH = 0xEE1ED87666F2ED67ULL;
    std::uint64_t aWandererI = 0x9FC55B401B7DBD3AULL; std::uint64_t aWandererJ = 0xE670AC9C30F48426ULL; std::uint64_t aWandererK = 0xDEE9A84622D3B235ULL;

    // [seed]
        aPrevious = 17684467540998515683U;
        aCarry = 18238660957172389738U;
        aWandererA = 12915603328150498470U;
        aWandererB = 10816677469044374421U;
        aWandererC = 10096243912782620899U;
        aWandererD = 15234376895357239071U;
        aWandererE = 9922552026638600813U;
        aWandererF = 17304832768146449728U;
        aWandererG = 17565842321896899295U;
        aWandererH = 18234920430575399237U;
        aWandererI = 14401424787282918720U;
        aWandererJ = 13408394885767927798U;
        aWandererK = 11317626371368490330U;
    TwistExpander_Mirfak_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mirfak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 21 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10868; nearest pair: 482 / 674
void TwistExpander_Mirfak::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2553U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1836U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4145U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4513U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7248U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5185U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 819U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2799U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3860U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1280U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7836U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5141U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4808U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1462U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2625U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5887U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 719U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 476U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1509U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1590U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1561U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 529U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1029U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 464U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1997U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 926U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2022U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1352U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1437U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1006U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 671U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1926U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1933U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 21 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10863; nearest pair: 495 / 674
void TwistExpander_Mirfak::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4511U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 126U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8102U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4504U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2569U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 687U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 535U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3238U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2515U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 801U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 821U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3585U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3004U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4255U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 64U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7069U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2011U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1840U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1298U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1810U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 174U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 766U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 845U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2028U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 650U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1336U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 872U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 553U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1787U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2004U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1204U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 501U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1909U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 537U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseASalts = {
    {
        {
            0x2DBEA8D1DAE905D3ULL, 0x6A0DF11332A1E7C9ULL, 0x8675EAAE19FC22ABULL, 0x408213BB77403985ULL, 
            0xE211711902312184ULL, 0x40115111F4A836E8ULL, 0x65A95AAADD2511BCULL, 0x4C77E5BD873866C6ULL, 
            0x6674E0241A9F9A1FULL, 0x8C8D8674E990D0EFULL, 0x5DFC7570A4BBDCC2ULL, 0x0493583C00F6E666ULL, 
            0x23F2A4359F45BFE3ULL, 0x56F20ECBB6A97AECULL, 0x1322B86DAD140950ULL, 0xA29FCA185D29B6C4ULL, 
            0xCA17D002A26B06F9ULL, 0xE7605433951C9E86ULL, 0x0878DC05022C6C8DULL, 0xB725697BAA91A63EULL, 
            0xFD8D1D18565EC5F0ULL, 0x35A6CA101BF28E14ULL, 0x5D33D0BB127FEEA1ULL, 0x2211996F16CD87A4ULL, 
            0x39A35024B5FD71B7ULL, 0xE0682B0EBA0052E9ULL, 0x1D622A29EF147C70ULL, 0x21A717EFC9DD9E39ULL, 
            0x3721E0EF467FCDC6ULL, 0x62D5B08593C794F2ULL, 0x4DC4F64625A5383CULL, 0x8A59FAE582699F56ULL
        },
        {
            0x35D4B9A6D7E6D4B5ULL, 0x20D56C8D4538F593ULL, 0x9FAF9C66EA6A203AULL, 0xA60CAF75A089202CULL, 
            0x6D862443ED1327D5ULL, 0x67016B0E84AC0309ULL, 0xDC71832D8488903CULL, 0x8F95FD6CF3B798DAULL, 
            0xCE249758BBCA19E8ULL, 0xB7B29A618F20DE4BULL, 0x5B9E9ED7EABECF6EULL, 0xF1C244F69D05B533ULL, 
            0xBCB5BD4F2DD541D2ULL, 0x466B24C0858D541DULL, 0xCAF4DC6BEBF16CFBULL, 0xDDFA3B6C2C581A6BULL, 
            0x6F544B3620D702F3ULL, 0x5A615369DA50A8A9ULL, 0xA81E76DDEAE6F0FAULL, 0x9A068D7AFB667E02ULL, 
            0x124F68031A1D76A1ULL, 0xAAE81E95F8385B2CULL, 0xDBECD4F01D5B04CBULL, 0x44D040B34D28779BULL, 
            0x755E6D36B2F9970FULL, 0x1E6A2E2D5BE66A3DULL, 0x45848A10B8AECDBEULL, 0xE518B45262C1F8AEULL, 
            0x0030C916A8217AC4ULL, 0x2ECCB7AC50DA1A98ULL, 0x3D745393B3E3FB77ULL, 0x6B38F7123C8376B2ULL
        },
        {
            0x8AB3B9B423EC37F3ULL, 0xCF9784A0E9804FDCULL, 0x8CF7975D1EA62B11ULL, 0x8698E9F3CB86E429ULL, 
            0xD9CE08C4F8BD3645ULL, 0x55020463CB4597E1ULL, 0x37BC8D561F5DF9B4ULL, 0xA84C119A4512BE88ULL, 
            0x2DB75E20095834B0ULL, 0x7554AE66F72A79CFULL, 0xEBF4FCDBB1B33537ULL, 0xBD2AA46089A69D29ULL, 
            0x642BC9E279A350BBULL, 0xF7646B552E0CE4FAULL, 0x3FD09AB0376A7DECULL, 0xD0C7175BB6A3994EULL, 
            0x561789DB2D475323ULL, 0x8EF4383A95EDEBF6ULL, 0x578FB0B2BA5C7AABULL, 0xCA84DC9B5893E9E4ULL, 
            0xC4932FB18F1E4961ULL, 0x64F24C2A9147CB85ULL, 0x384B637E279FDA25ULL, 0xFB7B817A05A18E92ULL, 
            0x3572A18DACE57310ULL, 0x0740BB335A26831FULL, 0x58484A7CC3B38BC2ULL, 0x070EA8C6FB95ABEBULL, 
            0x0C3F8D24A4FAB295ULL, 0x206CCF1D9A3C9D15ULL, 0x46B601E21362EE0AULL, 0xA30DDCD4E0FE4534ULL
        },
        {
            0x027A62F42C19319CULL, 0x9D3E61BA76B14FD3ULL, 0x5319A79F6AC6DC1BULL, 0xE8F448CC6AD66142ULL, 
            0x1A9D0D96C91A86B9ULL, 0x541986555381B779ULL, 0x125AA31F75D53F3CULL, 0x97F641D6082B7CE3ULL, 
            0x4A6A61FD87E1BD8FULL, 0x8B4FB90B092DEC8DULL, 0x9208621EF8AB0631ULL, 0x940C22D908D8ABACULL, 
            0x205D71475536C504ULL, 0x3C027028272B1FC0ULL, 0x8C2E03A156A35C28ULL, 0xF9F4D02E51E24363ULL, 
            0x3A14B5675AE94DC8ULL, 0xB1A565C78221D792ULL, 0xEB0E789BBBE1D707ULL, 0x933857885481AC0DULL, 
            0x2402D9BAECF6B349ULL, 0x2D863E8C07405D18ULL, 0xE4918F71CEB51545ULL, 0x5D48E3F81E819272ULL, 
            0x63A7E7ADBB5BAAF1ULL, 0x6D700202CC0E22E1ULL, 0x4C8C9B11E413D25AULL, 0x69D8985733886D49ULL, 
            0xA2A1C6FF430B42B8ULL, 0xBCBB452191AD6BC9ULL, 0xE597BEB66B9ADBD0ULL, 0xFF42489002498E27ULL
        },
        {
            0x7351A4B3A9375DEBULL, 0xC88816F52AB96DE0ULL, 0xA5837AADB63BE954ULL, 0x18575EA7E17E21FAULL, 
            0x7E1DEAFF99170BD9ULL, 0x06BD1DBE4ADEB7A0ULL, 0x267B1809FB4850B8ULL, 0xD2FD9BF1EE98E156ULL, 
            0xC464D7D88AF88754ULL, 0x090A3DFCB6323367ULL, 0x6A0A25AED43C593AULL, 0x9E3DF46BAE78F04BULL, 
            0x3CF686AD94E470EEULL, 0x688D9AA3678B6DA3ULL, 0x6829D3D5D7E1FC57ULL, 0x06A77BA90F4F376AULL, 
            0xE5305B373CA31581ULL, 0x38AF5BA607E1279DULL, 0x1663BA1BA0F3C334ULL, 0xE7B1EF4242DC432BULL, 
            0xE6F8F1A29F18EA44ULL, 0x574CB31869FF290AULL, 0xF8BFFA76665C01E2ULL, 0xC4A08E1CF2E4215FULL, 
            0x6A0196D3EBA327B8ULL, 0x79872CD40B953378ULL, 0xA2D06B1CAEE079FDULL, 0x358A738D80C338ACULL, 
            0x37778CEF20742A0AULL, 0x4F19A7B6EFF14906ULL, 0x108A320079B2C2F4ULL, 0x60768E60F79EAF21ULL
        },
        {
            0xC5BA9B2335A9A5EAULL, 0xDD1469AC31DC5222ULL, 0xC67CD94FBEFEF33CULL, 0xF32A81BF03567032ULL, 
            0x611D3101147053E6ULL, 0x008761C338B75138ULL, 0xE38AFAFA6CDCABF3ULL, 0xE84EAC11870E3A1FULL, 
            0xBD974B26958A1DF8ULL, 0x08579F5BCBD78502ULL, 0x935386AF7DDE7DE2ULL, 0x0F3292EC03C6418EULL, 
            0x1F78C2935EE837E8ULL, 0x90C152085F63AC48ULL, 0x083514966EE0D779ULL, 0x7ABA4E8087978DAFULL, 
            0x003E08BBF01A6B3DULL, 0xF487B8330B686FA2ULL, 0xE46DEFEB3E211E56ULL, 0xC1B56A1639A1AB73ULL, 
            0xBF73DBBFD58A1567ULL, 0x3B4DC4B2A6BA6F53ULL, 0x4E010E10699313E1ULL, 0x2CC9938865FC0172ULL, 
            0xFE5932653E1F0217ULL, 0xFD90FE57AA8C0C2CULL, 0x7E98345C97C0AAAEULL, 0x3382620EF24D733BULL, 
            0x3CEF0422FAD3108AULL, 0x71241C80180ADA62ULL, 0xED823DFADD455CFAULL, 0x12E37F669C96EB1EULL
        }
    },
    {
        {
            0x3E1B85DDFF135CD0ULL, 0x30705DF64A6D6FBAULL, 0xC54E0E81ADF11C06ULL, 0x70F06465FAD468D8ULL, 
            0x6131090B43EDD4EBULL, 0x24875429AC71ECD8ULL, 0x46CACCD14AE46CCCULL, 0xAD6A3ED6EDBCCB37ULL, 
            0x39BC8F8842549753ULL, 0xBEC5AC06B9DB997EULL, 0xC2D64297F6604840ULL, 0x6668CEF148FC0984ULL, 
            0x2CF660DD62AD9C33ULL, 0x98356B1F869AAC21ULL, 0x726D332F7CACAE20ULL, 0x463D470EEE9603DCULL, 
            0x8326BCEA0F1D175BULL, 0xD06110D21D4ED969ULL, 0x07A3111BA1175FA3ULL, 0x73049256A3A3F025ULL, 
            0x345EB63AF5396EAFULL, 0x13763C621C60B0B8ULL, 0x7095E9007DA56B68ULL, 0x3D2ADCC58BA8AA72ULL, 
            0x81C257B49CF315F3ULL, 0x677B22DF608469EEULL, 0xE486D80EA3315F36ULL, 0xA1972DF421438863ULL, 
            0xE8CFB2184F889596ULL, 0xEEDECFE339C77013ULL, 0xBBC8DC70D6A89B7AULL, 0x73E72E98B97F26A8ULL
        },
        {
            0x22C2534E2005D257ULL, 0xAD2EB18B977B5F02ULL, 0xAE2A00E8F74BF24EULL, 0x27A2B196B34DA471ULL, 
            0x0997381C6BFD3A39ULL, 0xA53BFCCDBE5A0FFBULL, 0x724BD983BDCE3CE9ULL, 0x84E7F3284DDA7E1FULL, 
            0x71D07C2ED12D3B83ULL, 0xB5FFE45C19023816ULL, 0x324BA4B700F68A60ULL, 0x633A43B69158F733ULL, 
            0x93658C6216B5DEEDULL, 0x214CB3A16497576FULL, 0x277FD4E34F28D880ULL, 0x0EAA187BB60A22F1ULL, 
            0xEB9C1A6D8986F3F9ULL, 0xDF12AD26A4443696ULL, 0x21EABDCC71159141ULL, 0x96A7B8D64A95A8B1ULL, 
            0xA1D25EC9FA6E55D1ULL, 0x509ACDB7ED0254C7ULL, 0x86C998C3398DF771ULL, 0xF5D99CF248A9AC6BULL, 
            0x4881D9AFE8278164ULL, 0xCFB240F32309C11CULL, 0x68EE32ACB58171EDULL, 0xD6ECBA834E355726ULL, 
            0x93F754B8EF340BFEULL, 0x26CDD3EB08F78895ULL, 0x0E0FEF01DCAB68C3ULL, 0x96F4F06059C8EDCAULL
        },
        {
            0x32964C7B15993320ULL, 0x8FAAE5AC94243B6BULL, 0xBA3FA1F7D1CB4F63ULL, 0x5883C37DDFC93D89ULL, 
            0xA0246547531E6DEAULL, 0xDF3CB8C54082511AULL, 0x5BA7A181F6CB98BBULL, 0x7BC00493480F344FULL, 
            0xE58FDF6632BBD36AULL, 0x90F81215C2B4A19CULL, 0xFF0A99B0FA3D998CULL, 0x6547117D92DAF93EULL, 
            0x0573DEAEC21AE0B2ULL, 0xDE652EF2754DDBB5ULL, 0x92278890C9CA0B81ULL, 0xAF58D3423F3DE84EULL, 
            0x86EB5890DEED7F7BULL, 0x17CC7DCF20218EA9ULL, 0x2D8944DDD398CD63ULL, 0x1F9A8A9F18B3672AULL, 
            0x0E3D3B64AE7EF54CULL, 0xA81C718C43A2C0E4ULL, 0x0C933550691B8722ULL, 0xE2E7B05A5240B707ULL, 
            0xA18CABB57CCBE479ULL, 0x127653EDFA632BA8ULL, 0x6399A9A9E52D69F3ULL, 0xBC92ED07A380E0AFULL, 
            0x34D9F211AFEB8603ULL, 0x940CD7DC235F7486ULL, 0x4052F2B685280D92ULL, 0x75A265284BAAE3E9ULL
        },
        {
            0x23D978530893F3D3ULL, 0x9D7DCAFEE09B2B4FULL, 0x41F72DB82CAE72FFULL, 0xBB7343E59E5B81F0ULL, 
            0x0586F7195407DAEEULL, 0xB937287A62ACFF59ULL, 0x26DE2611CE82F2CEULL, 0x9037336E40803BC8ULL, 
            0xCA9F4383D3A5EEE3ULL, 0x341AF439B8C683D2ULL, 0x3E5FD9D1E728930EULL, 0x4D1CD7F40B554D27ULL, 
            0x285F38A4EE4323B2ULL, 0x73A3886FD4A79F57ULL, 0x3E16C2E9E7DAB85DULL, 0x58012CEEA02F888CULL, 
            0xAD1A80BAF826AD03ULL, 0xE3904A47D79AE7E3ULL, 0xDA897649D4DD4D89ULL, 0x275F76FB0F9E61CAULL, 
            0xE26F19C49B114212ULL, 0x81A5A2BC3745783CULL, 0x0D468C55170AE043ULL, 0x754695AC563BEF36ULL, 
            0x7949139F3F382D55ULL, 0x3F0C01CD7BEACB91ULL, 0x4307FFA90CBE5D71ULL, 0x611C694883B76CADULL, 
            0x4265EEFA646B3F50ULL, 0x4A7BC758FB2BC647ULL, 0xA94D2799E0E90E1EULL, 0xA9B751E0E613A628ULL
        },
        {
            0x66F2F22B873FDA88ULL, 0x8B85A66B00B202DEULL, 0x4EBA61628A63045DULL, 0x661FEA22CF9A9CFCULL, 
            0x0B5E5D7507315100ULL, 0x559F33086C22BA4AULL, 0x773D8F5C06C19BDCULL, 0x2877B4D91D92C06DULL, 
            0x9138C6D9341D6552ULL, 0x09FC843BBCA2DA74ULL, 0xF1677BE6B30D571AULL, 0x823AD65A5B426EF4ULL, 
            0x104EB9224DF77530ULL, 0x18B7634BC0492644ULL, 0x09E5D7B79E6FEF75ULL, 0x883648471ABDA0F4ULL, 
            0x758414BE2E69B3A3ULL, 0x23FE9833A7060292ULL, 0x18DB07B411C2FC8CULL, 0xA1271050F8F94DEFULL, 
            0xE476DE4489C6FDC6ULL, 0x7AA833E95B688928ULL, 0x72F5C5868282F939ULL, 0x068F5B691C4EC27BULL, 
            0x0A8A8B2B36598EBBULL, 0x0C2397724408300FULL, 0x8827FD349E831BBCULL, 0xD017585A7CFE1ABFULL, 
            0xE7F6EFB08262E681ULL, 0x51D6AD00E6720E3BULL, 0xAD3C4C872C05EBE2ULL, 0x14BBAEF9AF8A2789ULL
        },
        {
            0x165B71F7E769A751ULL, 0xC15B10DFCF62F551ULL, 0x9476A08F4265216DULL, 0x16CD38FDC4CB5B3CULL, 
            0x6732E122336045A5ULL, 0x4917E768D4CB8BDAULL, 0x20A3E7B9F52840EAULL, 0xA61C50988FC92CD7ULL, 
            0x38D724FEA56B1F22ULL, 0x3A9DC503ADCAE136ULL, 0xE87D23EBA8D20E6BULL, 0x6EBC7D9C136AC00DULL, 
            0xF8A5488478FA287AULL, 0xF00BBB038C9F4F24ULL, 0xFF8845A14BDE5CC7ULL, 0x5106A104D5EC409BULL, 
            0x827718DA111D59EFULL, 0xF88DF00E6B7BE577ULL, 0x56923BC454EED87CULL, 0xA5DA4F92DF1FD565ULL, 
            0xDED5FA9ACEB5E537ULL, 0xECB4E8FE17ADABA9ULL, 0xB4175D86A5620834ULL, 0x4BB428857A0E0E37ULL, 
            0x372843513A8934C4ULL, 0x075C40885A583873ULL, 0xA32FDA3A19A49965ULL, 0xC698AC8841D7ABD7ULL, 
            0x3BC9567C5D8DAFFFULL, 0x607474CED3C4A8EAULL, 0xE15B8AD3B679C947ULL, 0x775C7C7F0A5EF4CFULL
        }
    },
    {
        {
            0xC89D22E0BFAF47C2ULL, 0xA11547FD05AD9967ULL, 0x0FCC2AD7F5634A39ULL, 0xF3F33AB940D90432ULL, 
            0x91B648B255F25B2CULL, 0xA0FA0FAA0862DB85ULL, 0xCD12B37986FCA8D6ULL, 0xEE549B4ABBE1D414ULL, 
            0x45F42DF7C6609B37ULL, 0xA880B76F3E77E235ULL, 0x0DB9E20ACA6953B2ULL, 0x0775403AD1FA0FE7ULL, 
            0x194E4F16251C6365ULL, 0x4136B7A8BA0E0B45ULL, 0xE3632959BA9967B1ULL, 0x99C976E8FBEDA6E3ULL, 
            0xE0D6E25FBFE562ACULL, 0x2BE1D24343E8AC9AULL, 0x23F20FFDFC1180B6ULL, 0x5E7A86C41DD7F185ULL, 
            0xB92BF09C558598B1ULL, 0x30748EC38A606D46ULL, 0x3784D3CE36C3E87BULL, 0xD5C1099CEE63BDCBULL, 
            0x0891467389F6D5ABULL, 0xBE197F3A41899007ULL, 0x84F2211C45F2F177ULL, 0x4A3C9D804F4D8215ULL, 
            0x100369C50D5AFA58ULL, 0xCA733219A20980A6ULL, 0x6FEB09697C6A747DULL, 0x23AB1FEBF6CB5C57ULL
        },
        {
            0xF0E37C90723B2211ULL, 0x89421D984D6DF48BULL, 0xF7E9695CB9240869ULL, 0xC7D920C3B4529078ULL, 
            0x1FD45A276913D00AULL, 0x442FB7B3248D589CULL, 0x1A61771F98D928F5ULL, 0x8A10B2EC5E339092ULL, 
            0x3AD4FBBACB6532FDULL, 0x196457915B232EABULL, 0xC3946A093C14231AULL, 0x01FF6224C4185D0AULL, 
            0x7F161A2D93228858ULL, 0x5D24E84042B88D50ULL, 0x1ABE459F8017B1C8ULL, 0xA8B1D972D7BABD40ULL, 
            0xDCD0D6A5CBE1414EULL, 0x913A71A0B199A181ULL, 0xB8B069C1EA09FB38ULL, 0x0C9A0D73BFA66199ULL, 
            0x24095260A1559499ULL, 0xC30805D804C0BD99ULL, 0xE8728273307631F3ULL, 0xC8610F39A102F202ULL, 
            0x9EFCA5958159DDA3ULL, 0xEA68F2B7E0AC4D4AULL, 0x36764207A9BE6854ULL, 0x384E613E472F9FACULL, 
            0xA74665084ED4FFBCULL, 0x6178D736DD08F6D4ULL, 0x3813D32B8EF4B24FULL, 0xC7125E0E6C85FF5CULL
        },
        {
            0x61803BE7199119DAULL, 0x1B2905D7D0579173ULL, 0x7771B8412911984DULL, 0x38AE82786C1C7D1AULL, 
            0x29EBD576B2AAABB3ULL, 0x28FEDDEEB6933B1FULL, 0xA08A935E6448EBC8ULL, 0xEE4A161A511038BCULL, 
            0xECDDA75023E2AD00ULL, 0x283F7178E39C8F15ULL, 0xE4D6362A9EE3B75BULL, 0x33E9D83F4BD79254ULL, 
            0xBE27D822580D36F8ULL, 0xEDC318CB01CCF6F2ULL, 0x8E5E05CFF2E933EFULL, 0x2C6CFC64C8EF7798ULL, 
            0x340A03AF151D93D5ULL, 0x586AA5D9A9D229A3ULL, 0x6F3B728380D7B7A3ULL, 0x9794B1A95D9080F3ULL, 
            0x7DCF352099591491ULL, 0x63BC77E3A7B8B019ULL, 0x75ECBD7BA1F22A4BULL, 0x389309F3B0BFB4E4ULL, 
            0x45758855F800ED5DULL, 0xDDEEBE3ED70A8C29ULL, 0x404EFB6120204803ULL, 0x8151A483200BCF0FULL, 
            0x3D2A4BF3824533F4ULL, 0x8CE28F6805739119ULL, 0xCE8B363F84048A82ULL, 0x47D75BC59ABC0AC9ULL
        },
        {
            0xE1082FE7B0F33D9CULL, 0x94CCC6608A8560B2ULL, 0x3F93297A7915A781ULL, 0x87966F40E3EE9478ULL, 
            0xEE8924F3E2E35007ULL, 0x76856965BF087665ULL, 0xADFE5CC6337FCA3BULL, 0xBEDA452D0A8F1961ULL, 
            0xB944A9AC4BEC8828ULL, 0xF355A890C4AD17F8ULL, 0xD9788D7A6A48C92FULL, 0x03F3DA8EB1EA1F6AULL, 
            0xE4BF4B8C0DDD5B14ULL, 0xD81B1504AB2BE746ULL, 0x1407B9B46DD4E70EULL, 0x1DC93BFAF9B70760ULL, 
            0xD3B640A0BB9ADE7DULL, 0xBF79DB122C08FD2AULL, 0x777AAA06E2659BB9ULL, 0x565D61C93B41A42BULL, 
            0x9E8498125C2ECBFBULL, 0x52AC883B9BCE12E3ULL, 0xFDB4529FDF578AA1ULL, 0xB98701589BEB57EBULL, 
            0x28FD094BA994EAE5ULL, 0xB0F87C70BE05B3CCULL, 0x99C0314B1B1A26A2ULL, 0x93FA00426F0CE105ULL, 
            0x9FF4CD75017D4F8CULL, 0xEB08B4ACBD802725ULL, 0xB7B8A5EA8B27ACA1ULL, 0x8D5EB6C59137FBD1ULL
        },
        {
            0x22D483C917B6A5EAULL, 0x8A14E0300CEFFAAEULL, 0xE65AAB6CAE7EA6EEULL, 0xEF0E8EDB45C6233BULL, 
            0xA3438F6D023EA15CULL, 0x2360A0BEB0311A4EULL, 0xD88C93687FD0C963ULL, 0xF1AF9EAEF9888166ULL, 
            0x106219C408AD16D3ULL, 0x4D4BF6DFD128B29EULL, 0xC2C45CA259C2BB0DULL, 0x95C01A9238B48627ULL, 
            0x893038A0550D612CULL, 0xD7DEAA849B8AA7ABULL, 0xF83A3E8C8474D1DBULL, 0x382140EC7B0ED873ULL, 
            0xBB42745FB8F86EE8ULL, 0x1F8AD9852EF21466ULL, 0x3EDBC3391816B6B7ULL, 0xDC156AD07AECED47ULL, 
            0xCB0D8A27C827416AULL, 0x921A09DCA50527ADULL, 0xF9AAE2D1EC48771EULL, 0x60CACEB75EEFD323ULL, 
            0x6A64C7287D4C0D2FULL, 0xE33AA1886724494EULL, 0x61023551D4C9BBADULL, 0x67C05CC2BBF491A4ULL, 
            0xA95BD4553DF32C60ULL, 0x22DB35B08D997DC2ULL, 0xE780752E686E4B46ULL, 0xD2D856968B4C7823ULL
        },
        {
            0x026F996DBC532ACAULL, 0x0314EFC2C6C24739ULL, 0x7C313FB90E952FBBULL, 0x8C45A788A9C0CCF7ULL, 
            0x2344700CDDAADD54ULL, 0x7F05868AEEDD68B3ULL, 0xA79C3DEB24E3481BULL, 0xB050D0F85EB88F1BULL, 
            0xDF6B6A7B595D9A5EULL, 0xA18FF73A246B9FE2ULL, 0x40A9EC4F3A39FF4FULL, 0x5271A1D9B84A612FULL, 
            0x05623B3DA9D41A86ULL, 0x1F15CFA087A506EDULL, 0x537A3A57AC0E684DULL, 0xE8F26541C2279E59ULL, 
            0x37F860E8DE6C276EULL, 0x4A817210743D2CDAULL, 0xEF431900F3A4AC96ULL, 0xC3955AB1D610C7DBULL, 
            0xCC71D93F39A49C57ULL, 0x66C9C010EB7F8A7CULL, 0x19B8D7883758B9F8ULL, 0xE03B92ED532E3E94ULL, 
            0x331857BD3A576049ULL, 0x52D4BE1C41B1A8B4ULL, 0xEB4FD966542D91C7ULL, 0x7AB60E1A6B878A06ULL, 
            0xB5025F730E45CD16ULL, 0x7C8A033CF05570F9ULL, 0x1BF84A407C5618FBULL, 0x318052B54FF645ECULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseAConstants = {
    0xF768754149678131ULL,
    0xFCA0A42E2845721AULL,
    0xCD2B7C2A1CC796F0ULL,
    0xF768754149678131ULL,
    0xFCA0A42E2845721AULL,
    0xCD2B7C2A1CC796F0ULL,
    0xF8EB1A13DCC9AF9FULL,
    0x69FA7D8D62282D56ULL,
    0x22,
    0xE0,
    0x79,
    0xD8,
    0x38,
    0x9C,
    0x54,
    0xAD
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseBSalts = {
    {
        {
            0xD2E3AB6134B2D372ULL, 0xD8CF51C695F8BDB8ULL, 0xEE250E7B687DFDC4ULL, 0xE1BC3A75BF36D882ULL, 
            0x8C99FF151C6B9CACULL, 0xD31A24CA04309ADAULL, 0x8B43F156A98D76ACULL, 0x471F878BB5915E6CULL, 
            0x706BD2ED26DC3738ULL, 0x8B7785094EC6D4B5ULL, 0x152F539C8C68AF7FULL, 0xEBD427C34DA009D0ULL, 
            0xADE363AA2964A339ULL, 0xCDC661B28C2FBC17ULL, 0x31F2EA26BD0421DAULL, 0x6CD1696D94633D87ULL, 
            0xFF5B6A4A9D20A327ULL, 0x2C47F6515DEA2FF3ULL, 0x85BD52767F71CF63ULL, 0x780F702EAD02E9B4ULL, 
            0x68E138FBB56EFAE7ULL, 0x2A160F5A20F8EA41ULL, 0x52D8B37BB60FB7C8ULL, 0x63995A66D4C08072ULL, 
            0x01407015C78B02A3ULL, 0xD663C061F2EE8AD5ULL, 0x79517D3EDD6C7518ULL, 0xD9D0132DB3F8D6CEULL, 
            0x3D095047565FC850ULL, 0xE880F2C3450863D9ULL, 0xE315594475813325ULL, 0xC1CA7677C1E564CFULL
        },
        {
            0xA50312A53CE31636ULL, 0x2F9E81E503B23EBAULL, 0xFAD5F86F1E4F0D20ULL, 0x07EBF87BD5D2346BULL, 
            0x920C78D71A0AE1ACULL, 0xAB8237D7D7B46576ULL, 0xCA3DC40C393AF391ULL, 0xA361377BE4BE7AE5ULL, 
            0x59A18B7ACBDC46AFULL, 0x38548F65A37DACBFULL, 0xD7858D29F830DC8DULL, 0x39294AB59995DE7FULL, 
            0x3C707A330D0E3C64ULL, 0x3B0A6890569D6E58ULL, 0x0E62ED623F86265FULL, 0x9BF45D6F73274502ULL, 
            0x79D6B308E85E2C6AULL, 0x5E39D7D9CD528AB1ULL, 0x7451E10B6EBB7112ULL, 0x630B88A1575FD651ULL, 
            0x0C677C65099AA4F4ULL, 0x64C20E3D1B9F752EULL, 0xBBAA4AB0670C079AULL, 0xE989F820DFB39BADULL, 
            0x5DD75E917A7B6823ULL, 0x97E836DD3F5694CCULL, 0x5DD2199BE56FEF16ULL, 0xB824933638FF2AF6ULL, 
            0x460061855E045B23ULL, 0x5499A28367B6B06AULL, 0x1F6C76A46DB70E67ULL, 0xD56121FACBAAF81DULL
        },
        {
            0xB7C1C1674CB02499ULL, 0x182E9791432E73F0ULL, 0x4B591972AB9FBB28ULL, 0xB9CF2CC82252F58FULL, 
            0x2A73CDB348CAD1ADULL, 0x18559210E35AEBADULL, 0xB0791A9ECFE130A4ULL, 0xC1944FF4AA53554EULL, 
            0x3B764DC533B2DA36ULL, 0xB0898EF264D8EC21ULL, 0xF1EE83090B8F6917ULL, 0xFB64046C9ABB4355ULL, 
            0x7EFE9CC9E22BDCE4ULL, 0x32B55EE28553CA46ULL, 0xC3B7CFFBBC34E151ULL, 0x73160F11C1EE5943ULL, 
            0x8B4774BBE47B049FULL, 0x0689DCCC35394831ULL, 0x18A71FF2FC305102ULL, 0x796236E669C85618ULL, 
            0x3646C156A7CD10CDULL, 0xC7B5C886E9561435ULL, 0xCDCC34C9D4E86A6EULL, 0x03E71125122A92D3ULL, 
            0x609050FD4E529104ULL, 0xCDE80019E4112C32ULL, 0x449D5E5B729F46BEULL, 0x7499D6ACD5F3925DULL, 
            0x9875D656BACE8343ULL, 0x2422734B83465768ULL, 0x953C48FCE96BADDAULL, 0x39F446DE7698FD40ULL
        },
        {
            0xD055A696398F704BULL, 0x445C68E4CFC09953ULL, 0x1E0263E3FA382A10ULL, 0x7A72568177A424B8ULL, 
            0x01150D9D70F9236AULL, 0x5BB0437CF884DFC3ULL, 0x68D67AE3A3066C46ULL, 0x4DC60E7F04C34FADULL, 
            0x8ABA8F18889BAF77ULL, 0xBA7AE2643F758087ULL, 0x1C0885F1634E27B6ULL, 0x36FFA8A1D6F21A8FULL, 
            0x93C67B681D012CF7ULL, 0xA095440D63A5A90BULL, 0x78488F82D2919542ULL, 0x40F36AB60D8BC963ULL, 
            0x281C45D82AD15670ULL, 0xDD02D87995633F9BULL, 0x477F2BE34D84101DULL, 0x339B13EAE4743D46ULL, 
            0x32349AC5604AC722ULL, 0x99B71F2E83AF28AAULL, 0xF2AF888FB277FBFFULL, 0x4AF443275B6B4D78ULL, 
            0xD0D6DFAAD456E88CULL, 0x65EB80B675768495ULL, 0xF297A3758140B218ULL, 0xF00732510EC5F80CULL, 
            0x88FD643125AA0531ULL, 0x0515615720DEF03FULL, 0x83D0A9CAFADB5FB0ULL, 0xCAA4E3A1FF668962ULL
        },
        {
            0x909486A2074BCB7AULL, 0x31EE73C38A47CCB2ULL, 0x8265FFE7E682AACCULL, 0xDD0E55B62FB69F0AULL, 
            0x578CC693B44228BAULL, 0x8B79E9E8D0FE0EDBULL, 0x3F96E60B5BD8EA10ULL, 0x8CF68D8879D4F592ULL, 
            0x6E6632D3F2E409B3ULL, 0xBCC2349B7F567EA5ULL, 0x2E0938E6C6596C7CULL, 0x3461977B5AB4BCDDULL, 
            0x2191DE68CF82202DULL, 0x9EBB3B93F6ACC95DULL, 0x8DDCA825C063FCC4ULL, 0x324D7E6615D0ABDFULL, 
            0x615475C3931E7FCAULL, 0x3AEA6C218AA7D20DULL, 0xF6CF166D963CEF9CULL, 0x937B8D9D2BF535BAULL, 
            0xA55C682B437B6574ULL, 0x6CF2927E263E864DULL, 0xA6D5BD80F653A6A0ULL, 0x078DAB1604D85840ULL, 
            0x3D372FB0E884DD71ULL, 0x3C7CA4A6DB2816DCULL, 0x2C0EB5997D58B850ULL, 0x222EF4FF19BDC2F5ULL, 
            0x31E635160613B779ULL, 0x620F99D95EEA4C89ULL, 0xD2B3F740BF263D44ULL, 0x73A79A9B3FDABDA5ULL
        },
        {
            0x3D89ECF2C56EA1E5ULL, 0x4547EDD20AE7DE06ULL, 0xDBDA7B117AE37BA4ULL, 0xB2E6ECDD58F0BA28ULL, 
            0x2BA77B366E77FB9FULL, 0xD3E9D648EF0812CDULL, 0xF2553823E0EC3475ULL, 0x4A674DF83374EA2FULL, 
            0xB08DBBD2F5A3934DULL, 0xF651CBBA310A5F9CULL, 0x1C96690BD6ACC40BULL, 0xAF1540071B6F47BCULL, 
            0xDA76F4E8A0DBB808ULL, 0xB081534F0E780CA8ULL, 0x2A704676537F6CB8ULL, 0xF2EFD054D926F9AFULL, 
            0x9B524DE7B17AC1D5ULL, 0xD232F303FA0A337AULL, 0xA83A5A8EEF79CEAEULL, 0xC12703F512FC87C0ULL, 
            0x74F0C6DCE1807EE2ULL, 0x83270AB9E7A9EAFEULL, 0xD625173C68AA91DAULL, 0xA0D30F969E08E927ULL, 
            0x9793B880FAA98345ULL, 0x607BA5C869EA8E5CULL, 0x04CE03E90CD9DA54ULL, 0xE31F1B0B2F3C9320ULL, 
            0x86805F9AE98A28C8ULL, 0x0195B20307EBC58CULL, 0x7272ADDC52E1068EULL, 0xF8B91386FBAD1CAFULL
        }
    },
    {
        {
            0xE8BEBEDFF349A3CEULL, 0xAE6F7EC182F9C842ULL, 0x3BCD144DE497F058ULL, 0x01BF7B5D25B076C2ULL, 
            0xD996B263F05D0CDBULL, 0xD6C7C175973EBC85ULL, 0xF65D820A243F1727ULL, 0x11BD97DAEF580D92ULL, 
            0xBCA699FD666D62E6ULL, 0x871F81EBDA3BBCF6ULL, 0xE9721B7379475026ULL, 0x08CD91B4FA72E8DCULL, 
            0xA183279A5EB5F456ULL, 0x52731C83F101DEECULL, 0x798B8F852B994B84ULL, 0x57A106E67065E540ULL, 
            0x6BD7BDDF3DDC7F04ULL, 0x9EE294929E26EDEEULL, 0xEBB468ADDB8A0669ULL, 0x56E1709A505113F6ULL, 
            0x4D006C247B2DD788ULL, 0x51B5B9DC4084A952ULL, 0x70FEDA055070B878ULL, 0xD9FFFFD1C74FE23AULL, 
            0x99EEC77D56C16A61ULL, 0x2AC9CC2AC46E2752ULL, 0x4932AC769D38205FULL, 0x3D71E6706A9AAC9AULL, 
            0x6D5CEF68D5031FCEULL, 0x731F287683CD1093ULL, 0xF0885D2D6CA63274ULL, 0xC967E47BC3FC8890ULL
        },
        {
            0xA724857F92CD8196ULL, 0x24E79375E6853C98ULL, 0x103EA6EF4F5F8D80ULL, 0x637364563C362656ULL, 
            0x8EB1D07A47325B50ULL, 0x880F305C19F09C2CULL, 0x364A79D24BBAFF70ULL, 0x5A25AEEFE9F0FF93ULL, 
            0xBD4DCA8DC3429B98ULL, 0x41CFB599A5F0180EULL, 0x655BE0343DCA4751ULL, 0x2F1694C7D51AF0B4ULL, 
            0x3F0677AD9C02AF3AULL, 0xBBED492EC2B21B9FULL, 0x2A524675CB537FD9ULL, 0x3E49C2838BE340E4ULL, 
            0x56239D90BD44300FULL, 0xC982DE7BE077EE39ULL, 0x59AD4CA08D332426ULL, 0xFEEE7E6ACF8DE0D3ULL, 
            0xFE894489F7222767ULL, 0x9DC12C95410E7EA5ULL, 0x620613A1B8F57E54ULL, 0xC0DB41CA16349DCEULL, 
            0xCF5FBDCBF995DC36ULL, 0x47EBE38B53F77C44ULL, 0xDF412D9F5E2AD05CULL, 0x08DDC00AF3422F5EULL, 
            0xA86F0382DC870ADCULL, 0x6CA6A0ACE81525DDULL, 0xE925841BBA86C0FDULL, 0xC55D0D34C6E3D3B1ULL
        },
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
            0x721FE74EA8837B64ULL, 0x64FD9D5CF0EEB493ULL, 0x57DAEBAAD4883C3DULL, 0x93212885CFFF5C34ULL, 
            0xC1DD93AA50F50C87ULL, 0xB9B20FE431B4DB71ULL, 0xDC0EB3572275A736ULL, 0xDB4EA74B05A09725ULL, 
            0x06A343476668EF49ULL, 0x79D4904C74566185ULL, 0x377775D75B3A0FBFULL, 0xE9DAE66FF652E9EBULL, 
            0x98E279A9CC3733DFULL, 0x6D2EA6501A5C5E4AULL, 0x2540A93602D192ABULL, 0x040ACB20D98A5E22ULL, 
            0xA6521C625A402726ULL, 0xC167743086F8F670ULL, 0xE2146B0CA6BFEB4BULL, 0x159B2EE16F69E961ULL, 
            0x8D700641F37AD70CULL, 0x6FB072D98930049CULL, 0xD03503663EC8C3C1ULL, 0x93F8C71D3B95BC32ULL, 
            0x8E08C88F96CC569DULL, 0x1FF9BCCF4FB11B7CULL, 0x6421E1C7BC24B85FULL, 0x70368C682019286EULL, 
            0x84302A230EDB459CULL, 0x5FF73154D7ED58E3ULL, 0x2F72B703A76D9146ULL, 0xAD130EC26232CA80ULL
        },
        {
            0x889817821663BD3EULL, 0xEC9B89CDEA63A682ULL, 0x204F514494FFDEFBULL, 0x9F55A81C03CB0ECCULL, 
            0x79AA60CC4454C3BAULL, 0x98073F3F0374C5DAULL, 0x39C7560DE4E057F4ULL, 0x344213A7AC47D412ULL, 
            0x13D0AEFC7242B48DULL, 0xE1BABEF72BD28AC8ULL, 0xDC84AFEAC42075B2ULL, 0xB92E2A83C25711ACULL, 
            0x1504A5E54B259823ULL, 0x49B8E707F8A6F932ULL, 0x048F0669E3F35C3BULL, 0x5E8C1E5EFDBC469CULL, 
            0x69024152A5968AD2ULL, 0xA290A7CEDF76266DULL, 0x5B1F75340CF21DA6ULL, 0xBE3174E494295B9DULL, 
            0x1EC72762F7F14A1AULL, 0x19DC2F6564D0A4C0ULL, 0x76319751EDB58A70ULL, 0xED96EDAAC06C4B03ULL, 
            0xF584B1AC40DC28A6ULL, 0xC1C892F5203FC6D5ULL, 0x3A45291F19C50F79ULL, 0xDBB53FE00ED5EC5DULL, 
            0xCC9FB64F659EF4E7ULL, 0xC5E8CAE4A728B993ULL, 0x05C1EC032C4C71ACULL, 0x8A7E7895EF3CB29BULL
        },
        {
            0x29B2CD04758AD496ULL, 0x508986767AF4E4F0ULL, 0x5E0ED6DF8B8A020CULL, 0x3E9F56702A85904AULL, 
            0x7826D08AF208A615ULL, 0xBFF0989D47AF727DULL, 0xE09A09DE6C41C6AEULL, 0x66D276A3DBF9844BULL, 
            0x1846F731D88FA081ULL, 0x232630EE3D825926ULL, 0xC5A210EDDAC69BF8ULL, 0xE5C50BA317AA6E27ULL, 
            0xEEABD4C3C2F7A642ULL, 0x73AD2B900BA7893BULL, 0x4994D4ADDC230E88ULL, 0xDF3C57DF93EBF089ULL, 
            0x5E695297365732B4ULL, 0x5BB5B46B7D58FB02ULL, 0x7D8D637C09DBAF94ULL, 0xB9480FE14B08AC30ULL, 
            0x8262B0FD32C29791ULL, 0x92557D98CDABD2FFULL, 0xA1FABDE5A8913D59ULL, 0x09F4772A4F96CA7EULL, 
            0x2D45C1D4C782FE2FULL, 0x59D91C1F2C80A54AULL, 0xFA5F3D8479115F62ULL, 0x08B8014B4F14E95AULL, 
            0xFEBD9346EF0EEA36ULL, 0x33D04B71ADC94A1BULL, 0xEA66A1C31497FBAAULL, 0x0534B249663B61B8ULL
        }
    },
    {
        {
            0x057081606BF84E4CULL, 0xCEB8D50F8B6484F9ULL, 0x892342B09ABB2082ULL, 0x407AB57ABC8E42F0ULL, 
            0x6C47FDC32609B0F4ULL, 0x330B33102FF36B3EULL, 0x411AFD541C677011ULL, 0xE6C279AC114E6FA9ULL, 
            0x5777DC8D3723184BULL, 0x064F8CF4340BB04BULL, 0x5A10D132C83CEA4BULL, 0x25F0A3A29FAF0A96ULL, 
            0xE00D94688DD29BD1ULL, 0xDCB72B3FC8A5D558ULL, 0x54F31E7E60B323B3ULL, 0x25FEC606C3C43F61ULL, 
            0xE7BC7ADFDB3DA798ULL, 0x1E23017F4760B784ULL, 0xE4EB20D24DFD5FCDULL, 0xBD594090BFC73598ULL, 
            0x3F7933EACD814D8AULL, 0xA799A1487C970218ULL, 0xB739F28997930CD9ULL, 0xA036542D34289E3CULL, 
            0xBA0A2325F8C8BBE0ULL, 0x612BC20CEE2ABAF1ULL, 0xB16718A3BAE671F1ULL, 0x24646F6CD31341D1ULL, 
            0x7A1826680555BCFCULL, 0x57EE8AAEE09B9502ULL, 0x98BDA5B5CAABC3ABULL, 0xE1AE029099E761A4ULL
        },
        {
            0x2EC03E8AE888888EULL, 0x3A1BB4A9BEF139D7ULL, 0x815BF6BA28A6D50CULL, 0x4C2AE659D10269FDULL, 
            0xA777BAD4DDC0246FULL, 0x9A9A6B143621CD1BULL, 0xDCA7515739A68B64ULL, 0xE1B91E801D07A0B3ULL, 
            0xBD2635E44B8911A7ULL, 0x7A486E70E24053E4ULL, 0x7F60BE3E7FBBDD4CULL, 0x44945C721086A9EAULL, 
            0x67ABFA9C4E61BD12ULL, 0x03CC499D9B08C7B3ULL, 0x1C5E84A19093EF69ULL, 0x88226F757A03DD54ULL, 
            0x7CC46E6DD9FAF866ULL, 0x13C9F1270EDD4241ULL, 0x106CE1578CD15963ULL, 0x2F48F93B209AA3BDULL, 
            0x89B50DFBD576B573ULL, 0x2FCC514C0D02C0A8ULL, 0x48E14153CA466D67ULL, 0x1F62AB61C5A7FE63ULL, 
            0x1A233656240EE7FAULL, 0x0CB193CE37975387ULL, 0x2C403C9B3A16EC59ULL, 0x5DB5F22742BBE271ULL, 
            0x581521777AC76092ULL, 0x13146C504D11CE30ULL, 0x07842E409ED1BB4FULL, 0xE9C048A1EA9257B7ULL
        },
        {
            0xAD31B07A24FF1529ULL, 0xEF8106023BBB64E6ULL, 0xF832B4B2B7B7B3B3ULL, 0xED88E39D2148F197ULL, 
            0x3D7C6F4C34064EDBULL, 0x7FCBD143C33F82CCULL, 0xEB8DB31922EE7BD3ULL, 0x744F684CBF5D0EAFULL, 
            0x2E2925A3A923E545ULL, 0xFA8F560205EFDD98ULL, 0x928210A76C980612ULL, 0x85C2BAFC0E9FA482ULL, 
            0x1FAD7E3986E64D2EULL, 0x624678684700849BULL, 0xA1707CF93CE6C7F7ULL, 0x456D16AADBF916D7ULL, 
            0x31112299D2495CB5ULL, 0x4D46131BBE88ED4EULL, 0x7F79A80711BC5A46ULL, 0x10F85165E13E11E5ULL, 
            0x6060E27034F11726ULL, 0x37391B75A6004BF9ULL, 0xCE3A0A61CAD9D9D6ULL, 0x10F8721AB91A2C28ULL, 
            0x7E1DFA194C570CC2ULL, 0x73C51C48EED9B8C0ULL, 0xC0688CF1C23B8D61ULL, 0xD3ABC222F3CCF964ULL, 
            0xF173D5C3B4059EEAULL, 0xD03AB0ED19CFAED0ULL, 0x39FD8645B561C600ULL, 0x0E8C0C8B3421F231ULL
        },
        {
            0xA2D5DA5490212EFAULL, 0xD1C1822C75035397ULL, 0x17D898CE7BFD9EADULL, 0x664070630654B07AULL, 
            0xB775EE19DEE7F134ULL, 0xA7951B837F66EEA8ULL, 0x230953606F1A5261ULL, 0xCAD282DBA428A37FULL, 
            0x1E846FCECFBBD9F5ULL, 0xD43FCBC3D7AA32EBULL, 0xE4F6F089047A62C1ULL, 0x2618136B7E9DF48BULL, 
            0xB51B96898DF3BCC5ULL, 0x677EF4577D96B08AULL, 0xA1BD9EC34BB4B4E1ULL, 0x1577F53FEA7E12F4ULL, 
            0xD161D0FD9FC3BB1AULL, 0x14F1C8AA12D37AAFULL, 0x486673B2BA69F3F7ULL, 0x62DB0F6C147AC7F5ULL, 
            0xA28940AE8261D7E3ULL, 0x8233BBD0EE4206C9ULL, 0x63B2E87A11493FC3ULL, 0x9CA7D4B12969F104ULL, 
            0x9D9C91C33F08BB62ULL, 0x24F12300CDDBD47EULL, 0x1F294B8BF37B8038ULL, 0x2DB00C9DF0AF8963ULL, 
            0x1DF0E2DA0DE70111ULL, 0xFFC9B823DE66F101ULL, 0xA9EFC003226B1DABULL, 0x177513C60F665A83ULL
        },
        {
            0xC8B70179C6D1C2C4ULL, 0xC1CEEDA6CE70FFD4ULL, 0xEB1F56167A0872E8ULL, 0xDD7EBA4FE2CEBA8AULL, 
            0xBFA737525510FD09ULL, 0x80DBC106627E85B6ULL, 0x45675E05810471FEULL, 0x2C464C206F6D77DBULL, 
            0xA846E7DABD8F4FD5ULL, 0x545F4B256D6BC0A0ULL, 0x6A2E50B26A5D9C2FULL, 0x04E2D64BB13B535BULL, 
            0xE6AE0932F2F8AD99ULL, 0x1E728CBAB44EA47EULL, 0x87E3609E3A124D2CULL, 0x484AC47A3D7F7600ULL, 
            0x7F94B8A3375CBCF3ULL, 0xFE604BEB87F4A0DCULL, 0x4D825479DB0E35C5ULL, 0xF92E9DA3C1CDB8D3ULL, 
            0xBC7E7575AE285317ULL, 0x85146702B35C13D6ULL, 0xFCC31FE8286DD547ULL, 0xD762534FAC1074FAULL, 
            0x797F95865EBAB771ULL, 0xCC72A551765C2617ULL, 0xD57590463D96C8A4ULL, 0x03CFC92686CEFE6EULL, 
            0x3082DC0EE0A5E383ULL, 0x75AAE8AC2C1CA2D0ULL, 0x23643D51FF2E3A83ULL, 0x4EA371930D159402ULL
        },
        {
            0x6F9E4316160E5FDBULL, 0x8A8196BB80291B49ULL, 0x7664EED3988ACB7EULL, 0xDB18AD3B3C7278A4ULL, 
            0x7382F646A0DDC1D9ULL, 0x1A499C48310B4778ULL, 0x32A0843413FEA455ULL, 0x40691C1A17A8DAE1ULL, 
            0x9DF471FAF2F8C9AFULL, 0xD50855907CD85B9AULL, 0x374CABB06EFD7F28ULL, 0xA1E0B5761B7FA636ULL, 
            0x279724AF8E3AE813ULL, 0x288C8B408D6BB700ULL, 0x1731DCB6537AADBBULL, 0x5674CDC524F56B0EULL, 
            0x22850FC15BFC788BULL, 0x2A267DC08632C0DBULL, 0x84E2F1BE56A1FA6CULL, 0x3DD4581DB5B4D07AULL, 
            0x2E23D0A4FBDA5F76ULL, 0xA8B8374DEB19A94AULL, 0x1CCDA44E963D31ECULL, 0x0CB7D9EFA9E32078ULL, 
            0xB54E0F8E35BA1B4AULL, 0x88387E8074F14850ULL, 0x1736600A62E494B7ULL, 0x3A45FC1F8A793F40ULL, 
            0xBB96B0A2A0BBE33FULL, 0x6FDDAA7A3420EF02ULL, 0x757082B408254846ULL, 0x4FDFF3AD831B7DB0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseBConstants = {
    0xCFA3D0B1889D5D21ULL,
    0x73B2DCA3947A1A77ULL,
    0xB1967F50949D4D4FULL,
    0xCFA3D0B1889D5D21ULL,
    0x73B2DCA3947A1A77ULL,
    0xB1967F50949D4D4FULL,
    0x742A0374869BBAE6ULL,
    0x6E15BF7517110EA3ULL,
    0xDD,
    0xC0,
    0xF7,
    0xDA,
    0x0B,
    0x89,
    0x53,
    0x63
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseCSalts = {
    {
        {
            0xAB37323E2709F06AULL, 0x86970A90FC4667D0ULL, 0xCFB076143F06BFD8ULL, 0x8F6BD983EABD4C0CULL, 
            0xB4BC9DDAD81EFB71ULL, 0x22263B4D9129529FULL, 0x9C86516BACD8CCD6ULL, 0x578E8151D8D1581BULL, 
            0x9C177537D9BA7FEAULL, 0xC1A3E6FCF890C8B5ULL, 0xE192F3587DC2169EULL, 0x3AC7E4EA8D036467ULL, 
            0x6EBB561228DBA21CULL, 0xCFE3CFFC6D264D93ULL, 0xB0FAD93B85346C31ULL, 0x505E59F492BCF7E3ULL, 
            0x2A6BAAFA4CB7835DULL, 0x450C5A66E8B9F6B5ULL, 0xD41F7FE6013F423AULL, 0x2C6789CF23E31943ULL, 
            0xA9CA1DEFA20D8625ULL, 0x8A90B8398091AD0FULL, 0x0E0B2F6FCAD1ACADULL, 0x40145326EC385CAEULL, 
            0xBB81F83168004D59ULL, 0xDFCDD9B7721CC169ULL, 0xEBB077EB376C6FFCULL, 0xECE86EA973AA5D3BULL, 
            0x2A9D9916132CE93EULL, 0x2455EDE81BFE8E18ULL, 0xDCD59D49E0BAB10FULL, 0xC3B844C71609BD06ULL
        },
        {
            0xB37C8D143F0CEDE4ULL, 0x54544D6E48EA2A3AULL, 0x5B352CFDECB56444ULL, 0x72DED28D3D45751DULL, 
            0xD4A9E436EE216B7FULL, 0x79656F03486D2B9DULL, 0x1E4FDBA3D7E4B319ULL, 0xA73DF52787322F28ULL, 
            0x7D970E9EB539F127ULL, 0x85C640762C9F3AA0ULL, 0x65C5F1D0CBFF1BEEULL, 0xD7CD1BE56ABBA4E1ULL, 
            0x0BFBBD9106E5FCE2ULL, 0x6EEFC88031C71226ULL, 0x56C32769B23F7FDCULL, 0xCA8C6CC4F8A20916ULL, 
            0x57823259D18E98D5ULL, 0xFDAB90FE2CED3E0CULL, 0xA0555CD44980D41BULL, 0x9AE09DF6CA95DD61ULL, 
            0xECEBE0C7EA55B7AFULL, 0x1CF51F48AB28D148ULL, 0xD3D430D5328C8196ULL, 0x17377D49BCD0BA28ULL, 
            0xDF236B541CD59062ULL, 0x3D6517078F503720ULL, 0x10EEBEF66A3D23BAULL, 0x91F8657657C71E6CULL, 
            0xD30BAEE9171548E8ULL, 0x1BF429EF267A0446ULL, 0xFB8E62B65D2E984FULL, 0x05A132EC4405BF52ULL
        },
        {
            0x6393ABFB04DC6D60ULL, 0xFD6FB38433D73A4CULL, 0x237A11EBFFD5C98DULL, 0x22F04E9CD87517CCULL, 
            0x176A12B000C25A4AULL, 0xB7849B8AF595CBA9ULL, 0xDD0995299689E8EAULL, 0x6A23A4D0E73D3A4DULL, 
            0x9457D362472EECA6ULL, 0xEE7F64EE55173D3CULL, 0xBF4B6BE221DB18E4ULL, 0xC659D69BAD4DF588ULL, 
            0x45EA666919B804E5ULL, 0x1136DF8F37510F92ULL, 0xE712E4220C7B4A3FULL, 0x101390C1F89E7A75ULL, 
            0xE27DAAEE5EEE7751ULL, 0x4C860D3A4D9A6B4EULL, 0x47316301CE2A698BULL, 0x7F31DB304C07C7DAULL, 
            0x0AADF97F0A8167C0ULL, 0x6F7960561DF470DFULL, 0xD8CCB709B3F37386ULL, 0x469F646457823592ULL, 
            0xCC4F5E37B55079ECULL, 0x3A19A1FEB81FAFB1ULL, 0x30AE04CACDD22518ULL, 0x5D46E63567FABFEFULL, 
            0xF4CEC9A980D03DD9ULL, 0xEFA68714EDF8B8C6ULL, 0xED7D321B5D6897AAULL, 0xF572F86543FBE8A8ULL
        },
        {
            0x429826128A45870FULL, 0x87045D40EA7A04B3ULL, 0x0984D6DF257C0B88ULL, 0xB874F67D28044B57ULL, 
            0x1920757E60255D5AULL, 0x8E4B87F833AA9185ULL, 0x7F594FF66D80A4A5ULL, 0x3712CF708B5D2A2EULL, 
            0xE5A7B54ACFABE9DDULL, 0x30AB5CC2EF7FA1A3ULL, 0x8CA15BB0A4CC0153ULL, 0x3B25CBE26FB1C7BBULL, 
            0x6DCBA60F3AA1F8CAULL, 0x96971F480FE3D404ULL, 0x6772F9EE5688F8ACULL, 0x72CDC849E7A067D5ULL, 
            0x9432F9731917876CULL, 0x09571EEE358B3D4EULL, 0x7BA1743BADED6A28ULL, 0x709C9D079E715D1CULL, 
            0x6B0FCB38E8A012F4ULL, 0xE4A5985917F33FBEULL, 0xA34A7887771795CBULL, 0x573A14C4808D0825ULL, 
            0x993580B5A7DA3D76ULL, 0x1A626EEA36B7B11FULL, 0xDE6A5ECCAE264ACCULL, 0x2E6A49597F6009BFULL, 
            0x93823820AA67BF96ULL, 0x573B8342BA965D4AULL, 0x67C7D4DAA5B97CF3ULL, 0x989E3EF01F3D46BBULL
        },
        {
            0x463F4FBE3402F3DCULL, 0x3FEBC347F9499BB0ULL, 0xE7B985FFD6B3036BULL, 0xF5B14BE69BC9098EULL, 
            0xFD424A0F7C79DB54ULL, 0xF4FCBA808061E02CULL, 0xDC584F7179634F9FULL, 0xE28D84FDBCC2DC5AULL, 
            0x90C137B715133DFAULL, 0xAA29F2D30CBD8B4DULL, 0x6CF9AC6EB0615F47ULL, 0x4B5B8DF1F8363755ULL, 
            0xFE5422445D5EE4FDULL, 0x4A8D506BB2600121ULL, 0xA8143017079769CFULL, 0xF7F74DC35D98A1C6ULL, 
            0xCD1AF045C22ED62DULL, 0x3455188EA3BA726FULL, 0x4227F617B02E67CAULL, 0xF699C57B7288C48CULL, 
            0xB63C5913A77A0199ULL, 0x20A464710955B958ULL, 0x643C05B81AE8DE48ULL, 0x10CAF6B051D9D720ULL, 
            0x7AE00E998B6BCC6BULL, 0x62895980DDC12736ULL, 0x6C1F138BCB6364D0ULL, 0xD2CF731BF451D0BDULL, 
            0xEEF8EB4F59013A3BULL, 0xC1B1E3DBE4E2ABD6ULL, 0x77B231510F2CF218ULL, 0x66902BED6B136FEFULL
        },
        {
            0xBC0EB37254B9EFA8ULL, 0x079F9970E7A29622ULL, 0x12E30BF0244C3F93ULL, 0x58643C92600CC26DULL, 
            0x702E56DD55439B56ULL, 0xFB681112BA334504ULL, 0xDF2975C36870049BULL, 0x31E16401D0A4C6EFULL, 
            0xAF8230DC56496E26ULL, 0x0B3F2585BCA96870ULL, 0x0D141AE353BC3D4CULL, 0xB1A3995B910B2948ULL, 
            0x46D7E5AED00D7AEAULL, 0xD9466C47F8312706ULL, 0xD4D5FF3C6C94C882ULL, 0xF7FACFABEEA2C737ULL, 
            0xEA9E73B46654DF64ULL, 0x68C0D6FA73A36BF2ULL, 0x313516AFDC220355ULL, 0xFC3BD7A0DF335F7FULL, 
            0x00D195068FA891E0ULL, 0x7139446EA1FB6AD8ULL, 0xBF23BF777F90B2D1ULL, 0x9C6620D1DEAC1D8BULL, 
            0x6422F2270A47FD40ULL, 0x82255CE2AEC12829ULL, 0x6C9F93EBB439365BULL, 0x304915310927F669ULL, 
            0x25493F261319E1D2ULL, 0x66EB54971229B7E5ULL, 0x05D41EA0D078A955ULL, 0x921CFB3335365F59ULL
        }
    },
    {
        {
            0x9B5B1E59380863C5ULL, 0x5074DA74B19E8E6DULL, 0x404589FDA6273DF0ULL, 0xC2CA88C3CE06ED9EULL, 
            0x886EB0F29B10DEB4ULL, 0x786370D9BC139506ULL, 0x9F8EB554F208A3CCULL, 0xACBFFB265E655598ULL, 
            0xDF23930F55478D23ULL, 0x6BF2CD4F639AA35DULL, 0x5ECC8CFE9C924372ULL, 0x6C4575BB21601B07ULL, 
            0x190637588F12AE53ULL, 0x01D3FAFEA06E3862ULL, 0x73E7D531B652B87CULL, 0x70BD2F880F27C139ULL, 
            0x278085DA01F22715ULL, 0x6BBF59530EE4D65EULL, 0xF91C7AC5944B362CULL, 0xB27A9857F42F0783ULL, 
            0x772DE7D3317A2C59ULL, 0x3D892C9A501467C6ULL, 0xDC27DA1206519431ULL, 0x1D6FEE7F56E6E868ULL, 
            0x290321352915C7C1ULL, 0x8CE5ADA884A48C10ULL, 0xF8A109E1DEE9B5C5ULL, 0x9C899B87893638EAULL, 
            0xCACEFD4CC2EEB143ULL, 0xD551ADF28AB5C207ULL, 0x10AE414F9F353CF0ULL, 0xCB661027CCF3B29CULL
        },
        {
            0xCE366B69191F8BDDULL, 0x7F832DF8139F9931ULL, 0x685B4BE9F0D71D11ULL, 0x95EC8426837ED9ABULL, 
            0x0C5C3810CD9B50FAULL, 0x5AC9E676B59B0AA2ULL, 0xD87F434A8419B797ULL, 0x82DA4D057590127DULL, 
            0xD54354CB4E35F2F9ULL, 0xFF62E5C064526E5EULL, 0x9A5D7ACA200BE348ULL, 0x8CBCF82BDEC55437ULL, 
            0xD20D41719E2AB1FFULL, 0x9C8CEC37E2FADA38ULL, 0xA5EA913E6F4F27F9ULL, 0xA91D82D31DBC6CDFULL, 
            0x492BD199AC33CF1FULL, 0x4F45273187A484C9ULL, 0x492E76E5B80865FEULL, 0x95AD5ED336A76A50ULL, 
            0x95A92332A22BF4B6ULL, 0x6161CB25C9D58C4AULL, 0x93C916B214C9AE62ULL, 0x8FE275EA6CD1A01FULL, 
            0x763DB7108B949D60ULL, 0x998ECFBA40407E1BULL, 0x623F835764517DDEULL, 0xB331A62757309D7DULL, 
            0xDDF98DF6210D2CCBULL, 0x45A3D7076808277DULL, 0x3558076FF2BBBE59ULL, 0x96DCEF640784BA47ULL
        },
        {
            0xEFDAE77D795CD0CEULL, 0x6E95F4F1A632C94CULL, 0x908AF07B74464C31ULL, 0xA0CEC8A4102B313EULL, 
            0x6B107B6C0F56B12AULL, 0xFEDAFC7CC5EDBA64ULL, 0x8A98C51822ACED4BULL, 0xF751683C72949600ULL, 
            0xFD8EFF342738E035ULL, 0x7A9DB9585C386C68ULL, 0xD2731DDB782A74B3ULL, 0xED5D9CA57B35C1BAULL, 
            0x491364290CAB0549ULL, 0xFE46A2FF52A7DF1FULL, 0xD859FA1AB7DA5B15ULL, 0x164F468F6BD9EAC7ULL, 
            0x916C5FB6CD6D25F8ULL, 0x0C3CB9BF04DD44BFULL, 0xFC7B51847544DA1AULL, 0x0DD40D9E508FB67DULL, 
            0x6B44EEB607ECCF3CULL, 0x388533B97661CF50ULL, 0x3F51876E600FC6CFULL, 0xD967204BCC7844D3ULL, 
            0xAA0E60E8A6E213C7ULL, 0x15B0F0416FC9BC08ULL, 0x91062F4F0808E3A0ULL, 0xD6EFF3017CE9C9A9ULL, 
            0x3458863D9D78FD93ULL, 0x81842C470DA865FAULL, 0xBFE82D2C75209EA0ULL, 0x319995174F6AAD2DULL
        },
        {
            0x9C5D90B8797DBAE1ULL, 0x65BEFFF41873DCEEULL, 0xB6E889255665547FULL, 0xCA3B42BB5890D491ULL, 
            0xD6A753BDA2BEEF59ULL, 0x8154468C8D67C2D2ULL, 0x17F94D42AA87A6D3ULL, 0x02DB7C1674B4792EULL, 
            0x728355B886C78D8EULL, 0x9A7AABECC936FAFFULL, 0x70ACDC4563B3811CULL, 0x2029033A08588243ULL, 
            0x6EE095745397D303ULL, 0x844E8F0FD1B8DA99ULL, 0xF1BC5B07939414E2ULL, 0x6D49F9914A95D073ULL, 
            0x35D082B815E21630ULL, 0x5414D43A0852D552ULL, 0x909F5BC1EF16AE6AULL, 0x006B85895A37D5E7ULL, 
            0x690335BDFA1908F4ULL, 0x09F11B3B008259C3ULL, 0x7C9E3D1B540DC969ULL, 0xFDF8D163DA77F7DDULL, 
            0x92DADEE0AA0E633FULL, 0xB6AEE82C56633CE3ULL, 0xBFFF980716FD236CULL, 0x08B78B37458C268BULL, 
            0x3FF80A7A9FDF4674ULL, 0x2D7C04A519F36303ULL, 0xA0E6AB6B71B0D6ADULL, 0x04A42F5BB85A05E9ULL
        },
        {
            0xBF5BB142D680938DULL, 0xF1E411BA8CA73AF8ULL, 0xDFCFCAEBCD6E9982ULL, 0x21153D588B6F528EULL, 
            0xA75319DF62D75733ULL, 0x766F44655DB93E45ULL, 0x2494A9D734907D7EULL, 0x5AFC0464D6B42AF1ULL, 
            0x02EC395580DE950DULL, 0xC9491B8637CC28F6ULL, 0xF48BFC5EA921BD57ULL, 0x836EC64E24F45C98ULL, 
            0x03395C6B524625E4ULL, 0x0549452E05341252ULL, 0x4E8E8AE87067BF72ULL, 0xBF79D7847E3DB598ULL, 
            0xA4E6D4C2DA70B5D5ULL, 0x1917824E3FBA4CD5ULL, 0x5F8AD0C1464758ECULL, 0xDEE79C5BDB5019BAULL, 
            0x2D9865C9C2FB1492ULL, 0xC9776F0C8CFCBD7AULL, 0xE4FD86EA7C00D665ULL, 0xEDC932A1819BAC31ULL, 
            0x019E2A0A02D1B5FEULL, 0xC2B34DB22FE293F2ULL, 0xF0175DA23BFA75D2ULL, 0x4AB7F58F94EC0E6DULL, 
            0xFEC68675794D8C7AULL, 0x07FF49F320AF209FULL, 0xA7387F4E8E6D6C42ULL, 0x5DD8B5DF0451F688ULL
        },
        {
            0x67866E37B1821DC4ULL, 0x361237F24931F7D6ULL, 0x12166EF705F2704EULL, 0xD8DFD717E89A8546ULL, 
            0x1CFA1645FAFF3EA7ULL, 0x92755B6C0DB669E7ULL, 0x23E6C26FE52ED487ULL, 0x08108BF189180982ULL, 
            0x99024B4797F427EBULL, 0x2B16DD674873C87BULL, 0x055C8BB7E6FA9990ULL, 0xA19FC7706F07DED5ULL, 
            0x9C096DF1F7046E40ULL, 0x456320E3AA7564C9ULL, 0x1B3FA818D7518D62ULL, 0x6F5C0F94FE397016ULL, 
            0x4AECC0B72CF8E774ULL, 0x50E0B7F66BE1D5E8ULL, 0x55C1BEF3DCD24C62ULL, 0x066BFFB39CAFFE6DULL, 
            0x09B575634E50B6AFULL, 0x1F9AEEBF89A3A72DULL, 0x5B359EFB893A6B12ULL, 0x1FE2D86C5655D60CULL, 
            0x6963546F543594A2ULL, 0x095471854F7734B5ULL, 0x448C87F2EAD38B5FULL, 0x662C31D85BBDD6E4ULL, 
            0xD50AFAF88A76DB56ULL, 0x8AC2E7C3F55B837DULL, 0xB4EFF46A3C4F3A72ULL, 0x9B2BF3488CB9984AULL
        }
    },
    {
        {
            0x746435B72082E113ULL, 0x5FBA07A9B676EC77ULL, 0x4522A9BE741682E9ULL, 0x1FB75BDBA1C929CBULL, 
            0x9E01DC8569BC7DBBULL, 0xD05BC4E81C207816ULL, 0xBB4A21EAB3349649ULL, 0x9E606B8658270DA7ULL, 
            0xF79CD02BC4834BD0ULL, 0xB064F1E390E1097DULL, 0x35674E33F5DC42EAULL, 0x1BCBC91E0C054D68ULL, 
            0x79A982AFA0E09AABULL, 0xDDA862960BAA558AULL, 0xB2267B9F0B8677BCULL, 0x7102A7BA001EDECFULL, 
            0xB5729231B9E2A3BCULL, 0xF75AB577DCFDC434ULL, 0x3B75E2190773ADC7ULL, 0x0C1CD70BF7522A1CULL, 
            0x0877B037C0796BAAULL, 0x38B509B31ABD281EULL, 0xFAD71DED333203EFULL, 0x4127FBE9C6C7406FULL, 
            0x3FCCD6986631FAAFULL, 0x80A28B4BA24778DFULL, 0x320269C8FADD872DULL, 0xA33018FD176545A7ULL, 
            0x346C9C1459F7555FULL, 0x1DE1941259605405ULL, 0xB4D30884EA03073EULL, 0xAF23DF3866576A04ULL
        },
        {
            0x176692FB4B558E42ULL, 0x868ECD62B35241C1ULL, 0xBDE69AE94CB11159ULL, 0x49BC83478BEAC833ULL, 
            0xE10CFA5A2AFF0598ULL, 0xCD12C0A11CD0BC47ULL, 0xDB56B0CE66D2D896ULL, 0xFDDDA18D273B15C1ULL, 
            0xB7CF66A73E0892DFULL, 0x26DBC852F7454448ULL, 0x4EA49D0F1F3C93BCULL, 0x8D6EA5CE314FEB4EULL, 
            0xCFA7435AC389465FULL, 0xB94BC10CDA9464A8ULL, 0xABF9DC7E3959E58AULL, 0x5AD5B78DD81F348FULL, 
            0x3719FD397ED82F1EULL, 0xA04495511B8723A1ULL, 0xFAC471CBA83160C5ULL, 0x66FD10E754569183ULL, 
            0x6B3A7CB48B08E023ULL, 0xAD768B28B10AE1E7ULL, 0xB0291681187EE5E8ULL, 0x7F0FC0E64F08C7B9ULL, 
            0x0E2983A498FDD6EBULL, 0x4EE2DD49D40CB881ULL, 0xA224481EFC846622ULL, 0x5EEF5369285C4BE8ULL, 
            0x048156258DC1794CULL, 0xE3F9E62E591E5792ULL, 0xC0E530FC929347ECULL, 0x4E201B384B8BE002ULL
        },
        {
            0x2129C6E71369FF49ULL, 0xCD8F6FEFF49F086BULL, 0x1EE00107EC51CE72ULL, 0x42CDDF71E40BBB34ULL, 
            0xCCFAFA3031388D82ULL, 0x1391BA55A51A4104ULL, 0xC3C887C588D2F9CEULL, 0x61EE90DE7F618154ULL, 
            0xD1A3FD933C47F468ULL, 0x9E0DAA6CB5BE6010ULL, 0x257FF166345A1035ULL, 0x16E53D3057287886ULL, 
            0x35E7F710551D1F58ULL, 0x5C02970D170CEB16ULL, 0x1F2A69BF17EAFD3AULL, 0xB780902C6452DBFAULL, 
            0xF75AB1AE65555284ULL, 0x4797D4040CF29F7BULL, 0xDF8A7698B5B46A40ULL, 0x177325241AB645A7ULL, 
            0xA4DB7D78F5AC6D1EULL, 0xEC5A033D57086747ULL, 0xDFDBA8C2058CE7F6ULL, 0xA488F5D10E188DF0ULL, 
            0xEADBB8380102C2B0ULL, 0xA1285B39ACD99E09ULL, 0xA2E11BBB213E82F7ULL, 0x740BF3B59E0539F1ULL, 
            0x47B48FE3E1E01797ULL, 0x97871598C5B87220ULL, 0xA4BC199C7AE8B3D0ULL, 0xCAE563DA2665FF12ULL
        },
        {
            0xC2DA63FD2CC10AFEULL, 0xCF8236017EE6DA2EULL, 0x185D029A7A223AE3ULL, 0x1E92033EFDAA12B7ULL, 
            0xB76522D2FFB666EDULL, 0x97B2C793610F7F2BULL, 0xF68DCB4DE47BC698ULL, 0x5D2CD3A0A6E923F6ULL, 
            0xD7C3B348F6DEC112ULL, 0xBC5274A07F957BE6ULL, 0xB703E357C179F918ULL, 0x7DB2EABDC1C8D8ADULL, 
            0xF72C92426CA6CED5ULL, 0x308443198EC8B664ULL, 0x2E7AC78A840CBDACULL, 0x0862363AC4EFB429ULL, 
            0xD6E70D76D712CEA6ULL, 0x6C4F14CC21C426F4ULL, 0xA43016F734B07C9BULL, 0xF71396B64772E91EULL, 
            0x18292735B720A003ULL, 0x08950583402DCDE9ULL, 0x14755179AE93B132ULL, 0x165687BBF295380BULL, 
            0x2A938E0DB1A7F1EFULL, 0x9FD08ECB45FAC19CULL, 0xC4D577E6452903FAULL, 0xB1ECAED9BA461735ULL, 
            0x1D0E152EB6D6EAC6ULL, 0x7476D2042AB1FE9CULL, 0x324F4CA4C55FC3C3ULL, 0xE94D5F8123348158ULL
        },
        {
            0xA5406799294EC2D5ULL, 0x7E9BA09A6B4EE5FCULL, 0x04EBBFC222FE83F5ULL, 0x3BCCC631BB4554F8ULL, 
            0x4192B39C0B434DEDULL, 0x225C4352DC22D2D3ULL, 0x6B6F6608FF53D6F3ULL, 0x4504726F97E96CB6ULL, 
            0x0DE484A541333D56ULL, 0xACAA15BD82F8170DULL, 0xF0670986859CED8AULL, 0x7BA2D175A8822974ULL, 
            0xCE7058A003E003F6ULL, 0xC32E62641B741FB1ULL, 0xA7CD551DC4118F6CULL, 0x892F6B93713BD511ULL, 
            0xA4D04FEB942BBCA2ULL, 0x80C20717A112EB1EULL, 0x5B720C25B18E35ABULL, 0x0BBA4F9BCFC0BB5BULL, 
            0xCEB3D30325B27F57ULL, 0xCDA9169F728BE096ULL, 0x5AE3B4CAC4CE71F2ULL, 0x6143314F3C01B71CULL, 
            0x771E24A424AC872EULL, 0x8F7B7FE2502A97FEULL, 0xC2A5467958E00391ULL, 0x68A0FC016BD88F28ULL, 
            0xDF97853AA6E8ADD8ULL, 0x1318122E85EF46B9ULL, 0x212B4E4768D4633DULL, 0xDAED36CDDF4590F9ULL
        },
        {
            0xBF4A43D6647C3935ULL, 0x704EFE1453E6BB1BULL, 0x91CD178110B18582ULL, 0xA7A1CBA91A0A6F3DULL, 
            0x71F60C8D223FB6D8ULL, 0xFF981353E5CA4970ULL, 0xAE06467408DA8E41ULL, 0xDB09E2563314CEDDULL, 
            0x5BFB5044CB5C86F8ULL, 0x0698CEFABB22F432ULL, 0xD82AA948F015FED8ULL, 0x817D4ADECC0409EBULL, 
            0x9670D7C5F14AE799ULL, 0x56338779D4BBCA9FULL, 0x5DD135D3432A51E7ULL, 0x7E39EA4836E79322ULL, 
            0xD378627B97291E3BULL, 0x08AA05334549F888ULL, 0xB6E63BB7C5D290AFULL, 0xE216E677C4D0C798ULL, 
            0xC31A3CE095EB25FFULL, 0x775D9DD05B1F5843ULL, 0xCECC00DDE9393773ULL, 0x35CAD73E12492544ULL, 
            0x1943E9759CB0ABC1ULL, 0xEBB697EEF3C62405ULL, 0xC281B5D59D3C2D1EULL, 0xCB44AB6F460ECCE9ULL, 
            0x4A833461EEC2B690ULL, 0x6BEDD4C9CA1F1CB8ULL, 0x99F85C09B58DDB3CULL, 0xA8894E9FB41D334EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseCConstants = {
    0x78E0ECE80586EEB6ULL,
    0xC5BCB9C2BEA6A3F2ULL,
    0x2F7CBDFDEA858A05ULL,
    0x78E0ECE80586EEB6ULL,
    0xC5BCB9C2BEA6A3F2ULL,
    0x2F7CBDFDEA858A05ULL,
    0x0A580B999E8CB5C5ULL,
    0xDCD7D13E9F17CA12ULL,
    0xD7,
    0xA0,
    0x13,
    0x37,
    0x70,
    0x56,
    0xE2,
    0x78
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseDSalts = {
    {
        {
            0x9B2091CD44D9B267ULL, 0xECFCBABF51FEDCD5ULL, 0x77BE06A5225C1201ULL, 0xA232078E15BFF647ULL, 
            0x038C075C7320581AULL, 0x0021939661FAAD91ULL, 0xAEA4CE92CF70157AULL, 0x399973802FC3E73BULL, 
            0xEA2259B18C1A151AULL, 0x439E18B1B73474CBULL, 0xA45FD347593D1F9BULL, 0x448B8632F6F50EEEULL, 
            0x9B3D2C48595E82C1ULL, 0x44D04FD5F108D1E4ULL, 0xB00EEDEFE2A72F18ULL, 0x52BB6B40C1E40CEAULL, 
            0x6EA18E6C4C737010ULL, 0x103D510AB9F22D6DULL, 0xC2FD8B04560FE894ULL, 0xDF80A12435DC1AFCULL, 
            0xD107799A25591735ULL, 0x9289B3AA013A1437ULL, 0xD22E95D03CF7B569ULL, 0xE15BC1AE8CF7B5CFULL, 
            0x26639617BD690E56ULL, 0xC6F569FF4C38B892ULL, 0x67A1D4C9250ABEE3ULL, 0x07FF5442BF79E508ULL, 
            0x6E193493831C1EBAULL, 0x045453A1FD8CD81EULL, 0xFE74F2F781DE2272ULL, 0xF4DCFA45559DC93BULL
        },
        {
            0x77BE08BB588749EAULL, 0x6155E044992A6117ULL, 0x824D3D3BFA227DD1ULL, 0x14283A284A3C607EULL, 
            0xA8732C29B17A6903ULL, 0x92FF7218E788B519ULL, 0x00D5CBB88E536E9DULL, 0xBC518A13B8195AD4ULL, 
            0xE93F5DFDF11E5D7DULL, 0xA9F52F35FD2940D1ULL, 0x2EF3984FD604060EULL, 0x704ED9B57EF9A598ULL, 
            0x3C5F8AA858B888A8ULL, 0x2C8EE6CE10069647ULL, 0x5C133FEBCB79D6E7ULL, 0xD35CBF0042118C52ULL, 
            0xF5B2951AA7CC178BULL, 0xCAD2C7F3DA71E913ULL, 0xB780EDAF63167F3BULL, 0x36B2E8E57F14A120ULL, 
            0xC530E55BF6742A6FULL, 0x08222869240A1D41ULL, 0x82A9B8530515C2A4ULL, 0xAC2385E692B95A00ULL, 
            0xB6575B17A2C51960ULL, 0xE06F64980FF3CE21ULL, 0x22B32535328BAEE5ULL, 0xF3B8712D8EE2CA61ULL, 
            0x68A6C604006F0E51ULL, 0x66C25B067E06EC91ULL, 0x6B7080EC8C9F84EEULL, 0xABDFFA93A41C07DAULL
        },
        {
            0xA142F759E7A71D71ULL, 0x5A7E2B4DC8F004AEULL, 0x42E064A2C90F7F90ULL, 0x9E8D83FD6C5561ADULL, 
            0x928BD26BD5F21A72ULL, 0xA146A23FFF0502B1ULL, 0xDAF16F6C8D035112ULL, 0x7F9B929848C58EBCULL, 
            0x8177B6C8F088CEEAULL, 0x49004917F05CFAE2ULL, 0xAE397C061F3B94D8ULL, 0x8329E50FAE277466ULL, 
            0x9535D035DEBCEE22ULL, 0x5719A944AAB68ED6ULL, 0xC82998BF2F07E092ULL, 0xA6BD5C4815D182D3ULL, 
            0x8EB7537F3A687EBAULL, 0xBC769AB6D62FED04ULL, 0x2CFA696D0113C505ULL, 0x385BE6423F133D3BULL, 
            0xEC8ED65D2F6912BEULL, 0xD9D421FA26614E59ULL, 0x822B7DC9762B1A9EULL, 0x42DEDD2319445242ULL, 
            0x9A4ADB83AB3F1FC0ULL, 0x4AB6AD2E79ACB8B1ULL, 0x2E1F36E1D8C91E1DULL, 0xC9BCDB5E0A90E553ULL, 
            0x5DEC3AA759A1560CULL, 0x8267CD5FA36A4C49ULL, 0x058AA267C9750AB9ULL, 0xA5D710F8FA267708ULL
        },
        {
            0x3284F0591C6E1673ULL, 0xF4BF489E68E26482ULL, 0x5B7C3CF8640C9540ULL, 0x9DE7096A818B20EFULL, 
            0x374C57D6BB138F11ULL, 0x009E366D1C816F84ULL, 0xDEB47DF9094E10D6ULL, 0x5F9C2954D59F668BULL, 
            0x720375AA9E6E58CFULL, 0xFAEAC4484A7E0E1AULL, 0x30D471B28383A697ULL, 0x0A5E0ED4F3F401D3ULL, 
            0xB8924E173A6FCF54ULL, 0xCFD3F2650058BB5BULL, 0xEF095CA61A232BC0ULL, 0x0C303097B2206E63ULL, 
            0xB81C232B79EEBEEEULL, 0xCD35236E76345649ULL, 0x45D1ED8C27E87798ULL, 0x2DF2B24D92390D0EULL, 
            0xB0FB6E9DA1C57E97ULL, 0x89450A6E0CCC463CULL, 0x0800039ECCBC2084ULL, 0x95088ADEC8EACB4EULL, 
            0xFEF29D8AEB460E8AULL, 0x243E0A6A28397453ULL, 0xB475A1C536AD9A84ULL, 0xDC08FA9D33C92ED3ULL, 
            0xB56237762D32D652ULL, 0x2C4D3121283AA4ADULL, 0xE5E80F8FC5B74F06ULL, 0x63CDDFFA0FE4DC86ULL
        },
        {
            0xEE4EAE360F017C57ULL, 0xE2457823C4501007ULL, 0xB4E9C4D057DC992CULL, 0xAEC3EF5E74ADC40BULL, 
            0x596559369C062186ULL, 0x557BED7178CDE9D5ULL, 0x400C0BF16F4C4F64ULL, 0x5F7FA35C8EEEE916ULL, 
            0x6B00164331D0194BULL, 0x9D4E7A823403CFCDULL, 0x88D7137A3AE327B5ULL, 0xF005D1BFACFC931BULL, 
            0x988FD1EA51C57BFCULL, 0x312019DA7935A166ULL, 0xE2B0DC27579A6825ULL, 0xC1D35C58EA3D1208ULL, 
            0xCA89ABC2E5691AD5ULL, 0x763769633C86826FULL, 0xD22436E968B7CDEAULL, 0xE7CA24993B99029AULL, 
            0x5042D06B30A12F1EULL, 0x81BD2D4BC4E96C2AULL, 0x686C032CE5BF7482ULL, 0x7D277FA288B2090CULL, 
            0xEB7162AA980716FEULL, 0x11764A732190DE77ULL, 0xAEE0A17F3B94FD67ULL, 0x530214F66FC0B2AEULL, 
            0x23A2507EB3182EC7ULL, 0x32CDF285B2FDE9EDULL, 0x007890DEBBF7AAFFULL, 0xF9A4546DCEFDF795ULL
        },
        {
            0xF1DDA28E14D9C428ULL, 0xAF846245AB2F877CULL, 0xB11235087AD88DA2ULL, 0x216526090028241AULL, 
            0x48372B51ACC85B06ULL, 0x85FD71A77CC3ABEDULL, 0x8BE0D030A8A0C9F2ULL, 0xAC432CA18B0FE51AULL, 
            0x0AF0D8DF8E23C477ULL, 0x48D31BB75E775534ULL, 0xC55CC07A1122C990ULL, 0xDAF7BDC67BAC8803ULL, 
            0xCD7C5D568EBA01BDULL, 0x5FA5C3BA54958BA8ULL, 0x22150A4D4A31022CULL, 0xCC1D5590AF069344ULL, 
            0x66AF26EF2FCFEC83ULL, 0x3A26B5D3A67F419EULL, 0x4E7237F27D111D7DULL, 0xE0DCCB972CFF3A2BULL, 
            0x83B0CA6C46108074ULL, 0x5F7EA874FC3B4147ULL, 0x438AFAFB00498623ULL, 0xB0B0DDD3A405773FULL, 
            0xC76A65A9ADCBC01CULL, 0x959F63BD50DE6B6CULL, 0x5653659A2B07B970ULL, 0x3700468C68C5EC2CULL, 
            0x3109B40D40B30D60ULL, 0x52E61D4B1769E7B3ULL, 0x9F650D6EF45A0AF1ULL, 0x9ED0B836AD4B52DFULL
        }
    },
    {
        {
            0xAE64595688BF1DE1ULL, 0xEEFB9FBEB7242667ULL, 0x0FF1356B98000198ULL, 0x6C0DA8BD70489758ULL, 
            0x15707AB9958C808FULL, 0x60F87DDEF227CF2BULL, 0xDF629AAC2B7EDD69ULL, 0x289CC239483C560CULL, 
            0xEFE5E5CE3CB1AFA7ULL, 0xCE6D4E6622D81710ULL, 0x75C51A58D5258E6AULL, 0x96334B1B5D781BC4ULL, 
            0xCC7BDCD9860A5C16ULL, 0x9310C4317BC7F1F7ULL, 0x3B8E1780272D7838ULL, 0xE70A97B990431591ULL, 
            0x0291BE3A7D5FF818ULL, 0x66180E546746C643ULL, 0x323F63FAE0E3A4AAULL, 0x54CB5588558974CAULL, 
            0x1C5F9BF8A1904744ULL, 0x86F438A9857E3435ULL, 0xC59C313F5554B3D3ULL, 0xD4607EC5E0B547C9ULL, 
            0x4F06B20F2E0358F0ULL, 0x799ACF5A4F3857B6ULL, 0x09AF40171766952EULL, 0x16593FC7FC844B32ULL, 
            0xD98C545F3F76F12BULL, 0xC79B78CECD6D457EULL, 0xF7927B6CD86D9DE1ULL, 0x05A00D23E2814678ULL
        },
        {
            0xD2B0FE48572AAB40ULL, 0x1A063A2B8F619A49ULL, 0xE13BD60D9D922980ULL, 0x4167D392744C40F3ULL, 
            0xDE1FD932022D666DULL, 0x5CA26D5366126486ULL, 0x9C865FF8098148CFULL, 0x71D579F816AA6D6BULL, 
            0xA10636A81AE7AC23ULL, 0x9E7D01633569216BULL, 0x2F7C321941B918C0ULL, 0x16DE23A40E2D55E7ULL, 
            0x370841E905E8B653ULL, 0xDBB3F40AF04B648EULL, 0x5ED6F5E79DA953F4ULL, 0x88C8F07D4D92C703ULL, 
            0xD900659E0951973DULL, 0xC4DF239F104EDFFFULL, 0x5B66AC75D5CB46CAULL, 0x473F12781909BB6FULL, 
            0x316D45424180CB34ULL, 0xC59CBCE2DABDA6B4ULL, 0x8E3A9DB2A37CB971ULL, 0xA1CF931B5FB7AE64ULL, 
            0x3904997F07586A3DULL, 0x3B584E561715A1F4ULL, 0x083BBF16B06FECCBULL, 0xF422F581EABCCD5BULL, 
            0xF5957DD318366C48ULL, 0x20F801584C604FAAULL, 0x8A699B7DC4474F96ULL, 0x21E06DBC4EB20362ULL
        },
        {
            0x347364F01B88AD9CULL, 0xF190D557D8126363ULL, 0xDA5CA0DD17EF6DBAULL, 0x2A4DD01E49686C92ULL, 
            0x4947975C0E3C361DULL, 0x2EDDBBDA1CE1B5DBULL, 0x1BD78A0F6C415931ULL, 0x9165F8ACC7A4079EULL, 
            0xA820C574F1DB6A9CULL, 0xC62DD298FDACF39CULL, 0xAAB6F991C9870616ULL, 0x9536A60147913D11ULL, 
            0x78445069C38EB019ULL, 0x4BA724D97BA2215CULL, 0x1DD1A23222C399E1ULL, 0x32AC94D35F9F10D0ULL, 
            0xB82DB923F68687B1ULL, 0xF1578713DF37DD20ULL, 0x31BB998382B0F7C5ULL, 0xC74FDF6FD55DE259ULL, 
            0x4FF95143FCD97F86ULL, 0x7B0338DB49E4AAA7ULL, 0x37108A7EC9EE9AA8ULL, 0x4D0722CD711CEC4AULL, 
            0x65B510547E177026ULL, 0x1F0370098A9E9A63ULL, 0x94FA66191BCAD42AULL, 0x605E68EE9CC245EBULL, 
            0xCEBCC7502CCF1AB0ULL, 0xF38611B95D860D83ULL, 0xE21687B625C9894EULL, 0xFD7F2222BBB9C14DULL
        },
        {
            0x11C0379532526CBAULL, 0xEAC5636056F8BD7DULL, 0xEA98E17624ED9088ULL, 0xBB5B3B58BFEBC60FULL, 
            0x4843440B0EF71461ULL, 0x6B9720934E14A861ULL, 0x619D6E007B8E1322ULL, 0xCF8C8C0E4B3D5AA1ULL, 
            0x181D223F2D1226ADULL, 0x25657B95460E918BULL, 0xD6725EAE3D38921BULL, 0xFBA8F88D28470CEAULL, 
            0x6EB922839BB7FD99ULL, 0x17254E6D70897504ULL, 0x260B947E7EE92614ULL, 0xF1BAA1E77B9832A2ULL, 
            0xC08F6E6450B6E253ULL, 0xD7675738BC8498AFULL, 0xF39CA221FAF15500ULL, 0x7619BEB989843E9DULL, 
            0x2BF91766C3463F02ULL, 0x98A32DAA778E7C29ULL, 0xB995C6244D4DFFEEULL, 0xCC06E064B2CAFFBFULL, 
            0x6863A272FAE89F54ULL, 0x8CAEF3D906521F30ULL, 0xED0C3F524750FCD1ULL, 0xF117771E06824860ULL, 
            0xF89EA74F6BF94DAEULL, 0xD48F3FDE0690FC39ULL, 0x272F8B860FAA6CA7ULL, 0x06AA04EEF55CEEB1ULL
        },
        {
            0x9BDDEFE5C6ADE035ULL, 0x7BEFF1FFB724626FULL, 0x56BC3BE7B1063944ULL, 0x17E76DDEB90F7E4AULL, 
            0x428F3962EECD15C0ULL, 0x2A92A431F90BEBB9ULL, 0xEE7C01A032E2A595ULL, 0x0F332BA99CD5168AULL, 
            0x3C25320F405B7595ULL, 0xB2407DF8CB63C201ULL, 0x404946FF3277C414ULL, 0xC7F6DB0A029DD5D6ULL, 
            0x38C207374AC65E65ULL, 0xCB2E3E61F1B0D977ULL, 0xCE22006FD32B6C85ULL, 0x5C0FE96967F8C35CULL, 
            0xC5CC704FDF087B60ULL, 0xD12EFD9437F7457CULL, 0x4945546FA4AA38CCULL, 0x78F2BA18C32249B3ULL, 
            0x7D2C2A58C0ECD5BDULL, 0xF132B3EEAE214E17ULL, 0xC7EA4AFA23AB901FULL, 0x439BFDCA1A9156CFULL, 
            0x503DE1A764429C4AULL, 0x48EF0E84114CD8DCULL, 0xEDDFCFB460E03E7EULL, 0x2173623E53F6A0AFULL, 
            0xCCBB809C577459F9ULL, 0x2B1A4839CEF78358ULL, 0x779F62E0DD1A8133ULL, 0xE2805102AA7C8987ULL
        },
        {
            0xED12DDF8811839EEULL, 0xF0C34E522634FF05ULL, 0xA2465A4AB6EA031CULL, 0x5D30DCE80DB94763ULL, 
            0x686CFB26AD4C3FF2ULL, 0x7BB9E898463E268BULL, 0x49F86F02ED2AB9B2ULL, 0xAD5072EEEC420756ULL, 
            0x6ABB6B54E792DFBBULL, 0x06034A69C3C0AABFULL, 0xF71BE67B6480A617ULL, 0xF98EF2D977A33F4AULL, 
            0x768633ABF2D1228FULL, 0xD8E95C43F7FE98AEULL, 0x6FD4E1DAC45A1191ULL, 0x1B7E47FA40993314ULL, 
            0x1A8BBD77044F017BULL, 0x1C1AC36E313AA057ULL, 0x0F3661C843D2F28DULL, 0x46D50BF447FFF2D4ULL, 
            0xD4D72F56F446B80EULL, 0x05F19437D6A41B21ULL, 0xC3A00E4F46FBBC7BULL, 0xA7617F206E9BD353ULL, 
            0x50D22C49183A3098ULL, 0x0550F9D623B4443FULL, 0x899F516C43EFF976ULL, 0x87876B340299E50BULL, 
            0x4E82D4121B159F0DULL, 0x4C33E0B312CB7740ULL, 0x040DA63FE21D5768ULL, 0xD912BC57937590A4ULL
        }
    },
    {
        {
            0x3038F6F8B4A5C71DULL, 0xE374939EB730CD6FULL, 0xAD49BE7C078EF35DULL, 0x0A9A0F45589F3520ULL, 
            0xE70F6D9C50F16245ULL, 0x1004F41AD38869E2ULL, 0x8825C778F6AAD7BAULL, 0x7128F08BBD0DE11BULL, 
            0x6F06776711E87C05ULL, 0x4F4E3776B7F47B5CULL, 0xFEC0166D124F7897ULL, 0x2BC2E0ED3CCB5A7FULL, 
            0x2DCB2A489FB46087ULL, 0xA990BFEC3B6CEC28ULL, 0xC7A4EB8F1CF023D3ULL, 0x6F7BEF9A6FFCF644ULL, 
            0x04972DF08F3C9C9BULL, 0xFCD26EA38DC8D830ULL, 0xC5EEC9D43CCE3E8BULL, 0xDF760435FE7BE069ULL, 
            0x2781CD3F241719D5ULL, 0x2D1EC3BEAB6DBCA2ULL, 0x42997313FB1F0F28ULL, 0x7276E2D37B3F7306ULL, 
            0xFCCC6D986F1E2B8AULL, 0x01A3673501B47471ULL, 0x69F143CD7B375192ULL, 0x7CE25069AA13A6BBULL, 
            0x1A44DE5126D557B3ULL, 0xC80D34DBCCAD3965ULL, 0x312C348FDE316159ULL, 0x1C4E37BAFB63BDD7ULL
        },
        {
            0x36C63D27FDE78DF7ULL, 0x83F0835633090A54ULL, 0x4DC3228B7C10217CULL, 0xA85AB54E9FE3DA0AULL, 
            0xF7FFD341D070968FULL, 0x840C595CFC5C4606ULL, 0x07C6E95D1AAE0546ULL, 0xCDE62E6E66C5767EULL, 
            0xE17B19E4856BE98AULL, 0x5B9D5FE39893ECDEULL, 0x28961B8C4ADF8DC6ULL, 0x1C9430CE72C5C526ULL, 
            0x93CB7DACCCD2BDD2ULL, 0x758702B9BDA6EF4CULL, 0xF7CBA64A2BBECEF1ULL, 0xD1798374B3A3A93AULL, 
            0x2A908B7D27D7631EULL, 0x6611E41057E6F95EULL, 0x2BE5D8307C7319BEULL, 0x21A0D2CF57C54716ULL, 
            0x09965B30068A59E7ULL, 0x532DE34C843438ACULL, 0x51E60D7D4F5AE6CCULL, 0x3C628D11ACDB15BAULL, 
            0x39054B42BE01865AULL, 0x70A72ED49995BC54ULL, 0xC89EA1E7812AEB4DULL, 0x82E6C6D9C6D42056ULL, 
            0x0AD6C4E3AF992764ULL, 0xA9A58969DD708554ULL, 0x5C9FE9E75E2D4585ULL, 0x86235B554E75A0E7ULL
        },
        {
            0x202BCE49A99DE19CULL, 0x287AB4C6B1D9CAEBULL, 0x6346E107BE2C14BFULL, 0xD40EFECD5FEE5EF5ULL, 
            0xF21A691BE8AB486EULL, 0xFAD98299A577C3C9ULL, 0x3E200A1DE7B3B49CULL, 0xFF9217DFD8171916ULL, 
            0xEFC99B2B434E5719ULL, 0x8F2C787D9F9E04DBULL, 0xB83D51BE38584A4AULL, 0x4A52DAAB668543C6ULL, 
            0xE4ACD4569FF527A7ULL, 0x9ED517DBF6E5642CULL, 0xA673567161747138ULL, 0x0FB238E28CF96D78ULL, 
            0xC46D3EEB715D3FFDULL, 0x778A53CE8690B8C3ULL, 0x3A871BDFBC7D55C5ULL, 0x220C13AAD20C9110ULL, 
            0xF26CBC2196704883ULL, 0x04BC8EDCB67C4A3EULL, 0x3F391A6431F89BD4ULL, 0xACC2B3EBD9441F40ULL, 
            0x30D8F89861A4E135ULL, 0xAE5F1EBF2BDE8E1DULL, 0x0B8F6F57FF370758ULL, 0x5DB52DD6DD3459C1ULL, 
            0xC2EE5AA3C37B1FF0ULL, 0x946B2E9D69A3F31EULL, 0xCC7074BE869C642FULL, 0xC65AD0B3410860B5ULL
        },
        {
            0x6AF2D5130DF3949FULL, 0xAFC77D6A027B26B1ULL, 0x85723DA4A2E5D7BEULL, 0x91D3A0EC919E4D8CULL, 
            0xED7135147406DFB3ULL, 0x362A91326A9F60A5ULL, 0x6C1E49954D45FC24ULL, 0x4323B8E100EB8207ULL, 
            0xCEEEABD5BA22EA26ULL, 0x32613F15E2ADB882ULL, 0x56EBCC514A363923ULL, 0xB2D0A7D5EC7215AAULL, 
            0xA117D5CF18470B18ULL, 0x23453B7E9AD337E2ULL, 0x2D0D9821E38E2F01ULL, 0x25828463E66A58A2ULL, 
            0x958C0A0F577BCD54ULL, 0x8A83BEA7DC09EF33ULL, 0x1BEA09013880786BULL, 0x2B266F15DE3E729BULL, 
            0x5DAFB12685223FC1ULL, 0x29B3072B342EC652ULL, 0x7E43DECC760D9F91ULL, 0xA00E3DCC5F1C0080ULL, 
            0xB0AA6BBD789E7619ULL, 0x09B4FC04B3969E7EULL, 0x95871C64653AAA13ULL, 0x00BBC44F7DE682F7ULL, 
            0xEB223E17C3390566ULL, 0xE3F341CB2AFA42E1ULL, 0x766F54C55516948AULL, 0x3444B3F29E986751ULL
        },
        {
            0xBB11E462FE2B67BDULL, 0x87D910DBC5FB9408ULL, 0x7B49715F99C8745BULL, 0x0F7B384165DFB85CULL, 
            0x993539AECBA7B7D0ULL, 0x5BE8C9A83ACF8268ULL, 0x89939836D99A29DFULL, 0x9BA12C3C30F85E7BULL, 
            0xA1EBB473E9EE5C61ULL, 0xAFE86B8A50C19653ULL, 0xB1043CDA1521AD64ULL, 0x3198CC61C70371A4ULL, 
            0x8E4A04E20833F1A0ULL, 0x45EA970E49312D18ULL, 0xBEECB5F47FBF7A84ULL, 0x3A99CB7BFA356E11ULL, 
            0x6B325E489FA8F0B5ULL, 0x45758BAE383CF206ULL, 0xABF4B63B0D776C52ULL, 0x6A70FEC72AC0C889ULL, 
            0x5B298EDBA1283017ULL, 0x325D1CFE5B6B5848ULL, 0xD9A9D73871356A76ULL, 0x099CB169FFC39301ULL, 
            0x8468DB0561C8657EULL, 0x24BE53863B219F10ULL, 0x327E03F9786CB67CULL, 0x29B16AD6AA8C0913ULL, 
            0xB3A018023E70E0EDULL, 0xD48F0C8E3F7E55CDULL, 0x768595DF75A83F32ULL, 0x5AB1D011B78A8D66ULL
        },
        {
            0x4536005000B77BBEULL, 0x4504DC50B71C25E8ULL, 0x9A9C927E0DAE205FULL, 0x2A8354A51CC8495DULL, 
            0xFB3D9CDB7891DE38ULL, 0x338FD61CC529832EULL, 0x8DB85051086C65EAULL, 0x304B27ACD60D8F9EULL, 
            0x21328E203BA1F64EULL, 0x80F854EFFB9E3C77ULL, 0xB4A85F5AEE1AD516ULL, 0x98FD3F4A2311164FULL, 
            0x48566EE12CFDD90FULL, 0x0133BDF45BFDEB3CULL, 0x6B96E3BE852E779CULL, 0x84E717E7F01B4C70ULL, 
            0x8FC1BF4E1271FA64ULL, 0x7B0091991B0BB1B6ULL, 0x7631D9C60E41792EULL, 0xAADDA4A7F9712269ULL, 
            0x9CB981324F9DC220ULL, 0xC60BB4812F0A045FULL, 0xC54BA632C76E1ED9ULL, 0x468042313116760EULL, 
            0x78A0039BD3560D72ULL, 0x677A2F08B0F2CE32ULL, 0x11DAB92380A80662ULL, 0x2432417343A42CA6ULL, 
            0xB6CB3205F2C16AF9ULL, 0xBB16D67855C978A0ULL, 0x90C5FE7896178738ULL, 0x90CFF105F4CC62E2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseDConstants = {
    0xC9C37EA1135BDE98ULL,
    0x2F0F1990DD933A3AULL,
    0x1FBB9A1A9829733EULL,
    0xC9C37EA1135BDE98ULL,
    0x2F0F1990DD933A3AULL,
    0x1FBB9A1A9829733EULL,
    0xC70669D464A7EC98ULL,
    0x4ED1342B4EC41C49ULL,
    0x4C,
    0xCE,
    0x6F,
    0x04,
    0x63,
    0x93,
    0x52,
    0xBD
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseESalts = {
    {
        {
            0xF43802F9334F327BULL, 0x49FA0CA94D666021ULL, 0xD56628E8CF00D81AULL, 0x8DD9726DE27FC674ULL, 
            0x64F23FF6D45CB25FULL, 0x3916ED4F2B7B8854ULL, 0x886BDEC2CF12B866ULL, 0xD475E7A61665EBE6ULL, 
            0xFCB93448ED907C71ULL, 0x2735460D1B4B8F01ULL, 0xB4A7509000D9B5DBULL, 0xD86285C1B52EB90EULL, 
            0xCE2E6AD8FC35CE9EULL, 0x62A37C132737DF9AULL, 0xC67BAD0D12AABB90ULL, 0x0CF8DA489DFA27B9ULL, 
            0xE4399735DFE57D94ULL, 0x7AA7323FDE973462ULL, 0xD0432A2B8C26975EULL, 0x990AC55523B20969ULL, 
            0x96CB33D891941030ULL, 0x1613935141F756A7ULL, 0x23C3A44357EC5045ULL, 0xC66A0F604670BDF9ULL, 
            0x459C69FB98E12B12ULL, 0x1B3E31D514CDE8E5ULL, 0x26190466A43FA7EEULL, 0xA4317D0B104A5761ULL, 
            0x01B3331190979F9FULL, 0xA604E5C366654F91ULL, 0xDBC6D4C2C566F171ULL, 0x86064F2685D6C0BBULL
        },
        {
            0x2D7C8C8B3DBC9792ULL, 0x81A9FB4967249D19ULL, 0xE4BD44A4E5BC78BCULL, 0x996857A1A9FDB191ULL, 
            0xCD491E3FBB719335ULL, 0xE07B8A340A9DD92CULL, 0x7E6A72D7E5D14207ULL, 0xD7A27703E1438DDBULL, 
            0xE4C0B07DE71C9788ULL, 0xB960E72C77BE793FULL, 0xFC7FA42E41E5640BULL, 0xE42F6F9090262D0DULL, 
            0x10A13A606A3E6A28ULL, 0x2C0C3E4746578C3CULL, 0xC818D4D95704E916ULL, 0x83019928DA8E5240ULL, 
            0xEDCB78D34C6AB7FEULL, 0x8D2C618ACE526232ULL, 0x5444A80691E64AAEULL, 0xE24EFD599D210806ULL, 
            0xE90E24B4DD2B8DFBULL, 0xA0EFE8B13C6B424DULL, 0x08535F2B314602F5ULL, 0x953EC76AC8D70777ULL, 
            0x57F0C11323676FDDULL, 0x69CD0E2DD0ACB6F0ULL, 0x837011B46C1AA022ULL, 0xF781A662D994368DULL, 
            0xEFEDE9DBD14031AAULL, 0x9E212A50059C6E99ULL, 0x457F163A7BDF00FAULL, 0xAE44907169AB8708ULL
        },
        {
            0x12EA5C333A2B3169ULL, 0x27336B0E1043337FULL, 0xD0C2760F5648681EULL, 0x42DD81A0ACD9184DULL, 
            0xE92ED6BE3EA08B93ULL, 0xB2C20547A2012056ULL, 0xE15A405FF3893B71ULL, 0xE01DF2C68A5EE810ULL, 
            0x506766052E1D21EDULL, 0xCA2F84C0DC606C57ULL, 0xA9EA0E2B6367C8DDULL, 0x7568C40E10CA3473ULL, 
            0x0386B666EFE1A57FULL, 0x2620555F87B64CA2ULL, 0xF69B18EE8F366778ULL, 0x91C55991BED532B8ULL, 
            0xB9EEBC4E54488DC7ULL, 0x6AA300BD7580EF92ULL, 0xC130598305299875ULL, 0xBD16521017D6244EULL, 
            0x6D07C0685C8F63C1ULL, 0x334D172507A1F95AULL, 0x720843313EDE0E70ULL, 0xEF65C1081BEB9DB4ULL, 
            0x58A4A72BFC3F8EA1ULL, 0x1EFEF59EB8F22EF3ULL, 0xB9A7A14244DD24E8ULL, 0x100058D6A6C07399ULL, 
            0x05F67C3DE2E9BF14ULL, 0x78CD719E0964906AULL, 0xBCD534382D3117D9ULL, 0x9A135E631C976337ULL
        },
        {
            0xFBE69637B1084C11ULL, 0xD287BA9F9FE85BD0ULL, 0xE9C6D7708E2C6FC1ULL, 0xDD4885AEB803C29EULL, 
            0x43B3865CFEDCE459ULL, 0x008348B1878748C1ULL, 0x6A5BDC11896FFF24ULL, 0x8EFC4D9CA4C0168EULL, 
            0xD0D2F9EC3CB951F8ULL, 0xB0523994B4DD3664ULL, 0x3DFEF345676791D7ULL, 0xDCE88C5469832FB1ULL, 
            0x92432F0E6B7AF2D9ULL, 0x359885FC07F2FFB5ULL, 0x6B26F617AA6FCB9BULL, 0x47938344867036C4ULL, 
            0x3239CEC808B32CB9ULL, 0xBA2B8E0014BB6CEBULL, 0xD5877152590F4036ULL, 0x70196E60553E217FULL, 
            0xF018046CCA86BCBDULL, 0xCAADA8104534D5D2ULL, 0xB830B96608E3265EULL, 0xD18349EC85D2C65FULL, 
            0x253EDA5040DC8BE9ULL, 0xB14EA580B30DE25AULL, 0xE5B2955CFC6160B7ULL, 0x5FB51E0AB97155FEULL, 
            0x36B2003974BAE806ULL, 0x723550D7D1196786ULL, 0x1F195CA283C56280ULL, 0xDA76D29C22D0A59FULL
        },
        {
            0x76E05F9151581A43ULL, 0xACCDE7969B73D3B1ULL, 0xC7275957F0DD5A8FULL, 0xC3755B5E77CBA1A3ULL, 
            0x66A6CFABA03EF6CCULL, 0xD2DF9E8C2707E618ULL, 0x02D44E63194E9533ULL, 0x457D280357F3E669ULL, 
            0xE53A1A6CD4D1DA1BULL, 0x1DD28C970F0C9F7EULL, 0xDD01F4C0BD28D1B7ULL, 0x6BAAC12E51EAA415ULL, 
            0x3D52996F35A0B312ULL, 0xF1BC7AAAC1249F54ULL, 0x276E990D0F67220EULL, 0xF4193CBEE0088632ULL, 
            0xC7BF9E79089CDA49ULL, 0xFA1FB977B9B82262ULL, 0x6FF4CC51DC77302DULL, 0xFA063A32D9F014F6ULL, 
            0x4DC594CDA6D4A62FULL, 0x5886BB58348A5CF4ULL, 0x3AA43EFEFB1EEE22ULL, 0x4ADC07C5C49EDDBEULL, 
            0x6B1897F3C521CA31ULL, 0x955D2DED451403D6ULL, 0x5591B5CA75F251EDULL, 0xF8AD9812257B1EAAULL, 
            0x7F356AD2F0B8A53FULL, 0x24823CEB67EE7D02ULL, 0x563271388C14E12FULL, 0x5E94C7C56CDE00F9ULL
        },
        {
            0xE3D2CF54FCC6A414ULL, 0xAF08D39AE6D46208ULL, 0x420D1758D570838CULL, 0xAB0877BC1E4F1F90ULL, 
            0xD0A0C5873AE7AC26ULL, 0x8BC335C3E862661FULL, 0x9590017EED759358ULL, 0x38FFEBB6EED73B7CULL, 
            0xE1F3860030134582ULL, 0x678F8AD74C967BCDULL, 0xB7B30D9DF34FAD6BULL, 0xDB031F2013ED6435ULL, 
            0x0BFD33824505A801ULL, 0xC1908E19E947EF44ULL, 0x7A74433BB0FBB9B5ULL, 0xFD3F830519A62800ULL, 
            0xFBB2FCD4F1F3C8F8ULL, 0xE4DD1FD3C18ED822ULL, 0xE7B663C6CBB5ABFDULL, 0xA93F918A2815EE19ULL, 
            0x65DA8554266ED802ULL, 0x6ABC358EB995223BULL, 0x14741AFFB30C0933ULL, 0x78E6F6355A14701CULL, 
            0x4F1CF38AF53BB621ULL, 0xDE15E525C691E45EULL, 0x3DF7D69773ABCD0DULL, 0xEAC12EAA9DF1EBFBULL, 
            0x890F59EB06997B57ULL, 0xEB47E382BAA2ED88ULL, 0x5B0106E360FAFD2DULL, 0xB306ECAF3C10BEACULL
        }
    },
    {
        {
            0x711E12217A7C6D16ULL, 0x3F27962A62F46A4DULL, 0x856D3785635EA1C0ULL, 0x7A3976739208B575ULL, 
            0x98DEF2D146423A46ULL, 0x8C5C82ABDA0AA9AFULL, 0x3AE062B06836C438ULL, 0x9471C63239BE3914ULL, 
            0xF76F3955E550F30FULL, 0x617A5568A0DE0F4FULL, 0x22B8C26CBAEB96F8ULL, 0x1AA2EA594E531986ULL, 
            0x36CB60FB4A69CE44ULL, 0x6F1886CED28D0F41ULL, 0x44CC7B3ABFB47D24ULL, 0x6EB18C9374AD93D4ULL, 
            0x35DA0CD114493467ULL, 0x59E07B521AE4A60EULL, 0x51FEEC20FD37E084ULL, 0xA028FF1EE6FA1B9FULL, 
            0xFEFE95EF1AC61584ULL, 0x7C28AD4314204ABAULL, 0x369997DC5485B029ULL, 0xFEC709AC57146012ULL, 
            0xD1B22735495BD190ULL, 0x2ED36B1C6DE47018ULL, 0x4A16CE189C09D115ULL, 0x9152F7D96BCFA8EAULL, 
            0xCD8D905BAF19D870ULL, 0x07046DFA2C2A2F5DULL, 0x32FF303EDE39E980ULL, 0xE8DF4926B8DAA3C5ULL
        },
        {
            0xD8940E9CBF767A26ULL, 0xC2A0A432348CB6B7ULL, 0x636AE0C2F02736C8ULL, 0x9CCB39C2CD88F719ULL, 
            0x7E2E704E92C8D440ULL, 0x34D33A7920A89ECAULL, 0x147663A5214BF559ULL, 0xB6AC2AB671BB14F4ULL, 
            0xEE796B040CC0FCE4ULL, 0x5DD3F35460DCD952ULL, 0x409900D2D6F2D8CEULL, 0x14B6BE23ECFFA741ULL, 
            0x81D360C887A69849ULL, 0x90D0A8C3EB56E9A4ULL, 0x280330067485588BULL, 0xB976B21EAA111074ULL, 
            0xFB89B2ADF013D7B7ULL, 0x4E341A0AAA086053ULL, 0x429844FD432EB6C8ULL, 0xCEAF143D3BBC4F6DULL, 
            0x092EB750C1C3D78BULL, 0x4DFF84CA4F344158ULL, 0xF7F82A9E5E1E59EAULL, 0x137C64124E1CB9AEULL, 
            0xD15C95247977CADDULL, 0xD4BDAE78F722DD61ULL, 0x29BF927D0B2076A1ULL, 0x5B601480B609C23BULL, 
            0xAFE2F952C094C8BFULL, 0x5D87F1B4F6BBDB6FULL, 0x776056E04994CE01ULL, 0xA7DA3BD4BDD469C4ULL
        },
        {
            0x480C4ED4AF9B1BD2ULL, 0xD528FB7261CA6D16ULL, 0x022BE985AAD4EBA7ULL, 0x5CE0FB5C5F6FD759ULL, 
            0x4BDCDFCA87E1C794ULL, 0xE25F0EA4DB3EB5E9ULL, 0x079D600E5DDA53A5ULL, 0xD1E1E6A73C4CB8BDULL, 
            0x132CCFAD5BE1B8B4ULL, 0xF876BFCAA3E083A6ULL, 0x05272757F1D3DE55ULL, 0xD1665BD4842A6CFCULL, 
            0xF3FBCBF3B81C6080ULL, 0xA2E516702BF1242BULL, 0xA010015F643CFE74ULL, 0x636C011AC55C9B36ULL, 
            0x4B44D94D03CBADBAULL, 0x1DD5C8355F579650ULL, 0x58107962AE327A4AULL, 0x3C61BCC9DC528F23ULL, 
            0xE187AF8012C36464ULL, 0x5CF73784825BED1DULL, 0x75854840294348AAULL, 0x03933D84B9C04FB0ULL, 
            0xB4AE774C9E0245CCULL, 0xF68A292FBBDE7747ULL, 0xA73973B42265806AULL, 0x701BB55B39E735EDULL, 
            0x366FFECCE32E00BBULL, 0x59EAE2F9834A228BULL, 0x923E6466768DFD4DULL, 0x170156A96EBAFD3BULL
        },
        {
            0x004D4303638D53FBULL, 0x5D9A9C1F036A42DFULL, 0xEDF2ED1A2734A414ULL, 0xC74AC6A1C0682B3FULL, 
            0xFFB6B906BF3B0D2DULL, 0x870B1CAF43C5F5B1ULL, 0xB9B9B0D635205871ULL, 0xF495AA1BF2F28686ULL, 
            0xC18D4AAF12135631ULL, 0xD34843159EED2AA5ULL, 0xC1B1DD2FE48DC66AULL, 0x6AA430DC6CAA2727ULL, 
            0x46A2D4CD57C1BEC4ULL, 0xB812871BC1794B63ULL, 0x7C57D3C333B9148AULL, 0x70BA069635E45B65ULL, 
            0xEFB1364776BB4766ULL, 0x67EF5F5B827C1CA1ULL, 0xCC22F36FD3027ECBULL, 0xE254163642E9FAE7ULL, 
            0x809BFE92F28D4682ULL, 0x2B348C538305E5D0ULL, 0x94A7C6E82A71E385ULL, 0xD416B4840FFD10EAULL, 
            0xFF6BD19C03C0C4E9ULL, 0xC1772C49A2B2D89FULL, 0xBBC0333046816EE4ULL, 0x61925665474FE67BULL, 
            0x28955EF9AE4EFECDULL, 0x4CC9F3ADDEE87B75ULL, 0x5A18081C477643C4ULL, 0x77938BFC7FB000D6ULL
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
        },
        {
            0xCA284AC0F320DE09ULL, 0xE68BA6E09D56A2DDULL, 0xBAE0E0FF218202F3ULL, 0x89E085133027B29BULL, 
            0x6981D1841F6CBC9CULL, 0x8C10374D855422B5ULL, 0xA4EBD6B13823C8EBULL, 0x833DC48D4AC34981ULL, 
            0xA2254EB6DE041051ULL, 0x52C57EBBC97A6284ULL, 0xB6ACF806EEDBFB2AULL, 0x466FB8AAE2FF696DULL, 
            0x7B8A2B149CD682B8ULL, 0xAAD4F48C23CBA4AEULL, 0xB00A46DBD7D5BFFBULL, 0x8C7CA0DDAA622CC4ULL, 
            0x2637EF6F4FE60C73ULL, 0x2FA3FACE00C10447ULL, 0x0066AB7AC3006163ULL, 0xD66054D917F320B4ULL, 
            0xCA3A1EBC11820E3BULL, 0xCAA6668031D7AF89ULL, 0x186EC471E1224E5EULL, 0x0EA058A8207B4B22ULL, 
            0x491453D67452AEEDULL, 0xDC8971A17BFA00AEULL, 0xE688C1CAFD3C5621ULL, 0xFF3BBCB09821AA47ULL, 
            0x2EC665CC20D2967EULL, 0xFA1CB26CC99F8A6BULL, 0xF3B33A738786D300ULL, 0xC592A0EC38F00BDBULL
        }
    },
    {
        {
            0xE4B1D257DB5884A1ULL, 0x150B8539656EABC8ULL, 0x22B567F3DA557F5DULL, 0x539386CEDBFB6AF8ULL, 
            0xC6F04048074A89CFULL, 0xE489532AAF6C9194ULL, 0xB8B01A36E58AA7E0ULL, 0xF328CF656E01275DULL, 
            0x88DBEB4BECCFE9CBULL, 0x6E8F30704EEAA7B1ULL, 0x38CC43B428AA516DULL, 0x60046F02C5998E2EULL, 
            0xD4BA1D470E5C295DULL, 0x25BB123B6F2B85EEULL, 0xA6FE70D3E10549EFULL, 0x73FAC5A0AC4E8ECDULL, 
            0xC3801F5A39804251ULL, 0xF1753823C06463DCULL, 0xD6CCE80AA3A82F1EULL, 0x3484DB6A44C2EFD0ULL, 
            0x4CD237F796B3BB45ULL, 0x47F736C3DEDBAF37ULL, 0x526CF2CE51704132ULL, 0xB8E149160B40D2E0ULL, 
            0x030ED572A999DDF9ULL, 0xB42CE4C2CA3BB2BAULL, 0xD453631851CD9B78ULL, 0xBDCC580977E32937ULL, 
            0x371660DC9CD85304ULL, 0x57FF149FD91AD83EULL, 0xADE677F6D2912E1AULL, 0xF80E3302CA858C7EULL
        },
        {
            0x030D783266A8EA60ULL, 0xD7D2178BF4D87E9AULL, 0x5F711171A6E9E745ULL, 0xBFD678CBB4A3A0DEULL, 
            0x969AFBBA54115D1FULL, 0xC88F40E0CA365C95ULL, 0x7D3F7FA799F5F37EULL, 0xFA1B926BBAEE892EULL, 
            0x2962C526D53ABD2CULL, 0xFBCF754EF0A6ABCBULL, 0x2D2547770BCD865AULL, 0xEFDF854A7DA7711DULL, 
            0x8CCE457CBA2CCB25ULL, 0x3AF76D63EC0DDE46ULL, 0x9C2BDB3044D388BAULL, 0xC94CFECE5F7EC764ULL, 
            0x9615914E164039EFULL, 0xDE98AE4726202B94ULL, 0xF23938B37C8066E0ULL, 0x5278168E626710EDULL, 
            0x6FFF9E824714A040ULL, 0x40FED3AAF0C70B09ULL, 0xD0975E01F8FDFEFCULL, 0xF9A8D323F61C5F90ULL, 
            0x4CEF2686BAD39EA0ULL, 0x21E4BE8756D93F34ULL, 0xA4F804D131CB045EULL, 0x7B0E23718A0C3A18ULL, 
            0xFBFB61A051A1DB4FULL, 0x60B9729FD05CA25EULL, 0xC5588B4B02122F17ULL, 0x10E303861A43BB1AULL
        },
        {
            0xB0E8297BD8062E97ULL, 0x3BDA0A95F89B4B17ULL, 0x3A7FEAF489C75B8DULL, 0x6A631EFF238B37CFULL, 
            0x7E183676C8C2AF24ULL, 0x4866EC5D606BEDA7ULL, 0x91FED7D1387A1053ULL, 0xA2B5C7FFCF43B5F9ULL, 
            0x7F434554AF4ED9BEULL, 0x0DB23E8D6C7C9036ULL, 0xCEBA1882D62D3510ULL, 0xD8D86E495784CF5CULL, 
            0xB82A97BD1797C0B0ULL, 0x8BC426438C19673CULL, 0x46364E848D298282ULL, 0xFB9EB7CBE15CC849ULL, 
            0x2177B7D85F7D6D5EULL, 0x44776A9C531156EEULL, 0xBA3AE4560ECDFB88ULL, 0x7C9F5F4951219FC8ULL, 
            0xE25C39438750D222ULL, 0x7C61AA670859CA18ULL, 0xA7DF3B3A123B0178ULL, 0x1B5B352119569A8AULL, 
            0x252760A974A6C5ADULL, 0xB38F6F452421A9A5ULL, 0x79F75219599AE65FULL, 0x4AC34619F795700AULL, 
            0x31C3D67EFDE0E936ULL, 0xD9727D0FE1C3F1D3ULL, 0xA15ADC4F2EB64ABDULL, 0x09700096C383BFF1ULL
        },
        {
            0x4D3276F087DA3EA5ULL, 0x95E8DB253F718867ULL, 0xABB3B0F47BF638AAULL, 0x430BA478B3058F95ULL, 
            0xFFA41B3D66B83FB9ULL, 0xDE1E5853081AAE56ULL, 0x8097DB7B819ECE60ULL, 0xA8F01E9FC799E919ULL, 
            0x92F7E72D9A8D5C95ULL, 0x07530EC657B1A1C7ULL, 0x3EC99B9D3A6CCE9DULL, 0x5F36F9A859BA2C4BULL, 
            0xA2A5986CAA13534FULL, 0xAE5A07642C3D4C57ULL, 0xFECD49E76AA3D0C2ULL, 0x2B4D11112BAFD1B3ULL, 
            0xE7A903FD37132936ULL, 0xB9D36EC0E0C1BF06ULL, 0x69A9347B4BA12366ULL, 0x0A1AC549AA6DC92CULL, 
            0x4A8E4E059013EE13ULL, 0x910FCD938A6D9D69ULL, 0x26802DA77D63814AULL, 0xB7EEC9C17BB10CACULL, 
            0xFE672EB0B4F8944BULL, 0x244550C18BAD5BE1ULL, 0x6BE165B55F3614A4ULL, 0x84EA2DABB5CF2832ULL, 
            0x2C96BBDFED4DCF11ULL, 0x984954B9F9C3A574ULL, 0x9CCCE3B2CF612B2BULL, 0x3A7C4139DBD1E9EDULL
        },
        {
            0xAF994969DD172ACDULL, 0xB6E08B46D76E13E0ULL, 0x19AA6F19AA9956C2ULL, 0x9DBEC20F5D5068A2ULL, 
            0xA0DE13A948986BF4ULL, 0x60E932D68656F742ULL, 0x9AAD17C152338B25ULL, 0xD07088AEAA19920AULL, 
            0x0AF613E47ACB065BULL, 0x80209FF93DA20A72ULL, 0x0423070D8331A9B5ULL, 0x262C33991B266989ULL, 
            0x0A5F344C730692EAULL, 0x016B297BC152B314ULL, 0xB43D78CFB4996195ULL, 0x0F093230E07F4C48ULL, 
            0x8601B90F4B83251BULL, 0x525FBFF9B3E62E7BULL, 0xD11DA0CAC9F4516EULL, 0xF4B432A37FC008ABULL, 
            0xADF2133195F4B349ULL, 0x0FD78DAF486B1510ULL, 0x6AEAA8C08E9CA032ULL, 0x81274DDB02E18BEEULL, 
            0xC2D25A2623D6EC54ULL, 0xFEB4EAA851EE0A62ULL, 0x307A171FA88CF4ADULL, 0x88642BDB7559AD88ULL, 
            0xA55CEBE208091F9DULL, 0xD1CF796463A9A12BULL, 0xBB3AE4DC6AEDEAD6ULL, 0x4396D0BB34A490F1ULL
        },
        {
            0xB861AAC53EB3B38FULL, 0x937884B3567672A3ULL, 0x43DD2F07A061A07DULL, 0xCB6DEFA06CC8902AULL, 
            0xB07E8C174631C45DULL, 0x0479A3DBB4C3E613ULL, 0xFF954AEFF12B56E9ULL, 0xA8697C243282CBA1ULL, 
            0x92AD7EDE4A4AE6CDULL, 0x56A77F495D0EA2BBULL, 0x9C6C43F3F7EAA8BEULL, 0x7368E1F65E8F3EE9ULL, 
            0xDCDEB580695F44CFULL, 0x7FAAE59813BAA5B8ULL, 0xAB18E939B0C835CDULL, 0x6B6C227E3F26D4ABULL, 
            0x90C4A9EC24188EE2ULL, 0xDCF839895FF94917ULL, 0x2CE00D3B15922479ULL, 0xA8695601EA9A06C3ULL, 
            0x171AD81C78554363ULL, 0x9432DBFE32BADA8DULL, 0xDFBD3DAF28D29F67ULL, 0xC5E3DAAC2A6688ABULL, 
            0x2AEEE09C9086CDF8ULL, 0xDBCD157736A7A94BULL, 0x7549A324B1D9032AULL, 0xB6E6705E9B3309D1ULL, 
            0x6158771B64A9B1BAULL, 0x2773E9730D5E52A8ULL, 0x62A275226B5B03E5ULL, 0xD28D8A81BD99EB5AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseEConstants = {
    0xAB29A165221657FAULL,
    0xCC80C08278EE1543ULL,
    0x412990D7483A67BAULL,
    0xAB29A165221657FAULL,
    0xCC80C08278EE1543ULL,
    0x412990D7483A67BAULL,
    0xC402696E8AD57EF2ULL,
    0xCDA0E7E2B1FACD9EULL,
    0xD8,
    0x45,
    0x68,
    0xE1,
    0x17,
    0x35,
    0xF0,
    0x6E
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseFSalts = {
    {
        {
            0x896E40FC022B3666ULL, 0x8C6268F2059CD2A1ULL, 0x5100B4B30F8DEB74ULL, 0xD46860A561C33F92ULL, 
            0xDC72D87778AD0D17ULL, 0x38097FC2F3D2C007ULL, 0x62E7EA09546F157FULL, 0xF7B8DE6F0D60D8F1ULL, 
            0xF02952B2D49DE0C2ULL, 0x45B7D598E4AE83A5ULL, 0xCE93ACBC4B73254EULL, 0xDA92ADBE232BD388ULL, 
            0xD125E1078C6E8CCEULL, 0x7C73B9F4A25F4B17ULL, 0x8BB0909442CC22A0ULL, 0x404EF6FF6D544E8FULL, 
            0xC9244D89D931D0E7ULL, 0x4223577979ABE6BCULL, 0x9D97A29776F60755ULL, 0x30E3FE139EA52CECULL, 
            0x1396155311C1EA15ULL, 0x397E6428B3198309ULL, 0x35A77F5EC95213E4ULL, 0x4106C43E6AE917C7ULL, 
            0x04165D7F02455973ULL, 0xDB145FD6F96F5FB0ULL, 0xDAE1F841B6A3AD49ULL, 0xBCD2EAFFE9EFD2BAULL, 
            0x82C6314364E534E3ULL, 0x856521180CFC074AULL, 0xB43516C79551617AULL, 0x544CC439ADE8AFAEULL
        },
        {
            0x39C7E38AD2CF5511ULL, 0xCE0F83B0326F58E3ULL, 0x7F8B918CAABC39C1ULL, 0x75012C4D1BEC5540ULL, 
            0x34BED1FF7DD95C63ULL, 0x42FF1AD9057EE27DULL, 0x7C4FE4DC8000366FULL, 0xF65B92727F69EF65ULL, 
            0x71FF463C12DDCF6FULL, 0x061837EE81EDAEB9ULL, 0xDCBBDFF899403600ULL, 0x56919F51A3463BB2ULL, 
            0xC7AC14793BB37C32ULL, 0xF6C8E26C7ED88011ULL, 0xDC05EAC40685303CULL, 0x7E08A1E143CD3F93ULL, 
            0x76D231333A12588FULL, 0x9CA55486E0704759ULL, 0xBC79219649DA4ADDULL, 0x5A4B2F8AF8686DE9ULL, 
            0xECC590800BD64424ULL, 0x8619D05BCCEB521BULL, 0xC1281403BDE460D9ULL, 0xCE9FF75FD9B821A4ULL, 
            0x03A2F113DA3A88C3ULL, 0x12444457A5DE9284ULL, 0x69235A682500A09FULL, 0x88E201A011C74219ULL, 
            0x3A2375240CA966E5ULL, 0x634F49111A356746ULL, 0xEE7F88EFB1857421ULL, 0x79AF9BC70AF11E1CULL
        },
        {
            0x869930E7B07B7029ULL, 0x7112D8BA70A9CE53ULL, 0xEEB657EC8133C033ULL, 0xD8915766EB8DBBD1ULL, 
            0x61F6E8FEAF19601FULL, 0x31E92FCB960C9C48ULL, 0xF54CF1663F4E98B6ULL, 0x068F273EA730AB59ULL, 
            0x23128EEADE7FE491ULL, 0xFFECE01651A623AEULL, 0x5265861E896E315EULL, 0xBAADB3F9962325CFULL, 
            0xBDDCD1A84AD2FB02ULL, 0xBD1EE5510E98209AULL, 0xC0594046EEFD6C99ULL, 0xC057E734E8DD486EULL, 
            0x0D121FA5367A3060ULL, 0xA2DF5750A09A19E4ULL, 0xC28AAB78E026A181ULL, 0xE45051C1C7B1680CULL, 
            0xA08BA575C574B0BAULL, 0x2AD454F36A9E8A39ULL, 0x80DE7B53297A8B37ULL, 0x538A7A6D277F42DCULL, 
            0xEE35D1313A83EF47ULL, 0xD9C156FFABD12D32ULL, 0x10AFFDF86AF8DF48ULL, 0x51A6577163221A66ULL, 
            0xD30DA08862E71613ULL, 0xD72E8C64219313FDULL, 0x0EF7C74A192E8E46ULL, 0x3254DABFCD0FD9D8ULL
        },
        {
            0xBA3F8844ACD796CFULL, 0x9F99E26A40884197ULL, 0xEB2649120F25C59FULL, 0xB5436388088E6F91ULL, 
            0xCB0532FA2FE75A40ULL, 0x5510C51229BE7345ULL, 0xC7B4896F4C318DD3ULL, 0xC5AB3D5EF682D89BULL, 
            0x46EBD72B9E3364DBULL, 0xDD79E24E8D81BA57ULL, 0x4712A8AF38E65FCFULL, 0x39F904B49FB1EB01ULL, 
            0xE7D096D3FA4F1F30ULL, 0xCBE06A4B929F7FF2ULL, 0x4015EC8946B22975ULL, 0x61E40E86C96F0BE6ULL, 
            0xC505D5A15D403440ULL, 0x401BAA293AF68233ULL, 0x15DA3D3B086DD50CULL, 0x9BBCE86B2176CDDEULL, 
            0xA78B248B16C2F1E9ULL, 0x81E0509A08731C28ULL, 0xC9E9761AD6441182ULL, 0x1F436D55475A69B3ULL, 
            0xB1A5172A9D4556B0ULL, 0x74EBC9318FF68E29ULL, 0x896A5975A0636836ULL, 0x24269D46FCF7A266ULL, 
            0xD00B3590AF9EE031ULL, 0x28DE80955A8FE60AULL, 0x98AAF63B36912D8CULL, 0xE0E282D7F8DECD49ULL
        },
        {
            0xD805EEB215D99DEAULL, 0x801AE0F841112572ULL, 0xE43323E8E45BE271ULL, 0xEC2AA1A3826367D3ULL, 
            0x8B315ABD017754DDULL, 0x3D970E59F4DE1019ULL, 0x73E377C341D085F9ULL, 0x04CA20C4A3A2719EULL, 
            0xDA1E4541572FEFACULL, 0xDD85CFAD94B65CB8ULL, 0xF5F38FF4FFF43DC1ULL, 0x5783525073B29280ULL, 
            0xA4BDFA0EBD53783EULL, 0x307FA9B6BFE19B28ULL, 0x5C5B3285204A098BULL, 0x8EFB885B9E8EE67AULL, 
            0x49DB0D2DB3274751ULL, 0xA1454B7D38E0CA6FULL, 0xF954CE21ED15FF73ULL, 0x834E3914018F042BULL, 
            0x18859DA171870F05ULL, 0x8B80803A1222763DULL, 0x8E023DF14DFF1050ULL, 0x1870A6C02511D07EULL, 
            0x87E3947CF8EA940BULL, 0xDC2FDD28D29D61FAULL, 0x59B86F0D733F14E9ULL, 0x310B6DCF7548D898ULL, 
            0x5E686A722312DF82ULL, 0x4605821C15589DE5ULL, 0xBDB313726C3DEC2AULL, 0x5DE84BEE355ED72EULL
        },
        {
            0x82BD62A48A972FABULL, 0x66DAE9019FB97E71ULL, 0xD9ADBBF2FFD25FDDULL, 0x21C6AF27492A9E85ULL, 
            0xA5FBF6F87FA0F2FEULL, 0x92335AC99EA93280ULL, 0x21FC6B0E75E0383BULL, 0xABFE54927EC440FFULL, 
            0x7D47FA071026A954ULL, 0xE11804CC5C180830ULL, 0xD49978C13EB7DE47ULL, 0xA74BDD7B895D1001ULL, 
            0x89E8ED7601AA9C5BULL, 0x61331EB8AA50B607ULL, 0x161EBBC868BA8F4FULL, 0x45F95C66F583C815ULL, 
            0xEA3A715B4FE799F1ULL, 0xC4EFF9D8274C936EULL, 0x10205D511E727355ULL, 0xE24603B88C32221AULL, 
            0xEF072711F821EE29ULL, 0xE9C62D65FC3A3A95ULL, 0x673EC377F014C128ULL, 0x6E020328299033FFULL, 
            0x02B59DAEDDD8463FULL, 0xA174B30256BB99F7ULL, 0x53F266B348D7D2F3ULL, 0x7F4541AB2B39E3A2ULL, 
            0x8082C5E995179838ULL, 0x435EF3106F5836A9ULL, 0x3FE1E3B81D34F5A9ULL, 0xEAF5E1D6CB5383CDULL
        }
    },
    {
        {
            0xF50058EEBDC8828AULL, 0x80F88964F3239FA5ULL, 0xE493AFF9632DE815ULL, 0x95D0D87F49A5A1C0ULL, 
            0x3AD9C7F198410DDDULL, 0xC7674B122512638DULL, 0x3001FA5FE35641FEULL, 0xE51ACCE7F73A0151ULL, 
            0x93E3F4304A87C502ULL, 0xA07A7522581B4B93ULL, 0x5414E56CF629DD8BULL, 0x455236242E706A89ULL, 
            0x013BF1BDD77A2764ULL, 0xDD6E8EC0AEEC1B91ULL, 0xE3534BB0CE3CEFACULL, 0x14B988C13129E1E7ULL, 
            0xFBA51A77259CA6DDULL, 0x94E1A10C345ABAB9ULL, 0x4ABE735B4DC6F075ULL, 0x295435133EEF585BULL, 
            0x4D33D421BF97BB65ULL, 0x3BB699E968FBD5C2ULL, 0x50FB8782A5EFA741ULL, 0xB42AFC322FA5F678ULL, 
            0x1919B997295DE603ULL, 0x692F7735F0AAC2E3ULL, 0x07518E64382EADF9ULL, 0xBC83469CB367B578ULL, 
            0x7A0A845A9D614D38ULL, 0xFAB155C78FD4EEFEULL, 0x20E5B55E2F23CB4DULL, 0xA24B9CDF5A0A4361ULL
        },
        {
            0x2D9931DC17567A83ULL, 0x1B7B0BF369C27E53ULL, 0x8DC10CD75292CD32ULL, 0xBE547D968041ABFAULL, 
            0xFCE2B542667D78F3ULL, 0xAD84E26691A864C1ULL, 0x9D3A2F27D1209F0AULL, 0x729E6DACD14C7BB4ULL, 
            0xDBCB1DBAE9DF42B3ULL, 0x38870681A008B9C0ULL, 0xAC7020A78F3B02FBULL, 0xC0B4A9566C2173B4ULL, 
            0xDCC148F538F38E5BULL, 0x992B35C94D984878ULL, 0x359C59E00434EDB5ULL, 0x10E0CEE69F30E04BULL, 
            0x9B004C15F8D8A29CULL, 0xBF6352FDA8A6CE5FULL, 0xC15881C9D86B3EB3ULL, 0x66917BE3D7FE668FULL, 
            0x3B5A59DE75E841B8ULL, 0xB1A742936CC15CCBULL, 0xBFC63C83F5000AFDULL, 0x1E9D53E25AB4EA94ULL, 
            0x1595F985FCED4A0AULL, 0x17F3E937A7D388C6ULL, 0x57785F1BCBB6AE41ULL, 0xB22A2AC36086B58BULL, 
            0xD240BC905FF13372ULL, 0xCB460A4048F2C540ULL, 0x55726C3DB82CFB62ULL, 0xF75FEAA52750CBF3ULL
        },
        {
            0x774ADF638308B3C4ULL, 0x17C7B9A6582E062CULL, 0xB237163AABD90BAFULL, 0x6AC93903865AEA39ULL, 
            0x5D73C46D80034DB6ULL, 0x67F58681895B31D3ULL, 0x4479C1BC1E181AC6ULL, 0x51815102CDA1BED9ULL, 
            0x3CABA89CD2F4C946ULL, 0xAFAB7DE8B9AA7CA3ULL, 0x1A0A3EEF49CD517BULL, 0x9C3D95F9571E35FAULL, 
            0xB2D3266F227978EEULL, 0xF94296515C08DB8EULL, 0x3322B26366876DC0ULL, 0x970F0F6D42D261C0ULL, 
            0x7DD1C34D1FA0F58FULL, 0x49F69CAC26749E8DULL, 0x037E5B518704C9C5ULL, 0x76A24DF66243FF75ULL, 
            0x540D2487C0872843ULL, 0x0CDA05EC1B0ABCB5ULL, 0x5F12CABF5B444C33ULL, 0xF0A5347BC9094188ULL, 
            0x42A22B1ABECE959CULL, 0xC83AD2A1565C24BDULL, 0xC1A9F6B9B01BAF95ULL, 0x8D5FC9C5291471B9ULL, 
            0xC0DE361E7D318397ULL, 0x21364FEB19590A98ULL, 0x60DD309D27467613ULL, 0xFD882BD76DD99187ULL
        },
        {
            0x2F4DAF3D9FEBF1C2ULL, 0x9DD5BC535B241C46ULL, 0xE83C768D8CE57E44ULL, 0x022181D442637311ULL, 
            0xE48E90354F500A83ULL, 0xC14FF5CE834BD5C0ULL, 0x62CE262A3EE391A8ULL, 0xAE73CC46C894F5E5ULL, 
            0x6F13B3DE98C62D22ULL, 0xDAE7B2E66AAA6B2AULL, 0xEBCAA1C022EFBB2BULL, 0xD99F75EC403B0C00ULL, 
            0x240F08E274D88FF4ULL, 0xAED9E771DE868B59ULL, 0xE6C40AB87170CCF7ULL, 0x9D1D50AC55EB0462ULL, 
            0xBC4642EEF9F80413ULL, 0x757BDCA3A36DCE8CULL, 0x0817BE07C155C915ULL, 0x96C75FEACAA8B956ULL, 
            0x59B585835049C870ULL, 0xDC66258C4334E611ULL, 0x8A25138C1FECDE71ULL, 0xD75EB2F72492BE94ULL, 
            0x280291AC019820F9ULL, 0x56F61CDDA640F4EEULL, 0x99C8E8525677D277ULL, 0x9F780F15EF150001ULL, 
            0x4ACD2FD9384A4089ULL, 0xE8F1A88F847475A2ULL, 0xDDF826D082B6DB3FULL, 0x507D41693A54D71BULL
        },
        {
            0x54262586CFA273CAULL, 0x5CF3433582612A83ULL, 0xFC55B651E0ADBFBCULL, 0x1E6F0601859F53FAULL, 
            0x8172563A3F426673ULL, 0xF2F3E2A384754CA8ULL, 0x8AA20ED87627D0FAULL, 0xF8FAE82664BFFF1FULL, 
            0x84C297571135CCA3ULL, 0x8EA764AB0494B676ULL, 0x27C9C8ABAAA8F6EEULL, 0x1948BBB05EC17974ULL, 
            0x518A6A4F795C1309ULL, 0xC6691288F92127ACULL, 0x156EDF4B5D996E99ULL, 0xD91167BCA2EEB116ULL, 
            0x2AA89F5EDB3761A0ULL, 0xEE7316F0117E019EULL, 0x74729457286AF29BULL, 0xDF9095F485B73DBFULL, 
            0x37B67D138212CD59ULL, 0x54FCE7C1D65E8BA5ULL, 0x5F8F2540C27D3E0BULL, 0x2B3637814572DC90ULL, 
            0xCB0EEFD70296E775ULL, 0x3B8613E83340BB2EULL, 0x22AC4A514DB6F145ULL, 0xD90DDB74BD0BB827ULL, 
            0x5F81A2CA9343BDF1ULL, 0xDA02EA748480EDF2ULL, 0x0B3B30119C26ECB1ULL, 0x3F7B21E85A4C8CB6ULL
        },
        {
            0xDE8FAF97706631ACULL, 0x894654F9BCCF633EULL, 0xA0013F3256A1C835ULL, 0xEA70DD9132EC7DF4ULL, 
            0xA8C98ACC807646F9ULL, 0x8F575EFA09A48CD5ULL, 0x95F01655E81223D5ULL, 0x9D5C6CD84FB3494FULL, 
            0x4CF7471667BF52D4ULL, 0x22B0301CE3551A86ULL, 0x0E8D8F8CD9921DA7ULL, 0xCFD98FA393A0BFDCULL, 
            0x338641EEFD9FFA23ULL, 0x53A1FE19AF357F30ULL, 0x2FD123FBDA69C593ULL, 0x60E535690C1936F0ULL, 
            0x67C4191A800F943DULL, 0x3FEE248E19BB13ADULL, 0x1331F0971C127D45ULL, 0xF28E3746217392CDULL, 
            0x45FD58B9D4720393ULL, 0x3F080906F2400132ULL, 0x94D41A6D0C083B88ULL, 0xF511B33C62D6A2FFULL, 
            0x783E2C0C0D58C4F2ULL, 0x21913FB9F78D19DFULL, 0x4D11FCE40DA4090DULL, 0xF0739E951626CA7CULL, 
            0x386BCFFBADA2286DULL, 0x5B76B4FEE37997CCULL, 0xE7E2803F61C9F1DBULL, 0x7551277B8BCE7D92ULL
        }
    },
    {
        {
            0x435D33DDAA995F7CULL, 0x41296E55ACBB325BULL, 0xD04961021F97F6E1ULL, 0xBED7FB27EA12A54CULL, 
            0xF7AD2CCD7A03FD68ULL, 0xB8267CDE38C0E9E0ULL, 0x35416D1FDAFE2CCFULL, 0xA2D41D5ACB1E543BULL, 
            0xB4C0BF45792C0475ULL, 0xF81572DBD41D0991ULL, 0x475AC605A020F48AULL, 0xE5E184437A2005EAULL, 
            0xE25D83CE434520CBULL, 0x6FDD6FE1A56993DDULL, 0x397BDC1B83D3A304ULL, 0xEDBDDCBCC15EC0DBULL, 
            0x6A0492A333FD2862ULL, 0x292490F498480815ULL, 0xAE94FBBF69001D16ULL, 0xD5F1B68061752D30ULL, 
            0x90E5B4F6580FE1FEULL, 0x588373147219B7F5ULL, 0x1C78F14B401F787EULL, 0x5B236C8A3E6970CAULL, 
            0x68E89D8043FC405FULL, 0x2E4A9FDC54699711ULL, 0x3B4118F2E9490092ULL, 0xBF5415D361F9D381ULL, 
            0xD628351899C5A3AFULL, 0x3DB01EBB55A319ABULL, 0xE4E327034E5D602AULL, 0x1718EB7E82D7E9F4ULL
        },
        {
            0xED4D4E917BA95D17ULL, 0x729FD5433925F272ULL, 0x9C385062195B65F5ULL, 0x812DD92F7528209CULL, 
            0xF847A58EEB51C7D7ULL, 0x3D8A8A639DB2CEADULL, 0x986B43100570DAE5ULL, 0x0516EB48617972F1ULL, 
            0xFC1A54230A8CE774ULL, 0x33F948F2626CE3CAULL, 0x412312955A876869ULL, 0x59E3A9DED34CFFF8ULL, 
            0x6362EEEC09612906ULL, 0xBF50E841A67375ADULL, 0x7246718B1B48F894ULL, 0x8D8F43C1C5195ADDULL, 
            0x506A0CCFCBC98F74ULL, 0x977012322021318BULL, 0x8171AFC1C4F8CDA6ULL, 0x3C6C104812962219ULL, 
            0x27D0F7AC37B1A41CULL, 0x1D40292DE6B0879CULL, 0xABCD82CB1D350BAEULL, 0x6312000BD2656542ULL, 
            0xFAA7268FF8026CA7ULL, 0x7E8583B7E133E157ULL, 0x61F591EEAF33FF8AULL, 0xC72B0349B7A4D339ULL, 
            0x735C650C78711DEBULL, 0x5AADE9323CF366C3ULL, 0xA380C3B3CF89D321ULL, 0xB20D7E1815692BF8ULL
        },
        {
            0x29F4CC6CBBA9BA30ULL, 0x1C8D34422FFD61BEULL, 0xB68CC2212194E555ULL, 0x7F49CBFB6BFBF951ULL, 
            0x0566B42BA225C21DULL, 0x31DDA3058DDC64C2ULL, 0xF77C20134E9A3BB2ULL, 0x1E59FFAA91C024B7ULL, 
            0x112DA9C8CCD11108ULL, 0x877D91722742B5A5ULL, 0x64C8B9175B3C0235ULL, 0x83D227808AD05990ULL, 
            0xC04F8002E133A271ULL, 0x7DE463B72906A8ADULL, 0x08C78FD1C6573EF7ULL, 0x3F259357BCA50660ULL, 
            0x0082F72C4C3B28E9ULL, 0x7EEA72BC18471FD3ULL, 0x30D458C0D83E0801ULL, 0xA86AB4FB39F91BCBULL, 
            0x6F95A5AA7882DA10ULL, 0x89B5FB0A2381D516ULL, 0xB7025697E424A8DBULL, 0x614786CF0A5C8110ULL, 
            0x301EA98A5A982CA5ULL, 0xAE944155AE4228F3ULL, 0xECEEA6E6CC28C6B6ULL, 0x046698BEC742EFCAULL, 
            0x3C739BD09192DBE3ULL, 0xBABFE5FB8CC4936BULL, 0xFD42A3ED83699753ULL, 0xA72B55E0EFBEDDF6ULL
        },
        {
            0x3FF6751292F694E2ULL, 0x61DFBADE2AE39836ULL, 0x53837FF971FF6DD7ULL, 0xA787EB9479017E67ULL, 
            0x75D15171712BE612ULL, 0x7D1435AFD62660D5ULL, 0x5E235540C01FED65ULL, 0x5F6799269C41FFF0ULL, 
            0x27BC16B66EA67577ULL, 0x22DF18A940ED4CA5ULL, 0x756E28ED5F5C2F7EULL, 0x142ED80B13B76076ULL, 
            0x47DB3AD1147C303FULL, 0xAA7B8E229FF94EB0ULL, 0xB503A00E7E5F1936ULL, 0x349637B8F987DCE5ULL, 
            0xD24547550A8EB9EAULL, 0xEBCF4146E43D145FULL, 0x3EB99BB127F3B18AULL, 0x36DE3E68927833DEULL, 
            0x683A5CD2FCCA2DD8ULL, 0xFAD223351761D38FULL, 0x6D24F63446602AA1ULL, 0x2CB02E69606EE1BAULL, 
            0x2639351F377B65BCULL, 0x50276545ED5746EDULL, 0xFF9254DE7C83DF24ULL, 0xCAE6C0F78F43D376ULL, 
            0x645B2D427D0805C4ULL, 0x30D9CC9CF7DADB9DULL, 0xFED286136BACD768ULL, 0x5FFE1806D058B12DULL
        },
        {
            0x248B407CEBAF1AE4ULL, 0x51E2999AEE83AF61ULL, 0x65DFF6EA5067E1EFULL, 0xB97F39C4B0D6E8ABULL, 
            0x226A541DAF37BF49ULL, 0xA519B3299C90CA3EULL, 0x2D9B65E3C71064C0ULL, 0x35E5AFED6280A72EULL, 
            0xA380A5569A4E02D9ULL, 0xC7C2C421E99984F0ULL, 0xD6A1384EA1B4F6E7ULL, 0x7E645F0F74E840A8ULL, 
            0x87DBBE24DDB69FA3ULL, 0xCC461566C1F94B28ULL, 0x82BB857F89CBAF7CULL, 0x2CA61B3280AC0A08ULL, 
            0xFA67A3B060064DC1ULL, 0xEED2865EF067576BULL, 0x91EA33CFE4554FBDULL, 0x8D3F2BAADA20501FULL, 
            0xC1C326162E3EABEEULL, 0x7F13709FC145AD55ULL, 0xEB358E47DFD44F64ULL, 0x6AD7C127E423D8CAULL, 
            0x393D45244A247F96ULL, 0x7F974552D83E03D6ULL, 0x5A109B041E1F0F53ULL, 0x0633ABCF2679B438ULL, 
            0x97FD55C871A9D7C1ULL, 0x6E6D252A30982824ULL, 0x27A20BED1F2ADB0DULL, 0xFD7E2CA7CF13B228ULL
        },
        {
            0xCA4228D3E55D9A11ULL, 0xE48866C06902C6A8ULL, 0x24EA39A9A003A9BFULL, 0x3FE5E3F9FC51C652ULL, 
            0x72AD778DC4086AAAULL, 0x1F28CA538B64109EULL, 0x5090EED334C31D60ULL, 0x11AAF895C510FB70ULL, 
            0xE34BD7406332CCC2ULL, 0x2350EDDC2A53DB63ULL, 0xFCF705BA5A4518F4ULL, 0xA84CD4B9D5637CB7ULL, 
            0xC23A2876ADF82375ULL, 0x51908D581E169691ULL, 0x8867FFD00A93472FULL, 0x67DA2350278AD4E7ULL, 
            0x61BC0CBFA6292E67ULL, 0xA833D0B84863D97FULL, 0x20AA80E6FEBF98C0ULL, 0x7C01BBC9CF2C8EACULL, 
            0xBAE19DA0F35F9C8EULL, 0x565BB0077DE5C7AEULL, 0x40ECA952AF7BA96EULL, 0x14429D92246E6FA1ULL, 
            0x718396D42FA0687BULL, 0xE0023FC32D181B2CULL, 0x759C2FAB3272581CULL, 0x232F6799F8F9EA2EULL, 
            0x31AA399DB13AAC19ULL, 0x3EB0688983D6AFACULL, 0x5A35898441A4368DULL, 0xFA9C45291CE5B367ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseFConstants = {
    0xDCA7497F0B7B0378ULL,
    0x006CB3EFC80C4DA9ULL,
    0xA651758A4E48684BULL,
    0xDCA7497F0B7B0378ULL,
    0x006CB3EFC80C4DA9ULL,
    0xA651758A4E48684BULL,
    0x2DDDA02AA71F9AC3ULL,
    0x3E8C1BDCD0E27288ULL,
    0xA8,
    0xA5,
    0x3D,
    0x10,
    0xE9,
    0xFC,
    0x57,
    0x5F
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseGSalts = {
    {
        {
            0xA2B40510FF49BD4FULL, 0x5A374BAA0B095227ULL, 0xBF17C0FF7289A438ULL, 0x0C4432E217A1E63AULL, 
            0x0B841451A2BE702EULL, 0x13BF068580798F15ULL, 0xA9C832487679C508ULL, 0x93C940D81B9AEB7DULL, 
            0x25724700DE445C4FULL, 0x56D105213F9DA6B4ULL, 0x9902935CEE6690A8ULL, 0x0E00F144AF349A17ULL, 
            0x89693E38AB41E77DULL, 0x7B5679DEE91D676DULL, 0x4AB55958CF433D4EULL, 0x04B2AF76ECA4593BULL, 
            0xB92F45388AA4123AULL, 0xDAC0C65497F28DBEULL, 0x85F307101B140874ULL, 0xD31FCC8813930866ULL, 
            0x18B9224B5000E46FULL, 0x29B37314C0498393ULL, 0x5187277F277DCACEULL, 0xC904D214D428AED0ULL, 
            0x3957715F77AFD02BULL, 0x687024DFDC81C1DDULL, 0xE03E61D304DE78DCULL, 0x60AB8BA5EAF8F1C7ULL, 
            0x51BF37F2C2F4272BULL, 0x4F614E7CE425ABC8ULL, 0x6E4ACA8DFBB53ACCULL, 0xFA86E995E50772D0ULL
        },
        {
            0xEB38C7D41B61D931ULL, 0xB4C4707AF7DEAB71ULL, 0xACEFA0396BB024B3ULL, 0xDDDA6D371AA83277ULL, 
            0xC90BAC9323A8D2F0ULL, 0x031D036B0C5F7F8EULL, 0x864BFD07AEBAFEE7ULL, 0x3FCC5DB96A146256ULL, 
            0xCBA52AC21F748E2BULL, 0x63061B88E5F35D98ULL, 0x7C810372E17B57E9ULL, 0x372C234FDC3D250EULL, 
            0x33C5FB202FB2907EULL, 0xDA2EE38181D5291EULL, 0x713738BA79448CF8ULL, 0xEDED2C4ADE534660ULL, 
            0x27964008F03B4468ULL, 0x59261982C1009827ULL, 0x8877035AC9C723BCULL, 0xD0A5B77428874D97ULL, 
            0x9404AC6667F9A768ULL, 0xEE391C8825B84CF4ULL, 0x34723F2114020052ULL, 0xA895D16A15F46D8EULL, 
            0xDD5DE47C0135E29AULL, 0x033CB00B0B4639E2ULL, 0x2DEF8E460A4A9B02ULL, 0xB2D1C988F1B4EADCULL, 
            0x71CA4CE341651072ULL, 0xA5C38870CE3BFD7BULL, 0x751D2798C134F617ULL, 0x9E25A9E50DE46439ULL
        },
        {
            0x2A68617FB377509DULL, 0x1E9B8154C1BF7E1CULL, 0x0AF4149CBF3C2943ULL, 0xBE2FDE40FCA40D9BULL, 
            0xE280541579106B32ULL, 0xE0868D74A8825130ULL, 0x6B29DF6FD5AB88E2ULL, 0x68BC902D81EC1F05ULL, 
            0x0FD905541997F5C8ULL, 0xBB627A9AB85EB71FULL, 0x530DFB222CBF7E01ULL, 0x490AB36ECC3917C6ULL, 
            0xEF1034B568F7699DULL, 0x4C3C7A44E9F99385ULL, 0x1248C26184A8FEA9ULL, 0x945E29E00DB10476ULL, 
            0xEF71161BB325E1DAULL, 0x20D1222CB6A4F8BEULL, 0x9CD4BF5513FEE910ULL, 0x72187859568159E4ULL, 
            0xE45A0EA2C0FC8B69ULL, 0x543C66AF307781BFULL, 0xFF90896B59DE9565ULL, 0x396787B135F52F1DULL, 
            0x9CA82EC2C6A85CE0ULL, 0xE0679B095FC31543ULL, 0xC0F47ADC6D86BDFEULL, 0xCEF215C28FFFF69BULL, 
            0xA5DF15D490587083ULL, 0x09571D4F03281BE6ULL, 0x038D19544B09CB73ULL, 0xDD6EC1D869A977B1ULL
        },
        {
            0x7EE1ADBF89F4DC3EULL, 0xDB4ECF36B773ED93ULL, 0xC7D64C5639B53A9CULL, 0xFE6D6D6AB7359D3AULL, 
            0x28A5801C285C6913ULL, 0x9EEE363A68EFC9C7ULL, 0x558D82F085B95FF2ULL, 0x5C85658CDFFA3E45ULL, 
            0x77FC8680D43FEE0BULL, 0x9F10833E05BC8EF4ULL, 0xCAE2D218EDE0BAA8ULL, 0xBF8DF4AB21BBA1DCULL, 
            0x89049E2340D527A5ULL, 0x15CFA7C40C79048DULL, 0x28253FF7D3D051EEULL, 0x409B6487ED23C43DULL, 
            0x647ABA0D34151E4BULL, 0x7D3138CE6CBB5CA4ULL, 0x1611AF7090FA05A0ULL, 0xD7430A6D2B2C8B8AULL, 
            0x7CB6B74A37A69078ULL, 0x7B2CB632AA999400ULL, 0xEF1979E6903D4823ULL, 0xCFBC9054588CE872ULL, 
            0xAB291743A297B0F0ULL, 0xA6CD59EB341B7F6EULL, 0x355D970C5E7745DBULL, 0x8AA7B21031516483ULL, 
            0x4DB5BF272EE19B8BULL, 0xC5AA557E9C3D70D8ULL, 0xEE92C983B4D932E5ULL, 0xF31EF0E5699383E2ULL
        },
        {
            0x066430CF4C66E2D3ULL, 0xF8D804695E36035DULL, 0x17ECEC520BEDC03DULL, 0xB5DBB38B0C43B4A9ULL, 
            0xAF525E61D9006773ULL, 0x767534BCABF09DD5ULL, 0x223D2D6F8322F65DULL, 0x61574015D37799C9ULL, 
            0x55F0B356499C7BE8ULL, 0x4BF79444F0337109ULL, 0x3BA2A7524BE43D24ULL, 0x404C39BCDBD3142BULL, 
            0xAAB539BBC7A1274EULL, 0x28F7198101C33A34ULL, 0xAA11DFD043D2A783ULL, 0xA6E4A81991189BC7ULL, 
            0x1BF39476953D60C5ULL, 0x6A676B306A3D2849ULL, 0xF557E4A3E7C2138EULL, 0x873CD6A03BDD98F2ULL, 
            0x0C37817C04734476ULL, 0x451FD803DA709319ULL, 0x9A0E07EA07AC195CULL, 0xF0FDBC9BC3B82364ULL, 
            0x352663A7D0711E7EULL, 0x9483FA025F3A7924ULL, 0x96E37FAC9F8992F8ULL, 0x624CD9017ACDD0E6ULL, 
            0xF46D9CC9D17D0D02ULL, 0xE52FA9961E37FE65ULL, 0xD7AA83A5D6A7FE94ULL, 0xE9ABA953769B58B9ULL
        },
        {
            0x6361C9091E31A112ULL, 0x962AC025EBF864BEULL, 0x3233B1ADFD57066BULL, 0x59380CDB1C0D3A10ULL, 
            0x6A5127B7D5DC5210ULL, 0x2F2899A07AF7D389ULL, 0xDB73CE48B6FD4C5DULL, 0xD035B6058386FE9DULL, 
            0x085ACDA7BC29377BULL, 0x7E9B486A27D886AEULL, 0x4B690B3A87134F92ULL, 0xD60A0B583B0D4DB1ULL, 
            0x7A91BC4C2611CF09ULL, 0x0558200FE7E811C5ULL, 0x8DF6BB7CE632C152ULL, 0x84BB6B7D552E366AULL, 
            0xC0F14379B7721EFEULL, 0x0529CA5226234598ULL, 0x5BB4434454C3DDC2ULL, 0xA6F971F45543A125ULL, 
            0x5363750C12AF77D3ULL, 0x09EFFAED3FCEED81ULL, 0x788A4FA92261A89BULL, 0x4C222C753E7788BCULL, 
            0x7C7EFE4CB267CA48ULL, 0x8A4C8A66022A4A5AULL, 0xED373E322B5CE06DULL, 0xD88EA3087A296131ULL, 
            0xC8E755DBCE2607CFULL, 0x7EB503FEC0B678F9ULL, 0xA565F9246F825FA3ULL, 0xB5A60C92CAC39885ULL
        }
    },
    {
        {
            0x6E9ADDBC672A7021ULL, 0x44D84C893418E6C0ULL, 0xD57A5B2174A03879ULL, 0x8484097F1480D409ULL, 
            0xBB252401C574393DULL, 0x90DDDB7B990BA922ULL, 0xFC584445FD00F23CULL, 0xB14C5E31515DF352ULL, 
            0xDFBDDD0A93502CE6ULL, 0x97858BD946CADD9BULL, 0xE869FD9BF0E0C0D7ULL, 0x70467F0BFD4928DDULL, 
            0xA7F853B859DC9148ULL, 0xD92EF3DAD45C0C59ULL, 0x00CC881E4467472FULL, 0x402AF8690512BCB3ULL, 
            0xD57196B3F766743CULL, 0xC75F46DCC95ACA74ULL, 0xB5135771548B8558ULL, 0x1DE24C2DE7B681B9ULL, 
            0x8C4A3B9148F09D76ULL, 0x28D933B151BE0248ULL, 0x6D3BC266BB3085A2ULL, 0xD4A51E950599C498ULL, 
            0x6B4D2FAF7F681576ULL, 0x3C38D5DCBD715CC9ULL, 0x5570301579AB873EULL, 0x62767BAF856BB4F2ULL, 
            0x420F0A068979935CULL, 0xEAACC1224267483CULL, 0x4CCF9E7F437CADAFULL, 0x2A340A032C3BD904ULL
        },
        {
            0x19452A70C2ECB152ULL, 0xE137BB66D68474E3ULL, 0xFE9E62786D1EDE66ULL, 0x23AA035318CF6A0EULL, 
            0x145E099C3C00087CULL, 0x6C26585407BCDA38ULL, 0x29CEA5E0B57F8B41ULL, 0x28F3FC35E0F86954ULL, 
            0x56FD30AB8D83CA23ULL, 0x773552AD2FEB944BULL, 0x78A830E42D3532C2ULL, 0x523020E5E8767510ULL, 
            0x4ECD12883CED7E20ULL, 0x6BD563FEE3393A09ULL, 0x6BB6BB928A2331A0ULL, 0xDD0A525D1BEA068FULL, 
            0x9EC35F7A5D60CA34ULL, 0x218AD6F743C290E0ULL, 0x5CCA440A50FF81C6ULL, 0xB5E86C0346C670C3ULL, 
            0xF5EB1C1A9F1BFE23ULL, 0xFD5F16539A4CE008ULL, 0xEF841AED6EB44227ULL, 0xE88255A6462F4379ULL, 
            0x60C29160750FEBF0ULL, 0xE26307658405113BULL, 0xF09879A435954B3BULL, 0x6497A61B8A20B9D6ULL, 
            0xF7A53BC3A387596BULL, 0x009A3BC0608CD325ULL, 0xCE2A36EB610D9DF6ULL, 0x518DD9E8BC647D6FULL
        },
        {
            0x4B95F2AF5CE467ACULL, 0xEEC7294E70D8B0A7ULL, 0x9963C1B363E193E3ULL, 0xF117243DDFB9F619ULL, 
            0xFB682E8A2DF005E4ULL, 0xD64E1DA37DBBE75BULL, 0x812B591F6F2A2C9AULL, 0x2753D3CF05F9CB27ULL, 
            0x2A287601D09E7215ULL, 0x613F83016C887688ULL, 0xB45DAA2ABE21A32AULL, 0x476CDB4B7085B4AEULL, 
            0x42FC4E1B7CFD0870ULL, 0xE3D9F4987E5F1154ULL, 0x0BB9FECC92FAA83DULL, 0x31F5B6DF5F2304EEULL, 
            0x67560A58D829472EULL, 0x4C823546EF2FD2CCULL, 0x7DCCA9769FDFCE7DULL, 0x9C19B6AAE8D60CE2ULL, 
            0x36347B58F8DE190DULL, 0x0DA6AB350B43D9E8ULL, 0x369C3F5621B51826ULL, 0x8CBD9B083C0B12D7ULL, 
            0x587A956C42B728F0ULL, 0x3DCB9535990650CDULL, 0xCA7B8ABF7A267CCAULL, 0x2E0DAEB106704B41ULL, 
            0x67D30A3F8DC9582FULL, 0x5FB957DDE8E26843ULL, 0xDB7F2C39487DF789ULL, 0xC150D9FE0769FECAULL
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
        },
        {
            0x4F99CCEEC5653870ULL, 0x4AA68195028DEB04ULL, 0xBBF9F89643E7B911ULL, 0x420A2BC339D9E761ULL, 
            0xA851EDA1B30921B9ULL, 0xD56CFE1C7AFAA890ULL, 0x9F74A5D13413FB63ULL, 0x32B0D3B9EE9C683DULL, 
            0x4A8B91546D1CBBAFULL, 0x4DDD7A426BBE3C77ULL, 0xDCF0CD541BF50624ULL, 0x357EFFA1B9FFCD82ULL, 
            0x65BCC6680FAF5690ULL, 0xEEFB8AC588C8697CULL, 0xDAD6B036D97001E8ULL, 0xE4F5951055DA1D5FULL, 
            0x37B6F2F84E43BF62ULL, 0xE04FD89437CB5A1DULL, 0x6288939ADC0273D6ULL, 0x68DAFD758C4C2F4CULL, 
            0x9EC83E07885C0180ULL, 0x280CB5993825471FULL, 0xC7ECE69140DD6152ULL, 0x8D79B92FED56920AULL, 
            0xA4756FEA10AF6814ULL, 0x4C48921031522260ULL, 0x650D93B777D71113ULL, 0x1096D68FE95CADFCULL, 
            0x1AFEC0E1A85F38CBULL, 0xC8D9295FA595461FULL, 0xD7063854BCC3682AULL, 0xC4609922C7F67B8AULL
        },
        {
            0x4BA0FDCB743476F8ULL, 0x4C2E2CB556FA659AULL, 0x5A74842C74832FCCULL, 0x807045CB1382EEC4ULL, 
            0x658980EFC74CA931ULL, 0x87A1B943F953A665ULL, 0xCBD3E7AECC8C516FULL, 0x0DD34EECE09340E9ULL, 
            0x6EEE8F55F76C4FCCULL, 0x45F3F0F6B199C560ULL, 0x7D4EFE11858D7E38ULL, 0x9BCB5799AEBB3274ULL, 
            0x2D5FCCF2A8223153ULL, 0xC72A86789E42E5BDULL, 0x9EDDA28C7E83B7CDULL, 0x5F9F413646D2F4DCULL, 
            0xAC1BD51CA6260275ULL, 0xB5B9FFC2C1673D98ULL, 0xED65E77FAB93CA5BULL, 0xFD6930AB3ACC095CULL, 
            0x0617BE47188D875BULL, 0xC11838280AA3B886ULL, 0x0A0E6F5F3E3CC3FAULL, 0xEE24A59271D142E9ULL, 
            0x3E4D93E543D42907ULL, 0xB42B7F52D3188608ULL, 0x9480CE589F85B5B9ULL, 0x4034B63A55322168ULL, 
            0x2ACEF557405E1A10ULL, 0x50B800624209AA3FULL, 0x4239B1F4064E3520ULL, 0xA4DA125FE49C7D38ULL
        }
    },
    {
        {
            0x1BCF994E6560FFD6ULL, 0xFF063B593712C39EULL, 0xF240D067D1C5C675ULL, 0x28AFD393F2AB476EULL, 
            0xC06BB7D421154A19ULL, 0x9D7F0470219170EAULL, 0xFC65285629413683ULL, 0x855D345881A0405FULL, 
            0xB4B2D7B2B624EBC1ULL, 0x5E793619AF0C8D2DULL, 0xE4969B5938BC0541ULL, 0x72272843DFE8D0F9ULL, 
            0xA1773E03092E72A8ULL, 0x8E95F2430053247EULL, 0xFF69B84F839B51D3ULL, 0x63DB92BCB16A17D8ULL, 
            0x1461CBC0F5C91470ULL, 0x80F9F80DE8E09C75ULL, 0x54917F8C79E698F4ULL, 0xE1ABDAB32C66CA02ULL, 
            0xEC10CF555A78F949ULL, 0x5B870CEE13174DBBULL, 0x77B660C22D987CAEULL, 0x3604E315FFF266BBULL, 
            0xF0A285878410AEC2ULL, 0xAFE99CB1A953291FULL, 0x3B5AC9ECFE5D0ABFULL, 0x507FE1E0F89E0D3CULL, 
            0x6EDD4FB9E22DE5F7ULL, 0x1B7014B01953E9B2ULL, 0x72E95AC426B98EA7ULL, 0x65C7B1E08E03D083ULL
        },
        {
            0xEEB5E8AE31B00995ULL, 0xAA3868BBB7FA280BULL, 0x4624C6B0434FEBD2ULL, 0x1F478FC675FCFB22ULL, 
            0x37D2C950567780A8ULL, 0x4ECACA3B80335750ULL, 0x89B5E1430B2EB061ULL, 0x9CE548EA61F4C1CBULL, 
            0x8361565DB5D0F721ULL, 0xF1DBFF22D121D022ULL, 0x146A83BAAE7FDDA1ULL, 0x2352D14FE86F5338ULL, 
            0xE8A30C6A794C634AULL, 0xF51733D0BC7D327CULL, 0x4497C26ED5AB6E6CULL, 0x642A1BF6833327A2ULL, 
            0x93FB43B85B9702E7ULL, 0x3B7630F1CFAD1D6FULL, 0x1C35A7E07B87ACE3ULL, 0xDA72575EAF0410E7ULL, 
            0x9EB4EDE62DB64833ULL, 0xC05FDCA638D1E1DDULL, 0xC24E1E50951C94D5ULL, 0x24BC0F809FE38E71ULL, 
            0xFF5E53BBEF430C13ULL, 0xB0C2371C9162A73AULL, 0x381E80DE0C44C1C4ULL, 0xF68F9D615E26A725ULL, 
            0xBAAA214938A7611FULL, 0x3AB9742AF085EB9FULL, 0xDCE084508C80B72EULL, 0x4226E6A8CFAD8B49ULL
        },
        {
            0xE5D499C02A0BA01FULL, 0x10DEACB30EE83654ULL, 0xF1249255C9E6414EULL, 0x741C40E97C1BAA55ULL, 
            0x01CA87BC37E29ACAULL, 0xFBF1E7A2C564124FULL, 0xBCAD6D1CFA1B4E35ULL, 0x7D3CF60B8A90E4F7ULL, 
            0x5E8B360D5D5EEC57ULL, 0x9FCCC39ABFEF8019ULL, 0xE0E104278BE0FF94ULL, 0xFA9C3E3F33FB3F4BULL, 
            0x0E2E785202814EB9ULL, 0x5FDDABD6E72FA554ULL, 0xDB40232E00451436ULL, 0x17BF2F2B03A740B9ULL, 
            0x464A2820814E63A6ULL, 0x6DAB833344B5B942ULL, 0x49DD03808F80691EULL, 0xDEDEE08F0B697EF9ULL, 
            0x1A76570FB6735B21ULL, 0x46642ED7E08AF9D1ULL, 0xB323568CA109D5F0ULL, 0xF608364BAAB518B5ULL, 
            0x090BCD3D601BFC72ULL, 0x87628303DAC890C4ULL, 0xAD6DFB5CF6F5E363ULL, 0x3EE9C4216439BEA1ULL, 
            0x8B05865FCB8B0548ULL, 0xA9AE0B1C895B81F5ULL, 0xD43D8D4EAD823534ULL, 0x490F32BF7A82AC2DULL
        },
        {
            0x533739577B436BF9ULL, 0x38A149C4AB62CD22ULL, 0x6595709EF8BE6301ULL, 0xB1CA8D1F77D80702ULL, 
            0xD6C54836ACC54E63ULL, 0x101FFCC4B31B2736ULL, 0x35716484C04118BEULL, 0x485567883FF575F6ULL, 
            0x3CC24A0E4982A6F4ULL, 0xF497A63C3F2680FBULL, 0xE904A1EF1FA6731FULL, 0xE3A671C63648F063ULL, 
            0xACEB71F3CEB6FF0BULL, 0x9903E7BF221840A1ULL, 0xDA838E8B99BA8FD9ULL, 0xD8AA44D934E0020EULL, 
            0x47A086D8D5224D6FULL, 0x51F9DF8C5EF8AA3BULL, 0xA15EF2D084B483AEULL, 0xFA148268CD13A6ECULL, 
            0x59B25C76ED228614ULL, 0x41F764B3822349EBULL, 0x93AEE3F7B55924A0ULL, 0x1F84037F324E0238ULL, 
            0x168333336B116A13ULL, 0x7AB13C37CC136E53ULL, 0x85AA9EA7F3D2FCC9ULL, 0xF07C320014BE9157ULL, 
            0xA738A168FD939FCFULL, 0x9220CC617882CE33ULL, 0x6120396CCA9EA7F4ULL, 0xA8A6AB9F31C49356ULL
        },
        {
            0xA9EFACB4FE1B3A4EULL, 0x84681DB43D5E1EB4ULL, 0x9C3766C913583C08ULL, 0xDA87C1BC7E3C6AF3ULL, 
            0x5AA456ADA5B4AECBULL, 0x00F88B81419F462EULL, 0xF8AF4687A440E8A6ULL, 0x3E9F343B52C4BE24ULL, 
            0x035BDB9867DE3775ULL, 0x1BFE1B9825D5DC05ULL, 0xE00F03A30F1249ADULL, 0x782548DBFDB0260BULL, 
            0xB93EBF71A6DE93B1ULL, 0xD9A48A63B785B05CULL, 0xDFF7EF32371AD1A3ULL, 0xC1978086D95EE2BEULL, 
            0x3FA49F0E14C25CE8ULL, 0x401A2CF50038FB09ULL, 0xF77AE578CCA5E697ULL, 0x78873923C9A64971ULL, 
            0xC25080595B5EED18ULL, 0xA194C50EFCA1762BULL, 0x777624ECDB138CE4ULL, 0xC128932EB35CB1A8ULL, 
            0xDAB8929020901C37ULL, 0x1EC202524EA84679ULL, 0xD90C8464797070CCULL, 0x4007C05003EBFCE7ULL, 
            0xEDA01BF0012600A8ULL, 0x5D4AB02D1360C4DAULL, 0xDEEE7C4235BE9D4EULL, 0x530E42139EF241FDULL
        },
        {
            0xA24D92B6D80AC0D0ULL, 0x7F075CFA92A92187ULL, 0x3BE503C1C013F463ULL, 0x9AD962258F1BD0C0ULL, 
            0x47F09F28A55068A8ULL, 0xF086CB7F1787F8EDULL, 0x35841AED9E1C8CC6ULL, 0xC4539AB0BD0EAF8DULL, 
            0xC56279CFC58B5276ULL, 0xAD45BDABFF39EEBFULL, 0xB97531E378A1E343ULL, 0xFBDD6932A07D3269ULL, 
            0xF5DF0DEE5F882559ULL, 0xCCAE3406C959A087ULL, 0x6CEDF9F633DA1E15ULL, 0x91006307D1BD5B1CULL, 
            0x8D23B5C0641264E9ULL, 0x144C67FF6C6D2B83ULL, 0x94EC9E5CF8C7A1D3ULL, 0xBA7A09F45FDED708ULL, 
            0x199C0AA707DA337BULL, 0x08519AC8DC7574BFULL, 0xFBBA31F34A817529ULL, 0x1DB1CDCB3A80A4E0ULL, 
            0x5E08EB6EE8A8ED15ULL, 0x37356DDB3A9223D4ULL, 0x9FE0904E67A2AFF6ULL, 0xF51BC769EA22CDEAULL, 
            0x788A71A8E48806AEULL, 0x2B3B534DB72B225FULL, 0x92D82959906E3CE7ULL, 0x32B72A74F2BE07F5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseGConstants = {
    0xACA741CCE178EC8AULL,
    0x5DB4FA6CB0334323ULL,
    0xEF49182A57D8A1B8ULL,
    0xACA741CCE178EC8AULL,
    0x5DB4FA6CB0334323ULL,
    0xEF49182A57D8A1B8ULL,
    0x151B698813CE13F7ULL,
    0xB6C1FA2FA2695876ULL,
    0xA2,
    0x64,
    0x9E,
    0x22,
    0x4F,
    0xD4,
    0x21,
    0x45
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseHSalts = {
    {
        {
            0x455F4046EF597429ULL, 0x59184E40C88BFAFBULL, 0x8FDFC33A5FDAE938ULL, 0xAD5341322439A39CULL, 
            0x7E4440EC8D74FC94ULL, 0x34EA9E0E5998A857ULL, 0x778E53094790D009ULL, 0x03959369E3C43D85ULL, 
            0xF041A5697E5C9982ULL, 0x7308FEB1FB89853DULL, 0xB385C7141584F066ULL, 0x903ECA819CB71C6EULL, 
            0x5F3D0A710DE40C1EULL, 0x7D49C8CC94FB2B4CULL, 0x5C08FB4E31F1FC08ULL, 0x7B3593E36A3F5C32ULL, 
            0xCB17B1415A00332BULL, 0xB03CAA5974B26DB4ULL, 0x4A3C914EBD2BB890ULL, 0x89568FDE024B46B0ULL, 
            0x99B2A9D8A1769E50ULL, 0x00286C6CD68DF1DFULL, 0x5FA2BE10706B6A87ULL, 0x55BE2E031DCF989AULL, 
            0x17B48EDD12C0D113ULL, 0xFD9272550205DE6FULL, 0xEC8BA9BF60C4C234ULL, 0x088737800AD49F42ULL, 
            0xDEA1093B9BB9DFE0ULL, 0xFF28C40B8B8AE7B6ULL, 0xCB094030329CF94DULL, 0xA7727C48D95CDFC2ULL
        },
        {
            0xA870E1E7E00D0188ULL, 0xECA52F26F9C91D7DULL, 0x9229F20B0B436FDEULL, 0x3450701303234723ULL, 
            0x1689DF560079F2F4ULL, 0x9C7854333EBCF898ULL, 0x91387B6C84EA3382ULL, 0x3BDA2CAD803ABAE4ULL, 
            0x0D75582B7927B3E7ULL, 0x9FC7DAD60413D25AULL, 0x365D58210667D154ULL, 0xD3ECD9A6492AE31AULL, 
            0x1E39744F24B0371EULL, 0x8974DDED3FF53A48ULL, 0xD7293A8D9F14ABD8ULL, 0xD9F5743AA53A2BE0ULL, 
            0x784165DD6B2C454FULL, 0x84016E62CCA70660ULL, 0x2798D029B8E566A1ULL, 0xFD13625B855332B2ULL, 
            0x26B0466FE210F92DULL, 0xAEC10D3C52DCDBD2ULL, 0xDD58B6FC3CB211F0ULL, 0x3E3F29E008494CFFULL, 
            0xB1A947EB7002D9F3ULL, 0xF00EF751AC78F2AEULL, 0x6CF246A610E42901ULL, 0x28D67789E2A95270ULL, 
            0x9E1F389AAC25F1A3ULL, 0x00C7F632A59B2AEEULL, 0x15FA70B025FACF56ULL, 0xA7EE1F145CB024FFULL
        },
        {
            0x7E21140F367BECBAULL, 0xAAEB76F0B4D6DFF4ULL, 0x056D031F04C566C4ULL, 0x4544FE6D2A0FA0F5ULL, 
            0x30D0F7D7436EC533ULL, 0x47D1FBF5CC34F331ULL, 0x616683DA3F190089ULL, 0x0BE3D3C2093CC485ULL, 
            0x7F59A32CFD870EB1ULL, 0xD84A4E9A04DE1857ULL, 0x9DBCE3DD22070087ULL, 0xCFC92659320A3EEDULL, 
            0x2A3716EA8CD8C51CULL, 0xD234448A1E1B50EDULL, 0x21B897547A0C843AULL, 0x1A145008650AA8F8ULL, 
            0x952A7A0EDCBC0013ULL, 0xD4706DB365C3B3A5ULL, 0xDB44A419495E7518ULL, 0x97D11956051074B6ULL, 
            0xD48C34225F374751ULL, 0x84DA22DAABC80F59ULL, 0x3D042544A370421DULL, 0x989F18B4C879AE4EULL, 
            0x80ADA0B0622A585FULL, 0x0662E22BBDB2BC69ULL, 0x157A338E366DC531ULL, 0x82FABCE731D46DA9ULL, 
            0xC5124C145AD3D0EEULL, 0x9A88CB14BC2F7485ULL, 0xFE5724F514A05AC3ULL, 0x193A067454A8E4C7ULL
        },
        {
            0x439A7E3BBF0DB07DULL, 0x560A5ACDD95B74A1ULL, 0x5CFFB49D2AA3883AULL, 0x979F7B23E27841EDULL, 
            0xE71D043A9CD299FAULL, 0xE7285C3DBF898F68ULL, 0x6BA5852AC92B8CCDULL, 0x67836B37A946CC0FULL, 
            0xD0738CEBACC4FB7DULL, 0xF60E71DCE3887D6BULL, 0x870829BF3A5087EBULL, 0x17C29F3E8FC36FD6ULL, 
            0xAFC08579A781521AULL, 0x478F372F2FC67892ULL, 0x3CD9675E3ED0E36BULL, 0xDBBE854E2B38ABF3ULL, 
            0xC5C8A4471A73E5F9ULL, 0xCA19B8FD9F9435CBULL, 0x2B22F3EB93A5FF84ULL, 0xBE3F25B85687C97DULL, 
            0xDB2924C2C65FCB53ULL, 0xA661777D9865ABC1ULL, 0xE00C401957FF2923ULL, 0x663AAEEF0E02DE8EULL, 
            0xE7E2F671207749E4ULL, 0x8A26B7B1192B8A15ULL, 0x394C4A1873BF4688ULL, 0x770240EAEAFF3AF8ULL, 
            0xE9488317AAD564ACULL, 0x6FF0396958655688ULL, 0x5B60868D217AEFE5ULL, 0x8A77C589EA881F15ULL
        },
        {
            0xC22E1167A7F2E415ULL, 0x7FCA50019A26EE6CULL, 0x7BDE66F836597CAEULL, 0xB2B6F0ADA84B5FBAULL, 
            0xAA61DBE12A7C7E37ULL, 0xB023F29A5615C5BCULL, 0x289DA4073BB7FCEEULL, 0x6B07B0DCF9689305ULL, 
            0x773E1BE746BBAD5AULL, 0x13447442E7A89EAAULL, 0x381BA5F38C540B0AULL, 0xD88451B2FA05C23DULL, 
            0x30DE5BDEEF74BF90ULL, 0x939318E5BF6022C5ULL, 0x625F70FE39D31B25ULL, 0x168D2DA9171ED125ULL, 
            0xE1424C2A9B242A65ULL, 0x345574864ECD8125ULL, 0x8D14CC0EEEF7B826ULL, 0xF8B29D829C11F35DULL, 
            0x3B95995370A85EF7ULL, 0x7F1490E62466F09BULL, 0x892D47E5E44DAD96ULL, 0xA3855864D8EB91E0ULL, 
            0xF07BA4C0DFB32F6BULL, 0x82D1E0768CFB2A10ULL, 0x02B6CBBA638DE551ULL, 0xEC7EDE101E67F0DCULL, 
            0xC1C85671B725861DULL, 0x45AEF13CB2B0BDE8ULL, 0xC6CB922D3450F1CAULL, 0x15260A04D9C5C782ULL
        },
        {
            0x90F3BD399A0A8A1EULL, 0x2A3DB3452B42DC78ULL, 0xF736D3E93F65A279ULL, 0x4400B1DA51F625DBULL, 
            0x59E2B01FDA8F4E18ULL, 0x5E1DBE569F882422ULL, 0x893C495579B69572ULL, 0xA50AACAD0C80F11CULL, 
            0x4319380FE5D2DD74ULL, 0x922EAD1097FBB781ULL, 0x1AE3055BC1EEEB15ULL, 0x6494BDA265651720ULL, 
            0xFCDE895FE8DCAC70ULL, 0x33D9C516D1E60CEEULL, 0xFC8D6852ACB6B375ULL, 0x109A44B9335A5615ULL, 
            0x5A5F046F6F75B6B2ULL, 0xE2046C9AA94E0424ULL, 0x925F86A46EB02C40ULL, 0xC0730089AB892CA3ULL, 
            0xB2174F832595CE2EULL, 0x4B75212DB7B672F0ULL, 0x6FD91D37AB139BDCULL, 0x6B3B661B0A59C2B9ULL, 
            0x3FB0052BC375F210ULL, 0x7264353768CBA1E9ULL, 0x832E80D753685FC9ULL, 0xED8F9FD82973C830ULL, 
            0x52E201EBB02AAD57ULL, 0xEADBDCC9F210B2EDULL, 0x7F56312DD0E10061ULL, 0xE48A9B79410AA903ULL
        }
    },
    {
        {
            0x4EE529CA6FC507F9ULL, 0xF86C3E136BE8EA80ULL, 0xA94F9D3E1B56125EULL, 0xC6B30135CF042AB4ULL, 
            0x59F030B794D3A71EULL, 0xB468C960BF9AB0B2ULL, 0xEF8ABA42780F901EULL, 0x4A6DB2DAD1B477ADULL, 
            0xA819D4273FF3CC35ULL, 0x0533E56E605C817DULL, 0xC80FC0EA54F5A3FBULL, 0x18A2698ACE674A30ULL, 
            0x4244B56C7F37FE3CULL, 0x2DD2D51C6B15FF89ULL, 0xBF9BFC01A3B614CCULL, 0x22A55209E82F5914ULL, 
            0x71F97DDAACDD6880ULL, 0xF0C91FA1731E3BCAULL, 0x7C18E5C356515D7FULL, 0x929EDE9BF0AD4631ULL, 
            0xA5F45F352FC3B231ULL, 0x0C788706A70361F4ULL, 0x84BCAA7CD845D0B6ULL, 0xDB90D20F88B6C435ULL, 
            0x09BF2F82C91C416BULL, 0xAE031F77B4FAA67EULL, 0x5311340D1FA1F3EDULL, 0x4ED715D34B6486D5ULL, 
            0x65E9438A06EE9F19ULL, 0xA36708B5D977F133ULL, 0x0A9581BBE80C4726ULL, 0x60436B654F9A30B6ULL
        },
        {
            0xEEB752D4C9D47858ULL, 0x3718C57B2A105C78ULL, 0xF1FC0816FD5146EBULL, 0x04B7F3B9CF3F174DULL, 
            0x31C16A101AE7F2F0ULL, 0x889BD6ADB964C7A7ULL, 0x8C3E4FC0B3BF2DA7ULL, 0x36005EA6ED374E4AULL, 
            0xF14AB07FE74DEB55ULL, 0x954767B37D5A597CULL, 0x30CCB6DF732984D6ULL, 0x1E01B1331FC754BEULL, 
            0x8958B913928A1A2EULL, 0x57EEC2C8DA50F5E1ULL, 0x7DB9A5630145108AULL, 0x7F5DAFD23065E1BDULL, 
            0xBADC8ACBED6360A6ULL, 0xAA1510A5F2838565ULL, 0x93716FEDADBADFDEULL, 0xEFD9D17D527E5E31ULL, 
            0x928872AC86B24FD8ULL, 0xFEB898E591960707ULL, 0x1DCA915CE45AA63AULL, 0x61A77026EF816EB8ULL, 
            0x6B915D600F60930EULL, 0x9F45FEB11433FB3DULL, 0xB1AB2613509C8987ULL, 0xD45FA8465DA801F2ULL, 
            0xED05218E7D9882ADULL, 0x39E61C585D257AB4ULL, 0xF11DEC2B9B0F81F8ULL, 0x43A2187DFB998677ULL
        },
        {
            0xA3C2E9033002E803ULL, 0x518F228D11C85869ULL, 0x25DFD8877661E106ULL, 0x17EC1988A897A22DULL, 
            0xF88F5B666D21159CULL, 0x40FB3DD142D915B6ULL, 0xE6DD32225A1FB5FBULL, 0xBCD311B2EC7A070CULL, 
            0x049D1225C43F8793ULL, 0x41AB42AF4102523DULL, 0x4F355955BEB0D964ULL, 0x7A280E359CA3664EULL, 
            0x991D7FEC035F606DULL, 0x8600AD1FA3EBC6BCULL, 0x34B03A854A39068BULL, 0x47D55493930FFE64ULL, 
            0x135E2D7C87377423ULL, 0x7263E71EF22301EAULL, 0x810CB9424F81571DULL, 0x1BF969DFE5042394ULL, 
            0x039BCAA922FEBB38ULL, 0xD36B2C9AC8031A86ULL, 0x32B6DDCB32FAEA56ULL, 0x55516307176F02BEULL, 
            0xB7674D74DA995D37ULL, 0x8AF01DA08BB99A5FULL, 0xFC14E583ACF726CDULL, 0xF5E4B03C9C5A8199ULL, 
            0xF02E32ED91EFB7DBULL, 0x9A2173A8F58D1CAAULL, 0x2E9A8899D601F389ULL, 0xDB8880872E250F28ULL
        },
        {
            0xAFD140B8ED734E2BULL, 0x126ECE0E60F4A42AULL, 0x762D4131A60EF3FFULL, 0x352293DF94E8DAD3ULL, 
            0x03652AAD5724064AULL, 0xBF91B388096FCE63ULL, 0x929215D013AE16FCULL, 0x06E741A0883BC7F8ULL, 
            0x92F9B54172E021FDULL, 0x6C7991516A0717BCULL, 0x651B99E7B54AA968ULL, 0x9F4FA533191A2A15ULL, 
            0xE57378B6857A0365ULL, 0x9384B04E11902FB5ULL, 0x6352972B5AFA696FULL, 0x7ED30AFE927995A5ULL, 
            0xE0ECBCE94AE4A881ULL, 0xB8108F504C05AAC2ULL, 0xAB7C2A989EBBD6A2ULL, 0x5AA86EED1EEA91E6ULL, 
            0xDCC6CB910AA8AE9CULL, 0xECE585B9E514E4E0ULL, 0x55356064EB08DAD3ULL, 0x383BF34273A23DADULL, 
            0x570E5D5F7B7DD0F9ULL, 0x6745EA6E984EEDCBULL, 0x3A7A1558A34F3624ULL, 0x015A5A8E5A3F7E34ULL, 
            0xE132DE719F609327ULL, 0x9C31B19327471757ULL, 0x69E178E1FDB2918DULL, 0xA5896B87905B8AD2ULL
        },
        {
            0xEB600D712E613BF7ULL, 0xB8C05F62C0D667BDULL, 0x7704703B6F087335ULL, 0xBACCBBF85B665D65ULL, 
            0xB11F7EDB9392C00FULL, 0x5FDAACD89636D59BULL, 0x67F7CE618503DE16ULL, 0xA383F3B37459C64AULL, 
            0x66A424671349E0BDULL, 0x9D41E4DB41C3B011ULL, 0x1F14971413E63C27ULL, 0x484A8F681ADD3371ULL, 
            0xE6642174766C0CBFULL, 0x7CA0E2F0805D8A43ULL, 0xD63B8B33509C05AEULL, 0xA54CE53730B1DA2BULL, 
            0x5CA645A1A0727E39ULL, 0x3BFE2665E07C0957ULL, 0xC0B9FD3B8C6BE872ULL, 0x035C23E7950A39B9ULL, 
            0x9BAC8E28B9249952ULL, 0xD0C16D6C0A2EBF69ULL, 0x6C7888AB9D4E0FFBULL, 0x5F8F34ADE834CDCFULL, 
            0xA47A9BEB74DBAB86ULL, 0x4370CD45DCD65C97ULL, 0x04F376BF1F2F9600ULL, 0x5AEA071545297237ULL, 
            0xE6C831ADB1C0962DULL, 0xDEC224C45E511EE8ULL, 0xFFEE0036122B8F26ULL, 0x81FE1AD93F547477ULL
        },
        {
            0x5A66D602D047E735ULL, 0xE6830C2FB5266CAFULL, 0xB8220CC8EDAED346ULL, 0x83A6F76347EB86ECULL, 
            0x369854E3703AF0ACULL, 0x3C2D29FB8BF0FD14ULL, 0xEB61869C85E2511BULL, 0xF27BC90C5011D2F4ULL, 
            0x98C6D6F48383A160ULL, 0xCE586291E2A8F05AULL, 0x5CBD4145CE2C2988ULL, 0x55CEC932F9ED85D1ULL, 
            0x4CD9A278D9BE786CULL, 0x5ADAFAFECBD77546ULL, 0xB6B60CC7D74A515FULL, 0x1745821A1D90A4ACULL, 
            0x78C626C70C19AA97ULL, 0x012F59C66D5A88EBULL, 0xE0B2313FF477DD76ULL, 0xF34FF0B19C7AB5BEULL, 
            0xCA7D71C7AAD932D3ULL, 0xE6577E1114332E63ULL, 0x7815F608D7C0511EULL, 0x0C02C2C96B5A061BULL, 
            0x4E5B3F6D4E6B8504ULL, 0xAD71DB0053570A17ULL, 0xAA392C9E458D32E6ULL, 0x97ADF47BDE924AB4ULL, 
            0x82BB0CD642EA3DC6ULL, 0x69C9401CC719640FULL, 0xE4A855BE2747A80DULL, 0xD492ACCADF9F7F03ULL
        }
    },
    {
        {
            0x3966B0D33F5716D7ULL, 0x690205CF4FFB3E13ULL, 0xCF0AF1AF8B882CB9ULL, 0xC925F6BF74459BEBULL, 
            0xD3A712F860F3DE80ULL, 0x69BB108D1CDC0B55ULL, 0xD8E44EE132157673ULL, 0x3632BC0A58027695ULL, 
            0xA573316DEC088AECULL, 0x9EB23A89E3CE4F6AULL, 0x9DA7154506788BF3ULL, 0x6B1DEF38FF4DA95EULL, 
            0xF7E7A120CB4C7553ULL, 0xCEF8A56AA26B7BF8ULL, 0x797589725B77565AULL, 0xC64A66C040C208F5ULL, 
            0xBDBECD17ED042321ULL, 0x700955CB47A29D34ULL, 0x6F2385EE5592C2CFULL, 0xF170E207F3E72757ULL, 
            0x10D70234A37EC578ULL, 0x0890D04C19B1A469ULL, 0xFEA6CDA5569FD656ULL, 0x9BC1AF4CE13ECAA4ULL, 
            0x1190EA78A8138634ULL, 0x260C6958E90B0A6BULL, 0x80B18BEDD5B00F21ULL, 0xAD2B907FCFCB3351ULL, 
            0x6D04034A21B4F58DULL, 0xCEBA46F7892B016AULL, 0x9A811341C8A336CEULL, 0x20BDD238B5F55BC4ULL
        },
        {
            0xDD88D5EB2BE2B370ULL, 0x94A2F5902596FA89ULL, 0x3B4945BC3868669FULL, 0x06B288DC3142331AULL, 
            0x94EAA21A3988F9C7ULL, 0x2DF171157B43023CULL, 0xC86FDBADCEFD82C3ULL, 0x824453CD9D81E6C4ULL, 
            0xE91F6EAD93AC90E3ULL, 0x0180AAFECD76A38EULL, 0x737D3FA331BE29CFULL, 0xBF98B5C8EE466BBFULL, 
            0x70EC60711048E442ULL, 0xA9FF135443E104FCULL, 0xAD17A333C9C13E72ULL, 0xCAE41D11E3968877ULL, 
            0x6711C294975D922AULL, 0xED6037E2EC5EDD37ULL, 0x32D22254ED74D1A6ULL, 0xBCAFF5E3A5F75C4FULL, 
            0x35C152364F674A03ULL, 0xE6ACC1FBAC4925EDULL, 0x75DD8DEBE3DEB4BBULL, 0x04C88746E933479EULL, 
            0x490F9A32572BC0A2ULL, 0xA20DCF7C5FDBAB29ULL, 0xE815E454A7AC2DEEULL, 0xE60FF73DDDAF915EULL, 
            0x64E631B99AFFC03DULL, 0x6914B60BF232148DULL, 0xA599BE28C0AF41AFULL, 0x2274F0A281A30939ULL
        },
        {
            0x6231CC8787B8754CULL, 0xC4C5BC9E22CD4221ULL, 0x48F214F2218B955DULL, 0x5BE9DC799D762C8FULL, 
            0xB2217B9EDAAB015DULL, 0xD622FD6B7A3F711BULL, 0x3C4F7E5657CEF5EBULL, 0xCF8A3180485AF2F0ULL, 
            0x828031DB60FB845AULL, 0xEC39491872ED0F65ULL, 0x41A3C4543B60C76CULL, 0x1A3BE10A8CA4B9B0ULL, 
            0x44E6D95C366AF8E0ULL, 0x79F0818017376B81ULL, 0xA9C11DA3CAA8ABBDULL, 0x6EDAEC61B499A7ECULL, 
            0x27C383068D70DFA5ULL, 0x44C55EA4951FA508ULL, 0x55D486DA773E4931ULL, 0x2D75DAA4151A1464ULL, 
            0x38B2FB44F80A982FULL, 0x9ECCA8347745566AULL, 0x9FE1FB4A43726853ULL, 0x0D0157BE3EE0D9D0ULL, 
            0x3D9DAC382CFC5975ULL, 0xCDFA8238CD097529ULL, 0xD1D2B50A4CB69DF8ULL, 0xBE82C0EAA3AD3B97ULL, 
            0xADAC8CF1B61616D9ULL, 0xE74C29435A6C74C8ULL, 0x7179999DE1986884ULL, 0xBAC11EE67A833C8AULL
        },
        {
            0x8CE9EDC71154E994ULL, 0xF1A2EC126B98677DULL, 0xEEFB52B84BD7E0E3ULL, 0xB820CE01F7E015EAULL, 
            0xB825E6C610A3E297ULL, 0x8465E9CE405B03E7ULL, 0xCF10EBE7FEBC4057ULL, 0x45E72D15D8DB3B57ULL, 
            0x63FFAF78558A38B6ULL, 0x49C914F8567AF6C4ULL, 0xB32F308A3D1D2AA0ULL, 0x7A7F85BE7CDC3AA5ULL, 
            0xA92E78FF9749AAD1ULL, 0x507F951DEA9A8142ULL, 0x708DCA9E7D3DB909ULL, 0x70A5C6A40D1D29D3ULL, 
            0xB12ECC45D1F440CCULL, 0xD054E3E3B6028A15ULL, 0xCC613B545DA1E6B0ULL, 0xBA4F3BC31222DE13ULL, 
            0x1BAC451CA67DD2F9ULL, 0x1824B34D1238B4E1ULL, 0x7E89D3FBE263D0D7ULL, 0x2CDE924D1DC3ADCCULL, 
            0xB17C7CFEDFA504BEULL, 0x787298C057799B55ULL, 0xD0629167FA00F8FBULL, 0xA4B0121F9C94E399ULL, 
            0x71DDB6A4A461993CULL, 0x43D9DE91188FEF67ULL, 0x5AFE2C67D0263E40ULL, 0xC83952402D420516ULL
        },
        {
            0xD534982629C83519ULL, 0xEB1D5536E36E4D9AULL, 0xCE9B7D016BFD36DCULL, 0xCE522458CFF7B597ULL, 
            0x1B9B0439247897BFULL, 0x9549E5E7F3056E0BULL, 0xAF0171AF58F1A3A9ULL, 0x0B34FCFA43146989ULL, 
            0x8CA93F875361BC40ULL, 0x5EE973F572BE1F9CULL, 0x8D44BDE9B7FA8AEFULL, 0x005E894BA4BE650FULL, 
            0xCBA263CB521E6C8AULL, 0xB70222452C4AFAF3ULL, 0x1A400070139945CCULL, 0x601DA75B16E99EF8ULL, 
            0x49B2456076B7EFABULL, 0xE813C929E1954CB1ULL, 0x06CD974954546E91ULL, 0xDD3FD01F841DB83CULL, 
            0xF358347F32D46007ULL, 0x083286594F21CE75ULL, 0xC241B7FE86197895ULL, 0xDCC3813602945BDAULL, 
            0x2A3E1405419E18DBULL, 0x18F10606D7855243ULL, 0xE2D809C0C879590EULL, 0x61FF970283D67D42ULL, 
            0x83CCE723F48EAEAAULL, 0x5C8EEBEA76AC55B0ULL, 0xB9607D27FFC768B3ULL, 0x8001135A63E427C7ULL
        },
        {
            0x931F6671F9ADA451ULL, 0xC9168D9D7B0ECD31ULL, 0x0747226FCB4EA93FULL, 0x6103DF6DCC2A026EULL, 
            0xE2547DEA84887E69ULL, 0x324C89148842596BULL, 0x7A788B4CB4A2349FULL, 0x4C78606860D4B49DULL, 
            0xA69F0B2557952F04ULL, 0x064EF15C95B23EC8ULL, 0x6D4BFD291A9490EDULL, 0x27364126FF08F76DULL, 
            0x64B0410E5667DFBFULL, 0x668ADCB678A015E7ULL, 0x3FED488AD20F34B7ULL, 0x6815BA78B804E999ULL, 
            0x4AA4E295CA1F1BE6ULL, 0x81CBA20E0C843A19ULL, 0xFF47D4B961B391F0ULL, 0x270EF5A3D11D9132ULL, 
            0x1F5F50D9FC406D40ULL, 0x84AD83058426A3C7ULL, 0xE06F61A41E363647ULL, 0xC627295E284A70FBULL, 
            0xA92F9A82FB2F8295ULL, 0x9B7387E1AB469460ULL, 0xE02D26118B3860FEULL, 0xA675DEB11E55A574ULL, 
            0x16B0BB74C208CCF4ULL, 0x8CA2717549855594ULL, 0x110C14B76D07E13BULL, 0x81492DC9F8BA0535ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseHConstants = {
    0xABACFEDE8D25E035ULL,
    0xCD17225AA0B9BD2BULL,
    0xBD48104172426951ULL,
    0xABACFEDE8D25E035ULL,
    0xCD17225AA0B9BD2BULL,
    0xBD48104172426951ULL,
    0xC09753BC943FC55DULL,
    0xEC7B79D5DBA2353CULL,
    0x63,
    0xFF,
    0xD2,
    0x69,
    0x8A,
    0x25,
    0x2C,
    0xAA
};

