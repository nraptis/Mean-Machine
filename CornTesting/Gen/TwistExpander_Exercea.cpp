#include "TwistExpander_Exercea.hpp"
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
#include "SnapShotter.hpp"

#include <cstdint>
#include <cstring>

TwistExpander_Exercea::TwistExpander_Exercea()
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

void TwistExpander_Exercea::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  std::uint8_t *pSnow,
                                  int pIndexKDF) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }
    if (pIndexKDF == 0) {
        SnapShotter::SnapStart_KDFA(pWorkSpace, this);
    }

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
    std::uint64_t aPrevious = 0xA6D90BF43D109115ULL; std::uint64_t aIngress = 0xA620007B7337EBFBULL; std::uint64_t aCarry = 0x9CFEEB735D39A380ULL;

    std::uint64_t aWandererA = 0xC266D1CC44A0C1C0ULL; std::uint64_t aWandererB = 0xCF268B643EFBF8E0ULL; std::uint64_t aWandererC = 0xE44409213DEFC5BEULL; std::uint64_t aWandererD = 0xC76DC6D3CC38D640ULL;
    std::uint64_t aWandererE = 0xA306C769B44783C2ULL; std::uint64_t aWandererF = 0xA4536E20C59B2AA4ULL; std::uint64_t aWandererG = 0xBF9E03BC98485F3CULL; std::uint64_t aWandererH = 0xEF36910E15A2A7B6ULL;
    std::uint64_t aWandererI = 0xF34E32C5CB76AA8EULL; std::uint64_t aWandererJ = 0x83BB49EC86E862AEULL; std::uint64_t aWandererK = 0xCE2C524A3EC0285FULL;

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
        aPrevious = 12843639563643948685U;
        aCarry = 17861393018078463770U;
        aWandererA = 9903233885192566124U;
        aWandererB = 12119854740943163037U;
        aWandererC = 14456689961980095989U;
        aWandererD = 16439927746221128988U;
        aWandererE = 15031368660952662657U;
        aWandererF = 15795896038824253549U;
        aWandererG = 12780619470650513697U;
        aWandererH = 10498469396392843619U;
        aWandererI = 12672709577233819290U;
        aWandererJ = 16539247170448303266U;
        aWandererK = 14433585335102971161U;
    }
    //
    // ---------------------------------------------------
    // KDF_A_A kdf_a_loop_a:
    // ---------------------------------------------------
    // read from: source, snow
    // temp storage: work_a, work_b
    // ---------------------------------------------------
    // write to: work_a, work_b, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::KDF_A_A(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_A");
    }

    //
    // ---------------------------------------------------
    // KDF_A_B kdf_a_loop_b:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::KDF_A_B(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_B");
    }

    //
    // ---------------------------------------------------
    // KDF_A_C kdf_a_loop_c:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::KDF_A_C(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_C");
    }

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
    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_DIFFUSE");
    }

    //
    // ---------------------------------------------------
    // KDF_A_D kdf_a_loop_d:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::KDF_A_D(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_D");
    }

}

void TwistExpander_Exercea::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  int pIndexKDF) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr)) { return; }
    if (pIndexKDF == 0) {
        SnapShotter::SnapStart_KDFB(pWorkSpace, this);
    }

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
    std::uint64_t aPrevious = 0x8983AF54C21D0062ULL; std::uint64_t aIngress = 0xF5F4AC8419BDD375ULL; std::uint64_t aCarry = 0xCA0E401C2E530022ULL;

    std::uint64_t aWandererA = 0xF972ABD21C4197BCULL; std::uint64_t aWandererB = 0xEA0690F9AD5F7B10ULL; std::uint64_t aWandererC = 0xD58FADD0AA34770AULL; std::uint64_t aWandererD = 0xF6E044ECE5B41747ULL;
    std::uint64_t aWandererE = 0xBA2DFCF8999FD845ULL; std::uint64_t aWandererF = 0xA4C561584B801FB8ULL; std::uint64_t aWandererG = 0xE3C75B83F64C1D73ULL; std::uint64_t aWandererH = 0x8A36E79D0EF447DFULL;
    std::uint64_t aWandererI = 0xE75653CFCEFAF6C7ULL; std::uint64_t aWandererJ = 0xEDF2D1EC45632340ULL; std::uint64_t aWandererK = 0xC50252D52B19A837ULL;

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
        aPrevious = 12621060158190705051U;
        aCarry = 16594546427316550832U;
        aWandererA = 17983817161680104744U;
        aWandererB = 11099675755643459997U;
        aWandererC = 17964774114320965316U;
        aWandererD = 9447780627638747191U;
        aWandererE = 10044458899451866112U;
        aWandererF = 18367316297271240032U;
        aWandererG = 13791469095105691089U;
        aWandererH = 13459035387690197100U;
        aWandererI = 14790378815804078807U;
        aWandererJ = 12088771846892288631U;
        aWandererK = 10059608498509346724U;
    }
    //
    // ---------------------------------------------------
    // KDF_B_A kdf_b_loop_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // temp storage: operation_a, operation_b, operation_c, operation_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::KDF_B_A(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFB(pWorkSpace, this, "KDF_B_A");
    }

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
    TwistExpander_Exercea_Arx::KDF_B_B(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFB(pWorkSpace, this, "KDF_B_B");
    }

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
    TwistExpander_Exercea_Arx::KDF_B_C(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFB(pWorkSpace, this, "KDF_B_C");
    }

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
    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFB(pWorkSpace, this, "KDF_B_DIFFUSE");
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
    TwistExpander_Exercea_Arx::KDF_B_D(pWorkSpace,
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

    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFB(pWorkSpace, this, "KDF_B_D");
    }

}

void TwistExpander_Exercea::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB1419007F12211DAULL;
    std::uint64_t aIngress = 0xADC320027F976B5DULL;
    std::uint64_t aCarry = 0xD609D968F3CAF229ULL;

    std::uint64_t aWandererA = 0xF053F99DC5E02B17ULL;
    std::uint64_t aWandererB = 0x96E7AEA706E94364ULL;
    std::uint64_t aWandererC = 0x9E3805AD61479D38ULL;
    std::uint64_t aWandererD = 0xDE6414C13CFDD8F4ULL;
    std::uint64_t aWandererE = 0x80A4B808580138EEULL;
    std::uint64_t aWandererF = 0xB105A696604F313BULL;
    std::uint64_t aWandererG = 0xBD33A9B96FFBF30EULL;
    std::uint64_t aWandererH = 0xDE52A8316CF58DE2ULL;
    std::uint64_t aWandererI = 0xA621ACFD1C2B8541ULL;
    std::uint64_t aWandererJ = 0xE09E7AF5C1EED7B5ULL;
    std::uint64_t aWandererK = 0x9A35E84DBD18EB73ULL;

    // [seed]
        TwistSnow::AES256Counter(mSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(mSource, aSnowLaneB);
        TwistSnow::Sha256Counter(mSource, aSnowLaneC);
        TwistSnow::Aria256Counter(mSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneB, 0);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts), 0);
        TwistSquash::SquashA(aExpandLaneD, aExpandLaneB, aExpandLaneC, aExpandLaneA, aInvestLaneD);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA,
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
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase B
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneD, 1);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts), 1);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneC, aExpandLaneB, aExpandLaneD, aInvestLaneF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA,
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
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts), 2);
        TwistSquash::SquashA(aExpandLaneC, aExpandLaneD, aExpandLaneA, aExpandLaneB, aInvestLaneA);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA,
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneC, 3);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneC, &(mDomainBundleEphemeral.mPhaseDConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseDConstants), &(mDomainBundleEphemeral.mPhaseDSalts), 3);
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneD, aExpandLaneC, aInvestLaneG);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseDSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneC, &(pWorkSpace->mDomainBundle.mPhaseDConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase E
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneB, 4);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseEConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseEConstants), &(mDomainBundleEphemeral.mPhaseESalts), 4);
        TwistSquash::SquashA(aExpandLaneC, aExpandLaneD, aExpandLaneB, aExpandLaneA, aInvestLaneC);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseESalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseEConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////        Phase F
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneD, 5);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseFSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseFConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseFConstants), &(mDomainBundleEphemeral.mPhaseFSalts), 5);
        TwistSquash::SquashA(aExpandLaneD, aExpandLaneC, aExpandLaneB, aExpandLaneA, aInvestLaneE);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseFSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseFSalts.mWandererUpdate.mSaltA,
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneA, 6);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseGSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneD, &(mDomainBundleEphemeral.mPhaseGConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseGConstants), &(mDomainBundleEphemeral.mPhaseGSalts), 6);
        TwistSquash::SquashB(aExpandLaneB, aExpandLaneC, aExpandLaneA, aExpandLaneD, aInvestLaneB);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA,
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
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltA,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltC,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltE,
                      mDomainBundleEphemeral.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(mDomainBundleEphemeral.mPhaseHConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseHConstants), &(mDomainBundleEphemeral.mPhaseHSalts), 7);
        TwistSquash::SquashC(aExpandLaneC, aExpandLaneD, aExpandLaneA, aExpandLaneB, aInvestLaneH);
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE,
                      pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(pWorkSpace->mDomainBundle.mPhaseHConstants));
    ////////
    ////////
    ////////////////////////////////////////////////////////
    // GSquashInvestToKeyBoxes (start)
    std::memset(pWorkSpace->mOperationLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mOperationLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mOperationLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mOperationLaneD, 0, S_BLOCK);

    std::memset(pWorkSpace->mWorkLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mWorkLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mWorkLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mWorkLaneD, 0, S_BLOCK);

    std::memset(pWorkSpace->mExpansionLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mExpansionLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mExpansionLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mExpansionLaneD, 0, S_BLOCK);

    std::memset(pWorkSpace->mFireLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mFireLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mFireLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mFireLaneD, 0, S_BLOCK);

    std::memset(pWorkSpace->mSnowLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneD, 0, S_BLOCK);

    SnapShotter::SnapStart_SEED(pWorkSpace, this);

    SquashInvestToKeyBoxes();

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "INVEST_KEY_BOX");

    std::memset(pWorkSpace->mInvestLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneD, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneE, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneF, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneG, 0, S_BLOCK);
    std::memset(pWorkSpace->mInvestLaneH, 0, S_BLOCK);

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "ZERO_INVEST");

    // GSquashInvestToKeyBoxes (end)
    //
    //
    // ---------------------------------------------------
    // GSeedRunSeed_A seed_loop_a:
    // ---------------------------------------------------
    // read from: source, key_row_read_a, key_row_read_b
    // temp storage: work_a, work_b, work_c, work_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::Seed_A(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_A");

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
    TwistExpander_Exercea_Arx::Seed_B(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_B");

    //
    // ---------------------------------------------------
    // GSeedRunSeed_C seed_loop_b:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: invest_c, invest_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::Seed_C(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_C");

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
    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "SEED_DIFFUSE_A");

    //
    // ---------------------------------------------------
    // GSeedRunSeed_D seed_loop_d:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    // write to: snow_a, snow_b, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::Seed_D(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_D");

    //
    // ---------------------------------------------------
    // GSeedRunSeed_E seed_loop_e:
    // ---------------------------------------------------
    // read from: invest_a, invest_b, invest_c, invest_d
    // temp storage: fire_a, fire_b, fire_c, fire_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::Seed_E(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_E");

    //
    // ---------------------------------------------------
    // GSeedRunSeed_F seed_loop_f:
    // ---------------------------------------------------
    // read from: operation_a, operation_b, operation_c, operation_d
    // temp storage: snow_a, snow_b, work_c, work_d, invest_a, invest_b, invest_c, invest_d
    // ---------------------------------------------------
    // write to: snow_c, snow_d, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::Seed_F(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_F");

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
    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "SEED_DIFFUSE_B");

    //
    // ---------------------------------------------------
    // GSeedRunSeed_G seed_loop_h:
    // ---------------------------------------------------
    // read from: snow_a, snow_b, snow_c, snow_d
    // temp storage: invest_a, invest_b, invest_c, invest_d, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    // write to: work_a, work_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::Seed_G(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_G");

        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, pDestination);
    //
    // ---------------------------------------------------
    // GROW_A grow_key_a:
    // ---------------------------------------------------
    // read from: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    // write to: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "GROW_A");

    //
    // ---------------------------------------------------
    // GROW_B grow_key_b:
    // ---------------------------------------------------
    // read from: expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Exercea_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "GROW_B");

    Zero_PostSeed();
}

void TwistExpander_Exercea::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 1
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 2
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 3
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 4
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_a row 5
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_a row 6
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 7
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 0
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_b row 1
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 2
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_b row 3
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 4
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 5
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 6
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 7
    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[aIndex]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[aIndex]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[aIndex]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[aIndex]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[aIndex]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[aIndex]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[aIndex]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[aIndex]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Exercea::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint64_t pNonce,
                                       std::uint8_t *pSource,
                                       std::size_t pBlockIndex,
                                       std::size_t pBlockCount,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pNonce, pSource, pBlockIndex, pBlockCount, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    if (pBlockIndex == 0U) {
        SnapShotter::SnapStart_TWIST(pWorkSpace, this);
    }

    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xF2476DF3EE28D870ULL; std::uint64_t aIngress = 0xEA2670A8AD34A5FDULL; std::uint64_t aCarry = 0xC9FBB7E8B571C386ULL;

    std::uint64_t aWandererA = 0xD939BC87359277B0ULL; std::uint64_t aWandererB = 0xF787CD276CB77AE0ULL; std::uint64_t aWandererC = 0xE1655602F9410789ULL; std::uint64_t aWandererD = 0xD968B71A7B75EEA6ULL;
    std::uint64_t aWandererE = 0xD07C674C7700EDE1ULL; std::uint64_t aWandererF = 0x8B512A239AF31839ULL; std::uint64_t aWandererG = 0xAA3CC89AFD2F65BAULL; std::uint64_t aWandererH = 0x9F005B269DD7D3E7ULL;
    std::uint64_t aWandererI = 0xA419ADD10EEA8478ULL; std::uint64_t aWandererJ = 0x91DDCD4C82FA7B2FULL; std::uint64_t aWandererK = 0xD5439E821DECFA9DULL;

    // [seed]
    {
        aPrevious = 11577172493461141702U;
        aCarry = 10973598395276256851U;
        aWandererA = 16683782401802617933U;
        aWandererB = 18065082076905237952U;
        aWandererC = 15167080186486922135U;
        aWandererD = 13424914003282836530U;
        aWandererE = 16787644926081533603U;
        aWandererF = 9896620385423119065U;
        aWandererG = 14866370503100480034U;
        aWandererH = 17914660482627423476U;
        aWandererI = 16976371610954093016U;
        aWandererJ = 12408608382228205112U;
        aWandererK = 15929300668921313855U;
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
    TwistExpander_Exercea_Arx::Twist_A(pWorkSpace,
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

    SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "Twist_A");

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
    TwistExpander_Exercea_Arx::Twist_B(pWorkSpace,
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

    SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "Twist_B");

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
    TwistExpander_Exercea_Arx::Twist_C(pWorkSpace,
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

    SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "Twist_C");

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
        TwistExpander_Exercea_Arx::GROW_A(pWorkSpace,
                     &aPrevious,
                     &aIngress,
                     &aCarry,
                     &aWandererA,
                     &aWandererB,
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
        SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "GROW_A");
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
        TwistExpander_Exercea_Arx::GROW_B(pWorkSpace,
                     &aPrevious,
                     &aIngress,
                     &aCarry,
                     &aWandererA,
                     &aWandererB,
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
        SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "GROW_B");
        } else {
        TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    }
}

void TwistExpander_Exercea::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        // byte shifts: 24U, 0U, 8U, 16U; diffuse: DiffuseC
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aIndex]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aIndex]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aIndex]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aIndex]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aOperationLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 0, 0, 3, 1 with offsets 5783U, 2150U, 1187U, 1666U
        // byte shifts: 8U, 16U, 24U, 0U; diffuse: DiffuseC
        // write to: aWorkLaneA [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 1U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5783U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2150U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1187U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1666U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aWorkLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 2, 3, 2, 0 with offsets 4578U, 7536U, 1885U, 5650U
        // byte shifts: 8U, 24U, 16U, 0U; diffuse: DiffuseA
        // write to: aWorkLaneB [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 0U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4578U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7536U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1885U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5650U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aWorkLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 1, 2, 0, 3 with offsets 3156U, 5048U, 2443U, 6171U
        // byte shifts: 0U, 16U, 8U, 24U; diffuse: DiffuseA
        // write to: aWorkLaneC [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 3U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3156U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5048U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2443U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6171U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aWorkLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA source quarters 3, 1, 1, 2 with offsets 699U, 3255U, 7583U, 4701U
        // byte shifts: 8U, 0U, 16U, 24U; diffuse: DiffuseA
        // write to: aWorkLaneD [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 2U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 699U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3255U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7583U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4701U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aWorkLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA fragments 1, 3, 0, 2 with offsets 97U, 574U, 1373U, 845U
        // byte shifts: 8U, 0U, 16U, 24U; diffuse: DiffuseB
        // write to: aOperationLaneA [0..<W_KEY]
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 97U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 574U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1373U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 845U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aOperationLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneB fragments 0, 2, 3, 1 with offsets 1665U, 1642U, 485U, 203U
        // byte shifts: 8U, 16U, 0U, 24U; diffuse: DiffuseA
        // write to: aOperationLaneB [0..<W_KEY]
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1665U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1642U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 485U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 203U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aOperationLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneC fragments 2, 0, 3, 1 with offsets 428U, 65U, 1590U, 657U
        // byte shifts: 16U, 24U, 8U, 0U; diffuse: DiffuseA
        // write to: aOperationLaneC [0..<W_KEY]
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 428U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 65U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1590U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 657U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aOperationLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneD fragments 1, 3, 0, 2 with offsets 1707U, 129U, 991U, 1701U
        // byte shifts: 24U, 0U, 8U, 16U; diffuse: DiffuseB
        // write to: aOperationLaneD [0..<W_KEY]
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1707U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 129U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 991U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1701U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aOperationLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA, aOperationLaneB, aOperationLaneC, aOperationLaneD [0..<W_KEY]
        // offsets: 1404U, 1393U, 1565U, 1501U
        // byte shifts: 16U, 8U, 0U, 24U; diffuse: DiffuseA
        // write to: aKeyRowWriteA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1404U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1393U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1565U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1501U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aOperationLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aOperationLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
    // GKeyFoldA grow_key_a_fold (end)
}

