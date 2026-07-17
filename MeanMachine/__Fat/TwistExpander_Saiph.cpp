#include "TwistExpander_Saiph.hpp"
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

TwistExpander_Saiph::TwistExpander_Saiph()
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

void TwistExpander_Saiph::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB4B435C6F75AF8E7ULL; std::uint64_t aIngress = 0xAABE1F9C2A436A09ULL; std::uint64_t aCarry = 0xC7EC275F64077D37ULL;

    std::uint64_t aWandererA = 0xA8089AF916F76734ULL; std::uint64_t aWandererB = 0xE845CD2AEC039955ULL; std::uint64_t aWandererC = 0xC4D3AD937BCC3893ULL; std::uint64_t aWandererD = 0x969664E66B2CDC3AULL;
    std::uint64_t aWandererE = 0x99EA06583181B8AFULL; std::uint64_t aWandererF = 0xB02886916CFC0A63ULL; std::uint64_t aWandererG = 0xDF068315E70C9318ULL; std::uint64_t aWandererH = 0x85D1F99CBD081FB5ULL;
    std::uint64_t aWandererI = 0xCAFEDCC9856BB26CULL; std::uint64_t aWandererJ = 0xCB90EA294CA584A8ULL; std::uint64_t aWandererK = 0xE1525C75CC021965ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13707307647317425020U;
        aCarry = 17998455432719767908U;
        aWandererA = 17071064390748205185U;
        aWandererB = 14890395574640549037U;
        aWandererC = 17515394424967568008U;
        aWandererD = 17064361307919618550U;
        aWandererE = 10385723074222476942U;
        aWandererF = 14514721625290560860U;
        aWandererG = 10969232050336148628U;
        aWandererH = 18015494786788461736U;
        aWandererI = 18316669235279425755U;
        aWandererJ = 13867244927537478240U;
        aWandererK = 9778153781187867111U;
    TwistExpander_Saiph_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Saiph::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8A24EADF8410425CULL; std::uint64_t aIngress = 0xB7E2EA992F4B9286ULL; std::uint64_t aCarry = 0xB112B50636874047ULL;

    std::uint64_t aWandererA = 0xF6107140FBF3704EULL; std::uint64_t aWandererB = 0xBEFC6E6432F03ECBULL; std::uint64_t aWandererC = 0xEBEC4217097792DAULL; std::uint64_t aWandererD = 0xB3FBF2E55C19F8E9ULL;
    std::uint64_t aWandererE = 0xF9F4A001E18EBF19ULL; std::uint64_t aWandererF = 0xE931A6D5980B65F1ULL; std::uint64_t aWandererG = 0x97A8ED367B8E33D5ULL; std::uint64_t aWandererH = 0xF239005DA03DE7FEULL;
    std::uint64_t aWandererI = 0xB4F5400F9A405F78ULL; std::uint64_t aWandererJ = 0xCF101E19A4E865D5ULL; std::uint64_t aWandererK = 0xA34C15DCBEDC7C6FULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12437987321266766897U;
        aCarry = 12856651512650078385U;
        aWandererA = 16742682697048081150U;
        aWandererB = 17567472974484722924U;
        aWandererC = 12403130511764613270U;
        aWandererD = 11256823400234691549U;
        aWandererE = 11748141077589316475U;
        aWandererF = 11709426615255307553U;
        aWandererG = 15113340750680502723U;
        aWandererH = 9295121266504470047U;
        aWandererI = 9962710755413383243U;
        aWandererJ = 16517507847416731902U;
        aWandererK = 18080531901516400361U;
    TwistExpander_Saiph_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Saiph::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC1CADF64C2CA6B0CULL;
    std::uint64_t aIngress = 0xABA8A39B703A25D4ULL;
    std::uint64_t aCarry = 0xC648283DBC79C980ULL;

    std::uint64_t aWandererA = 0x99D87B090064F2B5ULL;
    std::uint64_t aWandererB = 0xBDE30942A0503E17ULL;
    std::uint64_t aWandererC = 0xC1C232518718BC4CULL;
    std::uint64_t aWandererD = 0xD715305BC2A2DD17ULL;
    std::uint64_t aWandererE = 0xC15A6AD1016F0BC6ULL;
    std::uint64_t aWandererF = 0xA43D16E07973687CULL;
    std::uint64_t aWandererG = 0x8F30C02B5AC735F7ULL;
    std::uint64_t aWandererH = 0xD657C7529C9AB44CULL;
    std::uint64_t aWandererI = 0xCF0497E7BA771576ULL;
    std::uint64_t aWandererJ = 0x83B41AECF8A9A6C6ULL;
    std::uint64_t aWandererK = 0xCA882166A11815B7ULL;

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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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
    TwistExpander_Saiph_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    TwistExpander_Saiph_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Saiph_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Saiph_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 30 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1782 / 1984 (89.82%)
// Total distance from earlier candidates: 52654
void TwistExpander_Saiph::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1064U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 573U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 405U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1781U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2040U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 35U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 39U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 867U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 597U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 142U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1873U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1803U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 269U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1755U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 609U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 234U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 50U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1713U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 711U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1088U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1733U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1784U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1558U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1715U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 774U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 122U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1632U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1018U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 588U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1654U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 495U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 260U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 22U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 997U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2029U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 656U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 567U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1875U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 978U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 308U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 505U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1772U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1474U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1334U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1637U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1242U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1025U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1515U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 783U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1495U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1665U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 539U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1255U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1436U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1961U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 520U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1499U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1097U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 54U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1096U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1382U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1508U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 954U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1533U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1331U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 270U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1764U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 551U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1308U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1037U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 896U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1583U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1073U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1013U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1817U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 714U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 671U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 76U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1345U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1186U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 979U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 502U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1036U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1830U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 974U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 771U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 453U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 932U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 791U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 289U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1403U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 393U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 69U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1463U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 326U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 988U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1045U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1903U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1298U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1880U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 629U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1167U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2024U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 818U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 279U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1205U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1628U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 703U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1643U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 433U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1027U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1641U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 904U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1919U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 186U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1051U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1117U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1540U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1615U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1207U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Saiph::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x91688C02E9B44933ULL; std::uint64_t aIngress = 0xC943126873329E69ULL; std::uint64_t aCarry = 0xA2BC462C649E6BF2ULL;

    std::uint64_t aWandererA = 0xEF5D877F1667677AULL; std::uint64_t aWandererB = 0x910CD88B9098A7F5ULL; std::uint64_t aWandererC = 0xC026F0150E3F1E71ULL; std::uint64_t aWandererD = 0x886A7A80F4DDF695ULL;
    std::uint64_t aWandererE = 0xB19279BF47ACD3E1ULL; std::uint64_t aWandererF = 0xA20C22C94544A702ULL; std::uint64_t aWandererG = 0x8A51659AFE1A8DA2ULL; std::uint64_t aWandererH = 0xE4558E2FAE857FADULL;
    std::uint64_t aWandererI = 0xF04E3DD958A4A4DAULL; std::uint64_t aWandererJ = 0xA5B37F7C25B242F3ULL; std::uint64_t aWandererK = 0x8E6515C4426D22C9ULL;

    // [seed]
        aPrevious = 9890135524139003988U;
        aCarry = 14278198342035561302U;
        aWandererA = 9441531898020395636U;
        aWandererB = 14091008162218592732U;
        aWandererC = 13942214708407878101U;
        aWandererD = 11810526320678386321U;
        aWandererE = 17530428087680734625U;
        aWandererF = 18193251865518368327U;
        aWandererG = 11323121825546812702U;
        aWandererH = 12198503050179716138U;
        aWandererI = 15095107234538791421U;
        aWandererJ = 17579446624761995567U;
        aWandererK = 18238833117392095162U;
    TwistExpander_Saiph_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Saiph_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Saiph_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 30 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15681; nearest pair: 498 / 674
