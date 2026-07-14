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
    std::uint64_t aPrevious = 0xBAA437BDCCEDC33DULL; std::uint64_t aIngress = 0xF958E5974A141314ULL; std::uint64_t aCarry = 0x8EF35C34A88EB34EULL;

    std::uint64_t aWandererA = 0xD02196EEF12CAF40ULL; std::uint64_t aWandererB = 0x84EDCA5D81E26930ULL; std::uint64_t aWandererC = 0xE6A13035982A670CULL; std::uint64_t aWandererD = 0x8C3E16AF29F131D8ULL;
    std::uint64_t aWandererE = 0xF6B5BBFC78ACB790ULL; std::uint64_t aWandererF = 0xE4BCBC29DEEDC0DEULL; std::uint64_t aWandererG = 0xB149972DAC0BFCD4ULL; std::uint64_t aWandererH = 0xADA80D06EAFC7215ULL;
    std::uint64_t aWandererI = 0xB60D1C69C18D906DULL; std::uint64_t aWandererJ = 0xDE9F156A41FD38F5ULL; std::uint64_t aWandererK = 0x9331442C99C90F92ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14001669908707278857U;
        aCarry = 11154720874590615555U;
        aWandererA = 17418775703533703615U;
        aWandererB = 12443069060066596818U;
        aWandererC = 12534484815859418431U;
        aWandererD = 11229839709772080282U;
        aWandererE = 9263174987321024521U;
        aWandererF = 13175542811580940593U;
        aWandererG = 16081145478214465521U;
        aWandererH = 11719815821887714911U;
        aWandererI = 15927162820808334941U;
        aWandererJ = 12317176240071752558U;
        aWandererK = 17826135524919258877U;
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

    //
    // ---------------------------------------------------
    // KDF_A_B kdf_a_loop_b:
    // ---------------------------------------------------
    // read from: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Athebyne_Arx::KDF_A_B(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_A_E(pWorkSpace,
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
    std::uint64_t aPrevious = 0xF396EC7C6FB6F46AULL; std::uint64_t aIngress = 0xD42490FBB1FA24CFULL; std::uint64_t aCarry = 0xDD7B6C61CC7A6D0BULL;

    std::uint64_t aWandererA = 0xE64CFB2B9EB61F2EULL; std::uint64_t aWandererB = 0x9FD2ABC4ECBFC0F7ULL; std::uint64_t aWandererC = 0xD346451E52B1CA14ULL; std::uint64_t aWandererD = 0x9DA7B4F18A8FBDDBULL;
    std::uint64_t aWandererE = 0xDC76A8494811E472ULL; std::uint64_t aWandererF = 0xB72AE17DAB0846C5ULL; std::uint64_t aWandererG = 0xFE2CEEF9CF15CEBBULL; std::uint64_t aWandererH = 0xBEB77F346A476330ULL;
    std::uint64_t aWandererI = 0x8896BEAE6DC72370ULL; std::uint64_t aWandererJ = 0x9A94DFB8E058DE15ULL; std::uint64_t aWandererK = 0xE0775A3B81D515D5ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15349145022976479229U;
        aCarry = 9739513632091611411U;
        aWandererA = 18349114048566063828U;
        aWandererB = 9369449085867340483U;
        aWandererC = 18261427299113066874U;
        aWandererD = 12357595187918988194U;
        aWandererE = 11318316628297433947U;
        aWandererF = 11135188478128739841U;
        aWandererG = 10791097270709335434U;
        aWandererH = 11451859853217806646U;
        aWandererI = 10740266188306560620U;
        aWandererJ = 10429224158689040216U;
        aWandererK = 17464035434271242313U;
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
    std::uint64_t aPrevious = 0xDC06A9110418EC01ULL;
    std::uint64_t aIngress = 0xD236611386798304ULL;
    std::uint64_t aCarry = 0xEBC882ACE853F527ULL;

    std::uint64_t aWandererA = 0x9B13544D5B88C512ULL;
    std::uint64_t aWandererB = 0xCDBA0D2F1806E4E7ULL;
    std::uint64_t aWandererC = 0xC098941F992F9429ULL;
    std::uint64_t aWandererD = 0xE974439B41623596ULL;
    std::uint64_t aWandererE = 0xE6859FF2A99B5EBFULL;
    std::uint64_t aWandererF = 0xE2F506690B2268AEULL;
    std::uint64_t aWandererG = 0xB3985CA15DAEEA80ULL;
    std::uint64_t aWandererH = 0x8229228F54CE93E7ULL;
    std::uint64_t aWandererI = 0xC3D3EFBA144A5CE1ULL;
    std::uint64_t aWandererJ = 0x97471503E77F8585ULL;
    std::uint64_t aWandererK = 0xEBFDBFEBB4C057B4ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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

    //
    // ---------------------------------------------------
    // GSeedRunSeed_B seed_loop_a:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, earth_a, earth_b
    // ---------------------------------------------------
    //
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
    std::uint64_t aPrevious = 0xC115BE87B173136FULL; std::uint64_t aIngress = 0xD3C1A3892A6BD104ULL; std::uint64_t aCarry = 0xCEF23CC9267330FCULL;

    std::uint64_t aWandererA = 0xD6D80AB79FD88376ULL; std::uint64_t aWandererB = 0xC55B2CBEB112243FULL; std::uint64_t aWandererC = 0x8D1F7EEDF8DFCA9AULL; std::uint64_t aWandererD = 0xD5768CC75DD60B94ULL;
    std::uint64_t aWandererE = 0x9A914AD5110E0F26ULL; std::uint64_t aWandererF = 0xEEF053077DE4E470ULL; std::uint64_t aWandererG = 0xDCCA1C4AB92A2673ULL; std::uint64_t aWandererH = 0xBCFD91D7B54BB73EULL;
    std::uint64_t aWandererI = 0xAD5C28DF917E0272ULL; std::uint64_t aWandererJ = 0xF03059A908F75805ULL; std::uint64_t aWandererK = 0xB3DC9A537E0D2A23ULL;

    // [seed]
        aPrevious = 15686377111324059490U;
        aCarry = 13642869681513797958U;
        aWandererA = 10541672913747741819U;
        aWandererB = 13865257566677466721U;
        aWandererC = 15279613934894492500U;
        aWandererD = 16984309148257914086U;
        aWandererE = 15901968371163313316U;
        aWandererF = 16177773608933390119U;
        aWandererG = 13037233279230195856U;
        aWandererH = 11631231971281868873U;
        aWandererI = 10781621810080889223U;
        aWandererJ = 15284251462752345944U;
        aWandererK = 17567091534405716216U;
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
            0x632C19857DE248DAULL, 0xD7CDBFF99073E049ULL, 0xE07F2C389EE6AE61ULL, 0x1F6739F2EB7A3472ULL, 
            0x541A7E706FE5D12AULL, 0xFBEE9771A8B34D57ULL, 0x6F9BFF7AA42ECEC4ULL, 0xBCAF4BA67CDF7DE9ULL, 
            0x51D8D5DC4A30F56FULL, 0xF3C9E2485B694D35ULL, 0x66DD291875F989B4ULL, 0xE9289EAF6DC4A01CULL, 
            0x209D8C08638D1677ULL, 0xD99D4B91468386A0ULL, 0x1067513C6E1DB436ULL, 0x791B45EE826E6BBBULL, 
            0xFDFC96E408D13574ULL, 0xC23628468FBC1C55ULL, 0xF0ED3629DD714527ULL, 0xFDE512BE2A8EBA29ULL, 
            0xFBF377E6DFBCDC96ULL, 0x98696D312A4E6484ULL, 0x3A5391D6F913919BULL, 0xA7DAAAF92AC8735FULL, 
            0x7CAE10568EEA9114ULL, 0x1491AB9CA9A88601ULL, 0x942AB5AE243CC000ULL, 0xB3F3B9D62F04AB00ULL, 
            0x8486AB726E8A7A21ULL, 0x64AC61AF95293331ULL, 0x718DC1262B4726CDULL, 0xBDF10BD469956E4BULL
        },
        {
            0x23829FB6B314D6B0ULL, 0xA44714A2E45347B2ULL, 0xC96C7082CCCFFC0EULL, 0x92468C8793100083ULL, 
            0x386D72AA261BE6D7ULL, 0x47B046E755EC0444ULL, 0x0188FBDFE345E2A4ULL, 0xE1BBC0D6D481DF02ULL, 
            0x93D7F263EB5B9EB4ULL, 0x061365CAEE98CF34ULL, 0x8B005C1B2107773BULL, 0xDAB7C14E6ECA3887ULL, 
            0xCB83858EBAB6BA96ULL, 0x5F9AE0F288782692ULL, 0x466CE85D1CFB30C6ULL, 0x1C02238B7A2B0DD7ULL, 
            0xBB3AAADA64AC5D06ULL, 0xB87DEBC454EC2236ULL, 0xF31F8511A0477EC0ULL, 0x4182E7679C1A107DULL, 
            0x24A9FD832481BBE8ULL, 0xB13BAA40D5DB1073ULL, 0x311B4CB3347B11ACULL, 0x34F62B05159F6676ULL, 
            0xF2574DF84A3332A0ULL, 0x9609EFC04A9AA1D8ULL, 0xDB5089664BDB6676ULL, 0x9EAA5C2B86818184ULL, 
            0xFA9D3136638D48CFULL, 0x8E58306CC7CB9F01ULL, 0xB50D677DA12B956AULL, 0xE6E58BD2C67B076CULL
        },
        {
            0x6FA51BCCCD49D41AULL, 0x42416F94DF1BBFADULL, 0x3E02C766790CE0B9ULL, 0x0C8F013607C78D2DULL, 
            0xF4A2E6B5DBE7D600ULL, 0x079F12892BCF34EAULL, 0x1FEDA5731F5AA3C6ULL, 0x31AE68D6380D2B7CULL, 
            0xDEC8F3F8766FDFAEULL, 0x8BA2C8F3F29CA7C8ULL, 0x855DAEB6691F16EFULL, 0xB9606CBC088F3CA1ULL, 
            0x2651ACFDBBC7FFB4ULL, 0x5B271D221998E35BULL, 0x49C452E15FA66416ULL, 0x06E109F947DA4A2CULL, 
            0x9E486A5C8EE352DEULL, 0x75A96264FA31C270ULL, 0x4C1B8586C1235D28ULL, 0x6A9F2C2B6DEB50EDULL, 
            0x21B5FEC0CF069221ULL, 0x894ABDFAD1AC3C79ULL, 0xA60F193C9DBF39E9ULL, 0x31339515442800BAULL, 
            0x6A380483CA0A540CULL, 0xBCB25EEF25F31A65ULL, 0x8D6F6EC48594581FULL, 0x7B25ED805192A78EULL, 
            0x1A5A0909E6778742ULL, 0xA1D7556DBB967F70ULL, 0xE89862E09267F868ULL, 0xEF2A2282ACC56199ULL
        },
        {
            0x5187D005D6D0CD08ULL, 0x66800F29BDFD65CEULL, 0x81A26600D926EC29ULL, 0x275488BB85CDB15CULL, 
            0xFED028FC73A65C5AULL, 0xA5FEC69A456544F2ULL, 0x9DFCFE15D0BA814DULL, 0xE45B69C60C7397DAULL, 
            0x7C2B351E441BDAA6ULL, 0xE35D75E27924B456ULL, 0x1DFE680BEC2EF7F3ULL, 0xCB2E3E06BFD1A97AULL, 
            0x21CF129A7230687FULL, 0x8E6578597CA3786FULL, 0x66AB552875A6E267ULL, 0x915396A1EC8B6902ULL, 
            0x6E1E05D1F8D5B53DULL, 0x131135403024D4A7ULL, 0xB145006A7A69CB51ULL, 0xCD565C1FAB7937B9ULL, 
            0xC933E2D8DD9D1B6BULL, 0x0E953A9079AFD71AULL, 0x301283067B2F345DULL, 0x2C6249C8EC587BE3ULL, 
            0xDC9AC8484DBBFCC9ULL, 0x867DDEA1E3EFE467ULL, 0x660F704A06F8022AULL, 0x8F374572932B10C2ULL, 
            0xDA640B61BDB4082AULL, 0x6A8B7D89A9D3D0E8ULL, 0xAD1DD00961290A40ULL, 0x5EC2A71C5F3E952DULL
        },
        {
            0xA40DEC456B6FA219ULL, 0xCDEA56299323B5DAULL, 0x665959D90EE44CF8ULL, 0x60E36B91297B5A48ULL, 
            0x0E59650815B1BD11ULL, 0x3FCB1F2CA03F76EBULL, 0x38EEDBDDECCAF67DULL, 0x74C73D6BF9BA7753ULL, 
            0xEDC5F9321D564037ULL, 0x2A8ED64D133D2606ULL, 0x7881329C823E49A5ULL, 0xF3847CF7AE1CAEE4ULL, 
            0xE16B4B3CB55C65DAULL, 0x27B315DC60D8E407ULL, 0x3F4607E7EE050CB6ULL, 0x6473F6394E17A3CEULL, 
            0x9027B498CB13AD5FULL, 0x678F4CE55996A318ULL, 0xEEC74C8AEFA1B34EULL, 0x226CA1BD705F51C8ULL, 
            0xA97DF9FB6E1FF629ULL, 0x9902E18955939C62ULL, 0x48721F7522BD011EULL, 0x56EFE06803628A5DULL, 
            0x869C71E265E97112ULL, 0x7464CF35D1BE9A00ULL, 0xAD1A590158BCDD77ULL, 0x5FB1B646133F9A1DULL, 
            0x96ACE848B4DF9CDEULL, 0x4A881E6E22C2FF8EULL, 0x258B4B3878F83D1EULL, 0xEC9C4FB85941FE23ULL
        },
        {
            0xF828943D5231EC57ULL, 0xBB264AE2F67B906BULL, 0x00BBE84C68B2E6E8ULL, 0x7EF47021C17A42F8ULL, 
            0x18BF3E6F99FE111BULL, 0x2B48CBF2F21C33A3ULL, 0xF074FAC100B99145ULL, 0x625D39833525722AULL, 
            0x653572EA8D8D1E13ULL, 0x8767C840E37F99ECULL, 0xACDC2E34E24FFDE2ULL, 0xBC0E675227E16E8BULL, 
            0xF9E4715F991239DCULL, 0x32FE501057730F14ULL, 0x1DE36ACA28EFA19AULL, 0x1EA21A03BA8E2767ULL, 
            0x490282455BBC0367ULL, 0x2C0773F88B2F5AA0ULL, 0x10794B3580A2179FULL, 0x8FA3671E3118223AULL, 
            0x75441D4853E3C9BCULL, 0xEA84DD0620A2CA15ULL, 0x5B0ACF04C31C5153ULL, 0xDFF853CB41B0A638ULL, 
            0xBF16C841E3F6CEA1ULL, 0x3FB2E11BE0DFE392ULL, 0x2448E16D17A3B53AULL, 0x5315F346E933BBB5ULL, 
            0xA7CF78B42799BE52ULL, 0x8E2B53AEA4AA0E42ULL, 0x7EDD608D9DBE7A0EULL, 0x507F4A6D9A1ED2A1ULL
        }
    },
    {
        {
            0x87A8172C50FDC960ULL, 0x57D252A22F0EC428ULL, 0x766F8D56BFFBF22FULL, 0x958B89F21B053208ULL, 
            0xBDC248AA8703EDD1ULL, 0x2C01655B9844EFF2ULL, 0xD6003185853F6161ULL, 0xC7721BD2FCEACEA5ULL, 
            0x5F41EBBA075B8EDEULL, 0xB4875B3E652FCD4CULL, 0x3DB5D7C77A7EBDEEULL, 0xC9A3A8221B4BB66BULL, 
            0x7C9E84ADD19035A1ULL, 0x417BA22639AB1F9DULL, 0x2FF25B20CFEEBD47ULL, 0x8194B1D554DFCB60ULL, 
            0x6FCD71BF5E868BE8ULL, 0x0C0D93E49E04AF1AULL, 0xFFC60FCBE8E3B076ULL, 0x0A6E99F1E7CA887BULL, 
            0x7BD6B7175E14BE63ULL, 0xFBD4D42D8331E17FULL, 0xAD972BACD7168977ULL, 0x8C6DDD8C3D0AE519ULL, 
            0x54C0D90E9B3FA847ULL, 0xA533157E001DA412ULL, 0xD2D18E3C7C20437AULL, 0x05CA95E200A41749ULL, 
            0xE43BC1F8461ADEC3ULL, 0xFF5A0605F6F680BDULL, 0x194B78D49D2A1D78ULL, 0x1367E34215D27C7BULL
        },
        {
            0xED2FABCC670C8820ULL, 0x11FA7FA08C7B940BULL, 0x02184AB6A00BBA80ULL, 0x3F44C20F841167CEULL, 
            0xEF825FCABD653047ULL, 0xE2D5D378F8963DBFULL, 0xBBFDD7215410EC8EULL, 0x5F200201671DB76BULL, 
            0xB1014C33FFA01E0AULL, 0x1CC086326BAC3BF5ULL, 0x6E97FC12A0021E03ULL, 0xB741B1F07833C615ULL, 
            0x4BA2C44F90E3F02FULL, 0xE81EB18738FDC2E6ULL, 0x862CB877E6310D33ULL, 0x7D56F6E5152B8C49ULL, 
            0x7A14EF9BFE050EF2ULL, 0xC5405B7DE146DB0CULL, 0x833185E7D50C6DAEULL, 0x2A63B5F38901EB48ULL, 
            0x7AF276A74EB63BD4ULL, 0x7C1E39E8F336AADBULL, 0xBA15C5FED028CA2FULL, 0xCEFFD05D1007D24BULL, 
            0x7B659AA4B53E1E26ULL, 0xEBF91520354B2E45ULL, 0x4A17A664EAEC42CDULL, 0x50994B2332779EBFULL, 
            0x3D8A12CA971F854EULL, 0xBC8BDBB1820518DDULL, 0x20D160D93C423DA1ULL, 0x82B2BA9A4D09358CULL
        },
        {
            0xF9C42AA4B4926C44ULL, 0xD77F3E2B801C06A6ULL, 0x512AF3C3C4B85F50ULL, 0xA4442B90B197A3F7ULL, 
            0xE85092C0EDEB5648ULL, 0xDC239A5D95D54239ULL, 0x94B66EE3F85B4048ULL, 0x9C39679CEC9F81C9ULL, 
            0x6ACA4366621861F1ULL, 0xEEFB847516DCBCCCULL, 0x6763A610D86B9125ULL, 0x0ECDB3FC9FF21E94ULL, 
            0x1910408F6DD5AE89ULL, 0x1FDAF918A8CF3C80ULL, 0xD1E8CAE01A2156EBULL, 0xA638A6FF5605E104ULL, 
            0x8C126FAE48940873ULL, 0x16E3765668F63181ULL, 0x02EDE96DC462145EULL, 0x75793F86BF64DBB6ULL, 
            0xA97B6D2E9926D359ULL, 0x55E79C73B3234350ULL, 0x68E4F2271BDEDFD2ULL, 0x7F0AB110C6B4A644ULL, 
            0x578D12289D3E3E76ULL, 0x7E10B2DCFE144D65ULL, 0xC822F159B877EF10ULL, 0xC0E7DD1DF28B1689ULL, 
            0xA9686420A4008CD2ULL, 0x717CE4DF542A2624ULL, 0xA1A198877DE3CD69ULL, 0x78ECE20EDDB7173DULL
        },
        {
            0x1794F43D8381B5D5ULL, 0x59DFAB129B554078ULL, 0xE097D2DB81CD469AULL, 0x8617E5E65BE2D104ULL, 
            0x29542130C7DB71DCULL, 0xAC2BF7897FCE629DULL, 0x750B4DF509C1EE7AULL, 0x2E4E0B23DD491A8CULL, 
            0x7A474E46660ACE66ULL, 0xF1978ADCB32F5748ULL, 0xD6F45E47E9AD894BULL, 0x3F66A5BE98354D78ULL, 
            0x1765486ACCD7E4B6ULL, 0x3AA90DE222A6F081ULL, 0xC799D67F48A67A31ULL, 0x37AB1ED4C3DC096FULL, 
            0x7837A5FB6F99A651ULL, 0x978BA22008DDCAE6ULL, 0x257FED0428FCE49EULL, 0xD52B7A190E41A671ULL, 
            0xD5011F281BD93C1FULL, 0x9851D9B3644E2A79ULL, 0x727B325F19668EB4ULL, 0x128DBFDA470AFE66ULL, 
            0x5F567E98B5D88D56ULL, 0x503F68DD5E0FC34DULL, 0xF67416896874EE4EULL, 0x62AB5642A4AC36C2ULL, 
            0x385816080DB0683DULL, 0x704DE05A2A7CDE35ULL, 0xFA160D86A0438D1FULL, 0x3BF315A5CB757527ULL
        },
        {
            0x49EB27CD084E4596ULL, 0x0F162F25F78866E3ULL, 0xD661FD8FF142AE30ULL, 0xD365D002F1FF799DULL, 
            0x82293757EBA4A63AULL, 0x1529A9E14F6E108FULL, 0x772023008A2B0120ULL, 0xFA4E2A36E156AA2FULL, 
            0xD4BC8106046FA3FFULL, 0x5773F895897F1D12ULL, 0x5114149612049D8FULL, 0xB8AE83A160A772DCULL, 
            0x19955079D8619D58ULL, 0x1D876AD41290E8C5ULL, 0xD5F66EB6F217772CULL, 0x57155B098D5BADC5ULL, 
            0x844A450DEA111EE6ULL, 0x79EE414043A24248ULL, 0x45A3FB62598C24FFULL, 0xF2720EAC7D0A73B9ULL, 
            0x2540CC972610CEDDULL, 0x5A7B8689C2B577EBULL, 0x11A75B87AA9BC0BEULL, 0x3FA2D419BBA6910DULL, 
            0x88460C1CFD30C656ULL, 0xB3E054D8C6C9430DULL, 0xAF160E9E5A31B812ULL, 0x198E9DE9F28724D4ULL, 
            0x842084F38664F75FULL, 0xA205F318394BC61FULL, 0xD4378FA341B86FF4ULL, 0x29A58E651E8176D6ULL
        },
        {
            0x9942852EFB9E9A00ULL, 0x4C00F8D0941F7DD6ULL, 0xA66C9A1188554D4EULL, 0xC4EAE8FC8C59984DULL, 
            0x2F3202F627A51E9DULL, 0x536502418EA956E8ULL, 0xA8D81C9EF6A75FDDULL, 0x869914A5BF96F6B1ULL, 
            0x3FB135C075535F83ULL, 0x0F63FF8C0A8F0BD5ULL, 0x2F6AC5BE1667D12CULL, 0x4B7C84C944B498F9ULL, 
            0xCF86C42390706E20ULL, 0x5BAEB4EA06528E75ULL, 0xC7D87932E5980D12ULL, 0xBD29B22A85D51958ULL, 
            0xD24025F495127A38ULL, 0xD0087616142AC624ULL, 0xEC1B5ED42653324FULL, 0x5D2EA6A6E0532E90ULL, 
            0xC009C299B25D03C0ULL, 0x28734842D94292B8ULL, 0x4DF9B223523C7F70ULL, 0xB8D9AD6BEFDE0B5EULL, 
            0x8AB4FB6CE68F6228ULL, 0x3631AA8A3562D31AULL, 0x8C890EDFC66AE046ULL, 0x9C849A98C30CB8E2ULL, 
            0x3AEA29AA2DE3434DULL, 0xE0C7E0F2DB9FF1EEULL, 0xA60C05F767A7B1F5ULL, 0xBD663B048923DB2EULL
        }
    },
    {
        {
            0xED37FBA519BE463CULL, 0x7314867760E9A16EULL, 0x2DCA652993A5DD3AULL, 0x1B89AC498772C548ULL, 
            0xF2290B4D4A2A76E2ULL, 0xA3E0423EBEE3467BULL, 0x5C1FBBB8ECF710C8ULL, 0xF93E5AE559A945EFULL, 
            0xD8F1DB70B01FF328ULL, 0x0D80C7C7EE1AE9E5ULL, 0x4D8CE78E145E5BCBULL, 0xE685E5824659345FULL, 
            0x84828EF3DF19D507ULL, 0x49F0990B0EEC357BULL, 0xB9BAC6D881DB05DAULL, 0x812A04E3E399CE1AULL, 
            0x0C6A2869D57CB31BULL, 0xFE8FB3A9EA5FCDBBULL, 0xDE6F725A882B0334ULL, 0xCBA4EA2C7DB93E46ULL, 
            0x5B3FBBB9F11519FAULL, 0x65B4D4DD8743D304ULL, 0xED1067399792966EULL, 0xF43F82DCE8E8C521ULL, 
            0x1F16D3B892AA373BULL, 0xE398AAD1A76EB7BAULL, 0x27BCEAEF6AED34EFULL, 0xAB3B22BBEA321379ULL, 
            0x7AB79CB87F3CAE40ULL, 0x5F891841ED9763C1ULL, 0x8362AF7395E4DFF5ULL, 0xDB2BA788EA5561F1ULL
        },
        {
            0x3EA3F3FBD10E0BF8ULL, 0x2A36D931CDD7EEAEULL, 0xA9389141D159867BULL, 0xFB06B56CCBF9B70FULL, 
            0xECBBA1CBD3F44321ULL, 0xD019C2BF289E5386ULL, 0xE237B9F8C94B55A9ULL, 0xB65650D462D477ABULL, 
            0x4AD76944D4029B99ULL, 0x228178DF19B7B218ULL, 0x71A5FEB3B38EFA5CULL, 0xB4154F3F179201B1ULL, 
            0x08CD4A671D0DEDD3ULL, 0x5C53B80AC1AD6F3AULL, 0x32C30864ECC8357CULL, 0x1A153402B5A71D4AULL, 
            0xB14682B88454B26DULL, 0x92F91E5ACBB4031DULL, 0xF4BAD7106A257309ULL, 0xA3AB83DF541D031AULL, 
            0xAD4B840D4ED0A154ULL, 0x44EBBA61A73E4774ULL, 0x9C62BEE835613D67ULL, 0x409A6CDDB9C4B7D7ULL, 
            0xFD6C1BBF11F0407CULL, 0xA030011BEEACF646ULL, 0xB7D857FF9F795F54ULL, 0xC55FF884DA58EC62ULL, 
            0xA7C1A7CF43A93772ULL, 0x42A01404E25027CAULL, 0x57BFDF7E5EDCFB42ULL, 0xE253FAC4F5D2CF79ULL
        },
        {
            0x9E0D4D528626996EULL, 0xB2B58050E22700CFULL, 0x0B80444AD715C508ULL, 0xA64933B4E050A1C5ULL, 
            0xFBA25A68B2724CDBULL, 0x9A638BE345A84167ULL, 0xD2666677DE152A7BULL, 0xAE80C601D5DB213FULL, 
            0x66C01C885633E2EAULL, 0xC51C8A3C825C3A7CULL, 0x289FFF250F9CC51CULL, 0x47C75642B9390558ULL, 
            0xFCEFCEC9EFF5CFE0ULL, 0xE3ED2771FD49AD3EULL, 0x4FD056207B95373EULL, 0xE401D84956804D70ULL, 
            0x53B36B3FFFE81D8AULL, 0xE65A8DCCF16C842EULL, 0xD417DDF337A31CCAULL, 0xB8411BF4EFD7921FULL, 
            0x52CA63EC2BC3CF87ULL, 0xFBD9EB8FD0F72BA0ULL, 0x79776B11E9053356ULL, 0xF14E98D62C6398F4ULL, 
            0x66B78FB432433F67ULL, 0x12864A5F6BB96A03ULL, 0xACFF595E47B3371DULL, 0x03F50098C58E9096ULL, 
            0x1C003D6D63F3940BULL, 0xFA3688AEE0C0F88EULL, 0xC959C5E0C5687E97ULL, 0xA1F14C8B1D14389CULL
        },
        {
            0x9FF607AB008894A5ULL, 0x57B5605BE05FE001ULL, 0xAB6AF445F4E6833DULL, 0x6501433E1F9DF757ULL, 
            0x6754CD9B2265B554ULL, 0x68C48DED36B24C0CULL, 0xFD01DDED99B1E0E6ULL, 0xFA906278A978EC4EULL, 
            0x2B0B449FC431B3E9ULL, 0x7BBBBD821B490171ULL, 0xFA884F08C37BBFCDULL, 0x015E97D83361B396ULL, 
            0x4FB05FA9DB02437BULL, 0x146F433C2A3E1FA6ULL, 0xE7C2FF2927860554ULL, 0xDC2A094D317BCA29ULL, 
            0x78B26C96D4B84F0CULL, 0x1AD7C31F49A8A87DULL, 0xA578203D91543662ULL, 0xDEE98B409A9E9D79ULL, 
            0x502969EB2AFADB29ULL, 0xC0472AB885E23366ULL, 0xC0BF796B21ADAD83ULL, 0x3D27772E6AD979C4ULL, 
            0x540E55A6BAB82DA0ULL, 0xA51313616A20A8D7ULL, 0x9D3B4DC0BDD5FEAFULL, 0xE3D5995DF9723533ULL, 
            0x52BE1BF770B754B4ULL, 0x121CD1E28EDA3E2AULL, 0xB24E8C5BD8425D31ULL, 0x5975CC65ED932C03ULL
        },
        {
            0xBD24E9EE674199A0ULL, 0x6EBA0A7B7B3F6A0FULL, 0xD8684F7641972658ULL, 0xBF0C08D4264F0624ULL, 
            0x4364D5948602F951ULL, 0x436D2691559E5CA8ULL, 0xCD9EF98A2906905CULL, 0x9881F909073B15F0ULL, 
            0xD44F5A984327EAB8ULL, 0x0B4F9CC870F222E6ULL, 0xDE4BF1316F97159FULL, 0x33F92D689FBB7913ULL, 
            0x83603771149BE2C0ULL, 0xC4F4C4DBC31392BAULL, 0x0B8F48D239EEC9ACULL, 0xC4B28900C60AD6E1ULL, 
            0xE1AD58E9A35DAA5EULL, 0x73C482ED63410B76ULL, 0xD0998193F438FFC8ULL, 0x77DB8376FBACA16EULL, 
            0x97C62E03A097A4ABULL, 0x0CE8C4F3B052C3DBULL, 0x8D357DCD46DE705CULL, 0xD67E953527D6B803ULL, 
            0x2A458E6B39C59762ULL, 0x83D01E3E6858E386ULL, 0x0B6AFAB81DB2FC4FULL, 0x459DAA3FE6DF2242ULL, 
            0x3249AF63BE49B87CULL, 0xA9F43B038040BAD6ULL, 0xB4C7E4900907417BULL, 0xE060750F02190F66ULL
        },
        {
            0x37CCF62D99AFCBCCULL, 0xA9D69153D33728B5ULL, 0x2EADC315AB319FE5ULL, 0x3AC90541D5CA5E9BULL, 
            0x5546E22BA189BD8DULL, 0x63DBD6370A92E4F1ULL, 0x45BCD49FBC974779ULL, 0x4C7943D5A8627022ULL, 
            0x3FF8E23F81778E54ULL, 0x0A6996850234D69CULL, 0x04A3FFFDEBC5A893ULL, 0xBADFAF18822A294AULL, 
            0x2842B3E832B04412ULL, 0x98475F99984429FAULL, 0xDF01CC2512F841E2ULL, 0xC05B98B5F0A47AA0ULL, 
            0x514F47FFD41C3AB8ULL, 0x20C3B4A354E5C408ULL, 0x501D977666A21EE5ULL, 0x35162BD9197CB858ULL, 
            0x464EE198D60C8925ULL, 0x24048A51550996D3ULL, 0xAC7A487F995AF304ULL, 0x73343A65CD1F2C13ULL, 
            0x6FB0B7FD9B376408ULL, 0xE952ABC631F22271ULL, 0x2E8016747BF57244ULL, 0x1A15EE3532F02A72ULL, 
            0xF57E1D707833D358ULL, 0x7338253ECBA8565CULL, 0xD1B59230C976B7E6ULL, 0x0A4EC450D1758C43ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseAConstants = {
    0x06102A2F9A846D14ULL,
    0x3474F803FD9F7867ULL,
    0x9CA6EDEA2D82D8D8ULL,
    0x06102A2F9A846D14ULL,
    0x3474F803FD9F7867ULL,
    0x9CA6EDEA2D82D8D8ULL,
    0xD54F34CFE516EAE0ULL,
    0xB5D45D3D6142D135ULL,
    0xBB,
    0x55,
    0xD1,
    0x14,
    0xC1,
    0x56,
    0xEE,
    0xA9
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseBSalts = {
    {
        {
            0x0A9643441B0D085CULL, 0x17E7C5AFDEB6BB12ULL, 0x4B22321A7FB54466ULL, 0xBE3E73EF824FC309ULL, 
            0xD9C1F7E5BADFDFCEULL, 0x02A443C9CFAD98C7ULL, 0x5AAF8F8EA1D132DAULL, 0xD0972BC335C169CCULL, 
            0x826B52FCFFB21F29ULL, 0xBC250EF24B5BDF71ULL, 0x8D276565F568A103ULL, 0x5A2AD25323300680ULL, 
            0x69BCC73150D82A65ULL, 0xAED6FF281B8BDCB7ULL, 0xFFF8FE6A81460462ULL, 0xAC6A984FB7B25EDBULL, 
            0x25C7E0C322E19990ULL, 0x096F50BED922C4ABULL, 0x5998EDE4686ACFE4ULL, 0x9B00DBA13577F450ULL, 
            0x998A6EEE1F4E73D8ULL, 0xDB8AC128DA20BC6DULL, 0x93989D49EFE3BDE7ULL, 0xD17078A328BBA05DULL, 
            0x353D99BA42361BD5ULL, 0x14D4880233DC689CULL, 0xCEB7B8050E410EF4ULL, 0xC70CBACEBC564DF3ULL, 
            0xA86020B2E9127AAEULL, 0x6DBFB7209A4BA798ULL, 0x874590C96533AC0AULL, 0x36137197AC971A54ULL
        },
        {
            0x1823508A30CDF7A3ULL, 0x05F0E03B841AB463ULL, 0xECF022697ED64B37ULL, 0xD1E5F303F7CAFDA2ULL, 
            0x6411129972E95CF8ULL, 0xB1D3CF52731072FCULL, 0x4257B0713A83BA56ULL, 0x8AE73C081A0D71CDULL, 
            0x6666FD4F72F6266FULL, 0xC768E6039DBAEC88ULL, 0x8457686ACAE8D1D1ULL, 0xC12DC962BF3174EBULL, 
            0x2AF3F89A2C7F6A17ULL, 0x000E5528F98F760BULL, 0x8DBE89DC7E7F36F1ULL, 0x74104B947C705164ULL, 
            0x53E2DE9FAD192880ULL, 0x809101BC772A53DDULL, 0x8006DDE2C8852E13ULL, 0xC92E6F457C4B6655ULL, 
            0x44A8A60956AD1A7DULL, 0xA502E891DE0AC2DCULL, 0xD66B9908397D9368ULL, 0x20E3B4F36C6B9478ULL, 
            0x332FF311EB36690AULL, 0xDD222EA3C5EADDEAULL, 0x7D3D23DDC502619EULL, 0xFCFA6FF818339BFDULL, 
            0x87659C1E5477E227ULL, 0x3C85F9651706D33CULL, 0x6647AE0DA2562CCBULL, 0xF061122CD93E57F6ULL
        },
        {
            0x2AE25A77527D0660ULL, 0x5557066764043805ULL, 0xC2BC7AAD8409C16CULL, 0x67A0D09B17B341C8ULL, 
            0xEA2E048610A295E0ULL, 0x82936180BDCF4B38ULL, 0xD922D7F70CE8D50CULL, 0x015BE687FC05D78FULL, 
            0x9A8A9983F39BDBFFULL, 0xBE5F01C1D1D8EDE0ULL, 0xF04BA93D4CA3E5ABULL, 0xD6369C4E211D106BULL, 
            0x7D762F7B732BBB49ULL, 0xB294587CB0E5D81AULL, 0x6E4A541F3BC3A613ULL, 0xBE0555AA79FD5DE4ULL, 
            0xCD3D6BFEE9B78867ULL, 0x56561DC77555ADE7ULL, 0x1F5D94E330A0F7F4ULL, 0x871A3493371BBB17ULL, 
            0xAF98F8E88D90AE38ULL, 0xF009E4E5F1F33676ULL, 0x89595D4D03CDE3D3ULL, 0x9291A4CFEACE9286ULL, 
            0xCF16C86ED87555B2ULL, 0xF3F5FA6B9506CF6BULL, 0xB6B61949E785FCEBULL, 0x9A83D8D00DA3BCE0ULL, 
            0x7F2035F981BFFAF2ULL, 0x1593CEAEF9959A1AULL, 0x4A80AD90BDF747CAULL, 0x3628FA6CD629C3CAULL
        },
        {
            0xCBCB64A4B8DB15D4ULL, 0xF95777D3320B3215ULL, 0xD98CBCE9BB25FDDFULL, 0xA8ABB4D0DD877950ULL, 
            0xFFA4FA8B44EFCABDULL, 0x519D54D1E5F6782DULL, 0xA4B93167412390D6ULL, 0xA8229EA4685B887EULL, 
            0x6E757895FFA11626ULL, 0x8933407098A6ABC1ULL, 0xA684B60F2769E74FULL, 0x71FCF1A29DD2CAD0ULL, 
            0x559674EB4A7E3885ULL, 0x1C62BDD1B1381E41ULL, 0x7D20FE2B839856B2ULL, 0xDB3C841B0FFEB73CULL, 
            0x68946345F59D54D2ULL, 0xE2727FEB5C83C2B3ULL, 0x7E80A129BD30475FULL, 0xF4E58F284E6D4B02ULL, 
            0x1F1F477D47944ED3ULL, 0x93EE52C373280579ULL, 0x0E400E00834A4B82ULL, 0xB247305FE07069BBULL, 
            0x7EDD6BD12C104528ULL, 0x0C104EB69D8E8226ULL, 0x70E5778DE104ECE5ULL, 0x3D52DE036D4CA108ULL, 
            0x4336BCD62CDBD84FULL, 0x3018FA06972CFB62ULL, 0x7DC4563B376419D5ULL, 0x59B203CEB223077FULL
        },
        {
            0xEF966081DBFB9AD5ULL, 0x5EFC7374BEE19784ULL, 0x566462860C1B5AB5ULL, 0xD05F444F94BF4C20ULL, 
            0xFBD8AB00B7E2E092ULL, 0xC970FD4A7BB0706FULL, 0x2CC66A3E6F5BE618ULL, 0x1B67556878932B9FULL, 
            0xB9B57DA90FC5FEC9ULL, 0x56D348F3DE4EE227ULL, 0x819A0CB6A88A42FAULL, 0x41D6F72D1C4AC945ULL, 
            0x592E5F2182FAE370ULL, 0xCE468ADD3D2AF402ULL, 0x0C17AAF54882935DULL, 0xCD31B00F4A693578ULL, 
            0x7788A7421044020CULL, 0xE941887CC4F41041ULL, 0x67BE45B1E1AEAD6DULL, 0xF44B02C4ABCC3812ULL, 
            0x0CFAF44F600AD6C0ULL, 0x58D2C8D0B1B6B69BULL, 0x8E7DF65FC2B1D226ULL, 0x0016B3FB53F7448CULL, 
            0x02338B78630A9C17ULL, 0x749BFCAEDA339506ULL, 0xF39FC5F1739925BCULL, 0xF0E81572484C5F49ULL, 
            0xB52452051891D2C5ULL, 0x40800A168CC72D07ULL, 0x18806F3B9A6E893EULL, 0xD4399B31602639E1ULL
        },
        {
            0x9879B90A118EF6AFULL, 0x7776C823326DACEDULL, 0x16E240E2BB59C2F4ULL, 0x90A736F2CC491FDBULL, 
            0x391E5ECA29812573ULL, 0xE568024F033CA6BAULL, 0xDC86F0E3B271A8BAULL, 0x6CD3A19AF449235FULL, 
            0x5EEE323EC7FC087FULL, 0x6932C520392CC4FBULL, 0x9DB0F3479FB4EA1DULL, 0x37BEF809556DF36CULL, 
            0x0AD5E364899EF391ULL, 0x435A81B1F80FF453ULL, 0x1E0D87A7A8A00693ULL, 0x39F3428D7C959C49ULL, 
            0xB7B5DC90481C3159ULL, 0x5AB530E4A7B3EFB9ULL, 0x14FE39B48C04784EULL, 0x6EE0A29FFEA7F1C0ULL, 
            0x9C617C88C45554ECULL, 0x7E8BCCF9CAB0EE4EULL, 0xD05191266D634885ULL, 0xFB1760F243706D55ULL, 
            0x0ABA83AA70050301ULL, 0x7066A1040C23B38DULL, 0xB9011F8841B43C9AULL, 0x1F10618D27350F58ULL, 
            0x0F251471EB3AC275ULL, 0x602E44821F74BE32ULL, 0x676414669F5DCD78ULL, 0x7D1E113FC83BCEE7ULL
        }
    },
    {
        {
            0xE980DC437E825FF6ULL, 0x87B539045C003526ULL, 0x7DD2CEEBB1292F0DULL, 0x8357C09D7BF743D0ULL, 
            0x5AF9E3A3CB037468ULL, 0x19CBADE91ECA5136ULL, 0xF4D52A00FF4EBB79ULL, 0x1434F88F0D94EF66ULL, 
            0x499CACA0875A06C7ULL, 0x65D1E9847A015933ULL, 0xF68B877F86E0F8BCULL, 0x9E60776477DE48A1ULL, 
            0x57378311970E6818ULL, 0xA99B653147A581ADULL, 0xD0A4DAC1060D8062ULL, 0x6C42D47B5B9E7C24ULL, 
            0x3A66696C48DABFB7ULL, 0xD999AF0855E5341BULL, 0x1FBB0E736E72AC12ULL, 0x11BDA0E0E1D6ACD2ULL, 
            0xFEADA3A4723148C4ULL, 0x9364D6D155BFA8AAULL, 0x14E0F79903ABB647ULL, 0xDF0C1F3949359567ULL, 
            0xC9D11BC0B86423B5ULL, 0x9C90AD9E8CB9F279ULL, 0xA2DDC96D0981494AULL, 0xCBEC80A4A075F488ULL, 
            0x28BA823BD62E40CAULL, 0x77CB40829D655CDEULL, 0x8EE6365833D39E15ULL, 0x0E81733901AB6BDDULL
        },
        {
            0x9096EE6ECD681644ULL, 0x263074F17B3823BFULL, 0x0CD03941E3DD9470ULL, 0x3B5481C31A2B8FCAULL, 
            0x6F366CC5F087BB05ULL, 0x9D738F9A96A52323ULL, 0xF347A0998609D1BFULL, 0x679CBB3BAE59A04BULL, 
            0x301F957112A7038FULL, 0xC9A3D88D56F9FC19ULL, 0x147B32941F97CDADULL, 0x0C548FF430FEC4D0ULL, 
            0x055B3FC83C4113E1ULL, 0x1ED808822BF0622AULL, 0xA6E6BC4965F018A8ULL, 0x4840BBFD3D8CC559ULL, 
            0x8D78B58E404847E0ULL, 0xE8CAF1F3176D4F91ULL, 0xA90D5DDF65276F8EULL, 0x5388F38CD4EFE4DAULL, 
            0x9A36D781564CBB71ULL, 0x01BC1208884238BCULL, 0x8817EFBFD20C92F6ULL, 0x9E7AF6454BDFED44ULL, 
            0x76085DB9DBEF7FD7ULL, 0x410B732DC16B1987ULL, 0x6FA3854156B2209CULL, 0xC783164D2CF6185BULL, 
            0x72D09637332A9317ULL, 0x81E1A62155C33D41ULL, 0x114030CE54DAD3EFULL, 0xE4B230C381EE16E2ULL
        },
        {
            0x025637A3B0D2E84AULL, 0x9BF6945EB636F48BULL, 0xFCEFE20E65B97E5AULL, 0x40B0B9068765B7E4ULL, 
            0x4640AC25C2745B0DULL, 0x6575A5279E3462B1ULL, 0x91C7F8F0CAC9A205ULL, 0x2FBC8B614AD8B74EULL, 
            0xA222B41621FFC27BULL, 0x2EBC27E725910B0DULL, 0xA5766314535CE331ULL, 0x4A928B6DEE65CC0DULL, 
            0x444A0FC279507259ULL, 0x4CFC7D0B23374BC3ULL, 0xBB540EEC0A7B0D7EULL, 0x894CD7EC0057ACACULL, 
            0x546949C75ACABA32ULL, 0x51C74372CAA522F1ULL, 0xADC0831966ECA010ULL, 0x70D7D847F5C06004ULL, 
            0x161F1B25601B589BULL, 0x6519B2920858415DULL, 0x562FCE16AB29A1CEULL, 0x04384F466474BA62ULL, 
            0x287DC40F5E78E380ULL, 0x1E6E69DF9EA54BA0ULL, 0xB2F38CB3A2DFC465ULL, 0xDE06D7357AC977CAULL, 
            0xDA6CA9DA2987115CULL, 0xDCD2C4322E90BB26ULL, 0x245365B54C416590ULL, 0xE35DF4E00763C9BAULL
        },
        {
            0xC6A030C1ECDED03EULL, 0x2668809C22CFFECEULL, 0xDEE4A1D4913592AEULL, 0x674E56F6ADC9F2DEULL, 
            0xBE539D7578FD4413ULL, 0xDF46232C6B94C2DFULL, 0x8FA4638BA1FFCAEFULL, 0x5E6DD7C357CC79F5ULL, 
            0xE374391BB021C536ULL, 0xDCF5E2B53EFC42B9ULL, 0xB29AD29E8E6EEFABULL, 0x686640A53EFB7579ULL, 
            0x3AF0107B33AD6273ULL, 0x5F604943809A266DULL, 0xA394F85C4869C29EULL, 0x277A3575717441E7ULL, 
            0x2FB53CCB11318D37ULL, 0x01D675629A38BB2CULL, 0xF4C0348009998D2CULL, 0x5E5425AA223D89D6ULL, 
            0xDFC6CDC1C3463730ULL, 0x4AAFC9F891BC6BD2ULL, 0x3E4DA70CC705F085ULL, 0x6E4F394BD38EF382ULL, 
            0x770A9C667A98E141ULL, 0x0D2F62714FA6C459ULL, 0xAB48812628479437ULL, 0xCAB722C1F9B30702ULL, 
            0x737A2BF28B3B921BULL, 0x41CF0A9BDD1261BAULL, 0x297E54F95D862272ULL, 0xCE47AC3051CD4EA8ULL
        },
        {
            0xA92E7FCB6F8A95E7ULL, 0xCFE1E831A950F50FULL, 0x100FE27B1D729D25ULL, 0xD3ED2355B0599D57ULL, 
            0x0927F287F8AE2797ULL, 0x9908F3203DD5962CULL, 0xE8B1568626C93664ULL, 0xBA7B191BB05F7017ULL, 
            0x206F5464238318BFULL, 0x3109F2BD73B75BD6ULL, 0x9349D7E419A08961ULL, 0x89A7C4D013E531B3ULL, 
            0xF7D5EC40F60B3C01ULL, 0xBF600D6BA839D4C5ULL, 0x92654F2F8D8AE5FAULL, 0x98FA5351EA9DAF54ULL, 
            0xCFA35EDA7F62A637ULL, 0x31872F6087F121ABULL, 0x3C0EEEAB8EEC7BBDULL, 0x1F421DE5C5C50CA4ULL, 
            0x5CC8CB78A10A5DBFULL, 0xBD6E619D53E59FB5ULL, 0x2ED83B0472101315ULL, 0xEE0C671C57231476ULL, 
            0xA858ED677F065BAFULL, 0xF4DF8705C477C6FAULL, 0xA636128BE8BD1787ULL, 0xEAE5C0D1C0FF12AAULL, 
            0xED09B7F9067CF0A0ULL, 0xA45DD6171C354C89ULL, 0xEDAF65153AFA6C78ULL, 0xD0B37309722DB973ULL
        },
        {
            0x683C67F689A744A9ULL, 0x861932573C208D4BULL, 0x04C670B13AC8B5E3ULL, 0x9B964B137A71091EULL, 
            0x8C0AB3A2EE41711AULL, 0x53D7AA0BAE0D63C0ULL, 0x5C59729EE258A08DULL, 0xA1B71869B0A93522ULL, 
            0xBDCB2A5DD556B7FFULL, 0x4A6B597C9BDE3653ULL, 0x45BE77B83D86BE4CULL, 0x2B418DF3C29AC7D9ULL, 
            0xD692A264B97CAFD1ULL, 0xBAEF81C5A0DC77A3ULL, 0xD6CF4997BD708CC4ULL, 0x64CA7DE14E116109ULL, 
            0x39AC87063D0A847FULL, 0x9620E522E0A1D9F0ULL, 0xC541A3E349BBE33EULL, 0x2CA3B1BD354D4664ULL, 
            0xFBFB8C4393A2779DULL, 0xAB640FA565FA2810ULL, 0xF8578FF3592DC529ULL, 0x6E4EDBC7DC50A656ULL, 
            0x745805824BA2CEB0ULL, 0xC3CE5E459E7B40EFULL, 0x4652E79A1EABF086ULL, 0x9FC156E94BD6929EULL, 
            0x76080D03412BA4B9ULL, 0xBD65853796D32444ULL, 0x100F0B347B3FFD6DULL, 0x2A9DF0891876D8C8ULL
        }
    },
    {
        {
            0x0A767AE7EACF06CCULL, 0xB5E229B5A209608BULL, 0xDFB3436DDD5E1A45ULL, 0xC4391322CB88C2B9ULL, 
            0x20C16E248838F708ULL, 0x757125F2C9532927ULL, 0xC283827C1DC51FE6ULL, 0x315186E631C753EDULL, 
            0x237D74A2B9CA960CULL, 0x8BBF1D326665D553ULL, 0xB2095824CFF27D7BULL, 0xF78AC648A1628B08ULL, 
            0xB791A0B2620CE9B6ULL, 0xB79AE75D4E034425ULL, 0x272597773D10A854ULL, 0x23CA1888F6C3EE07ULL, 
            0x6CC05A2553A3DD60ULL, 0xF87F0EE2FF7D80B6ULL, 0x0BB48C96768EDD3EULL, 0x1DDFF8A107334562ULL, 
            0xEDE28625D162C015ULL, 0x59E02533A28D317FULL, 0x3BBCE25846EA77ADULL, 0x9CC8BC410DDD6B3EULL, 
            0x885ADEF80F009B37ULL, 0xBF860B95B8886892ULL, 0xE08B145573C3D27CULL, 0x2B465243E59DD7B4ULL, 
            0xB677442180BA35B2ULL, 0xC2006E67DFF545D0ULL, 0x75F15E851EA79717ULL, 0x2841AB139113802EULL
        },
        {
            0xC3964E3683826B92ULL, 0x8D4DFBF272C76A46ULL, 0xF4B8BBB72C667BA7ULL, 0x3CF72EC176BE9916ULL, 
            0xB8CB23CC65E38BA1ULL, 0x97094095CA073443ULL, 0x06DF3AA97CA85C8EULL, 0xC056E5E485CBA33CULL, 
            0xC65A737F07492234ULL, 0x25F05CC0E64DA52AULL, 0xE7C2C89D1CB8CB3FULL, 0x1B19C769DE240926ULL, 
            0x8B1E31A074DD3BCAULL, 0x2ED8CAA9264278AEULL, 0x5F9DF565A9012A80ULL, 0x8A0CC42FE9B49041ULL, 
            0xBC0D0EE3B9940867ULL, 0xD7562B1C0061A87FULL, 0xBFC3EB7C0E024F6BULL, 0xA0AFD611827812ABULL, 
            0xC3F19388D19A25E4ULL, 0xA77FFA43B6012418ULL, 0x7B8963426CE6C956ULL, 0x4C32DDD66A586593ULL, 
            0xD7B414226C3C6A8EULL, 0xE4350758925AEC2BULL, 0x6623707A277BCEBDULL, 0x8DF9FC13CA5B4E73ULL, 
            0xDE23A0856BDDD8BDULL, 0x21AAD621228FFD6FULL, 0x9E8A60E12E3AE456ULL, 0xFFF927043274ADB4ULL
        },
        {
            0x4B89C16D4E5DF46FULL, 0x1F51668510B19F72ULL, 0x2A23D416A88BBFA1ULL, 0x8C5A7883FAAADB15ULL, 
            0xD01F62094C4BC165ULL, 0x6D25AC164E91F117ULL, 0xBF121D61B3E3AE2EULL, 0xA15C6A80C2D15BD5ULL, 
            0x22C9096C37CA359BULL, 0xC442E3E047B9F59BULL, 0x3E81924F9FD7AA1FULL, 0xA88C7FFC9600D5EAULL, 
            0x482D8F5FE8894BB4ULL, 0xD5C5F62481054A9EULL, 0x2126538BF8253882ULL, 0xD07663C16301CD21ULL, 
            0xD6E1FD218B1A5EF7ULL, 0x4A7ECE942395B6B3ULL, 0xFFA84430FB56AADFULL, 0x57EB957434B6BF84ULL, 
            0x5A1EF87E8D8873AFULL, 0x43738A53762DC825ULL, 0x2B752807F903532DULL, 0xB6BCD6E084E7204CULL, 
            0xABDDBD9A24FD3DBBULL, 0x57ABE459B1B0C555ULL, 0x992D295ADE508771ULL, 0x91583228041FD06AULL, 
            0x879304F8F8680AB0ULL, 0x4F1098195B381774ULL, 0x0DA87818856B6179ULL, 0xD7E915967B43408CULL
        },
        {
            0xF0C77C174071F73FULL, 0x5F03E3A40CCC5BC6ULL, 0x893FA169C66219D4ULL, 0x5DF8C81850259943ULL, 
            0xE3D46E55E3DCC2F2ULL, 0xEC85FEE7D33BDB31ULL, 0x49002E3EB3951455ULL, 0xD3508925F00C8A9DULL, 
            0xC15614CB99112E90ULL, 0x9E6BE413F2337316ULL, 0x58B06D717B99101FULL, 0x958460CF08471534ULL, 
            0x7A36F839E0012ED6ULL, 0x41530E8CD8B70059ULL, 0x0AD1B991E3F8E44BULL, 0x0652D73813E422A0ULL, 
            0x062C549A80655E3EULL, 0x0C38EA0D7B358B69ULL, 0x1B8D7DDF4F4BB98DULL, 0x51E72DAB19F421B3ULL, 
            0x5337F1887322A49FULL, 0x7713EEBB999B85ABULL, 0x09472C910A843147ULL, 0x647C6B16D7441F56ULL, 
            0x8FDFCEFB1C10DC90ULL, 0x896EB206E2013E30ULL, 0xA8AB71EB85DC8882ULL, 0x1F5303C7969EC53AULL, 
            0x6AD2B0BAFE82290FULL, 0x445C60B8A39D4BACULL, 0x33DD0CD81D60DEC0ULL, 0x39F5187C642C8168ULL
        },
        {
            0x583CC64AD9F27EE5ULL, 0xCAB08B95B43EB63BULL, 0x89794A69AFB3DA88ULL, 0xAC196BE478010262ULL, 
            0x19DA66D6C92C9908ULL, 0xB64E435CD10156D2ULL, 0x9C8331471AABC244ULL, 0x655CF98E85D4916DULL, 
            0x1050C8CF17943346ULL, 0xB8298D7BEBB6F21DULL, 0xF01C8B426883C3B0ULL, 0x7F62D29501806EE6ULL, 
            0x366E9A02407F009FULL, 0xB1583BFDF64A3055ULL, 0x1553654873F8FF47ULL, 0x51629AF7E5215E7AULL, 
            0x12B87E81598C2EB3ULL, 0x2CA941A10B6D2847ULL, 0x95FFDED3FB804703ULL, 0x70DE643C130252ACULL, 
            0x06E7283BC74BFC77ULL, 0x66F4AEF169E61FCCULL, 0xDAF234932715372CULL, 0x2316ECA4CBAC6725ULL, 
            0xA744338B250AB5D9ULL, 0x593C754E5A7F4B3FULL, 0x6DF7B89673583E89ULL, 0x8B850D9A0F962694ULL, 
            0x08BADC69C2A54251ULL, 0xFFD2EF84853C3C7DULL, 0x5F55EA9C126306A8ULL, 0x1E3F4BC869C57E18ULL
        },
        {
            0xA8C6F5B4E2210DDCULL, 0xDC2C6525D4027126ULL, 0xFB4B54FC4C45B28CULL, 0xDD1DD5E7C603EBA7ULL, 
            0x57CFB3BD049B1780ULL, 0x9768998911117036ULL, 0xADA43BC6C66D134EULL, 0x42457DFC183F6A17ULL, 
            0x29AB0E0909DE0174ULL, 0x12271355997A5902ULL, 0x253C26035C1E34DBULL, 0xB0776958A1395A47ULL, 
            0x855CA831C0663755ULL, 0xDCC59E5A7ABC7578ULL, 0xBF63656B4B03C784ULL, 0xF3C6461F43AFC9E9ULL, 
            0xF0113B59F1958865ULL, 0xD22ADA5F0A8A9D5FULL, 0x935173437172FC83ULL, 0xDF48837131EE2ACBULL, 
            0xE9D1646E96991423ULL, 0xCF53C6EDA36E2B6CULL, 0x80103EF27672FA49ULL, 0x303F5073B0BF1E35ULL, 
            0xCF83AA159BE31C80ULL, 0xE5D4027205D53E58ULL, 0x0588F07C063313DFULL, 0x480AA7F7ABBDCA79ULL, 
            0x6695125E7943752EULL, 0x660B306054B837ABULL, 0xC6C9FE3D941B77FCULL, 0xB77CCCA0F5CBDF9BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseBConstants = {
    0xDF561F5106A8AA11ULL,
    0xE1A4A7441953227CULL,
    0x6940ECA6E8F2F17DULL,
    0xDF561F5106A8AA11ULL,
    0xE1A4A7441953227CULL,
    0x6940ECA6E8F2F17DULL,
    0x06510D6DCFB1261FULL,
    0xE4EA8C9C34C71977ULL,
    0xD3,
    0x27,
    0xA9,
    0x8B,
    0xE0,
    0x1E,
    0x6D,
    0x44
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseCSalts = {
    {
        {
            0x41DC533BD61CCE85ULL, 0x70A879E3124CD686ULL, 0x96994FF030A7C10AULL, 0x74FBCE6876254BDDULL, 
            0xC32426E7DE6EDA2FULL, 0x2B534490B5F9E531ULL, 0xE84080595B9D05C2ULL, 0x3BFBD206B8623601ULL, 
            0x64B281597E23B7F8ULL, 0x7307AD82D9A1EDB3ULL, 0xFF39E30661DEA31CULL, 0x7CF2884636E74911ULL, 
            0x4E81CB0D7E79B547ULL, 0x3187952D913FE367ULL, 0x91315B5B6FBB36EFULL, 0xB27F983A4822FF7BULL, 
            0x7BBBDDD581592ED9ULL, 0x41B1D01868AC93CAULL, 0x5EA47FAD9E8FA852ULL, 0xA553610212FC9805ULL, 
            0xDC4FA1D905DB9415ULL, 0xAF7A4B346AF8DDC1ULL, 0x1A7CAEBCAC54E1B1ULL, 0xCB4AF96E81BDA95BULL, 
            0x2F3594D16A067560ULL, 0xAF6F160732ADDB92ULL, 0x955B4FB9EECFBC75ULL, 0xEC6D3DDCDE5D9989ULL, 
            0x0EC59A16373E8B4EULL, 0x3775EEA4611EF348ULL, 0x97BF3B04E13A0D93ULL, 0xBB0FAB35267A1068ULL
        },
        {
            0x125EAC99E63F07E4ULL, 0x506EBACED94E8B81ULL, 0x6B005987BEE922EBULL, 0xF67D0BDF5C3E1E69ULL, 
            0x80D07832BCC4CE11ULL, 0x8209F1E7AF6E6F2AULL, 0xA90B93851FCAE6CDULL, 0x3D0B5CC7995919CBULL, 
            0x24C6A6CD2F68262FULL, 0x7AE68DC43F3CF76FULL, 0x7213CF6E8729E3DCULL, 0x0A4378F771004627ULL, 
            0xE9F8F0B1F55EE562ULL, 0xA51BDD28BFAA97CAULL, 0x709CA4C99411486AULL, 0x6F9A231E5DAD6EBEULL, 
            0x2A2A1042A4870AE8ULL, 0x4165961C594A25F6ULL, 0x44B521CB89DB77B2ULL, 0x98A44B312964FF2AULL, 
            0xE3ADFC59936D0E9FULL, 0xCD95F9B7C25CBD32ULL, 0x01B9E7B403C123F5ULL, 0x3496ABB07C49AA3DULL, 
            0x5A7B9AACDD4734AFULL, 0xF7E127073765E911ULL, 0xD2B748780FB8B609ULL, 0x400ABB64872253F4ULL, 
            0x9EF4358A0485DA45ULL, 0x37E3682938CC6A6DULL, 0xB19104C578F1D3C9ULL, 0xCC36C4FB34AC3F3EULL
        },
        {
            0x8BC37A5D8EB562B7ULL, 0x913DA4E4F770D12EULL, 0xE377CCC1E2B68055ULL, 0xDF17615669A23519ULL, 
            0x13ECDB2DEF06E8BEULL, 0x66B2CCA4A66418F4ULL, 0xC6DB042A4CE3E1B4ULL, 0xB94A08AD9870F68EULL, 
            0xFA33EFB905BCC650ULL, 0xE84F28050FFB8DF0ULL, 0x2EC3EDAFB7FC0F50ULL, 0x1355FBC983E23961ULL, 
            0x1FE4E55A656563B6ULL, 0x5198FAC8195A12B1ULL, 0x6199D38C102BB2B1ULL, 0x37F077C3DCA22710ULL, 
            0x100027282DB1DBDAULL, 0xA78FD9B1C118E8ACULL, 0x40120B410D6B7A30ULL, 0x6D35683E73015664ULL, 
            0x89385172DB73BF48ULL, 0xA07DA199A6E583FBULL, 0xE489B33D0B83395CULL, 0x08E9BBB459CC4EDAULL, 
            0x0201F15D6399EE00ULL, 0x700BA98BBD1B6FFEULL, 0x271186068DC7F425ULL, 0x4B1DACAF82A11D4FULL, 
            0xD6169CA1270170F0ULL, 0x1E5541A2B4033991ULL, 0x1C83B47EF7E7C149ULL, 0xAABAF4E9B90BC032ULL
        },
        {
            0xD0912C7437FF4B00ULL, 0x90E84F81B07A0D17ULL, 0x4236A0EFF2053767ULL, 0x039B969DBE6D6767ULL, 
            0x116853C555F57C51ULL, 0x34009CCF2005F17AULL, 0xC521333E04697BDAULL, 0x09B10C0FEA4397EFULL, 
            0x31E4DAB6110B4476ULL, 0x2BC9332E266D4CB6ULL, 0x83E2D31FEB63529DULL, 0xE2F6AD4D10955E75ULL, 
            0xC69E6F6F56C2A559ULL, 0x1B5E406BCC87E89FULL, 0x8B9F2F5CD5A8DB23ULL, 0x96195B7E1F45423DULL, 
            0xB1709B81DA4E27F4ULL, 0xE18EBF6E82984718ULL, 0x49179748AD6D9C3EULL, 0x181AE8AC3C9D6F18ULL, 
            0xB07B0B40FB9A70DFULL, 0xB8C3F8B2B44CC041ULL, 0xCE234249490FEA78ULL, 0xDA8A3F248D3F2881ULL, 
            0x34D5E185418BDA92ULL, 0xB3EE5D76BCCF6980ULL, 0x5B6BACEF2649B622ULL, 0xBA3592B1D79F22EBULL, 
            0x4B01AE6F873A3167ULL, 0x4D9860C77176205EULL, 0x63AB3C211773503BULL, 0x788CB027F9686054ULL
        },
        {
            0x6FF9C35254FCFB06ULL, 0xBEAAFFE12C164D28ULL, 0x5722441D97AB6123ULL, 0x87973A5B84D1853FULL, 
            0x3C4060B9A5BDCDB0ULL, 0x3FAFECD98FD88F5DULL, 0xA65C38518C430CFAULL, 0x1835DD97D6514CE8ULL, 
            0xF62F58C3F7430034ULL, 0x2990384D0BFF5D11ULL, 0x4AE9C15346D1C89FULL, 0x402A7A757CC7468FULL, 
            0x68C94923A86E01D4ULL, 0x7A0025F5C10418EBULL, 0xDB2C52667E89C11FULL, 0x169E5024EBD7C718ULL, 
            0xDE0168C8DA4C9B13ULL, 0x923657F9712ADFB0ULL, 0x8AD1AA3DEFFBC494ULL, 0x01EEE0721FA56418ULL, 
            0xC10A4E346F0EA0FAULL, 0xDA2830EE61665EE4ULL, 0x2D50D3B0C9FC806DULL, 0x8B36C1DCF2E3AB05ULL, 
            0xFDF03E9BAEC38A0CULL, 0x34C86262F619A0CCULL, 0x39CBCED8EA8EBB8EULL, 0xC0F5F1BC45849787ULL, 
            0x09F3D4C589C1EA13ULL, 0x89CA55BB8092B441ULL, 0x5227F0DF8016F1A1ULL, 0x8B8B57DB6571D718ULL
        },
        {
            0xCF914E50C4A6F348ULL, 0x7CED4F4105E9D137ULL, 0xF3BB29BBB37D8753ULL, 0xD803F0A14B62E781ULL, 
            0x9B166E050919C5D4ULL, 0x338C76978BB8A780ULL, 0xE96F2DB3C6501679ULL, 0xF29281037D510C5BULL, 
            0x7E13782CF44CF284ULL, 0x9BC7CAC9EA99B7DDULL, 0x7D4145CD9D0D568DULL, 0x76C7092D88B3F826ULL, 
            0x22E424F8203F4DCCULL, 0xCD62DEF211DEAF5EULL, 0xE4ADDCEF47B933C7ULL, 0x967216143D56D0DCULL, 
            0x410C3C22602251F9ULL, 0xF07DFA27AE11257CULL, 0xF91C204C69A33A31ULL, 0xBD54D8DCCBF99AB1ULL, 
            0x53C3E8CB3A41FA5EULL, 0xA9CB6CBFF12AE269ULL, 0xB56B1CEC2F520B74ULL, 0x64BB9E8CECBB273FULL, 
            0xB922CDD3EA73E806ULL, 0x01BB1DE1BC533B7AULL, 0x221F9C57E11E43FEULL, 0x2492735E966E32DCULL, 
            0xF6E759163CAA9DC2ULL, 0x8CAC46F8E228CC8EULL, 0x43586C317A6D3D05ULL, 0xC5D2BB3B71C033D1ULL
        }
    },
    {
        {
            0x9A4A0F26A874878EULL, 0x2B1A2685ADA20B25ULL, 0x04A301B343BA1EBFULL, 0xF16D573AC8BFA8EDULL, 
            0x119498E1ACFF1B7FULL, 0x6C6C1B709D25B80CULL, 0xDDEFE3179DD6630DULL, 0xECA17A7A62780BF2ULL, 
            0x3C8F141177DF1FA9ULL, 0xE2A124759CCF8B03ULL, 0xBB8DC49AB8BCAD4EULL, 0x0C75FF12BC3E9A55ULL, 
            0xBB5B8E2C290D27FDULL, 0x5AF607A344F6D993ULL, 0x0F407F601AC3DA18ULL, 0x84E38FC368196641ULL, 
            0xF160B40DC8014B35ULL, 0x640A27DF0698C4C4ULL, 0xE2E74D8164E30E01ULL, 0x1243D6A711A85E4DULL, 
            0x8A4B04F10C233495ULL, 0x7592F1278E4624E2ULL, 0x211BF94271A2B9BBULL, 0x0592B782C83AFFCCULL, 
            0xB92FDF171B7C4559ULL, 0xBAC30D788E0005F9ULL, 0x37384FC890842595ULL, 0x6FCEF24AC04E8247ULL, 
            0x40E7E87F4277DE12ULL, 0x604E4F8146B11D99ULL, 0x68B5F82D1DA5497FULL, 0xBB1424327968E061ULL
        },
        {
            0xD2AD136329559327ULL, 0x1AD602DD6267E042ULL, 0xB5C4FFEE51B038BBULL, 0xE98B0335A7AF7292ULL, 
            0x2CBB838A1A067521ULL, 0x8BB597478414A73AULL, 0xB09E808354A54875ULL, 0x9B6B5BC990592F82ULL, 
            0xDCF1965956849681ULL, 0x8C12B2DE41C7F384ULL, 0xACB465AE1F9A2998ULL, 0x3929ACE060351F30ULL, 
            0xBC7354FDA16BD6EFULL, 0x37E19678D441F4BFULL, 0xDFBC1723933B054DULL, 0x9AF15796223F0ECCULL, 
            0x4030BF971ADB47E5ULL, 0x2E0458705C589FBBULL, 0xBAAA41A12C5E4834ULL, 0xE2723C809D7AD3FCULL, 
            0xFDCC632BB37EC535ULL, 0x410FCAEC61BED9B0ULL, 0xBB590F500756243EULL, 0x052E4A2105521E1EULL, 
            0x56F57FD20336508AULL, 0xD6D0B8DD903C6FB3ULL, 0x6FF8A57406437398ULL, 0x92271AA49D1634F1ULL, 
            0x2C0ABBFA75E927C5ULL, 0x838C31460B6DD049ULL, 0xEDB05BBD8985D307ULL, 0x77B4250C8D75851DULL
        },
        {
            0x778B3A58BB490EBAULL, 0x67B4B31D9B6CACE8ULL, 0x9F9730EB9BCD8BDFULL, 0xA2A08941DDA64D98ULL, 
            0x2718F33AAAB9328CULL, 0x7CCFCDEF1050431FULL, 0xFC168BD79D2F2A5DULL, 0xC6596AE2AD569F53ULL, 
            0x120D2036CD40E765ULL, 0xB02E1ED05C31D330ULL, 0x00C53AD80683CEACULL, 0x82E7B5C905256669ULL, 
            0x472B7A2A14B1F572ULL, 0xA06F0460F2F3E755ULL, 0x82A138493D2BF47DULL, 0xE90474CBE080B999ULL, 
            0x19503E1DA88914BFULL, 0xEAABF41FDEB47F2CULL, 0x8654DFCE57F40F9AULL, 0x26ACD57BD8E7C4C9ULL, 
            0x39151E54C6383DCBULL, 0x983E5DADD9113B1FULL, 0x1C738C2AA648B9B2ULL, 0xF0368D0AA087443EULL, 
            0x2F6A7A6614BD33EDULL, 0xEB22D6C8B810D313ULL, 0x42B475F77D2612C2ULL, 0x91144E50BF2531EDULL, 
            0x8368C9AAC69D30A4ULL, 0xF4297ADB80BD1103ULL, 0xCC80EBC1E91D5E8BULL, 0x3B6AB470D4E321C8ULL
        },
        {
            0xF4EAAA6FFBB155CCULL, 0xA4D7E7EF67890230ULL, 0x6D5BAB157F2A95BAULL, 0x8BD5EDF8C53CA8D5ULL, 
            0xC081ADBE80121604ULL, 0x3FCFB69BAE5A0402ULL, 0x0B1B4F1B0D1C3A6CULL, 0xDD5DA6407B03B336ULL, 
            0x4E98E27A73522DFAULL, 0x549C49C3FB779959ULL, 0xD13C979BEA81B532ULL, 0xE699D3CBEA88D684ULL, 
            0x196A6BF8D65EA859ULL, 0x0D318ACCDDC86B37ULL, 0xF525DE5279B99AF3ULL, 0x204BA1E66776DB92ULL, 
            0x23EA326273336567ULL, 0x5FAD31EF526E930BULL, 0xF3B8B70EC9C9AA48ULL, 0xCA7987990502FD60ULL, 
            0x7D95221D568020ABULL, 0xE5737AD782C145CCULL, 0x408DBF4387005972ULL, 0xBF7B67459B91DF8FULL, 
            0x4C3AD4F260E39FCFULL, 0x827EC9A0CBA508F6ULL, 0xD3C27C6B1930C0BDULL, 0x5B68F00B30927B08ULL, 
            0xFD0A563D991663ABULL, 0xB06E11E75915466FULL, 0x2D164F967C11DF81ULL, 0x9DE3A57A20C5F8A7ULL
        },
        {
            0x824F9EDD59D20F0EULL, 0x63D645195E6D3F93ULL, 0x269A06763333E050ULL, 0x4E28DBA7C83D7C03ULL, 
            0x9207834ED25DB2D4ULL, 0x9CC481C9F0A9678DULL, 0xA41BF46B773F1685ULL, 0xD52C657C6ED476E2ULL, 
            0xEC4CEC6E9F7F9DA0ULL, 0x2D082FBDA3DB3CF0ULL, 0x5377AD5FA58A3C58ULL, 0x7C9BFA4F2B2E3B83ULL, 
            0xAF4B3DA53A6DF35BULL, 0xF6804EE780421D1DULL, 0xD12CCAF26D07444CULL, 0x2E8637E59A721843ULL, 
            0xFACBEBF3D0730566ULL, 0x4E8603D957BE46C6ULL, 0x79FBB55743584F81ULL, 0x231BED6D654199A0ULL, 
            0xE87C0FB972E0F57FULL, 0x0792D570A045BBF5ULL, 0xC9A5E1DD2A6D2323ULL, 0xB99E0109870F8AE9ULL, 
            0x9D8F7CCFF09D6782ULL, 0x935B4E1424A51471ULL, 0x17C8DA59D7B09C6CULL, 0xA87A7EDA469280A7ULL, 
            0xF0A9D3F971F11001ULL, 0x0B622D0FE6D46BEEULL, 0x2315C24F0859EB8FULL, 0x2DFF975B14F24D5BULL
        },
        {
            0x98A52C74DBD09914ULL, 0x156CC7FF2129844FULL, 0x6E323BDC8114191AULL, 0xC8FAB2E51928FE6FULL, 
            0x2FD0FB73DD1BC0DFULL, 0x6067E2D3025A30ACULL, 0x22618F54607614FEULL, 0x88937EA36ECF889BULL, 
            0x571F04AEF4848F99ULL, 0x2AC45E764DB3CC60ULL, 0xCD5AFB5602625987ULL, 0x73DDF042C9F78935ULL, 
            0xBA9FE45AC8FB8F09ULL, 0xEEEEB4F18C4F12F3ULL, 0x89BCF96F420D8887ULL, 0x5D04257E1C8CBDE3ULL, 
            0x294E646459263FE7ULL, 0x92EEABD28D390258ULL, 0x0BD04702203AC48DULL, 0x73F1017BF649FD3DULL, 
            0x6A2FDE4A1AA45217ULL, 0xDCDD58E20192A1D7ULL, 0x45BD013F3CFBCD2FULL, 0xE8F6B956C84AF032ULL, 
            0x41462C7262311FAFULL, 0x9B17D73791E767A7ULL, 0x09BE666320AFDE4BULL, 0xBF551A69FB5E16C4ULL, 
            0x681974144E33E1A8ULL, 0xF1CD3CCB57E07DAEULL, 0x564678248950CF92ULL, 0x442A7F12577D1227ULL
        }
    },
    {
        {
            0x3EA68B39D7E6EE1BULL, 0x8CB981600427974FULL, 0x8B426F4F430459F3ULL, 0xF1FD5709947D7F5BULL, 
            0x0365F9AD8C61AB0FULL, 0x802CD991589CA5A7ULL, 0x9D9150D814F7231BULL, 0x461FF49489248373ULL, 
            0x275F524473915E77ULL, 0xC33CDD43E3AE6966ULL, 0x1FB65A9CBF94FD15ULL, 0xA32790823BE39B3DULL, 
            0x5260D263FB1D1FB7ULL, 0x2AA976B6C6A25059ULL, 0x5E82375852238BA9ULL, 0xF44222E9A1AE6977ULL, 
            0x93E07BB90F0CB849ULL, 0x6D02C82399E8CA7CULL, 0x0DD9740A04AB0B32ULL, 0x8467575FADFADBBEULL, 
            0xFCCAB9F36C2895A3ULL, 0x4B9D8306A198243DULL, 0xE7AD7019807F241CULL, 0x115DC1399AAA6D10ULL, 
            0x03D9E442D6159969ULL, 0x57A4ACFFB4BBF56AULL, 0xB779CA8426E39589ULL, 0xA05B83D099229598ULL, 
            0x6941E0309079A921ULL, 0x63C4B2893DD3A908ULL, 0x25E2234D1E688A23ULL, 0xEA022454453EBEF3ULL
        },
        {
            0x9392E62EDC7B9522ULL, 0x651218C4DDD131A8ULL, 0xB063B6E5335EF590ULL, 0xB144C00B31AB902EULL, 
            0xFC5095F333B1E17BULL, 0x32F20579CAEC4AB9ULL, 0xCB87187A989CD9A3ULL, 0x234C90F4B484A6D2ULL, 
            0x026085045EBE35A4ULL, 0x2CAF332BF4DE6FF9ULL, 0xFD50F93B07F03F3FULL, 0x541676E916D6BAE4ULL, 
            0x6A925FF60D06998EULL, 0x42F666E809D9A551ULL, 0xD0F57678C067CA3EULL, 0xE5AC48CB80DF7D69ULL, 
            0xD9F0A143DD1080E3ULL, 0xFBBA05680B10D1DAULL, 0xC0080E84B37F8483ULL, 0x67253A13E81C7316ULL, 
            0x89FBE31F3AFD3DB8ULL, 0x67661B05B4BDF507ULL, 0x0C41B2D5F6B63F96ULL, 0x1538CF6DE293EDDAULL, 
            0x01BBD9ACDBABC9CEULL, 0x560E7ADA180224A6ULL, 0x39852307A4A433B3ULL, 0x676EBF64CB34B035ULL, 
            0xC6A8C8513329C0A3ULL, 0x680B194B9A763C61ULL, 0x1CB7D35F15D75910ULL, 0x405F2A1ADCB6E13BULL
        },
        {
            0x2A270610EB357E6CULL, 0x435F7F47BFF2F56CULL, 0xD15A3AC1C97B055BULL, 0xC519B80B57EADACFULL, 
            0x5E2532F8D9A7D141ULL, 0x8F2942F640A7338EULL, 0x50997C18B7BDE30FULL, 0x5FA9949B6DB9FFF1ULL, 
            0x53C01539037BA983ULL, 0x7A8FD87132A5883BULL, 0x3E5CD3E6135F0407ULL, 0x451C9F9A059AC9F5ULL, 
            0x306C940FC5CBE0C6ULL, 0xF0B5E3086DBB54A1ULL, 0x5D18E4AF49192D1FULL, 0xEE3F3CC297650D23ULL, 
            0xBA8AE377B58FC738ULL, 0x6CB15055E31F9320ULL, 0x2F9A2029D555C178ULL, 0x9B7E0147A242DF18ULL, 
            0x3BB5393DA82B3E7CULL, 0x8F5DA0543BE04D32ULL, 0xA96D47AB7AEA535FULL, 0xB1653550F80E40D7ULL, 
            0xA12A3A975038F818ULL, 0x84ED843A25034484ULL, 0x81AC97DC518698C6ULL, 0xDE294F479B81AAA9ULL, 
            0x0E70C565B6CB51A3ULL, 0xE278A21C30CE9D98ULL, 0x4F66435A4667CDBAULL, 0x4448D281FF16F3E5ULL
        },
        {
            0x0957C1CC86AC6C1FULL, 0x8FE6A4FBF0BE70EDULL, 0xD0A1062C64C17C39ULL, 0x09C30E8B4B57BFCAULL, 
            0xCA226D5579B097E9ULL, 0xF0EDB402D0D98420ULL, 0x31CD393D3D1E7B40ULL, 0xF30F863A311C15ADULL, 
            0x05998005C7C19DCEULL, 0xD6EE487C0B63AB98ULL, 0x7EA5F4F8CFA1E675ULL, 0x7282B5C77A2CD88DULL, 
            0x951668EF5CA24C25ULL, 0x4DB63CA2807DFF5DULL, 0xACC3DB3B7167646AULL, 0xBDA0D89D0E9E4602ULL, 
            0xE94C35ED5DD4CCF4ULL, 0xDAACDC50DBA0E328ULL, 0x5E1EC2CB1C90DC03ULL, 0x70C2261B2A76C6F9ULL, 
            0xDACE46C8066F1358ULL, 0x55BA75D25A732B9FULL, 0x270F8DFC2A04710EULL, 0xB63C533B4284ECC0ULL, 
            0xA0136D886D6903DEULL, 0x75C9E324722B639AULL, 0x157B01462A3FB4CEULL, 0xEFE02A03098D65BAULL, 
            0x62B5539E5F99E9A7ULL, 0x33219F2B60B8CF6DULL, 0x91A9D7309CF03151ULL, 0xA26AF87347DF870FULL
        },
        {
            0x08B0B1C478FAD138ULL, 0xB42C51159A382E5CULL, 0x11702DD7C868C039ULL, 0x3AD10FF15F722E70ULL, 
            0x422B6A1B227F6089ULL, 0x2AA26155F9EB8B25ULL, 0x5FCA83C8BDB50BD5ULL, 0x4D54E25DFB6FE71CULL, 
            0xEB202F1B538EFCB6ULL, 0x6E828C92B91BA8BEULL, 0x9D3EA67BA8AE7A90ULL, 0xFCF9F0631DAA39C4ULL, 
            0x93EA09A07BC85964ULL, 0x77EFD4DB1093D95BULL, 0xA6F9B06500204F51ULL, 0x5B99984FC6CA30C6ULL, 
            0x8D15B09B61487D53ULL, 0x26F5D15F750AF83FULL, 0x4EBEF4C1DEDB0FBCULL, 0x4477FD4153F4076FULL, 
            0xBFBDCA82820F5BF3ULL, 0xF02CD8BC83EED249ULL, 0x8805B10151FB6253ULL, 0x5100AA553098A987ULL, 
            0x6D9C3F88755E534CULL, 0x55C8C52F0674EB1DULL, 0xD5523D8B5093B8EBULL, 0x02E9D34947080EB6ULL, 
            0xD6DD109C8D19D1FDULL, 0x28B8B150DB895423ULL, 0x70809D494BAAB692ULL, 0x4E185450C9C3602DULL
        },
        {
            0x92813D7BC88253B4ULL, 0x5E453D1007D586C6ULL, 0x8BB3D838EBF02924ULL, 0xB0ADC5D01CB9AC8FULL, 
            0x46AB195C0F43CB01ULL, 0x6B4CEB175CC932BEULL, 0x454ED42296FB23BAULL, 0x4A71877AD5F444ECULL, 
            0x1B2CB355FAD1A3FBULL, 0xF62C35F346AADBBBULL, 0x205F98C5F0CB46D3ULL, 0x334055E86D54502DULL, 
            0xE62C97EDC86B66DCULL, 0xE7421C8FDB649312ULL, 0x9529764767E337C6ULL, 0xBE34FD358FC2EDF5ULL, 
            0x292FC3E9A4AC9EA0ULL, 0x585D64FC87E74E53ULL, 0x406ADB1DDF3B6643ULL, 0xC0B96A9A1A79640FULL, 
            0x59E40604A79FEF03ULL, 0x0926022345A9C19AULL, 0x2912BB999D60BD74ULL, 0x8056510E05EC7B9CULL, 
            0xC8D9FB3AC41B7548ULL, 0x20DD2AD2A65A47AAULL, 0xC5ED20044215D6D5ULL, 0x2C84E6869E25F7A5ULL, 
            0xDBFA5F53BFE9D426ULL, 0x7E72896F45F48A19ULL, 0x586766B6099C0FD7ULL, 0x97F32E83636A3CA4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseCConstants = {
    0x9C66068DE032ED97ULL,
    0xC8BE03C338B996B9ULL,
    0xA3002C117DCC7781ULL,
    0x9C66068DE032ED97ULL,
    0xC8BE03C338B996B9ULL,
    0xA3002C117DCC7781ULL,
    0x7601AF296D07C439ULL,
    0x2CD505F2092BB154ULL,
    0xDF,
    0x43,
    0xF8,
    0x99,
    0xFE,
    0xFF,
    0xA5,
    0x31
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseDSalts = {
    {
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
            0x8D32634C6233EE9EULL, 0x871D6A99FD8EE693ULL, 0x5F83E25110A43F5DULL, 0x1026D763C6128DA8ULL, 
            0xC68ED8C434C70E57ULL, 0xE0DEB668FC6005E7ULL, 0x4D0990A125B5385AULL, 0x3052264A7BEF2D44ULL, 
            0xF0A25A62F571322FULL, 0x27828E3A8E325DDEULL, 0x283D60750AFCE37EULL, 0xCB6E2CCED4BD39BDULL, 
            0xFB711826805DF5F7ULL, 0xF4C6FE456B1A83C7ULL, 0xE0DCEAEADCF8C0C3ULL, 0xF5EDF56B6D929002ULL, 
            0x78236B9B41A2C809ULL, 0x1E8879658237EB8BULL, 0x096047571E7EB875ULL, 0x9BEF01A0A73FA983ULL, 
            0x22113339AFF6F43AULL, 0x2EB1125ADEEFB4B7ULL, 0xD451A58FA7134CB0ULL, 0xC0F5D51BF8373A2FULL, 
            0xEFACDBC98E6EC297ULL, 0x289C8D3148420312ULL, 0xA6DB7EBDCC129DF1ULL, 0x8CCF3D4898D26AAFULL, 
            0xF9B31903D92A2A20ULL, 0xEB33444E7FB4260BULL, 0x074661917984C827ULL, 0x0EC1C94C0FF8DF77ULL
        },
        {
            0x5FC2E2FF28AB5664ULL, 0x7440D8DB96024EBEULL, 0x8F528E98B4D946D7ULL, 0xA668CE37412B2911ULL, 
            0xDD9D04893BCF8CCEULL, 0xA6687C5856435648ULL, 0x05D730D6335245E8ULL, 0xA32CC3E5DFC9C890ULL, 
            0x6C7D00CF83F8AE35ULL, 0xE93E1B1C46E643FBULL, 0x54FF14DACB5FB013ULL, 0xB45BCA055F8C97E3ULL, 
            0x879D6E758DDD0FC0ULL, 0x6BEC4B36BD422378ULL, 0x1835D7B8D87954EAULL, 0x2EE90D2BEDE9885EULL, 
            0xC8208FFC37F79A69ULL, 0x38BDC201EA82FCBAULL, 0xBA597D784263A321ULL, 0x7B221AC082C53552ULL, 
            0x4E46429674508847ULL, 0x4AE3EBB9CA1E049EULL, 0x06FD9EB10533EF86ULL, 0x69C9F4367C944B68ULL, 
            0xC45FE1A9A2E80AF4ULL, 0x46280197491764EDULL, 0xC30FA0E0CA15C623ULL, 0xFCFF4D4F6CB54A61ULL, 
            0x4059C3661D4A0E64ULL, 0xBAC745DC63B33A3EULL, 0x1C93A8EB92246842ULL, 0x0008BA62C522EBDFULL
        },
        {
            0xC5561980CDE8E928ULL, 0x66456B6B6B9EF06DULL, 0xC17AC63031877F16ULL, 0xDBAD41651BE83691ULL, 
            0xB85115CFBF1E904FULL, 0xF9213328EDE623A5ULL, 0x75BC558B71C5FEFFULL, 0xC773722416B3B3A7ULL, 
            0x58FFC32F283575D4ULL, 0x8AC538FCD61D4A8CULL, 0x53B2CBB76D8C1FB1ULL, 0xF99DC3E359C9603FULL, 
            0x60C449B31303609DULL, 0x3DA6E0D24DC30113ULL, 0xD6301F013D7BC874ULL, 0xC3093E1FC0A550E5ULL, 
            0x32B370CECB2A96B8ULL, 0x5BA78C06F51F2AD6ULL, 0x39E56833A2D7B701ULL, 0x3AD4A61B617FFC55ULL, 
            0x9B2CA3AE925A2089ULL, 0xD9AB402ED862C77EULL, 0x94B9B7BEBA47DA58ULL, 0xDF82AF8B3CE80157ULL, 
            0xA364EC272E527D44ULL, 0x1A24CCCFDE9167A5ULL, 0x4F38D2A77E34DE96ULL, 0x006FAFA1A15FF9B5ULL, 
            0x22ABC89A83F64095ULL, 0xB18633878CFC653EULL, 0xB67B677EAC60E3F8ULL, 0x273C7A1075D526ECULL
        },
        {
            0x356D54CA9A1A4E4EULL, 0x0FFD4945064D479AULL, 0x08D6ACBF80860945ULL, 0x7E8FEAAAB1B71E43ULL, 
            0x8A7DE3ECF8D0391AULL, 0x0CF3824B3101F6F1ULL, 0x8CA79F68356C188AULL, 0x9C3E111A5E58DA25ULL, 
            0xA52EC296153F3CDEULL, 0x5AC361D7EB77284CULL, 0xCEBBB6E2CF40C233ULL, 0x22AD0376D1B17040ULL, 
            0xCB5DE3291A494428ULL, 0xECB62FB0059B272CULL, 0x1B1F39EC5557D1C6ULL, 0x1EF7BDF2C07799D5ULL, 
            0x7D8CC3A833E66548ULL, 0x5301E285DEAD00E0ULL, 0xBC853517E17EBB6FULL, 0x231AB7670A4E0DC3ULL, 
            0xBA270013CAF08CD3ULL, 0x526128D1C501442DULL, 0xA1DB0031FF32D8BCULL, 0x3AB5B73231765B05ULL, 
            0xC59894E24C7DC872ULL, 0x731E18DC7F5C3BEEULL, 0x23FBCCC813B6AD2CULL, 0x4DB9538352F3FA6CULL, 
            0x2570326AC5C9319EULL, 0xDA757A4EF69FFF1AULL, 0x49B9FCFB242672F7ULL, 0xF5BA97A29F786346ULL
        },
        {
            0x4F2D0A5D00F9C4C9ULL, 0xC323A13CA5BB80AEULL, 0x9E21D57883F396ADULL, 0x677A727C3AAE048BULL, 
            0xD776636AC9EC969CULL, 0x132BD5D0A6233260ULL, 0x1A138509E65A8FC5ULL, 0x14D77E5F6EAD689BULL, 
            0xAA4618B02C431DD9ULL, 0x0D782C1B53080F9EULL, 0x08FB2551FB52E8BCULL, 0xC515E1BE3DF74301ULL, 
            0x6D104E591DEEE949ULL, 0x0DD2A47CE3390E32ULL, 0x74A6640871723689ULL, 0xCD552413E20E521BULL, 
            0x935B930A2197034DULL, 0x72F5DDEA8FDDD8A2ULL, 0xD2390F569277ED18ULL, 0xFD86F453FA7549F7ULL, 
            0x88AC7340C0F7FE1BULL, 0x0C1EFD920A72629BULL, 0x30651B1F33590D20ULL, 0xCED9319136448D2AULL, 
            0xD43461FFE8AAB239ULL, 0x566FE83549D01C95ULL, 0x1728A12C7279B96EULL, 0x705129A1311ED4DBULL, 
            0x8DE688CABBE16A0DULL, 0x5E1C7378CDAA0E9FULL, 0x09D28FFDA59CE8B2ULL, 0x7FC4492B1EE40D33ULL
        }
    },
    {
        {
            0x250331277B72E2CCULL, 0x362F1BD846EE385BULL, 0xEEAA5F82BD29E1CEULL, 0x01921740ACEE7179ULL, 
            0xC3C78F859F3C1288ULL, 0x53801E6C57058D13ULL, 0x68A97FDA9D89E82CULL, 0x7794DCDF29CDF839ULL, 
            0x0C80F4AF1D2E8066ULL, 0xF5F298E1C78D0B93ULL, 0x0E5E1AD1489E776CULL, 0xF5F3EAD7E257944CULL, 
            0x08D2E7DA68F677ECULL, 0x1CC464F4467A5A7AULL, 0xC2F3213FF866D0C2ULL, 0x49D006376039EDA6ULL, 
            0x252B28104A2CA9BDULL, 0x7145A596D9B42153ULL, 0xEFC4F3990D9AE20DULL, 0x5BBCE136DBC7BC59ULL, 
            0x2CF48AC4DC52ED98ULL, 0x072B6D844CFE7434ULL, 0x8CBD4FE23D702A11ULL, 0x89B7593319120243ULL, 
            0xBD7323ACB53E0278ULL, 0x0FCFFB79BA9194AAULL, 0xD4219BE496683AE6ULL, 0xB2C9D716F17EB858ULL, 
            0xAE7F9312237E6E91ULL, 0xDBFE91FF124C7897ULL, 0x974289B724BDFF2FULL, 0xBAB7D341399F80EDULL
        },
        {
            0x511EDE1717A14A9AULL, 0xB9AC42035F2B4A83ULL, 0xC5F21AA68B825133ULL, 0xCB41E326F9725546ULL, 
            0xC7C6965FC2B62A5BULL, 0xBA9954F8E5DAF6D2ULL, 0xA3D1D0112B96750CULL, 0x4153E1E9643E7747ULL, 
            0x40210FA653F61F36ULL, 0xFA1643409C4E2833ULL, 0x49E9A0C77C51A9D2ULL, 0xBDA6265B1C962430ULL, 
            0x8E789110B3F513EDULL, 0x719B330D42D7CF7DULL, 0x3963306C4B355900ULL, 0x7790146B84D18872ULL, 
            0xC34A416E28C12F0CULL, 0x338AE8F1A3B29459ULL, 0x3FB574D7A3DEF720ULL, 0xA5413690F7359867ULL, 
            0xE8599DC55ACC51ACULL, 0x73BD4E7497140A8FULL, 0x6582FC34E646ACF6ULL, 0x7392788CAD7196D4ULL, 
            0x3BF9EA688AE384FFULL, 0x5EA5C0B691FDE873ULL, 0xCE144ED64B719681ULL, 0xF0C5923A30E9B363ULL, 
            0x0E42D9A11A26AE83ULL, 0xA2870146ABB94DCEULL, 0x47464524ECC71D8DULL, 0xC05A08725AE38AE7ULL
        },
        {
            0xC0DBA667170CAB14ULL, 0x4367D4C6F5FA7029ULL, 0x2BE25D2294739623ULL, 0x41F890B8BA7A28ADULL, 
            0x704DEB7924A705A8ULL, 0xD81A0E0DC91D0D56ULL, 0xA92F525A26615F94ULL, 0x32A914354A2B3FA6ULL, 
            0xEEAA8AD8812A453DULL, 0x91FCA784A4131109ULL, 0xECED780091180BCCULL, 0xDE22903FB94C4B84ULL, 
            0x4B6748DA6790C583ULL, 0xF3EE667A02D9AA76ULL, 0x1E0DB9962E9B2655ULL, 0xE5FA2064E0B7F5A7ULL, 
            0x4F5AED3CE290CDEFULL, 0x49183302D47528DBULL, 0xFAB3B735DB7FB4E3ULL, 0x6EE52F463FE3AEF1ULL, 
            0x54002F5C3D85D8D1ULL, 0xF7699331C1245342ULL, 0x889A8FE21E3D126FULL, 0xE4D81280DE5D83AEULL, 
            0xBE51FC62E7707E33ULL, 0x25B33E7CA5F1AFB4ULL, 0xAA988D571EC63445ULL, 0x363939D90A0E577AULL, 
            0xDFAB08E4AD538E25ULL, 0x677B70DEF81F8744ULL, 0x787BC0658AFF2F65ULL, 0xAEE02A79E6B0A23DULL
        },
        {
            0xDC095B519EC453B8ULL, 0xBA7712B5DEF056F8ULL, 0x044623BCE73890F0ULL, 0xC4EA8734B6FE9B76ULL, 
            0x90F7E1824C20694EULL, 0x7BF525A1819B43BAULL, 0x5B7C52DF26E5E329ULL, 0x56FAF0F2E46D60F5ULL, 
            0x733EF2DCA48CB047ULL, 0xC16EC0DD97EE67DAULL, 0xD842FA7AADAEC20EULL, 0x17AD0813CA9DA79FULL, 
            0x62C5B3F31EFC27B6ULL, 0x42DA16D6C9A67CF5ULL, 0xEFD2A4B432DDECF4ULL, 0xEE98E0FABC236367ULL, 
            0xC886DA6EC079D650ULL, 0x79828ABBE1705D46ULL, 0x594F064D44809F20ULL, 0xCF837BF14FA5A90FULL, 
            0x7F9EABE62F6DC36FULL, 0xD5D2CD8A0C07960FULL, 0xF7FA0A5CDD20FC92ULL, 0x080CBD3BCAF28581ULL, 
            0x7FEEF37326914F3AULL, 0xFEAAA77D74E38FCFULL, 0x05C78AC7F98E1796ULL, 0x04160EB238CE7AE9ULL, 
            0x38267861471E5565ULL, 0xB12A16592DBC6423ULL, 0x562EE4458F915C01ULL, 0x458D1EEE5F8383DDULL
        },
        {
            0x8A52E716916E947CULL, 0x19C94D13AF4E9F37ULL, 0xD41222528538005DULL, 0xBE5DB6713152D3EAULL, 
            0xA227E04A50D60D94ULL, 0xD39B81EECA262D49ULL, 0xAE9AB927A5A93986ULL, 0xE0D0512EB6FFF4B0ULL, 
            0x3B0A779E0BE86EC5ULL, 0x73629E256D821F14ULL, 0x6364E3F6F5616DA4ULL, 0xDBD7E810D1FCD922ULL, 
            0xFDF7B43EA9FB9839ULL, 0x7B3607B37DC10870ULL, 0x290C2E2AFD5C3166ULL, 0x26D0449DC83095B3ULL, 
            0x90FDB7A43F33DA9FULL, 0x30B4631035D03E5BULL, 0x9AAC374B5893573CULL, 0x04280935838A1312ULL, 
            0xE26CA768A968E915ULL, 0x2989B0B70BEF863BULL, 0x3491832443C1CC3AULL, 0x4DD738A5F5B384CDULL, 
            0x29FC22F5AE4F8FCFULL, 0x45BFB724816FBFA9ULL, 0x317E4EE1CB7F2A56ULL, 0x84F3EC3F2B7011B7ULL, 
            0x25FF66A28AB61286ULL, 0x95F8D782F9605BBDULL, 0x179A60B2B2CF3D87ULL, 0x38849C08D32DC8C4ULL
        },
        {
            0xFDAEC0B2AA477613ULL, 0x4295C28C1CA30F3CULL, 0x9BA10D61A79B32FBULL, 0x3E9222B8E63F5C4EULL, 
            0xF9ADEA8E7DDF71C5ULL, 0x9ABD03ACFFC836C0ULL, 0x01A40595D560D9B6ULL, 0xF14CFB1DB28EFC4BULL, 
            0x95A427DA2A9C236AULL, 0x91FE5B7F5D5D8BDCULL, 0x0FF9DACE5D95941DULL, 0xFB97E64E06208B0FULL, 
            0xA0CC896689D77708ULL, 0xF0025EF0F66BF6FAULL, 0x2CC45BB7EA70CF35ULL, 0xCC6C68F581207835ULL, 
            0x56FCC5B9A28BA686ULL, 0x3279807437000201ULL, 0x0C1CD527A0B70745ULL, 0x37C3890FAEBE6AB7ULL, 
            0x42825BACCC247449ULL, 0xCD78EF59D8A01962ULL, 0x557226A37B4EB87CULL, 0x442490C43C8327BCULL, 
            0xA6E95C59E66E3EFEULL, 0x44302BFCFEAF4C43ULL, 0xACE4DDE77BAB1DD3ULL, 0xF9A42724BADC1D27ULL, 
            0xD98F0604E80B97DDULL, 0x8076725087579B58ULL, 0x384C440C90C8B458ULL, 0x9930D9D151CEE243ULL
        }
    },
    {
        {
            0x52CE24C92A20710AULL, 0x2E1C7C0864C63AC7ULL, 0x6A3EB865F86D72E8ULL, 0x92F2709DE7CA2548ULL, 
            0x7FD8F2A6F1E2058DULL, 0xAD2FD8C8B11A9F2DULL, 0x9B1FAB46D15598DBULL, 0x258444AE325369E7ULL, 
            0xC423EC70B98C6B02ULL, 0xC08E2870319C22DBULL, 0x80747BB5644091B9ULL, 0x41B243C073BFAA84ULL, 
            0x3CEA7FFF3F987290ULL, 0x076E198D9BCE982AULL, 0xC5C836A3FEAA179AULL, 0x636B6AD35D8BD461ULL, 
            0x9B008DB9DCC88A94ULL, 0x0779E2E954CE77F9ULL, 0xD97FFFE0EBE68EABULL, 0x2A419A120ACF5F7EULL, 
            0xF3EBFF7E781F5D01ULL, 0x3659779044FB151FULL, 0x8EF5B46588B3660CULL, 0xFDD6BED37536A7C1ULL, 
            0x2B1CE7A859C941E1ULL, 0x6A44B0A4105C0E09ULL, 0x9599CBD3E683722BULL, 0x0F70ECFB2DC3DD67ULL, 
            0x361A6521DBC32811ULL, 0xB45031C7F598EC69ULL, 0xED254005448784F9ULL, 0x096AC2E25A9964F0ULL
        },
        {
            0xC6E58330C92EF944ULL, 0x61D185F0C7EBDBCBULL, 0xEBFACFE1204DAC47ULL, 0x09EBD79FF2244055ULL, 
            0x9BAEF8706BBD8B37ULL, 0xFF85DA88BBA1890EULL, 0x11B634ED611854B1ULL, 0xF6612B69D95AC992ULL, 
            0x98A8DB8BFCC768BCULL, 0x2719559089F2D3D4ULL, 0x79083F36D37AD252ULL, 0xCD2BC6E3885A6F7BULL, 
            0x202417D26F8E75AFULL, 0x78D90BBFCC796094ULL, 0xE7BB1B0563F80CCCULL, 0x5C7932FC743F3477ULL, 
            0x986294DDD49A03B4ULL, 0xD59927EAF07482F3ULL, 0xE94C95E432D5998FULL, 0xB5771F2AF67A3E46ULL, 
            0xB0FA8C04C0E29890ULL, 0x6C5F63A79BBE7FCEULL, 0x403AB2F8AC887E0AULL, 0x15A1A8D21DBECA62ULL, 
            0xB91C452C0639977DULL, 0x352E4EFBAD4B2205ULL, 0xD01C7F692F3153ECULL, 0x580476CCA8FBDC34ULL, 
            0x6B82EC5349416D8AULL, 0x37C77DCE3F20EDA6ULL, 0x8F1D65CC9DF100B9ULL, 0xE994E877C0FED4CCULL
        },
        {
            0x61EAA84EACAF340FULL, 0x70687767FF3EEA9EULL, 0x490FE519710EE168ULL, 0x26D9FE3E252B5FEBULL, 
            0x431FB9B5C137572FULL, 0x96018C2A45A5B00DULL, 0xC4CCF7FE03B75E7FULL, 0x33E6D08EB8927B50ULL, 
            0xB1A2B3E5879A6EDAULL, 0xAD3510D568C7F5F0ULL, 0x91B747AA8C54CEF7ULL, 0x4D52A8B6C192EED8ULL, 
            0xA111C0AB0D0D6C37ULL, 0x3E70A177F5184CEBULL, 0xF8F0EBD94853BA79ULL, 0x0183AEE6E4447311ULL, 
            0x313C748ECB2590AEULL, 0x25910D59BBD3CE8CULL, 0x998FA99A4A97D2B4ULL, 0x9BE3CD43F5F14722ULL, 
            0x1201DA962E2ABFD2ULL, 0x144947EBB12FB92DULL, 0x311AA498C6A5CDD8ULL, 0xB7F202AF59F04F5FULL, 
            0xB253E7A4BD53970CULL, 0xF0A77F834386F6E8ULL, 0x2F78E863F922C053ULL, 0xE81C94BFDF3FB9AEULL, 
            0xB0AF10C95F8D6056ULL, 0x2387FA2DA5685EEDULL, 0x729C6784BC6A523BULL, 0x9D0BA64601817C8FULL
        },
        {
            0xD1E904CF89097F5CULL, 0x6FA6DAF7A3725FB2ULL, 0x1B6F6655E8259008ULL, 0xD186089C89DB574DULL, 
            0x54DC540E1A0C8073ULL, 0x63FE1D39987B4FAEULL, 0xA33E0E1B677F23B1ULL, 0x28D4BEE211332EECULL, 
            0xF2DC320033EFB16EULL, 0xC6243AEDAB27446CULL, 0xACD808C335F4D329ULL, 0xF7F9DC9002D3B435ULL, 
            0xEBDD26F025B9C75BULL, 0xC1F7C92D8CBC8215ULL, 0x96D9008F0D702E4CULL, 0x73CB99A8A01BE686ULL, 
            0xD1AA5EC1A4D0C3B7ULL, 0x1448EBB3C0A02D35ULL, 0x763D5EDD11FF8172ULL, 0xD25F9E7AE8F22EC5ULL, 
            0x1104F3A7BF48ED0DULL, 0x269399C0C5DF3A94ULL, 0x5C6F26C65B19AD50ULL, 0xCBEBF6FB7EE68991ULL, 
            0x2AD73B7157F65780ULL, 0x9A5216500A35D21AULL, 0xE7A56DE2BF469A2EULL, 0xD402FE4F2A0539FEULL, 
            0xB2162390F0A99278ULL, 0x35E4A3E0482AE055ULL, 0xDE3033517BE36079ULL, 0x77C08905E8AE1C9CULL
        },
        {
            0x77C2A6185231EB0FULL, 0x35899698B4FC4F87ULL, 0xF488BB666A957484ULL, 0x15770969A048C61CULL, 
            0x84F4316C6DF4682EULL, 0x737D0C72E897CE2CULL, 0xFE12C64794A4B9EDULL, 0x8A012078D10EF122ULL, 
            0x9C475D26FDAE5CA9ULL, 0xFD0E7F18EFF3CEE4ULL, 0xB90C1305B57CD578ULL, 0x5850C84937D06EB0ULL, 
            0xF163C3706D40746CULL, 0x8A12B1F492903D38ULL, 0x5F565FFC2A43DD3DULL, 0xBC69AA7B69483A7BULL, 
            0x21A59EF52B2265AEULL, 0x6D8C4179E1B94016ULL, 0x23AEDFB102C2778FULL, 0xD34C139D9EF178E6ULL, 
            0xF20DD5D2F4E19D0AULL, 0x53243B779932BE1BULL, 0xADCC005C647BE694ULL, 0xA5F519583960E328ULL, 
            0xE9B74340B30DA2FDULL, 0x64084CD015FB7D2DULL, 0xAF1A7BACFC26B3F6ULL, 0x1DCE15543A615E82ULL, 
            0x9C8565C09C3274F5ULL, 0x8A977526694848EEULL, 0xC6871B0DA5920A64ULL, 0xDF59CC9C9222433CULL
        },
        {
            0x8507B00442AF2E3BULL, 0xD6131FCA822C046BULL, 0x6146E152C49D6B5FULL, 0x66629E7A6244D737ULL, 
            0x25ECCD25316502B2ULL, 0xE6FB844602788BE9ULL, 0x9BC7B8CE5D736BD6ULL, 0x906AAE598F51BBA0ULL, 
            0xC0D8FCF64BB4CCD2ULL, 0x638892B050311957ULL, 0xB9FB779D573C9F9BULL, 0x6B1F803C11BA0E21ULL, 
            0x4545C302AF332C8CULL, 0xF2E3AFEDAC1370F4ULL, 0x2D667D7C09A0F817ULL, 0xFDC0F302B3326CBBULL, 
            0x3D306814F300F561ULL, 0x6B726C753E05F804ULL, 0x97B53D1DFFA22B47ULL, 0xF4A8E56E368D45F2ULL, 
            0x51CE84566D9ADACAULL, 0x83EE6279FA0CD129ULL, 0xCEDEB03FF2C33970ULL, 0x7154ACB2DB91E861ULL, 
            0x475B4D04E93F7753ULL, 0x68273AD620AF1CF6ULL, 0xCD6A45C4E6435FAFULL, 0x7E69B218D1DD84A8ULL, 
            0x914A23C31AD793C2ULL, 0x290D9B1A91665CE7ULL, 0xDF41E7D81B1ACA2EULL, 0xE108170ED7BC28C5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseDConstants = {
    0x4B7D1332A0D80728ULL,
    0xD93223B9F71BA811ULL,
    0xCAB2B33427FC676AULL,
    0x4B7D1332A0D80728ULL,
    0xD93223B9F71BA811ULL,
    0xCAB2B33427FC676AULL,
    0x7DDBAA63F38E5B2DULL,
    0xCD9E1A2DB85DABCDULL,
    0xA7,
    0xBF,
    0xD7,
    0xDD,
    0xA5,
    0xAA,
    0x09,
    0x70
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseESalts = {
    {
        {
            0xC66D57DD194F40FDULL, 0x7C9006076D343F21ULL, 0xE2F2102A9A7C9568ULL, 0x7A4029286C265BB0ULL, 
            0xFA7E9ED67292C6CAULL, 0x68E1C433B7733734ULL, 0x6B0AACBB4BC40995ULL, 0x6D3FFA0385CFF78FULL, 
            0x83E5E9458089478BULL, 0x573A7AACD8C4415FULL, 0xC0A43F0967637B24ULL, 0xF9F59712DAB09237ULL, 
            0xE57C2BEF83E9DB73ULL, 0x075C95D699D73CF3ULL, 0x2A54C6178B70237DULL, 0xC04B994FFB236165ULL, 
            0x35A1E9B99C053BBDULL, 0xC5FBD9088C95E292ULL, 0xCAA7267E309A3AC5ULL, 0x1CCB9BE93FA52BF1ULL, 
            0xFD8E4E4EC227E290ULL, 0x8CB573D4F3EF875CULL, 0x4A9A06DB889CA1C1ULL, 0xF05A6F5CF3E2BC6FULL, 
            0x07827F1C2331AF41ULL, 0x236CDB94B913F378ULL, 0xA3EFB398EB786723ULL, 0x3EAB07E4A9148B67ULL, 
            0x1490AD0755B051E4ULL, 0x642EF387247F5B9CULL, 0xB1F3FA1BDDBA9AB9ULL, 0x45FDCDA962A0FE16ULL
        },
        {
            0x8B597F6782453B9BULL, 0x0E44C32BAA4BCFFFULL, 0xCEF48C2A6112F583ULL, 0xB2CA11F2BB68B92DULL, 
            0x1F298A659E08305FULL, 0xB50A0A0092B497ABULL, 0xE479BB489FFB569FULL, 0x7FD5DB0AA1D62D0CULL, 
            0x1FF9583C664106DCULL, 0xE194213C21325C2BULL, 0x705095100A3238C8ULL, 0xE1C248E3317499A6ULL, 
            0x22A4F994C63E1487ULL, 0xA0773E7C05EB93B2ULL, 0x30F60FB3E20C68E6ULL, 0x6310F961EAA06966ULL, 
            0xDA0E4C31B544AA23ULL, 0xD886AF01CFD21B29ULL, 0xB486F2A19A02D76EULL, 0x3CAA5E1629A8631AULL, 
            0xB1CA6B66F6EECA2BULL, 0x8EB212B9CED3F4C4ULL, 0xF64E687C6894B3FCULL, 0x7A4F0E7AF8A5FFDBULL, 
            0xC20960834D2EA043ULL, 0x1715F0EC5FC769F7ULL, 0x8E29698E3973E3FFULL, 0xC86D552CB67ABCA2ULL, 
            0x3ABD17452A615E5EULL, 0xC0548EFD2EB3289DULL, 0xCDDCAEA78FB9BEE3ULL, 0x8D2AA5C04C6AADCAULL
        },
        {
            0xD8A6DEE0677E43A3ULL, 0x8EB2BD657E9422EFULL, 0xA28DFF15FA128690ULL, 0xDDF47F3C1FCCFD60ULL, 
            0xFA6E1C452413A1C1ULL, 0x777DD375F0199A8DULL, 0x2FE75E53CFB4B464ULL, 0x5AA068339EFB67DEULL, 
            0xE1018AFE0DEB29B7ULL, 0x926B07B1862E8C4BULL, 0x4404F22E2C907D58ULL, 0x8B416C9117CF888FULL, 
            0x9BFCE34FF60C9996ULL, 0xF66302A6094BCFBDULL, 0xA00CF42AEC6C6C53ULL, 0xCB27C884445D1848ULL, 
            0x93556A6E69E9A0F7ULL, 0xF1A1516B51865F3BULL, 0xE4262FBF19B8A8ACULL, 0x7082645C3BB6FF41ULL, 
            0x007697C1E3976979ULL, 0x930410AB62EE5F1BULL, 0x991C39CCC3705EAFULL, 0xA5645AC090F7DD7CULL, 
            0x56D72F602C16B3DEULL, 0xBABA5292837CF79BULL, 0xC59D80581DB0B81CULL, 0x4D6C1B8E4D4E3CE4ULL, 
            0x599A4450E0C028A6ULL, 0x9D82D30BBB5CB180ULL, 0x642797677549E053ULL, 0x89B6F7E993140BB3ULL
        },
        {
            0xC1D29FFEC4474B83ULL, 0xAD418B4ED861B926ULL, 0xEB6B625D5B88AF87ULL, 0xF951D1AA1654EB04ULL, 
            0xDA6E2C08BF5CAEF9ULL, 0x836F802E2BF9C3C8ULL, 0x888135F5EF122B6BULL, 0xE07D1A57D0FCF337ULL, 
            0x2BCDCAFC2B0FF2C1ULL, 0xFF125EF5E88C40A0ULL, 0x612D1C9E9913A531ULL, 0x0B0A351AEC03D864ULL, 
            0xCA88659DDFF3B83DULL, 0x0689BA4DDE2C32DCULL, 0xAE67742376640A0EULL, 0x6BC5AC9CB6572B52ULL, 
            0x679B1C64191FCC73ULL, 0xEE852DF35B7D9A84ULL, 0xA10B7115D320905FULL, 0x355DAF006BB51B0FULL, 
            0xE225255F3466BAE5ULL, 0x450F180FD17D0561ULL, 0x1AB9AA9CC204BB32ULL, 0x825F68E161395FE6ULL, 
            0xD13C63A0D825762CULL, 0x0E1B333A27E749DEULL, 0x556E62711BED6DBFULL, 0xB6B653F62569CD84ULL, 
            0x55C24EC6213ACF69ULL, 0x74F80151E5E134B8ULL, 0xA095BFE104701354ULL, 0x47EEA0C4BE031F6DULL
        },
        {
            0xBABC7CEEB2552005ULL, 0x1CF48DD212000F4DULL, 0xC62B15EA2F38A0BCULL, 0xB81B0F5506EB5614ULL, 
            0x149DBCD2376CFAEFULL, 0xCA235FBD4C7A1971ULL, 0xE132D3878DD465A5ULL, 0xFC2C0376F24387D9ULL, 
            0xDF589D393B26699CULL, 0x1E49FAC4497AC224ULL, 0x4DA7AF02C660C50AULL, 0xE975886D8C70102DULL, 
            0xD11C5D34A0BE1E85ULL, 0x2F7B363549611F34ULL, 0xC8E5E16A71E4AA15ULL, 0x12CE77A9878D3859ULL, 
            0x220BAFFFDB59980BULL, 0xDD381DCC23CB61C0ULL, 0xC0FF8658F9654526ULL, 0xF351F87EF6E5259CULL, 
            0xEDAE0C44432BCC26ULL, 0xE8477C05F38D804EULL, 0x66B17FCD5AF11270ULL, 0x550AE6D8A9493D50ULL, 
            0x156FF5828A5A8782ULL, 0x1A42FC412A577AF2ULL, 0xB3F525D32134FBC9ULL, 0xE738F22C91008838ULL, 
            0x620BA04879C6AC9CULL, 0x398E3F8070336D62ULL, 0x2CF2D79A32CFE562ULL, 0x7F4DFDC463B7D72AULL
        },
        {
            0x8500468FB994F5E8ULL, 0xDE1F64B0A82E95E2ULL, 0x8E2F92881C42EA48ULL, 0x7335A38F2E35436AULL, 
            0x1380AA98F1387112ULL, 0x37C018C30050BEABULL, 0x180ED7EAA72EB72AULL, 0x847E90FAE8083A4BULL, 
            0x6AE8FC1EB0A3DF83ULL, 0xDF3E820D765CACF4ULL, 0x54CDC676566112DAULL, 0x63F79E24C51CCC16ULL, 
            0xD6D492A159A676E3ULL, 0x7FB1DD3C49980C94ULL, 0x70F3817F0B90ADA9ULL, 0x2FDB1AFD6F432B79ULL, 
            0x2F5ECEE65B566D83ULL, 0x86CAA4F1AFEEA36DULL, 0x872AA225FA52FDC9ULL, 0xD50EFCD65000580AULL, 
            0xC9D8420F3359ABE3ULL, 0x94689B7BF2A914B8ULL, 0x2400657E392CA8A4ULL, 0x4C34094BF8BA09B0ULL, 
            0x4D4FC52FB01B71BDULL, 0xD8E689589A185735ULL, 0x0B711768DC12FCC1ULL, 0x48DC433601E9A27EULL, 
            0xF5F3308DDAC4B1FAULL, 0x4D8EBF0BF3B832F4ULL, 0x3F6F991C21636A7DULL, 0x68574921351E2746ULL
        }
    },
    {
        {
            0xBC7FDBBD12A2E189ULL, 0xB077FB4D72B53CD8ULL, 0xCD1995FBEA50B7CAULL, 0x2F9C5EE47CF0E527ULL, 
            0xE62F0F144145BBCAULL, 0x6F2AC3F0FAC1FD9BULL, 0x3CC5BC3D820FC937ULL, 0xABEEB7BEF661C724ULL, 
            0xDCB90F58044C658BULL, 0x8E4038F435A6931BULL, 0x038E3147D3D69D06ULL, 0xD66167366293CCFCULL, 
            0x07FE36F9DCC0185FULL, 0xBDDB0B18D6B83893ULL, 0x8FE47111BFAF57F2ULL, 0x1059DA495444F2B4ULL, 
            0xC1B89F87A44F3181ULL, 0xD5FEB8BD2D6747F0ULL, 0x11FFD1729656A37CULL, 0x7B1EE356DE160D7BULL, 
            0x32BB72CA4E9493A9ULL, 0x364279FDB5CD642AULL, 0x7352EBA05EBBFE71ULL, 0x91DEE3DFA715A6BAULL, 
            0x593DE3B1755AAFCFULL, 0x5E63E01D5AC1F888ULL, 0xBC0D021F8C6077C6ULL, 0xA700649C0AE4917AULL, 
            0x5054E4A462D96687ULL, 0xC1F89890E7FE7D2BULL, 0x84DBDFD0391EB11BULL, 0xA588D13872EC0951ULL
        },
        {
            0x445C58F644E7E149ULL, 0x91EEA44E7DB7CDE5ULL, 0x89BAA433D1DE2E2FULL, 0x6F1A0AB14B7BBBDAULL, 
            0x3AAFFD5B8A65236BULL, 0x5FE3AFDFB5A4EA13ULL, 0x6941384B5AC92D0AULL, 0xFC813B02EF7ECB48ULL, 
            0xD7923129DF2DE239ULL, 0x2EF925AE167ED7ADULL, 0x115BCFD355C48AF6ULL, 0xF6E8C222C3DEA3ECULL, 
            0xD66B68DDC9878FEDULL, 0xC466754ECC6F003FULL, 0x01447273E013C6BAULL, 0x18A1D6057FC398CAULL, 
            0x39C67320C380EAC5ULL, 0x60C8D716F8E20D88ULL, 0x77BEF25BCCCC09D0ULL, 0x9287F83333054326ULL, 
            0x72564C5E57DEF201ULL, 0xD4A46BECD3AE3322ULL, 0x29925C0FA2C36939ULL, 0xB9DF5147FFFD94C2ULL, 
            0x052D5CCC1CF1B347ULL, 0x125ED7B6F108006FULL, 0x58E93B9DFF16E370ULL, 0x9FB8619686E66F32ULL, 
            0x35988BF629242B1BULL, 0xB8CCC7481355B7B7ULL, 0x8CD30793E38A35C4ULL, 0xAC653A331778C79CULL
        },
        {
            0xF254B45D3EEAB728ULL, 0x6033AB05FAE09EABULL, 0x37C8F409BF45AF3CULL, 0xCDEEA0715CD3F034ULL, 
            0x2D712126277878A1ULL, 0x20F38E38083AF50BULL, 0x9C2887D147E39E67ULL, 0x2E407FB81F8ECD0AULL, 
            0xB9E39808292D820FULL, 0x084399695133BAA3ULL, 0x052EDEB7428EFF70ULL, 0xD5C3F7EDA7E95DB8ULL, 
            0xB45452F5A58EC049ULL, 0xBADC782C8C2288F4ULL, 0x5F306B670DBD6707ULL, 0xD1B87B08C3086802ULL, 
            0xBA17335B7D4F688FULL, 0x52CB022C40468335ULL, 0xDB25D80C5A004643ULL, 0xE55C9C1ABE9DD675ULL, 
            0x06F96B9D74F9F9B7ULL, 0x25EAFF2712496553ULL, 0xC8B7443A42ED2EF6ULL, 0x4A3A069F62F40B53ULL, 
            0x4866EB512418F9E4ULL, 0x461D65322D6A796DULL, 0xF27EC4455464C2DEULL, 0xF0329D1C8C5DB5F7ULL, 
            0xCA399CBCA8D55ED3ULL, 0xF03A7CBA82173C4CULL, 0x2BDCDF54127755BBULL, 0x8728789ED9C9E23BULL
        },
        {
            0x3A2E1B84626A5BBCULL, 0xBA127125CFF8A8CAULL, 0xBACE94E6AA2C1040ULL, 0xC4CB3A9D8A57159FULL, 
            0x5B2E1F74D81061D9ULL, 0xCDCACC040D60891EULL, 0x52A98E1CC0140D98ULL, 0xCD98C7A0CA531B64ULL, 
            0xC43042624D2112CCULL, 0xE36D50D153A6D6DFULL, 0x05388BB1FF479ECBULL, 0xD3B3C3E4BE7DD4C0ULL, 
            0xE0F5D5C6269CC487ULL, 0x202610E56CC40453ULL, 0xF926D1A555474AC4ULL, 0xA7069D1701B7DF19ULL, 
            0xF90067167664EE3CULL, 0x6F83340F4D50B032ULL, 0x291C6C901BE09109ULL, 0x733EAA2975501657ULL, 
            0xC81A507AF7EDE670ULL, 0x4BDDBE5F6EF65F15ULL, 0xB4EBB427A9154FC2ULL, 0x9026C0B7331C4624ULL, 
            0xEBEA2B5D40B524A7ULL, 0x9C655DC1B7341395ULL, 0xBDE734E36AEC8AA7ULL, 0xCCD6EC9741888F87ULL, 
            0xADCA38F177E5288AULL, 0x081C3FF157C2BB26ULL, 0xFAF4214093618BA5ULL, 0x570F4261A683301AULL
        },
        {
            0x4B783603972BE7F9ULL, 0xAE18191669C035E5ULL, 0x566B8A4608088951ULL, 0xC0B25C5F9DCF6BD0ULL, 
            0x36F161A7B582F92DULL, 0x6D40025BAAD65E5DULL, 0x044B354F576E2F14ULL, 0x3F68D5FA5815261BULL, 
            0x67B11A06D9F52D91ULL, 0xD74C1C36E9B8AFCEULL, 0x949BF604D9C3CCD3ULL, 0x6F9817FB7AF72774ULL, 
            0x55A56F14455DDD96ULL, 0xE4835586601AE941ULL, 0x7F26D82B92D0993CULL, 0xDB7CA6C31200A806ULL, 
            0x5681A5B9892D133DULL, 0x5245FC5FB5592A9BULL, 0x5211FAB300B13D9AULL, 0x99121C2061AD84E6ULL, 
            0xFDA85FD2066DA928ULL, 0x366BD97A35719D7EULL, 0xE431055EB6DED97AULL, 0x14169FCF19656C60ULL, 
            0xD23C65C1BBAA2426ULL, 0xE466F225E6CC6B76ULL, 0x2E05AFBE779022C0ULL, 0x1ED0320285532D04ULL, 
            0x82CDC08954DB6A7EULL, 0xCE11B7D548A696E4ULL, 0x7004935688F52F44ULL, 0x4E96231D4F8F3C6DULL
        },
        {
            0x32F29702BB22F13DULL, 0x5466FE5DB0F3279FULL, 0xA2591B62FF7299D9ULL, 0x9CDFF5C6D989D608ULL, 
            0x85B65FCE229A2AC6ULL, 0xDA2B2CC433459D95ULL, 0xDC0F3AAFB5B76D46ULL, 0x7A8B38DD0920A7FFULL, 
            0x720F5B5A89A02E19ULL, 0x1F78CC550D91D3BDULL, 0x2AAE890615F4C629ULL, 0x2EA9ABE586C506F8ULL, 
            0x8415B7E099D1D5CAULL, 0x543E008B934B024DULL, 0xE9008BC92F7ED96EULL, 0xD2B028F6ADDE6BACULL, 
            0x5B7E8CB54D56887DULL, 0xC21308FEAFC7173CULL, 0x62F728233E989EBBULL, 0x3B3FECBBDD07BFD3ULL, 
            0x20C92A270F5B2810ULL, 0x1036F050DE4EBC48ULL, 0xC84F7CF9AA4E23F4ULL, 0xBD3F30C63C942C5CULL, 
            0x45819717D53C634DULL, 0x60367CB9871DD8A8ULL, 0x1A57BE30FFC0EFD6ULL, 0x4C552411579285CFULL, 
            0xD131F41CD3EFEE5DULL, 0x3105497ECF4BF1E4ULL, 0x0510ADB5EA9CC8ABULL, 0x253D7D8364CCF01BULL
        }
    },
    {
        {
            0x6748AFF9E2DFA6B4ULL, 0x287FD33A8135323DULL, 0xB50159FE05F9B1F3ULL, 0x0F8F0AFFB8494F75ULL, 
            0xFF99997E9998EF08ULL, 0xF41EA6CA34738546ULL, 0x39BF214666BACCE3ULL, 0x230FB9097F1A520CULL, 
            0x099E6D42755A25ABULL, 0x8017B1B2EC4B02CBULL, 0xE950552556D767CEULL, 0xD9863EDEDFBB8B0FULL, 
            0x981E0DD80D2F8B28ULL, 0x300586A0DC750D99ULL, 0x81BD378AC077A010ULL, 0x767301EC17D07299ULL, 
            0x9D0D8D31A6A8CD07ULL, 0x83F3C324FC569334ULL, 0x73B94E03E633D6E5ULL, 0xA018F3AD7D65643EULL, 
            0xD16AA92951AED4BCULL, 0x12465A11AD003B4DULL, 0xCA210AA50258F7FFULL, 0x991A95032379CD90ULL, 
            0xB50DAE8A2E53D078ULL, 0x28F08B532102F07FULL, 0xD5AF7C7A6AE341D4ULL, 0x87CFE969712165B0ULL, 
            0x6EA6B96253E42CCDULL, 0x02E241E58B0BA229ULL, 0xA5804F9DC0BB782FULL, 0x834FAC6F73DB1A1BULL
        },
        {
            0x2C8D46CACA166D9FULL, 0x7F806A38CC17F7FFULL, 0x0E1196597686F637ULL, 0xC7BE46FEA7EB8B27ULL, 
            0x86573F1BC33E7F33ULL, 0xBEEE939B49DF1A08ULL, 0x866FC60DE011E47AULL, 0xA1C8A55E45AC3733ULL, 
            0x9E17F14D6FA9699FULL, 0xDCE6594665D9F539ULL, 0xBA7E95138E54E279ULL, 0x69E8F9537112358EULL, 
            0x1E9E55E87548D33FULL, 0x6212E314128992F8ULL, 0x3CBB58B056671BB4ULL, 0x05EEC1267EAC6820ULL, 
            0xFC6AF3E7D962ED10ULL, 0x111B4F806BD9A5D1ULL, 0xD69D140A906CCE2FULL, 0x8B5D14C677F1522EULL, 
            0x23EF49F40D192565ULL, 0xBCF44EDF7E513757ULL, 0x74D14B58317EEF42ULL, 0xB287AF1E24788732ULL, 
            0xEE013D5A81D516B4ULL, 0x50A3FFDE7C0C100CULL, 0xF95A91BAF2EF25A8ULL, 0xD833998F99FE3204ULL, 
            0xF4D61FD79245E003ULL, 0x26A6A69CA374BBA5ULL, 0x46747C164DCFBA9EULL, 0x639905BD3FE5EFADULL
        },
        {
            0x9318FABA49DFF37AULL, 0x6ED316E5DC0009BFULL, 0xDB5366FCA802337DULL, 0x200A4D4D3F98A04EULL, 
            0x4B2159B227231078ULL, 0x9743C3C28DBB3B81ULL, 0xD6A57A2A5B6D7265ULL, 0xA7DEEF850A2DFAB5ULL, 
            0x3D13C5CB6B70D2CDULL, 0x98DE804A07738528ULL, 0xF3670D7FBD3502ADULL, 0xE1FDDF0E6D29C0D0ULL, 
            0x8AC43EF3000CEFE3ULL, 0x4B1F9B9976B41EE0ULL, 0x341BA75247C7D15AULL, 0xFB7DBCFD1207A133ULL, 
            0xB9EF8F78E266E131ULL, 0x6AB0DCA40D163183ULL, 0x9E639A7EFC733BBEULL, 0xB42495BCE7CD28AEULL, 
            0xDB1649FC1A8908A2ULL, 0x9CD9A65AC3B78963ULL, 0x39244E0389BAB8EAULL, 0x0ABC3E7760C361E3ULL, 
            0x57CC5CBCE13E4D3FULL, 0xBE89D18DC8A044E8ULL, 0x136317E5EB0519B7ULL, 0x08226EFEDEEB643EULL, 
            0xB25A633D3DB371C7ULL, 0x7F5A70C333799FA7ULL, 0xFDB40BD44DA9BD30ULL, 0x602EC83D76FBFCFFULL
        },
        {
            0x14E766C6EF6F195EULL, 0x8910920065D556C0ULL, 0x4B4B793C90929350ULL, 0x0DEE00BB5E656563ULL, 
            0x857F7D0820AEA19EULL, 0x94F1C45E80E262C1ULL, 0x151F5DD346B3B0A0ULL, 0x56AB0612E9FBDE58ULL, 
            0xE7A6EF218EEAE3C0ULL, 0xA10B712E9A5AB18AULL, 0xED2F5ACF6750D47DULL, 0x827C6F0199A97FF2ULL, 
            0xC2F4BEC8A70E3E56ULL, 0x383AE11CE44C6494ULL, 0x16745F862ED7C96DULL, 0x2037EDEBB8DDDED6ULL, 
            0x540DBA32D990E2D3ULL, 0xE572C336A493555CULL, 0xED789DA3D0DE0007ULL, 0xCAFF545831E92323ULL, 
            0xBEDAD921378803EAULL, 0xEC642B6736888EECULL, 0xFCA063F4512561E2ULL, 0xCE239885D86F86C2ULL, 
            0x79A9C5EBC37E8A31ULL, 0xB01E8B7EC616417CULL, 0xC833E040CEFA58C1ULL, 0xBEA55D5D8D8BDC0DULL, 
            0x309E207313F62D6BULL, 0x2B08508E8638E182ULL, 0xA1BE333B266F6D68ULL, 0x9E9F5AA216D50648ULL
        },
        {
            0x735CF6131B95C13DULL, 0x236446C239969F0BULL, 0xF7F45BE15446A3AEULL, 0x93820215985FB1ACULL, 
            0x23E14B1C1E24D51DULL, 0xC7505B6D97983D1FULL, 0x825AF06049FB18FEULL, 0x3A9182D07CC01020ULL, 
            0x5158E7484C32847CULL, 0x59447169A9E6BD07ULL, 0x0B228020864B74FEULL, 0x13CDD0286990B0A6ULL, 
            0x9AF0C038D8FDA7C4ULL, 0xB836249925F82183ULL, 0x11E4373FF8C8BEEFULL, 0x2F1B865F49610F06ULL, 
            0x801401782CA1BD9AULL, 0x155DFFCB914A2758ULL, 0xE64D74AE500FA24FULL, 0x4A2B48E775EE3621ULL, 
            0x0B8C72E37B3F7904ULL, 0x07DE6154FC72D8C6ULL, 0x8ABAA86B662F1841ULL, 0x2E2C39789DB4B3EAULL, 
            0x8BB84014CAB1C4EFULL, 0xBD8F661AE0D9CBB7ULL, 0x644CF4A245AFB4A3ULL, 0x1ABD59EB435E01DAULL, 
            0x16D8DCB9D4809595ULL, 0x085F70C845AB62C5ULL, 0x5B118D2DBB4F92F9ULL, 0x8B9CF5BCFB22BA5EULL
        },
        {
            0xFB0D9E5997643407ULL, 0x711802789BBC743FULL, 0x0708B96998689646ULL, 0xA968B0D28A2135DCULL, 
            0x18773FE67D4E4554ULL, 0x447652CEEDD15D45ULL, 0x19272527E42E39AAULL, 0xC10212AEDD043D21ULL, 
            0x82DE16B7E0ECE752ULL, 0x1AE8A4C415FCFDADULL, 0x75E6D4BB2B12F32BULL, 0xA09CADF39CA11FE2ULL, 
            0x5232D4423D230DABULL, 0x07F58C40F966584AULL, 0x8314874B01A007D6ULL, 0x6EF715D66D603A0DULL, 
            0xE4E5C06959973F07ULL, 0x00B29B2DDDA08D8AULL, 0xCE12B3BD568B7201ULL, 0x9A5394289B880834ULL, 
            0x049EA066B4F8B37DULL, 0x0B1186D6ED972A3EULL, 0x28045F51EE8ABE13ULL, 0x8C37AD615C71B0A4ULL, 
            0x6857AE9B9386E822ULL, 0xBB6BCA0B0A4F36DAULL, 0x0D03AE3E76068EADULL, 0x81F9C6E1032BBA56ULL, 
            0x95D2318611041011ULL, 0x035B0750295E21B7ULL, 0x9EB4DE6969201481ULL, 0xA517146ED0A3C788ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseEConstants = {
    0xB9EE5FECAE8D6016ULL,
    0x71DD38B05ADA3461ULL,
    0xD06457758F3E5F02ULL,
    0xB9EE5FECAE8D6016ULL,
    0x71DD38B05ADA3461ULL,
    0xD06457758F3E5F02ULL,
    0x7D5F98827D56FF89ULL,
    0x8862144624F58520ULL,
    0x22,
    0x92,
    0xEF,
    0xA0,
    0x85,
    0xF0,
    0xF3,
    0x85
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseFSalts = {
    {
        {
            0xED87965B31288B7DULL, 0x06EB039CDFF87C7FULL, 0x09B6538E1CA7349BULL, 0x9AEA9C0CA7168C75ULL, 
            0xA3AD77BF946C490CULL, 0x48F2EB7EED18C09FULL, 0xF00768DB2022A619ULL, 0xEBDA3BC129933EA3ULL, 
            0x94F94B52EB398E48ULL, 0xF49E92EA7885339FULL, 0x60C505747642358DULL, 0xD54BAAB81634B6C4ULL, 
            0x6D12CD9F959721BAULL, 0x3551D529D8FF22DDULL, 0xC6D6B72C97780DFFULL, 0x086A515C8C20F553ULL, 
            0x09C2B3B66CB62215ULL, 0xB13E1D81812117ABULL, 0x8F3B3E2595F3A5E8ULL, 0x0F8FA78F8D65AB34ULL, 
            0xDDD69B8A83224E11ULL, 0xA542BEFDC61CA67EULL, 0xDF8EE9E2CCE70E79ULL, 0x2ACFED735DAA8D19ULL, 
            0x471555C2D5108C02ULL, 0x1D565059E0A6BE1AULL, 0x55AE52660AFEA4D9ULL, 0xDF09FE83E0967FC3ULL, 
            0xEE4E0045DE922DF7ULL, 0x21B494D5E7B5CD61ULL, 0xBA763CC11ACC5D0CULL, 0xCF4F1F978A754B62ULL
        },
        {
            0x203B7A1886E7E38EULL, 0x8304DF39313BF11EULL, 0x4FAFB45814A7DF09ULL, 0xE7126D8D27D9981FULL, 
            0x47168CFAD2284520ULL, 0x20F97F7CFF7FBF06ULL, 0xAA2E48F6213DDD47ULL, 0x920E7AD3923EEBF3ULL, 
            0x9B18ADBDD9771CE8ULL, 0x2BE66F6BD3F8C379ULL, 0x87D5DD95857DED0DULL, 0xE4559C7504D111D2ULL, 
            0x08BBFDFF46EF4276ULL, 0x0E7EEB82EA805288ULL, 0xA34D658F22FD7C77ULL, 0x0443C0F237EEE4A1ULL, 
            0x66289797D904E493ULL, 0x25C8059C57E2897EULL, 0x883CAA7466AB5EF8ULL, 0xF30C255079B2A9B3ULL, 
            0x96333AB9829AED3FULL, 0x449474282D42A6F4ULL, 0x66092499315B2BDFULL, 0xA83978D6D1CCF82FULL, 
            0x8CA5EBD8316B47A1ULL, 0x754995C59EA2420CULL, 0x29C3DA52CA8B9315ULL, 0x76EA22F30DDC36C4ULL, 
            0xB79EDAD190F03763ULL, 0xF05BA80638186AD9ULL, 0xEECC0955DEDC99BFULL, 0x7D05E733AFC157A7ULL
        },
        {
            0x3B3CAA224F865B62ULL, 0x1E88210E7C94CABEULL, 0x9DEB440F36730599ULL, 0x26A857D23434E6CEULL, 
            0x5BC92987EAB9A334ULL, 0xAF625792968F982DULL, 0xC578C24D5CA4BD67ULL, 0x9F38AD7558B9FA1BULL, 
            0xA6FA100C65616BD3ULL, 0x4AFA48DAF9CF27F1ULL, 0x296C084F3EDD4909ULL, 0xD7D8AD6CD180F181ULL, 
            0x0CBA32E39A6D5920ULL, 0xF173D348FA260B6AULL, 0x4C4A9B6B120F0290ULL, 0x1636ABB18C2399E1ULL, 
            0x8E5CA9C51E241435ULL, 0xB7998E9E1B7C84CBULL, 0x817D9E14BADA398DULL, 0xCAEAA9C05DC250ADULL, 
            0xECF68323450C8DD7ULL, 0x24C6E91C2CCB4514ULL, 0x26E9959810243C5AULL, 0xF962FA8476A4F29FULL, 
            0x2A4ABB40403F42BFULL, 0xCB02A73A480FE4EBULL, 0xE7D7DB6322D89C4FULL, 0x58E4627CA87EB9A5ULL, 
            0xB39AFF518A0F0226ULL, 0x760D0A977C99CD75ULL, 0xDE5878112D17B99CULL, 0x0C6AFB6F2610F709ULL
        },
        {
            0x6775CC0F20229F08ULL, 0x9BEE467258492895ULL, 0x9829A3990F10F0D8ULL, 0x27986FB4F8A4DFF9ULL, 
            0x61681B63C9E780DFULL, 0x4A67822E8C11A532ULL, 0x1DE166310153D91BULL, 0xF84CA2E0137CC59FULL, 
            0xDE4541AA0ED0E983ULL, 0xCDF55F13A73C9915ULL, 0xA6600FF1BBB4E58EULL, 0xE2206F0BA379457FULL, 
            0xF48321306D635E68ULL, 0x84C80004195E89C2ULL, 0x32FDF6BAFD161FE9ULL, 0x5BA5AC1E35EB0999ULL, 
            0x450F8E42AF96EFFAULL, 0xB5546F04CB91C1F6ULL, 0x135776FF67B0D3C4ULL, 0xBEF421AE47FEF5BEULL, 
            0x668C1AE26950A72AULL, 0x9B23C3FF714776DAULL, 0x2E1B937A899B3F02ULL, 0x95DA24D77D511F0EULL, 
            0x726CC9803287AB55ULL, 0xC72218AA1389BE87ULL, 0x1E6D677DC3904433ULL, 0x18B490C3442513CFULL, 
            0x36775C660A8A1507ULL, 0xBE5D6EF16EF133D3ULL, 0x5712A6C3A35A18D1ULL, 0xBD872D064B5BBF17ULL
        },
        {
            0x113981E533D34BDFULL, 0xEFDDD8E6D5696B7DULL, 0xD5DA9F0E5131639CULL, 0x8C33D54ACE8E0C19ULL, 
            0x811916E8645A8CC1ULL, 0xA2670A6CFDA276ADULL, 0x090A892FE64703F0ULL, 0xD926C3480A919541ULL, 
            0xFD7EE59C3ECEDF61ULL, 0x8ABB5151267BB18AULL, 0x4637F0EAA521D0DEULL, 0x10FBC83A29133FAAULL, 
            0xB899D99E987431CCULL, 0x3E8E49BA12579432ULL, 0xC1590999A2CE39D9ULL, 0xF3828C6D0ADEC82AULL, 
            0xFB7CA2881D3C0345ULL, 0x042074614C1257A8ULL, 0xDC5A5A154F701764ULL, 0x1620CA1F169F665EULL, 
            0xAB0BE763A0CC610CULL, 0xBC127E61CD09DC11ULL, 0x19115B88BC155E55ULL, 0x222B0B74E10EFC9EULL, 
            0x60B1811E5184917EULL, 0x32EBD0703174A9E9ULL, 0x416CA1D7AFECE5E8ULL, 0x631B0274B1269373ULL, 
            0x0E8ABE29C4380242ULL, 0xA9FB3EB141DD89AEULL, 0xE6FFEC4D5FFE8F45ULL, 0xA2CE78059F4C9C2AULL
        },
        {
            0x0446C4FA66A092E6ULL, 0x6D7357BBC57166D9ULL, 0xF6E4106C048AF997ULL, 0xDD200423DB136976ULL, 
            0x332FEE5639947764ULL, 0x7692CBDF4A7A57AFULL, 0xBCEA2ADF6A1CE9A3ULL, 0x57094B76C7DF3006ULL, 
            0x02150C138682E520ULL, 0xEB64BB367FF66B7EULL, 0xE6A6E748C27AA0A5ULL, 0x35EB6D12A6FF902CULL, 
            0x92A048F881CC3D50ULL, 0x67F9AF1E3B2F8C96ULL, 0xBC5C736233DE4226ULL, 0x333473113EB9FA03ULL, 
            0xFEFD65CF3FAF6DA9ULL, 0x0CB49AA913F0900DULL, 0xDD602F71BE930549ULL, 0x8E0B4EFD69348949ULL, 
            0x3DFD3E12B965AC96ULL, 0x63D55AA0E1B7640CULL, 0x34B93255A46C6DD2ULL, 0x30F489A8493DA153ULL, 
            0xC697704F43E6663BULL, 0x18455610F8C461D4ULL, 0xFD625A085FAB1F29ULL, 0x2AE605970911B0F8ULL, 
            0x7733A77490CF02C0ULL, 0x30FDE87637423F85ULL, 0xC5CB6D55E709AD5CULL, 0x43843F078B43D647ULL
        }
    },
    {
        {
            0x18EAFC3949BF87EDULL, 0x72AAC437E99E8F64ULL, 0xA49E82FC7ECE9E08ULL, 0xC3E9F848E06E89D2ULL, 
            0x394FF28C935B3A8AULL, 0x24475591C0BB1822ULL, 0x14B233283E9904F6ULL, 0x971DA5E7EE253662ULL, 
            0xC117890C6F84F7CFULL, 0xEA28FC8DA4A935F2ULL, 0x24B2300A6550E837ULL, 0x9A62DD8BFB246E1BULL, 
            0x887BA842815681CEULL, 0x2875BC491985D891ULL, 0xA45191017A1B5588ULL, 0x74616D206781A6D9ULL, 
            0xBA55450ECFE22866ULL, 0xC02012E64D05D997ULL, 0xE7DC8F5BFFB7464CULL, 0xAEFB4F7B9D7331D6ULL, 
            0x88FD78D9C2080BDEULL, 0x0801C2E689900721ULL, 0x9E8F804A0B2576A3ULL, 0x717EB3E4900B1AB1ULL, 
            0xF13FD04371376FECULL, 0xE84A554BFB61BE7EULL, 0x9526B64BA26849C4ULL, 0xCB1BE56A7E0D9A7EULL, 
            0x37B1F747262C3DCDULL, 0x51CA36EC6CDD30ABULL, 0xED892D3245445B20ULL, 0x21C4E5800F6C0E93ULL
        },
        {
            0xC35CDF21E8390660ULL, 0x2F73E5227F188EF1ULL, 0x363492753DA311A3ULL, 0x9088438BD58E50F4ULL, 
            0x8015E54705B0AE2DULL, 0x26E1CB5C289BD8CCULL, 0xEC36E485BEDCD2F6ULL, 0xF29BDC50514F4BD7ULL, 
            0x204908CF17A41F75ULL, 0xBB2B267E2A5167F0ULL, 0x0827983B43434BAFULL, 0x0D0269A6653B3172ULL, 
            0xBCE8D168097F7578ULL, 0x0A13FA38B297D965ULL, 0x454ECBFEF4B50CFEULL, 0x283297F2EAAC6DA6ULL, 
            0x239844CA5B25B4BCULL, 0x843CDE21F86EF369ULL, 0xD23264872BFAF29DULL, 0x9E3E2EC6A67E878DULL, 
            0xECF1EABCC9FB032EULL, 0x9F290BF2BD373107ULL, 0xA9DA495A6A23BBE8ULL, 0x374DA655FDB27CE7ULL, 
            0x0A2F8AEB68E18BA3ULL, 0x9E61A15D2730083CULL, 0x32A9CE37379EEFD5ULL, 0x8F75ACEA42DFF04DULL, 
            0x3B1F15D38E31755AULL, 0xCD0439318B04220EULL, 0xA95C99D07A6AF9E4ULL, 0x0A3B1DE25A4F4242ULL
        },
        {
            0x14D44495CA17DE2FULL, 0x35FE24888647B7F5ULL, 0x9E6D74500C8A7B50ULL, 0xD62E04D986C39ED5ULL, 
            0xCD4F4CF65C579566ULL, 0xD2ED549FD2B3BFCDULL, 0x91657460B47E7838ULL, 0x3993091A843D502AULL, 
            0xD4D2D65414DCF9B9ULL, 0xAAE34B34D925D5C6ULL, 0xDA6674760F022A4AULL, 0x08F8123493EF7DC4ULL, 
            0x2D0863A21E165E3CULL, 0xE6457413A6955640ULL, 0xF09DE02CE446D37FULL, 0xC92BF88864487680ULL, 
            0xA40EDF4914E694A1ULL, 0x62ED89C6F0F16408ULL, 0x5163D1E9DFF7330FULL, 0x87BFAE0C07A70957ULL, 
            0x18BE08214B1B285DULL, 0x20F42EE77878AD4EULL, 0x8FC621C6088B5046ULL, 0xE939636A02160262ULL, 
            0x481494587689CD67ULL, 0xFCF43B6C2A71BDC6ULL, 0x93EFCEF6172DD3CEULL, 0x94A96FAC7B4182FEULL, 
            0x036D9AD8915D47E5ULL, 0x4FB6272DB4D05C97ULL, 0x16425BA16D8A3E61ULL, 0x112A1DE9189B6C61ULL
        },
        {
            0xC04376F3192DD1B0ULL, 0x7A49EFCF169CB6A8ULL, 0xA925143165EA8578ULL, 0x876383B46F9329D5ULL, 
            0xA6DD9DF42E8B436FULL, 0xE4948D999BE1774EULL, 0x1918BFE81AC390DCULL, 0xB52D72534498153DULL, 
            0xA6D94C25203A3E07ULL, 0xDCAD6E4DA200F050ULL, 0x23490B0389F46308ULL, 0xB3A60F2270EC6DFFULL, 
            0x46387CD067FCC6FBULL, 0xA5F9B19B8C72DC64ULL, 0x77F4B6000FC6B1D5ULL, 0xBCB91676AD65AC6BULL, 
            0x29962A5163FE32AAULL, 0x50458D008E0AA9C6ULL, 0x39D29854A852A822ULL, 0x6985084B293935D8ULL, 
            0x89E12EFD74AAF44EULL, 0xE02D31D93DE71783ULL, 0xBDDA498289BDB6CCULL, 0x74F8219185A46AEFULL, 
            0xE7738E6DD74B4CBAULL, 0xB67B349538FD863FULL, 0x6635591DCBE85F40ULL, 0x246FF23A7F92ABFDULL, 
            0x47B25B711FEE664CULL, 0x08C80D0D628DE1A5ULL, 0x8457ECEB99A7681BULL, 0x3452F3C03C297D0EULL
        },
        {
            0x1FC2325CF9038A50ULL, 0xE5CEB517AEF5FC20ULL, 0x12B3F468169EBC8FULL, 0x05B26B6B217A970DULL, 
            0xCABE2FFD84FA1389ULL, 0xB2A2533560112743ULL, 0xABF7ECE8802DF4A7ULL, 0x263E27EBC82C84AEULL, 
            0xD96A05FA62A15D28ULL, 0x8E3F1E5249A327CBULL, 0x704B631FA1AE5430ULL, 0x8C18CCC372785AA5ULL, 
            0x461200AC93DB50C3ULL, 0x3F90B2EBF92460CDULL, 0x08A753B7C849E770ULL, 0x323352C1B5784B13ULL, 
            0x02F0D194A492C311ULL, 0xB2FB7AADCBA29191ULL, 0x8E9356D2580F781BULL, 0x72DC55AF1C1C639CULL, 
            0x022C56CB00FC42FEULL, 0xCD73375876FA730CULL, 0x08BAB297ECD6C502ULL, 0x9CA116DBEDAA9CB0ULL, 
            0xE9AF39032664383CULL, 0xEDC1CA710D340F40ULL, 0x878F0801BC5815BBULL, 0x95DA63FA9256201DULL, 
            0x4F985A56BF75786AULL, 0x337272231C8285FBULL, 0x185088A221BE0C88ULL, 0x009022F0AB75F66CULL
        },
        {
            0x0967D1F2B152844DULL, 0xFA8950B04BA06FF6ULL, 0x6892251F180AB3ADULL, 0x2EFDBFA0EFBA77EDULL, 
            0x24661FB219445A2AULL, 0x806E3333D60B0F4BULL, 0xC97C35759F34461CULL, 0x6DB26072C468FBACULL, 
            0x6E47FBC2DCA1B96EULL, 0x6B04C5DC6085AD20ULL, 0x142C3FC14B67BDE7ULL, 0xFA55CAF83F17A122ULL, 
            0xFC04C2CD04D06148ULL, 0x5FC1793D8FBE013EULL, 0xA0C7F916FA6E02C1ULL, 0x0169E7ED511DFFB1ULL, 
            0xD1C5A7D6ADC78B21ULL, 0xC165CEE4645D9072ULL, 0x2380DA4CE8A643A3ULL, 0x7FBED901B863E597ULL, 
            0x4EE07ABCDC80F469ULL, 0xF4E5FD9FE0753897ULL, 0x16F95E837459EECEULL, 0x5C2F90D92E277A27ULL, 
            0xA43D48FAB89AE9A2ULL, 0x87041CE92FBCF1B5ULL, 0x8CDFBFD5A35766CEULL, 0x9ADA3A9058085523ULL, 
            0x101EFA7A475E6FE3ULL, 0x527E8E3CEF57E795ULL, 0x412D8F2DFE139805ULL, 0x4BD21DA143607543ULL
        }
    },
    {
        {
            0xFC1D2DA138C96C55ULL, 0xBD1EA2E5E447E9D6ULL, 0xDA380368A252A544ULL, 0x6B1377FE37C6A783ULL, 
            0x7A87983807BA9E28ULL, 0x9D6DA37BBC2A89B6ULL, 0xD11DB301B84625D3ULL, 0x2FA967301B1F2265ULL, 
            0xAF8679185872B313ULL, 0xBAA1CE64916EA8AEULL, 0x848F50F6F74676DCULL, 0x925EA56DE19EFE56ULL, 
            0xD59F5C967BA67F61ULL, 0xFAC63F2AC52D2510ULL, 0x9BCF17E5A0CDC89AULL, 0x95DFEB85AD0891B5ULL, 
            0x9323B04F84D34CCBULL, 0xC4EA53749603FDD3ULL, 0xC0CD7214F74DCDB3ULL, 0x99943B78753F327FULL, 
            0xC5F988005BADFF54ULL, 0x02132A8CAA16E6FBULL, 0x716AFF9E790F168AULL, 0xDF8BC3A665FF0825ULL, 
            0xD466C1C2158118F8ULL, 0x2E1651BEB2B96042ULL, 0x004694D3FD8DD3B6ULL, 0xDC64C1E92C427E75ULL, 
            0x6690588951327576ULL, 0x9A589E7B90C9CACAULL, 0x6090A0D6736703BAULL, 0x18913749E81A257FULL
        },
        {
            0x289DBBFC4C40D87EULL, 0x850CCA1B7DCAD180ULL, 0x80BA348256F396E5ULL, 0x73252B49FDDB87BFULL, 
            0xF67FF9E040F2DAD9ULL, 0x6E096AFDCD32B4ECULL, 0xE468C5A19EF08859ULL, 0x45133020C4B63391ULL, 
            0x8694E019D264288DULL, 0xB1B2E1450C630187ULL, 0x8C82AF884091C12FULL, 0x974AF89DD706EC72ULL, 
            0xE74A3FFC66DD6108ULL, 0x09DB86E690114105ULL, 0xD6C6B4E2F3036D3EULL, 0xFFAC82700B8026DBULL, 
            0xBBC984F75C838F4DULL, 0x4454991292626D8CULL, 0x5B7F334674DA1CFAULL, 0x52754B410F44C52EULL, 
            0xAD3BA88AA70DD9C0ULL, 0xA49A090AF246FF9BULL, 0x47B56FB5150E63AFULL, 0x2BAD58E3FCB999AEULL, 
            0xC3A2761DD3965592ULL, 0x8E40318539FD21C9ULL, 0x29FAB2250277F6FBULL, 0x9EA77F7BE5DF433AULL, 
            0x7A3139305349C91EULL, 0x3EF0BFF71F43F9CEULL, 0xE4ED1EFD4C81C0DAULL, 0x416EC144BED184D1ULL
        },
        {
            0x80E3C2A1D52A3240ULL, 0x3AD77CC2CEB67E66ULL, 0xBCE8B7D4693EDA15ULL, 0xDD024F8E75EF4F58ULL, 
            0x651EC0D98922C45DULL, 0xD4C72C7FAA46A01AULL, 0x51C9A5E8E60C66F1ULL, 0x82DB479ED15FD4F5ULL, 
            0xBF69F3A950CDEA33ULL, 0x322B5D2A372CF4FDULL, 0x7CF114F801AB564CULL, 0xD6C042346A2DF184ULL, 
            0xEB80D3C4573BDECDULL, 0x8E533E644BBC1B87ULL, 0xB5062C28443FC15EULL, 0xC018EF0FC45D380FULL, 
            0x37F03B256FA7F373ULL, 0xA6A2C055B752F4FFULL, 0xC7A7D6F76B950199ULL, 0xBF8F68F43CF07AD2ULL, 
            0x0899E7503A485D0FULL, 0x0A33D0B6202DC410ULL, 0x8C2973CD9DC327E1ULL, 0xB33797A4D3F9EE8AULL, 
            0xDAFE986900ACA356ULL, 0x48110C894404A064ULL, 0xB7DF8348C72606C7ULL, 0xABA7DB59517C4470ULL, 
            0xB5B3820C2E9E0E1AULL, 0x52A24093C335FDEAULL, 0xA57A1B8F1D570C40ULL, 0xFB91078FDB95CB74ULL
        },
        {
            0x4CB2E4738B546E3CULL, 0x3F1F87AD7ABCF0F1ULL, 0x1F3E58B10EB2CABBULL, 0xAAF45F91358F0481ULL, 
            0x6DD7FA1EA968510CULL, 0x374E48B53B310642ULL, 0x4CC054234895F5D0ULL, 0x9246B366B64CF290ULL, 
            0xDA591C2F602A32D2ULL, 0x09D6FD344D0F4D40ULL, 0xC2496D26AA9CD797ULL, 0x30157826BDA27B80ULL, 
            0x4B15F5347706A5E7ULL, 0xE5216DEC0E9FCAE0ULL, 0xB7737D52DD96A7B2ULL, 0x60E40CE41D540D73ULL, 
            0x5A204CF3E7270A92ULL, 0x0ABA7A3F3A20B294ULL, 0x103362D80699AA7AULL, 0xEDFEFE8DBAD812FBULL, 
            0x77E1527E401F957EULL, 0xAEC3560BCD2A60B6ULL, 0x072D67C47D049F35ULL, 0x43CEA8822F4AABC4ULL, 
            0x3A36037F545AAE3CULL, 0x3CEF1E76B06507B0ULL, 0xCDB53FD4F6CEBD71ULL, 0x54F2343639ECCD31ULL, 
            0xF41BB66B5901336BULL, 0x1447316D7BD58805ULL, 0x64253C9283A9EFD4ULL, 0x77A1FF3015DE9791ULL
        },
        {
            0x0F863F46D2D7C6F5ULL, 0x8E6B76C55A79C868ULL, 0x46B403A9B1B754C8ULL, 0x6526F83A8AA0649EULL, 
            0x1F130837C078D969ULL, 0x129FBF66CE859D9FULL, 0xCFCED05F9D451E13ULL, 0x1C9DD322E87880ACULL, 
            0xD38F51610B6EA02BULL, 0x42570FDF89780072ULL, 0xDE1A34B40FAAEF69ULL, 0xE429BC2C1545DD52ULL, 
            0x16C0C91045907004ULL, 0x38AF2765ED1F30D0ULL, 0xC6E446D1283E67BBULL, 0xA5415D80F952DC3BULL, 
            0xAFD7EB04D169BB2BULL, 0xAD6611FA8E63CE74ULL, 0x1549C66B39CFA7FFULL, 0x6A78FA6ED9B478E6ULL, 
            0xB8C51B3B2E3C19E9ULL, 0x4BA61F748602ECD0ULL, 0xDBA9CCFF93D65B22ULL, 0xCFC03E04082B1297ULL, 
            0xB6B2D4BF0E5EEEC0ULL, 0xA4E411A78902480AULL, 0xEC6DDCCCEE5CFCCAULL, 0x0F6E83E1D57E6C0DULL, 
            0x224C7EB92875D7C3ULL, 0xDA310575A1A5A1D7ULL, 0xAD0AA74DE55D9695ULL, 0xD5D23D1FA9DB9BF1ULL
        },
        {
            0x2CDD04996BFA5961ULL, 0x9B8928E00AB5CE0EULL, 0xE815369D48C67519ULL, 0x4FFC91B4399B453BULL, 
            0x069B0473B970354FULL, 0x3F1E70EF685369F7ULL, 0xE9EDD2D997461F7FULL, 0x0F70D9CC8E66CDC2ULL, 
            0xA5CF337BCC4D03F2ULL, 0x771B1D2FAC53C259ULL, 0xFFFC36F2C5DA377FULL, 0x9B8C3E1B40547C3CULL, 
            0xE5F31C6EE38BBC7EULL, 0x3DFEFA2DB30358ADULL, 0x8B4DA82AF930E981ULL, 0x5A425F8DC07A75ACULL, 
            0x8DB1884B9FC07C17ULL, 0x0251986087F5C295ULL, 0x10F2DE5378584721ULL, 0x066EC4D5DB6961D9ULL, 
            0x4C08BBD0EFFF0CE5ULL, 0x0521577B7DDF3133ULL, 0xCAAF19F05065948EULL, 0x7B590AD912984360ULL, 
            0xFCC359A28CBA07EAULL, 0x91A1AF577A50A254ULL, 0xE48367687E1A5B2EULL, 0x0157245949735B4BULL, 
            0x23A0B4B1908089A7ULL, 0xC0A22304A381BB12ULL, 0x7F0A2E6925D13AA4ULL, 0x439C1646926D1762ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseFConstants = {
    0xFEF2862ACDFB08B9ULL,
    0x0BECC0AF680AF3AFULL,
    0xA9F06AB41EB0AFE9ULL,
    0xFEF2862ACDFB08B9ULL,
    0x0BECC0AF680AF3AFULL,
    0xA9F06AB41EB0AFE9ULL,
    0x2986061DAA847BA5ULL,
    0xA811E2ADCE7D1C70ULL,
    0x87,
    0x85,
    0xC7,
    0x28,
    0x9C,
    0x6B,
    0x6C,
    0xBA
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseGSalts = {
    {
        {
            0xF89173F0D04A7142ULL, 0x8EE4054DCEF03C7CULL, 0x6F13A6AFDD7A1EFFULL, 0xDE512220A8665C37ULL, 
            0xEB5D6EB6D459AFD4ULL, 0x15090235DC54A254ULL, 0x28268F42FC1E2914ULL, 0x633AF9E795B65E0EULL, 
            0xBBE99F80F6D71E6EULL, 0x61156F0F68F8CBD0ULL, 0xA48728B53D4CE58EULL, 0x3C40CDD5DEBD0D84ULL, 
            0x6AD0CB114BFBABCCULL, 0x0D335C5385306C9DULL, 0x4005B13C8E138A2EULL, 0xCEDE3AEA429B9E3AULL, 
            0xD7FFF0D0D6276969ULL, 0xFDB8458F6EF01B6AULL, 0x53BF8632B552D7DEULL, 0xF7BBEFE9E8C80A65ULL, 
            0x1061502494E1C767ULL, 0xD2C72CB192FF9576ULL, 0x25F9FD4A694AEC11ULL, 0x3CED9896C37636FCULL, 
            0x86723CA3C1763CABULL, 0xC122955EEB3F54AEULL, 0xEE96C49A6EAE05EEULL, 0xD92A40AE9E77F59AULL, 
            0xE2A05852B9F880B6ULL, 0x613383E789C8361CULL, 0xBD70E577E2843EC6ULL, 0x240C8FA9BAC29130ULL
        },
        {
            0x13BC741E2CF43D8FULL, 0x7ECD7AEF69087835ULL, 0xDF194C88B72524BEULL, 0x31013B539667EECBULL, 
            0xDBC05B7A34A140FCULL, 0xB39C494B66486C8CULL, 0xB6FEA37A7EE768AEULL, 0xF1108BB49A63D824ULL, 
            0x9326C02E0789BAEFULL, 0x33F3A415E818732EULL, 0x99DC17160CF1FC96ULL, 0x09E4D583A79F4197ULL, 
            0x95C333D9B945C39AULL, 0xFD359CD22C2EA3B1ULL, 0xB4FAA428C7C4A35FULL, 0x8F3905D44FB5AC05ULL, 
            0x37F61932F8A53C0FULL, 0xEEAEAB2EEF73DD23ULL, 0x5596CE5770429BC4ULL, 0x8EDC196848D011A1ULL, 
            0x0EF695EBFE3473BAULL, 0x1B6047A1897A9324ULL, 0xAA899E639D2ED56CULL, 0x62C3F24B70E2B9A0ULL, 
            0x9B6A3EFAF9BF3F58ULL, 0x06712D0C6CD46513ULL, 0xCFE89B3B448206EEULL, 0x0CE08D4EFD5E0C1EULL, 
            0x07698C0FEF48FDC2ULL, 0xB93946571752F5ADULL, 0xCDA1D3C7CF80B7E4ULL, 0xB8D91300DF3B862FULL
        },
        {
            0x97DD8AB495979312ULL, 0x57CEFF59BB7B0B2FULL, 0x793E536C8CDAF92CULL, 0xA581D4202165ECCCULL, 
            0x1B4200DA67B0F040ULL, 0xCEA430B95B88E8EAULL, 0x20CF50D06879CFA3ULL, 0xE63BF1BD8E7B850CULL, 
            0xAE177D7445A4FA98ULL, 0x581021A9606A2B9CULL, 0x97DD670B99895277ULL, 0x1D71E3E951E2AFE4ULL, 
            0x6179A73CF390D891ULL, 0x21EF4C1085FF6140ULL, 0xAA7DA90F37A46698ULL, 0xD5DB1526AB588518ULL, 
            0xF678601FCD9FA408ULL, 0x1D85CA45DA00DC79ULL, 0xE52AA2B4D55FBE2FULL, 0xEC0572D9AAE496EEULL, 
            0xD9D82ED243AB5A51ULL, 0x791556EFC649FF82ULL, 0x8DD391E9F3C80AB0ULL, 0x8E791508D18F323BULL, 
            0x9ED5E16BBD46AD0BULL, 0xF84F9064373AC372ULL, 0xB558F46BBEB94BFEULL, 0xB8FCCE268E3DFB0FULL, 
            0xB31BD30BBA1B3523ULL, 0x86F7586DDDD01D89ULL, 0x7C07AD045E379629ULL, 0x5EB73BC58D5D3AC9ULL
        },
        {
            0xF72D773DE1EB2B1DULL, 0xCB09852D71935D3FULL, 0xEF553C086F798041ULL, 0xDEBE9A6603048AF1ULL, 
            0xFAEBC35DD94CB8B4ULL, 0x28D19F7F89D57E16ULL, 0x52608B2FCD9EB85EULL, 0xF17772BA5D0C2BE9ULL, 
            0x98B173C9E647EE31ULL, 0x4702459C1726D652ULL, 0x86BC8FB2D3CD3D96ULL, 0x2327396960C63924ULL, 
            0x321CDFA07472CC8DULL, 0x586DEA660C63A18BULL, 0x639587CA7896723AULL, 0xC4F70C3CB2FAB702ULL, 
            0x4D18DC721841525BULL, 0x9B2EA1247600907EULL, 0xED3FE384527C893FULL, 0xC3147E85EC744A55ULL, 
            0xBFF9B47D6FC2889BULL, 0xD843700F1BD2FF9EULL, 0xE65D067D5A9447A9ULL, 0x95CB7B482FBAB963ULL, 
            0x8B4B6A63341DD38FULL, 0xE8D2725A09619516ULL, 0x32D14F8DC1FAC94BULL, 0x4D184A7EDCC9CA33ULL, 
            0xE76861FD44E370EAULL, 0xCD2DDE5E75C8B4CAULL, 0x67A67783F5DBB83DULL, 0x44D4A9881210DC23ULL
        },
        {
            0x0B431FFA9396D8D5ULL, 0x25FF5654BA362528ULL, 0xCDFA60CC91B14156ULL, 0x164B6BF52A107242ULL, 
            0xA1EE6B57C3C87C58ULL, 0xF1DA147A8A6FEFA2ULL, 0x6D6C680C6DD2A804ULL, 0x58565FA382CF2353ULL, 
            0xB3BE51A2DC089BACULL, 0x281D7A23185D0AD3ULL, 0xC0CB0E9C305F4CE2ULL, 0xD51A8FF86609698CULL, 
            0x5D20429001DDA30BULL, 0x2FD11D6E32601D2AULL, 0xCDA475FC37AD9C3FULL, 0x47E12DB2AFB13FABULL, 
            0x3F3FFA8E3E6D67D5ULL, 0x0E4DC19CC8117FD0ULL, 0x7DC2611B241BE423ULL, 0xC9B7837ED196863CULL, 
            0x4726D76CB91551BAULL, 0x0E6FC9853A7E2A5FULL, 0x137FDC5130F83F00ULL, 0xA6F697494CC156C8ULL, 
            0xF3E3623EBCD68789ULL, 0xFEACFFD72841D6A8ULL, 0x1847FC490113AD5FULL, 0x63439FB74F4FBA3BULL, 
            0x7AA521795C87B66BULL, 0x62F416B778E33106ULL, 0x712F0C0EBFBE6051ULL, 0x4D99C7E1516FCE80ULL
        },
        {
            0x547183E3756BC91AULL, 0xE2BC075D3B8E5572ULL, 0x06BDAF8EDDED7FD2ULL, 0xCD73229214E3D4C2ULL, 
            0x44CC619C6F28A7EBULL, 0xEA940DF442348B11ULL, 0x70DA94D8C8C5A2A2ULL, 0x47F984FA8358EDD0ULL, 
            0x12EC616F110F36B8ULL, 0x87049DE3EFAE50D6ULL, 0xC6F6B94CE67B6B7BULL, 0x80B7B69B98D64A95ULL, 
            0x3AACB16EE238F93EULL, 0xED796D9157B43A09ULL, 0x0E4368CB0DB20451ULL, 0x8747B6A361A07682ULL, 
            0xFF3B23521040B64BULL, 0x8B451E0B507602DAULL, 0x346C878A9730A7C4ULL, 0xDCD2E48808A2A5DEULL, 
            0x357222EF5A52A737ULL, 0xD972E0D8ED4B7EA8ULL, 0x7A0A6D6A0DD03FC7ULL, 0x212BBC8F83B089CEULL, 
            0x70FEFDF26B748966ULL, 0x7C50196DB2E620A7ULL, 0xF733990169C6858FULL, 0x12EED13D41168C36ULL, 
            0xFD362EC8CE58C697ULL, 0x920FB5DC748B0BB2ULL, 0xBE7CB82310B3DCEEULL, 0xD05C48ED6BC9D327ULL
        }
    },
    {
        {
            0x5A072CE08455D158ULL, 0xD7EF6A56253D6EBEULL, 0x3838E1AFC2755104ULL, 0x16FDC8FCC98C02E1ULL, 
            0x4C4BD1618403728EULL, 0xF12E4C3F2A80E1A5ULL, 0x76DECE17CA5B401CULL, 0x5DE9279FED2D484EULL, 
            0x1B6D799E261A3D46ULL, 0xDD90743BC0EFE24EULL, 0x223EB95C3AC00069ULL, 0x596B8A750FFACBCAULL, 
            0x7DE8A5CE315054BCULL, 0xABE4A02C1BD9F6ABULL, 0x33ED7B23C3EAB468ULL, 0x9CC2926FB041533EULL, 
            0x87D9B8511547D644ULL, 0x4E4BBD5A6112F828ULL, 0x4FA250C3CE6CCBBEULL, 0xC4EB1AB015263EF4ULL, 
            0x14CC601BC7769F0BULL, 0xA7D9CC61F1591FFCULL, 0xA455DB490A76CB0CULL, 0xDB4F09DC7F95FEF4ULL, 
            0x444567B752109AFCULL, 0x420A7E032268AB99ULL, 0x5D479B5ABFBAC6CDULL, 0xA66C3E52ADCDA7DEULL, 
            0x4C921C5B720AA479ULL, 0x0842DE032E3142A9ULL, 0xC5B53E556946CD5FULL, 0xD97BBFD7EB67CF20ULL
        },
        {
            0x21A37CC3438EEDD7ULL, 0xCF92487FFA25C2D6ULL, 0xDD6D0CEA5164FBC4ULL, 0xB2D187DAD5A936DDULL, 
            0x3A51971DBF1C4738ULL, 0x5343567E3AFF7E2AULL, 0x82FC46683E35DECFULL, 0xF72EC7AED31DE31AULL, 
            0xAAB23E15EFF27A0EULL, 0xB81B2A3F28E4FD13ULL, 0x45B8779C17E52571ULL, 0xD601E27CFB2F0CEEULL, 
            0x2856829034713791ULL, 0x7ADE335CF68386C2ULL, 0x63A87C1F03B0A448ULL, 0x82549F9DB57CB27EULL, 
            0x87A92B781A842D8DULL, 0xA2D3BE9327675274ULL, 0x7C0BA5BCF18CA69AULL, 0x49EFE443A9D33CFEULL, 
            0xCBDB089B77363FF4ULL, 0xA2A4D6B0E74F87F1ULL, 0xAAD2A3769F3DDCCBULL, 0x75D31426A61045F5ULL, 
            0xC0156FB1F281D0A4ULL, 0xA78C924EE97ADC47ULL, 0x991B968CE7D27371ULL, 0xC6C84DCE7536CAA2ULL, 
            0xB84C19801D7995BEULL, 0x029DE3F331D32E16ULL, 0x7C48982650971F34ULL, 0xFCD7F891810E28B4ULL
        },
        {
            0x03270145C574ECD5ULL, 0x1139C8CFD8C5BCD8ULL, 0xCC318C1D751B5499ULL, 0x35D45FAF8A58C84EULL, 
            0x6C234F7762ECEFE6ULL, 0x7A20E514D00887B7ULL, 0xD0F7855DBAFC7E5DULL, 0x2E62FBD516811F69ULL, 
            0x043A4484FF5B4207ULL, 0x441BCA5F19FF0CB9ULL, 0xF611A8AB7204B742ULL, 0x324806637741BFEDULL, 
            0x0E8D5E5BFFEC7853ULL, 0x2C90FE001646CFF0ULL, 0x4D6CF7B554D8983DULL, 0x091692A2A7006B71ULL, 
            0x82161561CFD2F2C6ULL, 0x52BC81C85DE999B7ULL, 0x275D9776ECAD5F58ULL, 0xA016E1B948B10F97ULL, 
            0xE4838B67BC14429BULL, 0x1FCA6E9BEC8B6DCCULL, 0xEF113EA3F697777DULL, 0x463E7FAF996276A2ULL, 
            0x2135C7D01714063AULL, 0x5F96BE03529858AFULL, 0x74BB8FD382F26A5FULL, 0xB43228C311D4A608ULL, 
            0x6A7560764C84C91EULL, 0xDA74DAF1E34F1133ULL, 0x24D2317990684808ULL, 0x3B4E390D2EFB2426ULL
        },
        {
            0x079DF3BEF0B3C87EULL, 0xCFFB9E2E04956F41ULL, 0x06FDF123BB1B3F2CULL, 0x7D6BC9EED3EE804CULL, 
            0xCE7B7D2B463680ABULL, 0x16F8E77627692813ULL, 0xAD59A21F3E251F7EULL, 0xD4D1792E262D285CULL, 
            0x43E0E19DD20793D5ULL, 0x89928F8A24FC780EULL, 0xD436CE07C84575A6ULL, 0xC0011F44DF9E1B7BULL, 
            0xDD78D5A04BE78EA4ULL, 0x8B3DC35E6BC5F342ULL, 0x3379F79E7E8675BCULL, 0x5EFB97F44D6E0068ULL, 
            0x334A62AD1EA3EA20ULL, 0xF29796E7FD811F3BULL, 0x6CBEB83E1379C868ULL, 0xA0EFF4A56097E3C6ULL, 
            0x45237961F5ABCDC4ULL, 0x76EF02EA2B260C18ULL, 0xCECA52003973B132ULL, 0xAEE03765F68A305AULL, 
            0xB62D678166F26E3BULL, 0x759BA937A08FE76AULL, 0x6F87B8810F484DE8ULL, 0x93FD5E271CFE44C0ULL, 
            0x488C178DDDD5476CULL, 0x9D5758CC5D1F688EULL, 0x35FE68EE886AA35BULL, 0x8BA542EB846278EBULL
        },
        {
            0x616767D1469BA6C1ULL, 0x23036CA3BF2F62DCULL, 0x3046ED8C0EFD6873ULL, 0xB8B7FB40D6B508E4ULL, 
            0x8EAA38867572F95DULL, 0x415116648B995837ULL, 0x20EC7AB229015A06ULL, 0x5D5C6DF049B0A98DULL, 
            0x59FCE433F81C9EC3ULL, 0x361EAA57BC2D8531ULL, 0x81C03A2F69938AE9ULL, 0x650C5ABFD790AA51ULL, 
            0x21143AE7C2E7D2CAULL, 0xB17AADFFE924E43DULL, 0x686BFE0FC76929E1ULL, 0x81A038CBED8FC38AULL, 
            0x65B1AFC961CE5D97ULL, 0xB6473F0A6B9C963EULL, 0x1766D4D8D211DA29ULL, 0x98F927DE6F7C8C3FULL, 
            0x0107C39CC6336E47ULL, 0x7574D64477E50E45ULL, 0x02B8550792380959ULL, 0x57F8B5AF08D8E3CFULL, 
            0x12F8206FAC888AA3ULL, 0x7AC468C8082A1257ULL, 0x0D65E247A06C6D32ULL, 0x6677502628716CC2ULL, 
            0x3425D9D65EFA9154ULL, 0xCB38374965D9D9FFULL, 0x286F1FC1443D7384ULL, 0x4978E804E21CEE2FULL
        },
        {
            0x4C91F1EE3F5B7441ULL, 0x3531A0CBE6712808ULL, 0x41D1FE2C461A060FULL, 0x19EBD213E4409299ULL, 
            0xD211DA370800BAB2ULL, 0xEB2A8024A6A1F278ULL, 0xCAD26F98C224A10EULL, 0x3CA81823D688248CULL, 
            0x0A29A018CB82D522ULL, 0x7B2B06B6E3E40FB0ULL, 0xE80937D60727D8E4ULL, 0x1FEBA228ABB1B5D0ULL, 
            0x906B8943F36C4B4CULL, 0x3A0A8A78422E2E09ULL, 0x888AE3BF134FFA60ULL, 0xFE042D3F288D6BFBULL, 
            0xD42DBEDFE4929876ULL, 0xC1221BE8951AB12CULL, 0x31452E36A0B7C7D8ULL, 0x7DD0215C8560EC1BULL, 
            0x5EC255BC9AD2AF80ULL, 0x8212686256CC94D8ULL, 0x3A25696BFEAC8497ULL, 0x8EAD40BDCA124554ULL, 
            0x9EF235307A8ADC3CULL, 0x39515716B36DAEFCULL, 0xB58B30AABD201F3FULL, 0xF1B48405A821D80BULL, 
            0x9C42B60C034B43F7ULL, 0x730EB29AC14793DDULL, 0x97C0647FA4F2D8EAULL, 0x1BE0D68A9E6F3B4DULL
        }
    },
    {
        {
            0x69D80FC0ABEBA802ULL, 0x2F3483A805417EB2ULL, 0xE6C3EA0D049CD976ULL, 0x1DF9B28F6978599BULL, 
            0x6EEAEE5C7A11D534ULL, 0x8A598B2322ECFBA4ULL, 0x78716680388C212AULL, 0x83D811B676B07316ULL, 
            0x634EA954BF98E42AULL, 0xB37C0639AE895B71ULL, 0x1606969E439CC824ULL, 0xB1FD97009C1BCF07ULL, 
            0x393FB496A04D6858ULL, 0x76278D2FFAFEF3A9ULL, 0x39380B04297D7CA3ULL, 0x35B22563DE44C61FULL, 
            0x3AD2BCF9268C6A50ULL, 0x7954DF64F9995CD7ULL, 0xB3F35B1B34DF5695ULL, 0x619F48B2AE6D3DB3ULL, 
            0x2A03FF0C55F3B6B2ULL, 0x670224FF0400FCFAULL, 0xDA7E18C7D1C9B914ULL, 0x8C0FD717D10EC91BULL, 
            0x0D498E034C1008E4ULL, 0x3EDCBC0834D0E299ULL, 0xDD0491F4E002CCB2ULL, 0xD1BD3FC0536A0D4BULL, 
            0xB115361FDA987018ULL, 0x2BB2C2A7C37CD50DULL, 0xF4411747A9F35E84ULL, 0xB31A51590C23A9F2ULL
        },
        {
            0x29592A274C7AD062ULL, 0x5B5CBA22B71B11FAULL, 0xBE61DDA7676CEB97ULL, 0x8BFF15C405C8F56EULL, 
            0x714426BD3663F44BULL, 0x727BE94CA6AA5AB1ULL, 0x199C8A1121B3847EULL, 0xF5974769AE52C0CAULL, 
            0x8073D37BFAD74F0FULL, 0x269C8154D74230F8ULL, 0x99D5702251873933ULL, 0x205C3358C72C2F60ULL, 
            0xB1650045E7BCB840ULL, 0x6AAA7C18DD095BA7ULL, 0x148F050FE81FEA3DULL, 0x2DB7420051204E17ULL, 
            0xAF7C833D7BD43B0DULL, 0x6429C398954BBE72ULL, 0xFD174851393399EDULL, 0x434F314067452473ULL, 
            0xD456B64BC70E289BULL, 0xA6A889B32B54714AULL, 0x26CAA797613BEDA8ULL, 0x760328A1494901BAULL, 
            0xB2694628D5FDE085ULL, 0x8A17946459910FB2ULL, 0xC786E8098E0DDCD8ULL, 0xC00A065A7D496EAFULL, 
            0xABA19E6EEEDB7108ULL, 0xA9EDDE0449C9A2C6ULL, 0x4971D3911C3DA7F2ULL, 0x66B46233AC9B84EBULL
        },
        {
            0xF191E4F5601BBE9EULL, 0x6A90B50A921567E0ULL, 0x4A898DDF118D7DADULL, 0x4FDFA273156F310EULL, 
            0x86CB43AD2B5EE6A6ULL, 0xCC7CB7618A22383EULL, 0x1885142E8660B420ULL, 0x07284B649ABE413FULL, 
            0x5B40B3226FA7EC77ULL, 0xDE926FDBD9DF44CBULL, 0x8F9B148F82596FC9ULL, 0xAA5610C4A8F99678ULL, 
            0x096E351D0AB1DC0BULL, 0xD48ACE5AD0D26370ULL, 0x5CB35A30B1DD2FD4ULL, 0x49EC31E0A8C61A68ULL, 
            0x508DC71B1B7F8735ULL, 0xFBFC180F478E808DULL, 0x4B730DFBCF8B5D2DULL, 0x9885DEA0281A1188ULL, 
            0x9B2C26A865F19A5FULL, 0x5FAFC1D31FB80237ULL, 0x4CAB9E10B6623799ULL, 0xDD5C2417A4035794ULL, 
            0x48A70C229967AD63ULL, 0xD0EE464990414AA5ULL, 0xF718EAB70A81407DULL, 0xB808259784D6A9EAULL, 
            0xBA349914B4D42856ULL, 0x2AB82EF613345A07ULL, 0x1824ECE2BD420632ULL, 0xB9761E55ACFC13C6ULL
        },
        {
            0x9C330C95E4134B9FULL, 0x438C1BBAD3249C52ULL, 0x5C97572722A6222DULL, 0x3DEAB36BB17DE475ULL, 
            0x7C4D99EDB9DEE619ULL, 0x9CD9A53AD462CB7CULL, 0x0C1DE1A13666D4A6ULL, 0xC8AC955A2C546388ULL, 
            0xD93F4FA3030A29AFULL, 0xABC9D3705E80C72BULL, 0x1219FB4AA1DF3CC2ULL, 0xF7B0F95A7DED0753ULL, 
            0xFE4E38A267DA341DULL, 0x1C92ECE341C2DA43ULL, 0x592B13276E090FA4ULL, 0x966AE406E705BFF4ULL, 
            0xA58194130978C976ULL, 0x62D38A935BB4ED61ULL, 0xC57778652D024106ULL, 0x1CBB135FCD1F11ADULL, 
            0x8E4E67072457E778ULL, 0x117909A39C0A5CB0ULL, 0x848BFC7AA20CE9BBULL, 0xDC4A74B333044484ULL, 
            0xB74C841C0E28E4CCULL, 0xBC1D0A9F9255A0EAULL, 0xFF38517C0A079844ULL, 0xAEDC6A8A63BCFBC8ULL, 
            0x2C171A3C12628A3CULL, 0xDFF78585537DBCCCULL, 0x9BB1F815D5421EA0ULL, 0xCAF0B97B49A30454ULL
        },
        {
            0x4607806DBFC95628ULL, 0x638140B70CF065B6ULL, 0xC94F2EEBB193519CULL, 0xE2F9E13122CA7829ULL, 
            0x4EFD66C59FE8F254ULL, 0xC76F1FB2B0FA88DCULL, 0x07C00677EB649345ULL, 0x11E24973AC9980F9ULL, 
            0x72595804A6C8918EULL, 0xA17563975625D051ULL, 0x555D1CF508385631ULL, 0x0E5873A5089BC4E5ULL, 
            0x371F7530D9AC1078ULL, 0xFB06D16AF8B53E18ULL, 0xF556E386A91EBD56ULL, 0xFAD308A15C1F92A8ULL, 
            0xC552B07D5A3A9B62ULL, 0xD5231052A3F56E6DULL, 0x940ECD83872F3AB3ULL, 0x9FF9B26FDA4CE3B7ULL, 
            0x54523D526E501AF5ULL, 0x590710FC3438FCB5ULL, 0x4E45777B24A1F9F0ULL, 0xA31C719D825FCF79ULL, 
            0x8F6045A725795EBFULL, 0x58DCD438D5C4BC85ULL, 0xCDE5823BFB129B63ULL, 0xDA9D0DA30DD10F66ULL, 
            0x3F876871622880D7ULL, 0x0518CB262733961BULL, 0x41C67BAF2D5AB304ULL, 0x5906A0A6993CD427ULL
        },
        {
            0x2FB1F572C7810CF8ULL, 0xF85D4527F64876DBULL, 0x5158A569447A62D7ULL, 0x6F761F8BD861D69BULL, 
            0x913778E9438874F2ULL, 0x982BAF17BE3E74C1ULL, 0x5D72AF99E25A0527ULL, 0x08C0EFCC800CECACULL, 
            0xA98FA42B5EE945EEULL, 0xF6F5602102AC6396ULL, 0x3950775407E9681EULL, 0x739AF63EE82997F2ULL, 
            0xD835DAA1B60E26CEULL, 0x43EC09823672B3A4ULL, 0x0BB9E31B1395D25BULL, 0x70038F5B5505B718ULL, 
            0x45D542BF54CAFF1EULL, 0xF1F97F31F965C8E1ULL, 0xD0B896BA78D090A8ULL, 0x7CB0C32434F33E78ULL, 
            0x767258BD86E88445ULL, 0x8B7210C9C139D061ULL, 0x49D34ACF89AD8123ULL, 0x1C7A8EF705846DDBULL, 
            0x1CA98D378598953BULL, 0x27275AC2DCBB66D2ULL, 0xDB3552FF8F9BA8B3ULL, 0x6BF28DE12CF493F1ULL, 
            0xA0215D603A839E5BULL, 0x3B91A4BB1D5B19EBULL, 0xE2403A0162D1D910ULL, 0x3C0D44955795EF45ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseGConstants = {
    0x87BCF26B489B8B9FULL,
    0x5A6F88813B405147ULL,
    0xC19847985B130307ULL,
    0x87BCF26B489B8B9FULL,
    0x5A6F88813B405147ULL,
    0xC19847985B130307ULL,
    0xCF792AF672AC3A98ULL,
    0xB297BD5F626897FCULL,
    0x52,
    0x9B,
    0x7B,
    0x4F,
    0x1A,
    0xD9,
    0x7E,
    0xB1
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseHSalts = {
    {
        {
            0x0243BD64FA69AA2EULL, 0x0AFAEB6DA510056BULL, 0xE8FC56238EB97EB7ULL, 0xCF0E625F4A46BF25ULL, 
            0xD2A048DB7108DEC5ULL, 0xC6757365D19BEDC7ULL, 0xBB3D05B4F8A058DFULL, 0x0A842F786EDFF4AEULL, 
            0x6DDA5FE8DAF76091ULL, 0xFD5AFDE5B45BD6FFULL, 0xC0F3B5833F840753ULL, 0x2F649439EA540C3DULL, 
            0x9255798C6AAD5BD8ULL, 0xCF7AABD034111C2CULL, 0xE2FC697530FC4D61ULL, 0x89618D5BAC68A088ULL, 
            0x779418ED2AF991E0ULL, 0x9D1BE6BCBB84D9FAULL, 0x707476FA8738CF61ULL, 0xB85ED3F05AAE1890ULL, 
            0xA9296B82633062BAULL, 0xF8236950302E435EULL, 0xF5FB12E9A3237652ULL, 0x3D06248E4250015CULL, 
            0x16A6C57566D34E64ULL, 0xEE8C6F9E4ED397D8ULL, 0x339A97FBE6FEB3F1ULL, 0x79D3D84E04A658B8ULL, 
            0xE794958C89574A25ULL, 0x2B04CED35068F16AULL, 0xDF4C0661EA8DDC01ULL, 0xC43A7DBB6BE049FCULL
        },
        {
            0x32D53C27FF8D1C58ULL, 0x8A6F83ACE499AC5FULL, 0x84BEBC16A7168271ULL, 0xB7DC978558F7AB05ULL, 
            0x97390BA65B8B3FC4ULL, 0x67F5EA1FCD8B961EULL, 0x8898E3852F612FF5ULL, 0x3281C87F06A8765CULL, 
            0xF177A1CB104BEA6FULL, 0x2568B35B9B04BA2FULL, 0x0273B86A55A1E3AAULL, 0x616B1FE6A8D13634ULL, 
            0x03EFC7D95A156C95ULL, 0x72047F97DEFD66BDULL, 0x19893D634267D06FULL, 0xAFE07CEC97C81BF9ULL, 
            0x5C533A3AECEA7C80ULL, 0xBA6F2827CC5F4BDBULL, 0x33B2C8C20612F6EBULL, 0xACEFA42F4FCF717FULL, 
            0x2DF754BB98A4CD1AULL, 0x5D00C059625D92B0ULL, 0x8E801556600D2D42ULL, 0x7CF3438DD1F991DEULL, 
            0x693FFCF570C4184AULL, 0x95B4357A369A6452ULL, 0x739016E249BA0875ULL, 0x7512A953AC428D52ULL, 
            0xCA87A0F2C5C47F3EULL, 0x613B2D068CC18000ULL, 0x0BF0F2FF0419551EULL, 0x03E2663064CD8434ULL
        },
        {
            0x04F5DC1969E4069BULL, 0xF072844EB8E25304ULL, 0xD648EB575D17A539ULL, 0x2A980706604166F8ULL, 
            0xC110DE3801C689BAULL, 0xC74193F2538F1C05ULL, 0xE46D0468CBC622C6ULL, 0x6C342F42082DE680ULL, 
            0x6E5A8D4D9BEC95FFULL, 0x308A3B99D6E906EFULL, 0x7B102F3D4908E33BULL, 0xD5604483F5A21E4BULL, 
            0xAD1435D53832B7B8ULL, 0xC1030943A46177BEULL, 0x5876C7147DC415C8ULL, 0xD618B065AB999565ULL, 
            0x13B6EA7876C7B772ULL, 0x43223BAD26D76670ULL, 0x99DFA1AE1D57DCCCULL, 0xB90FBC735FBC2166ULL, 
            0x18DA98625CA17D84ULL, 0x504E0BF4BFF527A1ULL, 0x9C74947CBF36B04AULL, 0xEDB3E7F155DAD869ULL, 
            0x7F739917C4741205ULL, 0x21B707321D056587ULL, 0xE9D205B14A4BF9F1ULL, 0x47809FF24D90FD71ULL, 
            0x1F1C0CF3D7EA663EULL, 0x32CA870AE52FE515ULL, 0x16C4A445DC9CA159ULL, 0x5AA8C4D431F4D4D9ULL
        },
        {
            0x17643C0009EE3C6BULL, 0x2944A7F2E237BEF7ULL, 0x72FF04011978CBA9ULL, 0x95164970FB2475E9ULL, 
            0x5C10C3974F0AE787ULL, 0xC120171CCD7E4C99ULL, 0xA81F67235233D928ULL, 0x6276279A5E0DB16DULL, 
            0x0E419DC6613965C5ULL, 0x0786B4714D32D19AULL, 0x0361127FB2EE8514ULL, 0x76AC43CD409913E7ULL, 
            0xA85789B30463A6B5ULL, 0x1B10A23B145E1DCFULL, 0x4898FC51CC00C2E1ULL, 0x8C0A9238F6FFA868ULL, 
            0xBDB4C438D0E3EA29ULL, 0x695F85AFFA119116ULL, 0x1FD472F06EFA1E74ULL, 0x46F554846EA80D7CULL, 
            0x14CC0B2F9C1B221FULL, 0x4EF5146701DE23C3ULL, 0xDCD49A3FA66AB38CULL, 0x53830E4722C69157ULL, 
            0x81A6B98D5B4349BFULL, 0x6148F00862B1C3A1ULL, 0xCC76195A28ADBDFAULL, 0x17D59BDEB33C32A9ULL, 
            0x2C11E4AB9F4CBAD1ULL, 0xCA4414233F04D0BCULL, 0x44D1527B7A3141B7ULL, 0x709A0F819E37799BULL
        },
        {
            0xBA76900205556E3EULL, 0x2EE36A3EDF787716ULL, 0x9B995C49C0728E34ULL, 0x833F327928A32C22ULL, 
            0xE99E8628C4C485EFULL, 0x06EC418DA809AF24ULL, 0xC4963170F8536FE5ULL, 0x2764441FBDEF5BC4ULL, 
            0x989E162DC3464E5FULL, 0x397ED711649FD83DULL, 0x652DA1C6DEFF78B3ULL, 0xEA605580988753F4ULL, 
            0x99CE01E90670408CULL, 0x8C9B3C46B5C4CA66ULL, 0x769DDE16842205C0ULL, 0x9FE8BFAFF6EBC06CULL, 
            0x4C9758C4467A2E88ULL, 0xF456BC70D45FE4B9ULL, 0x09C97E2DFECA7577ULL, 0xE10C2BAD27CDB108ULL, 
            0xBA86CCB353B8FD72ULL, 0x9D1C89D0E30E7062ULL, 0xE2D58F65AF822EBDULL, 0x26BC405DB5F50970ULL, 
            0xDD5846F1A0EB54A2ULL, 0x86AE23DC19CF5414ULL, 0xFA18C7DF5D910D51ULL, 0x76DEA4B0A80E6C7DULL, 
            0xBF698D76F490C6ECULL, 0xD7048A8C24C005CFULL, 0xE2FDA391493ED701ULL, 0x8E22F41F5E8353F8ULL
        },
        {
            0xF16C345ABB4F55C8ULL, 0xA1D0B499A7690AACULL, 0x5F4CA5B9E47380F9ULL, 0xDFD48E37D78691F2ULL, 
            0x1DCB05D63F228FACULL, 0x32D4F977AA632D13ULL, 0x26430201C38295A4ULL, 0x87597AB726CE6EC0ULL, 
            0x36103B29EACCD0EDULL, 0x9B99DB7EC0D87A04ULL, 0xEA3A50A7EFB06C03ULL, 0x968D259E75518243ULL, 
            0x7D4D709B2D9FFDADULL, 0x3DBC22F6A5F05647ULL, 0x7DFC50A74DE2B3F4ULL, 0x9A16DC36C66591B5ULL, 
            0x1BDC20F889CA811EULL, 0x94D4A5CDE80FA797ULL, 0x5110D121DE740A0FULL, 0x643FE8388C7B9266ULL, 
            0xF0BD4CDA94CB142EULL, 0x4ACCF590DB8DE445ULL, 0x335D5CBF08A12159ULL, 0xDED23E995A587C20ULL, 
            0xC1CB7F584754F789ULL, 0x76F7D2DA289F748AULL, 0xB0B3B51B2F038A28ULL, 0xB346ECBB1F76B0CCULL, 
            0x293B738E2758540EULL, 0xAD351B34DFA1C5FDULL, 0x49E25BC8D2802AD8ULL, 0x86E74EC18E62AF78ULL
        }
    },
    {
        {
            0x06D4DC3A448DDFF9ULL, 0x52EEBA7F04DDF672ULL, 0x9796C081FF6327D3ULL, 0xD871ACF6A68E2065ULL, 
            0xA6484A24046A4E62ULL, 0x1233925EC45F48AFULL, 0xE8D2802A04E7B61DULL, 0x4D61DAF93143D9A8ULL, 
            0x170B623129115D70ULL, 0x75F09AD47EA62DCAULL, 0x8F45396A82501E41ULL, 0xC67872CE149DC24DULL, 
            0xCF22ACD862E83B09ULL, 0x611B04921DFE0116ULL, 0x282D6844EFC961A6ULL, 0x00CB0F303F401840ULL, 
            0x773E220EEF67FADFULL, 0x5BF37B44B94646A2ULL, 0xDC64E7C15BF39A78ULL, 0x3EBE80FF7AA95591ULL, 
            0xB7C8B6CBD6A06F6DULL, 0x246DE1D207FB70C9ULL, 0x0D83D0BD9FF2D20DULL, 0x2D8D0C7853478AB5ULL, 
            0x28C6E8FD74BAC102ULL, 0x4C0B307B43B87B86ULL, 0x156EA39DDF143F33ULL, 0x6B2E9FEE4B8C5AA4ULL, 
            0x53C41D9299283B6BULL, 0xE65ADC41C9B59315ULL, 0x19D9817BEFDC03DFULL, 0x8D2310114AB8CB76ULL
        },
        {
            0xED82C8F7A62372F0ULL, 0xD36480382B1C97E2ULL, 0x9ED8BA5EFE9C28D5ULL, 0xC203021F28A5CBDBULL, 
            0x7431B912415F3431ULL, 0xFA9E41759A54C1C1ULL, 0x55543979DBE7640BULL, 0xFE63667925428547ULL, 
            0x6FE325FF095F7640ULL, 0xF9AB92E02EA36E31ULL, 0x68AE183352D18476ULL, 0xFEA930371424F9E7ULL, 
            0xE570DACB61C291C9ULL, 0xDA036D3332A72F91ULL, 0x9A07D9708550D77DULL, 0xBB620CB20496DBBDULL, 
            0x8659E6F82B6FB0E8ULL, 0x2D636B18734C8ABDULL, 0xA2ABA67C3E89E046ULL, 0x2625F523B9148042ULL, 
            0x2C2FA073D62F53B6ULL, 0xF8019DB303C3387DULL, 0x88D7B2F1B0A330EEULL, 0xC7D27D9E9BC87780ULL, 
            0xCF36E5C0DE5BCE06ULL, 0xB229137DA2558A92ULL, 0xE3CEB460F21FF16DULL, 0x922EDFFD174418C6ULL, 
            0x1BDFF60744E9371FULL, 0x57A5163BD18E4B1DULL, 0xE8A6EF074F74DF97ULL, 0xB54E2B07D9BB7733ULL
        },
        {
            0x66831B391242DD8DULL, 0x08005734D53823E2ULL, 0x186D65D6316830E8ULL, 0x235746E77DD15016ULL, 
            0x79834BCF9830032EULL, 0x42F37A5EF2CD2FE3ULL, 0x4104560792EE283BULL, 0xAEBC1526E8AF1EB6ULL, 
            0xA286591EEFE95779ULL, 0x00FFF24E27049FAAULL, 0x59911C9270CBFA9CULL, 0x3FC20BE02C8E7235ULL, 
            0x808149F98197D112ULL, 0x7257F61580D62020ULL, 0x975C32AEAD18E330ULL, 0x2E047420EB0536E9ULL, 
            0x71F0AA6F5E3D7DE4ULL, 0xA4963A49D0E709A8ULL, 0x53EFD5B6A7FA954CULL, 0x36DF5193FFC8DBEFULL, 
            0xBFC4B614C0508DA6ULL, 0x61D0934E0E2E0542ULL, 0x432172D95C52E59CULL, 0x814DF83F8410EACBULL, 
            0xBA41569B999DA199ULL, 0xDA4E90BBDEE8172CULL, 0x46122D91DBC4A982ULL, 0x941D8651C36DE278ULL, 
            0xBED6BDBE5D4E6754ULL, 0x9314C62544585DD6ULL, 0x93F00FFCC58B853DULL, 0xFFEEC4D008819A2FULL
        },
        {
            0x4F2917D09E123A09ULL, 0x5C7BDB09A8A85D36ULL, 0x42513712876459D3ULL, 0x50EC387345E067FDULL, 
            0x203DC0DC9BEE7983ULL, 0xE40D350387DF6F1DULL, 0x8D2AA4CCE7715EEBULL, 0xFC9453880F27C8F1ULL, 
            0x33B7C05889F0431CULL, 0xC68750BF6E02AEB6ULL, 0xE1B328E4EC152B4CULL, 0xC31C6182E706D5A8ULL, 
            0x9157711FACEAB2C5ULL, 0x08248D662B7EC49FULL, 0xB9F88ABA44A41C00ULL, 0xA69FBC463E480FCAULL, 
            0xC36A12A020D9EE44ULL, 0x0C82018D0915AEBBULL, 0x25B646F0F43D9736ULL, 0xD6DEE3D80C1B12FDULL, 
            0xE21C8FDA20608846ULL, 0xA604508240B0F0F0ULL, 0xD137B57F64D36E05ULL, 0x7F1F396851FAD4B5ULL, 
            0x2EB6E72EC02F47DBULL, 0xDCBBCF0D5A3658C4ULL, 0x6A1737E92F402812ULL, 0x0BB4E00D8FDCAE16ULL, 
            0x74304CD75FA28548ULL, 0x3AFF990754E81C96ULL, 0x17363D944192F1EFULL, 0x4FD576480536EB56ULL
        },
        {
            0x67678CEA33C1BC15ULL, 0xAADCFEF3CDFE8BC8ULL, 0x76E75C3E1CF1EDE9ULL, 0xAA0B3F305E06704DULL, 
            0x76CFE448278C5D8EULL, 0x3AF83DDC8D4A50BDULL, 0x65D057C59D0AC62AULL, 0x9738A12574E11AF2ULL, 
            0xFB81E6F0ED8B6C9EULL, 0x5078EB8A41224D86ULL, 0xB14FCF0E39C2DD5DULL, 0xE9B85E37C17941C7ULL, 
            0x38BEFEB459D13C10ULL, 0x5E80BA33CA97E2B4ULL, 0x840130AE5F67C793ULL, 0xC1586C46FD9CD1BBULL, 
            0xDA81B37CC376D984ULL, 0xFFA7BE86016503FCULL, 0x1A6A96A5495C36A2ULL, 0x1D37F603EF30215DULL, 
            0xD1D83F450B9A3262ULL, 0x94B647E20C147FE3ULL, 0xB99EFDE4CAB700F9ULL, 0x90F33547FA12494FULL, 
            0xDAEFBA68E2330697ULL, 0x10321A0D074C33FBULL, 0x2CDC22C75D85EA0BULL, 0x8754A9B1AB7DBD4DULL, 
            0x99D3FA6CF829B2F0ULL, 0x6073E438832B2506ULL, 0xC0E7B1F0A7DCC6DAULL, 0xEB148656C0F68A9FULL
        },
        {
            0x7870D85FE4BA4EA4ULL, 0xBD9A7B0260044F61ULL, 0x41C258C88B5987C7ULL, 0x5CBA41DB41720A6FULL, 
            0xC830B098D772F6F2ULL, 0xF7A5CAC0773E740DULL, 0x1D7AD0BFB3F26514ULL, 0xB2A95B681CC0BB96ULL, 
            0x929E32083A930CB1ULL, 0xF8623AD5FCBC658BULL, 0xA6C95E66FFF1F2ACULL, 0x19BDA27C11B4ACD3ULL, 
            0x7336AA3ECBBF47BDULL, 0x695F872C0209E185ULL, 0xD0327AEEE4134684ULL, 0x765143F782A5CAFEULL, 
            0x48F4FB2E746BF074ULL, 0x49B114C1165B3450ULL, 0x0D2AE0B51FA01EF4ULL, 0xF7FACF507288D64CULL, 
            0x10DAA7EA9A145637ULL, 0xB3621EBAB6A18881ULL, 0x617FF7645F16190CULL, 0x121DE27F2CBE3BE1ULL, 
            0x95C0F27392758DE7ULL, 0xFD414CA8B23FFAA9ULL, 0xD5004F55ECAD872AULL, 0xF9745B7BAE9585AAULL, 
            0x286A9AED2184CB84ULL, 0x2AE87A13184217F5ULL, 0x4041F30238B5FDF7ULL, 0x96DF4BCFFADFD5E4ULL
        }
    },
    {
        {
            0x9D7919D355656009ULL, 0x19C5A5463084F0D7ULL, 0x2E26485531FF4407ULL, 0x90DB349035923957ULL, 
            0x9D77D6774FAEA3B8ULL, 0x288AE24D40C098FEULL, 0xD0CA5887B7B9039DULL, 0x7C0A66332DE564E4ULL, 
            0xA0FC15978B4C5390ULL, 0xB48A52A6A387AB0DULL, 0xB075AFC7EBCC730CULL, 0x43ED4D79A5F4391FULL, 
            0x67A4D33E1BC08551ULL, 0x3455E5E206A1FD54ULL, 0xBB2D06C216646819ULL, 0xF087FAF8FACDC606ULL, 
            0x92715F9EDC293943ULL, 0x930FA1955D9396F3ULL, 0x9E77EF08662B178AULL, 0x8C29828365831B65ULL, 
            0x81941BD592DAF8ACULL, 0x6E5565C44C0AC6FEULL, 0x2927449F386DB691ULL, 0xCA281B324732982AULL, 
            0x3DB43FBFE5BD20F5ULL, 0xE9A971638A532837ULL, 0xE5035E5570B1AE4BULL, 0xAD520074780717EDULL, 
            0x974B77C9D4A548D1ULL, 0xE23B477D35EC6095ULL, 0x25A020C3AEC16A2CULL, 0xDA4C33C6F896162DULL
        },
        {
            0xDF128A893BB49A28ULL, 0xB1E8B614808DB68FULL, 0x6D3254E3C189E0FDULL, 0xF8D159C2C52AB4F1ULL, 
            0x03E27FF6BDCB395FULL, 0xD44C8AF3444B84F4ULL, 0xB16AA595BCD896FFULL, 0x5601B9FE9C103D4EULL, 
            0xCD03E4BED49BD679ULL, 0x576DBC3054B6C106ULL, 0x93A627F423269565ULL, 0xE8C69F59C3DEA231ULL, 
            0xA5DEF2623E5192DBULL, 0xA371B44E6DDAA64FULL, 0xC83CAD562F442560ULL, 0xFCB34A380F6DEE24ULL, 
            0xA4B5557021487F69ULL, 0xB6124C93621915E2ULL, 0xBA97B089FB6F37A9ULL, 0x59C9431CEACE8411ULL, 
            0x986703DA4BB1BBA8ULL, 0x3D4A6B0937064393ULL, 0x9EB410709071D2A4ULL, 0xA879FB2D637FF5B6ULL, 
            0x0F05B32C65C24326ULL, 0x3CEF301E54ACDA3CULL, 0x4EF8D61F6073A8FEULL, 0xCF22C806B3B03529ULL, 
            0x0007FD8E175FB944ULL, 0xA442F97274F1BB70ULL, 0xC0DAA87CF31AA239ULL, 0xA50E405452078B54ULL
        },
        {
            0x9A08649164B34DC3ULL, 0x84D0319147C09A31ULL, 0xEFE82D85C4C6A808ULL, 0x4C92563E453BAC67ULL, 
            0xEA844488F6555004ULL, 0xE20D717CB1859153ULL, 0x425A951B49697ACCULL, 0x0046F3058A1972DBULL, 
            0x52F930DB58EBBAB1ULL, 0x19B3B5C51AE19901ULL, 0x3599C31BC6D0B526ULL, 0x426D69BEC4EFA39BULL, 
            0xF7649E86E0D5A1A9ULL, 0xD948C5419356695AULL, 0x969C78CBC068AB27ULL, 0x76F0A275ED2440DCULL, 
            0x2216A3EFB35AEF5BULL, 0x0B983D8EC6E21C24ULL, 0x188CA25CA8C90849ULL, 0x9690C06382B47353ULL, 
            0x146025DA120CA42CULL, 0x5744E1FBA6870744ULL, 0xB339C41966DE5D03ULL, 0x29C4578905103222ULL, 
            0x23F1696375F216C0ULL, 0x1D99941139CAB9D9ULL, 0x66698C451BD11986ULL, 0x6419BCDC5096DD8BULL, 
            0x4B5D48AF30BE2432ULL, 0xF63CB8A666A33A15ULL, 0x20686725A0924890ULL, 0x72CC657B8778A95FULL
        },
        {
            0x17A44E5019E69A42ULL, 0x10EA96B1477F9DD1ULL, 0x2435476EB9EC783CULL, 0xA9999743F034D43BULL, 
            0x6F79F68BD47803F6ULL, 0xFE72968CEC919215ULL, 0xE04027E558BDD890ULL, 0x4B35586B132D6C60ULL, 
            0x9936FF08B76D7053ULL, 0x70D0FD27B1DB8601ULL, 0x7D26088FB67D7EA2ULL, 0xAED0CC11AAC3C4AEULL, 
            0x9A655E3F1ECB7D06ULL, 0xDF66CE5A7EF26014ULL, 0xE4F740A0B9E9A0C7ULL, 0x42B490C6FA5B81EDULL, 
            0x39B417EDA34C9E03ULL, 0xC8EFEDA99CC0508DULL, 0x7E12E03990298209ULL, 0x9AEBCD870812668AULL, 
            0xFE0547A9639A1843ULL, 0x123D5024A64F8A69ULL, 0x2B0049BEC7DD6574ULL, 0xB4542B6E5DC8A124ULL, 
            0x004362216F13E646ULL, 0x0F161E26F600BF24ULL, 0x17C2A91FB8520A24ULL, 0xC77EECD0CD386DD1ULL, 
            0x563B95B5B31DA764ULL, 0xFD8BD812D26B6853ULL, 0xD0240C23D4498564ULL, 0xF1C9DB230EF3D734ULL
        },
        {
            0x09CA72B42C8898A5ULL, 0x61CA4A216DF40DC7ULL, 0x4DCDA7B1FDF27E59ULL, 0x93923812BFFF74F5ULL, 
            0xF2709AA9207D18BCULL, 0x6838E00BB29FBC9EULL, 0x5A803A3CD07E61E7ULL, 0xE7B459EB47EEBC92ULL, 
            0x5EBF87D7CB31F864ULL, 0xD2631D969C086B2EULL, 0x73A91DD0E9B49C87ULL, 0xC07D503274A0DE5BULL, 
            0xEE5981FDA56F58BCULL, 0x2DD6FD8045C059DEULL, 0xF4AA3D1CB57BF8BEULL, 0xA7E1251FF6E9EB00ULL, 
            0xDE53E66A0BE3BD92ULL, 0x7DA050918ACE48BFULL, 0x662F25D56CA1C0F0ULL, 0xD2C101610F8124CAULL, 
            0x0DB07C37516F27B6ULL, 0xD7688CB3B43D97ABULL, 0x9AFAD0F3E8449549ULL, 0x84236D663F31D72EULL, 
            0x1238DC320FD88106ULL, 0xEE1D740C98B1DBEDULL, 0x64F0118E87219021ULL, 0x98C6F330EFCBABC7ULL, 
            0x2B18FCED193EF2A2ULL, 0xEB51E26FF92A9F79ULL, 0xEBBF34663A052434ULL, 0x47D4168F58AB235FULL
        },
        {
            0x3E9C8039BF907C56ULL, 0x236E158C0D56F0CDULL, 0x4779B978E7A70FE3ULL, 0x179CFDFD08C5A1AAULL, 
            0xB9C71C9CC45C3E7DULL, 0xFC6BDF167FC70434ULL, 0xE6D91D3E0C852076ULL, 0x20E66A6FFC2C4D9CULL, 
            0x4F483EE6C81D5A24ULL, 0x3050332E8574F9B9ULL, 0xC068D7E5A34EEF9CULL, 0xDCA1EED986DE8B0EULL, 
            0xD982B7A83DE6FEB2ULL, 0xFDDC056146C5A6ABULL, 0x6AB760A722D74C7EULL, 0xE1676EBB548106EAULL, 
            0xB7176623665E3DD6ULL, 0x31E99A0D7D1EDB6CULL, 0x891D2CCAF8C32DD6ULL, 0xA7633A2CAE3AA28EULL, 
            0x3A6C176E57D46608ULL, 0x931E77810BAB309DULL, 0x380BE169BE09FE31ULL, 0xEC525C799B3A99F0ULL, 
            0x87FDDD74757E88BFULL, 0x6BCB25FC4D77E75FULL, 0x62EC425253F70D70ULL, 0x5923EC50F8A8B523ULL, 
            0x5ED0EE1E09CD6588ULL, 0xEFEF6B551E556A00ULL, 0x37674FB744A301A4ULL, 0x651E2168FF67F8C8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseHConstants = {
    0x0F1ACC04642BB82FULL,
    0xEA0B5F909D30D27CULL,
    0x7F71697A2475372DULL,
    0x0F1ACC04642BB82FULL,
    0xEA0B5F909D30D27CULL,
    0x7F71697A2475372DULL,
    0x718C3A4E82C1FE0DULL,
    0xE14E6F095281EE03ULL,
    0x54,
    0xFD,
    0xA2,
    0x54,
    0x86,
    0xA2,
    0x0E,
    0x84
};