void TwistExpander_Exercea::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 0, 1, 3, 2 with offsets 1950U, 5586U, 91U, 7116U
        // byte shifts: 24U, 16U, 0U, 8U; diffuse: DiffuseA
        // write to: aExpandLaneA [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 2U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1950U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5586U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 91U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7116U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aExpandLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 2, 3, 0, 0 with offsets 3700U, 4536U, 5119U, 4517U
        // byte shifts: 24U, 16U, 0U, 8U; diffuse: DiffuseC
        // write to: aExpandLaneB [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 0U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3700U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4536U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5119U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4517U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aExpandLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 3, 0, 1, 1 with offsets 3143U, 7132U, 7300U, 3242U
        // byte shifts: 24U, 16U, 8U, 0U; diffuse: DiffuseA
        // write to: aExpandLaneC [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 3U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 0U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 1U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3143U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7132U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7300U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3242U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aExpandLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 1, 2, 2, 3 with offsets 1014U, 363U, 7141U, 4532U
        // byte shifts: 8U, 16U, 0U, 24U; diffuse: DiffuseB
        // write to: aExpandLaneD [0..<(S_BLOCK >> 2U)]
        const std::size_t aFoldBaseA = 1U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseB = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseC = 2U * (S_BLOCK >> 2U);
        const std::size_t aFoldBaseD = 3U * (S_BLOCK >> 2U);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1014U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 363U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7141U) & ((S_BLOCK >> 2U) - 1U));
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4532U) & ((S_BLOCK >> 2U) - 1U));
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aExpandLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD [0..<(S_BLOCK >> 2U)]
        // offsets: 6608U, 1426U, 5634U, 7012U
        // byte shifts: 16U, 8U, 24U, 0U; diffuse: DiffuseC
        // write to: aOperationLaneA [0..<(S_BLOCK >> 2U)]
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK >> 2U); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 6608U) & ((S_BLOCK >> 2U) - 1U);
            const std::size_t aFoldIndexB = (aIndex + 1426U) & ((S_BLOCK >> 2U) - 1U);
            const std::size_t aFoldIndexC = (aIndex + 5634U) & ((S_BLOCK >> 2U) - 1U);
            const std::size_t aFoldIndexD = (aIndex + 7012U) & ((S_BLOCK >> 2U) - 1U);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aOperationLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 0 with offsets 1250U, 264U, 1566U, 647U
        // byte shifts: 8U, 16U, 0U, 24U; diffuse: DiffuseC
        // write to: aWorkLaneA fragment 1
        const std::size_t aReadBase = 0U * W_KEY;
        const std::size_t aWriteBase = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1250U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 264U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 1566U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 647U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 3 with offsets 1418U, 633U, 1368U, 717U
        // byte shifts: 24U, 16U, 8U, 0U; diffuse: DiffuseC
        // write to: aWorkLaneA fragment 0
        const std::size_t aReadBase = 3U * W_KEY;
        const std::size_t aWriteBase = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1418U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 633U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 1368U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 717U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 1 with offsets 597U, 753U, 1356U, 483U
        // byte shifts: 8U, 24U, 0U, 16U; diffuse: DiffuseB
        // write to: aWorkLaneA fragment 3
        const std::size_t aReadBase = 1U * W_KEY;
        const std::size_t aWriteBase = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 597U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 1356U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 483U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aOperationLaneA fragment 2 with offsets 958U, 1367U, 556U, 1121U
        // byte shifts: 8U, 24U, 16U, 0U; diffuse: DiffuseA
        // write to: aWorkLaneA fragment 2
        const std::size_t aReadBase = 2U * W_KEY;
        const std::size_t aWriteBase = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 958U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 1367U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 556U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 1121U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aOperationLaneA[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aWorkLaneA[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA fragments 3, 2, 0, 1 [0..<W_KEY]
        // offsets: 1585U, 46U, 916U, 1616U
        // byte shifts: 16U, 8U, 24U, 0U; diffuse: DiffuseC
        // write to: aKeyRowWriteB
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1585U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 46U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 916U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1616U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
    // GKeyFoldB grow_key_b_fold (end)
}

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseASalts = {
    {
        {
            0x8CC43FBCE73DE565ULL, 0x5FFB52D4D1426CD6ULL, 0x9D1199C24EA69273ULL, 0x5334248F6B8C28E4ULL, 
            0x16483750AFEC9D8CULL, 0xEB1D52B6F4C2254EULL, 0x61EDD52643094132ULL, 0x84FF725FB2CFA34AULL, 
            0xA4273BDF071BE304ULL, 0x780733623017F29FULL, 0x6DFDC9F77F7AA03DULL, 0x20ADEF7AA53DA1A7ULL, 
            0x8EB0F2C8DB71702CULL, 0x6D220CA43CA1DE6EULL, 0x5D227B338A7F4F1BULL, 0xB9A5F4F7B519427CULL, 
            0xAF4C508CF1658A44ULL, 0xB83B5979D5BF5D8DULL, 0x07FD0D9CBABE6672ULL, 0x0222F76EE1ABCC5AULL, 
            0x556AD5290D78689CULL, 0xFCA462400F5E5D6AULL, 0x3A662F0A868059AAULL, 0xA9AF49B8757F4D76ULL, 
            0x6FA691AB7E01DAF8ULL, 0x7C8D740A9A6A8A8EULL, 0xBA642C12C186AAA2ULL, 0x5B2018DE72F1A374ULL, 
            0xE912B88FBA22CB1AULL, 0x7B6790A7F0956FD5ULL, 0x6B94E6925EC33092ULL, 0x9D86DD25A5773EEFULL
        },
        {
            0xDA6065BFEBC760ECULL, 0xEF12C3318D6EE205ULL, 0xAB9E5190BB9024E3ULL, 0xD65AB6181B223B0DULL, 
            0xE9C716C16B261C78ULL, 0x8546A755314733C4ULL, 0x78B38216543DC3ADULL, 0x0B84FEF810137507ULL, 
            0x4B332BAEE0612B1BULL, 0xE119469FD13C81BFULL, 0x7837937B8538CB09ULL, 0x6ED4714431F725FAULL, 
            0xA05F59001EE2CED3ULL, 0xAE820207464F1C0FULL, 0x8BD43FE100A68C10ULL, 0x81ACE8DEE2C21D7BULL, 
            0x97D232724AFEC677ULL, 0x6A4FA3D66DA72CECULL, 0xF6100DF7DD66605CULL, 0x2735F8EB1CF35803ULL, 
            0x98DD77C508B2E347ULL, 0xEB247EE3BA3ACEC8ULL, 0x7A53F86DC801A48CULL, 0xF81CACB58D7D6B28ULL, 
            0x9D21700840FC6F55ULL, 0x8415059954C5B414ULL, 0x79F89920A951239EULL, 0x1B5771B914C7E7C1ULL, 
            0x8B5EBD43C1FCF650ULL, 0x9E48168CE541DF97ULL, 0xDB741429A487A9BFULL, 0x789780D34F34C89CULL
        },
        {
            0xE7E5958D37C24B33ULL, 0x0CAA73AF042493D0ULL, 0xCEDD1F0563C5F5ECULL, 0x5FD43928234B4912ULL, 
            0x1137DD662CEC8C34ULL, 0x5C887C4594342677ULL, 0x7B2B658CFAAF20BFULL, 0xBE977E975AB07965ULL, 
            0x259A81715CAF6132ULL, 0xA52FDE24582F2CFDULL, 0xE2193650C9B7270AULL, 0x1045E55615DF9788ULL, 
            0x6E97B07070376FF5ULL, 0x943BC7889EDC0C0BULL, 0x401DD2A531B29A29ULL, 0xDA5F836D7E47564EULL, 
            0x6E4F432A165448B9ULL, 0xB0E0D07876C1AA03ULL, 0x21A5D33B2D7AB442ULL, 0x61C05DBCECE2E437ULL, 
            0xAC432487C5E2C55AULL, 0x9F95D56E5A8ABE81ULL, 0xF356CA2EB7F65A63ULL, 0x1D17A4F754960D95ULL, 
            0x1D58B8B64ED0353AULL, 0x4565C6E7DA997BACULL, 0x16B7BC6C68570F56ULL, 0x7ADC8A2171B475BEULL, 
            0x30950905341E2CE2ULL, 0xE1E9EC43FEF95488ULL, 0x209496A0E7E12A55ULL, 0x96BCAD9001093D80ULL
        },
        {
            0xDA7679C5A01EC552ULL, 0x8936861C183AECE4ULL, 0xC9DCEC0D4ADF82DEULL, 0xC0C9A6C3567817F0ULL, 
            0xF440E4325385E765ULL, 0xFBB311C9766104A4ULL, 0x660DF31F19496961ULL, 0x0A13641F29BC0EC5ULL, 
            0xD1E56FF88747D730ULL, 0x8E9E8823ADEFDFF4ULL, 0xBC5688F993A0A3BCULL, 0x1660B4250604F0C5ULL, 
            0x9C05542F704BFCE8ULL, 0x912963A10CAF1295ULL, 0xCC8A30D8569C050AULL, 0x231536920A1DD8B6ULL, 
            0x05B9AEA5DC0BA67FULL, 0x9D9E3CC127F4888DULL, 0xBED09E466625854CULL, 0x44D94BA2FD0D1966ULL, 
            0x8A3B9D86819CB0A4ULL, 0xBF97030ACC01945DULL, 0xFE5675C7FCF4A5D6ULL, 0x73107FBFF31305C6ULL, 
            0x1B6219A36102FFBCULL, 0x1288D49096848949ULL, 0x61026FC2DFD39D36ULL, 0x4673985D00A978A0ULL, 
            0xF780349E7545FF22ULL, 0x51B4D592119A1D93ULL, 0x28B218A4D3A7DE7AULL, 0x728C186D2AD6A6E7ULL
        },
        {
            0x40D4AB2E5AF7B92DULL, 0x63EDBB96CA0D397BULL, 0xDD13D9B26CFB6085ULL, 0x9F9524971B82CAFFULL, 
            0xE66E6852A0350CCEULL, 0xD21500BBD24E023FULL, 0xF9BAF2473F0F3801ULL, 0x33F45F1707AEAA3CULL, 
            0x8F53EE235DAB97FBULL, 0xC77B5023F2B4278BULL, 0x8E8E590746387AD7ULL, 0x3440F9EDD485A7B4ULL, 
            0x98CD7F8E396F35ABULL, 0x63852F8D06CE2219ULL, 0x1E2A4BD216C0AAA3ULL, 0x691853E41F08291AULL, 
            0x9DA54F67E5DF949DULL, 0x8C79C0779DD86021ULL, 0x1D2D9A1F2D9687C6ULL, 0x0EEBD0F93659957BULL, 
            0x534F9F2789DD1446ULL, 0x029FEB9DA6E2A0C8ULL, 0x2E44E92DE716D53FULL, 0x694726E74F93538CULL, 
            0x5863E24839FE5DE7ULL, 0x7EAAC9C4FA06767FULL, 0xFCBFE372BF144C79ULL, 0xFE911260BFD48C2CULL, 
            0x764F5C3ABCED476CULL, 0x44F226A0E39FA42EULL, 0xEA7D6DC588098814ULL, 0xAD6A90B9BE1C7DF0ULL
        },
        {
            0x91B1FC85B479BD6BULL, 0xCAFCAD1CD69EE817ULL, 0xBB31CD3D95870433ULL, 0x56C7D74739A9E5B8ULL, 
            0xB105AE5CA5939FA7ULL, 0x6BE5F5F1A44820A2ULL, 0xB27F01E3278D2FF9ULL, 0x1C166EBA63704EF4ULL, 
            0x429C3D85CB0C8884ULL, 0xEB62618B32FC986CULL, 0x482F738C8CF9B1D4ULL, 0x4629F80C5324D818ULL, 
            0xE8A81DB697B75746ULL, 0xD87CC31104F9485DULL, 0x799AB0A3CA0A2FEAULL, 0xE1730032131142A2ULL, 
            0xABBF644F9608AC8AULL, 0xAB543DC24F67F0BAULL, 0x608DEDB9F3B0AD68ULL, 0xA1929EBFD0BD202EULL, 
            0xD5EC961726A046A6ULL, 0xB958CB0486C63A71ULL, 0xDE721F1C4DEF460AULL, 0x8342B01877935065ULL, 
            0xADA651153CD63529ULL, 0x8116E00DAB7991EAULL, 0x00097D46879459BFULL, 0x84B32D01783A22BBULL, 
            0x114B49CF574A8DAFULL, 0x0E345CFE8259530DULL, 0x73627539C76F4056ULL, 0x1894E1040394A29BULL
        }
    },
    {
        {
            0xB37FA8090CA5B420ULL, 0xC4D7BCF16B118229ULL, 0x0CE6F87098635766ULL, 0x0BD2FAEA4AF277E7ULL, 
            0x5DE4BC2890A5140EULL, 0x238AF415874B21E0ULL, 0x08907C78A28CC689ULL, 0x5B6A1242877C3721ULL, 
            0x9B091E5B84E8DAF4ULL, 0xE007C6BFF3D9B66FULL, 0x04F8D4398A017C44ULL, 0x8F5E3E86ACA69C07ULL, 
            0xF124ED14D0DC937CULL, 0x1F8B95AE1717F319ULL, 0xD6D722B6F95A67DDULL, 0xA9B9072E6C7303B4ULL, 
            0xADA9ADA43CC81821ULL, 0xF43084FFB349541FULL, 0x02E7CE36764689A1ULL, 0xD1AD52384932FFF6ULL, 
            0x2E52AE3FE0AF63CDULL, 0xC598790EF4F5554BULL, 0x619EC6D197FF925FULL, 0x80F72795CF3E0D90ULL, 
            0x54B0390BF6F1960EULL, 0x0BD913BD12C0C358ULL, 0x5E9B9F92E40C748BULL, 0xCBFD01009A31569AULL, 
            0xF31672FE4D038862ULL, 0x9EB03DE82ACEF586ULL, 0x926F7E2F39EA8BC8ULL, 0x9FA1D6F7D625E535ULL
        },
        {
            0xFE04898025A7B7B2ULL, 0x95480DD3C7B60A48ULL, 0x7DD98A3736D071B0ULL, 0xD13C70710DE01CF7ULL, 
            0x05B70A64EDDECD91ULL, 0xFBD2306EFCED8A8AULL, 0x036B251F4D5D3A19ULL, 0xBC2771B347A98B5DULL, 
            0x5BAB8BC0141156FFULL, 0x9B5499D5FA960A17ULL, 0x130298F2BBA91390ULL, 0x339F800EC9F08AEDULL, 
            0xF06A71FA45AEEE79ULL, 0x2CD90BCEB9347D45ULL, 0xB4571813E504F705ULL, 0xE917D22B5B0A2D8BULL, 
            0x2835712AD1C5B704ULL, 0x3809A3CDC3E0AE44ULL, 0x7B66A798C38F1B54ULL, 0xFEE6A9D8ECC18273ULL, 
            0x0CAAC1972D99CF69ULL, 0x65DDCE6E6F428392ULL, 0x9C24E1E223D141B4ULL, 0x19A4D178FA024A93ULL, 
            0xBC95D81C15D7473DULL, 0x6B6828E16D0F425CULL, 0x6B385AC5F005E7E7ULL, 0x177FF1F4B04DFE63ULL, 
            0x95E4EDA798277B6BULL, 0x6C0202E7CA14AA48ULL, 0xDFA1A9A4DB73353CULL, 0x118BBDDA25B5B547ULL
        },
        {
            0x13F45CC45C2D7BE9ULL, 0xC018A2E20773E3EFULL, 0x363ACACAD69503C6ULL, 0x522CC89FB1D75DECULL, 
            0xE8A29282A2E2BA37ULL, 0x0E308B75430DFA3AULL, 0x47F0F7C8469E50FFULL, 0x1A45CD17F236DB08ULL, 
            0xE280AA0267BC7511ULL, 0x9802846845F796C9ULL, 0xC0CCB8E7C6EFF172ULL, 0x2F22C614F669B301ULL, 
            0x93AD15CC44C25D5FULL, 0x1A43B1A45D9C5875ULL, 0xE259F8B1ECFA7CBEULL, 0x50C4B35148355B22ULL, 
            0x5CBAF34E63B562CBULL, 0x89F6A304C46A4738ULL, 0x03FE76D1B2583A3FULL, 0x27EAFCD4433D33A4ULL, 
            0x054E230BE52E13D2ULL, 0x1F273AE9894076B9ULL, 0xF580230A4A96991AULL, 0x0DBB26F2D3F2220CULL, 
            0x31B7587CD6CD4FF4ULL, 0x7588DEF1BCD014E3ULL, 0xD02F7ED0CFAF5748ULL, 0xC404EBF213B424E4ULL, 
            0xA2A7967BBF530D15ULL, 0x20F3D68CEED65D21ULL, 0x48420D4D31B27A18ULL, 0x49C203201A6C39E6ULL
        },
        {
            0xC01F139F3A0272AFULL, 0xD08623BD690F0F70ULL, 0x14D9308382ADEF76ULL, 0xDFCE83F22208C7B8ULL, 
            0x5C6C1F77C8D161A6ULL, 0x1F123CFA9DD6B50DULL, 0xF5C546B6BC9F78EDULL, 0x85DFF6138E154F3CULL, 
            0xAD4A5DAD280B820AULL, 0x901190D3004A2CB9ULL, 0xAF3E716DFAFCEB0FULL, 0xC883FB33E3FCD558ULL, 
            0x25FF3FAD6B0CB02FULL, 0x61D50D1225FE387FULL, 0xE7B54EC8D7817C11ULL, 0xBB54E3E60062F5E4ULL, 
            0x4D08F44586E3905DULL, 0xA5E2DAA824315291ULL, 0x2CC9B03CF38C6FF6ULL, 0x89472DB315DA26CFULL, 
            0xAF818B2D66CF3C93ULL, 0x20E5B7DC11EB970DULL, 0x319554E32BB448EDULL, 0x80AD0674066DB796ULL, 
            0xB00313C9528F10C4ULL, 0xCD4160989D78B0BDULL, 0x8FA8277E54D2BC35ULL, 0x4840E34717609432ULL, 
            0xE4E92FEC70027289ULL, 0x6B577EA3580B98E2ULL, 0x0002C3460253C53CULL, 0x48C014F674DCBA0EULL
        },
        {
            0xD0E0939DCA8BB53AULL, 0xBFB667228CF5EC1CULL, 0x629364ED889E510AULL, 0xAB1651EF470484AAULL, 
            0x1C2CCE5D0A32FBB1ULL, 0xEA9685C8B72C0C66ULL, 0x603F47A0589F5480ULL, 0x1B7165C071441C38ULL, 
            0x7FABF248CFD9E83DULL, 0x4B78400AB5FCEACFULL, 0xEB55BE5908F9ED5DULL, 0xF1A298FA75F8791EULL, 
            0x703B7722C87E8FF1ULL, 0x9AF0B4B8BD977789ULL, 0xE32CE673DC8FAC79ULL, 0xA655B012692D3867ULL, 
            0xA19324EF71761787ULL, 0x5FBB23958327AFB8ULL, 0x2755258636C0C779ULL, 0x6811DA73A9A92E7EULL, 
            0x5D907A52B2D0B273ULL, 0x585C065A0D4304DEULL, 0x2223A84704CC2D84ULL, 0x7C020E72E116A57BULL, 
            0x3040CB330CBE4DF7ULL, 0xF3309ABA8DD86827ULL, 0xBEBFEB225A2A7939ULL, 0xFA6F3333EBFE671CULL, 
            0xA5B31BC839A4C0F5ULL, 0x5D349786A1EEA63BULL, 0x80C05B2338122F2EULL, 0xD8F6EBF056415A8AULL
        },
        {
            0xB3D74D0BD99B3A6DULL, 0x42B5871D4351EBD7ULL, 0x9F545EDD3B886F57ULL, 0x3C9B12F502624165ULL, 
            0xD25BA8314C771AEAULL, 0x45E83237ED58AF10ULL, 0xEC933EA89B6F7642ULL, 0x339D7EFAC7992797ULL, 
            0x5229CE40B657277BULL, 0x8D19C801C7A9EA41ULL, 0xFE59F924AF6CD8EAULL, 0xC33D0B51AC787B14ULL, 
            0x33DBAB12375226F7ULL, 0xA1842F1B427FB5FEULL, 0xD33578B2B922EA5DULL, 0x1E04539F55BAE39FULL, 
            0x618303D05E38F106ULL, 0xF5A9846C17957971ULL, 0xA711B5BBDF712180ULL, 0x29DA756EF8B7522DULL, 
            0x6514634AEF5D3C56ULL, 0x571CB3498CDC65E2ULL, 0xC96DC4809EA1F983ULL, 0x18052F6E3C8DAF62ULL, 
            0x3932DC858A430674ULL, 0x5D1C9DF3FE4D279CULL, 0x39D58307A1BDE824ULL, 0x7EF7650D0C8D28CCULL, 
            0x3004F7F3D9293D17ULL, 0xBF5D5B373E3FC0BBULL, 0xF73FCDB2128B25A0ULL, 0x06CDA81BC98FD3D2ULL
        }
    },
    {
        {
            0xE1227233499FD1AFULL, 0x4CFD704A5217EC55ULL, 0x07E6F08229146257ULL, 0xB3733A7AF9939722ULL, 
            0x739DEDBDC0C5D5CFULL, 0x5311C5700574E0D8ULL, 0xEC5EA70EFF757208ULL, 0x402595B01D89BC61ULL, 
            0x761E84F497203F9BULL, 0x959A84D5219AB19CULL, 0xDA43A9ECDB9F64EBULL, 0xCA81F928BAA1BFC5ULL, 
            0x0F8AFE45592E84BBULL, 0x33A1ED156DB6B01EULL, 0xD4EC998CCB6EE857ULL, 0x3AA38DBA56C20830ULL, 
            0xF71F26AED8A3EB45ULL, 0x749785D5396DC38CULL, 0xF48EA1A213CE2741ULL, 0x8844CC21C77C8650ULL, 
            0xA65F9958C3B2DEFBULL, 0x707FA489D9695830ULL, 0xD462FB2772FB4940ULL, 0x757164A696259AE5ULL, 
            0x5F8479C7FA2742FDULL, 0xB3BA8F902E2862EBULL, 0xE35C9621A6F9D232ULL, 0xC087D2749C5AE69DULL, 
            0x978599788B2C648BULL, 0x0B06C11B192C8E73ULL, 0x7EE6567F3A2E3FB1ULL, 0xD052CE7A90F796DFULL
        },
        {
            0xD67EC0B6BF6C039DULL, 0x3D3B09A068F22B67ULL, 0xD43D308D5C4D93A5ULL, 0xC10AC048FF27A61AULL, 
            0x4D7B00D8187288CAULL, 0x327E8B2E313EF462ULL, 0xDEA6E2969A2F9AAEULL, 0xE9FB9F311EAD6FF0ULL, 
            0x3B5BAB5F2885F96EULL, 0x7A32B3221CA1F3EFULL, 0xAE94AE90F5A118BFULL, 0xE17DBF9F289BC910ULL, 
            0x2D13E7F080B060F7ULL, 0xCF0E3B36DA9FCC75ULL, 0xDE6681B5780179D4ULL, 0x8A43D7CF17EF08A1ULL, 
            0x643A1F2DF65E10E7ULL, 0xA25413B866211E9CULL, 0x166727869D17C0B5ULL, 0x1779C219479C1BF0ULL, 
            0x52918B24FD73BEDAULL, 0x38E514DAC419E329ULL, 0x1832627E1284037DULL, 0x79D8B12EF73F6899ULL, 
            0xAD5ABDAC9B73C461ULL, 0x5D2837C470F14BECULL, 0x8146201C77D3C674ULL, 0x0C14F9AE0685BBA9ULL, 
            0xD09A54803A1AA8C6ULL, 0x3690C9C868D4B50AULL, 0x605A0750325CE2B9ULL, 0x39FBB5678C0FA93FULL
        },
        {
            0x20C1784B84873F4DULL, 0x4C472AF8255AF079ULL, 0x16E261A975E69EFAULL, 0x41C77A7776816496ULL, 
            0x0E0FC4EBC1FCBC52ULL, 0x904260D317868FCAULL, 0x6A4ECBDCD0130EB8ULL, 0x28A303A3C64954FBULL, 
            0x8FF34A35101B04C5ULL, 0xF3311E05B8A1F444ULL, 0xCFFF947D7BFB0521ULL, 0xBE333AAD26B943DAULL, 
            0x5CD5B15B12F537E7ULL, 0xE81D12747DB869DCULL, 0xE8E920A1CB565718ULL, 0x171EB9CD515150FDULL, 
            0x7CEF470EF8D5894BULL, 0x08AD14A3F93B6A93ULL, 0xA78603224FC8C006ULL, 0xE5DD8F71A02CA537ULL, 
            0xC1C29487FC9DD295ULL, 0xCF4BCD2CA1C044EAULL, 0x66BD7C18952E993AULL, 0xA07BA09FC426AE5AULL, 
            0x5E20078544214C9EULL, 0x7AC3CEFA296F3DB8ULL, 0x441707C25ACABB2BULL, 0xA2A0C31B0CC2F445ULL, 
            0x1EF23D228D9B6315ULL, 0xD8462B64F0F46632ULL, 0xE93DFC2287171528ULL, 0x65817A3185F41430ULL
        },
        {
            0xDDD8FFC385513390ULL, 0xC334BA044E9CAD29ULL, 0xABAE68BB7DEA6956ULL, 0xE247B1A9F33BED42ULL, 
            0xD1AB7744D19CFA1CULL, 0x5CBEE5A5EE2ABB5DULL, 0x1FB82776F9F4B447ULL, 0xAB495A50A805E277ULL, 
            0x0291BF6248A5E5E1ULL, 0xC4F6FB249F330537ULL, 0x895FEBF72A786AF2ULL, 0x14006009BE8E3E4BULL, 
            0x4762162935B318C8ULL, 0x05C0DE13E8E00F9BULL, 0x760442803655A82DULL, 0x1D3D4BD1A138E60FULL, 
            0xBDC00FEB3BE2CC77ULL, 0xCEA9006EC3607CB6ULL, 0xC340CD8F4C623193ULL, 0x28C518C8CFDC8DCCULL, 
            0xE7D168B3714A61ECULL, 0xC72CDF967527792FULL, 0x44A8B512CD3AF15BULL, 0xAA8C2A3874A57A92ULL, 
            0x8E22704D6CA37119ULL, 0xD6765153246D35AAULL, 0xBC644392E4D650FCULL, 0xB433A54D343110B4ULL, 
            0x233CAE2A6F4F1064ULL, 0x2911A1DD4539A8CFULL, 0x10D9BE8FFDC57F07ULL, 0x80A42F545285211CULL
        },
        {
            0x0848C0751B51AF16ULL, 0xD62D4BD4C01E883BULL, 0x0E1F14171C5FA1F0ULL, 0x4F7F568318685F67ULL, 
            0x9709B11D139478EEULL, 0x354B210FBDA6B764ULL, 0xFCA4B7EF61EE2DA2ULL, 0x6816710689EF2E16ULL, 
            0xB6DE345D45896ADBULL, 0xC968332DEAAA93BEULL, 0x7858C48933270467ULL, 0x63384D08C26FAE5CULL, 
            0xAE588680A982AB9BULL, 0xD520F2097F95926BULL, 0xF368AEDBD35E88AEULL, 0xCFF2B78C9E5376C1ULL, 
            0x4DB0D6C0EC320624ULL, 0x1924C1ECEC9D64CFULL, 0x82EFFCA2C006DD79ULL, 0xBF8118FE2FBA0933ULL, 
            0xED39A2CB601768D8ULL, 0xC5BAF83D808D8A85ULL, 0x7F6171721B8EB686ULL, 0xC9E678CB1925AB0EULL, 
            0x5CFF62129BB5C104ULL, 0x50E7AF7140DD9FF9ULL, 0x084A37685281045BULL, 0x0E35E3DCE1346676ULL, 
            0xEBBF66FB4790B299ULL, 0x39AC18FFFC3BDE23ULL, 0x5741DC6B44F026BCULL, 0xDD75DC85A45B29AAULL
        },
        {
            0x04463C22C28F4466ULL, 0x140A6DA80FE0B050ULL, 0x098E546535EFFC65ULL, 0x3BAC0581186A79D1ULL, 
            0x963974772B4A2950ULL, 0x42DD8A74838A16AFULL, 0x453F9970A71F36DEULL, 0x149356044C0D8027ULL, 
            0x8E7CE42F14AE6B08ULL, 0xC6235AF4E958D5EFULL, 0x3E09A66B35569AC7ULL, 0x238378E184438976ULL, 
            0x9B7E93497A00CAD9ULL, 0x1DD712388EF84F5FULL, 0x99FA78F82B8A4C6AULL, 0x0D51414A87352CF9ULL, 
            0x70AAD49D33DA94F9ULL, 0x103E929B2921BEC3ULL, 0x27303563D0E2FC40ULL, 0x2FDB25A35EB15147ULL, 
            0x19937DB0B9F14771ULL, 0xFED608C62DD27A95ULL, 0x3D0D620C04EF425FULL, 0x3695166EF29E1D06ULL, 
            0x52BBD1A3F03DE760ULL, 0xA27C48278EDDBDF2ULL, 0x5CBDCD858EF4B8FCULL, 0x274628F181E741B5ULL, 
            0xBC21F26661EB793FULL, 0x22A06103172A4BB5ULL, 0x11DFDB482425D0CFULL, 0x4A8708EA863746F1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseAConstants = {
    0xE63CD4ABF6108951ULL,
    0x779797F01E5EE17FULL,
    0x19D726A1401A7FBEULL,
    0xE63CD4ABF6108951ULL,
    0x779797F01E5EE17FULL,
    0x19D726A1401A7FBEULL,
    0x2066C37D3776F3ECULL,
    0x37A1F16E15291EE1ULL,
    0x09,
    0x75,
    0xD9,
    0x2C,
    0x27,
    0x61,
    0xBE,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseBSalts = {
    {
        {
            0x1E21DB8BE7E0FF94ULL, 0x5059EDD9E6AA7A37ULL, 0xA424924675E8B96DULL, 0xA19676FB5CD5317CULL, 
            0x1DD8E2378B006085ULL, 0x72B08D0E5AAA7D3EULL, 0x8A7780B5337D78B6ULL, 0x8D37670B52BD366BULL, 
            0xB9A6EE7FE1BACA89ULL, 0x0BE1F4D0F2FA249CULL, 0x76F30D8249C161C4ULL, 0xC6DD06EE51172A90ULL, 
            0x769CDB784B98D887ULL, 0x1AD50E57370254EAULL, 0x2DC7B46FB7109A8DULL, 0xB5805C0DB6874B13ULL, 
            0x4CA42772C3830568ULL, 0x72BCB35BA88B259BULL, 0xAF23E7E50557593AULL, 0xFD13AB76730464FAULL, 
            0x389CAFA11297ACDCULL, 0x850FE6E2D88D00A5ULL, 0xDD1451F625E7DEBAULL, 0x8B96F39A48459572ULL, 
            0xAF811779FD63E6D5ULL, 0x98234743E86FDC7FULL, 0xED276EA1D6B57934ULL, 0xF1D8B83C6237FB8CULL, 
            0xA8A308E8F9806EBFULL, 0x561F629307E1F5F5ULL, 0xF10EF49F3D7A4D64ULL, 0x452176615FFBC43BULL
        },
        {
            0x3409733BF21D5A79ULL, 0xADD8B25F107091C0ULL, 0xEBBB624574956CE4ULL, 0x0901F51AE7F88B7AULL, 
            0x923FAA719D3BDF13ULL, 0x87C9C02BB03CFD14ULL, 0xA5812070AC74631CULL, 0x52AFC7CE7FEE0F32ULL, 
            0x06390227D8B88CD7ULL, 0x03BF535D5838609DULL, 0x9DA52B6F0D30D0BCULL, 0x283AA83A32DB0CF6ULL, 
            0x660CE77087E584CCULL, 0xA99120ADD9EDABE7ULL, 0xCC453A803D45D53BULL, 0xAAD1CD7D59624CE1ULL, 
            0xFCE615C7589E2F67ULL, 0x70A51E49714F4228ULL, 0xC51DE9EF1F491C9FULL, 0xF51EF916228951C6ULL, 
            0x6884FDC8C9B462F6ULL, 0xD16D696B58C30707ULL, 0x79DD8C53865284EEULL, 0x7A421D06F0BB67ABULL, 
            0x1BC9450204C060D5ULL, 0x6E12F28417227907ULL, 0x899E00F92F90CD04ULL, 0xA28437F63E5D26E9ULL, 
            0x70A6A5A0D99B363DULL, 0x300D56C7DC576BE3ULL, 0x0E460491B68315D4ULL, 0x58078D2BCAA31028ULL
        },
        {
            0x82646C98001FA7C6ULL, 0x08CC369054B1ACB5ULL, 0xEC42B69B2B47766EULL, 0xBCF26CCBAE992086ULL, 
            0x6886D19F52EC70D8ULL, 0x913C6122C2E64EEEULL, 0x94EFA7B968BDFBDCULL, 0x60ECB65EDB4A9303ULL, 
            0xE590C9F17D0CC059ULL, 0x08B41824967B1E3BULL, 0x4D989244253FD806ULL, 0xE4786AD24B743B16ULL, 
            0x29E44C8B8260F042ULL, 0x0B178CBD99D81720ULL, 0x9D1DB44F8EE849F0ULL, 0xDE52922036A66A16ULL, 
            0x9D1E09C7E15CA845ULL, 0x2326D64EF1C2D22AULL, 0x2BD0C46AC2868082ULL, 0x4E21725E295C4ED0ULL, 
            0x753198A21E40A0A6ULL, 0xD6122ED0AEECA987ULL, 0x325382F5180F2360ULL, 0x79C3B4CEFC137D8DULL, 
            0x9F887BA1E4AD2172ULL, 0xA3823847562FA293ULL, 0xA5C42AF542067D20ULL, 0xE61E7B2B49065D7FULL, 
            0xE1CCB32F8EA33E63ULL, 0x218C203DCBC2B895ULL, 0x2B5F5A8A26CADAACULL, 0x6320198926DAEC5DULL
        },
        {
            0xD13A912E4D951EBAULL, 0xE2F7DF5C6FC007A0ULL, 0x463D517279E8093CULL, 0xA8CF82E8E1D96BACULL, 
            0xA91FA04F2C5E44EBULL, 0xBFCC328CBDBFBAE4ULL, 0xF1344092BFD279E1ULL, 0xFF2762F36D2F5B77ULL, 
            0xBF93B13D40552A2DULL, 0x4C714FDA4573838FULL, 0xFF8EDFF38DA3E41DULL, 0x463AB2997949225CULL, 
            0xD4206D3165F4CC15ULL, 0x54D14C070B2B5025ULL, 0x445F5EFA8F231154ULL, 0xED04150FFF2320DAULL, 
            0xE846858DB56D2914ULL, 0xEFE2D187509F68ABULL, 0xFFACF0702F277845ULL, 0x903B405189AB442FULL, 
            0xD917C96F0941CE63ULL, 0x8AE057E890ACD5E6ULL, 0x3C39275869960879ULL, 0x5FCACE2AD7CD3362ULL, 
            0x3C898A536A0FDD50ULL, 0xCF345A512884B6E2ULL, 0x381E34B9E6DFB680ULL, 0x56BA6A4C958D361BULL, 
            0x4B221760B60BCF9AULL, 0x7B48BA830BA48CC3ULL, 0x6F8624EBE8EFFE43ULL, 0x04F80CCCB474708FULL
        },
        {
            0x68C10244B7B01983ULL, 0x5F068627FA07E1E1ULL, 0xAB7D988FE4F2F72FULL, 0x3A3FE1A663D8C4E4ULL, 
            0xB3BBFF1A5C76F806ULL, 0xBC5414284C376753ULL, 0x0A9E123B3BFC4CB8ULL, 0xD4D02021ECB73865ULL, 
            0xE9A26AE9FFE95ABBULL, 0x26146BF0532CCF03ULL, 0x24CC7576D798E690ULL, 0xDD32E3D6DD117CF7ULL, 
            0x95A749AC248A8748ULL, 0x463FD4F82431E697ULL, 0x62CF2C75E4C9290EULL, 0xCFB6016999BD3657ULL, 
            0x7F34230C3D3AF688ULL, 0x11AB810607154079ULL, 0xABF6604E6C1BB501ULL, 0x4B1C5F7CAE19C606ULL, 
            0xCEA1686DB9666D14ULL, 0x1D1F952DCA6436E7ULL, 0x7DF414AA9524D789ULL, 0x2AB801EF4808F11FULL, 
            0xFB41C564E6E36C07ULL, 0x8425DCFF6CAC8010ULL, 0xD274B1154A533B6FULL, 0x9DE2E46958ECABDAULL, 
            0x1DA2C85F0B6BADA5ULL, 0xCB20401397C9ECCAULL, 0x6AD7A310ED94FE85ULL, 0x80223CEDD34D2E39ULL
        },
        {
            0x4E2A134D429D98E4ULL, 0x42A1E8DD7D95D8E3ULL, 0x83D945819C298959ULL, 0x0CB737E8D47D08ACULL, 
            0x5DDF4A97AEB6BBA4ULL, 0xBC04FA7E11050141ULL, 0x459D91B8FC6B1DC8ULL, 0x91520C45EEF35594ULL, 
            0x2697E21A8D08E3B1ULL, 0xEF9379357B9CC930ULL, 0x930737F84C7FE405ULL, 0xC4D1A4C1B56113C7ULL, 
            0x382BF70865313423ULL, 0xCF63A1FF52F57999ULL, 0xCEED41215DA706F9ULL, 0x3F5DAF729EF60814ULL, 
            0xD969624F7064EA96ULL, 0x2F6D7858E06810BCULL, 0xC3978A10DF85CFBCULL, 0x6C6F141E8B3B2D57ULL, 
            0x4079A1059961F861ULL, 0xFD4F4EAACAFE8302ULL, 0x1330749AF7A35E8AULL, 0x21ADA2A95D04F2CAULL, 
            0x507732B2D79F3B5FULL, 0x0793A99B1244A2A8ULL, 0xBD0C67218B9C3182ULL, 0xCF4BA0AD8C1CA2BEULL, 
            0x564EFD9A4F0B2AF4ULL, 0x2DAD422A8F0F92E1ULL, 0x9428D4722DDF75EAULL, 0x72A96B326FB4997AULL
        }
    },
    {
        {
            0xA15359698207EA4DULL, 0x24345B85DC672B88ULL, 0x6ACF533AD13BDB6BULL, 0xFB38CB15B80840E9ULL, 
            0xACBCB6146CAAEB95ULL, 0x967CE31ADBC62D9AULL, 0x49DCC7A11289CD68ULL, 0xDF48489C6237B9F5ULL, 
            0xDACE6F0DEA543DC1ULL, 0xB848AEF4B9F8AF58ULL, 0xB873D54778822948ULL, 0xE9B7EC1DB0DEB1C3ULL, 
            0x88456D46F77E7756ULL, 0xE5A2D03198F75C8FULL, 0x0F13B1459B2A1451ULL, 0x7E2946C3C7063603ULL, 
            0xFC6A8FA1BB40C097ULL, 0x393B00866C5E5DE0ULL, 0xC9048C95A012CF8BULL, 0x34F08DADE1BD4581ULL, 
            0xA00C656EFB3C68C1ULL, 0x0FF92714C4EE7147ULL, 0xF06311DB11E991F4ULL, 0x1188BD7C3AE4514BULL, 
            0x60744E170096D0F0ULL, 0x36D7DBB52DC3952EULL, 0xBB20E560E4C000C4ULL, 0x8FC25DBA9D214328ULL, 
            0x8ACFB883B3DE7682ULL, 0x3A4855736F350F21ULL, 0xF3879546A8004648ULL, 0x58D68CEB0B7E190BULL
        },
        {
            0x71722724C7920E08ULL, 0xAD8B74DB1D15E678ULL, 0x24566A4AAC98B044ULL, 0x7A4F0E82260CBADFULL, 
            0x9CDA9CA799D5C983ULL, 0x14E5398F6DB62B52ULL, 0x361A402F5FFAA865ULL, 0x7D27738A4638D225ULL, 
            0xEA468679A320B9ABULL, 0x7F416C6630725E7BULL, 0x3399214C3C143C0CULL, 0x7D65CE0679224A3BULL, 
            0xFD4CA8B40678988CULL, 0xD032C5248F35FFC3ULL, 0xFE10F63C0961E855ULL, 0xFEC2EC478209F50DULL, 
            0xCE44A245E3FCDA58ULL, 0xB898CCAC5C663401ULL, 0x1B3A88188C1FB80FULL, 0x849A32C483493CB6ULL, 
            0x9DEC8FCA8FB35C97ULL, 0xC8616A211C8CB647ULL, 0x30E02CC7638FFEDBULL, 0x7E77959C00E1A332ULL, 
            0x289B6F6452BF864AULL, 0x300CEB4D5E02A0FEULL, 0xBB58D3008A3756EBULL, 0x3C1937981F75BDCAULL, 
            0xDFDB5D2E2B72C7FBULL, 0xC37F3BFCB57A7771ULL, 0x53606445B23615BEULL, 0x5407CAC7504AE751ULL
        },
        {
            0xA1EC99ED2EBCA87CULL, 0xD3DC94EF8A2B603FULL, 0x145B2C80CC59CD6DULL, 0x1C553226F410462CULL, 
            0x3CF9F1FAC6EF8489ULL, 0x9C9333C4AAF9A780ULL, 0xF4D1551183DFFB6CULL, 0x057492B684EE7ADCULL, 
            0x277B3780B6FD4AEAULL, 0xE4CD509BA7F1EAC2ULL, 0xA0FF2EF629EA3089ULL, 0x2E2549F2483BA595ULL, 
            0x98BA2D68B8EA0A11ULL, 0x09252F9D92FE86EEULL, 0xEA668A71A21009F5ULL, 0xCC65589D2AECA86DULL, 
            0x7B933E1CA36B4D10ULL, 0xCA43DEAE1E0358FAULL, 0xCD29BA5BAC095F96ULL, 0x49D1EB7ECB8A7104ULL, 
            0x3807ED52A4CC1D44ULL, 0x4141A6F3CDEF223CULL, 0x064EA5CC72965049ULL, 0xF719E220633E4E2AULL, 
            0x7782546908A6CA77ULL, 0x23A0951E5E9DA4EFULL, 0x202AE9D9C7FD7F44ULL, 0x16DDAE99798B1331ULL, 
            0xC8178DE938236AF4ULL, 0x86EBB2D981A9F47CULL, 0x0958F6E6FB2CEC2BULL, 0xE4455098829EBBFBULL
        },
        {
            0x75B710E89A5A122BULL, 0x536C531F44184BA6ULL, 0xCF45B170E232C006ULL, 0x2BA08D25B8EF69F2ULL, 
            0x99451D32587DA2AEULL, 0x5366FA1BBAADDCD9ULL, 0xAC22926E3D69E9C0ULL, 0xF77BA2F0280E0E68ULL, 
            0x9BE0F314B48BAC20ULL, 0x3572BD15F74454D2ULL, 0xAEB295260E5CC2BFULL, 0x8D9E37882788F056ULL, 
            0xC278991161276F7AULL, 0x05963B9AAF612142ULL, 0x593EEEC417F5F912ULL, 0x4D6EB57BED3819D8ULL, 
            0xAABE6AE7CB1F38C7ULL, 0x88DFED1BA4781BC9ULL, 0xDF365D620A1401A8ULL, 0xF5C2D059B2F1E2B7ULL, 
            0x87DDCCEF93F6B248ULL, 0x0EF5ED6CC5A225E9ULL, 0x89DE3806ABAA94ABULL, 0xC7867F6B8C4F3451ULL, 
            0x13F17F119458E82AULL, 0x74459C117F62EF81ULL, 0x40A273F5AC1B176DULL, 0x62D36AD9AF7308CFULL, 
            0x775A71E0A05ECE57ULL, 0x195BBB7C0AA2391DULL, 0x70D188C3D1E290B2ULL, 0xA81D720721912398ULL
        },
        {
            0xF6E9033D5D258BB7ULL, 0xCAC1F2D91873645AULL, 0xF992810232760A0CULL, 0x57DD583C3707A48EULL, 
            0x51E68B00D89005A8ULL, 0x9B0597F7F0AD9144ULL, 0x1208020BD7AA49A3ULL, 0x603BCE8CCEF6220DULL, 
            0xEFBC5685C69710A5ULL, 0x2169480E83867D77ULL, 0x6370692B44D65B5DULL, 0xFCCE0E894FFE70E4ULL, 
            0xF288402DBE65B55DULL, 0xC0EF37A54CA6A25CULL, 0x8428F4A35FA8F2FCULL, 0x1BBE67A8608829A6ULL, 
            0x2EF01DA3ECF80D17ULL, 0xA013E2C26C52570DULL, 0x5B546D633111EC89ULL, 0x42E11EFDB46EF50AULL, 
            0x7DCB591ACE873375ULL, 0x039C7BEC33329FE6ULL, 0x82E5842684514DFBULL, 0xA10DCD88881E29BEULL, 
            0xE84E2612A046D07EULL, 0x6A4A9E8676270C8DULL, 0xE958E05C2648AA37ULL, 0xFB1CA15D2429E635ULL, 
            0x3136FB12CF669459ULL, 0x740F0DFA5D580BB7ULL, 0xAA9A05756AF22C97ULL, 0xA7889BE6E494D519ULL
        },
        {
            0x7C7AEE8FE9100678ULL, 0x14B38C9BAB9CAF48ULL, 0x201F9E47A8B005CEULL, 0x7E5F25773325CE0DULL, 
            0x4577DE40BB96152EULL, 0x06A84C0CC5CE1CD6ULL, 0x2731D55DCE2509E9ULL, 0x448DFFFCFC9DDD66ULL, 
            0xDBE56190882FCDB7ULL, 0xF97AC8659C6F88B3ULL, 0x8DF803904C38647BULL, 0x7D752B08B114B0AEULL, 
            0xFE0B183D37F66242ULL, 0x3A18C81CBB99391EULL, 0x8BC7419A364A989DULL, 0x567AEB46F70385B3ULL, 
            0xD28887B87B1FDE69ULL, 0x7053A1424B127F43ULL, 0x8D845246823A463BULL, 0x6E4F848F8D18ACEBULL, 
            0xF78ACED8466D162AULL, 0xBF553A66245834D1ULL, 0x9405DB3755D8B8EFULL, 0xD36D234D346C9C17ULL, 
            0x98D6CB801592C952ULL, 0xE7509D969516B91BULL, 0x8203AA06284993C2ULL, 0xD1F53CFE337D42AFULL, 
            0x7F590F6451D69754ULL, 0x04E3A647CD064C14ULL, 0x9C8DC75AD5A28B92ULL, 0x45E9E25CE64ACD53ULL
        }
    },
    {
        {
            0xCEBAA59CD05FDC3EULL, 0x8E8D9F314D3CBB67ULL, 0xD6CEF8C4EE1588B6ULL, 0xA5171C9B20BADFCEULL, 
            0x285CBD6B365B57B2ULL, 0x8223D172FB208ECBULL, 0x33F1D756A690D099ULL, 0x773D416B79DA3FF3ULL, 
            0xF8D7311788A6F973ULL, 0xB62016106BA622F0ULL, 0x9A5EE923A44F71B0ULL, 0xBC6F1C1A93D43CBEULL, 
            0xCC4A9278E6A8A6FFULL, 0xFE2F94B2243567ADULL, 0x03FF1B833301959DULL, 0x8803F1FE8AFF8442ULL, 
            0x3D40D37065EE8D22ULL, 0x2FE6CDE4C51EC373ULL, 0x37B09B5CA198359FULL, 0x7D0DF49DA3F67A0DULL, 
            0x841F2768B7AC233BULL, 0xC77A4C99ABFCD642ULL, 0x7EC5DA230666F385ULL, 0x54E2C6A063F3EC1FULL, 
            0xC4695A5E529634ABULL, 0xF7CDA2DE1F6F3AD3ULL, 0x9D0741C18D77FA73ULL, 0x058AAF5EFBF0FC7BULL, 
            0x6DB3732CDF1B2C9FULL, 0xB8E89B856625FC50ULL, 0x6896484A555410E0ULL, 0x5AAFA5ACAAEC70ABULL
        },
        {
            0xAAA1C819F20ADF52ULL, 0xCC75E9A264D28498ULL, 0x9914224ECACC206FULL, 0x2DE887A187B8ABBFULL, 
            0x84A25BC80137B7DAULL, 0xC4AD0A466F25A156ULL, 0x5919189A64D761C5ULL, 0x910328C989983508ULL, 
            0x17E865AFC3974072ULL, 0x3C9CABB226AA5251ULL, 0xF182C6EB0EA42F2CULL, 0x96A61E221691D549ULL, 
            0x5E2BAD0D24373EAAULL, 0x9477DEB3E95EB3BEULL, 0x28C33A6250B7F05BULL, 0x319761BE8E6895E3ULL, 
            0xEFB7957FC9C44FF9ULL, 0xB0FFDA0BC82FBD3AULL, 0xDA7DA836C324E825ULL, 0xC3CA14D3041F8514ULL, 
            0x363A1E5DEBADB321ULL, 0x820156E8F5C9D10FULL, 0xF7E52F99824435EBULL, 0xDF28E219F54B5182ULL, 
            0x7C74A17BC2C4BED9ULL, 0x857CFAECA566D514ULL, 0x5DB57BEEDF678DAEULL, 0x2C68AD902BE9FB84ULL, 
            0x671F172B8C824FFFULL, 0x5DC27E0CBF74D3CAULL, 0x99F3BDAE613687FAULL, 0x32F5368A43EA4B29ULL
        },
        {
            0x6BF1583C464D8DEEULL, 0x493B5419750FFE5DULL, 0x79318CF4904D51DAULL, 0xE96CBC8DB234F75CULL, 
            0x2D7561B3652A5625ULL, 0x110B6B8516C6FADDULL, 0xBC0531278E070786ULL, 0x3D95FE351883A561ULL, 
            0xA5D4F31845D21C9AULL, 0xB97DAFCB6AE33F4BULL, 0x84E711ED00523A71ULL, 0x386FB7051C717C0CULL, 
            0x36B587622FE09F55ULL, 0x5E3FBEA845C7E61CULL, 0x1F2D2740461330CBULL, 0x558E222B28EFB350ULL, 
            0x5A7D403F8017204FULL, 0x51E0EFE598FF3E61ULL, 0x844421169E339A28ULL, 0x817930C5F24564CCULL, 
            0x0893FD8357241E1BULL, 0x17D59AA5BAD988D1ULL, 0xABA35F54DB5B2DB4ULL, 0xF97D949CCA622659ULL, 
            0x5385BB859682B50BULL, 0x841DA95D075DAF75ULL, 0x387DD2EBBC75C17DULL, 0x47B474A8528F3A08ULL, 
            0xC2029BBD1EE8CDCEULL, 0x962C96B83FA0160CULL, 0x41399B64397B7D83ULL, 0x2D2173C23449EEE0ULL
        },
        {
            0x9CE80AF3FA6270DAULL, 0xA79FF18F998E5E81ULL, 0x1CBE50C8CFDFDB9CULL, 0x108368ACAA926E4FULL, 
            0x4303EA2576CE5BF9ULL, 0x362AC3DBA68386C9ULL, 0x85A56BB5CC2C5E1FULL, 0x45A222B59C2B0200ULL, 
            0x7F180C2FD0DDFBF0ULL, 0xF31D2AAE836BF9D9ULL, 0xA05166C0CCA07EF9ULL, 0xFE16E20932CF30AAULL, 
            0xE00F5D2F25E1D57EULL, 0x16B908AC1B4C01A8ULL, 0x26C2D9A7AEE3A285ULL, 0x24B18E12BE9958A0ULL, 
            0xA644173C8CC2BADCULL, 0x221D36CFF03AA80DULL, 0xADF09084990866C0ULL, 0xE0C6E8EC1621C178ULL, 
            0x200A8D021BBC6F39ULL, 0xB489AC39E023AD3AULL, 0xFCF13253E43D764DULL, 0xC9BD6E058D3E10A6ULL, 
            0x5F604643DBEE327DULL, 0x132E5F6A6BF9628DULL, 0xA50EC1038B8A9D9AULL, 0x8366E23E0481164EULL, 
            0x0114AB3C874F4F1EULL, 0x7CC19AF5DA78EF03ULL, 0x5B361C9441A1931AULL, 0x3D086A56CCF7FF9FULL
        },
        {
            0x238FD7D832933C51ULL, 0x7DB152E9AD8E637AULL, 0x0D05AC51BCD6D289ULL, 0xF069EB695D2AC8C7ULL, 
            0xBD972FB1284F463AULL, 0xD00A61C5415D2A78ULL, 0xE43D45407D122684ULL, 0xCBF263584A999DD5ULL, 
            0xA97F3B1A173A8910ULL, 0xACB1038BB102EDE2ULL, 0x67249B0368DD34B0ULL, 0x893699003D793CA8ULL, 
            0x6776B08AE038A6C4ULL, 0x20C4394F23941274ULL, 0x370F2B5EF6F9B337ULL, 0xA1DFB5E9A7510E0CULL, 
            0x8D6323BEC61DCAF9ULL, 0x8E788BE60F9ECB8DULL, 0x73617EF995832985ULL, 0xB817308FD3017771ULL, 
            0x74F81D18D4E14275ULL, 0xD287FFC3AEE961ADULL, 0x1303FA93033BF02EULL, 0xCD7BD5C54836EA72ULL, 
            0x91EC525D497A335AULL, 0xB68187104FA00A0CULL, 0x82322D46697E2480ULL, 0x85BCA54000F6C5EFULL, 
            0x47F9164E6594A036ULL, 0xF6CA3316518BD5A1ULL, 0x46311579C3192A5BULL, 0x410A1E5AB5036A0FULL
        },
        {
            0x048E56007F58FC27ULL, 0x83C9C1829BB4ECA3ULL, 0x37212947A0FD53A6ULL, 0x6E1510E01B168DA2ULL, 
            0xA5BD18D8F37B859FULL, 0x3993352CBFDA4648ULL, 0x894CFE3D4F29858DULL, 0x87979942581F3E6FULL, 
            0x58494BE1CAA58872ULL, 0xC1065FFB66496804ULL, 0x155B96F4F246AC18ULL, 0x2CD3407EA0475D28ULL, 
            0x72299A662B8BA4D2ULL, 0x8FB81B6C70216161ULL, 0x4483BDE3DFB1909FULL, 0x128CDBD6F82B6DBAULL, 
            0xAA37676695B9F533ULL, 0xECDB014EE40259F4ULL, 0xDD053227A3E55566ULL, 0xC4400CAC3BB5BC8FULL, 
            0x261436461892CEBDULL, 0xACDC4EC6041EC4B7ULL, 0x4276CD05572E3658ULL, 0xB3AE1C2095F5BD81ULL, 
            0x622F1C733B392D5FULL, 0x36F0BF8B7115B41EULL, 0x4C7DA3EF8584D12FULL, 0x0EA2B2F3DC4C604CULL, 
            0x99AC0D8DF2CD206DULL, 0x365089DAFD4D6E49ULL, 0xF927577E607F0917ULL, 0x5346F7767B3E1CA6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseBConstants = {
    0x03E34F4956A071F2ULL,
    0x52D07F601CDBAAF8ULL,
    0xA5C7ED7AF6BE4C0EULL,
    0x03E34F4956A071F2ULL,
    0x52D07F601CDBAAF8ULL,
    0xA5C7ED7AF6BE4C0EULL,
    0xD092E8217D2D9FD3ULL,
    0xB62626BDB725400DULL,
    0xFB,
    0x36,
    0x37,
    0xFB,
    0xD0,
    0x09,
    0x5C,
    0xF1
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseCSalts = {
    {
        {
            0xBAFCD26015656FC9ULL, 0x23D5470050AA8AAEULL, 0x5B4C0E01E7FB3199ULL, 0xEE8DF994712A7AF2ULL, 
            0xBCE2E8686356F1A1ULL, 0x84C758B956EE2AE0ULL, 0x11E0289C1C34883AULL, 0x49080BD7CB42A8CBULL, 
            0xC5C3BCD54B42EC16ULL, 0xD2C9628DBA86DFCAULL, 0x85665ACDF2E84332ULL, 0xFF1A7BEE7A9E1206ULL, 
            0x0604E1706CDC0F2AULL, 0xA80D0FCA1F3FDFB2ULL, 0x7BA96CFFEC6D9451ULL, 0x6E84B3FC489BDFEBULL, 
            0xE4076CD21FD64D86ULL, 0xEDF73FBACCC7A1A7ULL, 0x5636603BED704D23ULL, 0x79737FC6B175CE28ULL, 
            0x99F5574A9BB2E868ULL, 0x9617D2C4B9F4134AULL, 0x8502EA56537B7912ULL, 0x59582F1211CCEC43ULL, 
            0x8B839D79743C7A80ULL, 0xF71D88F598B96E6EULL, 0x0FAD538BA437F6EDULL, 0x753A9332EF001AC8ULL, 
            0xE4AC10827D48BD62ULL, 0xC70CD15AF571B4E6ULL, 0x5636B7040B5B2B3AULL, 0xC6A9DCF01141825AULL
        },
        {
            0xC382352BC6F4539EULL, 0xB4A397C2872AEEE8ULL, 0xCAD208BEDD78F9EFULL, 0x5BD7B8F3D541DF9FULL, 
            0x5E110AB6C5FF0E4AULL, 0x3406F5E240AE2601ULL, 0xFBC7665072FE1BDEULL, 0xA59411788EC2C685ULL, 
            0x4084D71CF8A4775FULL, 0x0A5FD83742141FBDULL, 0x9E1219C6E91E1B34ULL, 0xE2A76395CFAB158AULL, 
            0x58ED181100DE40D1ULL, 0xF3318289C5F6E4ADULL, 0x31D11C0E46867A15ULL, 0xD58DA9E491C5A9E2ULL, 
            0x192A85ABF4322E75ULL, 0x10A17376C97094CAULL, 0x47C3101D9BE00FD3ULL, 0x0D4102960AA6AD21ULL, 
            0x84D9273EFB84888BULL, 0xCC9EF3780ADCD28EULL, 0x8D3E1FF43AAAFFA5ULL, 0xDEF611354CD2B5D0ULL, 
            0x291662D8204763BDULL, 0xFCE101E950023B83ULL, 0x96ED1059E6CA8301ULL, 0xDDB41913D7F3F84AULL, 
            0xC9C251CB258DB8ACULL, 0x83629C0E071854CCULL, 0x97A1907DD04A967CULL, 0xB73041259F6659E3ULL
        },
        {
            0x22D19DF50FE30FD3ULL, 0x5BF7A92A3C78BD1FULL, 0xC7D00407C00A6884ULL, 0x094A1DA1CB929712ULL, 
            0xF776F4888C0D6A2DULL, 0xDEF58DC9AD6C176BULL, 0xA0BB9EE807C3142EULL, 0x6F66A2429E6102B2ULL, 
            0xBF9AB4FBA4630743ULL, 0xEB9D114BB9EB0D66ULL, 0x2EC1F655AD49F8D7ULL, 0xF19BEC506AF41E26ULL, 
            0xB473D48549B4B237ULL, 0xEE9C5F7B3599C005ULL, 0x3619734DBF2CF58DULL, 0x38E7C55A4A1F6CB5ULL, 
            0x15B8034A54E2BEA7ULL, 0xCC6D7C2D2A5049C8ULL, 0x288E910A48BB204DULL, 0x28BF55E37F61DE94ULL, 
            0xE9647756F14D3AA1ULL, 0x5EFF4FC45DE3A515ULL, 0x54DA2BE243466E17ULL, 0x03F85B96CED0E501ULL, 
            0x8599287B2D300E5CULL, 0x5AAE132B7C72F537ULL, 0x457C08BD1DBBE2E7ULL, 0x4319BE709067D072ULL, 
            0x80B9B81DEEFF0B91ULL, 0x5D6FDF16B3C7EBB7ULL, 0x7DD1D4271D886F9EULL, 0x94FA71E59A608F9DULL
        },
        {
            0x5CCB4CF87C60AFCCULL, 0xDCD1E052480D4913ULL, 0xE3880E4BA0C1A559ULL, 0x6D95DF928ADF09D4ULL, 
            0x9CF9E67FE99DF3C8ULL, 0xA6EACF5727010572ULL, 0xCCCA2EA0172C0D18ULL, 0x10DCDD70966BFE17ULL, 
            0xC5670A9C3B3F7F71ULL, 0xB92152886FA73626ULL, 0x6382DDEEBC8E3131ULL, 0x8DC99A449C267CEFULL, 
            0x743C8400A280A1B0ULL, 0x1902F93C50B02F8DULL, 0x8CEA6FD578D26383ULL, 0xD62A761DD2745F4CULL, 
            0x0CD70353AFF27F6EULL, 0x77368797827D00E1ULL, 0x1D0F00F1997FD789ULL, 0x406D7BF999048D69ULL, 
            0x4269E41430767A73ULL, 0x962382CCD7795BD3ULL, 0xEF437C1C5B61AC85ULL, 0x745774225CFCA52EULL, 
            0x35921CC8AFCD912FULL, 0x12F14B707E54EA9FULL, 0x5332C54FA08724C6ULL, 0x0F450CEB3F31DB67ULL, 
            0xDD2A4D40DB2F881CULL, 0xD7C83D173AC86D6AULL, 0x48A2A5521D1502B4ULL, 0x667922135E27009CULL
        },
        {
            0xDA9FE6CC75CC3469ULL, 0xC6BBCBFC3F0D3CB6ULL, 0x306E6D1AADEAC2CFULL, 0xDF3042DFB5F1EEEEULL, 
            0x17AD053173A1BB1DULL, 0xE51319AE97C5A07CULL, 0x81E121E0EE46A17DULL, 0x3BD98E356F5FB791ULL, 
            0xEF19847417B4FA12ULL, 0xD97171A0592CC602ULL, 0xE959AB8435628C46ULL, 0x510A3EA4C49E9AD7ULL, 
            0x6ABCC0D277E9F727ULL, 0x34BC35969BAE953FULL, 0xEA09E0F8736C6F2EULL, 0x7354AE8AF66E1701ULL, 
            0x1C5CF3B9F5FFDCFFULL, 0x96045B2EBFDF7D0FULL, 0x375008B30A2F4222ULL, 0xB88EEE73E0AF5D15ULL, 
            0xEB1424097D3D894BULL, 0xE6B529A928B6C868ULL, 0x58190FA5A39668A9ULL, 0x9EE5D7312537C50FULL, 
            0xD7ECB4DD328E47AAULL, 0x2399F15C7E4B24E0ULL, 0xF842CAEA8A8A4583ULL, 0x23B0BBFD3575CBC9ULL, 
            0x0995D00FE2B227EFULL, 0x97646B6D3328ECB9ULL, 0xBB28FF74938B7F26ULL, 0x8E49EE3251FE0356ULL
        },
        {
            0x7FADF2BCA84E87F7ULL, 0x12D9B78CB3AA571EULL, 0x678275F4FED73945ULL, 0x9A1C441403CAEDCEULL, 
            0x8A41FEFDD339289BULL, 0x67F909CAC5CCF4E3ULL, 0x173AB57BE51F3861ULL, 0x89F6A99898CF0314ULL, 
            0x09E51541E4A6553DULL, 0x4AF6D90A083FD3ECULL, 0x6850589B249BF95FULL, 0x4E15C0DCF7074D12ULL, 
            0x09F68853BD7576A2ULL, 0x6C1E3433288D5D33ULL, 0x3655CC6275CCFD76ULL, 0x2FCA520A1C234C3BULL, 
            0x6402467F21F0AC73ULL, 0x0759C125090ABEA1ULL, 0x91CA543306DA3783ULL, 0xEF622B34BBC98431ULL, 
            0xDAB9468990910E9CULL, 0xB783138901F095B8ULL, 0xAF54EC55E33175E9ULL, 0x649B54E3386F2A86ULL, 
            0xE8A4200F0F888CCDULL, 0xBACAE28F98F2C304ULL, 0x802A17AD66A5CCE6ULL, 0xA1963C6CA685BDFFULL, 
            0x3A18CF5BA4333BDBULL, 0x786656E6B17E111DULL, 0xA60C0DD7D46C6FADULL, 0x72BFB26DCC3E437AULL
        }
    },
    {
        {
            0x2C4C5613BB4EE403ULL, 0x7D5D16D94CEB20ABULL, 0xF497BE514A4055A1ULL, 0xC5E5B239FCB5D676ULL, 
            0x9AA6063A2E6AC641ULL, 0xB8B438E9EA82C5AEULL, 0xFF24F2FD2C128CEFULL, 0x1934081F95B1C34CULL, 
            0xF7E7E0DA44C7B8CFULL, 0xEE354749908D2BEAULL, 0xFE16C34432829366ULL, 0x5E31538D78240BCBULL, 
            0xDA0FCC8E51C61A92ULL, 0x068BB186D06B4FF1ULL, 0x8657270AC247B083ULL, 0x104C59DCE6197ADBULL, 
            0xE616B99D9878223EULL, 0xD1C582085C7E3BB7ULL, 0x674BE0742D305C6FULL, 0x0F3242C25D3FB88BULL, 
            0xEB2D87792A0B70D6ULL, 0x3ED5D87DA3D352DBULL, 0xE1F68B79F82E4ABFULL, 0xE0E0022239E7FFF3ULL, 
            0x3A0BDA9C07298FAFULL, 0xB2D50FC05FE29D08ULL, 0x230061BCF480039EULL, 0x8E7C0A7A21E8693EULL, 
            0x1DDF4047549538A7ULL, 0xB541CD9299713AB5ULL, 0xB2F89B978830C945ULL, 0x26D6E1F745DDA0D5ULL
        },
        {
            0x66D068D8668556FCULL, 0x0F24EF7E315B7439ULL, 0x7CFC80BCBD3A3FB5ULL, 0x1A360EC9AD7099D2ULL, 
            0xC20998737DD6A015ULL, 0x41B4D64E7D0F5900ULL, 0x80DBAFF0F770227DULL, 0x447A10F3E4EEFB26ULL, 
            0x0136FC937258BA07ULL, 0x8AAC9ECAA26216E0ULL, 0xEDB4BD18646E1B3BULL, 0x021D005CC2586AC2ULL, 
            0xD48CFD5157E24115ULL, 0xF80770A64596F0EFULL, 0x1C69529DCB0A8C8BULL, 0xE306B597299BDFBFULL, 
            0x890D7AA59B00C1D8ULL, 0x36BD7D6D9E2A84DBULL, 0x0FD26442818925BFULL, 0x1631F8CF00CCF366ULL, 
            0x584773FEBE6D9D7EULL, 0x806E5EDA0C922BEEULL, 0x6E1A6D671B0679AAULL, 0x18CBD4351ABE0B83ULL, 
            0x248A2D4DC846D20AULL, 0xC9E3C1D1F740D1F0ULL, 0x9F3E149D7CFB22D2ULL, 0x87E784E047883C32ULL, 
            0xE6424D3A342B2CA4ULL, 0x40CAD43D4E02E890ULL, 0x0B80725337F3496FULL, 0x6464CBA42440B511ULL
        },
        {
            0xABC24532DAD5D15CULL, 0x2FC7A7EA6CABF443ULL, 0x64B75D37BDEEF6B8ULL, 0xB74887A2517D62B1ULL, 
            0xF7D9472FEF67667BULL, 0x0AF98ACD349AB90EULL, 0xE9B23D10D40547A2ULL, 0x471C59A4EBECAB6AULL, 
            0x4456D73FD61698CCULL, 0x39938EE2CB288F37ULL, 0x5F04466B516C1F68ULL, 0x997DF04894DE59A4ULL, 
            0x218927DD1ACC9936ULL, 0x8F6E26731CFD1FAEULL, 0xE77CECBAD9DE428DULL, 0x9764C2DB64F925E9ULL, 
            0x103A56D42BFEE94BULL, 0x14B49FA9E3E3D52FULL, 0xFE8D6FE199EDC604ULL, 0x39AC96A0BD463EF8ULL, 
            0xDC3C1E6929DEA426ULL, 0xBFD3002C993A1AD6ULL, 0x9E16EA00B3E10637ULL, 0x2E87C2128C6B2368ULL, 
            0x53064C9E728A863BULL, 0x51875F344EE41EF2ULL, 0xAD6DEC5FF19D1EE2ULL, 0x0AF6721D3E8B20C4ULL, 
            0x124C4FEAFE48B396ULL, 0xC1D712D601A22E8EULL, 0x015BB3212396159FULL, 0xE22BFB298F03179BULL
        },
        {
            0xB49CD7AC0D118C7AULL, 0x4A8EF1845E67E21FULL, 0x029A32930E9D4C52ULL, 0x036F9BDD338FD269ULL, 
            0xBAA357780CFE716EULL, 0xD32B7550233E5BC6ULL, 0x3D3DCBEC09CF842CULL, 0xBB5034CE5BDCEBDBULL, 
            0x89B28E8ABCC2DB39ULL, 0x37D9B902F9213CD9ULL, 0x54558323D8C9B360ULL, 0xBC7B9B0F72CD34B3ULL, 
            0xA95C633A71AC67FFULL, 0xD11C756EB4DB556CULL, 0x5C40952252680B25ULL, 0xBC855EAFB186C87EULL, 
            0x21D969E56A4231EEULL, 0xC28A2CB3415912A5ULL, 0xC6423F49AD6759BFULL, 0x17C45AB73CFA0A79ULL, 
            0x54DF89A1D652C0DBULL, 0x7497D81257E5D80DULL, 0x2A85530209E80364ULL, 0x5FF0918CBDD17184ULL, 
            0x80506D25DC56E30AULL, 0x733EF166755DE31CULL, 0x12C39080235B5623ULL, 0x8E254D032FC382ECULL, 
            0x67CBA553B81C7DBAULL, 0x9FB02C23883DBFCFULL, 0x485EC78D36FF8B6FULL, 0x47264F5F35154B70ULL
        },
        {
            0x1A4DA7120FA11418ULL, 0x15EBB308AD35D302ULL, 0x4C58052912DFA8E1ULL, 0xD63A18E833037F3EULL, 
            0xBB6237878E88840BULL, 0x2879FCA1152E99E3ULL, 0xED8AC5264C67B8F7ULL, 0x84FFA96314D75445ULL, 
            0x429562329C7B031EULL, 0x1C600C82867A38CFULL, 0xAFCF1034885DDB10ULL, 0xA45AF06B6FFE822CULL, 
            0x75D354D591FA21EEULL, 0x654FDCE6E17C5AEBULL, 0x96EF4DA2C94BF70DULL, 0xA8F4F9912E00F24EULL, 
            0x3D02F18FC233720EULL, 0x62F561EF2FCB4595ULL, 0x123C31E3D66B486FULL, 0xACF96294E8964411ULL, 
            0xC41285DC86311FEFULL, 0x51F0A6F3B337A7E0ULL, 0xE8E31D1F84790E34ULL, 0xA06190B9E65014DEULL, 
            0x409793D2B6C34FB8ULL, 0xD7B5700FEE2EAD55ULL, 0x50129FA19C9FAE9EULL, 0x388A19D1F27F650CULL, 
            0x0806BEB8D2998654ULL, 0x7978D8FFAFCA97FBULL, 0xF990EDB8C25155EAULL, 0xB55DB614BEA160C7ULL
        },
        {
            0x7CE31CC7E5D0BF7FULL, 0x47C224A13C0D7911ULL, 0x7B39C11EFC26AD66ULL, 0xCD11543406D9C004ULL, 
            0xAEDDAF1182A3B78FULL, 0x55B00DF074E23404ULL, 0x492D15EB4EC07014ULL, 0x62795EBCA9F7A519ULL, 
            0x9B166A807DEAD86DULL, 0x37C17F62C3C7CAD8ULL, 0x0B5ACE2A5B685A63ULL, 0x2C19DCCD9262CDBEULL, 
            0x927B0789D4BEB5E5ULL, 0x8E2EF8F438367766ULL, 0x142CA99B1568A169ULL, 0x111357ADCF8F6662ULL, 
            0xF5BA0893FC105E55ULL, 0xB48CB2E64969BC40ULL, 0x3F17E64220CAE17EULL, 0x691D8BB576666EE0ULL, 
            0x994AFF81A2A2023CULL, 0x40890CFF40E1609AULL, 0x2B166C784EEBE9B4ULL, 0x0654608EB0E24F04ULL, 
            0x83DCB9D4ED1156DDULL, 0xCBC7201BA6820A81ULL, 0xC2C63DB0CCFA7BD1ULL, 0x9129325D15EBA10FULL, 
            0x8C08B31F0BDC9C79ULL, 0x6B7EA6728E824D77ULL, 0x81AD7A23B604D8F1ULL, 0x2EACC09AD3CF2BC8ULL
        }
    },
    {
        {
            0xF334A9288C7F15D8ULL, 0x342F590B1A1AC081ULL, 0xBB3492585AB32FB3ULL, 0x5C6D7FF0EA0729ECULL, 
            0xEC9FCE246660087AULL, 0xA3204AF8A0184ADDULL, 0x715DAD25FE2C1D0BULL, 0xB38D82E315878BF6ULL, 
            0x551D81345F0EB566ULL, 0xABD215C0BCEC8698ULL, 0xA80CC81CF13AAFCEULL, 0xDDD642F6FE3A1BA5ULL, 
            0x97CA5A7434C2E70DULL, 0x89D0388FDF11A9E1ULL, 0x36CC355F91BFE82DULL, 0x1A0D32FB2D0329DDULL, 
            0x1A51FF9DB576EA76ULL, 0x76557C374D5B33D6ULL, 0x17C1459B033299E1ULL, 0x7BD69A982C68C11CULL, 
            0x57A6CFE010BCDB6CULL, 0x8AC75314205F437CULL, 0xBFEE15C1B9A01020ULL, 0x27C408BDC6FFE55EULL, 
            0x59B95944D7075AB4ULL, 0xCBE6101E7B171FB4ULL, 0x6C69CF940E05BD35ULL, 0xEBA110B73C6C7823ULL, 
            0x59888437ED783193ULL, 0xAC7ADF2B83D9103DULL, 0x2E99F5E87D738CEEULL, 0xAECC1C9B2F003B04ULL
        },
        {
            0x81422EA2EE8B3E5FULL, 0x01C0C61CCB83D265ULL, 0x99895C21B32E58ADULL, 0xD63AD5C2C2435D04ULL, 
            0xED2B70B8B632D2D5ULL, 0x5A897360A64C1597ULL, 0xEE60DE097257558FULL, 0x9F5DFB4158736C8EULL, 
            0xD2D04CE4BC8D3A27ULL, 0x2AF9435C3FDA98BDULL, 0x1130F4EADE073D02ULL, 0x1589988F7BC95901ULL, 
            0x4C3C75BCC426483BULL, 0xF5F04B9FA9FD67ECULL, 0x99BD203950457253ULL, 0x98D8C46495C33837ULL, 
            0x2CEB05327AEB8E07ULL, 0x80561960D1A2F933ULL, 0x9B2505FE4325D459ULL, 0x49C735BEC121423CULL, 
            0x43D72831756AD117ULL, 0xDA5D2FC630094564ULL, 0xC54A6049F2C5ACB8ULL, 0x6D4145627E9D749CULL, 
            0x197BE4661F2490ACULL, 0x50CECBE154C8E346ULL, 0xAA51700DCA128462ULL, 0xB373B69B58794C45ULL, 
            0x5029F1D49FC4E9B0ULL, 0xD02E83EF780D16EFULL, 0xDF133E16D796C61BULL, 0x2361128FD3BCF4CBULL
        },
        {
            0x9736BBD6B776CC63ULL, 0xA3FDAF68A1E36AE4ULL, 0x7D3E537082C90FAAULL, 0x4D211C54B4A0E5CDULL, 
            0xDD89B3382E35AD5CULL, 0x19D7ABFDD5A4F294ULL, 0xA505FDF243FE63BFULL, 0xF6BF8D9F9F7E2C92ULL, 
            0xBACD50019FB6C728ULL, 0x4A915ED590A13EE2ULL, 0xFFF993A499165C60ULL, 0x3D705D9750E50396ULL, 
            0x3BE37C640E65D4DAULL, 0x382B565EF31DCEF5ULL, 0x9797CB6E2294D67CULL, 0x2EC06AE390AFC980ULL, 
            0x7AEDFD83ED7F3E2AULL, 0xDC2C712DFD30D74DULL, 0x99C9D8F90EED490DULL, 0x2E8C8B339760A0D2ULL, 
            0x369A3544A965E946ULL, 0xC6A101F5B1B91785ULL, 0x3AE07CEAFB2ED3A8ULL, 0x729CDA353CACA78FULL, 
            0xC2704A0E00B40AF2ULL, 0x06B90FF8DB79E4DCULL, 0x16711B6E8F103CB3ULL, 0x22B1F2F7275A4984ULL, 
            0x2284646F2CE9A288ULL, 0x50B0F48E4DEA7242ULL, 0x115280906C68E4F6ULL, 0xDFB3DF46DC4E9ADEULL
        },
        {
            0xC1CD61DF890C0ACCULL, 0x3EAC2D84ABADD41AULL, 0xCB179BE1A919B4FEULL, 0xE634EA4C66C19C26ULL, 
            0x79B5B792DFD28079ULL, 0x4689B77B4A273293ULL, 0xB2EA370083633F11ULL, 0xBD12FFBACCC25EABULL, 
            0x6060248C8FF3C91AULL, 0x42DEA3DD6E6FEE63ULL, 0xFAD59E67FA3567EEULL, 0xA22603EA75FCDD62ULL, 
            0xA684F66711C14D94ULL, 0x773533B843D9931BULL, 0x3BAFD1B73D29FE48ULL, 0x4182200F97CA0884ULL, 
            0x1FA0C0B9EB152368ULL, 0x904E996FACA2AFA2ULL, 0x1EBB9F0A28595651ULL, 0x7E39CF76333ABC5EULL, 
            0x6BA044FC935A3AB4ULL, 0x1368E8A7CB9AB13FULL, 0xCAC6EF39BEEEF26EULL, 0x6415D9ABE5D29B89ULL, 
            0x2E8F7CA6C8A5C34FULL, 0xE0466BFE3562F227ULL, 0xD7E38A24B144FA75ULL, 0xFFB4801B5B2722B1ULL, 
            0x6A304AF9B2C70F32ULL, 0xB74E5715FD42D6FFULL, 0xDA89A82D85172133ULL, 0x73A816B99B90A251ULL
        },
        {
            0x233C28FCBD299674ULL, 0x07CA4B35CC28F27EULL, 0x33DAE22E10259946ULL, 0x13D09E09851F0008ULL, 
            0xDB35882602D10D13ULL, 0xAD0FB3A9A806C2DFULL, 0xAB73D71BC3CB300AULL, 0x589629268F86E2EAULL, 
            0x9E093159559B518EULL, 0xB9B7A08D48A90A12ULL, 0xC00219F0E2C336EBULL, 0xA854B8750326FF5AULL, 
            0x39C4FFBDA95E482AULL, 0xDCE12D9E6E58BDBBULL, 0x826D14CC6D0F8490ULL, 0x206E1C7C10628702ULL, 
            0xFDDAF42E27B4E84BULL, 0x22E2233FE0234B66ULL, 0x7A4D9A8A887A595AULL, 0xA1CF3868E43E9B6BULL, 
            0x7273F2B5DF915FD5ULL, 0x2A90A5FB24CBB372ULL, 0x1E85D79ADF6D3797ULL, 0x455F9A8FFFD9A339ULL, 
            0xDB48A0683856B6A3ULL, 0xBD99E60784C91102ULL, 0x478FFC17554DC44FULL, 0xEA79CB77F06C284BULL, 
            0x4B8A1C9C63B43386ULL, 0xD5EEEEABC3B62EBDULL, 0xCB46A987D3489D26ULL, 0x699C4CDCB3FA023CULL
        },
        {
            0x318B2B9E0C7CD72CULL, 0x00779CE217372ACDULL, 0x54CDFA726978B09FULL, 0x20226D0606F8D8DEULL, 
            0x0F5635F2A9E31C61ULL, 0x19DE35D6878875C6ULL, 0x2B48E8E51AE95EABULL, 0x84777AD193A1500DULL, 
            0xB36A3E509D04F821ULL, 0x0B1901BBF56BE958ULL, 0xCD6CAB79748A44F4ULL, 0x22B7CD4ADC48DBDBULL, 
            0xD38EEDFA4285F459ULL, 0x1760A5014E6D191FULL, 0x11A9D31FBEFFBA35ULL, 0x711066C3448CD4BBULL, 
            0x8B4AEFE77D424721ULL, 0x2327EDC4800609A4ULL, 0xB5B4D78776F91306ULL, 0x506B96910D647611ULL, 
            0x6A2459FF7A217A69ULL, 0x4A5F1FDDA1D23E93ULL, 0xF09565A6DFB7DF45ULL, 0x807471D967F995E5ULL, 
            0x8CC0F21E94B3B9C7ULL, 0x4D02E0ECA176A986ULL, 0xBE9C72A7F39C1D63ULL, 0x9291D177DDBE9F7CULL, 
            0x43E70739933AD098ULL, 0xBA93FEB98175802AULL, 0xFE136B9D499120ADULL, 0x674AF793ADDBC1AEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseCConstants = {
    0xE1925967E72C5BE2ULL,
    0x0C118D78392EB47FULL,
    0x2940A46FF88A13FDULL,
    0xE1925967E72C5BE2ULL,
    0x0C118D78392EB47FULL,
    0x2940A46FF88A13FDULL,
    0xE9D5995235071793ULL,
    0x9C02381CD28283A4ULL,
    0x7B,
    0x6D,
    0xF3,
    0xD0,
    0xA2,
    0x59,
    0x84,
    0x62
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseDSalts = {
    {
        {
            0x5A304AB1A2A2A68CULL, 0xB02E841899E5C916ULL, 0x9934889D623BFD02ULL, 0x50DD369F6F78AEA9ULL, 
            0xFC24B9DF40BEEEEEULL, 0x8C70A359F17FDE29ULL, 0x97FDF892FBC1DD68ULL, 0x8541BD0EFD361D2CULL, 
            0xAE36884F9449144DULL, 0x80EE751C2B613DF0ULL, 0xA5736DEF21C4A5E5ULL, 0x72ADE2BF28AD52D1ULL, 
            0x53D2E676E37B38ABULL, 0x9617765C0CB2EE3AULL, 0x0F5E00415EDE08CBULL, 0x2BB9A5CF641956CAULL, 
            0x51A34B9B4BB1F8EDULL, 0x2C2E6796F162F6D3ULL, 0x1CC2DD2C0CC68457ULL, 0xA7E993E54235A8C2ULL, 
            0xA1A1616B5CFB1BA1ULL, 0xE8CC3BF2C9E8F0CFULL, 0xCF20C1AD73936EA2ULL, 0x12CC5D0136090148ULL, 
            0x8C5E6FCDC9C6D980ULL, 0x2EB491570F9BB832ULL, 0x0ABDC3BEA9A953B8ULL, 0xF488A5395D2D0D34ULL, 
            0xD5E30DC48CDC44D2ULL, 0x86FD5F19BA8F5DC4ULL, 0x3A244F281C829C9AULL, 0xA6A5A9647234C1B1ULL
        },
        {
            0xD537B7987746A612ULL, 0xC93F2D0C8692E849ULL, 0x3D2D9016B17CE512ULL, 0xCEB156221F878CC3ULL, 
            0xA0A2F80909DEAF28ULL, 0x41BBA41E6ED7F261ULL, 0x426C22C81B66DD7BULL, 0x65AF31925CA50AF7ULL, 
            0xF7DB737CA381AF36ULL, 0xB25FA94D84E8687FULL, 0x617E4BA5ED7B0534ULL, 0x8D5B14EEC50A28AEULL, 
            0x63FD5E1BEA125B59ULL, 0x3737F3A71F190C8CULL, 0xD661A8931D9B6304ULL, 0xC95B831231B151C8ULL, 
            0x3B124B505E112B0DULL, 0x52B98C031658C30CULL, 0x83C0033771CCEE36ULL, 0xC7618FB7D0182F23ULL, 
            0x376637CB606E181AULL, 0xE9CA1DFB916AEBACULL, 0xE0239476E3A31639ULL, 0x069B0C739024B65AULL, 
            0x27820381EE71BBF0ULL, 0x5773F9EDDEFCBED7ULL, 0x08D5E897E2F15418ULL, 0xC186292499EEED49ULL, 
            0x3BBC20524CCC98AAULL, 0x4F7E604C0D7DA23FULL, 0x6536971D116FD45FULL, 0xFBC406940C0D4EE7ULL
        },
        {
            0x9D661A0C3DDEC4B9ULL, 0x1C08EB9EABEB99FFULL, 0x11773E9F655BDE94ULL, 0x0F54D7468003D6EDULL, 
            0xF441A68D4E941E40ULL, 0x40055DAE12F6724FULL, 0x892775C118EBF72FULL, 0x33824BA4186BACA2ULL, 
            0x67D3F1A5CE8B9804ULL, 0xA2876E820901724AULL, 0x59322667BE400FEEULL, 0xC91606838BEC49ABULL, 
            0x235864ED224DE504ULL, 0xA87DA814666E6463ULL, 0x1DC4A057E6D85A01ULL, 0xBC6B429FD0C5816BULL, 
            0x52ED37989C086782ULL, 0x62172ED68BFB2F85ULL, 0x1E5DFCD57C6AF90CULL, 0x763C658B94278A5AULL, 
            0x3D297EE8072DE04CULL, 0xDEEEA259E948F902ULL, 0xABBFAE6AFCAFE17CULL, 0x32E4CDFDE5D1B83DULL, 
            0x3D959961B19A52A5ULL, 0x0F85C9A303BD4426ULL, 0xAB0940B5A6F1225BULL, 0x567A8B1505018846ULL, 
            0x36E01B9DE34F8194ULL, 0xC7437600E86F7225ULL, 0xDB77A552CF8444A6ULL, 0x89C1E543985DBFC0ULL
        },
        {
            0xAC61219B8C5EAFB0ULL, 0x7C0EA12C8DC667FEULL, 0x5A4E5150861583DEULL, 0x080A31F56F00998AULL, 
            0x8AE1B67EAE6F005BULL, 0xBF0BC2F71ED9EE90ULL, 0x95C7DE30A3A87AD8ULL, 0xD2A8E8C15DCC9E4BULL, 
            0x66636C47C06B945DULL, 0x9F5D08050A07560FULL, 0xF7E307C00B58A980ULL, 0x613836E08446A9BAULL, 
            0x22924F77C8113C49ULL, 0xD87310D6E8683865ULL, 0xF48EF7A8EBB5B12BULL, 0xCCDCFEA89535D02AULL, 
            0xA2B0E06771340B73ULL, 0x74DD71DFEEBC2B7DULL, 0x2852A0FA18B669FDULL, 0xFAC335FC51C09AAFULL, 
            0xB11A79191923868DULL, 0xA1D9671487AE141FULL, 0x794BD643AEC5CE62ULL, 0xCCEE29700BFFB0D2ULL, 
            0x2143E7833FDF2B79ULL, 0x972977A626BA6FB8ULL, 0x6656A1A37E92C14AULL, 0xCBAC337F6C6A7795ULL, 
            0x061D31CB729E8607ULL, 0x53868D1EED4595B3ULL, 0xAFB0434DB71AFF4AULL, 0x2EF6A38EA2628668ULL
        },
        {
            0x65538DA279969104ULL, 0x2A3F68CB910A8913ULL, 0xF726370E7587771AULL, 0x1B2FC35A988C1735ULL, 
            0x4F53601C7E33DAF4ULL, 0x3777C7A9FBDFD236ULL, 0xB2E60F46A4CBCCFEULL, 0xCFFEDFCBE2B5F89FULL, 
            0x1315B582EF9268E8ULL, 0x709890B4114A3D65ULL, 0x7B831B5CF9ECA08BULL, 0xE703DE6F30625EDBULL, 
            0xAD7FA5712F46DFD5ULL, 0x8943ECB2E6DA2BE1ULL, 0x3391D2D97A6F1E0FULL, 0xD02DA679BDC53536ULL, 
            0xADF7C30D35E65E6CULL, 0x6740D0CF1D46C9F2ULL, 0xF7B2713561374F2DULL, 0x54F926AA7BCE8B03ULL, 
            0x59F899643E922BA6ULL, 0x41356B2A68F7BC4EULL, 0x07CB1D17D3A39082ULL, 0xAB32B21994C21A57ULL, 
            0xA46B34DDBBF3DFFCULL, 0x33B41CB7428AC75DULL, 0x56CBC47CB4C3EAE2ULL, 0x8578AB0A32273473ULL, 
            0x97C74407B9E21BA7ULL, 0x7B405F2BC683DC72ULL, 0x04FA010C39830F5EULL, 0x308F62F0B2C9D9C5ULL
        },
        {
            0xCA95E2D830DE9E21ULL, 0xE65F6A557B1A3C4AULL, 0xD7D67F2433E6DDDCULL, 0x8CD353EA74EE7CEBULL, 
            0x1FD6F601A00630B3ULL, 0x9BDBA5D8CAFCD3B1ULL, 0xDB4DFEE4505C93B7ULL, 0xEEC9CB74E68A7CA4ULL, 
            0xE331039357E7C42BULL, 0x6B39B79815E8EBB7ULL, 0xD1ED0045158C7242ULL, 0x8EBEA9887A5CFA7AULL, 
            0x2775869818D49ABFULL, 0x8125DF2B5F9F290AULL, 0x8EF3884525A8FE3AULL, 0xE7810C8A914A5924ULL, 
            0xEF6C5BCA291442FAULL, 0xF6290A4880D188ECULL, 0xFCD8FDBD98F8E539ULL, 0x6C1DAB58B6EB0D52ULL, 
            0xE7256DA02D34A4E3ULL, 0xAE146B09B41E0EF5ULL, 0x18BAD103D407D035ULL, 0x3F3986A20D79B542ULL, 
            0x53C0E505096A95ABULL, 0x778D5EE2520BE946ULL, 0xA33F7A81EE403218ULL, 0xC783971E4B440FDBULL, 
            0x10506DEF01421A77ULL, 0x5FBD2938DAEB337DULL, 0xCBA00848592CAECBULL, 0xDF787F25196AE4EDULL
        }
    },
    {
        {
            0x71091FAB4DB374BAULL, 0x623E10DA01C33D66ULL, 0x1E352A6821E7F7FAULL, 0xA12B2D0B143E23D1ULL, 
            0x7621E714CC26FCBCULL, 0xF7D5BA527C0932ECULL, 0xC74D8EE29C321F59ULL, 0x4E101F208FFE33E9ULL, 
            0x49B54EC34FC2B367ULL, 0x8AE01416FD374356ULL, 0x274C012AB7B47DEFULL, 0xEC34FE6927992BBEULL, 
            0xDA850218BBD0DC7FULL, 0xFFAFAF08F6364EEFULL, 0xC51A175897E6D4B2ULL, 0x3420F6813DC55F5CULL, 
            0x27332765A4E5F3B0ULL, 0x538A95CAF8817139ULL, 0xFF1474FAAAE5F830ULL, 0xB02453CF31AAA451ULL, 
            0xA79DCC17552A79B3ULL, 0x02FF6329D80114BEULL, 0x7D106F531C32FC56ULL, 0xF51DF16E4A260B5AULL, 
            0x06B93AA70ABC3CBEULL, 0x174B6B99020F9CEEULL, 0x13D3939E1F970E17ULL, 0x793AFD29DCE8E476ULL, 
            0x6AF37E200AFE6DFBULL, 0xAE20846C2FDDF777ULL, 0xEFEA916F3C364B6BULL, 0xE07427284D378F14ULL
        },
        {
            0x671F5682CBF4D8ABULL, 0x13A9023D8F5048B2ULL, 0x10A18A664D95891DULL, 0x0D3C4177476D1270ULL, 
            0x503027372E32096EULL, 0xD8D30E9B22FDA7D1ULL, 0xA8975B72E403EB0CULL, 0xE7B41273FCE906DCULL, 
            0x4D48C34AF46ED5F3ULL, 0xDB3EA799030C8A93ULL, 0xCEC802374A3774C9ULL, 0xEE0EEB720102FF2BULL, 
            0x429BD9C4B204BCA6ULL, 0x84FB98FDD1CDFCB6ULL, 0x470F7F9214CD0D62ULL, 0x5FAEC5FFBB82D7B4ULL, 
            0x66A28CB5BA9260CBULL, 0x6160E588DAD077DDULL, 0x82E2C75DFA0E534FULL, 0xA1B054EE7B858139ULL, 
            0x6D603B0CB2A52A50ULL, 0x4D8684FE102A55C2ULL, 0xD96FF62661C22697ULL, 0x4ADA82EF64FF0299ULL, 
            0xEB3850B43D54AE85ULL, 0xC733381276450C67ULL, 0x43C7B3F70C3FE736ULL, 0xEEEB7679B69B3482ULL, 
            0x9AEFB77DA0E86EFDULL, 0x1E5BB6F6D26F59F0ULL, 0x389D3E470D521B0EULL, 0x11BB8430379ED85EULL
        },
        {
            0xBCA5B680B85D455CULL, 0xE1A547D986FE0A11ULL, 0x9CAFF6BA3B3C91A9ULL, 0xA5BFD11B4EE69C74ULL, 
            0xB42D7B6D34E4D03AULL, 0xD4781A503A82DC32ULL, 0x79D066BE36B01EB1ULL, 0xE9925B872942CE84ULL, 
            0x7BB8A4B95AE1A186ULL, 0xCC7CA9D04325D9E0ULL, 0xB1A9ACA19087EA34ULL, 0x91C78F1D057F63DBULL, 
            0x67FCD1F07FA83864ULL, 0x62306FFA5B17CB21ULL, 0x30E3323265838B84ULL, 0x9A8C4A4E7CF04F31ULL, 
            0x470D5A42E29BDDBBULL, 0xF2F48431B9568935ULL, 0x022EADE9A2662B93ULL, 0x33763652177CDF93ULL, 
            0xFBD505CC0568B8FEULL, 0x7C7E315A02F4F11CULL, 0xC3B99964F674D9CDULL, 0x2A87B76C73D6307FULL, 
            0x6D4DC3ACE2E457C8ULL, 0x1136F99C45AEDD01ULL, 0x69A91105D1962088ULL, 0xAD8414D4494D0EBAULL, 
            0xCE0D19F6D867612CULL, 0x615E560978056424ULL, 0x2AA0AEF0651AF8C3ULL, 0xB4365F8EE8FC43EFULL
        },
        {
            0x8CCC983D70EB9257ULL, 0x7AD7CBF7252F5B32ULL, 0x101FBFE0AEAA8A61ULL, 0xDF35CB98CD706FD0ULL, 
            0x8B0F846D5BB2270CULL, 0x307A4460296C08DAULL, 0xBA765DCE4BE3BB2BULL, 0x4F6C12913E9304AFULL, 
            0xD4383D9B570B19CCULL, 0x32AFD1A3DC9C30B2ULL, 0xA1733424A1AA3A6EULL, 0x7E876BA0B5EF5C45ULL, 
            0x5284DB3C27C78A91ULL, 0x80A3DB72D4099512ULL, 0x5E15153F964EEEE4ULL, 0x73C3A3FD0938E922ULL, 
            0x403AA3368BA5572FULL, 0xD60EB59073A48501ULL, 0x0FB00DD4C5957D3FULL, 0x05C3B4DE1D578DBAULL, 
            0xDB1CC46A807CA516ULL, 0x1E3935D8382162BAULL, 0xF4F21712CBE5B087ULL, 0x4CFB8F24CF060388ULL, 
            0xCC87AC9291B3DD1BULL, 0xA172DE56BD4E3FFBULL, 0xF01F8578B28C121CULL, 0xD7D5618110662056ULL, 
            0x9C9B30C2A574915EULL, 0x1DA6ECC05BDD4615ULL, 0xE81FDCACE8240B6CULL, 0xD39223FDEDBC2F40ULL
        },
        {
            0x5952B02314ACD777ULL, 0x7AA791870DA9DC19ULL, 0x488508555BEFBC23ULL, 0x8D579E14D796B2F1ULL, 
            0x5A8E6BC714D11355ULL, 0xF60E70C2FDF6CC88ULL, 0x8827252E959AEEE3ULL, 0xE2146CF7098A2E5EULL, 
            0xE95EB74D7B510E4BULL, 0x023DD7A403E40670ULL, 0x20ACF4F469C6D0CDULL, 0x5B2944E08F1CB60AULL, 
            0x364AF89E8DAB58A5ULL, 0xC59EB746582661FDULL, 0xD0E704CFB4CA6D19ULL, 0xC62BA1DD45709857ULL, 
            0x01A56A8B7488CE41ULL, 0xB22C72A2AC74C9E0ULL, 0x036AD3C0C76FB854ULL, 0xFBEB6E59AAB52BB8ULL, 
            0x12F334EE37AD71A7ULL, 0xA353484286FA3DE8ULL, 0xD5C86C79A9A614F7ULL, 0xF649B997A506BA81ULL, 
            0xB30C45FBB501EDBDULL, 0xA03390070AE53376ULL, 0x87270B3CD552179AULL, 0x4699F994B36B0D4AULL, 
            0xC572DA300A60297DULL, 0xE1190CCDC85785D7ULL, 0x4DB09FEC1DD17EDEULL, 0x9D46EB1E40A408CAULL
        },
        {
            0x5ADF9CC7DEF2FAA3ULL, 0x3A86D650A430867EULL, 0x822EF319A6611B56ULL, 0x5662E0E1E1E2209EULL, 
            0x5C37D852D983D326ULL, 0xDA250293B3503B99ULL, 0xA77A585BFDCF4076ULL, 0x5060CD8F81C6F790ULL, 
            0x113D43131E20684DULL, 0xAC0DC2040B156A42ULL, 0x9BF2A1F6CD447C84ULL, 0xB692E16E90755A65ULL, 
            0xB8491D07F0AEA919ULL, 0x7F7FF36C6083B3D1ULL, 0xE86586C7F744440FULL, 0x3EB0FF1DAA56ACD0ULL, 
            0x361E95FC8243ED66ULL, 0x96FD57D20D4703B1ULL, 0xC4373E30C701763FULL, 0xC02EBA261E80D2E6ULL, 
            0xFA08415ABDCDD78CULL, 0x230FB566039F8EE2ULL, 0x3E896711CC82A7F7ULL, 0xA70CE66785999753ULL, 
            0xAAAADB39232F33EAULL, 0x44A8C4D8F2AF886DULL, 0x8FB52EE2851668A8ULL, 0xDB35DB5CF79245DBULL, 
            0x871C59250EA6B8B7ULL, 0xE41531A8B940B4C0ULL, 0x472259C6B7C528A8ULL, 0xCDFEC0E9483C9C9AULL
        }
    },
    {
        {
            0x2662BC6B0BE2B613ULL, 0xEC5CE9EC16BC8CE4ULL, 0x632CAFEAD64C95B1ULL, 0x79FC0E327AD3D058ULL, 
            0x7EF1FF14DFEF126DULL, 0x444E943093A043A7ULL, 0x8759FA3AC3C6B4CBULL, 0x5317ED3806779579ULL, 
            0xA8A74F93A939D12EULL, 0xA17002797CC97018ULL, 0x76C5B09F8B111143ULL, 0xCA403AA470F85FC0ULL, 
            0x1B4B711B4B6CBCA6ULL, 0x08379F8799C22654ULL, 0xA46C2D6C320A3E4CULL, 0xD00711386E5B2A08ULL, 
            0x814202DF99C86540ULL, 0x1B42DBB83F909BCCULL, 0xC5E7038731223A2FULL, 0xFB0F0CE06C4796EBULL, 
            0xA7C563B823D48FE8ULL, 0xEB0F79FB7EADB31DULL, 0x5F80E9D0956D9727ULL, 0xA9EF8B337A1FC4EDULL, 
            0x4B1A14FE1518E8E4ULL, 0xBBBE37BA0B5140F6ULL, 0x3126BE291FAC8CE9ULL, 0x609ACE05B6F36A7DULL, 
            0x847F4E1E6BFE40F8ULL, 0x2B85FB53C0794A47ULL, 0xB460312C543F6C4AULL, 0x3BD5298CCE9C257FULL
        },
        {
            0xAF5D8574D95F95EBULL, 0x9E7EE4A320732008ULL, 0xB741B7271F4C9DEAULL, 0xAA3B182322342019ULL, 
            0x9979470705BDA27CULL, 0x02B1A8917B6B1278ULL, 0x87CCB41E92B1D1FBULL, 0x416775D0B616D512ULL, 
            0x11806D320DD1116BULL, 0xC6E76CA377E7C628ULL, 0xC0F447F8F20260ACULL, 0xA0C6049C375D6047ULL, 
            0x3293761BB27437C8ULL, 0xAF6295BC8A18A15CULL, 0xC8EB807B5A0D2FBBULL, 0xE966CCA687482392ULL, 
            0x9EF6DFF35A47907AULL, 0x6F658D9C679FD684ULL, 0x42703C230F4663D7ULL, 0xD3D1C60E5D0BBDAEULL, 
            0x3AF1481F78D76400ULL, 0x642AF5E02B4FE332ULL, 0xEA5A7FCB1923A6A4ULL, 0x7B2702DC69963963ULL, 
            0xDEA8FEBB38FA732CULL, 0xBD7FE47D549B81FDULL, 0x78AE268C37FBF958ULL, 0xCBD6654002A2FA58ULL, 
            0xF88A97686D428227ULL, 0x9E103E4B534D19F2ULL, 0x8798242C367694DCULL, 0x51F36191BE0A7755ULL
        },
        {
            0x559B78284D22BB89ULL, 0x090D0E00FF5A7A81ULL, 0xA01CAB154449EA8EULL, 0x9AB3409CC815F4DDULL, 
            0x9E804387A60C7A56ULL, 0x74EC0940BAB33CE7ULL, 0x611D373B096E1297ULL, 0xC61BE57F18BB6940ULL, 
            0xFA59793DCF959F38ULL, 0x536AE2B6CF8DC0A2ULL, 0x07FE9D7AF6438E35ULL, 0x246C9601C417EAD5ULL, 
            0xD2240DCB90A45178ULL, 0x56BF73BCA9914D60ULL, 0xB0376800D2E1F798ULL, 0xE4F9AEDE109BAB77ULL, 
            0x5982EA045B2D7E54ULL, 0x61A66FE04E621F23ULL, 0x80E2F4957B03043AULL, 0x9C0462E7F06017B8ULL, 
            0x9395D555A088AA5DULL, 0x9B89522AD89BBB85ULL, 0x4DB2EA0EC9F43D50ULL, 0xA11B4723AAF5DBB9ULL, 
            0x75A1096B207B2AD4ULL, 0x6398B280267E72F9ULL, 0xDF6504136C2F13CBULL, 0x2B7430363032D7EBULL, 
            0x0993620371E6DA29ULL, 0x774BF14F88959031ULL, 0x471679F6CBF315B1ULL, 0x912CED8B2045F6FDULL
        },
        {
            0x75BBAC312039073FULL, 0x7463C8A7B29ADE53ULL, 0x4C6B59ECAFEA15F3ULL, 0x4BEA40AC0F0B8B7DULL, 
            0x11DDC3527BF57872ULL, 0xC4636B0B060FD8ABULL, 0x919BEEE3D8DC4DA0ULL, 0x6352CF60C0409F68ULL, 
            0x1BE179B4AE27BA05ULL, 0xDD0CD84FE4D0B9D3ULL, 0xECE4F2E6F729F670ULL, 0x8780631E4ED24996ULL, 
            0x93C265FCFB732B1AULL, 0x99721B4AAFE9D900ULL, 0x0638A2C78FE874ABULL, 0xAE6D174BA61CB255ULL, 
            0xB3BCE0A9D03F3B4DULL, 0xAFAC990902C920BFULL, 0xBADBADE4A38F80F8ULL, 0x8C25EF8F23C70D90ULL, 
            0x5F293732CCAB3E3AULL, 0x8989142596BDACCEULL, 0xDC0C4A0CAA229F84ULL, 0xD49F07B4C9D7D245ULL, 
            0xE4E4A5A7FBC17A6EULL, 0x3CDC31AC039F7E2CULL, 0x60BD12E86783A4F4ULL, 0x1B683F9B6A7BFABEULL, 
            0x15A44716C25136B3ULL, 0x3F6FEE853131E40EULL, 0xDBCFAB47DBF53560ULL, 0xE7FC47B29C3A09D2ULL
        },
        {
            0xD9B77A4CF8B81977ULL, 0x77C646138933E575ULL, 0x69185325669D3D58ULL, 0x6E5BD94ECFA3470CULL, 
            0x36092B88C3986B40ULL, 0xECE052F24731C761ULL, 0xA4AFB6ECA4D3E208ULL, 0x9A21B9676C315527ULL, 
            0x4685E7034B388FE7ULL, 0x04CABBAD9C0B0F04ULL, 0xF3D299193E065CE5ULL, 0x20A292BDC43014EEULL, 
            0xFE08E68B21507813ULL, 0x59AD18120A63689FULL, 0x606314E2F85771D2ULL, 0xCC2CBEDA0277EC6AULL, 
            0x240535476AEBF53FULL, 0xB267A503E5C7D786ULL, 0xAD7534F19E5C968EULL, 0x776AEBA795F28E0BULL, 
            0xA1EB85A0A22B517DULL, 0xD39C7DC93D124045ULL, 0x5A8BE697F8985742ULL, 0xAE13C6D2CF458957ULL, 
            0x16E221826A977588ULL, 0x0CF72EDCA46C94ACULL, 0x1BE9EA10C30091E7ULL, 0xAA68DD57D24F7FE4ULL, 
            0x85853EE3AB0CCDEAULL, 0x3571C7EDBDA149D6ULL, 0x98025650FDF0E71DULL, 0x014AFEB4A36DE506ULL
        },
        {
            0x7EB41C37B63A6C2AULL, 0xDFFAC1B1AC693312ULL, 0x4BA1E294C2E7BFF8ULL, 0x4ABBD754D463A2F8ULL, 
            0x116CB2F0BB76F6F2ULL, 0x0B6556939F6E9E00ULL, 0xE8707880EB0E62E0ULL, 0x99BEE982649BFDF7ULL, 
            0xB443479E0FE47F32ULL, 0xC68E3770ED9A3B15ULL, 0xB0516C22F815E242ULL, 0x4C6317AA8084FF41ULL, 
            0x8C26C4BEE4437295ULL, 0x6558AEE908AC2377ULL, 0x232D5C9970FF33BCULL, 0x364EE23A2EB23F33ULL, 
            0xCBB776FD98DBE659ULL, 0xBC13CE47698B0C07ULL, 0x3CF79352B03817B7ULL, 0x556E27C4F937E23DULL, 
            0x8D884AFECA2E2872ULL, 0x33AD49E92F9CA339ULL, 0x85EEA7BC7A810689ULL, 0x53D762CAD41A9F33ULL, 
            0x77CDD8F2149B0866ULL, 0xF86E7DFFC6CCD9E3ULL, 0xF2E4FB0A5D039809ULL, 0x6A41FA7D3EA98931ULL, 
            0xD6C70CF175C719CEULL, 0xF793BC458A4DFD74ULL, 0xAA195EA00C8A51BCULL, 0x8BC8E2A5D2A04259ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseDConstants = {
    0x1291871C8B7F68A0ULL,
    0xC784D24F6B01F70AULL,
    0xD35BF336A0D13AB4ULL,
    0x1291871C8B7F68A0ULL,
    0xC784D24F6B01F70AULL,
    0xD35BF336A0D13AB4ULL,
    0x97336ABD7BE53952ULL,
    0x08641F01315CC6E7ULL,
    0xE3,
    0x26,
    0x13,
    0xCB,
    0x73,
    0x87,
    0x88,
    0xF8
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseESalts = {
    {
        {
            0x440E17B94D4D0282ULL, 0x5B7B2BF270D7BCF7ULL, 0x856EFA32BEADBEA3ULL, 0xC06470B63C223561ULL, 
            0xA054193E9312FB5AULL, 0xE014327897F826D3ULL, 0x4B92E6321C19B7CBULL, 0x9D9DF4C026DC6C1DULL, 
            0x9416A30E06AEAB4FULL, 0x1EACD99C42E728A4ULL, 0xD9C56162224288AFULL, 0x1140C09291CD14FAULL, 
            0x0F13575537268831ULL, 0xCE2145D269152E37ULL, 0x8DE6C7E2194E0C65ULL, 0x4A5604105B2DBC6FULL, 
            0x5B29CCB913998962ULL, 0x199CCA9101D8F82CULL, 0x72E2DD0D797A29C0ULL, 0x571A71D619024347ULL, 
            0xD51462D6F4D04B32ULL, 0x1B7E9FD2B251D8F5ULL, 0x40880C6C4D5BD613ULL, 0xA5F65AB66073171EULL, 
            0xDC8C1F2D3733E29BULL, 0x17DB1F459A223753ULL, 0xAF52B4D47ED2F924ULL, 0x5FCF5364300E67EDULL, 
            0xB0352A6E080A8FB2ULL, 0xD168D7D005AF138FULL, 0xBDEDD3838BC91C51ULL, 0x7D75111F5FCF6162ULL
        },
        {
            0xDF57C76503661D4CULL, 0x7F9BABBD2B02C7C4ULL, 0xB60E736BECD8A4D4ULL, 0x24B27159B295E666ULL, 
            0xC2AD6481259664B6ULL, 0x575E0F444BF6720CULL, 0x9294514F3E05FA70ULL, 0x1254093C2D2371AFULL, 
            0x97D1DBEB60D9205AULL, 0x73F14A3227E1BD62ULL, 0xFA4D75FE5A1B3D6DULL, 0xAFC1FBC7D8E8F3E1ULL, 
            0xDE8FC8416CDC28A0ULL, 0x43B2D32B81B01E7EULL, 0x9394DDC974DC1BC3ULL, 0xC214DF3A3C77B5D9ULL, 
            0x64B355A8D3C1C979ULL, 0x7456E5403B1DB6B1ULL, 0x49B8CF0E41C5E5B0ULL, 0x7375829BF8A6B8EAULL, 
            0x4DA5F12F87D2F9A4ULL, 0xB86C9B217C1F6E4BULL, 0x86FAF64EEAB5EF19ULL, 0x7813C04BC0D55718ULL, 
            0x745C1DCBC23B143DULL, 0xE6C103B3E94CEFE2ULL, 0x9CAE0ED54E64FFC1ULL, 0x0BD424E82DC0BAEDULL, 
            0xF723A31CB1681F02ULL, 0xE8D41C4D5A35E805ULL, 0xBAB756F021A65C9FULL, 0xC6A26E84A102961EULL
        },
        {
            0x947E594B1093B12DULL, 0x73A42F6922F74406ULL, 0xBB7C3A8EC43EDFDBULL, 0xD981EA252C896ED0ULL, 
            0x54FA419622EBA6EDULL, 0xB27C74791944F07EULL, 0x398F4254BD40D11DULL, 0xFEC110E6999FAFA3ULL, 
            0x98F1A46894C43C6CULL, 0x3C9DECECB1557701ULL, 0x3452928E4D141821ULL, 0x6485D0EB1BA9A5BAULL, 
            0xE782CDD58503D7FEULL, 0x79D02B7B29C85B46ULL, 0x1B7E89CDF0D79A9DULL, 0xE6BA23D72C5B77F2ULL, 
            0xE95ED2EF4756C658ULL, 0x1FB552834D5D726BULL, 0xB65B090008BED91FULL, 0x494AE817ABF91943ULL, 
            0x6D35595E14524734ULL, 0x38A8810B828BE73CULL, 0xF83E5531FBA48311ULL, 0xFF0A27F88195A1F8ULL, 
            0xF6508A8EE2194218ULL, 0x81A0F022C56E787FULL, 0x08A5C38646B4E655ULL, 0xE150D1FF245E5183ULL, 
            0xE6C31F15808344BEULL, 0x1407117B166D8CE5ULL, 0xEC562F9D6624D0D8ULL, 0x9201719F6B25A917ULL
        },
        {
            0xC2C29F5F2F2A92CEULL, 0x4E89E619F618782BULL, 0x6AA8F8FED568D610ULL, 0x5A65B53347F69A40ULL, 
            0x66FDA41A589C7D97ULL, 0xD298E890610CD305ULL, 0xE86F1D1FF29B7616ULL, 0x32D91C211342CF10ULL, 
            0x18F747F327154E92ULL, 0x2A65893B77D66C4EULL, 0xD4DCF94CF2A10776ULL, 0xE343BFB2BC00A5C4ULL, 
            0x7742E3FBFD706ABEULL, 0xB71B3AE110A3D859ULL, 0x728BA4B34A776990ULL, 0x5848E387D2279D46ULL, 
            0x39F7A89CC8FC6114ULL, 0xC95EFACA7CC354C2ULL, 0x33DB69FECD7C3957ULL, 0x30C4F65ADF7856DDULL, 
            0xA8AD771482AC35C5ULL, 0x2FE25C9015BBD7FBULL, 0xE2CA1C7B0C7E3A5EULL, 0xE9812D3AE9ABE49DULL, 
            0xCF245521850E1F7EULL, 0xB1E8D196173B0B89ULL, 0xD28D5B104A31561BULL, 0xBF6F5A328F247FB6ULL, 
            0x74340BB016FD8955ULL, 0x5CA312696EB9496AULL, 0x8F6F76E19E1C289CULL, 0x99F5E82B5DC7719AULL
        },
        {
            0x8275909D7C348076ULL, 0x8324D0230E47A59BULL, 0x9688714529E1258EULL, 0x7A63855681C32A10ULL, 
            0x6DB7872CA793FCD0ULL, 0x064B147E98DF59C6ULL, 0x5C9201D744E73BC9ULL, 0x5A81C19F17ACAF12ULL, 
            0x1E18E7D00420B3DDULL, 0x2170C1A7A658FD03ULL, 0xD00DB92FD271BE81ULL, 0x9DC176659D4F2C7EULL, 
            0x6091565D6506FCA1ULL, 0xF802B740601C6B28ULL, 0x1F24B5DDB2254C5CULL, 0x2F2F0AF28F1BDE79ULL, 
            0x5343458EFEDDF851ULL, 0x8EEAEA9C32B22679ULL, 0x860F075125E072ACULL, 0x009A0ED061B473DCULL, 
            0xC5F0D0A35C4074CDULL, 0x4D8E221D83BC61FAULL, 0x41F680A7B6556719ULL, 0x848A6B8072C54107ULL, 
            0xB4B45FE76241C21AULL, 0x156B701D8CA59745ULL, 0xC3F9B2D0E0FCE17AULL, 0x9C6DE33B8FAB9A63ULL, 
            0xA4257E6C1EA285B4ULL, 0xFA1E28C190ABA150ULL, 0x4EC878909B29A0D1ULL, 0xC437B738193F7190ULL
        },
        {
            0xD6541B9E3CF8F62EULL, 0xCE84AAC3233FECABULL, 0x93F01E8B62D43891ULL, 0xD0A6D77068DCE424ULL, 
            0x27D042D9E2A8F209ULL, 0x193621DACB00D6B0ULL, 0x316E1AD92523DE43ULL, 0x3890F7B185CCF2CCULL, 
            0x2D8ADA2739A1C976ULL, 0x722A477E34DB3874ULL, 0x7B0881A0C554D9D3ULL, 0x22D24CA9EB9F335BULL, 
            0xCC01B4BEBD9003F9ULL, 0x1C4D0F8D84851330ULL, 0xA942A10786887A33ULL, 0xF66D779206C72CFBULL, 
            0x915D42522A43F3E1ULL, 0x95D5096A77CF1DB6ULL, 0xF3FF32940FF1BCB8ULL, 0x3EEF0D8B4C42182DULL, 
            0x6B4A0CB3568789F6ULL, 0xCAC99BA77481BF63ULL, 0xDB4ABD9407749124ULL, 0xB68B005D70207C13ULL, 
            0x0B7940BFA3653A0EULL, 0xC5CECB3042369E40ULL, 0x8D214B226BD1F08AULL, 0xDDA396136E54704DULL, 
            0xD2B1B168862F8AC7ULL, 0x3BBA4EF770CED738ULL, 0x0A78B166547D7174ULL, 0xA502D272A74106D1ULL
        }
    },
    {
        {
            0x3D20FA42685DC497ULL, 0xFCBFB5D39AFC136FULL, 0x423D8E6B3CAB24A4ULL, 0xB496226E701098CEULL, 
            0x9EB2751B40757DF3ULL, 0x787A1DE0C840B5CCULL, 0x28B29A441A93C523ULL, 0xC91E3EFE2328EB0EULL, 
            0x9213E690C06320DAULL, 0x192C671066F6462EULL, 0xB3A436FA8EF3E8AFULL, 0x6053FDBCE2E0D1C2ULL, 
            0x380AC455067189E7ULL, 0x8FAA7559DB62EFF2ULL, 0x9343C1D975F5BC1DULL, 0xA16AC6C1432E63CFULL, 
            0x53036FF95CD7DE26ULL, 0xF5A5FCF1B10F2F5CULL, 0x69E1F8CC33778E3CULL, 0x29CC0301EBF9C20AULL, 
            0x640340C5F5755192ULL, 0x37660ACCCD777EBCULL, 0xE001A2A42ABE2C8CULL, 0x5C790DE40EDCF052ULL, 
            0xAB9B8A6BBD6DDEBDULL, 0xF6CEF99C13BFFDD9ULL, 0x0BAAF96B9B9BC6E0ULL, 0xCB0C88DC051000B5ULL, 
            0xCFC670D3CBBDFF53ULL, 0x76DB9649A81D9C2FULL, 0x10BF40023EDAE863ULL, 0x21964052EB70E613ULL
        },
        {
            0x6A2A5B1FEE324700ULL, 0x88029FF645CE025EULL, 0x0D3150E0076A228AULL, 0x4CF406F16EE84C4BULL, 
            0xE0E4856F7F330D82ULL, 0x9DD5E5A0D05D109BULL, 0xDAC0C35B420BE89FULL, 0x5C5E4AC243E6A382ULL, 
            0x23FD1BFCA2CF82CCULL, 0xC56F49FE13AB3A44ULL, 0x3AE58C6E574980A7ULL, 0x6DAE6EF1BCF0B4F0ULL, 
            0x7B07E99C8F15DCB4ULL, 0xDDF8B6BD031B41A6ULL, 0xB098F999E0C9135BULL, 0xB3CF339ADF244903ULL, 
            0xF08DB61993639F9AULL, 0x5B173E4C5EBBE8F7ULL, 0x1FD589264B17C8FEULL, 0xF18DFD9C64CC8115ULL, 
            0x640D6149A43FFE0EULL, 0xFD6CD9B323C761F9ULL, 0x1D32DA7B163E035EULL, 0x3E3DE8E97C583277ULL, 
            0xD2CBA114B555DC29ULL, 0xB4CD5B90D5772D6BULL, 0x38FE10C6DFC05FFEULL, 0xCB19F9BACEA3B017ULL, 
            0x7CDAD9C55694EE7DULL, 0x5F33247A1AC6EEE1ULL, 0x6B66390301582E80ULL, 0xFB2E083AE78BB243ULL
        },
        {
            0xEF9FB84B4FB38D6EULL, 0x976B17616E400763ULL, 0x16F39B32BB52474BULL, 0xE5391EE7CFD6310BULL, 
            0x7F4478B8EF9B31DBULL, 0x9665C291C5EE1E8CULL, 0x66D18770144C35B0ULL, 0xBFDFCD80FD55C3E8ULL, 
            0xEE520DD5BA6BEEFCULL, 0x6E17A3CD2C5C1197ULL, 0x06B8F1DCA1740D6FULL, 0xF48F2B5523802E5AULL, 
            0x04A33F5BC3536207ULL, 0x5592C9CC5A095E1CULL, 0x0F1CA8066E055F16ULL, 0x686448EE66A37B03ULL, 
            0x11B21EADEE8623B1ULL, 0x4363DBB58B3C996FULL, 0x9EC5174E85C99B4BULL, 0x634A2CD0644E3328ULL, 
            0xF75E8089D3E85F42ULL, 0x0A5B178C633E07BFULL, 0x460FDE83461B6F5DULL, 0x5909083EA7FA312FULL, 
            0x38CF9CE31A8700D1ULL, 0x9AFF6211FED0C857ULL, 0x654CE32834B9C9E9ULL, 0xE21492386082094EULL, 
            0x747055AEC94D1CD2ULL, 0x49E87E70F592A4E3ULL, 0x663341619313DBE0ULL, 0x982C46F186AEA3ECULL
        },
        {
            0xDF6D236D1E4D1191ULL, 0xBAC31984FFFD5A6AULL, 0xDB98C086A399C7CCULL, 0x8476288C01A2EA86ULL, 
            0xFC4399F50A8C1358ULL, 0xFE673B2329403D04ULL, 0x7CB10C9C14E101F7ULL, 0x91379534CBAB2D78ULL, 
            0x542441F7CFC470CCULL, 0xB41083816CA4D4CAULL, 0xFE9E465B9B17B3AAULL, 0x0693A766BCF839A0ULL, 
            0xBA86FE98A957DBA3ULL, 0x6375DED915E37CEDULL, 0xAC5404D73300502BULL, 0x635D45B66985243BULL, 
            0x2C0BE026BEB0692DULL, 0x6316336ECF0041D6ULL, 0x5ADFC7843E0BF1A7ULL, 0xF002AC245AB6E6D5ULL, 
            0x07A6AC4FD028249DULL, 0x1E905A664AFFD2F5ULL, 0xA0D94BC466791035ULL, 0x2E19005FF05F8019ULL, 
            0x96656E68CF02D23AULL, 0x1E57275EA1DC42BBULL, 0x767DE36E852D5F6DULL, 0xE9EDF5AC3613CB25ULL, 
            0x3FBF455F0315E852ULL, 0xD0A1EF10AFBE2D65ULL, 0xAFA82A6CDC226F4AULL, 0x2ECD543305BB93BAULL
        },
        {
            0x7B62D23D41367ED0ULL, 0x961777B52C43BBAAULL, 0xC61488B547747A0AULL, 0xDDD2BF347206C1C8ULL, 
            0xE6D2E641276F9ABDULL, 0x91303FAEEE58357BULL, 0x29440D719FEBC516ULL, 0x586E7DBB817B20B9ULL, 
            0xF350B1BBF4C24235ULL, 0xB3062E70144C479CULL, 0xBDD9C8329D389F27ULL, 0xC1D3DD90EE05660BULL, 
            0xB79411F2E17FF8FFULL, 0x2A24ABF09A23D754ULL, 0xC72C4DD87171A449ULL, 0x8666E3E8DC2B0D4AULL, 
            0x435566CDAD926714ULL, 0x24F9D61FA856197AULL, 0xD5ADC2B92332DCE8ULL, 0xE8DB4D0AADD45870ULL, 
            0x65E61542BD5382D4ULL, 0x61E43A2C97B532BAULL, 0x189735647341FD38ULL, 0xD707018FC62FE317ULL, 
            0x272F676385FC853EULL, 0x6154A307C4544F2FULL, 0x3D60BBB6FEF4ECCAULL, 0x2EDF8056BA3F517CULL, 
            0xDFA92CCB156EC087ULL, 0x68195B44E138600AULL, 0xB2AD2104D1F727CCULL, 0xF9A182E2F8B680B6ULL
        },
        {
            0x95A5ED2B441B394DULL, 0xE7910DD9D1F5B16FULL, 0xD66D7899CEF9BEDFULL, 0xEBA265C6B3CD2161ULL, 
            0x5616B01D01599653ULL, 0x264C3F8702FE91DCULL, 0x3BF87466D9F02CA0ULL, 0xA18588FC3FC3A417ULL, 
            0x9ABBFB3B071C583DULL, 0x891BE21013A37165ULL, 0xD7DFB8B4DA6A9225ULL, 0x6F744B3827241339ULL, 
            0xB75C8F15AF60EEC6ULL, 0x1224349A1EA387F5ULL, 0xDD01897F57E331BAULL, 0x550CBC32770EF71BULL, 
            0x6DA2DC3952A9319AULL, 0x8DFDBADA8FF6F032ULL, 0x8E8C049BB03BD64FULL, 0xF4B48DECDCDFBBB6ULL, 
            0x32B79D934F20DAE3ULL, 0xE2CF75154882F8C8ULL, 0x0C1470FC98E1C699ULL, 0xCB992ED5349A677FULL, 
            0xDD40B90733E5E105ULL, 0xA3F7F36EF00B110AULL, 0x205C3C9CAE48FA36ULL, 0x6A39949305296634ULL, 
            0xC0076E59D1F240D9ULL, 0xA53386A082BCE84CULL, 0xE38C12EE6B206E6FULL, 0xCA5A70B1ADFABB3EULL
        }
    },
    {
        {
            0xD2827E12C0978529ULL, 0x2EA214C555840C29ULL, 0xF8B9C695BE5A233DULL, 0x0EFA6992CE1D4F8DULL, 
            0xB1ED2AA999CB903FULL, 0xC492AE33ED54FAF9ULL, 0xEE13D1032EF86F4BULL, 0x9E272FB6E2F6CDDBULL, 
            0x059B0E054001E770ULL, 0x31E73B050E445B3CULL, 0x41B1637075587E9DULL, 0x69A55D3071CDE294ULL, 
            0x3D3075203C4A8A19ULL, 0x0A02EE91897C4A1FULL, 0x154DD491E2F0E6D5ULL, 0xB35C0A092AB1D71EULL, 
            0x0C299F1A16F51FF4ULL, 0xCC1DD12F683290C6ULL, 0x2F7E3098079489DCULL, 0xADFA530F54B64DAAULL, 
            0x145B8B5C183BE769ULL, 0xE5CFBE483A54106DULL, 0x8240B2D259602459ULL, 0x5183743B91BB0DC2ULL, 
            0x8E8705E7320E7C67ULL, 0xDF73B88C92B80078ULL, 0xDFE5E84402A2D60CULL, 0xC453731C37E59CB6ULL, 
            0x52FA781C8BF18DE1ULL, 0x66245A6241E66B54ULL, 0x7F6A113BE4799501ULL, 0x504750B7B8198EDBULL
        },
        {
            0xED1EDE6847856321ULL, 0xFFA8D70E190C4051ULL, 0xC944A62F93038FB2ULL, 0x14CCD56648E03B8CULL, 
            0x18A527E03C51E577ULL, 0xF61006AF0887789CULL, 0xA03C9868367C96C6ULL, 0x2FD2BF2BDA8EEC68ULL, 
            0x6B32F1391E09E017ULL, 0x2036985F6A3D6DA1ULL, 0x4485F3DDAB2BD4C9ULL, 0x47A57EE4EE904E3CULL, 
            0x3F84DAF225E12AC8ULL, 0x36175F7C6386D1FEULL, 0x87D81693739D05D9ULL, 0xDD39622C106E9123ULL, 
            0xC60D5001158D0536ULL, 0x3732659ED790A9A0ULL, 0x335C6197850E8D99ULL, 0xD91940CBA192AF34ULL, 
            0x73365057523B3DA2ULL, 0xC7B4613ED7F12701ULL, 0xE681E1F6FDCA9964ULL, 0x5CF796736DCE020BULL, 
            0xEC03710E1880CDF5ULL, 0x42D5AD4393768229ULL, 0x2A1F3959F82A9587ULL, 0xB016DA6594C23169ULL, 
            0x0C5D1BB47AE0CF13ULL, 0xCE6812D326D2B49FULL, 0x587D53074B403DF4ULL, 0x8A2716599A5C455DULL
        },
        {
            0xC440FEBE147404B0ULL, 0xE674BF9FCA0BF50AULL, 0xE94DBC86EA9FE218ULL, 0xD75E313C3834AEE3ULL, 
            0x173EFCA37D564CC8ULL, 0x777A417F03B66CD4ULL, 0xC7F0BF3E9332BB39ULL, 0x133B9F19A9F3DDCEULL, 
            0xE3E7A0A19759E243ULL, 0xAB42A3157FDDEB1AULL, 0x097D729D14E7CDC7ULL, 0x471B43C9CBBD688DULL, 
            0xA3C8786547E9D1CCULL, 0xD4450A26B003297EULL, 0x6D900301EF0E9A93ULL, 0xBBCB0B2CE439718FULL, 
            0x3606B0ECF3E4EBFEULL, 0x52276EF709FF7E2EULL, 0x988F87A0F74B2DF9ULL, 0x4BFBF0EBEB1AAF3AULL, 
            0x50607AEF28E07950ULL, 0x9E339B4C73A63E31ULL, 0x72DB91BAD410EA6BULL, 0x643757101F9670D2ULL, 
            0x2117FACD7146F170ULL, 0x1943A7827B001E75ULL, 0x629D2AF509272446ULL, 0xFBC1DBBA71F53AAEULL, 
            0x8880EF28DEBF6D62ULL, 0x5076666C1A06806AULL, 0xFE72052A859354B2ULL, 0x6ABF8DCD072C635FULL
        },
        {
            0x10416188D6C3CF8AULL, 0x57C661D287B03769ULL, 0xDB2A71F0751A99A5ULL, 0x8ECABB8D55E929C8ULL, 
            0x2C60FC8DD30ED271ULL, 0x63A74F3D5D02624EULL, 0x98374E82DB862D6DULL, 0x9992F6DCC134BBDEULL, 
            0x10E8A59D6B023B6FULL, 0x6D47CBEBA3A09DBAULL, 0xE55288804F3294CFULL, 0xE410A63B22CF1D0BULL, 
            0x2E571BAA0A01C35AULL, 0x8CEC6EF7BFBED873ULL, 0x1D3BCAD7CD06FD7BULL, 0x1CA9677A236C6684ULL, 
            0x7527A0FE9020A536ULL, 0xF58D4A794689B66FULL, 0xB9C8B019DD7F05A8ULL, 0xE69358B8AE9D5D4FULL, 
            0xCF75905E11077A17ULL, 0xF12487354E525334ULL, 0x12A56DE11E8F11EDULL, 0x1E4E0D49A71A55D3ULL, 
            0x323670842B4B5060ULL, 0x17E3ED4C84F36CC5ULL, 0x9C026990CC101488ULL, 0x2BDC9043B8D8AD02ULL, 
            0x0265BE7417414FD0ULL, 0xBF3B0D9B9370C357ULL, 0x6BFE908414EDD500ULL, 0x3EC31A101061B4B3ULL
        },
        {
            0xDD002A48FD3C3107ULL, 0x962F9BDCF233429FULL, 0xEF10167BBC3A0D79ULL, 0xAA41C253C355EA1FULL, 
            0x362794327E59214FULL, 0x01C7D34246F04C4AULL, 0x10632561B068FD6DULL, 0x1B0E7BD5EA509A1BULL, 
            0x89E98A4D924EAB15ULL, 0x71E0E3635F84A492ULL, 0xDC63F5C7DBC51957ULL, 0x1BE4CB3E49676C15ULL, 
            0xCE37CABDEBFE0402ULL, 0xFD71192E0EE2B8BDULL, 0xE5C7994B8B2F458BULL, 0xE2080F027F50C5A6ULL, 
            0x41D9BDC2B63B4D8FULL, 0xEC0761A0937B83DDULL, 0x3957361549389F4AULL, 0xC120F59EDFBDF950ULL, 
            0xBEEDF41D4FA77939ULL, 0x9C1DF95DB421588DULL, 0x97B1B2E1FCD0C06CULL, 0x4566FA8421A8F6C6ULL, 
            0xF515E2F956D3222EULL, 0x0B7B66C940C69479ULL, 0x507927D5FC3C7BE7ULL, 0x543DDABD7B40AA37ULL, 
            0x2CA5AE8AA39B794EULL, 0x946C5C829F1B8E20ULL, 0x12FEA5E260EB794BULL, 0x4C69D9441B1C63B8ULL
        },
        {
            0xB4568948FEDBB3FFULL, 0xCD44CF0394166AD1ULL, 0x9E0573280AEF2DFDULL, 0x56AB78C9950CF50FULL, 
            0x38FB5765C7B319CFULL, 0x11A0490AEDEF3B4EULL, 0x22523384A1CA510EULL, 0xE49F6D910F1BD00EULL, 
            0x85F6A0D59FE21786ULL, 0x5A6086E2605BDB13ULL, 0x6899F9BDAE111F6BULL, 0x56146B1F37F0E860ULL, 
            0x2B2A42F9843F56C7ULL, 0x3329BE409579882AULL, 0x8DEF7FFFF56D0F0DULL, 0xCE016ED9E35831CFULL, 
            0x6DD827A8FBAE101EULL, 0x395C19569B7F2323ULL, 0x9083D71BFF987ADDULL, 0x75DDE68A40DC213BULL, 
            0x67B9E2A9DC630EF0ULL, 0x478C81F148D00E10ULL, 0xB0B7E3B59D98ABA7ULL, 0x5A4C17DD7E619898ULL, 
            0xE1984CB170F64487ULL, 0xE0CBB1C747DCBEE7ULL, 0x2AABFE1E107CA9DCULL, 0xE84B06AC7CC15577ULL, 
            0x28DF91B47D42DE07ULL, 0x59B38D889AB989C4ULL, 0x88DBA18AEE090CEBULL, 0xCF71F5DA1E0B3D46ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseEConstants = {
    0xFCE3E5FE9FD38171ULL,
    0x55E8653398357BE4ULL,
    0x841DC1E0882FFD1AULL,
    0xFCE3E5FE9FD38171ULL,
    0x55E8653398357BE4ULL,
    0x841DC1E0882FFD1AULL,
    0xEDF540346B7A594FULL,
    0x629D3B5CAC9B71B5ULL,
    0xF2,
    0xC7,
    0x1B,
    0xBE,
    0x17,
    0xE7,
    0x74,
    0xBE
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseFSalts = {
    {
        {
            0xA8397BE406BEBB36ULL, 0x9AFE155F4ABDEF58ULL, 0x35EB4155FA76B4CBULL, 0xAAD25C0D3347E864ULL, 
            0xECDA09F0E093DB65ULL, 0xAD098B5A0FBF93EDULL, 0x4BDE4C909832DEA5ULL, 0x4B8448C86ED73ABDULL, 
            0x9B073AEEC74B7866ULL, 0x2F4B7A21C0BE957FULL, 0xBD9025C8D0517E8BULL, 0xDC9B839895ECFFE2ULL, 
            0x73E1B7F1344C77DDULL, 0xB4690A3589E06E64ULL, 0x8AEF3258A57470A9ULL, 0x2A6CF4E92BA22DD0ULL, 
            0xEDB9413D2004C268ULL, 0xFEC0DEDAEA5FDDC5ULL, 0x21C8157D84AFBA69ULL, 0xD8D00487587E8887ULL, 
            0xC9D541C52C25E013ULL, 0x878B32D516B8A6F3ULL, 0x59263D92AFDA27A4ULL, 0x8326B9783461F96FULL, 
            0x8EDB6A6CA3CAA826ULL, 0x220D6D1496338DD0ULL, 0x646900255CF9BD5EULL, 0xF64D286D90786574ULL, 
            0xAEE8A112C241549DULL, 0x27A41CAD32ABECD2ULL, 0x6C90A60509482607ULL, 0x7820AF605563B0BBULL
        },
        {
            0xF8892AF017F4CC35ULL, 0x1A084172FB5A0EA0ULL, 0xB7003DD0E06D4750ULL, 0x1EE7CC934E2A82C7ULL, 
            0xF1C681AD880F7677ULL, 0x977F09B0C94F5623ULL, 0x6F0B254BEAC5A386ULL, 0xB08CFF8A2A4633DDULL, 
            0xDEC07D1BE9756C3DULL, 0x121F4FE2F9281887ULL, 0x21218F4EC3891535ULL, 0xE486B914EC9DB59FULL, 
            0x9CAA56B324B2263DULL, 0xC1EF796C3C4BFE48ULL, 0x43F90C5C48DBD155ULL, 0x8560FF0099B9277CULL, 
            0x3CDCAD06684EC030ULL, 0x11466267C2BEF4C4ULL, 0x7B7E541D83B836E8ULL, 0x4E714F81BC53DD34ULL, 
            0x82102532E62E7A02ULL, 0x2574570EAA5F087BULL, 0x4550ABB55A4ED75DULL, 0xB44E2373213F0FDBULL, 
            0x651221B7A380F149ULL, 0xA2ADA2284AB336A5ULL, 0x49762DA66D6D5468ULL, 0xF38335E42BF96F7EULL, 
            0x64649BE6B5995A5FULL, 0x5E4919A11D5C01FBULL, 0x75A555BDB816975DULL, 0x24C0466567E58020ULL
        },
        {
            0x60DDCDA23887DC13ULL, 0xD22D36CFF9C0BA05ULL, 0xA4B56DB2AFBF302FULL, 0x8AFAFF873D17F85FULL, 
            0x597BFF4E67A95439ULL, 0x2C767D7557D5EFBDULL, 0x38CE148B11950AC5ULL, 0x9CD58C2BF63B4295ULL, 
            0x0C6194C9E2A1DEDEULL, 0x691D462800B5F3D5ULL, 0x08D767FF9A908425ULL, 0x70396F38E8266FEDULL, 
            0x2B11BB1418BD806AULL, 0xA7B7C122FA731343ULL, 0x5C074FED234391EDULL, 0x2D06A7F8AB6719A4ULL, 
            0x82626666E2E2447EULL, 0x3D8242BCBF69829BULL, 0x6C984BDD08C4DEDCULL, 0x47E7949957B5DEADULL, 
            0xF5A4C6F1EC1AA424ULL, 0x131B8B4B0E189BDEULL, 0xFCA5D477943E8169ULL, 0x7596FC1008D7A81BULL, 
            0xF76471A8D843E4FDULL, 0x7BA90C3F6C4F5659ULL, 0x117656923A26FA3BULL, 0x909B7D21194D9055ULL, 
            0xA0CAB54931B28566ULL, 0x29BC3402CDA335F7ULL, 0x89B83156A776E491ULL, 0x4E17837D6B911F2BULL
        },
        {
            0x3BB015B224EE57B8ULL, 0x1E7A76EEA5DC032CULL, 0x9E09CFCA67E59A6DULL, 0x6848A8A9C0954931ULL, 
            0xCBDB19724D80FACFULL, 0xF07BF9D73D380979ULL, 0x2AE2E995B1AB346BULL, 0x587FFB5C739CDDC6ULL, 
            0x3DA0FC60AE6E7C0AULL, 0xD28E3E66BC18B0F5ULL, 0x142CB19108E7E534ULL, 0x58B555A1087F7A1AULL, 
            0x168A72AEB710807EULL, 0x9EFA6B0C59500F52ULL, 0x60C44E7199264CF6ULL, 0x76E643F530F84AEAULL, 
            0xC81022995B02BDF2ULL, 0xA288F29DA273CAD7ULL, 0x3F0961C3260B53DAULL, 0x2D3C33FD861DE167ULL, 
            0xC048DAA000DE20B0ULL, 0x1DDF2D192A22596AULL, 0xBDAB58E9A84D92B6ULL, 0x46B7921CCD7CEFCBULL, 
            0x13A4AAF503DFFFBEULL, 0x3BF9623681070A08ULL, 0x4711070C40E3F9A1ULL, 0x48EFDCCF7FB5C466ULL, 
            0x5AEBD20805234AD1ULL, 0xF5605CB2F9263C1DULL, 0xA919DF44F81CC236ULL, 0x5947C06723993707ULL
        },
        {
            0x14C90A4492BFA0FBULL, 0x62B421EC5FA0347EULL, 0x6B77DE5B6972E2A6ULL, 0xBFC8889F8154EEBAULL, 
            0x65ED4C0AF50EC50EULL, 0x8509B900FFE7500DULL, 0x453FFB21AF0BC30BULL, 0x94239D4347039204ULL, 
            0x0421E4443CA4DD84ULL, 0x59642995B15151AEULL, 0x7422A38A8FD3C244ULL, 0xB8507472A6B57353ULL, 
            0x355A53A3715BA690ULL, 0x489F375BEDE7CC3AULL, 0xB9D6DCC1FB18CD0AULL, 0x1289136F126DB577ULL, 
            0x4CFE4DBDB6F90459ULL, 0xD480A1F2615261C5ULL, 0x150ADD981A4AF54FULL, 0x8D4FE7D338DB64EAULL, 
            0x51DAC856E5BDBA92ULL, 0x97260BFAB57F3B11ULL, 0xAD56E780391DC1CFULL, 0x1B5C668CB06334C1ULL, 
            0x29658605661D8ECFULL, 0x7AF3B2493FCDB16BULL, 0xB4BBF073A1A8ED10ULL, 0x65024B82ABAEA027ULL, 
            0x29214B3FEEB94B66ULL, 0x9EC6CF13FC47B579ULL, 0x113721842C2CFE99ULL, 0xC8845C8C73C6408EULL
        },
        {
            0x4F927C6F7E55C5DAULL, 0x062E25E60CA15D7CULL, 0x4A410C2C3643F820ULL, 0x53BD53539D41F62DULL, 
            0x9BA02ED4473D2CCFULL, 0x6032CB39D16448F2ULL, 0x0FF49A361AE2B84AULL, 0xCC0AD35C5CB42848ULL, 
            0xE2DA8A58FA3C82E7ULL, 0x25C6786ACFF94245ULL, 0x81A7822E7D61FF0AULL, 0x5ED421476AC07EFEULL, 
            0xABA6C3803FEE0BF7ULL, 0x9ED72F8776F7876AULL, 0x783A1F151176E447ULL, 0xC287FC6BA044801BULL, 
            0xC7173442CBF19458ULL, 0xD87187F8B7BC1798ULL, 0x80754894998EAA48ULL, 0x2D4A3B5220AB2668ULL, 
            0xFFC785E859BB63BFULL, 0xA1853112386040F3ULL, 0x5E5FE4AD4B21B99EULL, 0xBE66789BDDD08AD2ULL, 
            0x928E8174C46D5CE0ULL, 0xA29666AB46714A97ULL, 0x929774A0E2EB0AA2ULL, 0x81A7DB3D57BBF282ULL, 
            0x63B33217074F0269ULL, 0x5231047FEA37591CULL, 0x6521F67932DCFE78ULL, 0x73671EA9B30CB39CULL
        }
    },
    {
        {
            0x4F89E1181E8FEEE4ULL, 0x34CD78F31BD5C699ULL, 0xC6B3F911E798BF05ULL, 0x5E645346CE6E2C49ULL, 
            0x959CE570A4B8C983ULL, 0x6ED8C642CEC9BE4BULL, 0x0381ED620C8C72C0ULL, 0x5D76A38AED3F1131ULL, 
            0xAA97FEF9D6CF4163ULL, 0x723352D93B5277C4ULL, 0x45C3A983EF17FC8BULL, 0xF30867C6D9F9DAEFULL, 
            0x5600D5C036255FC0ULL, 0x20F825231D23824AULL, 0xA99BA6EB0A6EE766ULL, 0x56884DFDE710FA99ULL, 
            0xEEC50D129E11B8DAULL, 0x1A54B3A3C08B7CCAULL, 0xCEEF6CB2C59DEE92ULL, 0xA65868F2B81CE245ULL, 
            0x4D373E854BFD231AULL, 0x06C4948CB5F6C7BCULL, 0x506E6DF85FD3D08EULL, 0xBDB3EE971E9C85F0ULL, 
            0x0C58EC12D881CA16ULL, 0x4F0AF33D58F45E2EULL, 0xD560FD634ABD84FDULL, 0x281A81FFA05E84A6ULL, 
            0xBA5CFF7DCE77EB0CULL, 0x0268B5C8FF1EF28DULL, 0x0606692734DA426FULL, 0x5E88CD170B6B5C9AULL
        },
        {
            0xF201B701AE2C8427ULL, 0x21D4DEE41ECDA62AULL, 0xA06B9A618FECBE78ULL, 0x1AC9A8D27D911633ULL, 
            0x8AF73AED788460ABULL, 0xD4DA90EB30F58B23ULL, 0xB6BAD1996653A2CDULL, 0x195B86C082909536ULL, 
            0xF9985CCC33CF5B80ULL, 0xDB5A51F102F7B853ULL, 0xDBF34216B2872A25ULL, 0x1BFB86399354AFA6ULL, 
            0x9755E1B08E2CDEDAULL, 0xAE086140D4FBB57FULL, 0x70E18DA934D363F4ULL, 0xF1A375C656BF4441ULL, 
            0x9C34B33FF98FEC27ULL, 0x59CF8E046485B322ULL, 0xAFFFECE3F176A239ULL, 0x8DB2249D1A96B00CULL, 
            0x031AE62CD4F08F5AULL, 0x7798E5B1EB343933ULL, 0x93F242094E08C3CDULL, 0x33EA82B54862B600ULL, 
            0xBD362AD63749C494ULL, 0x8B9B3C80BDC15C9AULL, 0x536D1633BB8A917CULL, 0x98550FA5F4315ACEULL, 
            0xC45893058A846FD2ULL, 0x8267BC3893BE86FCULL, 0x3638B0FF413CA643ULL, 0xA3484C569F00C137ULL
        },
        {
            0x861713EDF875FBC9ULL, 0x70921E0A0AD14EFEULL, 0x5D78367CB7EFDF99ULL, 0x49E9A27247DB40CFULL, 
            0x6E115B35ECFE6994ULL, 0xDCFB84E2A4E1EBE2ULL, 0xA7814E8421980B98ULL, 0x11AEB182D31D65C8ULL, 
            0x114FA1FFA66488B7ULL, 0xCBE18E903090CDACULL, 0x6287CBDB3708A586ULL, 0x2C2790C5EB2218C8ULL, 
            0x8ED5A13003AE8D06ULL, 0x8EC1D27DECD6FA25ULL, 0x6ADCDEDE245C1305ULL, 0x56EA0D6C9CDC4CEFULL, 
            0x263EB51C14DA1522ULL, 0xF9BD7BDFD0A0B48CULL, 0x8EF34780CC5325DBULL, 0xAF6C084495EF89DEULL, 
            0x1FFDF884B7881B93ULL, 0xDC4673F465CEB717ULL, 0x3FD2915774567FFAULL, 0x4D355BAA1235954EULL, 
            0x0EC3C223F69017CFULL, 0x22C7DAF57D334904ULL, 0xE279485F47A39BFFULL, 0x9C2068803EAEA905ULL, 
            0x196E1590FF8C83F4ULL, 0xFB2AAE61B26FFA80ULL, 0x4930664EFE2FD675ULL, 0x6E96746820B137B3ULL
        },
        {
            0x2D2D82F8968E7ABCULL, 0x4E6FBB586697B85FULL, 0x93796A0B7D103AE3ULL, 0x83A2DA573B5D1365ULL, 
            0x796394E58588824BULL, 0x951962EA703B1470ULL, 0xAA5F2A03E376358CULL, 0x5E9604F83AE19DC6ULL, 
            0x381FCB9C14BDAF10ULL, 0xE931C451F7058085ULL, 0xFB8BB5CF1BB0CF6FULL, 0x2595A159BC2EEE4BULL, 
            0xFD7589C57DBE0C64ULL, 0x4919A339DA15C749ULL, 0x55A55C8B88ED34CAULL, 0x70299D458D1A42B2ULL, 
            0xE42A24804B3F5131ULL, 0x666C0A994CA3209DULL, 0x0B1B436B5E60F375ULL, 0xBD2003E1841C67DAULL, 
            0xD236678F716A2716ULL, 0xF8080FE0BD680894ULL, 0x79081C632C67BC4FULL, 0xCDE637C781F42F97ULL, 
            0xC5D9BDD37FACE0A0ULL, 0x97222462858A058FULL, 0xFBDB3507A181C83FULL, 0x0C6089D003FA8078ULL, 
            0xF4C3DE9231843CD3ULL, 0x213EAEE25C1BAA04ULL, 0xC53B9B3473608A16ULL, 0xAD33B55A355AC98CULL
        },
        {
            0x23B0FC666582F2BFULL, 0xECAF6399A75612E3ULL, 0x1DAC42A75DD8D48BULL, 0xA583544E1548FCA4ULL, 
            0x1909CC4F6C209D4CULL, 0x31E2DBC8786CF803ULL, 0x3114746700A50BBCULL, 0xE4E501D77CA3DCFAULL, 
            0x4F0266C959151FD4ULL, 0x672E8C4F4AF66E32ULL, 0x877C386A303D48F7ULL, 0x33A60BDEDB520A15ULL, 
            0x1AC7D6C5E15002D8ULL, 0x20B84FFDC61039C3ULL, 0x3ADCDB07A79A0F3EULL, 0x147316D3394794A2ULL, 
            0xAC8A1F8D29209131ULL, 0xCE96AD686F2E9DA3ULL, 0x9A67C34009D3FF02ULL, 0xCCC1ACB511FBD007ULL, 
            0xA02932073E36608DULL, 0x7C75CCE9AC70E32AULL, 0x00185FFE9A60BF76ULL, 0xF804BEC934C72A3FULL, 
            0xC8EC4EAB94AFC360ULL, 0xD2241517686B7717ULL, 0x44137CFAD2A512EFULL, 0x47F12C2553CB1425ULL, 
            0xE467BA09D026F302ULL, 0x882F361CAEA8580BULL, 0x0AB902FF0707A709ULL, 0x42E96219B605FD3FULL
        },
        {
            0xED4E0F30EA7BB5ACULL, 0x0F37EB8B17E6071AULL, 0xAB77891CC8AF781FULL, 0x5D80CE7AB6F7E563ULL, 
            0x64754FEB06E013B1ULL, 0x4896F271C8444FC1ULL, 0x4FA0F7C1682DDE78ULL, 0x68CA7E76EF40F13BULL, 
            0x82C94671784E5BE0ULL, 0xCEA72FEE870F3944ULL, 0xE20C52D3D7864A78ULL, 0xA05BB40F5997EF23ULL, 
            0xF486B2C94832CC84ULL, 0xB9615C7AA22F165EULL, 0x771280CDF4D0C3FAULL, 0x4E1E2FB3EB318892ULL, 
            0xBF8B761059E1C08AULL, 0x6B58625170506152ULL, 0x8990331A7431C1B9ULL, 0x1D663191169238F0ULL, 
            0x3CB13E3A7D4604B6ULL, 0x8F3A31778CE8348BULL, 0xBC50F0BE139449A9ULL, 0xD0BBB4E6ED710B88ULL, 
            0x3A399B7DC77966BBULL, 0x0F68E1D4D7C3FFF1ULL, 0x3F4FEBE794527464ULL, 0xD231D69A0B28C603ULL, 
            0x82AC1AD526C79492ULL, 0xAEBD99460F9B1F1FULL, 0x32A57905776E8933ULL, 0xDCC58C427F5AB5A0ULL
        }
    },
    {
        {
            0x4D95172BA00F99F6ULL, 0xFF670C6E99E0CF5FULL, 0x90C125FABE1EE643ULL, 0x5A1F71BCFC834147ULL, 
            0x5494106F8F6D5A9BULL, 0x9512F3E7D6C4F4DEULL, 0x686AD1753A31EBE4ULL, 0x1B4A9AC4534315ABULL, 
            0x1BF79F5F3D686991ULL, 0x78DBEEC2AB32C7C8ULL, 0x705A623FBE79FEA8ULL, 0x1F857856121537BDULL, 
            0xB4BB9F4687D3E6CCULL, 0x234127FBA484D88BULL, 0x09F5887002797617ULL, 0x318B79AFF43FAFFFULL, 
            0x6042977C1F5C7279ULL, 0xB034CB33E9AFC0E9ULL, 0xFE146255D475A0D7ULL, 0x51696F931D325B19ULL, 
            0x63D6FAF12CE5DA1AULL, 0x97B4ACF7FD3661E1ULL, 0xCE22156ACB80AC8EULL, 0x2C05299B84DF4692ULL, 
            0x2155E67EB9F69813ULL, 0x32C1F8BA9F8218B8ULL, 0xE0B6059CFF5F9883ULL, 0xCD1AFB5CE9BFF748ULL, 
            0xCA33816BBB24834FULL, 0xB8F05F8DBC000A93ULL, 0xEA0DBA4E26EF0B77ULL, 0xA91C1209B7DB77D7ULL
        },
        {
            0xD0A29E25221B2AAAULL, 0x338F3626E8E019EEULL, 0xA7EA87798A4201A6ULL, 0x21AD773005D6C64BULL, 
            0x4FCABA2C4FFC4C40ULL, 0xE008A08FFA715486ULL, 0x887D71D1F0E42BBEULL, 0xE818EA1E3CAC8750ULL, 
            0x471A52783B34BC6EULL, 0xEFCFA8B1FC92D986ULL, 0x21E0FEE1A3336149ULL, 0x1625A2DA3A465EAFULL, 
            0x93BE471BBEFFC22EULL, 0x49DF73BFB45204B9ULL, 0x1FC50C17737AEE80ULL, 0x699CE761F07570A5ULL, 
            0xFE27CD7BD2625DF2ULL, 0xB057846B03944E77ULL, 0x84C698D1D70CE09CULL, 0x19824ABA3616B3ECULL, 
            0xAAE546D76019ACEFULL, 0xF4938CF00A2E2DEDULL, 0x0CB81AEF90D233A7ULL, 0xDC3FEAAB4C71DF58ULL, 
            0x82CF2B7DCC8EC034ULL, 0x8BB32C11BA4EC797ULL, 0xF13812E2312ABAC0ULL, 0xBF3FCFC80B53CD2BULL, 
            0x887244728FCEB603ULL, 0xDDF96787BB794B3DULL, 0xF594296AAAE3740FULL, 0x3ED79EF9E9427076ULL
        },
        {
            0x7641FAC09F2757A6ULL, 0x1F756090763EEAA9ULL, 0x43B0C7A796300106ULL, 0x643DCE8B84688C1BULL, 
            0xC83D5C6DC5B2B87CULL, 0x037743D95438A4E8ULL, 0xF71ED7604D734826ULL, 0x779314E77F40546DULL, 
            0x9CA7408A43E5466BULL, 0xC761F6293D0F8E1DULL, 0x093D2A6DBD5656FAULL, 0xD287579A0BF4F6C8ULL, 
            0x752A10252EBCD841ULL, 0x4FE8D91F784A4243ULL, 0x3335CA9426DC52B3ULL, 0x75D6EA56DEAA38C5ULL, 
            0xC5BB3A78C434068BULL, 0x5EEADE256F7D3005ULL, 0x6452B038D229FDA6ULL, 0x61A2E08F7901DE68ULL, 
            0x2B94914758C1F79FULL, 0x5B7EFB1B97AC295DULL, 0xFEF216DE79FC1EFCULL, 0x9A2EBA475BD50B30ULL, 
            0xE19E2C6561711B37ULL, 0xB7661E56BC323FDFULL, 0x8266C1C10973D7ABULL, 0x7984CE41CFF4D4A4ULL, 
            0x52AF37992EBBCEEFULL, 0x18F8F3B2CDD08125ULL, 0x9817AAE2CA267D2CULL, 0x6C8E332FACC56FD4ULL
        },
        {
            0x4C0DCB019D039139ULL, 0x59BFDF57A27B7051ULL, 0xD7326B1817EB42C2ULL, 0xA8060B2DA29B2145ULL, 
            0x2FC7FB69EDBA29D2ULL, 0x14119B899B8BF3D7ULL, 0x0A25432B43CA7A27ULL, 0xEF9BA4DFF505397DULL, 
            0xDDE4FADE08994F8FULL, 0x84D7ADDA75326E67ULL, 0xED94F7B187885C40ULL, 0x0DC162B5FC12DD09ULL, 
            0xF1CDFD52EF0F155AULL, 0xD184A49C800B7D2CULL, 0xE874082AB36067D1ULL, 0x3D71D296FF14C119ULL, 
            0xB49E1BE1D45DEA52ULL, 0x90B8969F0F3FF893ULL, 0x1351FF50B433B633ULL, 0xC35600E3BADD0D7AULL, 
            0x56C4446671D368CAULL, 0xFC7D52E28284A216ULL, 0x89BBB2D317CF40C5ULL, 0x705F5B3615AAA847ULL, 
            0xC4AF85A440BBBA13ULL, 0x6D1C4ECB81B56087ULL, 0xF4914B3C4A5FD343ULL, 0x3E8370CC14068FBBULL, 
            0x3CC9F67B6E06A714ULL, 0x03E964BB6D3601B3ULL, 0x0FBC3FBFB5C30CC2ULL, 0xF78ABE9920D08EF8ULL
        },
        {
            0xA97E4983A8C1748FULL, 0x78D384C81320E7DAULL, 0x59BD8FBB98BF2538ULL, 0x3B760EACB225E0D0ULL, 
            0x1264B7746BE6B1D7ULL, 0xFA93D903193B8E93ULL, 0xA4210D6907794523ULL, 0x35B1617D2DE0CAB2ULL, 
            0x919C4BBBAE9DC921ULL, 0x742E556D7CAB0F89ULL, 0xC5E813EF3414A398ULL, 0xA267C688EB31DD23ULL, 
            0x61D197E17F798EFCULL, 0xE7AF44FD975B77DBULL, 0xA78F8DE98E1EFBBBULL, 0x0A0381A73FCEF372ULL, 
            0xDD120CA6D3FAD0C0ULL, 0x5E9C2B9F65B12249ULL, 0xE923C9B5BFF39787ULL, 0x838D6766AE0204D4ULL, 
            0xCB10A5AD9286AA91ULL, 0xED2782C46AE3948BULL, 0x57C0143DEA7EDD70ULL, 0x962CA2C235804C0AULL, 
            0xDDE4CA73214D2D36ULL, 0x89E66D2450E5FB61ULL, 0xCDC615DA9EC5EDBBULL, 0xE77761C8350C54CAULL, 
            0xE89B33D50A701DD5ULL, 0x1B9E0CCECFD4CB3BULL, 0x8C0E4572CAD2D50FULL, 0x81C0F7949EBD2209ULL
        },
        {
            0x6E512A4AC1DE5697ULL, 0x82A5E5684D736880ULL, 0x76A2609DE4E4940CULL, 0x60C6D7987A795580ULL, 
            0x5FDA840048AEAA09ULL, 0x64689886DA5490C1ULL, 0x69E4E07365626EF3ULL, 0xD27C8B3E75B297EEULL, 
            0x023BDD5993B414C7ULL, 0xC8180F98CCB2F282ULL, 0xA7EA54D7C75EF31FULL, 0x75991A607243BA8DULL, 
            0xA0F33489F6C01F45ULL, 0x6C4D8A96640081F3ULL, 0xE915AE0BEAF70C34ULL, 0xF65B9181534C2881ULL, 
            0x5A662208D9913FF1ULL, 0x7F1F22D7C7FDA6D7ULL, 0xE20222BE07688B07ULL, 0xF4C112A327FCFE51ULL, 
            0x3A312A6547831070ULL, 0xDE293C5141C56E2DULL, 0xB8DE84FF988B6E5EULL, 0x738064E4074CAD49ULL, 
            0x90A1139FC837A26FULL, 0x088A7B59AAF48AA6ULL, 0x607AC6DCF9850E8FULL, 0x6719712D1AB78179ULL, 
            0x9A0D9C426D3CFBD5ULL, 0xA90CB7F111FEB058ULL, 0xFA3CA38026AD613DULL, 0x89E2ADCC40A77CACULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseFConstants = {
    0x42B962BD6AD023E0ULL,
    0xFFE222DC7DDBC2F2ULL,
    0xFE4DB69C667AFE4DULL,
    0x42B962BD6AD023E0ULL,
    0xFFE222DC7DDBC2F2ULL,
    0xFE4DB69C667AFE4DULL,
    0x2DBF24DD326FE88AULL,
    0x3E1203A513EED4EAULL,
    0x86,
    0x82,
    0xCE,
    0x6C,
    0xE5,
    0x81,
    0x84,
    0xEF
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseGSalts = {
    {
        {
            0x616AC236AC5D1594ULL, 0x7DC0EDAA16C22A9EULL, 0x75EAC24FF24C036CULL, 0x5D24F30CF337A39DULL, 
            0x2C24C2325537BE59ULL, 0xC02051A7BCD09D11ULL, 0xE8B25FC9DD8440E7ULL, 0xED2D32BC941F8ADAULL, 
            0xB4C6224D6DFDEF30ULL, 0x37743C2727CD6D23ULL, 0x088643AFD0CCFC9EULL, 0xDB7AC385FEF06F16ULL, 
            0x00C455C75D1A1277ULL, 0xDD9B126338A34645ULL, 0x43B164FBC53E0A5EULL, 0x11D061C5DEA2F39FULL, 
            0xA0A6A22C80070894ULL, 0x053AA2620CB44C80ULL, 0xD62CC2A6C68F4CF0ULL, 0x31A34FA036E6B7AAULL, 
            0x20FBE30F8F9FDC30ULL, 0x9C0CC19B6AD8BC42ULL, 0x43A888CDC6BCABADULL, 0x28EB8D28A4E211FAULL, 
            0xAC8E7B4BC86801EEULL, 0x52988D2F64F5B326ULL, 0x6048DD43BD4F6CF1ULL, 0xD08DF3FB3835BD75ULL, 
            0xB30DD2F420DD9E9EULL, 0xCBA89F655144B17FULL, 0x21D93C237C631376ULL, 0x2C166B9C9634D3C6ULL
        },
        {
            0xA4F7E1E4FE930DBAULL, 0x75E9CCCB961743A2ULL, 0xCB0ADE97B060A260ULL, 0xF25C4F84A2C1A83FULL, 
            0x4A91633915F5BFE2ULL, 0x078AF47C4A575CC3ULL, 0x62F019BA9217D10CULL, 0x4D43229520BB1561ULL, 
            0xD73950E33C31F1FFULL, 0x50261E0265080769ULL, 0xFB830B09D771CD1CULL, 0xACE18869FEBE148EULL, 
            0xF4B66DF27EAD0E7AULL, 0x4BBE2607BA07E3A1ULL, 0xD4D8875DB28C1620ULL, 0x5596A5E417E5407FULL, 
            0x7D448AA2657677F3ULL, 0xAA2BFB3868A10F86ULL, 0x4966E6308CE21262ULL, 0xB3E0C46DB680A4F8ULL, 
            0xB3DF5B9D0C6CC6ECULL, 0x9B0CCB5E7F53916DULL, 0x12C41810F703FC96ULL, 0x23C5DF3C36F3053DULL, 
            0xC9DEE14E32D6B080ULL, 0xDFF13809D0FFE0F4ULL, 0xEE0623F359EC52B2ULL, 0x3749B64D08574CDBULL, 
            0xB7D3CFD27AB60997ULL, 0xFE4B32255FCF8DB2ULL, 0x7135FD69CFB52EB0ULL, 0x352B5843E672F998ULL
        },
        {
            0x55B07902B04FE94BULL, 0x11F4E769598D5299ULL, 0x7F844454233F6722ULL, 0x9DDE67C9A7846C10ULL, 
            0x5A4B4EAADC3FC22DULL, 0x7653696AD0E7814CULL, 0x654F7F9696489D47ULL, 0x659148056946895FULL, 
            0xB83B6E5349426C78ULL, 0x37731D57ABD7B020ULL, 0xD5C6D7A56D5B0C6AULL, 0x1BEE5F25C7C7C76BULL, 
            0xD948D44A41A03875ULL, 0xE0BB2D5802B44B42ULL, 0xD1D44D9A4C575083ULL, 0x65C9B7EEB05F7B51ULL, 
            0x04EC75D31E15E55FULL, 0xB3E41660BC8A0714ULL, 0x3EA91862A9F9E5F7ULL, 0x2F3CBEF88526446DULL, 
            0x6ADCD3407902523BULL, 0x81AAA249018A5F2FULL, 0x3AD114B720183308ULL, 0xCECA0EE808CE5FC7ULL, 
            0xE240967D69373D41ULL, 0x2093873E9B435ACEULL, 0x7E99C420DB1E52D0ULL, 0xB53C007D7F103EB9ULL, 
            0xA4CEA516B8F7CE36ULL, 0x70CE1E9D1E6F0906ULL, 0xD797D0A672C4EE23ULL, 0xA90235C326536CDBULL
        },
        {
            0x7275E9A534EBE273ULL, 0x0D96B480A3675EC1ULL, 0x4638B04D248A9790ULL, 0x3D7A41E62D986C19ULL, 
            0xF574DE2EAEE9FCFDULL, 0x48E380A8936D6678ULL, 0x9B40B0921A6D0CAFULL, 0xA2E8B45D5068601EULL, 
            0x55FA8816E572804EULL, 0x991C67B86418434FULL, 0x94D906775900CC76ULL, 0x7EED0D8FCD18A847ULL, 
            0x41B05D259CB021CAULL, 0x30DA13069BA056A8ULL, 0x37AE91061FAE560FULL, 0x6EBA3FAAD5E5C386ULL, 
            0xD91E5D349B5E633BULL, 0x430B7D81B8D0F49DULL, 0x69F9AA7854DD4773ULL, 0x52B968C88646F500ULL, 
            0xC7A9F2F156561A7DULL, 0xB3BC913B37B2E791ULL, 0x809A09BE58760CE7ULL, 0xB2F9E348CB6DE710ULL, 
            0xD170F69DDB21ED19ULL, 0xBC50B6145E5C4A39ULL, 0x93704551F2CAE2C6ULL, 0x61777B3EFD6790B6ULL, 
            0xE34BA420F11FCCD8ULL, 0xE860C59B87F203A9ULL, 0xC3FC4F8D324A2BC8ULL, 0x8EA1F08B3DDF6C5BULL
        },
        {
            0xC6755199AA41A85BULL, 0x02F2B41129365310ULL, 0x2B1E68499162798EULL, 0xBF00AFA504767E4FULL, 
            0xC70C7BE8457EDBB8ULL, 0x93A29D9EB0F4E7E3ULL, 0x2F2C83B85CC14C72ULL, 0xBB9B62F1A225174AULL, 
            0xC20A56BB7EF2C585ULL, 0xF5E80F1DC9A4B26CULL, 0x433E19CFFCB5A31FULL, 0x5AACD89FF63013C5ULL, 
            0xC4799EC79E67B25AULL, 0x7DD0E0BE14D65577ULL, 0xB04DAAB6E816B94BULL, 0xE95903EC9FB84081ULL, 
            0x7EA0638DEA23C360ULL, 0x7ED777AD7F2C1470ULL, 0xF92416E2BF2C57C1ULL, 0xCBA8232BB88245A1ULL, 
            0x085BDA6F1D606DC6ULL, 0xC9FA5E4E611DB01BULL, 0x0EDAF62C0BC5183AULL, 0xD655E1778B8A4BF3ULL, 
            0x1A13C4C3E33E206EULL, 0xDC08A39CCF4162FFULL, 0xBB2ED98D8FEE06DEULL, 0x0A23B1A2A65F9554ULL, 
            0x8F0CE46E1990FEA2ULL, 0xA0F8FD9690D9648DULL, 0x054B90D08A66883BULL, 0xD9DF5889F0DC4E05ULL
        },
        {
            0xB5671BDA30B5F12FULL, 0x4AAB18165EBC0210ULL, 0x168FB09E621A7FAFULL, 0x18A0081A876E78FCULL, 
            0x05D45E920BD87F6CULL, 0xCE29639ADBF63341ULL, 0xBBCF22FDE713A2E9ULL, 0x8AF98D0E73FF4A36ULL, 
            0xDE0ECB0F353732A7ULL, 0xEF0F5913F8D142BEULL, 0x8B6F8560ABA4925CULL, 0x8AC135B510D0511CULL, 
            0x6BB692A68DB8029CULL, 0xDA458885ABD50AFAULL, 0x7C92E57A887AEC65ULL, 0xF84E90F9D83A7EBEULL, 
            0xEF4198458D19C91DULL, 0x517A464D42F1CAFCULL, 0xF10326C82FD22A79ULL, 0x17001883236988F1ULL, 
            0xE2687B724B9A6F3AULL, 0xBF82BB68A4A44F39ULL, 0xECD516CA0670761DULL, 0xD2C552D1ACDB4336ULL, 
            0x9046A5A54365BE44ULL, 0x5A67B2F36BFDD752ULL, 0x634141CD355E33DCULL, 0xF32859D7519DBEF5ULL, 
            0xEF5EA948E887AF18ULL, 0x67050C99DD3DA59AULL, 0xBB22EA687F631238ULL, 0x3B86D3C661BBB6B9ULL
        }
    },
    {
        {
            0x0CBA45673F1C6518ULL, 0x0300E0186A215EB5ULL, 0x4014A88578FCCFB3ULL, 0x6BE2EAFE56F01779ULL, 
            0x5A3CD96B631135CCULL, 0x641AC0A1BBD464FCULL, 0x12DF7A1651F58C9FULL, 0x799A4FDE2374D53EULL, 
            0x2A113C5C457F3470ULL, 0x6E7D8423FD3EF4E9ULL, 0x2BACA85AE79FD510ULL, 0x99A7E81E09F02CA9ULL, 
            0x21430548A0D14842ULL, 0x6C9A648786C5BEB1ULL, 0x267D2BE349358CC9ULL, 0xBADC7DA897B39242ULL, 
            0xCA409B2FAC37F8B6ULL, 0x161CED8DA64D7769ULL, 0xA7E368475BDF67D0ULL, 0x2DABC764480E07C4ULL, 
            0x65B25B07E770DA71ULL, 0x3F87AC25CBE7CEE6ULL, 0x61BF0222E5E6D5BAULL, 0x9D975896F5056B63ULL, 
            0x8F5838C3FFEAAD50ULL, 0xC752B320F0D7CDA1ULL, 0x828D81FD3D47E763ULL, 0x9223599AC3525581ULL, 
            0x78A513DC6AFDBCCCULL, 0x4D9B82A3220B6946ULL, 0x3B0C40E6794D84F2ULL, 0xB5B17ACDED4D6B22ULL
        },
        {
            0x566C12351AE8ECADULL, 0x6115FEF03483ECACULL, 0x3D8A52826F1E104EULL, 0x5344A44E71A52D75ULL, 
            0xC83780D5834BECFBULL, 0x2D07ECC2ED4ACD6FULL, 0x99F5C807822DF949ULL, 0xD3E57226AEBBC5D9ULL, 
            0xDC178A7EF955E97CULL, 0x602DDE6A661016E2ULL, 0x1B9F8AF920217275ULL, 0x8509F3AC752B721EULL, 
            0xAF0DA436FC1DCF50ULL, 0xABFC0631CE221D74ULL, 0xB79BAFE75023B1F1ULL, 0xA5EDD0693B4BF4F8ULL, 
            0x81B02508D9176411ULL, 0x4F9FAFA526855D8FULL, 0xAC82650EDCB163CAULL, 0x459B58398A9A6B1FULL, 
            0x0821EE9157470F60ULL, 0xACD36C907BA3D024ULL, 0x14AE0F34266CAAE6ULL, 0x10AF7C34769A6D07ULL, 
            0xA135AC2E2665F4C2ULL, 0x8A375F8F2CD1538CULL, 0x11201701195A78EDULL, 0xF67605388EBA457FULL, 
            0x6F635CC22D199D2DULL, 0x950D7E003812445EULL, 0x46065EDE406B02BDULL, 0x02E7EAAD74CD1B05ULL
        },
        {
            0x95FDB7748BC428BAULL, 0x96E886FC63C4F348ULL, 0xB220DE26D35D0BFBULL, 0x73E06CDC2E13ECB1ULL, 
            0x7FD21B33FFEC8E92ULL, 0xC99BC4C1551AC0B5ULL, 0x1F8773463558E471ULL, 0xB2C50C01AAE90BD2ULL, 
            0x4F65F8119442C80CULL, 0x414FEECE281F5FDFULL, 0xC797FB2D0BB3B9EEULL, 0x555CE272F07A567EULL, 
            0xCC822E7F6A33BB6DULL, 0x6BA31970177B2A28ULL, 0x9689BA797A2A4A36ULL, 0x50D0258F2939BA84ULL, 
            0xF183BE3D89B987D2ULL, 0xA1955145934C5FF5ULL, 0x6DE01CA3EFCF47ACULL, 0x5873B73DAAAB8EBEULL, 
            0x66A08B04DD655D09ULL, 0xF3702038D1543707ULL, 0x98A1D05B6AC3D467ULL, 0xADE56B6D686289F4ULL, 
            0x2045A2843A52D03AULL, 0xAC3D4869061EE1A0ULL, 0x6787728DC1945C50ULL, 0x27BB061C565E495AULL, 
            0xE0A1EB3662B008F6ULL, 0x8E2A342BD46A3FC9ULL, 0xECC13D5911522905ULL, 0x787A53EF8DE29877ULL
        },
        {
            0x7363B99C596DB9EAULL, 0xCDE84A44F515D7F4ULL, 0x6F2FBA0DA7D0B4CBULL, 0xD0565B102451B1FBULL, 
            0x538DCCE3E7E7FF52ULL, 0x5077A5E8D79337D2ULL, 0xF997F17B24334E02ULL, 0xBAFA6DFDC380101CULL, 
            0x29FAE0E7F5F75F2EULL, 0xE1C7282F795F8C76ULL, 0x510FB8A440ECA040ULL, 0x0CE99E84ACAD1E60ULL, 
            0xD8327C798319B481ULL, 0x193D9751C4A513D2ULL, 0x2310AB38F95888CBULL, 0x08737AF059B483F1ULL, 
            0xEFD2E7DC21282480ULL, 0x1633DC99472F9401ULL, 0xD6074188D8C1B113ULL, 0xAC6F56D31955FB8AULL, 
            0x34613E343CD431A8ULL, 0x395D018ED9FB796BULL, 0x4B620EEFCEC5862AULL, 0x914BBB3161A6A484ULL, 
            0xB972D9A70C5973A0ULL, 0xBEBE9ABBBB022953ULL, 0x1CC51C3A7A5E750DULL, 0x9C336C3C7D541B7CULL, 
            0xF0640732530BDFDAULL, 0x26B04E00216A5731ULL, 0x058C448DF5D9B8B5ULL, 0x09014F355B1C6B72ULL
        },
        {
            0x06104802B8DD65C0ULL, 0x4D477158AF7ACC86ULL, 0x054585CAA2BE3CAEULL, 0x2B48BD682DCCED97ULL, 
            0x6B2F52F9D92C10A5ULL, 0x020DCAFC28A60A1DULL, 0x05A86826DAEF17EEULL, 0x0254E175A4CAC490ULL, 
            0x8875F243E849254AULL, 0x1AE3846095718E0FULL, 0x77A6153AB6D693E9ULL, 0xABD9E7A15808C037ULL, 
            0xB635EDBBF4631524ULL, 0x77F4FBABBA2E2CF3ULL, 0x51240F738CFB661AULL, 0x54A2560F5BF9116CULL, 
            0xE208B3C61939F0FEULL, 0x7D8A5DD380F148BBULL, 0x937FC1EF12DC6151ULL, 0x459D2D7603844237ULL, 
            0xF3B25F551213EBE9ULL, 0xCFD8A5716F354035ULL, 0xE39F54CF2D3946D6ULL, 0x0BA8A9D4B87881F5ULL, 
            0x8645C1900EA941B2ULL, 0x0543298ADB812F9DULL, 0x0B311DB9F5253F43ULL, 0xB5016D84CEECDAD1ULL, 
            0x4CEDE6399ADCD216ULL, 0x29DAFA02D45E4817ULL, 0x4F7619E594C8C180ULL, 0xF53FEAFE84FC8D96ULL
        },
        {
            0x26E35B4B31BBDE62ULL, 0x9A2589A7084B57A3ULL, 0xD438DC7FCA9127DDULL, 0x7469C7AEE6D66F23ULL, 
            0x6BBEC373EAE76268ULL, 0x39EB68DC123DDD22ULL, 0xB03179F28A453E55ULL, 0x9D27D4CA3D00C9FEULL, 
            0xFD6922E3CA41789FULL, 0x919CA6A5FAF68826ULL, 0xDB6D823D8EEE3BF6ULL, 0x8AEAA38EDC9C8284ULL, 
            0x8677863CB759BE73ULL, 0xD5FE322229CFE2A4ULL, 0xDF6B46A3D50CC925ULL, 0x98BC170EBCF1B340ULL, 
            0x80790192B26E438EULL, 0x7B9D20F8CFB45E3CULL, 0x81F11D5F595938E1ULL, 0xB1EE7910E1FD6C7AULL, 
            0xA80B3719590D1BF0ULL, 0xA33B96840E65F1CBULL, 0x12D995B1312A45B4ULL, 0x5EDF197532F2FACEULL, 
            0x3AF606C571F7F021ULL, 0xCFD32799BFFE324BULL, 0x12015340F8098566ULL, 0xADBCB887637732A7ULL, 
            0x5EB1BE68BF10ADC8ULL, 0xDF3D1F0571063123ULL, 0x88EBD98820EA801AULL, 0x497BF3AC408BAD07ULL
        }
    },
    {
        {
            0x4BDD25951F854800ULL, 0x0613EFE5D571B913ULL, 0x7E703A20BE71BF14ULL, 0x81268C704DE13D89ULL, 
            0xF60A72497E5445F9ULL, 0xC535FF4499203B23ULL, 0x8B7F30DE5124C532ULL, 0x36DF8D8F5F6CDCFBULL, 
            0x4A3FCD1D0FA63A3DULL, 0xDE8DC43D5310C071ULL, 0x5D9DD0E8DF23C436ULL, 0xD4E273B30F829BCCULL, 
            0xC99F01DAB7624FC8ULL, 0x880481BBBF423B57ULL, 0xCBD4953D6AA63332ULL, 0xE3BE3139CF872E6FULL, 
            0x03FB8DE063EE9BD2ULL, 0x7FF9E9981B5CA544ULL, 0xEA1F4EA998684CC5ULL, 0xDB89A74347FE821CULL, 
            0x9382588FB2AE9EDEULL, 0xA7DC679E20E8C9C2ULL, 0x6BE493558D240488ULL, 0xABD6CCD46C348499ULL, 
            0xD1EA654295405076ULL, 0x1D128860A0B6A6ABULL, 0x287D2741FFC0AA0AULL, 0xAE7F88C41DFADD2EULL, 
            0x71ABA572008A1DE9ULL, 0x6EC229668A52D3EBULL, 0x741368ACF4C76DE6ULL, 0xCAA59A189B568B0BULL
        },
        {
            0xAC84BDDF4A1F53F2ULL, 0xA69851431FA36926ULL, 0xD1CF25B9D2C0CA28ULL, 0x66BE97B61044FE8EULL, 
            0xD3EF3FA9CD51A6BFULL, 0xEBC5F2EB072EDF95ULL, 0x298D8D7DA49E9B72ULL, 0xD4E86E9B802787DBULL, 
            0x4C4CC8125544D902ULL, 0x93E1BE70A6ED3E4BULL, 0xCAC02DA026F010A7ULL, 0xCB8FEC627217303AULL, 
            0xC47EF4C9C252A2DAULL, 0x9687520DBE8472C4ULL, 0x5782ED08D2539A62ULL, 0x5FF7CB40D94A13E2ULL, 
            0xD175AACA60DDB47AULL, 0x5509C37D4E768B0BULL, 0x246BE0EB84CCF8D9ULL, 0xE70F3138427EC201ULL, 
            0xDA41CA3CFDCAA3D6ULL, 0x14D39F4870777251ULL, 0xF967ED8BA581E1E4ULL, 0x8802703AC46EED95ULL, 
            0x772A2F20C1BABEFBULL, 0x566590A73F7AE6A4ULL, 0xC66DE07AD645D412ULL, 0xE7D8612CE0C2CC1EULL, 
            0x80DA14C5463ACED4ULL, 0xA64489A271BBD638ULL, 0x2A61CB5826D2DA61ULL, 0x2FF6A2DD563449B7ULL
        },
        {
            0x16CCA0C903E8CA57ULL, 0x1BAC1213307F4AB4ULL, 0x666513C974E321B1ULL, 0x60759ABD1CD3C4D8ULL, 
            0xE6B741E315FD4E01ULL, 0x3E49977B53278E93ULL, 0x41C1B83EC8C05773ULL, 0x08E756527DF42DF4ULL, 
            0x010F9E8E117A9BFBULL, 0x5338BF82FE7B477EULL, 0x1203128D796CE1F2ULL, 0xCCD6F97AE77C43FAULL, 
            0x1B372762826DAA35ULL, 0x858E79FF8A41C017ULL, 0xEA02D99E7BF8E430ULL, 0xD6F448EC7DCE2354ULL, 
            0x498699A5C86C2BBBULL, 0x2787209C90F32FE5ULL, 0x659D33C0681E2052ULL, 0xDF4CBC8E5044D437ULL, 
            0xCBF7AC4F1532FE94ULL, 0x17D82B6EC626CEB2ULL, 0xA749AA419B599015ULL, 0xC63B0BF0239B5DBFULL, 
            0x5AEEE6214B7E0B5FULL, 0xCB1A66768E61565BULL, 0x63E87424EB35BDBAULL, 0x477C338048226C5DULL, 
            0x0E1831DF22DBF65FULL, 0x5C8D97C0232C7D1BULL, 0xFE16F2B55453331CULL, 0x5365FE6CD3E6FFD7ULL
        },
        {
            0x6F6DD8DA6A207C8AULL, 0x4A73B272809131C8ULL, 0x520865A86F02117FULL, 0x321B732A1B4513EBULL, 
            0xABA5460C020CA9A7ULL, 0xA4F7340440859D08ULL, 0x4967FB5B73D74566ULL, 0x474D73396EA393E6ULL, 
            0xE306BD37AA4A9660ULL, 0xC138A3F39FDD28CCULL, 0x53E5DE410250F9A0ULL, 0xEC23E0848208B7A1ULL, 
            0xE65DFA83715F3C02ULL, 0x94CB3AF5F82EF93BULL, 0xA92D3801C310C172ULL, 0x56D1A04E5DC3D706ULL, 
            0x466025E74695902FULL, 0x76E0CACBD16AB1F2ULL, 0x62F6BE42D47BE860ULL, 0x8018F8C53F474C85ULL, 
            0x6D4AACB5F7E10F06ULL, 0x10E9F9B5114995B2ULL, 0xE6DC0D9A59D7DD8BULL, 0x3E492AA958215EF9ULL, 
            0xB953C5E76FDEF91EULL, 0x412E30DAC2522F8CULL, 0x6B92D3058A1815E7ULL, 0x202BCF9AA3FD3984ULL, 
            0xEF1FEFE221C52345ULL, 0x2C1D482D8C0C0243ULL, 0x3F4B8CE9AB98223AULL, 0x4732551487527118ULL
        },
        {
            0xAC4932B8F72CDA2DULL, 0xC67F05EF96B17CFBULL, 0x150C4FDD259DC731ULL, 0x28565F26705BD2ECULL, 
            0x45A00539E78B27BBULL, 0xAA059B91B957DFEAULL, 0x7CF80DCC168FF674ULL, 0x23730118DA28ADC1ULL, 
            0xCF35938FAF732E74ULL, 0x66B6DCC3E76CF85DULL, 0xBF841B3AF4F24B60ULL, 0x6D444DDA17D944EBULL, 
            0xADFFA3080148DE77ULL, 0xF92B997369157124ULL, 0x149C420115FF861CULL, 0x57F6071C0936720FULL, 
            0x07B05DFD4EDDE780ULL, 0xE30D8A9A822FA710ULL, 0x2EE8F9696ACAD20FULL, 0x5957696F8E0ED331ULL, 
            0x90922A99EA770903ULL, 0xB43D8B62A98164FAULL, 0x102BD54B4850576DULL, 0x29B5F8AB66F4025AULL, 
            0xAE66E8B01F67C972ULL, 0xEB2F2BE9C0C1164EULL, 0x6D2EEE3508D944A4ULL, 0x5A28C5E6BC65C0C4ULL, 
            0xE3E2962574730F77ULL, 0xDC716AE021725229ULL, 0x1935ED135ED62936ULL, 0x64A643822BDCB4B3ULL
        },
        {
            0xD7295F8BCDEAC23EULL, 0xD4A1F229A4151F01ULL, 0x2C73711C435CB623ULL, 0xD325CB52001FF908ULL, 
            0x1EDD98E274FD7CDDULL, 0x3FA255669C1EC940ULL, 0xA9DD0E6862395387ULL, 0x76F431F8BDCBA878ULL, 
            0x0306D09D49E0B65AULL, 0xD2B8934BB9771543ULL, 0x3E2672D156209EADULL, 0x4D0DE13AFC7F8454ULL, 
            0xB8DD3A5DB8B58D29ULL, 0xF50D94493D4E0ECBULL, 0xD2FB5A9D059BCDCBULL, 0xB1854C90705A428DULL, 
            0x473B0A37D69322C4ULL, 0x889E9C9BC778EB9DULL, 0x6FBB2402E7BBABC0ULL, 0xB234B972B2CECE08ULL, 
            0xE919F67DF9C88B9AULL, 0xC81C3F2A34A08EDFULL, 0x27CA2129EA71B2EEULL, 0xDE08124CDA25A47AULL, 
            0x9C07226C63FDA78FULL, 0x08316758B73F75C0ULL, 0x60EDDCE6C79014A5ULL, 0x4B86EEB31B10F11DULL, 
            0x8BFD6FC10A6E7B54ULL, 0xB66A5A94758640EDULL, 0xEFC3CB4344EE67FFULL, 0xF0E0B6BB6E028DA1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseGConstants = {
    0x703602493CC6D4EAULL,
    0xFBFCC6CB63887ABEULL,
    0xC8DCC25B70F3092BULL,
    0x703602493CC6D4EAULL,
    0xFBFCC6CB63887ABEULL,
    0xC8DCC25B70F3092BULL,
    0x16B72AF30882279EULL,
    0xF0FFC4A9CF7E9FC9ULL,
    0x83,
    0xAA,
    0x67,
    0x33,
    0xBF,
    0xE6,
    0x5A,
    0x5D
};

const TwistDomainSaltSet TwistExpander_Exercea::kPhaseHSalts = {
    {
        {
            0x316E4ACC88943320ULL, 0xB6E09127A04D63C5ULL, 0x854AFF0068A135ADULL, 0xC1EE4A3AF1472B3FULL, 
            0x7A96B695459A2DACULL, 0xCDE6D37F9EF948A0ULL, 0xFE7443F00A90A933ULL, 0x732C815711D7FE36ULL, 
            0x1358289E2480504FULL, 0xAE49F1A7383A6965ULL, 0xC8D86DFF7D24DEBDULL, 0xB711841A3D8E811AULL, 
            0x8DEF69AE2D348F01ULL, 0x6CA6A11255444ACCULL, 0xB0C7671EE7FD7764ULL, 0x360C6C46A0063821ULL, 
            0x5147BB6EE8265155ULL, 0xCE66A1556B10705CULL, 0x4E58B1F52B06B113ULL, 0x1CEA5E716D1F3274ULL, 
            0x4C23D7FD918EDAC5ULL, 0xE618AA85BC8585D8ULL, 0xA10491C39BF4DAD0ULL, 0x953DA44A04F4BA83ULL, 
            0x08434F11BC9849B0ULL, 0x1A0580A46F8D75C2ULL, 0x69888274A8943CD0ULL, 0x2DB7AAEA6BB86192ULL, 
            0x5B46BD0783DB3951ULL, 0xFD779E1DF1F833CDULL, 0xC97506C0B7610448ULL, 0x5C3F22E050AFDE03ULL
        },
        {
            0xEF6B13A1B7BA290DULL, 0x363B475701F90E8EULL, 0xFDC6F8933E44E78EULL, 0x8C8BDE84AFBBD1C5ULL, 
            0xD3D236B954B0BEC6ULL, 0x506CB14F78FA0A2AULL, 0x0B5B70E312619CABULL, 0xA4038A4E6C422367ULL, 
            0x06963698F52C0A4DULL, 0x9795D03D3D85C2F0ULL, 0x1CABE05D8B0F5213ULL, 0xA0203EE64880DC0FULL, 
            0xB94AC781FE0359C1ULL, 0x9DEC7A92E0C2EC8BULL, 0x43F4A5A3D1D287E6ULL, 0xC18799D87DB893A3ULL, 
            0x642208B20AE0BD5BULL, 0x239BCF595DE35D5CULL, 0xAAA3DD8D0F436FAAULL, 0x0E1365AF03E512C1ULL, 
            0x2CF68342704CA30BULL, 0x4A97EE172E034AB1ULL, 0x7B5AF41EC5A5C9CFULL, 0x75384974AE8C4784ULL, 
            0x70B4770E6F155DF7ULL, 0xE2241E23F05C8218ULL, 0x9996CF7DB801F383ULL, 0x245E25FACC0B5225ULL, 
            0x67E07BC18742E2BEULL, 0xA82CA9BF7DD1420DULL, 0x9FBC7C7921D60D4BULL, 0xE0AC8D03E9EFFFF9ULL
        },
        {
            0x2B5568F3682F9B54ULL, 0x1BAB529EE9ED5B20ULL, 0xA1C7A8C9A7B1EA45ULL, 0x398258EFBD5D32BAULL, 
            0xEB12A6F5278AE0EBULL, 0x319EE4D828C60078ULL, 0x1EDBF56278CC5345ULL, 0xC29C4C0AA050A5F4ULL, 
            0xF791CC62124A1BA9ULL, 0x2417513344AA9950ULL, 0xBAA6B92E188F867EULL, 0xFAAC486A10D8CC29ULL, 
            0x2FFA8EAB05A1B44DULL, 0xB933CC802D8939DFULL, 0x4179C145566FDB3CULL, 0xD512FA5BA4B17041ULL, 
            0x27FCEF085AFD2CC7ULL, 0x032A1652313DDE48ULL, 0xEBA3919C4F772E1CULL, 0x5E4EF461E7074E60ULL, 
            0x4FF1D3135261CF8FULL, 0x81D73BFC7BE9FA9EULL, 0x909B8B55AD27E138ULL, 0x3CE720408078BB48ULL, 
            0xADD8BB5E68D4A9C8ULL, 0xD459271806ECCA9FULL, 0x2C0AAE9FB2F40E5CULL, 0xFF8669AD8139A7C9ULL, 
            0x2165A2368C084B30ULL, 0x2209E6368FEAEFFFULL, 0x8DC0BB30C2757084ULL, 0x13D7772DB1B65B53ULL
        },
        {
            0xA6F4F2840B1F051AULL, 0xD8B4C924220CBBCCULL, 0xC5FAF257E8A0FD5EULL, 0x2750586CC872D2C6ULL, 
            0xA08B1F768DDB92BFULL, 0x71A628C512A9301DULL, 0xE311518FEFB91866ULL, 0xAB4908B71F995AC4ULL, 
            0x878F58E1C93936A0ULL, 0x0B3D90874F58D197ULL, 0xED92268AB257355EULL, 0xD57CF783D09911EFULL, 
            0xEBA475C70F76B50AULL, 0x8F8383025D69E0C0ULL, 0x0FDD72A263503E15ULL, 0x1C4D40F0DBA369CDULL, 
            0x0B62084B60D7E4ADULL, 0xE9804E3F1C32AE48ULL, 0x155F786D431ED19CULL, 0xCB862B7CF0237F64ULL, 
            0x6E7E39BC70925B48ULL, 0x6E2E4A753281C110ULL, 0x0D55C774BABD47FAULL, 0x6DBE1D3A78DBC619ULL, 
            0x6356C7DEC19F979DULL, 0x511C50B227544163ULL, 0x6FEE37C9C6B70A01ULL, 0x61CAC493D7113593ULL, 
            0x943E57C0731E7114ULL, 0xB4ED3EF26487AB20ULL, 0xA460CC88FBB208FBULL, 0x0DBEF4E842F3A1B9ULL
        },
        {
            0xF58F87502EEF6FF7ULL, 0x795263CB6D4DF253ULL, 0x00F39DB96CD5B3F7ULL, 0x20719BBEE7721444ULL, 
            0xBD717C1FA3FEFE41ULL, 0x87F6AE315075ECDAULL, 0xB5281010FCF94036ULL, 0x6165EA19422525DCULL, 
            0x11A45C71CC857C20ULL, 0xBAE949C59AFA369FULL, 0xE8A61EE401A1C4BCULL, 0x080E800246A9D96DULL, 
            0x05F0E8238FBAA933ULL, 0x88E398D04D8D1396ULL, 0x4D67ABE9D776A5D5ULL, 0x30AE709060C3FE9CULL, 
            0x192DB39B5BA52301ULL, 0x3FDEA44D3A44A330ULL, 0x6EA6531C36AF2646ULL, 0x81519FC99F5DE0B2ULL, 
            0xD9AEC66EB1C94F45ULL, 0xB879D6D7B254012FULL, 0x9DD2E2BBD240C5AEULL, 0xF397850C9AEB9EA4ULL, 
            0xE597843BED68F461ULL, 0xDA015FA3F3AFAAABULL, 0x2D271CCF7CCB693BULL, 0x1703AC772190D34BULL, 
            0xD19496D1519B9A6CULL, 0xB85A2753E05F8CA8ULL, 0x6E82EE6D01AE8F75ULL, 0x304721F614A89583ULL
        },
        {
            0xFC6FBB12C8F21EC4ULL, 0xF5E14B1B369C7EC5ULL, 0x81A209F8620CC325ULL, 0xA239571AC187E6EFULL, 
            0x65598082F850DDDAULL, 0x5A5F074DC3C11023ULL, 0x3E4661F88DFE5FA5ULL, 0xB40B5E54496DC35DULL, 
            0x1828757A6A488328ULL, 0x90232C4756DEB8C7ULL, 0xA60C478A8DCF33B4ULL, 0x9BA00C0E356F5EE1ULL, 
            0xF195A754228B6D88ULL, 0x9B6203F49B7B07C4ULL, 0x5DB277276AC24AB7ULL, 0xCAADD69C8FA3382CULL, 
            0x13F0C577346094FDULL, 0x3FBB1271A34D2B0AULL, 0xD2E7DA99228D96E9ULL, 0x70029AF0A3D25D78ULL, 
            0xEC0ADD7985855571ULL, 0x8EEEE4F222231FF2ULL, 0x0DDDC317A8C033C9ULL, 0x3AF4F1DE85C863C0ULL, 
            0xD08110167CB23D49ULL, 0xA06EE748DB9811DDULL, 0x68B08584123CC9B0ULL, 0xE8E806F8483BDB89ULL, 
            0x2431DC0B0688D554ULL, 0xA9755ABF5DDBD768ULL, 0xA913A2988975E75AULL, 0xB64F164FF3A4DFE2ULL
        }
    },
    {
        {
            0x64F3FB5BAF00E2A0ULL, 0x47E4210FC0C47ABFULL, 0x85ACCA51210F1BC9ULL, 0xC67E2C2CEC8C16A5ULL, 
            0x43FEF600A45937CFULL, 0xDC2A8FEC19AD90F9ULL, 0x377840825E97391EULL, 0x876BF8A01272C3B2ULL, 
            0xC6AE173BBB22EB7BULL, 0x82F5DFA6B674F88DULL, 0x3C29C7611DD31321ULL, 0x3BD4AC3056BE6D1AULL, 
            0xEBAFD0D946394CA2ULL, 0x578C1AA7DCA2561CULL, 0x9ABB6542460E6330ULL, 0xFEEE19D102CF8BB4ULL, 
            0xDD9F0F2A1F566AD1ULL, 0x706E2FF912DDDD9EULL, 0xD4997B72AF2647E1ULL, 0x872C5222A4F4FE4DULL, 
            0xD22A23ECE085FFA7ULL, 0xAF25ECBA220D2AD5ULL, 0x20BD48F6B9B4B190ULL, 0xC2435E3FB050A4E5ULL, 
            0xC693F9EF994CAAB6ULL, 0x2E614B5B1BFCC936ULL, 0xA70D07916E254139ULL, 0x39FD1A77D5462826ULL, 
            0x6DA6E7C41E831459ULL, 0x8A45A3F0240F7E0FULL, 0x1173695242DBA39AULL, 0x5152808CA24E59A5ULL
        },
        {
            0x7396679785D80343ULL, 0x0652A54C667D9A93ULL, 0xE49BBFA9D665F200ULL, 0xBDDA4466063974EBULL, 
            0xD0337D11F4410AECULL, 0xF4E0FB6C20E18145ULL, 0xCC541195E873C000ULL, 0xD31A5215AD9D22A5ULL, 
            0xE45474F65975CFCBULL, 0xA8A1F573D4DC4D94ULL, 0x696C077710D2EBBAULL, 0xB63FBB203711BAFAULL, 
            0x1ED773E46EF815D7ULL, 0x07D154404F037CC6ULL, 0x3806CD3537EC56BEULL, 0x5C5025EF31563F0BULL, 
            0xCD34321B0EDF0B45ULL, 0xEE0DA47477AFD44FULL, 0x6A97E37AF6956220ULL, 0xD132FBDC30BCE1E1ULL, 
            0x01C9E79ECB64BC42ULL, 0x66EA78850FC1CA95ULL, 0x5B18B35084C86392ULL, 0xB381F91D8BF96EAEULL, 
            0x0503EA5FB77AE848ULL, 0x2166B52F2A3BB357ULL, 0x553BA15D3CF28967ULL, 0x236D436C546813A6ULL, 
            0xC74166B37A950795ULL, 0x0F06C395620D5C1AULL, 0x61ED509524C16145ULL, 0xAC3C48426CB46228ULL
        },
        {
            0xA0BA43CF02359B93ULL, 0x54A5894A45CA2BB7ULL, 0xAB368FFB45BEE058ULL, 0xA1CD121B39A9968BULL, 
            0xCC5C797237400A01ULL, 0x9F2F5115E9182FECULL, 0x95926C39AEBABE9BULL, 0x24ECADD478AA62FEULL, 
            0x659545E11416BE03ULL, 0x2C09F4EFD2956C1FULL, 0x79E827EA12E89C14ULL, 0x63B8B06E1D74EE0EULL, 
            0x3CEECC956F78DDEAULL, 0x8DFFB1A09152D737ULL, 0x94595F848B7F17DCULL, 0xAF487C7BE5BC07B1ULL, 
            0x0394780CF115567BULL, 0x96ACCF6A2F84D7D8ULL, 0x799C05464BCDF59EULL, 0xA1E66A64424D539CULL, 
            0xE1AAC6C9D4DEB13BULL, 0xFADC91328A135FCBULL, 0xDAAB52DDC96D18F8ULL, 0xE83BDEB14A90F917ULL, 
            0xF1AF12539CC18CB9ULL, 0x1112F4198705C306ULL, 0x5D2E819B5154A1C0ULL, 0xA20BEB5C6F6DC3B6ULL, 
            0x2D1C0E88DCB02621ULL, 0x10444468A651C268ULL, 0x92BFDA9C22E2ED2BULL, 0xFAC1855C8B946AC3ULL
        },
        {
            0x20FD07A9F8E83146ULL, 0xD02786C991AD5868ULL, 0xE519EF94135FCF27ULL, 0x50F81E650A2AEFADULL, 
            0xC909D65ED0C62388ULL, 0xD858EEDF37C0D85DULL, 0x1EBB80A442398EF3ULL, 0xF27F23F941EF372CULL, 
            0x9872AE07F04DEE44ULL, 0xAF69DE9EF9647DD3ULL, 0xE0AFABE40BDEDB79ULL, 0xE0A11D711D29E1EEULL, 
            0x5DCB265B7A9A2CC4ULL, 0x3544A6F0043D6B42ULL, 0x2C2D9B6537F3240EULL, 0xBF47F48FA02C063CULL, 
            0x2AFB80B517EC26A1ULL, 0x01D00B3DCEF44D81ULL, 0x2699951F815B6998ULL, 0xD3F99285B9576554ULL, 
            0x7E46C701472F9248ULL, 0xE5008146C311C77FULL, 0x3DB4A8008C0A75EFULL, 0xD30D593668469033ULL, 
            0x17B8DDE78B6E0990ULL, 0xDE9E8B34AD5BE0BAULL, 0x9CBFC509D8DF6B4CULL, 0x36F0EE5759A46F2FULL, 
            0x782FD3598B276230ULL, 0xBFE94B25B1BC1FB6ULL, 0xDDF6A0ABE68B72C1ULL, 0x6F4A92144938AF25ULL
        },
        {
            0x899C3A27F3D47F2FULL, 0x52C9573BFE71FF9CULL, 0x276378F0748A700EULL, 0x24CEC11C7A1ED52AULL, 
            0xC2147993355AF143ULL, 0x16EBCA55E39477BEULL, 0xAF00D9B9944A1850ULL, 0x32F10A0EECC32EB4ULL, 
            0xAD0045A9B55D9B9AULL, 0xD7BA6132879437F0ULL, 0x09AEB6F2E33C462AULL, 0xCBE68903CEEE0DE0ULL, 
            0xE96288D92899331FULL, 0xA1DB54484F09D633ULL, 0xE4C6F151E99A8408ULL, 0x6290CA4210DB3DB1ULL, 
            0xE9785C2715A0DEFCULL, 0xDDFD71B26BC93AD6ULL, 0x9A16FED03B1EFA90ULL, 0x2840E8AA6BE9E104ULL, 
            0xBA4A0A8C81982AD4ULL, 0xEAB5E7E8DBCA3E21ULL, 0xEAF91D970EA43627ULL, 0x4822B4897753355FULL, 
            0xD750219CC87ABAC5ULL, 0x5D0B9F9E1B6A8A6EULL, 0x22034F592726D979ULL, 0x13401D293DBF2570ULL, 
            0xFB42559B5B62D2A8ULL, 0x31311AFC7C149F80ULL, 0x9F0D659311A6483DULL, 0x96CA7E6C11CD3349ULL
        },
        {
            0x498AE440A455801EULL, 0x08681B831419808BULL, 0x3CE742893C2829EAULL, 0x33AA22410200B3EDULL, 
            0xA1569B2B751263B9ULL, 0x18E7309AFD1587AFULL, 0x59E601ACC4CC693CULL, 0xA38D161021A57E0BULL, 
            0x3230C553359320DFULL, 0x6C12F4828013FA35ULL, 0x2D6957DDED7361E0ULL, 0x9F3524135655168FULL, 
            0x48E615578D94C4D7ULL, 0xDBF01684113C18A9ULL, 0x3B5D01A83FFB30BAULL, 0x6C109B06F15654BEULL, 
            0x55C5FEF634C91AE3ULL, 0x9FB4087D831379FFULL, 0x49E7B67A947B8100ULL, 0xDAF87740B2E31B65ULL, 
            0x5F915ECA6A44CE82ULL, 0xBA47DA2DC0B1EE76ULL, 0x67C645010AB85832ULL, 0x6BB4C3F8DC68FA2EULL, 
            0x8FF648BEBEF9DF93ULL, 0xE4B0BC117A916E37ULL, 0x3E4E296D1EF3AD37ULL, 0x80BCEAD02BDFA8ABULL, 
            0x9E0EC751DDE4FD1DULL, 0x8E3F60E9CB653BCBULL, 0x800DD9B73ADA0856ULL, 0x9212733C28544376ULL
        }
    },
    {
        {
            0xA0B23E6047B0A544ULL, 0x45BDFA56CA665CBDULL, 0x980C3F3DE937F839ULL, 0x35604E082B2689DEULL, 
            0xDFB7F6ACCF718588ULL, 0x18E0BD6FCC49656EULL, 0xC1FD9B8DF0F16555ULL, 0xB37C739EFD3CD617ULL, 
            0x595A58D8B1137320ULL, 0x1DC325A6C87A062EULL, 0x46E93B6E33E3E540ULL, 0x01A79109FB37F115ULL, 
            0xC2D8D8162783EBD1ULL, 0x7064EB00B4EF04A5ULL, 0xDF50952DAC80D5CEULL, 0x78CB8CDC8B027B15ULL, 
            0xAFDE2E878B759333ULL, 0xC0B262E740FE7369ULL, 0x6587D38DC0108CD7ULL, 0x58BA826C88472524ULL, 
            0x597A4B2DCDFAE03EULL, 0xACBB640FD0FF6DB0ULL, 0x3B7C773B2FF63472ULL, 0x7B2C27A9511D0F7FULL, 
            0x37926D70FD240904ULL, 0x2C6C37171806F75CULL, 0xFE9759B58B05BE11ULL, 0xAF073379432296D7ULL, 
            0x6F317A8ABB0DB8F5ULL, 0x293B6DDC2A4B79A6ULL, 0x04206CD459568D81ULL, 0x29E30DB5B1076D79ULL
        },
        {
            0xD9AFEEF16134FC1CULL, 0x088EE1119BC2B8DFULL, 0x310E71BF5EC80070ULL, 0x7D6636438C05F8B9ULL, 
            0x4E4E9487822507B9ULL, 0x0DD78B0FBB1E76FEULL, 0x74EF935495C50933ULL, 0xFE4DF62269D2CF17ULL, 
            0xE62C1B9BE7080CF1ULL, 0xA4C11FE2B0FE2597ULL, 0x98FBCDB81B8F0A92ULL, 0xC730877B7ED74F18ULL, 
            0xED257A647BF915D6ULL, 0x014B744AFA130FECULL, 0x8DA90A2D963156F1ULL, 0x6E89B3A28CBD4C43ULL, 
            0x79ADA62D9422B9DAULL, 0x5ECD245E322B25D6ULL, 0x2F8466A6769AEC12ULL, 0x7D6EE92FA4C31008ULL, 
            0xA9D45E6FEE5EBDE2ULL, 0x53FF1617F4313F42ULL, 0x33AC2A1B4A2726F8ULL, 0x224870F9FA319463ULL, 
            0x5308C55CD139C3ACULL, 0x9472E01E59AC9364ULL, 0xF53EE1ACBDAB076EULL, 0x7C4CF4CD236BD770ULL, 
            0xA89F16EFA3136E7DULL, 0xE01A8819032B8837ULL, 0xCFDD51FA798E98BEULL, 0xABAF925A36294F2DULL
        },
        {
            0xEFE60D79D19AF84AULL, 0x0B53D642414430ADULL, 0x114A3F829329414AULL, 0xA8F115AA21BBF2A8ULL, 
            0xF6A9513AFDA15390ULL, 0xE946A816A0C442E4ULL, 0x43CA1424E938ABC7ULL, 0xD6ECA11E58334256ULL, 
            0x2B580240964B7734ULL, 0x48C94BAB97F25257ULL, 0x6EE064FC6271EFC5ULL, 0xDA831D84340185E6ULL, 
            0x65196ECB08E99A9CULL, 0x8723F13CDFC7269DULL, 0xDD7A26B0E20084FCULL, 0xC7C48FCD83C5E971ULL, 
            0x84C2595A962721CCULL, 0xA540614AE3E14713ULL, 0x44F1C2A8A5D9277EULL, 0x60EF890804FA595EULL, 
            0x706A0E3D65717422ULL, 0x7DE1E8ADBBE39B39ULL, 0x138C7B931D819A8DULL, 0x08F3F400E4E8C046ULL, 
            0xF4A51687CDFD5F80ULL, 0xFA2423CF857CDEBCULL, 0xA58D2F6425B80AFBULL, 0xAD46F36EF217E69BULL, 
            0x65CBEB752124663AULL, 0xF66FA4A18E260ACFULL, 0xC5959B457F1FF08DULL, 0x0BF8CE80E42AA538ULL
        },
        {
            0x4243612AF86F1313ULL, 0xF1B6A162EED469A8ULL, 0x4AF6642E799CC32FULL, 0x20940B7558F078D0ULL, 
            0x0DB585E37898F05FULL, 0xEE0C5C7E21CDD9B8ULL, 0x48A619384F431030ULL, 0x91D72BA0214C3F25ULL, 
            0x7971200285AC0D50ULL, 0xA2A5B575492B235AULL, 0x05DDC7F0EB2E8136ULL, 0x481A81A7F12F86D2ULL, 
            0x1A1C5A56FE860283ULL, 0x28CA6AA35671A291ULL, 0x9FC680C9523A1981ULL, 0xA3C4D5907756E9DBULL, 
            0x6032723244CC365DULL, 0xFF85A1BEE1EFFC5BULL, 0x38F63CB6C7C17D4AULL, 0x0EE823D8C3F7D42CULL, 
            0xB8E588806F1B6EA5ULL, 0x9790E9F1FB91FA8CULL, 0x79E7A44B04B7BC0FULL, 0xC02663A11FF06C11ULL, 
            0x31DE35B77DA4E323ULL, 0x4F09D26D3A0BF023ULL, 0x3A43B79259146947ULL, 0x6760F27077C5AAE0ULL, 
            0xDEB5BBD9EC602D73ULL, 0x84019E80C9C55F70ULL, 0xD24C18213545CF92ULL, 0x61ED8776E98DBEE1ULL
        },
        {
            0xC1AC464A3DA66636ULL, 0x666AC37BAC73FE9DULL, 0x878F55425A892CDBULL, 0xC7EF1DDE89BA3C6CULL, 
            0x19E335D6D103AC49ULL, 0x008501906F341B63ULL, 0x6FBD702D6B34D175ULL, 0x09E3F40581866EB0ULL, 
            0x1A98A4CF4FB8895CULL, 0x904F925E5256A2FBULL, 0x19DFA0298723DFA7ULL, 0xBA09BF0C9B2E1018ULL, 
            0x5ABC7E67B38159E3ULL, 0x7B03F34FB04DFE60ULL, 0x7A0CDDDC32502554ULL, 0x1D3E4D42603CD60BULL, 
            0x45FFDD37AF7C2D42ULL, 0x419367B5733EE846ULL, 0xAB34509745494EA7ULL, 0x3961BE55FE9B8753ULL, 
            0x99D0CD1D9693693AULL, 0x72F4E1F045B830ACULL, 0x8E3A2F0C17C1512AULL, 0xA8A297639F4BEC40ULL, 
            0x779DB7FED13C1D82ULL, 0x51D00DBDD5ADD828ULL, 0x37602480E604255FULL, 0xFB9373BCD5C8C1DEULL, 
            0x0381738061AF0B01ULL, 0x009182458E1A0256ULL, 0x6B55BC89194CB159ULL, 0x8E12701DB84CFB16ULL
        },
        {
            0x1B37B8634DA5A150ULL, 0x4578DEBE5819742BULL, 0x181A71B8FC27D2A5ULL, 0x012B377CDF055627ULL, 
            0xC074F875F5A23E16ULL, 0x9A10365B89ABBFEDULL, 0x2D860AB13CD4CF19ULL, 0x551DC48686104AC8ULL, 
            0x51D8FCD3106F83D3ULL, 0xB06F42D805E3EF23ULL, 0x9ADC7EF81E62A209ULL, 0x19ADC92D022A202FULL, 
            0xC731D9BDD6BC80C4ULL, 0x565EFF9983544321ULL, 0x2B25A735F965C529ULL, 0x37192D2AA301AC75ULL, 
            0x7B78432E4508BADFULL, 0x3B0B813943EF6135ULL, 0x90F50109C95B1114ULL, 0xE453D13187E3AD63ULL, 
            0xDC7E6037B9E18C3CULL, 0x689926B6AF54E59DULL, 0x21C4B973AC529A7FULL, 0x4F14DCE6532ADDECULL, 
            0x9FD1061FC54ED7E3ULL, 0x1DC60D796CE5EC8CULL, 0x373CD0EFFD15CB03ULL, 0x4942DD675C598B9FULL, 
            0x4E15EC58080CF073ULL, 0xCC2732AD50BEAF12ULL, 0xF72F4A0C81523BE3ULL, 0x9629C193B9626F1CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Exercea::kPhaseHConstants = {
    0x469A342F4ED4CC36ULL,
    0x0FA15AA1B0517247ULL,
    0x94F7B41E1DDDD93AULL,
    0x469A342F4ED4CC36ULL,
    0x0FA15AA1B0517247ULL,
    0x94F7B41E1DDDD93AULL,
    0xE0012FE0783CF4CFULL,
    0x6371447C5A9A523FULL,
    0x05,
    0x06,
    0xB1,
    0x21,
    0x44,
    0xAF,
    0x41,
    0xDC
};

