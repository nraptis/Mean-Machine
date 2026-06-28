#include "TwistExpander_Greezy.hpp"
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

TwistExpander_Greezy::TwistExpander_Greezy()
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
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
}

void TwistExpander_Greezy::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  std::uint8_t *pSnow) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xEA20ECC629F831B7ULL; std::uint64_t aIngress = 0xDD2F918E84BF6D49ULL; std::uint64_t aCarry = 0x9FACD73EF6C2BF29ULL;

    std::uint64_t aWandererA = 0xDE584C84C268B982ULL; std::uint64_t aWandererB = 0xF5D01BF5F80130EDULL; std::uint64_t aWandererC = 0xD286839AEB4C3617ULL; std::uint64_t aWandererD = 0xFDFEE42F9BE98F4CULL;
    std::uint64_t aWandererE = 0xB4FF3EFE48A767FCULL; std::uint64_t aWandererF = 0xBFEBC6C8FB99BB46ULL; std::uint64_t aWandererG = 0xF0D7105BBC4DECD4ULL; std::uint64_t aWandererH = 0xF43D26146E9125D6ULL;
    std::uint64_t aWandererI = 0x96D8B528977B8B5AULL; std::uint64_t aWandererJ = 0xBF8716F41BB4DAB3ULL; std::uint64_t aWandererK = 0x8DD18396385B94CDULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    {
        aPrevious = 12163485037664135244U;
        aCarry = 9813233460423988669U;
        aWandererA = 11936860041153688092U;
        aWandererB = 9915025676773819905U;
        aWandererC = 16231959308596510859U;
        aWandererD = 17187623732131582470U;
        aWandererE = 11694652761491216464U;
        aWandererF = 13262244067014862228U;
        aWandererG = 14438335430071864962U;
        aWandererH = 9354696266977017198U;
        aWandererI = 10257291898717315826U;
        aWandererJ = 18382760809809056604U;
        aWandererK = 11590393726114465010U;
    }
    //
    // ---------------------------------------------------
    // KDF_A_A kdf_a_loop_a:
    // ---------------------------------------------------
    // read from: source, snow
    // temp storage: fire_a, fire_b
    // ---------------------------------------------------
    // write to: fire_a, fire_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_A_A(pWorkSpace,
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
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: fire_c, fire_d
    // ---------------------------------------------------
    // write to: fire_c, fire_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_A_B(pWorkSpace,
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
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_A_C(pWorkSpace,
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
        TwistDiffuse::DiffuseWithDomainWords(aWorkLaneA, aWorkLaneB,  // input lanes
                         aExpandLaneA, aExpandLaneB, // output lanes
                         aOperationLaneA, aOperationLaneB, // index shuffle seeds
                         aOperationLaneC, aOperationLaneD, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aWorkLaneC, aWorkLaneD,  // input lanes
                         aExpandLaneC, aExpandLaneD, // output lanes
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
    // KDF_A_D kdf_a_loop_d:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_A_D(pWorkSpace,
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

void TwistExpander_Greezy::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xA6A238E9C89EE929ULL; std::uint64_t aIngress = 0xF8D43D7C51F77FB8ULL; std::uint64_t aCarry = 0x959B97656F283C59ULL;

    std::uint64_t aWandererA = 0xDF9CC59B30467FE9ULL; std::uint64_t aWandererB = 0xBC0C80CDB45914E9ULL; std::uint64_t aWandererC = 0xC1B5FA46FCB16775ULL; std::uint64_t aWandererD = 0xAD081E3266771716ULL;
    std::uint64_t aWandererE = 0xB75131236F9EB328ULL; std::uint64_t aWandererF = 0xA58AAD247AFBBE3CULL; std::uint64_t aWandererG = 0xBB8058FB32BDD52DULL; std::uint64_t aWandererH = 0x9AF150B92841BBEBULL;
    std::uint64_t aWandererI = 0xD042E124A7A60475ULL; std::uint64_t aWandererJ = 0x9204B6A21C1E3D1FULL; std::uint64_t aWandererK = 0xC9A82ECBC5736A33ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    {
        aPrevious = 13921206455333778537U;
        aCarry = 17784909789760209723U;
        aWandererA = 10795427070372987118U;
        aWandererB = 11346821147643989462U;
        aWandererC = 13274971618905836677U;
        aWandererD = 15216240837327746253U;
        aWandererE = 14539261762376477601U;
        aWandererF = 9877854735544110867U;
        aWandererG = 13566561667914549835U;
        aWandererH = 14370021352127075645U;
        aWandererI = 13155894750800501020U;
        aWandererJ = 14142932288429308485U;
        aWandererK = 15908891970000979748U;
    }
    //
    // ---------------------------------------------------
    // KDF_B_A kdf_b_loop_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_B_A(pWorkSpace,
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
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_B_B(pWorkSpace,
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
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_B_C(pWorkSpace,
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
        TwistDiffuse::DiffuseWithDomainWords(aExpandLaneA, aExpandLaneB,  // input lanes
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
        TwistDiffuse::DiffuseWithDomainWords(aExpandLaneC, aExpandLaneD,  // input lanes
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
    // temp storage: fire_a, fire_b, fire_c, fire_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Greezy::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength,
                                 std::uint8_t *pDestination) {
    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    [[maybe_unused]] std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    [[maybe_unused]] std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    [[maybe_unused]] std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    [[maybe_unused]] std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0xD974CE31F583A1EAULL;
    std::uint64_t aIngress = 0xBD31EDC79A6ACAC6ULL;
    std::uint64_t aCarry = 0x938011E7C16A5F7DULL;

    std::uint64_t aWandererA = 0x8C674D858AAA6A42ULL;
    std::uint64_t aWandererB = 0x995E79771470D726ULL;
    std::uint64_t aWandererC = 0x91B1A3431C52BBA5ULL;
    std::uint64_t aWandererD = 0xCD58AF68C76BD32FULL;
    std::uint64_t aWandererE = 0xC76E8CCCB3359156ULL;
    std::uint64_t aWandererF = 0xC614BB5CD2482223ULL;
    std::uint64_t aWandererG = 0xD934C2AEE6E591E7ULL;
    std::uint64_t aWandererH = 0xAC28FACB21943520ULL;
    std::uint64_t aWandererI = 0xE9272698A3546F1FULL;
    std::uint64_t aWandererJ = 0xEA1509FC69899346ULL;
    std::uint64_t aWandererK = 0x8DA153C57A744413ULL;

    // [seed]
        TwistSnow::Sha256Counter(mSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(mSource, aSnowLaneB);
        TwistSnow::AES256Counter(mSource, aSnowLaneC);
        TwistSnow::Aria256Counter(mSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneC);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts));
        TwistSquash::SquashA(aExpandLaneC, aExpandLaneA, aExpandLaneD, aExpandLaneB, aInvestLaneA);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase B
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneB);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneC, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts));
        TwistSquash::SquashC(aExpandLaneD, aExpandLaneA, aExpandLaneB, aExpandLaneC, aInvestLaneE);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneC, &(pWorkSpace->mDomainBundle.mPhaseBConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase C
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneA);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts));
        TwistSquash::SquashB(aExpandLaneD, aExpandLaneC, aExpandLaneA, aExpandLaneB, aInvestLaneH);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(pWorkSpace->mDomainBundle.mPhaseCConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase D
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneD);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(mDomainBundleEphemeral.mPhaseDConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseDConstants), &(mDomainBundleEphemeral.mPhaseDSalts));
        TwistSquash::SquashB(aExpandLaneD, aExpandLaneC, aExpandLaneA, aExpandLaneB, aInvestLaneF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(pWorkSpace->mDomainBundle.mPhaseDConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase E
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneC);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneC, &(mDomainBundleEphemeral.mPhaseEConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseEConstants), &(mDomainBundleEphemeral.mPhaseESalts));
        TwistSquash::SquashC(aExpandLaneB, aExpandLaneD, aExpandLaneA, aExpandLaneC, aInvestLaneD);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneC, &(pWorkSpace->mDomainBundle.mPhaseEConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase F
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneB);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseFConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseFConstants), &(mDomainBundleEphemeral.mPhaseFSalts));
        TwistSquash::SquashA(aExpandLaneD, aExpandLaneB, aExpandLaneC, aExpandLaneA, aInvestLaneC);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA,
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
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseFConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase G
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneA);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(mDomainBundleEphemeral.mPhaseGConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseGConstants), &(mDomainBundleEphemeral.mPhaseGSalts));
        TwistSquash::SquashA(aExpandLaneB, aExpandLaneA, aExpandLaneC, aExpandLaneD, aInvestLaneB);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA,
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneD);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseHConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseHConstants), &(mDomainBundleEphemeral.mPhaseHSalts));
        TwistSquash::SquashC(aExpandLaneC, aExpandLaneB, aExpandLaneD, aExpandLaneA, aInvestLaneG);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseHConstants));
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
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_A(pWorkSpace,
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
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: invest_a, invest_b, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_B(pWorkSpace,
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
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_C(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
    {
        TwistDiffuse::DiffuseWithDomainWords(aWorkLaneA, aWorkLaneB,  // input lanes
                         aExpandLaneA, aExpandLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aWorkLaneC, aWorkLaneD,  // input lanes
                         aExpandLaneC, aExpandLaneD, // output lanes
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
    // GSeedRunSeed_D seed_loop_d:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    // write to: work_a, work_b, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_D(pWorkSpace,
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
    // GSeedRunSeed_E seed_loop_e:
    // ---------------------------------------------------
    // read from: invest_a, invest_b, invest_c, invest_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: snow_a, snow_b, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_E(pWorkSpace,
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
    // GSeedRunSeed_F seed_loop_f:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    // write to: snow_a, snow_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_F(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseGConstants.mMatrixArgD;
    //
    {
        TwistDiffuse::DiffuseWithDomainWords(aExpandLaneA, aExpandLaneB,  // input lanes
                         aSnowLaneA, aSnowLaneB, // output lanes
                         aOperationLaneC, aOperationLaneD, // index shuffle seeds
                         aOperationLaneA, aOperationLaneB, // operation seeds
                         aIndexList256A, aIndexList256B, aIndexList256C, aIndexList256D,
                         &mMatrix,
                         aDomainWordMatrixSelectA, aDomainWordMatrixSelectB, // matrix select
                         aDomainWordMatrixUnrollA, aDomainWordMatrixUnrollB, // matrix unroll
                         aDomainWordMatrixArgA, aDomainWordMatrixArgB, aDomainWordMatrixArgC, aDomainWordMatrixArgD); // matrix args
    }
    {
        TwistDiffuse::DiffuseWithDomainWords(aExpandLaneC, aExpandLaneD,  // input lanes
                         aSnowLaneC, aSnowLaneD, // output lanes
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
    // GSeedRunSeed_G seed_loop_h:
    // ---------------------------------------------------
    // read from: snow_a, snow_b, snow_c, snow_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    // write to: work_a, work_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Seed_G(pWorkSpace,
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

        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, pDestination);
    //
    // ---------------------------------------------------
    // GROW_A grow_key_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

void TwistExpander_Greezy::SquashInvestToKeyBoxes() {
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if (pWorkSpace == nullptr) { return; }
    [[maybe_unused]] std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    [[maybe_unused]] std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    [[maybe_unused]] std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    [[maybe_unused]] std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    [[maybe_unused]] std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    [[maybe_unused]] std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    [[maybe_unused]] std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    [[maybe_unused]] std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;

    // key_box_a row 0
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 1
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 2
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_a row 3
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 4
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 5
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 6
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 7
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 0
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 1
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 2
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 3
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 4
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 5
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 6
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 7
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Greezy::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint64_t pNonce,
                                       std::uint8_t *pSource,
                                       std::size_t pBlockIndex,
                                       std::size_t pBlockCount,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pNonce, pSource, pBlockIndex, pBlockCount, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xA1F59EF17A772B03ULL; std::uint64_t aIngress = 0xA23FC3F139778CF2ULL; std::uint64_t aCarry = 0xC9F246538FE0A055ULL;

    std::uint64_t aWandererA = 0xCDD81C370A992AC5ULL; std::uint64_t aWandererB = 0xB1A9FCFC97B4AE8EULL; std::uint64_t aWandererC = 0xF37C6E0809EC4D20ULL; std::uint64_t aWandererD = 0xCB6B0836033DEB01ULL;
    std::uint64_t aWandererE = 0xB0C934865A58ACBDULL; std::uint64_t aWandererF = 0x9E2AF7BA42F88160ULL; std::uint64_t aWandererG = 0xB276789B206D6EBCULL; std::uint64_t aWandererH = 0x944FD510A653C23BULL;
    std::uint64_t aWandererI = 0xE4DCC01457801A4BULL; std::uint64_t aWandererJ = 0xF281B73FB1299D9FULL; std::uint64_t aWandererK = 0xCFEF1ABC702C5983ULL;

    // [seed]
    {
        aPrevious = 17190705412922790892U;
        aCarry = 11891670197299495010U;
        aWandererA = 17404107521347400845U;
        aWandererB = 15825918454460443045U;
        aWandererC = 15411744356986664592U;
        aWandererD = 13398773953806605770U;
        aWandererE = 16829625600722575467U;
        aWandererF = 16664520905852795604U;
        aWandererG = 15646768522748887584U;
        aWandererH = 17098105876886134156U;
        aWandererI = 12240467705437113057U;
        aWandererJ = 12713809019016880734U;
        aWandererK = 18101618882640466229U;
    }
    //
    // ---------------------------------------------------
    // GTwistRunTwist_A twist_loop_a:
    // ---------------------------------------------------
    // read from: source, key_row_read_a, key_row_read_b
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Twist_A(pWorkSpace,
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
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Twist_B(pWorkSpace,
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
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Greezy_Arx::Twist_C(pWorkSpace,
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
    if ((pBlockCount - pBlockIndex) > static_cast<std::size_t>(H_KEY)) {
        //
        // ---------------------------------------------------
        // GROW_A grow_key_a:
        // ---------------------------------------------------
        // read from: work_a, work_b, work_c, work_d
        // ---------------------------------------------------
        // write to: expand_a, expand_b, expand_c, expand_d
        // ---------------------------------------------------
        //
        TwistExpander_Greezy_Arx::GROW_A(pWorkSpace,
                     &aPrevious,
                     &aIngress,
                     &aCarry,
                     &aWandererA,
                     &aWandererB,
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
    } else {
        TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    }
    if ((pBlockCount - pBlockIndex) > static_cast<std::size_t>(H_KEY)) {
        //
        // ---------------------------------------------------
        // GROW_B grow_key_b:
        // ---------------------------------------------------
        // read from: expand_a, expand_b, expand_c, expand_d
        // ---------------------------------------------------
        // write to: work_a, work_b, work_c, work_d
        // ---------------------------------------------------
        //
        TwistExpander_Greezy_Arx::GROW_B(pWorkSpace,
                     &aPrevious,
                     &aIngress,
                     &aCarry,
                     &aWandererA,
                     &aWandererB,
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
    } else {
        TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    }
}

void TwistExpander_Greezy::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    TwistExpander::GrowKeyA(pWorkSpace);
    if (pWorkSpace == nullptr) { return; }
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);

    // [grow key a]
    // GKeyFoldA grow_key_a_fold (start)
    static_assert((S_BLOCK / W_KEY) == 16, "GKeyFoldA expects 16 key-row chunks.");
    TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    {
        // read from: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
        // byte shifts: 0U, 24U, 8U, 16U; diffuse: DiffuseC
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aIndex]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aIndex]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aIndex]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aIndex]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aOperationLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 0, 0, 1, 2 with offsets 4770U, 140U, 1469U, 516U
        // byte shifts: 0U, 16U, 8U, 24U; diffuse: DiffuseA
        // write to: aWorkLaneA [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 2U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4770U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 140U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1469U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 516U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aWorkLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 3, 2, 0, 1 with offsets 5118U, 4092U, 6724U, 4738U
        // byte shifts: 8U, 16U, 0U, 24U; diffuse: DiffuseB
        // write to: aWorkLaneB [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 1U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5118U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4092U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6724U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4738U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aWorkLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 1, 3, 2, 0 with offsets 5415U, 5390U, 1678U, 1216U
        // byte shifts: 8U, 0U, 24U, 16U; diffuse: DiffuseB
        // write to: aWorkLaneC [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 0U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5415U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5390U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1678U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1216U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aWorkLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 2, 1, 3, 3 with offsets 3544U, 6360U, 4656U, 2376U
        // byte shifts: 8U, 0U, 24U, 16U; diffuse: DiffuseC
        // write to: aWorkLaneD [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 3U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3544U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6360U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4656U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2376U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aWorkLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA fragments 0, 2, 3, 1 with offsets 555U, 1309U, 357U, 659U
        // byte shifts: 16U, 0U, 24U, 8U; diffuse: DiffuseB
        // write to: aOperationLaneA [0..<W_KEY]
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 555U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1309U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 357U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 659U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aOperationLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneB fragments 3, 0, 2, 1 with offsets 1982U, 0U, 631U, 240U
        // byte shifts: 0U, 24U, 16U, 8U; diffuse: DiffuseC
        // write to: aOperationLaneB [0..<W_KEY]
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1982U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 0U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 631U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 240U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aOperationLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneC fragments 0, 1, 3, 2 with offsets 1837U, 1544U, 1710U, 524U
        // byte shifts: 24U, 16U, 8U, 0U; diffuse: DiffuseB
        // write to: aOperationLaneC [0..<W_KEY]
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1837U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1544U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1710U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 524U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aOperationLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneD fragments 3, 1, 2, 0 with offsets 238U, 999U, 41U, 160U
        // byte shifts: 8U, 24U, 0U, 16U; diffuse: DiffuseA
        // write to: aOperationLaneD [0..<W_KEY]
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 238U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 999U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 41U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 160U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aOperationLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD [0..<W_KEY]
        // offsets: 980U, 2013U, 798U, 1891U
        // byte shifts: 8U, 0U, 24U, 16U; diffuse: DiffuseB
        // write to: aKeyRowWriteA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 980U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 2013U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 798U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1891U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aOperationLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
    // GKeyFoldA grow_key_a_fold (end)
}

void TwistExpander_Greezy::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    TwistExpander::GrowKeyB(pWorkSpace);
    if (pWorkSpace == nullptr) { return; }
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);

    // [grow key b]
    // GKeyFoldB grow_key_b_fold (start)
    static_assert((S_BLOCK / W_KEY) == 16, "GKeyFoldB expects 16 key-row chunks.");
    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 3, 3, 1, 2 with offsets 4267U, 5556U, 4625U, 2922U
        // byte shifts: 16U, 24U, 8U, 0U; diffuse: DiffuseC
        // write to: aExpandLaneA [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 2U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4267U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5556U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4625U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2922U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aExpandLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 2, 0, 3, 0 with offsets 589U, 7730U, 5904U, 1061U
        // byte shifts: 0U, 24U, 16U, 8U; diffuse: DiffuseB
        // write to: aExpandLaneB [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 0U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 589U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7730U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5904U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1061U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aExpandLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 0, 2, 2, 1 with offsets 792U, 3276U, 4259U, 3205U
        // byte shifts: 8U, 24U, 16U, 0U; diffuse: DiffuseC
        // write to: aExpandLaneC [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 1U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 792U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3276U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4259U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3205U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aExpandLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 1, 1, 0, 3 with offsets 5015U, 5685U, 5693U, 3929U
        // byte shifts: 16U, 8U, 0U, 24U; diffuse: DiffuseC
        // write to: aExpandLaneD [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 3U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5015U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5685U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5693U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3929U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aExpandLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD [0..<(S_BLOCK >> 2U)]
        // offsets: 1069U, 5416U, 4446U, 3189U
        // byte shifts: 24U, 0U, 8U, 16U; diffuse: DiffuseB
        // write to: aOperationLaneA [0..<(S_BLOCK >> 2U)]
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1069U) & ((S_BLOCK >> 2U) - 1U);
            const std::size_t aFoldIndexB = (aIndex + 5416U) & ((S_BLOCK >> 2U) - 1U);
            const std::size_t aFoldIndexC = (aIndex + 4446U) & ((S_BLOCK >> 2U) - 1U);
            const std::size_t aFoldIndexD = (aIndex + 3189U) & ((S_BLOCK >> 2U) - 1U);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aOperationLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 0 with offsets 1669U, 69U, 818U, 1942U
        // byte shifts: 8U, 0U, 24U, 16U; diffuse: DiffuseA
        // write to: aWorkLaneA fragment 1
        const std::size_t aReadBase = 0U * W_KEY;
        const std::size_t aWriteBase = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1669U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 69U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 818U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 1942U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 3 with offsets 1685U, 866U, 993U, 982U
        // byte shifts: 24U, 0U, 16U, 8U; diffuse: DiffuseB
        // write to: aWorkLaneA fragment 2
        const std::size_t aReadBase = 3U * W_KEY;
        const std::size_t aWriteBase = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1685U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 866U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 993U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 982U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 1 with offsets 1292U, 1023U, 1671U, 128U
        // byte shifts: 24U, 16U, 0U, 8U; diffuse: DiffuseB
        // write to: aWorkLaneA fragment 0
        const std::size_t aReadBase = 1U * W_KEY;
        const std::size_t aWriteBase = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1292U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 1023U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 1671U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 128U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 2 with offsets 549U, 303U, 416U, 1365U
        // byte shifts: 16U, 24U, 0U, 8U; diffuse: DiffuseB
        // write to: aWorkLaneA fragment 3
        const std::size_t aReadBase = 2U * W_KEY;
        const std::size_t aWriteBase = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 549U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 303U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 416U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 1365U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA fragments 2, 3, 1, 0 [0..<W_KEY]
        // offsets: 1525U, 1964U, 137U, 1501U
        // byte shifts: 24U, 0U, 8U, 16U; diffuse: DiffuseA
        // write to: aKeyRowWriteB
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1525U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1964U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 137U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1501U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
    // GKeyFoldB grow_key_b_fold (end)
}

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseASalts = {
    {
        {
            0x329222C84607A3B3ULL, 0x9F7924B100B49751ULL, 0xEEC5D76BDAAF0E42ULL, 0xF57445BCF00F8ED9ULL, 
            0xC505382B8D5C2E88ULL, 0x550708C4EF6CC3FDULL, 0x5A65C3FEEB0E3BC1ULL, 0x9337D12ABB2312BBULL, 
            0xFCCB04D8F383746AULL, 0x9EFEBFABB734A9E7ULL, 0x119198A8C2C0AD25ULL, 0x61F6A9BEEDEE3D58ULL, 
            0x8C4231DFDD862D3DULL, 0xE45275A4461E9A0EULL, 0x5665E3459B2F0268ULL, 0x7C524C96215A328CULL, 
            0x8182B1CF32B76906ULL, 0x642ED722EA080F32ULL, 0x8DCC626CCE201C7DULL, 0xB6EAA4A92946C164ULL, 
            0x2C9511F1FAC5D364ULL, 0x3621FCDBF7C491AEULL, 0xBFCF68C565ACA4CFULL, 0x77E00A59FC386048ULL, 
            0x02930E125FC56F57ULL, 0xAA4961AD3B0184ABULL, 0xEEEA908FC4E99B46ULL, 0x5FA97A57E9A30729ULL, 
            0xD6CD57F9DAC1A1DDULL, 0xD58F1A3599CF3307ULL, 0x9509052AAD86BE38ULL, 0x088F9344C2C75F4FULL
        },
        {
            0x824EA0736D52E6A4ULL, 0x2F3B3D5E3809D3B6ULL, 0xEDFFD82E50F8A0F9ULL, 0xE68FB079DED0A820ULL, 
            0x815A868428F3CF98ULL, 0x9AF10C0FFBEE260FULL, 0x389C3E767C2798C5ULL, 0x089B6252D2FB8436ULL, 
            0x6DF1CC65113F822EULL, 0xA903F7375C9E9D07ULL, 0x66F094D1A3C06313ULL, 0x0D1A5B4219FC5886ULL, 
            0xC5D5C558600518F2ULL, 0x89D3073BE451F8CCULL, 0x022CF1DADED9E848ULL, 0x7B10E821B4844425ULL, 
            0x98938562423CB0F8ULL, 0x4EF2EDC485583782ULL, 0x1838F2CE5180EF5DULL, 0xE03BC6D6001FED5DULL, 
            0xA7D16BBD78D93063ULL, 0xFB22EF6AA1D5D6AEULL, 0x1E3BCA3CDBE0E1C8ULL, 0x531A0304D4070379ULL, 
            0x3736E91FA92D985AULL, 0xAD2806C69965E8A8ULL, 0xED973B9D80577980ULL, 0x6295A922026EE711ULL, 
            0xD123E7DBA331D7FBULL, 0x647E18D9A35BFB9CULL, 0xEDBB9238CFAB4E36ULL, 0x36339C442E40E535ULL
        },
        {
            0x7B1229D4D4D2CF93ULL, 0x13008D6D64977373ULL, 0x1EADC9ABD8C1E154ULL, 0x139B26902F39AD4AULL, 
            0x416846A1A4F39177ULL, 0x4570ABDBF6DCB44FULL, 0x3554FF04FB639AC8ULL, 0xA68DF0041FCA8C55ULL, 
            0x28C9A90FEF57198AULL, 0x30A405DEB8DA9DAAULL, 0xAC7DF2042F8E209FULL, 0x55A06F44FEAFCBB8ULL, 
            0x66D2D423C44AC52BULL, 0xF1E9D309420CCA25ULL, 0x7727D37A55D623B6ULL, 0x44C26E7C4DBCEEAAULL, 
            0x599D105B561D3E48ULL, 0x2A8BAECCE1A35BB9ULL, 0xD12CFFC966986E88ULL, 0x993D6BEE8AE250A1ULL, 
            0x6081AD27CF532932ULL, 0xFDB48CBB0F464774ULL, 0x70D6C2AF219BF4B3ULL, 0x4099E2B741631C38ULL, 
            0xEAD886FA9E078D17ULL, 0x21FF59571FE2628CULL, 0xAF5CA0575DF4E5B1ULL, 0xD864FE795B0946C9ULL, 
            0x074469CBF20624C3ULL, 0xE23BBAE7E0BC7942ULL, 0x83F98FF8D1D25EFCULL, 0xC45C92B3B6447AB8ULL
        },
        {
            0x35FE0CC62671E778ULL, 0x6CAB728070D114ABULL, 0xB3804BD51ED2CC7DULL, 0xF98AD0F076E05F73ULL, 
            0xB0C1D14CBF534D69ULL, 0x794F93EF6B8DE132ULL, 0x0F044480797ABB71ULL, 0x44942569AAA0B617ULL, 
            0x82A8AAA0642FC2B4ULL, 0xCEFBEB5F45B6F1A7ULL, 0x2EA420A85B995A29ULL, 0xA08B5E9FA6ABBABEULL, 
            0xD9FE95021D1125AFULL, 0x03F3996710E20D41ULL, 0x044E257A045469FAULL, 0x75542BF14B90103FULL, 
            0x535399D3382B0288ULL, 0x9C17A024465061AFULL, 0x278B7F9F79FC39B0ULL, 0x087D3BF9EF39AE74ULL, 
            0xBA0FBA01D2234D7FULL, 0xC4706D5827361AB5ULL, 0x5AE9A10085634876ULL, 0xAF2054C880C26414ULL, 
            0xCDD1CA36E7A45400ULL, 0x68ABF2EBBC6C8E80ULL, 0x7DB30CE585AD34FCULL, 0xA2DE00338E8C9E95ULL, 
            0xA4E64753C35F1BB6ULL, 0x6FA469EDC758999CULL, 0x677BD02433E2963EULL, 0x3E4BA3DBA8569856ULL
        },
        {
            0x9E99E6BF29682CC1ULL, 0x15D33B6EB07C57ECULL, 0x9D476851EBF675D4ULL, 0xB13F8E4E576DE144ULL, 
            0x4357EC4AF33A8D24ULL, 0x1F383DBCB82BA40CULL, 0xE6D91609A699EC63ULL, 0x8DD46C8A2141EC80ULL, 
            0x588F7E557DD88656ULL, 0x662F0233778EA384ULL, 0xB9112101D026C991ULL, 0xC0B996C304A9C096ULL, 
            0x4F4B841CAF06AEA4ULL, 0x736EE97745B04223ULL, 0x182082D88CD5F9A3ULL, 0x734483946A520D33ULL, 
            0x5D5668D06A753F93ULL, 0x80424129C287448EULL, 0x29AE1363B540952FULL, 0xC0C671DECF07B4EAULL, 
            0xA4F25D8DB91B3332ULL, 0xA46117701DE80CFAULL, 0x00003B3357C873D2ULL, 0xF26A4176E1257860ULL, 
            0x9BFFAE1F250E3C34ULL, 0x0552FC0817F061CBULL, 0xA3B6B8784A0AEA57ULL, 0xE94509E4DE846608ULL, 
            0xE1C88037DBDAA232ULL, 0x5567FE26B5B1593EULL, 0x5FF87204BE858F09ULL, 0x2E225E927137061AULL
        },
        {
            0x7FF3C7DE049176E5ULL, 0xFFCBAB9829FFF0EDULL, 0xE02CE3A237500F05ULL, 0xFA92482EDB40752FULL, 
            0x98C3EAEDC04DDFB0ULL, 0x305C47F24EC08883ULL, 0x0270812F30B7C186ULL, 0xD498A94E77179CFEULL, 
            0xA386A53C7288C6C0ULL, 0xE2A3C103041262B2ULL, 0x84BE168EED7D972FULL, 0xE36AA412995135ACULL, 
            0xB1E596515331C9E7ULL, 0xA70681E4CA9C6940ULL, 0x339300BDEADE31CBULL, 0x500FF1D6758DF64DULL, 
            0x7EF0A5CB2016FA63ULL, 0x8E4C717FFD544BDEULL, 0x73188F2218172699ULL, 0xCB3A7A3062049B21ULL, 
            0xD5EB715676385512ULL, 0x2B3C80FF23FDDC0CULL, 0x2163CF5B94B678E5ULL, 0x45EFE14CC90853DAULL, 
            0x0268C331D7F168A4ULL, 0xE84C26B3947165EDULL, 0x1F891BAAA68F2BB9ULL, 0x4525F52D4443ABACULL, 
            0xA31D3899FEF49A9BULL, 0xC40EAB2E40B66F8AULL, 0x5B7B45B568CC728BULL, 0x97745A614D5A0A25ULL
        }
    },
    {
        {
            0xC1C52B0E1BB9711EULL, 0xE970D7B8A0CC40D1ULL, 0x2F72EAE981127009ULL, 0xC18EA398F1546C8FULL, 
            0x446E38AF01F406FFULL, 0xB2AA73CCE1437624ULL, 0xEE59C20E70DEA488ULL, 0x37617FFF8F5A9E0EULL, 
            0xD902DBDF6C79A65DULL, 0x7151D8FE550A0E6EULL, 0x1068C4690D70D9B2ULL, 0xAB8709FDB885C426ULL, 
            0xEF217F54925E31C2ULL, 0x362971AF820A4DB8ULL, 0x4C86239CD5BA1C2FULL, 0x642B083E27DAC049ULL, 
            0xAB4703F408991DA3ULL, 0x0E84B0A4E5E76FE3ULL, 0x0B8F50E689EEFA4BULL, 0xC4928D2BCF3FE617ULL, 
            0xC53FE585793CD819ULL, 0x1EF2DAAFA1B3BF07ULL, 0x81C7575062AF2DC9ULL, 0xC959964C97060D6BULL, 
            0x27C8DC3143B036F7ULL, 0x51A9C10759AE734CULL, 0xE387DAED5B67CEFCULL, 0xC985EFBE3E00B463ULL, 
            0xF1BA23293CB043B5ULL, 0xCA48177B9E3426A2ULL, 0x9487C2D3EAB28ABBULL, 0xDF938F1C519C0855ULL
        },
        {
            0x61676378C09749CAULL, 0x891AC5453027CEA6ULL, 0x4261C0D40F0A1491ULL, 0x30BAF513CD2D2996ULL, 
            0x850BDAFB2066CFF0ULL, 0x5EDC009849FD49A4ULL, 0xA50053BB6D3E7DF7ULL, 0x238CD9457BE33D9FULL, 
            0x8AF21C052987149EULL, 0x96ED4162B8EE219FULL, 0x7194803A2EE05E6EULL, 0xBB3E3449F80B18CCULL, 
            0x4D3823813AC764FAULL, 0x10FC92AC83CF6512ULL, 0x9A44BF03D4AAA693ULL, 0x88AA0DCC53EC38BFULL, 
            0xA4142EBC39A7A3BCULL, 0x800246AB7BDF4D42ULL, 0x20D0CA59C43CB2D8ULL, 0xEB74D462AD8CF576ULL, 
            0x00203DA919322C9EULL, 0x674035B86C6F853CULL, 0x20802D030164B4C2ULL, 0xBE8E65957AC76859ULL, 
            0x2A98A072AC8E1223ULL, 0x56DC7E7B8074C125ULL, 0x2A44E2B424CACB34ULL, 0x402DF95FF8FD96D2ULL, 
            0x1FFFFA8EA345BF7FULL, 0x85A59C79DE09829CULL, 0x012D145268713CBAULL, 0x7601ED0F467834CFULL
        },
        {
            0x31A3976F081A5482ULL, 0xFECB81932F70362EULL, 0xEDF40CC6D06268DDULL, 0x7B031CEC0C0DA661ULL, 
            0xAA72F62210310A0EULL, 0x57D7D4689BA64B8EULL, 0x883C6DC2CA9607ABULL, 0xB37105A628F7459EULL, 
            0xD5DE5FEF09471754ULL, 0x388C508FE550803CULL, 0x615E3F85B4A91F87ULL, 0xD3326D63C8AFB358ULL, 
            0x4052333625A0B9DBULL, 0x78046357833ECF6CULL, 0x4004C430E48AD54AULL, 0x8A705E16A424AC87ULL, 
            0x0E9993917323CEBBULL, 0x0BD4C8A6C718C6FDULL, 0xE708407DDBB1AA2EULL, 0x400765167F0A3CB4ULL, 
            0x45B948D285FDEBDCULL, 0xB26C02CB070F8E12ULL, 0xD00F22117AACC3C1ULL, 0xB6EC062559907B6DULL, 
            0xD9E90C492850A4EFULL, 0x23C619494E72DE47ULL, 0xB992FADF05BD58C3ULL, 0xA482DC39529AF741ULL, 
            0xACDC850DCA287ED5ULL, 0x22DB91A56F2631FFULL, 0x24A6BB09528BC59BULL, 0x3E6829927BE9C467ULL
        },
        {
            0x037F639D7A36C4A7ULL, 0xCDB37E80039E9B31ULL, 0xB7542A64E18D255FULL, 0x917857AD1FB96590ULL, 
            0xA80A4B0C4BCD0506ULL, 0xFC21B0B5ACA418B9ULL, 0x350616578CAEB47EULL, 0x938B78D985791788ULL, 
            0xC9BB005CA15D7B8BULL, 0xDCBB5651D6A7D663ULL, 0xD4E8389F7B66907DULL, 0xE14FD5E0F07734BDULL, 
            0x5C370609914E4A7BULL, 0xB3720239EFA58AC1ULL, 0x52C15F1826919ED6ULL, 0x123C0EA64E5AF11DULL, 
            0x4B69F5E7DF9D5928ULL, 0x47D127D3BD9EF07EULL, 0xDD588AFA1A8809C3ULL, 0x6AE99C2E44536B0FULL, 
            0xF28D3923311EB044ULL, 0x4D0930DB3D772BCAULL, 0x33FC2AF67B2A2D65ULL, 0xE30228CA9AD81E10ULL, 
            0x02F850B1115692B9ULL, 0xD874B3AA522F30ECULL, 0x7A89D0E5775116A3ULL, 0xA05DA245BC0ACDDCULL, 
            0x488A6B78EA7FCB9EULL, 0xB42E52DC1F9C422BULL, 0x8DA44838A2D38EB3ULL, 0x93E762185D46D40FULL
        },
        {
            0xF2D48B780D27AB77ULL, 0x25EC3A573891A4A6ULL, 0x993F8168BD627C0AULL, 0x88924B7C62CC5C84ULL, 
            0x09646414D7D2395CULL, 0xFE7DD352FC7444BFULL, 0x78E5E46099D9A096ULL, 0xF193947C7932466BULL, 
            0xC3700B515EA4A853ULL, 0xF796026D4CF3C6D8ULL, 0xE296A3B9C1ED474DULL, 0x22CDB8CE9751B229ULL, 
            0x7F916D7CB2131603ULL, 0x7B04FF40D16619F9ULL, 0x79D23B7C59B818D6ULL, 0x1C321094AFBF50B5ULL, 
            0xB9F429857FBCCB3AULL, 0x34082ED625EFAEC8ULL, 0x968CC7AB283C7F4AULL, 0x96D2580760F4F1E9ULL, 
            0x5995623FE9E15C90ULL, 0xCEC506C0956E096AULL, 0x38CAA42C0CDDFF73ULL, 0x3A4007159EE6AD15ULL, 
            0x5AAAC78DFAFC2E32ULL, 0xCD160E87117BBC1FULL, 0x14702F32B805B501ULL, 0x60EC6DA58AB0D399ULL, 
            0x09E02379A475A262ULL, 0x6D6BAD89EEA124C2ULL, 0x0D9B8CD717D538EBULL, 0x076821951C812B69ULL
        },
        {
            0x3F5E158F6CCD5CF9ULL, 0xC43902216C053AD3ULL, 0x3F5C5C9B1B24906EULL, 0xAAE3EF1AD4245339ULL, 
            0x208CD5D77AE5F1EAULL, 0x7C185A3F7337DB17ULL, 0xCB71D2A47AE43E33ULL, 0x8CA904B946CBCE8FULL, 
            0x97C73535509BC0C0ULL, 0xD3AB957899865C02ULL, 0x159A32F77FC01ACDULL, 0xC78AB6433236817EULL, 
            0x9E4463888217D407ULL, 0xCDC16F17ABDCCCE6ULL, 0x0B2D847E4B11B226ULL, 0x83AC671DC74B0E32ULL, 
            0xDED893EDEFA44CB4ULL, 0x067287C08E4D0448ULL, 0x73C5128FDBBE6FA5ULL, 0x6513FF29FF1D6DFCULL, 
            0xE7BEC442EA1E931CULL, 0xFC964C8B015DE8FBULL, 0x005FE02B3DBA730DULL, 0x7E3E0AC8A0FBB783ULL, 
            0x53C205ECC7D9D67AULL, 0x8CEA33BDEDDBCEC4ULL, 0x45E7F7BEFE871BA2ULL, 0x817F003B4F962E80ULL, 
            0xD2FA1F21A7FD49A8ULL, 0x585A8B8DA92FABA1ULL, 0x58CA8F18C565DA3DULL, 0x0E21A754FF2C8847ULL
        }
    },
    {
        {
            0x8252ECB501F7840DULL, 0xF0010D24EE0713BFULL, 0xFCCD83819AADD377ULL, 0xC381A971B90D2F53ULL, 
            0x504FCC339AFEF31EULL, 0x4694CE318449B172ULL, 0xB4691EFF4B17FCEAULL, 0xA69F2A3761A3D24DULL, 
            0xE834234A8C368920ULL, 0x460C0773A5B08B3EULL, 0x0E473448F61D1996ULL, 0x6F120E35C89F98B8ULL, 
            0x28BB10CCA4EEC91CULL, 0xAA12F166B452E3ADULL, 0xEFB90B6B62396E1BULL, 0x4262DEA4468D4B33ULL, 
            0x883354EB7B9F5828ULL, 0x79098D584DC11465ULL, 0xEB5C8D8314493396ULL, 0xA973A0B6E99FEEF2ULL, 
            0x6D233016ECDBD579ULL, 0x8233427180DFEDB2ULL, 0x1B8BB6800E3BF012ULL, 0x8781647461125C35ULL, 
            0x90A29F3DDB002538ULL, 0x800EB07CBA922E9AULL, 0x2AEA2874EFAD3D5FULL, 0x163B1AFA98E843A5ULL, 
            0x6CCCDB8F528AD8E7ULL, 0x17389C63EE9A496BULL, 0xCA584DA8A8A1D8CAULL, 0xB3A55543E1BD7129ULL
        },
        {
            0xE092744AEF724592ULL, 0x53865CDA69A89F94ULL, 0x3383D8B70506B665ULL, 0xA7131E5FDA90A2FDULL, 
            0xA6316DF5F114B7C3ULL, 0xCC6F527D665A9B49ULL, 0x14DA33FF4CED6C6FULL, 0x293B80AD4C5835C9ULL, 
            0x79947C529906359BULL, 0xB80FAC429F4AE548ULL, 0x373D2FC16EF456ECULL, 0xCBA34F309430AE68ULL, 
            0xF3A02FBC10B98703ULL, 0x7650CE196807FEEEULL, 0x08DC089DAA22008DULL, 0xCC0FED9E8CBCA698ULL, 
            0xAF2126395F4FC3CDULL, 0xDA2C7B011B9DBF13ULL, 0x632751E43AB6BE65ULL, 0x826D818D813EAABCULL, 
            0x336B7CB9B0536F1EULL, 0x8862CA8A892B0FE7ULL, 0x88B71BE597C26247ULL, 0xB885D332C1CDA11CULL, 
            0x405BB847B017C9ADULL, 0x982687BA18E83700ULL, 0x388375F057093E01ULL, 0xF3BA74532D4A5C8CULL, 
            0xAC6D45860BA5BED8ULL, 0x30CD76481D9D8A77ULL, 0x625B3886486EE5F3ULL, 0xB82F897B0FE0C802ULL
        },
        {
            0xF482AAC84AAE8DD7ULL, 0x435F9447CD243928ULL, 0x450F5A5916999C46ULL, 0x3158D93AAD9F9238ULL, 
            0xFC9926C0BB514BB6ULL, 0x46AF57019ECAD844ULL, 0x6B13FE965D33CDBFULL, 0xFA37ACAE25B0CCC3ULL, 
            0xC18F1218D750D344ULL, 0xD68C581A824AB72AULL, 0x1724D9EFBA0B8C60ULL, 0x95B5E390D50CA6E5ULL, 
            0x3EA4D7ED435DA90CULL, 0xF7DB1D07DB8D9107ULL, 0x8533FF38DFB941FAULL, 0xACDE6664D721293EULL, 
            0x9A6F01C1F31FB610ULL, 0xD4B4C5018220C321ULL, 0x0C128089BA97CF41ULL, 0x5EAC5EE95084A449ULL, 
            0xD627988622053AF3ULL, 0x03BCA09A359F2C08ULL, 0xBB1EEA50D653D263ULL, 0xF4427D70DCDE2B19ULL, 
            0xC21BD197892F48EEULL, 0xC0BB01B8EFD6BDCBULL, 0x83905EFBFA62871FULL, 0x65FD6BF8B279FB56ULL, 
            0x0110092DB7FEB3D5ULL, 0x78A36F586838BBDCULL, 0x6765A009173460F2ULL, 0x67BBC413BA544372ULL
        },
        {
            0x25621FEF737A75FDULL, 0x8562C6C2A23B5649ULL, 0x83898BFD3FDB26CAULL, 0x201ACDFBEAC67E91ULL, 
            0x929323B397AB9B6DULL, 0x6BB1C9F30187951DULL, 0x2AB11DF0D8D40184ULL, 0x894322D6A8E598EFULL, 
            0x944FA74E2C188CC5ULL, 0x8438981AA2798EA8ULL, 0xE296913FC81B033DULL, 0xB080BCADE35A3441ULL, 
            0x7D7FC23E8C76EA35ULL, 0x5E689D67268196D9ULL, 0x1E01E174CC2851F1ULL, 0x6B43941B2AE2D382ULL, 
            0x77BE73AE56790C94ULL, 0xD6168F93B825D0F5ULL, 0x5FF85C51DB164415ULL, 0x1FBC055C841C392BULL, 
            0x31363E660004666DULL, 0x99A6D623699BFDC0ULL, 0xE3681BC180B0F60CULL, 0xFF0DEDA2F6EF0CDFULL, 
            0xEAD0DFB56DD6DB9FULL, 0xB818C86042A6A859ULL, 0xF7096F8FAB0BB7DBULL, 0x58227319B92A9DFEULL, 
            0xBA75FCE27B98CD84ULL, 0x35BD31F88FEF2547ULL, 0x6EE363C785678A1FULL, 0x74BE2A8D74976188ULL
        },
        {
            0xF3E1FEAAF8538A8BULL, 0xA26A7EF7A65B821AULL, 0x538827645B43743CULL, 0xEFBF7A433183D82EULL, 
            0x813C410F94DB68CBULL, 0x11CFA5E22F9D6F37ULL, 0x9FFE6FAD8EFCA62EULL, 0x24DCD6A44DD699AEULL, 
            0x84D0349859415B27ULL, 0xC10F6FF3D3F967FEULL, 0x4292E77D732C4ED9ULL, 0x943B8299314C65F2ULL, 
            0x0F6FA7DA1C04114BULL, 0x7D8F39C8E4E8EB0EULL, 0x4A696EC1B0AC81E5ULL, 0x2E001C799B660242ULL, 
            0x010FB26C4F4C314BULL, 0xF783DA0A1EAC1059ULL, 0x229086AC2CE8B2F1ULL, 0x7AB19C2240DC8BEEULL, 
            0xD1447B4E40AEA25DULL, 0x77AACA89673EBFA2ULL, 0x4093EB7290899A59ULL, 0x0FA7171E14B1C7F3ULL, 
            0x358B2372C00650DBULL, 0x969C975DEC7387D4ULL, 0x7ACF97AE742D9225ULL, 0xB7C8E9B22D90C847ULL, 
            0xF17348F04C8FE001ULL, 0x181F32CF9F9648D6ULL, 0x9E66CD59B834D759ULL, 0x84720F07F6D54D30ULL
        },
        {
            0xC503CF33DB12212CULL, 0x6C41DDE449E36CB4ULL, 0xA8F5CE2D5FD3277FULL, 0x78408490D14731A5ULL, 
            0x1835AE532B47EC56ULL, 0xC9AC11A85D2158A9ULL, 0xDFFD5680BCAE3C81ULL, 0xFCEEEE49E40D9C80ULL, 
            0xEBBD7C546BADFDC3ULL, 0xBF8B418ADE163D45ULL, 0x45D1E6E4F71655D8ULL, 0x5769B25F90E265F1ULL, 
            0x0841C56529B7285EULL, 0x4F11358673E6D10DULL, 0xA880A2E8F656ADD0ULL, 0x0663C144041778A5ULL, 
            0xE921590BACD0FE22ULL, 0xE8871EA7CDB8A10CULL, 0x41FE9EBB6453C7C2ULL, 0x881FDC58871279FDULL, 
            0x1FBA92B96023FB82ULL, 0x87B441F780E02991ULL, 0x178FA34B3C30E124ULL, 0x02402B9B5D035754ULL, 
            0xA75978396AA4D0F5ULL, 0xF7BBBF33F06042FCULL, 0xC40B64717A46B107ULL, 0x896EF176D4877A0BULL, 
            0x70FFA640905870FEULL, 0x2F4F967050DBB652ULL, 0xBE0CE1602A58137EULL, 0x6987028294B56437ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseAConstants = {
    0x6475DB2897BC93BEULL,
    0xB151D85360CE88F7ULL,
    0x17D9B238F68F573DULL,
    0x6475DB2897BC93BEULL,
    0xB151D85360CE88F7ULL,
    0x17D9B238F68F573DULL,
    0x4CDAF7E7ACF427AFULL,
    0xD0D9A4C5AF3DE52BULL,
    0x41,
    0xE3,
    0x80,
    0x9B,
    0xD3,
    0xD2,
    0x65,
    0x89
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseBSalts = {
    {
        {
            0xE185B03A5F05B07FULL, 0x661CF4A775E2AC4BULL, 0x50CFDA65AAA9A7D8ULL, 0xBA20C6BA26046A97ULL, 
            0x16E78B729944C631ULL, 0x425EAD2AD11B9CE1ULL, 0x05215557D4209CE8ULL, 0xED413B219CB1E8AAULL, 
            0x4C94A35C058B7E5AULL, 0x3BE0843D3C385D4BULL, 0x787722E46457C830ULL, 0xD746692A5F6C57C3ULL, 
            0xEB9E6E24936EE6CCULL, 0xEC75EFF72C0D9179ULL, 0x275F1571B38A52C5ULL, 0x729CC694BBCA3234ULL, 
            0x46D7A45CD499B419ULL, 0xC3A3E0841D91E132ULL, 0x5F5CDA7235FACACEULL, 0x1C86EAEC550DD79CULL, 
            0x23E39C9DB1E40190ULL, 0x9CA398A354507CF0ULL, 0xB564822D09929C27ULL, 0x9E41EB77927FF7DAULL, 
            0x17A14601DEB5EE9FULL, 0xB5773F28D2446305ULL, 0x1D7700ABD6D9F454ULL, 0x46F598A14B260793ULL, 
            0x1DBCB001D6BC0BB7ULL, 0xC64E58A7489D77FBULL, 0xAA16AF8479727BB5ULL, 0x2E16D685018ED8B6ULL
        },
        {
            0x5E9AD7411C870EBFULL, 0xCEC42525136870ECULL, 0x7AAF0F887132DAEFULL, 0x8EB6AF54891A66F4ULL, 
            0xA35624601BD60862ULL, 0xC71235B5ADE0D635ULL, 0x705D63253496C3C0ULL, 0x645D78354E420A61ULL, 
            0x481A62D83F9F6428ULL, 0x188C4B64B2E3849FULL, 0xBFA504717C57FB16ULL, 0xAFCAA95F7779D893ULL, 
            0xB3752471A9C16652ULL, 0x0055ADC06E851DA4ULL, 0x50789A3DBA7A4050ULL, 0xB3EF9E02F29C7809ULL, 
            0x92EBC1A9334F5C22ULL, 0xE34EB04F150B071BULL, 0x4CFAEE2020E3FC6FULL, 0x25A1DD245472262AULL, 
            0x371D425E00080854ULL, 0x124663E8DC1A469AULL, 0x7349D0D808B41CFCULL, 0xBA549DB1AB12C148ULL, 
            0xC3762E82DCD1C7F7ULL, 0xC06FEB6C558022A8ULL, 0x70C700A454DB2560ULL, 0x27569AB7350AC4AAULL, 
            0x8DAF0228955C07F0ULL, 0x1824B6B56D181F8AULL, 0x042DCB15A40D18CBULL, 0xDCDBEE07F1CA7422ULL
        },
        {
            0xD41B359B8156446EULL, 0x85C4C472ACA068DCULL, 0xBB7160BEAB9CED9FULL, 0x8A740524CC20519DULL, 
            0xB9C02B77D064F9E1ULL, 0x2E50A1D3FA860C25ULL, 0x1AFE646337166097ULL, 0x8B6F9389B72F1B84ULL, 
            0x6EEC29E709F03202ULL, 0x0820980DFF9A6799ULL, 0x611382C7AAE77C66ULL, 0x4F6C0FE8C82EDF4AULL, 
            0xCB0C594848EDC517ULL, 0xA508CD68C911F4D2ULL, 0x4285CC458BB2AAB7ULL, 0x5414A046EDA9E6E6ULL, 
            0x50F907CFF8FA5390ULL, 0xF1ABF1ABC1B26B96ULL, 0x8372ADF2B6F672B9ULL, 0x87000F02603CB6C9ULL, 
            0x60C44DD0D7469D28ULL, 0x78AB2D0D87F62B17ULL, 0xD5FB138A4406BF62ULL, 0xE760C14F7767E8A7ULL, 
            0x648D7B4533AA6D70ULL, 0xC2606C034FDA7DB2ULL, 0x67F21DD2D9716092ULL, 0x0A145F58E6FCFC99ULL, 
            0xD43D9ADFD2C69D2EULL, 0xEA9DE7C9308477F2ULL, 0xA025862CC2463CBEULL, 0x8C7DE4DBD0A5A749ULL
        },
        {
            0xF1430271FBECDB8BULL, 0x5FF48503BB3BEE3DULL, 0xDA84DBE5DEE1E4ABULL, 0x1CD15810D2D139AEULL, 
            0x202CEE44E5B2C194ULL, 0x05C755979B33728AULL, 0x67309071D2521E51ULL, 0xF1623E9B7DAD2203ULL, 
            0x833FAAEFDACEB64CULL, 0xB811D383026619ADULL, 0x25DC3D7E3CB41382ULL, 0xFA42CA24FC78E22AULL, 
            0xC36EEE0127DE5066ULL, 0x0A9F63435DAA97DBULL, 0x10E7C7D3F30BC5A7ULL, 0xCA1AF9EE97BBDDF0ULL, 
            0xD189A362AF8AD72DULL, 0x563CE5E079E1DD3DULL, 0x2F63C525E61ED8E1ULL, 0xC50C3EEBFBD3C5ABULL, 
            0x6CB97015A5596F29ULL, 0xCA3517350008B545ULL, 0x3F3D60656E2DBEB4ULL, 0xB2C9863186A22AB6ULL, 
            0x69F9A9097386174AULL, 0x26CF52AE40D20A35ULL, 0xF62DB5CB0A38A9CCULL, 0xB70569112F423436ULL, 
            0x96772408A113B59EULL, 0x786A3BC49580C004ULL, 0xFD02358AEDBD8C91ULL, 0x845D84AF289E8F85ULL
        },
        {
            0x02617EE9A35C31C3ULL, 0x12CF68FA153CCC95ULL, 0xA4C8C5CDE7B649ADULL, 0x1A81524281FADD55ULL, 
            0x8ACA5246489EEA5BULL, 0xBDF63D3D8163D72FULL, 0x11FDC5419037C5B2ULL, 0x84CBFB22FB9F406EULL, 
            0x683C908F1C6D0872ULL, 0xBF193F52CB7DB97CULL, 0xA6B2105931FFF275ULL, 0x678CDC5301ED94A4ULL, 
            0xDE30516A00519359ULL, 0x0ABED1B25FB4C1CFULL, 0x4C76C21053D08ED6ULL, 0x711B0126AA5A9121ULL, 
            0x2EDFADC377073FB8ULL, 0xD5E15BC0C7A30020ULL, 0xEE72DED9E9BB2071ULL, 0x4C4217F14796A369ULL, 
            0x1829F67B2A57A4FAULL, 0x38D88474AE8CADAFULL, 0xF80E2B520F8F1FECULL, 0x99F656CD8434B355ULL, 
            0xE317DAE39FF85F5AULL, 0xD4C5144199402DAEULL, 0xD997995514C02F3EULL, 0x8CD7BAA52D455281ULL, 
            0x36B28664652E9390ULL, 0x50CFD12D78809DF5ULL, 0xC239C9CE9E332359ULL, 0x22C8D8C6D6793D3AULL
        },
        {
            0xA3349EF31EA99183ULL, 0xE96F1070D273A152ULL, 0xD08FF1389463B044ULL, 0x781D0CF4CCAF7941ULL, 
            0xE9B1B0238F8EFB6FULL, 0x43DC22F5B53390E5ULL, 0x180E19444B19369FULL, 0xCDE33EBE7B333075ULL, 
            0xDA18E3D1B7635D52ULL, 0xB3F1907F2C0334D6ULL, 0x84286078C2930B26ULL, 0x6979F0748046047AULL, 
            0x712162B477EEF7C6ULL, 0xD4F0D85FDDDD2B03ULL, 0xA69D09C4A31551BEULL, 0x39282A5BF9ACF67CULL, 
            0xAADBFFB5185997AEULL, 0xACCB4C841086B93FULL, 0x24E9530AD705F2F6ULL, 0x9AA794FDB9AB7B1FULL, 
            0x050802740D6FB684ULL, 0xAAEB658FBF41ED65ULL, 0x610AF5B2F3615DC8ULL, 0x057384F78AF0800FULL, 
            0xB8EAA5AB995F9137ULL, 0xF2F29495BB9B871FULL, 0x8EE4BFE3D1106249ULL, 0x2B1083AD992080B4ULL, 
            0xCB222C40642A9BF9ULL, 0x8FFDB279DE198A3EULL, 0x3DCCCE32AA85107BULL, 0x39C22764A882D0F4ULL
        }
    },
    {
        {
            0xFD17946CC38D1AECULL, 0x1E5196B5B2109D0DULL, 0x2DD1EFA0C876FD24ULL, 0x051BC2992533859AULL, 
            0xD376AA514ED34A0AULL, 0xB60D9C08680DB4A4ULL, 0x0623710C5D7B1271ULL, 0xF9596B6DCB234899ULL, 
            0x6FC0ECAF12421DA7ULL, 0xAA051B79AAC9C593ULL, 0xC7C58F2F6BC18EA5ULL, 0x5EB763767A30416EULL, 
            0xEDDDC169494D2E15ULL, 0xCA72CD4D98641203ULL, 0xA519DD5346EFC433ULL, 0x1ADAD16DB2BBBBA5ULL, 
            0xDE0E301E6FF50563ULL, 0x9ACB3F9010A64996ULL, 0xF8A2F0AE82054B8FULL, 0xB125C415019944DDULL, 
            0x966ECA6561CDBE9CULL, 0x52318DF2BF2112F3ULL, 0x1EA596FD2BA1E583ULL, 0x1D5970F6F36DD579ULL, 
            0x2FAAFE0533F35D86ULL, 0x925A9995FDD3C55CULL, 0x6F865FB0A783C72FULL, 0x42FEBE17DE781AB2ULL, 
            0xD93FCC4F5979E2DFULL, 0x3ECB7FDE9A49C150ULL, 0x1D66C75865D2CAA0ULL, 0xFE4A4F1EA8A2FCB0ULL
        },
        {
            0x12434B57A23DE50FULL, 0xD07B05358A68D43EULL, 0xC69E1569889899A3ULL, 0xEB0EB3B87B8FFB52ULL, 
            0x611E21308E8ADFF1ULL, 0xC321AE8CB1F944D6ULL, 0x66F3B31D6B5437D0ULL, 0xC6ADADB76569F4DDULL, 
            0x0AFE6263751AC4B7ULL, 0x8E4D31CEEDC8F8C9ULL, 0xB61253853A1B2222ULL, 0x435E3D93B4D21202ULL, 
            0x4F672E3FD261ABE5ULL, 0xC1A4091B6CDCD3C4ULL, 0xCF9D1D2D641C7C10ULL, 0xAA1523ABC5DFE34DULL, 
            0xDEDCE10B941D508DULL, 0xF6B63041314FCD67ULL, 0x317FF96B7BE51907ULL, 0x9CBAE8AECB8AEAC0ULL, 
            0xB5ED22A12B3E06F7ULL, 0x690CDB634685057CULL, 0x5A386E86D0C589E8ULL, 0xFA36D1011205F25EULL, 
            0x897888D3427032DCULL, 0x37946647CA69D6F9ULL, 0xDFD3341A3A2B0B93ULL, 0x4AAB08DE71860874ULL, 
            0xBD4E939FA833C315ULL, 0x5A07D557E1B6BB03ULL, 0x84CFD562D1DEF91BULL, 0xB220ED199D03CC06ULL
        },
        {
            0x116820D7F39939B2ULL, 0xE856B63F4872F015ULL, 0xDC4E8C2E7131817AULL, 0x02B1129BB934F6AAULL, 
            0x36630962FC4CBC28ULL, 0x4D0D6BD0559DB74DULL, 0x4C0E62784570A7A3ULL, 0x9D64A2B8F38D2472ULL, 
            0x54450C2D470A7447ULL, 0x4D88B60378DD2A07ULL, 0xE7EA546C1E628567ULL, 0xD93647A7C1D6FC14ULL, 
            0x7FC44A82D83D6A55ULL, 0x173666A52C3EAEAEULL, 0x78FEE18D8A38E938ULL, 0x6EF46A38AC71229DULL, 
            0xC2D444B13F443613ULL, 0xB290BF6E30842B80ULL, 0xA8979713CBC895E1ULL, 0x3DF5ED3E76474A97ULL, 
            0xC116744EEC2C987EULL, 0x46B9027FC67E4AFAULL, 0x290BB3A6FA678D18ULL, 0xBBB391E65418EACEULL, 
            0x6BA3D504D551D58EULL, 0x95BB03B62CFA7487ULL, 0xD7346450142FDC25ULL, 0xEB77159B59E95A4FULL, 
            0xF1D9F9F592361A3AULL, 0x74D1CB04F69E8975ULL, 0x820B385BC7C3F468ULL, 0x0CD343714215855FULL
        },
        {
            0x4DFDEA15F5D61048ULL, 0xCE24CB32906CF59CULL, 0x4EF679FCCAE3D6C1ULL, 0x2D864B14FA5D931BULL, 
            0x635BCB9C010A8C8AULL, 0x17B4775691B78392ULL, 0x3D11E2074C390D11ULL, 0x96CECA6D25267FD4ULL, 
            0x8CA87D55929181E6ULL, 0x3A69A0498358870EULL, 0xBB16A9201051A74FULL, 0x3FA55C7068790DA7ULL, 
            0xA96D370B93791D16ULL, 0x07095683F7B69242ULL, 0x737CFCC48A4FF119ULL, 0x3059BE379D9EC7C2ULL, 
            0xD5C0B3F2BB3DA029ULL, 0x2014566EA70E5D50ULL, 0x9DB4537A74D57416ULL, 0x05B39810365717BBULL, 
            0x43FA865BFBF66701ULL, 0x6F515910BD9CEBF4ULL, 0xF6F4E415DCA19423ULL, 0x849F3D31304DA9C3ULL, 
            0x4526064E13021063ULL, 0xDC0BFBC06D13935FULL, 0x05E2BFA4FFA421E7ULL, 0x00A64119DBC4EAA4ULL, 
            0x527509E34BC8EC94ULL, 0xD44C4C77A4C946D6ULL, 0xE932AAD591F4CC28ULL, 0x86137C40721BC32FULL
        },
        {
            0xE311FF928B5DCCB8ULL, 0x6B1C1FCFBD236A29ULL, 0xC079C7C48F332562ULL, 0x11C76C210F8186EAULL, 
            0x85D5E644AE324F2FULL, 0x78A5A1C8561B015CULL, 0xF2A6B11C62E57C2CULL, 0x82383AA515CD69BAULL, 
            0x5E49C30E0A986447ULL, 0x69E3D4EAA6023420ULL, 0x62DDCFDDB851F2BEULL, 0xC927B578D718F915ULL, 
            0xB167674EBA8AB71BULL, 0x03156198A298A0BAULL, 0xD5630D0A309A983EULL, 0xFCE7A8385CE9236AULL, 
            0x7291097E7469E94DULL, 0xF628FD08532C090BULL, 0x6671666C139DC3DAULL, 0xAF1319EE8F7619CEULL, 
            0x4A510CB20246D04DULL, 0xFF9F82772C4C711DULL, 0x63F0507B9A97EE29ULL, 0x65AF13C90F3B6C21ULL, 
            0xDCA12468D23848B9ULL, 0x6BA9BBE30EC33AD2ULL, 0xF3C9B4D8B533EEB4ULL, 0xB5A3EDD369B516CDULL, 
            0x12A603EE6BED29FDULL, 0x9A25CBFACACDF71DULL, 0x1F49B45811754E50ULL, 0x906C22139CC7139CULL
        },
        {
            0x824B6F6FDA98E2F3ULL, 0xA5074A53C6FD49A7ULL, 0x2256CC29124C24F3ULL, 0x9C7BE872447BF898ULL, 
            0x630D41239F36C08FULL, 0x292A1243EA3FD08DULL, 0x1B0052C2352FE351ULL, 0x6545C6F8FEB0BB58ULL, 
            0x717CA7FB8ECDF94BULL, 0xF8581DFF807548F4ULL, 0xCFEEC797955187A1ULL, 0xF68DBD2338D5A583ULL, 
            0x0EC320A6896EE738ULL, 0xE337241EF4AA79EFULL, 0x6ED10772A7A52E1DULL, 0x0AE6EA3AB09C86B5ULL, 
            0xDB7196151402C9A4ULL, 0x773B842B6CA6D4E3ULL, 0x74A9870A374072E9ULL, 0xD31F4E20AF8C58F2ULL, 
            0xB693E13CFD8522CDULL, 0x642C556659F61651ULL, 0x8A4D1366922B0903ULL, 0xD35E54057816AF8FULL, 
            0x3E1A72B0D6059D12ULL, 0x9CBE8BF0FBD46588ULL, 0xB76E30C9DEF724DEULL, 0xDA859BD117BD392FULL, 
            0x443803E358F75530ULL, 0xE3521D6D03E532F8ULL, 0x9CFB581FEEF5DC7DULL, 0xC5159DA5DFC56CB2ULL
        }
    },
    {
        {
            0xB9CE65AF7F70CA30ULL, 0xCE984D122F681805ULL, 0xC213644BB7A6901BULL, 0x4D371E7E54B4508AULL, 
            0xBD212A0290299765ULL, 0x9519AA1EE5C1A6DEULL, 0x7AFCE8DB4B4E96A8ULL, 0x3B8B2C9A5DA4F2FEULL, 
            0xB12E10537D99EB65ULL, 0x3A1F80738C6070BFULL, 0x58B9B86C480A6DB8ULL, 0x4DBF7E54BC08F431ULL, 
            0x4D05780F4C03F4AAULL, 0x433B2E49AB3EDDF8ULL, 0xEFC34060A1256B82ULL, 0xACABC48C582ABC2EULL, 
            0x584ADFF62FA88FA2ULL, 0x615D05FCEEA128BCULL, 0x482D70F26808C639ULL, 0xFECCA2542A8B658CULL, 
            0x1464185897A41340ULL, 0x871132773C0DAD64ULL, 0x6D75844788260DE9ULL, 0x4B6B6E1243326448ULL, 
            0xC9C01E2666108584ULL, 0xFCFE3BD97D5F5722ULL, 0xB324D572F31FD6A2ULL, 0x68DF9EB687D8DA61ULL, 
            0x57847F1278635FBDULL, 0x68CA20F7B6C24161ULL, 0x5AC8666438BB5B13ULL, 0x77D068A199EBA2FAULL
        },
        {
            0xF982B1DD5C0C6842ULL, 0x3005040C73E620D7ULL, 0x8A2BD1339ABD49A3ULL, 0x0E4BE2D6A38A23E6ULL, 
            0xF34EE2C5BDC3F28EULL, 0x24EB426450AF78ADULL, 0xF8DA43EC81030EBBULL, 0xEB5E795878AD8A29ULL, 
            0xE2CF35E94AF620CEULL, 0xCCB8B6F46444C941ULL, 0x771782306B7E8418ULL, 0x37E6804F5E8317C2ULL, 
            0x126FD673E34FA75EULL, 0x7623362CD405F439ULL, 0x9BEB94A3992E2D7DULL, 0xBE18F090E027B483ULL, 
            0xA4AF7C9373342A94ULL, 0x0B553D6AE4C269EEULL, 0x47887655FBD89EAFULL, 0x732FB0C595E5F63DULL, 
            0x72456AC67F5F6D08ULL, 0x3D757686DC53A5CAULL, 0x39C888437BDDF156ULL, 0xB3EEDCB27E954318ULL, 
            0x3FA288D558CC49BEULL, 0xC6CC3F93D02F4E6AULL, 0xC9BCE55CBF9C21ABULL, 0x47061321B0853F38ULL, 
            0x3EC9F03632A6DEB6ULL, 0x071D9F3BB981A0CDULL, 0x158F6A1A118E896DULL, 0xA3570AD7436CE0FFULL
        },
        {
            0xFE78C270C567B45FULL, 0xC705BC38F0C160E1ULL, 0x6280BB90FD93F653ULL, 0x156D18C263A92AC1ULL, 
            0xC45B6DA1E96AE876ULL, 0xC2C73120FCA2AB67ULL, 0xC5D88A614549B33FULL, 0x102A6940B095D16EULL, 
            0x7D37ADFB97EF91DFULL, 0x2F1BB22E5D4713A4ULL, 0xF3E185915694937BULL, 0x452F3EEB49842966ULL, 
            0xEACA1496A1F44863ULL, 0xAFE462011EE88C30ULL, 0x3293BF8F8FCF4050ULL, 0xAA02402F344BD75BULL, 
            0xB871F648F359A730ULL, 0xDB27C197B9012AC0ULL, 0x3043393C64205F3BULL, 0x4D333D6326C0E6F4ULL, 
            0x012C0D21F22A5295ULL, 0x3B79FF1B4B687FEDULL, 0xC7B6E605C7433743ULL, 0x912864A9540C7E5BULL, 
            0x5E69856748BBA2B1ULL, 0xA1C5A396858D71D2ULL, 0x0DFEB38D5625B01CULL, 0x664FE236158C9A3AULL, 
            0x61FCD66A531DF342ULL, 0x0E096C17E211430EULL, 0xF6BB4251C43F914EULL, 0xA1B19B48C9675A0DULL
        },
        {
            0x08A2CE39B734037EULL, 0x306F536A84B4745DULL, 0x0DDAAC0FF5F275CAULL, 0x188419923F794C1AULL, 
            0x4494BB99C7A9ECC8ULL, 0x322D5D30F2F6A48AULL, 0x5571F7E9E83E6925ULL, 0x9BE4194B11BDA97FULL, 
            0x3AFD97E7EAF47912ULL, 0x380E8E2C3465C3D0ULL, 0x76728DE00FD3B584ULL, 0x4A4A17DD2796A390ULL, 
            0xC530D0F74B877CB9ULL, 0x05DE2797AB465F7AULL, 0x0308E0EB60DE10B3ULL, 0x0AA921856C7635DEULL, 
            0xF4A8DC38980213B5ULL, 0x36783D33DC49D43CULL, 0x9FD048BE87FD46FCULL, 0x9C6688ACE3680F35ULL, 
            0x90C29AAFA540BC77ULL, 0x57E048C607C51A52ULL, 0x5CB25B589F99F6D0ULL, 0x2DA70B977CC61511ULL, 
            0xA7F4781AA49D3E40ULL, 0xB590228CDA269C57ULL, 0x04221339EC515874ULL, 0x68D7FD913A7515B2ULL, 
            0xAA94B76CE54F61FFULL, 0xD1A2F0C682C80604ULL, 0x299AA96B0BE8849AULL, 0x7628C319917B9E0EULL
        },
        {
            0xB3E49EC8404A6A4CULL, 0xC87E04C8CC91C5D8ULL, 0x7896EA4E625F4ACCULL, 0xF4D26761C31A1943ULL, 
            0x3DC5607AA01920DDULL, 0xD51D20ADF8CB523BULL, 0xF09245BBB379B734ULL, 0x35EE1305B29DD61FULL, 
            0xF7D0144E2358AA52ULL, 0x1B62C9AA9F958107ULL, 0x4B74B109B2E1458DULL, 0x241D86E763E2AF25ULL, 
            0x7FFECF3F575CB53BULL, 0x12FF50A281143EB6ULL, 0x8B45D24149632B69ULL, 0xFE8BCDAAABBC827FULL, 
            0xD3FF508EA0858089ULL, 0xC131DA2CB05BA597ULL, 0x0C461B0A5683F0DEULL, 0x67D27B575BD19D58ULL, 
            0x8FBAC743A10CEC7DULL, 0x32575A1ED12F3CC1ULL, 0x956C6534ECB2206FULL, 0x6BF8F95AB8392069ULL, 
            0x7B482341506989ABULL, 0x97869F56AC437333ULL, 0xDD89BC973029F30EULL, 0xB2EC6AE746036164ULL, 
            0xBD1139AFAE85FB4BULL, 0x17C2B329D4FEFB81ULL, 0xD20737BC95064FD0ULL, 0x28470C29969AC830ULL
        },
        {
            0x7B6E68F6681A9218ULL, 0xDFF4E2F6832692B0ULL, 0x4253BB83AF40BBA0ULL, 0xCB3ACD22793EA166ULL, 
            0xF74F86EA0EB701E8ULL, 0x23B139E0EE1B3B2AULL, 0xB9369C7475C2F830ULL, 0xD2037632A18E479EULL, 
            0xFCB276AFF45387F6ULL, 0xB658804FA5E91D6DULL, 0x02F80DC9FEA0B05FULL, 0x8460E6B878E93BFAULL, 
            0x745441B1CFF2EF47ULL, 0xADD8A263A723A05EULL, 0xED40C317902B3C7CULL, 0x73CFD8D611D89273ULL, 
            0x07E28A68AFAED57CULL, 0x888C776FD2B01C1DULL, 0xEB39095819D7A7F0ULL, 0x763820E103A22E91ULL, 
            0xE1735F2D51B48C05ULL, 0x488AC8A50C88879AULL, 0x1FC3A4CE75AB71A2ULL, 0x1EB3CCB77B013BE0ULL, 
            0xC670EC72A4859DB9ULL, 0xF810E09A90D52E6AULL, 0x4B25A0D4F1692BECULL, 0xD12D283AE499AE71ULL, 
            0x5CA59DB63A6413EBULL, 0x2FDE05B3FDA65CFFULL, 0x8809DB7213FA7BCEULL, 0xD7E0B38993891CFFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseBConstants = {
    0x0DD84C931D8FA2F0ULL,
    0x01606D209524537CULL,
    0x271634CEE781198CULL,
    0x0DD84C931D8FA2F0ULL,
    0x01606D209524537CULL,
    0x271634CEE781198CULL,
    0xB0D60B932ED336A7ULL,
    0xF387FEB4E1C67716ULL,
    0x45,
    0xFF,
    0x71,
    0xCD,
    0x93,
    0x21,
    0x62,
    0xB7
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseCSalts = {
    {
        {
            0x1FC5B305668FEE6BULL, 0x2B55B5E6CFE162D8ULL, 0x2636A5BBBD623827ULL, 0xCE56BFAC89A8B20AULL, 
            0x2038F2AA52603CB2ULL, 0xC8363CF924D8D508ULL, 0x4DF457A95E21EC48ULL, 0x0FFA3DB689DA707BULL, 
            0xBA2F8F45F07C99E9ULL, 0x7673C10D363CFEAAULL, 0x13718AAE42515EDDULL, 0x57E6587911D5B3F1ULL, 
            0x68B3C323465209D8ULL, 0x9CA84606BDF4038CULL, 0xDB074DC9266DC2B6ULL, 0x8A659729522C2B8FULL, 
            0xC2FA2A37DA1221BCULL, 0xA60AF6DE1C4FCE58ULL, 0xC29AC736315C5980ULL, 0x316674618A383C28ULL, 
            0x447B35CEDFC65D69ULL, 0xD4292F6994DF177EULL, 0x6382C3789518B519ULL, 0x58AE77B015516845ULL, 
            0x33369D060F688D29ULL, 0xACF9D550761F6B24ULL, 0x5D538F6A97EA56D6ULL, 0x5AD7F4CB463965CCULL, 
            0x748D8E5679B3C394ULL, 0x8FE7F72A42F76179ULL, 0x3F196A1667FC833FULL, 0xA48B15FE7EC01A0BULL
        },
        {
            0x4A9B64AF017E1230ULL, 0x8D5E46D3A67156AEULL, 0xB89F3DC143847312ULL, 0x0E01212F5115AB4BULL, 
            0x59C6907D4F4C5C9DULL, 0x63CA49F390DB504DULL, 0x6A3B3994E936772DULL, 0xE0213B65631BC440ULL, 
            0xEC287DFE07E95343ULL, 0xA2CAB2EEE3C8C00CULL, 0xF88E0E99D257B6D5ULL, 0x28590BC4574DAEF9ULL, 
            0xD00B358236CC09ADULL, 0x07D22D7AA82F7893ULL, 0x652BD07CE668912DULL, 0x123F88E378147235ULL, 
            0x8DD68BC7268289B9ULL, 0x0586304340ECDBF6ULL, 0x7E941DB3EE418CC2ULL, 0x699AD108D068CD7EULL, 
            0xE2335284A9E7A837ULL, 0x8FF830053D51790AULL, 0xFBCF1EEC688A60A5ULL, 0x5052A676D3B0529FULL, 
            0x98751C4E93F613FEULL, 0x91C5E5995A7FA16BULL, 0xD0194D60A614646EULL, 0x2CCD33E17BD14138ULL, 
            0x65443C2BA7421990ULL, 0xAD58AF934A56F1E6ULL, 0xCDD338699CBAA659ULL, 0x4B500B9980070920ULL
        },
        {
            0x7D0D4714A760DB74ULL, 0x5D966D578DA257E5ULL, 0x557B307DEC8727E2ULL, 0xE9E9758AD9C52245ULL, 
            0x9D397152C1D052B6ULL, 0x3D204B190F8B6F13ULL, 0x56220C6A783E8F26ULL, 0x808073505AF255A3ULL, 
            0xAAFFC5CBD75943B2ULL, 0x57D46B22854A3413ULL, 0xC27140F87F066B80ULL, 0x44D0305AD8E33DDAULL, 
            0x44A8B48F6C0730EFULL, 0xB4DCF216770DDE0AULL, 0xDF4186426FC55FBEULL, 0x18A24453573CE006ULL, 
            0x7106EE3B91EB8915ULL, 0xB585137B8737E899ULL, 0x54A35CBA774C1E58ULL, 0x99D890519B4F2402ULL, 
            0x52CE0C170CBD47E1ULL, 0x4744B1B9DA0B244FULL, 0xD1518B7A5A07F445ULL, 0x5BECC72182F119AFULL, 
            0x5773209C771A0D10ULL, 0x0C09B9FF2F3BD4D4ULL, 0xDC7AB43F397B7B7CULL, 0xD8622F2441B6E80FULL, 
            0xF963B0A957303069ULL, 0x0D9AE46A83857D64ULL, 0x2D8EC8CE1CF14883ULL, 0x4FF50A5E7B83B7E4ULL
        },
        {
            0xA77B4D3BE8678F6BULL, 0x46061F46617E1B15ULL, 0xD0F05305D33E98F4ULL, 0x5C60145DA428E558ULL, 
            0x686AF66C699DD34DULL, 0x3FB8E879A8D11167ULL, 0x45E849AE113652E3ULL, 0xDE81BE85B070C0C4ULL, 
            0xAACE0C7B1DAD4E4EULL, 0xF74D1DD8BB87942CULL, 0xEFC4E55398EF2176ULL, 0x173052DF2D921B66ULL, 
            0x03F87132FD008917ULL, 0xC1716036C110A594ULL, 0x826248C7B604C4DEULL, 0x33AEB6B52CAB3A26ULL, 
            0x2648D63A9AE40741ULL, 0x155EEE5BCA26A509ULL, 0x7E972E466FABAC43ULL, 0x506DB51578E73951ULL, 
            0xD97604E2A8285EBAULL, 0x4E3D51672388F533ULL, 0x89316505322ED244ULL, 0x99C3BF0D98183ECEULL, 
            0xB4BB53A09E730325ULL, 0xC1ABF475A027B582ULL, 0x856A73221CB32399ULL, 0xA2990AE2FB2F3973ULL, 
            0x12FEC6F0780A9EB8ULL, 0xA61B8C52C06A4BFDULL, 0x1F2208986FB2B37DULL, 0xFED4B140EEB38509ULL
        },
        {
            0x4F6C7EF77D74ADF0ULL, 0xC30EA8C1660F0F2AULL, 0x5E8B5A944E5E000AULL, 0x535E142F00E4506BULL, 
            0x482CC4A0F6D8A3B0ULL, 0x10AE923EA695890CULL, 0x8B28940AA3213F88ULL, 0x8E9F5972F19836ADULL, 
            0x2082A0A2A0A9DA71ULL, 0xC26899A62EF462DAULL, 0x572B0BE4BB70053DULL, 0x8F5C182ADA43FC23ULL, 
            0xF90720D0E9B9C353ULL, 0x84882D9019119B4FULL, 0x5377D691F8129EF7ULL, 0xF550E8EB4A470386ULL, 
            0x7D1CB6ED042FCE87ULL, 0xD8FB25475A11D568ULL, 0xFB223C57378E4E1FULL, 0x163C8C8419311442ULL, 
            0xA4774F2EC6452218ULL, 0x71C0291092C85399ULL, 0x8BE9A782B59565FFULL, 0x56DE33F94F8F54CDULL, 
            0x4D1D6B8924A11339ULL, 0xF275A11B33FB5DBBULL, 0xC22E2FEF08791DFFULL, 0xD264BFFDE0E33C2DULL, 
            0xB8BCBB7E91F86746ULL, 0xBBE8BD14BBE24A35ULL, 0xBDF32D1650C06046ULL, 0xBA60CC2108AAB7DDULL
        },
        {
            0xD89519A615015AA1ULL, 0xA70E1D50F53ACEC6ULL, 0xB1EE851A0993E09DULL, 0xFC9346717414B6DEULL, 
            0xA10A296A6942C756ULL, 0x4A34389A8534D3A7ULL, 0xDF23129B8142DB4FULL, 0x0A3B752F603A6BC4ULL, 
            0xD3A9D4FCE8AFFCCCULL, 0x549D3699EC9E784DULL, 0x055CE7E0E7EE8B3BULL, 0x47D2DE06510C9ADCULL, 
            0x030B1302CCE61001ULL, 0x4186D64738FF3DABULL, 0x025DEFA88F96979AULL, 0x3CA3CFD04F191110ULL, 
            0x796E40B8F5CD8F13ULL, 0x063F614C6D66BBE7ULL, 0x2706C6A893B19ADAULL, 0xAFFE043017ECA986ULL, 
            0xF6842FD683E27D35ULL, 0xE1A1C8615D22C8A9ULL, 0xE37FBC06701528C2ULL, 0x69940CFABC080CC8ULL, 
            0xFE1439F2B33433BDULL, 0x16FED3B847D10913ULL, 0x5DC26A515CDC8400ULL, 0xEB573B72769FDA53ULL, 
            0x4ED03416066EF31AULL, 0x576FD9DDD1788FD4ULL, 0x7FEF521A834052A6ULL, 0x5BAE22613955834CULL
        }
    },
    {
        {
            0x6B5B88C1B65D51CBULL, 0x7C35021A7F7697B8ULL, 0x9DEF6A918E801BBDULL, 0x33D4CA51F4C9D8CBULL, 
            0xFE7245CDE4A1F7C2ULL, 0x23EE31E14D654DD8ULL, 0xD18DD8566B8B1B8EULL, 0xC4AE6BE25A65283AULL, 
            0xB3C4EE7792ABD3A7ULL, 0x03E12B80C0D77223ULL, 0x61D675E74839E82DULL, 0xF84996B53B50E1F6ULL, 
            0x191B08BE511DCF6DULL, 0xF77CE3AD6725D8C2ULL, 0x69BE3BFFEDA6D8D0ULL, 0x6FD72644711E7EB0ULL, 
            0x527765E504E2652EULL, 0x9ED9AA4666F7DCF7ULL, 0x1EE04BF934730062ULL, 0x4657644B30D003D3ULL, 
            0x6D0BA488F5CAAB2FULL, 0xCAE04B82E9BE080BULL, 0x9895E4BC57B62DD1ULL, 0x8945886E6E21024BULL, 
            0x8644545C39BEC5DAULL, 0xBAE65DA7920CC011ULL, 0xC23E4277ADA0C491ULL, 0x67DFD248A0302E95ULL, 
            0x6CD6F758D31213B2ULL, 0x9D245EC19DC18E45ULL, 0x31934D0E9B44CE14ULL, 0x4E0454474CD4100FULL
        },
        {
            0x5FE2CF7775DA9D7EULL, 0x8485BA13A03E45C9ULL, 0xD25917AB2A795744ULL, 0xD72841A896D1806EULL, 
            0xB1DF3C79AAC90355ULL, 0xBC895DF01AAC9730ULL, 0x87392627C8A38F9CULL, 0x25C946FFFAAF9C00ULL, 
            0x6099FB44F49D1EC4ULL, 0x2D16AAA804A736A3ULL, 0x0C472574C7A4C205ULL, 0x910DA6FD723055A0ULL, 
            0xE8EC7DFEA60195D1ULL, 0x11C98FF83C0D8BA8ULL, 0xAAADC6675AA33D16ULL, 0xA4B86481C034BE13ULL, 
            0x7DC05BD96A1C60BCULL, 0xCD3FBE297160764DULL, 0x9439DD456D0A33C1ULL, 0x7F6B4F8DE39CB2DCULL, 
            0x1BC119265DEFFF1CULL, 0xEC8BFA0D780E892FULL, 0x867AF967B0E15042ULL, 0xC0BCE70202F17960ULL, 
            0xDBE005A1B332AB25ULL, 0x77697DD9526E36EBULL, 0x5250CB3CE5433F73ULL, 0x508BCC61E03EC349ULL, 
            0xA963DDCD2B112293ULL, 0xAF52AE832A85A964ULL, 0xFA8050BE66563B3FULL, 0x4FA1A6B2C366A945ULL
        },
        {
            0x06076BF32D079AF1ULL, 0xF7EE46358DB2FD4CULL, 0x9FDCF5FD9363B29BULL, 0xE06BA1F91BB50E4AULL, 
            0x2FFF29333A3B92BCULL, 0x5756B7F053B9EA54ULL, 0x9A121A3E6E919403ULL, 0x4395D6027D30ABA8ULL, 
            0xF8115BA55DE00B4BULL, 0x6206E4DEF018BCD7ULL, 0x1F86D98DF4E73197ULL, 0x5C9F009D220F5CD2ULL, 
            0xFFAF1636C039E0CBULL, 0x6B6F8874E8612FABULL, 0x83C301C4C3BA96C3ULL, 0x44040B62AAEF751BULL, 
            0x351CDB6F4D24F329ULL, 0xCB2093AAFB51AC03ULL, 0x4E2F6D30568AE9F3ULL, 0xFD26D8754028DA97ULL, 
            0x93FEAE1C67D50663ULL, 0x1711C6A20C2D422AULL, 0xF5F582F39DE7F578ULL, 0xCA0793D15C7672D6ULL, 
            0x28850398C67E8701ULL, 0x240B219E80352C42ULL, 0xA16DA1CDB5D3413BULL, 0xE146A9E71B27B1D1ULL, 
            0x2E3AE40F01F08D3CULL, 0xD2E8BF724F5E6C5AULL, 0x17E8BD52FE7CD9F4ULL, 0x33AED7DA1B5DFAFDULL
        },
        {
            0xB8C2C8AAC494837AULL, 0x69BD7CF68817C7B4ULL, 0x6C05B1BD1930750FULL, 0x96A07B1A481C322EULL, 
            0x16AD516314FE2137ULL, 0x1DC1589A4BD9CF02ULL, 0x8A549475BBA65771ULL, 0x78189172A553B057ULL, 
            0xE9A931E4693EEA3DULL, 0x9F9506C2B872BBE1ULL, 0x5500A4DD426C7AB7ULL, 0x48034E63B7725684ULL, 
            0x243C92D405A8108CULL, 0xAA62FD31198524F9ULL, 0xAA80783D03E170C2ULL, 0x2B5EB6C9E67B6FC2ULL, 
            0xA16A4EA4DC5D1432ULL, 0xECAB30BFF0BBC205ULL, 0xA1ADE7F0CB8880B7ULL, 0x91FCA8A4587A3DC3ULL, 
            0xA65EA21925DF8635ULL, 0x0972C86C1B293C82ULL, 0xF1BCC423BF81EE36ULL, 0xDDABC2F2640E8176ULL, 
            0x091898F409F9B6F0ULL, 0x6B671C3EB825AD40ULL, 0x3637A73C24338408ULL, 0x335643381871F8ACULL, 
            0x0E969F103F2550F3ULL, 0xAC647DC8C76F87ECULL, 0x4AFD8146FE4D95B1ULL, 0x94DFB03560C59F89ULL
        },
        {
            0x3EB3B610CE23C480ULL, 0xC2F4CC691FB53F48ULL, 0x8E7F0E84A73CCB97ULL, 0x61D1AC3DE98F239AULL, 
            0x7F6928F71FD14D6DULL, 0xF3190F0BF57AF19EULL, 0x423BF5FCB4A68298ULL, 0xED4D4125EE1DE09BULL, 
            0x31A5CBDECE969F38ULL, 0x7C669B41A496BC35ULL, 0x4C4A63D3D9455470ULL, 0x2ADE10CE375D78C0ULL, 
            0xE6CCA497C1059E79ULL, 0x3959720EAFBC8CF1ULL, 0x43F0EE5325BE5A92ULL, 0xDC51ECAFC8D2A5B9ULL, 
            0xD929E5E03BEA3EFAULL, 0x679EAA3CEF4CEC09ULL, 0x66E6A03356D12D6CULL, 0xBDA5F60E1D455DB5ULL, 
            0x456C53AC572E1B5EULL, 0x3ACE79476A52EBE7ULL, 0x5248ADA13480EF54ULL, 0x2CD44153594E2BC7ULL, 
            0x0312F245D8010323ULL, 0x835FEE8406DF44BAULL, 0x1E93A20B64691D07ULL, 0x55C4ABBA66FA08B8ULL, 
            0x3B7C3D11648E65D4ULL, 0x9BF685FFC42DF230ULL, 0x501265D1BE734C56ULL, 0x299D62F6C1D3F611ULL
        },
        {
            0x9E7A0B94AB689D6FULL, 0x6AFC748DAE28C01AULL, 0xED3DE7AD20422A21ULL, 0x1E96D4578EBD70B8ULL, 
            0x16E53BD0A1616E56ULL, 0xF3E7B291784E651EULL, 0xEB3735A3D972BA17ULL, 0xD131F9FB28787FDDULL, 
            0x9A95B3798B3C9FDFULL, 0x1962B7E24E721B3EULL, 0x4586B52589BE89D4ULL, 0x36CE7D4B72185DE7ULL, 
            0x0D7C2041CA769FF1ULL, 0xCDFAA88A29D11C26ULL, 0xF6992D16DBD0FCAFULL, 0x7B9463EA6308EC5AULL, 
            0x2D22853951E50544ULL, 0x2648689274D55CB6ULL, 0xFEF1A870A5E17730ULL, 0x9E723B9FA1D0F045ULL, 
            0xEA95CBE33B6C9C34ULL, 0x33D598173427B164ULL, 0x53EE4DFC67292D5FULL, 0xF905244142546EEDULL, 
            0x7B5F56B771409FFDULL, 0x730400FD06C4AD04ULL, 0x7AE70E5DEAC33756ULL, 0x849F24DA2EBF886DULL, 
            0x8B5B97E8B5A6C485ULL, 0x41F04E03E73C5B86ULL, 0x03A0E8AB4C8681A7ULL, 0x0833C7AE060D634CULL
        }
    },
    {
        {
            0x48F7692A2EE961CDULL, 0x49AF278A65C8E8B5ULL, 0x25F4F827BAE37A3AULL, 0x7DFB0391EB712857ULL, 
            0xD79AF43642101BA1ULL, 0xE94A38A34A79DA54ULL, 0xDDA93AF16E57D9A5ULL, 0xEF7C9CA94B34C8D5ULL, 
            0x511A3B2DC65C89F7ULL, 0x41CDD1B9DD8C4D41ULL, 0xC80424C7DE746345ULL, 0xFBAB0D9CABF73159ULL, 
            0x654CC28D0EAF322FULL, 0x07630C28928BD847ULL, 0x304F64FEBCCE43C3ULL, 0x6FCCE37AFADE2411ULL, 
            0xED4B01DBF3206392ULL, 0xFE3C2263703086C5ULL, 0x803FDE3B19DDCA5FULL, 0x906A8EF13EA77700ULL, 
            0xAABAAF1D223DC245ULL, 0x047A5713B615A4C3ULL, 0x45FBD3E185664836ULL, 0x3EE321D7FBD44581ULL, 
            0xE7E5D9DEED92EBA2ULL, 0x56B2A04B3566AB17ULL, 0x2DE8CEE44B77CCB3ULL, 0xB2C4E442208A8438ULL, 
            0x48C3682B40800E2DULL, 0x00D8ED3F2E333E4AULL, 0xF9120D1459995F00ULL, 0xE67E2A41B68098EBULL
        },
        {
            0x626D547D64B6EB79ULL, 0x7A57B296C201B0FEULL, 0x6BA57F488F5655F1ULL, 0x495B954A6FB61F75ULL, 
            0xF8AD224EF773614DULL, 0x07CEE7F908055DE5ULL, 0x5B6317DF4D952091ULL, 0xAB569FB2BC035F31ULL, 
            0x7C0AC5B02E5AB49DULL, 0xE26FBF4D24530890ULL, 0x108E89FBC1B7638FULL, 0x40FFDB8BCAA6195CULL, 
            0x755052F10B86792DULL, 0xD9F3BED5EBE83EC5ULL, 0x4DF746B55AE4FDDBULL, 0x24F103FFC89BAF60ULL, 
            0x1C43B0E3BC607A3AULL, 0x6FD373F2951D505AULL, 0x09695862D681206BULL, 0xC842EB2B7B4553B5ULL, 
            0xD4BE4228D8065E2FULL, 0x59553F3CE7BAE196ULL, 0x72E8861B00DCA857ULL, 0x06B0C1592E69BBE9ULL, 
            0x59CA468EA399A20BULL, 0x40D7A227B854FBB1ULL, 0xF94771E5A80FBAA4ULL, 0xEE909B3606C3E29EULL, 
            0x1C77883DE8F72BC3ULL, 0xBA6F8A225354FEBCULL, 0x28337375170E47D7ULL, 0x202CE317AE30C335ULL
        },
        {
            0xE82D8C3155AACBBDULL, 0x4234D8C2BCE2309FULL, 0x0EDD7D3FBA3DA65BULL, 0xFAC66B927ECE3D64ULL, 
            0x9FFD575F59D92851ULL, 0x8A60C97FD4F0C6A4ULL, 0x4F415834ED06DBE7ULL, 0x818F1936AF8C1310ULL, 
            0x9EBD3779EEDFBFA0ULL, 0x091C562641C6D6CAULL, 0xCF9171F404A1E804ULL, 0x431787BF70AC6D00ULL, 
            0x7D7A1C892E328089ULL, 0x6E7E460CEF1EA2C2ULL, 0xD619E865B4FB3AEDULL, 0xC0BE044A26BB7AD6ULL, 
            0xC1288EC7D0960F24ULL, 0x3661C07E974C4BA2ULL, 0x554316439C527E66ULL, 0xFA809F5AE5FF13B7ULL, 
            0x8D43DE5CD7DCF0B1ULL, 0xF8BCC686B0F07083ULL, 0xA43A9329C380D254ULL, 0x8EEF19892D4B5DE3ULL, 
            0x87EC3DDD84B67799ULL, 0xE595434C563102B7ULL, 0x2D2AC5E91C120A79ULL, 0x95BCDA3C89579DAFULL, 
            0xA5CD6D3FC6D798F0ULL, 0x809003F2DB8EC6D2ULL, 0xD18543EAE65E75EFULL, 0x217AB02BFCF3278AULL
        },
        {
            0xD23B1CF96B026E6CULL, 0xF462112B998F215BULL, 0x85C1D35266FA109DULL, 0xA6D29FCAE5881AB8ULL, 
            0x0A65F761254EA874ULL, 0xA97335A387BD9AA5ULL, 0x06E99298582D6D54ULL, 0x7E968E5DC3FDB022ULL, 
            0x55C4A60411332C38ULL, 0x12FAB5BBC04D1106ULL, 0x56F4754870633529ULL, 0xFCE91B271093693AULL, 
            0x44EFF4BFCE2BFB0BULL, 0x12D48792BC90A8EDULL, 0x26202F2AA8DAF21BULL, 0xD8B91F3F9033313EULL, 
            0x9EB5647B01F89D54ULL, 0xFC104265F5011048ULL, 0x7DE360C2FED4AA44ULL, 0x26B4913402B75B75ULL, 
            0xDDE41E74CFFFB7BDULL, 0x94702D41518410B4ULL, 0x1634C6D8BCD80C32ULL, 0xF30F6E7F8C53E547ULL, 
            0xAEC5615F4A002577ULL, 0x594D8701ED13FA1AULL, 0x7C7857FA263D8EB2ULL, 0x8A71C36084F9C77EULL, 
            0xD03D11CEA2F84290ULL, 0x46B0097F4A74041DULL, 0xD1308D62A5A30B39ULL, 0x0163E233FE2B7B2EULL
        },
        {
            0x6D87A648BCB77BF2ULL, 0x5F92D19343C0EC44ULL, 0x42803A61E99A71D4ULL, 0x2177C4432BE39C85ULL, 
            0x3243F3D87E456C31ULL, 0xDED63A7CC76D0C06ULL, 0x0A1E8023204E1E59ULL, 0x7F3837C86E2FCC42ULL, 
            0xB111772820E04FFCULL, 0xE7E52B29F9464D72ULL, 0xE26472FD4C7E5C1FULL, 0x494ACA70AD38F283ULL, 
            0x723C32FE653DAFE0ULL, 0x0B7E4A8F5AA651CAULL, 0x264DF128DF737BF9ULL, 0xA996F59B5BEB98B9ULL, 
            0x8B167ADE2B5818F8ULL, 0x3822383AE2812527ULL, 0x43A24D07B569054CULL, 0x0D78661AEB924C5BULL, 
            0xE11D1E3AC58D36ACULL, 0x32AFBEB1708654ECULL, 0x3F115698365ACFAAULL, 0x268FFF6FB81E816AULL, 
            0x6E9310AB3202B602ULL, 0xC6035014B58A44BFULL, 0x3EB7A0D33D58A54EULL, 0xF66434AA30FD6EF2ULL, 
            0xF889B93BFA6ED783ULL, 0x48C96E4CA7234F16ULL, 0xD08BD641861DA6C3ULL, 0x5DFDE85BDEB0B61CULL
        },
        {
            0x51B4B9C5E86B551BULL, 0x533863750381E6B0ULL, 0x643A6E37165A8097ULL, 0x61AE5399BA74DA63ULL, 
            0x52751470A7B1ADC9ULL, 0x71836B39D5B9F81AULL, 0x003827B6BBE05F83ULL, 0x912A333F7C1DD52FULL, 
            0x75483D5D6B6D9420ULL, 0x29531473EC5AE7FBULL, 0xD9AECCC8826EAAC2ULL, 0xD86584FEF5FFA7E3ULL, 
            0x7D7B008CB4E5B8F8ULL, 0x068308AEB26A025EULL, 0x9CCB563A862338E2ULL, 0x1216E2D4B3A0D49FULL, 
            0x4E93521336F209DAULL, 0x0F7E7AB7CAEF0AC9ULL, 0xFDDA61B43A9CB1EDULL, 0x60CC61D2D28FDCD1ULL, 
            0xECE3A399D82BEB34ULL, 0x6D9772E7CC68A526ULL, 0x3C19CB0252538B1CULL, 0x1CB290EB8FC00D03ULL, 
            0x67568216F1DD4913ULL, 0x198E7C1246ADCF33ULL, 0x49C15E5358FD1CF8ULL, 0xF3CCFEEF029FE4D4ULL, 
            0xF07BACD4493B951AULL, 0x4769E37F603FD1FBULL, 0x50179DB790740196ULL, 0xB53B64887696482CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseCConstants = {
    0xE22171465C3FE155ULL,
    0x8A49770E304AFDC0ULL,
    0xE9D938F725A3259EULL,
    0xE22171465C3FE155ULL,
    0x8A49770E304AFDC0ULL,
    0xE9D938F725A3259EULL,
    0x0581526E7FA7A430ULL,
    0x4614B07F6B878CBBULL,
    0xF6,
    0x95,
    0x3F,
    0xED,
    0xC1,
    0x6A,
    0x73,
    0xDE
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseDSalts = {
    {
        {
            0x60AB259880B89AA0ULL, 0x79B18766C70B9374ULL, 0x6F75A456C379CD78ULL, 0x5D09C0A50A079194ULL, 
            0x3E10FE7D17EC49CFULL, 0x964A6E7D8C0A0B59ULL, 0x5A31998E4AB9B422ULL, 0x3C24AB02FE3E4629ULL, 
            0xD485E07D7DD62E3DULL, 0x1124244B69545064ULL, 0x70964C2419DA88C4ULL, 0xD5A5530FEED0CBBDULL, 
            0xF077B9823926F89BULL, 0x96942938BDF853C8ULL, 0x0914ED18A15AD5F8ULL, 0x2D83204735070175ULL, 
            0x7FBDFFDA79497851ULL, 0x9F170D5663785136ULL, 0x57E5DD1B66AC3D80ULL, 0xAF9C6AC3FA609F05ULL, 
            0x3CB563CCD370411BULL, 0x92899FF67A0A5344ULL, 0x71736725BC5ABB2EULL, 0xAF1E18FD02735EBFULL, 
            0x9CACD0AFF965718DULL, 0x42D0FBF92C95CA1BULL, 0x144C0BA466B95D57ULL, 0xACC179ACEC229415ULL, 
            0x13DD0533DF7EF6B8ULL, 0xCE6D9EAE360BABE0ULL, 0x350210353E311F42ULL, 0x5D1673DC5A116E9FULL
        },
        {
            0xFBCA249CB902FB30ULL, 0x9F27130837798733ULL, 0x53BEE22218995C03ULL, 0xF1CF5BBCAB0FAFFBULL, 
            0x559A065FAEAAD3E2ULL, 0x216F3BF68A75B222ULL, 0x32049657E03BCF2BULL, 0xF6297D09A9B7B220ULL, 
            0xD2953D1056ABE0A9ULL, 0x035F816EC976E83AULL, 0x75110B0CDE4B6BB2ULL, 0xF543E1C609BE8CF7ULL, 
            0xE10D700EEF32C108ULL, 0xA334DCD886FD3922ULL, 0x45E7D9EBBDA69D50ULL, 0xFAAF1080D32062A9ULL, 
            0xDCB5085CFBF2C48DULL, 0x8AF7E0E34C20E225ULL, 0xE6C5572ABF90DCBBULL, 0x26CB49B999E3B1D6ULL, 
            0x42FBA4009D5F0155ULL, 0xA6476FED8925E074ULL, 0xBD533A6E52906F0EULL, 0x3B12B943595B5D33ULL, 
            0x711EE83DCC06EFB9ULL, 0x9602B56E1C9AB730ULL, 0x6BFCDAEC2F815492ULL, 0xCEF14DE4362C984EULL, 
            0xD52B2CAD5F621B12ULL, 0xA796054249B05E03ULL, 0xB0A10C05E04425F2ULL, 0x671027CADD78A4A6ULL
        },
        {
            0xCD93274A176DAF34ULL, 0x9DAB62306113A0EEULL, 0x87B6007E5090E28EULL, 0x6387BE8560ACE48EULL, 
            0x83815AD53151DAD3ULL, 0x13C48C7EDC2934FEULL, 0x8E115143218650ABULL, 0x309634D5C6BC34B0ULL, 
            0xD89057C89DD1B7EDULL, 0xB2BBA4322F6699A6ULL, 0x3C6DBB3D1D839B0DULL, 0x465B8326101EF3B3ULL, 
            0x4FAF556267318416ULL, 0x4C480F2AA1E1CFFBULL, 0x01BEB79574D2345CULL, 0xA2C8FAEB2E9EAF5AULL, 
            0x89354048EDA90C1AULL, 0xD8769D06E7FAFA5FULL, 0x77ADB14CD0A2EE71ULL, 0x4EA3AF21F578709FULL, 
            0x4368228ED8C35B36ULL, 0xFF290947BFF0FAF8ULL, 0x8F028D1934116B51ULL, 0xED955DC3BB761785ULL, 
            0x079E92D39709223AULL, 0x575759FC890C8A75ULL, 0xB948EC643F506957ULL, 0xCD3553BA24DCC792ULL, 
            0x1F1E139BC8A30E55ULL, 0x6110C8CCC839A79DULL, 0xE50621ADD9FF2705ULL, 0x43922CF3357F5B09ULL
        },
        {
            0xFFD87B008D9321A8ULL, 0x9CAAB75D3BFF9DD3ULL, 0x62F325B0475D22B8ULL, 0x63386DB6CC99D8C8ULL, 
            0x12594389B682ED3DULL, 0x22EF21594ADD604BULL, 0x9BB4312AC561F87CULL, 0xD8F8A719575290FEULL, 
            0x3CD9E5A1BD6CCC0FULL, 0x43A7B878D1582FA8ULL, 0x212D3CEA4C5561BEULL, 0x7A946CD58DCF3389ULL, 
            0x98C5E7E54C3032C7ULL, 0x57284C844DA414C1ULL, 0xC7D0B1CAF4DED179ULL, 0x2EBB0EED46ED3636ULL, 
            0x701FCD3FD0215FECULL, 0xD6BDE80AFE380D7DULL, 0x8DC826C3BC29ACD7ULL, 0x569CC94F7621B31CULL, 
            0x53438FE7705752D9ULL, 0x41690CADF9EBEDE1ULL, 0x46FB1F68490499B2ULL, 0x139AFA76263BF447ULL, 
            0x4F24A39DBC2BB375ULL, 0x02C03B29456DE7CAULL, 0x318D5663EA42DAB8ULL, 0xE1B6868E73474E37ULL, 
            0x0F724DC388CBCA00ULL, 0x4C443C27E8023124ULL, 0x187347C45271F12EULL, 0x139315F10533E4B5ULL
        },
        {
            0x216A551530950647ULL, 0xBA0B195753E21794ULL, 0x33EC28A17EF5B4C6ULL, 0xF6AE7BE0654D6C6AULL, 
            0xEB5E08CCE850E6D5ULL, 0x4D96BA90D7D9BA4FULL, 0xD1649E996DFC6B76ULL, 0xCAFA1CF01A5B9F59ULL, 
            0x57194FA1E88266EBULL, 0xBEBFFC3C911B94C8ULL, 0x0A3BF209FD7951CFULL, 0xD8F5F898BCB83FBFULL, 
            0x43D8913D9C023DCEULL, 0x35C9803AD60563CAULL, 0x82461416160146ADULL, 0x67E94C40AC571749ULL, 
            0x54B3DB9A5B959E84ULL, 0xB43F14BEB005CC1EULL, 0x19CA376674CA4BA6ULL, 0x9B382C6194A3D692ULL, 
            0x5E8C2C48C37DAB21ULL, 0x65685DD155D44824ULL, 0x4BEE9A73948345EEULL, 0x8DCD55E6274D1F01ULL, 
            0x260393B78CF9F867ULL, 0x60214BC04BBB64C0ULL, 0x22C9AAEC43ACA3CDULL, 0xABDE0AD01D44B853ULL, 
            0xF3BA52A5B07F5B71ULL, 0x585CC478D1B3BF15ULL, 0xB5C28E80476651BFULL, 0x45430B72F8F14DB1ULL
        },
        {
            0x05AC765B627AC7A8ULL, 0xE71FAB4155D9CC9DULL, 0x4094359C50521C60ULL, 0x5B9E611DA44B4910ULL, 
            0x8C2E4B8080BAB8F6ULL, 0xBB9C8EB1C7FDA399ULL, 0xDA27FF74C261D5BAULL, 0xE7BF5A96E9B3C4AEULL, 
            0xD0A603FB3331355CULL, 0x1A79D6B219873E50ULL, 0x7BFA9CBB4048A42CULL, 0x4E6DD1682AE3B38BULL, 
            0xA8512DE75C2751C5ULL, 0x35417FEAB3E4495EULL, 0x11522A7AA57D0BC2ULL, 0x430E61B590F6188AULL, 
            0x54F94F9E5DC39C52ULL, 0x92A5288FD59F7562ULL, 0xAFFA742D347746BEULL, 0xFCDCDADA8E7B2695ULL, 
            0x0B8007FB004C8AAFULL, 0x31CF19380F22A471ULL, 0x681E1C8F22D98128ULL, 0xDAD057D88B6986A5ULL, 
            0xCACFE331B71F2DBDULL, 0x4409DD15696FA8ABULL, 0x196A5BCEA99828CEULL, 0xAD1F9D3E33E7FF5CULL, 
            0xFD0F0935AE430A35ULL, 0x8FE3D0455D2DA1A9ULL, 0xFD8DBE745053CC26ULL, 0xAD69567251E01117ULL
        }
    },
    {
        {
            0xF94B9FE86BA70192ULL, 0xBBEF7D7C7D97C0FBULL, 0x2E347581E9E0CFEBULL, 0xB5F6D529BE6DA8FBULL, 
            0x05EE417789628A5EULL, 0xC630B7917BCB4A45ULL, 0xDC0B27A68ECF0A55ULL, 0xBD797FA042F29FEEULL, 
            0x3873FEE4DC760305ULL, 0xE5FDE3F233A160D9ULL, 0xE00FD115AC757B82ULL, 0x1B5C70494082F835ULL, 
            0x4B04E6BBE83BBF9AULL, 0xC7D8F2CF07B6C217ULL, 0x7E77D90DFD80DB18ULL, 0xF8C55EC2FE33296CULL, 
            0xA7D4A3731675D35BULL, 0x8A923D23EAF013E7ULL, 0x807B504ECBD48EBFULL, 0x9CF8188209FDCC05ULL, 
            0xC7144565A1445231ULL, 0x490D4AECEB18F69CULL, 0x9F190FBC5A5E027EULL, 0xE73167893884AD31ULL, 
            0xC786A1FB39C8BBF3ULL, 0xC54BC8A41F39E89DULL, 0x8247AC7B74A7080FULL, 0x470C1FA45D65EF50ULL, 
            0x37196608E3834499ULL, 0xD303D38F1A4F5C90ULL, 0x1CD42F83A421B1D7ULL, 0x49B7BC113CD76709ULL
        },
        {
            0x7A093844BD84E0BFULL, 0x150DBEB299C8C996ULL, 0xBCB0D133632A3A57ULL, 0xBED1E04F5C93064EULL, 
            0x5102A0808A380657ULL, 0xF70E610666922E07ULL, 0x293ACAF1C897033DULL, 0x960040A90D2A2FFEULL, 
            0x466F89F5060C1689ULL, 0xC8276071A2E6C66BULL, 0x7EEBBB1ECB192658ULL, 0x49B87AC6071EC3F6ULL, 
            0xE11132F1EF4AE2E0ULL, 0x8F00E50CA5D95957ULL, 0xE53ABB5711861A2EULL, 0x789F66BEACC16F0DULL, 
            0x5C23F5DE566B43C5ULL, 0x2F36733A16B3F5CCULL, 0x6BB7437589B0089EULL, 0x16FE1B02D9B5944FULL, 
            0xE8D445DD18186F23ULL, 0x7604BD74C56719D5ULL, 0x158AC8B50E2F9687ULL, 0x9CE025A22E93275CULL, 
            0x126A6FB954EC092FULL, 0xEBCDC53243EA7CB4ULL, 0xBBBA87B08BB7CBDCULL, 0x2F0B444C1B4E7DA2ULL, 
            0x635BC034C08F109AULL, 0x3DDF169C872A0905ULL, 0xF4D261DBCCEB1C82ULL, 0x7A9425544577F715ULL
        },
        {
            0x40404136A74B5A15ULL, 0xEF7713F0202FDF33ULL, 0xFD8B41DF500D6BDEULL, 0x434A84780F8FE3F2ULL, 
            0x4DE86912C7C7A190ULL, 0x246881AFD35CD0A6ULL, 0x23F113C2DDB52B3FULL, 0x3BB8A738089FA419ULL, 
            0xB042112AF75AFC6DULL, 0x9AE69F089D8BBA18ULL, 0xA5C3F9D6C7B22191ULL, 0x0EA2D1F5EEAB8BACULL, 
            0xAEF25A301BE81AA8ULL, 0x9975488514D9C3CCULL, 0x41D059D716888BD3ULL, 0xC099568DA938F252ULL, 
            0x14B27938C4FD5622ULL, 0xA672081BF32474B7ULL, 0x57F9E468C3567779ULL, 0x0923DB6D931FA546ULL, 
            0x071AC5E500A4FD3DULL, 0x90B7505A633D006AULL, 0xD12C30005A72D020ULL, 0x69F0A9E00D63477DULL, 
            0xCC44AFA3EFB785FFULL, 0xD0FE7E0F561B0D39ULL, 0x3FD6B3322604130AULL, 0x5BCA3CF5E928423AULL, 
            0x9B744A989B49CE79ULL, 0xECABA8C2A039F2D0ULL, 0x1DB4352024E2F116ULL, 0xE7D2AD603D532DBAULL
        },
        {
            0x5243B790655A8897ULL, 0xE09FEBE064597DBBULL, 0x0BF42821EA6DC517ULL, 0x3F1F0608D4978A1EULL, 
            0x389192B6B3255035ULL, 0xEC75B3827624D1E8ULL, 0xD5504B2704A630C5ULL, 0xD64539E75768C285ULL, 
            0x7CA549F463C44909ULL, 0xD6040FEA922A1711ULL, 0x9D837327CC444412ULL, 0xC1FCC1DB6E38A02CULL, 
            0xA52F5AADC1A6ACD2ULL, 0xE404575FFF6903C9ULL, 0x4B8F0DCBE5A15BDBULL, 0x1A6EECC50D272E41ULL, 
            0x8405F05B604D3460ULL, 0x235674FF4E1A670EULL, 0x9049FCDA06A456BCULL, 0x1E33D05D409293D8ULL, 
            0xA912C78035AE76CAULL, 0xD6CE6890EE4646B9ULL, 0x3AB59497F21A3BF9ULL, 0x9BCF97B0A24BA818ULL, 
            0x7D1070391543AC47ULL, 0xB7D67B3722B0CD6CULL, 0xE20314B78E161498ULL, 0xF5980BE8A5666958ULL, 
            0xF31767D27E9FB332ULL, 0x9FBAA15C218631BAULL, 0xF9030198D769A80EULL, 0x9CA5BB90A792475CULL
        },
        {
            0x8FD7B436A02A284EULL, 0x4BF37D6449D4D478ULL, 0x70C7D7D86CD6C855ULL, 0x13E76BA2A98BB186ULL, 
            0xA3C32D99ACA7A974ULL, 0xE876934A651590CDULL, 0xBA807B653DEF7F9DULL, 0xBB56799383AE4D51ULL, 
            0xB9B6A6A18D9E8516ULL, 0x3B82454D5DBBC908ULL, 0x2CC1D65C805B0942ULL, 0xFE6229792C244266ULL, 
            0xCC70019A3F145E27ULL, 0xED637FDBA230DBE8ULL, 0x3F9D1600E625C412ULL, 0x1426D6E9E6FEEE7DULL, 
            0x9D4388285A65F4DBULL, 0xF197C6320027EBACULL, 0x255EC921CA9EED88ULL, 0x910CC9D4C1A5C7B1ULL, 
            0x89C46AE66B188EB7ULL, 0xD394A2203BDD65E2ULL, 0xFCF7AF572A59C6CAULL, 0xE88CB67A16332691ULL, 
            0xC63F80773E525352ULL, 0xB56C62952EEF7C7BULL, 0x0DFA83B241B7DE1CULL, 0x81DE09162D19142EULL, 
            0xF2B3ECCC0FF9F20FULL, 0xC7B79A6F0FA997E7ULL, 0x91B13EF76CBEDD88ULL, 0x2FE5E92BA11B9DC2ULL
        },
        {
            0xD708233ADF96A0B7ULL, 0x221F01784F48D2C5ULL, 0x4244B5AFDCA545EDULL, 0xFD2E87740608FA95ULL, 
            0x29882BC32FED2889ULL, 0x209612F12F02CE4FULL, 0xE1BF043CBBE265C7ULL, 0x046006E015ECD56DULL, 
            0x743B520B4D8DCAFBULL, 0x96CB7C88FE3423FFULL, 0x121B39AAABDD8D9CULL, 0x2C215329C93BC4E0ULL, 
            0x5781AED1FDF482D7ULL, 0xDFD4343B5E546D9EULL, 0xC70DCF0085A0A4C8ULL, 0xD227D8224158970BULL, 
            0x818D8A0ED19D66D3ULL, 0x3D96CB48C31FE8BBULL, 0x5AB773FF89D48A21ULL, 0x8A7833515AD39ECAULL, 
            0xD65BF7C0ED0D9E2DULL, 0x7B70689C08AC610BULL, 0xCD4CCFE5EDDDDA47ULL, 0x303B18121DB4AC23ULL, 
            0x01D63D05A452CFFDULL, 0x76114228EB908DE3ULL, 0x0EF34016A679C156ULL, 0x24A317EDDD5F269CULL, 
            0x9BB43BF8FB9366F6ULL, 0xFCB604A12ADD1DA7ULL, 0x063903DBB768C42EULL, 0x4875A999EB0431A3ULL
        }
    },
    {
        {
            0x774441049F2D920DULL, 0xAD26EC433721EB69ULL, 0xCE5E8AB9534DC559ULL, 0xAD2CA5BA3F22ADC3ULL, 
            0x72AD8E5928FD11D4ULL, 0x34226CA79A006582ULL, 0xC37D0D8F4F5F963CULL, 0xA40922E6CE7C7DEEULL, 
            0x476457CBCA2D9DFCULL, 0xEEAAFA05C33753D2ULL, 0x97C1D0BA8CD10A95ULL, 0xA13DB0C8FD4D5D5CULL, 
            0xE942BA67FB986F8CULL, 0x7C37D3CCDE2FE05DULL, 0x82A2FB618E5BDBCBULL, 0x7FE8B5691116B0B3ULL, 
            0xC8B23C363D6D4804ULL, 0xADB4DC249E8EBBCBULL, 0x47434BE1DAE2B82AULL, 0x3A8E89DE7B012BD2ULL, 
            0xC3A1F8E4314A3B4BULL, 0x3853D5E0CA70750BULL, 0x42EF0B2B0B6B6AF5ULL, 0x603BEF99E8BDC78CULL, 
            0x50DA125561E15BB1ULL, 0x1D8B60F00AE13ACAULL, 0xD2472B36BC9EB2A6ULL, 0xD24BD9D0093C1D63ULL, 
            0x660C428D55386873ULL, 0x7A1E2EDC3771D1A7ULL, 0x98354BD2FEEF54C9ULL, 0xD05110F5137A156BULL
        },
        {
            0xAB21CD864570C3D2ULL, 0x5AB71A92AE0030E5ULL, 0x6EB1752393671B4AULL, 0x3113C052E51795F5ULL, 
            0x896BD6ED56E8F7FAULL, 0x10232C44A418E4C9ULL, 0x1B16D716A7B241A7ULL, 0x98DF5F11015D930BULL, 
            0x65033FB56B26E3E0ULL, 0xD9A55C1CAF560015ULL, 0x55FA3780B950CED2ULL, 0x18A5CE1431806D40ULL, 
            0x51E4876E26672C14ULL, 0x9C273E7D9E3E4260ULL, 0x4D03EFFBB6830FABULL, 0x8798651DF7A2CF76ULL, 
            0x53E5A29341D15C17ULL, 0xA7625977F74FD556ULL, 0x8DCFCD1C863369BBULL, 0x06334499FE09AC06ULL, 
            0x679150AA2AFAD8C8ULL, 0xDBA15CF74C3172F6ULL, 0x5FCEB24B39662A4EULL, 0x4731FBDBEF5BC0DDULL, 
            0x126E10E5C7213E60ULL, 0x94DD7ADE74C858BCULL, 0xFC81E0F43DAD6AA5ULL, 0x14329FF4D3AC97E0ULL, 
            0xB2E9D527B377EE43ULL, 0xB39951EC936EEDB5ULL, 0x59CC3243546975E7ULL, 0xB4C46CC5DEA75F35ULL
        },
        {
            0x4C5AC5BD47DAFED0ULL, 0x5A5BA075E447A2B0ULL, 0x2FBE9C0E97801E7CULL, 0x57122255CE561365ULL, 
            0xC32E8EA17C205237ULL, 0x1519268ABCD4114DULL, 0xBD5AC8603E53812CULL, 0x0986C3D7819C2892ULL, 
            0xCF177CBD9895B77FULL, 0x14AE06A57B668677ULL, 0xB667CBF1353EA327ULL, 0x1DB15C739EE64CE9ULL, 
            0x55F377FE9371B167ULL, 0x70C6B85F040CFA62ULL, 0x20CD000721278877ULL, 0x22CFC113978D5BBDULL, 
            0x189291AD9A466696ULL, 0xCEDC425EFE2F72BEULL, 0xCCDB1E3F857ED59CULL, 0x6CB8E097BA0CF51BULL, 
            0x5E82E4026265672CULL, 0xFFAF4036D1446240ULL, 0x3E4EDA9B847AA6D2ULL, 0x8D17C2E91FC4D076ULL, 
            0xB988573B85DE81B7ULL, 0x5734CF3F87228D92ULL, 0xC73775BFC0B0154DULL, 0xB2A01BF0CD84F803ULL, 
            0xCF1B03B2F99493AEULL, 0x13F8541116DAEDA6ULL, 0x48B45775F4C76D89ULL, 0x328FE7BDE144A730ULL
        },
        {
            0x86D7CC784489C57EULL, 0xDBB06F90D7D8FEDBULL, 0x7242DB6B6514A8B1ULL, 0xF9201746DE9AE15EULL, 
            0x943C634F50DA4F01ULL, 0x6CFA463D084B283BULL, 0x53B18A1012EF100BULL, 0x940B857C2FA18D34ULL, 
            0x61F2543AEAF76CAAULL, 0xA142E1A1325A4C3AULL, 0xDFC46405E1C97AD7ULL, 0x0881D1408407F92FULL, 
            0x56B0351D1CCE9CFAULL, 0x770937F1EB032BE3ULL, 0x886CA3864B308D17ULL, 0x8AF7BD659C78083AULL, 
            0x97F8863BEA160415ULL, 0x7C6481C33FAB0D21ULL, 0x6FD9E00499651E2DULL, 0x22146AFBBDA05C1BULL, 
            0x4B23C70E8AC7CC8DULL, 0xDCE0F18CF84D54D1ULL, 0x0CF6863FBB1FC567ULL, 0x210FCADDD74C7093ULL, 
            0x8E8E22B5A0D1A854ULL, 0x21665066DAD51B9CULL, 0x54E4AB79A4B4BEB4ULL, 0x0AD6B755A9C52C36ULL, 
            0xD93B83C064B60215ULL, 0x542150EE77AD6A5EULL, 0x60EC6F06301F5E87ULL, 0x1FB368503664F277ULL
        },
        {
            0x8EB6EFB4C08A02BBULL, 0x43EA0EB9ED9DCB57ULL, 0x269B769E7122692EULL, 0xC4B4DDB48B67C578ULL, 
            0x953E0D136A74AD25ULL, 0x7FBABB12E359370DULL, 0x56F8F14CDBFD7C9BULL, 0x63EF8C308D4A8EADULL, 
            0x2DE79DE9EFF04FC1ULL, 0x04F464F887D6B948ULL, 0x711167D09E0B9A2CULL, 0x61F5ACF53C5D7A6AULL, 
            0x9D478DAC29EE69BCULL, 0x4C1910DF74B497AEULL, 0x4FC697AF04B758A0ULL, 0x095E2A75136C47E5ULL, 
            0xFBE4DDB1D455556CULL, 0x38411D39C8D4DAF9ULL, 0xAFFB710A1C126C9DULL, 0xB3330740F3D50CF6ULL, 
            0x956679404159EBEAULL, 0x5D0CBC16F9133701ULL, 0xE9954CCE741BBDF0ULL, 0x007D4FAE453CCA4FULL, 
            0x0D7D8EC33CBC5C93ULL, 0xDF3E884644C41DC6ULL, 0x80ABBC4B51A21C24ULL, 0x3D7DBFE457BA6D8FULL, 
            0xB56EF652B6110F9EULL, 0x2DC19B02A79E928EULL, 0x394832A8B416FC8EULL, 0x4DBFE3EF73B5ED3FULL
        },
        {
            0x9D6FBCD208440C4CULL, 0x34EE9BB359CB8537ULL, 0x8707D8EC323F8F1DULL, 0xA7EA415C62785182ULL, 
            0xB27DDB76E3BA0F2EULL, 0x8954A360AE045C02ULL, 0x7B6A6633B14F7F59ULL, 0x885749D790686AD2ULL, 
            0x1C288F7F3DB9F7EFULL, 0x2032A6E05DAD2A57ULL, 0x641231E718360E7BULL, 0x18D2D3A740EA6FF5ULL, 
            0xDDDDF8C21A34796AULL, 0x5C92E9F14ACF21A6ULL, 0x864D4F179D633493ULL, 0xC7A9360CD419A12EULL, 
            0xEEFFADDCEC743F64ULL, 0xAF92C93BE26050F8ULL, 0x2407022FB0B6F41DULL, 0xCDAD01A2432D303FULL, 
            0x1943DC983DA780CFULL, 0xA3F50429168DDB36ULL, 0x989D7ED31C31EBE0ULL, 0xD8CFEED34390673DULL, 
            0xF8705E24C8F41E58ULL, 0x2108FD640BBA4657ULL, 0x0A1DE17CACAC4AB0ULL, 0x0B9AD4147679F8CCULL, 
            0x490D113EDBB3E99BULL, 0x05D62D32FDD464E2ULL, 0xAACAFD07FC3F006EULL, 0x6D9664995B313109ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseDConstants = {
    0x9657EC932266904CULL,
    0x3A69A8FE0DBBC45EULL,
    0xE5EFF0CD90267F04ULL,
    0x9657EC932266904CULL,
    0x3A69A8FE0DBBC45EULL,
    0xE5EFF0CD90267F04ULL,
    0x3E42D51507742BAFULL,
    0x3D2E7D64C73FE4A5ULL,
    0xEF,
    0x8D,
    0xBA,
    0xAA,
    0x08,
    0x9C,
    0x97,
    0xB8
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseESalts = {
    {
        {
            0x4BAD022B110B3144ULL, 0xBB5AC47B1AC93F8CULL, 0xDBCC45EAE2210312ULL, 0xF5C46D9E0CB3BCFCULL, 
            0x8204F9693681BF7CULL, 0xE7290211609233F5ULL, 0xC7A008390711FA28ULL, 0xB44A7BCF2FE2A1A3ULL, 
            0x18EEE041E7999AADULL, 0xFC8A381A1EE70727ULL, 0xD0608D2E163F8F3AULL, 0x7FF7BD89DEDC4B42ULL, 
            0x3234B48EC917A8CBULL, 0xE17762946D21E62BULL, 0x7524B81DED0E6CBBULL, 0xE72165F3AA3B53B6ULL, 
            0xAABFD3C0E35278C6ULL, 0x8F160A28B1E201E7ULL, 0x64FD94A00EB931EAULL, 0xC3877B8F1206DA28ULL, 
            0x9C42FD379C680284ULL, 0xA0FF06FA97FD145CULL, 0x220D6D1F6FB641ADULL, 0xC754611D39ADFEDAULL, 
            0xE727F382D9C011ABULL, 0x4701AF2CFCB44306ULL, 0x7F9C81F1E04B494FULL, 0x581CAD734742261DULL, 
            0xEA558EF9411EB0DAULL, 0x5BFE952B0E38D863ULL, 0x006211A9E5C347D4ULL, 0xE1E2835EA39A3203ULL
        },
        {
            0xA688379BDDF6880FULL, 0xA5CA8B55F07426E3ULL, 0xBDC5E62FAA7F2AEAULL, 0x90CA444C1B4B62F4ULL, 
            0x7A833EE4EF41C9A3ULL, 0x7688B6FE4820FC1BULL, 0x7CA8F51D69E03304ULL, 0x0A3B5932C8C900B5ULL, 
            0xBC98F6A54BB0ABBEULL, 0x7AC6F9DB11B30D2BULL, 0xF12D5BD45DC048B2ULL, 0xF19171ABB94B0B03ULL, 
            0x718534954DEBA6B1ULL, 0x5A4D24C3F4E4A2B2ULL, 0xC6010828A05841B2ULL, 0xF4A63C1DCFD157EBULL, 
            0xB466D8F581666090ULL, 0x06037FC85E5914DEULL, 0xD3CC7A3FE21111DDULL, 0xB69DCE9A83B81C9AULL, 
            0x55230F481FDA76E4ULL, 0xB9C5774E4F475AA5ULL, 0x5BC3B4BEC15590E7ULL, 0x1DC9AE7558924161ULL, 
            0x0B11727EA87E948EULL, 0x801701D09E2771B3ULL, 0xECEE73507FFCF4C5ULL, 0x9ADBDDDB63DA5126ULL, 
            0x1DAEA3C8779FA01FULL, 0xFC3D67532B5A3A73ULL, 0x35FC4DA6C9BE88FDULL, 0x50368831FC289AE9ULL
        },
        {
            0xA9B822CF184690BAULL, 0xBB517DCA3EBC80D3ULL, 0xBD10171F152D33AAULL, 0x9F5C917AF4EF371BULL, 
            0x736B9DBB46EBED65ULL, 0x4DA0051059C532BEULL, 0xBFC12301903AE526ULL, 0xBE1C65A10687C88DULL, 
            0xE61147BA49C2E0BCULL, 0xD302E4C34007D5D3ULL, 0x26EC5ECA0466237BULL, 0x2A23391E641BA634ULL, 
            0x4683B9C7DB67925DULL, 0x70EB23145873BE45ULL, 0xA7A6A8AF3405E5E2ULL, 0xDEC2CA64A95115E2ULL, 
            0x5F5EB06D92523F9AULL, 0x50F9498C391E32EEULL, 0x5C4120ED40E6C7A4ULL, 0x0F6E828DAE35B3DAULL, 
            0xF09F39571D984793ULL, 0xA069E33798CD7F58ULL, 0x3D34F291350DC7BFULL, 0xA5A1E0B12A592927ULL, 
            0x7767C0608EC04FE9ULL, 0x6DF8D73557B1B45BULL, 0x0F9B6D2C47F2831EULL, 0xA86416C86B557771ULL, 
            0xCE8E56A41C43E2F0ULL, 0xA9D385112E93122CULL, 0x77301BFAA49C0EEAULL, 0xD8DEB43D4E0C9E2AULL
        },
        {
            0x4C1C7AB61BC6D44EULL, 0x0C5D88EA2F605A51ULL, 0x0FC3C9B2EAA69ECEULL, 0x8A9B9039BA3A458DULL, 
            0x2ABCB305A6411315ULL, 0x6391F6417B5D8E20ULL, 0x4BA5824DD4E69AB9ULL, 0xDED993688DFA8A54ULL, 
            0xCB75F2028B97CD01ULL, 0x367348D80ACA1558ULL, 0xA965C0095C197945ULL, 0xDF2D058FF5BDE383ULL, 
            0x6DDEDB8F62368946ULL, 0xA19428452215C99FULL, 0x735CE1C8DBA837D2ULL, 0x326D890F0EB9861AULL, 
            0x80A91F1692807D39ULL, 0xA3BBCFEC8C4E91A4ULL, 0x23266BC3AAB22740ULL, 0x50B39E5D86BCE1A6ULL, 
            0x379CC18CF459765FULL, 0x8C33B757A0620EE2ULL, 0x2FA2E9362A6B94ADULL, 0x2612ED85814F1EF5ULL, 
            0x993BFD402C187E13ULL, 0xF424287B515C63ADULL, 0xCEAD699AFEDD58E3ULL, 0xA44CC2E951981F1BULL, 
            0x64454AF9C7B81DE5ULL, 0x6787A2799A10E369ULL, 0x1E438A07693BA676ULL, 0xA0476B682D9CAEECULL
        },
        {
            0x0CCB560A999AE911ULL, 0x48A8F44D5817842AULL, 0xE7AE61C79446399FULL, 0x7C1ABDBE837781ECULL, 
            0xA82341AB90973058ULL, 0x44EE3DE036D15163ULL, 0xE4F86CAD055D4E3DULL, 0x4E1435CDFE1AC050ULL, 
            0x9164FADF1CE0E64AULL, 0x4CD96CBCB0DCB547ULL, 0x6D922C1E73FEF384ULL, 0x3A33E10639964972ULL, 
            0x7D1C42CF82752AD8ULL, 0x551489F807AF41F3ULL, 0xA4F47774991B263FULL, 0xE9C0E5D9F573624BULL, 
            0x95C532288C7BA1D7ULL, 0x2A39F8A9C10B51EBULL, 0x0871BC59CD6EEB9BULL, 0x0B8F7F53A7CE6337ULL, 
            0x9909823E14AD67BEULL, 0x666E88A145A28F46ULL, 0x6CA4D2C8F19ACE34ULL, 0xD27FB536E5DA2891ULL, 
            0x6019E733DAC26248ULL, 0x356C0ADBFB044E3BULL, 0x096E35DA53FCF157ULL, 0x8270D1E363B01E20ULL, 
            0x8A247EA210CD7AB2ULL, 0x531F1CE5FD4628F2ULL, 0xD2EF0B523AB94EA3ULL, 0x7A65930EAE7389DBULL
        },
        {
            0x87A62179BA42B153ULL, 0x88D626CFC843344AULL, 0x0CD751AF5D4425B4ULL, 0xD2BC11DF17E6CA85ULL, 
            0x03F42CAC01B3556CULL, 0x9397C7B29DBF735BULL, 0x7A96EB8E3F7DC8FAULL, 0x6CB3CFD1E5516E71ULL, 
            0x78A213364FEEAA43ULL, 0x7019D2944867C236ULL, 0x5E0B43924B9C5F45ULL, 0xA6FDF0FC69654017ULL, 
            0xF9A039684CF45AC1ULL, 0xBE3F46CCB16BE7BFULL, 0x2516E65D1D266EB0ULL, 0x4F7C7747463F3CA5ULL, 
            0x35002148991BF0A6ULL, 0xF34A898BF8D350A4ULL, 0x4EFCDE73793BAAEDULL, 0x0BDE453B0792B490ULL, 
            0x631888CAA0F1025CULL, 0x7AE48C9CD9DF45B6ULL, 0x5B6A688A80A2E461ULL, 0xC35A5BB0DF45B0BDULL, 
            0x71CDD3F54CFCB1F8ULL, 0xC458DB10A15B4071ULL, 0x235F9AD5F99AC4FCULL, 0x1125BAC5574BF9EFULL, 
            0xADA70FAB911D7FA8ULL, 0x58A704D32D39D071ULL, 0xB794309AB87F2EC8ULL, 0xD7E1414623AE22ECULL
        }
    },
    {
        {
            0xE21D593D099A5055ULL, 0x061596B08834CD57ULL, 0x1EF1E1A48BF59EC3ULL, 0x33E55E31CFF38870ULL, 
            0x346FF54A2AC0BED6ULL, 0x76213ADFFA286C6EULL, 0x12FF154597D4684AULL, 0x03158BF7E9F663D3ULL, 
            0x050306013444E377ULL, 0x7F49A4D0C1B38510ULL, 0x74A1C054BF1301C6ULL, 0xB3CFC85B6E1FCE51ULL, 
            0x13871C8BE343840AULL, 0x80BAAFD2BAB70595ULL, 0xB23347C91F25EA36ULL, 0x6AFA539824D46C67ULL, 
            0xC1E1F896328A6B4DULL, 0x4C274EFF25466455ULL, 0xF23E15C579573DC8ULL, 0x599F07C54BD038D2ULL, 
            0xA104A2C51D1950A0ULL, 0x9EC8A295EC8E86B6ULL, 0xDBDC20993CD49F05ULL, 0x285DE1BADC050EDAULL, 
            0xD1F68997E7928987ULL, 0x5443F3D54D7EA0A4ULL, 0x8FF986FBECFEDCC6ULL, 0x73ACFFDCE1B06E6EULL, 
            0xBA73426D14378672ULL, 0xF66F23016C407188ULL, 0x447F670349EF8E4BULL, 0x2A45BFE1CA24F492ULL
        },
        {
            0x6F7E4E77078843F9ULL, 0x72916A95367B6940ULL, 0x7042B02BD5B839CAULL, 0x7AAB258A83FFDA46ULL, 
            0xAC7B13D5D017FFBFULL, 0x90AA4F87E049ED9FULL, 0x9562E1FCD2DAA4C9ULL, 0x8EDACBFB27272950ULL, 
            0x6E14530157D9A517ULL, 0x43DDD08A7F830791ULL, 0x682F7A23C111E13DULL, 0x04955B8EC5631772ULL, 
            0xD899FAA21E72CE49ULL, 0x2F7BC559B1ECA4A1ULL, 0x3C15B73E47F32554ULL, 0x72E13F45F757496CULL, 
            0xCBF9CFD2B28F9AFFULL, 0x40A4A43FCED30BACULL, 0xA27CE31359D7D62DULL, 0x5F88B1C9BCCE8C33ULL, 
            0x88BA52260E7BB35CULL, 0x1884E80A3120AB64ULL, 0x4874D1B77999C864ULL, 0x045DEE981FE8C8B0ULL, 
            0x89F708DF70EAE9B6ULL, 0x76A20804E711D8B7ULL, 0xF463FDD7A9ED7E71ULL, 0xF15561E093213AB4ULL, 
            0x190300C2A8B00113ULL, 0x6B512A38ED46AE1CULL, 0xEEC0989115EF6D53ULL, 0x0FED7A65592047BCULL
        },
        {
            0xE4EA38CAD5CA8E9FULL, 0xE10CE6905A17E05AULL, 0x0177F3A44F85A538ULL, 0xA8EF2BCCFF8CC264ULL, 
            0x662014A691DB9C25ULL, 0xBE3920D47F5498A5ULL, 0x694A42B9A21B84D3ULL, 0xE1A554B894E4C3D1ULL, 
            0x98625E4D3E6A7B34ULL, 0x59E1C1D1841101E0ULL, 0xECC985F0EC45AF42ULL, 0x15D533CB896CF419ULL, 
            0x6B8BAD5048E5466CULL, 0x5D0F8597BC67CBBEULL, 0x499ABEFBDACFCF85ULL, 0xD87DCA0B57A2BA50ULL, 
            0xE6101082CAB5341CULL, 0x1AA820535C87D00BULL, 0x83D686CCAA825C1BULL, 0xD874F306BBFE8713ULL, 
            0xE7EC9230F62C7830ULL, 0xF082B81ADD5F3A49ULL, 0xDC99B0EDCFA6AD35ULL, 0x43A9C4FB134BBF2BULL, 
            0xA45E55556F69D26AULL, 0x2CB6DC1B68DECB5FULL, 0x053117E1DE2ABBBDULL, 0x4CF3C445342B3B75ULL, 
            0x078C4FF75B7FE676ULL, 0xD1094149685B13E0ULL, 0x537136914F34CC2CULL, 0x404B54966277AE91ULL
        },
        {
            0x1E2F227B5E05279CULL, 0x0137E7B799D90AB1ULL, 0x1883D606113F3C12ULL, 0x2F12C540CE408ED5ULL, 
            0xC7AC4E22BC8FA3C5ULL, 0x6584A4A07D4BD3BDULL, 0xD6A5F6E7EC449F16ULL, 0xB9BA1EAC42DDF5F8ULL, 
            0x809DAA8FC05C2F4EULL, 0x6F0B59AD0A6EC7B9ULL, 0x46E74B55059D4574ULL, 0x0A5BAD218A5357B0ULL, 
            0x8797BD4244BD02E3ULL, 0xC659D2F2850AD9D6ULL, 0x9E70C8E59D4D24BBULL, 0x8049F984746D517CULL, 
            0x1C62CD185DEA0A6AULL, 0x2D37B3BA0DFDD9AAULL, 0x671D2C768F1AC4CCULL, 0x5B0A0505EE1C2607ULL, 
            0xCCC33E085D71DBA9ULL, 0x608E3ACF692A5DEEULL, 0x3C1D04C0F06CBC7BULL, 0x921C661C664F362CULL, 
            0x6733004076F6510CULL, 0xF7626392C8287984ULL, 0xCA4DF0B5C239AA12ULL, 0xE073DC9558669D8FULL, 
            0xFE0FC40BF03DD4D8ULL, 0xDC952AC277AF2518ULL, 0xAE4E5022A1A46415ULL, 0xE26F39A5492D7DA3ULL
        },
        {
            0x56715E386EFE8947ULL, 0x56562F8C2A16F00DULL, 0x7229ACA4127B28FEULL, 0x2443045B55C9D5C7ULL, 
            0xDEAC20DA81B56BC4ULL, 0x76A442CC883522D4ULL, 0xE85F42B69CAF32F2ULL, 0x685D1AA2D29D4A0FULL, 
            0xEA452131F31E0DC2ULL, 0xDCE10FBD1C8BC903ULL, 0x941618AF05FD462DULL, 0x36DC716625145309ULL, 
            0x838E6A8C926E4EC0ULL, 0xB1D47EE7B922AED8ULL, 0x0B77B9C8DE706B5DULL, 0x604C2FC89B558C16ULL, 
            0x96F1B510820A91EAULL, 0xD561BBF7270FD161ULL, 0xA65A2E4300E0E79EULL, 0xF5BE71B540995772ULL, 
            0x91B0BC3BEC1741B3ULL, 0x1AFA1DC4968D2C8BULL, 0x9D71BEA5EDF1A1DFULL, 0xD342985C7B6B49ECULL, 
            0x8E93D17573998B52ULL, 0xFB129BB6885CD2B7ULL, 0x35BF82461B39C09DULL, 0xA87DA017ADC20E9CULL, 
            0x1CFC17875319A360ULL, 0x7A1DE0B2E754C850ULL, 0xB7244BBC718F9978ULL, 0x2932C301390D249BULL
        },
        {
            0x1757113D1CE9B899ULL, 0xDA9159E7F965DA60ULL, 0xBBD02E7D128ACE98ULL, 0xECC0345D727B22A5ULL, 
            0x167811BD221814CBULL, 0x537FE5AE57712B60ULL, 0xF2DF1187CDBDBCF3ULL, 0xE61B262F3264C870ULL, 
            0xFE1D5BE852B7F796ULL, 0xCB136668508D2997ULL, 0x170C28A1D0FFD5B7ULL, 0xC4C5A594C1026A5EULL, 
            0xF3A285AA70FFE7B9ULL, 0x1155A7B1B49BD581ULL, 0x30D2924C677C610BULL, 0xF3F1B11BDF35D0CBULL, 
            0x4277EF05B10BF964ULL, 0x6D86548D32FB4AB3ULL, 0x0C1D0EB231D4191DULL, 0x5E34EA3E7C7FB318ULL, 
            0xC68B98718660FB1EULL, 0x87F610BB7644C45DULL, 0x8D826DF013198BDFULL, 0x2816DD5E3B322C28ULL, 
            0x01D9A4104C1FFF5CULL, 0x075B658C0ABDA688ULL, 0x530142A1096653BFULL, 0xE79E1B8119A36F2BULL, 
            0x586475DEBC22D727ULL, 0xA57B145A18B17CF6ULL, 0xE6D40984AF6ADA76ULL, 0xDBCFF0B31343AF96ULL
        }
    },
    {
        {
            0x517B9BB2F22A3019ULL, 0xA4F539F3CAF49F79ULL, 0xCE619201714D31CDULL, 0x8EFAD1B69DA1458FULL, 
            0x7D99F818FA1C0626ULL, 0xF672433113CFB26DULL, 0xA97E28911EC06D30ULL, 0x98CB180C97B53548ULL, 
            0xCF6B6F59A1C906E2ULL, 0x68CDCE7703EA1ABDULL, 0x806F7973F8208D8EULL, 0x942A5FF30BDC7A55ULL, 
            0xE9E9C012D8FE9685ULL, 0xF8AAAFB5783E34A7ULL, 0x90F143A0C3EEF79DULL, 0x748E7A7FAC062D98ULL, 
            0x7D6D87B005DE9E2AULL, 0xDA04A150D0E74D03ULL, 0x7311764A25692546ULL, 0xC408B2DDA6DE9162ULL, 
            0x8AC0B4E08505C095ULL, 0xDF81CD2B551CA9F9ULL, 0x8AEF5B4D0EDBF070ULL, 0xE7C3D08256BF1F10ULL, 
            0x085C24E9E15A8143ULL, 0x690A2CAD7E90AE9FULL, 0x39B9E7597AA27D41ULL, 0xC2E173DCF92BB58CULL, 
            0x60AF54B1D791B203ULL, 0xAB445EBAE237E367ULL, 0x02FA14781016B581ULL, 0xFF8CEE28EF070D7CULL
        },
        {
            0x44E2C96C07C9AB10ULL, 0xBD34C182E2CD520BULL, 0x1A1F7008955AECE1ULL, 0x8ED4AEC62B3FA94BULL, 
            0x8176ECFB4BBE8CDBULL, 0xD917419530E455D1ULL, 0xC532B98B16B2E867ULL, 0x684FEA8DE5B50364ULL, 
            0x0986FEE6F7913558ULL, 0xC8B2D618E009DC64ULL, 0xF5FE3A28C7CADEB6ULL, 0xBC16FDA8D7753DCEULL, 
            0xC56F620DEBA9A451ULL, 0x9E707ADBFA4C7151ULL, 0x80CE5240F6E51202ULL, 0x87E214C84AA3FEECULL, 
            0x722CA51CAEF8DBC1ULL, 0x0D897542A50631BCULL, 0xAF9AE0D7E85DF491ULL, 0xB54F2D52C8CFA2B3ULL, 
            0x8EEE5EBF628B1596ULL, 0x2BE4F81491096196ULL, 0x2488EA1802A60AFEULL, 0x48DFF61D8F5C9AB8ULL, 
            0x4E7A8C4A88F1DBEBULL, 0x46B30CF518E2C70AULL, 0x74D5D0445D1074E0ULL, 0x5BCFFD4FB96E1272ULL, 
            0xB3040176CD08705CULL, 0xA8358DC46CA03FD4ULL, 0x4C6E1EC1898E7894ULL, 0x20C20326252C255FULL
        },
        {
            0xA594CADC401A36B4ULL, 0x06783A459F0CAFF8ULL, 0x43CBBEB476D5FFC4ULL, 0xEFB3A45C17CDF673ULL, 
            0xA6F3E549F99F0094ULL, 0x570EA4CDB452D2A6ULL, 0x9AB73FA19EFFE4FEULL, 0x62356B68A796C90BULL, 
            0x9FE279EDE9D1059FULL, 0xB8DA58F814764A34ULL, 0x6A7C94CC30BF5397ULL, 0xD8F1FB4AE0B97C42ULL, 
            0xDDEA059C9DEC61C3ULL, 0x8D6D0F4E72834BFCULL, 0x368F751E4543E8E3ULL, 0x2BDC1BD2312E124EULL, 
            0xCD680F37CD6AAC5CULL, 0xA96D47CC83FA4F77ULL, 0xFC0898FA05F97E2CULL, 0x417F683A975445F8ULL, 
            0xE65939D13913B396ULL, 0x92765E5E1DFCFD71ULL, 0xF858435079EDEBF7ULL, 0x7C0876D01158317BULL, 
            0xA83647187A17729EULL, 0x98A61CEEA08DBEA9ULL, 0x6DED40774B320670ULL, 0x5638A0B8AF2A3C54ULL, 
            0xD06E65D76C55F74CULL, 0xDF63F047688DBEE7ULL, 0x4C62B1F0B2079757ULL, 0x58085613D65E99D5ULL
        },
        {
            0xF9D5F6C186C4BB1CULL, 0xE6BED003F785E865ULL, 0x81744C415EF5C0AAULL, 0xBD2851949EB824C9ULL, 
            0x2224CB023EF7177DULL, 0x6AD596200D09873AULL, 0x06B27816EC96E7A2ULL, 0xEF8DF5B071EB9F04ULL, 
            0x28FF74B4E4DEB695ULL, 0x10588679F6843563ULL, 0x70015AFB8A600037ULL, 0x72D7CC64900EEAF4ULL, 
            0x84506D736E0D73EAULL, 0x8E3D04FD23FBE906ULL, 0xC649524D24CF78BAULL, 0xF3D01274EE250BA5ULL, 
            0xAA6950E2A8C33188ULL, 0xFC79D8125D4CEC10ULL, 0xBAB0CC08DAD361D2ULL, 0x8400AC6E7A496273ULL, 
            0x0D2B82A162BD4E5EULL, 0xB23C8A383D12ED33ULL, 0x588F6352789D24BBULL, 0xF9E5BB54C5BCA641ULL, 
            0xFAAFE46E279132DFULL, 0x209DF90CF247A239ULL, 0x85A7C54597A511A3ULL, 0x6B484F074FB8EF55ULL, 
            0x9B32B88B1D65D4A7ULL, 0x4EEBA315AD37E0F8ULL, 0xF255CA8003CB5074ULL, 0xA6B59B37E7C9CBF1ULL
        },
        {
            0x1E4E78CC53284AE7ULL, 0xEE7F2D6BE1F3483FULL, 0x917BF89FC170C7EFULL, 0xDDD3408DD5116768ULL, 
            0xEA67581D098D85E8ULL, 0x3B269628819B7737ULL, 0x57177FDE347E46A3ULL, 0xA2EE16B1123CF718ULL, 
            0x56BDE7CC95C8BE6AULL, 0x4CD90D23FE07ADB1ULL, 0xDBC249F5B54CBFB6ULL, 0x244A21A877FECFBFULL, 
            0x15090DC3E519F5CDULL, 0x1EB5960C2D203237ULL, 0xC4F036C8D7688A42ULL, 0xEB0109ECFC002F86ULL, 
            0x526329935374DE47ULL, 0x80E1C8850084BA7FULL, 0x5A6345ECBE9AA24CULL, 0x9A5A50FBFDDCCB13ULL, 
            0xC655574454CDA0AAULL, 0x6D7B28A050E83BE5ULL, 0x108A7229C03AF146ULL, 0xB130A79A3FDD3E32ULL, 
            0x0C60B6A93BE3695FULL, 0xB1A9A1F769EAD33FULL, 0x6B8FD13A892D53BBULL, 0x8D89224924AE4D19ULL, 
            0x2CFF3AA78BA3EDB3ULL, 0x78C5A6E24213D853ULL, 0x2ED3EE4739146760ULL, 0xF1BD2A36D729C556ULL
        },
        {
            0x76C801A3314A32FFULL, 0xDC2516F56CCFD937ULL, 0x65869F31D1246640ULL, 0x29CA10D4663E983BULL, 
            0x1F490C6B76676731ULL, 0xE3E5A84FD157544AULL, 0x616AE32074FA4740ULL, 0x8A9A9673D1624824ULL, 
            0x0F9A3D9A655018ADULL, 0x7EBC1A64619F65EEULL, 0x72BF0D19278C3EA6ULL, 0xCB504429917265AAULL, 
            0xAA9386FDD57B390CULL, 0x98EB0FC32E730FF2ULL, 0x3892501F7F787E97ULL, 0xAFBA0B2D750C91C5ULL, 
            0xD058D923092682F9ULL, 0x588227D3948ED963ULL, 0xBE5DF8B221F8BA24ULL, 0x73D8FA28EED9F8E7ULL, 
            0x7564D3B6A72230D7ULL, 0x6786BF5135222724ULL, 0xFBAF3C7F5DCF9075ULL, 0xE82F61D4CC2C8682ULL, 
            0x696F2053E5AA9DAFULL, 0x8FFAD2F13E9A1FCBULL, 0xFE642679DEDDB45DULL, 0x1CDA57E175EBB84FULL, 
            0x48201423A33D1A58ULL, 0xFC23153591A82605ULL, 0xECDD7F9FBC0473EBULL, 0x883F85F0230A95A0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseEConstants = {
    0x54032F3ECDD2C3BFULL,
    0x99CBDF62CF2C7914ULL,
    0xCF061BDC444EFA50ULL,
    0x54032F3ECDD2C3BFULL,
    0x99CBDF62CF2C7914ULL,
    0xCF061BDC444EFA50ULL,
    0x5BA81CBB4081249CULL,
    0xB50526EC216FDCEAULL,
    0x94,
    0xF0,
    0xFF,
    0xDE,
    0x07,
    0x48,
    0x62,
    0x57
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseFSalts = {
    {
        {
            0x7594F5D52560BE14ULL, 0x37A27E38869CAA93ULL, 0xBB9ECD71B1583365ULL, 0x759288D9AF05C692ULL, 
            0x3AC520626A461E20ULL, 0x57C11BE2A8A6DE3BULL, 0x12CE0508FCC173C3ULL, 0xBB747439B6BD5930ULL, 
            0xAE9AED2A5D812384ULL, 0x4C0C764E074757E2ULL, 0x1F97D4B65E499DFEULL, 0x42DD4F64C028537EULL, 
            0x9D3F2F7781D9C2D2ULL, 0x0F62AD299667164EULL, 0x8989909B916EF03FULL, 0xD15776DA4B801127ULL, 
            0xDACE9EAD5E528693ULL, 0x862EFB2B925C3A5CULL, 0x360E0CBE8901FCA1ULL, 0x6B55886448C712D0ULL, 
            0xDC1A74EE28363894ULL, 0x090191D966AB0DAAULL, 0x54951CB99B4EACA7ULL, 0x20F00BA8B952F2CFULL, 
            0xB89E3B9E9199EEFDULL, 0x5DB1A2B748EBDB2DULL, 0xA0BCB22A6B20031DULL, 0x7FE4B018965A47D5ULL, 
            0x08743CB21EFC87CBULL, 0xD4BBFF217FC1752FULL, 0xCCA237BED3C66D79ULL, 0x436F9C4476FEFF4BULL
        },
        {
            0x8A9EE44FD1C6DF2AULL, 0x2C9ACB9678C905BDULL, 0xDC0297FD67939F10ULL, 0x201C1C44A8678339ULL, 
            0x74B72B889C6FB924ULL, 0x5E06FA54C68537B3ULL, 0xCA43411C758266ACULL, 0x072D46FFB2CFA4FEULL, 
            0xA456FFAD49DFA19EULL, 0xF53DEB6296ED4980ULL, 0x175AE55F6DF6D644ULL, 0x249C345B575A1D87ULL, 
            0x8208997288518E90ULL, 0xDED56E3C75E333E4ULL, 0xE8FC25B356CD30F1ULL, 0xE0AF6CD2A0DD1713ULL, 
            0x4B12686C26A449E1ULL, 0x9FD79B905DD1F130ULL, 0x624A61A24988836FULL, 0x6265BC1D2FCFCFD0ULL, 
            0xDAB23F61AA43B876ULL, 0xE3CB259379CBFBB8ULL, 0x4DDA9CD24E180EF2ULL, 0x6B0CF4DED388438AULL, 
            0x708C60E1812FFFB5ULL, 0x1D4DACCEB5DF67D9ULL, 0xA933B9A483C0B532ULL, 0xE94FD1E5748A6565ULL, 
            0x6FCE2C8FD856E958ULL, 0xB176A80935E08187ULL, 0x39197D54051E035FULL, 0xE61803D05C4F53F9ULL
        },
        {
            0xFE6ECDC3E73B5F70ULL, 0x2026172540E6C8B7ULL, 0xCBA3A9E8DA20BA1CULL, 0x914FB1F8BBBEADDFULL, 
            0x61CF4A5759BEE3F6ULL, 0x050D7C6C9194C515ULL, 0x470EB9ED798C3CF3ULL, 0xDE41321DDA580A17ULL, 
            0x9BCC0D07F300DC17ULL, 0x196618D10F247132ULL, 0x23A8908C3BEECC07ULL, 0x01EAB69C0D91C01FULL, 
            0xF4B0068C4482CFCDULL, 0x66124AD5F815F796ULL, 0xF02C60B224A07530ULL, 0xBED014FD8844E92FULL, 
            0xFF068CE065F14509ULL, 0xDF964998164817F8ULL, 0x30C3D87472EEAFEBULL, 0xFCE554842BC88125ULL, 
            0x431A0186FEAA2A3DULL, 0xC2229E0E6F844F71ULL, 0xE8D899AEA6C0A761ULL, 0x20042FA79EDC2204ULL, 
            0x8AF15FCA334D4D85ULL, 0xA6F786CDE8134B99ULL, 0x6E8D002360D668C6ULL, 0x9D5BB2A13AD1ACCDULL, 
            0x5813038AA6D0A80BULL, 0x0E1CA4D341990932ULL, 0x3215FB22F13DB65DULL, 0xEAB51E7D7DC02E80ULL
        },
        {
            0x845D25D4EAE0D245ULL, 0x5B04AF4C1151B966ULL, 0x5BAC0BE33CFAFD53ULL, 0x994BEA1DBB21F38BULL, 
            0x4EC2C393A50A9987ULL, 0x25A998FDACF9EFBFULL, 0xA49EEAEACA612D72ULL, 0xBD9CD1176030C2BCULL, 
            0xD4319C048CCEF0E5ULL, 0x787D596C18593F37ULL, 0x1FAEADA9AA553DDAULL, 0xB5EF58E4E1ECA424ULL, 
            0x8D3687CCC13CF39CULL, 0xD17EF42EE3193D6FULL, 0x1511309685542C9FULL, 0xB2E7F47267549482ULL, 
            0x609D943E1D84C13CULL, 0x791F8B0086438C47ULL, 0x986423D30F70CBCAULL, 0xFA7E47AAF84FB5C4ULL, 
            0xC8F9B4132FBF5DD0ULL, 0x3093DFC588A84EC6ULL, 0x6D843C3BA448554BULL, 0x06AC64BFF8F000E6ULL, 
            0x6CD81E32A75EA2F3ULL, 0x8EDE9AC7EDEF78E9ULL, 0xC179EAB06F3A5C61ULL, 0x5F75F8E772276D04ULL, 
            0x75608F7C4C1FFD49ULL, 0xFC60E2A7AD4E8B35ULL, 0x07074B42C9244AA3ULL, 0xE7813F93DFBA2367ULL
        },
        {
            0x91782909DCA9293BULL, 0x975A93067A7D4F52ULL, 0x5ADD711D530534E4ULL, 0xAFAFEF881B6F4CFDULL, 
            0x45460A23E51D1659ULL, 0x812383B7E38C5027ULL, 0xD64A533B7320B314ULL, 0x4E06BD282D2B7338ULL, 
            0xDDC5357730E5CD11ULL, 0x3C2236129BF059ADULL, 0xB1ED8B156FA98766ULL, 0x7F41A3154DE3487FULL, 
            0x162776D3F8E067A9ULL, 0xA119979D5121B2EFULL, 0xDB7628953536EF4AULL, 0x0E8203EF8EC96FF9ULL, 
            0xE890C104901EFA1DULL, 0x1077A974541F694BULL, 0x395C15ACFC9555B9ULL, 0x3C23BD41FC623214ULL, 
            0xA25451BD1B01A57EULL, 0x78DB320B3040E112ULL, 0x96719BA15BCC3993ULL, 0x0542C5E8A69B8C93ULL, 
            0xE9E173DA1C78D040ULL, 0xB5B2D76156521D84ULL, 0x0715E1D67B390E85ULL, 0x8446AACE42B5D938ULL, 
            0x5D8EB8C6C9FE5A5FULL, 0x9BE2F5CAA6485DA9ULL, 0xC1A0C46C7809975CULL, 0xF374AE53447D9FB0ULL
        },
        {
            0x57CF25F777747809ULL, 0xC10F36B4CC6FD3A0ULL, 0xAC60D1B329259C91ULL, 0x89ABD393DE0E1094ULL, 
            0xA78FA568CC54507DULL, 0xCD3351E3374B9985ULL, 0xE60E4C9199A5B340ULL, 0x19777C5BB23877FBULL, 
            0x0E5BEAA5147C5F79ULL, 0x93636FB54999D4A6ULL, 0x70613E2DA47DF609ULL, 0xE3E4682FA0B43169ULL, 
            0xB9448AA09009FB63ULL, 0xC38A90ED0FB7C05BULL, 0xE8F2C3CC90F9E543ULL, 0x43BABDB6C41CB324ULL, 
            0x8CAD4FEEC16759E3ULL, 0x347F57BFAA0AC8F0ULL, 0x34E4E30B44251611ULL, 0x5544E8414E5B8A03ULL, 
            0x4E00FF0ABEA30333ULL, 0xE1D9B9B46BB07586ULL, 0x527D3F564C4880C1ULL, 0x68B57DCF2A3928EDULL, 
            0x47F4E2AF99915FD7ULL, 0x5683F3A1EBDB0ADAULL, 0xE948FC8FE5989A1DULL, 0xEA1EC654E8E459D8ULL, 
            0x08FCDA855EE0BFFDULL, 0xB73D18850A57C030ULL, 0xC4264FF3F4D4C24BULL, 0x8732AF91DBFB0404ULL
        }
    },
    {
        {
            0xB6A066ED31E1AE93ULL, 0xF9EA2A5AFC398F8CULL, 0x07ED9C155A36A4F9ULL, 0x82EFC41B0B374026ULL, 
            0xCB28F2BAAD482FADULL, 0x1C9A74597EF9BF8DULL, 0x9860C1A1776E9DA6ULL, 0x7F55357DC9777CC0ULL, 
            0xD0245BEB1404D85BULL, 0xBCD744B27AF359EDULL, 0x01DE22BF29E7BAFAULL, 0x20E092A8BA18B78AULL, 
            0xB6F2A39B70598310ULL, 0x1568806060C2AA9CULL, 0xB4A5B9A1C11BB824ULL, 0xFB835290AA2D1267ULL, 
            0x1C26793267CC6D8CULL, 0xA045547ADF7F2AF8ULL, 0xC4C3238E79F1B40AULL, 0x0C0043F096D186A3ULL, 
            0x263897EFCA3BD842ULL, 0x3A2ABB4DDACE510BULL, 0xEBE12C0DDF6DB603ULL, 0x475E2E2E01EECACDULL, 
            0xAAC0A4DD956018EDULL, 0xF4F1AC8490ED985BULL, 0xE6760C2B6CDD7883ULL, 0x9F99DE53B51124C0ULL, 
            0x968356CBB0BA9C3DULL, 0x3002C5A91C24FD7EULL, 0x37863BAB8ABF8C11ULL, 0xB26DD3A2F0BEAA95ULL
        },
        {
            0x58432A46911C00CFULL, 0x0F592F1091BCDF0DULL, 0xD10DF0E3024ADB64ULL, 0x6AD8F418109B00F8ULL, 
            0x9A8F7EEB43621ED1ULL, 0xA2D5D7BAA5092D70ULL, 0x906CCE714ACC1906ULL, 0xD1B126933D3A8DAFULL, 
            0x849FA8FF4B100F4FULL, 0xA56FBA5EB2DA6E27ULL, 0xBD7CAA3D294A2804ULL, 0xE574B5C9F7287E93ULL, 
            0x25E851D567E0C38DULL, 0x1B5AE9D29718BFA4ULL, 0x40663E13797BA97FULL, 0x60DDB6A741C336DBULL, 
            0xE40B5A0F086828D5ULL, 0xE9984B7C1F0480FEULL, 0x4253A0CBFA29159BULL, 0x317451E12EC5E532ULL, 
            0x87BD50FECDB203B5ULL, 0x75CCB1F6B4A3CF3EULL, 0xB2D4623487A1B3A6ULL, 0x502979248BC69F9DULL, 
            0x5D7EFD9AB631DEA4ULL, 0x0FDC56FF3A7A5F5EULL, 0x6E7E21443570A970ULL, 0x9D3333B2061340F8ULL, 
            0xBE3D92BA226D19C0ULL, 0x054B0C323F052BE4ULL, 0x93D265E2E5102329ULL, 0xD2A98AC56A6B4181ULL
        },
        {
            0x0839D6D57396F4C8ULL, 0x8C742E582969540AULL, 0x4CEE4959B8FBE06CULL, 0x706397FD488C524FULL, 
            0xB35977CA514FE8E3ULL, 0x2F2D507F582E125FULL, 0xF6C3F99512D6196EULL, 0xD07466546FCA551FULL, 
            0x8A93DDEBDFD7BC6AULL, 0xFA8955D33389601DULL, 0xEDE253196860B017ULL, 0x66DEE8272F3CB21AULL, 
            0xC8EE304F4ADBACC9ULL, 0x651847384504C759ULL, 0x37EC0FF3FB271077ULL, 0x311669BA15ECF331ULL, 
            0x84E05B439E6B0EACULL, 0x5C28D383CB04799EULL, 0xC22A43B2818E81CCULL, 0xFFDE8BF1A0311E44ULL, 
            0x870F2A28B93700BFULL, 0x0CA7CD4B21096D6AULL, 0xE0CC6DDDE74831FDULL, 0x5585F8673522A237ULL, 
            0x48E0DEACD02CE319ULL, 0xC6B642609C898100ULL, 0x7F6B6A6AF67E6C4AULL, 0x7FB7542CE5FC93A7ULL, 
            0x0391B49FA545AA17ULL, 0x789ED02558757F84ULL, 0x74A19D55D349B938ULL, 0xBD4774166F9E3352ULL
        },
        {
            0x33C1A71D28D792BDULL, 0xF75D27A5C1F7B9EDULL, 0xD7B54E9414B5F5F6ULL, 0xE3FCC64936A12BBCULL, 
            0x316B941B8C827687ULL, 0x88FF52CD530C02FCULL, 0x2FF85A2E1190CF20ULL, 0xBBBBBBCD4C16B179ULL, 
            0xBDC1F92035F18158ULL, 0x87FE1A489F2EDD1AULL, 0xD9C74158976DFA79ULL, 0xF79F5981D6E0BE07ULL, 
            0x4C9285283A45502AULL, 0x6D722CE69FFE1C2FULL, 0xC28426C035CFDFC2ULL, 0xAC8D91B6978DE579ULL, 
            0x2C454D3F05F30E68ULL, 0xA625ED17C2BC093AULL, 0x160A6832A207AA0BULL, 0xAF490070DCD4FA4AULL, 
            0x0A155BEE3E29928FULL, 0xA1811166ECCA59C5ULL, 0x1AB6DD2C39AEB82EULL, 0xED0DFFBF8BCDC5CBULL, 
            0xD74B902E2C9FBC2AULL, 0x76A4D0955D942D8FULL, 0x7DF3BBC4E9188A08ULL, 0x94EFD6E76666EB60ULL, 
            0xF7F9559E81C11E18ULL, 0x743743B07BB2A4D3ULL, 0x82F1E14530BDDB72ULL, 0xCF74B904F668816EULL
        },
        {
            0x6F0042ABFE016936ULL, 0x7694996FB762B316ULL, 0x42171BD6E8A989F3ULL, 0x98D5FD873616478BULL, 
            0x5D567EA092CDAA46ULL, 0xE831355CB493F5B9ULL, 0x6E147C5854C9C6E5ULL, 0x369E879F66B68F85ULL, 
            0x14FEC056E949B024ULL, 0x2517D490BF30705BULL, 0x9BB8DBB74F2BB0A3ULL, 0xF4CFED510F29A82BULL, 
            0xA454DFABE2B9DDE7ULL, 0xD99391355589262AULL, 0x3AC1790E6E91C560ULL, 0xE16DD2AD3A5C1148ULL, 
            0x2E8730FAAACBE87CULL, 0x3E4B8B97B632FEF8ULL, 0xFE5E7ABCB0EC644BULL, 0xC02D1461C76124FBULL, 
            0x8F3010B53D0F74DCULL, 0xCCC3A85D6BBD1269ULL, 0x7564FED16D3679D2ULL, 0xB01E4FA1114E1CCBULL, 
            0xA329055828F91A55ULL, 0xB25BFF69BB0F8460ULL, 0xAAC3A8661D7DECF6ULL, 0x47BBCE74CA673735ULL, 
            0x2627A7D5EE070F6BULL, 0xE30ACBDF4254A59BULL, 0x9FB408D78E479160ULL, 0x413EB81E5922DB25ULL
        },
        {
            0x09F0D9DB91BC72A0ULL, 0x42207D4DC52A55F5ULL, 0xC54A8A60CF57DB07ULL, 0x081C92985DE11F1DULL, 
            0xB817E208CA381F88ULL, 0x1AFE8C6371A4C990ULL, 0x569BF7199F4E82AAULL, 0xBC9CF229AB7A97A8ULL, 
            0xE5645F1270F76AD0ULL, 0xF3345B3E7B93FB5DULL, 0xB2FAAA92C0E55DA6ULL, 0x0F5E8CBD24692222ULL, 
            0x44939D4D600D46BFULL, 0xA026D04994721F89ULL, 0x371EA6FCF85C780FULL, 0x9CED97C7323D9024ULL, 
            0x1BCB20C2DF5262B3ULL, 0x56B90B7D3A7591D4ULL, 0xCA6DB8C29F3AB07FULL, 0xC3BDD4993BCE3A77ULL, 
            0x1247032A191C1398ULL, 0x970F19D7CB085E49ULL, 0x4CB9437B7F03B82AULL, 0x17BCD62BF481065FULL, 
            0x3A663A2D1EF0EEE6ULL, 0xEF72C07967491FC9ULL, 0xF0FACC9DB043360AULL, 0x3D914E964CB2EC21ULL, 
            0xCCE3A2617818F3D8ULL, 0xC3655C7AA530F00DULL, 0xD0B2C6B65EC37C0DULL, 0x78396E9A0EEE6A64ULL
        }
    },
    {
        {
            0x9B4C36546A0BD3A0ULL, 0x44EBE51CE2644515ULL, 0xAF27E976B7F96AACULL, 0x9C569A31FD845EEEULL, 
            0xC1CDB39298A9C8C0ULL, 0xCD0D3A9F12747F35ULL, 0xCCB8C56BF62F4750ULL, 0x946966F07E6802B0ULL, 
            0x344C1F8D0A23054CULL, 0x53DA7009B5F38B53ULL, 0x55150DCB3A288763ULL, 0x0876648F709ED4B2ULL, 
            0x7C77B96DB0EAC6F8ULL, 0x3B6E8C4FA90281B6ULL, 0xBC99CF091A36C2CBULL, 0x6A880994CD421791ULL, 
            0x3EBEDC38614E2B8AULL, 0xEEA04D8793D24274ULL, 0x4ECBFA9687C8A1D5ULL, 0x50EE230F5AE979EDULL, 
            0x6BD32C81A722D936ULL, 0x46E7624B5641B5AEULL, 0xAECCAABCA8D2C070ULL, 0x14BC543E2A075D3EULL, 
            0x288D55290898A73DULL, 0xE4476DEBDA776156ULL, 0xC1B15945C9DB01C6ULL, 0xEA2D940840882968ULL, 
            0xCD354928601C49BBULL, 0x40ABD6B1B506F09DULL, 0x829E4256C8BF0A55ULL, 0x1BF26B76054E980CULL
        },
        {
            0x396161151DB0C453ULL, 0xD94680319FD8E1DDULL, 0xCFB7959191EDEA2DULL, 0xEC6E2FF131AAB770ULL, 
            0x1D4E9B6C1C8054DFULL, 0x65E541E3965A8D85ULL, 0x358C322671EFA935ULL, 0x7A8E7C1E7E21F245ULL, 
            0xA28BA3245C82F7DBULL, 0x852CD2C1C8DB01B7ULL, 0x680F4D8B1B89250EULL, 0xEFAE1071E48FD073ULL, 
            0x3CAE66BC7A5C4D91ULL, 0x8158819EC49EF688ULL, 0xA1AC95586FE5BDD7ULL, 0xE76CCAC47669A809ULL, 
            0x7A292BB7EF6BAEECULL, 0xA0A10A9B91836A35ULL, 0x5828FDF7F1216CE9ULL, 0x97C616475FC28A43ULL, 
            0xE1A05EA30B36A686ULL, 0xDFD7CAA4BD0AB18AULL, 0xAF2766A7695EC29BULL, 0xBF1AD41635D54943ULL, 
            0xFDACA15DAD42B557ULL, 0x760E8F687BE3D917ULL, 0x762FED7D4BEF348EULL, 0x1438748FA1C048F9ULL, 
            0x80C20F838C8109AFULL, 0x33993AF157DC3BD0ULL, 0xADCD2570F30B1A8DULL, 0x01B6601F796800B7ULL
        },
        {
            0x0DD5CBBAC6D607C2ULL, 0xAA0D7EB46A65A2EEULL, 0x99DFECA90FA75916ULL, 0x4D0DF75A3AA0115EULL, 
            0x756B30A4711BFA6FULL, 0x4828298375030935ULL, 0xFE29DB82AE8F8BA0ULL, 0x3242FD22333A785DULL, 
            0x0702C2023010AEC1ULL, 0x433686E5E4F28B51ULL, 0x91E7CCDC31FC3DB9ULL, 0x8456C0FDB2BDD843ULL, 
            0xF75B3EF4F2AA92CDULL, 0x6DF0748AE38FD688ULL, 0x9A73A6167971A3FFULL, 0x38C24F3F8A976DC5ULL, 
            0x347A7369D9469D46ULL, 0x626D96CB37DC338CULL, 0x60788C2F0E4DAD07ULL, 0x8DC5F5B4BF527869ULL, 
            0x9871F652B360EF36ULL, 0xD6171ABACCF11799ULL, 0x45CD7E8992ED4823ULL, 0xDD43F3B01862D191ULL, 
            0xB048A00E7129A5CEULL, 0x740415163090186CULL, 0xC79BB2C17C6D24EEULL, 0xBFD3FBED4680E8DEULL, 
            0x734F14CF9C04E481ULL, 0x14C62A7FD4847DD0ULL, 0x3AAE79B70420ABD8ULL, 0x4DE79C3A7B0C153CULL
        },
        {
            0xA4A361BF90A94D9FULL, 0x2C04CF2352FA3172ULL, 0x84894E2C0FB01B24ULL, 0xDADFFCE121FCFD63ULL, 
            0xE5C0BDBF69420692ULL, 0x368CE9AF3D8875FBULL, 0x12C8D482968DD8B3ULL, 0x0F386F19251EDB49ULL, 
            0xC2F48E157903F93DULL, 0x7CA5A24D29358EF2ULL, 0xD8796D097EB80644ULL, 0x34A08C89FA2F076BULL, 
            0xCADCE15C92BF0979ULL, 0x9D5C5B6D70263844ULL, 0x1F1C2B88396AED03ULL, 0x8DA82ED17E77E863ULL, 
            0x09681017BDB4F990ULL, 0x01B71D6186A16D1FULL, 0x13B5A258BB6F7462ULL, 0xC3FF9FDB26CD3138ULL, 
            0x537B6A612196A53BULL, 0x689F43AD01BD3253ULL, 0x9C6EF74BD9E2DF87ULL, 0x6834B54EA2C5F0DEULL, 
            0xDB43006A47FAEC27ULL, 0xDAF592AB0337EA82ULL, 0xCE0E7432A0AF2063ULL, 0xBA134ADD140C73A3ULL, 
            0x60B615F3E1C80638ULL, 0x3248877213032037ULL, 0xC22A659523BD9C59ULL, 0xF199275521338003ULL
        },
        {
            0x02BD2F28D9515B32ULL, 0x71A4F5DDE8D0FE53ULL, 0x6D953B6B109CD92EULL, 0xFF33726C64075ADFULL, 
            0x36C99D8186FA78DCULL, 0xA847A3E723F14CBFULL, 0xA0A6D76C6101C8FAULL, 0x9AC58069B1734023ULL, 
            0x94BB6D56731C94E3ULL, 0x6D390D6AC90D866FULL, 0x948DF9D061D8D5AFULL, 0x61F2367424A5A894ULL, 
            0x8D1EAE3CA14C5662ULL, 0x3B63620FD0F95CA9ULL, 0x8947FB80017681F1ULL, 0x06F601670FD30437ULL, 
            0x5B475513AAB09F27ULL, 0x737C95F5922F7316ULL, 0x8B7CECB8234B6634ULL, 0xEF32E276C19E770DULL, 
            0xFA4BD43181889992ULL, 0x0AD9DC285B6C22D2ULL, 0xE1C7C1647DC85AAEULL, 0x488F153D14F6F7A4ULL, 
            0xF5CA1399F2985C01ULL, 0x05622219F8F7C1A3ULL, 0x7FA25582432B22BDULL, 0xE0770D83E7B55062ULL, 
            0x5271FB9E13A074FCULL, 0x600C09717A89739DULL, 0x53A7C4B4E4EF48F3ULL, 0x48AC6869891DF388ULL
        },
        {
            0x210157DAC5B000E5ULL, 0x62C6307F3DB340E5ULL, 0x024EA8A1E566DBF7ULL, 0xC0334F9179D80DE9ULL, 
            0xB3D164D6B10A1EC2ULL, 0x98B6561426AAFFDCULL, 0x2CBA4B5E6B8883F5ULL, 0x815EA1DD041055A8ULL, 
            0x0427B4DA750F2C1BULL, 0xBDF0D784B85BD0BDULL, 0x9B3B9E4A52B7DAEBULL, 0xDFA55C3AB29F4AF7ULL, 
            0x6125E515E69FD07BULL, 0x2293D6D281CBAB82ULL, 0x33D6277B6534CCFBULL, 0xE275F9B588F87E0FULL, 
            0x33B4762162F2F3CEULL, 0x7C5130932F0D5A34ULL, 0xD5B621EEF13D620DULL, 0x8469DC9D934DAF10ULL, 
            0xD48D27481B3643D2ULL, 0x3FCDFA8EE3437686ULL, 0x30F571F97455635DULL, 0xFCEE9E8B30F81954ULL, 
            0x1B7387E6E2449855ULL, 0xEC071296C9DF6082ULL, 0x1B9A8C5706B7610FULL, 0x06E0EBC304EBBF78ULL, 
            0x70AD78BF2C15BA7AULL, 0xF3AD64B210ADA032ULL, 0xDECA91736712F9EFULL, 0x6AD8936E7C04FC39ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseFConstants = {
    0xBB8BB78EFCC1ED00ULL,
    0x017EA387BE6864B9ULL,
    0xDC7A70C9D905BF38ULL,
    0xBB8BB78EFCC1ED00ULL,
    0x017EA387BE6864B9ULL,
    0xDC7A70C9D905BF38ULL,
    0x01AE46A9B5288335ULL,
    0xA53A0C4DF53664E5ULL,
    0x68,
    0x6F,
    0x6E,
    0x7C,
    0xA2,
    0x14,
    0x6E,
    0x09
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseGSalts = {
    {
        {
            0x0ABEF22A883A3C49ULL, 0x054901B61A85A12DULL, 0xDFEF98DC8AC78F8BULL, 0xB69E3253545C89A7ULL, 
            0xA5BC9B36BD473359ULL, 0x7484F05CF79AD97BULL, 0xB04311D72F7A0187ULL, 0x8F22A9D14524994EULL, 
            0x2AC502F86F991865ULL, 0xD8101AED2EF87A39ULL, 0x63B6F65F3B68C860ULL, 0x9944C73E6D19981FULL, 
            0x363E75DCD369F00FULL, 0x57B9F3C54CF0E42AULL, 0xEA00030C3B325C1EULL, 0xD48A8D80BA058144ULL, 
            0xBD2333E0311919E2ULL, 0x01D15FE9B553EBABULL, 0xD18D00A32E852DB0ULL, 0x2B015B737FBD3DF8ULL, 
            0x9E926E206B7211DFULL, 0xB0291485797A113CULL, 0x5A5F4E2DC34600E6ULL, 0xC238B3F64989F644ULL, 
            0x3E365A2F04B7E96EULL, 0xD9D3A14BB882FC37ULL, 0xE3D5102561E0038AULL, 0x144F906A832A45B8ULL, 
            0x779AA36E4CD2C65DULL, 0x24556785184BAD9FULL, 0x5650E787D2A5EC58ULL, 0x15DFF48E7D73DAB1ULL
        },
        {
            0xAE55B23E6514CC00ULL, 0x7EA382A1A6034179ULL, 0xA828F70B23BA76A8ULL, 0xB441F83530131546ULL, 
            0x845FCC41570C80A0ULL, 0xB8E137DB1CD951FAULL, 0xBCCCB6FC279389DAULL, 0xE1B15316B0E313AAULL, 
            0xB0E31588FEDC5710ULL, 0x1524C70C439A92CDULL, 0x283C779E1066802DULL, 0x9FD193E7C2005748ULL, 
            0xFB7BE44BE4164E32ULL, 0xB96A3F38469D63C5ULL, 0xF201AE29B492CB7FULL, 0x98E8BEB3AAA9113AULL, 
            0x1CD62930A8BF8466ULL, 0xF97BFEB3F4D90F60ULL, 0xD178E2367EFB85E0ULL, 0x85C2CA1F692C99ADULL, 
            0x2E366FC8EF5A995EULL, 0xC21C50BC152E76DDULL, 0xFAE0900012BD0749ULL, 0x64632F8517D85BE5ULL, 
            0xCCB76B0FF4D10865ULL, 0x619FD389F9076000ULL, 0xF5EC967C785497B4ULL, 0xD211927093015477ULL, 
            0x40A61A02A6784DC3ULL, 0xC3776E16D9B61A64ULL, 0xFCACE9C649C32118ULL, 0xE3466AD1E9FD9414ULL
        },
        {
            0xA3D673991C90025AULL, 0xA54CFBA57DC8EDCFULL, 0x5495ADB82B98199AULL, 0x56B031FFFF92E243ULL, 
            0x08CCE6B73E53545BULL, 0x0B39AC385915836FULL, 0xEB6583CB70DE3003ULL, 0xFD074C0FF9E4A019ULL, 
            0xF26D8551CFC571CCULL, 0x839460552C706D50ULL, 0xA33CAB6154A9F285ULL, 0x395A41B70A4228A5ULL, 
            0x7053AE273458756BULL, 0xA2A05927A986BC64ULL, 0xCFA2FEC79AAB2853ULL, 0xC78A5FDAD672D3B8ULL, 
            0x2B9A2EB874E020EFULL, 0xF332403E7C2AFAF7ULL, 0x18508BF5539DB0FDULL, 0xAE960960216F29E2ULL, 
            0x423D092CF13AAD8AULL, 0x954A14D5F31D5570ULL, 0x06184B771ADF9347ULL, 0x2DF9EA75F855D4B8ULL, 
            0xB598D5CE7EB18E93ULL, 0xFC613CA214A97641ULL, 0x635D8505D1616C74ULL, 0x9A1C9B4499201D7FULL, 
            0x553765FE96DDD774ULL, 0x681AEB4F8935AEA9ULL, 0xCE54E0F777965B8CULL, 0x496FD6FF4898D137ULL
        },
        {
            0xB589ECFFAA06088AULL, 0x70DBA9E62EC1F071ULL, 0x344C0275F157F775ULL, 0xFB2DFDE6E9FE45DDULL, 
            0x25B0C56247608809ULL, 0xB9E92B047013B882ULL, 0x4298BF54C6F0940BULL, 0x4812D5AFFE5C229BULL, 
            0xF9B10B06AE9D25D2ULL, 0xC09F8258DB41C38FULL, 0x8BD9020ABCC85FB2ULL, 0x139E2FDA4E789886ULL, 
            0x6C8721254F1FFA19ULL, 0x7E3A4BB0E6EA1DC5ULL, 0x0DFA5F2DF2C9F61CULL, 0x0018FEFEB611612DULL, 
            0xE102ACA085AC8A36ULL, 0x7647F34CB3E72730ULL, 0x6EDE5E37B12AAFB0ULL, 0x1AF2B3B698A77C3BULL, 
            0x72D530A2BF2E6935ULL, 0x1AFA6AFAC6F713D0ULL, 0xD6B8F0C8B14A30ADULL, 0x7D4FCAFFBF153DD5ULL, 
            0x3867D72754A181E1ULL, 0xCD99D6D83DD19F59ULL, 0x58A0679084F20E1AULL, 0xA8EF55827495BBA0ULL, 
            0x6F0CBCA5C78BBBE7ULL, 0x71E9B4CD24DC6DE3ULL, 0x687988B82B42745AULL, 0x07A3922C296C1088ULL
        },
        {
            0x243F1CDE1D14AAE3ULL, 0x06BEA9920421A872ULL, 0xD1E6A11BC8E0BC39ULL, 0x737DE9FB0222FA59ULL, 
            0xE08F4A7F46B7C4D8ULL, 0x7670A646E50714B4ULL, 0x6E9EEF2F59DE6032ULL, 0x3CFC708181906C11ULL, 
            0xEA1EC917D333040DULL, 0x860186B7E58A594CULL, 0xDC110FC0710D2FB5ULL, 0x42A92195A1ED2C66ULL, 
            0x71CB12D1B225F52DULL, 0xAA5452C728B27B2EULL, 0xD53532A626021D79ULL, 0x34841A26F3CD1E1EULL, 
            0x39D704F22EAEA31DULL, 0x8399EABB3A16299AULL, 0x7A3D7822E7D87773ULL, 0x6C12791698F40E02ULL, 
            0xB37A906DFD8718F9ULL, 0x917965A372A737E0ULL, 0xAAA9BDD58F3E0CA3ULL, 0x6C4A68830F6129F5ULL, 
            0xC9B34EECEE3D7A48ULL, 0x9F211BAAE78023BFULL, 0x53CEEF19433AA875ULL, 0xFAB3F599684E51FAULL, 
            0xEADC4B1DC77E9B44ULL, 0xF9F79DDF16E2F4C5ULL, 0xBD4BB5AE13DB1107ULL, 0x97D1653D6AC078ECULL
        },
        {
            0x3AC3A7C01D6ADFDBULL, 0xDCF1817EBBD75945ULL, 0x39EB2FC1A781630FULL, 0xE4EA606AC4CE70C3ULL, 
            0x2E6F2C7DC993AD2AULL, 0x699D449971C0A1DFULL, 0x667DE5022AFBBBCEULL, 0x2ED7A6D5646F994EULL, 
            0xA10CDF236EC9B1ECULL, 0x582018E3C7CAD42FULL, 0x5F1067D13028BF3CULL, 0x699199FB13EF95D3ULL, 
            0x278B3A77843FE59BULL, 0xABC8EB134746A16AULL, 0x90F59C8EAA0A4A8AULL, 0x9CFCAE2382872433ULL, 
            0x1D1BA0C9B0D85BE2ULL, 0xF4338A2E155B8A00ULL, 0xCAEA818C2DF106CBULL, 0x7C9BCF8AFDBCDBC9ULL, 
            0xDFF4858C0F73B8DDULL, 0x9960B2783BAE95FEULL, 0x644AEC317C645832ULL, 0x6797B33B9E9E6C00ULL, 
            0x193FC482EDF85FF1ULL, 0xA79534C80E788901ULL, 0xB2906012A43198CBULL, 0x806826A5897C74BCULL, 
            0xFFDDDEE4982D3872ULL, 0x4FA50F454A0044E6ULL, 0xA00AD7EEDD7E3E6DULL, 0xDAC380930327CC47ULL
        }
    },
    {
        {
            0xC8C25726D035E2A4ULL, 0x672CE99DE43ECDCBULL, 0x983F04DD13A9AEB2ULL, 0x31089E1A0F97A718ULL, 
            0xF7C8B7E2D97A63F3ULL, 0x4B51F72DFAE0C969ULL, 0x3234D1CA7403B149ULL, 0x2F310B7ED39F9315ULL, 
            0x39B9C9AF9AE46EC6ULL, 0xE94BB9F5E5A6DAF2ULL, 0xA8FAAC79461466DAULL, 0x06F3B336DB2C03DDULL, 
            0xD72FF17C5F5B6F5DULL, 0x827FAB4A3DC30EC0ULL, 0xE41FEDB3736E2C4BULL, 0x001EB20789B2863BULL, 
            0xF710271D1A5509BCULL, 0x3AC069CDA93AC654ULL, 0xCC8707E4E13CDCAAULL, 0x18A6AC35A397A4A5ULL, 
            0x6D4291686C2E14E8ULL, 0x6365071C55191145ULL, 0x5D554BB66A377C91ULL, 0x7A022FD50C19DAD6ULL, 
            0xC4206C3A6570A952ULL, 0x07F0A1C00113C39BULL, 0x1A2290474C2165FFULL, 0xA96AA1B8AB04C8FAULL, 
            0xF6D61A40E0DAD604ULL, 0xEF343E11C145A33BULL, 0xA8810BA58921BAE3ULL, 0xFDF3420FF70293B1ULL
        },
        {
            0xF00B76C3966672EBULL, 0x800FC880F2A93D82ULL, 0x90738AA5AA7D96B5ULL, 0x465E5E71EA1B4F32ULL, 
            0xF57974A9C9446677ULL, 0xA7855E3B0402B14BULL, 0x2B64FDCE3C2FF0F0ULL, 0xBB8F9873E4F8879FULL, 
            0xA5E9427840585C66ULL, 0x727FEE405A30BA88ULL, 0xA004EA42F19C8DFBULL, 0x2EA24CB706FF4440ULL, 
            0x3AEAA575EA57967FULL, 0xE671DA7316EB2D0CULL, 0xFF171E2D09F13B0CULL, 0xA6BC7575818CB42EULL, 
            0xC3B2119A04A34C6DULL, 0x989F2269369D9D0CULL, 0x5F7192C6662BC068ULL, 0xE20FF4362F03542CULL, 
            0x1CD4E06DC4B48E13ULL, 0x7FADF19C0FACE739ULL, 0xF42470F36BAF80C8ULL, 0x085A92DA8612D222ULL, 
            0xE97C68BC9EBBBDCBULL, 0xCBA5113326D7465CULL, 0x8BE6FC13ADD38CFFULL, 0xB2E3EEB5754BE85BULL, 
            0x19126B0C0DEB4854ULL, 0x02C457CB60F9DD02ULL, 0x1A0BFCEF3E9C4267ULL, 0x70200742F5135716ULL
        },
        {
            0x3A67999E0BC11131ULL, 0x5D64FB1EAC2E6C8FULL, 0x788B2E396EEDB4DEULL, 0x262E85E9ACDA0CA3ULL, 
            0xA8CE5F1DDE51B3D3ULL, 0x8760110CB1A5C45FULL, 0xA1CF60F7CD5B4A99ULL, 0x305F87A5D4F92F37ULL, 
            0x22007D2991E950EEULL, 0x53E0CA0BB39EC52AULL, 0x76674B484C03906BULL, 0xA5BF09D8239275A7ULL, 
            0xF1B0B4D76648AE0CULL, 0x6590538FBE274392ULL, 0x47A6909817213CF2ULL, 0x4B8B2FE0C14DB358ULL, 
            0x2074B744322742E0ULL, 0xD8E999DA4FA14528ULL, 0x6ED95873D715F2D2ULL, 0xFBE89644670FEC46ULL, 
            0x47464CD48A20107BULL, 0xB9DBEC52B4CCED8AULL, 0x92A12221A5A46516ULL, 0xC0CACA95EC367555ULL, 
            0x08BB5AF496C9036FULL, 0x65DDF669D26ADE62ULL, 0x5AE75FFB4BECBD09ULL, 0x63653272A2B81B57ULL, 
            0x6DB17C3E132AE7B9ULL, 0x75EB72478026D816ULL, 0x7A124D8BC24779BCULL, 0xE52A6CE2B3E4BE2BULL
        },
        {
            0x5638B44003022780ULL, 0x8D8AFC6EFF5290ACULL, 0x59771089470DD638ULL, 0x686A64E655433C8AULL, 
            0xFC37A5D882B558BCULL, 0xFFA65BD72F767EECULL, 0x987E992BD56B3F48ULL, 0x31C0F269D29BD630ULL, 
            0xE576F17CA6357985ULL, 0xA4151E904CD9C7DFULL, 0xCFE061EB050321BBULL, 0xADE0B8988563E7ABULL, 
            0x8CA2C65C9DB5A7BBULL, 0xA467FD03775EE8CEULL, 0xC6613AFDE1875547ULL, 0x60D30B2258BFDE72ULL, 
            0xB9EA68C762B3498CULL, 0x855357F5FB97DCB2ULL, 0x08D99AA442891BEFULL, 0xC159543A42F33B8DULL, 
            0x7BBBA544E6AE4B46ULL, 0xB06941145876E71AULL, 0x1523F083D388BC2AULL, 0xEA7E4487A10BB2C0ULL, 
            0xAFF635D8DAFF72EEULL, 0x0CCB88CBBF367CC7ULL, 0x1BAAEB59BA0AC297ULL, 0xABB7DD50F433F6BDULL, 
            0xAAA77C4FFF490664ULL, 0x4B0FFB9EFA9D2BD2ULL, 0x9A52F474ED797D26ULL, 0x6FE72BF46F2DE11DULL
        },
        {
            0x7B31AA11F5F75748ULL, 0xA5D47CC5782012ABULL, 0xA9B10BEF93611EB1ULL, 0x9BCA9E21C13A2F6EULL, 
            0x5A8D4105C7861C37ULL, 0xBD59C4A906C971E9ULL, 0x58B1477313BDD5E4ULL, 0xD7CBB43593AC40A3ULL, 
            0x799489F8034D98A3ULL, 0x83FDC2ABCDC20D56ULL, 0x6A199AD40E94A947ULL, 0xF5B246F44BBADC0FULL, 
            0xFA11DD67E0F637FCULL, 0x24AE3BC6BDFE9C13ULL, 0x7CB21392A887E7D3ULL, 0xDFBDE036AE4481AEULL, 
            0x5C97F876118E3F03ULL, 0x9DC9E7F38AF87059ULL, 0xDC89C21C8092119DULL, 0x53A954FBF8EAA866ULL, 
            0x8E84B0C5D55CFFF6ULL, 0xA645CB2B50A00AEAULL, 0x1B9DC21E2467D1E8ULL, 0xDC7E461BADFB65D4ULL, 
            0x12250A2B7E9812A5ULL, 0xA44F7D89A28A0D57ULL, 0x138B0F8F27F2FC37ULL, 0x03836B45B9185EA7ULL, 
            0x6F86B1E48AB2608CULL, 0x4EDDD5519760DCF7ULL, 0xCCB009F9FF7B3A04ULL, 0x658886C296C565FCULL
        },
        {
            0x44B113A8BFD133EDULL, 0x06B2CD0062AFE040ULL, 0x0FB240691F43024BULL, 0x0AC34594BC7AE552ULL, 
            0x23564028CFAD3FCCULL, 0x7F4E99E9D48313FCULL, 0x14DE65065369199EULL, 0xF65714E029FD0562ULL, 
            0x940709859BEEEA4EULL, 0x9877E7764DD10AC6ULL, 0xF348A0ABBB5EE445ULL, 0xEAEE18D6EE2DE997ULL, 
            0xEDB96595F3E8FD98ULL, 0x86C8C9E2E3CEC270ULL, 0x8B7CF5C48A471EC7ULL, 0x2912C81A8308C417ULL, 
            0x60DB5D217D792013ULL, 0xB4DC24380B9703D7ULL, 0x96CFD5661B8528B8ULL, 0x50406B5784CD82D4ULL, 
            0xE0A3CFD05A8121E9ULL, 0x5F336D9787704ED3ULL, 0x2901E6BA61C094BEULL, 0x35F3C137A8CD5A60ULL, 
            0xCC6497D144335D72ULL, 0x1E7FFDC14EA01B4EULL, 0x35F8297A71E04A2BULL, 0x27688ED69A598324ULL, 
            0x929F568EE51DF170ULL, 0x1474E710BD090565ULL, 0x00ABECFC4A66BD20ULL, 0xFBA2574A69E464D6ULL
        }
    },
    {
        {
            0x19CADDB0CAC35866ULL, 0x44F14B8D7469C792ULL, 0xFAF15C1CB9E35DE7ULL, 0x67041164113A1623ULL, 
            0xD9F166B26E0C40D4ULL, 0xE8A42324FEA66B14ULL, 0x79B0A61BBAA0B630ULL, 0x36EF0CA992D1AF5DULL, 
            0xF61166B1A8112B60ULL, 0x9C45B0EB16D4E337ULL, 0x4A5BD269D889FEF9ULL, 0xE41E35B9EB7BE0F6ULL, 
            0xC5115B1B220E6094ULL, 0x5515BC02CFCF113BULL, 0x841BC38B9EE8590BULL, 0xA2681462568D0D3DULL, 
            0xAE4AE5FE7C83A189ULL, 0x74E4F5099FAC5884ULL, 0x7532AA52781F6B39ULL, 0x38FD215FB0E62787ULL, 
            0xBFEACCA7437A3A25ULL, 0x191B3E9CE0D58415ULL, 0x62063001BD8B8041ULL, 0x43A7DC3E228E1126ULL, 
            0xBD7486398EED7BE3ULL, 0x9D2E3F84D276D773ULL, 0xC1911DC07DC037D6ULL, 0xBD37CE8CEE7577E9ULL, 
            0x213CFA25A465C44CULL, 0x44C2D5138ADDB5F5ULL, 0xE9CE16AEB7A84D38ULL, 0x4F8FA9C585B77737ULL
        },
        {
            0xE69AAD232524E30FULL, 0xE62473F4CC7358FEULL, 0x980F0B200494FF10ULL, 0x606FEC4D361F7CE3ULL, 
            0x4722CEE84ADF5130ULL, 0xB56597ECD8FDE3D7ULL, 0xFB6672488B650665ULL, 0xFDD710063D903063ULL, 
            0x9CE72A7E4987D3B1ULL, 0x9B35DABEDF0AFAF0ULL, 0x774F888B7F89F263ULL, 0xEA3B69B052B7A969ULL, 
            0x78738C6220D69652ULL, 0xE58F764FC210F33BULL, 0x8B943D03570F42A6ULL, 0x2F51EEA83D50BDB8ULL, 
            0x5CAF8CEEF6745087ULL, 0x8DE89B50C75C9145ULL, 0x2E33E40264C66124ULL, 0x44E2EBF3C515C31FULL, 
            0xCFEA94D947D3CADBULL, 0x05EF01BA56DD3181ULL, 0x5FB0A234BC8A63D8ULL, 0xDCAFA82687F6DF4EULL, 
            0xBF5FD2F91084F71BULL, 0x07A2045B2165420BULL, 0xE5D870428B81CAD5ULL, 0xD2F5FCFA96FEAD29ULL, 
            0x47D19ED9DC5A2122ULL, 0xF9D95111E63FD95DULL, 0x5E60D0F5DD94C5D5ULL, 0xD73EC645726A002BULL
        },
        {
            0xCD3BF3582E7DFACFULL, 0xB51E7762CD76A514ULL, 0xD0970437D60BBC13ULL, 0x3DB851D8CA06BBCBULL, 
            0xAE5154CD318749AAULL, 0x9DD30A97300E9C6CULL, 0x339D2D88E2B7FF76ULL, 0xF42D290149B59581ULL, 
            0x6AC0A72660599997ULL, 0x7EA6A1F7A7048FCBULL, 0xDCAC8406DCE44809ULL, 0x7B24037E706826A8ULL, 
            0x866673E0F361C609ULL, 0xF7373C24FFBE5AAFULL, 0x11E73CA3A786BEC9ULL, 0x1303D38995AEF952ULL, 
            0x026B79D881E60091ULL, 0xDBCB54A97F053D17ULL, 0xB7EDB14536DC6B24ULL, 0x0636396540910C0CULL, 
            0x3115EF74DA4E1013ULL, 0x0ED4281A5C85BB55ULL, 0xCA30F5BB67AE0D64ULL, 0xBB26F0EF0ED06260ULL, 
            0xD3AE6B03D9E7D9CEULL, 0x586875EDF1430161ULL, 0x457A6F449D6B9EC5ULL, 0x8FFAA4B6B9174299ULL, 
            0x5CC5AE31B457489DULL, 0x62AA160F335E2A3DULL, 0x02E3D9CF73181427ULL, 0xD5BFD50099A66877ULL
        },
        {
            0x1B67ACD16A70E49EULL, 0x012F0599203D9D85ULL, 0x7A2A35A4CD72971EULL, 0xF1EE95DBEC50B33DULL, 
            0x839F9A77A7BDC156ULL, 0x1B7B0C9D95777382ULL, 0xFC36CB0778FB9389ULL, 0x1C33B7F1927A14C5ULL, 
            0x8A31AD2437885F3FULL, 0x80F4B1276131EBBAULL, 0xE86ED20CAE7F6DBBULL, 0x70F3CEB1C20D8C1AULL, 
            0x3B0211BBDBC9008AULL, 0x3BAEA68E3D5738CBULL, 0xD27FF6E365A40D17ULL, 0x5DA3BA0A0EB73F9CULL, 
            0xF9B996E22D99C26EULL, 0x1EFCE768AE84BEF8ULL, 0x348F8BD8D21F900EULL, 0x3A27A55F9D13217AULL, 
            0xBD93C2A77DEEBBBFULL, 0xA5CD9B6D373BE306ULL, 0xEA5BBEF58A0EC476ULL, 0xA62CEE57C5C987B2ULL, 
            0xAD610FD8BC7EB251ULL, 0xE15B5E390CEC503DULL, 0xB8E71B9F6FA0075FULL, 0xFA08BC95F530AEE7ULL, 
            0xE3BC733CA2285288ULL, 0xA54C14807AA30762ULL, 0x8092988DA3DB4479ULL, 0x5B8FAAC4E3863A4FULL
        },
        {
            0x81BB24869D4A8789ULL, 0x4880D315FF193AA1ULL, 0xB2D47FB6C35C8AFFULL, 0x52523CC772D162A7ULL, 
            0xD971DC1F959D5713ULL, 0x96E6C999908584D5ULL, 0xD001F18358E97F83ULL, 0x1B7FF291B46597CEULL, 
            0xDB1DE7FEEF00D833ULL, 0x9FA5F5DA99119FBCULL, 0x4FA36826012FDA7AULL, 0x0EB9EB0CBE3F0E3BULL, 
            0xEC42FE7AC1B29048ULL, 0x19DA3A6604592AF5ULL, 0x2E33B23501624B11ULL, 0xE4F1017CC76FEB55ULL, 
            0x88D5DC5A4D4E7F32ULL, 0x876E1E41BA6CBFE2ULL, 0xAFA015050EB72581ULL, 0x8A25734E5F8D55E9ULL, 
            0xCA6F4505BFF9FB57ULL, 0x4CBB8BD0EC85995CULL, 0x5164E77876752579ULL, 0x05D9668E79511A8DULL, 
            0x3413A0365F04BB5CULL, 0xABFA1A6FDA540BD5ULL, 0x7C1D5445AE3F3772ULL, 0xAAFE263080A15408ULL, 
            0x364A00CA6C0A96DCULL, 0xED70771A6206E5DAULL, 0x652480A73773CB85ULL, 0xC6382BE748022E0BULL
        },
        {
            0xC904E89496FD1619ULL, 0xB8C5EC1B4084AB1BULL, 0x7A84E172075358F6ULL, 0x2CD389D9792BFBCDULL, 
            0xCCC112FCECBD98B8ULL, 0xE98F4B1CECEE03B7ULL, 0x2E79EB581E697FB9ULL, 0xAF7233F4E6B32FB7ULL, 
            0xB0A3508A8A761BF8ULL, 0xAE1DFEBE472DA7F0ULL, 0xA8127C29E21D7110ULL, 0xB46A5DC862F3E730ULL, 
            0x198AE4B714DA4B97ULL, 0x53616C9308CC3CEFULL, 0x00D174222F675BBDULL, 0xF3951BB90BA89113ULL, 
            0xAAD7BF4D79C1DB10ULL, 0xE64F4E3DB033E6C8ULL, 0x95807E1F986067B9ULL, 0x187785FEDE97CB3DULL, 
            0xA693308AE77FE28DULL, 0x4D6BA147200ABFE9ULL, 0xBF13775C2DA9074AULL, 0x354DBAE922616A1CULL, 
            0x8DA94856615892AFULL, 0x656CD88EFF9897CEULL, 0xCE9796C97F57F215ULL, 0x8C414CBF9C03CF10ULL, 
            0xE9ABF68F5621D7D1ULL, 0x6FC9699F30F3847BULL, 0xBB5050C79D44F2BDULL, 0xAC6764A37F8983C9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseGConstants = {
    0x5C09C36B09090816ULL,
    0xB50848AD8BF87797ULL,
    0x75C276C9BDFC83D5ULL,
    0x5C09C36B09090816ULL,
    0xB50848AD8BF87797ULL,
    0x75C276C9BDFC83D5ULL,
    0xAA57B64C9B093FE8ULL,
    0x94CCF2ED796F8670ULL,
    0x97,
    0xCF,
    0xB9,
    0xD5,
    0x1D,
    0x8A,
    0x8C,
    0x82
};

const TwistDomainSaltSet TwistExpander_Greezy::kPhaseHSalts = {
    {
        {
            0x4B7C5C8CC7EE3CECULL, 0x59A459AA9BF713A7ULL, 0xB297873F60AD6263ULL, 0x7CD9A0EFA8744413ULL, 
            0xE01EFF696A4C9BD7ULL, 0xD18C96A19906AEC9ULL, 0xF7BB775E917E8C09ULL, 0xA6F4D6C4FBFCC682ULL, 
            0x4C99C911E06F6A23ULL, 0xEF947FAA1B3CCB27ULL, 0xC7D99803965BD23BULL, 0xC701A1F50EC2D0E4ULL, 
            0xE6C95743BDC5F4E3ULL, 0xB4343FB191A45572ULL, 0x1D1E8F2E5038661EULL, 0x21ABE0425C1A14C7ULL, 
            0xE554FF6938C9B73DULL, 0xC860CC4A5764F99EULL, 0x3B9E4B874A11FA0DULL, 0xDEB048341EC11D00ULL, 
            0x07E3918D900C4A7CULL, 0x4ED0B7F36BD32078ULL, 0xD355A0EA9E2CC638ULL, 0x0AFFFD45C1DC4891ULL, 
            0xEE4BFF13A3D95BF1ULL, 0xAE5DC3BDE5E1C599ULL, 0x911BCB174C15BA86ULL, 0x2897774D553E00EBULL, 
            0x48704F78C492AE3DULL, 0xF2A7D1C261774A1AULL, 0xA794251BF24FB24CULL, 0xF88A0E399F355C6CULL
        },
        {
            0xDA75B338B5366E2DULL, 0x659CF9F3A135D1C4ULL, 0x12A3DD4521A3ED18ULL, 0xAB4F5471023C192AULL, 
            0xC7B8CB3C868B9B1EULL, 0x51CBF3C34F860798ULL, 0xF33AB7A6B32B00F2ULL, 0xE97A50A3092347ABULL, 
            0xA24B7855F7314D97ULL, 0xBABAD00662E9B174ULL, 0x3A0B648C409E84A0ULL, 0x476E66EC33EB3E05ULL, 
            0xADD1F35615D20919ULL, 0x55AADB0E8651F52BULL, 0xC9265A72AA0991DDULL, 0x94A0EDDCB5E5B36DULL, 
            0xF9D6AB4500423499ULL, 0xB7FAD1D34FE2D46DULL, 0x2285DE315E8C6FD9ULL, 0xCA5FD1A2F099A3DDULL, 
            0x8033F3CD0A4D5849ULL, 0x517A60129A1668E7ULL, 0xF62E96D1BCC5277DULL, 0x5FD6F96972A9DC2FULL, 
            0x3A0A2A155F992D40ULL, 0x44BC6F68F080C69AULL, 0xB1DEC113210180AAULL, 0xC98B9AB024FE0BFEULL, 
            0x66270B8EAD42269CULL, 0x53DA4AFF3E78242CULL, 0x1FDA30359C456832ULL, 0xC4CDED0B145F2291ULL
        },
        {
            0x9AD60EDE82857A35ULL, 0x73110A75531FF84AULL, 0x12594C034A30A216ULL, 0xA3F67F2FC4C013FFULL, 
            0xCAD7904517F5C75AULL, 0x46E8468CD35C1291ULL, 0xECC860606B4F5AA9ULL, 0xB6F4A05B4B4B8EADULL, 
            0x41B98ED10BC6090FULL, 0xFCF0262CBBD9BA16ULL, 0x896070AA012E8C77ULL, 0x2E04348CD21C65D2ULL, 
            0x6DC3F8F8DB206477ULL, 0x99990A8A3F96A45DULL, 0x1C3632E0C68A4F9BULL, 0x392B19B64377806BULL, 
            0x2ACD332D190356FCULL, 0x53B0F5878E711A85ULL, 0xE780AB134E421272ULL, 0x72552D9ADC4620CAULL, 
            0x9CE34E7F3F21DB59ULL, 0x8C1646A1BC13734FULL, 0x161BD6A3D1197528ULL, 0xE7C8168A256E4CC8ULL, 
            0xC3DE218E681E5228ULL, 0x643380F6C8D20595ULL, 0xE3A77C0F77C8D64EULL, 0xA0E37F4DCFE20174ULL, 
            0x630DB26EB68C3D88ULL, 0xE1E919701548053AULL, 0x5D088549B5E8D1BBULL, 0x6A77C3D0E328A4E5ULL
        },
        {
            0x1FD2E19BCFCB29F1ULL, 0x876773D471030F6BULL, 0xD874DC6D9CBEE2B6ULL, 0x391B3C0C18CABFB1ULL, 
            0xD5AE3658656FE78FULL, 0xD25FB951D8C092C2ULL, 0xF52D58272932F22BULL, 0x02D63D2C19E91198ULL, 
            0xB6AFBFC520FAA4CBULL, 0xCF327660BB013CCCULL, 0x617118199FABE8E6ULL, 0x3840CFF261C816E9ULL, 
            0xA538F2A559D7FA47ULL, 0x159138990EBA4492ULL, 0x7BC38C13BD340F47ULL, 0x0D35A38DDBFDABF1ULL, 
            0x5D73A5F3278BA83AULL, 0x4629A81D8CC3B6DAULL, 0x556F3CBF34EEE064ULL, 0x5B29EA219AF8A8D8ULL, 
            0x669DD0203CF490B1ULL, 0xF310DA1371E7ACDEULL, 0x881410DC9D74EB7BULL, 0xB2173C26C9D38ACEULL, 
            0x6F64AFE05B7AE1AAULL, 0x4ABF3414D7EB7A04ULL, 0x3216B4C8159EB2C8ULL, 0xE377D4287944585EULL, 
            0xC9D65FADF0C3AC5AULL, 0xC2F2350E5202FE28ULL, 0x8C02831C38CA8B4DULL, 0x28F39AB55F8908C4ULL
        },
        {
            0xDDA060CDD6C568C4ULL, 0x704ED63332C6895FULL, 0x11379084CB1DCE0CULL, 0x253E1B4D84EF62E5ULL, 
            0x95929B6496DAFFCDULL, 0xAFAA5CAE9CF5E24FULL, 0xA6D14C5D55EC1F03ULL, 0x810F22F8D7E43392ULL, 
            0xFFA57806198ACE23ULL, 0x76785A21BB90DABBULL, 0x216A482A626ADEDCULL, 0x6FFA999275E6065DULL, 
            0xE6ABFBA0E219B8FAULL, 0x3B468BFEB722E14FULL, 0xF03155F6BA5D60FEULL, 0x87B2B11222A1D0C6ULL, 
            0xA4C2FE85C5337520ULL, 0xF6F83DC3DE181F1EULL, 0xFDE8DD41519969CBULL, 0x67B0404457906E5FULL, 
            0xC7D04508EDCA7124ULL, 0x75167A43579DA7FDULL, 0x72E7B8609F552455ULL, 0x163D69C459440F91ULL, 
            0x7084DD5AC1332BEDULL, 0xD2D7EB71FABFC239ULL, 0x8F0F653CBE6F8505ULL, 0xF5FC69ACE544C8A0ULL, 
            0xFEF67F9099D9C46CULL, 0x59B5A9BF7F69D331ULL, 0xF0971538022F0465ULL, 0xB9E6B3C29F286A27ULL
        },
        {
            0x85097510AEFC2390ULL, 0x6FE4BCD7D89277ECULL, 0xFA7F8AAED28B8080ULL, 0x8975B2F89EDE3074ULL, 
            0xA12059AE1C5526AAULL, 0x0A8BC790F5379856ULL, 0x836EA52BAC67DD70ULL, 0x244A7C97EFB1B3BBULL, 
            0x4C609151745946F9ULL, 0x287F6D752D7593E0ULL, 0x667E89FF8F7E06ABULL, 0x1226AD48C0768A19ULL, 
            0x47855B2FA2160067ULL, 0x9C6AFDFC4A6DD3E1ULL, 0xA23A8C1017C5F39BULL, 0xA25AF463CF7BBFEAULL, 
            0xF2A4F17D5CCEAEE2ULL, 0x8801147207128B53ULL, 0xFC3F2C47F97F626DULL, 0x641C972EC72EABAEULL, 
            0xCF0093510D1B18BDULL, 0x58F92767A113ADC2ULL, 0x4C8F417099C2F955ULL, 0x5FDAF2F0B78C06F5ULL, 
            0x66D59D0FAF577892ULL, 0xADE59FE4BD777997ULL, 0x17F80D746698FBEEULL, 0xCE14AE407E21FCC8ULL, 
            0xC33FAF795963AE80ULL, 0xF1521B36A100504DULL, 0x3C016C06D7E73AA9ULL, 0xA8A900D0E49E65F5ULL
        }
    },
    {
        {
            0x3839010CD68A3C8DULL, 0xBE8662FE1F204809ULL, 0xF5CE0696837DD2DCULL, 0xD149D6D21ABDD414ULL, 
            0x47016A0287251998ULL, 0x1A3CE5F78FF23551ULL, 0x673AF2D37C0BAB96ULL, 0xBAB5752F29C4AA40ULL, 
            0xFE50851AA4DA5944ULL, 0x41F908369EF05616ULL, 0xAFDFF03DD702C41FULL, 0x422C291464B8A7AEULL, 
            0x7F571472D78B8BEBULL, 0xC14D8C0B452B0E3CULL, 0x79150C42B7B9C8E2ULL, 0x732930CF51759CAFULL, 
            0x15FCC2D869387900ULL, 0x9C89895698A87954ULL, 0xBA09DACBA3344FFEULL, 0x0ED9475D7DF997CFULL, 
            0x7DC7256A7ED60C06ULL, 0x27DC3A37BD13007AULL, 0x9F9AF599E12D3957ULL, 0xEBEBDBB8CC135D82ULL, 
            0x8C5C39B2BA99E6BBULL, 0x2D0213EA5F5A26C8ULL, 0x6D5715DD80D29FC0ULL, 0xF864832F41DAE27EULL, 
            0x1AE6D7420E5C076EULL, 0x11CC646606F1576FULL, 0x52D1139EAE468A51ULL, 0x3146543D27F39896ULL
        },
        {
            0x248AA714A5795F41ULL, 0x4413CD046D5F714CULL, 0x0357990292373F68ULL, 0x899528B71E6DBED7ULL, 
            0x5844DF5223D5F65AULL, 0x718DECBD9455C679ULL, 0x3AB2307943EF338AULL, 0xF26FDC8B02D1DB15ULL, 
            0x471F895DC8A74D6FULL, 0x9599C8C6A6DC46D7ULL, 0x1A3BE586D9C6F3A4ULL, 0x9ADD8FCCA40D1857ULL, 
            0x0C2756549382C532ULL, 0x28575337D9DD453FULL, 0xD50EF5C4A60DA138ULL, 0xC85BCBD4636255A3ULL, 
            0xA2C3B652CDB2328CULL, 0x5A483E1CE2B3C0A3ULL, 0xE210D0907DC1AC7CULL, 0x6810C27DE6897C35ULL, 
            0x4775B10C4799FBC2ULL, 0x2845F0EDBC72F3E0ULL, 0x3D91ADC0AA9CFDFAULL, 0xB8962E826E27BE61ULL, 
            0xACC4A1390207052BULL, 0xA08FABE61E043FDDULL, 0x0360C86D70C07EFFULL, 0xA385974FF8996B6CULL, 
            0xFF2D2B0EC2D4CE8BULL, 0x756C5F1901A1E23EULL, 0xA393010D3148CF24ULL, 0x69B01ED2A740DD62ULL
        },
        {
            0xAF53BFA2F916B690ULL, 0xB9B4D7987BF35182ULL, 0x57E85B814B2B15B9ULL, 0x80C61C08D4979A36ULL, 
            0x1D00AE268D885D67ULL, 0x41FCFD56F9EB07F2ULL, 0x65AF4550FA68E20FULL, 0xC254A364C26E53E1ULL, 
            0x9BFC7AABF6E11C82ULL, 0x70DF9BB307A766B1ULL, 0x64B2AF6E921A08B2ULL, 0xEBC66BC3C68EB230ULL, 
            0x6187B96FAEF3468DULL, 0x7A7D7DDBDD8F81CAULL, 0xF0D62552CA500A6BULL, 0xF479227AB233AA21ULL, 
            0xE1F7D4C8C1DA5DC0ULL, 0xFB30F8720F160F4AULL, 0x10FBA93683BF86A9ULL, 0x3DE04EBC55CDEB4AULL, 
            0x7CE2618E878FD572ULL, 0x14FF663D182EB734ULL, 0x56ABD3B8B7EAB6E2ULL, 0x7BA49621A554C1FAULL, 
            0xA5A27292EC9F37A3ULL, 0xD027196D7FADFD4DULL, 0xA22431AA51453EA9ULL, 0xB9EE34BDB02B32E0ULL, 
            0xB563247218CF46CCULL, 0x53B02896DF3E3D64ULL, 0xC9DC5BEC1F0FA2B2ULL, 0x83248FE86FE76DF9ULL
        },
        {
            0x5CA0612E903C5858ULL, 0x7CEBF17EFC7F0653ULL, 0xF66383BCC0CDA22DULL, 0x82D8E070E6C6FF69ULL, 
            0x47C48EA299D93A40ULL, 0x63103936564122FEULL, 0x1EE1A7CB74060B85ULL, 0xCD3F814BC5766D8BULL, 
            0x3E03FC3040D96C17ULL, 0xB3367DE56A212AE3ULL, 0xAE80B3F9378F2E7FULL, 0xC7A4430D954B3657ULL, 
            0xD465018714EA8595ULL, 0xF0E3D6732BA44C34ULL, 0xB13E84FD6C0964BFULL, 0xDEFA4FF80ECC8053ULL, 
            0xD87F9F2AEDA8A670ULL, 0xBDA554DFBDF6E918ULL, 0x40D2ADF8DC2D4949ULL, 0x4E147B20CA87B0BCULL, 
            0xC63E41FD4B19D501ULL, 0xAEFC2B29CF1B84FAULL, 0xE429B9B5B0416E5AULL, 0x2C7B9C1F03C76188ULL, 
            0xC1062101BA4E0685ULL, 0xBEA6FB96D80C36A9ULL, 0x8B3233C55CF351A4ULL, 0x78CED4E67FC8B2CAULL, 
            0xD778415753B989E0ULL, 0xE2B3D5DF4686B86EULL, 0xAC8FBB0EA2BE09DEULL, 0xF03EA52CFADC92E3ULL
        },
        {
            0x5C96F08AF81E0400ULL, 0x955AC77236772DA1ULL, 0x7FCB2BB3C91F322AULL, 0xEBB11AE0684E6D3FULL, 
            0x7731FA58358A3C79ULL, 0x96D68FA7D97373F7ULL, 0x2ECA84BE997E76E0ULL, 0xBBBC30983DDD6AECULL, 
            0x794D7952F45FCD5AULL, 0xB0035C9D7E71FBA5ULL, 0x4406E0150044B8E7ULL, 0x45155702911D4450ULL, 
            0x8B9930D7233CA636ULL, 0x9FD92FD03CD808CAULL, 0x4ADDE303F3E4E407ULL, 0x411FBB08199495BAULL, 
            0xD47696D58609C1A4ULL, 0x0A1B7948F1B8E5E6ULL, 0x5F2A35523EB12B66ULL, 0xE09AE8BD8E1288E6ULL, 
            0x016F4F22BAFD9680ULL, 0x5EFF476CCD40BFEDULL, 0x53A19BCC25BDA9ACULL, 0xD3E8309AC6CA4CD5ULL, 
            0xBFA3ABBE1557ECE3ULL, 0xA7256A147B32D588ULL, 0xB7EB966C85C27B13ULL, 0x8029BF71CC2D9085ULL, 
            0x949F81258FDA61FAULL, 0x179BD08856DA0E47ULL, 0xB0681E33FEE654EDULL, 0x83C2CBE66383CDB8ULL
        },
        {
            0x93DE0FE57F5EBC56ULL, 0x47B693A6B6EB0A45ULL, 0x9D98CFB34AD96029ULL, 0x8EB607C9F9F95E84ULL, 
            0x315BAF308FEE0821ULL, 0x5D4C61ADFB3811FFULL, 0x5F13C258BCF1CD56ULL, 0x1BD2A66C5C708737ULL, 
            0x19C00EB384502D41ULL, 0x593F29E80C10979EULL, 0x0240685E723F522DULL, 0xAD01CC9E16475A2DULL, 
            0xDD523C234DD87814ULL, 0xCFEE4AEE125FD71AULL, 0x4E005A4A625E380EULL, 0x4E0F7BAD2D81F852ULL, 
            0x241E466C1C8F580EULL, 0x6D293198586F9984ULL, 0xB51185B31C8BA55AULL, 0x8D46875FF3956160ULL, 
            0x000C32C465EDE489ULL, 0xFF4DCB2A3D2F012FULL, 0x1FE37F8EF7074BF5ULL, 0xAE537D48C1AE10F5ULL, 
            0xAA3EF3BC91086AB6ULL, 0x87AF83D8A0C2BFAFULL, 0xAA24949CE52B8E03ULL, 0x9814BD4F5DCEE480ULL, 
            0xB879E7638C35D924ULL, 0xB884911C36B168EDULL, 0x69513260311C76C7ULL, 0x5D341845652A2A99ULL
        }
    },
    {
        {
            0x921F012C38B5DEF4ULL, 0x65A0EF0567DAC1B7ULL, 0x0B4EC46EFD4917E1ULL, 0xE07BBCBF284207EFULL, 
            0xB0867EB7CA02348FULL, 0xC68FF78C99FE7124ULL, 0x1782CFE68A8B7C32ULL, 0xF31E257165615397ULL, 
            0x3D06EC5BDD6FC575ULL, 0x66401359F23F0CA6ULL, 0x2ED3A1C46ABB405DULL, 0x28A272E4129FD213ULL, 
            0xBB96A2A7B2F071EEULL, 0x2065B5A3084E375AULL, 0x01687A90D66883D9ULL, 0xB9B2B6E78BE711F3ULL, 
            0xCF09088EEF8711CEULL, 0xF3FFDF9ADA3EC5DFULL, 0xC1FD4F526ACF84B6ULL, 0x3F887AE7013CF0EAULL, 
            0xA670FEF17A860032ULL, 0x141E354B0FD39B55ULL, 0xC9043D07B6950112ULL, 0x60874C3D1F94FA3AULL, 
            0xFC611F507AB6FBB8ULL, 0xE7CEDF8AF5ADF9F9ULL, 0xAC1F4385BB5C5EEDULL, 0xE0E63D30EE72983FULL, 
            0xCBCBDBDC643B827DULL, 0xEFF2606C23C9F09FULL, 0x9B1364ACE93DD908ULL, 0xFC9628EAD0F9A5ACULL
        },
        {
            0x2CBB450235DA261FULL, 0x2D2A50CC003C26A1ULL, 0xEADB66E27B505F95ULL, 0x517AC3B636E6A2F7ULL, 
            0xA78522CAF2746494ULL, 0x6697E90C77D2AE67ULL, 0x1D69564233175B3EULL, 0x7C02A6361CF3FD3DULL, 
            0xE07A0E7BDFB4BDE2ULL, 0x9951DA4A95B627DAULL, 0xED36BC48E2873461ULL, 0xDC9317D8394BB861ULL, 
            0x2AAD5BC22754EA88ULL, 0xC568C96C4AA29B4AULL, 0x12BBF4E8B39AF310ULL, 0x776600EDF768508BULL, 
            0xACC486293F8D0FBBULL, 0x6CDDB18A7494B561ULL, 0x71202274532BE019ULL, 0xCEC7CF7717F51393ULL, 
            0x37A7B4A69FCD90D4ULL, 0xB627B0468433CE2CULL, 0xAB76AC9AA2DB6FEBULL, 0x0B9E2084C5A6B65CULL, 
            0x742761A3ED3722B5ULL, 0x04FDBF8526F928C3ULL, 0x101D80034F3159C1ULL, 0x4597A40D5814E822ULL, 
            0x6CA2924D09D18A8FULL, 0x8D21790A48479B4EULL, 0xEFB8B11B4F63A04CULL, 0x944731308204ECB7ULL
        },
        {
            0xFF7B6E9A702C8865ULL, 0x859504FD6A94B6A2ULL, 0xA312EF68103039BCULL, 0x2C2C9DC8BC02D382ULL, 
            0x0A73CDFD0B0290A5ULL, 0x93C11147E1848713ULL, 0x7D81B626A5FA9E89ULL, 0xDD1CE7EBC495AFE8ULL, 
            0x18E2EE2C226778BDULL, 0xCB493CEA5F7F7438ULL, 0xBEE81E9235EBB961ULL, 0xA7648EA1773751A8ULL, 
            0x8193F35934FB2161ULL, 0x3E8403493F9DAD47ULL, 0x44E941D47DF0A785ULL, 0xC82AE41D950DB1D4ULL, 
            0x0A7D0F8F54BC2893ULL, 0xF85D475CB3C3012CULL, 0x68AF2952BF576CAFULL, 0xA53F299BE896A73DULL, 
            0x3F3D7A014C58E3E9ULL, 0x9B4253F01685FAACULL, 0x86A12088CDFDE16AULL, 0xFBAEA9540410567CULL, 
            0x50FD08FAE13C8458ULL, 0x8CC9553863FE0D9FULL, 0xADA13768EABB0DA9ULL, 0xA14BFD536D06EF04ULL, 
            0x6EBF28AD187958BBULL, 0x19FE4D80B03274E7ULL, 0x90934430E7148434ULL, 0x9F37118786EC3FF8ULL
        },
        {
            0xAF3ACC77733AA7C8ULL, 0x70136D001EC7E1C4ULL, 0x61E0C47BE50A4139ULL, 0xCAC6A10E848F9375ULL, 
            0x9FF1D3F757E5067AULL, 0x577B549EB0AF06D1ULL, 0x50CF41C39556815AULL, 0xFB4909D0562EA551ULL, 
            0x322FF2B8E9A42FF2ULL, 0x460D94D22132379AULL, 0x047E2CAE71D94FADULL, 0xD0C1EC7C28A30320ULL, 
            0x02E53E125B4A8263ULL, 0x37AC0D120A2ECAFFULL, 0xA9236DCE08958827ULL, 0x3C20C7C0FFF1C3E2ULL, 
            0x5E12C17F6ADD7C5BULL, 0x2BE1EA239CA330EDULL, 0x65B2FAA561FC555EULL, 0x9343512294985228ULL, 
            0xE38B0D55F078575EULL, 0x7682E235421A84DEULL, 0xCD2ED36DE9BB5064ULL, 0x2DF887CB4C6D45FDULL, 
            0x38D2BFC156578900ULL, 0x89DD50333BBDAC5BULL, 0xCF857DE5ECD161CAULL, 0xACB60939E64827CBULL, 
            0x0E16F62CEB8C5B2FULL, 0xEDBF77193CD4F327ULL, 0x0AAB7506D43FDAE4ULL, 0x2B61A0CB11DAFD46ULL
        },
        {
            0x5343B591F42FF226ULL, 0x96B0837F7264BAF2ULL, 0x06B583688A43BAC0ULL, 0xD279CE915011BC1DULL, 
            0x0325658492FF31A6ULL, 0x82705D1F3C697936ULL, 0x99F35CE53C3B0CB9ULL, 0x0C998BE9D2A0667EULL, 
            0xAA6E1FFA0841CEEDULL, 0x2E99D823A037B6B3ULL, 0x921BC52F8521F0DDULL, 0xADAA7F8C940D7A46ULL, 
            0x13A096EA706E7BABULL, 0x25D490C08D5F2148ULL, 0x9A7C090279701861ULL, 0xA917EB62ECDB4AA2ULL, 
            0x771CF82F9B841D07ULL, 0x548FCA7EEBB16B1CULL, 0xEA16AC436EC0FB46ULL, 0xEC03E48AD669A27BULL, 
            0x7EEAC074025BA4DDULL, 0x11FA7E624CE754EAULL, 0x3EE6BC7EE277BC20ULL, 0x3B432EAF35355A2CULL, 
            0x4CA948AE9FB81B83ULL, 0x9E268EBE05EA7D96ULL, 0x534B20C2CBA3E832ULL, 0x3EDC1387BA510BE5ULL, 
            0x5AAEAF489D506597ULL, 0x651B5A29A06243EAULL, 0x56D64A6004A427DAULL, 0x63B2F92F1AD4EF5DULL
        },
        {
            0x277C53457DBA5B0FULL, 0x16D92FB5DAA8CD48ULL, 0x87DB1A0BA94C2744ULL, 0x9907034D66D7966FULL, 
            0x97554739856B34A9ULL, 0x751B12C50B80C23CULL, 0xA81B4172C2224CC6ULL, 0x920F880DC7F6E562ULL, 
            0x8D78A830A4C82F4AULL, 0x73E13C7822E2E02EULL, 0x8DD22F21DBCFD72DULL, 0xCC1D2AC4EE904254ULL, 
            0xA3B0BD04FF4B3C28ULL, 0x8197FAD45FB453C5ULL, 0xA518ED42524B5C10ULL, 0xAE52D198DDA2C746ULL, 
            0x7F6A612DF56ADAFAULL, 0xCBCB6838E61F6F31ULL, 0x3CE539CC0D8F9C0CULL, 0x1A7DD2AEA7787805ULL, 
            0x1A40E901CCE98FD6ULL, 0x678F8E97E93C25B7ULL, 0xA12F7575D7B40752ULL, 0x1260667384F422C3ULL, 
            0x8AADEEC1AFFE402EULL, 0xC296CB16DB473F81ULL, 0x1CCBB4193E85135FULL, 0x417E5F76EBCAA891ULL, 
            0xC3C81CC2C52B4E8FULL, 0x2458DEE5DEDEFD7EULL, 0x6A43D87EE78F7CC2ULL, 0x6BCFDAF535190D97ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Greezy::kPhaseHConstants = {
    0x4F124F10E618072FULL,
    0xE8DD87D0E75605E0ULL,
    0x429704E411BD8082ULL,
    0x4F124F10E618072FULL,
    0xE8DD87D0E75605E0ULL,
    0x429704E411BD8082ULL,
    0x3D1B332F76A227DAULL,
    0x4A503B4085D4C8B4ULL,
    0xD0,
    0xC4,
    0xC8,
    0x51,
    0x0E,
    0x7C,
    0x85,
    0xF6
};

