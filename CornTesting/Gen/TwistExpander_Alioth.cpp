#include "TwistExpander_Alioth.hpp"
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

TwistExpander_Alioth::TwistExpander_Alioth()
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

void TwistExpander_Alioth::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB004E50AC9952C8BULL; std::uint64_t aIngress = 0xEC3940566BADAA95ULL; std::uint64_t aCarry = 0xF09F2C98D8288A98ULL;

    std::uint64_t aWandererA = 0x86E4D317A3869051ULL; std::uint64_t aWandererB = 0xFC51662F4DD7A1F7ULL; std::uint64_t aWandererC = 0xD6357E85D3A7000DULL; std::uint64_t aWandererD = 0xC20DC5DAE74FF195ULL;
    std::uint64_t aWandererE = 0x98A5B74AC0CA5A77ULL; std::uint64_t aWandererF = 0xF8EC1732D4304464ULL; std::uint64_t aWandererG = 0xB3368C836983B636ULL; std::uint64_t aWandererH = 0xF9F55A47EDBB673DULL;
    std::uint64_t aWandererI = 0xF44A4ACBD65431B3ULL; std::uint64_t aWandererJ = 0xCC159282C0C6B272ULL; std::uint64_t aWandererK = 0xFD7B7BEF4571C3AAULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10506628446308930683U;
        aCarry = 17499367825687222737U;
        aWandererA = 9841818871038318951U;
        aWandererB = 14611619311740337407U;
        aWandererC = 13483409252924029431U;
        aWandererD = 14972843449400667828U;
        aWandererE = 13021160435772826839U;
        aWandererF = 15241676961171914470U;
        aWandererG = 18116265796106074558U;
        aWandererH = 18064064994184527106U;
        aWandererI = 13593563164954820916U;
        aWandererJ = 13613384144458447186U;
        aWandererK = 10550932129954792236U;
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
    TwistExpander_Alioth_Arx::KDF_A_A(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alioth::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xBC82BF92781F7FF9ULL; std::uint64_t aIngress = 0xAB8A7F3831C63197ULL; std::uint64_t aCarry = 0xAD94C657E4094D7BULL;

    std::uint64_t aWandererA = 0xB7D181832D13BE6EULL; std::uint64_t aWandererB = 0xE8B968F145529EB7ULL; std::uint64_t aWandererC = 0xF6F66260EE42952DULL; std::uint64_t aWandererD = 0x8836CE705A9DA34CULL;
    std::uint64_t aWandererE = 0xE74B2D10A1C27C83ULL; std::uint64_t aWandererF = 0xEE58472064B9ACC3ULL; std::uint64_t aWandererG = 0xFA28DFDCAF49AB96ULL; std::uint64_t aWandererH = 0xD66F65381850B1AEULL;
    std::uint64_t aWandererI = 0xB368EC82B914C7B4ULL; std::uint64_t aWandererJ = 0xC8314C8C7D4D091BULL; std::uint64_t aWandererK = 0xB2E069E293DE209BULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12422912100477514544U;
        aCarry = 15647615659577812127U;
        aWandererA = 14338411331149524070U;
        aWandererB = 17239451575179326326U;
        aWandererC = 12849187230004247527U;
        aWandererD = 16572390203772485896U;
        aWandererE = 11190073892749837215U;
        aWandererF = 12783454397060581432U;
        aWandererG = 12831939902902292849U;
        aWandererH = 10496234466686979471U;
        aWandererI = 12570798977897770438U;
        aWandererJ = 13806334797610804494U;
        aWandererK = 13738742283815804578U;
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
    TwistExpander_Alioth_Arx::KDF_B_A(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_B_B(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alioth::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x834CC9E6D3086695ULL;
    std::uint64_t aIngress = 0xE97A54313861EF31ULL;
    std::uint64_t aCarry = 0xC7E4BB21A7BF9E88ULL;

    std::uint64_t aWandererA = 0x8DEDA2110F531D3AULL;
    std::uint64_t aWandererB = 0xF47CCEC4D17C6ACEULL;
    std::uint64_t aWandererC = 0xB70A2B11B07992A5ULL;
    std::uint64_t aWandererD = 0xB96A982426931C36ULL;
    std::uint64_t aWandererE = 0xF15F979320B78239ULL;
    std::uint64_t aWandererF = 0x8D219D33ACCE5B46ULL;
    std::uint64_t aWandererG = 0xFB8980C4F549AA54ULL;
    std::uint64_t aWandererH = 0xEEAB383E0E026435ULL;
    std::uint64_t aWandererI = 0xD74B32D7549025E4ULL;
    std::uint64_t aWandererJ = 0x85A26EB6D1F969DAULL;
    std::uint64_t aWandererK = 0xAA37BE6FF90F3428ULL;

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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    TwistExpander_Alioth_Arx::Seed_A(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_B(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_E(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alioth_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alioth_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 4 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 5784
void TwistExpander_Alioth::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1269U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1632U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1260U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1257U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1986U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1076U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1163U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 103U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 481U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1678U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1889U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1178U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 968U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1290U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 294U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 547U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1997U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 604U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1442U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1202U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 819U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 426U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1161U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1846U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 847U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 95U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1463U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 284U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 272U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 745U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1321U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 93U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 119U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 166U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2043U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 938U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1443U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 177U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1961U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1843U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 35U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1930U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1944U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1804U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 724U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 439U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1069U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 496U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 195U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 171U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 676U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1588U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 299U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 348U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1228U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1374U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1049U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1263U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1019U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 837U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 89U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1308U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1686U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1708U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 234U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1423U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 24U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1625U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1281U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 421U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1165U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1475U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1794U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2008U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1343U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 514U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1735U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1419U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1008U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1646U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1104U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1552U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 495U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1424U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1648U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 902U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2035U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1820U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1914U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 388U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 255U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1013U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 962U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1129U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1368U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 443U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1855U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 323U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1573U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 785U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 727U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 15U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1491U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2024U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 530U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 58U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1471U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 424U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 864U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 553U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 373U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1866U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1001U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1919U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 159U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 524U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1342U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1810U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 537U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1516U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 633U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 970U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 681U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1941U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Alioth::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xC2196DF281C5394AULL; std::uint64_t aIngress = 0xE477593C5686139FULL; std::uint64_t aCarry = 0x8B856CA6D76ADF0FULL;

    std::uint64_t aWandererA = 0xCD75384BEE00373BULL; std::uint64_t aWandererB = 0xDBCF1ABB4B2964F9ULL; std::uint64_t aWandererC = 0xCC7C19475DF42829ULL; std::uint64_t aWandererD = 0xE576823B8BCA4E1EULL;
    std::uint64_t aWandererE = 0xA8E371D5ABB5F9F2ULL; std::uint64_t aWandererF = 0xE8EBD755B83C0BD3ULL; std::uint64_t aWandererG = 0xAF89384FA2201585ULL; std::uint64_t aWandererH = 0xA6A4D3474E9D23BFULL;
    std::uint64_t aWandererI = 0xA42D9513938963B5ULL; std::uint64_t aWandererJ = 0xAAF3361D6605D89CULL; std::uint64_t aWandererK = 0xD9BB46A572742AEAULL;

    // [seed]
        aPrevious = 13006651099404921594U;
        aCarry = 10517437797364073133U;
        aWandererA = 17190267835954365491U;
        aWandererB = 12478687248978957539U;
        aWandererC = 17786117470285701135U;
        aWandererD = 15851978946683457870U;
        aWandererE = 10144399675993850263U;
        aWandererF = 14517773124720641197U;
        aWandererG = 9256800588014833499U;
        aWandererH = 12576813546113566265U;
        aWandererI = 16952521765302786587U;
        aWandererJ = 18186511685533936991U;
        aWandererK = 16182716613655431582U;
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
    TwistExpander_Alioth_Arx::Twist_A(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Twist_B(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Twist_C(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Twist_D(pWorkSpace,
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
    TwistExpander_Alioth_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alioth_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alioth_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 4 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1791; nearest pair: 588 / 674
void TwistExpander_Alioth::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4770U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3601U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6004U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 389U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1513U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 238U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4764U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1719U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1484U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 111U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2543U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3639U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2318U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1547U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5692U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5446U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 407U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 705U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 77U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1405U) & W_KEY1);
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
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1567U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 872U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 482U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 46U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1838U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 221U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1801U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 314U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1101U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2034U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1464U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1489U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1120U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 744U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1666U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 4 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1796; nearest pair: 590 / 674
void TwistExpander_Alioth::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6491U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5506U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4648U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7452U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3419U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5489U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7068U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4200U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3554U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2276U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6744U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3361U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6519U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4991U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1161U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1130U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 355U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1335U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1252U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 176U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1713U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1358U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1701U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 116U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1360U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1463U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 559U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1765U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1551U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1317U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 467U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 284U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1105U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 359U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 283U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseASalts = {
    {
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
            0x4D9F2DDCB6A5526EULL, 0xA353676B06B00810ULL, 0x4948CEEBCAC828E5ULL, 0x20BB9164F0AF56DBULL, 
            0xEC47725AEBBEFBF4ULL, 0x9AD540CD8A099EECULL, 0x19F67EFA83EECC7EULL, 0xFF897A63FBE24124ULL, 
            0xBBFC47C276E94C9EULL, 0x750FC60CA17F8975ULL, 0xFF76BA2F26EE9423ULL, 0x8DA3D6A8927B0F75ULL, 
            0xF7BADA96BF6E92C6ULL, 0x43A911CADD918F7AULL, 0xA471CB5C1F9CE7F4ULL, 0x1A544390F004971FULL, 
            0x96A1CFE220286B2CULL, 0x9B6E0A959C385FB8ULL, 0x025CDC53D6A6703EULL, 0xCF1C1F5DC377270BULL, 
            0x3B50E953E27639AAULL, 0x904EA37A17B9EB16ULL, 0xB7411FAF468BF150ULL, 0x1201DD42EA58077FULL, 
            0x9489F119D672734CULL, 0xB9E2639A51E71662ULL, 0xC89D326276ACAC07ULL, 0x39E7C823186B2620ULL, 
            0x3DEC8624D1BE2CE7ULL, 0x4F8F1ACF1AF3CFCAULL, 0x167D8A3320A584EAULL, 0x40ECB1D9C95236E9ULL
        },
        {
            0x1591A189362A4D63ULL, 0xE840D9C5C8835B0BULL, 0xBA3DB966C3F17FE2ULL, 0x01CD38C827C7EFD2ULL, 
            0xEB1450455A304A83ULL, 0xBA82985F66CD71EFULL, 0x9E3B81E6B6D40959ULL, 0x1E8F1E4492792FF1ULL, 
            0xDF101D46491B7161ULL, 0x119F4AB0E2E0A27EULL, 0xD89145A6644A62E5ULL, 0xC3C0A27A4B274860ULL, 
            0x247A20D79E5E4F51ULL, 0x850513B147C6C0B8ULL, 0xC4AA8F0DE9933C6CULL, 0xC6D4EA8715EBB148ULL, 
            0xE26E2C88CF39D7F6ULL, 0x9E66A90D9E2BC217ULL, 0xFC7143B37B061AF2ULL, 0x8B5E0C7ACE4D91B0ULL, 
            0x9C069D2FC5C2B4F1ULL, 0x1E3219786D0616D9ULL, 0xDE15A7B800FC22ACULL, 0x7EDD2AFFE4C3712CULL, 
            0x92E22507EB2866CAULL, 0xA61F574B4CDC5425ULL, 0x5C3676A6624A080BULL, 0xE886F380B77ADC26ULL, 
            0xFA66DB71D860092BULL, 0xB0011CC0DEE655EDULL, 0x6286D05E22B5B632ULL, 0x1A56C7AF8542B151ULL
        },
        {
            0x34D85949A7B58F3BULL, 0xC452FF6BF069E62BULL, 0x50C69302CB13A963ULL, 0x523947CCF6FAA086ULL, 
            0x0247C2D93DC243CFULL, 0x85188CC98794BDE0ULL, 0x70DD7BCD4C9D84F9ULL, 0x2C49E1090912A081ULL, 
            0x580973379C8F9AC7ULL, 0xFC3EAD9292EEFE14ULL, 0x7B747B8A00FCEACCULL, 0x65873E5EEDC5F37FULL, 
            0xBEE42E9EE0DB310AULL, 0xA4194DE2C487DA9CULL, 0x6F81CC5253CABF2CULL, 0xDDFF6FAF10B8F32CULL, 
            0x6DE5314D8E8C18CEULL, 0x8DBC1F53423C3909ULL, 0xDCDBA8C939787B43ULL, 0x42961775BC8C9DB1ULL, 
            0x1EFE95F4C55821F1ULL, 0xDDDECF0B5162D509ULL, 0x18DE34CB2115201DULL, 0xA1D02B96C0FB52D2ULL, 
            0x13C60209B999F679ULL, 0x8C23E9BB9FA4C864ULL, 0xAF7239D44ED3E0C6ULL, 0x0DA11D26524ABF00ULL, 
            0xB657D0094767CFCDULL, 0xF986D44363751D2CULL, 0xE6164D2675824277ULL, 0xE03BF3F73C093B3AULL
        },
        {
            0x4F6EDF278414E109ULL, 0x2EB9F9359DCFFF94ULL, 0xC20E57DA8DE77223ULL, 0xA62916CDDF368C69ULL, 
            0xF1A03FDA9A6CD7ABULL, 0xC606D21C9553C923ULL, 0xA43AFA0EC02F9A07ULL, 0x07FA79E4AB56A1BFULL, 
            0xF738CD5828AB359BULL, 0xF5EC4F92294BFE74ULL, 0x375F4A52D721DCAEULL, 0xE7FD0D0FC03AD05FULL, 
            0xDAFD214E88405D43ULL, 0x55611F2A3021B7D7ULL, 0x9145346179A64B3FULL, 0x0C0B51EB733E35AAULL, 
            0x6EEDF1F700E726F2ULL, 0x929C602A7EF8E20AULL, 0xBE697A5751422424ULL, 0x08E4593DB445ECA5ULL, 
            0xA65987CBDC24D37AULL, 0x1A0A60154166E1C2ULL, 0xCF83E31885E76DCBULL, 0x2849DF0961A55E16ULL, 
            0xEE1415E08486AF8DULL, 0x24546E2028878316ULL, 0xDCBE2F126E4BDC47ULL, 0x271B62186897981EULL, 
            0x87C222226386DF2AULL, 0xD3C14CDC0C6D9E3AULL, 0xB3266698CA4ACC76ULL, 0x8CAEE443DAAAE524ULL
        },
        {
            0xC81319E0CECDB556ULL, 0xBB065943F19F8713ULL, 0x9E1CAD5309A62ADEULL, 0xB867422F0036AA95ULL, 
            0x8246F3867BF869A7ULL, 0x07C78EFFFEC39D10ULL, 0x9A4A7340199A5ADBULL, 0x49972F7BC031D9FCULL, 
            0x0DA5B6456E892F8BULL, 0x86FB010E0A5A5F16ULL, 0x7923B81BA832D048ULL, 0x5B3871817D74A855ULL, 
            0x731EC86C6DB6756EULL, 0x77BCB616B79FB694ULL, 0xC4FC7EA2A21E6C65ULL, 0xEDA2D3DF1112D4DAULL, 
            0x47D3AF2475FCFCDEULL, 0xB14BFB7959285A4DULL, 0x4118AA28C6BE45B2ULL, 0x927950C05E01EF8FULL, 
            0xAEF7C0EF3D481794ULL, 0xB5C71CB1DB08FF9FULL, 0x8A109F5B22A79F15ULL, 0xDC83C6333D73A0B9ULL, 
            0xD0A7F08D2CEDDE62ULL, 0x121A391C6A15A3CEULL, 0x8D35E27B8AAAEE4BULL, 0x811B111CD15505FBULL, 
            0x98F24BFF890E4AB5ULL, 0x5B224BF51ECCB932ULL, 0x5FE97C1A6BE57A54ULL, 0xBFFAC65BFCDAEE0CULL
        }
    },
    {
        {
            0x79B98EA35F4864DAULL, 0xC3A52E097C053902ULL, 0xF50D3CF993808B68ULL, 0xA1DDC299FE8B4B89ULL, 
            0x004BAFF44FE5F3A4ULL, 0xFBC4FF7087709835ULL, 0x81D9B50C14DCCC2DULL, 0x031B6AF557F5A9E8ULL, 
            0x1DCA5FC056DCA42CULL, 0x5002220DC7746DFFULL, 0x9DC54B8DED3D2CFFULL, 0x4F3E91CD0F445324ULL, 
            0xD18EBC340958E2D6ULL, 0xF0E301B4F053CE7BULL, 0x80C2E5D66E598656ULL, 0x85C71BF0E0A62919ULL, 
            0xF97F5255566F9774ULL, 0xC9C964D28AA469B3ULL, 0x302E9457341DABFCULL, 0x28EB066B46EDC4AEULL, 
            0xCED1787A3CF10006ULL, 0x5E3C083676D1E7A4ULL, 0xCBC5ACE6D4A1018CULL, 0x6C9752A4C82ECFB1ULL, 
            0x47C9A6E110017215ULL, 0xFD460A8BCB27BD6DULL, 0x806BCFF368FC17FFULL, 0xDE6B924ECF196F74ULL, 
            0x74F34618DC78ED6FULL, 0xFEA6EEAA48A6F2FAULL, 0x2D80E6C9B7765D93ULL, 0x14AC495098825DFEULL
        },
        {
            0xCFB53C41D8A0665EULL, 0x22D24832FECF048BULL, 0x1F1FA762D5D4E497ULL, 0xDB77781F40AE4BF8ULL, 
            0x6C71CEC01FF6DBB5ULL, 0x8B474AD3FF9EED1AULL, 0x8FFF9B43446797CBULL, 0xF578DAF034C09987ULL, 
            0x9950F389D8A699A6ULL, 0xA5A06460F1D06856ULL, 0x766952ED1BF7CAB8ULL, 0x8CF453A782928A3EULL, 
            0x5ACF2D496A2382D7ULL, 0x5633050960E23AB4ULL, 0xFD6EF24BF05482EAULL, 0x29841EABDFE98713ULL, 
            0x96D833A0E674CF1DULL, 0xECDFE79750B54328ULL, 0xE1AF4A689771E6D4ULL, 0xEC4357F8F392E12AULL, 
            0x3C30190210E7CAE5ULL, 0xA4063B6C46F20B76ULL, 0xF5299BFF5F1B8129ULL, 0x87D78AA7CA171D66ULL, 
            0x75A96C5E88902B1FULL, 0xD40AAF8331D115D0ULL, 0x9E398DB33C7C97ECULL, 0x1DD2662B916E9D31ULL, 
            0x6537E873AC966E58ULL, 0x6F5EC9C3A90597A5ULL, 0x254C9DF54125E110ULL, 0x8529793D2FBAAC9BULL
        },
        {
            0xFF74F73980A8E086ULL, 0xE29596C8B8BA7549ULL, 0x0F338314F894B109ULL, 0xBEBCA4C35C86E260ULL, 
            0xCFC2C91B5A541E64ULL, 0x26E4530401045C3AULL, 0xA9B36697FDA9E666ULL, 0x4565E432CAA9A331ULL, 
            0x614E8708C279E868ULL, 0x6AC9EA2BC639EEABULL, 0x14BFC7F59A38980AULL, 0xE3E45DA11746A047ULL, 
            0x102CBCD27720A3F4ULL, 0x3EE5C0276238B9F8ULL, 0x06EB5539722F2D31ULL, 0x37A3DCDE93F65715ULL, 
            0xAC0A25E4C17A448EULL, 0x6C5917377DB759F2ULL, 0xB82F9B6A685A1030ULL, 0x84A7D67E89AC2C00ULL, 
            0x6B0FA45F4FB870A1ULL, 0x817012766BD0126FULL, 0x18347F66AA339430ULL, 0x7F68367267D54ECAULL, 
            0x9FB01363286C8CF8ULL, 0xF2A241EAA6D8E51DULL, 0xD86B9097F0C88643ULL, 0x9E4F40D1991E5779ULL, 
            0x2C235655AC0404C9ULL, 0x086505AD043A4313ULL, 0x2E447874767F72C2ULL, 0xF661DC3AF080C0BEULL
        },
        {
            0x9046E1E95BDECA8AULL, 0x3BB96239765A6A12ULL, 0x1CAB2D7A3C8F91EEULL, 0x2593862BBCF5021AULL, 
            0x433D48A09F649C68ULL, 0x9A8DE957C5D64F31ULL, 0x85CDF981C357115FULL, 0xFEB000420D2A0FA4ULL, 
            0x19B70913CBFFDC71ULL, 0x22059441529AE88CULL, 0x22FD72C918D78950ULL, 0xFD0C244F37881C0BULL, 
            0xAD01CCCCBE77FBF6ULL, 0x90B2C1BF8D04A758ULL, 0x67E66E988213E784ULL, 0x295EF23490385402ULL, 
            0xBF266AB9C4891594ULL, 0x1718788D9F603C15ULL, 0x2919CBC18701B879ULL, 0x6A7BA972EBF7E0ABULL, 
            0x95AA4338D4DF18D0ULL, 0x8DC5972CD689DAFAULL, 0xD1593198BFD4A3E1ULL, 0xD9E5B001D8D7D308ULL, 
            0x949EDE01A9AA075CULL, 0x13D5C24ED0C27732ULL, 0x35F35D67175DAD11ULL, 0x3EEFEC532B55D447ULL, 
            0x883CFECDF0AAF65FULL, 0x3249440D5AF3FFBFULL, 0x450C1DEE73A5C3CEULL, 0x29102D3D137A1672ULL
        },
        {
            0x3B1FC1018F972337ULL, 0xCFD11FC6D0DBE66AULL, 0x919B50B772D4DA76ULL, 0xCBB6C49281B24D48ULL, 
            0xDFE4BC9D48525B09ULL, 0x06063BB07E590987ULL, 0xE2E4AC2ABA81258AULL, 0xACA115C2BA31E5A9ULL, 
            0x51DD4D15F7987EAAULL, 0x11ED873A6F4352E0ULL, 0x49C3D0AB933BE6ABULL, 0xC711B8CB250172DEULL, 
            0xC79AD9ECBDC66803ULL, 0xE3ED71C667A1D13DULL, 0x7E7CE80219A6AC63ULL, 0x4D2E158F3B1F4001ULL, 
            0x15D72609C2DBF12FULL, 0x527F9DC75BA3930AULL, 0x1076D6B9DCDF0B52ULL, 0xE52AF087A49D1187ULL, 
            0xA97116754C75910FULL, 0x5F960C8811A7DE01ULL, 0xF865F9C021F19801ULL, 0xC40DEE91C58CAE3EULL, 
            0x24740D8894F11102ULL, 0x0105AFD4F9D98175ULL, 0xC8A295A5B33BCF04ULL, 0xCC31C3097D3A4B56ULL, 
            0x01C2C1FF0477ECB2ULL, 0xA723384A4FC3AE8BULL, 0xCD30D65044107D2EULL, 0x5CB536BBD3FBDE63ULL
        },
        {
            0xD62AEB502E5EFE26ULL, 0x7BCF470825DA46B5ULL, 0xFAA4580E28CE3B44ULL, 0x6ACEC7053BBABA50ULL, 
            0xE7DEB25DFAA3A2BCULL, 0x92465802172B5731ULL, 0x265F53C8D1F6E2ABULL, 0x8418EDE47DC8B440ULL, 
            0x4772177348D03B3CULL, 0x4D0A711B5E5D250AULL, 0xB475EC34BDBF8C81ULL, 0x4F61A601EB420008ULL, 
            0xBC60856BF517D00CULL, 0x547404BD89E901FBULL, 0xCDEE13F387602F2AULL, 0xA345E64DD5198D65ULL, 
            0x54C7AA95DB98E3CCULL, 0xCAFF0EEAD971ED14ULL, 0x4523729905F4BB00ULL, 0xA196909417EF8818ULL, 
            0xCA4ADE5EC5518452ULL, 0x4D95BD86082F86E4ULL, 0x72CA315BDE08ED55ULL, 0xB7504925BB0347DCULL, 
            0xB9F5592F9AC22226ULL, 0x809DE1E7FC82F4B2ULL, 0x6CED8F5B94B07AAAULL, 0x8919CAA589674955ULL, 
            0x9D658F5E1547DAB2ULL, 0x24821D827401645FULL, 0x6B5E177830769CADULL, 0x02D55A4A84894E39ULL
        }
    },
    {
        {
            0x745585C8DA6BAC40ULL, 0x26563D2EE05892E4ULL, 0x7F7EE3F177E6A816ULL, 0x3809EFB00B112254ULL, 
            0xB12E751F75948BBCULL, 0xF99612A053CE450FULL, 0x7D44F8AFCD8BF69BULL, 0x4DE818269B80022EULL, 
            0xB0054F7F3EBEDE9DULL, 0xDD466A96E15123E7ULL, 0x7F355189D59156CFULL, 0x6BF21545BD843585ULL, 
            0x8C392B48CF9B1C2CULL, 0xD9152A363C12E31EULL, 0x0DA9C556AE912E30ULL, 0x1475AC3E5CC23536ULL, 
            0xCF8BD36EBA5D7372ULL, 0x0B718A360B77A9D0ULL, 0x9ECA81B52BD98808ULL, 0x138288742877C6F0ULL, 
            0xFD9A3BE54873ED91ULL, 0x22923749CDF6559EULL, 0x850624DE0090A525ULL, 0x1B85DDC6634E2664ULL, 
            0xE82FCA9E71051480ULL, 0xFF3918A2A9D2B10AULL, 0x6E78C4F275EAEA20ULL, 0x0AC6391EFBC2C03BULL, 
            0xFEFD4AD28038252DULL, 0x29E3104AD187F6E4ULL, 0xD1FEB6939F350CFDULL, 0x0532365683644003ULL
        },
        {
            0x1F238D5E93527BF8ULL, 0x2027C35DF14B17A1ULL, 0x68BE807B85247E5BULL, 0x2DC168B284761920ULL, 
            0x117647843D4F659BULL, 0x9DCFC712CD5BB1D6ULL, 0xC21FA24642269DB4ULL, 0xE9579ECEB0DB3599ULL, 
            0x7718101DB8D5FB85ULL, 0xF577977FFDE5519FULL, 0x973A16DCA715955FULL, 0x4CE511BD965623C9ULL, 
            0xB4D13E0074567E4DULL, 0x5AAB3261B730A8F9ULL, 0x1466E9CC21C34086ULL, 0x8F01F09E71E63723ULL, 
            0x2C9D25F5698AD54DULL, 0x1E0A82FE01B574F1ULL, 0x8FA4E3FC804B7ECFULL, 0xFEDA48F82B1FB83FULL, 
            0xAA3977FF20457EF3ULL, 0x7F3FD00F32E5E917ULL, 0x04C7F00A98CB16CFULL, 0x035F3BD25477E734ULL, 
            0x4F127D9EE66523B5ULL, 0x83A7B03D8695BBFDULL, 0x69B3083B186C32C5ULL, 0xD96E9731DE589AC2ULL, 
            0x66DB7AE31CF610A8ULL, 0x82550831D796DF37ULL, 0xEF7768783102EC75ULL, 0x9668F743F4936CF7ULL
        },
        {
            0xDED0B5BE6A54D788ULL, 0x9CC52FAF2F5F43F2ULL, 0x574EB99D91774CB8ULL, 0xF9768FA4A76318C4ULL, 
            0xEAB8878AA927E028ULL, 0xCC28FF5FE38A8BA0ULL, 0x001AB82736D86EFEULL, 0x1F684EBD796C59F7ULL, 
            0x187F4B077B7484A4ULL, 0x478E50ECA1D8BC58ULL, 0x4A02594C988CF9B1ULL, 0x989175CF6AD7CA18ULL, 
            0xF14399F6B54AA7AEULL, 0x9EFFA18BCE7C6645ULL, 0x6CF58D8F15380489ULL, 0x03355181651F26AFULL, 
            0xAF4AE1D1F9C8FC29ULL, 0xBB692F514EF90573ULL, 0x3B4048719B13F054ULL, 0x92A8FB7055D4E327ULL, 
            0x6A3C5CE2F5A709FDULL, 0x4C04DA4674F7CD08ULL, 0x258F0AEBD4E90817ULL, 0xFCAD3C7F4AD2992DULL, 
            0xAEB2684FC769EA2BULL, 0x7C252C7C9C1536C0ULL, 0xB7AD3FC6D376447DULL, 0x056F40914B31751DULL, 
            0x68BD1845501D62C8ULL, 0xDA4E4C7A925FC823ULL, 0xC08E4E0BA643468BULL, 0x85E524CAC381E0D2ULL
        },
        {
            0x50F578AD7EC16A8BULL, 0xADA5D72CDDD72444ULL, 0x85C4F6BC3D9F8C29ULL, 0x2022BDD3B65FA213ULL, 
            0xE82D0B7979ED9073ULL, 0x7E9219D06056CBCDULL, 0xACA75D248074CB13ULL, 0x746E207456F49F14ULL, 
            0x1C4BA91F4476368CULL, 0x720E63A79C0346AAULL, 0x3ADB8FB1843A9A70ULL, 0xC47FFFC0083618BFULL, 
            0xC0DD2FF30DD49D1EULL, 0xF653692BE860FFE8ULL, 0xB3822102F3CE18FDULL, 0x049207EFE36A2301ULL, 
            0x3F18DED5885DDCCDULL, 0x547BBF5D3898A297ULL, 0x1C2FA99CF36E2E92ULL, 0xCB7CFB6AB336CDE0ULL, 
            0x63743D5C9791B61FULL, 0x65B34369175BA955ULL, 0x1B6EA36D3F7F9522ULL, 0x69C36955EAAEC8F0ULL, 
            0x53FE917B45E2C20AULL, 0x56694991B01311E3ULL, 0xCFB947A95223EC89ULL, 0x05679926C5A06B63ULL, 
            0x422346C1DA29639BULL, 0xAB3C494B3DB694FAULL, 0x77BBEF649E3C99A1ULL, 0xFEB078D3787214D8ULL
        },
        {
            0xE4D81F8B19B6C347ULL, 0x80E649CAA93E14A1ULL, 0xAD995AB773F0EBFBULL, 0x97E22AA8EBF2DE6CULL, 
            0x831D3F01E6AD9EA1ULL, 0x1E657536E3CDCB5BULL, 0xC306E123E0B3BA4EULL, 0x029048973D30792DULL, 
            0xF84FDAB188ADC6A1ULL, 0x0E85EB17D18DD851ULL, 0xBBA2F1BD058D5DA7ULL, 0xB6C23625A79DEC6DULL, 
            0xF74588A04BCB6AEAULL, 0x7D1F8FA0E5EF0BE7ULL, 0xF828F91C69CAAD93ULL, 0x87CEAFD5FC674461ULL, 
            0x869D20FB31E1753BULL, 0xE2A7E7D895F71E34ULL, 0x731FB3494CFE44A7ULL, 0x96A8F8F8E209BFA6ULL, 
            0xA0B7FB75C9E924A3ULL, 0xF50D70F6985FBDAFULL, 0x9791241F2A847413ULL, 0xCC4904C8A0B5D5D7ULL, 
            0xAEE44A736E2A60D5ULL, 0xFCECC2AD08F6EB80ULL, 0x132A4555CFD6153CULL, 0x55E70D6987885DF8ULL, 
            0xBE939B58B31C11B9ULL, 0xDD1A3D13387D03E3ULL, 0xA9F6F3F62E5AEC48ULL, 0x2D60D465A959AF67ULL
        },
        {
            0xE580C002A3D4B746ULL, 0x1D046404F6E94BC3ULL, 0x5DC01D0750851DB9ULL, 0xC0426CA5CED690CDULL, 
            0x4FAAAB36C4027C80ULL, 0xB5DC9BE4CB30B461ULL, 0x8A82121AFFB9B386ULL, 0xAD5B9FDE57952862ULL, 
            0x04A8FDFFA60A75E4ULL, 0xB7DB147F12D34DF8ULL, 0x244BE4A3BD5D4C1BULL, 0x4B8203594A6E7021ULL, 
            0x2C5E1302E5ABF236ULL, 0x9C01731DAFE489D4ULL, 0xEDF12F09767C7B3AULL, 0xC76436A58CB9B2E8ULL, 
            0x63B185148F6B6C90ULL, 0xDF417FBF63A27DE4ULL, 0x03C27C2DEB9C0558ULL, 0x2C9C9FBC66384660ULL, 
            0x0F81504D122C5FFCULL, 0xA7B5780538E0EA13ULL, 0x4DBE3C71F8205C54ULL, 0x0308102935DF62ABULL, 
            0x79962B25920C62BBULL, 0x32DFCD1B45B6974AULL, 0x0717B93CF4D4F5EDULL, 0x3BE5F5B6BF7B1202ULL, 
            0x1756705320E6182FULL, 0xB883D5F29CA262CCULL, 0x81975BD05FC54E16ULL, 0x5E6B218D1F8060ADULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseAConstants = {
    0xF13D6FB4074E73C3ULL,
    0x43E452578C45456FULL,
    0x989C24AE612D5F49ULL,
    0xF13D6FB4074E73C3ULL,
    0x43E452578C45456FULL,
    0x989C24AE612D5F49ULL,
    0x79ADB53FA905A0EDULL,
    0x546FDBF266981D97ULL,
    0xA9,
    0x92,
    0xB1,
    0xB9,
    0x89,
    0x85,
    0x0F,
    0x8F
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseBSalts = {
    {
        {
            0xED7280E61F1D89E7ULL, 0x6628B28916759E84ULL, 0x67DEA89D98B0591CULL, 0xBCB3834E3DF7A094ULL, 
            0x95E1CEFB412998B0ULL, 0x5298A4147DBC3EB0ULL, 0x71E74515D72C264DULL, 0x36BFB39B0EE6100BULL, 
            0xA739F43A9F2A57CFULL, 0xC8444DAC0876405FULL, 0xF89387FFA36B0E4BULL, 0xD6D17CBF7DDFEE88ULL, 
            0xD78B1B8BB869DD1DULL, 0xA9C911A505A9A785ULL, 0x5488A0E9FB635C8FULL, 0x81EE8BF7C5665272ULL, 
            0x0E73E45404BDA837ULL, 0xFA6C352FEDA2B249ULL, 0xB4379EDCC31049CAULL, 0xCFCB8C553B8E9F39ULL, 
            0x4542FBC8424F6383ULL, 0x02A0EFBB6D1FF68DULL, 0xF7478C4E6A5DBDC9ULL, 0xF5B1A994D49B0480ULL, 
            0xCB64A622B43BE910ULL, 0xE6BFAA25F36F6E68ULL, 0x7435A393F8C0A08AULL, 0xA4C2E0E703142B3DULL, 
            0x00C6F78254A2CC57ULL, 0x3324A510E86772D9ULL, 0x5B84291915AD9A74ULL, 0xF875491C63C3C0E0ULL
        },
        {
            0x74AC644B8479F6BAULL, 0x16F462D8514064F9ULL, 0xAD0EA787E6D2321BULL, 0xC5AC838732D05427ULL, 
            0x9D83032E6466A909ULL, 0x944E7671BEEE82B4ULL, 0x5A787BF11AC2CECBULL, 0xE73FCF6E1D326221ULL, 
            0x2D5B2D7B6786E33FULL, 0x57F5C27CC838F94EULL, 0xC682368F2B2E130CULL, 0x8B32DDF238F6C733ULL, 
            0x6A486402308AAA3CULL, 0xA2A936435613C9D0ULL, 0x1B82B6AAF3A22DC6ULL, 0x479C97C6F327C23AULL, 
            0x92C1E77BDAB39C61ULL, 0x27982E7A6E679C60ULL, 0x39AB7CE4352DBE09ULL, 0x7ADFD138E9616741ULL, 
            0x724299E433CFC71CULL, 0x76AAD4159E7B9E43ULL, 0xE993A380D2149A1BULL, 0x4E22651403ED58D0ULL, 
            0xB6090E8D33FB2F82ULL, 0xAE561E446CD0679CULL, 0xB4243DCA6595D1DCULL, 0xC00A7053858087ADULL, 
            0x2BB905421D83E428ULL, 0xD5D1E773C0ED2A4EULL, 0x0F1F9640C69B74F3ULL, 0x9BC8505EB8E18520ULL
        },
        {
            0x046519F7D61C55ECULL, 0x6E4CBBB85C6A4AB5ULL, 0x4087F0018862EB97ULL, 0xF9AC79800B26A7E3ULL, 
            0x330781AACD7574B9ULL, 0xF5D7FFB7A8DC5A88ULL, 0xEF0C0AD895AF4C42ULL, 0x0D01D5440C3C8F10ULL, 
            0x3242604E407DA606ULL, 0x9F684DD1177A616EULL, 0x2730833A19420696ULL, 0x16949A46DCF9931FULL, 
            0x52FF140CCAB58C22ULL, 0x636E830024C17E3CULL, 0x688C5F9A1D2C98D5ULL, 0x5E7B882E15665D17ULL, 
            0xE15409FF7E170304ULL, 0xC2F03CB868E465D0ULL, 0xCDBFD9803155EE97ULL, 0x082C8318E7FC72E5ULL, 
            0x6AB413A9A49B5502ULL, 0x710A574F6BA2E47AULL, 0x73EA793854C11D05ULL, 0x1E1A9F2277702B32ULL, 
            0x76B025A4E3758BF9ULL, 0x96AC31CB482BF3C4ULL, 0x60DA4B7DDBEB0962ULL, 0x76F5CCF72381672FULL, 
            0x37B1E2BDF6721A57ULL, 0x93CF8868B5ED8A2BULL, 0x2D9B963EE8532B95ULL, 0x5A1B4D22A980E23BULL
        },
        {
            0xDF129F1AB8DAB871ULL, 0x8BB955130005F760ULL, 0x50CB2700E06C73E7ULL, 0xB33367BC74A967F9ULL, 
            0xD4DB7A41819D4990ULL, 0x4CF1A313745FF30BULL, 0x9BB0249F3ECDBFBCULL, 0x3936DB1AECBD1500ULL, 
            0xABB5FFA7BACFB480ULL, 0x7FBA1BF45A9C4E53ULL, 0x966D81A75EBC540CULL, 0xB6E31A14ED2D0428ULL, 
            0x6967D78CDFD4DDD7ULL, 0x6D9676B6605915D1ULL, 0x5A3E7407FC729029ULL, 0xEA2FF0FA512A3561ULL, 
            0xEA0869E4DC66B88DULL, 0x9C79112F7A4C0049ULL, 0xE0558ECDE7E29DEBULL, 0xDEB1EAC128EA1CD7ULL, 
            0xD7E9623EF051DF5FULL, 0x6714E9ED60F97AF5ULL, 0x59B698AE839B5ABFULL, 0xF1E6FF7D22401E18ULL, 
            0x30E0D05FC3FE4A3CULL, 0xE89FB38425C8FA3BULL, 0x57FEC496D8EF07BAULL, 0xDDB6DA8D6CC9D332ULL, 
            0x77989E2A8BE88635ULL, 0xDCDCB4357B4C7073ULL, 0x209FD522F6B51CC6ULL, 0x703A6F6855BFEE1AULL
        },
        {
            0x92BFBD0DD95C5C66ULL, 0x3FD5BAB0B79A2ACFULL, 0x3211F9AB81F1CD26ULL, 0x4071688518A45887ULL, 
            0x11D7375CACC084F9ULL, 0xD7888D45CA309CEDULL, 0x30EC409109649889ULL, 0x3D0796FCE9AB3469ULL, 
            0x7FD838DA7E76C52DULL, 0xC642146479043EC9ULL, 0x5DC2D31ADBA8831BULL, 0x9BB80044DD812521ULL, 
            0xED59BC26ABD2C60FULL, 0x16D9FEB672C50A07ULL, 0xAD86D43265809B55ULL, 0x022D0C349FB7DA7AULL, 
            0x94322F3E896B7DE1ULL, 0x668C22602496BE5DULL, 0xA2E9C3D4C5858C1BULL, 0xA122FA90A4392FB9ULL, 
            0x42C76A45BACAFC42ULL, 0x117FB5F4B90CE1FAULL, 0x7567536DE5FD9FA5ULL, 0x01F62D5BEAF4F713ULL, 
            0x0D28C8826CB6ABAEULL, 0x61FE89B52DB86123ULL, 0x79736A514579954BULL, 0x348FEA0F80D405C4ULL, 
            0xB91EC7C9D45F906BULL, 0x4509536587EB93EBULL, 0x1577EFAB6357BDE1ULL, 0x01C36D45D0D8EB27ULL
        },
        {
            0x5DFAF09B4EE63C4EULL, 0xF3B9DCB439DFFE7BULL, 0x45E0B522EC041D65ULL, 0x4FC33A0248B42F92ULL, 
            0xCFB786C49C6E1A40ULL, 0xE53EEF7D8FC37F35ULL, 0xF526DF897770845CULL, 0xF12318F6DBC32254ULL, 
            0x75ABED4827DBC430ULL, 0x7303865B82243BDFULL, 0x9D2D800B756E7C0CULL, 0xC54F484F75BBDB96ULL, 
            0xEF1445C94B04F0EFULL, 0x1D3D3E76635F58D4ULL, 0xE6D6BF46D5804864ULL, 0x38A5DFC08FBBD711ULL, 
            0xAB184D0EA3D89BB9ULL, 0x877167EBB3DB20A6ULL, 0x54E25FED21F8FD6FULL, 0xB98DB27F41D91391ULL, 
            0x9EF330403A7D61C8ULL, 0x6A05B4EA0F153F02ULL, 0x45B06AF3724A50C0ULL, 0xE74AD626EC7D818FULL, 
            0xEB0E167B8FFC07FBULL, 0xBF1231E994F9B2F9ULL, 0xC8E0591CAF599B6DULL, 0x138F12018EB4A5F0ULL, 
            0x0045CBEDE075C280ULL, 0xA232FB7A50575581ULL, 0xFD1F06EF981844E0ULL, 0xC5550EBD830A7A20ULL
        }
    },
    {
        {
            0x48DFDBB0AB9E3BEFULL, 0xB9C8FF3526F6A84AULL, 0x65E88F9B4754C094ULL, 0xC209A5BF5C9CF2F4ULL, 
            0x57068EAD4A4C6080ULL, 0x3E3024D7105B135BULL, 0xE511948C9D347924ULL, 0x6EFCFFD46ECB8105ULL, 
            0xCECE6FA1A9DD6E5FULL, 0x7C2150FBD5E5C0AAULL, 0x31E1F3082362DAFAULL, 0xDFC7FE1A986566F5ULL, 
            0xDC1D4011F454BEB5ULL, 0xF510D9D32F01DD1FULL, 0xE33E98A151CB46E2ULL, 0x837E5F852D413C61ULL, 
            0x1912B454C7A291DCULL, 0x53E38598511C4A8EULL, 0x6890C754591A5BBBULL, 0x45824C6C62706A4FULL, 
            0xCE2E9EDFC4C46321ULL, 0x6861B2CFF5A336A9ULL, 0x1CC20B714F5E1674ULL, 0xAC23DC85D66250A9ULL, 
            0x9AE458D0FA2047E9ULL, 0x4B59E1DCE98A209BULL, 0x9B3ABA9B634DA4BDULL, 0xD3FABE6234C715C8ULL, 
            0xAAF45AC2B7FE94AEULL, 0x0A758C7FF94E8B18ULL, 0xE068147B5D6D0501ULL, 0x5E26A7F4A76F089CULL
        },
        {
            0x115016A9B62BB4E0ULL, 0x258F5E1E115400D0ULL, 0xABEF9BA9C47E29E2ULL, 0x0ED6CD6F48D38F51ULL, 
            0x6A9636E07F1C3533ULL, 0x3B4DB465BD2A66D8ULL, 0x1E3C1FF5A5B381E0ULL, 0x65F99EE53F1BF583ULL, 
            0xD609516D2BCC20ABULL, 0xB8A5C2D0B90D019DULL, 0xF967A807D5C309B1ULL, 0xE11490880747765AULL, 
            0x860723D3BCDE19DAULL, 0x5BDC88D7D5261D55ULL, 0xD3283749018A8883ULL, 0x9A71453F422ECFEAULL, 
            0xC7DB55FCB98E92C3ULL, 0x7B0A68E167B1E5BAULL, 0xC7BEA385CA368C54ULL, 0xDADB183B4794C89AULL, 
            0x1E3B9F4E6B0C9A74ULL, 0x84C2DEF77B189F52ULL, 0x3C912F839E07121AULL, 0x1D8610BFB0543FD2ULL, 
            0x9E82432C21276096ULL, 0x14EF2E570A029176ULL, 0x1F26325FA54B1AFCULL, 0xC222DD932186BE7FULL, 
            0xD22896EC95B35825ULL, 0x8B8980C309E311A9ULL, 0xEC612D33103CC73DULL, 0xA3F9EB7388C203B3ULL
        },
        {
            0x2F3C0C444BECC1DBULL, 0x4BD81CD1BE1A51FBULL, 0xF48731BD196AD311ULL, 0x5B101E53FB09D0F4ULL, 
            0x5E159E407143105CULL, 0xCF4ECEBE800151BAULL, 0xDEFE9CD8DB1D6568ULL, 0xA520C924362F140BULL, 
            0xDA8709D33F44EB6EULL, 0x378B28D847577797ULL, 0x1EF410E7ADBD5FA9ULL, 0x4560D02842846802ULL, 
            0x1CFDB596C40AC01FULL, 0x7CE60E4006A212C9ULL, 0x053F8F50B19F4AC6ULL, 0x25FE3678A97E60F3ULL, 
            0x82E1BEB4AD5BC72BULL, 0xCD6F6F23AC123C7AULL, 0x03C3D256CE86127AULL, 0x316A33E2653A74DEULL, 
            0x4C192DF7292D0901ULL, 0xEE015CEBE82CE21EULL, 0x9E5AC10B9BB22E64ULL, 0x0961523973251773ULL, 
            0x8A17CD36E880C256ULL, 0x9F9B4373283477CBULL, 0x1B759F386D375352ULL, 0xCCEE29D5ACDB29BDULL, 
            0x609A343C7EB6FB9BULL, 0x3297B0CD65B2C003ULL, 0xF1DA386C2180F0BFULL, 0x30ED75130166B4AAULL
        },
        {
            0xB4EAE361DDA879EFULL, 0x746A54AFCCC36353ULL, 0x3890DA1971F41A36ULL, 0x611321C1F8C838D0ULL, 
            0xE2D27C5544C8AAA5ULL, 0x408C5BB838DDB5FEULL, 0xDF8193E70B72FFD2ULL, 0x47730D8C14CFDD56ULL, 
            0x67E8F2859DC54ECAULL, 0xFEE417978080C0C1ULL, 0x45A9322D402E15B7ULL, 0xCCCD25C4B8246D40ULL, 
            0xA7F323FD3E9D170CULL, 0x2AEB82D70055D079ULL, 0xDD8B18126E6BA472ULL, 0x5F8A633100E8D9E1ULL, 
            0xAF9665BD3371C24BULL, 0x05E53DC97F0C6037ULL, 0x0D7257A26BABC5F2ULL, 0x92B95FA03BE4C574ULL, 
            0x43F8E26A3A73DF0EULL, 0xA5A7563F9BC0A6BFULL, 0xAC793CB1A2907261ULL, 0x682FA9B6783365BCULL, 
            0xCCEDB0EDACF7CCBBULL, 0xC93F882813BB928FULL, 0xDF46C711823CBB8CULL, 0xD01D6E6004F4DBDBULL, 
            0xBB59D21FF04FF843ULL, 0x0EB5EE25E79A3855ULL, 0x5F251D3BD48F3467ULL, 0x7B065C95B7B026A1ULL
        },
        {
            0x46522BEF664BFE32ULL, 0x5F4A273F27B61DBCULL, 0xC1C6076C34CFD112ULL, 0x63481292C8749C90ULL, 
            0x5942ACECD1B02109ULL, 0x6E15B5A2926B32F4ULL, 0x73F9F31B6CBFA556ULL, 0xFD7CE6DD05D7B86BULL, 
            0xC9B596A4AD1A81ADULL, 0x351F7D0DF53E3088ULL, 0x4BFBD58F229EE675ULL, 0xCD38212DC44C61A0ULL, 
            0xA01ADA712F7F9EAAULL, 0xA60FD2FFB783A9DEULL, 0xC3190281D0B05343ULL, 0x141C15024FE66322ULL, 
            0xA975F6F9A47183BAULL, 0xB266F4A79AA525B0ULL, 0x9AFD7CB2D88B706CULL, 0xE51CD263F6BAFA84ULL, 
            0x46AD64C732F5EE29ULL, 0x0F8AC72594A838B1ULL, 0xB21007CA58F0534BULL, 0xBBECA93F5CD9D4ADULL, 
            0x60C36EC4CA5A3A9AULL, 0x745E9E4F6F402CEDULL, 0x3636D833A354402BULL, 0xC030CAD3D7C9FF86ULL, 
            0x86E12A14CBD3F2A1ULL, 0x2F48F82048ABE89FULL, 0xAE9CE55401ED44F4ULL, 0x1591722DCB498BCCULL
        },
        {
            0xCBFF9EA5C67C4763ULL, 0x5711F94C74762233ULL, 0xFE2F8DF6A12AB7DEULL, 0x3F475F96A69AC9FBULL, 
            0x63B4E4F33B1C8948ULL, 0xCA59991293B4CB79ULL, 0x77F5460ECC927B0AULL, 0xB09A5C20B4DCA52FULL, 
            0x3A95A2E71A759944ULL, 0x704E9056D6B0790DULL, 0xA0670C5C26BFB10AULL, 0xF2056D548C02DA15ULL, 
            0xFA4D57861E4D875BULL, 0xDE3619928C9FF9E4ULL, 0x4DABAB8582BF7834ULL, 0x82B1C77721097CAEULL, 
            0x04961BF671783CF4ULL, 0xEAB947D14BC11C8CULL, 0x119D0FAC93AC1186ULL, 0x96FF5DFE087A106FULL, 
            0x9C7BC120D30EC966ULL, 0xF9B61319B5A445B8ULL, 0x9A2803E12A377662ULL, 0x9CCD9F780016B82CULL, 
            0x9F4FC19B22503B78ULL, 0x34348F851739D646ULL, 0xFB887F4229057D71ULL, 0x8C6E16461D6469DAULL, 
            0x180FAD43525A20B7ULL, 0x80F414771EF39C15ULL, 0x6B4DB048950D6187ULL, 0x9FC7748277598180ULL
        }
    },
    {
        {
            0x2CF0C440B5F6235BULL, 0x2629A289746472F3ULL, 0x5D6C374BB5B4EBDCULL, 0x586328684B92D2DAULL, 
            0x9DE889EE9E6A4D59ULL, 0x01A8402BBB49FAC4ULL, 0xE95F1CE3F5E6C1E4ULL, 0xB832A9AE584BC019ULL, 
            0xAB5EF39C93854891ULL, 0xF36DB1E998F5C847ULL, 0x513B626DF53C8F63ULL, 0x8EF15E7E6D6CE251ULL, 
            0x16FAA8AB993F761DULL, 0x875C391A94DD3F61ULL, 0x60C384FA0B19BEE0ULL, 0x6B4BEFF246CF8ED6ULL, 
            0x70F8C598E553B90CULL, 0x4A881BEF14A6D097ULL, 0x124102D17C97E256ULL, 0xACFF0808DA7BC158ULL, 
            0x72CAC66BD167C4D4ULL, 0x0D2B5935090166D2ULL, 0x0536F4D88C47B250ULL, 0x6DDF44C6380BB45AULL, 
            0x463A0CC47F325742ULL, 0xBFA4351272E7731DULL, 0xD685DB90CA80F575ULL, 0x89C4FEBFEEE8F96DULL, 
            0x4C8C56D7E42E4B38ULL, 0x60E8BD147657C6EEULL, 0xD9188A79136E26E8ULL, 0x93C52ED87610A621ULL
        },
        {
            0x8D323B78E4D89E74ULL, 0x49F0B608AE95A765ULL, 0xAFEB4828510A369DULL, 0x0FBCFC07BFEBFDA7ULL, 
            0x48B9358339AFF638ULL, 0x8007607A4B1036A4ULL, 0x852A047AD17A0E67ULL, 0x5578263FD386F3E0ULL, 
            0x05ACD23C4F639E33ULL, 0x5EF28CD7821A51E6ULL, 0xA6169F319D8EA502ULL, 0xF2905BD77A48AC89ULL, 
            0xD6ED67EBBDCC326EULL, 0x16603E9953117CD5ULL, 0xFCEC5E7EC0575917ULL, 0xEDDB5CB7F4D800BCULL, 
            0x53EDA6888CC7B9DFULL, 0xA2ED3E12F9AC3E2EULL, 0x72F05CC6B8B54057ULL, 0xD666FAFE2371D7C6ULL, 
            0x85851DBA82BE39E4ULL, 0x617493C891EAA075ULL, 0x7AB531264814DB18ULL, 0xF7EADCC6B710950BULL, 
            0xFFAE003F9B13E1B2ULL, 0xEA392FE2F262F8F2ULL, 0xE0854F322D2C8A62ULL, 0xCCAB7593112E2535ULL, 
            0xF8811955BFBEEEF3ULL, 0x5244F69F2B3F7BCDULL, 0x25F737DE0375C423ULL, 0x6563D2367F0B1174ULL
        },
        {
            0x330A8751BDD32225ULL, 0xBF65AD36F017FE0AULL, 0xB8C0C21FFF1833BEULL, 0xA378F5D0E810EBC1ULL, 
            0xCC1B487435BC907AULL, 0xCC2518AE44EC8BB9ULL, 0x396527A2D652BDDBULL, 0x747D912CE8FA9E2DULL, 
            0xD486E37810D7440FULL, 0x0038A116EA3138CDULL, 0xADDD33EEB8118A54ULL, 0x774D109F113A328CULL, 
            0xF326838FAABF7F1DULL, 0xB5598AF92AA18281ULL, 0xF69E1D5CEFBDF26DULL, 0x09A78419E755D15CULL, 
            0xD65EBE4764CE9F4FULL, 0x51AD72E1793D7761ULL, 0xA1B2B20F3515FDD2ULL, 0x768D8F63ADFAA5B3ULL, 
            0x0FDEF3228C401713ULL, 0x1482EEAB794A0590ULL, 0x694BC512037BB402ULL, 0x8864F18E2AAB00D8ULL, 
            0xBED5B5883A07D198ULL, 0x948334EA1B91AEFAULL, 0xA3C48E850C9CAEBCULL, 0x21A2BC224C3EDAC9ULL, 
            0x130BD122BF41450CULL, 0x62192DAD0A32A22FULL, 0x196AF1E057DFBA7DULL, 0xDC84BBEB64C5812DULL
        },
        {
            0x00BFA438EF6F6F81ULL, 0x90A0D714B6983CBDULL, 0xFF2574A9FA8D4564ULL, 0xDAC643C838879623ULL, 
            0x95B5656C280B6DE5ULL, 0xAAED7D283A24AA8EULL, 0x7FC139A9C727A51CULL, 0x392B3DC85E9BD7D1ULL, 
            0xFBA6F0957C1C7E3FULL, 0x7C91C04C0214D313ULL, 0xD04B7145CA2A3BCEULL, 0x2DD68A3428C11641ULL, 
            0x088035A7EECE31D0ULL, 0x0D2633CF760DE3E5ULL, 0xBCDD9C6E6DF76FC4ULL, 0x600004505BAAA291ULL, 
            0xBC379DAD71277C41ULL, 0xCBBC939967558E24ULL, 0x50E61CE01AF212D1ULL, 0xDE1BEAE58C1F4C9EULL, 
            0x2DD3472906E59838ULL, 0x4CD972D71EDDB2F6ULL, 0x9C0173BA2843C85CULL, 0x436E6D2F03F8C83CULL, 
            0xA78F9D90C6BAD01AULL, 0x10F43E77C58AD85EULL, 0x593A436463D72FBBULL, 0x493FAA34CE7BBC5DULL, 
            0xFE9E04F756151A6CULL, 0x46EF04EE90B4C905ULL, 0x9E3AC50143041384ULL, 0x8375A7B56E473D77ULL
        },
        {
            0x87523A60010027AFULL, 0x7F7E3037E8238478ULL, 0xBDE15AC4F8C13F9AULL, 0xB8200CE41389DEF1ULL, 
            0x8E038734A4229D55ULL, 0x3D1926D0D849307FULL, 0x85565BB3C26F550DULL, 0x8265A82BB1DBFB49ULL, 
            0xF8D75C288D6A33FFULL, 0xB0A28525ECF7ED36ULL, 0x1859880C51AE0D21ULL, 0x772205D2D371D9B5ULL, 
            0x762AA6FD972B217EULL, 0x76C4DD0C3A28FE87ULL, 0x9493BFE8A4ADD252ULL, 0xB5DB39562D66C04EULL, 
            0xA4D7F9B17752B5E0ULL, 0x0EA7E0F6A77518A2ULL, 0x46A11B43A05B55E9ULL, 0xDC9C46B6DB195551ULL, 
            0x957F977BA62B6E7FULL, 0x3D3D8137C5115202ULL, 0xE973C8951113E791ULL, 0x6323C224C45A96E5ULL, 
            0x8438434F9397E958ULL, 0x8571858D33D19745ULL, 0xF118854CC5D80E86ULL, 0x129757DE6D01AD60ULL, 
            0xC6A57BD772E23824ULL, 0x9978728B23F652C1ULL, 0xC89AE22A2B959039ULL, 0x4823AB63B18802B5ULL
        },
        {
            0xBE004F043E0F8AABULL, 0x36961F8C8C5953E2ULL, 0x140043F2B27E3CB8ULL, 0x83A0115333D94B0CULL, 
            0xF406CA15CF80242AULL, 0xC7213DA20A7BF5C6ULL, 0x9F8EE890C41A93FEULL, 0x16BCC1E166AC318EULL, 
            0x37AF457FBF4F8BF0ULL, 0xD343D7F8E596D419ULL, 0x24199E9895E442A1ULL, 0x9F2E1A0E426AB7E1ULL, 
            0x1F9CFD5B80EC0C18ULL, 0x10E8E29E595583EAULL, 0x851483698B52C033ULL, 0xBE21A20750D6D1E2ULL, 
            0xF5D73DF487160D16ULL, 0xA42F274CD7E7DEA2ULL, 0x28A339B5F98586A1ULL, 0xCE1FE6FE2EB99B7FULL, 
            0x89BAFB00B4DF43D6ULL, 0x274ED7038628451FULL, 0x018393E1FE451C28ULL, 0x5FAF9EF953923C3EULL, 
            0x7AE95BA79E4D8504ULL, 0x36FC1221FD659986ULL, 0xE9418778EC38B3A0ULL, 0x430569501217F484ULL, 
            0xE0F5E849FE142BA8ULL, 0xAE108E714C2D7B10ULL, 0x5906E1B2D77EBFBEULL, 0x737D212F30020210ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseBConstants = {
    0x570898C9BD439BFAULL,
    0xE32905AB8E31668CULL,
    0x81605044FE6F4075ULL,
    0x570898C9BD439BFAULL,
    0xE32905AB8E31668CULL,
    0x81605044FE6F4075ULL,
    0xFD5D04434DA7B357ULL,
    0xD2824477F4E1313DULL,
    0x0A,
    0x11,
    0xAE,
    0x75,
    0xC7,
    0xBC,
    0x71,
    0x37
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseCSalts = {
    {
        {
            0xDD600252E815ECECULL, 0x588AA4F7226596D4ULL, 0xF15CB3C2AB5791F6ULL, 0xF4C7990174AA4EA9ULL, 
            0xEF903A4AA82CE691ULL, 0xBBE28873AFC90AA7ULL, 0xA068DA8782D5B760ULL, 0xD1BB8586E6AA3168ULL, 
            0x84543383314B458DULL, 0x8C88A7CE500863C6ULL, 0x21F43B0AB1429446ULL, 0x5AB6760DF361CDB4ULL, 
            0x89DB399F22C48CD6ULL, 0x223DA87ACFE578D7ULL, 0x109568409FD84009ULL, 0x5FF9DDB4505423E5ULL, 
            0x42C6630B9276A832ULL, 0xE496CC0B31309E02ULL, 0x44E3DF607B0CF183ULL, 0xFBF0DC22A1149011ULL, 
            0x4E6B511442931741ULL, 0xA00F078EEA8C15A1ULL, 0x904616C6EA001E8DULL, 0x3CA0C6A8ECCE3B79ULL, 
            0xE1052F1822A380D9ULL, 0xC02F08740DA76DA9ULL, 0x79133D9BFD0F55ECULL, 0xAD77C091651EAC2DULL, 
            0xE50A1729A6B92D87ULL, 0x4AE25643DB5E0B9DULL, 0x81DB332E8F6215ABULL, 0x39FDE16689481A63ULL
        },
        {
            0x26D7A7750459F107ULL, 0x8C6583150C89F8FDULL, 0x78F53A39989376E9ULL, 0xC6156F2F5D0B045DULL, 
            0x9E50F1F70FB987C4ULL, 0xC58A397BB72E8C42ULL, 0x78C1311D42C985E6ULL, 0xF4A2DBBD72575247ULL, 
            0x08A63D9EC63A764FULL, 0x4CE077FB92512A62ULL, 0x7FCE06345E6DDC7CULL, 0x161A7056D8E6FFD3ULL, 
            0x22EA7F147D0651C8ULL, 0xE659B85156FC6AF2ULL, 0x7729D5C2ADFE4962ULL, 0xE23B53A7B8C717E1ULL, 
            0x2787A37DB0269158ULL, 0xD6FCF1426CDA3535ULL, 0x83755F794EFB61DFULL, 0xD8C4D0D762F76529ULL, 
            0x55FA7592D529C37EULL, 0x6D6C332EF04E9F12ULL, 0x9C022D39AE785714ULL, 0x165CBA4A5DCBC593ULL, 
            0xA5BB12A55CF263B3ULL, 0xA84C6664CBA743BCULL, 0x5306457E77327A14ULL, 0x9FDC09FD23AF4219ULL, 
            0x5D65194EB4CDC505ULL, 0x0C69A0D992F95695ULL, 0x7F7E627E84E2487EULL, 0xBA91599B676AC9A5ULL
        },
        {
            0xD4B004F524A48272ULL, 0xEB71628E2CC9D28FULL, 0x454B545CC918A23CULL, 0xCE8C22B8C04848F4ULL, 
            0x122BB6B327FBEC85ULL, 0x148FFD5A7BD3C34CULL, 0x680E6D7F7064E833ULL, 0x2E9FE226D4D8EC94ULL, 
            0x9D9B5D90F52B3B80ULL, 0xEE74F44D483AB302ULL, 0xD2D1784D8F394545ULL, 0x31AB7B8F26361EE7ULL, 
            0xD9EB03056D6C31B1ULL, 0x6C607514521804D8ULL, 0x9021A92D53C93016ULL, 0x073403F25FBF5789ULL, 
            0xF8D601E4033AB614ULL, 0xE1B15E1F7A8CA3F7ULL, 0x6CE1E28F5A344009ULL, 0x130BCB7C8DD37E78ULL, 
            0x74722B7E8A8EF6E1ULL, 0x226BB08A8E70F197ULL, 0x1762013D5BDA1743ULL, 0xBCA0D73575D6338FULL, 
            0x843E58051AAA1EAAULL, 0x1EF41D2965A856DEULL, 0x61E9678E2B505BAAULL, 0x42224751EA8461BDULL, 
            0x9E59F081E0594CBEULL, 0x2EDB3309B1EB958EULL, 0xCF70B88F40FF7061ULL, 0xA3138C1080D62496ULL
        },
        {
            0x22EFBAE9D67EB8F7ULL, 0xFC535EAD1925D0DFULL, 0x5D5A8875D0B114C0ULL, 0xB97C8885CBADD1B6ULL, 
            0x92CDABD5CAA6C996ULL, 0xD14926F412D31455ULL, 0x76F24615D7AEE0BAULL, 0x7EC20F947BC7D531ULL, 
            0x834FC1C65B0E8E92ULL, 0x5283B364B1F4CA1AULL, 0xA63B0DB04A27CFDCULL, 0xBD975974D95C9C64ULL, 
            0x3654C42A49C67837ULL, 0xA282BF04D932E7F1ULL, 0x3C9608203B80CF79ULL, 0x9AE5199DE69CCF87ULL, 
            0x9A2810CD0B1E7ABBULL, 0xE34258BB0FEF4B3EULL, 0xD1B5B097BF47C40BULL, 0xC48544DD69F15FCCULL, 
            0xA09F56CDF6F3CD96ULL, 0xFB7A337D9A061BECULL, 0x763493C18671BC2FULL, 0x138D4F059A375F94ULL, 
            0x521347AAE1C72695ULL, 0x490EF53A3D7DDA32ULL, 0x61B1EA4F202E7F3AULL, 0xEB8EB6BFD7D6B817ULL, 
            0x31FCB7ABB5FD165DULL, 0xDE313B61FB917896ULL, 0x2C5C55AE0951FE00ULL, 0xF0458192E8B01D34ULL
        },
        {
            0xFA2BAB16C755F514ULL, 0xF11079F2CCDE22F8ULL, 0x9B99C54D08E0241CULL, 0xAE5918E2202D6AD4ULL, 
            0xFF6CDE52B45BC7FFULL, 0x6958E2312BB95440ULL, 0x94FD415246679AA9ULL, 0xAFC676786CEA639AULL, 
            0x5A35BF58E2A70211ULL, 0xE5666161F0E90CCEULL, 0x773A6CADA815E54EULL, 0x31795AF9A191A4BDULL, 
            0xCE71B6D3FF417881ULL, 0xD98D7B03249C870AULL, 0xFABA3494744B6ACAULL, 0xE755DBBFC8F771BFULL, 
            0x2538AFD5D391FE55ULL, 0x6CB7EFFF6A2753A2ULL, 0xEA1CC8DF8EFE3285ULL, 0x1F48A3ED2104FDDAULL, 
            0xB9324E5FDD11F548ULL, 0x5D5F1D81DC0E053AULL, 0x7875426822A1F27AULL, 0xD10AE839454AE5B2ULL, 
            0x93A512602E29B9E6ULL, 0x8E6A0E884B534926ULL, 0x8BB779564F591BABULL, 0x608847CE2AC3955AULL, 
            0x12934AC5949BC82BULL, 0x1ECD4B9FA20247C4ULL, 0xFA66E4FE8493CCEEULL, 0x58035BB87E4C2491ULL
        },
        {
            0x0F733AEE0AC89176ULL, 0x69694FC2A422D245ULL, 0xDFFEFFB9E65F81F5ULL, 0x1E8680759F29345AULL, 
            0x35C01C6789BF8F72ULL, 0xDDEABA3E8CA744C0ULL, 0xC2B0CD6A0CA8835EULL, 0x55E9D23787C50C16ULL, 
            0x6051326FB158834AULL, 0x96DDBCAFC6380064ULL, 0xFDF2839F16734C6CULL, 0x1C6B879E86E7D88DULL, 
            0xC653C9A8141E5EB8ULL, 0xA8F1A4E95CBD66C2ULL, 0x9400DD05733A7BD6ULL, 0x0CA13EA762993198ULL, 
            0xBDF654653CAC1F34ULL, 0xAB5D8D63D35A0647ULL, 0x91941D855C986DC4ULL, 0x75057D1D339A3F84ULL, 
            0x0474AF408B10FD51ULL, 0x2F78C7E75E0C4BEDULL, 0xF42BBE70DF26C40EULL, 0x8B24FA49E4D1A89DULL, 
            0xBA2828C02D493C69ULL, 0x9A3070F9C9915B03ULL, 0xC1A7EA16D9771D2DULL, 0x3E3039D8BB5AC730ULL, 
            0xA535FAD95C1C048AULL, 0xF5C54B1D108455C2ULL, 0x741BDED5B33A390FULL, 0xB5908A2CDCA581D6ULL
        }
    },
    {
        {
            0xBE91366D185750B3ULL, 0x02C44A64DB0BC623ULL, 0x2869DCEFE7E35AE1ULL, 0x943D6112FA7D4C59ULL, 
            0x25C756AB7254A119ULL, 0x8FB0703E31509416ULL, 0xB66F1AF63DB888C9ULL, 0x7368E2FD9A4FFEA8ULL, 
            0x900724B2510D4711ULL, 0x92D9B9673115736DULL, 0xDC24C125689EB080ULL, 0x3DB4F42566D54206ULL, 
            0xEED42D8BC3B749FAULL, 0x9C86B78DCA003110ULL, 0xB4A4669335345194ULL, 0x4850291CB53E819AULL, 
            0xC2B1BCA7FF160DD2ULL, 0x3F25197A1A3AF115ULL, 0x760261175CB4F805ULL, 0x48219AF38AC8D9ABULL, 
            0x0BADABD74601726DULL, 0x651FE702E403BCE1ULL, 0xDA68017FACFA781FULL, 0x8C7117457E3119DBULL, 
            0xFD82F65A0A79DC41ULL, 0x2D66C59434B9A1D9ULL, 0x9EA00E5751493482ULL, 0x3A5D1857C06A21DFULL, 
            0x8E22489F1ED3938BULL, 0xE59C687D84616047ULL, 0xA24D0820DC05DB69ULL, 0xAA72E6624621C28BULL
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
            0xA0A9E94BE0239BFAULL, 0xBB826A00B7455DC3ULL, 0x94A7E684AC8D1ACCULL, 0x4CAD805DE7132EE0ULL, 
            0xE5F690DC680D4CEDULL, 0x5807BF486571AE3CULL, 0xC9D4DA86C878C044ULL, 0xE9DBBA896995274DULL, 
            0x05D3F26205DFB2F6ULL, 0x96C42FB2BF3311E4ULL, 0x3F978DCF26F4A12FULL, 0x0A771C2833ED1F3CULL, 
            0x073A99BAA1B1C9C0ULL, 0x4EA25CE6B4A070E6ULL, 0x6148F538194DE0D7ULL, 0x3BE07CFBEB219E65ULL, 
            0xDA035C46D7DCE042ULL, 0xAEA709245309FFA7ULL, 0xE4269EED4115C494ULL, 0x9B7834F88D665534ULL, 
            0x7FA3785479A8AC13ULL, 0xAA29C15B97CC0E54ULL, 0x08BB4684BE110500ULL, 0x21A1D118150F9B9AULL, 
            0x5AB4C45E0005144BULL, 0xF409E191F2AB0D10ULL, 0x26EA16D95FBB8E5CULL, 0x161E8DB2E3590898ULL, 
            0xB32CAE9C461E61D6ULL, 0x57F5FAF876F39663ULL, 0xC674B9F43C2DBA99ULL, 0x154BDAD7FC2ECB57ULL
        },
        {
            0xDB2E7613BB1AB876ULL, 0xC4532B5937B3099BULL, 0xEE5D2820EB53D6FAULL, 0x8A3A78DE528261CFULL, 
            0x2C1FDB43D7663342ULL, 0xC2C35155294FB8A5ULL, 0x7FCE2E98CC83545FULL, 0x999CF7FD49107B61ULL, 
            0xD01CBEFC2CDC1EBDULL, 0xC1AC2D230BED3AA0ULL, 0xC160FDF5A961FDDFULL, 0xFB920E16916EDCCCULL, 
            0x476984A1E4495244ULL, 0x8F1DC403D0019FAAULL, 0xD313E6E27C105C4EULL, 0xE8127E6141BB0842ULL, 
            0x17B0E9E5DF97C3C9ULL, 0x8850F1088B92D753ULL, 0x330364FA8488C2C0ULL, 0xAFCE9E0E21F7D023ULL, 
            0xBB9033E16832C40CULL, 0x6054E6AB0C47225BULL, 0xA1990644BC2E1EEBULL, 0x12BDFFD96203E8A6ULL, 
            0xADA209BCFF8A75C1ULL, 0x75E89F8DB11380C7ULL, 0xEF207157F6CFE535ULL, 0x49B9D1E67A2BCC4BULL, 
            0x0C554C2BC97DCE03ULL, 0x5488D98E5B5A575DULL, 0x8427C2CFF4E46049ULL, 0x08415790F0D6BBEAULL
        },
        {
            0x0FB486CEF8D94424ULL, 0x9E137B4CABE76246ULL, 0x6D333F5670ABB000ULL, 0x7C0EA1C82C77D799ULL, 
            0xB43B90ABE47EDF37ULL, 0xF407F2B2E396ADBDULL, 0xF61619BE66B3878CULL, 0x70596A18554F20F4ULL, 
            0xA9DE257D281A43B2ULL, 0xECF56B6FA9FFEDB6ULL, 0x688CAA0ACB9492A8ULL, 0x68C292EA93CD4E7EULL, 
            0xE31B60E6BDA21120ULL, 0xBF402A164A8FE748ULL, 0x4CABE2E1EBD4C14AULL, 0xF357EC9E1B653AA4ULL, 
            0x1A38D60A0E2E055CULL, 0x7460B9029F8232CDULL, 0x59A4B5CCB607F866ULL, 0x13DE0AE6BA4D7E7AULL, 
            0x3406571A07DE9E56ULL, 0xB37709B6B899BD4DULL, 0xD90956A7DA39197BULL, 0x6E677C51E5E392C9ULL, 
            0x43B4FFECF8DBCD45ULL, 0x6A5C6DF44C273D7FULL, 0x98305ADD790AD59FULL, 0x498E7C27085F269DULL, 
            0x54B740CA144B78C0ULL, 0x60C6CA55279E6E71ULL, 0x4D9564F970384BC7ULL, 0x62561744BDD122E8ULL
        },
        {
            0x07DC9450D085A1AEULL, 0x9D6EEBCDB1FC5E13ULL, 0x1C05B5C51282E97BULL, 0xCCE92D15A7047E74ULL, 
            0xEA6D7F0F55C151C2ULL, 0x7EE02D6F53DDB76BULL, 0x23E49FBDA7BA8046ULL, 0x477AB14AF813AD2EULL, 
            0x28EF4E85AC4BA75AULL, 0xE4B9AF7F72E09DB8ULL, 0x9F70046F548D4F23ULL, 0x749B52824C3E7CD1ULL, 
            0x9EF718914969C1FEULL, 0xF196BBAB3B6FC12FULL, 0x5BB1E5DBB9B1F7EDULL, 0x39FBEE1F12012836ULL, 
            0xBB0CBE2DD77E1B81ULL, 0x8866305A1AF690CCULL, 0x4CF211504A6BDE7CULL, 0x9D6F575E3708E01BULL, 
            0x15DC536F75B4A184ULL, 0x130113D9C2DFC683ULL, 0x04E92957C9759F10ULL, 0x095BFE4F4B92235CULL, 
            0xA727ED4E714A8544ULL, 0xF8EF870C82549570ULL, 0xD4E141DF088BE5C3ULL, 0x68B0BDB48F63FB91ULL, 
            0x703308A62CB61C73ULL, 0x6AC693CABB478F59ULL, 0x823A3BB1CC0DF88CULL, 0xA1ABB8BD930A5B8DULL
        }
    },
    {
        {
            0x227C3EC84215A296ULL, 0xC3E216FD7F432E65ULL, 0x7985D8AF35F96D4DULL, 0x62DA9178CC534606ULL, 
            0xC1E5CB297193BAFBULL, 0xDE38CB9C37729E63ULL, 0x8E449944B4BF4BA7ULL, 0xE397624A5158BDD3ULL, 
            0xC3CE417B0D42815FULL, 0x304F3F34658811DAULL, 0xD3C41FD5A139D9D9ULL, 0xF3D6CCBBFB463AADULL, 
            0x6593978754F8BCF2ULL, 0xCEB4199DD0F0AD1CULL, 0x34DA1DA8A0B1DED8ULL, 0x7B50B7EFDA631E55ULL, 
            0xAEA445148F749E5DULL, 0x2A57EC2FA137FEA6ULL, 0xD8487B249014B7C9ULL, 0x5F15A0D3D001B6D4ULL, 
            0xB788E3A22FE0C633ULL, 0xB652BF6241164C82ULL, 0xB9CF840262CBEDBBULL, 0xF5C0A5A6B18BBB2AULL, 
            0x28C9CE66BC4F8DADULL, 0xC566B5E77244255EULL, 0x6E8EC815C3032A31ULL, 0x3B10EE187E6D4330ULL, 
            0x8114DB099203D3E2ULL, 0xAE55D3E9B3A0331FULL, 0xA7E6606EAA0D02B7ULL, 0x94B0A7A38560A990ULL
        },
        {
            0x5889D71057248596ULL, 0xEE229998CEE72F91ULL, 0xE2C091DE0416D470ULL, 0x275E1B94C6C37EA1ULL, 
            0xAF37FC7E5888C683ULL, 0xECD2DD51A4E6DB87ULL, 0x2C630ED86A14BE50ULL, 0x251B140A974E8A4CULL, 
            0x3E441FF2253DF2EFULL, 0xA7B6E1D506AFA730ULL, 0x536D3C7DDDCA0586ULL, 0xCED929D2133F2954ULL, 
            0xE815C93969167819ULL, 0xC25BC70AD7447052ULL, 0x61AA9F684172814DULL, 0x33B8D10740D4334FULL, 
            0x3EC82218B6D13C7FULL, 0x86BCB4612A903F17ULL, 0xC9C81CDAE22FA318ULL, 0xE03C16FFD4FC959AULL, 
            0x3E5FE5D238951EDFULL, 0xA6B8F4300432190FULL, 0x92D83BB24213D58DULL, 0x795DE626131AAE0FULL, 
            0x16C0E7B21893063BULL, 0x639CB913921C03A7ULL, 0x6655B8E6AA9AB815ULL, 0x1AFB269A8F3E1DDEULL, 
            0x2B94A441B7CEB0A0ULL, 0x67E26F8F4A9C3DBAULL, 0x7AE43151B909611CULL, 0xB4DA51DFCA371E67ULL
        },
        {
            0xDAFA64FA7420E421ULL, 0xF5585C2CB1B63CA0ULL, 0x33936352E5A96F05ULL, 0x7184D32108E0B3ADULL, 
            0x1F83AEDAFED4F716ULL, 0xC7658CD1C577FC1EULL, 0x9D511EC8FC83A69BULL, 0x5D987E131E4871C5ULL, 
            0xB2BA24D27A4E543EULL, 0x890521754B14537BULL, 0x4CEC31C12459E89CULL, 0x0C12A4C4E549C914ULL, 
            0x277580019C16D7A6ULL, 0x5728635F4A6CA50BULL, 0xF8CFA74A32579889ULL, 0x0407316CF74E487EULL, 
            0xE66181B484F3FB97ULL, 0x936C359E531ED318ULL, 0x2CAA46C3F4C8CB1CULL, 0xE7A233EEF20F0D6AULL, 
            0x3D70797F2BB24285ULL, 0xA794696CDD5F9F63ULL, 0x1546F3525D8EF081ULL, 0x201DEB47B2114BF7ULL, 
            0x0B71811B02CA1B76ULL, 0xBBD20973E691360DULL, 0xD3C4C281CCB2ACABULL, 0x056DB55B7043875DULL, 
            0xB3A97BC5D5462F0EULL, 0xFE03F3D2C3E8D8FDULL, 0x2CCF139338BE0B22ULL, 0x88D152E2696D9232ULL
        },
        {
            0x1A340611EE62EE62ULL, 0x63C534AD6DEF1567ULL, 0xEEF7027ED3102514ULL, 0x518383042D1151CFULL, 
            0x92925846CCC73E90ULL, 0x9C2D86B6493E37FAULL, 0x2C83889C3F6B7E65ULL, 0x7A0FB7E434543162ULL, 
            0x065B30DE7B3672C9ULL, 0x461C165A5321A294ULL, 0xB72E3E9EBD76C99CULL, 0xDCFE247B4A874690ULL, 
            0xEA777B1FF37C8695ULL, 0xDA4D485832559FF5ULL, 0x95955CA579D1FEA9ULL, 0xD55D3C48885B13BBULL, 
            0x29C2AAD085C51954ULL, 0x8D5D53CDCD267630ULL, 0x4F0085E9657EFC84ULL, 0xACF19475CFBA238BULL, 
            0x3A3520DDAB15BDBCULL, 0x829E5B7EE84D39EBULL, 0x632453454A525FCAULL, 0x86C7081C5CF90F93ULL, 
            0x05A63E4E4A70B9A8ULL, 0x701D4677E0C9F31CULL, 0xB68E0CB5F468CC63ULL, 0x3C91DD80E132D2D3ULL, 
            0xC2DF93584362A029ULL, 0xF5CF49E97D1992C7ULL, 0x0B7DDF0083DEBE89ULL, 0xFAC8542E209DA278ULL
        },
        {
            0x8A2F372D9D22409BULL, 0xA124F01378A2206EULL, 0x5A1454A3983F3877ULL, 0x7229A2E7300E6D63ULL, 
            0xD1543A1EA67F2F26ULL, 0x692200CB30E48A2FULL, 0x7D479E2D514782C0ULL, 0xD67D386B4A18C340ULL, 
            0xF9CD6AF8963D5716ULL, 0x819CF73D857A0AB9ULL, 0xDC86ACE1421117FFULL, 0xFCDDE02076E0319AULL, 
            0x694356E44A0BB4E8ULL, 0x825B8B5EE00B028DULL, 0xEB2FE293F1B59831ULL, 0xCA2AEF11595CCC5FULL, 
            0x6956A3835F76DC87ULL, 0xA7A22FE52A527BEFULL, 0x443E06B521F6018DULL, 0xBF2BDA606E8E0CEDULL, 
            0x66636F4A5EC4D7B3ULL, 0xD41681BA195CF7A8ULL, 0x2C804D8B6401C258ULL, 0x33775561AAED699CULL, 
            0xAB72A18B13D30279ULL, 0x21A32AB55C910DCDULL, 0x905B152386F15FA2ULL, 0xA8B496D0ED0E0F9BULL, 
            0xEAFFED772514AA99ULL, 0xFCBAE0A5D7BA4144ULL, 0xDE89A3B8755081A3ULL, 0x6D8F4623945FC877ULL
        },
        {
            0x2FAA980E6222F19EULL, 0x9F1DB1CAAA5F864AULL, 0x565C8ED3DB835BD9ULL, 0xA89EE08D09FF5FA4ULL, 
            0x05FCF73AD9C99E1FULL, 0xB0345F4A389ED6C6ULL, 0x2059F043A5DA5039ULL, 0xA0CAD99B92B60DDDULL, 
            0x0FAAE499741C8EC9ULL, 0xD2A222CEA3EC3173ULL, 0x5CA15A5E27C61213ULL, 0x8B9D930D2571F643ULL, 
            0xB9422179236FFD84ULL, 0x90217CD43F367925ULL, 0x12AF766A4F19E4B5ULL, 0xE6CFF157FDBBCD73ULL, 
            0x5E57B68C10CF3FA3ULL, 0xB5EEC8CD120A4169ULL, 0x30F050EAEA3CB440ULL, 0x86183965903265A9ULL, 
            0x2CAA0D72F1DF932AULL, 0x394FD840019CA175ULL, 0xC6397676C8191D5EULL, 0xCF0425A5D8DBE83FULL, 
            0x776BD5F83B787C86ULL, 0x3EED9954F93BCEB1ULL, 0x2AFE33D1DB2BD069ULL, 0x327AA618CD91D25AULL, 
            0x0DA432A387D92464ULL, 0x75BF4C36796BC71FULL, 0xB47F443C17F02DFEULL, 0xA474734FA5C2AB04ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseCConstants = {
    0x439973EA24319720ULL,
    0x4FDAD7A633484433ULL,
    0xA8FB7521C6719EF0ULL,
    0x439973EA24319720ULL,
    0x4FDAD7A633484433ULL,
    0xA8FB7521C6719EF0ULL,
    0x5A008A8D5271C472ULL,
    0xFE1B7D42CD71A171ULL,
    0xA0,
    0x55,
    0x1C,
    0x10,
    0xC3,
    0x0E,
    0xFF,
    0x1B
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseDSalts = {
    {
        {
            0x9BAEF9953C32F557ULL, 0x1C37734FE2D89EE4ULL, 0x93D799CF6C96C093ULL, 0xAFF04103E6C0C164ULL, 
            0x65C0BAE7419A4880ULL, 0x401215A6EFAD3C50ULL, 0x344A4190B6F9C785ULL, 0x07FAC8634DBC8B8BULL, 
            0x54E434F7EFEC983DULL, 0x62D973EFF87BBCD5ULL, 0xF5002370EADE1E44ULL, 0x90802D596C9482F4ULL, 
            0x33CB5CB735E1C919ULL, 0xF9BCB292AC6A990EULL, 0x5A70FFA6DC5577E5ULL, 0xE73AF259BFEAD402ULL, 
            0x46F55708A19FF6F9ULL, 0x5C0693C20FAF2CA0ULL, 0x648A3CD1A6F20ED7ULL, 0x77F1525ACDFB2CF1ULL, 
            0xC7E3DBF46807B932ULL, 0x66696BE091E34A7BULL, 0x11F8054BC4A43421ULL, 0x21FB27C05D2A3547ULL, 
            0x40AFABD4E9FCD7FFULL, 0xA4D1F9A75D3AC7D2ULL, 0x114F57CD4078FB45ULL, 0x0C8799E0AF6B4DF0ULL, 
            0x5EBBE5D7D08E0B21ULL, 0xA6AAB796A846D54AULL, 0xA092248AF56C2C88ULL, 0x7A81D70383436ED8ULL
        },
        {
            0xC2E17EF6FFD1CAC3ULL, 0xD69FD3936F49C925ULL, 0x01804D2AA8E59998ULL, 0xD21626EDC27CE6E2ULL, 
            0x9071598DF9846D12ULL, 0xC93B3B4CA8CE7252ULL, 0x01A04D540EC249D2ULL, 0x283BEDACBE79E4F5ULL, 
            0x42191B061F54CC0EULL, 0xF6CEE018EB1FB218ULL, 0x983062A6B19417DDULL, 0x8A8081CD5FB976EFULL, 
            0xB98B40F1EB87CE1CULL, 0x54017862CCC42055ULL, 0x61B3B5858729D68EULL, 0xA822E886FF90EA78ULL, 
            0x348BC4DFA6A29CADULL, 0x66AD6B4298C802F3ULL, 0x6D6528FF9A8831EAULL, 0x916507FFC4C6EAFFULL, 
            0x181B6D562252B782ULL, 0x1D48F2EBC4F46D97ULL, 0xCEF55B6AE5D87782ULL, 0xDD11F02F551A5524ULL, 
            0xB1822628097FDA00ULL, 0x01D5FE726F5AC922ULL, 0xC710FC6ABD297CE6ULL, 0x0E4E0A8A4CA5BB55ULL, 
            0x8385FC166216D219ULL, 0xB88E96A5C3DE8133ULL, 0x976C826A3D85E0D5ULL, 0xF3603B0936079328ULL
        },
        {
            0x01A8F04560DC9F24ULL, 0x01A27A8C9481E797ULL, 0xF96A4E792449A905ULL, 0x79DB376F02306C1DULL, 
            0x55F61F534A9462FDULL, 0x5AAEA31DEAF49288ULL, 0x42320E75F00EC217ULL, 0x8AEECDFAA6167E1AULL, 
            0xC85DCE5E808824CAULL, 0x792408D39017B0A8ULL, 0xDC01F47124BE2A57ULL, 0x622CA2CEDEDB5F85ULL, 
            0xB2855B5B8AA84906ULL, 0x25DE5F1BEA798A96ULL, 0x28C3064C41AB50CDULL, 0x0EC64DF993E92A91ULL, 
            0xC78BF008AEB8AC77ULL, 0xD1BDD7E5FC4D9077ULL, 0x69133BFCF9538D36ULL, 0xDD449FAA10E97CDEULL, 
            0xC723019734406DB3ULL, 0xFE74B8322F6199E0ULL, 0xD099AB62A3AA42E1ULL, 0x03DA0E8FFE7D4E61ULL, 
            0x28AF9F8D583D59BEULL, 0x9E1F4AF29C5A107EULL, 0xC969FD8520BBB518ULL, 0x9434C5E0B9242E1DULL, 
            0x2C759262AD87C059ULL, 0x5BCA34C2BA499A4BULL, 0x4D604CFD950301C8ULL, 0x023114FEC6725650ULL
        },
        {
            0x2A67232896688754ULL, 0x7754957B94B87551ULL, 0x597B3DD3A4049460ULL, 0x6ED5345C5C30EE92ULL, 
            0x0FAAF0945A985494ULL, 0xFEECE6F98C3DCCB8ULL, 0xB3C76A1AFD46956EULL, 0xC9A601EFE282015EULL, 
            0x052A0435C3CD2206ULL, 0x86BF0BFC209C16BDULL, 0xCE3E8F32B202202EULL, 0xD20504655EE134C3ULL, 
            0x030C7FCD9F5DCE4DULL, 0xC7B08F09A26485BEULL, 0x2D8046A204FA2550ULL, 0x5A9182304CDEBB34ULL, 
            0x8803B1715A0CE7C9ULL, 0x120EE8D4C79A5DCDULL, 0x7FBF114DD8222202ULL, 0xD123DF88B7E33812ULL, 
            0x38EEB1FCDA72FF8FULL, 0x2FB3973F5E1D855AULL, 0xCC55E173B863B409ULL, 0xD101F8D6AE120E6AULL, 
            0x504A643A1DD75A9FULL, 0xC05AA0CC897BDE7DULL, 0x9CA8E16D33466361ULL, 0x6C442AC58666E452ULL, 
            0x29D9F1D393486EC6ULL, 0xD958AFB7005B06C5ULL, 0x242D704E54D83C43ULL, 0xF4C5EFE4B2EC60ABULL
        },
        {
            0x656EB24C77C518E0ULL, 0x8838D315E4033DE9ULL, 0x72EEB42F53D5BAC0ULL, 0x3B4B293EF6986752ULL, 
            0x7D8A5F788963EAAEULL, 0x978B939706B37593ULL, 0x130A92F20EA10E89ULL, 0x7660A724C2DD7AB3ULL, 
            0x79C519BB9616E8EBULL, 0x930E3BD2DFCC1F7FULL, 0x5D3B0B303A167556ULL, 0x5B4768C789E32407ULL, 
            0x00D86DD02D5C5B50ULL, 0x7FC520AF475D3E66ULL, 0x132F6A77E45619EBULL, 0xDF926C0B5C3755B5ULL, 
            0xA894122405B6E455ULL, 0x1029412503FA57ADULL, 0x1A6F9D919534E06FULL, 0x1A3F6727EF200B54ULL, 
            0x778EE15416605E12ULL, 0x79CB2FFC13AC6319ULL, 0xF9E73B72C802353DULL, 0x6723140CC12C9090ULL, 
            0x900D6DC9D8E63B45ULL, 0xBAFE5C06FC672F48ULL, 0xE3D2DD138397AD9AULL, 0x9C02647D6B497DB4ULL, 
            0x915FE58465F0C2C3ULL, 0xB80032A15EBA4138ULL, 0x7D6529B88592ECFCULL, 0xBD05082DF912BCDDULL
        },
        {
            0x0BB098A47BEB60C7ULL, 0x0ABAB1E08508458AULL, 0x35CEF383514A5C2BULL, 0x55B82ABD47D3B837ULL, 
            0xBDC5790FFB32C37FULL, 0x54EBDD2170AC3774ULL, 0x70401B360A6D051BULL, 0x6EAA99C4C6289646ULL, 
            0x288B557F75C3238AULL, 0x85368FEF4306BEAFULL, 0xF899725293941C40ULL, 0x2D0515BE7A6C9B85ULL, 
            0x4EEA9DF6BD35D8EFULL, 0xF6824B7207D31FCFULL, 0xBFCDEB94986056EFULL, 0xD797A0EFDFC0A393ULL, 
            0x0F35A958726E1C32ULL, 0x4B2AB761081E13B8ULL, 0x69228D21093D2A67ULL, 0x615D23F3B96ABC40ULL, 
            0xACE79B45C2EE7BD3ULL, 0x7A3AB2DF3DD67A9EULL, 0x4806616871863961ULL, 0x0614BA07E951852FULL, 
            0x8ABC54875550B818ULL, 0x29C5F06331B3734AULL, 0x63856CF4FDDBE21EULL, 0x6BC971832555DB73ULL, 
            0x27F0B000F54BA41DULL, 0xD419C0130DC80ECDULL, 0x16B16B1195D16FE3ULL, 0x89EF35A1A91470EBULL
        }
    },
    {
        {
            0x716D1FE1F72EBE3DULL, 0xB19A4D5632A15499ULL, 0x4856209A0CFBCBE7ULL, 0x4CEC84ABA5F5D4DFULL, 
            0x342C149C4E157D75ULL, 0x8777824EC71D3D60ULL, 0x6FD656C53F4C6229ULL, 0x6EFE096D94369444ULL, 
            0x1568841AB068F2CBULL, 0xFF70EB08AB1BEF2FULL, 0x59033BE71DE3D9A6ULL, 0xD431BF7CAAB0CD4AULL, 
            0x333706B24F5D174FULL, 0x16510F87B10CA5C9ULL, 0x8417B8DE7B7003A7ULL, 0xD4594176C3BFA01DULL, 
            0x2B149B47317C6EA2ULL, 0x9B4C7B2FF0D7C985ULL, 0x2EB264D46E46FDEDULL, 0xB38C691BB68F86CBULL, 
            0x8C50C5692E66FF57ULL, 0xDB46591F2AD7DE0DULL, 0x516D513F66AB5A67ULL, 0xDC402B05E6CDE043ULL, 
            0x8077FE457EDA775FULL, 0x2B90932D9CC7734DULL, 0xE8C8615C41ED38CFULL, 0x8E16EA58729A2B3EULL, 
            0xE9A723FF1602CF88ULL, 0x4A7A7A57295781DFULL, 0x41671B1CFC11C13BULL, 0xCFABD0B101390346ULL
        },
        {
            0xCC81504EEC0D6467ULL, 0xFBB4E708FFA563B8ULL, 0xFBFEBDEA4309B38FULL, 0xFEDA82AA1C238B2BULL, 
            0x07D59239757FF902ULL, 0x0D31AE4F591F7D12ULL, 0xE82F4BBA57C3F9FBULL, 0x8B9BDDAF659FF50DULL, 
            0x9DC346855D6C114BULL, 0x46C15C4057EEAD90ULL, 0x35FECACC2FFAC22EULL, 0xEFA633A04C1760C3ULL, 
            0x7D95BA9C0055DCC7ULL, 0x9B918485CBE4976BULL, 0xF56AF3E83301C4B6ULL, 0x8532D3F5BFD9CD25ULL, 
            0x25545DDD3946A8C9ULL, 0x5B941FBBC36E8ACDULL, 0xE89A93BC2959CD9CULL, 0xD08B30B9572847DBULL, 
            0x90E22366D87C871CULL, 0xBF8EF9D4E848AD82ULL, 0x625387FF9BBC1907ULL, 0x609C487E96426ABAULL, 
            0x11545906CC25C0B6ULL, 0x11F0F44DE9EBF3FDULL, 0x2DF0EAA0AE497CBEULL, 0xD96D844CE01FFB26ULL, 
            0x03819A04E06CC28DULL, 0x54A0873B7A5D80E4ULL, 0x1785E6EC5F32140AULL, 0xA4A1C826FEA72200ULL
        },
        {
            0x5E5DAB976F513256ULL, 0x3884479CF49AB069ULL, 0x7C414D930F0719DFULL, 0x02EE0D755DF6F93BULL, 
            0x8862C22FBD3BF730ULL, 0x82F52F1F952E66AFULL, 0x11C38E235CBFF755ULL, 0x4216FBC89910CB8EULL, 
            0x0798F66B604CDA5CULL, 0x1C8D22D75248DE07ULL, 0x58071EBE41A58D61ULL, 0x423DD79F3BA41298ULL, 
            0x511DA2A5B5A4A306ULL, 0xFA52152849621687ULL, 0x4B341C7751FCEF24ULL, 0x0525F02DEF024D00ULL, 
            0x9FB09BE7D636F58DULL, 0xF2F7E13892C305C0ULL, 0x9EC381A3FDFACF67ULL, 0x396C08169825AEDAULL, 
            0x90619C0A91886CA3ULL, 0x1C229896AE9227FDULL, 0x11F7BBCBE5966679ULL, 0xF63857611550C6E7ULL, 
            0x6E1E681A17F11341ULL, 0x9E3721DFF9FC8388ULL, 0x9072C9D525E9A50AULL, 0x352BBB751F44F2D6ULL, 
            0x21A25A375DFEF935ULL, 0x958BE306BC07C89AULL, 0xBF8CC0FA2E794B37ULL, 0xEF6C222EA24CBB5DULL
        },
        {
            0x0A3D0741D9CF0650ULL, 0x61249A2E3E9BF4F7ULL, 0xF3A5D59CAA1D0291ULL, 0xC6E743C4144861FAULL, 
            0x06B1763A8CAD7302ULL, 0x0A79E3DEDDDBB72BULL, 0xE0C93F1ACCFF26ACULL, 0xF14462EB0980381AULL, 
            0x51E25FFFCB9A7474ULL, 0x1638FB2441ED97ABULL, 0xAB36542C4E4AF9D2ULL, 0x5AF335214439F530ULL, 
            0x00DE5AA7344BDF3CULL, 0x92A56DCD8AC82736ULL, 0x4240344F3F3426D6ULL, 0xEBB679BE29BA07ADULL, 
            0x4FFBA91A297915BBULL, 0xE4891E8FAE4E4D2CULL, 0x3382071F56C03104ULL, 0xAA1B3D9DF82DC6DCULL, 
            0x24600928CFAE2A93ULL, 0xDA3D69510800EF50ULL, 0x68B5C5E2870A1AE9ULL, 0x1DAA01EB8C6B774BULL, 
            0x7DC74C7E2B8F2B51ULL, 0x3BD91252074F45C7ULL, 0xBDBA45A7E7ED0BD5ULL, 0xFF921B46214F80E8ULL, 
            0x0D4808B225BE06E0ULL, 0xF66F9E9AEC816234ULL, 0xF3815073C632975BULL, 0x79E821CA86C84231ULL
        },
        {
            0x8EF321452A15D748ULL, 0xB5C8A8E311DEB22EULL, 0x37F16CA7D0E9DFA3ULL, 0x1F91349368BA021EULL, 
            0xC31D0A04F4550207ULL, 0x7C68A6033DA1008CULL, 0x563B5671F2687454ULL, 0x2553ADD788976329ULL, 
            0xB8AFF3E8C9AD6ED1ULL, 0x0EB83B2B8D23B133ULL, 0xB46CD701070C43D9ULL, 0xCC03EA80748E876BULL, 
            0x4DBDA2E9FCF129DEULL, 0xD5F879CA74075EEAULL, 0x61F00BA1EEE10E20ULL, 0x53F393ED0AD988F0ULL, 
            0xFB1A201598046378ULL, 0x7F82DE30441A5960ULL, 0x93E881204E9D2505ULL, 0x322E4E39A9E18B2EULL, 
            0x67C26677BFF6BE0FULL, 0xC2BC224D7F1302AAULL, 0x21B953E1D5AB3D70ULL, 0x9382D6A49DD77943ULL, 
            0xD32280690742F954ULL, 0xE5D0AA928C669D4EULL, 0xA59EC522F6EE10E8ULL, 0x7B7F14E290EBDCB9ULL, 
            0x16C8E883B0FEC764ULL, 0xEC0E34FA153239B8ULL, 0xA8DA4259B579EDC5ULL, 0x32870EAB40440B57ULL
        },
        {
            0x0752C62A2B24BCB5ULL, 0xB1D9CD421F93395CULL, 0x4979A4C4FE78E654ULL, 0x1D8608785331C9FDULL, 
            0x6D4D5C860A64371DULL, 0x1E59E5F8E0EB72A2ULL, 0xBA449BC65422D259ULL, 0x12D10E32D3E2F50AULL, 
            0x5ADB2D34A0772B6EULL, 0x1DFE669F5E53CA85ULL, 0x5188435048C8672FULL, 0x39D9B90AA10ACB5BULL, 
            0x01F4411850A9CFEAULL, 0xB3448DEF99BC8794ULL, 0xB136F15729414E87ULL, 0xA36DF3FD45A402FDULL, 
            0x8B8EED09EE6C92A2ULL, 0xF1A178CDE3310443ULL, 0xB32E95EA2A59B3CEULL, 0xC6AD0BE4CF381788ULL, 
            0x2C05DE1A57D1805DULL, 0xE52411AF0606F9A8ULL, 0xFBCE0F6010BD0C9BULL, 0xBB63D8ED61251D8CULL, 
            0x35122A1DAA534E30ULL, 0xF7BA5B77A085884FULL, 0xED4A16112D697D1BULL, 0x471148F0ED81F2A3ULL, 
            0x98F7F1C05B763BB1ULL, 0x12004E7787F23227ULL, 0xE0CE2F10C63462DCULL, 0xC8000EF285D3234EULL
        }
    },
    {
        {
            0x5A301DFB9C4B5B39ULL, 0x5B6C42B4C32AECEAULL, 0x74D68354FC181781ULL, 0x412A2532420F0E39ULL, 
            0x0775315EADF46B68ULL, 0x04950534AB439D12ULL, 0x303156B18574FBC4ULL, 0xC27C27B071B59038ULL, 
            0x8DAFB3486EBFA0CDULL, 0x7C68A448915266E5ULL, 0xEF944A260DC6068EULL, 0x1CCD8C518DACB592ULL, 
            0x4A18A5794B6046F3ULL, 0xEC5FE52DD7D1769EULL, 0x178C020BE86D73E8ULL, 0xEB53A29CB4CE2F4AULL, 
            0x062164ADE5B4E222ULL, 0xCD419CB13AC8DB06ULL, 0x2290BD574C1FF484ULL, 0xAB5DBC04E21377EDULL, 
            0xA10C597979607626ULL, 0x11A17524AAF8C9E1ULL, 0xB734747ED20360BBULL, 0x59A0DF5599BE816EULL, 
            0x5CC360FD8E4E4136ULL, 0xD7BCF356C70F66CAULL, 0x235F0334AA9CF048ULL, 0xE6648F90DF487C17ULL, 
            0x3B65E4768A379BD5ULL, 0x8D58CA8FB468C203ULL, 0x8C83B53E3894AF27ULL, 0x7F2E11B12816224CULL
        },
        {
            0xBB46692BAFCA719EULL, 0xE4F5B3B16E70C7EBULL, 0xD175B84857DB8341ULL, 0xC14499F82E5C3F6DULL, 
            0x098277EFD1340952ULL, 0x3826CDA0A9F17980ULL, 0x292C05C03F667334ULL, 0x259136F7710818DAULL, 
            0xDF98CA5A2ECA6BC2ULL, 0x7683C43C9031D89FULL, 0xF959FC4C65A144D2ULL, 0xB712109804B1D991ULL, 
            0xC0AB0EEA9024A737ULL, 0x914607B884C151C3ULL, 0x8569B8877B9F7D7AULL, 0x82B1770941245A2CULL, 
            0x8DBC29EE2B492F50ULL, 0x0164B27377B19167ULL, 0x044DEC7F093F4629ULL, 0xACC5C99AA07540A2ULL, 
            0x1851629F277E67DCULL, 0x8484237C13EF0050ULL, 0x072AB007C4687111ULL, 0x5AE52CC981C2D736ULL, 
            0xEEE18EDE2850EF13ULL, 0xA03608A7750C4B8AULL, 0xA7A8CB866B648096ULL, 0xAE1C36377C16D88DULL, 
            0xCFFDF3AD2610C465ULL, 0x795AB2E56C002D24ULL, 0xCAFF1E291E06AAA5ULL, 0xA7447F3CBF3C336EULL
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
        },
        {
            0xF7A993EC037F02BEULL, 0xD35D3CDD2D714EA7ULL, 0xFD46E13D64BC7C87ULL, 0x7CC5C2F9E455C835ULL, 
            0x5847A2340448AFF4ULL, 0xFB9740C436CACC0FULL, 0x31D7DC52EA31C8ADULL, 0xA3EFAF76D673B812ULL, 
            0x572757C7C7503D9EULL, 0xAE16E29EF2DB47F6ULL, 0xF1D1A639A8AF2D2AULL, 0xC4A857784A0A5CA9ULL, 
            0xF2694F095E1437F3ULL, 0x2E96C0EF3BC826EEULL, 0x93A8519AA20D491EULL, 0x0530015910655B5DULL, 
            0x7990031014A92BF1ULL, 0x5174D4AF0D8ECAD4ULL, 0x8876983560ECB58FULL, 0x35E44AA618F4BB91ULL, 
            0xA91115453E4D41CEULL, 0x9D46360FDA9421E3ULL, 0x41D7419147F9E014ULL, 0xBDAF102A383E584EULL, 
            0xECD55F3B83DE57B2ULL, 0xE24D4DB59B41D732ULL, 0x984760CDE47A8288ULL, 0x15D40FC13B47A23FULL, 
            0xF5683809AC846466ULL, 0x5CD8AA260EBB869CULL, 0x411BAFC0115C5746ULL, 0x74B7AD739ADEF2EBULL
        },
        {
            0x1F78412AC5F2A24EULL, 0x8BF1E26495337ED5ULL, 0x734C012A1A553F8AULL, 0xEBC41424DA39EEA4ULL, 
            0x55F0CC6C4D8FA233ULL, 0xCEC67B079BC21AAAULL, 0xDC8308D0E8F76F07ULL, 0x00A4D68EFC93A5DBULL, 
            0xD0A762E9C0FF1B22ULL, 0x561E8C39C9E32DE6ULL, 0x769E3EA576507058ULL, 0x5441B9F767DD02C8ULL, 
            0x666BFD669A09389AULL, 0x231D6E137EDA14B4ULL, 0x5114396595104E96ULL, 0x4737BB1E4C733E7EULL, 
            0xD8741DA3890569D8ULL, 0x0B749EE7CDEE5FC5ULL, 0xC634254C33A398EFULL, 0xD9AC2304F16625E6ULL, 
            0x1338B85EED18C6BFULL, 0x08C2D6BCFB1F79D5ULL, 0x445C30194923D12DULL, 0xBDE9FAF0B3575A2DULL, 
            0x8190DBBAF164EFB0ULL, 0xA234FAC633AE9E3AULL, 0x45F5CB2E287D9ADCULL, 0xAD9E20AF3DDB2E0DULL, 
            0x136B92330AE2A740ULL, 0xBFAACF5244EEF72EULL, 0xDBF58957D0109AA0ULL, 0x14759E232BF908D1ULL
        },
        {
            0xFB21A5D38E867361ULL, 0xD89B2DBAFB8EB475ULL, 0xDC1B7F9EE4F9D2BEULL, 0xABDED4E41C1C676CULL, 
            0x937FCCAE39319183ULL, 0xFDA094F301804E93ULL, 0x0602CF3C19792CDAULL, 0x0C9C825A797F1644ULL, 
            0x197217625ADC3140ULL, 0xE3973865CA5E2F5CULL, 0x01EB33575FEB703DULL, 0x6E2D1BCF1F25C658ULL, 
            0x6DAB12A1E5FC1D42ULL, 0x5C5B04B364DA30EFULL, 0x304DAF6BF0BB9502ULL, 0xCB77859BB1B48B46ULL, 
            0x60C39DA43F2E8F4FULL, 0xC55D772FEE80FCB4ULL, 0x293F51FB79C6D396ULL, 0xEEBE743EFB2B4A68ULL, 
            0x193B93A51FE19465ULL, 0x0CF59FD632D05044ULL, 0xF48FFB2A48EA351CULL, 0x0E921B506CD3F009ULL, 
            0xF293B2C7FDF5BA27ULL, 0x1DA9CA54433F89F7ULL, 0x5CF04FD1BE56C5E9ULL, 0x26361E45848DD3F3ULL, 
            0xB832D5550BC193C0ULL, 0xA4BBD0824121397EULL, 0xF997DF39B7F81033ULL, 0x44FE5234E70161D5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseDConstants = {
    0x30A58D4806998BE7ULL,
    0x5A1F544769BBCCCDULL,
    0xC34EE12F5CBEFF89ULL,
    0x30A58D4806998BE7ULL,
    0x5A1F544769BBCCCDULL,
    0xC34EE12F5CBEFF89ULL,
    0xFBD00568B3836B39ULL,
    0x414C57F0303C4660ULL,
    0x48,
    0xA3,
    0x08,
    0xC6,
    0xE7,
    0xFC,
    0xAC,
    0xC4
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseESalts = {
    {
        {
            0xE7FD78D7DB4E4AB7ULL, 0xCE0DB76C62F9ECC1ULL, 0x4B2EFBD703194818ULL, 0xC83C892540B385A7ULL, 
            0xD4A530167ABB86D7ULL, 0x4A2258D19EAFE002ULL, 0x72B1EB41954CEEABULL, 0xA9BDC332B21444F2ULL, 
            0xB7511A021266CEE5ULL, 0x70101174FFF7DEC5ULL, 0x881FCA288DC28FBAULL, 0xB48FD4E0F1A03745ULL, 
            0x353AA4C81C9E5F44ULL, 0x689C174963D8D364ULL, 0x1A0E518D34611411ULL, 0xC11DF54120D70707ULL, 
            0x2941AA18DD118CEDULL, 0xBBE2237153D0C5EEULL, 0x22109C697D709917ULL, 0x3A406C6D823BB487ULL, 
            0x36BC950DCE98F8AFULL, 0xB22420D325BD56A3ULL, 0x4AD09D9575053FCBULL, 0x774CC0A52DD6DA0AULL, 
            0x21487E7E1156BDFAULL, 0x357A75FB39E5D1CCULL, 0xEAF1412E6C549FE7ULL, 0x471A0F887D45132EULL, 
            0x7269A350346B54FFULL, 0x2AB1D7711E0A958CULL, 0x3FD8C66327FF28ADULL, 0xAF6FCDE063CAD039ULL
        },
        {
            0x5DEF2A6DF30669C1ULL, 0x3796F0D72C3D784DULL, 0xC4046A97F8E12243ULL, 0xDC097BEC313BEA57ULL, 
            0x28807AEFD3E946EBULL, 0x3636952F311E0F20ULL, 0x52EFE4A050EBDCF1ULL, 0xF2BB0CC7ECF605D2ULL, 
            0x2A778429C8A85CFCULL, 0x4E51ADFEB8628A69ULL, 0x3968BBF62B5FFD57ULL, 0x7F5B9B180124B8ECULL, 
            0xA421393E0422ECBAULL, 0xB5CFF474D12322FDULL, 0x42F14829761D055CULL, 0x6940543D6D20D05BULL, 
            0xAF7A6DDAE5E4DA4BULL, 0xDE28233C67EB686FULL, 0xD5C5D79737AE4312ULL, 0xFBB9A0B79FAC3654ULL, 
            0x572136637B914B23ULL, 0x29A2B863163D75FCULL, 0x40AB4A7D29CF5E13ULL, 0x9461D939C14D4CE2ULL, 
            0xEA422CAAE3452913ULL, 0xA73B6F2CA5B4BBC2ULL, 0xC3DFF3E730D1B025ULL, 0x7FD44F3C8C1E0A50ULL, 
            0x7A260102650CC120ULL, 0xD3F72871460C8474ULL, 0xBE325A093B5D7E72ULL, 0xB7610638A4797D31ULL
        },
        {
            0x098394F22B71EB95ULL, 0x26DDB02AA85855E8ULL, 0x0292D68445FA615AULL, 0x7223BE40B34097FEULL, 
            0x039E0C7CC012AF9BULL, 0x25A90FE62C35749DULL, 0x1E489E982A34ABE1ULL, 0xA9F90A835BEC23A4ULL, 
            0x12253A05B024D787ULL, 0xC5DF79E6EB4AFA78ULL, 0x27952C77FB0B068BULL, 0x5272739D61116E3AULL, 
            0xCCDCD0D6B81244C1ULL, 0x5F1D73DCDCEF1D58ULL, 0x52BCCDDE7BFB2C4CULL, 0xB32D9F6FAE4952ABULL, 
            0xE347CD24EFD422C0ULL, 0x1999D90BF20A6A36ULL, 0x5CB1B5052CA4E15CULL, 0x034058CA5DC614B5ULL, 
            0xE1B8D0F41FE7F2A2ULL, 0x96FB1469FC8F4113ULL, 0xA5EBD79C981684ECULL, 0x978D983FCC580A9AULL, 
            0x1CF966F07EF69051ULL, 0x772BAD21C4DB8C2EULL, 0xDFED83869BA493B4ULL, 0xC7FEE3894BB0024CULL, 
            0xB8D7BDBEEF69036CULL, 0x86FB2D7CAA515CC4ULL, 0xD4F560A6E39A7AB2ULL, 0xB3874A3F79487B41ULL
        },
        {
            0xC0A66F4901F8E569ULL, 0x286A29593354A376ULL, 0x229380C765966CF6ULL, 0x3FEBC93CB0FCAFEFULL, 
            0xB011D5B8D1427A05ULL, 0x392596A34736AF73ULL, 0xC85EF021BD4D0F76ULL, 0x1F50A2DF842C9C26ULL, 
            0x50650ED33A7AFAFEULL, 0x50CA5771EC59F973ULL, 0xE74985636215DD34ULL, 0x5145A7148DA0F6DFULL, 
            0xB03F9B8BA2A941DCULL, 0xD28CF0B6246C6901ULL, 0x9E28FB703590BC71ULL, 0x902C9ADF0AD1BDC6ULL, 
            0x38F6902B59A611DAULL, 0x327D4FD0296F65D3ULL, 0xAAD76A55C2BD6383ULL, 0x78DB3806C299F273ULL, 
            0x58E851F820F6630DULL, 0xE7367344C7A4EC22ULL, 0xD959869D8782F4B3ULL, 0x92EF1387A18BF24FULL, 
            0xCC9977938C2F2ECDULL, 0xF9E63DBA1D88E2DFULL, 0xD4DEEF2964360E96ULL, 0x484E73195D2961D2ULL, 
            0xC28F7052CB1B056CULL, 0x3902078113D89B05ULL, 0x2E36EF8785F9EABCULL, 0xEA97BF9CA377F926ULL
        },
        {
            0x0CA5DA9A36E5E84EULL, 0x293E14AC5BD45250ULL, 0xC5094F3CC159CE88ULL, 0x9C21BBD668BF1418ULL, 
            0x0CDC559A3C3C8BBEULL, 0xCA048B136CA926A6ULL, 0xEE148A0383AE7966ULL, 0xACAB39CD58680C3CULL, 
            0x6BF87589892F75ECULL, 0x189E910700F640D4ULL, 0x95D5406D1D80B627ULL, 0x5DC83886765AC57FULL, 
            0x8A52045E3E07F890ULL, 0xA2B48B5728686789ULL, 0xECDA12C71BEBB01BULL, 0xD614EC79A23F3F5AULL, 
            0x7B82BB990AF55C12ULL, 0xA246B6E7BA05CD1AULL, 0x8B04ED0A776777D0ULL, 0xCF71B23F16B714BFULL, 
            0x477D910C236CA9F9ULL, 0x16560609B0D182DDULL, 0x5EF4162FA046F8B6ULL, 0x4D4081FB79315FBCULL, 
            0x9FECC89D586C353CULL, 0x0DF56D478D10E3ACULL, 0xA9E01F2DC3CCACC9ULL, 0x27A68D1DD4050017ULL, 
            0xD4BD6B98EE38A2F2ULL, 0xBCFD9C658F36F71DULL, 0x3D2EF02AEA6D915DULL, 0x8A823754DAE65255ULL
        },
        {
            0x919FF2B16DD23D18ULL, 0xB3993634EAA9784AULL, 0xC5FEF95E9C0E4A54ULL, 0xA015BA80DA57D273ULL, 
            0x5F7B8D6B8A520FDAULL, 0xC8C572553F2EFAEDULL, 0x98CF2AA84EDA54DDULL, 0xEA6292D01B265794ULL, 
            0xCC2820AACBF6F7B2ULL, 0xAC4328B9AECEB493ULL, 0xD619DA0D39EDBABDULL, 0x26350FEB774B8F7BULL, 
            0xF9973314688D787EULL, 0x822EDF1E44CA6ADEULL, 0xBA954466736E6720ULL, 0x3310AAD0BE41E15FULL, 
            0xAF2888FCB0C219B7ULL, 0x288238574D31E6B8ULL, 0x4C2F95D6CC9315B9ULL, 0xCFA220F13BC426C0ULL, 
            0x0B67B31992AB9C06ULL, 0x247D55FBEC2C355EULL, 0x6AEEE56A5982C1C0ULL, 0x88E6624C3FFC6029ULL, 
            0x94E60334A0DF7AC2ULL, 0xF4D212270B89EACEULL, 0xFDFAA288451C4CEBULL, 0x26DA621479512540ULL, 
            0xB9C2EED64CD8AB39ULL, 0x4B9B51DD8657D2ADULL, 0xFD99C97715792919ULL, 0xCB96D9354F66D84DULL
        }
    },
    {
        {
            0x013FD31BD2D8BC22ULL, 0x65A9D7F1C4C427CAULL, 0x7AB378F05FC5D969ULL, 0x60DC34DA0373DCB5ULL, 
            0xD6767876B626554CULL, 0xF57D7A3D730E76A0ULL, 0x99D10E6C70F27CFBULL, 0x5B5B3D22224A907DULL, 
            0x4A1C2994CFB74C93ULL, 0x9B7F00BE227CF4D9ULL, 0x6C09353CBC6540D1ULL, 0x20C909AF6911E5EAULL, 
            0x94F31C34812E7937ULL, 0xE26190931168B3A6ULL, 0x5D2DC61AA2DA99B9ULL, 0x4FF9E8628C5195DFULL, 
            0x2A299A15B94A1667ULL, 0xD77D5AB5151DBDD1ULL, 0x51572B58FE13F347ULL, 0xE416BA983ABDE675ULL, 
            0xCBBF1CACF05642BDULL, 0x1EA47D56C6F575FAULL, 0x4602866FD080E91FULL, 0x26F3E5A46C78BB4BULL, 
            0x8655B56F47692031ULL, 0x0342B9EBD5999436ULL, 0xA6912041867C8A65ULL, 0x812707A16E66BBB9ULL, 
            0x435DF2EE7E3CB4FFULL, 0xA96226885C838C4EULL, 0x8EE8000A9F3FF062ULL, 0x6C500BC1B5C6D97EULL
        },
        {
            0x7187DE8D9F6DB79FULL, 0xCC3FCA90594A8CDEULL, 0x794DE4B76BC604D7ULL, 0x88A6F349425B14EDULL, 
            0xA84E886E0A648D6AULL, 0xDAD5FAB60C9A1B3FULL, 0x984597A263FB99F0ULL, 0x6E0DEE539EA14920ULL, 
            0xF1F5164A7B5FB987ULL, 0x6467CCDADEDBCA0DULL, 0x16BB0B7B3B2016C1ULL, 0x2D320F9E18909D71ULL, 
            0x31F0752AB34F7040ULL, 0xB754D06BE4A03860ULL, 0xB5E3E99F367E9A43ULL, 0x4F35A3D3A8983A29ULL, 
            0x5DC64E1C3EF5CB88ULL, 0xD123D440968584C8ULL, 0x8CD642F4603FED30ULL, 0x5DACC28E28277344ULL, 
            0x80FBEE0D96DAD778ULL, 0x6EB21DA4B6C2BD0EULL, 0x806C4CC5AD84573BULL, 0xDE218AF9E5C6F1F4ULL, 
            0x48B3C9DF177D9B7EULL, 0xF1C2A186467E814CULL, 0xB4E043473546C77CULL, 0x09700D48D12291A1ULL, 
            0x9D610BA98BE65D43ULL, 0xFD81F64E15540B18ULL, 0x2D1B3260A00AE1CBULL, 0xA1F6941EC26BEE91ULL
        },
        {
            0x25C8EC469305B036ULL, 0xA7E7ACC7252CE060ULL, 0xB607ACA02D7CB8ECULL, 0xCA9DAE7DF556AE3DULL, 
            0x122CD4E99F1C41F1ULL, 0xDD8784329BACCAB1ULL, 0x69B0250D8915824EULL, 0x07125BB267ABE205ULL, 
            0x083B7B9F4B2AFFF1ULL, 0x56BD74BA7F8F341AULL, 0xDADE73AA249F49D4ULL, 0x2F0ECFC4B2277443ULL, 
            0x88340B2D8F51D2D5ULL, 0x1C8771BA4AFBD264ULL, 0xEDA5B5A6C44CE84EULL, 0x1A0025E3AC090E9BULL, 
            0xB502E7AFC31CD649ULL, 0x94180545492EDACCULL, 0x89587FC7F5BD932EULL, 0xD65E2F57311A9165ULL, 
            0xF9A63C9D9699BACBULL, 0x7B69AEA266B884D9ULL, 0xA25BAA6A57322BDCULL, 0x2501BB659E2EF8FFULL, 
            0x0F9C16758F40E640ULL, 0xA5A87B7C7C56A44BULL, 0xABE00DA2BC408D04ULL, 0x3C54ED81080024FCULL, 
            0x91B4DD92171F917BULL, 0x07AC37E36D3B9D42ULL, 0x74EE8C3E8A9732DAULL, 0x7D5F5691CC9C0AEBULL
        },
        {
            0xADF1023D6EB4CEEFULL, 0xBC6E7D06C2E5070BULL, 0x6B003626D05128F9ULL, 0x28DD47DAA58A6C27ULL, 
            0xACF60E0664DCCF4BULL, 0x82B34A664A7720AEULL, 0x8794197C1C162171ULL, 0xAFBAE3EB05F45803ULL, 
            0xDDCDC6CC198D3553ULL, 0x02F8B2D02A6E3E73ULL, 0xCE079CBE90B002D8ULL, 0x48BC0784FE3FFEA4ULL, 
            0xBBC1A25DC17EB924ULL, 0xAB7EFCF24153C162ULL, 0x530298194719AD16ULL, 0x325E0DD62B98064DULL, 
            0xC508C078471BF46CULL, 0x02B648A29F741E1EULL, 0x4F394EB2FF987575ULL, 0x87403FE58AEAAD30ULL, 
            0xCB3C4B0081B8FABCULL, 0xCBC2C7B4251DA305ULL, 0xA1EE91D032F7DFDBULL, 0x61227B63F00E4BF7ULL, 
            0x1BD22AC9F6B6D6CEULL, 0xA4DA38F9A5BD0EBBULL, 0xBB14D1C78EFE457CULL, 0x85D2FA0EF3A88ECEULL, 
            0x96CD26431F51CE25ULL, 0x720CCAB9A7A39551ULL, 0x3076C0DA6C35ABE4ULL, 0xCC9E9018DCEA9CA9ULL
        },
        {
            0x6D101908D2907DDCULL, 0xB1F2BD788584A083ULL, 0xB2F15CF253F08586ULL, 0x32A6C782A0816172ULL, 
            0x9AFDF98EA4EA5698ULL, 0x82E465530A918AFAULL, 0x31022CADE5B2D281ULL, 0xFE677C3C4E672D50ULL, 
            0x6DF741653A2AC4DDULL, 0xA23DD91E4289FF3CULL, 0x9234BA49ED685DBAULL, 0x6969FF8900973E3DULL, 
            0x3B8E176AA773B3CAULL, 0x3D0AA04BE873E5F3ULL, 0x2FF401777F97343BULL, 0x6BD6437997DE57DDULL, 
            0x3EFEAF9C6F7250BBULL, 0x8F26583248D9ADC7ULL, 0x81FA5C01954CFD1CULL, 0xD4E5FFA9ADE870BCULL, 
            0xCE92EB35B58F2577ULL, 0xA5FE9AE863948903ULL, 0xBB06C41B318AE5E5ULL, 0xC21D162F47EBCA02ULL, 
            0xEF48845277FD5B20ULL, 0xA3CB09374578AB4BULL, 0x8CF5AD9946A09470ULL, 0x4014A63AA8D25D37ULL, 
            0x3BA6E1DDD097211DULL, 0xE4B1622EAF16EBA1ULL, 0x0B057457B413E76EULL, 0x4153B7E66ADB61D2ULL
        },
        {
            0x9C8B62783BD20B9CULL, 0x8A194FCAF1525415ULL, 0x141139E420702C38ULL, 0x865EEFFDCECE2F4FULL, 
            0x927B92BAE87E1933ULL, 0x1FFE266D0FF4B2A2ULL, 0xE40252EF9078D2DCULL, 0xB68C2C9B55A87758ULL, 
            0xC10939AF2F828C1AULL, 0xC29022DD0B45665BULL, 0x84C7978514639945ULL, 0x27C289D4ACABB9B1ULL, 
            0xF067783B91F07514ULL, 0x11E11456FD772075ULL, 0x879FD015CB146787ULL, 0x78A463A8EE5309DCULL, 
            0x3306EA5167CEB6A8ULL, 0xE2E42002AA85DB54ULL, 0x58ABF8EDCEB70B8BULL, 0x4D9F57382BC6501AULL, 
            0x19A674ADE291162BULL, 0x0EB3A7A41DC2DF67ULL, 0x213C3BCE9F977488ULL, 0x0F9075A0B50DF3A3ULL, 
            0x491EDF7ADA3B79C7ULL, 0xE192E5731D42D677ULL, 0xFAE31B820CA78040ULL, 0x877080968E7108E4ULL, 
            0xD4EE14C46D9774EDULL, 0x9EBDD7B5811065B9ULL, 0x4CB4C3CCEF492616ULL, 0x179BFAF25D15F977ULL
        }
    },
    {
        {
            0xA0E52FAF1F4A4A96ULL, 0x734B78A8F044AED4ULL, 0xBDA9BBF9E82CE8C2ULL, 0x59E924B436F6A05AULL, 
            0xB18AAB25CBA2B279ULL, 0x749CFDCA17932A2EULL, 0xE9470275E069140EULL, 0x195B2A962AEA2741ULL, 
            0x0F638E6139776B21ULL, 0x8CC8730A6876F7A0ULL, 0x08D20CC36DCA8AC0ULL, 0x6E354A63FA31BF49ULL, 
            0xD8A77B695DB2FC2FULL, 0x68D693FB5178C641ULL, 0x92BD8090DC2427A7ULL, 0x0BF20BE5DE74AF62ULL, 
            0xE78F3E6B2147389FULL, 0x487DD0810AA74DC7ULL, 0x36FCB62C9D285B1CULL, 0xF872E23391A1797DULL, 
            0xB3C71ACA95BB5B27ULL, 0xEADF74C8F7618C67ULL, 0x1A965375C27D02B0ULL, 0xC0318353A58BB8D7ULL, 
            0x4CD6DF2C93BF3060ULL, 0x896D29B7EF97DF97ULL, 0x5487556B1472C4D4ULL, 0x05CC237CA0837460ULL, 
            0xE5AE118F1ACBDA0DULL, 0x1EF65631E9822824ULL, 0x992111CEB1D36B8EULL, 0x6B2967CB887A4D77ULL
        },
        {
            0x683D5CC574AC208EULL, 0xD9E21179A1D5BD8BULL, 0x53A57D4DAA840609ULL, 0x38614F39B5DB103DULL, 
            0x7A650268A62172EEULL, 0xB4C45786B0AD1729ULL, 0xDCB72C0EB9C36ABAULL, 0x677497DBF8E12F3EULL, 
            0x2A9394B3485C1C5CULL, 0xE58AF40211E5CFF7ULL, 0x17E3E59A7583B960ULL, 0xAE6E93389BDB40CAULL, 
            0x3B3BDEF2BF56512BULL, 0xE94A59BB04664BDBULL, 0x23DF093E53EE70F3ULL, 0x00EEE0AB35648383ULL, 
            0x3F28CCED27A6AC64ULL, 0x0D0CB961EC2FCD3AULL, 0xADB7EEACCD6A57D6ULL, 0xE081F2BE812294A5ULL, 
            0x0999AF6DAD2A2ABAULL, 0x3B57848D658C562CULL, 0x181A849D5B3271DAULL, 0xA2C58EA5C7BD8462ULL, 
            0x011AC6119FEC93A1ULL, 0x0D36FAB12B2A6577ULL, 0x9077407225A80DD5ULL, 0x7456DD30714BE93CULL, 
            0x989737EE7A0E193DULL, 0xFEC3BEEA3785DB70ULL, 0xF57F463B7A008AFDULL, 0x4B726E366AAC7802ULL
        },
        {
            0x9B77AC9A14F2F278ULL, 0x5C64121CAC7BB8D2ULL, 0x23FD22CE9041CC0BULL, 0xBCE13EA88B13B888ULL, 
            0xB20407F7B32BEE53ULL, 0x62A5B8762D7E21D2ULL, 0xA51E030F65A291BDULL, 0x7EFF9F0E26E4CAF5ULL, 
            0x088D8DABE6F06526ULL, 0x40440FC77C7F33E2ULL, 0x7FDBD633BDBA8DD1ULL, 0x4AE0315316ED934AULL, 
            0x5FCBDD389415FE2CULL, 0xF11BC76B8E53D027ULL, 0x19FCE7D4040CBCEAULL, 0xB6BC7855C6863F53ULL, 
            0x0F2663C2F5FCCC98ULL, 0x74FEAC893CD62F90ULL, 0x997162FB405A7B4EULL, 0x0798BBC70BDD718BULL, 
            0xA5C1E2F3A3D37561ULL, 0xFE3EB34B76B0D504ULL, 0x0CF193E06A1E5014ULL, 0x1943DB46CD9F6EB1ULL, 
            0xFE989FC176F98C39ULL, 0x8268DC94630FDAA6ULL, 0x9F1F9183A8D2EDD1ULL, 0x8BD7AA896057A267ULL, 
            0xDCE8D6336CAA2089ULL, 0xC26EDCDE6E7322A0ULL, 0x92A7BEC38D47E58CULL, 0xAB96EF23BF507CE2ULL
        },
        {
            0x7E928B58CDECA706ULL, 0x4F19EA49C45177F1ULL, 0x90AD3939CAFC1939ULL, 0x8B2FC43D23B4320EULL, 
            0x6D86A4E5D5BAD892ULL, 0x451FBD24783BFECEULL, 0x5AE2BC7DA567CB24ULL, 0x6875D2414424AFE3ULL, 
            0xAED789D8AC1A264FULL, 0xF8CC141F42FAED3AULL, 0x497E6518ED5E042AULL, 0x70D49FED58B04ABDULL, 
            0xD0195B4B1009F9C9ULL, 0x945BCB4917D11877ULL, 0x1A6742621A992E73ULL, 0x5849CC39D1900D07ULL, 
            0xBB0D79C5D3FFA426ULL, 0x63F491A490398A88ULL, 0xA3D92461950DD3D9ULL, 0x009AB481D13AE9DAULL, 
            0xCA0F717684FE8785ULL, 0x71FCB24366F1E647ULL, 0x68416F9E6E2EC6DBULL, 0x0F98B129EA257915ULL, 
            0x9229611640A0DA49ULL, 0x9A1F5DE54B053D30ULL, 0x4A3002EFC685B80DULL, 0x486A43161A004D53ULL, 
            0x9F4BA75163651858ULL, 0x2CA8F1A9297941C5ULL, 0x9FAC84F387EA08A9ULL, 0xD207ED1F683B9C0BULL
        },
        {
            0x77C23FD25D4CF0F2ULL, 0xF1CCF7C0ACDDC578ULL, 0x384AEB58E924BF78ULL, 0x6BB1503FD15438FDULL, 
            0x7C462044324E9724ULL, 0x5EB6C223A231198FULL, 0x1CBF699B1F4173D6ULL, 0xB22F44FE4C923D87ULL, 
            0x0E8FE1C0907484ABULL, 0xA7F34CFBBD441140ULL, 0x160B0CF03B5A90D3ULL, 0xC0C4262A6574B1C6ULL, 
            0x29E5E36AD01F4F57ULL, 0x10D15DCA0BCF4272ULL, 0x5596362D0B61EE7DULL, 0xF846B5C433EE330BULL, 
            0xEC3E2C09CE43827BULL, 0x1C53BDD80BBB2166ULL, 0x8B1EBAEDE8810F5AULL, 0x0BEF73BB1981FB9BULL, 
            0x412F443C28AC310DULL, 0x3EBC01318C0FB58EULL, 0xEB9AD97E06E18DCEULL, 0xF0EE5DB25117159EULL, 
            0xF8D22C3F03CDC7B1ULL, 0x0D8046AB64BFD938ULL, 0x3051AE70EBE92467ULL, 0x68A9F77F1DDCFC94ULL, 
            0x8190F440CCE75C07ULL, 0xE6131A8852EB92C3ULL, 0xB21B0F9A7B7DD4FAULL, 0x97499FDA5FF2ABF7ULL
        },
        {
            0x718577C674ACB311ULL, 0x429446BD0CA38AF3ULL, 0x54EA1A05AB7BD63CULL, 0xDF0B6A24594710B0ULL, 
            0xB9007C92E3922F78ULL, 0x3A9E2AEAA63AB3DCULL, 0xED2DC80B4C03C19AULL, 0xAA5FD940E33098C8ULL, 
            0x2B12D8F6C09C86D6ULL, 0x0D0B34CE1483F38BULL, 0x8C241739B70832A2ULL, 0xF34D27A62DFBEC58ULL, 
            0x207A9557718844CFULL, 0x1B51D8E46AC387D5ULL, 0x0DE834F30928CD96ULL, 0x670B0AAEC4B28608ULL, 
            0x8BCB30DE2B56B27EULL, 0xCCE720935B384ED9ULL, 0xC8137600E5137819ULL, 0xCAEA09CC912D4E01ULL, 
            0x95EADC35CABD54A9ULL, 0x5AAD51EEF8F2876CULL, 0x20D86FE02F30FAB9ULL, 0xBA222F85F22A2D27ULL, 
            0x2CF40CD2F7F324DAULL, 0x1C82EB124A392665ULL, 0xB736A733C0E83181ULL, 0xB3CB47070D81453FULL, 
            0x9CF0243856E2DBE8ULL, 0x69E3141459E313A7ULL, 0x075574FD3370554BULL, 0x16BB0DA3E8A73428ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseEConstants = {
    0x4D0F5BA89EDED0A6ULL,
    0xA40942EBA04BBDBBULL,
    0xA69A8608CD34FD4EULL,
    0x4D0F5BA89EDED0A6ULL,
    0xA40942EBA04BBDBBULL,
    0xA69A8608CD34FD4EULL,
    0x1F9D3782CC36F342ULL,
    0x5159A6AE0F4EB3D1ULL,
    0x1C,
    0x40,
    0x82,
    0x4D,
    0xF3,
    0x31,
    0xA8,
    0xB1
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseFSalts = {
    {
        {
            0x20EF5ADEBD0BC03AULL, 0xFFA6633148BAC362ULL, 0xC1606858778D8032ULL, 0xEA9C2AD43E32812EULL, 
            0x0F6F5DBFD00F8D58ULL, 0xB3FB42D633DFC93CULL, 0xD1EC64ABF645134FULL, 0x8140E5D12DA2991FULL, 
            0xBC71E7A9CBC212A2ULL, 0xE30F1A74D94BC2F2ULL, 0xA3E2F7AFD5F16266ULL, 0xBD07466C2A0F170DULL, 
            0x48E7CE1F1CDBC022ULL, 0x3B4E2B69F52581B5ULL, 0x58005E54214176DCULL, 0x2DDFC4EFCEFE634DULL, 
            0xB603052BC956D56DULL, 0x1BD05F9BC7AB5BB0ULL, 0x331A1AB42961D499ULL, 0xC02511AEF8899D64ULL, 
            0xB8877F76D186A8B5ULL, 0xA5C3D60EF63FFADEULL, 0x0ABB02B2B51FA169ULL, 0x05A0C5FAD41D4737ULL, 
            0x3E0569A6D8683348ULL, 0xA76F9B690AA66D86ULL, 0x72E4031FBF746E76ULL, 0xF005E36A283AF968ULL, 
            0xA42243E2ADD7F6D5ULL, 0x8384F808C33E9BC6ULL, 0xE7B1EBC6D6ACAE6CULL, 0x7D4785A734F6A66EULL
        },
        {
            0xBBA3913E6FAEB0A9ULL, 0x02A48E00D4ADC532ULL, 0xDE11BAA2016C7124ULL, 0x7365CE91C171305AULL, 
            0x1372F6F00458E0D5ULL, 0xAB9EB2777BC5EBEBULL, 0xCAB7CC9492EF26BDULL, 0xD2B4B2D662B8708DULL, 
            0xADE9349DADA409C3ULL, 0xBF41B48709711777ULL, 0x01BA0C881E7B469CULL, 0xCF146D10DC2C0D06ULL, 
            0x8C3D0AC2F8B97E4AULL, 0xA62CFB761B92820CULL, 0x18151E9C9A1406E0ULL, 0xF9396694CE497CE0ULL, 
            0x1EB5DF6BDAEB2907ULL, 0x695F792B701419EDULL, 0x4552B05B68343052ULL, 0xB2509D1CE4348A31ULL, 
            0x354BBDB19C07B667ULL, 0xC9CA955330EF7C02ULL, 0x4F469FAA5815A3CBULL, 0xE971C801236CE94CULL, 
            0x7179B839D9B382A6ULL, 0xC66177A7DE08C664ULL, 0xA37AA7896AA044BAULL, 0xD3A8227EA3C74C6BULL, 
            0x3947F83B0D075233ULL, 0x760B33CD6D4B1737ULL, 0x0DC894973D3D9845ULL, 0x4FE062A8382701D9ULL
        },
        {
            0x78BD694F90857C19ULL, 0x87DD7DCA6FD7CBD7ULL, 0x58067B93DB624E20ULL, 0xE8DA84E1E7607373ULL, 
            0xE1E920AE771B3D8BULL, 0x116DAB2B72D2F6B1ULL, 0x2079D5B7AE809C15ULL, 0x7E86ECD3A43AC563ULL, 
            0xB6B33797C09AE47BULL, 0x1CF500B06FB76B16ULL, 0x81911FB915700AF2ULL, 0xB0DAD062361EF21FULL, 
            0x764E0F5B126F53CDULL, 0xCCBD70F43FCFBF15ULL, 0xF6634F9CF0B591FFULL, 0x9FBF9C21CCD0EB42ULL, 
            0x9718897FAEC7C9FCULL, 0x8ACF81CE2ED23DE7ULL, 0x60DC9CAF41795037ULL, 0xDEA7D391ED6DB287ULL, 
            0xCB50FEA0D3CFB4A6ULL, 0x66E9E6863F5CAF47ULL, 0xF258597FAB47FB24ULL, 0x4CC9F105E2853E1AULL, 
            0xE3B8A7E70661DEC8ULL, 0xBA5C9ED101E660EAULL, 0x97D636FF2D2E1BFAULL, 0x4A7C66A3F0B963CFULL, 
            0x82DAC6009CE42E14ULL, 0x2862A3E8D3DF8037ULL, 0x7FFBDC94EC4A456FULL, 0xB255941BEF1CFEA5ULL
        },
        {
            0x84E1E7F87F8737ECULL, 0xF064136E57DCF929ULL, 0xE4F76D8555E5BD84ULL, 0xF6C091B9245EE6CAULL, 
            0xA1532731A2CF835CULL, 0x27793DDD1D5C115CULL, 0xEE7002826D46046AULL, 0x7A8773A2532E67CFULL, 
            0x33691E4B9023D42BULL, 0x80D0CE7A8D7CFB7AULL, 0x04A6B63B5E98EF63ULL, 0xF6E5FDA7088132DCULL, 
            0x8A23A98BA38C19EFULL, 0x180A17F60B3FE537ULL, 0x9DBF00B93387619FULL, 0x2784D094AFFBD70FULL, 
            0x1A63476F791E254BULL, 0x3BBC93D7B2EC8C4FULL, 0xD640AB6DC693F7EDULL, 0xE2A3BCF7435FCB05ULL, 
            0x32ECE66AF5BC71E7ULL, 0xB4F67BDA5501AB5FULL, 0x6407814A352FD84DULL, 0x39757446C6EBF35DULL, 
            0x8D6FEE4556489D56ULL, 0xF01AE1F2F9D8D612ULL, 0x3B8883EEE4518079ULL, 0x65F0B4E25AFBF3B1ULL, 
            0xC529D40B441F703AULL, 0x90945C8AD519DED7ULL, 0x9F1A7E2CE15A5CBEULL, 0xA52495E029B0196BULL
        },
        {
            0xBB8D94BB8D7AD69EULL, 0x8B3278623BE3730DULL, 0xC8C717B077D70AEFULL, 0x5EBF4F3FDD27E549ULL, 
            0x4B58F685AEE35A56ULL, 0x40411C62BD76DA1BULL, 0x260B85A6292DE7FEULL, 0x1306C5A1B31F49F2ULL, 
            0x58934FFF7BFC3FFDULL, 0xB7B311F494F46F88ULL, 0xAA457004DAE33430ULL, 0x0D66B4E5EE416D4CULL, 
            0xEFB376A9FCE108F4ULL, 0xB72DF6B3AAAF3525ULL, 0x4368FEFF23F4C974ULL, 0x261D3C98DA0EDF34ULL, 
            0xB3A878C9FBAB3003ULL, 0x3FB6BD7677AA5FF7ULL, 0x1C456412EBB29676ULL, 0x09AC74D6572462E0ULL, 
            0x6AA5815B8717BEE1ULL, 0x1F0C96F82132C004ULL, 0x5C5368BEC0B7AF01ULL, 0xD192260DE728CF60ULL, 
            0x51A3B7AC56F087BBULL, 0xDF84D569841321BBULL, 0x7C9FE9EFC732CA88ULL, 0x46F938BB05885B96ULL, 
            0x9241C664E940F741ULL, 0x5E782273AE2DB98AULL, 0x8E76C248FBF38AB8ULL, 0xFBD2B4A8D19168E0ULL
        },
        {
            0x66964E67155B2136ULL, 0x0403C75AB97A96BBULL, 0x6BF7CAFBF188294EULL, 0xC647A28939046D27ULL, 
            0x59EC34BEE1E7DDD0ULL, 0x1089F4F61E92A4F9ULL, 0x7A8BA828357DA287ULL, 0x32C1EE1579915E61ULL, 
            0x22454CB3B1D831AEULL, 0x8BC7A8EDD71054B5ULL, 0xD519D06A0E9C8E97ULL, 0x913EC94B352DCB8EULL, 
            0xFC8AF2F9EDA6C904ULL, 0xE07767A88B95A531ULL, 0x880BA6F5DFEB7E9EULL, 0x00E714C0ECF64295ULL, 
            0x498132B4ADE3D62AULL, 0x7017332F0955D498ULL, 0x6495BF1C62F70195ULL, 0xE1E8C6C977A3BF19ULL, 
            0x9842712E6514766FULL, 0xC809D4E637944956ULL, 0xD30973C2E203375EULL, 0x46BD85AF8C53E195ULL, 
            0xB1AE1938E123D8B3ULL, 0x186A3967E15054FFULL, 0xD515985C4A8695BBULL, 0xB165A59176731B89ULL, 
            0xDD681691B9D98BF9ULL, 0xB556A7C73F3AFE4CULL, 0xC2FBDD3E47847D99ULL, 0x9CBAF5813D24F6D2ULL
        }
    },
    {
        {
            0xB54FE186718EC9A9ULL, 0x09E9AF3A1D93C476ULL, 0xD41CCC3EB0D698EAULL, 0x958A6A0736D377BDULL, 
            0x73604B7EE61ABC08ULL, 0x5E40E0B2E6F21238ULL, 0x4B7BB554D0756F56ULL, 0x061598E5D07C93B9ULL, 
            0x6F9199D8499E1FCEULL, 0x20F905C067B8D8C9ULL, 0x0A7D9DF792C320A9ULL, 0xBF20CBDCC3D69E78ULL, 
            0x4C57FB4A5FECCEDBULL, 0xEA0674DBA9CD0F6FULL, 0x7F1792CBC295177BULL, 0xB4CF5E3564477753ULL, 
            0x49EC54E2A5C48F86ULL, 0x02C196A0B970CD77ULL, 0xD7A640C6DE9D883EULL, 0xFF7CA3D181BCE62CULL, 
            0x7E0D021923FFA84FULL, 0xD6DF7C3A5523C487ULL, 0x5CF8ECFB1A704493ULL, 0xDDCC6A51BA324198ULL, 
            0x8D276DAC40A7F4E2ULL, 0x40BE217F070AF59FULL, 0xF9E6F35C9FDCD71EULL, 0x21C9399364B8CA12ULL, 
            0xAEE76E9394C553F9ULL, 0xEE3CA715AE225794ULL, 0x10482875DED28C37ULL, 0x25230144D2EF4620ULL
        },
        {
            0x893687B908A39AF1ULL, 0x8300FB5CF59624AEULL, 0x776AB281B4E007E3ULL, 0xC83BE18E03D977CCULL, 
            0x2C5BB940463D2299ULL, 0xB88331299C076C3DULL, 0x6D62692F0108CB00ULL, 0x690EF12B38E7CE23ULL, 
            0x6926A1D0B2CEDC55ULL, 0x2ACF771FA5FE63E7ULL, 0x99F508EC24CE1879ULL, 0xE9F5885D173D5A12ULL, 
            0x91FA809BFBA94A7DULL, 0xE86A3B955F804645ULL, 0x853333FBA776E8B8ULL, 0x781C1CA15A5251CCULL, 
            0xD877F358AFE4364BULL, 0xA0D9D51DDCF8D454ULL, 0xAB8447E07AA940E4ULL, 0x11AA9918BD43E0B4ULL, 
            0x61866E2A4346055CULL, 0x841B61C8C39B9CB7ULL, 0x7A05BCAC169719DAULL, 0x04231DB7B9FC0868ULL, 
            0x44C3AB88C94D5577ULL, 0xF87E0CC262E949BDULL, 0xDA59CC73CB586AD9ULL, 0x2B53E7FF8D9DBE55ULL, 
            0x5035B43EDCFB3C9DULL, 0x3EA21CE228896F74ULL, 0x8A4829C334F006B2ULL, 0xD5559A044B0B8089ULL
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
            0x87117C7A5057A45CULL, 0x23D399C06BD22270ULL, 0xAD6374C01BC27813ULL, 0x943AC652E9553540ULL, 
            0xF6F5FE11B607CE93ULL, 0x39E898D42DC50962ULL, 0x47748B19AA912730ULL, 0x4A96AB4F107A1F17ULL, 
            0xBD5F5373499BE63CULL, 0x77672CAF9B46F7FEULL, 0xB9AD3DC9BCA24DE8ULL, 0xBE08ED53126BC77BULL, 
            0xE7EC3E78BC3A6257ULL, 0xB0529503E3F6F1B9ULL, 0x742FB7EE408E8470ULL, 0x969188BEDE18D652ULL, 
            0xF3938F33A5C14555ULL, 0xF8ECD3EBFB9A2860ULL, 0x23E5E3809FA11792ULL, 0x0411C4683120D442ULL, 
            0x8FED253EB3103BE1ULL, 0x67F65AE0FBCE4933ULL, 0xB523A262043E5154ULL, 0xB44B669F2B0FCE82ULL, 
            0xA37B8E888E16A1D6ULL, 0xC24600E17A10C920ULL, 0x26D9D7B7FE4D0546ULL, 0x4924B4402F903F82ULL, 
            0xA819F8410A3F0232ULL, 0x5321260DA031AE76ULL, 0x75F8FA69A8950CB6ULL, 0xA6E7FF80D5E16A6CULL
        },
        {
            0x33017C30BEAD8D41ULL, 0x5AAD98B4146F9B3CULL, 0x67682600D60526F0ULL, 0x77E359327D7BCCEEULL, 
            0x1D66E03A775152E8ULL, 0x256B1709496D511CULL, 0xF4865E3A44D72CD9ULL, 0x0A6F63792B73E89EULL, 
            0x2262A56A574FC61AULL, 0xBBC16925DB5161BEULL, 0x7F5A51A71283565BULL, 0xE5A6B54FAC4BCFA1ULL, 
            0x0520084C881A40D3ULL, 0x4EBB9BA2B85CE327ULL, 0x9EBC70A69B263198ULL, 0x53E7D1BC7CBE860EULL, 
            0xEB3F6D3CB2EA7267ULL, 0xE98838286B62AE90ULL, 0x975D6ADA7CAFE8F5ULL, 0x30D1FF851554A21BULL, 
            0x88BDEC1CF04752F4ULL, 0x150BA05FAB5DA8B6ULL, 0xAE9B2D368749D165ULL, 0x9713E297C05103FCULL, 
            0xDD46706D37D11B0BULL, 0xB9F6A2BEFFE5FB93ULL, 0x3AD8BD0E234E3F3FULL, 0x503974A667EDE51BULL, 
            0xEA12CDA753D69371ULL, 0x138DD8DBF7940CBEULL, 0x8E6F59977A40D66BULL, 0x637216284C386CEEULL
        },
        {
            0xA47801ECF11AC2FAULL, 0x2713D51D4CE1F27BULL, 0x12E34FBA81F26CDFULL, 0x88A1DCA23CD7A9DBULL, 
            0x3A0A92CAA3AC2D23ULL, 0x5622D2C9CD9DCDCEULL, 0x2257EDDBAD31C44AULL, 0xE9427EA4565C40D9ULL, 
            0xF7D8BCA24BDD57FAULL, 0x7B478FF0B9CF2751ULL, 0x031AAB53014D1C7AULL, 0xB1B3791D36DA2365ULL, 
            0x655EDCF4308BAA0FULL, 0x7489DDDAD3D09306ULL, 0xA9E4599BCCEC5CC4ULL, 0xE4DDBF6C9EDA887FULL, 
            0x103C092AEB2CDA8CULL, 0x1F0865EE9FA511FDULL, 0xEA1C5EF2369FBE46ULL, 0x965C848C2E6C9752ULL, 
            0x828027312B0AD5CCULL, 0x72431930C9DE8F06ULL, 0x17DEFDBABE6D9FCEULL, 0xB1E490F1BF6A6820ULL, 
            0x43A34FC3DCCF132BULL, 0x10CDFA760DDEBAFAULL, 0xA588408D47153D71ULL, 0x759B7820A89B527EULL, 
            0x18A9C418F973D8F7ULL, 0xF0E1DF05ED4CC52FULL, 0x82DF4050A7E8C1E4ULL, 0xFFCD996AD1E6ACB0ULL
        }
    },
    {
        {
            0x0BF971B37C8AB2B2ULL, 0xA7C6C2CAAB49BC65ULL, 0xB2CEC8647B774315ULL, 0xEB2DB61C83E0823CULL, 
            0x2500CF7D33231DFAULL, 0xDFF052A465FF8BE8ULL, 0x2F41F54159508B20ULL, 0x6287F9E612F740BBULL, 
            0x6DE8428E19A7FB13ULL, 0x1FB0C4393C9A57FBULL, 0x93C2D0C3C5663074ULL, 0xE820AB4A358A1F60ULL, 
            0xDA9AF205722B716FULL, 0x35D17BBBA644ADCAULL, 0x3FD3E4A84183A2FFULL, 0x0B22473DFB55B6ECULL, 
            0x4DAE7EF06015169DULL, 0xBD2790931797F9ACULL, 0x80ECB74644FD3926ULL, 0x597DDE0AE850294BULL, 
            0xB24ACA1506C71583ULL, 0x2CFB22997B1E18F6ULL, 0x2AAC8D4D653956A0ULL, 0xCAD44F555411C858ULL, 
            0xFC46B804B6E33016ULL, 0x9AFF41C87451956AULL, 0xB1EC5A5281AA71A1ULL, 0xB160391175478E0DULL, 
            0x2A50563A8136F354ULL, 0xB9BC44E838CAD1B0ULL, 0x55B69259F5E8EE76ULL, 0xBC44F98DB6AEDA47ULL
        },
        {
            0x6F780B7B253A251DULL, 0x0DA409BB93D29F61ULL, 0x91B34DDB6DDD04A5ULL, 0x5E7A5DFB4A78390EULL, 
            0x377CA7D067252E36ULL, 0xBF29A1A5E0DA1E1EULL, 0x27669AF604AA33E2ULL, 0x3509178F11F5BCEAULL, 
            0x9E5D46CB30C557BFULL, 0xA2A7664CB0C5BFDCULL, 0xFE592BA79E87F0DAULL, 0xE7AA24545D6893ABULL, 
            0xF68CDC26EDCBD22DULL, 0xF3080F258FDC306FULL, 0xF11382E09CE183A1ULL, 0x253DBA9597E3A0D4ULL, 
            0xF34B626A426579C0ULL, 0x3F3A03BD001D20B8ULL, 0x4914DEBBDB462072ULL, 0x5E426790D7798491ULL, 
            0xBF586622B2D98597ULL, 0x221E9EDF9494873DULL, 0x42F74B5CAA4397B5ULL, 0x9390DC64F3C7B554ULL, 
            0x4120201E29DE9285ULL, 0x1D846388BA132203ULL, 0x37B4051BF5FF0233ULL, 0x066B5464A98EFC38ULL, 
            0xB5C6E6A3BA500973ULL, 0x322C8AA057C1C3E6ULL, 0x6A57EB66BA315A6BULL, 0x16374E13D3C159CAULL
        },
        {
            0x757F781998B21CF9ULL, 0xF6E607BCA043071CULL, 0xAE88353E6ADC8EC9ULL, 0xB686BF90541708C5ULL, 
            0x8BDDD819A6428E02ULL, 0xE0057A84366A9B9EULL, 0xD87A6DF319C7FBD2ULL, 0xA8704CD4C8517A46ULL, 
            0xC1225F35F0ADF39DULL, 0xE9A482085CA00007ULL, 0x4A3BE530E7914574ULL, 0x1028720CB0DD38FAULL, 
            0xFBDAF229ED634C49ULL, 0x225E613CDC222E61ULL, 0x5F83A711A1CD1E8CULL, 0xCFEFA44BDA92B61EULL, 
            0xFB3C3304B87ECB20ULL, 0x0954E93123FD7242ULL, 0xB4674EDD6B77C52BULL, 0xC2633AFE655FC643ULL, 
            0xF8A533E0779F00D3ULL, 0xD69280B8910C6319ULL, 0x67720D81E95BA1C0ULL, 0x58FB815223545D04ULL, 
            0x453EAABA67C1C6FCULL, 0x6955E1AC6567E3DBULL, 0xF28E5E5E67C305B6ULL, 0xEA71269016575ED2ULL, 
            0x1A08A87DFC6A3CC4ULL, 0x0FA86C600544907FULL, 0x15A6A29D3C2B8FB1ULL, 0x301A5DE4E0351785ULL
        },
        {
            0x792C8D6035F0C1A4ULL, 0x436EE8671635BA16ULL, 0xA8B8BAAFE571ABE6ULL, 0xCD3F05D74B13B6CCULL, 
            0xE60000FBD565A2CCULL, 0x9D59D4647FDF604FULL, 0x7133CF5D66A26CACULL, 0x3AD32000541508CBULL, 
            0x1C33DE679F1E26E4ULL, 0xEF72FB5C17E01929ULL, 0xDB73BA01AAF0E5B3ULL, 0xE307F635EB011E10ULL, 
            0x90ECF4F701233F80ULL, 0x1393AEC3C5238A91ULL, 0xAF1EC16737EC440BULL, 0x6B1D36A9A62E2E7FULL, 
            0xCDB5542B51D3369DULL, 0x6593BA3363D80B1DULL, 0xFF26E31EC2033FD7ULL, 0x3A8D969E362F1727ULL, 
            0x53F49C88093A0259ULL, 0xBC1EBA8FBC353D1CULL, 0x8E7B89501F441210ULL, 0x5FD3FEC1698F11A0ULL, 
            0x55C4910E0E46DD41ULL, 0x28C15D5062B81E99ULL, 0x2E27039A60179DCFULL, 0x3EC17CA1881EA165ULL, 
            0x8F15B09BE396C29BULL, 0x3955555CFC1191E7ULL, 0x0576BD6E28C02046ULL, 0xB3019184CCD536B2ULL
        },
        {
            0xAECB866277D81A2CULL, 0x66DC7D625EF9A5B5ULL, 0x6C7AE7E8478BD6EDULL, 0x235E92363755DCF4ULL, 
            0x5AF2A4A500EA477EULL, 0xF71F557A2A38F87BULL, 0xCE1B49B37B157341ULL, 0x25CD34D5503EF05EULL, 
            0xEB54E36FE9B59A80ULL, 0xC6E8A591409C65A2ULL, 0x10FCDA28945FAA21ULL, 0xAC6F344CDDE5E813ULL, 
            0x8FF25882258AB6CBULL, 0x9E27E00FC6B74B66ULL, 0xB6ABBD775B5D08F2ULL, 0x76BF10C6254199B3ULL, 
            0xB6CE9B5A72DFF452ULL, 0x3C099B222987C926ULL, 0x8B56263BC8D41880ULL, 0x661F6E9F4B61F683ULL, 
            0xD573B53F485D0882ULL, 0x0BE949824F4A89E6ULL, 0xD6755583EE4564D9ULL, 0xFAC684B1B9FB077EULL, 
            0x307D0359AB85678FULL, 0x3ADFE79B6B07688FULL, 0x70C4E9715F9AD624ULL, 0x6A9F5DF4AC3A1A49ULL, 
            0xDBEA0F1F32DEEA80ULL, 0x2A7B36CD16737134ULL, 0x68F16A5C10BA4474ULL, 0x38A4D0DC367E2617ULL
        },
        {
            0xCF40BD6CB64C59B3ULL, 0x690075AACBC673CCULL, 0x64AE778DBBB0C8CDULL, 0xF1E37A905CDF0271ULL, 
            0x44E99A28F38218DEULL, 0xF5B1E548602F19ECULL, 0xD97D22A1502C4F96ULL, 0x16CEA71A89FB4811ULL, 
            0xEAB38024B06B0B6AULL, 0x7DBAD5FAEFCA9B7EULL, 0x8CDAB7BC18F4F043ULL, 0xD3C2D88DEFB01A7AULL, 
            0x1C60187BB1F78226ULL, 0xFF1EB4C6B91822F4ULL, 0xF40E11770CDCBA97ULL, 0xE0E6CDF48BA32BA1ULL, 
            0x92FE504450D65107ULL, 0x061748E3BA4DF12FULL, 0x54ADD959119D3EA7ULL, 0x8000A8BB46E881FAULL, 
            0x77B32B12B71C49F2ULL, 0xE4EB36B02BACD24EULL, 0x87A0068BB77E3A96ULL, 0x389AEA6230FEF3C7ULL, 
            0x32F1929959995095ULL, 0xF4D732EC382C5F95ULL, 0xE5BD9E38D22B39B1ULL, 0x7602AFD1F7C8CAECULL, 
            0xA6B4EE01C4DEF6BDULL, 0xC6521AD1DAE766D6ULL, 0x20CFA84B682BD618ULL, 0x7E1AF7EF063AB987ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseFConstants = {
    0x3B721C7A46CE0652ULL,
    0xB2F164FB8E2DEA00ULL,
    0x20CAF4D5048C24C0ULL,
    0x3B721C7A46CE0652ULL,
    0xB2F164FB8E2DEA00ULL,
    0x20CAF4D5048C24C0ULL,
    0x2AD7C01C002880FAULL,
    0xBD0AC14CC77F0159ULL,
    0xE8,
    0xFA,
    0x51,
    0x9F,
    0x15,
    0x22,
    0x21,
    0x61
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseGSalts = {
    {
        {
            0x2AC4415A8DD0D317ULL, 0x1C890FC9FF971D8CULL, 0x6082F3D1DD2BA562ULL, 0x9EF007243C0354E4ULL, 
            0x610E52F5ADFC3787ULL, 0xDEBDAEDA5D547141ULL, 0x99DF990805DE3796ULL, 0x272397A9598488E3ULL, 
            0x31F80D343F54A633ULL, 0x943F717EC842924CULL, 0xC0AC36B02331C460ULL, 0xA30B8F3E58179EEAULL, 
            0x8E996CDFC1EA3A6FULL, 0x813A4D4A52BB5438ULL, 0x4C635FEEAA154737ULL, 0xBA9EAED0B9107780ULL, 
            0xAF4C13F39484FDFEULL, 0x3CF69A30801FA996ULL, 0x4586516DF76CA830ULL, 0xA15D79E00BFA0183ULL, 
            0x95058D4F04953E01ULL, 0x4AA9CD790A8E4D91ULL, 0x291D6D9AF75C916DULL, 0x71F0F16D88337406ULL, 
            0x73BC5E740675FF47ULL, 0xE4D718A96C039BECULL, 0xFB2D8639314AA924ULL, 0x4B4F01E749ADE8BFULL, 
            0x7CF13D08ED61C598ULL, 0x9A9533F80205B51DULL, 0xFA4E94BBF50B58A8ULL, 0x6A737BA5719727D7ULL
        },
        {
            0x6167016911C8E26BULL, 0x62A37CFD4A046AE7ULL, 0x32AD5883A8C591C5ULL, 0x36632ED3B46CD73FULL, 
            0x2A959CF2D770B15DULL, 0xA7A3E113D1E88D04ULL, 0x568B05ABF25DDF4EULL, 0xCF533718002D3ACBULL, 
            0x07829ED19754D4EBULL, 0x19AA5289260BAEF9ULL, 0xDA0DF10F46BF1E05ULL, 0x452DD0F5F7C2713EULL, 
            0xC67D3D56AF683C60ULL, 0x81640123CD357A89ULL, 0xAC9B45C3CAA90C65ULL, 0x21EE7A35F171ADBEULL, 
            0x59DD6D32EDDCFA01ULL, 0x551EC368E4704915ULL, 0x1C28163B7387FEDCULL, 0xEEB2967141911231ULL, 
            0x3343EC5488BC9FCAULL, 0x3E33A172166B9D43ULL, 0x57C7C112B16E1D1EULL, 0x1A087B184437B9C3ULL, 
            0x37DEF11CD3A6A9E5ULL, 0x5D7CE077B5BD17B6ULL, 0xCCD472EE91A6D6F0ULL, 0x3B0DA1A70C1609EFULL, 
            0xE7A4490103DCB9F1ULL, 0x8D956BD0F91AA099ULL, 0x5DC91C8459BE92EBULL, 0x3FA57859F0248F19ULL
        },
        {
            0x165CF613F1EC652FULL, 0x1DCBDA8F6D2CC633ULL, 0x03541F271118C64EULL, 0x38071C20BBD601E2ULL, 
            0xF24AE5A6912A5C15ULL, 0x60884669CA9ADA75ULL, 0x7EABD34CCAFCB80BULL, 0x387162874511C41AULL, 
            0xB46BE47405A7578AULL, 0xE18711B998766101ULL, 0xA64FA0D7CA8A2738ULL, 0x939FEB7477D443B9ULL, 
            0xAE205E6A9AB884F1ULL, 0xF219366E7FED465DULL, 0xD29E8B761E69AF88ULL, 0xAC90698D8FFB2C89ULL, 
            0x751481E93D42B673ULL, 0x7625BAD2DDFA12A3ULL, 0x0216D226610DBF8FULL, 0x0CE5E2A372C88571ULL, 
            0x372375284B1D9A64ULL, 0x53E23278DB3B5AC3ULL, 0x3C72B349AC00B669ULL, 0xBF93DC038097C983ULL, 
            0x23BA7D4F696B6ECDULL, 0x6C32A5524078685EULL, 0xADCF274E2F564FFCULL, 0xF8989507D62CAC80ULL, 
            0x015F6D6429EB00DAULL, 0xE4E3D5815119536EULL, 0x8069CEE3A50151F8ULL, 0x355A7F4109AD51CBULL
        },
        {
            0xFC4DF53EE34585D8ULL, 0x6E65D260E47EF3E7ULL, 0x579BCBE28A30D49BULL, 0xC278E49CE3E9EE0DULL, 
            0xA13D088D7556B508ULL, 0xEF78A7DF56ABBC42ULL, 0x58AD260F41419A0AULL, 0xAC492685559DCF58ULL, 
            0x69CF66DB2E4F2DA1ULL, 0xA0412367BF25EF8CULL, 0x9265CD85D120838FULL, 0x3400F27A3BCC0572ULL, 
            0x3A3AD9D235CCCD0DULL, 0x07F501F8FF52072DULL, 0x3C6F6E75B54463F6ULL, 0xAE97683BD8EEE37DULL, 
            0x9BEA83CE53C4992DULL, 0xCCE92AB9DF0EEBE3ULL, 0x52CAAC010700D46BULL, 0x3A21B95AE052BBC1ULL, 
            0x1DB4B7FA353DCE94ULL, 0xD7F316DEA55A6ED8ULL, 0x52E4CD89268DD7CFULL, 0xB5C5C12E96101837ULL, 
            0x0205444116AB61AEULL, 0x0088468043CCC322ULL, 0xB12603A09D7379D3ULL, 0x7B27DF379F1B1531ULL, 
            0xECCD91996A0A4235ULL, 0xA76658F1371E4BA2ULL, 0x6A740241FD57F17DULL, 0x57D3A1BF95F817AFULL
        },
        {
            0xC4CEB137719210C9ULL, 0x3D6D0837CCC85624ULL, 0x2FF529062B295163ULL, 0xD6CD3FC68488F78FULL, 
            0xDD01A342108A117AULL, 0x3650E2226985C083ULL, 0x5AE5027ACD3CA103ULL, 0x6AAEB20D9B16D4FCULL, 
            0xD98DFBBF4447DBF1ULL, 0x1567A6522CC7A93EULL, 0xADF4087C55E6289FULL, 0xD5C8B505E2D6D59DULL, 
            0xC993E7EE2A2238ABULL, 0x794809300147AC6EULL, 0x580E1747A24797E7ULL, 0xC8097CB9B8BE6D2CULL, 
            0xE006C5A18FD8612BULL, 0x092200321E5E5290ULL, 0x563F9E0232530895ULL, 0xD0BDE12FB440415DULL, 
            0x227376BBBD8D503DULL, 0xDEF710134BB684CEULL, 0x0A752FE76D81F7D2ULL, 0x1878518C79360CDFULL, 
            0x4966E12A83075C35ULL, 0x2EF6D9CBAEF8A07AULL, 0x8A5DD307ADE7A856ULL, 0x4B1D687443D47498ULL, 
            0x7E7005897DE6D690ULL, 0x7FBDBFE54DF58799ULL, 0xDD54677180456A45ULL, 0xC6652E872AD89E1BULL
        },
        {
            0xAD4F42DA4206A747ULL, 0xC01BB2F3904C5C6BULL, 0x5F8544999E5F7E47ULL, 0xB493E5EF93D24B4BULL, 
            0x41B5EB90D4D94BB3ULL, 0x501B902CEBDB9111ULL, 0x05100A9601397A74ULL, 0x234B719DE0516D6BULL, 
            0x632E6A48AA619884ULL, 0x46A8E24A1C7592C1ULL, 0x3035F5CF2903E206ULL, 0xB657B4421DE04308ULL, 
            0xA4E0523C149C7B6DULL, 0xED4AA74069774779ULL, 0xBA66186A64AA3386ULL, 0x32FBE203860D7B1CULL, 
            0xE46F3B2B7D70CF15ULL, 0x7A0F240D0AA9B577ULL, 0x146C37A70FD93A07ULL, 0x4C8FE52E88B7C184ULL, 
            0xBA3A40899C4663B2ULL, 0xE039D5255681817BULL, 0xACD77FAEBA1B456FULL, 0x6D0313549462B9B2ULL, 
            0xDB7097AB9B7E32CAULL, 0x2F05BC1BA0B050FBULL, 0x30018542D4465FF7ULL, 0xB963B305CDF90AB8ULL, 
            0x20E2DC2A9D0C7AC6ULL, 0x6E4B9792F9D8F048ULL, 0xC22EFA3EDBBDB065ULL, 0xFE5EF9732FDB7002ULL
        }
    },
    {
        {
            0x05F48AA54D453ED5ULL, 0x3C157FEC354E196AULL, 0xFB44F79A302ABE2EULL, 0x9C0421785128AF3BULL, 
            0xDB4CE93B8F47ABA3ULL, 0xF4C37AAE1B3096A5ULL, 0x2033781177DE32DAULL, 0x2D27F1D342DDE65DULL, 
            0x14D96E8EB241DEDAULL, 0xA00DB1E34A97239CULL, 0xF5BF91EA7FD3E453ULL, 0x47F9B5BC645E21D1ULL, 
            0x4141B82896C373F6ULL, 0x9ACDD44F73516941ULL, 0x5CEB534E1FACBFBAULL, 0x9F90654664011896ULL, 
            0xED1757BCAB3CA8DBULL, 0x4FB6C0A5D0AD34C7ULL, 0x72D616D0325E9622ULL, 0x40632388C7B6E3B7ULL, 
            0xE59F4C48626A7B01ULL, 0xBE12681A6D3E3089ULL, 0x4CB26D0AF3B53615ULL, 0xE30E7EB6F55E1468ULL, 
            0xD3E5AF1E88C9F481ULL, 0x32BE7E9764C16E39ULL, 0xA2780C1B20C41E5CULL, 0xD31933F29B948FA2ULL, 
            0x2F57AFB12944657CULL, 0x714E090C5FB6BB13ULL, 0xAA9C146CC3657EF4ULL, 0x392DBB575652D328ULL
        },
        {
            0xA78601D6E0CC96E3ULL, 0x69D938CBA1ED94F6ULL, 0x8BF8811585F70B13ULL, 0xCE6E913E5580AAF9ULL, 
            0x1AEF21B7728D79CDULL, 0x0F8C49588D53DE3FULL, 0x5FDCBE6B30BA4ED7ULL, 0x02EEC05F3CD06A72ULL, 
            0xF9325A27FB73CBF8ULL, 0x562D7C4687566FAAULL, 0x815E249E269AA12AULL, 0x39E26D027EAF1BE6ULL, 
            0xA195A6F76ECD3EB8ULL, 0x7CAB25E100501515ULL, 0x2DD9376747FA1F4DULL, 0xAAD389439E3ACEA5ULL, 
            0x611999EA1C6008AAULL, 0x333CDC4E3EB4ED0DULL, 0xF36211EA750C32C7ULL, 0x750DCD6AB5E96888ULL, 
            0x9DD237C078C07AADULL, 0xD6654CD8593A16DAULL, 0x54451728F1569E4EULL, 0xC665D26EE80E899CULL, 
            0xB1AD4DE0D1217D56ULL, 0xFD28E6D8B4CA5D1DULL, 0x4CBCB13E52BFCCE5ULL, 0x44F3446227B6F8E9ULL, 
            0x0FC4434136DFAB0CULL, 0xBFB1E22317D2C1FAULL, 0xF68A96B678EA307FULL, 0x84F03A954E368FF3ULL
        },
        {
            0x0B09036724F28A3EULL, 0x93A63AF5D55EF5A7ULL, 0xA75C69B522DD813AULL, 0xC3680FA67A3EC376ULL, 
            0xA9874171AF050A33ULL, 0x631CDD395D8DF9A3ULL, 0xEB5587DF0A58826BULL, 0x81C36A30E27E237EULL, 
            0x5F0FDB0EEF6EBBADULL, 0xD61F21899C2C2384ULL, 0xA31C32A5BF14F410ULL, 0x67C8DFAFB62E02E9ULL, 
            0x2D068645FE8C873DULL, 0x0399D335D2C48C82ULL, 0xEB5CC55115B97762ULL, 0x9560E50BEF787419ULL, 
            0xF97B0059D6C06E53ULL, 0x39FB6E46F13F5CDBULL, 0x490BF6C340C63354ULL, 0xF948B2C00664C716ULL, 
            0x5CF0B1620A4D2898ULL, 0x02539E633CA675AFULL, 0x53E66EF65030EF4CULL, 0x79E62B6797F5A8B0ULL, 
            0x87B5D91523A642A8ULL, 0x788E65FA472D4047ULL, 0x0D59EFC246261E64ULL, 0x6421CD08C0D42D98ULL, 
            0xE30639765C24B368ULL, 0x3E90B2C344E5F635ULL, 0x9F5D073189F2AA57ULL, 0x14059F411299D521ULL
        },
        {
            0xF0A6CE3CF0CFB572ULL, 0xF1FBF41AADEFF23AULL, 0xDD1B2969CC8B9139ULL, 0x6826E21C516CB0C1ULL, 
            0x25BE72E1108A45B4ULL, 0x56D21068ABB857DFULL, 0x1ED6BF75EEFD488CULL, 0xA032DFE977AB6701ULL, 
            0xBC00FD5D2DABCEDAULL, 0x36E2C43213373EE8ULL, 0xA24710FFA8568B98ULL, 0x19ABF47FB61E5584ULL, 
            0x601DB85DBDEA55E1ULL, 0xB24EF73806B58274ULL, 0xE15B2545A70980CBULL, 0xC8B973D092891CE0ULL, 
            0xFBC8329336998618ULL, 0x2CC7C972FA285ECBULL, 0x2DCB60B4D61D0899ULL, 0xC29FEFFF48E42E0CULL, 
            0x90C4C0ADDB356326ULL, 0xF0A0EC89480F5E91ULL, 0xAEBEBA02E521D101ULL, 0xFF32CDC539C62294ULL, 
            0xF2736C7146F120C7ULL, 0x7BC8BEF15947412AULL, 0x441646976EDD4520ULL, 0x5357C38F895D9B4BULL, 
            0xCC45430860EEE7D6ULL, 0x6B2DBB7DC8D36E17ULL, 0x1AF88BA444A33A6BULL, 0xF54EE498EC097165ULL
        },
        {
            0x92FD41960C367D1CULL, 0x33C357BC6699038DULL, 0x010B67045D7C8815ULL, 0xEC96A7A19BD4056DULL, 
            0x6C211D60A6F87379ULL, 0xD8B9293BC1F4ED67ULL, 0x7EEC3BB48A0E4114ULL, 0x56C07E8C4EF33006ULL, 
            0xF3D81142FA4B5089ULL, 0x66B5D360554BAA77ULL, 0xB22DE77E587C005CULL, 0x350CB51398BDC364ULL, 
            0x9C046B84E12D5B75ULL, 0xD9F54F6AD62B86D2ULL, 0xDE55C7A1136BC846ULL, 0x5AE7B5C7B62A565EULL, 
            0x0DE820BB8C3A0892ULL, 0x164E12FE9A036500ULL, 0x4831088051949C93ULL, 0x997E80FF9A46FC03ULL, 
            0xA6072ECA9C56C386ULL, 0x67A5F548E2694B5CULL, 0x149BD41E840DE0EEULL, 0xEA9551F13BBBBBBBULL, 
            0x4DF9C2A92434B2FAULL, 0x76EEBD9F23977206ULL, 0xF6BFDA16EF7F1481ULL, 0xDAE23B1CA4325A05ULL, 
            0xF6590E626E126F8AULL, 0x6B4123A2475844BFULL, 0xFFC319F8B30E40D1ULL, 0x71DE8754162559ACULL
        },
        {
            0xB29F6DD2C27E0960ULL, 0x04BA85FFB59F3FBEULL, 0xD1FEFE3DAB1E9A0CULL, 0x146E19382FC9E3D8ULL, 
            0x554413A1B28C8416ULL, 0xA8D1A107DF359F7BULL, 0x27E943F2A42DF498ULL, 0x9BBF11BCDBA4906BULL, 
            0x07AB4217C1520F19ULL, 0x7C1ACED1CE68E842ULL, 0x2EBA565BAB614867ULL, 0x6327863F247DBFF6ULL, 
            0x8EBF60A8D0836C95ULL, 0x1A6AD053C1FABB07ULL, 0xB507980FA03A08DAULL, 0xF07D3946E58E8C80ULL, 
            0x37E88A810145652CULL, 0xD13D94289765780BULL, 0x5FB5CFEF740F3263ULL, 0xE5EEED2261809AE9ULL, 
            0xA4858E9F37DEB5CFULL, 0x9C12DA8F1B77010AULL, 0x2FE70A3FFBC38175ULL, 0xA18BA4CD7034AEE3ULL, 
            0xD29DCF1B73D6316AULL, 0x0D8644AE319AD615ULL, 0x0E679F5D0642102BULL, 0x395A458A81F6D647ULL, 
            0x199AB242201CD382ULL, 0xC45F7D558EC0A745ULL, 0x6EFAE3B2FABA9301ULL, 0x9D583D27673EF35DULL
        }
    },
    {
        {
            0xA886352685144340ULL, 0x235CC480270478EBULL, 0xD858B36270B200B8ULL, 0x3F08FBCEEEE1E0C5ULL, 
            0x8739439F0AB5225DULL, 0x188888124A428DD0ULL, 0x87B6F6C23F507D97ULL, 0x2C7350C213F6380FULL, 
            0xE33E478175EE8026ULL, 0xBD49090F8C92ABB2ULL, 0x00310D4FFB1E9AC2ULL, 0x2AD9806C2A88074CULL, 
            0x476D6147AB563E24ULL, 0x0302AE26A79CE930ULL, 0xB6A93F653F5A5279ULL, 0x42B8AFE271CC7FF8ULL, 
            0x1458E1E9E04441D6ULL, 0x8A1D7BE38A9A591AULL, 0xFE1850627BD712E1ULL, 0x9CEC527B503B5728ULL, 
            0xE36BA8E250853BFCULL, 0x224CC80FCF0C4C96ULL, 0xF3925738D3E00BCAULL, 0xBF019048593A9851ULL, 
            0x2CCD2CE249BD5FC2ULL, 0x390078064DA78AD8ULL, 0xC2725789DFAD7FF6ULL, 0x9F0047A470D32026ULL, 
            0xCF81DAF515B13965ULL, 0x8707FBB25D00CA89ULL, 0xD3B994EE75F80865ULL, 0xA6D391937FBF85E6ULL
        },
        {
            0xA1FC81CE8ABE7DB7ULL, 0xC68E84F5DDADE18EULL, 0xEDFD668FA6C7D465ULL, 0x5B778AD91DDBA2BBULL, 
            0xD79129FA85BFF387ULL, 0xD3BAEA14F4047D76ULL, 0xFDA53FA8153B133AULL, 0xDF40B958A44BB1E2ULL, 
            0xBA6953440032FBAEULL, 0x5E5603F6683FF3EBULL, 0xFCE7CFB55D37F4E9ULL, 0xD56C6F6E0887941BULL, 
            0x600924C0659BB6CDULL, 0x2A88F14A1DB04636ULL, 0xBDC171BBEF720C67ULL, 0x66032C1D23E4B974ULL, 
            0x1C3F8F5E0321C082ULL, 0xB782E313D35BA684ULL, 0x71556BB9D2F630E6ULL, 0x3C6841E3EFA5BA19ULL, 
            0x793D85A136EEEE1EULL, 0xA6407323CE7D8AFDULL, 0xCB501716BAD33F7BULL, 0x0663C4305A70332DULL, 
            0xFA456066222D08C0ULL, 0xBAB8B7B148F16BF7ULL, 0x69E581097A6C9FA5ULL, 0xA667BAC65F4A7EB7ULL, 
            0x253768E62C7D7E6DULL, 0xC20BFC2E4A8FE469ULL, 0x6055476A47249128ULL, 0xE739205D7EA50B81ULL
        },
        {
            0x8D437AF19208FC98ULL, 0xF9060B57ABFFE157ULL, 0xE6B4641A830CE813ULL, 0xF59AA98D0274A2A5ULL, 
            0xE6C396F0B775FA7EULL, 0xFB3174D6488F9F35ULL, 0xF078A2CAE9C9F88CULL, 0x0874F12EB24E2A73ULL, 
            0x19659F438BB91F74ULL, 0xE879F65FD967409AULL, 0x68745B69B5709516ULL, 0xCA71707252DCD36EULL, 
            0xDBBEFC5011915CF1ULL, 0x0214207AC70F38CDULL, 0x296CC343D6060ABCULL, 0xC792C513FE07EF21ULL, 
            0x0EA2261776B11495ULL, 0xC3328841BEA7192DULL, 0x83257487DF5420EAULL, 0x115A68EE9ADB9357ULL, 
            0x08C0BFB74FA8686FULL, 0xFBE3DEC785D22BC9ULL, 0xBC3E416F896998F0ULL, 0x7C0831B0EC7CE94AULL, 
            0x0EECE5E48DEE1E93ULL, 0x20E3F732404A1470ULL, 0xFFA524AB00E89A40ULL, 0xDC84EFE522DDF40FULL, 
            0x9D6B2C1768726A48ULL, 0x93D0BC38CE433D24ULL, 0xD9E20EF38287C015ULL, 0x545CA46FB9E97B9EULL
        },
        {
            0x7FB1A02ED12C5CE5ULL, 0xE921B51DA61C5D33ULL, 0x9FEB79557F1858E8ULL, 0xDDD474173A63FAA1ULL, 
            0xA3B792FF4FDB49B9ULL, 0x4DF00DBF2B4A5730ULL, 0x12FAF895A7601DADULL, 0xFA75BE8286178EC9ULL, 
            0xB9D1CE15AE6C52E2ULL, 0xD9D1F1AA2DC83B79ULL, 0x7E57CF6CF7F2252BULL, 0x669F9EF70F9EBB26ULL, 
            0xFFAFEFA9C7743E3CULL, 0x8342CFF8283E28C3ULL, 0xF89A49C05E380B1DULL, 0xD4A81458BF3088B4ULL, 
            0xDFECAC421C2371CCULL, 0xE500E5F8951103C0ULL, 0x0E06EEAC6EA075EDULL, 0x03686220D589868EULL, 
            0x92BF0485A043E68BULL, 0x70663D584FC2D95DULL, 0x1246159833183024ULL, 0xA8061FFD2EE8CE3AULL, 
            0xEF276AFE318377E7ULL, 0xCEA886FD068E57ECULL, 0x43005BC84B65A42BULL, 0x95E0377A5F3DBF06ULL, 
            0xCB4ECE378A648E1DULL, 0xB010E78B7DF4E013ULL, 0x0A1B6E91DC1FFCBDULL, 0x63E3081DEE632609ULL
        },
        {
            0x0AFE6BBBD9D32AE4ULL, 0x7E63E0FA066C11CCULL, 0x12B98664DF044954ULL, 0xD385D02F35EDAF25ULL, 
            0x2DA1658DA54D40FEULL, 0xFFA6C436F8DCDB5BULL, 0x5BF4D9FE26971DB6ULL, 0x8416F07C0346D671ULL, 
            0x892F7F6AEA7B46A8ULL, 0x24FD5A797AABFD64ULL, 0x2D60D036F2E82619ULL, 0xF7A1E1E40408F0A8ULL, 
            0xC41671A6A667D103ULL, 0xE0982FBFFDF74BBBULL, 0xE749F24FD4F025B2ULL, 0xCF02E4A49E5C70A2ULL, 
            0xAA936B57513067DCULL, 0x712FBAA0FEDD4B1BULL, 0xE9263BCBC1ADEE28ULL, 0x90F060C96B41F12EULL, 
            0x42A23637CE55E9F4ULL, 0x51F3B185FC43CA50ULL, 0xA84E263649E13462ULL, 0x587D562952D101A9ULL, 
            0x7C875E3445E48C59ULL, 0xE37371DD7F06BF66ULL, 0xA066ACE13319EBDFULL, 0x1075F498267CF647ULL, 
            0x9F22F5A8B3224431ULL, 0xABF62C1CC509C3E9ULL, 0x1F4B7221A983AED0ULL, 0xA368E357C8674308ULL
        },
        {
            0xC94E4E04F5317181ULL, 0xD0FA55574DC684F4ULL, 0xB21ABD4F5E1AE00FULL, 0xA9583DCC95AD4163ULL, 
            0x24898D2C2ECD3C23ULL, 0x77369F20E470A2D7ULL, 0x02B1103C8B307983ULL, 0xA46396C6E5E0BDE4ULL, 
            0x89BBCFC3938AAF8FULL, 0x23F50C5FE43E4EC9ULL, 0x25BD25E58C298CE5ULL, 0x9E8F2C834DC8F2B9ULL, 
            0x859F1AE31E006D03ULL, 0x0202BD56C5C87D5BULL, 0xCF5CAE58DAE1E97FULL, 0x3EE151BA9436914BULL, 
            0xA77A16E4D8BE5EF3ULL, 0x28916CA43D4C37BBULL, 0x56B311EEB1CE2CA2ULL, 0x81429C632D092A4AULL, 
            0xD9945DF0A5C001BEULL, 0x97FC805AF32ABF38ULL, 0xBD0279FB29A362F6ULL, 0xEA61BC50438EDE36ULL, 
            0xAFF534CDDBC8DB41ULL, 0x150AF4E7A2953176ULL, 0xF866150AD3667686ULL, 0x7577B74E7E838F9CULL, 
            0xD33C1060BBBB72D1ULL, 0x4C738CB513E77581ULL, 0x81AFA219BD8F2049ULL, 0xCCD88C600848FB2AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseGConstants = {
    0xA0CCC4AFDD04BAC3ULL,
    0xC97031D9D5D903B3ULL,
    0xF723E8EE4DD4C84AULL,
    0xA0CCC4AFDD04BAC3ULL,
    0xC97031D9D5D903B3ULL,
    0xF723E8EE4DD4C84AULL,
    0x49B05C7C7C22614DULL,
    0x2660D14EABB796B4ULL,
    0x37,
    0x35,
    0xC1,
    0x3B,
    0xD6,
    0x2F,
    0x67,
    0xF7
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseHSalts = {
    {
        {
            0x20664C4D5C07E465ULL, 0xA12AC6484EC16453ULL, 0xF80A900ACDF10784ULL, 0x76D13F41103E50CEULL, 
            0x8265250374D0FF58ULL, 0xFFD46341B8E2D5E2ULL, 0x6A78E97BC5F08692ULL, 0xB860D739C41C2E99ULL, 
            0x4A4B046CF7B03DCBULL, 0x91913C8C5BED678FULL, 0xFE986C7DE78CAD75ULL, 0xEB6566F330693F9DULL, 
            0xC93EAA2D6A8F5970ULL, 0x6000D932E92077B8ULL, 0x90EEA843D16271C9ULL, 0x194EA41EC0CB8DB6ULL, 
            0x3A02958554553781ULL, 0xF83E1A97767309E9ULL, 0xAC907A3688AB7B52ULL, 0x588FD4AEC47BE0B3ULL, 
            0x230A23DD50A45011ULL, 0x28AF9483F21B4137ULL, 0xC7EA8C408A3B5985ULL, 0xAAF130DFA1089966ULL, 
            0x46978C39363FFA7FULL, 0xDC005A0FA7CC1FE6ULL, 0x3461B5C3C19D9B9CULL, 0x9320967ED3C9D226ULL, 
            0x97D8F0348D13083BULL, 0xC69BAF1DA1CF2140ULL, 0xD76BFBDB84CACC89ULL, 0xAF311E6EC0728500ULL
        },
        {
            0x8894279AC2F02E41ULL, 0xBCD30A94533DCE1CULL, 0x4B73D9F4420F4910ULL, 0xC1E7E62F35FECF0BULL, 
            0x91EFB31F792534C2ULL, 0xEEC728CB42F3FB84ULL, 0xF8FAB56BCB5B7730ULL, 0xA0F97D57D7940506ULL, 
            0xA32AE09553162149ULL, 0x66EB0EC9DEF420F6ULL, 0x7BABEEF90408BCEBULL, 0x38377975A872A9F4ULL, 
            0x58EE7D32C5581D87ULL, 0x914062F6FF07D6E7ULL, 0xD6B5A19E4A8CC6D8ULL, 0x95F33A81500D4B31ULL, 
            0x058A866BB45C22EAULL, 0x89D2840B8AEC13DAULL, 0x9C584D55E1DBA955ULL, 0xE73A172D3695685DULL, 
            0x8F75209B95549552ULL, 0xB8DBF93181D4BB75ULL, 0xA3A6F51D12302120ULL, 0xC946A4C2CE279C8CULL, 
            0x3D933DE60B5372F7ULL, 0x4823A1029BE8227CULL, 0x81F081F9A136475DULL, 0x1F2DE774C30F5202ULL, 
            0x14482453B20F41C7ULL, 0x0C2B86D866AB9A10ULL, 0x47B7A7235281ABD3ULL, 0x2FAA5522FF9898F6ULL
        },
        {
            0x4C7EAF3C03238EA6ULL, 0xA10BC0490133E79EULL, 0x0BBF8D0B039071F1ULL, 0x308C6DBAE283181EULL, 
            0xC62749EB393A5300ULL, 0xF00C3FADEE5A8420ULL, 0xF8F91B87A2A71A25ULL, 0xD6654D42845B3606ULL, 
            0xE0F3104946422B40ULL, 0x0327374C8D75B9F4ULL, 0x74D77742C418E62FULL, 0xC4E8A461606589A6ULL, 
            0x215120AF5C83C732ULL, 0xF481BBA327FF8DA3ULL, 0xF8646A7F7EC24143ULL, 0x1A4B93A088B8F271ULL, 
            0x4511BBD836662F20ULL, 0xD3FFBA5BE19EE137ULL, 0xC86BF6F6D9629367ULL, 0x099EE1B01BC02D4BULL, 
            0xC65D6645EFE40494ULL, 0x658577060DFC8937ULL, 0xD707BDF60D08B093ULL, 0xF9344F102A701C59ULL, 
            0xB8F6EBC7CA668A7CULL, 0x7B72D010952475C4ULL, 0x28FBD8803155143FULL, 0x0FCE55D7E7E3959FULL, 
            0xF631069ECF5041BCULL, 0x7020A99CAA6BB7C5ULL, 0x945DFF58D413C2BBULL, 0x8FA2B0AFAA08D4FFULL
        },
        {
            0x696DDC87C972EF84ULL, 0xE9DB80C19C6B0F6BULL, 0x7E48921AF82162EFULL, 0x0400E30EDDF6C937ULL, 
            0x9E44E3E9CA033220ULL, 0x9E00F65AD9CA4520ULL, 0x329E5A10CC335904ULL, 0xC99F27192C4169B6ULL, 
            0x3795B40A279AADACULL, 0xE9E1A4AA246F6ADFULL, 0xCC3432DB7EADCFD7ULL, 0x1DDAFBAA4B042119ULL, 
            0x1AE6CE91AD4D1A48ULL, 0xBD5350D52EF0404BULL, 0x4F4042FDD61B4473ULL, 0x8F8AB21E55A3E5C5ULL, 
            0x44152D812BB16D90ULL, 0xAA5009D6AFCE54B7ULL, 0x2F38314855EBBDB9ULL, 0x2404F12BAC1573FBULL, 
            0xC3327C6A3C08C9EAULL, 0x6E1FC12C2DAF60A6ULL, 0xE13A1501A70BB898ULL, 0xE4C8C1DA0168FE85ULL, 
            0x85C027386C306E99ULL, 0xEE01692BE235D63FULL, 0x6BC66AC4F88E3B9DULL, 0xDA597DA76ABB7FBFULL, 
            0x0B9489C520A07BDCULL, 0xCBA21F1A591B16BEULL, 0xC29E28EDECA8EE55ULL, 0x2427CC27F0E70568ULL
        },
        {
            0xD2EB7B4C52A9843AULL, 0x703082CBF3C59772ULL, 0x050A4CB86ABB549DULL, 0x046E9066F605010BULL, 
            0xCD1651C881A55E43ULL, 0x7D5C709B0F2F6930ULL, 0x01903A7D1EEA072DULL, 0x6CD202A02F07055FULL, 
            0x4F8492A92E551B88ULL, 0xD9BC93BA3428388DULL, 0x3034ECA86682C60CULL, 0x4DA997D76B879217ULL, 
            0x18E529BAE0ABD2B0ULL, 0xC62D48860C355B6FULL, 0x3270DD6B3ACFF3E8ULL, 0x40899D00204BE495ULL, 
            0x5781B0B2F6EEED28ULL, 0xD7A21028B327C250ULL, 0x4A8DE258E128E38EULL, 0xEA9A6F6D80FDC481ULL, 
            0xE7B21B836D7A99E5ULL, 0xE7C303E75697FB77ULL, 0xBACE597A3E62C04AULL, 0xC3ACFEC6F7542DE9ULL, 
            0xCA27A845C0E078FEULL, 0x9DFA044C2B1E4987ULL, 0xD1AB60A85857C810ULL, 0xEA4097D89B8A730AULL, 
            0x4BC471AF8D4736FEULL, 0x7D9E70E4633B41BDULL, 0x4CEAD474B039A46BULL, 0x89DAC26CD413D69BULL
        },
        {
            0x14392D2EC52ACF17ULL, 0x842969CD1E2AEFA7ULL, 0x1E9A92FB34C3234FULL, 0x4EF33FFF7E55EA16ULL, 
            0x8174E2E51BB506EFULL, 0xC9138D13FCD38F57ULL, 0x30549DE6F3A734B2ULL, 0xE2A20A06008C2505ULL, 
            0xAD621F911BBAB977ULL, 0x9C3C0278FEC3A560ULL, 0x0994092D2EDB9655ULL, 0x5F8C959B9AA25CC3ULL, 
            0x039618863BCDF6E6ULL, 0x3077B220D174E22DULL, 0xE86D525F88026CE2ULL, 0x524963E4E14805F0ULL, 
            0xD06D4ED70EBACE43ULL, 0xB8F1FD4D38D71529ULL, 0xC4F54666D5397F7DULL, 0x5A9200EB807F763EULL, 
            0xAAE142FDFB22F4B3ULL, 0x473FB1885F5093A5ULL, 0x2393C2EB2C6B34EAULL, 0x89976A90C075BC43ULL, 
            0xC6B0DB58F7198588ULL, 0xD15AB9527C85DEE7ULL, 0x1A219828F455EF35ULL, 0x2660790455CFEA54ULL, 
            0xEE4C1D62120C9219ULL, 0xA15ECC76F4F6E950ULL, 0xAB37D534CBB8152AULL, 0x5ECC82986462E4A7ULL
        }
    },
    {
        {
            0xE9F453D41AF5180BULL, 0x288F32F8422D9A28ULL, 0xEEBC84F52E6CEEB9ULL, 0x82BC9CFC6833E15DULL, 
            0x6E231FD8037B0082ULL, 0xA7F0C2EE6E6C0AF4ULL, 0x8828D12C74B2A8BBULL, 0xDCB5E931CD7039B1ULL, 
            0x93EF7BFB07A08A3AULL, 0xC0E882E4973E28F1ULL, 0xF1454634CEFB4F1FULL, 0xF740767D3FF2B9EDULL, 
            0x56A638E77F8A10BAULL, 0xA41F4F8DDE2E4583ULL, 0x845C2FDB53F41057ULL, 0x2AAD343DBF07F36EULL, 
            0xC9D6975BDF195E88ULL, 0x6F6074BF3E586951ULL, 0xC9DD75950C45BBD2ULL, 0x7A89391676F0A445ULL, 
            0x78BEC17A1A5F6787ULL, 0x09A4E4B6C92BAF78ULL, 0x54FD59C8F533F4ACULL, 0x57B6225D26708EDAULL, 
            0x79CB7034BE44707CULL, 0x39B54BF4ED753E6AULL, 0x2912E8AF54F0DE73ULL, 0xC7514892942FE2BAULL, 
            0x38D5826EEA7CE8CEULL, 0x125F6F9F94AB6162ULL, 0x56EEE82E5C106FE2ULL, 0x42CB5DBE28FFA546ULL
        },
        {
            0x91D5B5912BD270DAULL, 0x951D39D34CEE016AULL, 0x29B49976CFCFA06CULL, 0xF59423DBB7EBEA12ULL, 
            0x012652C367516F2FULL, 0x505FE580BFB4D0E0ULL, 0x781C17046810620BULL, 0x3E6DC8E9F8A786FBULL, 
            0x776E4F8F6131E9C0ULL, 0xFBF3360954E0352FULL, 0x29434008F02C3DAAULL, 0x1094693FE96BC64FULL, 
            0x2A5D944567184E5EULL, 0x25147B7FED51E5FCULL, 0x8247F4349216458CULL, 0x0C9B7D924123E68DULL, 
            0x9E7E9973DC540417ULL, 0xCAFBE0F68A776B4AULL, 0x67CA0F6FA8AA2F7DULL, 0x80464C954BE0873FULL, 
            0x9DB7AE4B8BF47D7DULL, 0x413D502F9F8D2F97ULL, 0x9F1831415434A366ULL, 0x9032D22B0E6A1028ULL, 
            0x97AA363E0BA9C502ULL, 0x6B2E302193D90F26ULL, 0x64538D0DF8385384ULL, 0x2591DF3510640B0FULL, 
            0xB6412FC5B4490A5AULL, 0x684550490AAF0441ULL, 0x75CD6C4C73E1DF5AULL, 0xD21D70F2989EB740ULL
        },
        {
            0x2EA33EE08002A7E9ULL, 0xE0F5A29CF66AA9FDULL, 0xFDC2C5CD234E5F22ULL, 0x585DD3D52D80743BULL, 
            0x8558B24435C0DC9FULL, 0x102C04D11C02ADA8ULL, 0x7898B0E43E3E3A66ULL, 0xD748DB1842ED0D57ULL, 
            0x8058E2F9A854E14AULL, 0xEE55715614E0B051ULL, 0x678FD76FAB215BA7ULL, 0x5A660C3A092FF953ULL, 
            0x888D4E009989B172ULL, 0xB40E3D421A9D2973ULL, 0x9A4C666F0244E5AAULL, 0x3F7A2DBC793A7CABULL, 
            0x075C98435D5E0C1CULL, 0xD01D5F101B1092ECULL, 0xD2F0049289796142ULL, 0xA43484FECC4AD1BCULL, 
            0x5B573EBB5B9157B6ULL, 0x75555A850C028102ULL, 0x29C29ED3000DE424ULL, 0x65B838934D6EFB63ULL, 
            0x5F25EF12A8DCF859ULL, 0x71D9A9574023B52EULL, 0x6993A8B4567D3B56ULL, 0x54F5F267B5B7F3CFULL, 
            0xE329E22C883988D8ULL, 0x00F5166A8B6CE051ULL, 0x86F2B8CBB2D36C11ULL, 0x3704405811FF92A6ULL
        },
        {
            0x4739A52DDF123ABFULL, 0xBA1860FC9D7038CBULL, 0x4661A0EEA19E92E2ULL, 0xF7A7FD7FAA023130ULL, 
            0x25DD37A21CD25E99ULL, 0x8138ADD2A026682DULL, 0x5439E0958DAD67C1ULL, 0xF1D08077DFE7A2A1ULL, 
            0x128BC5CCF366D0B7ULL, 0x92F60496D3B3591EULL, 0xA106418320AF0E11ULL, 0x36661A2E5E5BFD27ULL, 
            0x80E151CE746BF490ULL, 0xF7CD47AEAD42DFC8ULL, 0x7B84A7977B43FCF7ULL, 0x7F7779450D200E9BULL, 
            0xF5847F39A9F28809ULL, 0x3EC71602F8CD0E21ULL, 0xE7B3AE0B9F75C11BULL, 0x0939DF4CC3C71E06ULL, 
            0xA73E560326DC1905ULL, 0x08BEE8A371363E8CULL, 0x2834D33B8815FF3DULL, 0xC2A8809D73E17956ULL, 
            0x3571D2A8FB88F811ULL, 0x3D5F01A074D09CECULL, 0x18DBA9E9B5727467ULL, 0x9B9AFFB81322B2C4ULL, 
            0xFE1E3664A418C8B2ULL, 0x2A1730DABF3E1F08ULL, 0x1D1A9FD76CA5FFF0ULL, 0x5F0F1AA61EF4CFCDULL
        },
        {
            0xDE0798B14385F59DULL, 0xC17F2BCEE109B57DULL, 0x424D80AB6CAF76B4ULL, 0x947EB02A1EB40187ULL, 
            0xE7CD7476BEF08B4BULL, 0x2E1A18B1A186E8D0ULL, 0xDA352B778135171DULL, 0x32076DC4F5C7B088ULL, 
            0x00C095963C4FABDFULL, 0x88999A7F209BB473ULL, 0xB1CC6C2449EAD14FULL, 0x62331786E73911ACULL, 
            0x7354082D8F528D02ULL, 0xE44C6D3870225005ULL, 0xDB33A12D9B6F66C7ULL, 0x79410A2BD71EC98EULL, 
            0x4F2A35CD19DEE9EEULL, 0x712FCF184DF0198AULL, 0x548D8B0952B94AD1ULL, 0xC4AD906E20606752ULL, 
            0x7F645FD10AFCD4A7ULL, 0x0BDDB48272D1210AULL, 0xB74A0A5A72A77DADULL, 0x9275A57866E96BBEULL, 
            0xB5CFF134F16FE79FULL, 0x65917D222DBDB565ULL, 0x984F87689E68E8DEULL, 0xE7887728E987191CULL, 
            0x9E83D790FBAAE079ULL, 0xB30D520A47205E4BULL, 0x0EE76CE5A7EAD1CBULL, 0xBF7BE92DB56C15C2ULL
        },
        {
            0x6B187A1C95793F09ULL, 0x7E761E5B1560085CULL, 0x9C1C8A3099E72EBBULL, 0x0907CEAE2FAFD483ULL, 
            0x69EA24845F17B36FULL, 0x04006CEAF41C2620ULL, 0xD88E4AA4FCB0C6FDULL, 0xE912C963BC1EB089ULL, 
            0x4818AFBB66F9FF67ULL, 0x66221917214EEE5DULL, 0x1BD8C19A1C4CCE29ULL, 0x0DCF5C11B1C7D0F4ULL, 
            0x196FA486954934B7ULL, 0xD7770970C24A1240ULL, 0x1EEF36401AF96E3AULL, 0x08DD98359A8E43C7ULL, 
            0x4443620DDAC396DCULL, 0xC3996F525BF6F586ULL, 0x1F073EE649A18405ULL, 0x3292C1B97106E19DULL, 
            0xF96D04C9EC033819ULL, 0x09FB572EAFB4D2FFULL, 0x8F331802D9DDFBE4ULL, 0xA2F0BC76A242C37FULL, 
            0x1F4997F6218D5D89ULL, 0x4EA187B8D2DB9088ULL, 0x9703FE54267DCAF3ULL, 0x9882C7283BB2D735ULL, 
            0xD662251EDE34524BULL, 0xE2D771AB1CF64CD6ULL, 0xCCEB5C12681730E5ULL, 0x0959B0295989E237ULL
        }
    },
    {
        {
            0xFD1C8D243FC09455ULL, 0xEFDF22D4620B963AULL, 0xCB72241235D66EBAULL, 0xAEA921221A86F3D8ULL, 
            0xD1AD88C8A0A3FA86ULL, 0xE6CF6AE783738757ULL, 0xB1CC08B09BA7E920ULL, 0x2EEAFD4C588F195BULL, 
            0x9A7D0B343595626FULL, 0xB6AE7D27C53BCDD8ULL, 0x90129180C3E19C8AULL, 0xD37A299342F23FE6ULL, 
            0x89EFCE96578EFE6AULL, 0xF5A5371F6EC6CC74ULL, 0x1D96AE528747769EULL, 0x8CA2DC51781E50A6ULL, 
            0xA80988CED669E27DULL, 0xB54CE4FA4B28CC31ULL, 0xC245FFBD3798E589ULL, 0xD328DF3E944CB8A1ULL, 
            0xF6555998049C2E86ULL, 0xAED1C9AB840A5CD6ULL, 0xE528669D8CB68ED5ULL, 0xEE8B579C505FC43EULL, 
            0xE1695A6ECE639800ULL, 0xA102AEF27BEAAC4CULL, 0x4EBF53E71E8AA220ULL, 0x64E486CD68A6565DULL, 
            0x09B5D602E318320AULL, 0xA2E019ACFE7D519EULL, 0x862F925BED1FB67CULL, 0xD3A7A369ABCEE783ULL
        },
        {
            0x725F021A4BA196D1ULL, 0x1B7F7A6C0FEDFC77ULL, 0x48C16D2AFCE05C83ULL, 0xC57D71B585FCE2F1ULL, 
            0x92F3F1C632196B54ULL, 0x3BE8A17DCFFDCC53ULL, 0x7BBE60E6EF555DE3ULL, 0x0E6543F595F625B2ULL, 
            0xABA04862AE32EB4BULL, 0x679C9B2BABFBDEE4ULL, 0x044B164372579740ULL, 0x5CD9C22F4161D0E4ULL, 
            0xB01A08CA78868E78ULL, 0xF2174B936E3D160BULL, 0xAAB638DDB55EF43AULL, 0xF992F349E94D8DB0ULL, 
            0x4C63BBAD6B58BA16ULL, 0x378D8534FFAED553ULL, 0xBE3972B9E099DF3AULL, 0x8F6B45F201388BB3ULL, 
            0xE970602F14F0FF7BULL, 0x7C3A2B3F453DC4F6ULL, 0x95BA327E97EFDCDEULL, 0xE003EBB04E37A7C4ULL, 
            0xFAE3029E88AD77BAULL, 0x8B7C779C8D71BE15ULL, 0x3BB27D3209B9626AULL, 0xC6968AFAA9C26721ULL, 
            0xEC85A12B7EC43E7CULL, 0xFEEDF251F1EE1749ULL, 0x1396512656F046B2ULL, 0xC37B29606CBC07F7ULL
        },
        {
            0x8BDDB2CF29881E0EULL, 0xE215995A1E4C73D6ULL, 0x07698D4B10CFF3A0ULL, 0xFCA0909EE67B2856ULL, 
            0x5817F406573DC7E2ULL, 0x2499E4A833F12EA2ULL, 0x77FCD20B70BB470EULL, 0x17E233E7E27A1A9EULL, 
            0xEA7155E99A829D5EULL, 0x0A757B19AC6B1A43ULL, 0x96DC1CB113C231B3ULL, 0xC01ABDC10B80D3F1ULL, 
            0x63EE81A8061C7B0BULL, 0x57F27157FEA85BD5ULL, 0xEEFE1DE7BA2756B6ULL, 0xCCF5C83C4D839EC2ULL, 
            0x5BB5CF94851FDDCAULL, 0x72166FF4F5397220ULL, 0x039D4D9CFBE94D95ULL, 0x9CD8C717C07B9FD0ULL, 
            0xAAF70124F906788AULL, 0x71E6ABC1D7742195ULL, 0xBDBDD35A69E531DCULL, 0x6B8599389528F7DFULL, 
            0xAC6BF10245494345ULL, 0x05608EBFA4379305ULL, 0x7D6ABB869922ED69ULL, 0xE0D30B6FDB2DCBD5ULL, 
            0xA1325556BB2FF3D1ULL, 0x830AA76D86235FEDULL, 0x7F2B8D429FDEE0AEULL, 0xBC7BC3D262A3DC61ULL
        },
        {
            0xCF71C202379E835CULL, 0x01FBC38EE2EB7770ULL, 0x209AD293BBA7FF01ULL, 0xB9F4487B8F95D913ULL, 
            0xED3ADE3DDDC69745ULL, 0xAC07B8541C7C2F2FULL, 0x10F2962CFB343E29ULL, 0x11A080FB7809B48FULL, 
            0x6040CEEDBF590C78ULL, 0x94CDE51617126618ULL, 0x556EB285704B48C6ULL, 0xA4631FFF9A37C4A7ULL, 
            0x9B0A8093368B6408ULL, 0xC416BFC78ABEC527ULL, 0xD679FBC7736B4C56ULL, 0x4641D214F4E814DDULL, 
            0xC05A6CF3BBEEB3AAULL, 0x061111B34FFBC696ULL, 0xEB629737444AE305ULL, 0x7EA95285499EC635ULL, 
            0xA03947FE3A16C28FULL, 0x7C537219891C25B5ULL, 0x1C2C653B95414614ULL, 0x69C76B2CB4BF6E0CULL, 
            0xBBFEF281C5E2F03FULL, 0x00C1DA97F5916C1AULL, 0x6688F24FDF68011FULL, 0x8715BC5C5E0E2270ULL, 
            0x1F74BE22A2573144ULL, 0x10D10FCC107B1AC0ULL, 0xC8C60127D83A4E51ULL, 0x464F53B576B437BEULL
        },
        {
            0x07019ECBB4274C67ULL, 0x1F3F16449F836B9CULL, 0x2B0156FD79F13C25ULL, 0x058678512572B8C4ULL, 
            0x147BBB885C7B238DULL, 0xD15A594A72862356ULL, 0x8DC25EBAF36D08D5ULL, 0x6464F18F84F26CDDULL, 
            0xC0CED25E0979C467ULL, 0x6BD9D2F087BD62CCULL, 0x89C849032E56CBE7ULL, 0x846CAFE96C298C50ULL, 
            0x44ACF2E705FCF8ACULL, 0x4185A3D30E66B0F0ULL, 0xD50A538B62E06992ULL, 0xCF67580B21C24EB9ULL, 
            0x826BBDD45B68A96AULL, 0xE425FE91A7089C2FULL, 0x55C1B58FA63F3AF2ULL, 0xFC36E58F4830A354ULL, 
            0x6174826DC4F7E288ULL, 0xC75AC26B8F6FE9C7ULL, 0xAD1DF6A9B45198F5ULL, 0x67307E2A753AECA0ULL, 
            0x9284D1CF70BB5BE7ULL, 0x5EBE186886366C40ULL, 0x6450F174D369AC6EULL, 0x6B832A5B12EADE4BULL, 
            0xFBBA671AEBB39458ULL, 0x544EBD59DC03E1ECULL, 0x9C023E2A6D9D28BAULL, 0x8AE09B83BE3D1C81ULL
        },
        {
            0xDEF6310730342D2AULL, 0xFDE5E91C88224232ULL, 0x51E952341EE7A1CAULL, 0xC54F301A349DCB21ULL, 
            0x13DD11D31EDA5E55ULL, 0x1F6D54C1B214DD62ULL, 0x9F7F7F09B26C8FBEULL, 0x89731A6D20C9105EULL, 
            0x48D2547BA5C12FD6ULL, 0x68C87EAB620C92C8ULL, 0x1CCA39C555BE5C20ULL, 0x6FB2D0EF6C4A0829ULL, 
            0x7BF8AE73A7F47BE1ULL, 0x9DDE5E7706DCD585ULL, 0x8FF33F21EDBFBF83ULL, 0x29F050A9EA0B4890ULL, 
            0xD6C7471562441BF1ULL, 0x03B307EB3611E426ULL, 0xFEF7247884F91EBDULL, 0x21E27D0079CE48FEULL, 
            0x2200EA7420A53BB0ULL, 0x5615CB484D497753ULL, 0x38A5B86C588FD9FAULL, 0xDE3141D3775B8C4CULL, 
            0xBBD474B077823099ULL, 0xBF7419FCA845F812ULL, 0x590C030C6ECEC781ULL, 0xBAC10B7F1CFC2573ULL, 
            0xDA44E78BB616E697ULL, 0x4607706266916DCDULL, 0x28514A6107C034C6ULL, 0x2F2EB085E381353DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseHConstants = {
    0x807D98F7BA09CC0BULL,
    0x3B1666391A88D503ULL,
    0xBF0B0F4C07D62B57ULL,
    0x807D98F7BA09CC0BULL,
    0x3B1666391A88D503ULL,
    0xBF0B0F4C07D62B57ULL,
    0x49E456C0C46BE098ULL,
    0x4110319EFF530192ULL,
    0xF8,
    0x8D,
    0x5E,
    0xA6,
    0x44,
    0x7D,
    0x41,
    0xE5
};

