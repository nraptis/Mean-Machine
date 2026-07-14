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
    std::uint64_t aPrevious = 0xBDBFBBCE127C13FBULL; std::uint64_t aIngress = 0xF931E4C6D31E5A96ULL; std::uint64_t aCarry = 0xD56A27AC378BCF7EULL;

    std::uint64_t aWandererA = 0x9EDD12F3E924B414ULL; std::uint64_t aWandererB = 0xD93E0935F2032416ULL; std::uint64_t aWandererC = 0xA9CF372971039F04ULL; std::uint64_t aWandererD = 0xD6C8CC70C95F96B7ULL;
    std::uint64_t aWandererE = 0xE291E61C28ACA520ULL; std::uint64_t aWandererF = 0x90011B556C640900ULL; std::uint64_t aWandererG = 0x9F9BAC56E2ECE0AFULL; std::uint64_t aWandererH = 0xEEEE80FC7B827695ULL;
    std::uint64_t aWandererI = 0xC291BEB0B593FF74ULL; std::uint64_t aWandererJ = 0xAC318709893F7B6DULL; std::uint64_t aWandererK = 0xFB507106DF85FFE0ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14471278853555148686U;
        aCarry = 11878197901660732062U;
        aWandererA = 9804121491141602933U;
        aWandererB = 12801630016643290048U;
        aWandererC = 12394613771221281583U;
        aWandererD = 16299270784731588916U;
        aWandererE = 17448303575029842373U;
        aWandererF = 18417723757072917857U;
        aWandererG = 15683952757549837119U;
        aWandererH = 9528830968916476913U;
        aWandererI = 12380514419366387492U;
        aWandererJ = 15617618550949094992U;
        aWandererK = 17979800800135115186U;
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

    //
    // ---------------------------------------------------
    // KDF_A_B kdf_a_loop_b:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Bellatrix_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::KDF_A_E(pWorkSpace,
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
    std::uint64_t aPrevious = 0xAB2E186CD5DE387EULL; std::uint64_t aIngress = 0xDDC437A42517437EULL; std::uint64_t aCarry = 0xDD20BFCB18AADFC1ULL;

    std::uint64_t aWandererA = 0xE25680D3E6A93152ULL; std::uint64_t aWandererB = 0x9D68F9EA74F26472ULL; std::uint64_t aWandererC = 0xA124914BE701283CULL; std::uint64_t aWandererD = 0xB1BA490785F5DFA4ULL;
    std::uint64_t aWandererE = 0xB54C52B307DF3400ULL; std::uint64_t aWandererF = 0xBD67281A25C4F835ULL; std::uint64_t aWandererG = 0xFD441301D9E2B35AULL; std::uint64_t aWandererH = 0xC8AF3021B06BAEF4ULL;
    std::uint64_t aWandererI = 0x8965A5468AA1E718ULL; std::uint64_t aWandererJ = 0xE68D3889F8F97F98ULL; std::uint64_t aWandererK = 0xC6D68C9A6789ECCBULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17046603025171924256U;
        aCarry = 17138169496803553940U;
        aWandererA = 16618078026332996630U;
        aWandererB = 17523210543710093303U;
        aWandererC = 10857065400599040535U;
        aWandererD = 13906146634542083520U;
        aWandererE = 13052273610714885930U;
        aWandererF = 12341793864091172790U;
        aWandererG = 17136771818378526600U;
        aWandererH = 16192696954602754552U;
        aWandererI = 13951590042290716759U;
        aWandererJ = 13082209910707780696U;
        aWandererK = 12424386368235236035U;
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
    std::uint64_t aPrevious = 0xD7E8B604A1D2F861ULL;
    std::uint64_t aIngress = 0xD6C64D541C3E5B57ULL;
    std::uint64_t aCarry = 0x97DDB539534FC451ULL;

    std::uint64_t aWandererA = 0xBB9665E56681653FULL;
    std::uint64_t aWandererB = 0x8C57B93FC9960A89ULL;
    std::uint64_t aWandererC = 0x9FCE7D01C022D8F8ULL;
    std::uint64_t aWandererD = 0xBAF44FFC944FF796ULL;
    std::uint64_t aWandererE = 0xF6E7C5B376BD9ED5ULL;
    std::uint64_t aWandererF = 0xF051D06CC83897E3ULL;
    std::uint64_t aWandererG = 0x8B6BE2CD3D7E605EULL;
    std::uint64_t aWandererH = 0xCA03622A913C2757ULL;
    std::uint64_t aWandererI = 0xB9B36F2C443FE70BULL;
    std::uint64_t aWandererJ = 0xFCB8F87FBEEE2C36ULL;
    std::uint64_t aWandererK = 0x8F4FAB953CCEFD27ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_B seed_loop_a:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, earth_a, earth_b
    // ---------------------------------------------------
    //
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
    std::uint64_t aPrevious = 0x952BE41A2A58756FULL; std::uint64_t aIngress = 0x983B745743BBCDABULL; std::uint64_t aCarry = 0xCB0889070A9A4761ULL;

    std::uint64_t aWandererA = 0xE1A8CA9DEC4A2574ULL; std::uint64_t aWandererB = 0xD607F014956F4422ULL; std::uint64_t aWandererC = 0xC7B3FD7DA5D22BBCULL; std::uint64_t aWandererD = 0x80CAA3CCFA1A6BC1ULL;
    std::uint64_t aWandererE = 0xF53E89BDFD7177C1ULL; std::uint64_t aWandererF = 0xE0BE8E9BACA7BBE9ULL; std::uint64_t aWandererG = 0xDE8B3BB8464EBC81ULL; std::uint64_t aWandererH = 0x8A5EADDAF5D46851ULL;
    std::uint64_t aWandererI = 0xCED0563EC53C3374ULL; std::uint64_t aWandererJ = 0xE4ECB1A04D191A40ULL; std::uint64_t aWandererK = 0x8FC12268B05BFAB4ULL;

    // [seed]
        aPrevious = 13177612185211712136U;
        aCarry = 11164878983082652931U;
        aWandererA = 12535712186677214686U;
        aWandererB = 11844362627574335996U;
        aWandererC = 17920993788114879722U;
        aWandererD = 17474235444287816064U;
        aWandererE = 17550720322195645954U;
        aWandererF = 18296008843415916015U;
        aWandererG = 17326522697659316744U;
        aWandererH = 14634272429206217636U;
        aWandererI = 13025307232840393657U;
        aWandererJ = 16564015827513569143U;
        aWandererK = 12034493486348597015U;
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

    //
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
            0x4FECF63BD768F292ULL, 0xEF805E6C80EAF572ULL, 0xE574B8D7316F4229ULL, 0x8B02F34889FBE18AULL, 
            0xBC66BC52E1014B23ULL, 0xCB12BD3538140BA3ULL, 0x0662528A1F56C74CULL, 0xF10B99700B0595B7ULL, 
            0x86636E624861EFF1ULL, 0xCE62CF24EF618546ULL, 0xBF8F0C514D15CEABULL, 0x1E9EE153E94B3534ULL, 
            0x8DE1EE1D598767F2ULL, 0x2FD75C7AC4CA57DAULL, 0x8F454861231C1A60ULL, 0x460F84BD554214D3ULL, 
            0xAE51EA3F1E4BDC3CULL, 0x8A64D4B22A097723ULL, 0xBBC71D4A6519AD81ULL, 0xBA95B9A1332E2482ULL, 
            0x29AB70EEC29FEC96ULL, 0x1C3B2B0A1354A8D4ULL, 0x5C31DDD8C1946CF6ULL, 0x7BEF058EBB82CD9FULL, 
            0xD8436B3FB2AE7902ULL, 0x3DE90A747FCCF967ULL, 0xD4AB3647BD19EE82ULL, 0x5C971E107DDCE15AULL, 
            0xF271BC2695A525DCULL, 0x43591121771D0E80ULL, 0x3F7DCC9CC6D14690ULL, 0xE6B73AD3B81D8ECAULL
        },
        {
            0x21CD446B280B36F2ULL, 0x0FD7868CB750A4D0ULL, 0xC37D285B038D5039ULL, 0x70A52912C6AAB4A2ULL, 
            0x25ECD13FC99E6522ULL, 0x6E8604D559C3EDEEULL, 0x2F6E5EAA56B9BE51ULL, 0x00F04F791BD90FAAULL, 
            0x5F04FDF795D7AA7DULL, 0xD6449DCD1D50820AULL, 0x198B942C8C30E0FAULL, 0xF746840A6CE7FC94ULL, 
            0x838D61EC5021125FULL, 0xBCC8EC95D1BAA139ULL, 0x61F1B7DD979C911AULL, 0x075CB9C048A8358EULL, 
            0x844476D727A134D4ULL, 0x6022A6D0BDDA76D1ULL, 0x5C56C219EFE450E7ULL, 0x3CB43D0258F361AFULL, 
            0xB342311247881786ULL, 0x99B0F7096EF54C69ULL, 0x5E22E8C99D368134ULL, 0x39B4F315A33C07F2ULL, 
            0xA66C9BF9BDAE1EB0ULL, 0xEEB9BA4565F5A97DULL, 0x8682C036C75109ADULL, 0xC22E24C91F09B9E0ULL, 
            0x91C043A6784020C4ULL, 0xBF49D4F243276DF2ULL, 0x68E0453AA07E9D3AULL, 0xA52E394C495CC00EULL
        },
        {
            0x0A21DBA07D38964EULL, 0xEA5847D966D7081BULL, 0x06D4284B39115FB3ULL, 0x1E0047D4D6CAA7DBULL, 
            0x4793A8CB48ACEB6DULL, 0x96BECBB023EC88F4ULL, 0xA60B0D7C51E788B9ULL, 0x6B4F2ED06FD29999ULL, 
            0xA160F262D29CA306ULL, 0xCA3732FB13BEE004ULL, 0x08B9F91D9A28A168ULL, 0x3B964FC132A1DAA2ULL, 
            0x36A920DD9361C2A7ULL, 0x7B014070AD57E100ULL, 0x44566701ECFA7F28ULL, 0x475C91335C3B1AADULL, 
            0xC6488974FC7EFD72ULL, 0xBDA707BCAAB278D8ULL, 0xCF3327DFD2B41E00ULL, 0xBBC3822A25CF04D7ULL, 
            0x74EB56675A766925ULL, 0x1B00BAFA1CAF7A98ULL, 0xF8B02A403C5AB3F2ULL, 0xDAF161111B7929C3ULL, 
            0x7C910E891127A137ULL, 0xFB07F89D42A12372ULL, 0x90508DEB1FFA47EDULL, 0x7BF75D2F221C444FULL, 
            0x5BB62B58545C5BAEULL, 0x65321ACD3C9ADAD5ULL, 0xD2443C0E9FFDD7F5ULL, 0x3FA916C3E89E40E8ULL
        },
        {
            0xE3C9907BA17E47D3ULL, 0xA5A8444836EBF288ULL, 0x73B8CFB9AA8FB8C7ULL, 0x96A0E35AB094CA15ULL, 
            0xCCEBD5DBF97DC343ULL, 0x9BFF8C9B7DA8451FULL, 0xCEC5BE9024AD7132ULL, 0x2E559D41E9A09186ULL, 
            0x472E4B33D35C8F83ULL, 0xDAB730D38596D91AULL, 0x1FBA72FB24B8BF01ULL, 0x5F516796FAA08B9EULL, 
            0x294F64DDCAD3BAF0ULL, 0x3E9C664EF9F7E9E0ULL, 0xC119B846A5137519ULL, 0x9490109703428747ULL, 
            0xF82DCAED9B5CC237ULL, 0x5ABE92872EE14AC7ULL, 0x3FF1F7A6883A397EULL, 0x2903A533433885DBULL, 
            0x7B6485E725ABEF5CULL, 0x2A1CFEAD1DB4D943ULL, 0x41AD856F6CCB56A6ULL, 0x767AA0D885B96C89ULL, 
            0x359C45DD4A4C0B24ULL, 0x3A2364376A4B4AF3ULL, 0x366126C9FB56C6A6ULL, 0x343B955B1AF0C6C9ULL, 
            0xA67D99DC8223AF2AULL, 0x8C6E95E047AD4B02ULL, 0x7E2D1EDFB7439B22ULL, 0x73D4CD7717282F6FULL
        },
        {
            0x8A7D462B9EECFF93ULL, 0x087BE74F174A9032ULL, 0x202B76045F00530CULL, 0xEA149A64D11FDBE1ULL, 
            0x08EC9198F5089540ULL, 0x062C4F6497DF61ABULL, 0x01E2D0A4A9D63B80ULL, 0x3BDEBCB6A4A106B2ULL, 
            0x2AB6365907D2CEB6ULL, 0x89D456E251D623E2ULL, 0x2A961D5480311B45ULL, 0xEAF07E4BE0170D68ULL, 
            0x3AF07F0A5442BC2DULL, 0xA4D7BB230B50C357ULL, 0x08DB6D5E666253DFULL, 0xF69AA02CD13CA7B4ULL, 
            0x2320B0834BA14651ULL, 0x404084A239DF4036ULL, 0x9A5A8F09EA4CA502ULL, 0xFC275C04F9A81297ULL, 
            0xF7ABE4D71D07DCF5ULL, 0x6EE5455D07A3BE0DULL, 0x40766C8323E93EEBULL, 0x1336C9ED403C9DBEULL, 
            0x9912C6F8A103DD6AULL, 0x3D2DA59E71FA8BD9ULL, 0xDAC00415704C3F90ULL, 0x6D4EB6A23976DCA6ULL, 
            0x4165EB3C1D543050ULL, 0x381F320627584551ULL, 0x51E39B4E2D606CF1ULL, 0x97AE2C2083EF7D0BULL
        },
        {
            0x54DB3CC8B2E107E2ULL, 0x60669FABB27677EBULL, 0xB604E23A85F98AFCULL, 0x9CCA5DA3DE16E78CULL, 
            0x44A4BCE44DB1FE9FULL, 0xD1006ACE1DECB0B7ULL, 0x0628816B3C22C0FEULL, 0xD625D3A4CC7C240EULL, 
            0x4D41A2786BA93A82ULL, 0xFE1126724CFFFD29ULL, 0xC3A277182B32E64DULL, 0x1E0B5590B4F833B9ULL, 
            0xE3BA0A10A81B3929ULL, 0x58F49C86CA5B5447ULL, 0xF56E84B5EFAB56FCULL, 0x24C59BA6F78033C9ULL, 
            0x49ECEF14D73B006AULL, 0x6C675E143A0B10C1ULL, 0x9809FCB918246469ULL, 0x7627BB112EA42DA5ULL, 
            0x997AA463A68EF83FULL, 0xCDF454D514936C96ULL, 0xB73A16FF148EA924ULL, 0xC6C21B56FD414260ULL, 
            0x757952703DB02C78ULL, 0x9B74B47AA61BAE5AULL, 0x7D50610BC0859DBBULL, 0x58A2D6E5852CA7BDULL, 
            0x16FE087EDCE4E199ULL, 0x07308EDBAB3413AEULL, 0x6BDB735BB331743EULL, 0x7ED60726A08E617FULL
        }
    },
    {
        {
            0x6884B3D226714EF1ULL, 0x93338044EF91E5F1ULL, 0xAC311EAC44F684C1ULL, 0x53FF4E1590C284F1ULL, 
            0x07B5B1E590A1B607ULL, 0x5129EE8396E23F6FULL, 0x393E12DE2A56A6D6ULL, 0xCDD48781E3BAA2ADULL, 
            0xEE79E4C45F72DBB5ULL, 0xF47C3C40E44D661AULL, 0x61CCBF9135A21403ULL, 0xF476F60BF6BBF071ULL, 
            0x558BA8B5A562F53DULL, 0x0EBC54AD05262F6BULL, 0x56DF4B8E4E8A3F27ULL, 0x586BE6FB2B26E8F8ULL, 
            0xE6C6C44546C96679ULL, 0x208B9A8DD48724DCULL, 0x2EF23B6D2559A0F1ULL, 0x2280AAF8EE252A7CULL, 
            0xCF8122C13B831A68ULL, 0x8B442850BE5C59E2ULL, 0xD0558CF5DA9EC96FULL, 0xC5C0A33CA009D26BULL, 
            0x69D7CE4FB6AD1706ULL, 0xAE452407DB6F8778ULL, 0xE4E83682549EE58EULL, 0xB802826B12D2C839ULL, 
            0x1D7AD81C45FDE294ULL, 0x86C43DCE216F3BACULL, 0xC3A747B40FF343A1ULL, 0x3A6AA800517880B6ULL
        },
        {
            0x7313C5EE46DB99A2ULL, 0x96CCCB5A3780A0CBULL, 0x7370E24EABE7E2B3ULL, 0xA77269AC5371965CULL, 
            0x20B02C407D604B72ULL, 0xEE4F75ECE9687612ULL, 0x60ED860FD9969742ULL, 0x8BD17F010CC5938BULL, 
            0xFC7975B1219E225BULL, 0xD2733496BD05A98EULL, 0x7FD0D2070D3D0A9FULL, 0x8B78113087865DA0ULL, 
            0xF2CF7AA954A9C86AULL, 0xDA54AD6A66DEE485ULL, 0xFE7B99B79A3314E1ULL, 0x3C3D4D3AB43E7663ULL, 
            0xDE90BB88CC6CB66BULL, 0xBBB514832BF02388ULL, 0x80AC678F1779635BULL, 0xF4B9BB7FD7C1101BULL, 
            0xDDF1BBDE3E0F7463ULL, 0xC31FD34AF79696B5ULL, 0x1981294FB4C9BFE1ULL, 0x28CA63D8301C23FCULL, 
            0xC653BD177284A738ULL, 0xD8673321EE5E71A8ULL, 0x7777B4C6CDBE5CA8ULL, 0xE7BCB011DE428D7EULL, 
            0x16566D41A94AED6BULL, 0x2E2795B8DA2F5A53ULL, 0x15E564C06EB8C25EULL, 0xF2847B103A541273ULL
        },
        {
            0x59DDE1ADDDE2BFC3ULL, 0xF305D5351D42B837ULL, 0xF0EC8A95E764BD50ULL, 0x03931DD67A2A3C68ULL, 
            0xF9B894AC84BC8D53ULL, 0xA039CD1CD3FB4F15ULL, 0x6C7F52C161DEC801ULL, 0xA7158A48CB8A7286ULL, 
            0x74C796D72632AE91ULL, 0x19FEE6609E38BE57ULL, 0xE6EC7079E556A3A5ULL, 0x10675445E3ECB240ULL, 
            0x8BC35976BF246291ULL, 0x7AB6AA6378EE79C1ULL, 0x01D22F4F60B5B300ULL, 0x729EFF1AF2AB8C89ULL, 
            0xB99E5D7236CBC0A8ULL, 0x3B83EFA8E6F6502AULL, 0x9F66B389A4F201BAULL, 0xB1BE3BBECBA59464ULL, 
            0xB621C19E4DEACCB3ULL, 0x56CD78AC38F3E9D3ULL, 0xF0477D0B48B4B65CULL, 0xB2CDC65BACEE22E6ULL, 
            0x8C01EC74066B2627ULL, 0xE4B7048DDDA2F1FAULL, 0x705EEA514C298D28ULL, 0x057A73EC8C0744FFULL, 
            0xE44D8557110868ACULL, 0x80F38E5746B6B160ULL, 0x02802AF75C6120A4ULL, 0x2ABD442B34ECFA2CULL
        },
        {
            0x8E547BB9BDD89370ULL, 0xDD1037BF0D4230A0ULL, 0x59F5CFCF81AF41E7ULL, 0x0789FFDB0388095BULL, 
            0xDA91B21A13368484ULL, 0xA32D9A4E2F674361ULL, 0x358A80DAA62A8D8CULL, 0x6C6776A58A7F7D75ULL, 
            0xA3E87DF4B48DFA62ULL, 0x5051E90DE7FA2FD1ULL, 0x4734665407F20503ULL, 0xAA3B664FB8450798ULL, 
            0xF15BDDAD2F861F4EULL, 0x6DC3F19F64EDBA68ULL, 0x063392D698143411ULL, 0x421D57E25D33EC80ULL, 
            0x64B3FBF79978BFD0ULL, 0x0F29F57DA98187CEULL, 0xE0B0AC388DBE72EAULL, 0xBCEE29B3A1DEA7B0ULL, 
            0x527464558A34E252ULL, 0x8445CE4AE4D36E93ULL, 0x491C609755365318ULL, 0x3B296F6B5A7AFE70ULL, 
            0x055E309BB2475E10ULL, 0xCDBE2F9CA5A67565ULL, 0x3BB4B6E511DD1657ULL, 0x1DA1C5F617178B63ULL, 
            0x2F4E4B1A49ECA6A1ULL, 0x9E52B3EF66679CE3ULL, 0xCA3855F59908578CULL, 0x1ADA05F232E2D307ULL
        },
        {
            0x2920997CDBEA774DULL, 0x7980559428F1094DULL, 0xDB7B69DE8C8BB88AULL, 0x63CBC8A3619C335AULL, 
            0xEFA64DA78CD1C68AULL, 0x8EEF7457C66DB064ULL, 0xC1491D40E87A929CULL, 0x631D5858B94F3CC1ULL, 
            0x7490691977B30AFCULL, 0x9CD8CFAD51FE3BC2ULL, 0x64DF38C24E08D76CULL, 0x5CF22A6135116822ULL, 
            0x56D9C494446A2F50ULL, 0x6189379D3F334EC7ULL, 0xB0F54F8F48579ABFULL, 0x2AEE8EC1BF7682C7ULL, 
            0x3647F25F0378D75DULL, 0xB46634883A9ED073ULL, 0x59198A2EFE88C636ULL, 0x23C1C4FDB76C2E67ULL, 
            0x3EB8BF1E18F09FF1ULL, 0xF7C56FA86A5A2624ULL, 0x73BBB5930A7FF6AEULL, 0x5BA124ED79A780FDULL, 
            0x81F3A7D65B6B23A3ULL, 0x96B4BB9EA142DDFBULL, 0x522D9B2863C72433ULL, 0x832E08F8692959ECULL, 
            0xF2C93E7C982209CBULL, 0xD81497F0161A47B3ULL, 0x7722F63E596BD38CULL, 0x676230CAFD6E925FULL
        },
        {
            0x1AE9E06E5ABB48E0ULL, 0xF744E84D485C6F97ULL, 0xED939D57B9EF0FCFULL, 0x6BFE20F3F85CF344ULL, 
            0x757B99076C9E8A3CULL, 0xE5D0ACA5321EC811ULL, 0x7FE7F90734E5383AULL, 0xF7FFE4BE091C619EULL, 
            0x49813481C3067946ULL, 0x851F87425CEFF775ULL, 0x1C0D2B9E9C10BA7CULL, 0x9BA1E47BA819BCD4ULL, 
            0x78244F2C9C69FBD0ULL, 0xE1B0A7AD7A75B3D7ULL, 0x56BDD6F7E66008F6ULL, 0x2A3FDAB973F2078EULL, 
            0x158F64B4154F6C37ULL, 0x967521F68AA769EAULL, 0x9896D6A749348BA9ULL, 0x14CD9302292FCF13ULL, 
            0x2A7011136333A0F8ULL, 0x6929D11E1BF49064ULL, 0x5823D6C480421446ULL, 0x1774D6D62E3C90CBULL, 
            0x56C83337179CBEF2ULL, 0x42C75AAB83B8E4A2ULL, 0x4C995D7B27EEC969ULL, 0x404BC47EF5B56C6DULL, 
            0x1FC78B127EBC0764ULL, 0x71CF00D8AB4E1D1DULL, 0xAC73EF3D710A433CULL, 0xE2E4224597CBC7AFULL
        }
    },
    {
        {
            0xC807F7A409CE9FC4ULL, 0x027A69194C6AD259ULL, 0xF7C0144D3B0A24E5ULL, 0x97EC311B46A6883BULL, 
            0x82CD37CB4E96096AULL, 0x0EE5C0599A8CC216ULL, 0xFD7EEA07401B3CD8ULL, 0x0B3A50418B883499ULL, 
            0x7D60B6D6D5955A36ULL, 0xD12519EE9C2BDFD6ULL, 0xED37ED60F23ED957ULL, 0xA78351670612B3E9ULL, 
            0xD39242E38461C1C0ULL, 0x2F9E6DC38CE0CC3EULL, 0x39A997919D1644A5ULL, 0xF9FC591B7EE75863ULL, 
            0xB9B89C632CF56182ULL, 0x83F42EB8711DA319ULL, 0x900ABEF56A07E4F4ULL, 0x3E21F2175D1582A0ULL, 
            0x10298950942AAAACULL, 0xBA7652A2E951B621ULL, 0x98B3E4BA786114B6ULL, 0x3117712A48422B22ULL, 
            0x9200D43FACC26DCAULL, 0x6DA90202D09FC09FULL, 0x2BD8B57699F67A65ULL, 0x11D823A64F2D5705ULL, 
            0x8EEA2E418D1D65D6ULL, 0x762588853372402CULL, 0x0E7173F3871199F6ULL, 0x8B9C54FFF42BB978ULL
        },
        {
            0xDD8F19A22A36EF1AULL, 0xA44F0A59DD78409BULL, 0x6332F98F6BE915BEULL, 0x0B9F38076D45A561ULL, 
            0xCB4ED50050CBA527ULL, 0x682808A55658F74DULL, 0x0B2C96CA2A352E27ULL, 0x472096011B1BAAFCULL, 
            0xB5E52C6C5D759993ULL, 0x7FBE155C0B704F3FULL, 0xA6A5BF8B6A47601BULL, 0x98DB3DDB9D82A83DULL, 
            0x94F1DFC63EA0379EULL, 0x8E5EBF1C88434477ULL, 0xFD77B43A62A8E48CULL, 0xD406FCD0025904D3ULL, 
            0xD4165C8E6BF1487EULL, 0x057D636BA12D4566ULL, 0xFC9FB10175689436ULL, 0x3DEA4CD8F39FF614ULL, 
            0xE2FCB337B7C0B012ULL, 0x03F2F54EE9C73B3CULL, 0xA72AD19924FC2EC4ULL, 0x724E04E46DDE6A2FULL, 
            0x585842522155E4F2ULL, 0x5837F4BB3F305342ULL, 0x7AD47F32743C085EULL, 0x3017E3E3B68C8093ULL, 
            0x10744D693471F904ULL, 0x31E1F855912DAFA9ULL, 0x6CA662BCD15D0493ULL, 0x74CEC28EC2B9BC92ULL
        },
        {
            0x751D96EB7FE347DDULL, 0x445CBC22AA659042ULL, 0x84749E5E2FAC842EULL, 0xCC22A50C4A06B9CAULL, 
            0xE7A4AB11637570C5ULL, 0x70A890045174A23BULL, 0xF3DAB559AC73C034ULL, 0xF58BD7884F0BC07EULL, 
            0x61ECD60FE79D2E15ULL, 0x0CBB51AC99168AB9ULL, 0x5DF125D3A8C87ED7ULL, 0xA158C93A69D91B22ULL, 
            0xD73B2214B55C4360ULL, 0xA5C49DE21B08ACD1ULL, 0xC3BAE8779098B985ULL, 0xDF61E1CD5413D44CULL, 
            0x071F0B5915373FEAULL, 0x6780850F5090BE1FULL, 0x0C363ADC1D450775ULL, 0x10A601BE3A783E8BULL, 
            0x858E2EB63F9DBCD0ULL, 0xE05F2D22A3C6D8D4ULL, 0x57C286E8F255710BULL, 0x829ECDD33909DE24ULL, 
            0x5BC6B2953EEE85C8ULL, 0x160E15A1920EE321ULL, 0x79C1857CB9F3981DULL, 0x6F90440807EE108BULL, 
            0x447843D167E26A1CULL, 0x9995E41498DB91B6ULL, 0x4A457FAF95B6BC6CULL, 0x1683CEB6B31BD1F2ULL
        },
        {
            0x53077C462A223729ULL, 0x1BC1670DEA8BCC06ULL, 0x8D379A11AF9A8A33ULL, 0x13AB4BFA118BBE81ULL, 
            0xE345BD6D16180170ULL, 0x7333F1577A1B369DULL, 0x3C62C60B4531CF7AULL, 0xC6EAF83A29D92B68ULL, 
            0xCC4B9C33E4C4D93EULL, 0xFEAB7888DBB99A8AULL, 0x4C4A1F3EA42B5EECULL, 0xAB30C4780E8C807BULL, 
            0xB172281664E9D583ULL, 0x7F29604232586679ULL, 0xEA75E141F61C153CULL, 0x2FE0C992C9E192CCULL, 
            0xEB3BADCF9A4282E0ULL, 0xD772D7725530C8A2ULL, 0xFA61F9215D17E18DULL, 0x4D2C702CBEA575DEULL, 
            0x208F7ADA960EA1DDULL, 0x7FBFD28BD4761486ULL, 0x78C6B63933CF8BA9ULL, 0x24EEE3D592306DF1ULL, 
            0x300A6DD0738061B2ULL, 0xBA5F897A3B76D24FULL, 0x68FAC737981935F7ULL, 0x6210CACA60086872ULL, 
            0x34EF0AF846B27297ULL, 0x19122F8E161D0EF6ULL, 0x9DDC132F6FB65F78ULL, 0x67C5748D16EFEB29ULL
        },
        {
            0x619404DD7A05DF0FULL, 0xECD2A3D8E2390F27ULL, 0x641A219279BEE4D2ULL, 0xACEF8BF006645C69ULL, 
            0x7E69681282C05410ULL, 0xB82AEC752F08FDF8ULL, 0x058C3A8C5268E0DBULL, 0xE72C91E6ECEB1D1AULL, 
            0xA01EFFF477FF4494ULL, 0x10A040EF30B16A4AULL, 0xCCE63DDEEB9524F1ULL, 0xFD11B3E5DC9E0CC9ULL, 
            0xF261592E3734CFCDULL, 0xC28125B5CC29E1D5ULL, 0xDF353EEA2F3A126BULL, 0xDDF98F87A18C97BBULL, 
            0x652DE9ECC6D70285ULL, 0x65A78E7B4CEA92DBULL, 0x15CCAAAD6F940DE9ULL, 0x70C48AE2950A7FA8ULL, 
            0x4AADA21C18B6A5A6ULL, 0x1CE5BDB47A354E3EULL, 0x12DBD1A824E12B07ULL, 0x7540EE1E5474D699ULL, 
            0x40640A8D5347A5AEULL, 0x7D7F65F16E4ACA00ULL, 0x657058A74D44EA97ULL, 0x5D8796BC33E2499EULL, 
            0xC3B68D18244DB34CULL, 0xAC01C7C33178174DULL, 0xA8C2ACD49AC6CFB7ULL, 0x1905675C28C7BAB0ULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseAConstants = {
    0x889487F7ECDC6775ULL,
    0x288BD35C58732359ULL,
    0xCCBA979BFAEE124BULL,
    0x889487F7ECDC6775ULL,
    0x288BD35C58732359ULL,
    0xCCBA979BFAEE124BULL,
    0x9E45B2153A4C357AULL,
    0xEF467F00F6E149B8ULL,
    0x64,
    0xFC,
    0x91,
    0xC4,
    0xE5,
    0x39,
    0xA4,
    0xE7
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseBSalts = {
    {
        {
            0x49DF1A991F08819AULL, 0x3DEC714C23465672ULL, 0x3393C9181D62A2E0ULL, 0xB3FD58E9228FB99FULL, 
            0x515F80BCC0DFC47FULL, 0x2263EC9D630D4360ULL, 0x4B83BEC4C919FB3AULL, 0x136783AAA466E5C9ULL, 
            0x913341150196385BULL, 0x1AD1184D76237BD6ULL, 0xD835DDF570351AB8ULL, 0xD4387E05D2D07E22ULL, 
            0x4B9121011B45E4A1ULL, 0x97DDE3C991995E41ULL, 0xBB04EC4E03D30119ULL, 0x0E2AEC8F0B7C42D3ULL, 
            0xCA853B1E9FB0A3FAULL, 0xFFA9626D479BA9C5ULL, 0xDE3B30ADC4D0E4DDULL, 0x272F27B9690200EDULL, 
            0x4D677C21A7A24131ULL, 0x956AC52FC0D3AB0AULL, 0xF77963E9CABD1EEBULL, 0xEE52132E7CD491DFULL, 
            0xD0E01B2B9B6BB6FFULL, 0x1BB75C8A267955EAULL, 0xE96F7E9D28970AC3ULL, 0xACFA9D90D951301CULL, 
            0x34C72E3B381921DEULL, 0x97BE7DC022C3B414ULL, 0x42F31CF51A31BF26ULL, 0x1CF434A57BBBC6C2ULL
        },
        {
            0xFDDC63F476536257ULL, 0xDA6CA86536603938ULL, 0x4DE21072907CD1F3ULL, 0x0342B168E79BBFF4ULL, 
            0x5329934A6DED4073ULL, 0x2F4AA55ACF3AD821ULL, 0x807A6F35A8F12863ULL, 0x2E3E1039BA0692D5ULL, 
            0x7F47F5A31CFE284FULL, 0x48184D82B6E7D9FDULL, 0xF0E3CBF73C4E7AEFULL, 0xCC9237A16820486BULL, 
            0xA5A792DA91000E9EULL, 0xC01129760533F516ULL, 0x53FE196AC9AADE63ULL, 0xC75B1BF127F29E14ULL, 
            0xC72E1FA00312BF93ULL, 0xF1EE7659D86ECC3FULL, 0x5A529D1B2978F1A4ULL, 0xB73BFE51C426C3D7ULL, 
            0xD9D294C28EEA7BA7ULL, 0xC7B5514D256D011FULL, 0x9CBA769EDF3D0B90ULL, 0x93E9881CFF33C219ULL, 
            0x0D83AB86A3333082ULL, 0x4C9C3414BF1057F8ULL, 0x5C63AEE656FD5707ULL, 0x2859EB1A0519F117ULL, 
            0x58BDD29DF06A76DDULL, 0x175F07990D31B2FDULL, 0x648C0036CF77DD27ULL, 0xE407DEABB7BBC3EAULL
        },
        {
            0xB4842BA56C12A8C1ULL, 0xA1ED3C6D42AD2B5DULL, 0x38D2FDF82F451FACULL, 0x494C2184DB607376ULL, 
            0x7E5B75E4ADF81898ULL, 0xDC4309B93290FD50ULL, 0x095783DEC461FFDEULL, 0xEE9F192A27C32BD5ULL, 
            0x3447F54F958E58CBULL, 0x62508771F23606DCULL, 0xA623BEED51118F05ULL, 0x9D6421659C03B5C7ULL, 
            0x6EC3A1DC027E349BULL, 0xA29B1B45516ECDABULL, 0x1C4C5F2BC98CA78BULL, 0xC152D63FD5958DD5ULL, 
            0x0108CBBD420CDA11ULL, 0xFEE8AB93B09881C9ULL, 0xDC70A89CFEF4E975ULL, 0xB5567210BED63DF2ULL, 
            0x720F690A7EBCF97CULL, 0x99A438D6B05223A4ULL, 0x6AB59039DB3F5F07ULL, 0xEB331DF12C9EA53AULL, 
            0x62B2FCCF87BD8801ULL, 0x0A212BFDAAE1CE1EULL, 0x532FD59E0225B20EULL, 0x24AEA7DDDFCEB61CULL, 
            0xBC8857477C5834D1ULL, 0x8087E74026E0D26BULL, 0x6714038208BEED1DULL, 0x740E681D1397C6CCULL
        },
        {
            0xBAC75C8A88DC970AULL, 0x85C8D71809C10901ULL, 0xE19C9B532EC99AE6ULL, 0xB4375D90EFCEF035ULL, 
            0x32E5BF748CB95C3EULL, 0x31B28BEE1C680267ULL, 0x6C739AD9524D85F1ULL, 0xA755F5926303E36BULL, 
            0x0437486993567FBCULL, 0x032A831F5BCAA4B4ULL, 0xD5F60167DB93E676ULL, 0xBB8EB6D6FAD024A9ULL, 
            0x510B0CA27322DB32ULL, 0xBE461EBA9FBC622BULL, 0xAA3580DB76ACC325ULL, 0x5107D9269B96195DULL, 
            0x21819396CE427AF3ULL, 0x9A6F405E443EED7BULL, 0xB6ED2096767F8656ULL, 0xE0A5D0BD365C7845ULL, 
            0x4211B5A860B18AAFULL, 0x5D84774322D3A777ULL, 0x62E38C814D4D2988ULL, 0x390FCA89F691D1D8ULL, 
            0x5220E98DE32A6369ULL, 0x40FF359A51CA104EULL, 0x28C610B1F82FD851ULL, 0xFE05A34FED131467ULL, 
            0x58C9D206285E7D78ULL, 0xF1F011837CCF2C69ULL, 0x45F19E6B068C7ADDULL, 0x5569FD4ED8E6AEEDULL
        },
        {
            0x688CFBF9F64F1646ULL, 0xFAA0C8FBA04CE466ULL, 0xBEEB47B8D33093F3ULL, 0x7E3CDFDD3EBB16D4ULL, 
            0x8116ADCEDAE5F600ULL, 0xFFA8927E477D732CULL, 0xD66A2F48E6779EC9ULL, 0x9B21B76CA62B9F39ULL, 
            0xADB9EB6F376B7187ULL, 0xABACA248637A4902ULL, 0x556EF8D809EBBDFDULL, 0xA8ADD61FA127EE93ULL, 
            0xF901B83F40862335ULL, 0xC401C909E3D7C976ULL, 0xE1E7F19A19DF78D5ULL, 0xA0FB318519A27C37ULL, 
            0x00AD832938C4BC0CULL, 0xCE67CAF25D497FE2ULL, 0x31045743E369FA07ULL, 0x1A74944B0507EC02ULL, 
            0xAB5CFF4BD7AA422BULL, 0xA47279409113AA05ULL, 0xFA7E41B1521888ACULL, 0x13A36D1607A37CF4ULL, 
            0x2D2F0838895C1CB7ULL, 0xFB8253F88A3CECB7ULL, 0x12879DBF5DA0080DULL, 0x4DE10716420CD560ULL, 
            0xC7767DBC49A65D56ULL, 0xD05129A0C1D123E4ULL, 0x94D060F950264DF4ULL, 0x45C87A118A46DF73ULL
        },
        {
            0x72563253443DB78CULL, 0xE1FC2967DC5585C4ULL, 0x696272CE9B5C3D61ULL, 0xFC3EF1FB2F98492AULL, 
            0x83A9DAF1E0363E09ULL, 0x946D375ED69AD8E9ULL, 0x92EC7738E36AC3B5ULL, 0x9CEB9359017141EEULL, 
            0x934D238F6F779538ULL, 0x5660DDC7160BBF79ULL, 0xB7118EF7BBF881DBULL, 0x3D3C73DEC8D64368ULL, 
            0x35E6F7506704E23FULL, 0x44FCCF885FE43648ULL, 0x2EB7E92D1BC44248ULL, 0x74693DFC329754EBULL, 
            0xC39828034C206C17ULL, 0x647A2EB1983DA312ULL, 0x6983C4FF8357D576ULL, 0xE63009D5E2379424ULL, 
            0x0EC023E876729B0AULL, 0x7908B55B5E5E4334ULL, 0x4E0E25E285812298ULL, 0x69FDCDF18FF91B5BULL, 
            0xE3A07834BA13E8A8ULL, 0x1FF417DCA474255EULL, 0x0E6B58E9ACC466B2ULL, 0x106136505B489716ULL, 
            0x182F3AD17B1890ACULL, 0xCCA5143970A617A1ULL, 0x54AF4A169F9B204FULL, 0x11D329107151330EULL
        }
    },
    {
        {
            0x59EB041A284ED88CULL, 0x74056780857C4A09ULL, 0x28C76FB6135611DBULL, 0xA40D965407931E39ULL, 
            0xE309E39B534EB311ULL, 0xFDE3CBF6C8CC494FULL, 0xF1B88E3D146E5460ULL, 0x64B4390D56749D15ULL, 
            0x9F38D89D059C0381ULL, 0x01B9900E62F34EF6ULL, 0x0AE8FDB7E541E609ULL, 0xFCD10F81F22C470EULL, 
            0x6B02E0E226A5E0FFULL, 0x9AA014CEACBCF3AEULL, 0xE58416FE9C226047ULL, 0x20CADAF4B88B976CULL, 
            0x1656426B8DC112EDULL, 0x36632AFA90ACE8EFULL, 0xBA15BDE62D1A1CA9ULL, 0x47FD2B11E7673E89ULL, 
            0x38AC495AE994A3FBULL, 0x677F5A8A205328A6ULL, 0xEB3208E597F9A60CULL, 0xA711EE5923AF9F93ULL, 
            0x106662FC8A579393ULL, 0x04071B6C8B8436C2ULL, 0x026039ABB0CCC606ULL, 0x028B7E880760958CULL, 
            0x65B72CD1E625A01DULL, 0x6D9205D89239317AULL, 0x587C34712B94E0B0ULL, 0x5A6A243F3F03734DULL
        },
        {
            0x153CB19B01AF9DAEULL, 0x683C5D1CB7541039ULL, 0xFEBA10524D73AF90ULL, 0xE831132760532D5AULL, 
            0xFF9CE05010095CA6ULL, 0x1AE9B1BF9B9D4C57ULL, 0x3994DDB57B5C5E29ULL, 0xFD2462E5A5C3718DULL, 
            0x15411EEA54312D99ULL, 0x5A595C16265A223DULL, 0xC80F785C54A3949EULL, 0xD37B92B143D0C5E2ULL, 
            0xED62FED590AC3D09ULL, 0xB55CFAD8F502A8FDULL, 0xE275EC283769898FULL, 0xA849BECC18294B18ULL, 
            0x2A6FF1D94131332AULL, 0xE905A98C19C04E27ULL, 0x3BD8DD63464AE4C6ULL, 0x9C0D5C1C360CACAEULL, 
            0xB070A52C5FA1ABB8ULL, 0x0C5704E478BCFDF0ULL, 0xA1F5017215DE0537ULL, 0xD13A7749FB2C39AEULL, 
            0xC74DB2F4B2BD3A92ULL, 0x9112E8AF6CEE4EC1ULL, 0x78BBEBE09D9E6EBDULL, 0xC7A95A1701C14D26ULL, 
            0xCFDB7C864EC7ECE8ULL, 0xD416D90A6099EC6BULL, 0xEC20E4990A85690BULL, 0x2A1FBE35582D8CCCULL
        },
        {
            0x7FD9708423FA482BULL, 0x0773245E4F60505DULL, 0x505A915A2DB51CFDULL, 0xE822EE9017E51DA9ULL, 
            0x588EE2FB8B076E24ULL, 0x831E1FCA031645AEULL, 0x6A9140630677F4A4ULL, 0xA6BD65DFC04F51BCULL, 
            0xDEE4CDC54A23B448ULL, 0xB68AD47B5FD75DFCULL, 0x0D8D838746EBA05AULL, 0xF47010598A94095DULL, 
            0xA5CF1DDC8770155BULL, 0x5731348DE38FE7A9ULL, 0x6FC89CB7C421F1A9ULL, 0x20BB319D1400948AULL, 
            0x882381429169297EULL, 0x21871ABBF9E5A7B2ULL, 0x9B361FA526224BADULL, 0x5BA90E1C4D4F5EB9ULL, 
            0x615F73B49797847EULL, 0x6993B0AAF6B2C908ULL, 0xD1876EF4335A3108ULL, 0x7418845FC1FD1A41ULL, 
            0xA54023BC72D5E23CULL, 0x09AD54E0BFABB53FULL, 0xBE1735CFA8F2FF47ULL, 0xA4A42CECDC346F50ULL, 
            0x68B0E4415A5CA1D6ULL, 0xD030C5CF52CCA814ULL, 0x1818DE8E63A7CAE1ULL, 0xF654FCF66BBC047AULL
        },
        {
            0xD5A23663E2C895D3ULL, 0x6493BF47A6BC49EFULL, 0x4180C2CDDFE6F675ULL, 0x42CA3A34E35A56F9ULL, 
            0x421D12DFC50F70D7ULL, 0x5F80716315092F92ULL, 0x531A93EDBDFF0C14ULL, 0xB71F77C5DCA3A605ULL, 
            0x29676061DDC241EDULL, 0xEB3EA57E752C6D1EULL, 0x576652C5517EC646ULL, 0xF142E417D6B27A30ULL, 
            0x99B4C9F24D0C306AULL, 0x8CE0D277075719C5ULL, 0x1FA8FB3A1A58353CULL, 0xDD9E7E7DBA97898BULL, 
            0xEFBECA545F725D93ULL, 0xA177029323B89DABULL, 0x8CA79A2C482AEF50ULL, 0xFBFA52D929AF50C1ULL, 
            0xD884F670185EA59EULL, 0xB3C76E466D4B5A4FULL, 0xED0E6C058838F72BULL, 0x4B18F2FB6F119134ULL, 
            0x3B748E8BA370EE9EULL, 0x1AC24B9A036A31E2ULL, 0xD7C99502CA8AB10FULL, 0xB18B000150B402F2ULL, 
            0xA0DA4B2A09AD68B4ULL, 0x16DF96A44CC53C34ULL, 0xA8EAA938E63DF632ULL, 0x5AC21A354267E77EULL
        },
        {
            0xFC92BE893EB0488FULL, 0x1B752AAAFA66E775ULL, 0xF851B604D8021DE4ULL, 0xDC649BA9F5A49643ULL, 
            0xCE1F69C45795233BULL, 0xA66F64C71E79FDA2ULL, 0xD9AF1C428DB860C6ULL, 0xDBABDA1E0F5AB445ULL, 
            0xA93598E07890ABFDULL, 0xB5F6F4955EEB32D4ULL, 0x33AD4F9C5F3A7B9FULL, 0x8E149A5B1DAE8844ULL, 
            0xBC0914418E9F15BFULL, 0xD2B5D347C0BE2D9FULL, 0xC2DFD55DC594DFA8ULL, 0xBCB49D92CE71166FULL, 
            0x214937C7DEACF5B8ULL, 0x7B1D09D983E64E1DULL, 0x8FFB4922C45D304DULL, 0xE29C8571626B9046ULL, 
            0x3600D69E382D9EB7ULL, 0x33B899C17ED16EF6ULL, 0xDC6A0A11DCE7A222ULL, 0x35C1541D24FC3D93ULL, 
            0x4B7C4AEDD5D2EB26ULL, 0x9C2B32AC9C5F47FCULL, 0x55832751029198C1ULL, 0x1207403A2E415F94ULL, 
            0x886E09932B149590ULL, 0x08B181AAEF980C80ULL, 0x36FA048A240D2388ULL, 0xADF83BC77D4E6EF0ULL
        },
        {
            0xA33F6560FCE92174ULL, 0xD1572B00BDA52FD3ULL, 0x25F873D4BDE6D07DULL, 0x524E935F3594601FULL, 
            0x826FCCBABFF7C4FFULL, 0xC3193BD5A6C9FC25ULL, 0x3F1A7C652D6BB3C8ULL, 0x35550221CB33DEA1ULL, 
            0x89346D0BBDCB316EULL, 0xB4B9D42FB0BA0B16ULL, 0x2EE623919E9ACBEBULL, 0xF0143C6C0FA129ACULL, 
            0xFFD25E6A0E35D304ULL, 0xC4C0874A730F1B90ULL, 0xAD16C400CEF6DD47ULL, 0xEBD2E7BB20ACC761ULL, 
            0xCA405F0A5D6F390AULL, 0x17F0D0E55FD88341ULL, 0xD63E12A2F088275AULL, 0x8CFBA0F563D18276ULL, 
            0x781D8772D4A969C2ULL, 0xE0A38ECDAC377D92ULL, 0x8CADC36880493F94ULL, 0x3BC71F74800378ACULL, 
            0x67BE3442FBBAAABDULL, 0xED568FCC7AEBFC51ULL, 0x68CD8D8081995604ULL, 0x983F7E02C659015BULL, 
            0xBAF2F7C27F3A7D95ULL, 0xE28FE1F05264E326ULL, 0x71847DA73AA8F2C3ULL, 0xD964AE524D0C19E1ULL
        }
    },
    {
        {
            0x6461986DC4EB9B48ULL, 0xE19F2A5B6B78254AULL, 0xD2926DCE202BA1B7ULL, 0xD34359C0CC4D8F5BULL, 
            0xC331DA3487A8190EULL, 0x2A4EC9211C304117ULL, 0xE5DE295D2D97D702ULL, 0xCBB58D51CCCA9A95ULL, 
            0x2B238555F0471179ULL, 0x7312E0982CD7BBB3ULL, 0x7CC59EC486AE6CF1ULL, 0xC843D4C59CAE562CULL, 
            0xB7F09DA856E5B00CULL, 0x078B2B3115197AB1ULL, 0xD479BE53726BA2E1ULL, 0x8F56446FFE936A96ULL, 
            0x6A7F2B241B9866C2ULL, 0x2CB5F637E20F8468ULL, 0xF575A43C5537B6F0ULL, 0x752BAE11AD573B01ULL, 
            0x06F73CE9349A69F6ULL, 0xFCB24AE84D87B2E8ULL, 0x4610B6D2224F1F65ULL, 0xB63B4E2D6393D07EULL, 
            0xB7A55CF9DFC0C497ULL, 0xDDCC8406B46EDA26ULL, 0xD1EEF7EDF817416EULL, 0x781D55233396BCF9ULL, 
            0xBFA023C5C5962145ULL, 0x007DA44D6B44B349ULL, 0xA2BF06F84EEB4110ULL, 0x294941192D6A6CD0ULL
        },
        {
            0x6373A41BBE019B25ULL, 0xFF671037263715C7ULL, 0x3497A51445AA3B73ULL, 0xC42428538CCFE80AULL, 
            0x6D8FEF6F4D78530FULL, 0x8A68934F9B96AD7FULL, 0x44C26421383A13ABULL, 0x23CD953430E25DC9ULL, 
            0x50DDE431335B994AULL, 0x24A636D37A76718AULL, 0x20AE21107D012528ULL, 0x8F1A076ECE70578BULL, 
            0x7D05CF142998A2F9ULL, 0x62F4974C4BA07810ULL, 0x7435BBAC4513E380ULL, 0x40C6C3C4D6E6CF39ULL, 
            0x86EDA3B47984D39EULL, 0x48A3D905AACCE319ULL, 0x5BF290769251FA58ULL, 0x610F53C24A38D684ULL, 
            0xD46F04C10A55CF7DULL, 0x543B2C627655DB08ULL, 0x4C321C38A028A1ABULL, 0xBB69EA7CA025FE18ULL, 
            0xDDAA3E7D3DF9FFFEULL, 0xC99225D902426152ULL, 0xCADDE95CFC2F64DBULL, 0x50493D1B467C7315ULL, 
            0x647B92B026440839ULL, 0xAD5CE4A0ECAB88C9ULL, 0x2D34DFEB544BAB0CULL, 0xD18C2E53FF58639BULL
        },
        {
            0x35F080B06C02DCD1ULL, 0x7A7DEA52CFB0CCCFULL, 0xCB5BA748C796E663ULL, 0x6F72D4AD086ADD35ULL, 
            0x5500AF30523E88E3ULL, 0x27DC154E988215AEULL, 0x72218C567827807CULL, 0x441CC3CC313BD946ULL, 
            0xABC4B9B943B2124DULL, 0x7AD353574E5B484CULL, 0x1AB35095907C6F5FULL, 0x2393512B2440BC87ULL, 
            0x387F693C28CADA24ULL, 0x4C0467857C1B751DULL, 0x6D5AD60763CAAC46ULL, 0x9E12C7A2002A432FULL, 
            0x39C7CD1B3904A9CEULL, 0xD96A432FBA9291AEULL, 0x0AAB35566A2FE1D2ULL, 0xCCA2648DA526FF68ULL, 
            0x1F8925D23754E8BFULL, 0x5415E07FB7289B2FULL, 0x0AE6D85EEF206695ULL, 0xCB113AFFEDC6416BULL, 
            0x94007031C3A54C8EULL, 0xACBFA1BA707F54E8ULL, 0x654C20AAEF348175ULL, 0x859445398F877D4AULL, 
            0x7914833BE65F26D0ULL, 0x9C1607940D5383C3ULL, 0x5C412E2BE7033492ULL, 0xB310682381E279EAULL
        },
        {
            0x5C46FD33E0DB9020ULL, 0xA6097034CB6098D9ULL, 0x07F13EFB82108F78ULL, 0xF4FDBE8D13BC1BAFULL, 
            0x85C7249097EA7231ULL, 0x918C8A906E61DFB5ULL, 0xEE930A8C25651144ULL, 0x79D8DA94426E4893ULL, 
            0x140F5E13DA8891C6ULL, 0xE6E3F94C793407E8ULL, 0x72D88AB16D18CC9DULL, 0xCC56FDF4F871FA49ULL, 
            0xC9427DF74EA6FE77ULL, 0x0E282A8CC3FFEE39ULL, 0xD9B7692C4E73A00CULL, 0xD7FFB5E1D870B16DULL, 
            0xBA2AC0ECA0722972ULL, 0x41121631EFF49DFCULL, 0x25D33EE058899D66ULL, 0xB80FC598F9CA9F3CULL, 
            0xD9F496BEF26B3DDBULL, 0x50BB63D0DACBFDB8ULL, 0x2E4CD25CB0FADD36ULL, 0xBD975DE260ED7058ULL, 
            0x4EA1EEC23A601776ULL, 0x0B266BDBF5AC280DULL, 0xA16C8132D82F86B7ULL, 0xFDBCC08DE64A1FC1ULL, 
            0xE69F90AE3B63A279ULL, 0x078711BFA18E6E13ULL, 0x46168ED1B7B2770FULL, 0xB8C62CE4CE86619BULL
        },
        {
            0x9EF2E7623C885B18ULL, 0x76F76F0F5F22E0D1ULL, 0xD887309D7D9FA2D1ULL, 0xEB2FAC33754F70CAULL, 
            0xE36EA3D6C749439AULL, 0x6BD45080F506C854ULL, 0xC55F959784F0FEFEULL, 0x99B52AA6C77DF051ULL, 
            0x379F4F3A58B97134ULL, 0x41E8DC77523583D9ULL, 0xC6F6F0F74722E29CULL, 0x3335C606BC9D5237ULL, 
            0xCF236C2A5D6F5057ULL, 0xAE35D8D85D8B3801ULL, 0x58342AAB1F700276ULL, 0x2A79B48409249C5DULL, 
            0xC3D76EA99E245883ULL, 0x43D90D38612AD3A5ULL, 0xFFBD4E242F9F8DD8ULL, 0xB945BC76465EF2C3ULL, 
            0x8AAFA4D311E4BF52ULL, 0x4E43F34B72E980A3ULL, 0x792474DB1ED41DC7ULL, 0x19D28172AC972FE4ULL, 
            0xFBE0C14C85E2781DULL, 0xAC2DD9B8EF49C91DULL, 0x70B1E4D0745C003FULL, 0x338E089A70CA06ADULL, 
            0x1DDEF3B1FF2245FEULL, 0x8D5A4D565BDA68D8ULL, 0x59B96EA7E77398ABULL, 0x9C56D0C007CE9080ULL
        },
        {
            0x392D0048D458EEDEULL, 0x3ABF7D5EF66A1279ULL, 0x6505D5D12E83B4F8ULL, 0x8B43129DDE8530D7ULL, 
            0x14A46E8DB7F71B87ULL, 0x10CCA37E60C42CE2ULL, 0xC4A5C1520AD8CADFULL, 0x09E2D0B09605A6E6ULL, 
            0x7A8B83A7CB623B33ULL, 0x8BA5859C3D5C4B85ULL, 0xB4D57B25A2C893B2ULL, 0x85D7DED093B59736ULL, 
            0xDDB0F1FBDE26134AULL, 0x0624979342871C81ULL, 0xE7DB08C997E67F97ULL, 0x7ACD249D13A50EFDULL, 
            0xE947F467B1D5798EULL, 0x2B19A1E011455F5AULL, 0x7A04C3C1186A30A1ULL, 0xAAF8AFFE2FE88B4EULL, 
            0x279AEA353D8C3BFBULL, 0x0091FD8A38B25A96ULL, 0x73425B9DAB6D8DB7ULL, 0x7A88DD3BAB6F2922ULL, 
            0x11AC4961C5A5BF57ULL, 0xAE0E0E90D78BE7FCULL, 0xBF7F3AB883706210ULL, 0xDC843758ECE9A00FULL, 
            0xC9EAB2437970888EULL, 0x7814D6D8E0982F66ULL, 0x8E154A427DA38D59ULL, 0xC580787BFB08DA5DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseBConstants = {
    0xCBD705880FA08CB0ULL,
    0x411EBD7A4231C1D2ULL,
    0xDDBD0AF09670BAB8ULL,
    0xCBD705880FA08CB0ULL,
    0x411EBD7A4231C1D2ULL,
    0xDDBD0AF09670BAB8ULL,
    0x44A2010362758D9CULL,
    0xE56429E1187563E8ULL,
    0xDE,
    0x35,
    0x52,
    0xAC,
    0x6E,
    0x28,
    0x17,
    0xE3
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseCSalts = {
    {
        {
            0x448F496604917B5AULL, 0xECC5AE9B744A03E2ULL, 0x5C16A14364C04162ULL, 0x5D5A1C61C8BB4CB4ULL, 
            0xC1C9CE72C8FCBFF8ULL, 0xB0EB591F413B0C84ULL, 0xD0119A51675709D4ULL, 0x3CF5EA64B6871C62ULL, 
            0xC3C8C5740E40C5DDULL, 0xC1F2E41E52C9BC50ULL, 0x45FBE4C8C259E3A6ULL, 0xBE5EA1BC53944A9AULL, 
            0x6CEA97E4AAEC9F32ULL, 0x3C43267996D526A7ULL, 0xBF5B1E7B30D007B2ULL, 0x378E905BB98C1D5CULL, 
            0x14ACF0D3CFB7D8F2ULL, 0x4A6C86CF16E4AF07ULL, 0x84F9354D44C7D574ULL, 0xD21246FC1BB81536ULL, 
            0x8D16A769F47B1B2FULL, 0xE1814B1E8AF44F24ULL, 0x05DEE126005CEEF4ULL, 0x836CE5F23BC5F667ULL, 
            0x1EA8A3F5703CF770ULL, 0xD70B5FB67A8E1BE6ULL, 0xE5BB0E08E848C8BBULL, 0x167D87C8309A1D33ULL, 
            0xD3D312D9DE6B33DEULL, 0x951D8FB4984B4DFBULL, 0xEE3F4203B66D1593ULL, 0xBAB83DBC4F5F0BEDULL
        },
        {
            0x9B23DDF2F3234BF5ULL, 0x56F77D3E41EF3D52ULL, 0x520FBCB7114BB407ULL, 0x409D93B6EC3DB986ULL, 
            0xA874CFC34FB0193CULL, 0x5781F80ABA7673ABULL, 0xB3821B135CE1CB2CULL, 0xD1A6DAEC073877C2ULL, 
            0x247148E0FCF1FBF3ULL, 0x39E76411F6526A78ULL, 0xA845CF38AEC9AE9FULL, 0x07E960B4FF9A9C5FULL, 
            0x707E766891FBB47BULL, 0xB84B3F1C0717356CULL, 0xAFE8721F14575A7DULL, 0x6D0ABDE38B8B95F4ULL, 
            0x068E5E4361464925ULL, 0x499799FA4A68995AULL, 0x3E9E5DC12A455330ULL, 0x9F3A25C5FB4F5691ULL, 
            0xDE98B7B179106A1FULL, 0xB059B6BFBF9ACA97ULL, 0x07FE35651E20CB98ULL, 0x39E89BAD85097E8EULL, 
            0xF9F8A59704BAAB11ULL, 0x192CCA365DFFF6CBULL, 0x38A3D3EB4718BF07ULL, 0x459FD724166EBA0AULL, 
            0x9A578892490EE098ULL, 0x4920375BB2BB4039ULL, 0x91CB31DA17080F67ULL, 0xCC142B87A01B83FEULL
        },
        {
            0x62C0726F6F5DCEBBULL, 0xBCA9A7E890696D51ULL, 0x8F83C530B8199D3EULL, 0xD1AE756DE09745EFULL, 
            0x4FF271F83131F28EULL, 0xB04713F5F85A77B3ULL, 0xCB4C7201C2527AADULL, 0x2262645ACA8AFAE4ULL, 
            0x7E4B56E073C54282ULL, 0x02557BEE7F0E1191ULL, 0x5D55264C96E3BC7DULL, 0x1771FC5B70F4EE1AULL, 
            0xFC1E0D57202D231DULL, 0x0B59386711F764D8ULL, 0xB7A9C49532315CF9ULL, 0x7159E84AB5C65EB4ULL, 
            0x15B91BEA1DC54952ULL, 0xF633D9669472CD77ULL, 0x0F8F798FFC275507ULL, 0x8FF7B8DE0423B797ULL, 
            0x8B1664D64039C8C5ULL, 0x29293E992D83AEB9ULL, 0x5F17A1BBFC2A6227ULL, 0xA74C578883357269ULL, 
            0x978FF69EC511989DULL, 0x2056B85DD639B0C2ULL, 0xB533916272A8880AULL, 0xCE13616F08295F5DULL, 
            0x87478C73B7222DB4ULL, 0xC84F53D3CEE3B1BDULL, 0x11A66065CA0E9B35ULL, 0x1F399D4FBA7045DAULL
        },
        {
            0xBADE18617E59B1CDULL, 0xFBEA483A67D9A2C6ULL, 0x19E675105552FA61ULL, 0xF4F811D4A07887A0ULL, 
            0x1BE002DC0F3CC306ULL, 0x1863D4786B95FEEAULL, 0xAE6E312FB7327929ULL, 0x22B983135EC0C5B7ULL, 
            0xA78D0D96013F39CBULL, 0xAAD62FC6C3DD18F1ULL, 0x13C2C45DF7BF9F3DULL, 0x5E1102A1A0BB8DA6ULL, 
            0xF7F2974FD88EB51CULL, 0x2AA3832E33A92305ULL, 0x78AA6B7787F2D222ULL, 0xA38A75DA4A77C04AULL, 
            0xE33449321C2BE78AULL, 0xC0DA236771F83EADULL, 0xFE3097DA397D65D3ULL, 0xDE0E62538864D590ULL, 
            0x7B95C721467B0152ULL, 0x7300D66814F04438ULL, 0x1C3948787A5995F5ULL, 0x9C29141456A4CF79ULL, 
            0x4535C6F7F431BD1BULL, 0x115623597E8C7BCEULL, 0xFA8A91AAC4B07125ULL, 0x48C087937024AB8CULL, 
            0xE04DC4437109BED5ULL, 0x0AB872A6E82E7B01ULL, 0xCCDF8D03E6784102ULL, 0xA875B80349F817ACULL
        },
        {
            0x3BEC56719F1DA244ULL, 0x007598D5650D8C53ULL, 0x0835ED25A303FE57ULL, 0x805518C8DDC9D3B7ULL, 
            0x2A5459BBB1333C79ULL, 0x1C1CC2692CBF46E3ULL, 0xFE6DF8D701959810ULL, 0xD5237EBC699B136FULL, 
            0xE95106DDDFD493D8ULL, 0x3D779F16F6DA311EULL, 0x563AC71683C14CD7ULL, 0x76BAB2B2BD8F5FE5ULL, 
            0x27899D77E6BB4829ULL, 0xE6983225C050AC54ULL, 0xA443C15ED6DCC0F5ULL, 0xE1B8C6F0F70144A6ULL, 
            0x3C10E25A85815868ULL, 0x3E4719F146A387F4ULL, 0x1EE5C66E7F7A86C5ULL, 0xFF9D03FFC5F2587EULL, 
            0x8DB5D1AE5BA5C05FULL, 0xBE736F2DCCC27A90ULL, 0xDDBCA27561B89351ULL, 0xBA7C642331B9C8AFULL, 
            0xD550B70DC6EFABDEULL, 0x9DB9F3977018046DULL, 0xB2F87478BC3276A8ULL, 0x570913E86A5EF6D3ULL, 
            0xBC1F937C5C9BBD66ULL, 0xEF39DB6D74C2F616ULL, 0x3B7DFE74553B9C9CULL, 0xE0CD7A46DEF53612ULL
        },
        {
            0x955298AB49A48D45ULL, 0x1C3826DBB75D028EULL, 0x8DBE3F7533E1C730ULL, 0xC6BE640640C2A8A4ULL, 
            0x9D9D62A5BE8F7F05ULL, 0x32C86F5063BED9C6ULL, 0x35A37CEDCE07D652ULL, 0x7D0F3CE28E11D71EULL, 
            0xCF72BEC5F6E0749EULL, 0xB9BA9C40090D7DAAULL, 0xC1612E122CB9E7CAULL, 0x32A140E13747D664ULL, 
            0x54C4119168B367D7ULL, 0x884AC55EDA3A5F72ULL, 0xD9C1088F1602AC1FULL, 0xC36167394D4F332AULL, 
            0x5F87AA918F3589F7ULL, 0x0593D568CEBDA33BULL, 0x9BE2B2F1D687F85FULL, 0x1084A0F774AD802CULL, 
            0xBF383A7673A6C038ULL, 0x5D498E2BF396711DULL, 0x21AAA5DE832AC1AFULL, 0x9DF3FA384ABA7652ULL, 
            0x2B6623A3CEB5F100ULL, 0xF74EC64781205A33ULL, 0xD59BA8E8CE4FA8FBULL, 0xCC8C034B632A057AULL, 
            0x4150F03CE4845D81ULL, 0xD66D97891E9B4769ULL, 0x0B6900EA36F5BC89ULL, 0xC96AFC26C061500CULL
        }
    },
    {
        {
            0x924F2E191FF43373ULL, 0x9753E364037E8A74ULL, 0xCB5C1CF3808EBA4DULL, 0x5EBCD5D16BA6181AULL, 
            0xF79495DE52C30B24ULL, 0x3F5CFF3E771B2F7DULL, 0xEDACC5C0404D1561ULL, 0x8F63BCE57B589618ULL, 
            0xB06F915D04FBFF01ULL, 0x8014A07AA5388E89ULL, 0xAD3ADD6E92B8AF49ULL, 0x99B97E619309E46EULL, 
            0x3C0E1DF858149B34ULL, 0x895E0B987141DC03ULL, 0x2504E484C2858D2CULL, 0x9D443867BBC1039CULL, 
            0x0DE182F1A68A77B5ULL, 0x9BAF0DD40667D53CULL, 0xE0C6021A284AC331ULL, 0x0386A1D09CEF8D0AULL, 
            0xD611D88907A06BDCULL, 0x6C918874D33E6A7CULL, 0x90543AF4191D3E6DULL, 0x51016182F798E34BULL, 
            0xF0A82151475433EBULL, 0xCF91F33AB6450B4FULL, 0x5A8A6ED04021F6CAULL, 0x2BDF9E0558DB8B43ULL, 
            0x70FEA38C6B743947ULL, 0x41DFD7946E063E4FULL, 0x4CBD58C304D5A64FULL, 0x30B340BC7898FB4AULL
        },
        {
            0x3641C2D7A1CF39D1ULL, 0x26E46397D1520F28ULL, 0x87A848448976CA56ULL, 0x5442C30F1222440BULL, 
            0x7AA195B31B4D554EULL, 0xAAB48BAC8278971EULL, 0xF3B9ADFDB1E0D681ULL, 0xA15E8BF70810AEB8ULL, 
            0x913BBF7BA56257FEULL, 0xFD349CEC6972A9DAULL, 0x1B8D5AEB7BD2C15DULL, 0xC26DC81297FDB0F1ULL, 
            0x5AB9B29642E90546ULL, 0x183AA59BF2F29975ULL, 0xB662B566E3771894ULL, 0x0A50844494C907C6ULL, 
            0x4965D4EA9C96E6CCULL, 0x030663AFAB56D55EULL, 0xCD6A4B47E88687CAULL, 0x323EF9A135B7BBAFULL, 
            0xD76FAD3E48CBF16EULL, 0xB878E932B339EB2EULL, 0x0F8B7D2E0B2A2C0AULL, 0xA5653EF6ED409306ULL, 
            0x95F28F65FCED6CE9ULL, 0xB798665BCE38B835ULL, 0x37A4657FAFC43213ULL, 0xCC02BDB7091E81DFULL, 
            0x3216E0C8D2EB3322ULL, 0x26814163EB568C84ULL, 0x1760A08A54B5C6A5ULL, 0xCEA7594D5B1F693DULL
        },
        {
            0xB54707AA4ACC3A90ULL, 0x79D0B12E9B409C65ULL, 0x5D235C9E8670EFB0ULL, 0xFAAD759BEDE410AAULL, 
            0x448C935072AAD8B0ULL, 0xF2DA79D54FB7E525ULL, 0xAD150D74460CC74FULL, 0x826565C7EDB4BA7FULL, 
            0xB102CCDDB444500BULL, 0xE9FB4952ED316121ULL, 0x02947C2F90C0C8D5ULL, 0xBBD4FDDFAAD8F6BDULL, 
            0x51672A7657F7682BULL, 0x0E2F008AA7B4C006ULL, 0x2C317F19EF5D26D2ULL, 0x2AEB766325BF161EULL, 
            0x6E400120E62F6FB5ULL, 0xF045118B712CD41CULL, 0x5DA903434831311BULL, 0x2C108AC024251D5BULL, 
            0x0F64CCF2F133533FULL, 0x7A09018BEEFD1202ULL, 0x6C39685D0A8B0CE7ULL, 0xC80AB5A8A33F64A0ULL, 
            0x128438A9E0194CC4ULL, 0x9E5715E760E06DF5ULL, 0xC7DB6B701F57FD61ULL, 0x62D79780AB79D15CULL, 
            0x2BC2BFA9B56EEB00ULL, 0x8897EAE3106D9124ULL, 0xD6E763E21A0CC1F2ULL, 0x03A57330DFD430CAULL
        },
        {
            0x3CAC49762598A925ULL, 0x7432E6EDEEC0969BULL, 0xE7A7F2CE210547DBULL, 0xF32313C786F48337ULL, 
            0x546C87A7AAC59FC1ULL, 0x426E0411D2A81BF2ULL, 0xC261E6743E2B1472ULL, 0x28D9548140793DE1ULL, 
            0xC4D8BDA60AD1FC03ULL, 0xB4AA18183E300C22ULL, 0xC291C32BA34E9EE6ULL, 0x91573AAF94FA2C2CULL, 
            0x036160AF483269CAULL, 0x13D5814D3E24B5FBULL, 0xBDF73D4C79864A57ULL, 0xB508ACA65B7926C9ULL, 
            0xD3D008B8F05C85FCULL, 0x6815AFB5AC897388ULL, 0xB44CF749B59F73CAULL, 0xC03CA6DD6670CCC4ULL, 
            0xBFF7B11993F3B900ULL, 0xBE1DE92B6DD4985AULL, 0xCADE9754E9E317E5ULL, 0xF40428CE5D709D9CULL, 
            0xCCF743236D3D21E4ULL, 0xB4BA314FB9E4BA02ULL, 0x72F0A24C7F248A1EULL, 0x658B08F4504F1E6EULL, 
            0x72C8F1ABEB6BD71AULL, 0xE8E4BDE7106372E6ULL, 0xD2B18E56C976FF75ULL, 0xD158E9708236C15DULL
        },
        {
            0x6E148EF273294025ULL, 0x258B47DA2C6C1B37ULL, 0x5D44BAB9825DDFF3ULL, 0x29EE7EDB9A587789ULL, 
            0x65D3360BE3037E8EULL, 0x905FCC9A7B4B5A2CULL, 0x369C7EACBDC1ED59ULL, 0xA828094943C91B1FULL, 
            0xFEDE6FC66326F64AULL, 0x04434ED7A0EC64BEULL, 0x398FDA55245FA11FULL, 0xC0D96D6548B1C94CULL, 
            0xA23E4253A7D0AEE3ULL, 0x6F85A0B7B23CC836ULL, 0xF1EBADD8F7C3397AULL, 0x57CFCE5940EAB23AULL, 
            0x4F8BDF167B09BE2DULL, 0x3DFAA72E68B9E0DFULL, 0xBF6418C2C7C9B2CCULL, 0xA105AB10C157156CULL, 
            0xB10B3D39417812AAULL, 0xEB8F91812084E3BBULL, 0x7CCE302C1A58B25AULL, 0x0FBC0EDB2B2BE610ULL, 
            0xAA9B8D6FFB97D167ULL, 0xD741710713C9EC3AULL, 0xC89D45CF4A7E23E7ULL, 0xB28F8C19DC7C150FULL, 
            0x1D73167F8825D14FULL, 0x134DBDFFE2E3E055ULL, 0x0497E79BDCBC2A7FULL, 0xDE45D7D8F7F2E50BULL
        },
        {
            0x9D0B675D7B8D1966ULL, 0x8BCDC2E09730C8BDULL, 0x357041BCD95D6171ULL, 0xA7C561350AEC35C8ULL, 
            0x2B3F76C9B5600A9AULL, 0x7C2966EC3241AFBAULL, 0xAA50A9AE66F3825AULL, 0x1CDBE60751D49B0DULL, 
            0x4E9F300496017942ULL, 0x7FB6F408CD6B7F64ULL, 0x785B622050BA0A63ULL, 0x7C5CC1CE146501BFULL, 
            0x67399EC14B399F23ULL, 0x1640F5C6DB55D2F7ULL, 0xABF276833732C286ULL, 0xC21ED39532EF08F7ULL, 
            0x8FCE4F90749A8820ULL, 0x216BF8491150BDA1ULL, 0x4A1EB5D967BFE344ULL, 0x42A959E80FC1D93EULL, 
            0xE098EDF30D215E11ULL, 0x9273BE551F8D1D41ULL, 0x57B4720AB487C888ULL, 0xED089B1C737E9CB2ULL, 
            0x5B6293F2E65D4C40ULL, 0xF4950D2F04FEACD2ULL, 0xE804CE86C9E519CBULL, 0x8A984979DF054209ULL, 
            0xC5533229110E3984ULL, 0x18D8361C0FD3708EULL, 0x76ED8ABD7DDC7D3FULL, 0x741CB37D554592E5ULL
        }
    },
    {
        {
            0xAFEB1147D2F2271FULL, 0x6665F17322C75DE3ULL, 0x562CD4A490471FB5ULL, 0x713E2C123468318CULL, 
            0x782EE80E6E3C6758ULL, 0x1BF1B42D7DC05F4CULL, 0x248DB43BA9213FF6ULL, 0x829A258D38B30E84ULL, 
            0xD086D845362DBC69ULL, 0xE6FDEBAF300A16E8ULL, 0xF05F49FD84AF1CC0ULL, 0x5FB2F04DD486A630ULL, 
            0x20380A2F00BB6592ULL, 0xE61C8E06B226DFFBULL, 0xDC8D916AD526E18CULL, 0x189A030A993829CFULL, 
            0x8E1A57D3EC63DA29ULL, 0x559C4B1DD1574A9EULL, 0xD15984B4C60A9EE0ULL, 0x37F71F12B9F7F8A4ULL, 
            0x214D0B89CC6C548FULL, 0xE8077E9F1031A712ULL, 0x6EAB8940E7E36D6CULL, 0x2A1FD8AA3E0A2846ULL, 
            0xA46D7367C34EB6A6ULL, 0xA7DAA9C27C5F280BULL, 0xDB0F903FBDB9F3D0ULL, 0x9392D033C2AB119CULL, 
            0xEA83DC66A5E70148ULL, 0xBBB61593D278E5CEULL, 0xC473438CB6290910ULL, 0xF1EE9B06E5F10EF1ULL
        },
        {
            0x2E60A8E7E8F19A2DULL, 0xC40FC91903F8AA3DULL, 0xAAE2E19CC34206E0ULL, 0x42582F50D197D1E4ULL, 
            0xAFA223080AAFB4BEULL, 0xD6A34763E0D086D3ULL, 0x6E3A3C762FF38C99ULL, 0x62EE0CCAD7F2E910ULL, 
            0xF17A31C4BAF90079ULL, 0x7DD3E0C0620E3124ULL, 0x7A903C981BD815DAULL, 0x39F08B7883E2E1C7ULL, 
            0x33CF98BF0770CCB7ULL, 0x6C64DE024748BD8DULL, 0x5D11D29E87422B7CULL, 0x00E52F0FD6B4797CULL, 
            0x437BAD01F6A56078ULL, 0x715C79F9AD6697C2ULL, 0x39E2BDE482A74AC4ULL, 0x6C1E155E9D1934F7ULL, 
            0x3B290A479E365733ULL, 0x0AE36A6976D577EFULL, 0x67744E2385B1B4CFULL, 0x0FC68184BD9FC503ULL, 
            0x962591DFC7A39DFBULL, 0x3AD08EBEC1AA3661ULL, 0x6FE610F113D84DC9ULL, 0xA26B53DEA83A4132ULL, 
            0x04551903828E2691ULL, 0x0D7B5F79CD220DD4ULL, 0x2C24A2A27BD284C2ULL, 0x8C07535B60435820ULL
        },
        {
            0x9857224C53E299BFULL, 0x56B6AE8E8E97C795ULL, 0x6F4BD34FCFC5E107ULL, 0x74C1F138F5586D54ULL, 
            0x9D54964AF4074693ULL, 0xBE6DB37802696B9EULL, 0xCC1C2DCC1B0453F4ULL, 0x3754E233EA3D02E6ULL, 
            0xA38B0C44FEBEA108ULL, 0xAD983A5507A0F765ULL, 0xE0314206B800F384ULL, 0x2993E3E94DEFAF90ULL, 
            0x7CB9D43F19C1D26FULL, 0xBE7899CC7B053094ULL, 0x610F1AA845D7E13CULL, 0xDDF21369B1C46E2DULL, 
            0x7B436AEB03463B39ULL, 0x9BF0D1CBF5B155E2ULL, 0xECF70FF614317F22ULL, 0xD0ADA9663AAE5ECFULL, 
            0x3FCC81DBECA48139ULL, 0x2D444CD4DB54FF45ULL, 0xE18FBBF7F7F36F20ULL, 0xFE54299D1F2F3B00ULL, 
            0x62CF08D4A328825AULL, 0x11F6740A08179DF3ULL, 0x8B9BAA771BBE9560ULL, 0xC07D6CF61CB6CB3AULL, 
            0x19BA88653A920A63ULL, 0x47A2D95F18C6EC2DULL, 0xF0AE783358E98C4BULL, 0x5F959EFB2F185291ULL
        },
        {
            0x0E14BCA0CF9957C9ULL, 0xC83D034C8EE9DC75ULL, 0x9A4A872F6E6946E2ULL, 0x4E77E6BDD51227FFULL, 
            0xC4ECE26C6FF8DFE2ULL, 0x4E88F4851B314EBFULL, 0xF46DA715D402BFECULL, 0xAE4EA55CED804A2AULL, 
            0xB5ACD90A3840AFF9ULL, 0xA6D21A30E7648412ULL, 0x1C0A3EF687FC60A3ULL, 0x2D12AC2D7451E5B1ULL, 
            0xF84F7A41C6341A61ULL, 0xFDF118D3436BC49AULL, 0x3B53F06F0A75A34DULL, 0xAF4F67FA7E1A6FADULL, 
            0x5C0AEF6CEC581BBDULL, 0xD0D6CD0DD1230C88ULL, 0x32171950557CD6C5ULL, 0xC71C4EE02A60C617ULL, 
            0x373C891BE4EE1B4CULL, 0xD08C32490F8FD790ULL, 0xF329A737AAAA1B5DULL, 0x66EBC11ABA28D3CBULL, 
            0xB711E59CF992970AULL, 0xA9F4FA2D2D85D13CULL, 0x54BB9C51250626B1ULL, 0xD698B1ABB95BD027ULL, 
            0x5307D8BEC137C4A6ULL, 0x7707958254EAF711ULL, 0x7CBAD50127DFB6EFULL, 0x9D8B7C7471479AD7ULL
        },
        {
            0xF74B7D6F47EF1B61ULL, 0x916BE8C738A5BF7BULL, 0x98758497296A2052ULL, 0x26FF43127E50A92BULL, 
            0x00621F10F58FFA8EULL, 0x314BC83A1E69B6ECULL, 0x6BF864D2F6B459AEULL, 0xFA98D8738A3B3EAFULL, 
            0xE97C502009CD1EA3ULL, 0xB6BD2200D3F5C261ULL, 0xFD0B9C8B342B5E35ULL, 0x3814BA36630859EFULL, 
            0xABF233868F47474CULL, 0x3D556E9ED839EA38ULL, 0x6927DCE1BA1372C5ULL, 0x796ED7A339D18C2EULL, 
            0xCB54BC9C8CEA3796ULL, 0xAD3CDB2AA0BBF5ECULL, 0x70894160E7698EC3ULL, 0x3688FE4E74F60743ULL, 
            0xDE4CA909C3A760DBULL, 0xF75F861785579E53ULL, 0x5B715EC6C708DD8EULL, 0x106AA3F9B693BCA3ULL, 
            0xAC972689EC001119ULL, 0x656D1212A5C733F5ULL, 0x6E220D34C477201EULL, 0x0806905C65B48305ULL, 
            0xFF439F183BCD9AE7ULL, 0x3EAF3D3C33C7141AULL, 0x40315B4152208BFAULL, 0xDC057EFD07CBDE8FULL
        },
        {
            0x0084BF13EE81EEC7ULL, 0x2C36A29CCC5DEC77ULL, 0x04607C4728F618D6ULL, 0x1A10F6DEC06E5B48ULL, 
            0x06DA0311AA279F21ULL, 0x585443F1056DCBF0ULL, 0x6DAB024376BBA69FULL, 0x4B69FD54BEA3FC4CULL, 
            0xF390F89286E5288EULL, 0x777B94CC82980170ULL, 0x4573179A1C9DD7A4ULL, 0x02EB5ABAA72BCC64ULL, 
            0x72D96F887EF488CFULL, 0x5422951891F021C6ULL, 0xA65BD40E7A6D5CA7ULL, 0xBE2A500604FB3E46ULL, 
            0x141740680F96AB4FULL, 0xBAD2907D153CBD72ULL, 0xF8DCFF1E0A4905D7ULL, 0x5429F4EA6375568EULL, 
            0xAB83E6A943C13CBFULL, 0x0F083DD5E37345DAULL, 0x56B47F6C40A40A21ULL, 0x40E65156E66FC616ULL, 
            0xA1DE7172161D02FCULL, 0x9363F723D28A0F79ULL, 0x28EB7CF56DDD2C44ULL, 0x7EC9B8FF7E4EB18EULL, 
            0xDF0F4CE88BB853F4ULL, 0x95CFAC38A28EB11EULL, 0xC7BB9400E9B71A70ULL, 0x5715A04741790982ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseCConstants = {
    0x76A817DC3C70E038ULL,
    0x3609FCF3021844F9ULL,
    0x68286081D714C5D5ULL,
    0x76A817DC3C70E038ULL,
    0x3609FCF3021844F9ULL,
    0x68286081D714C5D5ULL,
    0x1ECDE36402F5565FULL,
    0x40DDF1A19D7D758EULL,
    0x0E,
    0x0C,
    0x5D,
    0xF2,
    0x21,
    0x7E,
    0xD5,
    0x29
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseDSalts = {
    {
        {
            0x12FB32B6A2F6EB83ULL, 0x78723162A9C14FBDULL, 0xA001D4B0BBF4878AULL, 0x6F5C6764EA6DC7B3ULL, 
            0x02716A7A5C963347ULL, 0x92853D3D1E22EF7EULL, 0xD3A06E7894CB7655ULL, 0x951A53C47D0CFA2AULL, 
            0x519D795900D5099EULL, 0x66707B488B90A607ULL, 0xBF6D478DF26354F2ULL, 0x9D7D2746D28F2D1EULL, 
            0xC1122E7444F8961BULL, 0x6750165417EF879BULL, 0x4FC9F58EAF1C16B7ULL, 0x52338099FDD1302EULL, 
            0x63F4DC841A15FA79ULL, 0x43D3B715F3FF834FULL, 0xD4C78565BFAF879FULL, 0xFA53D51FAFD54733ULL, 
            0x273E705EF848C0B0ULL, 0xC66040DE11CB23ACULL, 0x2BDB33B4D45E8759ULL, 0xE220470AC2151743ULL, 
            0x402DB1270273DD11ULL, 0xA43EC25E4DDA39AEULL, 0x1A74D759699EA5E4ULL, 0xF93A7B7286E921CEULL, 
            0x26D500F8A379045BULL, 0x7C5497CCC658AE2CULL, 0x851304ABC486E5D0ULL, 0x1C18A083866C4E22ULL
        },
        {
            0x1CA0C276783826A0ULL, 0x9D8880056340A64BULL, 0x263E351672CCA672ULL, 0xDADA1D8982A53B6FULL, 
            0x6360429A976D85C4ULL, 0x921A94FA88B1C8D8ULL, 0x9998B466A8C624C1ULL, 0x6F679A866E29944CULL, 
            0x90B16B42B496F58EULL, 0x09789C462B481907ULL, 0xC7791552BF0CA29BULL, 0xD1567F0CF4CD19D0ULL, 
            0x9A4449B0EE6E09ACULL, 0xC64214529C6D9BACULL, 0xACBCA12696080BE9ULL, 0xAE70A503C825CFBAULL, 
            0xC09754A624D6E795ULL, 0x91EE6BF5B519047DULL, 0xC3340BE6A8514FEEULL, 0xCC79B630853BF6F5ULL, 
            0x04CEBFE1313E321AULL, 0xB5E48DF62BED403CULL, 0xA642C3C0103924E5ULL, 0x6192CCE3F39A7825ULL, 
            0x1F5157ED95FE6E1CULL, 0x4D9B3144700C3A32ULL, 0x893D167CC881D88AULL, 0xA15E4AC80992B527ULL, 
            0xEBB990480CE1A1EFULL, 0xAA13E613E555DEF4ULL, 0x8F45F08C69EBB826ULL, 0x1668870B691C0B41ULL
        },
        {
            0xF5573D583F670A90ULL, 0x7D6E099718A7CD81ULL, 0x1250FEC1907CB3C0ULL, 0x360CC7F0F83168C1ULL, 
            0x67E545226697325EULL, 0xC4FF43973739E0A2ULL, 0x3CF4017721997D69ULL, 0x0F81CDCD2A07B1FEULL, 
            0x3547AD80F672C1A1ULL, 0xF6FC59900E5A8DB2ULL, 0xDFD6E23B3CA01878ULL, 0x5BFFFA7D144950BBULL, 
            0x765FB760CE632DBCULL, 0xF7EFDA571CB2AB8EULL, 0x3A1285715D670579ULL, 0x4F78570B7BCD9ADBULL, 
            0xAC58690A1EA24AC4ULL, 0x9CF619E60A692E71ULL, 0x31AF8F92DFFB746CULL, 0x3ADE5F419D9E5B99ULL, 
            0xFB8019DA0F79FF32ULL, 0xDBDCC7B76215734CULL, 0x9BE6FD158B06A746ULL, 0x18DF3B6CD9BA277BULL, 
            0x863311400F52DF0EULL, 0xAF17C2A795B3C189ULL, 0xE45D70681A945801ULL, 0xD8C1156A2B953FACULL, 
            0xC0F244CCF7883095ULL, 0x13F5C4CB5336FDA6ULL, 0xDA48616E00A0AE40ULL, 0xC2F66601AD6DEDE9ULL
        },
        {
            0x913CD02FCC8B9A03ULL, 0x0C2953FC3B431A97ULL, 0xF17176BCB98B748FULL, 0x24161D56472820EBULL, 
            0xFC2C31E98E5E969AULL, 0x0940322C23AF2537ULL, 0x1EAF44DE779AF5A9ULL, 0x23D906D1F5C8A778ULL, 
            0x7808C96F3FC6A3F2ULL, 0x5033B4BB47CE7A5DULL, 0x40C890F1EF711E92ULL, 0x7713A75B3CEA13B8ULL, 
            0xEF404BFA035AC27FULL, 0xA40A0D52A2BAFC08ULL, 0xBB0547F4D0C580B8ULL, 0xBBC255E616E70E82ULL, 
            0x3B5741679AFE6813ULL, 0xD3061EB17D1EC298ULL, 0x56C3000180529403ULL, 0xEC7DE32C82672A45ULL, 
            0x2ADBCDB9F05733FDULL, 0xD16293D68E10795CULL, 0xC83087354FD5AB8FULL, 0xF3A86C3C2060AD90ULL, 
            0xE40A162E33140A36ULL, 0x1BEE2EF070673246ULL, 0xD136A8559D0B925CULL, 0x8620FDA8FF5E1B3DULL, 
            0xA65C83CA9914C832ULL, 0x19E635F9341AA193ULL, 0x42D62A75A3F7F900ULL, 0x9D3930ECF3F8985BULL
        },
        {
            0x93117DA037755C96ULL, 0xD416BF1056E6A825ULL, 0x21AEF5C86CFF0ED9ULL, 0x166372980C163F3EULL, 
            0xF47F5DA280B6F881ULL, 0xA3608DF842C80290ULL, 0xF8F64B12B1FCB429ULL, 0x27D165BD103335BCULL, 
            0xABD7841845C2D03FULL, 0x3BEAB52453B65BE0ULL, 0x901146E4E60825E6ULL, 0x0DFD2DBE52E1510CULL, 
            0x1F26E5967A3759DBULL, 0xBDE66A1EFEC43B5DULL, 0x58D148190A675038ULL, 0x2F22E31E6B11B393ULL, 
            0x7E630A385665E07AULL, 0xB2469F77BB60E332ULL, 0x829768A156530A4BULL, 0xA29BB32D103DEBE7ULL, 
            0x432FD07C1465A9C3ULL, 0x32DA4F7AC6687707ULL, 0xEFDBD9C146D50263ULL, 0x7FDE67B155B32683ULL, 
            0xA26A241AE523FCBAULL, 0x6FF0785C34FC987EULL, 0x0071F5F8A001A87EULL, 0x7D20745047B3B4E9ULL, 
            0x2F6F478A37FEE098ULL, 0xD4D35082C8271408ULL, 0x150ADD59D47680E9ULL, 0xBFBC362D01F6B69EULL
        },
        {
            0x506F6DFCC4D687C1ULL, 0xD89725DA0F634575ULL, 0x18A32036772AAA27ULL, 0xE139E68994BF80E4ULL, 
            0x80CEF87A6550B9F3ULL, 0x899849CC221B28E4ULL, 0xC9D5DD3BF6E4E0E0ULL, 0xEA0B52A59BDE1777ULL, 
            0x76052F772BD70B2CULL, 0x6FB652052CFAC51FULL, 0xA3E046054E941FEDULL, 0x0BA9FF169567C3F7ULL, 
            0x042EA3519CB4B8A2ULL, 0xCEBBC68A46EF1426ULL, 0xD2BC6982F1D9BECEULL, 0x1122C717956ACAEAULL, 
            0x0E027B128BA9EE11ULL, 0xC698201292FF686BULL, 0x73A44532E76F459BULL, 0x3EDE65E95F881E11ULL, 
            0x78DAB0D207139586ULL, 0x8B41EB29D94A019BULL, 0x3B9E319EC664E2BBULL, 0x178C4C3D34417798ULL, 
            0x5DD39DF8B5B3288EULL, 0x602C154C16ECEEEFULL, 0xC71613153B202060ULL, 0xAF57301155AFED58ULL, 
            0xA7575B48B19CC8FFULL, 0x7AC274C59FF829C4ULL, 0x951662ECA844839EULL, 0x921B24D5BD11451DULL
        }
    },
    {
        {
            0x4A11B77AD3C2AECFULL, 0x2FFC9E0681EEF4D9ULL, 0xE3D265CB76178A9BULL, 0xEBFE335C21974C84ULL, 
            0x9EBD2B0C99C67609ULL, 0x3FFA3CBFA03FA673ULL, 0x0BF97739BBB9AA6BULL, 0x9DADC718299EFFCEULL, 
            0x1CFE10A1D91D2336ULL, 0x7B56C9E47D7E7706ULL, 0xD7D459E5A0750A53ULL, 0xFACDF3DFDA67F349ULL, 
            0x0E5910D6B5BC2478ULL, 0xE443B9B9BE0299DDULL, 0xA3A3965F71A506CEULL, 0x43870284D7F857E8ULL, 
            0xAB84682E99C96428ULL, 0x3D85DD8019A448C0ULL, 0xE9D078A6907D257DULL, 0x52313DA4BBDFF6DBULL, 
            0xEF2C10847FD997A0ULL, 0xD4B4B02E74C85A32ULL, 0x1806132BE80C6A73ULL, 0xAD94B2270FD29BCEULL, 
            0x1FCC3C331E29A2C0ULL, 0x19C18AE797471F1FULL, 0xF49DE39EBC6B03EDULL, 0x52AE86019B08725FULL, 
            0x35AB1308E2E9C732ULL, 0x3AC842BFBFE35F0EULL, 0x71A9C54284AE415EULL, 0xE281233B8BE495D5ULL
        },
        {
            0x58C1C71A0C0C0237ULL, 0x4FEBF8F52FB246ECULL, 0x9C74D7A71ACB1E8CULL, 0x08EBDCD7DA59B2D3ULL, 
            0xA67A735FEB76FAFEULL, 0xF8C90CA41BCEE1C8ULL, 0x49F4B302743D5910ULL, 0x70FD0822A3C54D7EULL, 
            0x2FBE8EDA588220C2ULL, 0xFD1BD32990677220ULL, 0x4A7EC8F73EE48C71ULL, 0x6A9F29E8D5DD66FDULL, 
            0x5EBC421CAD395E4CULL, 0x5728F8B27CCB3193ULL, 0x7C3591BCED9A91EFULL, 0xC6935F6FC68683C8ULL, 
            0xFE51BEEB7B07E3B2ULL, 0xD83CAE660EB2D28BULL, 0xA51929DD02A4455AULL, 0x541A764EDCD3EAE4ULL, 
            0x6DD6995F7D38E0DCULL, 0xE745983D30406D24ULL, 0xC0589CB9BD5B22DDULL, 0x8683FBB1B1CDD94DULL, 
            0xB0DCDC48E47E6740ULL, 0x8C4C1E1BCF6D4320ULL, 0x68AD42DD584C9687ULL, 0x6820A2AA31282D60ULL, 
            0x648A6A581CB4BD6AULL, 0xC73083807B894920ULL, 0xF4C025292F144F82ULL, 0x425F08075FAF8960ULL
        },
        {
            0x83458616E7A95472ULL, 0x02217B1C4279D83DULL, 0xD607EC07535C028BULL, 0x0E728D8AA808A0F7ULL, 
            0xDDC246B54455DD17ULL, 0x6FD26B909958719DULL, 0x1F8101455832DDC3ULL, 0x712752FC4533D723ULL, 
            0x01A1BB8492E53AC7ULL, 0xC612B3852529AD47ULL, 0x5642C183FC3AC719ULL, 0xF4BF62228DE2439CULL, 
            0x85C11695E9EB39F7ULL, 0xD4AFA81D8852A905ULL, 0x9397ED5C1F92D5B0ULL, 0x4BA3C8BFC8F9352AULL, 
            0xE49EB1D96091A689ULL, 0x71AAFB02C5CB49D0ULL, 0x86B621E40EEBC5BFULL, 0xFACB9E236A2B1283ULL, 
            0xDD1D47519F27FE66ULL, 0xDAB76E1CBF46F6A4ULL, 0x4ACCD08A167B800BULL, 0xF5B1D4FE2BB7D544ULL, 
            0x6137B0039303C5D4ULL, 0x496B531BC29800FDULL, 0x6799105712C18365ULL, 0xEFC609B60E955E99ULL, 
            0x9F062118C0618D41ULL, 0xBB7A856F22F81B4EULL, 0xDCF50D1A1DCF0708ULL, 0xA419C8FCB0ACC611ULL
        },
        {
            0x646433C36E23C0BFULL, 0x389FE6A5462B1BCCULL, 0x2493497D99A5C9BEULL, 0x2D2FF006223A37C7ULL, 
            0x4CC991077318B84BULL, 0xAC1C5C5E996B4101ULL, 0xC0413C6125DA0EEEULL, 0xFD9CB481BD3284D5ULL, 
            0x152E3EC431EAB9A4ULL, 0xF7AE06783152502CULL, 0x7D29A88D1B3175B6ULL, 0x34AF2645475D3F26ULL, 
            0xB393090C44AE2315ULL, 0x5C5EA20C4E3CA345ULL, 0x4687803E5186E17CULL, 0x7B4D55E2B0006B44ULL, 
            0x914BEF7B16E32376ULL, 0xF2B91A1E8C511D3DULL, 0xAE535DF69F667085ULL, 0xA078228FBA0C7950ULL, 
            0x7CF136C682943B0AULL, 0xBAC493CC6B41CCE8ULL, 0x044C45237E323A7DULL, 0x230ED10D9D311711ULL, 
            0xCF65065BE7999C09ULL, 0x35A9430FA3F1448BULL, 0x2D4249DE619A5EB7ULL, 0x988617C9FAE5D01AULL, 
            0xFA086C2EF758C15DULL, 0x32AEA278764216E1ULL, 0xE7ACD2E2193D2968ULL, 0x079892FFC4366A7BULL
        },
        {
            0x0998532D02D83675ULL, 0x303D598F81E25714ULL, 0x60B154905DD241BEULL, 0x9079E35246D5BBF8ULL, 
            0x5F1B160C3C3F9DC8ULL, 0xCA373D66AF795988ULL, 0x2BF3BE3F1CB438A0ULL, 0xF5A170696592A912ULL, 
            0x90B1F87F8C02DFA9ULL, 0xF17940FDE539D126ULL, 0xF3012B95ED238D94ULL, 0x77F08157E742F293ULL, 
            0xA55377BEBAF43EC6ULL, 0xDAFF4B0ED7BF5346ULL, 0xCA3341D40703C5F9ULL, 0x1AA882923B7BD2BDULL, 
            0xFD2106B529F9BF69ULL, 0xED293A8405AAD200ULL, 0x5EE6ABFD8769513AULL, 0xD66D57B870F8C142ULL, 
            0x22E82853B577CF32ULL, 0xE86AA63E4C4A33DFULL, 0x0778E424BB5B7A68ULL, 0x0B51326016BF8132ULL, 
            0x32DAACB2E28D3350ULL, 0xBF3D3B49DC12DAE3ULL, 0x5176B6DF0008B543ULL, 0x61A0841D1EFD604CULL, 
            0x7242F621DC63314EULL, 0xC1B264526E410125ULL, 0xC2C4F60EB996C3E8ULL, 0xA5405EBC425A43CBULL
        },
        {
            0xCC17AD3DA5CF1237ULL, 0x5F78FC986AEB6CFCULL, 0x8B08F40647931B25ULL, 0x003FB43940C49DD5ULL, 
            0x2E05BE6686F602CFULL, 0xFABFA5C0B4D253DAULL, 0xE16DFE870CA453C5ULL, 0x6374133CDA42917FULL, 
            0x4E9EC45DF8857AB9ULL, 0x6CC0F459B8815A4EULL, 0xAF8B0A1D6B026D92ULL, 0x10592C2969BCF062ULL, 
            0xFF41BAA6EE0203A6ULL, 0x3F6BCAED5A274FAAULL, 0xF57ABF7B8AD1D982ULL, 0xBF0041D3452B6409ULL, 
            0x30F63D347E110E3FULL, 0xD5C3316E23FC79D4ULL, 0x44BD636D7B399999ULL, 0x614CD34F9ECC5022ULL, 
            0xF3A7F517925DB02DULL, 0x48C3EF9B937CC63EULL, 0x8BF56A3CDA368804ULL, 0x1800F37B16F93372ULL, 
            0xC26B1983175DBCC2ULL, 0x7A232C2361537465ULL, 0x175663F27FAEBBE4ULL, 0x69D74C4B9DC0DC57ULL, 
            0x65824DB1B80EC7CBULL, 0x2A6AB5E67D82ECD9ULL, 0x8F17F4201674BC65ULL, 0x75DF942B7F4A3F64ULL
        }
    },
    {
        {
            0xCD298F328EBEE164ULL, 0x6E178D591000CCB4ULL, 0x1DA3BE2260F0C2A3ULL, 0xB9EC64ABF75B14BCULL, 
            0x8A3FC9C9293CBCCBULL, 0xBFF02D726F5282CFULL, 0x3BE84267176B5EBFULL, 0x607872ABDD0D9529ULL, 
            0x3A40875F71301A0BULL, 0xD9E659DDFFFAD27CULL, 0x2AEE960C1436FF3EULL, 0xFFC81E1AADEB056FULL, 
            0x844C3FE9653E6C7AULL, 0xFD28768BD4F30E92ULL, 0xDC07BE13FD830A63ULL, 0xA021789E1D0B2E5CULL, 
            0x58AB2038CB03B30FULL, 0x70F256904A8217EFULL, 0xA9913F97EB73861EULL, 0x4AA751AEE06E9142ULL, 
            0x5AF77999BF654374ULL, 0xDF880E56E1C07338ULL, 0xB40228B810BB8D78ULL, 0x2AAEAFA8E14E4682ULL, 
            0x75979A30BD9A8548ULL, 0xC18489BA5892ECD6ULL, 0x9D54C951C7AEF60BULL, 0xF46516A18F4538B6ULL, 
            0xDC9F38C7BC6E2CF8ULL, 0xCCAC32905C11C9E0ULL, 0x8F0D6E4663759B6AULL, 0x23414216D3FC5054ULL
        },
        {
            0xBDDCD126D4DE3B50ULL, 0x73B2021E96825B76ULL, 0x22E6B648E0CD5AD4ULL, 0x4876EDCB566FF2FEULL, 
            0xC0C114C05D01A118ULL, 0x5758E8E499CD9E3EULL, 0xC7909A5E0A15615FULL, 0xBB1209F86CF38C11ULL, 
            0xB1A089FB64802705ULL, 0x098A8795FAD9AC15ULL, 0x92C8B543229F062EULL, 0x8B567C7D2C8C8E01ULL, 
            0xAF4B0941870D2A62ULL, 0x5105D8E42407C24BULL, 0x534B36CE43342FD4ULL, 0x94BE007ABB538BE1ULL, 
            0x979E056C887BB954ULL, 0x49FB682345D1C4C1ULL, 0xA36C3BFD145BD1D4ULL, 0x6861E028F58553F2ULL, 
            0xB9473BCE55AD64DFULL, 0x5D925D2C01FFCDE3ULL, 0x8C32E2E41EA3C7A5ULL, 0x8C6095B9FCD993F6ULL, 
            0xDC2B4A9A83B7588DULL, 0x1061E0041292F58CULL, 0xC7191A831E8406EBULL, 0xCAD409147543AB11ULL, 
            0x39AE10F1F17D0B76ULL, 0xC9B23A1ED7C79D7CULL, 0xAA51D9E94B345346ULL, 0xD229F1F482C581BEULL
        },
        {
            0x5AE254016CCD5862ULL, 0xBB3F0CBA14AF0161ULL, 0x3749D3E9141BEC21ULL, 0xB100C6402EE57627ULL, 
            0x198BC3C819E4AFF7ULL, 0x6BE7DAEDBDD8B442ULL, 0xE2E76E0429E8664AULL, 0xE391289EDFCC2967ULL, 
            0xB8C8EF9C1FDE233BULL, 0xDD49F48A69B44C59ULL, 0xB9DFD9C2726DD07DULL, 0x29261808B9C96024ULL, 
            0xEF73E8974649430AULL, 0xE149E8CDF1DC1F91ULL, 0x727C543B527EE21DULL, 0xA644F9F6D40D5B24ULL, 
            0x515E7924DBFF267BULL, 0xFBD16A61E6D91686ULL, 0xB317C4EEE68A82CDULL, 0x5306B3CB58467162ULL, 
            0xB29FA3412BCDB0C2ULL, 0xCEDB3E8EFE38200BULL, 0xB58A5FA83E4B0AF6ULL, 0x6B893621C64B5717ULL, 
            0x29D714CEA7838AB6ULL, 0x567411B94633800BULL, 0xF7A2972E4DD7EF25ULL, 0xAD6961778160BA11ULL, 
            0xB1EC9E7903E3D19EULL, 0x940FF92E90774529ULL, 0x49EC0FBE7227CD1EULL, 0x90B2968BAC156808ULL
        },
        {
            0x80C3E87EF460D91AULL, 0x41C3C06BC7684C57ULL, 0x963500CF84F96941ULL, 0xCA4AAF516E0C9F2AULL, 
            0x4597112BAB67853FULL, 0x53C0B8AB58C8D847ULL, 0xF7636448D3CBE24DULL, 0x69B8A530CDA6A64AULL, 
            0xF3C1B2DD57364877ULL, 0x9413E98608FDA5A3ULL, 0x8F29C39D17685AA4ULL, 0x5D7A23192E132F52ULL, 
            0xA8FE914D66CCAC8DULL, 0x435802DAF59785DDULL, 0x915F04229E961860ULL, 0x640885C8910F54D5ULL, 
            0x4D9B0BE2F6B40D6AULL, 0x0FCED22CB32986FDULL, 0x2D07E528489C05BAULL, 0xC7A946678E442C13ULL, 
            0xE38F40F52A65EA17ULL, 0x1FA34D027BC23151ULL, 0xFF0229D284D3D873ULL, 0xF4D086F9357BBA92ULL, 
            0x8CE25BE6D63F830AULL, 0x304E93026882E42DULL, 0x0639C1A20DBE9311ULL, 0xD2E44DF5D7B45EA2ULL, 
            0xA8326D1F8C671947ULL, 0x4B8610BD067D3210ULL, 0x62A323E89A8AA199ULL, 0x07181936849C532FULL
        },
        {
            0x08F83D86E44B5DF5ULL, 0x6C4612E3DC0123C9ULL, 0x23F371FD94892B62ULL, 0xC302AA666B8A5316ULL, 
            0x70E5D284CE51BC7BULL, 0xFF4A095FE1C08869ULL, 0x50D19262D32E8165ULL, 0xE95472A27565E2E7ULL, 
            0x94456C2BF1A94CB6ULL, 0x422C77D3FE54363FULL, 0x31954E1AD8739A0DULL, 0x5BB34DFBC43DA60BULL, 
            0xC76514EB9B3EA78EULL, 0x2B739BB9BF54D55CULL, 0x6169A46AD2D5CA30ULL, 0xD9CE422387B18DADULL, 
            0x54253196D1496BB4ULL, 0x77F84FA6B74EB3B6ULL, 0x4E6BD3532D9DD94DULL, 0x26F6FB43D07120EEULL, 
            0x8BFAE309F567C0DDULL, 0xFE5A7601D5177ACFULL, 0xC0CD403BF15E3C5AULL, 0xBF5456C70FB99912ULL, 
            0x447B3D8C24CFF0F6ULL, 0x70CF9585D036B539ULL, 0x810ABA4A4C36BBBEULL, 0x416D14B43B03CC6CULL, 
            0x5AC943B88806D11DULL, 0x574443E8E45D961AULL, 0x62FEB3ABFA14EFD6ULL, 0x277A4AEEB6965270ULL
        },
        {
            0x9DBC0D2EEF1D2FD0ULL, 0x145BD8C37340C0B9ULL, 0x8CA7520623DDA564ULL, 0x96063B8E13FD0D73ULL, 
            0x1AEB22CF87DDD004ULL, 0xDF2F1539B1AC3178ULL, 0x2D5171E3416B51E1ULL, 0xF35EE4A4EBAA7EA3ULL, 
            0x2C35C56E5640888AULL, 0x6FCF4AECFB6AFD18ULL, 0xE870F14357ADF308ULL, 0x87F387859B56D301ULL, 
            0xFE5DD19FF4F40ABEULL, 0x324B719B9841D776ULL, 0x6EA324A989B134E2ULL, 0xD35CC8594996EEE4ULL, 
            0x89EFF1282FC4802BULL, 0xDEF4B8ADD5191A89ULL, 0xD5D3B6EC04F03892ULL, 0x637F251BBD63EEABULL, 
            0x0D6D7F1F4716BEA8ULL, 0x203087E22CA7F54BULL, 0xBEB2B7A45BE14F2BULL, 0x69D5110DE15FF4A2ULL, 
            0x7F28C3736AD0099CULL, 0x2370E6D8DF9D2EECULL, 0x556DAF63BC273166ULL, 0xC4C5E745B561ABC0ULL, 
            0x7DF85B68896E18C9ULL, 0x0730B3B80C54A8EAULL, 0xE755D9C3242B6786ULL, 0xE65AC59B1E0E7D3BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseDConstants = {
    0x4B66BCC59DDBF3D3ULL,
    0x331DF0105ED7010DULL,
    0x6C1D640EB0D786C4ULL,
    0x4B66BCC59DDBF3D3ULL,
    0x331DF0105ED7010DULL,
    0x6C1D640EB0D786C4ULL,
    0x37358B67F4AABC82ULL,
    0x2D05B86C71496CF7ULL,
    0x3F,
    0x10,
    0x2F,
    0x58,
    0xCB,
    0x68,
    0x87,
    0x44
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseESalts = {
    {
        {
            0xAF8DDA9C7ADA8E78ULL, 0x2DDBD0A5BBDF6D0BULL, 0x2DCBB7F11D73CBD0ULL, 0xF55B3CD9453DD71BULL, 
            0xE1C89E1275B70204ULL, 0xAF977B9AC039035CULL, 0x4B55B88BD7E3ECAAULL, 0xF51FB089797DA1F7ULL, 
            0x0E48286824682F1AULL, 0xC55D3DFD8EDCDD5EULL, 0x5A53DA58C0F21F2CULL, 0xE892306015B07C81ULL, 
            0xB7CDA2E2B6ED2937ULL, 0xDFBB6E33F975F8CEULL, 0xFDDA9B35B3936220ULL, 0x54DC3FEC3C06B289ULL, 
            0xB858F308BA9CCD37ULL, 0x587C3275A4D94627ULL, 0xC5BC272E02C2000DULL, 0xEB25FDF44BAC7A66ULL, 
            0x5A8F7DC40B7DC140ULL, 0x90DCFAE90A4CA756ULL, 0x38362AB0D3A62367ULL, 0x24F56037DD94882BULL, 
            0xE459F9650A0D2637ULL, 0xAC4EFF2FE72970C1ULL, 0x49D810BEE5F01E94ULL, 0x2E2B43A2860E1E8DULL, 
            0xBC8E281C78DD23BBULL, 0x3BF40FCAD1BB812AULL, 0x71AB7DD331B6B7E1ULL, 0xA9D658F149802519ULL
        },
        {
            0xE4C85C6822E82D9CULL, 0x1DEF283AF068852FULL, 0x1789EB6B6986D52DULL, 0x5F09833041EE6FD3ULL, 
            0x8C1C5E6BC408BEBFULL, 0x52E053C0F7D0025FULL, 0xD8F52421E4CCA0AFULL, 0xAF7C56A82DD6B4DAULL, 
            0x979D6D8BEC1F6595ULL, 0xFB2194E3675092F7ULL, 0x761E0763E8EDB9F3ULL, 0xBB96F23414886092ULL, 
            0x57154550FED90A5CULL, 0x3A29308B55BC1F25ULL, 0x2B077004E116B0E2ULL, 0x40CB11475BA05BFDULL, 
            0x1FA4E49B80D690E8ULL, 0xB041A5F5CBAC783EULL, 0x97C8A68F7121852CULL, 0xD341954F485836E2ULL, 
            0xCC9F3D08C2F0FDFBULL, 0x2F9BEE9F91AD320EULL, 0x56052ED1050F4829ULL, 0xCE329FB478E0FFB3ULL, 
            0xA1073B20FD545072ULL, 0x5039481708238D75ULL, 0x994C2E67EAB329A4ULL, 0xB2B8582170FE207AULL, 
            0x009324D062E667ABULL, 0x2B1406DE389924DDULL, 0x9E4B0783F2035783ULL, 0x40FD39D53FA52334ULL
        },
        {
            0xEBC1B1DE363211CDULL, 0x687F34ABFADF9390ULL, 0x6683264A023E8EB6ULL, 0x7F4DB151D592E6D6ULL, 
            0x8079794F90537261ULL, 0x79C19EDDA65A8372ULL, 0xA122FE542CDD2150ULL, 0xAA9A264A65965F0DULL, 
            0x42A71D0826D2C602ULL, 0x660AD7DE67E2FEEDULL, 0x23DB835951B9A366ULL, 0xB58C41BD2A513D18ULL, 
            0x52B5FA0C4AD3E0EFULL, 0x4682AB10233F8038ULL, 0x4A76AEBC1AD9C567ULL, 0x052FE3B7ECFF6046ULL, 
            0x22478B610B20F8F8ULL, 0x28CE891C4D2EA08BULL, 0x541CD240B5F49C1DULL, 0x417398650C045911ULL, 
            0x56C394DCAD7F568FULL, 0x8432DF5FCFA94987ULL, 0x76369F27842EEDD2ULL, 0xF5CA91E14AE381D8ULL, 
            0x4935FD2AD2A02B2FULL, 0xC822CC51D64CF589ULL, 0x38C386F92D859CF5ULL, 0x197430D96857DC4BULL, 
            0x315E8069E5597C3AULL, 0xC576BCACA03BB446ULL, 0x326804E1A3D79A74ULL, 0x977710CAE30EBCF3ULL
        },
        {
            0x41523D961B29F6EBULL, 0x936B5F53D455FF5AULL, 0x5687AD8E1F1500A5ULL, 0x671C9A94BE6FFDAFULL, 
            0xC16D2715224CE67DULL, 0xEA4E6960E2FA9CFFULL, 0x1003E6F2C736DF89ULL, 0x969DC473E80CB091ULL, 
            0x343D322402858B34ULL, 0x37F26B2DF1DFFCB7ULL, 0xDB01BF8881F961E7ULL, 0x8C96900AFBD9A80AULL, 
            0x13FDA88C8854D15DULL, 0xD27A43D5F57ABF23ULL, 0x39968B0C30C1F6DAULL, 0xFF55BF6FF284C4A1ULL, 
            0x9F2DEB7DF9134912ULL, 0x468A2CA88DA3E85EULL, 0x5C91B383F5183B5BULL, 0xDFCAD1A305F30E37ULL, 
            0x8C136490C865EAABULL, 0x14D7FEDA164C3FAFULL, 0x7DA7C80EEB110A1EULL, 0x75FC64D7F9254930ULL, 
            0xBA777F17119F6752ULL, 0x59ECE6C9B66E9C05ULL, 0x2EFADA99216D0018ULL, 0x2B19EF704A8C82E7ULL, 
            0xBE14047B1B85780FULL, 0xE90E405556DB9B29ULL, 0x6F52686BEC94B272ULL, 0xF7CC80909EB5976AULL
        },
        {
            0xAFEE11E21DB58AE6ULL, 0xFDA691F59561BAC0ULL, 0x802040E2C2AAF32BULL, 0x90E4A9C38960B01BULL, 
            0x3138BC77517B2B69ULL, 0x1DA3808B66E5EA0DULL, 0xAE13292127A7167CULL, 0xB84CDDA54A78894BULL, 
            0xFC4545A6854C10A9ULL, 0xA9E236644D863159ULL, 0xF831C2BCB784B500ULL, 0xC3D2FFD9186085F7ULL, 
            0x2B38BC22D742F9D5ULL, 0x0D529ED906C91D06ULL, 0x12C11734FBCC83BFULL, 0x6D04904EA92FD320ULL, 
            0x456173ACDD1D8715ULL, 0x546F272D7137090EULL, 0x5BC1A587E8B4A4C4ULL, 0xA61A91E5F0F9A1D9ULL, 
            0x1B340BF140A485A4ULL, 0x258358D81BA429E7ULL, 0xAFC2A4F6838B2EB4ULL, 0x660CEBB25B174F84ULL, 
            0x524E7E0F34187865ULL, 0xF00DD6704C1135AFULL, 0x92F419551A81FAF9ULL, 0x695B4D7F9AADB5A7ULL, 
            0x7D57B5836C28824AULL, 0x34372D648B915514ULL, 0x9F775CB354225D4AULL, 0x1B72840D710BE2C1ULL
        },
        {
            0x0BC634D4EB125CFAULL, 0xA51B593A547B766DULL, 0xEFC334C11455073AULL, 0xE8B43C6C36E7484DULL, 
            0x76A734DD5816A130ULL, 0xC5F817D158841F3CULL, 0x93D2AF219E862790ULL, 0xAE2B6716563329A7ULL, 
            0x14F275ED5EB9BBA5ULL, 0x30A3D5879BF11E2CULL, 0xB6EBA87E84D048ACULL, 0x6058A836BE119D44ULL, 
            0x946BA2424ACD876BULL, 0x211D9E1A50E41DB7ULL, 0xD6AD9EB527277B16ULL, 0xAD5FC381DB058BFBULL, 
            0x1E4EFCB6F333D4B9ULL, 0xD6A12720C07F0488ULL, 0x61F73D5DED3660E6ULL, 0x478004B5696EAD84ULL, 
            0x10C3CC39AC2059EFULL, 0x9B73A510B7689CDFULL, 0xB8B6760E31A3B393ULL, 0xA73DE874ADB7D185ULL, 
            0x136DFFB7ECC80C90ULL, 0x0CC51B3B4521B92DULL, 0x11E5A545D31A55A6ULL, 0x2E5F3A15464D373FULL, 
            0x49B59C9149EE574CULL, 0xF1BE22EE937B7A1AULL, 0xB81F605C324B7926ULL, 0x064215F0B880F46EULL
        }
    },
    {
        {
            0x8CD9BF0CB3B92A81ULL, 0x255BA4576F28C2E4ULL, 0x0AAC600C7B23AB92ULL, 0xD9E3825B94764077ULL, 
            0xE54EA9D1BD8DC557ULL, 0x89E7DA2D6EE0F4B5ULL, 0x0B24C0D57286C29FULL, 0x28BC8B01F2A590F8ULL, 
            0x3EA6CBB64F762A3BULL, 0x6E8C055807908FE3ULL, 0xDAC0F8BC21AC29D2ULL, 0xA790A2D62AE732E6ULL, 
            0x0C054086B410D948ULL, 0x54920FB0AAFF59AFULL, 0x5DA9A070FAC6BB97ULL, 0x3A2F383B3BE2FCCDULL, 
            0x4110314C19D18063ULL, 0xF83352B40C638C66ULL, 0xF61CCB0006FC186EULL, 0x3BDA58CCCF579B0FULL, 
            0xA0B9E78546793C3DULL, 0x185DDAD412533E5BULL, 0x663A66FDFC667D43ULL, 0xA9F0B38884A8D545ULL, 
            0xC071A207E5250B6AULL, 0x5837AEAA18F164A8ULL, 0x5FE8D16C92CE70B4ULL, 0x9AA5F884CD8E502EULL, 
            0xD1C2872CD9BF63ABULL, 0x1BE55BB7E897FFDBULL, 0x1B156E279FB112A8ULL, 0x29992BE83F20D546ULL
        },
        {
            0x9F5D20F85DA6DE82ULL, 0xBA4F47D41C2A221AULL, 0x9FF3178BA7FAA35EULL, 0xEEDB4CE722E3E737ULL, 
            0x347C4E14F4BE0D01ULL, 0xB6F76F2CE243ACCFULL, 0x1A7EF27C068FB25BULL, 0x9CF76D09C5649A5DULL, 
            0xFD706A74FD1CF372ULL, 0xFA19ED872CCA1BA0ULL, 0x0AF61D717030DFFEULL, 0x9265E1CE3DDE9A55ULL, 
            0xD6C3C35133DC5D53ULL, 0x181FB77EB23D3B6BULL, 0x0A97D32A41C841E3ULL, 0x57EFC5760A778C2AULL, 
            0x148CF8F56F04B5BFULL, 0x746E6C02935AFFFCULL, 0xD48A4CA334C44F02ULL, 0xE96D67F7230A17D1ULL, 
            0xDE9A9441BDDAA225ULL, 0xBDEAB81D7E5AB4BAULL, 0xF9A5C8E8649C8C5AULL, 0xA70E7C2471DD78B7ULL, 
            0x073DA5E7BE7B1E14ULL, 0x4EE8C5E79303DBE9ULL, 0x2089B7BC66669BC1ULL, 0x6263CFE56CA96240ULL, 
            0x3BFD91432A194663ULL, 0x0C61A91CB1E77A85ULL, 0x7DED063F58E42CEBULL, 0x20C0668362DAE4BCULL
        },
        {
            0x6113B09893C14B89ULL, 0xACEAEB928DB2FDB7ULL, 0x45A8E3E420BAB886ULL, 0x95A30E1380127B2BULL, 
            0xBB1B63A34984F7C4ULL, 0x827E24D093AB7C68ULL, 0xECED0C694FD7A181ULL, 0x2F5F6C8B287DECC3ULL, 
            0x874143314CEF6768ULL, 0x6F9FF776FFEC8EC9ULL, 0x8AD0E20DD2A51CFDULL, 0xAD45DBE8A744923AULL, 
            0x11A4A27AA34A2682ULL, 0xC29E936357932599ULL, 0x7849C70025A22BFFULL, 0x5C84112301DA0AE4ULL, 
            0xABFB4E8676E3AA05ULL, 0x17B37BB63A4A2E49ULL, 0xCCC62483C997DD7BULL, 0xD4CF51C2F7AA20DFULL, 
            0xC7E5FF3ED081BB4BULL, 0xF94D11C66AB32293ULL, 0x16656815A4DA9FB1ULL, 0x342C5E162E602D37ULL, 
            0xAD13A51A8B5F175DULL, 0x458ACF282401B76FULL, 0x95AC39DA9FAF719CULL, 0x495BD4BE66D42A83ULL, 
            0x7B556253B554C2BBULL, 0xA7151D90FB3D0A92ULL, 0x962F7B1B4CAEE170ULL, 0x686989A5DFBF3CDEULL
        },
        {
            0xC06EA4C1BDFC1DA1ULL, 0x587295BFF83CAA79ULL, 0x8FDB0CF889BB1DE7ULL, 0x30AACDF24C2BB229ULL, 
            0xA68A156B1474D525ULL, 0xF713228B9F365560ULL, 0xE7E1322B3203DB77ULL, 0xA97CD45A35214245ULL, 
            0x5D44F1DE463009DFULL, 0x0E92740997E2C0F4ULL, 0x1858036A366F8677ULL, 0xCCD4938C33E874E9ULL, 
            0x12CD0952F80A227AULL, 0x2D104442C7E52B03ULL, 0x81C8E287F85ED118ULL, 0xD2B3C28A7323AC80ULL, 
            0xCBE28CA42C688F44ULL, 0x816B0816393AF0AFULL, 0x228B5004395310B8ULL, 0xC056E38826AF3105ULL, 
            0xA88177E46F569422ULL, 0x1CAE4A71C59A409AULL, 0xD8FB6FC0C852F228ULL, 0xDDC6E4488C9A0FFEULL, 
            0xF39E7562FB293341ULL, 0x812262510BE191A9ULL, 0xE2255D4E91F2C0C2ULL, 0xA8A79F5327C5D368ULL, 
            0x2E711348E0FAF990ULL, 0x25B9E35AC685D16CULL, 0x22050A7F8A5A878CULL, 0x250873E441A49254ULL
        },
        {
            0x8221115F58B1D69FULL, 0x366BDF511FA2C3AFULL, 0xC0A1A09FCAF558A1ULL, 0x330030FB49667BEDULL, 
            0x4155D373CFFC0044ULL, 0xCD8E16190AF6D69EULL, 0xACAE1CCC5C17AA7AULL, 0xF4074BD69C585E44ULL, 
            0x8B8B317A8755FEB1ULL, 0x62434EAEA3F6EF37ULL, 0x513E06C53710305DULL, 0x2F57DF832E20FA00ULL, 
            0xDD79F2532257EF58ULL, 0x2C4B844D78CAE290ULL, 0x39F89E5759D4995AULL, 0xD7180C573B53AB6AULL, 
            0xB7A0682D75F8EE9FULL, 0xDA3E9A28480D0180ULL, 0xA95306529F26F634ULL, 0x032EAA2C244C3B44ULL, 
            0xD6F59902B244CD81ULL, 0x1FD6BCDA8E65F9ADULL, 0x1C772EDBF81DE49FULL, 0xB59F3DC3D1480747ULL, 
            0xF8D352FC4EE68A6EULL, 0xE5A13803A47236E8ULL, 0xE0EC63142F040751ULL, 0xF93CD836E6CD1EDDULL, 
            0xA9526993DCEDD045ULL, 0x6C35E7B9559B8380ULL, 0xB94BEF508FAEDD7BULL, 0xABB3B6147BABA851ULL
        },
        {
            0x5E4467C3E819D1F4ULL, 0x22206D7C86297BF8ULL, 0xD26017F469EDBF8CULL, 0x98A0489D2DBAEC83ULL, 
            0x8C0644A5B3234B4BULL, 0x3D287407501780F3ULL, 0x97155E7B92B9BC5DULL, 0x29F0DA679CF6ACB7ULL, 
            0xC5AC25FDDF94E0ECULL, 0xC2580D6EED438F47ULL, 0xEE93E0BA81801152ULL, 0xEF84F55BC6F57E19ULL, 
            0x4E5C5CC85EC82C28ULL, 0xB8E6E6B0386B4F65ULL, 0x92799D27249AF2AFULL, 0xF8FFFE755CEB0C90ULL, 
            0x7AEC29110A3FF386ULL, 0xC4D673C8672E0B7FULL, 0xB9576B269C46EE7CULL, 0x167E37FC0A5FBFC6ULL, 
            0x0B76B617BEB07513ULL, 0x933FB950E767D252ULL, 0x6111761A8E5FBE4EULL, 0xAB43C6FC086A3971ULL, 
            0x8D386438B1427559ULL, 0x1FD9818E869E99BEULL, 0x611BFD6B629F9D14ULL, 0x8085FEEDA38BCA6AULL, 
            0x50FA7FC7EA754097ULL, 0x8D4565E233F42E55ULL, 0x736175C3D59960C1ULL, 0x2B284EA7FA4BF574ULL
        }
    },
    {
        {
            0xD563B1E221DBED49ULL, 0xF40E763F8842FE8CULL, 0x710DAA1F9A998A50ULL, 0x23307B2C1E176907ULL, 
            0x0CC9574633B1079CULL, 0xDD63976CBF70E036ULL, 0x68A02ADA37B5032BULL, 0x68FDA955C12BBAD2ULL, 
            0x85D2C6B68B6E665EULL, 0xFB150EFCBB5E04ADULL, 0xC6FB32B4531FEBF2ULL, 0xAEB8637AE7078C0BULL, 
            0x2917052D128F597AULL, 0x0C921C8455F0E124ULL, 0x0D8BBF71AC0075B8ULL, 0xD3D4E2FDBB872AC0ULL, 
            0xECFB133B19A0D48FULL, 0x68F1D11919EDBC89ULL, 0x8CC5036BB59DF186ULL, 0xD33163E2FC29EDE6ULL, 
            0xF75255D1373A72CCULL, 0xE1F28E9F6531AA2AULL, 0x71D98A756ECE59F1ULL, 0xFC417E21D58E2E6EULL, 
            0x4586308499ACE090ULL, 0xEB7F2458CF1F329CULL, 0x8C528F43F9997EFFULL, 0x019CE100E318634FULL, 
            0x9F964E1FB5356C33ULL, 0x951AF931939153F5ULL, 0x1C4F615A8DB178DBULL, 0x2150B141B98AF09CULL
        },
        {
            0x58E4E4100CC6E826ULL, 0xA44131066FF3A9E6ULL, 0xD5E14F797642ECB0ULL, 0x357E89A81432CC14ULL, 
            0x74EDA126AD73BAA9ULL, 0x34228E74EDEC6009ULL, 0x3215ED75743D80B5ULL, 0x55D3DA088B890CB9ULL, 
            0x51E169C9D8B957B5ULL, 0x21DE070A5E9F729FULL, 0x6E113CAAEB416A81ULL, 0x3B0456D8B32A2383ULL, 
            0x91EA127AAEF02ED0ULL, 0xE2B4B6ED3F3FCCF4ULL, 0xC6E0A2E624CAB378ULL, 0xFD41BE2C334586ECULL, 
            0x007B3C816D0A145BULL, 0x306F0BD5FF05B352ULL, 0xD0ED1B401CA722AEULL, 0xB7CBA9CCF6C90C8AULL, 
            0x8557E93801768329ULL, 0xA899F4ABE67A0D76ULL, 0x9A51532E1175FC79ULL, 0x666B95ACFC18554BULL, 
            0xB22CE0DE6EB02E39ULL, 0xD2AF63771564DDA1ULL, 0x32B5B302C1756911ULL, 0x1157FF97BFD43996ULL, 
            0xD66D340D8963E229ULL, 0x9E52FCEEDD0EF3CFULL, 0x919F88FA4A5E5211ULL, 0xF647D6774538120BULL
        },
        {
            0x60CCD21CDABB6419ULL, 0x5441B98D02963CEBULL, 0x4E01F05FE68A1D5DULL, 0x15A409993F8EE556ULL, 
            0xEE363A29245BE154ULL, 0xA0F5165D2977698BULL, 0x3927DE6B63843C92ULL, 0xC76D6472F776F6BDULL, 
            0x1775F169838371AEULL, 0x4F5217696264A2BCULL, 0x8EA5F76EF6A74DBEULL, 0x7AB79C7B1FC6FE2AULL, 
            0xD68BBCE9FF225F48ULL, 0x1C0E1C5B7747E7C5ULL, 0x16CC67B5E0FA8E61ULL, 0x4A11BA17F200C260ULL, 
            0xBED2DC5C2304C345ULL, 0x70D48F25B02072F7ULL, 0xC82425F8B8FF8DEDULL, 0xD92789AFE21401B0ULL, 
            0x6D0ADA44C549224EULL, 0xE7C70EA5828258BCULL, 0x4C28CD859305C4F9ULL, 0xDE15080573865B86ULL, 
            0x6DD17206993C3FE0ULL, 0xFBD808A784376706ULL, 0x0D64AC8807028A26ULL, 0x037924B8BAE2F0F3ULL, 
            0xA4E66565A38433C0ULL, 0xA8E8DD3E3213D204ULL, 0x4B4FD3AEFEF71E1DULL, 0x87E3E071180A4635ULL
        },
        {
            0x18FF1ACB77CA5265ULL, 0x14936F8D66FB346AULL, 0xF6DF36B25135C3E9ULL, 0xB97EB7CDAEAE69D7ULL, 
            0xABD33C6F15C93894ULL, 0xDF7E92EE0989F93DULL, 0xF5020DBA4139F228ULL, 0x809F2F3504341E2AULL, 
            0x3C9C0AD88822AD61ULL, 0x66A7C310C2176CE2ULL, 0xB9EC957BB7F76AE5ULL, 0x474BEDEF42342818ULL, 
            0x290354B655E5A389ULL, 0x59E6EF9067D05919ULL, 0x5DE40FFF45360066ULL, 0x6AC1A62B7D760792ULL, 
            0x65A4408C61A2085FULL, 0x829DAD3519786732ULL, 0x52ABE22F76108AF8ULL, 0x2AC1B107BFB7D996ULL, 
            0x28831DCD31A01B0DULL, 0x272AD4FEB6663BBDULL, 0x8A9F500D2B30D134ULL, 0xD1D88923ECF8A19AULL, 
            0x7DC176CCF8AC3D14ULL, 0xB1930436F0D02687ULL, 0x22BACA3BF518D22DULL, 0xE5867E77EA558B39ULL, 
            0xF88D192A78F010D3ULL, 0x7C767D2E3F924EC2ULL, 0x2AEC5036C93176F7ULL, 0x29A6F4F0F46788E5ULL
        },
        {
            0x9A628C9EE229142DULL, 0xA0648CEDE60148BBULL, 0x800AC0AD3C9C7B08ULL, 0x5A63CB8034172249ULL, 
            0x430E493C038D6F79ULL, 0xB15D6F46939E8F9DULL, 0xFCBBB9B13FF98534ULL, 0x405CA85CC4281ED6ULL, 
            0xABA60F29138752DDULL, 0x4D47470ACE757C94ULL, 0x2D352BB279466234ULL, 0xCCC7AA8653AA6B5DULL, 
            0x0B1A296D22D7B2C3ULL, 0x2A50831382EBFCE6ULL, 0x1EA4C5A3D38F4373ULL, 0x07004413C6D4941AULL, 
            0x03FA6AEB114DCC69ULL, 0x0C3DBA06962B6613ULL, 0x812B6AF3E1FBEF81ULL, 0x74F5697644C681ABULL, 
            0xEA5F66584140C819ULL, 0x039D4EDF951B1CC1ULL, 0xF8B79D30CE226C9BULL, 0x05540BB63891DB1DULL, 
            0x9678EBF471A2D6DEULL, 0x2B159A23B6AA3FF8ULL, 0xC0C892EEE9F018E7ULL, 0x28818FE044191A4AULL, 
            0x9A355B5CA01ACA58ULL, 0x67CF3A2E05F2AA97ULL, 0x2FB4CCF294EF2849ULL, 0x7F7A1181B993CC7DULL
        },
        {
            0xF6DF7445F78CCBA7ULL, 0x890DD56A207DDD05ULL, 0xFE961A7CB5A24A49ULL, 0x3E473C8CA63389E6ULL, 
            0x40EA3B2B666B3302ULL, 0x36FFF78A36F0D57CULL, 0xD229EF9C28C43444ULL, 0x6EBDF9BE01B02981ULL, 
            0xD9E7FD379915781AULL, 0x99E1F64BF3C60CB3ULL, 0x4C623240CD574EEAULL, 0x11ED40C5347C3DF8ULL, 
            0xE653DF7C99FF23E6ULL, 0x66CEB1BFA1633BF7ULL, 0xC830312D16A4AB20ULL, 0x1CB02B17729CD007ULL, 
            0xE238D0577CE248DBULL, 0x09B9CD3A9B5A3A0DULL, 0xF9718C31578F8384ULL, 0x4F65C7100EEA8834ULL, 
            0xDFD0012ECFCA741CULL, 0x5BF8F030A946BF57ULL, 0x6228865564426FDFULL, 0xB2D7D0921617BCB0ULL, 
            0x4B048ACC1EB5A54FULL, 0x90BA67FFEF74CB27ULL, 0x68DE6D666567C1FCULL, 0x4C2E400C0AFB5CB1ULL, 
            0x7450BF4CF9E2A329ULL, 0xF4F7C0F039A4166DULL, 0x589030B7EE8C2B62ULL, 0x7A26558F2BDD02FEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseEConstants = {
    0xB5209C83B4D62996ULL,
    0x6DEA8C05E577FD4CULL,
    0x71029DB61635E688ULL,
    0xB5209C83B4D62996ULL,
    0x6DEA8C05E577FD4CULL,
    0x71029DB61635E688ULL,
    0xCA991894908B88F5ULL,
    0xF3F4992146E72203ULL,
    0xAF,
    0x0B,
    0xAE,
    0x3B,
    0xAD,
    0x37,
    0x63,
    0x79
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseFSalts = {
    {
        {
            0x342104FD33E12364ULL, 0x54D7805E8F6EACC8ULL, 0x8D148E41CD845238ULL, 0x214C6F09133CD7BEULL, 
            0xAECEF3DBB5D7F194ULL, 0x333EDABC3B3669A2ULL, 0x70A9D528F9C42444ULL, 0x9E4C8A652209DECFULL, 
            0xDE10A3396BD5AA39ULL, 0x7370A26D03FBCFC9ULL, 0x055DE2EDD308F02EULL, 0xCB7DDE0C5DD4C9B0ULL, 
            0x7FECA77C714E19DDULL, 0x6DD413D09C58CCDFULL, 0x8C8D8ED4B39CCDC5ULL, 0xF9529048D524E578ULL, 
            0xD55A69DA48C98655ULL, 0x2F1C81AD0C3483C9ULL, 0x2B8302F9DF0628D0ULL, 0x7D7F6015ADC2FA1BULL, 
            0xC2398818053FE125ULL, 0xAB47B0AAA2841FA8ULL, 0x86A79132568D3DE0ULL, 0xF4C1671EAD1A8804ULL, 
            0x0A2EB485A5B3535BULL, 0x32C61731B2554485ULL, 0x1E96D5B22858C10CULL, 0x382CF7F15EEE2088ULL, 
            0x5230B5836136B3FFULL, 0x62E635D10C03BB65ULL, 0x93F306AED00B3AD1ULL, 0x88A94E544190EE64ULL
        },
        {
            0x1C8BBFD07C7C3E6BULL, 0x604DF46FDD99A1CBULL, 0xD89F65E8C8F0B8CCULL, 0x59DDC08AC23D7034ULL, 
            0xBF2158F296D38219ULL, 0xF9CC254EBE21071CULL, 0x03B68B0699942785ULL, 0xFE81F581435B1A74ULL, 
            0x96893D5E43E5E407ULL, 0xD3A836F2943DC5CEULL, 0xF05548E64C995EEDULL, 0x7624125CE88AA18EULL, 
            0x3D23DDA4E029A1F5ULL, 0x101BEEC1908DF8FCULL, 0x33FDB9235FE93FD0ULL, 0x704F59B78CB5206FULL, 
            0x4EF7F6953324B072ULL, 0xD2DF4F045468BF03ULL, 0xFE81D7A68D2D0CB2ULL, 0xF2A2850D6F5FDD64ULL, 
            0xC708047E2E1D85B3ULL, 0x09111735DDDDF63EULL, 0x446938AFFADB8194ULL, 0x38940EC725C80D2FULL, 
            0x5322E5377FA40B28ULL, 0x528581690A4D4666ULL, 0xCF781B12E98A3E12ULL, 0x65167C910CCC016EULL, 
            0xD951BB9A848D06D6ULL, 0x6E3E124D2E4996BEULL, 0xC299E421CE6753E3ULL, 0x4FF7EFA93D0553FEULL
        },
        {
            0x2D05BE1D3C4AE4F9ULL, 0x500979C5358B54CAULL, 0xB26F6F222EE6B967ULL, 0x8ADEB2A224D512DFULL, 
            0x872FEE0D84D2FB28ULL, 0x65AABD72A02F77B7ULL, 0x23B788C76AEB56AAULL, 0xEE9481385163D7DEULL, 
            0xBBE55F9962F57E48ULL, 0x504F07319CD4129AULL, 0xBBE3A20A9C484425ULL, 0x706EC9302D409FD1ULL, 
            0xEABBB1ECECC8BECDULL, 0xA38B96D0E30972E4ULL, 0xAAB246A44D56D46EULL, 0xFF3E5D175F137E04ULL, 
            0x819EB983F4A5B890ULL, 0x1A4782193E736DE0ULL, 0xD9C116F61FC8B54CULL, 0x09A57256D074D1DEULL, 
            0x3544C58C45241E5EULL, 0x02A0F456A201E116ULL, 0x3433304262EADF6FULL, 0xC51DAF9EAB22D0CBULL, 
            0x0F469FB4FAE83B35ULL, 0x2AD0D5DBBED95E33ULL, 0x5AFBB0287B400A33ULL, 0x0FB310F5614289A4ULL, 
            0xEDCC97CB1E510351ULL, 0xB0628481D104A676ULL, 0x93875275E798EE60ULL, 0x9EB5AAF480FC23E0ULL
        },
        {
            0x8943BD5A3E456A02ULL, 0x05AB075E4F448C07ULL, 0xFFE596DA0C270998ULL, 0xF209FEE40C817405ULL, 
            0xBEE7FD6D27E122DEULL, 0xAE5B7CEF5CFA99FFULL, 0xE630383DF1943138ULL, 0x8A8BA98A4E3B0167ULL, 
            0x5A70CF5AFACC38E1ULL, 0x73781B0C5166479BULL, 0xCD276B0447401FD7ULL, 0xA00F03E0323EF48BULL, 
            0x35D2E58AAECBD5DAULL, 0x8B41D744D5B8407FULL, 0xB63DFAC699637623ULL, 0xDB0489B54B8B0F6FULL, 
            0x6B6406753C796BFEULL, 0x3832A707969A92AFULL, 0xC0EB5B5ADBD41192ULL, 0x157A0587C5380480ULL, 
            0x1789647F0B74438FULL, 0xAF0811E58B407066ULL, 0x37E2E00735176298ULL, 0xADE8E7F3482D9640ULL, 
            0x372C59D35073E9BCULL, 0xA33F32F49F507B16ULL, 0x680CF3494E91D0CBULL, 0x5B4CBE4B57892962ULL, 
            0x2152DC5A14F20E66ULL, 0x5C9EE1B43244A2F9ULL, 0x7FAA6EB845561B3EULL, 0x966473E91010A6C5ULL
        },
        {
            0x7A1EC5642297E22EULL, 0xD0BE899F0B48E183ULL, 0x09374DA69EE79C5EULL, 0x4B6F0665E6D52A41ULL, 
            0x35974CBE68764912ULL, 0xCA81CB76D083C026ULL, 0xCFF84B39D22188D2ULL, 0x8A5DC7573ACF5ADAULL, 
            0x09C802AF8436A6DAULL, 0x89D6C7CC328A20E9ULL, 0xD01BFD99BE0D6667ULL, 0x03C98309406A9CC0ULL, 
            0xBCE5C8D5B6A3C8DAULL, 0xC3E58259F68F635EULL, 0x0B2D832A4C2C56EEULL, 0x048602AD7EF03548ULL, 
            0xD8D9177C8D1C581EULL, 0x32A7ED9D55951132ULL, 0xF0AB163E584D0DDAULL, 0xF980B3EAE097DC7CULL, 
            0xFADD282B7D5C870CULL, 0x6D7450E0454A57F4ULL, 0x4DE58422262A6D47ULL, 0x45A3B8F8B181CD28ULL, 
            0x3A1E6546BDA9E5BDULL, 0xB6852994817A6F36ULL, 0x237683B4E8ECD6EEULL, 0xAB5AE141FF54C2FBULL, 
            0x11EA0CDD41D2C3CFULL, 0x0FA07B12C9806496ULL, 0xF495E4A4151BF2C4ULL, 0x01276C74D427CB7CULL
        },
        {
            0xBB58FC505F7F9185ULL, 0x152D16BF6DB2D27DULL, 0x6FD1EBB80D5A3484ULL, 0x9A8EF9B3E3AE714FULL, 
            0xBBA8CD94F5E798E0ULL, 0x7420D393CAAC4253ULL, 0x072B4149D48CE620ULL, 0xE36398307DD9B7C8ULL, 
            0x2DB9F7D2AB3D4728ULL, 0xA7EA9D7274B9267AULL, 0x5997A4C8269437A5ULL, 0x1B0C446E9184479DULL, 
            0x34E9B7A9ACC9FDD6ULL, 0xA38F4DC4CE0EA5F4ULL, 0xF6921F80F0133C81ULL, 0x756C8EB726586614ULL, 
            0xD989019A6793AD3FULL, 0x82FC3584678D2D2CULL, 0xF291C826AEB5BE45ULL, 0xB8448F6F15EA91C7ULL, 
            0x0095C8EACB685DB9ULL, 0x4C9CA60281DFF057ULL, 0xA2A2ED2CAE494AEAULL, 0xE0105E0DFB625853ULL, 
            0x3F4EA973A6BD30F1ULL, 0x4CF3C01032230BA3ULL, 0xF85F991F3B0E99F7ULL, 0x2EF70901BD418A5BULL, 
            0xAE41C7894B517D84ULL, 0x2882123D49529C29ULL, 0xF44995858EBE1C97ULL, 0x0A8220DA5FC19032ULL
        }
    },
    {
        {
            0x051F0435FCE798EEULL, 0xC9ACB8AE2F14352AULL, 0xCFB3B251E016F54BULL, 0x9D66D32CD3C00200ULL, 
            0xC5BEBAD0BE179715ULL, 0x0F37B5321823FC0DULL, 0xDE9C5ED731B6BE0BULL, 0x03EF791CBA28E9F6ULL, 
            0xF71AAFDA4EECCCE3ULL, 0x54D156D6A6A123E6ULL, 0xF8599BF74C634488ULL, 0x5F579D61C1265C53ULL, 
            0x11333165FE791DBFULL, 0x4201DAC7C477B3C4ULL, 0x001EDDF27C4549D8ULL, 0x8BF1C401C8188138ULL, 
            0x00D761DCDA5B8708ULL, 0xC437B95B89F3A88DULL, 0x7C55629158BA1BF4ULL, 0x1D5736D848B09F05ULL, 
            0xA92E582F886123C6ULL, 0x55483457F2F6FF4EULL, 0xA0341F1B4634D49BULL, 0x1AADDD0402915DECULL, 
            0x6A634EBB1EA62D84ULL, 0xEC3A5D7E240F6390ULL, 0x537682373FA0DAB9ULL, 0x99D8F603D82C2D21ULL, 
            0xBC86A4B6F040991FULL, 0x198CF020F21012D4ULL, 0xD0C2F24811F874E4ULL, 0x6081BA6FD636F973ULL
        },
        {
            0xE190A87209648F5FULL, 0x00FA59EA1E664320ULL, 0xBE6F5F71313A2BA9ULL, 0x1DDF9226966BF673ULL, 
            0x4F586AE441F0CDF9ULL, 0xA9F3FDD81C500A9BULL, 0xBA686EB8EC354170ULL, 0xD17EB8107BFFF1CBULL, 
            0x9867676D7DC68051ULL, 0xC5DB562F7D89DD25ULL, 0xB2DDABC02551A689ULL, 0x0EDAD120E09581A5ULL, 
            0xB592D4D0AEF75B63ULL, 0x0EA5DD0084CB3688ULL, 0x859F6E08CF50223CULL, 0x73623BC3493B7DB2ULL, 
            0x2656780C4D5899EEULL, 0xEFA0C19AA94C4C56ULL, 0x8E4B1FA45D2DA2C0ULL, 0x3921AE710B309A59ULL, 
            0x583E9D420A4B1F4EULL, 0xEA3D48C67FAD4727ULL, 0xC76C69BEB57EA6C0ULL, 0x8B19A0E2E25B170CULL, 
            0x893B336877158137ULL, 0xEB5A8D3563549E78ULL, 0x9FD7FC778D51EF46ULL, 0x41076A68C5E91BB4ULL, 
            0x24C32105E617A6D4ULL, 0x0D85D224BC2D8832ULL, 0x3DDADF1A6F228FE4ULL, 0x6664D2A5F9CF0666ULL
        },
        {
            0x66BD5E1D4C58B609ULL, 0x2D8AA7DE66BFD8DBULL, 0xB210CCDACA48401EULL, 0x63BD0612A5B28B82ULL, 
            0x5A340D69067772A8ULL, 0xF908902F405F7880ULL, 0xAC0837FB04D68555ULL, 0x97FD870C88914513ULL, 
            0x9924F62201F3A5A3ULL, 0xBAF0736C88EB2381ULL, 0x9B9B1CC37F23BF5FULL, 0x73EC124713E5B408ULL, 
            0x461E8B631027154BULL, 0xD32A70E31F1CBD30ULL, 0xE94A7F3D6FBA9C5EULL, 0x0C50878C24AD14A6ULL, 
            0xDE3C37CD9EA69AE7ULL, 0x513CD261C179DE4AULL, 0x1AD6F56CB1E10022ULL, 0x06EA18AB0F504EC7ULL, 
            0x146F0FE27AE3FCF9ULL, 0x7C05F61AEDEE9BE4ULL, 0xED945C66BEDBF690ULL, 0x4B5E4B86EF525FE0ULL, 
            0x55366ED8F8816137ULL, 0x852982651F653E59ULL, 0xD718C5D30DCEF81AULL, 0x6E937DC4AE2728B9ULL, 
            0x7B44B4B6C127BA74ULL, 0xD6B6DBAEBF279BE1ULL, 0x2C2BD5CA03E79471ULL, 0x612E992ADE1D0655ULL
        },
        {
            0x8EC4B0C9A725B8C2ULL, 0xE37B54462F9AC71CULL, 0x91FB30E6A8CFBAEBULL, 0xA4987EAD11D3BA30ULL, 
            0x168A93D17C5391A4ULL, 0x970D88C85B5AA953ULL, 0xF028DA92060A7050ULL, 0xADAAD6009613D516ULL, 
            0x96245545F8721D1EULL, 0xC4014CE673CB33F1ULL, 0xBDB86A2BE0BDC7EDULL, 0xCFAC26AB0FDF00E2ULL, 
            0x9BBCA448DF09A2B4ULL, 0x87B4B669A9162020ULL, 0xF49BD4EB348E9505ULL, 0xEFCAA09B370E2C26ULL, 
            0x62D770E342B186A5ULL, 0x64EC67BC5F33790DULL, 0x288B7A29A382D441ULL, 0x9E6C026E37B74320ULL, 
            0xEF9FC4496447D1D1ULL, 0x8A1A01F1CC29766BULL, 0x5C46B3FEE52404FCULL, 0x55ED92779081EC45ULL, 
            0xF9D1B819B9FA8814ULL, 0x28CC1536182AA3ABULL, 0x055D07A24E1078D1ULL, 0xA6B14189460D7F3BULL, 
            0x152D2B26E954067DULL, 0x4F6543D90E161176ULL, 0xAAB496787CBABBC9ULL, 0xD37D82A192329789ULL
        },
        {
            0xFBDBEACB4851911DULL, 0x188FAF766D60C736ULL, 0xF9BDDF82B9756168ULL, 0x1098239C7FF7808AULL, 
            0x046CB1DA07861C70ULL, 0x3F616651A1B4E841ULL, 0xA6C6AE6C581C5FA8ULL, 0x03E89623DA4CB5CAULL, 
            0xC3ECD75AE5235BE8ULL, 0x81EFF8A7BE5B5F16ULL, 0xB3D4C7A446A49B0CULL, 0x69CA81A5743D1778ULL, 
            0x75874E4D744B365CULL, 0x190ACA82E2CF67D1ULL, 0x7F566851205276DEULL, 0x57E4AE3609E00D48ULL, 
            0x5873A6F3AC2F189BULL, 0x5F3FD770545EC840ULL, 0xE76AD1ADECC5D20CULL, 0xBC1EB7FFE201E006ULL, 
            0x180AA58D9FBF630CULL, 0xECCCE6B5F7038CDDULL, 0x0950CEF7D6C7B4F7ULL, 0x79AC7398E3FAF390ULL, 
            0x494A40B7ED1F762BULL, 0x4D3958B162ED18FEULL, 0x57539063A70A8BAAULL, 0x5CA0D427F517651EULL, 
            0xDD638BFCB1BEA1FEULL, 0x6FEDDA1B98A51F22ULL, 0x09D450F7EE3736E7ULL, 0xF2B48658737299F9ULL
        },
        {
            0x9D6A1EB73806018AULL, 0x684999C6C7A1FFBFULL, 0x6811163A254F4C0AULL, 0x8FE5F636A56793DAULL, 
            0xA39C978025707588ULL, 0xFF6894A0B9A3B5C7ULL, 0x8BC7E078B115835BULL, 0x2B2FCDEB119DDDF9ULL, 
            0x4CB8D5D80FEFCACCULL, 0xF66BA2FBDFF5715FULL, 0xD83AB386BC6ABF2FULL, 0x91A2FF745BDF56DBULL, 
            0x977F62C402ABBCC2ULL, 0xE6C031186EB05BDDULL, 0x56D3BF9236B52E6BULL, 0x6089B7EC49E3C000ULL, 
            0xA13715F482302317ULL, 0x65746E30A65601E5ULL, 0x86DB34946A91096BULL, 0xDE86D8CF2B5E361BULL, 
            0x8C20CE44FC4C9F8AULL, 0xE2760EC59AF531E8ULL, 0x212A49DD5D0284BEULL, 0x0992CADF260CB5C4ULL, 
            0xB59AC2567F88AA07ULL, 0x53F8F54D26F18604ULL, 0xB48D631CF221FC60ULL, 0x872CB43A6EB28696ULL, 
            0x11826B000997C6FFULL, 0x9B5F9A7708616B0BULL, 0x915E1701F7BEBA4AULL, 0xB1459578ED00558AULL
        }
    },
    {
        {
            0x08FF583F09283987ULL, 0x5E1043C8F4CD3AE0ULL, 0xDF92097E6FEC65E2ULL, 0x5FF27F4BA45CA53EULL, 
            0x0D0B87827F36A224ULL, 0x5759C260D1621B9FULL, 0x7A8FB68F045DBDF3ULL, 0xEB2A0ABAEB38359CULL, 
            0x2173287518B5C64AULL, 0xA8CB5A1452A091B1ULL, 0xA9F1CCAE4F6D90F2ULL, 0x0C93755139947EC3ULL, 
            0xE1497FAB5AA8BE42ULL, 0x5D43E44CB70E0238ULL, 0x5C5198C933B2CA35ULL, 0x7B5A1885EC736F10ULL, 
            0x88DEC3F088456517ULL, 0xA3356F26BB5592F7ULL, 0xE3B5698FE2140DD6ULL, 0x2AA8863299F28412ULL, 
            0x743F3A791F2484D7ULL, 0x214C0C4ABD3C7033ULL, 0x58533E82F9DFF2E6ULL, 0x643357715F000EC8ULL, 
            0x4BD0851FE2D63D2CULL, 0x553D24266A7F3AD8ULL, 0x6F61E31FB32357ADULL, 0xEFA96DF77CAF5C28ULL, 
            0x4D8C366B7E7A15DCULL, 0xD851D1DCA2AE831CULL, 0x13FD424EF30823BEULL, 0x77D86D72B15EF31BULL
        },
        {
            0x41BEB0D298F6D708ULL, 0x53E6E3DF2B4E7844ULL, 0xDCA261CFD39CF698ULL, 0x4967F686ACAE82BDULL, 
            0xB62A22996D151D21ULL, 0xA6A63E227341C253ULL, 0x6CD3517577D8EE36ULL, 0x8D3BD657C36A099CULL, 
            0x200361B118CFD1E5ULL, 0xAD70662C530EA8ACULL, 0xE77E486B6B981E3AULL, 0x451EFB4103790FE0ULL, 
            0x8F5FF3ADC623A44DULL, 0xC30FFFFE62445AB0ULL, 0xFBC02B50CC8CC12FULL, 0xA3F97CB23FDF6264ULL, 
            0xFFE19FED654B8429ULL, 0x1563CEBE0924665CULL, 0x0C3B63B1FC841866ULL, 0x0C0665022B55787AULL, 
            0x4D242BD1298052B2ULL, 0x11AE2B72404FB7FCULL, 0x0A38F53BDF18615FULL, 0xF8DF97ED30A78E78ULL, 
            0x0FC07EB99D7ACEC7ULL, 0xEFE3D1096427A987ULL, 0x8E78021F85D3E0DEULL, 0x696241DFA4CE51DCULL, 
            0x8CF5B7721A88E716ULL, 0x7BDEA6F53920CF1AULL, 0x7158B9FE734D85A5ULL, 0x842B1D52E268E7A3ULL
        },
        {
            0xE0CE2AC5FF81829FULL, 0xA27786E164C54288ULL, 0xC803ECA8CB2D1299ULL, 0xDED3C73D4A5CB5A4ULL, 
            0x5A3A34B8BAE87AA8ULL, 0x974BCAD243ABA280ULL, 0x73A7B35ECEE69674ULL, 0xB56E211EB4B0D1CBULL, 
            0x6BB0C29BF4B73570ULL, 0xC862585E3ED81732ULL, 0x3CA79BD8E08E0528ULL, 0xFDF9095E75B9004CULL, 
            0x61A6CC31E0F1FA34ULL, 0x838E8F58E6785FF5ULL, 0xA5309717877A334EULL, 0x7DAA26C50951AB18ULL, 
            0x55EAA56742511469ULL, 0x226E371999AF4961ULL, 0xC2F080A0B0CA446EULL, 0xCDB555F2ADA864E1ULL, 
            0x1162AB068C3D8B1AULL, 0x1FC4E1987081BAC2ULL, 0x641E42382ADBD043ULL, 0x54E7BB7577E75A2DULL, 
            0x065A9C8B0F425255ULL, 0x0E7F8B35284A78B7ULL, 0x9412E7E806B42960ULL, 0xCC591880B0B3B290ULL, 
            0xD25F1ECBB1C0ED30ULL, 0x441229207476432AULL, 0x43564DCE66CF5DE9ULL, 0x721A2A51891C810DULL
        },
        {
            0x4EE671513E08C2E0ULL, 0xD024F5EF9B11A5B1ULL, 0x54B164592A96681FULL, 0x636202451665CB83ULL, 
            0x61C9B8D143430C73ULL, 0xE766B8260B41D300ULL, 0x44865096AC88C36CULL, 0x4156C85458CE13AEULL, 
            0x2BD2B2E22916DB3FULL, 0x1A4660E0F20FC6A9ULL, 0xFD5290CA034E5A52ULL, 0xBF9E2A6CD5C95620ULL, 
            0xBEAE37A17329EFCEULL, 0x04B8FC5ABBED75ADULL, 0x8C04536E55905187ULL, 0xFEE2F416315C3162ULL, 
            0x7D49379124068C0CULL, 0x30D0917ECE562450ULL, 0x908F382C500B1DA9ULL, 0x34B275D6AD99DEAEULL, 
            0xDE22F13CAEAC3791ULL, 0x8C12F2920CD49881ULL, 0x79B864664BEBE13DULL, 0x340130488D324128ULL, 
            0xE63FE8AEA0DF7F1CULL, 0x1CBFEB55C814D0FBULL, 0x648F2CA8EE1CD3C8ULL, 0x1B5EA151554CC963ULL, 
            0x7DA2E2D2F637A232ULL, 0xED671DE5EE09ACEEULL, 0x8D8237322080E2E6ULL, 0x8E37D7943C7848F4ULL
        },
        {
            0x17FBD0718BD25540ULL, 0x102B0C833C86A5D3ULL, 0x101F7DA189177171ULL, 0xE958E4DFDE39160BULL, 
            0xA1505B459815BA33ULL, 0xAED88C5BD23054CEULL, 0xAD54A741B7EC2A44ULL, 0xB28215F5A3CC7473ULL, 
            0x2166D6FED2FAA311ULL, 0x4380D9C2C8BD6C6DULL, 0xD39B0964C9734B14ULL, 0x4B102E44C3645D90ULL, 
            0x51E9366575E25D44ULL, 0x319B5F7AD73B7109ULL, 0xCE62B1D35F9E51AFULL, 0xE32035CB9B5FDC75ULL, 
            0x5703ECFD6DB2E9B1ULL, 0xE712AC1CDF838C4FULL, 0x2D508574539EE6D7ULL, 0xFE2487CAD53A27CEULL, 
            0xEEE6EB3853B3DF38ULL, 0x59236FE5631E3363ULL, 0xF286A9E1892A909FULL, 0x62FE3CA3F5C0EE3AULL, 
            0xCCE0CDB0C3DB2B28ULL, 0xDA0D9957F69C92C1ULL, 0xAE20FECC857FCC03ULL, 0x6A51686FADA82501ULL, 
            0xE22BC61201AEEE43ULL, 0xB76DC63C0BBA6FA7ULL, 0x652446E29D49C1EDULL, 0xBA286F0A089EA0C6ULL
        },
        {
            0x7ECB660BD4910AB0ULL, 0x95025A7021FCCAACULL, 0xACB4B20C7D64553DULL, 0xFB353F336AEB00CEULL, 
            0xCF899FAA7769B7BDULL, 0xCF860C40761D7E40ULL, 0x1A57A7231E01FB73ULL, 0x9BF05177C6CC4EE8ULL, 
            0x583D85DDC1E9F6D0ULL, 0xCEF1D698636DA71AULL, 0x1F2898B3C6E3A0F5ULL, 0xB4137A80754151DFULL, 
            0xE9E289D8AF5DA6D5ULL, 0xB99B5E1D9B18F417ULL, 0xB597FD4E7361E92FULL, 0x658C948EC3E36236ULL, 
            0xCF5144368E035C28ULL, 0xEA107E008EB5AE1FULL, 0xE557CEDCA4BC7190ULL, 0xE6C1285C4CC2D667ULL, 
            0xA167002B0F3D8303ULL, 0x0D4B181A69B734C2ULL, 0x892C2430A55FC6E6ULL, 0x3BDCA3DC027F7B54ULL, 
            0x66CC69AC8242767DULL, 0xA59B8C1967842566ULL, 0x9B58444C05E40121ULL, 0x827A752E30D1D005ULL, 
            0x3033EE6FB6B7A346ULL, 0x6AABE581F21C9614ULL, 0x86FB90328E9030D8ULL, 0xB124C22208F905F2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseFConstants = {
    0x3B264B8C69E398D2ULL,
    0xEAAE2B20177A02E9ULL,
    0x15AD3EEED8872AA1ULL,
    0x3B264B8C69E398D2ULL,
    0xEAAE2B20177A02E9ULL,
    0x15AD3EEED8872AA1ULL,
    0x0426FE3A5A342692ULL,
    0x3F2BEA7D4CAA7A6EULL,
    0x05,
    0xA7,
    0x0C,
    0x3F,
    0x44,
    0xB8,
    0xE1,
    0x82
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseGSalts = {
    {
        {
            0xEF99394C8D7F1ADFULL, 0xABEC6DDFB7A5326EULL, 0xADB3DE7DD9CFA2E8ULL, 0xCFE6BAD8595D07ADULL, 
            0x1624AB2202312C14ULL, 0x2D822A6AF71CEABCULL, 0x8F8575DA89AFCF3EULL, 0x3C26B946AF77EBB5ULL, 
            0x1E9A9C0AFFB961E2ULL, 0x899F3A1F20667301ULL, 0x1C6CD32692BF5976ULL, 0x366BFA5100A54861ULL, 
            0xF602EF77B2A8E9D0ULL, 0x5CF39560F8273EF5ULL, 0x803370B74C66BA85ULL, 0x20D1C1EFA3A57560ULL, 
            0xCC357CC414C6C5E0ULL, 0x006FBD9A964F6154ULL, 0x50E1A1C594A72F77ULL, 0xF8E9B916DFE34DF2ULL, 
            0x41DCC5D83547EEFFULL, 0xA406763F708B9CD4ULL, 0x2D59162963C15B38ULL, 0xB002A3E82860FA18ULL, 
            0x105FDCDCCF131501ULL, 0x5F3426ED3BC38F61ULL, 0xD5ABD5A4C504D590ULL, 0xFF5FAFDD6D0FE63AULL, 
            0x50F2D820489F4EDDULL, 0x77F4EE41D5A1EF3DULL, 0xF09B12A9D20EB6BBULL, 0x97965E19B146692DULL
        },
        {
            0x4E02509276A4D562ULL, 0xA6D3C2C12D4E532BULL, 0x7327C261FA043DE3ULL, 0x9CDA0423CC5187BEULL, 
            0xA7BF8196FC6616B2ULL, 0xBF1AC6D207701C7CULL, 0x594589068783CF0FULL, 0x9A0DF97E3783AA73ULL, 
            0x1D2C0232CEDAE860ULL, 0xFF0714406538B5E7ULL, 0x784236CEBAE566B4ULL, 0x051AC235D59D7ADFULL, 
            0x1C0A9AB816438439ULL, 0x45D7F25493182096ULL, 0x04D5D01E3CF064AEULL, 0x75428006263A9989ULL, 
            0xC3AAE3E7641DCAB7ULL, 0x61EB289F0B1E0034ULL, 0x6BB773D57173B891ULL, 0x166217FB1D2B4D31ULL, 
            0x1494454947249385ULL, 0x1ABFBB012E666674ULL, 0x1537B439529D78F6ULL, 0xB7B154F78BEB315DULL, 
            0xFBF68A9D53D97B16ULL, 0x79BEB41A42B55F67ULL, 0x29792231B8EE3B34ULL, 0xE77A7CD30A44228DULL, 
            0xA2D3864564151E11ULL, 0x5C98D723C1219169ULL, 0xE76AC6D88F3BD881ULL, 0x624343BF80A7590FULL
        },
        {
            0x809CFE3C32642D8EULL, 0x477940547CBE2B8EULL, 0x857B8AD1B87B8DCFULL, 0xE17AF1608C968E68ULL, 
            0xA1C13900C8E3E15EULL, 0xDAA1A664D29B2402ULL, 0x989ED307A6E0F1DFULL, 0xDF0AB6C869CA7647ULL, 
            0xCB452B33E59A1942ULL, 0xD177B4C74E89425BULL, 0xCBAF5AA590013D81ULL, 0x368EEDDF00F10EFBULL, 
            0xA115C3DBF7CE2D9DULL, 0x05453A204B6BD6C7ULL, 0xB4502A09AC047F6FULL, 0xAB42AF9D0C283705ULL, 
            0xD049727A24EE3816ULL, 0x1FC24A9EBDD51E82ULL, 0x03DF7B5B39F695CDULL, 0x46096A9CDC43EF0CULL, 
            0x8EFEB44AEBAED2F5ULL, 0x8C32599C4AE0101CULL, 0x5AE653B7257478A2ULL, 0xFB6949B8D357B1ADULL, 
            0x8FB293B77ADA6822ULL, 0x724316A9BA15F842ULL, 0x1F2FEC0F366CF3BDULL, 0x3AA904015544B921ULL, 
            0xFE5A68AE670B9A67ULL, 0xFFB03A2FBD3933C0ULL, 0x45E9446022BB2209ULL, 0x44501C3F1CC3B8D2ULL
        },
        {
            0xCD385AAF2B8A252FULL, 0x642BF71B21DD0032ULL, 0x57269B6D8761156EULL, 0xE567581256670B81ULL, 
            0x7EA7FAFEDF1A2417ULL, 0xCF6BF2527290ABB2ULL, 0x048ADCA333FBEC60ULL, 0x928DE5A7E1F1E88AULL, 
            0x0EB2C2168BC3EB62ULL, 0xC8C1B62EDC9F7853ULL, 0x53FCC97ED24F9A53ULL, 0xE2F4D61D44160085ULL, 
            0xC42AAD8C0A3CBD7AULL, 0x528A1A7AD3DB7CB1ULL, 0x22FE3036135E3B0AULL, 0x68B2228B142F3C5BULL, 
            0x0AC3B1AD737715FEULL, 0x81FEB31290FCCE05ULL, 0x9CF0AD26BA36B83AULL, 0x1EF49D65EF7437EAULL, 
            0xB5A6A16419F88C89ULL, 0x6D3C6C8276211881ULL, 0x05C393AA1251A5ECULL, 0x7102F7AD14DD373FULL, 
            0x3A814C0006CC5DFAULL, 0x3F8C47E3AA385D04ULL, 0x4580598447646236ULL, 0xFC9E8DAFC710A418ULL, 
            0x5A724805326172F0ULL, 0xE1B9BD913AABF6B1ULL, 0xE569B49DED9015EDULL, 0xDE14B66421339BBAULL
        },
        {
            0x2B66E294176798A6ULL, 0x7540E3035C918D38ULL, 0xE499725B13944D60ULL, 0x1C2F36EBA2E07A9EULL, 
            0x81A255D5504DCDF5ULL, 0xE323D5177C1F27A2ULL, 0xA2C325068C06EEFAULL, 0xEF0916711003B317ULL, 
            0x765F61E2374EF336ULL, 0x6921DDEC683A6FF2ULL, 0xC5DD1B68C3A11472ULL, 0xB015E00B0A263C08ULL, 
            0xD3528C108E567080ULL, 0xEE564FD29E5BFAA2ULL, 0x91885D6A52D74E21ULL, 0x2365B8E6DDA2FCC8ULL, 
            0xDCC66C9C55B3D58EULL, 0x097DBC1FB410A204ULL, 0x4DAF0AB4F656C98AULL, 0x75D544912216B7E1ULL, 
            0xF9AB7624D8E3F31AULL, 0xDB6E285D45B32604ULL, 0xA291A4ECA8FAD992ULL, 0xA190EF66F6C78B1AULL, 
            0xCEB4A00F2804E3AAULL, 0x677999B4D161A224ULL, 0x06A69FA7ABF3D745ULL, 0x9488D04635A056A8ULL, 
            0xE9F0A31563845AD2ULL, 0xECFFD4E6B6E2BFA0ULL, 0x41C63F28DBA6E8D8ULL, 0xB808008CE8EC2885ULL
        },
        {
            0xB849D24A8405368AULL, 0x55B9276648FAE29EULL, 0xA1D033F3F0C59269ULL, 0x6AAD7ECD38291555ULL, 
            0x0EC3DE5386A82583ULL, 0x27FE29D2DB16EF85ULL, 0xB071E02FB794A46DULL, 0xE77CD4B625D101B4ULL, 
            0xB3D9277D6F0212BDULL, 0x030B0FB4147C64B2ULL, 0xF6D7EB9CE6A4D883ULL, 0x03343AF24E6D9474ULL, 
            0x00D5E7C95BB16918ULL, 0x049E0AA08CD3328EULL, 0x55730EC583CC8631ULL, 0x25F103CF9DA51DCAULL, 
            0xF66CC500840183B7ULL, 0x95110EC3AFAE0470ULL, 0x2BC57F7E9AD98C68ULL, 0xAF48728790233A7DULL, 
            0xDD08EE86B6943B45ULL, 0xDF56B07E7B260CCAULL, 0x4139BC3A4D648627ULL, 0xD356418CEC223D64ULL, 
            0xEAB9286EA30C976FULL, 0x28CC2D244DF76287ULL, 0xAC3D8EEB85E5CF97ULL, 0xF22A9568E0A4B4B5ULL, 
            0xFF9F985BD7DCDCD2ULL, 0x999E2B5732398611ULL, 0x2F062C93D3DB3ECCULL, 0x184DCDB5AF0DCE28ULL
        }
    },
    {
        {
            0xC0D435EF303C151DULL, 0x7DF8ABD7E0A6D205ULL, 0x1E30AB35BA922B22ULL, 0x2DDED6AD6F70B887ULL, 
            0xE8F7071C0142D4A6ULL, 0x01DD3BB23D2F2400ULL, 0x89F9C07849D9538CULL, 0xD706825E70DE2014ULL, 
            0xE1EF5255507A826AULL, 0x3BECED18A24B0C70ULL, 0xED1D46E65B97E462ULL, 0x8E18522564277D78ULL, 
            0x6A1CDFD79A535F0AULL, 0xDCF31385B41FD8D5ULL, 0x1E245ED249629AABULL, 0xDE7EA06C4A1BF9C0ULL, 
            0x06C9268E1B9C1812ULL, 0x7947EB6602E8E908ULL, 0x8CB232DFDAE113EBULL, 0x08026C003E882DDEULL, 
            0x0603E35C1204AE60ULL, 0xA4A1045EC27ACCE7ULL, 0xA24D8DFF7DBEF28AULL, 0x3B33AC56C24985ACULL, 
            0xAC6299365072F277ULL, 0xA32EC3707FAE05E9ULL, 0xAED32EB1640C66E0ULL, 0xE04521861FFD0E23ULL, 
            0xE698132F88713538ULL, 0xC734B9CA56D391EFULL, 0x1622E9BBE5DA59F1ULL, 0x21963C3EB9AB592DULL
        },
        {
            0xBB137752C0A5E887ULL, 0x0888E7EC16869555ULL, 0x22AC0102715CB6F9ULL, 0x0039196A145B97DFULL, 
            0x067B73A232ECD979ULL, 0x1A64BDE889191FAAULL, 0x04A15CB346789D25ULL, 0x391F593197F00E1BULL, 
            0xEB725391E049995BULL, 0xAC495B5923CDEAC6ULL, 0x4370B5CA2AAB82F1ULL, 0x081502562F7D5FF5ULL, 
            0x0B4206D937561FFAULL, 0x3F4A90DDDEA9D6C8ULL, 0x37BD182CC48CDEC5ULL, 0x04F1C0D1D10149E4ULL, 
            0x90932125B5720A19ULL, 0x09654FDC5B3F967CULL, 0xD72503C8850CE784ULL, 0x24308082D91659C5ULL, 
            0x0C1D28271204814CULL, 0xF777B5386CE93FFDULL, 0xB3BB6F76B611E172ULL, 0xAFF84F689B764BD7ULL, 
            0x750B0FCBD2CCC413ULL, 0x473E75697DDBE824ULL, 0x95C54355A59C9B30ULL, 0x724E4DDFE19701E9ULL, 
            0x067B3404F9EEC027ULL, 0xE68A47BBEA8AB1B4ULL, 0x2377DAC0CE62E172ULL, 0xB892D91B0F9DDC0BULL
        },
        {
            0x5D3A4BF6E8146561ULL, 0x0E301E6A9521DBAAULL, 0x5B936DBF99794731ULL, 0xC10E5424D21D7106ULL, 
            0x94E90B3EB6AC1A98ULL, 0x589FD2FEFF38D81AULL, 0xC6B6ED785D24E32AULL, 0xB97FC8583EC6AA27ULL, 
            0x72F06961DB510ACEULL, 0xFA159B509708A1A9ULL, 0x3D1B4D30EA52C67DULL, 0xB4D363B846AA2642ULL, 
            0x4B3439FDE9F04E5EULL, 0x29B5059415F0F635ULL, 0xC1EF866F46057709ULL, 0xC20DE9C656F8DFCDULL, 
            0x2CA8A75A4AAEB7D2ULL, 0x06FA543FB00CB25EULL, 0x0FF37B8D61C72EBFULL, 0xFD3107AE24C73E7FULL, 
            0x3E6BECE3A1FB6B35ULL, 0x256F90631830FDC7ULL, 0x2759AA8E99C0716BULL, 0x345F75CB0A39A89AULL, 
            0xD665CBA9E951D73FULL, 0xEF92135B48F96759ULL, 0x42DAF0B751C3390FULL, 0x97711F6547562853ULL, 
            0x220E6CACC40A08D3ULL, 0x94FEF6F046729B73ULL, 0x21A0E1380458BF16ULL, 0x9ED8AC567132244DULL
        },
        {
            0xC7C3ED7041EC85ADULL, 0xC0BA11E262D38528ULL, 0x8ED71E9C452BB9EBULL, 0x011A18BE83B5AEDBULL, 
            0x75708D42EBC9E251ULL, 0x58EFFCCE5658ED3FULL, 0x8279DEC79868807EULL, 0xE97A6C0A377A151CULL, 
            0xBC80843B084BB779ULL, 0x9EA0DC14920DEB34ULL, 0x47BB5C03634131E3ULL, 0x65ADBB2B4308A7CAULL, 
            0x340726A3B1A73757ULL, 0x8A6F2C451DF7951AULL, 0x932C093EC8D1F5DDULL, 0x24DEA76989568CDFULL, 
            0xB2BF3F1E7A086C7FULL, 0xCFC21525BB0C5BCEULL, 0xB2834B52860518F5ULL, 0x990C45603558F340ULL, 
            0x171CD0EB02EF2AC7ULL, 0x69FC6BD4FDE9050AULL, 0xAC2F43E0F8D92081ULL, 0x3A9B2E2F66A21B12ULL, 
            0xAF5B736B754CA412ULL, 0xF2203AABAC5D1366ULL, 0xF18E74B115D26319ULL, 0x8D8D2EB11D417FC5ULL, 
            0xB68D5697002F4CFFULL, 0x70BA4FF8CAC18EA7ULL, 0x06B709460B2F6467ULL, 0x44601358ABA04585ULL
        },
        {
            0x826C814CCA2A9851ULL, 0xC2F4131733F53314ULL, 0x83828D3428C86BEFULL, 0xC633850608752E06ULL, 
            0xC8D87A6C5D63B2D1ULL, 0xF87E8CECDEA8D38EULL, 0xA34D5E0C64591E53ULL, 0x5824C4F2A965BE73ULL, 
            0x2C12AEBA5AC9EB9DULL, 0x2894FE9F07F38587ULL, 0x22074BC93B3C2DE8ULL, 0xDEF7232E225F09DDULL, 
            0x077CB439E3DEA2F4ULL, 0x0079BC324B316BF4ULL, 0x44B14293A8062196ULL, 0xE89D58E992C84565ULL, 
            0x83C4931A8AFEF1DBULL, 0x61C5D82C3E47FA46ULL, 0xBBA0B1A453FEBFFEULL, 0x1AD3CCBB5710FDDEULL, 
            0x780F32D060716CDBULL, 0x6D85DD35021567F8ULL, 0xC219624865055A9CULL, 0x474DEEC8B91E92C8ULL, 
            0x2F9ABC11D2C8EAAAULL, 0xEB01E372A0016AC9ULL, 0xA2C40A7E910E5583ULL, 0x66971C36EBBC5FE8ULL, 
            0x943F92911B4EA56DULL, 0xA5A45A10C9C48088ULL, 0x3DC8C2691AE1CA7CULL, 0xA085044F48515344ULL
        },
        {
            0x3A24C33715884B0DULL, 0xA0D724091C98AA14ULL, 0x6A1F5BED35116AC6ULL, 0x506AA147FA35F46BULL, 
            0x6FE51537BC1CC772ULL, 0xA435B8B87B5F51DAULL, 0x32FC7BCB4F225E28ULL, 0x92318C3939D64815ULL, 
            0xAD93ECA796380B41ULL, 0x2C52386A1F890577ULL, 0x41290305AE836440ULL, 0x408AE2E6DB9CC12CULL, 
            0xCB512E71C1876A29ULL, 0x2BBC8017059E2F76ULL, 0x1DF1E0588FA9C964ULL, 0xB313ABF073B74926ULL, 
            0xB0A6F3ECF4E6378DULL, 0x79F449DBE4959BC0ULL, 0x4B06030B162DB75FULL, 0x6369E3CF34892147ULL, 
            0xE25E8500DEB74763ULL, 0x8A39E36F53821342ULL, 0x0E0FA93CFF068D21ULL, 0x294795E7A8A211ACULL, 
            0xC3ABF8B04FEC1C88ULL, 0x16EC6A036A78481EULL, 0xAD0F8C998F24BED6ULL, 0x2406A0134E77C9D3ULL, 
            0x31178DCE7DC015A1ULL, 0xD384500DB847C2C4ULL, 0x277F6980213CD4D8ULL, 0xAF72E90D896F6F03ULL
        }
    },
    {
        {
            0x5880B79292172377ULL, 0xC309C980AC8DE569ULL, 0xBAC35DC65DD45FF2ULL, 0xC03ADF909E1CBEC5ULL, 
            0x3010F5CC9E0B4E66ULL, 0x65C5A3CDA45FE325ULL, 0x011CAC867A4F63B0ULL, 0x88E62BF56EC474EEULL, 
            0xC47B4B0BBDBD6A23ULL, 0x26F1755C54CD2F50ULL, 0xD9895DA46CF8C50BULL, 0x4A88FB9C276147B4ULL, 
            0x459503716D722C6BULL, 0x61C00ED5AD6CDCE3ULL, 0x2068E53F6E785EA3ULL, 0x838899A83E573BE4ULL, 
            0xAB94A080E794D0DEULL, 0xA75FBB5C7B24EEA6ULL, 0xB61C4F54F2C32E41ULL, 0xD48A0F7E6A114F32ULL, 
            0xFFE8469961F7AC56ULL, 0x9331BBD5F248C120ULL, 0xCCFE13A49028F54CULL, 0x73DE50CD121182DEULL, 
            0xA7B10C5F857ADF7DULL, 0xBD0A11E87B686CAFULL, 0x9E24FA8A7B6BFF41ULL, 0x00DB7E50F034773FULL, 
            0xE1FBF13AC22D5BBBULL, 0x3F401DA0FAC9DBAEULL, 0xF15E1D6C6CA330BFULL, 0x13C6FCE96C517F04ULL
        },
        {
            0xE4FD194A0B831129ULL, 0xDFAAD8CF89C0C9DAULL, 0xE22C4B7C5650100DULL, 0x2CF2C8251AA17BC0ULL, 
            0x12D0FBD5EA9EE5F0ULL, 0x84A68E23A71D9EC5ULL, 0x2066F268BA4CFA92ULL, 0xC27524DC71FDF93DULL, 
            0x0C4FD533001CB917ULL, 0x2804046B37E6CA14ULL, 0xC1A78D3496799C1BULL, 0x9179DF4EFFB2B549ULL, 
            0x1C1C247C66124EFCULL, 0x726AFD3C56AC4BE8ULL, 0xC190302B2A7DD09CULL, 0x7273EDE7372CA84CULL, 
            0x7C5D21CD240C5CDAULL, 0x95D0CF86209A0D77ULL, 0x0208E37F6B3AF092ULL, 0xBBD348828D3C79BBULL, 
            0x18F39F7A1DFC74D1ULL, 0x158F0571E1030CECULL, 0xDF8468E539DD4AF0ULL, 0x7F32F63DE3BB0576ULL, 
            0xE6271895E95BEF68ULL, 0x2575A8EC547C75EDULL, 0xCBB82BD0E409B1F4ULL, 0x46AB004AA0EF2A0AULL, 
            0x5832012F9F2A7E70ULL, 0x22D45CE13E82FDEEULL, 0x82F0D67C6ADC01D7ULL, 0x66FDE7CAB1E9F0DDULL
        },
        {
            0x95937B2F8E57B268ULL, 0x57BD1A712939B8A2ULL, 0x0AEA03431218EA1DULL, 0xB2A185DC67B9B7EEULL, 
            0x37F57399DCB995B1ULL, 0x3F16B1BC5187C2A3ULL, 0xFFFE3FFBD3D5C6E8ULL, 0xAA37E13117854936ULL, 
            0x0AF3B1DC7164AB8AULL, 0x70B2A5BB50F1817DULL, 0xFC0FF51AB0FACF6EULL, 0x4C6CDAA1F10E6FD5ULL, 
            0xBEF973CA944E2AA9ULL, 0x5B6E6DBC896238CDULL, 0x14C722ACD5D911EBULL, 0x11E8B730CBC8C1A4ULL, 
            0x6D44D41BB32B492DULL, 0x0FBE0F123CC0D955ULL, 0xF6EAEE6BE5E01061ULL, 0xE509E6C0C0AEB997ULL, 
            0xD64DAFDA42F3714DULL, 0x20D06DBF1B3D0F05ULL, 0xB2B21E33A57F32DFULL, 0x82AE1C367EA0DF80ULL, 
            0xEE6080EEA0816E00ULL, 0x7EFD55FEA4E4FED3ULL, 0xAD0FDF05CC58672CULL, 0x2EACAACC524747DDULL, 
            0xEF7AF619AC430B64ULL, 0xAAE3440FA385C903ULL, 0x7481142E6E899D52ULL, 0x1465B18BA265E399ULL
        },
        {
            0xEC81FB0759E4F193ULL, 0x9F42F4679AB6B8BDULL, 0x3E3877569B075EE7ULL, 0x79B45114E5AB42F0ULL, 
            0x1FC7E4CF12E8207BULL, 0x1173FB7C825BCC07ULL, 0x374C4DCEC5337313ULL, 0xB5423440CDADE346ULL, 
            0xF5ED339900118191ULL, 0xF93876239720EB7DULL, 0x2311FB3325A8DEFAULL, 0x7F12CEBE9692C220ULL, 
            0x17129AD0D872CD37ULL, 0xAF780B2CD041868CULL, 0x0A7EDE2AA2867430ULL, 0x934F0758C5DE4242ULL, 
            0x56A84D832E2DE97DULL, 0x233E714511280202ULL, 0xC63BE3D17AF55FACULL, 0x23C18B30251BD9B9ULL, 
            0x416FEF723DDD661CULL, 0xAFF357BFF5DE6AC3ULL, 0x22C7F80F682DCB89ULL, 0x9857386060760D96ULL, 
            0xB8484A85A2ECB8DAULL, 0x50580C4E4C4921B9ULL, 0xF8F44C636A99D0CAULL, 0xE368264F4B4DB0F1ULL, 
            0xE86A46A26A2B2897ULL, 0xD8F9FD751DA66231ULL, 0x1A6B8C0163ABFEBCULL, 0x44263E420CF78B93ULL
        },
        {
            0xDC8F17ED59F1CD7AULL, 0xB7E12B74B160A8FDULL, 0x8B3AE69B9C1964FAULL, 0x02D42C133A1F8A55ULL, 
            0x07E81D5BE43C3F48ULL, 0xB90E747C042646E2ULL, 0x83DB9FD15013C5DBULL, 0x2EDDBCA6A33BA00DULL, 
            0x64E2355ED604D605ULL, 0xB6A7B1E7A3493433ULL, 0xAEC66A50395BC52DULL, 0xA133DEE310FF3DB3ULL, 
            0x7D1D3550FA54D7B4ULL, 0x88BDE6A7B1D8ED26ULL, 0xA09E50B70BDBBCCFULL, 0x860C40EF0B8BF687ULL, 
            0x7634E4E722DBF75EULL, 0x1C5FCA1D434586C2ULL, 0xE8F34DE12EB1C653ULL, 0x78709A339AE97D9EULL, 
            0xE4930B859E09B5D0ULL, 0x69351420B5B19BDCULL, 0xC815C22EAADC9C4FULL, 0x6FC5528C18233922ULL, 
            0x63AF50594BE27173ULL, 0xE9BDC9404F552C36ULL, 0x5BAB7839331CF290ULL, 0xC762CF24B76C83D7ULL, 
            0x4E3415777968639CULL, 0xFD1C6762BBF517BBULL, 0xE7E03D2332F34AFFULL, 0x9A5FCB40DD6A8EDFULL
        },
        {
            0xAA838C92635BAD14ULL, 0x55C199690CE4B656ULL, 0x14E4BC2A7C06D3B9ULL, 0xEC7025073907179FULL, 
            0xBBD27D7E231CC58BULL, 0xD97281553D5FCB5CULL, 0xA7D3EC69B48CEC12ULL, 0x5760274C45073B50ULL, 
            0x479ABDBDF6BD9103ULL, 0x6590D5C6BBE42D8BULL, 0xAD1349B2D9DA1CB9ULL, 0x61E6976709E8FB00ULL, 
            0xBA497A551AF56954ULL, 0x238FF15C0B91DF50ULL, 0xDECDFA16C4ADD339ULL, 0x00E4A30BEAB60EAAULL, 
            0xE6DD21B3AC0103F6ULL, 0x9365C325FDEE2873ULL, 0x97F309D4AD172702ULL, 0xAB316E74B4B3868BULL, 
            0xAB5BC8548CF9DE0CULL, 0x65A13AA1817A04C7ULL, 0xD206E2D6CA4F0F10ULL, 0x6D414E0CFC6C798EULL, 
            0x2C9B4F2A53EAFB38ULL, 0x426CB80C74C26361ULL, 0x934B7A7E64221F92ULL, 0x67A44DB38DFAD3B5ULL, 
            0x645ADA3BB89275BDULL, 0x9C592F515E95BB8CULL, 0x05AAB435E6F9BFC1ULL, 0x35346795B9B969ADULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseGConstants = {
    0x61A1ADB860671144ULL,
    0x6B8C09005027913DULL,
    0x3FA3E238244BF20BULL,
    0x61A1ADB860671144ULL,
    0x6B8C09005027913DULL,
    0x3FA3E238244BF20BULL,
    0x0EE14956F059AAAEULL,
    0x49531AB58D11116BULL,
    0x23,
    0x58,
    0x3C,
    0xAB,
    0x09,
    0x7A,
    0xCF,
    0x9E
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseHSalts = {
    {
        {
            0x99E545A09253F9FFULL, 0x5F7A7D8B01AEDCEFULL, 0xE1A0AB87758F5E91ULL, 0xD64A4660D6B2D35EULL, 
            0xB213CE06FFC80333ULL, 0xC8381EA09D2C07FEULL, 0xDA6778864D7F31E8ULL, 0x2064F833F8DDEFE1ULL, 
            0xAD9F1B33D50B5113ULL, 0x08A36F0DFDB7C8B6ULL, 0x0CED6E77F3B57296ULL, 0xB5721D320D7D4694ULL, 
            0x59C94F6FA4B80A8FULL, 0xBB22B9D4E96199E4ULL, 0x4C59ACA6DD5C10F5ULL, 0x26F8BD466C7D5279ULL, 
            0x35BDE2B421576F26ULL, 0x85F57F4428396343ULL, 0xB38EBB73CEF1E6C4ULL, 0xE2C46CCA93984EEAULL, 
            0xA79D598E29165C14ULL, 0x751AF3792DAE1D65ULL, 0x9F412C797E57C41CULL, 0x225B4823E7598376ULL, 
            0x15CF8F541638C8CDULL, 0x240FD8B911237A2FULL, 0x7ED79070B04EE75CULL, 0xDCAABC4980700CA0ULL, 
            0x07FB49D62891FB7BULL, 0x871D542F678D231CULL, 0xBAC9A7B92A0684A3ULL, 0x49B2D9EEC7627589ULL
        },
        {
            0x6D0B9D27F8E14AC5ULL, 0x6C67692E08478C5BULL, 0xB44861850CECF575ULL, 0x5792F1528B4A82BAULL, 
            0x16072A76F66F1560ULL, 0x2D3C3ADDD9B787BCULL, 0xF42E4313B5DC1AFDULL, 0x89D2BA296BCC9F6CULL, 
            0xEE76CF78B58A7576ULL, 0x6580CC326A0B70B9ULL, 0xB488ECDE6D142CE5ULL, 0x38B9FAFADF3C295AULL, 
            0x8CB25C1422E79363ULL, 0x4100F9F4EB86C461ULL, 0xC9ED693745D0E85AULL, 0xAD53CA4A0AD8F5DDULL, 
            0xAD8B0D6627A414CFULL, 0x524B1435F5E929B7ULL, 0x9969F9BE56887A63ULL, 0x5E9751BA42ACBFD1ULL, 
            0x16E4A76B90B0ECD6ULL, 0xD435679D3725332EULL, 0x149E23C5BF3D744AULL, 0x536CD852A62776D7ULL, 
            0x31763840BB2EABA7ULL, 0x83DF4B0A37E00377ULL, 0xCED0635821CFA306ULL, 0xF3FDF698FC9A8A26ULL, 
            0xEC37FBC03C268903ULL, 0xDE42114024175DB5ULL, 0x98094D78D57620B9ULL, 0xF9540E4D3E74C938ULL
        },
        {
            0x363263C67BA913D9ULL, 0x8CD15A1D3EC3EE73ULL, 0xE06276FE1350A197ULL, 0x27D85B8373FA87C6ULL, 
            0x8D134AA88E257197ULL, 0xD8E82F74C1E87D03ULL, 0x3DE227FA77028E68ULL, 0x62FE0E3D6E6530BCULL, 
            0xC13BECB1A19AD681ULL, 0x7B341ED63714EC96ULL, 0x311DD42F674EF692ULL, 0x763FFE66B1E2A0C5ULL, 
            0xE372019E772E534AULL, 0xA8CDD96AE6377C04ULL, 0x9475720A187AB442ULL, 0x79F1164FC86BFFB6ULL, 
            0xBF09E2CBFF62C58EULL, 0x03EA072CBE8DF385ULL, 0xB73E8B6948B9A83DULL, 0x76009CFCBA6A874AULL, 
            0xBD4279CC58664FD0ULL, 0x01B8CEE240360D83ULL, 0x31FD70CAC69487BAULL, 0xA4D17E571B88BB72ULL, 
            0xC2DBC37CD89536B1ULL, 0xDE5750B57D4147FCULL, 0x96FD45884EE0B17BULL, 0x82653961A846751FULL, 
            0x5DB9AB1F1B471ACEULL, 0x78CCBB09D2ABCE57ULL, 0x8C8519930EAE64BBULL, 0xFA1554C34251BC5CULL
        },
        {
            0xA7430E780C051D63ULL, 0xADC118733DAB48DDULL, 0xA54A2FE6070FE5D2ULL, 0xE38B5BFFD322D392ULL, 
            0xFC36C964A4D66958ULL, 0xEBFF3524FD4AFB6FULL, 0x2F994814B6BBB195ULL, 0x0D108FBF8E659CB7ULL, 
            0x13937508D2A10BB7ULL, 0xCC6C49B1D156A06FULL, 0x01C28C0A66EA60E8ULL, 0xDE9C12C7FB4DAD1EULL, 
            0x5EEBDBE4B38A55E0ULL, 0xFC5E20B3AC47CC80ULL, 0xF7036EE12D0F6FB5ULL, 0x6437D37C1D289F2EULL, 
            0x4ADED6D2760F3E85ULL, 0x1701748267736E93ULL, 0x3B7C44A5F6C8128FULL, 0xC1CD486631916F46ULL, 
            0x2E5ED21AF1C50C1AULL, 0x7AE6E02DAFA6E38CULL, 0xD9E2CB12731CD912ULL, 0x6879F6416BB268B1ULL, 
            0x573D3244857CFB89ULL, 0x3CE73B179A8D6254ULL, 0x5166FCD7D54CC882ULL, 0x5108CAD8704F9098ULL, 
            0x416265DBDA74EDA9ULL, 0xCF1ACFF0F4E673A4ULL, 0xB13810F7D187B9E3ULL, 0x4B1AC321CFCBA404ULL
        },
        {
            0xD8CF94B71F100103ULL, 0xDA9CB26E4B0C5CC0ULL, 0x7E35546A9999CC1AULL, 0xDE15179433F7E354ULL, 
            0x78B7F19A75B04B91ULL, 0x674909CB8BDB5262ULL, 0x551841368ED5A0ACULL, 0xCB98D4F0EBBE2D20ULL, 
            0x8ECA9F5906AD2720ULL, 0x915D96A3FA0B806DULL, 0x6ABF37ACC10739E5ULL, 0xCC169B702F07EB70ULL, 
            0x6853902D7C122577ULL, 0x5A868D0C1BECBE3BULL, 0x0A1B4D7276FFE756ULL, 0xD3C7CA5C580CFE45ULL, 
            0x987E83A7153C89A4ULL, 0x10C48257388BA531ULL, 0xBD7D8D9881EFEF0FULL, 0x1D3AB27DFCB617EEULL, 
            0x65951058C0B92A6DULL, 0x6A00E4E1E8623AE5ULL, 0xCCA66D879FB759F4ULL, 0xC12A5B8D0B7AA849ULL, 
            0x539278CD8FE1CEC8ULL, 0xB70A9E59D99C92FAULL, 0x6DD7D99DA61606AAULL, 0x8324796DDFE37481ULL, 
            0xECB7659157BEE49CULL, 0x524E59D62F480528ULL, 0xCE806732120F91A7ULL, 0x07A1A31B3BF41401ULL
        },
        {
            0xCBCC56502FC077F8ULL, 0x69A0D1EEF81F1FD3ULL, 0xF072F6B6BC1C9286ULL, 0xC31E2F93CA9FF842ULL, 
            0x963E03D5EB2F678DULL, 0xA50ED0CFF7753D4AULL, 0xF234805CB8C6D58BULL, 0x071680FBBFB47EA2ULL, 
            0xD8EC695C48821862ULL, 0x60271C13E529704AULL, 0x3205240E4D3B81E0ULL, 0x010F2865A60FE78AULL, 
            0x7627AF4286018348ULL, 0x6E7A9B8C75FD4C7AULL, 0xD7DE2488A37D6EB0ULL, 0x05EECB9CB64FC909ULL, 
            0x45E7286B6861DCDDULL, 0x830555FBFA1A8314ULL, 0xCB897B86F2CB9ED4ULL, 0x9B088A29D4C11A96ULL, 
            0xCF8F3554977A66E5ULL, 0x83CEF6F850E75FA6ULL, 0xF9D883EE74C44831ULL, 0xF978470F296EF652ULL, 
            0x8639805B4C1EC360ULL, 0x0277FDFB8CF45924ULL, 0xEEDAABDB1B985CEAULL, 0xA22A6A748478B4DDULL, 
            0x605C6463C1DE92F7ULL, 0x466153840A74D67FULL, 0x97CC10B4C7FA3D9CULL, 0x4906BCEC32725E67ULL
        }
    },
    {
        {
            0xA773FCBE72F04FDFULL, 0x22AB7D15CEC542E9ULL, 0x2B79706F274FBDE1ULL, 0x7DD859B8F0D4B085ULL, 
            0x2E6216074D1B8964ULL, 0xA920B07AD58797BFULL, 0x6B165D213FFD04FDULL, 0x50E32959865174B2ULL, 
            0x580A64A89C7D1BDFULL, 0x271554D0085FDCA5ULL, 0xF4FA840640712A83ULL, 0x1E48DF13164C07E8ULL, 
            0x771C1D7DD67BDCF3ULL, 0xA01B3CA688902EE3ULL, 0x2DB803D2F371142EULL, 0x2AF6B2ECD1AFC1DBULL, 
            0x5FF4FF2F36C8B40CULL, 0x438EFA6DFB9210E1ULL, 0x355B94376B25A747ULL, 0x0DECCF7EF3766793ULL, 
            0x00020971B586DDD3ULL, 0x8D07F4C3E05AB4D4ULL, 0x2A9E6824AC18A495ULL, 0x5F59518D0F545D73ULL, 
            0x0DB3AE4561F76263ULL, 0x93FBC34F7E29D478ULL, 0x4A37BA2EE2F97CBEULL, 0x64789BCC995FE73AULL, 
            0xEED95C88E87BA766ULL, 0x1B87FDCA13F72CB1ULL, 0x1795DA27FA559FCAULL, 0xE1A5BC68477A22C2ULL
        },
        {
            0xAE51313101F0CBE7ULL, 0x3714162B230749D2ULL, 0x998DEC2EB46485FBULL, 0x8D96EE54DB7E744FULL, 
            0xF4BA1F439545DC36ULL, 0x50DC3A3ADEAA6C04ULL, 0x1DB9A55271EEC312ULL, 0x530FA554FE68C6B5ULL, 
            0xC18BD45FAA50F847ULL, 0xAE05653C82400DFAULL, 0xADDB41F198FD10B1ULL, 0x359917AEF5A34541ULL, 
            0xE7FEA8975571E36DULL, 0x4CF54FEA14149A80ULL, 0x8BB9CE391F6EDF3DULL, 0x5607AF38DDA84611ULL, 
            0x844369921B11CAF7ULL, 0x2386ED30AA39E654ULL, 0x2EE95936B9BD9614ULL, 0x73137A5B0902DB18ULL, 
            0x2D18A249D5E31A4DULL, 0x8F5B6C500B9B7945ULL, 0x5B74DE2A382D643FULL, 0x809C84B4DF85A9B0ULL, 
            0xE5B2D56AF5BC1E65ULL, 0x3B42A9BE42C87105ULL, 0x886B8CD6549461DAULL, 0x23BCFD8F59DEFBAEULL, 
            0xD474B3AC4C1E1348ULL, 0xD3690A509182DD36ULL, 0x9CCF23A28B17C126ULL, 0x8EA8E814D50C5084ULL
        },
        {
            0x65CF735A91BF1F4CULL, 0xE5B2752A9EB82B08ULL, 0x3D4A2642D050A454ULL, 0xBC36D7E79E4BF6EEULL, 
            0x5C46507DAF1F5AD0ULL, 0x4B98482188A6ACBFULL, 0xAB25846680F537CBULL, 0x7343F6BA9377BB21ULL, 
            0x0409FE4EA2A4DC54ULL, 0xA532FBCE3D2CF418ULL, 0x53FE836564289B72ULL, 0xE1281F6F691CBE70ULL, 
            0xC376F3BBEC5A4E50ULL, 0xC1DC454F752BB772ULL, 0x359DEAE6BE89DBEEULL, 0x49EBA52692181B31ULL, 
            0x7C08828ECC8A545BULL, 0x1BE8F7E6B7F2174BULL, 0xF91E6D89A4C96789ULL, 0x8ECED1B9CD3295F6ULL, 
            0x1AD6273122E3E615ULL, 0x5D958C0F3A1F6338ULL, 0x36175F78F38A5512ULL, 0x23E3527029400F1AULL, 
            0xC8698DE7E989B498ULL, 0x14E6B41958C49DBFULL, 0x32B9A6BCD894096DULL, 0x3C826485B33AF0A4ULL, 
            0x7341960CF32A9ED7ULL, 0x6BB1DDA30122B29DULL, 0xC2B7EAF18342FE03ULL, 0x291621092559B182ULL
        },
        {
            0x2742920F274AF596ULL, 0x8E74920948075BF8ULL, 0x292A9A04D7AFB79AULL, 0xB67AF02EF58F1F26ULL, 
            0x50E6FFD6334038CCULL, 0xB71C6259DADD6C82ULL, 0x6D9E1F8861F3AEA1ULL, 0x2E39931527832D0FULL, 
            0x09A29180BD272258ULL, 0x926400DF5AAE0217ULL, 0x7249916D2F58D329ULL, 0xADE088B0B5303969ULL, 
            0xC1C51B803BED87FAULL, 0x75402634D1607164ULL, 0xCFF28EFBD6516E2BULL, 0x63FF9AF296ECED77ULL, 
            0x50E03B65905170ECULL, 0xF9FBD9448AAF42D1ULL, 0x8C43E7332D515B38ULL, 0x25B6CC884D67CA49ULL, 
            0x5D4E4003C543557DULL, 0x615B3155DB96D44AULL, 0xDA880B562AC06912ULL, 0x672EC1AC231012C1ULL, 
            0x9AD8D67B03885231ULL, 0x670A9F50FA8E98A3ULL, 0xDFB507A011488842ULL, 0x6C22B16272EEF16BULL, 
            0xBA9CA6F3FA82DEA6ULL, 0xEF7634C8D78C4C9CULL, 0x61FE9888743C2643ULL, 0xE69638EE727F1542ULL
        },
        {
            0xF62511613F303D56ULL, 0xB06A5804D41D245EULL, 0xD9B188C328ED9A88ULL, 0x46CA3E7DF94EC871ULL, 
            0xC28DF25AB8695C30ULL, 0x6BE8942CDBD028C2ULL, 0x9BE4ADB9D3CFF57CULL, 0xC075B83C2EB37C7DULL, 
            0xEDB12D74CE99B8EBULL, 0x15D47CB3D9A0D063ULL, 0x8EEDEB5E0B299224ULL, 0x7037AB8DA7E30944ULL, 
            0xC98E9171765B6DBFULL, 0x9E39DFB853B6018FULL, 0xD76E9C2C2760A4BEULL, 0x9DB49E0D4FEF6799ULL, 
            0x93BC1610A3FBB627ULL, 0x0B75BBD674C169FEULL, 0xF47A13D2DFCE6A47ULL, 0x82B31DBA6F04750CULL, 
            0xB3B70C20A6D06D73ULL, 0xF70E7DBDCE7DD244ULL, 0xC45D3F9330643544ULL, 0x95195FAA10723340ULL, 
            0xBDB842EB66A96AF3ULL, 0x26D7776B6127F019ULL, 0x545529387645B9ADULL, 0x9B23EA2D75519DFBULL, 
            0xF49E9D026CD46EF6ULL, 0x2C7C2B2C7F70CE39ULL, 0x8141312E8720E42CULL, 0x16EEC6A1486DF803ULL
        },
        {
            0x0A25E85B6550A01DULL, 0x8BE2B91CC7AA9D6AULL, 0xAC0ADE546510D14EULL, 0xC8909064EDFBC55CULL, 
            0x0FFF28AC50043D4CULL, 0xC96274D027578EECULL, 0xAADE042C90E7230DULL, 0x27E9085CE2A80085ULL, 
            0xBA82B8D990DD9ACBULL, 0x652020A70F1326B7ULL, 0xDB446FC0D2313CB8ULL, 0x105666B35A9FE2DCULL, 
            0x34F0351A57E53C0DULL, 0xAB14308BB11206F9ULL, 0x8FB33D313EDB00DDULL, 0xDF663C415150A2A9ULL, 
            0xD767E14941B4B45BULL, 0x74431B32DF33B23CULL, 0xFEFE6F789499F99FULL, 0x6353EFABE6B25A0DULL, 
            0x5E3BB7D560C6EA0BULL, 0x498E3B00070E3410ULL, 0x9AB334859CAD14D6ULL, 0x84C8F4F19D033155ULL, 
            0xBCC192D7DDEF52D6ULL, 0xEDED8FC3CE2E6189ULL, 0x787C457C67776F5BULL, 0xAD681742F0CAB466ULL, 
            0xCE38DEE517B64C88ULL, 0x8FC7B1C81F858630ULL, 0x2721A182A9E8E41EULL, 0x7079981D383F1B75ULL
        }
    },
    {
        {
            0xE96A7DF0270C3147ULL, 0x682336F26CCC47FAULL, 0x8B4AA0B65CB8AA42ULL, 0x8048892000C22700ULL, 
            0x0CB2606C4190DD3AULL, 0xDA2C899EAD01D882ULL, 0x7E8128365A8BDFDCULL, 0x5439987AD8DFCE2FULL, 
            0xE175BA82AD14EE85ULL, 0xD5EFB557ED63B7DEULL, 0x67888479EF343B36ULL, 0x90C9EE09C8646450ULL, 
            0xAC2BF59D0F9DCDADULL, 0xAED53E0166D22277ULL, 0x7D5CEAE781EDE7B8ULL, 0xF420FD272036101CULL, 
            0xF0D26C77ABD5B159ULL, 0xD7B6F37C052A2FF2ULL, 0x59884CED126EAE5FULL, 0xCEB614735A899FF1ULL, 
            0x5CA3AFF1B784CD3EULL, 0x6EA98104E1D194E3ULL, 0xDE017EF0900B7CD6ULL, 0x0D100923A3C0F58DULL, 
            0x037A7E6768E1CEFFULL, 0x134B91AA42E30E07ULL, 0xBFE36ED1CEF75C86ULL, 0xFB4FF5A5F487753DULL, 
            0xE022D1CA2D210884ULL, 0xEF91969DA1763D17ULL, 0x7EA739287B193FB3ULL, 0xC64CF45A7FE27D45ULL
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
            0x3704EB806A389E2AULL, 0x0A570B260F3C6837ULL, 0x9A236ADEE153914AULL, 0x3B083B521EA9DDA8ULL, 
            0x37E642EE99D88CABULL, 0xEC622B3DBC1585C6ULL, 0x20E4C97841859640ULL, 0x07EE6C528C36AFD7ULL, 
            0x5E783CB6C7273128ULL, 0xEE47E3902B73AA62ULL, 0xE821FC7C5F7171A2ULL, 0x1F6EBE7B97C01C86ULL, 
            0xB299D3E93BCACAC7ULL, 0x4C10F6B1840D5FF3ULL, 0x9D22C02D6A69DF8EULL, 0x5DACB19DE6C69904ULL, 
            0xF5DBBDCF2A72EBE3ULL, 0x524B9146B21C8473ULL, 0xD8638FCD6F655D26ULL, 0x7DEE2021A3DEE639ULL, 
            0xBD9F4E771029EE87ULL, 0xBF2F4D50F6A41E9CULL, 0x9DF8EDAD54159ECDULL, 0x99074F19F82A4043ULL, 
            0x741C93C2183D62F7ULL, 0xA190476291352A93ULL, 0xD8BCC67D3CFA271DULL, 0x0C8B3F6B4258C257ULL, 
            0x8927D97EA556FF08ULL, 0x9328F5D7400CAF44ULL, 0xB39208DE9A712CB4ULL, 0x5899114D6E18E1DDULL
        },
        {
            0xB1AECC5DCA183D94ULL, 0xB3235111E26088ECULL, 0x4D40917C2A0CC788ULL, 0x4063746D6C20C92BULL, 
            0x2359D6EA18A701E1ULL, 0x11E876F726C2AD4CULL, 0xC971B54297DA4E1FULL, 0x4465CC0E54FE837DULL, 
            0x9B595A7ADB250C94ULL, 0x85B8BBDACC93ECCDULL, 0xF231511909E6ABBBULL, 0x2276892A197AB866ULL, 
            0xA74023246D471279ULL, 0x542A12C97FE7FB33ULL, 0x782351DAF25BE07CULL, 0x08594D9E4907F62BULL, 
            0x194D3AB0217322F9ULL, 0x3D064B736A11C6C2ULL, 0xA8556193BEDC21A3ULL, 0x21DA266ED0AAC9EFULL, 
            0x01AF1DC3E4A239CBULL, 0x912FDE9C6F28FC5EULL, 0xC6FA0159E54E540AULL, 0xBFC4FAA5A6983567ULL, 
            0xA8E78C6E70335460ULL, 0x9DC7C7C9EF75BD50ULL, 0xEE31B07A3F82A06EULL, 0x3C60E9B272CED711ULL, 
            0xE81705B950D39F01ULL, 0x49623DC09F222537ULL, 0x8606DC091ED9A4AEULL, 0x48A6F4433FA4319CULL
        },
        {
            0xF5F63F66977B313CULL, 0x4CF3EA18E39F79F5ULL, 0x06A892D44DEC0F77ULL, 0x54FC8C4C1E892E90ULL, 
            0x7F9D55DAEC7C9FE8ULL, 0xB355D8EE8CF37DDEULL, 0xEEAD791F808B49CEULL, 0xBAC7BC4C6D0423FDULL, 
            0xB2D7E9775EFC4710ULL, 0xEB2E8602137E1213ULL, 0xE046C0529AF1FC0BULL, 0x74BA925FEB8F55BBULL, 
            0xCDBD03F25D707671ULL, 0x9AC436810E1248D2ULL, 0x2F1FE110683CF13CULL, 0x3F34B6893EB1542CULL, 
            0xB31BB733F6F53075ULL, 0x0FA9DBC5D3A3793BULL, 0x467FF1C03D9071C9ULL, 0x13456E48FC6C1D28ULL, 
            0xBF36A9D583E4FCFAULL, 0x11010CDCF74F57ADULL, 0xE6229B4BC2392CD1ULL, 0x9ECE7193F0606713ULL, 
            0x0866236AD4ADF8F9ULL, 0x7455941F56169068ULL, 0x59C69E45CA2870AFULL, 0xD80B081EC69DB74AULL, 
            0xA339EFB48C675039ULL, 0xD8BE1CAC20929BF4ULL, 0xCF6A18FB760E6702ULL, 0x0E12F3344F03F5B4ULL
        },
        {
            0x710C2C3764B64BB9ULL, 0xD13EA24AF556460DULL, 0x394F9195247949D6ULL, 0x76803CE0F5F519D9ULL, 
            0xD36D89580491F2FFULL, 0x7A105374BD8A67A1ULL, 0x76970F2DFF6D62C3ULL, 0x333BE0C4B4D6CEFCULL, 
            0xF6D49563575F3B3CULL, 0x8116286B3ACF31EDULL, 0x38AAA284C68870A6ULL, 0x5E0F0903B27BF360ULL, 
            0x245CEA41781668A9ULL, 0xAB1894884C5A4C5AULL, 0xE499723CD0B6D162ULL, 0xB85AF50E914E80BAULL, 
            0xEC266D8C85603DC5ULL, 0xEC8E803E15E506D5ULL, 0x706E6A5C8AE0E47AULL, 0x2BA83BB41F13BE0BULL, 
            0x2F9F43CFF7C327EEULL, 0x06CFE0C53FCBE7C8ULL, 0x969B32DE278AD3A4ULL, 0x6EDC7A4C2412FA7BULL, 
            0x2232ACD26FA8C2DDULL, 0x99CF29B9C6489CACULL, 0x2F29C7001484658BULL, 0x55BFF315E5F4584FULL, 
            0x0043156D152931BEULL, 0x3FDF4B6AE279099CULL, 0x191AB511E76DE6C4ULL, 0x76DE0FC62FFF7283ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseHConstants = {
    0xB9645D06760DD4B8ULL,
    0x5F05ADEFA6895B2AULL,
    0xFC0BA27778668DD6ULL,
    0xB9645D06760DD4B8ULL,
    0x5F05ADEFA6895B2AULL,
    0xFC0BA27778668DD6ULL,
    0x3979E4CE97D32CDEULL,
    0x5BD490B22F208DB5ULL,
    0xE3,
    0x45,
    0xDD,
    0xFB,
    0x88,
    0xAE,
    0xED,
    0xE3
};

