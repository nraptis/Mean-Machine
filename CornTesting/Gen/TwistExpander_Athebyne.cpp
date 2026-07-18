#include "TwistExpander_Athebyne.hpp"
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

TwistExpander_Athebyne::TwistExpander_Athebyne()
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

void TwistExpander_Athebyne::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD324E77826632B85ULL; std::uint64_t aIngress = 0xB4275C589FB081C6ULL; std::uint64_t aCarry = 0xB6A1689544F6078AULL;

    std::uint64_t aWandererA = 0x9483680EFC610553ULL; std::uint64_t aWandererB = 0xB7880FC890535D99ULL; std::uint64_t aWandererC = 0xF49D0465EE5D14C0ULL; std::uint64_t aWandererD = 0xB819182D98D135FBULL;
    std::uint64_t aWandererE = 0x9ACC6A9A21491065ULL; std::uint64_t aWandererF = 0xE6116DEA35FEB0A2ULL; std::uint64_t aWandererG = 0xB49A748B9C6C51F5ULL; std::uint64_t aWandererH = 0xF27F44A570BC20A6ULL;
    std::uint64_t aWandererI = 0xA9CFC500DA1A894DULL; std::uint64_t aWandererJ = 0xB27D68EC070C6C5CULL; std::uint64_t aWandererK = 0xB5D452BFD31D77B5ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9800731500060351666U;
        aCarry = 14425808566136755808U;
        aWandererA = 12258947705769852700U;
        aWandererB = 10255837562858115711U;
        aWandererC = 10744150584182241665U;
        aWandererD = 17944328041987643509U;
        aWandererE = 11518990412947537385U;
        aWandererF = 16647607175012738722U;
        aWandererG = 13883137715110362423U;
        aWandererH = 17319058243020608268U;
        aWandererI = 12039942433020539526U;
        aWandererJ = 12533981763195664137U;
        aWandererK = 11639999359527283169U;
    TwistExpander_Athebyne_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Athebyne::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB6FACA89DC6E3B5EULL; std::uint64_t aIngress = 0xD634CCEEF9C65BDCULL; std::uint64_t aCarry = 0xFFA6D73D6B2B30DCULL;

    std::uint64_t aWandererA = 0x8F6ED2EDCF281C01ULL; std::uint64_t aWandererB = 0xB3D9DD7F53A548C1ULL; std::uint64_t aWandererC = 0xEC41EA6FB388524CULL; std::uint64_t aWandererD = 0x8B077C52EC940AF1ULL;
    std::uint64_t aWandererE = 0xD5DDF8A74A364C24ULL; std::uint64_t aWandererF = 0x8C9173207A25D216ULL; std::uint64_t aWandererG = 0xE0D1EDC7F969DD91ULL; std::uint64_t aWandererH = 0xC4B37E639DF91C85ULL;
    std::uint64_t aWandererI = 0xD2CF88A0A42FF6BEULL; std::uint64_t aWandererJ = 0xF446A931122CEB05ULL; std::uint64_t aWandererK = 0xD68134BEE8BC54A4ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10833586027553384708U;
        aCarry = 11783044626425024922U;
        aWandererA = 11627470029942403542U;
        aWandererB = 12399005173697567127U;
        aWandererC = 12372688287086534361U;
        aWandererD = 10357436093842826206U;
        aWandererE = 13539043652366528468U;
        aWandererF = 14748721176660015119U;
        aWandererG = 18314379064196305548U;
        aWandererH = 17002003904377885197U;
        aWandererI = 11232979470390594443U;
        aWandererJ = 15033520556604375268U;
        aWandererK = 16069671711780068117U;
    TwistExpander_Athebyne_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Athebyne::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD8D4E2D33C2883A2ULL;
    std::uint64_t aIngress = 0xD2FD16F15816FB65ULL;
    std::uint64_t aCarry = 0xC84DF9922E792641ULL;

    std::uint64_t aWandererA = 0x920CC39D0F17CD56ULL;
    std::uint64_t aWandererB = 0xB2ACF898B9D1C425ULL;
    std::uint64_t aWandererC = 0xEC2CEEEF2AE526F9ULL;
    std::uint64_t aWandererD = 0xE249345D1B8AB98AULL;
    std::uint64_t aWandererE = 0x94C3FE8585205B97ULL;
    std::uint64_t aWandererF = 0xF6F01800A5166702ULL;
    std::uint64_t aWandererG = 0xF660069043A3EFF9ULL;
    std::uint64_t aWandererH = 0x823895963E370092ULL;
    std::uint64_t aWandererI = 0xBAC1E6A324E2304EULL;
    std::uint64_t aWandererJ = 0xDB7AA9D6D11A5685ULL;
    std::uint64_t aWandererK = 0xBA740D0B579029FEULL;

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
    TwistExpander_Athebyne_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Athebyne_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 11 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1849 / 1984 (93.20%)
// Total distance from earlier candidates: 18633
void TwistExpander_Athebyne::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 76U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1015U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1773U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1972U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1178U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1273U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 180U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 416U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1826U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1060U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 104U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 958U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 94U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 805U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1997U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1665U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2025U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1482U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 871U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1049U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1024U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1429U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 189U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 566U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1080U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 662U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1841U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 403U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1122U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 595U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1941U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 99U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 0U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1738U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1258U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1922U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 28U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 119U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1155U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 95U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 18U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1202U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1012U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1631U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 232U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1880U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1048U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1655U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 990U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 970U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 162U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1210U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1034U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2013U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1356U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 526U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 160U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 230U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1968U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 515U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1742U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 988U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1127U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 381U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 229U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 492U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 868U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 791U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1324U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1174U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1460U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 842U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1110U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1221U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 914U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 100U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 201U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 720U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 794U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 717U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 918U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 935U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1422U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2021U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 387U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 505U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 428U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 171U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1932U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1791U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1082U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 696U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1136U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1411U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1650U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1578U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1114U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1087U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1815U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1391U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 751U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 457U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 223U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2023U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 880U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1002U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1564U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1211U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2032U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1446U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 314U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 745U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1857U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 985U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 521U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1906U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 572U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1162U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 412U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Athebyne::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCBB3FA516D7D33FAULL; std::uint64_t aIngress = 0xA2B1C2EAD61A0951ULL; std::uint64_t aCarry = 0x89539D7974C40697ULL;

    std::uint64_t aWandererA = 0x88ED0A8FB4B918F9ULL; std::uint64_t aWandererB = 0xDB034AAE4FEB338FULL; std::uint64_t aWandererC = 0xCEB7E963120AC917ULL; std::uint64_t aWandererD = 0xE57100CB8A8708E7ULL;
    std::uint64_t aWandererE = 0xD906A5276E5BE635ULL; std::uint64_t aWandererF = 0xA50A6F92FB889C17ULL; std::uint64_t aWandererG = 0xD9E24848CDEB802CULL; std::uint64_t aWandererH = 0xFF94F794E2397B44ULL;
    std::uint64_t aWandererI = 0xF021B2719C8D997BULL; std::uint64_t aWandererJ = 0xAD881AD4E2C978C3ULL; std::uint64_t aWandererK = 0xE8A95ECCAA2BBEBFULL;

    // [seed]
        aPrevious = 11623106567014779717U;
        aCarry = 14081605415456079865U;
        aWandererA = 11289255964373031260U;
        aWandererB = 12170976182474810141U;
        aWandererC = 9842762729055490286U;
        aWandererD = 14076705238404254479U;
        aWandererE = 12552488709162328841U;
        aWandererF = 12906107822380552337U;
        aWandererG = 11420218295850645767U;
        aWandererH = 12948980036914935152U;
        aWandererI = 13387147297604704487U;
        aWandererJ = 11271110415122475019U;
        aWandererK = 14164315990470015287U;
    TwistExpander_Athebyne_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Athebyne_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Athebyne_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 11 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5538; nearest pair: 510 / 674
