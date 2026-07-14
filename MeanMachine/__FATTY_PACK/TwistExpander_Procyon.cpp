#include "TwistExpander_Procyon.hpp"
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

TwistExpander_Procyon::TwistExpander_Procyon()
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

void TwistExpander_Procyon::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE84EBB056CF0F9B2ULL; std::uint64_t aIngress = 0xF1C140C090C59F9AULL; std::uint64_t aCarry = 0xC685FACB88461046ULL;

    std::uint64_t aWandererA = 0xFAF926C6129DE7D3ULL; std::uint64_t aWandererB = 0xBB989F5DF0123F71ULL; std::uint64_t aWandererC = 0x886BDB17F503311DULL; std::uint64_t aWandererD = 0xA6A116D32E35446CULL;
    std::uint64_t aWandererE = 0xCDE95BDB59DFD904ULL; std::uint64_t aWandererF = 0x996ADF7751E6EFD5ULL; std::uint64_t aWandererG = 0x86AE3581B145CDD6ULL; std::uint64_t aWandererH = 0xAC8B333BED0B4277ULL;
    std::uint64_t aWandererI = 0xF87E095F8DE16703ULL; std::uint64_t aWandererJ = 0xFDF4532A39721AA8ULL; std::uint64_t aWandererK = 0x8698BDF222862F10ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17669068845663252536U;
        aCarry = 16224319461364453453U;
        aWandererA = 13941482478828811223U;
        aWandererB = 14408256937431188137U;
        aWandererC = 10709991626240979460U;
        aWandererD = 17515385902134214342U;
        aWandererE = 17684272753823313854U;
        aWandererF = 15970625744887428840U;
        aWandererG = 15605578617248567973U;
        aWandererH = 11337120072210644234U;
        aWandererI = 17044479588591738539U;
        aWandererJ = 17834823428144049647U;
        aWandererK = 12576183840890208608U;
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
    TwistExpander_Procyon_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Procyon::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD3B439C2B5C8AC15ULL; std::uint64_t aIngress = 0xA649137FD5E725A0ULL; std::uint64_t aCarry = 0xD6B29B822A0DE673ULL;

    std::uint64_t aWandererA = 0x8B1800587B7940DAULL; std::uint64_t aWandererB = 0xF9F2118EC45E48B1ULL; std::uint64_t aWandererC = 0xF19A9E9E63886742ULL; std::uint64_t aWandererD = 0xD4D618153C49E276ULL;
    std::uint64_t aWandererE = 0xDF3343C131039D59ULL; std::uint64_t aWandererF = 0xEEBB9767943DA1F7ULL; std::uint64_t aWandererG = 0xD77FBD5D7A7DAF03ULL; std::uint64_t aWandererH = 0xEB9E7CCAC6DE051AULL;
    std::uint64_t aWandererI = 0xADD2390FB452ADB8ULL; std::uint64_t aWandererJ = 0xF0552495C59A095FULL; std::uint64_t aWandererK = 0xA687E243CAE3C122ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18237615271265935604U;
        aCarry = 9741366406460956974U;
        aWandererA = 12411338409078134886U;
        aWandererB = 11771634131695942923U;
        aWandererC = 15320021614512509458U;
        aWandererD = 10098811201605306011U;
        aWandererE = 17932246519326926524U;
        aWandererF = 12365122961372742770U;
        aWandererG = 12021133994326892202U;
        aWandererH = 10184398567147559624U;
        aWandererI = 15142178605762884628U;
        aWandererJ = 15771708862287509536U;
        aWandererK = 11291314055567167613U;
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
    TwistExpander_Procyon_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Procyon::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC8893DEC25F41DD9ULL;
    std::uint64_t aIngress = 0xD96B2156D7E9B277ULL;
    std::uint64_t aCarry = 0xDC37205F740E40DAULL;

    std::uint64_t aWandererA = 0x8C4ED14EE44E7654ULL;
    std::uint64_t aWandererB = 0xCD82444155F2C066ULL;
    std::uint64_t aWandererC = 0xEDBC81A9EAA925D6ULL;
    std::uint64_t aWandererD = 0xF6DD2E803BB60815ULL;
    std::uint64_t aWandererE = 0xFA46F798E4D101FBULL;
    std::uint64_t aWandererF = 0xFD8C12B9546A7645ULL;
    std::uint64_t aWandererG = 0xF37E0D13DF4CB44DULL;
    std::uint64_t aWandererH = 0xA83ACA3896F211B3ULL;
    std::uint64_t aWandererI = 0xC78157F0FE00FE39ULL;
    std::uint64_t aWandererJ = 0xF6D1A649754C80BEULL;
    std::uint64_t aWandererK = 0xB1E8E45C8C9B80FAULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    TwistExpander_Procyon_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Procyon_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Procyon_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 26 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 45307
void TwistExpander_Procyon::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1286U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2004U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1712U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 361U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1688U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1372U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1369U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1121U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1195U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1459U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 380U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1753U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1929U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 820U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1772U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1213U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 417U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1855U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1635U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 461U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1137U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1013U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1671U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 783U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 367U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1922U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1582U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1059U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1295U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 842U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 686U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 299U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 539U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 174U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1382U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 889U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 728U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1547U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 306U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 199U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 734U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 887U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1076U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2042U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1241U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 168U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 569U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1355U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 235U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1594U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1412U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 401U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 99U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1397U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 536U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 787U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 38U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 544U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1974U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1579U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1852U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1959U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1328U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1518U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 562U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 604U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1609U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1826U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 816U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 90U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1235U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 504U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 586U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1616U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1782U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1455U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 111U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1123U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 387U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1915U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1127U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1166U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 37U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1007U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1716U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 921U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 335U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1387U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1391U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 634U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 984U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2028U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 262U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 793U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 280U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 429U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 809U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 963U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1441U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1298U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 503U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1146U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1653U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 415U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 455U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1103U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1350U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 204U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 638U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 82U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1494U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 383U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 325U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 391U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 761U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 792U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 342U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 612U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 22U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 691U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 876U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1089U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Procyon::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xB037DF50CE15FEC7ULL; std::uint64_t aIngress = 0x8C2B5BD1FCCBEA7CULL; std::uint64_t aCarry = 0xB376F06A0BF3DD73ULL;

    std::uint64_t aWandererA = 0xD4C2D6E3FA43CB29ULL; std::uint64_t aWandererB = 0xF3253A4A99054817ULL; std::uint64_t aWandererC = 0x842495F12A50375DULL; std::uint64_t aWandererD = 0xFA5F72C5F638C51AULL;
    std::uint64_t aWandererE = 0x9AC73B68764C6E98ULL; std::uint64_t aWandererF = 0x9A5B844970E2D1DEULL; std::uint64_t aWandererG = 0xCB53FADBC272027CULL; std::uint64_t aWandererH = 0x9095DDF6EFCD23BAULL;
    std::uint64_t aWandererI = 0x887F43B2E6EFC718ULL; std::uint64_t aWandererJ = 0xD4FE2985A63DF33CULL; std::uint64_t aWandererK = 0xBD23ADE64BBD21A4ULL;

    // [seed]
        aPrevious = 12352815390996608490U;
        aCarry = 14098010236639413010U;
        aWandererA = 16211505524285589392U;
        aWandererB = 16259320284616546436U;
        aWandererC = 17232646435594011760U;
        aWandererD = 12132203620279758667U;
        aWandererE = 13034889864602698367U;
        aWandererF = 15722325565085435653U;
        aWandererG = 15107176152781347342U;
        aWandererH = 9970973624024078277U;
        aWandererI = 10851919300812184168U;
        aWandererJ = 9974085828223773204U;
        aWandererK = 12693185499492239285U;
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
    TwistExpander_Procyon_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Procyon_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Procyon_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 26 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13528; nearest pair: 467 / 674
