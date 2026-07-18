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
    std::uint64_t aPrevious = 0x90D0B2299A4E379FULL; std::uint64_t aIngress = 0xFC01ED43A3CDAEB3ULL; std::uint64_t aCarry = 0xAEC87C9901689331ULL;

    std::uint64_t aWandererA = 0xB24A4183B1C47ACDULL; std::uint64_t aWandererB = 0xDCDCE6BD9CB7BE8BULL; std::uint64_t aWandererC = 0xCA5387BF639C828DULL; std::uint64_t aWandererD = 0xAC9964A21A1BFA1AULL;
    std::uint64_t aWandererE = 0xB6F6D64B550FF4B6ULL; std::uint64_t aWandererF = 0x8FF7F2A5A9D21142ULL; std::uint64_t aWandererG = 0xCD8ECA46555F5EEBULL; std::uint64_t aWandererH = 0x8BA55254701D520EULL;
    std::uint64_t aWandererI = 0xE8B15C80A8E3FF9BULL; std::uint64_t aWandererJ = 0xBAE6058B1EEBE6F6ULL; std::uint64_t aWandererK = 0xE56D5C54E03566EBULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13373964943131514610U;
        aCarry = 18185523968455518299U;
        aWandererA = 13229143823429031762U;
        aWandererB = 18101356653082755777U;
        aWandererC = 16660246914585185704U;
        aWandererD = 16003009508050356788U;
        aWandererE = 9467797497753328467U;
        aWandererF = 18101669569627960810U;
        aWandererG = 12757212525689864206U;
        aWandererH = 13177841733040420913U;
        aWandererI = 11092564553745871964U;
        aWandererJ = 12914510501740477588U;
        aWandererK = 11889836792158304420U;
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
    std::uint64_t aPrevious = 0xFAC80D39FA5F3AA8ULL; std::uint64_t aIngress = 0x9AAE300E48EA95F0ULL; std::uint64_t aCarry = 0xE7A6D878955696ADULL;

    std::uint64_t aWandererA = 0xE009A99076DB3D71ULL; std::uint64_t aWandererB = 0xF9BB98497C0EA59DULL; std::uint64_t aWandererC = 0xF3098BF069696FBDULL; std::uint64_t aWandererD = 0xC6399157BA554445ULL;
    std::uint64_t aWandererE = 0xF566846B4E1FBB72ULL; std::uint64_t aWandererF = 0xEAC7DA2A5AD5115CULL; std::uint64_t aWandererG = 0xE5DDCF9EE604D227ULL; std::uint64_t aWandererH = 0x88E0B9716DD8234EULL;
    std::uint64_t aWandererI = 0xAC1FA7A820D36A4AULL; std::uint64_t aWandererJ = 0xD87478BBF6264976ULL; std::uint64_t aWandererK = 0xAAC00DA5DBBCBA73ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18182544961574518904U;
        aCarry = 12892522156850673882U;
        aWandererA = 12197392899244376272U;
        aWandererB = 9822276566196979370U;
        aWandererC = 10545338364144567056U;
        aWandererD = 10833828700990361488U;
        aWandererE = 14504933693205125142U;
        aWandererF = 18180812411612910369U;
        aWandererG = 17311833717028205938U;
        aWandererH = 15848081425883166310U;
        aWandererI = 14810695949762397714U;
        aWandererJ = 11183784918664016874U;
        aWandererK = 12771256330522505216U;
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
    std::uint64_t aPrevious = 0xBAD4A8C15107C859ULL;
    std::uint64_t aIngress = 0x938EDCA4CE3E04CEULL;
    std::uint64_t aCarry = 0x9D7D81CE16A3FFC9ULL;

    std::uint64_t aWandererA = 0xD66A16D813680F4CULL;
    std::uint64_t aWandererB = 0xC01D577F94429B70ULL;
    std::uint64_t aWandererC = 0x83A4ACCFE555A6C1ULL;
    std::uint64_t aWandererD = 0x9A52370B4853351FULL;
    std::uint64_t aWandererE = 0xE1DAC678B01CE0D7ULL;
    std::uint64_t aWandererF = 0xFAD4A2442EBBD796ULL;
    std::uint64_t aWandererG = 0x970B8126FB4ED141ULL;
    std::uint64_t aWandererH = 0xF18414A8271F3B72ULL;
    std::uint64_t aWandererI = 0x873C84BC5007CFA8ULL;
    std::uint64_t aWandererJ = 0xEA021E9E11F0AF57ULL;
    std::uint64_t aWandererK = 0xF718A88443300CF1ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
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
    std::uint64_t aPrevious = 0x8DB200DF7F12F931ULL; std::uint64_t aIngress = 0x8A45DFAEB451CB07ULL; std::uint64_t aCarry = 0xD3D58208889B887AULL;

    std::uint64_t aWandererA = 0x84AECC71547FA44AULL; std::uint64_t aWandererB = 0xDBFD72A48422A388ULL; std::uint64_t aWandererC = 0xDC18883EC5F999A6ULL; std::uint64_t aWandererD = 0xD2F545763A3DA5BCULL;
    std::uint64_t aWandererE = 0xD31BAC3A33619686ULL; std::uint64_t aWandererF = 0xB6D86374BC93B069ULL; std::uint64_t aWandererG = 0xB329D89547FE8C8CULL; std::uint64_t aWandererH = 0xE10BFD73F7F51BC7ULL;
    std::uint64_t aWandererI = 0xFF0762FD3B4E02C8ULL; std::uint64_t aWandererJ = 0xB18F74B61B93A789ULL; std::uint64_t aWandererK = 0x99C955B2164EC4CAULL;

    // [seed]
        aPrevious = 10065430247010479776U;
        aCarry = 18333359429891234963U;
        aWandererA = 14133552783022715019U;
        aWandererB = 13819844235819771835U;
        aWandererC = 17323061320078697084U;
        aWandererD = 14897528266825557844U;
        aWandererE = 16011648405357368900U;
        aWandererF = 16603157524485537080U;
        aWandererG = 9776557403807243058U;
        aWandererH = 10728318146936134880U;
        aWandererI = 14727753784892735205U;
        aWandererJ = 16512455190988703492U;
        aWandererK = 14023379588947779684U;
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
        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
            0x1348AE8270B38F65ULL, 0xF694BB6F2BB6AA91ULL, 0xB93104B01A592B3FULL, 0xCBC6E2D0F21BC343ULL, 
            0x96E8FD2FAF053745ULL, 0x21BA1B579C5BABB0ULL, 0x00C150AB2CA7C590ULL, 0xD434D57820956711ULL, 
            0x2722EE142C3481D8ULL, 0x1B705A00326B71BDULL, 0xBF738045D2062477ULL, 0xD6D77C661CA19F23ULL, 
            0xAAA365D1CDF09AEFULL, 0x2CD12E5CD2D6B1FFULL, 0x33DD5BC5663F61F2ULL, 0x42AEA930EB92F0BDULL, 
            0x10AD3EDD32B15036ULL, 0x4D34CE82141B0A38ULL, 0xB12F722F06E9A61FULL, 0xE920B74565800BC1ULL, 
            0x578B5591188D945BULL, 0xC6BD99DB1CC22023ULL, 0x734C1EAC34744D26ULL, 0xAA4806C7EE08BE8BULL, 
            0xEED73DE1DE9DEED5ULL, 0x17336D9F7A5906B1ULL, 0x68D3571CD9A58DA2ULL, 0x04404E162640B975ULL, 
            0x240243B9E7DCC64FULL, 0x51973361B46CF683ULL, 0x1F75D49F12D0EC83ULL, 0x30E316BC6C8E3310ULL
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
            0xDB4B320052164789ULL, 0xB61709F87D336B71ULL, 0xD0021191797168F4ULL, 0x8C0E251B3D404518ULL, 
            0xEEA7A9DBB1BA1511ULL, 0x66DCFB9CB4C0EE1FULL, 0xDF4844C748EF1551ULL, 0x4893E99133349EC8ULL, 
            0x9FEF47CD36801A8BULL, 0x968DBC9B5F40102EULL, 0x2E7D305B36D11FA4ULL, 0x3EED4F3636DF4DFEULL, 
            0x8E37AF92AEECFBBFULL, 0xABFA39708B8AC03EULL, 0x06847FE1FC235348ULL, 0x50CEE62CA182E6CBULL, 
            0xCB18B9E953E9A980ULL, 0x53988844D0FD23C2ULL, 0x008E75CE19D1F518ULL, 0x4A710AD7F5A49C72ULL, 
            0x3B8D5900E203679DULL, 0x02AE0755B2F799DBULL, 0xEF1E89AA7D7065E0ULL, 0x085CADBA5550B9A3ULL, 
            0xCB983E105F73E52BULL, 0xEB8A0C253C7A8FF0ULL, 0xCE05EFBC78273581ULL, 0xEA6ACB8D0A00A095ULL, 
            0x0C7FD39C490BBDD3ULL, 0x83C12033DF8BADC0ULL, 0x38491AB6BF104DF3ULL, 0xACD07B96121DE798ULL
        },
        {
            0x158EE65CBD3EDE5EULL, 0x553CF6F185B15154ULL, 0x8FE939DBBC707F1EULL, 0x9177628A6BD541A0ULL, 
            0xBC92CBFA341525F0ULL, 0xF7DA08268F8A108BULL, 0x8A756FCA2CF5F761ULL, 0x1EFEFDA7C4371A9FULL, 
            0xA5B64F97F7C933D7ULL, 0x25D4B17F47C3625EULL, 0xDB255B1CCF34A806ULL, 0x25A759CEFE50DC6AULL, 
            0x131E52955D53BE20ULL, 0xD0E4426E21D1EAD6ULL, 0x5BF1D6AE71E09836ULL, 0x941D691C19EA361EULL, 
            0xF2636C332425F88DULL, 0x6F2AF00DB2733791ULL, 0x398DDFE78755129CULL, 0x7706CD48E920EB15ULL, 
            0x874D813821DB584FULL, 0x4FC300F3A0EA2EDDULL, 0x687093357B3D1EF6ULL, 0xE0B0517578F4C496ULL, 
            0xE3921C00077F3027ULL, 0x553B5BC3E43877FEULL, 0x252D835672BE98E5ULL, 0x24286C08F6C801D9ULL, 
            0x36C84A69E0B827ACULL, 0x389D98EE22875BF1ULL, 0x9BFA74A95577BA36ULL, 0xCD81D487B9103ACFULL
        },
        {
            0x0C565F9B68AB1A0AULL, 0x7A9EBE7701441142ULL, 0x7D4E0BC0EF511792ULL, 0x95215CA834ED8AA2ULL, 
            0x94C2BEFC8CA6095EULL, 0x3856939D15DE608EULL, 0x920D3139EE9C1161ULL, 0x01056409A2F25B2FULL, 
            0x143A5A97C4AE214FULL, 0x307FE0855D1A4E12ULL, 0xCD9A7973312FFFA9ULL, 0xE4288C6E9E7D22DBULL, 
            0xAED2B00CD590419CULL, 0xC274DA6282444B0BULL, 0x3833B8BFFD070F09ULL, 0xC5565203A1E22F50ULL, 
            0xC3459484BF873F68ULL, 0x7882065664481693ULL, 0x2FD1D807A5124D4AULL, 0x0AC2C7E3FF2BF561ULL, 
            0xC57C12F6778E6A22ULL, 0x880F4630F8227DE6ULL, 0x45B350C81568FFC2ULL, 0x6EFBF5634F444A83ULL, 
            0xB88983549A9345C2ULL, 0x819BA311F358AF83ULL, 0xA7DE9163372ADC05ULL, 0x65DF6C6C862152C2ULL, 
            0x6998BB9796FE11E1ULL, 0x28B6418111342E62ULL, 0xB7E4D6B5E1D50830ULL, 0x8E02BC7906AD48F9ULL
        },
        {
            0x641FE63882CF433AULL, 0x842A1AA61C95A7ADULL, 0xA40D34E4E75E3E8FULL, 0x1157A8AE1CC3332BULL, 
            0x70E96825ED750FCEULL, 0x40E4E08AB4FB57ADULL, 0x6B2DF8308FEDC70BULL, 0x6CF69AF653ADBD07ULL, 
            0x2741DBE5E1AAB7B9ULL, 0xE45705148F0363E5ULL, 0x30EE1B865FFD72BCULL, 0x6A7BDD8A640F36C0ULL, 
            0xA82A794466481C2EULL, 0x9ABF86AECFCCC8B0ULL, 0xB1A95C19865D3C85ULL, 0x44776BC2516B440AULL, 
            0xBA84D83CE83D085AULL, 0xF6F37E8CE65D55B0ULL, 0x4874222256C09AFEULL, 0x385CC3152F8C59B3ULL, 
            0x5707651928CFC708ULL, 0xCD80F6E5FC09DD7EULL, 0x48F553B34C00325DULL, 0x3098F1BAFD428252ULL, 
            0x6C474E92D4B0811FULL, 0xD1086012E6123C56ULL, 0x5BDEF57F97FA5DC7ULL, 0xF0C11FFC4F475EE1ULL, 
            0x2FC49A4AD5487EF7ULL, 0x3F05F40EA9B50D53ULL, 0xB79F7523BEE8CF41ULL, 0x8F1A63A944607B77ULL
        }
    },
    {
        {
            0x05042E23A8FFE031ULL, 0xF4679F127E403E96ULL, 0xDE1ACED9408F3E7CULL, 0x8E4BAFA6C4326885ULL, 
            0x2B7C624AF7DED3A9ULL, 0xFF6CB72750001FECULL, 0x7E78759C6249697EULL, 0x281E8A0E582F5B5BULL, 
            0x8E44803F7520C594ULL, 0x37769E5AF39C929EULL, 0x013BA5250456375FULL, 0x972110C037E9D26CULL, 
            0x99114145407BDBD7ULL, 0xB7D02C04ED5A1BC6ULL, 0x94B460BC7B4B44E6ULL, 0x11BFB15F731C5EB7ULL, 
            0xD392A37BCE97E291ULL, 0x0E3EF3CCCA18D64CULL, 0x18C471CF6F1A6194ULL, 0x88673AA36A96B749ULL, 
            0x3807D01A39B91A42ULL, 0xF2ACA5057F7BD9BEULL, 0x46FEBFEB5794CC9AULL, 0xF1EB4A407D59BF7AULL, 
            0xF5B010C52EEDFAA6ULL, 0x66B70F0D79791397ULL, 0xEB5A9D269C25134CULL, 0xFDCE34E83F5BC950ULL, 
            0x6D421688D46DEDB2ULL, 0x0D48E0157E8A4802ULL, 0x42BD63CE387A1166ULL, 0x50F94BD7185B1EDAULL
        },
        {
            0xE365CB1A89B92827ULL, 0x11973D32651A610AULL, 0x9E9F25827F41C8B1ULL, 0xBCDC5155937ACC98ULL, 
            0x69D75DA57CD817E1ULL, 0x9B00A8B517711833ULL, 0x3348567E5DB514E0ULL, 0xAC8B0C6FC9BD8C0DULL, 
            0xEDF33E8294674EC3ULL, 0x783394FE39B5D394ULL, 0x4F105DC7A2F43C65ULL, 0x1E4A5AF110A0FE3AULL, 
            0x994A0ED2F1233070ULL, 0x4B505072665FD67CULL, 0xEA16ED9878B1D079ULL, 0xC6F14C87A38DAD61ULL, 
            0xABF71F0CAABB2DA0ULL, 0xD27616413928318EULL, 0xFE91A00DE8304C3DULL, 0x1A643329FF627F69ULL, 
            0xF8F28DE066A4669DULL, 0x9D7ABF4028681A43ULL, 0xE1DFD344EE122D7DULL, 0x28A150EA8531621BULL, 
            0x64752BFB34E46812ULL, 0xD8FDECECE77F6389ULL, 0x9E2750ED2A59C191ULL, 0xCE5C37F09F98257EULL, 
            0xD6773C8409A7398EULL, 0x96C7548544490B0CULL, 0x4E322749130D8451ULL, 0x55D703378DDFFF9BULL
        },
        {
            0x11600FE1D250ED75ULL, 0x94BD758076AAA73EULL, 0x840467327E67AAB0ULL, 0xEAEF15B9266CEA94ULL, 
            0xF894548634DCB4FFULL, 0xFB7B9A3A57AD80BDULL, 0xEF5C7A789D520758ULL, 0xC6769689EADA8179ULL, 
            0x539D1270E3E9A1FFULL, 0x55A6808C2CE78C89ULL, 0x4E77B9AF856DE5D6ULL, 0xD2E68B0865D19357ULL, 
            0x000FE6C8A955CD6CULL, 0x9C6FD1613948188CULL, 0x441D3A4159525BB9ULL, 0xD95DE1D0B77D596BULL, 
            0xFCB7B085524948E2ULL, 0x6F5F93D68DAFD784ULL, 0x2E8DB3809974CA5FULL, 0x51B65C6DF1266C1FULL, 
            0x8DF5DB98BBBB247BULL, 0x54277ECED5DC8E56ULL, 0xA008121A2236358DULL, 0x1350EDF88380B9D9ULL, 
            0xB55C1083AFECE7A9ULL, 0xE71CFBDBA6D43E7AULL, 0x28B5E0BFB185BFBAULL, 0x172727ECDD28EC67ULL, 
            0x2211202EBEB7BD36ULL, 0x02133A95F20358DBULL, 0xA20BD2EC53B1C707ULL, 0x292C67F2B43DAD36ULL
        },
        {
            0x38D3CC0F5BFB6DB3ULL, 0x0588A864B4851F34ULL, 0x39F529B798F477F6ULL, 0x54FE2787D0851BA7ULL, 
            0x8CBDACBF51F5CD0EULL, 0xD6C153F139FBA3F6ULL, 0xE78E0975A99AFF48ULL, 0x19E2AB16467E2887ULL, 
            0x35668E2F2E4F6293ULL, 0x2C94076D8EB888D7ULL, 0xED28994C4AA1EB19ULL, 0xB051FA50ABC492ABULL, 
            0xF90D96197CC67C49ULL, 0x0F187ACB97C7147BULL, 0xA8925331B4A62913ULL, 0x2BA24C3107EB5C2AULL, 
            0xC4866FFC8966C911ULL, 0x2C245AB2D906C214ULL, 0x0FD54799625AEF20ULL, 0xD9C2D70B322B5E55ULL, 
            0x49B3E74FD602F5B7ULL, 0xA0ABC11FC17A57C9ULL, 0xF6134FA940C1BF07ULL, 0x84B071AA85E69700ULL, 
            0xB0A7E5A6F797C1ADULL, 0xFF59390F5CE3CF06ULL, 0xD6E004C0C0C638B1ULL, 0xE5FB168BC1DF2AA1ULL, 
            0x3877D33A5A6F0FF7ULL, 0x0E379B6F7552726BULL, 0xFBDF569FFF232380ULL, 0x33BAD0E9BD78B3A7ULL
        },
        {
            0x083D90AFAB708A48ULL, 0xE7DDC0C709CFFDE9ULL, 0xC7E1CC3195518911ULL, 0x85EF52952D6044B4ULL, 
            0x1D591D825091C273ULL, 0x7AEB819B312B7998ULL, 0x322341203C320E9EULL, 0x04019D018A8EDF68ULL, 
            0xA29F02284CFE9BC7ULL, 0xA1DF2A2522579070ULL, 0x14114876CB61FA92ULL, 0x4BD435E8F15B1A45ULL, 
            0xED49FBCDABED2BC3ULL, 0x0426FF2A6072FE56ULL, 0x3F356AED07BE0CFBULL, 0x1285617DA47499B3ULL, 
            0x78EEC12B1E168996ULL, 0xA45915F8D9522F9FULL, 0x11669327136F75E1ULL, 0xADEB3691F3B98E04ULL, 
            0xEC318F0464482A8FULL, 0x201E43DDE099C69CULL, 0x7AA3D2D0A244937FULL, 0xF7A28BC605F9133DULL, 
            0xE651C249312BA0EBULL, 0x3289C35487EEF146ULL, 0x262B555890F1B92AULL, 0x41159C359F19A3F2ULL, 
            0xCBF28D67E6038B46ULL, 0x86F9CE6330283ABBULL, 0x81CA23CDF0E37321ULL, 0xC75C1764BC7C93DEULL
        },
        {
            0x7DF68F9147FF79E1ULL, 0xF0E69244D981862FULL, 0x34EA52A313312194ULL, 0x08951C925BCEEAC3ULL, 
            0x822C7F99E18387C9ULL, 0x5EFCC7C914551E22ULL, 0xDB0F020C63F63215ULL, 0x3FB203415C706A90ULL, 
            0xCEA213CEB503FD67ULL, 0x0C48E71DFAA5902EULL, 0xBE83A787AE63DE14ULL, 0xF79B82323F9F294AULL, 
            0x6F4398883CB2B48BULL, 0xF792B7C367E2B4D2ULL, 0x0C1290BEC4F6A556ULL, 0xE1771DEFB1A1C8A2ULL, 
            0x17CE339D7FC35D32ULL, 0x661229157332C1D3ULL, 0x03C234B152C005F1ULL, 0xD70072C26490F7B9ULL, 
            0xA3F76C3AA8BC3347ULL, 0xFF2F348F43CFA9A0ULL, 0xB065782670A7AB4AULL, 0xDD24817D583839A0ULL, 
            0x146F9B458614AA83ULL, 0x697FE72D639B358DULL, 0x001027AA536503A9ULL, 0x62BF1A6709160D20ULL, 
            0x5AE439624E33628BULL, 0xD20A948C7209E0CCULL, 0xFA88AEB7261DAF1CULL, 0xF97DABDA9DD59165ULL
        }
    },
    {
        {
            0xF290148784C1DDB5ULL, 0x4A211A66046C1B0EULL, 0xF41B269E4DE9557CULL, 0xA5A0F89A442CD57FULL, 
            0xA0DFDBF3FECD1CBFULL, 0xB95F58300A2B2FFCULL, 0x3426463D9215AA0DULL, 0xD04BC027AA97314FULL, 
            0x5588ACF3B3520AF9ULL, 0x0BCA5B12F3458470ULL, 0x5292BB18FD6E99F8ULL, 0xF96375EF287B7C1AULL, 
            0x4CE7ED58978FF2AEULL, 0x221085459F0DE085ULL, 0xCB55FFC00960E1A0ULL, 0xFFFFD7CC5A7F76BFULL, 
            0x685117E1619E766EULL, 0xF17342177D977A7CULL, 0xBD9E0471013EA748ULL, 0x73D187D50298A91FULL, 
            0x53A0D37F0839066AULL, 0xEC45A3826A66AB9DULL, 0xC7988C276FD10976ULL, 0x15DB45E82F185F6FULL, 
            0x1642EBB74F952611ULL, 0x6569CB8DF0492B2FULL, 0x9B00740DFE33453DULL, 0xE176C71A31C5C8B5ULL, 
            0xAEB75EFBE730AC20ULL, 0xDA592B4791CDA385ULL, 0x9E0F083D409066A9ULL, 0xC83807C6A5BCB1AAULL
        },
        {
            0x6ADCE6CC546A675AULL, 0x877F8130B37487D2ULL, 0x1096A053263BE556ULL, 0x53FC4E62BE6CC9F0ULL, 
            0x1C19FF765D158F3BULL, 0xF3DE9CF3E5AB1978ULL, 0x05030A5772CE369BULL, 0xE3F16E28D42F5110ULL, 
            0x847373401598F42FULL, 0x10FB60BB476D0B97ULL, 0x67EEFFF19B58E284ULL, 0x93FAEA3C1CB8970EULL, 
            0xA8E3739D0139C04EULL, 0x435A231A24D7238AULL, 0x65EB8A827547BB73ULL, 0xA5D7C7F8F7CFD2D5ULL, 
            0x9C7BC415B9CF0F02ULL, 0x1B6FAF7511E1A933ULL, 0x06582A2A34CF84A0ULL, 0xBDD2ECB701E7CBEBULL, 
            0xC3EB6288398DB5EBULL, 0x647B1BB32E52441BULL, 0x01BF096E25BD06FFULL, 0x4E39C3A3353D1109ULL, 
            0x9F81DDADB0DDD540ULL, 0x8F4B8FF4C2AFB035ULL, 0x941F70C1130A803FULL, 0xB17433AB93913AAAULL, 
            0x071ED01CB6203E90ULL, 0x78DC99FCF5AF1F03ULL, 0x7BD2E15C3B6AE605ULL, 0x77F1BE95BF9500B3ULL
        },
        {
            0xABD41F0507B32B8FULL, 0x46BFBE64BDF8437FULL, 0x9A47AD8059357455ULL, 0x6CFAEE4843058F8EULL, 
            0x2C72F0AC7FE22AC4ULL, 0x12042BAE0A8F697FULL, 0xA4250FC3FE2583DEULL, 0x845B399965C5CE41ULL, 
            0xFDF50EC266FD5737ULL, 0x50F9661AA06629DEULL, 0x9D15A470142F9E74ULL, 0xA405BBB4BD49EB3CULL, 
            0xB0E3025E4DB873ADULL, 0x0203C7EB321F04ECULL, 0x01CD13485C575C38ULL, 0x025B3C2DD26D971BULL, 
            0xAED805FB649FA1D9ULL, 0x6E1C59354E76B516ULL, 0x6E04F4E71307EE84ULL, 0xA237D2225A81184DULL, 
            0x91F9BEF514E5AFE5ULL, 0xF2048EC07E731219ULL, 0xE3F2304E53A4FAACULL, 0x014E48F85A95A4E7ULL, 
            0x6D8346EF421DBDDCULL, 0x4CD1AD1A27637BD3ULL, 0x7E2E3355F599A36CULL, 0xD94E2CDC5A77D322ULL, 
            0xF40663834D4D35D9ULL, 0xB584CF2F1D164C41ULL, 0xD109CE46A5C77765ULL, 0x69C5DC2FEC6DA31EULL
        },
        {
            0xCA62B95F6B8BDDF7ULL, 0xDBCF59A31A17776BULL, 0x006DA6F222103E02ULL, 0x4630A64B3E52F8D3ULL, 
            0x2C97C4E0AF49AD9BULL, 0x97F72D3B93C60221ULL, 0x50CC2898E4ED7040ULL, 0x080BC5864E1D3CD0ULL, 
            0xCE8E096A270D43D7ULL, 0x6151E983A3497DF3ULL, 0x04790FAE20B9E6A6ULL, 0x94BD1F895AF7E951ULL, 
            0x1453D18D0DB3AAF6ULL, 0xBF870D3C861BA271ULL, 0x7F95AF0CEFDD900BULL, 0x69D53EDDC0905F0DULL, 
            0xBF186FF5FE42E8A0ULL, 0x8D35E02F727209A1ULL, 0xBCFBE28B9D4D66CCULL, 0x333557A500D69889ULL, 
            0x3323AA2DA6EC73BBULL, 0x0F969BF9FEA9B689ULL, 0x21ABAB47B64D21A1ULL, 0x2B60A8C1C3D774B3ULL, 
            0x440D0D54FA3743CCULL, 0x1099B7F713BEBBFAULL, 0x0D3B18F754AB986CULL, 0xE7F3E944F7DED162ULL, 
            0x03AE1CBE26A6D9F5ULL, 0xB673C7E927D85190ULL, 0x27527F823F2808D9ULL, 0x6E795FA46FF68F8EULL
        },
        {
            0xD933CA451CCF87C6ULL, 0x991DE08EECDCBA8BULL, 0x552D963A5BA96AA8ULL, 0x5E4F0D9C4814D27FULL, 
            0x1D634EECF281C501ULL, 0xD6660C177B6FB08CULL, 0x8197750D2276FEDFULL, 0xA975E8DD5A2861D5ULL, 
            0xE9D5E6ECDD0A00FDULL, 0xA9F8B9EC2AB69623ULL, 0x6C88945EFCC6F6A6ULL, 0x242FD32F7CBBD6DDULL, 
            0x313CED58AF901091ULL, 0x3732B8DDBE1A7E34ULL, 0x615C4F54B33F7C2DULL, 0xA80C0B8976B88307ULL, 
            0x19A6C001B9915986ULL, 0x6F5B69A698B8E023ULL, 0x9C1FA65F9CE3457AULL, 0xBB3ED3FAC1E84ECAULL, 
            0xCA9B9D13196B03B1ULL, 0x03B7BFEAFB4109A2ULL, 0x838B93AEA078CA86ULL, 0x14C07673DFC5AC50ULL, 
            0xF96B799DDE500781ULL, 0x90956886A2F83134ULL, 0xD9C73CD346119A53ULL, 0x772436F5247F4661ULL, 
            0xC7884C1FA47FA2FBULL, 0xC99BC7275B5F3A65ULL, 0x2809B26B40C866D0ULL, 0xC64B29D52659F4B1ULL
        },
        {
            0xABD8EC89922A06BDULL, 0xC09B263B887D6057ULL, 0xDACF5426CC05B81FULL, 0x54D61B0C086DEA8BULL, 
            0xB25F15FE4BB5B944ULL, 0x3D7E78DEF8B61BBBULL, 0xDFBF6D3739560512ULL, 0xA04E88BCABAEA501ULL, 
            0x1F04C9C60DB2E5F0ULL, 0x73C8A6D2288D3CFEULL, 0x96DAFAC47E03E54CULL, 0x5E70F68BEB20351CULL, 
            0xB61990B13170B78AULL, 0xE1CFB54591D1C064ULL, 0x65AFB5FA42BC7F58ULL, 0x679BFCABEA629294ULL, 
            0x00A2D3D3033C95B2ULL, 0x0F484EB28EDB7919ULL, 0xB74DEF3A7D9B44C6ULL, 0xB533CA470635E65FULL, 
            0x0AEB2225EC326ED6ULL, 0x12549FE55FEA0845ULL, 0x350DBE66F28941E8ULL, 0x0B317FB3AB6D139BULL, 
            0x8E55E3B41834EEF0ULL, 0xCD960A5A11200404ULL, 0xECA05B65DFA0A764ULL, 0xFDADD537B62E0B2FULL, 
            0x510701B3AB08B690ULL, 0x200E232AFD415EC0ULL, 0x95FE871A10628B12ULL, 0xBC1E3C55A013C9E7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseAConstants = {
    0xB7E4C9BD5BAF7D29ULL,
    0x78606D56D5BED5D2ULL,
    0xB44A999BC7E38839ULL,
    0xB7E4C9BD5BAF7D29ULL,
    0x78606D56D5BED5D2ULL,
    0xB44A999BC7E38839ULL,
    0x2415D7EBB9304967ULL,
    0x00C97A55551C19CAULL,
    0x2D,
    0x27,
    0x0F,
    0xE5,
    0x3C,
    0x93,
    0x32,
    0xCB
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseBSalts = {
    {
        {
            0xA3205253B0969C11ULL, 0x48378577B74FFE1CULL, 0x7250873A867FDFBEULL, 0x2A2B955788059EA5ULL, 
            0xB157599DED2E6120ULL, 0xA5395A71E63382B9ULL, 0x858DF88E1038EAB4ULL, 0xC6D8752F49BE6D07ULL, 
            0x09BF569E97F793A2ULL, 0x2433FC302059ED0AULL, 0x8BA70F343170BC98ULL, 0xD2F06A509F0CD533ULL, 
            0x9FDD1F572454CE03ULL, 0x4002CD2D6F3843E3ULL, 0x53527227712023A2ULL, 0x8DBAF97668EAEC85ULL, 
            0x599E061B699271D5ULL, 0x8D4E2F818CCCBA05ULL, 0x1A947382B38FD8E2ULL, 0xBD56EF8FA6229649ULL, 
            0xD1D6DBB17E42CF40ULL, 0xAF5D33B486DC67FEULL, 0xDF1A3263818F3E12ULL, 0xD85714A196475E36ULL, 
            0xBF2EE8A94D375E14ULL, 0x850AF9F2B4F13A2DULL, 0x473E45F2F02BBC01ULL, 0xA799C3697B709B24ULL, 
            0x80D2B37ADCC9AA97ULL, 0xAE86C9F30983F5B1ULL, 0x30DFF763DE177CE6ULL, 0xC7D4D10F0F56A0A9ULL
        },
        {
            0xEE1DAFBC66260BD1ULL, 0x574D5135D0B6B9CCULL, 0xF732A8B3ED1C7B7BULL, 0xCA14F0204A297089ULL, 
            0xF9E1D6F9859C33F9ULL, 0x2619DB911D9F7692ULL, 0x20C4F03EA912023FULL, 0xB40DF42495C870F0ULL, 
            0x7B110806A7ADBDB1ULL, 0x186C49190999744CULL, 0xF5AE6656EEF4B3C4ULL, 0xBF05151798778CF0ULL, 
            0xEECD1241CB703128ULL, 0x8DB1427D4AC6AAF0ULL, 0x5E569870CC682CACULL, 0xE5EE651EEC9CC41FULL, 
            0x843020A3EB4BBE6AULL, 0xB1335DE4FCA401C0ULL, 0x647AF28F9D354772ULL, 0x1723B81295158A08ULL, 
            0x2D664EA187EDC311ULL, 0x4EBAC8DC9E56ED77ULL, 0xBC4F87F9FA561EB1ULL, 0x6F50795393A389EEULL, 
            0xDDC4E58B1E8259F3ULL, 0xCDCBF38E738FC5C3ULL, 0xE798E02B128459CBULL, 0x73E7EC855B4F4E54ULL, 
            0x75B4AA6C329B2B4BULL, 0x556EC63F2B49C98BULL, 0x8EE28A4F8B25E441ULL, 0x26D00DE426C412B7ULL
        },
        {
            0xFB4387EC159472D3ULL, 0xEE6813CA8940805FULL, 0x36152149F202D6CFULL, 0xE447363808CD687CULL, 
            0xA4A36FFB1A1FD66EULL, 0xC74A75BF7BCB9DA9ULL, 0x3E609B132D45EDCEULL, 0x0950E3565F201A1DULL, 
            0xAE02E720BF55E933ULL, 0x6C35B398DF155107ULL, 0x77909B5751F21657ULL, 0xBA2E2F5F9A62A911ULL, 
            0x9A55D5F5C2FD6D56ULL, 0xF511A988FEA41352ULL, 0x128404E073CF6C4CULL, 0xE0A8B702C242ED4BULL, 
            0x459898D0A90376A0ULL, 0xC7B1601DD6F6F70DULL, 0x810D9223565DE1BAULL, 0xDFFB91F8CE98B7F4ULL, 
            0x81B9E7FB3AEB668BULL, 0x88A9DA0199971E1DULL, 0xCE5956496CC96E5CULL, 0xDFF3C427DCBC5CDFULL, 
            0x73091D0877A01675ULL, 0x4A32DC491E52AB9FULL, 0x9DF6F24078E5BC3AULL, 0xDFCC706B666C034AULL, 
            0xF80552C37A5C0BCCULL, 0xF88A6F5C5DAF8AB0ULL, 0xCB9215CAA237A9A9ULL, 0xF5A1B06B8BA47D25ULL
        },
        {
            0x3999EBFA9312EE91ULL, 0xEE760DE621789E59ULL, 0x71CD756B06562003ULL, 0xF9699FC16D691293ULL, 
            0xF63113ECAE0D943EULL, 0xB090210EDC0AE789ULL, 0x255B7FD8964D3CDEULL, 0x744896079CBAA8E1ULL, 
            0x4AE29A66B9AFA62FULL, 0x069C9ACFF0B06431ULL, 0x7C540BB7CF90D17DULL, 0x83BEC3910D014BAEULL, 
            0xAE7AAE6BD66C4302ULL, 0xD6DAF78A40F54BD6ULL, 0x53B203C79724D873ULL, 0x738F6FA83A9606D0ULL, 
            0x4429875ED78956FBULL, 0xA4D222319C9EF401ULL, 0x319D025277A445AAULL, 0xD39B7CC732295DDAULL, 
            0xEAFF1D0980754D11ULL, 0x8D24DA3CF2FE1227ULL, 0x510F03AB57ACC446ULL, 0x748B816AC93D1EA2ULL, 
            0xB8F986A6B831B508ULL, 0x4CB959D91A35AC76ULL, 0xC7F5DFB768F9569CULL, 0x95B88535F851609AULL, 
            0xF70D0B41B93AB737ULL, 0x71A270002F6046ABULL, 0x086C2607ECD8BB3AULL, 0x78C0CE7096AB35BBULL
        },
        {
            0xE3CC5988E2404C5DULL, 0x016E1A35C5431036ULL, 0x5DD88FAD711B1BCEULL, 0x97A1834EDB50E81AULL, 
            0x06B9468948A85F9CULL, 0x40B535F80FA1297BULL, 0xEF9C9E1A9478D0BEULL, 0xF9BFC0C7DDBD9A32ULL, 
            0x0FBADA65CF4BB29AULL, 0xE864E87AEE38F2ACULL, 0x93A48C018C6A5865ULL, 0x4298DF0C4DA28CACULL, 
            0x33CA7B2F9024092AULL, 0xEA4A2AA37898D9DDULL, 0xEAB8E42245698165ULL, 0xAB6F2A63587625BDULL, 
            0x4E5397B68C2E8D8DULL, 0x311CD35BC32E8B33ULL, 0xC2E835B1ED6014BAULL, 0x80F5F77EA2E75575ULL, 
            0x1D51138278674839ULL, 0x751C94CDB08D06E0ULL, 0x394E5110E43E969CULL, 0xBDB7867B44ACAAF8ULL, 
            0xFF0D27157B4CA9C0ULL, 0xDB0BF245B0C863FBULL, 0xA1CEB1285EF60880ULL, 0x0F7FC7F16B738569ULL, 
            0xD256D9D3BE6BA5ACULL, 0x0F5B767A69E86BCAULL, 0x2D1BA2A36AB451A8ULL, 0x72E626C33D8B6266ULL
        },
        {
            0x0C44422F21E8BC00ULL, 0x076447F3AD57C0D1ULL, 0xFE423977A401EF93ULL, 0xF55E0F4F2F72C783ULL, 
            0x0B9CF4C2DEC67B56ULL, 0x9571BBA3B9824555ULL, 0x6AB1892C76B4B0ADULL, 0x5314B0C2F5BEF3EFULL, 
            0xD7501BB74223B815ULL, 0x8A0C309FBD32812CULL, 0x878725DAED9A0EDAULL, 0x412FF5039A4B74B4ULL, 
            0x95E5AFC75C3CD0A6ULL, 0xB9A050402BFB0213ULL, 0xACD83CF43C621052ULL, 0xBAD81F78AE97DC7EULL, 
            0xDAFF8D78FF1C2589ULL, 0x4FD77148F11CA5EDULL, 0x339BA8B9A12EC00AULL, 0x5EEAF206A05CA065ULL, 
            0x87F613F5B409B651ULL, 0x18F79C82EB9FCCE0ULL, 0xBDE3E20B9B8EAFEEULL, 0x1E8FB897CCCDD441ULL, 
            0x2FCEBAC5E1A99268ULL, 0x7D4739F122DC2634ULL, 0xBF3F231138506022ULL, 0x535C657D861A8E35ULL, 
            0x8E18A2DD0ED15999ULL, 0x73CB299FCA807758ULL, 0x771E508A1CA4A26BULL, 0x45371BF8FAD278E0ULL
        }
    },
    {
        {
            0x17E9A651C906DCBDULL, 0xB452ED18A45774EEULL, 0x1273B681C06F7D06ULL, 0x2196E5AEB5CD94A8ULL, 
            0x15118B0990CE59C3ULL, 0x9E370C59DAC1757DULL, 0x943598A31D5F8B41ULL, 0x84EB2E522A439E66ULL, 
            0xC460CA14EC43EE3BULL, 0x37F4B7A10DDC1432ULL, 0x90B93C3004FAF66FULL, 0xB6D99875C0638BB0ULL, 
            0x4BD2F05F8D49FFB7ULL, 0x3B8F1BC7CEC8D586ULL, 0x38F52BC3812099BBULL, 0xE37E5EF1554C6B60ULL, 
            0xEEFF16EBC7534587ULL, 0xC5678EDC9D770EB0ULL, 0x2E870E586D276301ULL, 0xD89A5AE77FBBF36AULL, 
            0x342651BA7E910BC9ULL, 0xAE4DCB3A325A4903ULL, 0xFCDDBC2AD88FE3B6ULL, 0x5E7CBB2FB0D822CCULL, 
            0x443DFF935C5D742CULL, 0x3F7E441900476A93ULL, 0xEFE0BF167BC9D8D1ULL, 0x6ECF38BF3EE09D1AULL, 
            0xA2F60FDA7B0F6FFFULL, 0x2594F2C9D8D963AAULL, 0x92C2E75402C4E5CBULL, 0xDA70E44096B91B2BULL
        },
        {
            0x78C3F0327C87E91EULL, 0xA912455F75FEB450ULL, 0x2D71D1F892719856ULL, 0xBA0DACE6900C1076ULL, 
            0xED01F88FFD53274EULL, 0x7A9C317DB0A3A86CULL, 0x5A652D2A2BC582A9ULL, 0x06633EE189E50BEFULL, 
            0xAC6B65CB1CA1F57AULL, 0x63462AD035B6259CULL, 0xE7C8F6DCB405E224ULL, 0xB03F67159F02D18DULL, 
            0xAF743FBE4E5D67B9ULL, 0xD0E5DFFE7D969F32ULL, 0xC061FEEFAA20BF96ULL, 0x899744A81046BEADULL, 
            0x49E425CD11B12968ULL, 0x105DD3C54CBCA8D1ULL, 0x5D3D2695027DC6C1ULL, 0xCED35BC2B5BB9E84ULL, 
            0xFC9885F4FAECF36CULL, 0x99B5A74505C7A6B7ULL, 0x58F49A7FCFFED365ULL, 0xE601A7AC0CAC12B0ULL, 
            0x7758E2ECE1857783ULL, 0x6B4BCC814DF2D919ULL, 0xD0800A6F1876A6FAULL, 0xD98428C1CA1498D9ULL, 
            0x10F09A202001DC54ULL, 0xFCD331A897D107E0ULL, 0x770B7D3C2D08DFE8ULL, 0xC1CCEDFD354852E9ULL
        },
        {
            0xAE6E6571AB9DA40DULL, 0xA4F9BAD52451F7A7ULL, 0x1FB6B368F1DA2005ULL, 0x6A3A8746380A4DFCULL, 
            0xCBCD1AEDBEEAC8A3ULL, 0x7AF662A4EB63F74AULL, 0x9393A8CA61D79A70ULL, 0xB105838E67F0FAA2ULL, 
            0x341BBE30A4CA6091ULL, 0xC7F1460CF7D775E9ULL, 0x1D3F2F187206F5F8ULL, 0x43153F0E2267D51DULL, 
            0x01C709B0A21307ECULL, 0x29655AAF63ED5D05ULL, 0x99FD9B63E043F25AULL, 0x5CB0598A279038B8ULL, 
            0xDF24ED3AA182665EULL, 0xD72DD71FD9AA0C3BULL, 0x3F06D4FB57760621ULL, 0xAE51A6FF246CECACULL, 
            0x163EDF4E038309ABULL, 0xCCBAEDF8BC0E9B5EULL, 0x705D940E8722C000ULL, 0xFBA145061AD3C9AAULL, 
            0x721F4EA3E489D411ULL, 0xC12B640EAE619194ULL, 0xD6C915845EE3170CULL, 0xBF7F2CE94524D427ULL, 
            0x78FE1EF2BF057A00ULL, 0x47744A590041EE69ULL, 0x30BF608ECA06E4A3ULL, 0x64585925F0080414ULL
        },
        {
            0xC9C76BC92F99CD42ULL, 0xAE4CBE8DB1030E45ULL, 0x217969FB98F13F8AULL, 0x7EE2C471649FF1DCULL, 
            0xACFF4CFC7694DF82ULL, 0x1BF18DB2D2E82A07ULL, 0xC090DA7D40ECC60EULL, 0x36B7D543AABBD50DULL, 
            0x0FEE62F6D3054275ULL, 0x238CB8C79ADBB211ULL, 0x3DCAF5D4E0913424ULL, 0xC4517DA6D27EC54EULL, 
            0x854FEC9AF283E4DDULL, 0x300190B702D74A07ULL, 0x09B87996DAE2110BULL, 0x079C7C5B8C01EF1DULL, 
            0x08E44184A105868FULL, 0xF7CA4B2314EC73E2ULL, 0xFD2BD49804C73E29ULL, 0xFE20FA1DD665FE11ULL, 
            0x412F2FE20909C45BULL, 0x8FD4D89232CB90BBULL, 0x56087E05107DDE49ULL, 0x01EFE7921BE13480ULL, 
            0xC799218980ABBD21ULL, 0xD7301C8BD221A222ULL, 0xD8A065E7670D2A86ULL, 0x305B2004A8FA9DCAULL, 
            0x860A8B3D8F262246ULL, 0x73F4F7BE22394FD6ULL, 0x0A05F7DA0BE8B52FULL, 0x19D84D41672A1CE0ULL
        },
        {
            0x1D975CEDA894FE3AULL, 0x9B56FF695B56FDF0ULL, 0x1962E67F14673E5DULL, 0x496AB8E32145FE8DULL, 
            0xC63A806C434DB520ULL, 0xFBF351CDE97C9212ULL, 0xE8C90FCE2F9A2FF1ULL, 0x93DB97391733D2E9ULL, 
            0x00E9685E4A2E5A76ULL, 0xE9F864B061B35A50ULL, 0x47499B53B2777C61ULL, 0xDF4A20E68A31A912ULL, 
            0xBACCD570B09CB04FULL, 0xFC025565E2F32052ULL, 0x0AB613633FA5E9A6ULL, 0x8AFEBC00815EDDA8ULL, 
            0xFF07AFD19B638E8CULL, 0xA9B07A794F0EC657ULL, 0x2D68EF34E262A8D9ULL, 0x67B07E5F9B7D3D8CULL, 
            0x9EAE55DD540E5411ULL, 0x1786301FF3F033F8ULL, 0x7AF14EDD719A0546ULL, 0x5B9BF79C3853E933ULL, 
            0x275874654049F37AULL, 0x497C42B5EBD9EE8BULL, 0x11176B0252D01BD3ULL, 0x1E36F642E179E6F4ULL, 
            0x794FDB8B302248C4ULL, 0xC6DA2A64AD86B12BULL, 0xAB1E9CB83B57D075ULL, 0x74CC5D40607ABD28ULL
        },
        {
            0x445D5F5EA1B049A4ULL, 0xD55A860987DDCF12ULL, 0xDF1680DBA214299CULL, 0xCC9375AEF4170B7DULL, 
            0x96C34D66C44B11A2ULL, 0x64A49D27E429CFB5ULL, 0x8DA2E66ABB9A987CULL, 0x3D882376DD0990F6ULL, 
            0x0833E9564EBB9BDDULL, 0x7036F7407CCBC72AULL, 0x0959139DF8B4342CULL, 0x7C7B8555465B9165ULL, 
            0xE479F103B1B8D2F2ULL, 0x64CCEBBC836EBB75ULL, 0xAE27B8D7B0BEDE45ULL, 0x5E545B8F85C449F3ULL, 
            0x829CA63D0BBFAE77ULL, 0xD07F4389A74E25BAULL, 0x7621D4C2EA10267FULL, 0xB23A7D76D881F9A1ULL, 
            0x03F1C287A00A1FB8ULL, 0x439FA8760607FA9AULL, 0x9C844F855C987D66ULL, 0x1FA69EECBFF0F986ULL, 
            0x5311A713ABA30297ULL, 0x3B52CCF4FD98A8A2ULL, 0x0FF250C366F3718DULL, 0x42275D69E56B3204ULL, 
            0x9A35F95E3B6B78A2ULL, 0x123B690671FFA098ULL, 0x4BD2509D264B7DE7ULL, 0xB08E3F4BFD8DC458ULL
        }
    },
    {
        {
            0xB1CD86CC34655207ULL, 0x6DC312AE06FD00F0ULL, 0xD1BEC358BAAC6AB4ULL, 0xFAE426E55C584E03ULL, 
            0xB88C54ECAA36B8E9ULL, 0xB203043C56698113ULL, 0x9975C2F82E1233CDULL, 0xE71E6E4775BD7BC9ULL, 
            0x24E75A43E9DE449FULL, 0x765F2E777B9AB94BULL, 0xCAB2B33427FC676AULL, 0xB0123CACCEC93A31ULL, 
            0x19B1A62F7DB998D2ULL, 0x94EC81818B1B0BFAULL, 0xC30BF47F55A6CB7DULL, 0x35A9D55E5EC48752ULL, 
            0x6798E18EC5A30718ULL, 0x6C5B5CCF31E8A6A5ULL, 0x2BCD391118F18531ULL, 0x8E833A145FE040D4ULL, 
            0x578A83D9DC109817ULL, 0x9E5850643F4A1F6DULL, 0xF76AD44FAAD81983ULL, 0x96D251BDCCCF1E49ULL, 
            0x545589D777796F53ULL, 0x2EA7137FBA18CBF3ULL, 0xD2961D49AF4D9A4BULL, 0xC73AC0D415AD8785ULL, 
            0xC913A026E1397172ULL, 0xDD03AB3DA64571BFULL, 0x6701CD570AF91E80ULL, 0xCE2C2894E17B887AULL
        },
        {
            0x862890794BAF7F60ULL, 0x0F00302ED09AD207ULL, 0x90CD2A75B61F9726ULL, 0x7E20257FA8F081D3ULL, 
            0xB49C0DED710E35DCULL, 0x50CF4ED0CE4E5685ULL, 0xEB536A7395A90C5FULL, 0xD4C69AB0C9ED4988ULL, 
            0x6A63B5669834FE3DULL, 0x34419C82FB40A234ULL, 0xB624B31900763B12ULL, 0x93F56E32686D0610ULL, 
            0x212E9A996C84DD0CULL, 0x6C7C96AC3105E870ULL, 0x21C27B68FE9C2AC8ULL, 0x370DFED65F9FB7F7ULL, 
            0xF8AC395D06D32AEBULL, 0x19C9C66B3774CD3AULL, 0x37A2272ED2C9AE5FULL, 0x7212270534049389ULL, 
            0xE235BD036DB7BA5CULL, 0x027EF10AB6DD1BA5ULL, 0x7930BC9337CD1DEEULL, 0xD67F71368A14A400ULL, 
            0x1DA59726923A1976ULL, 0x8CEB0902AE8D69DDULL, 0x4D5B3944A30A82A0ULL, 0x536F7748FE3448FAULL, 
            0xD419C8FAE22BBDA7ULL, 0xA59E02B6404F41EDULL, 0x03567D6C8CBDB94EULL, 0x5441BB6B2920CD14ULL
        },
        {
            0x46ABC9F381628BF1ULL, 0x90E46E9FC92DD267ULL, 0x0D0CD0C60A558F57ULL, 0xBFDF8249CFCDCE78ULL, 
            0x58F75C088F240595ULL, 0xD5A9FE85BDAAA7C5ULL, 0xE02B76BEFCA06CBBULL, 0x0C626869BD16D437ULL, 
            0xA5F61794D0889091ULL, 0x853B2D0C2B9BBD51ULL, 0x0346ECD5FF43DD5CULL, 0x8C56CF779850F954ULL, 
            0xAD81FD2DCF775F21ULL, 0xD67AA346F203A489ULL, 0xEAB3747CC2E68691ULL, 0x77799479E2EB82BFULL, 
            0xF4C5255B6D0F17BBULL, 0x51C129ABC4BAEAE8ULL, 0xD50D0BDB08B12555ULL, 0x7452DDA0AE1563CAULL, 
            0x70CD3A8FA8E9B09FULL, 0x17BF990FA78F38B6ULL, 0xA0417C93B6B85A96ULL, 0xF0609A54350D102AULL, 
            0x191213A2DF47A5E7ULL, 0xFCA5F7E7CE41A08BULL, 0xA4F55B6E2F42CDC3ULL, 0x61AF9E746DD8B609ULL, 
            0xD67838ED2759188AULL, 0x9D9B845254A20194ULL, 0xF8E8A638D9B79C11ULL, 0x3D002431571DD952ULL
        },
        {
            0xBE55D9866BFECDA4ULL, 0xA595F09FC810AFD0ULL, 0x34621B313E0B82BFULL, 0xB8890D515A6561D5ULL, 
            0x71EC526F972D45C6ULL, 0x1745797CFE7482B5ULL, 0xC1F4AF2319FDB2FAULL, 0x1D22DB6FDFA6AC19ULL, 
            0xEF74CB853522B28AULL, 0x6579920F70E019DEULL, 0x49B8AF299E312414ULL, 0x1C7F62252A575C8DULL, 
            0x59A4EF49A3E8CD1CULL, 0xA6D978942A14837CULL, 0x567A45CD082CE2E3ULL, 0xE00F57F7D56016A3ULL, 
            0xDDDDA1472997509EULL, 0xEFA75287D8A12113ULL, 0x8BDA94CFEA8D3D85ULL, 0xB35117C3693646DCULL, 
            0xC2B5BFFA4594DC44ULL, 0x26824EBED9E72648ULL, 0x1449BAB368D5B118ULL, 0xE1FC41B96645E676ULL, 
            0x018A0038C212D610ULL, 0x2D8B9608E5E2EA4BULL, 0xC4C297E743CA8B99ULL, 0xD4979299630A6F7DULL, 
            0xFAEC7C90D030395AULL, 0x0A77B049DB2F5AF1ULL, 0xD1A2CD397AF209F1ULL, 0x4A05C2609DF4D414ULL
        },
        {
            0xF0E41EE497DB7716ULL, 0xF8C8CB04D81E046AULL, 0xEDE6DC1CBE206794ULL, 0xDF5FECA7D563DCDEULL, 
            0x4E7A2E5AEF021162ULL, 0x33E0F15764784246ULL, 0xB8BF7C94ED83A482ULL, 0xA2494CF0610AA7D7ULL, 
            0x90745DBA97515AAFULL, 0x80719B821617F891ULL, 0x56420A52DDEE096EULL, 0x511AB51858F58EA4ULL, 
            0x526381A3BC9B857DULL, 0xB4C9CA38B71F5362ULL, 0x51BD0E074E253963ULL, 0xCE811ACDB655C72AULL, 
            0xECB2D52893EDA73BULL, 0x72D8EA9A2A76A85FULL, 0x018DE78B8E531D65ULL, 0x9F1715E74112373DULL, 
            0x0A8CDFF89940D9B5ULL, 0x2F005BB936152FA2ULL, 0xD43DA44A1F789DC3ULL, 0xAD43DB06C0DB18B8ULL, 
            0x4BC4F54193E4E918ULL, 0x89C075179C0A1E20ULL, 0x2D65DD2D5D648078ULL, 0x9CA25F714F4D206BULL, 
            0xA3D34AA9C4D97A36ULL, 0x58E4CD415F66F465ULL, 0x132D288FFFE6FAC4ULL, 0x4062292E6B36F93BULL
        },
        {
            0x5E83DE3C0FF0BC3EULL, 0x2D7EDA8320CEAA0DULL, 0xA494C46D8B171C82ULL, 0x504F1BF77C9BB290ULL, 
            0x63735DBB9296BE89ULL, 0x17ABE7DD7069B16CULL, 0x11F8FC63344927B8ULL, 0xDE31829C74B2A7AEULL, 
            0x6CA63C0941105F5FULL, 0xA91F5935874E18A9ULL, 0xFDD58C8212FF1293ULL, 0x9154A828991206D5ULL, 
            0xA9E1763215F4BD74ULL, 0xA8CEEBD9A54CE463ULL, 0x767054FD3854DA2DULL, 0xAB03F5BE2F0EA974ULL, 
            0x08936CEE26E63334ULL, 0x1AC20F3527F5FB71ULL, 0x0CA797CD393B2CCFULL, 0x81A59E425FBCD103ULL, 
            0xFF55C2699F440188ULL, 0xDF592F283DADBBF4ULL, 0x954574CF2841800DULL, 0xC9C86026329A7E70ULL, 
            0x6DF4FAA9FAF8B560ULL, 0x0B1C0996DBBA9671ULL, 0x7D287FBAE64D301EULL, 0x4592411864534DC1ULL, 
            0x9034F4B81A33CBCEULL, 0xF7EF880BF47A14A8ULL, 0xE80939D48ED2270CULL, 0xD7FDEE1523689617ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseBConstants = {
    0x9FB6669D826FA0B3ULL,
    0x072D48CEFBBED0A6ULL,
    0x7EFBDB363240BFE7ULL,
    0x9FB6669D826FA0B3ULL,
    0x072D48CEFBBED0A6ULL,
    0x7EFBDB363240BFE7ULL,
    0x9A0D99513BB3A757ULL,
    0xB84A2A62309C99A7ULL,
    0x36,
    0x49,
    0x12,
    0xF0,
    0x56,
    0xCD,
    0x89,
    0x3B
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseCSalts = {
    {
        {
            0xE8A30BB2944C004DULL, 0x225C3480948F5E05ULL, 0x1B548D542FF4BE19ULL, 0x2A140929A13BCD3BULL, 
            0xC7DE90C8C1D0CAF1ULL, 0x97100EA54FFC204DULL, 0x8C67EABAD054E7B1ULL, 0x273685AF87EB06BAULL, 
            0xD363BEF6BD0E9678ULL, 0xDEBCDF2EEF2BB761ULL, 0x37CDEB614762EEC9ULL, 0x7280EA06803E7620ULL, 
            0xB7F0F869FD52D215ULL, 0xF4AF70118C301548ULL, 0x3B8CFA303624B6F9ULL, 0x698806B2466B76D4ULL, 
            0xBA6830FF5C6F0DCEULL, 0xB8661BD1168D6CB2ULL, 0x23619EFBC5F0BE18ULL, 0xD5A1BE0A507FDDDEULL, 
            0x75F4192DA80FDA48ULL, 0x134FBB55F20348CDULL, 0xB4FBC58E59FF4269ULL, 0xF0ACA58B10A23B03ULL, 
            0x0354BEBD90B35355ULL, 0x2F18AC39B165E32FULL, 0xD568FDC24F8A3EE9ULL, 0x2CF1554B10F8ACFFULL, 
            0xEA3760902C645595ULL, 0xB101E2D7B8AD3741ULL, 0x206DF30AD8C87F72ULL, 0x88CD075A9F1C003DULL
        },
        {
            0x16906E877C91A930ULL, 0x0B94917DC9085835ULL, 0x0BA8A095F90E2B75ULL, 0x4600CA438BDC8D94ULL, 
            0x3113F5AA5E03C296ULL, 0xAFC897685AE58D72ULL, 0xCAC9242E7F07D929ULL, 0xD8F5BFE13A060132ULL, 
            0xD8818E5E3A7CA0EEULL, 0xC2B79B98DC374F99ULL, 0x82C2A73FD58548C4ULL, 0x4600E4A98F61B12CULL, 
            0x3E3F1B946318C1A2ULL, 0x7450EF2FD490ABADULL, 0x528D62915E8E07ABULL, 0x919114CC28BFFCCDULL, 
            0x557BFCCF601BD5DEULL, 0x537BC083D2C3F79CULL, 0x8189BBF2A518EA3FULL, 0x632C6F80A556A9CEULL, 
            0x8995FA385A85C582ULL, 0x080E3035A337A383ULL, 0x599F407590933AEEULL, 0xC557D484F25A5479ULL, 
            0x4DEE879D830FCFCFULL, 0xEC0A10BC0CAB860FULL, 0x8C2B5B1A73CE6389ULL, 0x94118D5CAA22CAE0ULL, 
            0x81FBC126CFB00DB2ULL, 0x6FD9589AC8AB966FULL, 0xB40FB6EEC6E5B792ULL, 0x387526B5AF5CBF1FULL
        },
        {
            0xC89F869FC697DC99ULL, 0xC81430B39601D91CULL, 0x0A4E388762F7AE57ULL, 0x03B8D2DDE001558FULL, 
            0xD00EF2A7076A936BULL, 0x49A88B6BD1050C01ULL, 0x83CF3376E27CB690ULL, 0x868E4AC720716462ULL, 
            0x355C706E3D02B72AULL, 0xE4574B2FC57989DAULL, 0x5760761744D298DAULL, 0xC03E42D3C7602257ULL, 
            0x68214C5323AEE3D4ULL, 0xEC06E5029AF09999ULL, 0x8D3D5AE649E5642CULL, 0x689DF71651555131ULL, 
            0xC422EDF8F2A0CFF4ULL, 0xF6C2C34A71E1D66DULL, 0x1CDB259A51503E11ULL, 0x7EB9521607128458ULL, 
            0xE4C40DC3ECCE66CDULL, 0x4500F95F7DE91050ULL, 0x7535517EA0A85E44ULL, 0xB046231705E6630EULL, 
            0x2FDD31B4969CF4D7ULL, 0xFE9D31D66BF19FF2ULL, 0x8C73AFA011B53DDAULL, 0x955E35C6F75908B2ULL, 
            0x75BBCDD4D6CC5901ULL, 0x40EFBA53460EF6A4ULL, 0xEE3F4CCC69E617D3ULL, 0x35C88A46F376547FULL
        },
        {
            0x515F8809A74A38A0ULL, 0x58C1D38B6D6BF5E6ULL, 0xBEFF58860778564AULL, 0x454464D1FD77C14EULL, 
            0x938F18660382D3EDULL, 0x41910560190059EAULL, 0x7F0FF15F10224616ULL, 0xF1CFFCB5F9DB5133ULL, 
            0x5390A59CC890FD96ULL, 0xE5404B31D7BAC6A6ULL, 0x98EC11F83A24AE9EULL, 0xBF500D524167BBEBULL, 
            0xCE61B3F8A125D630ULL, 0xF03A70E5A9220078ULL, 0x174E1C691EEC0929ULL, 0x9F88EFB1BF36F8FBULL, 
            0xF039A26DBBE25D99ULL, 0x90D7958C9E720F05ULL, 0xD79034A35563AA4FULL, 0xD5072FAAB91AC2AFULL, 
            0x88ED872A76B87201ULL, 0x196BA744D232D69DULL, 0xDF0B14EC63625B42ULL, 0x7BD92E36BCC715C4ULL, 
            0x357058B4BD678F95ULL, 0xBD7355BF5788EC66ULL, 0xCB7520E4443938D2ULL, 0xDF674A2DB2FB6160ULL, 
            0x67A6C1126D003856ULL, 0xCE4F9912C07CDB44ULL, 0x4133F1931AD0F3DFULL, 0xCEC7885986520F6DULL
        },
        {
            0xE1449C25A3744F9DULL, 0xC308856087E5C371ULL, 0x6833858D5E9C1575ULL, 0xFB20831158200694ULL, 
            0x40985F73DA8BBFDFULL, 0x03C8809A3522B341ULL, 0x7AEB006515C11B49ULL, 0xAF14D08DA59E719BULL, 
            0x3DD8CDF089F3D9E6ULL, 0xC7670ADE8E921FC0ULL, 0x8AC2B6BA9AC79467ULL, 0x959AB86DE4405B77ULL, 
            0xD891EF970F7B75BFULL, 0x479E12F7485D4780ULL, 0xCA2A334E8E587359ULL, 0xE8FC88AFEE96DCE7ULL, 
            0x178AF90BBC0807D4ULL, 0x79C5B5838D206647ULL, 0xD761E570735F6DD9ULL, 0xA610B57A2F74D0C6ULL, 
            0x8FC75EAB37AB42A1ULL, 0x2B033A61D23A1DFDULL, 0xD1A99A61B69E6365ULL, 0x0DBDACAF4C656221ULL, 
            0xEA880FE5A111EA85ULL, 0x2D57A8A55648F19BULL, 0xD013261D86EE344AULL, 0xB6952482EB0FFC04ULL, 
            0x4E789B061F7BC58DULL, 0x5A55A7BE11A688FCULL, 0xD84CA7F6BE3D1E21ULL, 0x24AA5476761F810DULL
        },
        {
            0x4EE7723601DF90D9ULL, 0x0402EF9EBC6F6AD0ULL, 0x5B2CF95088ED3B93ULL, 0x9A23761AEAD0EFD0ULL, 
            0x8E8EACEDE3566E77ULL, 0x3B8D04005E3E2CCFULL, 0x070156A4092DF586ULL, 0xAB5F54A407DEC07EULL, 
            0x28FD359E4B05A69DULL, 0xE924DA7D6BC6A42AULL, 0xE1393AE579AAA6D4ULL, 0xC0361BF7114A690CULL, 
            0x6075BEC2EC2B8127ULL, 0x54C618CF90C38DDEULL, 0x44B5AC22A2A0BD21ULL, 0x694EF8B830738EA0ULL, 
            0x3DEA26B0C8B8CC09ULL, 0xC0679B8260507346ULL, 0xE13C27899E47275BULL, 0x5F0468BEB1B9F2C0ULL, 
            0x42DE65BDCA620DB7ULL, 0x6CE7AE7CA07EA502ULL, 0xA477203DBCCFF76CULL, 0xC464053D7D714E4EULL, 
            0x56BBC923DF54A35BULL, 0xADC0AC1F20FDCBCCULL, 0xDDAFCEAA3E6A0E4DULL, 0xD75EA4DF706C804FULL, 
            0xF8498BDDD7040524ULL, 0xF41E67430CB6060BULL, 0xFECFD22FAD72DA9EULL, 0xF538E5C9256AE65BULL
        }
    },
    {
        {
            0xA64F462CF32EB3A3ULL, 0x56826FB2EF9750EEULL, 0x48FE526E0C099CB2ULL, 0x4034DC55D458E256ULL, 
            0x2BE1824295536D20ULL, 0xDF666A224CFF4177ULL, 0x4D7D1DEC92C6EC93ULL, 0xD117F0028E653DB1ULL, 
            0xB73BEF46778F6C8BULL, 0x0B64712C45A72ECDULL, 0xDC3FDEBC47593038ULL, 0x78CA202A07D16EF5ULL, 
            0x36976BD6690D6ABBULL, 0xA9D639434F1EC600ULL, 0x883FDD79C7C868F4ULL, 0xD593815142E5DC60ULL, 
            0x8FE2866178EC62BFULL, 0x0149BBCD0808C338ULL, 0x90BD0B357E097EF6ULL, 0x9A29BD2225B505C1ULL, 
            0xA95223E118FEC6E0ULL, 0x52A94E5351165BE0ULL, 0xE73B0C86224D914AULL, 0x34A4051E4AF01BCAULL, 
            0xAB02D089C22F4927ULL, 0xB3E508E4E9894CC5ULL, 0x86B6A02FF29C0A89ULL, 0x377CC29C4DAFAA3FULL, 
            0x615EB69194F6063BULL, 0x317E0A5BDC6BFF8EULL, 0x9D47A49432176F0BULL, 0x080707FBA0DEE807ULL
        },
        {
            0x581346B9626D319DULL, 0xBAF6FBA55277C7FEULL, 0xA9C8BE12F254417CULL, 0xDDE1EE0133C13A38ULL, 
            0x53878E591DFE29C1ULL, 0xE07E2E9FDD6FFF50ULL, 0xE5D51099A2AC4A2AULL, 0xD390EF7FC9A58746ULL, 
            0x491741332682ADC9ULL, 0x4BCD59CD0EA9161FULL, 0x75F648287F87D6D4ULL, 0x51F17D568A02EC3AULL, 
            0xB1A47A00B806B3C1ULL, 0xBFBF7B7705723C34ULL, 0x704832A50BED394DULL, 0x39D7163CE5FEF458ULL, 
            0x59FD50EA2E0A49B7ULL, 0x8B5F5E47756840A8ULL, 0xF73F46B1DC0D5204ULL, 0x8B13422913123874ULL, 
            0x3EEC200FAE416DB6ULL, 0x383B4D477781E67DULL, 0x66CAE07C6994829DULL, 0xF4A20765BEEF03CDULL, 
            0x532A12036EA2C49AULL, 0x6A5B14855FE3752FULL, 0x2DA6144CA9D0BA3BULL, 0x18800276E26071D4ULL, 
            0xB6052CB093C7D3C1ULL, 0x70A355614F67082BULL, 0x7CE0FE183ABD36FCULL, 0x52D406AEF560F65CULL
        },
        {
            0x6942E566C026FCF1ULL, 0xF89F43321ECD0393ULL, 0x43F0E52D2E9A476CULL, 0x37C379F15BC6BD32ULL, 
            0x3F98A9FD61F84D9BULL, 0x133116ED8A3C66E6ULL, 0x5012AEDE52AB2492ULL, 0xDA6AC1C83A2172D6ULL, 
            0x9637A828E78C7F76ULL, 0xA526D029537C2BF9ULL, 0x1AB143D44FCEF01CULL, 0x9360CAC89CE81C8AULL, 
            0x6E2B4F4F84641BF7ULL, 0x885940F695352695ULL, 0x17D37F805B557D80ULL, 0x4665E59BC67A80E0ULL, 
            0x212F116A9F5F9954ULL, 0x16E2BD0EE4256470ULL, 0xC2643E054081A586ULL, 0x0EEBAA26A9A9BDE7ULL, 
            0x7A34FBF3F7CE76D5ULL, 0x0DD4BEE29DAEBCAAULL, 0x6CAC76FE5CC0FAFFULL, 0x96A93D4E30B1BB74ULL, 
            0x1538D51C308F2CE1ULL, 0x357287CA6F301F29ULL, 0x3A74907820F6B170ULL, 0xCF3B08E9F0FAC807ULL, 
            0xEF3AAD90498E385FULL, 0x633D95CA6661F7EAULL, 0x6CE9E2F1E68B067DULL, 0x2C3228743254C0AEULL
        },
        {
            0x501E3F3C6B50AA6EULL, 0xE3D462E969C8C9CEULL, 0x04C2BE3140054F44ULL, 0x6E926C68C63119ECULL, 
            0xAB293EE0956CF4DBULL, 0x5D73CBE5439B8612ULL, 0x95CC7D849AB555A7ULL, 0xB4D3BEEA7B7C2103ULL, 
            0x86DB713609D8A07BULL, 0x986503C22972D9DDULL, 0xB7C531C1042C3163ULL, 0xE49392774AF5B0CDULL, 
            0x25325E3C9FBD2100ULL, 0x637D4C03575BEE07ULL, 0xD5CDBF8B0B8DD7C7ULL, 0x5F0CBA3A10E0B188ULL, 
            0x9F64A48FD97C95BBULL, 0x43A1ED4B24950B68ULL, 0xA5E2F612AD0684A1ULL, 0x1C571FDB326DA66DULL, 
            0xEF3C68E33DE2D2AFULL, 0x5FEFC7FA051BCBBFULL, 0xAAD3E7C51C6FE536ULL, 0x6D4FD3DDD9DE9A47ULL, 
            0x0D7FC0E1D537E67DULL, 0xEAD1BF88B026111FULL, 0x029D6CB4F1AB4BD9ULL, 0x3E745594935FDAD8ULL, 
            0x170D77675F186D6CULL, 0xD52AEB7416AC65E5ULL, 0xA14FF95CED501E67ULL, 0x4E56C7FE78725B4FULL
        },
        {
            0x743E9034EE650291ULL, 0x31457D00411B6922ULL, 0x73D58734767FB25CULL, 0x9F45FFC3DB568A2DULL, 
            0xEE9081C9C71FDF08ULL, 0x912C173280A3D7E3ULL, 0xDE40A9F4DBAF56EEULL, 0x5A4192FED8503F13ULL, 
            0x96CE28EA0EB9A082ULL, 0x14726B9426DF29F8ULL, 0xD785B2893D39E5C0ULL, 0xFEE86C57E9785091ULL, 
            0xF40B8F914021890DULL, 0xD4509C0F85B057ADULL, 0xD555ECBC64604B99ULL, 0x9F995BB785F034BAULL, 
            0xDA24B5BA70BB0B4EULL, 0xB64FFDACFE58A5E2ULL, 0x34A87DC9F2052C5DULL, 0xB1F0F7DED0F29725ULL, 
            0x48F220FF3C9D7348ULL, 0xF5E254493B8812E5ULL, 0x6BC4F81F47C7A48FULL, 0xBD21A65FFEA6598AULL, 
            0xADCA971E2F5EF23EULL, 0x9FAF84AB73953DC3ULL, 0xC6BFE477ED340D49ULL, 0xBCD52F106D0230CBULL, 
            0x759182590B91B030ULL, 0xA353907CB6BAFB9AULL, 0xD88339FB17E8D50EULL, 0x8844ADECDCFBA6ACULL
        },
        {
            0x4C2CB4E00F012820ULL, 0x34F8A6276085E324ULL, 0x16D235703F52EDACULL, 0xB98D84B455F1D279ULL, 
            0xF809F210B627E092ULL, 0x2C35DE7A473DE0FCULL, 0xF7CDBBB66D47E281ULL, 0x7FD3D1B5B22A8EBFULL, 
            0xEBC57AAE619FA0BBULL, 0x07031D85AE546407ULL, 0x4F53C39C00731949ULL, 0x1A12441A5746BE88ULL, 
            0x9FE890778D7F55ADULL, 0x0FBFFB6736DD2812ULL, 0x87A8CE3512C8B042ULL, 0x4A8FD02A7C3D1F87ULL, 
            0xD945DB82D766B98CULL, 0xFFDF740FFEFEC88FULL, 0x163676866A3DC389ULL, 0xC359ED3A00594FCBULL, 
            0x10625FDC6FE20064ULL, 0x04D53DFE17330E2BULL, 0x2EE2173F3F6CE4E1ULL, 0x706DE3386DF83880ULL, 
            0x2DAF802C87C086F4ULL, 0x292DA93ABCA0AC9CULL, 0x50126DE13EBCEC62ULL, 0x00689564878AFABBULL, 
            0x6E516962A089396FULL, 0xBC61362C7D82465BULL, 0x9B16A6A74DAAB6E1ULL, 0x56F36507B9D70720ULL
        }
    },
    {
        {
            0x8687CABAAC7CEDC5ULL, 0xBB57D984D5E2F741ULL, 0x0D3BBFB660705B27ULL, 0xFAFA5AFB605A5AE1ULL, 
            0x4B0EF35DA8F8F634ULL, 0x044B790F5357CC92ULL, 0x2BF3FC438BCAF70AULL, 0x560C0ACF12EA93BDULL, 
            0xD2861B248AF00818ULL, 0x361EE9FDFAE46772ULL, 0x04405BB69B309897ULL, 0xDB37F1F18069344DULL, 
            0x6CEA85983FCA9A65ULL, 0x98EEE56A330400AFULL, 0x63C3E6BA38E426E5ULL, 0xB0772DAFD36E0590ULL, 
            0xDA6F9C06A612EB08ULL, 0x9631F2B1CB3E6921ULL, 0x2FA70024F1E2653EULL, 0x2B8B62FA2944842EULL, 
            0x64EC47EFABDDBA70ULL, 0xCA9E4E49F5318C0FULL, 0x9527E77A3770504AULL, 0x7648129366283898ULL, 
            0xB0D8788561401FF4ULL, 0xE93B3EEFF437D2E4ULL, 0x352C78FC06C23315ULL, 0x29A13CE90E67BD31ULL, 
            0x30FE0E292F7DFE85ULL, 0x6F326F9FC797FED3ULL, 0x68ED9015153CFEE4ULL, 0xF0D267C515478784ULL
        },
        {
            0x9C20363EBD04A0D3ULL, 0xF28C50758A77035EULL, 0x50C771C29C04D9A3ULL, 0x56DC6437D21F5E84ULL, 
            0x3B2E710B866FCFBBULL, 0xAE6E116BA9A18671ULL, 0xB7EAB768BFED7453ULL, 0x7FAA00AAD43DDEC4ULL, 
            0x707DAB5AEB86E314ULL, 0x818DCC0E2260C0C5ULL, 0xEA86C05F69621826ULL, 0xA257EE8D29906A88ULL, 
            0xA228BED58405CF36ULL, 0x385F10FA28AC1DFFULL, 0x47632D13FE202FC2ULL, 0xFE96A5D67835193EULL, 
            0xF5288963350A5DF2ULL, 0xFDAB292C720824E1ULL, 0x125EBA3B31D64C50ULL, 0xEF87645BEED7C55CULL, 
            0xB28949E3AB1E8FFDULL, 0x624735A8CC15DC20ULL, 0xE9BDB5550494B3D1ULL, 0x64F5D48C57F17B31ULL, 
            0x5D3B46DA49869D21ULL, 0xA88D46FE04A767EFULL, 0x5D25BAA143450B8FULL, 0xB3B9008B75D43A70ULL, 
            0x91F5379A35D77795ULL, 0x2410B8C75E3ECD66ULL, 0xA2E98C536B71AC0EULL, 0xD62029A943C4A190ULL
        },
        {
            0x3AA72C6F3E12DA9BULL, 0x8D02CB8507B251F9ULL, 0x0D676AD81A7E04C4ULL, 0x4A53226121B3DC19ULL, 
            0xE0883C89D33A6740ULL, 0x4E9169240266EDF4ULL, 0xC2F19862B940BDE6ULL, 0x3834067DA6EBAB64ULL, 
            0xBD1D74B3959B906CULL, 0x2DF48A2AA0AC466FULL, 0x95A3D4EDEDF09A7BULL, 0x4452EA63D08E5D0DULL, 
            0x590403E9310AB24DULL, 0x7CF46267ABBF105DULL, 0xCE40FB04A33CB41FULL, 0x00E207A661E82325ULL, 
            0x5EC3B11EB6F4017AULL, 0x98CA5BB66A37AF3BULL, 0xA8CC43298B80079EULL, 0xF152DB0B26ACB467ULL, 
            0xBFDE97207FD3E855ULL, 0xD1E4DEE4B15452EBULL, 0x68E98F422441542EULL, 0x7E613A4FE6AD33F1ULL, 
            0xE1FC027CDFA928AEULL, 0x0377DD1B5C5CB90CULL, 0x9BEC74334FE1C48CULL, 0x6A254C1B47ABDABBULL, 
            0x025D201B8363F611ULL, 0x2AEC00C1F426B8CBULL, 0x15C60672D920C2F9ULL, 0x91AE3608DE2D6764ULL
        },
        {
            0x33F0D89EDC335CBCULL, 0x68760C3371D51A40ULL, 0x5518FFA48B7038DAULL, 0x3A824DFE127296E3ULL, 
            0x2C686FA4CD55D0E7ULL, 0xB142934DC3B41314ULL, 0x4AA115D8BD4C619AULL, 0x8D0DACE054257C9CULL, 
            0x801EF839D0619C2DULL, 0xE08DC12CB9EB1412ULL, 0x6982B7E4B996053AULL, 0x3FDA966B862D6C04ULL, 
            0x766ABE5417244DC9ULL, 0xCA0A71A11DB5B2ABULL, 0xC5BF0EA24516123FULL, 0x075DBE53C9340EFAULL, 
            0x7AA27F4CF98F6CECULL, 0xA76316ECB12AAA0FULL, 0xA9FF491C980A350EULL, 0x51403D4B8CBB28BAULL, 
            0x15384CF9D28478BCULL, 0x77C703D93531236CULL, 0xDE1415EA94A28E96ULL, 0xDBB8C711AFB3FE8EULL, 
            0xD34EEC45CA7C40A1ULL, 0x019A31DC6A91893FULL, 0xCDF45AA5FBA84A9AULL, 0x248381E0A648DF56ULL, 
            0xC50D002F72052481ULL, 0x85FC725DAD5068A8ULL, 0x6C44D9F37550DEC3ULL, 0xDF1A5062ACF8B3DEULL
        },
        {
            0x27DDB42990DCDF0EULL, 0xE52E57F5C42D86DAULL, 0x56DD86E0E46F14C2ULL, 0x94ED6EDA8C1C03B2ULL, 
            0xD0F08AA01D8C2756ULL, 0x10D1F0601D0487C5ULL, 0xFC58E0DE3FF60B6CULL, 0x231C4A772A713568ULL, 
            0x93398B053FA2F17FULL, 0xE91CD9E98B7FBDE6ULL, 0x84A5D639986D1780ULL, 0xCC15A8A3806A8375ULL, 
            0x79B3DCB527C8242FULL, 0xCED34CCBFD2DC9C9ULL, 0x66584FA5E5660B8FULL, 0x0C113B5A20FF8E0CULL, 
            0x5174493B7BCE52F4ULL, 0x9D56C7B614C5D059ULL, 0x6FCF73677EA1D207ULL, 0x649FB9AE10855727ULL, 
            0x43C2760913D0273DULL, 0xA3A9AA4576999EF9ULL, 0xC4F8A5A2ADA43C20ULL, 0x7D444BD8348EE9DDULL, 
            0x7081393BBB876905ULL, 0x41AF8EC89FA9DEC4ULL, 0xFFB1569098FAEEFDULL, 0x650426790E17C96FULL, 
            0xB2C24544DCE327CCULL, 0x39765DF144B2A2CAULL, 0xDED19F239E36E0D5ULL, 0xDFB49CECAB255ACFULL
        },
        {
            0x8FA95217B3EAA76FULL, 0x756FF815FA862CECULL, 0x2B4AE6081C36F80CULL, 0x0E0314BBEAAB5CB6ULL, 
            0x389EB36BC61EADEAULL, 0xD0EA91E800A63D57ULL, 0x72740C53804D51EFULL, 0x07C6AF190A294853ULL, 
            0x66B02492B3FA51FEULL, 0x4F2B19BC6FAB280AULL, 0xF2BF6C2F74304494ULL, 0xE82525798F23BD82ULL, 
            0x77D5370BAF50AA4CULL, 0x64811F19F798EFB3ULL, 0xEF7CAAE2CD1B6D46ULL, 0x3DCA52EB84ED6A2FULL, 
            0x44AF59E4AA70618FULL, 0x20D820D2116A212AULL, 0xA6107BDC9ADC4617ULL, 0x1EF508DC87194334ULL, 
            0x3DA71D5C01402EDEULL, 0x679437C519B4A4F6ULL, 0x845F06A9375BA690ULL, 0xFD66AF2974CE4DAFULL, 
            0x4F284144DA28DBACULL, 0x9329AFC7649B3908ULL, 0xAB5FA546D19D7FF4ULL, 0x7768C28C7CF29A60ULL, 
            0xB5F802115657A81BULL, 0x2B2B291EA3363508ULL, 0x9A9C88C6367C70EBULL, 0x917A45D8916FE4AFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseCConstants = {
    0x5D91FE5B70B0B98CULL,
    0x971C1FBA8BBEF8ACULL,
    0xDAC1B382FE749236ULL,
    0x5D91FE5B70B0B98CULL,
    0x971C1FBA8BBEF8ACULL,
    0xDAC1B382FE749236ULL,
    0x3E6288A711D8DBB2ULL,
    0xFF222167A6C7E450ULL,
    0x32,
    0x54,
    0x17,
    0xB4,
    0x06,
    0x27,
    0xAD,
    0x7C
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseDSalts = {
    {
        {
            0x6E33F3CC4DDC6C8EULL, 0x267C25B448BFA012ULL, 0x5BB3F2AB6372E1D5ULL, 0x7FBEE49DD961478DULL, 
            0xAD725724F5E43C3EULL, 0x0B6B6CEF4B16906AULL, 0x2C200EB39B2B6F10ULL, 0xA07695FEB568FEA5ULL, 
            0x9F15D46311D67B80ULL, 0xE0B7185AB5D10191ULL, 0x5A1417FA6A5CFE26ULL, 0x749BFC047446DA76ULL, 
            0xAA0BA612909C8B16ULL, 0xFCD680D619D055A9ULL, 0x2ED4CF867F4BBC07ULL, 0x8B8B37FF338156D9ULL, 
            0xE06BE36BBFEC4C22ULL, 0xE84775504FFF5E1FULL, 0x0409BF4EDA8443A2ULL, 0x089FAACBBFD50AF5ULL, 
            0x70FC6A08BD52BD02ULL, 0x351C683036AC73FFULL, 0x8E6535195A280C3CULL, 0xFBD9A05DC5657928ULL, 
            0xC67CABF7A9E4133FULL, 0x932D6CFC3FCEE205ULL, 0x71DA5D189104B0A1ULL, 0x87588BB290534E0DULL, 
            0x87FFBB4863406F5CULL, 0xC0ED2E3DC170E51BULL, 0xD5E6B24A21182DA0ULL, 0xBBE653BCA5AD7695ULL
        },
        {
            0xA6A61969F93616A8ULL, 0x7D815F96B8E36554ULL, 0x2C1AF912EF5F3411ULL, 0xB5D65B4AB7CED1C0ULL, 
            0xCE07D4736FF98C95ULL, 0x19E09A74AECB6925ULL, 0x144F51A5FCBDB67BULL, 0xE3E4693A69D12E34ULL, 
            0xF201B0EA3ED2EB27ULL, 0x9DFBF1484A7CD725ULL, 0x16ECDE7E6FDD2D2BULL, 0x59EF458C1FEC7CB1ULL, 
            0x4B8DDAEA8FF54CAAULL, 0x4AC64E9D1DF19D83ULL, 0xC4FD4D0982497BB1ULL, 0x5BB30BF57F748C4EULL, 
            0x13B4DEB476DBF016ULL, 0x69F033DC4863656CULL, 0xAFA93F567CE4C0EAULL, 0xBCFF99F0735973C5ULL, 
            0xBC292BB42CE0F588ULL, 0xEF20E6AA50884F8AULL, 0x23CCC400ABFE6810ULL, 0x509EFDB0CD5DB740ULL, 
            0xECD40CC4F0621E72ULL, 0xB9E593118805DCCAULL, 0x51B3B409EB1592C5ULL, 0x4AAC1573F80D6615ULL, 
            0xE7FEB4C88C88EC71ULL, 0xAAD67CC4B89C5984ULL, 0x840002F8FD2D849BULL, 0x26357D1CB65DCE42ULL
        },
        {
            0x9174212836DD33A5ULL, 0xBE9ADC7AEBF64152ULL, 0x62FD201E0744A9E3ULL, 0x869A3706637841DAULL, 
            0x6AFB13D57294B3B9ULL, 0xB6247FBAA8A20070ULL, 0xC40CC41EE8626EA1ULL, 0xC124F91C36ED4704ULL, 
            0x1B77850E9C26DA0FULL, 0x9D7EB725FDF57BECULL, 0x0686DB14BD2ABEC0ULL, 0xFDC698DFD0CD29E3ULL, 
            0x932AD994F6884FD5ULL, 0x9ED8F70846090880ULL, 0x1500A3FBCDA56AA0ULL, 0x8FE0EA3C91EE036EULL, 
            0xAFAF970ECEEB72CDULL, 0x70726E39697D3FABULL, 0x89F05DDB212C47CEULL, 0x741214808D97DC6CULL, 
            0x9E9656EC646BF278ULL, 0x195BD1151847883CULL, 0x58D9486BA087FC72ULL, 0x7B831E3D104CDC63ULL, 
            0x932CD8FB86412206ULL, 0x2D24393B00395C6CULL, 0x1FDD4464E323B728ULL, 0x79E6B2B6F46AA291ULL, 
            0x499D366965D8F7D6ULL, 0xBAF09F82121E5FA9ULL, 0x852F0AF7AA33010BULL, 0xF4C8320DB7D1222AULL
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
            0x754A5E5C68484A43ULL, 0x29CE3CBA440A479FULL, 0x718057F6B20BF641ULL, 0xD8AC375356FCD3E2ULL, 
            0x40BA5404314D27A6ULL, 0x3D8F50EA6ABCAF6FULL, 0xAD554C97637B6CCAULL, 0xC0A3C7BCC411F500ULL, 
            0xF3C8438BC197D550ULL, 0x966C6181478FB3F2ULL, 0xCAE27DA7E29C1A3DULL, 0x495C2769DC164A1DULL, 
            0x3F43C5848C8046E5ULL, 0xE1C5126846EE06D6ULL, 0x4DCC3485140B4416ULL, 0x34E512D0DEC8C176ULL, 
            0x333389585E9D4637ULL, 0x8CF29BE5968C7875ULL, 0xDF1C8D7685376DE3ULL, 0x2669CEDBA04B3F43ULL, 
            0x06D05C9B131AE8B9ULL, 0xBA644332E953D4FBULL, 0x5D64AFBE508873DEULL, 0x1402B631814B7A0AULL, 
            0x32F006BEE0B813A1ULL, 0x529FB5AFDB983D13ULL, 0xDD9053EA0FBD85F1ULL, 0x9F66DC685D24340DULL, 
            0xA5BC175A0A702414ULL, 0xA2D7C57CA2913E32ULL, 0x118C1F29E29A3368ULL, 0x0AB8CB9749459FE8ULL
        },
        {
            0xF31B5FA0AADA259CULL, 0xADCECFD81CE0FF87ULL, 0xFBE636DEC47E3EE5ULL, 0xC0A6EA320337E68EULL, 
            0x7DE9642F2F0DC28BULL, 0xCC34E69816A4718DULL, 0x325237516E4B9F13ULL, 0x531B3DC0BDFB8C45ULL, 
            0x7B4E7B2166E435EBULL, 0x8F25EDA52D638426ULL, 0x54B993DD9DDAEF1CULL, 0xCAD30F84DFCB16D9ULL, 
            0x8E98E2B1364750D5ULL, 0x383CCC6F195476FAULL, 0xFE7455C52B0372BEULL, 0xC45CE6502D10914FULL, 
            0x4BE56308C216035FULL, 0xAFFD9291BBABDDCDULL, 0x2305C6490411981EULL, 0xBD8FD44132C86C9CULL, 
            0x9627194C511E6A3EULL, 0x1AAE68F3CE178990ULL, 0x469693147241B5C5ULL, 0x846F8BC0CD2ADE79ULL, 
            0x76CA6768506DA336ULL, 0x0E69036920E721E1ULL, 0xA49F1AA72A33B17EULL, 0x0B5F55B350FEC1FDULL, 
            0x8907F53AF5E35117ULL, 0x28C5871D56C36DB3ULL, 0x5746F431C63049A7ULL, 0x3C999EE8630469B8ULL
        }
    },
    {
        {
            0xD635BEEF0A060CA0ULL, 0x21514BD4FEA89553ULL, 0xAB248F7DBD681E5AULL, 0x828ABB263F6D3A16ULL, 
            0xA387C6763D7B29F9ULL, 0x09E5137EC8B4B2FBULL, 0xCFEA899EE5E036B4ULL, 0x40EAAB0DE1B135D8ULL, 
            0x0A8D9ED60E1F4ADEULL, 0xF974D8B1D1101A3EULL, 0x8A68F4EB5A5D0A3EULL, 0x3948BFA4B631F4ECULL, 
            0x6E7B1B240D0F7A25ULL, 0x0FC31D0978FC8DC3ULL, 0x63264EA6C771E656ULL, 0xBB7B2CC867F7B026ULL, 
            0x262B8E25C77500F5ULL, 0x0B966476CF444BCCULL, 0xB22804A834F5B788ULL, 0xCC8A12DF1613EC5BULL, 
            0x5F5AB8F6BCABDA9AULL, 0xC55458852E032FB7ULL, 0x5F6171662834FBF3ULL, 0x5E944BBCE1857A4EULL, 
            0xA3731B2EC8F422DAULL, 0x19EBC696C517591FULL, 0x83D1DB15965A471CULL, 0x2F37A45E0C9181C5ULL, 
            0x42F7C34DC8FEFDD9ULL, 0x2E3FDA6EAB848EF0ULL, 0x6E1C0FF249A9804AULL, 0x5F1EC573BF0C1EE3ULL
        },
        {
            0xD885A05E054C3031ULL, 0x0D2FFE1CAF8D6C10ULL, 0x38C735C26473E6DCULL, 0x97A4BD2B022CDF91ULL, 
            0x9E966E2FA6A15AEDULL, 0xA3EF4BF4112A7C47ULL, 0x291E262ED0D7E999ULL, 0x609798B709319846ULL, 
            0xB8A2141674F3AD0EULL, 0x8C277150BC4375B9ULL, 0x6409E6ED241CF201ULL, 0x821D2D97041628D5ULL, 
            0x456608397C7E7377ULL, 0xA047199709FD946FULL, 0xC2A581B0D84A8226ULL, 0xA771F0E5D250ED58ULL, 
            0xFC66B965D466EE15ULL, 0x767E39145D157762ULL, 0xB05B57BC09716AB4ULL, 0xAE383E874B35B03EULL, 
            0x1F1F3E620FB995A4ULL, 0xA5C74DAB5EC9943BULL, 0xC2B1FB4EF49F1EDCULL, 0x2FEE578E433118C2ULL, 
            0xE076DD8E0A21837FULL, 0x2D218356D7E35872ULL, 0x051EDAA892063750ULL, 0x6A3AE26298662E53ULL, 
            0xC6B792581776209AULL, 0x7DF0EDDA325DD302ULL, 0x7AF65F8F423AA6CBULL, 0x7CF3505E9F3D1D8DULL
        },
        {
            0x5E70AC333B07837AULL, 0x21565DFF1490E876ULL, 0xA4E31F5304F155DFULL, 0x1E357D1A2D3A2AD0ULL, 
            0x72808277707ED5C7ULL, 0x8D14559461006275ULL, 0x97FBCD365871EAFEULL, 0x2A3B140C59A66E71ULL, 
            0xB225F249ED6990C0ULL, 0x8F72A2A8CAA82AFBULL, 0xA7BAA95B2D0C5604ULL, 0x11BDC3FF46EB7C95ULL, 
            0x2D9C19C1E5E266E1ULL, 0x45A7ECA065F396CAULL, 0x61047516C69AB1DAULL, 0xAFB273AE7305AFA1ULL, 
            0x187DAC31AADC8E22ULL, 0x0CF1AECAC5E86D92ULL, 0x63C5BCBDA7F3945CULL, 0x94C76F2267038910ULL, 
            0xF61026FD8F0E7238ULL, 0x3701794D56FCFCECULL, 0x670E7D260DC9B8D0ULL, 0x54FE27826AB04D70ULL, 
            0x77D357DFD3BBCBBFULL, 0x535BC6F0E894189AULL, 0xEF60B0D46BED0C02ULL, 0xF0E16284C0032946ULL, 
            0xCD0A9118BB9179B8ULL, 0xAECA84B0D469AB01ULL, 0xC4DC65775903683FULL, 0xD79CB323F64B051EULL
        },
        {
            0x0212699BB8CE077BULL, 0xFBB44E3A0604738CULL, 0xCD5AE01C9F76861EULL, 0x6459320F4B582A4DULL, 
            0x8A63E96FBACD258FULL, 0x54A3B4E3554A9F8EULL, 0xD665575AF907D59FULL, 0xE38E6F13D541927CULL, 
            0xACC5764369B4B53FULL, 0x0E311C280055506FULL, 0x80112C4ED842BC40ULL, 0xF281E917B3F4B4E2ULL, 
            0xA1263167598DD3B9ULL, 0x4494B965B6527E2DULL, 0x9C76C6BAC32B5527ULL, 0x7C0DD84A172E067AULL, 
            0xB1912D1A7214C32AULL, 0xE6AF9CCA1D5551F5ULL, 0x459E53853A225860ULL, 0xC771926AAACDB3BFULL, 
            0x934A23CFC3C3BC0EULL, 0x27E608C90B2C17A1ULL, 0xBCB437D2847D277AULL, 0x45E61A0C8168AF57ULL, 
            0x5ED17CCB738C429BULL, 0xBAF740AC331BFE39ULL, 0x0DA598A351F5C3B4ULL, 0x6186748A81E40205ULL, 
            0x3B361794909F55F7ULL, 0xB85E92F1F5C8F3CEULL, 0xA4F0537A2B4DB487ULL, 0x4DF02FAFB9D3BFC9ULL
        },
        {
            0x30CB8A6752FFFDD5ULL, 0x178F11DA6DF72911ULL, 0xF88BA5476DE0E3CCULL, 0xEFE007A26C5E2BACULL, 
            0xC1DF7BB1B67C0B04ULL, 0x4C241C3321B906A7ULL, 0x5912EE74DE506F9FULL, 0xA15063882998F0EBULL, 
            0xEC9D61A380AB63D9ULL, 0x2456E25EA9E395A3ULL, 0x65E743983AA5C1F5ULL, 0x786AB64247A892BDULL, 
            0x3E75A55FF43BF6BBULL, 0xAF9B02BC9F4DCD5CULL, 0xD9B0241D23556099ULL, 0x2424C2772F6760AEULL, 
            0xC8F24EC47B32394BULL, 0xB35413B115EFAF6CULL, 0x9B5A6AB8C4964F94ULL, 0x2CFC4A06069D9950ULL, 
            0xD5EDCE473A3DC0FAULL, 0xD7FB4D5181146C4BULL, 0x3148CD6695F75D27ULL, 0x7BDF7D2BBAE364C8ULL, 
            0xA75E6C65AB70B18DULL, 0x83CC4A9D68A3A2FCULL, 0x5A922A6641349741ULL, 0xD2F7A7284F0F2203ULL, 
            0xB7B7082253C42958ULL, 0x20F22FF1DB1E4764ULL, 0xE1B40F971F6647A2ULL, 0x0539451C07C82299ULL
        },
        {
            0x5BEB32FCC18571C8ULL, 0xA8793854540E7217ULL, 0xC899390FB4DF0B56ULL, 0x570EB9AF5DB4ED18ULL, 
            0x103C8BEF31C86596ULL, 0x9F1935F361F93DC4ULL, 0x70220C3079D617F6ULL, 0x7684F04BEDF5E2B0ULL, 
            0x59477164D7F665E2ULL, 0xBF15939EC011C648ULL, 0xE2A0123DBD083A76ULL, 0x38BBFDD1C8162592ULL, 
            0xAE09EEE9477D112CULL, 0xD4B076D363F07504ULL, 0xC7ABC0577E5E5496ULL, 0x4968B5A1B80B69F7ULL, 
            0xC1E843C8AA03D056ULL, 0xC7A5129FD53C1DEDULL, 0x3824B38046078FF2ULL, 0x16BC8608AD262234ULL, 
            0xBD0DC7F08E99B16BULL, 0xCF9A796B44E0A52EULL, 0x879C4AC26008109AULL, 0xF5DE84DC63B39E66ULL, 
            0x498420A89AC62637ULL, 0xB2CBC33C6550677BULL, 0xFE21D944E26F3CA6ULL, 0xD78DA544643BF4EDULL, 
            0xA9E1CE5F3C2D4330ULL, 0x9BE0FDF900B33C14ULL, 0x523F21449BD53678ULL, 0x3E2C7EC864383302ULL
        }
    },
    {
        {
            0x4A77640CE7E48570ULL, 0x1804EAEC1932EB74ULL, 0x15B047651F0CE0ADULL, 0x52AD77632A5C70DEULL, 
            0xE0BF29BD4879C398ULL, 0x8FC719887E214B96ULL, 0x4E4669B4177B3EB6ULL, 0xCE6D8E6A0DEBDB11ULL, 
            0xB3D29E559C3021ADULL, 0xC90BA889F3F5B670ULL, 0x94264A7297742927ULL, 0xC1D93B0A124D9AFCULL, 
            0xD68B98A014FE62A5ULL, 0x01C94E566F7C13A7ULL, 0x4837843E8106E0F8ULL, 0x3A03C025DE9BA5BBULL, 
            0x8C51832732343984ULL, 0x408D4B041EADFEACULL, 0xE32D14990ABCAB02ULL, 0xEE0D50E8AF7D330DULL, 
            0xCB57E5FD55AC8E87ULL, 0xEBBC2B7C381F96FEULL, 0xE63D8E3D221909F3ULL, 0x391CBB3E6CFD97E1ULL, 
            0x8EDFC94652892CD6ULL, 0x0E732D75FB06BE73ULL, 0x9DA216B564B9E550ULL, 0x0CE28E9E664C32A2ULL, 
            0xAFBB584C4C2AA0A3ULL, 0x0238FB6265EFEEEFULL, 0xD2E7C3C2AB23123EULL, 0x1D93A9391E7E2F4EULL
        },
        {
            0x079B85D67B14511FULL, 0xF94BD9658A4E0544ULL, 0x0A9CC25AF8DEC31EULL, 0xF8EEAD7ECD69D38DULL, 
            0xDAA576B11EE9C88CULL, 0x4897B1D5889E2476ULL, 0xD333C013E19EC695ULL, 0x4E5B6C0740B70336ULL, 
            0xF9A5D3C3D825EBD8ULL, 0xB13861228C708D46ULL, 0xD9E78CC59989C5E8ULL, 0x31FF2F0C43CE2173ULL, 
            0xC095855D01CCEADFULL, 0x17ACAE088A25D471ULL, 0xA35D5C8885928789ULL, 0xA3E7C3B8904465BFULL, 
            0xD4A52FD07A3C0C75ULL, 0x7E232DB2FB96D757ULL, 0x772B53B54708B57BULL, 0x596BA743DFB2981DULL, 
            0x70F18A1F5E0A3596ULL, 0xEAD4273866C79858ULL, 0x55E289D2F7FCF632ULL, 0x939E0171267ACB2EULL, 
            0xF387E932CDA2839EULL, 0x43260CC53F98A344ULL, 0xF4CE98658D2CE275ULL, 0x7F879F097284B5A7ULL, 
            0x71F74BFD1F3D985EULL, 0x7FF7A630E0201103ULL, 0x3A2CC6217173A31CULL, 0x7F2C4BC65561CD94ULL
        },
        {
            0x6D006BFDB1F589E0ULL, 0xC64E6F3C405B5BB7ULL, 0x23C0F05DF16E6C7DULL, 0x88091D50F83DD119ULL, 
            0x8CFC50A333BB9D5CULL, 0x8B28E24D2FE6BC3EULL, 0x6AEB2AC8880B9B84ULL, 0x769A6031DF944E62ULL, 
            0x225C9A97091BA1E6ULL, 0x509AF9281F2CEE59ULL, 0x2E296222D3DA3447ULL, 0xF88B97B548C629EDULL, 
            0x88325757F9DFDE53ULL, 0x9156C3C55C82EAFBULL, 0xD1AAAE2392B87263ULL, 0x825A9CF730FD1792ULL, 
            0xD04666E6051C3FB8ULL, 0x0CCC52DD1B6AD317ULL, 0xBAE0E74157B2F9BDULL, 0x9BB2F06D9E09CF9BULL, 
            0x9A94735B34665155ULL, 0x9A1BAC4C4556AF4DULL, 0xC7117C3AAEAD3F8BULL, 0x2148D2B889561D81ULL, 
            0x0AB4F8C158DAAF6EULL, 0xCE8E7EE1C7A9BEEFULL, 0x0FD9BE255ECCDE2EULL, 0xF10089E4F8CDC500ULL, 
            0x86D768BCBBD56910ULL, 0x0306A6D9572B7CBFULL, 0x6F3890ABE4E47A85ULL, 0x80A416B07CDD9808ULL
        },
        {
            0x60B40B9E80E24C9CULL, 0x5BF2A430293B2939ULL, 0xFC5D6DADF3AAFF1EULL, 0x583A8275A0F03B37ULL, 
            0xE42DA45D73F9EF02ULL, 0x353D8DEAB66DD6A0ULL, 0xBC11D8FA5A11B11DULL, 0x1F62322CF15A01E7ULL, 
            0xF59C18A4AC824918ULL, 0xEE040D19CC3AACFEULL, 0x87DAD55C97331416ULL, 0xE126D80BD18ED2F3ULL, 
            0x073ABF9229CF97E1ULL, 0xF0B49233C379551EULL, 0xD6B0DF6CC114C619ULL, 0x3CA1336A72726537ULL, 
            0xEBEF60AFF2694F0EULL, 0x611C52965AF5B340ULL, 0x096CF1CBD1F02A6AULL, 0x8AF2292D7FB5DA92ULL, 
            0x2C9F32A61B40EEF9ULL, 0x8E00BB1D3B3DE681ULL, 0x9EADF7379445BF24ULL, 0x9BB25057CAFE47F0ULL, 
            0x193FC70F8CC812D9ULL, 0x9FDA71DC4198912EULL, 0xDA176A8F6F24376AULL, 0x8F9B57009D677303ULL, 
            0xDBFEECFC44D6E211ULL, 0xE84D9748086FA8D9ULL, 0x6C2EDBFDB6EDBF48ULL, 0x5D4C21880A1D1D5AULL
        },
        {
            0x44037BEEC5AC7ECDULL, 0x4F202319354CC069ULL, 0x4784F2C023DAA437ULL, 0xCF584B9FAACD7DD2ULL, 
            0x2E5AC3CDBBB2F8B8ULL, 0x6B1628A7A6D7165DULL, 0xA2164DDD7673135FULL, 0x112A5F52FF89C577ULL, 
            0xD92D0F95C140BF45ULL, 0x485FAA5E301D0738ULL, 0x634EEDC36DAC307BULL, 0x26BA96C72467C412ULL, 
            0xDC7D20FD6D10D4D5ULL, 0x3AAE8627540E1A99ULL, 0xA27655AEA6FFCC1BULL, 0x9FD6CAE2B242779BULL, 
            0x032B2F1D949E928AULL, 0x22FEE30130BA77B0ULL, 0x8DAEE3588AF76296ULL, 0x50C6F6ADD3718FA5ULL, 
            0xAD478593060B76AEULL, 0xB0D5B5049C017579ULL, 0xF01725936E975EF1ULL, 0x0DCA8BC52088EE98ULL, 
            0xEB70E4FB8569743CULL, 0x78AA7734D476084AULL, 0x59022F925455DD53ULL, 0x514A07483A9017D6ULL, 
            0x86A32A21B7B167EFULL, 0xE6FAF41615BEBD87ULL, 0x1EFEF87860DB9BACULL, 0x44A769DAD7CB7C13ULL
        },
        {
            0xB97434565201CA83ULL, 0xD4B0DBEAA6702352ULL, 0xD0959B9B0649B1B5ULL, 0x9230C46B93F0CF12ULL, 
            0x482EA31C083015AFULL, 0x58D58F736AAC22FFULL, 0x4C4C77C1C36E8A7FULL, 0xE19A88355E934A94ULL, 
            0x94DE939832B274D7ULL, 0x61BF15BA22491B96ULL, 0x2F4443B7AF103ED0ULL, 0x9D3F345603B4F5F1ULL, 
            0x91B207489EF21CE6ULL, 0xAEF0F3D5004E802BULL, 0x44BC8B379A56F124ULL, 0x60B245B1411476DCULL, 
            0x339C01B3A4D5E1AAULL, 0xD3F1FF609F049DC3ULL, 0xEEC91A8147B9FBD8ULL, 0x21D09F3665C320FFULL, 
            0xFB96EEBCDD63EBB4ULL, 0xCA149DEA71D6894AULL, 0x28CE4CB33D8A96CEULL, 0x6F7C9056ACAD43CCULL, 
            0x898452943018546AULL, 0xD794C5221E601DADULL, 0x07435DDAD2E2FA51ULL, 0x4B4C1D916352F83AULL, 
            0x78E473B06AF206F8ULL, 0x61A83497931DF198ULL, 0x96296DEDF43D97BCULL, 0x60860DE9EAC05801ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseDConstants = {
    0x5C494F866D166E42ULL,
    0x7DF7F2E3923C039BULL,
    0x86239F23AE73BD98ULL,
    0x5C494F866D166E42ULL,
    0x7DF7F2E3923C039BULL,
    0x86239F23AE73BD98ULL,
    0x53B284C8304D27F7ULL,
    0x54ED69807ECB5864ULL,
    0xA9,
    0x34,
    0xDB,
    0xE9,
    0x31,
    0x21,
    0x18,
    0x38
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseESalts = {
    {
        {
            0x0FFAC1E00A656E46ULL, 0x5D2CF0325CCE8F56ULL, 0xE633839681B6F8F8ULL, 0x01927F9A28633A9FULL, 
            0x42BF38AD22DB3570ULL, 0x5FA5CEA8DA5AF586ULL, 0x94B152B0E0576DB5ULL, 0xEA12878640083AE0ULL, 
            0x0C5B3184811BAD33ULL, 0x747C3C820BC3569BULL, 0x589C87506B66FA50ULL, 0xB2E7DFE144A55530ULL, 
            0x259F3B20756B5BA1ULL, 0x9DD1727913CA8958ULL, 0x809B3EC5012489CCULL, 0xD4E66D5A4C21538AULL, 
            0x1E85CD82A748B1D4ULL, 0x7BE1258542F14DC8ULL, 0xD6BC5D9D51100066ULL, 0xE30B7B8D63BAD6D0ULL, 
            0xA8AB4E7761D4330AULL, 0x585CA4C5B7640515ULL, 0xAD3790FEAD9EF48EULL, 0x78CEAB0F0509BB72ULL, 
            0x37B060C6F801CE59ULL, 0xA14D92CAB4426EFEULL, 0xB8972E06AE69190FULL, 0xE78A2392C320D2FCULL, 
            0x1E05FAB7D2EED3ABULL, 0x7DFFD55DBB348263ULL, 0x7C6C7B2A312E82E0ULL, 0xA3836736EBACF524ULL
        },
        {
            0x3DC7201C7F256FBCULL, 0xFC85B0FC6700D810ULL, 0x1296FE13B06A4EF8ULL, 0xEB41749A9A366AC4ULL, 
            0x6359B25726F64C63ULL, 0x9C9C520E2B1097B5ULL, 0x1790B34A2ADF37D8ULL, 0x1854840003FE9AD4ULL, 
            0xE5A734DF9A06630CULL, 0xDD1A7AB2117AFD39ULL, 0x831A76479B94028CULL, 0x33C13F76663A4F2BULL, 
            0x26EB697930BF2194ULL, 0xB0193A02E3C9860CULL, 0xF1BFE35748C8800EULL, 0x02A12B9EF72FBC1DULL, 
            0x2BF7EEA6107723A1ULL, 0xDD893394AF225222ULL, 0x2EEF97D196485789ULL, 0x59B785AD05BB97FAULL, 
            0x6BB9EE0879E1D4A7ULL, 0xFE7815F69E901AD6ULL, 0x236B90AD67293D06ULL, 0x0CE244EE080AF7F4ULL, 
            0x9776454098D78F34ULL, 0x59DE56F7CCF81B53ULL, 0xF216266BEDDC183CULL, 0xF35774883C2CC3D4ULL, 
            0x8E419EF686712D7FULL, 0xA2FD441A9B37D054ULL, 0xE48903AA9E152367ULL, 0x6A843D4CDEA48B7FULL
        },
        {
            0x079080F1C0A1EBAFULL, 0xB04DB0735A173124ULL, 0x7462ED8A0F94A693ULL, 0xD722B0E543CF015DULL, 
            0xACBE6A1A37658C5FULL, 0xBD74804FEBD6F17CULL, 0x395F008F9C9C0130ULL, 0x3EE1DAC7F337161EULL, 
            0xADCD73AC8792F315ULL, 0xDED793D7B06B3C0EULL, 0x6C0B88DE8C00B827ULL, 0xEFE515B2B2FD89ABULL, 
            0xDE3F8A1D738A470CULL, 0x1DF2F3D8AB2793ACULL, 0x8FC31881D1C22FB8ULL, 0x2C336264C6ADB873ULL, 
            0xE6B529A9C7ED33DEULL, 0xABCBD85C1EFF9B39ULL, 0x0CF7CF04E1DF390DULL, 0x8C839DA5A9CC7F15ULL, 
            0x2DC8F9A927C69595ULL, 0xC9CE2CAF6C3726DBULL, 0xDEC8CA74611448CAULL, 0xAFE5D78AB1380D5EULL, 
            0x93144A1EAF6C0BD9ULL, 0x01E1595C79ED4DF4ULL, 0x1CABC6B7028EA808ULL, 0x97555A966855C4B7ULL, 
            0x582194642C980904ULL, 0x3B7E09D998193706ULL, 0x0069C99ACC28AAADULL, 0x2FD01C1F520583ECULL
        },
        {
            0xF9FE8F81B9C15811ULL, 0x86DE9115A63A8445ULL, 0xED1AACF51DE930FFULL, 0x93D2D27C3F44FDBDULL, 
            0xE8FA8E34F5259F1EULL, 0xD91A7F7CC424970AULL, 0xB50C5332EF168A4FULL, 0x1A0E7FFD15BE7D1BULL, 
            0x433C816C3E8866BFULL, 0x82B4D84C59E27D4BULL, 0x86D04559846A0A8BULL, 0x5B1949AD19D3620BULL, 
            0x474073BD4DECE0B1ULL, 0x69F32FD9F0D4085BULL, 0x269B44FA3C975BE8ULL, 0xE815C8236B4EE565ULL, 
            0xB140325923046F1FULL, 0xBD39CB4C1F1B3F4EULL, 0xC1FAC20BC5B9E6F2ULL, 0xA3A2C0A65F4C7444ULL, 
            0x5A72734462270DB9ULL, 0xEE07CC56A0605AEAULL, 0x5D4E69360FECDFFBULL, 0xA51A9BC05402A57EULL, 
            0x70BB198D75AC2B12ULL, 0xCA8C4D648839EDA6ULL, 0x64F28B75F028A51FULL, 0x13B3702F2E8809C0ULL, 
            0x1CB35A24F7583791ULL, 0x9D76DB0FEA8BF7E7ULL, 0x96BC858FB2DF05BEULL, 0xF14D0988B8D725E9ULL
        },
        {
            0x4415825F86A4ED23ULL, 0xED6B7872905299BEULL, 0x8045AA1589A93B1AULL, 0x727885CDA425D3C1ULL, 
            0x7FCF4B5F84B93AC3ULL, 0xCE93B8C8A686A8B3ULL, 0x992D22FCBD38E589ULL, 0xB7E8DFAD6C5DBF94ULL, 
            0x55DB68CDEDD16E79ULL, 0x926B083C76A19A5AULL, 0x728B8D08907B93B0ULL, 0xD2178BD877379B3EULL, 
            0xFA059E795B57F5BAULL, 0x58D4702502722A23ULL, 0x8857DFB863636846ULL, 0xF6B29A33831031CDULL, 
            0x40FBB77BD81B2989ULL, 0x062CD36B0DDB8141ULL, 0x7FB06B2B0B634EB1ULL, 0xC7DA6E533AABF674ULL, 
            0x7DB92C181676BD0AULL, 0xC4806999084CB38BULL, 0xA0B39716AD554BF9ULL, 0x3BFD797F47C1B6E3ULL, 
            0x5E4AB8328667BA88ULL, 0x812E900F6A5187D8ULL, 0xC2D91D1A112A6847ULL, 0xE11059320BB4FDB8ULL, 
            0x4C38B3BFE22EB8C4ULL, 0xB0A497AB6EB92EC9ULL, 0x9F3B43A4A6EA0C88ULL, 0x4E1DCAA370E71913ULL
        },
        {
            0x5C3366D6C3272EC3ULL, 0x0343AFEF30C1A020ULL, 0xD23531B626526AF4ULL, 0x3FE0B3ADF9DF68B8ULL, 
            0x9A98CF4D099A97ECULL, 0xE9804A62038023C5ULL, 0x7E66151F345A95A3ULL, 0xFC41C1F89E61014FULL, 
            0x6CF8F1B0A516F7A4ULL, 0x2D4E88753D602960ULL, 0x473061FDC5427BC6ULL, 0x69AAE0BD03AB50F6ULL, 
            0xF4000ED128DB30DEULL, 0x5B8158ACB8758E6EULL, 0x51FE85EDBE3A88BAULL, 0x4F8B75CFC03701C0ULL, 
            0xD397AE67BF6BCB75ULL, 0xD74A1A9553AD4E25ULL, 0xB9C0E5E3A36A6B47ULL, 0xB2E4E0A59D88D5E8ULL, 
            0xB141FB56169DADBDULL, 0xE335A9D7C64EB163ULL, 0x5531F9301C3776C4ULL, 0xBADA4D2D79ACCB75ULL, 
            0x8732021ADB1040C4ULL, 0x490EC09DCF2A96FBULL, 0x7231EB1D8D0BE099ULL, 0x7B8FB4F4F2214A9FULL, 
            0xB5A4AE4CAE3AAA9FULL, 0x82352A17C5FB6E55ULL, 0x9733BF5DB784D914ULL, 0xA62DE0B69B575045ULL
        }
    },
    {
        {
            0x58B8BBE551BA8486ULL, 0xB4B95CC5A95C3DD0ULL, 0x3A6FC602A8D8AAE2ULL, 0x7C55B8050C58FCCDULL, 
            0xB84F3C80EFEB86A6ULL, 0x151D5671D748EAFAULL, 0xACDCB1E06CE39F82ULL, 0xC54EEE79E474FFA3ULL, 
            0x438324CE1597514FULL, 0x50E880EBD2CB4BF8ULL, 0x6D827DDCF9701C0CULL, 0x3440A3DE775A548BULL, 
            0x0908589F10857E29ULL, 0xD7D2AED614527639ULL, 0xB0B5A10EE8D6D574ULL, 0x315083AC6F324545ULL, 
            0xD7624BDAF56814DCULL, 0x194AD728CCA35CB9ULL, 0x66D363E2A505E099ULL, 0xFBA33BAC153BB978ULL, 
            0xC85990AA1195B68AULL, 0xB6AF5E53C8D80950ULL, 0xD459B4D64BAA9EF2ULL, 0xB628E1A573231055ULL, 
            0x65BF0B073538EF09ULL, 0x54AD8EFEF6614F85ULL, 0xE09B7E9337DDC57CULL, 0x9DF8E4017BDB6AA6ULL, 
            0xA35DCC8474C7CF3AULL, 0x14A9D1FC239692CDULL, 0x5ABECF1E57E911D9ULL, 0x30D2C78D3E65AA0DULL
        },
        {
            0x600DDB5A27158768ULL, 0xA78605416AB9F567ULL, 0x611A2DE41A526FE8ULL, 0xD92213E9607186DEULL, 
            0xF2116F059E040EA4ULL, 0xC8F47E1623E04005ULL, 0x7CC217AF063DE5C1ULL, 0x2B4612F6517F057FULL, 
            0x17B5E9A7265CAE3CULL, 0x83F7F67C392DC411ULL, 0x8F7C7886E29A4F16ULL, 0x8BB7BB3CFA3B9FBDULL, 
            0x243CBAF445585972ULL, 0xCE7F17AA0EBE21F3ULL, 0x71099EDE090161E3ULL, 0x19C96C414C39C61AULL, 
            0xCED86FA5FCD9C0AAULL, 0x8B361C719F50E9DEULL, 0x5A1381ABB2B41080ULL, 0x0D03855438853EAFULL, 
            0x9CF79CEDA534DBDDULL, 0xDBC2247B5E18D9FAULL, 0x93309AA5C4879038ULL, 0x7646B1F5267DC29BULL, 
            0xBAA4E98D58B5F08CULL, 0x576A8AC6DA5089A1ULL, 0xBAAB649357240288ULL, 0xB2D61C775C8F0B81ULL, 
            0x015F65C927D41E30ULL, 0x76F92C6DFA1C10CBULL, 0xCC8D22672C527689ULL, 0xA6DE588EBEF18302ULL
        },
        {
            0xC8B208692C7B3320ULL, 0x2983DF21F244947BULL, 0x82207E447E82B309ULL, 0x1D1DADC32EC9901EULL, 
            0xCD71AE30D3272984ULL, 0xE6AC69931E4325CEULL, 0x3E5E0BE92D9E7F4FULL, 0x0AED83B044A616DBULL, 
            0xF7593C7D9ABCB155ULL, 0x9E53D666055C14FEULL, 0x34DC818668626C03ULL, 0x6F95ECE75B182D3AULL, 
            0x12CA1BAEF78B73CAULL, 0xA1C25B1BD3ABD0A0ULL, 0x3A43CB1C9F0961FEULL, 0x176B158DE09F268CULL, 
            0xBE967A3F7EE125C8ULL, 0x960ED55BB7A73C72ULL, 0x8B513D6F80883158ULL, 0x1A19260EBFBD6D57ULL, 
            0x9FA8D121C7D11CD6ULL, 0xE8145228544CF9D7ULL, 0x4C1FDDBC4F52A7B2ULL, 0x1DDBD4677270EFD0ULL, 
            0x80B22E74E586BF6FULL, 0x2A77D56E3F27C96DULL, 0x0BD1A98C39561863ULL, 0x560FB9AEB50A1B17ULL, 
            0xF5AC41017F87CAB5ULL, 0xB06EA34BFA6AB245ULL, 0x3DB06F0FB3BF35BFULL, 0xF44DE27F6D91E971ULL
        },
        {
            0xA8DBD5698322D84BULL, 0x57397B7C323D46A7ULL, 0x4434C882F87B1C39ULL, 0xD75C7AD6A014ABCAULL, 
            0xE5E8C3B4ACE5EF77ULL, 0x6445A5E3C9E85EE1ULL, 0x6DFC1EF7A51CCB19ULL, 0x05EB4A4C06A5AB13ULL, 
            0x6BBFE3EEE129DFE5ULL, 0x66728037CB777D75ULL, 0xDE78F2059A28C804ULL, 0x4F855B63AC481838ULL, 
            0xACD6D325EECCE766ULL, 0xBAFBF251D2EDBE3CULL, 0x499A8B9866299675ULL, 0x7462BCEF5525BA9CULL, 
            0xC3A7C314C3F6C662ULL, 0x1947223970067174ULL, 0xEBFB76740BEAE83EULL, 0xB12E5B4320534F94ULL, 
            0x3F8E848B89E030C4ULL, 0x5244897278780EEFULL, 0xE38688A240F7072BULL, 0x4704B30DC8F62FA2ULL, 
            0x908B61086A232ADBULL, 0x4B3286BCB87F0C6BULL, 0x46B507A713CE2DE3ULL, 0x86501B43E65A9EF3ULL, 
            0x59CB59827B033A7DULL, 0x61A88A0291939864ULL, 0x345446ACD96DDA2BULL, 0x5B8D9D9B1CC8BB69ULL
        },
        {
            0x90BDA783733D2198ULL, 0xB69B223DFFC7829FULL, 0x6AC91A9694E3B2BAULL, 0x9C0BBB281066CBD3ULL, 
            0xD5535BD9F78DAC8AULL, 0x7E4D3A8D257011FAULL, 0xB7AC9B7AE24F5676ULL, 0xCA66691B268D2FBCULL, 
            0x87001913895795B3ULL, 0xDDD8B4CA4B4C7F2FULL, 0x5D56A6FF25AC990DULL, 0x3DDA6E75A57AEC43ULL, 
            0x956A073A7FE4E27EULL, 0x906181C55441B236ULL, 0xE2264B713D41348BULL, 0xF02335CB951778DEULL, 
            0x34CD86D1305FE06CULL, 0x1CF315052AC467B1ULL, 0x19C05A728F1F2582ULL, 0x07A268BF68B2B45EULL, 
            0x034D94CE0C4AA609ULL, 0xDFDCEDFBD02654F3ULL, 0x41AB44F578A97E45ULL, 0x751FA5620F9D6D88ULL, 
            0xDB04DAAD0AC92E4CULL, 0x6015E978EA4566CAULL, 0x0BF95B69B28810A8ULL, 0xFB45871F594ECC9EULL, 
            0x11F71D0A909B5976ULL, 0xAD355FB88F581011ULL, 0xA5B3BE25A2B4094DULL, 0x4BDF8C75C2AEAC4AULL
        },
        {
            0x17117B45EEC4BA83ULL, 0x483ACF22B926B617ULL, 0xBA8EE68D4F4EC7C4ULL, 0x8EA777747BB0CB9FULL, 
            0x75B2705AD596EE5BULL, 0xB65B3CE0C2B8DA34ULL, 0x11D547A279AC9657ULL, 0x5E4058202150A7DBULL, 
            0xC9D8DD5C308B48B4ULL, 0xC29258C39A17A99AULL, 0xF92EF7439EB7F98EULL, 0xDA23F26449E09136ULL, 
            0xAD54EE1FC12D4EA6ULL, 0xBDD088F7AD0320A4ULL, 0xD4B677EB2BCCF7D5ULL, 0xDC59781567758240ULL, 
            0xAE93DB3300010EECULL, 0xC660894637DD7078ULL, 0x5E2B0C31FEC659E6ULL, 0x0CBD41284989AB24ULL, 
            0xDB85BD604D173E03ULL, 0x825BCDF7C802151AULL, 0x0844F87195300A58ULL, 0xA5F621E89DABD6DBULL, 
            0x6ABE01772F6A35B2ULL, 0xA1761D42F8359983ULL, 0xBCF3B51D7D3D788EULL, 0x23F6B211E5474317ULL, 
            0x25ED5943A957F0E0ULL, 0xF564194C0E2A3225ULL, 0xE59F6FBB1449C66BULL, 0x4FF69178264AF5EDULL
        }
    },
    {
        {
            0x734B83BAE6670C2BULL, 0x695F79297491C16AULL, 0xC33ECB5D6801F703ULL, 0x7E10BC670979572FULL, 
            0x7A2A2377B911E4BBULL, 0x2D93DEBAA4D2EE4BULL, 0xA77AD512091E126AULL, 0x874B07422AB59EA7ULL, 
            0xDFF8A51785A3B008ULL, 0xB4FB9FCD9E71889BULL, 0x35B7C3D92C01886AULL, 0x5491C258076EE918ULL, 
            0x8EA8E3C89F342AC4ULL, 0x7D11F6396107588BULL, 0xD8059132D2773F80ULL, 0x8FD2226CD9717E32ULL, 
            0x1E6847FC30B2D473ULL, 0xB8358CEE2112B254ULL, 0xE757C1B5C09A0095ULL, 0x4082DACCBFA93964ULL, 
            0xD8D4580ADAE7E64DULL, 0x265DC017551C19C7ULL, 0xA0D9852B1EFFDDE9ULL, 0x98DA7A6F8A7E5081ULL, 
            0x21C4E3BC6D69D7B4ULL, 0x31637FCB628B5FA5ULL, 0x34071F774DD2F66FULL, 0x8181B5EBF028E350ULL, 
            0x02954E278D174F8EULL, 0xF4C5D8E5112890ACULL, 0x4F523EDD17B8B076ULL, 0xC436D1691EFF828CULL
        },
        {
            0xD9F0E5D8F4951EDEULL, 0x3EA43BC2D4E95579ULL, 0x5DE3C48623CC719BULL, 0x3D78482A4AA4BC8CULL, 
            0xF13ABEC5E5A113A4ULL, 0xD887D21C8CAFD45AULL, 0x88A79E71DE20BF8EULL, 0x7E9B6687D24ECDF5ULL, 
            0xFCB03107DD52BA1CULL, 0xB6386AC800AE7254ULL, 0x97DA5BEF1CEC7008ULL, 0xA542118B6ACA6DACULL, 
            0x72E4B017BC7357A5ULL, 0xF96A330248FCB8CDULL, 0x4C6A7ED660636F37ULL, 0x6FB8F04263100DB7ULL, 
            0x8C92551CB880EA69ULL, 0xDC69C71D3618FD3DULL, 0x2B2A744B44297BA0ULL, 0x905D04103D7FA426ULL, 
            0xBA0D144954472860ULL, 0x180E905E633E5D25ULL, 0xE73A9C0F7066513AULL, 0x1C613143485A638AULL, 
            0x8BB272E6C3AB7D3AULL, 0x0C95B41CA63384B6ULL, 0xD0B54DC6BD26623CULL, 0x88F67478E436FD74ULL, 
            0x23A836D58E8136C6ULL, 0xD57188C32FD819A0ULL, 0x4905D8703A7F09C1ULL, 0x06AC174FA9FB9629ULL
        },
        {
            0x0B97D283AA907BDBULL, 0xCDC8D1DB61CEDA58ULL, 0x9FA79A540AEAE80CULL, 0xCEF416229AD980CBULL, 
            0x2A7CF20FA44C377AULL, 0x83BCE5928B7D5B23ULL, 0xB669080B3442E002ULL, 0x20882CAB6C224FF4ULL, 
            0x33B0C07681EFFED0ULL, 0x19F5C64F5EC2C3D8ULL, 0x1ABEC0C074037B37ULL, 0xD5D3825EBA16225AULL, 
            0xFCED44FFCE55C812ULL, 0x303E6AC8D56E6EE9ULL, 0x214B46665F80E048ULL, 0xB347DB6A139C512EULL, 
            0x038637A0EA194817ULL, 0xBB40533214E0522FULL, 0x4C8D583A452B4F1DULL, 0x70238538058794DFULL, 
            0xE3A87D460EBE43B7ULL, 0x771B7272C511FD69ULL, 0x04D979B1D94E0432ULL, 0xE7B1CF0166D0BD4BULL, 
            0x9344BFCAFAB56826ULL, 0x8634F8084A3C5A1FULL, 0xD18FF3C57F985574ULL, 0xB94DEA5797330E07ULL, 
            0xDEC90E0DC27B9B22ULL, 0xF3895888999CC60AULL, 0xD4ECEF0148FCD8EEULL, 0x7AAC98C3695D9620ULL
        },
        {
            0x04FF47ED013AC3ACULL, 0x9A0D0F22CA8B8B52ULL, 0x3441D293A1024FCEULL, 0xD8CE3AFC178653B4ULL, 
            0x7EFF97388632AA9DULL, 0xBA7FF1130AF274DDULL, 0x7C29A913D2B4AEEBULL, 0x9A0431EB23DA486DULL, 
            0xD321D1847CAF76B1ULL, 0xCD777B79F2CBE5FEULL, 0xBD348DD821AAB9B2ULL, 0xEBE65D2582E9BBDFULL, 
            0x041094827D8C67A1ULL, 0x1E3A2AB2FECDB570ULL, 0x12B801A889BAADF6ULL, 0x2DF3D3FB4AD3F468ULL, 
            0x45ED93D334924D6BULL, 0x1137DFBB77865970ULL, 0xBB0B25B31B6556C7ULL, 0xC3D3D9D1D169FC15ULL, 
            0x6785D04CD8FB172DULL, 0x60676265EB5EB4F1ULL, 0xF9675F0DF80D7EE7ULL, 0xCB07FF132850F5DDULL, 
            0x7E0BBF6517A54723ULL, 0x7E874D6EAC9E8110ULL, 0xE8BB4BF1CA5ECC8EULL, 0xBD98FD18FA325509ULL, 
            0xA426B98DA5A681C1ULL, 0xB7886303DEBD3B56ULL, 0x57AA13F753BF5D7EULL, 0xCC8F9816EC77BFADULL
        },
        {
            0xE28F254349B7B411ULL, 0xF00719F16411C2AFULL, 0xB88DBB567A4C0E90ULL, 0xADF15F3BC1A1E47FULL, 
            0xC8C3875C38514860ULL, 0x2CA8953A2FEAA24FULL, 0x109D07B791F17D6EULL, 0xEE49A551FD53501FULL, 
            0x85022E81B6588849ULL, 0x9FFBBE6B5D7038ADULL, 0x639C5D0B757AD069ULL, 0xF7C70E5CC8061702ULL, 
            0x64C4A4C4FF02EE0DULL, 0xEC2C542DF6878CF4ULL, 0xB52AC2DA54B786D1ULL, 0x9645BF0A92F53E06ULL, 
            0x8CDD20669EED67A0ULL, 0xE40CF5F31F5F5379ULL, 0x93FD99515AA31CBEULL, 0x4B0E497E2D62016DULL, 
            0x595188349791DCD1ULL, 0xBB86A2BB7E0465C1ULL, 0xD27FF0A45813CC20ULL, 0x3A92FE981EABE3DDULL, 
            0xF43BEAA3DF75F6CDULL, 0x486722B5A2CF59C9ULL, 0xB5CB36C277D50817ULL, 0x74476249A22F12F7ULL, 
            0xD8A80F9DA09176DDULL, 0x186F899A98C6C725ULL, 0x1B771F8E884C5F1DULL, 0xD51463A15256FB25ULL
        },
        {
            0x4B2441407E505C6DULL, 0x4229EEF9E5CFB3D5ULL, 0x4351D3BB249C45E1ULL, 0x0E8613A02242D7B2ULL, 
            0x541AB753E94E7998ULL, 0x4690E11A107573E1ULL, 0xAB0CB22B4587FF09ULL, 0x934C3D1D0BAE6A34ULL, 
            0x4DB8B635499DC401ULL, 0x1A67231EAFBD418DULL, 0xBFF3A0813B69A7CDULL, 0x1147F03180AB753BULL, 
            0x10ABBC861DB315ACULL, 0x01BFB6D14B3A3137ULL, 0x26A75E86A9CBDCC6ULL, 0x33020880D8F9BB5FULL, 
            0xA8B179496B7BA2A6ULL, 0xBE3185BB37371F87ULL, 0xC125FAAF1D621884ULL, 0x3D2A96D940F3E547ULL, 
            0x1F09243FF8A174C5ULL, 0xEDAC7F6D66DA09EBULL, 0xB37EEFB16CAB8539ULL, 0x3AA47A5FECF39E1DULL, 
            0xA42AC26ED61002FCULL, 0x6F59D2AFE4AAADB8ULL, 0x9430FFA8FF395E84ULL, 0x8F59A3F7EB483A81ULL, 
            0x37A0B50CB76E22E8ULL, 0x4DBA93FCAB0EB26AULL, 0x9FE036984C867897ULL, 0x7A5BDB0E92D9F163ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseEConstants = {
    0xC1993B5D0794D780ULL,
    0x3405CB22B3E1475DULL,
    0x097A658EEC16447CULL,
    0xC1993B5D0794D780ULL,
    0x3405CB22B3E1475DULL,
    0x097A658EEC16447CULL,
    0x2EF6A268DE07DBC9ULL,
    0x882609162D1838FDULL,
    0xFC,
    0x1F,
    0xE1,
    0xE1,
    0xB8,
    0x3A,
    0x10,
    0xB1
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseFSalts = {
    {
        {
            0x7776C1DD010025E3ULL, 0x53ADDBCEFE6D190FULL, 0x770C7016E2718B08ULL, 0x3F0B93C37ADF6624ULL, 
            0x87A3D436348C68BBULL, 0x90A7D847EC1EBBE9ULL, 0x9AFD34D6325ECA38ULL, 0x80C20B30143756BAULL, 
            0xCCA22AD5281D0872ULL, 0x8723954908D106AEULL, 0xC99DDCA5F2921B7AULL, 0xE03B73797327896FULL, 
            0x1BD89375B0D12E1DULL, 0x1C8F2ABADCAC26D6ULL, 0x180A5E71913EFB61ULL, 0x4ABD41A8A8838D90ULL, 
            0xFAAAE73A078E3A43ULL, 0x93FC602E307F3C0FULL, 0x178FA8F2EDCCA807ULL, 0xC2DBE43F463D109AULL, 
            0x812A4C31D22C038CULL, 0xECE8611C4323E9B8ULL, 0x38F0677567962DC6ULL, 0xEF3EB07836CDCD94ULL, 
            0x3090376C290C6DAEULL, 0x4E91698085BA3DD2ULL, 0xD95BF7B0307CCFAFULL, 0x1D95D8F6DDEEB6ABULL, 
            0xD81B8D65AD044FE7ULL, 0x3A6F5A6851B13AC6ULL, 0xC3355DDEDC51690AULL, 0x3188726E54727526ULL
        },
        {
            0x0F647E7841A831A3ULL, 0xB00F3DA8195DABC2ULL, 0xF94040020DA927B0ULL, 0x11BCD4EFBA4669B1ULL, 
            0xAE2D11D5AC4D6171ULL, 0x57D8AE4EB08AE3C5ULL, 0xDD0ECE4613181A02ULL, 0x1AF98F5B1F9AEBB1ULL, 
            0x7525F0900DCE7725ULL, 0xC2387F173D750120ULL, 0x11F9B85F0DE55A95ULL, 0x6772549E8B80153AULL, 
            0x53EA90F650992667ULL, 0x05F5417C11CDB1E8ULL, 0x8B4AD3EFDF8E42E2ULL, 0xD7394A01C060F290ULL, 
            0x8820D9ADFBE2A656ULL, 0x46B3CA045CF61311ULL, 0xEC4E8DC22BA46284ULL, 0xA4CC8D083E2F720BULL, 
            0xABE2B1AF9663AFD3ULL, 0x571DC43AA215356BULL, 0xC4FEE81E9E22C4ABULL, 0x3BEC31E514ED468DULL, 
            0x78A02A04B888D51BULL, 0xEE72374A14271F62ULL, 0x01B24E24DAEF9257ULL, 0x250BDC647C46FB1BULL, 
            0x12C0C62554FC30B1ULL, 0x6D85BB9388F1BD17ULL, 0xBAF8AFF7E7CAC127ULL, 0x17573909CA96EF7EULL
        },
        {
            0xE983CB94D3FF3D5AULL, 0x375BBD13194922E2ULL, 0x9B3C5689DCD41FF8ULL, 0x922502C8EB71951BULL, 
            0x5A7E19E73B606A7CULL, 0xF6C430AE49984BE7ULL, 0x5014B6AB14BB0A32ULL, 0xD3D5BFC58B93B7F3ULL, 
            0x425B301673485DE4ULL, 0xDCFCD4E5DCC9F4C4ULL, 0xC331A6196FEBE925ULL, 0xD861AC4AF29936C5ULL, 
            0x34290DE32FC084B0ULL, 0xEC85703D259DF1B2ULL, 0x1E8D2A1D2A56B0ACULL, 0x97863206ADA22DDDULL, 
            0xA2E0A8578EE306D6ULL, 0x87330DA7DFC227DDULL, 0xB5A7B98104E81FB4ULL, 0x729373F47DF39266ULL, 
            0x3415086F4C8EFB55ULL, 0x154C8AFD09DE2B5EULL, 0x4167817047C7979BULL, 0xF748CC3B0ADBDAF6ULL, 
            0x19C833479FAAF157ULL, 0xEE222CFFCC36A5D4ULL, 0x7AB82B077F36CEF5ULL, 0xA14D24472662A98BULL, 
            0x4BE2C4EEC3F4816CULL, 0x7C479B1CA58C9936ULL, 0xEB284DD401359E36ULL, 0x4A5826521663CEF4ULL
        },
        {
            0xEBC7EEA83972FF4AULL, 0x823D6E9B2962361BULL, 0x7527F5F4EC816A70ULL, 0x64F449CF2C7B80ABULL, 
            0xFBF5E19D70AD68F3ULL, 0xE91A7B5E917B7B0EULL, 0xFC40D66925515C2DULL, 0x866DE4E0FC5BCED7ULL, 
            0xF83DB6531188C90AULL, 0x7260317599E1FD30ULL, 0x6AEE9E3653B35E90ULL, 0x0C442777A4AB8D22ULL, 
            0x40E414C8A1536E86ULL, 0x2ED8E92744F43610ULL, 0x22C7C207021F593EULL, 0xC4B6F9D0858693FBULL, 
            0x09A599D10CED115DULL, 0x980E4C91045D97B8ULL, 0x809BD00BE4F2B334ULL, 0x74CEA69E3287B8C4ULL, 
            0xE0B89465F5D8C36CULL, 0x6E2C64581A4272BFULL, 0xB3BC446033314B69ULL, 0x50865993958CEF3AULL, 
            0x2DA18FDEAB876846ULL, 0x3A4464705871097AULL, 0xACCCACE030587343ULL, 0x2A89BA80D5BEA551ULL, 
            0x73651157310F5545ULL, 0xA391F926FA3B2C2AULL, 0xC0580D7729DB20B5ULL, 0x6533210DAA4C158EULL
        },
        {
            0x3ED2D34C21EEBB27ULL, 0x6D171D27E1FD1D40ULL, 0xEA1F5A459A6BD66CULL, 0x9C9AB1995E2EDBA9ULL, 
            0xFC5DAA776818F471ULL, 0x06447D6CD3C8C3E5ULL, 0x35771DEAE30BF117ULL, 0xD1BD658F24389B15ULL, 
            0x86C5420A096D1B4AULL, 0x6E7FE73B436F5F1BULL, 0x02E3E6C5CEA115E6ULL, 0xC2B572902FD91746ULL, 
            0x6B3066085A7827CCULL, 0x4C38B1AC9C2A4069ULL, 0xC6303BB1DB6C40D3ULL, 0x648718CC31861A09ULL, 
            0x5B8E060FEFAF9A3EULL, 0xAEB8CC2B6D27E68FULL, 0xC32E1598049A8CC8ULL, 0x1B9EDE042EE11235ULL, 
            0xB3CD673E33057601ULL, 0x0A31F064C2ED7F46ULL, 0x788DB82C33C293FCULL, 0x5A73E8ECE1A67A4BULL, 
            0xE0D64E1A8B74B5A4ULL, 0xCB2922DEA44BEDB1ULL, 0x0C5ECBEBAD6B397DULL, 0xB842617D30B8ADF3ULL, 
            0xC682B84DB629FF0EULL, 0x3300A1EFA4157EC3ULL, 0x317DBFC593119C52ULL, 0xC605EEB8823A1CF4ULL
        },
        {
            0x3681E35AE1DCB8D1ULL, 0x95AFD6D06148BE55ULL, 0x980E284E0C01B78DULL, 0x18C33B06B0B85B21ULL, 
            0x60224ECC52BE1300ULL, 0x6C2AF371EC0A216DULL, 0x172896A9A792432BULL, 0x797CBD8873039542ULL, 
            0x856D21A227EB9A7BULL, 0xA36DD339A1A00063ULL, 0x570403593F3C938AULL, 0x6C55F2DC3D8DCC17ULL, 
            0x715BA237E887DFAFULL, 0x37D39D3C5584D74EULL, 0x6200304FCAF141E3ULL, 0xFAE1A18E8035E82AULL, 
            0x653C72A7A5F77A10ULL, 0x6BE0860DEBBA5051ULL, 0x61529AAD789A0481ULL, 0x7D9524CFD10682D8ULL, 
            0xADBF102B73954570ULL, 0xF0DAF0AEA68FD05BULL, 0x218019F167466EFFULL, 0x852EB7972E310F25ULL, 
            0xAD6B5FADFDCE68CEULL, 0x1112A082EA48B740ULL, 0x1C58E54D3FEE1C17ULL, 0x9A0FE66023D1E49DULL, 
            0xE8DFBF29C6647198ULL, 0xD8A9A9BB844B180CULL, 0xEA4CBAFBAA95638BULL, 0xAAB91FB99E8B18FFULL
        }
    },
    {
        {
            0xF0B7ED71BEDC717BULL, 0x8CF0AB3138CE58B3ULL, 0x6B316B46FFCA1C7EULL, 0x67710D645976154AULL, 
            0x9A1CA554AF37A42FULL, 0x3D31D0C57E168AB9ULL, 0xFEA8EF2602C84E4DULL, 0x4A1385840B47480DULL, 
            0xFE9D8695790253D3ULL, 0x56482D30E314878FULL, 0xC61453301D2A7717ULL, 0x73B47DF4E6B2A1FBULL, 
            0x57B59C926AC70A45ULL, 0xC90D78B61E7B3B71ULL, 0x9E8479FF9B2387E9ULL, 0x8EE1E196CF0ED297ULL, 
            0x139894E85D0AABD2ULL, 0xDBD423B60F8F0F5CULL, 0x7407DC88FC4C562EULL, 0xC314A4ACE07D7265ULL, 
            0xA0763F778783D185ULL, 0xBDA714E97E15002EULL, 0xDAAE9519299CCDBAULL, 0x79312B64697E6C0BULL, 
            0xADCA0E70EFC498FBULL, 0x658FFE03A171D071ULL, 0x2F8694F3746D4DCFULL, 0xA3DF94D470F4FC44ULL, 
            0xF838FF9B62B0F52FULL, 0xCF5B471852270313ULL, 0x9E6AF9A8659C3A52ULL, 0x0612FED6955FA3D0ULL
        },
        {
            0xE89EE7CBB0C7FA62ULL, 0x2D168B35B26A98C9ULL, 0xBC5C7A0DA94D2B78ULL, 0xA1B35DAE6EB564EEULL, 
            0x0DEAA9328930298EULL, 0x40FB36B72ABAB639ULL, 0xD9485B8087CE8CDCULL, 0xEF913C74823F0D55ULL, 
            0x6CC82F06220FAE68ULL, 0x2A8815912C9B1F2FULL, 0xEBBA15522727B118ULL, 0xE5956C219994280FULL, 
            0xEDE1379CF0985463ULL, 0x2CC0F863355FDF4FULL, 0xD4793C3AEFA35B0AULL, 0x6ADD60A75EED9821ULL, 
            0x36C7B8AD6D744BF4ULL, 0xACC11751640EC316ULL, 0x93AD7436FC24669EULL, 0x606CE3779F1418C9ULL, 
            0x608013A0D70FC234ULL, 0x879ED813D5BEF0AFULL, 0x90E5061BC6BF87BEULL, 0x52CA64189BD82863ULL, 
            0x9E9075C80DE818A2ULL, 0x6827D6A5C302365CULL, 0x9D7983D14CD66DC6ULL, 0xAD0687FE6F6F2B39ULL, 
            0xCA376A7CB8D74104ULL, 0xD8696D0C310C6C03ULL, 0x630A04F106096177ULL, 0x00B61B714E99A7E1ULL
        },
        {
            0x972386E9B610481BULL, 0xCB95BECA87D41B90ULL, 0xEEE9C806536D8D78ULL, 0xEA35695D26DB50A3ULL, 
            0xA0920B11590A4F9DULL, 0x61F8459D743549E9ULL, 0x9D7057CA0C2C80A9ULL, 0x9212B6C1620A9CEAULL, 
            0xEA80514574A49E1BULL, 0x280EA636131B0158ULL, 0xB64780118B3A1B0BULL, 0xAFBEC62FD5A91F1CULL, 
            0xCA1EFC76034F46C5ULL, 0x494B921712DB8175ULL, 0x7320E619ACD49E6FULL, 0xC4472DA3706E0726ULL, 
            0xC1DB20E940B829CCULL, 0xE32E5C87E0D21787ULL, 0x5F289A0C0EACF484ULL, 0xAC0E332D72A539ACULL, 
            0x645300D242A59045ULL, 0x8119A5545B418A45ULL, 0x9532A11ED3497974ULL, 0x3AA66DA2E0A0A267ULL, 
            0x42A3817A2B7107D6ULL, 0x07400EF06D82F387ULL, 0x466BE9EC011B6158ULL, 0x63FF3BA07C2C587DULL, 
            0x76ECB0917ECC8FB4ULL, 0xE54D2D8B5FBD38CBULL, 0xADEAB760DCD6A38CULL, 0x297CC1239BE2B875ULL
        },
        {
            0x74A8C1C4CA9CF8C6ULL, 0x20B03E7CB33CD12FULL, 0x6D051CFBC6CD5494ULL, 0x9EBBC1BFA0C269A1ULL, 
            0x0EA01B0EAAA9F737ULL, 0x5272AB181F9D7F63ULL, 0x45903C1D0C8CA2E6ULL, 0x090B0C2757CA8156ULL, 
            0x30033DC6B7A84557ULL, 0x077B622ED4034117ULL, 0x01D498DC975627AAULL, 0x020CC7C966E3111FULL, 
            0x3F00D818A35D4EF1ULL, 0x756B6E96CFA7185FULL, 0x79BEC925576AC966ULL, 0x53D7E9C261D132FDULL, 
            0x48BC4F5481643CBBULL, 0xA3D54973E71F34DCULL, 0x7C6A08F61778AE12ULL, 0xD7681AC36ADABD76ULL, 
            0x768501399254679BULL, 0x2A9817394B06D223ULL, 0xC9048D1C28B85B4BULL, 0xB051FCC68C527C22ULL, 
            0x6844ABD3BF21C09CULL, 0x54379951D5B94A92ULL, 0xDE84B0D77F966A9FULL, 0x1A685700708222BCULL, 
            0x3B3B76D6ED413238ULL, 0xABAB528800822C18ULL, 0x2AF9089DB72D45F5ULL, 0xF60740536643F373ULL
        },
        {
            0xDD1EFCF4C08E42EFULL, 0x33EF86B69A49CBB8ULL, 0xC2315DE3E90EF0CFULL, 0x0B29ED92BAD6F809ULL, 
            0x8169AF9A863CAAB7ULL, 0x85F60D56E9AF8449ULL, 0x4C7DE36009FBD401ULL, 0xB253513588593DA7ULL, 
            0x176939522BC9D332ULL, 0x219449D300BF2669ULL, 0x87B9E9002DC4728CULL, 0x69A1B2715AB4CE58ULL, 
            0x09F5869A984BA8B2ULL, 0x47378DA457F172E6ULL, 0x74A6274535E80A0FULL, 0xF1A68513853639A2ULL, 
            0x6859AD554DE2D720ULL, 0x95C27AF7D643B40DULL, 0x1B4C653ED13BEAB0ULL, 0x1EBB0142E541B09FULL, 
            0x8367513B47047644ULL, 0xD7F4E1865DB7A8FDULL, 0x945B857F74D6AC98ULL, 0x528B457C3E27C469ULL, 
            0xD975A175BEDF1B67ULL, 0x82A7C3487E0F6833ULL, 0xA361EE37430AA423ULL, 0x14FB1EEEF798AA1FULL, 
            0xFCE28CC3FCD49B9DULL, 0x6D42CA37DDEDC891ULL, 0xD25560C9E6E45D52ULL, 0xDD53D3DC1C7D1DE3ULL
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
        }
    },
    {
        {
            0x2E0FB136C98E3E34ULL, 0x925EAE5152B042CAULL, 0xBB057F51A1910487ULL, 0x1326DA512F4F3C3DULL, 
            0x8854B5251A07E25DULL, 0x99B02208B1E83141ULL, 0xE933EBB851CA4329ULL, 0xAAC1EB20C8F599ADULL, 
            0x06C5687188A0D838ULL, 0xEA51A2C7FFD5502EULL, 0xB48AF1FC9DB557E2ULL, 0x1C93DEF517629281ULL, 
            0x5F5906F30A6CA636ULL, 0x42BFB09174A1FEF9ULL, 0xE1C90BAF2CD4EB15ULL, 0xA570CFFD8FAB97A9ULL, 
            0x59269FA8DCD05E68ULL, 0xFBAF78F76A810557ULL, 0xCDBA4D702F950C17ULL, 0xBAF1B96FE496E632ULL, 
            0x5A098ACE504BEC11ULL, 0x206C41E82C47E44CULL, 0x0F6B859E3B1A973CULL, 0x77E3F6DDDCF32A94ULL, 
            0x77EBE5FA93B31B24ULL, 0x04655A8B1D6D15BCULL, 0x5B21EEEBED0350DBULL, 0xD4601602593AEDF8ULL, 
            0x26E3E1F5D3DC34D6ULL, 0x1715519966065084ULL, 0x8CA5BC8D9303E696ULL, 0x377600EAC2CEBA05ULL
        },
        {
            0x94DE4BEA38E0A5E6ULL, 0xC83B5E049153C501ULL, 0xEC2384514E151819ULL, 0x0BBA0FD1A985F3BDULL, 
            0x8805BB85CD52CDBDULL, 0x751617D92D1049DFULL, 0x5EA0B937ADFEC761ULL, 0xD387F68C2460DDA2ULL, 
            0xCB878DB42F68A7C2ULL, 0xCBDF10A9C3644FC0ULL, 0x2058F830EE109A05ULL, 0xBD5A792D229EB553ULL, 
            0xA39FAE9C81512697ULL, 0xC0B80BEB7319D9CBULL, 0x213D02EA37142684ULL, 0x21327D3CCD464F5BULL, 
            0x4E5FC7540A89496BULL, 0xF8343778A83B0695ULL, 0x6B58D7391F6FE331ULL, 0xD9A452A23354C2AAULL, 
            0x18D1CB22ED564ACAULL, 0x7F3D6F40CD23EF64ULL, 0x7B252640E6F87820ULL, 0x8DE51AFBD793DE4FULL, 
            0xE106FB6EB87A14D0ULL, 0x334EE6AD6E95F296ULL, 0x75FD7FB1718461E9ULL, 0xC32DCCC4B12C7A3BULL, 
            0x9EE87600C0254AB1ULL, 0xFA4A2B1C2DA3BD44ULL, 0xD1BD7E0FFD48769AULL, 0xAE16BFBD432BE2E8ULL
        },
        {
            0x139EB20EB99B2520ULL, 0x3AC4D0F925E61538ULL, 0xE969B37EA7A2E97FULL, 0x840847B23BBAC120ULL, 
            0x85C5F8BC7427A28CULL, 0x04F47A266CBFB16EULL, 0x0A4A8B3203CE2562ULL, 0x1BFB849D1114E66CULL, 
            0xDD1EB496863DAAF4ULL, 0x975A5B88CA0984F5ULL, 0xA219E6B87F1B08D4ULL, 0xD2BBBA7FAB4881EEULL, 
            0xDE8DE3A14A75DE37ULL, 0x138CC9921240C738ULL, 0x6DCDC1284D684297ULL, 0xA15332EB28BA7F27ULL, 
            0xC71957150382D6A7ULL, 0x4FE19B8BB0AD0FEDULL, 0x048BFC557B928CE0ULL, 0x096A3D22E0452130ULL, 
            0x5FBA0863A5AAA6F6ULL, 0x2ACF949254BBEFA6ULL, 0xDC4A69BB4F6E3869ULL, 0xD5ADDA6FACA81BA6ULL, 
            0x5225BC7FF0FA6575ULL, 0x741CC929C6E922C0ULL, 0xEA9449880369A8A4ULL, 0x04D744998CFF27D4ULL, 
            0xB4C4C7A70F9A1F54ULL, 0x3DFEBE3B227471FDULL, 0x87872FC27876BF3BULL, 0xCF21462C28E5EAC2ULL
        },
        {
            0x15B5720E1E643E0BULL, 0x98F924568A2A0C3EULL, 0x77BD021886D2B9EEULL, 0x372C1DF245FFBDC7ULL, 
            0x7211CB92786E4A49ULL, 0x6DA86CB1F093163DULL, 0xD9E9424BAF9F16A2ULL, 0xFF8AB5949FE93C1FULL, 
            0x9F21542332721DD3ULL, 0x81F4739DB6A15C9BULL, 0x519754298BEB6D2EULL, 0x0F14B2D796A1F9E1ULL, 
            0x0A33A30AF80A63D7ULL, 0x1874F82F04F6ECA1ULL, 0xAD3953DCA5EF7E78ULL, 0xAD43C438C020B2DAULL, 
            0x7934E97C3AF6F6D9ULL, 0x7B00D6210085E72FULL, 0xD36A59DD6569475DULL, 0x6E14A1E11D98A6F4ULL, 
            0xD5C090B5BA3A2D0AULL, 0xE6DC6B76721BBC51ULL, 0x91ACFBE6D42944EDULL, 0xB3F877A4B6C7446AULL, 
            0x785914667F5C85BCULL, 0xF8117843ED2BD534ULL, 0xCDCCCD6CE31A3AD3ULL, 0x66EE40507A617DB8ULL, 
            0x472FE6AE8DCA3C53ULL, 0xBB73B653EF5DEE93ULL, 0x8B11FCAC924B968AULL, 0x70832C84B44F5DDEULL
        },
        {
            0x405E2B467EC6B16EULL, 0xED2FC84B27BF304EULL, 0x8ECFE21C44B7B41DULL, 0xA6A8DFDDE54946A5ULL, 
            0xD34475C03896F237ULL, 0x760E45D8507E1D6FULL, 0x12C68D3F6F96E831ULL, 0xCF0D40D8495456A1ULL, 
            0x8EF770BFDDD68CA6ULL, 0xCFD7920E0E62F588ULL, 0x5574CE1ED5A85493ULL, 0x145DE505D26BD1E6ULL, 
            0xA9771467AABBC2B4ULL, 0x892E2B2A8127ADF3ULL, 0x3DEB62FF8AD3EFEFULL, 0x7B49AB39A093A26EULL, 
            0x11E111A275B95CE7ULL, 0xAEA65C0F5A6D40A0ULL, 0xFBF146669ED9516DULL, 0x1F40A7A240DFD029ULL, 
            0x8679EC1652080818ULL, 0xBA2CBCB45D6FD777ULL, 0xE4414377A7C764EBULL, 0xB2BC6557DF1223EAULL, 
            0x725031EF197A79C6ULL, 0xFF701858113AC068ULL, 0x9ABBCE31DEEBBA41ULL, 0xFF34E5DC7767B77DULL, 
            0xB678DD4C9FDBFD3DULL, 0x66BA7823938EDE3FULL, 0x44C23857F5F69B17ULL, 0x7196FC26D4014FAEULL
        },
        {
            0x741745691EC0EC8EULL, 0x9F0A9A32D5EA7532ULL, 0x1E7C14FB9CF0466AULL, 0x714C7BF4238BC8D4ULL, 
            0x38C1AA700DD8AB06ULL, 0xDCF1E869068C09D5ULL, 0xF1FD22A4BF5D4A45ULL, 0xC1CE067E71646E60ULL, 
            0x22F02883BE564A50ULL, 0x32A6039423E83151ULL, 0x48B4738E6AB6A219ULL, 0x4216D3BF2F7C0F10ULL, 
            0xD4142FF688A147B2ULL, 0x4EE277078BAA3BB3ULL, 0x3A591D3E34620CB5ULL, 0x34B153CA6208D717ULL, 
            0xDC5750BB95E2F4B3ULL, 0xD246F35A2CB359D9ULL, 0x96597EA0F943E122ULL, 0x8FA19A50E334236AULL, 
            0x9F87AAFF9210D1DCULL, 0xB65A51E8D55BBB2AULL, 0x67D10B5A2859C9A8ULL, 0xB219579852CF73B7ULL, 
            0x25F0D967C4715372ULL, 0xE953E3FE012EE518ULL, 0xBB836C7766D31B43ULL, 0x959F4DC6B4384B5DULL, 
            0x3FE8D731E40CD76CULL, 0x08C6B7A35B95D803ULL, 0xA6B4F097B3432FDCULL, 0xD76C53337F1A1124ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseFConstants = {
    0xFCBCB3BEB3A7F02CULL,
    0xA9BF005BD03526D4ULL,
    0xBA67A663E354E38EULL,
    0xFCBCB3BEB3A7F02CULL,
    0xA9BF005BD03526D4ULL,
    0xBA67A663E354E38EULL,
    0x9D64E5436B652C29ULL,
    0x8E792086C030E950ULL,
    0xEA,
    0x27,
    0x1B,
    0x47,
    0x19,
    0x07,
    0x54,
    0x12
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseGSalts = {
    {
        {
            0xEE840C0EC2A4C174ULL, 0x9CB05776B78C8B5AULL, 0x87725BFB164F98B0ULL, 0x7470FF6D221D126DULL, 
            0x4FAA9C77CD4F38E9ULL, 0x924149B438975EE6ULL, 0xC630E9CBE1D10E89ULL, 0x4A0F4230AF035862ULL, 
            0x1C8E68307B3DF614ULL, 0xE22120FF6185AD84ULL, 0xFC92487C9A08E97BULL, 0x9A387C7B3F32FBEFULL, 
            0x1E4ACD692548DA4BULL, 0x8923714CFB416141ULL, 0xB0AC535315A0C2CCULL, 0xB9A5B8036CFF25E5ULL, 
            0x9A22A9B7834B951EULL, 0x040F4698FA399AA8ULL, 0xCF2DAD024BC53C3CULL, 0xE44FFDA1352A4867ULL, 
            0x0402469E2C15553CULL, 0x3AF12D66BED4040FULL, 0x1470EB2334EA116AULL, 0x2ED902A976227E21ULL, 
            0xFC226DD55999A481ULL, 0xE794DCB806AD7735ULL, 0xE6FE72C693F8FC88ULL, 0xE221F2936FDE68AEULL, 
            0x2FBC7A5D4B311A99ULL, 0x44E559ABB92CF8E4ULL, 0x94AF2C5FC1781173ULL, 0x285EE3290BC7FD82ULL
        },
        {
            0x9BC7E2706652E883ULL, 0x65F181F86B9F5B7EULL, 0xF97FAFC3A8F4A3F8ULL, 0x8988E44B6F52F7A7ULL, 
            0x38DB18623884DD67ULL, 0xEF8A544228B30150ULL, 0x548BE9AC800A5321ULL, 0x34CF7C60EA0CB355ULL, 
            0xE41257F134D3FFCCULL, 0xE0EE0B52B19649A5ULL, 0x247F9BE934560202ULL, 0x135441E2BF573C60ULL, 
            0x834FC5C9D31E8459ULL, 0x99D7F91982AB35F9ULL, 0x880A3188BE1852E2ULL, 0x14C6C95C6C3026A1ULL, 
            0x1D6BFD8D46E30AB2ULL, 0xE09FA71BA0F8B958ULL, 0xD5724B3589DB6094ULL, 0xDE7C9D7759D379CFULL, 
            0x37014C9D65645149ULL, 0xF06168DDE4232CF5ULL, 0x7FE4432BF29A362FULL, 0x04644BC085D06677ULL, 
            0xB108C8197F126E28ULL, 0xB9050C0D3FB7763BULL, 0xCF270062612771ECULL, 0x097CB07FB113FEACULL, 
            0x1557A855F037F512ULL, 0x10B2E8118CDDDB6DULL, 0xB083B7F7A5F3634EULL, 0x8DF6980B998C60CFULL
        },
        {
            0xF314CF917004097FULL, 0x22FBD4C281B32E7BULL, 0x33C9DE306ECD2AFBULL, 0x16D967D25A4D59E8ULL, 
            0x1753DD70B9BDB8FEULL, 0x0D6D821DA8DB55B1ULL, 0x88F62B06E7CA9843ULL, 0xD81B88EB03C59733ULL, 
            0xF9E07A80A4335C19ULL, 0xFCE40D91AFC6C65FULL, 0x011881D7C4002134ULL, 0xF471F377A2210817ULL, 
            0x2BC18F71DD68B626ULL, 0x8252158AAB338ED8ULL, 0x6C696D0B9950CAD9ULL, 0x2F535F4360F8C6B8ULL, 
            0x091591E0C3375297ULL, 0xB7B85B5EB94BE836ULL, 0xE45F4FFACAEB931AULL, 0x76E8F6A8F31A6513ULL, 
            0xCC9F788ACE8CE1F8ULL, 0x377C2193E3539C32ULL, 0xBB4E7F0E42635E90ULL, 0x9E1555DCA1474BD2ULL, 
            0x67B6C359199D64F6ULL, 0x66F98BB0B0ED8360ULL, 0x9109B2E092A719D4ULL, 0xFB0129568F23A774ULL, 
            0x911DB393A2671933ULL, 0xD438C98EE89D2EDBULL, 0x4B0CB974E76C8E12ULL, 0xC1616D035DBD454BULL
        },
        {
            0x11BD063112C7385DULL, 0xC10B2812DE7CB389ULL, 0x76301B90614F800EULL, 0x445484044680A134ULL, 
            0x2FB1AA677C4075B0ULL, 0xD20D47587C2E2199ULL, 0xA6E8A6B67EDA06C8ULL, 0x01CEA37F7F94B1CBULL, 
            0x07CE5F21F49D759BULL, 0x5CBA2B9E31C81459ULL, 0xCFD793F5DEEE38A4ULL, 0x4B55159A548F53E0ULL, 
            0xCB4D6341DDE2D91CULL, 0xCFF583D688E8F61FULL, 0x398C9EB74D6FE50FULL, 0xE0E1F24C4E4C4F40ULL, 
            0x977CCE8716FB37A9ULL, 0x41D5278BB7358C51ULL, 0x9E9438BA6E707718ULL, 0xB74BA5440BB4536FULL, 
            0x4F6A04FF83B7AAE8ULL, 0x9B2A4687EBF3EA7DULL, 0xED7B7BC4F2513CB3ULL, 0x6159B6451503A36AULL, 
            0xDE43203CCE29B2D3ULL, 0x5185FB47F8393C9EULL, 0x47B846BD970F0ABFULL, 0x1E15C008AFC99829ULL, 
            0x0AE2F2E744F2CDEDULL, 0x346E64DEC8BD0BEAULL, 0x2280BFC6690BC7D0ULL, 0x63DA30687D143696ULL
        },
        {
            0x04A9AF73A3AA23C2ULL, 0x7D52CA236B26195EULL, 0x7D967818D637AB25ULL, 0x0654CB99699C741CULL, 
            0x6490E853103A0F19ULL, 0x297D9E8D1F8C8725ULL, 0x92BD8AA6A158A987ULL, 0xC68247A32CA1ED6BULL, 
            0x94B82D68B6D30E53ULL, 0x4BAF2E0BE6C960D8ULL, 0x73C1FAC91DDC58E8ULL, 0xFCF7801926F0CE52ULL, 
            0x481289065431168BULL, 0x09D92864D39C1DB3ULL, 0xA3005EF495565503ULL, 0x4D5CBCCE0D5A7FBCULL, 
            0xEC208A960B0CE533ULL, 0x63500DDC45AAA342ULL, 0x4CF4E559A98BD810ULL, 0x79502212FFBFF8BCULL, 
            0xF394F7C4181E98E0ULL, 0x97521061C03BD6E8ULL, 0x61D6627946C867C3ULL, 0xBC1165AA77D3417CULL, 
            0xA082C959DEEAD599ULL, 0x0438B2CCCF24D2D3ULL, 0x7FD0EB6C0D81FFEFULL, 0x6DC50BE89D60387DULL, 
            0xFEFF9EE086E060E7ULL, 0x0FF109BB2BD216BDULL, 0xEE323518B9B9B206ULL, 0xCEAE4B50D0EB4922ULL
        },
        {
            0x993BD26281CB0C68ULL, 0xA5E8D4F0D5D524A7ULL, 0xB3627993DEB16ABEULL, 0x36D3F909B21A96F7ULL, 
            0xF024727F63040D94ULL, 0x9B27F6AEAFE255BFULL, 0xC2D014F09BD3235BULL, 0x2ED6F493A1E1DFEEULL, 
            0xC409A613FDC5B43FULL, 0x1AA0D5FCAC2DF32AULL, 0xE69EDF63FC3F2888ULL, 0x1490B61744991A29ULL, 
            0x78B806D52A276F93ULL, 0xBBE1726B7672D401ULL, 0x56E8248AD3DDA571ULL, 0xDA17F8D68AD80E1AULL, 
            0xBBF996BA4CD6860EULL, 0xAB002DC3B41B4001ULL, 0xBA16D967940FAB56ULL, 0x2F848FFEEA1E656CULL, 
            0x1DD740803D13B3F6ULL, 0x746071DCB4459B13ULL, 0xB4F589DA4AAEED09ULL, 0x62C7460C8750C8B8ULL, 
            0x76BE8A8109FFDD9DULL, 0xCA1EA1F80FCFC013ULL, 0x7834C29366A3FEBDULL, 0x3FD731C5DF739D3FULL, 
            0x218E1FE95553514EULL, 0xE6A68C6AE9F22754ULL, 0x3529D3A3D068EACCULL, 0x4BCAA5DA55940D7CULL
        }
    },
    {
        {
            0x05DE573782F701ADULL, 0xE35B291E023A2ED6ULL, 0x55CDC9D7C8FC8257ULL, 0x39F326081067E60AULL, 
            0x4A0C4646A89E4CF9ULL, 0xA923785E4A41A10EULL, 0x32F62C5230108D8DULL, 0xDE4615677A7E15A4ULL, 
            0x807F6869ADBB9922ULL, 0xD351F08F8DDB88B0ULL, 0xAAB1918D44DFB478ULL, 0x665063C431C442D9ULL, 
            0x303CDD9F053BB12BULL, 0x80219B557EBF164BULL, 0xD51917134B25034DULL, 0xEB70DDEA245384F0ULL, 
            0x77B608CD38DBF7F5ULL, 0xB3E79CC6EA3F1094ULL, 0xCF4268882D96801EULL, 0x2CF034227F3FFF84ULL, 
            0x56039D3E8417B48FULL, 0x1C1D52A3A294F5DBULL, 0x2EBFD6BA16F25489ULL, 0x2404FA7FECF8D50FULL, 
            0x6AFC1907C1163AECULL, 0x0BA70D8B733E785DULL, 0xE417C4E4B6722D43ULL, 0x6DD93CC1A27AAF7FULL, 
            0xE13F41615353193DULL, 0xC9CA21B03DC740E9ULL, 0x862FFA7A13980994ULL, 0x54B861F13918967AULL
        },
        {
            0x3E1C2E82633B1894ULL, 0xBC15342F9E8C0119ULL, 0x583CC4E4BB772796ULL, 0x9EDB1BFB52A3FAA2ULL, 
            0x534C484D34D73620ULL, 0x6F13985CA589E6FFULL, 0xBAA54AAD03C54A46ULL, 0x7EEF8683F10CEF6BULL, 
            0xE70E7917B9407059ULL, 0x3FD0F363C0C8D555ULL, 0x62BD1B9CF611C95CULL, 0x42C7D12B61FA55D1ULL, 
            0xF8B2F0A31367482DULL, 0x58344BE304C2ED26ULL, 0xF17F719B059A1474ULL, 0x531832EBA080C0BCULL, 
            0x9B76376AFD7BE2FEULL, 0x183C63AB12121A27ULL, 0xD40CC18F54D0776CULL, 0xF1018808155756A3ULL, 
            0xE8CAD0E6232FBD65ULL, 0x10423FA58B828235ULL, 0x65EAB7A9100501B1ULL, 0xF6D522F2D462AC0EULL, 
            0xF1D438264D701D8FULL, 0x22FAA31BCF2191BFULL, 0x9DA377EA8DDC2CB9ULL, 0x66782CF89B948206ULL, 
            0x08EFA37805EB1060ULL, 0xE8B07F6CCED8DB4AULL, 0x92D902A3F8C7E2E3ULL, 0x27D33785EBCA354EULL
        },
        {
            0xB36C99E6F0A908B4ULL, 0xAC577C007CF1F006ULL, 0x2A16CB44E6581A85ULL, 0x025D8E9ADC2226FBULL, 
            0xC5E8C635AE4C6E2EULL, 0xC700A7D4BC798903ULL, 0xBB2FC09A7D594C1BULL, 0x50038C380F69AF62ULL, 
            0x5BFD1EECED339F03ULL, 0x1D9B43B8CF649497ULL, 0x7E25E567F471498BULL, 0x452FD6B2750B74C9ULL, 
            0x839DC7F3571141BFULL, 0xC384C4B44B98DF1DULL, 0xEAFDCF8B81A3A554ULL, 0xB5FFEDDFC59FBC45ULL, 
            0xA237D7074DFBF337ULL, 0x6ABDAEC1552F8F98ULL, 0x0928BFFE16D7CF63ULL, 0xB29BC15BAFC666B1ULL, 
            0xC3D60DB6012BCED7ULL, 0x291ABE4247C1CC18ULL, 0xB40662D8ABEAB823ULL, 0xD2A7189F68374CFDULL, 
            0xE527B0F5E658F9B0ULL, 0x89A85A7BEB1F358FULL, 0x222D7A260442CD2DULL, 0x87D91B4D1AF7FE42ULL, 
            0xE65DECDFD9E09721ULL, 0x2855D0B4EBFC58A5ULL, 0x8410D389005C2E6CULL, 0x042D777F3D653411ULL
        },
        {
            0xAFE6DAFF926DEFA7ULL, 0x9E16B55ABE2CF8ABULL, 0xDACC8265F0D1E6C7ULL, 0x2635817F1089B7D9ULL, 
            0xDD45D8D6B5A1CA7DULL, 0x667F3F5D3BD3EB8AULL, 0x8242A58D186BEA0BULL, 0xEE514E43E80E92AFULL, 
            0x16240EE782217B59ULL, 0x99F8C3CD46F8E9C7ULL, 0x0098D79A2021D8CDULL, 0x17430840F41F2BA7ULL, 
            0x052B74BCED37834AULL, 0x47E327E77ABE3895ULL, 0x8EBE63241DF01983ULL, 0x652676AD79FA8FB6ULL, 
            0x1A48C464E760E764ULL, 0x2E8E2D4244BB1A2DULL, 0x622E0A17437C8D2AULL, 0xDC8DDE2D9E986B66ULL, 
            0x58FAF92397F8B9DDULL, 0xC61B04B0134407F5ULL, 0xDF5EAA5FA48FD23FULL, 0xFBFCB474C18666B9ULL, 
            0xF586E51F632AE028ULL, 0x0AB974A0480D76EBULL, 0x1812E134DBD5E819ULL, 0x6C953C245206207DULL, 
            0xEAD9F55E974450CFULL, 0xBABE4BA0939BCA90ULL, 0xF6F03AA1CF6C0AF7ULL, 0xFF5EE05344E45BBEULL
        },
        {
            0x23C9BA09271185BAULL, 0xA2DF0F8990294428ULL, 0x130802056492454FULL, 0xEC606892F6E30C5DULL, 
            0xED55FD92275EC51CULL, 0x5CE9E87BE6EF41D8ULL, 0x137F46F750648C2BULL, 0xFB2B1B91EB7977B2ULL, 
            0x892FCEA5ADBCCE53ULL, 0x484A4B5AC1232A52ULL, 0x5A9A67CA6C240EA3ULL, 0x63121A9A3C7EAC94ULL, 
            0x9B8FD523291A7B58ULL, 0xDF4FAD744CC5796BULL, 0xF3EB328DF6250C48ULL, 0x514FDE93828CAB07ULL, 
            0x075E2B00453931F7ULL, 0xC25F0BF3EA8F26F9ULL, 0x416AE30804E1B2EEULL, 0x4B80C719C17F2023ULL, 
            0x50539B66D236E549ULL, 0x53B05F45D916C66EULL, 0x1B450B352E15636FULL, 0x4A42893FFEC4DF5AULL, 
            0x5B0EE4186F094E8DULL, 0xDE2211B9EEF19784ULL, 0xDD6B665D4BB3ED15ULL, 0xA42590D2CB8CA3DBULL, 
            0x0211B594E0248CFAULL, 0x032E31C71F1B75ABULL, 0x731D66F1F2979376ULL, 0x626FF64FB76D9DDAULL
        },
        {
            0xBB18432CF609C3BDULL, 0x277802AA6A61FA24ULL, 0x1B0D48254A2D052FULL, 0x1696C0014C0C7E17ULL, 
            0x88BF2AE811CEA607ULL, 0xBA7BDF4B6C7EBD5FULL, 0x24CF080D948F84CCULL, 0x62FFDCBF045E62CBULL, 
            0x63D778001CEBC2F9ULL, 0x8780D3236D617273ULL, 0xC0F81D38C74A2DA4ULL, 0x7E9111F3B2591953ULL, 
            0x332F4F1EA8A0E494ULL, 0x10C32AEC04EC0525ULL, 0xD2DCCCCC9CE53C9FULL, 0x730234B4CB080F92ULL, 
            0x941FFF5B1C7A4D33ULL, 0xC66132D552D66EF4ULL, 0x0A999CBDCB2B719DULL, 0xCFC9EE372914BBBFULL, 
            0xD79A33D621B4734FULL, 0xBAF7AF43F411083DULL, 0x09BBF943248A046DULL, 0x72EDF292F7A26185ULL, 
            0x0880F43F6EB60E54ULL, 0x541B952FFDA0F96CULL, 0x9DA04AD815F6C273ULL, 0xC03F29496A87CBF9ULL, 
            0x7F112BD685E4FBAEULL, 0x050C5D26AFE4EA91ULL, 0x7F729CB8421A472CULL, 0x7FE97ED3E5F22763ULL
        }
    },
    {
        {
            0x138822E09992D490ULL, 0x12CB7F9C13D348AEULL, 0xBC967766147D5283ULL, 0x5DBE107CEA2FD164ULL, 
            0x9216598D8B7B8A56ULL, 0x2F2439C576DA5E82ULL, 0x9E9EA407E002A282ULL, 0x69F17F4B4ED7DBB0ULL, 
            0x67FA8AFF57E48784ULL, 0xF0706A1881A158AEULL, 0x3BAFD945BACFCCFEULL, 0xBA1B90E5F1CFE9A4ULL, 
            0x5B48F10BF3EA29F5ULL, 0xEB7729FF4E93BBDAULL, 0xF9F796F9DC333E2BULL, 0xAD8FCAB649FE67D3ULL, 
            0x5CA9BB9F6FC001C2ULL, 0x16A4F06F52B9C344ULL, 0x5C39A217A3A1F3E0ULL, 0x81837D4B47A5BF4AULL, 
            0xB35193EC74B37E43ULL, 0x020B9A4E1A9EF588ULL, 0xE0AA8506C38E0A87ULL, 0x7E52854F5A1FE87CULL, 
            0x58C604B5C009E25CULL, 0x3DB7121DCAA1CB9FULL, 0x83FBEA0470824D01ULL, 0xB26376D349009F56ULL, 
            0xC5598B4061457978ULL, 0x5F6827F7509EFF49ULL, 0xF0DEC2420AF46572ULL, 0x80DF33278872A8C9ULL
        },
        {
            0x491F00F5EF7C2013ULL, 0x68E40F5AFA04B9B9ULL, 0xF79FB17BEBC03986ULL, 0x9B8E042F3D293BD0ULL, 
            0x3C3FF522119E6875ULL, 0x2F2A644E85883BDAULL, 0xC7931561784695C9ULL, 0xC85D16DE6F9C5EB7ULL, 
            0x4A396BB3FCB71843ULL, 0x38253D226B3659FBULL, 0x1C94685608530CD7ULL, 0x34DF441F99FC771BULL, 
            0x2F7DE204B073458DULL, 0xE4206AAE20088A17ULL, 0x098DAF8E07D8C4B7ULL, 0xFC3063BC65D0678AULL, 
            0xEF66F0C95ECA98E0ULL, 0xF3DB1C6586818CD9ULL, 0xC41CAF38D7E361E8ULL, 0x81D1EE6F1E223578ULL, 
            0x71F5EC528A2EFB5EULL, 0xF414F50E70EDBEA6ULL, 0x3CB78242C8788CD0ULL, 0x330AD0065C23F470ULL, 
            0x6231BD78E1A25EFBULL, 0x873AE1406A815ACCULL, 0x9FF7E4AE534CFC9FULL, 0xB451E80ED496BECCULL, 
            0x17F1FD2B97C105E0ULL, 0x495C43B8874165E3ULL, 0xC1A8B6A41D611974ULL, 0x1821D7C7EE13D732ULL
        },
        {
            0x5DEBEBADC56D781DULL, 0xA4D4AFD0240B42C0ULL, 0x6F0BDBE2CF8C2485ULL, 0x0024C6A5B5BC23F4ULL, 
            0x6DC4B93B64BC3929ULL, 0x58B484E8B0349A8DULL, 0x2027A62A6C03EC93ULL, 0x5CBDC490068E6CF5ULL, 
            0x2164D93EE9C57C35ULL, 0x1B6C051B80631BD5ULL, 0xF09FB084CBC56150ULL, 0x8F84595C880CBB1DULL, 
            0x9CE5662269DFCE8FULL, 0xF3953031A8B5462AULL, 0x12288ED03A6160F5ULL, 0x3AC22B86227618CAULL, 
            0x67B0728818A4CDCBULL, 0x352BCA67AC146E60ULL, 0xBBA8A902FB9CBAF1ULL, 0xAED2AFAD9CA6F7A1ULL, 
            0x3330CBFC3BA914F2ULL, 0x8DE60BDCF8459B01ULL, 0x0E700C6D409808DBULL, 0xC90B7F58C7E236D5ULL, 
            0x4F2C7E160CBBCFA2ULL, 0xB6E8B2E20B05131FULL, 0x844F04484F1A3B1FULL, 0xF4DC5E9864DD1BF1ULL, 
            0x35FB25F6854BF8D5ULL, 0xA336A97B2150C22BULL, 0x05815AE36BA9CA26ULL, 0x07D645021A503DBEULL
        },
        {
            0x36F9D771A3623D8EULL, 0x72C84F1B6052A3DDULL, 0xD93F33C145E3A064ULL, 0xD5040B36DA58A101ULL, 
            0x78F98E6F070D9490ULL, 0x956475C23958C577ULL, 0x86D6380DE0E9B015ULL, 0xA4F0F37CF61036DCULL, 
            0x3EFB7D42F96AE071ULL, 0x91574B20B324BB3DULL, 0x5737CE9A98CE75D0ULL, 0x6E63057F68D4201EULL, 
            0xF8E3CF952B74D65DULL, 0x2FF434BD6B03E525ULL, 0x0946710B184C0587ULL, 0x0F28B9A55C9448D9ULL, 
            0xEC3432976F10DF60ULL, 0x89C9C67F892ABC09ULL, 0x0D1121DF13FE6B70ULL, 0x750E45BCC8114F1AULL, 
            0x93B58C07829B6AA4ULL, 0xD705D6A587041C18ULL, 0x27001FFDE00A3D71ULL, 0xB8991124E528CB28ULL, 
            0x71C777BA5DB3D19CULL, 0xBA6960C858D11FA8ULL, 0xF0C76F2EF6716138ULL, 0xD9B21F5F1AF50287ULL, 
            0x63E19CD6D4D31100ULL, 0x14ED4E2230E67C5CULL, 0x0280CCC00A485F46ULL, 0x8F0332C2B59B861FULL
        },
        {
            0xC0D02D2F0FB65026ULL, 0xC6A0FC920427FFC7ULL, 0xCD11CD67D77FF49DULL, 0xB02487E7466E894AULL, 
            0xD9DCA2419C295327ULL, 0x21E33A94B24D6BBCULL, 0x8918FD713E57E780ULL, 0x6E4AC271B4B54284ULL, 
            0x60538850828AD18BULL, 0x39E7AC535EDD4AF2ULL, 0x50D84D3194AA3B64ULL, 0x0172F8D3DACECCD9ULL, 
            0x23914CE37F54D05BULL, 0x44DE147494356E5FULL, 0xC43178BC6FE602FFULL, 0xB973F33D515C46A7ULL, 
            0x3038954FAB7FC1E8ULL, 0x07FB744C6863A384ULL, 0xE38B6B0BF48E4A74ULL, 0x69C48D32B8B22FDEULL, 
            0xD945CE9B50391663ULL, 0x5903BC35AEEC772CULL, 0xC4460A47A97B5705ULL, 0x9FB1403C2E803B30ULL, 
            0x537ED7CB5CD12572ULL, 0x4621654482425F78ULL, 0xA14151B8F91C4CA9ULL, 0x341C21D6065C6198ULL, 
            0x9C0097884274C0DEULL, 0x3F014A93528BB07CULL, 0x6A6B4B32B3EDEB82ULL, 0x1B13AB377FE836F3ULL
        },
        {
            0x2FF081B8E70AAA08ULL, 0xFACD90206220C6FDULL, 0x460FD444A7D4BF09ULL, 0xAAAC8CAB35B9CF07ULL, 
            0x6853854E530EA083ULL, 0xF2D8BF69E3CAB416ULL, 0x2148D6E2EA7A3AA6ULL, 0x3803422DED437EF1ULL, 
            0x53F51C623041C8C2ULL, 0xBD2CFC755F1AA000ULL, 0xA2429CE1C977AC6EULL, 0xAB000DD1883B23EDULL, 
            0xF3850AC593E6BDC1ULL, 0x5011158F11B74946ULL, 0xA074593043537C9FULL, 0xB3D48314054866F3ULL, 
            0xE3E25B94822134FBULL, 0xCC11F7CCD305683BULL, 0x73164CB8FA33B95EULL, 0x0190DC630FF7251EULL, 
            0xA96BF93BF2C19E60ULL, 0xE31F2F3596FFD514ULL, 0x79702B502B7ED105ULL, 0x35D6EFAC132FAA8BULL, 
            0x7512DEEAAE7E2ABFULL, 0x419392FF0B7BD394ULL, 0xB901CF4EA804AB8FULL, 0xF5AF780A5EA5F0CDULL, 
            0x78A77302655405B5ULL, 0xFBC13ACBB6535AC0ULL, 0xDA49CB7599C9649AULL, 0x8BDA6D5DD92C3D4BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseGConstants = {
    0x2D006F622F971441ULL,
    0xE45D94D38EEED57AULL,
    0xD22E80D897FA002DULL,
    0x2D006F622F971441ULL,
    0xE45D94D38EEED57AULL,
    0xD22E80D897FA002DULL,
    0xD95A34B0F96C9615ULL,
    0xA936A16C31AA7282ULL,
    0x46,
    0x4F,
    0x60,
    0xDB,
    0x90,
    0x36,
    0xF0,
    0xC8
};

const TwistDomainSaltSet TwistExpander_Polaris::kPhaseHSalts = {
    {
        {
            0xF2674B8E80956FA0ULL, 0x2C99FA220CBFE0E3ULL, 0x95836A2C6A38AC45ULL, 0x51D1EB9B7B3E9A7BULL, 
            0xE6E83F7FDE4C3D8DULL, 0xC04CE6B0A3F010F0ULL, 0x2069F49798C21B26ULL, 0x4ECFD1B167421EC0ULL, 
            0x8B45215E19BEFDEBULL, 0x3BEF9E6333E037F5ULL, 0x75480073EE83C152ULL, 0x07740E1BFB02947CULL, 
            0x0C4B8D69E59C984EULL, 0x2A5B2501F88B8CB2ULL, 0xFE83237B76C97BE2ULL, 0x5620863377C82B59ULL, 
            0x13DBAAFF5865E062ULL, 0x83B28AFAE7989C4BULL, 0x4BE319212B7C62C8ULL, 0xFB1B1974AC0E0309ULL, 
            0x5ABA379D844572C3ULL, 0x55BC2B0AEAF0C674ULL, 0xD96A279044B6C733ULL, 0x56FBD631EE3CE95AULL, 
            0x7D0C3FEEA63BECE8ULL, 0x315CE00C4F68AD1DULL, 0x8E7A0EF77179B1E5ULL, 0xF03AFC6758378513ULL, 
            0x7ACC42F4EBBB7BB4ULL, 0x0EE0230E0192DE74ULL, 0x6CD16259656D742DULL, 0x63149E0EA4D1D7D2ULL
        },
        {
            0x787F91198649F08EULL, 0x501B2DF76734B7F9ULL, 0x5D9F76034A2201B5ULL, 0xA08E8B4C578B4E7AULL, 
            0xB57F5A9C44E80C25ULL, 0xF742E67AA0C58544ULL, 0xAB544F63555E5FB0ULL, 0x1EC5331BA26EB48EULL, 
            0xAD881AB6CC45FAC7ULL, 0xDB1C5F4C5780B609ULL, 0x5BD6248F79676976ULL, 0x214DE99D3479D822ULL, 
            0x33F89BCD0901DE09ULL, 0xFE8581B52C3532DAULL, 0xF598F2A7D6B83F34ULL, 0x93D08D50BAF3E885ULL, 
            0x44634AF9F202E7DFULL, 0xC06CE95FF00DC75BULL, 0x2EBA15EA70296951ULL, 0xFA080E033E14AB3EULL, 
            0xC4E74BAC2D2581B9ULL, 0xF84225BB7D705A36ULL, 0x8322ED0FBA6FEFF1ULL, 0xBDA98257BE614CA6ULL, 
            0x311EE7F137619976ULL, 0x89C013582D45DC90ULL, 0x3262AD76DCB7793AULL, 0x272AC420EC274E34ULL, 
            0x628527B18D2ED7F9ULL, 0xE5CCB32DBC3BE39BULL, 0xA64BCF92E6D40D79ULL, 0x821BE91217D60688ULL
        },
        {
            0x05B0C0E10AD22197ULL, 0xBF945D6CDF589A65ULL, 0xCC184EF36F7B4FADULL, 0xE379FA0AEA38DB90ULL, 
            0x83FD0614F8BB62B6ULL, 0x63F349E7AD2B493BULL, 0xAC044372731EF3E0ULL, 0x45A7BB8E5E958883ULL, 
            0xDBCC41029ABA8E7CULL, 0xAB5171E25C25D5DDULL, 0x875D4E82D534F23DULL, 0xF3B88419AF76A39CULL, 
            0x52D24431176B9B67ULL, 0xA9CC9C24D4C4296FULL, 0x80FEC16326146144ULL, 0x20781E419B7EE75EULL, 
            0xC224C0FDA597D07DULL, 0x3595B3AAB18185E4ULL, 0x9AF327CC7037215BULL, 0x7EDB5C795896996FULL, 
            0x0D82F3BEAE6856C1ULL, 0xEE46EE13BB2F4EA7ULL, 0x31129B6BFF048066ULL, 0x94A43E9E3AC1E76AULL, 
            0xF66929E1837BADF1ULL, 0x9047BE57C51EA894ULL, 0x1513E41CC48FB600ULL, 0x4C103399A46713C8ULL, 
            0xCE04A7383A14A1B6ULL, 0x9A8FA8F9A1BC939AULL, 0x6D9152CA00D31BCEULL, 0x60BFBB9D3D737446ULL
        },
        {
            0x0E72F67E45CB0C86ULL, 0x74788D5813B6A1FDULL, 0xB80C4B789F0D62FFULL, 0x17F5FFD243DAA346ULL, 
            0x670BA1C47AF1388CULL, 0xAD69A90F62B9353DULL, 0x7DAF3BEA71A37A88ULL, 0x74D26C7B5FC0184CULL, 
            0x5C8ECF7D173B98CBULL, 0x2897F46BEBDFDD0DULL, 0x6582BDBD18BD5E26ULL, 0x7191F556B30BE12DULL, 
            0x663AE1B91A650034ULL, 0x3456C655DF1E73D2ULL, 0xEFAB2C245D4B2257ULL, 0xCA487F55BB7709ADULL, 
            0x4124A049B3B5C644ULL, 0x1CD4AF9F27BB6D05ULL, 0xCEE32910D73AD522ULL, 0x2B8B9F3D5325D5E2ULL, 
            0x75A3B0ADCEB9941CULL, 0x9282C72A3CE60AE5ULL, 0x16486409F27D6F29ULL, 0xA913BDDD5F8DE4ACULL, 
            0xFD745E16F60D0D5AULL, 0x4929779892192B03ULL, 0xE3E8696A5B722476ULL, 0x0DBA5CF4F4D75095ULL, 
            0x4065BD019E087869ULL, 0x7112E623F48D3D4EULL, 0xE7D4106F5BBD84CBULL, 0x50E7D1E27C3C0597ULL
        },
        {
            0x064801F9C75F932BULL, 0x80D7ACE3EA777CBFULL, 0x29B03AA3A88B933CULL, 0xD444B37710101FFEULL, 
            0x95771057A2173C01ULL, 0x25E5CF8B2055202AULL, 0xB05D9FD59982904BULL, 0xA98980AA6D7A07C1ULL, 
            0x0798A6D5BCE442F7ULL, 0xFDA7020C9CF43317ULL, 0xCE54806F7D404611ULL, 0x0F3BFD11928A38D2ULL, 
            0x69158E7D071FA3FDULL, 0x73FA4F3266639A55ULL, 0xBFD7DC23F951F30AULL, 0x545F6B007414E42FULL, 
            0x268EF72508F5E7E7ULL, 0x34277470DB06602CULL, 0xE7589C6768088169ULL, 0x13B2D22D8CFD5FD4ULL, 
            0xA8D431809DD71537ULL, 0xBADEB61968F94113ULL, 0x9E9D238948DBE8BDULL, 0xAFE2B0CC31373C1DULL, 
            0xD3A760120EB2228FULL, 0x4E412CFA479AAC56ULL, 0x5D4A89300689A574ULL, 0xDBCD455AD82CE82AULL, 
            0xD30E219DF8410DC3ULL, 0x69B7CD2FC2E45D11ULL, 0x834A9D0B0093D5F8ULL, 0x5411EEC8E21045A7ULL
        },
        {
            0xBC15BC326C810F3AULL, 0x5B71FCAD5FE380E7ULL, 0xF91DE7485AA80DCBULL, 0x01EB9FE1AF996C82ULL, 
            0xBFE2A99571766C7BULL, 0x8D642621F13DD5BBULL, 0x71A17F6F1D68CD04ULL, 0xFF9519E7DCBC516EULL, 
            0x7F60F3B763CDDE4CULL, 0x71605ED99D414C94ULL, 0x79A5364FA29DBCCCULL, 0x5D8551A8E6021712ULL, 
            0xA19EED810140BFD2ULL, 0xC48470DB5BE1B63FULL, 0x535CAD53322085ACULL, 0xCC921E45688A1ADAULL, 
            0xA141680D2E4CC067ULL, 0x23DAFE70E0733AB0ULL, 0xAB77E6F22D5CC5C9ULL, 0xE396165E04F02ED0ULL, 
            0xDDA3DC23E0C499F9ULL, 0xF8CFFB057437E65AULL, 0x07662326B676A80AULL, 0xAFABEFAFDF5E3F07ULL, 
            0x400AFA6944A8671EULL, 0xA51580DEEB272FF3ULL, 0x5FF5AE5523D9EAF4ULL, 0xA79E82ED29096772ULL, 
            0x4186E746EC28C6BDULL, 0x2CBC4707F3DEC1A3ULL, 0x62DAA3960F58AF75ULL, 0x6C91EE29FE6C485FULL
        }
    },
    {
        {
            0x7E7F66204D39AC3CULL, 0x788C2466F9042574ULL, 0xB8E519138681EED2ULL, 0xF3880DEF0CFE9BE3ULL, 
            0x9C4A72D97D64A648ULL, 0xBBE91AAB98265751ULL, 0xC39D9D10C540C5B8ULL, 0xD85213FAAE199D84ULL, 
            0x7D107B14B145E5B2ULL, 0x6F82DCB3CB88036DULL, 0x3204DB4A60FD59A5ULL, 0x0FC4A0B9EF78DDDFULL, 
            0x993BDE77967D15ADULL, 0x3EB700B1B94134C6ULL, 0xBA450319FA488E7DULL, 0x0CE24D7C3F543861ULL, 
            0x9C57CA321906241BULL, 0x18D644CDB4973BFFULL, 0xF6D1BBABEB3517E1ULL, 0x930F514D31BE584AULL, 
            0xF2048ADA94FA4A07ULL, 0x4CB70086B7DE1123ULL, 0xF744A41F38761BB0ULL, 0xBECB842C97FFD5B9ULL, 
            0xE67C302EF008E16FULL, 0x173D334BB48DB08EULL, 0xCBB6E198CFE36189ULL, 0x00F7B460ADBCC283ULL, 
            0x44DD31D938D756E6ULL, 0xEAB6182418736C42ULL, 0xBAA82DBF92133EF1ULL, 0xD7D6AD096207BCC2ULL
        },
        {
            0x03C46E4F574B3834ULL, 0x6198E07697EAD94BULL, 0x94588763DC40BB5CULL, 0x5F8E1E79B9FA5DA8ULL, 
            0xE1E2C90CBD73A7AFULL, 0x0736A4413DD142BFULL, 0x4A91D404D7939402ULL, 0x07AB0A8635C3A410ULL, 
            0x13C1DA8F2B5E7CC8ULL, 0xBBCF950525583DBCULL, 0x5DAA1FF8088F060BULL, 0x1DDB45BC169F13F1ULL, 
            0xE6DD5BFA7FBE1DD7ULL, 0x3EA999AF72121389ULL, 0x15D2458255401B73ULL, 0xBF1F8E3543242059ULL, 
            0x2C027275408A3815ULL, 0xB658D2D46CC05E47ULL, 0xB55A39C4D8632249ULL, 0x1E539EE3E453AC91ULL, 
            0xA80791DFE16C6A16ULL, 0x48D9B5FEFB2D67B5ULL, 0x954B60941FF17E89ULL, 0xDCAB589E63CEE5EAULL, 
            0xD501C9C8DBFE31DAULL, 0x2D580FD0D28CE316ULL, 0x82B3D101D96B7330ULL, 0x411471CFF1383791ULL, 
            0x2FB9F05FB6847215ULL, 0xD291DF3416F2183DULL, 0x4F5B032725C192B0ULL, 0x38249537CE42FAC4ULL
        },
        {
            0xB28D84475B5233B3ULL, 0x94DE705E71EB11FCULL, 0x547FFD599F04A176ULL, 0x4F1E7E46DA88E48DULL, 
            0x30E85AB367697E47ULL, 0xFE2352F3BF9D55BEULL, 0xCDC4D2ACCF6B359AULL, 0xEB5987F1A1547DFEULL, 
            0x018DD85C32CA64AAULL, 0x7918969752B9F2B3ULL, 0xCA55B88CE60B7799ULL, 0xCA6C21A1ACE0CA8AULL, 
            0x34E8FA76E208C1ECULL, 0x19E36DEA475870B2ULL, 0x7AE18F62628537F5ULL, 0x29CD3F13AEE7FAD1ULL, 
            0x0C1E0BB13A92CC93ULL, 0x564EEBE87E296C4DULL, 0xBA4448F227CF9877ULL, 0xD58DE5294F28BE36ULL, 
            0xF9F8DB902798F89BULL, 0xF588FC2D31E07C8DULL, 0x9996655116138F5BULL, 0x64B6EDE6FCFC1403ULL, 
            0x6BEE00FAE404B9CEULL, 0x338B408FC013765FULL, 0x7DE285A2925DCDF4ULL, 0xAC5B840A1096706BULL, 
            0x9A340A3BA9C97ED5ULL, 0x262B2D9D6DE7F624ULL, 0xD3CC5D64904190CDULL, 0x3D652F3C8566EF06ULL
        },
        {
            0xF0CFA8FBD8369E10ULL, 0xAB9AA55457536589ULL, 0xD524388C035F8493ULL, 0xD86D5600748C907FULL, 
            0x88F751E2D7222CB6ULL, 0x1FD8A80C2C3EBA28ULL, 0xC04B2B22862E1938ULL, 0x258060518B4BDA13ULL, 
            0x0D36EF8C99A737A0ULL, 0x80953745AEACA089ULL, 0xE8F3E663C2564BDDULL, 0xCC90F75181315837ULL, 
            0x7EA106FF5AD0AF50ULL, 0x76D04710DD742100ULL, 0x9B42A725A93734C7ULL, 0xD81ABF09B2543F0EULL, 
            0x9FF160FBCA5A9230ULL, 0xC400605A9ACF52D0ULL, 0xC006370E74603943ULL, 0xEF797EF7D5727CBDULL, 
            0xD108F1F914874BE9ULL, 0x4601AEC8533CE223ULL, 0xF08381F416A59785ULL, 0xF0FC290F81C896BCULL, 
            0x758F24EB3DE8231CULL, 0xA403B17F4A3BAFAFULL, 0x083E07F1A917F437ULL, 0x3ACE2153FDD15546ULL, 
            0x103E987AC3B6AE10ULL, 0xC0748D9A6E60CD74ULL, 0xBBFD6B9F65F867B5ULL, 0x55BCFE8BD31DD4F8ULL
        },
        {
            0x9C8CEC607A4B4EF5ULL, 0x02E80A72D3C16A73ULL, 0x6ABC5A4EE2E13FF1ULL, 0x1D66117A00C63DDDULL, 
            0xFC160B5A84D1C193ULL, 0xCA86CB1438DCCC77ULL, 0x81F232F48BB03A41ULL, 0x5F7DD0609F501A29ULL, 
            0xB9D6FA2F065DF596ULL, 0x08539AD2DFB03FBCULL, 0x1CD3463E2B3E112BULL, 0x4F46E4A0C0E2EFD2ULL, 
            0xB969480C071DA6B9ULL, 0xAF1D901B60B84FD9ULL, 0x76C150ADF20FFDA8ULL, 0xBB9E2371B575E1B4ULL, 
            0x55B61463702F67D5ULL, 0xBCEE82AD62260039ULL, 0x8CB7A18989C58B80ULL, 0x3279F3DECB11A06AULL, 
            0xA81DE0DA02841AA7ULL, 0xAABDF8232AD46321ULL, 0xD1E7A0C212A95905ULL, 0x5F0C1672CB3F1916ULL, 
            0x10AB8010C8C17EDBULL, 0x5971C3D178BC7A25ULL, 0x716ADA13EC9A696DULL, 0xD9F42ABA41E7C2DFULL, 
            0x13B685839092531CULL, 0x7FEF2D0C361898DDULL, 0xEAB20161E6FEA2F3ULL, 0x36C8CC58F77EBB2FULL
        },
        {
            0x137287B8CAF8FFB7ULL, 0xA22D8AE7CFF90883ULL, 0xD23B4202A88400E2ULL, 0xD0B88AE02D58C34FULL, 
            0x545D41316315F298ULL, 0xA12A34FBEAD353EAULL, 0xE320761FCCDE7B2FULL, 0x1E402A11465FB927ULL, 
            0xA71D8D2D327E0FADULL, 0x54CFC714B14F8527ULL, 0xCC64455FF153C81EULL, 0x9D808DB3C9E2D52DULL, 
            0xAA65CEF44D0D1FB0ULL, 0xA0A335ACEF6C27D7ULL, 0xCD6F0549B7557A05ULL, 0x0A26543B1508ADEBULL, 
            0xC6DB72E959CFF2A1ULL, 0x364712EBB3B6659EULL, 0x211DC62D320BA87AULL, 0x4FFF8F0524581575ULL, 
            0xFCE150924FAC50B8ULL, 0xD8AA3E397799E026ULL, 0x5B8A3CD3F3297CE2ULL, 0xCD36537965943D52ULL, 
            0xC347BBEAD5DC98C9ULL, 0x4F85DD7397BB80C5ULL, 0x078F9E79EEA8AFE1ULL, 0x5AD6B7BA12E10509ULL, 
            0x84E9D5BEDC4A6280ULL, 0x97C6543F3B796486ULL, 0x0B46699F8B9D5F87ULL, 0xD15CB1F06B13F6B8ULL
        }
    },
    {
        {
            0x237D6403BD562452ULL, 0xE8F973EF41E3A475ULL, 0x9D0199F2B8BA05ECULL, 0x67ACE3D84F46EE08ULL, 
            0x5584FD3D7ACD75A9ULL, 0x2ECC864E2F81358AULL, 0x2FDB002432F71862ULL, 0x6594597A8CD232E2ULL, 
            0xE8BFCF503A0F1848ULL, 0x9A5FA0722F437F95ULL, 0x1CC22D3E8AA5DC6EULL, 0x20DCA2EFE372CA3FULL, 
            0xC51C8E9392AB279FULL, 0x317D0241FBCAF5C5ULL, 0x6AEBC98C95C3470CULL, 0x53D29E34ACA78F06ULL, 
            0xFACE51D8849EF0DBULL, 0x40AD6B355B1862D5ULL, 0x60E45EBF7AB6BF30ULL, 0xA8F182734CF11BA9ULL, 
            0x050375FE9D1053CDULL, 0x4B566990D79C3560ULL, 0x0D88806897DA2782ULL, 0x91C4054FA73DCB28ULL, 
            0x6F62C80AC02DD608ULL, 0xB96EB53083960CC7ULL, 0x6500CBF56610D739ULL, 0xB4EBEF00C7E6A6F8ULL, 
            0x1B1E97C048A3E4A4ULL, 0x75942620E2DBF432ULL, 0x04DD655AB19E6195ULL, 0xA04D19AEFF5DFCD6ULL
        },
        {
            0x49269A96D5BC34F0ULL, 0xA4C0AD51C9D25678ULL, 0x644522B4BC912545ULL, 0xCD441D06DE06727FULL, 
            0x56D8CC2E65D69486ULL, 0x509FAC061B52837EULL, 0xAE91735FE1F23143ULL, 0x0A9DF15845C2EDA5ULL, 
            0x3B501D06BB5EFF81ULL, 0x5219EA4B31B6775CULL, 0x255779488A06D636ULL, 0x976678AA44F9CC24ULL, 
            0x81B8492ADBEA873BULL, 0xEE824BA5E6E3D430ULL, 0x69BD68F12B33651AULL, 0x2E59A535BF61372CULL, 
            0xF514A591B21D606AULL, 0x69A2F0E62F4D7B3EULL, 0x1266153B8CCEFB43ULL, 0x82E3EF90E65564A3ULL, 
            0x93FDADB0F6F141FFULL, 0xC47D63A22D0B1E28ULL, 0xAA1BEC78D95775F7ULL, 0xE5A64C6F1F770CF3ULL, 
            0xE13D19DB719E48D9ULL, 0x7015867068ECB909ULL, 0xEE70A697CC397680ULL, 0x28D95DEB2BD68E9FULL, 
            0x685281C729127F9CULL, 0x0445C9593251957EULL, 0xEB5BD6F3D35A11D8ULL, 0xF14B1B90D5054928ULL
        },
        {
            0xEA4B02D6EF975A5EULL, 0x526311B8555A3D25ULL, 0x6508E5C37CBFC039ULL, 0xF8F33EAAE0E8873CULL, 
            0x58D2BEB62586357EULL, 0x71E002A962595207ULL, 0xE971AF4502C4464BULL, 0x09B5E57027156750ULL, 
            0xA9B63B8A804C9915ULL, 0x31DD934425B9EDC8ULL, 0x3BE6B646CDFCFE7AULL, 0x394CA406F785C508ULL, 
            0xEBC6F6C6E7F21643ULL, 0xCB126329EBFBF393ULL, 0xBCAF6EF57F4C8202ULL, 0xA262C9DFD5BD4E4BULL, 
            0x2966649427DC901FULL, 0x42A59BA554215D6CULL, 0x18816531797AF1B5ULL, 0x3D1E4EA0F4733AEEULL, 
            0xE13F6423F490A0A9ULL, 0x808EBB76D79ECC6DULL, 0x2ED77D417D109586ULL, 0x9D68F5324E30D525ULL, 
            0x442C41787F43EAA8ULL, 0x06A6402E1BC054B4ULL, 0x71AF85E54BE8B71FULL, 0xE88D8A1C3E25C61CULL, 
            0xBE717FFA8A92688FULL, 0xAE5708ECD8D8BA5AULL, 0x17E2231434586AD5ULL, 0x18873F49A0371790ULL
        },
        {
            0x549E9316822C4C51ULL, 0x797E5DE3D739DA93ULL, 0x33616081F6417615ULL, 0x1137E7049CCD07E8ULL, 
            0xB418AF2E418DD943ULL, 0xC7D845F3D7CE94C6ULL, 0x655C7415CF4207CCULL, 0x57D0C8306D48D3B5ULL, 
            0x577CA053C9AF6C76ULL, 0xA106F814973D53B5ULL, 0xA9927E48E7349E79ULL, 0x98D39B8CA3E92E34ULL, 
            0x06321C9EFFACF2D3ULL, 0x5C9BD7310C7F3DB1ULL, 0x87985051CE0A1459ULL, 0x754E4FE3CF774650ULL, 
            0x0E235AA09178903DULL, 0x2D45C506E0654CD9ULL, 0xDF9A9559E10EE425ULL, 0x3821B366A29D689EULL, 
            0x5624F103367A1953ULL, 0xDE230A46760736A8ULL, 0x1376FF33CADE98D9ULL, 0x7D83B05B568791A9ULL, 
            0x9C04E309D1F9CFE7ULL, 0xA6600554A9C65EDAULL, 0x981E94E8D657C612ULL, 0x6F474CB32E090E93ULL, 
            0xFBC42F1F7801770AULL, 0x0910B6DB94F32B5AULL, 0x682BCEED39135016ULL, 0x4896083AF1476882ULL
        },
        {
            0xD8871B4F84979E7DULL, 0x525CC2345C6EF1C0ULL, 0x1A3BDD81D427CE5EULL, 0x10299EB9EB2AC035ULL, 
            0xA5AF14265290A424ULL, 0x24A2A03D5467D21EULL, 0xD4C83BE5DF1715A2ULL, 0xD18C5DE907DC8BDDULL, 
            0xF1A78A74D7C23C45ULL, 0x542E2F9F942C9F0AULL, 0x3FEFC5E8A8260098ULL, 0x5E9D08B378B0B625ULL, 
            0x43F1FA0AFCD2205DULL, 0x181E08206D7255BAULL, 0x92D47F2886C6D8AAULL, 0x54403B87F04E2454ULL, 
            0xF02CDB8933F39366ULL, 0x87404C238924E24DULL, 0xBD6CC1F967E5216BULL, 0xE50E39D1CCE2AA77ULL, 
            0x8D70CCFE398EA10EULL, 0x7F6BBD35928DAF62ULL, 0x9EFE1FDB75AB6D81ULL, 0x401D8799E7115023ULL, 
            0x87FD95E8527132E6ULL, 0x10E2A6074272B4EAULL, 0xAA4A9F509D19B887ULL, 0xF6F3DC1B47F43469ULL, 
            0xF67A0C159ED6414CULL, 0x9F60688462A2E93EULL, 0x228267669065A20FULL, 0xD9DD0331E9CAC5F7ULL
        },
        {
            0xDCD3154F6ACFF34DULL, 0xC11C38A799B1AFADULL, 0x0E8987E57607DF40ULL, 0x292204038059952AULL, 
            0x49065D16582109E9ULL, 0x0140AAC5638C27D6ULL, 0xF46B2FB2D4CE7304ULL, 0x45C2BC275C16A66BULL, 
            0x493EE4EF6966ACFEULL, 0x05A508624DBDFFB0ULL, 0x7D692614E8C0A51EULL, 0xC6DA660B28A4E663ULL, 
            0x628C59A9E0512E6FULL, 0xE0D3C0A5C1EBC0CCULL, 0xF910732985BA7A2AULL, 0x84EF637E68D9FDBEULL, 
            0x00D93F3885D3A3C2ULL, 0xD1CCDE8BDE5ADAB5ULL, 0x04F63E89D37F82C3ULL, 0x6510C9B55D706E60ULL, 
            0xF29BB897C9EED44FULL, 0x50F0E48E96C79003ULL, 0xD2E29D1B9B3F9C1DULL, 0x57B50BA827D02475ULL, 
            0xD19D5E5C0885830EULL, 0xD330BEDC6DDCC351ULL, 0xAF0FB577C29E5150ULL, 0x1DE878B6466AECF2ULL, 
            0xB397D0A40B5D2AC7ULL, 0x422CF564411937FCULL, 0x5962120266021A0AULL, 0x597EE48DEB0679F3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Polaris::kPhaseHConstants = {
    0x631C8EC305A90D6FULL,
    0xBAB977DB31F68B9DULL,
    0xBB6AA19D7C0A06BFULL,
    0x631C8EC305A90D6FULL,
    0xBAB977DB31F68B9DULL,
    0xBB6AA19D7C0A06BFULL,
    0x8A3A371452F64393ULL,
    0x612F9B1F74D360AEULL,
    0xB0,
    0x0E,
    0xDF,
    0x9E,
    0xAE,
    0x5A,
    0x2F,
    0x65
};

