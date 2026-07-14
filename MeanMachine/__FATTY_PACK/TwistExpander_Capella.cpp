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
    std::uint64_t aPrevious = 0xEC9B6ECEA35C51B9ULL; std::uint64_t aIngress = 0xF99EA11328FD36ADULL; std::uint64_t aCarry = 0xA9A2C534A7BD9E97ULL;

    std::uint64_t aWandererA = 0xC4809B3D486FEE00ULL; std::uint64_t aWandererB = 0xA78F1511310237D5ULL; std::uint64_t aWandererC = 0xE1FAC2FE347EAE3DULL; std::uint64_t aWandererD = 0xCD4AE45D9C4A470EULL;
    std::uint64_t aWandererE = 0x81DC8C2727F6329AULL; std::uint64_t aWandererF = 0xF1EF4467BF6156AAULL; std::uint64_t aWandererG = 0xC5C731EEBB4F1245ULL; std::uint64_t aWandererH = 0x854E3F47CBC212E8ULL;
    std::uint64_t aWandererI = 0xC884F132ECEDC4CEULL; std::uint64_t aWandererJ = 0xD50D3F90961CC6ECULL; std::uint64_t aWandererK = 0xB80C6BB6448386D0ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9464300770037001953U;
        aCarry = 11155083795936685585U;
        aWandererA = 12760449829338236390U;
        aWandererB = 12535538288718772819U;
        aWandererC = 12030183985466862491U;
        aWandererD = 11723785732229887804U;
        aWandererE = 14568163348170534965U;
        aWandererF = 15852559050626712034U;
        aWandererG = 17293303486856312864U;
        aWandererH = 12359240085131459391U;
        aWandererI = 17275727448380665442U;
        aWandererJ = 16296646161788709737U;
        aWandererK = 9385971847389493644U;
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

    //
    // ---------------------------------------------------
    // KDF_A_B kdf_a_loop_b:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Capella_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_A_E(pWorkSpace,
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
    std::uint64_t aPrevious = 0xECA7B9D1669C4AA2ULL; std::uint64_t aIngress = 0xC109007CFC57B04FULL; std::uint64_t aCarry = 0xA6277B1A006329B0ULL;

    std::uint64_t aWandererA = 0x8D8CCA9E2C8DE520ULL; std::uint64_t aWandererB = 0xC2238236CA12C565ULL; std::uint64_t aWandererC = 0xFA3A8A7F6D3B3FB5ULL; std::uint64_t aWandererD = 0xCF5B961EA9685A7EULL;
    std::uint64_t aWandererE = 0xD6E3AE397D904BE3ULL; std::uint64_t aWandererF = 0x993E4C89BB731D71ULL; std::uint64_t aWandererG = 0xF7F4CB170CFDD310ULL; std::uint64_t aWandererH = 0x9715318C4C9C8623ULL;
    std::uint64_t aWandererI = 0xC129FBA90CBC851AULL; std::uint64_t aWandererJ = 0xE06C79B9822CE262ULL; std::uint64_t aWandererK = 0xD7A06B712B0B1D56ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9317195531416818505U;
        aCarry = 11005596730009536993U;
        aWandererA = 11965744085885402694U;
        aWandererB = 15170103428912756033U;
        aWandererC = 16295144125945552589U;
        aWandererD = 16136336776081841498U;
        aWandererE = 11760167035918954700U;
        aWandererF = 12264065741135075777U;
        aWandererG = 11002264828601772361U;
        aWandererH = 17540809975099759171U;
        aWandererI = 15726032209499965890U;
        aWandererJ = 18233345993576935244U;
        aWandererK = 16882322278824183912U;
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
    std::uint64_t aPrevious = 0xF8C2CC1448BED70EULL;
    std::uint64_t aIngress = 0x9964AF6B7C095178ULL;
    std::uint64_t aCarry = 0xD8F34CCD0EEA94B6ULL;

    std::uint64_t aWandererA = 0xE87B5947BA789377ULL;
    std::uint64_t aWandererB = 0xC8CE381E4EF51294ULL;
    std::uint64_t aWandererC = 0x8FC9963DD16041ACULL;
    std::uint64_t aWandererD = 0x88BD67C5F53F5761ULL;
    std::uint64_t aWandererE = 0xA25BFB05F8FD0335ULL;
    std::uint64_t aWandererF = 0xFE1B48F2EE76FAF6ULL;
    std::uint64_t aWandererG = 0xA9EF82F07452D308ULL;
    std::uint64_t aWandererH = 0xF6DC035B4E58CC31ULL;
    std::uint64_t aWandererI = 0xAB96F706CE7541D7ULL;
    std::uint64_t aWandererJ = 0x9604BAE1440C5DC4ULL;
    std::uint64_t aWandererK = 0xE62AEA9599181ECCULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_B seed_loop_a:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, earth_a, earth_b
    // ---------------------------------------------------
    //
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
    std::uint64_t aPrevious = 0xAE985C8E4C8B7A4DULL; std::uint64_t aIngress = 0xA8CE95AC145CEE6DULL; std::uint64_t aCarry = 0xC2613CC82CC019C8ULL;

    std::uint64_t aWandererA = 0xE677B60D9305CFAAULL; std::uint64_t aWandererB = 0xE04D84301B15B647ULL; std::uint64_t aWandererC = 0xD356263234A7A8B7ULL; std::uint64_t aWandererD = 0xFCB0551202C70980ULL;
    std::uint64_t aWandererE = 0xEA83CB3DBABFB48CULL; std::uint64_t aWandererF = 0xF5CCA759FBFD5067ULL; std::uint64_t aWandererG = 0x831FD284E0CDE297ULL; std::uint64_t aWandererH = 0xEF2E807B46A75071ULL;
    std::uint64_t aWandererI = 0xBBD52FB653132F5AULL; std::uint64_t aWandererJ = 0xEBCC7A6DA74E19DFULL; std::uint64_t aWandererK = 0xE61C2DAE4CF792BFULL;

    // [seed]
        aPrevious = 16252441534632406880U;
        aCarry = 17276989787762414923U;
        aWandererA = 13351946505588405158U;
        aWandererB = 9488246836459125836U;
        aWandererC = 11280227118082353404U;
        aWandererD = 15478209312358694733U;
        aWandererE = 13236150295683145405U;
        aWandererF = 10065762284367939351U;
        aWandererG = 10253603290470986309U;
        aWandererH = 13051528560825303940U;
        aWandererI = 14874188150013613289U;
        aWandererJ = 17915288609025840781U;
        aWandererK = 11182674678121056255U;
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

    //
        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
            0x22C8ED895AD47470ULL, 0x9BA32A6031CB1983ULL, 0xC07EA3291DAD44C1ULL, 0xDB15EB236DB71EE7ULL, 
            0xAF3A5910F41DB62DULL, 0xD7F01954A6B5BEE4ULL, 0x45EA3929EAF4D5FEULL, 0x4064530DBFFA1715ULL, 
            0xD70F661283E2B6A1ULL, 0x0945A50E76380A95ULL, 0xFF16D6DECBD4B44CULL, 0x2C0342DB89E19A22ULL, 
            0x7AFF8125C5829F33ULL, 0x7C7EA183220D5F76ULL, 0x4A448868F08F1A79ULL, 0xF4C6B418F1546222ULL, 
            0x9FA3BC261CB9B056ULL, 0x770C5CA78EC7905CULL, 0xF5F90CB3CFFF51B5ULL, 0x7AFEDF2F624136D9ULL, 
            0x47CFBD1C0689B49DULL, 0xF1C70EACF9418003ULL, 0xB2E99B7198E6478DULL, 0xB376B8E3A57A12F0ULL, 
            0x150D1A6E18F6F5D2ULL, 0xDECA32B3F06ACAF7ULL, 0xAFBD5E422C94168CULL, 0x4D17F10DD5505668ULL, 
            0x4B3D9B58BF389D3FULL, 0x20C74ACA960E5B7BULL, 0xE0A100E7277C7419ULL, 0x24B31399AC41559EULL
        },
        {
            0xEDC4DFA5D90CF673ULL, 0x45C44A2438A6CDE7ULL, 0xFA9578E5E04F521BULL, 0x60A2B78ACADFFE91ULL, 
            0xBCBB76D2F771E00AULL, 0x356C3DBCF9DFC700ULL, 0x5A4F17984F675116ULL, 0x12C2C502A9BF0DBFULL, 
            0x0F391D14134114B4ULL, 0xD019409883533FA0ULL, 0x7000ABE02ADD69C5ULL, 0x5700921625BDE88EULL, 
            0x0063805C688ED24AULL, 0x7832BC5B14E82E51ULL, 0x328A13DB2D788DA3ULL, 0x480BA91AE57457C9ULL, 
            0x5A1F82DC0328EF80ULL, 0xC75CAA4DCA9A5F0BULL, 0xC6256D1DE5AAE268ULL, 0x183C861664F9D1D1ULL, 
            0x1100B9CBA0B9013FULL, 0x2EEA99ED0B856E5DULL, 0x399476929E766BF6ULL, 0x8986E181B2451F0FULL, 
            0x564B3C893C0B6759ULL, 0x601FD6A81B469E02ULL, 0x28AD5E497A4A0A12ULL, 0xD5BFFE683B0D4E80ULL, 
            0xAB19C68030F27C2EULL, 0x29412BA1DCEA8FE4ULL, 0x2F7CE19327BBDDF8ULL, 0x29E73C9E86DFB93FULL
        },
        {
            0x5538DC4C2830621AULL, 0xF1D3CA1F7A08F688ULL, 0x04AED86E19464989ULL, 0x9A869D66C4B15922ULL, 
            0x32E21EB908AF3636ULL, 0x7E7719400C8AE69AULL, 0x21F0158243C72086ULL, 0x7A20DAEC5ADD990DULL, 
            0xF5549CEAF28DA015ULL, 0xCEE5C02B8B82E3B1ULL, 0x2DEEE6BCAABFC536ULL, 0x22A3F11CA027A125ULL, 
            0xA8F4DF4B7A815F64ULL, 0x3558D88575BFC5E2ULL, 0x923897B1663F3166ULL, 0x1C4932D18CDD88EBULL, 
            0xBBE1F1B1D2D512A3ULL, 0x23EF07A56CB28F66ULL, 0x6B97350865D616FFULL, 0x252D4D2106A75949ULL, 
            0x782E0B23D41B2D66ULL, 0x784D35A2E3DF1380ULL, 0x6916C15E00F0E05FULL, 0xB3156AC9A24F189EULL, 
            0xF39AA2E5C6B3F2C9ULL, 0xDDB002CE8EA5E0D7ULL, 0xAABEAEECAE7153BBULL, 0x68E1E9A7AB43CE2BULL, 
            0xBEBAF991985B0400ULL, 0x75674EF5E23DE697ULL, 0xC747EDFD6783136DULL, 0x6AFBB14FEB9F3F50ULL
        },
        {
            0x2FE581565E657D34ULL, 0xA9DC0D3028AF94B9ULL, 0x25D7106DC954AF91ULL, 0x70EAE29F059E3CDCULL, 
            0x2D7E7AF27AD5E3B7ULL, 0x79992467941A35BEULL, 0xDF57D8A2A5897395ULL, 0x2E7D7508DDD758A2ULL, 
            0x2B1C18CBF765B641ULL, 0xF37D8678C045C04BULL, 0x5C7DFB382F9139EAULL, 0xEDE5606BFD9C964FULL, 
            0x6291689E9A0975AAULL, 0xA535541B5BDFDAC1ULL, 0x6A24E65A5D7E2F99ULL, 0x7DBF34410C9FF657ULL, 
            0x9EA01EFF93D52A78ULL, 0x8F79333954E235F7ULL, 0x6F70B155D6CC9887ULL, 0xFF168D66DD516F7AULL, 
            0x4641CD51F27A1E71ULL, 0xB82BDAE3AAEC355DULL, 0x7943F7F82F3BA703ULL, 0x6BD37F9A5D663033ULL, 
            0x1AD9391BB8A46B4BULL, 0x60D587C327ED3CD4ULL, 0x9D73F05B92ED3340ULL, 0xBBC61C96A0936219ULL, 
            0x79C8A657B67A6EE3ULL, 0xD040FA2E01E7243EULL, 0x65A6B66FE69AB632ULL, 0xBFB1964E54D24830ULL
        },
        {
            0xF8156A2997FEB8F6ULL, 0x19FB659BE83565A2ULL, 0xECB576626E0A84B2ULL, 0xD56D5C19B102164EULL, 
            0x0C335F49ADFB0608ULL, 0xA0BA4B991D956DD0ULL, 0x552AF6D50DAD0853ULL, 0x8C10152EFEF64BFAULL, 
            0x0BFD912A0CCF302CULL, 0xDA5E4FAAC5BD57A9ULL, 0x4C3B2079F7E57D68ULL, 0x8752BC536888EC36ULL, 
            0xE848F2D0AF100158ULL, 0x425D0081568D5DFEULL, 0xC3FE9658D2E62820ULL, 0x577161F9FF18C17AULL, 
            0xD917618E193996AEULL, 0x5DA7369504EBB2C6ULL, 0xA3430CDF47D70994ULL, 0x24E0DD3E579A298CULL, 
            0x0C435A0D9D6075ACULL, 0x40A357F201752BB2ULL, 0x4F7A53749267313EULL, 0x0EC1B0B264993E1DULL, 
            0x056A9C41FE905297ULL, 0x9C5A5A08027688D9ULL, 0x564BC66F31DEDAFAULL, 0x5D4CD145930601DBULL, 
            0xB1838C60ACFED3A7ULL, 0x612BDF4540E0B32EULL, 0x8C8DBB5E194F8748ULL, 0x7E8A2499EE1FF064ULL
        },
        {
            0xB5DF975EF437BF5EULL, 0x4E34C9284C9180F2ULL, 0x779A79B9478E5EFCULL, 0x657AA3F0EBF1AA67ULL, 
            0x163BB38E309BB74BULL, 0x2B3E46FC0A3DD236ULL, 0xAA83D614BFF9A25BULL, 0xC595CE822AD85AE2ULL, 
            0x08DBA17127920029ULL, 0xAE7DC02F5BCB5182ULL, 0x175DB825ABF88FC4ULL, 0x9B7947E2CDD4A11DULL, 
            0x0ACACFFC8763B3E2ULL, 0x180E93C9D9ECEB03ULL, 0x04B73D34A38F8475ULL, 0x85B1E471F8E00B23ULL, 
            0x7F72A8E906FD72A0ULL, 0xDF9E828DB356DB4CULL, 0x3113235802DE31E1ULL, 0x0C54DF1FA20B447BULL, 
            0x972AE130F6FF3066ULL, 0xE3771F556E9AC0C0ULL, 0x4534E0D9E7D51B48ULL, 0x42097D3D809E4125ULL, 
            0x83F9BB4863F799FCULL, 0xD251F3A44660341AULL, 0x379B26AE665BC519ULL, 0xAE4C4FD68BAF2A42ULL, 
            0x31A6C200C7EFEC4BULL, 0xAFE96F05DA7525D5ULL, 0x32A9EACC0B24DDDAULL, 0xA30FB53F6D2B22FAULL
        }
    },
    {
        {
            0x28C80DF843626392ULL, 0xE97A2349D6539899ULL, 0x6337146C0D9EA8D1ULL, 0x3643563CE8EFDAC8ULL, 
            0x870A5EF5591E864FULL, 0x2A847B80E9E1D262ULL, 0xD97F0B79224800F2ULL, 0x61BC3FDC689DEB2CULL, 
            0xEC6B018D9D92AC37ULL, 0x462D7823F074FDE1ULL, 0x5F3D541028058C5EULL, 0x0CB903E2CCAC8779ULL, 
            0x7E585374A8E942A8ULL, 0x6F4482EE4E9FE203ULL, 0x7160581C9F8C9B28ULL, 0x852079D44E9573C2ULL, 
            0x82019D48F39C75F8ULL, 0x3451E8DC69B0836EULL, 0x29C197B784E8B9E0ULL, 0xD483655F73CEAF35ULL, 
            0x60226097B60808FAULL, 0x87C64850FF15103AULL, 0x05B2ABC8FF6A10C7ULL, 0x9181B89EF4F07154ULL, 
            0x6A0A4AFE27990006ULL, 0x8FA57DB132B34CEBULL, 0x781359DE45D03986ULL, 0x774D21546034363FULL, 
            0x37DC873E274FE4B9ULL, 0xB271EE94B18BD73BULL, 0x52F18888ADFBED36ULL, 0xABBADAE6F69D004DULL
        },
        {
            0xE658DD5D4291D982ULL, 0x333E39623B1130FEULL, 0x207FF53EF604A44BULL, 0x3D1ACB9290A25832ULL, 
            0x7C981193799EB69AULL, 0xF56BD018E6DC43D6ULL, 0xD27B92FC632EB270ULL, 0xEA40FCBB808A34D7ULL, 
            0x8578315ACA5F61CBULL, 0xA4F96F2C39C90E43ULL, 0x3738CA1A8989EDE7ULL, 0xD150F8C383B0BCB7ULL, 
            0x414C117F3D24C97AULL, 0xFEAAE8D40937ECB7ULL, 0x1AC5FAFF3E7DA357ULL, 0xB113696C70BD67DFULL, 
            0x84C150C792BFD25CULL, 0x4449C02BECA6F6FFULL, 0xD78CAF19B269F624ULL, 0x083073311E4A898EULL, 
            0xDDB3B00D5AE3CAC5ULL, 0xBA3C290C5AD99343ULL, 0xCD5053D12A77EDF6ULL, 0x8C416C136A112098ULL, 
            0xAAA6757C6B147B73ULL, 0x5F0E3EC52E23C0EAULL, 0x9F50E3895B9E82F6ULL, 0x837990ECFAE306D5ULL, 
            0xC1A1D1EAED907E0CULL, 0x9FA26E20971478E7ULL, 0x08EE68514B4B98CEULL, 0x2DD4F71F092A479DULL
        },
        {
            0x221A8CE1A3D00E8BULL, 0x8EA13C9079B07D59ULL, 0x8E5C9501F85957DFULL, 0x846A23454852BD07ULL, 
            0xA3281E8AD2A32319ULL, 0xFBD7F1B5F94D105FULL, 0x354863BE133AC322ULL, 0x6B0B7813E1F71D80ULL, 
            0xE71F6A5BEE02ACB7ULL, 0x3ECAEDC357CAFB53ULL, 0x596361AB227CD85BULL, 0x674A3E25376911CDULL, 
            0x101CBDD10CB70266ULL, 0xC66267C5F570B404ULL, 0xCB9B0FDDC9536D6FULL, 0xE3DB590828CB17D1ULL, 
            0xB5632556D1A98F0EULL, 0x7E64E38EDDEC57C5ULL, 0x7BD9E458B49D9846ULL, 0x4E96C81874BDB549ULL, 
            0x9347772060C6B5B9ULL, 0xA2A68700739BAC91ULL, 0x1DAC395365FE88CEULL, 0xA5AD8CA34551E3CBULL, 
            0xA92CD26012C57E15ULL, 0x991CD37D7E5FACF5ULL, 0xCA8F4DDA9A11CD4FULL, 0x9969D6C7B74843EEULL, 
            0x74204801D98B50CEULL, 0xB46570A7CB415BE6ULL, 0xCE78E6B4781ECDBBULL, 0x4C9A484885704999ULL
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
            0x40BDD54F9D01F578ULL, 0xD1F2FF5DB96E39D1ULL, 0x98F014EF56223090ULL, 0xCD2095A42968EA01ULL, 
            0x388584460CF1C45CULL, 0x58E69658373E8487ULL, 0x912EA8E952525442ULL, 0x042A6AD73B4C5A14ULL, 
            0x671BEC7F9A82F723ULL, 0x74445E8126EB09D0ULL, 0x226EE9B8154B492FULL, 0x89989286D4F22AF1ULL, 
            0x0CFE805D2CC7FF7FULL, 0xDB34BA81D362B380ULL, 0x00EF847C6FDDB51BULL, 0xBDB924BB4FA15B0EULL, 
            0xEE40299A63DAB6A1ULL, 0xCDA338C0E3007F6AULL, 0xC94130F83751FDBAULL, 0xBB177535079BB425ULL, 
            0xCFEE10292839690CULL, 0x52EAE4C7BF4DFE66ULL, 0x88A8C9D7310475BBULL, 0xF4C80BF288E28952ULL, 
            0x6BCD24336ACC4873ULL, 0x36B8632DBDEE1CB2ULL, 0x90CD76E2DD073FD0ULL, 0x7A2F9C41AA5C868AULL, 
            0x061F5054083DB706ULL, 0x54B6605F8BA1B4E3ULL, 0x669A7214E0B63658ULL, 0xF0106933C5FCD784ULL
        },
        {
            0x04FC3AA418E7A648ULL, 0x334877031567F291ULL, 0xE0AC49498B2C4F09ULL, 0x03A1D1E7800EBE36ULL, 
            0xD7363C21E8CBFF1DULL, 0x0B0524261D885C98ULL, 0x9979DE287CC2F1A1ULL, 0x48DB931464C01647ULL, 
            0xCA3EC0FE53F8B6A6ULL, 0x5CF765A5A22E6FF1ULL, 0xF60FA6F6292146E1ULL, 0x4B2EC3CAE8EC39E4ULL, 
            0x1C2E508B2B2DB0EEULL, 0xAD891512E81058B5ULL, 0xDDB0C70799804E0EULL, 0xA6A897E1FF30766AULL, 
            0x38551A019E4E3BDCULL, 0x60B9140647F26FB1ULL, 0xDC48E836B05C4D01ULL, 0x54957B211CF7C994ULL, 
            0xB51A8EC0D14BB938ULL, 0x2E3138F4FDECCC09ULL, 0x9F1C5878E815878CULL, 0xD008714654E825B5ULL, 
            0x9570A160508C5A61ULL, 0x16C5AA0780157655ULL, 0xCE42E7A12E5BF755ULL, 0x30DD6FF945225EB5ULL, 
            0x0B0B010C1E1C169EULL, 0xDC196EE71F46E639ULL, 0xF4CC475103514515ULL, 0x12ABEDE4C6B5862BULL
        }
    },
    {
        {
            0xE8890DCF80D23DB9ULL, 0xCE519F51483C9ABFULL, 0x743547D46CB009ECULL, 0xB378BA9E30003F3CULL, 
            0x1F85F4CC6377D7C4ULL, 0x9214400DFE6DC4F2ULL, 0xEB44DBE674639AD2ULL, 0x12E75FC738660821ULL, 
            0x3E1C6595F957BF57ULL, 0x8A7E7479221AF0C5ULL, 0xDF8E1D56AE28A2E2ULL, 0x7DA8B41B4DACA77DULL, 
            0xCE983447D2263532ULL, 0x7875F708FDE3FCCBULL, 0x1D1CE576AF1307D7ULL, 0xDE2FE32752A8ABA7ULL, 
            0xD0DA4ACBD2E755BBULL, 0x912518F7A3EF33F0ULL, 0x6660639942082173ULL, 0x950D31CF9E57D72AULL, 
            0xBE2E8AC94A9ACF9AULL, 0x06BF1873C344222BULL, 0xCC9FCD3206D6D4A6ULL, 0x7AD2F4350AD80226ULL, 
            0x488C6CCDB4A63D6DULL, 0xBA1587C2A2C2566FULL, 0x4113FB107C528804ULL, 0x84CC46E37673AB2BULL, 
            0x81AD5031C11DD6A6ULL, 0xDAB8515585361B61ULL, 0xC233769681E679F1ULL, 0x193BBEB143D67D30ULL
        },
        {
            0xCD4D8EB26433F594ULL, 0xE7B3C0E93B86E22DULL, 0x4B50B3D17A0CE224ULL, 0x727BCF7EAB15B67BULL, 
            0xF24416DEC1A5B177ULL, 0xFEC0428B5F2FD0EBULL, 0x75FBD2BC2F95570AULL, 0x602AA55C2340745FULL, 
            0x1A6C10D28D56019EULL, 0x2E640F57E063058FULL, 0x0120B479C241798AULL, 0x26F25A4AC731F094ULL, 
            0x59F55ED3154B4CD7ULL, 0x00AD4E64724D3E6AULL, 0x7168358B2E6A6959ULL, 0x6A15B61D41E3BE35ULL, 
            0xEF4DD6EAD182F71BULL, 0x9413CA1D1C9469B5ULL, 0xBA9A9F22C67DB930ULL, 0x3D81933CAC7574BCULL, 
            0x3240057222AC24C0ULL, 0x4BC937BEFC1D066FULL, 0xAE02BE25736FE420ULL, 0x437409955665F82EULL, 
            0xFD74E13F541983EDULL, 0xCEA564D39532432FULL, 0xE323408F84779673ULL, 0x0DB72D50FAA4B228ULL, 
            0x2BAF0CC7C8337F2FULL, 0x3AEBB63517A6D9CBULL, 0x5A09B2BB7EC04ECCULL, 0xE4E5BE8FA27EBD2BULL
        },
        {
            0xEA630B216D723DEDULL, 0xB8195202F5E184F4ULL, 0x443AB88AD9FF0D6FULL, 0x743485638B1C7A00ULL, 
            0xA803B26047D73643ULL, 0x67D3CA0FDC70F1BDULL, 0x2B2D32A76853ADAFULL, 0x2B8832E6772A312AULL, 
            0x65B1A76C930C67A8ULL, 0x54D3FF4668E04E28ULL, 0xD78F0C6049970DC6ULL, 0xF0E9F30E6577CA21ULL, 
            0x1D08858D30EDDC6BULL, 0x1F5969716DDF5CB1ULL, 0x5C2E66214213B3D8ULL, 0x59F16B4F0DB3260EULL, 
            0x8E6BEE0F331FA1FBULL, 0x1C6BE3718B1E6BD0ULL, 0x7D811065C6FCE0C0ULL, 0x407E5C6185CF778BULL, 
            0x25D497C60793CDD9ULL, 0x45C5A7F8FEDA8C9DULL, 0x04343F592B699844ULL, 0xABC7F9399F2A1E19ULL, 
            0xB839828B7A9AD89DULL, 0x489A0B5F46DA0CE8ULL, 0x81E21101AD81E19BULL, 0x31EBAF1F74EF777DULL, 
            0x064AB1BB6EFA3E61ULL, 0xE4C054E09FB0BECEULL, 0xB01580DEF4397B0DULL, 0x8CDCAAFC4B33B5A7ULL
        },
        {
            0x9F261423522E7C03ULL, 0x0B467681CB8AD95EULL, 0x4D9740670D127642ULL, 0xD882E6B756F7DCCFULL, 
            0xAC8FFFEEB48E2818ULL, 0x48CC1134742F001AULL, 0x209504A0D2F3807DULL, 0xA32C2A71EE045D4FULL, 
            0x367BCD67AAE72DD8ULL, 0x41DBF953EB987A50ULL, 0x8FD0B6A85F5DB5D0ULL, 0xA90794652FBCE0BEULL, 
            0x334756D3C3A420F5ULL, 0x720B4DE54F352C53ULL, 0x6161672C87635025ULL, 0x3BB0F5A4D994A6B7ULL, 
            0xAEF51E6C7A5A4526ULL, 0x1C3DE06AD64941BAULL, 0x6D750F472C231C44ULL, 0x51837EA706BF2E13ULL, 
            0x2AF5446DE177076FULL, 0xF4ABFE7C12032064ULL, 0xC9C080C7C99EF1B1ULL, 0xC513394D9CC88CF3ULL, 
            0x06966C4BC272EA2EULL, 0x476BD5219E85A3B0ULL, 0xA23C5A132F662867ULL, 0x2A2AE18188B5C7EFULL, 
            0x019AD22913C7745BULL, 0x662E9151BEE3D0D0ULL, 0x973C916BD1BDC12FULL, 0xAB6BE33D5475BD8EULL
        },
        {
            0x399B94A8649CED82ULL, 0xB8D13C151F92F4B8ULL, 0x983D8B62F8DD7534ULL, 0xFC13DB03F339D33CULL, 
            0x74035E262CEAF8EEULL, 0xB889ACBC4BF69A2BULL, 0xCDD5AE5F5C237933ULL, 0xF208FE36DF68D960ULL, 
            0x4ED25F4D6A4DDE07ULL, 0x7BCEF06C4B68B811ULL, 0xC41AB716CC382C12ULL, 0x355795D3D65AACEDULL, 
            0xA1C427B567B9A170ULL, 0xAB1B90D7E2E5043DULL, 0x544517429D9EC85EULL, 0x24FCF21ACB48E6EEULL, 
            0xAFBA60FC352F8B26ULL, 0x15DD08F167CC16CEULL, 0x54F0BD574438BEE1ULL, 0xA8ADD839453A2115ULL, 
            0x98C2B6B75E0FB876ULL, 0xD97F03647FB5488EULL, 0x335E60F7E785E4CDULL, 0xFF00D7E700D00671ULL, 
            0xB1B428BB9C762D13ULL, 0xF96913469C0BED8FULL, 0x0CD66D463CD5A318ULL, 0x0B03EEFEA3D10A20ULL, 
            0x4937ABBC3D762271ULL, 0x36C815E9995E9293ULL, 0xB0F352842625B984ULL, 0x95D69ECC678D3CBFULL
        },
        {
            0x3463C3F3EE5A5C83ULL, 0xB2C2809612660D01ULL, 0xBC3D8BEB978BF3E6ULL, 0xAEF0924502D230BEULL, 
            0xFFA680ACB5111276ULL, 0xF75C048C97A6A41CULL, 0x8D68990548B2698CULL, 0x57961CAB5CCE6BACULL, 
            0x9A2E6DB893BF2B71ULL, 0x4E1F144099A95D9FULL, 0x95063A661C542B92ULL, 0x0B494E3C9B16E4A4ULL, 
            0x6EF9E631210342BDULL, 0xC232BBFE8F09E586ULL, 0xBF06A7075B00F4DFULL, 0x3D069A923C5E1290ULL, 
            0x742F722ED6C9E589ULL, 0x1E8B32D8FA181D98ULL, 0xF06D9F99DB999F82ULL, 0x6CCB6BAE0D3F5948ULL, 
            0x6B8DC1BBB183D3A1ULL, 0xC1B3E724F7899701ULL, 0x59637C8C1C9319F3ULL, 0x7E29342657E103EBULL, 
            0xF4B0A2EADDA865C5ULL, 0x853031F8CF3D7598ULL, 0x11FF1DA69EAA70B9ULL, 0x551210DC3E9174B8ULL, 
            0x45ECDF33C687BCCAULL, 0x1C3D0045242FC585ULL, 0xCE5845D436D89BA9ULL, 0xE2846AB817EB2216ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseAConstants = {
    0xE823655F59D7FFB3ULL,
    0x89154A9061CD65FAULL,
    0xA5E71373322DFDCDULL,
    0xE823655F59D7FFB3ULL,
    0x89154A9061CD65FAULL,
    0xA5E71373322DFDCDULL,
    0x424051C5615575B1ULL,
    0x6B81D6E977D9DC25ULL,
    0x1E,
    0x69,
    0xC7,
    0xD0,
    0x7C,
    0xFA,
    0x92,
    0xA0
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseBSalts = {
    {
        {
            0xEB116A4826BEE3C9ULL, 0x352EFD4ACB7D8753ULL, 0x0D934F79C6AAA992ULL, 0x2A092E75E59D327BULL, 
            0xACF2765940DC2F58ULL, 0xD8D719BA22F6D75DULL, 0xA4F4CD09FF090627ULL, 0x01A4D9D6FBC94E7DULL, 
            0x969123248FEFBA68ULL, 0x3F2F6BE2E79ABB52ULL, 0xA668C0A8AE766FE8ULL, 0x1D17FB053657BA9FULL, 
            0x52E02CAD6CF12DA4ULL, 0xD8793EE74576E98EULL, 0x814F7AFD85DCC87AULL, 0xE4D97738DA74E39CULL, 
            0xACD2D0DD17861C4CULL, 0x21DCF6F8B68D57CFULL, 0x41626931A85BF949ULL, 0xE74F7569C1437931ULL, 
            0x38B3DA29AC31920DULL, 0x624220875892BA7DULL, 0x6B047AE1CCB5DDF5ULL, 0x11A2254C2E68BF8EULL, 
            0x966A740A3697B61CULL, 0x993FBD622EEF06EEULL, 0x6E4099F66D2A9099ULL, 0xE721D0F0931CC75AULL, 
            0x9D353A2ECBFCE527ULL, 0x931DBC80A2E3A4A9ULL, 0x710F22C7FC349572ULL, 0x789A268FA28AEB85ULL
        },
        {
            0xDDF03ADA89E1D285ULL, 0x1ECDFAAFB0FEECFAULL, 0xD53F591CF1701680ULL, 0x17DBCFA7DD0AE1CFULL, 
            0xCDF1C75F92968517ULL, 0x8030CD3191ED80B1ULL, 0x75669ADC0BA80E43ULL, 0xC9ADD9F6A3A2862FULL, 
            0x90798270EF384B1CULL, 0x138A607A9F1EA62CULL, 0xE7CE108244B9AC8FULL, 0x16D5D169D867F57CULL, 
            0xC207E38F2CC3A8E8ULL, 0xBA513AA939C3D6EAULL, 0x49AFC2F8E7405606ULL, 0xC7D51E0939DBF41BULL, 
            0xBDE62E938AC55A12ULL, 0x2ED34AC9E3669E8CULL, 0xE79D8C0838CE4E69ULL, 0x6CEF00A5479D319FULL, 
            0x2EF5A5529B501771ULL, 0x10C098DC59B54103ULL, 0x041C0315470F7BA8ULL, 0x23BBC18448CB538AULL, 
            0xE7B73DDEE11441E3ULL, 0x441EBC442CC86570ULL, 0x56D3DB2990B0318FULL, 0x9FD6FFD5B952E971ULL, 
            0xBFB6FEA169F9CC9CULL, 0x2EC3B205F4EEC98BULL, 0x696C92F75BC01B2BULL, 0xE54A0FE0F69D2786ULL
        },
        {
            0x3BF33AF18E30BC73ULL, 0x9603F457137AD43AULL, 0x1B886FA7C7C60151ULL, 0x3D654CB35E723A3DULL, 
            0x5732E10CA23C6E67ULL, 0x7D8F18FCA8C188C1ULL, 0xFA7E17D2E1F86153ULL, 0xF3DA51978514D96DULL, 
            0x0E44ED075B94A2F2ULL, 0x40F8F54610AC34F5ULL, 0x8FD2FAF789669A88ULL, 0x1BA9D0D4F65F0F2AULL, 
            0xB29DC924D172B73CULL, 0x67C19A0C03DBD3ECULL, 0x70487F3C88DC6F3EULL, 0x8A2189D593E5B76EULL, 
            0x33120F43D3F71389ULL, 0xE53B859D30D988BDULL, 0x7D5B2EE7D3892642ULL, 0xDFAD9AD414A6C50FULL, 
            0x2B8512B0B57DE47BULL, 0x2C39E44A6FCF6D57ULL, 0xAE48916D5B26A679ULL, 0x9315F745005FC4BEULL, 
            0xA1D7C5F47A367CCBULL, 0x2528ADF7A3A9F26CULL, 0x41065E4B1B8BA29BULL, 0xDD301B5F40AB334FULL, 
            0x957764EF30A10413ULL, 0x51FC2ACE9F2C2731ULL, 0xB44B589DB28C9600ULL, 0x53A7B6F8FF14C010ULL
        },
        {
            0x0F71FAA7A2F25941ULL, 0x1E80922A3A5EA3C0ULL, 0x41F3104EF4700EB7ULL, 0xCD44C5993BE19917ULL, 
            0x8BCE93B27F77D10AULL, 0xB29AF0CFFBD87CE1ULL, 0x12BE2021E4FF4949ULL, 0xFF6DBB10E5E581A1ULL, 
            0x9AF9A6427642AB4FULL, 0x3826844844E75D1AULL, 0x82CFD1799F17D5AAULL, 0x44604F3CE95E5523ULL, 
            0x76F085EC6B79470BULL, 0x927F6A936F2478BCULL, 0x3811D1BD56839918ULL, 0xE397CEA9378F3365ULL, 
            0x9427115FBAD9D055ULL, 0x2C95C387B67C5759ULL, 0x8D0E0388BC9B73FAULL, 0x720E33D92DB04FCEULL, 
            0xF3F750CAE2EA0BFEULL, 0x2CC2B9E8AE3CCC33ULL, 0xFAEA5ECB31B3B30AULL, 0x09FAF4191889206CULL, 
            0xBEBEA840CAB28CF4ULL, 0xFCDAC40574CD4DEBULL, 0x90A6F0B0C6D5644EULL, 0x3E4671BF71A3DA87ULL, 
            0x0736607FCC112738ULL, 0x27CF4FEE2454E70CULL, 0xC382D261A1B48204ULL, 0x2566831B41203C44ULL
        },
        {
            0x8298589F49D72CCCULL, 0x10075E580F07683CULL, 0x8C593BA8D10B7EA1ULL, 0xE74F98D9563E0EBBULL, 
            0x06374B8DDFCB7456ULL, 0x7DBBE077C94C404DULL, 0x2FD496F6BA9B8E95ULL, 0x1476744E97DF09E2ULL, 
            0x469D8A61FC8E2637ULL, 0x743698F3C07DAAB8ULL, 0x64BA5BD992BC12DCULL, 0x88E18A823CDEB8F9ULL, 
            0xB415790DE6943377ULL, 0xEAA14A6FF3158776ULL, 0xA0BF0CC1591F7360ULL, 0x9BE7F5C6A11142CAULL, 
            0xEC9002FA2899F6FBULL, 0x939A8C060E593974ULL, 0xA6D557FE650ADF42ULL, 0x5C5DAFF7A169D2F9ULL, 
            0x9201A2CAB9F7744EULL, 0xC357DA54B66E3B51ULL, 0xD06D272FC0DF1358ULL, 0xC8F471DCD6414188ULL, 
            0x7425CCC6965F9ACEULL, 0xCDA6A9B77AFF527FULL, 0xBBBD0C1B7DCAE258ULL, 0xB8B10A7822EF739DULL, 
            0x4CBB319E384DB326ULL, 0x817DFF76B8D7DF89ULL, 0xACF4B347BC70711EULL, 0xE22E9CA941030144ULL
        },
        {
            0xF1389AF491376016ULL, 0x5DD35F879B825500ULL, 0x9AC98F42D0B7EC0FULL, 0xBA0422F5903BA11EULL, 
            0x5B2B58D17151168CULL, 0xBB8B58582C2B1C27ULL, 0xB662C01D967C105CULL, 0x7C018B156BA7C2EAULL, 
            0x3E8769EDADDB8DF5ULL, 0x79812691B4DE17BCULL, 0xEE6DE2A155A2CAC6ULL, 0xB5183BD6D0FCE4EAULL, 
            0x4F1FAD4ACF86F04AULL, 0xD2F769746AAC7E76ULL, 0x28973022F6F18662ULL, 0xDA15D491055A64ADULL, 
            0x0F5FE62201A0F07BULL, 0xEDEB9037B16F097FULL, 0x72EE8394FDFD977AULL, 0x8D38CB6F41585FEDULL, 
            0xEA00B3E78CFF1949ULL, 0xCE763C9CDF8EA4D5ULL, 0x08CFE8D00AE5DC0BULL, 0x0A53AA62E1DE454CULL, 
            0x100FF2ADA4B9C0EEULL, 0xA8F9C957911BA876ULL, 0x20FBCAC424CF9BBEULL, 0xF73A11AA9C616127ULL, 
            0xC8FB6B7062D4734FULL, 0xE432E25D1E3A0052ULL, 0x8AC68695E6D4B651ULL, 0xC21D00FA6A5DC93DULL
        }
    },
    {
        {
            0x6B1BC3BEC0EBADF7ULL, 0xDD0B8BA538BA9410ULL, 0x8EA4B6571250AE8DULL, 0x2034E934F4D3132FULL, 
            0x87930D03251AC710ULL, 0x28C325917A4B89A3ULL, 0xD3E137BBCFA04D54ULL, 0xEB75510D03820876ULL, 
            0xB55B980A0B492305ULL, 0x764F1850A117B5B7ULL, 0x3E11A5451293AF66ULL, 0xCBC93EBC6D561F3CULL, 
            0x24E5B358E37E9BE1ULL, 0x588EF77F909E700BULL, 0xE90335023D25F469ULL, 0x6FDF9FC4475BD0F2ULL, 
            0x15907AF546F50588ULL, 0x204E3C8EA6288B1DULL, 0x757E23B0BFCD5411ULL, 0x46E355A28D197B42ULL, 
            0x94729CD17212066FULL, 0x3ACA321DAE8501A1ULL, 0xD065E1F7579E9EE5ULL, 0x2DB9AA8AD468CB88ULL, 
            0x1B63AA1D665013B6ULL, 0x35F160C143A1D63EULL, 0x3067D1EEB9C99273ULL, 0xA5698876F6F3A50DULL, 
            0x6D735560E8AEA9B4ULL, 0xC6E0A58A292C5FEAULL, 0x7B64BA26CEF18BE2ULL, 0xE5FFC16489BB9DB9ULL
        },
        {
            0x495187D7C1E7D5D4ULL, 0x2241A29D6555368DULL, 0xE2CEC9FCD77DBA1CULL, 0xFEBAC159028955B1ULL, 
            0x7F439DF441BC4C87ULL, 0x3929E9C571E52C3BULL, 0x473F39E683E934FBULL, 0x50B3A699D6FD0768ULL, 
            0x7DC747CD5B12044DULL, 0x33A5292112693C61ULL, 0xB0BB0359138B9987ULL, 0x4452994D86439C45ULL, 
            0x88BBF95E9E5705DCULL, 0xC8D104F7D0EF358FULL, 0x1E1769FC6AFFD587ULL, 0x51A807ADC5CEFD4EULL, 
            0xC5E19FE505589D68ULL, 0xEBCFC6652A931716ULL, 0x49D690F7E5CB0823ULL, 0xFB8328609CCF8644ULL, 
            0xB14AE9DE286E1A7AULL, 0x77083F983AD0649DULL, 0x9A2386EDD361CE51ULL, 0x3F5C8C193A1BB151ULL, 
            0x2A91DEF741B75907ULL, 0xEA25FB07DCE2F759ULL, 0x432205912D724745ULL, 0x7CA516DA3EA92ADAULL, 
            0xE7BCD5A633D2B945ULL, 0x8A36A720647E6CA9ULL, 0x2084D41663D39BB4ULL, 0x5F30F050A7159291ULL
        },
        {
            0x2FE790427D4A1ECBULL, 0x23346AA7606C2814ULL, 0x7E297F9F91633868ULL, 0x8C77353739E408F0ULL, 
            0xA1ACD6FACD871AC0ULL, 0xC8CDA2C1E1E98EDAULL, 0x95ADF39842A76FDAULL, 0x3733AC097F2B6909ULL, 
            0x89A038CDF1848859ULL, 0x3DBB2DCEA7135042ULL, 0x725572844B739FB4ULL, 0x07935E7B8E9BF618ULL, 
            0x6575FC1C24F9B9EDULL, 0x2A9EBE1DB6CF549FULL, 0x8DD0843519C3205CULL, 0x41049CF26C7B00A2ULL, 
            0x3ADB059C1E2311AFULL, 0x8709F7122BAEF096ULL, 0x46BE8A9F8241E345ULL, 0x869C986DD8861317ULL, 
            0x025B667936961A6EULL, 0x4C881B39ABA699D3ULL, 0xD5D0A4383EA35C59ULL, 0x02E17F04E90ECA27ULL, 
            0xF1323A1263290EF3ULL, 0xEE756AD94D7546CCULL, 0xFFF836B0EE6FE0A8ULL, 0x2318AE2F6221E3F3ULL, 
            0x5D71C867EC0FF390ULL, 0xC04804BAC64F8706ULL, 0x9CA127915EBABFD3ULL, 0xBE47E03C708027D5ULL
        },
        {
            0xD2E1E93A7AFFB62BULL, 0x524BD1C6CB901143ULL, 0x7FF8FCB3F18C0F8AULL, 0x1BCC8C9CB1F34CC9ULL, 
            0xBE5F4A78C9D07D75ULL, 0x2FC224FADEF28E17ULL, 0xD759CD2EA0C3C15CULL, 0x521DD0149EB8AB88ULL, 
            0x63069837122345C4ULL, 0x8974680250DF7514ULL, 0x501847CD5F36BE09ULL, 0x8B32AD8D4684AE36ULL, 
            0x2EFD6A939D59DCEEULL, 0xF3756E512B88C823ULL, 0xB6CF005F699763BFULL, 0xB20CFDC26DCE7C85ULL, 
            0x7376AE370C59F627ULL, 0x980B09AEDBEA6370ULL, 0x3D82FAE56917CAAAULL, 0x4ED2A48CC6C64E79ULL, 
            0x0C41F0EE080C347CULL, 0x1E9CB8E804741D06ULL, 0x6F423B430DC113AFULL, 0xF06200C3B9DBC1BCULL, 
            0x8B086A4348F9ED11ULL, 0x31F263FFC457540BULL, 0x69AB7D864FD3062CULL, 0x27DE6C9E600079EDULL, 
            0x02709A03EB850FAFULL, 0xB0D57CFCEB3D90D0ULL, 0x9635860E978E9645ULL, 0x4A0A55D626DD20FBULL
        },
        {
            0x11423B9789785BE5ULL, 0x52F39C51F077BEFAULL, 0x0DFF2F84363A2BC2ULL, 0xD4478981E8462324ULL, 
            0xA193485C9F204BF1ULL, 0x84E5D0FC04CD5164ULL, 0x738FEF3B7D0F657CULL, 0xA5058ABF0D8DE374ULL, 
            0x6E54E85F8703A5AEULL, 0xE00D165D4119034BULL, 0x7CF831902C9391B9ULL, 0x4DE14A4D7A5364DAULL, 
            0xC67F7F50AB3F4328ULL, 0x5A7ED2477932E15CULL, 0x4C2964CBA144F941ULL, 0xD8D1094495FEA847ULL, 
            0x381966F56690B453ULL, 0xA11D0C057C78BDA3ULL, 0xF3A628D34D029095ULL, 0x13E16EEBA57A04E9ULL, 
            0xF5F8AF6B2B522B66ULL, 0xD4C163DE6AFAC2A0ULL, 0xD9D55FFAEC3877E4ULL, 0xD350EC7B6EB0E6D7ULL, 
            0x930AA7C372F24CB0ULL, 0xA35CE5DD61D0CA79ULL, 0xCA67C8540478A512ULL, 0xDA12294B7CCFCBAAULL, 
            0xF321847CB0CA7699ULL, 0x523BDA73CA681E06ULL, 0x008350DE11A175DCULL, 0x6BCD671077F5EC9DULL
        },
        {
            0xCD625F2A6F8489BAULL, 0x6A76A0C19A0958FBULL, 0xB4A121454B2B9C20ULL, 0xF4B7C62707E73197ULL, 
            0xF1E48E37B5DD26E2ULL, 0xC9FBC616C5E80BADULL, 0x666891F9EE49B2F2ULL, 0x0D57B42044CFD53FULL, 
            0x5924745684C04A59ULL, 0x3873E85CFACDD93CULL, 0x274123B36279FEBEULL, 0x3885DFBCE6964843ULL, 
            0x14BE36EC4B49E1B0ULL, 0xAD81EF0EAD30412AULL, 0xE70FD664A436C028ULL, 0x2F880BA008F47596ULL, 
            0x4A7EF2EEA0C104C6ULL, 0xA2B2E155C01E31E6ULL, 0x94DAD6757FDF3272ULL, 0x91B24A4CBEF0CA93ULL, 
            0x3CD317BCF785132CULL, 0x7B9CC42EB8E00506ULL, 0x92C00E1660F285C5ULL, 0xF857412B9E77FFC9ULL, 
            0xF307E450FACDF4DDULL, 0x682B0C958DC08BBAULL, 0xA0119EF0D4E6BBF8ULL, 0xA2C3BAE846E66305ULL, 
            0xA9D7E95B6E69A184ULL, 0xB45D147B03FDF37BULL, 0x54309C667FCF5F98ULL, 0xD475173D89F6FD47ULL
        }
    },
    {
        {
            0x77871DF6BFC70D4FULL, 0x628C839337226A71ULL, 0x0F3A285EF0771865ULL, 0x6B0219AFA23810F1ULL, 
            0x818C3469E7514F65ULL, 0xFCCA721A7198F462ULL, 0x0CF6B1F5596427F7ULL, 0x3D849B4281652C8DULL, 
            0x4B2C917160A4D971ULL, 0xF88F730211A9D764ULL, 0x99697F46B1AA39F0ULL, 0x4C27DC583CEE562BULL, 
            0x8C2492DB469D49AAULL, 0xB8F006175BB6AFEDULL, 0xF295854462250400ULL, 0xBC282BD173EF8A2BULL, 
            0xD5C6541ED588231EULL, 0xC88BE441D55F9D42ULL, 0x283CBB87D2727E7EULL, 0xCB32C2D488F8FE77ULL, 
            0x7B77F495E65995C3ULL, 0xCDC29FED1265FDF8ULL, 0xD58A8F84B2617E04ULL, 0x3B7AAF6A72933043ULL, 
            0x404DE214403F4D3EULL, 0x889156FB2864EB2AULL, 0x4732BBD359EFFE67ULL, 0xB44D73340F8FD885ULL, 
            0x1B0B4844D896E31EULL, 0x43C6276EC49A1DBAULL, 0x0ED57B763463924DULL, 0x7BC1DB3529383947ULL
        },
        {
            0xCD682DF7F6340407ULL, 0x827BC46B7E672F29ULL, 0x2F878707B12B2E8FULL, 0xB2650CB6A5389186ULL, 
            0x2624F18101D4825CULL, 0x5E5931206FF98696ULL, 0x6943F3A2B2BB7268ULL, 0x50512288E473352EULL, 
            0xE2228706B8B85B6AULL, 0x661EA7D523279AE1ULL, 0x9FD93D111543D0B4ULL, 0x2FB532FC5313A009ULL, 
            0x37AF891F35717AB2ULL, 0x62F21F8C13805B4AULL, 0xDA35A403465B8CF4ULL, 0x16EEA8486C61B559ULL, 
            0xB406DFD485103165ULL, 0xA871720964B1CE63ULL, 0x9833EEB7BB3BF2EEULL, 0xE67E09C37FE64930ULL, 
            0xDF26127F13C9033AULL, 0xD916F4FF6F97360FULL, 0x7746AC8077A159F8ULL, 0xC4440B439895D7D1ULL, 
            0x8CF517F20A893A1EULL, 0xC55E8B9C29403F67ULL, 0xDCFB896918F1A723ULL, 0x6EE53A1D09BFC6AEULL, 
            0x2DB74ED512EE5DBFULL, 0xD3A7D29AA164D3A1ULL, 0xCCAA478ACCF1066DULL, 0x521E310D56F50327ULL
        },
        {
            0x08918364764D95C7ULL, 0x7ED8D02FFF2E9B3CULL, 0x44CA236FACBCC59FULL, 0x6F83E85C36DA49B1ULL, 
            0xFA182BC172CC4F70ULL, 0xDD005AE0D81C99C2ULL, 0xB6F720719EA64D3FULL, 0x0C386397A11849AAULL, 
            0xF224E28DB2E08CBCULL, 0x67EB67BA9E6FE46CULL, 0x23312E01B4AFFD52ULL, 0xE99400442855CF7CULL, 
            0x39DB1DCB4E82C266ULL, 0xBC33851E086F1EA9ULL, 0xD6E4D21045140B21ULL, 0x08EDE0509170AA58ULL, 
            0x3EB17746403ACF93ULL, 0xA7C74B2D13538438ULL, 0x2D5FE514370D9DF7ULL, 0xB51737747D18A896ULL, 
            0x365272CC112077E6ULL, 0x55720C666EBBAFF5ULL, 0x00D289F48E31C648ULL, 0x9AC604177E02CDE0ULL, 
            0xC4B40F2493EED48BULL, 0x916A2EBC9C356F30ULL, 0x8F48C24689D840CEULL, 0xE59DBCAEB00BA91BULL, 
            0x8F90CF382CD7F8FFULL, 0xDE873AA89101B6CFULL, 0x2A6F2A30967EC55BULL, 0x5A7042C66C3AD9D8ULL
        },
        {
            0x66C96DD955411D5EULL, 0xB24A2F6ACC96179CULL, 0x3CD1A3B35CC40F13ULL, 0x43E28C4534B320A6ULL, 
            0xDB3F8B82EB559952ULL, 0x495185C550DD5CBBULL, 0x1E100AA9CE72C50DULL, 0xA6F73C40B28A74F4ULL, 
            0x237F19EEE95B9C7AULL, 0xFA960F32000D70DAULL, 0x4B50E2EB3FABA5F3ULL, 0x5646250E8C8A8469ULL, 
            0x65AE176702AB9D1EULL, 0x12F45A65F37656ADULL, 0x6D269B558B90F80CULL, 0x78A0798FC7EC0ED3ULL, 
            0xCD163CAD495FF384ULL, 0xAFE08A5B926466F9ULL, 0x0DC99E8F6496E33CULL, 0x456066E23FD0D6A4ULL, 
            0x4B2DB6788926C741ULL, 0x99EF3FAF4829F71EULL, 0x276D26309AAD2975ULL, 0x7729391441B177E8ULL, 
            0xFCD7C86DAABEB976ULL, 0xDBFFBBA4582512F5ULL, 0xE7D999449C41C9F6ULL, 0x24FF1B2AD6446597ULL, 
            0xB6B4BE4EF5BB1AD9ULL, 0xB7B4BCA5D27732C0ULL, 0x6117820228AA9E7CULL, 0xDFF873696FDEE818ULL
        },
        {
            0x3406E7DEDEC9071EULL, 0x71F9A6C2EEBD0BD9ULL, 0xDC2A648FD0594137ULL, 0x8F34AC464EA309DFULL, 
            0xBA939A1DE9A37EDFULL, 0x802629987D082B31ULL, 0x335DAAAD780B1947ULL, 0x1192B74F96094DA0ULL, 
            0x6C5C960EAFD46EC3ULL, 0x8BB1D8634F71B710ULL, 0x5BE851DEF267D7C6ULL, 0x0AD828CB0A2989EDULL, 
            0xF5437743A9194057ULL, 0x5045476652604972ULL, 0x9D87BAF46637E953ULL, 0xCB4A2CB606A10A96ULL, 
            0x7348BA99C3610405ULL, 0xFFC7908CF637B86AULL, 0xFE871A9C4073F4E0ULL, 0x5413F8C34DC562B5ULL, 
            0x47FB0070C219C992ULL, 0x4099716BF26C0EF4ULL, 0x968FA0371BB42B07ULL, 0xCB9B82223B131DC6ULL, 
            0x95BED9BB9DED6CB5ULL, 0x8852E5A5AA2C2203ULL, 0xF11168CC3A4660C1ULL, 0x21680D5358BB9CC6ULL, 
            0x5CFDE72185AEE3AFULL, 0xD264F8A44F136915ULL, 0x3BABFE2F82096D29ULL, 0x98A0C0D544E63272ULL
        },
        {
            0x4DB9DB8607474E18ULL, 0x8102D831277E75EDULL, 0xCC0196F10F05EBECULL, 0x56F1074FD69ABE79ULL, 
            0x18BC134CB5EE7EDEULL, 0x4F11F954FCADFFB3ULL, 0x9109B86D6B2C279FULL, 0xE741F9F139021BF9ULL, 
            0x939B0F2DD7A35A4BULL, 0x4E952ECF0E0027C5ULL, 0x7334EBA45FCB487CULL, 0x5CAF3B36330A756CULL, 
            0xC446E636F5F38DB3ULL, 0x30D7068C8405DBF0ULL, 0x5BFC7A0E419C120CULL, 0xF59406BE4AE29B4DULL, 
            0xC003745D34895FEFULL, 0xE4E5C9248D9ED0AAULL, 0x9E1091E95EA02AC5ULL, 0x7E936CDC0C2B68AFULL, 
            0xFBC656CA5F846BC7ULL, 0xDDDE39723935E615ULL, 0x77439D4A93CCEEEBULL, 0x132D94891BC078B3ULL, 
            0x0A09111921A408AFULL, 0xE1F6DA58DC6FAE82ULL, 0xD6A686A55B18D90AULL, 0xCC7C01EC372CFF9DULL, 
            0x0CDB11470F17D352ULL, 0xBE20B2EF6196AF73ULL, 0x9A752373AA2A14E0ULL, 0x65AC7FF9C91E96CFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseBConstants = {
    0xDAD6B036D97001E8ULL,
    0xC4FC6B52525E0EFCULL,
    0xBEB5405E7556523CULL,
    0xDAD6B036D97001E8ULL,
    0xC4FC6B52525E0EFCULL,
    0xBEB5405E7556523CULL,
    0xABA9A85F7B57EB94ULL,
    0x42A847CE57E6CFFBULL,
    0xF5,
    0xC5,
    0x4A,
    0x17,
    0x3C,
    0x7A,
    0x65,
    0x80
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseCSalts = {
    {
        {
            0xA0D38672DBD06F38ULL, 0x4339C5E541E0194DULL, 0xAD8961710E4C2828ULL, 0x5B22BDB18980DC5BULL, 
            0x3EBB1F9BE5D8B121ULL, 0x1DA493104AF10C4AULL, 0xEE1996B75A823EECULL, 0x9297B8F1E2503285ULL, 
            0xF38B1D5AF7BC45E5ULL, 0x84A1BC6F7FB60756ULL, 0x0495332E8E29B027ULL, 0x803AF172904D6456ULL, 
            0xACA51E25A1EDF8E0ULL, 0xDB102DC7F1A7B54BULL, 0x02E08229D3779BD1ULL, 0x24B32154972A9575ULL, 
            0x31E546CEDAF299D8ULL, 0x09A5725196850DCFULL, 0x8A19533F87C053C0ULL, 0x7D81CA222BA13DB0ULL, 
            0x883ABC85BE630978ULL, 0xE66AD9317D12CC2DULL, 0x5498DB7E5CCF74A7ULL, 0x099DE83737D7D96AULL, 
            0x30E9FF11E21D6DEFULL, 0xDCDD6D7B174ACAD3ULL, 0xCB0CF27872D4DABFULL, 0x78E54681AA2BF099ULL, 
            0x4B3B625319643F64ULL, 0x7567F781EE0869BFULL, 0x35836D3C872172ADULL, 0x841B0965EEE288AFULL
        },
        {
            0xA1147845696F0972ULL, 0x7F78E032A297C1BFULL, 0x29C2E155765B4980ULL, 0x8AB8D2A49E3F88E9ULL, 
            0xE61A0C71545B2DE4ULL, 0xE0665354C3D0AAA2ULL, 0x7DF91EC817F9F5A0ULL, 0x2AB67781542C9A0CULL, 
            0xAC932D5850B6CD5DULL, 0x4A64AF4BA62C9B94ULL, 0x62B7894EF2F13B07ULL, 0xA93682BF42B7425DULL, 
            0x71E7959A79370EC8ULL, 0x1344B02BE38AF9B9ULL, 0xDAF07CE18FAEE0F7ULL, 0x8E5948A13A28F17BULL, 
            0xF8D53DF205EFEC47ULL, 0xA6B362832A7233ECULL, 0xC0C0DA67F646BD6BULL, 0xEAD87BCBD9BDD2DAULL, 
            0xE2C7C8AE2308C522ULL, 0x3DEC841EB0FCF87AULL, 0xA669A388591D04FEULL, 0x930ABE2AA9F3E8F5ULL, 
            0xB13D81C0D449D501ULL, 0xB609D060E7260B3DULL, 0x8FC1E34FB2F522B2ULL, 0xD248FF57BD25B327ULL, 
            0x223E534A8714BFF6ULL, 0xC151D0B225351F51ULL, 0x550D8F8376997A45ULL, 0x4B0009D0F6323CA4ULL
        },
        {
            0x5DDDCCE13BF69395ULL, 0x49099C523DDD66CFULL, 0x854DDB4B7B3D2A1AULL, 0x0DA7E987C2B139BEULL, 
            0x68DC280837D1743EULL, 0xC7A5D299F2C05B8BULL, 0xB72123BE0B73CE94ULL, 0xCEE30F5FA3A7335FULL, 
            0xBE983C3F84B04948ULL, 0xF322DCC619C41F26ULL, 0x8CEFB24E104B87B0ULL, 0x47D30A7BAC351DB6ULL, 
            0x14B352F393CD7DF7ULL, 0x218D77BA213905BCULL, 0x1F8ECF1A973CEDBDULL, 0x5344D8B4BF2DC01BULL, 
            0xF90E370E8824A23CULL, 0x807B011B83FBBF06ULL, 0x76A5D96B1F441A87ULL, 0xF5614EB32368A3CEULL, 
            0x554A8FB69A30E086ULL, 0xC31409F3E7D755BCULL, 0x4C1C58B8512C2886ULL, 0x609185D6A5416A32ULL, 
            0x76922B7AF32D9394ULL, 0xA7EC6FD8EF8E8EC3ULL, 0xA4A70E0BB8C218DEULL, 0xC96C8E9369A20149ULL, 
            0x2330E21912C4B8D4ULL, 0x6AD7907C74549A61ULL, 0x12D979345DDD915DULL, 0x6610968E5E2AE0CFULL
        },
        {
            0x695C3CAA5D6233F2ULL, 0xD0A0020F54389CAAULL, 0x9FAAF08C0ED7042DULL, 0x286592BE196FA3E8ULL, 
            0x2F135E067E63B2E7ULL, 0x067C91906D56274DULL, 0x98A1ABAD1AE484F0ULL, 0x5D09B4541A21D980ULL, 
            0x7E13DD46C67663E1ULL, 0x5E4F688DE7EF2103ULL, 0xEA6D294ADF481561ULL, 0x1E543A9D73D5FFE3ULL, 
            0x621084000F6DF0C8ULL, 0x5A37829A601E582FULL, 0x4DE6276A7472E952ULL, 0x493176176B21C5BFULL, 
            0xA0C5EE04FF2F38EBULL, 0x5690921A8F7C8769ULL, 0x40C97FB78DCFF3F2ULL, 0xBAF5A0DD57E73E8BULL, 
            0xB99CEBF2A4ED2E27ULL, 0xAADE6D70AA40C833ULL, 0xED9A2F2F3782C6EBULL, 0x2F58935A5713351CULL, 
            0xA10298CCF56E03C0ULL, 0xF3DAD01336E4E02CULL, 0x406E35CF8BA6F1D6ULL, 0x1E383D9A54F70F3DULL, 
            0x6B60CB00C79DC454ULL, 0xF6525DACCFE28074ULL, 0x01EB6875DF0EFF98ULL, 0x4DF57332A7091E8AULL
        },
        {
            0xB12F6BAFD7B9B059ULL, 0x81077A29C3B4FDB6ULL, 0x8B25E8D81FEF4685ULL, 0x38A735F8543A82D0ULL, 
            0x84E819EFF811C051ULL, 0xF9BF0A6FD902CFBDULL, 0x9E523EFCF18EE8E0ULL, 0x52736588641E09FEULL, 
            0x053186893C5E5FECULL, 0x6F2BCCE73D789D22ULL, 0x355D1C8E556F074AULL, 0x9DD85463CE46D7D9ULL, 
            0x15FD62F932C53F4FULL, 0x8E402784ABC4BDD7ULL, 0x73B546AF343CCE28ULL, 0x5ADDB5F0A01A2900ULL, 
            0x7CE1537FD6100087ULL, 0xAA804B2B7DD23F15ULL, 0x94122AB501C91645ULL, 0x088DF8FE1042D239ULL, 
            0x2C560013EC42D9ABULL, 0x2B23439A6897E458ULL, 0xF30E717BA3ED5B64ULL, 0x9D9C4DF1F30A9329ULL, 
            0x6969C1CFD8BC3D54ULL, 0x91536F79CB399C83ULL, 0x733958BCF5D812B8ULL, 0x26C8EFBC8B9E1978ULL, 
            0x3A82143D1BB1BCF9ULL, 0xE6209DCFB2B37DF2ULL, 0xBC4AC6811D9B4521ULL, 0x373B5C019FADCB44ULL
        },
        {
            0x9BAC1221F54CCF0AULL, 0x2D8E8DC76839E8C1ULL, 0xC1AF088973109C9EULL, 0x1F11090D5192C81AULL, 
            0xED918CA109E0C5F3ULL, 0x01A87DB0F1EA643DULL, 0x558DCD2A6D0D763CULL, 0xDFABA541E46743F2ULL, 
            0x103DDE7FDCF1B11CULL, 0xBAB472B549E3B0BEULL, 0x289C3D1AA80126A8ULL, 0xB1F26E27B5A7BA88ULL, 
            0xCC009ED41A461D68ULL, 0x05FF56C98E5F2A63ULL, 0x43D90AD0A11EE688ULL, 0xC613BEDBC85D57AAULL, 
            0x90228B4AC535B4A8ULL, 0x8149092E5EED21A8ULL, 0xA3B939A9C3309BE0ULL, 0x47640B888CE8EB6DULL, 
            0x7CEDDE1C5B15CE4EULL, 0xEE7DD951F2F63A60ULL, 0x3532DE13C1E8D414ULL, 0xA7DB77CA6BA474FCULL, 
            0x559E2BDE563EDD1BULL, 0x89906ABC957BF45DULL, 0x1C80D10FEE0E1F61ULL, 0xE76D39ECE7B90DD2ULL, 
            0x96E7B6D88379C95BULL, 0x98DC41422EBB5BCFULL, 0x6AC78ADFB9F4F90FULL, 0xAD31190D1982AA20ULL
        }
    },
    {
        {
            0xCA66E667219F1E10ULL, 0x121BA3690C6518D1ULL, 0xDE64719D3A095F6FULL, 0x0C7F76702B3B01DEULL, 
            0xA4096339615259DAULL, 0x37BDFBB9479AD6CCULL, 0xC318E36C57FE7893ULL, 0x8008E9A27B707E98ULL, 
            0x87A0EF2A6E29B965ULL, 0x92FAE7D8BFF9BD1CULL, 0x384A10447185FDD1ULL, 0xD32BA922B5A08617ULL, 
            0x12963D27FABD9759ULL, 0x1DA67F158A133424ULL, 0x01C15C270D305F59ULL, 0x91EBDC14F54592DFULL, 
            0xCC05B37E494EDB80ULL, 0x311FEBE05D1ECDAFULL, 0x98761E48D43A8304ULL, 0xA94E68CBCA5F06DFULL, 
            0xB8306F347976CA4AULL, 0x95BB497A58D16B26ULL, 0xA27155DB9E1B2AA5ULL, 0xBC0772534A03861CULL, 
            0x859278AB416B4232ULL, 0x97E2E9FC3B6D5FDBULL, 0x24B3F5CC241F5179ULL, 0x42231E09D0463997ULL, 
            0x543811676A6A46B1ULL, 0x8AC78D30308BBEADULL, 0x3F8B1B91139B36FBULL, 0x5D0184125A6AEEA8ULL
        },
        {
            0x2452C311C53E7526ULL, 0x8F4B8C4B7894052BULL, 0x858DBE9FBD30FA0DULL, 0xC906181E8F819C28ULL, 
            0xB03EFE5BF1CE632AULL, 0xAB78AE7E0612FE74ULL, 0xEAE2250D97DE6862ULL, 0x57B2A25B458428CEULL, 
            0x2DE0074E760B9DCDULL, 0xB949399130E53100ULL, 0xC07B03CFFC5C92B4ULL, 0x11E9C227D157FB27ULL, 
            0xB557FB32FB0C2729ULL, 0x8646F7A27FB6158CULL, 0x60DF79C87BB9005FULL, 0x0D16B25A12DC5F06ULL, 
            0x907689A5E5F18CC6ULL, 0xC30095B63AC25A66ULL, 0xA099261B7A48EEFDULL, 0xBEC1D131C1A01A8CULL, 
            0x9BBFCE60FEFCE7EEULL, 0x9DDC1D587F0474DEULL, 0x549CBF9F553067BAULL, 0xB213B12CD136198AULL, 
            0xDF70F8F8ABF8827BULL, 0x9F1774B04A88695FULL, 0x2BA5116844340FFAULL, 0x683B6912AC64C677ULL, 
            0x2C48CC564DCC0A5BULL, 0x064DE4A36EAFC412ULL, 0xC1621098F327EBA1ULL, 0xCD49CFAA1F01BA87ULL
        },
        {
            0x9C1B25B3FC797C7BULL, 0x69A660095D947672ULL, 0x1434396ED42EC61DULL, 0x04F4CCAF7FE16F49ULL, 
            0xC59307F3D8DF0BEFULL, 0x1176A7A2BD8F9F03ULL, 0xEBC023615985EC7BULL, 0x9CD6E8B8C1F1E299ULL, 
            0xDAB869E77D62FBC2ULL, 0xE69A636A60D0D8BEULL, 0x51F26134AE80DEFFULL, 0x3864BB29C6F1987FULL, 
            0x11F070DD4D380E39ULL, 0x3D2B186EF2124DA6ULL, 0xF5DDB0D956C27057ULL, 0x7BD09A6B09274A08ULL, 
            0xD47F8BE2677EEAE1ULL, 0x6846CF05F2AA67B8ULL, 0x5C0FF1A3B7AC29B6ULL, 0x7E5922465CBF1C04ULL, 
            0xD25C64FEA25B908BULL, 0xCDAFBF55ECE9A2FBULL, 0xAAD080C9204F48AAULL, 0x4BE695FA3109BCD2ULL, 
            0x3D3B55D7A4D37EA4ULL, 0xE2B1815FAFC82E38ULL, 0xA23E0F652A8EB539ULL, 0x9C750248C61708F5ULL, 
            0xC9DF68A650AFAC60ULL, 0x707F35C663A937A7ULL, 0x4FA6D8EBE80ADDA0ULL, 0xC2E62EC22FA7673AULL
        },
        {
            0xD4EA3C5CC57C1A6CULL, 0xFD5DB5A72077D38DULL, 0x98C1FB18B75382A6ULL, 0x4E92D3C4B2032F83ULL, 
            0x9E790D518CE81F1BULL, 0xE095947E667E7FDEULL, 0x6A89D537423E5608ULL, 0x7143388513B8E98DULL, 
            0x7338DBE4A1CAF296ULL, 0x1097D694489F0600ULL, 0x643047C1FA997BCEULL, 0x2DA76F46A31A6AA3ULL, 
            0x3B5B2255D71B67CEULL, 0xAF5824537B8EA68DULL, 0xCFFA78DF0A933658ULL, 0xF7B728C74740F5D6ULL, 
            0x807A1F78B21C6531ULL, 0x77D9163F894DEDACULL, 0x60121779EEBA7BF2ULL, 0x0D553C90A2951EF2ULL, 
            0xCAE3E7BBDC439D08ULL, 0xCAD3E47A2A3C886EULL, 0xAFAD43CB00504A90ULL, 0xC646BE0B12A7AC5DULL, 
            0x3F3C0F8D432E2054ULL, 0x15A7346860B58436ULL, 0xA48DAD3750F236F8ULL, 0xBAF3F177ECCCC4EDULL, 
            0x39A0C10D5B41BD7CULL, 0x84E59AC49143F60AULL, 0xA238D676183F7C54ULL, 0xA7D5921E908044DDULL
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
            0x792FFAE48D8EA3A9ULL, 0xF127EDC88C4EB42EULL, 0x82D19C6BB9A4C54FULL, 0x4BE777745D042A24ULL, 
            0xE5DF59CDA5B53501ULL, 0x71AB74F9ED032632ULL, 0xE7627A3FE864945AULL, 0x9A12E91C3F8DC077ULL, 
            0x7B843DFE5D747724ULL, 0x7EC0948ACF90165FULL, 0xF07F75D9374F14A6ULL, 0xF1D195BF04832698ULL, 
            0xFC09EBD3E26097B9ULL, 0xC04BB42B6BC45B54ULL, 0x3BFC7B71E64E58E1ULL, 0xFD591EC172587248ULL, 
            0x414BB2D0B42C6C70ULL, 0x728137595D76CB15ULL, 0xBFA30F231F9B25BDULL, 0x68B608E55FD21424ULL, 
            0x1ADD38DCEC8BF7E5ULL, 0x81B8F6E3E3F3F67CULL, 0x592EE60AA2E123DAULL, 0x9BDDC0DBCED84BB7ULL, 
            0xD83F389176821718ULL, 0x208A0D3EC04950E0ULL, 0x3E96E5E37D0FA152ULL, 0xD014DB6A65B566E5ULL, 
            0x907895C1B130CB4EULL, 0xF63D61092398F3B5ULL, 0x0ADF5E9089FCBF96ULL, 0x11711255BC4DD4C1ULL
        }
    },
    {
        {
            0x20FC0950A389C8D2ULL, 0xA114A7350FAA3ED5ULL, 0x66DEEB0437DF0180ULL, 0x37AD6B94507A5731ULL, 
            0xD5A9AB6F5DB913E6ULL, 0x4E2C22F74ED4BF9DULL, 0x84BC64090B927ED9ULL, 0x1907438D039C113CULL, 
            0x25204DB8173D2898ULL, 0x2609979AA58B677BULL, 0x4427E380E8297438ULL, 0xE041CC8250EB852EULL, 
            0xBB615A41044D303FULL, 0x981E53EF150755A2ULL, 0xE99C1590EB07434AULL, 0x8550D6F15109C1FAULL, 
            0x6EF7503F5595A712ULL, 0xA583FDB712A31107ULL, 0xE2895449FC8A0F80ULL, 0x536B326F7C63DD27ULL, 
            0x45B15542F7D694A3ULL, 0xB1F4D237AD9F9D23ULL, 0x7CEDFEBD6F334976ULL, 0x196E0F61684E0C37ULL, 
            0x421E5BAC22EDE4EDULL, 0x996DACCDC1379F3AULL, 0x9705CE5D8848B2BBULL, 0xB364FE8992633B6DULL, 
            0x35842036C8396D85ULL, 0xF3358F4758A02AA7ULL, 0x81388EA39170E6EAULL, 0xD28214CFF9DF0BE0ULL
        },
        {
            0x64548CF4989D8568ULL, 0xC4A2B44C008A35FDULL, 0x2617F121F72598B4ULL, 0x334EB0A569E717BAULL, 
            0xD05D7DF0900AEBFAULL, 0x04B0A09641FF5A72ULL, 0x4D716832065C9001ULL, 0xB642881159E6B850ULL, 
            0xC14E96933F0C2470ULL, 0xB4848FA9057950A3ULL, 0x0944924CF5EA46FBULL, 0x3DB121FE8A2A6E22ULL, 
            0x332E86391A4FCC03ULL, 0xEB6FCD27B4E0CB51ULL, 0x8DDA88E851C5FA9DULL, 0x14A4808983B18A61ULL, 
            0x577DD725721E9995ULL, 0xC93E55B3FF2048A7ULL, 0xE2657F30B98BBBEBULL, 0x61DDA5053BEC6F89ULL, 
            0x8BA5A90BDA08ED81ULL, 0xAE760570993FA21CULL, 0xFBB2B18D8FF803C2ULL, 0x6BCBD5A3111ECD81ULL, 
            0x92651964E914BDDCULL, 0x82434F8E53CE5BAEULL, 0x206E1EDD66D18F54ULL, 0x894772A19B631EF0ULL, 
            0x8BD1F5B0AACE0EAEULL, 0x585F78BDDEF29E2FULL, 0xD0ADA5B8947FFDB0ULL, 0x118F7CC8FF4FACD1ULL
        },
        {
            0xB5BE73F549DD06D6ULL, 0x898ED7A8A2089789ULL, 0xAD54012F6DC0DEC8ULL, 0x2E7F420416E1F0AFULL, 
            0xFE64B5B15B3FAC38ULL, 0x53E028A2302A3EFBULL, 0xB2CDC7045BC7D189ULL, 0x868188C359DBF8FCULL, 
            0x4C437A31D55BB9E6ULL, 0x1E387AF5B782A5B4ULL, 0xA27AD57A8710D2FBULL, 0x2C5128AD3AEB739EULL, 
            0x2DB5B179C7C12D8BULL, 0xF2478F1D4108ECDCULL, 0x71D281FF195F1A89ULL, 0x7D277FEC7AC19BBCULL, 
            0x5F7B9DB731A9FFE3ULL, 0x1B67BCE51A52BAB4ULL, 0xEC0BD67908B3F7AEULL, 0x1EEAA96F393B6E9DULL, 
            0xFE0FAC3BB7AF8FB9ULL, 0xE58650328E44E490ULL, 0xBF676CBA68B91AA9ULL, 0x398671E6587DC04BULL, 
            0x7A8F1C436EEBFFABULL, 0x7FE2EB305A5E57D1ULL, 0x419D1B6173AC7442ULL, 0x7BE5D6E12FC15F1BULL, 
            0x20B80EAA39B64A7DULL, 0x63816FB6AE8E4D5AULL, 0xC95633413F952411ULL, 0xABBEAD1A5AFAB3ACULL
        },
        {
            0xB9FB6E6E4661A925ULL, 0x757D32096AE66C5EULL, 0x6A8C0274C1B0C123ULL, 0xC5170327D912B861ULL, 
            0xC7DD92B7A1F78398ULL, 0xACBBD1D8CE0AA6A8ULL, 0xEC7659F71E4A4704ULL, 0xDB0C38823F40E4D8ULL, 
            0xB7D9E67E526A25EFULL, 0x33840FAEFA15B1FDULL, 0xABE10AAB63445F52ULL, 0xF135BE038C360FBFULL, 
            0x8B383ACD1B6CA270ULL, 0xDB30CDCDA58C09B6ULL, 0x6256E0AB26AE5B55ULL, 0xA4E4FA18B291A878ULL, 
            0xE841AB5C48254993ULL, 0xC20530AE99642EC6ULL, 0x36FBCC11730D2F91ULL, 0xEFA75B48D5353F5AULL, 
            0x66D796D9FF0826EAULL, 0x2DBC4B7E932977BCULL, 0x44C60F9FB9BD616FULL, 0x1FE6B865A7DFE38EULL, 
            0xE584D163961844AEULL, 0xE80C5249BF2A8F16ULL, 0x5B1C1245F41022E6ULL, 0xFC67D2B8D075251DULL, 
            0x1DE16A2338876115ULL, 0x29928479EF434D62ULL, 0x2DC841DE073F5B61ULL, 0xB2D0580F84D7FFB3ULL
        },
        {
            0x9ED910D83E745E16ULL, 0x6172076F9DCAB75EULL, 0x7EF8F6D67F3A8714ULL, 0xE1C0CFD214BF9025ULL, 
            0x112F98FE99B36DE8ULL, 0x849D73C36A0CC9AAULL, 0x7E2E07CAF22B98FBULL, 0xE802E162FB79FB20ULL, 
            0x5074B334F2DE1413ULL, 0x56021D14703E8735ULL, 0x5DD75CC0221ECAE4ULL, 0x0A2354742E56031BULL, 
            0x3B414E7CA0AEFF3BULL, 0xCE6A2A70A0BB226BULL, 0x42EEB9D0ACBDBF88ULL, 0xBC6991D6D4C7420DULL, 
            0x0BBE3A975D8AFBD3ULL, 0xCB8A12C2E66B2495ULL, 0xFBE2F5338CEA52E2ULL, 0x2453DE102E72D523ULL, 
            0x69A9F88BF997BC0CULL, 0xECC7060D915F745FULL, 0x9C5C7136908F6F92ULL, 0xEB63DE5BB43358ADULL, 
            0x59117A148F796DFFULL, 0xE604E5A476B210E5ULL, 0x93713BED9B9CCFAAULL, 0x8EA1B633C33943CAULL, 
            0x545BF1564C07D207ULL, 0xF597B43900D3B62EULL, 0x1AC3AE60FAC9DEB4ULL, 0x027EF5D00AFFB2CFULL
        },
        {
            0xF8114996A6DA0560ULL, 0x645FA6AFCFD29D31ULL, 0x410186DDBEFED983ULL, 0x9E537576DC1C15BFULL, 
            0x9DEC6C22E746AB6EULL, 0x8CB167374EBE612AULL, 0xB0D2B374E4F63AC5ULL, 0x42FAE87E3E15979EULL, 
            0xA0E3613611BFF9E4ULL, 0x3D1FD693E42F8B8EULL, 0x317106951F896C9DULL, 0x95FA12CA9E35CF6BULL, 
            0xE076358E7F6792B0ULL, 0xE447063787EA40FBULL, 0x4821F71113164C8FULL, 0x570D675EC7F514F7ULL, 
            0xBCB1F92EB105EDF8ULL, 0x1F88809BD5D9DADDULL, 0xFCD8793E21B6D8D7ULL, 0x1D8D0817F46EFB88ULL, 
            0xDC4CEAA6A2E88A26ULL, 0xAE87452E6B40959CULL, 0x08FD56FC8569672CULL, 0xD4A93E001FC58896ULL, 
            0x69B74EF2B24CEBB5ULL, 0x5265BCE0D33F7A8BULL, 0xF27CAE4042A30A24ULL, 0x6C309E37636CD780ULL, 
            0x18C320F8A25CAB4DULL, 0x6CE677845224106FULL, 0xAB823B30452557FBULL, 0x661C02A962709661ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseCConstants = {
    0xD6D9DE93E5E9EA45ULL,
    0xACCBFA6B2B372759ULL,
    0x430EA68BE3AB1CD6ULL,
    0xD6D9DE93E5E9EA45ULL,
    0xACCBFA6B2B372759ULL,
    0x430EA68BE3AB1CD6ULL,
    0xE6391504E1415643ULL,
    0x3333199AC35E47E7ULL,
    0xF0,
    0xF0,
    0x94,
    0xA7,
    0xBA,
    0x64,
    0x36,
    0x40
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseDSalts = {
    {
        {
            0x1BAA5C9EF7CD2B1EULL, 0x7D28FDB8EAC6CDD3ULL, 0xF262B5AB50380DD3ULL, 0x2B6B05D0849BFAE5ULL, 
            0xD105FF3588926086ULL, 0x7A73FC88C56410CFULL, 0x12242F3E38D2734EULL, 0x85C8B5698E211B7BULL, 
            0x6B1810915F63326DULL, 0x4378A61E50A9BC3EULL, 0x2198F9B311B27CAEULL, 0x3097F85AE990BD13ULL, 
            0x05B787C7C6410BFDULL, 0x55C3F41DAFAC1CCFULL, 0xA442E99AA5C2A502ULL, 0x75442BEFBE4EBC68ULL, 
            0xB03DC5381BA50B19ULL, 0x18B4D2767D246C20ULL, 0xBCCA179AD7C18FCBULL, 0x613D6DA8ECEC8D73ULL, 
            0xB860108BF457FE90ULL, 0xA89EB9FC6BE95A34ULL, 0xAD8E2F07261B7028ULL, 0x9B6FAA2577AA48CDULL, 
            0xB00B184DCB03C5C1ULL, 0xEE69CEFC8D6A0A11ULL, 0x28294A7E8C19270EULL, 0x9E00A48B10D815A4ULL, 
            0xC828D974094F82CAULL, 0x65753EC3C3767A7FULL, 0xE4EB01A7EC7557D4ULL, 0x885D96D70AA5D704ULL
        },
        {
            0x969DF8E38D4728F2ULL, 0xFE48F900B8B09BFFULL, 0xAA61E8E34004B682ULL, 0x5E15A4108227C21DULL, 
            0xE0F11C0E3309E90BULL, 0x2FA5D64738577226ULL, 0x3518048F185184E5ULL, 0x402BE9CB9579325AULL, 
            0x7B13051CF2695177ULL, 0x8861CE7D1B4F3F71ULL, 0x99FAE22043B332E6ULL, 0xFD53AA84B6F3B4D9ULL, 
            0x78803ECE9DC8B772ULL, 0xC5152932038E5E35ULL, 0x32768A7C6A0C1243ULL, 0xE8BD5AACA5B1778BULL, 
            0xF55D06785B8FC648ULL, 0xFE93946CB8CADC6FULL, 0xF08ADE6CEB4D6496ULL, 0xE7C565F6BAE7ECA1ULL, 
            0x50ADA0F5DE697BAFULL, 0xD2711229B150338DULL, 0xB51F191DF39FD978ULL, 0x1668A5C0879C4C51ULL, 
            0x85A40F119DF08847ULL, 0x946692D998D59115ULL, 0x20D65943F40B14D8ULL, 0x550B6A84D76BF205ULL, 
            0xE13D9F6462BF273AULL, 0xB217114502356847ULL, 0xD6F1C2F8F7CD7183ULL, 0x4B1BC2A94E7348C4ULL
        },
        {
            0x03CA6F9540D7819BULL, 0xAD286BEDD281C85CULL, 0xE728452D713DA897ULL, 0x4881F39F51AB497FULL, 
            0x6B255015BA5BD920ULL, 0xAB416D99AECEBE90ULL, 0x39600EBDA9DCFF54ULL, 0xE55CAB83C3AB45E4ULL, 
            0x00F0D43F558BF67BULL, 0x06CF639A86BA210FULL, 0x89E55E8074FC2B82ULL, 0x1A8B15A9BA3AC843ULL, 
            0x3882028AB45097F3ULL, 0x6D69204F788CA98EULL, 0x0C92B37561943A5CULL, 0x336D3A6FC72367EEULL, 
            0xD13962B54C22AA10ULL, 0x28CDBDF3E663EE2DULL, 0xBD4B917B94AEDF43ULL, 0x64A1FD559B25C0C1ULL, 
            0x5CE5EC216E00862AULL, 0x3D8BD071984D4944ULL, 0x4953B11FEA551621ULL, 0x734F0A84406C6172ULL, 
            0x24CBBD194D130946ULL, 0x106FFB5C655124D9ULL, 0x8A293B380246FCFBULL, 0x51EBCA3A6DDAA393ULL, 
            0xA977BDC3EC75087AULL, 0x6EAD75785E773B7FULL, 0x29398A1DFF4C32D0ULL, 0x6B4EC2C28F8093E6ULL
        },
        {
            0x1E2EFE8F9FAC3FCEULL, 0x3825969124706712ULL, 0x6E6E21921D9432CCULL, 0xD17481A474E79FB3ULL, 
            0x45A4B94B9202C3EAULL, 0xCA11D2131F235E48ULL, 0x25EEA3FD5E1CBAE5ULL, 0xB478B820E11DDDC9ULL, 
            0xD9B920DDC031B16CULL, 0xE63CC7FA3D1FF7B1ULL, 0x3ED14FCBAC2E5B2EULL, 0xE5AC88F6C18B383EULL, 
            0x08160C31BF433389ULL, 0x44DFB649B0002FDFULL, 0x325501771C4E11B9ULL, 0x142A7295971731EFULL, 
            0xED2B3B077B5963D2ULL, 0xDEA0EADBB7B4E9C5ULL, 0x7B3673866AEFA0ADULL, 0x3A857E56D375D6B3ULL, 
            0xA9953B7F2CEA589EULL, 0x4DC74E990E46E08AULL, 0xF04145224B3A48B8ULL, 0xDAE774B967ADE12BULL, 
            0x493A2B775653D9A6ULL, 0x6A6EE16F80A52596ULL, 0x712D3C44FC4B6EBBULL, 0x653FD5534459DFF0ULL, 
            0x52F82CD330278737ULL, 0x8EA3DB5A98516F41ULL, 0x5AB7BE948D3EF969ULL, 0xDBD8F784AB4AFC4AULL
        },
        {
            0x4F6E6D231E6433EEULL, 0xBF4FF1E83186892FULL, 0xE34933CCC965DD7CULL, 0x76913D8F5C4A938AULL, 
            0xDF5F18B86A6B3A03ULL, 0x7C42EED794839B22ULL, 0xEB8A84BA27D5F051ULL, 0xD29D4D160EB2C661ULL, 
            0x21A2131B96638095ULL, 0x3CEAC2748A5AD77AULL, 0xC915E4A47F75845EULL, 0x2D5CDF2DAA8F9AD9ULL, 
            0xEC29CCA2D583C823ULL, 0x16F93A93C4779E7DULL, 0x8FED626D03188BF1ULL, 0xD46C3A7BEF8B1B64ULL, 
            0x221886FEA4EC82BCULL, 0x105A71EE2C62AB46ULL, 0x531617D7B61243C3ULL, 0xABA70702E86C0268ULL, 
            0x807AFD03639982D0ULL, 0x08C7896F0A648163ULL, 0x4F949B1292705D46ULL, 0xC2864C862D4BF71CULL, 
            0x68135242A10A360FULL, 0x6C896A4673E1087DULL, 0x25A59AD07442568AULL, 0xD2B4A4C6D29B7C04ULL, 
            0xEA7ACF8573BF9730ULL, 0x56735E27F3E34C68ULL, 0xC5FF9B1FEE11F6AAULL, 0x9AEBDFBA3A77BE37ULL
        },
        {
            0xAF53D500AC8F4B3DULL, 0x356892F0678370C5ULL, 0x6F4A03012790FFCCULL, 0x0434CA0D6DDB46F6ULL, 
            0x33090E37991AF6BCULL, 0x30FA79501381D13AULL, 0x4B9D490A994DFADDULL, 0xF4DC1C6DB4841F15ULL, 
            0x72FC178FF35E04D2ULL, 0x8689F9DA45936839ULL, 0xDAC70A76A49816C6ULL, 0x2F11D8DFD37AC246ULL, 
            0x692840A3613306F1ULL, 0x526BD18672EDEC19ULL, 0x741804F546630795ULL, 0xC158B20774EA99F8ULL, 
            0xA8CB0BF1CC6AAA92ULL, 0x5A52F4C2C6F67BDBULL, 0x0E8B42295E302A61ULL, 0xE1A9DE0117B798A5ULL, 
            0x224A48D71E751F9EULL, 0x271B329C1819D2CFULL, 0x8982C607B2A61D5CULL, 0xF8B1F10834B3076FULL, 
            0xFDD1939E66D1F919ULL, 0x0587DF7821F2762DULL, 0x9DDACB2E576AAB50ULL, 0xE4CF4A17D994A46EULL, 
            0xF2005010074A843FULL, 0x201EC8DAEF203736ULL, 0x9E65C5D99D652E6BULL, 0x44C4BA5393631A0AULL
        }
    },
    {
        {
            0x546CC3C52897CD01ULL, 0xA25FA370875AD913ULL, 0x470816B4F36683FDULL, 0x278194272536E299ULL, 
            0xB742BB721F74C169ULL, 0xD00365C2DACAF989ULL, 0x21CC47A012595BD5ULL, 0x83BB663559842512ULL, 
            0x28DCAA2ED9853826ULL, 0x70B238ED438170B4ULL, 0x7F6E8E00FCD646B4ULL, 0x7B76B16D23345A62ULL, 
            0xC0C65E9B1FC6B51BULL, 0xCF78598093A6CA91ULL, 0x63085FF8BE5DF4F7ULL, 0x9637DA1220855E17ULL, 
            0xCD1417FFF7133922ULL, 0x7861552D99A5E6F6ULL, 0x46B436ABFF316851ULL, 0x1B0FF8920BFD5793ULL, 
            0xBBCAA7B6795F0434ULL, 0x26013BC626DA9273ULL, 0xF5960A208BDDF60BULL, 0x640835C14B8EED55ULL, 
            0x9B40391D5BF224F0ULL, 0x57CEDB784A11D998ULL, 0x809B565162479432ULL, 0x48EAD802FFFD234DULL, 
            0xF03F886D217E5E1BULL, 0x39CE5BFA212925C0ULL, 0xA8F875A18DFB95DDULL, 0x1EBA9E6ED15520A1ULL
        },
        {
            0x5C8167FC92BBEB37ULL, 0x71AD0726A2F51DAEULL, 0x93362BB0CFB6837EULL, 0xB1C32471C83F087DULL, 
            0x2010F0204C9DD58EULL, 0x5500D02B0F9CA05AULL, 0x17333A502726BCC3ULL, 0xAFFB3DEC59E07BC9ULL, 
            0xEB72112BA1992F8BULL, 0x957007E752D50374ULL, 0x6DE3FF756E09EAF8ULL, 0xEC88552AA62C5137ULL, 
            0xAF4BE83B3681488EULL, 0x8936EAE69B926841ULL, 0x3078F72E366FFEDCULL, 0x9B10A747DF44C623ULL, 
            0xF3F46213BF3D53FBULL, 0xA47536B820961D34ULL, 0x293BD1C1720988D2ULL, 0x654CB450383FC407ULL, 
            0x58B5E3592A5BE429ULL, 0xA375ED342066B06EULL, 0x782470EEA0174E82ULL, 0xF988D3540ADD79EAULL, 
            0xE07A9A21BC0A7E3DULL, 0xBC7EEC237C46F9F5ULL, 0x89695CE41D6331AEULL, 0x6F5CF6A998EAB33AULL, 
            0x79E1DD21F290F35FULL, 0x9EC558D5C7B1A96BULL, 0x491F962D3DD85B17ULL, 0x5733A083C524F452ULL
        },
        {
            0xBB78D06BDA1814A3ULL, 0xB97E791AE4558839ULL, 0xF32A984462751C62ULL, 0xAE20D15E012D4F33ULL, 
            0xA96756F171B9EF4BULL, 0x2DCA4D1DCA4FC443ULL, 0x1A7A7E6C41F30E1AULL, 0x25CFB9FA72D9D95AULL, 
            0xE8468BFFE5A87B29ULL, 0xF07D16EC7C147E55ULL, 0x822D6EBE66DD2E4DULL, 0xE361997F1D72305FULL, 
            0xD573580F02A1D99EULL, 0x89A7AA08AD8527C5ULL, 0x2C4E49E6DCBFF354ULL, 0xD4B7195C7FDBF202ULL, 
            0x5A4E85E5B1A1579EULL, 0x3201B28572519330ULL, 0x694CF03939B7305BULL, 0x064CF5479BF27EE6ULL, 
            0x2807FFFA25BFBA20ULL, 0x19D415905B6013D8ULL, 0x3AFA05191EAA58A6ULL, 0x8105F460EE990155ULL, 
            0x5D3280B757615F9EULL, 0x0A86BB3E914B5C8EULL, 0xDC21CE7F7B0F025AULL, 0x122BBF665C04E822ULL, 
            0x256329DD78401355ULL, 0xE3092CCFC10B5DFAULL, 0x0031D77BB240A5E8ULL, 0xE42BE0C61AD06FC5ULL
        },
        {
            0x0457C134AAB5EEF3ULL, 0xAC578498E1FDAAA3ULL, 0x78C612044BE6482CULL, 0x4DBB5BC7C4BFFF88ULL, 
            0x5CBBA8ED4BD1F140ULL, 0x5565E26F9EE5238FULL, 0xD7550A7EBC99A1F1ULL, 0xA05A3A40A7F76A8AULL, 
            0x112DA2F1549444A2ULL, 0xC481297FA4E912FEULL, 0x1E291869AE42F9B3ULL, 0xEDDE8EBE0AC52580ULL, 
            0x14B34AB9BB3DED9FULL, 0x601E342EA675839FULL, 0x40AEA6B9B69633E9ULL, 0x30684F1F120A183AULL, 
            0xB928F0315008001CULL, 0x3F9C631EC283ED04ULL, 0xBEEF5D8D19CF87B9ULL, 0xFCD39CEDC9FF3323ULL, 
            0x8DEDEB46443EA741ULL, 0xBDC25CF1C02135D0ULL, 0x57287A8B2F6B5FFCULL, 0x6FBF515FACA895F1ULL, 
            0x3D7B5933DD9EECF4ULL, 0xEA98FAA0E989F61AULL, 0x46B9E6B746C88D69ULL, 0x6E50DC363CB400B9ULL, 
            0xE7761B2B63611EAEULL, 0x2E98CB903F1534FFULL, 0xAA87C0EB5622F056ULL, 0xD7106F72BB0F596DULL
        },
        {
            0x1BF9B96019A7BE1DULL, 0x8FE2BFBA0FB05E47ULL, 0xB3CD6031D355CDB3ULL, 0x17079EE74DF9A4E1ULL, 
            0xD2CA20FC044781D5ULL, 0x93E0F41EAE819C59ULL, 0xE35F32C211F13D3DULL, 0xB22E01E0664FD814ULL, 
            0xA28B281620679B33ULL, 0xC83CDCDD51F57AADULL, 0x80C7E13827FDD0E2ULL, 0x096E296BD1B74BE1ULL, 
            0x0D268F2AC408E743ULL, 0xB9A4490FE71216BCULL, 0xD92CCE0BEA6E77B3ULL, 0x2D4DE1E6E661C511ULL, 
            0x2A572E289EC2CA1CULL, 0xA9F56D93722291C4ULL, 0x0B3E19D4CE5E7105ULL, 0xC1F6ED8E02ADC4D4ULL, 
            0xC14A983825D5CE08ULL, 0x25598A6459D8B891ULL, 0xDD8F810269F8B594ULL, 0x7B8D2A8A9D9D47FCULL, 
            0xF1B3A15278799563ULL, 0xD4D93C611D16EC4DULL, 0xCEB1ADDD0CFF6232ULL, 0x6171CC051BAB66BCULL, 
            0xBEF6A8F0AD841D4FULL, 0xDBA7913C56829084ULL, 0x6C3431F4285B90FBULL, 0xA2B6D8796896F4E0ULL
        },
        {
            0xFFC6A7BBC720BFBEULL, 0xF36DB5B8F3C077A2ULL, 0x50FDC4C441BE0502ULL, 0xADBFDA54DC472C8EULL, 
            0xA34F46AFA8F5A82FULL, 0xEDD0DC8430B72B87ULL, 0xFEA6E68EF6BAC251ULL, 0x88938901CE2A7917ULL, 
            0x89356CF600C49019ULL, 0x035A1D884D862123ULL, 0x37B6E9495194E4F5ULL, 0xEDD92401DE48A2FDULL, 
            0x3DBC0956A56C0A8BULL, 0xDA3D77EC49CD61F1ULL, 0x139DCE949F647FCDULL, 0x3B7DB72ADD982FD0ULL, 
            0xB21CF38852BD4296ULL, 0x781C275C63597267ULL, 0xB31076F36E3C9BD8ULL, 0x05C0A874D1062AE0ULL, 
            0x658FE9B9857E239FULL, 0x445A2A57E2039CC2ULL, 0x4CE059D928A75081ULL, 0x4155AF11143AA81AULL, 
            0x660CA5C34D112091ULL, 0xFB885E1C65A856F8ULL, 0x75424B4E27FC54D6ULL, 0x6D8DCB253C159976ULL, 
            0x413229705A50ADB5ULL, 0x0F6E642C0DEEF965ULL, 0x09D5FD37FAADB780ULL, 0x8C5E563F3D5FC435ULL
        }
    },
    {
        {
            0x274665283B21028FULL, 0xDEBCC1BC620E640CULL, 0xBF79F7C65E74192AULL, 0xDCF7455A416B03F0ULL, 
            0x59A1B08C9E46B66CULL, 0x7063B2E420BD4C64ULL, 0xB81C1D6206001469ULL, 0xBC1272E4B8C1F83FULL, 
            0x23D2AFD6B3E94915ULL, 0xB772B6A8E9F3B38EULL, 0x5261DCFEEEF66B27ULL, 0x75987679B652C892ULL, 
            0x3C09B0C6D997E8BCULL, 0x1FF175B9206CD405ULL, 0x53895C77E2EE183EULL, 0xDE2B955003AB6891ULL, 
            0x9E3050EA42C847D4ULL, 0xFFF12FD2D5200FD3ULL, 0x2F5A04F7E0F7B62EULL, 0xB667F1EA501B1E7BULL, 
            0x41572C8F6D09BE37ULL, 0x2F14D1D0D8BF15A7ULL, 0x63AE7C9680454B9DULL, 0xC33C3046CAE8C189ULL, 
            0xC18A05DF880B809FULL, 0xA8B00AD1B9DE3FE1ULL, 0xED1D71BEACC822EEULL, 0x2B4241483239C3F0ULL, 
            0x043D0682D673A2C4ULL, 0x35CBDBB78A9E0EB8ULL, 0x2FC402591D1762DEULL, 0xF3BE07499270A7B4ULL
        },
        {
            0x2FB9A7D2894262D0ULL, 0x060E44E7EBD796CAULL, 0x8A795A29564D3311ULL, 0xE102B2B5A355C8B4ULL, 
            0x06B45D1905087050ULL, 0x53D968DDE8689E50ULL, 0x632B00CCC4051B8AULL, 0xF22EC7B9B7F2A54EULL, 
            0xEEBF54D38A128CBCULL, 0x1102650B6B59AA71ULL, 0xF0B85726C6A0EA2EULL, 0x545B74596CA0045BULL, 
            0xB57935268DE6A9F4ULL, 0x6A5EECA23C2CBA7BULL, 0x0F20213FA6BF4441ULL, 0x4E86F32541AE0CE9ULL, 
            0x8B0AB80BA705AE54ULL, 0x7076E3E13897CAE9ULL, 0x16A996DCA70083A5ULL, 0x81607318D8CCFE0FULL, 
            0xB9099BB7B2D0B57CULL, 0xBC3C8F0540A3D0DFULL, 0xFA112A6EEF962D4EULL, 0xC7610EDE4F068A8EULL, 
            0xF6B5F8533B5952E9ULL, 0x27CF3AAF44625A62ULL, 0x761852420F16CAB5ULL, 0xC18436FC91C41948ULL, 
            0xC7E182311923460FULL, 0x7F434F267F4903A8ULL, 0x51C6328741CFED87ULL, 0x3541707D62F0A444ULL
        },
        {
            0xEC49024522A71D75ULL, 0x4E2EA5C6C0107FB7ULL, 0x72CDAB92342ECA4BULL, 0xBBD4294F8D2F5BDEULL, 
            0x7A5B8C2101B6A1A9ULL, 0x713EE35DFC66C0F0ULL, 0x5C526149A0370A68ULL, 0xF2C2BFA92BF7F8E1ULL, 
            0x4FB4701C6E5C2F0CULL, 0x7A0B61CF2B9BD286ULL, 0x6BF6ADA1755FE369ULL, 0x4DDA89FACEB48604ULL, 
            0xBEBEA512CD6F0A1BULL, 0x74B4BB71FBFD4489ULL, 0x930F76DCA4077524ULL, 0x80636BE231553BBFULL, 
            0xA9024593BB5CD778ULL, 0x29D5A52108486E52ULL, 0xFA97FE68A21DE336ULL, 0x916A6B1D7EC9E224ULL, 
            0x642F3D3FF35ACE15ULL, 0xFEB5B1A0AB0C7745ULL, 0xC6D5F15CA6A4D749ULL, 0xFF951527F6A6742CULL, 
            0x19B63A4C215D8BA6ULL, 0x759E8006559270E1ULL, 0x8B4F27E77D8E4BADULL, 0x2592F8841982A15CULL, 
            0x230EA26A3EA1CA75ULL, 0xD9202B4AF75F25BBULL, 0x292EB15AD8670F63ULL, 0x9A94D65788CB93CFULL
        },
        {
            0xE246FF9A3E28A2F0ULL, 0x7EEBD8E8F7C3DCEEULL, 0x09EF289C2F1E1F76ULL, 0x9101EB737F69A818ULL, 
            0x203309C1D4D85281ULL, 0xE83706465EFF8280ULL, 0xB8C9322B5C167AF8ULL, 0x0B57A1FF4B58692CULL, 
            0x9ABF160A185752C9ULL, 0x51A5A6F1387EA5D3ULL, 0xB64DED828E14AF60ULL, 0x46ECD21292D59F07ULL, 
            0xC4E73A7EE47C21BEULL, 0x3815A8CA049C2008ULL, 0xB8AEE82BDA97FAD8ULL, 0x46101FD9C1F92B18ULL, 
            0x479DBA2B82C0D126ULL, 0xB4AD1675FB147412ULL, 0x6C7702C312E3A130ULL, 0x8BD340418B14CDF9ULL, 
            0x131DA91FE923B9FFULL, 0xD4BD9F47FF7A23DAULL, 0x8EF837A23D7E3D2AULL, 0x71CF2A403B566257ULL, 
            0x4CA1B52CDC53B61AULL, 0xE410E81278FA4540ULL, 0xF0C8ABC0729A6B49ULL, 0x5D123F6EDB4FE7EEULL, 
            0x52B12A787D6656B4ULL, 0xD1D75946CDD97016ULL, 0x9486B21BF2EB6AC3ULL, 0x2A425D073AD8EA47ULL
        },
        {
            0xFC94CAFD51FE2ED0ULL, 0xD10BE6D8DA40A0B2ULL, 0x3D15FAB0FB189DD2ULL, 0x8D58D3B7B46ED283ULL, 
            0xBF98F88833504944ULL, 0xEA948EE7549CFA4EULL, 0x543551E9386AA920ULL, 0x21B9DAA320727DCDULL, 
            0xFD68EB8364F70551ULL, 0x4A0E70328267F3CCULL, 0x338DDF7A8F14274BULL, 0xCE33E2EDF7011F3DULL, 
            0x1420701E3A948D7DULL, 0x6A13263726C8E5A2ULL, 0x88FC69120F852D8AULL, 0xE8CAD87BFCCCD43CULL, 
            0xC01081DCF4571BEAULL, 0x1DC1EB2D690C93A6ULL, 0x34A547C328DBC842ULL, 0x32A61DAB7C6C76BCULL, 
            0x22591D78555C71F0ULL, 0x8021486EF4C8110FULL, 0x5F51EF2E60EE26F4ULL, 0xC8FFEC07622C55A0ULL, 
            0x5321174E616EFA70ULL, 0xE4FF452B54DD855AULL, 0x233427DA89AD4B3CULL, 0x73503209BDDAFB17ULL, 
            0xF5C08CB69A9281B2ULL, 0xC5417836DF7043B1ULL, 0x5F0F74F385DB1390ULL, 0x3C0438BF5F59972AULL
        },
        {
            0xBF50C99ABB13D99EULL, 0xBA5980DF767208A1ULL, 0x93087B9ED77F515EULL, 0x89B87B5C717E4716ULL, 
            0xDE854AFDE2E04CCEULL, 0x572CF33D33BC1BCDULL, 0x0EC9D7B631E7C9FDULL, 0x612F68C51606DA93ULL, 
            0x77EF9844CD379751ULL, 0x543F90AD540B20C3ULL, 0xF1CA3CB709BBF82FULL, 0x14B4EA91836770BDULL, 
            0xAC672362CED231B0ULL, 0xE4194BFC6282D156ULL, 0x587B16C0FCF0FBA1ULL, 0xBA59FDC012BD2ED6ULL, 
            0x817F1A3F41A42BD9ULL, 0x802BA5B16F32E4D9ULL, 0x07E5D89FECEE700FULL, 0xF087BC76700BD1CFULL, 
            0xB71BF4708FF97DEEULL, 0x76E1946A31E42280ULL, 0x0B078F41102EB2A0ULL, 0x92C0BEFA33D07DD3ULL, 
            0xA1237D135BD06FC0ULL, 0x9B76BFD52FCBE9EDULL, 0x562338641D5B5748ULL, 0x4880BA551715F8CEULL, 
            0x4AA11CB50353D355ULL, 0x9E1745B76ABFB0E6ULL, 0xA79DAE34B79BD6AEULL, 0xDF8AEBA3006F973EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseDConstants = {
    0xE4729CD95768E1CAULL,
    0xD2855FDC61BC6D54ULL,
    0x360FEDEA5CACBA43ULL,
    0xE4729CD95768E1CAULL,
    0xD2855FDC61BC6D54ULL,
    0x360FEDEA5CACBA43ULL,
    0x17D245B70E7A0AD1ULL,
    0x02D8D6C708DCCF51ULL,
    0x84,
    0xD3,
    0xA7,
    0x9F,
    0x46,
    0x7F,
    0xC3,
    0x23
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseESalts = {
    {
        {
            0xE7413B52E105DA8DULL, 0x7E9FD884B6341A5CULL, 0x55AA8472A5130C1EULL, 0x942C27CFFA37F98EULL, 
            0x63FD78606C640ACCULL, 0x2CFC293B6B852FBAULL, 0xA98367C1AD4C9796ULL, 0xDE3E317F3C3F97DAULL, 
            0x5FD52DCAB8B3A0D8ULL, 0xB32E30C90B137CB8ULL, 0x1B0DCB2E3DEA2569ULL, 0x77270E5D9C7D5E29ULL, 
            0x1C8DA8B7C1976C3DULL, 0xE6A1C213096B4886ULL, 0x8520387053E4609EULL, 0xACD9D05E02A018CDULL, 
            0xE415A169D3A9B5FDULL, 0xE7D8E3ECA1855CB5ULL, 0x4C6BD76F2ED18235ULL, 0xC1EDE8F8E15A3D26ULL, 
            0xFB33E1B324A0CC55ULL, 0x1315B95DB62678CCULL, 0x40B4143104C8DB00ULL, 0xEF63D8C4413204E4ULL, 
            0x66A1E3531D0666D0ULL, 0x0C824BEF2B5DB4F7ULL, 0xD3E945252C800991ULL, 0x93E34A4B9F47433CULL, 
            0x04DBC9C8AF016240ULL, 0x935F394948C3B938ULL, 0xF81E8123F1C22C49ULL, 0x290D6BC0B4482310ULL
        },
        {
            0x6B2891CF60D216ACULL, 0x51EF4C69E61C42D5ULL, 0xF306C7C890A0CC23ULL, 0x601FEC2A5C5E28CFULL, 
            0x46FA81160D3DC924ULL, 0x9AD2950286A4AE6BULL, 0x80845C03EF24BC32ULL, 0x6CD89285DD96DD71ULL, 
            0x3EAAAD23A6D2DBB5ULL, 0x0D2EB2A8BD30386AULL, 0x9FC603FFAE447005ULL, 0x5FE9C9F69060D8CAULL, 
            0xBB0E8862A19A9B4CULL, 0x78520B47B02F657EULL, 0x9C1890D1085F67BBULL, 0x970C10B064B82915ULL, 
            0x3E144712BE3DF8BFULL, 0x4771204B62582281ULL, 0xE7B6C979BCAD07EBULL, 0x716E145506DDA81BULL, 
            0x0A0832D39B6DDF4BULL, 0x036B7C683B5B2300ULL, 0x53027461F6ACF270ULL, 0x789894792F545A8DULL, 
            0xAD2FEEA4DE88D074ULL, 0xE1F867614F625754ULL, 0xA02E509CCC206EB7ULL, 0x41238CE148087707ULL, 
            0xF440E12AEA00980BULL, 0x76DF729E3C1D34BAULL, 0xBD98F4EEBB047F92ULL, 0x03FA5B0E166E3D80ULL
        },
        {
            0x5E5D8D09C5A9F540ULL, 0x592A8DFD23D76644ULL, 0x2381C8C4D3AE9BB3ULL, 0xB29B6CA7F0A97BDCULL, 
            0x96C51EF2771EF419ULL, 0x7EC0AD66C2D217B3ULL, 0xF96A6A428344F01EULL, 0xB7C79CE0356A8618ULL, 
            0xE9C473B1D969A92FULL, 0x628AA6ADE7C60E45ULL, 0xE42FBD2DD155D187ULL, 0x9180361777312B4DULL, 
            0x9B43D222868CC333ULL, 0x82EC8B468F3B9B25ULL, 0xA47E7D7755D27F53ULL, 0xB69B5C8D4DDFD023ULL, 
            0x78FB1B9974BF28D9ULL, 0x564FA4C36867A6F2ULL, 0x130CBFEB0A9FB3B7ULL, 0x008EE2B7AE97AAE5ULL, 
            0xA568B9FC5C272F99ULL, 0xA263F471488F3D82ULL, 0x2BCCF111DB9F2E8CULL, 0xA936591101531279ULL, 
            0x656FFE001DF899B6ULL, 0x674AEE2ACFC726D6ULL, 0x149B7BE9AED4173AULL, 0xEB56A4718D20DECFULL, 
            0xF884F74D8A06D5DFULL, 0xEB8FC8B8DB28F0E2ULL, 0x1BF017031E7B280AULL, 0x7AE094748970E0E3ULL
        },
        {
            0x06D2CC848C71E77EULL, 0x454A81AA14855AFBULL, 0xA9C38BE5F998EB35ULL, 0xFFE20D3DAB7BCBC7ULL, 
            0x5E8EFCE7081B047DULL, 0xF6E4F62500151A60ULL, 0xF13FBB372C236638ULL, 0xE31100DB19A80189ULL, 
            0x86D83501A26BE1FFULL, 0xFAF78935ADE8CE99ULL, 0xACA181B085DC9DE8ULL, 0xE6110F1C2D6881E3ULL, 
            0xFE99FDB23F776A1FULL, 0xBADDDAE8F7607163ULL, 0x879F48DB9E54B4F7ULL, 0x1836D44D0117DBCBULL, 
            0x9FBFDB60226B2EF7ULL, 0x15B5E8F88E9311A5ULL, 0x3CABA5B0FF3BB6BBULL, 0x6A9C7D6BE8244FACULL, 
            0x5A23C9D3D218342BULL, 0x5CA95E02D678E6FBULL, 0xD7999F2763AC0FD7ULL, 0x4F0E60BC8FA5F715ULL, 
            0xF36A88BB9E969E3BULL, 0xE7F3FCE86F142BA4ULL, 0x48CA53AFC62820A6ULL, 0x989EACD24DD5B4C9ULL, 
            0xB899CBEB265A3F3DULL, 0xCA20CC32D34CDB8CULL, 0x7DD89BF58FCA9BB8ULL, 0x976720F8DC277EADULL
        },
        {
            0x82D945A577D278C0ULL, 0x9B9C592DB917582EULL, 0x8FE939D540DF7753ULL, 0xB9426B42B74C3EE5ULL, 
            0x313426284E384197ULL, 0x4572BA5D855DA73EULL, 0x32FF3E0DB880887DULL, 0xE598DBD0E7CD0D61ULL, 
            0x5AD6A6F0453585BEULL, 0x0F2D50B3C09A4E8CULL, 0x16DFE0F2EB2B4C06ULL, 0x469974E007B7C7F1ULL, 
            0xF8DBE46E94C344B6ULL, 0x257A2A5CB6F4C77EULL, 0xF76FCDA00FBC3A50ULL, 0x52622A4C97FF8A63ULL, 
            0x36DC96EB2E51DADFULL, 0xC6B950157E358F34ULL, 0x35E5B5EF5C739F4EULL, 0x570ED0E35DDA833DULL, 
            0xE166F05F445DB624ULL, 0xC148B95A2B9D9949ULL, 0x97279F948BA8CEA4ULL, 0xEDBBCCDFBEB84930ULL, 
            0x01BE2CA284C04F5AULL, 0x043ECE2EF9C04243ULL, 0x0B3BECDDDF67C280ULL, 0xEF365424155D39DDULL, 
            0xB1DD8092DBA2C2BEULL, 0xE5BEEF69FB1BBF79ULL, 0x9B27CB47B3D13B2AULL, 0xFB064464BF25BA1FULL
        },
        {
            0xEC24021819D2DF3DULL, 0xEA42E28F3D7DDF51ULL, 0x8D38D139539E8525ULL, 0x8819622DBFD4F0B1ULL, 
            0xCEACAA1072A5CFD3ULL, 0xCBF42C9632F24FA6ULL, 0x198A28325477121EULL, 0x945EEC1EDDC830A4ULL, 
            0x83C0F659FBF88C8BULL, 0x969329EB6C07A696ULL, 0x85A4CAE9E20CF2B7ULL, 0xF4E30546CC212200ULL, 
            0x3C15CDFD2EF3D615ULL, 0xE5E4F5653FD0F415ULL, 0x3AD0D06F6C50A78FULL, 0x7D3BEBE3797E9B1BULL, 
            0xDD1E39E88BD454A6ULL, 0xFEF211B8F7D0ED6CULL, 0xF72C2FD08B4EBFC0ULL, 0x44231C5D5A8D6142ULL, 
            0x37E39371665A61AAULL, 0xDFB243FC14548854ULL, 0xC305603664F4DE97ULL, 0x6ABC0050B2001188ULL, 
            0x127B5B57C801207FULL, 0x1F94B7F9DA826493ULL, 0x36B80D51237DEC50ULL, 0x78646A5F569D7795ULL, 
            0xA6B361C2611A2A53ULL, 0x403EA17E1B37DCBAULL, 0xF6F9579946E2C290ULL, 0x7D038FEDCE6668A1ULL
        }
    },
    {
        {
            0x179DF0C3B79F7FC5ULL, 0xC181C9FB9E7E27D0ULL, 0x26C1E7272723BC94ULL, 0xFD99C69D637623EDULL, 
            0x494BBCBCF32B0DA3ULL, 0xAE0C9CA0003E74EFULL, 0xFE97018A039B3212ULL, 0x1532F31588A1F2E7ULL, 
            0x7AFF7BEC13AA09EDULL, 0xB4FFB90C8C361A08ULL, 0x773009787BC18EAAULL, 0x4A3C707090A16E96ULL, 
            0x2368D9665AFC230CULL, 0x6345EDE1016CD7D1ULL, 0xF33523F3A2D1229FULL, 0x0405D675853ECE6DULL, 
            0x99A9B8A537933EBAULL, 0x63F4C1E8ED17AC64ULL, 0xAFC7D0197D330EDFULL, 0x883F5610D7AE0477ULL, 
            0x9235E7FAB5749BE7ULL, 0x8B693A9F94A05162ULL, 0xFA2934C71E3127ABULL, 0xD338523D72423926ULL, 
            0xE4D6C5C18E2F7E00ULL, 0xDA1DFEA40F0307E2ULL, 0x274EC56EE76B5C69ULL, 0xBE177B5FD59CDB2BULL, 
            0x852E6675F6C158A1ULL, 0xFDABC418D5C797CAULL, 0xA91565AD835A6293ULL, 0xBE27AAC84C9D0C64ULL
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
            0xF36D7A767A619230ULL, 0x43912FFA077F181AULL, 0xD73088A0BEA15F3BULL, 0x5E6CD1FC1F1F09D5ULL, 
            0x5593284E20AE41F8ULL, 0x6661E1D41B124567ULL, 0xC3ACB0202A454361ULL, 0x1999017DA510B43EULL, 
            0xD83670FBD1890BE7ULL, 0xFCBE1F563FCD276DULL, 0xD9348F661914B312ULL, 0x202FA5BFEF5895D8ULL, 
            0xD51F44654166CD1AULL, 0xA6E9AA124D1E5828ULL, 0xB153856F216EF546ULL, 0x497918EE08E91325ULL, 
            0xE930C9D327C700AFULL, 0x3C0D24E5C7A90D6CULL, 0x10ABBD92C65A1F3FULL, 0x21BA6F8AA3B5B349ULL, 
            0xDF9BBCF7770DC7D5ULL, 0xBAAB67172F393266ULL, 0xACF28D4995631096ULL, 0x50D42FFCC1A467CEULL, 
            0xFD52D7613AB83E89ULL, 0xA613D95789B5C21DULL, 0x179167168E6C24EFULL, 0x8C3D6DF1598C41D4ULL, 
            0x9712769B6C878448ULL, 0xFB5EE2E727B8A9F8ULL, 0x4D90DAC2F1911E93ULL, 0x469C6202EBFC9403ULL
        },
        {
            0x80E7195504790ED5ULL, 0x9F6ECC89382991C3ULL, 0xD08B76E0CEFCB942ULL, 0x109A622452439172ULL, 
            0x18D0F08498394F5BULL, 0xA43DB89260A5F0FAULL, 0x4E9D94664AFCD966ULL, 0x2639895E607021C1ULL, 
            0xEC0A1440D630AB7CULL, 0x1806A932376978E8ULL, 0xB4A3456A552809A0ULL, 0xE76C7A025E1F7087ULL, 
            0x9ACB7931F5F3D2C7ULL, 0x53A00CF4C07D4710ULL, 0x5712FF695431965AULL, 0xCBC50333E4D3B073ULL, 
            0xF5786A8141DCA892ULL, 0xD3FE7C30AFD27445ULL, 0x29D53F3A62FF6D64ULL, 0xED783EC54F87F308ULL, 
            0x26D135D16B0C3CADULL, 0x9E2990427A0290B1ULL, 0x7AFA76D7D6E5C45BULL, 0xBDB186C20598F2CDULL, 
            0x7C3B64D4767DD31CULL, 0x6462CA38EE456F6CULL, 0xA90AE02122A93F2CULL, 0x84D28979D9E99BCCULL, 
            0x9E33BDECB20F5911ULL, 0x6FE66B40D2744983ULL, 0x21EA46EE83C05A77ULL, 0x4E954282EFE33382ULL
        },
        {
            0x6B9DDC7566561ECEULL, 0xB05A9149AF5B40BEULL, 0x0CB6A56132F9065AULL, 0x79B7F055CDF6545AULL, 
            0x8EE3FA883E36C5A6ULL, 0x1847C9F4FC6063E2ULL, 0x70F76A16EA94AC1FULL, 0xD741098F04C9E2A3ULL, 
            0x1E53DE89E057EC34ULL, 0xCFC421FC1CCADB27ULL, 0x200F02060B668E2BULL, 0x241F7EC7437B3164ULL, 
            0xE53CB26C91198CEDULL, 0x009595FE16344817ULL, 0x9718F4828082B81AULL, 0xBB97B6A7D29C6D04ULL, 
            0xEA611C334ADD65EFULL, 0x19443C0684161981ULL, 0xCD57D0B032972342ULL, 0x79618C8E04A0327BULL, 
            0xBC308B9923798F4FULL, 0xF07B0ED02A393270ULL, 0x80AC360B593E2453ULL, 0xCF5F6F4DE96B5D7EULL, 
            0x518BBF22108E5ECAULL, 0x957747EB6461D94FULL, 0x17251F0F026040DFULL, 0xABEAD504CAA93ADEULL, 
            0x267BB5869CAFB020ULL, 0xD56CCB7CF9048AA0ULL, 0x8CA32D30AA075C96ULL, 0xE59A04C6D03D4031ULL
        },
        {
            0x764B66494CA83865ULL, 0xB53D99EB163E9E52ULL, 0x1210F38A701253E2ULL, 0x77F40756C219F5CFULL, 
            0xA38AAAB16D4D8EA6ULL, 0x4832013E4D0E5FFAULL, 0x7FDCAC21E0775ECEULL, 0xDD593595CEC30B77ULL, 
            0xF4506521F5F2B660ULL, 0xC02D926BA12394F4ULL, 0x213DEA546A88250DULL, 0x2C9B327780612547ULL, 
            0x46AB3E3BDA9ADDADULL, 0x93CDB7839C2A5D05ULL, 0xDA00248A980D271FULL, 0x7C27FF95FB56D857ULL, 
            0x5DF79F2CD74DEF09ULL, 0x8C3C19460000124AULL, 0x865D66FA308225A3ULL, 0x90A13C259990C846ULL, 
            0x249BCF428B80F2A5ULL, 0xC463468AEDB2512DULL, 0x8DBD955714E665DBULL, 0x7354C6478FC8F43BULL, 
            0xE432100325DC39F8ULL, 0x4DE8A0B40FBDF555ULL, 0xC3760CE430C61EA7ULL, 0x09AD04D5BAAB2524ULL, 
            0x7CC2A095BF28D4E8ULL, 0x92840B94233DF7D3ULL, 0x48C53525B6C0DD76ULL, 0x719242ADC0252550ULL
        }
    },
    {
        {
            0x2B03C4C64AB32F81ULL, 0x6DEC4F1475ADC385ULL, 0x17EE2E45F0D19FC3ULL, 0x0E399DF1D2A82AC5ULL, 
            0x6178A33B730E5B1AULL, 0xF25C620D27953070ULL, 0xE9E9A80780C103BEULL, 0xE6DE5D7C19156DADULL, 
            0xAE0F3215D1732909ULL, 0xCB1D1A474F50A37BULL, 0xBF14985AEC32DA4BULL, 0x34C3695013B3729AULL, 
            0x62170DB49ADDEC4DULL, 0x25D3C05370F68AB9ULL, 0x78BD3CFFA0BC68E1ULL, 0x5277FA6DE02CEE0AULL, 
            0x0BC74EABC68B7649ULL, 0xDA70B4C86B52318AULL, 0x7097296911565F12ULL, 0x55677B5A39880ACBULL, 
            0x9EDCAC1BC2DE4D3AULL, 0x4CFD514208119A44ULL, 0xF1E585040B8B1F39ULL, 0xA7CF3BF2D12FB508ULL, 
            0xA74B062A724FB59BULL, 0x84463E2BDE6E11B2ULL, 0x8DBA4CDEC225FC03ULL, 0x5E0D8586D009E7EDULL, 
            0x6F0F2C379F010C3CULL, 0xB9220A9CF6E38F13ULL, 0xCF85ECC40FA47E7FULL, 0x41E42F9720AD4B2DULL
        },
        {
            0xC09962FD48615EFAULL, 0x0C208A9A5F3AD578ULL, 0x590F21386FE4CE6AULL, 0x816FEC995FA637BFULL, 
            0x64B9B21F3170CEB8ULL, 0xCB4762F28409E004ULL, 0x72C21730CEE26682ULL, 0xB5CEA5ABE2771CC0ULL, 
            0x156BD3E44054B57BULL, 0xA2B107D6FD03C5E2ULL, 0x87CFF852E527076DULL, 0xADE65AA20A8BB917ULL, 
            0xA697043B9B7BA7BCULL, 0xBD180D7271C51651ULL, 0xEFFA176410FDEB0CULL, 0x40DE1E4C19C1778CULL, 
            0x2232A7EC91BBA6BCULL, 0x2EAD445E0FD4D6D8ULL, 0x7FA42A8A8BE5B5A7ULL, 0xBB938E3350546570ULL, 
            0x1C9D41F4B701E51FULL, 0xAFFA0A14B98247A4ULL, 0xFA2140A9CA80CB61ULL, 0x0F7866170511EFA2ULL, 
            0x56F73EE1439EDF3CULL, 0x2A6113CE48E72A51ULL, 0x8CF87D574A0038B6ULL, 0x9792F0E486BB5887ULL, 
            0x5D1841A9DC0148DBULL, 0xA3951470E902CAA9ULL, 0x7C832C78359C452CULL, 0x65B54A90825AB9BCULL
        },
        {
            0x40DA50FF005401A3ULL, 0xE5C0261676B58208ULL, 0x5096D423B87F30E2ULL, 0x0F6F8BA49BDD577BULL, 
            0x83E996BAF2131458ULL, 0x626A1CA98B78FC1AULL, 0x1D918F98A49DD1C3ULL, 0x8910C377AA51EEFDULL, 
            0xED880EE51DF946EDULL, 0xC8EA38168512B58FULL, 0x657D74C196DD71C1ULL, 0xF8E4083F2018DE5EULL, 
            0x66803D47F3EDE3B9ULL, 0x68895F92C66285A1ULL, 0xF950D9B12178F070ULL, 0x20B02F0ED4F09369ULL, 
            0x4D6ED45C3B4B7527ULL, 0x49C8FCD4D0CCED89ULL, 0x491DE84AD76D5E54ULL, 0xB8BB25B66356BB3CULL, 
            0x1FB5C29F6F78112DULL, 0xDC505AF9F2CB14AEULL, 0x9BD79BA9E3E976D2ULL, 0x8CBACC265AC14F6AULL, 
            0xEAA18906E763537CULL, 0x05C143FBD5D09092ULL, 0x8D8E1C3DD9ACE4DFULL, 0x7D236B93DB746699ULL, 
            0xE903E3817511D834ULL, 0x57ACADA94DF6D7F1ULL, 0x471912239641C998ULL, 0x2B5540BE327FA60EULL
        },
        {
            0xE5F70EB159A62E42ULL, 0x1BD7982EF1C9516BULL, 0xB5C68F0239D416F1ULL, 0x935488E481536105ULL, 
            0x578F007EF3BC2878ULL, 0x38DBC093EE7E7DC0ULL, 0x239E0809E34861ECULL, 0x09400AF874570F53ULL, 
            0x36C8F658C4F22C2BULL, 0x19985485C7AF4C10ULL, 0x7C41692F8237C70BULL, 0xF941085EA4F15613ULL, 
            0xC2F95789977858E2ULL, 0xC574FDD18BAFC6B7ULL, 0x33AD349B610217F0ULL, 0x0C3A06A5BC6AA92CULL, 
            0x1D44BA29F69E1E2BULL, 0x77D0CA09DC9A203BULL, 0x83177CBB39FF7720ULL, 0x9922CA9CCA5A93C4ULL, 
            0xA87B9C4B4BEC4288ULL, 0x05F6EBE1CF97A58FULL, 0xFE2053EBC5FE2C5DULL, 0x16940BCFF07417F0ULL, 
            0x446FF8EF8C36A968ULL, 0xB2D79C8A0F253F95ULL, 0xD3165A23B9E91306ULL, 0x0DC335CD6CC128BEULL, 
            0x077BC503C002C991ULL, 0x17A11823BEC6AE3EULL, 0xE91B3B7B4123FA0CULL, 0x7B9C017C83E39076ULL
        },
        {
            0x47B5151191DAC643ULL, 0x955ABF389D55E68EULL, 0x3EB9A9F1EB331583ULL, 0xA3BE1AF02D2AC4F5ULL, 
            0x897F24810D2E059AULL, 0xB697AF3F49D51B95ULL, 0x4C3EAFEF1AF554A4ULL, 0x93AB05EFE34EE7A7ULL, 
            0x14C9689AD1C48B05ULL, 0x8C55DA9554CCC547ULL, 0x719B0A1C6A887D4DULL, 0xF33FF7E8C4D6F61AULL, 
            0x8210F079E55D4917ULL, 0xF106D7DEEE4BAF24ULL, 0x76A7F9C307FDA9DAULL, 0x49FCB6CCF660BA24ULL, 
            0xF83C075AC7EF2761ULL, 0x32B0ACC1B18C872EULL, 0x7046184B81B41FC3ULL, 0x6102E0ECCA0CDC55ULL, 
            0x58FBF0CFF9F5F28CULL, 0xAB097AFB4E7E1EE8ULL, 0x6E8E6398A6ED9E91ULL, 0x6347475550771675ULL, 
            0x8DBECFD6156F1277ULL, 0x2FFE928FE9DF368DULL, 0x6859264E949AE895ULL, 0x777EDDB5C982E222ULL, 
            0xF445D6BBB768A6E9ULL, 0x36700BBA0C3F917EULL, 0xD1B9932287AAD144ULL, 0x862959401DD92DF9ULL
        },
        {
            0x0977A718D246F870ULL, 0x16ED3BCB09F6FA94ULL, 0x844F8C5284D877EBULL, 0xBB86BDF7BEBF5487ULL, 
            0xC2D2D330276FCA69ULL, 0x516C6F37E9BFF649ULL, 0xF61C703D2F81CC73ULL, 0xEF3C8D17E2FB1A55ULL, 
            0x476A91ADABB68A2DULL, 0x31EE08D23B719A92ULL, 0x2B5DCE64A22D8341ULL, 0x14A2D58E84BEEBA1ULL, 
            0x7FCA38AE7C4E88BBULL, 0x34074B4F2DC86DECULL, 0x4A81AEC110DC1730ULL, 0xDB52FB033881D857ULL, 
            0x06AE5ADDD348A7CDULL, 0xD5614144F4947A13ULL, 0x04FF40111E7D4694ULL, 0x5864BB2531C83F93ULL, 
            0x265FE2EF83BFBD8EULL, 0x7C363DEF584CD877ULL, 0x7D2014598E2DE609ULL, 0x7449D77A3157AC5CULL, 
            0xAF3C34A9AA9B68ADULL, 0x36962BD46C969836ULL, 0x249178668433E59EULL, 0x537AB830F9A6781DULL, 
            0x291F2EF0DD4EA9B3ULL, 0xB7B0D7D179C79A58ULL, 0x747F65A1296D3F71ULL, 0x209C40059F7C82C7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseEConstants = {
    0xC4FAEA2CAFE0D1F9ULL,
    0x1A2FF07E1673D3BCULL,
    0xD788E451CE9B865EULL,
    0xC4FAEA2CAFE0D1F9ULL,
    0x1A2FF07E1673D3BCULL,
    0xD788E451CE9B865EULL,
    0x22589ED62602C808ULL,
    0x17A4483AD3954180ULL,
    0xB1,
    0x87,
    0xEF,
    0x65,
    0xC2,
    0x9C,
    0x33,
    0x95
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseFSalts = {
    {
        {
            0xDF437AB9E20E5014ULL, 0x9992A7EF5014D57FULL, 0x1EBB8009F5BF21D2ULL, 0x9DE0B571F1942715ULL, 
            0x052768C94CE245E4ULL, 0x42C7678A1C3D5817ULL, 0x48D583A2A35D8896ULL, 0x6BF6EB0B2E4ECA8DULL, 
            0x180052FE6BF3B3A7ULL, 0x71847B79C0E095FCULL, 0xB572F5C32E02AA10ULL, 0x338145827D8A00CCULL, 
            0x4D88B76440697FADULL, 0x4647B9EC041E684AULL, 0xBD3C8D319879DEF6ULL, 0xD67D3D63F5D3F4C9ULL, 
            0x29A73B1B985C2890ULL, 0x3F6A9ECA7D901BFBULL, 0xE9396D9196370316ULL, 0xC73CCCE0ED257B6DULL, 
            0x395EEB36C6B8A3B3ULL, 0xB3ED2A231EB9728EULL, 0xF94B1015E03849CEULL, 0x23C6879C92DC10F2ULL, 
            0xB525F75414874BACULL, 0x99E7201788363864ULL, 0x64C0DC8F29F66F2BULL, 0xB95C81CF5D3409BAULL, 
            0xD3ACD0E8C76011ABULL, 0x91FBA04C408B9A62ULL, 0x7ACFCE4B877DB183ULL, 0xBF8F257C5F001515ULL
        },
        {
            0x79DC2EB54EBC39CBULL, 0xDDAD718EAF3F7428ULL, 0x441BBCB158BADE29ULL, 0xBABC017284B3BC16ULL, 
            0x3B4773F41202A68CULL, 0xF69D8066F08D8EFFULL, 0xA122E4EBEF0A730BULL, 0x9338CD5B2512C695ULL, 
            0x951A8FECE244F2AFULL, 0x7347F0CBFC7534D8ULL, 0x4C4DC9D54AF20FAEULL, 0x263D52314675D3B7ULL, 
            0x121E3CA60400B797ULL, 0x4954ECA3D4BDB59EULL, 0x8669DC52F9DDFAE3ULL, 0x4620F1C21ED3CEBCULL, 
            0xBF234F45EB24151CULL, 0x1497BE684F9EF999ULL, 0xFABA416C28179BB2ULL, 0xFB880C4264CF6D50ULL, 
            0xC32C3707D16E1494ULL, 0xBC73570A07FBB6A4ULL, 0x2F43FA22189E097BULL, 0x08783DE9138F6AE2ULL, 
            0xE33A7C24DA2D2EB6ULL, 0x8D1A35FF31728767ULL, 0xF738263426D6CC58ULL, 0x84C62508C25DD302ULL, 
            0x98CD163438C14DD9ULL, 0x02521E5537E7FD08ULL, 0x66A5CB80C4798F6DULL, 0x0AAE490182EEB32CULL
        },
        {
            0xDDC2BBC61D570659ULL, 0x25B466696FDEB8BDULL, 0x18822C62966EE52FULL, 0x679870B5DFD98633ULL, 
            0x4B34EFE26ACCF9E2ULL, 0x1F8748A6A26E5EC8ULL, 0xE6EEA6EF31A972CFULL, 0x4B5B31405235B13FULL, 
            0x671A3C09923AEF1CULL, 0xCA1EC62EDE490BF7ULL, 0x37AFC1C25E3A3E65ULL, 0x6287D1D8BA188202ULL, 
            0xF0F6A9324897BD8EULL, 0xADBD1D676B993F9DULL, 0x1D8AF591745D1248ULL, 0x4CB1869F0C571CA5ULL, 
            0x5A343F845BC1E922ULL, 0xDBEA6C48F441AC6CULL, 0x5BC857ADB032ECB0ULL, 0x00B304AA8CA7C765ULL, 
            0x16CD558E863E664CULL, 0x52DC06112548DCBFULL, 0x6C8F00A8D524998AULL, 0xE44EF1F5D9E8DEEEULL, 
            0x06EA5FBD2DD56934ULL, 0xF7C276D15A312B76ULL, 0x37B672ED732DB557ULL, 0x0ED0D50AB45E9D3CULL, 
            0x3B1F3C494604ADA7ULL, 0x4FCD127CDAAEC399ULL, 0x313664CA1FE2530AULL, 0x65A64249305442ABULL
        },
        {
            0xFB51DAC0898EAC2FULL, 0x5670416F53DB9A5BULL, 0x9AB87A8565CC1B9BULL, 0xA608BF58B91477A9ULL, 
            0x09CE432B04C087D5ULL, 0x33E39607D62E08CAULL, 0xDDDE684DA48CFCB0ULL, 0x92E2270F356BFAC8ULL, 
            0x56C8EE32BC794178ULL, 0xE83F5DBD3029BEF7ULL, 0x60FC76C2E6B1B6CBULL, 0x69D2DB17C2CA2F94ULL, 
            0x1626669F155586DDULL, 0x6618E1F08C06778AULL, 0x357F84A65EE10E66ULL, 0xB71FB03D347D3134ULL, 
            0xCF02EA269DDD226FULL, 0x3230732022F5D786ULL, 0x30668F8618902E30ULL, 0x55C14FF8457DA1F5ULL, 
            0x0790F5564103BDCDULL, 0x7F2ED62B35F459FFULL, 0xBE685B08E929A713ULL, 0x9FA797BC76E90D1AULL, 
            0xBF966564EE837CF5ULL, 0x43E38C016E336A21ULL, 0x83CE41CEFDE3CCBAULL, 0x27E997C11D62FE81ULL, 
            0xB0FE6D948BBE8657ULL, 0x71220861FF262EACULL, 0xB0112B1BF4D7FD22ULL, 0xAE3897D2946AEA6BULL
        },
        {
            0x135C5FEF68733CAFULL, 0xCC309FA35E962B3DULL, 0xD3BCF919DEDFAC4AULL, 0x7EC388D5E6A3331CULL, 
            0x2D9FA1AB3B3802BAULL, 0x39C0274C282124BFULL, 0x5D3CF3A785DA4627ULL, 0x93A959922A35F002ULL, 
            0x6282605D37D19FBEULL, 0xF00A0CBB51EEE7C1ULL, 0x9134569E10849093ULL, 0x03503C7B2026ADB4ULL, 
            0x44A4BC68511F6602ULL, 0xC804F909B4B17A0FULL, 0xA3D6ADA9E7F381E2ULL, 0xAA6A470DD5A144EFULL, 
            0x0E64BAC23E65C18EULL, 0xBD67FA0CB17E5DA9ULL, 0xD2D8160C340BF29FULL, 0xF275C7BD82A0BF8DULL, 
            0x676D56610FFCAD67ULL, 0x0BDA25C8DBF5DE2EULL, 0xFB8BFC24E99914FFULL, 0x08D52E78F42E0589ULL, 
            0x3E4612E6B9004F68ULL, 0x83CDF996C7F12FB5ULL, 0xE9E44E6C32C6A29BULL, 0xA8ECA0971DB5A9E8ULL, 
            0x943F30B158B8F4AAULL, 0x8C93066D5166FBC8ULL, 0x1D46E9E3DCFBA2EBULL, 0xC0EF7661A88FF27FULL
        },
        {
            0x9EEEA04570B1C166ULL, 0xA235F178E4920C6AULL, 0x2DFAE7843BF269F9ULL, 0x6DD55741B77FF003ULL, 
            0x053BF10DD4AD871CULL, 0x917C99F707596975ULL, 0xACC926A0FC58FD7AULL, 0x5E72765F11626B65ULL, 
            0xE26C7F8B82B09622ULL, 0x0BEA050F5C8E1B2CULL, 0xE9D9A44A5713C8F3ULL, 0xE46C6138A109ED00ULL, 
            0x3FE02F384742AC64ULL, 0x1F5B139D13875E73ULL, 0x22AB8AC900D2D9E2ULL, 0x6869352EE0C30DC4ULL, 
            0x351A8B2DD394D1ADULL, 0xFAFB1F41B5E7E823ULL, 0x9FD6A08EF656F9B4ULL, 0xF02B2260081DCF68ULL, 
            0x791A9C2D6AFAA164ULL, 0x0CAEE480BA51B45AULL, 0x4B3AE237F578437CULL, 0x2C98D574FA536350ULL, 
            0xF2547AB78751691DULL, 0xF4A7A153445D2FF9ULL, 0xC3E917454B64DB00ULL, 0x57C79977A3C4B8B7ULL, 
            0x22824D6095A40271ULL, 0x49B45E4F35B1598FULL, 0x2414BDF601888080ULL, 0xCE72B3AAFA3358C7ULL
        }
    },
    {
        {
            0x207898BCF8C9AE27ULL, 0x6324AD70A0F028D8ULL, 0x434FEA100F946CA5ULL, 0x4EEC638C9974211DULL, 
            0xF6636AAD96812787ULL, 0x2FEABB0FA164C160ULL, 0xF834B2DAC1A0A967ULL, 0x65169DAF20420266ULL, 
            0xF25F60A0A90A7ABBULL, 0x1DFA61E5370D8B55ULL, 0xB69B5E57985C84CAULL, 0x01CB51743AA86B47ULL, 
            0x6B61CC1365D5535DULL, 0x480CB7608448973FULL, 0xCC6462B252FA776EULL, 0x5F9C84940E25026BULL, 
            0xBB511E81BEACCE2CULL, 0xDAF1AF61C47B5408ULL, 0xFEB2DBB4CF113DB2ULL, 0xFCBB8219EB42B8FEULL, 
            0x54455ED79AACE340ULL, 0x42A3BD7059CEF691ULL, 0xD420FD10C09C612FULL, 0xCF54A7E3ACBEFAA0ULL, 
            0x108E62E39DBAB1EFULL, 0x7AF8D8CA472FA506ULL, 0x74121BBAA1AFC61FULL, 0xC92D37C521CEF480ULL, 
            0x974615E4AFA1B862ULL, 0xA0FA187AB9B321ABULL, 0x1C2A1190F294DDADULL, 0xD1335DA029F05C4BULL
        },
        {
            0xFF6E9BCBE59C5FD8ULL, 0x2A5FB8D3D3B541B1ULL, 0xD4EB630F42E7C6F3ULL, 0x9E60C112EA34A4F8ULL, 
            0x9BAA3BBBB33073CBULL, 0xC527EBF208990D1BULL, 0x7DEBD769AC55AA4BULL, 0x80ACDA3320D296D0ULL, 
            0x6C04A873FDEF01EEULL, 0x73FF8D23F468870AULL, 0xC8ACBB192C99801FULL, 0x46D21B38C3929686ULL, 
            0x23DD0F43FF993938ULL, 0xE951E1F31963323AULL, 0xCCCF8626E9D83BD3ULL, 0x6D1A1DB0C95A7324ULL, 
            0xE272E3D787E8B86DULL, 0xF059FB713603DC87ULL, 0x771B3D110A94FD09ULL, 0x28210B8121D93D8BULL, 
            0xE4707ACAE46416E2ULL, 0x5CADB05F95910DDCULL, 0x29E8A2D897913DC0ULL, 0x6808863F44709ADDULL, 
            0xD20E9C5B8986CD2CULL, 0x392EE2DC7A659A08ULL, 0xF2D97ADA8A185D7DULL, 0x5BAC92AE3775F4CBULL, 
            0x6805AF4D0550BDB2ULL, 0x331E4F1A5A576037ULL, 0xC95A53E563E93A82ULL, 0x54C4F977B326EDD2ULL
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
            0x5BF59896694D7539ULL, 0x41606FB007108563ULL, 0xDBB5775D8C2331A7ULL, 0xEA4D7C07642E1DF6ULL, 
            0xE433A7B0407457C2ULL, 0x3EC8247E7058885FULL, 0xE0B286670501AA8FULL, 0x2F2C18735E04141FULL, 
            0xD3E1A120D9CCA49EULL, 0x880992941F23BDF5ULL, 0x381D2FC6ADE6DA78ULL, 0x5F798889A5EE9EA6ULL, 
            0x9AFD7BDF0FA7ED97ULL, 0x03D3C2CDC09470D1ULL, 0xDB3110EFE91442D1ULL, 0xB3C541C164720737ULL, 
            0xFAED8662944C429BULL, 0x9814ABB86337AC12ULL, 0x6CEB680C0E42ECB1ULL, 0x6F6DFF86022EF139ULL, 
            0x14C92E8503B0EA25ULL, 0x2D21299009331C96ULL, 0xE5A1121D9D008CE7ULL, 0xB17433BD278F38B0ULL, 
            0xEAEEABDF08C23025ULL, 0x6A6082E554A15B8CULL, 0x2B7795A3182F44B8ULL, 0x39C46DD856983E31ULL, 
            0x09D607FABDB3CBFDULL, 0x130CABB957E6D4E2ULL, 0x69D9C0888B7F04F9ULL, 0xA85E2D437BBA1B2DULL
        },
        {
            0xFE518FA286C29ECEULL, 0x566BA766F98473ECULL, 0xF894691027F3D238ULL, 0xC446E9188A27DF22ULL, 
            0x33576ACD40744AB3ULL, 0xC4E2AB9E7C5EDB6FULL, 0xD80D51939E2FED0AULL, 0x6928F93E28490B85ULL, 
            0xE0504279CC432C01ULL, 0xC58B12B833C37BBEULL, 0x97C3D192FB084DCEULL, 0x7B2EC3B48BD35BE4ULL, 
            0x3D9DA5C6E1A39786ULL, 0x42A61F40E56DC3DDULL, 0xE4A2ED4636D29D51ULL, 0xAAB26E79D1E6EBE4ULL, 
            0x5C01787596039D2CULL, 0x600F17826AF62A35ULL, 0xD5C834DB3BA7A49BULL, 0x1D0D55FCA3784FBDULL, 
            0xA45EB4EBD5DD7384ULL, 0x5DF25418EF667040ULL, 0x6A593255A8921F89ULL, 0x9BDE08D18E6845CDULL, 
            0x8D71F6B11FAA7CBFULL, 0x3ADFF8622BCBFC14ULL, 0xAC14DAC9250B2756ULL, 0x5E281E881CDC97D6ULL, 
            0xCA468300D3103997ULL, 0xDBF3F6C373291656ULL, 0xA11F786C847B9CADULL, 0xF7172E6454A17FC7ULL
        },
        {
            0xE05412BE83868F94ULL, 0xBE72CA2E0B25BB53ULL, 0x5825A2679BEAC132ULL, 0xE2F46C4329C49A1CULL, 
            0xDC6B5632BA198647ULL, 0x46A28609612AB09BULL, 0xE02F4A1E8100072AULL, 0x814F752A37CD3441ULL, 
            0xC132B5532F56BF3CULL, 0xC0B132C5665ABB8AULL, 0x349F23059B788331ULL, 0x1D4F7231A5104A02ULL, 
            0x5268B17661AC23CAULL, 0x8A06C0D79585E0DBULL, 0xD78C1195D1094DDDULL, 0x909CC9E31036EF91ULL, 
            0x442ADCA1D3086139ULL, 0x570FAAC36BCE9917ULL, 0x161BB0ED219F9D51ULL, 0x0F20D6D6F79C42DBULL, 
            0x6481D9174ECE005DULL, 0x0E4A462F03987405ULL, 0x4844DB671ED74161ULL, 0xFB44B2205E9DE0BDULL, 
            0xBC33E1B3385241C8ULL, 0x327193FF60318003ULL, 0x747E7289B312C6B5ULL, 0xD80A09B2A512C233ULL, 
            0x7A96928F07EC2E19ULL, 0xC4BF20CD49B1F0DEULL, 0x5240D3E880BDAED9ULL, 0xEEA4860B8B6204ADULL
        }
    },
    {
        {
            0x8474ECA51879B0EEULL, 0x8E09492B311E6F1DULL, 0x2A6ACD2D0EBAE69EULL, 0x086A86174B6A5185ULL, 
            0x612929CA2BFE1D4AULL, 0xA12CF3C0A9CDCDDBULL, 0x76E2E68DBA41B928ULL, 0x04C48BBC1399EC63ULL, 
            0x203161FA18B243F3ULL, 0xA508E7CBA044F98EULL, 0xA4B46C53890C6ED5ULL, 0x8F739C385C412F1BULL, 
            0x7592E3D339A8AFD6ULL, 0x460153B78D2F4A5DULL, 0x5FDC5800D77C2218ULL, 0xA3194FFF47908B96ULL, 
            0xEF642B8A12BFBE38ULL, 0xC7C26C1B3656D1F6ULL, 0xA9369F39D39E2DC6ULL, 0xA2A04149FECFA057ULL, 
            0xF52EDE4F0168315BULL, 0x3BA844330C553FE7ULL, 0x034EF9CB164315E3ULL, 0xC95826E3AF7CC074ULL, 
            0x274E609C9CC6ADBAULL, 0x4721E45E0030E474ULL, 0xF2ACFEAF85F89539ULL, 0x9980D509BC105683ULL, 
            0x8DEAA873DB79D33FULL, 0x5EA62272C5730262ULL, 0x613BA639D4A7714FULL, 0x6AA0E197AA3CADBCULL
        },
        {
            0xA41E5D6A39575AE0ULL, 0x7961E391103D03D5ULL, 0xA2AEE4BDD49DDFEEULL, 0xB52E66068976CF26ULL, 
            0x9689ED1FE533F33BULL, 0x6A2CDD44E0AFA5BDULL, 0xA2476F3CF03242FEULL, 0x9730041B9DEBF6C4ULL, 
            0xF5AE50490ECE186AULL, 0x7BE18CF3278E1B59ULL, 0x94344B480F4789E4ULL, 0xCA042A07DB0F2A2FULL, 
            0xD9DF3221141F43A9ULL, 0xAE2E85D63851BCE4ULL, 0x7C6117BB3D907487ULL, 0xF5FB77BC28E05B19ULL, 
            0x8190E5C98610A03DULL, 0x0646288C8D8B76F5ULL, 0x68284E501E109C69ULL, 0x41367C827C0401E8ULL, 
            0x3A933B03C14B9295ULL, 0xD974E3EDBE8D0197ULL, 0x43F9170671464D07ULL, 0x11681BCEDF40584FULL, 
            0xBAFBC2B6C3251082ULL, 0x6781F4AA19016600ULL, 0xFF37A51F9CE57ED1ULL, 0xAD0307E7DDCC95C8ULL, 
            0xD7B9798EBAA5BD93ULL, 0x60888685E611A5EAULL, 0x396066EB7089547BULL, 0x4E8558C554912546ULL
        },
        {
            0xA025978D94C97DF1ULL, 0xD461A0CB1F92A784ULL, 0x01E81B40A072ABCDULL, 0xBFCB1568F2699B5CULL, 
            0xFF9E808F65378530ULL, 0x88AD971D06A653E5ULL, 0x84F87A8C302243CEULL, 0x65301CCE0FC02D5BULL, 
            0x20EC359C4BE0D8F4ULL, 0xB0B5646A5AC8DDF5ULL, 0x00486AA70AA6A5C0ULL, 0xC443DE5AD0A3677AULL, 
            0x6EBB7D083FA33A70ULL, 0x98C45006EB5346A0ULL, 0xD2328EFAAA2D4898ULL, 0x9D9DC7316B818558ULL, 
            0x25DB1A1535C983E4ULL, 0x259EF670A95FEF7DULL, 0x20010FD99FBF1901ULL, 0x0CFBDDF4456AF12AULL, 
            0x6412DB5B42558173ULL, 0x4627836B812AFF9CULL, 0xC4AAAF9246E892E6ULL, 0x3C6332A0AD3FCB85ULL, 
            0x0096E492E5975D79ULL, 0x01DAB7ACEDC683C0ULL, 0x8B45F4A5F22749B8ULL, 0x0B787B2DD4A36776ULL, 
            0x4DD0248C1162E2B5ULL, 0x5E143810B0DA40ECULL, 0x9F1E7A3F696AC458ULL, 0xC099351630CDC64BULL
        },
        {
            0xE4A18A5A2D35298FULL, 0x4D2CDDB1D968E13BULL, 0x17D8BCE17A3F1365ULL, 0x7A41E5B1A97C9E82ULL, 
            0x37A002DE74EE368CULL, 0xAABEE66E456B2DBFULL, 0x3FC409AD32438B99ULL, 0xBB1728EE92A0EEC9ULL, 
            0x50D472718E879503ULL, 0x3B7246061E60A7FEULL, 0xED6077B46E06CC84ULL, 0xD8D47A8F34C9AE29ULL, 
            0x3A4FCBA3B8AE926BULL, 0x09B68257F7D5BD08ULL, 0xBD5A7D4A19F81FE2ULL, 0x9E875AAD7BE1991CULL, 
            0xCF8334217B0C25D0ULL, 0x81ADC305C52AE50CULL, 0xCF243D8D31D6AFA1ULL, 0x878A7A37068DF897ULL, 
            0xB3B9F6BC2DC7BBA9ULL, 0x769745DC485BD13FULL, 0xE9ED3A68DB253EA1ULL, 0xF187A1B2080ECB15ULL, 
            0x8461C1D2ADC35EC9ULL, 0xC4D043A530E8F1EEULL, 0xA9F337CE67D7641AULL, 0x8EE8FC00D0419AB2ULL, 
            0xD69C39908BCE87D9ULL, 0x0BF65928D2307F72ULL, 0x2025EF9DF1AEDFD2ULL, 0x923031A2B89B2AACULL
        },
        {
            0xD1691E0201A9E3C0ULL, 0x059A5F720391DC58ULL, 0x252340165D39F635ULL, 0x2DD043958BB67EE6ULL, 
            0x47F30C88526AD572ULL, 0x9A7A349CC384713CULL, 0xD3DA4420CA52FEA9ULL, 0x20080350EC17B82CULL, 
            0xB15CBAF61810E76BULL, 0x71201525DBCC26E3ULL, 0xAB6047AD7232AAE9ULL, 0x53EF78C553CFC6C6ULL, 
            0x4614EB0A25E264F3ULL, 0xB2120C9B208EAA11ULL, 0xFF1667D2D37D937FULL, 0x0FC5FF2EC4F2560CULL, 
            0x71AFDB849C1021CDULL, 0x73E1AAF414F7036FULL, 0xF663253A052BE7D3ULL, 0xECCD31C33D7CB930ULL, 
            0x385E1B3B4A79F3BFULL, 0x97D3861E2BE5998DULL, 0x77B9422E16C87639ULL, 0x1512AC026E24FC5EULL, 
            0x861B14D60F092464ULL, 0xB23341C4EB4AF3A9ULL, 0x76587756979421A3ULL, 0xDD3F0FC065362727ULL, 
            0xCB072807C70B2955ULL, 0xFD72460ADC76D90CULL, 0xBE48E9EC0932F072ULL, 0x62F52FB3774BAFE2ULL
        },
        {
            0x60BC1594BBE22C0EULL, 0x6CE1497AEFD84FB4ULL, 0xB64A354F1B7C6940ULL, 0x038F694C56CF873CULL, 
            0xF4A94FBB0D44944AULL, 0x81B78C8F24163D63ULL, 0x1951F1803B92CD08ULL, 0x0C01220F5B67BAFEULL, 
            0xA1A4A74DE310CAFEULL, 0xA341EDCB3EE861B9ULL, 0xC3664D4A95077C20ULL, 0xD90ADD9A9C3244BAULL, 
            0x32DF08FC2F66F1DEULL, 0x3B5E7138AA7CC530ULL, 0x9ED8ADBD374F4AF5ULL, 0xDA3660FF4B3E7F41ULL, 
            0x4BEF73C4FA10AAC1ULL, 0x9DDB402DDB6DFE25ULL, 0xC08256E38EB09227ULL, 0xAAC3013341A36C1FULL, 
            0xBBBD4E9FC67AC4D7ULL, 0x8D7BEBFFEE2497F2ULL, 0x9C0178163FA5F5E9ULL, 0x7A7B9925C6B756ADULL, 
            0x30BE308282785D8DULL, 0x17FC62DABD152E48ULL, 0x66D439FCF688436CULL, 0xB8848B9D09038E39ULL, 
            0x5E7D1525256C5DDEULL, 0x832A3DC263937A25ULL, 0x934833B82F730ED5ULL, 0xE12B309095B0732BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseFConstants = {
    0x55C16A142BB558CFULL,
    0x38BC3E9B47257C92ULL,
    0x5D8E4730A4A358A7ULL,
    0x55C16A142BB558CFULL,
    0x38BC3E9B47257C92ULL,
    0x5D8E4730A4A358A7ULL,
    0xA9051E2902DA63F2ULL,
    0xA326807A8FDCF2C5ULL,
    0xEA,
    0x63,
    0x55,
    0x07,
    0xCC,
    0xF5,
    0x02,
    0x2C
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseGSalts = {
    {
        {
            0x5EABB11875B0270FULL, 0x552B6B4A3CC19676ULL, 0xCB056A33C9CE1DCEULL, 0x3727FBE80F3371F1ULL, 
            0x2BC0A9EC7B2EC96DULL, 0x5F276708834D7E15ULL, 0x6A065C584D1ED050ULL, 0x6B9E591B13D86127ULL, 
            0x3214F6CCE1E9C000ULL, 0x06D0F9BA263EE533ULL, 0x0CBE27561FB53AF4ULL, 0x5DC37AE84F0F6872ULL, 
            0x70F6F5C917662F4AULL, 0xDA69D0743798E034ULL, 0xEBAF92F2D6C2B172ULL, 0xB1CC04F7699E3E75ULL, 
            0xC76D5B19BDAEBCB1ULL, 0xC8AEE43DE1146E20ULL, 0x42397474C40260AAULL, 0xB8A976CC18A9F349ULL, 
            0xAFCB25DD81A84BC7ULL, 0x812254ECA5D34BEBULL, 0x3816BD61C18E449AULL, 0xCE5162FB4772E863ULL, 
            0x0E08CCF14F89EA94ULL, 0xAFCA3A5FC2308487ULL, 0x20DC68B486F614F4ULL, 0x1E9E42607624995AULL, 
            0x4586DFB5ADB21900ULL, 0x66957938680CAEA5ULL, 0x88D38AEA6EBA204DULL, 0xB511B2542E36638CULL
        },
        {
            0x19115B6479BDD245ULL, 0x3375810326003847ULL, 0xA808DED39B3A75C1ULL, 0x9F0A67C6A9E67D39ULL, 
            0x4B744579B53A64C8ULL, 0xC55A63C336920FD6ULL, 0x91825D49462C4164ULL, 0x900A3D09FE2B0AABULL, 
            0x1E793D4BF8212A6CULL, 0x3A0896F794D1F226ULL, 0x8DFDBA7267EA00E1ULL, 0x6E51FC80DC03AE20ULL, 
            0x7719B07181836BFDULL, 0x409EF00CE8B76E1DULL, 0x9D0694999F84B35FULL, 0x3F9DED5C1AF5EF91ULL, 
            0x1FC671D9F7F86119ULL, 0x8EA1C63077C4ABB9ULL, 0x17A3C7C32661FA54ULL, 0xB253DD411B27A35FULL, 
            0xB56C1EC026FDDADCULL, 0xC2F81D4062FBBD58ULL, 0x7938FB77BBCA880DULL, 0xD6864C9CD4275DFFULL, 
            0x655E02A1BF519A47ULL, 0x676A062D6CEE111EULL, 0x0A762A9002AF60A6ULL, 0x7ED14DC4D217ADD4ULL, 
            0x2D619ECFB14C6F82ULL, 0x94389F00531E9B1DULL, 0xA900CFE7FA2F0F43ULL, 0x8B1EB0EDA9F0BF8BULL
        },
        {
            0xBAA64244BE310B26ULL, 0xBB2129694BBE2ADDULL, 0x1C87E1FCC853115EULL, 0x4EE88F6E2604867FULL, 
            0xE62A9C7BF30F9954ULL, 0x9986A50C42741EDBULL, 0x24F87D4FFEC2C891ULL, 0xEE96AFEDC3EF583FULL, 
            0xD374DA8627E44C19ULL, 0x5B7AC313C866CB8EULL, 0x6D8404529A7F898FULL, 0xFE506DED9F1BA98EULL, 
            0x43A801B67DE4A251ULL, 0xE86D238D35E0F4A1ULL, 0x1D58C45891CCF9C4ULL, 0xBF19A943D868C74DULL, 
            0x469A314740A55103ULL, 0x3F8CF701A019770DULL, 0x107DA9C2B5CB8306ULL, 0x1FC0F93E091A6B2CULL, 
            0x1020F09C3C9BBC50ULL, 0xB1ABA1CE443EC8A2ULL, 0x6E3D573564BD6E46ULL, 0x7AFDF1DC7214C465ULL, 
            0xFFDFDAA4EFCF69ECULL, 0x1D57F50361C86216ULL, 0x882B83A71F8471C9ULL, 0x67F6AF0E5A370E0CULL, 
            0x4A0A4ED4486180DEULL, 0xA2A2D3D88DD7A934ULL, 0xB24BB6943AEAB3ACULL, 0x8B970F777132C75DULL
        },
        {
            0x915D61E696B2BC1EULL, 0x765F9A1397D67DF9ULL, 0x1CA71C81BA44C94FULL, 0x3BFA6109FA0508F4ULL, 
            0xCFE5792D23F72B2CULL, 0x08040248EC4E481EULL, 0x0323F1A35B518EAEULL, 0x11EE0918EA38CD7BULL, 
            0x6E1055FA33820A17ULL, 0x976F02129A912A33ULL, 0xE8723AEC9A420AC5ULL, 0xF170D3B7EDC8782AULL, 
            0xCA1D85BCB44E2A3BULL, 0x6B5B3E5CF872D2B1ULL, 0x392B15DFD2F223EDULL, 0x2098B5E647729FD5ULL, 
            0x62212AD65E88C10DULL, 0xB762EAB13A73DE62ULL, 0x0CFEF11044E57CB3ULL, 0x3F5B722CD28CD7FEULL, 
            0x80890774C4272830ULL, 0xE9EBB1E5CE881321ULL, 0x96ADF896A7FA2F11ULL, 0x066DD9A5956594B2ULL, 
            0x986CBF8A0A705836ULL, 0x6DEBCD65F35DA9BFULL, 0x7E8E9EA64DAAB1DDULL, 0x3F7F6D694E12B50AULL, 
            0x370759899C4BDCDBULL, 0x10CA85BFB6E7851FULL, 0xBBB8B2722CFAC665ULL, 0xB4D12036B8429811ULL
        },
        {
            0x621D41D721467C7DULL, 0xD53EB0D125C471E0ULL, 0x4D762A598D2F22EBULL, 0x838AB6AC625DA479ULL, 
            0xFEEC44628474D00BULL, 0xCBB7B795348E9820ULL, 0x138F4C98A7EA66A4ULL, 0x0C79B2BE71ACE01BULL, 
            0x2DDDB522E48B6BF3ULL, 0x86786695365E67BBULL, 0x38791E580D33AF75ULL, 0xD496FAB23B350BAAULL, 
            0x165D468F2F37CA8BULL, 0xAA495ADB92F9C4BEULL, 0x21820B635664D847ULL, 0xC0C60D536E47D13AULL, 
            0x91C005554E05160BULL, 0x8A1DD76A1EC2B33BULL, 0x618B862397737C7CULL, 0x405D32BD859D70FCULL, 
            0xDC72772208D609E8ULL, 0x8510068FD9FBAED3ULL, 0x2F450209A6077EB1ULL, 0x53738EA59271A612ULL, 
            0x4368C4D8F122F602ULL, 0x7CEFF6B34B3F47F9ULL, 0xD37DBDF6217938ACULL, 0xAFF3F8E1A187D6FFULL, 
            0xC6F8C6D6FEC6E020ULL, 0xD2735DE67E575A2EULL, 0xDDED766B0093C363ULL, 0xD3797EFDB7D97253ULL
        },
        {
            0xE8F914F6CFB0B9C7ULL, 0x64CD29DD5621CE63ULL, 0x493CD28D0B7F412EULL, 0xCC1950335128EEA2ULL, 
            0x7EB6BFA32360F9C4ULL, 0x176DD88573932A90ULL, 0xAC092CD412ECABB2ULL, 0x4F261C203C3DFF5CULL, 
            0xE2ADDF450F880446ULL, 0x9F4E56861C8BB2CBULL, 0x47830DC482DC0C31ULL, 0x09F8D5B190E83C47ULL, 
            0x2F160CD0384ADD3FULL, 0x01D7612E13CADCAAULL, 0xF7FDDD5C55D4A75AULL, 0xCBA2B1C43A9E333AULL, 
            0x96E95395FBDB2C13ULL, 0x7660997539C11855ULL, 0x48369116876BECF4ULL, 0xE04600632431074FULL, 
            0x4D9068C6CA573780ULL, 0x9F65B12E0DAF3C5AULL, 0xC59A6962B1ABD7F8ULL, 0x3B6DF66B9C0F9801ULL, 
            0x5C5263C1849716B8ULL, 0x27A35DB8ED715D0AULL, 0xCACEA356E3632979ULL, 0x13CA196C05FEBAB2ULL, 
            0xC85F9791C01FA4F5ULL, 0xB434EE9F51764004ULL, 0xAE2497476F29244BULL, 0x7F61CB324454C576ULL
        }
    },
    {
        {
            0xA0E61F62BC2E5AA0ULL, 0x3A946349CEB4E880ULL, 0x4CE4D2CE72B8AC21ULL, 0x4909CC35CAC47DAFULL, 
            0xCF04C1EA3C6E9B30ULL, 0x876760253E9EAEDBULL, 0x62B86934F33F6B8AULL, 0x2C34679ECCC90836ULL, 
            0xE845B1B988B752DCULL, 0x6D1D779E6E069C89ULL, 0x020ECEB1C3B736CCULL, 0xBD66EEAD140B875AULL, 
            0x8B6964ADD4426053ULL, 0x5F73EE5017A76F66ULL, 0xFD5BD352C5E27DF2ULL, 0x35BA55B87A592D3AULL, 
            0x407487DE56BD1C1BULL, 0xAAE2439BB1FA0EF5ULL, 0xFED88A4D87077D50ULL, 0xAB00DADAA5C91191ULL, 
            0x60981E139F2AB606ULL, 0xE68323320898BF15ULL, 0x7F395380652EA6F4ULL, 0x38E8B69CD4C6E396ULL, 
            0x87E08A79A817D852ULL, 0x2E8E1A14AF9A814DULL, 0x13C7B8AA1634BBBDULL, 0xD16A2FBCE831EBE5ULL, 
            0x0BE328F07DD7AF9EULL, 0x79A834FB3B0AC4B1ULL, 0xCFFF744B202EA6E9ULL, 0xAEB8B469E97A1667ULL
        },
        {
            0x860C9B861FC1C5F2ULL, 0x93733C56C44A8C7AULL, 0x874A07205708D1E4ULL, 0x08649357C55D2910ULL, 
            0xE69582D88A03F949ULL, 0x923B769CBDA52D9CULL, 0xF644159AB0E78576ULL, 0x49CD0E38762A3126ULL, 
            0xDF2F3095264DE451ULL, 0xFE515B80E76775C8ULL, 0x741C7D0B7382C282ULL, 0x039E487C71930E49ULL, 
            0x1BFBEFF6EABB2412ULL, 0x732C8ACC269FB877ULL, 0x08138D90E42AF877ULL, 0xD9A84434B9E83543ULL, 
            0x934750D398A57C27ULL, 0x2F5BAE40D7974EB4ULL, 0x4D886F351EFCD91BULL, 0xF5E3C6B60E9E6E65ULL, 
            0xDF0BE1506C86C7A4ULL, 0x6E687EA6E3F1FD51ULL, 0xBBE54A4BD6BFA97CULL, 0xDF69448B5C965652ULL, 
            0xE62CC3E6C8BABA78ULL, 0x05F1D0ACBBA436B5ULL, 0xF4C6F0ED931C4648ULL, 0x68824B69E702D771ULL, 
            0xA583497F128B4D83ULL, 0xE9818CA0903C4950ULL, 0xE7F274D7FB26E018ULL, 0x369D6C8613679AE1ULL
        },
        {
            0x2100EA387905F197ULL, 0x4D96710BFABF22C6ULL, 0x0D991D1CCA320A74ULL, 0x81A5D10346FEF627ULL, 
            0x4FDDFB584022ABD7ULL, 0xD0DBEE4F595C33B9ULL, 0x889B0EA4403B36BAULL, 0x79FDA4AF42DF1525ULL, 
            0xB0E62666DD5A1FA4ULL, 0x64431C2FD5C2AC7EULL, 0x19F006623E4B2249ULL, 0x05B927A35F9F3267ULL, 
            0xEB3DFB3806071B4DULL, 0x5EA39D31C359AD25ULL, 0x7DF76D7552C335F7ULL, 0xA3A9D5C24C38AA39ULL, 
            0xA1798BB57EA450AEULL, 0x08322A85CE1007F9ULL, 0xB16583B16F229DE3ULL, 0xF5D6CEA0340684E5ULL, 
            0x7B859D941A5D3A99ULL, 0xD426C4BC74621F75ULL, 0x35CA20D37DCF9B34ULL, 0xB0CE44DA24B3637FULL, 
            0x79BEF011E7684582ULL, 0xB49D98B79CCBB3B0ULL, 0xA2D687D4C461498BULL, 0x3397C512BE006812ULL, 
            0x000E39F43603DE86ULL, 0xEE471B3BB3A4C1F7ULL, 0x6001AD9B145B7214ULL, 0x7B540B6829DDD4DAULL
        },
        {
            0xB7181F59A1A4990BULL, 0xA9D308419F369833ULL, 0x1C90069CDE9AFE6BULL, 0xC94C9443CC4DF7DFULL, 
            0x17B1DDC8BDCE159DULL, 0x364E7B8CEB675E8AULL, 0x17CB831CEC3391B2ULL, 0x28C83364180F90DBULL, 
            0xD68845CFC947B8E7ULL, 0xC1B0127FB8D1DF01ULL, 0x4916F36B10FC2FC6ULL, 0xE9534F623C3F58B9ULL, 
            0x17A1DC0E05B1B994ULL, 0x985D23496D3BED6DULL, 0x636714C9D328D958ULL, 0xA3DA880153BB3204ULL, 
            0x525FDA262FCF5E49ULL, 0x14D776F8618E91BCULL, 0x846078129E8F6DD9ULL, 0x91FF243238645D6DULL, 
            0xA366ED6E451AF63FULL, 0x0B3712FC24C27B73ULL, 0xDF09FC97A2945C8CULL, 0x15A16C693AFE7B7BULL, 
            0xA9D9753A942F2CD5ULL, 0x53D582EAF721DF19ULL, 0xEBD78C40260605E4ULL, 0xF621E731E169351EULL, 
            0x3385B82775418357ULL, 0xE2C0C29658921453ULL, 0xF21A8AB2A33310D2ULL, 0xA78EE9BBB2C40CC8ULL
        },
        {
            0xEEC1CD28878B68D7ULL, 0x12FF1C6343DB979CULL, 0xF8AB582C42B5A0B2ULL, 0xD1CB84E67FC567C3ULL, 
            0x8BA4F3D56EFC0F7EULL, 0xA9D05E0C5B3ABD69ULL, 0x7BA2AF143B2591C2ULL, 0x9AFC1738AF787AE5ULL, 
            0x0D5F1113394989E6ULL, 0x850ED84D70F87F3EULL, 0xE4917094ED0A976DULL, 0x001F640F138D15E8ULL, 
            0x803170A7455CC5B5ULL, 0x5A7C0DEB46872929ULL, 0x5CD82F8B6E4F9500ULL, 0x9FB129C3731C15C2ULL, 
            0x27369BB05A49B637ULL, 0x1FFB98B9A567C6C6ULL, 0x578B25D5718CC00FULL, 0x61E531D37AD26F93ULL, 
            0x78BBDB2684C13EE8ULL, 0x701F0C959E37B5CBULL, 0x45738A8068984018ULL, 0xCB6B8A7D26436BDAULL, 
            0x19C8D43A7ABCCC85ULL, 0xEEF2396FBEF022C0ULL, 0xECE46D819CC2C8AFULL, 0xE10971C55C0A0B2FULL, 
            0xBE9DA6CA8C6DEF85ULL, 0x0E8FD08E2E622095ULL, 0x3B90E58310070B62ULL, 0x6E22583A69B6B88AULL
        },
        {
            0xE6903755CD2F4517ULL, 0x3CA6B4B7B4E195EAULL, 0x90CD0BEF5AFD51A5ULL, 0x49237A73ACC52F1EULL, 
            0x6D48BBAAA158F187ULL, 0x5F75FEC4998D44AEULL, 0x921CA77CC3D4F96AULL, 0x5E7E913BAF026BC6ULL, 
            0x33E20F080A2739A3ULL, 0x09E2EBBD06A3091FULL, 0x1B7DCECF9B860EC6ULL, 0x9473C1303F9E703BULL, 
            0xB618D6E233B8F803ULL, 0x86F8C56B9EB21C93ULL, 0xA9E4553525FDB4E4ULL, 0x02938BD114711550ULL, 
            0x1FFEED3348995E5FULL, 0xFAE581A9AC53773FULL, 0x7D354B86F0B60F92ULL, 0x184420BDD4FFFC69ULL, 
            0x9E37E0834B435CE9ULL, 0xE53B90F65F7996A9ULL, 0x393517F8AF14565AULL, 0x065DCDCFD8542BCEULL, 
            0x1FB57D77F69945DAULL, 0x04534A1AB9ACA698ULL, 0x404BE242C65F13B8ULL, 0x775B168F725BCC9CULL, 
            0x577DF51A6532FC8EULL, 0x845FA43C1FD0688DULL, 0xCE9A467EE6BCE4D9ULL, 0xCEBEB5BD466CC047ULL
        }
    },
    {
        {
            0x116CD3EF83D7C61EULL, 0xD71EE5F2675142B6ULL, 0x55503D2038BF6047ULL, 0x11992163B7388759ULL, 
            0x7C8C61404F1C21C6ULL, 0x8AAED7E2D15EC029ULL, 0x5CE96E933B828510ULL, 0xA2297E91227FF4A9ULL, 
            0x5CF3BF8A1FAF0A18ULL, 0xE9E6A7B50EF0F9F1ULL, 0xFE221311965EE1A6ULL, 0x2CB9DFC830FEB9E1ULL, 
            0xD94E4132470F7F55ULL, 0x35033C01B8E32ECBULL, 0x187CC25C3B2C9861ULL, 0xC84F1AC559675C1FULL, 
            0x68016DD686F43F94ULL, 0x26123DC6A1F26307ULL, 0x401AE2C727B303F0ULL, 0x89FE28C32983932CULL, 
            0x0611F6D513A3FE4FULL, 0xAC0E0BCC13D5FF77ULL, 0xD9DC65734FE46507ULL, 0x01D4CC0E647A4122ULL, 
            0x3D4128F3AF887E78ULL, 0xFD3C49EDE379F723ULL, 0x49945BF3387C869DULL, 0x63EF7412A93BD145ULL, 
            0xED1D007A6716F90BULL, 0x089B09942E85897CULL, 0x28C3C490E692F20BULL, 0x464378C43BBE8571ULL
        },
        {
            0xF6C9957ABE9AD2F4ULL, 0x7EE9FDAB09EB79B1ULL, 0x8F426436967B3AA3ULL, 0x3CA66E5F8BBD4F44ULL, 
            0x76034342A4F80091ULL, 0x6E51FE12992701CAULL, 0xFC16879B136CA865ULL, 0xCE62A5321A85E3BBULL, 
            0x05F3EC5611D25489ULL, 0x27B2B0947D7A073DULL, 0x5CF384A52F03494BULL, 0x89F7D731D2CFA173ULL, 
            0x79F485C2354B744FULL, 0xFEB06041BADB4404ULL, 0xC5C5696FA956EC10ULL, 0x1F0349B67861E3CDULL, 
            0x0825A7C7617377BEULL, 0x54AD3EB46748C58CULL, 0xEB2AD2441A3C6307ULL, 0x095FBD770E1F39D1ULL, 
            0x80BCEC45BDD8E11CULL, 0x6E95ED099104881BULL, 0xF7B46E8728609A91ULL, 0x6FF85C0890734E3AULL, 
            0xD0CADD301253381DULL, 0xBC5B3B516D77C5A5ULL, 0xB39730B3EBA30B85ULL, 0x40266E2A0CA3C92EULL, 
            0x81BCAD0E10E74DFEULL, 0x06E01D66B409B1C2ULL, 0xACEBF42931535A84ULL, 0xDB17EC6F65AF845CULL
        },
        {
            0x0945AA979B9EA042ULL, 0x33B41269199EB841ULL, 0xF231C9F7FA80ECF8ULL, 0x48B4C5C30840A845ULL, 
            0x13F11EADAE84FE22ULL, 0xEFF9802AB038E80EULL, 0x6A3AFFED75D31A07ULL, 0x407AFD0E6F9837C7ULL, 
            0xED3CB5250A663507ULL, 0x372CCF7C3A27F3ABULL, 0x66B9DEF8E589B2D9ULL, 0x2FA513B386D737C1ULL, 
            0x960C4DBEF336E731ULL, 0xD3919A1C2BD97682ULL, 0xE5896FB6D3E706FAULL, 0xEA4FB7E311E5F2F1ULL, 
            0xA996FCC615DBD0A4ULL, 0xEDA998EBA6A9CACDULL, 0x424B2E3C16EED900ULL, 0x3257C2D889C44C64ULL, 
            0x50ECE7B6DFA03EBDULL, 0x29CA41121B234F21ULL, 0x58EF3547EE8CDB53ULL, 0xDC2FB47E545E98BBULL, 
            0x5D4F4052DD581AAAULL, 0xD0627955C22C0215ULL, 0x2324005EB5BA3F1EULL, 0x57CC7C94F1945676ULL, 
            0x99A15DD3D94FCADFULL, 0xCE6CF67FC8F6F3BAULL, 0x0227DAA791A683A1ULL, 0xF826F20C07BC46CFULL
        },
        {
            0x5423291B56563DD8ULL, 0xC3066C0C8C8166FDULL, 0x8B71404E067B0BE2ULL, 0x0050E2F2BA0566DFULL, 
            0xB90DB13778295953ULL, 0x2330FCC7FAE9579BULL, 0x817BB5B5F8238D01ULL, 0x42472DE672191B15ULL, 
            0x292FEC54727DA383ULL, 0x3FCB00C6F1D1D272ULL, 0xF92F9F8BD39F2092ULL, 0x2B1A8650E9C90639ULL, 
            0xDB7149F17A968BE9ULL, 0x882D3651C83EEE3AULL, 0x58E4258DC79D0A72ULL, 0x759F460F1FCB833DULL, 
            0x9048373A8B75A29DULL, 0xF5C3CCB293270CE5ULL, 0x1D88DA17086ED9CAULL, 0x2862621E45C7F4F0ULL, 
            0x2622EFDF4E0F6904ULL, 0xBF1B22E473845434ULL, 0x8057C5FC52094EAAULL, 0x5FE3E5AB4D7F85D2ULL, 
            0x27DA14491B97752BULL, 0x1F72F73B15A9E842ULL, 0x76E8CC0A92AA9BA8ULL, 0xEF05AB6F722AFCCAULL, 
            0x1304587177D2752AULL, 0xB51F041E8A9E86F0ULL, 0x343C57A401B186C6ULL, 0xB3219CC0C1DDB495ULL
        },
        {
            0x0ECEDFAFA9612A52ULL, 0xD7197F4D325A4B56ULL, 0xF90EF171B1991421ULL, 0xBC51EC5E68FE596FULL, 
            0x52CA678DEF989D3DULL, 0x9F7AC179297DFF28ULL, 0x18C12A19833527B1ULL, 0xEA6AED92BA58A813ULL, 
            0x69EC4ECC001955C7ULL, 0xDCDA4DC56FF30F15ULL, 0xE9462F15947BB9CCULL, 0x0C672BDAF39D6F51ULL, 
            0x1C4E07459A21758FULL, 0x96E3FF4C3A1B42A3ULL, 0x35D2865E1448EE03ULL, 0xF2279CEA5160F2F3ULL, 
            0x31D9C6531EF412C1ULL, 0x5527EF3419237FEFULL, 0xAA25F76AD8EC2D41ULL, 0x729BC13D1DCEAB67ULL, 
            0x7772964B4F46B2C1ULL, 0xCE8A056C8DB3D02CULL, 0x10FCEAB514959773ULL, 0xE773332FA44F6D55ULL, 
            0xC9CF21FBD4E111F6ULL, 0x3A43FD546050DD85ULL, 0xA26BB367BE685E8FULL, 0xA23958491A6276B9ULL, 
            0x93D5599FEE1F4ECFULL, 0x87ADD2D0DB80A0D9ULL, 0xB1C614C91717149DULL, 0xBA8E491FEDFA5CA5ULL
        },
        {
            0xD2667CC5E4EB6EE2ULL, 0x3BB25B68434310EAULL, 0x82DEBA4D831591D2ULL, 0x2FBD750903657284ULL, 
            0x4B6F8916F4CABA94ULL, 0xC57FCA6ABECDF45EULL, 0xF27B2A38B42E9CA9ULL, 0x5D82D817E1987D39ULL, 
            0xCFC4C64FC1C3EF30ULL, 0x1C1F15F4C6C44D2EULL, 0xE69B57D06BCB2B08ULL, 0x5E783FE819672C59ULL, 
            0x5AEB3251D8BF18C9ULL, 0xE8FB895BC91C7300ULL, 0xA9289EFCC2E7E5B5ULL, 0x8240217A5528B40DULL, 
            0xD83E50C2C73F8E68ULL, 0x493119C7E21CBB6AULL, 0x607D6CE0B2199D02ULL, 0x72834848E7BAAF67ULL, 
            0x17F8419A861A29C0ULL, 0xC61211F3EBD2882FULL, 0xD2966C467E2F0787ULL, 0x8FC13CF05E7F1FC3ULL, 
            0x7E095EFBD686D601ULL, 0x7CEE5ABF4593E86BULL, 0xD493ED0CCB4F6574ULL, 0x8E7611F7B53AD263ULL, 
            0x0D324D4C55B9DE17ULL, 0x0DA119B22F391FE6ULL, 0x712F1DDE4C65F1B2ULL, 0x0DC3AF6BBB5EADB4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseGConstants = {
    0xF0B11D2E6F13C4AEULL,
    0x8856E7D3BB5AD358ULL,
    0x74B765D5E807F600ULL,
    0xF0B11D2E6F13C4AEULL,
    0x8856E7D3BB5AD358ULL,
    0x74B765D5E807F600ULL,
    0x6C28492E5DA43F69ULL,
    0xEA6DEE391EFCB7B0ULL,
    0x56,
    0xE3,
    0x5A,
    0xE7,
    0xE6,
    0x11,
    0xE1,
    0xFD
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseHSalts = {
    {
        {
            0xE8DD6DCF5B0DE1FCULL, 0xDAC41CE7437C6373ULL, 0xFF02D42E3F509D4AULL, 0x7036DF25B37FB8E6ULL, 
            0xB4A09F91F498ECDCULL, 0xB627AE41ED317E57ULL, 0x0B892B37AB3920F1ULL, 0x79A80796B506E815ULL, 
            0x4950C7AED7633479ULL, 0xAB63B3F83BC03302ULL, 0x39F6D6EB5D5D01DAULL, 0xB34D5EB89516014EULL, 
            0x2E13C3A0BE9675EEULL, 0xE03F6F2B6B0D56F9ULL, 0x8FAB1151A1B466BFULL, 0x8EAC5EA0364EDB57ULL, 
            0xC1302E86EA90ED1CULL, 0x0BF5A1DFB0C4ECC5ULL, 0x2EEC790869E96A02ULL, 0xD20F912B221872E8ULL, 
            0x979E1847A1C79EE3ULL, 0xA89E9AB90093CA32ULL, 0xEFEC62C5A0FB3BBDULL, 0xA39EFD0DB14D0C51ULL, 
            0xAD79FC4100486614ULL, 0x9A330BF1B6594EBFULL, 0x467734B7F1BDD044ULL, 0x16F3DE1D1BB97CF9ULL, 
            0x882EF4974DE78587ULL, 0xBB00FC59E7722175ULL, 0x344D515BC0AC7743ULL, 0x51E9C569570849BFULL
        },
        {
            0xC98466B2F2FB3C3DULL, 0x57FF97215EBAB124ULL, 0x93EE7892FA1500ECULL, 0xA715319D9FA5BC6EULL, 
            0xEAD44A25B3AAEF18ULL, 0x2AA6984291C7970EULL, 0xDEA1F78C1FDD93D6ULL, 0x03721CC99EFAFD4CULL, 
            0x5327A28EF493B4D4ULL, 0x75A36DE16B8C1BFCULL, 0x7E83497D6942CD6FULL, 0x632A46A3D7E0C9FFULL, 
            0xE98BBD902E41666BULL, 0x6C58B3C1E91EB58CULL, 0x9631C772DFB06A41ULL, 0x88C57A4E8BE8CA51ULL, 
            0x6008783F5E3F43A0ULL, 0xC58EEB0DAFBAF5B6ULL, 0x21AB8D66F1064032ULL, 0x335B0648D357DC75ULL, 
            0x84D65147B5452258ULL, 0x2770A07BA60B1976ULL, 0x50CE9FD59A0420EBULL, 0xAB922E5857A32FA5ULL, 
            0xB78C754D3DD513FAULL, 0xF3A7E479E07D3504ULL, 0x6666C5786F61F4FAULL, 0x93A805936D58707EULL, 
            0x0A9D8A0F0B33DC5CULL, 0x67838FA28EAC6F5CULL, 0x5E5584D6F3EF3BA7ULL, 0xFBAAB71B8586C532ULL
        },
        {
            0xF5ABA2868943DF19ULL, 0x474E993A39262387ULL, 0x2E6454F480EC1794ULL, 0x3ACB44CC21A9D865ULL, 
            0x969D56CEBA1E9BE4ULL, 0x53603CAE627CCE5DULL, 0x9668DC1FDB484DAFULL, 0x6CCBA0836EC68F80ULL, 
            0xA712BFCAD8242311ULL, 0x3325225F244685C2ULL, 0x09F1A9DE4C5B374BULL, 0xEF5BBEF7D3E4A919ULL, 
            0x1090EF1F8783A4CDULL, 0x8AAE7B0B362754B7ULL, 0x886C83FA4557EA39ULL, 0x299369C9BF6B734EULL, 
            0x41C7DB10932DF8E1ULL, 0x2F91DBEF97AEE759ULL, 0x2150DF36D04AE266ULL, 0x81F32187448783A5ULL, 
            0xC0E716E1DE351E56ULL, 0x6313E7E367D0F35CULL, 0xCEB3B703962D0084ULL, 0xB3EF4613745CBC62ULL, 
            0xC36DC079C06BE2E4ULL, 0x290B093FB9B4A17FULL, 0xABDC3953F9EB5D3AULL, 0x38E6C5D465DAE78BULL, 
            0x95B6D70DEFCE6D86ULL, 0xC9EE5A46201CA288ULL, 0x3D02741FDA1E21DBULL, 0x4F9CD48F6A8D5CB7ULL
        },
        {
            0x6A10ACEA6E24AEF8ULL, 0x69EFB9FFCC5C29B6ULL, 0x4CE565664BACDFE2ULL, 0x4156AE4CCD7E8123ULL, 
            0xA721B71FC71A8D15ULL, 0x97ECE4792A3EE784ULL, 0x8266D3197EEF3B26ULL, 0x30807C976D8FF908ULL, 
            0x30B64FC5F63CC336ULL, 0xA2279E2FEE257409ULL, 0xFEFDE9B68A0CA07AULL, 0xEB7EF3C04B22DA6AULL, 
            0xB5277467A3DD240AULL, 0x0BB2DDD30525A75DULL, 0x2FA07509977E47CCULL, 0x9AFE80AB7F98563FULL, 
            0x623503849F7B80F1ULL, 0xCFD0593F38E3294EULL, 0x4BD80B3F72085697ULL, 0x912DA6E3DB62CF61ULL, 
            0x58C60463068811BBULL, 0x837D333EC7282C73ULL, 0x577256ABA8402287ULL, 0xDA6723371490B68AULL, 
            0xCC7523246472E651ULL, 0x6DFEE2B4EBA2B249ULL, 0xBA1F2E3EFA2165F2ULL, 0xF067F0D7BDDE537FULL, 
            0xF3D513AAE69AD7B4ULL, 0x00ED336F3501DA4DULL, 0xA1BDD52F376076D2ULL, 0x5F720FBC4516ED4BULL
        },
        {
            0x9D980DE1E2897B41ULL, 0x69B4AA6AE5C6EE72ULL, 0x181D83D584DAB8A3ULL, 0xABBCB5AD2BA061D5ULL, 
            0x03109B0BC72210ADULL, 0x87E88C0A2FE2F147ULL, 0x3CB888A1A0B38807ULL, 0x978E2BB70604D6CAULL, 
            0xD515018C9B6888B9ULL, 0x2AF704A761509E6FULL, 0x7696FF39C46B035EULL, 0xEC9A7E278D2A916EULL, 
            0x2CCA9ED46254CF41ULL, 0x2C4D765D762AD51FULL, 0xCC4ED77DA5CF75E7ULL, 0x4F2DBA5610678DCEULL, 
            0x5CD33D083EE63861ULL, 0xEE3FF51F664F0032ULL, 0x30D006DDF0142B5FULL, 0x3258856FADC02E19ULL, 
            0x244D85F747A1209DULL, 0xAD8BBB228C2DD08AULL, 0xCDEDC0562A8790FEULL, 0xD296910C62FBD788ULL, 
            0x7934EBCA0CC75C1FULL, 0x2FC2B7F40618ADF7ULL, 0x774F922377C6400BULL, 0x84A8009340A2675FULL, 
            0x4E38DAFD02150FB4ULL, 0x2AB75573B4E767C3ULL, 0x305B9731D8C3C1FAULL, 0x6B413204B9ACFE51ULL
        },
        {
            0x2123EB98BA81222AULL, 0x26CF66178B693857ULL, 0x554BCE5DD6ABECB3ULL, 0x11C395FF3F611DD9ULL, 
            0x04D518C026796D75ULL, 0x15102CC8831AA478ULL, 0x9EFB071A61B56F88ULL, 0x9B66A62182ED43E0ULL, 
            0xA353CAC845DC8C53ULL, 0xC739F07BBB7B72EAULL, 0x42C5FDDDC483DAEEULL, 0x92B2A79A0518D555ULL, 
            0x8879D98B882BEBE0ULL, 0x0EB767C4E5E263A4ULL, 0x639912EEF40D39FCULL, 0xCD2A63FFA23B75ABULL, 
            0xA265EEEFA6B8D727ULL, 0x988D1F9462273191ULL, 0xBDC62CB51BB505F0ULL, 0xB5EF172DF5353C5DULL, 
            0x2FE2C8EDA4E44315ULL, 0x8F625B9BDA6AF06FULL, 0x6D030DD13ADB2F2DULL, 0x8BB1776F228CE61EULL, 
            0x9794F5CCE7EA1AFCULL, 0x3A2B236800066B79ULL, 0x85E48BF5BB97F715ULL, 0x2213CC8CD709193EULL, 
            0xEFBF88E74AE43879ULL, 0x237829BDF65B293FULL, 0x78E5F1D0221F824EULL, 0x514116D2A941FDE8ULL
        }
    },
    {
        {
            0x48727F33E5A26ACEULL, 0x174DCFF71240D9D8ULL, 0x748B62B28C05BA4FULL, 0x73EC4754CFFF8A86ULL, 
            0x114C36262DF5DE42ULL, 0x356B8075500D9354ULL, 0xC8ACA98F21B98B64ULL, 0xE37A5670984A51FAULL, 
            0xE27A16DDD398DCEEULL, 0xF91618A721AAA6E5ULL, 0xB04525238EE58D73ULL, 0xC77A9D8B67689270ULL, 
            0x6B9C9A60B3381A9AULL, 0x2D59C9CE28939CF3ULL, 0x834A0CE172441F5CULL, 0x38186BD2E7D53EABULL, 
            0x6C4EC8D09D2479FBULL, 0x76856EC1AE75753CULL, 0xBAFAAB312F34D926ULL, 0xA83F9FFF96D25E25ULL, 
            0x828E32E996C2F16CULL, 0xEA92CE244EA9741AULL, 0x6A696C78C13A2AC6ULL, 0x2249BE2A12344447ULL, 
            0x8E09347515DDF882ULL, 0xB2D775356D158622ULL, 0xA04EFBD47B618E8FULL, 0x619203F9897A6D60ULL, 
            0x1A5B2C2F2F4064BAULL, 0xC14C79C22D4C432DULL, 0x9270A80ADFAE83D2ULL, 0x64D7D335B03E2E1FULL
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
            0xC86AEA5FD012DB24ULL, 0xFE979637ABA9FCCAULL, 0x4ED086F532435006ULL, 0xAB9DE573ECB36A10ULL, 
            0xCB9EBC29C813D517ULL, 0x0CF7F6B70FD2A99DULL, 0x50B7CCC43B71E025ULL, 0x2CF4D68FF3E3129DULL, 
            0x2B2DAEA9B6A83C65ULL, 0x9F1C87B4401B75C7ULL, 0xCB7C0163A963BA44ULL, 0x10042CE56591A8BEULL, 
            0x8FCFCB76BB106D6CULL, 0xCA02E647AC1C3705ULL, 0xC972632D33842257ULL, 0x27859C765545F4A6ULL, 
            0x7CAF5190F1BB705EULL, 0x0612033CF5B4A40EULL, 0xE974FB5728C33F61ULL, 0xB83CC88BFE97CFD3ULL, 
            0xFA664B9E3FE98D8FULL, 0x24CDFB2ED6E5F364ULL, 0x562235111F862456ULL, 0x7207983175DB9D0CULL, 
            0xC48C753DF4CC5CD7ULL, 0xDD27E2F62C5F9542ULL, 0xE57D80E446151A34ULL, 0xA2B2450B42DC2D84ULL, 
            0x1133010193C9D367ULL, 0x0F48EAD3499A30E9ULL, 0xEA48179171AF8B1AULL, 0xA06B58EE317D8184ULL
        },
        {
            0xFC034F418DB6E975ULL, 0x7891C9D9CB4690F0ULL, 0x6DA1C285183773AEULL, 0x0FBDF4478E61593DULL, 
            0xBEA9FFAAD5065535ULL, 0x660690378EA2EF3CULL, 0x7B196DA2DC929788ULL, 0x3F533FA1540646A5ULL, 
            0xAB5112FED8E2EF9CULL, 0x2AE08543C7263BBBULL, 0x151DB377D44DE9F0ULL, 0x6AC02AB41430F673ULL, 
            0x00DE848C3CED2FB6ULL, 0xBDCC831F8A1E3C0DULL, 0x50C87B789FA75FBBULL, 0xC27D4EBFCB5E6AFFULL, 
            0x99C8CA746A329A52ULL, 0x3B1B296A0CB907F8ULL, 0x8086CBCD9B0D5CC6ULL, 0xBF5463A779C192C9ULL, 
            0xFC728D038CC3DEEDULL, 0xF0210B96D36E04FFULL, 0xDF8FE43E9FD65734ULL, 0x8A5440A1768EC88CULL, 
            0xD20D28B330B094BDULL, 0x15B5721C95710602ULL, 0x5C4F1E241A26A3D6ULL, 0x12421DA4CE770C96ULL, 
            0x12566DC9058235B9ULL, 0x1DBFCB4BAE26447CULL, 0x7B240448142421C9ULL, 0x0EB988D4E9848B07ULL
        },
        {
            0x586744511F0BAD03ULL, 0xB4D7403B9CE3239BULL, 0x8A03AC7B6E4745BCULL, 0x91FA830605971D5BULL, 
            0xB04F0C5191839763ULL, 0x0AA2FD091F785064ULL, 0xAEDFE14BD3E43EAEULL, 0x7A4F5FACFE590258ULL, 
            0x60FFA7B54CE314E0ULL, 0x64C627B6AD4D3AABULL, 0x9ED15A8EFDFF47F4ULL, 0x30CE60B791C05723ULL, 
            0x69EA32D2C14F3ED6ULL, 0x6F916F4F7605D70FULL, 0x0C93ED0B57C1ECEDULL, 0x7D4712D35235323EULL, 
            0xFD407E069DBF61E1ULL, 0xB17CB652BCA2DA56ULL, 0xEC5CE666A4FA05E3ULL, 0x5F2D0CC6D9C77B27ULL, 
            0x3710DA3AEB3194B8ULL, 0xD7CE388C617C39F1ULL, 0xD3F4C6F3337129A3ULL, 0x4CB8CD7C6E0A41E4ULL, 
            0xE4A3BF6180218EC6ULL, 0x0838BBCD5C8C50F2ULL, 0x29469355F6008F98ULL, 0x6C10BFA77511A8F5ULL, 
            0x0F2390B1D50E72AAULL, 0xCF2706655BC938CEULL, 0x05871A93F81DBA05ULL, 0x126C1A56FA5FA802ULL
        },
        {
            0x8314F4C9588AF721ULL, 0xF4E4B8056ECBD276ULL, 0xEF224D6320E6E611ULL, 0x204DE8E1D47BFF66ULL, 
            0x262ED8C35E315779ULL, 0x993986460A08B5F7ULL, 0x2EBCEE9F961A05CAULL, 0x4D1E0097948EAD90ULL, 
            0x77A8A821BFBB1445ULL, 0xA7C48F0D523D2AD8ULL, 0x49D1E9879D495E2AULL, 0xE1E6AEE67BE26BA4ULL, 
            0x7BC74152D21DF958ULL, 0xE888DBA69787D8C6ULL, 0xCEE1C7A44716045BULL, 0xCFFB5B5237D230DEULL, 
            0xB0A6FC7CA09335BEULL, 0x1A6CF4D7EBEF9C31ULL, 0x871BC9B353A6288CULL, 0x0FFE882ED71C4C7EULL, 
            0xAA392D6C398DEBDFULL, 0xC7E037BE2EB4A069ULL, 0xBE4DDA50C174CA54ULL, 0x67BECFA7F234AF1FULL, 
            0x837875BF5D588B8FULL, 0x3A253F9503663BAFULL, 0x76A3ED33461071D7ULL, 0x4D410ED7B09C6BBBULL, 
            0x85DA4634F9E3585EULL, 0x39E3EA4A51E3E0ECULL, 0x9FE1E322F659D6FDULL, 0x0649E28FD984D122ULL
        }
    },
    {
        {
            0x7AE2CC20E98E8E01ULL, 0xE5672C2E1D65A410ULL, 0x71B53DE069C7FB76ULL, 0xC2AF507DC1955307ULL, 
            0xD83351B3C767DE9DULL, 0x12EA17DD088BE298ULL, 0xADA00BE724A7A8C8ULL, 0x611B9A81EBCD7AA4ULL, 
            0x8562B1352DF0E398ULL, 0x879DF13915ABE5ADULL, 0x58730F3C7F58EDD9ULL, 0x03119D8A750B353DULL, 
            0xCF03754F8B82E6A4ULL, 0x6CD54B101B80EF80ULL, 0xDC1EB6988E9AFA56ULL, 0xBD363F29F1CB1C3DULL, 
            0x4ECD396CD7A8767DULL, 0x891C664C5FBDDCF5ULL, 0x04B6C0D1531D26C6ULL, 0x29F1987BF4D8138FULL, 
            0xB5EE2D646A8BD650ULL, 0x4C3868F0421C9038ULL, 0x1C56994816C09E7DULL, 0x79E2124975B4EB6DULL, 
            0xB5D9EE3EFEC5582AULL, 0x0D5F2188AAE309A8ULL, 0xE79A985B98E05B9BULL, 0x318503C5A1704DC4ULL, 
            0x0EAD896A507EDB85ULL, 0x6F97A8FA099FE1F9ULL, 0x15A6F9807E3CF221ULL, 0xACFA2013E5FA0C53ULL
        },
        {
            0x1346EAF60685EC99ULL, 0x6A1A6DFBFDDAE1AEULL, 0xF263369EC4AD4705ULL, 0xDD6300ECE21AB21AULL, 
            0x873567E59E2B1246ULL, 0xB760F64778E2501CULL, 0x410A1727CB021B48ULL, 0x7FF7F437A4EAF269ULL, 
            0x46B9979097A93946ULL, 0xBDC3E4ED1C8B6239ULL, 0xC27BEA10E8C8E42DULL, 0x881FD0A278E37A4EULL, 
            0x229A6771C6B6053BULL, 0xC96EE2483447150CULL, 0x50F3D800F5403E54ULL, 0xB5150C48213C634CULL, 
            0x1157AF097BC6CCE9ULL, 0x298A92E515C9C4A0ULL, 0xCB520BC6CE857713ULL, 0x85956CD18EB668ADULL, 
            0x932F080B23717A72ULL, 0x8497939D742399DCULL, 0x00475CCEE5399A63ULL, 0x4CE46E087863E116ULL, 
            0xBE5AD94A861890ABULL, 0x40B079C20105AC3DULL, 0xD2A1B01142941ABFULL, 0x55FB888D1FD19262ULL, 
            0x2244F8CE39AC6CA6ULL, 0xE0F05450959A85B3ULL, 0xA5A9EB2AE2E5DAD8ULL, 0xAB5B00732BFC0689ULL
        },
        {
            0x814CD99224899BA4ULL, 0xAD595E37648ED26EULL, 0x45273DF8D6D503F0ULL, 0x423A05E3B65738DAULL, 
            0x8CD5A671366929A7ULL, 0x33B24002B82501D0ULL, 0x28CAEBC9E979D07EULL, 0xC66AB9A5EB8B055BULL, 
            0x3A3E5D95BC1481E4ULL, 0x28B95785D26D58EEULL, 0x9D4CBCBB9E130FCCULL, 0xEF1B6431A372654DULL, 
            0xA3888B869A62E03FULL, 0x67E19B25758F0279ULL, 0x205D65E3D44DC4FBULL, 0x174AC37AF72EF943ULL, 
            0xB6EAB48642BD0522ULL, 0x5EF739F23E86E575ULL, 0xD1113EF1B9478548ULL, 0x1D6F6F2FB43F14DCULL, 
            0x90C5471B55B9ED0EULL, 0xB888187FC616CDCBULL, 0x8051018894D42B49ULL, 0xD1B40110D6BC2F7AULL, 
            0xC494BE5494519FF4ULL, 0xC4C5348802B44ADDULL, 0xC0DE8D945EDC6343ULL, 0x521B55C4025A2394ULL, 
            0x5B8CC19243AE725BULL, 0x42EB53ADBFC314C2ULL, 0xD730E8DDC256799CULL, 0xB7C222B6DA2EF390ULL
        },
        {
            0x20C03FAB50FE555CULL, 0xB22826C3E769A736ULL, 0xE9109E435836A889ULL, 0x965A6C2B3D2042A3ULL, 
            0x69510BC73D2497DEULL, 0x1C02B3E6B9347D01ULL, 0x1B9C61F749B55DC4ULL, 0xE8FF5C39FFA79673ULL, 
            0xAD6E47FC36BA860EULL, 0xF21F0844AF01E5A9ULL, 0xBF3E842E3FEE5C4EULL, 0xDA5988C73974DF71ULL, 
            0xA8686FA3F6694A82ULL, 0x95750A430F75F2D8ULL, 0x35A507CA31760924ULL, 0x8CB3FE232B0DAE5FULL, 
            0x90E5CF431243ACC4ULL, 0x4A684C6026D29DB2ULL, 0xF0558D4CC25B7B4DULL, 0x295158A89E5755E5ULL, 
            0x86AAF0CD80030592ULL, 0xAE37D343294216DFULL, 0x08A349C39BE81C83ULL, 0xE93B9862C5CDBA3BULL, 
            0xFD8C58A2A6F5B64FULL, 0x6C0C374C8303F44DULL, 0x6C15F5608C305FDBULL, 0x4AA2EAF4684C58B4ULL, 
            0x3480E7A4B54A9917ULL, 0x408A72981A4C001CULL, 0x24C8CD6AF89241D1ULL, 0x9D47385441670D0FULL
        },
        {
            0xE07623E3B585AB97ULL, 0x331899A3D7565A87ULL, 0xFB590AA82B4E01C9ULL, 0x4D9F14B8A71DB4A6ULL, 
            0x4FBB60CC09EB540AULL, 0x2E5076E552871886ULL, 0x31315BCB9321A8F8ULL, 0xBDF7093A8411338EULL, 
            0xB61E9520D1724895ULL, 0xA23E7AAA0960055AULL, 0xD8CC2862DD226971ULL, 0xE1E05F60A80AD3D9ULL, 
            0x0CDDB72DD9BF6C57ULL, 0x156A0B8E3E217F20ULL, 0x55BFAF9CBBFC18AFULL, 0x714671A8B375C45EULL, 
            0xF1CC8114FDC6F1DAULL, 0x5403C56411DC4BECULL, 0x3D7212F4C82B4937ULL, 0xED97DE5945545E98ULL, 
            0xC27D5E5F95DD5EC8ULL, 0x5660E26390C3B3E7ULL, 0x801C82ADB3113B02ULL, 0x669B63AD76FC4842ULL, 
            0xD0D801816704DC4AULL, 0x31A7B8B591FFB2F0ULL, 0x81A90E70D92619ACULL, 0xEE741E19184E854FULL, 
            0x160466FD98D36146ULL, 0xD9BE23F4DD91624CULL, 0x8160EE92692ACD77ULL, 0xAC2E547F7C1C6EC4ULL
        },
        {
            0x2C16B805CF365F4AULL, 0xF73B1D83C9B0D118ULL, 0x4AD2FF330B879F0EULL, 0x79E674B30E37E8B0ULL, 
            0x76F1768217CA902AULL, 0x210B86283965B19EULL, 0x8FD7D8BF82B7017DULL, 0xD2C8ACB970B4A871ULL, 
            0xC3C192EC22928C9EULL, 0x27FCECB3B3B398ECULL, 0xEEFCC6117AF87159ULL, 0x1F61C426E6F6F91FULL, 
            0xCB17ECB2B0AB1A47ULL, 0x60C7D21BFFF17C76ULL, 0xA9AD7620065806CEULL, 0x9F21F7BD12822512ULL, 
            0xD012A4C6FEDA6F4AULL, 0x50275E85ACD24830ULL, 0x4C20348FA616EB54ULL, 0xFE01A77FC68C97A8ULL, 
            0x1CC06DB2BBD30EB6ULL, 0x9F8149AA97491EA4ULL, 0x46F2811AAECC1C9CULL, 0xA43CEA0C20B0C575ULL, 
            0xAAC14CC80CB071D2ULL, 0x0523C3AFF26CD374ULL, 0x214AA32694E85ECCULL, 0xBC82185A841411DBULL, 
            0x8FCD41C4A3582242ULL, 0x48307029C5D4030AULL, 0xEE2E3D58E5B26006ULL, 0x8304697F90A67DACULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseHConstants = {
    0x23BA165687370D68ULL,
    0x1A5117A4BBD80185ULL,
    0x076017901A016E6DULL,
    0x23BA165687370D68ULL,
    0x1A5117A4BBD80185ULL,
    0x076017901A016E6DULL,
    0x375C2C3F6B5D17D5ULL,
    0x53ADA5C7105D302AULL,
    0xE0,
    0xAA,
    0x3E,
    0x50,
    0xE2,
    0xCE,
    0x5B,
    0xB5
};