void TwistExpander_Procyon::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7073U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 907U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1840U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2175U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 692U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1733U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1939U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5094U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 221U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6356U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7458U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6166U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7695U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2351U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 238U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2874U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 514U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1108U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1690U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 672U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 857U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 418U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 115U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1401U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1193U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1428U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 173U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2029U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 799U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1985U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 666U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 359U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 821U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 937U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1672U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1074U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 26 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13520; nearest pair: 476 / 674
void TwistExpander_Procyon::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4639U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2048U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7577U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8034U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2897U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 609U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 781U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6269U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1558U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5701U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2833U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6755U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8128U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5734U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5018U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 266U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 408U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 571U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1049U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 368U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1303U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2011U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 521U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1921U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1258U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 202U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 918U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 829U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 942U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2024U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1832U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 907U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1913U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 701U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseASalts = {
    {
        {
            0xF27CC064283B1CBAULL, 0xD58F38D6A89ED8DEULL, 0x16ED3F5A268C029EULL, 0x76A11C5D01B89401ULL, 
            0xFA7AC8F8B921EE24ULL, 0x1A6A47B4065DA6ECULL, 0x1EDCD75E45C1C4ECULL, 0x9A03EFCD7D172A6FULL, 
            0xCEF0A795B23CBF3FULL, 0x3C7666DE77366C1AULL, 0x1DFE662642DEF9CAULL, 0x1C863BA177251ED5ULL, 
            0x2BF7E2D9BE3D35D5ULL, 0x0EE7387A2349C5A9ULL, 0x7865F3042E2173FBULL, 0xF49C07B242203174ULL, 
            0x9FCDECBE75086FAFULL, 0x83CC864B149671FEULL, 0x0BA3D791EC32109EULL, 0x3B9BD55AB02D0F4CULL, 
            0xC079F276A9CCD108ULL, 0x36463EE85DC66AA9ULL, 0x6E9ED9490998F802ULL, 0x45AC56292AAC5C18ULL, 
            0xCD802FBAD5710846ULL, 0x9B5D99CC2EDC01FCULL, 0x67B94763AA8F09C2ULL, 0xDFDD515866B3EFB1ULL, 
            0x7360B5DC81D8EE4CULL, 0x28AF2AF8A79DC4D4ULL, 0x01AA5E9547AEC81FULL, 0xE717D24DF228E861ULL
        },
        {
            0xD86AD3813A6B3B0BULL, 0xCB3A9962D8123FE0ULL, 0x28BF6136630AE5A3ULL, 0xF9D3F4FD3B26E500ULL, 
            0x6ED7458C4211661CULL, 0x07E0B7DEB7F6E051ULL, 0x24195483256E41B3ULL, 0xDAA0D68B78E31C0AULL, 
            0xC1C4856537EECBFDULL, 0x76D9DF239C66ED75ULL, 0x2598150F2D9F5987ULL, 0xE96006B329A7BF22ULL, 
            0x7903FC6E08833040ULL, 0x4C46D149E7832388ULL, 0x2009A5D5A964B5E3ULL, 0xE197B516B7BF5303ULL, 
            0xA21ADFB452CA0F4EULL, 0x4C831DD3C157843CULL, 0xA324611F99FA30F1ULL, 0x8F23D754E03B383CULL, 
            0x5B1A87B080F2D848ULL, 0x8C0092176602D7DBULL, 0x259E29908D7F4904ULL, 0x3978029CEDFBA480ULL, 
            0x4126814FCF375035ULL, 0x08CFB52D4750CE7BULL, 0x7E147FE8556D7385ULL, 0x6519960AD0554A0BULL, 
            0x38D4EC82650DADB7ULL, 0x9CC1227F6F53C814ULL, 0x412BACE726191D9DULL, 0x805080DA72AE1D79ULL
        },
        {
            0xD554178104DB3609ULL, 0xB49E820A7CDD2F27ULL, 0x77C71953B3E730A3ULL, 0x7D069726243CE124ULL, 
            0x72DD67D93EC7C6DCULL, 0x598EB4129D2A1D78ULL, 0x5D64B0335501B2CDULL, 0x1772EAE89B3590C5ULL, 
            0xF342111BA24EF9BCULL, 0x86949CC20712DCE2ULL, 0x881010C25DBEF8A7ULL, 0xE2A65222FC061155ULL, 
            0x6ED48EAAEC551DBEULL, 0x50010E930EF72A21ULL, 0xF0D3EA64D2B84465ULL, 0x0B65B4D5CB7B8667ULL, 
            0x3DA10FC59CBD2581ULL, 0x34B8E192283CEA6EULL, 0xE71645D22605D37BULL, 0x0B453943527B426AULL, 
            0x33E07DB19C9B8165ULL, 0x62B564401A7BA3C6ULL, 0x4A589C68E10B86C4ULL, 0xD1185A6AB10D06A4ULL, 
            0xC3483A33657FDBD1ULL, 0x985E547FB8A46B0DULL, 0x0A36805A6BE3096EULL, 0x6B19CEFC571B6609ULL, 
            0xC249C59C8F9A55A1ULL, 0xD74532268E80D8D9ULL, 0x71F4121CFAAFE8B5ULL, 0xA66FC5D4F17CACB1ULL
        },
        {
            0xB495676C7D971DD9ULL, 0x86B40D50B6825E54ULL, 0xC8035803EA0CBB7FULL, 0x718C836CE962E546ULL, 
            0x515A45B9F82EB87CULL, 0x6A4CA40F0CD6FB37ULL, 0x0564AA27FCEB4DB7ULL, 0xB4489DADD922FC92ULL, 
            0x6BA7AE30DDB11DF0ULL, 0xBE3633B3A183DFAAULL, 0xB36978BF77E3DF3AULL, 0x35AD70E5C35C04A1ULL, 
            0xA106D67735DA786AULL, 0xA85947C75C40D74DULL, 0x62A5255AB4C07404ULL, 0x95203EA2A2040B4BULL, 
            0x29FFD93C31A249F7ULL, 0x749CA13CB5CDD8E4ULL, 0xF03F6E66321D9126ULL, 0x9575B14FEFF28ED6ULL, 
            0x616A1FC556328FC5ULL, 0x43175AE85F576EC3ULL, 0x53192BBBC10D376FULL, 0x081205C6DED16D8AULL, 
            0xFFC10A974633C041ULL, 0xE5ADCABF14FA7704ULL, 0x49D50E1AD5C692C9ULL, 0x0616F0518BA17497ULL, 
            0x15B4333A3C5F44EDULL, 0x11A7971B35DE043FULL, 0xA3AB997025FA222FULL, 0x4A4D20CF1C49D265ULL
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
        },
        {
            0x86B1DFC2EBFE5FB9ULL, 0xF5788E0F726F48AEULL, 0x477685AF86B8916CULL, 0x1F796FB4AE272B2AULL, 
            0xAB1B06E161461EF7ULL, 0x7B9D74C0F5778FCFULL, 0x1D211BA21C840E7EULL, 0x9B2DD2BB69AC6CBFULL, 
            0x367EA6E36AC3671DULL, 0xF336045CB2D86A08ULL, 0xEAF5D9B0BD89D18CULL, 0xD10F5A76C298A284ULL, 
            0xA1B08F06BFF6E68CULL, 0x4AF02819943D9C5EULL, 0xC7941B6E2C0345C3ULL, 0x30D87C15B65276DAULL, 
            0x3D48A5A900B36817ULL, 0xFA59FE161A5FF2C0ULL, 0x1CD2ECEB228A68E8ULL, 0x5FE9AE3CE93A6E02ULL, 
            0xC238DC65C3A1D3C0ULL, 0x983B38B7567D61D3ULL, 0x9DD6F476EACF7701ULL, 0x9E3C7D19A5E6A0F2ULL, 
            0xA7A555EE986FA142ULL, 0x64801763E4C44CA4ULL, 0x5B592A3F197284F7ULL, 0x0C4A5FD5BE6A84B4ULL, 
            0x86F581D303FE992EULL, 0xC4DD21BC0BE2DD13ULL, 0x428A5C9862B64913ULL, 0x680673A46ABF5970ULL
        }
    },
    {
        {
            0x87DCA4D08698FDBAULL, 0x4B179D7C0DFF2DB9ULL, 0x6B9B6F25586CA83AULL, 0xBDE73D181DD57F87ULL, 
            0xE6577B362A759A4BULL, 0xF61EF01D1A80D7A3ULL, 0xECB011E346877ACFULL, 0x7A677C7A40F02722ULL, 
            0xF388AEEC56989817ULL, 0x17C465ACFC8F3EBFULL, 0x8869B029FE8484C5ULL, 0xC84DD1DB1677CC0FULL, 
            0x6EA7791C507A4516ULL, 0x7BBB9FEE2212BD3EULL, 0x0727FE5E81E5A06CULL, 0xC172A14AC0B0C463ULL, 
            0xFCBEDFD0A442D71FULL, 0x13DB4C281AA77624ULL, 0xCD835CBC9735917AULL, 0x4D3678D034E57C1FULL, 
            0x3B2357B3C8C97B80ULL, 0x6557D2DBEAFF90CCULL, 0x6B23AA44B3EB75CCULL, 0x6AA13A0A8ED9345AULL, 
            0xFB415C807FD11668ULL, 0x493E13C14AD41688ULL, 0xA11D60E284FA2B94ULL, 0xE7BC597CE07AE9C4ULL, 
            0x3A7BDB6F15F849B0ULL, 0x55B7D6FF015C2B41ULL, 0xA40DE829257A5FBFULL, 0xF1911469BA1073B3ULL
        },
        {
            0x9FCA6A28CF7ED199ULL, 0xF3B3528A8B17F48DULL, 0x1E64D937F1B7FBD1ULL, 0xBF4E2CD000F13925ULL, 
            0xD83FF7E8D604FB42ULL, 0x29508804BF96F002ULL, 0x692C1AA04308D2A9ULL, 0x2A624418EF8D1FB5ULL, 
            0x0DFE6C6E0C5A9DF4ULL, 0x3BB71C357A6594E3ULL, 0x7FE9623A8E7A9720ULL, 0xB40479252FEEFE9EULL, 
            0x0A7BEE28B4F1530BULL, 0x8CF39AFBA1173721ULL, 0x8AE474853A1B3A7CULL, 0x87F57344121C074DULL, 
            0xEB61E773C51C7AC3ULL, 0x76ABB843B752D91FULL, 0x06ED9E00B4B55CE9ULL, 0x89A52358E3E5AC1FULL, 
            0x5A9B7EA9B1E0F871ULL, 0x5F88DAEB7571BB14ULL, 0x722F31AD458F3E53ULL, 0x0F3C2D410322C40EULL, 
            0x5069699391B466FAULL, 0x368F699607F9EE8EULL, 0xB80B191C6AC921DDULL, 0x0D2150EFCA5488E1ULL, 
            0x5B7C3DB6AB75F88EULL, 0x47265E4799FC9654ULL, 0xA3AB355E0A018F80ULL, 0x17E5E306DFF25C54ULL
        },
        {
            0xC80C316A79B11B47ULL, 0x5B272454ACEA4A8CULL, 0x15A087C495046E26ULL, 0xB8E4B9AA9CCC0D69ULL, 
            0x3BE21C375CDFBE3FULL, 0xABA23A9BABB5283CULL, 0xB27A8020CF77A3ABULL, 0xBF9F2EB19BFA020EULL, 
            0x35E8B33418333C0AULL, 0x91225D3F402926C9ULL, 0xDC2B072EDC53E38AULL, 0x6F86668DE477C741ULL, 
            0x758BC892FF537D9CULL, 0x3F692EBDC2E29072ULL, 0xF8289CA03125B583ULL, 0x1D108C16A9A48A3DULL, 
            0x1BDB3987F53A587CULL, 0x72053E7D43D7E37EULL, 0xD539BAD82E38D1E5ULL, 0x4E24EC07AEB6ED85ULL, 
            0x90FE230E4BEBA969ULL, 0xAB5DD72CC09BA601ULL, 0xB6A1F8725B3FE46CULL, 0x0AEFE35222E75768ULL, 
            0xEC2BFF90D27FE4ABULL, 0xBE83CB486FE42546ULL, 0x17284BA21669E8C9ULL, 0xCC90D6FB1F6C428CULL, 
            0xC3E368586423D5C4ULL, 0x0B708BD9A7E24232ULL, 0x128BA21CC6E64982ULL, 0xCD8F7189C547FAB6ULL
        },
        {
            0x1601386AFA8436EAULL, 0xF5847213CEC0875AULL, 0x48F1B55C725B157AULL, 0x2E9E0FD97A0BEFF2ULL, 
            0x346C0DDF6C8E96F9ULL, 0xA05442DDFF2AE809ULL, 0xB68AE342D2B554B7ULL, 0xFC7F61210998267CULL, 
            0x496BF331696DB416ULL, 0x1B811381B3CC35A7ULL, 0x452693F9E0C707C7ULL, 0x09E0C0BF1366E5D4ULL, 
            0x46DBB23B5DB38403ULL, 0xC1057F132EB77EAFULL, 0x9BC6273A2E2F843AULL, 0xCB25641D452CF3E2ULL, 
            0x924D3DADBD976788ULL, 0x2DD04E86AFFF70B8ULL, 0xB2551406D5D5D8FAULL, 0x6520CE70EBC6CDCBULL, 
            0xD6F1CC804BAD0349ULL, 0xAA996672326FACDFULL, 0x33947F5C08C951D7ULL, 0xAED1B12DB95EB447ULL, 
            0xD1BE0B446217F73BULL, 0x3275B5F5B2261791ULL, 0xA475C1F771B11DE2ULL, 0x93EA4166574ABCB2ULL, 
            0xC1700E0D9D9F65D4ULL, 0xB94D52B5ED04CD36ULL, 0xAAA6CE627437EA60ULL, 0x0658D16D1A649647ULL
        },
        {
            0x8B9ED20451C15BB3ULL, 0xDC983DAA46D9ACA0ULL, 0x45B78DA262E9F39CULL, 0x9AA3114662FF4020ULL, 
            0x7D6B7E28A6C532DCULL, 0x44CD06DDB8663F91ULL, 0xB7DED44A8B2239DAULL, 0x83F7B6A68A85E5A5ULL, 
            0xAB41B745A533B1B3ULL, 0x2D088739D9987198ULL, 0x287B765CD2C03F7DULL, 0x8A43A8F53F36CD7FULL, 
            0x98BA151C14484F27ULL, 0x97BF6080B2679C2BULL, 0x001775F56F93105FULL, 0xD1915F637AB0B7F5ULL, 
            0x85F95A446371A589ULL, 0xC0CFCA0267299296ULL, 0x9E94C3F51B785C30ULL, 0x6191E980D907F242ULL, 
            0xC6BC0F8B105BB203ULL, 0x4BD7616B23F84F4EULL, 0xE31050A5C3BC5F2CULL, 0x10C07E4DBD18FB3AULL, 
            0xBD1B52AD1ADE767BULL, 0x1802D4E2BA66044FULL, 0xFCE0977B154D1C17ULL, 0x4A5E500A33BB01B0ULL, 
            0x0CB9631ED4E67F3EULL, 0x7D4A643FFB0E15D8ULL, 0xBEE188CAE5E7FC3BULL, 0x5596F7AF5F60D610ULL
        },
        {
            0xD0A428D18D96B113ULL, 0xF410F58E5F100D95ULL, 0x00D8F28EEC0D8178ULL, 0x42D9475E03CABAFAULL, 
            0xCF9E6F390BC2AE69ULL, 0xC5A7AB7AD10EF590ULL, 0x1D58AD97CA74EC36ULL, 0x78784DCF9B5D842CULL, 
            0x51CAF89451889362ULL, 0x317F785306B36875ULL, 0x004694F3803D928AULL, 0x42E11D6177F68BCAULL, 
            0x9EC0FFFBCD750F74ULL, 0xA648A673AD85C27CULL, 0x164D87DF03D391E1ULL, 0x5B5203FCC5141D9DULL, 
            0x4B15B7475AD0FF47ULL, 0x735954003E35552CULL, 0xE2200F19A2BF3575ULL, 0x78FC92BF8B0DFC3DULL, 
            0x6CCE071B5417C6AFULL, 0xBF53FD4F82E1EF1EULL, 0x935C10DD0694B2D8ULL, 0x4BA5BD1F41CF015AULL, 
            0xAFC8D6C5D228BC12ULL, 0x2220D30FB5C7D07FULL, 0x8C3D4BF84B60492CULL, 0x24ACAC8049667E49ULL, 
            0xE5F8690174632DBBULL, 0xECE709F9791130E7ULL, 0x8C0B3F3A07D7024BULL, 0xFD228CF2A98E98F8ULL
        }
    },
    {
        {
            0xBB7CC5A2B26C8EF4ULL, 0x2F60C5D992307A19ULL, 0x57424A140D044165ULL, 0x9CD38557D2C295E5ULL, 
            0x430D68F028D8ACAEULL, 0x5E0D77025C615AA9ULL, 0x3C7646A4F5379C2FULL, 0x694A1F61F3BBAF95ULL, 
            0x91488FAD4DAB0E57ULL, 0x89AEE6A8AD6F9AC1ULL, 0x1D67CBF18F0A3AF7ULL, 0x70E756C24E6BABB7ULL, 
            0x0341709A9D3B1BB0ULL, 0x1EBBB25CAB9C4B52ULL, 0xCABB966241814AC5ULL, 0x82B2406888B8AD20ULL, 
            0x5B3CEFE7DEC8833EULL, 0xFEC49E30E9041C81ULL, 0x7ED6A723416729C2ULL, 0x859BE0E80F9168CAULL, 
            0x062941659A298D1CULL, 0x12B1B05090BC58AEULL, 0xCD83E8AB9E71528CULL, 0x24A447F0E5B95937ULL, 
            0x79C287A950347682ULL, 0x7D3403410ABE41F3ULL, 0x5FF8898D243DDCA9ULL, 0xA85D32EEABD4169EULL, 
            0xECAE18F7CA3CA81FULL, 0x0CD20C073B680D43ULL, 0x3DE7F1D2F69BC6D5ULL, 0xC9F6F68AAFBC5729ULL
        },
        {
            0xA527E0CC5AE96DFCULL, 0xD2C9F0E5DE031F1DULL, 0x91B67DCBD8E91F96ULL, 0x0B2DB65D51331C99ULL, 
            0x9AAB45B4D98C9F30ULL, 0x149D2555DF9FFABCULL, 0xD536357A3573116DULL, 0x447E457ECE0CA760ULL, 
            0xE15167670A254003ULL, 0xC475976515335BCEULL, 0xEAC6699C1EC22082ULL, 0x720EEC8BDDA2AA2FULL, 
            0x881E3DC1420C8597ULL, 0x29AB4340DD12683CULL, 0x77D8473D780D5960ULL, 0xC79846279DFD87E8ULL, 
            0x1EE0587BC48C4782ULL, 0x05A49DBAB529E3D8ULL, 0x24F78DD8EC1EFC2DULL, 0x7E15028C977DA094ULL, 
            0x0899D2259689A92DULL, 0x0A255A2E51CA9771ULL, 0x2249EC9D43F16867ULL, 0xC88D92B7FFB504E0ULL, 
            0x7E51F5CFA7B50F7AULL, 0xBFEA231FA2A8BCAAULL, 0x56D052256899BA6FULL, 0x39B2DFD53E66AA08ULL, 
            0x6052902F94C61ACAULL, 0xCA6B01A2FA7E7F1DULL, 0x786333FC3CA24B4CULL, 0x61AE3A541F63223CULL
        },
        {
            0x78C55DA2E78CFA49ULL, 0x1A5857E5F1A096E3ULL, 0x4C7F13F4E51B2B3FULL, 0xF1F708A514519399ULL, 
            0x24C40198389C7A7EULL, 0x233B6DAC11848015ULL, 0x49E939CA0070044DULL, 0x022201E22DDAB9A8ULL, 
            0xA1AA98EEC6281C87ULL, 0x5F76937ED9A44202ULL, 0xA019018E16D65E0EULL, 0xA78A0B483768100BULL, 
            0xB2C66FE8838041A8ULL, 0xF32E462B71FFF8C2ULL, 0x93F91F5997690A41ULL, 0x056DB95D38D718A4ULL, 
            0x2272AE524FBF9A37ULL, 0x9C35965107DECF02ULL, 0x51CE14004651492BULL, 0x7E94B12499DE485CULL, 
            0xF2606B42446BB81DULL, 0x47815D9BD6CE2C30ULL, 0xA7DBC489DF32914CULL, 0x86BFCEF3B1DE762BULL, 
            0x69746D5506EAD68EULL, 0xAF711B0B66E58887ULL, 0x978BFBE221714D61ULL, 0x248F88E61E3A70E0ULL, 
            0xB62240A3348BF6F1ULL, 0xFA47B95C68877EF2ULL, 0xE50E90F024820743ULL, 0xDD2782ECE851E2F3ULL
        },
        {
            0xDE39403253208450ULL, 0x6CD6F2CF212A6C84ULL, 0x08E06BE84FC66469ULL, 0xB8771FFF7FDD54D1ULL, 
            0xB274227E5C3D390BULL, 0x8DC54CF45398C300ULL, 0xCB4BD2487646E5AAULL, 0xB37B4646CBE86BC0ULL, 
            0x5C0A263605E3370AULL, 0xBFA1F0CE9B7C9FC6ULL, 0x08D3471C57E5B6F5ULL, 0xE8663BE1FFB7BAAAULL, 
            0x171BAF759F99B1EDULL, 0x28D49487F9512884ULL, 0x068B04F877CB6E20ULL, 0xE6C3DFE7E22E01E3ULL, 
            0x5BB6D23246ED2BE3ULL, 0x8C6583794DE30459ULL, 0x4971F8178A9AD864ULL, 0x5D07F203B0591CDFULL, 
            0xE31745224FCEE52AULL, 0x5C34CB3AA28D29FDULL, 0xB76C0376C6E1E9EEULL, 0xEDF6C2A97E8AE270ULL, 
            0xD59DA88C32E89D78ULL, 0xC60BE3E375A7B808ULL, 0x95F27356B7D4D9FDULL, 0x5C65F36061AB8A41ULL, 
            0xDD56F9989944BA46ULL, 0xAE8D48DC61103D6DULL, 0xE65CC9694932058BULL, 0x3C4387EA8720EC97ULL
        },
        {
            0x93CD852BEE6E22A7ULL, 0x978675AD54F283BAULL, 0x6240924AA0503124ULL, 0xB3F5758AEA540A89ULL, 
            0x53847987C6F39651ULL, 0xE8B03754EC9CB22DULL, 0x27A9C94E0ED6DFDFULL, 0x3289D96D6D1085FDULL, 
            0x1879E68B4C8351FDULL, 0xE413EBC03B4B56BCULL, 0x842BA386010DD75DULL, 0xD66DABF90392B38FULL, 
            0x845393837A417D84ULL, 0x5C841EE7FEE2456AULL, 0x18A8716A72D82E6BULL, 0xF35D211FC96AABDBULL, 
            0x5BCCBC55E5396122ULL, 0xCC1A0FAC50A823DDULL, 0xD910EF39057A31B5ULL, 0x054842DAEFBC4F50ULL, 
            0xD445BFD0A67F9FC2ULL, 0xD98F8A14D386B83FULL, 0x1A613411885F2818ULL, 0xC5E7864172BDB241ULL, 
            0x09E0C95AD3C609DEULL, 0x405A5FD674ADF78EULL, 0xF9714D119B946AD0ULL, 0x68A2A7D056729F7DULL, 
            0x635D1812007A15D0ULL, 0x6EC585FCA1E5DB08ULL, 0xDBBBDE96F86DC72DULL, 0x5C49E7F3A68CB0FBULL
        },
        {
            0x4AC1D1038A4B1638ULL, 0xC7F52688114A25AAULL, 0x1E63D4CDF6048966ULL, 0x594CDB88D4851BBEULL, 
            0x86FBDF0FC1C71B1BULL, 0x3BA828D94C6B3E9FULL, 0x8E908841F254BB7DULL, 0xE27A6CF716F05E7AULL, 
            0x8B4A16E70C314C16ULL, 0xDF98D7EE5DA3DEFAULL, 0x3FCD32B9D48C513FULL, 0x2358952C0E30A5ADULL, 
            0x76ABC731FFB100A7ULL, 0x62A5862684068A01ULL, 0x1D7B1C954B40523EULL, 0x7876C67594842BD0ULL, 
            0xE6AB88C1B1FAD4E0ULL, 0xC24D438773E0C793ULL, 0xB58A42D71531655FULL, 0x7C0903CFA510284BULL, 
            0x6183BEF574C095BFULL, 0xFD42D04D069A17F6ULL, 0x547B2CB3952DC3E2ULL, 0x16A6FD6FB436D429ULL, 
            0x10D5E01964AC8AE3ULL, 0x6AEB3957BDA47313ULL, 0xD912304AE58AD760ULL, 0x8253DF1C49DCC2BDULL, 
            0x0812DDD2512854B8ULL, 0x5F170C5577BCD491ULL, 0x45846CCC89A93BF6ULL, 0x8E8B80498CF46F63ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseAConstants = {
    0x01541F5E9719E59FULL,
    0x6467B43E68E3FD00ULL,
    0x50B88B5E25A53E3EULL,
    0x01541F5E9719E59FULL,
    0x6467B43E68E3FD00ULL,
    0x50B88B5E25A53E3EULL,
    0x9048D5F97CDE4E0CULL,
    0x19D1A6CF304EC9D7ULL,
    0xD2,
    0x07,
    0xAB,
    0x27,
    0xB1,
    0x93,
    0x37,
    0x8E
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseBSalts = {
    {
        {
            0x2496ECF20383C188ULL, 0x4AD15D44861A65B1ULL, 0x73DF799E8D3E6D5FULL, 0x1F20B380B86B06C2ULL, 
            0x1FA51AF48BBD84ADULL, 0x3F78EA36AC6E5B8AULL, 0x27000FDCCCF3CEF1ULL, 0x1800DBCAA4110644ULL, 
            0x0FDE3C1935010099ULL, 0xFD63AC544C680A1CULL, 0xADCE72BC52E5E3F7ULL, 0xF9D4F5B266713A6BULL, 
            0x08669C909920D608ULL, 0xD04990D70510112CULL, 0x75B24AF3AF6AC9DDULL, 0xD112B3D1CB800F00ULL, 
            0xB84BDF85F7534591ULL, 0xCA49342504B2B551ULL, 0x7AED1F14F586508AULL, 0xDFC2A5A6A53B4231ULL, 
            0x0CADD823751527C6ULL, 0x698D1F7D913E796EULL, 0xBB93154B3862C0BFULL, 0xF20F5508B8DE8B7FULL, 
            0xDD819BD8E12A5E92ULL, 0x260C4665D6CEB1AFULL, 0xFACE48EEA5C38DCEULL, 0xB79836D2C8AA7A13ULL, 
            0x3FE1F8790301694AULL, 0x607F690397E3B31FULL, 0x62F4083DD8F8C028ULL, 0xCDC09ECBD61E145DULL
        },
        {
            0xE24C292D581D8D0FULL, 0x5BF168CF98889688ULL, 0x3D274DCD10458BD6ULL, 0x8EE4BEA22BB853BAULL, 
            0x400E61D2FB2DE331ULL, 0x89B3F5F21C5E5736ULL, 0x82062CD15F04C1A5ULL, 0x92E90897B0E55CB3ULL, 
            0x531587369A4BDA0CULL, 0xD2BA26E90FD54EB1ULL, 0x77C6571F48F9D8C2ULL, 0xEF7BBE451847B0ACULL, 
            0xAEEFDB3F7CB23397ULL, 0x0C69537F3CC92B21ULL, 0x5915D3A3349C7A0EULL, 0xEB5E7549BEF9DD41ULL, 
            0xF4FB81F04B909FBFULL, 0x2BF6F208CAFC2D02ULL, 0x41DDA243A4D55589ULL, 0x34220C3BDE2075FDULL, 
            0xA9D71C1203CBE994ULL, 0xC248117111B02E0BULL, 0x6D30100CECCC1D7FULL, 0xF11C97D25BD305AFULL, 
            0x044BEE892666F322ULL, 0xA194635923B6E330ULL, 0x0CAFF662498B561DULL, 0x3DA823D7AE923393ULL, 
            0x250BBF8100CEA778ULL, 0x085AB5923438EBA5ULL, 0x7B9B617B38A11533ULL, 0x3288D911668E3FEBULL
        },
        {
            0x4A83C6BB53E94F7DULL, 0x78DC7E5734938D4AULL, 0x813B61669C963F01ULL, 0x946D183A483EED06ULL, 
            0x5C1B0BA3CDDC2D49ULL, 0x27A8D9025809E364ULL, 0x8D0270FB82B99B2BULL, 0x47A3880877CA88CEULL, 
            0xE825A52898EE26DBULL, 0x9B64B39D60A9FB38ULL, 0x2C800A27ED0DC1D2ULL, 0x4625B047CFDBF6CDULL, 
            0x04A824C9FA5F7B54ULL, 0x63E232575E11FB83ULL, 0x9AB9586C2BD62100ULL, 0x6BBA3BF5E65A0B62ULL, 
            0x675B8BBD4B682AE5ULL, 0x8959BB4D4E44FCFBULL, 0x8BF272FE2A154F4EULL, 0x5E5110FD1BE3B0FCULL, 
            0xFC05C12CC1911D8FULL, 0x4118671B6062089FULL, 0xD750F2A67C7854E9ULL, 0x16F643CB792A0D46ULL, 
            0x277F3A0F387F8C5CULL, 0xBA9295381FDECAAEULL, 0x3B4CB61267346C72ULL, 0x7E576A251DB2C60EULL, 
            0x205DCAD64AD3FFE2ULL, 0xE6B2C86015F36631ULL, 0xF58264CB3DFD5DD7ULL, 0xD16F803AADBC79E3ULL
        },
        {
            0x170BD709A52106AFULL, 0xBBA9FC91C28C77E0ULL, 0x60490C9FE0B0FBD4ULL, 0x75AA2DC689BD9F2FULL, 
            0x0A6C55D896FA951AULL, 0x7045EB6240538A4AULL, 0x6966E91CD6987E1EULL, 0x781FCC9F4EC727B6ULL, 
            0xE632D126256CFA57ULL, 0xFEAC8A18E6947FC0ULL, 0x44D2C36367D109BCULL, 0x6C0AF0BFBCEA85F8ULL, 
            0xA951182F846B2E31ULL, 0x702ECDE5C7871A7BULL, 0xDC2B137FC48ABE93ULL, 0x67E60F6920685EF3ULL, 
            0xDB47DBEB6A9CC63CULL, 0x281B7C4CF78B4885ULL, 0x7CC69988FF38D4A3ULL, 0x10B4C507E285E0E9ULL, 
            0xA85DB3F7E214B927ULL, 0x79BD1EDC1ABC1BB1ULL, 0xDE7C594C3D9FE6E1ULL, 0x1E5BAF1B37A462C4ULL, 
            0x11A12E9C96FA3819ULL, 0xC8486146A18870A1ULL, 0xCF56C2C90ABFED67ULL, 0xAF2377170F526B3CULL, 
            0x86AB9EB92B420D23ULL, 0x0CE8F307CAC3D3B7ULL, 0x2952947CEAE94BF7ULL, 0xA9D39F076199C987ULL
        },
        {
            0x20BDE8CDFEF886AFULL, 0xB969EFC50220938BULL, 0xFECDE2DA2F6B4D03ULL, 0x3486879E522E118FULL, 
            0x1AAE5C13927C778DULL, 0x46538466FC40460FULL, 0xE151A6AEDC72A9B7ULL, 0x76E9DB7807B5F06EULL, 
            0xAB4F922A62D5B699ULL, 0xDC5C61C22063A049ULL, 0xDED2ED01B3700D38ULL, 0x4587C8199C47CD19ULL, 
            0xB13D1ABA3D932AD9ULL, 0x188323E1B6E3B1CFULL, 0xC22E7714090D2CC1ULL, 0x4AF5A6EBDE895C00ULL, 
            0x564C8DA810ECAC93ULL, 0x3B6EF9D0CF187EFCULL, 0x04F2AABC4ED27D32ULL, 0xCE6DCC7360A20869ULL, 
            0xC7F479A6A72DCA46ULL, 0x60B9EB42B0B73089ULL, 0x560F6B08D8547C08ULL, 0x8B6E27D80C1D3E1CULL, 
            0xBD60AF3FA67C4D85ULL, 0x86240D1D47BC691BULL, 0x9478AB8D6CC5DDC3ULL, 0x2C3119FE8E558A44ULL, 
            0xC0A3CD6F9EA80148ULL, 0xF6AC8980327B29ADULL, 0x61FDC9B53733876AULL, 0x006745A67E6C8CD4ULL
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
            0x06E069706C9D65DCULL, 0x0FEF3DECDAF4F06CULL, 0x06E4402EA00F10B7ULL, 0x2D6239241208F457ULL, 
            0x1E5DAEF18662BC03ULL, 0xF11402CE1B84CA78ULL, 0x7072D41666D3B06AULL, 0x44C1DC08354A317BULL, 
            0xFEB177CC7FC58B31ULL, 0x79C9A522A3F023AAULL, 0x24284E6A60E238DBULL, 0xD2EE5432D6CF350FULL, 
            0x33B5E4283EC87F2DULL, 0xB8FF4FF3AC7726DAULL, 0x99170AF7B52335E0ULL, 0x45246E76DFCD97C1ULL, 
            0x9460B5A21BEB9CF8ULL, 0xE867B8D6DBC60C4FULL, 0x8A732213D5F5ADF3ULL, 0x3E02C344D169E80DULL, 
            0xA75A54AB68E95CB1ULL, 0x7E756016437A1177ULL, 0xD4F2989F95D96DE4ULL, 0xE8F3A758FBD47D14ULL, 
            0x98A875A056E06047ULL, 0x219A9DB38DD0CE8FULL, 0x04EE80992377A156ULL, 0xA9984C1F9BA6C792ULL, 
            0x45BEC54A504E2868ULL, 0x58D7D64809912E95ULL, 0x46274146BB8ABFE4ULL, 0x72759A82A5C9E8B7ULL
        },
        {
            0xA96C9283BBAD379BULL, 0x84F31C8FD9A5B8F5ULL, 0x40BBC3ECEDB230B0ULL, 0x97FA9FDAF89994D1ULL, 
            0x1250E9C42A774AACULL, 0x1BAB373AF8393657ULL, 0xB8339290D9EBB919ULL, 0x4996B24251742FDCULL, 
            0xF6EAA59F8F54C5B8ULL, 0x552EDD381C0EFD1FULL, 0x7382EB231973D6DDULL, 0xED52BC065CD5E653ULL, 
            0xB7B5EB3CA531AF2BULL, 0x91EF03C662F373DFULL, 0x913F91C9DB531EB1ULL, 0xF001AB5DC1C56655ULL, 
            0x34E8813A70A1D270ULL, 0x38EA783576EF864EULL, 0x692FB64C81A78050ULL, 0x233D25032B3A32D7ULL, 
            0xFBABEF935882814BULL, 0x8FF3688803975A20ULL, 0x1D17D0D4E276E585ULL, 0x6D670100A619BEF2ULL, 
            0x93E1F863DB9FE802ULL, 0xF46F8F77A76838DCULL, 0x9E365DEB1633B798ULL, 0xB21402FE693F3E65ULL, 
            0xE9B3129290543E37ULL, 0xA584AE3B4ED292C6ULL, 0xCC71669D3CC064B9ULL, 0xC9CA8F534F3CE70DULL
        },
        {
            0x368B41B41E43DC26ULL, 0xFF7B1194F1092F8CULL, 0x1882EAD09C712572ULL, 0x024EFF4A9F1D748EULL, 
            0x89ABF2500E1EBE13ULL, 0x270B8798A4C3EE57ULL, 0x952E15E07563E2EFULL, 0xCDD932C89732BEB0ULL, 
            0xA3F1F6825F346B8FULL, 0x460B9903C7198B17ULL, 0x62118BA811999A49ULL, 0x665C85D16BD1202DULL, 
            0xFA5B7018F208B2B2ULL, 0xF4A400E85EF68A83ULL, 0xEA1C470C2DCE62FFULL, 0x12343BC6BB598975ULL, 
            0xEDDF8B189E7D2EC7ULL, 0xBA4FDC265B812C8FULL, 0xDB7DABF191AE176CULL, 0xA9E0A17531612FFBULL, 
            0x88644429375D6C22ULL, 0x97B806544413D291ULL, 0x13177182307FCDBDULL, 0x9304983D31ED1ED9ULL, 
            0xD71BBB63984E6661ULL, 0xCB119D8DA37E8272ULL, 0x7F9B68FED91688ECULL, 0x54685D3EC17C23C3ULL, 
            0xC4ADCBDE3B6CBFEBULL, 0x883725A1849B254EULL, 0xD2B7FFC7F002E4E9ULL, 0x7FA49C0377FD4467ULL
        },
        {
            0x3004C657A1D4227AULL, 0x4527FB091C0047CFULL, 0x45674E0F6FE3DF46ULL, 0x5A34A3357D2C2657ULL, 
            0xC7334AB58C745FA0ULL, 0x6D12286F49778C78ULL, 0x6ABC7899FB8ECE13ULL, 0x002BE251C0AB91E0ULL, 
            0x2315A88A2DCEEDF5ULL, 0xB75B6FEDA3155092ULL, 0xDCB4C22B730FDD39ULL, 0xCC60B03C569E60E3ULL, 
            0x0003718C04B5625CULL, 0xD74149E1694FA523ULL, 0x40D868DE11186FA5ULL, 0xF07C1A2652CD8F65ULL, 
            0xDD52BB54D3991804ULL, 0xC6D5C7A62C7ECF37ULL, 0x93F3C7F488CDBC08ULL, 0xB4B3444E08ED1891ULL, 
            0x5D52635B9321C13AULL, 0x519C803C073A1F83ULL, 0x8CBC743EFCA95B89ULL, 0x5CADF22105785C1BULL, 
            0x2DA09DDA345226DBULL, 0x1C1E8C6D637D8093ULL, 0xD17D3DC9D03733EAULL, 0x01A69BE692DC7198ULL, 
            0x388B716F6085A0CEULL, 0x05E23F2A1B2579ABULL, 0x0E1E3FD18FBA56D9ULL, 0x2CDAB27E36A6928CULL
        },
        {
            0x4B899E672BB31AF6ULL, 0x1AF149165058E22FULL, 0x423514167BAC109DULL, 0x8A65C19A15757979ULL, 
            0x912AFCAD7C210980ULL, 0x248E828825A501BFULL, 0xFC9E44959B156A5FULL, 0x7D2D08D7809AF7BCULL, 
            0x32684EF2EBE12CB7ULL, 0x3D6BF80FDC70A1CBULL, 0xBDDB0796ADCF9B08ULL, 0xB245C3C075C29948ULL, 
            0x44618601F2374DA8ULL, 0x34972521CDC0F707ULL, 0xC9CEF9158948262AULL, 0xC908076538BC3263ULL, 
            0xA04814C3FF8DE828ULL, 0x026EAB009DFFF388ULL, 0x68DE748D182FFE4AULL, 0x9F2D75847C5D18CFULL, 
            0xDD63E9807213EEBFULL, 0x4AABAEC027037A53ULL, 0x5C825492698EF52CULL, 0xCEB0EE13B5CA8E56ULL, 
            0x9723A64D11A8FD9CULL, 0xA374A0BB76BB4DCFULL, 0x46FF312FB1FA9890ULL, 0x90F6B6270405BAD4ULL, 
            0xEDDEED743CC9A66CULL, 0xDB072D1A5555FB7DULL, 0x0D06314A28F07789ULL, 0xBDF870080BE49F4BULL
        },
        {
            0xBBCC4BBC8497DF37ULL, 0xBA7B096E1BDD13D9ULL, 0xC429E119502DF054ULL, 0xF9C6CD0883A1B08DULL, 
            0x36DE2705B7958B0CULL, 0x219474EBA1C01D43ULL, 0xC43BD7372B7A7CC0ULL, 0x2924E528F2EC62BAULL, 
            0xFA59F0289AA7D970ULL, 0x175556A5C9F7E6B2ULL, 0xA085C6DE3C1D685FULL, 0x031530DC547ECA2AULL, 
            0xD84BFD4B5AFC7F63ULL, 0x0DF49A65388266F0ULL, 0x38D02E2F9FB53C82ULL, 0x65838FA1521D37D1ULL, 
            0x01AF21AEEC1DEE45ULL, 0x806A1708A98977E3ULL, 0x6BDE0AD6D908D45BULL, 0x474654BFE3F36005ULL, 
            0xCC75E1B3BB1B2004ULL, 0x4D600545F8264384ULL, 0xC9D685BD578A7410ULL, 0x544F713C3DB128C8ULL, 
            0xFAAA9EB10EB6750EULL, 0xDCC425162CFA02D7ULL, 0x6D62BDBDC10B3756ULL, 0x6E114F709442771BULL, 
            0xBCE304C3EA12ACFDULL, 0x21CECD2CABEC48D6ULL, 0x7C2FD2EC971626D9ULL, 0xAC2185ED5C0113E0ULL
        }
    },
    {
        {
            0x7426B2F8D4138846ULL, 0x636F20CEB1B974E3ULL, 0x0EE712E32FB22A48ULL, 0x13FB95FFBA56DF09ULL, 
            0x95C7FA798C8AA774ULL, 0x2A8B548980C81512ULL, 0x960757B88FFF53E8ULL, 0x002863DB5AFCD474ULL, 
            0x4D98F87BE9DFEB30ULL, 0x96E9F782DCFF961BULL, 0x018B8A214B074841ULL, 0x7E0385C2C353CD0AULL, 
            0x130C1F5503DFA812ULL, 0x2CD53E4A66B88F9BULL, 0x32B279A78D95BF72ULL, 0x7885B9CB3145322FULL, 
            0xAB3897707DE4B92CULL, 0x31C4BDD45CF1E4E0ULL, 0x6927F4B47B366CF3ULL, 0x401A575F65D107A9ULL, 
            0xB8A424B1682A8284ULL, 0x7085970E43BA7081ULL, 0xC97A33872A5D775BULL, 0x4C8B6BFCED6C1A9BULL, 
            0x48C0C59C19A5AF52ULL, 0x7BFAC0826D395E7EULL, 0xB6FE06CC84F9B470ULL, 0x102ED2AF6C5E2107ULL, 
            0x4979821DCC7B0BC4ULL, 0x16FC7FD170780AACULL, 0x27135499509292DAULL, 0x0B4F0E7FEC8252B0ULL
        },
        {
            0xEB2EED0B1B9CF4CEULL, 0x4F1EA5481F079D87ULL, 0xF9D925C3B4290A7CULL, 0xEED899F504CCC620ULL, 
            0x72CCEB48BF874B19ULL, 0xE72079D85FCD1AF4ULL, 0xB00718E439439CC7ULL, 0xF2BFC9BC471ED882ULL, 
            0xA10AE9AFD04A1885ULL, 0x30BE8203066D1FB2ULL, 0x4E4BE296AB92C29CULL, 0x6DBF763FEA34AF98ULL, 
            0x87E170B4A7B6959FULL, 0xFCF8103B20698A9CULL, 0x49C10E240C284662ULL, 0xECDCF4788C5E0A8EULL, 
            0xB805025C730EC719ULL, 0xEACE61164B004826ULL, 0x1696DF2CF4DA9C8CULL, 0x8E1F8472EEA3D986ULL, 
            0x4D6DB6FF009210F8ULL, 0x1751CAC7EC9C5BCCULL, 0xE4CDDB628C3EEA7EULL, 0xFBAF53BAC92A8E3CULL, 
            0x5EF78E330D33FB0DULL, 0x2E9C0BEC7AD72ACDULL, 0xBBC6ACB778B7E471ULL, 0x6C86865082706D85ULL, 
            0x1EBDC3E19A6CC17DULL, 0x3FA02604C08E5417ULL, 0x284E1DBB3ADA404DULL, 0x629D814F89651DC2ULL
        },
        {
            0xAAF70DF6647C1015ULL, 0x49CA992114BEA560ULL, 0x70D158A8993A0062ULL, 0xCCD3F01FD5DD98C2ULL, 
            0xC1CEEBB45ABC5C55ULL, 0x57EC5CF7C72A0EA9ULL, 0x30966D32E0089842ULL, 0x9B5CE72890110E96ULL, 
            0xA1ED31A2FABE70B6ULL, 0x523A322F9A99BE0FULL, 0x9E7CB977DE3AD611ULL, 0x3C6373CDD7EAB61FULL, 
            0x8E322EC6FF598D77ULL, 0x58677898B6D90D5CULL, 0x3A6C82DB451D3587ULL, 0x9EE1B4E33066C11EULL, 
            0x6AB2B92A8A5D0E1EULL, 0xF94231D5606A5A43ULL, 0xC2F7B314EB8804C3ULL, 0xB6A62DA19FCBE747ULL, 
            0xCA444930237E0E02ULL, 0x35DD978F79332496ULL, 0x687E6ECC2B76945CULL, 0x1F64AEE6AF18D6A5ULL, 
            0xB3D4563FFE08723AULL, 0x7FBB5C6EF4173BB2ULL, 0x03142F4B304B41B3ULL, 0x34021BBE5B34FF01ULL, 
            0x6C74D0E8B4925529ULL, 0xFF216C5E375BB651ULL, 0xA0FA80E72E3DE3DBULL, 0x829A699708D79FABULL
        },
        {
            0x6664F50AA60BDED4ULL, 0xAC52D43FE9081717ULL, 0xDA50EF2F9870D158ULL, 0x794BA2F0D26FA67CULL, 
            0xD3B4371E50B71785ULL, 0x7E785FB703F73CDDULL, 0x1FBFDA310CA5A03AULL, 0x65C450B56EE1971CULL, 
            0x8A375C448BD2F185ULL, 0xFCD61D67714FDE0FULL, 0x743F7CEE0D3B8762ULL, 0xAA13AEFC88765FFDULL, 
            0x7EFD4B948F8D6D6FULL, 0xF95807C37D0E97F3ULL, 0xAA81808F997FA083ULL, 0x98D6259DF3C31DA9ULL, 
            0x6E4573D6953E9AC7ULL, 0x5E38E708E789E7F0ULL, 0x9515BF9B8E1BD3C9ULL, 0x56BC74C9AB0496A8ULL, 
            0x8878F6CC2733F589ULL, 0x13A9E12E037DF4C2ULL, 0xFB4A7010B51C6E97ULL, 0xC3271DC3F5B04830ULL, 
            0x6F32D931F71B266AULL, 0x47C32170DB8EED1FULL, 0x68947F84B9023D13ULL, 0xBF378E4E51F85A07ULL, 
            0x38AB148765E18375ULL, 0xCC10CA9C8B761024ULL, 0xD9905658C66A8133ULL, 0x63B7521D92AD6694ULL
        },
        {
            0xE979CB64C9BAE4E5ULL, 0x2B037919AEC2847DULL, 0x5A2435546DA480ABULL, 0xD23CD9B064DC68D7ULL, 
            0x45EDD050A7CBFEEBULL, 0x5AC7C0928B449E40ULL, 0x0406C0AD1EAFE427ULL, 0xC412763574B0E8FBULL, 
            0x9E70AB17C9182810ULL, 0x0E5EA574A6604159ULL, 0x001BE776967581C5ULL, 0xBFE6BC23C860827FULL, 
            0xA52B3E1E28409CD6ULL, 0x40451C7CC374E520ULL, 0xBB659C28369294F9ULL, 0xF9195C1ABDA8FA72ULL, 
            0xE54B113EB9BAAAE1ULL, 0xEE899F1A87DE2C18ULL, 0x0EF528E629BD034BULL, 0xCD61A2D0D642EFC8ULL, 
            0x9EA4D9552159C43FULL, 0x58358BA6F7C32D0BULL, 0x3C44ABA8EA9A2C4CULL, 0x85051B2D52312812ULL, 
            0x2A70183EF72B59EEULL, 0x56DC27324B0F150BULL, 0x8C8F496481BB1662ULL, 0x6301757A22514C13ULL, 
            0x9F49BD4E67ECF068ULL, 0x28104CA15DEF823EULL, 0x86CA1D8A1A699BB3ULL, 0x922A8444AE7364ABULL
        },
        {
            0x879E1F9F139EB8D2ULL, 0xD695ACD9F79C9D7EULL, 0x13344041F9067AC7ULL, 0x3819914D2B036840ULL, 
            0x51C117A7B8992ACEULL, 0xFB7F92F024973F72ULL, 0xA7C91F5556175287ULL, 0x330F5879E295CD7DULL, 
            0xBC63D07C403F5E82ULL, 0x0B0628D2B895C8FBULL, 0xF4C3CA389EE78A7EULL, 0x46E5F3BB39FE6CBCULL, 
            0x3DD9CFB30C1919CFULL, 0xA0EBED4AB1CE10FFULL, 0x32C516C256076E97ULL, 0x244FABC1B80C7111ULL, 
            0x4D37AA5180F9863EULL, 0x7F62C7BF80409F45ULL, 0xBE5FBB5532C96D5AULL, 0x133D60E80F5C33B4ULL, 
            0xA0A8B19E24D66A42ULL, 0xEA549440369B8E24ULL, 0x351661260F3E274DULL, 0xD98B9A3870D4EFD6ULL, 
            0x51EEA8A616133FAEULL, 0xD07FF202DD1088FDULL, 0x09C443E66216C5C0ULL, 0x23944D4E5DF37E37ULL, 
            0xE4AE7CAC4B15E335ULL, 0x37C895D951ECB79FULL, 0x7793F6702569BB2BULL, 0xE029518CBD1DA3BDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseBConstants = {
    0x7CBF7C3F3E1BD494ULL,
    0x5C469F8AD7B8BF09ULL,
    0xEB435395AC9EC5FFULL,
    0x7CBF7C3F3E1BD494ULL,
    0x5C469F8AD7B8BF09ULL,
    0xEB435395AC9EC5FFULL,
    0x166438C516BE3FE7ULL,
    0x7C18E5C356515D7FULL,
    0x8E,
    0x54,
    0x0F,
    0xCB,
    0x06,
    0x4F,
    0x4B,
    0xAB
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseCSalts = {
    {
        {
            0xB84197D1312F2DF2ULL, 0xB68AD4B1D1426AA1ULL, 0xD9721814625747B6ULL, 0x5B94FED01CB5CB78ULL, 
            0xA33BE7C3D5D18C4FULL, 0xA5059BDBE3491E24ULL, 0xDEA049B98310689DULL, 0x749C076F88A1D67EULL, 
            0xABDF793158325B78ULL, 0xE26FCE8FE15B1694ULL, 0xB44A040AFEB21A29ULL, 0x2C92EB190849B4CCULL, 
            0x2E2B9B4DB4462A21ULL, 0x1893E51194000918ULL, 0xBF08DE0C3DEBF683ULL, 0x41A9657D9A20C27BULL, 
            0x19707AA2B1FC73A6ULL, 0x8BEA9EDCA9B8D451ULL, 0xA6995180156DCF36ULL, 0xCB43AACD8434C602ULL, 
            0x989694766327F221ULL, 0xC64E9D5D3D5CB0EAULL, 0xA64F4024B8FE3EAEULL, 0x6D7C87177A3D8889ULL, 
            0x117A951132D859D5ULL, 0x07D0F0DDC15A681DULL, 0x319297A57E7A030AULL, 0x7AB5C47B2994E489ULL, 
            0xF9A3B4CAD4E84F16ULL, 0xDFA6A4D5D9FC990DULL, 0xC7EAB2BDD50DC33DULL, 0x437F3177B4570B31ULL
        },
        {
            0x8A4482F13AF13CBEULL, 0xDFD85D6D0D7629BAULL, 0x29FD2CBB5F82846EULL, 0x9ED15F3EBE3EF6B6ULL, 
            0xF346F1327FE5EDA0ULL, 0x42E52EA878686E86ULL, 0xEB1A186B7E7409F9ULL, 0xDFEF0E647A0BD7D7ULL, 
            0x9211A624FDDBF141ULL, 0x99191F350858F84EULL, 0x04DD89695863B747ULL, 0xF436B6026121E712ULL, 
            0xE0B9550F5880DBBAULL, 0x19793910686A2C21ULL, 0x228EB156B7E16E2EULL, 0xD2B68F1320BBEDA8ULL, 
            0xB58CAB02BA9B0726ULL, 0x676DC1B545C43AADULL, 0xBEB867B6FFD4C406ULL, 0x3CD1FAC1D62EA576ULL, 
            0xEC750AE820B885ABULL, 0x434B982EA86DD3CAULL, 0xDCA5FE908F7AB69EULL, 0xD109726CCBE332BCULL, 
            0x89BB7D6F1BF37CEEULL, 0x12FCB27882DB3144ULL, 0x7BA9E3F4136E5674ULL, 0xDC3D67C64DE92674ULL, 
            0xE32E46F5DA7CD248ULL, 0xA0FE2F53186FB3A0ULL, 0xED30E493AA85179EULL, 0xAA2C0FE3AB509FEDULL
        },
        {
            0x8010A0F11B2C056DULL, 0x28D523D27469A97DULL, 0x98612134876ED7CAULL, 0x4F45FE65757BEF87ULL, 
            0x61A79EBE6E5FBB73ULL, 0x1C25E1D56E6E91A7ULL, 0xC73AA51091BAD3BBULL, 0xBE3B2EB0B501F0D3ULL, 
            0x1CFB1820EB11B1D2ULL, 0x7CDCA67B6D9ECDF2ULL, 0x58CFA9C49BE90777ULL, 0x538F3F324AA2C912ULL, 
            0x5FEC8B20E4394772ULL, 0xDC981CC1540872FBULL, 0x6EBDB1B77B54F5D2ULL, 0x5C74FA7B2365C54EULL, 
            0x0E65C80D099174A5ULL, 0x4E52B3D6F90E4AAFULL, 0x001EB0BF5AB135CAULL, 0x8305C28728E47680ULL, 
            0xEADCD0A6C3236C06ULL, 0x9F85E3FA7509015AULL, 0x4C4DCF61082842B9ULL, 0x345739DD9BEDCD40ULL, 
            0xCC02AC01ED088EC3ULL, 0x70FD4D0578B1514AULL, 0xCEEB17B4C97C6432ULL, 0x03241BF63B5EF22BULL, 
            0x8D8EE79A21792A2DULL, 0x4CB15FFA9C81A379ULL, 0xE0CC0A5E4A753726ULL, 0x34ED8050631B80B9ULL
        },
        {
            0x3BACCEA128D22368ULL, 0x486D2F36123605AFULL, 0xBB01C18740BC4825ULL, 0x3838FD2B3AF9D0EEULL, 
            0xFEEACE82F8516C6CULL, 0x152B19623128547EULL, 0x606125E5777648A5ULL, 0x28C82717F117D4CDULL, 
            0xDCC55249F65B6AFDULL, 0x0A29650C81D74F7AULL, 0x1DE76057662AEEFFULL, 0x50B13585C15FE4DAULL, 
            0xB144DAE0F1F16CC4ULL, 0x06C56E9D0539BCEFULL, 0xDB2C9DE8CF9444A1ULL, 0xE791CEAE7A08A73FULL, 
            0x6F868DC145343724ULL, 0x5F9DC468C6C8F669ULL, 0x044BE547E9246162ULL, 0x1A556AF3B59BB4DFULL, 
            0x7E7A6736209F03E4ULL, 0x4CD8A54C742DAAE8ULL, 0x6BCBDF16FE227DFCULL, 0xE30016E83DD86AECULL, 
            0x62895B142D4903A1ULL, 0xAE2D9950315382BAULL, 0xF3F40E4AA07E1978ULL, 0x1D1D562526781D0FULL, 
            0x105E3C6B28C5E96CULL, 0x96789D54E2462868ULL, 0xCB8FB6C2ED94D517ULL, 0xD6B36C644DD04D36ULL
        },
        {
            0x150E76D368B0F720ULL, 0xC60F20CA952E0097ULL, 0x000714B5D1CEC6D3ULL, 0xF8AA99A05AC39A48ULL, 
            0x9790F8A618B8E206ULL, 0x381404D5EAC60016ULL, 0x2BE6DFEB91CBC8C0ULL, 0x7F01AB514E71B21AULL, 
            0x5FF99267296A5F15ULL, 0xF91A3A5E342D03EEULL, 0x16CF10F30A38BCB5ULL, 0x64E690F132F61E5BULL, 
            0x761D2FAB0603505EULL, 0xEAC012E994AEFD9EULL, 0xE2E09AC0052D5FD8ULL, 0x64679463D59DB413ULL, 
            0x341D96FCC48E6B4CULL, 0xB065F49A3CCF8887ULL, 0xFC2EB92790777463ULL, 0xC0A17EB6301C89D6ULL, 
            0xECD41B2B29C8EEC6ULL, 0xEABDE1F5831FA7C9ULL, 0x168B047275456C61ULL, 0xD282551A9F79A007ULL, 
            0xB0E3D11A0C3352DBULL, 0x18096AA701097C91ULL, 0x894E7F79481D83BFULL, 0xC1FCB9A06379CCC7ULL, 
            0x80A993B5166D64DCULL, 0x2CDA542A1A23F2B5ULL, 0x9A933A6DD8626326ULL, 0x223F3AAE6AAF27EFULL
        },
        {
            0x79DFC6EBC5D95AA1ULL, 0x67E71EE4E61A8A32ULL, 0x11BFBDD97BB5EC6CULL, 0xEBEEA1D34AE9F32DULL, 
            0x675827E7B3AB7DC0ULL, 0xFBBFA8FD4078B6E0ULL, 0x3983CD7B902DB57AULL, 0x1AFEB069E6919201ULL, 
            0xA2DA02C94FF300A8ULL, 0x4F2D1B0504A44540ULL, 0xA6B5B5CC6D6A3EADULL, 0xA648F4AA34D53C61ULL, 
            0x637E8846D46E18DAULL, 0x6C13A98733046681ULL, 0xBCEB8B2D96DCF36CULL, 0x3AD01B2B714CAAA0ULL, 
            0x8FF909A27BFC80C5ULL, 0xE6FC96E176CB59BAULL, 0x352F9280C6624673ULL, 0x5EF4AFCB90B941A6ULL, 
            0x575FEB9D440D9706ULL, 0x42168131DB142365ULL, 0x08E3534F181E3B89ULL, 0x5127842D0E50C18DULL, 
            0x4579088854A027E6ULL, 0xAB84E7DE11EAE52AULL, 0x24DD2B6B88D0B865ULL, 0xE2556889EA484789ULL, 
            0x4750CBE71F343076ULL, 0xF81CA4698C5269C9ULL, 0x327270DAE628FF6AULL, 0x7F648AFCFBB92540ULL
        }
    },
    {
        {
            0xE8D524443FE84F59ULL, 0x62325B6850A9CAA6ULL, 0x5C05285AAEDD32CFULL, 0x2B32F4E6B6F169C6ULL, 
            0xA7B9DFF9E2FF9F4BULL, 0xA6D72D03E49B408BULL, 0x3E80B3A4E8E4B1D7ULL, 0x209034A6D9979A25ULL, 
            0x9663EA91ACB0884BULL, 0x68B3598CB6041914ULL, 0x967403002DDCD496ULL, 0x9BC071365374DF75ULL, 
            0x8CD9DCE3A853E17BULL, 0x427C7D57255AFBF9ULL, 0x0BBA6C8791B147F9ULL, 0xF4875E7E4641F219ULL, 
            0x18621301C62AEFBAULL, 0x22454A2EC0152893ULL, 0x956DE48AF145FE18ULL, 0x87E0677FDB75A327ULL, 
            0x3581CAEFABDFE7B1ULL, 0x0034016800817E56ULL, 0x568CFF054B3FC623ULL, 0xEF20BF481E6CEC5AULL, 
            0x913CA7C5A8781340ULL, 0x5B82EDB24511EBA7ULL, 0xDAEEB36708292F14ULL, 0x9CE6FCB6D8F83B3CULL, 
            0x3800500B29130C94ULL, 0xDA15C72FE8D9CCAEULL, 0xEADE20E6476781D2ULL, 0x24DC7337D5F86D9DULL
        },
        {
            0x067EA804DB446D1BULL, 0xEA8290F033ECB8D4ULL, 0xB61113021F3797C2ULL, 0x8DBBDB8CA051D184ULL, 
            0xA117CD8689DDA8A4ULL, 0xD276D14F4C05BC30ULL, 0xAD244A2761D9BA42ULL, 0x8DE7ED8ACAE13411ULL, 
            0x748F39B9E38858F0ULL, 0xDE571EAF4126794CULL, 0x3CA9723D283D5F41ULL, 0x4700A0FFF9A91C31ULL, 
            0x9515EBBA877DD628ULL, 0x9249621A8761968DULL, 0x714953A44CE218E5ULL, 0x97049B2DA04E3C7DULL, 
            0x3DDD971A7D3770C9ULL, 0x5E5A39F983F41C10ULL, 0x788D8F7395AD59D8ULL, 0xC994EF830E123D19ULL, 
            0x265B6B95B8DD775FULL, 0xF3FEB16F07079348ULL, 0xB35BE87ABD8E6FF6ULL, 0x3CA25F0548AE57DBULL, 
            0x628EA7A23832F1C1ULL, 0x9FEA92CFEE81B09DULL, 0x59093D38B606E4E7ULL, 0x508E431E34D5758AULL, 
            0x4489D75C26C9A843ULL, 0x7D5B2C30FE12742CULL, 0xF1E5DAC1D5E151A9ULL, 0x8D20FEAA2B73A6D9ULL
        },
        {
            0xDCA0D4DF89858F23ULL, 0x8571CB3002A50D67ULL, 0xD269ABAE7CA00772ULL, 0x7E7603ADCDB957BFULL, 
            0xA58F9F75DF466F14ULL, 0x66340B71D83C1A49ULL, 0x000C2649C1E6161CULL, 0x63C1B6B1BE2A084AULL, 
            0xA850F6F53AD3A383ULL, 0xA4F239514B844263ULL, 0x04337F6CAA8E0AAFULL, 0xEDBCF7B710713A29ULL, 
            0xD23B739EC479D5A5ULL, 0xAE3EF7C70E03D982ULL, 0x69FC54D17BA7E026ULL, 0x27C69C451FEC632BULL, 
            0x31752BD2C77CD886ULL, 0xC6F08E9D431E4598ULL, 0x4556DB6E21C96930ULL, 0xBD38A6DDA87435E3ULL, 
            0xFB44307DDE8978E0ULL, 0x2D1460895AABF770ULL, 0xE0AD3050EE9317ACULL, 0xA071719A8069CDDEULL, 
            0x40BB7163C255831EULL, 0x66EF966F172C6E33ULL, 0x4AF17E5FF2632D65ULL, 0x34892D77BD0D2371ULL, 
            0xEE504FB28919FB23ULL, 0xE459E9D651A4278FULL, 0xBEE721E2797AC0C5ULL, 0x9EA35F62E8C997D3ULL
        },
        {
            0x6D8987EE65C605EBULL, 0x50F17D916ECB6C5DULL, 0xAFD2B69B3488926DULL, 0x42D62489986681FEULL, 
            0xDEBDD40B416FEDD2ULL, 0xB3DAB8CFF2E09FAAULL, 0x2F308436D6D34849ULL, 0xF180716256B53959ULL, 
            0x1E5B11DBF1237A82ULL, 0xCC8A26EC35CA3E0CULL, 0xC07CD14D6CA36802ULL, 0x324C9062FF09AAC2ULL, 
            0xC4E1E08541DBAB87ULL, 0x097430CD3BB17144ULL, 0x31B10B78ADAEDBC1ULL, 0xE4BB612E1C4A8394ULL, 
            0x183936AA2ED95F90ULL, 0xCE84C5BEFCBB3AF1ULL, 0x1356E6C6CCE023EAULL, 0xBF6B58B1714BE2DAULL, 
            0x86DE6B6807A90EA0ULL, 0xFFD85ECAD5DEF3AEULL, 0x456F3B7D667DBA29ULL, 0xDD05431346491FCAULL, 
            0xD8E4C0391BF6F1E9ULL, 0x617AC475B3D6EEF6ULL, 0xB9576E021666B9C5ULL, 0x887FDAD5F8F7421DULL, 
            0x9E7D9E17BD6CCB8AULL, 0x5032502B37DB24DDULL, 0x8408BBB9E96E8BDEULL, 0x3A30E3ED705DF179ULL
        },
        {
            0x91FDBA31F852ABCAULL, 0x50135FC63E70D173ULL, 0x295E45A54C2D6E85ULL, 0x7AAF6F406DC01C59ULL, 
            0x7141133FB18502A8ULL, 0xE8F8F4A375252F59ULL, 0xB8A21B30F1ADEE6AULL, 0xD6E95F3E1B378F3FULL, 
            0x542557849DCBEA01ULL, 0x03180C142FFC4D2DULL, 0xF53D84BE1C967CECULL, 0x7E746851BD156F12ULL, 
            0x6ACE9CB361A2083CULL, 0xD8577D5935BAF876ULL, 0x49DE6CEF5D4FAA54ULL, 0x5FA80A8CC6C31F42ULL, 
            0x9AE4662F74C68149ULL, 0xF404759109E75F4BULL, 0x7714AC02C1D7B6F3ULL, 0xC0161E2CD00E8B8DULL, 
            0x6D8F921EB6B10CDBULL, 0x4BC3C9B41E844CE9ULL, 0xC6F3E551F532812DULL, 0x04FBB00A052ABB51ULL, 
            0x8D6E69C469AF0618ULL, 0x92E3E3F00CC00A3BULL, 0x6BF33D5D42950232ULL, 0xCEEEB7733683D56BULL, 
            0xABA42432E11D5CB5ULL, 0x8A0791B4D91750E2ULL, 0x67E817E0E65C241CULL, 0x6C7425E4F959C574ULL
        },
        {
            0x1CD95FE750081914ULL, 0xAC14D406D183BBD9ULL, 0x8611A33BA3704E7EULL, 0xEEFC7D7A7497A674ULL, 
            0x6C366A5D283DBF0AULL, 0xF8364E952213A5D0ULL, 0x6366C6CF4CA8E385ULL, 0xA92608D588808E92ULL, 
            0x8744CBC7D367737AULL, 0xEB0EC4E868C5B3A7ULL, 0xD80FD3C291DF67B7ULL, 0x56B1230BDA61A11EULL, 
            0x63803C59630053CDULL, 0x8D3DDA122EAFFE5AULL, 0xFB4075EE77C52A36ULL, 0x95D746E3A7ECAFC8ULL, 
            0x819E80FAFB1803F5ULL, 0x76418735C42AB830ULL, 0x691D2263ED7DD52DULL, 0x505C34F8CF1AAF4CULL, 
            0xBC67E3E561EFCB79ULL, 0x355D8DF90BCAF832ULL, 0xB2693E74F68F4984ULL, 0xC7C7661AE504881BULL, 
            0x1C36216EE5BE276BULL, 0xB8825F56DDC160B4ULL, 0x600DF954C3B636D0ULL, 0xEF9BAE2A9E448F77ULL, 
            0xD2441EAF0B179FC2ULL, 0x9E2B0EF4E6746B1DULL, 0xD3D56723D34B69FDULL, 0x9468C2026862B35CULL
        }
    },
    {
        {
            0xD2062513CA3B15A0ULL, 0x62CFBD8B8AFED73FULL, 0xA37D14C1FC8BAC25ULL, 0xBFF3E1A55CF356ACULL, 
            0xA48B5E5E760A0236ULL, 0x51E03D4367765AFBULL, 0x9538ECBC0F3268B0ULL, 0x1B43ED930E56F3ACULL, 
            0xF3C5B80D7748B5B8ULL, 0xF28764B024E6916CULL, 0x020AB496FB7CD7FFULL, 0xF07885F110ED3CCBULL, 
            0x2F1E017C59E1F486ULL, 0xA2BB9B59B9B8C311ULL, 0x7EE216D88C578E4AULL, 0xB515D2A354536F29ULL, 
            0xEDA2D3BF8B8AB08EULL, 0xE24B1F58F7A48A26ULL, 0xACDD90A3FB6F229BULL, 0x221D6DD53EAA843CULL, 
            0x9E4AB413AEA1FB4EULL, 0x13AF3BE3D88DEC37ULL, 0xF214B530DCA7DD32ULL, 0xD82243B7C1F8A803ULL, 
            0x223ABE112247897BULL, 0x9E3DABD9CF18B8C7ULL, 0x2C0E1BA0232E1573ULL, 0x324C283CF15D7342ULL, 
            0x28666E93331EED4DULL, 0x9DAAEB1186B9780DULL, 0xC24E93E774F3E04BULL, 0x19FE21406D21D4C6ULL
        },
        {
            0xBEB4D06EB69ADCC3ULL, 0xC78BE8396B46F9ABULL, 0x549ACA1B2C275B7CULL, 0x6363BCB87D2E8595ULL, 
            0xAA781DF4F704D7D4ULL, 0xB8B0A8DED59ED287ULL, 0x1D1BD892EC6EF905ULL, 0x1FF6E2FFB6FA1B96ULL, 
            0x05FE390573E7B872ULL, 0x7BC90908AA88549CULL, 0x5EAD67004B200BCFULL, 0x1CFFE69381B3A0F2ULL, 
            0xD350DBD064FA6081ULL, 0x0D759BFDD40D1A01ULL, 0x1DEE680737450835ULL, 0x174167278B307EF8ULL, 
            0xBACE111B4D5A39E9ULL, 0x4EF24B567995B5ABULL, 0x9084B7DA6B8B35ABULL, 0xC1C9F3F969571450ULL, 
            0xAABC5B746B5B3CB1ULL, 0xC74D60434B0AD6FBULL, 0x89F0ADB84CAF76A5ULL, 0xD1899EFF11C4413BULL, 
            0x3B671DD730A17623ULL, 0x9A1ED4F9E05F96EEULL, 0xF21110DADBD93B65ULL, 0x4BD2C10DF129CA02ULL, 
            0x67AC75948FE9904EULL, 0x90F0DE1E43BEE6B2ULL, 0x6A8E405846050539ULL, 0x821ABA404A5BB97FULL
        },
        {
            0xC9F5A819DF7CC66BULL, 0x20F8E14B37C7CFE7ULL, 0x9087D094939AB20AULL, 0xFEA4C7D1CC084E20ULL, 
            0xA9D0D4096409EA48ULL, 0x94B636958AF31648ULL, 0x53C46721AF93C185ULL, 0xD3B5B0611AC0DE0EULL, 
            0xB35E948EA85DF9B9ULL, 0xE1086BE0D5DCC771ULL, 0xEFF74918346B3372ULL, 0x7B6E639C2B93EE74ULL, 
            0x3055914B94B709D2ULL, 0xFD81CD1C4AEB5188ULL, 0x3CE0DD49E4B6AD26ULL, 0xCD419909F9FFCB19ULL, 
            0x54BEC0AD6C4089A3ULL, 0x45FB9E34F0C8727DULL, 0xF5DAB66C1206143BULL, 0x6CDE577DFFB69AADULL, 
            0x0FC8FE5EFCFDA6D4ULL, 0x0249B9B0E1013494ULL, 0xCEC32DFE9E1CB461ULL, 0x4165E14ABC9D8EA6ULL, 
            0xAE9D7A5BAB4B6A46ULL, 0x80B4DCE945CD300EULL, 0xF9B850916DB26DF3ULL, 0xB8758E66193024ACULL, 
            0x2B9119A340CEC909ULL, 0xFEC850AB2DEFE288ULL, 0x657FCBDC01A632FCULL, 0xAD2F5A26E3E88EB8ULL
        },
        {
            0x568162C83FCA77BBULL, 0xE0EA16D17A0815C8ULL, 0x9D148FE76AB49D1CULL, 0x5AFA7DBB412D5D13ULL, 
            0x4011ECDB1EC86E34ULL, 0x88DDCBA90096CCB5ULL, 0x7F9F843E88E6C3F9ULL, 0x965D0270102CF062ULL, 
            0x2CFE9AB9B4CE9247ULL, 0x826C949075484810ULL, 0x4D3680FDBB8C6A81ULL, 0xC1F89259A3462871ULL, 
            0xA67F92274297D73CULL, 0xD74050BC3C3A1F03ULL, 0xABB3099495140F70ULL, 0x4C3E1A17107E287BULL, 
            0xBD193FCE507FD6DDULL, 0xFD30E068F2EE590FULL, 0xB53A594F06EE7AFBULL, 0xB21328FD7F7F3DDEULL, 
            0xC20F7005A9129418ULL, 0xA8957C5DC5A6C8B4ULL, 0xD7B2F09B37C501B7ULL, 0xA7C043C350E2B86BULL, 
            0x19BB2A93BEC41391ULL, 0xB3772F33266E623DULL, 0x695B66489A09BDE1ULL, 0x515D4633C8B27657ULL, 
            0xA811C17E5B1CC274ULL, 0xBE50343B99EBE607ULL, 0x6D2F6FE0010379B9ULL, 0xE4149BBC9F64314BULL
        },
        {
            0x1820E60E312A0342ULL, 0xE6D4AEFB990BE230ULL, 0x506C86FE2A756D21ULL, 0x24FE0C35C8E7327FULL, 
            0x4D8A87BDD0B3D9AFULL, 0x228063444B7D587CULL, 0x9AD1DB4628AFA83DULL, 0x4AB296FB5A1330CEULL, 
            0xC77B31C6CACB1972ULL, 0x936BDCF8DCA56936ULL, 0x6D384C52E5771D65ULL, 0x89543157CA449F01ULL, 
            0xA45554D454782E96ULL, 0x3E1F07E96FB38D35ULL, 0x7FC9787F4AC0BC36ULL, 0xDDE243940860652DULL, 
            0x1E5EF356903F3D38ULL, 0x3EDB313AFA327E21ULL, 0x6F07EE9A8CD34DB4ULL, 0xD3B7FA0C830816DBULL, 
            0xCECA4EC0C3D91D67ULL, 0xBFCEC0F2BBBE278DULL, 0x5C6C9CA41B7BBE88ULL, 0x71AE4D69069AED38ULL, 
            0x21EC376647F873E4ULL, 0x4ADE96418DD9E804ULL, 0xB2EE80A3F0322248ULL, 0x04C9E688006E0B57ULL, 
            0xA53674AC3E3F79EDULL, 0x4164FBF6162F94ABULL, 0x6C3782BB24D3D3E6ULL, 0x850D82E219682F90ULL
        },
        {
            0x56BD2D11EDF08EBFULL, 0x89999BBEA181F982ULL, 0x497BC3F7AD347C80ULL, 0x64D88F9921638773ULL, 
            0xBBA1EAF8347F5B61ULL, 0xE803ECF61FDF382FULL, 0x6AA1121666B90A76ULL, 0x737AC1844BDA3947ULL, 
            0xD15161DCD7DF0901ULL, 0x7DBB880CE9523752ULL, 0x0BDD587982A67CFEULL, 0x5B710851105C335EULL, 
            0xB9EB967A2FCF0EB6ULL, 0x6D817FE14366C654ULL, 0x9FC0BA8E15BBA08CULL, 0x0E427564A865EAD4ULL, 
            0x361F5AD6FA49FC2BULL, 0x21D552438032270FULL, 0x6B436EC55298D3B2ULL, 0x92D6E3E0DDB7A0EBULL, 
            0xE8B7FD3084064EE4ULL, 0x9CE41D0A7DA78E2EULL, 0xC43B1D50E4281F30ULL, 0x340D3AE45F418356ULL, 
            0x4B29ABBC4C62C306ULL, 0x027B7364FEEA9310ULL, 0x0E495695DDE4B310ULL, 0xBDE17D7A343BD159ULL, 
            0xC3B625A57D75CC5DULL, 0xC1DB0397C820AB5FULL, 0xCBE3E08ABD06A8B7ULL, 0x704C0B01706A9B07ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseCConstants = {
    0xBB035B0752728638ULL,
    0x3DD1F522FDD3B5E1ULL,
    0x4E6034DA82D256C1ULL,
    0xBB035B0752728638ULL,
    0x3DD1F522FDD3B5E1ULL,
    0x4E6034DA82D256C1ULL,
    0x5BF571154E92754CULL,
    0xE23CC7FF5ED4F399ULL,
    0x28,
    0x38,
    0x25,
    0xF9,
    0x8C,
    0x31,
    0xA0,
    0xD3
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseDSalts = {
    {
        {
            0x668A66B740842E52ULL, 0x11B73A605675F36DULL, 0xFEBE5A99539018A5ULL, 0x98DF0FA334B49D00ULL, 
            0xAF807584BDD95157ULL, 0xF9B54445AACD18A1ULL, 0x4DDA24AEDF5C3A2AULL, 0x02D803A5C38FB17BULL, 
            0x21CAEA128081357FULL, 0x8E5C040FC053269EULL, 0xA1752C1C9F7EAA2DULL, 0xC109639EA870AFAEULL, 
            0x311652E9823E489EULL, 0x21746EDBFECC496CULL, 0xB0A6841550C8106DULL, 0xD25BF9F23C57EF34ULL, 
            0x020C24788FA08C40ULL, 0xFE049447EEEEBC73ULL, 0xB38B2FC0CE59E51AULL, 0x4D724049F29C621DULL, 
            0xB9F376211297D84AULL, 0xBEAB282009F6A8A7ULL, 0x39022765B7090DFFULL, 0x9BAC35E4B6C03079ULL, 
            0xCFB466B7241D3211ULL, 0x27D79A16EAFB8F11ULL, 0x2292DBF91A176B5BULL, 0x2FD7A179C7E277F2ULL, 
            0x1F2B1E9E586F1C34ULL, 0x25127BDE4A987258ULL, 0x5E4DE843EA021F69ULL, 0x03B0BEC2D11F66C5ULL
        },
        {
            0x7972C2C6B46D1C1DULL, 0x7D8673FBF8CCE72BULL, 0xC6EE9B1071EF6CA2ULL, 0xE9539B86F43980CCULL, 
            0xB6CDD2CA527BF4A4ULL, 0x325B3086714F318FULL, 0x8662A7E41475B2BAULL, 0x92E7562CFDBF32A2ULL, 
            0x563D43BD4098FBC3ULL, 0xAAF8091360AACA9FULL, 0xB0211293D62C531FULL, 0x508595F9E15DFF22ULL, 
            0xDC1B3FCED760D9FDULL, 0x841DCC81093981CCULL, 0x73F67178B37DBB96ULL, 0xA158EA9C5CCE2293ULL, 
            0x637FACE34EEA7BA1ULL, 0x7209796B2B569ECEULL, 0x3C24E4D1D9A30544ULL, 0xA09C6FF7E08DFAFCULL, 
            0x75D8E8A8998FD421ULL, 0xB00CCD2C0FA8FDA3ULL, 0x1F7BC2195B568F4EULL, 0x447E6B6A05E50144ULL, 
            0xD366B430D8C5CE61ULL, 0x6AB4EBA6EDEC9E52ULL, 0x709ED6F32F09B387ULL, 0x1976E84AFE6D111FULL, 
            0xE73CD0B7BCF3E54DULL, 0xB513E90F3EAEC064ULL, 0x2D6FB9B6EDC08FD0ULL, 0x079032CC61DE47F0ULL
        },
        {
            0xF0959552E82CECC5ULL, 0xF4B74589172760A6ULL, 0x523743ECD41BE209ULL, 0x662FE6FF3502C478ULL, 
            0x57EAC69660B6BC76ULL, 0xDFE63CEA15ADA31AULL, 0xA15416A95D008DF6ULL, 0x7D08E358393F2228ULL, 
            0x99CD5347D9AA852FULL, 0x397B07141CEB58C7ULL, 0xFCCEC2A863705959ULL, 0xA12E87E30A9E020CULL, 
            0xE79EA2F52B28CF73ULL, 0xF98F8B60E125BDB5ULL, 0x88E84640CB82142AULL, 0xEA6DED8BBEE18633ULL, 
            0x00D39EE5C2BE1AC7ULL, 0x95336DD2B378B9F2ULL, 0x4DD0B8D91F0ABBF7ULL, 0xF7007A72134D1566ULL, 
            0xA1A99EA9F8A894CFULL, 0x6158A3D801CB0134ULL, 0xB8642770AD30F81BULL, 0x5EC3588781C14E7EULL, 
            0x83A49004B0907A1AULL, 0xDBFD6CDF58BF5527ULL, 0x6FE68680051009D5ULL, 0xDAFBD157D974D556ULL, 
            0x95A373F9FAC7F85BULL, 0xA53F0AE1998CE6EFULL, 0xA304174558E9EAEDULL, 0x12D36F78049976AEULL
        },
        {
            0x56F2812383F3937DULL, 0x56D61A6E8A0E9DE6ULL, 0xCB09B06B664A4D19ULL, 0xBF4923FB9A0083F0ULL, 
            0xA505805319725FC8ULL, 0x1DD690519BAEF4ADULL, 0x72DD4E2D3FE0C0F7ULL, 0xB0F6E4379D15D475ULL, 
            0x2D836097A144B076ULL, 0x8EC5C13ADD75B3FEULL, 0xE070169AC61F9BC4ULL, 0x0CA1D65114AF046DULL, 
            0x05E82DCA5CCF76A0ULL, 0x61EA812AFC3CDA0FULL, 0xE557EDA09A6B9F10ULL, 0x2DCF947FFBD9AB38ULL, 
            0x88FD86EBAA7C734AULL, 0x29DA228099D8539BULL, 0xF0F6E22DBA1C4F4CULL, 0xBD3BDD2172DA88ADULL, 
            0x73DB32147FE8D348ULL, 0x1549B997BD7A630AULL, 0x9C39C3FDFD5F2AD2ULL, 0xCC5ADB07EBF4FC46ULL, 
            0xFA5B40AE1CC59E22ULL, 0x9F96EBA07ED9E73AULL, 0x8CF2B069D3B89310ULL, 0xEB3D72F7AA58EA02ULL, 
            0x76E4397EF0E18477ULL, 0xFDDB9C9A111C1B64ULL, 0x9FA0B3538C6B314EULL, 0x771436CFBDB79CF3ULL
        },
        {
            0x0B5B824A696A99F1ULL, 0x79A12D5DD6800F77ULL, 0x4FDE1A3F3C8BF83CULL, 0x4BD3CA5DD9BD88F2ULL, 
            0x4E675AEBB47E449CULL, 0xE2797BC32C1D79D5ULL, 0xABB9BECE68EE4D07ULL, 0x8F15032DB404C7D0ULL, 
            0xA1E181A3A4B66DF6ULL, 0x57AB4E06857EB11CULL, 0x96D70D6392578CD6ULL, 0xB34778033273E0C9ULL, 
            0x2F92C4B9F19B81A2ULL, 0x1FF56EADAB43BF37ULL, 0xCB59D7B48B489503ULL, 0xCDF59887FD39A08DULL, 
            0x3B385B135F7815B1ULL, 0xF8BD09ABFB6FFF30ULL, 0xE53D9BC0757D9CDCULL, 0x2B93764379CA8E67ULL, 
            0x264527E3B8615F08ULL, 0x0987D492D2A896B5ULL, 0x213B236B49EB8F9EULL, 0x187E7913EDCE07CBULL, 
            0x4961A9BCC900FEDAULL, 0xAB5FDA96F28A6EEEULL, 0x0BE54A9FCE345BACULL, 0xA17DE23B56D0666EULL, 
            0x965B2ADC362C8D10ULL, 0x50D097CDD1BE3179ULL, 0x3FB9D5F4B9E66690ULL, 0x07764C2A7C3BA47CULL
        },
        {
            0x0E1184FA343127FAULL, 0xD25872C284BE63F1ULL, 0x1D8530D6CD9B79EBULL, 0x3511B786EBE188F4ULL, 
            0x3A062210CD2E1A32ULL, 0xDB8603D172B3BFBFULL, 0x8AFE6B8621821CF9ULL, 0xA82CC7142F43EB95ULL, 
            0xF219126A910DCB6BULL, 0x5B43A55F72F933A7ULL, 0x4AE673DFBD4E59BDULL, 0xDEF742FDF2DACDA6ULL, 
            0x4599967BA0F63CA9ULL, 0xBA03B9CEF6DFB3E4ULL, 0x58840C7B6E795DB1ULL, 0x4B48C89EC6717780ULL, 
            0x501C7CF49FB8083DULL, 0xE27783F429B908D3ULL, 0x41A9FC5CDD746146ULL, 0x96B12C357D74FBFBULL, 
            0x750394C4F9915DF2ULL, 0x31C931661D7BD474ULL, 0xF67F47A619C34B92ULL, 0x94249522B2CD1E3BULL, 
            0xE1F97578AC96FEF3ULL, 0xCBD0C78707126BE1ULL, 0x4B0C471898059693ULL, 0x405509977D373A2FULL, 
            0x66ABD5D6598F8ED5ULL, 0x6B15AA19664D4EEDULL, 0x99919116AC7DB2FFULL, 0xDBC845AE236034B8ULL
        }
    },
    {
        {
            0xFA0724013E8A7F6FULL, 0x6033A69DBEB5AE8DULL, 0x71A452EAB2EE3553ULL, 0xB0D2BFA884A45FFEULL, 
            0x5F7F3569F96FC1BDULL, 0x557626E8262055B7ULL, 0xD49DD5CC184E96D1ULL, 0x77034C6A0213506BULL, 
            0x468127DC8AF23072ULL, 0xC611B9A60AED1055ULL, 0x35D154B0ED936C1AULL, 0xDF8CC7B1170A2565ULL, 
            0x92D5BE58DD70DB06ULL, 0x9EE10EA8C57E90F4ULL, 0xCCE9A78A5FC9F833ULL, 0x36EE2718C5AAF278ULL, 
            0xD644E85735ED1824ULL, 0x509659F550685DDBULL, 0x91286B520B0C0E9DULL, 0x03AA2C95C18158E3ULL, 
            0x8DCCD8BBB5B7FBEFULL, 0xE5724A82AA52CDDDULL, 0x7D986DA819E44FA2ULL, 0x75E39EA784BE6142ULL, 
            0xFD5BE8FD9BE6DDA0ULL, 0x4D64BCB588BCA674ULL, 0xE9C19BCED41795FFULL, 0x15AA464B682840D0ULL, 
            0x6C75E9B7F12186F8ULL, 0x259B2F8015081E67ULL, 0x2AA79B0DCDF25A09ULL, 0x2679954C1EA3D248ULL
        },
        {
            0x5C34E1034D7D2BA8ULL, 0x173AA056967CB664ULL, 0xF9A6D8F0AC5DEE08ULL, 0x0B2A917719421238ULL, 
            0x1A9055A91B465A84ULL, 0x9B0CA47573C3754AULL, 0x5440EB96238420ECULL, 0xD07275C465356B4CULL, 
            0x2166A21B4973E01CULL, 0xDCA5DE9640641ED5ULL, 0xB328A76A5862B861ULL, 0x5115AF6303FDBFB6ULL, 
            0xFF7DF8D11967E94DULL, 0x33A2A400D5B7DD38ULL, 0x32F7536F757D0506ULL, 0x919CDECA84AD523EULL, 
            0xEF93B1D7496EEA8DULL, 0x06D1D9B673C5985BULL, 0xEE5DEA5E0EB9504CULL, 0xB0B4BB6706FBA9C2ULL, 
            0x02C56974204D2336ULL, 0xBDC05B14890F0633ULL, 0x60FBA28673C88D5DULL, 0x05E69A0145A6D700ULL, 
            0xF8522487535D38B7ULL, 0xC28D0157B2130881ULL, 0x44CD1C4FEA059531ULL, 0x354F0A5F307C12B8ULL, 
            0x9055FB3EDF719455ULL, 0x2DD74DD64C5AC600ULL, 0x615F4639C8581F5CULL, 0xE0724B04DAF6440DULL
        },
        {
            0x0ACA7CB7705F3B37ULL, 0x7399810E9650527BULL, 0x517D364780E8291BULL, 0x34FC5DDFAE3B903AULL, 
            0x7D44B00D32C80AF6ULL, 0xB6778481F7686E5AULL, 0x95234BB8EA4DFC69ULL, 0xCBFAAE72F498ED0EULL, 
            0xD2B8C8E93DF5BD22ULL, 0x9670949D40F498B6ULL, 0xED83BC3F384AB675ULL, 0x3EAC8A3A776BF18BULL, 
            0x767838FA458F6439ULL, 0xF60207677D429585ULL, 0xFC98091A7568B01BULL, 0xC844F33D088C10D4ULL, 
            0xBFB5C82E28945DD4ULL, 0x61C6DEA4B929FED8ULL, 0xACCDAD7B36D15F7DULL, 0xFB9C3CDB5008D140ULL, 
            0x1B7E603A1BEEB560ULL, 0x1322D9B3E0B1BCF7ULL, 0xD10ABD98D42C1C2AULL, 0xB56B00BC8EBA1D7FULL, 
            0x26B80E1DEFDC26F2ULL, 0x358B893A7F3FBC14ULL, 0xD3BF947D6F722032ULL, 0x68E60341C70EF27CULL, 
            0x61F5ED96C0ECBACBULL, 0xFCB290B5D49484C2ULL, 0xCF32889B3C3C0C80ULL, 0x165F48C8B6F58F15ULL
        },
        {
            0x4DBBE14927573E5DULL, 0x4FA50064BAD7E088ULL, 0x6310AABF0ACD308FULL, 0x68DC768470754740ULL, 
            0xDD3E160FC6771317ULL, 0xDD6C9AFC395FD7DAULL, 0x1400DC41F52C149AULL, 0xD4E6E0E0011EB68FULL, 
            0xAA773A27EE3A1E6FULL, 0xD7F9BFD19CBF6AEAULL, 0x7D569365C2AC940BULL, 0xFD15F4ACE2ED29F5ULL, 
            0xC9BD3DA7E55F4937ULL, 0x06910BABE07FBB3BULL, 0x12607A24274E2A63ULL, 0xF90CF1859247C2F7ULL, 
            0x3D79D58D969F62FCULL, 0xB0CDBC403C0176A0ULL, 0xEC29683E716FA042ULL, 0xF5AD57FEC0D3B7BAULL, 
            0x8032B0475AAB7173ULL, 0x7AA357FBB0937E33ULL, 0xEE452E4ED9D2A3ACULL, 0x07DDC0F30F848B35ULL, 
            0x86C8D86948ADFA40ULL, 0xBDA3EDECE992144DULL, 0x33F4F03035ACB360ULL, 0x6400BF6A5D701E79ULL, 
            0xCB01E6CE9A77F0E8ULL, 0x08AF62F69C52125DULL, 0xCC5F0C8566165A9FULL, 0x2E46A4C77FF7A673ULL
        },
        {
            0xCD6A0B065BD84E4DULL, 0x82B3A2E4028B255AULL, 0x886965D66C057608ULL, 0x74FB0816F12FC883ULL, 
            0x1EBF8C8604C3A038ULL, 0xCB6FB0D5349BB243ULL, 0x7BBBE1F142D65339ULL, 0x273E610754761E71ULL, 
            0xDD61DA90C5C49840ULL, 0xA28616564E0220A6ULL, 0x8B3000EDB9811A24ULL, 0x2E8BA18A43112E11ULL, 
            0xAB05A70797A977E9ULL, 0x0BBDE78AD16676BBULL, 0x1428C9A93E5687F7ULL, 0x929C73E66234EF72ULL, 
            0x0BF12DD7F1FE6312ULL, 0x759645FE68DCE638ULL, 0x8484CD106B4F1E5CULL, 0xC5EB934FF8CFD83BULL, 
            0xFB55CD6416BB3E2FULL, 0x40E12852978605C7ULL, 0xD8C7479B92402E90ULL, 0x5663AFF15704E5DCULL, 
            0xA990E57FABCEECFBULL, 0xDBF20D1DD01DDD9FULL, 0x8A95D06C82FA35ABULL, 0x4E33E7E4D61F083DULL, 
            0xBC2D206EC92906A5ULL, 0x24A497825D50E7A2ULL, 0xE3AC424DB6940586ULL, 0xF9546002C9B62914ULL
        },
        {
            0x8AC4A8CC40D2C5ECULL, 0x0F519B6DFC682261ULL, 0x4B06736D2BAF8174ULL, 0x192A0051C27FA4ADULL, 
            0x457692FCFCEE1C2EULL, 0xF0B390F50BE6D383ULL, 0x8B761099EEEA62FDULL, 0x6EDD63A27E1982E8ULL, 
            0xB38B21CB37AA08CEULL, 0x4467122644FF3DA7ULL, 0xE2C947F8B4E6B21BULL, 0xDBA030A90958D4CAULL, 
            0x89805943D0183A7FULL, 0x604CEA75E49A6885ULL, 0x4AC82632BDDB8EE9ULL, 0xE099C662B019B490ULL, 
            0xC5148A45CBC9F2A4ULL, 0xF92FB7BE5D2297C3ULL, 0xF673FA484A182810ULL, 0x3FC3FFAA6A66D1B6ULL, 
            0xFA6B029A040CE894ULL, 0x30B61E469CD54ADDULL, 0xFA9A9628FB5E0C6CULL, 0xD3D995D158039948ULL, 
            0xA227BE75F4FA42F0ULL, 0xAF8E6F295220BD8FULL, 0x693D572B71A611B3ULL, 0xA2DB3D7E413414B2ULL, 
            0x113AA95D4B9D7C63ULL, 0x58E007E9CC3CFD01ULL, 0x4EB9CA1F502D38FEULL, 0x5BA8DC93EC793667ULL
        }
    },
    {
        {
            0x24D8E3815BBAA06BULL, 0xAF55334F9FD2A94EULL, 0x836131E5EE6DCCB1ULL, 0x47C8A35375EA9EACULL, 
            0xC953B0F2DF0109C0ULL, 0x29A0261106912B7EULL, 0x900479CD1C0E8666ULL, 0xC5E70706266E3E45ULL, 
            0x2C27F64F0A39843CULL, 0xF26F122B3BEFBDC9ULL, 0xF78F1B5DBDFA84DDULL, 0x8E6EFFD9B34BBEC8ULL, 
            0x62B76587E576A914ULL, 0xF13768461DD872B0ULL, 0x6DBE5EB7B0D3D15DULL, 0x1F72D0A21406F487ULL, 
            0xEB1367DD1FC21524ULL, 0x3049DBE7FBF69E6AULL, 0x8087D8D54684858AULL, 0xDADC9A7BA4354A81ULL, 
            0x1903B227B638F9F4ULL, 0x3815FF30453617E5ULL, 0xCC1A25AC28B28C49ULL, 0x82807E3EECDFA4A2ULL, 
            0xADED245C6260C3EDULL, 0xF178373C9A1B04DCULL, 0x632835B52477B4CBULL, 0x17D4DDD5C43E0B35ULL, 
            0xA8A0CE5481182261ULL, 0xA30279D1E7D5671BULL, 0xEC04E23743DED164ULL, 0x7DF74663E8BA7D60ULL
        },
        {
            0x6C5479030B7A0EBBULL, 0xA076AC7AC71F9CD5ULL, 0x63CDF7ED674C8DFEULL, 0x30F5F0E1F1084FF8ULL, 
            0x6CAE47FAB3A75ABEULL, 0x0FC8CA525675E4A7ULL, 0xF751A503E4D7B996ULL, 0x34538F023551C38DULL, 
            0xE44F61F6198C9EEDULL, 0x2B4ABAC9F371658DULL, 0x9212BB03463E5B66ULL, 0x0CFBB6DA40F45CF4ULL, 
            0x1770426C1B30C299ULL, 0x086860FC28BDCE82ULL, 0xFA2A8D4F44871430ULL, 0x37330C85D5941F6EULL, 
            0xA0C5E2E0A8A02770ULL, 0x02870B988A3C2DE7ULL, 0xFD4A8CEE7A8F8D87ULL, 0xFCCAA9B0CAC0700CULL, 
            0x199A0EEFC09F19C8ULL, 0x042D5DD6191644E9ULL, 0x78F26B7329C5BB4CULL, 0xF1D0BC69734994FAULL, 
            0xCFF2F6B29AFFA25CULL, 0x0CD5EE06D9962F9FULL, 0x3B19E51C96CFC228ULL, 0x6BAFED9C68924E16ULL, 
            0x944B8BBEA7985A69ULL, 0x8E87A49495B1FB4EULL, 0xB7F05411CC0A5227ULL, 0xE79CCDF6C0F2F608ULL
        },
        {
            0xA4D6AFB55BB02791ULL, 0x44C3779231AE1892ULL, 0x3D6AD9E9A1DB5D71ULL, 0xE0727C3425FD5156ULL, 
            0x1DCDB9E3596A1488ULL, 0xC060A5E538EC40C7ULL, 0x27E2D444F75499AFULL, 0x90E75BF327726E90ULL, 
            0x71462D5FFF36FFAAULL, 0xF42936F7D3E2C602ULL, 0xFCE3933704C55668ULL, 0x64460910DC2E795AULL, 
            0x19D3D81465C73B9EULL, 0x02E96EF51C65E43DULL, 0x115EE8A5D970ADE4ULL, 0xA6F45BBA323F689CULL, 
            0x8A4C726A60BC045AULL, 0x0B59AA3EBE0FD43AULL, 0xAE33C6F218503977ULL, 0xCD7C0E4387B2FACCULL, 
            0xAB7FCAE848C5C2EEULL, 0x8D53744D1DECD0DEULL, 0x29DB56B864B5F56EULL, 0x3076F5E2202FA640ULL, 
            0xB85E0F8F67D60CB6ULL, 0xB2F687946031B90AULL, 0x0EF53D695F50B41FULL, 0xEA618B04292BA1E9ULL, 
            0x56AF31DEDF1B2650ULL, 0xC445CB350632D60BULL, 0x4F1103ADAE259780ULL, 0xA0F994E3CED3EAD8ULL
        },
        {
            0x84BD5F566CAF178AULL, 0x15760EA30D7E61C0ULL, 0xE3289BBA2F9B4F7DULL, 0xC3A11F2E62332BB6ULL, 
            0xB48C532798A9DCD2ULL, 0x11C01E1C8B365260ULL, 0x342551B83274BF70ULL, 0xE1324C52655F99FEULL, 
            0xD43B93742A7B5A04ULL, 0xEEEF46BBA529A16CULL, 0x434A58598F05F588ULL, 0x1A52AEE70D5EFF55ULL, 
            0x36E6C8066F5972D5ULL, 0x9B0098048CA5BD2CULL, 0xA77A84CF305CEFC8ULL, 0xC2FCABEE5C37D157ULL, 
            0xE43B34B70FD10BBDULL, 0x083F8B8CF039E8B6ULL, 0x20488C6542007735ULL, 0xA9725E3EE42EC2AAULL, 
            0xD1130BC086EE4286ULL, 0x0C12B5F51B2B44D4ULL, 0x6BDEC56AFF5D7FF8ULL, 0x39CDBAB445CA56FAULL, 
            0x8A3666DB71CC34BFULL, 0x42EEC73D90F547E7ULL, 0x00F7B87A5BF64362ULL, 0x94DD7F2C532D3700ULL, 
            0xCD8BFE59FECAC11AULL, 0xB49348E522378812ULL, 0xDC17F76154F9F063ULL, 0x12E816CC1AB51A30ULL
        },
        {
            0x664A825178317418ULL, 0x43C644A451A44F78ULL, 0x771725D741D29B1DULL, 0xFD4276E16A8AD949ULL, 
            0x07964C21EEAE6934ULL, 0x122FD7EE9E397C2CULL, 0x1B55827627C50EAAULL, 0x913C003CDFB05466ULL, 
            0xAE155EBEF238DC4DULL, 0xB73EBE1F34EF3A26ULL, 0x2D213C2AF38E9EA3ULL, 0x71FB4BA5FDFE11DEULL, 
            0x975EA1BB358F6E01ULL, 0xA180167846398618ULL, 0xADB3B17C9AD89A5FULL, 0x684C64B033AB8DB0ULL, 
            0x73A1C91D02B2024AULL, 0x414244E3468CF39CULL, 0x9E755EFEABB60527ULL, 0xAD6F64C362E86A5AULL, 
            0x8C1985CBCC45BECFULL, 0x6A2466EA4B7D14DAULL, 0x50AFE504B53E5778ULL, 0xF514B599157C3D4CULL, 
            0x60604A547CDB4353ULL, 0x70E90E719D0DC307ULL, 0x2A2AD32B6FC10055ULL, 0xD2E061EFFDC8524EULL, 
            0x05FB34028F016CC7ULL, 0xBB5A52D306771116ULL, 0x0C913E6DE3C67EC7ULL, 0x4CFDEBA12E5D64C8ULL
        },
        {
            0xF55C574D629D1555ULL, 0x0E6BDC7982581AE2ULL, 0xF3E786DC852A114DULL, 0xE8FBABD57373CC21ULL, 
            0xB91C73A53B0D96ADULL, 0x9669DBAD5B5636D7ULL, 0x10CC6216093C79F4ULL, 0x8A1F5E16672E88A8ULL, 
            0x4C5D78E8274E6D03ULL, 0x50914316D1500A90ULL, 0xB89733693F726B5EULL, 0x33083852F36F25D6ULL, 
            0x2E1BE8E5DBED805BULL, 0x3F448F08E05D9B9DULL, 0x7A4BEFFD42657CF2ULL, 0x9D452B861090EBBAULL, 
            0x80CEDC8F57972331ULL, 0x63FB3608C3866FA1ULL, 0xEBA77FE03CB707D2ULL, 0x324FE7638EC936B1ULL, 
            0x15794AD2798CAD09ULL, 0x99E88FEF0F973F94ULL, 0x8210E24EF54E7F2EULL, 0x32F4EF34EB680FFCULL, 
            0x972C224309D26F79ULL, 0x44E3B756B238C493ULL, 0x8FAF73FAFA7E603FULL, 0xAC9D4DD464FDB0E6ULL, 
            0xFD79D8C44C149510ULL, 0xD29139FC694615C4ULL, 0xFD9178E32BDA5535ULL, 0xEFBD25C581FD0A25ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseDConstants = {
    0x3CD973D9C9B106AEULL,
    0x4FD59271EC4A8C44ULL,
    0xC543617CD9B52407ULL,
    0x3CD973D9C9B106AEULL,
    0x4FD59271EC4A8C44ULL,
    0xC543617CD9B52407ULL,
    0x912523E50F770E2CULL,
    0xDABB2C456338C2AFULL,
    0x70,
    0x7A,
    0x13,
    0x39,
    0x88,
    0xE2,
    0x98,
    0x8B
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseESalts = {
    {
        {
            0x0A5315AFA4815CB1ULL, 0xE56092BC0929BCD7ULL, 0xB753442E532CF1A6ULL, 0x16122EC10A28296EULL, 
            0x0CF0E240AAE114A3ULL, 0x6BF1811F8E36CB5DULL, 0x084054E2D8D20B16ULL, 0xECCB7A4E70AC3F39ULL, 
            0x868701A2F443723FULL, 0xD98E93A8C863D8C0ULL, 0xC3A06E9E75C8760FULL, 0x7BADBCF7C25E1BE4ULL, 
            0xDE27CE8950F187BEULL, 0x0F21F1775808E11DULL, 0x88D49CB1595DB60EULL, 0x9D450D42232A68E9ULL, 
            0x274764D28AFC65E5ULL, 0x8241335BD12EEBB4ULL, 0xC85AC8E2A71AFD5BULL, 0xE72EA5B4E86B9EE7ULL, 
            0xDA9CDACA7E251009ULL, 0x0584AD5F22957AD9ULL, 0xB61E9DC2663B0D4BULL, 0xD29DD8A4CF8D2B36ULL, 
            0xFA2C6C9FF48606E3ULL, 0xB9245FED53BDA35AULL, 0x49AA2D444132DE1CULL, 0xCFF20C3C7D9BFB90ULL, 
            0xB7F4C4632B1AE8AEULL, 0xF91B6BD583F182FAULL, 0x4AEE3966BAA0EB3CULL, 0x57700FDC13C6CC5FULL
        },
        {
            0x8000EF441285D243ULL, 0x21DF1CD7E02DAEDCULL, 0xB28ED771895178E2ULL, 0x93A995FB6C981EAFULL, 
            0xC23CD63A5ADD18E4ULL, 0xE370E9C57418A96DULL, 0xC0760E544DB5E450ULL, 0xBBC452933432B5EDULL, 
            0xBB2879B281AC51DAULL, 0x255A336222512CA2ULL, 0xE6F2BDC9C5CEA850ULL, 0x89B7B3670EB823F8ULL, 
            0xF73B1CC7DAA3D2C1ULL, 0xB0D92DD3A9D8FB46ULL, 0x3452BB881EAD5FBDULL, 0x72135A7A41DC8B3EULL, 
            0x90F3C6C8AA91D95EULL, 0x055F70F45653B8BCULL, 0xD6C35B72B017585EULL, 0x1B794E29271EC388ULL, 
            0xF7A7E144D5EB2C02ULL, 0xE682525CCE80AEAAULL, 0x54055BBA4BA2EE8CULL, 0x2C64F9EE3AB062ABULL, 
            0xB6689D2F51F1E264ULL, 0x0727BFD909403DCEULL, 0x4AD7EC6ED4BD1688ULL, 0x7B46B083085625BCULL, 
            0x785C2842BA9AA5DDULL, 0x676F1A98645345BBULL, 0x5E4721569FFE104CULL, 0x5F42328CCF120924ULL
        },
        {
            0xB8CA3438457AD207ULL, 0x14FD2527CCF47EC4ULL, 0xB78395D9ED1E779EULL, 0x4CEB6ECA58DF16C7ULL, 
            0xD7535042D362B872ULL, 0xB71EAF26560DA5E6ULL, 0x93F5A0820F5C8FC7ULL, 0x328B226B0504F076ULL, 
            0xD95B5707833A0C44ULL, 0x6BBB894E2CB28805ULL, 0x4D05BABF1AA66FF7ULL, 0x217C97EA4AACBC56ULL, 
            0x4B36C5579E66BC7DULL, 0xC13D5CD420311D03ULL, 0x150914909BAE69B6ULL, 0x879E0320060BE172ULL, 
            0x363E1FF9A2197E1CULL, 0x2B77CF7A20684FE3ULL, 0x3ACBB976CDED4A3AULL, 0xAC1EBD3DE434DFC5ULL, 
            0xC6470D13B9C0E9B4ULL, 0xA8D8C0019C57C11BULL, 0x1D6FFEBCB9919CB4ULL, 0x0642ED949E280370ULL, 
            0x8CDE770944560A31ULL, 0xDC76B69766933F11ULL, 0x510F736B9ED952EBULL, 0x959446A924698EDDULL, 
            0xF0066BB60F0ED833ULL, 0x47F3A20947CA6734ULL, 0xE7B0B114822D3726ULL, 0x6C941A66C5AF2D5EULL
        },
        {
            0x51BC8156E7DB6F18ULL, 0xCE617701C6409D7EULL, 0xE1AD24C116601AE4ULL, 0x1985EA5E7E4B6CFEULL, 
            0xD2A034D7E8293D74ULL, 0xE5B3DA0CCBA80643ULL, 0x00C11630DC312BDBULL, 0xACDB7254305A1B6DULL, 
            0xD6BCD64AC640DDBBULL, 0x72058CD68FBC0748ULL, 0x10E0BFCC260B5581ULL, 0x068484778A99D9D2ULL, 
            0x57339AC8C36847B0ULL, 0x8C2544EDAE23B209ULL, 0x90C0939F89177876ULL, 0x227DACB15AC8D920ULL, 
            0x8C2280F0466908F0ULL, 0xCDF7BA6F4CC4B24AULL, 0x08D53E548CDC39CCULL, 0xF2BB8972CC5BFFBAULL, 
            0x31A84E709050A4EDULL, 0x6C692E49D7FEA011ULL, 0xA568A87B935726A3ULL, 0x8750A9DA3421A528ULL, 
            0xA63CCD8BB9F18BBBULL, 0x43F816638E12E787ULL, 0x1A46FF96373009D2ULL, 0xBD9C3993F80110A5ULL, 
            0x2BA4B2E1D34BC396ULL, 0x9741B65527F675A0ULL, 0x0A7899C5DE6BB7EDULL, 0x441EA7EE7AA332E4ULL
        },
        {
            0x27B6DE3389BF7D44ULL, 0xCDBD4E85EC9334EBULL, 0xF61B812048AB686DULL, 0x8A24E00A0B9A182DULL, 
            0x2A9CE3D32FA4D3CDULL, 0x0509855CAFDF3C29ULL, 0x384A38020DFCA8BEULL, 0x6CF1D6E4336EA501ULL, 
            0x71844068DABBA33FULL, 0xCB6D28C6152E4872ULL, 0x521ED789FF062863ULL, 0x9EF5C831E9E8A1A7ULL, 
            0x09F1D53DA53A1056ULL, 0xA86CD1F3A89E2E12ULL, 0x96A2C8B83D8C4838ULL, 0xE1FF53108D7D78EFULL, 
            0x60068E57F584CD29ULL, 0x021CB5300996E52FULL, 0xB1CD7059050CDCCCULL, 0x200D926E84605D6FULL, 
            0x76DF80D791364835ULL, 0x08DA3BC33B99B0F5ULL, 0x3DC53B4F8EBCB7BFULL, 0x6DC783210801A5E9ULL, 
            0x9B39DF1F21D73341ULL, 0xCAAACDF1172119ADULL, 0x65597233BDAB51E9ULL, 0x78E1CA450F28C851ULL, 
            0x5B3B28F14911C78EULL, 0x63E34C7D01E9637AULL, 0xC85C0A02799C53ACULL, 0x7F7345700E47BF2EULL
        },
        {
            0x64DDC3E77B9F917BULL, 0x79230B87B0A2B7D2ULL, 0x7B7B1471DDA09DCCULL, 0x51BE5CD235A04069ULL, 
            0xBEAECAD8E7934010ULL, 0xF211B3CEE54CFD37ULL, 0xB851656F01FB6AC4ULL, 0xC1B942B67A1F6A34ULL, 
            0xB324DE4FB5FFA52AULL, 0xD11AB65C74AEC1C5ULL, 0xDBCB48EA812FC6C7ULL, 0x54B827D42F3C92EAULL, 
            0x2512F333659322F3ULL, 0x7C01DF43AA56EDC5ULL, 0x2573CF04F252198BULL, 0xA3B0773478F494E8ULL, 
            0xC59250F50FE34118ULL, 0x19A50796E2CA0662ULL, 0x79A8E1BD0DD6EA28ULL, 0xA82DEE073061E6FBULL, 
            0x4032042C6BA8F120ULL, 0x92D0C08E11D2B49BULL, 0xD0C9864972323B0AULL, 0xBF28818B31C11EC8ULL, 
            0x002FEB5CD7A14E02ULL, 0x356F85F79D99BAEFULL, 0xFA8198E0E62D73D3ULL, 0x3FA94A5E541E2BEBULL, 
            0x82514731122FA165ULL, 0xFF890E8E99FA5F36ULL, 0xB250613638881C32ULL, 0x15141E742CD7E977ULL
        }
    },
    {
        {
            0xAF1AA8C9AC1C14DEULL, 0xD693C819B15090CFULL, 0xD7933ABC9FA5855EULL, 0xD0F6CFF7AE3D3C32ULL, 
            0x79CDA90F7195F2D8ULL, 0x48176218E4D8D776ULL, 0x20B9F97F59A5A59EULL, 0x89F6F1FF6C7933F2ULL, 
            0xDF14955219665926ULL, 0xD54043428034F5FBULL, 0x3BF110118B5D7FB5ULL, 0xD27B406654E79E16ULL, 
            0x0FEFF14E5936F3F4ULL, 0xDE3B4070D8942295ULL, 0xA2113101C8A93A3DULL, 0x327EDA7FC22DB477ULL, 
            0x591CEF5F6BF6D8FEULL, 0x9F95350EC9AD764BULL, 0xAB5786085EAC7BA4ULL, 0x3046FBA821EEF80AULL, 
            0x98476BB0B537254FULL, 0x00B28A16DD518CE9ULL, 0x50C9C63A9A157FF4ULL, 0xAE57AA0774E3A4D4ULL, 
            0xC8D0FB2763BE466AULL, 0xDAC8EE7BFF77D923ULL, 0x5A1C08D146EC502FULL, 0x03FCDFCD37B33249ULL, 
            0xB514794A9D8B6DF3ULL, 0x816A90DDB215F156ULL, 0x221AE0D5D0D36098ULL, 0xCA4F57226DD3D3CEULL
        },
        {
            0x1D60591B0995B9B1ULL, 0x1D6F1EDF4A205DF0ULL, 0x6E9118809012A9BBULL, 0x43FDF786D84091A5ULL, 
            0xB8F193A30FBC7FCAULL, 0xBE8A3106FAE99346ULL, 0xD4AAA9160199A6EDULL, 0x6929DD95A9540186ULL, 
            0xD6658EDFD1F60EA0ULL, 0x719C331D5202A8D3ULL, 0xDC1E118B4E49E0C6ULL, 0x2E45D03EC6D3C25AULL, 
            0x95ACEF75A9F6C4E2ULL, 0x2E6BDF78AFC00955ULL, 0xBFA1398306FF65C2ULL, 0xA3CD0E2645437B9AULL, 
            0x4EDB3D72A34F350BULL, 0xC6CFCDDA08DD2AD8ULL, 0x065196D75BE83F2EULL, 0xC8515167E25B45BCULL, 
            0xA2CB55FBAA681C8FULL, 0x2B9BC9C23FBEAE36ULL, 0x051F8E8CAD8C85FAULL, 0x96148DCFC57394C2ULL, 
            0xEF3F4BCD5E1C2BABULL, 0x731A5989A39BD40AULL, 0x70FB32D725C1FF24ULL, 0x142957ED910F399CULL, 
            0xA7FEA6B5BFC1E408ULL, 0x221B83AB84F70953ULL, 0xB8BC6B2D443A722EULL, 0x76DD1C19977D97F4ULL
        },
        {
            0x7F638A72C1F75E9CULL, 0x9867421F24524021ULL, 0x5D0805E2B7122821ULL, 0xC1746811B929ADE2ULL, 
            0xC17E89E7E878633AULL, 0xF84EEB62C1ECDF8EULL, 0x635FF42A6AB05014ULL, 0x709D3630184CDF11ULL, 
            0xF91B1CD999C87A7DULL, 0xC82CB8196D2DFB28ULL, 0xDE51C444EF3437EEULL, 0xA9603ADA63E92141ULL, 
            0xF663CADF5FF7B20CULL, 0xEB321E067C223641ULL, 0x4430AFBB84FD4FECULL, 0xF379C10FC68AEC2BULL, 
            0x7AE4473C7063B1DAULL, 0x9A5769EC65B9EFD3ULL, 0x76A4ED735E098E41ULL, 0x18AB66883D2EBC7FULL, 
            0xB7E76002B7DF5BB2ULL, 0x7BADDC235446C6A9ULL, 0xCBC9A29A041D38DCULL, 0x2D53143A9A43ECA2ULL, 
            0x555C9573D01A0E4EULL, 0xC7FC391A62521FE4ULL, 0xB278109A88E81FD6ULL, 0xAF99F0D4A7EC846CULL, 
            0xF0EEA94A0E90D57EULL, 0x8F763D0BA5A640A5ULL, 0x6BF7D3192994EB5EULL, 0xE775EC3DFEF7CA6CULL
        },
        {
            0x6E86EBA12DEFC79FULL, 0x5D6DA6E3D762062EULL, 0x9153DA28E29560B2ULL, 0xC61E929D80AC6513ULL, 
            0x8B28461088DC0CA5ULL, 0x8D1420D971F89001ULL, 0x4324BA11E44AC28CULL, 0xCE13CFDB50DE8CA0ULL, 
            0x11389045337F6154ULL, 0x1A0E340234A10278ULL, 0xBE07B4635DAD9977ULL, 0xA3998664757265CDULL, 
            0x604B869BA0345504ULL, 0x5CE8EF41CBD44DF2ULL, 0x2E3D52CAF3984350ULL, 0xD5A7A300327AEC24ULL, 
            0x9753CE44E47672FEULL, 0x882919170192EDA5ULL, 0xAE33883365D931F8ULL, 0xA1CD35EC1E20AB85ULL, 
            0x149F26FABDE0635DULL, 0xAEE49087932A33E1ULL, 0xA309E20524E02EFDULL, 0x0C367FD108FAE6B1ULL, 
            0x33036FBD20E7D18AULL, 0xE957613E2CDFDCE4ULL, 0x03BD32BE89F9352BULL, 0xA6A66DFAD1EB17C6ULL, 
            0x7A88C78E4EBC198CULL, 0xC5983229A9E001E8ULL, 0xB0F67B948DC3F647ULL, 0xEA4D7B3AEBA3AB93ULL
        },
        {
            0xC46175FDEBC2FBF4ULL, 0xA6F4CB92FF3EF0AAULL, 0x5DD5DCD53EC458B1ULL, 0xC50CB6D9C20DF67DULL, 
            0xAB02138DFCC83610ULL, 0x7EA04B86DC9C2B1BULL, 0xA6F1A6513F9B9A7BULL, 0xFE05F6BD7B0AC290ULL, 
            0x9DE38AD8EE9783A4ULL, 0xEC3628AFA72BCDEDULL, 0x0AA96DA4653C4E9AULL, 0x5DEF9428D0539908ULL, 
            0x60D94212F93A1E46ULL, 0x4AAF6258B24F8444ULL, 0xA5A1C008000606C9ULL, 0xC516A36CCB8ACD5BULL, 
            0xC406D6D892B419B7ULL, 0xBD02888BD58C7BC1ULL, 0xD2DDABCE53D41E5FULL, 0xB3BCDCE7C7B11012ULL, 
            0x4FA3E11EC9DBEFB4ULL, 0xAC7A7EEB4F61F7BDULL, 0x199BED7F47256F38ULL, 0x3CB48C5AF944A539ULL, 
            0x7148C281F79C876EULL, 0x84A3088476318E89ULL, 0x8EA6381D2254D8CDULL, 0xAF90C8B1C9961530ULL, 
            0x2E693DF0671482EDULL, 0x04E1C0AB7F8C775EULL, 0xC091976285D09A47ULL, 0xBEC3044D17CA8B45ULL
        },
        {
            0x9A6BA22F22B7E461ULL, 0x74951F8706F9E27DULL, 0xFDECD46A73BAD242ULL, 0xA107B219AA4EBA09ULL, 
            0xE8711131F00E47F7ULL, 0xABAC7A90A21FDDF0ULL, 0x4873DEFF831E8CAFULL, 0xDAEA82427FEBDE0EULL, 
            0xD6783FD2B226DB94ULL, 0x59051826EF983905ULL, 0x7BF7E4F8ED209BC2ULL, 0xCB7A62E0945BA8EFULL, 
            0x947448C10D456568ULL, 0xA8AFCD2347971EEDULL, 0x9507E5CC7945545CULL, 0x040AE7550DD6A4D5ULL, 
            0x3A0C3C78F80F52C4ULL, 0xDF9E01450D446F61ULL, 0x753ED941E5EC9F73ULL, 0x1F1325962637D983ULL, 
            0x74D2DB404AD8F231ULL, 0x5EC0EB48B60E82F8ULL, 0x55BD77FEEE24F546ULL, 0x5F7D1A6BB002CA28ULL, 
            0x1CF96DDC567B9B28ULL, 0x4EC0D80E3227542FULL, 0xC61B993114609D5CULL, 0xFD6949041FA21114ULL, 
            0x2D0D6B9E0CADD759ULL, 0x0F552FBE7110C55EULL, 0x4DB6163E79587D56ULL, 0x02630D96420F275EULL
        }
    },
    {
        {
            0x27165753E97AEC43ULL, 0xB4A4241D95F15573ULL, 0xF18AF5826692E944ULL, 0x77EF1773FA92A77DULL, 
            0xE9CA24BBF3B91010ULL, 0x32EA0F525963C9DCULL, 0xDE312F6F5D64FD25ULL, 0x5BA054DF662785A6ULL, 
            0x5097D5D9B1C4CAB5ULL, 0x99D3343B65EF4F0FULL, 0x997B5D92A0373E8CULL, 0x455080A49E0984E4ULL, 
            0x77316E846D847354ULL, 0x773D45A1189C7C90ULL, 0xCA0687D30B6C5B14ULL, 0xD50ED1A65A451DEAULL, 
            0x477926154EDB4844ULL, 0x37C6B241A005CFD6ULL, 0x0B24E0A33320B0DFULL, 0x2F63A8EA0D72528FULL, 
            0x54FA3AA2968E3961ULL, 0x31FFFE9DB868A813ULL, 0x55371BB5DA5476D2ULL, 0xC0129114D84B354DULL, 
            0xAA6C49A072B0514BULL, 0x2F9A62CCF63B5BE2ULL, 0xC73BC5BABB22AF65ULL, 0x9C654CC8CD0DE936ULL, 
            0x54ECFD77A1261348ULL, 0x2743D6399CF2E03EULL, 0x9DFD0CA1C56737FAULL, 0xA4351E9FFBD744A9ULL
        },
        {
            0x2C12976F4C775F9FULL, 0x4EDA9B1AE73E7403ULL, 0xF1FEEA2C0BD69CC8ULL, 0xD247275E2C6ECEB4ULL, 
            0x0B5A06011210B2ABULL, 0xF7AC9CE9605120EEULL, 0xDDAD22E71D305905ULL, 0xCAFB635958A27347ULL, 
            0x5651F947EFC6ADA3ULL, 0xE160189969CF28B9ULL, 0xD6D278D512589B2CULL, 0x6947446242F4824AULL, 
            0xD40154A5EAE83F36ULL, 0x039ABC8233B884C9ULL, 0xB41E03CB2684A9E3ULL, 0x07613455DFD16B2DULL, 
            0xE211B47AABBA6B35ULL, 0xE727ECA08A6B8D27ULL, 0x77595299C6CC7055ULL, 0x618AA40D41E43A28ULL, 
            0x8CBC6E5ACBD0A4D5ULL, 0xAABDFFE3B56553AEULL, 0x8500CE8A981EF709ULL, 0x9F7565D3727FB6E5ULL, 
            0x73D86E4361181EBFULL, 0x5CBF1655080AA881ULL, 0x0B89040250F9CFC1ULL, 0x0BA8BDD58E45F4A0ULL, 
            0x939D67D371F2E774ULL, 0x740056B5352EA096ULL, 0xAE911E1E0BE9C158ULL, 0xA46A58C177EEDAC3ULL
        },
        {
            0xB0F7F0EC186DAEE8ULL, 0x2D5A09FC2BCF7E84ULL, 0x6F57186AC09FD929ULL, 0xF68BC31DAA54794EULL, 
            0xBC5785CDF77795C9ULL, 0x6914BD4231043D44ULL, 0xE21FCF453D247ABEULL, 0x93A526738514A56AULL, 
            0x7D123F3C9A326822ULL, 0xDC2A5898E4B82DE9ULL, 0xAA70E3109E72BCA0ULL, 0x9C83098114DE26BCULL, 
            0x97F686B9333A4786ULL, 0x8B98EC9AB207B2CDULL, 0x0FC64F5FFDDA2288ULL, 0x28542402F9D9CA73ULL, 
            0xBA2D9DE664B8781EULL, 0x30E2427CBF14DE54ULL, 0xB3FD7FAF472B29F6ULL, 0xD859484897B5C543ULL, 
            0xDC8FE15632B5E0C1ULL, 0x55DEFBF38C52A615ULL, 0x45DC8400B7EC84FBULL, 0xF8C40699F47411FAULL, 
            0x3A55B67EACFCF9BAULL, 0x35D3A7B9C29DCBE2ULL, 0xD7E778F3797E00FDULL, 0xCD52AC2A09B3ED39ULL, 
            0xF36102E7F6A01E5EULL, 0x251B0E828A7C619DULL, 0x81707D373972127AULL, 0xF45AB3E727B98559ULL
        },
        {
            0x9F16ED60673A31FAULL, 0x489B5DFB6A63AE40ULL, 0xC29ABB9330C768F4ULL, 0x63143090BA01464AULL, 
            0x7FCD19016952018CULL, 0xDCBFF98AFBB4E7B4ULL, 0x92F2578983BC72EFULL, 0x8746DFB8D075FC84ULL, 
            0x59F82E70D81F4450ULL, 0x6F6CEA02248F7182ULL, 0xAB107370E3AC8926ULL, 0x2C29F74CE3CA5206ULL, 
            0x35C3B568CC22F27AULL, 0x2C862816000FBB16ULL, 0xDD2A122A7FC7272CULL, 0x19C4CAADC8629AB5ULL, 
            0x299CD36AC89E803FULL, 0xD49BFAD71BB288A6ULL, 0x498EC2C03A0EDF59ULL, 0x9051DABB85BA777CULL, 
            0x2A3457C67F1C59ABULL, 0xFFFDC7907EE96E89ULL, 0xCC89C173EEBDC903ULL, 0x3F8239686E6EBA24ULL, 
            0x8B14BB4542B4C3C3ULL, 0xAE1840758653B9D7ULL, 0x86A7318968258E38ULL, 0x3ABB5986F02292CDULL, 
            0x64B6E5937F87D23AULL, 0x1CE57024BD4EE883ULL, 0xB1682FF5965CEB43ULL, 0x6B9244BE51B6D9FFULL
        },
        {
            0x1ABA9DE09C42FCD1ULL, 0x4680B5365AC8D8E6ULL, 0x78240017B6774F0AULL, 0xF89D2C8C85D38083ULL, 
            0x87BA123E64983089ULL, 0x8E435B1B81A8C416ULL, 0xCDE422161B04B5C0ULL, 0xBCDA4A4020D98BAAULL, 
            0x13E9F32196391B37ULL, 0xCFD305EF1B9BA54BULL, 0xBBC960C7DDE9D171ULL, 0xDACD41457E1D2490ULL, 
            0x7197E20A6275CC7DULL, 0x94A1B64389288F3DULL, 0x6A5AFEC1A5DCD683ULL, 0xAC3324941F46F20EULL, 
            0x866DEE8785632264ULL, 0xDB594BB64AF7F673ULL, 0xBA80615FFD0A264EULL, 0xCFB947527F55B182ULL, 
            0xEB60668171879644ULL, 0x91DF4CCFD96ADF2BULL, 0x3D7F63C532E60B56ULL, 0x84B4C3EFA0185FF0ULL, 
            0x9606EF6FA3A076BBULL, 0xF236A2D4B0EB9C5AULL, 0x81485702EB7103B9ULL, 0x2BAB06F13C922277ULL, 
            0x4DFEEEAA16D1C0E2ULL, 0x49455F286B98DFF5ULL, 0xBCF891F551B33FCFULL, 0x5B3CB65BFBD3C9BAULL
        },
        {
            0xD4EB51FE858A9E4CULL, 0xFE942B7897D9D839ULL, 0x9B904AE06CE35142ULL, 0xC3D89F3F8F3FE09FULL, 
            0xD40F142FB8E0AED4ULL, 0x9A9E339E44B52083ULL, 0x7CF24E4F63FCA584ULL, 0x8A29C7061B6B627AULL, 
            0xAA71924241E35C46ULL, 0xFF3086ACE3B02FC6ULL, 0xDC037E908FEECCA0ULL, 0x706F263664C2C980ULL, 
            0x2FBECD468223E704ULL, 0xA8F456DEA2F72B73ULL, 0x362195BAA6631CFCULL, 0xFF66F209D2AE1180ULL, 
            0xC2849449815B92E4ULL, 0xA711F902120DCE09ULL, 0x0BAFE6B6714D4011ULL, 0x0ABB6C2FA2C9EBCBULL, 
            0x912C50FE26147EFCULL, 0xB054170863D96C05ULL, 0xD02FA56EF56D73C2ULL, 0xA6C667E9C8A23E0BULL, 
            0x2CDBA9CA57A5E018ULL, 0xECD513CB2256BE85ULL, 0x3DD727CC5DB1C540ULL, 0xDA2D6D216E6A826EULL, 
            0xA3FA953495991360ULL, 0x593A47E907322628ULL, 0xDDE8EC2B6D7B8257ULL, 0xC90D46AF4FF034B3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseEConstants = {
    0xD2F4851EE086B18FULL,
    0x677252EA6FA0D6FBULL,
    0x77F340F44A582F96ULL,
    0xD2F4851EE086B18FULL,
    0x677252EA6FA0D6FBULL,
    0x77F340F44A582F96ULL,
    0x793B6A14B6A659A3ULL,
    0xA1F21054EE5B43EEULL,
    0x2E,
    0x42,
    0x94,
    0x49,
    0x4C,
    0x53,
    0x8E,
    0xC4
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseFSalts = {
    {
        {
            0x306FD6B8B17ADB4FULL, 0xD929C648958B7CCCULL, 0x0D47FE139128D767ULL, 0xEBEDDE84F06AE7BFULL, 
            0xA421214229B978B2ULL, 0x55CDFA602225BBC5ULL, 0x802A7E9FE66F0A21ULL, 0x969F12EA91FBFED0ULL, 
            0x637A1DE9C4CDD468ULL, 0x7890DB7AA79D9117ULL, 0x9E817AAB6034C2C5ULL, 0xED5066072429225DULL, 
            0x5F2864E0CB081FB9ULL, 0xD9070C29E4D898BBULL, 0xEB9B630358E6E237ULL, 0xEDBC43E464C7B079ULL, 
            0x9F5AC8C362BAE743ULL, 0x67CC4E613BFF7387ULL, 0xD723EFB1890A81EDULL, 0x7EB078B5B86415D4ULL, 
            0xB895E726C19194F9ULL, 0xC5F04F51365081B8ULL, 0xEFEED885907B4104ULL, 0x82E143B2DDBA9B62ULL, 
            0x568DA9B0536A8FB8ULL, 0x1D65FDD242EAABC9ULL, 0x94F87D7EE67F8801ULL, 0xE2F8F0D20D940646ULL, 
            0x6BAAB0755750AC97ULL, 0x44EB60EED891942DULL, 0x2C686848576D30D8ULL, 0xE3230B78C16C61D4ULL
        },
        {
            0xBF4303CC564356D5ULL, 0x8CB31CEF1BF5862FULL, 0x63A756858C747718ULL, 0x3ACE49F8D2C56C23ULL, 
            0x8526B14C82F9F453ULL, 0xDBBF5058CAB7C65EULL, 0x3AD5A97DADE8C3B6ULL, 0x23F8EC9D1BFEDB75ULL, 
            0x90C70775CCB0D09EULL, 0x77A9AF2EF03FD18EULL, 0x7903B37BAEABF18CULL, 0xDA24FDBEB6D3C3A4ULL, 
            0xEEEFD3EEF32F435AULL, 0xA5670AD5274BC3C0ULL, 0x583F630596FC095FULL, 0x6A299FD993BB945CULL, 
            0xE40EEAD50D46A95AULL, 0xBC901B16BEA90BB4ULL, 0xD2267FD4A1108D42ULL, 0x4326726819A73866ULL, 
            0xA1AB0B8F79E9A95EULL, 0x20773BA0F65924D6ULL, 0x447E3EA776230962ULL, 0x84A678E22B07571BULL, 
            0x6A193B4446CE447FULL, 0x7C8847E488AE2FD1ULL, 0x18D920DD228F6904ULL, 0x42F72E5F868815C1ULL, 
            0xDE2679B76B75F8ABULL, 0xFA50527249A7980AULL, 0x59F77FC8AC5CC7C5ULL, 0x5EEDADB8385449BBULL
        },
        {
            0x151D3BB9A6D14F87ULL, 0xE8B271FB782800FFULL, 0x1AB794AC33D46F09ULL, 0x7932BB9F08A09EA3ULL, 
            0xA4CC5435FF0236E7ULL, 0xCDCD8F317FBD4CE3ULL, 0x06935C85E7F2BF72ULL, 0xF7BE3D84F29EA84EULL, 
            0xF15AC832C7E4FA78ULL, 0xEFCB133D898DE19CULL, 0x96E6B6800FE9F6FBULL, 0x60F9366B7C910B80ULL, 
            0x634C521D936F944AULL, 0xBA061AB2EAC5AE2FULL, 0x7435CED7288B686FULL, 0x7DBF14CC8087217AULL, 
            0x5557331F6AB253FAULL, 0xEEA9EEEC3BC8FBFDULL, 0x3C3948EABBA91340ULL, 0xB38D7A0A02B23F10ULL, 
            0x1A322BB8E0749919ULL, 0x64E1199B11399595ULL, 0x199B32319D8E81D0ULL, 0xD3A1355AFCA04D3DULL, 
            0xABBCF56BD25A8018ULL, 0x153898DFEC1225FFULL, 0xC349A5268062AB52ULL, 0xD1CE46D3B7D37B21ULL, 
            0xBE2E3C4B16F5A608ULL, 0x79C72A265A90D329ULL, 0x387F941E48BAA213ULL, 0x928967BC9ECA0FDAULL
        },
        {
            0x35E3F56502C574B9ULL, 0xC84F7A5594CFC1B4ULL, 0xDF4429E427A59953ULL, 0x9A212ACC9986D172ULL, 
            0x98F106BCFA7D7748ULL, 0xD4C8BB1679BA2904ULL, 0xF2377EFFB62CA052ULL, 0x2652BAAB85E6DAF7ULL, 
            0xA044A7B3E8B89714ULL, 0x981F40E4ED4DD510ULL, 0x3C1238940E9193B1ULL, 0x914A8DE2AE36586CULL, 
            0xCDDCCE7976809F89ULL, 0x4ACD6444F3F124DCULL, 0xCD8B7E49444862AFULL, 0xEB5BE87714ED76F3ULL, 
            0x5AD24740BFAE2B98ULL, 0xCC5B0E3533193324ULL, 0xB23FFA57E0189DF9ULL, 0x7A5AFF6C862B2EF4ULL, 
            0xEB6B9456EF79B7B3ULL, 0x67007789CA623D5CULL, 0x2924A17FCB9B04FAULL, 0x7A7565F0C8D6C060ULL, 
            0x1AFE430C51EA2D2EULL, 0xC1D025A7C0906E05ULL, 0x904A6A25435C3457ULL, 0x0D4EFABB87A707C8ULL, 
            0x28C864D19E056775ULL, 0x1C74E514B460C163ULL, 0xFC0B8E75E0BD9097ULL, 0x4F65A82A26489294ULL
        },
        {
            0xFFB885D975CAAE39ULL, 0xC7CF8ADABCF91464ULL, 0x1688C90FD29515CCULL, 0xCEE498B6746336ACULL, 
            0xB312ED3D4ABAE2BAULL, 0x2F081467C78E4FF4ULL, 0x58F655A46E3EF525ULL, 0xF144CB7981ACA45DULL, 
            0xCD1957FFBCE1B167ULL, 0x496A83973C662273ULL, 0xA312DA4F94674364ULL, 0x3D3BF4D938DB0472ULL, 
            0xD1C2BECA77E98DFBULL, 0x08D2CAEECE5012D7ULL, 0x6012497A5B351AC9ULL, 0x4066A0408F16916BULL, 
            0x4861238BBA8EA8DCULL, 0xC29BCF7A3D773D38ULL, 0xBE53098B6B9AB26CULL, 0x71F41E44EE83F40BULL, 
            0xA0A1570566A6D6B7ULL, 0x2C85CD7A76B9FA6DULL, 0xD1A94E8C504E2788ULL, 0x6D364A91B01C7651ULL, 
            0xAB8A920107F39CC5ULL, 0x72E798206C979439ULL, 0xA453D33BAE0B11E4ULL, 0x456DF9958F1A1CCBULL, 
            0xD9F42C6FBD64FCDFULL, 0x8C42A2E5C114C8C0ULL, 0xA9E618CC28FFBE8CULL, 0xBAF69F343AD96089ULL
        },
        {
            0x3C1B2758498BD8A5ULL, 0x0C325FE966B711BCULL, 0x69EC3A4CD111D767ULL, 0x3B46BD9BF911B835ULL, 
            0xD3B078D6A74E5D75ULL, 0xFBE9CEF5489EEC00ULL, 0x3366F0F5FA35F297ULL, 0x4B48DF03D2722410ULL, 
            0x486C4D32C065318BULL, 0xFA020336D14693A6ULL, 0x93AF5749DA2EA557ULL, 0xE8AAB5DBA3512F18ULL, 
            0xC2949E7231DF7AA0ULL, 0xF7AF209948188505ULL, 0xEC816E556B825B0EULL, 0xE81C33A93306DA34ULL, 
            0xB62B37FC261DE905ULL, 0x02EC60D42EA069A1ULL, 0x499688E9BF27DBDCULL, 0x475A69ED933654ACULL, 
            0xFD0827BB70971111ULL, 0xC0F2C8B2E90FB1C6ULL, 0xE266CB082F1DDA77ULL, 0xB2463E26174315D4ULL, 
            0x75AB7D4D62098265ULL, 0xA6B8C936F9D8639DULL, 0x5128C437D5129D6AULL, 0x6259CF3D228A1084ULL, 
            0x61A547855A75418AULL, 0x3695E9BD486DE2F4ULL, 0xE8A5A0AE563A1F0EULL, 0xEB5F42E9A036379BULL
        }
    },
    {
        {
            0x0DEEC7A086DE098EULL, 0x9D36FACFC6CF9CEAULL, 0x499CFF9FE3555DE0ULL, 0xCF0EE32D9FB05796ULL, 
            0x6803F4D5770B617BULL, 0x129FE149921752CBULL, 0xC2BBA1541F91FD89ULL, 0x1BC3FE0CF7C3AE81ULL, 
            0xCBFC24D97DCA74BFULL, 0xEE4A8C0E9EA8E9F4ULL, 0xD35B41113CB0BA2EULL, 0x90E7E6D5EA7599E3ULL, 
            0xFBA33D7CF8119FD7ULL, 0x23E1D808B8B5656FULL, 0x329BCB3CE25097F6ULL, 0x5C361D515A4F2528ULL, 
            0xCA2A197918657715ULL, 0x41FBF9FA42C7BF44ULL, 0x3AA544BEB98F79C4ULL, 0x84681CF9DCCFDAE3ULL, 
            0x9D5DF615B5CE54D6ULL, 0x783B1549B28E7C0DULL, 0x478FAE9905DD2FB2ULL, 0xBF45B749855D6358ULL, 
            0x95DB87C1764A2697ULL, 0x62D22CA29FD868E2ULL, 0x02D55EB340C32996ULL, 0x9CBBE666328B6BC3ULL, 
            0x1226EBC1CEE88BEFULL, 0x2B2D736FD847CA7DULL, 0x77AF05609E2C833FULL, 0x75BDA6A1754C9E6AULL
        },
        {
            0x5CECFD6EF1F4BCAFULL, 0x0CCBAAB3D83953D6ULL, 0x40A8D4F787FD84A2ULL, 0x10DC5A099527DF71ULL, 
            0x0B7B606D8BB4ECABULL, 0x08988B1D0BC6F147ULL, 0x03E7A160D0189E65ULL, 0x0F009C6CC5193014ULL, 
            0x74FC2D102137939FULL, 0x7E0EAE059CF4BD4DULL, 0xCFD6F857A1DEFE07ULL, 0x89275F8E5C508C8EULL, 
            0x19E776FD6FD15992ULL, 0x47288F60854EC660ULL, 0x02FDBBE12A077BE0ULL, 0xC27F30ACC0DC2F2EULL, 
            0x90AB38B5F49F8096ULL, 0xB2F59D85F1D79624ULL, 0xEECD9D2008237B61ULL, 0xE6958DD3E132CA88ULL, 
            0xF69618B6E607D5F3ULL, 0xD2947A6E79D11ED2ULL, 0xD1FD74175930CDF5ULL, 0x3A4E3B10CDD9C2B4ULL, 
            0x62C61376A71D8CC7ULL, 0xC0E0E3E0D2DF1CE0ULL, 0x68005761466C57AAULL, 0xFCC7A86B271EF372ULL, 
            0x62142271CCA2372DULL, 0x92DDC08D7BD5A296ULL, 0x094FB29FA2526F06ULL, 0xC7FC1571F2E431C8ULL
        },
        {
            0xF3CEE732711A9585ULL, 0x90AA8CC83340AECBULL, 0x846348F82299C5A0ULL, 0x345D63AB8269AE33ULL, 
            0x0E3ECE5834A2D1E5ULL, 0x51963D782C59520BULL, 0x3EBD26B5C8472B6BULL, 0x41C44213730AE9ADULL, 
            0xB8D6CC2F590D8A71ULL, 0xC554AD9331E19C9BULL, 0xE0515FA8C3318785ULL, 0x280276ED8A809502ULL, 
            0x9145F83032EB06D4ULL, 0xED649DE123955290ULL, 0xAC1C003F0E01A3F2ULL, 0x799DF31B7EC2731EULL, 
            0xC0BBBEBB9E4615F6ULL, 0x64456158417A19A7ULL, 0xDB1B7C7D1B976B06ULL, 0x44DBD2706D46A718ULL, 
            0x15DE6EF1977F9AAEULL, 0xFCE5B9420E63E8B0ULL, 0x7DF7780C6D2C74EEULL, 0xAE97E4D417A09DA2ULL, 
            0x42FB691235BC9232ULL, 0xAA8A9A4F04193133ULL, 0x4720D756EFAC0530ULL, 0x3289B643245E09C0ULL, 
            0x2698A3AA9E153CE7ULL, 0x18DDDBDA95E99444ULL, 0x533C592562571BF0ULL, 0xB2C1673AFA72E25EULL
        },
        {
            0xDC793B46AF490DBCULL, 0xE7246ACB1A338DFAULL, 0x2EDCC82BDEAA93BBULL, 0x79699C634AF8D6BEULL, 
            0x9A63EAD709BDE98EULL, 0xB647C41C93E214AEULL, 0x2DDA6A48DA7198BEULL, 0xA40492CEF76418D0ULL, 
            0x7E79889F58D85C3FULL, 0x81E25AD37321138DULL, 0x97319FECEA096CB9ULL, 0x2EAC3D0287FDAD40ULL, 
            0xB7D0408B3CDD850CULL, 0xADA6FF2142C743D5ULL, 0x746A92E5A043FAF3ULL, 0x6C9DEE889DF5899AULL, 
            0xC06F2C0BA64D88F7ULL, 0xD1E32438B9ABED43ULL, 0x68C52C56BF16C999ULL, 0xACC513DBDAC4C613ULL, 
            0x896EEC22FCB44DF3ULL, 0xE8F941D72265D157ULL, 0x2F9A5A5D6705B2ECULL, 0xB1C82689438DCDA3ULL, 
            0x18F97360D03DDBC5ULL, 0x692A725246FD5179ULL, 0xF114BB3BACBBEF36ULL, 0x995F26B8F3FA7395ULL, 
            0xFDB1F07D85ECDCF8ULL, 0x6906490DBB6FD27FULL, 0x5E13C3934D5F5882ULL, 0x5A879BBB22EFF6FDULL
        },
        {
            0x7BC227F9A9B6F982ULL, 0xB1DC1BABBB2BF828ULL, 0xE38E6FCD47F08F7DULL, 0x33478C1ECD7EDAB3ULL, 
            0x71264913FA8C9A29ULL, 0x216A874570C3CA55ULL, 0xC939CD24CB1125E7ULL, 0xDEAFC08666500E60ULL, 
            0x6E0986C4EE3B2FA8ULL, 0x89B22C1F94BCA469ULL, 0x71BE302C5D20ECB0ULL, 0x106728EED8406FA4ULL, 
            0x03E23649E8E26D70ULL, 0x3DE0F3A78B7FCE1AULL, 0x552871D77975DD47ULL, 0xE58A416F64885E09ULL, 
            0x7690803F9B27C304ULL, 0x0DAADABC44185172ULL, 0x1E23E839593EC657ULL, 0x55E2255F44CED373ULL, 
            0x607E467E7285BD42ULL, 0x5F051C0957BBDD37ULL, 0x9AB7A4B25A8B9260ULL, 0x977D9F2719CC5047ULL, 
            0xE0C2C441067C588FULL, 0x951FBB253575261CULL, 0xD0D8D0FF8F064120ULL, 0xC75C3DF5EEF72C8FULL, 
            0x7AABD93DD6365E90ULL, 0x2931A5F4E1B520C7ULL, 0xDAF5003F80C5FFA8ULL, 0x85EDA28439965F07ULL
        },
        {
            0x4144F07790C2372EULL, 0xB7B19EFE06B50FD7ULL, 0x15420D685F5D4DF7ULL, 0x87C76EE0A6D6FC7DULL, 
            0xF226D2C884F1381EULL, 0x5F7BBC6122114657ULL, 0x3AC43E37B6C82811ULL, 0x5F6E7F709D317BDFULL, 
            0xC7F3E8997A868D75ULL, 0x88C59A2D50173A28ULL, 0x5CBAE096EB5A7E41ULL, 0x400BF1089E790DA9ULL, 
            0x16EA35490F144D6DULL, 0x7E85164546522C62ULL, 0xECCF59AD09ACB0F0ULL, 0x0939B6BBB924EE67ULL, 
            0x2562C3C14168E605ULL, 0x449A81C8C34D11DEULL, 0xCD9F2C0D7C3593DBULL, 0x3A1C85A66E7795D8ULL, 
            0x52D1CE0C18628371ULL, 0xCE4738E3783D7254ULL, 0x931F4322749CB160ULL, 0x7AF14A1045200311ULL, 
            0xB891F6997211CAB3ULL, 0x99F1AA2BF44E5FF4ULL, 0x8CA85B975A03B088ULL, 0x0AB324FF72D13603ULL, 
            0xABA65D8EECD584DCULL, 0x1A3332631333F92FULL, 0x783D2FC3CD6F2887ULL, 0xEEC858750EEDB847ULL
        }
    },
    {
        {
            0xABD3084C931DC458ULL, 0xDA5FC739D509D9FEULL, 0x65F4337235E50D73ULL, 0x830DAA987CF138E6ULL, 
            0x0B887B7BD7A19266ULL, 0xC152A747BFEDEA9CULL, 0xE5FD729D3A2DAA30ULL, 0x868FC0295D45CE62ULL, 
            0xF861ED6E116A81B8ULL, 0x39CA7AD2F342E430ULL, 0x723F83EF2B6C49D6ULL, 0x423F28F3C54F92D5ULL, 
            0x506E654B809A4433ULL, 0xBF18367C8607C4B2ULL, 0xC77E2EBC021AC6A5ULL, 0x6BFB611351159268ULL, 
            0x1D13F79BB41FCE30ULL, 0x8D0805382C660034ULL, 0x8008B91A7C42B80AULL, 0xC434B53DCB8A59DAULL, 
            0x1CD6D09FBD6263C1ULL, 0xA46B76F6C958686AULL, 0x916ECAFC1B68270AULL, 0x7EBA392BB192CD01ULL, 
            0xE56CDF26B1776B42ULL, 0x3C121C67238F6370ULL, 0xC9FE31B667CEE579ULL, 0x25F0EDDD7F3FF508ULL, 
            0x7E7A65357D3C4964ULL, 0x4C2E0326150C7696ULL, 0x47FC906D071E0BAEULL, 0x4DE13DD1F9A927BBULL
        },
        {
            0x5E04D1039FB18158ULL, 0xB592607CDC95BEFFULL, 0x87F0C615D8C0BF67ULL, 0xBE6D4576B70B2872ULL, 
            0xEA2293A8709B9047ULL, 0x69C88BEC0D02D7C3ULL, 0x7ED6AC026A067E8DULL, 0x6F7EF685628774FAULL, 
            0x0D743F8993215DC7ULL, 0x4A4F925711BD6C33ULL, 0xCA71F28B21492D19ULL, 0x5E0C4794BA7D9563ULL, 
            0x4C8CB3F00130AAEDULL, 0xE5BDD7F3C279799EULL, 0x8A6822F0D1BC69BEULL, 0xFC8FF9A71F91B6CEULL, 
            0xB5D4A35A883D9600ULL, 0x6B389E037C557F1DULL, 0xCCD98369BD29F077ULL, 0x4589CC054B4B2E29ULL, 
            0xA21FAA84776A3512ULL, 0xD23D2F57132C612EULL, 0x663DCEBA708198C1ULL, 0x7F47CFF0EB8FF8FCULL, 
            0x2E37709DE156145CULL, 0x9E85D90DC2B52C3AULL, 0xCD9535343086ED55ULL, 0x9F2D58B32777B079ULL, 
            0x0CEC6C213FA88D3EULL, 0x5477074687862569ULL, 0x4D72F2F7C600844DULL, 0x42C6A7929786DC30ULL
        },
        {
            0xCFF2B64FA791CF81ULL, 0x75393566BCDCCA74ULL, 0xBCFF107F2126919BULL, 0xD89FAF189CADE03FULL, 
            0x345C5E4466ED3E59ULL, 0x6C2385AA73B551D3ULL, 0x748D82C758B14D2AULL, 0x2435A90104A650BDULL, 
            0x2BEB4A67474E420FULL, 0x7DBE4AADA434CA3CULL, 0xD6834BA6DA9CF89BULL, 0x9FEC8B70519A3408ULL, 
            0xDCA975DAC9EF0022ULL, 0x6E781644E4DAA8FFULL, 0xFC21D08727CCF6BBULL, 0x5C3EC8C372D0F4DAULL, 
            0x5F6578A3B37775EDULL, 0x0106806AF1A23D52ULL, 0x5DBAA1DF2BDD94A0ULL, 0xC7F73DA79202F573ULL, 
            0xE7BC3F19E6DF4368ULL, 0x79FA7898008868D7ULL, 0x7EC27FAE7A6A169DULL, 0xFF80A18A348FAF77ULL, 
            0x632E37ADFE798AF3ULL, 0x175D606DE7B317DDULL, 0xFDDF59A7BD5629E5ULL, 0xF3E9A2996BB34F5AULL, 
            0x10AE0177051668C5ULL, 0xDD1D1F603BE3A979ULL, 0xD37319844BC31607ULL, 0x672614FEC62D5D09ULL
        },
        {
            0xB51845277260F830ULL, 0xA429ABC4246253DFULL, 0x01C6E81CC2B45FB7ULL, 0xC2DFACBAEDA62E58ULL, 
            0xBD96E735C8CA4CF8ULL, 0x8C768FFFCB54624AULL, 0x95B4C858046C78A6ULL, 0xA317D86733945826ULL, 
            0x67B4016E1E86480CULL, 0x8FE7D33AFDE06D07ULL, 0xB5E1A9EAD8CF5B62ULL, 0xD261906423AEADE4ULL, 
            0x20C2C9A8305C7055ULL, 0xB897DA2173C37EB9ULL, 0x7A578917782B6B89ULL, 0x6130A3D4B8616A67ULL, 
            0x780A7884C663C9E3ULL, 0x9DFA7D962CA2D88BULL, 0xD433B72BDD98E5C6ULL, 0xF25495DA22B09B7AULL, 
            0x403CC11506D49AD3ULL, 0x94569A5D171A81B6ULL, 0xB71FA3E8650D0336ULL, 0xB17EF270ACA915CEULL, 
            0x39E1AF34276EE34FULL, 0xBDC204214D8F8D2DULL, 0x067A9A6589DC8A91ULL, 0x12AB785D539D461BULL, 
            0xFDD0B813A0D9FB1AULL, 0xCACA7EDD415DF279ULL, 0x6B0C48945281291CULL, 0x6A530117F1E3E5C1ULL
        },
        {
            0xBACF9577BCC80BD4ULL, 0xE60AEC4BD46D60F8ULL, 0x27FC89A72FDF259FULL, 0x740B13FFA0801EB8ULL, 
            0x206CFC0D75EFF16AULL, 0xEB41330322E3010EULL, 0x7C926CEC62BE0A54ULL, 0x080621BADFD4FDFCULL, 
            0x6F034BC9CD762331ULL, 0x1BED7B7B0501CF8DULL, 0x8A2A54CA38110057ULL, 0xAE28E9A817957A91ULL, 
            0x14CBE83BA5F7AB53ULL, 0x1A096BA608DA2B36ULL, 0x8427E9CCF81D698AULL, 0x933AE2DBE8D03A40ULL, 
            0x7A7EE4D83949EF59ULL, 0x3AA5C27C954C54A1ULL, 0x75763A0EF43BA5DEULL, 0xF27C1C54BDE4ADD7ULL, 
            0x0A4861ABFBD23756ULL, 0x366E326D125A95F2ULL, 0xDF0ADFFDA08B1A39ULL, 0xAFBD6A853BF6C0D0ULL, 
            0xBF02404F68DD97AEULL, 0xA8A91D73C94B47C9ULL, 0x76E9E2A2005A8F19ULL, 0xA71D5830C6121BE3ULL, 
            0x64570979C815619BULL, 0x3EAF3209DFA9511AULL, 0x80AF65BEB9D723C8ULL, 0xD71AB133AED30A1CULL
        },
        {
            0x24CCD5E1481DEBE6ULL, 0x186E8A5D8BB17920ULL, 0x44E90AAEE661809CULL, 0x00D8964DE3D70EDFULL, 
            0x86647A8AAD41DE1AULL, 0x9CABC9DBCAD94B23ULL, 0x3EE0F59CFAC5AA25ULL, 0x24227477AE56A007ULL, 
            0xFB5ACC95D35FC283ULL, 0xDD0D6B30F63FD700ULL, 0x5B108B9C77C0AF1CULL, 0xFB938C2851034D29ULL, 
            0x747C075E09BCF9FCULL, 0xACD560A29E8B9D10ULL, 0xD942E3DD5E6D3888ULL, 0xB1BD96734225F520ULL, 
            0xB7371946BD3FE32CULL, 0x28D1548CD51C1AAEULL, 0x404FAD884B59CF3FULL, 0x6026C4A94E22BDADULL, 
            0x9A8DDEA697EE127AULL, 0xE24EE5AC765522BEULL, 0x2B3DBAE61D62CF46ULL, 0x7829DDB5A7A55D97ULL, 
            0xD5A7F58D30149057ULL, 0x6C0CC4F20F91CC77ULL, 0x0D42E0A03C4767A8ULL, 0xD4B6BC72BC149E7AULL, 
            0x1FC06B0CDABBEBA8ULL, 0x58749E779A945649ULL, 0xD082614220F6E204ULL, 0xAF546D5B1D11A5ABULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseFConstants = {
    0x5954A7C38496B665ULL,
    0xCE345E802D9CF236ULL,
    0x722F3BA7867BEE7CULL,
    0x5954A7C38496B665ULL,
    0xCE345E802D9CF236ULL,
    0x722F3BA7867BEE7CULL,
    0x58E66C923029CE5EULL,
    0xD607F07353245E4EULL,
    0x42,
    0x80,
    0xD8,
    0xB9,
    0x7C,
    0xB5,
    0x1C,
    0x94
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseGSalts = {
    {
        {
            0x198430413E159CD8ULL, 0xD6441FF10DD25A84ULL, 0x3F2763A5270F7974ULL, 0xFBCF485F81AFED11ULL, 
            0xCA8A2B9B8BB0EDF0ULL, 0x80A9063E1D03F867ULL, 0x1545D3B5885822A4ULL, 0x459F156EA81ACC5AULL, 
            0x371E59E4CAB56602ULL, 0x6075D5ADD906BE32ULL, 0xCE2D4725FEC393D2ULL, 0xEC39789F8C6AF481ULL, 
            0xFBA8E9BEA87FF540ULL, 0x1BEAC11F6C902979ULL, 0x1A4418ADCB27498CULL, 0xB543A551DE440D2CULL, 
            0x37020089BB6F52E9ULL, 0x714499A72F9A6922ULL, 0x7B12D6AC522B2991ULL, 0x20F9E44FD79BCB07ULL, 
            0xDFC8F4136C130979ULL, 0x01830079C037286CULL, 0xB7BCF2AEAD0DEBEDULL, 0x9CF066D51B39FD06ULL, 
            0xEA25EAF8172E99B7ULL, 0x624CD6EA77224F1CULL, 0x63536ADAB8A60208ULL, 0xB6D423C7FC744721ULL, 
            0x0EE210AE6B2D5F89ULL, 0xCC541FBED7DE48CFULL, 0x5C0437A69578C19FULL, 0x1F78B888670C11DCULL
        },
        {
            0xD19C45C2BADF233CULL, 0x4E7641E3D241897CULL, 0xA072AB4F3B24343EULL, 0x335214F9CB01F17EULL, 
            0xCF44C1AE8588417FULL, 0xFED342A888B5EF3CULL, 0x7CE946A6D22691A5ULL, 0x702CCB6E669F1740ULL, 
            0x1996857DA8F5EB85ULL, 0x6C3E815CC969C231ULL, 0x951B737BC29AE03EULL, 0x8A47FE8CF2315260ULL, 
            0xD63CFD38B8C64205ULL, 0x0B25467E7F380BFBULL, 0xC1DD1E7FB293C783ULL, 0x2D3AD7FEE8C88426ULL, 
            0xE098897351195BBCULL, 0x140803CF1295C5E0ULL, 0xF8FDA7A858EB5E52ULL, 0x678936009C99C9E8ULL, 
            0x45521C49B8B5CEA4ULL, 0x6549F4F5B4C0E180ULL, 0x92FEC03AB8389FF0ULL, 0x5B4D616527C9A656ULL, 
            0x42CAA357527D7C11ULL, 0x8B785C0B31427142ULL, 0x83BE495F96048484ULL, 0x22673459B3A0DE6AULL, 
            0xA27F74BB4F91F302ULL, 0x8C6B305D979A21F6ULL, 0x032261B869EDEACFULL, 0xD8EA362941D93F43ULL
        },
        {
            0x358592D9EF999187ULL, 0x1EA13B179E0CB417ULL, 0x6686C4C187F6C7C7ULL, 0x167B490C80376313ULL, 
            0x9DD14CB1C759800FULL, 0xAE020892CC1ACA75ULL, 0x6EE74B73C2BC9A46ULL, 0x45FDA5B396D7C40FULL, 
            0x65111B46BE61FA77ULL, 0xFF6A8BB1B796AA07ULL, 0x705C3A179FDA69CEULL, 0xB04278B8E345D9A0ULL, 
            0xDD5E231D4D1DF349ULL, 0x19D344BA615340E7ULL, 0x7A5FBB02838D7D26ULL, 0xAC9106E5C83ECEB7ULL, 
            0xBC5FAE691A001E3CULL, 0xD675142AD1BE33D5ULL, 0x5F7C2C8B311C3CDEULL, 0xB2305E930DB97E6AULL, 
            0xF3E1148FCC5297C5ULL, 0x8A9C4EA69C2DF611ULL, 0x3D114F7BE4EB556BULL, 0x94845A5C40D2AEB2ULL, 
            0x77997F94CEC63978ULL, 0x537A295932884486ULL, 0x7E63F1219EE9C613ULL, 0xC5025C357E4AAC19ULL, 
            0x915E475C52E06586ULL, 0x1772C1BBE901C618ULL, 0xED1DFEC170B40C97ULL, 0xA203000C444D5397ULL
        },
        {
            0xD573601934589B52ULL, 0xD40FF961ED00302DULL, 0x8864E2C557C58963ULL, 0xDD0B0510AE1ED373ULL, 
            0xC95F604E5656E5D5ULL, 0xDA0DC5737A02BEDBULL, 0x8428135D7EEEB4B0ULL, 0xE803388023C57070ULL, 
            0x045BD21116BFE623ULL, 0x8C12A334EB97ECD2ULL, 0x17A2DEC24D8E3D7FULL, 0x1227328864F7D354ULL, 
            0x2A565B69F228B0D3ULL, 0x1CEC8A2A216EDF0FULL, 0xB147A5F80D103FE5ULL, 0x14429767FE520020ULL, 
            0x56349E3295933CCCULL, 0x199E240088946199ULL, 0xEF0E24C4561267CAULL, 0x36F7B08B9E214D5CULL, 
            0x5DE0FDE17DB41E6EULL, 0xBE0A170A77FA5BEDULL, 0xC8C17C024329EA11ULL, 0x1E322278AA69FBE3ULL, 
            0xF856538677BA97FDULL, 0xFCE549C164C63AEAULL, 0xE7B5D59CC05E1899ULL, 0x1B66DBD05BD2B532ULL, 
            0xCD44357D9C4FA4C1ULL, 0x70541D3EBB9B0588ULL, 0x722C1F5D5FF52BE2ULL, 0x7DD6B6B94617C779ULL
        },
        {
            0x6E92B45DFFD8A178ULL, 0xAFC0C6AF554CD773ULL, 0x24A1F8D59770BC57ULL, 0x4775ABEB9F0FA974ULL, 
            0xEC51DACF77E5AD14ULL, 0x130762F5D65E4017ULL, 0x8352AA6062975E60ULL, 0xCF62243EE7FBD147ULL, 
            0x04CFF1E00F48B07DULL, 0x3C61ABA8B2144419ULL, 0x325D8CAE400395B4ULL, 0xC1A8AF92A8937B77ULL, 
            0xE60C2ABDEC0AB7A0ULL, 0xD1C38FF16ECE5B2EULL, 0x0D224FBFA2C6B015ULL, 0xB876E47029735249ULL, 
            0xE0C894006D3B0621ULL, 0xB7F98ECFBFC0172FULL, 0x2AF217A38B920814ULL, 0xF96AC3A8D0C3F5BEULL, 
            0xDC64CCF2A8893590ULL, 0xD910921EA7A503A8ULL, 0x4D7A5C2239593446ULL, 0xC5880E36BD3BAD48ULL, 
            0xD44FE6DA07E4816EULL, 0xDDFCA8C1D39CA118ULL, 0x625C1A3E7777C3CBULL, 0x7D0935EFA8184CBCULL, 
            0x7713D0FDEFDD78CAULL, 0x34E23F6334DA674AULL, 0x520EEA72635A4AC5ULL, 0xADEB402AE88B7F61ULL
        },
        {
            0xA3A93D1935301BD8ULL, 0xD094E3C96592B670ULL, 0x37D3F3C3CB5941BEULL, 0x0D381DF451CB52D4ULL, 
            0x4CEE45A393B8C208ULL, 0x4B8CC4A6F7775D5EULL, 0xC784956C59B170FAULL, 0x67C01C47434A853EULL, 
            0x65BD10B0A2DFC23DULL, 0x3D9B5339F4C6E365ULL, 0x095E0891157C0520ULL, 0x1050F00095D27BEEULL, 
            0x4E4B0108227129F5ULL, 0xAC31EFEC33F6CB68ULL, 0xC12AAC0582462091ULL, 0x74F78CCF86239B93ULL, 
            0x70EE11D21CEF72AFULL, 0xC5681ED4E33E5D4CULL, 0xAF7A47F325EB92F8ULL, 0xA9EEDC22E989CD7CULL, 
            0x814C0A9597A1B65DULL, 0x3BE7A2F8D3D4A53AULL, 0x7266DF589B73776DULL, 0x4AE475AD4ED9D5C6ULL, 
            0xE8D3E8312AF426F6ULL, 0xEEEAEF93E2AA8C0BULL, 0xEB89CDD17607D271ULL, 0x6F389BD37D5CE4E9ULL, 
            0x0622D8B3471F1E50ULL, 0xCC433C574A6A51BAULL, 0x21E4C38A0622B9AFULL, 0x28AEA95FC081B55FULL
        }
    },
    {
        {
            0xEBEAFAB28F7F5D02ULL, 0xFBC02B82FF3AFCD0ULL, 0x2C0619A468128CCDULL, 0x0A41BCDA444B5821ULL, 
            0x231D9D3460DADC2CULL, 0x3EB674E7FFC2AAA2ULL, 0xF8B27D2B9D784AB3ULL, 0x11FF6C7D4C34462BULL, 
            0x2A764F07A5EEB05EULL, 0xD8DE2693F331D839ULL, 0x5ACA79709BB8C148ULL, 0xCADF78A4BC2EE23FULL, 
            0xD502DC91C60386F4ULL, 0xA5EEA078B1D2E2AEULL, 0x47C46DADDF6C9F44ULL, 0x6488FF3D5FB56CBCULL, 
            0x3C009F7C2817C732ULL, 0x322C2B88C5B3B6FCULL, 0xD44BF0BF4009E3CDULL, 0x6EF2B5E074E6F4CCULL, 
            0x6C2F23B70133B38AULL, 0xF322AC6C5FB1DDB4ULL, 0x0019A33A682CA972ULL, 0x6DE359C4F7F28E1BULL, 
            0x99062B6102A78638ULL, 0x448EBEB32962321AULL, 0x28116D85EB72EB98ULL, 0xDAD3DBB5D6E63A5DULL, 
            0x59F33A460F289EBCULL, 0xCE3FAE79A5C524B4ULL, 0x1A4411B6E8811AC7ULL, 0x5BAFCA8266C65DA5ULL
        },
        {
            0xD3221745C6854641ULL, 0xC3D1305CB25A8B1AULL, 0x5001475C8AF6761CULL, 0x767D66059CBC9CFCULL, 
            0x9A21C2F83EDF2F64ULL, 0x768F25DC529A3353ULL, 0xAE23689B93712133ULL, 0xBF8EDC58CF132B1AULL, 
            0x210B664958C89CCDULL, 0xA87FA9463B74A133ULL, 0xB4B6F62B129D9730ULL, 0x8EAD68B1163F6F38ULL, 
            0x81CD2BA9AE51624CULL, 0xC5BA402A2B6F13EFULL, 0x7C85146EF7460FBEULL, 0x45D6CC7528D72F3AULL, 
            0x9E8CB5BCBC135F00ULL, 0xAA65E5F8082E55D5ULL, 0x0BABEDB893B84E4CULL, 0xBAA8F066E1B7BE20ULL, 
            0x7A436904E3AFA8AAULL, 0xB0DBD49CE9D338F4ULL, 0x605356695AC69DA4ULL, 0x1D15DDD77A1B7F66ULL, 
            0xDB65DD62EC40D266ULL, 0xB67403A7C2566084ULL, 0x657719435B21F9D3ULL, 0xF81EEED11EFEE58EULL, 
            0x08886E1DFCF36C80ULL, 0xE770C94A077947D0ULL, 0x51ED3FC8DE6DB461ULL, 0x4FA1040073C1E946ULL
        },
        {
            0xDD2401E9258A5D79ULL, 0x76F67666E769AF49ULL, 0x0DC0119C111D14ADULL, 0x7E82D228A5D52C0CULL, 
            0x70870E65FB463F0DULL, 0xB4790016F1D38048ULL, 0x43E7E1779F8EC25FULL, 0x2220FB1BC6F74373ULL, 
            0xF4DD9E1FDFB9674FULL, 0x60BED8C3F48F34FEULL, 0xBD8BEBADAEA99BF4ULL, 0x6FD9AB567BCB041FULL, 
            0xC7CBD118EF7AD673ULL, 0xCCA7B2881AB88299ULL, 0x2998EBAC884899BDULL, 0x3599BE54E799308DULL, 
            0xE4E87FD50F5CF4EFULL, 0x6D379EE0EDEC93F8ULL, 0x77F53E896C8D7048ULL, 0x2494D9406D8F5D05ULL, 
            0xFDF9DEF4848EBC99ULL, 0xF37151B3080E924EULL, 0xAD1EF67AB2AE5039ULL, 0x22E9AC2DB89999E8ULL, 
            0xC456BCD2BB30E517ULL, 0xD2B5F3994C42D860ULL, 0x425876BC6E8A2175ULL, 0x2694FE818655DE3CULL, 
            0xBF9C0B4C2F351ADFULL, 0x2871CFAF78A74FFEULL, 0x472B898EFC0F8926ULL, 0xEF06AA83F8EF2C0AULL
        },
        {
            0xC0967A9F12E84EBBULL, 0x1BC5566BD41CA19CULL, 0xFC70BD313D48AC16ULL, 0xF1E06DB22E0E70CFULL, 
            0x9520344A8B373D65ULL, 0x71CA7B8FCD105208ULL, 0xC4B59381C02C3E37ULL, 0x61E82E0E0CFDCD42ULL, 
            0x41518C0105927F95ULL, 0x8CEC3B0523D5BBCAULL, 0x8400926103A76D0DULL, 0x696F9935A14BDF39ULL, 
            0xE10D9B43EE6F1280ULL, 0x7B60F36F328202DEULL, 0xDB4AA73A17C17491ULL, 0x9C558C7A678C7C76ULL, 
            0x7B138B433A2B62ACULL, 0x28F297D10013F151ULL, 0xCE7FABC35E89B07FULL, 0x6AA335DB7BF9EF3BULL, 
            0xA1E3287D85653C1DULL, 0x50DA03B81D873AA4ULL, 0x31DAE6C8D5E36D04ULL, 0x1BC5E11F47B25DB4ULL, 
            0x4771950E3F7D27D1ULL, 0x7D17AC83964C1D6FULL, 0x5D170A6EFE8DC3A4ULL, 0x4D62DEAD682C87A8ULL, 
            0x0FFE28F7E5E4FF00ULL, 0x030B259EFCDE6328ULL, 0x8DA4B57B2C28C21EULL, 0xD02A278F080A3AA6ULL
        },
        {
            0xEA46A7DA99E87B70ULL, 0x156721EB81B1071BULL, 0x21A5222A62F561E0ULL, 0xA806081CC219C02CULL, 
            0x912D588F6749371DULL, 0x4023B128E9FB6F99ULL, 0x074002D38BC33290ULL, 0xF419DF5B76FEE97CULL, 
            0x9403DD8103D568FBULL, 0x8AA16D6F2207D2D7ULL, 0x8B56D31183BC074AULL, 0x29622094EA8C492BULL, 
            0x054444EACD4E6C61ULL, 0x0598EB607540901FULL, 0x93B4926C3F4F1D0CULL, 0x499B5306E6E2595FULL, 
            0x89D285BEC8FD2B89ULL, 0x03E83F2014FA20F2ULL, 0xCD566AAAA23DE0E4ULL, 0xF53CA4F215A5671DULL, 
            0x18BCFACCEEB5D154ULL, 0xEB21C60CB8AC3D61ULL, 0x985D33520D7BC138ULL, 0xEABAF13A8640C18CULL, 
            0x1B6F07CA0A7526B8ULL, 0x90B7E4E629F77C67ULL, 0xBDB01CF20A9E931BULL, 0xFA82032F2924BDCFULL, 
            0xA46A7A64DD7EADD4ULL, 0xEE4B6900B6294149ULL, 0x9A6A6288B3C060D9ULL, 0xFCBB5ABCE57D0C55ULL
        },
        {
            0x14259FBB6C3FCABBULL, 0x33534CA1B6EE5AE0ULL, 0xA6014915CC54AD8EULL, 0xD16E5B6C5989C54EULL, 
            0xECEAC6EC572D2A54ULL, 0xA438B91B4DCED177ULL, 0x28FECFEA38ABB02CULL, 0xC0D8E91F38B87017ULL, 
            0x829F0A2F080244D0ULL, 0xA5660EDF0DE87577ULL, 0xB935F3389FB039DCULL, 0x4FF24D276294B2F0ULL, 
            0xEE16B2307800E506ULL, 0x308B48FCADC887BCULL, 0xFDB6A522DEF65ED7ULL, 0xD7B91F9EFC201209ULL, 
            0xB062123C5A1085E1ULL, 0x68A81390DCECA86AULL, 0xCB88B69DF2500D3EULL, 0x3373ECC8469FEB7BULL, 
            0xEC231132A9939399ULL, 0x81C5B1F40817C67CULL, 0xF347B05BF5EBADC1ULL, 0x0D357EC8AE56BC7BULL, 
            0xB64FBA1799CCB021ULL, 0x9A0322278ED31799ULL, 0x5ED8F2ACCB70063DULL, 0xA96F9D4D136B7247ULL, 
            0xD7260CA8FFA76ADFULL, 0x6F2478024DAB798BULL, 0x3041D48DDB2D207DULL, 0x06400AA618DB761DULL
        }
    },
    {
        {
            0x9E17D36B643B447DULL, 0xE46A150F0320462CULL, 0xEEBD47D06FD004D6ULL, 0x03369FDEC168787CULL, 
            0x9A79AA925FAA254AULL, 0xB17448CEBB59EEA3ULL, 0x37E2FBF687D9B2E4ULL, 0x2860266EFC0FEBB4ULL, 
            0x53D929D556B8C72BULL, 0x639EC2D8C30F6530ULL, 0x3FA515714B2A57DFULL, 0xD23BA5124C040846ULL, 
            0x7A4873F3BF0BB815ULL, 0x81823B6C4480C2B2ULL, 0x9795C7BD572AE145ULL, 0xD97E07255F2CB6C7ULL, 
            0x753595BD3EBDDF3BULL, 0xD92D05D04AA03811ULL, 0x928FE21A1C36DAB5ULL, 0x89B205DFC916AAC0ULL, 
            0x61531EA1FEF8888FULL, 0x64ADA5750EF0995EULL, 0x355BEA360CED3069ULL, 0xC4BFAE3112C6AD77ULL, 
            0x552CF11228DBFAC4ULL, 0x563D9F629A370E71ULL, 0xCCF7DF757D8F3FD3ULL, 0x19F50FD3C1CC4199ULL, 
            0x40C092692DB0B0E9ULL, 0x45CA3C672DEEAA4DULL, 0x297E8B149E43864BULL, 0x7A43B31025CF8BDAULL
        },
        {
            0x9F7EB4A8F3F619DFULL, 0x9E048828E7FD3CE6ULL, 0x7D4AC6410FD06BF8ULL, 0x11CB2E17706EBAB3ULL, 
            0x5470E86147B20D7FULL, 0x240A4BD44FB6931AULL, 0x00E6016CFFD73899ULL, 0x71D1AEDE155E2CCCULL, 
            0x7979C1E36480EA8DULL, 0xE490F58B64BEF341ULL, 0xC2FBA28FA165164AULL, 0x14FE27F97807359FULL, 
            0x674898937D4E2205ULL, 0xF9C9299A992E23E1ULL, 0x05F7685992C141FAULL, 0x2EE405992056C96DULL, 
            0x2AD5542E88C1646DULL, 0xC69BD8E2C2E0DF09ULL, 0x3380C5197FF56059ULL, 0x634E4888663A1465ULL, 
            0x8C9EC568FC4F199DULL, 0xC66025FE3D141675ULL, 0xA59E9AC6C938BFCCULL, 0xBB8FCB47CACD1B50ULL, 
            0x566AA6C22D91CDF7ULL, 0x17D3F8555A264B39ULL, 0x255F03A2C82CA0B1ULL, 0x250E1604EBAA987BULL, 
            0x54D31D25FC19814BULL, 0xF7DE060D29E58802ULL, 0x1320F98D9D485021ULL, 0xCFDD60412AC8338AULL
        },
        {
            0x1BCB77EFA8706B38ULL, 0x97067542D1ED8F62ULL, 0xAAEE7D8C84994947ULL, 0xF96EB9B4A6BE46D9ULL, 
            0x4099617698B163A7ULL, 0xF39BF7417B527E1FULL, 0xD35CC70C26D2143EULL, 0x88B7253EB569AF4BULL, 
            0xAF658B765704254BULL, 0x7C53201F6FF7DA54ULL, 0x5C8025890958688EULL, 0x742FF25EEDBAC688ULL, 
            0x71F7227A55ADA1F4ULL, 0x9735F074EF88CE84ULL, 0x0075CE9EA6AF1D81ULL, 0xC72AB79A58AA4755ULL, 
            0xD3925993717D162BULL, 0x379F7A2AA3E4685BULL, 0xC148B31A7A50C34FULL, 0x110AB1FAD64D2DE9ULL, 
            0xE920CC923DF3C58EULL, 0xE3AF52CBB05B13BCULL, 0x2F27607646287D64ULL, 0x7A469D73F910BDE8ULL, 
            0xF5C96770E8D93F6DULL, 0xCE493461AD368811ULL, 0x4616CA8AD1575E34ULL, 0x35CC1F958AF44E69ULL, 
            0x2874898E09D01D88ULL, 0x28BF70F9D6BF5C52ULL, 0x168436A8F40B0000ULL, 0xEEB4A69BB2E93517ULL
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
            0x310B1243C2F45809ULL, 0xF7173E352BCDD98EULL, 0xDA50225145FC2AA6ULL, 0x8D577C8D7DF02FF0ULL, 
            0x3114D64473308607ULL, 0xC32303C074CE1920ULL, 0x6FD2DE0A62E9667BULL, 0x7B664A47E8F84DA2ULL, 
            0x92345339F1D73F8BULL, 0x88EB7C56F9C1FFA8ULL, 0xB12C0F0D035F5209ULL, 0x0ED76432D26F9AD6ULL, 
            0xB527F87D27AE86D7ULL, 0xDE41C95E0617DF88ULL, 0x23545838C16FCC2BULL, 0xD744327EBC6C5121ULL, 
            0xF92241221501F49AULL, 0x754D162FA0889F5EULL, 0xD3F91396F1E6E7A8ULL, 0x46006BE2BCC994BDULL, 
            0x294735A165A511A0ULL, 0x1BA58CAFCA5DE7BFULL, 0x2A19281D7BAD634AULL, 0x62211B0A1F146BDBULL, 
            0xB2DEC1C2117FF5BBULL, 0x924D4DF906FBB5CDULL, 0xBF96E708206BE953ULL, 0x58A4EC71783A76B2ULL, 
            0x1743B5D35B4FAADAULL, 0x5C335D34D3281A75ULL, 0x2A2F10AE57C5461AULL, 0x46FADE95FAAEFAC3ULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseGConstants = {
    0xEA60FF36D9994AFFULL,
    0x5B812A5A96EE9776ULL,
    0x48EBE5A0B751DCE4ULL,
    0xEA60FF36D9994AFFULL,
    0x5B812A5A96EE9776ULL,
    0x48EBE5A0B751DCE4ULL,
    0x4AAAD5FFD926FBA6ULL,
    0x60C3E4E29E9D2746ULL,
    0x5B,
    0x56,
    0xE7,
    0x82,
    0x0A,
    0x40,
    0xC4,
    0xB1
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseHSalts = {
    {
        {
            0x13EAC98EFCE21005ULL, 0x50AE2B14E37B7572ULL, 0x09E282AE0B007D50ULL, 0x31E0B50E80F7F384ULL, 
            0xEF8B3F89CAE36B16ULL, 0x9A1C93D6349A43C0ULL, 0x98FFDCD3DFBDEE99ULL, 0x47B69EBDA7495CE7ULL, 
            0x590F32C766AA7980ULL, 0x0CFC15BAD4946150ULL, 0x3928904D6FA95D45ULL, 0xF61E814A816A69B7ULL, 
            0x1D42BD79A4BDFF48ULL, 0x53869A9AF7B31B25ULL, 0x4E992CB81A744FA2ULL, 0x68E452D415D23574ULL, 
            0x6AE77EF91AD18131ULL, 0xBC3ED4D4AC67503CULL, 0xEC93CF25AF20CA19ULL, 0xF04FBB7CA572642BULL, 
            0x4D0765A1EAF19176ULL, 0x6C26490C428B048DULL, 0x86654CDA8DC7DEE7ULL, 0x3AF6C32204799674ULL, 
            0x815D41B5EBBEB20CULL, 0x19EADB2069F73188ULL, 0x44A612C45190B7F2ULL, 0x5BD8FB0335E96825ULL, 
            0x2B949C64FE48D3E4ULL, 0x7CE8ABC67238811BULL, 0x561010648E67D241ULL, 0x714E3411CEE27FBEULL
        },
        {
            0x51C2C731C1902144ULL, 0x0DF117761C05A8F6ULL, 0x2EEDEF3AB30398C1ULL, 0x080C8474566020CEULL, 
            0x272843B4C56FFB73ULL, 0xC2C9EE80A1BD067FULL, 0x03DF010584236EFDULL, 0xE460FC4E4890241FULL, 
            0x348F7E0D6754330DULL, 0x1939E3147A073E1BULL, 0x36161A6494BD73C4ULL, 0xFF6ABBFA824C1BF2ULL, 
            0x49B64C4881DD77ACULL, 0x4B95164CEAA2EDFBULL, 0x6245BF89A4400187ULL, 0x70B115CE0C5E04E4ULL, 
            0x544156049CE93757ULL, 0x246D7C3FAD231134ULL, 0x99C248156474E1D8ULL, 0x2CE060E63C453D3DULL, 
            0xF2AE8AC1D13BC996ULL, 0x374E88330B1C459FULL, 0x01F2018320DFAA2AULL, 0xCC31EDCDC3FAB15DULL, 
            0x20E58EFC8FF8AFAFULL, 0xD3066E967C84A7CDULL, 0xE06E7864EFE79A3EULL, 0xBE8036A76425733FULL, 
            0x1CAE31315EA5BAE9ULL, 0xCA5F30DBD9706A57ULL, 0x6F341802B3A9261AULL, 0xB42ED22C42D7D1B6ULL
        },
        {
            0x60CCADF49069F62FULL, 0x82F467412F5D9928ULL, 0xA618DECFBD1ACC70ULL, 0xAB459E6E86C4A681ULL, 
            0x82F4E8CF791B51FBULL, 0xAF707DED5F162DCAULL, 0x4C2916638B93ED49ULL, 0x95834822AC3F10A7ULL, 
            0x32A05698EE5B0426ULL, 0x3A7101DE604A517AULL, 0xFFD24507A8F3D1ACULL, 0x423C530C8D7E2D50ULL, 
            0x60ABC4E1E5146BA5ULL, 0xB38849B9367F1796ULL, 0xF59864732198F910ULL, 0x09942A3D0A9D61E3ULL, 
            0x8A2C65FC1E9AE46EULL, 0x513273C192DF6CA8ULL, 0x9038D399F40E683DULL, 0xFA6094741C7EA160ULL, 
            0x3FC9611E0CB600F1ULL, 0x5C9D832A60EB3FEEULL, 0xD3F84B7057F90659ULL, 0x77DDEEFFF0FE9D22ULL, 
            0x178921A4BE90A9F1ULL, 0xC5100F53502D6ADBULL, 0x21586823BF28A277ULL, 0xA692A2B9C65FFFE0ULL, 
            0xE0E3D8CAFD99B07EULL, 0xA9F3D0F1F85E2317ULL, 0x34314E3548D5CA92ULL, 0x38348C440746D2A1ULL
        },
        {
            0x1C49D4F2E6CC5362ULL, 0x2D5AF53CDDD3FA88ULL, 0xA9862715B5A22127ULL, 0xBBD2F51B3CB63C09ULL, 
            0x406CDC4984228D2EULL, 0x40A8C0F9A085261CULL, 0xC9001CD11079FFF4ULL, 0x3E8A88892FD70487ULL, 
            0xECB0CFD05DBF1259ULL, 0xDF86D544869CF33CULL, 0x9954187F517952A1ULL, 0x49DC7BA2D5A5BB1AULL, 
            0x00468BECBD9791B6ULL, 0x28EC20D8DA5DAF4DULL, 0xCEE0DEFCFEAC81D1ULL, 0xF0FB3CD6C4249C00ULL, 
            0x0A4F5500DEBF2E53ULL, 0x1687E30E5E4581B0ULL, 0xE1823EAB503BB193ULL, 0x0E4A3F4FB96547FAULL, 
            0x4F4FDACFAEBCF7CCULL, 0x72FCBEAC52570F84ULL, 0x0F25A1F1C4584687ULL, 0xE964DCF71CF8273AULL, 
            0x1FA553FB6604B02FULL, 0x48CF496A4561D5FFULL, 0x14A40F406BA72E30ULL, 0x01B5C867295A8214ULL, 
            0x53616198AF30A671ULL, 0xDDBAF861FBB692F2ULL, 0x99D260DE4CAC6DEEULL, 0x009CA78DDFAD6753ULL
        },
        {
            0xF8D97E3668E6CBC7ULL, 0x1BF72D850B73A38AULL, 0x4848D0732CC69332ULL, 0x2178DF024ED8122AULL, 
            0xC8BBF844029B30B4ULL, 0x16132D1EB2F0A406ULL, 0x0C6469D9720DD9C9ULL, 0xD1D4EE6B03D957C4ULL, 
            0xE671E895D343E63AULL, 0x95B165FA9DE90D02ULL, 0xC48481BD25C9A715ULL, 0x655FD9ABA2AEF39CULL, 
            0xB573AC01ADCF69B3ULL, 0x81138FB1350D06AFULL, 0x5307D91A942BFF00ULL, 0x718D5B213F3FFA75ULL, 
            0xD5C17BFC6C64F41EULL, 0xD6B44EEAC6D03794ULL, 0x9BA78B2156B4B962ULL, 0x9058D415A3574CC7ULL, 
            0x2DDBC2B6F543172FULL, 0x046770F0C4B414D2ULL, 0x618F4726E3AA6E8EULL, 0x0D455ABE4E7127C0ULL, 
            0x980B80AF5BDA6F6BULL, 0xF7CB4EEA87ED8415ULL, 0xAE1975F0646CE034ULL, 0x32935B9AC126C273ULL, 
            0x81BF4090F555F6EDULL, 0x79A635F5E7991812ULL, 0x8C922F3005269491ULL, 0x874604257A0EBA28ULL
        },
        {
            0x6231A2EFE96CE315ULL, 0xF971B9241FC2864EULL, 0x722B6089E0856344ULL, 0xC97A0B5F950606C3ULL, 
            0x1E2CAEF5826B4795ULL, 0x45A804F3F392E761ULL, 0x2EE8AC64B36A72FCULL, 0x741B0A3098203A08ULL, 
            0xA49ACCF30BBFDFDEULL, 0x473ED4B97DAE9960ULL, 0xE1DC81B34267842BULL, 0xC4E12F7C0F0560F7ULL, 
            0x9CBE632CC9EEA101ULL, 0xF800F6ABBCE0CA9EULL, 0x0BFBD3AA0F47612BULL, 0x39F358B28F3F93F8ULL, 
            0x9A598B4709ACFDA5ULL, 0x5A9BBC57D4D6C798ULL, 0x7AA13F03354A3957ULL, 0xEE57711A4FE34431ULL, 
            0xC8230C0AEDBEAA10ULL, 0x6E1F409159C6F9B7ULL, 0x07A49D3A98B8AEB6ULL, 0xD279CDE444B0DF70ULL, 
            0xBC3E5332BCBC2EC7ULL, 0x41F0F661586533EAULL, 0x5594C6A01071B765ULL, 0xB629AA69FE4C3EF2ULL, 
            0x3B8630F0E1FF68DBULL, 0xCA799931CEB95322ULL, 0xECC2F10A98B25ECAULL, 0x61F5E762761F6AD9ULL
        }
    },
    {
        {
            0x595AF6255FBBCECCULL, 0xF2B59A3D84A0605CULL, 0xB61A262AB5A675DCULL, 0xCD3F1F6C0086FBDCULL, 
            0x3DA39BB3FF6332EFULL, 0x5A55A3FA02FA8E7EULL, 0xCC59E417E93DDD38ULL, 0xE9AA8CD5AA78E4FDULL, 
            0xB3E9E7E93238EC96ULL, 0x85C280F6F7010263ULL, 0xFB0106DC162BEE41ULL, 0x468C3DC062AD00B8ULL, 
            0x37F7667051A80C9EULL, 0x1AA186CD16FC85C7ULL, 0xA13CFF0350A02D32ULL, 0xE8CA758098F4D782ULL, 
            0x24C3650D2510813EULL, 0xCF3B87535F99F6A1ULL, 0x91F94E69F741D0C4ULL, 0x6A6452E2E7B1FC0BULL, 
            0x6D5CC62AA042CE82ULL, 0xD4A716490B8E8AD3ULL, 0xD33363E5DB2B141DULL, 0x4434FA0D6C9BD361ULL, 
            0x5C47F681DE40B2FCULL, 0x0EBE5D8A67E47FFCULL, 0x2CD64317A5881602ULL, 0x88CB937EA892DB9AULL, 
            0xB06D4DFD3CF7CB2EULL, 0x0AB95B772A4F7FD9ULL, 0x1474CC9672C79675ULL, 0xB4D0D9E06A4331F1ULL
        },
        {
            0x56FEE6470EFAD18DULL, 0x90581AAFE3B5CF93ULL, 0x5A50A241495377CAULL, 0xC0FE98A5AADF91EEULL, 
            0x4CC12E50D0977039ULL, 0x966E1229EA6E5483ULL, 0x51624BE34550AF68ULL, 0x3DEBF9D436E7CDE1ULL, 
            0x56CA757E631BAB2DULL, 0xA7F0DA022148204DULL, 0x1569FD1468446C8EULL, 0x29D4663AE922D6CEULL, 
            0xAD80F41978598B96ULL, 0xEB7988A1F6E5ED05ULL, 0xFF08B3B02429F01EULL, 0x231473EC7E120330ULL, 
            0xA8A4B7F8B6EDEB7FULL, 0x49B8E40B6CA6B6A5ULL, 0x1ABD45E89149B385ULL, 0x5EF1173A8C3A0748ULL, 
            0x8337299FBE25E84CULL, 0xD805AFBD3E65993BULL, 0xA211165750A30AC9ULL, 0xC333CCFF67559098ULL, 
            0x4881D35D17E9FDA3ULL, 0x571AA5E55D9447BBULL, 0x3AC5AAAC0595165DULL, 0x62BDC1038832D4E0ULL, 
            0xF3FFBDC830F6FB64ULL, 0xCD54E6CA6B77B334ULL, 0x7308216FCD23E4A0ULL, 0x1166A51CB566E122ULL
        },
        {
            0xFB93326D1F6E19B5ULL, 0x78F44C143A7540FAULL, 0x82810411DCC932E3ULL, 0x178977C1520A3380ULL, 
            0xA44416316582F7ACULL, 0xFFBC5822A8C581F4ULL, 0xC0ED21AF974D4923ULL, 0x8C304B3340AA0F57ULL, 
            0x9052F3A664152562ULL, 0x02DD64E9394C46CFULL, 0x34ABBC8C1B4FB986ULL, 0x2B9A4A02FF4D525EULL, 
            0x0B46E8DED26A0F46ULL, 0xD3F9CC69B875096EULL, 0xB2E78A828433B0D8ULL, 0x99AB5A959DB0AE19ULL, 
            0x2F371091D635F825ULL, 0xD29D32C064CF8C2DULL, 0x8365507E7F2D72E4ULL, 0x70F41DBAFAF30DD3ULL, 
            0xA7FA1C8A788CA82CULL, 0x00E000D0B1D88086ULL, 0xBE4BC099CEDF5147ULL, 0x8BF711E27E99BD9DULL, 
            0x2539F80D2CC84490ULL, 0x1859A9B77E15814DULL, 0x91CC4CF7FB021988ULL, 0xE78206B6B8A484EFULL, 
            0xA50C886DA8F5BCE3ULL, 0x9E2BFF8B3470A313ULL, 0xB254B7065358BF51ULL, 0x1152092B6090B0C5ULL
        },
        {
            0xA98C14333B83F519ULL, 0x60BF72BC4607CF30ULL, 0xA8DE0981F1B20C52ULL, 0x7C28B9E7EF6726EFULL, 
            0x2508DAD7931A7825ULL, 0xA376DA1E05BF8657ULL, 0xDED5A072DC3F61F6ULL, 0x9944D7D9D4A78F02ULL, 
            0x25E7942EE9072458ULL, 0x99176C3505881487ULL, 0xFAE5E1A7459F75FEULL, 0xF95CB980F6453D74ULL, 
            0x21E3434CDB99F01AULL, 0xDF697754CCAF677DULL, 0x45466A9E344F7484ULL, 0xE5EDD0F195AB6E88ULL, 
            0x4C5C0608D62D5814ULL, 0x1700D4BEB9293C68ULL, 0x65594C6EAFA9EDBEULL, 0x0A0D05B53A0014B6ULL, 
            0xA485D62D8C022F92ULL, 0xCDA9218C1E028738ULL, 0x80C992F47F9741BCULL, 0x089008314FDA52DCULL, 
            0x74E51968ECAF11F8ULL, 0x615A50A1A07EF5E7ULL, 0x42F798DEC6C785E8ULL, 0xB7DF6D2D1CB1DF06ULL, 
            0xDC7BC292AB1DE0B2ULL, 0x9F07120929680C46ULL, 0x0CE4CE22A57D9FA7ULL, 0x35AFE80B90C1BBA4ULL
        },
        {
            0xE684D7C1840ABEF0ULL, 0xF1C512BEDD1D88E8ULL, 0xAB19EBE059A8857CULL, 0x7A9B2B0046F985E8ULL, 
            0x5FB4823C37D0B2E1ULL, 0xCB16EC3A3DA24665ULL, 0x6D5BC78A839A9C82ULL, 0x69E88A0147056431ULL, 
            0xA185EFC4DF3A2C68ULL, 0x4B2754F07FFF1AF6ULL, 0x3D20E552E77F80B0ULL, 0x6AFCBB694440A79CULL, 
            0x2787E9285A1774A9ULL, 0xB9701F741E17A770ULL, 0xEC06B8230F9AF62CULL, 0x3793B613B31AB21DULL, 
            0x7333812B39913A96ULL, 0x6600E9017F8579A9ULL, 0x77199CED8E17AD95ULL, 0x2D32A56BABA3AB0DULL, 
            0x6D6B9A677AD05598ULL, 0x468E10EB838F35E1ULL, 0xE69948F57FA84844ULL, 0x62A3F2C545F1ABD5ULL, 
            0x5D2B4C630CE93707ULL, 0xB8279C533F9D2064ULL, 0x8DE82199CF914D6DULL, 0x7AC27D42E21B3530ULL, 
            0x1BBE816C22CF3049ULL, 0xAAE39BDFE1C25F86ULL, 0xE4592311CC4F4A86ULL, 0x50471D64901CEFD9ULL
        },
        {
            0x54FF6F655EC86E35ULL, 0xA0D4CA7740D797D5ULL, 0x8310D32090AEA9A3ULL, 0xC852580A48AB11C6ULL, 
            0x8AB107013BC61CACULL, 0xBD5183A9FF0C7D1EULL, 0xEFCFD769D6CFD9DDULL, 0x99CAD0F818C82ED8ULL, 
            0x9A76AC3B414064D7ULL, 0x72BBFEED25FD2ADEULL, 0x6F87332D0E52B5B1ULL, 0x61BCE78A63389F2DULL, 
            0xD036CB8B132BDD7AULL, 0x3AC8765F3387850AULL, 0x92421E1162E86A70ULL, 0x30B35838A714C743ULL, 
            0x17ECDA8B6A4BBD07ULL, 0xBACFE244DD397915ULL, 0xD7404556210CA6A7ULL, 0x11A65C04DF85CCB9ULL, 
            0x0E0B8C7E89EEDF18ULL, 0x88BC8F5F08FEBAEFULL, 0x14C71D14EC46F614ULL, 0x85F6401CD28618C5ULL, 
            0x2C8A46846F819FC5ULL, 0x9C52D0E0FAD3E353ULL, 0x3FCD595343110FE3ULL, 0xC4FDE9BE8EF5317DULL, 
            0x3AA521308439F4FEULL, 0x89E706F936A8B952ULL, 0xB89C39FCB856EB2CULL, 0x33103A525B556E88ULL
        }
    },
    {
        {
            0x1A0ABF6527C492ADULL, 0x14FEDBC69FA11D4CULL, 0xBA657735401FDF0EULL, 0x996A43E9EDC6E091ULL, 
            0x2A80BDE5DE9A43F8ULL, 0x2BB444018F89E9E5ULL, 0x3204C59F9AF8F34CULL, 0x69358D2894CB6678ULL, 
            0x46039FEE24C10892ULL, 0xE7716612D2EBDC50ULL, 0x68D0600C09DC57FEULL, 0x31D517EE05CD7C64ULL, 
            0xE8D69D8063944C1AULL, 0xF074AE8614B333EEULL, 0xE458DCCCFEF689CBULL, 0x24E853CD99D62A80ULL, 
            0x5C0CDC3AF007EFDCULL, 0xE018202903BDF299ULL, 0xA959679FBC67E790ULL, 0xC88B23BE808EE263ULL, 
            0xD827F60776EC9656ULL, 0xDF154C96BAFF778DULL, 0x4C48BF1AD9AAFAA1ULL, 0x5D5044219F89A7F8ULL, 
            0xE6F38BE4577B64C1ULL, 0x5E52EA0A6B289AC5ULL, 0x1D33F18EE7C5EA1FULL, 0x3F2C942F52856F1FULL, 
            0x4B0A1D59404895DCULL, 0x4405306933D98B62ULL, 0x246D66ED13501AF9ULL, 0xE1B24FA99DA4878DULL
        },
        {
            0xDC43B929A5CFEC82ULL, 0x935A131A29E0C9AFULL, 0x696439222617DFE9ULL, 0x32D8B6814D360063ULL, 
            0x414519E5504DB31CULL, 0x61C5DBDFC546F672ULL, 0x36535CD720686D76ULL, 0xF1CC8D520A2EA026ULL, 
            0xC852918532BA31DEULL, 0x338553383CC3C658ULL, 0xB368EBC7377E4183ULL, 0x23AB2C274FA1980DULL, 
            0xDF4CDF419FFFA857ULL, 0x3CFB414164FFA672ULL, 0xD11E9AAD8C6D5F22ULL, 0xCC0E5086D866A92BULL, 
            0xF71FD59EC9A42364ULL, 0x742560A3630F8E6FULL, 0x7FA24DA11EDED539ULL, 0xFE034947D56E8912ULL, 
            0x0DD77A226FAD2C1DULL, 0x79A4C3AEFFD091B4ULL, 0xD9AE4609948DA884ULL, 0x1947A8BB22AE4233ULL, 
            0x0C1DD5296B38A293ULL, 0x49EE7AA2FCE01C7EULL, 0xB53D609F8B8A22E9ULL, 0xC558B5C5AA8D308DULL, 
            0xDC72BC29D0806A9EULL, 0x19BA5AB7413E0857ULL, 0x24374FD40E266695ULL, 0x9790BC125C3B1275ULL
        },
        {
            0x0F1B874350F9C58DULL, 0xC07410193F83AC5BULL, 0x5068901EE86AFFB0ULL, 0x6891814AF5890BCFULL, 
            0x97D5BE83457DE38BULL, 0x7FD0E0F5F5C26A8CULL, 0xA461CE129D710B82ULL, 0x1F1A3384517DCF4BULL, 
            0xDA2005B91D064523ULL, 0xA30241768C5F931AULL, 0x5B89686B952A849EULL, 0x2DB70B78FA56951DULL, 
            0x75681AAAE6B81E20ULL, 0xE97961B02738D381ULL, 0x8573BD6D2626CE3EULL, 0x377468EAE98EBAB0ULL, 
            0x45BDFA9A364AACC4ULL, 0x1F48F3F8A81FF64EULL, 0x338D51CAA9742E13ULL, 0xDFD54E8C5E19BD81ULL, 
            0xFDD9CC0E0C7F013CULL, 0xA86AFAD581E530A9ULL, 0xA803BB8245580741ULL, 0x3C20308EE6C29C76ULL, 
            0x4C337458DE68249CULL, 0xB814F7F8FD01061DULL, 0xADE27B6194D89A48ULL, 0xC39C2920B7843EEBULL, 
            0xAE1DAB4A76B730DDULL, 0x43846C240FA27C16ULL, 0xAC969C1F3E600DC4ULL, 0xD433FFDDB858B449ULL
        },
        {
            0xE38A41ED7FD068D4ULL, 0x0B6327ACCB77EE1CULL, 0xA58B24B64BDEA2ECULL, 0xDA163D795342AB60ULL, 
            0x66680263A9951276ULL, 0xFA9C8C49483721E9ULL, 0x72F402AB255971F4ULL, 0xEB01EF74C614D300ULL, 
            0xC128C3B0204DDF8DULL, 0x692DF12A633F4F9CULL, 0x29A38A62A05F31F5ULL, 0xBE6D07AA4590EFCDULL, 
            0x0E1D69B2D74FE286ULL, 0x8816E95A2BDB522EULL, 0xCECD657432ED9C6EULL, 0xF15963944BE3BA9BULL, 
            0xC1B3CFDC1DA19974ULL, 0xBCA744ABD22A043DULL, 0x8BBF23F1807F5E37ULL, 0xF3E01963BE3EFCBCULL, 
            0x157C8EED62A11FE4ULL, 0x2CF59B07FA9FA059ULL, 0xD6EC4C102735D89FULL, 0xA72AAE84033B48BBULL, 
            0xC4194CD9E6820971ULL, 0x440707253DEAC0F4ULL, 0xCE60EBE118665C81ULL, 0x6B8960EAAAB83082ULL, 
            0xD8BF91107DC2EEB4ULL, 0x5B6E81824F4156A6ULL, 0xC971BB35A3DF445EULL, 0x603A7D9BDD48F75AULL
        },
        {
            0x6375F138EBFEB476ULL, 0x9103286907F1DF36ULL, 0x5685D264C4043FB8ULL, 0xF057F5EEAF60B4A4ULL, 
            0x4A7101272B744A99ULL, 0x9E1CAA21BB613CE0ULL, 0x14DE695AD2C91242ULL, 0x581CFE56F672919BULL, 
            0xDC5014BBD1929132ULL, 0x6FCB38E153B2C1DFULL, 0xB4279C265CE236DBULL, 0xD82C64D3044051B9ULL, 
            0x412313321818518FULL, 0x0A68509ABAC4CDCCULL, 0x92EA109412419C38ULL, 0xF3CF9ACF5C0ADDBEULL, 
            0x149AE892363554FDULL, 0xE82AB59BDAD27EF2ULL, 0xFF53D76004EF2F1BULL, 0x4BA962636D2D7820ULL, 
            0x1D9E671B6DFCD7F2ULL, 0x934BDD762B01A0E9ULL, 0xCC3CAC4BA929A6DAULL, 0x4019FA1EC423331AULL, 
            0x5D0E0DE9489AA5C9ULL, 0xB2447EAB15F797BFULL, 0x6A859029426C903FULL, 0xCD7421D57C63221EULL, 
            0xD497C9CB953674FCULL, 0x3632D4F8CBB86BD0ULL, 0xF6DE0CF50FBD5A8FULL, 0x8BF0D8F143C2D3DBULL
        },
        {
            0x9D05A8022A3471FAULL, 0xEB7980758E407F0EULL, 0x761D0DA30FA5B574ULL, 0x5736B8E1EA98F8E3ULL, 
            0x3411EED63E138292ULL, 0xFBADC53D99422503ULL, 0xC404C69E70D0A358ULL, 0x8C025AEEF3915964ULL, 
            0x0B8BF167F1AEA76FULL, 0x78881EFC58474E92ULL, 0x38F97EAACA6ED08EULL, 0xBEE4569A71EFF145ULL, 
            0xA369F030B12B30DCULL, 0xA7DA255D9950BD8DULL, 0x5CDD7180C94605F5ULL, 0x1FE65FA1239559EBULL, 
            0xE1B0C2D004244DDFULL, 0x124AD7D7756A8EF9ULL, 0x8CD6500D9F9BBCA7ULL, 0x1238E798D407F081ULL, 
            0x99FBB8BB69F234BCULL, 0xF6FAFD36B8ECEB00ULL, 0xADBBF11F3B9B2202ULL, 0x9B980B470755DDD2ULL, 
            0x95068A1C2B16C201ULL, 0xF1D24E4F4E09A29DULL, 0xCBEF121B948EF306ULL, 0x60DDCD7A5B81B10AULL, 
            0x73E721CC21EE018BULL, 0xE35DF7C6E12204B9ULL, 0xF138156E882108C2ULL, 0x2AB0EB8441E86220ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseHConstants = {
    0xB21229DA2B374060ULL,
    0x6A9FB090B171D8CDULL,
    0xDF781E74D866484EULL,
    0xB21229DA2B374060ULL,
    0x6A9FB090B171D8CDULL,
    0xDF781E74D866484EULL,
    0x68B15A2348AECA6AULL,
    0x44B2B14F5ACCBBF3ULL,
    0x2F,
    0x5C,
    0x74,
    0xF4,
    0x30,
    0x80,
    0x6B,
    0xAE
};

