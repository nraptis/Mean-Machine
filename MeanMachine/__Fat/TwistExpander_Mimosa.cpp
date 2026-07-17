#include "TwistExpander_Mimosa.hpp"
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

TwistExpander_Mimosa::TwistExpander_Mimosa()
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

void TwistExpander_Mimosa::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB430E0BEB58E4A9AULL; std::uint64_t aIngress = 0xC53DE363ADD9306BULL; std::uint64_t aCarry = 0xFB2EA247AFBA9B09ULL;

    std::uint64_t aWandererA = 0xD677C0ABF6F7DB43ULL; std::uint64_t aWandererB = 0xD5FCF47A88A8E209ULL; std::uint64_t aWandererC = 0xF3BEF4082F4D0121ULL; std::uint64_t aWandererD = 0xEB407104B3CF5022ULL;
    std::uint64_t aWandererE = 0xC860BC0BAB8AC981ULL; std::uint64_t aWandererF = 0x8591ECCC47C63644ULL; std::uint64_t aWandererG = 0x9BE327AF2D83720AULL; std::uint64_t aWandererH = 0xA1D93F974D0064D7ULL;
    std::uint64_t aWandererI = 0xB1FD616CE7144735ULL; std::uint64_t aWandererJ = 0xE2541680C9087409ULL; std::uint64_t aWandererK = 0xC4E477E2CD68EA34ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17025366519896927218U;
        aCarry = 11830362311021751952U;
        aWandererA = 18249737471857292486U;
        aWandererB = 16542907457318899547U;
        aWandererC = 17906934993540492192U;
        aWandererD = 14867356389356180707U;
        aWandererE = 9676364364628148872U;
        aWandererF = 12507705360314774497U;
        aWandererG = 12377972457050507853U;
        aWandererH = 17142074959698328854U;
        aWandererI = 15753147654031725366U;
        aWandererJ = 12910342421151474785U;
        aWandererK = 12372865493565236657U;
    TwistExpander_Mimosa_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mimosa::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE3DF7B005212CB71ULL; std::uint64_t aIngress = 0xC1975967317048D8ULL; std::uint64_t aCarry = 0xFDF070F44CF87E49ULL;

    std::uint64_t aWandererA = 0xB4ABB3D689B751B3ULL; std::uint64_t aWandererB = 0xD868F46E4187D2B4ULL; std::uint64_t aWandererC = 0x8AC536E3BAB5632EULL; std::uint64_t aWandererD = 0xC27B0F987456C5E1ULL;
    std::uint64_t aWandererE = 0xDD095C86FB6BACE2ULL; std::uint64_t aWandererF = 0xAB18E32A4843B62CULL; std::uint64_t aWandererG = 0xDA120DCCF56C4D54ULL; std::uint64_t aWandererH = 0xA4E21F31F548DF24ULL;
    std::uint64_t aWandererI = 0xBCB4FA4FD0A87317ULL; std::uint64_t aWandererJ = 0xB15BF23AEF7E00E4ULL; std::uint64_t aWandererK = 0x9CF1740FC6462137ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11393939911508080463U;
        aCarry = 16032806794474700533U;
        aWandererA = 17870317003291986216U;
        aWandererB = 15497488400319143862U;
        aWandererC = 11624911805165272942U;
        aWandererD = 9945561041237051960U;
        aWandererE = 17077535675664258188U;
        aWandererF = 11427430517736439955U;
        aWandererG = 12462598781574609048U;
        aWandererH = 9968316166985979817U;
        aWandererI = 12746236432496045623U;
        aWandererJ = 15446319353556845177U;
        aWandererK = 12105791857265740497U;
    TwistExpander_Mimosa_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mimosa::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDE25D0C56BE2EB3CULL;
    std::uint64_t aIngress = 0x9C92E5E23DC05631ULL;
    std::uint64_t aCarry = 0xADD424C1985BC375ULL;

    std::uint64_t aWandererA = 0xA6711C494A910A97ULL;
    std::uint64_t aWandererB = 0x942853D339E3FBB7ULL;
    std::uint64_t aWandererC = 0x90811DED3E2AF836ULL;
    std::uint64_t aWandererD = 0xE8C76248F7771D99ULL;
    std::uint64_t aWandererE = 0x8ED7F2801A5912A2ULL;
    std::uint64_t aWandererF = 0xF87BB8AE19EF98D2ULL;
    std::uint64_t aWandererG = 0x9B2BA3E6AC0A49BDULL;
    std::uint64_t aWandererH = 0xDB319F71E5802CA7ULL;
    std::uint64_t aWandererI = 0x8374F4A79CA5428EULL;
    std::uint64_t aWandererJ = 0xA80FCC7583C560A8ULL;
    std::uint64_t aWandererK = 0xC9D3F665DAAC09B1ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    TwistExpander_Mimosa_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Mimosa_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
    TwistExpander_Mimosa_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mimosa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 19 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1794 / 1984 (90.42%)
// Total distance from earlier candidates: 32722
void TwistExpander_Mimosa::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1511U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 973U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 447U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1565U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1310U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1993U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 590U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1510U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 378U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 928U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 395U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 875U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 358U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1574U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 481U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1127U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 276U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 635U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 478U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 200U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 163U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 936U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1405U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 113U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 787U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 44U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 485U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 659U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1273U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 902U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1515U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1282U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1343U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1689U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1712U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1855U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 138U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1278U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 719U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1371U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1711U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 632U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1076U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1145U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1355U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 624U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 643U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 778U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1631U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1500U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 147U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 89U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 353U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 300U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 683U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 487U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1093U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 556U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 647U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 95U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 925U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 611U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 233U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 929U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 482U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 322U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 107U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1550U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 926U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1925U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 193U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1232U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 139U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1675U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1820U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1863U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1473U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 604U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 992U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 90U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 145U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1544U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 463U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1116U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1769U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 448U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1206U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1430U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1385U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1774U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1176U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2015U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1193U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1275U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 910U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1258U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 473U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 786U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 170U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 327U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 660U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1337U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 204U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 918U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1920U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 699U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1676U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1471U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1982U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 267U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 741U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1923U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 944U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1311U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1381U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 978U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 35U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Mimosa::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCC51DC6D32AEBC9AULL; std::uint64_t aIngress = 0xD07A65A5D3B34A4EULL; std::uint64_t aCarry = 0xBCB3F4196049E8C4ULL;

    std::uint64_t aWandererA = 0xBB79705CA5700FA8ULL; std::uint64_t aWandererB = 0xB89E05248809A4F0ULL; std::uint64_t aWandererC = 0xBB4E884A2B8E6BABULL; std::uint64_t aWandererD = 0xC8E1DECA499DEA9AULL;
    std::uint64_t aWandererE = 0x958CDED57C1C8008ULL; std::uint64_t aWandererF = 0xF836F74F23F638F5ULL; std::uint64_t aWandererG = 0xB4CE19895A0B54BDULL; std::uint64_t aWandererH = 0xA2DE179A1DF2EDBEULL;
    std::uint64_t aWandererI = 0xE1FBB3D3B346F991ULL; std::uint64_t aWandererJ = 0xF4D0AA880A042819ULL; std::uint64_t aWandererK = 0xCA6A49437418728EULL;

    // [seed]
        aPrevious = 17746994681294004170U;
        aCarry = 15951570688451976847U;
        aWandererA = 16385507405816366226U;
        aWandererB = 10427040573237022450U;
        aWandererC = 17653860599746927632U;
        aWandererD = 13708200287663260591U;
        aWandererE = 12987867751906069554U;
        aWandererF = 15863058407357512599U;
        aWandererG = 15204085635958675346U;
        aWandererH = 18227192431906051702U;
        aWandererI = 16249163899518068524U;
        aWandererJ = 14027842481510487911U;
        aWandererK = 14517325016767138596U;
    TwistExpander_Mimosa_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Mimosa_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mimosa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 19 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9815; nearest pair: 487 / 674