void TwistExpander_Saiph::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5534U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5398U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5835U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5454U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3810U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7516U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 455U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6060U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1172U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1672U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 24U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1560U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3110U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6262U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 984U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3950U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1560U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1443U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 842U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1635U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2042U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1282U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 12U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 960U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1681U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1504U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1999U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1482U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 818U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1118U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1473U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 816U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 374U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1040U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1744U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 30 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15681; nearest pair: 467 / 674
void TwistExpander_Saiph::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3799U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3536U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1063U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6927U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4310U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6914U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6575U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7084U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1055U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5404U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2267U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 968U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5474U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1384U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3857U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7376U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1564U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1377U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1847U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 631U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 805U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 998U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2021U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 259U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1909U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 55U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 63U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1980U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 224U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 525U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 625U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1688U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1204U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1277U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1035U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseASalts = {
    {
        {
            0xB9D631994010250CULL, 0x47656A6DABA1FDF7ULL, 0xF4FD5E8DC7E137A8ULL, 0xD0811477E5D82829ULL, 
            0x269015F96E2F8DAEULL, 0x5D6BFD8B3F8B14E9ULL, 0x3420FB4A1FB0EC28ULL, 0xB965FD73C6AB460BULL, 
            0x8416F2280327ADE2ULL, 0x6A8C29ADE2733C3DULL, 0x42004AB060DC255FULL, 0x066F7A188F7495EFULL, 
            0x3EF26391AE13D377ULL, 0x5D7E042664F02E66ULL, 0x31EC1692BB8F6605ULL, 0xD708DFE5D5FE32CCULL, 
            0xF3C22B5FEDE75838ULL, 0xD0C9EC2A3B03F56DULL, 0xFFDB264583B76B7FULL, 0xB69CD8BC2CA8E24FULL, 
            0xEBA61D8E76F93DCAULL, 0xA3B2FEED2F40C058ULL, 0x73C7294DBF44979EULL, 0x8F444BC0B246A174ULL, 
            0xA1FE19950F61F4D2ULL, 0xDF7DE3420E3E2F40ULL, 0xA7038F25B4471696ULL, 0x6117E1F520306F49ULL, 
            0x34BDBA429D8739E1ULL, 0xB04473F94AE05422ULL, 0x0C47C07DBC1A6D9DULL, 0x7781C7FD7F502D02ULL
        },
        {
            0x540403871E776741ULL, 0x3DDC4FACB89F40F0ULL, 0x32EE51A786510985ULL, 0x4AE40CD7B420E4ABULL, 
            0x11C71E8363101EFEULL, 0x6D17B9EFC46DD9D7ULL, 0x86EA5F607B8D113CULL, 0x3BAF8B5B0CCA82A6ULL, 
            0x5FC2B2A4F1D92CF2ULL, 0xF67DAD08BBB8C8ABULL, 0xE2C5E9A90B3424B7ULL, 0x8EDC3329B864545EULL, 
            0x815C0D77BEE43024ULL, 0xFA06C32948819A26ULL, 0xE3062BCEBC0A47C3ULL, 0xA5E06C2CABEA705FULL, 
            0xA49E33539394084CULL, 0x08D728EE8EC9E577ULL, 0x92ADFEE96F204A14ULL, 0x3CCC5436388A5A2CULL, 
            0x51158DFFDC07563CULL, 0xA40F7D114F3BBD0AULL, 0x6B23DCE11A2FF9CBULL, 0xC9DC2FB94166898DULL, 
            0x168FBA709EDFE159ULL, 0x50B306F57D25DD2AULL, 0x65B136BAE6EDA1F6ULL, 0xEE91F34ABDF89EE6ULL, 
            0x48E515C7F0F693FEULL, 0x38894DA997652A36ULL, 0x82A548BE99D22E16ULL, 0x84E0A41946EB0D0FULL
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
            0x937169C3AEA89A1AULL, 0xA53C2B7BDDC843C6ULL, 0xD3EADB92CB286E9DULL, 0x68AFCD973D5E663EULL, 
            0x6FA5C8AC79DDB34FULL, 0xF0C7D7D8AFD8301CULL, 0x1B4606E98CA0F321ULL, 0x038B326F237E89BBULL, 
            0x67A86DEAF7A506CEULL, 0xBF66595CDAAEF387ULL, 0xC77135DB5B7EBB15ULL, 0x8D1DE34CF9EE32DAULL, 
            0xF8A215D79A9518BBULL, 0x18127C76831BC207ULL, 0x406448CC5C66F4F8ULL, 0x3DE78FD23FF68949ULL, 
            0xB7FADC71905B7C32ULL, 0xD9DFAE98E3813BB6ULL, 0xCD44A649844ACB4AULL, 0x4D624B56BD2DF13CULL, 
            0x78AE5550AB8690B6ULL, 0x37655A0FC5B20E6FULL, 0x6E7F4E609427111EULL, 0x96083A9DEE892B9AULL, 
            0x7E1B9B8C6100776AULL, 0x35F8DE8F1A56B79EULL, 0x1DAFD17BA0221028ULL, 0x55E2B79B84B2CF76ULL, 
            0x200E6A6CE5FD14D6ULL, 0xF99AAD3314653705ULL, 0xAFE435E4C1C0A075ULL, 0x02EAF23B91BDBC71ULL
        },
        {
            0x1CFD0AB01D888935ULL, 0xF691141468B9D68FULL, 0x57747EA2E1F21D9FULL, 0xBA3907D45A0E6B3EULL, 
            0x88906E48B98ACF2FULL, 0xBBDA6E52795F6124ULL, 0x8AE029CE301498F6ULL, 0x7E8CF46CCFEDAB86ULL, 
            0x03E8D3891408B496ULL, 0x4448790BE7267208ULL, 0x693ABC8EBA7EBFD7ULL, 0xA64659FA2E947BD6ULL, 
            0xABCEE78695206DEAULL, 0xAE6DFE17282D8178ULL, 0x3A5D164D8DF25622ULL, 0xA96C018A074CFD6DULL, 
            0xE29D17AE7CB555B4ULL, 0x2609735A3CFA301EULL, 0xA02EA2833B62D539ULL, 0xFE29B76719DFDEB7ULL, 
            0x8241AFCBD47D94C6ULL, 0x8AC0EA00AA82FADDULL, 0xA183D1AB9B06D937ULL, 0xC11804A61AE85AC9ULL, 
            0x12F0554FCFB0C12EULL, 0xC3994F7B82700BCBULL, 0xD440178389F78E3DULL, 0xC308EAAF11CDFB9EULL, 
            0x924FFCEDE3509231ULL, 0x0F984FA718A0481BULL, 0x8F33DABBEA804DE9ULL, 0x2158D369F0C56E28ULL
        },
        {
            0x2F8C248EC1F17A19ULL, 0xFB0C6EBA18E90034ULL, 0x5218B0E14F175609ULL, 0x5D9EE35864F2F880ULL, 
            0xDF7743C1F0CA61BFULL, 0x322F0489D8418112ULL, 0x9F4795AD31754A87ULL, 0xC6931571AA829AAFULL, 
            0xA01346ACE1E49916ULL, 0x9536B827A8625FEAULL, 0xF22AC0DEA751D028ULL, 0x3C5095794C62FE0EULL, 
            0x63150491A1EB97CAULL, 0x32F6799A55CCE8FFULL, 0x9B4D94AA401EE09AULL, 0x54A21106EBC7C445ULL, 
            0xD480FF0DFB61885EULL, 0x596B352973928712ULL, 0xCF2B72465838B56FULL, 0xBE5F8A887D67DC9FULL, 
            0x5A64770A81DD5018ULL, 0x99135FEB9E520CF2ULL, 0x213EFBF5E828C2BDULL, 0x09426256005D00CAULL, 
            0x5CC3180846764143ULL, 0x9DAC52F7DFDF2442ULL, 0x3CEF024D529804ACULL, 0x5F7E5E920CAE3766ULL, 
            0x0E994C02810B2619ULL, 0xB8611A8E820B6FDCULL, 0x377420D0E042C035ULL, 0x6E41E73FEAEAD031ULL
        }
    },
    {
        {
            0x526D40E97A1CD470ULL, 0x9791E424D4625564ULL, 0xFB9B79C7D9BB0C9EULL, 0xD4A03B13C917EFA7ULL, 
            0x8B6D855A04F28BC3ULL, 0xDD97054A5BB36254ULL, 0x49260E8A9A89466CULL, 0xE014B0E8CD69E287ULL, 
            0xB162AEF2D12B8576ULL, 0x118B4A3A4ECE1727ULL, 0xB63668A548199BDAULL, 0x5C171C302CDDA0AAULL, 
            0x7E536C3A522A6F1EULL, 0x5F0118FA2FD2C8CBULL, 0x32B0A4ACD84F9193ULL, 0x0416AC02594979A5ULL, 
            0xF1F174AC1A153F66ULL, 0x64E1D21633688052ULL, 0x12E30BA50BC4C94AULL, 0x5B9AF7572058C484ULL, 
            0xD5C52AD8915AA99EULL, 0x296EBF658BEBE4B2ULL, 0x093F2EB5429F7D77ULL, 0xC7BEAD35DF6873B6ULL, 
            0xA294F27CB0063BAEULL, 0x1F4852CB417E7CC7ULL, 0xFCAC85024DC8F78AULL, 0x230F03A6E318F33BULL, 
            0xE6CE6761C3D7FBEDULL, 0xDA456291713FC1C8ULL, 0xFBE4BDB041A2F63EULL, 0x67C46D2C189F2A65ULL
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
            0x3BE1234806644F11ULL, 0xEA4958455A7D9763ULL, 0x1DA6F23BF8E0C9B7ULL, 0xE6F79AB0F14BE789ULL, 
            0xFA127CFB3E8A1683ULL, 0x15A95B38E415EEC1ULL, 0x2DC721290DE6892BULL, 0xF792A75F76DF9CD1ULL, 
            0xF83827311EA89407ULL, 0x0A6349701FD01BC5ULL, 0x45DD3707370E3C67ULL, 0x48FD265054C3F6CEULL, 
            0x87970097FD249CADULL, 0x0A7B5C964D5A2B09ULL, 0x8E88FBBBF432CDB4ULL, 0x3CDE84A6E0B5034CULL, 
            0x0BAABAFB70E83EB3ULL, 0xD28F09A804A0BE45ULL, 0xCBD9DCE5EF691470ULL, 0xF4C007CF0CE3B415ULL, 
            0x37D0C9CC0B7BAA89ULL, 0xDFBED67A8D66D371ULL, 0x9DD21AA736B43D83ULL, 0x238B9CF1D834A3D7ULL, 
            0xA7C243F0E565E618ULL, 0x739338696146D226ULL, 0x69F03690FD14616EULL, 0xC7FB3F22831E4327ULL, 
            0xC278BD18D89E0821ULL, 0x55F87DED62E766D4ULL, 0x92FEC0396D7CEC23ULL, 0xFDEC9DBE25145931ULL
        },
        {
            0x1034A64E9AD73DE9ULL, 0xEC08F6F3240DC25CULL, 0xCC453F2E24473F1FULL, 0x87ECE0BF2C61A7F3ULL, 
            0x3EF012E9760DE6B6ULL, 0x57DAF4687D19ACA8ULL, 0x5A020B92C855771EULL, 0xE53CF8C52613655DULL, 
            0x8F2FA0BD648735B9ULL, 0x52FB5E00826218F6ULL, 0x9EB68B3642618475ULL, 0xAC4984C2CD193460ULL, 
            0x86A51B9282879584ULL, 0x6E3DF3F5FC81E1E7ULL, 0x90F6A393D20D38C2ULL, 0x80D2E75952FE9974ULL, 
            0x490615400892B463ULL, 0x789049C8DF54CFECULL, 0x37272B03DD608398ULL, 0x33B811BB3C46B663ULL, 
            0x8112CC5FB33268E2ULL, 0xF1BFDBB8F087C8DBULL, 0xD7C57242D7FDAEA9ULL, 0x713EAB232AC65847ULL, 
            0x9F285F147E38EF4EULL, 0xDC239E0599B902D4ULL, 0x4806CF96D7DB8FF5ULL, 0xACC3B94CEAE8434CULL, 
            0x9F7D8E3A30FCB999ULL, 0x5378E5F400F17716ULL, 0x2531E1CC2BDD08F0ULL, 0xFFB92D8DECCFF14BULL
        },
        {
            0x5F5A787D4687BB6EULL, 0xA738B3446519B14FULL, 0x10AFA407DCBDC109ULL, 0x0CE8C0A8984DD67CULL, 
            0xA6646B23F6730B20ULL, 0x9C5425BB5BF6A7D1ULL, 0xB8B50910D48D9B1FULL, 0x1BFC7B940B532457ULL, 
            0x1F258E812C1B9479ULL, 0x2E5E4CB1CB20A7FCULL, 0x512CD17AB50490A3ULL, 0x4C65FA6846ACB4BFULL, 
            0xDDC9319130D34F11ULL, 0x885D22F0F4EFBCD9ULL, 0x28F6825866A2F2E7ULL, 0x8608ECA7D60045FCULL, 
            0x797C1D69375089A3ULL, 0xA7BD9879592265C5ULL, 0xFEB2EFB1C2C15F66ULL, 0xF7DB8B2221901C5DULL, 
            0x6DDA28F988D3FB85ULL, 0x2752DEAF301F7269ULL, 0x3B7CBCA9F4D90B78ULL, 0x20D338155D112522ULL, 
            0x5B1C7D5E85DCA5BCULL, 0xB25A5CFE04F03731ULL, 0x63B370648CBA674BULL, 0xF01D804FC583F469ULL, 
            0x0E8A47D5A7A53D4DULL, 0x1501F4A3B487827CULL, 0x2972A8AE1A217C00ULL, 0x66E6A67B5C77616DULL
        },
        {
            0x64368460B13902E4ULL, 0x21B20A71E9367F79ULL, 0x87B1A5705F784975ULL, 0x7B20F164FBEC9DCEULL, 
            0x148B6A66D03A720CULL, 0xAB9A5533A91557D1ULL, 0x2ED1EBC53DD703F4ULL, 0x75DFA7A1B6AAC66DULL, 
            0x2919B748751984EAULL, 0x02798AE6571B0CA6ULL, 0x821A73E4ED1DCAA6ULL, 0x0E85D6B122F6446AULL, 
            0x85D2BBC1534BE189ULL, 0x8CE6416C3065A05BULL, 0x22DC63DAF6B1B750ULL, 0x427D6CD5E088A17CULL, 
            0xA3C4DC9731651931ULL, 0xB6B95827AD618B49ULL, 0x52B5D312CC4DA8D4ULL, 0x092E236E98F1ECEEULL, 
            0xBDF6D30362828C9AULL, 0x1B50C1237D5CBF79ULL, 0x6337B61D66BDD9BBULL, 0x71944D6882951EAFULL, 
            0xC77F6C42ED6B28BDULL, 0x11C64FC2B0B1CB52ULL, 0x35CFE8EDF4DEEDADULL, 0x31F2E756086A3E70ULL, 
            0x042597008267783FULL, 0x3046F5D2B6FE43C5ULL, 0x07A023E681625C77ULL, 0x99D63823844A1D4DULL
        }
    },
    {
        {
            0x590041E0D17E4450ULL, 0x8F7202A892BB5C4CULL, 0xB1167C2F8A2DF9EFULL, 0xF12DDCBA9709BEE0ULL, 
            0x736A1FCAAA31AE7FULL, 0x58939466C196A45AULL, 0xC208FC55A357CC70ULL, 0xFF3D211D3A5F2BF8ULL, 
            0x884AA104451C3C49ULL, 0x975145239B49CD11ULL, 0x85B22C54E5C4397FULL, 0xBFDD7EFF3F7B6FACULL, 
            0xBD9C7C2104F5876AULL, 0xBCB8997362446629ULL, 0x352D0C6BD81E0C5CULL, 0xD8563F12CC7C9A9AULL, 
            0x3D0B060BEA39D909ULL, 0xC53344E01F836504ULL, 0xD90F9AF3079AFFF0ULL, 0x8ECB098ABC67B6DAULL, 
            0x4253442B3FB4C1F8ULL, 0xB06D1428447CAA19ULL, 0x926F8784CB8441CFULL, 0x8537A2FF61D957BAULL, 
            0x7CA56693FECA3913ULL, 0x22E8AFE53CFCCCA7ULL, 0x48EA5EB31013B7D7ULL, 0x2F29669C333629C9ULL, 
            0xD4D20B7E9B58FFB5ULL, 0x6661F9AA4762D03CULL, 0x31B66ECACC590719ULL, 0x7B02E1E10841E288ULL
        },
        {
            0x461CA0C2BE47F2BCULL, 0xBC50172196FCF305ULL, 0x28150F49892F8194ULL, 0x458E0C4379F16977ULL, 
            0x7C963B444D6A21FFULL, 0xF45158019536321DULL, 0x5B0129E1F5A59C7CULL, 0xFFF6950A092E6AB6ULL, 
            0x4B6D36E3B93351EAULL, 0x0D5E4698C372F761ULL, 0x565D15F6533BD98BULL, 0x00EF086D6B76A27CULL, 
            0x43067DF269CCE0A2ULL, 0xEB925E81991C21DAULL, 0xA1688C5576A0ED74ULL, 0x412FCF22842F6A07ULL, 
            0x934489E136B22B08ULL, 0xCE7F5DB220D523E2ULL, 0x1E13C7153B260D5EULL, 0xD8564EE62B640B7DULL, 
            0xBA9D89FF390FE88AULL, 0x17C01A24BCF46BC4ULL, 0x9584658F202F7391ULL, 0x07CA3C414068932FULL, 
            0xC0EAF50362F71A20ULL, 0x1C627986459C7A0EULL, 0xEDBD8E25AA4D92E2ULL, 0x2F735412B1121E3EULL, 
            0x7B7A7105C217AFC3ULL, 0x12206603A886B4F2ULL, 0xD4AB57E98C1F90DCULL, 0x5F35436CE5275F80ULL
        },
        {
            0x8CB0582A00136F7BULL, 0x095E50EFC0168DEBULL, 0xEA16E947FA212ED6ULL, 0x63766E4865C43DA1ULL, 
            0xC1357248E8CFA6BCULL, 0x059548FC6F47B872ULL, 0x3814C844A5DE5045ULL, 0x6B1B38676CD31645ULL, 
            0x04EA53F01A3B9574ULL, 0x5B9FA32F94C5F84AULL, 0x24FDFFF2E4CC4EF9ULL, 0x90CBA46E81A96F07ULL, 
            0x6FBA26AF87DFED83ULL, 0x8956AB6F5E83C622ULL, 0xBA584959ACB7E120ULL, 0x9C277E33A929025DULL, 
            0x4BB30E7CE2735F76ULL, 0x4920071977C53B08ULL, 0xFF7FE4E466A0EFE3ULL, 0x3DCA5522D65CFB81ULL, 
            0xF89655DD4CD7D2CFULL, 0xD97AF99BE8D97AF8ULL, 0x32F32D00F2EBFC26ULL, 0xA73238F2A145077FULL, 
            0x2DF54F291F11C612ULL, 0xED59222DF2C8803AULL, 0x61AB7E146096FF74ULL, 0xC2E886B6FB668E8EULL, 
            0x44B2CE6232CB1D77ULL, 0x9C340F35B0C36807ULL, 0xC1A44FC4DAD15A67ULL, 0x47DE813511196284ULL
        },
        {
            0x7156C8D3D07F815DULL, 0xEEDF29743068D6A4ULL, 0xA6433758BB8CDE0FULL, 0xCD7300AE90FBCABCULL, 
            0x3600FA24EB8126B1ULL, 0x0FC6F0151A6D80DFULL, 0xEEDA0EF562CA16FEULL, 0x05D6C4D656D58871ULL, 
            0x39597D205A3E2E18ULL, 0x62087811401D7D1FULL, 0x36BF8856CC53C2DBULL, 0xD84D72B3D283A767ULL, 
            0xC4E26FCF7F0918B8ULL, 0xF43F601C3AA4DE08ULL, 0xA13E4CFBFD5C8698ULL, 0xF6825637D94E7930ULL, 
            0xC61C3D06E037B41EULL, 0x7AB2D2D09BF90A71ULL, 0x78870D559CA9D17BULL, 0x9687C12A812C293EULL, 
            0x10080BE362096DC6ULL, 0x45083EFC457C354FULL, 0x7347CFC6B0DDC18DULL, 0x20F2DD0094CDA7F7ULL, 
            0x52FB098DEA0259C7ULL, 0xCE992C888A1101EAULL, 0x3A157BA9C5D6D53CULL, 0x92AA030F3EADB605ULL, 
            0x0B7CDBE3064FCEB2ULL, 0x29BEA909B5B46DA2ULL, 0xD28B569DD4509C57ULL, 0xAE19CBD01833BF4AULL
        },
        {
            0xDE60DD40DDC9ACC9ULL, 0xBC2F09637C317D5DULL, 0xDD6AFB89CFE89128ULL, 0x71A0566AF5B50CBCULL, 
            0x1C445E61BCDA1F73ULL, 0x93BEE41850B3002EULL, 0x15D28115B3159DCBULL, 0x7D9BD8D94A210D76ULL, 
            0xE373EEE904BBB2DFULL, 0x83BEA009229F9FECULL, 0x1C7AF04E4269C7CCULL, 0x51AC76FF25B50FC8ULL, 
            0x75FA3CCA06D1F03AULL, 0xFBADC998D35C7643ULL, 0x890070476DE15568ULL, 0x1E1109770A327679ULL, 
            0xCDE08B5292C82957ULL, 0xBB74CC35DC181E7CULL, 0x17639AD8AE0B5535ULL, 0x2AAE75BC99BCFE31ULL, 
            0x17A68A316BB4F34CULL, 0x9C3F257E5CFAA846ULL, 0x999D8DF54EB76B1DULL, 0xD14F02628B8CFB45ULL, 
            0x59F15F9198DE3FB7ULL, 0xEA3D362944FCC780ULL, 0x53AB42E4B3F7E5C7ULL, 0x2396FF90398722DCULL, 
            0xA1ACD533765575C8ULL, 0x1F8AD0BDB134A04CULL, 0x52F86A86F4CBB290ULL, 0x8F333D4161338EE4ULL
        },
        {
            0xDFB962392952FA50ULL, 0xB45BC26A90AA85ACULL, 0x8529E93C4FA0B1C0ULL, 0x0D7AACFBCEFEDCECULL, 
            0x799BB14618E1A164ULL, 0x14B64A463E8B1078ULL, 0xDAC5FD246AAA3DACULL, 0xD9C60E028C3B4AADULL, 
            0x4327EAB907D0B987ULL, 0x98C907F8F317DE8CULL, 0xCF7A4526BB7F5122ULL, 0xBC1588B61E2BD461ULL, 
            0xDAACF560CC934D9DULL, 0x23C2882E84702DFDULL, 0x6CE7474F23C89995ULL, 0xCEEF44B42C0B62D2ULL, 
            0x697D2B118F6199C9ULL, 0xB3AAF26568AE3CA2ULL, 0x82AF248AA2FA8E0BULL, 0x3BB0DC80C0D45311ULL, 
            0x184F5327B6C72EA1ULL, 0x7FC5EF7F01217F68ULL, 0x43610DB9D4661CE6ULL, 0x8DE4D1E3586FDF2CULL, 
            0x400C507F16F85985ULL, 0xD0755C7D4E9B1188ULL, 0xBFA7582883857A94ULL, 0xAD861884BEBD5B3EULL, 
            0x4B3CB933049B15ABULL, 0x20B6D5BE52878925ULL, 0x8096C6A30AADF157ULL, 0xF94D66CAA9851C39ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseAConstants = {
    0x9A91E04CCB36C6D8ULL,
    0x0E1C5FE7E0E039C2ULL,
    0x6211ABC376C76C9AULL,
    0x9A91E04CCB36C6D8ULL,
    0x0E1C5FE7E0E039C2ULL,
    0x6211ABC376C76C9AULL,
    0x26C1B1DB222B4FDAULL,
    0x5D474C7C24FE212FULL,
    0x0C,
    0x8F,
    0x96,
    0x49,
    0x6A,
    0x05,
    0x6B,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseBSalts = {
    {
        {
            0xAF8D0DB486361BB5ULL, 0x8C8856FEE08B1330ULL, 0xA51D37F1E90B9F37ULL, 0x207B3443990DA283ULL, 
            0x8788895BF6E778B2ULL, 0xB490F9CD8C67F72DULL, 0xEB7DCE4EE78FBBF9ULL, 0xED26E8AB97DF5FDFULL, 
            0x12306747BCFFB62EULL, 0x09F4F652EC597FECULL, 0xC13FFF83DB568438ULL, 0xC0AC9C6548B27278ULL, 
            0x1FC9C2A952231190ULL, 0xA905EEC36242BEC4ULL, 0x0F6B85D5313D83BCULL, 0xD5C334F5F633426AULL, 
            0xB00564C7C3A9618BULL, 0x30B0C3D1D8167E0AULL, 0x0A976416C4D0C88AULL, 0xE47E99C28257AEC4ULL, 
            0xB29D3029F41D4443ULL, 0x83F9EA9C562B98C8ULL, 0x54FF113F599D5871ULL, 0x483D9A16409609CAULL, 
            0x4F386CC924858E3AULL, 0xF3D41000230E7BEEULL, 0x07F9D37BDCA5F8E1ULL, 0x3B45E8B263583F11ULL, 
            0x65E5393020EFF01AULL, 0xEBEB7A0353F0A226ULL, 0xBC9EBB14649F2D17ULL, 0x68F6E9E355FE4DEBULL
        },
        {
            0x25FBE272DDD3C067ULL, 0x16F8B926FB23206BULL, 0xB7D7F00251E75DC3ULL, 0x3C05BE68E984CFFAULL, 
            0x82CE2E810EDE0843ULL, 0x71F5FCB94DCBC248ULL, 0xBADAAE029CD8E11DULL, 0x63397F82C34DF879ULL, 
            0xB4F6EB23FA361CF3ULL, 0x2B91BA66CF4B0770ULL, 0xDC23A15CB676D1CDULL, 0xD401B92ACFA4A299ULL, 
            0x21703083BAFE0901ULL, 0xADDC3ED499BF28FCULL, 0xE8EB935B0AF2B9D1ULL, 0xB173A1301C0E19FCULL, 
            0x93F12000E5437395ULL, 0x5265DD76CF91451DULL, 0x895F69C75C55D5CBULL, 0x91FCBAFF7D51F0AEULL, 
            0x6013FD52F67D3AEFULL, 0x1E410E4912CAFCBFULL, 0x21EDD454638D928CULL, 0x7CCAAD727D6FBC35ULL, 
            0xF3A1623A29F2DF8FULL, 0x868EAFDEF56941AAULL, 0x1B157CE5BAD25887ULL, 0x9344ED78C692D024ULL, 
            0x8D9C404E4C35DA49ULL, 0x17F630DD1BD187C6ULL, 0xE4CA3D58678CC354ULL, 0x4A865ECAD26BB5C0ULL
        },
        {
            0x3321BB2E9EA02FFAULL, 0xA9AE474CD1D0CAD9ULL, 0xE54B1347BE09F91BULL, 0x7EAA435D615FEA85ULL, 
            0x015A29120F03221BULL, 0xF36C30B699C955AAULL, 0x5F01D0CF4436AED3ULL, 0xB6B2AEA692B59D59ULL, 
            0x6D20A715A78A1B6AULL, 0x410126D336CFB478ULL, 0x8AE775CF5BC8C873ULL, 0x1C4B34147258056DULL, 
            0x2C1F665701D659C1ULL, 0xCB81C18596F434BEULL, 0x6DFC6A534722CC1BULL, 0xCAC7F50852087CE9ULL, 
            0x39DB42F456B5AAA4ULL, 0xF544A3B229E670A1ULL, 0x6A357F1E7BF5477FULL, 0xBC417A0D815D9709ULL, 
            0x2430CB132CECE0C1ULL, 0x6075A533830934DCULL, 0x7C88C00FD6BB40A0ULL, 0x93B27609D4869E7CULL, 
            0xCEE9D85CEFFEE57AULL, 0x95D90F4B9265F201ULL, 0x51510E48D7C186B7ULL, 0x04492E3D5FBD7E1BULL, 
            0xA4936BA64FAF9235ULL, 0x20BF8E43253D61CEULL, 0x3C40D0ECE725DDA2ULL, 0xF3B992EBC94C6E91ULL
        },
        {
            0x49D1204572B3BB0AULL, 0x188925A8FB58B3B8ULL, 0x5E016EFB073CF69AULL, 0xBC65C2970D20A1BAULL, 
            0x9AC95ACE51294519ULL, 0xCD34443861A6F841ULL, 0xE8B8D45C6D2B0765ULL, 0x268C1E1C2DA914BCULL, 
            0xF453FF37957AE0CBULL, 0x90BFC3A466026BC6ULL, 0x053B130EC48A6318ULL, 0x40395C3623B5A621ULL, 
            0x36405C536F827CF6ULL, 0xA106E51A651942CEULL, 0x8B5AF262E7210F7EULL, 0x245761243AB3F2D4ULL, 
            0x1A66B3149ADEB046ULL, 0xC816208C4A432FFEULL, 0xF9BF01F036A2A6DCULL, 0x6D2D5E5900C28F0FULL, 
            0x8AFD2801873FE7E6ULL, 0x2FFF84D790CEAF78ULL, 0x2037053F3334E320ULL, 0x6E66BB7072B1F608ULL, 
            0x3A14D859E898A54AULL, 0x197F54F28D7F9DA2ULL, 0x9AFABFBF19255746ULL, 0xE49EE15D133024DCULL, 
            0x0A03539A93E7C112ULL, 0x1324D5C9B5BD9759ULL, 0x342DD133B191C74AULL, 0xDB70F24647C381B3ULL
        },
        {
            0x23EE698D27F96883ULL, 0xA087D4895FF95607ULL, 0xD9F753DB10A9E063ULL, 0x6E595A46F21B0162ULL, 
            0xB9548B95EB30FBB1ULL, 0x392C41F95208ABF1ULL, 0xA5D4B667BDF1E2BAULL, 0x9B0CB7A869D7D933ULL, 
            0xA5237EFD8A3D7BE3ULL, 0x7CDA18AD039A6352ULL, 0x05D1381F76746688ULL, 0x0ACE41EC13812E24ULL, 
            0x96133989F7615E62ULL, 0xC7C42C7A98550B28ULL, 0x943CD59CC5E6BE41ULL, 0x3AFED79F423EBE27ULL, 
            0x3308A6C93D5B67DEULL, 0x1CB739D0ACB6C371ULL, 0x1A503AD6AF07A188ULL, 0x84AEDE8E7C6505CEULL, 
            0xEAB54F9A747C7A10ULL, 0xA284D92E5A3B8A99ULL, 0x152F1F778773D439ULL, 0x14FF03DB181B07D9ULL, 
            0x2A5511ADF5AF8654ULL, 0xE3AB1392EC3ED2F2ULL, 0x3989D7D2D3DADB20ULL, 0x792A1F2DBDF0630EULL, 
            0xA9F3A863C06AAF58ULL, 0xBC08D6FDB2C49710ULL, 0xAEC246F701EB1966ULL, 0x9C752CC83784D59FULL
        },
        {
            0x0FCF5CC5A6899F3DULL, 0x37F1678ECE95B6C6ULL, 0x92E6448B9916A930ULL, 0x0299A294B26E84D9ULL, 
            0x5FE13563A5E5CCC8ULL, 0x3DF94A3AFCAC86E1ULL, 0x7CDA541DAFBFAC70ULL, 0xD1136674BBA31403ULL, 
            0xBD30D21C41D1DCB9ULL, 0xFD7AC25CE32AE9F1ULL, 0xBAED9D39559AF93EULL, 0xF879DF9FB67DDDD6ULL, 
            0x459F0E2E3390CA67ULL, 0x361187265770D201ULL, 0xBA418247E438AC21ULL, 0xB4237CB794DFD01BULL, 
            0x600BB65EEA59BB9DULL, 0xE138BBF31B702F0FULL, 0x6A51014EDA30C884ULL, 0xF1A05F3D39B7664AULL, 
            0xCC9463375748F789ULL, 0xBEA2DA1782279669ULL, 0xBA7FA78261B7DA27ULL, 0x920E47CCF9ABCA0AULL, 
            0x4524596FEDF2A4B9ULL, 0x88760124E7430CD7ULL, 0xCE9C0EB8483CD6A7ULL, 0x69F3581C4C519FAFULL, 
            0x855F31D1DF979D42ULL, 0xB770100B3600A00AULL, 0xD7B43DA49B9DE155ULL, 0xF73A0E354F8DA6F4ULL
        }
    },
    {
        {
            0xBD3F4406BB2703EDULL, 0x11CD6BF64876733EULL, 0x8F35E30CC9E89BCAULL, 0xE8F0B6F506A02A47ULL, 
            0x1DA6E2070C26C900ULL, 0xA00EDBA6D9556555ULL, 0x4B925C30E1CA02B8ULL, 0xA99A5ACA369AE320ULL, 
            0x6F8F6AA7BEC119F4ULL, 0xEA58ADADD571C818ULL, 0xF8E85E223C7C6FE2ULL, 0x5D55A9345F685A35ULL, 
            0xA5625ABDA97E156EULL, 0x50D489A8CB995CBCULL, 0x0939619EEF269D87ULL, 0x27DE323D2891F52BULL, 
            0x81628D77E1CD516BULL, 0xFAE530DD76E11A11ULL, 0xC395418987B8548DULL, 0xB1598D33250F477EULL, 
            0x1F1C893181B8D74FULL, 0x4CF394FBCC3C306BULL, 0x98CE1E6036A10874ULL, 0x10F1DF4F269AFDCDULL, 
            0xFF4CCE47440B2ECEULL, 0x075D12395F7F55A9ULL, 0xCE8F27FD37BDC7FFULL, 0xF667A9FA9887061CULL, 
            0xF4AE032264710B07ULL, 0xA60D7BE5685256BEULL, 0xA8EAF125553D669BULL, 0xACA505AD68DB02B3ULL
        },
        {
            0x05BBD7FAFCF3BAD7ULL, 0xE036A0E184A1959DULL, 0x14D8E15E0A036E90ULL, 0xBC3B16A90E9BBF1DULL, 
            0xF01D2E83C6B6B265ULL, 0x40D3095C470C7269ULL, 0x6ECE1B6CFF1C0C7BULL, 0xF4278046BF80B3C0ULL, 
            0xB0467C380DFB2D8FULL, 0xDCF57B490F6882CBULL, 0xD8790CCDF510EA73ULL, 0x62C23CB693C7A15DULL, 
            0x64B42EDA1C25ED0BULL, 0x5B270A43CD954788ULL, 0x0AC3CC29730B3B6AULL, 0x5CE54DA70B336CB3ULL, 
            0x16567C2776C8791DULL, 0x88AFA2288291D31CULL, 0x50D54EF7FA4D53DAULL, 0xE0FE3BE21B2FD71EULL, 
            0x9BB09FCA7291BDDBULL, 0xB9B811AA4BEB1E58ULL, 0x95D773E70324F82EULL, 0x229353CC892E232FULL, 
            0xBA1C7A3D3E00177AULL, 0x14E309A356BB82DEULL, 0x4CAC08A743E1DD14ULL, 0xF7694CBC93FA9069ULL, 
            0x7FDB98AB647CB837ULL, 0xDD402EF43814A0BEULL, 0xA3DBC2D99089FD94ULL, 0x534CA0D4A0BAAC6CULL
        },
        {
            0x3D97B3C3D46F6202ULL, 0x1AB879FE5C6BC7E9ULL, 0x8BB0053AB3BBAAEAULL, 0x50B95EB3E31C07CFULL, 
            0x535C5090643A024CULL, 0x9D289B9AD2A9E52AULL, 0xCAF18A874877869DULL, 0x6D646997257BC9ADULL, 
            0x9F600D4420610C21ULL, 0x41F79FC2E16632A0ULL, 0x11C28BDE53BDBBA9ULL, 0xD22A2038B79CE38DULL, 
            0x3E3374736ACDAA7BULL, 0x7497764181A56919ULL, 0x1B26E8111F6EBE1FULL, 0x1099E7F8804D26D1ULL, 
            0x58EC013763DB2763ULL, 0xC7FB3AC5A825D3F4ULL, 0x73CA018B40445852ULL, 0x177BD584B017E56EULL, 
            0xE5C65A06FC1CD9CBULL, 0xE30835A17AAD6D9DULL, 0x357170CC30980CEBULL, 0xA6E2AA31D549B955ULL, 
            0x4D5CECFA0B4C0DFCULL, 0xCB5161E1023754CCULL, 0x139A1AFB565F5194ULL, 0x29B424589A921A14ULL, 
            0xE2C8A93B6E29C2B7ULL, 0x0054F16696DB5F25ULL, 0xC1758E977738AEF5ULL, 0xDF912B301E6979DBULL
        },
        {
            0x1516D634744EB0FEULL, 0x95B4B7E63A193C79ULL, 0x4297AFEA3D29C197ULL, 0xFDF99332BD94F675ULL, 
            0xC2B5B7AAA54FA680ULL, 0xF16C53FFEBE45D6FULL, 0x8D58EBEDB9897E92ULL, 0x82DDE4E706B51984ULL, 
            0x072C01399D0990C9ULL, 0x919C2E2F3090C7C8ULL, 0x7A1C4FD4AEB1039FULL, 0xDBF1121B2D4A55A7ULL, 
            0x856266DF8FC1F07DULL, 0x2C84DFE0C9509B49ULL, 0x81DFEB80810E07BFULL, 0x86075FEFB8DE61C7ULL, 
            0x03C6BA9D35803E5BULL, 0xE0561049AB4E0B63ULL, 0x715BB21232CDA57DULL, 0xD88A9856C8F07141ULL, 
            0x0C005298EE9982E2ULL, 0x30CECF1E65E15F58ULL, 0x5AD931489E3C807EULL, 0x51BB6580065735BFULL, 
            0x30A10CBBCF67B9FDULL, 0x3666AF6308F6E78EULL, 0x8717314CFD5BACB6ULL, 0x003F99C7B4BDD31FULL, 
            0x626066095D529E71ULL, 0x2C091AC08D231F66ULL, 0xA944FD44F9E26FD3ULL, 0x3AC4F51A0EE4418AULL
        },
        {
            0x4AA0C27E914B9AAAULL, 0x725345F36F4B1E0BULL, 0x4AC369E5987C915AULL, 0xC423A6D857EA138FULL, 
            0xC598DF07B9513823ULL, 0x8DC4D6B45011C5DCULL, 0x41CCC9EB225120BFULL, 0x79A1E211B8310A1CULL, 
            0xD3217D98F01622F6ULL, 0x8FBD87BDE1FD5193ULL, 0x03A08FB4FFFEAE99ULL, 0xFFBC0414204D2196ULL, 
            0x0F45F8C59924AD50ULL, 0x32E458D3DB4C7E81ULL, 0x7A86F2E7F3970FE1ULL, 0x4B2F80D697040264ULL, 
            0xDB0D16B176E7FEE4ULL, 0xC0A0AB9251BD6FBDULL, 0x26E2630AF10B444EULL, 0xE7108335FF7D5CAFULL, 
            0xE69D7EFB1BF93064ULL, 0x2899442AFB118759ULL, 0x648F378B86F4B82BULL, 0xDEB3ABFBA7958E09ULL, 
            0xBB8FE85FD82D41DDULL, 0xDDAC3066D69844ECULL, 0x80023EBA47B54464ULL, 0x349F063E6F993D25ULL, 
            0x4BF004802331EF9BULL, 0x6453DFE0E47D6531ULL, 0x94F3E1469A69A98FULL, 0xB819B8F3A381A71DULL
        },
        {
            0xE904B7E30406EA18ULL, 0x787D93817CEF648BULL, 0xCE1E265AE2EA0E2AULL, 0xC32293DD84CB3E44ULL, 
            0xBE1615FC27A08D0CULL, 0xB161D742DE6B3A30ULL, 0x6C58AEF99D434266ULL, 0x799317F93AA0A514ULL, 
            0xCC74CF704B23F142ULL, 0xF1800877EE92B882ULL, 0x1736D42932A31923ULL, 0xAA1D4D89DD1C2DDDULL, 
            0xFC251EF0A583AE8DULL, 0xC71FB4BB809184CEULL, 0x3F3771037AB01D68ULL, 0xD8AB113D2F72B01EULL, 
            0xA501E258502CA9B1ULL, 0xD22E6B53702C3523ULL, 0xB2AC6140B9CB32AFULL, 0x10CF5B7FBAFFC69FULL, 
            0xBD14CDE8AC4ADCDCULL, 0x7948B704A6AE6B58ULL, 0x85EBFFD428B07F3DULL, 0x1F8ED00942F06F7DULL, 
            0xF7BD58B38E1D8171ULL, 0xB1FC53B8D6CD0EBEULL, 0xF36FC12A78E2F723ULL, 0x2B26AFDCA0544C83ULL, 
            0x917700D93545D99AULL, 0xFB6FA780772E1AF9ULL, 0x0D85DBDFC42C1A35ULL, 0x0D552E2593587FABULL
        }
    },
    {
        {
            0x5157267098722AF8ULL, 0x71B178A23EEBB8F1ULL, 0xF0E8BB7FF6508803ULL, 0x97C5F77B2D613DF9ULL, 
            0x991E293412B477AFULL, 0xBF953F156325ADE9ULL, 0xE48D7E5302789327ULL, 0xC35AF25603EDC368ULL, 
            0xC1DDC958A0ADCD3DULL, 0x67DDAF917DEDB629ULL, 0x8A0C09CCDD34F75FULL, 0xBB21195BE441E332ULL, 
            0x72A754428C10FB91ULL, 0x0B11A9B477DF10D9ULL, 0x992C8BD7AF158F03ULL, 0xC66111CACBE9557BULL, 
            0x8084CB3DFCFCDEDBULL, 0x2C501AB1E04150D4ULL, 0x3D9BE0FA29D2F079ULL, 0xF1C90F5AF104FD37ULL, 
            0xC296ACA46A5781B9ULL, 0xBBE558BBE7D7E396ULL, 0x6FA28AAA5E17A82BULL, 0x972E30491B150652ULL, 
            0x300DCD7553DA2798ULL, 0x58128A97857D90F6ULL, 0xB09794E0618A6A31ULL, 0x76B7A22AD091E64DULL, 
            0xB972423FCA77FE98ULL, 0x4394B4B0F6D0C119ULL, 0x06B892199CD7E08BULL, 0xC7692F5B6F424C2FULL
        },
        {
            0xECDFE4A8BF6F9354ULL, 0x44AFE478D85467E8ULL, 0x5BF76BF212A1DA4AULL, 0x39DC1F412FD1F19AULL, 
            0x7C2B806E97BD10D6ULL, 0xEFF48F01FCC7935DULL, 0x7C6D2C2B94301C21ULL, 0xE02A223412AFD248ULL, 
            0xE5D6CE5D7292EB59ULL, 0xCC79B25525B47969ULL, 0x32F3D7DDF19156F0ULL, 0xE0F925740C81F908ULL, 
            0x02F9EB3F4FB62C0FULL, 0x9710338F4FB0FDD7ULL, 0x7CBA6530AB53631CULL, 0xC19480BF1CD20059ULL, 
            0x5CF9EF1EA3387546ULL, 0xC2070D9D32527E89ULL, 0x1ECC72C26ADBB7B0ULL, 0x68720876D269981DULL, 
            0x363B38942A135CB7ULL, 0xE44411E0CF984FA4ULL, 0xAA790BBB76280E48ULL, 0xF4759945B2096947ULL, 
            0x93C56913DF0465BEULL, 0x0577619FB7F29D96ULL, 0xEB32502350B587A8ULL, 0x965D4660F7D46F48ULL, 
            0xB0411B2B5E490D92ULL, 0xFB3E73DE8BBB0E14ULL, 0xA7B69DFC407B3301ULL, 0x75D36FE5AA9DBCEEULL
        },
        {
            0x3C4302D937187805ULL, 0x1611D21EDB4A83DCULL, 0x5DD362704564B6A8ULL, 0x340072080DB530CAULL, 
            0x6B9DC35DF6F30A51ULL, 0x9F1DBD48670AFCC5ULL, 0xC3198D68398F2055ULL, 0x2EBAC338D911518DULL, 
            0xA6B504C749501CD6ULL, 0xB3EE2665E6129A51ULL, 0x4C34A103E22A4DEAULL, 0xECBEA75FAE4879ABULL, 
            0x0A43D50ACD69223BULL, 0x40457BD245D6E638ULL, 0xDD4E4FB9B481FCA8ULL, 0x7219F41E6FE42F82ULL, 
            0xDBBF222DFE3F4C35ULL, 0x29C7A2C7069EA934ULL, 0x29592F1C82E22A19ULL, 0xDAACBC3EB18FCEC9ULL, 
            0xFDEFDFE469EFFECAULL, 0x7CC0A276F7B784A1ULL, 0x5C261C5ECC62A126ULL, 0x7210C260A6D655E2ULL, 
            0x03C15BFC9C5CEA2DULL, 0x5D8CACAE2CD878E0ULL, 0x38FEE0502CB94C82ULL, 0x5FF044E250D31199ULL, 
            0x64D071E3DCEEC364ULL, 0xF2DAB7F19AB7AEB9ULL, 0xF33410AADC5A85F4ULL, 0x8C634D666BB914B0ULL
        },
        {
            0x058CFAE50604DE9DULL, 0xB022F5F0D8E2B352ULL, 0x64BD6328D0AE8599ULL, 0x0FA8446B87297E21ULL, 
            0x2923E3BC983AC14FULL, 0xB32385C18D48F2AEULL, 0x926815BF7C4C2BF1ULL, 0x0E23B9C0F50744EBULL, 
            0x548C6261479C0B39ULL, 0xEA0AD11BE6CDB634ULL, 0x56B3C74141CA5C36ULL, 0xAE4AB641F69FD054ULL, 
            0xFD84B1327051CD8AULL, 0x6CE6B7A03E9A9D2EULL, 0xED4C736143F7C342ULL, 0xE7F734BE2451A4E6ULL, 
            0xE560DBD9414DE8E3ULL, 0x1A8F53BEF491433EULL, 0xE94799ED14284F38ULL, 0xBB64F686B1CBCB4CULL, 
            0x567DE1BA61018F2CULL, 0x8A4B3B944176BDC9ULL, 0x9FE105F29587833BULL, 0xF8EE3657134D491CULL, 
            0x92149D92717BA6EBULL, 0x7BBD0815E460D34CULL, 0xF6899B0B9E37664BULL, 0x9A5785C39AD92588ULL, 
            0x334AB3F8B1635DB5ULL, 0x75CCCA61A10DEF10ULL, 0x8F35BC11DAF6E2EBULL, 0x194DDC5982F59DBFULL
        },
        {
            0xFA525C084BB97178ULL, 0x864E7CD7DDCC4E39ULL, 0x7F212353E099E547ULL, 0x17140541DD728BE7ULL, 
            0xA2976965B83B6145ULL, 0x182B2668B2F8A68EULL, 0xDCBEE2DBE39C4A84ULL, 0x74A93CD490EF95ABULL, 
            0xF27BD97A9C3F96EBULL, 0x2B07F134E0B73500ULL, 0xCA8A9D61D494EC46ULL, 0xD745B36A3092F9F9ULL, 
            0x9A0D28CBBC265331ULL, 0x73EEC69768259233ULL, 0x1DAB0E5A8DD2A3E0ULL, 0xDC09BB7B8825A6D5ULL, 
            0xAFF60EC2902C5EE3ULL, 0xE4029D99125BBAE5ULL, 0x301133680FA272A2ULL, 0x83FC8202E112C37AULL, 
            0xA4EDA4B4BDF46B8AULL, 0x74610F47DC7E0498ULL, 0x344AE486DDB4BEB0ULL, 0x33A6D4129D506C6AULL, 
            0xCA16265B1A714710ULL, 0xACBA14A91EA6360FULL, 0x63F45F63FADEA4EBULL, 0x092092F44C42B559ULL, 
            0xB53B3317DC871E3AULL, 0x156F04FB15D85ADFULL, 0x1B181DFCF8EF2763ULL, 0x9EC427037FE43309ULL
        },
        {
            0x75AB3FC44A2AFE0DULL, 0x8DD04BC0AB4A8E24ULL, 0x675D15C734626414ULL, 0x82E3CB7D1DBB3690ULL, 
            0x0687590F531DDF9BULL, 0x766468E00650C88BULL, 0x287DCD5031D6A76FULL, 0x711553C592961F65ULL, 
            0x396570D5471DEBEEULL, 0x3B0A35F516C6452EULL, 0xFFFA3A6B882D83F6ULL, 0x2E5EAF01BA40C7FEULL, 
            0x71DC681B6792A0A7ULL, 0x286FF8EA05698CF8ULL, 0x1B2109D4EDB49311ULL, 0xCBF99955BAB37A8DULL, 
            0x84ECCF8B3431130FULL, 0xFE9FE3D1BBCB2736ULL, 0x7321D28B75B44DD8ULL, 0xC17A585466062C74ULL, 
            0x22EED1408A9A3B12ULL, 0x876BF15EA3A976D0ULL, 0xC7B3AA837BA84BF5ULL, 0x10A9CF39C5B64C70ULL, 
            0xE8AEBB5D8E4BFA04ULL, 0xAA63DAF2680C1601ULL, 0xBB4E87BA3717F0C2ULL, 0x31BC6CD3806767CEULL, 
            0x9501A394AB580019ULL, 0x0D5178B259375C37ULL, 0x52BCF430B534DBFFULL, 0x9686504A27BBA846ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseBConstants = {
    0xF4C585E734920F68ULL,
    0xE6B9289157417476ULL,
    0x258B9C424C222983ULL,
    0xF4C585E734920F68ULL,
    0xE6B9289157417476ULL,
    0x258B9C424C222983ULL,
    0xAC30623EC8585A3DULL,
    0x89DAA96222CE2345ULL,
    0xCD,
    0x0B,
    0x3B,
    0x11,
    0xA1,
    0x5E,
    0xD4,
    0xE8
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseCSalts = {
    {
        {
            0xBD0C6A5A1149F7AFULL, 0x03AE1BA36F1958C2ULL, 0x827E1EF147339378ULL, 0x9A52DD008CE48B4DULL, 
            0x5FE7718B44706DCEULL, 0x34CF999EF9AD0A7EULL, 0x52A7BD661522D33AULL, 0xA9BFDCE30FE80C09ULL, 
            0xD54357D12C6E129AULL, 0x492371E9E8DA3DD7ULL, 0xB5890F00B235EB98ULL, 0x8F50E0A4EF3B94ADULL, 
            0xEC7606D8F62F444EULL, 0xB7DECD980937B85CULL, 0xFB58CF124A4AB898ULL, 0xDFECBFCE28A82331ULL, 
            0xC155DE4622372AAAULL, 0x1A48541845CD590DULL, 0xAE7F4193C3947273ULL, 0x907CE5B05109794CULL, 
            0x43B82F9A3D517270ULL, 0x38F54E2946A4A491ULL, 0x8400D938D6C9414BULL, 0x572BF87DB28EDAF4ULL, 
            0xEA48C6F35B1270CBULL, 0x57A3E8D4E6CF4F4EULL, 0xFD3FE5F70AA711B6ULL, 0xC62596E19EFDEF44ULL, 
            0x132909F39F09D2D9ULL, 0x0ABEBCCF19664AF5ULL, 0xA30E7FC3849B4FBEULL, 0x03D3D9810B4F7B48ULL
        },
        {
            0xE6B42CD93A64479CULL, 0x894042C19F44F3CDULL, 0x3ABB56FAEDE7C5C4ULL, 0x0C8295E1FD0F7F55ULL, 
            0x44BF569CA0B885FBULL, 0x298D5925B1DA1BC4ULL, 0x149D89745F7D60FBULL, 0xED82856C10D5BB1DULL, 
            0x77ED8F2FDF89C648ULL, 0x7845395C5BBD8D25ULL, 0xDEE54E9B3DB0924CULL, 0x9CA702242E45C314ULL, 
            0x7C877D222BC71CD1ULL, 0x98B24C83E5AFB256ULL, 0x17D91BEF94E51B1FULL, 0x3F7675F2C691A5B9ULL, 
            0x03E53B59CD1BF0C3ULL, 0x1CE5A50348A303CDULL, 0x47A312C14525565FULL, 0x1132B9EFAD513A34ULL, 
            0x6FCC7BD8DC184F23ULL, 0xFAF0B16AE79DC813ULL, 0xAA20E632E4F34272ULL, 0x6B6C1F9A5730C728ULL, 
            0x51B3C7053B8BF2DAULL, 0x5EFC3DB94747AC35ULL, 0x0B0445F14B5B37DAULL, 0x088B7E8D0B5DAAE8ULL, 
            0x0126CBCF5DA6B1ECULL, 0xFF7C21D196C1E6E3ULL, 0xC49AE8C2E6C019E9ULL, 0xE10A2E451C0B6B93ULL
        },
        {
            0x2747B166296C8E7DULL, 0xB0FC4536035C90AFULL, 0x9F85E8092C22FFCFULL, 0x063BB75E1D7C00A0ULL, 
            0xCB0F12B8A51F2E83ULL, 0xE06DAD9522F1D1BFULL, 0xBDA87FC8F108A622ULL, 0x7BE7E3B46C005445ULL, 
            0x1B3C463BFA02EA2BULL, 0xFE92B3831610F449ULL, 0xC618BF4F1E1B4F89ULL, 0x6E8E0DEBB2926947ULL, 
            0x26D65CB7DB2F5BE3ULL, 0x5473CBA35E4DF6A4ULL, 0xE98AAB7F0F2F6E3DULL, 0xAB669310DBA3597CULL, 
            0xC3637DA33ACE7875ULL, 0xB6AD4831147712A6ULL, 0xAC8164E1EFE6D6DBULL, 0xA1EC770006704C20ULL, 
            0xEA87BB2EB2417768ULL, 0x7DB5EFF1BF118145ULL, 0x297E2235AA14BB1CULL, 0x9BC567915DCAE0CEULL, 
            0x58078A767E0B57A1ULL, 0x30EF369C249C27F7ULL, 0x2E418AA686307CC8ULL, 0x4C5FA3E8E27CFF06ULL, 
            0x394E5E78AB917677ULL, 0x53B259164E44C97BULL, 0xC45C9180FFD65E8BULL, 0xBFDE0CB9D93EE196ULL
        },
        {
            0xAF219B532A2D1840ULL, 0xA05F4C1C6769E265ULL, 0x541E8DFBFD557F51ULL, 0xE92A1AE0E07D0E34ULL, 
            0x99BDC38D6552FF3BULL, 0x5E4582DC1C08E9A7ULL, 0x65872CC38B13BB9FULL, 0x9B7B7260D1A0988EULL, 
            0xCEA67E8D3E45C957ULL, 0xAF0520275058EFD5ULL, 0xE016CE5AE7591EDCULL, 0xFA1D5D9EFBB48DDEULL, 
            0x7B8CE708C039BA15ULL, 0x9A9A9BCD518FAF9BULL, 0xFE4F9AFF6C9AD7E6ULL, 0x59649B516F45A60CULL, 
            0x666EC18A1785C753ULL, 0xE34FB86363674401ULL, 0xFBA32F06ABE6906BULL, 0x86EC89918E4B6CA7ULL, 
            0xDFFF6A37BA002DC8ULL, 0x700FC683631D5B2FULL, 0xF7D6EE44F7277397ULL, 0xB31D6584D092D38AULL, 
            0x437BE2BCADD54F6DULL, 0xCD2DFB37CD3E426EULL, 0xE09F90369B413E0FULL, 0xA1EA22097D480CA4ULL, 
            0xF4CF481F3765A4A1ULL, 0x28AB3736B1D23668ULL, 0xD63DDA07B1E9FF34ULL, 0x4079D13F31346CE0ULL
        },
        {
            0xE9CCB5BE94FBE5D7ULL, 0xAF39959495D5CA92ULL, 0x66E85A10ED25CC9BULL, 0x194A56EAAF2359F9ULL, 
            0x60E4CA7113F82505ULL, 0x74150CAB9ABC14A2ULL, 0xF66AC738B57E0429ULL, 0x1ECA7EE15BAB3917ULL, 
            0x731083C27900C39DULL, 0x7E5009078783F106ULL, 0x9D43D78607BCEBF8ULL, 0x26434D1260745827ULL, 
            0xC50211A45F4D4147ULL, 0x72FCE427A041AA38ULL, 0x705D59208A1E96EBULL, 0xCB2C1AFF0A8F0152ULL, 
            0xE48BBE967376319FULL, 0x3CBC0DB4DC453B26ULL, 0xD5D8E3712B1E8D9EULL, 0xE33590540AD8EA6AULL, 
            0x518DE3BB020CE10BULL, 0x0BAA6562134FB576ULL, 0x7A5F30AC22A61781ULL, 0x3794C0D1A68A44ACULL, 
            0x697047E07C6D403EULL, 0xFD5280B861055E08ULL, 0xA1546E835F55864BULL, 0x59BF082EC7ADFDC5ULL, 
            0xAB21E8170A99E2C8ULL, 0x2A443EE272D24B0DULL, 0x0239965D9D73DA03ULL, 0x54F46D0E5328F372ULL
        },
        {
            0x369192AC9D18916DULL, 0x45DD90C46DF1ABE7ULL, 0xE381006B2FD94276ULL, 0xD239F6EBEE683473ULL, 
            0x2306A046FB5C0003ULL, 0xF2934D865B64BDEFULL, 0x810774C34513F4B0ULL, 0xE38C10ACC7B4C180ULL, 
            0x5D2C17BEF14867A3ULL, 0xF3A588B808610540ULL, 0x507914D8B91FD64BULL, 0xC9A5783CC4D8AB5BULL, 
            0xE8308C74F13C59EDULL, 0x37D6D63F52202C5DULL, 0x140836F508ED79A8ULL, 0x1A55EA7DEF1CB1ABULL, 
            0x0F0CF6C9458769AAULL, 0x268454EB3701E2CDULL, 0xF4A0F4A60885A103ULL, 0xEEB6239A2EE1C6FAULL, 
            0x8C96A9FC7802BAC7ULL, 0xCB85B1BEEF22AD40ULL, 0xA308E2E6BE9175A6ULL, 0xBDA3B743BE24188BULL, 
            0xA294286AB9F8A025ULL, 0x1453056FB199FA87ULL, 0x0C11885E1C45DF30ULL, 0xCC513AC60900924CULL, 
            0x62F9FC7FBA923CF5ULL, 0xE34D7136BB27EA2AULL, 0xE0026C4BA4A3C571ULL, 0x4B66EA6E4BD00853ULL
        }
    },
    {
        {
            0x047FAB091C590B7DULL, 0x661693206D630CB7ULL, 0x57E86D22977B690AULL, 0x8A79EEE08F47A54CULL, 
            0x9570E7B6334DEFB7ULL, 0x318521D9772D6F5FULL, 0x9F024FE6C9DCF9E7ULL, 0x4D6E0BD5815E8353ULL, 
            0x7014FB61BAED82E8ULL, 0x039388403D5816BBULL, 0x9292AA8F8FE5292BULL, 0x6D97C195AFD78A02ULL, 
            0x347671940FF984EBULL, 0xED6622170338876CULL, 0x5424446322C667AFULL, 0x1EE5DB4EA66ECAAAULL, 
            0x17B7DD6B46C605F9ULL, 0x354259F9D6AED1F6ULL, 0x43853830B74BEA5CULL, 0x213845F5AAD70028ULL, 
            0xE98FE8B43BB7B648ULL, 0x3399EB6DD3E019F3ULL, 0x9789C3FE5BE3D6C1ULL, 0x243F098E9C341E30ULL, 
            0xA12254210BE0B307ULL, 0x2A770D647358F26CULL, 0x328DF0645C78C854ULL, 0x66BF1D22021193F5ULL, 
            0x311F01F902DD68B6ULL, 0xB72A6899766E17EDULL, 0x1F7FC1D5C6BE50EAULL, 0x7B6023C9BCA83A42ULL
        },
        {
            0xAB506FA941088086ULL, 0x83B49641449FED50ULL, 0x096A43D3B435687FULL, 0x1475EDFE6993BCB4ULL, 
            0x45D29D1C3923286FULL, 0x4A9DA7912A53B302ULL, 0xDD19E67CBD23DBDCULL, 0x011F7BCA3409261BULL, 
            0x321DD10B03BDB2DBULL, 0x042259C42B2541E4ULL, 0x303B2CB96F800963ULL, 0x32BAB04230EF7F1BULL, 
            0x895B7AC6D4861795ULL, 0x4CA0E152BC872B5FULL, 0x7572F66865B2111CULL, 0x81079DCCF3ADEE68ULL, 
            0x0A208018E393ACEBULL, 0xE454F98986E721DAULL, 0xFD1D7100243712A6ULL, 0xCBEC985ABB658028ULL, 
            0x985BC4773A85F338ULL, 0x6D48CE5CD6C1A578ULL, 0x1E4457112FD37BD2ULL, 0xC447C6C810F86607ULL, 
            0x4F107125234F8687ULL, 0xC3B7F9F2464C0953ULL, 0x4421607C0EECB0E2ULL, 0x28873EAFEA26F66DULL, 
            0x7A008EE4576E3764ULL, 0xEDBCAEC06C6475FAULL, 0x63E0EE3C4B761D99ULL, 0x3AC295F94F3562CAULL
        },
        {
            0x458A0FF699211F5DULL, 0x491D3493052F142BULL, 0x43E680BA609CCD82ULL, 0xEED3F2B939B982CDULL, 
            0x845266EC14FDEEB7ULL, 0x1CF6000C7F498EE8ULL, 0x0931E9492551EC0AULL, 0x2702DD937159E48DULL, 
            0xF9574C184BE1D587ULL, 0x57DED1896D34C3F9ULL, 0x5DAF4687451C3A3FULL, 0xE87B508B0541C949ULL, 
            0xBE35706A1755CC7DULL, 0x4F5A60B11F1CF9D3ULL, 0x5C3D7B7D53237D8AULL, 0x0834914EA9E17BD8ULL, 
            0x22B127F5C5D1970EULL, 0x35B770AD726C2D63ULL, 0x78A1BC632A4926F8ULL, 0xD7012A6338B71333ULL, 
            0x669D3D711CA68E75ULL, 0x0194FCAE0664AE33ULL, 0xD31B634CAACBDBD2ULL, 0x3D87D23308B5E081ULL, 
            0xD36CFB3F7048C967ULL, 0xB0BA7B5737737AA4ULL, 0x417288021C0B063BULL, 0x05E64BF02936BE32ULL, 
            0x8EF3EF32065E1236ULL, 0x46B4B4A0DBAF270DULL, 0x2B2C1698EC4FCACBULL, 0xD1EF76122BF56706ULL
        },
        {
            0x9DEE018325628D24ULL, 0xDDD08C32C853CCB6ULL, 0x496C450856D912DBULL, 0xE5BB70058A80C330ULL, 
            0x3A70F36D7F817AB8ULL, 0x59CF7F75654FE477ULL, 0xA9FED50CA119B7CCULL, 0x8E730C4B9FFC1E95ULL, 
            0x9C6CBA6F04FF1423ULL, 0x3AC0394BACFC4454ULL, 0x9AD91607D15137A4ULL, 0x7351CBAC086B70A9ULL, 
            0x64BF4B5621022AACULL, 0xA744DE1D78170055ULL, 0x6CDD8CE2E9073FB3ULL, 0x78988A49AF497B6AULL, 
            0xDD7B7B4B95A7D5A1ULL, 0xE6FCE619EE241130ULL, 0x5192E8A068BA4CEEULL, 0xB3F2302CC5C010A0ULL, 
            0x2C6D5D201E187DECULL, 0xCC78EA8CBBED65A3ULL, 0x737307CA70FAAA73ULL, 0x4355F547E3B69730ULL, 
            0x7E64BFA9B21A5F67ULL, 0x411F2E34D2F7D0A2ULL, 0x56DA097F34302105ULL, 0x8EA893C09F0B915FULL, 
            0xE6316CAA5C673AF3ULL, 0x1BA72D00295D90BEULL, 0xE59AF6B12A40AABFULL, 0x9D2408EA928B3FDFULL
        },
        {
            0x9B98CDB2545C1D52ULL, 0x8B2576C5A1894E82ULL, 0x91CBA4C2D86618E5ULL, 0x322E35F8BD90E77AULL, 
            0x2310E1605408E286ULL, 0x84A24346CD27D864ULL, 0x8AECDA152110AF14ULL, 0xBB74B9F7175F19BAULL, 
            0x7FAECFF46821EF31ULL, 0x68325438789D4C01ULL, 0xFEBDCED1B7B6DC43ULL, 0x8CB3A34DAA5DDA4AULL, 
            0xC26ACFA6600417DAULL, 0x45BA52533DF2D171ULL, 0xBB2A018DDC29139DULL, 0x83DE9B569A4173C3ULL, 
            0xADEB2FD87D41EB22ULL, 0x2CED3AC86352571CULL, 0xF33825A598E1AAF5ULL, 0x3D84139BC6A9EEA5ULL, 
            0xCACE6C391C025FD3ULL, 0x9DA2E17C7C376DD1ULL, 0xE29163084F51E94DULL, 0x0D4F4291494B1AADULL, 
            0x5F28B6631795BB75ULL, 0x50FDC4ECE6527CC4ULL, 0xA2C64FF258B18F91ULL, 0xF1F863CA02AFB257ULL, 
            0x27D8F75EDD35A320ULL, 0x8AC4C258E653AC32ULL, 0x6639F2076EB5CFC8ULL, 0xE9FBB0DC224AE814ULL
        },
        {
            0x3E69ABF8F4F48F12ULL, 0x87750E07E2923E2AULL, 0x9D2E4320EA247192ULL, 0xDD7FDBCCB88E0CE3ULL, 
            0xECB10215C78FD60AULL, 0xA1A9331C92C22C81ULL, 0x11004D20DCEA6958ULL, 0x566B0FA47D0756ABULL, 
            0xD1DC07EB7C9D9F17ULL, 0x77C45EF3D94E96A6ULL, 0xAA2868E9A3162AD5ULL, 0xE09EEF42801C8AC9ULL, 
            0x04617A5B24BA8774ULL, 0x16C8BDEB4AD6B871ULL, 0x9DEC4124850D12BFULL, 0x38FBFF55A5E54E88ULL, 
            0xA978C193E7B23CBEULL, 0x73D2BC498918C22AULL, 0x410ABBED2B024268ULL, 0x04E2C96E586292CEULL, 
            0xC3424C5E2DC7A576ULL, 0xFEF236AA925EC7ACULL, 0x313A32DF9DABA7D6ULL, 0xC694BA2D24B3E380ULL, 
            0xC120C6742F5D0AFFULL, 0xC80B6DE944681AE1ULL, 0x3398A9304AFAA4C9ULL, 0x9C25F89CE9046154ULL, 
            0x254E0747760B906DULL, 0x7B79732240C53DFDULL, 0xFF822928FC2ADB63ULL, 0x440EB3729232F74BULL
        }
    },
    {
        {
            0x5BBCCE29324D8205ULL, 0x7CA6016D4DE428AAULL, 0x3174E7D499D9E5ECULL, 0x64974640F898890BULL, 
            0x9F84E484E5B7F2D6ULL, 0xC7883D5460E830A2ULL, 0x26351BAD844F6678ULL, 0x2C02236E48168543ULL, 
            0x50479F4167EE013BULL, 0xFC007571B6C7B42BULL, 0xCDAB171077F04DFFULL, 0xBB4D6D7377D2EF7EULL, 
            0xB8A3A375ED9F2BABULL, 0xD0B8DB42CA81810EULL, 0x61491A9C3D3CBB9BULL, 0x51B8343534C34E5AULL, 
            0xC221CEDA6EB8D22CULL, 0x9BCDA3AD07E89DB6ULL, 0x9D7C5B9513394338ULL, 0x48B44D406CC94D59ULL, 
            0x6C8E43390FA1ECB2ULL, 0x54AD036F15A45A1FULL, 0x2011FA6719C271ABULL, 0x29F4A03D493CA429ULL, 
            0xC405F99B4AEC070EULL, 0xCA57FE43D0A9735CULL, 0x740A6D0AC403BE0CULL, 0x5671784BF5F284AAULL, 
            0x8DF6FAF0BC639838ULL, 0xA8966042A217359EULL, 0x1D1B7D71CE598DBBULL, 0x07C50EAAADDDB936ULL
        },
        {
            0xA04CC97A823D3F30ULL, 0x7132C004299F5468ULL, 0x86DE63FF701E7DDDULL, 0x5E6824C861F804E2ULL, 
            0xE2195D30492160E3ULL, 0xF4AD474EA7E210ACULL, 0x4B77DB96BB4FCE13ULL, 0x726B3330CBF092C2ULL, 
            0x135737E66558809AULL, 0xAA9B588E03621181ULL, 0xA7CCCE17EA95D1E2ULL, 0x9726071E6B4A2571ULL, 
            0xDE906CCA0E982FFAULL, 0x0DB16060D96FFAA1ULL, 0xC9322742DE6DFF32ULL, 0xD9B6EADA78830FDEULL, 
            0x3F09C87A8B75D872ULL, 0xCFE2D22FB76AC6E1ULL, 0xEB0CDAC5B3CA988EULL, 0x3BC88F7625011BEAULL, 
            0x6D51B25A5AC638BAULL, 0x83F8185AA843E3DCULL, 0xBCA58525B1810320ULL, 0xEAB88313968BEF44ULL, 
            0x45B05FD32C79633DULL, 0xBA4849117C2AB83DULL, 0xFF535C69E54B7086ULL, 0xB84910C0EF0D11E4ULL, 
            0x12C8617074E1FD30ULL, 0x3F109D834B90B699ULL, 0x48A12F42DEC0F197ULL, 0x19AE74CCD5D33930ULL
        },
        {
            0x0E148700C494F973ULL, 0xAA5F4CB95FC7EC74ULL, 0x5467669D40C49A70ULL, 0xF38ABF4EF8C45FE2ULL, 
            0x5AFB235087B9C3B2ULL, 0xEFBB8DDC199A1357ULL, 0x30C2FA4100C2A0ACULL, 0x848E57A15872BA36ULL, 
            0x3180BA05270FBDDAULL, 0x6702B8A250B58E9FULL, 0x77E7D0C9FFB55DB7ULL, 0x72B6CCD87879AC06ULL, 
            0x88075648D52395BBULL, 0xFE24C814B71697D2ULL, 0x39B2B173862AB842ULL, 0xBD306D263900D303ULL, 
            0xF62AB5E787DB27F2ULL, 0x47ADF23378139033ULL, 0xE5EF62894A95AD31ULL, 0xFDB3085C9C28A175ULL, 
            0xB33955F2AB961FDDULL, 0x077B13C85CDB741BULL, 0x6B06817052BBDA43ULL, 0x7FF467405CFE9A58ULL, 
            0x2920B7C974EE3E75ULL, 0x5E5CABCFD3C1F47AULL, 0x1ED80EB49E854DD7ULL, 0xA31DDAF87A4C31B4ULL, 
            0xD0CAABC2F4482852ULL, 0x5DC491C7B313A583ULL, 0x114BF1AFCD02B13EULL, 0x389AA07130DDBA0BULL
        },
        {
            0x07F33C8509D31A68ULL, 0xEB44FBA95FBA76CCULL, 0xC932C56FAF52CFD3ULL, 0xB0071AFE2801751EULL, 
            0xD4B1A7486D90D61BULL, 0xB1F34795AED88975ULL, 0xF8C33BE05D8B469AULL, 0x756991C351F23A92ULL, 
            0x4A9EDE7849B5E154ULL, 0xE64F61CB1B9DFB8AULL, 0xBC8F8D7A9315FF26ULL, 0x72B1FA3D5AF60F15ULL, 
            0x6DC183C9D70D6E2DULL, 0xF578AFD3553F97E2ULL, 0xC528E5E94DD00BCAULL, 0xEB18B517EE5833C0ULL, 
            0xFB602ED9FB002986ULL, 0x7A3FC7E0F93C9075ULL, 0x64E7F6B961A21F93ULL, 0x0F982E28EF7E2D93ULL, 
            0xE1AA4F6EC6DB33C4ULL, 0xF39A893FF24631EDULL, 0xC98FD111FBEB289CULL, 0xED60D34C42CA63D7ULL, 
            0x760518EFDEAF97A8ULL, 0x0C51796BAF4C47DEULL, 0xFC03213791D74B5DULL, 0xF7AC1CB3BCE7D41CULL, 
            0x56E07BCE1074D0C1ULL, 0x051B3A65285CC808ULL, 0x19AD4E2F33974A2CULL, 0xF4BFECEADEB8BA83ULL
        },
        {
            0x279C682F9F59E70DULL, 0x8AABEA4EB9605F92ULL, 0x6056EA2F1815CFF8ULL, 0xD19883D81413DA75ULL, 
            0x8AB5D4E7B98118F7ULL, 0x4D917B12153713C8ULL, 0x51B7B31773EF2F0CULL, 0xF08FD2DF920A466AULL, 
            0x733A399AA2EA288DULL, 0x83D5B819F10BE756ULL, 0x4FD22DFA6C54B126ULL, 0x45B0DB1E26A32890ULL, 
            0xB09A5ED72D4DA85AULL, 0xB3BA2DB4D672EBA8ULL, 0x50B4363A2AC7F0D6ULL, 0xBFF4AA971E160244ULL, 
            0xA4EE80A0825A3A5CULL, 0x040A2498F1386026ULL, 0xF407B0045B2C1244ULL, 0xCE580816693985C7ULL, 
            0xFF708CB02C7FB0D0ULL, 0x0B6AC321EB6644B0ULL, 0xEE8455B9694E8F66ULL, 0x149DD63C8A594A45ULL, 
            0xE6642AF081D67AF0ULL, 0x48D5C401A15C9DC8ULL, 0x341DF6F92B1D0A04ULL, 0x4350D6B88017A6BBULL, 
            0xEF6833A2EDCD3125ULL, 0x920B5DD462BAC319ULL, 0x8A62FDFAD944A410ULL, 0xE2306BE9C78CF989ULL
        },
        {
            0xD18C4911679D40B0ULL, 0x5402583CFFFFE05EULL, 0xC2662C3AC27B85FBULL, 0x0F466E70929B104CULL, 
            0x38F0AD916BF0D703ULL, 0x5971B13B8BC65F49ULL, 0xE3A3D232CF0141D4ULL, 0x04110AF0CFBD738DULL, 
            0xCDB5ABE9E20C4C35ULL, 0x71E70804ECEA83B4ULL, 0x532C4F40C7B2766FULL, 0xA1AA32B420A1D729ULL, 
            0xD4563CAD161F3A6CULL, 0x9008BD5E4F1AD8D5ULL, 0x5B601988E99150C8ULL, 0x13436CD5D3B6FB8CULL, 
            0x840060F63137234EULL, 0x05F6F7CAD70A84C8ULL, 0xE9F485A543DD4CB0ULL, 0xD8253151E62F8CB4ULL, 
            0x51CF1772BA9C51B0ULL, 0xFDE6E4C86F9F47B2ULL, 0x6B358399116F0E61ULL, 0xC2504999F04CB0B3ULL, 
            0x5F4E4FF468DCD6A9ULL, 0x6EC800481B5D4050ULL, 0xB98B70144C857FBDULL, 0x13BCD76642E35EA6ULL, 
            0x603A0EAE9A889E9EULL, 0x23A47C519CE9067AULL, 0xBE194B706D119B4AULL, 0x2F23301C93A62153ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseCConstants = {
    0xCDD479FDDDE7160CULL,
    0x64888172EBA13FDEULL,
    0x4CF03EF29E10B374ULL,
    0xCDD479FDDDE7160CULL,
    0x64888172EBA13FDEULL,
    0x4CF03EF29E10B374ULL,
    0x215B753FD91D85DBULL,
    0x53EA1CF5C99774FAULL,
    0x27,
    0x46,
    0x1D,
    0x89,
    0x08,
    0xE5,
    0xE4,
    0xBA
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseDSalts = {
    {
        {
            0x4A6D2C5011BF1115ULL, 0xC15C0959C180BF6EULL, 0x2559CD50B2065CBEULL, 0x954DF2BC8F850EE7ULL, 
            0xA30FDE5461A1A33FULL, 0x3D6DFE0904A6D765ULL, 0x09C02FB1533E7965ULL, 0x14248EB8F740E746ULL, 
            0x0004DC80562C86B6ULL, 0xEA78D669F475AD97ULL, 0x7D062606DBA401CEULL, 0x7C3CE09A5E6777BEULL, 
            0xD65545E0C22343C5ULL, 0xD9A919918311B258ULL, 0x6843926A46543412ULL, 0x81F7C3FC96C1E9A9ULL, 
            0x1D3FF25FBCD92C87ULL, 0x07A3A60E152CF391ULL, 0x69755617448F5B45ULL, 0x0CD3A45B5D3996C5ULL, 
            0xEDE3DC07F65E4648ULL, 0x4940CC78FB5FE4C6ULL, 0xEE474BCD3AFD023BULL, 0x51C29E03A49DBB05ULL, 
            0xE8BAD4C8285BD0F2ULL, 0x02B833F36EF128D2ULL, 0xBF7E886442BC624AULL, 0x6F1C266F02BBB0CCULL, 
            0xB74DFE995E794E8CULL, 0x640B300DB36B10DDULL, 0x06A45919E8E8CE38ULL, 0x87F2FFB9D0201C67ULL
        },
        {
            0x6C43EBD1491CC381ULL, 0x98D636C1E1E579FCULL, 0xF325014D6C7B497CULL, 0xEC308E6F1FB68A18ULL, 
            0x2C8E7D79AB80F026ULL, 0xE6FD5EA501B0CCE9ULL, 0x76BFA88D6BEA7B36ULL, 0x54BDA761C745A910ULL, 
            0x4B31089DE8748E18ULL, 0x4C698D3216885CDDULL, 0xA6B07D8D372A5AFAULL, 0x980A779DE8975F57ULL, 
            0xE8D147C1AC6EF0B6ULL, 0x3FD9BCE39AE5EADDULL, 0x84763630905627C7ULL, 0xD3FEEAB03BD36D17ULL, 
            0x6DFB822E9E1ED48AULL, 0x526FEBE2BE4738D3ULL, 0x989B7D3FBF593730ULL, 0x8ADE54BF62F32FF2ULL, 
            0xC4B0D1B3133549D4ULL, 0xCE8C0B4409A1DDCDULL, 0x0BB8573296CB7F5FULL, 0xE173C978041ABBB7ULL, 
            0x1625CA58BBC32369ULL, 0x835308691D64037AULL, 0x271741421BBFE00EULL, 0xAC5214E901842C52ULL, 
            0xC00BC8017AC066AAULL, 0x3296EC629D43E155ULL, 0xA6A888BFAB91C719ULL, 0x394E790B13AF6ECAULL
        },
        {
            0x5179C53F5E4618D4ULL, 0x4D9DD7E64300A382ULL, 0xE7C66165AAB5C47CULL, 0xECD499019754B70AULL, 
            0x7581EC1001C1CAB0ULL, 0x54D0BF6F278B4D40ULL, 0xDEAA69C06DAE913CULL, 0xA2D92003AB938661ULL, 
            0x339A9859FA7FC7BEULL, 0xA4EA7D7E249D0951ULL, 0x65C39DFB1F51E923ULL, 0xB925D0D174D87348ULL, 
            0xD2D91BA37777AE2DULL, 0x185F3A3582365A28ULL, 0x71FF4C1E737F1B1FULL, 0xFDE310CC1B7A5B87ULL, 
            0x4FB2CE92F2593CEBULL, 0xA66D28DF406D66DAULL, 0x582F5E82B661E756ULL, 0x829A01486A8EADD2ULL, 
            0xA43D40DFD9DF05CFULL, 0x996BB6967389CB5BULL, 0xDA267C40BBE57E8FULL, 0x3E9AA2D1F5E2DF12ULL, 
            0x19D546093F5768FAULL, 0xF266A73016590505ULL, 0x655B529745612BF4ULL, 0xB3ECE4C9FC0B8D47ULL, 
            0x69BA69AF55820C02ULL, 0xC87B72BA80953E11ULL, 0x9314996719A37474ULL, 0xE1463CEDE96BAAEEULL
        },
        {
            0x99EDAEAA8F9282F7ULL, 0xE7435ECD377FA85EULL, 0xBED3BD7F534F88D4ULL, 0x7CF99C6ECEF6EFFDULL, 
            0x58D18A7E7BDC97B3ULL, 0x2C7A5BB47D18F0A7ULL, 0x6A357D48AC2AE3C0ULL, 0x69EA296647C8A55FULL, 
            0x5AC86C731764F346ULL, 0x2A1EAD7D13468DD7ULL, 0xF6230115E3D162ADULL, 0x9ED261EC3DA2469AULL, 
            0x33A292C9716AF324ULL, 0x99220D5A4B3BEEAAULL, 0x9D44C08D1F4BEDC0ULL, 0xA7FCE0419F7A3C45ULL, 
            0xEBC70A0C9E4ACB6AULL, 0x4F9CD278FB86EF9FULL, 0xA2D495636735D17CULL, 0xD63D9F0EA9609869ULL, 
            0x8CEC9033E8EBC905ULL, 0x8C0C310C518BAC72ULL, 0x6D0058DE4A446DD4ULL, 0x6DAEF012BAB6FEC7ULL, 
            0x963D603495030C73ULL, 0xD57271F3EA263874ULL, 0x0DE5ED07522AD8DDULL, 0x938E7F6E72870898ULL, 
            0x0130C86D4369C275ULL, 0x60E941218B716014ULL, 0x0D1F90433F93A3D3ULL, 0x868F70D1DAB6FF77ULL
        },
        {
            0x7DAC1F0DA92F7D23ULL, 0x92061335A731C228ULL, 0xB6665463D8D93770ULL, 0x355627E15E913DD7ULL, 
            0xC3D088C7198A9224ULL, 0xF53246785D204835ULL, 0xA2D6D9CB79D43DD2ULL, 0x402619CA82AA9983ULL, 
            0x0C0DADA5379C249FULL, 0xC075364981E28D70ULL, 0x5889283912615D33ULL, 0x6918D375B8C7EBC8ULL, 
            0xE6227A9742B1DB58ULL, 0x7711796C7745CFC2ULL, 0x18C3FCF1790F3C0EULL, 0x95CB5037ADB10FE2ULL, 
            0x12316A9785E601D5ULL, 0xF26E3FD883657DFAULL, 0x811A6BCF5AB7D914ULL, 0xD3F982E1C35D2DB6ULL, 
            0x96A18F7D19AA02ADULL, 0x0053EB5E1FC5EEB9ULL, 0x75D82C5B3387611AULL, 0x054DF87CD4DD2F49ULL, 
            0xA8163511BE92C172ULL, 0x7677AE5D174C8E60ULL, 0x9534217AD423CE43ULL, 0xA2A71328A3FAC0DEULL, 
            0xAC18461E941A3083ULL, 0xB4BF9CEAA31CD814ULL, 0x6868CE3B73D49A63ULL, 0xFA9DEEE04E2BF9EFULL
        },
        {
            0x37B5D39DCFEEBF6AULL, 0x155F3FD49A0B05A9ULL, 0x4EC9020AD3A5114CULL, 0xC98785F86350A67FULL, 
            0xF5C950EAD8F41D68ULL, 0xB07E028CFDA94592ULL, 0x0D7BF8D735E192A4ULL, 0x3F17528F9AF47933ULL, 
            0xF5DECB51A85A3B2CULL, 0xA396D2F4A76DB760ULL, 0x1115CB388D045F13ULL, 0x0E9CD23DF61F612DULL, 
            0x8A8C0524A6A7340FULL, 0xFFB0DDD10F69629CULL, 0x8EFC30DDEE06177DULL, 0xBCFCAD85339DA1E8ULL, 
            0x85E8B7814C491772ULL, 0x6BF22D2BA0DEB680ULL, 0x63A2FCDEC2DE2B14ULL, 0xDB7F3190F65E1764ULL, 
            0x9D2A4876F1AAFDD6ULL, 0xCBE92253F59E2361ULL, 0x3743E0B0CB0B7AC1ULL, 0x34AA48FF105AC10AULL, 
            0x1E98E95493E9EC8AULL, 0x75B5A10A5F62E722ULL, 0xDD5EFFE063EB239AULL, 0xBFE09DF73A3ED6C5ULL, 
            0x7BF2B87913E5C20FULL, 0xE84C2BA99A609D49ULL, 0xEDF05C0BC61851BFULL, 0xEA307F14EEDDF377ULL
        }
    },
    {
        {
            0x572203F00A5AE9E7ULL, 0x01F93EDBD8572EFEULL, 0x8ED0D5706990474AULL, 0xA0FE91E76789FC9BULL, 
            0x82E3B5945DE7C81FULL, 0x5F3CCDFA18C3E113ULL, 0x1F9665AA3F1750B4ULL, 0x5291C9AFCF6223DFULL, 
            0x3A380E9C018C749BULL, 0x78E7D9FB386FF7B4ULL, 0x14AE7860C59DC63FULL, 0x4512BB889478178BULL, 
            0xFC65E62D4097B828ULL, 0x8CBC04A67F38194FULL, 0xD6B2F7C57A243FB9ULL, 0x4CD80C6AAE3E1C7EULL, 
            0x827E4FD570FB821AULL, 0xEEE4CABDDEB6365CULL, 0xD508AEA1D982725EULL, 0xDCBDA56BDFA65716ULL, 
            0x947E9AF74AD8762CULL, 0x487626F74CDD1058ULL, 0xC625C1AA474C8EC4ULL, 0x4B1C7AA6E09642B8ULL, 
            0x17E8DC159893B3C7ULL, 0x44D88D0031679918ULL, 0x290C9F81D74A467EULL, 0x8A70E5EA231E1D3EULL, 
            0xE9C65EF00D49F10BULL, 0x80702A3766E13773ULL, 0x8134DBA44B5C8913ULL, 0xFB01F0BF754B3444ULL
        },
        {
            0x2BF423E268BFFEB9ULL, 0x7C83AB0021828C88ULL, 0xED72BE133A0C7740ULL, 0xE2D25982B5AE8870ULL, 
            0xD8E4EB111A538489ULL, 0x89FB58BD726A2AF5ULL, 0xF6375E56825B00BAULL, 0x035AA1309B799659ULL, 
            0xBDE2E7A123FB4CC2ULL, 0x2FB9816E52AE5392ULL, 0x2EDA081E230E862AULL, 0xB8DA196904C7CC08ULL, 
            0x92EEB92793BFEC6CULL, 0x89ECD8F83810532DULL, 0x8F2C5F4C0982FCA0ULL, 0xD2093EE28E03BB71ULL, 
            0x33FEC3EB8FEA23E0ULL, 0xB80DDF6CB171C7CCULL, 0x73CF52F8177F8021ULL, 0xE71416C9BA368B80ULL, 
            0x037856B666115668ULL, 0x34786CD741E19204ULL, 0x9E3FE33627A11FF2ULL, 0x20A75B0BE450D348ULL, 
            0x81D4BA8426757F42ULL, 0x4E0151DB94394495ULL, 0xF759E9C8FF332F5BULL, 0x53520EC57C977B7AULL, 
            0x8EBCCDD694166E7AULL, 0xDDEBF1D9C8EDDAA7ULL, 0xE80A1ACBDB5F91B4ULL, 0x1A2DD1BE1A514744ULL
        },
        {
            0x30F503F982114B12ULL, 0x9574C17098C74142ULL, 0x293288A5B3C936EFULL, 0x92660293769A8DF5ULL, 
            0x6121F4776E0AD26AULL, 0x47F761E6273B21DAULL, 0x085A8960093DCE7FULL, 0x57B77C1A470CE460ULL, 
            0xD047ADA665F5E593ULL, 0xF078222B59DBDF4BULL, 0x4028A4404DE1464AULL, 0xFBA61F13CE0DC60CULL, 
            0xB9C80F16D12CA001ULL, 0x4A515D37AA746666ULL, 0x121AF0EF468805E3ULL, 0xCA167A460181ECEDULL, 
            0x93EA0D48C0F4976DULL, 0x5FD424EAF3AA7926ULL, 0x5BD0DDA792A803B0ULL, 0x9E2C06B22D2273C7ULL, 
            0xA783C5E62A8035A4ULL, 0x127E7B4096644DC4ULL, 0xCDF09E035065C8E7ULL, 0xAE2126611BD62BF7ULL, 
            0x92CA09BEBF2DC0AAULL, 0xB61003AF9C1B39E7ULL, 0x8ACEFB81F23D8CDDULL, 0x43819B6ABDE8521DULL, 
            0xF04AAFA79C071F9EULL, 0x9BF3727A9E41F1EFULL, 0x7E53E5B7C7D4F0EAULL, 0x532FB9F50BE682A5ULL
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
            0x5F8FC07013F3A795ULL, 0x09E62BBB141674A8ULL, 0xDF2CB1025E5D80B3ULL, 0x8045CB249CB21D17ULL, 
            0x7F989D320370CDB6ULL, 0x38CD79F38BE03EE5ULL, 0x16D48BA90BDE5AA6ULL, 0xE3FFB69F10B26F06ULL, 
            0x87C2136895235AFFULL, 0xA1F4920B3C3D1C1EULL, 0x2BA36FB068B7991CULL, 0x385409C75ADB3E34ULL, 
            0xA41F1653FA7CFFAAULL, 0x957D94F56A1AA3BEULL, 0x1DCBEED178DF8BE2ULL, 0x339CAA29A01196C1ULL, 
            0xE013C389F1D08F2AULL, 0x269DC4E61BA8578FULL, 0x03AF5CE9C2300EBDULL, 0x7B0EB2B01E271F95ULL, 
            0x7BB0D4117601F05AULL, 0xEA6273FB853B74C9ULL, 0x025B76D9BF238C68ULL, 0x2B742DCAEEE2C90FULL, 
            0xBC55149D3B2E24C5ULL, 0x97604799718141ECULL, 0xF102A5C5CA0F5102ULL, 0x0E58D0FC64563700ULL, 
            0x43671445E110795EULL, 0x50466CB54B574730ULL, 0x56F6928E59FDABBBULL, 0xBA0A11934EA77C8AULL
        },
        {
            0x308C4A194D95A8C9ULL, 0x729C92A38A4D6872ULL, 0x9FF7322AD6F3B109ULL, 0xE6527D8F4FCEB525ULL, 
            0xA25A927829C6A329ULL, 0x5DE1635B0D123314ULL, 0x1BD6562B3388D36CULL, 0xD05EBFBAECFE713DULL, 
            0x46460074FFF988F0ULL, 0x3E44B06D274CADE4ULL, 0x5EC4DB00EC1BD5BCULL, 0x1B8A7DC0BA251B19ULL, 
            0x934B5492B6C448C2ULL, 0xCAE53365A38E4537ULL, 0x1F187E4FD455A4BAULL, 0x80C5377D43C71EACULL, 
            0x250F6BE5FA233E03ULL, 0xABE9EA5656EC02C3ULL, 0x207D973F75A7665EULL, 0x6FF83AD0B62E5193ULL, 
            0xF414F7211E99ABD0ULL, 0xED5B684FFD561320ULL, 0xFC3A53AD9972956AULL, 0x92E46D7F3D8AC7BAULL, 
            0x2E7A3C53F732ACAEULL, 0x01A0F770B8C7189CULL, 0x329721BEB607E450ULL, 0x577AF19A3FD87C22ULL, 
            0xE10DF5F7CFE6F694ULL, 0xED208F0110C7AD36ULL, 0x4B25D51E55621C80ULL, 0xFDCB57F9C1C8FBD4ULL
        }
    },
    {
        {
            0x4699ABB5C93A08B0ULL, 0x47066CC08B05190DULL, 0xAC13AEF7350DE8BDULL, 0x631645CC2E4825FEULL, 
            0x480D47F44BAEEF09ULL, 0x96AB1A8578D389F6ULL, 0x47EC481D4E3032C8ULL, 0x69483130C620352CULL, 
            0xED5DAF3F4BCE454CULL, 0x8F51737F74B9F521ULL, 0x7B176AF564765E56ULL, 0x74481D42A4A7DF4EULL, 
            0xEBA9F29C121439F3ULL, 0xED7AAB26CF5DB640ULL, 0xB95DB20D0C37DB73ULL, 0x4E56ABD7E9F50039ULL, 
            0xFA8F02B216CAED52ULL, 0x32674CF2183BEE6CULL, 0xCCDF5806A418D852ULL, 0x0A400511AEB795B6ULL, 
            0xAAEEA8B9C6B8F35FULL, 0xB0FFE6D9EF3C9A9EULL, 0x0027FD15F085E99DULL, 0xCA7E635986F7BC23ULL, 
            0xE15424EDEF330669ULL, 0x5928BEA07F25A43FULL, 0xB8296E324CC3D614ULL, 0x83C4CCDF40313716ULL, 
            0xA734A159E36A9188ULL, 0x4880FE8404319D9AULL, 0xA8EDCC584C716E3CULL, 0x8563C2F431BBBEEFULL
        },
        {
            0xBBAFC32CBC96F70BULL, 0x8EE4073B24E39313ULL, 0xE98D6326E2AC3B48ULL, 0x97264C2E64C04059ULL, 
            0xF352FE38A8F76FF9ULL, 0x8EF0A16B8758A93EULL, 0xAAF802A07247D23CULL, 0x388D224440E4F84BULL, 
            0x7FC4BC636110B9B2ULL, 0x4763AE9E4707028BULL, 0x6A4972269D5C7A5BULL, 0x0257F6871FD57D59ULL, 
            0x422C3D8BD18C46EFULL, 0x447C488851259E98ULL, 0xD5AF427D5BEDD593ULL, 0x9C7E2846280C1B9FULL, 
            0x60E113D36869B48CULL, 0x4E42CFA25F37392AULL, 0xA42BF1E2542954B7ULL, 0x25C8BABAE4B8FD79ULL, 
            0x77A742E8C7E74B3BULL, 0x5AE98BE442576DB3ULL, 0x96CD76D494C161B8ULL, 0xCBCEB1E33C5BADC2ULL, 
            0xBC29A9D5179FF300ULL, 0xD8D65A599ACB9D3DULL, 0x3336690A900CE0D4ULL, 0x05A896E7F1B818D1ULL, 
            0xA05C53EE89665E4AULL, 0x84C612DCD9F0832CULL, 0x5D6BB9EE5E2813D5ULL, 0xA170FAEEBA926AE1ULL
        },
        {
            0xAB953857B71EBC4CULL, 0x2E2C24CC983F8A22ULL, 0xB24B5F32520F685AULL, 0x11491BF0B704E629ULL, 
            0xA7BF2334998A010AULL, 0x5CFDF11A9613680AULL, 0x99D813D3267240CCULL, 0x203A238E987A3DDBULL, 
            0x1C48A27C43CB4F12ULL, 0x5A9462B2BA919FBFULL, 0xF7636463CF2A5F7BULL, 0x67003832A74AF67EULL, 
            0xD6BA9A5BF8441289ULL, 0xD9E72583BF7B1FF0ULL, 0xFA184C4E481524E5ULL, 0x6FB5AFCCF44B114AULL, 
            0xC1A3F9E7FB77D602ULL, 0xF55675F25410B44EULL, 0x22F027447CC088B2ULL, 0xD28FA7CBDDD85B30ULL, 
            0x5E6EBE6F83455C13ULL, 0x72EA9D6B639D7DD3ULL, 0xFD70618A54CBC42EULL, 0xA58D6359999BEC7FULL, 
            0x319904C49763CBD0ULL, 0xE7A8EF4C079F71C1ULL, 0xE3C7F9434612F6BAULL, 0x9562AE4793847A59ULL, 
            0xD2194105C3EB88A2ULL, 0x9D097A4E7BFBDDA1ULL, 0x7D81753BB5A86ADFULL, 0xFFBD9440080CC76BULL
        },
        {
            0x0513DF808D8235BCULL, 0x4B030EDBAE6481C3ULL, 0x864C90AFA74FB777ULL, 0x83A258D214FF19E8ULL, 
            0x39177DCEBDAD385BULL, 0xB31DB8B6CB09793BULL, 0x1997D3420DE48D19ULL, 0x3C24C8B85C94C6D5ULL, 
            0xDC46FD7DCCB237CFULL, 0xB4C2DE5F86223D5FULL, 0x29556A721CCDFA10ULL, 0x3DF7B78C3CEB1711ULL, 
            0x979F6C94568767CEULL, 0x9D4187161E1134AAULL, 0xBAE25E9BB3837F6BULL, 0xFBCD52CEB31442A7ULL, 
            0x3B9522BC44A029D9ULL, 0xF563E3B104D30284ULL, 0x92288ECBDF9885E4ULL, 0xDF09FAD2B7BCE5E1ULL, 
            0x06C490EC7310568EULL, 0x208309B4D31E8024ULL, 0xB0EDACB604936981ULL, 0xA8806BA2C4A2132FULL, 
            0xD61CB357E1C58C15ULL, 0xADCBD7E63BDC82D6ULL, 0x7835A38AB07FE98CULL, 0x67B5F7DE4825BA8EULL, 
            0x79ED923C2B6C2CCEULL, 0xE394D468F24AC2A7ULL, 0xC75F61A0256D087DULL, 0x5E9A197292BD03A7ULL
        },
        {
            0x712793FC76D617D8ULL, 0xDEBF959F99684CE8ULL, 0x5CD1B6CA8BEC94BBULL, 0x65095471C79ADF9CULL, 
            0xFE8C78FF603BB599ULL, 0xDD894ADB952907F9ULL, 0x65AA60AB70B6A930ULL, 0x3FCBC9191F497EE5ULL, 
            0x1ACF016E59DB7572ULL, 0xCCD823585D755A53ULL, 0xDD519389469C73A0ULL, 0xC0943BE415FAF0B3ULL, 
            0xCC9113B974EB80A2ULL, 0xECD8572E1CAB2BB5ULL, 0x1B3852C0BD7A1E62ULL, 0xC17AF5217B666AF8ULL, 
            0x02F3B31C2402C283ULL, 0xCE6283483428FFF6ULL, 0xD0A45049EF783062ULL, 0x76D41DCC64B28057ULL, 
            0x38E638B49DCD2F8FULL, 0xD3D57B498D233003ULL, 0x83B7C818286A92C7ULL, 0xEB0FE38DD7BA753FULL, 
            0x9871551FA5D352F1ULL, 0x0AD4E9ABB77C0F8DULL, 0x9FFF92957B0ECC04ULL, 0x1878E8BA7833776CULL, 
            0x7A9A57CBB801316FULL, 0x3F9BBE3782CF66EFULL, 0x7B549B88081CE740ULL, 0xBB547B5A0901C03BULL
        },
        {
            0x74425A4EC27DC09DULL, 0x815AA2F0BE81EE4BULL, 0x5D42A872EDECFA15ULL, 0x7BE2DA0CFEE12415ULL, 
            0x6F9E22D91DEDA202ULL, 0x7FCF589206313DC6ULL, 0x5B3A91AA1C38A6A5ULL, 0xD2CEBD6FB0B4AAA4ULL, 
            0x6F01C820847B0B7FULL, 0x720B84D21FD3219DULL, 0x8688FA877674F62BULL, 0x63DAA4CC4E6CC645ULL, 
            0xE3B15C9E70E844E2ULL, 0x22B8CF7E4169D3F6ULL, 0x3F71FE599EF4EA7AULL, 0xE0EA054D6A0891FDULL, 
            0xDE377F13BA2332B0ULL, 0x459C5174E0BA2173ULL, 0x14FA056ECAAAAE33ULL, 0x00BE96EBA4834225ULL, 
            0x8490316EDC99765EULL, 0x34DD585DC438CED5ULL, 0x8498CC2E64787612ULL, 0xEA4CE07052E7BF4DULL, 
            0x30810127B73FA1D9ULL, 0xF924B0ADBCC61A46ULL, 0x6AE01C29956B9376ULL, 0x5C73BAF078556384ULL, 
            0x37D3C8064E430897ULL, 0x43DD8AD48ACBC6D4ULL, 0xB0A8669BB8BF0CB8ULL, 0xDB234B29893A1335ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseDConstants = {
    0xCD4E1C97A03C2136ULL,
    0xBB2C32EDC2C74198ULL,
    0x95122FE7621FA7A5ULL,
    0xCD4E1C97A03C2136ULL,
    0xBB2C32EDC2C74198ULL,
    0x95122FE7621FA7A5ULL,
    0x5CF25E3FCBCF989DULL,
    0x2B671241489045F4ULL,
    0x8E,
    0x3F,
    0x2F,
    0x67,
    0xB8,
    0xDB,
    0x78,
    0x7C
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseESalts = {
    {
        {
            0x86976147ACB5060EULL, 0xCD55218C4B390D68ULL, 0x926DF1F85910CC0BULL, 0x792ADA06DCFC0C9DULL, 
            0x911021FC2B3A2F9FULL, 0x7926869EB101467CULL, 0x82C380FAC8FD4BD1ULL, 0x7116077F58DFB06FULL, 
            0xD88B01D7FD05DEF9ULL, 0xE0B827C21D41AAEFULL, 0x96F72E830122C039ULL, 0x54EB298270A3A762ULL, 
            0xE7C88101A28651D0ULL, 0x6EBDC72CFE6E2A5FULL, 0xA200B479EB7B25D3ULL, 0x8536029FABD880A2ULL, 
            0xF208DB835147BAE9ULL, 0x97A213B466928251ULL, 0xBF9CB3E13A0EBFE1ULL, 0x21CEEDABBB1592CEULL, 
            0x186044F2F205A4C3ULL, 0xC644F1A866A663F0ULL, 0xB34B7CC038C2E940ULL, 0xF937A5E1DC23951BULL, 
            0xBF902F88EEF4AAC0ULL, 0xD8FD3DB4D4F561EBULL, 0xB1CF65C8054B8035ULL, 0x0D49F98B5B3BBB66ULL, 
            0x875ED122066AE74CULL, 0x1A76E8295F4363C1ULL, 0xD80A1912B757D8A6ULL, 0x2DFE1DDEC1D0E20EULL
        },
        {
            0xB3ECF8A88F3B5515ULL, 0x176D1DF36845F9CBULL, 0xCF548DB5B79E8C22ULL, 0xCEE563283D5BFD22ULL, 
            0x09DD82D08A497835ULL, 0xED8EF2941B517820ULL, 0x107BEEA5491E6B91ULL, 0x277650481002194BULL, 
            0xFFEA828D335DA98BULL, 0x41EE6A2D69E04594ULL, 0x934C45198B5DA4EBULL, 0xEC1616F63234247BULL, 
            0x6D9638773851DFFFULL, 0xC634FD26E3794E10ULL, 0xD75B3EB57FFDF457ULL, 0x0E8DDE73633108BDULL, 
            0x08A419EC9A82DAB6ULL, 0x782EA965E3A89CA9ULL, 0x06ED4440EF86C32BULL, 0x7E8D1B916AF43327ULL, 
            0x49D6160D81066231ULL, 0xBAC5AE44223975FEULL, 0x0F744A25630C030DULL, 0x4FE3D3DC861EEF0BULL, 
            0x321830E21ED81131ULL, 0x90ED664FF5A50DC4ULL, 0x7F674E830256CA5CULL, 0xCA6C08E579A3893EULL, 
            0x8B6B9F38CF8351C9ULL, 0xA5F665FC87DCE63EULL, 0x2A86F183B07F8DFEULL, 0xAE58245C53D1B261ULL
        },
        {
            0xBAA6B3B90FDC1B54ULL, 0x86BD2974CC17FF49ULL, 0x181F675B073B87E1ULL, 0x60A1C00F28740869ULL, 
            0x7B16298AB268ECD5ULL, 0xB8C29807EA0171BAULL, 0x054CD61663FBDE10ULL, 0x9F5E1D1705845379ULL, 
            0x898A2469BCA0D265ULL, 0xFBD2311386F5D3FFULL, 0xE353B1D42D664200ULL, 0x2B1EAFA07396D5EDULL, 
            0xD2D42A6D73F28F49ULL, 0xA7B17CB66C19397AULL, 0xAB6370074356E62CULL, 0x44BCB940FDAB9564ULL, 
            0x0E667FE55E9C3A58ULL, 0x4786E67832992C52ULL, 0x0CD45BEB4367A21BULL, 0x8CE0828E1A28BCB6ULL, 
            0x5BB5F4A52C04AD3DULL, 0x2EF3211249A949AFULL, 0xED8908712A5FA167ULL, 0xBF305D5FB0323A81ULL, 
            0x8A5AF0697E9C70E2ULL, 0xCE9D56F23B7647CFULL, 0x247ABF25355A16C5ULL, 0xDEB6A78499E43A2FULL, 
            0xF8B8491D48D76FC1ULL, 0x93BF2E2518B55F96ULL, 0xBB8D642C1E67A998ULL, 0xDA2E80A7FA1A5FCFULL
        },
        {
            0x8711DB6491E30B4DULL, 0xF685101D71A4EE93ULL, 0x6A8122F0199B64ACULL, 0x2B7DDC59537E9C4BULL, 
            0xAC96273B85C7D6C2ULL, 0xD8C06D15E61BB388ULL, 0xB41448435EF22E72ULL, 0x1D98169C139F5D4CULL, 
            0x95BF68CD51FD27D3ULL, 0xB1EE67957FB65366ULL, 0xB2702973013E9182ULL, 0x2E9F6AF4828001EDULL, 
            0x6FB127C30A297AD9ULL, 0x967A1B0A346B052EULL, 0x31B68AF65D4358BEULL, 0xC4358D95C8E35F87ULL, 
            0x0BBFAB0DCCFD54CDULL, 0x831596DF3FCF63ABULL, 0xE59FBFED6076F618ULL, 0xA5127CC26AEDD310ULL, 
            0xB033A22E39CEF129ULL, 0xC1993B5D0794D780ULL, 0x3304BEC86328CEAFULL, 0x90BA99F5CA2ABA8CULL, 
            0xE6E5E89A23DFE30DULL, 0x820C5DDC990C2FA6ULL, 0x8C3987F1A050A206ULL, 0xFD3100A6EFB52D87ULL, 
            0xBF78F5CAFD7A21B5ULL, 0x4FD61B4D1145CC85ULL, 0x656A1C3B71898754ULL, 0x6758D4543F4A82E6ULL
        },
        {
            0xEEB2D6F524AA83AAULL, 0x2C552C709F2B2E55ULL, 0xAFCBAB31EF29062FULL, 0x7E66AF4C7EE5AA19ULL, 
            0x19100F310E5E2F12ULL, 0x0145866EDD7092C7ULL, 0xD0DE4F1011C13CD9ULL, 0xBF707DED90A856FAULL, 
            0x2D65565AB237CF80ULL, 0x095AD6393704AE9AULL, 0x78FF3237B8E4CF4EULL, 0x131FDE1DD779F3CBULL, 
            0xB53BDDF27EB71993ULL, 0x12CC438001E3CBFAULL, 0xE07D922F62B2C37EULL, 0x3A11EE633668F69BULL, 
            0x624782A0E3BA9F26ULL, 0x990D184683BF4759ULL, 0xE30BC68DBF4628DEULL, 0xC3C4F4D3861BF7D8ULL, 
            0x3C3A2C528B767842ULL, 0x9073BE43E9DEC407ULL, 0xB27F680941090CA7ULL, 0x71440C1C5B38BD87ULL, 
            0x822B93FAF5914D5EULL, 0x6A872C13A330C112ULL, 0xF5C7D25F221F903DULL, 0x6981F12B61964959ULL, 
            0x52185481F5B7C9E8ULL, 0xE42AE2420EE48384ULL, 0x664346C9BC9E77EFULL, 0x4406115FE8356942ULL
        },
        {
            0xB443F36761663494ULL, 0x48D3FDAEB00870F4ULL, 0xD5D27C1A3D95E660ULL, 0xAE99F1A288ED1E8EULL, 
            0x56D246FFC46D80D2ULL, 0x49B59C73D599799EULL, 0xB7C734D175CE37B8ULL, 0x24DB8EE27CF956F0ULL, 
            0xCD9F0E5F303F785AULL, 0x9A234CC400CBFD59ULL, 0x6DF64F511C59CCC7ULL, 0x432CB6024EA41921ULL, 
            0x3299E812C8AE5DCAULL, 0x2A1BFB2903A50537ULL, 0x232367C231E5E3DDULL, 0xEB9B56078838DB3BULL, 
            0xC067E5EB479034A6ULL, 0x1CD07A8E56BA52E0ULL, 0x4FBF1623AB43034EULL, 0xBFE3A466C135AE0FULL, 
            0xD5E80D119DBF0F3BULL, 0xDBDD3588979C6A33ULL, 0xFE78C2946EC2E2D8ULL, 0xF407C7F9A0E910ACULL, 
            0x4FADED656E4CE1E3ULL, 0x2B797B8D1E5DD118ULL, 0x57BD43EE8A0E53DAULL, 0x2EB7C802B6A456ECULL, 
            0x07861230C43A0DEAULL, 0x751A134696FEA2DFULL, 0x7FD9E1203347E7B1ULL, 0xDBD7F5AD199BACE7ULL
        }
    },
    {
        {
            0x32C3CCFE4A8CE1A4ULL, 0xCB0D5E0A3AD44DCEULL, 0xB475B08923555593ULL, 0x1709CA9CD5BA176FULL, 
            0x25723DC6A13A945EULL, 0x3C0C73796C2E1DE1ULL, 0x5ED3A36A04F71B48ULL, 0x109D29AEBE1543D7ULL, 
            0xA58218C494B9F63DULL, 0xE2FC96C706087725ULL, 0x8891A6B4883205D7ULL, 0xCB0F09332DF4047CULL, 
            0x06218B4938BFB886ULL, 0x63439F07C8278AB8ULL, 0xF292DF6AFCDAF202ULL, 0x6DA23D9E579CADD1ULL, 
            0x56F0676C1E32CD4AULL, 0x7F1647BFF36B712BULL, 0xDA10155DDEAB2EDBULL, 0xC1725834B908F12EULL, 
            0x25A70587FE95B26EULL, 0x11A7587729A89CA8ULL, 0xD51D7B7806A37B32ULL, 0x6074B572DA4E21E2ULL, 
            0x1927950FC1E19C2EULL, 0x737B62FC026D5636ULL, 0xFD31EDB5B8DF6846ULL, 0xB9A78B671DEB3558ULL, 
            0xC060B6528A10B018ULL, 0x718149A1BAD6C611ULL, 0x21EDEE8FD6E29A70ULL, 0x71F147E75B42459DULL
        },
        {
            0xE1F08F07A20F57D7ULL, 0xC1040229DAB23564ULL, 0x87C9206E547843DCULL, 0xDCD8FB8ADA993CF6ULL, 
            0xDBC511035393D568ULL, 0x11E499A6AA39D0EFULL, 0x9F53AD45EF77ED6BULL, 0xB16CA5686405B4D3ULL, 
            0x6746E329EBFD7D45ULL, 0x7AC60BD2EE21F9CBULL, 0x7820352F93CCE363ULL, 0x3D228544C517F134ULL, 
            0xC5BDEB5EF866B94AULL, 0x122A5440CF257B92ULL, 0x490B3746065BA2E7ULL, 0xA872AB62A6CEFD04ULL, 
            0x3FA7858F0795A036ULL, 0x4DD858DCF8F133DDULL, 0xBA35B3BF7CC1A38EULL, 0xA56AFE3A2EA65157ULL, 
            0xFCD97B9FFAD37F33ULL, 0x1475CA2B14C6AAEDULL, 0xCEE7F226CFE30DBEULL, 0xA6612A4AD655E29EULL, 
            0x61A6889433D3CE11ULL, 0x743B4DA34762E7D4ULL, 0x3834E7A1665DDC16ULL, 0xB8619AADAD2AD573ULL, 
            0x3D4FD986E6D67735ULL, 0x8244FAD706995286ULL, 0xC41D5EB4B8CCC946ULL, 0xEDB9864DA769004EULL
        },
        {
            0x95B64CCE2AB6A75DULL, 0x559F3A12C6483FF4ULL, 0xA564F5EFC53CA151ULL, 0x9CEEA9326CAB65AEULL, 
            0x307D7D43F3C40FEDULL, 0x7D66EC12C6CAC02EULL, 0xF351EF2E9887AB6FULL, 0x82871D5107CCA28CULL, 
            0xFD7EB818456703ECULL, 0x3747727E6C65C1B5ULL, 0xDC4BA0E19EB1E0ACULL, 0xC37CBC04056761CBULL, 
            0x62F92501801D5ED6ULL, 0xC7F00819865AB4D4ULL, 0xEE8FAF935CC920E2ULL, 0xC0C37A194E127A91ULL, 
            0xB83246624E060851ULL, 0xFC831B6B3E6487EBULL, 0x4AECFC7E70042671ULL, 0x210E852796F60597ULL, 
            0x7B148E2F10ED34CBULL, 0xCD97AFA2F04FB738ULL, 0xA0FEF8C63EFC33FFULL, 0xB1E23E109C97C994ULL, 
            0xD196C50A9B33622AULL, 0x753F53456C186E79ULL, 0x5F0F6EAA936AE8C5ULL, 0xF8A9630B06F06F8EULL, 
            0x0ED34F132B0A972CULL, 0x4221800AEA291D9AULL, 0x0E0CCE38102F91AEULL, 0x92601490671BA20DULL
        },
        {
            0x882CB44C404C8916ULL, 0x37777CDD6B091FB1ULL, 0x30958FCC19A80B27ULL, 0x7AF6CD7132AB519DULL, 
            0xF3DD88E8A9FE9B67ULL, 0x07C4B0FEC82FB21DULL, 0x61B709C2B3CC894CULL, 0xE830F744E008F072ULL, 
            0x32F7D4200EA82B5BULL, 0x17B197A65C95D406ULL, 0x103EE6D924702DBCULL, 0xE8696E075A6C35E6ULL, 
            0x0543C8397A8F3035ULL, 0xD538169BAFDB84CAULL, 0xE94C503E0EEE26C1ULL, 0x7E3B3422AE4C36E6ULL, 
            0x1483BE093CDF4D45ULL, 0x23E1A5B0682EC46FULL, 0xD320974D0201FF56ULL, 0x1D411E3C2DF83CF4ULL, 
            0x63DE14995A51BFEEULL, 0x7293ECC155302E2EULL, 0xF1488D34CB057EC6ULL, 0xEF66D5692C9FEF4DULL, 
            0x56F7F5DB595A2896ULL, 0xB6011A15366E534DULL, 0x74666DBD5A1CE034ULL, 0x27980BDB5BA8A500ULL, 
            0x8C187DB22B9B51ABULL, 0xEAC37F56AE0FE6CEULL, 0x1CD848DFC56DCBBBULL, 0x47ABC01214FA9EBAULL
        },
        {
            0xA048DB7560ABDD7BULL, 0xC49FA5FD4FBC96FDULL, 0xA9CF15D481144763ULL, 0x89A5CD4E80A81918ULL, 
            0x761BB0356C6821BBULL, 0x7EBCF8BEBD184085ULL, 0xCBDF61FB0F817413ULL, 0x6B9F3C9384FE7A25ULL, 
            0x7235478977730776ULL, 0x007FC415CBDC4A3AULL, 0x13841AE3B99BCEEBULL, 0xB3F0E029DF2DAC58ULL, 
            0x850FE30B23CEB440ULL, 0xCDDDBF352FE669DBULL, 0x7464E8FAD42FB1AFULL, 0xAFC8C5D597633458ULL, 
            0x43A8D137B2DEA0BCULL, 0x747E939958223FE1ULL, 0x84C4281ADC07339AULL, 0x03E7C623765E8DC9ULL, 
            0xC569565D8D08662BULL, 0x5C658F208E7097ABULL, 0xEBB5CDC53EDEC170ULL, 0x6B4591A1721BAA5DULL, 
            0x262AEBC448A8EF4AULL, 0x22CFCDB742169114ULL, 0xE580E24BB5C90A99ULL, 0xC56F56FDF8EC094EULL, 
            0x7F8E15AC5491D897ULL, 0x90E58AEC5A57E34DULL, 0xB21B265D857B1840ULL, 0x18B12822AC20082CULL
        },
        {
            0x067BC0CD4454C945ULL, 0x5F934F6CCF28948EULL, 0x5187013F1968EB6DULL, 0xD2603EF35E5C3589ULL, 
            0x11018B7A7F374AA4ULL, 0xF10F363BB94E3F14ULL, 0x99690B2CD3B569C5ULL, 0xDA28313C7A6492D0ULL, 
            0x71A23ED2984648C6ULL, 0x2368CF97FACF05F3ULL, 0xA39BD3E550C561F8ULL, 0x066D3B89CE8FDD43ULL, 
            0x0D29CD39B78DA6E7ULL, 0x04BB7992CF5CDA6BULL, 0x7B1664514DB05796ULL, 0x8A0198531951D3EAULL, 
            0xE2FCAFB7B564866BULL, 0x3274FD109E97C516ULL, 0x28926C901AC62DDBULL, 0xDBC6D1876D327EC9ULL, 
            0x026F255111F2814DULL, 0x38A8675078658A9CULL, 0x1EBCB2B861653281ULL, 0xD1CE9977073F6544ULL, 
            0xDE791A23AEEC79BCULL, 0xC5D2D38629BDBDBAULL, 0xE2AA04E12E6F0B6BULL, 0x156752DC785A4449ULL, 
            0xF8B3EADCC552A9CDULL, 0x1E65DB8D18CA0685ULL, 0x699AEC66EC70711EULL, 0xF5495BEDCE39DCFCULL
        }
    },
    {
        {
            0xA88825B25FCABC3CULL, 0x7CD1167627A1C012ULL, 0x6CDDC98B33FE83AEULL, 0xB511980A3C43BDD6ULL, 
            0x23092DF59C945FC3ULL, 0xF093EE155CD9A44BULL, 0xDF7381583CB3BD15ULL, 0xDA54F23D7A6395FEULL, 
            0x01584D43183E2BEBULL, 0xF4D971B42B853E43ULL, 0x946A86FF7D4BE072ULL, 0xFA1639CCB7D56166ULL, 
            0x1CA8FD30C12BB019ULL, 0x97397C60FB956D46ULL, 0x30EED39325F15FFBULL, 0x6B8032FBA015CF9FULL, 
            0x2E2327C0A228A0FDULL, 0xD3A264AB475EA0E2ULL, 0xB864EEB9FCE043A5ULL, 0xEB3DC60D6FBFAE7FULL, 
            0xF92966E359D20CFDULL, 0x0282109E03B92D03ULL, 0x2E1C95B48A945ACDULL, 0x70F2D424AA8E9480ULL, 
            0x070B87B435DBAE76ULL, 0x63C3B13F0262EF7EULL, 0x6C3B2DB3E6511BF8ULL, 0x9086C7219498E315ULL, 
            0x1830AFB745CB1EEDULL, 0xC3DEA7EFCCF2E94CULL, 0x460F472625056FF9ULL, 0xE31C7A34498FA55BULL
        },
        {
            0x9BB6265B8F2952A2ULL, 0xB8A3FB65EA6AC4A0ULL, 0xCBE3B14AD6FE2765ULL, 0x031CB6D9050962FCULL, 
            0x74CB1F67EFDCF952ULL, 0xEA94443DB0847C8EULL, 0xB0E27EC48CE61431ULL, 0x7AA59F90EC3FFA1FULL, 
            0xBC36EF5AAFC185E2ULL, 0xA057F49AB5F288A9ULL, 0x7FCADDFF61776D9CULL, 0x892B80E2F26B3EB5ULL, 
            0x97AEE0F92029F799ULL, 0xFE1E763A6C081C07ULL, 0xCC470D959BC065CFULL, 0x071422B83CB32D26ULL, 
            0x24812BDB34EC4976ULL, 0x3204F24B3ED53E5EULL, 0xD50AAC7C34371DEEULL, 0x2EDC041E27A123A4ULL, 
            0xBD2C2029A80FA960ULL, 0x8497C2D0A89CA906ULL, 0x863C3801BB36A8AAULL, 0x8912972664B96779ULL, 
            0x959705714FC61D93ULL, 0xC5CA6109FFCCA96CULL, 0x150A0C1B63DF5414ULL, 0xB189EFD060ED9BE0ULL, 
            0x5F822B96AEA5A7A5ULL, 0x69DFCC978B2719DAULL, 0x33A81EA826783514ULL, 0x6BA3FA3F9E805AA6ULL
        },
        {
            0xBDB66639CD3DB4FCULL, 0x5C80152BEE96154DULL, 0x8D89CF820E47D7F2ULL, 0xBE2FAAADEC2EDD83ULL, 
            0x6035C692C4214649ULL, 0x9479BC543A5D84BCULL, 0x681F3C2E602D5495ULL, 0xF5D8DBAD519BD785ULL, 
            0x4C9F590A56C722D5ULL, 0xFC8999CD6402B4F9ULL, 0x18177D8D1AA61300ULL, 0x0D7AFE0D73956F70ULL, 
            0x4FA976DD045D6812ULL, 0x9E6A8A60BBE5EDC7ULL, 0x0B0826D7D239B59AULL, 0x9D32810911964B2DULL, 
            0x76E0F5D6178C440DULL, 0xBAA2691F05C74C80ULL, 0xF088B74385F13FEFULL, 0xEFA3023A061AA1D8ULL, 
            0x236E4544BF758CB3ULL, 0x616B961847AC016CULL, 0x5CFDF293AE17B777ULL, 0x668270F722B2ACE2ULL, 
            0x771442C9E5D76B4CULL, 0x5BFC076F63D8DE6BULL, 0x9BAEA28BCA80E889ULL, 0x108D6F795ECE68A0ULL, 
            0x9594FFD2E614E903ULL, 0x51E630457551B02EULL, 0x5AC830A302307A30ULL, 0xAA23904726837091ULL
        },
        {
            0xD84910A72230CB6FULL, 0x8E405A080B2D1699ULL, 0x5FE4D60757295F35ULL, 0x38E1804CF74711C5ULL, 
            0x2FD77E716B111DF8ULL, 0x8D73961364901D88ULL, 0x4F6741C337444115ULL, 0x82D1BD3A15DE0345ULL, 
            0x280F65E07DA56A1BULL, 0xCC89D7402895F1C2ULL, 0x7510BA5F0E8140FEULL, 0x58C3B7EC71F6328BULL, 
            0xE9769A13280FC2D1ULL, 0x8A9CFBD2116B32A2ULL, 0xC16DA83A40F74663ULL, 0x7622CD9586F0F2DBULL, 
            0xA3C2088A1DA31096ULL, 0x509438AE4DFAD91AULL, 0x14A17ADC48BEC4CFULL, 0xB56B6A20ED95F521ULL, 
            0x057C0FA44E792E2AULL, 0x592E9DD782746DC2ULL, 0xAE4D22173E195216ULL, 0x8463DB3472DA02AFULL, 
            0x28D015649D60D962ULL, 0x5FB5F803CBB2EC3CULL, 0xF91B75E93C2E98B9ULL, 0x827AFD66D4C0D9AAULL, 
            0xD7BB0A91C621A17BULL, 0x9B76DDEBFD0EB3B3ULL, 0x954C0E27B520EEC2ULL, 0x795DFF8332A7BEA4ULL
        },
        {
            0x08AD13DC5118F7ADULL, 0x64F4EDFD52B552A4ULL, 0x02956FF568118707ULL, 0x0E9C331F7B3411E5ULL, 
            0x168B46A4D5E12948ULL, 0x2560ED7EF405046FULL, 0x6B419CA1156AD9CAULL, 0xEB2EE77BDD81DF0BULL, 
            0x9633250F62B1F818ULL, 0x9B46A0FA8CF96441ULL, 0x8671BE61289671F1ULL, 0x64A28D01558D2FF0ULL, 
            0x13623A3176D1E043ULL, 0x6EF9BF8D3680DA18ULL, 0x06A277ACDBBD7965ULL, 0x9DB6EA13726503D2ULL, 
            0xCF91A48396DDA60CULL, 0x02823893B2AAFCECULL, 0x7BDBAA524A90276EULL, 0xDD2F984A843BE22BULL, 
            0x5D5A4560340A256FULL, 0x5A8E58320711E96CULL, 0xE8543347990A3818ULL, 0x0E211A859D22A92AULL, 
            0x361D4661BC8E1653ULL, 0x0A143F037D8374AFULL, 0x7AAB26F38523F833ULL, 0x3E7F3605A55284B2ULL, 
            0x0BF274A71E9EB54DULL, 0xC89B7D9E2E49E521ULL, 0x91F9150E358D492DULL, 0xDF82EF8E95EE1D98ULL
        },
        {
            0x16FE2FD3BA97C7E6ULL, 0x14AAFFDCEC577563ULL, 0x37176FD75B4AD0DDULL, 0xED27A8DF9FAAB4B3ULL, 
            0x6ADC585AC2C54134ULL, 0x41CCC56052FDB276ULL, 0xBDE19247D8932792ULL, 0x3230A27A7FB182A0ULL, 
            0xB08CCF6B2BF03E43ULL, 0xD4287E4AB0ED669AULL, 0x59D0333566E75858ULL, 0x9580C89CCF9D0EA6ULL, 
            0x5CA729AE80531EBDULL, 0x4153E8675B4C3628ULL, 0x6C338821D35CCCE4ULL, 0x38162EAB275FD49CULL, 
            0xADD3B2719462A173ULL, 0xE501572022804B87ULL, 0xA18294D74D0189C6ULL, 0x93CBCF16DB16C9AFULL, 
            0x0B67EA4423C38152ULL, 0x80A17AE4073C1113ULL, 0x05EAB5B1AD936F19ULL, 0x10A3FE568546F4D4ULL, 
            0x7E951823DF954D30ULL, 0xB65FA91852EAAF48ULL, 0xD20FF7144B008BDDULL, 0xD2694526E2507A09ULL, 
            0x5F4E048708860936ULL, 0x4C21479C6D4CF891ULL, 0x9D42E7D6AFE209FCULL, 0x9E5E10D1A358A999ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseEConstants = {
    0xC2D75D8B51AFC2DBULL,
    0xA77EB276A5490D33ULL,
    0x7B43B4E6BC297A3EULL,
    0xC2D75D8B51AFC2DBULL,
    0xA77EB276A5490D33ULL,
    0x7B43B4E6BC297A3EULL,
    0xCE689179C3CB43ADULL,
    0xC26787E6216F445CULL,
    0x77,
    0xCE,
    0xB0,
    0x69,
    0xB3,
    0xBA,
    0x62,
    0xFE
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseFSalts = {
    {
        {
            0xE29B3E61855E35CCULL, 0x5AF3E040AFFDBA0AULL, 0xD307AF37768DECC9ULL, 0x038D877A77BC8264ULL, 
            0x6FC19A67F57EB0E2ULL, 0x9D768F16CE8CAE9FULL, 0x177ECA46DBF8B06AULL, 0xCD28B780E5881A07ULL, 
            0x08891A2A996CFD82ULL, 0x737108DA1F19876BULL, 0xAAFB512288EF447DULL, 0xD112A42EC45B3845ULL, 
            0x169D6B37E62A2A27ULL, 0xA503D7C7030E7CAAULL, 0x3FA94D0905F40B5EULL, 0x5E3E27E912734BBDULL, 
            0xA8A34C18B3990257ULL, 0x85C17F45FA3A34E8ULL, 0x2E172F9487CA16B8ULL, 0x7FDC1540C7EDA5E0ULL, 
            0x258E30B839A6D51AULL, 0xE339DF471BB1D3B3ULL, 0x6282E11F2D4EE36AULL, 0xF9A3EE76D0AC5717ULL, 
            0x30477CC0FBF22C31ULL, 0xC588189D16C8D1D4ULL, 0x11EB00C2C9286E5CULL, 0xE776422A2A749285ULL, 
            0x3E0DB2CF31025438ULL, 0x767DF52FD94CF51EULL, 0x01F04706F7C466C0ULL, 0xDDD4FA1ADE5A8029ULL
        },
        {
            0xF48D92B0672F13B3ULL, 0x3DA8B8EA19C90BB8ULL, 0x3B862049A8707B2FULL, 0xD4685B8F572D83F8ULL, 
            0xDBAEEC5FB44DBE11ULL, 0x4F8AF9B04E23A2C0ULL, 0x038531205900046BULL, 0x83FBB24BD7CF5ACEULL, 
            0xE321ECF123F45828ULL, 0xDC1E77980B4C066AULL, 0xD120D651A21F418CULL, 0x3B57508CABA8C11CULL, 
            0x1A378BCEBAE8254FULL, 0x01B1289363C9B4D9ULL, 0xAE7A701BD800C899ULL, 0x2E8F487C726D742CULL, 
            0xA2D75039B84B8D4FULL, 0x2CBDABD55F3748C9ULL, 0x710CA3EB8E6D40BAULL, 0x3D9912BBAFAF93E4ULL, 
            0xE63E3A822D6A050EULL, 0x9FE6A0EBED16117BULL, 0xE15929E764080C4AULL, 0xC2129E2FDF0D02D7ULL, 
            0x18D376E0D9094707ULL, 0x192C2E18EAE1482CULL, 0x95DA75BD091A9B58ULL, 0x9F15ADAB8B7A09FAULL, 
            0x1EE3B45888854922ULL, 0x126BCBB605FB03A1ULL, 0xD9415406FC71F142ULL, 0x1E4AC0930F6DD473ULL
        },
        {
            0xFDAF3EE3CBB26642ULL, 0x88B8EC1D424E6F21ULL, 0xFBB0A6123AAC96CEULL, 0x579861A295066CA2ULL, 
            0x305FC01DB84BF02EULL, 0xF58FBEB8AAA808DAULL, 0xAF0960CB4B4FFEBCULL, 0x0286C3BBBA53AD08ULL, 
            0x2E47F1D299DB085BULL, 0xEB1CF8A867372FF3ULL, 0x357E16C6B8D0216AULL, 0xAA3403262DED24BAULL, 
            0x8CAA8AEB888BD55DULL, 0x32E18B38F40D63D9ULL, 0x034B300ECF59D838ULL, 0xF3A2BA6EC7BB6D33ULL, 
            0xD798C60DC606CA21ULL, 0xDB4E3F2B4A5E88B1ULL, 0x2CB52931C4B29CD6ULL, 0x7F8A02435E2011A6ULL, 
            0x98B9C274C8357A03ULL, 0x5C51486A8A61E9A9ULL, 0x22E0C6EDF3D94D7FULL, 0x936DEF6626897E8BULL, 
            0xE5FF5CFC0E0FB903ULL, 0x0838160B8ACADA33ULL, 0xB7FDA2FCBA14D34FULL, 0xA28A906273A904FBULL, 
            0xD461E5691F98075BULL, 0xA3369073F483B573ULL, 0x213CD1BB3AC0DCC2ULL, 0xF30D1B1C2812C4B4ULL
        },
        {
            0x8621F6D958435150ULL, 0xA86B80A54BC7E31EULL, 0xCE33F65C17966B0FULL, 0xEB5FC4CF13E8C8BDULL, 
            0x3FDF38CBF02D2F72ULL, 0x24E9D92B9FD87040ULL, 0x100D60461DAECA52ULL, 0x4C4F8D583BE5A5F9ULL, 
            0xE1036BC293076C5AULL, 0x6DFF5806B1CCBEB1ULL, 0xE0FE1550520893FCULL, 0x9530CEE65944E9A9ULL, 
            0x160269C8E5FE05AAULL, 0x22C2D34CFC96A2D7ULL, 0x81E7E58F4360BB99ULL, 0x56C3BA175C2053A7ULL, 
            0x20689B1E69857D5AULL, 0x1A7BD9375BADF470ULL, 0x44466F5CF7E21D06ULL, 0x50A9789E2F8366A0ULL, 
            0x93BDB96624E89DACULL, 0x90E8EDB268FC1BF2ULL, 0x2AA165BA6E2A8AD4ULL, 0x6587EE9D438C3778ULL, 
            0xD5ACD89E3D62BDF8ULL, 0x6A93C36207D76915ULL, 0x5B531F9CE6E53AE2ULL, 0xDC37B349E6EBBE31ULL, 
            0x27E43C492FC60106ULL, 0x167512950BD4FA8AULL, 0x75A43C46ABD6078EULL, 0x389A2FBA8D09E4CBULL
        },
        {
            0xC7D8247D3145898BULL, 0x70A87694EA5EF931ULL, 0xFDD6835C00E67A25ULL, 0xF97494D5CC5EF0A4ULL, 
            0x57E3A5D7D7972AE8ULL, 0x09BA0F7718636E2BULL, 0xFEA6F0E1E3D30EC3ULL, 0xE71CAC0DF0355D76ULL, 
            0x959F132549EE7534ULL, 0x0EA6DDB7FDA3398AULL, 0x0EFD93820CE46446ULL, 0x3F8A8A0EEE5627A2ULL, 
            0x7F42D4BF561C6934ULL, 0x8AD2F2A71D0C3AECULL, 0xD052FF6F1A5CEE3CULL, 0x6D73566EF6BE6C1FULL, 
            0xEB117ACC0CF487C5ULL, 0xD874B698CD735E37ULL, 0x55B17EBE09633B14ULL, 0xBDEABEA318B58B69ULL, 
            0x666CF4FA901F71B9ULL, 0xAFF68741526753A1ULL, 0x87C4755E11D4669DULL, 0x0E570ECFC7C16CECULL, 
            0x0965C0434A71F370ULL, 0xB4D557595396A308ULL, 0x20420748868D4F02ULL, 0xF780F1DA6B1F05EDULL, 
            0x2FDDAA5F87B6D87EULL, 0xA87142932EC92EEEULL, 0x5CBD9C89A004D52FULL, 0x6A408F7CE4DAFD21ULL
        },
        {
            0xE211E1F2C10FF3CEULL, 0x8E22DBD862EB6C74ULL, 0xAE857A3F7531C0EEULL, 0xA2BDDBB353DAD5FBULL, 
            0xAE4B7682710DADF9ULL, 0x2D6561FF54D8B8D7ULL, 0xB5A6F004CAC4056CULL, 0x4490C250C7A0F47FULL, 
            0xF8186D2341ABDF93ULL, 0x12E60E5BFCD33CDBULL, 0xE12EFECCF9D3EC3CULL, 0x366060666DC0F4F1ULL, 
            0x4D9D7D0A4012C048ULL, 0x8FB48098531C924BULL, 0x6715F7B09103E53EULL, 0xB0866B18F0338B80ULL, 
            0xE8C9014C814F92ACULL, 0x8E0F7D9F7E38B2EBULL, 0x9BB8BB607774ADE9ULL, 0x6CE3FF0F0FD7CFE0ULL, 
            0xE79722C1CFC4FBE8ULL, 0x84E34AFF676DFBF3ULL, 0x572DCFAAD7455EAFULL, 0x363107E469F1B5D6ULL, 
            0x8A5D25705B204440ULL, 0x6EA53BF700D4F505ULL, 0x734CF626CDA65823ULL, 0x584367D6E5AD11EFULL, 
            0x2F1354F5AA1242FEULL, 0xB32E02B657F2D4F4ULL, 0x17B0A3FCDE54BF40ULL, 0x1226FD7F0E7C8E4DULL
        }
    },
    {
        {
            0xBCF7CBA1B824CFD3ULL, 0x1FC337367451BD19ULL, 0x831977C4F1B95959ULL, 0x1F47D326F0EC1CA1ULL, 
            0x9D60BB95B06AD931ULL, 0x6A94435AFE908375ULL, 0xDA01CC43926C870DULL, 0xFFDB3FA2CD51DB91ULL, 
            0xC63893B348AFFD2AULL, 0x15611071A52D4B40ULL, 0x1AED1C525CF19596ULL, 0x623DB934C40BBE3CULL, 
            0x5756F4D89647BB61ULL, 0xB50AD3B4EE3D2970ULL, 0x61FC9B64680BB914ULL, 0x5526F668D7941801ULL, 
            0xADE2B5C35AA7008FULL, 0xE8BECA83D6CC284DULL, 0x20AD3A2670A79C80ULL, 0xD18731424314694FULL, 
            0xD34663D47D887BC9ULL, 0xA10449A4032A5466ULL, 0x28FCBCE92918634BULL, 0x1A4F5EB7EF2715B3ULL, 
            0x0BCF0BED4F17B269ULL, 0x0DA6DA1EDA09CD8CULL, 0x7E007E62E06FEF71ULL, 0x75D3D43A30284A3AULL, 
            0xF3937036FDBA5FFBULL, 0x0926A157593104E6ULL, 0x15F9EA988CA5747FULL, 0x72E7ABF539B7BDB9ULL
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
            0x55B2CD2ABA2CD567ULL, 0x6E14F8C2B443C4D4ULL, 0x25AD1604741D463DULL, 0x314BB0FCA55A035AULL, 
            0xB8BAC1BD4C203FC3ULL, 0x0AB4E4C306E5855AULL, 0x741F736B1485902FULL, 0xC754F27024D4C7DFULL, 
            0x675B2A720A562858ULL, 0xA0EF4B936A03C2B4ULL, 0xC2D4512562C59BDFULL, 0x5E8032E5DE9D639CULL, 
            0xCD70510DF39E45C5ULL, 0xF2F307EE8C1A5A20ULL, 0xAF8400F550FBA42DULL, 0x49EAE2A335ED07BFULL, 
            0x5A05C15586BF9D61ULL, 0x27DFF8F8F5A9412AULL, 0xCCD4D08C05F43D22ULL, 0x8F2A382987344B82ULL, 
            0x5C7BA4A9F86867C3ULL, 0x85A3BDFEDFCE7D8BULL, 0x902E07A680DDF9D3ULL, 0x3E3E3421E3A089DDULL, 
            0x1504C58A6F17F118ULL, 0xDBC0418136DD8D95ULL, 0x60B2DFD56338E8FCULL, 0x1654369A91600B79ULL, 
            0xF8F272D57C43C2DDULL, 0xDA5EA16859783E10ULL, 0xA0D31AC90227B0F0ULL, 0x922C59C79FC7E695ULL
        },
        {
            0x4C6B8812BF14B817ULL, 0x6F30281BEE55480EULL, 0xDBE976E1A7EBBFF1ULL, 0xE5AB2227E7A4BE1AULL, 
            0x0F2AE7C84C756B88ULL, 0x7A92BC70559E6B4AULL, 0x78B149606B18C641ULL, 0x0EE1D7AC070D9C0DULL, 
            0xC95985C8D3980A19ULL, 0xD0EC32B36CE9B9C0ULL, 0x323897136344E6ECULL, 0x680D96DAC9BFCBA8ULL, 
            0x482CCC5CE43465B9ULL, 0x62E409EE3DEEF54BULL, 0x3C3A4EEB1E823746ULL, 0xD4133A5968A3D5B3ULL, 
            0xD5FA36760F7499D7ULL, 0x52A00B8A94AE5BF6ULL, 0x1764A85B6CFCA262ULL, 0x5BE21CE66E6C752CULL, 
            0x07B35446582819A9ULL, 0x89E1C60ACF5AA10FULL, 0xF2530161E102ECA0ULL, 0x38B1384573F5DC4FULL, 
            0x78573DD086EE7725ULL, 0xFEDC1A9AC9B5042CULL, 0xCE0FA60161AA9EC7ULL, 0xB47FB1F11E73D790ULL, 
            0x37A95E66B8406D17ULL, 0x42EADD0425E8C25DULL, 0xF5BFC304BFCC5082ULL, 0xAEC4866804229E33ULL
        },
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
            0xA9E15CD9394C35A8ULL, 0x46B16EDB0B4A7E6AULL, 0x8DAC46EB150052DFULL, 0x8BCDAD98CA79518AULL, 
            0x5E48FAE56A0E1016ULL, 0x66688F551294188EULL, 0xE99ADE1A938B4444ULL, 0xA91A27A8DA2EC673ULL, 
            0xD7F4434F351E21C2ULL, 0x150F10CFBCC720E6ULL, 0xADD97CC769E1D7BDULL, 0xB44349F69C1CACE3ULL, 
            0x9C8C3D33B707B208ULL, 0x942BC70E2968EDC5ULL, 0xECFADEE7A949FB58ULL, 0x655719B68A59A488ULL, 
            0x3529D372D63C2CC4ULL, 0xCBA44642C911F09EULL, 0xB7B4EC2276552414ULL, 0x28AB2A8D01FC5336ULL, 
            0x462829FFC483756AULL, 0x7FF229DAD9E447DBULL, 0xB7BEF86FCA1D48FDULL, 0xB98F0489C2A83E27ULL, 
            0xF5DD5BE25A6D3102ULL, 0xAA3158CF188D310AULL, 0x768CDF319DE8A353ULL, 0x008639351021115DULL, 
            0xBE0BC1EB0E60A060ULL, 0xEE05A3055508A2A2ULL, 0xCA939329D7CC7CB5ULL, 0x36B7AB2D0056D9C6ULL
        }
    },
    {
        {
            0x5F107EBB0595F459ULL, 0x18DCE8843083840CULL, 0xF44D1A32C65F266FULL, 0xB412C27DF880550FULL, 
            0x3FF69C7DEDD52719ULL, 0x012380EC577733E5ULL, 0xADE9FE47282B1FF4ULL, 0x1CFECAB8FF0E5EA3ULL, 
            0x507258973CD3B2CFULL, 0xD32A91EB4E592555ULL, 0x2B92C2D9D78F8D4DULL, 0x4CF049846E40E6D4ULL, 
            0x5F40EE0218A0E354ULL, 0xD6DA2C1C19982406ULL, 0x9AE4FC43D1F43EF8ULL, 0x5F3C79316FE595BDULL, 
            0x166345631B0576FCULL, 0x233DC01FDEA14D7CULL, 0xF2128779150C292DULL, 0xF64B711ADE38B1E0ULL, 
            0x28635C9781FAB66EULL, 0x921E97DC1E8ECCFEULL, 0xEE425572E4693B7FULL, 0xAFBB46070C3D4362ULL, 
            0xD8FF61840157A92BULL, 0x52423DF21FD91597ULL, 0x5D45A5CA484A3B7DULL, 0x46952EC3F7A458BAULL, 
            0xDDE92FD2BD7A610BULL, 0xA7EDBE281876B53EULL, 0xB486FEE997588E54ULL, 0x03B8DDD84334494AULL
        },
        {
            0x58B7CC2B798E1C67ULL, 0x520461F82850C6F3ULL, 0xA3CA60CEED14614FULL, 0xFF2910F493A45347ULL, 
            0x760CEBEC5C1DF2A2ULL, 0xA7AB261E837DD81AULL, 0x01523B783D66DF06ULL, 0x5142B6C6390661F0ULL, 
            0x5F5D534BAB1CE1E4ULL, 0x141EF176DF8FB6B3ULL, 0xC170992625AF5A57ULL, 0x04863844DE903965ULL, 
            0xD3F6690692E7DD4CULL, 0xE5B8EDDB3B5BA7FBULL, 0x689BA400159AFC93ULL, 0x76150C1DB3342465ULL, 
            0x49570258951DEA08ULL, 0x1CF337B26D53894EULL, 0x1542D90F23027A2EULL, 0x812EAA6253D1199FULL, 
            0x48BEE88D5C209115ULL, 0x673DB86DBF25BF2BULL, 0x87D84D38B8200F11ULL, 0xF59FEDB1730A15CBULL, 
            0x5EDC73B5CD7C5ECEULL, 0x59375F5C4DDB6FE6ULL, 0xF5685A83318849B3ULL, 0x896474E70BBBA310ULL, 
            0xE0446B7A4113C2FDULL, 0x32A954CF0BADBFECULL, 0xDF54CDA457A5E08EULL, 0xF20CE72AEFEA2AB9ULL
        },
        {
            0x80A603DE9949E393ULL, 0x45AFCE3D88A88281ULL, 0x0100429C22D7CEF1ULL, 0xDE924AF31118D26EULL, 
            0x93D0903ABA9E7A77ULL, 0x7D6203CD98E47467ULL, 0x1BC551DCCB313084ULL, 0x3CCB08E4336EABCDULL, 
            0x3FE2BB78FB28D45DULL, 0x85D04875D5E3F3FAULL, 0xE255CE4C29958FA1ULL, 0x8F7303A4630C3FB4ULL, 
            0x9AB50A39F6FDCDA6ULL, 0x7B757EADA8964295ULL, 0x021E86C40DB473D6ULL, 0xCEF9A7118E5C2032ULL, 
            0x3A31B0DDF6995A25ULL, 0xE2EAF19557A4D363ULL, 0xBB991CA1A2D9C9A5ULL, 0xE364A8C4263059C7ULL, 
            0x20A1B1FBA6983D58ULL, 0x53AD18179C2AC342ULL, 0xAAD85C1212D2104AULL, 0x4CDA4DA1D478E263ULL, 
            0x18320810E0A43EC5ULL, 0x26C3D919CD5F6967ULL, 0x393F1C758B1D7FADULL, 0xECDB9525518A19A5ULL, 
            0xA71CEB671BE400CAULL, 0x6CB5D02CC31F209AULL, 0xDF0F16E970FDFA25ULL, 0xE0CC609C3A360601ULL
        },
        {
            0x74CA2E3F4F827E2BULL, 0x93DBA47B6C6A7E64ULL, 0x5FD791E8265181E2ULL, 0x72F54BC27CEAEBE2ULL, 
            0x3CB680D3E046E5DEULL, 0x8DF1DE3D264F7859ULL, 0x3A6C515F3A4D50ACULL, 0xBD92F1600FBEF4BBULL, 
            0x32080930BC3383B9ULL, 0x1B41894B4973356BULL, 0x916F47725A9FDF15ULL, 0x513B024A54B1A998ULL, 
            0xCD735B5FB33DB6F3ULL, 0x20BD6E43C53D58D4ULL, 0xFEF545AF6C2439DAULL, 0xFB452F1832819BBCULL, 
            0x332195DA8D3A1CBEULL, 0xCD532FFA21004AFFULL, 0x5CBFA599D9BF5557ULL, 0x2BC2D929F4957F09ULL, 
            0x4E5DF46408CCE79CULL, 0xFFE4D2EB42B67A8CULL, 0x4EAF2C62DA415EFDULL, 0xD6356A7AF44AD935ULL, 
            0xB5275A0C3F402D6DULL, 0x6AF75554A0FF501BULL, 0x3615B600E87ED8ACULL, 0x4E7AE0DDEB392ACCULL, 
            0xCBAF322DB171544DULL, 0x08C19BCFB5901F2AULL, 0x83F31A506B6BA3BCULL, 0x375620FA6EDD733BULL
        },
        {
            0x7497D3E8F6D3EE0FULL, 0xD80638F26D30B9D5ULL, 0x3B2BFAD9F2329B0EULL, 0xF09B523AA5ED3DDFULL, 
            0x0F3C42C9C678992AULL, 0x6CA6411B362C7F86ULL, 0x6C269DEA73391608ULL, 0x5E478D59852C452DULL, 
            0xD22A8CB409197224ULL, 0x40E0994D7A68603FULL, 0x21692BDF088B8632ULL, 0xE0F82F3CC5BB5A57ULL, 
            0xA183D33E0911CA45ULL, 0xBF4998A620669A4DULL, 0x2B90A15AA2ED5E8EULL, 0x5D56596FBF2073E2ULL, 
            0x8B83AA46231C035BULL, 0x60816518FFA4EDBAULL, 0x7EF02E7E3160763DULL, 0xA1FC8BADAAE88A7BULL, 
            0xE534AFA95EE5C13DULL, 0x6EAE257D6A66F9BAULL, 0xB20DBAF99C693E23ULL, 0x1EC837791C51CC00ULL, 
            0xA1C3F73D7EE5AE13ULL, 0x1B924B7950EE2647ULL, 0xF9A7C4DCDD201A4CULL, 0xCBC0697DC781991AULL, 
            0x9F9019CF0998FE4DULL, 0xD4E28428429B8929ULL, 0x33A97F188724121BULL, 0xD13224D3386A7BE6ULL
        },
        {
            0x15E027EA45547310ULL, 0x196081647D8C2B48ULL, 0x4C86FD103F5560B1ULL, 0x5C93727DCA1A2D38ULL, 
            0xB42E42BD9F463302ULL, 0xFD5A728FF63BA94FULL, 0x640929022E031B1BULL, 0xEFCFDBDAB1676D47ULL, 
            0xCDD4D6D23419FBABULL, 0x9A1E2511123FAF60ULL, 0x3B626EE1AA269CA5ULL, 0x78DD30B7AEEA1C71ULL, 
            0x40317CA9624A7B86ULL, 0x1E16462DE30AEA15ULL, 0x702AD5CBB606D837ULL, 0xBFD34F83D9C03114ULL, 
            0x3424BF7186D1B624ULL, 0x4AEF99E30F014145ULL, 0x10557E8F16A375C0ULL, 0xEA307B60B696BF2FULL, 
            0x07BD8A34AE36E05DULL, 0xF0BF23D25888E364ULL, 0xAF154C6E924FE137ULL, 0x9F9A6CC7ED70C994ULL, 
            0xBF3ACE1F6B84AAA6ULL, 0xD473345DCE656B14ULL, 0xAE62CD8573DB28A6ULL, 0x906F5B15109AD28AULL, 
            0xEBB771918D8E5E47ULL, 0x1E08AF1ADEF8D114ULL, 0xB12F9782C261B2C1ULL, 0x1C207DB05878D513ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseFConstants = {
    0xBD4344CDF8BC4E63ULL,
    0x759D46B87C8457C1ULL,
    0xD6AC65079421578BULL,
    0xBD4344CDF8BC4E63ULL,
    0x759D46B87C8457C1ULL,
    0xD6AC65079421578BULL,
    0xDDD335BC8911BA54ULL,
    0xA38C56DD75F1D53FULL,
    0x11,
    0x12,
    0x60,
    0xFA,
    0x8E,
    0x4C,
    0x6A,
    0x38
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseGSalts = {
    {
        {
            0x52466D4CE4447BE2ULL, 0xB035B505F85DE4ADULL, 0x40E678AFF90DFEF5ULL, 0xDB3617D8E8AA4D11ULL, 
            0xFA1B6E535433E8F4ULL, 0x0F5B8386FDBF11B4ULL, 0x83B8A503B1314FA8ULL, 0x558D267467812B36ULL, 
            0xCB22584ADFE98965ULL, 0xCF5C7BC008EF5761ULL, 0x8A7CF879F6A75511ULL, 0xECC600CBACD4FCCCULL, 
            0x7DA0A282350D5F96ULL, 0x6AA18D0B2E4EC744ULL, 0x6B1BADCC72E8AC60ULL, 0x0EAF3B2961E5E21BULL, 
            0x0091F3FCB2C1D1DCULL, 0xF3F0C952076F9268ULL, 0x40728DFC7B000D7AULL, 0x9F159256BF4D49CCULL, 
            0x8A4D54377F856EBEULL, 0xEB3457D77ADBFCB2ULL, 0x6BD17A3AEEE97043ULL, 0xE3444DCC0F42FAECULL, 
            0xD4F8FACFF2C6FD96ULL, 0x6EE27BF243338C46ULL, 0xD7B0BFE012449BDCULL, 0xB20DBEEEC4634F68ULL, 
            0xD476E55CBBDC7ACAULL, 0x56E22D12195F5206ULL, 0x09D4F0CBBB13E14CULL, 0x0BC95C68C99DA46BULL
        },
        {
            0xFAF57214D21981FBULL, 0xC2F4B00D5D0188D8ULL, 0x8375F2716BD0E389ULL, 0x64655FCE18C09EA6ULL, 
            0xB66DB35704C02D16ULL, 0x7EADCA4A96DA1D22ULL, 0x440185ED31B47CA1ULL, 0x3706B2AE6733A686ULL, 
            0x2F7596FD0AE52C54ULL, 0xF891711775A83037ULL, 0x947DBF9B30CA4F8AULL, 0xB8EEC993290BDCB1ULL, 
            0xF12B965B4EBC46CBULL, 0x1718B76EFC084673ULL, 0x91D80FBD6401EC36ULL, 0x8E01F0D44326363AULL, 
            0xD5267E1A540EFC2DULL, 0x990CD39C9CA8D714ULL, 0xF17824C8A90FBC39ULL, 0x6B98FED0CB7E9594ULL, 
            0x00BE4E5911A54A7AULL, 0x4F9ABAE78F41F32FULL, 0xE08B5B71FFEF4503ULL, 0x9FB86F01CB343248ULL, 
            0x05C6C975A6E28A26ULL, 0xA9DCE238CFD7FB63ULL, 0xEE076D504D93ACB3ULL, 0x7346CB4CE4B60221ULL, 
            0xB61D8E3C9492BB86ULL, 0xC819C50A464D8CE8ULL, 0x3B6E0CC476F40CE0ULL, 0xDF0D8FAE04CC3E85ULL
        },
        {
            0x80FC2F59BD2AC056ULL, 0x7625F49B304F00FCULL, 0x9F552D058D07EAE0ULL, 0xA31ABE6234CC1196ULL, 
            0x9C685AB553064B74ULL, 0x26E1DE08DC362423ULL, 0xA3EAB1F05AEF5761ULL, 0x6B9BBC180B675E62ULL, 
            0xF28753A1FFE2345EULL, 0xCCE72A6FC53BB7BFULL, 0x64CC41C8FF9BFB52ULL, 0xB587B3926FC9F99AULL, 
            0xACCBABA0B9C5513FULL, 0xDE1581C95BB1D8EAULL, 0x5F744D81143F5F1EULL, 0xB12406074D9420F6ULL, 
            0x74FD8BA60D2CBDFDULL, 0xAD5F1A0F237700A6ULL, 0xD0ED035DB475D540ULL, 0xF0495DF20E5ECDE0ULL, 
            0x5EF47FDBC83BF193ULL, 0x3743CC23E7616AE8ULL, 0x98DFEA7B0D9AE94CULL, 0xF81755A4CE09E89CULL, 
            0x998705FF02FF225AULL, 0x001F2A110E651CDAULL, 0x442F9C79FB9BC034ULL, 0x8A7CB001497153E7ULL, 
            0x7066C5C6883C263CULL, 0x72CDADDCAB62C8C9ULL, 0x17160A0F503B3621ULL, 0xDED757DFDE1B88F5ULL
        },
        {
            0x7546BECA200F8E0FULL, 0x1AC7561E1A4ADE4BULL, 0x5B440856CD281F41ULL, 0x25C0EE4DF7408ECBULL, 
            0x119ACE4D38DD2F70ULL, 0xAE99905317110484ULL, 0xC9A90EB8535CC93FULL, 0x5B63DD19F4C91E75ULL, 
            0x622D543E40954978ULL, 0x98E0DD3F3B728F13ULL, 0x2E880913203B3F1AULL, 0x648486F9FA20F707ULL, 
            0xFD95E796FEDC1D19ULL, 0x14E8E6A56C8D6A49ULL, 0xA9178DA49F0C1FB0ULL, 0x36A0E2744732D3D5ULL, 
            0x1E52C8B16D3BA7A8ULL, 0xF8CD7E5B4073015EULL, 0x00C8504304B4ABFBULL, 0xC1A1FF16FCFB06BDULL, 
            0xE3FC3D6F854B4803ULL, 0x029B22C64AF0087DULL, 0x1B3009E35BC10FF5ULL, 0x3BEFD88157C15800ULL, 
            0x125F4985F68598CEULL, 0x510A06CCE138EFAFULL, 0x4E56A4804A2EB3ECULL, 0xB9522CEC7DA6D7ADULL, 
            0xCFD1A2048AE7B250ULL, 0xAB44492F40F2458DULL, 0x4CCBD84118314645ULL, 0xEEAC7AD08ACE08F9ULL
        },
        {
            0x7F65EC483BD7B68FULL, 0x709B99215C6C490AULL, 0xF0E58BFAB45294E0ULL, 0xA9E28D6FB2E4EB0AULL, 
            0xBC56D7C50D77E3DDULL, 0x3790A08306C27B9DULL, 0xF3097CAD29B79DF3ULL, 0x4C786EB772C390E4ULL, 
            0x9BE517C51214101EULL, 0x1370E7646DAF23E4ULL, 0x9F359D0CB48E356FULL, 0x3E5138A7C8A53EE4ULL, 
            0xDF1B5DD3426504BAULL, 0xD7CE9F3E09A609E6ULL, 0xDB041330DFDB58CBULL, 0x01F68FBD1FEF773AULL, 
            0x9138762B672EFED0ULL, 0x3BA9F57C5B60CDBBULL, 0x297C011B56343470ULL, 0x48DB8972FB557ED6ULL, 
            0xA13E96429AADDDACULL, 0x3DF675337F1C2C9CULL, 0xD56DEA81AA7FD03BULL, 0x7A66340707171A87ULL, 
            0x95C5F79E01DDF54CULL, 0x909876CA91772289ULL, 0x1C9F97668ABBF6DBULL, 0x4382C7D9D7CD0ACFULL, 
            0x6E67F3C09582500DULL, 0x7639DDCF809E0062ULL, 0x7B52FC0218DAA3B1ULL, 0x5DB3281CCA320B35ULL
        },
        {
            0x179DF0C3B79F7FC5ULL, 0xC181C9FB9E7E27D0ULL, 0x26C1E7272723BC94ULL, 0xFD99C69D637623EDULL, 
            0x494BBCBCF32B0DA3ULL, 0xAE0C9CA0003E74EFULL, 0xFE97018A039B3212ULL, 0x1532F31588A1F2E7ULL, 
            0x7AFF7BEC13AA09EDULL, 0xB4FFB90C8C361A08ULL, 0x773009787BC18EAAULL, 0x4A3C707090A16E96ULL, 
            0x2368D9665AFC230CULL, 0x6345EDE1016CD7D1ULL, 0xF33523F3A2D1229FULL, 0x0405D675853ECE6DULL, 
            0x99A9B8A537933EBAULL, 0x63F4C1E8ED17AC64ULL, 0xAFC7D0197D330EDFULL, 0x883F5610D7AE0477ULL, 
            0x9235E7FAB5749BE7ULL, 0x8B693A9F94A05162ULL, 0xFA2934C71E3127ABULL, 0xD338523D72423926ULL, 
            0xE4D6C5C18E2F7E00ULL, 0xDA1DFEA40F0307E2ULL, 0x274EC56EE76B5C69ULL, 0xBE177B5FD59CDB2BULL, 
            0x852E6675F6C158A1ULL, 0xFDABC418D5C797CAULL, 0xA91565AD835A6293ULL, 0xBE27AAC84C9D0C64ULL
        }
    },
    {
        {
            0xAB6BB2E7AAA1B140ULL, 0xA67212BFB38D6C3AULL, 0x79E6C1FF3453A1E1ULL, 0xDC155B0FF8A167FAULL, 
            0x1AF722D96869C3FCULL, 0x3D0D28D78B584F6BULL, 0xE17E8D81270C981CULL, 0xA2798E6B64276CDFULL, 
            0xDA37591819205432ULL, 0x11362F5EC53180E5ULL, 0xF2F70B80114C4886ULL, 0xCC4D31BB936C35EDULL, 
            0x92981AEF792C4A31ULL, 0x4ED06140F7D6D277ULL, 0x49905D752C6C850DULL, 0x79141410B185E04AULL, 
            0x1C59E8F95EFBCEBFULL, 0x1FE77C2A9C451666ULL, 0x82E4BACE83F15883ULL, 0x8132091DE8B78DB7ULL, 
            0x27A3EF6FD347BFB0ULL, 0xF2127202F2ED6B39ULL, 0xBF44EEEC013AC200ULL, 0x5214B745AB28F41EULL, 
            0xC1ABF5C84376D12AULL, 0xDED7CB284C68B7ABULL, 0x7388ECA42B5F2421ULL, 0xEE2C729D4DD696D7ULL, 
            0x2ED2FE5CCBDC0D39ULL, 0xCB2126F6F82819E0ULL, 0x8B7B4D284D9A3D81ULL, 0x0DB4865357B871E5ULL
        },
        {
            0xB9312664989FB402ULL, 0xA64890D8E102DA0FULL, 0xA6E02B1B42E2B844ULL, 0xFE4F872A8B6AB071ULL, 
            0xBF552DC283DDF32AULL, 0x7045883B652ED156ULL, 0xE2042511D0296CA9ULL, 0x27B2D6AD84BC3CD4ULL, 
            0xE436AB17055C7267ULL, 0xFC7340D6BB83F475ULL, 0xD783285F5EB0EB86ULL, 0xFD69031AD78A428DULL, 
            0x578222E071A2C23CULL, 0x4B05541DD0212DD2ULL, 0x458599D887D1CD99ULL, 0xEB5B68B814963FC0ULL, 
            0x3FD1F007F7DF40C2ULL, 0x644BC12A342AD649ULL, 0xAEC38D7DBFFE56A7ULL, 0xBACB00AC0376B688ULL, 
            0x4B72E90AF5A70EADULL, 0x27E44F542DB362E7ULL, 0xA743269EDA06CF49ULL, 0xB940567EDAFB8534ULL, 
            0xA68BD3A5D9D088FAULL, 0x1DFA90D492924A66ULL, 0xB30CC909A052A71EULL, 0x9C586F772EA08621ULL, 
            0xCD04471432C53075ULL, 0x5950E7A281B11A12ULL, 0xAFB5DCBF6DFD6613ULL, 0x5BF18E8550798855ULL
        },
        {
            0x966BB8B9D362B647ULL, 0xC5517C6BC3DEC252ULL, 0x451C94A08A90CC7BULL, 0xD527DCDAA8CF9166ULL, 
            0xDE495B9DE4F62323ULL, 0xB31E7F6AD570CA72ULL, 0x12AB4181C5736926ULL, 0x86F6DCC426144E1DULL, 
            0x4381A3988D0D18EEULL, 0x8886E447603929F6ULL, 0xB7D0652FBD67F8DDULL, 0xCB7614D919B721A8ULL, 
            0x5BE55369535E1418ULL, 0x8D89C0B9AECD171EULL, 0xD35055FDECB7803CULL, 0xE44EF2CC317E04ADULL, 
            0xE053FC400031AFD7ULL, 0x5931ABC39A2EEBE6ULL, 0x3DA5F3D88B2FE383ULL, 0xA63E5CF05B0DF361ULL, 
            0x5F3CB43F6F838C7DULL, 0x7D9EEE68D4FBF4FDULL, 0xDC20C832A0203FA3ULL, 0xE90FC331011C9F1AULL, 
            0xA49F07E3AA7690DFULL, 0xD81F78B55D6E571DULL, 0x603E7463F79BA2B6ULL, 0x57C0366AC7E947BFULL, 
            0xB8637033E04B4EC6ULL, 0x6C8D23341BA8C85DULL, 0xD5922294BC349416ULL, 0xADD9701FB697A63BULL
        },
        {
            0x38925BD2CD22DE2DULL, 0xC46E6698D923DE93ULL, 0xF5A93F9C7A02645BULL, 0xA0BFA0BECA82D3D8ULL, 
            0x5E7F9C482C7ED5ABULL, 0xFC7BDF842E2B517FULL, 0x0FEE701B49901067ULL, 0x21D0CCD21AF4FF67ULL, 
            0xD5D78B669BAC1BFEULL, 0x203EE1ADC4FF5327ULL, 0x46C3154DBBE8EC77ULL, 0xC6D46CE487A0B971ULL, 
            0x52342927E0E225BFULL, 0xDE06F29A0B8217A7ULL, 0xA5CF7131321F3464ULL, 0x1968AFB6C0DD5E0FULL, 
            0x0D69568A9F2CB8D5ULL, 0x95A138F962D6718DULL, 0x92FA6838AF32B7CCULL, 0x51E5DD1D937D4402ULL, 
            0x599D8929E5137784ULL, 0x7A5D92E77BA50583ULL, 0x2555B389C6144A28ULL, 0x84BE757E42EE11D1ULL, 
            0x8F2054C300E6E87EULL, 0xC3AB62CFE23C84EFULL, 0x3761F12B8703D49DULL, 0x553BA4DDFE47047BULL, 
            0x6D7422937DD861A8ULL, 0x24F18B7C4945B6A4ULL, 0x0A9EC601217097B9ULL, 0x8FE12CF7A71122C4ULL
        },
        {
            0xAE8AD4B4A3751196ULL, 0xFC48858E89BBEC26ULL, 0x0E9AB1030E657BD1ULL, 0x3E57AA24FDE3169AULL, 
            0x477A39591CA8EF7AULL, 0x6B95BC407CBCD47FULL, 0x41BE82EA953F3096ULL, 0xB995C908224587DDULL, 
            0xFAAEBA43F7CD207BULL, 0x9F2C4491B27BE2C1ULL, 0x006DF39BD1E77F15ULL, 0xE4CBD146CD76CC43ULL, 
            0xB78D17DAE38CFA15ULL, 0xBAAE5485754B1E1BULL, 0x933150EF6494986EULL, 0x1228851D5139723DULL, 
            0xD6C636B371B3D9E9ULL, 0x9E080443EBDCCAD4ULL, 0x62CB661BA48BA2ABULL, 0xDF101992133B1637ULL, 
            0xC369F0C41546351BULL, 0x972B7FAEF1EEA2C9ULL, 0x7BEA461EA112999BULL, 0x5A7D001146C8698FULL, 
            0x4784220DBCF45C5FULL, 0xDEF482AFD3AFA01EULL, 0xF6778C16456BF52DULL, 0x33A2716B73EE0159ULL, 
            0x76BAC5BC55264CE7ULL, 0x40BA8DF30EFBE01DULL, 0xF1B101160F8B94F9ULL, 0xEBF8846003F2A4D4ULL
        },
        {
            0x1E59F9884FCB3FEBULL, 0x6BC56B163244AC62ULL, 0xDC9AAE2E59E380D1ULL, 0xAB32372C248BDF99ULL, 
            0x5F95635ED99D14EAULL, 0x0C49E75A2EB2704EULL, 0x87F627F2CB56C44AULL, 0xEC1C3F1B38495BBEULL, 
            0xE15A5D0920C11884ULL, 0xA9A05EAFB5AA770CULL, 0xFFAA74A26A2A4599ULL, 0x3EF517FB415FB18DULL, 
            0x657521BC31032E1BULL, 0xDCF44E65E67C728EULL, 0x2B93F4F05B22CA56ULL, 0xBC13D3E9E22B85F1ULL, 
            0x6DC59E9D3E1AFF5DULL, 0x571B76FB502DB8CEULL, 0x82BA4A8F546EC9E4ULL, 0xE202DFC49F2308B8ULL, 
            0x798246436391EEAEULL, 0x35979A87C23D80B8ULL, 0xC3424F9F07FCB6D6ULL, 0x52149D2F2252ECE6ULL, 
            0xD143FFDA8C64A6D6ULL, 0xD587745D63FEC165ULL, 0xCE827FA1B905CC9EULL, 0x52FC29E3B46886BEULL, 
            0x9873F3A7044F8FCDULL, 0x900142F1C0A0748CULL, 0x897A2673CD49249FULL, 0x79FAE4AA6990465AULL
        }
    },
    {
        {
            0xD8F2A01492E2E2B1ULL, 0xF2DB9E0E799176EFULL, 0x1FE89DD215959177ULL, 0x962BA725E7E56F7FULL, 
            0xC05295681F836EACULL, 0x794FA46706DED32BULL, 0xDC341C9757F3613BULL, 0x91010AA5D02AC483ULL, 
            0x7B6E988245A84049ULL, 0x1304BD0181362676ULL, 0x010AAB67D2D9D6B4ULL, 0xC1853DB3061633BCULL, 
            0x7BE6947BD97792C7ULL, 0xBE465CE9F64604ADULL, 0xB95CBB9880ED38DEULL, 0xDC168C2636A93928ULL, 
            0x25351667B7298802ULL, 0x3383995BAFA66C71ULL, 0x4C437F7654631A68ULL, 0xBD6676CCDE81E1C6ULL, 
            0xA0BDC19E861C09BDULL, 0x284F03D4511484A9ULL, 0x5D53E694FC7A3471ULL, 0x1506126BE6C0F672ULL, 
            0x2664D31A50A740CFULL, 0xD7753471F807C806ULL, 0xD128BBB389C57101ULL, 0xCE643941613BCB56ULL, 
            0xE7AE82DBC944065CULL, 0x46E5AB2E6F07531EULL, 0x96FB534457FC96D3ULL, 0xFAA107350BA6EC86ULL
        },
        {
            0xD3D02BAB5A7DAD54ULL, 0xC92CAE34F0C14356ULL, 0xFE42FCA6AB7301F1ULL, 0xDFECC0415123A14DULL, 
            0x3DBCD15603DC86EDULL, 0x03C66E6D491CDDE4ULL, 0x1EF7AC1BE8C01C7CULL, 0x0FF5275F11AC91D3ULL, 
            0x67551138705F1CFAULL, 0x5B06DD1D7A70856FULL, 0x3574EE116C138F45ULL, 0x1947EDDEA8FBF269ULL, 
            0x2C68B8B964F93AD4ULL, 0x5460E6E122468CFFULL, 0x76A88CF63B8B1A88ULL, 0x5AF74BD2834F736EULL, 
            0x2DF27389CAE780D1ULL, 0x7F82C03BA276AAE3ULL, 0x890722FE69152700ULL, 0x969FDAE70D9FF2D7ULL, 
            0xE32004ACEA7D9A43ULL, 0x91E8F255BE15738CULL, 0x74320A483630ECC5ULL, 0x9C7E90ECBACEE405ULL, 
            0xCB65F1EBF5390080ULL, 0xEE9CAED13B4620A4ULL, 0xE4C8A6008D31F802ULL, 0xE80CE31FA27D4C77ULL, 
            0x0085AC9B5CAE2B86ULL, 0x228F6EBC7A44DC67ULL, 0x1937D6447F7662B2ULL, 0x06D358093BF63997ULL
        },
        {
            0x1451EE1835EE835AULL, 0x47262B018140E6E0ULL, 0x7FC75510151337E5ULL, 0x98E1773C98BB12F1ULL, 
            0xE9A02ACA6BF382C0ULL, 0xA3455EBDF9789F79ULL, 0x42D2067FFE5A1CE9ULL, 0x6FA448D22349154FULL, 
            0x1A4E9C25E3C41EF0ULL, 0xABF600744DA6A532ULL, 0x22C1367B12A7FF7FULL, 0x5F33EBEF929B64A8ULL, 
            0xC6955BCB278FBF50ULL, 0xAD13CB7928BEBC7DULL, 0x057F8D111D2F3E69ULL, 0x05BC5FBA37325686ULL, 
            0xB1DB3E1CFEA47F7AULL, 0x03A02B2F761BCE8BULL, 0x7151CEB3C36EAB65ULL, 0xAD94F73F7EC7B1ACULL, 
            0x315203EF856E5A80ULL, 0x8B63ABAC84CB2C5CULL, 0xD233B099E124FBFAULL, 0x3F67DEDAEB1AD15AULL, 
            0x217E2C70A5594632ULL, 0x54C010737ECAF252ULL, 0x5F693BB366B0DDC6ULL, 0x3655E322451E1B42ULL, 
            0x96E62907251B215FULL, 0xD45126A138926213ULL, 0x2F35817118C16DDDULL, 0x156B551D3D97AC29ULL
        },
        {
            0xF79DDE4DA19F739CULL, 0xBBD0E97BF835A434ULL, 0x347CDACDBFA4F154ULL, 0x13878EB0562654DAULL, 
            0x26BEB82A8ECD5E50ULL, 0x7626F2FF878B406DULL, 0x68E352F27E47F07DULL, 0x6F53B8573192B545ULL, 
            0x714B38CE4F5A1BEDULL, 0x34635F3A042615B6ULL, 0xFD1FFA49BABC4A80ULL, 0xF0DF391AC3422E2FULL, 
            0xBC1887730DD4363FULL, 0xFE45C6AD7567BF3CULL, 0x5B41C0BA28B7FDFCULL, 0xC58FD0A4D646510AULL, 
            0x525E69850DD80881ULL, 0xE9B6816ACD0FC4F7ULL, 0xF4262E21451C986BULL, 0x89EB8D0D81CC1152ULL, 
            0x2D6B02C8A89B1BC2ULL, 0x156B5D57CE0601A7ULL, 0x7EE8F050076850F6ULL, 0x534EA8FB2523195CULL, 
            0x3613CD07BA420282ULL, 0x1EE9C6972FBCA066ULL, 0xB370AF79FF96D29EULL, 0xC6914821C54903C8ULL, 
            0xCE2E4449E9957113ULL, 0xCF00C52D37C04260ULL, 0x6B4A195AA01B4649ULL, 0xC67BD885202312F9ULL
        },
        {
            0xAAA2FBE9CAACAD18ULL, 0xD752037C6AC7FC25ULL, 0xD87885E8DA88C100ULL, 0xBE35E36F7B11745DULL, 
            0x059CA45C75FB3368ULL, 0xA92DFE39698BC357ULL, 0xE6AF1EAE87315481ULL, 0xDD0D0D5686D33838ULL, 
            0x90752B131A216D6CULL, 0x6C9B4238C212DBA6ULL, 0x4F4511316C8AC073ULL, 0xAC58E0385498F574ULL, 
            0x8741604E75973325ULL, 0x4C141BE51EC94B38ULL, 0xFC69BDC9C8ED98A3ULL, 0x57FD9D108431FE75ULL, 
            0x0139F572691A45ABULL, 0xEE6DFD9593612139ULL, 0xF013F09C51143DA8ULL, 0x709341B8F479A287ULL, 
            0xD0026CC4BCAFA404ULL, 0xED0CBCE93FEE8FC2ULL, 0x701AD4EC978830ABULL, 0x8BA2AD6F99F323B4ULL, 
            0x3D53EFD53FFE99CEULL, 0x80E1BE3BFB906D1EULL, 0x770BF6CA1FB8EA43ULL, 0x21F574F9D5D85426ULL, 
            0x5C9629702EDB875CULL, 0x7773A8C3F5A3E9F1ULL, 0x4997E4BA7090C816ULL, 0xA1116C0D0139D417ULL
        },
        {
            0x9770279B105DB132ULL, 0x42D0E5C8E28B0E72ULL, 0x9757A75EC0E79DEBULL, 0x6E9424EC8D02C746ULL, 
            0xFB0206335BE49B6CULL, 0x8AE75DA8900B9D41ULL, 0x80AD998F64E5958BULL, 0x2D2D9B65597E3F0FULL, 
            0x39C6030EE72B0118ULL, 0xEF15DEE7E4172B1BULL, 0x0D9588E7C87D1B04ULL, 0xC6E6D1FDE5C41BD1ULL, 
            0xCEBB55D7E3FCBCEDULL, 0x21FD3EC90C5E5D26ULL, 0xA1249EE6A764E145ULL, 0x4E5042E61CEB3B37ULL, 
            0x33D460F79F8B2ACBULL, 0x99988C1AAD24519DULL, 0xDC18CBF4B7F676CDULL, 0x008929990CFDA61BULL, 
            0xB5EFFA890D3FB42AULL, 0x2C26B15F164CD988ULL, 0x2BA273604CFEDAE5ULL, 0x2B0D1047B6023EE7ULL, 
            0x8AE789BB6CA9B61DULL, 0xFC98F7DDB827A90AULL, 0x7E744888B9B1FF63ULL, 0xE72160FAF7A88F89ULL, 
            0x09E65FE568812548ULL, 0x381DD1D44E6959C8ULL, 0xE4EF3B7983D91010ULL, 0xA3F9C50C1F6CF4E9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseGConstants = {
    0x48DF6B62CE3E2780ULL,
    0x33022A46451DA876ULL,
    0xCBF2C527932985BCULL,
    0x48DF6B62CE3E2780ULL,
    0x33022A46451DA876ULL,
    0xCBF2C527932985BCULL,
    0xC57778652D024106ULL,
    0xF98246ABBCA88A84ULL,
    0x38,
    0x3D,
    0x14,
    0x33,
    0x7B,
    0xD5,
    0x08,
    0xC7
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseHSalts = {
    {
        {
            0x2AD953652B423A7FULL, 0x6E97798C15DE3421ULL, 0x045B99CE0EE3A48BULL, 0xC4CC9BBE0ADF4F94ULL, 
            0xBF485B1C639EFDE3ULL, 0x1FF531C402ACC886ULL, 0x1F7127AB04A9511BULL, 0x202D0D4A87199254ULL, 
            0x78A8B3DD66534A97ULL, 0x7DA342A0BC07A3FEULL, 0xAB22183FDB275908ULL, 0x8DC35822A98E1BF3ULL, 
            0x600449585C366B83ULL, 0x19BE9DCE15200E6EULL, 0x0BC147CB25961BDDULL, 0x78322F4ADCAE66B2ULL, 
            0x5D603DE8BE6FFA87ULL, 0xA386113D1CB503ACULL, 0x74ED1E8B56976F1BULL, 0x70394618D7C31C13ULL, 
            0x0C8E98E57199052FULL, 0x72FEE9ADA934A2E6ULL, 0x8C4D3788FC0C1AF3ULL, 0xB210D005C0541369ULL, 
            0xCB23B77C0EAE26B9ULL, 0x39BA4E13FB96548DULL, 0xD0AC671F667581D9ULL, 0x76A7FA7A649AA279ULL, 
            0x9D6E9C24939E1BE9ULL, 0xFD57E7676F177377ULL, 0x1495A55F1AF9120EULL, 0xCCBA4845912660E0ULL
        },
        {
            0xC485DD37B1BC9DB4ULL, 0x18C39325EB4F5A35ULL, 0x9793EC70C4C7A043ULL, 0xB5091A53FFFA3C44ULL, 
            0xD86BF31B196E9E0AULL, 0x12FC4B0E82B26430ULL, 0x8684CFB4C07AB5D7ULL, 0xE0EE2DC2204EC812ULL, 
            0x1CB502B1891263EFULL, 0xEC3744988421462AULL, 0x1CA7CB4E79A14061ULL, 0xBA6B24B66F3002E3ULL, 
            0xE9331FF8DAB6BFE2ULL, 0x1749155DF5CF74FFULL, 0xDAB780F0C5E8BAB5ULL, 0x6CFAEB7946322584ULL, 
            0xC9F5721D4F0D2D59ULL, 0x4D0A7E90F3FEFC83ULL, 0xEF5F796F72D2EB58ULL, 0xFE1EFA336F5CB554ULL, 
            0x7ACE7B921FF39917ULL, 0x53294BE3C49F02BDULL, 0x84AABC73F227F59DULL, 0x2DA0891D9A2DE79DULL, 
            0x3824846F5ABC67FDULL, 0x3D99608E8D90BA08ULL, 0xF41D34DB64468AECULL, 0x7C1E6BA18C889C0FULL, 
            0xFA9D90187381940EULL, 0xCC46661355C3A114ULL, 0x2518DB40DDECBD6FULL, 0xB0BEC8F077FFF89CULL
        },
        {
            0x681206D420310447ULL, 0x0B38C193BA0BFDBFULL, 0xE5E03F46AD073E6CULL, 0xCBDF5313AC8F530AULL, 
            0x5494942A7D861A28ULL, 0x38809FEACC98196BULL, 0xB0024F4284BC79AEULL, 0xF70DAF4C658DB823ULL, 
            0xFFF8332DD660EDF5ULL, 0xBE4005B5E4EDF3A8ULL, 0xEAC87F77BDF7BFE6ULL, 0x5EB08C0B2F20E4F3ULL, 
            0x134444F31A851670ULL, 0x36D88A861C1FCFF5ULL, 0xD73846A5212C0CCDULL, 0x99429A1D6FA1C6FBULL, 
            0xF15D1031D3381CAAULL, 0xC31D4D96D8F7C15EULL, 0x752E2939D9EE07F7ULL, 0x67E711E389090C0FULL, 
            0x9137E662F78A32D6ULL, 0xE23E43C6E660257FULL, 0x2A2589964C956D91ULL, 0x7F5B6F510AC6ECB9ULL, 
            0x3BF470CC46E254FAULL, 0x89AD61C7B87B816AULL, 0x78A0BA9730DBEF83ULL, 0x9CD314011BA861A6ULL, 
            0xE08A29A565090182ULL, 0x7F4D37BFF7AB0013ULL, 0x35632C3352E25C96ULL, 0x5BD8A85AD12D4B9CULL
        },
        {
            0x7BB9E3EE641B9B26ULL, 0xFEACC816B7EF1BFAULL, 0x494C4278EFC52AAEULL, 0xDF5D16705A43D204ULL, 
            0x1716EAAC0DF7C81EULL, 0xBF14437AC6A785FFULL, 0xD5E5FC30D0879587ULL, 0xD4D0B93BDA451D6EULL, 
            0x51EB038FBD670145ULL, 0xE1D3142AA51C6264ULL, 0xDCA476FC25373BEAULL, 0x0899CCCDC13CF8E6ULL, 
            0x22726CA2CBDB7D42ULL, 0xE20820BCB709AEECULL, 0xF916587E1ABF90A9ULL, 0x43362AC65010FBECULL, 
            0x2D8FC3466C1BDDF7ULL, 0xA06EE5A8CAA3987DULL, 0x1CF05064B9518480ULL, 0x4DEAAF63F5005681ULL, 
            0xA1D8E7159894DD14ULL, 0x27B5EEBA07D639EBULL, 0xB131895E355C2E8AULL, 0xE23FCD6413761839ULL, 
            0x5F58BFFFF7E71B53ULL, 0xA2DF7B4DF0917B64ULL, 0x85E2E2BFDBF0EEB6ULL, 0x1C848B703027D89EULL, 
            0x7B468E80139DADA8ULL, 0x34FD439358DFC3CEULL, 0xD97A183BAE369E0CULL, 0x3E343D3BA5F49CF0ULL
        },
        {
            0x7009BFA07B253B77ULL, 0x3197DB7036C31DF1ULL, 0x426FA93F49F75647ULL, 0x4E15F258EA5674B6ULL, 
            0xC2DF137594E65A1DULL, 0xCA0FA8B20CEBCC00ULL, 0x8DC0CAD2CBCA76DFULL, 0xD5154F444B08ABCDULL, 
            0x663D6D887BDD7E09ULL, 0xB9034B1C587983D7ULL, 0x40F266D701E941C5ULL, 0x0FC1A8611768D9F3ULL, 
            0xE7BD62519CCD1004ULL, 0xB6ED2658083A72A6ULL, 0x5D2605C1C047A961ULL, 0xF70C0D16F2B40ADEULL, 
            0xDE1B2C5676D0809FULL, 0x4C8BFA1F2429AEB7ULL, 0xEE74C4130E9CCCB0ULL, 0x22A27D2C6E3A2C28ULL, 
            0x79210609583E5CD8ULL, 0x3EE346DDF6960C1CULL, 0xD3B858F0B39F89DEULL, 0x0D687AE52EF4C4DFULL, 
            0x1D4C2091FB60CB1FULL, 0xBD461BFADEE8274AULL, 0x73F5DD9EB624619AULL, 0x7A11ACDE19998583ULL, 
            0xEDE1BE7576A3A701ULL, 0x1EB1E140CDB9E94EULL, 0x339369B2D75A993BULL, 0xF3CA4E61E5019325ULL
        },
        {
            0x5B6948CCF586AE0DULL, 0x69DFF4104B71EBF2ULL, 0x2480665AA35B349AULL, 0x3EE80BFE72E3868DULL, 
            0x70D70D3366422FE8ULL, 0x6E4368F2F2A16979ULL, 0xF478D2B2BE820BBEULL, 0x72E93072627DE3EDULL, 
            0x794BA60A244BE166ULL, 0xB611C8E8798A673FULL, 0x037C87E07ACA526DULL, 0x614534C112AEF987ULL, 
            0xE372BE309D7DF704ULL, 0xF3DE6F24328FDCA8ULL, 0x4165B0D4822FD428ULL, 0x1CBD1F064506B48DULL, 
            0x7EC3CCD746A198D6ULL, 0x58EC4F3DC69D47D5ULL, 0x44D8146669728B42ULL, 0x6752618203BF8541ULL, 
            0x65DE5225869B54C7ULL, 0x22C44772BB0503A3ULL, 0xCFB2047A2828E809ULL, 0x13069B35DAE39EA8ULL, 
            0xF7A9B9E5C257A4D5ULL, 0x6B3285F2FD5CB26DULL, 0x012969FBB5EB3FFCULL, 0x2E894AE3E6342815ULL, 
            0x34A203FEE99B99FDULL, 0xBAE6E986D3C6860BULL, 0x6B24D2EEB900FDAFULL, 0x085213FF2DE6C2EFULL
        }
    },
    {
        {
            0x4B08AB99BFB35AD9ULL, 0xCB345CA395C39BE4ULL, 0x75FC42389BA2A4E3ULL, 0xE4AD896DAD232E72ULL, 
            0xA96FBFF2F3C4B747ULL, 0xC1F04537BBE46597ULL, 0x196C161491645FCBULL, 0xB15EC3749FEC0A54ULL, 
            0x42CC6AF2A4143C05ULL, 0xCC70423D5B6CC9B8ULL, 0x4E2D2D3086ECB856ULL, 0x6E32D93EF79BB792ULL, 
            0x74FF8078E32A0EB1ULL, 0xF1D8E91F24A1E2C5ULL, 0xA12CB3BC7D516093ULL, 0x9ECC9D5ED81D8D09ULL, 
            0xA8EF06D7C090C509ULL, 0x0E55A8FB9942004DULL, 0x4F44B498F6AF856AULL, 0x68D974F8D26A7418ULL, 
            0x515CF2A0C3608BC2ULL, 0x270E7DA14DB03032ULL, 0x6E52339696E02B26ULL, 0xF85F3FDA9A27EB92ULL, 
            0xC1502193576EE397ULL, 0x95C37A2E6BC42014ULL, 0xBE4473E420897F87ULL, 0x5EA3B8D5F2ADF1F0ULL, 
            0xF701A0E2BA98B3B0ULL, 0x75E0CCF2E6BC77B0ULL, 0xC7E8BB246F44CA23ULL, 0x80721AAF69556682ULL
        },
        {
            0xEB8C3836404D3F4EULL, 0x7C0E06D8341D82A0ULL, 0x76AFF52B8FF3ADC3ULL, 0x7A48DC7DAA96A580ULL, 
            0x3A59E1AF84256C05ULL, 0x5D709D2AE7834552ULL, 0x1F54C00B5B74B5C7ULL, 0x56DD963AC47F5E31ULL, 
            0x1A7FE5064701377BULL, 0xA75E4D0882AD0E55ULL, 0xBD1A153322C5F0A4ULL, 0xEA822C2BD6283B27ULL, 
            0x155FE42BC6B185B1ULL, 0xE3776DFEFA183ABCULL, 0xDBA16F36B767B1C6ULL, 0xF374855D89D92375ULL, 
            0x4600A043A9B6A208ULL, 0x0024F3136E5D1DDBULL, 0xB691F783B4E4FB34ULL, 0xB8BDA82A20277B8BULL, 
            0xF90730D6A2DC893FULL, 0xEDE4AB41DC4A9D54ULL, 0x099A0C5ECCF40932ULL, 0x1A42A7016429A850ULL, 
            0xB8BFE32834692312ULL, 0x975E1CA75FC159B6ULL, 0xB4DC6E3A3838DFBFULL, 0x05488DE584AFD120ULL, 
            0xD057E3405BCB7558ULL, 0xB96BB93626D55FE4ULL, 0x11B2C6AB41971085ULL, 0xBB67158BB6A02E5EULL
        },
        {
            0x96251A0E7C765FFEULL, 0xF0428060092C872DULL, 0x9D43E2371499831FULL, 0x30D87C0B69F24032ULL, 
            0x2F784C37E9DFF024ULL, 0xF7C9A9BB6A88500AULL, 0x4A115BC5A0D65AEBULL, 0x5704A1C9592C694AULL, 
            0x2E6F2DBA236EB458ULL, 0x58664582DA4E889EULL, 0x2694B94871E482D0ULL, 0xCA4AF486DD6124D3ULL, 
            0xB3A7330D7376B508ULL, 0x77C30B21C690E40CULL, 0x6C77DDF88F6D5DEFULL, 0x7EB4E9C1DE10B08EULL, 
            0x3AA9B9B94E11863CULL, 0x2B6720A1779AFC67ULL, 0x22566A429E8E57D8ULL, 0x542B5CD0688850A4ULL, 
            0x9EA6EC980DD079DFULL, 0xF8F80E10AFF201D9ULL, 0x2F04AB75B479C748ULL, 0x9C0D496630C30DD0ULL, 
            0xF4824B3DB15EDCBBULL, 0x16CFFA8CB1826BA9ULL, 0xFF1BA75FA2699BF5ULL, 0x384BA2B74A31A1B5ULL, 
            0xBB81ABF99829226BULL, 0x31A6E03C6458ED60ULL, 0xE8C11E36F13E53D1ULL, 0xA6CA04BD14AC9697ULL
        },
        {
            0x02BB7FE852D1398CULL, 0x6EE335534DFB6345ULL, 0x31F654257461A808ULL, 0x93C59CAD682B36E9ULL, 
            0xE8DA36746DA67549ULL, 0x3A184D045FDE1D5CULL, 0xF9B913F2A5DFEE7BULL, 0xD1561DC8910CD385ULL, 
            0xCC1B6AF4EB023FAFULL, 0x5BB267098D0F8A79ULL, 0x96F454E55F9FD614ULL, 0xD46311C0E04983B1ULL, 
            0x98D020C1E8CE0550ULL, 0x442E3734642CDF9DULL, 0x9BB2AC5387EA553DULL, 0x80748D5C95404A7EULL, 
            0x7D383AF2FC1F5F93ULL, 0xEAABBA5ABEE0FEA7ULL, 0xC4CEF81E903D952CULL, 0xD8967B06C7B8CEF4ULL, 
            0x8C198A20F5B65A0EULL, 0xA10DF760009762B4ULL, 0xD888A14D637AB9CEULL, 0x0863751C83725B14ULL, 
            0x4F6DB08DE8652B82ULL, 0x9FA9CB15A1102E88ULL, 0x2AA7FF1A66019B7AULL, 0x8A4E85FA3660B5CAULL, 
            0x7071B1EB0A436478ULL, 0x412253721CBD4B59ULL, 0xC957E5AF3CB0BA16ULL, 0xCB8761CE5A87F8C0ULL
        },
        {
            0x25F533D0079F66A2ULL, 0xF09230D6D0D757A1ULL, 0x6CB926C6A85C1905ULL, 0xC7E6A698653520A2ULL, 
            0x37178433C7EC09C1ULL, 0x4AA40637AE27E4B2ULL, 0x07A3318AF67FB7D7ULL, 0xE82D6C62D84A0E5CULL, 
            0x8110F2322DAA8277ULL, 0x75439D37DDA12718ULL, 0x375D485A7DF3B904ULL, 0x034D2526BB2AE226ULL, 
            0x1B63F7294A659DB5ULL, 0xE0755E7851C3AFFEULL, 0x6EFD1050F803B5F7ULL, 0x71BA7F8621C97972ULL, 
            0x17243C6C0B3E309DULL, 0xA7165FEB8E4E062FULL, 0x35044D24FDBB5D8FULL, 0x27B8A9877BD71DC3ULL, 
            0xBAF6435734951340ULL, 0x2C3ADC9226DF5223ULL, 0xDCF350FFCB7BED18ULL, 0x9F9E0046A5388FF1ULL, 
            0xF588916772CB945DULL, 0xAEC36D0C0AEFDB01ULL, 0xABB6CDA7AB4133FFULL, 0xCE995C09C9ED98D3ULL, 
            0x59A74AE3D3CE76A2ULL, 0xE0C1CABCEEF55901ULL, 0x801FA03A05AC1B1DULL, 0x59AC6C5DD7DC7B0FULL
        },
        {
            0xCAACB727A9085B8CULL, 0x2A4EFB5448ACE1B0ULL, 0xD9CFDEA462D1C0F3ULL, 0xF75ADE3101DF963DULL, 
            0xCC093EC03748952EULL, 0x21D35CCD968423C9ULL, 0xD44D3FF3C5827839ULL, 0xD50D19E4FB1A2858ULL, 
            0x220B32868F235693ULL, 0xC181338B8AA348D6ULL, 0xDB4F0AA02392AC39ULL, 0x011DF99D5E6894A4ULL, 
            0x8031948E9A5407B5ULL, 0x859A31717CD8F238ULL, 0xE743CCDF1D574542ULL, 0x9216F95C485C3859ULL, 
            0x3DCB7ED52AE67A88ULL, 0xFC2B9A245783BB90ULL, 0x1991C8B80C1DCCECULL, 0xB77B1B15134A82E2ULL, 
            0xAB38AC80293A8F33ULL, 0x230D3548E1D38AB5ULL, 0x7174AEA3C20C7E13ULL, 0x5C1D21003DE433EDULL, 
            0x85E35F44221BBAD4ULL, 0x39BA37870E35FE25ULL, 0x921A0650A498FCEFULL, 0x772ED6B8A772B641ULL, 
            0x7072398E256576EFULL, 0xFB00E3E304E69F8DULL, 0x9DB3EDE20FD6D68BULL, 0xE5D9F4D3E067E74FULL
        }
    },
    {
        {
            0x266FFC53C1F60499ULL, 0x7A23B53357B49215ULL, 0x31438ABE2906CF9FULL, 0x4F5AC9144FF435AFULL, 
            0x429F9D0BBEC34126ULL, 0x421778C8CCA36349ULL, 0x99E7C45CD4152A7BULL, 0xDEF426683BA6F4A4ULL, 
            0x38BE411E1019D21FULL, 0xEE75C36110BB0AD5ULL, 0x220F5DE9DA92CA1EULL, 0xF45FA63F70AFFFA1ULL, 
            0x51926818FA65C9EFULL, 0x2EFA051603B6FFF3ULL, 0x3855B27BEFF02079ULL, 0x79405B15A83FBB96ULL, 
            0xAB28ABCE98AF8F69ULL, 0x63BF2582A5001BCDULL, 0x70B2913BC8FC85FDULL, 0x9F4A8746F3A24BA7ULL, 
            0xED664B3D162FB5C9ULL, 0xD4D7DEB2639DF0D1ULL, 0x1524ABFEC026C4AAULL, 0xD87006DAD80A9DCEULL, 
            0x67FE6A42F920C579ULL, 0x14F5BAF8BDBBAAB7ULL, 0xA9EFE8DA0C6A38B6ULL, 0x5D3193A3B7716504ULL, 
            0xC17F2E05A8161317ULL, 0x82CA176B558A1F4DULL, 0xB11B3ADCA1548C57ULL, 0xC471C271E2CC3422ULL
        },
        {
            0xD92876130A3A93A0ULL, 0xF7DB931F776536CEULL, 0xDE488080DE723A63ULL, 0xFC521C48B0D16C01ULL, 
            0x9C36C61FAB845D9CULL, 0x246B4DEA63189FD5ULL, 0xA9D45E79D42B9B7AULL, 0x097EDB212F66E55DULL, 
            0xBE15E05316AF2D7BULL, 0x8AFB6D8F2F6B907DULL, 0x237170C21AB97C1DULL, 0x0C64CC25F48021F5ULL, 
            0x8B5B89EF1FE1B718ULL, 0x35873D7E160ED308ULL, 0xC2A6BCB55413FA14ULL, 0x4B76DA5FE1778ADFULL, 
            0x784DF33D9142FC32ULL, 0x75B656C74A5CDDC4ULL, 0x1695FD62588BE89EULL, 0x2167675BBD4CDAB8ULL, 
            0xFC2D3B59EEEF29D0ULL, 0x5F337D3CE21797D1ULL, 0x6341005FCA0EB460ULL, 0x2BCBA1C7FBBCFA98ULL, 
            0x80B26DD14A58CE18ULL, 0xAE2D1E1E35B5BFD5ULL, 0x2D41B0552D205532ULL, 0x5FF4347F004C2931ULL, 
            0xEE2DB9E53EBA1587ULL, 0xCBA6E732DBE5CDDDULL, 0xACA5683E3752C291ULL, 0x399B6CB4044D2C65ULL
        },
        {
            0xE8C51D540A6FDB3DULL, 0x3F31C0FEA6C66AF2ULL, 0xDA196B5909D5A8CBULL, 0x410D69BD33FB8F46ULL, 
            0x3EB014EDC317861BULL, 0xFC12A560C0288E5BULL, 0x549C19E048492B5BULL, 0x073B25A50ADA5FEEULL, 
            0x4E9439272043C82BULL, 0xCCC714275881A156ULL, 0x04048EB209DF0B5EULL, 0x6838CB44D42672F4ULL, 
            0x0B6082F9B927DCE6ULL, 0xF18C30E78043E38CULL, 0xBA807F8E4C1EEF63ULL, 0x4E2949D56FFC94F1ULL, 
            0x6EA1E2319E1EC63FULL, 0x3DB2F33E944FDF1DULL, 0x15D36C2BA6602E24ULL, 0x8531641BEE486885ULL, 
            0xDE120FF5B5B9E89CULL, 0x599DD49655D70E1DULL, 0x4CA217CB7D0D7CDAULL, 0x840DB76BE21CA4CAULL, 
            0xB0804E687BE86C3DULL, 0x453E268151DB9AA5ULL, 0x580693F5CC068621ULL, 0xB531A13DBA2CA3A3ULL, 
            0xAC1EE9A969D5EA5FULL, 0x4C7214F70BBE2871ULL, 0x058BD3BAF59DCD8BULL, 0xD68F44A4D101703BULL
        },
        {
            0xB29562F6902DF246ULL, 0xE44E82674B3D2EC8ULL, 0x863F57E4223A81ADULL, 0x2901F86412D34D79ULL, 
            0x728B22487E630006ULL, 0x19FB9A234383FDA7ULL, 0x1BBD451060A1E909ULL, 0x7DF2FBE0DFA4A03EULL, 
            0xEDB8C4C4A04BAB66ULL, 0x0D9FC5386AA0960BULL, 0x4BABFE8B0E5898FFULL, 0x3FBA86B323FFA11FULL, 
            0x724E783CA338FF4BULL, 0x10FD8166F8CF20A5ULL, 0x558BBACE8A060DA4ULL, 0xCC0D1A07BA94333AULL, 
            0x802B062F0409E1FBULL, 0xDDEB1B7ED18A41CEULL, 0xDD8110466E74867EULL, 0x64F7AE362B8DF914ULL, 
            0x73271E42C6F0B51DULL, 0x82FA6036B34876EEULL, 0x7890ABF05C3EBDFBULL, 0xE0C014C141DE5AD3ULL, 
            0x66E4D48395A45155ULL, 0x34C2494EA1F93EB9ULL, 0xE8D2B0F038F280FAULL, 0xC730ACC3D44B4E2DULL, 
            0x3113191FB407498BULL, 0x412A84E63EBE8A99ULL, 0x20FB0281AD2FF50EULL, 0xECF540379ED2298DULL
        },
        {
            0x52D41D2DAB205F63ULL, 0x99B7E67F81383021ULL, 0xBBDC5954A60BBC6AULL, 0x44D1119B6E55E91BULL, 
            0x003AC6F17F877841ULL, 0xEF3FE36CD99C2ABAULL, 0x0D19B23934178463ULL, 0x67DFF2312DA44FA5ULL, 
            0x06CB14854A6092ABULL, 0x9BC8CE58A9CF2B66ULL, 0xEBA4106D3A652595ULL, 0x250CFDD9EB6ECE52ULL, 
            0x01970089953EFBE8ULL, 0x98A7E36BA10D65A4ULL, 0x9FD1C4397497BDE0ULL, 0x9B0AE4F8A485056BULL, 
            0xF9DFBF12049DC80EULL, 0xBE2CF2959B804BDCULL, 0xD35632457D4530D9ULL, 0xA21393FDE7C86113ULL, 
            0x0D9BBFA24D18EB92ULL, 0x7A67FB73F4753FCFULL, 0xEF92FE4D69E666D5ULL, 0x6138FA79F450A5CBULL, 
            0x5DF7315FE0BFF9C2ULL, 0x56D3D05D5AA25B13ULL, 0x1CDD3415F0546BD9ULL, 0x5699D5630F9AA882ULL, 
            0x974D8384ECE5FA7CULL, 0xDC99E395885ACA55ULL, 0x06C191DDFC33BA1EULL, 0x8716D457B01F2266ULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseHConstants = {
    0x93E02CD2606A92D7ULL,
    0x15C8607A62803680ULL,
    0xEFB655970E650449ULL,
    0x93E02CD2606A92D7ULL,
    0x15C8607A62803680ULL,
    0xEFB655970E650449ULL,
    0x0565576A21A9D14FULL,
    0x58B770EC41C8E691ULL,
    0xF0,
    0xE4,
    0x60,
    0x49,
    0x67,
    0x44,
    0x79,
    0x43
};