void TwistExpander_Athebyne::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4469U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6347U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5350U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6183U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1104U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3375U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2140U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3901U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2392U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 978U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1097U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7115U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1003U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5637U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5032U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6448U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1109U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1692U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 502U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 222U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1274U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 869U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1249U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1464U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 49U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 822U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 347U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 735U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 61U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1244U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 728U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 942U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1270U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 191U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 723U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 677U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 11 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5535; nearest pair: 500 / 674
void TwistExpander_Athebyne::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7783U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4223U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3554U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4667U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 709U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2860U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3352U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2217U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 575U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2636U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7709U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5571U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6882U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3675U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5484U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 842U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1676U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1986U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1420U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1768U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 985U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 550U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1336U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1091U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1562U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1746U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 419U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1122U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 452U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1174U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1236U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 843U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1938U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1812U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 982U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseASalts = {
    {
        {
            0x9DBFF3D3CE8AC18DULL, 0x45FD208A8C7F11A1ULL, 0xE524CD07758A8802ULL, 0x6C7AAFE7F4CFA4A5ULL, 
            0x9B10FFA05405049CULL, 0x67ABAFF07F9A2046ULL, 0x67D3FA8D3DCD7B88ULL, 0xDEBF84DED0643DE6ULL, 
            0x976B0EED070234A9ULL, 0x6A483983AACA44CAULL, 0x52B458F153045565ULL, 0xAEE59A14C5317C1BULL, 
            0xABE5875C8BFD850EULL, 0x44FA325397D0FE33ULL, 0x1DDC74477D9948C6ULL, 0xE2E14A728E5B6AB9ULL, 
            0xE8BC365681F19161ULL, 0x4D6C53A7994D6846ULL, 0x5C1B7E36BFE51CFAULL, 0xD8E37F1325B511EDULL, 
            0x32A829F94212848AULL, 0x7EA46ED95AE9897CULL, 0x8B758AFDFCFE9079ULL, 0xBA47ED73CE1B6739ULL, 
            0x652220F9C86C260AULL, 0x899DC4FBF4069A66ULL, 0xD5C02A0BC759EB26ULL, 0xB1845FAF63C59EBBULL, 
            0xBC3A1570614DEDF3ULL, 0x8B8D847FDD5E4C41ULL, 0x93545709DF19DFF4ULL, 0x1C27C08E5F4FE6ECULL
        },
        {
            0x4AD2F52C7D85732AULL, 0x8EFB53919D5D6959ULL, 0xBB6A6D10E1414F38ULL, 0x2E79C475E8AC0184ULL, 
            0xABDEE6613B2BDCE8ULL, 0xC48BA6D8C0AD2386ULL, 0x6AAFCE1345643FA5ULL, 0x4589FDEBB3E7FA55ULL, 
            0x328FB9A3ED944F96ULL, 0x2953EC7A19C727E3ULL, 0xB2AC83D7FB09FDEEULL, 0x9BC1802FDC863EE3ULL, 
            0xAD0F3999D58AED62ULL, 0xA2C93ED8264020D9ULL, 0xBFF4CF0E070047DFULL, 0x0569F3941F700D96ULL, 
            0x271981F78DC97CBEULL, 0x0E21358E9C302B70ULL, 0xE7FBF8C67EB5B3D9ULL, 0xBEE351F60083D3B1ULL, 
            0x1AB6612FCF225A3CULL, 0x0DC5AA322EFD62E0ULL, 0xDA4B504372A9051BULL, 0x05C9072A57BD24F8ULL, 
            0x1004603908D826DBULL, 0xFB3B7E1BE6B5E074ULL, 0x35EAB9FB62E83B74ULL, 0x217755480E1FDED2ULL, 
            0xE931A0FA4C206826ULL, 0x3568BD48676B7403ULL, 0xA994F3C59B897F39ULL, 0x5D1F67C26D13292CULL
        },
        {
            0xA56A136B94E58093ULL, 0x05A713D3583F81C4ULL, 0x25E5187D865F3BC6ULL, 0x9D93B503D4907B02ULL, 
            0xE79CE88B89E5ED92ULL, 0x17685624F19A47ACULL, 0xD3827C83A1244D6AULL, 0x63E4AC51081F5776ULL, 
            0x83F4FC7D39434695ULL, 0x38EBE6F1C5DEAD19ULL, 0x053C9A8D62092AF0ULL, 0x8113F66B30E7542DULL, 
            0x0C536166CA57EF39ULL, 0xDFC355874544F861ULL, 0xA599346682C94CB7ULL, 0xEE0982B59DDE6396ULL, 
            0x8DE1C8B4D56C2522ULL, 0x10CB30DB61437F8FULL, 0xF606D9A1C78DCA00ULL, 0xF6A49BEF790C00B5ULL, 
            0xAFB3F76E7BCABE4CULL, 0x39DCE9CA03B82D08ULL, 0xC6318A5482443B6FULL, 0xE55FD2D87659D42EULL, 
            0xE0BDEBD9B6ECF41AULL, 0x21DEF1D281248FD8ULL, 0xF464A7BBDFA61955ULL, 0x8F1D751D8C35CF75ULL, 
            0x1F7EF52AA63E2A81ULL, 0x429FAAF894E359EEULL, 0x2E6EB977D87C8214ULL, 0x8CA4D56DF419F246ULL
        },
        {
            0x019F10680E3FAABBULL, 0x2CE0FA0A19F009C2ULL, 0x5EB8DB8EEF4F6F0BULL, 0xBCC8260645B90FE2ULL, 
            0x3F105B58E4189B21ULL, 0xCBCD7E42266F5CD9ULL, 0xEA4089DE24F1B8A9ULL, 0x151743521C037EE0ULL, 
            0x4CEF24F9128CBFF3ULL, 0x401072DEA040041CULL, 0x5DF5A2551DA744BFULL, 0xCE602A63A83E847BULL, 
            0x7F2CEC5EE1A25B24ULL, 0x6E7E4409AFB6B151ULL, 0xD91B7ABC7C11A95DULL, 0xA99617DDEED6DBDCULL, 
            0x1A7E8B506AFB786FULL, 0xF1F9752EDEB7475BULL, 0x014389D3E73473F6ULL, 0x6DA1B0BE7A2F6CEDULL, 
            0xD834EFEA5DEA13AEULL, 0x9D8463D8079A6211ULL, 0xF222E59B9D118566ULL, 0x9773A14A6943C54AULL, 
            0xF6EDAEC215FCD5A0ULL, 0x01BDAD3D560EAFD0ULL, 0x877063946F7E58A3ULL, 0x2E6F8728828F3CFFULL, 
            0xDA1CA3C4CB1AC674ULL, 0xE6E0A5693478755DULL, 0x63B32BBCAB3B760AULL, 0x28060C53E6C85B3DULL
        },
        {
            0xA241457E763CFF5FULL, 0x8695A38DE5AC60A8ULL, 0x14CCE6E049F63E4EULL, 0x748380F358F79FC6ULL, 
            0x2A8D2FE7E77D66F5ULL, 0xC976BC3719BF46AAULL, 0x28789132A6AA906CULL, 0x85CA4BA10E00AD87ULL, 
            0x38BF1ADD42405AC8ULL, 0x1DE55CC6F1244676ULL, 0xAFD5E44F7DEBE1FBULL, 0x66CEF50D2D221280ULL, 
            0x3BB1BD0E90C40425ULL, 0x3C716E6679CB0B3CULL, 0x4DDE124483126707ULL, 0xD44766411DD08CC2ULL, 
            0x4EC3D296E69C66EBULL, 0xB0EE34E2C4BF5C3DULL, 0x263FC1B61FE0DF6EULL, 0xE1BC0E898A7169FBULL, 
            0xC35E3C54E03DFCD2ULL, 0xD79A28E330C4C740ULL, 0x039C4CD9CE2FD400ULL, 0xE7280A44F1F2CC4FULL, 
            0x7FEC9B4B3D2F1F88ULL, 0x10915183786F2DD3ULL, 0x4910C7F692B8E597ULL, 0x12B1B42AC3F07AB3ULL, 
            0xBA6C4A8B4ABFD5AEULL, 0xBD28E930C819D1C9ULL, 0xDF635FCDD98CECCFULL, 0xAF54ABC3D14C9D86ULL
        },
        {
            0x8F05EA3B19E2C6C6ULL, 0x354AC4EE024A2458ULL, 0xF701AB576719941BULL, 0x7A1B97C7791990B7ULL, 
            0x31F49D27B1BCB5F1ULL, 0x34A19B1D6BF2F513ULL, 0x54345999D1DC9FC7ULL, 0x921CADA10EF6E452ULL, 
            0x5EF425F1A0E4DACDULL, 0x19ACCCE3BEDC05BEULL, 0xE5EA3472D01304F6ULL, 0xF7AF41E4F5E7AF2CULL, 
            0x8A9B1BAE69BBE831ULL, 0x61A0A52C6624F06AULL, 0x76254F1B7BF98562ULL, 0xF359234859B89669ULL, 
            0x988C8EB1F11731F7ULL, 0xA38A45A11352877EULL, 0x9840FF5CC4010408ULL, 0x905C9B37AC312519ULL, 
            0x32681F318B8A8DCCULL, 0x1DADD4E176E22E25ULL, 0x7CFDDC485087CDCAULL, 0xC1CE7FE388CCCC8CULL, 
            0xCD4C3CCA4A16EE53ULL, 0x6D4620844E111DD6ULL, 0x46D510B7EC4B6683ULL, 0x351D160D7185C3D5ULL, 
            0x901CCAD9EF94CDC5ULL, 0x19D45CB7FFAA1CD6ULL, 0x3FFFE034E5118066ULL, 0xAA6DBDD97D117B95ULL
        }
    },
    {
        {
            0x83A3315ADC86DFC8ULL, 0x93A7FA30DC1EAF82ULL, 0x2AF72467E98400C6ULL, 0x419472121F2D840FULL, 
            0xE493AAAE20A9516CULL, 0x3076AB3C2ABAFB32ULL, 0x5F0D1DE8C0142141ULL, 0xBB40F2013A256535ULL, 
            0x3FD6B5E50D239957ULL, 0x175D07735F6CCD27ULL, 0x9C96BC14C8BEE7D6ULL, 0xC6C02382C14A844EULL, 
            0xCE289D8BD9FEFCBFULL, 0xFB0EA4D27E131D50ULL, 0x81B7231A94C496BFULL, 0xEA9F12A998E39734ULL, 
            0xF72FAA425F296F62ULL, 0xEB7D0A8D5174D9B0ULL, 0x384465A289A887D8ULL, 0xE8AF6D98D958F7EBULL, 
            0xB5DCD4961417D294ULL, 0x806C69D198DEC9B4ULL, 0xC95D2F9E40AD521BULL, 0x22234570D09569C2ULL, 
            0xC8B8E8AFD2DACA7AULL, 0x314E1A03324B8CB5ULL, 0xF15B78090DF16D67ULL, 0x4C82D2EFEB69476FULL, 
            0xA9331333020EFB2AULL, 0x8D2EA4FF90C78FF4ULL, 0xC1FCC81EF59EB633ULL, 0x275563934B81C33CULL
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
            0xD510C74C61B20FE7ULL, 0x7A61B583C6AC4475ULL, 0xEED7DE53474FD34DULL, 0xDAD2BE7A2726A34FULL, 
            0xAB91D4A1E9A951FFULL, 0x51B418D207C66220ULL, 0xE3CDC8321E7D12BEULL, 0x9FE0C27564DD7EE6ULL, 
            0xCBA109F87F327669ULL, 0x42E5C882AF460E1EULL, 0x53DBBAAADFEB387FULL, 0x8DFDAD70334C0941ULL, 
            0x5A9AEB2F8BE3E88DULL, 0x6D115AFE49184667ULL, 0xBD372D8515B4AAFFULL, 0x9923BA9C028D9A87ULL, 
            0x82ECEE7BB85EC3F1ULL, 0xD5B8D9B01573DC67ULL, 0x590A8088BBF16D47ULL, 0x19B19ED8E287F09BULL, 
            0x5FC299953773AD34ULL, 0xC774CFA79860330CULL, 0x32A112A51C24E5ABULL, 0x475CFED779A85878ULL, 
            0x1525164A8AFCFB22ULL, 0x35664E22FDE9EBDBULL, 0x5DCD60908A102F8AULL, 0xB5D142A8166F2A6EULL, 
            0x14C3CB59647D1805ULL, 0xE8E724626AF8939CULL, 0xCA6F0F5A6D343C76ULL, 0xBFED0167367DB906ULL
        },
        {
            0xCE5AD798B954A277ULL, 0xEE8192EC94962007ULL, 0x755374DA70EE8D2AULL, 0x028C683AED714DCAULL, 
            0xDAE5A44BEEA35BB3ULL, 0x2A1461AF1F81AC4CULL, 0xB0402A14C8A376F6ULL, 0xFBFDEF2C0D2C6386ULL, 
            0x5DCE04648FA3D578ULL, 0x686099D03C958625ULL, 0x4529DD756EA22813ULL, 0x913EC04DC3E7F588ULL, 
            0x00A76BE45C5CFA4FULL, 0x813A78A987CD3032ULL, 0x1D181F264C8454FDULL, 0xF2F76BF66541A423ULL, 
            0x93C0F16349DB4C00ULL, 0xF974FB9D2F572085ULL, 0x038AB14CAE1A06D1ULL, 0x2988BC13F7AF1237ULL, 
            0x1FE9738336CB45CEULL, 0xD537ED68388130F7ULL, 0x59F0005683E8FF1BULL, 0x02109B4BB601A3FCULL, 
            0xC6EBDC6850D78625ULL, 0x8C4440180A6FE33CULL, 0x7B6E54AB6A93536CULL, 0xC8189D8664C43425ULL, 
            0xAF9EAA51323D7788ULL, 0x4418B4500C818EDBULL, 0xA5D98B0A19AB4447ULL, 0x3FA4563801B208DCULL
        },
        {
            0x1E41B1DA2BCA88A1ULL, 0x5BA3E8C5B303E793ULL, 0xA91F6B7270FBF663ULL, 0x4E8B7E1BACAE01B7ULL, 
            0xF02C289B06753A7AULL, 0x5D83FA78A77271BAULL, 0x2A2FCA981F588094ULL, 0x47E97A13BFC4C056ULL, 
            0x5C864605CAE4BF87ULL, 0x71B984057C719FDEULL, 0x7794ACD30EBD868BULL, 0x63D21D04B16B746FULL, 
            0xEB1EE8EEC64E9CEEULL, 0x2244A0FA296A65B9ULL, 0x6CDA84B192EF5DCDULL, 0x96FF4B3374DEADFAULL, 
            0x8AD4802412846D0CULL, 0x665D6C35261B7A4EULL, 0x8C027B6462A3166AULL, 0x35AFB6FA33F88B99ULL, 
            0xF7AEC1D68633999EULL, 0xDA7BACFAB98C0F24ULL, 0x29ED77E70BBA9F9BULL, 0x68DB2A254E8D01D6ULL, 
            0x242A4E53BD1FA035ULL, 0x9D2A121C28500F2AULL, 0xE25C34CEC3E2196BULL, 0x61AAC529818CD0BFULL, 
            0x8F03FC18827B4DFFULL, 0xCD8E46A4B7DAF927ULL, 0x9A6D51FE83AC0920ULL, 0x824B8B5D43CE1943ULL
        },
        {
            0x9FBB24D89487A634ULL, 0xFFA5D2323AEAC504ULL, 0x7380B32FE8681A2FULL, 0x471844BA7BDCBB25ULL, 
            0xA58CD95995C39BBEULL, 0x86D96487BBB17B7FULL, 0xCF30E4FC59504342ULL, 0xB08B93F35FD410A1ULL, 
            0x8E54939A16E27DF6ULL, 0x1A286F27BCE360F0ULL, 0x4A73DDA398D82136ULL, 0x814930D2B23878E7ULL, 
            0xC5E7B04F2EE4655EULL, 0xF0F7C048B2054BD4ULL, 0x8BF9668C4C2E1575ULL, 0x314D10E5C0356682ULL, 
            0x978105F64274EA3DULL, 0x38A30F78AA9BFED9ULL, 0x4BB4372306D4B7DCULL, 0x49D2971C91A8593EULL, 
            0x9F068B96F6D19D20ULL, 0xD1149B4C51006680ULL, 0x58EDE756CC5727FEULL, 0x25494248136BC9D1ULL, 
            0xF69C992F15E0C4F7ULL, 0x9B45F8BAED779273ULL, 0x057B659D9269677EULL, 0x9A0E3C348AED197EULL, 
            0x436BF94782989D8BULL, 0x065F019F096A1148ULL, 0x6B644E3770A68D11ULL, 0x744A73CB6B8C6483ULL
        }
    },
    {
        {
            0xBD7B1DB19BEF2ED7ULL, 0x68CA1D0CA75F3D46ULL, 0xB2BD4EFE76B5A6C4ULL, 0x7644F96B303F548DULL, 
            0x18EA12D904092ED3ULL, 0x25EE94C2CFABCFE6ULL, 0xC87FE209163FAA4DULL, 0x204D85F79785C8F1ULL, 
            0xAAE966720EF7B074ULL, 0xCEDFFBF8B91BBF8AULL, 0xAD02A995DE3913BCULL, 0xB524C3AC9422BF96ULL, 
            0x5646F7D5A7097CB8ULL, 0xA314E6102363FBD3ULL, 0x94E60B9E6195F48BULL, 0xEE655900A5245313ULL, 
            0x6FE59CD8008726DCULL, 0x32D7218C27AEBD89ULL, 0x5D7FC6DBC738E0AEULL, 0xB26D9C6C9780DCAEULL, 
            0xC5476021249A0218ULL, 0x7168ACDE43F39E1DULL, 0x473698CF018DF114ULL, 0x8B91DE6505D8116AULL, 
            0x38548BDFCC6DC70BULL, 0x509F86BD922FBFC2ULL, 0xC723F7FA50BAAFC4ULL, 0x1FF79EF44128FB44ULL, 
            0x117EA654C75C8AD9ULL, 0xFAD9F6C520437935ULL, 0xC0F733DDA638D093ULL, 0xFDB3FE9F99744737ULL
        },
        {
            0x19E4F0CBF339CCA2ULL, 0x728F1262F96ABA7AULL, 0x7037BF9CFDAE52BAULL, 0x37F03E992A9D464BULL, 
            0xDE4DA6CF3E037F34ULL, 0x89E679CC2401F0E0ULL, 0x6962C5724BB58BD2ULL, 0x694F953A9670FD78ULL, 
            0xE4A96CE0F4D0F7ABULL, 0x48AEC3CCF4758F57ULL, 0x32B7149F97144402ULL, 0x988CE9916826D8E2ULL, 
            0x81B9D57DB8953C9DULL, 0xFB1899BBC1D8C9A2ULL, 0x6EDD6F750DD591EEULL, 0x85016428DFE46DE2ULL, 
            0x6E4B141CC8352281ULL, 0x7B15F86ED990D3C9ULL, 0x208403D33B237952ULL, 0xCE49B1E36FC98499ULL, 
            0x8BCC6439169FFDB2ULL, 0xCAA78C8F4CACA8AAULL, 0x33C08855EC275E16ULL, 0xD9B30F259D4E2075ULL, 
            0x22FF3ACB6A0F8B44ULL, 0x35CBE787099EBC55ULL, 0xA7B865C6EAFD7A68ULL, 0xCCFBB76D874B1BF2ULL, 
            0x2C07BE9A0230DCD7ULL, 0x715295D007D51135ULL, 0x8E89E28D3DECE3B1ULL, 0xC5A92D30EBCB4E75ULL
        },
        {
            0x3DA14B15573CFF8EULL, 0x13202AFAC6F676F3ULL, 0x044E412A3C6CBD9CULL, 0x3F1DB3635AB76328ULL, 
            0xA14C8883A315C34EULL, 0xBC8A484E36064857ULL, 0x0F770EF0AE06223AULL, 0x0B95073E5AC3BB90ULL, 
            0xD28836F3D0F98ED2ULL, 0x6C930F42C92905AEULL, 0xB6736536D0D45826ULL, 0xB1D076CD56CEDE0AULL, 
            0x80F70B601D255598ULL, 0x50785B0A3FEC1BEDULL, 0xFB88B38E131F02B6ULL, 0xA8BA8ADFFE314F8BULL, 
            0xF5B6D947510E26C5ULL, 0x56AF518B0BA9C939ULL, 0x4305AC517AC1EA44ULL, 0x8BF5478B2BEED18EULL, 
            0x6DC3BDB43C476135ULL, 0x53FC5F816105456AULL, 0x79AEF4DEEAB42ABEULL, 0x600226A114E5C598ULL, 
            0x2A3EB46F3DD98385ULL, 0x78EE4F9E41203A10ULL, 0x2A6034F0896AA443ULL, 0x0DD00196461948CFULL, 
            0x002ABE68F1E51C50ULL, 0x16BA65DEC309CA97ULL, 0xDD20451049FD655AULL, 0x131B9A24024A3ABBULL
        },
        {
            0x27C50B65730E5715ULL, 0xF97F5839C48242F0ULL, 0x90C944119BBC8B3EULL, 0x245F848269853D1BULL, 
            0xC4CED6C3F032FE98ULL, 0x729BE7FDA59746D1ULL, 0xB2E614B749B1020CULL, 0xD46A067899AF250FULL, 
            0x02DCF511BB64F319ULL, 0x87C65C059930780EULL, 0xEBCE795E0B990E06ULL, 0x564F54A84F43B537ULL, 
            0x7D23147BA4CE94B8ULL, 0x0228E5AE49742F0AULL, 0x204B46473A2334DFULL, 0xE479AACC09330291ULL, 
            0x6ECE5C1B57674C43ULL, 0x3F8F4C4F77D7A579ULL, 0x8CDAAAE21CF8F263ULL, 0x499AFD40C0D5A9CCULL, 
            0x0ED8550AF307387CULL, 0xEC8092EAE7837D7FULL, 0x09CE9048066C9544ULL, 0xA508AD73CC41BBEDULL, 
            0x8A9D4E851446767DULL, 0xE5CE6D4966DD0E07ULL, 0x92C822086C6DAF5EULL, 0xF5B017DAD1E13ECDULL, 
            0xDCBB6C7D0A454B0EULL, 0x41342A05BB3C841BULL, 0x1C49EA357E9C6FEDULL, 0xF66CB2DCFEF1BC26ULL
        },
        {
            0x8C53E3424C09441AULL, 0x04EC71106A4D906FULL, 0x1BA23E62A2B8E5C2ULL, 0xB234EE0CAD033B6DULL, 
            0x3F2F17D1F71EF29BULL, 0xA73A3D60217C24FDULL, 0x3E7E51227DD3329EULL, 0xB7E0295042D56428ULL, 
            0xF90C0EAA3CFF78FDULL, 0x5ED34411A2485123ULL, 0x5127A47785DAAF32ULL, 0x929AD88D6F2CD591ULL, 
            0x0B2D5F25ED403810ULL, 0xDB20A0C11A9178C8ULL, 0x8E50241B552BC422ULL, 0x34B17FCA4B0EA629ULL, 
            0x2AA10E86163EE152ULL, 0x295AB19896FAFA6AULL, 0x58F59081F490C6ABULL, 0xC96856E4C03DD168ULL, 
            0x20AF46116BA45C2AULL, 0x9A988D94B674EE36ULL, 0xB2BE7836E92F0174ULL, 0xA111417B664460A6ULL, 
            0x381F168437402D93ULL, 0x4F2DE02D3B2A037FULL, 0x5594F8214D8C2EC2ULL, 0x5310D6BD95B14773ULL, 
            0x745FF064C44DF022ULL, 0x0E6F88134A1C1883ULL, 0xC569C398A108E539ULL, 0x9D30986C08EB07FAULL
        },
        {
            0x1906FB89567CEB42ULL, 0x2BE1C8C9FD18710AULL, 0x1285DE94DFDFA75DULL, 0x0A0B86E91CD4B8DEULL, 
            0xDBB8C131763624BCULL, 0x4DFC9CF74F085187ULL, 0x5790B3B584E9D011ULL, 0x3DE5696A2201237AULL, 
            0x2BFBF85D089F82BBULL, 0x0C58BAB90C5E84E1ULL, 0xB61672330C9ECB62ULL, 0x1F9CDBD503B1EBDAULL, 
            0x5966B3F3CD7E28ADULL, 0x49957C06B9E34F51ULL, 0xAAE75E553CE722BDULL, 0x432921424CEF7C2FULL, 
            0xECC4067FEDAA04EDULL, 0x9157DBC97429AA2FULL, 0xB4741AF3F117BAADULL, 0xBE6CF798CBB3CFBAULL, 
            0x080053F2E5F7C2C2ULL, 0xF03FFCCC29E6D036ULL, 0x2A128E6C68729BA7ULL, 0x8DE5B341CA8B7229ULL, 
            0x2E77DB38FFD0C9B2ULL, 0xB89B26208A065A89ULL, 0x9CBEDA0DAC1428C1ULL, 0x6BD97C0C797B259EULL, 
            0x24DBEA5220E5882AULL, 0x46B2BCC2C2007CDDULL, 0x50F057882930DF46ULL, 0x05AF256C996A0199ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseAConstants = {
    0xAB52DFEF312B9C3CULL,
    0x656908D7A6FA06CEULL,
    0xC04AB2A173052521ULL,
    0xAB52DFEF312B9C3CULL,
    0x656908D7A6FA06CEULL,
    0xC04AB2A173052521ULL,
    0x698FAE364850B092ULL,
    0x0934F76E742B4C8EULL,
    0xE8,
    0x5A,
    0xA8,
    0xE1,
    0x18,
    0x6B,
    0x43,
    0x84
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseBSalts = {
    {
        {
            0x4245653B01F0D39EULL, 0x23BDB323C1BDB17DULL, 0xD0D591C7CA11BADBULL, 0x7F6FBA4B9889C37CULL, 
            0x9AE8B582DBEEC184ULL, 0x0EA5E8C08F03B0E3ULL, 0xABEF59485FA6509DULL, 0xB23A30206000200EULL, 
            0xFC9AE67339AF207EULL, 0xAEAC5AA6418B00A8ULL, 0x5AAF8095D25A09FEULL, 0x8E0E89AB3BBBFADFULL, 
            0x075AC5A60796FB71ULL, 0x445515699B7279F6ULL, 0x5EB12D340E34C1FFULL, 0x9E2A6D0113D07099ULL, 
            0xEE42A7395DE04BC9ULL, 0xB060251C18F7F0CEULL, 0xECB5E3B08D314A19ULL, 0x493BB2D8789F6C1FULL, 
            0xCEE6F642464C997CULL, 0x83723C8CBE73EB84ULL, 0xE3198747E2EC104BULL, 0x83B7C8F1770C2ABEULL, 
            0x69E4E01C4EC4B52FULL, 0x9E0ACE0458F0CC33ULL, 0xDC9933E62949641DULL, 0xE2DDD7C37F2F7F8BULL, 
            0x01577CF65BAE5374ULL, 0xC155AF71267B1D55ULL, 0x8EBEDB8B93644678ULL, 0xD3D15E0A7927864FULL
        },
        {
            0xE9025F3F3A4DEFECULL, 0xE4C993DBB538F930ULL, 0x1347E4C5D49D5FC3ULL, 0x2CA23E61D16F45EAULL, 
            0x795A2B2426589BF2ULL, 0x022EA09D9E72894AULL, 0xB851D562CB73FF5DULL, 0x49D0E7E351884032ULL, 
            0xD843F940CC3F13E7ULL, 0x482CAE7B6C6C7911ULL, 0xE09F511D219694E2ULL, 0xBE77E73993D98BEBULL, 
            0x5FAF67CF8DD28CF7ULL, 0x257107D27712996EULL, 0xD80DC5A8E2E8BA91ULL, 0xE79E8B22C57B975BULL, 
            0xDE7C65F9052C760AULL, 0xFFC009F4D6D43CFBULL, 0x8D37CF37800D6D54ULL, 0x786E2DB07B9B55F8ULL, 
            0xAEE23A9C877D7765ULL, 0x5F9E069478E9165EULL, 0x20831E265070EF05ULL, 0x84A87E5FA8F3CC95ULL, 
            0xEAFCDED9FD45A989ULL, 0x149B971C15976882ULL, 0xAC2ED8C5B5FA3E64ULL, 0x74453388E39409BDULL, 
            0xD714BA10D9388FC0ULL, 0x2F49397607DF731FULL, 0xD8836C6505817EEFULL, 0x430E5445FA817190ULL
        },
        {
            0xA522B6344EF199B0ULL, 0x26CA423A41851992ULL, 0x000CD32538EEE7EAULL, 0x45FB8EED03215C0AULL, 
            0x61F3C4E9CB19A654ULL, 0xE00D7FC76B489364ULL, 0x396D06F03B9637C5ULL, 0x31430093E1A1DD14ULL, 
            0x35CC39E4B03AB586ULL, 0xF7BFC34D1FA7C793ULL, 0xA6FD480B6B0983ABULL, 0x570B7163A8C840C6ULL, 
            0xB87200D6664B56ABULL, 0xBE983A0C46A6AFDCULL, 0x39AEC7F6960FA15BULL, 0x307D6A1601864994ULL, 
            0xA03D70DE8D4BF8CDULL, 0x982BBD4D18C2408DULL, 0x4CFC54FFFE6E725BULL, 0x40C902D4EDA55F01ULL, 
            0x6F67FA8E2546099BULL, 0x5EEC8F096801B597ULL, 0xBBFB449ED48B1961ULL, 0x057C03BBD3ED6935ULL, 
            0xF39DA0A487A6A0AEULL, 0x6FFDE2C3A017BB6AULL, 0x9DC04CBD02415860ULL, 0xF31AE8663330AE03ULL, 
            0xFEDAD03A5066AB7CULL, 0x46C46F46EC1AEFFBULL, 0xB114078AA8329C82ULL, 0x31F95A0839C560F4ULL
        },
        {
            0x91F0EA573061315EULL, 0x2EDDD4F7D42B8386ULL, 0xD7AEFF7E4A1F8742ULL, 0x1C414E141A54E1BAULL, 
            0x28577A5A84644C27ULL, 0xC728161B24466847ULL, 0xD33FF4188AC58A27ULL, 0x15C56BBD8558F712ULL, 
            0x0D9A93F6F6BA4201ULL, 0x0AC75127B10173EDULL, 0xBBB3656442BC404FULL, 0x00E24956FCF56EDAULL, 
            0xDD4CC37069FE2B3FULL, 0x81E06FEA7CAA8C3FULL, 0x0D14928A7D1C412CULL, 0x2C76214330E389F9ULL, 
            0xE5ED898732739FEAULL, 0x8C9B9EF1EB34C9BFULL, 0x7A05BD0152124AE6ULL, 0x3B55AD10883354CEULL, 
            0x11D07715981308F2ULL, 0xA384E4B2C838607CULL, 0xC6367159CA87680CULL, 0xABB7D7E7BA95544CULL, 
            0xA003C387F325E1BDULL, 0x7AFC86A333D9BEB0ULL, 0x1E83E30D4A8F93C1ULL, 0x3584BF45695126FFULL, 
            0x830D21E0A1DD6BF6ULL, 0xF937D8EDF116F6DDULL, 0x58CE2CB6298DCC4EULL, 0x7258169E50181627ULL
        },
        {
            0xF20FD8DCB44A33D3ULL, 0xAECC4AB4D6B270F5ULL, 0xB1DD7F6B917BF287ULL, 0x63506E0D348F3217ULL, 
            0x42C7573A48C79355ULL, 0xAA7FC7091352EAC1ULL, 0x4F7515D41B35396BULL, 0x9EAE8209E390CFD0ULL, 
            0x2150DD3CFDB36192ULL, 0x703C548E33902082ULL, 0x57EAE6556F1110D8ULL, 0x627F36A8842885DFULL, 
            0x9EBE9761033650D7ULL, 0x1CD579A3507F19B6ULL, 0x1DCEE5842A28F089ULL, 0xF2F8392237DE2A9CULL, 
            0x7F213DB8FE9E4BDFULL, 0xAEC2C4B7DBC01FD9ULL, 0x3C308AE8E9177D6AULL, 0xCD38C80F13ED6E8EULL, 
            0x3716F9EC69CEA1E4ULL, 0x9A6666DA13B8013DULL, 0x60145271544A66F4ULL, 0x0CCCB8C8D42DE45BULL, 
            0xC11166618D45C175ULL, 0x50DED795E62B1E79ULL, 0x1E80D07A82C81538ULL, 0xC22AAF450E9A4AEFULL, 
            0xB8E62324049B7E10ULL, 0xCB1D7D21C57B9D12ULL, 0x0DCA69ECE8F94F68ULL, 0x0D188ED58757ADC7ULL
        },
        {
            0x4AC265C77E07A2F1ULL, 0x55C0CF2552BF0F37ULL, 0xA085F22B92A201C9ULL, 0x7936AF5AE4190FD7ULL, 
            0xC9AB2042DE337EDFULL, 0x83967958CBDCA7B2ULL, 0xA1A9B0FC0C587AAAULL, 0x2D31EB652C5C7FB5ULL, 
            0xF7838782BE628AFEULL, 0xA1E2AFFB963BE3B6ULL, 0x2A853865C1874DC4ULL, 0xCD25F7463036B5FEULL, 
            0xEE933BED28E808DFULL, 0x49AE55D2FEDB165EULL, 0x1398972AA0C4006DULL, 0x0F5B72156BD15E23ULL, 
            0x794B5EECCAEEDD32ULL, 0xB28AD587B17A54DEULL, 0xAD2935D4C14C1249ULL, 0xDF6C2D99763B97CFULL, 
            0xB245030B6D25282AULL, 0x4486DF2908E5DCBDULL, 0x1203D3F0ADE5E5CAULL, 0x1915B4FB03694568ULL, 
            0x5E1388E7BD10D7A0ULL, 0xD9B32959285FDBD7ULL, 0xA2B99EBCA181B423ULL, 0x75D82D07C1FC37B7ULL, 
            0xE48D91385D887B00ULL, 0x713EC28B421FDE5BULL, 0xE81CB063A0B10306ULL, 0x106C6B2E35724A4FULL
        }
    },
    {
        {
            0x4F053EC8EE5100FAULL, 0x84D0FE8D1DDECA51ULL, 0xE8AAE67AD313A6F6ULL, 0x824561B7C0927153ULL, 
            0xBE328228FE3A6131ULL, 0x240A8B60870A6312ULL, 0x3FA4B5F292377DB8ULL, 0xDBCF2A718959D5D1ULL, 
            0xCFE0D0652A9EB956ULL, 0x0B370620923D1EBAULL, 0x2261A0553F7757B5ULL, 0xABA3F08C5D1A6589ULL, 
            0xC9F235D4B3A95334ULL, 0x079D5C5090BFC702ULL, 0x340ADD8CF18993FEULL, 0x5BC56D6C08BDE96AULL, 
            0xF44CD8E111496B08ULL, 0xA0E1768E632F490BULL, 0xF7CEDFCA1A08439BULL, 0xACEC34E5972FC943ULL, 
            0x58D4B8F598DEC324ULL, 0x4D7312C262B6F67AULL, 0x87E54AD39AB5C6A0ULL, 0x26FA23B7A72E96ACULL, 
            0x90D06B9943EBA1C5ULL, 0x0B664DFC8F78E782ULL, 0x256E7B385B737193ULL, 0x0EB901874875F80AULL, 
            0x09C0DFDCFE380ABFULL, 0x619A61584E259C1CULL, 0xFFF91CD376069B99ULL, 0xBD79BF51F2CC1F88ULL
        },
        {
            0x236043F8E98FEBDCULL, 0x17ECFD9604E3D1D7ULL, 0x140DC2EAC036AB19ULL, 0xF7E57C65749AFA1CULL, 
            0x75BF4C57F9C0B7E2ULL, 0x93BB26DB99A25F95ULL, 0xEF0FB10290104C5AULL, 0x5D25DF5E8D4CCB9AULL, 
            0x19F7B6830AA0D7BDULL, 0xB4E24DB50DD0D58AULL, 0x21CABD1524FBDB02ULL, 0xE863548B3CC1664BULL, 
            0xDC548F9A7FF691FCULL, 0x6D4A2AEA160AB1AFULL, 0x0DFBC306C42336C1ULL, 0x5D983B28D8039E69ULL, 
            0x0CCE10EEA8881C8FULL, 0x9D031A7A8D8C2146ULL, 0xE64D7F63680E0BC9ULL, 0x04D92103CCAD4F7AULL, 
            0xCA68361BAB50A0B7ULL, 0xF23A8A6800F292CCULL, 0xB5ADDCDE1412AF18ULL, 0x0CB545B366E78F1DULL, 
            0x1EC7876C9C706F98ULL, 0x494B99103EDEBAA3ULL, 0x771B45EC5C68B25EULL, 0xC087C2777540D30BULL, 
            0x09BF60996C391662ULL, 0x69376683730BB810ULL, 0x72C0D144D44AA2C8ULL, 0x0B4FA7451C875679ULL
        },
        {
            0x37CFF1FC4BCC8C99ULL, 0x5CAF96FCCEC28D08ULL, 0x59777D642A4AF06FULL, 0x34AAA7046B271EECULL, 
            0x80C9EF043567FC87ULL, 0xB072061059C7BE39ULL, 0xF9DB14E06B0F955DULL, 0xECB727E3E62994CCULL, 
            0x7C3593380C90CFAAULL, 0xF1FDD824C1AD327DULL, 0xEEBC5913722C2569ULL, 0x98C55DCE7879487BULL, 
            0x013C942791FBC6AAULL, 0x1C5462C2AD734E00ULL, 0x76358DD0546A02C9ULL, 0x48008033EEA8B092ULL, 
            0xBBBC7C3B239221B8ULL, 0x1A18DDF98C8D5D68ULL, 0x6896E1B719351862ULL, 0xE67F5F51C5D04AD4ULL, 
            0x5795050333D13BFEULL, 0x68F0F2796626AC90ULL, 0x84E4553E6F77D019ULL, 0x4D04CE590F836987ULL, 
            0xA4B6433E80809E1DULL, 0xECA2F16878EA2A46ULL, 0xCBE0E032FAE090AAULL, 0xABE2803D0BC900AEULL, 
            0x175C17904415E0A7ULL, 0xE6030B622EEF9ACAULL, 0x4A828A2EC7D6497EULL, 0xA618E2F3EB7AE47CULL
        },
        {
            0xCBFCD73401029967ULL, 0xAC46959F94ED15A2ULL, 0xB82B8695005CB459ULL, 0xB969843CF0381CD6ULL, 
            0x9EDC3848E38D2C2DULL, 0xF7EB34D4C12E9235ULL, 0x974A9CB2D23D24D7ULL, 0xB6E53BE687F44170ULL, 
            0x5A6B82E4874DD372ULL, 0xC52AD037D804E510ULL, 0x8227575A82AF6016ULL, 0x79A548F89E1EB47BULL, 
            0xDBF62A04D0E33831ULL, 0x2B82F6B8CFB9C50DULL, 0xF8E6F4DD89F07D89ULL, 0x8F9CC9F31EC63825ULL, 
            0x3A61EE0D213B12D9ULL, 0x3A68D716E9534C2CULL, 0x71D032EFB5175392ULL, 0x380BD67DF762EF80ULL, 
            0xB44F924BDE7B708FULL, 0xBAC479CB2FFEDB96ULL, 0x93731E795047A472ULL, 0xC110EBEE63235BD6ULL, 
            0xB33240DEE90E199DULL, 0x5DB42A7A15309772ULL, 0x10CC63585B81578CULL, 0x36293C7C339540C3ULL, 
            0xA223E6C5911A1594ULL, 0xF8A53A4EDCEAE42FULL, 0xA7F45820DD233753ULL, 0x2DCF0DB310A23D4DULL
        },
        {
            0xCAC0A0D02E113CF8ULL, 0xA276346B73885FF8ULL, 0xF7E8EB63FC9A718EULL, 0x08CE91219CDEC633ULL, 
            0x1DA1DDDB4E63FBF1ULL, 0xD203AB360E5CFA65ULL, 0x1DF4373FBE85FCEFULL, 0x9FB0B4CB0569BA68ULL, 
            0x138852220B190413ULL, 0x4CD1C7F33BEB2203ULL, 0xCAD0D813984599B3ULL, 0x7EAA26BAE5ABE0A6ULL, 
            0xF09251166D3E82C1ULL, 0x32F47C812D985CD0ULL, 0xA8EC62477E170695ULL, 0x0AEFA3BA661644DDULL, 
            0x898D2A5C7DE3D82FULL, 0xC4E73EE286D55481ULL, 0xBDA0F25C7FB52BB6ULL, 0x2FD6E9828904A991ULL, 
            0xF1E192EE114FC708ULL, 0xB6C559599321E706ULL, 0x3B3E412F0B347925ULL, 0xE3081F2F9839FBDFULL, 
            0xD66217C78D9073A7ULL, 0xD2BA26913C69B749ULL, 0xB4DF9C0D91B20A85ULL, 0x1AD1A1653D817384ULL, 
            0xD10C2CB5A553E2CFULL, 0x057DEB06C08A0AF8ULL, 0x33DD48AE4EC091DFULL, 0xA144E062691468C6ULL
        },
        {
            0xE6C369FC7BFB220AULL, 0x27CB65914646AABAULL, 0xC81488E959F73982ULL, 0xE7A034FCC58A92F9ULL, 
            0xF480C57D39457DAEULL, 0x90150BE7021AF90CULL, 0x654FC3DA30E0DD00ULL, 0x16965D103E79E257ULL, 
            0xEC892DBF4C0B13A9ULL, 0x278918A70CBA81ACULL, 0x04C410E7B74619EDULL, 0x8D3DB46AAF6932F1ULL, 
            0xE738D41216BA0C5CULL, 0x3D0CA0D45F4F2C86ULL, 0xD91906FBB23A5629ULL, 0x255ED3A8BB31B8F6ULL, 
            0x522EE4D1AC9D262FULL, 0x33D916C9F7E1D99DULL, 0xB6052DD89FFDC0E9ULL, 0xC63B9D74B720FD68ULL, 
            0xC029B42BBAE55C51ULL, 0x9BE3807CF1C71E63ULL, 0x2401222EAE0FB6A7ULL, 0x99C9D55F2B24F3B9ULL, 
            0xB73127F8E6C87700ULL, 0xF2FF70860B2D647DULL, 0xF68193E5E734A0D8ULL, 0xF1A8553AA4A7D8DEULL, 
            0xEC1A45361E62B979ULL, 0xA46C8C1E5FFA7136ULL, 0x04E2A6779F537A8CULL, 0x8F179B2C23170974ULL
        }
    },
    {
        {
            0x8A678EA0510F1941ULL, 0x3E77B159B1EC61C8ULL, 0x6E2E22D6ACCE2522ULL, 0x39B6E45D48A890D4ULL, 
            0xA4D9BCC6E1C88BB5ULL, 0x183EF1DE125748B5ULL, 0x86EA651EFAB7E4EBULL, 0x6C1FFBFB4CDAD9B3ULL, 
            0xE58888893BDC3F06ULL, 0xF04B1655CD4E8D97ULL, 0xFD5F27A3AB7CB7E4ULL, 0x6BB2B77D1955A74BULL, 
            0x6456C8E24CA8BF58ULL, 0x0F8B9BA2C462D1F1ULL, 0x45DD9C0C4B0C4264ULL, 0xFA1C3180B21A67A3ULL, 
            0xED09FB95E60FB383ULL, 0x4FF057D0E7F1F8C1ULL, 0x3D5D8C4BE16D3D5CULL, 0xABBB25A2E4B7A3C7ULL, 
            0x927526775BAB2B6EULL, 0x309C279BF61A6EB5ULL, 0x0B628BEB02CFF0EAULL, 0x97AE21F4050505C3ULL, 
            0x7FFB7569A7DD8EB2ULL, 0x733D3D04C02A39CFULL, 0x55ABAB4186351DD3ULL, 0xAD62F9F7FF4DF597ULL, 
            0xCD16A8B8469E4919ULL, 0xFEBFB1E5CF6001CBULL, 0x0657DBEE2BB6B8A4ULL, 0xF0C60228FF033446ULL
        },
        {
            0x6B733ECBFFFBA5D4ULL, 0xB84214587F60230CULL, 0xD84FB808C68A87AAULL, 0xE6C601AA4DA9C410ULL, 
            0x2AF6A1BD684D7E4AULL, 0xEC11797674F6FEF6ULL, 0xBB76C821368DBF87ULL, 0xF429628618EDEF88ULL, 
            0x725F6999454A323CULL, 0x5276FAFF3F491484ULL, 0x8C9ED5F78A518163ULL, 0xB537302F24E58229ULL, 
            0x75D8C37DBCF6BB1BULL, 0x15E71537C3377629ULL, 0xC7C1F14CA4EA85DBULL, 0xADBA6AD6B26188C5ULL, 
            0x5BA9C4892BF9E81CULL, 0x8D526364DE9D68A1ULL, 0xC318146805867F20ULL, 0xD3F8123582FCCDA5ULL, 
            0x21C06C816E7E7AEBULL, 0x1D8BCEFDA1990EF7ULL, 0x828F355915A2584EULL, 0x9BFD15C79E2313CFULL, 
            0x7B73618545C1230FULL, 0x1784307F477A05E5ULL, 0xA8910511DCAD54DBULL, 0x6A22587B0ADEF6E0ULL, 
            0xCE98FFF47D360914ULL, 0xDE126D1E2D0B9DFCULL, 0x5B249D049253DB31ULL, 0xCDD7C9D75BB4D4C2ULL
        },
        {
            0xBB2696DCB8267508ULL, 0x5EA4363DA2B3FB34ULL, 0x60AD8EE71E53516CULL, 0xCAB151DF32D6426BULL, 
            0x4F7AF20A36DF3225ULL, 0x4A2C23797BAC1CB6ULL, 0xD429D1F8A6A4435DULL, 0x789A1E7847053D8EULL, 
            0xEA58C078EA31297FULL, 0x5DC36CD71EBF48D4ULL, 0x6B4CCC6BB20ED7BBULL, 0xC2A98AB173C930D4ULL, 
            0x27C83FD66586B611ULL, 0xE3B1F51B2636D291ULL, 0xFFC5E17BBDA8F311ULL, 0xA653E5F539136EB1ULL, 
            0xF0C31B08D9442287ULL, 0x82693C43A6AC01F1ULL, 0x15D0C8747B25F232ULL, 0xA82B570C1B96CD88ULL, 
            0x47906F679E65253AULL, 0x926E4564BE5CA705ULL, 0x9CBDA74EF1A92CC4ULL, 0x9D203D8D00CF2D71ULL, 
            0x563AB6E48E614FB9ULL, 0xB408FC6CBAA394B3ULL, 0xD98A32D1E7C6D8DDULL, 0x851A3E59AEA9E852ULL, 
            0x3802396110836C3EULL, 0x63F97BE0B1ABF4D0ULL, 0x31CE9D3A71914F3FULL, 0xA55FB12F0D6F2261ULL
        },
        {
            0x8E32993E894023CDULL, 0x8DB6C7814430BE85ULL, 0xFA221317348C583FULL, 0x9AB1B40AA5E7FCE4ULL, 
            0x2941062AE739CA1AULL, 0xF25795A9FC580F56ULL, 0x14772EB0BD506D7CULL, 0x91640123EAA860ECULL, 
            0x962A0790D68856FDULL, 0xCB26944F0E83BE4AULL, 0xA88369819FA3B8CAULL, 0x23F2CA1D6991CFD1ULL, 
            0xEF91C4480B3C901BULL, 0xF4D63A404914BB71ULL, 0x4C83D6EBCBD375ECULL, 0x771C9C0A7BD445B9ULL, 
            0xDC392406E38E4B16ULL, 0xDA91667DADA7A2F0ULL, 0xD9FE49AF7ABA929CULL, 0x15CC1E67B6DF91EAULL, 
            0xC0FCFCE8D9E72D73ULL, 0x32530213FCA04B60ULL, 0x6008DD99DFFF0DC6ULL, 0x9F913CE07492B251ULL, 
            0x3E3FD9EF83249519ULL, 0x17993A271D1A0961ULL, 0xCF1379E1971D439AULL, 0x552BD729A871E641ULL, 
            0xB9178F1E52DD4BDAULL, 0x76306040535E3BC8ULL, 0xF014CCD2E30692B3ULL, 0xB6FD7F3BF1604743ULL
        },
        {
            0xD5CD12504F5AFC4AULL, 0xA4E74B16A6DCF8BDULL, 0x5ED55C5FDCA81CE4ULL, 0xFBF1A4B36FE25926ULL, 
            0xD9841CEC7DA3EF3DULL, 0xE2E94C30B3F74E95ULL, 0x668D5929BF122867ULL, 0x68537DB06F58B11BULL, 
            0x22E6997618EACDB3ULL, 0x674E8468DCDF3A17ULL, 0x4D1E1305C34C60BAULL, 0xBAA118D03B94F4B8ULL, 
            0x1C63E69CF74E9E8AULL, 0xD4BD947BAF34CAA3ULL, 0xE8C4F896F55972FAULL, 0xF314874377CD55DEULL, 
            0x112C80C63624A48AULL, 0xC88ECFA6ACDBEF15ULL, 0x38904372D14C697DULL, 0x45500A184872338EULL, 
            0x6FB04669E929D715ULL, 0x42FC6A37717BE0BAULL, 0xF4BB9B31E7825CFBULL, 0xC33340B908524827ULL, 
            0x32533A7A79F70535ULL, 0x8C0CE6C0ECA8AE80ULL, 0xF8F16FB76D8D2809ULL, 0x22494666281793B4ULL, 
            0xAB4A7B69D18A81AEULL, 0x0977694C63AD4AE5ULL, 0x4C84900247CC9464ULL, 0xBA27277EC6D211F4ULL
        },
        {
            0xA59563E153D9F52BULL, 0xB2C4C6719CF9810DULL, 0x187194752860B9B7ULL, 0xF07E3551A2056A54ULL, 
            0xA4D714574D0D7433ULL, 0x503312A4816A253AULL, 0x8BA0D887BF142488ULL, 0xC7AF08E7EBCECB2AULL, 
            0x894DF7D81E70A135ULL, 0x3921F3D0AEC3C9C6ULL, 0xAC26D418A00602D1ULL, 0x94A47316BD42ECD4ULL, 
            0x1A5F85294B3224A2ULL, 0xA3A15E0802D2C7B4ULL, 0x8C14B6CC40EA2B2DULL, 0xF9B715A2EAD7BD4DULL, 
            0xC8B5BB9B0417A2DCULL, 0xD06AC1331C94A77DULL, 0x9D3F27D55AA77450ULL, 0xC882B9D3FE08648DULL, 
            0x90D82FB05ED59D07ULL, 0xCE93785F0C27233BULL, 0xE29C58FD4B9992D9ULL, 0x3391EB0E282C7AC2ULL, 
            0x5CBC54C0723C2DC5ULL, 0xA2A989EEA8321C1AULL, 0x46548EFB34DBF08FULL, 0x7E594EA5904D81DFULL, 
            0x07EBCDA7CCA35822ULL, 0xDB5CC32C528F62E9ULL, 0xD51087803A432EF1ULL, 0xC06CBA4466134A6DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseBConstants = {
    0x2B430480F6A1B5E4ULL,
    0x37771F097DB48205ULL,
    0x93BC1610A3FBB627ULL,
    0x2B430480F6A1B5E4ULL,
    0x37771F097DB48205ULL,
    0x93BC1610A3FBB627ULL,
    0x05CE5CD4D1F2B672ULL,
    0xCD8566738EC4D4C8ULL,
    0x5D,
    0xED,
    0xA7,
    0x32,
    0x2F,
    0x17,
    0x3C,
    0x5B
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseCSalts = {
    {
        {
            0x20FCF024CC57E056ULL, 0x26CD351974D24535ULL, 0x891A67CD7918ACBEULL, 0x9B8E46F94687C8E4ULL, 
            0x1E2E2EB02A17826AULL, 0x8C65E3A5A0D64444ULL, 0x500AE64BC3EE831EULL, 0x6A1365FFAA93DDB7ULL, 
            0x816FA19B17BD1D66ULL, 0xF4A137CF66765538ULL, 0x364F75E343D41F45ULL, 0x54EF6A621B753E18ULL, 
            0xBB8FA52B27B22CE1ULL, 0xECA7C97ADDD42219ULL, 0x11957F3F79F6EE24ULL, 0x4F32D1BC8E7C855DULL, 
            0xC7F3B4A6D076F60EULL, 0x6CFA96D5FDAD47AAULL, 0x5205997D450E2402ULL, 0x76FE2C8F9A714CBAULL, 
            0xC0F8EE31A5E433CAULL, 0x21CEA137B72BBC55ULL, 0xCAB291B8B309B275ULL, 0x9653CB090B135B58ULL, 
            0xBAD6AB3D31FE7CDBULL, 0xD8EB4EDF90CC8D15ULL, 0x7BFE765CF1417E25ULL, 0x3353DC3D2A7CE1EEULL, 
            0x45988594D79B99A1ULL, 0xD78F1A7B965036FFULL, 0x76DB4EF143808F33ULL, 0x9874A5C91EBC24F4ULL
        },
        {
            0x604C17855EF733D9ULL, 0x2B8311D49C33F01DULL, 0x606BEE746BF0794CULL, 0xB62C5432576914B5ULL, 
            0xCB758609CE1110E2ULL, 0x7BD0F3493F79EDC4ULL, 0x5852FFBBCB162251ULL, 0xCE97BE25F3E3D1CBULL, 
            0xC3C606A306EFA0AAULL, 0x57351057A665CA31ULL, 0xA690AACD8FA220CDULL, 0xFAC37122AB1E4FE7ULL, 
            0x1F18AD645D2F105AULL, 0xC092B055300E90A5ULL, 0x2BB6702B7E3E2BC6ULL, 0xAF823C55D2FE8554ULL, 
            0x600376210ADED0B2ULL, 0x9CBCD9ED7AB561A1ULL, 0x9C7D51653E63AFF6ULL, 0xCB310FBA15DBDFECULL, 
            0x428CC7FF0BD2C655ULL, 0xE89D40B6675863F7ULL, 0xA3E066F7B4F11510ULL, 0xA9B17953804948C2ULL, 
            0x4CA724D895385220ULL, 0x500D0BABB3F5D795ULL, 0xB6F3143213563760ULL, 0x1411C0497E42648BULL, 
            0xD368BE66023F5F43ULL, 0xD77AF63CF874DFD2ULL, 0xE73E1AA8C05E6F99ULL, 0x84442AB6E856B65AULL
        },
        {
            0x8B0D25F216E53A50ULL, 0x6DC46802B2991E2AULL, 0xF0708F143F6C35BAULL, 0xEA5ED8A68ABE3078ULL, 
            0x9E3993FA7681AA9BULL, 0x476530CF1AB0CCBCULL, 0x1CBA07390572D4ADULL, 0x27603DFD635BB272ULL, 
            0x024534C5DEA56CC0ULL, 0x7CA1A64AA5F65929ULL, 0xEE807E1A39CF0141ULL, 0xF530554559AF29C5ULL, 
            0x6BCE04650B0F5A92ULL, 0x21207BAA6A271194ULL, 0x6B465E65F4713A14ULL, 0xD16935D98D5BFB50ULL, 
            0x8F24D588C10C189EULL, 0x049BBAEAFE2219B5ULL, 0xE0203C5E0517C835ULL, 0x559EE8627D63F860ULL, 
            0xF9A4BC5AB839A6BCULL, 0x108F4ED4936B334BULL, 0x7EFC099B9D7A53B4ULL, 0x686BF41C3EB8BDDAULL, 
            0x271ED99A88239D6AULL, 0xBCD7918077797553ULL, 0x0990FACC228191EBULL, 0x379C175067E93B9FULL, 
            0x4F79F0E8F69A86CDULL, 0x2D17885E9B1F812CULL, 0x58E1DFF231C4E26BULL, 0x1D3A011E57E9F8DFULL
        },
        {
            0xCD1EC261717601B1ULL, 0x21032277A0E3E22CULL, 0x05A0EAFA3EAD1259ULL, 0x7C75F2DADB6186F5ULL, 
            0xA7E9B7260E4590D8ULL, 0x01492D18DB94DD24ULL, 0x7E9072713511A559ULL, 0x594B6F7D666A952EULL, 
            0x6607DF0BB0E0F1ADULL, 0xD79BDEE82FA73A3AULL, 0xA112D2977ADB240EULL, 0x3105800207302D47ULL, 
            0x8AB3F3D2FEB44E64ULL, 0xFC2B04D60DF1F1C6ULL, 0xB5FB0AA121ED9F73ULL, 0x41444F53E45B4023ULL, 
            0x6B94C5F790F494D5ULL, 0x2AB1EF2505039DC3ULL, 0x7AD073828CCA5F28ULL, 0xA4003137E8BC3DF7ULL, 
            0x9E8B3EB504BC1A61ULL, 0x359BF787DB7843FDULL, 0x0BEF4275E4F864AFULL, 0x0C01BF7753A3DC63ULL, 
            0xAE4C74B3078A3556ULL, 0x470C88445B49F533ULL, 0xE70230672ECB8500ULL, 0xDCF931D38FD0110CULL, 
            0x7B1DE1EE9E695B89ULL, 0x230EBE15F3C0178DULL, 0xB0C80F9CFE30AF06ULL, 0x20789BC8D13FB5ECULL
        },
        {
            0x6B8E77AB29601CD1ULL, 0xA1DD99511B1DE792ULL, 0x4AEEE09900641A31ULL, 0x758BD24A19D2334DULL, 
            0x67B359A8A42B9DE2ULL, 0x42BB08B5BF47055FULL, 0x02A8106B193CB364ULL, 0xFF91BECD42E824B9ULL, 
            0x2C4B9E050F077D02ULL, 0xE69A9CF3D09F04C6ULL, 0xAE72A11180A6736DULL, 0x670AE46EDDAFB6AFULL, 
            0x4696F22AA1B1C260ULL, 0xB7D3C10E086D05A4ULL, 0x4090D84351895A9AULL, 0x8F9B864C4C8E7629ULL, 
            0xE8F2FE9FF4F50F52ULL, 0xEFF6692A665B295CULL, 0x461C6CF7CD8C7AFFULL, 0x03BE3DB5EA66A157ULL, 
            0x073D3338CFBD50F3ULL, 0x4E0D4EB39DA532EDULL, 0xA894F45981043BCDULL, 0xE52A8B7890C3F0EBULL, 
            0x00C550456014847DULL, 0x97DE48EE78102E24ULL, 0xC36D5BFAD9BB5977ULL, 0x459629D3A252AB9CULL, 
            0x6E310F39A11BA36CULL, 0xBEFD8BAF096FA2E9ULL, 0x19E05D89A3A8218DULL, 0x35322DC1F8ED3C41ULL
        },
        {
            0x7DF52EB6F82071ABULL, 0x8CA9ED5D4D0CE66CULL, 0xF300AA1696463757ULL, 0x4CB61F1996853263ULL, 
            0x9AF9713A517B338CULL, 0x45D60E0FC6DC9F82ULL, 0xA1BB5DC02A258CBFULL, 0x9B4BA9FF9EAFC982ULL, 
            0xBF5A45CD7F21208FULL, 0x7060FED714439205ULL, 0xBCCBC91F976C9A40ULL, 0x3A5041C8FAA69ABDULL, 
            0x2FE6DEEDF3101010ULL, 0xFE3E5DC97E1843FBULL, 0xAE1EA860A1CBD87EULL, 0xDF240C677CD773D8ULL, 
            0x5559B62CD66C522CULL, 0xFFC0B66C40BB0B12ULL, 0x2813FD95DB47430DULL, 0xEDCFD4F2D6E48A56ULL, 
            0x8FE59620EC71624DULL, 0x50D3AA37AB7E35DFULL, 0x381CA7E24B1F9126ULL, 0x40A847E22088DC9BULL, 
            0xF3566ABD2855A7C5ULL, 0x8D33B797B8B76CD3ULL, 0xD988B5BC083D0A7DULL, 0x4725605A078D1AD4ULL, 
            0x8509AFB0E7F0B4C5ULL, 0xEE410D9326FAA253ULL, 0x5B17FFD948086995ULL, 0xE180FFD5C9D64F41ULL
        }
    },
    {
        {
            0xC88C4C69C70376CAULL, 0x2932920053718DD1ULL, 0xE107E65D0E815E34ULL, 0x99AEA6FF4DFBA28CULL, 
            0x512ACCCB53F8D3DAULL, 0x5C202A3B7C89BCB0ULL, 0x02F392132CE4C547ULL, 0x153EAE19124363BAULL, 
            0x8E8B68E76E94EBE5ULL, 0x9D2C041B15265F7DULL, 0xC1B1808F653EA11FULL, 0x8F50DB4B90DE6A81ULL, 
            0x125268BD54240D5CULL, 0x28555AFB806C033BULL, 0xCD57FA059EFAFAB6ULL, 0xD2F1528A17E43F80ULL, 
            0x80AEAE5431C0E89CULL, 0xD901437F7105604CULL, 0xE2191908EA126AA5ULL, 0x4E31C4E5D7461C07ULL, 
            0x2B27CD86952B3259ULL, 0x190D76ACC9911A2BULL, 0x29F9FA3CA8FD8C08ULL, 0xAB509507B8C39FB0ULL, 
            0x2012CCE8853F724EULL, 0x5C602C31CEB5368DULL, 0x34189A5047BD35B2ULL, 0x28782ECEF50C2C46ULL, 
            0xDC6BB76677069A71ULL, 0x6BB7734E0F42FCD6ULL, 0x9F5A644FF6D8EEBAULL, 0xB22B9D2E36E494DDULL
        },
        {
            0x9E8C1BE7EBA79C0DULL, 0x59E9B2D982C7ECD8ULL, 0x3646D574A3DCB0DFULL, 0x6C1B637940C78CE2ULL, 
            0x2479BF4FAC8EE404ULL, 0xC804D8601D49B88DULL, 0x5124787821D4492DULL, 0x476D09263581A14AULL, 
            0x17622165BB5C9B7EULL, 0x0459F19AF2F45FC7ULL, 0xE9B85C3D1AAB9905ULL, 0x1678843B362189C5ULL, 
            0x1813B2F61724ECB8ULL, 0xBD194C4E48307DF8ULL, 0x35E6F1A70839422BULL, 0x46E297328FC5D6DEULL, 
            0x087C38B9A8217C69ULL, 0xF990BFBD7565A8B7ULL, 0x5E1A515FBB8359EBULL, 0x92F7A403287895C5ULL, 
            0x92976CC1BFEBE2DFULL, 0x1576DF6187E231FEULL, 0xBC08191016DB8F62ULL, 0xAA004252E09986FDULL, 
            0xB7B480C3F4C8B0A4ULL, 0xBA980F0EC67C8118ULL, 0x3CE8CF6853CADA16ULL, 0x39F1C7050CAFBCA8ULL, 
            0x1B03347227F1571EULL, 0x78637D76E5E74E31ULL, 0xC99A3A9CC4EF1BEAULL, 0xF381091096D5B284ULL
        },
        {
            0x070F46728D33276CULL, 0x5F9DA1CA7DB9A036ULL, 0x1A79157FEA25664DULL, 0x03853F6B464ADC5EULL, 
            0xA73A694011057694ULL, 0x2BFBA20391CAD71CULL, 0x91E15E04FE80FE8CULL, 0x2B86348F4821197AULL, 
            0x91565473E5F5F0E0ULL, 0xAF17D0DF4D4C5A5BULL, 0x039EFADE785DDC56ULL, 0xCD1B38D9CFA14E0CULL, 
            0x337D11197A3C6F23ULL, 0xDD3A7FDF6D2C7096ULL, 0xE1684F836679A192ULL, 0x479917B8E3346339ULL, 
            0x4C3C9D88BD4288D2ULL, 0x8EF04EA20DD47B88ULL, 0x5E532310B6533E26ULL, 0x21E35CEAC2C203B9ULL, 
            0xEBE184F46FF0ED92ULL, 0xFB9120CE9DDC0507ULL, 0x1AD495CF96C28E99ULL, 0x7163E01B40410394ULL, 
            0x58BBF37C700AB94CULL, 0x0E2477C344A46ED7ULL, 0xFA384FAF678A061DULL, 0x8058FD3451010F62ULL, 
            0x4497AD5B0960B822ULL, 0x4054E5A9891BE25BULL, 0xF51A66D17AEFF0FBULL, 0x37279C3D88DAA760ULL
        },
        {
            0x6FD8D57A1AC3F87CULL, 0x163BCC05C3BDDF17ULL, 0xE42F04FA4F0D6229ULL, 0xA20464C6BB5209D2ULL, 
            0x4DC0E7C7C86AF021ULL, 0x11688AD7E04FF4E0ULL, 0x6FF32063CB2F74FDULL, 0x76319D802CEE32C6ULL, 
            0x97ED08767993A965ULL, 0xD12443C346CAA042ULL, 0x6DD8383A961F96FFULL, 0x56215FBA770BBF16ULL, 
            0x5831211786903C25ULL, 0x37E2E25D98AA67CBULL, 0x7480F920F8DC9E08ULL, 0xBC9BB0E354066AFCULL, 
            0x11B290FFB4737E1FULL, 0x61E53436AA8686BCULL, 0x3BA9C4F4DB8805D5ULL, 0x7A242F1BCC27EA90ULL, 
            0xFE97AF780970645AULL, 0xF8F83116B7780E42ULL, 0x5BBD759917C387DBULL, 0x8A9BEAFA8E06F733ULL, 
            0x02CBBB4E13DE32CDULL, 0x6097FBDAC372DF53ULL, 0x2098E24290A7B0E1ULL, 0x93B4E6084A31DB39ULL, 
            0xBE38FB6CB57C3303ULL, 0x8AF403ABCFC80BADULL, 0xFA1AAE3373A5035BULL, 0x6E2D195C92CED655ULL
        },
        {
            0x3D8741A98E2EBF27ULL, 0x4609E7CECCA49BC3ULL, 0xC85CDFC50021514CULL, 0x391BA5693D981FE3ULL, 
            0xA68A49A7E125B50FULL, 0x2D88FDDA7EF7CB38ULL, 0x662F4FE787EA230CULL, 0x99B6182F8E9DD604ULL, 
            0xFF73364BF0569C78ULL, 0xC2C41512C5F60F38ULL, 0xC3D3C843FEAC9FC0ULL, 0x5AF44E8A54EC2BFFULL, 
            0x62412C681DA98D6DULL, 0x384AA03A879E75CBULL, 0x2DD974D1CD8C4AEDULL, 0xFBBF5183D118A11EULL, 
            0xC77CA52D7CDE6055ULL, 0x21007B2AE4ED1207ULL, 0xAB03FCA173326530ULL, 0x3ABB3171A98F5D79ULL, 
            0x139661E79ADFBED1ULL, 0x71111BA0A4B752A0ULL, 0x6B0E99B606ECED07ULL, 0x71FA1D85EC7AD7B0ULL, 
            0x24BB35E06A8F8A94ULL, 0x2A6EEAE8B466B0C9ULL, 0x7AFA17393C634143ULL, 0xCA6D8539FDEDB8F7ULL, 
            0x2E4DE392C3C609EBULL, 0xCD16D37EF48EAD37ULL, 0x7185021E31282112ULL, 0x04E98398FEE12879ULL
        },
        {
            0xE544C1702D895FBFULL, 0x56CBF10F9DE2EDE0ULL, 0x50AEF58B68049F0CULL, 0xD5E0E68DC94E9362ULL, 
            0x033EA2DC785A1C04ULL, 0xF2D4EB1EF1A2123AULL, 0x88BCE33BE784880FULL, 0xA5C8D9648B9DDEC0ULL, 
            0x5287AF3D1883B3E9ULL, 0x2492EF5FFF806B8BULL, 0x79B53913E29AB54EULL, 0xDA4ECA2E35851074ULL, 
            0x8D65F3C5EE89112FULL, 0x2537E16675475E93ULL, 0x53C52095BC6E1522ULL, 0xBD04D475530E91F9ULL, 
            0x2F5ADD94BD5BF9C6ULL, 0xDCA7161A7E46595EULL, 0x987801F1D022D9E8ULL, 0xF790A8D782EFB8E5ULL, 
            0xC559139AA735ACFEULL, 0x87C8AD0F0DC950EAULL, 0x91ED3C2513D1D7B4ULL, 0x8E9B30E1518CB227ULL, 
            0x010E0876986E284DULL, 0x69FAAB8999FAEAA4ULL, 0x94DAB06471AD547FULL, 0x69D417C6A4073BB6ULL, 
            0x862FCBD05F75F1EFULL, 0x8C1F66CEB73E5D38ULL, 0x3C69A3E4D229DE8CULL, 0xC6AF04448F90C3B1ULL
        }
    },
    {
        {
            0x425150401A952140ULL, 0x2908569C61327209ULL, 0x3C692F5983ACD5DAULL, 0x1DD8EE1C2ED37DD7ULL, 
            0xDD2054A311A0E94CULL, 0xF2939A3AE6BA9366ULL, 0xAD5BC8C51504646CULL, 0xE3492ED6F2A45618ULL, 
            0xED32227A1A2283E2ULL, 0x23264632CC751D24ULL, 0x57CD71546A265DDBULL, 0x51D93F6664F8DD76ULL, 
            0x091805369DADA3B6ULL, 0x5A2EEA9AF042A7D6ULL, 0x82862F4402AEB08CULL, 0x491593DFDAB52429ULL, 
            0xB1460E59021A4B68ULL, 0xD0F8FBBC1F8D8F89ULL, 0x3AFB194756231D34ULL, 0xD78E7B18FEBC83D9ULL, 
            0x63569856F44193FAULL, 0xF9EB9EA56C8F27F5ULL, 0xC07EDF9335C2B4AAULL, 0xF712EFCDBB44665CULL, 
            0x14DEB2922B6CDF1EULL, 0xAE93A6FA982FE1B0ULL, 0xB65414F026491D6CULL, 0x58B6310A3506E008ULL, 
            0xB70B49A2EF1C6882ULL, 0x83710F23932CFB30ULL, 0xDA14E5987C711157ULL, 0x9EE7B829BBDF5A72ULL
        },
        {
            0x04BA85D882AD8F72ULL, 0x3D79F36884046D6AULL, 0xA2CF296064802FC2ULL, 0x3264FC95F79409ECULL, 
            0xAE8CF752C2AEB801ULL, 0xDC93E9D79D5DE606ULL, 0x52AAF11A96952441ULL, 0x4D131FBD9A4F3AA5ULL, 
            0x39C545FA3C7E0EB6ULL, 0xEC125BD9FC6E6AEFULL, 0x25B2A3758A5C4382ULL, 0x8EF15F506618C7BBULL, 
            0xF562E62BE3A11D08ULL, 0xD139F41727E0132DULL, 0x2CAC8A80AB0214E1ULL, 0x08637D5EF3F43A7AULL, 
            0x49BC521A917B655FULL, 0x4D1A86783E9E964BULL, 0x91482C08E6A43031ULL, 0xF3CFBF4461288765ULL, 
            0xF838756B86DC5682ULL, 0x2FF44E5D3D643FEDULL, 0x383F495F58D83148ULL, 0xFC6B9BE417438920ULL, 
            0xDC8E2B0E188FAF37ULL, 0xFEF530721376678CULL, 0x30C68563B7603E05ULL, 0xFC6319E83A427F0EULL, 
            0x9D7076E2F5BEB48FULL, 0x45E41429E2974740ULL, 0x681B84CA5DE31EBCULL, 0xA66D71D636E0AF37ULL
        },
        {
            0x2764492B9365C6E9ULL, 0xBD932B6EF514E36AULL, 0x6F3D065ACD146A4BULL, 0xB132F909DE47D181ULL, 
            0x6C9030F2C235D6A4ULL, 0x241EDA63EC693574ULL, 0xF00BF31BF16833FBULL, 0xDDB1B26B716874F2ULL, 
            0x05FBA1E2C882130DULL, 0xB99EF0439E1ED4EAULL, 0x4EE899BF0C1DD013ULL, 0x537A6942F8835EC4ULL, 
            0x70ED1652BB80D59CULL, 0x87B47452C2B4C02FULL, 0x9F069AE0B37AE814ULL, 0x6C675C9B401F9E70ULL, 
            0xA9593AF81CEDA50EULL, 0x1F2F97B0114464A4ULL, 0xD4335EBACA15165FULL, 0x3676DB8FCDB64A56ULL, 
            0x143636D74D8296B1ULL, 0xD683B8F6039011BEULL, 0xFAC11789A5FAD1CFULL, 0x7E0373CA5EC3923AULL, 
            0xFA74C5017FB925D9ULL, 0x5D84AA34DE34C6E5ULL, 0xE5395CF7F512D267ULL, 0xC8DD8A799053F844ULL, 
            0x146D439F23762E4FULL, 0x66C9F91EA47E8A1CULL, 0xA9233C85A03F6C5FULL, 0xD81DF31EE552B5AEULL
        },
        {
            0x7D5D1952B53E2FEAULL, 0x6C95B1CC2296D376ULL, 0x4ABA201B0446C82DULL, 0x91A28AE1BAF199E0ULL, 
            0xC8AB80CC415D36D0ULL, 0x77557C7EFAE6ED3CULL, 0x00383153991900A0ULL, 0x3A5D2200D8EA526CULL, 
            0xA6E33277F4184905ULL, 0x326416156C6D01FFULL, 0x56E3BCE2BD127632ULL, 0x2254874395E3DF57ULL, 
            0x88E361AA24AFE049ULL, 0xFED4BA9964810E4AULL, 0xFBBB26D36AE5E528ULL, 0x13D313C362BEEA4FULL, 
            0x5B598CE22417154BULL, 0xBEAE8562A4698B8DULL, 0x4C98E99041C641EBULL, 0x335EDB582EAE634AULL, 
            0x0D5A400AD708C93BULL, 0x15B19A062DAED51CULL, 0x1838985C9A0E24B8ULL, 0x4B05846696346BFFULL, 
            0xB61B9B01E2F6530DULL, 0xB01983229E873BD4ULL, 0xA056EB317C6D1CE9ULL, 0x3AE070BAC0104A91ULL, 
            0x4FF3CF69C46C7FDBULL, 0x0007BEEE3D38803AULL, 0x2E3A734F82024AF5ULL, 0xD6CEA3D91D64929BULL
        },
        {
            0x7D3B8C1CACEAD8BDULL, 0xF14D016E5A00C066ULL, 0x14BBD9F5F6A5AE28ULL, 0xCC678EE0503A9096ULL, 
            0x2AD239B456012471ULL, 0x29D3572D93C454EFULL, 0x70AF50A3CC123445ULL, 0xA69F5484D874302EULL, 
            0x6A4FF6B654EFFC7AULL, 0xCD8EA16A789D2849ULL, 0x9F2AC8E7970978F3ULL, 0x2B625D53646B6D5DULL, 
            0x49DF085ED0A4E2B2ULL, 0xE215CFCB41600927ULL, 0x6525DA5D116E77D1ULL, 0x2D7DCE88807C95AEULL, 
            0x7A2BF9BE477E9C87ULL, 0xC47D61E25175478FULL, 0xE8B08FD93C85618CULL, 0xC2C8C52D312333B1ULL, 
            0x70337560E7649253ULL, 0x20A0900E1C024C6DULL, 0x10049FB1CF8FFFEEULL, 0x4A1E66451B561645ULL, 
            0xD4964E73B0A15DC3ULL, 0x78DB5DB9B4C9928DULL, 0x2EC0C0129EB8CC35ULL, 0xFD1780980EEAE7FEULL, 
            0x6AC93AEB49ED9AF1ULL, 0xBBF560885CA52AE1ULL, 0xBA633937C7917427ULL, 0xACE8817A4CA65EE0ULL
        },
        {
            0x826FFFD24E967709ULL, 0xA2C3F49F6598FA04ULL, 0x75AA490C5819DB52ULL, 0x239113089DB3FF2FULL, 
            0x752DD388D9759D4CULL, 0x3F5660746E46FF0EULL, 0xF6EC255F235BF755ULL, 0xFF1D9F2E3943A729ULL, 
            0x5C7CFE1363CA5A32ULL, 0xE68D00241CAEC5F2ULL, 0xA2B850A571C62EB7ULL, 0xB0DFC0CC3576E000ULL, 
            0x8EAE55DA6023BD10ULL, 0x5DBE72F24873F18DULL, 0xC812078EA862BBB9ULL, 0x67D6D34BEFAD63BFULL, 
            0x90268A9DC4DE3B7CULL, 0x1BFAE88A9418A100ULL, 0x2295F433F6ABF7D3ULL, 0x35978511C56257EAULL, 
            0x204E9B4F578A30F6ULL, 0xB6FA151A30E8F76BULL, 0x8CF380C96DEAEF20ULL, 0x18974FCE70C3E089ULL, 
            0xEAEBE2E30076F094ULL, 0xFA96C13E24048CBFULL, 0x50C50E9D3E39499CULL, 0xA066306D8D29784BULL, 
            0x424D9D105C66EBCDULL, 0x0F7224E05ABEA0E0ULL, 0x71EE95C8AF196281ULL, 0xC6DC6F197B9E7CDEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseCConstants = {
    0x277CC15EFD54EFFDULL,
    0xF7450E332D67D87FULL,
    0x3264337EBB365B71ULL,
    0x277CC15EFD54EFFDULL,
    0xF7450E332D67D87FULL,
    0x3264337EBB365B71ULL,
    0x5E0DA604F61C40B6ULL,
    0x58BEBD138665C815ULL,
    0x04,
    0xBE,
    0xCD,
    0xD5,
    0x0B,
    0xCA,
    0x2E,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseDSalts = {
    {
        {
            0x42C49A48EDF8D8A4ULL, 0xB8DC2C10DE2B4E93ULL, 0xD583AA44D627B62CULL, 0x48CE72ACA061B8EAULL, 
            0x30F0801564E15B2EULL, 0x829B68042DE58AC2ULL, 0xE3DDF7D4EFAC958BULL, 0x54E9CDFF6FAF16D5ULL, 
            0x5AF6C1ECD1F2EEBBULL, 0x2BADAA29F480E14BULL, 0x545BFB9A25169739ULL, 0xF3CD8C64562FFB4DULL, 
            0xE92AE177D6B2EA4EULL, 0xE779C98822E09E33ULL, 0x3293EAF6ADC950F5ULL, 0x05E7E8044B4B6EE4ULL, 
            0xD598D20F958945C2ULL, 0x8F23310B11C430C1ULL, 0xF5C98D4061390172ULL, 0x32FA634B04373A8AULL, 
            0xE537C328E493FCC4ULL, 0xDD487AE950BFEDAEULL, 0x13BD9EB000397F71ULL, 0x6CF5CCDA6BE95557ULL, 
            0xDE1247EE18A7E51CULL, 0xCBE8F67B59A57EC7ULL, 0x08ADA46BD57FFCA8ULL, 0x91A7F8A5EA7E14F5ULL, 
            0x64BE8EC50A1F21BFULL, 0x8C8F4271816F6FDAULL, 0x8505F76A546F1106ULL, 0x401A8AC2F7206E0EULL
        },
        {
            0x42337F8B36D3984EULL, 0x19D74F2065CCBA49ULL, 0xB015FCD326789FF2ULL, 0x14E50D6098021A59ULL, 
            0x409AF9D2E2D590B4ULL, 0x4C669B8955B26213ULL, 0x7B873E620478174FULL, 0x100091979A9F9003ULL, 
            0x156370C2361C292DULL, 0x9877C4C30A3B7A20ULL, 0x8F98BC02F6B49ECCULL, 0xD0B40E95CF57702EULL, 
            0x936EDBC7CEFB382EULL, 0x2CD0732E9A2A93A0ULL, 0x3C8A35E4989218EFULL, 0x8ACA7186A6E862F8ULL, 
            0x307EF4A3E20B1A2DULL, 0x993BB1F55E424BF2ULL, 0xFF90096DDE958C56ULL, 0xAA1C8F3CA05F5315ULL, 
            0xBB73A912DA9A9F0BULL, 0x8CB35A265BEE2052ULL, 0x897F8091EAB71180ULL, 0xC42BF322B92F04ACULL, 
            0x2D243C4D07B012DEULL, 0xF28E538499F81F36ULL, 0x5047A4FE7CB74BD9ULL, 0x888EA5A8F91B2015ULL, 
            0xE58AFCF7144F684CULL, 0x224C118CCD992E04ULL, 0xC02109E9D9AE3DC9ULL, 0x84067FC983BCA2EAULL
        },
        {
            0xE724FF7E04942635ULL, 0x9147988D9A8A1213ULL, 0xAF0FC5012761B8D1ULL, 0x1F56F106489FB4A0ULL, 
            0x65822619593BEEE8ULL, 0xD3B7CBE24F691498ULL, 0x41ABF17BBEE9065DULL, 0xD4D84D58457638FAULL, 
            0xA00E2B6F99E12E2FULL, 0x956754E5E71E13F6ULL, 0x101F84B74A141484ULL, 0xED8EC36F9388F1B6ULL, 
            0x150A72211827B91CULL, 0xE88A1C523C6B2D78ULL, 0xD66362EF2C3D6A47ULL, 0xCDD87AC080FAF93CULL, 
            0x346343C5853D5ACEULL, 0xA177249A016D0ECEULL, 0x59EB97A9EFB27454ULL, 0x915E7B32C5DA7CEBULL, 
            0xC43EAC4F03F8D89AULL, 0x9FB591570692D753ULL, 0x3CC1C91F6C47D710ULL, 0x60CD60146A7ECB04ULL, 
            0xF0519CEA9B99E2C0ULL, 0x934DE3FAE7202E1AULL, 0x28FCE4F08646A251ULL, 0x26233925AC629FCEULL, 
            0xD6E94ECD29E04F78ULL, 0x2F3959AC3B8D0369ULL, 0x000A1B7DF35B6AFCULL, 0xC8E94A2FDD15FAE5ULL
        },
        {
            0x2A810C1F5D18673EULL, 0xA9511BDA6AC8D3F2ULL, 0x35A30BE0F6A7B16AULL, 0x9DAD45BB95BC8446ULL, 
            0x89BA505734F07107ULL, 0xA75940C8B5E9B587ULL, 0x051B4EEC5B284F4BULL, 0xEE7652B0D11A0D0BULL, 
            0xF2CCFAC0B8821465ULL, 0xEAD293E90471E2D1ULL, 0xEB925CBAEF1CD05EULL, 0x0EC9B08E04670E63ULL, 
            0x4B0F2552F18F6370ULL, 0x69BF1CF4B13EFDCFULL, 0x58C65E81FAC1BB1DULL, 0x7A757823A4F8CA62ULL, 
            0x0F766A1D317248A6ULL, 0x410954673D598F5DULL, 0x03B1C9A96B9A0037ULL, 0x868D0063383C3754ULL, 
            0x2C7C8AA55324AA2EULL, 0x4D57E08D4798CE77ULL, 0x66A4C2EF50E46183ULL, 0x77BDFBAA409B9AD1ULL, 
            0xEAD9592349B8C7CFULL, 0x7A636B95E9E8227AULL, 0xA04B8B96204C3D87ULL, 0x92A669C1DC344959ULL, 
            0xF14D01D42DA1CED9ULL, 0xF4E662106ED135C6ULL, 0x45B658CB3A3713DDULL, 0x338320100B7A5710ULL
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
            0x6DAD1E86AFCE0059ULL, 0x6761AE87C4667B8CULL, 0xC53A10B96DC6D278ULL, 0x420E6851805E23A7ULL, 
            0x26B88BAD089C14B6ULL, 0x80184CBD341052F1ULL, 0x3CEE25EEDEFE1BA4ULL, 0x27816269E08BA5B3ULL, 
            0x23F0E08F83E6F5F2ULL, 0xBFB087B80DC55560ULL, 0xD58C65339D683F7AULL, 0x68BA3C4C1F90297BULL, 
            0xB72D724B1A8384EEULL, 0x6BBA83B8141C1DD2ULL, 0x06A23853E8783FFFULL, 0x73749C182A1A7059ULL, 
            0xA7C85B3A7FDEC46DULL, 0x8359D6DD2E1391BCULL, 0x6D43CE33A4E30D82ULL, 0x7CA89858DAE6A6F7ULL, 
            0x58E9053CC8C0CAB9ULL, 0xEC897AADEE448441ULL, 0x11DFCB48F526CF4EULL, 0xCBD4CB3D7EBD33A4ULL, 
            0xFEC2246FDBCC145FULL, 0x2CBD72E7B1336410ULL, 0xE48E4A2A6A55D56FULL, 0xD9C9863C72A7E1B2ULL, 
            0x6DC8543BDAC48FEDULL, 0x36A29E11BEE5D5A6ULL, 0x477719185F4B7D4FULL, 0x54C358DFBB421739ULL
        }
    },
    {
        {
            0x4FC439CAD87A18B8ULL, 0xFC60E5DF95324EC3ULL, 0x30DC882C7D8FF6F8ULL, 0x53832EE2709B0CB4ULL, 
            0x0086D4D54529D72CULL, 0x77C9D66EFE2EB614ULL, 0x82C5F0A4E991A8E6ULL, 0xBDCD8DCD64C6D29CULL, 
            0x575A458D9FCAC296ULL, 0x4AF1EFF5ED0EFCCEULL, 0x19B48415A6F70FCBULL, 0xFB0BAC6B4CECAEF5ULL, 
            0xA0528422B2D400C9ULL, 0x3DD8A12785E15957ULL, 0x063823E51443A4EEULL, 0xB746E969A8798EB8ULL, 
            0x2CAE0608600F88D4ULL, 0x7EB0D07F992D30B0ULL, 0xE34A7D5672DE869FULL, 0x938282DDD08E4FD5ULL, 
            0xA872069A4D27726AULL, 0x6F7026DC6169281FULL, 0xE687CDF41800B6E7ULL, 0x7A03E8FA93302263ULL, 
            0x81DE62CE839990E3ULL, 0xE512D9DA28B18F02ULL, 0x2F6F039DDC993BC1ULL, 0x464DB0FAB2D5B539ULL, 
            0xA938AAA672989A7FULL, 0x961F4E385F05AAC9ULL, 0x276575EFB7DF766CULL, 0x72725EFA2C9A47A4ULL
        },
        {
            0x7CDB8627A2B73EE8ULL, 0x5B6E57DD45E677BDULL, 0x4D34ED86F8993418ULL, 0x2881F05CDE8D24F1ULL, 
            0x165E4B0AE0BC9791ULL, 0x4E518F5BADE6D707ULL, 0x5267A35D2D75AE71ULL, 0x3F3123DF8A6F77ABULL, 
            0x3E2B318981B46E24ULL, 0xE7025EE4AED24804ULL, 0xAD36448455BE99FEULL, 0x42D105E9BB38A701ULL, 
            0x41497420E062D455ULL, 0xB12788C8A58649C2ULL, 0xB9D548A839D31CF3ULL, 0xC598DD1C2C4A2AE3ULL, 
            0xA66BF8FB282AD1C2ULL, 0x3E63132B4E8D9E18ULL, 0xF3E6E6FF807FF0A3ULL, 0x481EF6FADA6075EEULL, 
            0xD36010FC811173A6ULL, 0x885200382DCDDF24ULL, 0xE4EC4D7C4A7F4605ULL, 0x363390630E0F7263ULL, 
            0x4C7C534378FF00D2ULL, 0xCCEA1C79D61CA952ULL, 0x1D9CC589B99FC526ULL, 0x5F681BA1C5BD23BCULL, 
            0xF99F6F7DCE795A06ULL, 0x2EE11657278577B6ULL, 0xCA151D6F8ABD45BAULL, 0xEED1B56927239F9AULL
        },
        {
            0x2AC63F4367AD4381ULL, 0x13A7A2392A3201A0ULL, 0xADBDBDDF46BF0D1BULL, 0xE5D46F1C61F362B8ULL, 
            0x16D70EA211EF86A4ULL, 0x634F700633DA9C46ULL, 0x98072A891CCE849AULL, 0x20AAC6829F612F1AULL, 
            0xD16F8A4C6819CFA1ULL, 0xEA8C6E78B0DC19B4ULL, 0x4058F6DBE1AF8FECULL, 0x0F654AF812ED1A67ULL, 
            0x17729D2AA34A7CA9ULL, 0x13AE70B199EFCE94ULL, 0x0D5B84FF109B37F1ULL, 0xBF626DA24D2FC7B8ULL, 
            0xABCBF0FA97D8098EULL, 0x4EE8691AAC2A5659ULL, 0xE2C747D0B4D18736ULL, 0xC1DE400BFB95CD89ULL, 
            0x90255E462F955A1EULL, 0x32B0F635E58635E8ULL, 0x0EA16AB34EB85101ULL, 0x08E3FAA580714255ULL, 
            0xEFF1E0ACD42C02B7ULL, 0x5F3AA0AFA9F503DDULL, 0xB475A1F96E092E73ULL, 0x9FF7DA8BA7B2E612ULL, 
            0xE316085877F47FADULL, 0xF02B60C8749EA63BULL, 0x0FC0A375A102BF19ULL, 0xB134481499B9D190ULL
        },
        {
            0x273E600E84EF9C34ULL, 0x52984D2A745859FDULL, 0x8BDED1A261F8EBD5ULL, 0xF155D298117F88C0ULL, 
            0x2240B36CE5F5A152ULL, 0x2BB3427DAF4A083DULL, 0x6913E8478ED9F870ULL, 0x42B7225E7B593BA3ULL, 
            0x7BEE88951B4C238BULL, 0xCFF8BCADEFFC7487ULL, 0xE85078D4D572B3F9ULL, 0xD2D6D2D08E6BF982ULL, 
            0x15376F4D8695A31CULL, 0xBC5563B9A00DDC5FULL, 0x374BEC1DD7270CABULL, 0x41CA153FC036CC5BULL, 
            0x42171E903CF4AFB2ULL, 0xA0970003FFF10811ULL, 0x8227AA8788955D69ULL, 0x5FDFCDC21922A950ULL, 
            0x0864ED3E7A8B27B9ULL, 0x7BD6042D0D466A8DULL, 0xEE0CCC6022991FB3ULL, 0x2F6F75D0820BDE1DULL, 
            0x9E169F8370CD3701ULL, 0x10573DA4CDA4C32FULL, 0xE687EE4089DC799EULL, 0x13EF0ECC31E3E9A1ULL, 
            0x1F89A20A8BDA35AEULL, 0xE821C839B0D103EDULL, 0x6F0A259EE6A17B58ULL, 0xA84CD9B3FCBD8470ULL
        },
        {
            0xA60AE85819E956F0ULL, 0x47411EB599CCAFDBULL, 0x243D6F0B699DDA46ULL, 0x43C947BC502B3D1FULL, 
            0x42B6BA8F92F59A72ULL, 0xFE0ACC1DC20E0357ULL, 0x88D9A6BE07738F62ULL, 0x046517484FE79EDCULL, 
            0x14ECCA0C0DCE33BDULL, 0x677D315ED75DFD02ULL, 0xCABB96F0387B8551ULL, 0x79100FE5C4924910ULL, 
            0xC85D27EEDDE6321FULL, 0x082A577A350030BAULL, 0x8216AC9F04F500B8ULL, 0x0DA8B464E2C1A0C3ULL, 
            0x7600EC6E4830E76FULL, 0x57327A8962B5F534ULL, 0x4FAE57428E89C8BFULL, 0x80146C5634D84660ULL, 
            0xA8B8C0AB21FD9194ULL, 0x3951DD8593243FB7ULL, 0x0CC3370731578FB6ULL, 0xB287724E2539DD60ULL, 
            0xA8B7B886FCF543A9ULL, 0x9A575FF46CC8F8A0ULL, 0x7FCD697B5A4236F1ULL, 0x88BF1AC743CAF22DULL, 
            0xD3022E5CD019384AULL, 0x8CE1F1350CD6A372ULL, 0xF8B2F4BE55C73809ULL, 0x64D389FF5C329FE0ULL
        },
        {
            0x0239BA2D88DA13E6ULL, 0x885E80AEC86A7C25ULL, 0xC150667F75C21105ULL, 0x886E61BA9D7E29B3ULL, 
            0x8E9DE638962F5C2BULL, 0x095DD2A44589368AULL, 0x79E9905B009872A1ULL, 0x294A147BA7237134ULL, 
            0xE99CCD6E7816C557ULL, 0x20950E7D8F2CBB65ULL, 0x521851865C17743DULL, 0x7D3FB2EC849CAF5DULL, 
            0xC5751C144DF788A9ULL, 0x36ABE8CBCCA1F343ULL, 0xA748CB9775DDB6DEULL, 0xF86A708074B60D08ULL, 
            0xE9AEB4512DF475A2ULL, 0x3F7EAF852F2C6524ULL, 0x62BA967030DE79CFULL, 0x4D7BDC5E673B9B34ULL, 
            0x2EC8EA5C7E583982ULL, 0xFBE4F128E669683FULL, 0x76CDCC289845C07DULL, 0xF5E17C5A67DBE111ULL, 
            0xDADCF6CC747565CEULL, 0x86318821CDC2DD1DULL, 0x5D03763F1856F759ULL, 0x7CB89E76DD020DB4ULL, 
            0xF6C175C1B38AE2E1ULL, 0x404262AF58444586ULL, 0x9CC78EC473CE6395ULL, 0xC0DC570FA0CC0F07ULL
        }
    },
    {
        {
            0xCED52999495D561DULL, 0x6F29F8099FCF0334ULL, 0xF1C6FAA2DB8DA23DULL, 0x70A31EC760FA24B8ULL, 
            0x1D7D8ED249B110B2ULL, 0x6C10DAA25B5B8ACEULL, 0xD62CC84CB4B333A6ULL, 0x65EEECFA66E5E719ULL, 
            0xAF6FDD91A3C71FF0ULL, 0x04326EC2D7CE507AULL, 0xE8B1191FE14F6283ULL, 0x364E62C5B2E24E61ULL, 
            0xAA61911C69AC72D8ULL, 0x06D548F31E9C6989ULL, 0x76B2AEC8C2069117ULL, 0x05ACAF73192D9332ULL, 
            0x1DA7EFF442717869ULL, 0x7D3A3D11E3A2AAC8ULL, 0x27C9B468CB2D1677ULL, 0xC764E995C56A25EEULL, 
            0x69BB1053AD6EDB54ULL, 0x09E4E9C57E5EF010ULL, 0x38C355081FB374C1ULL, 0xCE0ADDE1D56C00CDULL, 
            0xBA9EC0B96F3024E3ULL, 0x2E5010DB44A477BDULL, 0x411E5A4A32DBDA31ULL, 0x78874D50F2DE8FB1ULL, 
            0xAD49D8118FD04CACULL, 0x6A6833DF1C113E3FULL, 0x7CC542E23D47B4B7ULL, 0xEE3155EFE1FA25B3ULL
        },
        {
            0x47E45CFBD4EF6A9BULL, 0x2738DA9D6A64DE00ULL, 0xD82AC451A33BED56ULL, 0x464F44CEDBD3F290ULL, 
            0xA66021F425F12DCDULL, 0x6F7AEC36A00BE7A0ULL, 0x559B00C9173FD085ULL, 0x4CF0A6224FBA5481ULL, 
            0xEDA2D0638ABF18BCULL, 0x7EB9F179B245B0EBULL, 0x47F3E79F5A340359ULL, 0x2B3073F5E7DAFD33ULL, 
            0xED6912F474CA9F1DULL, 0x576F74A720098698ULL, 0x07401657C7634EACULL, 0x2CEE69B305FF1A4FULL, 
            0xD40C5BE8DAC3B256ULL, 0xA574743804424F5CULL, 0x412A3BE9FE2B3263ULL, 0x04A10048AD02F1EDULL, 
            0xF3F345BE79DA5E19ULL, 0x12FD1514796B1099ULL, 0x74B4E6164169CF62ULL, 0xAC963CB8502F159EULL, 
            0x78F45021DB4D76AAULL, 0x575DE8C3AE8CCAC3ULL, 0x0B73EA1A6D9B3C3DULL, 0xF9478A05F59B7518ULL, 
            0x17B8594BF30E6177ULL, 0x8469D7B643145545ULL, 0xC4CDC84161301956ULL, 0xE53F45D4CEAF3089ULL
        },
        {
            0xB1597921E55010DCULL, 0x54DDFC46D8B915E8ULL, 0xDFF2ACA9301F4A2CULL, 0x4D181790D455525CULL, 
            0x39ABCC4C05383175ULL, 0x59A5A03EA12AA231ULL, 0x1A559C11A1437467ULL, 0xEFF17347A1B983B8ULL, 
            0x4F2E6D89B03682F8ULL, 0xB922A35107E491D6ULL, 0x742A64308ABE493BULL, 0x810AD992DF72066EULL, 
            0xF073EBCEB6B65D5BULL, 0x9990413879BA2E07ULL, 0xD6FB1804933AD044ULL, 0xDE5D43F1749D5F04ULL, 
            0xDA04B0E92D001A05ULL, 0x0FDBBDDEDE0AF03CULL, 0xEDA84257B8E6EBA7ULL, 0xE86B7DCDF2F90DBEULL, 
            0x8FE859F0356CC2B4ULL, 0x9E93128989448695ULL, 0x5F1C1AE37B87FE87ULL, 0xA5BB6831F04BFA1AULL, 
            0xECFD711C262F9653ULL, 0x79359AF6A4385C96ULL, 0x39116DA71CAB5FF8ULL, 0xB3E876D39CF74403ULL, 
            0xE3A3FDEC5E61B36BULL, 0xF7022D252A2E70EEULL, 0x07B7178076B3257CULL, 0x93AEE94017DBB467ULL
        },
        {
            0x606F5C40C7DDD98EULL, 0xB786C79D8B292341ULL, 0x56CA7894F37C0EB4ULL, 0xE0CFB6A9DC899944ULL, 
            0xF27D3F523678D0EBULL, 0x2323B52133A75EEBULL, 0xB82521EAA59A74ABULL, 0xF9D7BEF5E1A81495ULL, 
            0xBDB5FC26DF11047BULL, 0xCC1AEB9D4D2AF38EULL, 0xCCFD008DDFEC854CULL, 0x435266AF2890C2FBULL, 
            0x482CE890BD9927FAULL, 0x19D924A98A0E4216ULL, 0xFA8891D0B7E65A2FULL, 0x3473E924AB7DF0F4ULL, 
            0x2BADC814F53F1898ULL, 0x9F25FE4FD5D47D57ULL, 0x3F728BBDB8B0C459ULL, 0x93B3DA365EAFEEB5ULL, 
            0x1BC9C2E7F9959F48ULL, 0xC0B6963233E6BDE8ULL, 0x9527E169D57552CDULL, 0xEB4BACBD4CD8EE1DULL, 
            0x97B497FE080D24DFULL, 0x369AEC2C3AE7AA63ULL, 0xDABBCFACEFBEFAB5ULL, 0x00F71A5629AAE039ULL, 
            0xC5E0DA750968ED3EULL, 0xDF5C5D9DA8BB2E5CULL, 0x2CDFB854421D338AULL, 0x87196BDD98CC104BULL
        },
        {
            0xDBFF561A3F52BC32ULL, 0x90BBA825C10D22F9ULL, 0xE730534FF08E636CULL, 0x3D6E8929A8B3F86FULL, 
            0x4FE38114413DD868ULL, 0x031063A4C4FA2485ULL, 0xA5E9A9FF7E56E848ULL, 0x27099B9E5D7F3D57ULL, 
            0x547A39C97ABDE2F7ULL, 0xAF2E8E29985B8A12ULL, 0x19E1F4BFAA04F95EULL, 0x4C5D91CF445EAE1DULL, 
            0xA0A5641E8A07A495ULL, 0x0B59B7E93AD1316BULL, 0x4E39EFEFA5477E3DULL, 0x4C0BA2E4A7C5695BULL, 
            0x6E6E1A422F7DF846ULL, 0xD2DB5819E7BE4825ULL, 0xCC5FF62CD84A95B5ULL, 0xC73336F7EA9EA5D5ULL, 
            0xFC168494F55FC374ULL, 0xE6089408D820D8D9ULL, 0x5044C895286CEFDDULL, 0xA93CE268F2172C50ULL, 
            0x4C1885E86607E470ULL, 0x5F0E469229225957ULL, 0x22CEB919D2173303ULL, 0xD0F209426219A02EULL, 
            0x2EED262B9D761C50ULL, 0x9979B1D2C7F51A1DULL, 0x8681F99E587732B9ULL, 0x627952E4E7900F3AULL
        },
        {
            0x0CC9B2A5F6968E82ULL, 0x87B268F75756BDB4ULL, 0x578F9013590D6A41ULL, 0x95FD6E8F4F3E0D03ULL, 
            0x8BB8FC538BAC17C8ULL, 0x20543E2CEB834C13ULL, 0xEB167DBDD0960849ULL, 0xA290B42AFD1D9357ULL, 
            0x7DDD03B489DF70C1ULL, 0x7B811CD8CC0B29F2ULL, 0x53AA40BCC93DAA07ULL, 0x5B990A9AF3956B31ULL, 
            0x64B750D65BFF8D14ULL, 0xC24840D4ABB958AFULL, 0x3A06A028F28A2B96ULL, 0x3DCF2C8ADED95955ULL, 
            0x4720A4A43D33B12DULL, 0xA89D05874139EA99ULL, 0x42AC570ECF3EF059ULL, 0xA2B77BB698635B1EULL, 
            0xB4821266CC61B8CDULL, 0x9BFB2364A0F3058AULL, 0x358C58F69385344AULL, 0xD8CB83CFD34FDE18ULL, 
            0xB0FA8905AAB837D7ULL, 0xDCD19AC3337E734AULL, 0x0B7CBDE49781277FULL, 0x15F34F994F60ABACULL, 
            0xE5177891A0ED6DA8ULL, 0x347930A6A41A1134ULL, 0x052C67BC4278783BULL, 0xCF1590B476925987ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseDConstants = {
    0x44875FBB99C69C9AULL,
    0x95530785468A02A5ULL,
    0x550293A4DA95F116ULL,
    0x44875FBB99C69C9AULL,
    0x95530785468A02A5ULL,
    0x550293A4DA95F116ULL,
    0x9F48D33EADAC9D8FULL,
    0xD2D9FA1E06F69D1AULL,
    0xBE,
    0x86,
    0x5F,
    0xB1,
    0x27,
    0x84,
    0x69,
    0xAC
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseESalts = {
    {
        {
            0x97B8CBB26528B3D6ULL, 0x6B6A6B59C0B79CD9ULL, 0x872BB6414378CB4CULL, 0x70C0095AD9ED1B38ULL, 
            0x3C5A8A962DFBF380ULL, 0xF82B14C2B6161330ULL, 0xD2C6241FAEA97BD0ULL, 0x27BDB5BF2D07382EULL, 
            0x028C8E236636352CULL, 0xDADF7277716298A7ULL, 0xB41F92E8D9C67216ULL, 0x92DD814FE4C2097BULL, 
            0xD6DDE3C30F37A1FEULL, 0x4B48BD8817AB086DULL, 0xED22A52780829FFEULL, 0x1BC44066796A6E49ULL, 
            0x37A30F4385ADC8FCULL, 0x62606C9D3A4C8868ULL, 0x6A1A5A74223F0789ULL, 0x72153D1AA76D1340ULL, 
            0xDDC04E3DFB267830ULL, 0xFAEE41DF7CF4252DULL, 0xEBA2F1D61C89CF0FULL, 0x4442E08A4248B114ULL, 
            0xB00F85B5286F263DULL, 0xDDE9344334E7CB6DULL, 0x4618DF9B2033103CULL, 0x91208BE797556D43ULL, 
            0xD62A0B8FE3B2A50AULL, 0xCCB5B387CFE552BCULL, 0x841ABE7D2D7E1AD6ULL, 0x330795771628D948ULL
        },
        {
            0x1CFCFDA2D5224FCCULL, 0x6A0CBE51443ADD3AULL, 0x7680F5D1F2C45123ULL, 0x50AB228CE9B2B180ULL, 
            0x2C3CA7635B7B4AEAULL, 0x1110BEAB3A135C3CULL, 0xB8A77F11F1785EFDULL, 0x7C8266365CF56AEEULL, 
            0x8769287F060A43B0ULL, 0xF9776D40813F2B0CULL, 0x7CBFAC63FB351478ULL, 0x045B8FD7F06402EFULL, 
            0x395B7C9C3F917407ULL, 0xDB9A72AC9B210994ULL, 0x26CE8B3B407EF47CULL, 0x4F357853D9A1A984ULL, 
            0x5224885FFF8FE675ULL, 0xD879E7CA20AE4202ULL, 0x6F280C90EDCAB4C4ULL, 0x8B60A1029737D900ULL, 
            0x063F377AA574100AULL, 0xDA532D3A94E19D11ULL, 0xF89BDF0DC798AE6AULL, 0x28E3FD19A867B574ULL, 
            0x719A8B170C1A6CB4ULL, 0x4B0A88F4ECC90746ULL, 0xA9FB103261E981A5ULL, 0xF5D0C6B71457DC22ULL, 
            0x7101D7DAB9D5407BULL, 0xF60A53DFB7C98108ULL, 0x8E57FAD2C0A5A99EULL, 0x33375A7667E84FFFULL
        },
        {
            0x033158DD555F1F17ULL, 0x5CF62D77F88F4E16ULL, 0xE20710587B21D9EFULL, 0x9CB2BDBBC1263E4EULL, 
            0xC7DF1B465A6E7534ULL, 0x88B06F175E1BA64FULL, 0x8DEE757A65EE472AULL, 0xB830F322EC5F61FAULL, 
            0x1985217E8A366B85ULL, 0x0BBC1AAB9DD25583ULL, 0x6A8B5173D0DE6F9EULL, 0xB07DDB3243C11D7AULL, 
            0xC8D8EF88EF0B18B6ULL, 0x31540055BE1C6E3FULL, 0x1D25D9CE05CAACCCULL, 0x8DBDA15BE404495BULL, 
            0xCD5CEC28337669CEULL, 0x4B7B7346020D4DD8ULL, 0xDCC60FA0E6D627A3ULL, 0xD0875746CD1F6150ULL, 
            0x319D9DCA3BCEBF02ULL, 0x870544E24C817EE7ULL, 0xCDDC5B3C9B44F579ULL, 0x9FC44D1615237D6EULL, 
            0x812B35C20AA92A0FULL, 0x783909085A5ABACCULL, 0x4D7D2F9CDAFE7983ULL, 0x95DE90CB6CC84517ULL, 
            0x3C7613DBB410461FULL, 0x7086F4446BF3A09FULL, 0x96F0147E4E3576E4ULL, 0x738327EEDCF875CDULL
        },
        {
            0x8C036988675ED1A2ULL, 0xCA85F307B473464EULL, 0x3D97AE91C03112C5ULL, 0x2728B4DF10CA45B5ULL, 
            0x6C9F256604F10D37ULL, 0xEB6AACF521C58268ULL, 0x0B5C657AA597E6C3ULL, 0x4FF527D55AE56012ULL, 
            0xE7F6CBD6103418A4ULL, 0x63A6CBECFC7FADA1ULL, 0xC14933F1AD3B6B00ULL, 0x7DE23153107E5F48ULL, 
            0x4AB0477FC56E10C8ULL, 0x673B83DDAEB01CBCULL, 0x62EEF62CE675F9B4ULL, 0xAC2BF4D3F23EB7A3ULL, 
            0xD504E11D219EFF46ULL, 0x7DBC650B3F974A77ULL, 0x01B959B1B642CA27ULL, 0x3192F1415AC4FB3FULL, 
            0xAF2CB010C2124870ULL, 0x3952BAD2052CD75CULL, 0xF80F903D6C66E34AULL, 0x7E921CB372A87A38ULL, 
            0xBA95BD7768FF5531ULL, 0x5A164999A3E3C2F6ULL, 0x7634FECD84A659DAULL, 0x03218D1206B8381FULL, 
            0xFB332B75D9CF3539ULL, 0x25D8BC6CD472D3E4ULL, 0xDE1ADDC7F2955489ULL, 0xE4C5D4443BDB4321ULL
        },
        {
            0xD33BB51A00334919ULL, 0xEC8AFD30A3B89947ULL, 0x232139AB04902ABFULL, 0xD6974CE3E2B26F89ULL, 
            0x90CC7707A313AD9AULL, 0xF15C155AE76430B9ULL, 0xC31E5446FE92B818ULL, 0x30EC2E6E40D1A039ULL, 
            0xDEB803DAB2C70ADEULL, 0xC84C79772C58058AULL, 0x85FDDC26A7E0B29DULL, 0x79865F1DAFDD48C4ULL, 
            0xC328122539BD7EC4ULL, 0xE322A8937F61D1BAULL, 0x273A1E03B4487E21ULL, 0x9A02042631E8EA8BULL, 
            0x8BD0C3B2083F85E5ULL, 0x75B8A823EC125FE1ULL, 0x124F1AFF3E034725ULL, 0x87054E758DAD8DAFULL, 
            0x54F1CC2C846CB40EULL, 0x15C000ED8D958BE5ULL, 0x2265AD9F717F1AD5ULL, 0x6FACF278CA72C298ULL, 
            0xD46803867B72692AULL, 0x8E169F792E073A95ULL, 0x2D748AF0A682C18DULL, 0xCC69ECA772204CF7ULL, 
            0x376EFC734C710592ULL, 0xA7E16306B0771A35ULL, 0x98639826A5D48DDEULL, 0xAD787A3F31EEB3B2ULL
        },
        {
            0xC3267344345112B1ULL, 0x7E58EAA1EFAA742CULL, 0x19DFD035C7E36CFAULL, 0x731E2258BF3D58DEULL, 
            0x8DE9991C15A06E51ULL, 0x62917058831444A7ULL, 0x4AB7DD388755A722ULL, 0x5E2B96C9F2B77935ULL, 
            0xA9497C7412DEE41DULL, 0xD69BE6D609912A67ULL, 0xA2EDE11F55FEE901ULL, 0x10D270E1D6162395ULL, 
            0xC853E9C17741A5B4ULL, 0x47C56D8BE91BBD20ULL, 0xCEDBB80A4B35DB2BULL, 0xA127EC2DFC9717A9ULL, 
            0xD19FE320F53A6E5CULL, 0xE4CF3F63B77F1E4DULL, 0x694AC318F4A24D5EULL, 0x21437D0795874964ULL, 
            0x0AF95FCEB287E792ULL, 0x5B932253AECED74CULL, 0x65983B9998B9A0CFULL, 0x3689E4ECA3A44F48ULL, 
            0x9DDDBBE93BC932CBULL, 0x9A799B8749EA64CCULL, 0xA5BAED1DD1226E39ULL, 0x55B39E583503BCCDULL, 
            0x8F183A0DAD21526CULL, 0x1FD8F8A8186AC168ULL, 0x10E2D4D06CB856C7ULL, 0x0697BECA223D0E57ULL
        }
    },
    {
        {
            0xE7344AF4B81E1429ULL, 0xCE6E54FDABABE82BULL, 0xB4FEFD86B1499BA9ULL, 0x37A3377B4425BD49ULL, 
            0x11854C1CD5553B6DULL, 0x7D4FED5A62166DA4ULL, 0xEF10CF9DD46EEDC7ULL, 0x956FEBFAFB140137ULL, 
            0x6827811A114B6BA3ULL, 0x85946536FCC83657ULL, 0x96C171294250A852ULL, 0xD5A999189CF7D32AULL, 
            0xA89D03A37FDDF861ULL, 0x36140FC4E46FB932ULL, 0x4614D5B6F4997068ULL, 0xA9A3308B0EFF7D73ULL, 
            0x0C26C791EEB6D401ULL, 0xBF3117052D3CCB4EULL, 0xD40223AD45E9E55DULL, 0x7E2CD70ED93B4594ULL, 
            0xABD0B8238FE7E9B0ULL, 0xD39244C2088E9393ULL, 0xC7BB2FDC9E3A368DULL, 0xA739DB1BABA66804ULL, 
            0x6FE67983408679FAULL, 0x5CB824B2CA41F1BAULL, 0x9392ED741B6F7859ULL, 0xFD98CBEE646F1E81ULL, 
            0x7B73CD3C4E4259B9ULL, 0x2373BB983324B29CULL, 0x8353FE106D7CDFF1ULL, 0x5242480F76B956D9ULL
        },
        {
            0xE2052043438AFC85ULL, 0xA8C37B3989656C0CULL, 0x10929C784FF22AACULL, 0xE3CF5F9E8734FAD0ULL, 
            0xF77F1F9787B18C21ULL, 0x2B83B0E2914E85E3ULL, 0xBCE4BF7250EDBC90ULL, 0xA8BD805ABDC67936ULL, 
            0x53E0CA00EBA6C3A1ULL, 0x6A8330CBABA49A5AULL, 0x4BA89A415EC86238ULL, 0xE75DA49BF6A032CAULL, 
            0xE162C67C1A0C48B1ULL, 0xA2EBC1041875D4CDULL, 0xF4DDC2C6773D9BA3ULL, 0xAFC114A06F47EAC0ULL, 
            0x25CFCC6CCDF2808EULL, 0x5449053991DD01F3ULL, 0x9E0C1FE978E17DA1ULL, 0xB7B33FFD9408D688ULL, 
            0x97EFE9960376441BULL, 0xD340F5A600CC2192ULL, 0x6B5DDEE21622D2F1ULL, 0x5410D05DBCE2B5CDULL, 
            0x4F54D209D4F86FA5ULL, 0xE103FF9ED44ADFC6ULL, 0xB88605B3CD855108ULL, 0x6E93A62EEF04F815ULL, 
            0xC296C8E216173DCFULL, 0xAC059A9B5BE105C1ULL, 0x1A523DF137FDBCA6ULL, 0xD95D6CA89BA85E61ULL
        },
        {
            0x8BA87B368EC35A8BULL, 0x807CE669A5C16CFFULL, 0x9CA6A489C77CC54CULL, 0x24CA993D3BA74A44ULL, 
            0x6945E6B7DA112A6DULL, 0x57808E771456C65FULL, 0x16E5C8F0D622AD3EULL, 0x66E56ADF0BC47DB2ULL, 
            0xE2BF5869F57BB419ULL, 0x04A449464681773EULL, 0x60273851C7389432ULL, 0xBE1E19FDC3EC803DULL, 
            0x70595ECC2D958E20ULL, 0xB4EB78D9E68194E2ULL, 0xB87571F566D0F270ULL, 0x85791B9CFBE0AD77ULL, 
            0xE20CE331C5A5FE42ULL, 0x3814597B0D8FFFABULL, 0x45DA7FAF098F2CA3ULL, 0x3B309A72017CF1B6ULL, 
            0x94139E3B9ACE2877ULL, 0xE991D95E14DF8327ULL, 0x147E4E57B1AA049FULL, 0x9FE57B29745674C5ULL, 
            0x1B027F766DBF65A7ULL, 0xDEC6AEB956E4A5EDULL, 0x4E685654E24CE999ULL, 0xC2D0CFE997BD7BB3ULL, 
            0xBD5FE9CC5ED7D94CULL, 0x4C37EC9B10B37C2EULL, 0x90689A389AF0CB11ULL, 0x2B9A60D7387B11F3ULL
        },
        {
            0xD12D650EB8475EEFULL, 0x93ED286D84ECC138ULL, 0x008111E101922BD2ULL, 0x15E5516B3DE4A055ULL, 
            0x4A8752EE5E513442ULL, 0x8EE168A77F69D7B8ULL, 0x24B6152B76E17FA2ULL, 0xD5D38DBFD7CA7D7BULL, 
            0x0B25EE450A7A085EULL, 0x6F0DCABC1E31743CULL, 0xAA48ED6FBA2D6005ULL, 0x98EEB703689D6B1FULL, 
            0xBE89773F967E55CEULL, 0x189770A78B0E3710ULL, 0x397B8953307E2D7CULL, 0xBFD23E7BBE7A44BDULL, 
            0x2ADB21276EC82E0AULL, 0x4A4A30F24AAE86B9ULL, 0x21B2FE97C6B3B2DFULL, 0x9864473A4B73A8D5ULL, 
            0x58A6CB9BEA5E76D9ULL, 0x9488A0DA95FF1AABULL, 0xDDAD6E0ED3D43CEEULL, 0xB9DE743BE76DEF63ULL, 
            0xED3066FD0EB5CFA1ULL, 0x740C568EFE9556FFULL, 0x0B967A3C1DEEFECFULL, 0x50F71B647DC5DFA9ULL, 
            0x492798F72E0E0977ULL, 0x48052F32FDFB41C5ULL, 0x5ED19DE7CD4A7154ULL, 0xEC2067725B99A97AULL
        },
        {
            0xF44599E9DB0675CFULL, 0x84D0BEC82B61C84DULL, 0x07F9B65350D97933ULL, 0x1EE5F6A3A98C9E82ULL, 
            0x4D3A776FBDCF7FFFULL, 0x5CB7954352755ED2ULL, 0x192E822AC146D8AEULL, 0x54A1A40E91AFC512ULL, 
            0x37F4914F0A3C1258ULL, 0xEA86F46510B5F3A3ULL, 0x07C6DD1A42B99993ULL, 0x66C0F506E1ADE2B5ULL, 
            0x6DF029478C6CFBA1ULL, 0xE9204658FFF179C5ULL, 0x033D3FEEB9105C38ULL, 0xC3268A85CD02BF31ULL, 
            0x0A257E59B3750B1AULL, 0xBCC01BFFA21F5D5BULL, 0x2EEA9FB2ABDB9A6DULL, 0x22DB8A842EA1BC38ULL, 
            0x2515114155A39268ULL, 0x7F00B6A58EA11B9BULL, 0xDF4AF69175B59672ULL, 0xC533C1CE8703B932ULL, 
            0x793B6A14B6A659A3ULL, 0xBA0105CE597359C5ULL, 0x217AEC60E8A0C072ULL, 0xA5E3756E92200638ULL, 
            0xB94B86E81F724B73ULL, 0xDAC823F70F8F418CULL, 0x5424F66F2698234CULL, 0x7C1A150EA9ED8455ULL
        },
        {
            0x0A57DA75169099FFULL, 0x95700A031D0AD688ULL, 0x5080983C3D9110BFULL, 0x35B6699A7B5317BEULL, 
            0xAA81D811D001093BULL, 0x89DBEB5130A9B0ADULL, 0x3545CBFC3F2B6A2CULL, 0x2168990D846966FAULL, 
            0x0FAEC978832BA5FFULL, 0x3A5FA18ABAA4675FULL, 0x9EF0C6946879BFFDULL, 0x67F67A4B7AAC76CDULL, 
            0x1E3A621DD091FC1CULL, 0x2CF14D4B02CDE8BBULL, 0x5B9B5BC2127CFD97ULL, 0xC8F82490E33E3645ULL, 
            0x3CE3AD8737533A38ULL, 0x67FC141D6D0BB6F3ULL, 0xC6C2B4834F3AD3B5ULL, 0x8AFBCC69BE26C422ULL, 
            0x4376E499214C3BD8ULL, 0x1F69839CB217BF36ULL, 0x3B83876E88E11ED8ULL, 0x9496EA62D0C10268ULL, 
            0xBFF5883B982CBD86ULL, 0x42E2FEB8A51AD4A6ULL, 0x6A002AEF51CC4EDCULL, 0x3E7C970FA53EDEA2ULL, 
            0x4CD2022CD2E3BF92ULL, 0x5A5192841D514038ULL, 0xE45F9713B1E6707AULL, 0x9C872F1CD8BFED3DULL
        }
    },
    {
        {
            0xC78E1AD951AC9ABEULL, 0x942B81DDCFE6498FULL, 0xF8BE2FA243924985ULL, 0xEF52C92080565B9BULL, 
            0xDF118D76FB18DF02ULL, 0x68F0AFCB6D6AEC64ULL, 0xFC4DEB38EA22A773ULL, 0xCED1401B8E79AD6EULL, 
            0x1C4E884951B19CB8ULL, 0x2AD092D7A44DC041ULL, 0x12D6F64446A6CC6FULL, 0x22C05DC289EABC5AULL, 
            0x17BD2B7C11874ECFULL, 0x5AC7488333A6E2F0ULL, 0x8BA07A3F0EDCFD8BULL, 0xBE3CCC5EDE9C3EFEULL, 
            0xF2D4F9315B1129D7ULL, 0x5579261FDAD02CCCULL, 0x169D72C83962CC9DULL, 0xCA3F144E37F12013ULL, 
            0xBC93FD9B29CA0A94ULL, 0x9B199DCB22114093ULL, 0x8A51F10F3E49B689ULL, 0xC9ED53934AF25C5DULL, 
            0x727DB6ADAFFCA21AULL, 0x92C41060A94FEB2BULL, 0x1395FE21B6272B1CULL, 0xF51BEC7FC561A195ULL, 
            0x41F869EF419E33C6ULL, 0x9698AF2BE4B9BC6FULL, 0x6E8D318D806FB190ULL, 0x772C53E3ECC0B194ULL
        },
        {
            0x8BB934351BA49C46ULL, 0x66234459D9B1B9DAULL, 0x4FE39C6594C4CD79ULL, 0x840BCC9A382ADB8DULL, 
            0x9B25EABFED0AEACCULL, 0x253B92AA818D3EE3ULL, 0x3989EE67924BD50BULL, 0xB72727B9A5F8FC12ULL, 
            0x75E590F4EF922C42ULL, 0xA1EA6DD4C35BC89EULL, 0xD47A4A86EB101E81ULL, 0xA89020544FCC1643ULL, 
            0x92738547317AC6EBULL, 0xA1332315D0988D9DULL, 0x1AF03222F208712BULL, 0xE7C71A114DD2453CULL, 
            0x11DBDA0F2DD477DCULL, 0xFE8342278F1E4F80ULL, 0xF3071900963BFFE4ULL, 0x800FED081F296E34ULL, 
            0x15F76AED6DD4DF4FULL, 0x45910A1BFDDCD274ULL, 0xB154DDB26723D0E6ULL, 0xE4C8EED709A54DEEULL, 
            0xF13F3BF3566618F6ULL, 0xE994DD4CA86C5421ULL, 0x0DB41CAED735C752ULL, 0x2499914AD577D931ULL, 
            0x462D36D022415AD0ULL, 0xB829DEE55E5D8057ULL, 0xF0116E1404EA1433ULL, 0xB384D2862A88F573ULL
        },
        {
            0x9D5766A4AD25DACBULL, 0x6B164550B074B399ULL, 0x4E82588B7A5A096DULL, 0x456DA3D6AD0BC123ULL, 
            0x640E8277CA28C160ULL, 0x2C48B8C935C70AAAULL, 0x7A868578121D722FULL, 0x3D5932464AEC0E16ULL, 
            0x96F21F27B8822CC5ULL, 0xE7DAF030655BFED5ULL, 0x5B1CD2519511FB1DULL, 0x7BA6643B73DED36FULL, 
            0x69DCFC60186FFD4AULL, 0xC3C05D4F98B071D9ULL, 0x569C8F24CF756534ULL, 0xB030919B15B731C5ULL, 
            0xFEC7F0F6EEE8F643ULL, 0x09335384872ACB37ULL, 0xD409C8E9A0977A59ULL, 0xC89D3D974AC6B6ABULL, 
            0x3D554836F604FF7FULL, 0x49E2D0EF147DF847ULL, 0x6E77BF47375230BAULL, 0x55BDCBC8FCFF3404ULL, 
            0x78BDED496B5D7675ULL, 0xF00CDB61AA366A75ULL, 0xD01DAC92B28F3F22ULL, 0x0DFE113E9339A0FEULL, 
            0xDBAA58BFF33864EEULL, 0xC964C554EAE38C55ULL, 0xC8E00E58ED50909FULL, 0xD711055F23077AC9ULL
        },
        {
            0xFD64081054525349ULL, 0x6E80396A2F1F88B6ULL, 0x4CE3A4EA58C4ED70ULL, 0x4416D8994410066CULL, 
            0x6111FAA7FEC80435ULL, 0x5D06883A3614FCBFULL, 0xE299B45078BCB037ULL, 0xA20B4DB18DBD3A3DULL, 
            0x9DA9BD5F60E3D922ULL, 0xBF40C4E88CC665B2ULL, 0x75AC8E2A48DB0051ULL, 0xC7529E4F4A2AB215ULL, 
            0xA6635D798ADBD00DULL, 0xB8D4D73C0E415E89ULL, 0x081736221C55DD82ULL, 0x5EC5DF6C272D6E89ULL, 
            0xBB30FF49656AB824ULL, 0x600B3E69269A2C36ULL, 0xF1E6F22FF76E483BULL, 0xE64B58949CF70C57ULL, 
            0xD0024CF474028F21ULL, 0x64C669D71A52928AULL, 0x089EAA4FAFB514EDULL, 0xED6FB9E6F9DFC47BULL, 
            0x8B3E6C21BAB2B9F5ULL, 0x52CDA800A61C7B39ULL, 0xCEE13C31952B3B1CULL, 0x19FC0391EC460526ULL, 
            0xEDFBC245EBB03E43ULL, 0x4B7F99C87A096705ULL, 0x188B861640CFF16DULL, 0x7D73DB3D0E8707B7ULL
        },
        {
            0x83FF03AA7B3E1379ULL, 0x4234041465C10658ULL, 0xF706D4FAAF203BACULL, 0x24DE8A7689F5538EULL, 
            0x0D30AC0E545CADE7ULL, 0xF7609A6BC36B3C93ULL, 0x93758F6DA8CB915DULL, 0xFA2CD059DD5C3A96ULL, 
            0x074A74FF649D9031ULL, 0x880A7D520A1F1B72ULL, 0x7F7BFFCAFCE325FFULL, 0xFFF73A1890B7D91EULL, 
            0xDF382C2B5476CF2DULL, 0x6FE16C610FA2614DULL, 0x1F32259473ADFAD9ULL, 0x7C569528D6619EB9ULL, 
            0xA085A38359867BB2ULL, 0xBF15A57FDD4EC4CBULL, 0xC26E60975E59629CULL, 0xEBE73BD584178A44ULL, 
            0x15969D0AB36DA594ULL, 0xF44A0AC909CB959BULL, 0xD05B6CC2B6E18FABULL, 0xAFE596AE33B145C8ULL, 
            0x60A0C69AC300D406ULL, 0x8B8448745F3D5606ULL, 0x8FE497B2BC6C145FULL, 0x10F93CD83706215FULL, 
            0xCF54975FE58A355CULL, 0xAB1BDA24A3365914ULL, 0xE46DE8761650B346ULL, 0x8887EA06E08C7958ULL
        },
        {
            0xB26A540168230C34ULL, 0x696A7847D2C8BDE8ULL, 0x16537B66FC79AFEBULL, 0x0D5E733EB7266F83ULL, 
            0xC8D95F9145C8671FULL, 0x7459E49362F24E0AULL, 0x7B9CFC88698952ACULL, 0xFD8C3CDD83D3585CULL, 
            0x8D8373A5177E60FCULL, 0x0389AF6F3C3B8A91ULL, 0x5FFC8546A426ABC7ULL, 0xF478623A530DFEB4ULL, 
            0x124A4B6E710C21FDULL, 0x5E2C52A67692BE08ULL, 0x0189415FE6E18B0EULL, 0x5293188A2E3DED5AULL, 
            0x75E852F8332F7B98ULL, 0x98AC8BDC69F653B2ULL, 0x3DC4DE7BCD4F056BULL, 0xF0389670CBFE46FBULL, 
            0x26139899DBF68D34ULL, 0x4590C2129895534FULL, 0xF7787AE6BFF1CEC9ULL, 0x1B81128CC2B5EED0ULL, 
            0xF3E29728DFAD0200ULL, 0x610528610B4E860AULL, 0xB011B2DD29AA4501ULL, 0xA2AC174AD3C2317FULL, 
            0xE454782E119E5769ULL, 0x746ACC1C1F295D7BULL, 0xB8A62A424CDD8071ULL, 0xC42FAF2F42F7E0CAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseEConstants = {
    0x6BE7DA028264C1C1ULL,
    0x02F044DADA6A2FCBULL,
    0x2DE5825CBAF6B17FULL,
    0x6BE7DA028264C1C1ULL,
    0x02F044DADA6A2FCBULL,
    0x2DE5825CBAF6B17FULL,
    0xA5491EB6E76A1B0FULL,
    0x7DCE17466A65EA36ULL,
    0x49,
    0x22,
    0x1B,
    0x14,
    0x58,
    0xA9,
    0xC5,
    0xFE
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseFSalts = {
    {
        {
            0x705D4A1774396493ULL, 0xAF3E6538D3058764ULL, 0x1277777D1F430147ULL, 0xE4A217BC7587F615ULL, 
            0xE2DE6A3EC8155A43ULL, 0xF80C190F03B8AC1DULL, 0x397988C911BFD97BULL, 0x54097535AF117E81ULL, 
            0x4891E5DC345EB49AULL, 0x0C9AE8666B9F6DB8ULL, 0xA6BDD8C5EEC332AEULL, 0xF35AA021CB71C45FULL, 
            0x50699443CFB33C08ULL, 0x1F6C5387A2F51A29ULL, 0x4098718D67E122DDULL, 0xBC912310FC50ACFAULL, 
            0x3B3A589C2FD51246ULL, 0xDEA37D953B24C88CULL, 0xFBA2459B583505D4ULL, 0xAA5A023CBBCF3BACULL, 
            0xF1C81B729472ADACULL, 0xC509A9D835C3DD27ULL, 0xAE657DC326BF5B42ULL, 0x55D812D02A9D0FD7ULL, 
            0xEA03F38CD74818E1ULL, 0xF125FA352B388409ULL, 0x3FBCA493BC71E76DULL, 0xDF8F1CFDD808C746ULL, 
            0x7F0C412D84FE9BC3ULL, 0xD3BDE94C37DF790FULL, 0x2F6DFE64F0527D98ULL, 0x631B7267B5DE8F80ULL
        },
        {
            0x5085762490613804ULL, 0x6013BDDA4796E686ULL, 0x81773C50E3400DEFULL, 0x3CFF51971ED00A2CULL, 
            0xF46393EFB9D002E9ULL, 0x6411211036F2C53EULL, 0xA4D056AC67460F71ULL, 0xA6868D33C1FE7D69ULL, 
            0xF9C070CE82D2257BULL, 0x7385FFCFD69312E7ULL, 0x1089FAC1EEEDEB0EULL, 0x203D07783BF53FB7ULL, 
            0x5E42FBA494863AD8ULL, 0xEF8EB80501E77B9EULL, 0xC112362BFD1140BCULL, 0xD8A59B3ED2D12D75ULL, 
            0x67FB6FC0EA341C1DULL, 0x0939019BFD9BE25FULL, 0x0199DA32863196E8ULL, 0xE1914AD98515633FULL, 
            0x8C94E6CEDF1A8BC5ULL, 0x24B2AFAAA5B9DE26ULL, 0x90A309174E58AD4BULL, 0x30CBAE5E29CE26F8ULL, 
            0x60F3C4D05434119DULL, 0x69BCF30CD5DCAB43ULL, 0xCA3743CEEF346C3DULL, 0x0FC4C9A2141CC2B8ULL, 
            0x538B27461EDCEF9FULL, 0x86AC38996B17C1B4ULL, 0xDEFC5147B03CCE05ULL, 0x283AB430B98B8F7CULL
        },
        {
            0x28596645B96C32EDULL, 0x48A474998B3C4FAEULL, 0x63AB46A4CCB46E75ULL, 0xF87B4FD782BACE93ULL, 
            0x464C57A7F19B6758ULL, 0x9B76ADCB69032BA6ULL, 0xDE2EF67CADA65D76ULL, 0xF20DCFE14BA6E2CBULL, 
            0x48646C6BC504627CULL, 0x1A6EC1ACA3726E3DULL, 0x1EA734B0FB226F32ULL, 0xD0D16BED3FC81106ULL, 
            0xAA8B0D85E3CFA2C2ULL, 0x91B4EFAC767E30A0ULL, 0x750D64A9E6A2F4FFULL, 0x3CF9BF40E0CC3C19ULL, 
            0xC9EE2DEF9125DF9DULL, 0xE667EE60C85AF464ULL, 0xC1E472A1FBBCE53EULL, 0x036252762B753946ULL, 
            0xCF89BFC5FE4FB077ULL, 0x79C165F95AD0A5ECULL, 0x7C39F024E9EF5731ULL, 0xA0203DA0CB1FA1FAULL, 
            0xEFF944B9E691F643ULL, 0x0FAF7681A29964DDULL, 0xA82DC676E51B3B0AULL, 0x5BBFADB38EC5070FULL, 
            0x10B339A8FB58663BULL, 0x5AAE89AE2D083351ULL, 0x0AB65BB41B7DE2ACULL, 0x71B11DEA8FF0DB9AULL
        },
        {
            0x55E9383AC3F6B532ULL, 0x1C4D6902E746B563ULL, 0x70C1E99ADCA08D00ULL, 0x9F06772DE45CD79AULL, 
            0x17DFAF27B931672AULL, 0x033444452BE24C8AULL, 0x8B243AD99BA0A05BULL, 0x832D8F96D3EB3416ULL, 
            0xCAFA40A3627A5CADULL, 0xD4886D5C7883BD65ULL, 0xF39548CC567EDDFEULL, 0xA9E1264C6F81E02EULL, 
            0x7459B135E1F02B50ULL, 0x6C4A2F115B0C29BBULL, 0x9457415624E1B70CULL, 0x8173A8D4E5A7032FULL, 
            0xE1FB1E39D27EE7C3ULL, 0xE5F0C4FDE58FB410ULL, 0xEE7C82FCD4A1BE02ULL, 0x745A2687E3FC978DULL, 
            0xE757C44E890C1B44ULL, 0x22F8F34060A73804ULL, 0x444A3ED5865762F0ULL, 0x6332ED2DA6C47968ULL, 
            0xE9BE9CC91E6C302FULL, 0x59A9C0150E718AFDULL, 0x65BB7DBDC98A603CULL, 0xAB2FC578C6FE4166ULL, 
            0x7230B39290C0C7EEULL, 0xD3904C413CDF7330ULL, 0xEA40F2018C62B303ULL, 0x9C338ACB3549FBACULL
        },
        {
            0x6354C1B989254370ULL, 0x4408AA46AE58632FULL, 0xE71C3FFE0343CB15ULL, 0x4CB3876CD088006FULL, 
            0x415FBCB28450E791ULL, 0x8F711586D0C0D95FULL, 0x0E4C07D87ED1A822ULL, 0x4F3A581BC9401BF0ULL, 
            0x0705CF16925773A6ULL, 0xE0128FF009780F4EULL, 0xB4C285013F03FA3FULL, 0xBC7C637D540A0DC3ULL, 
            0x40C2B01048A5AA5DULL, 0xF56797BD60272CD8ULL, 0xC682B136DCE3E43CULL, 0x8F3F105125F3B841ULL, 
            0xBFB4DB340E15056AULL, 0x5119E15C7477D242ULL, 0xCE3205EB5A364063ULL, 0x50092174C761FAFBULL, 
            0x7B88E7424A5D9019ULL, 0xF921C6B7A0EC462DULL, 0x898E2997B2762E84ULL, 0xC07800215E9D4343ULL, 
            0xD69CD9151F842596ULL, 0xE93B5AF25986F739ULL, 0x98478F86F8E00DD9ULL, 0xD5E295769B223C94ULL, 
            0xCA6B7A6915C43CE4ULL, 0x2DC4DDB9EF43C279ULL, 0x6732E932C44FB033ULL, 0x5840076B07A1BC41ULL
        },
        {
            0x2611421487C76352ULL, 0xE7AC0BECD5B0DBEBULL, 0x8C381BFADAC0F351ULL, 0xC10EC592BC2B4925ULL, 
            0x5F168716D1C36F88ULL, 0xD10D739625E224BEULL, 0x48E7B0150633F971ULL, 0x2CE0CE67D3E5A707ULL, 
            0xC22F9F67D64CFF21ULL, 0x363A23CACF3A683AULL, 0x8264BC68EA467437ULL, 0x342AC5A8D69AB305ULL, 
            0xDBC78E0FCDBC7050ULL, 0xF22F4657814B7EC9ULL, 0x998B4A39843AFE35ULL, 0xD0EFFF8BE9B8AF4EULL, 
            0x7F46087FBCE88CA9ULL, 0x24D17E38D31DFAB7ULL, 0xE8077AE2F622FD2AULL, 0x4EF8392E2B3E943AULL, 
            0xDFD5F9BCC1638CFDULL, 0x5D12524FAD886EC2ULL, 0x9380C23735DD0B96ULL, 0x9612FBA13D8B744DULL, 
            0xD7B97DA6A409F7DAULL, 0xB79AEF150767A941ULL, 0x596631C9C70BCA1FULL, 0xB27541AFC072FC21ULL, 
            0xBE85CB4D5DE0446EULL, 0x50A23835354A8A68ULL, 0x342F55BA4BFB4B6EULL, 0x9CFF694A7EF6E5AFULL
        }
    },
    {
        {
            0xC1AD858FCBA288F7ULL, 0x9D1F692926731FC7ULL, 0x183264B87DE6E605ULL, 0x3A933FB18FB829EAULL, 
            0x54F6810BC0FAC559ULL, 0x8BFF25FBB0A02E3AULL, 0x4C1C6C3433D10D48ULL, 0xBFDC3B468FAFD211ULL, 
            0xB0169C1D20BF09BCULL, 0x1A7584541393E1FDULL, 0x0F084922E2F65610ULL, 0xDA8B8972DE08DEB8ULL, 
            0x3CBAB62ACEEDB4F6ULL, 0xA918B072A75D9B49ULL, 0x038FB03C48106952ULL, 0xFB3C4FAB9BF260A8ULL, 
            0x8F9C71EEF381D4DAULL, 0xA9CED3A33F0D38ACULL, 0xF7FCA396C049D6C8ULL, 0x5B55321E5E767EA7ULL, 
            0x7957DD30651B9EFFULL, 0xE21F6A693AEA1BA2ULL, 0xD509AD9BF3095860ULL, 0xDE6F6136A566AADAULL, 
            0x8475B56EAECD418AULL, 0x84EF33FF0A65C38FULL, 0x8AC8A2137E193266ULL, 0x7C142229F5EA78B8ULL, 
            0x59EC195DF080AF98ULL, 0xA8D4BFF70DEC4E7CULL, 0xA2A8CB433FB22649ULL, 0x28AF4DE1012F3DD8ULL
        },
        {
            0x7EE653E9EFA5A2C8ULL, 0x2DF636ACAC7A42F0ULL, 0x46C4C5FC28BAAE65ULL, 0x934D1F13BEFB1D4BULL, 
            0xCBE4063B74698376ULL, 0x1534361EEE924F81ULL, 0xBEBFD1294156F353ULL, 0xA7F51FB5D6A1ECFDULL, 
            0xAAAC274B8015A0CBULL, 0x5BCC816DD606C377ULL, 0x94532CB247F63B11ULL, 0x8EBAFCD2BCCFF2ADULL, 
            0xBCBDDAB299CCBDE2ULL, 0x72195EDAF5063981ULL, 0xFDC8AFF829496640ULL, 0x907A6BFC660E4FA7ULL, 
            0x5AF3EA411FCF162AULL, 0x5765A7B38D46E880ULL, 0xB4D4D3512E0206A5ULL, 0xCC933F5D8B0F65D1ULL, 
            0x77BB96973AD91DB4ULL, 0x07A7A10C0D5AB35CULL, 0x2B92E8F38E2F8FA7ULL, 0x000ACC0C9F8CC139ULL, 
            0xD7A0D8151D029F13ULL, 0xA9E1C03B393DC97FULL, 0xB5097AD58D3FF29EULL, 0xE86ADCC0F266036EULL, 
            0x1E88EFCD2CDA5D6EULL, 0xFB2F648CD2B88D2AULL, 0xFB5BCE6B901B041EULL, 0xA3CABE21CCF2B4F1ULL
        },
        {
            0x1C3D7D7592A65987ULL, 0x83A79009D1EF6BEAULL, 0x7734864D15A1AFF8ULL, 0x3C0EC6BFB1F5F488ULL, 
            0x0ED8B01A23E5FC7DULL, 0x0D509B24C4BA6F0FULL, 0x1FDF359AB86F3531ULL, 0x046877C36C8D6F29ULL, 
            0xFCE50980FA0EF826ULL, 0x67D0A231D4870FCEULL, 0xEF199E963FAFEDE1ULL, 0x0A037868E22E233BULL, 
            0x534A08E145D320E1ULL, 0xC14B97CA36E72810ULL, 0x37341E098EA694BDULL, 0x41A92176AFA3D09EULL, 
            0x2E2B7B48CBDFBEF5ULL, 0x09F9B75F7FAF4C32ULL, 0x1F83A442AA008BCAULL, 0xBC0B5AAD81DE1A68ULL, 
            0x3EAA4D33EBD3D1ACULL, 0x67CFEE9BA817007AULL, 0x3D24F24B969F45E7ULL, 0xCAC9D3759DCE9532ULL, 
            0x11AB2383F5C739BDULL, 0xDE20141412579EF4ULL, 0xE7510171166BBEA7ULL, 0x68C8BBF98101E746ULL, 
            0x83094902B0F9A075ULL, 0x9FBA29AFC6AAF6A3ULL, 0x21DB6D5D5BDC12CEULL, 0x466F77C0F286256CULL
        },
        {
            0x48755778F9B4EB16ULL, 0xE91512B742BB1BBFULL, 0x06BBE23E1F871D3EULL, 0xD210E1C19B391D1CULL, 
            0xF84EA2ED142345CDULL, 0x325BE432E41FC9ABULL, 0x59EF78A5CD345074ULL, 0x51687AC4FCCE8D80ULL, 
            0x6770AC184FF8276CULL, 0x9C0E9CCC23447A1DULL, 0x2430F768756EFB3CULL, 0xFD0F7F0480B20367ULL, 
            0x16F897D243E4931AULL, 0xED7E8D45A32B15D2ULL, 0x0E828AA9E0A300F7ULL, 0xBC1DAA04ADDEF662ULL, 
            0x3E0EBFAD7CE15A0CULL, 0xC235B7C083E2C712ULL, 0xEA8245D527CE7CEEULL, 0x6AC12F32B14E47EAULL, 
            0xDE90B7CBD2135E1DULL, 0x9FFE209671D02E7EULL, 0x330DC1782E68E767ULL, 0x469344FFAE549797ULL, 
            0x23450BB5B425D592ULL, 0x871DF8840D6CEE56ULL, 0xF847648C255767DAULL, 0x7B57CFCC35695DE1ULL, 
            0x16A27D9B2F439C18ULL, 0x2ED21B52CCAC5475ULL, 0x4241EB9DCC9F56F7ULL, 0x83BB75FD11ECE109ULL
        },
        {
            0x91501302CFB3BA38ULL, 0x96DE5C5E2DD57612ULL, 0xF24441547F443A29ULL, 0x996B84334B5345DEULL, 
            0xE27BD8F9B4166B24ULL, 0xA83C20DC4883221DULL, 0x3918290E22F9E1C2ULL, 0x15C6466432C16281ULL, 
            0xE951A877DC6E5A02ULL, 0xB41C0FE274A9573BULL, 0x864B6E8B3E9E0CE4ULL, 0xD9798C17414A0FD2ULL, 
            0x728202E0F97A00BDULL, 0x8117416EF161B59AULL, 0xE9FC7BD7F3740754ULL, 0xAAA82062AFC2E39BULL, 
            0xB026EA87E1443592ULL, 0xA14931AA2A7794D6ULL, 0xC44F91F72D67A468ULL, 0xC6457AFFEC6B92CFULL, 
            0x6274E8AE46600B84ULL, 0x7F8904A8E4C1252CULL, 0xABF7F50B20C5AD33ULL, 0x8C4B4518C5145FC7ULL, 
            0xE42EA7021AC0770BULL, 0x11DAFC9C9F99A7A2ULL, 0x2220BFEB8FF7C4EBULL, 0x4F138B6F34C879B7ULL, 
            0xF06878DCBCDE0385ULL, 0x8EF60456AEB16EC0ULL, 0x74E4A349D82008FEULL, 0x6F09810B7354F7CEULL
        },
        {
            0x76091F7FA239C500ULL, 0x0E77F3A0A0E3FD73ULL, 0x0A45C7591E73C71AULL, 0x9DD7D2F618B7D2ABULL, 
            0x7E3FC90999BD1F11ULL, 0xE81E6A8C70FC8532ULL, 0x17638C589A675E90ULL, 0x8D330B26161F3BF7ULL, 
            0x0F6FA08C998A734CULL, 0xFC3EE9B3E0D96E60ULL, 0x614BC2DF4CC69154ULL, 0x1572036B4153B138ULL, 
            0x6E6AEDC9C31E7AFAULL, 0x06957E4ECFFA6354ULL, 0x4021EABCF6A565EBULL, 0x13F12F5D4695E701ULL, 
            0x4B32D8862B07401EULL, 0x5EF1024BF7E15B6DULL, 0xD82D57CB3A330CB3ULL, 0x14A795436F3EAB69ULL, 
            0x902B14590CC430CCULL, 0x09C3BE238B2AF46FULL, 0x16C2D60DAF0740C2ULL, 0xEAA95C2912BCF948ULL, 
            0x057A3FA17F8A0486ULL, 0xDB6BC13D952E83BEULL, 0x7377AEDCFCBA4BC6ULL, 0xD0838AC9A1B970C3ULL, 
            0x3B8C3B5757B3FCC6ULL, 0x3C475996ACA6B265ULL, 0xCBA8CDAFE6D8997CULL, 0xE614010973C70386ULL
        }
    },
    {
        {
            0x7BD1114390274C59ULL, 0xD420428ADED2E70EULL, 0x0F573EBED6DB4630ULL, 0x732BC700A03DBC8EULL, 
            0x993EF4BE160F21B9ULL, 0x7772C0ACC947262BULL, 0x03683FA9AE8A8A2CULL, 0x0FD1F4D93D80E841ULL, 
            0x40BC587961AF9E77ULL, 0xDF3AF6E4FD2B79BDULL, 0xCA5DE60101CC4D6BULL, 0x1CB59B0B4CF6F373ULL, 
            0x83444B645B7C8DCCULL, 0x0258BB4F56085DBBULL, 0x47E0C8FE03B6D382ULL, 0xFE6AA49C3CD9E2F4ULL, 
            0x2B910ED8513BC1BEULL, 0x92ABB0CD00EDF5D5ULL, 0x82F1745D059E5D98ULL, 0x7B8F4D64087623C7ULL, 
            0xF76BF5A3E8CC5516ULL, 0x78FEDC88F02BE83DULL, 0x9BF01527A15EE973ULL, 0x5C37E14AA0FDD4B0ULL, 
            0x0CF69C87D9D777ADULL, 0xF5DA791D38F36D11ULL, 0xEB0D355F9B50420FULL, 0x9BE76A8B9672B16BULL, 
            0x9183F3BA26BCE630ULL, 0xC219B8BD448A3C71ULL, 0x161BA5B15B0F2059ULL, 0xCF94F5B7C47F3469ULL
        },
        {
            0x903112E4BFCE192FULL, 0xB497BA21241FC2ABULL, 0xE30006243A598AB3ULL, 0x2A6D0CCC4048F116ULL, 
            0xBAF75F5B3A9F1758ULL, 0xCBDBD784CE0714CCULL, 0xFCA81A7A73CB7308ULL, 0x27503E6FFAD83D19ULL, 
            0x8F73F2662A3A34E5ULL, 0xC82FDB7EA342BE21ULL, 0x4E9F229321081DB0ULL, 0x432EE54420F884B7ULL, 
            0x478B72E06D4517A4ULL, 0x2FCB12230C2B5317ULL, 0x4F7EEE38C0E5FBF8ULL, 0x3C6A2C7E9E121444ULL, 
            0x63DF5F38466E9066ULL, 0x71AD5354A92B5533ULL, 0xC8AB6B370D278CEBULL, 0x913383351F4B0824ULL, 
            0x4FB42A337D8C051CULL, 0x2A3A446FD14EF22DULL, 0xB885711002AD7B2FULL, 0x60ECF6FB0A465931ULL, 
            0x351D3AF9AE697E33ULL, 0x70330681FD8B191BULL, 0x65D1FC1B488CAD0BULL, 0x075E37C71FC29995ULL, 
            0x25AC3BF29DC1D169ULL, 0xA6404B6CC3957388ULL, 0x2642D98DD701BF27ULL, 0xFF43F814FA00931EULL
        },
        {
            0x55B5D8C687C88CA1ULL, 0x0373F7678209BD96ULL, 0x4A14072A99B8955DULL, 0x71E69BCB923290B4ULL, 
            0x85F51B546261472DULL, 0x7437412EE62216B1ULL, 0xEDA70E6AF5001268ULL, 0x139A5C37E59080C0ULL, 
            0xD933E9F52E7F1230ULL, 0x806A409BA17B47A9ULL, 0x5EB2367BA0E47D04ULL, 0xE7EEDD59498E3CFAULL, 
            0x318AAC07279FD040ULL, 0x9E665E2243A897A2ULL, 0x33BA426DBB338039ULL, 0x6B62926A216BB31DULL, 
            0x98E6BE279E9B93C1ULL, 0x1AF658BDBC67D9EDULL, 0x34AC909B54E133E9ULL, 0x81DF5C26BF48186EULL, 
            0x8156CDCA4D7B89E2ULL, 0xF3D312B302A4895BULL, 0xAD0C1798C1E200B6ULL, 0xAF196A4E426F0266ULL, 
            0x76CE287AD3F36C84ULL, 0x9A1678F666BC3374ULL, 0x32EF672D0845F07DULL, 0x5740A16D0C488530ULL, 
            0x84F394DF7ED67A3AULL, 0xDBBCDE9144D3FCAAULL, 0x489A9F039D8B411FULL, 0x01717BC77B39DB55ULL
        },
        {
            0x29F03EDA62C44D91ULL, 0x40E84F16BA45A1B2ULL, 0xA0F72EAB06412729ULL, 0x255A7A3527369436ULL, 
            0x73AF288C06A97F1DULL, 0x7C811F6D9BE3AEB7ULL, 0xD8EB4F7174DB4F9FULL, 0x9EBC24A590B7FD45ULL, 
            0xE4729CD95768E1CAULL, 0xF27B36E0DCF2A18CULL, 0x20BB4C0A2E0942D8ULL, 0x9CDD5AB9F3074A95ULL, 
            0x857294106D8CA260ULL, 0xB392CB4B0F2E7D29ULL, 0x10AB30A0EA88B1B4ULL, 0x05B87DD0F19545ACULL, 
            0xA85FCFA18CE99E5AULL, 0xAABF84F82D3E9878ULL, 0x0B4974C3591F247AULL, 0xAD9090C220027C65ULL, 
            0x7C14D95A6F5FB591ULL, 0x7E5C55C102A63554ULL, 0xF02C0580AE8E00E0ULL, 0x0105629A73DC0D13ULL, 
            0x696DAD5F6037AA2DULL, 0x99B6A3ED8646478AULL, 0x001DEB318326BF0BULL, 0x527D38249D15CECEULL, 
            0x75B67CAD80A1F403ULL, 0x74B6057E5C5815D6ULL, 0xF34B29D647C43EADULL, 0x6D84F2BF98D1A3C3ULL
        },
        {
            0x062958E6555BD79BULL, 0x56FE7A44B69ED06FULL, 0x93C7BA6E98120226ULL, 0x670D0E05995A502BULL, 
            0xB70AFBC4F8FBC54CULL, 0x9F9BBE8616E3FBE9ULL, 0xA5F37DE9DB76D840ULL, 0xF20093B3DAA9C511ULL, 
            0x2C41885F779F3E18ULL, 0xDA0FCBADA39FE7C6ULL, 0x4146CAB485333C18ULL, 0xBB9D25DC02E28CC6ULL, 
            0x086805356983F216ULL, 0x707A1EBA10467348ULL, 0x5F875CD76FBA976DULL, 0xB32C62DF4A0EC716ULL, 
            0x1CC5F0B37731F1BBULL, 0xDE8A5B8AFA3D532EULL, 0x7B1DE75D502639C0ULL, 0xDFD9091F3C75C0D7ULL, 
            0x837B256B4C731397ULL, 0xB1BD51357E7456EDULL, 0x082432D7CB1222C0ULL, 0xF1FB99EFA9368E29ULL, 
            0xD5905BC825375AEFULL, 0xC2EF58EE44557FC9ULL, 0xB763BE08AA772E1EULL, 0x6936F8F0193665B9ULL, 
            0xE1CF7676D05323E3ULL, 0xFF14849D27D07686ULL, 0xD4A0B1D8015C5A6FULL, 0xAEBB0B086DF69AD9ULL
        },
        {
            0x302664AF1F2D00D9ULL, 0xA2EA076F92384A22ULL, 0x8FFD3776C5B93F95ULL, 0x7359998D4BF08320ULL, 
            0xA4E59CE1DBC2D805ULL, 0x559BB6F5C81D951DULL, 0xE636738554EEF455ULL, 0x6F9A83BD08BCAD12ULL, 
            0x1F25A70BB0B535B9ULL, 0x673D58C9B2C24B1AULL, 0xA4343BA90A44EDA9ULL, 0xCB64E1CF53AF74F8ULL, 
            0x23B28F0EA760F886ULL, 0xD72EF0F82912802EULL, 0x8F5E353C32E6C37AULL, 0x89F9428701782887ULL, 
            0xB369646DC175F9E4ULL, 0xF1EFCE5E5D710526ULL, 0x9FE495298EF56E47ULL, 0x730C84B5325C6370ULL, 
            0x9441489617F6E112ULL, 0xA4717745B357A2A4ULL, 0xF48CE77C91597B5BULL, 0x572183F30C4B1093ULL, 
            0xF8945700CDD3EEE2ULL, 0xF64D19E432F5A08CULL, 0x378B283B5ADDE6E7ULL, 0xC5AA62A29A7E5469ULL, 
            0x03C14E5874402424ULL, 0xC412352CD51D68ECULL, 0x7581513FA872FC39ULL, 0x775FECEEFEBD56D8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseFConstants = {
    0x235512A0B9F0AC31ULL,
    0xB8474225C424C359ULL,
    0xFC3C32733316059DULL,
    0x235512A0B9F0AC31ULL,
    0xB8474225C424C359ULL,
    0xFC3C32733316059DULL,
    0xB7E7638D53BE6567ULL,
    0x1B073F1901DE807DULL,
    0x71,
    0xE3,
    0x49,
    0xC0,
    0x41,
    0x15,
    0x5B,
    0xC3
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseGSalts = {
    {
        {
            0xDB65F758CF6FC686ULL, 0xA75291174BC91D0CULL, 0x8500C7BF8E71E86CULL, 0x1A4BBAF4DE180BB5ULL, 
            0xDDF05DF967ACCCD2ULL, 0xEDFD9C435C0BCE25ULL, 0x7134A160C4FBDDE5ULL, 0x8C72262C94D6E1A3ULL, 
            0xAFDD1AF35F1AD039ULL, 0x42E2792298E5A5C8ULL, 0x9A96106CB4F08E45ULL, 0xD4C967D3934CB9F2ULL, 
            0xE87B40BD54A4A727ULL, 0x2B28A3A558A79149ULL, 0xBD0FB909A237AE67ULL, 0x88C579203F573A94ULL, 
            0x72A7E4E162602A5EULL, 0x00DA72504E38E272ULL, 0x317F0BD8176A80A2ULL, 0x51D99BF92C403B61ULL, 
            0x265C101636375B57ULL, 0x5B0D33F14F69A65EULL, 0x67318DD123BECF40ULL, 0x26AB1A402D9106AAULL, 
            0xDE9BB4172A3943D9ULL, 0xF682F87DDF64056EULL, 0x73EFD4D93E9747D8ULL, 0x366A3B7B14E099B7ULL, 
            0xC90EDEC0111E3281ULL, 0x330E984D6DF2E1B3ULL, 0x5DAA5AE052BAF472ULL, 0xEB7F84C1C05B9F2CULL
        },
        {
            0xE5D1329504152148ULL, 0x3E29A5B38A13825DULL, 0x37F738D1E8415EA9ULL, 0xE717BF5A68F63DF0ULL, 
            0xE778698EF0CEC877ULL, 0x8A911488B356A82DULL, 0x5E659C9418310B52ULL, 0x7FDAC9C85C435FE3ULL, 
            0x08100AC43F2FEF96ULL, 0xA2E051A93DE79081ULL, 0x5147A40249495367ULL, 0x970DE1E611935A78ULL, 
            0x2051377D1B80357BULL, 0x336EBDAE21C285D9ULL, 0xF75357FB2FE2E54FULL, 0x605147A97629E86AULL, 
            0x09693BE64C8CBBB1ULL, 0x6825BB14D75A004DULL, 0x85BE7DD711610703ULL, 0x4BB65682311E6B99ULL, 
            0x75004CBB2AFC4B23ULL, 0xBA93246F912DE9D5ULL, 0x08D2B659C4BDA3C5ULL, 0xE86815676DD43B1FULL, 
            0x2406FF02C03ABC3FULL, 0x705081934C4F9618ULL, 0x7510D7EF8B2D3EA5ULL, 0xA5C67BEC440DE14DULL, 
            0xDED05333758DAF4BULL, 0xF9FA9C6439EA64C3ULL, 0x211CF8A31DDC9B20ULL, 0xE4B457965D4FB532ULL
        },
        {
            0x4BA41E0E38ECADF8ULL, 0xC6468EF8F909AEA5ULL, 0x680ABC10D3E1051BULL, 0x4D8486C3F1B8CC87ULL, 
            0xBB9DA6959280FEA8ULL, 0x78A27AC7A5E38B03ULL, 0x686C756DF4339793ULL, 0xB091E7FA86E6873BULL, 
            0x6B917B259DFBD063ULL, 0x2E37C0A6C9D6F905ULL, 0xB0753E5E115404A2ULL, 0xB801234B2F53D692ULL, 
            0x1BA34155996C36B9ULL, 0xA7F9B5F1BC144A11ULL, 0x9979AF76688B187CULL, 0x23C58CF1BF84CEBFULL, 
            0xDDDD4B1AF3A77229ULL, 0x0BEECDD406B3D0B1ULL, 0x72E47C842247139BULL, 0x455E66978912D9A1ULL, 
            0x99A2A30C0B7DCF6DULL, 0xBBE13E37FAE3AC2FULL, 0xABD4CCE8CFB4870DULL, 0xDC9090DAF2B4533AULL, 
            0xE52A2CE2C52FFBB1ULL, 0x64457E1DD7CCAD79ULL, 0xCDA74D81CB546045ULL, 0xBDFA2EE41D283C46ULL, 
            0xB5A33A3CF17A91B8ULL, 0x603102B3CB13A0B1ULL, 0x753E113F57077949ULL, 0x6EE4E1D9DF36EDF2ULL
        },
        {
            0x8A2EB5E199AB0034ULL, 0x6A91B92E6AD800C1ULL, 0x86447B94242082DBULL, 0x62BE1257D85E8CC9ULL, 
            0x5AAFE3220B181D4DULL, 0xFC4FAEA3032B4AB8ULL, 0xCC84F819ECF9D8ADULL, 0xBD6FF434071B90A8ULL, 
            0x6DF16FC812D1A818ULL, 0xF22BA6C2C9CE5229ULL, 0x0C08F3C1174A0530ULL, 0xC03E50443F79E672ULL, 
            0x126997F55B6A6B99ULL, 0xA02E1F1B76E666D0ULL, 0x9618AE7A1D8A9B0CULL, 0x079B2BFC3AEF93A8ULL, 
            0x2F172B0C46581521ULL, 0x28768B0C67C77692ULL, 0x4C0BD5B6D848E1CBULL, 0x58FC18F44FE9E2D1ULL, 
            0x6695F8C2D47B143DULL, 0xE2B9973A64C60DB4ULL, 0xD05A47CA772345DEULL, 0x2FD1A5FCB7E2BBA0ULL, 
            0x9D8D291B183B614AULL, 0xE358C3B2899AF60DULL, 0x8AAA5C2C29690BCDULL, 0xC02A70587CC50A40ULL, 
            0xB2765736EF37BF72ULL, 0x15E21A73D0DABBC0ULL, 0xB7CEA0DBC96B5314ULL, 0x5878A781B430D412ULL
        },
        {
            0x65892A99EF8D5EE3ULL, 0x0975A309C6CEF610ULL, 0x63F48E16984F584DULL, 0x090DBDCBF2B64F8FULL, 
            0x9D152896CEA2DD9BULL, 0xCF866B7ADF798225ULL, 0x9A765D7C01AA3125ULL, 0x78B8E77CCDAFECC5ULL, 
            0xB8312DC53179B86EULL, 0x2A006DF89C9B68ACULL, 0x31B4994DA554E250ULL, 0xFD8F12B348C6643FULL, 
            0x66F61AFF636B28C2ULL, 0xCC8982A24FC6C7E9ULL, 0x3B7766712CA9DCF7ULL, 0xC88D31177B4645B0ULL, 
            0x13FC93E7B39AD7ACULL, 0xAA2D3B3DF9D95358ULL, 0xF3D521C4371218C2ULL, 0x4B907051C143D3CCULL, 
            0xB81ACC683B114C31ULL, 0x75E5D2BC397DFD77ULL, 0xE1B38E0E29867BB0ULL, 0xD478057DDBA8D6F3ULL, 
            0xE5BB2FE2D3DF2441ULL, 0x7994E4AE948103EDULL, 0x6CCE24B915D2CB33ULL, 0xAE42D0A854D12E51ULL, 
            0xD9945178766C3150ULL, 0x02310BDCE396D48EULL, 0xAF4B78504F9C7B09ULL, 0xBBCBB173C6A32CD5ULL
        },
        {
            0x5D336DC0AFA7FE22ULL, 0x2CDEED353F680036ULL, 0x20452F304FFD0F61ULL, 0xCA701A50A638ED5EULL, 
            0xC54B6F71388FABD1ULL, 0xEAAF1FC68E57FC53ULL, 0x6AB2BA1C870B6D60ULL, 0x93BCAA668C058F55ULL, 
            0x4B0B01754EF7A459ULL, 0xE16CB5ECE736D5E1ULL, 0xD58616837C3E3B7EULL, 0xCE3ADD29347F8B34ULL, 
            0x11F7B5C2A84F108DULL, 0x4AFA09E80419173AULL, 0x649D70EEEF1C85A8ULL, 0x76A9C915879B7935ULL, 
            0x4CD747E36F160D5EULL, 0xC385878C77F6BA65ULL, 0x559946BA41E1BE6FULL, 0x5B632E2A9F80E674ULL, 
            0x200C8A89B225B285ULL, 0x0A1ED684B35742F1ULL, 0xDD856902981B2EAEULL, 0x99B8F061A02DE839ULL, 
            0x89469E3C200611C0ULL, 0x7917273F7B865A99ULL, 0xB1C714EE4E966A8DULL, 0x93D9782E78F125B5ULL, 
            0xC185958B4DD60A4EULL, 0x892DB5C2CD9A05A8ULL, 0xF0AC15B462D4A2B6ULL, 0xEBCB4AF72EFCA3B5ULL
        }
    },
    {
        {
            0x615DD7210D79E790ULL, 0x85EE2B863DCD3722ULL, 0x6E79A69015C76111ULL, 0x8C05F4D28DF89650ULL, 
            0xE5F0A6C3F7A3AEA1ULL, 0x8962B7B2EA5C018DULL, 0xD8BA24587663B922ULL, 0x98C5824AE8A98851ULL, 
            0x1153450C2C7E9BA4ULL, 0xF22B081007DB9962ULL, 0x967C4E5DCA2B01E8ULL, 0x6CA2A65D73E9CDA7ULL, 
            0xB2C761FF1697762CULL, 0x5C21103704781148ULL, 0xA74485AD50E27D60ULL, 0xEF4227E4076C957CULL, 
            0x9125ADAC7276D57EULL, 0xBFA92AD4A0D9B76DULL, 0xEEEE1BFBD71268EFULL, 0x7032688EBD3FA7CDULL, 
            0x136CE98A7E62361CULL, 0xF8A15C70CAEAF5C6ULL, 0x510F7F881D9F449EULL, 0x77F46C6EEF1DDD14ULL, 
            0x6F36BA98A2EEB399ULL, 0x05C0C330026AC6E2ULL, 0x2120534A51045593ULL, 0x23BF029375DD7CFCULL, 
            0x98E8E2B3DC8EE570ULL, 0xC73F9AC94991AF4CULL, 0xF4C4333E47DF28E2ULL, 0x35D6826F3A0E7C5CULL
        },
        {
            0xC932202FC5EB4703ULL, 0xAFF9FEB2639B9E28ULL, 0x518C60D8F1730FABULL, 0x33C44D4B5AB2070CULL, 
            0xFB7D28CB7C2617A7ULL, 0x95C739D602B01027ULL, 0xD389EBEA6FE6E180ULL, 0xA123F2D25313F1D0ULL, 
            0x0FF2DC287EEDC614ULL, 0x906C8B0D6A589F2AULL, 0x719EC8AF20A9DCE0ULL, 0xCDE9D33CB461A196ULL, 
            0x73126722754210C8ULL, 0xD4DD83DB7BAD078DULL, 0xD18E7EFB301D7A7DULL, 0x21DDA8BF9B18B1BAULL, 
            0x49031C9D98D79F49ULL, 0x0412443B0C37C002ULL, 0xF47C3B9D32D94F5DULL, 0xCCADD8A6F5AD193EULL, 
            0x58B64DEDD09CFBB1ULL, 0xF33AFFD437A323ADULL, 0xDF62E3272FEB313AULL, 0x772FA943414BA083ULL, 
            0xACF42F1DFE82E4E9ULL, 0x64A798DF7264EB24ULL, 0x971A8B8C117510F8ULL, 0x3CDB1D7293B04A46ULL, 
            0xB6970470D667A1B8ULL, 0x5C88EB9F5325956EULL, 0x9BB1F50AA6E3D05DULL, 0x31A45357F502412BULL
        },
        {
            0xF37448DBAEB50647ULL, 0x4137A1A2D642EA4EULL, 0xB142B1CEE7844C33ULL, 0x18BA83E4D145015FULL, 
            0x3267C46DA514F15FULL, 0x365B40F731369964ULL, 0x167166D9732015D3ULL, 0xF9D3EDC52EA60B62ULL, 
            0x4CC68217B9297587ULL, 0xDB86A8270F209AE3ULL, 0x44EC003161A7BB9DULL, 0xD136719AF6C0B3EFULL, 
            0x7E87E7A2D607B1B3ULL, 0x81C0A7A8CF0A27D5ULL, 0x7963C9945B40DB1FULL, 0xCD786E3899F9BFF7ULL, 
            0x407969217D02D9B5ULL, 0x478A89BD34813DF9ULL, 0xAD6CB50417895F12ULL, 0x45DE115642B76261ULL, 
            0xD17A4874965C48E2ULL, 0x012BAE5AF0A0F307ULL, 0x236D1B28C91912A9ULL, 0xB10DDE83FAF4A92EULL, 
            0x35CCDD931C460A78ULL, 0xFB7F5AEBFFE2C30DULL, 0xC924CDEAE1DAD900ULL, 0xE16B26E4592ADB52ULL, 
            0x551A2A94AE9D636DULL, 0x1C084D28E94AE1F1ULL, 0x188473A27CC73D42ULL, 0x15079E52A5B2E574ULL
        },
        {
            0x30C54D4ED7280715ULL, 0x29E4F3ED1250DCDDULL, 0x8E554A911528BDD1ULL, 0xA1A7D9F5AE0C0713ULL, 
            0xDECD907D2F68DCCAULL, 0x2080148BBBC4E13FULL, 0xE3BF37AA51E96618ULL, 0x17DC81286029060BULL, 
            0x7996D65EFD371DADULL, 0xBC8D7F8C3CF43568ULL, 0xF3B2EF1C8C797A63ULL, 0xC20F97A613B46C97ULL, 
            0xDC7436B16DBD8DCBULL, 0xC5A1270D0930D541ULL, 0xED8B70006ED52F4FULL, 0x24A2EDDAF76DFEC3ULL, 
            0xE5613D3A3B9E4406ULL, 0x72F6544132828926ULL, 0xD4AD0255FD136220ULL, 0xBA4081A8D8F41BDCULL, 
            0x46F46675A7DBA79AULL, 0x05A51A2723C2DE4EULL, 0xEF31273B09A23FD9ULL, 0x1209F34917725128ULL, 
            0xBD9A3D827300E929ULL, 0xE77B447EEC045AE0ULL, 0x5486EC103AE61BCBULL, 0xDBC13F5D22A4B2CEULL, 
            0x26FC7C0EA8F918B3ULL, 0xFA1481B125583FF1ULL, 0xBD8671B3ACF20479ULL, 0x1EFB071136B0FF60ULL
        },
        {
            0x80AAF133ADD5A808ULL, 0x9B0DA20A1D3B1090ULL, 0x65213EBAEB35E8CDULL, 0xE5330510B3B3948CULL, 
            0xD9155CBA45F7FF14ULL, 0x279CAFE9B142AA5DULL, 0xF360E7FFE77FE285ULL, 0x301EBAD32339060CULL, 
            0xFCBC7F61550A0D65ULL, 0x9D81B9B9F97D23B4ULL, 0xBF74EC5D1E4092D7ULL, 0x2EFE06679D4264D7ULL, 
            0x0FEE330E87253D9FULL, 0x30CB41D7448D1551ULL, 0x65198BD8B893090FULL, 0xBB77037E71E463FAULL, 
            0xFD4C7A4F8F49CEDBULL, 0x1FE8770A1B349CC2ULL, 0xB88E902DA13BEC5FULL, 0x010E498B8CA0B33CULL, 
            0xDFA4A8BC49400D21ULL, 0x1882A8FE259A66ACULL, 0xD8807D68245716B7ULL, 0xB4F2F126519F3E4DULL, 
            0xEF9AEB070B04F2FBULL, 0x2A23C6FE3E818663ULL, 0x140D63E4B6C6BE74ULL, 0xE21FA786C793450DULL, 
            0x67213890277F1B35ULL, 0x36868ADA83248A68ULL, 0xCA7024BA4E699318ULL, 0xAFCC45CDEBD7525DULL
        },
        {
            0x1EF29DC772E1F2F7ULL, 0xDDEA50598D582212ULL, 0x1C278EA44289A610ULL, 0xC5815128FBCF99A4ULL, 
            0xB636D20FF02891B5ULL, 0xAE62774B0F80DF0BULL, 0x58000962D2120DE7ULL, 0x79A416EB8B27F4AAULL, 
            0xE54CD55BEF6461DCULL, 0x3D16C808AADB8418ULL, 0x3AA4A3CE36130121ULL, 0x76DB583041DC448DULL, 
            0xFF30EB5CE76BF038ULL, 0x8ACEF4E5676A6A9CULL, 0x039F38D7E5DFD589ULL, 0xE8F6507BA9FFE5E6ULL, 
            0x798CD7716B8E84E1ULL, 0x07AA653D0E45E840ULL, 0x9AC1AF2689B94235ULL, 0xA6E3419F3A69AAA0ULL, 
            0xC489F6FBF982546CULL, 0xDF72749CFA84787DULL, 0x3F5E8ED6B588C096ULL, 0xA7C9CDCF9617FFC7ULL, 
            0xA3D1A4E50C989032ULL, 0x6A446BE569497473ULL, 0x8A65A07D4E9BF30AULL, 0x02795FFB52834EE4ULL, 
            0x2C86D33BF3966DC0ULL, 0xFDBCAE38D7F40593ULL, 0x1DC1BB778FA68A6CULL, 0xB809286EB52334B2ULL
        }
    },
    {
        {
            0xD32B5F0D825EA2B4ULL, 0xD948AC447243EAF1ULL, 0xBDF941116A4F91CEULL, 0xF713F060611BE412ULL, 
            0xC695B0F5835B6599ULL, 0xB2EC364FE0B29728ULL, 0x7BA178F2ADB755E4ULL, 0xA250458A5143E027ULL, 
            0x8547922745C5D978ULL, 0xA83AD3DD07242257ULL, 0x3ADF95310892B628ULL, 0x246916494A0CFBC9ULL, 
            0x7DB3F43D900F4540ULL, 0xC222012E572D613AULL, 0x6971EF8B71914D75ULL, 0x10B4795915399423ULL, 
            0xE0467F823E5BA3CDULL, 0xCA98D075B5B6AE11ULL, 0x16B9CAF956B830EFULL, 0x997ED029392849EAULL, 
            0xF199760173A6E8F8ULL, 0x92F38478A7BE8A9DULL, 0x5FEFC9296A223289ULL, 0x8C344FCC09139F3DULL, 
            0xD4ECD4E440AD9044ULL, 0xFF0E67DB83BF12E5ULL, 0xAE4762795F109760ULL, 0x1BFD49EB6C114513ULL, 
            0xBAED220124D85932ULL, 0x89B78C88565147DCULL, 0x6687CB4D612C4E11ULL, 0xF3539A3848B5882CULL
        },
        {
            0xD2F0EFFEFAF7B30DULL, 0x4BEA04D378BBD4B1ULL, 0xFD12565793554D24ULL, 0x32C6F0AD55DD5496ULL, 
            0xE9CC6B0DAC110022ULL, 0x7508E4B95B64DBB5ULL, 0x62C543614D8172E6ULL, 0xD6B3436458D5C1E0ULL, 
            0x626B58836D05D219ULL, 0xBC86C1BC8AB249DCULL, 0x3EAC9FB22520FC93ULL, 0xA84FCE9E19B0FEB5ULL, 
            0xD05C09474D13B24BULL, 0x0B1533086EF97234ULL, 0x5BB800512CE98922ULL, 0xBEF93CA63EE1E801ULL, 
            0x2FE06E7A26F3EE4AULL, 0xEAC0BF57C06B90CEULL, 0x1591504A047458C8ULL, 0xFC37CBDA9C4172A3ULL, 
            0xA555147DCE437861ULL, 0x5672A5CA2B6ECA8FULL, 0x1B3495A7AA226EADULL, 0xA8002DABFCD0D0E5ULL, 
            0x3C1A540DBC78316FULL, 0x9E27B31F5BB21F3BULL, 0xD26A081315002091ULL, 0x5F94961DFE6C084CULL, 
            0x10F8080329D0809BULL, 0x9283117062A6A861ULL, 0xCCED632E383F94EFULL, 0xC94201739DA0D5B0ULL
        },
        {
            0xE5C1D4A9DFCE6511ULL, 0x8BE2A635C9DD1CEDULL, 0x3E3E2444B9E98D24ULL, 0xC906744C4F705C26ULL, 
            0x20FC17D835BB24DEULL, 0x8B82D1C11456CD41ULL, 0x29DA4280189BE1BBULL, 0x466160EC0D1209E2ULL, 
            0x5F5A0D876D7EFF28ULL, 0x4180FCF5D2CEEAEAULL, 0x59E2F5A21099C42BULL, 0xDBEF87748BD23923ULL, 
            0xEF9F75C215159C9FULL, 0x4E7D2D493246711DULL, 0x41C979CD3D399A94ULL, 0xECEC4373600317AFULL, 
            0xF82568FFAC3EC4EEULL, 0x15AC99943A670DEBULL, 0x20E9DB4E0CD1942CULL, 0x2D34453CA0E492B9ULL, 
            0x4FDD83086BD3F92EULL, 0x05B27B97C59B966BULL, 0xB566461A38613ED6ULL, 0xF7972579BADC27D5ULL, 
            0xAE6AFB83B817CA15ULL, 0x91E47B102436724DULL, 0x1118E05A3D2325E0ULL, 0xC6DFE99511C896A3ULL, 
            0xBCE0FF2E5D3A104FULL, 0x29AC34B331A3EC43ULL, 0x9476A3B3BDD3BC49ULL, 0x79081EBAEB653157ULL
        },
        {
            0x336B7F20AD91291EULL, 0x82EBF8D1E17B652AULL, 0xCA0A56303D7D3684ULL, 0xACE3A43122B60CEDULL, 
            0x7D902459F0827F8FULL, 0xEF051B074D279D0AULL, 0xF7C12965CE69533AULL, 0x2F95C68E66AEA0CCULL, 
            0xC4ED604646F72570ULL, 0x85FFB74FF2C8A533ULL, 0x32FE105D2B82AF1AULL, 0x02A95660ACDEBD95ULL, 
            0xA8F6674DD69D5666ULL, 0xA629050ACA2E8243ULL, 0x01A32E0072FC8B46ULL, 0x6942D17D61D2B10CULL, 
            0x2F19D0D3A2691E2EULL, 0x92742FBBAD5151DDULL, 0x98BCB475F6A9C3E9ULL, 0x51B63725E2DB00B0ULL, 
            0xD4EB3969950AA8EBULL, 0xC3C6DE02F5B207AFULL, 0x55400C801E13A8FFULL, 0xBD1A850C943B6B15ULL, 
            0xC4B30DB305C10E2FULL, 0x3438B9D9AE51751DULL, 0x474E4BEFFB038EDCULL, 0xB9A93433E506296EULL, 
            0x0A18EAC2E78BFE01ULL, 0x8291E5D016A4F68CULL, 0x062A4F72CE3CFD26ULL, 0xD5CAC1030C2459A7ULL
        },
        {
            0x7D519404D4C945F5ULL, 0xFA5BC387C473CE23ULL, 0xA48900931A8E9668ULL, 0x8158B7AFC57F8456ULL, 
            0x77F51E68037E4D2EULL, 0xF56CADD39C08A09FULL, 0xB91A042AF72AD99CULL, 0x836E11D525C5BC92ULL, 
            0xB8289A6E62A26CCAULL, 0x02B54D77D404590DULL, 0x3A202272A64B61A0ULL, 0x39F78F05A1F0D4C9ULL, 
            0xFB98B5EE85783AB8ULL, 0x97FD2F3688CFDCF2ULL, 0xEA2BE9986C7E17F1ULL, 0xA1E8C2BBE88F4F92ULL, 
            0x47BBBB8916BE1971ULL, 0x071C9BB11912ED9DULL, 0x46EB0ABB1772D507ULL, 0xF83DF3B85590528DULL, 
            0x80A26F469B82DBE2ULL, 0x6316D7BDDC6F554CULL, 0xA9586B06A07F565DULL, 0x6325BF6BF2061731ULL, 
            0xC5B9733EA8CBEEBAULL, 0x833C63DE5D96FB4BULL, 0x328FFC46E6CA9ABEULL, 0x222D44B7E1104002ULL, 
            0xAC6B007918B6CC44ULL, 0xAC20F6EF00C0936FULL, 0xE6E9C974D47FF19AULL, 0x87771E8962BDFCE4ULL
        },
        {
            0x6E5DDC16AC870B40ULL, 0x9140FAE7FA582CBBULL, 0xA22AEFE787DB08A0ULL, 0x1429DDFD216E8432ULL, 
            0xFF64CAA5C61D43E3ULL, 0xBDB65873892B8091ULL, 0x5958973F0AE8C201ULL, 0x28BCE6D77D3C8890ULL, 
            0xA6A5EBA96840D663ULL, 0x98B9F9BF189250A9ULL, 0x28072FC5E8AD9C92ULL, 0xB79895EF99CB0418ULL, 
            0xB68BB9EF8A4718F2ULL, 0xBB7B5EDCD417CAE7ULL, 0x5E4B2338DB4B8AC7ULL, 0x515A33B735CFABBBULL, 
            0x2A2DF4C193EF64D8ULL, 0x4F2B2F1D9298EE58ULL, 0xA4F7E2840CBE1ED9ULL, 0xC31D3E7D7143BAEFULL, 
            0xEED1218FDE874A82ULL, 0x1F0DDE581F8105FFULL, 0xBD41998510E4B04EULL, 0x7CC9919E77CEE462ULL, 
            0x05C74F0E9CD9300CULL, 0x0A25F897AEA642F0ULL, 0x280F9F206E04E73AULL, 0x6B92E9E1E817BEA6ULL, 
            0x06904AFB7BE3BA25ULL, 0x882095D818CB2A83ULL, 0x738C467F91A76FB6ULL, 0x78389C156DE2FF38ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseGConstants = {
    0xD5FDB6A29D3AC4A6ULL,
    0x47E55493FAADC014ULL,
    0xF3E2C5008ABE719EULL,
    0xD5FDB6A29D3AC4A6ULL,
    0x47E55493FAADC014ULL,
    0xF3E2C5008ABE719EULL,
    0xFA25DAA7A20A32C3ULL,
    0x9F75BE214B4744F0ULL,
    0x99,
    0x90,
    0x78,
    0x29,
    0xD9,
    0x39,
    0xF4,
    0xC5
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseHSalts = {
    {
        {
            0xEEF432EEF3C8F3B3ULL, 0x88288A4B8A938EE0ULL, 0x54E97BC3645FEA2FULL, 0xF92FE13DC7B8A855ULL, 
            0x71DE0BDE614C647BULL, 0x323F5E311F5A8C72ULL, 0xC19BB6F1565B6E29ULL, 0x5E70EC78878E8F8EULL, 
            0xB6783B5B04C18F52ULL, 0x9599B424D90C9B84ULL, 0x88B4EEE2C92CC677ULL, 0x1E2AC74C8DF64FA1ULL, 
            0xD0EF541737B9399DULL, 0xD90FC6BDE924F67CULL, 0x188BCC676FB7E7D0ULL, 0x323721AE4B08A1B6ULL, 
            0x853648D5F323B019ULL, 0xDC8D19BFAAE7E7AEULL, 0x2B325E881F99D8C8ULL, 0x28437A412BA4B53DULL, 
            0x710A55B07366E2E0ULL, 0x7B2A7A66F6034A30ULL, 0xE1EA6273174DAE91ULL, 0x5817AF53996BA524ULL, 
            0xC9698AD7D3248CC7ULL, 0x5D9765E5622BBE2EULL, 0xEBBD0552C2343458ULL, 0x09746E1F5EE0C19BULL, 
            0x32EAAE51560FCE93ULL, 0x24BC5B6186EB448EULL, 0x517948EAB7150DC1ULL, 0x260E3C1F164BCEB6ULL
        },
        {
            0x3719CC72E803761AULL, 0x9BF16C9608C40FB1ULL, 0x2791105D90CF7F66ULL, 0xE6D10216D44135E0ULL, 
            0xB2ED280470CAB712ULL, 0xD6394D64D140E3FFULL, 0xC17754E0D2BF0F7FULL, 0xF8A679E67DB25376ULL, 
            0x5F9B9AE5AD9E2E5BULL, 0x98F1942642849324ULL, 0x6D925E08D393FD3FULL, 0xA19C675E67F7756BULL, 
            0x2CFAFFBB3D9048ABULL, 0x7C960BD8DA67311AULL, 0xBE0AC7AE592E74A2ULL, 0x0BE4E52C72205129ULL, 
            0x86AB2F1F25E41179ULL, 0x493908CEA2B29ABFULL, 0x5FD4F68FD4934466ULL, 0x011C69A040E45BE7ULL, 
            0xEE5E930F61754E34ULL, 0x7AFAC5D782F9AE6FULL, 0x92D9F0A18BE26B86ULL, 0x579FFCF35780826BULL, 
            0xABB8711ED775A71AULL, 0xBD403B93E2D92D25ULL, 0x3FE11224D0C4B0A1ULL, 0xEB106D41B848F1FBULL, 
            0x6E863AFB670FA536ULL, 0x26FDB0F8CD05E498ULL, 0x6C77FA958DA898C5ULL, 0x6B862BB42B135073ULL
        },
        {
            0x11BB7D5C681B741FULL, 0x6EC4195B01D0BB5EULL, 0x8D6DA09E766AC5A1ULL, 0x74474BB8FE5C54DBULL, 
            0x0242F3551016C387ULL, 0x710126DC268C9F62ULL, 0x050F4A5092704708ULL, 0x943F5762461B5656ULL, 
            0xF7AF4E89C2BA582CULL, 0xB8211C3BE6C72A23ULL, 0xE9C342059EAE7079ULL, 0x0A4377E146A07BAAULL, 
            0xDA3D6D3366C8603AULL, 0xFD248974EB5D0C4FULL, 0xFE8C5490285A7984ULL, 0xC7A2C2F4F297F70DULL, 
            0x88EAB33234B41CFDULL, 0xC58FAEEFD150A789ULL, 0xD4B372E4CE5E7C55ULL, 0x63B7CB1B09E9C69AULL, 
            0xEF250CD234E9FF94ULL, 0xE462E2BB6A994500ULL, 0xD153072FF75CECCCULL, 0xB67C9DA6133A1A83ULL, 
            0x6C16697A5F34EBDFULL, 0x5C1B3FD3005D6379ULL, 0x1689168C8874B110ULL, 0xC78A58ACC1CD755BULL, 
            0xDB723169F712E6D8ULL, 0x28C35448422EC2E8ULL, 0x8303D818378B6B28ULL, 0x42B1F843BC440ABCULL
        },
        {
            0x048E3DB27B6437BEULL, 0x20279D1A332DE70DULL, 0x64CC339C5716CCB4ULL, 0xB4F97296B1638A86ULL, 
            0x257F74954F3A9095ULL, 0x42E86E7D2031352AULL, 0x6C9D6FE84AB61BF7ULL, 0x561045A90B1E018AULL, 
            0x0105BCEF539FBA52ULL, 0x6AEF8B403C740022ULL, 0xB074240CBF338076ULL, 0x6208B2585860240EULL, 
            0x5683AA7D57B9ABD3ULL, 0x8114EF407E7FA041ULL, 0xFD21C57A7879DE1BULL, 0x45A0637DA361FADCULL, 
            0x96D2556CA064EE6CULL, 0x055C0991E6FBAC5DULL, 0x0522477342135E5EULL, 0x64CC70B56C89FD19ULL, 
            0xA8344B1A99F2B779ULL, 0x0BC7B90B7A74E32FULL, 0x5BF2EDD008BF2CF2ULL, 0x2990015CC8BEF9FCULL, 
            0x421EAE16429CDEDEULL, 0x77E1DD9A5DE46FE9ULL, 0x5D49BDD6AEB03295ULL, 0xDC66DCF27A410C09ULL, 
            0x6F33F17239A41235ULL, 0xCF31B19D945771F3ULL, 0xB27BF616479A8E2AULL, 0xB51A989077CA9CA4ULL
        },
        {
            0xE210704E1F9AD874ULL, 0xC9847D581A6D267BULL, 0xBC6C3E8243D1C3BFULL, 0x31C16631A89E03E9ULL, 
            0xA3243E56436866F4ULL, 0xDE6030BCDE5F56A6ULL, 0xF80C131ACCAFF083ULL, 0x283758A9D21F31BBULL, 
            0x6E771B5226D566C5ULL, 0x83DB4481303407A6ULL, 0x1170780F2F3DE1EAULL, 0xBC6A6C3A9A74C3BFULL, 
            0x795B4FD3A80DA221ULL, 0x3D0121B59FF580A6ULL, 0x6AB4BEB6C0DADDC3ULL, 0x59A343A3BD0E5CBDULL, 
            0xCF5874F848049857ULL, 0xDEA804475E9B9382ULL, 0x8E9E0D5FBE14B8C9ULL, 0xDD96381EBFA240E8ULL, 
            0x3874DAFFD76133C3ULL, 0x798F4A2D53797C22ULL, 0xDD9C0E3F818939CBULL, 0xF1CC78C0BAA57C28ULL, 
            0xC6DA890DE8D81D57ULL, 0xDF811ACBB62332CAULL, 0xA5DB8321257A70B4ULL, 0x2291B88F65E3BFA2ULL, 
            0x21B56BB93F7EAA7EULL, 0x9C229FB7A64A3466ULL, 0xDA6F55CF4E577308ULL, 0xEF8351B36DF0512CULL
        },
        {
            0x487109784887EC3EULL, 0x00CB0A8A5EB496CDULL, 0xDA3196573EFEE5C6ULL, 0x2A612F742903BD0EULL, 
            0x0A745A02D12491F0ULL, 0x5C0C36DDF214D3C9ULL, 0x47C2C94BCDACF567ULL, 0x4EF76BE082A4E3A6ULL, 
            0xFD5928A8B76FABA6ULL, 0x9690A3AD4ED837C6ULL, 0x12D2D532D786C80BULL, 0x7889D71B8A51AE8AULL, 
            0x0BEAD84D9B0F5D55ULL, 0x02E96E6A4732736EULL, 0x9BD28B168646DE0FULL, 0x3D286628153FBC28ULL, 
            0xB80B1DDB3515A584ULL, 0xEFD595C91FE6D518ULL, 0x40DD65BF48F690CEULL, 0x5F721E6CBD7F97BAULL, 
            0x66F9449E273A8698ULL, 0xF104ABF2EA9F1680ULL, 0x6CEA90E1F57E9D9BULL, 0xFBEB8BDB261F9E8DULL, 
            0xFCF78D81B217E0F5ULL, 0xA7E5295A8B3AE37FULL, 0x285E28242F7D4023ULL, 0x4A3D0C4AB1A8233BULL, 
            0x93AFB75C805B7D95ULL, 0xC6204190875CCEB0ULL, 0xA5B3941DAD3FD9A8ULL, 0x3CE9E1D9D3F21431ULL
        }
    },
    {
        {
            0xCFE4CEE9CCB0FF22ULL, 0x7F124B851F9BACA9ULL, 0x359B0409C59CC334ULL, 0x3C6A52E0097A739CULL, 
            0x87DAD947B8D0A18DULL, 0x53E09BBFECB3623EULL, 0xBCFF44D7F616D0A2ULL, 0x92FC909631BC85CAULL, 
            0x0D8B54CE9D59DC47ULL, 0xD2EC3B8984638261ULL, 0x520A5B8680D2F1DDULL, 0x2F0D333252843803ULL, 
            0xC27FF5251C1CD6F9ULL, 0x880F7FEB158BA08CULL, 0x86AEF066C251ED72ULL, 0x60B18B6E8C5E3F98ULL, 
            0x5C638C16BA0CB634ULL, 0x3B0075401F4D4FCFULL, 0xE0006A66B6BEB4FAULL, 0x5FA51E18D485165CULL, 
            0x6564D67A14334188ULL, 0x13BFF801CDF8E1F7ULL, 0x374B2AF14C0A66E7ULL, 0xBFB717FCCE058CC4ULL, 
            0x90290EC44213094FULL, 0xA1E9FE834F901A15ULL, 0xC5209C7E0B7337E7ULL, 0x703451171ED57CB1ULL, 
            0x585080856F87D103ULL, 0xA42DCC314DF96473ULL, 0x7F4ED2AA9E33FBA9ULL, 0x5289AE4465C28E0EULL
        },
        {
            0x207AC133EA3B65ECULL, 0xD0AC92E9600F63C2ULL, 0x27828FF01FD39C67ULL, 0x92EA1194D3F50518ULL, 
            0x5A0F8E9EA789CC41ULL, 0x65B85F4F7B8BB8FBULL, 0xB2AD929F14E53BDBULL, 0xEDFB13E3B2C466ABULL, 
            0xE3767759F1FBE143ULL, 0xEB26B97F8385EEB3ULL, 0x61F25BDC2917D16AULL, 0x8E9CFDAA103D4822ULL, 
            0x26CC5E16BA62E17EULL, 0x4F79A2DEE6948A24ULL, 0x1781A7B3BBAC1405ULL, 0x148396B51DDF2FA6ULL, 
            0x6C8C1CC150A47E55ULL, 0x8BFC6FE8C85255E4ULL, 0xEB13F6C914603B85ULL, 0xBDE55E60BE10C5B0ULL, 
            0x33B744E0578C6152ULL, 0x24F197E4E0D51188ULL, 0xECC3707AD03D0A78ULL, 0x403E077DB28E9F79ULL, 
            0x17DBAD47F4BF1FC6ULL, 0x38EFCA82BB5282C7ULL, 0x80448CC0FCC7ED53ULL, 0x990284B42FE425AFULL, 
            0x13EABDD9E3954551ULL, 0xE4AAD5A8A45F9FA8ULL, 0x6F1657EE43B47278ULL, 0x924A146ACFCF37D0ULL
        },
        {
            0x6D4D91F811B3B234ULL, 0x6C967DA92D7CC275ULL, 0x01B8A5CF958CA858ULL, 0x85E838215DCA6525ULL, 
            0x68C41F52A3F5F57AULL, 0x60BB4A58F8DADB12ULL, 0x482E5CD277FE9620ULL, 0xCE987A4DB543A4B0ULL, 
            0x01488E7B0314493BULL, 0x055E42F05FA2E04BULL, 0x15A602D941CFC884ULL, 0x060DBBC5B51955C6ULL, 
            0x222E06E04200C940ULL, 0x8413A2B03C6F05AFULL, 0x2E46541023F715F2ULL, 0x33504DA290A50CD2ULL, 
            0x751D44C2D56B9297ULL, 0x25E0C1138F103317ULL, 0x7F4C6FE791781EA2ULL, 0x1E078E74D931EEB1ULL, 
            0x8F44D7C367061DB0ULL, 0xAE86CB4BB1311F3DULL, 0xD6BB34B95A867459ULL, 0xE1AC6A3372DC7378ULL, 
            0x171007C6C1256D78ULL, 0x009D7E0D02180CA2ULL, 0xE6458DEA5CDE7522ULL, 0x43390D4707236048ULL, 
            0xDCC95D1E62F188D1ULL, 0xD5E3BD7118DA965EULL, 0x55A6786777870B38ULL, 0x703DF13C39874E69ULL
        },
        {
            0x7142A35C9FFA6AE1ULL, 0xA7D5FC34C478B257ULL, 0xF12A6305231F1493ULL, 0x13BA46AA7D520AE0ULL, 
            0x798F3AD9DE686E24ULL, 0x9F73764E5FE86D71ULL, 0x8D268E5BBEB57929ULL, 0x6EECF7A1C9B6E7A0ULL, 
            0x7D56A13ADDC2BEAFULL, 0x7BDDE472D721CCDCULL, 0x127C31F01EDC2614ULL, 0x6E4C6E7C124379AFULL, 
            0xDAFFB15557FFA47FULL, 0x14E61F83A1B2B54DULL, 0x0BF51BF46EE6419CULL, 0x36ED7B76A3DC310EULL, 
            0xED46014165E9A4F6ULL, 0xEC46550D443D1C8BULL, 0x40DC53C3EC257350ULL, 0xC3EBC387FECF51E4ULL, 
            0x1370995349C3AE93ULL, 0x4B372124CF28FFDDULL, 0x27ED869ADC27C8E9ULL, 0x9C7D12A0519E79A1ULL, 
            0x3F026BF107747411ULL, 0x849E785B73C14388ULL, 0x4A4B05910CA9D3A8ULL, 0x7D3D089AEC3BEF90ULL, 
            0xE78A556B1D37CE6CULL, 0xC2FA19DB2A538975ULL, 0xDFC3D000F998A429ULL, 0xFFC57B279D65EC1AULL
        },
        {
            0x57E4BB9BAD8383CBULL, 0x006C359200F737A3ULL, 0x1D1D00FB0F805FE5ULL, 0xB116C92A28AFA908ULL, 
            0x9FAF10BED8675C42ULL, 0x1D99531067639E65ULL, 0x11BC66E7E28DAE20ULL, 0x8F254BBDE7723EB7ULL, 
            0xA2B5AA493B8CB996ULL, 0x3550D7E4E296D5A5ULL, 0xE350D521A7BB910FULL, 0xD41AEC932397CA6DULL, 
            0x0A095CA21BA89881ULL, 0xFC4C9C58C20CA310ULL, 0xADB10FC577738ABAULL, 0x920E842149F9CF48ULL, 
            0xD63896038860A5DBULL, 0xB5678FD95C3AAFDEULL, 0x602DBB510B85979CULL, 0x7DB8152506C24FEFULL, 
            0x9D45BCAAD3B96E28ULL, 0x755CDE1E3A532DDCULL, 0x8E84165DDADFF730ULL, 0x460F3C70DDA19B03ULL, 
            0x018423C12AD20B1EULL, 0x0A33E7DE08E22F0BULL, 0x6E7A667C8AA031E9ULL, 0xE5603F1F03D0A713ULL, 
            0xC00AA021D24BAB32ULL, 0xA411AEA6A5263BB8ULL, 0x76AE722D8031E47BULL, 0x624EF44AB2202B39ULL
        },
        {
            0x5BD373F30639B809ULL, 0x1E40D31808B9C167ULL, 0x3722695E3E99DF13ULL, 0x8435972F1614E977ULL, 
            0xA312B7A08D2F70C4ULL, 0x1F9779EEBC173838ULL, 0x334AD8461A0C624FULL, 0x33F8F2E2DBA2C8C2ULL, 
            0x5F32992BF14E03ABULL, 0x24A6F9CCA1461A55ULL, 0x916C0C0E9520235FULL, 0x39DC18A98E6E8E29ULL, 
            0x1FDD8F8AB84F6EB7ULL, 0x4E03B740C7871C36ULL, 0x1D53A7B5AAAF3902ULL, 0xDF60C54553161F54ULL, 
            0x96202E8561AC5F14ULL, 0x4DE452ACA0CCE14CULL, 0x191778033340030FULL, 0xC5768E7DE6ECC42FULL, 
            0x2F8743314D0122F5ULL, 0xDA4C942A677143CCULL, 0x436B4A58C8CA6C91ULL, 0x15BF7EF5935B21FAULL, 
            0x32F217D7DD4C8E0EULL, 0x3E628D47C7C28139ULL, 0x04A33E4D47F8114DULL, 0x354EFF6C742BF514ULL, 
            0x8107DC4563FAC0B3ULL, 0xE8D17C22F113FCC1ULL, 0x0F3FD849094A906FULL, 0x904A8EE7435ECC60ULL
        }
    },
    {
        {
            0x2E5E12906C994C9DULL, 0x5E9B68D2BB0B38D4ULL, 0xDFC3EBF23D799743ULL, 0x82268D27934876D0ULL, 
            0x7A58F06503CF5E44ULL, 0xCDFAA1825A5C58FEULL, 0x83AB6B632464C64AULL, 0xA0AD65367F8CAE84ULL, 
            0xA937E53D954ECB06ULL, 0x3E7073F70D1C1641ULL, 0x942A87229C62CE08ULL, 0xA5934CDF5A930479ULL, 
            0x59E67F3250CC7436ULL, 0xD93277A1E5D2DE02ULL, 0x7510E5C5B7619306ULL, 0xD430817A8340403DULL, 
            0x4C26A4AC4C8574BCULL, 0x04C4593465FCF65BULL, 0x4ED97B74BD3AB29CULL, 0x9811D2A266523AABULL, 
            0xE38A1B312B8DA3CAULL, 0x98174C747458FB0EULL, 0x6E2B340BF35505D5ULL, 0x3182DFC1655351E1ULL, 
            0x97E3C5ACEEC5D27BULL, 0xE6749554EB9434B0ULL, 0xCCAFC4CE0DFEB38DULL, 0xE2F7C308F589131DULL, 
            0x6BC3B8CA9B9C5481ULL, 0x9D9D564195C41790ULL, 0x09FB08E3D5B0B696ULL, 0x3D1FE80B895F0D16ULL
        },
        {
            0x05AAFFD627015BE4ULL, 0xD9D25B855658D56AULL, 0x9C1459D6CF405763ULL, 0xDB54E05E71FB72D7ULL, 
            0xE0A71536BBBF078BULL, 0x720D82AB6C74AE91ULL, 0xAE69440A7E24E2C5ULL, 0x276B76B6BBFD86B5ULL, 
            0x5D7146EDB0FB976CULL, 0xD5BD37923D52572DULL, 0xFEBEC3F9166BBCEBULL, 0xD0051DE200937E59ULL, 
            0x9438DD8DCBA7FB1FULL, 0x6C4977D331EF3AB1ULL, 0xDBA55BD6428E124FULL, 0x6961123D6F1CF784ULL, 
            0x62B28F3E53F6FFB6ULL, 0x0D5452356B5B144DULL, 0x2C08F46D10614B84ULL, 0x66BE946051810414ULL, 
            0xAF6C8514314E17A9ULL, 0x023F4C6F09F5921BULL, 0x49E816881DA9B079ULL, 0xE179134656185F82ULL, 
            0x46724BFC1037C53DULL, 0x2A7EB260EBCC7B6BULL, 0xE1263C7A8BA67209ULL, 0x504F55C1D64BBAB5ULL, 
            0xAFE2947AF0B49138ULL, 0xF32E204BE70FDE66ULL, 0xA02282B4799E709EULL, 0x9E56909EA99011E6ULL
        },
        {
            0x2569E1C9325870BBULL, 0x61FA7D09D85DA793ULL, 0x0EAD25B13D808FA1ULL, 0x9A5E33F8CB0C51B5ULL, 
            0x1D81E1EEC40552E4ULL, 0xB508C5928C2AAEBBULL, 0x2BB7EEDBC392756AULL, 0xE9EC10C979680639ULL, 
            0x20428736E264F116ULL, 0xAA43487A937DE0F5ULL, 0x9BF1129C92B20397ULL, 0x04B248AACF785317ULL, 
            0x3291AFFB862C58AEULL, 0xA47F67807EEEEAD4ULL, 0x02297656F03D8D09ULL, 0xFA6F160519662AABULL, 
            0xA29A387A56C31610ULL, 0x48D7704B05E42C69ULL, 0xFC18494A35464E19ULL, 0x8AA54647BFB9FD57ULL, 
            0xAE17C97CE208C0FAULL, 0x86535130EBE36255ULL, 0x03CBF2DC546DDB4DULL, 0xE811C9DA9CDDBF4CULL, 
            0x7914F219374DF1D3ULL, 0xE1C281A00AFA7070ULL, 0x354CFF90B1B4CAD5ULL, 0xB3F4B4754ADD5C48ULL, 
            0x75D784D0C2D5AB5CULL, 0x2B5E2DA58999076CULL, 0xFD9A46A0C7F17370ULL, 0x42243FE9CC9988C0ULL
        },
        {
            0x0958CD1561620C42ULL, 0xE36FD4A32B6425C4ULL, 0xA393AAF50EEA60EAULL, 0x6BAB6FCA6589FD53ULL, 
            0x41725605DB5CBD43ULL, 0xD7AE3E239E3F5FAFULL, 0xA2FC6EF0A044FF27ULL, 0x42F8DF54F4456375ULL, 
            0x9896E93773697277ULL, 0x8E9CC78A8BF84EA6ULL, 0x74EFFAE746A789A2ULL, 0xD69BAE1669DB3FB5ULL, 
            0x7F3857734694CE3CULL, 0x74354F0D15BBA870ULL, 0x29ECEEBB7BC7D3CAULL, 0x00FAD3844ACFBA11ULL, 
            0xFF20B1031B632274ULL, 0x957A002923D0257DULL, 0x421DD275398CB395ULL, 0xE4485064EC010C35ULL, 
            0x34F45A7D2CA60880ULL, 0x5F2F04F0A08590FBULL, 0x80F4D196441B22DCULL, 0xD8D31B863CE45FCEULL, 
            0xA58232458CE48836ULL, 0x34BDE58F08F3ADD3ULL, 0xF17CE34120DD5ACCULL, 0xABEAE7F18D72AF95ULL, 
            0xAEC6A0DE7E79F2F5ULL, 0xC4CEDFA68D1D452AULL, 0xC3762A7087747D54ULL, 0xE9C9A20774FFBF85ULL
        },
        {
            0xA06A22128B190BCEULL, 0x45121092F4B3CE9AULL, 0xB2CA2356CC36F8EDULL, 0x443F2700A5D93C2BULL, 
            0xC248D944AE2FE98AULL, 0xF19607532782F60EULL, 0xB7115C57F248D663ULL, 0x2149EE5ECAD1B17BULL, 
            0x3B63805BCDD97838ULL, 0x823BF2284C6F9F4DULL, 0x92C056158D37EC08ULL, 0xE5F7D7E59FBB796FULL, 
            0xC546CAA2F3A05443ULL, 0x04387D8AE46ABDB6ULL, 0x4C3F642705412D51ULL, 0xC6904BD7FC24A737ULL, 
            0x7A1AF0D4A374FDFEULL, 0xACDF46A30F9A466AULL, 0x70ADEAC88CC0D8F6ULL, 0x838B29223CB04E9FULL, 
            0x88AF9A829AE03215ULL, 0x994B3858C69B1A81ULL, 0x93EDB21BE71CE600ULL, 0x3F184734E637085DULL, 
            0xF8DC1414CC3BAA35ULL, 0xBCD8D3C44A03367DULL, 0x6C0908E70BB7E7A2ULL, 0x6FEB59BB8E4E5098ULL, 
            0xB8353BC0DB62EF4FULL, 0x85878C73CA426030ULL, 0x8CEFD15E5ED3DBD9ULL, 0x5E52DA1760659114ULL
        },
        {
            0x9B157CE4C15897F4ULL, 0x3B903337C4534D8EULL, 0xA2F977FBB3A0AB75ULL, 0x6746396BC6A40036ULL, 
            0xA76F4E296B873CA3ULL, 0x4A5BFEAE8D033AA1ULL, 0xE9EA595D141EE238ULL, 0x542C7F28E7195C79ULL, 
            0xD88509476E3846EBULL, 0x40ABA20CFBA38F3BULL, 0x4B6E767ACDEA43E0ULL, 0x93D926C2FDE15E27ULL, 
            0x156FFC77E4D0AD4AULL, 0x4A83CF12D94E4B01ULL, 0x0053FB11B56DFA0EULL, 0x6A41318BA990334AULL, 
            0x19D612D7833BE8BEULL, 0x60C5C33200817A9DULL, 0xFDBFBF590EDA5E76ULL, 0x97EC1BAAFEBEB112ULL, 
            0x4228E95A1E70B63DULL, 0x7CA5CCCA728CB926ULL, 0xDC940F922359810DULL, 0xD304125215428B7BULL, 
            0x9D3BDC781A7C0E32ULL, 0x3EEE8DB2F7627688ULL, 0x7357407B4A251840ULL, 0x8C4F8B8ACCB887A9ULL, 
            0x800897CB8D300083ULL, 0x278665EFB09349EBULL, 0x6CBBFBD025F9C8ADULL, 0x2F8D90A78E04F7F2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseHConstants = {
    0xCDF631028185815AULL,
    0xBDBB5FCDD12D2F5EULL,
    0xA31C5B3BADC74DA2ULL,
    0xCDF631028185815AULL,
    0xBDBB5FCDD12D2F5EULL,
    0xA31C5B3BADC74DA2ULL,
    0x500479DB2E83FAEDULL,
    0x2ACC942B0FB8E569ULL,
    0x2C,
    0x74,
    0x30,
    0x61,
    0xB5,
    0xA1,
    0x37,
    0xBC
};