void TwistExpander_Mimosa::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3698U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5865U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2451U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4319U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4191U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8144U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8040U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1584U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5829U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4508U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8015U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8138U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1148U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 301U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1958U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 342U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1718U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 593U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 897U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 395U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 407U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1459U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 652U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1997U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1983U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1907U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 900U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 248U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1822U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1591U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 92U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1734U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 19 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9794; nearest pair: 451 / 674
void TwistExpander_Mimosa::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6848U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1786U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3997U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6525U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2927U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1476U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2547U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5580U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7580U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5153U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5893U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6167U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1477U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1668U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1519U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 425U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 755U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 147U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1869U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1516U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 914U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1842U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1186U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 595U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 10U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1057U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1797U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1043U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1001U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1368U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1334U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 7U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 860U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1721U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseASalts = {
    {
        {
            0x5E7079D3516C1309ULL, 0x39BCFA9D02F3854BULL, 0x06CA105D33E728DDULL, 0xA5A9AF7C3C07BBD8ULL, 
            0xA6CC92B402C18319ULL, 0x2F2FEF98F6C5FD70ULL, 0xF222F3FD451E85D1ULL, 0x07FC59849D6AAE2EULL, 
            0xFC2FAD86670F758FULL, 0x0A60F40F9A13FAEEULL, 0x86DD9DA1538ED2F5ULL, 0x4544500C1B2871B8ULL, 
            0x5E618D17260307EAULL, 0x8AA5BA3F1C40922FULL, 0xEC1BC55712A3FA74ULL, 0x65595493F34F3964ULL, 
            0xE545142DD9C754D3ULL, 0xE4D7B9DA2125217AULL, 0x562B016E4DF7985BULL, 0x8AF2FD3D30D205D3ULL, 
            0xA5CFD1269DB35CF6ULL, 0x97A993537BBD7001ULL, 0x4B1AC46E27FD16FDULL, 0x27760B6749B94EE9ULL, 
            0xE68264FDCAE1BA12ULL, 0x59B4F4ED87F6AA66ULL, 0x2C7E15D6023EC4C2ULL, 0x8472E83C0881D7E5ULL, 
            0x2B2F9E80C0159A74ULL, 0xB140A38E79828EF0ULL, 0xA7CEC543292E3FE5ULL, 0xCF9594A7C7C1ED48ULL
        },
        {
            0x0DC72022FB716E85ULL, 0x135EB69EE6BB7E8AULL, 0xACB6C8BFA85773A8ULL, 0x7D393C568D060522ULL, 
            0x046FF1FB31767511ULL, 0x60619C80CBDF6BCCULL, 0x600C1073D141DF9EULL, 0x00D0946B34CBFF56ULL, 
            0x05ACCD96C68C213FULL, 0xFE51E018D6758210ULL, 0x7A6A87E6988C823DULL, 0xFEE8B792418F2FBBULL, 
            0xF5F33BE5C2E20E54ULL, 0xF22EA7C97437809BULL, 0x8A21021CBAB1C3CEULL, 0xEDC1B517D9363D54ULL, 
            0xAFC10FAFAF71ADC9ULL, 0xA6F9F13D18F0AD12ULL, 0x7A4443BDB70232E0ULL, 0x7995B6B078F0B908ULL, 
            0x24A1AF9239905C7CULL, 0xF26F4214636960FEULL, 0xFE43DA5C4F45AC83ULL, 0xA0244E8E593347EFULL, 
            0x24F5D5AEC26B5171ULL, 0xC59F4E132D9482B6ULL, 0xFA050738E59C51CAULL, 0xC1FC39032EFC938CULL, 
            0x36678F3FE8E71F79ULL, 0xCFB762FFC89D5E53ULL, 0x42DB8A9C33B4E194ULL, 0x85C6A0F732F02244ULL
        },
        {
            0x6B5DC1786955A9B5ULL, 0x2718DD0095158B42ULL, 0xFA5802862599DEC6ULL, 0x1706452A42B5E5FAULL, 
            0xE9D060BB7DD05E9CULL, 0x43FF2E7F70D9D154ULL, 0x92D4DD6BB1528AE3ULL, 0xFAA81D0708358793ULL, 
            0xDC1FECB71AD4E076ULL, 0x8F7B70800E042B3FULL, 0x927CA46D272384E7ULL, 0x9B1A69E78B5E1A2AULL, 
            0xCFAE19F7EE145A13ULL, 0xA8E69B489178ED88ULL, 0xADF15AFF5F3FE29AULL, 0x9AD7C209DC37D448ULL, 
            0xF0F981E42B29DB7BULL, 0xE9BF95741A9D4C25ULL, 0x6BBC9776D632FB29ULL, 0x98F6AC598DBC569AULL, 
            0x72D8F353F753496AULL, 0xD13D61E6F8FEE2B1ULL, 0x0981D20E3E380ECFULL, 0x60D24D18EB950BCEULL, 
            0xC652DBFE0621CFAEULL, 0x3E74ABC1793652DDULL, 0x5A956E30C1CB72C0ULL, 0xE21E5C4D67DAB517ULL, 
            0x74AB9FEBFAC77E9DULL, 0x0911065E53FF2952ULL, 0xBB52A42D060EFC0FULL, 0xB5630397EEED1D48ULL
        },
        {
            0x92022A5024283BCCULL, 0x9F3426383AE5114DULL, 0x3B6298815C4C2588ULL, 0x47DD53105D1B0CE4ULL, 
            0x4A08A1C980A05EB4ULL, 0x599E47EE91C2EC2DULL, 0xA9290BA5E1EC6ADEULL, 0x49C13BE199BD2C3CULL, 
            0x717A8114B385F9BAULL, 0xAE8E2776CDF0C283ULL, 0x96606E603360AA14ULL, 0xC476B559679D24EEULL, 
            0x4CD46CEAB2A2B814ULL, 0x3651240D8D1E90DEULL, 0xDAD3A0484BF20812ULL, 0x584CBF2BFDCF4B8CULL, 
            0x29FA33E537676435ULL, 0xBD8E4A652AA5786FULL, 0xCE88795129D3BA71ULL, 0x483C30F4BA3139F1ULL, 
            0xC6CCF64903476B21ULL, 0x3A85CFB931269A34ULL, 0x8E4FD155607B6440ULL, 0x436675F4D3AF8587ULL, 
            0x99D260BB5520B701ULL, 0x8C63D04D4B0AD58FULL, 0x7772E2387022B161ULL, 0xBD916FE9DCA52EEFULL, 
            0x34BAC5388CEB0A0AULL, 0x692197925978E625ULL, 0x464F209F527F59BBULL, 0x0305BB7137CB9D26ULL
        },
        {
            0xB047FE34C0F6CB1FULL, 0x448B31997EF6DDBBULL, 0x24FD7FD6202AA613ULL, 0x8B4FC89664A52A5CULL, 
            0x038E72C66F380394ULL, 0x9E280358AC903F5FULL, 0x1D34933920E79A90ULL, 0x50C282515E338F97ULL, 
            0xC65585E7DED0676CULL, 0xB74C4C633850A92DULL, 0x7FB5C4AC4AC8246FULL, 0x93C12486770867A8ULL, 
            0x3C2A3B0949BD6A4EULL, 0xEBEBC9C566E15803ULL, 0x2446AAC93F56A554ULL, 0x2BAB274BF09BDE8EULL, 
            0xDC5E8CC684B538ECULL, 0xEC819100BA399A96ULL, 0xD5129641FD8D4098ULL, 0x4D1E1B93EC05D36DULL, 
            0x2A57ECBD6ABA90C2ULL, 0x7CC87D55F701EA02ULL, 0xD78AE77FA746724BULL, 0xEA742EFD3FBD07E1ULL, 
            0xEE353E6E0A18BA07ULL, 0x155A262203355F4AULL, 0xB1EFA9AC4788B0BBULL, 0xD01EF807F3F6D67FULL, 
            0x36B8FE9ED69F2D56ULL, 0xE73A3DCD483202B9ULL, 0xF7292228C8AE4F01ULL, 0x02A939C508CEF856ULL
        },
        {
            0x53035754EDB822A3ULL, 0xD8ECF03DC6E8B16AULL, 0x94071AC3DEC32930ULL, 0x0EA7A05ACF6CF9F3ULL, 
            0x7D521A5779CA838EULL, 0x4746308C3E066FC9ULL, 0x15325739E0B0E658ULL, 0xD51B2C3F1818C558ULL, 
            0xDF31CA966272A332ULL, 0x8266B4CBF183D5DFULL, 0x39B0171ED75BD9C9ULL, 0xDC0A8EA01DB179C6ULL, 
            0x43C389576BEACB5FULL, 0x7EC51938D72DEC7DULL, 0x115370895CDFF1C3ULL, 0x4E99C3769AA96A20ULL, 
            0x1C40C12E046E6191ULL, 0xA342EEEBEF781B16ULL, 0x7E5A691E7A43B827ULL, 0xA27C728F928FC4BCULL, 
            0x09375DBA7B885030ULL, 0x5A7543ACB06C65E4ULL, 0xA410CA6938CC8685ULL, 0xD1B23C286F2E33A6ULL, 
            0xB8C8271BBF8799F6ULL, 0xA4A8CD21DA0596A1ULL, 0x34634308CD6F9066ULL, 0xE7DAB1660352ACB0ULL, 
            0xD6C3111453A8616EULL, 0xF061ED733A481F7FULL, 0x3E75E58DD5375AB5ULL, 0xE40FDD9D5D9D089BULL
        }
    },
    {
        {
            0x3930EE3E931FE777ULL, 0xCE3BE481CCB6846EULL, 0x032CCD7967198AFFULL, 0xCEEDBA6CFE8A2BC1ULL, 
            0x216B97C01FE5AAB9ULL, 0x79FED422A4496C94ULL, 0xE9AAF2DB5989C339ULL, 0xD1C0678703B691A1ULL, 
            0x80FF89EC2EE715C0ULL, 0x4C8B6902DAA4F834ULL, 0x4D036DB859698263ULL, 0x3DFE5BE643841BF1ULL, 
            0x733B56D018CCA1A0ULL, 0x9C4FF9A5F35196EFULL, 0x12D6C8B62FED3A2BULL, 0xDBA0BB87B6AEDF7CULL, 
            0x2677747E19348E44ULL, 0xE78C9C533715D21CULL, 0xF8A0EDAE39F85770ULL, 0x83B012A49166E98DULL, 
            0xC1F395F246B70EB6ULL, 0xC07556009C645C2BULL, 0x46CF6EC2874DC09CULL, 0xCFB8B2F955F01097ULL, 
            0xF13D7E4B5F30DA15ULL, 0x8279D8666C66F17CULL, 0x6E5DBF0C787EB473ULL, 0x8AA1C057799624B6ULL, 
            0x1DDA7A2ED1260BB4ULL, 0xDBFA7920756D0FCEULL, 0x263CD70C5575D82BULL, 0xCB463C7CC345F014ULL
        },
        {
            0x6075E0F9C9EECEA4ULL, 0x5449F04D27B38D6EULL, 0x82CDE0CE6552293AULL, 0xE774542CE0AFCFBBULL, 
            0xAF5E8F333A7AE563ULL, 0x56FCF279BB60FDCAULL, 0xB358A01D2B6F529CULL, 0x84142296BCF42AC9ULL, 
            0xA51B798866A4F1A7ULL, 0x57B16510EF2811D5ULL, 0x0578258E4E4C43AEULL, 0xC2DAB40C631B5052ULL, 
            0x4D4B9B39E9C6ED28ULL, 0xFF437A8631A20253ULL, 0x541911823AB095ECULL, 0x2B538C769662C17BULL, 
            0xEFA5ACA3F5796C3EULL, 0x463B238D7FABA605ULL, 0xC3FEBF250039DD91ULL, 0xE499926ECA90E397ULL, 
            0xB1B85A2FAB952145ULL, 0xC3FEDBD9AC1E334BULL, 0x2A3CE9115258EB95ULL, 0xD42306BBE0EF3923ULL, 
            0x3C8B032C4935DF4CULL, 0x84DB6E6CE105DB5CULL, 0xD3146E28D6C5B8C0ULL, 0x7DA32011207A1A0CULL, 
            0xFA20407C9F24F71DULL, 0x48D1AB480937179EULL, 0x24D5D02EE8FC801AULL, 0xFB788716A7F2384DULL
        },
        {
            0x81D0151FD4AF5B31ULL, 0x5202F022F2B90839ULL, 0x1076DCBAC4001612ULL, 0xFE028262D9E6D576ULL, 
            0x6E7EA3D6FB4F6C57ULL, 0x311222BEC39F3591ULL, 0xCC3C29450D68B7D2ULL, 0x1A5957429F3E138BULL, 
            0x1D3FCE5FD1C94B65ULL, 0x198E88896FA82A87ULL, 0x951A9781D6FB6EE5ULL, 0xF1D383DAA6A876DFULL, 
            0x8489741F0754A9D9ULL, 0xBA4524C72E07E04EULL, 0xC6A830059DEA10BDULL, 0xF0B4F269BBF1967DULL, 
            0xA74643341201A4A7ULL, 0x66A6376048006887ULL, 0x0B1216791C949519ULL, 0xF6D48FB5882347EDULL, 
            0x010C821792913056ULL, 0x1B52B169AC5BF71DULL, 0xD7A1B71696541FA9ULL, 0xF51BD7C739DD58E7ULL, 
            0xA4C7F175D5B78983ULL, 0xB5EDF96B1BFB956AULL, 0x8FCAADABD5131919ULL, 0x7F7B5261FA52FEF6ULL, 
            0x54888A9908FC9DFCULL, 0x485C775995B0B278ULL, 0x6A2781E07EF71C88ULL, 0x8D373F6B8B329561ULL
        },
        {
            0x4BF3ADC9F0629D9BULL, 0x61FDE6ABDBD76B50ULL, 0xF9D33FB88531D935ULL, 0xB15677E57E067406ULL, 
            0x3B68E792DD9A65C2ULL, 0x17DE3646075B014EULL, 0xB2499D1642536510ULL, 0x0E8BBD342103F5A7ULL, 
            0xC4E2A3C69F2C25F9ULL, 0x7A054DF422C18C3FULL, 0x3A8ED15454959D4EULL, 0x22AFCB7F9EB54E5AULL, 
            0xD9F0F966497B4190ULL, 0xADD8C0B4746A76ECULL, 0xDA95C3E87F3AA40CULL, 0xAC90396BA546AA94ULL, 
            0xD8E7ED2E84C8EE70ULL, 0x9F2E3209F6803A3CULL, 0xB8F5B5F684F90845ULL, 0x2375178E98B9CAD4ULL, 
            0x40135EB6982B6580ULL, 0xC643F70401450787ULL, 0x72C0BCD2780F2DCFULL, 0x5A6AB64F5233CA39ULL, 
            0x90EAE9EB37AAF5A9ULL, 0x362ED735A56BA8E0ULL, 0x6A61D485BE12FA20ULL, 0x77038D66BF733ED6ULL, 
            0x864D4D1F9DEDFCB4ULL, 0x012CDC94598DB4FDULL, 0xBB9BB456DE8162FCULL, 0x392F399888C32B66ULL
        },
        {
            0xFDF3CD5C9F6D353CULL, 0xAA7C691B2606E20BULL, 0x20C1E755DE354C90ULL, 0x00DB596F96C9F696ULL, 
            0xF746D5636A5C3C07ULL, 0x8342CDE4DDEAE968ULL, 0xA8997B37916ABA98ULL, 0x4AEA29455D80383DULL, 
            0xE643FD814EAD9142ULL, 0x5BB1A6A8BE0156B8ULL, 0x562C94D2629D681FULL, 0x8EC290F6C6E1BD12ULL, 
            0x492393A492FAAFB7ULL, 0xA672F06293BF0CC9ULL, 0xA01137F839F3BFDAULL, 0x2132F64A1C29734CULL, 
            0xB7A7948C3EC4DDEDULL, 0x98929C4E8A0E23A3ULL, 0x1CC9CDD59E0D682EULL, 0x8B744F2B600DA778ULL, 
            0x4A9809D060AFC7EEULL, 0xB5C8659B36F421E4ULL, 0xB4D92E53A9FA2BA7ULL, 0xC9B918384B4BA683ULL, 
            0x37417BBE831BDB28ULL, 0xD2792A3DCB2E9A72ULL, 0x48FFC03FD71F1E84ULL, 0x59A3CA83EE94B51AULL, 
            0x0075BE1E2B6E56C3ULL, 0x3545AB3F0E3D1492ULL, 0x782547F75B0890A7ULL, 0x86D3B72A8EF738BDULL
        },
        {
            0xED7EEF190F750C63ULL, 0xFB13540964597CA9ULL, 0x9C02CC90688A1FD3ULL, 0xC7524E7F59465ADDULL, 
            0xBAB9B2A6A7E70E01ULL, 0x80AE782A4D2421D8ULL, 0xDE2926E6B5850189ULL, 0xD0240F7306EF70F6ULL, 
            0x4D7C1BEA25143D26ULL, 0x173354124B615039ULL, 0x7EE68C01D63299D4ULL, 0x721367F19260C0A4ULL, 
            0x618703A12FFC8227ULL, 0xB3B012155B17479CULL, 0x14EAE6FA8D7872C7ULL, 0x4545E1A3E4319F08ULL, 
            0x62ABE176C6903225ULL, 0x9D263B940367DD6CULL, 0xA9E278FD8860BCF4ULL, 0x548B9F768D3DD332ULL, 
            0x0E700D0B97BE93A6ULL, 0x527B7B64AFA129E5ULL, 0x6777114BC024307DULL, 0x6E75BE2D02A287ABULL, 
            0x97D8DAA0C4E6F5ECULL, 0x5D32C9E5795D1B8CULL, 0xBCBC93D97DC4520FULL, 0x1120D5D105F560CFULL, 
            0xC9F7F4E9AEF6EC9EULL, 0xB8E6432565009A1FULL, 0xEC09969FE09F15C5ULL, 0x6184868077B3E428ULL
        }
    },
    {
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
            0x2948B53782B864AFULL, 0xF5A2E1AFE34615E4ULL, 0x513A3576650A6EA4ULL, 0xE0DBFAA5BE61B4A0ULL, 
            0x8C8A60FADAF59429ULL, 0x1A53125A29D008E3ULL, 0x6741268CBBE4D5F8ULL, 0xA04E7F83F517CEBCULL, 
            0xAE56296C4B3EF577ULL, 0xA4A1BCB89B8429CEULL, 0xA9D27B8E2389D088ULL, 0xC2138A56CF113AE1ULL, 
            0xFBF5AC31D18E11FCULL, 0xF8835E63BD93AF57ULL, 0x6A76CC74A45321CCULL, 0x431B625622706605ULL, 
            0x13EF28DA90E60988ULL, 0xD9CC492169AB86B3ULL, 0x35F596B9D8759526ULL, 0x2AF8C35826F4C03FULL, 
            0x8DED6A4DB8B06B4BULL, 0x1D7966941F8A2EE9ULL, 0x2FA428B1797CC6E9ULL, 0x791EA8D2A1926218ULL, 
            0x7EDB04E42072A1EBULL, 0xB3C7FCE3C288E5DBULL, 0x1A7B6AA31654360CULL, 0x14DF4B9B5149B9F6ULL, 
            0xE40EA3DC6FD54410ULL, 0x2F62D6F501550132ULL, 0xCFA9262DEF62B95EULL, 0x4118DBBDC17B8D66ULL
        },
        {
            0xC93565001BF764E8ULL, 0x1CCA323EDB719539ULL, 0xCF23F7B03FFA7DD1ULL, 0xD8B3790482DE6FFBULL, 
            0x11EC9CAEF4BDA35CULL, 0xF2A8D1962C8A1B7EULL, 0xB0BD2D72E25844C4ULL, 0x5FA51DE8B7F94F25ULL, 
            0x0606E95CC12D8FEDULL, 0xF48952243AEA004AULL, 0x3B6749986C0E051FULL, 0x6B31EDD09A146BBAULL, 
            0x6883B086D534F9B7ULL, 0xB834FD7429657C23ULL, 0x13C54202AF8CE966ULL, 0x9E047F2E6F84E162ULL, 
            0x1D9F2CDED31C7197ULL, 0xBB45B53C5725D326ULL, 0x41AA29210778B925ULL, 0xC0137993EBFD217DULL, 
            0x11F33B9F42552ED2ULL, 0xE3EEE934FA0739C2ULL, 0x6381905CBCC18C4AULL, 0xC3799500A4078A37ULL, 
            0x06BA8A0A776FC462ULL, 0x1D00669FD3B78D66ULL, 0x2A5F627773457465ULL, 0x5A98BB03772FC8DEULL, 
            0xA8FB8FE5EC60BE88ULL, 0xA50E989C54C0DBB8ULL, 0x3C4FBE24A7B49C51ULL, 0x3593A6C8048F9E3EULL
        },
        {
            0x44109A8B6B7D6305ULL, 0xE09E04FB1A598568ULL, 0x42CA0505520C8CBDULL, 0x75E644A15148301EULL, 
            0x98036E765F08C6E8ULL, 0xC2841EAD842EBF4FULL, 0x1AD5C07C94DDFBCFULL, 0x2794D8A8B94F43E3ULL, 
            0x6EE61AA68E3A913CULL, 0x137167A15E8D996BULL, 0xD8F65D59C93B975EULL, 0x370C8D54FAA51758ULL, 
            0xCF02A4F467CF6BCCULL, 0x75A620F3F007A91DULL, 0xED99B7BA22736206ULL, 0xAD3F622F248CB67FULL, 
            0x3E43D2997EF93177ULL, 0xD72BD238D72E5EA7ULL, 0x01C60E2377364E2AULL, 0x40529F8AB42A2027ULL, 
            0x1FBAE396B7316330ULL, 0x4D59A19CAC828A20ULL, 0x677252EA6FA0D6FBULL, 0x05026E45FCF443DEULL, 
            0x0520D4CC8E310538ULL, 0xAB1E98CA44F04615ULL, 0xEE723BB135D012E2ULL, 0x8A2D2328DC46D232ULL, 
            0x4DEF3E7BBB8BC596ULL, 0x85E38FC49C0BBC84ULL, 0x6C1E888559295485ULL, 0xBBE3267E3F9354F5ULL
        },
        {
            0xC3D55588B4B734E0ULL, 0x823ED854B5A3DEA9ULL, 0x8DC87DF5741E8F36ULL, 0xED4552A55B5EE1D0ULL, 
            0x5403751F6F65E545ULL, 0xEA09E0C4F8A1B829ULL, 0x46B5697C25C71C2CULL, 0x1FDA8885C3D41402ULL, 
            0xBA0D9DF26878F542ULL, 0x7FDEDFA46E16F44FULL, 0xF8DF726E3056693CULL, 0x85CE95EC2BEAA5D2ULL, 
            0xC1F17FB046EF1CDAULL, 0x5A67A89AD94B1E79ULL, 0x5BCBC37639DE9215ULL, 0xBC8DE11ED4FAC90EULL, 
            0x25451900597BC6AFULL, 0x064AD548E3373D03ULL, 0xCE95A75773E570F6ULL, 0x43FEFC7038AF9D56ULL, 
            0xAA12744F67527DB2ULL, 0x7637FA397D89A603ULL, 0x0101D86D83273A58ULL, 0x5999443680AB320BULL, 
            0x46BD9537AC800F88ULL, 0xC5F3BD7BA39AA526ULL, 0x25407552A450758EULL, 0xED8C8863642AFB90ULL, 
            0xE3DD868F86F36F34ULL, 0xE224751CCF920F31ULL, 0x9CA8E8B23FEF3F40ULL, 0x731CC0CE62F33F28ULL
        },
        {
            0x1B53F16FEF3F6996ULL, 0x8300FE998D237364ULL, 0xBED1BEB5AA4FE9B9ULL, 0xFB55EBA94670682AULL, 
            0x9C0DE7E55EE4D92EULL, 0xB29463E22A1CEE83ULL, 0x49C3E7B15319CDC2ULL, 0xE3314AEA12B6C248ULL, 
            0xCB200CFAEED89498ULL, 0xCCD4F03FB22F32ACULL, 0xA5FFF750333860DDULL, 0x764B8E4754FDF07FULL, 
            0xCDF168A5395E3329ULL, 0x0825B3F208981539ULL, 0xAA6B4F904D88D82FULL, 0xA6852B0D0390B7DEULL, 
            0x961B8CD43AA5069CULL, 0x2C816E7FDB6E5781ULL, 0xBCB7B3D052123F70ULL, 0x2F6BDC51A30D24BAULL, 
            0x54053D9CF6E1CE9BULL, 0xE3B610442152C4F4ULL, 0xF1F1606EE4AD09DBULL, 0xCDA18B78AF6B16F3ULL, 
            0xDB5EAA25555F6F47ULL, 0xC2AF6E01ED058578ULL, 0x32649F9A89C84ABAULL, 0x5E2AD6F53DE5AB78ULL, 
            0x8E723896CFDAF808ULL, 0xEFA03D6531420340ULL, 0x7222F216827D0686ULL, 0x1B37CEA6DCE4D9A7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseAConstants = {
    0x7410B5C036B97BA0ULL,
    0x837F2784A98C4E49ULL,
    0xFA0429EFF0166FC2ULL,
    0x7410B5C036B97BA0ULL,
    0x837F2784A98C4E49ULL,
    0xFA0429EFF0166FC2ULL,
    0xE5B380361F29B913ULL,
    0xD22E8F7FD8F17189ULL,
    0xEB,
    0xAA,
    0x18,
    0xF8,
    0x6D,
    0xAF,
    0x17,
    0xDE
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseBSalts = {
    {
        {
            0x94EB3465633F3681ULL, 0xA1FF074995E00E55ULL, 0x9807DBEAD66C3981ULL, 0xCAE0294EAEFE37FEULL, 
            0x786E9271A22FD58EULL, 0x0CEC9C93AE98BAF5ULL, 0x6FD856D3CCB95645ULL, 0x4208967725567BE1ULL, 
            0x89C9131ECF0B5BD4ULL, 0x2FDB180C2EC1AC2BULL, 0xB36A5306E2EA12C8ULL, 0x66F0DFC3FBB27D45ULL, 
            0x81E6C9758A9505FEULL, 0xD30F3C46E6FBA12AULL, 0xA603B7FEA641A53AULL, 0x7EA68E2AA0C12A05ULL, 
            0x9B10ECB582A6BDF9ULL, 0xAD6E4747681B68FAULL, 0x1B1C97C0CAC6D2D6ULL, 0x8F8A6F25F35C7A77ULL, 
            0x2E27420B54E1A1C0ULL, 0x036044E0210E9230ULL, 0x6106857895FF7528ULL, 0x7711EC86F4EC06C6ULL, 
            0xB0235654CA7D4578ULL, 0xDA48BB15B436C942ULL, 0x2C00EDEDF3041B33ULL, 0x7D08196A4104BD55ULL, 
            0xC3E4BC9512C69288ULL, 0xE78A95DD681FF123ULL, 0x6D0F38F385040DE5ULL, 0x108549234883C707ULL
        },
        {
            0xE6B96214EB62CC2BULL, 0x892D661F442B388BULL, 0xD99469487909E2DAULL, 0xCBC30756BF868FEAULL, 
            0x0ADA9BC16176AC0BULL, 0x3B8664505E874FD8ULL, 0x8725089359DB5C38ULL, 0xD63FE8F42301E314ULL, 
            0x2D071D8C6B89699FULL, 0x65A69A8B00788311ULL, 0xAA74FD4CA4990883ULL, 0x1C646B5EB725E5A0ULL, 
            0xBF4B9A8F3B618675ULL, 0x4F05645069DC0B38ULL, 0x92C16753DE61FF52ULL, 0x589013767794D864ULL, 
            0x95DBACA574293230ULL, 0xC990F57DE762520DULL, 0x072F55547DFA6FF8ULL, 0x849491DDD963BDD5ULL, 
            0xE6ABF3871805116DULL, 0x9B238ADAE129F0A1ULL, 0xA125F44E72058ED5ULL, 0x936ECF56A6B7E233ULL, 
            0x18CAC28667E2DEF2ULL, 0xDAA3E555911038BFULL, 0x5C96ABD450E08956ULL, 0x293FAA33D23F938FULL, 
            0xD1AF6245B89E9D9FULL, 0x7FBF91199FE26715ULL, 0x9FF340C019DD8ABFULL, 0xA52AE6E81814A891ULL
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
            0xC903BB46D8300BFFULL, 0x3E7C395E9EF51C66ULL, 0x2ED6FEE571A7439DULL, 0xFA8DCFCC98631E88ULL, 
            0x7DB70C0963069347ULL, 0x29F3BC1FA7D9CCDEULL, 0x9DE5EF643B56C808ULL, 0xCA97805EF763F235ULL, 
            0x02F653A5D914911CULL, 0x774BBDA8A46073A9ULL, 0x30F241106E28BEA9ULL, 0xE239935B9A9E2DB0ULL, 
            0x7E2B58AF81DC8036ULL, 0xDC45A2F88DCB6735ULL, 0x702C7097DC8C76DFULL, 0x8CB52C00C448F495ULL, 
            0x73572EF4C625471EULL, 0xAF22111A1F31ECE7ULL, 0x8DB7802DC9673D73ULL, 0x6D3378F1218607E1ULL, 
            0x0877B20D4D372A1FULL, 0x057FD69482701ED2ULL, 0xC1C320B10D59B20FULL, 0x10B0016BFFB513B9ULL, 
            0xB18A2633FBD790F4ULL, 0x446E9BCD70E07000ULL, 0x231C6BB459AA519AULL, 0xDC7BC1976B22C5C9ULL, 
            0x0C48C269BD876E52ULL, 0xCA73834C34E5F23BULL, 0x379A3B71182356D1ULL, 0x23938C6E6A829907ULL
        },
        {
            0x3F4C9D9ECEECFAEBULL, 0x40C305A14508138EULL, 0x1B001D9D110AE1B7ULL, 0x0CFC62B3E8A5FA18ULL, 
            0x690E2D8B4B757845ULL, 0x1F9240F585A92F71ULL, 0xB6DF14D6F0630059ULL, 0xDA7D64487040FCE5ULL, 
            0x503DAB2A492130A5ULL, 0x6CC2594F03CE9F22ULL, 0xABC7975A464B1EB1ULL, 0x83AE1A0A37AF4DC2ULL, 
            0x4640CE8C2596AEBDULL, 0x70578AAB18A9D004ULL, 0xA86CB67177717CC0ULL, 0xD7A7FF3664B0923FULL, 
            0xDF51390773420A13ULL, 0x667F041F65E34489ULL, 0x6BB05F0BE79CEAC4ULL, 0xB97C22E661A792E1ULL, 
            0xBF373E3C0F404A4DULL, 0xAB28260CE88FE63FULL, 0x84287DF907972B57ULL, 0x0E678D387C8E17EDULL, 
            0xE123D4A4FCB667D5ULL, 0x6E91348F1B6C9951ULL, 0xDA54833625A4AEA3ULL, 0xFCA54395425563C3ULL, 
            0x17B574F1A898F5D9ULL, 0x27966056BAB02ED0ULL, 0x631445BD6B2BCD0DULL, 0xBC0D4F19446032BCULL
        },
        {
            0x0E0F90393FA38FBCULL, 0x8CAA2A1E94BF7F3DULL, 0x16178E85B3083C0DULL, 0xED6767B78113F92FULL, 
            0xCCE754A0B7FD3B39ULL, 0x14C6B9FA01D0D4F7ULL, 0x33D56DC8A17F8E89ULL, 0x73F0FACC0B3FDD16ULL, 
            0xD5DDC27436337EBAULL, 0x770E51D6FEDD59A1ULL, 0x660DBE9296404A0FULL, 0xC781A947E5026414ULL, 
            0xD97B2DC76C599E54ULL, 0xE3D82E69CED295C4ULL, 0x0DC456F7510C54AFULL, 0xF4A1FA2E8D73DFFDULL, 
            0xC23055C5B3163E69ULL, 0x285EFBB320AB2925ULL, 0xA66180A1AED6694BULL, 0xE025B6A1F3611EF7ULL, 
            0xAB9F44283EDE6EE6ULL, 0xC6A0A3A3CE022C6BULL, 0xE8B2D856A3278FAAULL, 0xAEB8381FB4A20361ULL, 
            0xAE1A3C52C4C7695FULL, 0x6E89E52719E397E2ULL, 0xE5633A1D75AF02CAULL, 0x191F6D033AE24528ULL, 
            0xACF80D57EFD249A4ULL, 0x33E6CE3DDBA2BDEFULL, 0xC7EF1CFA93CBEABAULL, 0x757EB976B4CDBC23ULL
        }
    },
    {
        {
            0xFCEAE85C0E1658C8ULL, 0x0CD3E8BEDBAD0E75ULL, 0x69C91390FD66C93BULL, 0x928E768BA13A0462ULL, 
            0x81AF4FA3748C6324ULL, 0x9F8BBD32C0902323ULL, 0xD5AA91105B70810DULL, 0xAC0E087DE6DE853CULL, 
            0xD18977DD2185C366ULL, 0x061F77740503FE75ULL, 0xCB77262D18785672ULL, 0x7899C5FE544446C7ULL, 
            0xDF61BF0F89FFDA69ULL, 0xADCBA2B1823D495DULL, 0x8FE2270CD6ABC304ULL, 0x160609FEFCC492DBULL, 
            0xA7EA219344A75B23ULL, 0x6ADEBDB4B86110FEULL, 0x4C62382D0477AF58ULL, 0xA22917737177D322ULL, 
            0x22931C9870CB44A0ULL, 0xFA6079BE4FE91904ULL, 0x096CF0D567A40C37ULL, 0xC1DD987CD578C1C7ULL, 
            0xBAB2D096D9082E5EULL, 0x355165FD29959BE0ULL, 0xB7BB36A1598A8E88ULL, 0x7FF4889EF6C5E197ULL, 
            0x6E46BAFD8F2D2A0BULL, 0xFFDF8A8DB9C5201BULL, 0xB359B4EB9490DE87ULL, 0x194A4E37650E487DULL
        },
        {
            0x085CBB8B2A4480E0ULL, 0xC49565494F60D734ULL, 0x9F19F450366566D7ULL, 0x00D3B5BCEF4D5445ULL, 
            0xDBEB729A497130F7ULL, 0x47C6D5B374EFD327ULL, 0x5ADFB4F33DCA57E8ULL, 0x251682C60F38C329ULL, 
            0x4572F55C8A7382CCULL, 0x35F7C425493445D0ULL, 0x231F4CBD29664442ULL, 0x5C076DAF5B9D390AULL, 
            0x495AE997D0DD0DDEULL, 0x48BFF1A17EEF6E7CULL, 0x946C155FDA8F5277ULL, 0xD883C829DBF58236ULL, 
            0x9EFC1200428395F7ULL, 0xB47F5352C52A01E8ULL, 0x85E903313BE33081ULL, 0x946EB2D7E1BB82AFULL, 
            0x8B27D34D1411238FULL, 0x045886253CDB9F6BULL, 0xB9472F700F1B8CF5ULL, 0x428B208A54AE30F4ULL, 
            0xB2FCC7EC5C90E588ULL, 0x237EC2C3009016D9ULL, 0x71191B2EE181F275ULL, 0x9E80D3A2A7DBCA6CULL, 
            0x0766E6BC8756BA37ULL, 0x2DC8991BE1D27C20ULL, 0x0368983E856D369AULL, 0xCD9BC719BEFD72A2ULL
        },
        {
            0x358AF8BE60D8FFD4ULL, 0x557E92339A22AAC9ULL, 0xFDC6A63E403CDED1ULL, 0xE7A9A73EDF75E67DULL, 
            0x6B0F4AE7BA202260ULL, 0x280AB18D032AE28BULL, 0x96D94D48D6B67E99ULL, 0x9F64F741E339BB4FULL, 
            0x898F6BA677836AF0ULL, 0xCF33590931D43556ULL, 0x5E8B7EEDE63CFEB5ULL, 0xF4E2B00D198836ADULL, 
            0xC74AAA5FA59A4A7FULL, 0x8DFA5FC646D46BCCULL, 0xBEB3CF01DD2CB6DDULL, 0xE03D869611153AD8ULL, 
            0x4A5025488BCBECC6ULL, 0x83E1255CE614B0AEULL, 0x22526FACFF3F231DULL, 0x7639BC4DAB32E907ULL, 
            0xEAAB5364BD141403ULL, 0xE17991DCFBEDF738ULL, 0xE1B60277CA692A5CULL, 0xF753CD13CC98D8B5ULL, 
            0x512490329ED4FFA5ULL, 0x1B64A52BBCCA715CULL, 0xE5160A722F523F76ULL, 0xF608D233BD6F7E1FULL, 
            0xEB494C106C6A0DC8ULL, 0xBB28FAA50E1A6206ULL, 0x364B490643E839A1ULL, 0xBB51C1BD3BB196D2ULL
        },
        {
            0x88329EAA845B69AEULL, 0x6D11F52C01883588ULL, 0xEEFF233CA9DA9E68ULL, 0xDF984BE7B3D892CEULL, 
            0xB0673006DE5B3E26ULL, 0xEC3EBB0B08782753ULL, 0xA2F95A74809C5CE3ULL, 0x2FE35F719F29AC24ULL, 
            0xCF3709780BD590FDULL, 0x74B82765912CEA46ULL, 0x4DE4C8310D7102DDULL, 0xF10EB980E10BE22FULL, 
            0x575155D83B031091ULL, 0x51CF00DB6CB11B12ULL, 0x94D64C1AA0E4C486ULL, 0x82E7843A303370C5ULL, 
            0x92168B12A4814CFFULL, 0x7EDBD6FFCAF80AD5ULL, 0x5CB0FDC62DA33C53ULL, 0x9B53B7E601C0E6DEULL, 
            0x4EC7BAA45644DC3DULL, 0x4938C3E6A91C498BULL, 0x4668E4B0670757E1ULL, 0xE9D3A383006D8BF8ULL, 
            0x8761D6860B093D64ULL, 0x8D99A32B95D37ACDULL, 0x6D600A9B791EEF84ULL, 0x18AB266323C9EC4BULL, 
            0x750DA392A22D5AB2ULL, 0x57A1286F249C5124ULL, 0x0DA0A916723B77DCULL, 0x4C1EBA8301761643ULL
        },
        {
            0x7F262C0B87267EB8ULL, 0x8E4F4596409DA883ULL, 0x921FE3E96B93A650ULL, 0xF20C56F6135CCFC5ULL, 
            0x233E73BAC5E3EBF7ULL, 0x7BFBFB802CC45768ULL, 0xD6EDD35E6BF7125BULL, 0x97DCC94603FAAC24ULL, 
            0x5AAC487B2307503BULL, 0xA53059AD61855FFDULL, 0x9AED284DAF8A764CULL, 0x5198532243BF9A1BULL, 
            0xAF109DAD63169A6DULL, 0x41049FDADE9B0BA5ULL, 0x8AD4D2D36DE7D549ULL, 0xB1F07F15A414A3E2ULL, 
            0x8BA90E36E5C6ED7DULL, 0x929DA49F7C242D3FULL, 0x95BCC8A76E47A551ULL, 0x4FB90D485B874213ULL, 
            0xDD6E90DA5E271CF4ULL, 0x728BEDACF1268B1AULL, 0xE39C13C9FE98516AULL, 0x1A3AF6F2CF4EFC5BULL, 
            0xE3D95E3B5BA7B7E6ULL, 0x094A40052127CD85ULL, 0xF43DC52529E275E6ULL, 0x338419AAE72FA615ULL, 
            0x6D6596F8E6A82A12ULL, 0xAC13312E04C90D7BULL, 0x9A43C340597AAC92ULL, 0xE5BBE0CCB396D13DULL
        },
        {
            0x201205B061CF4EA8ULL, 0x74F47CC5FD34EED5ULL, 0xAD70FC886EB5BF2DULL, 0xAC5FFF5C6A5BA97EULL, 
            0x08018FEA7119BF68ULL, 0x79316F879D4808A1ULL, 0x3187E0EEF2A824D0ULL, 0xF8274B179A5DDD37ULL, 
            0xC326BD1AB319FB31ULL, 0x62F566A9B1B47A39ULL, 0xE3DF762D4176C531ULL, 0x809DCA4D8E0CCBE3ULL, 
            0xD694DBB8742F3D6AULL, 0x2CF9F36D5B40FB90ULL, 0x5B1EBC24E9BA1109ULL, 0x132202C7475D0366ULL, 
            0xF614221F57CD2909ULL, 0x4EA84DD674D480FAULL, 0x9CDDC6C07703C507ULL, 0x4C3F506CA26E9EEFULL, 
            0x62DF6326DF22BA09ULL, 0x5C00ECC0FEB868FFULL, 0x8C464FB076795274ULL, 0x337D802C8A30B271ULL, 
            0x78361C196BBDCD6EULL, 0x12FDCFAD4A56EC3FULL, 0xEE1298CCFFD49DB7ULL, 0xC75F4D061DB18F0FULL, 
            0x974464D70DCB8565ULL, 0x60222E05E6811A98ULL, 0x79C6F63B22412950ULL, 0x0A553BAF5B2D9395ULL
        }
    },
    {
        {
            0xA28FA772F79E7B25ULL, 0x96455C81059EC0D1ULL, 0xAE091655A21C96CFULL, 0xA7792B968A908F34ULL, 
            0x573B0FADCF399B21ULL, 0x0A8603DB52526E41ULL, 0x22D9DAA57C85DB19ULL, 0x61179194D0DCEBE4ULL, 
            0x2F26987BDEAEFBB1ULL, 0xC7292F9D1BE16141ULL, 0x19411EFE3DD57BFBULL, 0x97B83175E350B162ULL, 
            0xA7BDC58EADD99C1EULL, 0xC807B4427B31CE97ULL, 0x28FC586073182B09ULL, 0xE24B227D592D5451ULL, 
            0xDC2B8C6FDD67A9C6ULL, 0x18ECB27F3A9ADB11ULL, 0xA31A0B1202BD7FE6ULL, 0xD5F2FA14CDB318E7ULL, 
            0x5AABCB727B3FCDD2ULL, 0x14BC6D7791A1AA97ULL, 0xE3E035198919D2ACULL, 0x8FD834A8D4370841ULL, 
            0x6B8BD5FC5C6D365DULL, 0xCAB01E74E34792A1ULL, 0x9E4BF8C7E25EFBFDULL, 0x02DCF32BD97007DDULL, 
            0x0B336260ECE8070BULL, 0x31B0CD67E425A09CULL, 0xF417D2EAAE9B5F5AULL, 0x29BB9F95FB03306FULL
        },
        {
            0xF968076C7B4EC0DCULL, 0x0AEE6EAC8689AEF9ULL, 0xB192371724EEF912ULL, 0x5BAE7D0EDE52D96FULL, 
            0xC27D4D8C016776DEULL, 0x14635BA3066ADE7AULL, 0x29C75A78BE868D87ULL, 0x297F6BEF44FE4568ULL, 
            0xB1B73660A7EB77DDULL, 0x4A768074C71D2853ULL, 0xCA83A2147740B793ULL, 0xCAE6D8AB5BDA383BULL, 
            0xDD9710E1355B51E6ULL, 0xF6EEEDFA98473C0DULL, 0x7867174C0A45ADD4ULL, 0x7DE92E06F390CB88ULL, 
            0xDA2C73668A7AF3FAULL, 0x4D5DF8FA321BA996ULL, 0xF592C9A784261E12ULL, 0xB58720D422E3E1F2ULL, 
            0x7877B94BD7D0F94CULL, 0xF0EF0298EC97EDFCULL, 0xA0CC29CAD97B0265ULL, 0xA414AB5B00B09A56ULL, 
            0xEE40B041BEB71545ULL, 0xDE1008405352ADFAULL, 0x46A33D7A6B9211D3ULL, 0x2183BF541A572C5AULL, 
            0xB71F265204455D23ULL, 0x18E1F98D7F0A862AULL, 0xBFE377C8E330308FULL, 0x6961412FB91A0304ULL
        },
        {
            0x9AB503F9D30CF26DULL, 0x2215ACE74B09C32FULL, 0x4B79901DC4520DF3ULL, 0x2C311318B356439DULL, 
            0x47A169224B7B4706ULL, 0x49820C395449BC38ULL, 0x71480C0D282C2F52ULL, 0x4AE68CAB418C243DULL, 
            0x0B7E5CF0EEA3FE8FULL, 0xD1912F8B46F65C8EULL, 0x3DBAD3251326B08BULL, 0x825C0342EB4D464FULL, 
            0x204BDFEAD5CB023EULL, 0xCBC0B6A4EDCEE4BDULL, 0xD5161419196F7288ULL, 0x56BBB805F7264014ULL, 
            0x8E8A7E8DD9045FAAULL, 0xE59D3E79C7037AFEULL, 0x8419E0CF2B9297A1ULL, 0x75873E11500AA61DULL, 
            0x927F81B8B171CDACULL, 0x8DAEE12C86B225D1ULL, 0x4E7589CCD064B016ULL, 0xB7B24D2632DC7E9CULL, 
            0xEE72D6BCB02A86E2ULL, 0xFEE3CDE739C74303ULL, 0x09187778D3B4614EULL, 0x6A0D913E501CF9EDULL, 
            0xAD5BE6A810DD02DAULL, 0xFBF46240E32C4FBAULL, 0x28BAA15EFF97FBA5ULL, 0xC26FEB93E35C1513ULL
        },
        {
            0xCA87120049498542ULL, 0x292C69B9017F1890ULL, 0x1B2A487A09DF3B8DULL, 0xC68AD96B5D5A47BDULL, 
            0xCD45FF5C5C550B4BULL, 0x43AFB40FCBBD15A6ULL, 0xBF20A833F2D52D49ULL, 0x0FAEF25FDAA32EF4ULL, 
            0x801DD4010F5D92BDULL, 0x58DC8A53C39D1A8FULL, 0x300237D4FA1180BBULL, 0x96BBDF6FC4A27D11ULL, 
            0xBF439A61307D6665ULL, 0xE47EDF2F1EB90851ULL, 0x56C695E984951BCDULL, 0x07D1DAB781AF5865ULL, 
            0xCC018E7FC98B62EBULL, 0x06683E9AF506C309ULL, 0x6622B98B6FCBBEA3ULL, 0x3691CDCEA5FC6505ULL, 
            0xB62D3A4A845FB361ULL, 0x2DFDB465D3283241ULL, 0x76D5B9E0422CA9EBULL, 0x6169CB194458723CULL, 
            0x9090060D10ADAE34ULL, 0x6A032A516E9DD6E9ULL, 0x0123E6AB2681EF0CULL, 0x4E9B5C6B5B96FB1BULL, 
            0xBA0E1662BBD55A6EULL, 0x08DD59FBF41D8EECULL, 0x96ECD7E0BBBDC04CULL, 0x5771E3EABFAE379EULL
        },
        {
            0x0DF517B2EBFB74DCULL, 0x099918DD8D4304B1ULL, 0x3B9D70CBC3B02723ULL, 0x4C90EE3840C78C23ULL, 
            0xF3527F7C7CD86EAEULL, 0xB74BF94EEC422824ULL, 0x24F050021475B5FFULL, 0x57682D67D1D243EBULL, 
            0x44874481EC16B0F0ULL, 0xFE57F6AD5F917054ULL, 0xB2E3DD28DB821FA8ULL, 0x9535F0E7C814DF72ULL, 
            0x6307D8E030FBADB4ULL, 0x6B4971C7216D08A6ULL, 0xE6D351A2CB5A3A32ULL, 0xD29780095348B9E0ULL, 
            0x02729CE98DA29881ULL, 0x4582530108BA08DDULL, 0x8BD4C2AA7CCF7B40ULL, 0xD13C97B7016FFBF2ULL, 
            0x59681A5789E0BAE9ULL, 0xA207A3D49C145E15ULL, 0xFA5642AFA9954CE0ULL, 0xF40422845EAF1CA3ULL, 
            0x0255EA252B172189ULL, 0x6CB6ACAAE3CE1B02ULL, 0x6AF64F7576D6ED80ULL, 0x59AFE207CE739074ULL, 
            0x97ECC2EB5F3C4DA3ULL, 0x09D3920DC734801DULL, 0xF78205FF93684EE1ULL, 0x6969C40DF4882D9BULL
        },
        {
            0xF7A26F8CC48B20C0ULL, 0xE23BD93FD0D1F541ULL, 0x4792758E4DDCA6F8ULL, 0xB7E5DC403B7E527BULL, 
            0x8F8D3C59A9F1F496ULL, 0x10E2AAB2886B627AULL, 0xD1DE2E66BBBD3769ULL, 0xD7F3302118FD12F7ULL, 
            0x5C99BE03D7AD5E0AULL, 0xF30910E1D1F98F90ULL, 0xC0882A1A3FAE8DF1ULL, 0xA115D7A1AE7109A7ULL, 
            0x5833442074D6945CULL, 0xCE001F631AC98501ULL, 0xD08F7A67592FECECULL, 0x041050C8199887A8ULL, 
            0xEE2C869FB4DBDADCULL, 0x388B08F2171A0FD6ULL, 0xEA2A43F700458685ULL, 0xBDCCD0C4B9C4B0EFULL, 
            0x51B47570F8A9177DULL, 0xC04AD4A91B2BA229ULL, 0xFC3C3FF35CA26987ULL, 0x854034445B67C835ULL, 
            0xAD6DAF8D1171F51BULL, 0x98222FD745DFA2CCULL, 0xC478124B996EE300ULL, 0x5EEB5639C6602B08ULL, 
            0x9CBEFA71CFB3ECF1ULL, 0x8129962FC2852494ULL, 0x86BB90A70C084A24ULL, 0x3A7B6B273BE3D958ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseBConstants = {
    0x67F9E7156F03D71DULL,
    0x1701CEB87427C5FDULL,
    0xC3DB19E19A2FA8A2ULL,
    0x67F9E7156F03D71DULL,
    0x1701CEB87427C5FDULL,
    0xC3DB19E19A2FA8A2ULL,
    0xCD27A0DE913D7157ULL,
    0x5F985D6CC4CED41EULL,
    0x8D,
    0x41,
    0x24,
    0x4C,
    0x48,
    0x10,
    0x50,
    0xEC
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseCSalts = {
    {
        {
            0xB78E52E5E5216188ULL, 0x34C4B25F3D06D127ULL, 0x156B5C8765983D04ULL, 0x65BE534F5F1B5FDDULL, 
            0x3CDEA1609C20C975ULL, 0x0D755D7318B04595ULL, 0x1A3FD9B88DB750FBULL, 0x7574E4A3EBBD43C4ULL, 
            0x3BDBA87C8AEB6CA8ULL, 0xBE5CC1E52E633C3EULL, 0xCDD6DBC708F82D8FULL, 0x839B6DAE03802946ULL, 
            0xC536F6AFE7A43E36ULL, 0xE59B62D9C822B01FULL, 0x6BA8E14BC7A03197ULL, 0xAB98BC21D1A74B8CULL, 
            0x4F1749827B93E3EEULL, 0x801A7DB52013F0F6ULL, 0xABEA08265A55CBF7ULL, 0x54A3935239716C09ULL, 
            0x22038F7A6707F129ULL, 0x57B5E5C763AFBC76ULL, 0x0A03164D538AF590ULL, 0x9189666EC61657B8ULL, 
            0xAD5DB5449D9AA7F3ULL, 0xC499A06562FD7E45ULL, 0x8FF0DAA222E99A2FULL, 0xC28935B8DF4BC427ULL, 
            0x8B7A6F558B8FF49EULL, 0x698A10ADC6521499ULL, 0x599C906CCC4AE90BULL, 0xB595532912237DB8ULL
        },
        {
            0xAACD0D80A21EC56EULL, 0xC5E3760596D74E7EULL, 0xCFFAB9236893BFB0ULL, 0xE15ADB7D9EC5C5C5ULL, 
            0x124A11A433C127BCULL, 0x8699FA459A8A0980ULL, 0x2DD265F045F49DBFULL, 0x15ACB1C176D6AB4BULL, 
            0x94103A1D68410DBFULL, 0xB0F59430B2E38315ULL, 0x09F306210570B722ULL, 0xD2AF60E8E337BDD0ULL, 
            0xFCCD1532024DDFF7ULL, 0x9287498C00AAD698ULL, 0x4EBC75B65620D8D6ULL, 0x8FC52FD476F0C902ULL, 
            0x47D06B6F7648C102ULL, 0x41C456E6498140BDULL, 0xFA118125226A6145ULL, 0x2CAA137E7449E15DULL, 
            0x22D1124940EBEA1AULL, 0xF6968A6D37EA0439ULL, 0x9F3CD336039BBA66ULL, 0xC25035B2464BEC9DULL, 
            0xA472B8DC71D36314ULL, 0xF2268C953C20C8F0ULL, 0x266B8803D51D3758ULL, 0x31FEADF7423A7CBEULL, 
            0x98F3E6A0E71DCE76ULL, 0xC084A2F875A13BA5ULL, 0x1A916E28D7D95A35ULL, 0x4DBAB7599755334DULL
        },
        {
            0x80BC0047DC8F96DFULL, 0x2D828F759730373AULL, 0x72C204661CB3AE76ULL, 0x869B010E612F70BEULL, 
            0x4715A83CF25DEA2FULL, 0xCF5FAA020C4D71D6ULL, 0x49AE7BA82EA4C7A3ULL, 0x42BFEB725CDDC635ULL, 
            0xDA5C435682D94D4AULL, 0xDF1CC0B75A26FA5FULL, 0xA39248660DEC18DDULL, 0x9435120EE60D8027ULL, 
            0xF768962C3DAB278DULL, 0x37824C087DF7FA83ULL, 0x8AE0690468915B1DULL, 0x8691AE7E3C6853BAULL, 
            0xB131FA15F93C5CDFULL, 0xAC8CF15CE53DC7BBULL, 0xC0B7D77519EE2EF8ULL, 0x5996FE7D8D78FC2EULL, 
            0x2CC6925CB96953CEULL, 0x2ACAF2BD70DA4E2FULL, 0xF425146FBFD01E2CULL, 0x4FA9CA3D0092E7C9ULL, 
            0x6F46AF0363D82E7FULL, 0xEABBE3906C40C5F9ULL, 0x8230E0FA2B534F9CULL, 0xA203A713B77693F5ULL, 
            0x27B4F5F7A775B05BULL, 0x51A9A67346D3E49FULL, 0x003B874E4BF82A49ULL, 0x4F1B15958371D131ULL
        },
        {
            0x0736893BE51FB971ULL, 0x3C8F8A049FE32E0DULL, 0xB8AAE2910194B100ULL, 0x1EE24342612D85EBULL, 
            0xC964483D67E96ED4ULL, 0x67F9B6B49F11E18FULL, 0xFDE3454BC1AED64DULL, 0x5A5E497FEE874EFFULL, 
            0x82D1F8B2764A1720ULL, 0xCC47EF5510B294ADULL, 0xB38F7763A77D9A62ULL, 0x3CE270E64A28C985ULL, 
            0x784BFAE96C08C7EBULL, 0x20D3CCD3C7684370ULL, 0x00E4377ECA4B634FULL, 0x69E69B5080AE65BBULL, 
            0x6BED3B3EB6187563ULL, 0x89DD25C385F87D6BULL, 0xF4E89406F8C38109ULL, 0x7525B0DD8B859F55ULL, 
            0x3C7D42F7686383EDULL, 0x6D9E4A660EE1F463ULL, 0x506F8F476A9EF6CFULL, 0xF8EE963B353C41C3ULL, 
            0x4BE31C100AFB86E2ULL, 0x75184CEB9D74B88BULL, 0x7EC8F26E0879558CULL, 0x77D77D796D931540ULL, 
            0x351DC3F8A08F0E4BULL, 0xD1C6AF16D7F48A39ULL, 0xAA883AFD93AABDAFULL, 0xB16D95E4D8FAAF88ULL
        },
        {
            0x0FCE9E627BE066EBULL, 0xAC66200B591756CAULL, 0x9CA149E1C4A351C0ULL, 0x5E547CDC819B0DEFULL, 
            0xE8D00FADA5697BDFULL, 0x614978E03A23E9C9ULL, 0x8997449E9A49D8CCULL, 0x2BFF160D85F1DE22ULL, 
            0x67F91B902145A46BULL, 0x9F2422AFDBA27B84ULL, 0x303AA2A89D18FAC8ULL, 0xDBF7CEA4D74BEF0FULL, 
            0x1C2AD0A3A597FBABULL, 0xDC663B957EFF859BULL, 0x85D027661E052FA9ULL, 0xDEDEB92DD5A3FB1DULL, 
            0x81612C450EA500A0ULL, 0xE1F9534D40B6819FULL, 0xA134471E7E975E71ULL, 0x87B69892B4F44275ULL, 
            0x745BE5D13EF4D6B3ULL, 0x082E6F0F774EFF97ULL, 0x425D967DBA350678ULL, 0xFCE829C0B4D6C42BULL, 
            0x7B67E1FC8B138465ULL, 0x2185A5DC1DA558CAULL, 0x1561E4C1F41273CDULL, 0x8A62BF59DAE0B6BCULL, 
            0x28C6B32871B0C418ULL, 0x9152D44D781DCC31ULL, 0x15E2DD9A3D75E61DULL, 0x2910D3F88A252CE7ULL
        },
        {
            0x5A00DB45C0D9F91AULL, 0xCB410901B6E503A5ULL, 0x06D20D7749AD495AULL, 0xD0F4669C8D255975ULL, 
            0x7DEE23CCDBD1432FULL, 0xE94E091F5499A2EDULL, 0xBC8C3E0790C9E79DULL, 0xD83C2786B1B404E6ULL, 
            0xEBF84FA886E2F9B3ULL, 0x140976F502B97FBAULL, 0x5C3759D5480F31B1ULL, 0xFC85A0A43AC60FB4ULL, 
            0xB69C906B3335169FULL, 0x39BD1401142C9F86ULL, 0x70EFEF1F0F46F568ULL, 0x4E5526D71D1AED2FULL, 
            0x9DD0449C942FDD9AULL, 0xF21EDD725D8DE15DULL, 0x1B98C54A03EF39D2ULL, 0x50462E0F6DCC4ADEULL, 
            0x18BCFE45D2905A93ULL, 0x1E45CEBBFB422B5AULL, 0x5638EE0AF9E6F40EULL, 0xB0F76A6A7FF6DC42ULL, 
            0x3B02B418098C0CCCULL, 0x195037841E243A60ULL, 0x19F1EF77EE2656E9ULL, 0xEB806498475D5EA9ULL, 
            0xFD908BD386FAE465ULL, 0x179512AEE5745D6BULL, 0x655E37D6C273D43EULL, 0xA4B20B0FD312E447ULL
        }
    },
    {
        {
            0x247EF82725360208ULL, 0xAD310D45D0FFF1EEULL, 0x0A0896DEACB04E32ULL, 0xF14733CB8051E094ULL, 
            0x6E0CEB8DD9BEB233ULL, 0x6FF152DD411E1F04ULL, 0xBC6583D394D02921ULL, 0xECC7FD9F118EB5DAULL, 
            0xE963520B373A4E38ULL, 0x8902E5B390589B6EULL, 0x4EDE0AE4DF835945ULL, 0x8E36D9EA60FE99E8ULL, 
            0xAA92CE0CE7E9F8C7ULL, 0x610EB876990748D8ULL, 0xC29557DA8C6BA365ULL, 0x36109BA86E9736B0ULL, 
            0xB08AC962ECE90819ULL, 0x94E5653E45905118ULL, 0x090EA78A807A9736ULL, 0x95E9C20E3759E76DULL, 
            0x256CCE6B32D0BA1BULL, 0x49823DF1DA5A87C5ULL, 0xE7D3CC97A0CB5AF0ULL, 0xB94A88CF8919FAA8ULL, 
            0xAEE992DBD00F04D5ULL, 0x5ECB4D62280D981FULL, 0xB583D270B584514AULL, 0xD07F690D1307E0CCULL, 
            0x8E55DB33D5E64A8AULL, 0x80A200755690E994ULL, 0x9B0AFEFE291C9BC3ULL, 0xB53F5C7CBBB03658ULL
        },
        {
            0x1FF9207A69ACF78BULL, 0x8E62FA0D88CFA671ULL, 0xA8E89BD45564C3FAULL, 0x984C9831B429D519ULL, 
            0x9A723EF4443976FAULL, 0x2118DA5F72F793FDULL, 0x48BC5C947EFC6B71ULL, 0x565B1298AC66A2B2ULL, 
            0x2F598F4F7E1EA296ULL, 0x577AA74D0A416F65ULL, 0x03A77B62057CAFF0ULL, 0x67D15E0AFAD1E86FULL, 
            0x69280439F72BB85BULL, 0x59CC0D486343E8DFULL, 0x0D6ADE70387ABD10ULL, 0x18187C37D148351DULL, 
            0xF21F4042334100E5ULL, 0x8F5AA2E6C14F6E6BULL, 0x192D46743022EEF4ULL, 0xEF4F77C63E34B87AULL, 
            0x29438ED96B607416ULL, 0xAA3B4C3CC25E6368ULL, 0x876FF69F934D8911ULL, 0x7966CD1A5C5711B3ULL, 
            0xE2599B48FCA86D14ULL, 0x1D2A71553E04885FULL, 0x9711C55DF8B104DAULL, 0x9D9D5598B08E7855ULL, 
            0xC71FF1B55C8AA1D0ULL, 0x1CEC25D3A8A0D674ULL, 0x66957EF5E9B98F6FULL, 0xA88C01E5C44E0AC6ULL
        },
        {
            0xB95D4446430DA36DULL, 0x0B09E7E12852F2B3ULL, 0x5E57DE840AA1D14DULL, 0x41004BB8E9FB7A51ULL, 
            0x934354F63F79E379ULL, 0x18A44C5B5C562AA6ULL, 0x77FA128D1BE59637ULL, 0x8008952EB63F1483ULL, 
            0xC90DF26E28174715ULL, 0x73C366167C9A41E5ULL, 0x89F21CC92567EE1AULL, 0x0714980601B12A12ULL, 
            0x518C906D2615D018ULL, 0x52FE6B2D6552D272ULL, 0x90960CB71425C3EEULL, 0x147B21170910585AULL, 
            0x0CD520F10BDE4CEAULL, 0xB60CEE1726869003ULL, 0x218761059B719212ULL, 0x0C37D598D229D7E1ULL, 
            0xE5BF08B185A5E62EULL, 0xC8C4026E1961D4B2ULL, 0x26DDE15E49DC83ACULL, 0x8F3849EE8B4ADB12ULL, 
            0x435DDCDDB510FB0DULL, 0x331826B3937282B6ULL, 0x94CAD2CC5B8DBAE9ULL, 0xCF45FA0692444AC3ULL, 
            0xF0045A8CF7397846ULL, 0x25E2E4CA19EA63C2ULL, 0xF97AE510673317FAULL, 0xAB41320D74F80E87ULL
        },
        {
            0x1911402B428F750EULL, 0x7AA1DE64162838F7ULL, 0x6C37E394C15FA0B4ULL, 0xCD137660550449CEULL, 
            0x11602ACDF6A4115EULL, 0x664FB5A23E17262BULL, 0xEB91CBE34B316630ULL, 0xF3F236FCD113A2DFULL, 
            0x2C7A285A8EF99D24ULL, 0x5E0CB0E54D8878F4ULL, 0xE280703C0FDC9993ULL, 0x7EA5A4EE4832187EULL, 
            0x81EBEBDDC2EBFE1DULL, 0x99633663831CF8EAULL, 0x0A7BD475EB8655B3ULL, 0x0E5C153344403B65ULL, 
            0x820B40DC7CD7B215ULL, 0xF9F8306D396F5090ULL, 0x7BCE585577697AA4ULL, 0x082BD9BE6904F41CULL, 
            0xE207C2AD81227982ULL, 0x6675BBC39E775077ULL, 0x966C506E53E0CCDCULL, 0x3C66C5CBB1E4D49CULL, 
            0xDCBB6A7AA2D3B859ULL, 0xA239ABDA966F7CEBULL, 0x21A4D8D79329E84AULL, 0x505A262A0AC8AD1DULL, 
            0xABCC0BDC412CA77EULL, 0xAEE52255A13CC69AULL, 0x4F1633288B49D72FULL, 0x3C0ABF6CA59D994DULL
        },
        {
            0x7C5A9F1E34CDDD0AULL, 0x04C30237894841C6ULL, 0xB51D41C30A2BD440ULL, 0xB6F47A30ED53B447ULL, 
            0xC151443BD95199EAULL, 0xB715A4F2E67FD930ULL, 0xD455FE9EF3BFFCACULL, 0xE13B575545707060ULL, 
            0x5CB766C9B45D9BF9ULL, 0xBE520DF2B2C5AE85ULL, 0xD8AAF14519132358ULL, 0xE913613FD0F55E55ULL, 
            0x7798F37E052CF72DULL, 0xE688ABD6D59034C6ULL, 0xB4DBC5C3883CDC5BULL, 0x91E50ED8451BE7EBULL, 
            0xC250F71B1C320102ULL, 0x92E5CA1FF35CED20ULL, 0xB4684B283CC39D7BULL, 0xA76D7B6952B2E5DCULL, 
            0x46929FC9B9D837AAULL, 0x70BC81AB6EDD2E00ULL, 0xCAB86B9609BA524DULL, 0x6673CA4DC6347052ULL, 
            0x8D596F02EA85A136ULL, 0x21ED93CC8B8BFA5EULL, 0xB7080DA1BC4EBF1DULL, 0xDE38127E8438B34AULL, 
            0x7C1E883E1CD189C7ULL, 0xEC29C81FC39F1824ULL, 0x64D0E6DACE945084ULL, 0x179874C7179D9D9EULL
        },
        {
            0xF5C890E24E679A8FULL, 0x048886FE1C45CA87ULL, 0x8FFD67B4913907D5ULL, 0xAEF6623986CE0297ULL, 
            0x86345E0877394092ULL, 0xC0AAAACDC691E931ULL, 0xBE4675A1E61FC079ULL, 0x6B0264A63A6D53E0ULL, 
            0xD266726EE6B8E17CULL, 0xFCB68E50F02719A3ULL, 0xB6562B4A80BCF04EULL, 0xD0779AF01E907CB6ULL, 
            0x7C1F372CB92E46DEULL, 0xE853936325ABCFC2ULL, 0x5F5F0EC58FE74E90ULL, 0x79B8E02111042F54ULL, 
            0x816A68281A43AAAAULL, 0x00989FD42271D7F1ULL, 0x091A196274F3626CULL, 0x8C003D0C49B1941BULL, 
            0xC988AABE2109A3E0ULL, 0xD8E58792B0295006ULL, 0xA5112358E7B3F910ULL, 0xA20E87C8A2719BDFULL, 
            0x7050D76113F5E0E6ULL, 0x24290AE3DBB51C21ULL, 0xE59206F36497863CULL, 0x20EA99B497AD86CBULL, 
            0xF308D9ADCC0AEFA7ULL, 0x9B557DEAA677C493ULL, 0x361491907710028BULL, 0xDCE74AAA570DCA06ULL
        }
    },
    {
        {
            0x5CF501E79094FF5DULL, 0xF0159F72D119D40BULL, 0x6F61FE2D1CD529DAULL, 0xCA11D60DF24111BFULL, 
            0x9E4AD075C97BCCA7ULL, 0xE141F998A47B9419ULL, 0x2D6C19A92065FB3CULL, 0x1AA37945D8D7D6FCULL, 
            0x4334DE257C695A5CULL, 0xE9EDE8E52875AE88ULL, 0x6853D983C01676B1ULL, 0xBB0A2B0C57379265ULL, 
            0x909546DC815F9073ULL, 0x92522A743BE05F28ULL, 0x316CA2F3A195C6DEULL, 0x7FB8AA1C894C13D8ULL, 
            0x09979BB5E8254174ULL, 0x3F7AA9BD5DC298F7ULL, 0xC9C31B0A93BEA6BCULL, 0xEA0DED7B76752720ULL, 
            0x205E52FAAD3D304DULL, 0xC75EB0B0F14232DEULL, 0x3E73D044CC518029ULL, 0x6A03BAB5A9324C81ULL, 
            0xFD9729AD860ADD72ULL, 0xE736E11069C3B544ULL, 0x729CED5FE6050E10ULL, 0x564CD5F8D8CEDF15ULL, 
            0x2A3181026FCC3370ULL, 0xC68047069D77AC93ULL, 0x6A185EF05750E34CULL, 0x235CC86EA504FEBDULL
        },
        {
            0x4F8556415F1979E2ULL, 0x620A5B1832B5DBB7ULL, 0xDCC174D7C95E6C06ULL, 0x8CA021898A93F412ULL, 
            0x940FF865FCCB8E83ULL, 0xD9BB3B52FD0350A6ULL, 0x40EE8C195B10BFF0ULL, 0xA405242F3A4136CEULL, 
            0xA5B1FFB70EEDE263ULL, 0x58E5309DB4CD488BULL, 0xD0FCA2B3CC985FF3ULL, 0x99FAB80B1D7449E1ULL, 
            0x32291C39B41963A1ULL, 0xEE101A2419F03F28ULL, 0x1D7120F0CC5A2786ULL, 0x6EFDD95240EBB2A0ULL, 
            0x8E622E3F40719610ULL, 0xB86DD7A7AB67843FULL, 0x2643BB995331951EULL, 0xF4A83B25902E0E39ULL, 
            0x399C9B07F5A20203ULL, 0x05C0AE374052A9A1ULL, 0x35D7A13ACD220972ULL, 0x94130494FA92A697ULL, 
            0x7761F25BA5057AC3ULL, 0x48DAEECC2A2ADF41ULL, 0x4402D48E83B798F5ULL, 0x6D0F6C6A04797A7DULL, 
            0x82455D06C188D901ULL, 0x1E1E102874A51779ULL, 0xEE339D6F09AB3554ULL, 0x9C2EE0C7B880EB4DULL
        },
        {
            0xD7C1E3797AF00EC5ULL, 0xF2220BF0DF231DAAULL, 0x6A86B0472487ABC3ULL, 0xED054B60C76CC79BULL, 
            0xA3E97D611C6A9A76ULL, 0x1BC507386DE45C7CULL, 0xDEB0768AC6688B6FULL, 0x511BABDDADF3DE55ULL, 
            0x7F968834E350EF64ULL, 0x1057C7DE0AEB40A3ULL, 0xC54453D4A19A1E8EULL, 0xBF5A4FFF2FB46AA7ULL, 
            0x2ECC3D61A8866E39ULL, 0x6266956FCEFA7C40ULL, 0xC098499DEEF2E70DULL, 0x5A07843557139D8EULL, 
            0xBB5577C44EE1F5F3ULL, 0x8542BA74A2CBCFEEULL, 0x61B0A09676031B21ULL, 0x9373AAFDB2F1B367ULL, 
            0xADB3257C76E54E90ULL, 0x01FA16DF5E810322ULL, 0xCC9A87E380154C79ULL, 0x9CFF39398254D555ULL, 
            0xCA991894908B88F5ULL, 0x42BE87B4134D8BA9ULL, 0xE0916593130A9A31ULL, 0xF775C55278165135ULL, 
            0xF13B8E1CDD6BCF67ULL, 0x2913063FB676D929ULL, 0x46759B3413317030ULL, 0x5BF7CA41DB770147ULL
        },
        {
            0xE7EB93A50C49E2C8ULL, 0xE3BD79A85E005971ULL, 0x17DC4595F0E7A18CULL, 0xFAD7609BF2751749ULL, 
            0xC887EC8C24237319ULL, 0x00CDFEEC82DC66D5ULL, 0x40DAD1C8009053EDULL, 0xE3D62004BB2848AEULL, 
            0x24F788F3C01E8175ULL, 0x513615B561BBF5ECULL, 0x834EFAB11D2F5027ULL, 0xA695D1EEC7663B83ULL, 
            0x55F361A9B1098056ULL, 0x97A21FEDF4FA5206ULL, 0x0FCB1E6CCF378AA2ULL, 0xB1A1BCB8A3679F3EULL, 
            0x91056EDDA0C52622ULL, 0x23F7E14AE264614BULL, 0xA135DFB83840DFC0ULL, 0x5B4923998F5A6663ULL, 
            0x2C68A064E0CC4539ULL, 0xA4E1978797B2288AULL, 0xD5CB6F40925578F9ULL, 0x3568F3681041CB78ULL, 
            0xB932660FFAA047ADULL, 0xDF277424647E0DF7ULL, 0x07A20237B9F4A31BULL, 0xA764248893509D00ULL, 
            0x20C946C6E975D41EULL, 0x966CEAEA82C3B7FFULL, 0xB405F7E1BA60EC60ULL, 0x5FB50509AEE3DEB8ULL
        },
        {
            0x228826E6B76BEC7DULL, 0xF6570B0C94105523ULL, 0x5FC9E3439ACFD56CULL, 0xB3391A604E45FB91ULL, 
            0x6A9FEFDB9CBF6D4DULL, 0x56DD553A51596C66ULL, 0xFC629497838B5712ULL, 0xB6BAA2E1FBB24ACDULL, 
            0x3692C9817289B7CCULL, 0x647E224EA7361061ULL, 0x536EC036DF2CF2BBULL, 0xD9990F03B45E1ACEULL, 
            0x0FC2A4557EE7069BULL, 0x5100F7DD17FEC6D8ULL, 0xA58B5C1F8CADC9B3ULL, 0xB0AD6311B8E1ED40ULL, 
            0x629DE2957937572CULL, 0x4FBC3956F6286458ULL, 0xB9B30B4C7AC84222ULL, 0x2EBE577213A8CEAFULL, 
            0xCA367D829CBED6E3ULL, 0x7FDF0B5B201806F5ULL, 0x83730E56B64D6056ULL, 0x427778A9FA155669ULL, 
            0x9582791F61ABF09AULL, 0x7194349692928583ULL, 0x7C59B105C3C269E6ULL, 0xB7422318F897D310ULL, 
            0x62B483B254DA22DFULL, 0xAC587594C0DD3D2CULL, 0x5F1BBC87FEB9BDAEULL, 0x75CD138A12470160ULL
        },
        {
            0x7363A969F0BFBEADULL, 0x851D5E8D3433BE8FULL, 0xDFC8F806D8B3DD4CULL, 0x661B0855C461B59DULL, 
            0x79359388BF0BB7BCULL, 0x75A1EAAEA1BBA0DFULL, 0x298A7CAA560D1BB0ULL, 0x07024734C82180DFULL, 
            0x2F0654895ADCC4A5ULL, 0xA459D3E0A5E2C9DEULL, 0x011DFD4A1D8E8E95ULL, 0x4A45D5F6175D81DDULL, 
            0x1B91DF8133906F18ULL, 0xD850D09BDEE02830ULL, 0xD4251309A4A23AC2ULL, 0x2363477454CE5712ULL, 
            0x477B247FF36DE18FULL, 0x08F964CD613E5B99ULL, 0x7107880E9B8F4995ULL, 0x1D162D096B078D4BULL, 
            0x9ED6D2634FE00D75ULL, 0xC7A47427E373AAF0ULL, 0xF3FB74A0CE28CF11ULL, 0xCF66EE7C4B5C51F0ULL, 
            0x461A6347FA57E197ULL, 0xA280D59894889237ULL, 0x503A846B5FB0AA25ULL, 0xB041E53CB1E0EB09ULL, 
            0xF1E7ED2C8DCCA7FFULL, 0x51A69F4391E0EEFBULL, 0xACAEDC69CE2A21DFULL, 0x8D8C0281FCF03FCEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseCConstants = {
    0xE07DC69A1B91DC6EULL,
    0x0552EA7D89A23E97ULL,
    0xBF9907ECDA94430EULL,
    0xE07DC69A1B91DC6EULL,
    0x0552EA7D89A23E97ULL,
    0xBF9907ECDA94430EULL,
    0x6023307303B40B78ULL,
    0x2CCCE31B2364AC9AULL,
    0x21,
    0x7E,
    0x6E,
    0x1D,
    0x7D,
    0x34,
    0x24,
    0x1E
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseDSalts = {
    {
        {
            0x9889F0D90A5917BBULL, 0x27128128B986095CULL, 0xA6A0A1D0D12DFC5EULL, 0xCDB16C104F9BA8B7ULL, 
            0x1B9DDFC9FBB7152BULL, 0x15F5A03383A937AAULL, 0xEEABA42A6C95350FULL, 0xC68E7984C5B84BC7ULL, 
            0x04977EC634A6824AULL, 0x83CCE17D812B4B78ULL, 0x0630F140B58D8837ULL, 0x9FE50207837D3F52ULL, 
            0x247AA4DAA201D175ULL, 0x1CBF23E1A32EF2CCULL, 0xA80EA3D5F3082BFDULL, 0x084BEAD1C3E54D77ULL, 
            0x515CBBEA76A6CFF9ULL, 0xC09E95A344E32C5EULL, 0x889E47F9BB5D0D88ULL, 0x308FC07FC77E4C0FULL, 
            0x88255350D1162394ULL, 0x21B4FFD32B09BB33ULL, 0x46285627CBA5383FULL, 0x5003B9C3972B0CA3ULL, 
            0xA4FB5C0E211B8559ULL, 0x30E1989584218F41ULL, 0x0DCAE70AE842F8F6ULL, 0xAF8874A93F75B4F4ULL, 
            0x7749A2EF4B425E4CULL, 0x8202BC8AD686AF22ULL, 0x92992285B5B7F825ULL, 0xA50E8BEA398A23B2ULL
        },
        {
            0xE5F2ED823829B11EULL, 0x8BCFC7704EC2CD7AULL, 0x63D1C200C61B24B6ULL, 0x1720A997D0BEFD32ULL, 
            0x575153C4E1A903AAULL, 0xBB0F49487E06C038ULL, 0x0F89293BDAEC22D7ULL, 0x3B3802017EFCE6C2ULL, 
            0x2FA4E7316D02754CULL, 0xB4DBC898FE9852C1ULL, 0xB0D2969AECD62B9DULL, 0xCA916D9AA4FCC0B9ULL, 
            0x85028E92B6E55FF5ULL, 0x1E06E28F8D289049ULL, 0x789EB2DA36ADC525ULL, 0x0C2180BCAE9F01C5ULL, 
            0xAFF9F92B5A1C3A78ULL, 0x98F4F5E3D68B7F2DULL, 0xC210EA7A61A2E895ULL, 0x2100A38897C5A20FULL, 
            0xE168EC4D9B2475ECULL, 0x3C7BC81A0113113AULL, 0x820A08FF5084A48AULL, 0xFCCB59D2F841A571ULL, 
            0x791C22725F6D93D3ULL, 0x9C0EA0C45C7240E2ULL, 0xB9B2AB19B2CFA7CBULL, 0xA93092501DF68B66ULL, 
            0x96245ABF49509B6DULL, 0xA403198291673899ULL, 0x1C88DE173BEBE472ULL, 0xA273AF1446F04D9EULL
        },
        {
            0x2406D54CE8DB85F3ULL, 0x095771610437A364ULL, 0xECF707FFDB249EC1ULL, 0x39477D0288A67107ULL, 
            0xA166E99B74DA2B74ULL, 0x9A38808F65079467ULL, 0x079FE880334368E8ULL, 0x118456266BEC51DFULL, 
            0x49A5CD95B5AB3862ULL, 0xE9C37BCA470D053FULL, 0xBC14228322C6A8C6ULL, 0x8D08856247789924ULL, 
            0xD8B954AECF2D5F2AULL, 0x002410FCC4C6294AULL, 0x294E9174B2369612ULL, 0x380A7C8E33D0E0F3ULL, 
            0x3C1EC7B18EFBFA41ULL, 0xB7619FB1B9A058FBULL, 0x807025CF766A830EULL, 0x7DB4BC8140BD890DULL, 
            0x2EA5FD761BB5091EULL, 0xCEC6B9FA66A6EC92ULL, 0xB91F3E6C156F0F59ULL, 0x0D63467609E3F282ULL, 
            0x40DE3806388364DEULL, 0x65A364939AC7A6F6ULL, 0x4072E5FFEDEB5975ULL, 0xBBB7CD2717FFBB4FULL, 
            0x5970CFDC62C0C17EULL, 0x1CF4F77046C9DAACULL, 0xECDFDCCE3C0074E0ULL, 0x82124EBE5EB405F8ULL
        },
        {
            0x78CBF6DFABC6FFB1ULL, 0xCDD79165294402F2ULL, 0x22D369A3DBE6E97EULL, 0x2674BFB5BDD4BAB5ULL, 
            0x5DDA643FE52AD19BULL, 0xFFFB9297EB21A867ULL, 0xFD00D396EF59ED89ULL, 0xA75884FFA949101EULL, 
            0x4D833F89AA1E0E29ULL, 0x94584AD42D7F4155ULL, 0x4326C31FBFBB3016ULL, 0x0EC60778C0ADD565ULL, 
            0x3B623169D8F15C03ULL, 0xF41BE43494C52A93ULL, 0x43A3711BAAB2B4B7ULL, 0x8BFE6F8863AA895DULL, 
            0x598EB44AC797B870ULL, 0x51372C9E95B50D37ULL, 0xD076335EB030631FULL, 0x4543E3AB2211AE00ULL, 
            0xD6DFFD629A90EED9ULL, 0xA18A2CCFB27907BBULL, 0xCF85107D1EC960FAULL, 0x0C0CA1BA78928AF8ULL, 
            0x19E7E64DE0991DE4ULL, 0xA7873EF355758977ULL, 0x49B7D9483E7875F1ULL, 0x4EDBC1992E826099ULL, 
            0x304AEB52A774955AULL, 0xC97D79DEC0762284ULL, 0x1BF73F722BC5C0E4ULL, 0x34E18F2767421046ULL
        },
        {
            0x20B28CBF844C2EAFULL, 0xFDBE9F890521059CULL, 0x248B07751337CC60ULL, 0x732A75C2E64BB65CULL, 
            0xDA86B33B8E0594C6ULL, 0x5C665F4FD6DD7E00ULL, 0xF064F5C31A124FD4ULL, 0x4B91E876189C4892ULL, 
            0x3AE5833CA38A9B22ULL, 0xA51371477233721EULL, 0x5C625C6E567CDC73ULL, 0x7498B60A754474CFULL, 
            0xF73E5D22B3F185FDULL, 0x30F9185BDAB056DAULL, 0xE16447A0AE7A01CAULL, 0xBA7E805D3FD3C438ULL, 
            0x31C75289826B5237ULL, 0xF1EDE4A912DEDE31ULL, 0xF202A6D9F20996C0ULL, 0x7D1803AC39D18E9AULL, 
            0x44D0C3CDE1A43E94ULL, 0xA59E70CED796F40DULL, 0x37492F99F785051AULL, 0xA1B89F3ABCA27EE3ULL, 
            0xC6AA2308CE67F8ABULL, 0x3D08C7AC858721CFULL, 0x77FCCE2A72EE6CEFULL, 0x6519E807C51A4175ULL, 
            0xFEA44263AB5A3FC5ULL, 0xD6C59F2C24275F29ULL, 0xDE7EE1985749F8AAULL, 0x90A8C68BC6A59C0CULL
        },
        {
            0xF1873EBA6DBD6072ULL, 0x7C766AB9806D6388ULL, 0x9BE27CE8B5674251ULL, 0xB95881B1D843E385ULL, 
            0xA41BAB3847ED86DEULL, 0xB31B35F9276940CDULL, 0x4D47E0679D8868CAULL, 0x8626488987DF9E3BULL, 
            0x89DC0262131EC2CEULL, 0x9883E7DD34AE34D2ULL, 0x7D19C3FEE58B59F1ULL, 0xD8927F3F83AEABC2ULL, 
            0xD5582D5903C59209ULL, 0x4385F8BBE6F07B2AULL, 0xBCB76D0BF37B3508ULL, 0xD0FCF1AF3709F757ULL, 
            0xC3DC25164201CDA3ULL, 0x7C24478567216DCAULL, 0x560090CBA588FDB7ULL, 0xDC26A5D22E268BBBULL, 
            0x8CF489EC3E74AFF3ULL, 0x4E5F9857FBE1A97EULL, 0x554DEAB795A01714ULL, 0x22B6A9247E74B744ULL, 
            0xEB9522C0BAC7CAD8ULL, 0x514B92D14122F9CAULL, 0x1BFEAEF5FA581703ULL, 0x1E8A453B0D367404ULL, 
            0xD54F865B8738E13DULL, 0x734E8A09F439680EULL, 0xDB47E622DDF296B3ULL, 0xCB57D7F25A6985E7ULL
        }
    },
    {
        {
            0x042D099C877D0F9BULL, 0x992DEAD640AD1E30ULL, 0x8F0677861938FD51ULL, 0x432B5B7722869679ULL, 
            0x48C810CCD0EB759FULL, 0x3FB62FE7F2371372ULL, 0xCA44602D8E8E6199ULL, 0x0DB0FACA59A6400DULL, 
            0xE7D0D3D2F2E25D39ULL, 0x185E782E10362436ULL, 0xFA05E14A3DDEBB8DULL, 0xF59C7ACAB0EAAD03ULL, 
            0x4FECA6FB4DF3B757ULL, 0x49248F109F7A536CULL, 0x5747482EECFC5E8BULL, 0x15948685F875F055ULL, 
            0x9F42341C1C7F7163ULL, 0x84C9C1A98781D3B9ULL, 0xC33D41CA4A012499ULL, 0x5A21AE4D25FC17C6ULL, 
            0x18B27D27A71B1D95ULL, 0x201225517C35CFD6ULL, 0xFCC43B69FFEB887CULL, 0xBB61E9D84835890EULL, 
            0x596649A918B105A5ULL, 0xD1C2648227072F23ULL, 0x161542996D67A691ULL, 0xFE50E68DE0C189CDULL, 
            0x9B7E29616E79449BULL, 0xAD2F1CCAE7DA2B61ULL, 0xABC5476922F43EA6ULL, 0x812C0FADBBBB651AULL
        },
        {
            0x3CFE3D579B36ACB5ULL, 0x11613328A9D7AC90ULL, 0x22679CAA400929D1ULL, 0xF627AF8B3E870BCFULL, 
            0xA85F31CFAB353D2EULL, 0x0651F2696100077CULL, 0x5C679BB81C37F229ULL, 0x369FE2282E43EC93ULL, 
            0x55B1D786FC8FCFB1ULL, 0x7DBDA322C30E87CBULL, 0xE0F0386E3AB0AD3AULL, 0x5F13177B012919C7ULL, 
            0x4600204F98174C53ULL, 0x4813E63BDDB1B4AFULL, 0x49BB73298148563AULL, 0x5517FEB80249773EULL, 
            0x218D02BEA9309688ULL, 0x73CDE5698A1A9E1CULL, 0xBBBD876F6604E5E6ULL, 0x55C9F67D951E64BAULL, 
            0xE8854DEEBD740954ULL, 0xFC8596935B5E66A7ULL, 0x6D431FFF26DC6E29ULL, 0xF8EEB830C83A9F63ULL, 
            0x44B5121C9D341CA9ULL, 0x0B806E1E115327C4ULL, 0xF33D7AC86923CF0FULL, 0x4CCC73F4701E8B9FULL, 
            0x4390DB466B4DED6EULL, 0x8D3A43AA59C2939FULL, 0xB814A3043D290592ULL, 0x39B54BF35D867215ULL
        },
        {
            0x318E78BB6B55D03DULL, 0x3CEA6E791769711BULL, 0x064C22E0773284DEULL, 0x8DEF538EC0A4243CULL, 
            0x67FEC230B7C8F697ULL, 0xA59E319695E3E974ULL, 0x13069D5DD6C3F529ULL, 0x64CF8CEAF1B59F91ULL, 
            0x0EC49D17BD73A9ABULL, 0xD71B1F1DF58EFD6DULL, 0xEB25598DD91C9293ULL, 0x249F573102825253ULL, 
            0x91175CDF14ADCFA3ULL, 0xB0E2FA6E3D644B62ULL, 0x9F1800D70244E647ULL, 0x68FE90313FB21180ULL, 
            0x0ED40E8777D0F1CCULL, 0x62694C605E57F2BDULL, 0x025EEF7FF18CC183ULL, 0xC49222701FDED0DBULL, 
            0x5EE9D33769EF62D5ULL, 0x9ED3D0EB00ACA85BULL, 0xFE14AA38833EECAEULL, 0x3DDE7FB9FC302BDFULL, 
            0xC7B8FE8D7E24BC0DULL, 0x2F9770E55B1F72C3ULL, 0xAAA9F9A911CAC71FULL, 0xD311F48ED221C095ULL, 
            0x564CD5727DE93FDCULL, 0x09592B130CA3862EULL, 0x9BB6AC75CCE7FB3EULL, 0x69A42357C7B80470ULL
        },
        {
            0x740C4E25CFE21F75ULL, 0x53A6BC5B7356C138ULL, 0x44288C2829882863ULL, 0xEF3DD81FD0C23C81ULL, 
            0x1CD8BF1ACE8D37F3ULL, 0x729E5AF13AC29E95ULL, 0x144C16BA3FDDE39CULL, 0x98C2058B1FA4B09BULL, 
            0xF97FF7C664F74E7CULL, 0xCB24FB2B53E13447ULL, 0x64265B7FC1459F7CULL, 0x419B191555C4D3CFULL, 
            0xBBBA6ECEE4ADED5EULL, 0xCDB53C3845B14D44ULL, 0x5262FAE3F805AF18ULL, 0x13933AE00BBEAE47ULL, 
            0xE414EA770CB14B05ULL, 0x0431608FFC58DF83ULL, 0xC3436F65C5F01CE1ULL, 0xC2BEB22E1A457B25ULL, 
            0x8ACC627586040470ULL, 0x17859024776E3359ULL, 0xEA1E227C221AD1F9ULL, 0xA11DC88FA1DB7B05ULL, 
            0x299D838C635DF386ULL, 0xBB8B4175E7CA9B2CULL, 0xEB966BA039034E20ULL, 0x3CD0C889ADCA8A9DULL, 
            0x5F1E2DEAFDB401BEULL, 0x0170E2A8E2C7DDD7ULL, 0x6E8F5C1AEFED3A72ULL, 0x18FAB267CEFCB5C7ULL
        },
        {
            0x74CBB9903BAE0763ULL, 0xF97CE705E1AE271EULL, 0x245DB97381622FA3ULL, 0x5C2EF7510BA23808ULL, 
            0x21A762DBF769E605ULL, 0x245CE0F13D007EE6ULL, 0xC5D3DDD4DE444D65ULL, 0x2EB3A315345718B6ULL, 
            0xD442F76F9C52A97BULL, 0x662B6006329ACB59ULL, 0xBF33B0586DB46828ULL, 0x1AE789AC8D15D411ULL, 
            0xD040404796A3248CULL, 0xD09FE3A21163E35AULL, 0x93A044D7D5876D04ULL, 0xB7140A57023A04CCULL, 
            0xB66F181231DAAAD2ULL, 0x176604936A2E819FULL, 0x24D3154C391E2E5DULL, 0xA0C6BEAFB02C62AEULL, 
            0x1F0A54526BED842DULL, 0xD955585CDA3CF1DAULL, 0x35022B58E2525583ULL, 0x3498A5822A92B875ULL, 
            0xE6D422A5422EEFADULL, 0x18C2CC51A2CC1B47ULL, 0xF7BEFC16EE98E47AULL, 0xF596E6F6E97CCDE0ULL, 
            0xFEA3002FC633A129ULL, 0x146C9E12C94F87B9ULL, 0x27C264C1204F895AULL, 0x910FC95DC5857A47ULL
        },
        {
            0x7807003EE4767B49ULL, 0xC7B9029D2F377149ULL, 0x4125638A25288E60ULL, 0x890087AB405B5B8EULL, 
            0xDD92DE4A4C08CF81ULL, 0xCE29E196CB31B5E1ULL, 0x094360593D79474FULL, 0x0F66AE4C83E1CF29ULL, 
            0x4BB0AA36AA834B5DULL, 0xC623EBA33E1B570FULL, 0x0B0C95C1C0AC6148ULL, 0x2A3DF66243818CA6ULL, 
            0xEBD4C04D4147AB2CULL, 0x1A19D4FFB33AF54DULL, 0xDCD5BB72D3C32821ULL, 0x2D73D241B45D8AFBULL, 
            0xF441F8BC59A6DF47ULL, 0xA61EEA6B8FD0E615ULL, 0x99EDF2D2CAD8BD2DULL, 0x6DBEB1BFEB33AB2FULL, 
            0x69740B7C30076AAEULL, 0x56AB092516B3D269ULL, 0x3D08581E431F3804ULL, 0x32ADCA770E7DE821ULL, 
            0x268AEFEA5FA5422DULL, 0xEDD27863755B5A96ULL, 0x6DC6A5473C223E1FULL, 0x6A5267255B6EDC2BULL, 
            0xDEBAC330A584B148ULL, 0x803EA98E31F18690ULL, 0x3433DD546F9EC57EULL, 0x36B13C4FFB5BFEC5ULL
        }
    },
    {
        {
            0x99B4D8229E154F2DULL, 0xE13A181DCB4E93BDULL, 0xB0E7813914C10DBAULL, 0x8CE9F09051B652E6ULL, 
            0x8B2610416B380904ULL, 0xC34346F004CEF717ULL, 0xC4697B1B8C5A72FCULL, 0x1662594AA116DC69ULL, 
            0x2250B50E61A161D0ULL, 0x91F808D56C59AD7AULL, 0x866260DB4E061A44ULL, 0x0A2B7F33C29EAAB4ULL, 
            0xB43C06601F70C88FULL, 0x19A4D41A639174F9ULL, 0xFB2DB4F9932BAC36ULL, 0x497DEB4599EAE803ULL, 
            0xFA4DDD8BDD8097C7ULL, 0x927737BE6496729BULL, 0x65A99C8FB059CCCAULL, 0xD3671EA706733AFAULL, 
            0xE7684EB7398A5B53ULL, 0x61844183B073628AULL, 0x4E23E3C2545B8663ULL, 0xA7ED7CA56ABBDD62ULL, 
            0x709992C2076B7CC8ULL, 0xD15173EC51338DAAULL, 0xC2B5686CE8DD0822ULL, 0x0F2AB23EE0AE09BCULL, 
            0x33DA1E0DA534CC54ULL, 0x3488911F163858BAULL, 0x831248BC299B2489ULL, 0x4D6150B2A8D5298BULL
        },
        {
            0x53491F3023243C1BULL, 0x7CB7FD93778896DDULL, 0xF05D7CB1070B5B8CULL, 0x65EB4195A1109FD3ULL, 
            0x97EEA53B00E7D8F5ULL, 0xDF20408FE666FDB3ULL, 0xE1B47DF35342266DULL, 0x29CA55B574902123ULL, 
            0x4244C9402A7E8A63ULL, 0xA1508190A719A4A3ULL, 0xFE561CFE9424A729ULL, 0x9081770D381A9DAAULL, 
            0xA6498E3E0BF72327ULL, 0x70BC7642D46FB6ACULL, 0xB8405DC430637162ULL, 0x4FE455AA0B07C3C1ULL, 
            0x539C9F4439225E1AULL, 0xC9C71B7F78DC1F7FULL, 0x31F1897AAEBFD85CULL, 0xEA016485BD5ED405ULL, 
            0x645C633F0CC1275EULL, 0x300B1D59A9FB0856ULL, 0x5C7A3071396DE5DBULL, 0x0B267E7470C3018AULL, 
            0xB3118E9591707D2CULL, 0xC69072D69DAC873BULL, 0x935232EF3A729F5CULL, 0x9DEA96CB096D26E3ULL, 
            0x52F4BA0DF7B2FB8EULL, 0xF679F3B354990688ULL, 0x76FF3E842A550A61ULL, 0x1F56895DC5951F35ULL
        },
        {
            0x0B255B3C8F1CCA25ULL, 0x75FCC142C61711CBULL, 0xD6796E71DDA8F146ULL, 0x724492A68BCE0652ULL, 
            0x9962B82195325216ULL, 0x8897B84A15394A4AULL, 0xA8D42A6ACFF829F1ULL, 0x199FCF066DB0923BULL, 
            0xE03CE5C5A28ED81BULL, 0x1E318F79A77F2564ULL, 0xF4AA7D3A7084FDD5ULL, 0xCEA13DDD6B42A09EULL, 
            0x9660BCE99F0ED0D0ULL, 0x4E2F2A1FC861270BULL, 0x579B089675CCC9D4ULL, 0xA120D8D9C8613F6EULL, 
            0x72C0D8A19D22E254ULL, 0xD86A2284E1512405ULL, 0xC15256E4797EE2A1ULL, 0x0770F3FE20E6E39EULL, 
            0xE42D1F1C23A01BFAULL, 0x0B4887DAB2C07007ULL, 0xEF504B8BF0017EC2ULL, 0x07364CA0AB763BDBULL, 
            0x5BBB5F6C52C699F7ULL, 0x05BBA266E438E392ULL, 0xB543ECEE59E94B6EULL, 0x22914623207EE2EEULL, 
            0xDD83976846C03534ULL, 0xAE34B3B65446387CULL, 0x69A627E35B21225CULL, 0xB118B7C6F5545796ULL
        },
        {
            0x3487E9DEE2FF057EULL, 0x6FAD6509CCB9B3A3ULL, 0x8148A037738042F1ULL, 0x42DC7EC2E40DAAB7ULL, 
            0x857F68E5DDE8E555ULL, 0x644F00A744D53CC4ULL, 0xAC47D80D4B3F04D0ULL, 0xE3BE38B2C6981C72ULL, 
            0x0AAA4A012E856C11ULL, 0xBB84930252853C8AULL, 0x1D0641B011E40B27ULL, 0xE423E47D275A8C5FULL, 
            0xFD1AFE56BC88B630ULL, 0xBE0C21972B33073CULL, 0xE797E18D117FC81CULL, 0xC9CC132A2DBB84BDULL, 
            0xF968A7B77056BFEFULL, 0x276211CD7411464AULL, 0x02D5F28FF33B4B64ULL, 0x6D7391D4C9CE3B1DULL, 
            0x310F67098403A7DAULL, 0xF407AD57A8B609F6ULL, 0x52941FA78664FED4ULL, 0x647B09E13D1B773AULL, 
            0x165F556DBF06BE62ULL, 0xC055F63BB7EE6DB3ULL, 0x37E7C74C5A073340ULL, 0xB636A166E218E44FULL, 
            0xEC2B65AE0B04F61CULL, 0x9C3C41E0B2701610ULL, 0x926062D04697122AULL, 0x742E274DA63D3BA9ULL
        },
        {
            0x0E153BFD690EF6CDULL, 0x64CC4FC7CC8C1B13ULL, 0x98A2FEE066104ECDULL, 0x474FF2C192D281D3ULL, 
            0x3E32CD43B46A8FE6ULL, 0x4542F392A2FD4EE2ULL, 0xB30D6C3ED0951A92ULL, 0x22D2EDF843EC06E4ULL, 
            0xD3325C25B856B279ULL, 0x4A07D9031B65D467ULL, 0x6CE2A75B2BD574B3ULL, 0xAD1E9AAE783C3AEBULL, 
            0x1624F48D8C0F22F3ULL, 0x4F733FAC099D4159ULL, 0x0E42177E7EC75D3CULL, 0x12985944CEA69C1BULL, 
            0x943F8E9B85ACD4B6ULL, 0x4AFDFA6860D3BA27ULL, 0xBE660DC98744CA56ULL, 0xA77E3AACBBB65AECULL, 
            0x35CC5B3294DE2452ULL, 0xEFD8653A10F1F43BULL, 0x538CE16DCAB7C7BBULL, 0xD0D146AE4DE6B0A4ULL, 
            0x17C2FC1A3B2348ADULL, 0x597B877B283CFD03ULL, 0x9EE9F4A865F7C934ULL, 0x933B1A1087BBE399ULL, 
            0x41BAE8C0828FB259ULL, 0x9826A4C494F4738AULL, 0x9E7DF82C99B7710FULL, 0xF682134C2B9E5BEDULL
        },
        {
            0xB048FF8D621B5E99ULL, 0x4DBFD87FD39E5CACULL, 0x5CAEAA900CF4CB68ULL, 0xE024A424D624A9C1ULL, 
            0x868E952E4B8C61F8ULL, 0x27F0BE29A306B06DULL, 0x95EEE723A5CEB7F4ULL, 0xD9E446359BC79CB2ULL, 
            0x1ED052819A1FB110ULL, 0xB675B326959F1867ULL, 0x9D1471282D4ABB57ULL, 0x5AA60049ABF4F9F9ULL, 
            0x48C81DFAF64D5AEFULL, 0x020FA8EE10290F80ULL, 0xB68E447D42A0184FULL, 0x0FF0EC39276BE011ULL, 
            0xF747365B43839954ULL, 0x7D9BAB77450596F4ULL, 0xCFD54EF6AD05687BULL, 0xE5936C4ACD623EE5ULL, 
            0x6D644045360AA7DDULL, 0x4B3BC770E0858707ULL, 0x669AD2F2BB6F09CFULL, 0xC5B91D0C4507FA66ULL, 
            0x99DEA96910225AD2ULL, 0xFB4964C71ADCC9E6ULL, 0x5F5137014B676FB6ULL, 0x36D9F7F4B4B3071FULL, 
            0xE6CD872D64C27D29ULL, 0xF69ECEF18FF32BC0ULL, 0xFCFBC238B4671998ULL, 0x70E79C80B47551B9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseDConstants = {
    0x511345A357A28B42ULL,
    0xC25F561973F614FEULL,
    0x927A7549D4C9CA52ULL,
    0x511345A357A28B42ULL,
    0xC25F561973F614FEULL,
    0x927A7549D4C9CA52ULL,
    0x9814945A0B9569D0ULL,
    0xE523E88E8A1E5042ULL,
    0x52,
    0x79,
    0x8F,
    0x10,
    0xD1,
    0xE3,
    0xD5,
    0x33
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseESalts = {
    {
        {
            0x030AFD4DF98BA7D3ULL, 0x10A0D050066B0C1EULL, 0x44C3D774D6063158ULL, 0x28CEFE8292DCDB6CULL, 
            0x3C31D24B3ABE6701ULL, 0x8AD72E7E154780FAULL, 0xB50FA03EF0BB17C7ULL, 0x0A9708014904B376ULL, 
            0xFAE3748C240B1708ULL, 0xF32552BF09BB6880ULL, 0xD02AA9F9F2E8FF77ULL, 0x676483FF98DA6A8AULL, 
            0x780DEDBFEC99669BULL, 0xA684691F19BE1ECAULL, 0xA4EE7CA3B2F68075ULL, 0x64133548A826C278ULL, 
            0x03741FBF5C78BEBEULL, 0xC814B978A0FE3F2CULL, 0x7A36AB935BD217E2ULL, 0x77F5D662B097B65FULL, 
            0x1F3CC4EEB0198DFEULL, 0x3956552057D534DBULL, 0x41FB2CD007016739ULL, 0x3C5F1F7DA72E2B62ULL, 
            0x1C1B3CF3CF47C688ULL, 0x2CE5A364A7068D8BULL, 0x1271EC74E4224676ULL, 0xD6992AE831456902ULL, 
            0x24DF3B8A669829B8ULL, 0xB3CFFB55E583887BULL, 0x995D439FAC01B7F2ULL, 0xC0112173F3279165ULL
        },
        {
            0xAF02CB75C86FD855ULL, 0x782B41FA00D4C415ULL, 0x36C6C414A5C96DEFULL, 0xB56F9FA772C075A7ULL, 
            0xC959C0AE9E342E69ULL, 0xC267AF0B97242BD0ULL, 0x4A754AD5265C42B0ULL, 0x21E2DEC5CCFDF756ULL, 
            0x277A33C225BAE245ULL, 0xCA65CCEB62BA7C34ULL, 0xCB7E5C863496019FULL, 0x8C9205214EC659E4ULL, 
            0x882A7300E8C5AFB6ULL, 0x41E5F9559034E3E5ULL, 0x8390251C36BAD39BULL, 0x0AFAC71EDEDBCB04ULL, 
            0x5F5A26DBC7841ECDULL, 0x4E03D5BE96DED4DFULL, 0x7FEF73CAFCD8CD6CULL, 0x1DA957E83D78BEE6ULL, 
            0x782EE7A5AB154EE2ULL, 0x054655D6C93B9CC0ULL, 0x577B167965F5F9E5ULL, 0x4A75F7B054A764C1ULL, 
            0x4003573EBDA9A739ULL, 0x8A69F6458F4FB16DULL, 0xFDDB3C8BBBE8A624ULL, 0x4CF0FB9E1F07ABEAULL, 
            0xBECDDCFB58F05561ULL, 0x9970F3D7FEEC706CULL, 0x5D2323A694CD36BBULL, 0x7071DC1B375CAB36ULL
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
        },
        {
            0xEFE3820969F347DAULL, 0xA8D4C4A665B5EFC0ULL, 0xA1F538BC41FE9969ULL, 0x92059C93604A87E0ULL, 
            0xFA8562C6A723D470ULL, 0xFBCD4ACEBE10A3FEULL, 0xEF20B5A2B1294156ULL, 0x9E8D02328C3E6961ULL, 
            0x48E628BE72BC5052ULL, 0xACEDC67F972560CAULL, 0xCEE14B30C9F9805BULL, 0x95BBF8C55B06437DULL, 
            0x78669D2E044A7511ULL, 0xFC5517622F6979B6ULL, 0x7AFA7E3C8737C7A7ULL, 0xBBCD3B335E46BC19ULL, 
            0x54B2E7AEABFB970DULL, 0x81932CA6ABB82F6FULL, 0xC87C3E3C2B23C55FULL, 0xFC977FD4CBB73929ULL, 
            0xE5EB189D9EEF1881ULL, 0xD12492992DFA6ED3ULL, 0x6E5DA3C3545D4794ULL, 0x133334FEFC914E30ULL, 
            0x622FBEEF6D179AD1ULL, 0xFAC3DB5E4359509AULL, 0x6679FBB5508645A8ULL, 0xA4966AC564B56FEDULL, 
            0x79ECC469CA6CF1D6ULL, 0xD7286B4B1DC26649ULL, 0x4D7C68CAEF7378ADULL, 0xDB3AFE2DAD0DCE42ULL
        },
        {
            0xC2B4E472894D14AFULL, 0x79DF68D9EDF62DE0ULL, 0x7169E908067251ADULL, 0xA6E743D8C7847DC2ULL, 
            0xAC1D8561C2EE4911ULL, 0xBB3B81866699D566ULL, 0x33001526B3CDC406ULL, 0xCAC9508BC468F5C2ULL, 
            0x6FA1C13DD7CC9455ULL, 0x79E92FAA91555786ULL, 0x130F8CAA3A57BF31ULL, 0x08151D63AA0F172BULL, 
            0x0080787AE1729A2FULL, 0x538C6DD762DB8C0FULL, 0x2BC5D7277C4AE734ULL, 0xC700FB86D8C179F7ULL, 
            0x499576E6672C1083ULL, 0x20AD4E7A593A1548ULL, 0x53115B08054B00F9ULL, 0xF030A10259914FA0ULL, 
            0x9D8EF5D359094D97ULL, 0x5CC74C21963D3560ULL, 0x34100C12539E98C9ULL, 0x8C5C21C8BDE92533ULL, 
            0x2EA747C13EFDF328ULL, 0xC23A0D523F560410ULL, 0xD3C09354A1687375ULL, 0x00BB0E0DAF1DE1BEULL, 
            0xDA0FE32D1F79A09FULL, 0xF46B9E144FE5FACBULL, 0x2007B248D5E3FE48ULL, 0xA7668F43F158D015ULL
        },
        {
            0x3006CCC9FB39E575ULL, 0xA3B3DC89DCCE67D9ULL, 0xEC5BC545E120E97AULL, 0x40A5E901791E6B1CULL, 
            0x0B135A80D7D594CDULL, 0xF71AE7F470DE4775ULL, 0x47F9707C7A66F3E0ULL, 0xFE8D28C2AFDE557EULL, 
            0x041D9D07EFF3BF1FULL, 0x012992851C2AE342ULL, 0x80F9C27C9E27D14CULL, 0x6C2B9B948DD3BFE0ULL, 
            0x0E4B6B21678B194FULL, 0xFA597486669973D2ULL, 0xF7165782FC5E0FC1ULL, 0x827DCCE915F68322ULL, 
            0x2C0313B2EA90D04CULL, 0xB93C6599727308B0ULL, 0xA4C5CFF43C215736ULL, 0x34577916137D6AB6ULL, 
            0x8CD25FED6747339DULL, 0x41E96541B40A5FA1ULL, 0x7A055621CD2362C6ULL, 0x586734B8E7708F5AULL, 
            0x91B48527378C1C11ULL, 0x3C04CAD1B0829BCEULL, 0xB54791392A0D8386ULL, 0x6B32C1545E483762ULL, 
            0x6A6212140E830E17ULL, 0xC03F781726C544BAULL, 0xB68D4D77C5E4E9F2ULL, 0xA21679294C47A106ULL
        }
    },
    {
        {
            0xA9AD2CCBD0E2A62FULL, 0x73DC55C6FD0A3BC1ULL, 0xAA33AE4B7FDD7EC4ULL, 0x38345600C735EBE5ULL, 
            0x33FA092BCE512D7CULL, 0x369CEC57C2AB797AULL, 0xDDAB4F5AB17F2CDCULL, 0x3EF4F29B591B66FDULL, 
            0xC22591588733B298ULL, 0x31206FB11496C866ULL, 0x5DC82F62B7508C46ULL, 0x735A69820B74C598ULL, 
            0x91D61CD3D26B01D3ULL, 0x276CC8DFC122D9DFULL, 0x0F1E207C42E973BFULL, 0x77F8F1FBAB77A0CEULL, 
            0x1B6AA9986F0C3474ULL, 0x7B014685897241D4ULL, 0xF32EA9BE3DD7476DULL, 0x3815667BD37A14C9ULL, 
            0x838FACA20DD784CAULL, 0x2C01E671ACBFD1C7ULL, 0x1DA971003A45B750ULL, 0xDBFA89438EDE3250ULL, 
            0x47BD470BFB05A6F9ULL, 0x8EE9259D610DAFA1ULL, 0x10DC783AFC9B8ACAULL, 0xC1E83FDD7410BC34ULL, 
            0x5F1BF1CC84409559ULL, 0x9EED84C67DCB1CF9ULL, 0x8CD95AE4A434A42DULL, 0xDCAE7FB9F5521ADAULL
        },
        {
            0xABC03F05054AF33FULL, 0xDF346C0A379047B7ULL, 0xA19176AFF90CB8F4ULL, 0xEC187A2396371E7AULL, 
            0x9DAAFF99CC6C264CULL, 0xF255E44D4C74F008ULL, 0xFA553BE27F1B7FD8ULL, 0xC4BB8252A059E518ULL, 
            0x83D3836CA995C3E8ULL, 0x31BF027920B14A7EULL, 0x3D1E841B10679E50ULL, 0x1F4C568D82F19A2EULL, 
            0x3AB1F8AEE7B0BA05ULL, 0x3FB98DD934E5E439ULL, 0x7BE885DEDE9FD88EULL, 0x8C3B385014A772ECULL, 
            0xC11111ECC4DDFC39ULL, 0xFDE5D0CCE6317C2BULL, 0x0B956263D02A98C3ULL, 0x1BB6EDC1E8BF943BULL, 
            0xF57E12F5C3EEECB9ULL, 0x61643969BB65FA45ULL, 0x78F9207E5D264EBFULL, 0x1071BB865311ABD5ULL, 
            0xE47443741C83EC2EULL, 0xAEC2C96AD3A98358ULL, 0x609B082CDD4D10ABULL, 0xD38CD19B6EAF9E37ULL, 
            0xB63AE5FEAA3023AFULL, 0xFA57A3DE065336D8ULL, 0x0F3F96A30A8CFA96ULL, 0xC6A60903524A336AULL
        },
        {
            0xF358989E6A649FBEULL, 0xF1ACB661BEFF7326ULL, 0x76D41DE68705516AULL, 0xA16A9516FA108A55ULL, 
            0x6F9EC53F91CF0BE4ULL, 0x45BC1C75C3BB2980ULL, 0x20ADAEA1860FC647ULL, 0xAA122C207F766C9BULL, 
            0x4EDC169C56C5D49DULL, 0xA33EA5128A19EF70ULL, 0x4C409F20C8101067ULL, 0xB916CC1CCB40E9A1ULL, 
            0xC7B082FDDD8C2128ULL, 0x5812E2DF6C580E9EULL, 0x61939395406DA1D3ULL, 0x3F0F7E0C6D2C91F9ULL, 
            0xD02ADAAB954884C1ULL, 0x10A818409550778EULL, 0x5D79AE474F50C7B8ULL, 0x22DAEDD80385FD0AULL, 
            0x88160AB5A733030FULL, 0xCBE0EE8306A5701DULL, 0xEB9A3C09DF13A67AULL, 0xA3B5C1277114C7B1ULL, 
            0x31BFE6A36B91E19BULL, 0x25EC02A3B7A0BD0EULL, 0x82E01D87E3F816E4ULL, 0x53158E1B634F26ABULL, 
            0x9B306CE7F7E60399ULL, 0x7F869F17516E9A0CULL, 0x17C4F7E5905D599EULL, 0xF87D50ECE1AE0E66ULL
        },
        {
            0xCE717CBF7301CE82ULL, 0x4EDCC888202C5C94ULL, 0x53C54DAAD8D6DCACULL, 0xACE3C96FCB941F89ULL, 
            0x879C74481B4D2848ULL, 0x00DC5D3A7905D31FULL, 0xD14671FBB97AA6D0ULL, 0xBABE6306E1F12E88ULL, 
            0xF2037C5F8C0494BBULL, 0x20632D6DE4EB43CAULL, 0xB66A37442029A199ULL, 0x6480B5182531535DULL, 
            0xCF067F29891730C5ULL, 0x33BB1F545F4759E6ULL, 0x1584627A266F40A7ULL, 0x6EF7BF17F6F48E25ULL, 
            0xBC7559A597EA6F3BULL, 0x1EAE32F464F6EE68ULL, 0x12FDE3F1E80787F9ULL, 0x5DDF82FE5FEF76DEULL, 
            0x29BD206EE087B738ULL, 0x230EC018C25ECA29ULL, 0x50C814355BA67319ULL, 0xEBD6D284BADE8880ULL, 
            0x01CD9B5117327C9FULL, 0x8CF7ED53406A176CULL, 0x74765204F04CB17EULL, 0xC4433E00F303F814ULL, 
            0x2DF18EDF0BAB4265ULL, 0x1EF6ADBED893C014ULL, 0x1217A790ADFBEEB6ULL, 0x29CCA85306953C10ULL
        },
        {
            0x10E1B1E283507586ULL, 0xD2588983F22E6BDEULL, 0x468F6B174A3E373CULL, 0x21382CA5A2F4B6C1ULL, 
            0xB95CC0913F416108ULL, 0x73BC8A5B963CB410ULL, 0xA56C6D553874FD74ULL, 0x50312D75457F0442ULL, 
            0x15C68620347CC10CULL, 0x657C4BB36526CBC1ULL, 0x70F16CB7114A40D0ULL, 0x8A5DB07D319534FEULL, 
            0xA7603AF882A0C942ULL, 0xF5995005F504E28DULL, 0x237C2C0F668E9501ULL, 0x960B945F70C5D8D4ULL, 
            0x059596A4E873E6D5ULL, 0xA223392AE19A94A9ULL, 0x3EA4E366322223B0ULL, 0x35787F033D68F00EULL, 
            0x18C6763804FDBFCBULL, 0xC588ED12CFB80C6DULL, 0xDB39168D0C95CBC8ULL, 0x11709AC91C070245ULL, 
            0xB5B46D0C2067CA87ULL, 0x3005C1BC32F585ABULL, 0x7C00BC850A519461ULL, 0x8104F8EBE84F1A4CULL, 
            0xC43EABD1325E09BDULL, 0x9E25031AAB76CFFAULL, 0xBECE2C3653FAF41CULL, 0x7FD7C9E6194B334AULL
        },
        {
            0x337ABE9BEBAC35FFULL, 0x11BCCE99D58CD124ULL, 0xEB5FCB6C57C52DE6ULL, 0x2EB0E3C2F9F44D2CULL, 
            0x9CA00FB4CE48A5ADULL, 0x338F634DC48F55C3ULL, 0xDC1A61511D47FFCCULL, 0x221175D92BF2FBACULL, 
            0x190E9242DA23A4E9ULL, 0x8B23F1BA8BA41EA2ULL, 0xA4B609F45B8E14CDULL, 0xC1388E440A3AFEC7ULL, 
            0xB9FABEF072F676B1ULL, 0x570BD85EBF272D08ULL, 0xF23045855FDB12E9ULL, 0xC2609F9CA625EBE8ULL, 
            0x57659B6040FBB115ULL, 0x7CFEF3F16BBDCB1FULL, 0x249F13B781DD3D39ULL, 0x1E89B14E00456D37ULL, 
            0x5F6FF24185A6CF38ULL, 0xEE4EBD126DE3982DULL, 0x8CFD82133E2FE5FAULL, 0xCAF06F6473322E5DULL, 
            0x5CD93E38E08F52A8ULL, 0x35CDEC303B1160F7ULL, 0x4828257981550080ULL, 0x5ED8F713308669D7ULL, 
            0xA3A92516431F2A7EULL, 0xBE9601D9F899C06FULL, 0x0409D5FBED9119A3ULL, 0xA7C5CB9BFA220B5EULL
        }
    },
    {
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
            0x6946C2DF9F4B3156ULL, 0x0A7EBA7BEEC1D582ULL, 0x3B9B407F4DDC1F7FULL, 0x6380E55BB975786CULL, 
            0xFF81751B391F6285ULL, 0x4FDC3B86ADBB08ADULL, 0x0A28229CFBC8AB70ULL, 0x85470F7B96E40872ULL, 
            0x9177234E84EE3E78ULL, 0x768C5E3C7D8412EFULL, 0xBDDDB2A64D1B338CULL, 0x8C485EBFD18F9091ULL, 
            0x4D34A2D6E9397B56ULL, 0x8EF5C42C65275B2EULL, 0xAA0B845CA843653CULL, 0x8E7BD74848EBEB7FULL, 
            0xCC754F58EF4F2D5CULL, 0xC33E7B6172D12BCCULL, 0xA27C32D85A5F5893ULL, 0x065F37AA93F910FEULL, 
            0xEC201F8EA096C096ULL, 0xC0442AB7C862A660ULL, 0x6F8A47F4A625114DULL, 0x0D1A3B4EEA45E6FAULL, 
            0x85A5AA6F8AEF77D2ULL, 0x4C282A343CA8579DULL, 0x2ABD43BD7E42EFF4ULL, 0x46095C9AA6115B5AULL, 
            0x2F55059C19D1F83AULL, 0x1A10AEE6DC583BADULL, 0x6F7BCDA12E088682ULL, 0xC18C869CCD4FEFCDULL
        },
        {
            0x3DA450F054C86FAFULL, 0xE2AB8366B8EEB75BULL, 0x35853478062B02A9ULL, 0x6645AD999E3365D4ULL, 
            0x70AAAC5C6063B4D3ULL, 0x9A605244E7511E8EULL, 0x42A817743C26B5CFULL, 0x5A19F953C357FAFCULL, 
            0x8BBCBA71B6AC6F86ULL, 0xDEC052C2965C28E3ULL, 0x8A8CB108CD821755ULL, 0x0EF4509642E51C25ULL, 
            0x6B0D89BA759BDC68ULL, 0x90C0A1E69957F444ULL, 0x6AC1334DFC28BC66ULL, 0xB3740C83A4449A24ULL, 
            0xBC91C6B306A040A8ULL, 0x0A5F252E5E1D2E9DULL, 0x815DA118A3E3322BULL, 0xD2E0CBA63E4BC7B0ULL, 
            0xA5451E98E475BED7ULL, 0x6732235BF279F6EBULL, 0xCE1DF35CEBB868C8ULL, 0x070864FFDADBBB9EULL, 
            0x526626029A192D9EULL, 0x8DF627A7BB6AA87FULL, 0xF8DECAFBD924397DULL, 0x526F7C76E76C231DULL, 
            0x571B8CAD57FB1D92ULL, 0xF400A1E18E3E42EAULL, 0x51E2E92E3D538A0EULL, 0x61DA58C78ABED6F6ULL
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
            0x636908D93A4486C1ULL, 0x8069600BDD17B61DULL, 0x0B6879A4B410721CULL, 0x67CE453E9E0A937DULL, 
            0x0F2913262E3C77F2ULL, 0x222EB8DE58DF89CFULL, 0x89715247C6C067BAULL, 0xB43F634715A4C5EAULL, 
            0xA1E2C1068BC83290ULL, 0x67B8E8225A71018BULL, 0x6D3A2B4B21934771ULL, 0xAE98420BBE2E72E2ULL, 
            0xF5BB626CB2AE19F8ULL, 0xEFCC7D31E7EC66D5ULL, 0xC3D12C6341CBE831ULL, 0x48C49C2B619AC92BULL, 
            0xDF4F41404E106871ULL, 0x7ECF7D1A72F2628BULL, 0x962FB59059621C85ULL, 0xB93F94E8288B0E00ULL, 
            0xEBD26AE427EE53B3ULL, 0xF939ADAB3C099788ULL, 0xC0994B5A24459743ULL, 0xE491EAA1C4537B7CULL, 
            0x0519F33EE6056CDFULL, 0xC1949BF76576C27DULL, 0x501043685F113380ULL, 0x0523F5B462490FABULL, 
            0x6E5E5E514CED93D6ULL, 0xC744DDFFB23FFE54ULL, 0xC5CFD05327EF80BCULL, 0xFC2A531E77240E2DULL
        },
        {
            0x23183317CDD207BFULL, 0xDB5EC0BF661F1E04ULL, 0x2A4204DC72EF233AULL, 0x9C8F25EF41371D23ULL, 
            0x1D4FA98E822D8C9FULL, 0x505870C440575261ULL, 0xB6FE9D7482E22094ULL, 0xA6E2881F34C160E3ULL, 
            0x7E0D6625463D0C64ULL, 0x156F802E59A4D41BULL, 0x208FC5D45285D5A1ULL, 0x2D1F50D247D5DECEULL, 
            0x3CF839A1DE53E383ULL, 0x2A0A0909EA5B9465ULL, 0x390CCA99FC423CB9ULL, 0x12E4C9AF3E52804CULL, 
            0x9F0CDD7C0807A28FULL, 0x9C34A20205372BF4ULL, 0x98183B8E39562D83ULL, 0x9B6953B5DE493B3EULL, 
            0xD94CC0BE37D01A19ULL, 0x236D8934AE70A498ULL, 0x5F26564E71A0929EULL, 0x62594BCD4A308938ULL, 
            0xAA80A83A3A905994ULL, 0x038F1A4007C1E2ECULL, 0xB3DDE6D3646B8CF2ULL, 0x07E91A5AEB36E5D5ULL, 
            0x091876EC454F2176ULL, 0xEE356C540B3FEF4EULL, 0x5CA3CAC2D9BA74E2ULL, 0xEA1849BF984388E5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseEConstants = {
    0x6E6166ECB630C3C4ULL,
    0xF6D07262655DA0E0ULL,
    0xA686FEFBBF0CAE3CULL,
    0x6E6166ECB630C3C4ULL,
    0xF6D07262655DA0E0ULL,
    0xA686FEFBBF0CAE3CULL,
    0xCD75C36DB7525C1EULL,
    0x9DE2053A16695F20ULL,
    0xA1,
    0x3E,
    0x44,
    0x46,
    0xA7,
    0xD6,
    0x4A,
    0x74
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseFSalts = {
    {
        {
            0xA0B20F7F8DE9D515ULL, 0x52F794B2129EDF71ULL, 0x778024E21E7B5FC9ULL, 0xC55C94E02F72D86BULL, 
            0x967F2EA132BD90A8ULL, 0x15FB52FFDE34C646ULL, 0x1914B77AFF05984BULL, 0xDDDC978AD5496219ULL, 
            0xE649DC4ADEEC8BE5ULL, 0x4BADD7B0FD4DFCC1ULL, 0xCA0B3C3A18F19E9EULL, 0xC6093C9AA41A7E1DULL, 
            0x8DF44EC16DB03EF1ULL, 0xA90CEC64B193FA8EULL, 0xF47FAEE8870069ADULL, 0xB2A96C6C6737E425ULL, 
            0x9621EB596561C25EULL, 0x17B16AA4B081E3F8ULL, 0x62F28B7AB873C703ULL, 0x3B8479C1D7861558ULL, 
            0x2D658EBBA12A66E4ULL, 0x7F428E77C4C319BFULL, 0x5376E0C7C4D35E1EULL, 0x26588667E9A52142ULL, 
            0xC6B61EC3671D8876ULL, 0x56C527480D7D2506ULL, 0x734F4B0F24CFCC2EULL, 0x06B0B563774BCD6FULL, 
            0xDC0740B633B344BDULL, 0xA415347A489B881CULL, 0x5D18C4C4C8D9BAB1ULL, 0x9C8045F2C70743DDULL
        },
        {
            0xB515082A8DA2DC55ULL, 0x149CE73C9E4B85B5ULL, 0x73B326892C49B766ULL, 0x49E6C78DB3A13196ULL, 
            0x70EE3C5C51AA06F5ULL, 0x525179C1DC898880ULL, 0xF21B6A82942F5A11ULL, 0x2F917C076D35ECF6ULL, 
            0xF958967DC615385DULL, 0x47EF6A48B1133ED8ULL, 0xA94671F3A1A1332EULL, 0x371B0ACD405336EAULL, 
            0x46831BA10A15B198ULL, 0xD292E9E287A490BFULL, 0xA2BE4F7369247BA9ULL, 0xDFE74E5585F82EBCULL, 
            0x9B50BD57E323FDC8ULL, 0xB3443C54E0665AC1ULL, 0xDD9849B9BAB2E19EULL, 0xB9A5037245FC4ADFULL, 
            0xF947B0561B1E25A3ULL, 0x100AB003B92F8639ULL, 0x1DE7ADCDFF257922ULL, 0xE41588C49FE91C5FULL, 
            0x9425C017A098F379ULL, 0xF39F7EBFA56F76BBULL, 0xE72B3DA7C4EAC28FULL, 0x9092B30B2A4B52C5ULL, 
            0x7FDB8049BBE88FECULL, 0xE9F9DAD961574AAEULL, 0x81A609800F20F25BULL, 0x8E80CB1A2533D064ULL
        },
        {
            0x1705116C9B59053DULL, 0x7E5F986052EA618CULL, 0xFA23AB15709906EDULL, 0x572E8166FFA472BAULL, 
            0x66B8222AB922EEA9ULL, 0x92CDDCA56E34FC59ULL, 0x4B7A6D129C7FC082ULL, 0xA94CCF884737237AULL, 
            0xEA53FC4B435C7F87ULL, 0xB402444FB5876397ULL, 0x466A366A57193A07ULL, 0xBE5C266E44445F6FULL, 
            0x41FEF55E2643D8BAULL, 0xF40CE63D968C7642ULL, 0x4A45CA1ECB8DDDA8ULL, 0x20C0DD33D3F6104BULL, 
            0xC33F8DA3CDCDF562ULL, 0x1B7C29A628A60057ULL, 0xF6D3E09DDD4EA054ULL, 0x87C2724901FEA338ULL, 
            0x0660394CEEFD11C0ULL, 0x32BE9CD5689DDB0EULL, 0x73142BB45A847A7BULL, 0x56DFE099A91394A8ULL, 
            0x7D8FE870C9292FBAULL, 0xD4CC249646CFB2ADULL, 0x33B6933EFC0892E1ULL, 0xC117145631A2F301ULL, 
            0xBBAEFB04625AB0BDULL, 0x166279959202C747ULL, 0xBCF4C7FBBAF5F4D8ULL, 0x1C1EFEF210DEDCDEULL
        },
        {
            0x479D90B9CD01E79BULL, 0x78D0CE5E4E2CEF74ULL, 0x711DFB4F4E49B6C4ULL, 0x37F6B5364525ED91ULL, 
            0xEA83EF3E05C51C08ULL, 0x83BF2F13C4151FE5ULL, 0x63586BF9FDA239BFULL, 0x745570710270F038ULL, 
            0x1E25828A2469DB52ULL, 0x8C2548AF28FE3D97ULL, 0x530695FAE06098F1ULL, 0x3E7D1FA5E3C83AB0ULL, 
            0x524CCE542EBEBF83ULL, 0xC2CD9DD8C97F7429ULL, 0xFA4C08E01ACFDD2FULL, 0xCA5994F2C6B6B689ULL, 
            0x3DFB34E274965BCCULL, 0x5987CCAC9AA348B3ULL, 0x618A4553C7646D30ULL, 0xE543375386F0D75DULL, 
            0xF4951996BE729458ULL, 0x5B91DAB21145CF6BULL, 0x324600B1E83331A9ULL, 0x0E300FB5CF2B73B3ULL, 
            0xF77CEE67BB4C013BULL, 0xCF32AC80B132C714ULL, 0x92C2DE541FB11C61ULL, 0x0DDDB0BAA37E9938ULL, 
            0xB0739DC8260A875BULL, 0xDDD3CFE765F20CFCULL, 0xAEE56DC0E4223B2DULL, 0x9298D547CEE4EC10ULL
        },
        {
            0xA25B95C947D7D7B2ULL, 0x9F15A7F08F69FC04ULL, 0xB199832E9F320C59ULL, 0x4D17A66A6438982AULL, 
            0xF4DB1C91E5C70811ULL, 0xA4DAC783E7A5F0A1ULL, 0x63764D77A7BA8348ULL, 0xDDDE25E7F38A06C4ULL, 
            0x6E96544912960789ULL, 0x4A8C272D55930E95ULL, 0x4C107BC986B69229ULL, 0xB0AC35F7B0BEB4B8ULL, 
            0xA0DCB0046C790FC4ULL, 0x0F03D18DBFD66B7FULL, 0x07E989F54759995DULL, 0x501B2750FB22621EULL, 
            0x69FDCC87612DDD8EULL, 0x00D6847A051BF9FBULL, 0x90905EBD1E2050BEULL, 0xC8E9ED5EC7360DACULL, 
            0x5F4BA140F3384C04ULL, 0x431B169CC72FD1C4ULL, 0x6935AB40DFC2675EULL, 0x4D8EACB67B33BC81ULL, 
            0xB34335F02655BCD2ULL, 0x3BE7E396A9FBBCFDULL, 0xB7CA7969A6000E0DULL, 0x44A059500E35FA40ULL, 
            0x4D83E8A0B225F8AEULL, 0xA23A8616E11F95D7ULL, 0x6E60BED2AF8EDA3FULL, 0xB86066C478987C65ULL
        },
        {
            0x7D51F365DDFB4F93ULL, 0x7BA895B5FF9BD9D1ULL, 0x68A22193505DB9C7ULL, 0x1F70DC775A953D09ULL, 
            0x64A140EFE007F1DBULL, 0x68EB2D0C9B5EA93CULL, 0xB85C0173DCFC40DCULL, 0xC122EE70490CB1ECULL, 
            0x845619626C2DBAF8ULL, 0xB076C3AD430E55D7ULL, 0xB6B2A059A07A0FA5ULL, 0xAE225EA375752D7CULL, 
            0x270FC6E16036E67BULL, 0xB10D98259616A688ULL, 0xD887EA74E0B9404EULL, 0xF128E94D023244F8ULL, 
            0xD5C6E65F800E37E9ULL, 0x9536B318EBF483E9ULL, 0x0B28F1C3B09D3749ULL, 0x8FE349371073276FULL, 
            0x4C439267A1550423ULL, 0xE3BB18A84B4F953CULL, 0xEF26160C73533628ULL, 0xC463D0C228DA2412ULL, 
            0x9828844F64D5DF63ULL, 0x7927ED763E6A60CDULL, 0x67223176EBE0AAAFULL, 0x35C86843AB366B8DULL, 
            0x63C47B47E99A7510ULL, 0x92D18297F2CE3A27ULL, 0x2D7DA61053AF0D5AULL, 0x94685180CFDDD1BFULL
        }
    },
    {
        {
            0x08CAA5EBA11CC05BULL, 0x2FFCD9BC41D15445ULL, 0x9BA41534F4DA12A7ULL, 0xBB415D7D28F85C86ULL, 
            0x486BEA9FCA61BE96ULL, 0xD9EFBA6795245EEDULL, 0x94A695D726B32AF3ULL, 0xED3F96CB31CCE536ULL, 
            0x1455DF9477436532ULL, 0x438E7BC0DBB9889BULL, 0x3937FB3CF5FA6653ULL, 0x7F5F0E47D631B5AFULL, 
            0x460EA66888B80F7DULL, 0x3A46640D4B74BA45ULL, 0xAAB9A7B6C8BBD596ULL, 0xE6CC245392E09422ULL, 
            0x9CC7E004175790F2ULL, 0x28E7C63207461D78ULL, 0x9682C234C750185EULL, 0x552E8C8F7A93C1D0ULL, 
            0x5F7EC5F3C416392DULL, 0x21E3A08E2DA24F0AULL, 0x143C3F62669DAEEAULL, 0x347F4E64DB4F867EULL, 
            0x84A24C129EC67600ULL, 0x058A6E5F51E88923ULL, 0xCF3D52118EAFC7B7ULL, 0xBC50728B4C517162ULL, 
            0xC8C030C08A61BC6FULL, 0x412CA8C5B40CB8BDULL, 0xA871A23FE10B4F64ULL, 0x613A59B113C0DBC6ULL
        },
        {
            0x7EDD1743FC90191AULL, 0x9EAD802D059489B6ULL, 0x31404FB50E4D67A1ULL, 0x8B60460CBF56E86FULL, 
            0x37AD1CABB27BF3F8ULL, 0x59D2833E55FA9065ULL, 0x1C6917FE1B46A3B1ULL, 0x44614C7A8D1D154EULL, 
            0x49D1B95DF9CBD6AEULL, 0x4934DD7CE95A12A6ULL, 0xB041BB8647DD32A9ULL, 0x7EFB109043B5A5A3ULL, 
            0x359CEFA7D4EF1452ULL, 0xA2C934FF1A713FDBULL, 0x84AA6C47C4D32B73ULL, 0x411E7745334CAC9AULL, 
            0x0E48D87B483FE903ULL, 0xAB7DEC36F45AD230ULL, 0xB619E21E87E026FEULL, 0x693BC0A876FA3CD3ULL, 
            0x0391E73A53492D35ULL, 0xE368C624F882031CULL, 0x9DFC47D0E603CC55ULL, 0x3E66A49C1E4575CFULL, 
            0xF9DD9FFA6335FC48ULL, 0xF536A83425454216ULL, 0x5D14C2E13CE2E0EFULL, 0xCF82D96107242EE6ULL, 
            0x1CD4111B765FEABBULL, 0xDE4ACBFE6A8C0F42ULL, 0x84C49AAE5C928E7CULL, 0xA65C0ECC0D307BC6ULL
        },
        {
            0xDB216A31B924943BULL, 0xFB9F7BF2BB4867B3ULL, 0x55A32667D00BA3BDULL, 0x6D615E02799E5C6CULL, 
            0xE8574442033F82A5ULL, 0x84400E37A3A34E3FULL, 0x8762DDC62BF5D915ULL, 0x18D78DC7A69F6874ULL, 
            0x0D04501A9DDAE7F5ULL, 0x894D95906B9267D3ULL, 0x4378172DF4C9AEB1ULL, 0x10C9F37ABFCDF9C2ULL, 
            0xDAEC4ED47BFFDC18ULL, 0xD53516E715B19A29ULL, 0xF9B36BD894705BB2ULL, 0xA786667DA4A1908CULL, 
            0xAE3066516E36AD0BULL, 0x4FE1410545D46BBEULL, 0xC2501A211CE0E1A1ULL, 0x8A2508F711028F5BULL, 
            0x844B97C0F63C3D45ULL, 0x76D4A12A0655EA5FULL, 0xFF22BFF680FDEB62ULL, 0x1F3FDA208129137FULL, 
            0x13F1C4D41B5FC458ULL, 0x62F3CE4EDE1D3D69ULL, 0x63FBDCE5F44A92E2ULL, 0xAEEE4F0DDD197ABBULL, 
            0x3274CA6924B7FE59ULL, 0xA98A23D9E19B78E6ULL, 0x1FCA18155DF0B1D2ULL, 0xE70B16DF7530EFABULL
        },
        {
            0x79A62FBB02C9F533ULL, 0xE9CE2DAF81322297ULL, 0x7B18ED258E095808ULL, 0x50D57B34C3CD3A7DULL, 
            0x742671D862CF58F2ULL, 0x4F6FEBF7A0A1E606ULL, 0x78D80FFFC3EBDF88ULL, 0xFC9EC7772FEBA2FEULL, 
            0x57F1714E3183EFDAULL, 0x1C3D55FCDA656AD5ULL, 0x1CF09FB609809CB7ULL, 0xA127482C3D1C1A44ULL, 
            0x157492F61ED4DC57ULL, 0x17AB126A5077C51BULL, 0xCEEF4AB32140B085ULL, 0xA8EB8C0512702FE5ULL, 
            0x3E9CE54AD83DD67EULL, 0x7D597D142BCFAD1BULL, 0xDE40397DEEDCABEEULL, 0x7D0AA3D6702BDC6EULL, 
            0xBDA21A658F6062D1ULL, 0x68C154AD8D2F34F8ULL, 0x1428DEC8285AB8BBULL, 0xEAAAC7D02FF74A8FULL, 
            0x3B0FCF2A0A79904EULL, 0x69B6B4E8B15BBB79ULL, 0x5BDC1B25CD5F6984ULL, 0x9C6CEE031221A827ULL, 
            0x5520EA862FD779C7ULL, 0xDA67545FCE9A4D7FULL, 0x30700F790869D408ULL, 0x6D15500251E2ECD1ULL
        },
        {
            0x27649AF0A16CCFBCULL, 0x1ED11E8102D2D800ULL, 0x0B3A098D9314E157ULL, 0xFEA1A9027FDF6613ULL, 
            0x4890DC5ED1ADC5F3ULL, 0x94F71483E9EAB54FULL, 0x0FD96EE65432807BULL, 0x5C6F0D016815DD7BULL, 
            0x4903F515240B79F0ULL, 0x2E5BBC7C99388973ULL, 0xD643DA4B31D0E9B4ULL, 0x47D1870B30E060F2ULL, 
            0x04650C4EF6A665ADULL, 0x690913292E4BCFB9ULL, 0x5FFA049C6960AA81ULL, 0x0DBA151ECDF9D243ULL, 
            0x644269C5B48C2355ULL, 0x8B8D88AB78861234ULL, 0x3A5FC273C9F5A961ULL, 0x25B5AC4E2C081F25ULL, 
            0x268120DB53C6554DULL, 0x2620BA66F455FAADULL, 0x55B73FE0FAF19F3DULL, 0xD76B9E7F94A4E98EULL, 
            0xD20B573AFC98B39DULL, 0x52EFC772AE2CB453ULL, 0xC9793799488E4C5BULL, 0x825B063E240081C4ULL, 
            0x07915CACCEE1BFFFULL, 0x3679699158BED2A2ULL, 0x40EED3D0D13E50E5ULL, 0x8830E0D8369EE6D2ULL
        },
        {
            0x6411B46CC84F5BB7ULL, 0x5D3B6F72029D1663ULL, 0x8531A6DA06709C54ULL, 0x94FB08997D699B8DULL, 
            0x5964E3A24195B44CULL, 0x264223AEFE7E8697ULL, 0xA122F8085AFEDE26ULL, 0x814161D1EBFF7113ULL, 
            0x90A15CD23D643B3CULL, 0x0BF4E10CC882D449ULL, 0xACEE4734A3B40604ULL, 0x9B95326E5E2247B0ULL, 
            0x8197F8997954C602ULL, 0xA345ACC68E2BB244ULL, 0x8AF3EE4804DF9A19ULL, 0xDB2DF2EA2C50D66AULL, 
            0xC02F36A6F46D6FDFULL, 0x5655F416D436345BULL, 0x805FC12910BADFD4ULL, 0xBEA7E71153AE1807ULL, 
            0x4C40058ED6ACFF04ULL, 0xD95F7E21A14CAD5EULL, 0x5C29B6C1A00E9D85ULL, 0xABB69579697CBB3DULL, 
            0x84ADB86C3DEF13B5ULL, 0xD8803A055BCCB4D4ULL, 0x8AFAFBB5978C57F2ULL, 0xAC4341C62D5CD809ULL, 
            0x47DB26B628F63549ULL, 0xCB148CE7B6EC5A69ULL, 0x6A72F7C94C9A8F47ULL, 0xB93B91B2EBF6640EULL
        }
    },
    {
        {
            0xE9BBC7CD8B5A8751ULL, 0x8CC40F4C4C44CBC0ULL, 0x58D1E679E1B1E1C2ULL, 0xB03B86F337990BB9ULL, 
            0x4DAB1D6C0AF9EF4FULL, 0xE1FEA029054D3BD7ULL, 0x7070ED4D113D0EA3ULL, 0xE92CD20BD0478E7BULL, 
            0x5AE5B5931FD88C55ULL, 0xBD10A86C2090EF81ULL, 0xD381F53092EDAD8EULL, 0xBEF643CC0332426EULL, 
            0x332DCDBEF6DABE30ULL, 0xC764731209E1434AULL, 0xA0B6CD5701DCCABEULL, 0x36B703981B0563A0ULL, 
            0x7051E2929CB90EA1ULL, 0x7A845FC135951550ULL, 0x34D4298604684607ULL, 0xF0A4788B6AF341BDULL, 
            0x19C05D95E84778D9ULL, 0x46858B349F89C6F5ULL, 0xAE98AEDAAB57F18AULL, 0x5AB04A802517870EULL, 
            0xD0E3191057F37E1FULL, 0xB18D3FC4DFDED190ULL, 0xEB79B92169993A80ULL, 0x5BD13408940E8D28ULL, 
            0x4FB513054ADF0429ULL, 0x9167182FC5A05B55ULL, 0xF28A03C03436ABD1ULL, 0x9EDC007E6C698AA3ULL
        },
        {
            0xEF5929CB422FB900ULL, 0xDCB69BEE090B8357ULL, 0x58A92AB54CC06F58ULL, 0x196408463FF5D904ULL, 
            0x02828265E891E348ULL, 0x1B1671FD38EA6EF0ULL, 0x8D5BB12B68F9D1B9ULL, 0x5F58C510948B120CULL, 
            0x996AA32FE3B0D27DULL, 0x445DFDE772765CA1ULL, 0xAF8A156D4327B3A3ULL, 0x540058C191A831C9ULL, 
            0x185A6E79D1E00EABULL, 0x45E91D1432E67D8DULL, 0xBF121CD00B863F2EULL, 0x8764BE8178CE8394ULL, 
            0x8D7779E33E8F9DFBULL, 0x8A2188BB87F46929ULL, 0xD3AF8FB0F80918D6ULL, 0x3AC23A7A71B39D4BULL, 
            0xB5815F2BC4877D3DULL, 0xF508732F9E49E1E4ULL, 0x4E234647DA42780AULL, 0x13A05118FF1CFAF4ULL, 
            0x35B1D4F23A4C6C3FULL, 0x614622FAAAFA4775ULL, 0x6191920FBDBB02BBULL, 0xE7E7D415AE375ACDULL, 
            0xD9F274BC23CC0A14ULL, 0xD988D90E33BE30D0ULL, 0x258485F9C1C892ACULL, 0x6D4593E6B417F45CULL
        },
        {
            0x281A8962D89EF7D1ULL, 0xFC7495256FC3B7BBULL, 0x85B6CE1230B9055EULL, 0xF5A7242C5174F059ULL, 
            0x8D5432A60B659B5CULL, 0x3E46AD2B64F0592FULL, 0x8036A73965E2286BULL, 0x0EE0A893845282A4ULL, 
            0x23109AE8EC9F1F10ULL, 0x2EE637088727B504ULL, 0xD16A20567923BA1BULL, 0xD9CF54AE6C5AA63BULL, 
            0xD3CD83570FF22A5EULL, 0x7F9111A4360A65D3ULL, 0x7A396CDDFA6BBCC6ULL, 0x8D8FD06CE0E14AACULL, 
            0x85EA4967B2D3909BULL, 0x948115438E9C15CBULL, 0xBE387969A44B7A63ULL, 0xB1E02705C7B25D16ULL, 
            0xA07904A7B700257BULL, 0x4F45D74D0A0F6105ULL, 0xF2BA21DEB7852231ULL, 0x03A470747D5AB6F2ULL, 
            0x67CECEA93EEF4AE9ULL, 0x5DE7C7BDFDC71231ULL, 0x00C53C4B5BD3D1F9ULL, 0xE13C0109C014258AULL, 
            0xC6DD1133BDC68B3BULL, 0x2A88C4351800698BULL, 0x336B4C3D27EA22DFULL, 0x2F29ACEBB0FCD23BULL
        },
        {
            0xD78A93564F05F09BULL, 0x4F0ECEEBC0AE9B5BULL, 0xF9E6872541DDF283ULL, 0x5C5D7987F97BC384ULL, 
            0x8BC55E94FDE0CD37ULL, 0x23B96C58DB96DE64ULL, 0x3F85E72E55B7C425ULL, 0xE9D0FA38C86A1E81ULL, 
            0x01500F7C5D9876CBULL, 0xC871C2A685CF3DF4ULL, 0x9A258EEBC5D7D61EULL, 0xA4F28B410D348142ULL, 
            0x5945140A8D048450ULL, 0xBA81FFEE5DD0BA16ULL, 0x69C3D478EA2043F5ULL, 0x07AD1F9E37F26FF4ULL, 
            0x5B7FE0A292A98716ULL, 0xF628CDA9B6200DA1ULL, 0x9FDC4A5E774F2F51ULL, 0xE1D5CBB7E4D62EFDULL, 
            0x1A6A195D5BDFFDFBULL, 0x937CE55857C0F0E2ULL, 0xD5FC17D1E173A55AULL, 0x010D47F164E750EFULL, 
            0x46DF35678567B7F5ULL, 0xC008A21C41001829ULL, 0xBFFB451ABF28C4EBULL, 0xBF5C6BE99228F96AULL, 
            0xC582F0FD11CE8898ULL, 0x016A4D4D906736D1ULL, 0xF9C65A027EB7118CULL, 0x2D20613619B8E498ULL
        },
        {
            0xEAC5EA79D49117AFULL, 0x87A52C89EBDF8086ULL, 0x7CDEAA1B84F17263ULL, 0x384571126F8C26DAULL, 
            0x1AB63D9EA4EDFA21ULL, 0xCC3C8EAF8D7F0771ULL, 0x53844A18E97A05B0ULL, 0x6AFA344F921A1E0EULL, 
            0x910EBF4708D87FA3ULL, 0x077F0E8303EE790CULL, 0x5FA4A6E99EAD6038ULL, 0x968DE6F2DD2210FFULL, 
            0x30A31A9BB394286CULL, 0x7B55D1D48DF2E27DULL, 0x481CA9238DD14A67ULL, 0x30BA37FA4C0B8DD7ULL, 
            0x7716E29A37249CB2ULL, 0xB6894A9ACB954A9FULL, 0x22FE1AF6CDAD15EAULL, 0xE8FF10F33893ADF6ULL, 
            0xD9CF9BA8B7E3FB06ULL, 0x87EE53CCBB7BAE6DULL, 0x2141BAB40A0665B0ULL, 0x4B00A8E8E4FDCD1AULL, 
            0x4E3ADF0BDF7659F6ULL, 0x5C0C48FCC7FFB20EULL, 0xB70F41026AC561BBULL, 0xEEC7B1E00B64F78CULL, 
            0xD64EAB7569B5511CULL, 0xD791593C8379FB1DULL, 0x9570D98AE7490C16ULL, 0xB49A8E68EEBFC76DULL
        },
        {
            0x991F48D697FCC89EULL, 0xA4FFE533E4AFCDA0ULL, 0x0623C95E0D9152CBULL, 0x3F7E59D48D8434D3ULL, 
            0xCAD9D6A19E0C1C13ULL, 0xCB59C5594FD41B0DULL, 0x056CADCFA1F2AB75ULL, 0x8337E0665BF1F913ULL, 
            0xC6C491504DB0283BULL, 0x4DFEA1359AB57F63ULL, 0xDC3A47F8709735CCULL, 0x07B381AB9E5C3783ULL, 
            0xFFD8C90884C7A88AULL, 0x4DA185FE6D182C18ULL, 0x59BE55054A6FED07ULL, 0x6AF8DFF16AA34723ULL, 
            0xB1D7EF771EAADDACULL, 0x38218409197BAED7ULL, 0x0969DA58E040BEECULL, 0x87B49C0BF51AD67EULL, 
            0xEF7F0A88B101BE95ULL, 0x8330EEF06D7DC989ULL, 0x31B2174BEBC546E2ULL, 0x3FF7F3D2E8C06299ULL, 
            0x390EEE27F3C686C6ULL, 0x0F3FEDA9D30556F3ULL, 0xA49F969D9EE6C962ULL, 0x312D12FECAF0C4D5ULL, 
            0x3E1217C45A6EA3C7ULL, 0x3E9D2BF0AACA2D74ULL, 0x58907E35E7DB77A1ULL, 0x7A9E9E853DD623EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseFConstants = {
    0x6AB8E158CAD729B5ULL,
    0x474171195D8F8915ULL,
    0xB0EB4A2D2BA21610ULL,
    0x6AB8E158CAD729B5ULL,
    0x474171195D8F8915ULL,
    0xB0EB4A2D2BA21610ULL,
    0xBDB8781F060521CCULL,
    0x10C2047FF55803FBULL,
    0x82,
    0x45,
    0xD7,
    0xAA,
    0x62,
    0x8C,
    0x0A,
    0x2A
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseGSalts = {
    {
        {
            0x38B44A5F1502AAA8ULL, 0xCD116108AB8733FEULL, 0xDADDC3138A66B34BULL, 0x8879395FB77336BEULL, 
            0x08B7DD3F5E1E3F01ULL, 0xB461C8F23B5B9EB0ULL, 0x5D77962DFBFA73BBULL, 0xD1F900228F97101AULL, 
            0x9819BCA093C2C908ULL, 0x8CD1789D01B63176ULL, 0xCD62A13A0ADC66CFULL, 0xAA6531AADDFCE984ULL, 
            0x555B7956DF0EA899ULL, 0xD83F5A9644C2231EULL, 0x0C67639531F4B34DULL, 0xC0A9F581DD456DFFULL, 
            0xE8CF9EB16E7DDBBEULL, 0x1BF7B38B88D09A38ULL, 0x32F8FF27210FA64EULL, 0x6F1220398943D643ULL, 
            0x18CF36BE6F8A6D9EULL, 0xA3A8B73D8B57B6A3ULL, 0x12EF6A43F33CC8EAULL, 0xD2D2967EDF2F1C7DULL, 
            0xC36C5C7861DCA9FFULL, 0x8371DDE08531B89CULL, 0x8C8C9DDE14AC5D20ULL, 0x0FDA44E69D955FA0ULL, 
            0x1576B94F55960553ULL, 0xFBBA2F3AE6BBD696ULL, 0x7C69903480E24A58ULL, 0xE2C11FD803F1F18CULL
        },
        {
            0xA925A7ADFD02CE6AULL, 0xE2264D94D7CB7769ULL, 0x743BB022763DCE28ULL, 0x8AC4B0D5E0D6A99AULL, 
            0x99495340EB7FA968ULL, 0x84CF3A970A409C64ULL, 0x8D847B5C9A591CF7ULL, 0xB457D5792C2E534AULL, 
            0x13FE6A44A98B131CULL, 0x9EBF1478D323B4F1ULL, 0xB66405A8CE225B8BULL, 0x2CB1C94E161BB4C6ULL, 
            0xA6493BE8A3562B1AULL, 0xFF048C4C462AF43EULL, 0xB738AD121EA7887CULL, 0x9AE4D8C922ADC6E5ULL, 
            0x2A9010B446E13B79ULL, 0xDE8999E7AF268353ULL, 0xD0C5582C2ABB7F43ULL, 0x42BCBEE16674C36EULL, 
            0x60E87AC127A4694EULL, 0x2AF1E5A961C0D5FAULL, 0xEABD189BA3BE94F9ULL, 0x4406F355F76ED5F8ULL, 
            0x29A08079C86781F0ULL, 0x73AE8440F40E292BULL, 0x8E6A9D64EFE0A85BULL, 0xC2C49C91A0E0A021ULL, 
            0x8060BF2C1FEA656CULL, 0xA615450217099B4BULL, 0x5242932ECADD3568ULL, 0x87F403C340783F1DULL
        },
        {
            0x50372B9352D9003BULL, 0xEDA508BC140DD269ULL, 0xDBBE7EA3FC54BC68ULL, 0x7369CC033F57D472ULL, 
            0xAF880079BF66DA40ULL, 0x163CF504EB9763CCULL, 0x45A079CD9D021844ULL, 0x7BF177D5808AAF72ULL, 
            0xE0E2B2E5D2FEA8B9ULL, 0x4F8373E8FCD01ADBULL, 0xFED9D2F334F2034DULL, 0x6080FD5D745B33D3ULL, 
            0x4258FAE6AEAEE0F3ULL, 0xD3F3E25B42AD0515ULL, 0x2ABF7955DC85E474ULL, 0x4EDFA133BA95049EULL, 
            0xB4F528A3F093DD3EULL, 0xD03D1FB1177E80C5ULL, 0xE4B123D725E65AC9ULL, 0xACD77A9FDB188A98ULL, 
            0x41DE9B6D59249B8AULL, 0xDA2D5F421C2F631FULL, 0xB92B66F2C6C891EEULL, 0x7BB34E515669A88FULL, 
            0x4F8361E500764CE3ULL, 0x9140B53B05B895EEULL, 0x6AED3506DCC1BD68ULL, 0xA23545EBAED67F7BULL, 
            0x8414BA3C6E1FDF7CULL, 0x874E418577874813ULL, 0x6BACB104E31C2926ULL, 0xCEC6FA624DD32C9AULL
        },
        {
            0xF4FAC9CD8CE1295CULL, 0x26A5DE32C4538D55ULL, 0x8F9361864E7C9E9AULL, 0x0C72FA234736E4BBULL, 
            0x6170C3D6E07CC829ULL, 0xDAE18F222BCA88B7ULL, 0xE5A102E7F595647FULL, 0xB3C993DFA6F4E431ULL, 
            0x709BB3D0998E2B67ULL, 0x9B9DD647E9A1903BULL, 0xC7EFE7D1A1CC4050ULL, 0x2F7B1483C9CBFA78ULL, 
            0x0CBCD625BC4004A7ULL, 0xBFF3EA193BF888D3ULL, 0xDBD997CAEB489746ULL, 0x36376678F135DA33ULL, 
            0xB75BCCD565B5294DULL, 0x60BDD483F866A68CULL, 0x6AED489220AD9EB4ULL, 0x271E7F39CAD76EB0ULL, 
            0x01EED8148286F3EEULL, 0x6E3BFF5720C84C4DULL, 0x965541E26888B8C3ULL, 0x8B17021877FBB53AULL, 
            0x2879FD674852D892ULL, 0x639FD471589BDCA0ULL, 0xEFF2B169381B57F8ULL, 0x29A31AC2B823BDF2ULL, 
            0x2842C4C1379DA747ULL, 0x8FA7032FE9543A56ULL, 0x92FF7C8221605C64ULL, 0xE8BBFFCE06EC8595ULL
        },
        {
            0xAE7F7D67654008CAULL, 0xE08A4A265CA25B80ULL, 0xCA7DD3A9869F5C56ULL, 0x12C78C8A7068A5A1ULL, 
            0x5E6C25DAFCB29F15ULL, 0xBBAC9E524A5601D9ULL, 0xD7D409F3C3A73848ULL, 0x06BCC280DE6B5580ULL, 
            0xC76C964D7F32C61BULL, 0xD4B2225D3898228AULL, 0x737731B47361DE26ULL, 0x35C3A7EE3A40393EULL, 
            0x67B48A2CAC4345F5ULL, 0x6053839F9F15C482ULL, 0x115BF8B2E88E29B5ULL, 0xFE5C180BC313CC79ULL, 
            0xA510BC8C412A3764ULL, 0xD07D662432F24F21ULL, 0x4CE1A76B4106B09CULL, 0xAAC4646D626E19B7ULL, 
            0x015A9D8DD70421ACULL, 0xDE1A91EA1DD8590BULL, 0xA16A720DCCC8FA0DULL, 0x21DCB134E5F722E3ULL, 
            0x859C5FB75D97F541ULL, 0xE705F49494011CBFULL, 0x65A7D708E3169985ULL, 0xC81B3BE30B4A0AE8ULL, 
            0x15BCC19E7A8847E3ULL, 0x4DD57773A6EBBA04ULL, 0xA2692ACA280AC29EULL, 0x3EBF5B5F56911425ULL
        },
        {
            0x58D7B7F0EAB77C2CULL, 0x2BAD9358597893D9ULL, 0x626A259FFCA54460ULL, 0x875025755677DB7BULL, 
            0x0BA11587E629715FULL, 0x815A85EF28F0058AULL, 0x28C85EABEC0D6D3AULL, 0x0841ADC5711F3394ULL, 
            0x4CF57BCF1663080FULL, 0x1AFD64C71D8C0A7BULL, 0x6B2BA8227CC8C093ULL, 0xCD0ED93713A64FB6ULL, 
            0x25D1BB8F4BC389C6ULL, 0x2696FC97595F2188ULL, 0x370B87501A254B95ULL, 0xEF140368BD800806ULL, 
            0x2D6CE9ABE19834DAULL, 0xDE2AC4825AD06172ULL, 0xE58BB6445DE3F9C4ULL, 0xC9827069DF636074ULL, 
            0x687FEDB5FF1BDE4CULL, 0x1C8B38A465A370EFULL, 0x87660ED9E08ADBFAULL, 0x317A218C09A719A0ULL, 
            0x76F377883AAA9959ULL, 0xEB58EB2069AAD9E4ULL, 0x4087FFC2BC7BDB85ULL, 0xA204474D94A4A1B6ULL, 
            0xD1747B25DD418CD6ULL, 0xE1B61C71CA622AFAULL, 0x391616341D9321FCULL, 0x58BDBF7B6E31FB09ULL
        }
    },
    {
        {
            0x4A6031048C8AE147ULL, 0xA5D58FED59A4D8DDULL, 0x4F71723C010637C6ULL, 0x8AC6CB49ABB65B03ULL, 
            0x2B82E4C13CE074F8ULL, 0x85AE12EB81F214BBULL, 0x52CD833281ADE335ULL, 0x18B2FA20A7896364ULL, 
            0x78A34A779FB664C1ULL, 0x66CAD0B0703DE000ULL, 0x405ECCDA0640AF38ULL, 0xAD5DCF1B43729B53ULL, 
            0x35F3DDB71834B8B7ULL, 0x68A58C2A7EA5E858ULL, 0xE42F0FC532CADF82ULL, 0x65D89B3DD37602FBULL, 
            0x39B857F59725D0B2ULL, 0x1C846FAD20F0D77AULL, 0xFEF668B5BDDE7228ULL, 0x40CB1A58B88F455EULL, 
            0xAA4870BA1DDA0F39ULL, 0xAE18864F5DCA583EULL, 0xAA5D4075B3339CEEULL, 0xA2702BF0D064DE1BULL, 
            0x6E02FDD892DAB74EULL, 0xE16653235DB12DAFULL, 0x5AC1DE3F5DDF199BULL, 0x8A95232E6A42373DULL, 
            0xB1EC122810AE6439ULL, 0xDEF5A3F4C2580408ULL, 0x0DB22B171D72C84EULL, 0x6264D5277378DD87ULL
        },
        {
            0xD7937BA393FD0AA2ULL, 0x8B418A85A953FC8CULL, 0xF4C025C6D7A05F5DULL, 0xFCECC93B415ABD1DULL, 
            0x216B5DDB28ABCF23ULL, 0xAAF2CAB4FBA0DC4AULL, 0xE9900074D1662095ULL, 0x89932B45933C2BFAULL, 
            0x8FCD98228A3A83CBULL, 0xABE5E1CABC0BBFB1ULL, 0x1C722D9BE97237EAULL, 0x4E9791081D6B44F4ULL, 
            0xCCAAC9A51F9B98BEULL, 0x5C4535D3C16C185AULL, 0x885A86E58EBD6BC9ULL, 0xDD944A4BAB321630ULL, 
            0x87C244AFF6D11695ULL, 0x1B8F8A35E9AE2E5CULL, 0x0095237CC39ADA7BULL, 0x0378CE08A2327946ULL, 
            0x994A60855690964AULL, 0x1A07CBF7D84674C4ULL, 0xAE4D9147A993968DULL, 0x0B242C4882A036B4ULL, 
            0x1ECCE2233FD91E15ULL, 0x902F96BDB6735868ULL, 0xEBCCA6FA13661CBCULL, 0x5CB0720705CD19F2ULL, 
            0xC10492A2093A90F8ULL, 0xBC483456B2635F17ULL, 0x860944184E836DE8ULL, 0x29CB8888A506D6B4ULL
        },
        {
            0xBBD6FC919759DDA2ULL, 0xC2B48749F0A9E6D4ULL, 0x5EB03398A5051ADDULL, 0x365A0F9581FE2258ULL, 
            0x8990647D2F22981AULL, 0x9A0C2A6940CF124AULL, 0xFD9CB2C46AA28FFCULL, 0x095FAEE696CFF790ULL, 
            0x49E5D765FCEFC400ULL, 0x7E1948ECE577000FULL, 0x775CFF71AB452B69ULL, 0xC6FC0B427FEB9F52ULL, 
            0xFCF081A8037F4638ULL, 0x045D6FFFB6D335ADULL, 0x92EA6A7941C8B650ULL, 0xA5F7BE3A4ABCB149ULL, 
            0x38FBBA6FCFC74829ULL, 0x4795FD85270F1961ULL, 0x5B116A25F9A5E423ULL, 0xC21ADC27F1BFB097ULL, 
            0x16F7E33D74365C38ULL, 0xE5A532CAEFFA4142ULL, 0x6E8A984EF4F8C824ULL, 0x1016A77F6BF514EFULL, 
            0x1B339F88399EB46AULL, 0xD9942F669A87F0F6ULL, 0x3168B53C9B1883C0ULL, 0x9797DEE42A40F230ULL, 
            0x6083247F441002BCULL, 0xDAB91850F869CFC3ULL, 0xB6F2E8ED121D6781ULL, 0x44CBBD0739BE2E6AULL
        },
        {
            0x32F2AD5FA1ABCE66ULL, 0xB4DA0B01C7E89D4CULL, 0xA6378879DD06707EULL, 0xC3ED358918357C1FULL, 
            0xF82E3D50CDF2B76DULL, 0x5BE65DCC26E229EDULL, 0x38D22C3831E7D8DEULL, 0x677D726AC1498989ULL, 
            0x405B4E4F2EEC2603ULL, 0x24F7893C69588697ULL, 0x8027FEB10DB6B1BCULL, 0x956C7B06C8027E96ULL, 
            0xBAEFB52546948906ULL, 0xBFE29B7F1E57DB02ULL, 0x36BEE0378D197274ULL, 0x05240533BAE4A21EULL, 
            0xE7390E7FBC2DC242ULL, 0x64E185BF114C4A24ULL, 0x417541D7B028BCF7ULL, 0x1F920146CB7734F4ULL, 
            0x25E1539CB3C32DB7ULL, 0x92C9E4A2D544CBAFULL, 0xF2DB2EE73F3CD92DULL, 0xA3274FB22667D4CAULL, 
            0xD64FAFA025E0A49DULL, 0x102F7BC76B4DF8BEULL, 0x6FC310AF5EE6D7D6ULL, 0xF38D3A688E2A8EC6ULL, 
            0x00EE25EF6742DB13ULL, 0xF74A3DD5BCE502E6ULL, 0x22082C2BDD33551BULL, 0x0CE0409B4AB7D97AULL
        },
        {
            0x86E94379787E2A2EULL, 0x1E958C1F465B21EDULL, 0xC0DC31D393547A25ULL, 0x2532591A9E744871ULL, 
            0x18EE99E207A721D8ULL, 0x827CA524811CAFF2ULL, 0x0E2030BFFBA52CFAULL, 0x76E9D3F3FB6C6C60ULL, 
            0xDD674D2C956756D3ULL, 0xC8C53AD18A0B1294ULL, 0x92CD29D099617E88ULL, 0x89DB680DB9D34DA7ULL, 
            0x8F2AF0FCABA73B59ULL, 0xA315CEE6EAB54970ULL, 0x24953228B12CA598ULL, 0x8150F32DA8CB65EFULL, 
            0xD09CF7EB598E6221ULL, 0x85D444F3051C023FULL, 0x5BD9745A8F08B27CULL, 0xCCF5DB5936AFF7FEULL, 
            0xB5B8D63C53E48FC5ULL, 0x839A657B93CDDDABULL, 0x8BF83DF9A7773FEDULL, 0xEB3A66902247BBF3ULL, 
            0x781BCC77B9F6227FULL, 0x507575A1582654C6ULL, 0x52A68BEE86C52044ULL, 0xC431C032AFE0AE65ULL, 
            0x1F2B1627A9FEE964ULL, 0xB9014856BE867A28ULL, 0x65D546B903A16BFBULL, 0x7708FF4A88A90C58ULL
        },
        {
            0xBA050A5C3375288CULL, 0x30D0AC289C97BD9EULL, 0xF9488EF03A3D5D67ULL, 0xDD3607D1D843A98AULL, 
            0xDF4754D00C107459ULL, 0x38C0727E07B53C21ULL, 0x659F8CA42DB33C87ULL, 0x9B5DABF802702FB6ULL, 
            0x98F70FA5E0E74DE3ULL, 0x31E65DC831D1FB61ULL, 0x32ACD48323C4434FULL, 0x5CD1C122A017515FULL, 
            0x7D2F6097CA603360ULL, 0x5A19EE86225A13ECULL, 0xED926CB4C0F458DFULL, 0x60C6A8AAA1F33AFBULL, 
            0xE7B4E3EE71077AA2ULL, 0x1F6BEE2AA813FCA0ULL, 0x131FED1AB30773F2ULL, 0xAAB0BCA17D04917DULL, 
            0x23A10A503263B824ULL, 0xAB11BA1BA3F04365ULL, 0x54509D6BDAD66C4EULL, 0x3711AAC5383002E4ULL, 
            0x6A7C98905A314CA2ULL, 0x40CAB1B969D7B989ULL, 0x66EBBFC4122DE46BULL, 0xF5ACB8B975754E4FULL, 
            0xF0910C4DAF9A1190ULL, 0x003BD9D074991CA9ULL, 0x2E946B3D26344750ULL, 0x65952319F4471B84ULL
        }
    },
    {
        {
            0x918767CBC00C7D9EULL, 0xD97231EB20975B9BULL, 0x9745C82510618E43ULL, 0x037F36148E706944ULL, 
            0x5995C2FC845C18EEULL, 0xF51490115620679EULL, 0x6E6EA401C4643AEEULL, 0xECC014DCFB6B536FULL, 
            0x3AACB3F9A3A5EA57ULL, 0xD18F3BA4846A3CA4ULL, 0xB25DB7294C4742E0ULL, 0x65BFA73A02B2A95FULL, 
            0x22EA6ED611F2197EULL, 0x9A8A9ADD56EF8576ULL, 0xBCC1269E831CDC69ULL, 0x4DECDB4F3870442CULL, 
            0x7FE3A7EA1A396C5EULL, 0xEDEC5212B7CE4734ULL, 0x7D66B70F307106A5ULL, 0xDBAA6590510D2A04ULL, 
            0x95322E32E659B3F8ULL, 0x547953468B139614ULL, 0xD92826FC4BB0BE7BULL, 0x41EDC44B0CFE71E0ULL, 
            0x6DA4CB047F2D7D6AULL, 0xB2CE1B63C7F9AAA8ULL, 0x79A123E09ED25DE5ULL, 0xEF1559E09B1D14A9ULL, 
            0x9C363207495E1FC9ULL, 0x06262A7CD3B2720FULL, 0x50294119EE2A3C4EULL, 0x9A82AEEC0578304CULL
        },
        {
            0x138159524B7DDAC8ULL, 0xE153D028038DE579ULL, 0x2D6A5A41885883F2ULL, 0x8614E2E55EAA4E7CULL, 
            0xDB94F22D0B6B5178ULL, 0x27FD5B15CE047E02ULL, 0x8C662A49D490B68DULL, 0x6F006FEE104B2D9EULL, 
            0xF341AE2B38791358ULL, 0xB5C49ADA9823A1BAULL, 0x57083ACD6C0689CEULL, 0xE7BABD728912429DULL, 
            0x82A36C982444D19DULL, 0xA5324380FE37A9ECULL, 0x36A930029C4460D5ULL, 0xD396699F5D8585FCULL, 
            0xC15DC22956EC66E1ULL, 0xE6A47FF6718E5C4DULL, 0x713B1616161E6D11ULL, 0xDDCDAF947FDAFF98ULL, 
            0x77A5DE21D7B4E85EULL, 0xFDC6C9E3999F14BDULL, 0x5AD6CF31256D61EBULL, 0x2B01FB202A0180E2ULL, 
            0x47E7FA9961B90E1CULL, 0x57B077783C465594ULL, 0x97B80A58E092692CULL, 0xACA5BDEF7B2465CCULL, 
            0x39DC457D9875878EULL, 0xBDC62598FEAAE16FULL, 0xEF5E6D3B6891778DULL, 0xFF0B9410FCED2C5CULL
        },
        {
            0xE061BCE273790D51ULL, 0x1C752C21CF10835AULL, 0x4196AE18018613B4ULL, 0x66B7DA59E2F43102ULL, 
            0x45B490C7AC000E9BULL, 0xA9487322566F87A8ULL, 0x8B59003488D93341ULL, 0xC600B008C679C01CULL, 
            0x940D72B79D37A810ULL, 0xA6615113D1FB269DULL, 0x4883C4D55148C1D5ULL, 0xB9EFB935AB9FB037ULL, 
            0x6BE18A81B4898156ULL, 0xC56F52D0C734D5EEULL, 0x99F0014E93C0B544ULL, 0x645C913A1D9CCEECULL, 
            0x69D932B7C60DC01AULL, 0x49ACEF66B4C3AA1FULL, 0x2187F4B0E8E13AA7ULL, 0x22103565A7F80B41ULL, 
            0x67702C3F19A2A295ULL, 0xE0BF5963FF5459F2ULL, 0xC0BF9B384B0CFED3ULL, 0xAF585B49A1DF3CE8ULL, 
            0x8E397D1E87C4B5B6ULL, 0xDECB28C83E24B4D9ULL, 0x1E031D2759814827ULL, 0x29F30E057A50CEA0ULL, 
            0x29494EB34522FE52ULL, 0x30EA7A04BEF1D478ULL, 0x075A46DDC6FECE3DULL, 0x034FA54722BD0562ULL
        },
        {
            0xF933F95208640F89ULL, 0xEDF0708D9BC90291ULL, 0x39B1428076697A87ULL, 0xEAA3FD6E1FBAE5D9ULL, 
            0xB4F41176DCB47F6AULL, 0xBB4E091A7B01C5A0ULL, 0x7052ED4EA054C911ULL, 0xB8FC6CE2D83A982FULL, 
            0x8FCD3C2A5A94F5CEULL, 0xF8B2BE33C2EF61DDULL, 0xFA52AA17EACE5E25ULL, 0xCB23FFD4F1607C02ULL, 
            0x42E85E453F931A04ULL, 0xC13AD508DD88FFDDULL, 0xB050AFD9CAF909DCULL, 0x58DF91802A4FA5F5ULL, 
            0xB3ADA0E0172D4AE0ULL, 0x548B28025E527AD4ULL, 0x5636422BB0F077CFULL, 0x55B807BDEDA3F820ULL, 
            0xFD94B81A0D1DED78ULL, 0x01239B99C1537BE5ULL, 0x67C83E00C0E6389CULL, 0x10052C2D51C855C2ULL, 
            0x865CB108FB4BBF8EULL, 0xBDA8FA61D9FC25F8ULL, 0xEAF9ED264DF64DE7ULL, 0x42B9CEAD220E7A7BULL, 
            0x1F0F5319E31E0ED3ULL, 0x8485CD953E6DAE20ULL, 0x9348C3520DBA4A14ULL, 0xAB6B5B536532E69CULL
        },
        {
            0xF4E92BA287E0ECA5ULL, 0x19D2BAEC19B61555ULL, 0xA5CC462902DAAEAFULL, 0x70276FBD2864412BULL, 
            0x3F090FD805E5B4A6ULL, 0x629836EAAF98F539ULL, 0x30FB2F010917F099ULL, 0x0E4E105B439FDD7CULL, 
            0xD33FAED8E5C0E4A2ULL, 0x1E2AF602754E0384ULL, 0x7D3B57321A673FE2ULL, 0xCEEA8DF563CAB373ULL, 
            0xD8CDB0F3882657F5ULL, 0xF082A08F25C3CFA7ULL, 0x4B6EC4EC5D8AEACCULL, 0xD21B1395BEEFEA54ULL, 
            0xE1E783C68C164DDCULL, 0x2B78912A843C2139ULL, 0xAEF1149F1A50BB4DULL, 0xC578DD18ADBE067FULL, 
            0xD710D32BD0FF06D5ULL, 0xF67AB37B25A380CCULL, 0x35515E21DA1814C2ULL, 0x5B764DA833AFACDDULL, 
            0xF7D91F3792C15FDAULL, 0x4BB1D0D50757B81EULL, 0xB6FAE5FAA8F68790ULL, 0x43D0A916AE1A891FULL, 
            0x8AD1C39ABC544A3CULL, 0xC639B0FACD9ECA45ULL, 0x88525349712F2A5CULL, 0x0D85A352BBB6C0D8ULL
        },
        {
            0xBFD24AE421997E08ULL, 0xFD0925E6D2E2D2B3ULL, 0x891508AFA628125DULL, 0x5BBCA22BE12FC618ULL, 
            0xC0261E8706A6EF38ULL, 0xC7EECA55CB774ED9ULL, 0x68106DFA25C3CC80ULL, 0xF2BF3BD35229E744ULL, 
            0x6846A6E12ADEAE73ULL, 0x179378A7F8FC8AB9ULL, 0xD4FDAD7AAC3177A7ULL, 0x46FDD310C713D750ULL, 
            0xE01BDB749A1B22BDULL, 0x14448828CBF2093BULL, 0x57E9FCC6A3759089ULL, 0x45C07E14E68A7DE7ULL, 
            0xB2AA352AC8A1D74FULL, 0x6F650B1449593987ULL, 0x6778FB6154877061ULL, 0xF777F738DE5508ECULL, 
            0x867C1EF63B213055ULL, 0xDCB5DA5BB1EF59DBULL, 0x41F45E04A301A16FULL, 0xF34715A03F7DCA4CULL, 
            0x58FF162EB2B1C0D4ULL, 0x4710E484B3FB8810ULL, 0x0A06BC8F0C10FB09ULL, 0xE6931CE8B62D14FAULL, 
            0x7691246C4B9DF175ULL, 0x7847D79C8C6DE744ULL, 0x7CB75B97DC245BFDULL, 0x028F2A9DF897C168ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseGConstants = {
    0x1BD32F51D91F5A32ULL,
    0xD18E06DE31678DE3ULL,
    0x3009EF9636065ECFULL,
    0x1BD32F51D91F5A32ULL,
    0xD18E06DE31678DE3ULL,
    0x3009EF9636065ECFULL,
    0x50495DF456B502FAULL,
    0xFB02C1FC5344317EULL,
    0x1A,
    0xE8,
    0xEB,
    0x18,
    0x37,
    0x8F,
    0xA5,
    0xD6
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseHSalts = {
    {
        {
            0x6F6CD8D944D33882ULL, 0x171EF9CD4078C4F4ULL, 0x9A314AEAA40887D3ULL, 0xCF46CF3F8903E550ULL, 
            0x0AD965CAFF359FA0ULL, 0x59421F1CEC6CE30EULL, 0xB6CCCB35113981F9ULL, 0xFD6EFBD6A67A7959ULL, 
            0x16C4AE1B447B5149ULL, 0xC7E03AF7C0826962ULL, 0xD0CF932BB7B2FF3DULL, 0xD6B19AA16CE0F860ULL, 
            0xD33968D3D157DEDAULL, 0x7EFEE0A68936DB76ULL, 0x394E82394C36F3C6ULL, 0xF777B3D03E47C741ULL, 
            0x81823D47922C8756ULL, 0x17619227CD1414E9ULL, 0x32DF02F54EF38B11ULL, 0x286868AB8599429DULL, 
            0x1110B3F37DE6EEC0ULL, 0x04EE077C6A55D98CULL, 0x9B1B787513FAE365ULL, 0x5BCD6B4020A89A94ULL, 
            0x1B9CA8028A7DD950ULL, 0xFC1FBB157375386DULL, 0xB606800F8FD31E1FULL, 0x610F03CBB81424CFULL, 
            0x3D7BE260B682B397ULL, 0x85722F4A05AC3D82ULL, 0xB89ADE366A8CF305ULL, 0xEE4AD19161B4ADE7ULL
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
        },
        {
            0x0D3B80A9E16C53DBULL, 0x797846B824062194ULL, 0x5970F0D877EDF5B6ULL, 0x665D970E34DA7F54ULL, 
            0x478EDEB165807B96ULL, 0x22FCD8C060E43E84ULL, 0x398EE5A4AE081D3BULL, 0xB5C00666D82E948DULL, 
            0x7A18FCFFEF5BCA00ULL, 0xD84D4BB8038D9F36ULL, 0x24B89B9665460DD7ULL, 0x34DE720EF3091558ULL, 
            0x2190917C94945E29ULL, 0x177FBBB80B03F5D0ULL, 0x30F295A3004D096BULL, 0x1E2C98D6566993C2ULL, 
            0xE8D32504BF42B004ULL, 0x85EEFE365B37D41DULL, 0xC6190925C060E5D4ULL, 0x61F8943EFDDAFF8EULL, 
            0x8B7EC8608BEAB08FULL, 0xECD8EF63B933FFB0ULL, 0xF151049D80153AAAULL, 0x56BBCA316253FA20ULL, 
            0xF9C9D60FD15B5370ULL, 0x9C669C5DA7C5FF2EULL, 0xB2C389B02B939CE6ULL, 0x26AFC29969CC444CULL, 
            0xD31F5A1D917B08ECULL, 0xAF2B3E6F6CF2FD33ULL, 0xB47877DAA5B3F602ULL, 0xE9CB9E9ED9086A53ULL
        },
        {
            0xBC8CCDC410D23786ULL, 0x1992899C3FA08C55ULL, 0x00CA0EE31DB8CC40ULL, 0x475451FE44295AD7ULL, 
            0xCED3BD8F3A90F226ULL, 0xC2FCADCD61E68A2CULL, 0xBBDD3478FE5E1BB0ULL, 0xB4A4FB23AF29A7D9ULL, 
            0xCA7AF043D9860A9AULL, 0x38ACD337A861D7A7ULL, 0x00807A3F4ACCDD96ULL, 0x89B00B9F17BEDA9EULL, 
            0x00E3FA5778C67FDAULL, 0x2C994E9CF93E9D55ULL, 0x0502AC2E01A8D432ULL, 0x30BE26B94E8A980DULL, 
            0x72F2562455C30B51ULL, 0xDE6690B9E57AF43FULL, 0xA0ACD6A933F5AC41ULL, 0x760B5A4A4C8ABFEFULL, 
            0xDD287199355C773AULL, 0x7EA16B1981B9DAA5ULL, 0x2AF6B054E8E98228ULL, 0x7623BB9A7904F227ULL, 
            0xE8783957D992B749ULL, 0x99DAC3BDA33819E3ULL, 0x4D8C68208BF67A0EULL, 0x1DEB529E803FAE24ULL, 
            0x55CAE38AE6A9B809ULL, 0xFBC5391E1D18990CULL, 0x0653D0AE3DB26433ULL, 0xE68FFEDB7B6404D6ULL
        },
        {
            0x4565D44ABE4B1774ULL, 0x9AE3690C07AE7EDCULL, 0xF6D72F9F8F150522ULL, 0xDC047D87F22AAC45ULL, 
            0x2AC38DA96B9BDE60ULL, 0xCA0C2CC1BBD864A8ULL, 0x7474EA444EABC5D5ULL, 0x565DC9826BFBAF89ULL, 
            0xE0AA5EB3832BF53DULL, 0x818739859D99DA7EULL, 0xC18D70DE4DC54E02ULL, 0x035D0340DC3B0315ULL, 
            0x9410AD94963916A6ULL, 0x79F8A6B220A20BFFULL, 0x0824358142553751ULL, 0x215D5D0E9D9E56D5ULL, 
            0x79BD8A538A2BA020ULL, 0xE5565C4B8260A32CULL, 0xD4F92BD7CEEEDF9FULL, 0xE091AEF30E62675CULL, 
            0x46113D904E44D288ULL, 0xC93F6DE8240BA5F0ULL, 0x2B31AB75303F694AULL, 0x47CC171EC87CC88EULL, 
            0xC3D7FEC0F8AACE87ULL, 0x5C0627779667E895ULL, 0xD44E0B10660046CCULL, 0x5159CDB65FB73687ULL, 
            0x7187ED005B9FCF66ULL, 0xDF2D695B172A5415ULL, 0x481D5D27936462D6ULL, 0x401F8743E55A077FULL
        },
        {
            0xE766877CBDB014DDULL, 0xF258FAAB603E01EFULL, 0x6C999C4A11196D8EULL, 0xD283C4BFDFE66C2DULL, 
            0x7EEBE72C82BF9BAAULL, 0x7224C5BE188BF82BULL, 0xEE1684950D7560F6ULL, 0xE93018B401A85776ULL, 
            0xCFF35E96C883C9CAULL, 0xAA1C7670EDACD337ULL, 0x94F3137AFB8E0B87ULL, 0x6CF7F25F59F6A7D3ULL, 
            0x393DD17D80AF1B67ULL, 0xC09DDDF21A33307DULL, 0x15E181B9E673DEFCULL, 0x4D325A884F13CAA4ULL, 
            0x4C25C70D237673E9ULL, 0x08C88FFB2C6796C1ULL, 0x3145DD6760FE148EULL, 0x03CE86738AF394BFULL, 
            0x68CA9779C99178F2ULL, 0xBE2D88283A1F15FBULL, 0x1492B13896949A93ULL, 0x400A357AB849A9DFULL, 
            0x6C01DCC0372F0037ULL, 0x945B602368D90CCBULL, 0x0610DB8AD8C35251ULL, 0x61F36565A0E1EC36ULL, 
            0x6347EB34636DF252ULL, 0x6A8371205AA202C2ULL, 0x088E042F3EB5F59CULL, 0xCD03DC88A3886AE4ULL
        }
    },
    {
        {
            0x8D9E880374E8E910ULL, 0x9DC2B16B84C38883ULL, 0xF7FBC979159224D5ULL, 0xFC3FD10C49D79526ULL, 
            0x9DA38D6CBFC7628AULL, 0x241F6AA5BDD5940BULL, 0x404239FFB01B0B2CULL, 0xE056B4A709956749ULL, 
            0xD2A15849619E00C1ULL, 0xEC106CACAC8AC790ULL, 0x2F7F43673CFF16EBULL, 0x4752E9F3B77537C2ULL, 
            0xD7EB0FD58E12A405ULL, 0x54DE22EEDD93826DULL, 0xD1B5C7CFB2A8AA48ULL, 0x3B9420E8A2A93986ULL, 
            0xEABB64DECF1E0D8AULL, 0x25A836140B564920ULL, 0x46DE5DFF560679C7ULL, 0x255A96975D0D24B6ULL, 
            0xFC840D25245733FAULL, 0xFF879736477F7A59ULL, 0x36D003938CE82F7FULL, 0xB3CCAA0DA7C1A3F8ULL, 
            0x3545B7FAB7A8D309ULL, 0x3FB674F57CA312BBULL, 0x20091D5E670CE059ULL, 0x47006B02747EF183ULL, 
            0xC04F4DA0567E2DF9ULL, 0x200A42D03CF67E5BULL, 0x955BEE02042EA335ULL, 0x5B835664219621ADULL
        },
        {
            0xD601513D41E635E2ULL, 0x8FDA771A0C4AAC36ULL, 0x525EECE510C2ED2DULL, 0x506480E470BD6416ULL, 
            0x34140EC9E9EA1234ULL, 0xC6A2B89E552B697DULL, 0x6E2D98018A04FC8CULL, 0xF2487324838182F7ULL, 
            0x39DA2910A2CF0E38ULL, 0x3B3202540EFE9AC6ULL, 0xA087C06A68C5800CULL, 0x3017CF4A31F35ABAULL, 
            0xF96B00729CA3D810ULL, 0xDBC475E9C9290124ULL, 0x615814D4AD348D56ULL, 0x1B57F91A9D3C629FULL, 
            0xBC79F93A0B336304ULL, 0xB976FEB7710AB0EAULL, 0xA30383891E174C20ULL, 0xE15F18E2F9198ABBULL, 
            0x01CA649C67178695ULL, 0x7058397F874D279AULL, 0xA0C566F8B2AA47F6ULL, 0xD38D3E2FD300DBF1ULL, 
            0x09370FBA1651F4F3ULL, 0x8BFB22E22618D493ULL, 0x095219199FE21A97ULL, 0x0922FEDEEF5CBC01ULL, 
            0x7A3039437718FAB2ULL, 0x65FB6E8283D50BDEULL, 0x7045C46BFE8302F3ULL, 0x0BFB6C4D2268DD9AULL
        },
        {
            0x7C611B1BCE54A98DULL, 0xA385472EFB220879ULL, 0xE23F70D88368E51CULL, 0xD927FA57F3AB49A1ULL, 
            0x1515D0B2F03E1948ULL, 0xC6C9F1D5C0BAE9AEULL, 0x27DBA3151C7F5BC3ULL, 0x7DDF3FB5976C55D1ULL, 
            0xFFF2DAFA3AEFDDA4ULL, 0x630E309B9B717CC5ULL, 0xD943FAE09168CCCDULL, 0x4E7647F801CE2020ULL, 
            0xF332E2D5FA1CE0C3ULL, 0xFE402AA30ED74FA5ULL, 0x014A1A7009F0FC7DULL, 0x926261A77271CC48ULL, 
            0x9967D4970E28B74FULL, 0x9CB8D45E2035F1DAULL, 0xF80340A96E7128F7ULL, 0x72702BE7AD3B1236ULL, 
            0x250360E11256472AULL, 0xB857E9C06726501EULL, 0x324BFB2CCBFC7B68ULL, 0x50A449CBB921487EULL, 
            0x7A0461C4F4D56F45ULL, 0xA48064C0D06F4BF5ULL, 0xA53479CB0E10F3DBULL, 0xE0E13D0B2E2BCD34ULL, 
            0x09F80E9C266183F5ULL, 0x35B1BFD8574B946CULL, 0x744C10B576311566ULL, 0xAC870A88407AF873ULL
        },
        {
            0x4592CA68DBA87D6AULL, 0x7E0CA2D107CEE2B6ULL, 0x17C383F70ECDB412ULL, 0xD2974517BF66B30DULL, 
            0xA124CE1131007DB9ULL, 0xEF99B907501AF5FEULL, 0xB665106181271DECULL, 0x396139A0F104461EULL, 
            0xBEB3CE8ACD16FF46ULL, 0x8838205475643E07ULL, 0x1C4EB785ECAE7223ULL, 0x0E7EDA86573CA41BULL, 
            0xFE706DEDE297F852ULL, 0x0C78BAE0625848E9ULL, 0x95DCE55D841611EBULL, 0x2A958454F5FBB84AULL, 
            0x013A33DD13C9BC15ULL, 0x5D958327A3C47409ULL, 0xC79DDDC09792EB60ULL, 0xC244525E9608FA52ULL, 
            0x6A225595EE98EDFDULL, 0x483EF00B1D007DD5ULL, 0xBF5FCA1BACF173A0ULL, 0xE3C0E916439543DCULL, 
            0xD94A83780578B57FULL, 0xA36497DB18F349C7ULL, 0x724C98E89009FAD8ULL, 0x25CD3C00A6C4645CULL, 
            0x216D96A14D1FF914ULL, 0x0CF49879D1572260ULL, 0x6B97977D007669E6ULL, 0xB4BDE1C0D57959CEULL
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
            0x795D9B5BDCBE1693ULL, 0x974AD334FF9B3A0BULL, 0xDF330D3B0C9BB700ULL, 0xDE7CA98590D36810ULL, 
            0xE87A8B1EA8FDE26DULL, 0xA457A3F0EA2B505DULL, 0x9FF94F77627644B2ULL, 0x5589A1A92D5E1EB4ULL, 
            0x46EDF0A14679E2FBULL, 0x8F82077557E0824FULL, 0x0F126D575F220489ULL, 0xFCFA8A577BAED91FULL, 
            0x0B79A4F836337BFDULL, 0x318631E9FEF3BC8BULL, 0xF9133A822184D986ULL, 0xE5F979D51A584501ULL, 
            0x7B8CCCD95C06CC7DULL, 0xCA43DB4EE63ECAFBULL, 0x5D21B43087685219ULL, 0x36ADD704A40BF833ULL, 
            0x7A4A2627A83269C7ULL, 0x450384C5624AF324ULL, 0x45E316F752E46D18ULL, 0xA74FF6DECED863C1ULL, 
            0xFBF29D6E533B13B4ULL, 0x4A8AE4CC4AA6C422ULL, 0x14FFF44601B70AF5ULL, 0xFC78258D6BF764F1ULL, 
            0x4D597FB55B2A5463ULL, 0x7C631170B68E9C66ULL, 0x445287E4BC48ED32ULL, 0xB45D6925821B8746ULL
        }
    },
    {
        {
            0xF15FBA69F14FDA9AULL, 0xFAB5DD37DC1DB33FULL, 0xF99826F0FAFA178AULL, 0x86314BE2A06E09ACULL, 
            0xC3CF635C20330B37ULL, 0x9C4968113C85D066ULL, 0x4AF5588FE0C2009BULL, 0xD139AB43E7BD67F5ULL, 
            0xC409B314CD8262E0ULL, 0x24C9C91D32FD7020ULL, 0xDEACAFADD006876BULL, 0x6C449AF3735E4F2DULL, 
            0xABA755E01AC91B48ULL, 0x74169246BBD78D2DULL, 0xAFA3FAACEB1C368CULL, 0x5CF497F7B5C6B06AULL, 
            0x35B8D05CD7AC46D7ULL, 0x33310F5EBD533D65ULL, 0x13FBF85D6740EF4CULL, 0xC672DE89D02D8419ULL, 
            0xD2318B243AA2FCE3ULL, 0x5F6971DB9C66C02EULL, 0xE294AB287818F5A4ULL, 0x8FC6E728908DEA5CULL, 
            0x672C2CC6A54A8AE2ULL, 0x3145C05ED3A8F358ULL, 0x09097CD736BA836BULL, 0xD5B1308C4B6CA030ULL, 
            0x3D7697017ECF3127ULL, 0x0134798D6E63DB97ULL, 0xABE904186663E65FULL, 0xCDC3A98AECF9A171ULL
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
            0x3DE6E54446AB3CFEULL, 0x47CB9DE12D094809ULL, 0x3D9F91D3B2FCC3B6ULL, 0xFD5DFD2B08DA1E58ULL, 
            0x076FE8A954623F34ULL, 0x554D92896EAF9E27ULL, 0x149419EB9D72D10DULL, 0x63D66E1733C9F3ACULL, 
            0x39E80BCA93CDCDC1ULL, 0xA62FABAF5A7DA51DULL, 0x4F895A6C667775F6ULL, 0x299F1BFE77FDB939ULL, 
            0x3DB611AD06383701ULL, 0x3CC587E4BFD1EA3AULL, 0x310951FA251A5975ULL, 0x4FACF791DFBA2E76ULL, 
            0x53D0CAAF3260280BULL, 0x8185FF0BAA097A50ULL, 0x39A642D6A3CD980AULL, 0xC93736A52B573AF0ULL, 
            0xD4DC315130939DDEULL, 0x608D44B6DC213072ULL, 0xA4469A0943081404ULL, 0x7114E0AB6178022EULL, 
            0x16FDE0410A1C7B26ULL, 0x8E802E1FE7D330E0ULL, 0xFB180263CD6FC295ULL, 0xBF4A360B45131D57ULL, 
            0x679045503C0FBC81ULL, 0x11C8D051571B5F5BULL, 0x4B432493FFB1B18CULL, 0x4F532A8B813E28DEULL
        },
        {
            0x8F93CCB8FC42F2A2ULL, 0xC803CA08BB150ADDULL, 0xB7AE65118E102176ULL, 0x58487A71028C6141ULL, 
            0x6B0C68AA1A488FC2ULL, 0x8C422586C6AFDADBULL, 0x6362A1A00E3AD0E2ULL, 0xC5441FA6ABB5E53FULL, 
            0x081284DD6821C5BDULL, 0xCC9CB0683FBC5F30ULL, 0xD9BDD937726C831FULL, 0x19384E05C316EA81ULL, 
            0x630CE0A0D500B0B4ULL, 0x5DDEDE86AE23A7F8ULL, 0x1E590760C4AD84DFULL, 0xEDAEA8F79A6B33FCULL, 
            0xC4418B4B9362741AULL, 0xFF86CADDC4C82B8BULL, 0x696B47729099BD76ULL, 0xBC44B2E4E3EA8498ULL, 
            0x2EA20C9057359FBFULL, 0x2E55D4BFF01A9E18ULL, 0x6AA6C3595D225DACULL, 0xBAEA3CD010AA93A2ULL, 
            0xBF01060B937E86B9ULL, 0xBC8621F5F808979DULL, 0xBA41FB5F7B7232A0ULL, 0x8DA2D5C87FC3CADBULL, 
            0xE204F84040116ECAULL, 0xD0B490FCC61B60D9ULL, 0xA3870C7CECF896BAULL, 0x15135D9240B880DAULL
        },
        {
            0x211AFDFF20B0AFBBULL, 0x6229138C5856754EULL, 0x636C3C901510758EULL, 0xB99887B9AF151EFDULL, 
            0xBF15BA141F698DAAULL, 0x830BD7E845F0BFF7ULL, 0xC6684078F0494857ULL, 0x33DE0E6628E1792CULL, 
            0xABF9DA958C3B5B3BULL, 0x10E688B3F91F52CAULL, 0x1A314E87C640E39EULL, 0x2AAAB402B325C23DULL, 
            0x8FB54B30C293856FULL, 0x69289FEC58E88700ULL, 0xE577FAEEE42EC86DULL, 0xAC8A9984915833C0ULL, 
            0x68322DDEC6B9569FULL, 0x81051EAB7E0F53A8ULL, 0x6AE11942C388F2E9ULL, 0xD9AA4DD7D6FD30F4ULL, 
            0x159DAFE8F03E86D5ULL, 0x3D3AC99219AE5AB0ULL, 0x5B05FA9D047D6DBBULL, 0x2DA4341B647A480AULL, 
            0x1EAA0CF5C83A2A67ULL, 0x57B003965B3F7AB9ULL, 0xE214F2B9D2F8440BULL, 0x9438A68891291E9DULL, 
            0xBA0852DB6CCD8659ULL, 0xD6CE5EA15302A4FBULL, 0xA56C555121F924F0ULL, 0xA7C00EC962EBDC75ULL
        },
        {
            0x399C44E710CC7EC3ULL, 0xF5749D3337AAC23FULL, 0xD70CDFD1A752A68DULL, 0xCB36FBE65D26EF98ULL, 
            0x01B708BE7B8F32BAULL, 0xA9CF7D784055B001ULL, 0x46E9BBDC3490FF09ULL, 0x3C88A868B4E14982ULL, 
            0x26204854EA3FBDE3ULL, 0xF0EB3F0FBC0E3FF2ULL, 0xFDDDE4E0107E3A9FULL, 0xC5D37493F4229C10ULL, 
            0x579666ABDA646273ULL, 0xB63AA2A6AE80B41BULL, 0xDF360EECD709C7ECULL, 0xD18A810641C3098DULL, 
            0x86C7D03CC3DEE146ULL, 0xA08D199D11E24FD7ULL, 0xE9E001F789062774ULL, 0xD6CDA15B63133A00ULL, 
            0x4BBABA5206FC55B6ULL, 0xE7AB3987B06B4623ULL, 0x64ACB5F370E7C499ULL, 0xC2B89CACB56DA0CBULL, 
            0xDE6C718624570FD0ULL, 0xFBFD40DFB21A3A50ULL, 0x15F72ED9D575EA1EULL, 0x5A99E3AD33C3513FULL, 
            0xFF18D85240F6006CULL, 0x9FBF81022BC65B39ULL, 0xD0413F027B09BDF1ULL, 0x4FD7E2F533AFF9C7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseHConstants = {
    0x2D3CAFB65D0C27CEULL,
    0xBCA2E31E8735E54EULL,
    0xE3DCD56BB2078E39ULL,
    0x2D3CAFB65D0C27CEULL,
    0xBCA2E31E8735E54EULL,
    0xE3DCD56BB2078E39ULL,
    0xC769C675F1DD42BCULL,
    0x322D9510C886FBDFULL,
    0xAB,
    0x1E,
    0xC4,
    0xE3,
    0x38,
    0x16,
    0xB4,
    0xDC
};

