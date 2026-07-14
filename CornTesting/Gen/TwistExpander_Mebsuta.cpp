#include "TwistExpander_Mebsuta.hpp"
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

TwistExpander_Mebsuta::TwistExpander_Mebsuta()
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

void TwistExpander_Mebsuta::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCF1599706EBD0BA8ULL; std::uint64_t aIngress = 0xE023B8BE97DDE490ULL; std::uint64_t aCarry = 0x8A6AFD05AF96F0E7ULL;

    std::uint64_t aWandererA = 0x8153515B8819CB41ULL; std::uint64_t aWandererB = 0x9EA11E4E0F1C780CULL; std::uint64_t aWandererC = 0xD21E22E5FDF17CC7ULL; std::uint64_t aWandererD = 0xC8DEB9CB82CA7DD0ULL;
    std::uint64_t aWandererE = 0xB5923360138C4964ULL; std::uint64_t aWandererF = 0xAAE497C736C87654ULL; std::uint64_t aWandererG = 0xC4067F0D2C2FDA45ULL; std::uint64_t aWandererH = 0xBB0B817633B5B87BULL;
    std::uint64_t aWandererI = 0xE8D582ED9F99B989ULL; std::uint64_t aWandererJ = 0xCDB961273A75204EULL; std::uint64_t aWandererK = 0xBBB784E3201034B7ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10353595354743919429U;
        aCarry = 16374946884271591389U;
        aWandererA = 12318334069437172544U;
        aWandererB = 14564605825389450086U;
        aWandererC = 10047795867389524285U;
        aWandererD = 16803404758975888740U;
        aWandererE = 12844203576212753724U;
        aWandererF = 16178965061789132020U;
        aWandererG = 15269733704622632555U;
        aWandererH = 13514596832509330747U;
        aWandererI = 15406750829988699878U;
        aWandererJ = 11319477517669538639U;
        aWandererK = 17847938996810250625U;
    //
    // ---------------------------------------------------
    // KDF_A_A kdf_a_loop_a:
    // ---------------------------------------------------
    // read from: source, snow
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_A_A(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // KDF_A_B kdf_a_loop_b:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_A_B(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // KDF_A_C kdf_a_loop_c:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_A_C(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // KDF_A_D kdf_a_loop_d:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: earth_b, earth_c, earth_d, source, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_A_D(pWorkSpace,
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
    //
    // ---------------------------------------------------
    // KDF_A_E kdf_a_loop_e:
    // ---------------------------------------------------
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: earth_a, earth_b, earth_c, earth_d, source, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: water_a, water_b, water_c, water_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mebsuta::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9F88C5AC94933C36ULL; std::uint64_t aIngress = 0x98BD3E17D2A3B588ULL; std::uint64_t aCarry = 0xB7DA21F9FFAECA37ULL;

    std::uint64_t aWandererA = 0x8B7014E9AFF40149ULL; std::uint64_t aWandererB = 0xF7972756FDBF915CULL; std::uint64_t aWandererC = 0xD55F6875E5E02530ULL; std::uint64_t aWandererD = 0xB66547242DF9F904ULL;
    std::uint64_t aWandererE = 0x88E6C3CB4BC6A065ULL; std::uint64_t aWandererF = 0xB2E6368E636ADBF5ULL; std::uint64_t aWandererG = 0xE8ACC60E4E18D17EULL; std::uint64_t aWandererH = 0xAFD8B3847DE45F9AULL;
    std::uint64_t aWandererI = 0xBC9D4362C8039DE6ULL; std::uint64_t aWandererJ = 0x9EDED9A9F20160BEULL; std::uint64_t aWandererK = 0xF38342110CD0D6C4ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18398517253142156939U;
        aCarry = 11762784678912781410U;
        aWandererA = 14576118407288036207U;
        aWandererB = 16099682604263628097U;
        aWandererC = 13424226690172888745U;
        aWandererD = 16857334145097472048U;
        aWandererE = 12081916997486714019U;
        aWandererF = 15611541577261193363U;
        aWandererG = 11762259843008562762U;
        aWandererH = 15075285848062899577U;
        aWandererI = 17546457318081086863U;
        aWandererJ = 13553604536842578459U;
        aWandererK = 9457263727862500231U;
    //
    // ---------------------------------------------------
    // KDF_B_A kdf_b_loop_a:
    // ---------------------------------------------------
    // read from: water_a, water_b, water_c, water_d
    // temp storage: wind_a, wind_b, wind_c, wind_d, fire_a, fire_b, fire_c, source
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_B_A(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // KDF_B_B kdf_b_loop_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: water_a, water_b, water_c, water_d, source, wind_a, wind_b, wind_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_B_B(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // KDF_B_C kdf_b_loop_c:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: expand_a, expand_b, expand_c, expand_d, earth_d, fire_d, water_d, source
    // ---------------------------------------------------
    // write to: fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_B_C(pWorkSpace,
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
    //
    // ---------------------------------------------------
    // KDF_B_D kdf_b_loop_d:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: water_a, water_b, water_c, water_d, fire_a, fire_b, fire_c, wind_c
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mebsuta::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC49B6C1766A3D8EEULL;
    std::uint64_t aIngress = 0x85D38A484648F25DULL;
    std::uint64_t aCarry = 0xD9E5DE866B88A745ULL;

    std::uint64_t aWandererA = 0xA3037163A5FA88EEULL;
    std::uint64_t aWandererB = 0xA632F6A4F0FCA150ULL;
    std::uint64_t aWandererC = 0x9068B7B8D444607FULL;
    std::uint64_t aWandererD = 0xAE33E9004833FBA8ULL;
    std::uint64_t aWandererE = 0xCFAFB79E850C351FULL;
    std::uint64_t aWandererF = 0xCDC40509793B88ECULL;
    std::uint64_t aWandererG = 0xDAEE361856B5E2C6ULL;
    std::uint64_t aWandererH = 0xFE968C700E72F332ULL;
    std::uint64_t aWandererI = 0xE79114A955E177A1ULL;
    std::uint64_t aWandererJ = 0xF052022626F4AE0EULL;
    std::uint64_t aWandererK = 0x9D13AC7CA9E72CB3ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
    //
    // ---------------------------------------------------
    // GSeedRunSeed_A seed_loop_a:
    // ---------------------------------------------------
    // read from: source, key_row_read_a, key_row_read_b
    // temp storage: water_a, water_b
    // ---------------------------------------------------
    // write to: water_a, water_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_A(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_B seed_loop_a:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, earth_a, earth_b
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_B(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_C seed_loop_b:
    // ---------------------------------------------------
    // read from: work_c, work_d, earth_a, earth_b
    // temp storage: work_a, work_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: earth_c, earth_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_C(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_D seed_loop_b:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: work_a, work_b, work_c, work_d, earth_a, earth_b, expand_a, expand_b
    // ---------------------------------------------------
    // write to: snow_a, snow_b, fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    //
    // ---------------------------------------------------
    // GSeedRunSeed_E seed_loop_c:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: key_row_read_a, key_row_read_b, snow_a, snow_b, expand_a, expand_b, expand_c, expand_d, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: water_c, water_d, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_E(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_F seed_loop_c:
    // ---------------------------------------------------
    // read from: invest_a, invest_b, invest_c, invest_d
    // temp storage: snow_a, snow_b, water_c, water_d, earth_a, earth_b, earth_c, earth_d, fire_a, fire_b, source, key_row_read_a
    // ---------------------------------------------------
    // write to: snow_c, snow_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_F(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_G seed_loop_d:
    // ---------------------------------------------------
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: snow_c, snow_d, source, key_row_read_b, invest_a, invest_b, invest_c, invest_d, snow_a, snow_b, water_c, water_d
    // ---------------------------------------------------
    // write to: water_a, water_b, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_G(pWorkSpace,
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_H seed_loop_e:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_c, fire_d, source, key_row_read_a, snow_c, snow_d, expand_c, expand_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_H(pWorkSpace,
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
    //
    // ---------------------------------------------------
    // GSeedRunSeed_I seed_loop_f:
    // ---------------------------------------------------
    // read from: invest_e, invest_f, invest_g, invest_h
    // temp storage: key_row_read_a, key_row_read_b, fire_a, fire_b, expand_a, expand_b, snow_a, snow_b, water_a, water_b, water_c, water_d
    // ---------------------------------------------------
    // write to: fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Seed_I(pWorkSpace,
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
    //
    // ---------------------------------------------------
    // GROW_A grow_key_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: scrap_a, scrap_b, water_a, water_b, water_c, water_d, invest_a, invest_b, invest_c, invest_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    //
    // ---------------------------------------------------
    // GROW_B grow_key_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: scrap_c, scrap_d, earth_a, earth_b, earth_c, earth_d, wind_a, wind_b, wind_c, wind_d, invest_e, invest_f, invest_g, invest_h
    // ---------------------------------------------------
    // write to: scrap_c, scrap_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 17 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1817 / 1984 (91.58%)
// Total distance from earlier candidates: 29246
void TwistExpander_Mebsuta::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1702U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1204U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2012U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1119U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 247U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 407U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 327U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 34U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1837U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1240U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1199U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1730U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1015U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 732U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 3U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 950U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1151U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 224U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 45U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1153U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 705U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 131U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 162U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 814U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 785U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 796U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 937U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 448U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1926U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 136U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 620U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1192U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1773U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 526U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 601U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 15U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 528U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1919U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 630U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1454U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 693U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1398U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1731U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 704U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 81U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 178U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1411U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1577U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1183U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 333U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 211U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 867U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1096U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 823U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1170U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1918U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 945U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1375U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 145U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 773U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 964U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 109U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 734U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1042U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 918U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 90U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 489U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1052U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1868U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1615U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 581U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 361U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1658U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1169U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2023U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1568U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 940U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1297U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1145U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 146U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1499U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 324U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 879U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 194U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 710U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 308U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1633U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1869U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1485U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1762U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1647U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1910U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 449U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 29U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 833U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1347U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1670U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 815U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 920U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 925U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 663U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 64U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 939U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1959U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 606U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 654U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1070U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 623U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1589U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 656U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1216U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1562U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 270U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 988U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1853U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 9U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 534U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1828U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1603U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1163U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 352U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1458U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1048U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1955U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1862U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Mebsuta::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0x87880176A3163A6DULL; std::uint64_t aIngress = 0xE4325BA94FE300BFULL; std::uint64_t aCarry = 0xC0D0DC44F4336294ULL;

    std::uint64_t aWandererA = 0xC1F71E013F3F77E9ULL; std::uint64_t aWandererB = 0xE9D4A71860C8A61DULL; std::uint64_t aWandererC = 0xE93235058B26455DULL; std::uint64_t aWandererD = 0xE7DB89C4D9F0E518ULL;
    std::uint64_t aWandererE = 0x856F422615D301B7ULL; std::uint64_t aWandererF = 0x90985C7B69B0B26AULL; std::uint64_t aWandererG = 0xEFF760BEE94E567EULL; std::uint64_t aWandererH = 0xDEDCCAE6924FF714ULL;
    std::uint64_t aWandererI = 0x99747A1A6557BCADULL; std::uint64_t aWandererJ = 0xFF34B40CA4376AC1ULL; std::uint64_t aWandererK = 0xD39C720843083996ULL;

    // [seed]
        aPrevious = 9232022775323790397U;
        aCarry = 11014670607093966141U;
        aWandererA = 14928139553613055082U;
        aWandererB = 11758035695282572630U;
        aWandererC = 14465786629976991548U;
        aWandererD = 10747215365672985902U;
        aWandererE = 11930465215261365344U;
        aWandererF = 11742766150283115400U;
        aWandererG = 18021316829750497855U;
        aWandererH = 10399312270213985079U;
        aWandererI = 16141177659360604614U;
        aWandererJ = 16591345654761700140U;
        aWandererK = 14402835009724055375U;
    //
    // ---------------------------------------------------
    // GTwistRunTwist_A twist_loop_a:
    // ---------------------------------------------------
    // read from: source, key_row_read_a, key_row_read_b
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Twist_A(pWorkSpace,
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
    // ---------------------------------------------------
    // GTwistRunTwist_B twist_loop_b:
    // ---------------------------------------------------
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: water_c, water_d, snow_a, snow_b, snow_c, snow_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Twist_B(pWorkSpace,
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
    // ---------------------------------------------------
    // GTwistRunTwist_C twist_loop_c:
    // ---------------------------------------------------
    // read from: snow_a, snow_b, snow_c, snow_d
    // temp storage: water_c, water_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    // write to: water_a, water_b, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Twist_C(pWorkSpace,
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
    // ---------------------------------------------------
    // GTwistRunTwist_D twist_loop_d:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: water_a, water_b, water_c, water_d, wind_a, wind_b, wind_c, wind_d, snow_a, snow_b, snow_c, snow_d
    // ---------------------------------------------------
    // write to: invest_a, invest_b, invest_c, invest_d, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Twist_D(pWorkSpace,
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
    // ---------------------------------------------------
    // GTwistRunTwist_E twist_loop_e:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // temp storage: invest_a, invest_b, invest_c, invest_d, water_a, water_b, snow_a, snow_b, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: invest_e, invest_f, invest_g, invest_h, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::Twist_E(pWorkSpace,
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
    //
    // ---------------------------------------------------
    // GROW_A grow_key_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: scrap_a, scrap_b, water_a, water_b, water_c, water_d, invest_a, invest_b, invest_c, invest_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: scrap_a, scrap_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    //
    // ---------------------------------------------------
    // GROW_B grow_key_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: scrap_c, scrap_d, earth_a, earth_b, earth_c, earth_d, wind_a, wind_b, wind_c, wind_d, invest_e, invest_f, invest_g, invest_h
    // ---------------------------------------------------
    // write to: scrap_c, scrap_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Mebsuta_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 17 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8752; nearest pair: 481 / 674
void TwistExpander_Mebsuta::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4331U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5024U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 601U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6529U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2775U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7814U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6245U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7686U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2098U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2003U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 380U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7933U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3091U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5474U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6939U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3129U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1744U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1993U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 501U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1691U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1138U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 170U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 809U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 233U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1862U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1728U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 244U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 256U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 19U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1592U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 572U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 116U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1102U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 76U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 897U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 17 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8737; nearest pair: 481 / 674
void TwistExpander_Mebsuta::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2056U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6378U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3807U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4685U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7840U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3222U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 508U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5836U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1282U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4266U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4082U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1153U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4406U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2106U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5247U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2399U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1498U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1892U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 82U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1857U) & W_KEY1);
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
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1384U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1355U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1069U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 536U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 99U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 342U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1550U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1787U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 645U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1405U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 866U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1568U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1801U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 568U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 18U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 930U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseASalts = {
    {
        {
            0xC4B139C927D24942ULL, 0xA689005826CE0FA0ULL, 0x078BE59761CD87EAULL, 0x1D7500D64DBE7FC8ULL, 
            0x695C9428C266840EULL, 0x64A198F3F099E0CBULL, 0x9ECECDED95DB1404ULL, 0xDF22F4EA7DC78163ULL, 
            0x8C10134D88D8D336ULL, 0x9F59806009150933ULL, 0x4BFE65F7A252D392ULL, 0x38F60E89D79E0BDEULL, 
            0x5D97F389C85BA662ULL, 0x008F22609CB5BE5CULL, 0x46BC62B8FD5F657CULL, 0x2E745293A1C55A42ULL, 
            0x0666EA14BB3E4926ULL, 0xA31C65A2FCDD34D4ULL, 0x3BD3F8FA536C93FBULL, 0x6AD1C85BCA03A856ULL, 
            0x58035FE1E7BAD6B2ULL, 0xCF66027749930F00ULL, 0x1EB3FF0E86B079FAULL, 0x59DF8EBC3F5E896FULL, 
            0x0789E8851F3FB719ULL, 0xF57787D6C11AAEF5ULL, 0xB3109A1F8C46AA8EULL, 0xD3BE40A468D6B0E5ULL, 
            0x8CD0D73E145CE9C1ULL, 0xB5BD47D079EA1FD2ULL, 0x88233CFAAF1418F0ULL, 0x71AB49EBDB3CE36BULL
        },
        {
            0xD805926677B231B0ULL, 0xA22D812B675ED812ULL, 0xA4359851788CFBA5ULL, 0x5A02985D2BC95948ULL, 
            0xFCBD265BD75F596EULL, 0x33DB567F4B7226D7ULL, 0x5659C0AE5A6F0661ULL, 0x3AC0E51E39084E23ULL, 
            0xBC88468CA7872BF6ULL, 0xDBD25F8898D3477AULL, 0x1BBE8AAB2C13ED76ULL, 0x7F74F8C1313A8AB6ULL, 
            0x6C5586F40324B097ULL, 0x5EFF716EA26D635BULL, 0xEA5F8603364C78F9ULL, 0xDF558A10946B1FA0ULL, 
            0xD7F8411020CC2E67ULL, 0x8FCC93904F6C64F6ULL, 0xC2DE6E77FFEF3458ULL, 0x23EABDA6B0B68ADAULL, 
            0x35EA14188EA46390ULL, 0x136448F27E1FC16FULL, 0x0545B6B13E636554ULL, 0xD6045D41E279166BULL, 
            0x02AA669FEC070372ULL, 0x8F78357B635F863DULL, 0xFBE647D6F68EFCBBULL, 0xB5CC819889BADC3DULL, 
            0x1F40292ED221EAA1ULL, 0xA3D12A18D262F0C1ULL, 0x87A047BBA056A30FULL, 0x0B3C0D5E01987353ULL
        },
        {
            0x42449F4DC02D0015ULL, 0xAE441097FD4535F9ULL, 0x836C49D1D0531E72ULL, 0x162346C2DA4A89F5ULL, 
            0x3FF1B6F47ACA99B3ULL, 0xBF13DC43F350A136ULL, 0xEF021CDB0EB13318ULL, 0x3911D6B813F388BCULL, 
            0x3067407A5933C439ULL, 0xED19E692896A7C5FULL, 0x4E187764AF24D6F1ULL, 0x1537015DDEF77E97ULL, 
            0x152CA73610A092ADULL, 0xD9E386175E26AAB6ULL, 0xF55BAD1AE0FE18F8ULL, 0x40292A4D0320FC40ULL, 
            0x3C86BE1C244764F4ULL, 0x500FDBE22EA83845ULL, 0x3BD7B4ABB2768F27ULL, 0xE0593BD820A4CFB8ULL, 
            0xDA33D9C28BA00064ULL, 0x9142430029E1FD75ULL, 0x53C7A8F0063637B5ULL, 0x9C937938FB297BDBULL, 
            0x57B8CDE5F7891D31ULL, 0xFBB5B4FEB6E9CE3EULL, 0x2779EF93AA5A2B2EULL, 0xF1655F6A80541B68ULL, 
            0x4A81CD6BE8F80870ULL, 0xECAD9B413D2333A9ULL, 0x129D67480C902B5EULL, 0xCD0656BAF06F0F4AULL
        },
        {
            0x207C3D94DC298015ULL, 0xD3BA886543A2BA7AULL, 0x0C0ADC3307800D89ULL, 0xE61453471750A356ULL, 
            0x6AE124A37019EA2CULL, 0x69F6100C6B9C7E28ULL, 0x59CF02AF74BC9CF7ULL, 0x201D98D7D700A6EBULL, 
            0x55CDD839E0CEC3D2ULL, 0xE35997335A8A00A4ULL, 0xE28662D96292BA4CULL, 0x7583191B12C46BA1ULL, 
            0x8D7A5609D60AB516ULL, 0xFBC58D92A9ED8332ULL, 0xE2DFF1FFEA67677BULL, 0xF8D8B734E42ED7F0ULL, 
            0xBAA440D64B3C84AAULL, 0x053C7B9B91FE04CBULL, 0xAD878CEBA691362BULL, 0x94A0D727DB8A7383ULL, 
            0x7B0AC735423E97CEULL, 0x048DCA3A44E83661ULL, 0xBAE2A130926B8532ULL, 0x970D7351D031D01CULL, 
            0x7FBCC1E6A7E3DAE8ULL, 0x77B0B11A87B0565DULL, 0x38AA5B01AF9106A6ULL, 0x0108BC02B858C24EULL, 
            0xAD703C12A06F8F6BULL, 0xECB11F38AA9BFAB1ULL, 0x084304B3EE317926ULL, 0xA9EFBDCB701C3B08ULL
        },
        {
            0x219066A6E3956D6CULL, 0x434B9A602A8EBF48ULL, 0x409DB257C86D3343ULL, 0x969702623A3429DDULL, 
            0x62976E22DBB104C2ULL, 0x45FBF26B74ACE716ULL, 0x40B5A15E5D7F3532ULL, 0xECB6725A43D040D0ULL, 
            0x807C165AFB662687ULL, 0xFDB2BF0F78686B6CULL, 0x08ED20537657E523ULL, 0xD3DAD99889F54B44ULL, 
            0xDD2C05E1A30BAEADULL, 0x42F4106908B3A7F7ULL, 0x2A805BCFE8C2E0C1ULL, 0x149261BF3BC7D8F8ULL, 
            0x67D7768D2246FFBFULL, 0xF4789FFDBB8F99C4ULL, 0xD7516B532980CF10ULL, 0xE118E6A112E9350EULL, 
            0x63A102031B5D6AC3ULL, 0xDB28CE345B0FD3CCULL, 0x66DAAFD007D5CE83ULL, 0xF771082D3AD3EE0FULL, 
            0x7504ED7A627BED2CULL, 0x145EB83CD0877699ULL, 0x91E38A622C9C4F0EULL, 0x49F82CAC81390455ULL, 
            0x7C6C249EC4C20DF8ULL, 0x8E9B54DE569744DBULL, 0x54D9758A000D6862ULL, 0x94C761CB21ABC3A2ULL
        },
        {
            0xD883EE24D2F6999BULL, 0xDF455DF101B53502ULL, 0x05D42EFD0FABE3D2ULL, 0x3509484E46B529E7ULL, 
            0xFF67802887BCF49AULL, 0x3FC628BCCAC92C1FULL, 0xCB1C908BF24FD4CAULL, 0x0CEE4A8BB6D3B301ULL, 
            0xCA63D14EF1C6BCFBULL, 0x5704D95B135453EEULL, 0xCD2AD60B287E57DEULL, 0x65BFE3C48681A9F3ULL, 
            0x348040CA3875D0BEULL, 0x2877ED188BB25C63ULL, 0xF9554AD8DDB6D0C1ULL, 0xF50F166EFFD29EF4ULL, 
            0x0130C585DBE32353ULL, 0x0DBD1D48A7852E7AULL, 0x3B82803F7B2A4870ULL, 0x4CACC50E5A77A24DULL, 
            0xC9C95B766C3B8D7EULL, 0x8AFFB069A8114D3BULL, 0x13E2A3AFC7FF8B50ULL, 0xE3A15B553721DF8EULL, 
            0x24528D6DDD733E89ULL, 0xBD375509BD9599B7ULL, 0x67717634163E9678ULL, 0xB0E4A43C347C670FULL, 
            0x436B993C46085AA5ULL, 0xD612359EEB39BE83ULL, 0xB15CA47C1CF68856ULL, 0x622D6D58226BE03FULL
        }
    },
    {
        {
            0xF67CD5B03DAC7BB6ULL, 0xF26BD54C75B60053ULL, 0xC5EAA4F62F04E98EULL, 0x4E00217B8E942A40ULL, 
            0x8B97D752DFF29E4CULL, 0xF63CB1723D25CF8EULL, 0x48BE5CA3CA75B608ULL, 0xE5568A203128ACACULL, 
            0x340199AA59FCA519ULL, 0xE1349A173540A6E7ULL, 0x3D3577D464678BA2ULL, 0xC2579897D8081ED1ULL, 
            0x4F6B572083AB134AULL, 0xB65265E6C8E09DA5ULL, 0x70FF0E44A81C3EFAULL, 0x0E775E67665D2378ULL, 
            0x279F6F2EB9D07673ULL, 0x1818F8C04C507C8FULL, 0xAA51954AAE9635DFULL, 0xE861C0826B19DD7EULL, 
            0x3EF8B162F4353D68ULL, 0x7CC1AB4E135F97D0ULL, 0x0B561B4715B5F239ULL, 0x5215B635C1912820ULL, 
            0x9071365C87A9C4EEULL, 0x5FBA6244AC197778ULL, 0xE73699237CC6EA17ULL, 0xB2B8A0B26394D24EULL, 
            0xB624FF689B198BC2ULL, 0x4A38D586260CAB2FULL, 0x5461043ADDB7C4F7ULL, 0xCF870F81BDF91616ULL
        },
        {
            0x0FE363E25FBC879BULL, 0x3E603236ECFD1E3AULL, 0x30D117817C941805ULL, 0xAF6F74196946A0A6ULL, 
            0x2329F3EB8D4A8B27ULL, 0x6ADB489DE4DEAA93ULL, 0x77D20BF01C10B376ULL, 0x8B3D57841FE93086ULL, 
            0x5323327859FD8715ULL, 0x72648FE89621D7B7ULL, 0xD34A8A42F8ABA755ULL, 0x31F93565BE861BB6ULL, 
            0x06B301F73FB2A165ULL, 0x5979521065A24888ULL, 0x2D6765FF3B7359E2ULL, 0xD7A92787A25AFA64ULL, 
            0xE98BAE3AA7B3B729ULL, 0x470BD33E902D6319ULL, 0x3509F84516BC31DBULL, 0xB2E04E090ED1B4B1ULL, 
            0x752D127BCD996725ULL, 0xB20AEAB6FBD28E1CULL, 0xC1111E8ED1818833ULL, 0x9D1309B3C104C44BULL, 
            0x56BFE3108C1F9E53ULL, 0xC172F047B67FCE69ULL, 0x048E5E3CCB13CB33ULL, 0x1A41E4550F2B62BEULL, 
            0x5CD2A26DCB25672AULL, 0x99D132F9AD49DA19ULL, 0xC0220571EDB962FBULL, 0xEAFFF17A2B6D76DBULL
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
            0x915F835C5BB3C63FULL, 0x06E65141D4E20F0AULL, 0x4DAA841AAE654645ULL, 0x336C8523863307AAULL, 
            0xCFECE8A3273A298FULL, 0x9FECAFED46C1E3FDULL, 0x17E0C3A6B4AC21C2ULL, 0x420EEC16CCB67AF3ULL, 
            0x804DB2FFEA40B8A7ULL, 0x22C796D01B1E2F12ULL, 0x4D15BB55E8211B73ULL, 0x53EC0CCF98215F41ULL, 
            0x834737293C6023BCULL, 0xBA13E755EE543AAAULL, 0x4A2710DC652149F6ULL, 0xEC8907A44326CFDDULL, 
            0x59E6E31FE41AE755ULL, 0x0B8BC0F8087F3D3EULL, 0x2A7DAF34DE876F8CULL, 0xA2FE40A401D7C41DULL, 
            0xC72BE0305A9068B4ULL, 0x0DBE49E16DE09E9DULL, 0xDDBA6E5C739939A7ULL, 0xF54FAC0EA2004183ULL, 
            0x79512C51207868D6ULL, 0xE8B84E9F0D41C8D5ULL, 0x1B7ECE99DAD77CB0ULL, 0x03CDA9F22F237E9DULL, 
            0x4D4F5F02B75F4605ULL, 0xCD257367EF370B67ULL, 0x9917F24AE3359F0CULL, 0x5913F1C35D4D1FB3ULL
        },
        {
            0xB7CE63E94D625E93ULL, 0xDC47848CF105C69FULL, 0xAAE6A471A05AEABEULL, 0x927FAEAF1DBB46BBULL, 
            0xF5CCED3F7B22E16DULL, 0x93D31AAA83855947ULL, 0x8E96C7B8483C5AB9ULL, 0x280D018A55645DD9ULL, 
            0xB1453BEEDB14F840ULL, 0xFF42E9C769B854D7ULL, 0x72855277458D7B4EULL, 0xD66AA520A93D1AD1ULL, 
            0x022C2072CB6DAADDULL, 0xC29B2DBC2FF03790ULL, 0xC7297B348DE05ADEULL, 0xE7BD364C43EF8AC5ULL, 
            0x47486789BBC973A9ULL, 0x5BE0D8489619A206ULL, 0x976491DACEA56C11ULL, 0xA44296F68516763DULL, 
            0x306D720AB51B9D9AULL, 0x8FEF0ED0938763F2ULL, 0x924D559D5D3AD706ULL, 0x52B80506550E57B6ULL, 
            0x8935C0E765BF27F5ULL, 0xF88EF24CD3FCBE71ULL, 0x5057CE247DB18438ULL, 0xEE7E0E64D157A40BULL, 
            0x6FC705206E6D65D4ULL, 0x393666723FA8629CULL, 0x415145678D7888BCULL, 0x1C2BF77F5A85059AULL
        },
        {
            0xE947C4A63AC0D41FULL, 0x5235E3994B1E87C2ULL, 0x0AA2066A60DA9B04ULL, 0x557636FA558383AAULL, 
            0x8162814A7216FEBFULL, 0x5D887DAE52B65BA5ULL, 0xE422D77F67920C9BULL, 0x84B4FABF15BDE4CDULL, 
            0x65E5BD3D4C13AC16ULL, 0x3BE388F4044D64D7ULL, 0xA8766D92C0F47C67ULL, 0x684B11FAA6278984ULL, 
            0x1E729548BC398176ULL, 0x7201D928CF211C3AULL, 0x229B995884F71425ULL, 0x8164DCA447E75C5EULL, 
            0x9A51316C3B9E07F7ULL, 0x63365478F3B3FB1CULL, 0xE9594369E51BAB1BULL, 0xC7FC2FA2888FB30BULL, 
            0x6B9978CB864831B1ULL, 0xD0B5B79882E8B6C0ULL, 0x9E9BC5D05C9D8DCAULL, 0xF87A1F3F896896D8ULL, 
            0x71018C5C9AD16B04ULL, 0xA44C52EB1345D09CULL, 0x3E40CFE4951D645CULL, 0xBDC334205FA8AF90ULL, 
            0x1D5944948F0B18B3ULL, 0x771D790041DB5804ULL, 0x3DD5530452935EE8ULL, 0x0468D75FFE15425FULL
        }
    },
    {
        {
            0xD2460921934337BDULL, 0x8F593F63EC0C25E4ULL, 0x6AA714C124DC726DULL, 0x8B2B757B3DC00CE7ULL, 
            0x14AA9A167D00DBE8ULL, 0x22E01692D359D6EDULL, 0x5D94B1E5E78C342DULL, 0x58355DEBD5B87642ULL, 
            0x958670819ED4F69FULL, 0xD1CD339E2B35F4B2ULL, 0xF602915F3BD3F00EULL, 0x1C76516333039D08ULL, 
            0xC00F36B686CF567CULL, 0x15BBDCAAEA0C09CEULL, 0x5273D6A52B011305ULL, 0x7255F69F211A5F8CULL, 
            0xA700907B4FE29E53ULL, 0xBFE8AE51E2FE2CAFULL, 0x27BA7553A27C0426ULL, 0x02FE890971ABF4EBULL, 
            0xA909BDD33664579EULL, 0x395487315D0BE39FULL, 0x7E83E7F7831FEFDDULL, 0xD5F858C176C10DD2ULL, 
            0xF5EE9C5C43312058ULL, 0xDA929D6841326F38ULL, 0x2487E356A1585E5BULL, 0x00601657618A9FE8ULL, 
            0xE9E219D3E0002944ULL, 0x4CF7666FEFCFC6CEULL, 0x11512B0495401C00ULL, 0xDA552395CD0C54D5ULL
        },
        {
            0x31C49E2742D596FBULL, 0xA2BA6BB6D59BDA56ULL, 0x4991E7AE869CB554ULL, 0x9C3FF8064F8FCA6CULL, 
            0xB5E9EE1F95C2E599ULL, 0xF7FAF48A473946E8ULL, 0xAD14057D760ACC8BULL, 0x10378DC90DC83507ULL, 
            0x622E40E9BAA302D4ULL, 0x7249DD7F19D7779BULL, 0x6011493F8244CE2EULL, 0x8C88203ECDF6FD7BULL, 
            0x83932F64720F2D02ULL, 0xD41030DC9A2E2402ULL, 0x0882202FA8B3F5F5ULL, 0x1579C4873DFF3538ULL, 
            0xCC0D8CE9357D68DEULL, 0x86B77570EF56074BULL, 0xF2801480D476D6ADULL, 0x78799A355C6EC78DULL, 
            0x9D0A56317A244349ULL, 0x057537F385FC9F62ULL, 0xD3677E6EB302206CULL, 0xD72D30F15F8DDE2AULL, 
            0x10E6DE9D2D5201D6ULL, 0xEE8D6A746107E6AAULL, 0x1AB6347C283FE6D4ULL, 0x7BCA7D74FDAE9BCCULL, 
            0x2C74666C303D4FF9ULL, 0x7506F95D0383287EULL, 0x84BFB1DBC9774024ULL, 0x8720B2F4C3A6DB77ULL
        },
        {
            0x84D475D5B680C9F0ULL, 0xE879CD2439FE560BULL, 0xB99D2BF726D9BDC6ULL, 0x7C62D1B709DD3149ULL, 
            0xCC447F67D9D85ED1ULL, 0x16B5BA09B1A9C063ULL, 0x4A6C4AC63BC48000ULL, 0x7DEA32B038B61645ULL, 
            0xCFAD5A85A4ED9363ULL, 0xC62B595B0C9BE957ULL, 0x410CC04A9199FAB5ULL, 0xA391757F5ED7AF0EULL, 
            0x194685D4E975FD49ULL, 0x6BF56D8A2AB9A372ULL, 0x8B5C15C242A91EB9ULL, 0x974CF9637A947DBAULL, 
            0x7A7598B92474E310ULL, 0x50C73F4A647744CDULL, 0xAA3DC1CDF913C1D1ULL, 0x147E1D07730CC29CULL, 
            0x39F8306865517335ULL, 0xD009FE3CB382FDDEULL, 0xEB851931320375F3ULL, 0x7F7AAB5CA0CB21D8ULL, 
            0xDE344560F8EA0301ULL, 0x4BACD80D6CA09657ULL, 0x12CA7206D230D0F6ULL, 0x327FC82B42701262ULL, 
            0xE56E5747198EAD3DULL, 0xA210294E574A3FA0ULL, 0x694EAE1E50DEDA34ULL, 0x2B65DDF664DABAC9ULL
        },
        {
            0x1439846605EAFC98ULL, 0x4CE8E1FA1964D614ULL, 0x46CC948A0D60B12EULL, 0x5A27D9385F88B0CBULL, 
            0xD4AC2E509082B020ULL, 0xE8ED1C5028E48522ULL, 0xD4281A620FD8C9F3ULL, 0x035C464F14B95A5BULL, 
            0x120ADCCB7E9FF6AFULL, 0x004451E513FF1D6FULL, 0x8E3A750C2860954AULL, 0x87B320B3E3BA40A9ULL, 
            0xD7CE35273AE09AC2ULL, 0xF73C03D5ED5467FBULL, 0xA105C428BA6F1E37ULL, 0xEB956E3A1B5D65E7ULL, 
            0x76B21592A26652FEULL, 0x92B6B6467EF56548ULL, 0x4F37E323A5B8DBE5ULL, 0x8B4986B5D2DC5803ULL, 
            0xE3663AA70FC74843ULL, 0xC20824671D86728BULL, 0x7320F3FC6FCEED0EULL, 0xEF056192592AAB80ULL, 
            0x8DAD43F36C756DD8ULL, 0xF433D1FABC395728ULL, 0x0495DB3B24187DB0ULL, 0xAFFCACCE2BD55CD6ULL, 
            0x3663F6DE9CAF37F6ULL, 0xECBA46AB61FD4A6DULL, 0x4687D6A2C06809E5ULL, 0x1F8777F50BD9A2D6ULL
        },
        {
            0xE6F8031F014CC3AAULL, 0x188EFFECE1C5D0E6ULL, 0xDF27C845D5E0AF7FULL, 0x0CC0AE30CCCBE8ADULL, 
            0x97A4EEABFD340560ULL, 0x6AEF2C6D3FDDE625ULL, 0x16E37076D949F625ULL, 0xB38D8AE3EA363704ULL, 
            0xF63B5784771F5999ULL, 0x6C01CF634E036D56ULL, 0xC5C900E4C7CA2B5FULL, 0x6C410E646CFAC74AULL, 
            0x8932A8D33FA0D8EDULL, 0x6910614174258D49ULL, 0x95BFBE22D9FA10F1ULL, 0x72576A39996CDBA4ULL, 
            0xBF2F55D83A55D1C0ULL, 0x2B548966ED23B727ULL, 0x1A3FD219CCA28581ULL, 0xC4E03BD2CD3B1FFEULL, 
            0xF095A31624596A84ULL, 0x41F0928BD6842C6BULL, 0x0529921D475B97FDULL, 0x325D3B528248278BULL, 
            0x5D273A33E1B8E0C1ULL, 0xF23CEAD6D532C2FFULL, 0x256B4D31996CA37EULL, 0x2FDFE1FB37860234ULL, 
            0x23FD10D5D36789A7ULL, 0xE3BF6668583828B7ULL, 0x328083C3B9CFB584ULL, 0x5B33E8794B67EB11ULL
        },
        {
            0xBC64045C44B93D32ULL, 0xC1C8F29D7717C20DULL, 0x1343EB700DE4FCE4ULL, 0x9D1D6886C8370EEBULL, 
            0xFCD38D49140FEB0FULL, 0x7204DF06AB28BC18ULL, 0x88067E046D6CF0EBULL, 0x30FB4554551B5396ULL, 
            0x997906A3DB93B157ULL, 0x669D963DA19F1BAFULL, 0x5DDA957FBBF2AA04ULL, 0x828746D7A8AF6FFFULL, 
            0x2375E9082A1211CDULL, 0x4DB63CD6F895F0DBULL, 0xED3CB08ADC52384BULL, 0xEC8D0DA94C0F9002ULL, 
            0x15774AFECFDD714EULL, 0x2495E588755ECCD8ULL, 0x4756E74D408800EBULL, 0x6AFD871967BBC325ULL, 
            0x5E9CA8E938A07920ULL, 0xBE0F7809504AC27BULL, 0x22A577231B26D1A5ULL, 0xFB0F45C0F452C377ULL, 
            0xB857D8A3C6A4DA9FULL, 0x2EC29200000079ECULL, 0x68E2FDF2AA1954E8ULL, 0x89EB2E9AC19BB252ULL, 
            0x34D89751CED934D4ULL, 0x1E38012A73DC0C56ULL, 0xB9654FAFCC9C0477ULL, 0x859292116D9524A0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseAConstants = {
    0xA3C03E5E9BDE2C37ULL,
    0x1DE6ABFE447662A3ULL,
    0xB491B02319BB5CD1ULL,
    0xA3C03E5E9BDE2C37ULL,
    0x1DE6ABFE447662A3ULL,
    0xB491B02319BB5CD1ULL,
    0xAE6FCDBD372F75BBULL,
    0xCD561E84DA37B308ULL,
    0xD2,
    0x61,
    0x87,
    0x14,
    0xDD,
    0xA5,
    0xAE,
    0xFE
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseBSalts = {
    {
        {
            0x1B959F7478E65E4FULL, 0x74E1612962299F7AULL, 0x7BC3EA8E50ECB35BULL, 0x415DC9A867A119AEULL, 
            0xE642DBA9B90904CBULL, 0xAB9EF5D8ADF46740ULL, 0xBECC5FB7CBCF9699ULL, 0x66DF2E44994AFE7CULL, 
            0x23065F5BD327B3DBULL, 0xE3CBA11C6EA74169ULL, 0x1C81CD7BC25964ABULL, 0xDC6DD0DFD4778270ULL, 
            0xFA5ADDA732BD3B99ULL, 0x870DF007CCDC3CE3ULL, 0x7C5B6D2817350887ULL, 0x91FF54E272C48635ULL, 
            0x467586E45DDA1DFAULL, 0xBDB348AC356FC541ULL, 0xE877AEF1C3CBD2C9ULL, 0x01640AA816CDCD1BULL, 
            0x447781E6281D2EA1ULL, 0x5C6C6102BA7308B1ULL, 0xF14B953230505BB0ULL, 0x4B67D4AE01CF85E9ULL, 
            0xFEA7FE836DD3E0FBULL, 0xAAD45414E2BB6EE9ULL, 0x7C9E750E28BC2109ULL, 0xF7A7670457909553ULL, 
            0xE6B702AEF1471641ULL, 0x1ACF2969EBDC9E18ULL, 0x0DB68A905751FB0AULL, 0x602239C2E9399109ULL
        },
        {
            0xD36F32254F91360DULL, 0x886EFAD3D69703D6ULL, 0xECDA5424D68BBE34ULL, 0x315538BD8E3CE688ULL, 
            0x4CD43A26813B9F38ULL, 0x800649919E8EA152ULL, 0xEC3AA77DB68B51EEULL, 0x11DCAB20761C4394ULL, 
            0x66F34E52F6478C62ULL, 0x14E103097A9786DFULL, 0x2D1E2D761CF3471CULL, 0xA99294219C86EE26ULL, 
            0x7D63E1AF0F7DF4D0ULL, 0xFDF364B0496E4EBEULL, 0x9566704536797DC7ULL, 0x416F9878E6F7F19AULL, 
            0x1B99132F576B5474ULL, 0x6D98E4A06C392288ULL, 0xE9D117D29CB8A116ULL, 0x4670645875B5E6A6ULL, 
            0x12681A9C15F82A9DULL, 0xD5F6C131959EB0DCULL, 0xDFFDEDEF827B7B49ULL, 0x67E5A292E9D39586ULL, 
            0xD19356AC6D11F964ULL, 0x55C4C822DD574312ULL, 0xDFF23CBB3867ACF7ULL, 0x008613D04DDA36F7ULL, 
            0xD27EE8539A28425DULL, 0x4A4B6E3AEB31031AULL, 0x03A6618AE75EB870ULL, 0xAAEC3EE4C44E709FULL
        },
        {
            0x148CA5CB66B75F2FULL, 0xBC8494BE5509EC05ULL, 0xDE22ABBF7C0F11A2ULL, 0x90133C1CEBCD2CD1ULL, 
            0xDCD0F3B4AEA66DAFULL, 0x11246810757C3895ULL, 0x869B02013DCD9480ULL, 0xC30D14D9F99E99C2ULL, 
            0x5A5CB63C25363D41ULL, 0xABC86B2F0932779FULL, 0x31DF51EF9E8F0CC9ULL, 0x86083B8E117FC4CEULL, 
            0xD5DD128ABB4860BDULL, 0x7709D77ED6134B14ULL, 0xABC5E8E1CD00C5E5ULL, 0x27C0F998C28EE64BULL, 
            0xC89DE77208FBFD20ULL, 0xD857C14CD9564C82ULL, 0x4B95232933B07566ULL, 0x8AD652AD96EFE94EULL, 
            0x7555FF4B67B81F41ULL, 0xFFDB71813C17FE2CULL, 0x1CAD712FCA30C37DULL, 0xB246E4ACD826E888ULL, 
            0x0693ABBE04CE69E5ULL, 0x68902F578A937E61ULL, 0x190D0453FC5A3D18ULL, 0x98BA2E6FCC5750DEULL, 
            0x3B1E392FFC05949EULL, 0x30F49249AEAAA13BULL, 0x14A286D2FE33C4BEULL, 0xBC4EBA5379BA01FAULL
        },
        {
            0x8EAE5FF79E98B788ULL, 0x58BDAC9629301991ULL, 0x6531F6FFAE56D6A0ULL, 0xDC55F906B72FC784ULL, 
            0xCB73E051A9208AA9ULL, 0xFBE4B107E100C17CULL, 0x8F7007B68C796BA5ULL, 0xF9AE315C3D4EB63CULL, 
            0x510E14AB1CE6E535ULL, 0x24D16848D83BBBA9ULL, 0xB1CD1C36828571EDULL, 0x7ABDB6256FAD37F3ULL, 
            0x7993C9E8F32EDBAAULL, 0x359C0812D1BF1A7BULL, 0xC0254ED8ABB4B001ULL, 0xA054F20BAF3C4C61ULL, 
            0xBA90BB59C940D553ULL, 0x77A76862D01177E3ULL, 0x66294CCDD3834884ULL, 0x25F18E67DE94F750ULL, 
            0x5BDBD2FABBCBB840ULL, 0x774004E7B4B1C219ULL, 0x35601DBE2F919478ULL, 0xD442C57E5F64BCAAULL, 
            0xA141BD0B5D49C794ULL, 0xAD9BA07318455FE0ULL, 0x9F29A87951BA5E06ULL, 0x3169A1EF5F2398E2ULL, 
            0xC3585A2BC0C60E36ULL, 0xE3DA7B602D0D5959ULL, 0x4006E8B98903B288ULL, 0x36BC58D4F2B6BA80ULL
        },
        {
            0x94D74261104B841CULL, 0x4512274572FD2AA4ULL, 0x472CEB761B6B48DCULL, 0x9CC814AFCCD1E1CBULL, 
            0xA17301C4B3EF0225ULL, 0x01A580698EA71EEAULL, 0x085DB9994AB2DB2CULL, 0x1325371456822B04ULL, 
            0x6ACA93559A5C20EBULL, 0x0EB4AAA421E2FE19ULL, 0x18FF3011C2037015ULL, 0x26B980956A45693FULL, 
            0x7EC8E6096B4439A2ULL, 0xD61A5D6254C64C9DULL, 0xC3E08FAE5B5912AEULL, 0x304F69003649AE8BULL, 
            0x4CE707663D2B6C01ULL, 0x536FD49F968FFDD5ULL, 0x7F02A5923EB8A06CULL, 0xA3531A494B50B204ULL, 
            0x6CE7855C40FB65DCULL, 0x210EE18F139D0490ULL, 0x3E9B89869A697B89ULL, 0x75CEC6C0B94BBE05ULL, 
            0x1F11AEA7A84D5BB5ULL, 0xC90EF47F74D8F0F3ULL, 0x0B7F3C4D21555E40ULL, 0xA3E509F750F5D86DULL, 
            0x68FA57D62C0D4890ULL, 0x1087E02EA29FC5A6ULL, 0xFA65B3ADA00A0036ULL, 0xF5B0753C443B8513ULL
        },
        {
            0x92B6A5B09C435598ULL, 0xA91BF0492E77236BULL, 0xA5916553BCEE36A2ULL, 0x3D93C07DD59FF7A7ULL, 
            0x4FAD48888D5EFB59ULL, 0x7F520F0073E4A582ULL, 0x46EE2076AB17B01AULL, 0xEDA2C221CC995A51ULL, 
            0x92AB5D3BA5E01D22ULL, 0x856B79F5CDEF827BULL, 0xEAECFB1AD0C90380ULL, 0x4A6A7EE6EB3E0B5DULL, 
            0xDE1DBA6203BDEF33ULL, 0xF5626786D2FB44D6ULL, 0x0AAAFF77A03AAE74ULL, 0xFC02DC4B2C785F79ULL, 
            0xDA081BAF540E5420ULL, 0x47775A2E017B445AULL, 0x00AEA6F262E5A482ULL, 0x2C17BE0760509A0DULL, 
            0x7C4400C072657EF4ULL, 0x3D1AE0B438D197BAULL, 0x2DEBD08D263188EAULL, 0xF6E9DF918A3F99E4ULL, 
            0x3B21D540FBFDAEFDULL, 0x57EDE002152DCCB3ULL, 0x193653E339C7581FULL, 0x1105F80905D0BF78ULL, 
            0x39AA29C243E65DF2ULL, 0xF3C02D3D341E4B73ULL, 0xF64F3D523678E9CFULL, 0xAC1F7C2337612891ULL
        }
    },
    {
        {
            0x0AC5F7817BB77C7FULL, 0x577B0C793E923558ULL, 0xEDFCE99E1A51A230ULL, 0x7D377BC56D9503F4ULL, 
            0xD03661E329E00AAEULL, 0xDB661E8F6A60AED8ULL, 0x353086E8ECF33729ULL, 0x97F4D9A84204F440ULL, 
            0x9FCE6D89E57AFB96ULL, 0x761CABDC682E6F59ULL, 0x572751C9CB319C57ULL, 0x66E742C53ACA24A6ULL, 
            0x21A882374A7D3487ULL, 0xC16B9C484F0B1669ULL, 0xEA25D7CCE9C4BFC1ULL, 0xDA0E05734D7E013EULL, 
            0x1F697F337D808975ULL, 0x655461B4CB530F2CULL, 0x3E19643A4EA1EC08ULL, 0xEFE4CE81993D5FD2ULL, 
            0x16423D988BF93561ULL, 0x03F6AFA5D11B5C6AULL, 0xAB8A45888EF45728ULL, 0xB8DBC4C9D11FF840ULL, 
            0x194986EB829697A9ULL, 0xC5AD6282F5CC728AULL, 0xF6CB3A4C339D381EULL, 0x584E29B5ED1CE309ULL, 
            0x340BBA258F9148A3ULL, 0xF8A294E87D7C0832ULL, 0xEBC8B5A002B73993ULL, 0xBFAC1E398379D091ULL
        },
        {
            0x2CCF7C5EBDFDCD87ULL, 0xFAAC4BC2D26D1189ULL, 0xEFC3C51122CE5DFCULL, 0x61AEA0D5C7ECB2A8ULL, 
            0x34FA10847B45C76CULL, 0xCB272ADAAEEF3182ULL, 0xC2EE6F3DD7E13D84ULL, 0x549D0E7A8DF466D0ULL, 
            0xB7231CC9287F3B86ULL, 0xD68FEE6DB2894CABULL, 0x88011B8F324555DCULL, 0x669419C08AE79D70ULL, 
            0xBC6A4119E4060AABULL, 0x16BE506857E9202CULL, 0x14EE706E8B871EA7ULL, 0xBEB2EE32302F6E0BULL, 
            0x16D80DB2CFAE6B86ULL, 0xF3C24936CABF4472ULL, 0xB4E80269E0C84A5CULL, 0xEA3C09DDD9B46D4EULL, 
            0xF33FBFC5CC577867ULL, 0x433A50E1D828F16DULL, 0xAB6C4561C5621B7AULL, 0x08714027C5D313B0ULL, 
            0x17CC534F784483C3ULL, 0x40D5E597C4D0D06BULL, 0xCD936C9971B1660EULL, 0x8B44013A50D67244ULL, 
            0xAD47D52FEC499574ULL, 0x223322E676B10D8BULL, 0xCF2CC2B647CAE125ULL, 0x1F0DD392D4757B7BULL
        },
        {
            0xBC10A95900CBE272ULL, 0x8BECD16322B51A6FULL, 0x5C7FEBC2E8861C9BULL, 0x113696D0C90CBBC1ULL, 
            0xDE321176E63A21EEULL, 0x8729B732CDCCB058ULL, 0x69B1F2C0402953FEULL, 0x1513C315F3ACD392ULL, 
            0x583AD6B684E0D5A9ULL, 0x8D2612A576ED461FULL, 0xD8D4C2F3ABC1AF1CULL, 0x324503A70B96FCBAULL, 
            0x071A310A37E618B0ULL, 0xDFF1FECD78E225F6ULL, 0xD19DDBBDF90B432BULL, 0xA2466846CEF9BECBULL, 
            0xCC0096D1AAE771BEULL, 0x2364C6197669CE11ULL, 0x2AF31C5A41146752ULL, 0xB0947494FF6C71C2ULL, 
            0xBE6AA07A36097F65ULL, 0x1380175CCF82432EULL, 0x0ED922E1119356ADULL, 0xC4127536066B7D2AULL, 
            0x3103C13531C52B74ULL, 0x8F07D40FED315E10ULL, 0xF68F7D2ECDBD6A9EULL, 0x749E43C72E27324AULL, 
            0xA12B5187766427DBULL, 0xF9D8031C7E8E428AULL, 0xA503B2D3C7966F3EULL, 0x131F65D4836037AEULL
        },
        {
            0x057AFD6F7A092DAAULL, 0x3404CAC448B8BEC0ULL, 0xD580032A586A0D91ULL, 0xBC04D7A77346D824ULL, 
            0xE6761A891399AE33ULL, 0x9D5751E5B3E872AFULL, 0x03045446B0FC02FEULL, 0xE69286903BE1B1BDULL, 
            0x2471DA2E3D728FFAULL, 0x7453AC91ACADD6B1ULL, 0x6AC7C9BB59E85FC0ULL, 0x5F5D0D2B9397592AULL, 
            0x26D6283BBB8783FBULL, 0x71141D28610585E6ULL, 0x907B87FFA2D328EAULL, 0x3D3BBD331C253DF5ULL, 
            0x9B370D30B25E682EULL, 0x7FD4F2FCC1DA81DBULL, 0xD91D5F65DFBAD8E5ULL, 0x70BF46FC7B544B15ULL, 
            0xD497C5D60879D05FULL, 0x079219E7E01AA935ULL, 0x95B1B86240B0ADB9ULL, 0x5EE6C1BBB3E20542ULL, 
            0xEBFCD59C5D047E23ULL, 0x8BDE2260163ECE2BULL, 0x34DD52FC5C8A7F0EULL, 0x25CCFABC675A4801ULL, 
            0x511EE1D97A1C6DA7ULL, 0xE53B086C51427CD5ULL, 0xA1DED0E7E889BF9AULL, 0xC05CB95CFDDA68A4ULL
        },
        {
            0x9AD12A3BD3929C89ULL, 0x20BC11E8C16212C7ULL, 0x0893DEF296C33326ULL, 0x05F1DE2BD718E133ULL, 
            0x956D7F015D50F8FAULL, 0xFD527CDA1DB16A1CULL, 0x0617452FCA8FCBCDULL, 0x6D11B55F1F8DC717ULL, 
            0x914213598140856FULL, 0x0E46414D1169FCB0ULL, 0xEF4AD9B3CA69323FULL, 0xE9FF43BF740A5426ULL, 
            0x39B186480B0355F0ULL, 0x959841F78FA06B51ULL, 0x5CD2EC1C0EB532F3ULL, 0xA534E2097A118909ULL, 
            0x9C57399D2FBB3BBFULL, 0xDEDA12B6946E7CF5ULL, 0xE84DC2DEFB59C817ULL, 0x0638CA6230653B56ULL, 
            0xA1C204460814CC3EULL, 0x6FC0BC464145DC10ULL, 0x290EB8E377343E52ULL, 0x773FAD6DE6F45EFAULL, 
            0xD05F7E2306FBC678ULL, 0x1D6C1BC497284A56ULL, 0x17ACA52B83E7B242ULL, 0x41578797C9A1FE02ULL, 
            0xF19F0FD23631C085ULL, 0xAD2B8067C245D510ULL, 0xFE1946F9CB1401C6ULL, 0xCEBEAEF24626DD64ULL
        },
        {
            0xBFAE98FC4054C826ULL, 0xB078BA8823FAE2DFULL, 0x7399109F3640459CULL, 0x26D172CDC9318E91ULL, 
            0x02E73F06788075E2ULL, 0xCB549625D077E1E2ULL, 0x4E580E0F1A7D113BULL, 0x26EF6E41B4693F68ULL, 
            0x97AFD086A3E7B53AULL, 0xD46D650C0DB6AA28ULL, 0x5B0F9A1311FEEFF1ULL, 0x7544EF3E3ADB1FA2ULL, 
            0x0BE7182C7C33F2DBULL, 0x632EE5F3205BE776ULL, 0x0FE9D08E6275F501ULL, 0x17E90C9125FE07D4ULL, 
            0x5AA1F718C6F53ADCULL, 0x6978E1616D97ABE3ULL, 0x685DEA8EDF25DD3BULL, 0xC11969287AEFA6FFULL, 
            0xB810A34A73393CE2ULL, 0xD00A2818E221A5CBULL, 0x69E4C286DC1DCD37ULL, 0xB3F7FBDFB7C41401ULL, 
            0xE33258F2793000D1ULL, 0x228D7D03BC9B70DDULL, 0x12861C456580FCA1ULL, 0x7FBFF588BE6A2232ULL, 
            0x14DBFDB390BF3A5BULL, 0xE3E3EE4A0D728360ULL, 0x24C41D18D8D472E8ULL, 0xAD185E019F262332ULL
        }
    },
    {
        {
            0x0C149595566C1CEEULL, 0xEE5F4004FB02BBF1ULL, 0xF44766AB17A7E3A8ULL, 0x14264180608E3065ULL, 
            0xFF848395A24F44F6ULL, 0xB805EE6FB375BDADULL, 0x648EA68CE438511DULL, 0xAF54CDA4A423D529ULL, 
            0x5E1494E8CE33B6C0ULL, 0x28424F761F780730ULL, 0xA17AF02C36E20A45ULL, 0x1AB0393471678F01ULL, 
            0xDFCCE20343C18178ULL, 0xC145AE5DFBA6E230ULL, 0x8C8D896007637830ULL, 0x2B778798E05A2B8FULL, 
            0xC48A4F2D53C5C34BULL, 0x5741B78735041248ULL, 0x02FC1259A9D30F33ULL, 0x86DC15AB4B4B00AFULL, 
            0x3552E59694125671ULL, 0x5AFD674BA7A5B6F0ULL, 0x60CE06B4B60D8148ULL, 0xFCB00FC0C823D64DULL, 
            0x2F43AD07D5995791ULL, 0x571323E573FC561FULL, 0x46F3FE79DDFEA377ULL, 0x889C2BA2E618E2BCULL, 
            0x732D1FACAF1C89BFULL, 0x8D3E98B75DCBA4EBULL, 0x33D45B1EAA2888C5ULL, 0x228F173E4E1D4D9AULL
        },
        {
            0xE4B223A1C4E22BFAULL, 0x561F5DE41801A7E1ULL, 0x6C67D1133CAA29E5ULL, 0xA4BD0FE071AC46EFULL, 
            0x30CD118AED0DD59CULL, 0x58EA6D00DB6B659FULL, 0x085D6932DC470207ULL, 0x3405EDB4836E03ECULL, 
            0xA82A1F3A151EF384ULL, 0x5F6F78C6E8B84909ULL, 0xB0D1D886C949D003ULL, 0xAC2BAF0508BD0C63ULL, 
            0xD52C5D0185445C46ULL, 0x21251F7B110E8CDDULL, 0x20A2274C2912A31DULL, 0x7CD877799A748E7BULL, 
            0xCA36008A0ADBDDB1ULL, 0x87E98A669A1E36EDULL, 0x8B5B1E23F5EEB6FEULL, 0x2FDF7E76DAFA514AULL, 
            0xC59E9F508D55ACCFULL, 0x835FE190EA8C8246ULL, 0xE1C8C7D66C924761ULL, 0xB20BEB008610B8B4ULL, 
            0xA8813B8B3AB4B037ULL, 0x8E0A8C59154ADD63ULL, 0x57700F8D7B24875AULL, 0x7D96932AA62E945FULL, 
            0x3DEF8C3DF57BF327ULL, 0x69646A57B5461305ULL, 0xA3E7A341AA9921B3ULL, 0x2EDAD3171DDEF1BFULL
        },
        {
            0xC0EB03B53F124435ULL, 0x2F39696BFD0762CAULL, 0x38C9032644BD5231ULL, 0x7D3E89FE4313A5D3ULL, 
            0xB8689F3B676EC50FULL, 0xCA8E523E54DC9F36ULL, 0xE66505015A5A4972ULL, 0x5357E1A4209B85F3ULL, 
            0x05AFBEC028D9F748ULL, 0x3299EC98538B6809ULL, 0x4A5E97AC51E9FFD8ULL, 0xCC31655FE629611FULL, 
            0x238B40AD9DDBB1BCULL, 0xB9008CBD35A62FEEULL, 0x861B6934DD3D5191ULL, 0x70C98A899C98989BULL, 
            0x2C0AC1F18833B46BULL, 0x81A0CE31996DFA88ULL, 0x9B5FE5EF59A11232ULL, 0xE78273C4A11F8517ULL, 
            0xF92067790BB4E832ULL, 0x1214DF46F4A26784ULL, 0x1870BB6C5DCC1FBFULL, 0x568B8E1A7103990FULL, 
            0x649B4C298734D81FULL, 0xBA6BF009FC14E187ULL, 0x043B0327755D98DDULL, 0xF8D2ED0522EE561CULL, 
            0x3607032A6FEB35B6ULL, 0x00CF6B84FF1B8C33ULL, 0x8E84EF5CED8FC5C4ULL, 0x8C5671F30ED11390ULL
        },
        {
            0xBCABA252960E5D43ULL, 0x1D27223285617A2AULL, 0x1728E4E3092BAED6ULL, 0x6ADCD8AD058221E7ULL, 
            0x31B8311AC0917EBBULL, 0x3AB06AEBE92E6B75ULL, 0x4C3A422E5B37CF95ULL, 0xC7D881CC1C46161EULL, 
            0xD16E58B6C3920EB9ULL, 0xED32B54477E178CEULL, 0x768216F6589FF2ECULL, 0x0287CA860D7E09E2ULL, 
            0x01C8E20292DE56FAULL, 0x2F09B51C2EE0091CULL, 0x167A9F57BC4DA469ULL, 0xE56ED446D62C2499ULL, 
            0xA36589A091D0CBCEULL, 0x4DC0FF7DB07421DFULL, 0x7D1C442CB7A472E7ULL, 0x39A5437AA0E8FE24ULL, 
            0xB12EA5D0E98D1142ULL, 0x6D7B84FD57CEF79BULL, 0xE1648540BBE0590AULL, 0x32F8BF90318A8F39ULL, 
            0xC466FB7440F272BBULL, 0xDCF62C3CC7996B22ULL, 0xD6765814C129CBF1ULL, 0x0A15E1F4FCCF0044ULL, 
            0x8B6A51A5B97C6DA7ULL, 0xFABDE390D61E7A30ULL, 0x61EC87B65BB8B6F8ULL, 0x57E2E86D70395293ULL
        },
        {
            0x7F4E0496B30D03F6ULL, 0x968C0D772BD258BEULL, 0x450B0B2AEBE1B658ULL, 0x5454AD76930BEBAFULL, 
            0x90158A43EE4AA861ULL, 0xE56A541ECCA6A7CCULL, 0xDA3565B90F5364FEULL, 0xC9F92FD015B75212ULL, 
            0xD9065056B3BC60D3ULL, 0x565DF9B21CDB6521ULL, 0xB216DA79FF7E89A7ULL, 0xC19242B4DD5A0C0BULL, 
            0xC9A5AE4CF377053CULL, 0x636E37F247EBB161ULL, 0xA8FF01D520C71E17ULL, 0xA8080ABD9FABA0E7ULL, 
            0x4DC79BF2864C72EAULL, 0xA5968033A91F1EC4ULL, 0x6926FAB379C6C176ULL, 0xFB4E2531BB95FA13ULL, 
            0xEC238714CD90ACFDULL, 0x23D40D279007A6C6ULL, 0x513C649598F559E0ULL, 0x4EB09524AEF48382ULL, 
            0x5CA6811C1235AEFBULL, 0xD5B1D992C20EF67FULL, 0xEE125EB58788A048ULL, 0x77B61CBAA616D26EULL, 
            0xD28023436214B937ULL, 0x1C8E8D20AB26C971ULL, 0xD45E0B831D4E8402ULL, 0x850A404FA5F4F587ULL
        },
        {
            0x4749A23A3F601011ULL, 0xEDB2BB9CA9BEBA59ULL, 0x7730D41C9EF9F5F8ULL, 0x29983029947FFEF0ULL, 
            0xBFA8371E07DAE465ULL, 0x9376558640831F9BULL, 0xDC9175232A1F87F9ULL, 0xCC47FEA8DFF1C547ULL, 
            0x280A219E99CF8112ULL, 0x97D049C43BB24935ULL, 0xF0D0F5B41A95737DULL, 0x5128F052AE335BFAULL, 
            0xBD171F4456AE0DA9ULL, 0xF848882CB8156B90ULL, 0xA92AA41703A6ACA0ULL, 0xDCC6E3B4BA4A0233ULL, 
            0xD7AB96B9161AE512ULL, 0x297D7E6F6BA35EE0ULL, 0x8926B1E184250D19ULL, 0xC31C5B933DA556B9ULL, 
            0xA2C68E7DCC5B1121ULL, 0xE8DAC1EE3CD6FD09ULL, 0x050D4B71659E4D09ULL, 0x1A144E4934783E01ULL, 
            0x217EC8072BA27C38ULL, 0x13B3FDC469526A67ULL, 0xE361FEC6A42D4082ULL, 0xD7488CD31DC08931ULL, 
            0xD420FA19829FD0DBULL, 0xA9837D061634DCAAULL, 0x1B33EE9421F67AEBULL, 0xF996F79E915B5191ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseBConstants = {
    0xF9B310E67F7BD768ULL,
    0x9138287D1B5A74CDULL,
    0xA4D7DF9C83F6AB5FULL,
    0xF9B310E67F7BD768ULL,
    0x9138287D1B5A74CDULL,
    0xA4D7DF9C83F6AB5FULL,
    0x5D79B01B201D52CDULL,
    0x7B2A4EB885436021ULL,
    0x48,
    0x9A,
    0x53,
    0xE8,
    0x20,
    0xDE,
    0xF8,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseCSalts = {
    {
        {
            0x707B9FB49B1DC2FAULL, 0xF0F5BF54699D1E4DULL, 0xFEF9F72C7D979E7BULL, 0x46BA5B6D755136D1ULL, 
            0x5C5FE1811A3B3BA7ULL, 0xA6E512DB553617D6ULL, 0xDF8CAC3C149B5EBBULL, 0x4B16BFB12CA516B7ULL, 
            0xBE16026C22820939ULL, 0x1A7B8EF71C3EEB01ULL, 0x0A7B17E1AE8DCB19ULL, 0xCDEE5BA069D91F11ULL, 
            0xB5752F7C139D3EF0ULL, 0xFE3186BAD262DC3BULL, 0xA268681EA807DA6FULL, 0xF442274359B36378ULL, 
            0x9F4464F65F731BE9ULL, 0xE402D9559204007DULL, 0x389E439F5B4DA270ULL, 0x288E47118BF75696ULL, 
            0xBB15FD5455ACA300ULL, 0x91CE59E6E7AC82CFULL, 0x60883853635EA61AULL, 0x5780E1CE18FB489EULL, 
            0x8CDC2C5D349BFF57ULL, 0xD50C95F9A43666F2ULL, 0xF9F6B48E5F7F6F00ULL, 0xFF8D565024AFE548ULL, 
            0x058147F7EF5B862AULL, 0x81BC9A3A7FF0A9BBULL, 0x4B948CA38796DC55ULL, 0x20548D4F974981E9ULL
        },
        {
            0x538E43F383941FFCULL, 0x9899AA4210FA1530ULL, 0xFD3FA837FD14F0AAULL, 0x980D0ED8B2E52864ULL, 
            0xE93833618F5B4658ULL, 0x97FA6D3C7FEBA695ULL, 0x36B6FDEDCACFE923ULL, 0xEDD904EEE3AE663DULL, 
            0x4C801CD40471E96CULL, 0x3847560648DFBFF2ULL, 0x421F32005FB640DDULL, 0x369B7BD3BF6A5CF0ULL, 
            0x8274DCD120E2ACDFULL, 0x137284995D910D7AULL, 0x61D5441C78C6D723ULL, 0x3BECDECE4E9CBE5EULL, 
            0x80445D3E8D18BBD6ULL, 0xB6956EB49381C3B8ULL, 0xFDD6B13F3376ED11ULL, 0x1A19D9713565C0D8ULL, 
            0xABE92D7DA5B48600ULL, 0xD20EB8B1EDA8B8A9ULL, 0x22809842E9FC7060ULL, 0x91DBCD21F0B3E691ULL, 
            0x85E618228BD05C76ULL, 0x8A55A31C6A41D42CULL, 0xB6BDD70A796A17F0ULL, 0x8E1B8C637D677374ULL, 
            0xEA4762877AD4F2D8ULL, 0xA5F73CB72E3BA623ULL, 0xC1CD39AC3E8C8844ULL, 0xE417625430A3B991ULL
        },
        {
            0x01D97485238E8027ULL, 0x2A96FF2878C718F3ULL, 0xB376E4244968B180ULL, 0xDB950D0EF15D4AE1ULL, 
            0xE020AE78F8F71351ULL, 0xAF0FA5D4FCFB1B56ULL, 0x61CBFF27AA8B6463ULL, 0x42A5606561BBF89BULL, 
            0x4D95820F9B833D88ULL, 0xC4B5FCBCD20A82D9ULL, 0xC43D71438FF5CBE1ULL, 0x77A90872F3E115A3ULL, 
            0x3A50D3306D3DDAE2ULL, 0xF844DEBD1A752851ULL, 0xC3367A9D0CD08493ULL, 0x32F0B72027E55251ULL, 
            0xADA1EFBD7508E561ULL, 0x907166D1D8476060ULL, 0xA0A1E580122A81A7ULL, 0x74FA5EDD8B69D1EEULL, 
            0x9EFEF8A65AC3F91FULL, 0x06D4A6DE62411236ULL, 0x0A2B853306C0378FULL, 0x219E506B368A8E6EULL, 
            0xE5EB8034D6996A01ULL, 0x6638B328FE19C4CBULL, 0x45718222A5C9D69EULL, 0xFD52F7BE2CEC8865ULL, 
            0x0B394289ECBF790FULL, 0xB9B8F4FBB7D1148AULL, 0x3623050123200932ULL, 0x01AD25A09A0F6965ULL
        },
        {
            0xCD3A8B36217C4207ULL, 0x75911A5BA9E5D9AEULL, 0xCD47DB11DC83A96BULL, 0x903CF963D8FF8D19ULL, 
            0x06C50D0EB71A4002ULL, 0x0B0950C04D6EB1C6ULL, 0x2F40BA01AF304DA4ULL, 0xA10393DBAA73F6CBULL, 
            0xDC86E1FA79966EC5ULL, 0xF1B598B855BFDF80ULL, 0xE84856C0EFDCB1DEULL, 0xACCCA069BEAD33D2ULL, 
            0x6F8239D9055407C0ULL, 0x5827A7818501403CULL, 0xE888C3C3637AB5B2ULL, 0xF8F5E940A74222BBULL, 
            0x437A1358AD50FCA5ULL, 0xE76C01EAECD38059ULL, 0x5511910EB6FE25B3ULL, 0x1946CDDEAD6D3765ULL, 
            0x4E28E3608450AD97ULL, 0x4608D78A6F6AA545ULL, 0x9BE35B6B67102219ULL, 0xAC6C8D52B570304CULL, 
            0x7EBB2D6ED4ACBDEBULL, 0x6ED1F38A356CBD35ULL, 0xBCE9E82199B7D06FULL, 0x14DDA462784F2F3AULL, 
            0x59594D4C0F564CF7ULL, 0x6AD42B2AA5807A2CULL, 0xDBB40C40F97BA334ULL, 0x00DEA04C3AA547D0ULL
        },
        {
            0xD209159E364DEBA1ULL, 0x4E0973DA8357057AULL, 0x095E2F9111A5F7A4ULL, 0x64792463CA01FBAAULL, 
            0x873A0C1E96910EE4ULL, 0xB3BC21E0A3F5D9E7ULL, 0x857E84B86180491CULL, 0x6DE631B7FE8E7AB9ULL, 
            0x0D2177A937FCEA2BULL, 0x0B209B4225588730ULL, 0xDA2BC621AA4E6F4FULL, 0x55CA7E87DBC611CAULL, 
            0x19A6643C17788F95ULL, 0xB4F7BEC3641ADBCFULL, 0x2D2A9B896D2663FBULL, 0x711E496CE4D5EFDEULL, 
            0x1E4EB700BFD657D0ULL, 0xD554D57B4AE6D7A0ULL, 0x62391B44503F6BACULL, 0x312D6C4F7087B7DAULL, 
            0x3E3C85B6171B8D1CULL, 0x68D334C4ABFFC502ULL, 0x153359139FC0FF10ULL, 0xAFAB5CFEB7F79D4BULL, 
            0xF54D7B0B1D1613ECULL, 0x4C2D5BFD2556AB4CULL, 0x3EFADB201CB79B37ULL, 0x4E6D4D81C6405A5FULL, 
            0x39ADF05DD7036E40ULL, 0x1B7B61856633CD6FULL, 0x6C27D7F906D517D7ULL, 0x67B6E1BD3AFAC7E9ULL
        },
        {
            0x2F762838FBAF25E4ULL, 0xADDE90ADD9DEE80BULL, 0xD162A80BB2D50670ULL, 0x669758D06879DDB3ULL, 
            0xA275D2E33D27A455ULL, 0xA60FAB9922DA543AULL, 0xBEEE1C01A8EA1436ULL, 0x6702F37C508031DDULL, 
            0xEB4D073B225DD710ULL, 0x13AEF50F6212A353ULL, 0xAAB714854339D19CULL, 0x1388EA2FB592AED3ULL, 
            0xF1AD147059067153ULL, 0x3FF53F271AB25843ULL, 0x49CE3DF5581C3048ULL, 0xF986E6349503B883ULL, 
            0x49F92386547F9505ULL, 0x635CC5E2548D9BA1ULL, 0x921A0DC403003FD3ULL, 0xF35646EA833DF876ULL, 
            0x38C4A73194F4BB61ULL, 0x58AD4F0CD3376422ULL, 0xF79F2133606EB553ULL, 0x32B03DBB2FAABFE8ULL, 
            0xDD813D10A53043ECULL, 0xF3315A4562D55F48ULL, 0x4D2E25C60CAA20CDULL, 0x1C253B63CBDCC462ULL, 
            0x15673492AD1AFE61ULL, 0x2A10883AA3616371ULL, 0x132191D18F646D2FULL, 0x27B971D9B4CEF412ULL
        }
    },
    {
        {
            0xD3EC27175B3EE96CULL, 0xD4087C96EC5CDAFEULL, 0x0DB49811F0D3416BULL, 0x166E9A404D1054B2ULL, 
            0xC98BEFAAC9703A52ULL, 0x87ED86DA1F6EDB4BULL, 0x635D17D68D5E808BULL, 0xF32FBCE9C249E136ULL, 
            0x760EDE052D343D6CULL, 0x9D70FDAAF8AE92AFULL, 0xE3399F2ED3300C34ULL, 0x4FE89D78C59C7B58ULL, 
            0xCB36D1E83485D1AEULL, 0x447D8791153E0240ULL, 0x01627C49A22A1591ULL, 0xB23B13C8C4D2620FULL, 
            0x608944DDC3243A70ULL, 0x9F22BBF675381B7FULL, 0xF6B0F9E1454FE91BULL, 0x6897CE5E21D837B8ULL, 
            0x4322D3DA44730CA4ULL, 0xC7D027E36B4FF8AFULL, 0x8148D6E3BB89CB2CULL, 0x0FE334E461774F4AULL, 
            0x4AC0E2B63B7E51BFULL, 0xA03BD845004E4356ULL, 0x6E102F797EB1C2C0ULL, 0xC5047D19C687354CULL, 
            0x5646A9F597919921ULL, 0xD3BD7D85A0CAF960ULL, 0xDE055C968300F7FEULL, 0xD3F6C5A7C56D6A31ULL
        },
        {
            0x47DCB32413D05580ULL, 0x43E45FBA222E81E6ULL, 0x5D691166496E964BULL, 0x4DDFC0120880E732ULL, 
            0xEBC42B52038448E8ULL, 0x3D71BB8CF41E4855ULL, 0x25ADD469AA8ED6F8ULL, 0xF18488167F4B185AULL, 
            0xE11F156FB11F5654ULL, 0xDE7E64BFA2C5558CULL, 0xD6793753FD9E022FULL, 0xA4AA5AF59B05D298ULL, 
            0x7B2B17645410ED76ULL, 0x46403F2AA435C813ULL, 0x30935B30839241C3ULL, 0xE7D45C7FFBF82EEBULL, 
            0xCA584644E74E1C3DULL, 0x94B03B135ADF7C4FULL, 0xE3DF23619644F006ULL, 0x4148839F7F60C303ULL, 
            0x2E9424ADF5BE3F16ULL, 0x8C51CF01B22ED61DULL, 0xFB45981E0CD144A6ULL, 0xC2C768B12412F5A1ULL, 
            0x27E314EC77A0A020ULL, 0xDC54EF4C3E74979FULL, 0x9DAA15761F09E639ULL, 0x10D33C8F63ABA1EEULL, 
            0x91DC300E0437B946ULL, 0x64E782B5F00F7199ULL, 0xF696A75B2A012C09ULL, 0x52DC3F37F0D1CE6EULL
        },
        {
            0x814E32CEB514CB84ULL, 0x948DAEFF10ED3840ULL, 0x0950E1D020C8AA50ULL, 0x91F807404078F537ULL, 
            0x0D463573FF5E4A74ULL, 0x05E1DF24F683BA94ULL, 0x68B43059CF513A8FULL, 0xAFB61DC97C91E952ULL, 
            0x69FCF6079C13B9A8ULL, 0x5B3A04E93FD64F97ULL, 0xA3B692D0A37A0AA0ULL, 0x4E45B1FC32FEFB0FULL, 
            0x7341DB610790F3F0ULL, 0x18DE17BF297A9DC2ULL, 0x0A6BBCE13D3CAD64ULL, 0x9C4BA0554164BB92ULL, 
            0x31CA0D23E76FC588ULL, 0xC13A4171B143A56EULL, 0xC715E7FEC8CFABCFULL, 0x63946523DBC5E9FDULL, 
            0x5BAEBB026C79C847ULL, 0x71E734DCB1B87290ULL, 0x988538D46291FEAEULL, 0xDB81FCB346A90777ULL, 
            0xB51589A1D1BA8B4AULL, 0x40115DFEB36599FCULL, 0x16FABF16CE36A8A9ULL, 0xD56CE90999B59EADULL, 
            0x4BA5FFCB26350223ULL, 0xC75C2AFAA31B8DEAULL, 0x8CD904191D2D3C3CULL, 0xB365B09BCB3C436AULL
        },
        {
            0x0BDAD77604CBAAB1ULL, 0x19D4EDD356BBCF9CULL, 0xBAD80BBE10090397ULL, 0xFB432F798FC34697ULL, 
            0x3972444C16CA6894ULL, 0x1332FB0668A4339EULL, 0x5C6363FF5D531205ULL, 0x2A6B7F5AACB0BD3EULL, 
            0x6C972A7E1FC68D2DULL, 0xF24A872798C2C54DULL, 0x7AC516EFC5DFB7C3ULL, 0x4D04028AD7086483ULL, 
            0x60D2BC8AA7523B0DULL, 0xE7D69F9C6E1A22E0ULL, 0xAD0D32A94155780BULL, 0x5E95FA4A288F950DULL, 
            0xE44B66CB64BE9D61ULL, 0x5C6275486952887EULL, 0xC9D36CB4868EFBD2ULL, 0x37789B780FDB6FBEULL, 
            0xEC99804226DDE258ULL, 0xCB8FC45AF30A54B6ULL, 0x7346CF396F035D4FULL, 0x5F2B4BBE61650A97ULL, 
            0x085AE63408F917F0ULL, 0xE502062741DA7334ULL, 0xA9CC1610359BECC0ULL, 0xDF7ADF7E10109C28ULL, 
            0x4BCC4AE357C68B8DULL, 0x932E6E36ED1E8AB2ULL, 0xD9FECEBB730FCCBCULL, 0xB21EAEBA289FC8A8ULL
        },
        {
            0xFE9492B01D95EFACULL, 0xF17D2FF9D543928EULL, 0xE2D8A26B83A42E64ULL, 0x86C50DC97D11DACDULL, 
            0x0E7A8B03FB477585ULL, 0x2A7D08D4026AC432ULL, 0xEB463A101E67299CULL, 0x53ABBCB36B048C22ULL, 
            0x0143673C67992D96ULL, 0x5A314543B77B4D4DULL, 0x2BBD5467D798FDEAULL, 0x9EAC6EF974C02856ULL, 
            0x7E06ACC82E4372A9ULL, 0xF9DDEAE822419F20ULL, 0x35C19EA835AC5562ULL, 0xCA436900C4CB8DA1ULL, 
            0xFF65239E65BDF5CBULL, 0x67BB32BC7209E7DFULL, 0x09DF46BDFC0D3606ULL, 0xC14F301D83C9FFE1ULL, 
            0xC1814FE7D79DCC1FULL, 0x31F350B200A4338FULL, 0x316DB042AB7BD769ULL, 0x1F678B36E448912BULL, 
            0x555F90C52834F2C7ULL, 0xF5C05A0CA313FD80ULL, 0x9FC619940DF5B087ULL, 0x36E62B569B41EC48ULL, 
            0x47779A724BFBF64AULL, 0x15AC3C034635B23FULL, 0x30955B9B175CAD66ULL, 0xB06C66D0FF8D35A4ULL
        },
        {
            0x433448F9C465AFA0ULL, 0x851EDF35F7EAAB24ULL, 0x97BADEEDD84A69C9ULL, 0xA942BFD63145B890ULL, 
            0xE5619E3BAA44C681ULL, 0x745A5B00BD2E6484ULL, 0x97B5C8C4A010F61BULL, 0x07F8ADFDBA9D78C7ULL, 
            0x0D394F4E3F4B1DF9ULL, 0x9110716D56140C27ULL, 0xE82B0F62B7071E61ULL, 0xB05DCEB75A4A4058ULL, 
            0x229C5CB1EACE7163ULL, 0xB5FFF914C4835A47ULL, 0xF5729158636CD7E9ULL, 0x72392A698F642CFBULL, 
            0x57DA4ABBF302DDE9ULL, 0xC6E34E39471461B6ULL, 0x08290D8127540C0FULL, 0x7DDB58095985B503ULL, 
            0x6F2B12E71EE6F007ULL, 0x3C27D363B5198227ULL, 0x8F53700A8C883A14ULL, 0xE59C195B84DA203AULL, 
            0x546AAA7B86913016ULL, 0x5E48A700B37A584AULL, 0x0D5F2F85222CB9C4ULL, 0xE8453C1D6AA53DE3ULL, 
            0x8EDDF8C35A1119EFULL, 0x8436242874BC5064ULL, 0x7BA9882FD2111B2CULL, 0xB7043E5CC26E5D38ULL
        }
    },
    {
        {
            0x41BB3225B78DDFABULL, 0x3E4CAF51C247DC1CULL, 0x88CD232133C8C891ULL, 0x76B6D63318AC481CULL, 
            0x97ECD4444560820DULL, 0xAB863736EB6C13DBULL, 0x6A6B66148D000D55ULL, 0x93F4C4A0055EA04FULL, 
            0xC6E3004FE3FCACC3ULL, 0x1E7C5D9F5C71A8A2ULL, 0x9F894D355B115B04ULL, 0x30896BD2B0F1A4F3ULL, 
            0xBB8BBC62E7ECE7AEULL, 0x7FA5B11484A91E21ULL, 0x8591C7E50D621CC8ULL, 0x8CFE62A680E05E03ULL, 
            0x9FE598A593D06EC8ULL, 0x7FD7CD025674DAF4ULL, 0x130883461F82375DULL, 0xB2BF69CE5E1142CCULL, 
            0x9C859E7916BD2D47ULL, 0x187DC9BA26DC73A2ULL, 0x3F2D83BF9D66CD12ULL, 0x5C48C7DBBB0663F5ULL, 
            0xA011E78DF02C6F51ULL, 0x6FE948766260F4F3ULL, 0x1D4B655864244DB7ULL, 0x7DADF4DC6D508F12ULL, 
            0x198E724E435AD610ULL, 0xE9E5FA816A63F1DEULL, 0x5055E25FCD9779A7ULL, 0x177F06DAEA9EE1E0ULL
        },
        {
            0x949F56CB2437524DULL, 0x783AE2E8A9067CF8ULL, 0xD1D86CC9780589F6ULL, 0x96F364EF6F9ADD20ULL, 
            0xE907B001A0E602BCULL, 0x89FEA79A37587B27ULL, 0x7C6815ABDBF42F76ULL, 0x47A90E5249DFF8B8ULL, 
            0x4CB1443E630688D4ULL, 0x26C5BB9EF9CF36F2ULL, 0x7CAEB948469864C0ULL, 0x05A09F6A89551996ULL, 
            0x4DA3FB08D9433045ULL, 0xFBE12C4C6210CD01ULL, 0x6731FC171123238BULL, 0x0BEB30080DCBDEA3ULL, 
            0xB9571BD2611705E2ULL, 0x69DA608D1CC8BAB9ULL, 0x9E267F4BA79138C4ULL, 0x973CF7AC59F7B66DULL, 
            0xF9EFE8FFB42D624AULL, 0x3A5B8EE5F5F05505ULL, 0x0D9601E9D09AAB09ULL, 0xA95470B3D9F6F1DAULL, 
            0xD5E2BD6E1F62B97EULL, 0xE0E6D38DBF308E0BULL, 0x525B086396C99619ULL, 0x048C81843ACFF122ULL, 
            0x30003376E7C5A8D7ULL, 0xC9ADDA1F1207AB48ULL, 0x0B484FC2C0549AF1ULL, 0xD3C05AAA9182F07DULL
        },
        {
            0x9FF6DA9B55C20A61ULL, 0xB1708D0AB4FEB43AULL, 0x817EA262B8F4C433ULL, 0xEBFBA6F5400A1AE0ULL, 
            0x8CCF832E8FCA7CA0ULL, 0x05090F6AC742740AULL, 0x70C0E9B994135457ULL, 0xD834331511C1A16FULL, 
            0x2F8E3053DBF530F4ULL, 0xB8F582C4504DBA6AULL, 0xBFDDF6441132124AULL, 0x10287F1B2DED3596ULL, 
            0x3F17BE765A17AF42ULL, 0xF1B512C0127B7B58ULL, 0x40F61508BED00779ULL, 0x3216200EC9E02A86ULL, 
            0x5FB2F7487CF04DE1ULL, 0x77DB09C9A82CB06AULL, 0x022A3E1B82D964C0ULL, 0x0C7FE1D1B20DA71EULL, 
            0x8BDF464E4989C2F9ULL, 0xC875B5F3841081DDULL, 0x388A1E41E818FF20ULL, 0xD48F2F607CAAC031ULL, 
            0xCAB7A52D292AB88DULL, 0x81ACAC305E31224DULL, 0xA980A99D55708DEAULL, 0xD8C763884A72B75EULL, 
            0xA6D915C14C5942E4ULL, 0xFB027A61506D0B4FULL, 0xE408A9EDDE2E560DULL, 0xE07D2C22CA13C5E9ULL
        },
        {
            0xCCB874EDA9724050ULL, 0xF56B7A5DEAACAB41ULL, 0x518BA6BADDDE57D8ULL, 0x3B3B340E5128CF97ULL, 
            0x26EFF43CC8D79866ULL, 0x0EA3882CF55202DBULL, 0x426BBA55C2EA282DULL, 0x8025DF9A31B93CA4ULL, 
            0x14EE322D0A515133ULL, 0xE2999F96B4112D31ULL, 0xEE714661C8B46992ULL, 0x7B7B21A8F48FA7F3ULL, 
            0x92909032629D472BULL, 0x8EFD1C9B0456A606ULL, 0x043EA1617D0062F2ULL, 0xDE458E851AB6AA81ULL, 
            0x497E7FACC09636F4ULL, 0x39C98EBAF81B6BEBULL, 0xBE1DBF85B650A724ULL, 0xD2B14BC5A408BC30ULL, 
            0x0C18CC149C92C7A8ULL, 0xEDD988309D48544FULL, 0xD89F84223165BA33ULL, 0x6A743AE631CE8DF6ULL, 
            0x7CC2B699128D294FULL, 0x72CE6BB58F7996F8ULL, 0x69191E4AA1DA3A26ULL, 0x7A442ED2BA08A2A4ULL, 
            0xD4794A65F17BD711ULL, 0xB1EFAB78B8F6204EULL, 0xA079AA36B8394959ULL, 0xFC884B27BDB36B2CULL
        },
        {
            0xC1B72C9473921213ULL, 0xB861ED949D155AA2ULL, 0x87DBECBDACB39D1CULL, 0xBC76B709C8D4CC14ULL, 
            0x37DA62358A7B6384ULL, 0x03136A2E0621F82AULL, 0xB27CC3FA7BF1B2E1ULL, 0xBB1F1C7D778FAEA6ULL, 
            0xB215EB2AA5009B7AULL, 0x5F7BED78D6BF85EEULL, 0xA16DC32A6799CD37ULL, 0x31CF6EB79D5BF9A8ULL, 
            0x4180F7806A134A38ULL, 0x5742071952CC44BDULL, 0xAA889D515072BDCAULL, 0x2464692126A121B2ULL, 
            0x2E9052F09500D348ULL, 0xFB09C250DA72E66AULL, 0x1D498F80C2E5FFCBULL, 0x2CE1C563B39F1E37ULL, 
            0xA5D659B4622251F9ULL, 0x7735C299D4886B06ULL, 0xB5CD898AA1EAA9F5ULL, 0x717597CF05947B36ULL, 
            0x9384C3B97F68CA58ULL, 0xE3AA48C2974CE561ULL, 0xD4615DF5C7A4D771ULL, 0xDC4F9363DF9E6E22ULL, 
            0x81E5697C18571789ULL, 0x15D43A30D84FF882ULL, 0x31818D531E071C6DULL, 0xBBC059434D07A8DCULL
        },
        {
            0x41BD1950D1B12681ULL, 0x4892F366F676372BULL, 0x133BFBEF4DB27317ULL, 0x45BEABFFD1B2C7F4ULL, 
            0xCF98801430AA7D03ULL, 0x150945D2EA91EC3AULL, 0x63542B9C0D0E3ED3ULL, 0x6C7AF2763363185DULL, 
            0x433BD1E7410D4E8EULL, 0xD77B23807DC920E6ULL, 0xAAF1959989536415ULL, 0x3EF6DEE033C0FBA6ULL, 
            0x61F92F036F8AF844ULL, 0xF92F570237B0EE1DULL, 0xAB84611B68849974ULL, 0x403416F23EC12448ULL, 
            0x11CED78119A3E27FULL, 0x1CEB177A835E4CA6ULL, 0xE40C1B8646A1DDCEULL, 0xCD8829586B35C390ULL, 
            0x58873561747A184FULL, 0x9D83C4F47B875B0AULL, 0x65DC1AB5D05E2B16ULL, 0x5F3F04C7C3A0642EULL, 
            0x52065A16D35B7574ULL, 0x78A6F661A5E64B2CULL, 0x2C1F92E79B9B504CULL, 0xBEE3B56D9CCDA63BULL, 
            0xE8DAFB44C0EB0833ULL, 0xBFF5C492A97FADE0ULL, 0xD1185532EFAFBD03ULL, 0x9B2AAAE52815C5E7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseCConstants = {
    0x66C837A829582B01ULL,
    0x9304DAFBF7D23BA2ULL,
    0x82BF93D0CF9EED54ULL,
    0x66C837A829582B01ULL,
    0x9304DAFBF7D23BA2ULL,
    0x82BF93D0CF9EED54ULL,
    0xBAA82DBF92133EF1ULL,
    0xFE15DC7AD2249F5EULL,
    0x0C,
    0x2F,
    0x60,
    0xDC,
    0x2C,
    0x8A,
    0x7C,
    0x94
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseDSalts = {
    {
        {
            0x5FD5D8B3674D3060ULL, 0x2C631C1D532C4C4FULL, 0xF0F9BA77C116486CULL, 0x5D759441D7B5353FULL, 
            0xC4B850ECFA69A06AULL, 0x9BDD33C508F7F939ULL, 0x28E8CAD815AE8128ULL, 0x4E26BE7845E83A58ULL, 
            0x6E87BCFD5ECECA0EULL, 0x273C1533D43C230BULL, 0x133F6D6E3A180D53ULL, 0x2307A6C832CFAD8DULL, 
            0x8309EABB627632C2ULL, 0xAE46D7A810323C7DULL, 0xF9883F3139729B42ULL, 0x7FDFC60042D63DE9ULL, 
            0xF056B1451E099464ULL, 0x32AE9F9F443812B6ULL, 0x8ADB1D53C1D07941ULL, 0x43ECF14DADB85EABULL, 
            0x297683CBC1861A9BULL, 0x4EC264FC0E9B2095ULL, 0x5389202B9B535526ULL, 0x5C3A59B06657E298ULL, 
            0x3D2D06C9641CF77EULL, 0x254B58E9AC81BFC1ULL, 0x09E71526CCEA2DE7ULL, 0x22ECA42043E57968ULL, 
            0x82DE727409BE6703ULL, 0x1F77A25BDF5FEFE9ULL, 0xF41A18F452C1CD40ULL, 0xAF71C301F04CB622ULL
        },
        {
            0x20E046859C7BFB42ULL, 0xF0497644978AF44CULL, 0xE3A620EA1D9AC1A8ULL, 0xB89B728B6589ADF9ULL, 
            0x123ECBA8DF6C250EULL, 0x68A0A9D754982B32ULL, 0xC7078A5DAF813DFFULL, 0xD02C53B64729D6D1ULL, 
            0xFED6180C17BEE94FULL, 0x51F0B3E027E6DCF0ULL, 0x3379A99C2B422200ULL, 0x8BF4580C66989C62ULL, 
            0xAEE1EC020059927FULL, 0xBE87A6B6A8E1010BULL, 0xD0666EC0432095EDULL, 0x2E83A1E3936516D0ULL, 
            0x98E681A67DA31F31ULL, 0x76B4EA91017519D3ULL, 0xB74E2C0401C08F23ULL, 0x7F6F6EDEC165727EULL, 
            0xBBE1FB36EF75FB27ULL, 0xE2D30E9AEB22E86BULL, 0xF8D50EA465191414ULL, 0x98A684BE68274A8BULL, 
            0x350E9D738E5B8E4BULL, 0x98A4EAEB84A1A8F3ULL, 0x5E63D8ADB6597D1BULL, 0x22067BA3220A7A99ULL, 
            0x0A901865BA3DFC7AULL, 0x4F607062E927D1A7ULL, 0x2C514C5292439210ULL, 0xB37EB32F841CB51FULL
        },
        {
            0xE4A53C25D8393D9DULL, 0x42A2EE2F8F04D9ADULL, 0xA1C00BF7B83E48B0ULL, 0xEC7A5ED5F76184CDULL, 
            0x663D81E158A41707ULL, 0x3B3FE17C271E4F2AULL, 0x6D7D103CF12BE0EAULL, 0xA589FBB628EC7203ULL, 
            0xF0907200CE89A737ULL, 0xB89F730495598AACULL, 0xC98FC03A834E4210ULL, 0x0807F80CE85EE0D0ULL, 
            0x778B1C3BA1326329ULL, 0x8C19C9DE850165C6ULL, 0x1090356B26FF8760ULL, 0x00D20E8CEEB4FDA1ULL, 
            0x7D23E666BD6CA5D4ULL, 0x0E028952A92A8CCBULL, 0xAFF5DACB091ABEB2ULL, 0xB866F4D5C624B7BCULL, 
            0xB9FCFA3E0BCF789FULL, 0x6768F10A6E46A8E7ULL, 0x1A0AF4A0B904A59BULL, 0x2A753C5D2617F270ULL, 
            0x36979E8571B573BCULL, 0xF2BC0F11597E8F8CULL, 0x7E66B6FEE90799B6ULL, 0x96F3D56F9F7AEB63ULL, 
            0xF1888216CDA919F2ULL, 0x4943F22BF36DA8CDULL, 0x01601178D7FB82FCULL, 0x69FDCF1EC9E0D7FDULL
        },
        {
            0x05A9B730002C8C2DULL, 0x2C68E37675DA70E8ULL, 0xB65FCDAD2A6A212AULL, 0xA37A4EB94CF98FB4ULL, 
            0x647792120031BFF5ULL, 0x59CE718D2F3FBB0CULL, 0x17FE880E879DAD5AULL, 0x855FFC52EE18B4CFULL, 
            0x52748C6DBAE4A3ADULL, 0x029C044FAFFF9600ULL, 0x44A1EDFFBE477570ULL, 0x6DE108EFEFD6404BULL, 
            0x765712DAFFEFC473ULL, 0x7436B37190257CF1ULL, 0x653E2CBD8171EA95ULL, 0x21CB5D61F18520E1ULL, 
            0xF001B4759FFC9105ULL, 0x9688D6BEDAB9B9BEULL, 0xEE84D6EF2BEDBBFDULL, 0x12D54454F087B3AAULL, 
            0xEC70111CA0A8918DULL, 0x33A76855F42EF3FFULL, 0xCFD3F770DB577B2DULL, 0x2895E74FEB17A730ULL, 
            0xE5EBE5345DE28E5EULL, 0xC0AF567E39945A70ULL, 0x800C8D0A6F7E4435ULL, 0x911A9467A81D6903ULL, 
            0xE651459E580EB342ULL, 0xA9B22D7D76CEB351ULL, 0x0C7A16B2C858EDDEULL, 0xFE344537BC381ADBULL
        },
        {
            0xBABFB55E455DCC3EULL, 0x9FF3BC48AC54E6F6ULL, 0xA8B1463930C8B9BCULL, 0x0D404C5250706F5CULL, 
            0x5EF8E0845B46B25AULL, 0x6FCC475D777433EEULL, 0xC0C026FB166D887AULL, 0x2304DAB6B1C2C50BULL, 
            0xC64B8406165F6828ULL, 0x8945836FBEC18B05ULL, 0xA7ACA04E7DBD4060ULL, 0xAC1A394859813D00ULL, 
            0x97DF3D9BA71C0E81ULL, 0xBB558CE82CA0FCDEULL, 0xB72A8F95F412CECFULL, 0x8844C5FB700E063AULL, 
            0xCF231A0BC90C29C9ULL, 0x209BBDEEE87CCD6BULL, 0xA9348BD7148EB079ULL, 0xD501A95CC82E2734ULL, 
            0x519C3E63457623FDULL, 0x5FD683DBD53E990EULL, 0x6BEF9B1D1C660475ULL, 0xEEE02DC25E316B51ULL, 
            0x97FE4D2EDB8BB1C9ULL, 0x5A5826A8BBA455ECULL, 0x1F0533C53B0E0F60ULL, 0xD13FDCE722C310A6ULL, 
            0x359EC122795A5C1AULL, 0xCCF036BFD8C6F4CBULL, 0xAC95355E4B2FD130ULL, 0x0989CDEFD8303564ULL
        },
        {
            0xA7B955E3874C2732ULL, 0x4FD71A4F1928D45DULL, 0x62E0C43595C7FBA5ULL, 0x95C268ECE374AED0ULL, 
            0xA3EF675BAF233E9DULL, 0xF820F81C01D0E4C3ULL, 0xF45A97168BD4652BULL, 0x3A5777A1F07CE427ULL, 
            0x2B183B97178CBFE5ULL, 0x4292EFEAF759B908ULL, 0x6C7FDF96E3A1E685ULL, 0x6BC25169D10EB310ULL, 
            0x72B2DCE065861D44ULL, 0x45397EADC6C6418BULL, 0xBAC347A315214283ULL, 0xC226D97F196EBDC0ULL, 
            0x3E53E790ABDBF12AULL, 0xED7B83B9354E1FD4ULL, 0x1F31A7A51344C064ULL, 0xC76B0B303A5BD735ULL, 
            0x79705E142E62D4ADULL, 0x15697072B671F452ULL, 0xADDA243D4B1DE9D9ULL, 0x323286A74A6FCAA6ULL, 
            0x452498DB7C9846AFULL, 0x3F05DD463C485D40ULL, 0x50BD60900D508ED1ULL, 0x3C219E487912ED90ULL, 
            0xF875A7B78B248372ULL, 0xF23323C236170085ULL, 0x8FDBCA364E47A52BULL, 0xE2234CB3BD3CC12AULL
        }
    },
    {
        {
            0x0310CACB28556D1AULL, 0xFBAA8157209487F6ULL, 0x731FA936491BCE02ULL, 0x871167E099182418ULL, 
            0xD48B4E37CA44203AULL, 0x3A015F2D7D162C09ULL, 0x9C2C0BE10DAF9544ULL, 0x1E5AD59D1D629754ULL, 
            0xF780427A396A0B73ULL, 0x5154AA12D7B54162ULL, 0x92B55F86965F01B5ULL, 0xDD384B7129BD8841ULL, 
            0x5CDFB145C12EEC3CULL, 0x5F15BC846F5F562BULL, 0xC83682D2F275E552ULL, 0xFAD3274270D9144BULL, 
            0x79C23596BAB03238ULL, 0x3F1F8605CBF67B8BULL, 0xCBCD7DECC072EB5AULL, 0x7FF201DFBE75F668ULL, 
            0xF2DD90B6A208376FULL, 0xE738B91EACB2B115ULL, 0xB3B53AB0D4059DF3ULL, 0x62EC47B4A5C4E99FULL, 
            0xB4EC8BB62D54037FULL, 0x29C1894D11F82AB2ULL, 0x2CE6C0DA7694DE6BULL, 0x1E14219B0DC99322ULL, 
            0x8CB29B87B9AC605BULL, 0x66142FA64A51EE25ULL, 0xF66B161B76D3FFE0ULL, 0x09DD5AEC6741808DULL
        },
        {
            0x4EDCCCF3669C18CCULL, 0x03680145F673F22CULL, 0xCCCE8A3FD5D8B268ULL, 0xC5B7BC9D0E0A6C78ULL, 
            0x1943DCAC8BFC8DAEULL, 0x7F8B9B41971D1038ULL, 0xA49B94E8036029AFULL, 0x638CD759CD421376ULL, 
            0xA53C2EF88B9F3718ULL, 0x765BCEF218DFD996ULL, 0xB224A997A7A088FAULL, 0x68073C11E5421927ULL, 
            0xF8C69C1DB4670192ULL, 0x40740D67EECD684AULL, 0xF2AC4EE97EDCD5A7ULL, 0xDA0E0F5D982BFB72ULL, 
            0x06AD68211E5CA21AULL, 0x6CE679814CA45161ULL, 0xB3E632ADB47DD91AULL, 0x56E720601B057706ULL, 
            0x70A537F6CACE6AC8ULL, 0x0704FE20FD902093ULL, 0xF035341C409CEA9EULL, 0x909C776646805326ULL, 
            0x309B17DED500CF5BULL, 0x06F2DD73AFCB0DA8ULL, 0xAF7BC7B4D6D7D3A6ULL, 0x42D87496D0DA75BFULL, 
            0x1B4B207DD169EC13ULL, 0x4F9CB90A1C0292B1ULL, 0xB473A4FCC49AC4CBULL, 0x498F2F41C1082D07ULL
        },
        {
            0x6ACE503AA6E527C2ULL, 0x6627D675948DDF7BULL, 0x6DCAB2BAE3743FF0ULL, 0xDFD8700CACCA60C3ULL, 
            0x3DD188B0B410850EULL, 0x0F30BF45DF786CE1ULL, 0x393B02082FC4C9C0ULL, 0x50491B1D1E8A850DULL, 
            0xD96AC531DFA1433AULL, 0xB6442917C2368614ULL, 0xC537EA7DCA7F0D42ULL, 0x7AA8049B356B6FE1ULL, 
            0xC781BD4298635C85ULL, 0xAB8758962918C3BCULL, 0x2CACD50B931E7BE0ULL, 0xD7EB4191CBA33DF9ULL, 
            0x971A2F1E0657D337ULL, 0x24968FF36FD7C39CULL, 0xEB16F7D2CBAEAA8FULL, 0xF16FE44EB1B9E34DULL, 
            0xB28CE2674FBE0980ULL, 0x886C6E8EA600E3CCULL, 0x6745FE8CF94033B8ULL, 0x5975B9C7CE1BF426ULL, 
            0xAD7836E66614097FULL, 0x7F9D36FE5AFB46A6ULL, 0xD754DB8024F0F918ULL, 0xDFB4EC04A1B3F4FAULL, 
            0x29AD9410ABCE818BULL, 0x1A0705668BCDEC4FULL, 0xF7CC34647EE4C3B7ULL, 0x925E48C3B91EF835ULL
        },
        {
            0xA441441ACEE63585ULL, 0x625267C0E231D67CULL, 0xF749B3DC52295CCCULL, 0xF630563A28FCF8F4ULL, 
            0xA92E8435D80F9782ULL, 0x599880CFD3D63B12ULL, 0xACA40A67E9DE405EULL, 0xC91ECA2CD4EAA124ULL, 
            0x93301D68EA7AF50EULL, 0xD6C5D4165485A288ULL, 0xF5E133F59DBF64CDULL, 0x5149A5F5984A45CDULL, 
            0x773096B4D1C67FAAULL, 0x6163FE00545ECE9FULL, 0x88C9EAC3E7B9F96DULL, 0x3A067C7D48106065ULL, 
            0x7222DFC32F46F4FDULL, 0x8DE4763FFB09C2EAULL, 0xF14BFC75291B6731ULL, 0xAD66D8CEDF283AEEULL, 
            0x9F4C558DFEB0AA03ULL, 0x1C438B6608A58434ULL, 0x2A246264828C73F7ULL, 0x111E9AA723BE1783ULL, 
            0x091463E8ED5CC5FFULL, 0x60C266AF9058679BULL, 0x248B90F2B9966346ULL, 0x45444C63FBDE2DB7ULL, 
            0xC11D38A2096DE29AULL, 0x5ED7F25D2DF97569ULL, 0x755238AA20CD2877ULL, 0xEF667280C3F05226ULL
        },
        {
            0xC808B437608EE611ULL, 0x95EBFE013891418CULL, 0x47FE3B68420F220EULL, 0x347657B49E3ACA32ULL, 
            0x6F12718444864879ULL, 0x87EADFD9315B874FULL, 0xD5C861A595B079D7ULL, 0x25107714A1C19BC4ULL, 
            0xEED71F44CDEC6F82ULL, 0x94E26BFFD4FF0C7BULL, 0x5098652EC151B563ULL, 0x5472E456B1ABFF36ULL, 
            0xE156B3C7F535F9A6ULL, 0x846205CC706FC01EULL, 0xC429CA0AF91530B1ULL, 0x8894D965B64F66B7ULL, 
            0xBA2D951D49A5351EULL, 0x668CF0CC6C5D96C2ULL, 0xD4E7044143C91940ULL, 0x966465B89DE67CC0ULL, 
            0x1153FDA6F6E9B0F9ULL, 0xBF28FC6BD967D570ULL, 0x6DF540C30C8248C2ULL, 0x52A5DC2FB977C2E1ULL, 
            0x3D578B16518ECCC1ULL, 0x6C175C208B23DB9BULL, 0x2D3A2B911AF1BFADULL, 0x725FCA4E879FD52BULL, 
            0x0047AEE50E8E1EDFULL, 0xD6EAFF198AC10C6BULL, 0x4D53CB3DCCDD8939ULL, 0xCC79A54714EC716CULL
        },
        {
            0x86F5F211EEAC6017ULL, 0x7302DCFC85766579ULL, 0x07B75C0325ECC5FFULL, 0x15D95F134F1FDE44ULL, 
            0xC979582FF310FE67ULL, 0xF550A1912E4451ADULL, 0x11A9E8F95BBDE64CULL, 0xAE9E6666EB875773ULL, 
            0x35A3D557E8235D1AULL, 0x9C5EA92B4DE6DDF3ULL, 0x1008767894B40D6AULL, 0xA33D23F8C20D0644ULL, 
            0x6940D5D46D2627E1ULL, 0x5A05A3E0EE803102ULL, 0x4861CC3E3DBE9D00ULL, 0x7E31501EB52A4112ULL, 
            0x19E9B6F8BC8FE44AULL, 0xCABA839FC33B53BDULL, 0x406888E4ABBFD257ULL, 0x1F5404778B265390ULL, 
            0xD5FFD9946C319483ULL, 0x8ACEE3BE752406CBULL, 0xA0D38F5A0ABE0CC7ULL, 0x085B136AA1212A1EULL, 
            0xBD4275FD7666E6A6ULL, 0x7206938B1ECC08F8ULL, 0x036BADC9D11CE800ULL, 0x4914E27975012BBCULL, 
            0x7BE7B59EBF2D0EA7ULL, 0x9ECD240A4EECFEE7ULL, 0x50EB95F84650667EULL, 0x1B9CE768F2EA4784ULL
        }
    },
    {
        {
            0x87011E088301500CULL, 0x64A9E256026C6B2EULL, 0x761B68359C509B64ULL, 0x320B86B4697DDC28ULL, 
            0x07337A0C0741C527ULL, 0x85CA63C26ED5F33BULL, 0x878A1916A8EA0CE2ULL, 0xAA5C26F176A41C8CULL, 
            0x1EDFF7C543C52BEAULL, 0xD7B56013FB08670CULL, 0x43108573BC85D51CULL, 0x3D6055C905878500ULL, 
            0xDC7CD0D30630F257ULL, 0x9B238D3F4362FE57ULL, 0x9D9648E277626361ULL, 0xEE2920D7BD698C4DULL, 
            0xDAF0930A5ECCDF12ULL, 0x3396DC09E537D513ULL, 0x6BCAB36C1D769148ULL, 0x75D2082183AB8E8BULL, 
            0x1AEEF676F20BD816ULL, 0xC7D8C20E62AA4269ULL, 0x321A9DB42A1076CBULL, 0xFF689857F184E56FULL, 
            0xBB341FF02BC126B2ULL, 0x1CCCFDFAD5CACD4DULL, 0xE58861182CBEB7C6ULL, 0x1BD3DED2BAB638D7ULL, 
            0x839BD9D776AD9F65ULL, 0xED65211B423ED4DBULL, 0xA6015E7EBD0E4036ULL, 0x6268DBA7A313572FULL
        },
        {
            0xFFCD6D1CCD0CBDA2ULL, 0x5886CD1C172E9BA8ULL, 0x678C0C0197ABF44AULL, 0xA95113E02CBC1403ULL, 
            0xA9613E8DBC4E47FDULL, 0x520D71488037F822ULL, 0x32BF83DF244FCC4FULL, 0x9665072C4BDE2E20ULL, 
            0x3C382DC4CCE5235BULL, 0x99952C5F57ACD199ULL, 0xC77C729A66C73098ULL, 0x0C1D010884900980ULL, 
            0xCD0DB444B6EEFC62ULL, 0x7983FEAE7165FB7FULL, 0x998B9004A7C6026CULL, 0x0776F37AC34183F9ULL, 
            0xB856386CD0BF3B96ULL, 0xDBFD214E93C8F507ULL, 0x3E474B80C6B96118ULL, 0xA293F018A7149613ULL, 
            0x14FC9A81A67576BEULL, 0x42C9D436790F8D05ULL, 0x8BAF2E2AD359BF72ULL, 0x2D7A0351DF4B7BF6ULL, 
            0xC55AF73F9BBDFED2ULL, 0xBCACB27E1EE01287ULL, 0x5BF29C189D187201ULL, 0x4CD41815FEC87C61ULL, 
            0xDEAC46EB6A3686D4ULL, 0xA78C34FC13B6E9AFULL, 0x3279140D2702DBB7ULL, 0xF07E84AA82E26825ULL
        },
        {
            0xD8832164A8CE8DD6ULL, 0xAB7C66ABEF82E3B5ULL, 0xE7A0E3175EB951BEULL, 0x1AD53A694F2FD36AULL, 
            0x86B3731EFFF2CE58ULL, 0xC619F89EA18351B0ULL, 0x449ECEF10011CE9AULL, 0xA3AEEE65BAAC4140ULL, 
            0x084FD81F5ACC7930ULL, 0xF10F17116740F8BDULL, 0xB289E038AA3185C6ULL, 0xDFC9604A0F4541BAULL, 
            0x6F36B511C7A981DCULL, 0x55545B4CA49031B6ULL, 0xC6CE30EE83D45639ULL, 0x01FF8E2ECE9CB8E7ULL, 
            0x30857B2111622B12ULL, 0x39400EE786CA9D68ULL, 0xD9B8A3244622E5D0ULL, 0x886058DD73060E3BULL, 
            0x0A016C252BBFFC21ULL, 0x27DABDF75AEC2BA8ULL, 0xC7A9E543F199072DULL, 0x6505831D149D5316ULL, 
            0x9672D9591582D749ULL, 0x24C006FC10EFFC82ULL, 0x181C7ED50900EA7CULL, 0x8642F699F56D7607ULL, 
            0xDE8484A99EF66F0BULL, 0xE0A3A262F2171CAAULL, 0x21E51D3DFF449A89ULL, 0xABBAE5CAF7263D48ULL
        },
        {
            0xDAAAC0549EE2A9EBULL, 0x647D0DE4A2CABC00ULL, 0x6188238D144A0583ULL, 0xC8E50F71DE10A1C6ULL, 
            0x92BAF4568E25C970ULL, 0xB389E0E39C5C8E2EULL, 0x3FD97E55AC1AE6DAULL, 0x3C399313E7A53D69ULL, 
            0x52CE49AC2412E8ECULL, 0x41370E2DFB2D2000ULL, 0x3942433F85E7E9EFULL, 0x9112F2BE31B2175DULL, 
            0xD6BB05A701AAFE0DULL, 0x23DA84A9A0422DB7ULL, 0xB794F88798042A14ULL, 0x92E9B4E92A8C5268ULL, 
            0x98ED0B1A02ECE44EULL, 0x46320A9EA3B5E64EULL, 0x1918B494220B4D41ULL, 0xEB1624B86121202EULL, 
            0x043710055240A08CULL, 0xDF65BB09C40D4186ULL, 0x92016F67FA388EB1ULL, 0x2878DFDA43085FB7ULL, 
            0x1AE32070EC00DA72ULL, 0x9EDB57BE4A8C4B69ULL, 0x21DD3C0F9709C693ULL, 0xB6E688F2ACB53B16ULL, 
            0xA879E47D7889BFBEULL, 0xD3CD3D09CC5C9A98ULL, 0xB53EE9E5C8C4D18FULL, 0x1332893A2B06383FULL
        },
        {
            0xA141B7D0C112DD97ULL, 0x6674C305210D822FULL, 0x016BCD1CDC174288ULL, 0x2ED9409F6561935FULL, 
            0xDBA7FBC7BA72A08CULL, 0x99BA245AE231D8CBULL, 0x8459F2E4DC2CAA71ULL, 0xA24E92DF44A8460BULL, 
            0x7EC77EBC4744F426ULL, 0xE606FFD48453F60CULL, 0x6B5DDCC11F364BA2ULL, 0x26EFCFF0CDD20596ULL, 
            0x12A12733C19B9056ULL, 0xC3756FC3985C3FB5ULL, 0x0CAA75121F01179EULL, 0x430E4BF4B14A0CEEULL, 
            0xF5EE85EAFA2BD186ULL, 0x794FFB2E6DD0C65BULL, 0x72A9F98D80D0A5D5ULL, 0x202E7EA012AD02A8ULL, 
            0xD49254A0A3BFC754ULL, 0xB53BFA97FEC5F84FULL, 0xACA8F7A034B8F022ULL, 0xC1104A94D7EF72AAULL, 
            0x43433AC2C45230A7ULL, 0xDECFA79B7820C24EULL, 0x4BDD076D272B0A09ULL, 0xBD2E00E0746B4AA2ULL, 
            0x0362FEA9965D8208ULL, 0xEBD76E0C95E090FAULL, 0x3710F0315599C3A1ULL, 0x470439F8A8BC2BD2ULL
        },
        {
            0xD99F9AEC6F864826ULL, 0x2574667657DD32F0ULL, 0xEA3B751CD925A43FULL, 0x85580CEBF89D6E10ULL, 
            0x5115167BDA724A57ULL, 0xF753E0ACDBB32325ULL, 0x40D78DA85AC20B62ULL, 0x9DC15BBE33C66EF7ULL, 
            0xE639E16632381EA1ULL, 0xA3FE3BB1AF9C2804ULL, 0xDE1E670AB69C9EB9ULL, 0x3D78153DD79CEA54ULL, 
            0xF9063338AEAC06C7ULL, 0x39AA3A0C11FB6383ULL, 0xA2DB4376A622365EULL, 0x1C45F0DD23AE6E2BULL, 
            0xC77B597F892DAD08ULL, 0x5E099D868703B95AULL, 0x5EC5D76657151B3FULL, 0x3D862F8FB6B8404DULL, 
            0x48C6F09C9764149EULL, 0x74B5408F829EFA02ULL, 0x053F90E36FE0AD48ULL, 0x6A8BEB8201F3C67AULL, 
            0x1FE7FF6328DA748DULL, 0x9BAC08B5D3DA1C96ULL, 0x8726ECF756B601BFULL, 0x9A9B2A324BDA971AULL, 
            0xDD4AA4A1D89C09F1ULL, 0x18261471BCEE57FDULL, 0xAA58F10B178D1D89ULL, 0xF7A001E716734467ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseDConstants = {
    0x25D81D30B6992431ULL,
    0x7B3C26552A2713DDULL,
    0x232D420A7F3459A2ULL,
    0x25D81D30B6992431ULL,
    0x7B3C26552A2713DDULL,
    0x232D420A7F3459A2ULL,
    0xB30799DC4FA2C2B2ULL,
    0x275E31E21FA6B139ULL,
    0xEB,
    0x64,
    0x13,
    0x28,
    0x30,
    0xBD,
    0x1F,
    0x84
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseESalts = {
    {
        {
            0x2D23E2F80E6D9D8CULL, 0xC6331FA262DE80DBULL, 0x20647D2F33795771ULL, 0x1661DA7F06690571ULL, 
            0x165D9406F8D9B968ULL, 0x237C589420AB597CULL, 0x903FBA25B1419E69ULL, 0x11102958D857588BULL, 
            0x6C08ADC407FB3CAAULL, 0x60C28EAE3E03242DULL, 0x518B71B57F7338ECULL, 0xC0EB0874B9F16D30ULL, 
            0x529A84B25164EBC7ULL, 0x7EC60B5455B245B1ULL, 0xC38C0505465A9694ULL, 0x89EFCBC9F24B92A8ULL, 
            0x438D22A9170884DBULL, 0xA94C328947992B97ULL, 0x7B97CE1562FDB4C7ULL, 0x461E56A4D511884DULL, 
            0x6FACF3D8E2364C50ULL, 0xD78BA60ED5514074ULL, 0x5FFB59809BE67CD8ULL, 0xE67469BDBF360492ULL, 
            0x5D37E178F7F6B6C7ULL, 0xED51DF13C896BEFCULL, 0xC82FF822B9AB16E4ULL, 0x31E44A7FAC9366B9ULL, 
            0x84FADB6372758E73ULL, 0xFCEAA13F80CB7DFAULL, 0xCA287D9B9C149C57ULL, 0x4FDE9AE766EAD280ULL
        },
        {
            0xC382149EE40560B7ULL, 0x609E38A3CD4413F1ULL, 0xA3CDFFBF9F841AD3ULL, 0x3A89FDDE75B11F36ULL, 
            0xC93F9E50268B440EULL, 0xADF2DCEB9C093A0DULL, 0x1DB8743D6E9870FAULL, 0xEBA3355FEC6CEB3CULL, 
            0x16D22212BF089186ULL, 0xAF42C4756E1A472AULL, 0x679829CD5578DA0FULL, 0xE54782CA6FA5D6B4ULL, 
            0xB48CDF8F1A5EFC0EULL, 0x94CA8E571D6C95FFULL, 0xDDE0D751EFBA60F5ULL, 0xF35E5F290E4A2810ULL, 
            0x8F0B28FC291F7006ULL, 0xA8E8866C4FAF6A46ULL, 0x2EABCAA585221764ULL, 0x67118D8261C10E2FULL, 
            0x3D765E6B31461DD8ULL, 0xBF91EBAEBAAE54EAULL, 0x0BB6B21D32248F38ULL, 0xC930C36320492986ULL, 
            0x98AB1A4F7150F5A6ULL, 0xADD2BDDC1CCD03DDULL, 0xAD594683EDE01C54ULL, 0xEE2E918691103BC7ULL, 
            0x89FF3451B2946C77ULL, 0x1497FCF27AD9A749ULL, 0x7BED626CC729750AULL, 0x6B015890E00DFF0FULL
        },
        {
            0x070FBE7A50C1B2DFULL, 0x9BBB08DD480CE6D3ULL, 0xBE418538AD7DC405ULL, 0x7E1B89FBAA3E77FFULL, 
            0x99D2BE10CB927DD6ULL, 0xA32CD79F30104089ULL, 0xC1780EAC2FBAE0EEULL, 0xD3CDB5B9A9B61301ULL, 
            0x14E860CAE31CDBDFULL, 0xFCCFE795F190479DULL, 0xCE6B0AF7A83EAC45ULL, 0xFD8EA430FCDDA603ULL, 
            0x0C249552729F7267ULL, 0x04D6613F6CE009BBULL, 0x7C4B8E9E6EC602E3ULL, 0x7E5CFB64AF456B1FULL, 
            0x850B4C5A6B2F0A76ULL, 0x1884F11F4F5EA1D9ULL, 0x70A043BB7C71A2FFULL, 0x0806A53935F8A283ULL, 
            0x930828238934BA01ULL, 0x2481686A0F5582FEULL, 0x594024B369A06D86ULL, 0x53248DD3380C8799ULL, 
            0x564A8151F333E84EULL, 0x6E458465AAEFE3F2ULL, 0xE61A79958F3C0269ULL, 0xD15100EA34CC43F1ULL, 
            0xF80EB7FD940ABA3BULL, 0x58033C775354AB8BULL, 0x969CB8BBE7881FF0ULL, 0x0206325FCAA5367AULL
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
            0xC4457CC495DA462EULL, 0x641E8DC51BB4BDC4ULL, 0x26183ECBB2BB7781ULL, 0x0828F9370A67E3A9ULL, 
            0x7029F13064053986ULL, 0xA4739DA0B986054DULL, 0xA48567BDC5C02DE9ULL, 0xBD5E9B90D393081BULL, 
            0x8F8F368C240E541BULL, 0xBC974D07EE0BE430ULL, 0x5B9ABDC9EF150E8CULL, 0x0E6A6F90FD4FF31AULL, 
            0xBF42A113A8071B0BULL, 0x78F87AE623CE4DD3ULL, 0xB875D864CAF43053ULL, 0xCBB2BE1284156B5AULL, 
            0xF1ABDC57AE2E5BC5ULL, 0xD84ADB36C33A4F5EULL, 0xD57A7C7622023595ULL, 0xFA1BCBF70F161376ULL, 
            0x05E1EA1E0CA5A5F2ULL, 0x9E427B9A9A5FA8E5ULL, 0xAEDA21BBAEF408B3ULL, 0x57EF8547210F4CE7ULL, 
            0x9905A4C41F430EDFULL, 0x143C4754B0E8C285ULL, 0xC664BBFF8EC1C0BFULL, 0x6D95B497AA67B6ADULL, 
            0xB1B8ED8F1635799CULL, 0x4C60C02EF9E8F0BCULL, 0x072632494D533ABCULL, 0xA9D35C9693F7FA57ULL
        },
        {
            0x95F06B8FE40740F3ULL, 0xF95F693C8B67DCBFULL, 0x24A5A32C36A8E377ULL, 0xEB5B9B46EC5B0D35ULL, 
            0x66E21D989719FD17ULL, 0x82C119C909BF0A11ULL, 0x44500530F1F2B4ADULL, 0x91438F29F6EDBEDBULL, 
            0xB011C4EFFC894656ULL, 0x56143E3D9D76E888ULL, 0x623A82C928A3EE44ULL, 0xC65D1D69A29C22EBULL, 
            0xB4A1BEBE801F898CULL, 0xFB3D5AF71A56B6BDULL, 0xC0ABE2A5339104E7ULL, 0xE6C322C43B953903ULL, 
            0xBA3BB260B7E06C6CULL, 0x73AF896061A76489ULL, 0xB5DD65E383BCDFB4ULL, 0x4DCDEEE0AA7141F0ULL, 
            0x59AD6D2B6FB37B00ULL, 0xAB08B68A216F9821ULL, 0x90E93948EDD3C8E1ULL, 0x76A3D640DE19FEE7ULL, 
            0x645AE8984E4EA10FULL, 0x731F6EC0E0145F69ULL, 0x4E1138FBC7E3355AULL, 0x57402DD187CCB99CULL, 
            0xB560CEA28DCD38DBULL, 0xE59AB1C94F64D863ULL, 0xEDFA8BE62D96AAF2ULL, 0x710C7D610E5B9CEAULL
        }
    },
    {
        {
            0x7228C3D287050A4AULL, 0x80BB8DFF855A2B84ULL, 0x34A61763BBDC2354ULL, 0x1746061E04A3F209ULL, 
            0x510B3E1F2AF21926ULL, 0xC9B63FE24B5CFC69ULL, 0xB27688147AB75110ULL, 0x8B18C1ED22221CB2ULL, 
            0x313665F0E37ED10FULL, 0x7CD91D142F87A778ULL, 0x626C560C092DD6FBULL, 0x937486DC813069B9ULL, 
            0xB8B7821F893D2FCDULL, 0xE2B05CAD66FC0451ULL, 0xE6717C049E8040EDULL, 0xCFAF1C14BE7BEF24ULL, 
            0x4B4603BF0CA89FC2ULL, 0x0D517D26EE35FFD8ULL, 0xBCE6805F74B43387ULL, 0xC0840E29B3B44862ULL, 
            0x23B53E5DE294E0E9ULL, 0x9170378F361324F4ULL, 0x86A2EF987B5BEFE0ULL, 0x9DC346BC9565E024ULL, 
            0xFE346ECFD35775D5ULL, 0xDC25A0F0928662E9ULL, 0x8780C7A51BEB8CA6ULL, 0xE405B4C1A8687FA1ULL, 
            0x952F2ECD9EFB314BULL, 0x108CE714A74C7816ULL, 0x326A52025032EDECULL, 0xA11F3E4FBA9E1B6EULL
        },
        {
            0x173B1AAFE7390CEBULL, 0x6A1FA36F8AB8B306ULL, 0x0865F7E696D85A58ULL, 0xEEDE2A3D4B85C751ULL, 
            0x4B95512BB69F189DULL, 0x60C76D0566200FAEULL, 0x82B27260BB046970ULL, 0x15A6EAE070DD6931ULL, 
            0x75333CAA17037C28ULL, 0x40F4DD758BF26901ULL, 0xB5F875FF8C9FE366ULL, 0xB925FCFF11011DBBULL, 
            0x658A9246A8D11711ULL, 0x451EB65731CF1635ULL, 0xD2854E6A6DB0CAF4ULL, 0xCD5E1CC65CEBF3B1ULL, 
            0x8D5EA315428B3578ULL, 0x95C02BAF9A71F917ULL, 0xDC1DF079970AFD9EULL, 0xA0FA697B648180BDULL, 
            0x35C6E766ABE14809ULL, 0x6AA62DDF21AFF9A1ULL, 0xA2C2D9596B7B4FABULL, 0x45C5007CD47E8DEDULL, 
            0x729506F28703090DULL, 0x66C03B3DC3E2A1CFULL, 0xD7A1A4040A71D4EBULL, 0x6F4BC453720BC260ULL, 
            0xC469C590397FC8BBULL, 0x18CC7F22780DBCDDULL, 0x527D6703C84D6400ULL, 0xFE4AAE4B7D4EF5C3ULL
        },
        {
            0xB390521125AF0A1FULL, 0xC401D1AA2DD91B81ULL, 0x8D9D6269EF4DB4A9ULL, 0xF427D219B9DB5C68ULL, 
            0x0D4716CACA77AEDFULL, 0x383BB4606EF3A986ULL, 0xB69D1FFC6A631D26ULL, 0x90327BAE694D6106ULL, 
            0xB91AD48E2FB8DCDAULL, 0x32B6F0CAFF1724ABULL, 0x7B4575FCF81F016CULL, 0x46D32BBB8908CDDCULL, 
            0x403DD547026E5917ULL, 0xAEE29D718009718DULL, 0x4B95783364D0830DULL, 0x091149D9D4B5BF32ULL, 
            0x43777957E3121E36ULL, 0x5C235923E1DE7225ULL, 0x233E9C1AFE27FD6DULL, 0x33F1E6FC2251BA02ULL, 
            0x973F8CBB09C65790ULL, 0x8D804D4B821B9321ULL, 0x4D6732C7C2A3A5F1ULL, 0x4C9DAB66F062889BULL, 
            0xDC51EEE1CAE968F3ULL, 0x907DAA290CD1CECCULL, 0x283C6F1018423F1DULL, 0x7E9969B4226465ADULL, 
            0x4D35C67E476095B4ULL, 0xBC4ABA3DAB90AAB4ULL, 0x95A35874BE3CEF9EULL, 0x1856B519D89C1DAAULL
        },
        {
            0x71E6B6AAB1073B23ULL, 0xBA3CA6F6CDBC7A7CULL, 0x9AB22E85B92A9310ULL, 0xBA96EDBB717273C0ULL, 
            0x9029680E1FFD3CA5ULL, 0x52BAE489A0C16998ULL, 0xAE8B1E44F39A0614ULL, 0xF662EBF2BB10B43EULL, 
            0x6A5281CEC7540F78ULL, 0x4810093C339088CFULL, 0x2EEDD411C50F2310ULL, 0xCBC70A4910AD7C93ULL, 
            0x86E3A2B6ED4637D8ULL, 0x91859EDDD1578BEDULL, 0xEDAC983D6D9A3C6AULL, 0x8E20B4C3E9D85446ULL, 
            0xD802686FC21608EBULL, 0xC00AFE021E699358ULL, 0x78549D56C51095A7ULL, 0xC7DB35B1C1534786ULL, 
            0x58826E386539A3F3ULL, 0xD2F6345713747FADULL, 0xD2D765D346ED53B5ULL, 0xB7A0356D4070573DULL, 
            0x8F03FDE91EDA01DAULL, 0xD219585A6051F5EFULL, 0x177225972FAB364CULL, 0xC62D49862E6B762DULL, 
            0x830A54E698BCA2E2ULL, 0x3CF8DB49CE4BF8ECULL, 0xED01215D6402E365ULL, 0x7F1D3428892DA407ULL
        },
        {
            0xA89FEA7A8A2D2D80ULL, 0x72691EFE644A0783ULL, 0x1B4B5E06FFE21655ULL, 0xEBCD9DE83A683650ULL, 
            0x51171675B19AA984ULL, 0x42A1019974D1DCB1ULL, 0x8A90DFD6C317A1F0ULL, 0x4E4A488AB99D9102ULL, 
            0xA126026EF146BCE9ULL, 0xFA0BD843E5E4C2C7ULL, 0xE269928D6767DA34ULL, 0x600127DAB1657B31ULL, 
            0x11F6C453CC11B3F8ULL, 0x0686B76410C21FADULL, 0x72F8B8B22B0093A1ULL, 0x96585D78ADE4EB8DULL, 
            0xECFABA5F551474F6ULL, 0xF36AFD8B0CE2913EULL, 0x19811567164FCA9BULL, 0x9794C5078DFBA79BULL, 
            0xB1DD14F3FBB37323ULL, 0x3064E364B6FCF45AULL, 0xA86CF04072764C64ULL, 0xA211D6DF8610D964ULL, 
            0x8989178DE14CEDCAULL, 0xD538DC2978B06E66ULL, 0x3F2E74A0E82A5208ULL, 0x6572F1102C614084ULL, 
            0x69389BFD3F63576CULL, 0x04F681B712E17596ULL, 0x184CADCFD2D4B663ULL, 0xE617B66CF89024B4ULL
        },
        {
            0xC487181989895498ULL, 0x4652A4B5B80CCD03ULL, 0x2FF2599FEE3E898EULL, 0x4608415CA4C08D38ULL, 
            0xCBF83D7DF4A713B4ULL, 0x857DCBE19233C7D0ULL, 0x122B1B49FB368092ULL, 0xBC8508DDD54F5CECULL, 
            0xADA5D77F2F3E83CDULL, 0xA841CCCB1C26A098ULL, 0x7CB0D92AFA2A17C3ULL, 0x4C28651DD36E6842ULL, 
            0x36C33DAFF5CE4D73ULL, 0xAFABF2740724D203ULL, 0x3057002CBA4F9532ULL, 0xE31A2F78C765D698ULL, 
            0xBBC51DA57EAA9057ULL, 0xFA1BABF19D9F91DDULL, 0x9527CAE2D2BCDDD5ULL, 0x53FEBEE4527C6124ULL, 
            0x6C51BB494FF0118EULL, 0xDE7A98DE81AF8F88ULL, 0xB9E63821565503ACULL, 0x666EC1AADCD395BDULL, 
            0xC9E4363834FA768BULL, 0x7E748C79CF219ED1ULL, 0x9A81404B5C9BE17BULL, 0x469842C3707EA528ULL, 
            0x2C532564610B989CULL, 0x2B8F0B2E6E20C3BEULL, 0x6819A479E4A85514ULL, 0x50E737BBDA02505AULL
        }
    },
    {
        {
            0xF957990EF99D4764ULL, 0x110BA1158CBC9783ULL, 0xCE63BC3643913E74ULL, 0x7DB09F50FFE0788EULL, 
            0x4D1ABAC951CAD63DULL, 0xF43FFAB2F7E9A8AAULL, 0x182D40909D2CB76AULL, 0xCAD9FF1887207E3DULL, 
            0x675EAF96AA24D412ULL, 0xCA11C17F1181987EULL, 0x20BFDFDD70F414EFULL, 0x1CA0F9F18B99274AULL, 
            0xBDAE8527348CAD2DULL, 0xE6BE43C9B02696ECULL, 0xAF02824E1589CBD7ULL, 0xFD493E899DCE652BULL, 
            0x6D4168EA7E0A061AULL, 0x5D821017FB5EC8F2ULL, 0xFE0FBAB6788290D6ULL, 0xD22743DFD93A5809ULL, 
            0x32E34665A3EC9B81ULL, 0xF6D4071DB32861B5ULL, 0x2114D24032DEA29BULL, 0x2FA146A6C091080BULL, 
            0xEA029120BB7853DCULL, 0x6740E59E943D3F66ULL, 0xF97DF85B94FEB60FULL, 0x434F0D324CFE27B4ULL, 
            0x6F3794B344369876ULL, 0x64CF41D0E57FD276ULL, 0xF894BB9B9563A7F0ULL, 0x49052E3590EC5DA7ULL
        },
        {
            0x5F87F7292CC7E30FULL, 0x173B21EF43B2BD22ULL, 0xB74CBA37C177148BULL, 0x49E6B8407B809B2FULL, 
            0xC86EEC49E4A7910DULL, 0x6C27F69129E98817ULL, 0xC458523EE1CB6481ULL, 0xA1F2757FC9FD1405ULL, 
            0xB51C18F2016F7628ULL, 0x2A9AD3186DCC0392ULL, 0x842382DBDD2C4C97ULL, 0x6CC71A666A347327ULL, 
            0xD6E36A279C20E8AAULL, 0xAC3FD49870C60AEAULL, 0x4741A056C77C9103ULL, 0x08F76E67E50CAD15ULL, 
            0x5D5E7A2339A71CB3ULL, 0x61C8F8491572D867ULL, 0x62E3F735F90B5202ULL, 0x46561B8E87F05E96ULL, 
            0x5A6F63BBF7B094F9ULL, 0x21DC11048E172E39ULL, 0x295C6A67EFDBE59DULL, 0x70C954454F31C91DULL, 
            0xC64AAE81CA356171ULL, 0x287702232DB0F70DULL, 0x23DF2D98087D57D2ULL, 0x53F9E260FE4F7CBAULL, 
            0x1D3D7DAC66E96344ULL, 0x76441B960EE478E9ULL, 0xBEC95C0AB9B2D74DULL, 0xD55EE15A28E6F9E4ULL
        },
        {
            0xC1AB3821AB311967ULL, 0xF47DD03D8D849C2CULL, 0xD2E48CCFA9E12C16ULL, 0x28570374C895FDEBULL, 
            0x4CB7F8372356EEECULL, 0x5794BD6208E0B277ULL, 0xB3037FE54C57F577ULL, 0x1AE2324FFFF0A89FULL, 
            0x645532C499F373FDULL, 0xF133AC9CB1C3556BULL, 0x36C33FE8A724424EULL, 0x66D677864B5BE0AFULL, 
            0x168D671C85B66158ULL, 0x23155FF2946C136CULL, 0x4BF2F811040545D4ULL, 0xCA777E7C69BE2BEAULL, 
            0xB8A60721426ADF2CULL, 0x8112EC6F21FC5B84ULL, 0xEA2C23ABD3816BB7ULL, 0x3CDB10116F574D85ULL, 
            0x33AA098F24650610ULL, 0x95FFED50F1A847DAULL, 0x26360E44DB9E5A08ULL, 0x5E5CAFC4032BA7BBULL, 
            0x7DEF03F524973097ULL, 0x46DD802AC5CA5287ULL, 0xD65B5991563EA0BAULL, 0xDBF08A82327B274BULL, 
            0x9E993B1711DFD898ULL, 0x7C90526EB2171F66ULL, 0x3CFEA496F43EB3AAULL, 0xADA53D97337753DBULL
        },
        {
            0xCAA7BF23B28A4E2BULL, 0x05B290A4D540DF20ULL, 0x2F3D5DE93B98FDB1ULL, 0x5EB0078BCFF19048ULL, 
            0x99F4C3A864D08411ULL, 0x2BBE7090A3D1D786ULL, 0x5B56E47BBC144A25ULL, 0xAD5CCFBED2A27452ULL, 
            0xDA9CB910B77F14BBULL, 0x32BBBFE0EBFC6F14ULL, 0x1F6F95B44AE9FEE1ULL, 0x7B42A18F2970AA2EULL, 
            0xD51698B5E73F44BFULL, 0xC053FF2CB483E9FCULL, 0xD4308533EBD5938FULL, 0xD6D0069F623979F9ULL, 
            0x29E5AA89E72F287DULL, 0xC71068A8F3AED138ULL, 0xA43F4457D1F0B354ULL, 0x2ED5935E3FBD0C55ULL, 
            0x07D52860B5B1901AULL, 0xA66FEB25B209B64EULL, 0x019CBEB9DC9E3D67ULL, 0xCBC03FDC6F7F8530ULL, 
            0x674E5347BD478D7AULL, 0x605727A40EB4CCB4ULL, 0x7E2EAAAFD6A18B9FULL, 0x31433FC0DAEFAD79ULL, 
            0x65236543FDDD64BFULL, 0x8341DC0CE58CBCD0ULL, 0x0DE606D9A25A3F51ULL, 0xCE16FF2DEE6D9B08ULL
        },
        {
            0x0116EBD00562C411ULL, 0xAF83D7C983A28687ULL, 0x1FDE1EA4E5570E26ULL, 0xEB5DE5F3D1D55C16ULL, 
            0x7DEA9259865EC901ULL, 0x1F13B8E7680F648FULL, 0x22091D67DECCCC6CULL, 0xB63DA2E9F0D03448ULL, 
            0x3CC214C0C8A3DA51ULL, 0x1025C5AD5D15AA35ULL, 0x250CEB68716C4DD8ULL, 0x9D8B73187B5DEF0EULL, 
            0x81D36BD8E37CA475ULL, 0xD762601687B0F1BCULL, 0xD9823D65B85800DAULL, 0x731CCEFDA550D437ULL, 
            0xF32CE207B3775C18ULL, 0x14C601D262A6BDF8ULL, 0x52E2E15853DB80A7ULL, 0x2233E64E6BBF6D9AULL, 
            0xAFBB2154D37F71ACULL, 0x0C8D0C7BF45D1881ULL, 0x577B9B7F0C98AD7EULL, 0xED3B11991F5BDF9FULL, 
            0xC2B1B63951E1695BULL, 0xEB066E475867BA5EULL, 0x14300B95BF9297BBULL, 0x4557322DFD7B2C52ULL, 
            0xA67AF1098A1E9E60ULL, 0x71D6E35271812A56ULL, 0x63DB1BCD9F39AAE1ULL, 0x78E047CA62EB6605ULL
        },
        {
            0x71C59FA031C738E3ULL, 0x4DEAC3ADD10E5879ULL, 0xF7B23739F7D2DDC1ULL, 0x7CF9199620E09FD8ULL, 
            0x2F2A77C0B36C2251ULL, 0x7F172C0B027D473AULL, 0x6B6D020C648684A3ULL, 0x24C9FEE038A4E90CULL, 
            0x57A95CF148EB6E87ULL, 0xCBDF88CEF4C48692ULL, 0xF5DA18E5DFD9C43FULL, 0xB1196EC6C56A89A4ULL, 
            0x5D2666FB30CB030BULL, 0x79DB4F8CEF276CC2ULL, 0x31229C7369BA097EULL, 0x595CC58B986C641DULL, 
            0x473067494AFB6F50ULL, 0x101C7386BC5A21A1ULL, 0x007183C74F256249ULL, 0x2191F6329015E9CBULL, 
            0x163E72C35A54246EULL, 0xD239D1CAFE6E2A6DULL, 0xDF161FB324E5818BULL, 0xF76686CDA38B0BC1ULL, 
            0x8FCBC6F175A4162DULL, 0x810562B2AF7A7A89ULL, 0xA533C24FC0ED53F1ULL, 0x3AF348AB8E6DA5DBULL, 
            0x444E4C0F15C4C9EAULL, 0xA7C3D85BA038F7E6ULL, 0x076F6B65EFC6D39DULL, 0xD73917B5E0F2E607ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseEConstants = {
    0xC448C3D6783FBF71ULL,
    0x9DF06CA9802C57D3ULL,
    0xF94F3756C11EC2D2ULL,
    0xC448C3D6783FBF71ULL,
    0x9DF06CA9802C57D3ULL,
    0xF94F3756C11EC2D2ULL,
    0xC2ADE6614F39F671ULL,
    0x8EFF25D6C72900F7ULL,
    0x50,
    0xCC,
    0xFD,
    0x82,
    0x4E,
    0xBD,
    0xFA,
    0x85
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseFSalts = {
    {
        {
            0x25DF33FEEFDCBC32ULL, 0xC34B72E0CC854CB4ULL, 0xEF9BB74121D2A910ULL, 0xBD6497D5FC2A5514ULL, 
            0xC1D91204BF8C81F4ULL, 0x66BB9E5676074EB0ULL, 0x4C733AEF1A8778A7ULL, 0xB99B1E537B0B95ADULL, 
            0x006256854A47B03FULL, 0x5533BACF0558FE31ULL, 0x69931EDC473AAFB5ULL, 0xED7131EA7D24828CULL, 
            0x47DD551F1A4FD6C9ULL, 0xB37D0C7CF5FC3819ULL, 0x5DF05D054786D722ULL, 0x246B17A5230F37C0ULL, 
            0x4B8CC49B01BD8260ULL, 0x6F3144614991EE86ULL, 0x04373C10EE1071CEULL, 0x93B91EC7E81C8128ULL, 
            0x94B1C37211D60E0EULL, 0x67479FD63D10FE3AULL, 0x07B51DFD385667DCULL, 0x2C1E918119886ADAULL, 
            0x39FFB60C75849EF6ULL, 0xCF05475898C616D7ULL, 0xECF1DBCAE64B9CB2ULL, 0xCFDB84FCA32C294BULL, 
            0x8D00A82E241BF24EULL, 0xD73C51B5BAB1FA14ULL, 0x76C08631AFBDA196ULL, 0xF743DF8D33EB8B9DULL
        },
        {
            0xC417E9BCA3383ECEULL, 0x4040719FC8A3A51FULL, 0x456984537F8AA2A4ULL, 0xC27973E5A4E63EC9ULL, 
            0xA05535383359DBBCULL, 0x4A3F708D78D31C09ULL, 0xBFD4BB431043EEC7ULL, 0x0C41AD4837EDE171ULL, 
            0x70805E19DBC53105ULL, 0x75EC1A24DAD6E2BCULL, 0xD4CCAF0D69258A3AULL, 0x3C04F647D2656D02ULL, 
            0x3B6347888B741BACULL, 0x3130740B2ECE73E6ULL, 0x67FD73B115AD2018ULL, 0x5DD1C9E442E3A8B0ULL, 
            0x6CD86B7402F17848ULL, 0x581B869C871C7392ULL, 0xDCF53EC9CC63E76BULL, 0x230AEB4E51BD65C7ULL, 
            0x34BFEEA265269ECBULL, 0xD641B2E422DE117AULL, 0x5E32EEFA9AE82801ULL, 0xC0D75A1F6996DAD2ULL, 
            0xF4346E0342274FC4ULL, 0x02A9BDCA7AD45891ULL, 0x48956B19BA88F313ULL, 0x403676DBA19AC534ULL, 
            0x78B197A153746470ULL, 0x4FCE2440A5B0DC69ULL, 0xC71C84712B2C6225ULL, 0x49D2989577120032ULL
        },
        {
            0xF0E014168506F66EULL, 0x5534E716DC24F234ULL, 0x173D5A7568716C65ULL, 0x39FB0D7764F486DDULL, 
            0x71CC6E55E24CFEABULL, 0x4A62E84B0E7F752AULL, 0x9DA40F4829DF7596ULL, 0x2AF0A77AA0F4E52EULL, 
            0xD080679DB62A528FULL, 0xEEE80BE7960D0566ULL, 0x741C712A45FA66C6ULL, 0x6AD39B3AF1821905ULL, 
            0xB8360F1D6E4E3670ULL, 0xA01D09A65E83435DULL, 0x25921A7CCCF29A61ULL, 0xA2F9EAF246681C16ULL, 
            0xCFD53EB3CF4DA898ULL, 0x76FF5A6A0AC2B108ULL, 0x9232C69CDE961BEEULL, 0x50BFB7F7B3504A12ULL, 
            0xF130A4EE28C7B296ULL, 0x8337D539B1926A8EULL, 0x13B78CB3DECF6770ULL, 0x65A19ED285F4F11FULL, 
            0x777185A1DD9D17F0ULL, 0xC56E579800B2E173ULL, 0xC6A099457C38F148ULL, 0xEA075752EB1E1E76ULL, 
            0x7DC879FA437A4E79ULL, 0x679B51A2D5F77E1DULL, 0xE5C137E7E786D1F4ULL, 0x92F3258DAAAE48FEULL
        },
        {
            0x01CCC7ABD3E59C44ULL, 0xAA15B50A2E5661A9ULL, 0x9EBA5287C1D03E22ULL, 0x29D82164DAA7CA21ULL, 
            0x7105D1B9F337F72AULL, 0x56AF4C4E89188C87ULL, 0x8885837EE7091CE4ULL, 0xEEA793B7695D6A09ULL, 
            0x18FB9B077A73BEA4ULL, 0x0C373AF32E6EA16CULL, 0x9637428D0B8BA66CULL, 0xD1940609BC129B03ULL, 
            0x40E25D7FCA6E7CA2ULL, 0xB2C8BCCFA59904CCULL, 0xDC0201B299F611C7ULL, 0x182A69AD92655EF8ULL, 
            0x62299F2B8AB093ACULL, 0x6CAD9A71FF0C2A67ULL, 0xA7552C845DDA72E2ULL, 0x8D606EBBAAE81C17ULL, 
            0xFC3AA2D2F42CDAA5ULL, 0x20A5A22B559F0002ULL, 0x8F235A2F29833AC9ULL, 0x15CA2DB35EBD6B84ULL, 
            0x1C6A47C1DC3D4472ULL, 0xC8FBD07A3D5D154FULL, 0x1946753F02F41187ULL, 0x76C9A7953BF10B39ULL, 
            0x984CEFF0F0FEFAE3ULL, 0x301550D99E253E05ULL, 0xF65E8D913EBAABADULL, 0x7F19E38250DD1358ULL
        },
        {
            0x50A7DB270CFDBB54ULL, 0xB9449D28E010C406ULL, 0x722A573ACE7C08A8ULL, 0xCCFCD8CFB25FC566ULL, 
            0xEEE4290272E848F0ULL, 0xA808CC0A900262DCULL, 0x5F086ADBD702F993ULL, 0xA66EEF6483E44B64ULL, 
            0x55DA6B9EE8C2C6BCULL, 0x06899C234F1CDF69ULL, 0xAA3FD23369FCE0D8ULL, 0x2C6A757069679890ULL, 
            0x6760BFC68E2A7965ULL, 0x4CA9A2BD3995CF82ULL, 0x7F4313CCA6EA4E36ULL, 0x006B626B0EA0362EULL, 
            0xED6F92F52DC9469DULL, 0xBAFF3471D1F86F50ULL, 0xA6A5D537E690A791ULL, 0x4ECD6A8FADA52AA5ULL, 
            0x8BC948270B655BA5ULL, 0x2000E5031DA13868ULL, 0x3FB5E2DF8BEFA172ULL, 0xF28AEDC73C79AB49ULL, 
            0x1E6446569E4308FEULL, 0xEB75118F2C8F5D6BULL, 0x1F0AF77A9F728507ULL, 0xB56D0BED7A5287ABULL, 
            0x810F13AD14DB2B9AULL, 0xE497E761957C41AEULL, 0x5A3E699CFAB53306ULL, 0x69679A46FE9E32B4ULL
        },
        {
            0x4DCF5B8AE2E2E044ULL, 0xEFBBB1C9F1FEB25CULL, 0x5B2E6F5AD71D002BULL, 0x289E4ED344C437FDULL, 
            0x2AC0FC5AA79C4E26ULL, 0x9BF7D21F70B45E9CULL, 0xD65A8F58B781BDE6ULL, 0x7E2B17B11BCC6B20ULL, 
            0x6B1C32C744E3F4B8ULL, 0x6A8F64FF93199907ULL, 0x8D383823602253BBULL, 0xF08BEEA3C94A6713ULL, 
            0x024EA3D002AC1873ULL, 0xB778B26E52B846FDULL, 0x87DB7C06C6593961ULL, 0x63C73C84EE2C9953ULL, 
            0x21F21E6CF014D83BULL, 0x0944827841B27D90ULL, 0xACE6D718274C2917ULL, 0x7C6E8B70A1702CA0ULL, 
            0x4F65743140B61796ULL, 0xAC6D9B1E46753C54ULL, 0xF3E04B36AE0934E0ULL, 0xB96A6D55D9BA26C7ULL, 
            0xD972DB02224428C2ULL, 0x03B79F50D70A64F0ULL, 0x609DC0FB9BC6ADD2ULL, 0x99A95550AE53D210ULL, 
            0xC4E8101290A493A5ULL, 0x0DB76023FFD7E1AEULL, 0x22748717004F9A04ULL, 0xC753FA62DF126031ULL
        }
    },
    {
        {
            0x7D07497F24D46B92ULL, 0x77DCD0D3B84BAA9CULL, 0xFA8833AB8DA1E912ULL, 0x10D1DA3A529DDC98ULL, 
            0xB82197E4DDAD1E91ULL, 0x621572FA5B97102FULL, 0xF009A387C85DA7DFULL, 0x8703CE12462C64B3ULL, 
            0x6161F23C8F05CAA3ULL, 0xC9EFAD3907A84C41ULL, 0x828F56EE6BAA9EC2ULL, 0xA637F849CAF7BA7AULL, 
            0x2F8999C2AEEC761BULL, 0x89B18D7BB65DCAB1ULL, 0x053E81C335C3E085ULL, 0x5770B6272D9837C0ULL, 
            0x6A0A0A544B9BC0CDULL, 0xC6BFB734996FE787ULL, 0x1AB13FF009699C67ULL, 0xF22271392188E5ADULL, 
            0x129C162EB74DEA60ULL, 0x59769853CC91EC5AULL, 0xAE5CE51AFB4F89A4ULL, 0x02E97D813CE2A56DULL, 
            0xEC77277DD1A18C66ULL, 0xBE713C539D07473FULL, 0x6405DF52B886ACCCULL, 0x9651C3EEDF4EBF95ULL, 
            0x2B3417AD9045FCC6ULL, 0x73CD216FD275C792ULL, 0xC44B4FD005D46835ULL, 0x91B4EE226BAB038CULL
        },
        {
            0x8B831CBE9F514623ULL, 0x875E0E8D50088F80ULL, 0x217CFF81B2E2317BULL, 0xDFAEE9713527E902ULL, 
            0xD4D4AEF0F7B78180ULL, 0x2F7B6C2636BF5388ULL, 0x741FD8ADC1753A93ULL, 0x7158A46A941BEC47ULL, 
            0x61E692370084A011ULL, 0x09F3BE549C51BDEDULL, 0x6A8212E1E7352E8BULL, 0x91F0674A596FF9A3ULL, 
            0xB31666EE8EF3F7AFULL, 0x90A9CB198DDF24B6ULL, 0x8799804D969C1E9CULL, 0x70B87C0975911B2AULL, 
            0x6FE86B06C2B18A09ULL, 0x94A312ADE76E0846ULL, 0x5B7040D754083891ULL, 0x59BAE9DF2E450B87ULL, 
            0x5B3D270129574608ULL, 0xC48DE6861904764DULL, 0x7AE5B2192BCB7ADEULL, 0xFE1A4E01C53A14F1ULL, 
            0x684ED9C2678B900BULL, 0x7F350982BE461DFBULL, 0x35CDE66A0E3F3B24ULL, 0x5FD71949999E9739ULL, 
            0x759FCBDCCC5498B8ULL, 0xC8999354B1B52B31ULL, 0x99C96DF506871CC3ULL, 0x0D6532776023F138ULL
        },
        {
            0x43132917C4843091ULL, 0xABA1C28114AD05C4ULL, 0x8FA44176E93CFE56ULL, 0xE0702C3FDFCBC24CULL, 
            0x1E98EC6973BBDBAFULL, 0xB42994CF12B38E44ULL, 0xBC91B770B91B2357ULL, 0xF33144A8FD66C844ULL, 
            0x91E0269343048BC5ULL, 0xC57F1E5EDF48590AULL, 0xBF544CA2AF3EBBFBULL, 0x4227F7830C1CABB6ULL, 
            0xF7A7CB4155B5A8D0ULL, 0xF325C0023025466EULL, 0xAA12ADE79CC1CFBBULL, 0xE5B558DDBAF92143ULL, 
            0x2DDA1BEEF4283544ULL, 0x7F2E637A925567DFULL, 0x91B3664400847434ULL, 0xBEAA726807B09224ULL, 
            0xC69815FEEBBF55A8ULL, 0x4E2EEEA17CC73D14ULL, 0xD42EA9EA6431B988ULL, 0xAEF91DA2EE1A7483ULL, 
            0xBE15E8DFF92D6EC6ULL, 0x7B0B9F861C73A35AULL, 0x1B43A27AB22D43D5ULL, 0x0119D8EF6618DA59ULL, 
            0x86B0E5F13E0C477CULL, 0xABC01A5896286935ULL, 0x3FF58B6E9ABC4D97ULL, 0xD4F5F64A54D6E8F0ULL
        },
        {
            0x45ACDE9184F9D3D0ULL, 0x179A03B9D7C2C543ULL, 0x40F4B1E30812DA7AULL, 0x6B45C0294F8F639BULL, 
            0x14539169FEA10096ULL, 0x57BBBA54348C3178ULL, 0xC45521DA5C15468AULL, 0x6DA8AED9EF2C6191ULL, 
            0x47FF0D1524545D3DULL, 0x9CE5D73756CBFDABULL, 0x1844F7CE8C30AFEBULL, 0x1ECBC74FA81383A2ULL, 
            0x0AE1BCD6AF0E963FULL, 0x99E28B56DD474A56ULL, 0xD9CAAC5D9D2BF7C0ULL, 0x5FE8B65037F7956AULL, 
            0x07AF2C6CF9BD5968ULL, 0x92FF533DF4267D25ULL, 0xF717BCFCA4694C8AULL, 0xCBAE2699A5DE37EFULL, 
            0xFA73E33AB7888CDEULL, 0x747E7559ABC2DB7EULL, 0xA440297F2B45268AULL, 0x49DA881B3F3E425FULL, 
            0x13ECA14249C5BA48ULL, 0xA2547C404BD8E354ULL, 0xDBCBCF29F9F1E157ULL, 0xAF3FF86D9AAEE7EDULL, 
            0x4DD443C0DA9C12BEULL, 0x78BFA39F7A2F490BULL, 0x780038B969CCB8E3ULL, 0x9102E0CC7DBF5A2AULL
        },
        {
            0x2F2E7A2C3C6543E3ULL, 0x298AF5B4D483FEFEULL, 0xF084090E07D16014ULL, 0x31B2FEC8A5CBA26CULL, 
            0x42C02BED27915784ULL, 0x78554305F543772BULL, 0xD1B9AAB07999274BULL, 0x5681BEDB311A915AULL, 
            0x5306E54E7FEF4EA9ULL, 0xA7D673473EB3B591ULL, 0x2DD6AC771F938FCBULL, 0xB2A7A566743524FBULL, 
            0x20C50EB1EF398C19ULL, 0x019BFB1C6485943DULL, 0xA34E0D88D3CB1E70ULL, 0x8B152B6E7EFE0195ULL, 
            0x44184B249AA230F8ULL, 0xDB472827BFA1F7B2ULL, 0x030621B4BEA48631ULL, 0x57A3C39C84B3962AULL, 
            0x7EDF632F9253C217ULL, 0xD7766205256DABBCULL, 0x5AF081922FB1861CULL, 0x1F2B0FCBA33644EAULL, 
            0x2524138870651F35ULL, 0xACD21C5DE77CA03CULL, 0x99092AC196852759ULL, 0xCB9359731023E87EULL, 
            0x0A90F78C28FDF913ULL, 0xC9344C7EED228ED9ULL, 0x0E8DD154EF1B9696ULL, 0x72A06A3B1EB983D4ULL
        },
        {
            0x22CFF5431B560FF9ULL, 0x2CCAB1A6951DAC7EULL, 0xB4E85F7D7D271BE6ULL, 0xE3B8C1FC28F8021BULL, 
            0x1705E17D1AB3A31BULL, 0x88C8122FF3983629ULL, 0x8F60B77271D07DA2ULL, 0xCC7E04AF51CF1B86ULL, 
            0xB6E9A4722BC82B25ULL, 0x814193354FCA7128ULL, 0x619559F5B5BBE53DULL, 0x60BA1625EE50529CULL, 
            0x9241B6928847F0FAULL, 0xD323D8CA0D0A9F3FULL, 0xAC0A40B51F5E6AE4ULL, 0x3159D8C2E49501CCULL, 
            0x1EF8FC7C67D31989ULL, 0xE6795198C727A759ULL, 0x5A164293E70A03A9ULL, 0x1B19F7ECB4C5B7FBULL, 
            0x4F52EE01D1D35922ULL, 0xCCC57D8247D141E8ULL, 0xEE4CFC33240ECF08ULL, 0x4D498D41115E5276ULL, 
            0x1FA1C765143256EFULL, 0xAEE698BE360FA71EULL, 0xB0378F941C0AA95EULL, 0x98544061442912A3ULL, 
            0xCFB0C92A472748C4ULL, 0x6E4D1E5CFA0723E4ULL, 0xA0534C27081FC518ULL, 0x43D754973FBB5907ULL
        }
    },
    {
        {
            0x4D3EEBE46C470623ULL, 0x67D6CE7A9C847718ULL, 0xAFBC7CBF0158668AULL, 0x5BB3E8C19C9F62E6ULL, 
            0xCFC5CF9F5D584C6CULL, 0xEABDEC22A0BB9AF4ULL, 0xA715409FA513BA38ULL, 0x283D7FB5655D402BULL, 
            0xD6C7B21C8E816523ULL, 0xFC65904ADF6AF217ULL, 0x6330C3127904A8E5ULL, 0xDAB8BF91BD828002ULL, 
            0x942082351724A44EULL, 0x6AC3D85A220B46DDULL, 0xE10E7938F95D0796ULL, 0x37B65087CBE2E059ULL, 
            0xF4188A12A73D7E83ULL, 0x085EBC29FCC78C6BULL, 0x46486B53E3873D33ULL, 0xB9EA8A4F26A975C6ULL, 
            0x1362F549F83B8ED8ULL, 0xA7D9FF6291946770ULL, 0x1EA4639542946B0AULL, 0xC828AF686876BC23ULL, 
            0x7CDFD28ECA832637ULL, 0xE638555DD1CA7E4DULL, 0x1F1103103477CB79ULL, 0xA739B13EF7DA5041ULL, 
            0x5FBBA5721DCD90EEULL, 0xE5E5AA820AFE79AEULL, 0x10E5AED024232AC2ULL, 0xB14E6D0622221ACDULL
        },
        {
            0xDB2E7403505CA4D9ULL, 0x3D87642820E76408ULL, 0xC5C43BE296C3169EULL, 0x3CE303C597CD0CD2ULL, 
            0x273EDEA630D3E78CULL, 0x647C98690026B658ULL, 0x95790C05454529B3ULL, 0xA402E288432741B3ULL, 
            0xB8C5950EF3821376ULL, 0xF56C30160AFE626AULL, 0x9344F3DF31E2C62FULL, 0x641D4EF5C3D1A67EULL, 
            0x50465D8274AC54A4ULL, 0xD0A1257996CF9DF3ULL, 0xA67FAB89D1BC5766ULL, 0x58BFDEEF4FBF8EC6ULL, 
            0x46667B0D4B56DCAFULL, 0xB2C42EEE98EBE980ULL, 0x0FDF14531EA720C1ULL, 0xE0264C4F874A77ADULL, 
            0x601EC476DF6B91EAULL, 0x8DA488B2ACF2326CULL, 0xF9534C91A1A2F688ULL, 0x95D9F5844282D477ULL, 
            0x38C65DF535104894ULL, 0xA08613044D1B675DULL, 0x0FBBDC81514C206BULL, 0x953E16EEE94A6918ULL, 
            0xFE3E07D1FA294BA1ULL, 0xFD0813D41F374605ULL, 0xD0C72ECE8E9D21DBULL, 0x934B6C0D658729B0ULL
        },
        {
            0xD085D1D2C7BB8AC5ULL, 0x67DDB7B226746905ULL, 0x1EFB2522B7A4CDBEULL, 0xAEE064EBC259B0D5ULL, 
            0x73B5A7736CA65DE2ULL, 0x57421CE9D33434D1ULL, 0x7045A9B2EAAA4509ULL, 0x97CD9CED2F1C36C9ULL, 
            0xD1E9AEBF3BD27B43ULL, 0xF7548F28724A2C3FULL, 0xB851924869BF4F67ULL, 0x1D1B160B1021A9BEULL, 
            0xCBAB3D7F8396D65EULL, 0xE6F5549F1AD280E2ULL, 0x3B225D6E7EEBF913ULL, 0xE2A994F84AD4F303ULL, 
            0x55DE0E8A7D0188EBULL, 0x59D3E3A6B20E3B3BULL, 0x571B32CF9D8F8AF5ULL, 0xBE6959EBFCF5E55AULL, 
            0x10041FE8BF6AC7DAULL, 0x06AAB1135B601C63ULL, 0x4C37AE7A543499DAULL, 0x6F55A3F59B990597ULL, 
            0x93A6163223D1E324ULL, 0x1B52972536530F2BULL, 0x5A984E0BCC1BF8EAULL, 0xD4DC7C695AA116C5ULL, 
            0xF4F3FDCE6D5A4AA9ULL, 0x1D20C810AB119067ULL, 0x8E76858FBA1BD86FULL, 0x4A7E7017185B3079ULL
        },
        {
            0x9153AB667BF7F2E2ULL, 0xB7166A818BE71B77ULL, 0x16025768C0189DB8ULL, 0x6FE549FB20D33EBFULL, 
            0xA2521320BA03286BULL, 0x2F429C8A0A5B6B40ULL, 0x15B539B45920ABB3ULL, 0xCE0D860E61690206ULL, 
            0x2F77833037D9DD87ULL, 0x5EE2F1D2DAB8370AULL, 0xD500091671E6CEF5ULL, 0xF20B3B0FC8AC9A5CULL, 
            0xAA0C3D0A0E3226DCULL, 0x454C8E3402DD0B39ULL, 0xDD3CB381AB98163EULL, 0xA0B00F3BA4290DFEULL, 
            0xC823D2CF5269705CULL, 0xE3494FA5D802282BULL, 0x05D386BBBF2CB898ULL, 0x1BEA735EBC6E66C4ULL, 
            0xE10E3E012B24C878ULL, 0xB7FAB3B8E1EA83F2ULL, 0xBED4199A0F03067AULL, 0x659D41E7DBB58AD2ULL, 
            0x0289CD508A82805EULL, 0xB0E29E8985CA0BC0ULL, 0xC34B666F83CF455BULL, 0x2929CCCF95F270C7ULL, 
            0xA235281DFE87066AULL, 0x99D7332162ABB0D2ULL, 0xBD78D7C21F1AF527ULL, 0xC4712E9571431A6DULL
        },
        {
            0x54E3E0DA4346D05CULL, 0x8A4CD25F8BCF0781ULL, 0xF887BDF702D5806AULL, 0xC20C3409BF0CA4D6ULL, 
            0x1CB42229568F491BULL, 0x0DCE651355998191ULL, 0xAFD6D47871C98B89ULL, 0x25234A706B4BF355ULL, 
            0x68268D1F32FAE87FULL, 0x918494EA9738EC41ULL, 0x4D3966AD3875356CULL, 0xDB36C0717C8FA130ULL, 
            0x72F09AE4E3920C64ULL, 0x00FDFAE5665E71E4ULL, 0xEFD2F4F4FB9C76A1ULL, 0x4737F63456931ABFULL, 
            0x353851FB8C285D24ULL, 0xED88289F79DE526DULL, 0x10A91ED29539ABFDULL, 0x34A6F3F31ECD7711ULL, 
            0x854B88B946D577E1ULL, 0x88F2347A0D9DE289ULL, 0xE530E0066E849DDAULL, 0xA3609E0E3CD4634BULL, 
            0x55E79F4104954355ULL, 0xFC7589CCE8FC0AF4ULL, 0x96F54E337BE7E113ULL, 0x3AAF770430705058ULL, 
            0x425FC79BD40FB153ULL, 0x64DB19F7E699C464ULL, 0xD3E143B0AE1B6E08ULL, 0xC3B242D46264FE33ULL
        },
        {
            0x5D777803331DA5FDULL, 0x0319BC46E1ABC814ULL, 0x9238EB25E28A696EULL, 0x91871009B3F6DC72ULL, 
            0x3BA92C563C6B1082ULL, 0x53854DE0D152706BULL, 0x8B167DD045A208E1ULL, 0xB8B3E1832B563794ULL, 
            0x7A7D829A656CCC26ULL, 0x8AFBA08F589ADDB3ULL, 0xACC1BE40DE798ABAULL, 0xE882C30B8006EB81ULL, 
            0x3B04D5FBCE496878ULL, 0xC3E6B4982B1304CCULL, 0xB218A233D220FF78ULL, 0xE491B76FEEE55F91ULL, 
            0x08B2A4DC48CD8E06ULL, 0x0298C7BC088DDA6EULL, 0x8493FDB1360E41CAULL, 0xBD2BA1237706CAE8ULL, 
            0x517386422FFCD654ULL, 0x6D61FD5BD739FCE2ULL, 0x22F9D87111869F84ULL, 0x94753C05010D1D90ULL, 
            0xB6C165D37E987D57ULL, 0x53FC4D34E71DFE40ULL, 0xF71D4E6AA814D12CULL, 0x7DE546FE7A011C47ULL, 
            0x6F414D71D6EB6CA8ULL, 0xBFB38A90D9EC83B6ULL, 0x3F68F25D740B7B29ULL, 0xC6163A551C4F7B9EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseFConstants = {
    0x9B0455ADA8BA2AD1ULL,
    0xA0357D4A13A3B106ULL,
    0xE15731F5E7673CB1ULL,
    0x9B0455ADA8BA2AD1ULL,
    0xA0357D4A13A3B106ULL,
    0xE15731F5E7673CB1ULL,
    0x007E1CB82B768603ULL,
    0xAE267FC8551E21AAULL,
    0x47,
    0x9F,
    0xD5,
    0x82,
    0xBD,
    0x42,
    0x73,
    0x26
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseGSalts = {
    {
        {
            0x5C2FB5DBAA01DA28ULL, 0xE0CB615616783CA3ULL, 0x3F8EDC965ECFDE77ULL, 0xE40CF824B445C849ULL, 
            0x15C6AF38A25ACF06ULL, 0xE5AAEE5DB922F13DULL, 0xFEF3F3C544DA2BB5ULL, 0x526360F7D947F799ULL, 
            0xB46FCA446C4D62F6ULL, 0xE29C413B4709E178ULL, 0xB436563055008469ULL, 0x7E6688EB5EAF5D4BULL, 
            0x5370485B95B7D92DULL, 0x3710DC708A11FEE0ULL, 0x552DA96565ABC9A7ULL, 0xA99DB452334A6B3AULL, 
            0x5E9A4DB7B0660C69ULL, 0x7CCC8C2BDCD73D0AULL, 0x98C1F4DE35AF5F9DULL, 0xA44D67B8F4545B38ULL, 
            0xB38D69DDEE1319F8ULL, 0x82C7522CA90A6505ULL, 0xA9BCAC357E791835ULL, 0x68D970316829994FULL, 
            0x574CA4FC8536B955ULL, 0xFEFE8AFF3156615BULL, 0x371A643FE8E838F5ULL, 0x0D8B7BE2114962D5ULL, 
            0x58D7AECAE03F2738ULL, 0xF7FFD19E21B09E8FULL, 0x4781F013F962F808ULL, 0x004E8B4C73E5541FULL
        },
        {
            0xFA3EE82309D34C14ULL, 0x8DCD43880990978FULL, 0x530EAD6CD377DA6EULL, 0xACE7C244B0563513ULL, 
            0x21FE1A154E6A1DA4ULL, 0xB6FCB5B6F7D89068ULL, 0xA5DF77AFA95B73CFULL, 0xA56B3AA7090C1EE8ULL, 
            0xEC529E3EFBD2840DULL, 0x243E8B90A255097FULL, 0xF041D12BA3D9E9FCULL, 0xEC1096D8B878A2E6ULL, 
            0x424FBD1A81778436ULL, 0xBC05831A272FCD1CULL, 0x058B0E54F700A54DULL, 0xB5FE9947E610A94AULL, 
            0x7D597CE7F709D04CULL, 0x1251058B4514DBF2ULL, 0xC701D097ED43636FULL, 0x7B3A9389F227A2D1ULL, 
            0x977E2321F24573CBULL, 0x014FB7B6B245C7DCULL, 0x3DF975491FDD8251ULL, 0x1440E71CFE059EACULL, 
            0xAED47B9EA3AC7911ULL, 0x4B7173AC2C372B98ULL, 0xE045AD19EB11E941ULL, 0x986424692FDDCBF2ULL, 
            0x154AB843ABA15C32ULL, 0x47B0332D685A50AAULL, 0xB74146DB2E22BDB0ULL, 0x2464BA90457036A0ULL
        },
        {
            0xBC34B985F16A2653ULL, 0x59BE2248318960AEULL, 0x542A85BA75C981A1ULL, 0x8F3498F34A7D344EULL, 
            0x634D70B552C8A52CULL, 0x2F237FAC7A19B47AULL, 0xF61085E267681292ULL, 0xA0E998A42FD764FCULL, 
            0x000A8DD4AE047544ULL, 0x885ACC04245F6AFAULL, 0x17C0895479634C57ULL, 0x84010E313DC3B418ULL, 
            0x028C245A3807136AULL, 0xA96B2131EFEA5F14ULL, 0x67BCF1E51B820B71ULL, 0x6D3D4E8AC6E3373BULL, 
            0x956082558D13C0A3ULL, 0x0F3B3221069D349EULL, 0xE4A0F3BEADDEE340ULL, 0x5AC1E8F99A2C458DULL, 
            0x5B6C78B1A54C8399ULL, 0x0521CA271B9C340EULL, 0xF76FB54EB03D53CAULL, 0xB9A166585823E55EULL, 
            0xA806786F058F3A6AULL, 0xE5EB7E2433CCBD3FULL, 0x1724B573A2B26232ULL, 0x0E054D38317469EFULL, 
            0xE964D8C26305B6F2ULL, 0x5E3B19BEE01DB6D3ULL, 0xD737D0A3CC0F308AULL, 0xE9719B4D712A0A14ULL
        },
        {
            0x6B6520A2B988BBBEULL, 0x7332763E9941BB5DULL, 0x988832F6171EDCB4ULL, 0xA9AFA84FA3F8AC41ULL, 
            0x4556DAD36008F205ULL, 0x993498EA5CF8C993ULL, 0x6964D38795B21296ULL, 0x8622205D4BB0E65CULL, 
            0xD63E7ADA5A0D1374ULL, 0x5EEBA2C893272164ULL, 0xDFFF0AA7A65004A1ULL, 0xD983A706EF8C1A6EULL, 
            0x8B6E43D45D2C2E68ULL, 0x64D9FB93CD25F0EEULL, 0xA9DC78DB4322EA56ULL, 0x136A8F1260AAB5E8ULL, 
            0x8E74568AE52DFF70ULL, 0xEF6B958BEB41FDAFULL, 0x6CB220F641978E01ULL, 0xB384164BCA140A50ULL, 
            0x2E9CB1F6A3572389ULL, 0x6CA1AE0606277E49ULL, 0x72A4F0FF3C8D0186ULL, 0xB59F3F27DF2D4B1AULL, 
            0x351323D02007CE83ULL, 0xDB6FAE4290F06FCDULL, 0xC9B9962237F4F989ULL, 0xCAEE5284CA809E77ULL, 
            0xEDE0B39C4D4B2772ULL, 0x17BA3DC2D4764406ULL, 0x9D342503EF14A31EULL, 0xDD1F53F2B8CEF92AULL
        },
        {
            0x3F3933DB53A63E25ULL, 0xB4835AD9B5D4D4CDULL, 0xCE06B18BCA36B900ULL, 0x3F66F2B0B939598AULL, 
            0x5387EAE674F34637ULL, 0xB454844B0C5657A2ULL, 0xCF29691CE17C5605ULL, 0x4F36803355F925ABULL, 
            0xC2F09602E2FDAA58ULL, 0x0A7C005D74BAC390ULL, 0xC9970139F22728EAULL, 0x85DD05F3F566DC27ULL, 
            0xECCF6E0222FB91EBULL, 0x80CAA144CD248176ULL, 0x30062020F50307F9ULL, 0xBEC825F32A83E6DEULL, 
            0xC5FF6522D0991716ULL, 0x99AF16D8D265113FULL, 0xF8646BD9EBD236E7ULL, 0xD559C1A1F414FAA4ULL, 
            0x6FA522D67C788DEEULL, 0xD1B7317E7657BEF3ULL, 0x839CD7A0567CA37FULL, 0xBBCDC78113D57F6DULL, 
            0x796052831EC8E5C8ULL, 0xC3FCA2919DA3CD20ULL, 0x25644C6526E13219ULL, 0xD63021EC9CE656BAULL, 
            0xC5C1C24DB7957B6AULL, 0xBDAAB3D9C13052E7ULL, 0xDB71E8BC7BCBA812ULL, 0x0F693EB068D4F383ULL
        },
        {
            0xF5D181096A6AAA8FULL, 0x5FABB6D91D1FCB94ULL, 0x6AC33AB3C4D4F5EAULL, 0xCCF27BF1E1B13F7FULL, 
            0xF0EA8A2C04752528ULL, 0x6A5E9FDAA6B4EF02ULL, 0x7BAEB55FD0FB91B0ULL, 0xCF2AFE6E2A328A79ULL, 
            0x2BF521EB9B556F82ULL, 0xD811492AEAA9EA77ULL, 0xD45B76FBA8CC6BC9ULL, 0xC41E4D07766D28E5ULL, 
            0x9D19D51EB716DFDBULL, 0x043ECB92783A733AULL, 0x59E34A9AAD42A581ULL, 0x6C561399F905546AULL, 
            0xEC698B6C71C830E1ULL, 0xB8125FD935F5A41AULL, 0xEB8DF77EE8F31A11ULL, 0x21DC4BFD13A92229ULL, 
            0xD038EAFCB5AC0654ULL, 0xD96EBA6925660985ULL, 0x8B8B4C33FE3387C1ULL, 0x85287002FA6D4060ULL, 
            0xF05118A591FB678AULL, 0x1612B69C0B6DED5DULL, 0x565C631707E92584ULL, 0x60C835121EACC56FULL, 
            0xF615A390A956E9ABULL, 0x2F43BAEBF90B1841ULL, 0x7FF035B38E6C93FEULL, 0xAEB59711DDB4D0AAULL
        }
    },
    {
        {
            0x84F5CA7871C3C8ECULL, 0x344105D50BAB1E9CULL, 0xF1A4DEADFC436040ULL, 0x626234E0A9D04770ULL, 
            0x159DF148E3CEFE7AULL, 0x930C913C43FFDE9DULL, 0xF025AE0FFBBA8310ULL, 0x96CBF05C4620CA64ULL, 
            0xE691EED51E37E307ULL, 0xBC670AA6E72AF248ULL, 0xE83EE9E7F44E771CULL, 0x993D2DCD99C46F67ULL, 
            0xC4134E04E2D72B67ULL, 0xF3543F65E0B912FBULL, 0xE32BC4987BDE5109ULL, 0xDF41A2FC9196E928ULL, 
            0xA7F0F53B98A45A20ULL, 0x12EAD9110E41E0D3ULL, 0x70C4FEA9E18A738FULL, 0x361652B9A0B76A7AULL, 
            0x5108A4325BACD5A1ULL, 0x8E374A78E319DD69ULL, 0x28156A2AE5131BD4ULL, 0xBF86B379ADC67711ULL, 
            0x0DB93685EE835CC9ULL, 0xB73AED523FA64D82ULL, 0x00CEA83425D56A40ULL, 0x1CF012155EC69724ULL, 
            0xE387F201F0650B3AULL, 0x907963586293F7EDULL, 0xCD56481DE41F8A5EULL, 0xB1517061A8294BACULL
        },
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
            0xB5F4BF3169427B5FULL, 0x214EB08CABD05BAAULL, 0x2BE34BAA030B2C7EULL, 0x38726A56DDD99E49ULL, 
            0xA8FDD1993B47F572ULL, 0x686CBE8851ACA95EULL, 0xC5F610F2C58D737FULL, 0x76105BEA7CDC3C3CULL, 
            0xC32505D83CAF0596ULL, 0xF529409581583FFFULL, 0x8508E8F7618AAB1AULL, 0x4B62B39D5DAE758FULL, 
            0x6C0DE6ACC9121D8DULL, 0x472D6FA757304ED2ULL, 0x44FC5334695B1713ULL, 0xF991A3007E315459ULL, 
            0x4BE1885F1F3B20AEULL, 0xCE6D2D24B4670AA9ULL, 0xA6F32E05C1C0EE0EULL, 0xD53E60953722C67DULL, 
            0xB942195C0CC1179AULL, 0xAABFCD627B1C4095ULL, 0x0B983FDD3D73A141ULL, 0xEFAB33C20837C084ULL, 
            0x24CC67F7C96A259FULL, 0x099377D0220042CCULL, 0xAD2D9CAF85C441A2ULL, 0x0CE697C015B3DA74ULL, 
            0x9683B7A60F9F5C25ULL, 0x9B7CF0EB6294318FULL, 0xEDC779F8360E3E9FULL, 0x78F1659F8BDF8CBFULL
        },
        {
            0x6E5D2ED678BB032DULL, 0x9881F8EF8FDCA95AULL, 0x338A1B4FD1663105ULL, 0x7661C5E770C35698ULL, 
            0x5FF488ED4CCF82C2ULL, 0xA57C01A4CF656228ULL, 0x1A674EFE873B9B21ULL, 0xE3892AAC8C8CC791ULL, 
            0x68F88751870C0EE0ULL, 0x1B72BB0AC7409D2FULL, 0x5564DB182441EAC0ULL, 0x893FF518056BF318ULL, 
            0x71074D54FF78ECA2ULL, 0xE757FA1B418230D4ULL, 0x80663DA2F1D8D01DULL, 0x48C108EB9430B63FULL, 
            0xA03778157D88D404ULL, 0x17AB11623E71A821ULL, 0xBDFFEC427D793F91ULL, 0x0FB23384ABFF02E3ULL, 
            0x1E977866C6D987A9ULL, 0x0D5EFE228CBF367BULL, 0x266D699C07E02B65ULL, 0xA09DD8FFF47DC742ULL, 
            0x12B746550BE9D324ULL, 0x34481EBF1772A2E2ULL, 0x15E38943C84B616DULL, 0x76E48B57530B5F7EULL, 
            0xCA611B7D140FD980ULL, 0xFC0587B181330B3DULL, 0x4B56805B9D2F4B94ULL, 0x7F7122327D6DB9A8ULL
        },
        {
            0x6EE2B3D99B03D4EBULL, 0x0C117472D4178BACULL, 0x7D6FB0C3EFA3D0FEULL, 0xA7670A234859F6C4ULL, 
            0x71F4D5E1BF09DF48ULL, 0xD45571E958C440B0ULL, 0x3502A4C0017AA4F0ULL, 0x87215E82F3DEEC29ULL, 
            0x949733086C4FC00AULL, 0xB26589E1431A9AD0ULL, 0x8A252C63B57C22B6ULL, 0x236888D9BB1FE3F1ULL, 
            0x1FB9178E4EC4D590ULL, 0x9C7692FCB0FC6E08ULL, 0x7BBE426DE5B04025ULL, 0xDF85293A1D901B51ULL, 
            0xB73A5042AF1EE543ULL, 0xC44945B876F85E27ULL, 0x3DAC4100D3D8961DULL, 0x9A2A6DD07EE91444ULL, 
            0x928CAA6B20AA51C9ULL, 0x5AF4101865FB7FE1ULL, 0x95CB0159D5520927ULL, 0xCB03C8B16A726D82ULL, 
            0x255693BA37CB5D2EULL, 0x8C425F59F55DF9D9ULL, 0xEA1289053841B6E5ULL, 0xA8D6E53A5B9F7FC9ULL, 
            0xD26E81047960057AULL, 0x02178EAE71835A47ULL, 0xE0D89E9B2AC3CFD2ULL, 0x67123D6914CB5717ULL
        },
        {
            0xDE73863DA64949CBULL, 0x2F494833AA6AE1D1ULL, 0xCB924F3FD638BFCCULL, 0xC00BB3CBF4FC9943ULL, 
            0x9999A4EF2635C438ULL, 0x7CABF4038C4B97E4ULL, 0xD5B95D75A2D2A8C8ULL, 0x767C2882270FF6D1ULL, 
            0x92D84BFC741C34B1ULL, 0x30DCE1956C0C73DEULL, 0xFE5B5748163C1453ULL, 0x878A65514847D150ULL, 
            0xF0CA79A2CB0130D3ULL, 0x816D7A1B8C409B3BULL, 0xBA9DF793333BEEFDULL, 0xA7F2ED1209897146ULL, 
            0xA986288D264A385DULL, 0x29961BC5C0550F79ULL, 0x65B5C1C9C1273F8AULL, 0xD97B7D43F0B30737ULL, 
            0xBF65A5C7115BF1A0ULL, 0x1812D6B6233F2F48ULL, 0x61E22CF3C2311B4AULL, 0xE15BA6723E953F9DULL, 
            0xBA730117282EE412ULL, 0xBDD7E26FE6B83E03ULL, 0xE28B72C448196017ULL, 0x1294B6BC8B2B5F95ULL, 
            0x4131607E2C1818FEULL, 0x3483EFBCFB01225AULL, 0x300779D55E92D549ULL, 0x87563F1797AA6A0AULL
        }
    },
    {
        {
            0x1D494DECA21E46FFULL, 0xB2DE2E45027EF689ULL, 0xA17ABEDE0E1E7497ULL, 0x91CB65160760DA28ULL, 
            0x911C67E5B3F93EF1ULL, 0x62FACCE5285E4308ULL, 0x278ACD0234350429ULL, 0x87EC5A69292A43EEULL, 
            0x0BA45A80F1BEBCB7ULL, 0x6532568755B743D8ULL, 0xF48D1DE96F311FE7ULL, 0x0AFE0FBF26C42326ULL, 
            0x071CE03A16E90997ULL, 0xC88DEE3D52ED516EULL, 0xD5F7B4A85FA67D15ULL, 0xE7E71297913BB3F7ULL, 
            0xABE5B2AF3B0DAF78ULL, 0xDBD8B6ED6B83A352ULL, 0x3191B6DBBC707180ULL, 0xD41561C926353E8FULL, 
            0x2E48A49746F546E9ULL, 0x83F8DEF26560B473ULL, 0xF718CB21B012713BULL, 0x646A814C996A3F0DULL, 
            0xA41247E8619C8058ULL, 0x02F563B3E04E2BDDULL, 0x1A9FF0E043188E1BULL, 0x1EBF859E826E09FCULL, 
            0x1177CAEDC786ED00ULL, 0xE96BCD9DC8105686ULL, 0x81E5E6BE49B1AD9FULL, 0xC7E8F152FBB57E66ULL
        },
        {
            0x4C5DB7E6B25751B0ULL, 0x439C58DA39B0D54BULL, 0x4A00CDD3332ACC67ULL, 0x446E373933E9A798ULL, 
            0xA57E5D53D23E00A0ULL, 0xFF6EA1C85D1F4947ULL, 0xEC49AB49DF0F3231ULL, 0x599063FD4B7394B4ULL, 
            0x37A12DA6C4BE0402ULL, 0x1E40A3AB0CDABAD8ULL, 0xC6CFB0B56200F945ULL, 0x050A998252F53C1EULL, 
            0x998BE6C7D885602BULL, 0x1B70738CF4D3D1CCULL, 0xAFB3DA5850A4AADBULL, 0xAD2F88E7E1E88BBFULL, 
            0xE52BBE1111B8A63EULL, 0xF549CCCAFD784099ULL, 0x45AC3FD8FC4F9705ULL, 0x0587296EBE0E908DULL, 
            0xB54F155CC09B1569ULL, 0x79420A1FCC8D79D5ULL, 0xB1D76AD71E78CAB2ULL, 0xE721BDFBA552730CULL, 
            0x36208551C4F5BFEFULL, 0xC63E3556C247E964ULL, 0xFCF4956E8FCC0307ULL, 0x425EE83791C294E8ULL, 
            0x4D084227A6AC41FFULL, 0xC045CB620D91DA53ULL, 0x7E08076D0E2D6C29ULL, 0x19312077E2618680ULL
        },
        {
            0x5F7B26F58DF6BE08ULL, 0xBDCD74277935CEFFULL, 0xD421819D80C93C02ULL, 0x08BD9525717EAA37ULL, 
            0x82C590F88EF6CB9DULL, 0x1BFCA8E2D9999C7DULL, 0x6850C8C500B5E4EDULL, 0xE106D3CD08089910ULL, 
            0x201AD3841FBAAB95ULL, 0xDF3CF9C7826211BDULL, 0xEE7637E997CDB332ULL, 0xA020FA093CE68F66ULL, 
            0xF0F567938F5D85BEULL, 0x1F61603D86E67D72ULL, 0x1CE4C4A4C8E5869EULL, 0x818A81E34A9DFD06ULL, 
            0xE6E1DD365CC9FD31ULL, 0x02CE958D30E56627ULL, 0x26016214DF0C109DULL, 0x47E5973410223DDDULL, 
            0xA2CA0678ACA52B6DULL, 0xAF6D2CF03CCDEA8FULL, 0x574B79C7ABB2D9BFULL, 0x89A7A2994674E55EULL, 
            0x3606B4A6E84A5770ULL, 0x8A4626AEC652627DULL, 0xD08FD549EA35FF0CULL, 0x215C5E520F9D6EE9ULL, 
            0x32B098E2D0FB7A24ULL, 0x4CD6CDB857183AA8ULL, 0x5215E13C02403168ULL, 0x03F237DC6492439DULL
        },
        {
            0x9F3F9FC765C96683ULL, 0x78392CA59367629CULL, 0xAE84C75833942E0AULL, 0x9E3DF1EB82559450ULL, 
            0xA6F8CCF20D5D31F0ULL, 0x3842CC4B532CCC6BULL, 0xB23003AB7D8A8B74ULL, 0xFE99CBAF65A61160ULL, 
            0x71CF1EBAEEA4B17FULL, 0xAE7F0F185601882BULL, 0x52CCC404A07E3ED2ULL, 0xA9676358DE48AB20ULL, 
            0x6381955A8C725605ULL, 0x07934BF0F00ECE25ULL, 0xBBF0C217AE593702ULL, 0xCB0D52700FAA126CULL, 
            0x4FBAB997F0AD49A4ULL, 0x974174BB1D1D4CB4ULL, 0xC5420E09D6315646ULL, 0x2DEFFC8BA27D6468ULL, 
            0xB6E52D9ACC88DFF8ULL, 0x596EEF39EB55EDC5ULL, 0xF637AF3A3C645A96ULL, 0x2F020965BF971745ULL, 
            0xC31529C5ABDEAC66ULL, 0x3A7D812CEF356C30ULL, 0x4093BCBC387A55B2ULL, 0xE467728E3DEF6C73ULL, 
            0xC561C6190FB48B96ULL, 0xF970B5F142A00747ULL, 0x3EEA92F281FD4ABAULL, 0xF5C181CAA2D09018ULL
        },
        {
            0x00B9E6749736B0C4ULL, 0x923C05287241969FULL, 0x1D2C5ECDB024D190ULL, 0xCEA60D33A4735E6EULL, 
            0x6980F499D0D8CD30ULL, 0x4173BDA295257BECULL, 0xE96AC1B13E86C8C5ULL, 0xF65C94CE9AA9A329ULL, 
            0x8B3C8A2660CA2FF2ULL, 0xBD3ABB0D4529D68EULL, 0x499808F41419365BULL, 0xE99BF5268BCEFA8FULL, 
            0x96F90FE9FF82792AULL, 0x8C769890AAE69DDFULL, 0x5B2AF0515137DE47ULL, 0xD8EF8B61CA4386C6ULL, 
            0xEF7358B8F702D47EULL, 0x9CC19E6A2D651870ULL, 0xE43AE2E609A773DFULL, 0xE7724B9676037AF0ULL, 
            0xE36A0CAB4C0661FAULL, 0x456BD18EF7F87998ULL, 0xEF32B8DCF5B55D75ULL, 0x44A242543B8DB4AFULL, 
            0xF4BE9993B24DF8EBULL, 0x2D8A799FEA0DEC39ULL, 0xDE37B978D0EB6A39ULL, 0x10BB2FAE17531A87ULL, 
            0x40283B515ABEB9B9ULL, 0x2EEDC1A756BEA70CULL, 0x1A3AD38D1779B08CULL, 0xE8048A2587440413ULL
        },
        {
            0x6331F0AE3FE5C62CULL, 0x672672AFEC8BA42AULL, 0xF1D7007163E57C7DULL, 0x8BFF05524DDAAE63ULL, 
            0x0EBF01E2D62A39BCULL, 0xDEE39BCB494F9336ULL, 0xE4A2928A0C7BC1D5ULL, 0x416B8922B60BBFD4ULL, 
            0xC1955D4C413ED231ULL, 0xABED9A0B5A7EDB90ULL, 0x940A545E7AB1FBE4ULL, 0x1658481576E11026ULL, 
            0x79D1090D47E363F3ULL, 0xE378C7730F6E2E61ULL, 0xA1A0685566744006ULL, 0xA7ACB4839823E9D0ULL, 
            0x10799F493EDAEF01ULL, 0xC32FD9A721422F0CULL, 0x63F5BB409EA1BEAFULL, 0xE3748C97D99C2277ULL, 
            0x96F7592F1ED352E4ULL, 0x71B312C4E2F3CE8CULL, 0x577CE8BAD92A326EULL, 0x9E1E10663F5FFF87ULL, 
            0x2CFEA4E5B73EA6AAULL, 0xEE162869FC526073ULL, 0x97467D27B5B36E2DULL, 0x61BECC3A6B7D532EULL, 
            0xEB736CA51D105115ULL, 0x4D2F52E0763C5F5DULL, 0xD89F26149D71E77AULL, 0xE41A136E79208B3BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseGConstants = {
    0x594706A0B148F648ULL,
    0xA996CEB26ACDB2F1ULL,
    0x142EFBFB084ACB81ULL,
    0x594706A0B148F648ULL,
    0xA996CEB26ACDB2F1ULL,
    0x142EFBFB084ACB81ULL,
    0xD5724B3589DB6094ULL,
    0xAF0510FA464A9F41ULL,
    0xD3,
    0x8A,
    0xFB,
    0x04,
    0x31,
    0x4A,
    0xAD,
    0xFD
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseHSalts = {
    {
        {
            0xC086F05081E355CEULL, 0xFC40465F34939B42ULL, 0x209E558B0FAF1B7CULL, 0x45F458BA1B552E95ULL, 
            0xC012DFDD50C137E9ULL, 0x88322F329B71A699ULL, 0x36F726061A716D61ULL, 0x5855D85BDBCE2443ULL, 
            0x73D1BA004E766B7DULL, 0x0F9231C7F6A523CFULL, 0x51D41B070018FBABULL, 0x3134BF7B00EEBD14ULL, 
            0x436114F59923D203ULL, 0x723176C31BC5B794ULL, 0x5016DB120716BE31ULL, 0xEBACB77E9C7E91C2ULL, 
            0x8EC8C09DB1E78B36ULL, 0x1D5BBB2704A14C42ULL, 0xA320F6787A4DAD34ULL, 0x6A59716964FED8B1ULL, 
            0xF3748AAC8A57671FULL, 0x097A5D90D1C04DE7ULL, 0xE44A26148D71F8B7ULL, 0x59F208A914BA951BULL, 
            0x4DFD95A6C85280E7ULL, 0xFFC2640850A1BF92ULL, 0x7E97C0A717A8C030ULL, 0xF0E69880612C2DC8ULL, 
            0x0CB4832D5E7EB361ULL, 0x4D30BB9C69681F8BULL, 0xAF6AB8BD00C69F9FULL, 0x75D1C69324A6A04BULL
        },
        {
            0x9C20CBE8830CB119ULL, 0xA4EED1A639633483ULL, 0x6E1D74E7E47B8252ULL, 0x97A47007097D7AD0ULL, 
            0xC3F43C297450F4B9ULL, 0xCC2B572D50727A3CULL, 0x4213E12F8C4D97DEULL, 0x7D764CEA0FF266D9ULL, 
            0xCF24D428328AE686ULL, 0x06019813B68461B8ULL, 0x51B13A5827E2AD46ULL, 0x2749C4625A05259CULL, 
            0x7FD5B836185E7002ULL, 0x927DE2D18CD6D44FULL, 0x43D4E5D3AF1059D0ULL, 0x64DE1C2CC985D57CULL, 
            0xF44B29295BB1CFFCULL, 0xCD35335CE698F5FFULL, 0x6696F95D5D4DF9FFULL, 0x0CECA4D0EA082380ULL, 
            0x8BC315CBAFA30886ULL, 0x47F4CA95A4FD59A2ULL, 0xCF418B66BBD1711CULL, 0xD2212E84E2A5476CULL, 
            0x7EDFEDAED097B9DBULL, 0xCCF7DB7C1424C34EULL, 0x84A423A7D7AA8806ULL, 0x8141D1E180791B98ULL, 
            0x98C3653AFF8EBFB0ULL, 0x610AD60583E00F59ULL, 0x5C718204BD847473ULL, 0x9EDBBC663FC9427CULL
        },
        {
            0xAEAA308109A1D9D5ULL, 0x690F974A90FADB8FULL, 0x7747FCCF6B460ED2ULL, 0xCA943DE1F27B2CB3ULL, 
            0x4968E61DD2E6A6A3ULL, 0x46B8645483EC2198ULL, 0xC8754E2343B8CA5FULL, 0x0EF6F348F08D559CULL, 
            0x4741214F6943A99FULL, 0x31E94C6E2E10F57EULL, 0x76DF6C965E22B853ULL, 0x2240E67938498527ULL, 
            0x66266ADA16C049F1ULL, 0x792E73986FBDA8CEULL, 0x64C2CF403EF7441FULL, 0x6945DD5B980BBC5CULL, 
            0x356C4312065F9B25ULL, 0xED4D58AF77C7421EULL, 0xCED49ACB0A3AAAECULL, 0x528359814C75FB76ULL, 
            0x9DC43D59279B8DFDULL, 0x129A3B996F7DD98EULL, 0x619420E30DF8A6EFULL, 0x6472F2766308F3B9ULL, 
            0x0B01114929F27726ULL, 0x0141AA991B10A91CULL, 0xA9F85BA40F4DF3F0ULL, 0xB905167F11505C0FULL, 
            0xB8DE95005F97E1B0ULL, 0xEA1740B052D5FA75ULL, 0x0DA4903C85174F9DULL, 0x8359E1EAE4FE08D5ULL
        },
        {
            0x496E7402F913FAB6ULL, 0xD4D64039FD487ABEULL, 0x01374A63717EAE5BULL, 0x06561EE82AF07ECDULL, 
            0xBD648A33A42AACC8ULL, 0x3CCB7CB35251D6C9ULL, 0xE116A6EABB117732ULL, 0x594203388732D896ULL, 
            0x920ECE2FECAAAEA9ULL, 0x4591407CE66523CDULL, 0x97AC7C9FD8128DCEULL, 0x85AD57B0DBBB436CULL, 
            0x5F51B918707A6366ULL, 0x4E629DD798CAAD43ULL, 0xDA50E4A940A3B4BCULL, 0x90999A371BBDBCD1ULL, 
            0x30A479A50F5AC566ULL, 0xF3BEB233A1CABDEFULL, 0xCCB9355FF2D18EA5ULL, 0xC7FBCA111501BD94ULL, 
            0xACDFF80B9F8EB58AULL, 0x9A9A1EE74CFBD8CBULL, 0x17BCF02123737E98ULL, 0x37F8509DA73AE080ULL, 
            0x5F3A4D2BF9AEBF7AULL, 0xF0FA361794AB3F45ULL, 0x1EE1CA28E33CF5CBULL, 0x7FF86333616A9EEEULL, 
            0x7A96083BC5665E34ULL, 0xA2FA6C8C113F662FULL, 0xDAE29703548A8EBCULL, 0x13997A796D68CD2CULL
        },
        {
            0x2355EFEEEFF8FEABULL, 0x9E3B906480427717ULL, 0x7ADA914F5B629F45ULL, 0xC742C73B93E9BCAEULL, 
            0x6131A3E7775424FDULL, 0xCE65AD0E5AB1C275ULL, 0x808428676E4AD3BFULL, 0x5A76CE28834DC93EULL, 
            0xD8351833CB2C339FULL, 0x872C7A534AF355DDULL, 0x9D4893F9786A6D8BULL, 0x9E8474ACB244EF55ULL, 
            0xB690853886E95722ULL, 0xD2C567771C79D3B9ULL, 0x44E7D5B0C1F841D8ULL, 0xFD963A67373D4DB6ULL, 
            0xE4228D9BC708A8A8ULL, 0xD6101D37962B0504ULL, 0x75540DC41C34A9F6ULL, 0x72B1E0F4B006BBECULL, 
            0xBD09D05F64DBC8B4ULL, 0x1053B069D80C4433ULL, 0xBCEB49574F1A0C4CULL, 0x6109E6AE61247A5EULL, 
            0x13C1ED2C40813516ULL, 0x4D7DF6B1947AEBF2ULL, 0xDBB6DC5E37C158E5ULL, 0x167F7221B33BD7E8ULL, 
            0x616B5F3C1D7FA7C9ULL, 0xDA16879F21EEC638ULL, 0x85CA2CA0B230E657ULL, 0xD865ACFDCA2D0AD0ULL
        },
        {
            0xA981F101E771BF78ULL, 0x81575D5BC11407AAULL, 0x95266D53FEF31E69ULL, 0xE1A019A3BCFEDF65ULL, 
            0xFD7514F608A678C1ULL, 0xB37771E85F7C886DULL, 0x9A6323E229121310ULL, 0xED0EE6C5736EC6BEULL, 
            0x882ED6238C1D53E4ULL, 0x82FA36F895171598ULL, 0xA1F4D55188CCBA5EULL, 0xC21A308586F6FD5AULL, 
            0x69942E17B5074F57ULL, 0x6FE2A2CF2BDE2C12ULL, 0x1E41CED90D791198ULL, 0x7A61249D5DB4F382ULL, 
            0x1ABF502D383A6E1DULL, 0x3E7599825179E7A4ULL, 0xE5472158612B80C4ULL, 0x384E4D2A59632102ULL, 
            0xC397D43DEB28C65CULL, 0xFCE88FEDB7E73AADULL, 0x1CEFB9A82D8D9EB9ULL, 0x12D5C3C6E07C95F8ULL, 
            0x9CDCBADBAA7CE731ULL, 0xDE51123A31687E03ULL, 0x66EDA683E764B74BULL, 0xCDE4A8B04AEBF016ULL, 
            0xFE19DCE49A4A1CB2ULL, 0x81388CB6871EBE93ULL, 0x6C4755AE81625928ULL, 0x0A19A96ABD40C406ULL
        }
    },
    {
        {
            0xE6748D67C5BC6462ULL, 0x7311DA7594B389C9ULL, 0x9E8BD07ECEBF6F9EULL, 0xDBBC110E2FC1DB9DULL, 
            0x61BF866E34413723ULL, 0x033DAD695C53FC6AULL, 0x368942E5321D3574ULL, 0x8A328AFD4D4D1CC0ULL, 
            0x8DBAE6FC9DD8235FULL, 0x7E8F2EDB3208F35EULL, 0x0818D36830DB1A1BULL, 0xC3CDCE17BA3DE25DULL, 
            0xC77D0D9B98A08947ULL, 0x28A8E2D2B46B360EULL, 0xF6546470B27B532EULL, 0xD62B678CADFCE4B3ULL, 
            0x1D4897C4BABDB386ULL, 0x8BAA8208AE7A92D0ULL, 0x72836A94F92C09F3ULL, 0xCF1B6F94FE20C0CEULL, 
            0xE4A2977682A136AAULL, 0xF07026DDAFDB4A01ULL, 0x259924B208A90B7DULL, 0xAACBCEC474E82E86ULL, 
            0x6FBA04FDD0FCCBF9ULL, 0x7A800D20044C2447ULL, 0x599A305A8743A826ULL, 0x21B2C6E40B5A2DF8ULL, 
            0x0A9B494C5A2FA89DULL, 0xFD2CDBE7980B4FF3ULL, 0x030139F108428034ULL, 0x1C48D8BBA3BF66B9ULL
        },
        {
            0xABE9B2FE65EF761FULL, 0xC009BE32FA55EF2AULL, 0x99688E707BD82400ULL, 0xFF7AAD77EE55DF43ULL, 
            0xBB00879239D7185DULL, 0xC6A8A1B34B1BEB9DULL, 0x9D070FB4F88BFB2EULL, 0xC09A40A7E844573DULL, 
            0xF13CC8EC4D879928ULL, 0x3B97A6AC942BC816ULL, 0xF64A81F9E46AA304ULL, 0xC064C9C7FB223FB7ULL, 
            0x27D267968951B9E0ULL, 0xE590F63300F566B9ULL, 0x9ACD937D41862FB1ULL, 0x8CDE377D908A8655ULL, 
            0x4280F17DC00BB873ULL, 0xB0C0695D0843EFBBULL, 0xA45E58259457840CULL, 0x3B87BA5838924255ULL, 
            0x7F2032ADBEE3140FULL, 0x90205A5C4E90DB4CULL, 0x2E9F62FAC3A2E6EFULL, 0x5515E8C065B62BAFULL, 
            0x357D1DE2D49837C7ULL, 0x085A80440525A28CULL, 0x101B73C73C662DB2ULL, 0x422E994C40BEA6C9ULL, 
            0x80B5A3F60F86B04BULL, 0x7989457AD51EDAECULL, 0x4256BBF5EB163427ULL, 0x55CB0DB003995EDAULL
        },
        {
            0x02597795FB18B9C8ULL, 0x8FDA07AD68AFDE51ULL, 0xF723892EE8EE4155ULL, 0x80CB05AE4EB58C3FULL, 
            0x2E0423FECF79A14FULL, 0x9B5F85A24AD53032ULL, 0x786C050877B060B8ULL, 0x3A202475F51D7C4FULL, 
            0x28928E9D21CBF75FULL, 0xD3042081A70BEE53ULL, 0x56AC5E8B77511B61ULL, 0xDC201F0857496E6DULL, 
            0x6D7D2E4742DBC52CULL, 0xD369E57738050B4AULL, 0x72E0AA90D37DDB62ULL, 0xBF364F1FEAF06935ULL, 
            0x66B8212E38480D66ULL, 0xB7C5BFE0CFFC46B9ULL, 0x3B075F8657D4A0F4ULL, 0x1D0516152E94CAB3ULL, 
            0xF5CD7955A1BDBFCBULL, 0xD8C5FDF06D042163ULL, 0xCAF04C38B8E2DF6CULL, 0xFA2832DB7D54204AULL, 
            0x7E40D7457B7DBA5CULL, 0x1CC4FBD7A8909699ULL, 0x11A817C77D0C54C0ULL, 0x5332A844193EB80DULL, 
            0xDA49078C55449535ULL, 0x8CA82A8D4DB65ED5ULL, 0x2E799322B018F164ULL, 0x3514FE3CA7EAC0E7ULL
        },
        {
            0x20CAA3CFFFD6D8FFULL, 0x6896387786F2E0D2ULL, 0xB27BCA3B94E6E1B4ULL, 0x18D8E9E2E412DAE2ULL, 
            0xD329B81940F6C286ULL, 0xEE8AB7BA4B3B233BULL, 0xC362751F350FA4FCULL, 0x57DDC78F992742B3ULL, 
            0x20443348324F8AB7ULL, 0xC8656AE78CC0A435ULL, 0x443C1E5BC10198FAULL, 0x2140ED3CA1A28D9EULL, 
            0x938FEDD1AFE28A77ULL, 0x9B1C269366D97AECULL, 0x3856C23247DE8CB1ULL, 0x988120D81EA63E01ULL, 
            0xE3507320488BDB0DULL, 0x57FBEFA88F683169ULL, 0x538B72A272E19E26ULL, 0xA313443E61F52F79ULL, 
            0xFFF90B6F7AAAA487ULL, 0xE8950BEE2147BBEFULL, 0xD9A2E5817E7B70D9ULL, 0x961156C74B3936C9ULL, 
            0x935D0042E73B6E16ULL, 0x2F73EB753DC0EA83ULL, 0xDA85CFEABB30E6E1ULL, 0xAA7324DFD92B9EACULL, 
            0x2D68CCFA96DD6347ULL, 0x150585E86F93DD11ULL, 0x235CA2698F0A0487ULL, 0x92CA7AB9B6798838ULL
        },
        {
            0x808AD1F9127B3E02ULL, 0x41F47D3DFE77D975ULL, 0xFCD20C472C4BBB00ULL, 0xD940DA834E2A3253ULL, 
            0x89896B2034BB1204ULL, 0x35BC466F437FC320ULL, 0xFC612A3B0160CEBDULL, 0x00C5B2DEA534B52BULL, 
            0x325C43B06BACF52DULL, 0x5DA6926B8B54BB7BULL, 0xF78886CEAB298074ULL, 0xCD3DF4B5F48E19E1ULL, 
            0x702ADEC2B3B93315ULL, 0xC86FE9B9EC68569BULL, 0x6D457899B7EC8944ULL, 0x01E0FD8268CD37E0ULL, 
            0x095FAD1D97D0AD31ULL, 0xE01A6AA845DF37A6ULL, 0x08203E6E24719098ULL, 0x0944ABB727066A8DULL, 
            0xF23E1A425EE0A2F6ULL, 0x0D267C6DE77008FFULL, 0x2F751E631A0D80C7ULL, 0xFCBE61D4A3901316ULL, 
            0xE618080F4236D2EDULL, 0x22013B27D7D259C2ULL, 0x4FF162E08AFAC142ULL, 0x7F237879CBFC9AFAULL, 
            0xBA9FE3A0D38ED9E7ULL, 0x83EAC520B407038CULL, 0x43970EFB79917F9DULL, 0xA3D3A6A3C5338C14ULL
        },
        {
            0x051E511CF019321FULL, 0x4639067CE6B15A0FULL, 0x339FAC2C1DB9C053ULL, 0x43ABC7A46EE921FEULL, 
            0xA812CB573C2F1574ULL, 0x23E97BBD3A05CBA9ULL, 0x7250CE21C44138EAULL, 0x4AB1C2F5E6C819AFULL, 
            0x5C5153234130EC6FULL, 0x98C46D05D2035F1CULL, 0x0A8E0FBED6D9758AULL, 0x4AE13821D55E6597ULL, 
            0x81367055618B3F38ULL, 0x820D2C83307D7F49ULL, 0x529E4882244996E5ULL, 0x2F9D58C5B1715549ULL, 
            0x363818776FC6B496ULL, 0xB172596F3C7A1D49ULL, 0x5D11B179C1C43E6EULL, 0x80A47A1BDF9C21ABULL, 
            0xC59DFA6A3538AF9EULL, 0xBA76E309F551D836ULL, 0xD96492D8EE178F50ULL, 0xDE94BD66BF7FC53AULL, 
            0x0F0CBD7C3D55E527ULL, 0xC1DC5CA6E362DFC4ULL, 0x6CBD5A4D720EA9D2ULL, 0xADA144E3DFA3AD7CULL, 
            0x5B3FCA7BB59869F4ULL, 0xFC1B0475422DDF8EULL, 0x1A9A3DC6C18E55EBULL, 0x0335C55721F90151ULL
        }
    },
    {
        {
            0x46F546CD22C5401EULL, 0x9A8E86064A3B3E9AULL, 0xBF74E8C917DCBC5AULL, 0xC4D01A4D486DC93CULL, 
            0xF882587AA29740F2ULL, 0x9D67754561A6009DULL, 0x3FBFC9105A04005BULL, 0x56EED52892C15B0BULL, 
            0x707F467B86C36476ULL, 0x3E55B9FF257916FAULL, 0x64BDE9B6D8F1746EULL, 0xB34A9F7F587C04B8ULL, 
            0x03C64779FAF961A4ULL, 0x70222F186AFAF976ULL, 0x692A98F2AB1E3969ULL, 0xC9B1DA63EC7F2BABULL, 
            0xF1746075F01F7E43ULL, 0x6E78DD32979257A6ULL, 0xAD684DAF559C1C83ULL, 0xD236742076062556ULL, 
            0x22645ED4C2CD94DEULL, 0xE9039F107D489D9AULL, 0xECA75C3CB11F5ABBULL, 0x419B407AF0CDBF58ULL, 
            0x3E047F8C25A5839BULL, 0x14AD1A0428009A00ULL, 0x32723DF66D6285B6ULL, 0xD5DE9DDB4C16A3EEULL, 
            0x4F242AB746BF0A21ULL, 0x05B1BBA58035945EULL, 0x55A99DC4F5ECC753ULL, 0x858DCE055756D7C6ULL
        },
        {
            0x676512F60983706FULL, 0x45C262131148B967ULL, 0x31048BEF37D47397ULL, 0x5707B661ED36156AULL, 
            0x812CF60EA5312CCDULL, 0x5247216FB1250575ULL, 0x4B4F3382A5A99482ULL, 0xA2E584CA36F0F5A4ULL, 
            0xC0EF5B9923D9AE5BULL, 0xB9FDFD1B52AF0477ULL, 0xA769076A9122508BULL, 0x1CFA467D4FC808B9ULL, 
            0x5ABEF3CE94525D3BULL, 0x2182198C5565F9DEULL, 0xFAB81383604B8D37ULL, 0x6CE0104BFC9AE1E4ULL, 
            0xE5F1A9E393918F2EULL, 0xD826F1459D062EF8ULL, 0x9CFB6813CCEA2E93ULL, 0x810E5F12FB0AC2AEULL, 
            0x62C089795258D176ULL, 0x33E30522605387FDULL, 0x093BF9ED77F8B5C6ULL, 0xAF36935A7C7E1809ULL, 
            0x48C4E9D0A530B633ULL, 0xDC8843A33253428DULL, 0x0FD8EA9D8B7A9175ULL, 0xFFB473F8092F2BE2ULL, 
            0xCF70CDFB64A51372ULL, 0xE596A9B9DA93A616ULL, 0xCD90FBEB6F5C7DADULL, 0x472F5A41D7DBEF93ULL
        },
        {
            0x6A1913C47822E741ULL, 0x27C29C1EB1FB52C9ULL, 0x1EB4949BAC2AC477ULL, 0x45401DAC99483781ULL, 
            0xD316AACDECCA2297ULL, 0x2AE04D8DD05F95E6ULL, 0xEE262312F131E6DDULL, 0xE517042D4AE36C7EULL, 
            0x0A06DFF143628F52ULL, 0xB30E8314C1B680DBULL, 0x6D230FDD4C853944ULL, 0xCF824967C8121644ULL, 
            0x9BFAFC2AE8483EB5ULL, 0x95C079C9A9FF71C2ULL, 0xD136A1C36E7C383AULL, 0x62056305D4DF1DC7ULL, 
            0x3798840584BC532AULL, 0xAEF937D30B365F71ULL, 0x81C441F9FDB7EFF1ULL, 0x6FF8C7D4D446EC91ULL, 
            0x8CBB687CE8DDBDDFULL, 0x8930D1954E67FCB0ULL, 0x0ED4A2CF426DBD4AULL, 0x6D5B5F3502CB47CAULL, 
            0x89BF664FB1867A04ULL, 0xBEC5DDDF1A4F1581ULL, 0xF287FF98C27911E2ULL, 0x13D20C63B7845821ULL, 
            0x6457FD21AE51F7B7ULL, 0x6011BB1DC1230BC9ULL, 0xCFDA9F5525039E27ULL, 0x5BAC2C6851ADBD12ULL
        },
        {
            0x02BDE4FDDAE5851AULL, 0xCDB0A1C19E4D3E55ULL, 0xBF9FB8D112BB5161ULL, 0x1AD0D586E4575086ULL, 
            0x0543E4219609FB9DULL, 0xA5FFC98BA4A6A9F4ULL, 0xAAFAD2FA8AAE21A1ULL, 0x4C54F82B045F7101ULL, 
            0x748F5C72D789DDBEULL, 0x74F647D5306E26A0ULL, 0x324B1776793F7580ULL, 0x3A8E5D618DBFB26CULL, 
            0x594459E793381F2EULL, 0x3980807598000398ULL, 0x7DED87FE428DD9C1ULL, 0xF5496A9EA1A310AFULL, 
            0x84F0889AAF28A227ULL, 0xC70CB4BA2EA2CEB0ULL, 0x7B0988C5D038DF9FULL, 0x7F69B61048B7E489ULL, 
            0x0196BCE5815847A3ULL, 0x4F348AD6F6EC0103ULL, 0x7392F94252E70875ULL, 0xBD39B63F686BE6EDULL, 
            0x23AEAEC63971F97BULL, 0xE5E502B65F693285ULL, 0x9F0ED4F6AB8BF63DULL, 0x4DF9CEF3760F87AEULL, 
            0xAD608FF06ADC32DBULL, 0xFE570E7752CAC6EEULL, 0xDE5E41A04CE08ED9ULL, 0xADEC5E84FAE5B2F2ULL
        },
        {
            0xAAE2778A15D56187ULL, 0xCEBE237E2D6EC3DAULL, 0xAD43B322C1EA4517ULL, 0x00BEA735CC991CD4ULL, 
            0x3502AC181C16A27CULL, 0x39182BB380324B0FULL, 0x10E0B551F025147AULL, 0xD49C18CF754E3AFCULL, 
            0xB9936E71C03FC7F6ULL, 0x73833AD6E8C97F70ULL, 0x3C93A52CD329EF70ULL, 0xBFF55B347674BA61ULL, 
            0xB2162ADEA0EA2C73ULL, 0x4E5856459B81DDA9ULL, 0xA5297BF05BCC48C6ULL, 0x3BE7939F04183157ULL, 
            0x7C512963256E8D9EULL, 0xDF1A87E2121A4DC8ULL, 0x3B1847EFA073EEBAULL, 0xE044C3BAED072721ULL, 
            0x29D5DF5CFEFFD6C8ULL, 0xEF097417CC9B6F09ULL, 0xE2CE7D9607B77A9FULL, 0xD61D5C08D067DE17ULL, 
            0x072020471FAFD66FULL, 0xAA5A92E68530C102ULL, 0x17F9687D3BE5110FULL, 0x0EE1903BEAD96F20ULL, 
            0xFB4C175D7BB2435DULL, 0xD5695C056DEEBBABULL, 0x10059F8FDB5EEB92ULL, 0x1A06D65C6C3F9DE5ULL
        },
        {
            0xCC752BAD25A50781ULL, 0xD84344E51D242A46ULL, 0x6B1FE9C8934D2A8DULL, 0xEA3B0BDE8E0F66FDULL, 
            0x2AEFC11AC343D9D3ULL, 0x014EA5DAD728B13BULL, 0x9DEC14675148F1F7ULL, 0xF93DB89E0E61887EULL, 
            0xF3EC2A416BADDC4AULL, 0x89A64B619BD10689ULL, 0x4936261094523B29ULL, 0x606467CC43C76CC7ULL, 
            0xB52B35D2A4E59FCFULL, 0xCD546008B764D6EAULL, 0x96CA5DAAA2F3F5CFULL, 0xCAACC242CA59E769ULL, 
            0x3B12570890006EDCULL, 0x2F40C0DF7B092023ULL, 0x4881AECF3C26105FULL, 0x1663E55F35CA845EULL, 
            0x3528D9EC9868A853ULL, 0x44C9E6205BF01689ULL, 0xAF48F5E9042D9404ULL, 0x9FCC69C7FF977A7DULL, 
            0x84F6A57F080ECADBULL, 0xA5D3457BDC0F4853ULL, 0x1BA8BB3953A03B5AULL, 0xB8CC606FEE784A5BULL, 
            0x59F93F02AFB71323ULL, 0x8E13C436BECB64ACULL, 0x6F617B332D0A9774ULL, 0xB2EBFA97DE8539D6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseHConstants = {
    0x9ACC65BAE93F9874ULL,
    0xDFBEE737B2C625A5ULL,
    0x5ABDE9940BA55727ULL,
    0x9ACC65BAE93F9874ULL,
    0xDFBEE737B2C625A5ULL,
    0x5ABDE9940BA55727ULL,
    0xB998774147AFBEEBULL,
    0xA7E8005905FF5679ULL,
    0x98,
    0x07,
    0x5C,
    0xAC,
    0xF6,
    0x28,
    0xB5,
    0x21
};

