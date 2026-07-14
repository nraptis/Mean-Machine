#include "TwistExpander_Gemma.hpp"
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

TwistExpander_Gemma::TwistExpander_Gemma()
: TwistExpander() {
    mTwistBlockCounter = 0U;
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

void TwistExpander_Gemma::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  std::uint8_t *pSnow,
                                  int pIndexKDF) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet, pSnow, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr) || (pSnow == nullptr)) { return; }
    if (pIndexKDF == 0) {
        SnapShotter::SnapStart_KDFA(pWorkSpace, this);
    }

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
    std::uint64_t aPrevious = 0xD8DB2120E160D55DULL; std::uint64_t aIngress = 0xBF8BD366D1BB22EEULL; std::uint64_t aCarry = 0x8A24EBB46135AAC3ULL;

    std::uint64_t aWandererA = 0xDDB8CAE5CE42AF65ULL; std::uint64_t aWandererB = 0x862CEEBB69C31D58ULL; std::uint64_t aWandererC = 0x8CE88FC015C158B1ULL; std::uint64_t aWandererD = 0xF7646758DEB5FA4AULL;
    std::uint64_t aWandererE = 0xEADC2A96384F756EULL; std::uint64_t aWandererF = 0xB9DAC1174F6D2652ULL; std::uint64_t aWandererG = 0xDF036B0085CAB49FULL; std::uint64_t aWandererH = 0xF237BCA87672944EULL;
    std::uint64_t aWandererI = 0xB022700AF4F74958ULL; std::uint64_t aWandererJ = 0x98FE522D43598E4CULL; std::uint64_t aWandererK = 0xAEC93EEC6B222203ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16939658735756624952U;
        aCarry = 12920146452475568009U;
        aWandererA = 13747465545089958932U;
        aWandererB = 13823514854892163628U;
        aWandererC = 14767265077764816999U;
        aWandererD = 12122449421894060779U;
        aWandererE = 10350836625319917166U;
        aWandererF = 16260486983882338746U;
        aWandererG = 13021495562055936308U;
        aWandererH = 16287818480295405078U;
        aWandererI = 13648309671796733320U;
        aWandererJ = 16718276175406531015U;
        aWandererK = 12122615141282789185U;
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
    TwistExpander_Gemma_Arx::KDF_A_A(pWorkSpace,
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
    // read from: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::KDF_A_B(pWorkSpace,
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
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::KDF_A_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::KDF_A_D(pWorkSpace,
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
    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_DIFFUSE");
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
    TwistExpander_Gemma_Arx::KDF_A_E(pWorkSpace,
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
        SnapShotter::SnapUpdate_KDFA(pWorkSpace, this, "KDF_A_E");
    }

}

void TwistExpander_Gemma::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet,
                                  int pIndexKDF) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet, pIndexKDF);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (pConstants == nullptr) ||
        (pDomainSaltSet == nullptr)) { return; }
    if (pIndexKDF == 0) {
        SnapShotter::SnapStart_KDFB(pWorkSpace, this);
    }

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
    std::uint64_t aPrevious = 0xC76A60421ED8352EULL; std::uint64_t aIngress = 0x9576BAC544473EC5ULL; std::uint64_t aCarry = 0xD58280A20D3AA037ULL;

    std::uint64_t aWandererA = 0x8476BAE46710841AULL; std::uint64_t aWandererB = 0xAB9B1DBC65BC063DULL; std::uint64_t aWandererC = 0xB9169F14BD4916F4ULL; std::uint64_t aWandererD = 0xDA831E549A7C5E65ULL;
    std::uint64_t aWandererE = 0x9046D125B0D123F3ULL; std::uint64_t aWandererF = 0xB2EA51490D35AD54ULL; std::uint64_t aWandererG = 0xE0E2282EE3E0002CULL; std::uint64_t aWandererH = 0xC423B6438A256F12ULL;
    std::uint64_t aWandererI = 0xB51921478DA1A127ULL; std::uint64_t aWandererJ = 0xCF1D96A27D72934AULL; std::uint64_t aWandererK = 0xA36D917D2EEC865CULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17755356794487564727U;
        aCarry = 14758358328625460904U;
        aWandererA = 14571322230210415955U;
        aWandererB = 10097738772888518903U;
        aWandererC = 16700029370186222804U;
        aWandererD = 16583135212193066185U;
        aWandererE = 12546708473173968113U;
        aWandererF = 15583889248267592602U;
        aWandererG = 17688561784323082555U;
        aWandererH = 12743827279822160349U;
        aWandererI = 18128809233340105714U;
        aWandererJ = 12281570099943835000U;
        aWandererK = 16789965692172585013U;
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
    TwistExpander_Gemma_Arx::KDF_B_A(pWorkSpace,
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
    // temp storage: water_a, water_b, water_c, water_d, source, wind_a, wind_b, wind_d
    // ---------------------------------------------------
    // write to: operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::KDF_B_B(pWorkSpace,
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
    // temp storage: expand_a, expand_b, expand_c, expand_d, earth_d, fire_d, water_d, source
    // ---------------------------------------------------
    // write to: fuse_a, fuse_b, fuse_c, fuse_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::KDF_B_C(pWorkSpace,
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
    if (pIndexKDF == 0) {
        SnapShotter::SnapUpdate_KDFB(pWorkSpace, this, "KDF_B_DIFFUSE");
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
    TwistExpander_Gemma_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Gemma::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pPassword,
                                 std::size_t pPasswordByteLength,
                                 std::uint8_t *pDestination) {
    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pPassword, pPasswordByteLength, pDestination);
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr)) { return; }
    mTwistBlockCounter = 0U;
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
    std::uint64_t aPrevious = 0xF5404D12B73E9435ULL;
    std::uint64_t aIngress = 0xD8B4FD698930F4CBULL;
    std::uint64_t aCarry = 0xBAAC385F2239C0F0ULL;

    std::uint64_t aWandererA = 0xFCE92E6917EB657FULL;
    std::uint64_t aWandererB = 0xC8209F7C93DB6551ULL;
    std::uint64_t aWandererC = 0x80FAC278D5078A78ULL;
    std::uint64_t aWandererD = 0xA47559A6ECEAE106ULL;
    std::uint64_t aWandererE = 0xAF931B3CF76629E8ULL;
    std::uint64_t aWandererF = 0x8F8610D586D69068ULL;
    std::uint64_t aWandererG = 0x89716A06876053A9ULL;
    std::uint64_t aWandererH = 0xCD65ED5B424F9069ULL;
    std::uint64_t aWandererI = 0x86DB28F126BE8E00ULL;
    std::uint64_t aWandererJ = 0x854DB75007AD8674ULL;
    std::uint64_t aWandererK = 0x8BCCBEB29FDDCEDFULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    std::memset(pWorkSpace->mWaterLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mWaterLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mWaterLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mWaterLaneD, 0, S_BLOCK);
    std::memset(pWorkSpace->mEarthLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mEarthLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mEarthLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mEarthLaneD, 0, S_BLOCK);
    std::memset(pWorkSpace->mWindLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mWindLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mWindLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mWindLaneD, 0, S_BLOCK);
    std::memset(pWorkSpace->mFuseLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mFuseLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mFuseLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mFuseLaneD, 0, S_BLOCK);
    std::memset(pWorkSpace->mScrapLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mScrapLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mScrapLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mScrapLaneD, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneA, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneB, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneC, 0, S_BLOCK);
    std::memset(pWorkSpace->mSnowLaneD, 0, S_BLOCK);

    std::memset(pWorkSpace->mMergeLaneA, 0, S_QUARTER);
    std::memset(pWorkSpace->mMergeLaneB, 0, S_QUARTER);
    std::memset(pWorkSpace->mMergeLaneC, 0, S_QUARTER);
    std::memset(pWorkSpace->mMergeLaneD, 0, S_QUARTER);

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
    // temp storage: water_a, water_b
    // ---------------------------------------------------
    // write to: water_a, water_b, expand_a, expand_b, expand_c, expand_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Seed_A(pWorkSpace,
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
    // ---------------------------------------------------
    // write to: work_a, work_b, work_c, work_d, earth_a, earth_b
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Seed_B(pWorkSpace,
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
    // read from: work_c, work_d, earth_a, earth_b
    // temp storage: work_a, work_b, expand_c, expand_d
    // ---------------------------------------------------
    // write to: earth_c, earth_d, operation_a, operation_b, operation_c, operation_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Seed_C(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_D(pWorkSpace,
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
    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "SEED_DIFFUSE_A");

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
    TwistExpander_Gemma_Arx::Seed_E(pWorkSpace,
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
    // GSeedRunSeed_F seed_loop_c:
    // ---------------------------------------------------
    // read from: invest_a, invest_b, invest_c, invest_d
    // temp storage: snow_a, snow_b, water_c, water_d, earth_a, earth_b, earth_c, earth_d, fire_a, fire_b, source, key_row_read_a
    // ---------------------------------------------------
    // write to: snow_c, snow_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Seed_F(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_G(pWorkSpace,
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
    TwistExpander_Gemma_Arx::Seed_H(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_H");

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
    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "SEED_DIFFUSE_B");

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
    TwistExpander_Gemma_Arx::Seed_I(pWorkSpace,
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

    SnapShotter::SnapUpdate_SEED(pWorkSpace, this, "Seed_I");

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
    TwistExpander_Gemma_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    // temp storage: scrap_c, scrap_d, earth_a, earth_b, earth_c, earth_d, wind_a, wind_b, wind_c, wind_d, invest_e, invest_f, invest_g, invest_h
    // ---------------------------------------------------
    // write to: scrap_c, scrap_d, work_a, work_b, work_c, work_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

void TwistExpander_Gemma::SquashInvestToKeyBoxes() {
    static_assert((S_BLOCK / W_KEY) == 16, "SquashInvestToKeyBoxes expects 16 invest fragments.");
    static_assert(H_KEY == 8, "SquashInvestToKeyBoxes expects 8 key rows per box.");
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;

    // key_box_a row 0
    // read chunks: aInvestLaneF[10], aInvestLaneH[10], aInvestLaneE[9], aInvestLaneG[12], aInvestLaneD[14], aInvestLaneB[15], aInvestLaneC[15], aInvestLaneA[8]
    // index offsets: 897U, 1703U, 1656U, 276U, 465U, 1704U, 1717U, 522U
    {
        std::uint8_t *aFragmentA = aInvestLaneF + (W_KEY * 10U), *aFragmentB = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneE + (W_KEY * 9U), *aFragmentD = aInvestLaneG + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneD + (W_KEY * 14U), *aFragmentF = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneC + (W_KEY * 15U), *aFragmentH = aInvestLaneA + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 897U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1703U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1656U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 276U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 465U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1704U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1717U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 522U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 1
    // read chunks: aInvestLaneH[13], aInvestLaneG[4], aInvestLaneB[1], aInvestLaneC[13], aInvestLaneF[14], aInvestLaneD[9], aInvestLaneA[13], aInvestLaneE[5]
    // index offsets: 609U, 87U, 938U, 165U, 575U, 1252U, 363U, 345U
    {
        std::uint8_t *aFragmentA = aInvestLaneH + (W_KEY * 13U), *aFragmentB = aInvestLaneG + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneB + (W_KEY * 1U), *aFragmentD = aInvestLaneC + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneF + (W_KEY * 14U), *aFragmentF = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneA + (W_KEY * 13U), *aFragmentH = aInvestLaneE + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 609U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 87U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 938U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 165U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 575U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1252U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 363U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 345U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 2
    // read chunks: aInvestLaneG[0], aInvestLaneC[11], aInvestLaneE[8], aInvestLaneH[2], aInvestLaneF[7], aInvestLaneB[12], aInvestLaneA[0], aInvestLaneD[1]
    // index offsets: 44U, 1596U, 501U, 1496U, 1998U, 635U, 618U, 889U
    {
        std::uint8_t *aFragmentA = aInvestLaneG + (W_KEY * 0U), *aFragmentB = aInvestLaneC + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneE + (W_KEY * 8U), *aFragmentD = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneF + (W_KEY * 7U), *aFragmentF = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneA + (W_KEY * 0U), *aFragmentH = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 44U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1596U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 501U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1496U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1998U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 635U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 618U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 889U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 3
    // read chunks: aInvestLaneB[13], aInvestLaneG[14], aInvestLaneA[3], aInvestLaneF[1], aInvestLaneE[7], aInvestLaneD[3], aInvestLaneC[10], aInvestLaneH[4]
    // index offsets: 790U, 1352U, 384U, 1052U, 503U, 38U, 54U, 921U
    {
        std::uint8_t *aFragmentA = aInvestLaneB + (W_KEY * 13U), *aFragmentB = aInvestLaneG + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneA + (W_KEY * 3U), *aFragmentD = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneC + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 790U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1352U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 384U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1052U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 503U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 38U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 54U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 921U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 4
    // read chunks: aInvestLaneF[11], aInvestLaneC[6], aInvestLaneG[8], aInvestLaneH[1], aInvestLaneB[0], aInvestLaneE[10], aInvestLaneD[7], aInvestLaneA[6]
    // index offsets: 198U, 562U, 1101U, 520U, 213U, 1281U, 495U, 252U
    {
        std::uint8_t *aFragmentA = aInvestLaneF + (W_KEY * 11U), *aFragmentB = aInvestLaneC + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneG + (W_KEY * 8U), *aFragmentD = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneB + (W_KEY * 0U), *aFragmentF = aInvestLaneE + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneD + (W_KEY * 7U), *aFragmentH = aInvestLaneA + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 198U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 562U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1101U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 520U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 213U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1281U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 495U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 252U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 5
    // read chunks: aInvestLaneF[15], aInvestLaneH[7], aInvestLaneE[0], aInvestLaneA[4], aInvestLaneD[13], aInvestLaneB[8], aInvestLaneC[4], aInvestLaneG[11]
    // index offsets: 11U, 253U, 1633U, 1719U, 1952U, 372U, 585U, 898U
    {
        std::uint8_t *aFragmentA = aInvestLaneF + (W_KEY * 15U), *aFragmentB = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneE + (W_KEY * 0U), *aFragmentD = aInvestLaneA + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneD + (W_KEY * 13U), *aFragmentF = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneC + (W_KEY * 4U), *aFragmentH = aInvestLaneG + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 11U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 253U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1633U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1719U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1952U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 372U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 585U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 898U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_a row 6
    // read chunks: aInvestLaneC[1], aInvestLaneF[3], aInvestLaneG[3], aInvestLaneH[15], aInvestLaneB[3], aInvestLaneA[7], aInvestLaneD[12], aInvestLaneE[13]
    // index offsets: 1924U, 1641U, 99U, 258U, 653U, 1366U, 1354U, 65U
    {
        std::uint8_t *aFragmentA = aInvestLaneC + (W_KEY * 1U), *aFragmentB = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneG + (W_KEY * 3U), *aFragmentD = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneB + (W_KEY * 3U), *aFragmentF = aInvestLaneA + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneD + (W_KEY * 12U), *aFragmentH = aInvestLaneE + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1924U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1641U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 99U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 258U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 653U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1366U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1354U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 65U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_a row 7
    // read chunks: aInvestLaneB[7], aInvestLaneA[14], aInvestLaneH[0], aInvestLaneG[1], aInvestLaneE[11], aInvestLaneF[6], aInvestLaneC[9], aInvestLaneD[5]
    // index offsets: 273U, 676U, 1894U, 561U, 421U, 67U, 1284U, 1924U
    {
        std::uint8_t *aFragmentA = aInvestLaneB + (W_KEY * 7U), *aFragmentB = aInvestLaneA + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneH + (W_KEY * 0U), *aFragmentD = aInvestLaneG + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneC + (W_KEY * 9U), *aFragmentH = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 273U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 676U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1894U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 561U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 421U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 67U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1284U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1924U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_b row 0
    // read chunks: aInvestLaneG[7], aInvestLaneE[15], aInvestLaneH[12], aInvestLaneD[15], aInvestLaneA[10], aInvestLaneF[8], aInvestLaneB[6], aInvestLaneC[5]
    // index offsets: 1472U, 68U, 1317U, 1755U, 1341U, 1542U, 1488U, 1762U
    {
        std::uint8_t *aFragmentA = aInvestLaneG + (W_KEY * 7U), *aFragmentB = aInvestLaneE + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneH + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneA + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneB + (W_KEY * 6U), *aFragmentH = aInvestLaneC + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1472U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 68U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1317U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1755U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1341U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1542U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1488U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1762U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 1
    // read chunks: aInvestLaneC[12], aInvestLaneE[6], aInvestLaneF[5], aInvestLaneA[12], aInvestLaneH[5], aInvestLaneG[13], aInvestLaneD[6], aInvestLaneB[10]
    // index offsets: 1632U, 1852U, 1337U, 41U, 1999U, 2029U, 1250U, 29U
    {
        std::uint8_t *aFragmentA = aInvestLaneC + (W_KEY * 12U), *aFragmentB = aInvestLaneE + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneF + (W_KEY * 5U), *aFragmentD = aInvestLaneA + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneH + (W_KEY * 5U), *aFragmentF = aInvestLaneG + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneD + (W_KEY * 6U), *aFragmentH = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1632U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1852U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1337U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 41U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1999U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2029U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1250U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 29U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 2
    // read chunks: aInvestLaneE[14], aInvestLaneC[0], aInvestLaneB[2], aInvestLaneH[14], aInvestLaneA[1], aInvestLaneD[4], aInvestLaneG[2], aInvestLaneF[13]
    // index offsets: 874U, 1098U, 278U, 1083U, 1245U, 850U, 294U, 1019U
    {
        std::uint8_t *aFragmentA = aInvestLaneE + (W_KEY * 14U), *aFragmentB = aInvestLaneC + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneB + (W_KEY * 2U), *aFragmentD = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneA + (W_KEY * 1U), *aFragmentF = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 874U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 278U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1083U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1245U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 850U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 294U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1019U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_b row 3
    // read chunks: aInvestLaneD[11], aInvestLaneB[9], aInvestLaneH[8], aInvestLaneG[9], aInvestLaneC[7], aInvestLaneE[4], aInvestLaneA[9], aInvestLaneF[4]
    // index offsets: 1697U, 181U, 746U, 840U, 1075U, 1786U, 251U, 1959U
    {
        std::uint8_t *aFragmentA = aInvestLaneD + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneH + (W_KEY * 8U), *aFragmentD = aInvestLaneG + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneC + (W_KEY * 7U), *aFragmentF = aInvestLaneE + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneA + (W_KEY * 9U), *aFragmentH = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1697U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 181U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 746U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 840U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1075U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1786U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1959U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 4
    // read chunks: aInvestLaneB[14], aInvestLaneG[5], aInvestLaneC[2], aInvestLaneF[12], aInvestLaneA[5], aInvestLaneH[9], aInvestLaneD[0], aInvestLaneE[3]
    // index offsets: 1877U, 2046U, 84U, 586U, 1568U, 690U, 1893U, 1147U
    {
        std::uint8_t *aFragmentA = aInvestLaneB + (W_KEY * 14U), *aFragmentB = aInvestLaneG + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneA + (W_KEY * 5U), *aFragmentF = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneD + (W_KEY * 0U), *aFragmentH = aInvestLaneE + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1877U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2046U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 84U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 586U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1568U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 690U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1893U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1147U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    // key_box_b row 5
    // read chunks: aInvestLaneG[15], aInvestLaneF[0], aInvestLaneD[8], aInvestLaneH[11], aInvestLaneE[1], aInvestLaneA[2], aInvestLaneB[4], aInvestLaneC[8]
    // index offsets: 1174U, 1779U, 205U, 448U, 493U, 875U, 940U, 482U
    {
        std::uint8_t *aFragmentA = aInvestLaneG + (W_KEY * 15U), *aFragmentB = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneD + (W_KEY * 8U), *aFragmentD = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneA + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneB + (W_KEY * 4U), *aFragmentH = aInvestLaneC + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1174U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1779U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 205U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 448U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 493U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 875U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 940U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 482U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    // key_box_b row 6
    // read chunks: aInvestLaneC[14], aInvestLaneB[5], aInvestLaneA[15], aInvestLaneF[9], aInvestLaneG[6], aInvestLaneD[2], aInvestLaneH[3], aInvestLaneE[12]
    // index offsets: 587U, 802U, 103U, 966U, 1685U, 991U, 111U, 1021U
    {
        std::uint8_t *aFragmentA = aInvestLaneC + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneA + (W_KEY * 15U), *aFragmentD = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneG + (W_KEY * 6U), *aFragmentF = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneH + (W_KEY * 3U), *aFragmentH = aInvestLaneE + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 587U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 802U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 103U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 966U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1685U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 991U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 111U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1021U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    // key_box_b row 7
    // read chunks: aInvestLaneH[6], aInvestLaneA[11], aInvestLaneC[3], aInvestLaneB[11], aInvestLaneD[10], aInvestLaneF[2], aInvestLaneG[10], aInvestLaneE[2]
    // index offsets: 2004U, 1867U, 1273U, 285U, 1210U, 1068U, 1205U, 2029U
    {
        std::uint8_t *aFragmentA = aInvestLaneH + (W_KEY * 6U), *aFragmentB = aInvestLaneA + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneD + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneE + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(pWorkSpace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2004U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1867U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1273U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 285U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1210U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1068U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1205U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2029U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Gemma::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint8_t *pSource,
                                       std::uint8_t *pDestination) {
    TwistExpander::TwistBlock(pWorkSpace, pSource, pDestination);
    if ((pWorkSpace == nullptr) || (pDestination == nullptr)) { return; }
    if (mTwistBlockCounter == 0U) {
        SnapShotter::SnapStart_TWIST(pWorkSpace, this);
    }

    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint64_t aPrevious = 0xB2526015D06E8D47ULL; std::uint64_t aIngress = 0xC7BE50D598C23EA7ULL; std::uint64_t aCarry = 0xA5CB7109BD44A683ULL;

    std::uint64_t aWandererA = 0xF0D93CAE9335B5FFULL; std::uint64_t aWandererB = 0xB16390ABBEBE0BCFULL; std::uint64_t aWandererC = 0x945B9A8EDCAE5313ULL; std::uint64_t aWandererD = 0xCD3DE04A4793F492ULL;
    std::uint64_t aWandererE = 0x85CE94E3F233817BULL; std::uint64_t aWandererF = 0x9D3DB203061CF334ULL; std::uint64_t aWandererG = 0xF63E095B5FFC32CCULL; std::uint64_t aWandererH = 0xF1CF90282D04B839ULL;
    std::uint64_t aWandererI = 0xF3BB4A2C2EA6D395ULL; std::uint64_t aWandererJ = 0xD846746F389820B2ULL; std::uint64_t aWandererK = 0xE91435F1F8F355A6ULL;

    // [seed]
        aPrevious = 11058763444101565981U;
        aCarry = 11694063120930178324U;
        aWandererA = 13320913273345522540U;
        aWandererB = 17982502425156596248U;
        aWandererC = 13451352497284260258U;
        aWandererD = 12188666686310980308U;
        aWandererE = 17011208190549443079U;
        aWandererF = 18236779047157507449U;
        aWandererG = 10942723519739664728U;
        aWandererH = 18397754228902536008U;
        aWandererI = 10153997795867297492U;
        aWandererJ = 14217366361867805538U;
        aWandererK = 14791636830497974880U;
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
    TwistExpander_Gemma_Arx::Twist_A(pWorkSpace,
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
    // read from: wind_a, wind_b, wind_c, wind_d
    // temp storage: scrap_a, scrap_b
    // ---------------------------------------------------
    // write to: water_c, water_d, snow_a, snow_b, snow_c, snow_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Twist_B(pWorkSpace,
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
    // read from: snow_a, snow_b, snow_c, snow_d
    // temp storage: water_c, water_d, wind_a, wind_b, wind_c, wind_d
    // ---------------------------------------------------
    // write to: water_a, water_b, fire_a, fire_b, fire_c, fire_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Twist_C(pWorkSpace,
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
    // ---------------------------------------------------
    // GTwistRunTwist_D twist_loop_d:
    // ---------------------------------------------------
    // read from: fire_a, fire_b, fire_c, fire_d
    // temp storage: water_a, water_b, water_c, water_d, wind_a, wind_b, wind_c, wind_d, snow_a, snow_b, snow_c, snow_d
    // ---------------------------------------------------
    // write to: invest_a, invest_b, invest_c, invest_d, earth_a, earth_b, earth_c, earth_d
    // ---------------------------------------------------
    //
    TwistExpander_Gemma_Arx::Twist_D(pWorkSpace,
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

    SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "Twist_D");

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
    TwistExpander_Gemma_Arx::Twist_E(pWorkSpace,
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

    SnapShotter::SnapUpdate_TWIST(pWorkSpace, this, "Twist_E");

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
    TwistExpander_Gemma_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Gemma_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

    mTwistBlockCounter += 1U;
}

void TwistExpander_Gemma::GrowKeyA(TwistWorkSpace *pWorkSpace) {
    TwistExpander::GrowKeyA(pWorkSpace);
    if (pWorkSpace == nullptr) { return; }
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
    std::uint8_t *aFireLaneA = pWorkSpace->mFireLaneA;
    std::uint8_t *aFireLaneB = pWorkSpace->mFireLaneB;
    std::uint8_t *aFireLaneC = pWorkSpace->mFireLaneC;
    std::uint8_t *aFireLaneD = pWorkSpace->mFireLaneD;
    std::uint8_t *aWaterLaneA = pWorkSpace->mWaterLaneA;
    std::uint8_t *aWaterLaneB = pWorkSpace->mWaterLaneB;
    std::uint8_t *aWaterLaneC = pWorkSpace->mWaterLaneC;
    std::uint8_t *aWaterLaneD = pWorkSpace->mWaterLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aScrapLaneC = pWorkSpace->mScrapLaneC;
    std::uint8_t *aScrapLaneD = pWorkSpace->mScrapLaneD;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aInvestLaneA = pWorkSpace->mInvestLaneA;
    std::uint8_t *aInvestLaneB = pWorkSpace->mInvestLaneB;
    std::uint8_t *aInvestLaneC = pWorkSpace->mInvestLaneC;
    std::uint8_t *aInvestLaneD = pWorkSpace->mInvestLaneD;
    std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);
    std::uint64_t *aPhaseGOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltA;
    std::uint64_t *aPhaseGOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltB;
    std::uint64_t *aPhaseGOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltC;
    std::uint64_t *aPhaseGOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltD;
    std::uint64_t *aPhaseGOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltE;
    std::uint64_t *aPhaseGOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterAssign.mSaltF;
    std::uint64_t *aPhaseGOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltA;
    std::uint64_t *aPhaseGOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltB;
    std::uint64_t *aPhaseGOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltC;
    std::uint64_t *aPhaseGOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltD;
    std::uint64_t *aPhaseGOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltE;
    std::uint64_t *aPhaseGOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mOrbiterUpdate.mSaltF;
    std::uint64_t *aPhaseGWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltA;
    std::uint64_t *aPhaseGWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltB;
    std::uint64_t *aPhaseGWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltC;
    std::uint64_t *aPhaseGWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltD;
    std::uint64_t *aPhaseGWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltE;
    std::uint64_t *aPhaseGWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseGSalts.mWandererUpdate.mSaltF;
    std::uint64_t aPrevious = 0xDAC92C7EF1336371ULL; std::uint64_t aIngress = 0x8F90CBC905E449E2ULL; std::uint64_t aCarry = 0xDEC94FAFFD9BFEF8ULL; std::uint64_t aCross = 0;
    std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    std::uint64_t aWandererA = 0xC4155FAECE486E5EULL; std::uint64_t aWandererB = 0xAAA9B92BE1099BD5ULL; std::uint64_t aWandererC = 0xA14AC065E0470865ULL; std::uint64_t aWandererD = 0xF83664021A60203AULL;
    std::uint64_t aWandererE = 0xC5D4CBA8D2106F1BULL; std::uint64_t aWandererF = 0xE6A7AEE652550C79ULL; std::uint64_t aWandererG = 0xC03762D86993D836ULL; std::uint64_t aWandererH = 0xC04485907DD7A366ULL;
    std::uint64_t aWandererI = 0x815E7504FE4947D5ULL; std::uint64_t aWandererJ = 0x83C03E9088AB63E6ULL; std::uint64_t aWandererK = 0xFB06394FEC4D9286ULL;

    // [grow key a]
    // GROW_A grow_key_a (start)
    {
        // grow_key_a loop 1
        // ingress from: aWorkLaneA, aWorkLaneB, aWaterLaneD
        // ingress directions: aWorkLaneA forward forced, aWorkLaneB forward forced, aWaterLaneD forward/backward random
        // cross from: aWorkLaneC, aWorkLaneD, aWaterLaneB
        // cross directions: aWorkLaneC backward forced, aWorkLaneD backward forced, aWaterLaneB backward/forward random
        // write to: aOperationLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 509U)) & S_BLOCK1], 28U) ^ RotL64(aWorkLaneB[((aIndex + 1262U)) & S_BLOCK1], 51U));
            aIngress ^= RotL64(aWaterLaneD[((aIndex + 1843U)) & S_BLOCK1], 11U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 717U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 1442U)) & S_BLOCK1], 24U));
            aCross ^= RotL64(aWaterLaneB[((aIndex + 2652U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aPrevious, 42U) ^ RotL64(aCarry, 23U)) ^ (RotL64(aCross, 11U) + RotL64(aIngress, 57U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterI = ((aWandererG + RotL64(aCross, 44U)) + RotL64(aCarry, 53U)) + 13573748775322384702U;
            aOrbiterC = (aWandererH + RotL64(aIngress, 11U)) + 1508790373766817555U;
            aOrbiterB = (aWandererF + RotL64(aScatter, 53U)) + 4101167033724090291U;
            aOrbiterD = (((aWandererB + RotL64(aPrevious, 3U)) + RotL64(aCarry, 13U)) + 11712259216119276151U) + aPhaseGOrbiterAssignSaltA[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterH = ((aWandererJ + RotL64(aScatter, 27U)) + RotL64(aCarry, 37U)) + 4183080539551663286U;
            aOrbiterE = ((aWandererK + RotL64(aCross, 19U)) + 14111846113516254330U) + aPhaseGOrbiterAssignSaltB[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterA = (aWandererD + RotL64(aIngress, 37U)) + 15062338073599940599U;
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 667358345790213041U) + aPhaseGOrbiterUpdateSaltA[((aIndex + 27U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterI) ^ 4470276278753325517U) ^ aPhaseGOrbiterUpdateSaltE[(((31U - aIndex) + 3U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 4135255924456944021U), 27U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterI) + 8775800577736742329U) + aPhaseGOrbiterUpdateSaltB[(((31U - aIndex) + 7U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 18083275446623452632U;
            aOrbiterH = RotL64((aOrbiterH * 829237560212524205U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 9653168351721037877U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 5705675023433144371U;
            aOrbiterC = RotL64((aOrbiterC * 6328202306903297603U), 51U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 13128905949733348097U;
            aOrbiterI = (aOrbiterI ^ aOrbiterA) ^ 11198088863490178757U;
            aOrbiterI = RotL64((aOrbiterI * 12152687090100570841U), 41U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 614983401398366183U;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 342018619913581783U;
            aOrbiterA = RotL64((aOrbiterA * 17691133405434904445U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterA) + 17670351873147676890U;
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 11118105711778793884U;
            aOrbiterD = RotL64((aOrbiterD * 18036890969455619205U), 19U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 13180630220339767470U) + aPhaseGOrbiterUpdateSaltC[((aIndex + 29U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterB) ^ 9787574387124296787U;
            aOrbiterE = RotL64((aOrbiterE * 11033698515894011169U), 11U);
            //
            aIngress = RotL64(aOrbiterB, 47U) ^ aOrbiterI;
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterA, 35U));
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterE, 11U));
            aIngress = aIngress + RotL64(aOrbiterC, 21U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ ((RotL64(aIngress, 11U) + aOrbiterH) + RotL64(aOrbiterC, 60U));
            aWandererB = aWandererB + (((RotL64(aScatter, 29U) + aOrbiterI) + RotL64(aOrbiterA, 27U)) + RotL64(aCarry, 39U));
            aWandererF = aWandererF ^ ((RotL64(aCross, 51U) + RotL64(aOrbiterH, 47U)) + aOrbiterD);
            aWandererG = aWandererG + ((((RotL64(aPrevious, 4U) + aOrbiterE) + RotL64(aOrbiterA, 19U)) + RotL64(aCarry, 21U)) + aPhaseGWandererUpdateSaltC[((aIndex + 23U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ (((RotL64(aCross, 41U) + aOrbiterB) + RotL64(aOrbiterE, 37U)) + aPhaseGWandererUpdateSaltD[(((31U - aIndex) + 4U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aPrevious, 35U) + RotL64(aOrbiterI, 53U)) + aOrbiterD);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 19U) + RotL64(aOrbiterB, 3U)) + aOrbiterH);
            //
            aCarry = aCarry + (RotL64(aWandererJ, 28U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererG, 57U) ^ aWandererH);
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererK, 11U));
            aCarry = aCarry + RotL64(aWandererD, 47U);
            aCarry = aCarry + RotL64(aIngress, 24U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        // grow_key_a loop 2
        // ingress from: aOperationLaneA, aWorkLaneC, aFireLaneD
        // ingress directions: aOperationLaneA forward forced, aWorkLaneC forward forced, aFireLaneD forward/backward random
        // cross from: aWorkLaneA, aWorkLaneD, aWaterLaneC
        // cross directions: aWorkLaneA backward forced, aWorkLaneD backward forced, aWaterLaneC backward/forward random
        // write to: aOperationLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneA[((aIndex + 8659U)) & S_BLOCK1], 60U) ^ RotL64(aWorkLaneC[((aIndex + 5820U)) & S_BLOCK1], 37U));
            aIngress ^= RotL64(aFireLaneD[((aIndex + 8338U)) & S_BLOCK1], 21U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 9566U)) & S_BLOCK1], 40U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 5474U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aWaterLaneC[((aIndex + 10153U)) & S_BLOCK1], 23U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 3U) ^ RotL64(aPrevious, 53U)) + (RotL64(aIngress, 22U) + RotL64(aCross, 37U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterH = (aWandererF + RotL64(aScatter, 35U)) + 13349300890417403538U;
            aOrbiterE = ((aWandererJ + RotL64(aPrevious, 41U)) + RotL64(aCarry, 57U)) + 4747024557686503915U;
            aOrbiterJ = (((aWandererD + RotL64(aCross, 47U)) + RotL64(aCarry, 13U)) + 9710763067672348740U) + aPhaseGOrbiterAssignSaltC[((aIndex + 4U)) & S_SALT1];
            aOrbiterK = ((aWandererI + RotL64(aIngress, 3U)) + RotL64(aCarry, 39U)) + 9582616234945215131U;
            aOrbiterG = (aWandererG + RotL64(aScatter, 53U)) + 13390500863602398697U;
            aOrbiterC = (aWandererA + RotL64(aCross, 11U)) + 14017648025257021014U;
            aOrbiterF = ((aWandererB + RotL64(aPrevious, 18U)) + 15847595745307503159U) + aPhaseGOrbiterAssignSaltF[(((31U - aIndex) + 6U)) & S_SALT1];
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 1987818040891304702U) + aPhaseGOrbiterUpdateSaltB[((aIndex + 29U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterH) ^ 13788417044574273306U;
            aOrbiterJ = RotL64((aOrbiterJ * 14746707284607477999U), 37U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterG) + 10559380097619249575U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 16U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterK) ^ 7873778436863320784U;
            aOrbiterH = RotL64((aOrbiterH * 8457166541133974129U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 18047427300183846749U;
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 8675513193127111708U;
            aOrbiterK = RotL64((aOrbiterK * 6788306112625411653U), 5U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterK) + 10166487940363266813U) + aPhaseGOrbiterUpdateSaltF[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 1308984468113823759U;
            aOrbiterF = RotL64((aOrbiterF * 14527960816319413671U), 19U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterJ) + 15804865821083864756U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 17977235434944605211U;
            aOrbiterG = RotL64((aOrbiterG * 9474346879853986351U), 57U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterF) + 1239866355903461009U) + aPhaseGOrbiterUpdateSaltD[((aIndex + 24U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 4079484728062556526U;
            aOrbiterE = RotL64((aOrbiterE * 1464227687518008453U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterH) + 13970204155695383009U;
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 12229849460667372629U;
            aOrbiterC = RotL64((aOrbiterC * 10244754882278065637U), 11U);
            //
            aIngress = aOrbiterC ^ RotL64(aOrbiterF, 60U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterH, 37U));
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterK, 53U));
            aIngress = aIngress + RotL64(aOrbiterJ, 23U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aIngress, 57U) + RotL64(aOrbiterF, 27U)) + aOrbiterE);
            aWandererF = aWandererF + (((RotL64(aScatter, 47U) + RotL64(aOrbiterG, 3U)) + aOrbiterK) + RotL64(aCarry, 53U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 21U) + aOrbiterH) + RotL64(aOrbiterF, 11U));
            aWandererG = aWandererG + (((RotL64(aPrevious, 5U) + aOrbiterF) + RotL64(aOrbiterJ, 19U)) + RotL64(aCarry, 41U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 30U) + RotL64(aOrbiterG, 60U)) + aOrbiterC) + aPhaseGWandererUpdateSaltF[((aIndex + 18U)) & S_SALT1]);
            aWandererD = aWandererD + ((RotL64(aIngress, 39U) + RotL64(aOrbiterG, 53U)) + aOrbiterF);
            aWandererI = aWandererI ^ (((RotL64(aCross, 11U) + aOrbiterG) + RotL64(aOrbiterE, 35U)) + aPhaseGWandererUpdateSaltB[(((31U - aIndex) + 9U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererF ^ RotL64(aWandererG, 27U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 38U));
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererJ, 21U));
            aCarry = aCarry + RotL64(aWandererD, 5U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_a loop 3
        // ingress from: aOperationLaneB, aWorkLaneA, aWaterLaneA
        // ingress directions: aOperationLaneB forward forced, aWorkLaneA forward forced, aWaterLaneA forward/backward random
        // cross from: aOperationLaneA, aWorkLaneC, aInvestLaneD
        // cross directions: aOperationLaneA backward forced, aWorkLaneC backward forced, aInvestLaneD backward/forward random
        // write to: aExpandLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneB[((aIndex + 14740U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneA[((aIndex + 12171U)) & S_BLOCK1], 41U));
            aIngress ^= RotL64(aWaterLaneA[((aIndex + 15670U)) & S_BLOCK1], 4U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 13704U)) & S_BLOCK1], 18U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 14179U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aInvestLaneD[((aIndex + 13273U)) & S_BLOCK1], 39U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCarry, 23U) + RotL64(aPrevious, 42U)) + (RotL64(aIngress, 5U) ^ RotL64(aCross, 57U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterH = (((aWandererI + RotL64(aPrevious, 60U)) + RotL64(aCarry, 51U)) + 16226547771815123635U) + aPhaseGOrbiterAssignSaltE[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterF = ((aWandererC + RotL64(aScatter, 53U)) + RotL64(aCarry, 5U)) + 5843079558549373747U;
            aOrbiterD = (aWandererG + RotL64(aIngress, 5U)) + 4305814240870041934U;
            aOrbiterK = (aWandererD + RotL64(aCross, 13U)) + 15980163103992751963U;
            aOrbiterG = ((aWandererA + RotL64(aIngress, 27U)) + RotL64(aCarry, 23U)) + 1016146291835041202U;
            aOrbiterJ = (aWandererK + RotL64(aCross, 39U)) + 10440075547223125578U;
            aOrbiterC = ((aWandererH + RotL64(aScatter, 21U)) + 9171990912720404196U) + aPhaseGOrbiterAssignSaltD[(((31U - aIndex) + 5U)) & S_SALT1];
            //
            aOrbiterH = ((aOrbiterH + aOrbiterF) + 475441034491990129U) + aPhaseGOrbiterUpdateSaltD[((aIndex + 15U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterH) ^ 9819608336350524544U) ^ aPhaseGOrbiterUpdateSaltE[((aIndex + 20U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 2483376418515468913U), 57U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 15945300798800311857U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterK) ^ 11617508541315029705U;
            aOrbiterJ = RotL64((aOrbiterJ * 16669171293959140009U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 3642160581450714603U;
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 12647887280533544709U;
            aOrbiterF = RotL64((aOrbiterF * 9276738523402145261U), 35U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 6016543273344783429U;
            aOrbiterK = (aOrbiterK ^ aOrbiterF) ^ 4320492529184734688U;
            aOrbiterK = RotL64((aOrbiterK * 17512812977517166889U), 29U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 6389944244386706772U;
            aOrbiterH = (aOrbiterH ^ aOrbiterJ) ^ 16344996279964788658U;
            aOrbiterH = RotL64((aOrbiterH * 6857788551814543441U), 51U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterJ) + 16762435553103545386U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 23U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterG) ^ 9652410870558248179U;
            aOrbiterC = RotL64((aOrbiterC * 8796410937404105549U), 11U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterK) + 8428385138274524834U) + aPhaseGOrbiterUpdateSaltF[((aIndex + 21U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 6969713877305605827U;
            aOrbiterG = RotL64((aOrbiterG * 12455712392834922509U), 19U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterJ, 21U);
            aIngress = aIngress + (RotL64(aOrbiterD, 13U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterG, 3U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterK, 60U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ ((RotL64(aCross, 35U) + aOrbiterC) + RotL64(aOrbiterD, 57U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 43U) + RotL64(aOrbiterC, 35U)) + aOrbiterJ) + RotL64(aCarry, 57U));
            aWandererC = aWandererC ^ ((RotL64(aIngress, 51U) + RotL64(aOrbiterH, 27U)) + aOrbiterC);
            aWandererA = aWandererA + ((RotL64(aScatter, 20U) + RotL64(aOrbiterD, 3U)) + aOrbiterF);
            aWandererI = aWandererI ^ (((RotL64(aCross, 11U) + RotL64(aOrbiterC, 43U)) + aOrbiterG) + aPhaseGWandererUpdateSaltA[((aIndex + 29U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aScatter, 3U) + aOrbiterJ) + RotL64(aOrbiterK, 50U)) + RotL64(aCarry, 37U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 27U) + RotL64(aOrbiterK, 13U)) + aOrbiterG) + aPhaseGWandererUpdateSaltE[(((31U - aIndex) + 17U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererK, 23U) ^ aWandererA);
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererI, 46U));
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererD, 57U));
            aCarry = aCarry + RotL64(aWandererH, 35U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        // grow_key_a loop 4
        // ingress from: aExpandLaneA, aWorkLaneD, aInvestLaneA
        // ingress directions: aExpandLaneA forward forced, aWorkLaneD forward forced, aInvestLaneA forward/backward random
        // cross from: aOperationLaneB, aWorkLaneA, aInvestLaneC
        // cross directions: aOperationLaneB backward forced, aWorkLaneA backward forced, aInvestLaneC backward/forward random
        // write to: aExpandLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 16515U)) & S_BLOCK1], 36U) ^ RotL64(aWorkLaneD[((aIndex + 17860U)) & S_BLOCK1], 19U));
            aIngress ^= RotL64(aInvestLaneA[((aIndex + 18522U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 17716U)) & S_BLOCK1], 39U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 17924U)) & S_BLOCK1], 26U));
            aCross ^= RotL64(aInvestLaneC[((S_BLOCK1 - aIndex + 17265U)) & S_BLOCK1], 57U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aIngress, 6U) ^ RotL64(aCarry, 39U)) + (RotL64(aPrevious, 53U) ^ RotL64(aCross, 27U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterC = (aWandererB + RotL64(aScatter, 11U)) + 5006119653500666944U;
            aOrbiterF = (aWandererF + RotL64(aPrevious, 29U)) + 12731377758075368839U;
            aOrbiterG = ((aWandererH + RotL64(aCross, 5U)) + RotL64(aCarry, 3U)) + 9696984853663582145U;
            aOrbiterI = (((aWandererK + RotL64(aIngress, 60U)) + RotL64(aCarry, 19U)) + 7864851163268445360U) + aPhaseGOrbiterAssignSaltB[((aIndex + 19U)) & S_SALT1];
            aOrbiterD = ((aWandererE + RotL64(aPrevious, 47U)) + 15255056930730534052U) + aPhaseGOrbiterAssignSaltA[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterK = (aWandererA + RotL64(aCross, 53U)) + 6299700409709765728U;
            aOrbiterA = ((aWandererD + RotL64(aScatter, 23U)) + RotL64(aCarry, 51U)) + 6977801832794306286U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 1759895484444771358U;
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 12113959235595653807U;
            aOrbiterG = RotL64((aOrbiterG * 1929270821020966107U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterG) + 4556501790387745111U) + aPhaseGOrbiterUpdateSaltB[((aIndex + 13U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterF) ^ 3413603705156224822U;
            aOrbiterI = RotL64((aOrbiterI * 8585304814882555155U), 19U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterD) + 8108788888043222136U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterI) ^ 12455248405990369983U;
            aOrbiterK = RotL64((aOrbiterK * 1575801070353410373U), 27U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 14062084974145250966U;
            aOrbiterA = (aOrbiterA ^ aOrbiterD) ^ 10809749548704923272U;
            aOrbiterA = RotL64((aOrbiterA * 8520522052697004669U), 41U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterA) + 6987631137198614115U) + aPhaseGOrbiterUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterK) ^ 2078179399147020030U;
            aOrbiterC = RotL64((aOrbiterC * 17414555915190929755U), 35U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterC) + 10361280539760095537U;
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 15967536008017364872U;
            aOrbiterF = RotL64((aOrbiterF * 14497469712884538703U), 5U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterI) + 14111385430709173501U) + aPhaseGOrbiterUpdateSaltE[((aIndex + 6U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 12439781574089871032U;
            aOrbiterD = RotL64((aOrbiterD * 3922709139791825835U), 11U);
            //
            aIngress = RotL64(aOrbiterK, 29U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterA, 57U));
            aIngress = aIngress + (RotL64(aOrbiterI, 4U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterF, 47U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH + ((RotL64(aCross, 19U) + RotL64(aOrbiterG, 29U)) + aOrbiterK);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 29U) + RotL64(aOrbiterI, 11U)) + aOrbiterK);
            aWandererF = aWandererF + ((((RotL64(aIngress, 36U) + RotL64(aOrbiterK, 19U)) + aOrbiterC) + RotL64(aCarry, 57U)) + aPhaseGWandererUpdateSaltD[((aIndex + 3U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 13U) + aOrbiterA) + RotL64(aOrbiterK, 35U));
            aWandererA = aWandererA + (((RotL64(aCross, 43U) + aOrbiterD) + RotL64(aOrbiterI, 41U)) + RotL64(aCarry, 21U));
            aWandererB = aWandererB ^ ((RotL64(aScatter, 51U) + RotL64(aOrbiterG, 47U)) + aOrbiterF);
            aWandererK = aWandererK + (((RotL64(aIngress, 5U) + RotL64(aOrbiterC, 54U)) + aOrbiterA) + aPhaseGWandererUpdateSaltC[((aIndex + 23U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererA, 48U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererB, 3U) ^ aWandererF);
            aCarry = aCarry + (RotL64(aWandererD, 23U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererE, 57U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_a loop 5
        // ingress from: aExpandLaneB, aOperationLaneB, aFireLaneC
        // ingress directions: aExpandLaneB forward forced, aOperationLaneB forward forced, aFireLaneC forward/backward random
        // cross from: aExpandLaneA, aOperationLaneA, aFireLaneA
        // cross directions: aExpandLaneA backward forced, aOperationLaneA backward forced, aFireLaneA backward/forward random
        // write to: aExpandLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneB[((aIndex + 26439U)) & S_BLOCK1], 22U) ^ RotL64(aOperationLaneB[((aIndex + 24854U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneC[((S_BLOCK1 - aIndex + 26137U)) & S_BLOCK1], 47U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 21966U)) & S_BLOCK1], 26U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 27252U)) & S_BLOCK1], 39U));
            aCross ^= RotL64(aFireLaneA[((S_BLOCK1 - aIndex + 26595U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCross, 35U) ^ RotL64(aIngress, 23U)) + (RotL64(aCarry, 57U) + RotL64(aPrevious, 10U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterJ = (aWandererK + RotL64(aPrevious, 13U)) + 17809934856350153077U;
            aOrbiterB = ((aWandererI + RotL64(aScatter, 37U)) + 8430454232309043523U) + aPhaseGOrbiterAssignSaltF[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterF = ((aWandererG + RotL64(aIngress, 29U)) + RotL64(aCarry, 51U)) + 15549202871053800086U;
            aOrbiterD = (((aWandererA + RotL64(aCross, 19U)) + RotL64(aCarry, 5U)) + 5998508141268055909U) + aPhaseGOrbiterAssignSaltC[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterG = ((aWandererF + RotL64(aScatter, 56U)) + RotL64(aCarry, 19U)) + 1243264108047220903U;
            aOrbiterI = (aWandererC + RotL64(aCross, 43U)) + 6563186430453201837U;
            aOrbiterH = (aWandererJ + RotL64(aPrevious, 5U)) + 15872520028936069678U;
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 5559659247211217901U;
            aOrbiterF = (aOrbiterF ^ aOrbiterJ) ^ 2756366676852835100U;
            aOrbiterF = RotL64((aOrbiterF * 462022063105139269U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 10186062197196127260U;
            aOrbiterG = (aOrbiterG ^ aOrbiterD) ^ 16676493757625497289U;
            aOrbiterG = RotL64((aOrbiterG * 10573304383098963515U), 19U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 5795387499115683693U;
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 5398673777022738318U;
            aOrbiterI = RotL64((aOrbiterI * 15675766711369546075U), 41U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 9464760115716862962U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterI) ^ 7372912459502541319U) ^ aPhaseGOrbiterUpdateSaltD[(((31U - aIndex) + 15U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 16732875545732743989U), 35U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterD) + 12205765123959222390U) + aPhaseGOrbiterUpdateSaltC[((aIndex + 23U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 782553668587049108U;
            aOrbiterB = RotL64((aOrbiterB * 13999628963075083927U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterF) + 18078885036992904489U;
            aOrbiterH = (aOrbiterH ^ aOrbiterG) ^ 1235102260315547880U;
            aOrbiterH = RotL64((aOrbiterH * 1005598117821971313U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 11308998383593806224U) + aPhaseGOrbiterUpdateSaltB[(((31U - aIndex) + 17U)) & S_SALT1];
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 1028072383538456894U) ^ aPhaseGOrbiterUpdateSaltF[((aIndex + 12U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 359231290689954859U), 13U);
            //
            aIngress = aOrbiterI ^ RotL64(aOrbiterF, 13U);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterH, 57U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterB, 47U));
            aIngress = aIngress + RotL64(aOrbiterG, 21U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aIngress, 47U) + RotL64(aOrbiterF, 11U)) + aOrbiterI);
            aWandererC = aWandererC + (((RotL64(aPrevious, 20U) + RotL64(aOrbiterJ, 27U)) + aOrbiterF) + RotL64(aCarry, 47U));
            aWandererI = aWandererI ^ (((RotL64(aScatter, 41U) + aOrbiterB) + RotL64(aOrbiterH, 57U)) + aPhaseGWandererUpdateSaltF[((aIndex + 9U)) & S_SALT1]);
            aWandererF = aWandererF + ((((RotL64(aCross, 35U) + RotL64(aOrbiterG, 39U)) + aOrbiterB) + RotL64(aCarry, 29U)) + aPhaseGWandererUpdateSaltB[((aIndex + 3U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 3U) + RotL64(aOrbiterI, 21U)) + aOrbiterJ);
            aWandererG = aWandererG + ((RotL64(aPrevious, 27U) + aOrbiterG) + RotL64(aOrbiterH, 50U));
            aWandererK = aWandererK ^ ((RotL64(aCross, 57U) + aOrbiterD) + RotL64(aOrbiterF, 5U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 53U) ^ aWandererJ);
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererA, 48U));
            aCarry = aCarry + (RotL64(aWandererK, 5U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererC, 43U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        // grow_key_a loop 6
        // ingress from: aExpandLaneC, aExpandLaneA, aFireLaneB
        // ingress directions: aExpandLaneC forward forced, aExpandLaneA forward forced, aFireLaneB forward/backward random
        // cross from: aExpandLaneB, aWorkLaneB, aInvestLaneB
        // cross directions: aExpandLaneB backward forced, aWorkLaneB backward forced, aInvestLaneB backward/forward random
        // write to: aExpandLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneC[((aIndex + 29955U)) & S_BLOCK1], 4U) ^ RotL64(aExpandLaneA[((aIndex + 29617U)) & S_BLOCK1], 13U));
            aIngress ^= RotL64(aFireLaneB[((aIndex + 29735U)) & S_BLOCK1], 23U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 29290U)) & S_BLOCK1], 53U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 29367U)) & S_BLOCK1], 13U));
            aCross ^= RotL64(aInvestLaneB[((S_BLOCK1 - aIndex + 32201U)) & S_BLOCK1], 40U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aCarry, 20U) + RotL64(aIngress, 53U)) ^ (RotL64(aCross, 37U) + RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseB(aScatter);
            //
            aOrbiterD = (aWandererD + RotL64(aIngress, 4U)) + 623174123981201047U;
            aOrbiterA = (aWandererA + RotL64(aScatter, 13U)) + 5974052412316028335U;
            aOrbiterF = ((aWandererC + RotL64(aPrevious, 41U)) + 2831329879893180984U) + aPhaseGOrbiterAssignSaltE[((aIndex + 25U)) & S_SALT1];
            aOrbiterJ = ((aWandererH + RotL64(aCross, 23U)) + RotL64(aCarry, 5U)) + 12101135778897109293U;
            aOrbiterK = ((aWandererG + RotL64(aScatter, 57U)) + RotL64(aCarry, 21U)) + 2733335464569384523U;
            aOrbiterI = ((aWandererF + RotL64(aIngress, 47U)) + 8923891957314998458U) + aPhaseGOrbiterAssignSaltD[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterG = ((aWandererI + RotL64(aPrevious, 29U)) + RotL64(aCarry, 53U)) + 7507530446661534495U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 7324042513423404173U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 5255355591163176063U;
            aOrbiterF = RotL64((aOrbiterF * 16933950345172569431U), 51U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterJ) + 7852175027306750593U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterA) ^ 9999405293527672705U) ^ aPhaseGOrbiterUpdateSaltC[((aIndex + 3U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 18211832151369574313U), 11U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 6890816887717959986U) + aPhaseGOrbiterUpdateSaltF[((aIndex + 4U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 2401514672352436125U;
            aOrbiterJ = RotL64((aOrbiterJ * 3064270012809716071U), 19U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 6726983415252511908U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterJ) ^ 10730743857925907615U) ^ aPhaseGOrbiterUpdateSaltD[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 14937219816766233263U), 43U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterI) + 7146923184717377661U) + aPhaseGOrbiterUpdateSaltA[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterA = (aOrbiterA ^ aOrbiterG) ^ 9498496063941177874U;
            aOrbiterA = RotL64((aOrbiterA * 9406303791278819091U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 1135390523730972389U;
            aOrbiterI = (aOrbiterI ^ aOrbiterK) ^ 13550890042572148497U;
            aOrbiterI = RotL64((aOrbiterI * 11770689145593172861U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 6291994375487870700U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 11582684513845885118U;
            aOrbiterG = RotL64((aOrbiterG * 12514116839612505319U), 27U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterJ, 52U);
            aIngress = aIngress + (RotL64(aOrbiterG, 19U) ^ aOrbiterF);
            aIngress = aIngress + (RotL64(aOrbiterK, 43U) ^ aOrbiterI);
            aIngress = aIngress + RotL64(aOrbiterD, 29U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 35U) + aOrbiterF) + RotL64(aOrbiterD, 43U));
            aWandererD = aWandererD + ((((RotL64(aCross, 4U) + RotL64(aOrbiterK, 27U)) + aOrbiterA) + RotL64(aCarry, 13U)) + aPhaseGWandererUpdateSaltA[((aIndex + 17U)) & S_SALT1]);
            aWandererC = aWandererC ^ ((RotL64(aScatter, 13U) + RotL64(aOrbiterG, 19U)) + aOrbiterJ);
            aWandererG = aWandererG + ((((RotL64(aIngress, 43U) + aOrbiterI) + RotL64(aOrbiterG, 11U)) + RotL64(aCarry, 53U)) + aPhaseGWandererUpdateSaltE[((aIndex + 23U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aScatter, 51U) + RotL64(aOrbiterK, 58U)) + aOrbiterD);
            aWandererI = aWandererI + ((RotL64(aCross, 23U) + aOrbiterG) + RotL64(aOrbiterA, 37U));
            aWandererA = aWandererA ^ ((RotL64(aIngress, 29U) + RotL64(aOrbiterD, 51U)) + aOrbiterA);
            //
            aCarry = aCarry + (RotL64(aWandererC, 41U) ^ aWandererI);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererA, 57U));
            aCarry = aCarry + (RotL64(aWandererG, 20U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererD, 35U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GROW_A grow_key_a (end)
    // GKeyFoldA grow_key_a_fold (start)
    static_assert((S_BLOCK / W_KEY) == 16, "GKeyFoldA expects 16 key-row chunks.");
    TwistShiftBox::ShiftKeyBoxA(pWorkSpace);
    {
        // read from: aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD
        // byte shifts: 0U, 24U, 8U, 16U; diffuse: DiffuseB
        // write to: aScrapLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aIndex]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aIndex]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aIndex]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aIndex]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA source quarters 3, 1, 0, 2 with offsets 2071U, 7263U, 1494U, 102U
        // byte shifts: 8U, 0U, 16U, 24U; diffuse: DiffuseC
        // write to: aMergeLaneA [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2071U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7263U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1494U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 102U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA source quarters 1, 2, 3, 1 with offsets 7508U, 3017U, 4162U, 3650U
        // byte shifts: 16U, 24U, 0U, 8U; diffuse: DiffuseC
        // write to: aMergeLaneB [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7508U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3017U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4162U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3650U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA source quarters 2, 0, 1, 3 with offsets 3781U, 6945U, 3167U, 6477U
        // byte shifts: 8U, 24U, 0U, 16U; diffuse: DiffuseC
        // write to: aMergeLaneC [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3781U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6945U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6477U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA source quarters 0, 3, 2, 0 with offsets 4809U, 2717U, 8067U, 5784U
        // byte shifts: 16U, 0U, 8U, 24U; diffuse: DiffuseA
        // write to: aMergeLaneD [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4809U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2717U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8067U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5784U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aMergeLaneA fragments 0, 3, 2, 1 with offsets 462U, 1547U, 1364U, 208U
        // byte shifts: 8U, 24U, 0U, 16U; diffuse: DiffuseC
        // write to: aScrapLaneA [0..<W_KEY]
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 462U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1547U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1364U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 208U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aMergeLaneB fragments 2, 0, 1, 3 with offsets 1721U, 754U, 1101U, 1539U
        // byte shifts: 8U, 24U, 0U, 16U; diffuse: DiffuseC
        // write to: aScrapLaneB [0..<W_KEY]
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1721U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 754U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1101U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1539U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aMergeLaneC fragments 2, 3, 0, 1 with offsets 1726U, 668U, 767U, 66U
        // byte shifts: 24U, 16U, 8U, 0U; diffuse: DiffuseA
        // write to: aScrapLaneC [0..<W_KEY]
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1726U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 668U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 767U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 66U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aMergeLaneD fragments 0, 1, 2, 3 with offsets 82U, 347U, 2028U, 1564U
        // byte shifts: 8U, 16U, 24U, 0U; diffuse: DiffuseA
        // write to: aScrapLaneD [0..<W_KEY]
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 82U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 347U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2028U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1564U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA, aScrapLaneB, aScrapLaneC, aScrapLaneD [0..<W_KEY]
        // offsets: 481U, 364U, 1562U, 635U
        // byte shifts: 16U, 8U, 24U, 0U; diffuse: DiffuseA
        // write to: aKeyRowWriteA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 481U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 364U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1562U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 635U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
    // GKeyFoldA grow_key_a_fold (end)
}

void TwistExpander_Gemma::GrowKeyB(TwistWorkSpace *pWorkSpace) {
    TwistExpander::GrowKeyB(pWorkSpace);
    if (pWorkSpace == nullptr) { return; }
    std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    std::uint8_t *aEarthLaneA = pWorkSpace->mEarthLaneA;
    std::uint8_t *aEarthLaneB = pWorkSpace->mEarthLaneB;
    std::uint8_t *aEarthLaneC = pWorkSpace->mEarthLaneC;
    std::uint8_t *aEarthLaneD = pWorkSpace->mEarthLaneD;
    std::uint8_t *aWindLaneA = pWorkSpace->mWindLaneA;
    std::uint8_t *aWindLaneB = pWorkSpace->mWindLaneB;
    std::uint8_t *aWindLaneC = pWorkSpace->mWindLaneC;
    std::uint8_t *aWindLaneD = pWorkSpace->mWindLaneD;
    std::uint8_t *aScrapLaneA = pWorkSpace->mScrapLaneA;
    std::uint8_t *aScrapLaneB = pWorkSpace->mScrapLaneB;
    std::uint8_t *aMergeLaneA = pWorkSpace->mMergeLaneA;
    std::uint8_t *aMergeLaneB = pWorkSpace->mMergeLaneB;
    std::uint8_t *aMergeLaneC = pWorkSpace->mMergeLaneC;
    std::uint8_t *aMergeLaneD = pWorkSpace->mMergeLaneD;
    std::uint8_t *aInvestLaneE = pWorkSpace->mInvestLaneE;
    std::uint8_t *aInvestLaneF = pWorkSpace->mInvestLaneF;
    std::uint8_t *aInvestLaneG = pWorkSpace->mInvestLaneG;
    std::uint8_t *aInvestLaneH = pWorkSpace->mInvestLaneH;
    std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);
    std::uint64_t *aPhaseHOrbiterAssignSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltA;
    std::uint64_t *aPhaseHOrbiterAssignSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltB;
    std::uint64_t *aPhaseHOrbiterAssignSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltC;
    std::uint64_t *aPhaseHOrbiterAssignSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltD;
    std::uint64_t *aPhaseHOrbiterAssignSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltE;
    std::uint64_t *aPhaseHOrbiterAssignSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterAssign.mSaltF;
    std::uint64_t *aPhaseHOrbiterUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltA;
    std::uint64_t *aPhaseHOrbiterUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltB;
    std::uint64_t *aPhaseHOrbiterUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltC;
    std::uint64_t *aPhaseHOrbiterUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltD;
    std::uint64_t *aPhaseHOrbiterUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltE;
    std::uint64_t *aPhaseHOrbiterUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mOrbiterUpdate.mSaltF;
    std::uint64_t *aPhaseHWandererUpdateSaltA = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltA;
    std::uint64_t *aPhaseHWandererUpdateSaltB = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltB;
    std::uint64_t *aPhaseHWandererUpdateSaltC = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltC;
    std::uint64_t *aPhaseHWandererUpdateSaltD = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltD;
    std::uint64_t *aPhaseHWandererUpdateSaltE = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltE;
    std::uint64_t *aPhaseHWandererUpdateSaltF = pWorkSpace->mDomainBundle.mPhaseHSalts.mWandererUpdate.mSaltF;
    std::uint64_t aPrevious = 0xF1A8DB1DFDA5E4F2ULL; std::uint64_t aIngress = 0xCEF0EB65B59FEEB8ULL; std::uint64_t aCarry = 0xBDE07E988FBC5ADBULL; std::uint64_t aCross = 0;
    std::uint64_t aScatter = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    std::uint64_t aWandererA = 0xDD8C79A138B57C70ULL; std::uint64_t aWandererB = 0x811AB52CFBA0BDD3ULL; std::uint64_t aWandererC = 0xE0E17D2610746793ULL; std::uint64_t aWandererD = 0xAE3DE0AD314EB45FULL;
    std::uint64_t aWandererE = 0xBAD7F8DE0CAEB310ULL; std::uint64_t aWandererF = 0xE2B4961AEE996DBCULL; std::uint64_t aWandererG = 0x95ACB3AB2B4BE778ULL; std::uint64_t aWandererH = 0x9930E6120CCD48D3ULL;
    std::uint64_t aWandererI = 0xEA6DDF325A58B898ULL; std::uint64_t aWandererJ = 0x9210B3441A6AF31AULL; std::uint64_t aWandererK = 0xA41F8061AFED415DULL;

    // [grow key b]
    // GROW_B grow_key_b (start)
    {
        // grow_key_b loop 1
        // ingress from: aExpandLaneA, aExpandLaneB, aEarthLaneA
        // ingress directions: aExpandLaneA forward forced, aExpandLaneB forward forced, aEarthLaneA forward/backward random
        // cross from: aExpandLaneC, aExpandLaneD, aEarthLaneB
        // cross directions: aExpandLaneC backward forced, aExpandLaneD backward forced, aEarthLaneB backward/forward random
        // write to: aOperationLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aExpandLaneA[((aIndex + 2825U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneB[((aIndex + 4145U)) & S_BLOCK1], 30U));
            aIngress ^= RotL64(aEarthLaneA[((aIndex + 4236U)) & S_BLOCK1], 3U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 2999U)) & S_BLOCK1], 39U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 5203U)) & S_BLOCK1], 48U));
            aCross ^= RotL64(aEarthLaneB[((aIndex + 3635U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 3U) + RotL64(aCarry, 40U)) ^ (RotL64(aCross, 53U) ^ RotL64(aPrevious, 21U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterB = (aWandererK + RotL64(aIngress, 11U)) + 14026236449040551455U;
            aOrbiterA = ((aWandererA + RotL64(aCross, 20U)) + 15935331187222885821U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 6U)) & S_SALT1];
            aOrbiterF = (((aWandererB + RotL64(aPrevious, 35U)) + RotL64(aCarry, 29U)) + 2326691492337153556U) + aPhaseHOrbiterAssignSaltA[((aIndex + 21U)) & S_SALT1];
            aOrbiterE = (aWandererC + RotL64(aScatter, 47U)) + 889756524911482426U;
            aOrbiterJ = (aWandererG + RotL64(aCross, 5U)) + 1739159498119106122U;
            aOrbiterH = (aWandererJ + RotL64(aPrevious, 39U)) + 7310031653915456337U;
            aOrbiterK = ((aWandererD + RotL64(aScatter, 43U)) + RotL64(aCarry, 13U)) + 1167734455875292779U;
            aOrbiterD = ((aWandererH + RotL64(aIngress, 27U)) + RotL64(aCarry, 41U)) + 777762718097789858U;
            aOrbiterG = (aWandererI + RotL64(aCross, 54U)) + 1644760532996967281U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 10940326146776721766U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterB) ^ 15328249595286143717U) ^ aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 24U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 4644548765796417381U), 47U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterJ) + 3181692772114099003U) + aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 10U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 2893632561951406625U;
            aOrbiterB = RotL64((aOrbiterB * 17512035650521846213U), 57U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterB) + 15728918215244268537U;
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 14920526483450351796U;
            aOrbiterK = RotL64((aOrbiterK * 4136156265069341167U), 13U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterD) + 3563007744856752991U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 10290055569653430439U;
            aOrbiterA = RotL64((aOrbiterA * 3827335946052215311U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 3081973006069128181U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterK) ^ 3808430990302142296U) ^ aPhaseHOrbiterUpdateSaltC[((aIndex + 25U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 17092321447154300283U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterG) + 14361867162011847346U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterF) ^ 16712285095458279190U) ^ aPhaseHOrbiterUpdateSaltB[((aIndex + 19U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 4738643062534406509U), 51U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterH) + 14066124381845077688U;
            aOrbiterG = (aOrbiterG ^ aOrbiterA) ^ 9289663079782743416U;
            aOrbiterG = RotL64((aOrbiterG * 11037713381473992149U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 16878932578775064746U;
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 3800450138739386012U;
            aOrbiterE = RotL64((aOrbiterE * 9867718771471937947U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterE) + 14382553751319031841U;
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 9912965760400635999U;
            aOrbiterH = RotL64((aOrbiterH * 15302779109210682385U), 35U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterK, 19U);
            aIngress = aIngress + (RotL64(aOrbiterD, 56U) ^ aOrbiterG);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterE, 47U));
            aIngress = aIngress + (aOrbiterH ^ RotL64(aOrbiterB, 23U));
            aIngress = aIngress + RotL64(aOrbiterJ, 13U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ ((RotL64(aScatter, 47U) + aOrbiterG) + RotL64(aOrbiterA, 47U));
            aWandererG = aWandererG + ((RotL64(aIngress, 35U) + aOrbiterF) + RotL64(aOrbiterG, 19U));
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 19U) + RotL64(aOrbiterA, 29U)) + aOrbiterK);
            aWandererH = aWandererH + ((RotL64(aCross, 53U) + aOrbiterF) + RotL64(aOrbiterD, 37U));
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 12U) + RotL64(aOrbiterE, 54U)) + aOrbiterF) + aPhaseHWandererUpdateSaltD[((aIndex + 13U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aScatter, 39U) + aOrbiterB) + RotL64(aOrbiterE, 5U)) + RotL64(aCarry, 47U));
            aWandererI = aWandererI ^ ((RotL64(aCross, 27U) + aOrbiterA) + RotL64(aOrbiterH, 41U));
            aWandererJ = aWandererJ + ((((RotL64(aIngress, 5U) + RotL64(aOrbiterA, 13U)) + aOrbiterE) + RotL64(aCarry, 3U)) + aPhaseHWandererUpdateSaltC[(((31U - aIndex) + 3U)) & S_SALT1]);
            aWandererA = aWandererA ^ ((RotL64(aScatter, 58U) + aOrbiterJ) + RotL64(aOrbiterA, 58U));
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererD, 42U));
            aCarry = aCarry + (RotL64(aWandererG, 47U) ^ aWandererA);
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererB, 3U));
            aCarry = aCarry + (RotL64(aWandererC, 57U) ^ aWandererI);
            aCarry = aCarry + RotL64(aWandererK, 27U);
            aCarry = aCarry + RotL64(aIngress, 19U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        // grow_key_b loop 2
        // ingress from: aOperationLaneC, aExpandLaneC, aEarthLaneD
        // ingress directions: aOperationLaneC forward forced, aExpandLaneC forward forced, aEarthLaneD forward/backward random
        // cross from: aExpandLaneA, aExpandLaneD, aWindLaneB
        // cross directions: aExpandLaneA backward forced, aExpandLaneD backward forced, aWindLaneB backward/forward random
        // write to: aOperationLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneC[((aIndex + 8136U)) & S_BLOCK1], 10U) ^ RotL64(aExpandLaneC[((aIndex + 7865U)) & S_BLOCK1], 27U));
            aIngress ^= RotL64(aEarthLaneD[((aIndex + 5784U)) & S_BLOCK1], 53U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 7370U)) & S_BLOCK1], 35U) ^ RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 8454U)) & S_BLOCK1], 47U));
            aCross ^= RotL64(aWindLaneB[((S_BLOCK1 - aIndex + 8356U)) & S_BLOCK1], 58U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aIngress, 39U) + RotL64(aCarry, 21U)) ^ (RotL64(aCross, 6U) ^ RotL64(aPrevious, 51U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterH = (aWandererI + RotL64(aScatter, 47U)) + 17742031215909498728U;
            aOrbiterK = ((aWandererK + RotL64(aCross, 52U)) + 17946156073587220548U) + aPhaseHOrbiterAssignSaltC[((aIndex + 7U)) & S_SALT1];
            aOrbiterB = (aWandererH + RotL64(aPrevious, 43U)) + 1798127232233831617U;
            aOrbiterD = ((aWandererF + RotL64(aIngress, 37U)) + RotL64(aCarry, 39U)) + 7107546980331046494U;
            aOrbiterJ = (((aWandererC + RotL64(aPrevious, 19U)) + RotL64(aCarry, 5U)) + 852994164338612577U) + aPhaseHOrbiterAssignSaltB[((aIndex + 23U)) & S_SALT1];
            aOrbiterI = (aWandererB + RotL64(aCross, 23U)) + 15151245667038584889U;
            aOrbiterG = (aWandererE + RotL64(aScatter, 60U)) + 3107353022442759837U;
            aOrbiterE = (aWandererG + RotL64(aIngress, 11U)) + 7939589876004272753U;
            aOrbiterC = ((aWandererA + RotL64(aCross, 3U)) + RotL64(aCarry, 19U)) + 12253312928064990756U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterK) + 7400326131889976684U;
            aOrbiterB = (aOrbiterB ^ aOrbiterH) ^ 8451431524288489944U;
            aOrbiterB = RotL64((aOrbiterB * 6109890886559886091U), 43U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 3516937412435713619U;
            aOrbiterK = (aOrbiterK ^ aOrbiterD) ^ 18079498329443479155U;
            aOrbiterK = RotL64((aOrbiterK * 17104253606997313725U), 3U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 16838599799272474669U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 16270394444787893462U;
            aOrbiterG = RotL64((aOrbiterG * 9508622033109874651U), 27U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterE) + 10837465865802158308U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 16859500618376922927U) ^ aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 11304959042454373361U), 35U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 1245626985281587612U) + aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 12U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterE) ^ 12287802894335701061U;
            aOrbiterH = RotL64((aOrbiterH * 8253770936772900415U), 23U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterC) + 11882945384098024252U) + aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 14U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterG) ^ 13569940920588245547U;
            aOrbiterJ = RotL64((aOrbiterJ * 11427382202428624393U), 11U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 354812166316342790U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 1170089391555418558U;
            aOrbiterE = RotL64((aOrbiterE * 7643939990616220811U), 51U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterH) + 826054161383800350U;
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 8134458439198259102U;
            aOrbiterC = RotL64((aOrbiterC * 11435190727075595201U), 39U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 14286145001842844335U;
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 8182041785451027551U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 4U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8756950228312765147U), 57U);
            //
            aIngress = RotL64(aOrbiterG, 39U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterK, 51U));
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterC, 23U));
            aIngress = aIngress + (aOrbiterI ^ RotL64(aOrbiterD, 46U));
            aIngress = aIngress + RotL64(aOrbiterB, 19U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererG = aWandererG + ((RotL64(aScatter, 3U) + aOrbiterC) + RotL64(aOrbiterG, 52U));
            aWandererB = aWandererB ^ (((RotL64(aIngress, 18U) + aOrbiterB) + RotL64(aOrbiterH, 37U)) + aPhaseHWandererUpdateSaltA[((aIndex + 25U)) & S_SALT1]);
            aWandererF = aWandererF + (((RotL64(aCross, 57U) + aOrbiterJ) + RotL64(aOrbiterD, 5U)) + RotL64(aCarry, 13U));
            aWandererC = aWandererC ^ ((RotL64(aPrevious, 43U) + aOrbiterI) + RotL64(aOrbiterH, 23U));
            aWandererH = aWandererH + ((RotL64(aCross, 11U) + aOrbiterC) + RotL64(aOrbiterI, 57U));
            aWandererE = aWandererE ^ ((RotL64(aPrevious, 38U) + RotL64(aOrbiterI, 46U)) + aOrbiterJ);
            aWandererI = aWandererI + ((RotL64(aIngress, 29U) + aOrbiterJ) + RotL64(aOrbiterH, 13U));
            aWandererK = aWandererK ^ (((RotL64(aScatter, 47U) + RotL64(aOrbiterK, 27U)) + aOrbiterD) + aPhaseHWandererUpdateSaltF[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aIngress, 53U) + RotL64(aOrbiterG, 41U)) + aOrbiterE) + RotL64(aCarry, 41U));
            //
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 19U));
            aCarry = aCarry + (RotL64(aWandererI, 36U) ^ aWandererH);
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererC, 29U));
            aCarry = aCarry + (RotL64(aWandererF, 39U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererA, 43U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_b loop 3
        // ingress from: aOperationLaneD, aExpandLaneA, aEarthLaneC
        // ingress directions: aOperationLaneD forward forced, aExpandLaneA forward forced, aEarthLaneC forward/backward random
        // cross from: aOperationLaneC, aExpandLaneC, aInvestLaneG
        // cross directions: aOperationLaneC backward forced, aExpandLaneC backward forced, aInvestLaneG backward/forward random
        // write to: aWorkLaneA
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aOperationLaneD[((aIndex + 14820U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneA[((aIndex + 11055U)) & S_BLOCK1], 41U));
            aIngress ^= RotL64(aEarthLaneC[((S_BLOCK1 - aIndex + 16314U)) & S_BLOCK1], 52U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 16103U)) & S_BLOCK1], 44U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 13597U)) & S_BLOCK1], 29U));
            aCross ^= RotL64(aInvestLaneG[((aIndex + 14505U)) & S_BLOCK1], 53U);
            aCross = TwistMix64::DiffuseC(aCross);
            //
            aScatter = (RotL64(aCarry, 35U) + RotL64(aIngress, 53U)) ^ (RotL64(aCross, 18U) ^ RotL64(aPrevious, 3U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterA = (aWandererA + RotL64(aScatter, 11U)) + 13312771810102402154U;
            aOrbiterC = ((aWandererD + RotL64(aPrevious, 30U)) + RotL64(aCarry, 11U)) + 2408701477078769210U;
            aOrbiterB = (aWandererH + RotL64(aCross, 53U)) + 15898175696098902918U;
            aOrbiterI = (aWandererE + RotL64(aIngress, 43U)) + 17086827176216509387U;
            aOrbiterG = ((aWandererK + RotL64(aPrevious, 21U)) + 18154376208390426980U) + aPhaseHOrbiterAssignSaltF[(((31U - aIndex) + 22U)) & S_SALT1];
            aOrbiterF = ((aWandererG + RotL64(aScatter, 47U)) + RotL64(aCarry, 23U)) + 17343153562163595315U;
            aOrbiterH = ((aWandererJ + RotL64(aIngress, 5U)) + RotL64(aCarry, 3U)) + 5274974849186456440U;
            aOrbiterE = ((aWandererF + RotL64(aCross, 39U)) + 12655986225149550089U) + aPhaseHOrbiterAssignSaltD[((aIndex + 5U)) & S_SALT1];
            aOrbiterD = (aWandererC + RotL64(aPrevious, 26U)) + 13108461624891702257U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 15573088734931412140U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 10U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterA) ^ 15463940386343127480U) ^ aPhaseHOrbiterUpdateSaltE[((aIndex + 6U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 15575184014199171553U), 13U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterG) + 3590974717405182103U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 5215059170766789825U;
            aOrbiterF = RotL64((aOrbiterF * 747255113576132589U), 29U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 1010887598510694914U;
            aOrbiterA = (aOrbiterA ^ aOrbiterH) ^ 777176848609835859U;
            aOrbiterA = RotL64((aOrbiterA * 10725714937997958449U), 23U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterH) + 10942153294252110364U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterB) ^ 14023654893132397865U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 15U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 9643936358054561345U), 47U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterA) + 9004968496985878099U;
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 16269403060579132393U;
            aOrbiterD = RotL64((aOrbiterD * 11253350093482752651U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterF) + 8982618862206248714U;
            aOrbiterH = (aOrbiterH ^ aOrbiterC) ^ 10185443366031747807U;
            aOrbiterH = RotL64((aOrbiterH * 374469939028734721U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 14774556026838295916U;
            aOrbiterC = (aOrbiterC ^ aOrbiterE) ^ 9666233136622314124U;
            aOrbiterC = RotL64((aOrbiterC * 510769722913612343U), 57U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterB) + 11766416526101706177U;
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 9925079043964769891U;
            aOrbiterI = RotL64((aOrbiterI * 17220173954338040627U), 37U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 13522648733577548745U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 4509514210598500757U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 9818460969314281785U), 41U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterF, 11U);
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterE, 19U));
            aIngress = aIngress + (RotL64(aOrbiterI, 5U) ^ aOrbiterD);
            aIngress = aIngress + (RotL64(aOrbiterA, 46U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterC, 41U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ (((RotL64(aCross, 28U) + RotL64(aOrbiterI, 57U)) + aOrbiterE) + aPhaseHWandererUpdateSaltE[((aIndex + 4U)) & S_SALT1]);
            aWandererA = aWandererA + (((RotL64(aIngress, 11U) + RotL64(aOrbiterI, 48U)) + aOrbiterD) + RotL64(aCarry, 41U));
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 57U) + RotL64(aOrbiterG, 3U)) + aOrbiterB) + aPhaseHWandererUpdateSaltB[(((31U - aIndex) + 17U)) & S_SALT1]);
            aWandererH = aWandererH + ((RotL64(aScatter, 43U) + RotL64(aOrbiterB, 39U)) + aOrbiterA);
            aWandererK = aWandererK ^ ((RotL64(aIngress, 5U) + aOrbiterD) + RotL64(aOrbiterA, 29U));
            aWandererE = aWandererE + (((RotL64(aPrevious, 19U) + aOrbiterE) + RotL64(aOrbiterH, 52U)) + RotL64(aCarry, 29U));
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 47U) + aOrbiterG) + RotL64(aOrbiterD, 35U));
            aWandererG = aWandererG + ((RotL64(aCross, 24U) + RotL64(aOrbiterD, 13U)) + aOrbiterF);
            aWandererF = aWandererF ^ ((RotL64(aPrevious, 51U) + RotL64(aOrbiterC, 23U)) + aOrbiterF);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererC, 57U));
            aCarry = aCarry + (RotL64(aWandererD, 30U) ^ aWandererK);
            aCarry = aCarry + (aWandererE ^ RotL64(aWandererG, 3U));
            aCarry = aCarry + (RotL64(aWandererF, 11U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererJ, 41U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        // grow_key_b loop 4
        // ingress from: aWorkLaneA, aExpandLaneD, aInvestLaneF
        // ingress directions: aWorkLaneA forward forced, aExpandLaneD forward forced, aInvestLaneF forward/backward random
        // cross from: aOperationLaneD, aExpandLaneA, aWindLaneD
        // cross directions: aOperationLaneD backward forced, aExpandLaneA backward forced, aWindLaneD backward/forward random
        // write to: aWorkLaneB
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneA[((aIndex + 19024U)) & S_BLOCK1], 23U) ^ RotL64(aExpandLaneD[((aIndex + 18835U)) & S_BLOCK1], 5U));
            aIngress ^= RotL64(aInvestLaneF[((aIndex + 18320U)) & S_BLOCK1], 50U);
            aIngress = TwistMix64::DiffuseC(aIngress);
            //
            aCross = (RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 21043U)) & S_BLOCK1], 37U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 18004U)) & S_BLOCK1], 10U));
            aCross ^= RotL64(aWindLaneD[((S_BLOCK1 - aIndex + 18572U)) & S_BLOCK1], 21U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aPrevious, 6U) + RotL64(aCross, 23U)) + (RotL64(aCarry, 51U) ^ RotL64(aIngress, 37U));
            aScatter = TwistMix64::DiffuseA(aScatter);
            //
            aOrbiterG = (aWandererA + RotL64(aPrevious, 35U)) + 16265135856982121182U;
            aOrbiterH = ((aWandererE + RotL64(aIngress, 39U)) + RotL64(aCarry, 53U)) + 7967778521818105121U;
            aOrbiterF = (aWandererK + RotL64(aCross, 47U)) + 2436616030051124866U;
            aOrbiterD = (aWandererH + RotL64(aScatter, 57U)) + 10253131839990119883U;
            aOrbiterA = (aWandererB + RotL64(aIngress, 52U)) + 3169108321013652943U;
            aOrbiterE = ((aWandererD + RotL64(aCross, 43U)) + RotL64(aCarry, 37U)) + 12579861590830913409U;
            aOrbiterJ = (((aWandererG + RotL64(aPrevious, 29U)) + RotL64(aCarry, 3U)) + 17787718770529258408U) + aPhaseHOrbiterAssignSaltE[(((31U - aIndex) + 27U)) & S_SALT1];
            aOrbiterC = ((aWandererJ + RotL64(aScatter, 19U)) + 5060601741591219425U) + aPhaseHOrbiterAssignSaltA[(((31U - aIndex) + 25U)) & S_SALT1];
            aOrbiterI = (aWandererC + RotL64(aPrevious, 12U)) + 8763558326209499701U;
            //
            aOrbiterG = (aOrbiterG + aOrbiterH) + 10195181860574704456U;
            aOrbiterF = (aOrbiterF ^ aOrbiterG) ^ 11336491586056125160U;
            aOrbiterF = RotL64((aOrbiterF * 12788478214646527571U), 23U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterA) + 1107097523586849116U) + aPhaseHOrbiterUpdateSaltE[((aIndex + 15U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterD) ^ 8469188489778843232U;
            aOrbiterH = RotL64((aOrbiterH * 7164326593442882599U), 19U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterG) + 1560151177591770290U;
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 17025481276957470248U;
            aOrbiterE = RotL64((aOrbiterE * 17412477974717221205U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 16928482538739323969U;
            aOrbiterA = (aOrbiterA ^ aOrbiterJ) ^ 15107520052029745498U;
            aOrbiterA = RotL64((aOrbiterA * 168182366508272483U), 3U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterD) + 733612944962470772U) + aPhaseHOrbiterUpdateSaltD[(((31U - aIndex) + 26U)) & S_SALT1];
            aOrbiterG = (aOrbiterG ^ aOrbiterC) ^ 13995076003069240038U;
            aOrbiterG = RotL64((aOrbiterG * 4938704677897670281U), 57U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterF) + 10019566274673314837U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterE) ^ 5778351015860850540U;
            aOrbiterJ = RotL64((aOrbiterJ * 10804461093514728327U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterJ) + 12884863659666467818U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 10560990615879759254U;
            aOrbiterD = RotL64((aOrbiterD * 13181108865888519677U), 37U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterE) + 991677799785704325U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterH) ^ 14764101174962392379U) ^ aPhaseHOrbiterUpdateSaltF[(((31U - aIndex) + 29U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 5395935122925143361U), 13U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterI) + 17637865983232683271U) + aPhaseHOrbiterUpdateSaltB[(((31U - aIndex) + 19U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterF) ^ 9716193647811191929U;
            aOrbiterC = RotL64((aOrbiterC * 6707963025966133833U), 53U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterF, 22U);
            aIngress = aIngress + (RotL64(aOrbiterC, 19U) ^ aOrbiterA);
            aIngress = aIngress + (RotL64(aOrbiterI, 39U) ^ aOrbiterJ);
            aIngress = aIngress + (RotL64(aOrbiterG, 57U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterE, 26U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB ^ ((RotL64(aCross, 41U) + aOrbiterF) + RotL64(aOrbiterC, 11U));
            aWandererA = aWandererA + ((RotL64(aIngress, 14U) + RotL64(aOrbiterD, 47U)) + aOrbiterC);
            aWandererK = aWandererK ^ ((RotL64(aScatter, 57U) + aOrbiterE) + RotL64(aOrbiterG, 3U));
            aWandererC = aWandererC + (((RotL64(aPrevious, 19U) + aOrbiterJ) + RotL64(aOrbiterE, 23U)) + aPhaseHWandererUpdateSaltC[((aIndex + 21U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aScatter, 37U) + aOrbiterF) + RotL64(aOrbiterE, 30U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 23U) + RotL64(aOrbiterI, 37U)) + aOrbiterD) + RotL64(aCarry, 39U));
            aWandererE = aWandererE ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterA, 43U)) + aOrbiterC);
            aWandererD = aWandererD + ((((RotL64(aIngress, 53U) + aOrbiterC) + RotL64(aOrbiterG, 57U)) + RotL64(aCarry, 21U)) + aPhaseHWandererUpdateSaltD[((aIndex + 12U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aScatter, 4U) + aOrbiterH) + RotL64(aOrbiterD, 52U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 54U) ^ aWandererJ);
            aCarry = aCarry + (RotL64(aWandererB, 37U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererE, 11U) ^ aWandererC);
            aCarry = aCarry + (RotL64(aWandererD, 23U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererG, 47U);
            aCarry = aCarry + RotL64(aIngress, 51U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        // grow_key_b loop 5
        // ingress from: aWorkLaneB, aOperationLaneD, aInvestLaneH
        // ingress directions: aWorkLaneB forward forced, aOperationLaneD forward forced, aInvestLaneH forward/backward random
        // cross from: aWorkLaneA, aOperationLaneC, aWindLaneC
        // cross directions: aWorkLaneA backward forced, aOperationLaneC backward forced, aWindLaneC backward/forward random
        // write to: aWorkLaneC
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneB[((aIndex + 26850U)) & S_BLOCK1], 35U) ^ RotL64(aOperationLaneD[((aIndex + 22866U)) & S_BLOCK1], 47U));
            aIngress ^= RotL64(aInvestLaneH[((S_BLOCK1 - aIndex + 25660U)) & S_BLOCK1], 14U);
            aIngress = TwistMix64::DiffuseB(aIngress);
            //
            aCross = (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 27287U)) & S_BLOCK1], 11U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 26146U)) & S_BLOCK1], 20U));
            aCross ^= RotL64(aWindLaneC[((S_BLOCK1 - aIndex + 23341U)) & S_BLOCK1], 51U);
            aCross = TwistMix64::DiffuseA(aCross);
            //
            aScatter = (RotL64(aPrevious, 48U) ^ RotL64(aCross, 5U)) + (RotL64(aIngress, 21U) + RotL64(aCarry, 35U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterC = (aWandererC + RotL64(aIngress, 29U)) + 9395694453772431803U;
            aOrbiterE = ((aWandererG + RotL64(aScatter, 42U)) + 8731378013692375215U) + aPhaseHOrbiterAssignSaltB[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterK = ((aWandererI + RotL64(aCross, 47U)) + RotL64(aCarry, 41U)) + 5966054646323140715U;
            aOrbiterB = ((aWandererF + RotL64(aPrevious, 11U)) + 7896521547034414333U) + aPhaseHOrbiterAssignSaltC[(((31U - aIndex) + 11U)) & S_SALT1];
            aOrbiterI = ((aWandererJ + RotL64(aScatter, 19U)) + RotL64(aCarry, 57U)) + 7619228823689632963U;
            aOrbiterA = (aWandererE + RotL64(aCross, 53U)) + 11575113235351186833U;
            aOrbiterD = (aWandererK + RotL64(aIngress, 5U)) + 16887229475815457825U;
            aOrbiterG = (aWandererA + RotL64(aPrevious, 38U)) + 1168901162854925470U;
            aOrbiterF = ((aWandererB + RotL64(aIngress, 57U)) + RotL64(aCarry, 3U)) + 4171448516768183714U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 16427923378303981173U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 13572662622129757676U) ^ aPhaseHOrbiterUpdateSaltF[((aIndex + 6U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 6112900473350466653U), 51U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterC) + 15770841890682963245U) + aPhaseHOrbiterUpdateSaltD[((aIndex + 25U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterB) ^ 2590778533249711419U;
            aOrbiterI = RotL64((aOrbiterI * 11831379924768656001U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 11938749510569738096U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 7680237628249416373U;
            aOrbiterC = RotL64((aOrbiterC * 17656258712470263067U), 23U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterG) + 11101426346303771735U;
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 7919094121026009569U;
            aOrbiterF = RotL64((aOrbiterF * 14505691408106282207U), 41U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 392587549385563492U) + aPhaseHOrbiterUpdateSaltB[((aIndex + 21U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 496898847737668228U;
            aOrbiterB = RotL64((aOrbiterB * 11780642163188119397U), 35U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 9599094742551193342U;
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 14352176217515594100U;
            aOrbiterE = RotL64((aOrbiterE * 4795347640693410923U), 19U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 785487199156196859U;
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 16466474831952131608U;
            aOrbiterG = RotL64((aOrbiterG * 15365890600555590679U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterI) + 15334554831072230919U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterG) ^ 16800517814661312929U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 7U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 12128346378262653073U), 29U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterK) + 15363650013679354363U;
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 13476476660658541961U;
            aOrbiterD = RotL64((aOrbiterD * 17659068169919842417U), 3U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterA, 3U);
            aIngress = aIngress + (RotL64(aOrbiterF, 57U) ^ aOrbiterG);
            aIngress = aIngress + (RotL64(aOrbiterK, 47U) ^ aOrbiterC);
            aIngress = aIngress + (RotL64(aOrbiterE, 60U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterI, 11U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ ((RotL64(aScatter, 29U) + RotL64(aOrbiterE, 43U)) + aOrbiterC);
            aWandererG = aWandererG + ((RotL64(aCross, 39U) + RotL64(aOrbiterD, 19U)) + aOrbiterI);
            aWandererE = aWandererE ^ ((RotL64(aIngress, 23U) + aOrbiterK) + RotL64(aOrbiterG, 60U));
            aWandererK = aWandererK + (((RotL64(aPrevious, 35U) + aOrbiterA) + RotL64(aOrbiterE, 37U)) + aPhaseHWandererUpdateSaltA[((aIndex + 22U)) & S_SALT1]);
            aWandererF = aWandererF ^ ((RotL64(aCross, 6U) + aOrbiterB) + RotL64(aOrbiterC, 3U));
            aWandererC = aWandererC + (((RotL64(aScatter, 19U) + aOrbiterF) + RotL64(aOrbiterK, 11U)) + RotL64(aCarry, 43U));
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 47U) + aOrbiterG) + RotL64(aOrbiterI, 50U)) + aPhaseHWandererUpdateSaltF[((aIndex + 3U)) & S_SALT1]);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 11U) + RotL64(aOrbiterG, 23U)) + aOrbiterA) + RotL64(aCarry, 3U));
            aWandererB = aWandererB ^ ((RotL64(aPrevious, 60U) + RotL64(aOrbiterE, 29U)) + aOrbiterB);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererI, 43U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererE, 3U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererF, 47U));
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererB, 38U));
            aCarry = aCarry + RotL64(aWandererK, 19U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        // grow_key_b loop 6
        // ingress from: aWorkLaneC, aWorkLaneA, aInvestLaneE
        // ingress directions: aWorkLaneC forward forced, aWorkLaneA forward forced, aInvestLaneE forward/backward random
        // cross from: aWorkLaneB, aExpandLaneB, aWindLaneA
        // cross directions: aWorkLaneB backward forced, aExpandLaneB backward forced, aWindLaneA backward/forward random
        // write to: aWorkLaneD
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = (RotL64(aWorkLaneC[((aIndex + 29300U)) & S_BLOCK1], 41U) ^ RotL64(aWorkLaneA[((aIndex + 30378U)) & S_BLOCK1], 11U));
            aIngress ^= RotL64(aInvestLaneE[((aIndex + 29534U)) & S_BLOCK1], 30U);
            aIngress = TwistMix64::DiffuseA(aIngress);
            //
            aCross = (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 29459U)) & S_BLOCK1], 3U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 32020U)) & S_BLOCK1], 47U));
            aCross ^= RotL64(aWindLaneA[((aIndex + 28427U)) & S_BLOCK1], 38U);
            aCross = TwistMix64::DiffuseB(aCross);
            //
            aScatter = (RotL64(aCross, 57U) + RotL64(aPrevious, 11U)) ^ (RotL64(aCarry, 44U) + RotL64(aIngress, 29U));
            aScatter = TwistMix64::DiffuseC(aScatter);
            //
            aOrbiterD = ((aWandererF + RotL64(aIngress, 47U)) + 7913617740036998249U) + aPhaseHOrbiterAssignSaltF[(((31U - aIndex) + 4U)) & S_SALT1];
            aOrbiterF = ((aWandererA + RotL64(aCross, 13U)) + 10223135119276108951U) + aPhaseHOrbiterAssignSaltD[(((31U - aIndex) + 5U)) & S_SALT1];
            aOrbiterJ = (aWandererH + RotL64(aScatter, 38U)) + 17842870763920847032U;
            aOrbiterH = ((aWandererJ + RotL64(aPrevious, 57U)) + RotL64(aCarry, 35U)) + 6061667813173580936U;
            aOrbiterI = (aWandererC + RotL64(aIngress, 3U)) + 11237470056677877926U;
            aOrbiterK = (aWandererG + RotL64(aCross, 19U)) + 14460116650356853044U;
            aOrbiterA = (aWandererK + RotL64(aPrevious, 43U)) + 4569207057909819720U;
            aOrbiterC = ((aWandererI + RotL64(aScatter, 28U)) + RotL64(aCarry, 3U)) + 9578092229036349923U;
            aOrbiterE = ((aWandererD + RotL64(aCross, 53U)) + RotL64(aCarry, 43U)) + 2433089304123587229U;
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 6182889674680051266U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterD) ^ 5016797556017807674U) ^ aPhaseHOrbiterUpdateSaltF[((aIndex + 17U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 10035541221807053653U), 47U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterH) + 15902587773921935545U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterJ) ^ 17632272027645045430U) ^ aPhaseHOrbiterUpdateSaltC[(((31U - aIndex) + 9U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 11045258342713589463U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 16012211729036394040U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 12703054994756970049U) ^ aPhaseHOrbiterUpdateSaltA[((aIndex + 20U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 11375549661644449565U), 35U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterJ) + 2673233665779684895U) + aPhaseHOrbiterUpdateSaltE[(((31U - aIndex) + 13U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 5636609163002990210U;
            aOrbiterC = RotL64((aOrbiterC * 8309860152827763147U), 43U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterC) + 4016024320022125078U;
            aOrbiterK = (aOrbiterK ^ aOrbiterE) ^ 16761853077094208432U;
            aOrbiterK = RotL64((aOrbiterK * 5427344796948679403U), 27U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 4457081242657477885U;
            aOrbiterA = (aOrbiterA ^ aOrbiterK) ^ 9377211675183584663U;
            aOrbiterA = RotL64((aOrbiterA * 11512163375892718357U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 7624277840088275485U;
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 8488175012128496241U;
            aOrbiterD = RotL64((aOrbiterD * 9740892956910142235U), 3U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 12283009803826161638U;
            aOrbiterF = (aOrbiterF ^ aOrbiterI) ^ 7714559011706602326U;
            aOrbiterF = RotL64((aOrbiterF * 15397774628604152513U), 39U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterA) + 16627065453264585720U;
            aOrbiterE = (aOrbiterE ^ aOrbiterH) ^ 15260428433845320674U;
            aOrbiterE = RotL64((aOrbiterE * 12189269925736256773U), 19U);
            //
            aIngress = RotL64(aOrbiterI, 48U) ^ aOrbiterJ;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterK, 5U));
            aIngress = aIngress + (RotL64(aOrbiterC, 53U) ^ aOrbiterE);
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterH, 37U));
            aIngress = aIngress + RotL64(aOrbiterF, 21U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC + ((((RotL64(aIngress, 27U) + RotL64(aOrbiterH, 43U)) + aOrbiterF) + RotL64(aCarry, 27U)) + aPhaseHWandererUpdateSaltE[(((31U - aIndex) + 15U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 54U) + RotL64(aOrbiterC, 39U)) + aOrbiterE);
            aWandererH = aWandererH + (((RotL64(aPrevious, 23U) + aOrbiterC) + RotL64(aOrbiterF, 30U)) + RotL64(aCarry, 53U));
            aWandererD = aWandererD ^ ((RotL64(aCross, 47U) + RotL64(aOrbiterA, 47U)) + aOrbiterE);
            aWandererK = aWandererK + ((RotL64(aPrevious, 11U) + aOrbiterE) + RotL64(aOrbiterK, 35U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 3U) + RotL64(aOrbiterK, 13U)) + aOrbiterI);
            aWandererG = aWandererG + ((RotL64(aIngress, 36U) + RotL64(aOrbiterJ, 3U)) + aOrbiterC);
            aWandererF = aWandererF ^ ((RotL64(aScatter, 19U) + RotL64(aOrbiterD, 53U)) + aOrbiterC);
            aWandererJ = aWandererJ + (((RotL64(aCross, 41U) + RotL64(aOrbiterD, 18U)) + aOrbiterA) + aPhaseHWandererUpdateSaltB[((aIndex + 28U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererG, 3U));
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererJ, 27U));
            aCarry = aCarry + (RotL64(aWandererK, 13U) ^ aWandererH);
            aCarry = aCarry + (RotL64(aWandererD, 47U) ^ aWandererF);
            aCarry = aCarry + RotL64(aWandererI, 19U);
            aCarry = aCarry + RotL64(aIngress, 60U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    // GROW_B grow_key_b (end)
    // GKeyFoldB grow_key_b_fold (start)
    static_assert((S_BLOCK / W_KEY) == 16, "GKeyFoldB expects 16 key-row chunks.");
    TwistShiftBox::ShiftKeyBoxB(pWorkSpace);
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 2, 0, 1, 0 with offsets 3237U, 1860U, 4897U, 7284U
        // byte shifts: 16U, 8U, 24U, 0U; diffuse: DiffuseB
        // write to: aMergeLaneA [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3237U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1860U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4897U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7284U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 3, 3, 0, 2 with offsets 7639U, 7911U, 2336U, 1962U
        // byte shifts: 24U, 16U, 0U, 8U; diffuse: DiffuseA
        // write to: aMergeLaneB [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7639U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7911U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2336U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1962U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 0, 1, 3, 1 with offsets 5473U, 3708U, 2934U, 259U
        // byte shifts: 24U, 8U, 16U, 0U; diffuse: DiffuseC
        // write to: aMergeLaneC [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5473U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3708U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2934U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 259U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD source quarters 1, 2, 2, 3 with offsets 1893U, 4906U, 908U, 4229U
        // byte shifts: 0U, 16U, 8U, 24U; diffuse: DiffuseA
        // write to: aMergeLaneD [0..<S_QUARTER]
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1893U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4906U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 908U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4229U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aMergeLaneA, aMergeLaneB, aMergeLaneC, aMergeLaneD [0..<S_QUARTER]
        // offsets: 2873U, 3698U, 6040U, 5393U
        // byte shifts: 8U, 0U, 16U, 24U; diffuse: DiffuseC
        // write to: aScrapLaneA [0..<S_QUARTER]
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2873U) & S_QUARTER1;
            const std::size_t aFoldIndexB = (aIndex + 3698U) & S_QUARTER1;
            const std::size_t aFoldIndexC = (aIndex + 6040U) & S_QUARTER1;
            const std::size_t aFoldIndexD = (aIndex + 5393U) & S_QUARTER1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA fragment 1 with offsets 1098U, 1055U, 301U, 413U
        // byte shifts: 24U, 0U, 8U, 16U; diffuse: DiffuseC
        // write to: aScrapLaneB fragment 1
        const std::size_t aReadBase = 1U * W_KEY;
        const std::size_t aWriteBase = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1098U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 1055U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 301U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 413U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA fragment 3 with offsets 1154U, 347U, 145U, 1934U
        // byte shifts: 0U, 8U, 16U, 24U; diffuse: DiffuseA
        // write to: aScrapLaneB fragment 0
        const std::size_t aReadBase = 3U * W_KEY;
        const std::size_t aWriteBase = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1154U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 347U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 145U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 1934U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA fragment 0 with offsets 1588U, 947U, 152U, 889U
        // byte shifts: 24U, 16U, 8U, 0U; diffuse: DiffuseC
        // write to: aScrapLaneB fragment 3
        const std::size_t aReadBase = 0U * W_KEY;
        const std::size_t aWriteBase = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 1588U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 947U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 152U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 889U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneA fragment 2 with offsets 840U, 1965U, 1103U, 225U
        // byte shifts: 8U, 0U, 24U, 16U; diffuse: DiffuseA
        // write to: aScrapLaneB fragment 2
        const std::size_t aReadBase = 2U * W_KEY;
        const std::size_t aWriteBase = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aReadBase + ((aIndex + 840U) & W_KEY1);
            const std::size_t aFoldIndexB = aReadBase + ((aIndex + 1965U) & W_KEY1);
            const std::size_t aFoldIndexC = aReadBase + ((aIndex + 1103U) & W_KEY1);
            const std::size_t aFoldIndexD = aReadBase + ((aIndex + 225U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aWriteBase + aIndex] = aFoldWord;
        }
    }
    {
        // read from: aScrapLaneB fragments 2, 0, 1, 3 [0..<W_KEY]
        // offsets: 933U, 836U, 1531U, 648U
        // byte shifts: 8U, 24U, 0U, 16U; diffuse: DiffuseC
        // write to: aKeyRowWriteB
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 933U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 836U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1531U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 648U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
    // GKeyFoldB grow_key_b_fold (end)
}

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseASalts = {
    {
        {
            0x22908DEA1339858AULL, 0x20983E5930BAAE06ULL, 0xEB4B3C4CB7569706ULL, 0xE124C920D92CF75FULL, 
            0x83BC67A15A450AE4ULL, 0xAC79867E144086A9ULL, 0xC33B39B8081875C1ULL, 0xD5E472DE52B40C27ULL, 
            0x4DE1DA592C565763ULL, 0x5113CA3759296F37ULL, 0x9C211A3964EBEF96ULL, 0x24E1569A2CAB2992ULL, 
            0x6CCA5BD75E3E856DULL, 0x43798D8F04320F46ULL, 0x6A20F1CEDAA70B7AULL, 0x06B53C34BE018115ULL, 
            0x8A840C5A18D56752ULL, 0xD42A32115DA4037AULL, 0xBA7569E4D23BF226ULL, 0x661F967875B1C0D3ULL, 
            0xC728E7FF532DB997ULL, 0xEDF266FA4ACD9914ULL, 0x5514687BABAA8009ULL, 0x352BC5DF4F72FD99ULL, 
            0x913604614DD439B4ULL, 0x8FFE4AA74E5BAA6AULL, 0x1CBCC7396C45490DULL, 0xA5FEDF7A7906A862ULL, 
            0xB0E2E4489EA14985ULL, 0xA729E4EA1DF9F136ULL, 0x6F90530ED7A0BA2FULL, 0x5BCE80B196B95AA0ULL
        },
        {
            0x8D5B2C420E60FD1BULL, 0xFCA2FBBC35C9D65FULL, 0xE5090F571B83F01AULL, 0x3C026822577BF912ULL, 
            0xAE6FCDBD372F75BBULL, 0xD2ED1ECF8B2BBE7EULL, 0x479B0FE1EA6EFBB5ULL, 0xD7376AD78BADD4BBULL, 
            0xC0370538E1DA4EF5ULL, 0x15B6653A22D49221ULL, 0xEB4511478F3C7BA0ULL, 0x2E0A03899251936EULL, 
            0xCF5924301FD64736ULL, 0x7A3F9FC1254EEFEDULL, 0x06B9F2A51116B936ULL, 0xF0A154304DB22644ULL, 
            0xBB5746EEEF5332A1ULL, 0x7BEA9AB8BD990456ULL, 0xB8F903695A5040EDULL, 0x26E0A275A8D54B69ULL, 
            0x0E6AC44E424AC652ULL, 0x42E8A3BDD4FFD0A8ULL, 0xDE8159770DA43196ULL, 0x815018F6F74F3F55ULL, 
            0xE83112611D34F3FBULL, 0x6E5A6B2E3E2403E5ULL, 0x6B8DCF6403B562A9ULL, 0x148800D8BFBC166AULL, 
            0xCCD2D243B21FA9A2ULL, 0x093AECCF99C8176FULL, 0xCFB5F44D1130DA3DULL, 0x4B6AB13AB6C92426ULL
        },
        {
            0x73D5C86FE4A2965EULL, 0xC0486DBE20329B50ULL, 0x583940AA91F9B6F2ULL, 0x2884ADEC8385C3A3ULL, 
            0x5C791EC31B4240BFULL, 0xA17052F9AC10F92AULL, 0x38A997A716A69AF5ULL, 0xD560BC650477E95BULL, 
            0xC79A3E96D59A55F1ULL, 0x22E6DEA707021350ULL, 0x50AFBBED2967C348ULL, 0x2D666C3578169172ULL, 
            0x274BD285916DFEDDULL, 0x6B9C7ADFE82D5518ULL, 0xD5E93EFD206F64A6ULL, 0x1F343EE96C33F104ULL, 
            0xB36B8DFEECB8410CULL, 0x6D5742A27FBF72BCULL, 0xBCC3ABD7E219866CULL, 0x57B824DADD1BA193ULL, 
            0xEA536D49A6C367F3ULL, 0x04FE748C80724553ULL, 0x0FF83BE5047AD5D2ULL, 0xF15203C021D0859BULL, 
            0x9FA5107A76B8FD6AULL, 0x78C17B57A97B1E25ULL, 0xB1958A8DAE0C2CF2ULL, 0x41378D5D4886D13DULL, 
            0x34AD4407989D5EB6ULL, 0xB1643EBD61250337ULL, 0xDD0E15A1CAF72145ULL, 0xEBA1373879F09526ULL
        },
        {
            0x27988C32B3A7B87EULL, 0xFB4A5F9275187E12ULL, 0xF579177D9EC24DCDULL, 0x243F3C8B15D88DAFULL, 
            0xD48134C47AD26FD5ULL, 0xE8FA69513B8E1373ULL, 0x70BFE7536B11171CULL, 0x03EF02C71BCAB57DULL, 
            0xAEF2443F69D9602FULL, 0xD58C0983CD4942BCULL, 0xF9A8A906ED0152B7ULL, 0x4B180E07D3126420ULL, 
            0xEC47361BFE533F14ULL, 0x8A8DBEC5954EBFCDULL, 0x0D9AB022396E3BEDULL, 0xF868FC9B6FB82D11ULL, 
            0x2BF695BCFED22D14ULL, 0x290BEA8626111E6BULL, 0x63DE88C17E43F5AEULL, 0xE158065295C8332DULL, 
            0xCAA1D4F0324270A6ULL, 0xE3313F280F0C107FULL, 0xD592D14552674B63ULL, 0xA17E1256BFE8AA7CULL, 
            0xB7D1308C265F45A5ULL, 0x31DC4E0891BBD0B3ULL, 0x8E2E454E42CD98ABULL, 0xAB2F8F46501A827AULL, 
            0x38939060E38FB7D5ULL, 0x8CEE91F574A2EF25ULL, 0xCCF07089C5D79629ULL, 0x3DF342D92074E3E8ULL
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
            0x14CE09BF63CAF7C1ULL, 0xD095E1678D639E88ULL, 0xCE9758FEA258A797ULL, 0x0694C3FC228E3128ULL, 
            0x083865A790B8F701ULL, 0x97EB936A3C99EE8DULL, 0x9564FCF9374E51ECULL, 0xD53D0291B860A81FULL, 
            0x70A8F4BA06BEB793ULL, 0x2077C7581BE50B48ULL, 0x0F2589A8EF2AD05BULL, 0x304E5C85F9BC3AA8ULL, 
            0xF9186A2B50B806A9ULL, 0xA96039A13ECA1081ULL, 0xC6360B2B7A6ACF2AULL, 0xDB0CED5627FE56F6ULL, 
            0x0080A82B5A636631ULL, 0xD986C0235E93046CULL, 0xDFFE5F9FFE0E4FE0ULL, 0x5BE0C70EDD278BC9ULL, 
            0x1524B0212DB2E350ULL, 0xD392CEF7E3497817ULL, 0x2FF204BA4EF1F23FULL, 0xC62ADA34A8AC602FULL, 
            0xEBE7E36EF60974CDULL, 0xF12924A50C3C9289ULL, 0x218FC4B9D3FD59E2ULL, 0x774FDF1FA806FDE1ULL, 
            0x6B19F9AF3F0489D5ULL, 0xD246A47BCD6EF2E3ULL, 0x5106D268BF5FC800ULL, 0xA4C5A981E5E1FF4BULL
        }
    },
    {
        {
            0xF4C6A792044D1D0AULL, 0xDE29DE1C210F15B5ULL, 0x1763CE83678A3770ULL, 0x11946841B5E91712ULL, 
            0x13736F9D4C122FD2ULL, 0x2456FF98193CC7BFULL, 0x6091C4373C8D5286ULL, 0x5592A4073A34CFF3ULL, 
            0x08B5D6AD74B028E7ULL, 0x5F73A436F535D45FULL, 0xEE5694581D35A8E6ULL, 0x934670E0E31809DAULL, 
            0x2849BDDF216A02B6ULL, 0x64BEB7927AF4DC25ULL, 0x6F403FA52696EE22ULL, 0x7AFC97E9F606A39BULL, 
            0x50C1213F45A721E5ULL, 0xEEF2D49529D6000CULL, 0xA0C09E6800C52FA2ULL, 0xFF66BDAFC41B9BDBULL, 
            0xB42A9623BB5DEB46ULL, 0xD928F769055A123AULL, 0xFF896BB9D2A01B83ULL, 0x97F33B08692F1432ULL, 
            0x52563A06DA27B8A2ULL, 0x9FB4EEF9D75B3801ULL, 0x26A17B2CC2C022B7ULL, 0x469384763F391DD6ULL, 
            0xCCEF54BCB455178CULL, 0x3642EFA32FC45731ULL, 0x9D191EE8C64AFD16ULL, 0x35EDC41B5C1706FFULL
        },
        {
            0xB6AC445CF9E87665ULL, 0x7F13A2EA1D7F1469ULL, 0xDBBC05F2DF42D2C2ULL, 0xF1D89F5D4F71D055ULL, 
            0x9C965BEF02B24DF8ULL, 0x4EC39F076F8A345EULL, 0xAB089894ECF2371CULL, 0xFED6E8CA00E057F0ULL, 
            0xB23A20E7B93BD42DULL, 0x948A57D64D4A177EULL, 0x63DA1AAA2C9863E9ULL, 0x0AFD1F5C14FE9F68ULL, 
            0x17A44AD97730BF87ULL, 0x95CEB858E87EA620ULL, 0x89D77F60395EEC83ULL, 0x59A729D092264661ULL, 
            0xB73FB770129EEADDULL, 0x8F3FE0694B628BBDULL, 0x93BBC92F6102587BULL, 0x82E1185085175FD8ULL, 
            0x70FC40446B9B7096ULL, 0xBCA57373E065905EULL, 0xCAE3579BAC2B5AA9ULL, 0x10EBBD292528D665ULL, 
            0xEB11CF2E075953F3ULL, 0x450A1585EA0DA9E8ULL, 0xBFA7202A588C4884ULL, 0x06B6EE8FD37F805DULL, 
            0xBF52E8F8580B82A2ULL, 0x9593CF104688DAA1ULL, 0x989834E7D953777BULL, 0x98D7FDF480570D64ULL
        },
        {
            0x44799ED62FEED58EULL, 0x74CB171E4E8129FEULL, 0xB9E17AA36738C869ULL, 0xDA658805636D0992ULL, 
            0xD07FBD0C701919CCULL, 0x9185AC9D723F8EA9ULL, 0x5DBAE040622FCAFEULL, 0x4D62247CFC89F831ULL, 
            0x2BF8D426477FD2F6ULL, 0xE739E6F52E7886F3ULL, 0xE435E8A042C6A21CULL, 0x6F6F8337E1B34757ULL, 
            0x7FB1C06EB675E6A5ULL, 0x8F63B3AB6FB4A17DULL, 0x54488479298A0CAFULL, 0x441BE64AEC07AE99ULL, 
            0xD32B9C5479342231ULL, 0xD0DFD396572AF378ULL, 0xD7F9B1981CB67445ULL, 0xF7BFB390937CC5D5ULL, 
            0x82029B8F47D0BDD0ULL, 0x9B2C833BFBA1AFF9ULL, 0x475B6FCC0C48DB30ULL, 0x0F68E2061172DE46ULL, 
            0x4C671A58D456BBF9ULL, 0x07EDDD041C6DEBCAULL, 0x8E47F2FE75117131ULL, 0xBCBFC7E0F3387739ULL, 
            0x72569B4877046C01ULL, 0x7C87E358FA8A91BEULL, 0xD8964A3FB9D02E30ULL, 0x87D0ABE998060692ULL
        },
        {
            0x15ED78C89942E519ULL, 0x6B9A9F380787F33DULL, 0x7FFE1B0DDFB27167ULL, 0xE3AB84707C514CE2ULL, 
            0xF846CA30EFA08B45ULL, 0xECF015CD69D0803FULL, 0x1FE556DAC510317BULL, 0x68C09D5243E2349AULL, 
            0xE3D118E1F29AB8B5ULL, 0xAC81180AE83A25C7ULL, 0x0130E20EF1ABFBB8ULL, 0xD24DA629762C3EF8ULL, 
            0xA94951F2605D8F3FULL, 0xDD84E33915CF6DB2ULL, 0x2FF1F57EB417DAFEULL, 0x72D09CEA8447B65AULL, 
            0xE267908FD2C3ACE4ULL, 0xCC8255469BFBA781ULL, 0xD6249C13A23EA69DULL, 0x1CE561199C532569ULL, 
            0x8E2F9D6D098FA350ULL, 0xB9BC4203321ED4CAULL, 0x86388A8E958344CDULL, 0x505CE5F66AF66A04ULL, 
            0xC327AB6A9972E0E7ULL, 0xB1F2A2D64E985F62ULL, 0xEE960E52C9139282ULL, 0xA7689794BBD776DFULL, 
            0xDB2D3282315942CDULL, 0xA6DB1E3B1A355F5AULL, 0x3C5D52482E554A2FULL, 0x8C3D022AB41A6802ULL
        },
        {
            0xAFD37EC60D3F720BULL, 0xD4CA7429E82812BBULL, 0x6A6F6979BA275AE7ULL, 0xEB0E924B31A9BF56ULL, 
            0xFFC9E1AB03FB8066ULL, 0x0B829A6F34438450ULL, 0x247E9948C17E7A73ULL, 0xD109AF5D9E79B30BULL, 
            0x46C3F0E0F0B7679FULL, 0x7036FC2ED5CFD1D4ULL, 0x63E86CE634A69D31ULL, 0xCAE44F02DA51CF07ULL, 
            0xF8008AADD5C832ACULL, 0x9E364980398F1B7DULL, 0x1BC71EC38DD81859ULL, 0xB5C94E8F9925AB26ULL, 
            0x61550C5B946EB237ULL, 0x01EB91DC4BACA1DEULL, 0xF44964D5E2779E36ULL, 0x6D7A8B94C316D217ULL, 
            0xA283D1C3B4779862ULL, 0x6F4BF2C19096A234ULL, 0x7996A4515E8A1E7EULL, 0x9ABE30C9FC905104ULL, 
            0x109AECC50773543CULL, 0x2800BFB8C33F1777ULL, 0x1079C6840B6D52C3ULL, 0x410C1918119914E6ULL, 
            0x740AABC7A536F007ULL, 0x576FEAE944C03C55ULL, 0x99AC880FE944F853ULL, 0xD181F249667C5CC3ULL
        },
        {
            0x15E74DC6E697C021ULL, 0x0C229B702D4F26F5ULL, 0xA49337761714D266ULL, 0x0E6B6BA6B7AAAA59ULL, 
            0xE11F700517A7AF4DULL, 0x787F4309F26AED3AULL, 0xA09F94611971701BULL, 0x4C377A3F3E97F167ULL, 
            0xBCCA2130E18938CBULL, 0xBDBC00AB5E4F17CBULL, 0xF83C64AB0C16ECABULL, 0xD8BD4B3F6B0C30A5ULL, 
            0xEAC613FFACD04740ULL, 0xC5576765BFD512B2ULL, 0x8A2D9FDFF8D6D4E0ULL, 0x8D5472C72C61BE26ULL, 
            0x78A86536416D1E06ULL, 0xB145D3E73E887CF5ULL, 0xB5C469F97782C75CULL, 0x42463AD38FE5776EULL, 
            0xFAA3DF1D2259D989ULL, 0x1131D65CF49551D8ULL, 0x76A97342563E695FULL, 0xE3B0D115AB01414FULL, 
            0xFFBEA1AE322497E5ULL, 0xBA7017E6AFF76237ULL, 0x372D90FC4F0125ADULL, 0x3DE836F228AB2C23ULL, 
            0x0BFB8860AD1BB62EULL, 0xD8B29E58FCC9AAD5ULL, 0x50514F5DB44634E5ULL, 0x6732D0D3B61F1D6BULL
        }
    },
    {
        {
            0x0ACDD3CF25BDE2B5ULL, 0x308C56A7227A62E8ULL, 0xF1A41FBADC9F22D5ULL, 0x95FE16E20D32DA0DULL, 
            0x97D2F6AAF788ECBAULL, 0x4CA1C3BEE29C6071ULL, 0xE030A6633C94D95AULL, 0x989FB669087324E5ULL, 
            0x1A94F88C4DAE05CBULL, 0xEF92ECE1983184B2ULL, 0x3FCA49CD03A39577ULL, 0x831EB7C8EA684714ULL, 
            0x44A4B111B7BA8E9BULL, 0x9AE52BEEB5578A15ULL, 0x41633BAB6883D32CULL, 0x206A19D4D3E3F866ULL, 
            0x292376CB469925B6ULL, 0x89C9770205739DCCULL, 0x38A21FE770306076ULL, 0x7E02B67061C1A17AULL, 
            0x9726054CBDF6294DULL, 0x45F010403E05862EULL, 0x3120E656C25FCE73ULL, 0xB13FE1F2D3606A72ULL, 
            0x6A0BD613CF3A31E0ULL, 0x2A13FD9C0F89221CULL, 0x5E2BD27EE50BF203ULL, 0x63E8379536D307EEULL, 
            0x4F13AE7696B37E30ULL, 0xB62614A1C9CF4D8DULL, 0x76C097C030182D21ULL, 0x90A395717C1D796DULL
        },
        {
            0xB94E4C163E1FA89BULL, 0x2E5645511575FE0EULL, 0xD43E3329CBF25613ULL, 0xFF9FBAA7857EB74EULL, 
            0x296DF2FFFCBF68BAULL, 0xEC97E85FEEBCC189ULL, 0xDB38D77A921785B4ULL, 0x00C1DE752E94473EULL, 
            0x18FB990C1E400644ULL, 0xE621B235170C176EULL, 0xA69C71BF6C7DBBDFULL, 0xB15A7AF82BA5BD5DULL, 
            0x67338E1A7EF850B2ULL, 0x58F034666111867DULL, 0x8D10755C58E2F260ULL, 0x0C5772FF52DD00DFULL, 
            0x814B4F559F39F8F2ULL, 0x464F01FB0D9539ECULL, 0x5FB93AD81B770D10ULL, 0xFEFBAF6C2AC125F4ULL, 
            0xD00C05571DD6C20BULL, 0xDA2DE19160E52CD8ULL, 0x2EC09858AC2F0435ULL, 0x3EDD2CC5FC0F3653ULL, 
            0x006D8CA0143D809CULL, 0x9796C3E0C4D8F57DULL, 0xB26C93094ED9FC1CULL, 0xA0CA1D7719A25A34ULL, 
            0xFD66DAFD33DB0723ULL, 0x3E66AE00E631378FULL, 0x390F962BAA8EAD9FULL, 0x116712CDCAC9660BULL
        },
        {
            0xB1E4F2CD698ADF58ULL, 0xA0A5DC98F2185703ULL, 0x3E3CCB9023CE1E63ULL, 0x4AB831F7372972C4ULL, 
            0x465BF491D3E79E14ULL, 0x1D17B6580EF399F0ULL, 0x4F35964079E37242ULL, 0x62FA6628AE9CB610ULL, 
            0x66FE91E759DFDABFULL, 0x680668C49B2382BFULL, 0x18C9453DC669D30CULL, 0x9E546CA36CEF95DEULL, 
            0x38D5F338DF8C2A62ULL, 0xE6DB40CF0A7EFC23ULL, 0xCDD0A49FC68B2A24ULL, 0xE8714168C03E64C9ULL, 
            0x20FCD1069B112E7BULL, 0x4A138DED58994422ULL, 0x9138FCD2D357F919ULL, 0x5FF9C87989AA0DDDULL, 
            0x269870D07A74F9B1ULL, 0x9E01A3E716F3FA6EULL, 0x83C7BC70AD7F43B6ULL, 0x88A3456B8A49EFE6ULL, 
            0x0512B9508A1DC146ULL, 0x3DDB9D7C5094BA3BULL, 0x633873DAAEA877BFULL, 0x8DEC101F8EC3123DULL, 
            0x6153A84837EADAA5ULL, 0xF4B22FEEF1544489ULL, 0x1E1F40E2C126FFB3ULL, 0x15ECA391B78C7388ULL
        },
        {
            0xC6599F0571FC2B3AULL, 0x7F3B77E63BBE5996ULL, 0x24CA91D6D161096DULL, 0xD86AC047B7124C80ULL, 
            0x31B08E5BE6B92ACAULL, 0x988EF33C45C971A6ULL, 0xD1EF7FDF9F11C3A0ULL, 0x73500F92436A6285ULL, 
            0x2CCDBE24F48A5594ULL, 0x5A06A58F50D070FDULL, 0x3653D43B4899C2ECULL, 0x511E365EAC230AA4ULL, 
            0x3E3E67CEA198E0C5ULL, 0xA0D3B569B5F551E6ULL, 0x3018937049C15AA4ULL, 0x86BEBD827677A4BCULL, 
            0x2BEAA1640F4FE765ULL, 0xD858639569FFE8B8ULL, 0x88E7E322A6545141ULL, 0x2223D7C25F1BC2C8ULL, 
            0x78552779AC541966ULL, 0x8021884EFD961CC5ULL, 0x54CD9B57C7C25BEEULL, 0xB1B544F0E1A854FFULL, 
            0xAB4EC005BC765302ULL, 0xA8EF3C1D571ECC85ULL, 0x8B36DAB137230104ULL, 0x7D2AC45445B4F388ULL, 
            0xCE92D0651D0641C6ULL, 0xBC5DABA2BA2E3FCFULL, 0xB9C3356CF6C09B8EULL, 0x0774B6E5786060ECULL
        },
        {
            0x6DFC4E0BE587FD04ULL, 0x92462E7009EFD910ULL, 0xC60497050CEF12A5ULL, 0x5A7743DD3AA0B22AULL, 
            0x929F579F5F068326ULL, 0xC457A3D2885E1FADULL, 0x9B3E89322936196FULL, 0x4C726FCCA4FC5B75ULL, 
            0x6245BAF45CCA8627ULL, 0x3CEBD2D54AF467B8ULL, 0x43C9F37147DF8FAAULL, 0xF2CB4238F4128121ULL, 
            0xBA7BA53A75AE955FULL, 0xF2A896AD2F101F9FULL, 0xE52E742F428DE289ULL, 0xE6C4268A5127B049ULL, 
            0x47A1407CA4889F65ULL, 0x296CC3D2D0A0554BULL, 0x18E37F86B8755D19ULL, 0x91DF5F30BF232A17ULL, 
            0x4B31BBB87BBD39C2ULL, 0x8528CF31B384074DULL, 0xB348B1B7D28BCBC8ULL, 0xDCC6A4FE0A987AE5ULL, 
            0x29042C3B4CA55992ULL, 0x82BA9EF0595D9277ULL, 0x12BA03ABDE31D58FULL, 0x4207A00C85D907BFULL, 
            0xEE26CFBF2E951BDBULL, 0x768697673A46DC54ULL, 0x6574BFE7B132A1A0ULL, 0xA4E20FFF9E61A83EULL
        },
        {
            0x255B567AF5A9B446ULL, 0x2EF34E5C24331EFFULL, 0x2C47D8BADEA7E59FULL, 0x16DC2CB23B598F18ULL, 
            0x0C970DDD89751237ULL, 0x98A3FB86DFD437A1ULL, 0xD758A488918C1165ULL, 0x49B2B01CB968133BULL, 
            0x6F032757584208DDULL, 0xE45D9B65F483038CULL, 0x600FCFC763A7EED3ULL, 0xD4D7F4973832C50DULL, 
            0x5E17BA41E32409C7ULL, 0x945C9FBB22AE9299ULL, 0xC2935414F51ECBFFULL, 0xA17563569C2D5AD0ULL, 
            0x3D82FA84E2FF20FFULL, 0x0F4D277EF7DE06FFULL, 0x32F63256BA936272ULL, 0x375C2DDA9C86310BULL, 
            0x8F9417D537F34881ULL, 0xD26EA888841F9C2DULL, 0x95382285D0791C14ULL, 0x7414407ABAD64680ULL, 
            0x35CEF64EFC3D585AULL, 0x9B367A937EF13535ULL, 0xD8AF42CD5C7A723AULL, 0x67C5DF4414867BA1ULL, 
            0xCE120BAE4A78BC14ULL, 0x1FEC609B36A959DAULL, 0xFC0E0CDF17B78D97ULL, 0x563D47460D4A0E6AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseAConstants = {
    0xB2AB7E3F4ECD8CC0ULL,
    0xE16523BE14F7C25CULL,
    0x18528FD8014D0F5AULL,
    0xB2AB7E3F4ECD8CC0ULL,
    0xE16523BE14F7C25CULL,
    0x18528FD8014D0F5AULL,
    0x2EBA47DBC123247CULL,
    0xE3CE2DE63B37059DULL,
    0x8F,
    0x1F,
    0x89,
    0x2B,
    0x30,
    0x66,
    0xCD,
    0x50
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseBSalts = {
    {
        {
            0xC31FFA7100E4047DULL, 0x63B40739C8148E12ULL, 0x6DA9D065636E8EEDULL, 0x9E864964758A7519ULL, 
            0xCDDF396EA80623A5ULL, 0x498971C84700AABAULL, 0x02C1C0D1C38EC507ULL, 0xE6D8E403B0809DB8ULL, 
            0xA14FE15D717F7315ULL, 0x9095A7F5308B7C22ULL, 0x66077EE590E23831ULL, 0x125FB73BCDCDF3C7ULL, 
            0x144D7C5E28CFC138ULL, 0xDA2FAD4117186B77ULL, 0xE277FEBCBCDD5C78ULL, 0xBB4B6CD7727AE422ULL, 
            0xE0890CD2380D2C15ULL, 0x0A7D104BD2F55BF1ULL, 0xACE87BADC36732CCULL, 0x3D0D1A0B5807D1A2ULL, 
            0xD34ECD6F402F8109ULL, 0x73654540CC9844B5ULL, 0x3BE9728FC455D493ULL, 0x8C0B23344E3189C6ULL, 
            0xC1B773D0046B3466ULL, 0xF91FA9C9365F3102ULL, 0x8482ED8DD1D44320ULL, 0x2FD6D6C5023E6A50ULL, 
            0xE8799A7E91DAE02AULL, 0x68976C42C1DB37D1ULL, 0xFF25618E227FD782ULL, 0x0CE97A57FAE8EC5BULL
        },
        {
            0xF6CA53421B9B582CULL, 0xBDDD4B9CC6C4393EULL, 0xB0ED307673FF28D6ULL, 0x4BC6A3055207EEF1ULL, 
            0xA78A9EDC61E2ACAFULL, 0x582CE4435C32C979ULL, 0xC923F239C2B209AAULL, 0x735B1E6BFC21B717ULL, 
            0xDC865E83D138ADF5ULL, 0x5D6824A7D733061EULL, 0x023A677C8132150CULL, 0x3939C54DC15EA690ULL, 
            0x0316066F85C1F236ULL, 0x23EE72FC490E458EULL, 0x9807FCA776AEBD63ULL, 0x8FE8F779FAE9E8BBULL, 
            0xFBBAC991D61D0677ULL, 0x1913757B31E24BF6ULL, 0x7D82EFB212D58B3EULL, 0xCB4008195A0E2D38ULL, 
            0xFE02F63F0AD1479AULL, 0xA836207A5DD67F73ULL, 0x0A79437A66C20C28ULL, 0x7774B18D24513C7CULL, 
            0x334CBC39416F88CDULL, 0xB95D19EA67334258ULL, 0x1D15428F7FC3F6EBULL, 0xE7470369BA4486ECULL, 
            0x7B8BECBB714D8B2FULL, 0x43C96B289C38AD3BULL, 0x06DA5FE5AE1B0DB7ULL, 0xAAA242FA50EF498FULL
        },
        {
            0x8DCE0138BE75DBF2ULL, 0x28041981F2876BCAULL, 0x2BA997EAF9B92DDFULL, 0xB686044A240AD2D2ULL, 
            0xB3B33E6097260216ULL, 0x283A772A79AC6920ULL, 0x53EAD8CAE5958A9FULL, 0x19FF339B5DEC705CULL, 
            0xA288EE0D586A4A8CULL, 0x54389368A19C534AULL, 0x82B458DBDA1EA230ULL, 0x110DA5FE6DCB7690ULL, 
            0x11BFDE3FE08475BFULL, 0x2F2EFAF3313E0F6CULL, 0xCFAC6DFA67BAB299ULL, 0xE7B38F2C5B4875C5ULL, 
            0x2BEAC2DD09B27A64ULL, 0x127DCC7865D0E315ULL, 0x7C62105E9CE114E4ULL, 0xEAA6273AA8CF7822ULL, 
            0xCA075D541CD4110BULL, 0x1301EC5C11D3C7C2ULL, 0xA6E4E7C58687CD72ULL, 0xC6EDEA3751AF2B28ULL, 
            0x45329E95040214B3ULL, 0x70951EFF171F1AFFULL, 0x8524373428561FF5ULL, 0x70D6F00FD992F13EULL, 
            0x4312663EC0E538C3ULL, 0x62B8B78060F984ECULL, 0x54228191D7A983B2ULL, 0xD19082546164240AULL
        },
        {
            0xC7A56564547510A8ULL, 0x209A683071A868F0ULL, 0x88AC029BB54BD236ULL, 0xAE0A01EBC9418869ULL, 
            0xFA373436CA29CF4CULL, 0x9ED1E0F7AE48C4CEULL, 0x9C49A096711EF07EULL, 0x720C874021EA424EULL, 
            0xFCA18DBD890EC37EULL, 0x0EC3C2976FDA231AULL, 0xD79414542C639E59ULL, 0x00AE3061AC1F412AULL, 
            0xA1E7C55E5A4AF0E7ULL, 0x0B2F2E4134DC61EAULL, 0xE489C0AA72A43EA2ULL, 0x6F6F6D70B594DB69ULL, 
            0xE85B36CF54E7F019ULL, 0xEB0CE553E8B1D319ULL, 0x3ADAC4738664C29FULL, 0x29F2C73C7C5F03D2ULL, 
            0x8D473DE699A30082ULL, 0x5C703F03C4098523ULL, 0xE33B47E879B2ECACULL, 0x100DCDAE345B42D3ULL, 
            0x0AC06FE3A906E290ULL, 0x5415CCB733C392F9ULL, 0x62348401E5CD565CULL, 0xE8569F264DBE4DD9ULL, 
            0x027F1E4E9CC1E880ULL, 0x99403044F6B05ADAULL, 0x3B56A70387FB6708ULL, 0x3577321F757CCD7EULL
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
            0x7A00443A0D4CC058ULL, 0x8E64FB5A1DE0EC19ULL, 0xCFFD29DE4B8F26C3ULL, 0x928918D9D0351769ULL, 
            0x9A3C13A742C47E02ULL, 0x1C90C7EC08AD9C6FULL, 0x6E9B7F0D296222B4ULL, 0x0C9F612D33CF6BB9ULL, 
            0xA4F43C3625498F7DULL, 0x46CDE805AC058FE7ULL, 0x4C94BDF69A49F84AULL, 0x7A330B83F9AF2454ULL, 
            0x44656A34EF50A9AEULL, 0xBFDACB2FF071EF9FULL, 0xF9B04DDB5D14A2EEULL, 0x47820DF306C46513ULL, 
            0xDD6574C84F95823BULL, 0x1ADCD8C81D752BB6ULL, 0x4BF62FE7F9AB7A55ULL, 0x5CEE526990015A82ULL, 
            0xE8F732C837F3431FULL, 0xB033DE9BF9C8E0E0ULL, 0x8D4D1B5556D83FF7ULL, 0x68B7D5C07DDCCF90ULL, 
            0xAAE4CDB7F0139FF6ULL, 0x305F4C9AE1368715ULL, 0x86D9515D201E963CULL, 0xE4BB8C0F3C391969ULL, 
            0x522E8F9C30DCDAD3ULL, 0xBF61A584A6BD7873ULL, 0x9128EA8095737397ULL, 0x91F329A0B7531342ULL
        }
    },
    {
        {
            0x9CC8AA565DD82023ULL, 0x108D4A6542340044ULL, 0x9964097BA3421893ULL, 0x14FAFDB22D459380ULL, 
            0x907C5ACBCB6A5BB3ULL, 0xE29EECFFD5E4163FULL, 0xFFDD55885C32E892ULL, 0x8F5A4A6307535382ULL, 
            0x4E751EC2E00675DDULL, 0x6AB6FCD039AF3A77ULL, 0xB74B16FC0ABC77B8ULL, 0x9002F6B64313CD68ULL, 
            0x8333F49FADCC088BULL, 0xCC3A3B52DFCE12C7ULL, 0x89972E387ECDD87DULL, 0x3D8FC1CC076DDDF5ULL, 
            0x5CABD4D60234B588ULL, 0xDD52D1F2818C13C3ULL, 0x8D08BF9F9F9321D0ULL, 0x8E65BC2300428048ULL, 
            0x725F1B4BA2066C8FULL, 0x7638FDB2F67AE01EULL, 0xE44D5C382461FA5AULL, 0x8B84FA42F9ED2D87ULL, 
            0x12F4ACC1D3BBAD66ULL, 0xB8274BE9C738FCC5ULL, 0x5C2E3EABDE3FA52BULL, 0x01CE8353C046F40DULL, 
            0xA7997E65A5C62F0FULL, 0xFD9DA915EC23F071ULL, 0xE30092D128024E69ULL, 0xDA83D51EE1C3A5E3ULL
        },
        {
            0x0364736C5E86D8BDULL, 0x42B203667002538AULL, 0x49838C0DBDC57E77ULL, 0x897865CF80568998ULL, 
            0x5635B30983A5C423ULL, 0x9822E9B1D319C7E0ULL, 0x141B783D8BBC903CULL, 0x982BA4F5E4CF46AAULL, 
            0xB01D3533F2C49ACEULL, 0x5F9D7DCF87A23FE3ULL, 0x2CCB836F643D3484ULL, 0x1012647A5C7FB7A9ULL, 
            0x32CFF838BD4432E1ULL, 0x28C8BDBC7D04C731ULL, 0xBCC5FDE9C15E2DB8ULL, 0x648A451307CEFCC1ULL, 
            0x0E9B8EE620CD6F60ULL, 0xC27FC3B9798D7B77ULL, 0x9C3706078E2705AAULL, 0x18D733B74C65560FULL, 
            0xE7A1384592F24269ULL, 0x36CB0316D8B72B11ULL, 0x5F439DDCB30655D5ULL, 0xA90252CABB3324B5ULL, 
            0x812423864DE67CB9ULL, 0x6A59328A05968219ULL, 0x5CC577869B679495ULL, 0xCBB971E9E4EDCE69ULL, 
            0x3A8E3551B3B642ADULL, 0x8421E8470104BEC8ULL, 0xCC15AE7DDDDD5636ULL, 0xACB58B00A9776517ULL
        },
        {
            0xD6EFC8B2E5AAFE95ULL, 0xB193C761F7BC38A7ULL, 0x5F71DD1656D63E38ULL, 0x36299EFDEEE9D6ABULL, 
            0xF40B0DF6A3084CBEULL, 0xCDEF31C6C86A1ABEULL, 0x7591D7FD2527F0ABULL, 0x86588F5870C28462ULL, 
            0x7D091A60A448F791ULL, 0x00BBCD7E0B634997ULL, 0xD84B6C866C936F7DULL, 0xCB8B0B6387FD1A41ULL, 
            0xD23A173F0C2A059EULL, 0x70BD20690AAF467DULL, 0x3A6865081BA50F87ULL, 0xDCBCF26A66F635D4ULL, 
            0x2E51C26AAE9ED9A3ULL, 0xC02C444DA29A7F49ULL, 0xCFC23F068C75A7B2ULL, 0x6430FCB4A0984F8CULL, 
            0xFCB3BB8447DB2CDFULL, 0xD555D4EB86E5E4E4ULL, 0xE4B6C8AA6E1C5C4AULL, 0xF57D84F3843FE23EULL, 
            0x660D944273D4866CULL, 0x8A522DA0D6EB837BULL, 0x8BF46F72FFFE36A0ULL, 0xBA947353ED241263ULL, 
            0x3D6999E908EFD93DULL, 0xD0477DAD7CA00F0BULL, 0xC3C8C0275801E2C7ULL, 0x40D228A3CC67B7DEULL
        },
        {
            0xDC1ACC654737FE16ULL, 0x818B2F6CABB2EF50ULL, 0xF32EBE52E56CE9FFULL, 0x0AD23774338CA39EULL, 
            0x565D4D0A6E6D96F2ULL, 0x062A5DF718D9DAE2ULL, 0xC04E0339DAA52C88ULL, 0x97408876BCC6986EULL, 
            0xFA3960867DD0D9A8ULL, 0x7CF5037C67444438ULL, 0xFE3870E55E199F66ULL, 0x13174D70548DA949ULL, 
            0x49B53F42C3610E6DULL, 0xD736BF3E5E1A325EULL, 0x4AE904B400E3C8E4ULL, 0x79BE7CB6F3772101ULL, 
            0x5EC62A0E7B8208AFULL, 0x0B8DF2EAB1874363ULL, 0xB43A2765A4B36149ULL, 0x66ABC05BD7DAEE1AULL, 
            0x67FEB61826403DA2ULL, 0xF93BAF6568684642ULL, 0x3B15F832609AD82FULL, 0x6A9EBC1F1856B158ULL, 
            0x9088F42147FBB9FBULL, 0xB2EE0DFFFDD97DB9ULL, 0x435F6B3FF09AB61DULL, 0x8CA83403E2759729ULL, 
            0xD3C0B1D7AEFAC58EULL, 0x5526A38FEE366600ULL, 0x296C8D06B862DFC3ULL, 0x86BCBE5568E0D5A6ULL
        },
        {
            0xA44B29EC057F6A20ULL, 0x051E6424EB3E9423ULL, 0x4B0AE6490CDF484EULL, 0xFC74E37E77A234EFULL, 
            0xE37D9320389C1958ULL, 0xC5776B3A6B032023ULL, 0x7BFC41BC35B800CBULL, 0x4A7078589D6096D2ULL, 
            0x1B4F27C86873329BULL, 0xF6C34150B286A26FULL, 0xE46F6DC5AFF443DDULL, 0x98E2436EBEB8CDF1ULL, 
            0x634F28E798C72BD3ULL, 0x126A141DA4589B72ULL, 0xBAA29890D35F1323ULL, 0xF7FE9C815C6F4C58ULL, 
            0x4A93808B074FB303ULL, 0x49EBFEF586D6DADDULL, 0xFB2C5FDCBD748C7AULL, 0xD0BC45FF9D0325DAULL, 
            0xA2C6901820D3F2D7ULL, 0x020C952ABB3E8036ULL, 0xB3AD8C748B253B61ULL, 0x196BA59CF59C94A7ULL, 
            0x09510A38A028C904ULL, 0x3B5791FD1E36652AULL, 0xB8FA9C47985F4D4FULL, 0x764D63B985D2C995ULL, 
            0xA531EBC62D29826EULL, 0x4F1F1071CE3E111DULL, 0x6D0B78A96F9137DAULL, 0x2315F57775743808ULL
        },
        {
            0xB37DBC5162072C0EULL, 0x468543D766A1D4DFULL, 0x8E5245B13F8A9AF8ULL, 0x49DA662A3C8369C9ULL, 
            0xE8EC46B8AC17537BULL, 0xCD87C2E0CD8D692EULL, 0xEE3623691C727833ULL, 0x1EEED103D30BEAD5ULL, 
            0x3C83AF2682E7FEE0ULL, 0x98C0F6381FABD4E2ULL, 0x14342EF88DC80E0EULL, 0x10EEBE6F80460298ULL, 
            0x5C60E72C27B04380ULL, 0xC99944C391BD48C4ULL, 0x1147B623AF2DA681ULL, 0xDDE17803F0A961C1ULL, 
            0xFA1A07566935E04BULL, 0x4E1266ADAF2F368AULL, 0x7C7CB8D707DB7072ULL, 0x93F6D0F7494AFB92ULL, 
            0xAD1B8CC20EEF267BULL, 0x36C5C6E28CCBB1C9ULL, 0xDCFBCEF1C11B531EULL, 0x8BEA49949EC71199ULL, 
            0x01DAD6A00EC991B3ULL, 0x2A1E153AE5E6F3A9ULL, 0xB880245BF8C3BF52ULL, 0x12B9A23ACB982A9DULL, 
            0xD1C1D8349FD6B017ULL, 0x7B9588896AD9EF4EULL, 0x28D291D3A569153AULL, 0x2C3A53304FF290D1ULL
        }
    },
    {
        {
            0xAE78BCC73B6446BAULL, 0x534669621C22548FULL, 0x244902C4055E6F55ULL, 0x4A49909C08308746ULL, 
            0x86E60B49D6945510ULL, 0x060D270CC1C826F3ULL, 0x68E36307289597CBULL, 0x8383C7EC877E7960ULL, 
            0x07E831EF5A91F5E2ULL, 0xD4BC55562C3765E8ULL, 0xF201DD4478FB9CB8ULL, 0x50A6693BEC7FEE9BULL, 
            0x5C71B2E939D5D75FULL, 0x813D632A76C806A6ULL, 0x6E8EC9FC92F84CA5ULL, 0x5BBFA95A488B2843ULL, 
            0xF2C3FB546B1AC8FDULL, 0x4D0A40DDDC389EBDULL, 0x3ABEB418414EB0C2ULL, 0x04B7F31BB549EF6CULL, 
            0xB902D9BAE2181607ULL, 0xAA03BC1DA8A2AC92ULL, 0x12FA3928F78BC29DULL, 0x11BFC0D1ED04E941ULL, 
            0xE53279D65BEF3235ULL, 0x2311711E74054735ULL, 0x1576FE6EC28421F6ULL, 0x8C2770626D97DAADULL, 
            0xABE36A57184BE04FULL, 0x0CCA310B4DCD77B4ULL, 0x08F1012C46F5679DULL, 0x39C1348C2FD347A8ULL
        },
        {
            0xF60CCFCF22E59665ULL, 0xF03CE63EA09DCE47ULL, 0x8F034AC06D549CD0ULL, 0xAD5209083E1D25FBULL, 
            0x4FF952C9E6E0DB50ULL, 0xB20D3A2B5D534D32ULL, 0xC3CFC38A8B663922ULL, 0xDAC800CA7887324FULL, 
            0xAE51808B048A188BULL, 0xA8A9D4B75DE7CF92ULL, 0x4017820F8C87BDD6ULL, 0xDF77E3AE1637FE39ULL, 
            0x05E3DF9AD8C2CE41ULL, 0x27E04E6AF9E4D8B6ULL, 0x87C581E04937B590ULL, 0x7E3F5A2CEC41D6CBULL, 
            0xBE0598F5CEB28AC3ULL, 0x0560673DD5BAE376ULL, 0xA1040AA8EE8193A1ULL, 0x8F136A43AB2F4ED4ULL, 
            0xFBF8788A4A8D6A58ULL, 0x472DB99020DAE9ACULL, 0xAD7904BD186DB779ULL, 0x2693D814084AD868ULL, 
            0x177E7297E5BE931DULL, 0xDFEA68319DA99659ULL, 0x358FF5D3C45BCF6EULL, 0x62B1220D141504BCULL, 
            0xE2A374EDA1314912ULL, 0xB126A30DCB94F340ULL, 0xFA28463C81F81878ULL, 0x8F309AB11D412BCDULL
        },
        {
            0xF9600B42D06AC775ULL, 0xED2E063A64EBC9B5ULL, 0x581A10F7A2D4CC98ULL, 0x14C0DB649DC69942ULL, 
            0xA1FA608CD727BA4CULL, 0x2B46E8C1B0BE3D55ULL, 0x44032A4EDAF5D182ULL, 0xD41F29CCB1424D46ULL, 
            0x178C09001562EBC2ULL, 0x9D91295176D3B6A3ULL, 0x2DB1FA11F7669A54ULL, 0xC8DBF4BB51823D26ULL, 
            0xCA762D308BC2921FULL, 0x78C6C286B4C1FC49ULL, 0x4855B26232E7561DULL, 0x4D3CF312077DA9D5ULL, 
            0x977E0045E0690063ULL, 0xD68D4F714E956179ULL, 0xF5A4E7EBAB593BF3ULL, 0xC06C5147EE1AB179ULL, 
            0x959CF7A9F3921D62ULL, 0x7FC9F550993F3597ULL, 0x9477B329CC7DEBD0ULL, 0xE1A94CEFB5F4908AULL, 
            0x404949250E3A3CE5ULL, 0xE88102899912F67EULL, 0x8232D0212AF0C81BULL, 0x3161C4A1BF235AE1ULL, 
            0x4F26BF099778ABEFULL, 0xE9E4BFB802158816ULL, 0x27BB9A3A9B1DA930ULL, 0x27C9952DC0A56A3EULL
        },
        {
            0xDD079AA4F998B086ULL, 0xCC13DFCA9B967E44ULL, 0xC131ED6406ECFD62ULL, 0x90FE4796C6FB666EULL, 
            0xF608D2B59C15B94FULL, 0xEC616353BA048C4CULL, 0x6743FCEBA6D6A555ULL, 0xC6C053E482CF23C8ULL, 
            0x2DB8843A83490AC1ULL, 0xE6EDBDEB2A5A4E52ULL, 0xF6B77946B2ECAEAFULL, 0x1CA66238D2C53FDBULL, 
            0x94A2544BE073B0E1ULL, 0xED004BFB7C241730ULL, 0x754E4A7AC83A2F11ULL, 0x1855A4BC84C8808EULL, 
            0xEEB463ADD7B615B6ULL, 0x08325AB66F76879DULL, 0x750F463A5E24BEFCULL, 0x03CD4C10B9BA3B09ULL, 
            0x891A9D8BABE57F0CULL, 0x2CA19E9CDA0CD8D0ULL, 0x56D1205B779E3441ULL, 0xC2FCC9581A91B41CULL, 
            0xA4C371B0473D344DULL, 0xB6958496D40028EDULL, 0x57C4B8B70776DF63ULL, 0x2D1594F0E46B30AAULL, 
            0x7ECB2D32362939C5ULL, 0x1DBF798429997950ULL, 0x2C59632B3ECDBA63ULL, 0x65F23C38671DC4A4ULL
        },
        {
            0x0A70D708BB78470CULL, 0x51CE4776C00A7EBEULL, 0x0017139CA60C40DEULL, 0x386CE90FCCD25AE5ULL, 
            0x661DD9474A434F3CULL, 0x3B4E0CE3BECB08CAULL, 0x5950705AAB995AEEULL, 0x0FBB0C55D218CBD3ULL, 
            0x3568ABD4CA02C77EULL, 0x07F2222265A60044ULL, 0xC1616D20D44FE7A3ULL, 0x7ADF2B8BF4C25BAFULL, 
            0x89378D26C9E89D2AULL, 0xBB5F149D2D4F983DULL, 0x90BEDAAA78B108D9ULL, 0x00A9B7157D9C190AULL, 
            0x701C218AD7ACA8C2ULL, 0xA27389F1F9CFFC62ULL, 0x0644F9A11B5D5C6BULL, 0x5EB26DFE2B57A6F5ULL, 
            0xB304063A28BC3927ULL, 0x8793B85ADE946036ULL, 0x3D36BA2C46979CEEULL, 0x11D93573E43F40C1ULL, 
            0xA000EB4DF01AC7D3ULL, 0x721E12907B049BCCULL, 0xEBA33BD1C27F858BULL, 0xE813FF8037771A6BULL, 
            0x8782104C55AC8AF1ULL, 0x80275002B2F55099ULL, 0x9D696EA1080D94A8ULL, 0x539AB7459E1C496FULL
        },
        {
            0xC499CC350AC6D97AULL, 0xD65D46DFB2CA6672ULL, 0x93E7052D1D5E816AULL, 0xFBAD635F40000880ULL, 
            0xB4017DB3292FC56EULL, 0x50661BA84D03AB11ULL, 0x5ED780C82B7120E3ULL, 0xC07DEB01C7F11BB7ULL, 
            0x627D78A5BD5A40C0ULL, 0x3589D817553E7AD8ULL, 0x17DCB2565E32395AULL, 0x7299D061AF25D57EULL, 
            0x1929A8455D421C2BULL, 0x2656F751E2713A06ULL, 0xF174A596E9A0AA0DULL, 0x4D7E59FC1278631CULL, 
            0xC36BAC221ED10A28ULL, 0x01C0DF4FDB8E1076ULL, 0x982B0318B22A3DC0ULL, 0x0FC2B4ACC9DA2ACEULL, 
            0x5190145A8C240477ULL, 0x9C81656FB09D56EEULL, 0x2B55694F12A4FA76ULL, 0x3CD26CF072FB4618ULL, 
            0x34CAEE3F6EA45D99ULL, 0x93DBBA4CDC8C89C5ULL, 0x02B7F17206E8061AULL, 0x8E822E5580B4D714ULL, 
            0x42B9175E3296EA00ULL, 0xC0C4B3C6B4827C41ULL, 0xCBED8A1538C740E0ULL, 0xA3CFD00F71ABD217ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseBConstants = {
    0x0901733FD756A7A6ULL,
    0x8B77D29645BE76E4ULL,
    0xBBB1507E60DD40CCULL,
    0x0901733FD756A7A6ULL,
    0x8B77D29645BE76E4ULL,
    0xBBB1507E60DD40CCULL,
    0x9601417C757F3024ULL,
    0x1CB3A26507E4CC7AULL,
    0x46,
    0x6E,
    0xE3,
    0x1A,
    0xA1,
    0xA4,
    0xC5,
    0x4F
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseCSalts = {
    {
        {
            0x21FD7F58596D60F8ULL, 0x4E7DB7EF25B6BF69ULL, 0xD1DDC3283BC4C3CAULL, 0x7D0E2324D6989610ULL, 
            0x300ADD86215691C1ULL, 0xA007E42C29F9C97CULL, 0x278CF0AD2739FA1EULL, 0x275CA1AAEC1B732DULL, 
            0x5A86F5CAF1FC309BULL, 0x7322DB3044B5AA86ULL, 0xB229F02E133B865DULL, 0xEA7E860932607412ULL, 
            0x8FE49D97D8F5C299ULL, 0xA97ED045E0D424B0ULL, 0x9C94B7F136AE95F5ULL, 0x4586BB7E04700A6FULL, 
            0x5C6309F33ED0FF49ULL, 0x33C0585B7465E0A3ULL, 0xBAED849630812D8EULL, 0x5CBD315E16775033ULL, 
            0x0937B6C47E32A3A8ULL, 0x29C969B672F93F35ULL, 0x19C206F113431A2CULL, 0xABACE7667F80F25CULL, 
            0xC139903078FBFBCBULL, 0x5D8443DFB6AAD134ULL, 0x082DDE76F62DAEF4ULL, 0x4696BA5506A9FD16ULL, 
            0x5602832B1CE337E7ULL, 0x81B1819E3F8FE7B2ULL, 0x1BDBD9A8C3E5AC18ULL, 0x2DC1A17BE01B6083ULL
        },
        {
            0xAF6234AE9A9420C1ULL, 0x162AE960E300C917ULL, 0xF71DBA81AE9A475DULL, 0x7D99CE3938EBF473ULL, 
            0xC2496B5263DBB576ULL, 0x9DB187150D620C0FULL, 0xCDC852A69E86C86DULL, 0xD3A1901AB3FA02D4ULL, 
            0x8FA31755EF30A5CBULL, 0xB889249713A29952ULL, 0x533CB9CE4C25E0EBULL, 0x9BC971AC3E2390B3ULL, 
            0x7F75205E732072A5ULL, 0x65B9DC074BC8BF97ULL, 0xE3E77AC4ED455165ULL, 0x1EED72C4A850320AULL, 
            0x926C215103FEA4B0ULL, 0x7C26FE5D0D75F10DULL, 0x54CFD590C00F69D4ULL, 0x69FCEC8C3C669226ULL, 
            0xC547082D8F39A491ULL, 0x06A5B8158D23EB0DULL, 0x21B63795E397BF6FULL, 0xBCBCDEACBA7E1573ULL, 
            0x0E5E6C088EEC3B80ULL, 0x616D11DE523D37DEULL, 0x2ECD3086CE940FF7ULL, 0xFF1C3832CC6D0A19ULL, 
            0x4AF8B24680C1E66AULL, 0xAC33A2700F856AD9ULL, 0x4D9F92507AAE3DA3ULL, 0x46842B14219F20A3ULL
        },
        {
            0x188EC4E969B1709EULL, 0xEA812C200418ABD0ULL, 0xC774A7C758FBB36DULL, 0x08B3B9446F585045ULL, 
            0x3BCFCE56CCE1B5D3ULL, 0x4E8F26389E1A6DE3ULL, 0xDA0600540EE1320AULL, 0xDC5E6DC3142F9ED5ULL, 
            0x3C9B92401D8E29B3ULL, 0xF41C64E612B3064AULL, 0xABDE4B92B80C6871ULL, 0xF95E6D83B154DF6AULL, 
            0x3D1B989F2470A0C6ULL, 0x53D35AFD05222468ULL, 0x52B8E245665FEC4AULL, 0xF4B6E1D3F94D518DULL, 
            0x46FD52255A66C62BULL, 0xE6326C271A64B4E2ULL, 0xD3E1BC2193BBC8D9ULL, 0xAC21427AFD454A68ULL, 
            0xEFD60A9DCBED0068ULL, 0x5DB8F2CB744B82FEULL, 0x07A260A59F206ABDULL, 0x371E22B353515514ULL, 
            0x9D58B99F898A57D9ULL, 0xD2AAE04AC368FC03ULL, 0x30C97EFD39672BA5ULL, 0xFC7F3F2ECF96AED8ULL, 
            0x64E83EECF0D69642ULL, 0xBFBD1F7D01653C19ULL, 0x989FCFBC6F700775ULL, 0x7F0BF98DBBFE37C4ULL
        },
        {
            0x390DDBFA82DC4D91ULL, 0xAB1F74C7E3658BD2ULL, 0x68559EF988237C3FULL, 0xB8DAF9F62F5D7E20ULL, 
            0xF1D347F48C0094BBULL, 0xB608A178625FCB29ULL, 0x3FC2BD21F83BAC97ULL, 0xC8EC8C7FCDA4C9C0ULL, 
            0xE0870EBFF7542F22ULL, 0x7E4288B15B850A54ULL, 0x17CEAEEB577A7CA9ULL, 0xDE6FFF8E97425148ULL, 
            0xBDF740EC8FEF957CULL, 0x760C3BEAAA0EA4FCULL, 0x9065B3594F0CE619ULL, 0xCE11BF12BD2B97C0ULL, 
            0x5514DA01DE530B73ULL, 0xD6E588187E384FD0ULL, 0xC61C4ED5578463F2ULL, 0x0684AAD8B8AA3B9DULL, 
            0xD90C44ACFD47966EULL, 0xFBB5DDCA3CF85CC9ULL, 0x84AEA627E9A19FC6ULL, 0x555F09AFF99570F8ULL, 
            0x032659E364BA5E29ULL, 0x31ED22CDDDA20038ULL, 0xC78AE6353E1EA261ULL, 0xF1DB4FAFD6C4A3FFULL, 
            0x97098CF2599F5BD3ULL, 0x39373A3617E1D3E4ULL, 0x464D41769A719BC4ULL, 0x22B0B6AFC88D9D76ULL
        },
        {
            0xF9469A7DC36AE9BCULL, 0x639B81DE5CDEB87DULL, 0x45B0993C61A366B5ULL, 0x7807B6B414054EB5ULL, 
            0x0B5926DD118FC8E5ULL, 0x82AF4CF20558BA05ULL, 0x37521E9B98232524ULL, 0x283271282BC9BC50ULL, 
            0xD0D4B6569A565E72ULL, 0xF866EA9F66E427D5ULL, 0xCE53656D439F5B53ULL, 0x2E7EB2B08D24B990ULL, 
            0x730231E1BD3D4113ULL, 0x9434B91F83EAFBEAULL, 0xA561BB7434B196F8ULL, 0x92510BE3CA2D881CULL, 
            0x2F2DCDB1736C2520ULL, 0x6375AA20D86D877DULL, 0xC8DE153B83436CCFULL, 0x69F8ECB09B6E760AULL, 
            0xC0A9DDC942FA3A86ULL, 0xACA3685028849F02ULL, 0x59BFA5574F420ECFULL, 0x95C805CCA5A67B4BULL, 
            0x168A5D3B518429D1ULL, 0xB7F42803C4DEAAEDULL, 0xAC7C7C00FC7BF366ULL, 0x37BF00117AB2B9BEULL, 
            0xB5FDB97962090CF1ULL, 0xA00507EC9905F86AULL, 0x4F284ADDD6A74958ULL, 0xAC7310A5BDEBEB9BULL
        },
        {
            0xA1FE78F1DB15940BULL, 0x93AB7F0D69225B47ULL, 0x85B9A321EC711C8EULL, 0x74371D22FD18345CULL, 
            0xF8DEE970ABE914B6ULL, 0x58A8AD6F53DF888FULL, 0x04DCC723DCEF5F2CULL, 0x64809323C2E51090ULL, 
            0x9862068A348708B1ULL, 0xE3001513F21EFB92ULL, 0x549B5E08BDD0556FULL, 0xA1885044F5FEFB76ULL, 
            0x2CCB4848A7434AE7ULL, 0x0CA589C1D5474079ULL, 0x649DBA73440BB771ULL, 0xE517A3A61D62CEE9ULL, 
            0x275C034F3F4C744DULL, 0xD4FC1FE017BE7778ULL, 0xFEA04D2F8CD8E4C0ULL, 0x5F014E557F3B93D0ULL, 
            0xCD5D533CF017DA70ULL, 0xDAA4F97397F7DD37ULL, 0xC6878D8E6C38BA23ULL, 0x7B70B733DEA3809FULL, 
            0x59FE96655307567FULL, 0x42018FA67F11B4E5ULL, 0x7D35823264AD1552ULL, 0xE315D5FB9CAC50E0ULL, 
            0x42683B83AE6CC558ULL, 0xF2F88FFD884D2B43ULL, 0x9DDA606E975D8638ULL, 0xEC2B9D09EE9AC6BEULL
        }
    },
    {
        {
            0x130365B9C8111D66ULL, 0x2EB83A8BEBC6754DULL, 0xE6ABD154ECC9EEE3ULL, 0x2C7E74608B32AC29ULL, 
            0x1E30BCC3880805CAULL, 0xD405EC0FC56918A8ULL, 0x857B59DD8822B5F0ULL, 0x672817152283FB60ULL, 
            0xF95470976473A4DFULL, 0xC1213C1A96CB896BULL, 0xF580FE7400AB942AULL, 0x5ADF55E0253AC749ULL, 
            0xA8A8CC8FB362F4ADULL, 0x74B27EE66AB1E9ECULL, 0xB781CACD16EB1848ULL, 0xD27A4850982D2861ULL, 
            0x72D12EB3D73171F8ULL, 0xCCB4E20D500725F9ULL, 0xD8F3D1E44C9FE9ACULL, 0xFBA590B3688AC8FDULL, 
            0xAD7C630753025CC1ULL, 0x0D63647018D12DA1ULL, 0x9276CE9FA69D5106ULL, 0x17D253187FFDBD48ULL, 
            0xDBDCA4954C35C778ULL, 0xE7EDEE76D9D5A003ULL, 0x4403669CFCB721CAULL, 0x733448B0FE79DAB3ULL, 
            0xEC39F6293C80A2D1ULL, 0x97F7C7A298876A36ULL, 0xA5DA66C6D0A7FEA0ULL, 0xC8BBA98C5DB08E63ULL
        },
        {
            0xDCF5CE0D1FA3C3F9ULL, 0xD6E6F96FF40CB717ULL, 0xA99871C474AA470AULL, 0x667CD28975B4BCC9ULL, 
            0xB41F48CF0AE08A30ULL, 0x91CC61F6CAF6895FULL, 0x797A15C3CD4FBC5BULL, 0xC375917535C8FD83ULL, 
            0x18E38498D3902F43ULL, 0xDB900D169B69E37EULL, 0x7989244A98F3E920ULL, 0xD87C644DC2027845ULL, 
            0x6EC0ECF6F391FA0DULL, 0xCFCD7BCB56B8C5D1ULL, 0x4497166D062747BFULL, 0xFDD8B643C5D5714CULL, 
            0xF42FFDC68EA31AE9ULL, 0x7CD00FE818E155EBULL, 0xCFABEE99E4A18696ULL, 0x75B943A068673BB1ULL, 
            0x71AE2E8CF936AEF8ULL, 0xAD1B5453E2AA2378ULL, 0xCDD547E9DAF99EE1ULL, 0x2467EB9DAB6FC466ULL, 
            0xABEDF2FBA8798410ULL, 0xEA182DA94864D279ULL, 0x5E9646BCEBE1B0E4ULL, 0x2FD5FE137DE35713ULL, 
            0x67DE8B01A6271805ULL, 0xD7116FFDFF00A8AEULL, 0xB30F77058A563CE2ULL, 0x2E8865FB88D7069DULL
        },
        {
            0x923D82116BC626F1ULL, 0xA9F9384935E5E24EULL, 0x9EF74E7453653267ULL, 0x728A320E81897B59ULL, 
            0x3F5248568562A198ULL, 0xA4FA79C5F56CE4CDULL, 0x357E54BDCC66BE19ULL, 0x99733317C038F153ULL, 
            0x9EB312E713E451F4ULL, 0x87E69780B2E426C6ULL, 0xA9E1140BFF0E1525ULL, 0xE1575BBBFCBE660DULL, 
            0x985E7221185BCC10ULL, 0x70897B88DACF113BULL, 0xE29027B207638442ULL, 0x2F5E8E16E9D5EDC2ULL, 
            0x329C3C5B86ED7270ULL, 0x8C832A6AA11BD215ULL, 0x14CD823788260778ULL, 0xC4463A4A61AEDA51ULL, 
            0x987F2BF932799FAAULL, 0x154BD4650897CF01ULL, 0xD0BEA1126A0F2D38ULL, 0x773636C4B412091CULL, 
            0x00B4ED89B7D5BA75ULL, 0x27CF37E617B98259ULL, 0x355497B73EFA81E0ULL, 0xDBD146FF1C85B1D9ULL, 
            0x8ECF0A2AF30A55B2ULL, 0xA39CC2C137DE3611ULL, 0x1282F0B1CF902D0EULL, 0x093D5832ABA178DCULL
        },
        {
            0x6D15A9E3F1419974ULL, 0xFCF96A028CC47D33ULL, 0xB37E4C09511E9CBFULL, 0x570D14F835D74209ULL, 
            0x8F9A11FD952D63D7ULL, 0x95331528BE7DB9ECULL, 0x3336D9B2A1F80AAFULL, 0x9E3D1535E1168F01ULL, 
            0xE6DA1B95A4AF42D6ULL, 0xA10ACF2E4EFB7446ULL, 0xD35290D354DC75A9ULL, 0xED859AB4406F5F0BULL, 
            0xFB9ACA7196087E5CULL, 0x55B37C74C7709FD8ULL, 0x042BAA1741173189ULL, 0xAB4351B2131426A5ULL, 
            0xD12AC8F967B56A84ULL, 0x60F51E1BAACBE8E7ULL, 0x2182CE6B6920E9D2ULL, 0x64FB58C8938D74AFULL, 
            0xF1ED28E71B4E9193ULL, 0xD1ABAE2FAE756EDAULL, 0x34BD979544F28366ULL, 0x328F23F35AF32536ULL, 
            0x87794F6CE0DF3095ULL, 0x673096A6216E6870ULL, 0x6B44AE9AEAF5E8E8ULL, 0x8934070BA6DC2C78ULL, 
            0x588DD010A58931F2ULL, 0x3F47D8C89497AA34ULL, 0x1E1E3FF879F1AF87ULL, 0xBC06CDCA4A1F3477ULL
        },
        {
            0x2F67E350CEC77319ULL, 0xCE72A63C2A67FE50ULL, 0xD98C66948F19D055ULL, 0x48AC95FCC202D38BULL, 
            0xA38C0C53B9292C99ULL, 0x6A27A9CAAFAB8E7DULL, 0xFD2C5A258CE06EDBULL, 0xFD461EFFB653A921ULL, 
            0x841E8050E4824FD9ULL, 0x8CE2213E6EF85336ULL, 0x04E9878D56408E7FULL, 0x4315E82EAE48A4F9ULL, 
            0x4FEECB6CAA4403F1ULL, 0x2B96BFFAC53AEB52ULL, 0x5785084BC3DC7860ULL, 0xBAF2FCCEB4AB2D16ULL, 
            0x3394E6DA5C2610F2ULL, 0x2A39345B364E14CAULL, 0x8F28E62CA6E2D8F9ULL, 0xFB4C303FA16E459AULL, 
            0xA2B2136536B72921ULL, 0xE46669364766AB65ULL, 0x3A5DE336D8DD9685ULL, 0xA49A1EAEE2DCFBCFULL, 
            0xE5991A8ED9DE9254ULL, 0xC11BB226386058A8ULL, 0x5D9A595FA0C17AECULL, 0xC5FD386EF0CDA92AULL, 
            0x4836C8A72D0AD6E2ULL, 0x4965D69C084D4402ULL, 0x1D113707CC43F894ULL, 0x0702E559937D2A5DULL
        },
        {
            0x3114D9C766B0DEBDULL, 0x43965C3E939124F8ULL, 0x21DD59D06A761805ULL, 0x992FD1DFB7CD67C0ULL, 
            0x36278949FBDAF941ULL, 0x9F21EF2B66307EA6ULL, 0x83F2FE5EE5DAE589ULL, 0x6C0E4A87DCCB9854ULL, 
            0x16ED761191DF1694ULL, 0xEAAEE9F40782AAD9ULL, 0x268A8B678AE250F7ULL, 0x76A8271F25D4FAE1ULL, 
            0x6B15C30616564DA7ULL, 0xCF7BD0A4C9985CD1ULL, 0x4BD38F267D290DE3ULL, 0x5FF4A67EE15D1BE5ULL, 
            0xD1EEF582A4565721ULL, 0x7A5FB4CFF0F88C9DULL, 0x85D7DC2F313AEC57ULL, 0x231E2E2899B24066ULL, 
            0x7A666D5407AD541AULL, 0xDEDF3E9390FCF31FULL, 0x67A6BA4300F08360ULL, 0xE8AA30D7C45BB445ULL, 
            0x5CCBF5BF2D98E260ULL, 0xFDC24619B0314035ULL, 0xA093331796C5C9D8ULL, 0x4003FB20757F050CULL, 
            0x035381FAB891C0E6ULL, 0x5A46AF66B59E8C15ULL, 0xACED5EC09D174049ULL, 0x56E10CAB5B7C7F80ULL
        }
    },
    {
        {
            0xD58579C94311E675ULL, 0xA7CE8F4D6540C6A7ULL, 0xB9E776DBF528218AULL, 0x67D0F5708D2F1B5EULL, 
            0x416EF376AB8BF1C1ULL, 0x1CF546B168E01C58ULL, 0xCD982F3DE2EDB078ULL, 0x576AC27DF94B382DULL, 
            0x63D5DA83F756A76AULL, 0xE090C9B34D716D3FULL, 0xE210A0D619CB6AEEULL, 0x5EAED8108D43C460ULL, 
            0xA1D0ADAE0910CBD0ULL, 0x568B363F598A8A88ULL, 0x36CA02F78AFEB8AEULL, 0x764699671219892AULL, 
            0xFB132A42EC93E558ULL, 0x1F48E6DEBB7F558CULL, 0x3AF3D93BAF125605ULL, 0x8C1450D0638F2660ULL, 
            0x74C1520C145F1E76ULL, 0x460DAE3384CBC1ACULL, 0x359BC7EDA2B6BC2CULL, 0x71238D03690CE328ULL, 
            0x7E675470E0B39087ULL, 0x0840A706472C6AF9ULL, 0x37AF4F799BD24D8EULL, 0xEFADF0405DC0D45BULL, 
            0x65730B1B891B80BAULL, 0x48289566512C6B28ULL, 0x25E5BFC480E738ACULL, 0x727EB691517DA7D2ULL
        },
        {
            0xC2DA2005AA281F33ULL, 0xA530C9AFC8F07B2DULL, 0x027D56AF6B1380CAULL, 0xE255587EB0D5BEDEULL, 
            0xF6C2B3B4FAE2D6F5ULL, 0x97F0D65392461750ULL, 0xD58FF35DE6F19497ULL, 0x8DC9011FF2C0D303ULL, 
            0x12A13F965EE2AFD1ULL, 0xC99F16A80755FBABULL, 0xD48CCFC2BF2B40F5ULL, 0x3272291D63ADC089ULL, 
            0x0C988AA544FAF735ULL, 0x5824503D19FD00F9ULL, 0xDEF668020137C3FFULL, 0x527DE48D4F9A509DULL, 
            0xBB2FFA51DC1D740AULL, 0x3AE3D952C1C1C464ULL, 0xEEFF120BAD6FEEFBULL, 0x8706485601E7011AULL, 
            0x60FB4DD58810CBA4ULL, 0x366A2F9E396B941AULL, 0x9B485B2A43AF3A34ULL, 0x509E6CA92FBC217CULL, 
            0xB1952D76B2AC13C5ULL, 0x6FDE37683346050DULL, 0x3E9646911300501BULL, 0x7B642DCB0016E723ULL, 
            0xD7DFAAE209A23715ULL, 0x64609FABEDF84D6AULL, 0xDAB6F70722D1FC4BULL, 0x56D8E3027E03B413ULL
        },
        {
            0x8BBD2DF13C980C2BULL, 0x3C14B9636B5DF61AULL, 0x5E9F1B77E73F7E8AULL, 0x27102A88A2ED51A0ULL, 
            0xDEC5D3513D6A0AE9ULL, 0xE057BE8D69B9ABC8ULL, 0x5448340AE605CA7AULL, 0x106F676B46DF3C55ULL, 
            0x08B9CD8AF5919634ULL, 0xA0A2380FE743039BULL, 0xB21B6D709C33A1BCULL, 0xF16AE517E969401FULL, 
            0xB8B9ABC5B4322679ULL, 0x34C3D2109C4EF5FFULL, 0x11B652AC483E8249ULL, 0x2ADFE0DED13221AEULL, 
            0x0ED94ABBB4BD7AE6ULL, 0x2E194987C082D696ULL, 0xFBAF9C1E9D4541DBULL, 0x76D53A1F62F881A4ULL, 
            0xBF91BF2193399E3BULL, 0xDA34C51A2E66E907ULL, 0xEAA10718E959C085ULL, 0x2005B935A50275D9ULL, 
            0xB88B88AA6CE7AFA0ULL, 0x86D4C322789978FDULL, 0xE9C399D79D176DBDULL, 0xD8C075741A097666ULL, 
            0x7EA90498F3B62AF0ULL, 0x50ECFFA649890916ULL, 0x71AFDA83F94FA9B9ULL, 0xF4B0C3D52953663AULL
        },
        {
            0x4EE8583463B99358ULL, 0xE56B3C80E5D5C218ULL, 0x99C4E5CCA7122F85ULL, 0x6135DC652A704050ULL, 
            0xAC0A217911EF50F3ULL, 0x674AD9E8BE0C949AULL, 0x57EC2435134F460DULL, 0xE7A29B2EDB0F9CBCULL, 
            0xF57BE7665C9E43A5ULL, 0xA1B931C2279D053DULL, 0xA3300E2206330E8FULL, 0x170FE26B3A386144ULL, 
            0x5A5AD87546BDFCA3ULL, 0xA0824240308E3B48ULL, 0xFCE3D58055BB82F1ULL, 0x2BDFADD855A1A57CULL, 
            0x0693686E469AB91BULL, 0xF71E149922E8B3DDULL, 0xEDC4165181C60F6CULL, 0x0BA970F7A6EC368BULL, 
            0x5AA3EA3B455B25B2ULL, 0xD44C968316129533ULL, 0x4F1096F9683C012CULL, 0x62C43085A3F79FC7ULL, 
            0x152AAAF7215B71B6ULL, 0x580998E138AF707CULL, 0x02053246AEFF4249ULL, 0x3F69E077864D5B1DULL, 
            0xE3FC8A25E982591FULL, 0xB4FE7773F2D12552ULL, 0x94D21476F3CE2F33ULL, 0xB3358007E7D58F10ULL
        },
        {
            0x3B57AB9F3DC25BA5ULL, 0x6750BFA6B84E2494ULL, 0x942F57463D4B62CBULL, 0xC80885CF0AB76D11ULL, 
            0x05E8A73B6D8649EEULL, 0x1088B59BA9854E9AULL, 0xD7EC3CAB2B79C4BAULL, 0xD6FEA5B4122D8C05ULL, 
            0xC2BAF03B0FACF01DULL, 0xC44AED83BF82DB5BULL, 0x1EEBF1F47EFAA37CULL, 0x72E5F1E91746D7FEULL, 
            0xAAEAA12F1F4F9217ULL, 0x483CB81811AC0D52ULL, 0x7F942945D75990F4ULL, 0x0A8178E9D30AA187ULL, 
            0xB1A3E295F0101CACULL, 0xCCE7B81B1EEAF61BULL, 0x81953DD06C858446ULL, 0xCFEF86F1BE86E4FCULL, 
            0x1C692704DC1B908DULL, 0x9489A522EB177926ULL, 0x29539F5B3F8CCB19ULL, 0xE5021D81884405B4ULL, 
            0xAD657B3667962591ULL, 0x7DCE17466A65EA36ULL, 0x3E5B7B22E49F5EE9ULL, 0x22A8B7FEEE895269ULL, 
            0xDD718187002DEB81ULL, 0xBDF4DCFD8BA8CB20ULL, 0xE38161AAC38F2DB2ULL, 0x48988B13DAD53A0FULL
        },
        {
            0x0C47B5D3C9E447DAULL, 0xAEEC54189FEB6C29ULL, 0xDB320C08A8B81143ULL, 0x8A6543EC42FE3292ULL, 
            0xAD4DB12DA5D18CB5ULL, 0x1490CD3CE9FDAECEULL, 0xF5A6E0F64DD43565ULL, 0x31FC4C4EB425ED1EULL, 
            0x9C772BC93B3D6196ULL, 0x3A0E6A7D5E2A1EB4ULL, 0x54726E1780B4F512ULL, 0xF760CD8CB42B120FULL, 
            0x29032EB66D10A8D1ULL, 0x8C5DB43FD7278BFFULL, 0xAD7E802E3A0A28A1ULL, 0x433BE40B831BB234ULL, 
            0x92ECCD240D9ED3DFULL, 0x7D0AD1AF4AD68688ULL, 0xDB3B739AA0A336BBULL, 0x781AF80580143D5DULL, 
            0xDB7F80C4045E1F6CULL, 0x9E4254778A931BA7ULL, 0x2598290808C244CFULL, 0xD61A4B4E9F132252ULL, 
            0xB0B1404D6C54DDACULL, 0xEC8CFDC6233B16CBULL, 0x4AB0EC2882CC6D96ULL, 0x95F88FE746C35CEFULL, 
            0xA1328ADF5AB1EA9EULL, 0x891D54196B5AC190ULL, 0x11502E4E2D5CC12BULL, 0x0E3BA5548679F0D7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseCConstants = {
    0xCBDADBFD5DB5ADEEULL,
    0xDD843483F7674B57ULL,
    0xE797F7B19AC97E03ULL,
    0xCBDADBFD5DB5ADEEULL,
    0xDD843483F7674B57ULL,
    0xE797F7B19AC97E03ULL,
    0xB5FB61D547B6BC92ULL,
    0x167F8CD1591141BBULL,
    0xF4,
    0xC0,
    0xC2,
    0xF9,
    0x5A,
    0xB5,
    0xB5,
    0xE7
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseDSalts = {
    {
        {
            0x654A811AAA51A539ULL, 0x441A95A62EDC631EULL, 0xCAF77732ABA23B83ULL, 0xA877F71F58518A8DULL, 
            0x0221146336E160B7ULL, 0xF210DDCCE7F51469ULL, 0x61688271E8D327F5ULL, 0x937C828C2A856FC0ULL, 
            0xE5ACDF70991B0CFDULL, 0x19E276B7DCCF9F3FULL, 0x0C3B66090BD76706ULL, 0xAF6D125374F87937ULL, 
            0x17874B47AB6A7793ULL, 0xF6BC8B7C3889CFB0ULL, 0xBF013DA39D9D4E4DULL, 0x12971E9DB41D3BA7ULL, 
            0x6FC208E0495C936BULL, 0x693D494DB27A091AULL, 0xA965F427DFEC865EULL, 0xBC6B2CA8B9CBB10BULL, 
            0x3387DD52D9577A6CULL, 0x73C0F3471DB71BC3ULL, 0xC760FB18B57E4625ULL, 0xCA00506906F33A24ULL, 
            0x316E06EE48C429D7ULL, 0x4114831C46CFEF8AULL, 0x1A0A18E763690D8DULL, 0xD16C20B0C07D4B52ULL, 
            0x24167C85AFA749B1ULL, 0x8E9CC3E52DF9963CULL, 0x14FC7CB236FB74A5ULL, 0x1D8F3639F0B557D7ULL
        },
        {
            0x10AE814DCD13C959ULL, 0x558AC5EAA496AB36ULL, 0x955031EAD1D1C019ULL, 0x5E09076F728A5BE7ULL, 
            0xF725757BDA4D8B08ULL, 0x7B71A1B685C56801ULL, 0xEEA9A02968684ACDULL, 0x395CE659BBC37634ULL, 
            0x9ADDC73B79E57284ULL, 0x0BF0DDDD913F2C9CULL, 0xB1D0C0C0A7BE31D8ULL, 0x9FC53D022A6A24E7ULL, 
            0x202A925162647F5DULL, 0x42FD4061BD198F03ULL, 0xEFC4715DBFFCAAADULL, 0x3CEE04133CF2CAA7ULL, 
            0xD638B7F853217324ULL, 0x4D766B0D724C35D3ULL, 0x8FEE7384256D2CA5ULL, 0xEFCA5806AB3F3030ULL, 
            0xD202C4B140455081ULL, 0x31CF81C230EEE461ULL, 0x22E32055E95E06EDULL, 0x5DA8BC8470F44651ULL, 
            0x1B08369623845B86ULL, 0x7B156E5B0342EBD0ULL, 0xA0CDC537FCB00F05ULL, 0x66AE9EB41B55289CULL, 
            0x9D5083949BA8041CULL, 0x2EEC4A233BE0D699ULL, 0x7C83665AB9C59001ULL, 0x58F6D7B6D29EF0EAULL
        },
        {
            0x7975CCCE3B62F56BULL, 0x05FD7800DAF6034EULL, 0xBC6F3AC1A3010EA8ULL, 0x44F06BA0D95E52A3ULL, 
            0xDB9F97858775618DULL, 0xE54559C94A1D92AFULL, 0x8BDB05CFB8CE8911ULL, 0x8BB8431D37163734ULL, 
            0xC7E3572F63465A92ULL, 0x22511E3AEAD8FBC5ULL, 0xF8F4B55236CCF95FULL, 0xAF98D6CBE1E3DDFFULL, 
            0x926CFC052D88D77BULL, 0x061B09828532C82DULL, 0x65C7EB9B5362F8C5ULL, 0x57641CD16959881BULL, 
            0x56F73EDBA159CA6AULL, 0xF6E40096F187559FULL, 0x567430CAEA5363DEULL, 0x086F7F736036583DULL, 
            0x566FFE35E508CD53ULL, 0x498488BDC9CE9BCDULL, 0x9933A131364E0530ULL, 0x97A9E49C097767CCULL, 
            0xE61C4D5E397BC342ULL, 0x0D396CD7EA0D001DULL, 0x2D236AF234E538DCULL, 0x566242827A649B7AULL, 
            0x6F29AC08EBBD0852ULL, 0x1D8EF0E257FB5A84ULL, 0xC10D4E01CDA03FD7ULL, 0xFF6F3AFD7D1EBADCULL
        },
        {
            0xD09FC32471B05743ULL, 0x7E34E34CD554B434ULL, 0x192455DA0A0DCA55ULL, 0x7F49EBF7A3360080ULL, 
            0x173DB486A5E529B6ULL, 0x24019015BC92C3F1ULL, 0xF53B407E9B704482ULL, 0x74BC068B2D544D96ULL, 
            0xAAC9D9434BADD84BULL, 0x5A7A932C60B8E9A8ULL, 0x1AAD5455C36F3E9DULL, 0xA7E274AEB39F807DULL, 
            0xF0F1712F19053FF4ULL, 0x333775F4B8CEC93BULL, 0x589C18171ED2469AULL, 0x9215BE8E4BA6F2CBULL, 
            0xF7A565BE3C4A5AC5ULL, 0xB5A4AE41C7EE506EULL, 0xED47D2DB68D557A3ULL, 0x52BA255B3A034294ULL, 
            0xFE02D31299776689ULL, 0x7EF86DF9F99BEA74ULL, 0xE6B103841D2874B3ULL, 0x00C5D5017CC87DD4ULL, 
            0xE30742E90BCEA0C6ULL, 0x7D53E8B60A880276ULL, 0x8378715960E81AAFULL, 0xD49EAEF5D6D0EA6AULL, 
            0x3285CBF239D089EAULL, 0x24BB559B1519E557ULL, 0x49AD314201C92D8EULL, 0xCBF38A8839C6DF90ULL
        },
        {
            0x55864F5B74F23110ULL, 0x5C8FD69F073BA5A9ULL, 0xD000394B9E0FC6BAULL, 0xB5FB013314298007ULL, 
            0xFC68FB2477C94396ULL, 0x852415980E6C06E1ULL, 0xB675F92B06CE19E6ULL, 0xC3D0A4BAF567935BULL, 
            0x1CF6BA61FC8F10D0ULL, 0x99A0182ECBCF7E02ULL, 0xA05786CE3A0795E2ULL, 0xC20AEA2F72F267BFULL, 
            0x690C4520BA15B8EEULL, 0x9F238D69FB445496ULL, 0xB431C5ADE55BAAE0ULL, 0xAB0FB8D0410E6134ULL, 
            0x77C9B380ACE4019EULL, 0x11F1CBE1BA951B8EULL, 0x61C406DBEF6602D3ULL, 0xE0B8DF2139692539ULL, 
            0xEDFD21BDA472E9FCULL, 0xD5634140E0471183ULL, 0x050A47A77B9766A9ULL, 0x8A33D866930164B8ULL, 
            0xF7406544F803DE09ULL, 0x6769EF85A9899539ULL, 0xD03EB910A5D4B271ULL, 0xA1884AAD14E0433BULL, 
            0xA2D05124C5509A02ULL, 0xE6DA4DDD5FD6F9E5ULL, 0x043777B1AB081128ULL, 0xBF623A65164EF6CFULL
        },
        {
            0xCBD7A8BF8BAE2C46ULL, 0xFDC9D54A4CFB3CA5ULL, 0x4F7682875B71CFAFULL, 0x45E94600849C3915ULL, 
            0x726942349FFA2B0EULL, 0x5DBE7DEF92E4EFFDULL, 0xCD7312965AB2ED1EULL, 0x474C0EB5021D51F3ULL, 
            0x63D66EE11CC6F03CULL, 0x999E4BA8D181BB99ULL, 0x05436664B4AE355BULL, 0x66641716D9E722A1ULL, 
            0xD4B971C647EE6EFAULL, 0x7CED82153CB9F001ULL, 0x632F4BF96F556368ULL, 0xCCA566B22F7A0D17ULL, 
            0xAF0C37E9137A719FULL, 0xBB872D823D57D001ULL, 0x8512E128C912F562ULL, 0x0A0949BD4B9978C6ULL, 
            0x9ACCF11F1D4D53ABULL, 0xF63214B2980DC539ULL, 0x5EEB0C63F0A5C7A7ULL, 0x66C9AED1D56FDB32ULL, 
            0x68EC097A204F6B1AULL, 0x6A3A9BD1BCE2972FULL, 0x8EFAAF01AB381345ULL, 0x0153420702B4BA37ULL, 
            0xC902716B86CBE129ULL, 0x00BF424F6D78E093ULL, 0x9619C3FB0FC8342EULL, 0xCD4ED3CEF93AF1DEULL
        }
    },
    {
        {
            0x2147FA19CC251644ULL, 0x75F8C38D94E36150ULL, 0x95ECDA7C89357DC5ULL, 0x78D2D64920E20997ULL, 
            0x67340353B23CD90DULL, 0x25187252A3C59886ULL, 0x0FE02EFE28A07939ULL, 0x4A0E5AD9B639EB39ULL, 
            0x193E1DA3C6764F89ULL, 0x10E717A03DC76C82ULL, 0xA56EF00543E2ACA0ULL, 0x0815023A6C6F63BDULL, 
            0x04523447FFA9EB5BULL, 0xF478F16F038D041FULL, 0x42D1052FD401FB9AULL, 0x73C737993430C1A5ULL, 
            0xF458AFB8856DE0C9ULL, 0x94A376F6E9F83AAFULL, 0xFFCD4D80F4C26243ULL, 0x6887A1E57C9EFBB1ULL, 
            0xCAE07AB87F65922BULL, 0xC04E2A274CA2FDACULL, 0x05D4AFC177446F63ULL, 0x1A4643B6A4DE6B55ULL, 
            0x31ACA30FBAE243FEULL, 0x080823766D5B06F4ULL, 0xB3D2788EF0F45DAEULL, 0x8FF6A0EE07E64805ULL, 
            0x7132BE68F1553F5AULL, 0x135E4C55B0D5C8F5ULL, 0xCA08C08F33F318A0ULL, 0x89DC80159CD82708ULL
        },
        {
            0x17B92E78E62FE33AULL, 0x5B7E397B8A3445F3ULL, 0x802E260A68DE0990ULL, 0x9756D85F3A7561DFULL, 
            0xC6B517A23CE885ADULL, 0x0D8B3C803754E1EBULL, 0x523BC1FF0F6B14FEULL, 0xD3F2BB7392ADAC5AULL, 
            0x6C6B52BD423774CBULL, 0x8517A72D22BB2673ULL, 0x9295E0EEA3453FB2ULL, 0x9FBAC3245A0D1E7DULL, 
            0xEC3D1D6C5998BEA5ULL, 0x24849ABAB5E4E588ULL, 0x2FC76F5C99D08120ULL, 0x747399D66F6BAF98ULL, 
            0xD9A379AFE53F6327ULL, 0x61B775712AD4F41BULL, 0x196157B007C3B0E7ULL, 0x78FF73C670C22E37ULL, 
            0xAC2E41D182D3557AULL, 0xD2ECDE9087CAC617ULL, 0x566969EC72065590ULL, 0x1DECABD178AF585DULL, 
            0x2CF0E44AF3CAFDB2ULL, 0xCE34B37E5C865C63ULL, 0x4B266F1E1B4C244EULL, 0x37B656070C4A4A59ULL, 
            0x7A57B2D03A826578ULL, 0x740CB5223E8EDC04ULL, 0xE444F829D385F206ULL, 0x9DB502A0A824E9E7ULL
        },
        {
            0xE84EBD37146314EFULL, 0x3198176A5409A118ULL, 0xACC18C071E114E70ULL, 0xE5405C31C83311ACULL, 
            0x90E34C1FA00D81A6ULL, 0x74E8565CF3834517ULL, 0x0F86AFA03D421E38ULL, 0x7684BCE2F8172E65ULL, 
            0x0F38357496DB59D0ULL, 0xE8ED8D33684DAA58ULL, 0x27B5EFCB12323FE1ULL, 0xE011CE3A183FAE8AULL, 
            0xBA4CA5EFD1C752B2ULL, 0xBC40CA208B22583EULL, 0xF8D7150793867329ULL, 0xDB029B831C81D3C4ULL, 
            0xBAED441C40EC93C3ULL, 0x920D1D77D8B5A441ULL, 0xDD7584A1C432B713ULL, 0x1C3F8C8EED1227A9ULL, 
            0x5E64B05C581A883DULL, 0xA9D222A511C1C7DAULL, 0x84ED62FF2EE7DE2BULL, 0x55BAB829D3E5C53FULL, 
            0x6A63126BD5F88336ULL, 0xAD4119E6495454F0ULL, 0x6242F187A4B52F1EULL, 0x5B20EEFB345E5355ULL, 
            0xF0C965508C5B56C1ULL, 0xED0A30F280571234ULL, 0x15412D489DBB2E50ULL, 0x82DD71E7AE0647D7ULL
        },
        {
            0xB93C644F216AA47DULL, 0x5C3CAE35BAF38C2CULL, 0x1F4228ABCFE8B081ULL, 0x8127CE10F9811C3DULL, 
            0xAF58DD28BBBE6DEDULL, 0xF2C4F850086462DDULL, 0x0A913CD1DD73419EULL, 0x42F9FBD3DE8329D4ULL, 
            0x8715F5F6B0928B08ULL, 0x813E97B15BDBFAB6ULL, 0x78FD0CA6CC3163C2ULL, 0x8A5FAEE7AD06C2F6ULL, 
            0x7BACBD702AE0856CULL, 0x164386FFD1441307ULL, 0xA78F13A44AA3206FULL, 0x00D0926858015B2EULL, 
            0xB0A482E94B44DAB5ULL, 0xC0D993D576A58CDEULL, 0xE8E5FD0B39865AD5ULL, 0xD0D2E0680356B47FULL, 
            0xEE025D936B03DB6FULL, 0xBE0AA34424C03F6DULL, 0x41124ABB2D3F2FEBULL, 0x412320D9A1834B6CULL, 
            0xF49D5B5E0054BB06ULL, 0xB3AC3E57FC9B5215ULL, 0x90BE57322A7C0FA0ULL, 0xC71420C48995B5A1ULL, 
            0xCBFC72B05B4971E5ULL, 0x937895228690A99AULL, 0xEAE8A338822AFDE7ULL, 0x3E02050D8003CD04ULL
        },
        {
            0x0734F10DE84CB854ULL, 0x0CC0CED2535C4142ULL, 0x3A5A8F32DC3AFF85ULL, 0x6A1168B7931E26A6ULL, 
            0x7FDC696C1B1CC5F7ULL, 0x6906F4B8072020CDULL, 0x1AC49C5619041C68ULL, 0xC292B536E2CFE8C4ULL, 
            0x733EC767B5AC64ABULL, 0x94844365763B98AFULL, 0x59175C88201D7E3AULL, 0xE9E985EB50F68425ULL, 
            0x2FFBAE881301ED3AULL, 0x5BBFC97833A73B05ULL, 0x9C22B4B4796DFDF6ULL, 0x6262478605DD3E5AULL, 
            0x4B6706535EF8988AULL, 0x87F0BC71502E6997ULL, 0x9749BF99DE69A0F1ULL, 0x39E6F70A98892A3EULL, 
            0x4BADC1134DF1B929ULL, 0xF3DC1150AB30D9CEULL, 0xEFAF77920A397A42ULL, 0x447839D8CE650635ULL, 
            0x141EDFBB790ACE57ULL, 0x1A62527DE44A554EULL, 0x57D5968664171B06ULL, 0xF427B41F5B339631ULL, 
            0xC95E2154776A5D61ULL, 0x54E5CE28E051E9EEULL, 0x2E2932B9905672D3ULL, 0xD565FB44572EFDFCULL
        },
        {
            0x3F4D99833F14F8C6ULL, 0x1C8A97A804308F69ULL, 0x716CF91DFC8AE77AULL, 0xC30F750C8341128CULL, 
            0x75F83C439311463CULL, 0xD4D4972FF3FBA4C9ULL, 0x593AA0750712BF75ULL, 0x14464CED1E40243CULL, 
            0x62C4DC551AFEA5A7ULL, 0xD06486BF08180527ULL, 0x7994183DD49D885BULL, 0xF315EE89BD343ABAULL, 
            0xA6DA355C3605D770ULL, 0xCF0A30C073FC3D4EULL, 0xF778C1FD8A7CCBA7ULL, 0xFB6672DAD052C3BFULL, 
            0xF529C487ABB4DFF4ULL, 0xA2CAB3D32CFA2B44ULL, 0xE328D9B24F72437DULL, 0x97067B86BCDC2402ULL, 
            0xFBCA4A3ED2D0FE60ULL, 0x3DFA1FF68C187620ULL, 0x21D7A14A511798ACULL, 0x1C3914D0E0B17C40ULL, 
            0xA1BCD0DD062A627BULL, 0x49DC22AAC7968071ULL, 0x27FB8D43770EADE7ULL, 0x562CBFE5B8423755ULL, 
            0x20411BCA2FBDC16DULL, 0xC50A1E0BC1FE16BEULL, 0xFB09C9B30C7F4A79ULL, 0x4B8877818459765BULL
        }
    },
    {
        {
            0xC5E9DEB87E862D56ULL, 0xA7D91C22CE708114ULL, 0xD9E9569F8042A20CULL, 0xC027D824566A11A3ULL, 
            0xD7BA152B11EF238AULL, 0x969C48AA3DB98AE3ULL, 0xED0DDE6E83391F51ULL, 0x4D91B1B9BF147A09ULL, 
            0x8851B53878E4E5A3ULL, 0x14AC6DD7324FCC2FULL, 0x45F8F4D693EAEE58ULL, 0x3F13062DB471BA8AULL, 
            0xE07296AA8D07DB1EULL, 0xD26BF49CD4475037ULL, 0x03F5BF91A4EB7D1AULL, 0xD40259ED00A8244FULL, 
            0x01A80A52F266A951ULL, 0x0D3D6227A4A35E29ULL, 0x35EC32FF12B845F2ULL, 0xA57CF908AF22674AULL, 
            0x1D806758AEA41921ULL, 0x2F374C963F03D7CCULL, 0x29AAB82615DE12F7ULL, 0x45C4074138C2937AULL, 
            0x77D9E9D046FEE883ULL, 0x5A5FC72D92AF31BCULL, 0x44B936FA15820016ULL, 0xAE25B7F7E806DB18ULL, 
            0x39BC5EDD3E7D9887ULL, 0xA280B8F3A51B49C8ULL, 0x9FB075F18E90CD66ULL, 0x90AC2687CE17EEDDULL
        },
        {
            0xCE347FF96E80C860ULL, 0x914E082397C9DDBFULL, 0xDC0A9A1AEC2D5AC8ULL, 0x9269CC97A8C26D24ULL, 
            0x1AE09E32E18576E2ULL, 0xECB98F364C71D968ULL, 0xCB6B68B6DF7A25D3ULL, 0x20D50DA88D655F2CULL, 
            0x144898AB5D83BC36ULL, 0x15C538799EF303D1ULL, 0x9AA741B695443C3EULL, 0x39BBDECDD370B167ULL, 
            0x2440E62C73CDA649ULL, 0x2E895B9EADB64D8BULL, 0x073368A131320554ULL, 0x3F2579A15EA8CF6BULL, 
            0x04A9E21F497D9D87ULL, 0x2CC736F456AD27F8ULL, 0x2E5D7FC9D5181AAEULL, 0x06325E117CC9632DULL, 
            0x54C9AF35CB5FF51BULL, 0x1908A3E049F9E69DULL, 0x98EFBAD411E66ADDULL, 0x1C46270A1CEE28FEULL, 
            0xE1FA10D2C04D4A55ULL, 0x3A9E424E4F914FD6ULL, 0xBB0E1BD792BF87C3ULL, 0x54DBA6C73BE2ABCBULL, 
            0x7682217765E573FDULL, 0x05DC18190FCAFB25ULL, 0x55EBBB7FA9169919ULL, 0x99D28F5D9714A454ULL
        },
        {
            0x3316AA20AB779D95ULL, 0x8712A28070871EB9ULL, 0x6EA1A5B4815F51BBULL, 0xCAA644F63363768CULL, 
            0x77DFF9D7B1C055DCULL, 0x700CFEE07F9DB843ULL, 0x052780DC74418B6BULL, 0xB849C020E4DD0213ULL, 
            0xAD2485B456B3E2C9ULL, 0xEB8DFDBF06B67733ULL, 0xCC6C88193797B995ULL, 0xDA3FDE25ECECD571ULL, 
            0x87A9F41F6246A95BULL, 0x15CE4FAE815D7C9BULL, 0x78F7E9D34974C597ULL, 0xD77C626DE30D6347ULL, 
            0x547DE085CD0C3722ULL, 0xBF304626177A3D1EULL, 0x0A29B46F99BE7E33ULL, 0xE9F47732712E692DULL, 
            0x5523BDC3940551D7ULL, 0x7C00C08BB325351EULL, 0x14BA5A531636835CULL, 0x53384AECF33B6D8AULL, 
            0xC048325344924A51ULL, 0x5F4B8F4C98874D37ULL, 0x641F61D3F6E570FEULL, 0x747A1E7D658416ACULL, 
            0xEBD2564F076C2221ULL, 0xC671EAC2005992EEULL, 0x161BD217FA22E69EULL, 0xEDBDBA8DEBBA7F8BULL
        },
        {
            0x8245529434BF9016ULL, 0x2FCB90E31AD409A1ULL, 0xEC23B39A1A32F0F8ULL, 0xA5077098DC1C099EULL, 
            0x8EF917557B75C290ULL, 0x9342FF7E4D38C14DULL, 0xD9EB5C481A28E263ULL, 0x6BB6B98731608D34ULL, 
            0x02CF30ED1BA38F20ULL, 0xFD92F158B3B1B63AULL, 0xDC17794295CDFE1BULL, 0xB9E7A9357B6BEA70ULL, 
            0x8307696A661E49EBULL, 0x09133C136A3C960CULL, 0x6A6DDCB3CE652A1FULL, 0xC75CF25BF607BA9DULL, 
            0x4075AE46F0901E49ULL, 0x83ED1924F36CB1DEULL, 0xAD9156201A6CCF58ULL, 0x3CB1C6BCA09AB52EULL, 
            0xF39C8F0FE2803B3DULL, 0x1F427BF512522A35ULL, 0xADB20A428687A1C0ULL, 0xA6A2697BB97E345BULL, 
            0x829536BCA5C3D205ULL, 0x9F6FFD52D9CF2295ULL, 0x0359B19CAF747CDCULL, 0x36F9165F379A9972ULL, 
            0x5296AC61C3932F30ULL, 0x1F7C763553BCD02CULL, 0xB8BDF58D51E0C1C4ULL, 0xB21830D5F5B641A3ULL
        },
        {
            0x78F3BC21F45249A4ULL, 0x32EE4D99FD763769ULL, 0x643D79BC479DDC68ULL, 0x6652AE4EE6635643ULL, 
            0xA781AC2539381F4FULL, 0x63431080B2071728ULL, 0xFD72F1184D72AA6CULL, 0xA8778E544BF6DF8AULL, 
            0xD5EA3F6C17BE512DULL, 0xC6F8F1F23BA7D204ULL, 0x73B36B4523366943ULL, 0x62F1DBED9E2769D2ULL, 
            0x330DD41D3D4563EEULL, 0xE84DC2A43E43882BULL, 0x7ECD003306B42DC2ULL, 0x316AD225EF132ABDULL, 
            0x265B84F6119BF1C2ULL, 0x1E1ED444FF1E6C77ULL, 0xC943871395794EF8ULL, 0x901F5B8A5C69BFCBULL, 
            0x677394478DD639BCULL, 0x3AC8B17D9BB706ECULL, 0xC082ADBB916E3AE9ULL, 0xEC60603AE46A7E85ULL, 
            0x3D073A2AC64ED2E4ULL, 0xBCCDE67A5AD1C350ULL, 0x199EEF24612D7F76ULL, 0xC631A3D0984AA795ULL, 
            0xD554697D15009DB5ULL, 0x233DF2CEC75601A6ULL, 0x171D4416945E2FB6ULL, 0x50E50661D9077A41ULL
        },
        {
            0xFB98950B74EA3842ULL, 0x7E11F2EB1165E1DAULL, 0xC6510FBC9431FA86ULL, 0x99649DAE3A9B295FULL, 
            0xB3BC2A01BAEDE4B6ULL, 0x34959BFDBA09BFC0ULL, 0x7BB9114A0D8DD916ULL, 0x8AABFC592C3BB4D0ULL, 
            0x008AF486EFFD1422ULL, 0xB2E9AD61598E0903ULL, 0xC126E6AECD5CFCC3ULL, 0x8F8DD4A935A0A9A3ULL, 
            0xEAA15BFFD8DAFD76ULL, 0x2F92244297269101ULL, 0xBC8783DD7DCFAC46ULL, 0x2BDB1A6BEEB3FE97ULL, 
            0xA320B24EDE8269A4ULL, 0x421523ED6C526F4DULL, 0x4493247A4871F6BBULL, 0x9FCA4DFB6977D457ULL, 
            0xDFD3137239340517ULL, 0xE565CD76BD8A0725ULL, 0xE1D526AE9C833C58ULL, 0x6626E4057FF6DD57ULL, 
            0x642016DA4E930834ULL, 0x19881D0A6ADB6CB4ULL, 0xD66425957BFE7032ULL, 0x5369C11E1366E4DCULL, 
            0xC0B23FDD08E628E2ULL, 0x34997D076D93F359ULL, 0x1628C1ADA84B5394ULL, 0x192A5FFA56F59ABFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseDConstants = {
    0x4A6A9215D9630E9FULL,
    0x42F0A2DB484055C1ULL,
    0xD9F7D17550AE9550ULL,
    0x4A6A9215D9630E9FULL,
    0x42F0A2DB484055C1ULL,
    0xD9F7D17550AE9550ULL,
    0x1C8691D966FD42D8ULL,
    0xF4DADFE414684634ULL,
    0x14,
    0x3F,
    0x1B,
    0x7C,
    0x83,
    0x66,
    0xC4,
    0xAD
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseESalts = {
    {
        {
            0x0242C30F2DDCEF59ULL, 0xCC84744C8BC44DC1ULL, 0x9605B8ECAE494B3AULL, 0x1918F3FF3AADA36FULL, 
            0xC8BFCB72E9B981A7ULL, 0x3D5F7934696C2613ULL, 0x1CC06387F1FBA621ULL, 0xEFCB29E59A536450ULL, 
            0x5E377F85D1082071ULL, 0x16B9029152AB6FE4ULL, 0xE2D898F9DA4CA4B1ULL, 0x53F784F343FE5E22ULL, 
            0x5D608E3B14560BACULL, 0xACFBF26ABC8277FEULL, 0x94F612532C39CB1DULL, 0x13DFB658A772E6EDULL, 
            0xF2436D206A9D7F01ULL, 0xEF20BB22E3B5984DULL, 0xAE9070EB5F81CD6DULL, 0x7E2631D0EE576744ULL, 
            0xE03B533354E2FE91ULL, 0x7D73E6B1F654F7B3ULL, 0x95DE9977F9624FC4ULL, 0x6515829A9A7A1279ULL, 
            0x8A306A597B25EC09ULL, 0xA839228F20CA6541ULL, 0xCD0A9BE407D95242ULL, 0x1EFDDA54835E9C9FULL, 
            0x70789E237C18A79CULL, 0x7B328F8A0335F28FULL, 0xFD888FB138757DEEULL, 0x7CDC404FF1045454ULL
        },
        {
            0x52B6B41031D2326EULL, 0xA380E7E7EEF41FFBULL, 0x602B109E26516202ULL, 0x9A6766CBB2E5C8CBULL, 
            0xDE7B0EFB069CDEC9ULL, 0xAA1127A3565936A5ULL, 0x5F23B00378C1967AULL, 0x551D8342D195ABBEULL, 
            0xE45CFC6123230026ULL, 0x9DBE33BE2AC28A38ULL, 0xE7EF8E3C925B08A0ULL, 0x10E1762E894EBB1BULL, 
            0xF31E04EB1684A856ULL, 0xBC13F5E6E47CE63CULL, 0x03556DEE2C11FB17ULL, 0x085A094099E3FC64ULL, 
            0x27110C2352A104B6ULL, 0x181415114401995BULL, 0x153317E2926B2EB3ULL, 0x61988B9125228EB4ULL, 
            0x805B7A897F8D0CCEULL, 0x12DF619FDCA29D5FULL, 0xFDABC58C7A73C288ULL, 0xBC71D780CCC56BCEULL, 
            0xFA62574E8A4A2C3EULL, 0x6EF662E408240F25ULL, 0xAF268BB58C28E53CULL, 0x13FAAD60C5999459ULL, 
            0x31A82253E0604707ULL, 0xCA4597E08456DEF7ULL, 0x8B2A9FB8D1A8B8AFULL, 0x7A6D6D6AE08F63B0ULL
        },
        {
            0xEED0F39029D72979ULL, 0x155233DB21CF58B9ULL, 0x2D8215A2E18D5F30ULL, 0x0BC4BD7C9889FE89ULL, 
            0xE85A152826860C41ULL, 0x6AD55D8A5EF779DBULL, 0x9C8752FEA421F216ULL, 0x03241A4B205EB7E1ULL, 
            0xE88C181400C2CBAAULL, 0xB89CA4EB5F6CE2F1ULL, 0x46227D764140CB6EULL, 0x966654C62B21CF92ULL, 
            0x7DE3C8543B498F35ULL, 0xEFB34DA11618ED65ULL, 0x138F77612BD5CE93ULL, 0xFDF696F461285644ULL, 
            0x112C45DF38AA28A0ULL, 0xFA308D6F2F3FC56CULL, 0x1BA1F3FD980C5089ULL, 0x687A3D380BAD257FULL, 
            0xC13CA8ABD7CBB215ULL, 0x8915F16BE74DA3C5ULL, 0x5D836F274F91384AULL, 0xA4D7870C5F889DC6ULL, 
            0xE15D741F691B38D8ULL, 0x0256A8D7B2B726DAULL, 0x3A37236CE8788A06ULL, 0x166824D4596A77B8ULL, 
            0xB786FADA162B9EA7ULL, 0x036C5A1FCA324C90ULL, 0x687043C2B8FE3F95ULL, 0x33A4886B496513DEULL
        },
        {
            0x6ADB86DF34239434ULL, 0x45B9EFA0C8DF44C0ULL, 0x1F9815819F89701FULL, 0xD8030B71419F3806ULL, 
            0xBF1E737DBCA88257ULL, 0xD2D6C85F4BCBA3BAULL, 0xC2D22AB774EF7B47ULL, 0x659F2724B889FA65ULL, 
            0x93D62427D7506C3FULL, 0xB1EE85449B43F661ULL, 0xFCE5AAD5BBCEA92EULL, 0x49CAF9FE8AFEA76BULL, 
            0xA7FF46510085D9E4ULL, 0x79D3C72B51F8B52FULL, 0x6DEE5AA9F4611931ULL, 0x20E429870E83785FULL, 
            0xF782DC287B8FFDE9ULL, 0x241BF0FB87239097ULL, 0x0AE37F78B32DBDA2ULL, 0xF2D53C02018D7E19ULL, 
            0x5F8253D328124B11ULL, 0x9FC2B706F37ECC93ULL, 0x27B7514006680F60ULL, 0x0E33C44BD30B7C14ULL, 
            0x3EA1F65AD4455BDBULL, 0x537C277904CB29C2ULL, 0x6136F9F468E7F37CULL, 0xBDF639C09C920B17ULL, 
            0x1F23E9CB04752A96ULL, 0x1CB25BBFD6A4E9A0ULL, 0x8686E6061450DF8CULL, 0x04510AA2FA469E16ULL
        },
        {
            0xA5E7A40208B8103DULL, 0x49161333966E203BULL, 0x82C3290570E5868CULL, 0x0A87006D29026767ULL, 
            0xE13C0BCEBBF4BBD0ULL, 0x9E3C4E46409109ECULL, 0x7E09B2DC9EE07BAEULL, 0xA5ACBB960BBDC61EULL, 
            0x40093C70B7F754BFULL, 0x7ECF92AEA7845D10ULL, 0xF0A6756C29DC5F84ULL, 0x7BB7726970F6AE64ULL, 
            0x6D609C405A36C2FFULL, 0xAF1EE2E7807DE907ULL, 0x607C64C06BF05309ULL, 0xC195310E108EC979ULL, 
            0xDAE8A61396DE2272ULL, 0x5F0012B4A379225DULL, 0xA8FB72B84B59CE63ULL, 0xBB935034AE6F253FULL, 
            0xA5F6D8078C516661ULL, 0xD7D5CF404FA87B98ULL, 0x17850FAA82D94928ULL, 0x6E3E3737932447E4ULL, 
            0x50384FB3C6428920ULL, 0x9FF44843C4A54A40ULL, 0x707A775858B76C71ULL, 0x13B82A774A656A42ULL, 
            0x1521766A0BC078FAULL, 0x9BB9744BAF61E9ADULL, 0x6F915F386C2235E5ULL, 0xACE52F2E24DE40D0ULL
        },
        {
            0x01DE76B83A4BFC72ULL, 0xFD20D3A1479802D4ULL, 0x3E0FB233131856FFULL, 0x13E136A2DABBAA80ULL, 
            0xC3E8E1D25637B89DULL, 0x6E625943F46CFC8DULL, 0x060D3FF02B6E19C6ULL, 0x37B1327209871588ULL, 
            0x8BE9DC55FF2654A3ULL, 0xC757CCAE6DFFC1EBULL, 0xC0D48D4881945D29ULL, 0x493DB9B7084C18FBULL, 
            0x05B9E13B1FF2239CULL, 0x6FFDFC6D6B57244AULL, 0x8B5E0EA67DA4702AULL, 0x508B1AF67E6845E3ULL, 
            0xF11C722BF0B4A101ULL, 0x5F92142CA874E1CBULL, 0x45C9034D7593BD22ULL, 0xE6696C37C8AEABF3ULL, 
            0x1FC038C59A8522B3ULL, 0xCC1732F92FF4C012ULL, 0x10CABAAC5E6D9F67ULL, 0x37F19B66EAE0FE37ULL, 
            0xDA48A73493546AA9ULL, 0x4222565301681821ULL, 0x549459EC03A48F21ULL, 0xFA48ED22E8F16ADAULL, 
            0x87C6D232984E8A30ULL, 0x266EE2FFC6526D8FULL, 0x6A727CB1B7B93AD9ULL, 0x419EF248A5EB05B1ULL
        }
    },
    {
        {
            0xBE159630E7953862ULL, 0x452A218F49C7A25BULL, 0x1A00328EFEF9CA4AULL, 0xB85816764C779B00ULL, 
            0xBC90B7B2DE3C85DAULL, 0x3FF89822ED7D4224ULL, 0x2BB6FD6F323F6F2DULL, 0x75503BDA6FFFD17FULL, 
            0xE53DA471CAB0B690ULL, 0x856B61EB49B8C24AULL, 0xB02FE9FB9B14BAE6ULL, 0x33A436DF9CF16668ULL, 
            0x59A3C419E5E23651ULL, 0x1D0CD8961AE3BB1AULL, 0x66BC4C6E125FAE5CULL, 0x50E323ECB894F2C4ULL, 
            0xB2C8B5D6B9508C12ULL, 0x86DE9263F5408491ULL, 0x166F599E210AEEE8ULL, 0xE7FB011B2A9EB5C1ULL, 
            0xAADE865E50344C18ULL, 0x1B734870EE1C2C41ULL, 0xD7E4C7048D5F0087ULL, 0xEE8706982BA564ECULL, 
            0xC964C8772BA99484ULL, 0xEDAD82027AF4C80CULL, 0xB4867FDA3398B4E4ULL, 0x639FE41BF9590E8FULL, 
            0x4AA12E158D7BF6F4ULL, 0xF9D5CA9DB9355B49ULL, 0x9F23EA035A571B08ULL, 0x456AFA2954294300ULL
        },
        {
            0x4C4E83D19E522EEEULL, 0x3884CB46AEA3B5CFULL, 0x42E6973666B6DE40ULL, 0xD88BCB6027A18773ULL, 
            0x48AACDCB78A1518AULL, 0xC9D49392D978E145ULL, 0xB82E0DBCA7DB8FF7ULL, 0x8D77BD8473A118B0ULL, 
            0xAD834CEC8E21B623ULL, 0x38CB87ED3763310AULL, 0x6B2C58ADFA04C0B2ULL, 0xCE29F4958BFB8F70ULL, 
            0xBAF68C5E6E235EF7ULL, 0xC4823C76BB67A71DULL, 0x80F2AD47048A2593ULL, 0x81A0FE2232926B8EULL, 
            0xE39DCBA23CD07214ULL, 0xF860367E8D9B7A3CULL, 0xF18950CCC05556A5ULL, 0xD587562623A0C3E7ULL, 
            0x064DD001EDC522D2ULL, 0xA8B61F675E1F93FEULL, 0x15ECAF8B8532E8E7ULL, 0xD45F48A35DAA0976ULL, 
            0x941FBD54A37E65BCULL, 0x11721ADDF48F9B19ULL, 0x0F2FEF8321398B96ULL, 0x0651ECAA5C1406F3ULL, 
            0xCDED3186AA145E29ULL, 0x3D3822A305DBBEE3ULL, 0x394AA9C0E203146FULL, 0x905A0A388A32FA77ULL
        },
        {
            0x61659C1D37216A86ULL, 0x69216B553B481099ULL, 0x3E4767B0353B9FE3ULL, 0x1E554BF5EA258EC2ULL, 
            0x922016E5024D9016ULL, 0xA2287318409BBB70ULL, 0x1DDB5D81F52FFD39ULL, 0x26C41BBBD5E96B0EULL, 
            0x2B73F0E9F33C2B1FULL, 0xC167B3C1EF36B045ULL, 0x076C1F76CDF95B03ULL, 0xB3195CFE03B595CFULL, 
            0x4AE236C138B17163ULL, 0x6C97D3496765162AULL, 0xCB769A836BE70211ULL, 0x7E788AF3CA21AA53ULL, 
            0x805D31087FE80DC3ULL, 0x6B682F208B4EA42EULL, 0x4786817615D23640ULL, 0x1DD5ECEF1A1DF019ULL, 
            0x29E75BC2B0406FE6ULL, 0x79D901E98B1BF1CFULL, 0xE31FF92B069538ECULL, 0x97A296E63B14DC33ULL, 
            0x2740D10D23EE440FULL, 0xAC383A1B7D942364ULL, 0xB3660AEE74458C89ULL, 0xF3A868741849E6A2ULL, 
            0x5CF21430E098B7F4ULL, 0x2A96DA4056E6567DULL, 0x32348E6624692CA8ULL, 0x70E698994F7A9CDDULL
        },
        {
            0xBF2A70B73B05C760ULL, 0xED8CF6554F33199AULL, 0xF4BD8046BF6A85FCULL, 0xA572BACD1789FE0BULL, 
            0x52B4C569E4DFDE7EULL, 0x9DFEDD6237E41987ULL, 0xA96D22E75A0EA50FULL, 0xF3BB04957A56859CULL, 
            0x6395134B8AB59F0BULL, 0xECB7FB93DF2914AFULL, 0x7586880775D37E4FULL, 0x96AA25264700C486ULL, 
            0xA6BE01908FB96F36ULL, 0xC1CCD46046612A14ULL, 0x666F57D420DCBE84ULL, 0xAFA8416256195C7AULL, 
            0x39E49EB0F1E7F77FULL, 0xB264920608535601ULL, 0x2DB2AB7993E301E0ULL, 0x8B92E224DBD02E53ULL, 
            0xBF370D9594074FE6ULL, 0x6A878CB1EDD04B88ULL, 0xDDB8A4B3562882D4ULL, 0x263BE515B25E39C9ULL, 
            0x427CE64137F0EA29ULL, 0x9E46998E3257E5FFULL, 0x7A3B1543CCEF8AC7ULL, 0x2B5BC30D8BA78102ULL, 
            0x1527F898A4806AA6ULL, 0x4C7427B1BAF4FCD2ULL, 0xC86521F4D14615C7ULL, 0x8E5AE9B0242D0C69ULL
        },
        {
            0x74E0008EA2162A8BULL, 0x7A68C41F2DB9F3E4ULL, 0x28AB9085264E675EULL, 0x68A9B4EF45F1341AULL, 
            0x2EB6C0D3D6585961ULL, 0x8CE5565C2446FBFDULL, 0x33A721713EF9B5C6ULL, 0x0E8637C0A263C10AULL, 
            0x2B143BB0D2DC2DA5ULL, 0x9FC079DA7013BCABULL, 0x87511D049D560844ULL, 0xA7F294132D982951ULL, 
            0x38AEAEC15DD7D360ULL, 0xC8EED79CB5A2606FULL, 0x402B6795B8A281DDULL, 0x52C37FF795312A14ULL, 
            0x14C319B81B33D210ULL, 0x6D6DA0EB32F6406FULL, 0x2D91B1418945A5D4ULL, 0xCF879E3D00E751E8ULL, 
            0x7CAD904C7A58C484ULL, 0x795688B71402C9FEULL, 0x042A97ECFAC04A47ULL, 0x1866763C16F09B50ULL, 
            0x3CF5362AB4E9B4F6ULL, 0x14A271D9B5008A48ULL, 0xD1FFBF11FA078F77ULL, 0x54524D578C3C2CCAULL, 
            0x7A7F17D6AC7E7B94ULL, 0xD04F6AEE7B44AFABULL, 0x5D04AB4964850271ULL, 0x86F338A88A95D4D5ULL
        },
        {
            0x0BA9982FA3D7993CULL, 0x6C42B542912B64E8ULL, 0x3BF1598E053878A4ULL, 0x33EDC6C4E9710A23ULL, 
            0xB1BCFE04CA91AD21ULL, 0x0AD6692E85D6D934ULL, 0x5773803CDE7F2FB5ULL, 0xE8EB42B21B5F51EBULL, 
            0x05B56F93653E3A9BULL, 0x96379F5C3629C15DULL, 0xEB40A656D9CBACAEULL, 0xC8DF628F123A818AULL, 
            0xA590386EF5B99D53ULL, 0xE3D23D9BBBAB1246ULL, 0x3E14D11172D4D8D5ULL, 0x5DAF97466A5810EFULL, 
            0xD0328BD167D0EB8EULL, 0x8BB7A46BD02869EEULL, 0x652391B6BC196DE2ULL, 0x0EF4189081BE3957ULL, 
            0x6E7B426980C51087ULL, 0xA8759B63E89DBFD3ULL, 0x7774A82160027BEFULL, 0x3C73D3BC9B97B6DBULL, 
            0x696F6F1993C43893ULL, 0x8AEE5FA3DACF606FULL, 0x4C8D44C8D47BD536ULL, 0x68FAD7EDB42BBE25ULL, 
            0xB651C99BEF9C3BE1ULL, 0x2E14D1B93E42FE7AULL, 0x9BE0AA4C62A85723ULL, 0xBA3AE38B3E969199ULL
        }
    },
    {
        {
            0x7FAC6E7DDD1FF6E0ULL, 0xE5468CB4C424028DULL, 0x84A4CCD8F47827FBULL, 0xC4848FF361D0721DULL, 
            0x6DB4626B965C8A83ULL, 0xF01BD7FD524444F5ULL, 0x09EE4DA69901F044ULL, 0x0DB699C9671648C6ULL, 
            0x19DD362CB8932242ULL, 0x9303E1246BA97818ULL, 0x351A5777E264AD1CULL, 0x285E1CE3FDEC59AEULL, 
            0x1E0642341B4416DAULL, 0xE2E578A2F109B416ULL, 0xE7DE442F47C89259ULL, 0xC3BAAA967BF889ADULL, 
            0x6066EEBE0D1260F5ULL, 0x51F3F1C5FFEB6C9CULL, 0x729E3934A80B0133ULL, 0xC84FA4D31C0ABCD8ULL, 
            0x68157A2AC82932C3ULL, 0x9813013E8AA8C196ULL, 0x91B6C64AA11D0B99ULL, 0xBB503999482081BCULL, 
            0x94297CC4C918ED52ULL, 0x55AA643F080A98DBULL, 0x487FEC8AA99651D2ULL, 0x40A042D28EFA3AA7ULL, 
            0xCA5D21AA33194E2AULL, 0xD1B92B047C6F63F9ULL, 0x039924F497104353ULL, 0xCDCED3911C4AA19BULL
        },
        {
            0x9189CAF5E310367CULL, 0x3748DB99A3A30310ULL, 0x1F5C27CDED4CBFD2ULL, 0x322FD53863285AFBULL, 
            0x6ACB6CB8CF6EACE6ULL, 0x1476AD74309DD75FULL, 0xC65476D721CC39F4ULL, 0x2B8477CCF68A187BULL, 
            0xDCF191AE173F9179ULL, 0x06635D41435B3B73ULL, 0x7537DBFE9E6709ECULL, 0x6034097B0FF9D9ECULL, 
            0x38B0609EFED22994ULL, 0x08487180EC3DAFE1ULL, 0xE1403DE8EDEE1791ULL, 0x3AABD85DEBE487A9ULL, 
            0x21030D1467B2C763ULL, 0xCE41AD6B660A8CB8ULL, 0xDCB43A740C4FF6B3ULL, 0x06C5F7D684A6A716ULL, 
            0x9AFB32A3502DE10FULL, 0xF80F7C32A4F4F776ULL, 0xD90B6DEC1C75DB13ULL, 0xAFB1E1905B78D10BULL, 
            0x32004F3C03BDCC7AULL, 0x3B8511888D7EA535ULL, 0xA8E27631BB5A75BAULL, 0xE0FBD9263DF2F776ULL, 
            0xA739726E1F827672ULL, 0xF9236C11727B2441ULL, 0x5BD1930974115E2CULL, 0x3AD6A3B5C624B4D2ULL
        },
        {
            0x4A727D1C81D897CCULL, 0x0592E75F552056E1ULL, 0xD87BEC9A28782318ULL, 0x648D0BE8F237AC15ULL, 
            0xCA633FDCFB1565BAULL, 0xC41BC21C19A62BDFULL, 0x785DF7AF04A1B8E3ULL, 0x93108F223BEFA44EULL, 
            0x392DB6F7A8C29C36ULL, 0x52383E5139883E59ULL, 0x358512ABDB23EEDBULL, 0x36F3BAB4FDAA09F5ULL, 
            0xAE6845A95E42864DULL, 0x6B0913D8953108B7ULL, 0x904A680958171FD7ULL, 0xE28EDAB071759723ULL, 
            0xCDD080CD206E43CCULL, 0xBF879FAAB03BA68AULL, 0xF4F3BAA61FB76730ULL, 0x24E2579702543BDCULL, 
            0xD33A14586C46F907ULL, 0x5143B8F1ED4C84F2ULL, 0xBF2AF160A4BCCDA1ULL, 0xC4AEB23BEE4E131FULL, 
            0x3D92E81D9EE853DCULL, 0x8D949B51BABBB055ULL, 0x9EF000C29733C167ULL, 0xC5D3D5631362C5F0ULL, 
            0xC31D6D951253DC1FULL, 0xFF8DC0320AD143B2ULL, 0x0830FA3E3E745B40ULL, 0x705F7D761E754BC4ULL
        },
        {
            0xB81CD2E2B6B9CDDAULL, 0xB585A3E32FC4F051ULL, 0xFB38297F19EAB6B6ULL, 0xD749041A89207B0CULL, 
            0x81A0CB65BE78F7E7ULL, 0xABE0C84E286CF198ULL, 0x77DA6FA469CA9C20ULL, 0x0931FFBD3F2D3886ULL, 
            0x9ED6F41EABC793B1ULL, 0xCC472AA9BC62C1A3ULL, 0x72DBE4593D04FFC9ULL, 0x627919530CDBDC33ULL, 
            0x1EDAD74DF8F2F7BAULL, 0xD18814A868F56660ULL, 0x9EDD10092EEBF852ULL, 0x3DB4235588E36A3AULL, 
            0x0EFD1FDD4E9BAF61ULL, 0x49EF0ADEDA135FE6ULL, 0x835C45E1F990700CULL, 0x9708B7EEC1846AFDULL, 
            0xC9D485CFF259F602ULL, 0x62BF55B956EC9255ULL, 0x42AC7631A83A9415ULL, 0xF5E6A4AFF300621DULL, 
            0x8332226C08088DABULL, 0xD602F76B77B556E7ULL, 0x90301630FD6F481BULL, 0xCE7D56BFEF5609A3ULL, 
            0xC04E3C88223DBC61ULL, 0xE1E8F550749CEEABULL, 0x76BE7A2333657C0CULL, 0xD871A5EDDB7404A1ULL
        },
        {
            0xA4D5D4E7B9B0FDA8ULL, 0xF808D133709FFF0DULL, 0x89FD801830B53403ULL, 0x6DFF15820106B52CULL, 
            0xF45EB76A39A01D3DULL, 0x92FDE7D0895B5CB2ULL, 0x2FFC1AEB8F36F471ULL, 0x5773DA035FBBBF3AULL, 
            0xD5E5A2C10F987BE8ULL, 0x90E677D0704754FAULL, 0xE5B6860ADF37EE11ULL, 0x6A69181B662B5BB4ULL, 
            0x0694DB0D64908C89ULL, 0x90464C67D59219B3ULL, 0x12462320458E7E3BULL, 0xFA64F140A8A53C73ULL, 
            0x151DF367A183486CULL, 0x9509ECDC902691DFULL, 0x1EE7BD7E1A9C47E1ULL, 0x216B7A9466F95218ULL, 
            0xA195F65E0DF4C574ULL, 0x0306A7E7C71CE38CULL, 0xB427158625BC4639ULL, 0x59EB1D3FA9CD129CULL, 
            0x19E28ED7ED142B0BULL, 0x12E2C59EAEECB5FDULL, 0x8C76806441D2252BULL, 0x38146BF396F80E44ULL, 
            0x996012C59872411BULL, 0xF4EEBC2603FBD464ULL, 0x50D606F6A903783CULL, 0x834029F8232DC3B4ULL
        },
        {
            0x2772DC2D3905A46FULL, 0x7EBA24E7982A4429ULL, 0x5105F8D2430AACEDULL, 0x31D98FF4189CB58FULL, 
            0xD9F16BA718751AFCULL, 0xA481A2BD033EC7CCULL, 0xBCE0D7C408F987E1ULL, 0x175243AEADE19AF3ULL, 
            0x0A6EBB5A1C6D3B11ULL, 0x7FB2749FAA504AE3ULL, 0x4B895462CE4EEFC0ULL, 0xDDFB53B511737FD9ULL, 
            0xF5C896D94E2C3DEFULL, 0x74F18D3743B3CE93ULL, 0x14ACB6E161391F6EULL, 0x7AB280B019F48BB3ULL, 
            0xC65687A3993AB196ULL, 0x808DA4D85EEA7AD7ULL, 0x104A7B1858B903E8ULL, 0xCE14157FCEE5776FULL, 
            0x8242762739BC014AULL, 0xDE2D4607144BA1F7ULL, 0x74EBC770CF8596C2ULL, 0x145000010E1C606BULL, 
            0x562D1DA7F8063A45ULL, 0xD2A6E8CCC6FB5710ULL, 0x5FE2E31620FDEC4FULL, 0x8253085B97E9E9FAULL, 
            0xC7536DBE9FDB7015ULL, 0x555F194D53E8301FULL, 0xB873E7A308F7F7A3ULL, 0xE423D28EE4D7601AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseEConstants = {
    0x395876FA363CF0A9ULL,
    0xEF549895438E8D84ULL,
    0xB4CA011B731901BCULL,
    0x395876FA363CF0A9ULL,
    0xEF549895438E8D84ULL,
    0xB4CA011B731901BCULL,
    0x6C8DAA661E4D1E62ULL,
    0x839EDECA02204D0BULL,
    0xD1,
    0x94,
    0x39,
    0x71,
    0x90,
    0xEF,
    0x67,
    0x6D
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseFSalts = {
    {
        {
            0x44C3C0A2FDEC5F1BULL, 0xBD19D67E81C94822ULL, 0xABA137FD05F9B983ULL, 0x7B63B60F6E837EAEULL, 
            0x09EF802C25F64E86ULL, 0x770B3FE126ACD36BULL, 0x9DA5309FF072D8D1ULL, 0x4037ED2ED9117515ULL, 
            0xF8BEA2C7188476E9ULL, 0x435A65D5B5A04B6EULL, 0xB4D8E1940420F3E5ULL, 0x8D4FDB658C3F8802ULL, 
            0xAF73DB3CFB251FD3ULL, 0x0712BF65CE35551AULL, 0xEDDC38082CA0A373ULL, 0xBD97D8B977EADCC4ULL, 
            0x6F2FD5B78686DE16ULL, 0x1E239BD4DC7DC8BBULL, 0x3FA720BFB409CE33ULL, 0xBD089FAF40EB890BULL, 
            0x2259B79F67D60853ULL, 0x075EC034FE16CE7CULL, 0x9E68026052215920ULL, 0xE4B75E8C1F303A91ULL, 
            0x35C568A64E40ABABULL, 0xE8656688DC987223ULL, 0xE48DD2BAF18405C3ULL, 0x731E73CE5F947F62ULL, 
            0x073325FC98B02A69ULL, 0x94F3698BBBD19A89ULL, 0xC9FA1E1F46156808ULL, 0xE9EB90CCBCEF49FEULL
        },
        {
            0xCC331FCDF9076090ULL, 0x7770CD75F300DC73ULL, 0x2536C10C5BBB17E1ULL, 0x1DD1E9B3B88F1D9CULL, 
            0x5C67DBDB595FC8A2ULL, 0x7093FB65A8A50D81ULL, 0x50C1E78BAA2D9237ULL, 0x21218629D3116006ULL, 
            0x336DFC14EAC61E7CULL, 0x178F20A3A8BE4022ULL, 0xB824C9DC207F0B8DULL, 0x044BF5403494B3D3ULL, 
            0xD65CA6BC2E62F4EDULL, 0x40A62AC62101618AULL, 0xC3848E0C72317645ULL, 0x0FC6F8F609FF0596ULL, 
            0x52304E0EB0ED133EULL, 0x28019D74BAA322FEULL, 0x5BA8004205E8255DULL, 0x108C9ABC38F71D7EULL, 
            0x9B60B3D34DEBA4C6ULL, 0x1985DF7FE4FFA341ULL, 0xACCF8467651EC961ULL, 0xCB2A142331A3EB20ULL, 
            0xA1E9FAF8D95AC57CULL, 0x22FD12FBD25BB61BULL, 0xA059EC49BE0E17FEULL, 0xDC5A124074B9A2BBULL, 
            0x5DC448DBCF8A8594ULL, 0x41D62654F987A7E9ULL, 0x30331C253CF2A066ULL, 0xCD7F04E37F94A873ULL
        },
        {
            0xBF729C91483FDF18ULL, 0x32F130B5BDF0D78EULL, 0x8AC0D11ED6EF28FFULL, 0xC9B51DCBA5A6A903ULL, 
            0xF017EF33A06E841AULL, 0x204D69CEFAAD9CB8ULL, 0xAE97E0A04CCD01C5ULL, 0x5553B9B311050B50ULL, 
            0x433711D1F7578514ULL, 0x7C4C4B4037A87F10ULL, 0xA734098EB8834A69ULL, 0x6401C6363BC3FE03ULL, 
            0xC460D1CE763F8B8DULL, 0xD1480B55F3EE51D5ULL, 0x8B5DD3826461C3F3ULL, 0x70CB49A2FEA791F8ULL, 
            0x589A36FB0635B5C1ULL, 0xD6A212E366D698B2ULL, 0x7D1ECED381218058ULL, 0x04F999C4B534D8A0ULL, 
            0x09164D1F5838AF8EULL, 0x5D016C844213E8ADULL, 0x8E19DAF49F7F1319ULL, 0x8454BF69096D751DULL, 
            0x73B4C0A1B7A4E4ECULL, 0xD4078B13C89C1644ULL, 0xD38D522992CA8A3EULL, 0x1499F4C8FE588713ULL, 
            0x98CD92EE1CA61A93ULL, 0x65E95796E3751C1BULL, 0xF75516F6191F99CDULL, 0x53351657DA499FFAULL
        },
        {
            0x781F0093A42AB1BDULL, 0xD8A4118473FDBDF4ULL, 0xFEB63BB9ECD4FE30ULL, 0x09A1AFA9A0078828ULL, 
            0x9E8DF5312969CFFAULL, 0x41D6E639CABC2917ULL, 0x721C9B8B194291C0ULL, 0x864F77F1623BFE76ULL, 
            0x5CAC2FDE74B1DF09ULL, 0x602C5A61AE55F376ULL, 0x9BFED77F1B4BB0BDULL, 0xFE61FAEE31477528ULL, 
            0x490F523D03676D16ULL, 0x905E14B604FC18E2ULL, 0x6FD235FBF4EBD8C3ULL, 0x312A358327B60D43ULL, 
            0x0B0B4990E5541B67ULL, 0x1E74F6E16F987A53ULL, 0x900DF6E7D6E09431ULL, 0x151D195095A037FDULL, 
            0x41A3CE9C9284136FULL, 0x44C796B4598E767BULL, 0x941EC123FBB537DEULL, 0x4716904E478AA925ULL, 
            0xEB43DF23B1A3080FULL, 0xC303F887071F9892ULL, 0x1D67029CD7644CE9ULL, 0xE0002BA06F629D3DULL, 
            0xE9326609960E8B34ULL, 0x36C3E7533033CD4AULL, 0x773C3E2C5155AEDFULL, 0x299D5166E0AAD793ULL
        },
        {
            0xC6E2A773FE5A712AULL, 0x28AFC697145D98D7ULL, 0x31C36C60F77BA01BULL, 0xADA7ED6329B11DF4ULL, 
            0x00A36EEA4E82A0C3ULL, 0x732BC22B6D07820CULL, 0xC07DE5ED310C7943ULL, 0x92189E1CA21BC970ULL, 
            0x6BD7A40D56781901ULL, 0x3078EAE6A90EA743ULL, 0x6AB48B012F927ECAULL, 0x30A1A7503866DA6AULL, 
            0xC4B8CFDB8A61700BULL, 0x13BE23BDC013954AULL, 0xAE6F15F055362A28ULL, 0x1B08A7967EC29B70ULL, 
            0xBF7C1D0A7CBD1AB5ULL, 0x93D2884FE0C22997ULL, 0x9B6051A094B6D81AULL, 0xE990DE64B909B119ULL, 
            0xE784C7ABD1EA71B0ULL, 0xCBB7034C4B7C15C3ULL, 0xC1D8E1CCD8176B9AULL, 0x304BE65FCE2B131EULL, 
            0x9BCD1D9BC9EA3621ULL, 0xF1261DE064838457ULL, 0x2A7082A50400AD91ULL, 0x4C16029914E6804CULL, 
            0x2078614963E3C8D1ULL, 0x9CB96F1EAE7EDC5BULL, 0x8F1E4BD35385BCE0ULL, 0xE8754C6476FC853EULL
        },
        {
            0x92BBC5E08871BE08ULL, 0x6B0DC920488D6F46ULL, 0xC46AF3D07E1DF7D3ULL, 0x79002B44C93AB09EULL, 
            0x6023A2902CCFE02DULL, 0xDE8AE3D28F9B0A83ULL, 0xB4AE88F06C6817BFULL, 0x325F02A57E34E322ULL, 
            0xFE4C7C3F03A6F342ULL, 0x702AC90A81A6C209ULL, 0xB6BF9BF55728417CULL, 0x7143A64BFA03585AULL, 
            0xC57F2B065F1BC4BCULL, 0x1561EECD10DCF751ULL, 0xF24EE435D891B644ULL, 0x3943D28F50257AF6ULL, 
            0x5F12D3A8DE0852D4ULL, 0x5C317EB8820E8801ULL, 0x9CE38FDD6F2316DCULL, 0xE3EFDC7E6DD97887ULL, 
            0x3F139314E33AE392ULL, 0x12F908290F7745B4ULL, 0x5125B518807EC52AULL, 0xDAD85411D5CC36F5ULL, 
            0xC8B66307BDC236B3ULL, 0x5303914FCBEB1994ULL, 0x883C87303ADD4BEDULL, 0xCC64377EB0DAA08DULL, 
            0x7221841214EEB55CULL, 0x000928809C2C5618ULL, 0xD43D48E5D41FFC87ULL, 0x96A95C1135E95ADEULL
        }
    },
    {
        {
            0x69DB2F247879072BULL, 0xCB76979767DC71CFULL, 0x8040AAFAA9C70FDAULL, 0x2A70C1FF0BE03F15ULL, 
            0xF7082969E051C1C8ULL, 0x0FC5665DFC68E806ULL, 0x0C9E5442EAD21F85ULL, 0x0F1A83643640DCF5ULL, 
            0x3BC31519E46A2E9DULL, 0x92E8F4C9958710D6ULL, 0x3BBD5F94D5F07453ULL, 0x9CFDC1467826E40FULL, 
            0x1441EF2E9F2DBA27ULL, 0xADCA334CFA39DAC4ULL, 0x251122D9C6D962E9ULL, 0xA92635CCBF70F2ECULL, 
            0x14D715615D0C5BFEULL, 0xF9E39203CAB169CFULL, 0x1E7AD44347858795ULL, 0xB9B60F6F9422303FULL, 
            0xCEAA98FD477FD12FULL, 0x6CF5707DF488BD21ULL, 0x41F77D85BB88CAC5ULL, 0x959A9A8CD2153A0DULL, 
            0x3B6E09C83F043B8CULL, 0xF7F1562535C01B9BULL, 0x501CB072F4419EE3ULL, 0x4704E7F790DB7F5BULL, 
            0x7BF9E3FF56B78207ULL, 0xE477DE37F8BBA155ULL, 0x5D441D0B225E4FEBULL, 0x5AE0433C508FD544ULL
        },
        {
            0xEDBD1E975D568E3CULL, 0xEFC5B4AF6218D35CULL, 0xA68B6B9E6A721DC0ULL, 0x4CBF2F4132DC4CA8ULL, 
            0x57822D2B96EADFEBULL, 0xE40F7FD12DBE6961ULL, 0x7B1B92CD426A0AB9ULL, 0xA9C96B368956EA01ULL, 
            0x037143308B9B2F1EULL, 0x406B872C79843919ULL, 0x44B917FE1D97E683ULL, 0xF3379937C50089F8ULL, 
            0x201936F7CDB86017ULL, 0x1AABFCB80E0ECBE2ULL, 0xC3D737FA495F49D5ULL, 0xEBD209739E50BE18ULL, 
            0xAEB0D0C48D3ED6F5ULL, 0xCCD8E4D29DCCB104ULL, 0xFEF57EE8FE70A742ULL, 0x977B4603A0C2401DULL, 
            0x2F639B3C009A9265ULL, 0x5E72EF6D210756F5ULL, 0xAEFFDBA840A0057CULL, 0xB7E9E93AAEBC3B07ULL, 
            0x0D408A37BD685A1FULL, 0x3783FB0405889746ULL, 0xD94EEB2A73D2C443ULL, 0x40A26B178FEA02E0ULL, 
            0x49C4C8CCCFF684E7ULL, 0x6C27101CA5192803ULL, 0xC6AD80E16DBFD205ULL, 0xC0888740A0C3D84EULL
        },
        {
            0x7EB3C10712AC4C97ULL, 0x75F9E1C874BF7B73ULL, 0xE69D1B59744D8B4FULL, 0x7F90F0422D6A51C5ULL, 
            0xF682BB9F6D2B1821ULL, 0x3D2DCE382EBFF711ULL, 0x708B2E1DA9460A20ULL, 0x59C53993891315EAULL, 
            0x2C24A6629BE1C843ULL, 0x91BB4E3ABFC078CFULL, 0x47E823C5ECE2D5C3ULL, 0xB3DCA144B28164F3ULL, 
            0x1B626D5093ED59B3ULL, 0x8439DF73D99D0920ULL, 0xCD451F42487940FBULL, 0x65E53B8B38E1D8A0ULL, 
            0xA4428D74AE0BB2A4ULL, 0x658E5FBAA3440C06ULL, 0xCD93494B8E58F528ULL, 0xA3A63F9F816A5320ULL, 
            0x16812475A532D6DBULL, 0xA6BA200182B5A923ULL, 0x8F7A0AF4B0FFC1CAULL, 0xBF2D99ACAE66F888ULL, 
            0x6C50DBA63159B809ULL, 0x7EBEBCB0B7EDC865ULL, 0x6ACEF86C2929236FULL, 0x91931C59620B8422ULL, 
            0x9E6D18AC8522B128ULL, 0x7FAB01FA7EA5BC6BULL, 0xA54F7EF159DD3926ULL, 0x5C6E1885140EB938ULL
        },
        {
            0xDD144D825E94FE07ULL, 0x67A3E338B3489CA3ULL, 0xA05BAB0A726238CBULL, 0xBD2AB0C94A0621FBULL, 
            0xB0B9EB1B378A328EULL, 0xB37084F9FEB9A020ULL, 0x6FA355DF46041F9BULL, 0x35488DF4D2406F1FULL, 
            0xF4387DA1C40C343CULL, 0x59AB8735E490939AULL, 0x3C165346EE984CFBULL, 0x8D3BC32FB2E66581ULL, 
            0x05216D64C5C14A43ULL, 0x04A47CC5B76387D8ULL, 0xF5FAD20D783ADB28ULL, 0xE382185FCF6BB61BULL, 
            0x87E9B8A5CDE4AFF2ULL, 0x50DA7BE1EEEA9104ULL, 0x7F72AE9D8A7D4854ULL, 0x55C73FB140AA67C4ULL, 
            0x26B252FCEF3ECFCFULL, 0x7C18178F9BA8D8DAULL, 0x237E6A9F1A75C8CEULL, 0xBCD1E2AC0C6B2631ULL, 
            0x6504F378B5597AD8ULL, 0x5272FA5B98BB2623ULL, 0xFF3387FCA07DCF19ULL, 0x6DB4C4E233442331ULL, 
            0xF7AC1CCE1B84C2D7ULL, 0x40E72334FD87F70FULL, 0x10078A029AA5A1FFULL, 0xAC0C0E7E97BB5248ULL
        },
        {
            0x8FD55854EEACCA5DULL, 0xC8431841D1EAC761ULL, 0xBC9452D75D484571ULL, 0xD8758B52B37C5B25ULL, 
            0x24B545E0722191EFULL, 0x0CEEE5D39AA5AC42ULL, 0x98AFFD1CC80C3836ULL, 0xF5E9F856F63C73C5ULL, 
            0xE2990D67510F4B6CULL, 0x71C16D68FCD9FB4BULL, 0x824F252C9A2D0D05ULL, 0xB1AC6B2323E87575ULL, 
            0x2506D62FFD09EC3BULL, 0xB5BF5ECB275E5F59ULL, 0x866B8C3D57A9890AULL, 0x0B327EFDAD5F04D0ULL, 
            0x27C501D3233351A2ULL, 0xD9B6FE7A1B0204C8ULL, 0x4923AB3F9BC1A45EULL, 0x40382EE66033E6C1ULL, 
            0xDC24B57679C16998ULL, 0x68D9A828F3AD5979ULL, 0xDF1CD40A5726FCEAULL, 0xC8C937C54B6FFD0EULL, 
            0x71D9CB612191E90CULL, 0xA31208F45D886124ULL, 0x6434EB2788CDE566ULL, 0x564BC9F9F04368EAULL, 
            0x3896DEA9D7632598ULL, 0x54E49553093E52D2ULL, 0x55C122B5FB453030ULL, 0x0A14DB7565852A3DULL
        },
        {
            0xB63EDBBBE27FCF8FULL, 0xE3707D077FEBD4FAULL, 0xE90BE76A69512752ULL, 0x834C8459D574E82AULL, 
            0x20B15F600ED43F89ULL, 0x9D496891552EC140ULL, 0x4C81F544375B2B9BULL, 0x588D9155DB41993DULL, 
            0x5446946DC575E98CULL, 0x6EE51ACC9EBBE64DULL, 0xE6B6092EC41A7794ULL, 0x39D82C41159699F1ULL, 
            0xC5CDF718444BE941ULL, 0x5ECC91E5A5A5CA1FULL, 0xF51D629D68E5F8D9ULL, 0x9DE164107338FDC9ULL, 
            0x13FAD6B5D39DD071ULL, 0x6DF187BE994908FBULL, 0x3BFB26AC85666434ULL, 0x4CE178B6A23B94ECULL, 
            0x57E16E9BFD088AF9ULL, 0x70A9578ECDC9D9B2ULL, 0xD388268DAEAD0885ULL, 0x8EC9759B154E0CBEULL, 
            0xEC60D28ACED29C1BULL, 0x2CFFFEEEC8476D6DULL, 0x416A173723B74021ULL, 0x244731A7D55197E8ULL, 
            0xC5E5F7034472ADDBULL, 0x59159F5A5C4B66F7ULL, 0x5EDFC08ADB78AEE6ULL, 0x5C0663E3EE79BB9EULL
        }
    },
    {
        {
            0x581A14D54E8AC602ULL, 0x0C8436DD14ADA23AULL, 0x0CEBD1CD2EBA2623ULL, 0xA00600F58B5B2DF8ULL, 
            0xAD380A4CBB2A4272ULL, 0x019C39B7CC3C3F9AULL, 0x025A2908839ED4BEULL, 0xBADF05AE95C13BA9ULL, 
            0x9B2DE652D5C9995BULL, 0x78438092EF4C3F49ULL, 0xCB975259AA7D473EULL, 0xB9395668A754223FULL, 
            0x1EF610744F05FA7DULL, 0xFDCEA1A573F14F5EULL, 0xB63B67ED697FD875ULL, 0x4E4EE247A5DC1143ULL, 
            0x2B68F746B0B7917FULL, 0xDA6DF99CA0BD7AD8ULL, 0x69ED7BFD88E0DC8EULL, 0x89CB0FCFEE3FF62AULL, 
            0x971B7F3154EF0333ULL, 0x6E9653553730748FULL, 0x520A279E82F6C189ULL, 0xEF43D4ABD9F9A17AULL, 
            0xCA637280094283EDULL, 0x98364558816B9BADULL, 0xD9D2417FC3D118C1ULL, 0x9D9434653ADF763BULL, 
            0x70E71110CD4286D1ULL, 0x9A9D60AA128EBA44ULL, 0xF44EEDDAF2E8FD5CULL, 0xEF9DEFAC4BEBC75BULL
        },
        {
            0xD46F0FAB6D5CF3B9ULL, 0xB4C413F9A7C8D49FULL, 0x40094FCE0A827872ULL, 0x4628A7ED94EACD63ULL, 
            0x9FF0CBAA543125E3ULL, 0x7C98EF1EC7FF6F12ULL, 0xD109E6B5E1BCA4CEULL, 0x323BA955BB15CA66ULL, 
            0x503940CBFF7E4459ULL, 0x58363278612001E6ULL, 0xB9B54D2E93459E30ULL, 0x2A30059D1BF0C94DULL, 
            0xC1B9143C2FD5D90AULL, 0xEB9880ED916C8A6EULL, 0xE066FF9DE09AE8D4ULL, 0x3A721EF516210F13ULL, 
            0x2D90CEE9CE522FB9ULL, 0x6DC729726F19ED93ULL, 0xB21F14DD33D828BEULL, 0xB88B45AD4AC3A569ULL, 
            0xB9787F0D58F3BCB8ULL, 0xE8A1A21EBBF6E071ULL, 0xC9959F3C383BBFA1ULL, 0x4F19E573BF8B83F7ULL, 
            0xD5C946EE9FFC0FABULL, 0xF21E2D0170F0FAE0ULL, 0xE59854076C637247ULL, 0x5F15849C7052D1D3ULL, 
            0x471CE0A996D1DD94ULL, 0x23C6D261F91CD70EULL, 0xE2512E8E9C2EFD84ULL, 0xB4EAB1CBAECC9C95ULL
        },
        {
            0x3E2B3C3EF6655740ULL, 0x904BD02EDAD739D0ULL, 0xFF0876D0246F0B8DULL, 0x804DFC78585FD3DBULL, 
            0xF7E600B3A40D5A45ULL, 0xBEAC858DC71BE3FBULL, 0xA7EC05F8C6445193ULL, 0xB857756B9DF928E7ULL, 
            0x80003D0E8FFEAE66ULL, 0x80E39B2B1ACE0620ULL, 0xA55437EDF7C25B47ULL, 0xA22C4ABCFE8E67E0ULL, 
            0xBA1D6172396B3FC2ULL, 0x8F8454DF612BA6C2ULL, 0x3A28CB57D78FC89EULL, 0x85AF55E59AEA10DDULL, 
            0x6EAC8F3AC5FF3B17ULL, 0x900CD9C9EAFB4A9AULL, 0x05638C6F32EBA2ADULL, 0xD2FF347079993CD7ULL, 
            0x0EE80799C44EE748ULL, 0xAB7C998779985A5AULL, 0xF6240ED31D77AE06ULL, 0x16BE38A3B3BC6561ULL, 
            0x602A552E29C30377ULL, 0xB7D22590AFD8A1CFULL, 0xFA470FF350688FBEULL, 0x97135236A7AA77A0ULL, 
            0x9C18307D64EA5AE4ULL, 0x1BF4E812672FAD33ULL, 0xDB60750BED06C523ULL, 0x8C27029140D4EF8AULL
        },
        {
            0xDC0590F05D08197CULL, 0x13CBA2BB5AF977DFULL, 0xBFFE3CA965FFB086ULL, 0x1036E0AD20919251ULL, 
            0xAE8A10678521771BULL, 0xA64FE636AA433056ULL, 0xD5F685F7BB03EA3EULL, 0x646D3E98CE276418ULL, 
            0xA8A83ED8625B1084ULL, 0x4D646D95E64840A7ULL, 0x6913B2D97EB678A7ULL, 0x333DCC1A7DC9DCF5ULL, 
            0x6200DA5C6426E18EULL, 0xC3C6EF6037F83DEDULL, 0x27A1BF547673C27DULL, 0x28939DA3499ABEA2ULL, 
            0x47FB3AAB661562F9ULL, 0x866DE9D1DD470653ULL, 0x8A074D744527D24EULL, 0xA0415C223771A8B3ULL, 
            0x09CCE888F8FB16FDULL, 0x7993DDB4878B41C4ULL, 0xD45040358C3E4D3EULL, 0x150DA986378790A4ULL, 
            0x2261E1A77238BD1BULL, 0xDE8BCD3267805C5CULL, 0xB535C58CF8B171ADULL, 0x86321A6D86CE2F7EULL, 
            0x4A12389EE74BA492ULL, 0x0ACF103F3C353FDAULL, 0xC243069813F13CB9ULL, 0x018688F2B966B18BULL
        },
        {
            0xE7A0088FC3B9950CULL, 0x01AD153503A7E5C5ULL, 0x3CC38BAA0856BE21ULL, 0x49E44AE3F7CC0730ULL, 
            0xFB174F9CC0C6D8A9ULL, 0xEA52B3247F266E4FULL, 0xCFD695A6ACA4BB6AULL, 0x153FC9D926A3EEBAULL, 
            0x7F0052D5F8029EB0ULL, 0x3E60AC7913599D9BULL, 0xBEDC938E2D2746EDULL, 0x7891E2B60DD7C79BULL, 
            0x4F72B3C095655442ULL, 0x03ED34B59EBBA1D8ULL, 0xA825A065446380C8ULL, 0x549BD9890A0A479CULL, 
            0xFF62E69651512518ULL, 0xA7B980AD654D44E7ULL, 0xBF88FA97402D7AAFULL, 0x902ECFE83C8E5824ULL, 
            0xA86A3238C6A28129ULL, 0x974F93C576BF6C68ULL, 0x5F1BB2F154941DB4ULL, 0x84710B539E5A02D0ULL, 
            0xBAC4F1CB22C07067ULL, 0xF30DE6875ADA5EE9ULL, 0xBE6463A2E624CA68ULL, 0xE03D1A5DA9DD1A6EULL, 
            0x2878C9CF59A43CD4ULL, 0xC04B13E7765BFFFDULL, 0x1A8C772FA23B35E6ULL, 0x770D200790C2CDBCULL
        },
        {
            0x4279313B5DC7C2BEULL, 0xFA28DA03CB64B45AULL, 0xCAF63F2EF611C37EULL, 0xAA25CA23B904EDEEULL, 
            0x55E7005FBA1ED5A9ULL, 0x87B798C0BAE3BA0EULL, 0xAFEFFC564DA52639ULL, 0x8857956C38B1F26DULL, 
            0x70A82D064D3E1F28ULL, 0xA1DAD0E0C1548A4BULL, 0x5E1ED2D667377A1CULL, 0xB088FB45BC08E325ULL, 
            0xFB67B80D49B491BEULL, 0xA3AD42FE5CFF730DULL, 0x932B4DCE09F90033ULL, 0x0DA99C4F85BC4F49ULL, 
            0x4149F43A4DBACED0ULL, 0x3E1605124A15A0E2ULL, 0x014EF8F040F4F9ACULL, 0x47C14ED99998480FULL, 
            0x6A0A26AB14967648ULL, 0x2F69A1C69105FFBFULL, 0x88616F19F6C990E1ULL, 0x292EBF5DA8A35063ULL, 
            0x533564843FDB768BULL, 0xFAD0F83FC8D5EAC6ULL, 0xB507CC5601075D9DULL, 0xDB80DF74EDD74B1BULL, 
            0x1033D126B91273CCULL, 0xC9B08B7FE050F335ULL, 0x64945FF4B1A32A0AULL, 0xF30719B6E5CFC98EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseFConstants = {
    0x3C08F51D9A3DADF9ULL,
    0xA989EFF2A2F96A7DULL,
    0xA9BD48AE5FF7A823ULL,
    0x3C08F51D9A3DADF9ULL,
    0xA989EFF2A2F96A7DULL,
    0xA9BD48AE5FF7A823ULL,
    0x63D4385977D536BEULL,
    0x546925DB4423AC8FULL,
    0x0C,
    0xDC,
    0x15,
    0x5A,
    0xA8,
    0x5B,
    0x98,
    0xD7
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseGSalts = {
    {
        {
            0xAD343E642B0AF47EULL, 0xDB04AEAFC0F8771AULL, 0x39CC3695CAEB4F29ULL, 0x7557AB03BBA81AEBULL, 
            0x076710462045645DULL, 0xFABB47C0D820BBAAULL, 0x027B681CD10D3072ULL, 0xCE77AAE654F83EBEULL, 
            0xDBCEBD1EFA715D6FULL, 0x10FAE056CF8619B1ULL, 0xEDC59FE3F3268F3EULL, 0xC71078802BC13A6AULL, 
            0xDA57D6E8BB6E49F4ULL, 0x3A7379D89DD94B41ULL, 0x1C1EACD01E2700EFULL, 0x7DA20B02785AB613ULL, 
            0x0B8BE86B9CB850A3ULL, 0x5B98C0B11E8B9DAEULL, 0x5BAE4B6419D64744ULL, 0xACF5D2753D1F4EDEULL, 
            0x595F0995F7C88F3CULL, 0x5BE6DEC104E75776ULL, 0xF2EE6A9A86E7B65AULL, 0xB8AF64D9A916FDCCULL, 
            0x5E77BBD02A04E7B7ULL, 0x9418C271C319356EULL, 0x5CFC3DC813FEA61BULL, 0x29FB056EF3D56FA1ULL, 
            0xF823619831C686BCULL, 0x66E253E28348D20AULL, 0xEA15BE9BE0AE9D40ULL, 0x2D33E34F48AA6556ULL
        },
        {
            0x86F079538809F75CULL, 0x49B199518B7582A0ULL, 0xCD5470B849A2FB06ULL, 0x94BBF94C275D8423ULL, 
            0xA1A258C5B78B4F4FULL, 0x0A1F79177437EDC3ULL, 0xE9AF55B9AA59FEEBULL, 0xE2888BA16A2E680EULL, 
            0x635C90C89B1838C1ULL, 0x4B8C244296E990E7ULL, 0x5E128E334F93AC76ULL, 0x98EFAC93836E2F7CULL, 
            0x11984830238210C5ULL, 0x728D582D1955E8E7ULL, 0x69C657680ADA77A8ULL, 0x28CE68A41628F198ULL, 
            0xF2A96B5ABBE5C30AULL, 0xD39358456118362FULL, 0x5198E8303B19B1A3ULL, 0x170EE11C6ACA42A8ULL, 
            0xF5667DB1FF567864ULL, 0x681793E205E02592ULL, 0xBF804AD6697C56B2ULL, 0xE80A7CFB46254105ULL, 
            0xA2D5B95BF6CA0AA7ULL, 0xCA8CB8C815443D57ULL, 0xDE13D040749A62BAULL, 0xBB942DDC6421A598ULL, 
            0x6A60C6A0D914DB1EULL, 0x43162FA1C8198146ULL, 0x8E8FBC49B92598E9ULL, 0x52CF8F7E09296706ULL
        },
        {
            0xA70E4743D6E93153ULL, 0xFB78D11147A71AF4ULL, 0xDCA6A36F93255DF5ULL, 0x8297DE776A7C08EDULL, 
            0xED718394280D9809ULL, 0x4DC985A087F95CC1ULL, 0xF44B1EA56559927CULL, 0xE672C3BD0C0C06E0ULL, 
            0xF0E5FAB8514B2D1CULL, 0xF6D2D61BA82B1975ULL, 0xA8E845A35322D067ULL, 0xB3B7225692CF8D64ULL, 
            0xF8A4FF9AEC048D0CULL, 0x6734612FE9B5BCDEULL, 0x29511BE5DBA6B5A1ULL, 0x19393BF618033F2DULL, 
            0xA88FD34492E557A4ULL, 0x75C0ADC4A7CCD0BFULL, 0xED0534F34F4A225FULL, 0x194C6131CFA4C1B4ULL, 
            0xD8DE3E89005611DDULL, 0x96098CC2875FF53FULL, 0x44B2AE38FA38DFB8ULL, 0xE24BE80826816D7BULL, 
            0xD4FBBA89AB1BB328ULL, 0xD12F1AAF8A3FD678ULL, 0x1B1D19CC8CDD5016ULL, 0xA83E885D5321A7E1ULL, 
            0x1EBD582035E6CFBEULL, 0xA07CB66B11562329ULL, 0xE0760559962675B1ULL, 0xA2F91E13C926867EULL
        },
        {
            0x5897850C310B43CFULL, 0x69CDD493A6016448ULL, 0xB1F6ACCE8C34AE90ULL, 0x3846350A293B12B0ULL, 
            0x0E5630F9579D58B0ULL, 0x7001ED97500EEF2FULL, 0x7B3AA5AA6E6F2805ULL, 0x18363681585DA1EBULL, 
            0x58AAFAAC4889760FULL, 0x84FA64EA353125BDULL, 0x802BB8440115D9D7ULL, 0x6125E9156E339C38ULL, 
            0x75EA727C31A8E3A5ULL, 0x4C583D55C8FA58B0ULL, 0xBA189608BE48A738ULL, 0x788CB38491096E4BULL, 
            0x3F8717D160B79FB1ULL, 0x07656B4F835A6554ULL, 0xEA94097C0E530B82ULL, 0x4CF8FFFF1F159B9FULL, 
            0x7F9677703B8BB59DULL, 0x9531D6E6A2383F7BULL, 0x57923CD102C8EBB2ULL, 0x8EF22DEA9822B5ABULL, 
            0x829A323F3204A634ULL, 0x05509090C88875F4ULL, 0x87FE0607DFDB1301ULL, 0x0250038FFA9C4576ULL, 
            0xAD7599628A8DFA4DULL, 0x4C8842048755C10CULL, 0x10F9702443254C7EULL, 0x650C58D87EEC5585ULL
        },
        {
            0xB170DC44185BE114ULL, 0xE68796E0E48D070DULL, 0x42B233C6A7218A23ULL, 0x1F94E53429E0F2EAULL, 
            0x115E2D08046E481AULL, 0x6704204EFC9FBDBBULL, 0xB91536DA5AA1510DULL, 0x2E9A67F04992F9A4ULL, 
            0x14268EAAE052904CULL, 0xD810725FD0464D68ULL, 0x52FB344BC9A93B12ULL, 0xF0197F6A71F2A56AULL, 
            0xE70EFF665E90F410ULL, 0x58A2007696664C81ULL, 0x9FDAB879236B1F7BULL, 0x55DC798F5628D2CBULL, 
            0x8190333560C524C8ULL, 0x5431A6D605075173ULL, 0x193D3F8760CDDB10ULL, 0xD0D868CC665183D4ULL, 
            0x56A01D7935C1D02AULL, 0xACDEE24676C70138ULL, 0xFD7EBC4DD842D2A3ULL, 0x5816D86B41DDE748ULL, 
            0x5D4FD8DA26947D76ULL, 0xDED6B06F29185F8BULL, 0xF933E011F50F8B4CULL, 0x03CBE43F06A47E46ULL, 
            0xDAB5602C2AB147DFULL, 0xF1E55BF2223DE5D2ULL, 0x15E32333845E35DEULL, 0x14E3E41A7EA400D2ULL
        },
        {
            0xB4DE6553205CB4ECULL, 0x80AF52C77340A4ABULL, 0xE2743A3342608D63ULL, 0xE9633A3140833444ULL, 
            0x9E38FBEAB5F7B44EULL, 0x251DD1BD0798199EULL, 0xB3AABF3486E86E21ULL, 0x81B83EC42748A17EULL, 
            0xF14D3261152192C1ULL, 0xBA6DCFFEE6CF7FF9ULL, 0xB74BA124FA676291ULL, 0xA4C2254FF417B91EULL, 
            0xEED0911CA4C9CC63ULL, 0x0CF272BB90695345ULL, 0x7DF4E80B0617D75BULL, 0xB871DD33CCA69D2EULL, 
            0xB13171A1B75D9EEDULL, 0xD9BAABAC77275CCAULL, 0x282B4524BD8AFC71ULL, 0x105C52EE3BC16215ULL, 
            0xE946A36A303003E9ULL, 0x0873A4B002BA8753ULL, 0x6C4F1DE963531911ULL, 0xE4773C6BA05BFECEULL, 
            0xC13A1AC7B0795CAAULL, 0xA03A60FBC26AAC74ULL, 0x23BF8F45BA63A2AAULL, 0x25EAA4F753C73A2FULL, 
            0x87F9A55A2AFC069EULL, 0x276CD2F58549D14EULL, 0x6E2A308BC61EE6FDULL, 0xF033D25BE20B2F8AULL
        }
    },
    {
        {
            0xF3D283498613EEFEULL, 0xAC12A7D517E2F3B6ULL, 0x9729A8A538809CB4ULL, 0x30CEFEF8473049D2ULL, 
            0x5AFDA4233632E223ULL, 0xFDA85950A2275F9CULL, 0xC87E8737E24B6C3DULL, 0x4A31233B9E4FB3B5ULL, 
            0x68221F13264D9799ULL, 0xD955362C9DC4D9A2ULL, 0x47CB8422B78C99E4ULL, 0xFAA72B2A96783B04ULL, 
            0xCD2B31D695F5F3D8ULL, 0x05D271B5982D8A99ULL, 0xEB748A033AA4FEF6ULL, 0x555A0E62BD3A8EA9ULL, 
            0x95BB085E253C9DA3ULL, 0xFD63C5A28F42B029ULL, 0x4B77517B5A32E2EAULL, 0xAA91EF19312354DFULL, 
            0xD2AFA5CCBC2E9880ULL, 0x87D05D397247F267ULL, 0x67EB93C9C975F7A7ULL, 0x7F2ABE47E5A89930ULL, 
            0xC62B8BB86A428E4DULL, 0x1DCA580917630C56ULL, 0xFF3E76FDFC4EC813ULL, 0xE316DEE2CD3C46F4ULL, 
            0x10EB3EE027685F79ULL, 0x914B9F8428BDE40AULL, 0x65E8EF0C601027CFULL, 0x15635C5AD639A08CULL
        },
        {
            0x3F08275C5699BEA7ULL, 0x461685B6B98B406DULL, 0xC07D9A992343C69FULL, 0x1EE49F5A40E55C11ULL, 
            0x379A57A951F09237ULL, 0x561E006FF3C5B9F0ULL, 0xDC71AD20ADEC83F3ULL, 0x7C06810892EB8B1CULL, 
            0x00817956EC5D9F3CULL, 0xF7D2E1562FFE4B7CULL, 0x29AC1F6823745478ULL, 0x0C1624D587E3B926ULL, 
            0x6C667ACE112FDB15ULL, 0x9B48903EB560DE59ULL, 0xBFE592E1CA80E468ULL, 0x5EFD79FBF87BAF6CULL, 
            0xFCC11553732A7F7CULL, 0xA585A465990B9E55ULL, 0xFD74E365DFD965D0ULL, 0x0F864726CB21DE26ULL, 
            0x7DE5F5AAF5C65DCFULL, 0x1E1D8798CE097CF6ULL, 0x59C6647542FAA863ULL, 0x6139DF3372D99E97ULL, 
            0xE156EC22EF2DBF15ULL, 0xFC70E26BE0F1A7C2ULL, 0x2FEC22C247A05846ULL, 0x2BD3D424964AC5EDULL, 
            0x2C6657AD9C9CF5D8ULL, 0xA6797AAD21F0146FULL, 0xD14B1277DE9E91BAULL, 0x49306E8C8D2A7601ULL
        },
        {
            0x695B6DAB4648E691ULL, 0x96717470F253C57EULL, 0xF0FD4505F24CD468ULL, 0xC0D643FBA5047497ULL, 
            0x31B0D0CD1EE3DEA5ULL, 0x3FC0D93A12F1775EULL, 0x5EAF3B52BA4FBEA6ULL, 0xB601297C4F077C20ULL, 
            0x96D3B49C91C9ABC9ULL, 0x6C02365C9E8C2658ULL, 0xF4F8EED5A3C921E6ULL, 0xED693E5ABCC0438DULL, 
            0x90F30B18551296BCULL, 0xB0DE018E11585DE2ULL, 0x0C38830BA89A345EULL, 0xF85007FCDA71B91DULL, 
            0x45706B4BDE150C20ULL, 0x19EBB3F7F3A323B2ULL, 0x9C7467AFD9C866C7ULL, 0xC45F896CA0F9965CULL, 
            0xBD67A6A59BC3787EULL, 0x4536AA9382E96C7CULL, 0x80217E443E8F8252ULL, 0xCB292472921A6FF0ULL, 
            0xC753F7D1212B70BCULL, 0x08950702E1A11205ULL, 0xE9882EB2FD74DB38ULL, 0xB802C565C1A011F9ULL, 
            0xC01E4721BA749E7CULL, 0x0C936F486346A2B8ULL, 0xC1F57DF1D0A48F62ULL, 0x74739B3A5393642DULL
        },
        {
            0x6E7C870E70F541A9ULL, 0x6A6247D28AB30493ULL, 0x5A2FC6E697BD6862ULL, 0xCE886C543681DA9CULL, 
            0x5D572235A12D9B70ULL, 0xE13D65C9FC38A9BEULL, 0xDA7E8932C7E1B95EULL, 0xC2201FBDA16C0697ULL, 
            0x0223C90E5498DB0FULL, 0xFB67FD23A06E5D33ULL, 0x51C1EAC6C753FD94ULL, 0x528B39E49909B142ULL, 
            0x88B929505FBF22C6ULL, 0x37ACCA9A6B8505ADULL, 0x4969B0244A7ADF1AULL, 0x1731D2D6C8194863ULL, 
            0xA6F940AD64162383ULL, 0x6A80FC8EEA715E74ULL, 0x016E44472D272E02ULL, 0x5C6D11A48F618DFBULL, 
            0x1476CBD1CEF03076ULL, 0x30693B575D6E589CULL, 0x53B3494250AFA935ULL, 0xE36449D309C4E5B4ULL, 
            0x3E6D6BE8B0A31FCCULL, 0x95E8BBDBE5DE9FD3ULL, 0xD10FFC6C55721CD3ULL, 0x3A0230829D021A4FULL, 
            0x0F0917D93C0C478DULL, 0xA50E597EC555FDD7ULL, 0x00671ED04389D095ULL, 0x31B22A33FEDBDA1CULL
        },
        {
            0xE41F2A7CEA9A2345ULL, 0x80306E6815055A03ULL, 0xDD2AD23D965F5037ULL, 0x4E88763B3B71F5D1ULL, 
            0x7D4E01CA2B533960ULL, 0x2808D4E7EEAD163FULL, 0x24A8CB6D884A12D6ULL, 0x05985D1DD1DF1E1CULL, 
            0xD7333D97D9ACB272ULL, 0xBD32A86A68EE4147ULL, 0x48FF1EF42CCA93C2ULL, 0x2AE8818E0CC63022ULL, 
            0x738A7021B30595AAULL, 0x1769C5971641F924ULL, 0x3C71C07B15C08527ULL, 0x5A0D1E484C4F106CULL, 
            0x329651FE06FC680AULL, 0x76C48C438F04BB4AULL, 0xFC46D73832FE2292ULL, 0x82E9B7FD05E629F1ULL, 
            0x9BA6B0EED01134B2ULL, 0x36D8F61EFC65C340ULL, 0x1134328FFC3A0203ULL, 0xA92815E5884289F4ULL, 
            0xA5A0890305F69445ULL, 0x71374ACF24457830ULL, 0xCB0A3C399FDFAAFDULL, 0xD8D668751AAE4F6FULL, 
            0xB5503B23A7615F3AULL, 0xD561FA58AEF276F6ULL, 0x530546C488EB1D2EULL, 0x2868676AB467FB7FULL
        },
        {
            0x1CFD96617C8DB28DULL, 0xAD1FDDCEACDB82F0ULL, 0x7C8970F475AC0D51ULL, 0x2C6B87C7ACB17F75ULL, 
            0xCD94F44D728BC6B4ULL, 0x63EC5474FEF09F9BULL, 0xABFED65A375F488FULL, 0x23B61A2BEC520E2BULL, 
            0x6209594F54B4D281ULL, 0xD562841127D1AAF6ULL, 0x277C7696039CC08CULL, 0x9466E16612553EDEULL, 
            0xE07B67253F2A99BDULL, 0xB5116226452444FAULL, 0xE9179027015B32A1ULL, 0xD8F8F387A362BBBDULL, 
            0xF7614713AE56F0F1ULL, 0xB8C6207F2D4236B9ULL, 0x5FCF7867BD2B16D4ULL, 0x2B4C7A3338FD487AULL, 
            0xABABABD74C9BF3DDULL, 0xA86D05F317E93395ULL, 0xB6C2E5D624B8622AULL, 0x4AB6BB84820CB8C2ULL, 
            0xF0BA987C6381135AULL, 0x46701DDCD2270BF5ULL, 0x41EBE67FFB6298ABULL, 0x30A770205E6CEAA3ULL, 
            0x8C9C9FAF6A7834CDULL, 0xA9E2EF33E93F9741ULL, 0xF37A3685E5945D16ULL, 0x3D56BEB092CDD30AULL
        }
    },
    {
        {
            0x6B582B6B9B1B64C2ULL, 0xC52C62507F6CF37EULL, 0x0B889C0C9DE79902ULL, 0x2C1B6AE205A9A87FULL, 
            0x2D604F1A6F52ABE9ULL, 0xC5AD1A8DD65D63ADULL, 0x3EF0DB43C3D28FDEULL, 0xC04F4C04FC686552ULL, 
            0xAA4E583F6A5089F0ULL, 0x642DCE221BCA16D2ULL, 0x2ABB38B0D6E3DA5EULL, 0xB0DAD83A88577776ULL, 
            0x27579A5B53ED188EULL, 0x74814C23C59AE9D8ULL, 0x8A1DFD51ABC36C8BULL, 0x593E51E95AFDA5A0ULL, 
            0xF4E30AF2B4A7C337ULL, 0x446EFD6E1AFD7102ULL, 0x07C6ED3BCA60DA1FULL, 0x5F70DBA702993B1AULL, 
            0x2ECADDC9BC382C35ULL, 0xF2BF647C38E52620ULL, 0x45C3D1B79AF6825AULL, 0x235FE62946444683ULL, 
            0xED200AB4271E545AULL, 0x0DC19F7E85E59528ULL, 0x800A9E776E38E2DAULL, 0xE45147082E5EC5F0ULL, 
            0xCECE0A24847CA514ULL, 0xC6B2048CC54779F2ULL, 0xCE7CDFAFADA745E7ULL, 0x6C43089296ADAD19ULL
        },
        {
            0xB73FE7099E3D35A5ULL, 0xEB2C231CCFECF67EULL, 0xDA35D15617FDCCDEULL, 0xDFBA7E794AD05FB8ULL, 
            0x640D97BB28F1C9B6ULL, 0x96549743E3412A8CULL, 0xC1469EA120917171ULL, 0x72C27A21B9702E98ULL, 
            0x84B8890CF811DEE9ULL, 0xA5F103E24AA33CD8ULL, 0x0C323125D5346CE7ULL, 0x8C159CE6F3C3436CULL, 
            0x446969076C9F0C50ULL, 0xB7527B7DDADF4F58ULL, 0x3EE7662FF75BE6A3ULL, 0x767C586EC8A4B00DULL, 
            0xE7A459A732775B2BULL, 0x78F0B771BA52B7B1ULL, 0xD354ABD6D2BD0BFCULL, 0xEB07623FD13DA14BULL, 
            0xFEDB2F6E1EF0F5B4ULL, 0x27488F85EBF72F45ULL, 0xA997FA081103FB3EULL, 0x549C82D1B4415F7DULL, 
            0xBF9848EE9ED8759EULL, 0xAD16F40A0C18675EULL, 0x0870B8725077BBA8ULL, 0x05D28D16D64BC926ULL, 
            0x0832937B946C98F0ULL, 0xAF800F167398E0CEULL, 0xA87D0EDB42321112ULL, 0x51EEE32C30D7A987ULL
        },
        {
            0xF08F06B5BBC5CA6CULL, 0x215DAE3B52D95A37ULL, 0x4E804C3996D13E5EULL, 0x8BDCD9ECB7EB6923ULL, 
            0xE65B57336F46FD76ULL, 0xEA7E599AFBF4C549ULL, 0x41725CB3CA57820DULL, 0xDCB5764CF1644D89ULL, 
            0xF7A45891B868039FULL, 0xE3C4F5BCBC425CEDULL, 0x64C26344DC5536DBULL, 0x6CD09094CD4334AEULL, 
            0x3333A79CE8FB32C8ULL, 0x0854CB632A468328ULL, 0x823FACAAA0D8C3BEULL, 0x162F93DC90B1FC32ULL, 
            0x158278246A6C260FULL, 0xB27FA2D20147E22BULL, 0x77DB40C08A8D312FULL, 0x2E478FA2C608CABBULL, 
            0x47F8B61C4D089BACULL, 0x5E27482B79B623F3ULL, 0x2C1E7C6B2C2D5BB1ULL, 0x32F6738ACF46E989ULL, 
            0xAE73F2D3D742F963ULL, 0x24128A16AE9D1E21ULL, 0x2E99808F2944CD73ULL, 0x37B1C36D2F53FA16ULL, 
            0x650BC7B3502F48DCULL, 0x9C01CE3B6D435248ULL, 0xA326BF003FAB1448ULL, 0xBD2809455D473986ULL
        },
        {
            0xBBE708B612075665ULL, 0xE4FD64CC6849E9DCULL, 0xCFC6B46AD1CEB2E5ULL, 0xBD90BC3C48F9571BULL, 
            0xFD5C3F839048CA8CULL, 0x27388D821DD4B8FDULL, 0x92BAB4C4848003ABULL, 0x15B357614CB4AA9DULL, 
            0xD403EF4040BF57F3ULL, 0x323E3B142BB1C0B0ULL, 0x165F284851ED5B54ULL, 0x67ED2A3F610F3D97ULL, 
            0xA27F4634F8BFFB8CULL, 0x380A97EAE60CE224ULL, 0xCD5E61D56AE95294ULL, 0xD02E9D8A2931EE1FULL, 
            0xA58AC2E1DF1826B5ULL, 0x11469FEFF8835817ULL, 0x667E9033C585A120ULL, 0xE6246EA7295537B9ULL, 
            0x496B0516487C7EBAULL, 0xCAE6480D6431C741ULL, 0xC07FC5144AF1929BULL, 0x8B1DF3C2E72030F1ULL, 
            0xEE0314890AA2529DULL, 0x61BA96240E756849ULL, 0xD5BE2C2C16CF26A0ULL, 0xB675924644EC5EAAULL, 
            0x630C55E665D925ECULL, 0xCE3C67C7A230884FULL, 0x0E58D7E27C3F53AFULL, 0x2B5C55E95F25FA19ULL
        },
        {
            0x0E46E4A7BFBCA6A4ULL, 0x34056A371494A007ULL, 0x860084E724EC829BULL, 0x97AEAD489DC91DE2ULL, 
            0x0C172402CABA96FAULL, 0x079F7624D0B10036ULL, 0x5EE0DB550AADA1D5ULL, 0xDD53D4A212F410DEULL, 
            0x5C439AB8C5089AF4ULL, 0x701783E1E4B14E78ULL, 0x26DB3C98336F9E32ULL, 0xB35E03DA45A3CA57ULL, 
            0x0E2D8E8A4CF679EBULL, 0x64FB95AFB01CDF27ULL, 0x4128324862E086BDULL, 0x04AB62339D764F44ULL, 
            0xF614C15542A279CBULL, 0xFB08A7CFB6A13E9AULL, 0x88F4AC3324677A01ULL, 0xD8FCFE7DBE08FE7AULL, 
            0xB53EA1F88DE0CCA9ULL, 0x697260CDF9A6D62CULL, 0xE02AA10F39798838ULL, 0x205E6CF43C96513AULL, 
            0xA090240E3C945C38ULL, 0x47C1334673ACFC14ULL, 0xDE6B5E4476AAA0CBULL, 0x4F8FAABCB47EE9B0ULL, 
            0x68CDC4868DF212FFULL, 0x6453DB508868879CULL, 0x2E7854CE9DA56C99ULL, 0x9EB85A21B7D803A3ULL
        },
        {
            0xF930D8BAB4133EFDULL, 0xFCFEED770B06C953ULL, 0xAA959644AA604303ULL, 0x2329AF8D553B57A6ULL, 
            0x54C6123DC0225046ULL, 0x596C42B99982F5EFULL, 0x5907C20F48A127AFULL, 0x3E355BA41C764FCEULL, 
            0x88028B235A77E3D1ULL, 0x237B3CF2E99B9F6BULL, 0x4B3E00DEF4A2FA24ULL, 0x5EE7CDCA29D77707ULL, 
            0x7BD6CF2517D1920AULL, 0x613F5C2D4CEFAFF4ULL, 0xE6F76B04E580D401ULL, 0xF25C08C7DBC667B2ULL, 
            0x1FD1C047931E4866ULL, 0x2A8920FB4E0E1940ULL, 0xE479DDF230BA9955ULL, 0xBEBE95A29BE82F90ULL, 
            0x79915FA68FEE70BDULL, 0x0B870939D6AB9446ULL, 0x18B70A92AACAD4D9ULL, 0x7076623570A79019ULL, 
            0xA1EE79ACE7A09637ULL, 0xE5C7FEC35911CC7BULL, 0xDD2D1BBC102A061EULL, 0x67417E7E5C231FB1ULL, 
            0x9CB8B3AD0F9BF69CULL, 0x13B33601F2799418ULL, 0x58E344A45FDF3D8BULL, 0x8E0CF3FA6CE8D182ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseGConstants = {
    0x4BFF1134DC79FFCCULL,
    0xDE7F0A92F7E163A0ULL,
    0x4A63AD651F0E2E39ULL,
    0x4BFF1134DC79FFCCULL,
    0xDE7F0A92F7E163A0ULL,
    0x4A63AD651F0E2E39ULL,
    0x68C12D93C936A21DULL,
    0x85CF4A6EAC755155ULL,
    0xA5,
    0x97,
    0xE6,
    0x37,
    0x17,
    0xC8,
    0x33,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Gemma::kPhaseHSalts = {
    {
        {
            0x7A36D418BA38FE86ULL, 0x323E907FAF51A28DULL, 0x7142499A55F32331ULL, 0xC4BADFD87F986786ULL, 
            0x6E78A7E61A6E2271ULL, 0x4352EFF69B1AB298ULL, 0x9B346345E50EC8D5ULL, 0x50659D27FB3E06BAULL, 
            0x799D0320937FA079ULL, 0x96A6EC3362E20D42ULL, 0x0F527A010AC0CBE0ULL, 0xAD9158F7D8B560C7ULL, 
            0x38C956FE25FD3C10ULL, 0x03997D7DB5F28049ULL, 0xAC8D11AA3CA43611ULL, 0x1B671074F636DF4CULL, 
            0x924F3259395F9885ULL, 0xA4708D669012EE92ULL, 0x14B01559D4DD4F79ULL, 0x0CBABCD66D829360ULL, 
            0xD1C0E8E5D4CF48E2ULL, 0x6E75D2C559406CACULL, 0xC94A155AAB1566F8ULL, 0x60AA7036661AAB90ULL, 
            0xBD663F116C49D7CCULL, 0x3008D78F5AF25D6EULL, 0x2F7A758DC69D2FDAULL, 0xF38C2F31AE84F23FULL, 
            0x2F20B098C6701F47ULL, 0x51C91848C55CA0C6ULL, 0xA7509C1189BF04F5ULL, 0xB4256723569DE85CULL
        },
        {
            0x2B491E5B47FE1AF1ULL, 0x1AFEC4EF0B35C234ULL, 0xF3733998CA2F4B4FULL, 0x65715AF31A286C30ULL, 
            0x3E4EBFB428202FC1ULL, 0x10A894F691389FD7ULL, 0x6DF2CA64E0A336D6ULL, 0x0BCC103138FC9457ULL, 
            0x9A0080B47CCD28C2ULL, 0x73158462AFC8291EULL, 0xC9B4B6F60DEFC44CULL, 0xFD5FF23E5393F794ULL, 
            0xBE4524708C3E2E55ULL, 0xFFAC9C1942460625ULL, 0x4555478B65EF274BULL, 0xFE8519582BB8DD5DULL, 
            0x22D4D9540A94E260ULL, 0x8606EA0B6BC94F9AULL, 0x5DE09887CA6B9E88ULL, 0x2AF2976301DC7A68ULL, 
            0x3FF13EE8596AF529ULL, 0x4F420B67E8DCD4BAULL, 0xD524AFF983DBF1AFULL, 0x43597693E2C650C1ULL, 
            0xCB954928E7C79B9BULL, 0xC1BA122E33DE42EFULL, 0x3D19A9CAC07D9C60ULL, 0x9F073C3E11A32860ULL, 
            0x26B7F2B5C212C110ULL, 0x43392BBB903F0D4CULL, 0x5C25369E01531FAAULL, 0xE62ABEB1F4E80654ULL
        },
        {
            0x151CECB8CFDB0C24ULL, 0xF332083EB5233B46ULL, 0xE9450ACB27280E19ULL, 0x4D0DAAD3598FD79FULL, 
            0x1D246E98F72DE075ULL, 0xBDE06ACBA544DE29ULL, 0x8A343B9346B1F08BULL, 0x2E5E8DB4539AC923ULL, 
            0xEFBDE1F4E9E2FE8EULL, 0xE2B7A49388295697ULL, 0x50E1378CEED1089EULL, 0x6E5BA471BB8B8DB0ULL, 
            0xC7159BE51B180CF1ULL, 0x24C7131A7B90DD22ULL, 0x98F40E6FD3CBBFFDULL, 0x4D4B3D6EDE8D6FE7ULL, 
            0x15BC8C8C0D60ED33ULL, 0x4063C3CC9A84230CULL, 0x39D5D9508F5FEA8CULL, 0xD38EA8696D02782CULL, 
            0x02073542AABAC4EFULL, 0x6473A9F820B4187AULL, 0xB0EFFC7109127831ULL, 0x13B8C26527845472ULL, 
            0xEF4F81A7F370AFCCULL, 0x357402334D84C7BCULL, 0x8A164DFB739A9DC7ULL, 0x1B9857FA8625664FULL, 
            0x4E7BFC68E6557EE0ULL, 0xF69FA1281E53DABAULL, 0x88459C9B14435C83ULL, 0x52E55F9D197EFCC6ULL
        },
        {
            0x14AC074C130138DFULL, 0x77A0E8EFF72BC2CEULL, 0xDC75B8AA8A15B36EULL, 0x04E4162C74437E74ULL, 
            0x682E3A17529217C1ULL, 0xF1DEE00766F8DE21ULL, 0x91ACAFEEC0965BBEULL, 0xB54F752ED60AB9B8ULL, 
            0x3B12A37D49BAC169ULL, 0x37D775B4380C1D1FULL, 0x8EED8783D21CB6A8ULL, 0xF2CD70B03AAC8F2DULL, 
            0xD44F46B1BB43F4BEULL, 0xF396E3D5D8C4953BULL, 0xCC679064C38F61F5ULL, 0x3FC43ACDE8756374ULL, 
            0xDB3AD3B2FB950094ULL, 0x58A8439DC69CB8AFULL, 0xD4F5C1B7F263CB7DULL, 0x72A0363ABB04EC85ULL, 
            0x53011A08F5DB7E3DULL, 0x4F61749A5013AB77ULL, 0x0FE53E541AFA8547ULL, 0x565445CF64F3F464ULL, 
            0xFA66D6A567D480FCULL, 0xDD5EBB4AEB1CF61BULL, 0x2B0FE6963AD7E605ULL, 0x05B30B5A365159D2ULL, 
            0xAE6AC8AA2CF5117EULL, 0x05B261D87D354392ULL, 0xA92E9B1A7A49CA34ULL, 0xBC9BB533957C679EULL
        },
        {
            0xFA9CBCDA499BFA32ULL, 0x251B282FAA9A5A38ULL, 0x495E5A1B98D820E3ULL, 0xFB8BABD9009EDEA4ULL, 
            0x6888F3A247FC8B84ULL, 0x75C7C4C61E70AD79ULL, 0xF294DB3A6FFE00BCULL, 0xAEBD762F1B844CAEULL, 
            0x62669A46E0184A55ULL, 0x27D63DD78AD2F0F4ULL, 0x8D867F6372B5C292ULL, 0x6E7D20F98086E536ULL, 
            0x9B0072BCE185F6A7ULL, 0xA55464C4FD402C02ULL, 0x82D6556E700E6474ULL, 0x4134D4174D81B00FULL, 
            0xB9974908B9E607B8ULL, 0xDBBD9A05BF2ABF93ULL, 0xCAD1D142BE0D23A7ULL, 0x6850303C03DC30B8ULL, 
            0x09AF37D19A1F0406ULL, 0xF3AC7907A96513F4ULL, 0xD6BF0CE78F0314D5ULL, 0x08BAAB69E8641BC8ULL, 
            0x2EF6A268DE07DBC9ULL, 0xF91F7BA5D63512D7ULL, 0x8ACC7D6F24658399ULL, 0xE312600899789F2AULL, 
            0x4C919BD1BCAD7256ULL, 0xC551F3EC0F54B721ULL, 0x4BAF9EC4E5A59A5CULL, 0xF9A939301DDE9B11ULL
        },
        {
            0xBF6BFF26E2652668ULL, 0x764C602C27E69F4EULL, 0x439D9E72AEA866FFULL, 0x516792A8D536D4B0ULL, 
            0xDE24D87B18247AA6ULL, 0x2DF5CA447932C759ULL, 0x02B9113A855EF2D5ULL, 0x552E3BA92FEE7BB8ULL, 
            0xA7401AD70C1C35CAULL, 0x2E7212F7F698883CULL, 0x69E1328FB166F65BULL, 0x4A500DE857655672ULL, 
            0xCC316BC451551C7FULL, 0xEE921F28075D3E5AULL, 0x8A708A8BB0DA6A3EULL, 0xEBB7339BEAF85130ULL, 
            0x5A511A0E24EE0A22ULL, 0xF8FD368F67DBFD27ULL, 0x17D2D0F8944AE82CULL, 0x9C9E2F6DE19C802BULL, 
            0xD1853DDFE5B34AEFULL, 0x7AD9418C0F823FA9ULL, 0x583EAC0EEAFA4526ULL, 0xE8B4E6A37D59A3C3ULL, 
            0xF6714DEF2563ED51ULL, 0xF360C2BE1AC64BF1ULL, 0x02A04B569DD0A70AULL, 0xBB39C5971C83A0B4ULL, 
            0x90BEF4BF1995E770ULL, 0x4997853AE21FC347ULL, 0x9529F92CCD69D2BDULL, 0xBC500A0BE1A858BFULL
        }
    },
    {
        {
            0x47E6B5AD0BD77CA3ULL, 0x970BEE0847F8ED4CULL, 0xB32F5016D8A0482CULL, 0x35E7CB9F3167BB79ULL, 
            0x453359735B3A9E27ULL, 0x5B565C1B8884092EULL, 0x79CA73092334D722ULL, 0xA882237DF909B9EBULL, 
            0xCF38F82143A343E6ULL, 0xC1E20EB5ACD51D3DULL, 0x4C88C19A8618F5EBULL, 0xEE7F70FF23D874DCULL, 
            0xF86C74FC635E7B64ULL, 0xB1B009F03E712BCBULL, 0xFAA571E7CF51B687ULL, 0x3936D8C9C6CDA270ULL, 
            0xF2D12612A0DC0444ULL, 0xD41FA7167E8584C1ULL, 0xEAA25665EC0F0DADULL, 0x6FF864FC775F0A9DULL, 
            0xD3E46AFBFE1A552CULL, 0xCDF025504AE795DBULL, 0x9FD09631EEEA7003ULL, 0xC8F8E94ED485C2EDULL, 
            0xBF3DEBA503B702D8ULL, 0xCE5C91EE0B9D9BCCULL, 0xAA6EB7CE48B0CABEULL, 0xE0CFBA314C83AACBULL, 
            0xB3495DB668329932ULL, 0x8F0CBB8BFDB48AF3ULL, 0x92CFFF468AE20B22ULL, 0xCC75258A2E5DA587ULL
        },
        {
            0xC8817A2A02AF19AAULL, 0x0019C130BF2BEBB7ULL, 0xB448E5B419C268FDULL, 0xD419918A23420B84ULL, 
            0xB302FADF7C5E3EA7ULL, 0xF5443C27315E97D4ULL, 0x9FB64E754FA834BAULL, 0xCDE83CE00385F5FDULL, 
            0x79DB956DEEAFBF83ULL, 0x76CFB1F81CF3B37FULL, 0xC8CFB22F0666D028ULL, 0x535307764464B13FULL, 
            0x9D7F65D9EF9D4FA4ULL, 0x2C71DAF80008CB34ULL, 0x86029DB9ECC515C2ULL, 0x1E81F9A92D700F34ULL, 
            0x8A5141CEC734810DULL, 0xF5258249C2807131ULL, 0x5FF863F4FE760BA6ULL, 0x7008B52D26F30285ULL, 
            0xD8D2EFB0C4083364ULL, 0xB261AA26745B5952ULL, 0x002DE2861E7D2D02ULL, 0x711B642D8BD5D25EULL, 
            0x6FAC96E2641AF5F3ULL, 0xB0F3936CDB8536CFULL, 0xD9DC7A44684503EDULL, 0xD6D1E04809B9DF00ULL, 
            0x7ECD6F5CA76CD240ULL, 0x8CF93681C4567B6DULL, 0xF0A867647284475FULL, 0x5EBBF56CCC2AF141ULL
        },
        {
            0x03B3F4C1EDB53348ULL, 0x5AEA5F201550FA61ULL, 0x48B3FD681A085486ULL, 0x639EFDED5EDF3087ULL, 
            0x28E173E18B445C58ULL, 0x65C16AF4748D6C8AULL, 0x87E7C7BD3D5C1F2DULL, 0xFC8DE11B4256DF93ULL, 
            0x09B8E975A4F45103ULL, 0x2216F1BA85660A40ULL, 0xAA3C2706F7463D0CULL, 0x2A98E8D11CCF0391ULL, 
            0xE2A301811F5780E3ULL, 0x8A6967DBD748314BULL, 0x5C6C4BDB64A8524DULL, 0xE0B039C85976E980ULL, 
            0xEEFAF2F4A89A0B7AULL, 0xCD1B096EC23F2AAEULL, 0x94FAC0FE12BD0559ULL, 0xE44C248A1B612CCAULL, 
            0x8E266D084B91E1BDULL, 0x6E413D5C8311C20FULL, 0x326D7805C58F2E09ULL, 0xE5820AB70D0681E5ULL, 
            0x9020D9899AEED398ULL, 0x08EC0FA227E39344ULL, 0x32F1FF02D1E80666ULL, 0x7DF62F373C879878ULL, 
            0xCA4F9062C8E4A4CFULL, 0xCD6C68524D620151ULL, 0xE80AC9E1E280B545ULL, 0x699CB2CF4E0683E2ULL
        },
        {
            0x49FADEF086E100F4ULL, 0xE868463A292BFE58ULL, 0x27BA544926EBFA35ULL, 0x0583A5BBD94E9626ULL, 
            0x0EB7FE650D15AEF3ULL, 0x980C089F3803FEC0ULL, 0xFDADB186798083D9ULL, 0xBEE93175521B0CE2ULL, 
            0x06FFC304FFB20A9CULL, 0xA7ABF7F1F3FD4A6BULL, 0x428C1A8D9E2502E7ULL, 0xCC349665B0150E52ULL, 
            0x4078943DE333DB66ULL, 0x251F5E2C1AE105C5ULL, 0xA862AC00087227E4ULL, 0x2D80E14D3F697D0AULL, 
            0x09B5E7BFAD1AF424ULL, 0x36DD20603E19FD43ULL, 0x593FBA2E617368F1ULL, 0x222EAB7D7B97D3EBULL, 
            0x2E90A00DEF7412C8ULL, 0x829BB1687F8A0EA2ULL, 0x2B95C557939DDE83ULL, 0xD39FA7B4F0142DC7ULL, 
            0x75F470E5C3DC3D72ULL, 0x285B94D494CB20D0ULL, 0xA5A3E85AEC694904ULL, 0x0FE7C6F4CE2BC78DULL, 
            0xA4DA5007F2496BD5ULL, 0xE2A9F58BFF1D56A0ULL, 0xCA9E5FA752277C50ULL, 0xD7C0425F1134C9D3ULL
        },
        {
            0x36BE28EE011C120EULL, 0x6F8F5731325CCA6BULL, 0x8FFC237F97DF5323ULL, 0x34B16DE9BFB3AD2EULL, 
            0x4B5C7CA87CD9553EULL, 0x141F143C88101BA6ULL, 0x466EC568F868CE8BULL, 0xAC0E9FADD43F5B45ULL, 
            0xBF47F7C6B3D0E475ULL, 0x17544C7FD4E47ED6ULL, 0xE3F4FF8E6EA122C4ULL, 0x6B28A983FD014AFEULL, 
            0x5E6F6B67782088ADULL, 0x9BF528AA936133CEULL, 0xBB12D6D7853BED38ULL, 0xFC801566275156BEULL, 
            0x001624AA6E0CF18CULL, 0x78CA4746A12E2CCBULL, 0xD95E3721817FA0F9ULL, 0xD49898C53F599C20ULL, 
            0x8E1A4EC6133324DDULL, 0x9CCD824C924F957EULL, 0x0B7DEA156786638AULL, 0xC217A3419018A8CAULL, 
            0x6CEE6D1D14702FCFULL, 0x1CBE63A484984707ULL, 0x05B1FBA2C082CCC5ULL, 0x98D519772CE6F74FULL, 
            0x83F13C8E94E7CB7FULL, 0x0F56E4B1CA246915ULL, 0xC88A34E5EAD0CAF9ULL, 0xCA264D7D5C4F8BE2ULL
        },
        {
            0xADA4A6574DE2B5D7ULL, 0x1611F1ABCA3BDCFBULL, 0x3A93656B9AAF9B64ULL, 0xB59FBD38B30E89C8ULL, 
            0x63594ADEEB79F566ULL, 0x6DC76F06DC7CC08FULL, 0xA52578EBDFB4466AULL, 0xD48CF67291A082BDULL, 
            0xB9B2097882F71176ULL, 0x304F138F11644E42ULL, 0xD682F81DCEF93DC1ULL, 0xB0E494E2596BE778ULL, 
            0x51AA2083082CDB4DULL, 0xA3E435B1AF660007ULL, 0x3E0267B1A2B83807ULL, 0x35B163CAFF3CEEEAULL, 
            0x7D8C4131DA5B4F69ULL, 0x76DC7AB67DD8B3C0ULL, 0xA9DE329E1242A568ULL, 0x9545DFC4FF0B8294ULL, 
            0xFCB379178F473DB4ULL, 0x1ACF60D5D827FBC6ULL, 0xECDAED930525D968ULL, 0xBF1F323CBF50EC77ULL, 
            0x1D93CA8625E3C0B1ULL, 0x89184F70392D2BB9ULL, 0x5EA82B7809737027ULL, 0x10567F3B008736BDULL, 
            0xBD882017DEFFB801ULL, 0xF1B3A9BF649A2CB7ULL, 0xC0D727131AC989DDULL, 0x03BAC3D200F2BB42ULL
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
            0xA931E407EF6EECFEULL, 0x004F25182DF82B6BULL, 0x69CA401250AF23ECULL, 0x950EEAE4890B07C5ULL, 
            0x7D652DD3BC74B596ULL, 0x35D4A0C43FF96C57ULL, 0x058E527DDF5239E9ULL, 0xC7AFFA2E4E0AAB37ULL, 
            0xA0DABBF548C654ABULL, 0x6E687543A248B112ULL, 0xB948D615B6564165ULL, 0xA4BFD411717AFF41ULL, 
            0x75693F021C053324ULL, 0xAE5ACED0487E7910ULL, 0x0EF6259CB6E55A32ULL, 0x2E4750AE11823F9EULL, 
            0xF801B1336DF15A28ULL, 0x94EDF8A67F0BF8CAULL, 0xA00C3653D0B4972DULL, 0x7915E4820F0C67EDULL, 
            0x4E9B5300CCF5C70DULL, 0x5491857EAED9F890ULL, 0x0197492BAF1712E9ULL, 0x52ABE033B3504809ULL, 
            0xA4F8320D322C06E8ULL, 0xF3BDAFF3BBF48912ULL, 0x4A0D5557BD9DDA73ULL, 0xB2219E3E82E5962FULL, 
            0x20F402B135710613ULL, 0x060201DCC76A5BEBULL, 0x8F4998B6BBDDE5AAULL, 0x9AC5770FC0CFA74BULL
        },
        {
            0x94290D84AEE68515ULL, 0x3A8A3744DC371103ULL, 0xF9544A001A5CD7B7ULL, 0xECA52B20C6C00AF8ULL, 
            0x8568ACABA0E462ACULL, 0x7EB3E47904EABC84ULL, 0x51F2BA0DDF761E12ULL, 0x45F5F276BC455131ULL, 
            0x2E3054FAC41453C8ULL, 0xAA40CECC5DC56012ULL, 0x3406FD9E2C705107ULL, 0x4B968D17DCD9917BULL, 
            0x383FDDACEB486C27ULL, 0x4F6B492F9545F6A8ULL, 0x030C72E2652BB9F4ULL, 0xF41F3049848BF8EBULL, 
            0xCC121C0D688D1BD5ULL, 0xD371DADDFE7DD1B7ULL, 0xF6D078F1B030CE30ULL, 0x42EB0C93D4DDA527ULL, 
            0x3F227A11E501F8F9ULL, 0x16B3534437D21D35ULL, 0x1608E43997537DECULL, 0xDE2700050E39A735ULL, 
            0x29739AF346C2B146ULL, 0xF269622E7B568E45ULL, 0x202B26E1118E503CULL, 0x2D412EDBD012EFA4ULL, 
            0x639CC7EFEC76D9C3ULL, 0xFAAA28581BA9E3B6ULL, 0xB53BC51403E1D844ULL, 0xD53F1FCD46E44C64ULL
        },
        {
            0x1B8C04FEC275A2E8ULL, 0x87E63D65993E83AEULL, 0x874E0052FE23702BULL, 0xF9C0245C3AC4C67EULL, 
            0xC4B84CE47939A2F8ULL, 0x72A97189104F10BEULL, 0xB928BFE694B668CFULL, 0x7F90ED6AE1BD2A36ULL, 
            0xE4E91E852D014744ULL, 0x61E04608EC1D5355ULL, 0x8AE8AECE74948118ULL, 0x3CE027F846F15674ULL, 
            0x80482B13E365ED43ULL, 0x2492ACB1E8765793ULL, 0xC58EFDC95ADB9ACBULL, 0x1C877229DA7D4580ULL, 
            0xB5F8FE58ACDCC46EULL, 0xC8AEA93C76B43FD3ULL, 0x1D5368F9D6943A12ULL, 0x96B43555EB3D167AULL, 
            0x2902A6AAC9B23D20ULL, 0x770978E532289582ULL, 0xF5FB212965EB0AD8ULL, 0xE40273455CE4A3FDULL, 
            0x507BF7AE39BD06C1ULL, 0xA9B93B37D60E9BCEULL, 0xB10F8125269B9D9EULL, 0x2B7BD44BBA4195E7ULL, 
            0xB5812B1D740C1140ULL, 0x3F59294CE76F2850ULL, 0x440F0543077AFED0ULL, 0x4E882A8510FFC692ULL
        },
        {
            0x1509DF8D2CF5AA7CULL, 0x9A379F176295EA29ULL, 0x5F1D46F3F2929F8EULL, 0x7606407BAEEF5DD2ULL, 
            0xA0FD488FF7F02D92ULL, 0xB21948D4A744D340ULL, 0x561927AFF2D987CFULL, 0x36FD8505BAAE84C4ULL, 
            0x355AF86A3D8763D6ULL, 0x90BA23293A96A4CFULL, 0xE245FCC07C6DFBC8ULL, 0xB19DEC916E3DB932ULL, 
            0x33B84A9372BE3021ULL, 0xB9BBF24FD260B471ULL, 0xB9E91C049EC93549ULL, 0x269DB65B1889244FULL, 
            0xF0CB78E452AC46E8ULL, 0xFB90F95D7CB4CCF9ULL, 0x03BE950FEA34309AULL, 0xBAD311EDFAC7E879ULL, 
            0xB54BF7387E9F26F0ULL, 0xA4C00B319563C1D6ULL, 0xB3C76B9F92BA8148ULL, 0x8530C89093FCA8DAULL, 
            0xCD7AFD4C88292084ULL, 0xE1081EAA1E3D3718ULL, 0xA576B97EDA39F0E7ULL, 0xF466051183797358ULL, 
            0x925A01DC457BAE19ULL, 0xA38A09EC1B20331DULL, 0xE23E261CB21946B3ULL, 0x89BA9D89CFA9FA03ULL
        },
        {
            0x5209C3FE9BAD0B8BULL, 0xFF225A8A1D98DC1FULL, 0xA59B5B259D87D895ULL, 0x89B75D28F2CB8593ULL, 
            0x7B9E5A814920EFD6ULL, 0x53B6899BB7FD926EULL, 0x9FAC7409E96D4509ULL, 0x74DB65A87DBAD09CULL, 
            0xF0537BCF49BDE834ULL, 0x7D31C5E6B1E2C251ULL, 0x064B8B2938088748ULL, 0xA684E45F560EF129ULL, 
            0xFE83B60A3D72814BULL, 0x89540B108762B1B4ULL, 0x24034B470780C577ULL, 0xC16E554BBCE0F9B0ULL, 
            0xA0ADCA297A9295DCULL, 0xDF868699D04FEFFAULL, 0xD49E5BA4FC93E2EDULL, 0x15B8CD11DB72BC5CULL, 
            0x4FFC162F4E2DA514ULL, 0xAEFE81B9510C2470ULL, 0x83628B15770EDE0BULL, 0x631D684505C47438ULL, 
            0xE891256BA2B66785ULL, 0xDE3DD0B807EF7C6FULL, 0x272E5D11D8FC7127ULL, 0x2D3D38CE3BB29020ULL, 
            0x3F328B5C2246BEBFULL, 0x3D5EFE97D86063B8ULL, 0xC6EB043875FF9639ULL, 0xCDE43BF28DBA493DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Gemma::kPhaseHConstants = {
    0x8E004624A4CACCA4ULL,
    0x5FC064A45FF13FB9ULL,
    0x779EB65758ABB224ULL,
    0x8E004624A4CACCA4ULL,
    0x5FC064A45FF13FB9ULL,
    0x779EB65758ABB224ULL,
    0xEE6F7B6E35DDFFA7ULL,
    0x8C103E0D487D8562ULL,
    0x19,
    0x30,
    0x92,
    0x1A,
    0x75,
    0x9D,
    0xD0,
    0x7A
};

