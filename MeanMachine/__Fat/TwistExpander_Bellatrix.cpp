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
    std::uint64_t aPrevious = 0xBCBC77F58D0729E5ULL; std::uint64_t aIngress = 0xF44B88D1C835AA04ULL; std::uint64_t aCarry = 0xAEBD2A68C4396772ULL;

    std::uint64_t aWandererA = 0x8684749735C67ED8ULL; std::uint64_t aWandererB = 0x8842C5B981C98835ULL; std::uint64_t aWandererC = 0xAFE0613E3D292FA2ULL; std::uint64_t aWandererD = 0x92574655ECACD680ULL;
    std::uint64_t aWandererE = 0xA6A07C28A90B2AFCULL; std::uint64_t aWandererF = 0xA2E073682C6A1E56ULL; std::uint64_t aWandererG = 0xE673B7E390493C29ULL; std::uint64_t aWandererH = 0xD5019DB541CD9B71ULL;
    std::uint64_t aWandererI = 0x80B0177D0E8231B0ULL; std::uint64_t aWandererJ = 0xEFE26E5EEA00D14EULL; std::uint64_t aWandererK = 0xBCB37D05193588F5ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13916588402450790323U;
        aCarry = 10833284826107823111U;
        aWandererA = 16176997900230206137U;
        aWandererB = 11301387398974294116U;
        aWandererC = 9546749335871507063U;
        aWandererD = 15504045161003017703U;
        aWandererE = 11156875549187125641U;
        aWandererF = 13935690786827397764U;
        aWandererG = 17804194337017002465U;
        aWandererH = 15084516068670794089U;
        aWandererI = 16330505179826925879U;
        aWandererJ = 13954851021649169437U;
        aWandererK = 16072519251659551469U;
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

    TwistExpander_Bellatrix_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Bellatrix_Arx::KDF_A_E(pWorkSpace,
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
    std::uint64_t aPrevious = 0xE413360888434E32ULL; std::uint64_t aIngress = 0x9E3669D8BA55A010ULL; std::uint64_t aCarry = 0xEDA202F64F5D7469ULL;

    std::uint64_t aWandererA = 0xC48F0F670BA4E282ULL; std::uint64_t aWandererB = 0xDFD74787B4237390ULL; std::uint64_t aWandererC = 0xD470DE34FC7CC064ULL; std::uint64_t aWandererD = 0xD23BDA8088442BCDULL;
    std::uint64_t aWandererE = 0x90106CCFDD9432C5ULL; std::uint64_t aWandererF = 0xD62A6A55263A22EAULL; std::uint64_t aWandererG = 0x9E0DB4D3A44EDDD3ULL; std::uint64_t aWandererH = 0xE2DF6FCF96926B49ULL;
    std::uint64_t aWandererI = 0xD065F3F13DA2BB74ULL; std::uint64_t aWandererJ = 0x9F2B1D1D2AEA4EFAULL; std::uint64_t aWandererK = 0xE68C7B1F84AD43C6ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10481730725968206531U;
        aCarry = 17423472806203335769U;
        aWandererA = 15738584427810794869U;
        aWandererB = 13105324691688023437U;
        aWandererC = 15995737475865548482U;
        aWandererD = 18191241559597669921U;
        aWandererE = 18429790821113876021U;
        aWandererF = 11590801296501056626U;
        aWandererG = 12069439558029036914U;
        aWandererH = 11620495037669424876U;
        aWandererI = 17297543206916605913U;
        aWandererJ = 18144487829320458460U;
        aWandererK = 12746328143568877339U;
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
    std::uint64_t aPrevious = 0x8F6A5ED4F596E56EULL;
    std::uint64_t aIngress = 0xB4B19AABC7B39E34ULL;
    std::uint64_t aCarry = 0xC0862D71073848F9ULL;

    std::uint64_t aWandererA = 0xEEECCE94BC175938ULL;
    std::uint64_t aWandererB = 0x877CFD222E785F49ULL;
    std::uint64_t aWandererC = 0x855768A0500AB554ULL;
    std::uint64_t aWandererD = 0xD68385414FDA03C4ULL;
    std::uint64_t aWandererE = 0x991D8F12C11CE7FDULL;
    std::uint64_t aWandererF = 0x94113DC6E1C19D69ULL;
    std::uint64_t aWandererG = 0xDD9F0FB7079F4680ULL;
    std::uint64_t aWandererH = 0xA2CAD90403DD2B15ULL;
    std::uint64_t aWandererI = 0xE754D99ABF0E02DFULL;
    std::uint64_t aWandererJ = 0xB6740606B73E8825ULL;
    std::uint64_t aWandererK = 0x9EEBF19A7403F999ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneB);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneC);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
        TwistSquash::SquashB(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    std::uint64_t aPrevious = 0xA955466510E6D4EFULL; std::uint64_t aIngress = 0xA148AE278E873AA5ULL; std::uint64_t aCarry = 0x8ABB4CE43F307A14ULL;

    std::uint64_t aWandererA = 0xADF5C9AAC7A77E93ULL; std::uint64_t aWandererB = 0xA584D45F2C88D7D3ULL; std::uint64_t aWandererC = 0x9050AFAC932A7CA6ULL; std::uint64_t aWandererD = 0x92C1F95114868D67ULL;
    std::uint64_t aWandererE = 0xCEEAE9230E1F017EULL; std::uint64_t aWandererF = 0xA23185794A2A7388ULL; std::uint64_t aWandererG = 0xC900D4C40672B18AULL; std::uint64_t aWandererH = 0x96E3167BF7182D89ULL;
    std::uint64_t aWandererI = 0xBCC7EC64B8C121FDULL; std::uint64_t aWandererJ = 0xA228B1662D540F41ULL; std::uint64_t aWandererK = 0x9FA931256D2BC76EULL;

    // [seed]
        aPrevious = 10881673727439842161U;
        aCarry = 16252434340700159087U;
        aWandererA = 11491941932709244240U;
        aWandererB = 16768764787930138576U;
        aWandererC = 14246342182021727650U;
        aWandererD = 18112090744091075356U;
        aWandererE = 15745829090580399431U;
        aWandererF = 16139874406082639167U;
        aWandererG = 11701175628313092142U;
        aWandererH = 12008519469082740538U;
        aWandererI = 17948337495394803930U;
        aWandererJ = 17774768390678159623U;
        aWandererK = 18324418467596087597U;
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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
    TwistExpander_Bellatrix_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Bellatrix_Arx::Twist_G(pWorkSpace,
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
            0x0B07AD7A3E69960AULL, 0xAC2CB8DB4927F55FULL, 0x6C7713FDB8B0E344ULL, 0xFCD9C43D3CDB94FFULL, 
            0xDC083D05150BEA03ULL, 0x61F166C5EF89EDA0ULL, 0x33E866C7ACD0C982ULL, 0x27EF8E6ED80431A1ULL, 
            0x814394E5D8A8B1FEULL, 0xBC2ECDAC66754680ULL, 0x82BEF945EC7C5B4FULL, 0x66FE97D1CEB42721ULL, 
            0xB4F25D493E9BD059ULL, 0xC62368B1E9489B63ULL, 0x9CA117CB7CC34946ULL, 0x9BC8E0B59041F114ULL, 
            0x6C433E1D64AACA2CULL, 0x6D67A5803BF91BC9ULL, 0x3B9934C64ED1FD7AULL, 0x541B988E443EDDE8ULL, 
            0x6114A193ECA63825ULL, 0x7676C84A1AE6774EULL, 0xA2940D7D24FB8499ULL, 0xD14E9DEFF3E6285AULL, 
            0x9EF7354B14879077ULL, 0xEA6997B88AE832BDULL, 0xD591C22612C5E09DULL, 0x7442BF568ABA221FULL, 
            0xDE5D3697D1E327E3ULL, 0x39440FEE94992C3CULL, 0x611834275B2054ADULL, 0xB2E040BCB6D61133ULL
        },
        {
            0x73C8892415C2D897ULL, 0xDD6E29ECF0B36B8AULL, 0x2476657648025FCDULL, 0xA57C4F656276A6C8ULL, 
            0x8585629021AB95CAULL, 0xC588AAB4C2EC3C8CULL, 0x1CD8ECC8737125DCULL, 0x25587C83F63C8720ULL, 
            0xF41AF941D7A038D6ULL, 0x15211223983CE5B8ULL, 0x71B6F5DB5981C7F9ULL, 0x684CC5FBFBF0CF36ULL, 
            0xDD2C0794E98FBAD3ULL, 0x7C9B0231562C9AABULL, 0x352D8CC8DD700A04ULL, 0x0C76AC8CEBB0CEE6ULL, 
            0x1C43D18B417EE5F2ULL, 0x8AC80D60E2D9A516ULL, 0x01E8425132FC482AULL, 0xE6C6099FA9F82401ULL, 
            0x84B16FDDBCA8C941ULL, 0xEF7AB45803A2A613ULL, 0x3DE7A19FF00AF623ULL, 0xCCA1DAAA990018FCULL, 
            0xB7990E268A21CF2EULL, 0x09E7C37BCB74E2E6ULL, 0x14C2ECAAAA3DE196ULL, 0x00481FB68E298462ULL, 
            0x1AA7E540ECF1F5E7ULL, 0x648C177DE079BFDEULL, 0xB45674481E0A258DULL, 0x553FBAA2B1B75280ULL
        },
        {
            0xCDBC72480173E640ULL, 0x0C4810DF55212C2FULL, 0x7CF78FBFCEBDC40FULL, 0x69CA25579663E1A4ULL, 
            0xD2EB3EBB35B4F5E9ULL, 0x06A4CC11B2390533ULL, 0x5C0C1BCE6AEA6405ULL, 0x272C9C32D6E00412ULL, 
            0x35543831CCD9AF51ULL, 0x85FF2F9A5A736D4EULL, 0x70374712A69A5DC3ULL, 0x8C741B09FF7C86CBULL, 
            0xDB8FD046261AEFE4ULL, 0xDEA95376CC197923ULL, 0x6295F45F124ED5CEULL, 0x08A68EE022CDA1FFULL, 
            0x74DAE45DE31438CEULL, 0x9601417C757F3024ULL, 0x3F85B168934BF7B2ULL, 0x402C3D2201AFB509ULL, 
            0x8A109A15BEA904F6ULL, 0x8C194B1D88B4602EULL, 0x80AAB2C46A061360ULL, 0xFF6CB568E9D6F69EULL, 
            0x193E9648809A049EULL, 0xC2B2C08F8206C3B6ULL, 0xE4C873B5C0DC81D1ULL, 0x2D598E2486033FC0ULL, 
            0x26B147380B8F0007ULL, 0x072322D1F16D6250ULL, 0x9ECA2EC5C9D8D6E1ULL, 0x5EE30091E5C745DDULL
        },
        {
            0xAB5F90E63C1F82DDULL, 0x2FDB90CD019E6686ULL, 0xD13694A5B8800F53ULL, 0x48708C3FF3AA9014ULL, 
            0x7056A6B6685FDA20ULL, 0x4A2598D128FA10D8ULL, 0x31BED724B8D81400ULL, 0xD3A376E62830D371ULL, 
            0x268F9C8F91D5DD4FULL, 0x94326511D1D68D36ULL, 0xA5178E5E1C379C8BULL, 0x1864CA51A7472D1BULL, 
            0x0D2C243A73A9F582ULL, 0xA617E24194E9FD6AULL, 0x5B8B6527A97EC222ULL, 0xB184C4045C1069A0ULL, 
            0x0F07814A57255E5AULL, 0x113FD2B3BF1F1908ULL, 0xF67D5ADEE755D059ULL, 0xE6F2DA855E390AD7ULL, 
            0x1A4D36863C40BA5BULL, 0xDA4DC7D2034A8DE8ULL, 0x19B9A038CD2D0234ULL, 0x7AA10C0D2011CFD5ULL, 
            0xDFD8471A078D845FULL, 0xE824D85E3D44BB43ULL, 0x589768D3ECCF297DULL, 0x2F1F1ACBB31C8776ULL, 
            0x4440CE8892056911ULL, 0xA3D7F404BD340A3FULL, 0xBC486D77294CAAE4ULL, 0x8F0102F10290AC63ULL
        },
        {
            0x93CC23561EBE95EFULL, 0x4B00D97A804CD7FAULL, 0xE9865BB4CDE3151CULL, 0x1A449291CE3A06A2ULL, 
            0x19A7384EF5C4FFA2ULL, 0x2624C6FF4360AEBAULL, 0xB1F541B30E554D5DULL, 0x4F108AC3DEBC19AAULL, 
            0x06C54B2AC286B2FEULL, 0xF0A878CAE29124DAULL, 0xCD61F235802FBB1BULL, 0xB90BBB24F72C171FULL, 
            0x7922381674606B92ULL, 0x6D7BEB78EBD35301ULL, 0x234EF69A2C5843F8ULL, 0x7290F2A220D27A88ULL, 
            0x1C3B09041329878EULL, 0x3187E400663091C1ULL, 0x99FABF33883B800CULL, 0xF5B03A7AD9B108F0ULL, 
            0x16F4BE63948A8DF9ULL, 0x1288F1178BB3F265ULL, 0x3D1F21B40AD0A6E1ULL, 0x0810CBC99AC46E2CULL, 
            0x281ADB2B86867C6DULL, 0x98B9AA2AC8EEA9CAULL, 0xFCF42CD552FE0A9BULL, 0x5C0277534E723100ULL, 
            0x227E62C7A1CC001DULL, 0xE34D426687645946ULL, 0x275ACF1F0094EACBULL, 0xF2B171A3AE34A466ULL
        },
        {
            0x27F5990A7EC19EBFULL, 0xBBDCAF361044AF8CULL, 0xFD64D6F1171CC4F1ULL, 0x7E3395CE165C7873ULL, 
            0xA7D196D7218BB376ULL, 0x4D0248713FEE5930ULL, 0x147FE193F12FDEF7ULL, 0xE298E2C318C93748ULL, 
            0x23C295C7658750E6ULL, 0x38783ADCBCC66A33ULL, 0xA3E741AACA8F5A66ULL, 0x0BDCE746CAE26B81ULL, 
            0x2CF52ACE99602471ULL, 0x15D7D2D7B5B3BAE3ULL, 0xBFEB0B1C3923E447ULL, 0x6915B4E97AC11B02ULL, 
            0x8A820072ABAD0E79ULL, 0xB3AFA776C0F40F0DULL, 0x6D3A13A8574570A0ULL, 0xF18A69CD526FB2CFULL, 
            0xA6AF94E805A9CCB4ULL, 0xA142337E93FAEAB9ULL, 0xEC0CC8C82D987841ULL, 0x4BC2E16EBA53C621ULL, 
            0x8C1D0D9354D5B5DBULL, 0x1EFAFC53E409172AULL, 0xA974FB6270AE74A0ULL, 0xE74B8ED81C130E8AULL, 
            0xBC5583C18151B47AULL, 0xD359BAF4F4A98A47ULL, 0x64BEB3B34A875E8AULL, 0xFD3FA1CB00D337EEULL
        }
    },
    {
        {
            0xA602CF6146102C6DULL, 0x9641892A184B7AA8ULL, 0x52DB39F741C0681DULL, 0x4E849397B2DC2679ULL, 
            0x3053A0138AD0133DULL, 0x570D7A8BEE563B55ULL, 0xE09D98EFE44AB646ULL, 0xFE83AAF2AD1A82B3ULL, 
            0xAFD39A6BF21A9886ULL, 0x2C93DEE9FEB9A1C1ULL, 0xDF787ECF1959CF2EULL, 0x95ADA406F6AA7215ULL, 
            0xEB2B237229D30BDFULL, 0x9190430034D71C95ULL, 0x2D8CBBF875B3784FULL, 0x8C1B14D93D46AD39ULL, 
            0x1730CA568AFAA515ULL, 0x0A9584DF6948E3CDULL, 0x6920A3AC47AC7744ULL, 0xA0897E5E7BA71ADBULL, 
            0xE2579E6D79CF3BD9ULL, 0x10C6437A1E587325ULL, 0x8B1989E5F747CD10ULL, 0x589CBB9375A440DBULL, 
            0xF25D0F23464DD9EEULL, 0x18B43C01DE91B7CBULL, 0x9F23335810D0BA81ULL, 0x64A27E81E1ADD405ULL, 
            0xA5D7E7EB1AB7BF6AULL, 0xA38E884D1DD2E44EULL, 0x23E0292AB7062E90ULL, 0x84EF94CBE66A1113ULL
        },
        {
            0x7C08D74D2D6635A6ULL, 0xE9189C582E46F93BULL, 0x357DB8DA69388063ULL, 0x70577A7134CC386BULL, 
            0xEF76983121F1AC73ULL, 0xD9125136B550B1ABULL, 0x07ADD16B04C0A0CBULL, 0xF26447C57D987650ULL, 
            0xA4CCB447164498F5ULL, 0xCE3A51D476A78579ULL, 0x2B5B1BFEBAD5D13EULL, 0xBA124EB21754C364ULL, 
            0x344C7FC82FC183C2ULL, 0xF36E64CCB285A8EFULL, 0x55525E015BBF773CULL, 0x2F0C54628B23C22EULL, 
            0x67E77C57C7875CF8ULL, 0x1B9C50A16787AEFDULL, 0x9C211AF1964E0117ULL, 0x9ABB260C73D154B0ULL, 
            0xCD12FF197612ACE3ULL, 0x6DC5DA80F893D01EULL, 0x8C4D42615A2CC719ULL, 0x5186CBB3D8E37551ULL, 
            0xEEBBBD343602CC80ULL, 0xFFB85ED067776B78ULL, 0xE832246B727E9CF7ULL, 0xD894C29E7752DEA5ULL, 
            0x999CD8150494CD3AULL, 0xC8E578C589B459F3ULL, 0x83D68BB85EA20EFCULL, 0x409C1FDE0CE5AB54ULL
        },
        {
            0xFE5A38AFBF40D0C3ULL, 0x394063C6007ADCCFULL, 0xD198D6E2A4FB7C27ULL, 0x8002EA37992260A9ULL, 
            0xC4CCA1CFD7F7E534ULL, 0x4B6D578C7881D2B6ULL, 0xA555E6D13F008FD7ULL, 0x813159F67F88EE12ULL, 
            0xC99F062C6A46C0B7ULL, 0x6E2C39983277F22FULL, 0x9C6EE12B66B493FDULL, 0x4D3DCA68D3F26E2AULL, 
            0xB9BEA6D17BCC47A2ULL, 0x2406208C64DE3BDCULL, 0xA7FD083831DAC85AULL, 0x65C8DB7BFCF1831DULL, 
            0x71920A6C6B6D3B90ULL, 0x17909DFFA4F5C6ABULL, 0x5CA6EE491BBDD773ULL, 0xD71059BD6EEC0E11ULL, 
            0x8DC49F18399542CAULL, 0x7B9261B7F7517513ULL, 0x863E39408EF0A997ULL, 0x0A8AECCD2375ADD2ULL, 
            0x4CEA9F4FC95A6584ULL, 0x0465EE5B60A1882FULL, 0x1B5F8BCF1328247FULL, 0xD8A769D500F85145ULL, 
            0x0D2867BC0A7C0738ULL, 0x087912E9E70C8171ULL, 0xA04BC86A18BD91F0ULL, 0x4DA0A16A26F50D83ULL
        },
        {
            0x64725DC1483B0BDFULL, 0x727F54F493983F7CULL, 0xAC33603661EC9B31ULL, 0x1E00AEEC54A97559ULL, 
            0xB008FEFD061CF51EULL, 0xA79137BCD4C0D56AULL, 0x57C5387EEDF7B0C4ULL, 0xCCFF9579CB57BAFDULL, 
            0x46E6EDD0380B8FC3ULL, 0x1F81089116F29B9FULL, 0xA7773EA4D8E0CA36ULL, 0x1AE6223B82A516BEULL, 
            0x044E8379179B3166ULL, 0x44DD27C665F7A032ULL, 0x279D5ECA4B735CD9ULL, 0x5096B4A0607B3FB0ULL, 
            0x6E35D516DDE55867ULL, 0x56096DD55408E78EULL, 0x6F1055CF9C753515ULL, 0x5D6033E9A7B46215ULL, 
            0x68281B30754363ADULL, 0x6CDCE08B952685C0ULL, 0x459CDC2FDE77694CULL, 0xA87133AA2512B114ULL, 
            0x21F2C7866BB1D552ULL, 0x5B1F647D4EF4F59EULL, 0xA9BBE1854279CE65ULL, 0x034615E0FBFF7CFBULL, 
            0x92E12242331B2F8AULL, 0x25227318BFE7831EULL, 0x8BE56EA16603D9B8ULL, 0x0AFC99C9EE226389ULL
        },
        {
            0xD865B288BC672D2CULL, 0x318E796661196738ULL, 0x5248E973C436F21FULL, 0x7BCD78C09EB7D42BULL, 
            0xF2070C5DEB14C3B5ULL, 0x59912978914EF488ULL, 0x066713E71F284D41ULL, 0xE6FA2228F6B30DC5ULL, 
            0xA9B02670AE614C4DULL, 0xC98FCA07734B3C4CULL, 0xDB1C8A962946968FULL, 0x6F36BA6C9AEF066CULL, 
            0xA9ED31944DCF2B05ULL, 0xF4A2EA2007350770ULL, 0x086E895315454FCCULL, 0xE9CA245563830272ULL, 
            0xDF59453DE0DE855FULL, 0x7E4D11C7EFA763AFULL, 0x11F2DF6B25EFE645ULL, 0x35D65E956C0E320BULL, 
            0x11C85B7B028BD0F6ULL, 0x9A8473D5D05C34F9ULL, 0xCB703B3509BD902AULL, 0xE6247A74DBAF0A9AULL, 
            0x763076E35170F85BULL, 0xFF7F0720714C396DULL, 0xC7654B245E8B0596ULL, 0x4F2CC3F4F874A8C2ULL, 
            0xFADF1B20D1058976ULL, 0xE1F4A361CDBA34CEULL, 0xC79CF21C2E5F23BDULL, 0xB3D12DE0B2FA515DULL
        },
        {
            0x8A8A68D6D4BBD11BULL, 0xBA1A9ADA7814A136ULL, 0x9BB1EBD43E20085FULL, 0x0B7D43E192F54615ULL, 
            0x877027BC75A64A57ULL, 0xC37DD3534BB79F5BULL, 0xC61831AB780B5942ULL, 0x7F3A77E2D3E4707BULL, 
            0xD1A46D28CE39E012ULL, 0x1C8C67B008D882BFULL, 0x5E9C0145A8EF3EDBULL, 0x98FBBC5C068764BDULL, 
            0x4A71EE438D2C35F1ULL, 0x60AEACC6D06F9C05ULL, 0x7F4BD2246CB9F3D7ULL, 0x37ED5A54BEEFCC7BULL, 
            0x89D9C11D754F25CDULL, 0x38E4B1CBBCDCECF4ULL, 0x1F2D71C81768D3F0ULL, 0x1FA9D072EF91C72BULL, 
            0x61DD151EE7B962A5ULL, 0x6A6A38A180BE39D6ULL, 0xAEAFA2436D6D9C7CULL, 0xE8DF02184157B124ULL, 
            0x66F849DFBB67FD72ULL, 0x0220705DC2667C30ULL, 0x3F13A4728AF1B31BULL, 0x771B0398278920E8ULL, 
            0xE96F942A6C456368ULL, 0xCECA827F32C15634ULL, 0x3945088260B393A3ULL, 0x1AD1A3DE6356C426ULL
        }
    },
    {
        {
            0x2417769647EEDF37ULL, 0x5469A751C5601DECULL, 0xD5206B026C97B940ULL, 0x70EBD497C9A27F91ULL, 
            0x3C0FA9A3AFA2107FULL, 0x11ED459CD818FAE4ULL, 0x6B8A75DD3D7F2283ULL, 0x4C0D085DB0730A16ULL, 
            0xC498746B11092CF5ULL, 0x81199C3F2095F729ULL, 0xD6D8004DAE2AAC05ULL, 0x9251E62BDE60C3BBULL, 
            0xFFFF6C9805F46C15ULL, 0xC34B009F28B72255ULL, 0x74112FAC259E3E32ULL, 0xBD9C59993D669D73ULL, 
            0x25BA8B6D16AB7CF1ULL, 0x42C1FF48BF55F0D1ULL, 0x6ED886C2664737ACULL, 0x277437AEF6E432D7ULL, 
            0x46E1571854E18B05ULL, 0x7F8C331255A76327ULL, 0xDA7F425E521F413FULL, 0x98F65E5600E66C41ULL, 
            0x8B60117FE83652B9ULL, 0x16E849B55D23CC99ULL, 0x2EE39D9457A341FBULL, 0x2D7E1F54370D6B1BULL, 
            0x54CDFD631E06E5B8ULL, 0xFBA8A1D6B4622B0EULL, 0x5CE3FE887420C957ULL, 0x237D2BD1B471A934ULL
        },
        {
            0xC2DCECEF781765D9ULL, 0x7054A6FBBF1051FCULL, 0xCFDA387228054A33ULL, 0xA7DB49CB5A7925EEULL, 
            0xD6C5AAFA806B639AULL, 0x0CBB4D97EB958898ULL, 0xA7EB5F9C986572ADULL, 0xDEC7F2A0C581D1EEULL, 
            0x027D09A57D614D24ULL, 0x9DA0368B22779B5DULL, 0x513A5B5DDADEF573ULL, 0xD33AC2C97437FF89ULL, 
            0xFFB3B7E2752586D1ULL, 0xF4B352F1DCCA79EDULL, 0xA0E53D3D95522EE4ULL, 0x7849A5432D568299ULL, 
            0x1135FA759E125DB3ULL, 0x01C79CB5D3B0040AULL, 0xE73692E98C404788ULL, 0x9B5FAFEEB16EDBE9ULL, 
            0x8EDFBA0B78AA76CBULL, 0x183AB9B91F7D19DAULL, 0x51424BC134B59840ULL, 0xEF11B65F2D91FE24ULL, 
            0x708166EBDC57934EULL, 0xCA17FB17DB75E1B1ULL, 0x9BAE36616443E450ULL, 0xFD129916B214D262ULL, 
            0x1637543A22B7C56CULL, 0x3E218A77FAB46DB1ULL, 0xCBF5F08E79E6C365ULL, 0x28B0D7B74F96B264ULL
        },
        {
            0xA07F6FB69E5B33ECULL, 0xFDA3F2F5C70C0990ULL, 0x6E6A8A602BCBBC06ULL, 0x81F3C373436B3AA0ULL, 
            0x02874BE49E6F2BD2ULL, 0x13ABA57B65F1006DULL, 0x0C4143B267516934ULL, 0x952C7BBAC7601C30ULL, 
            0x97D3D6F8236CDA63ULL, 0x0CC9F4AF5A4F5C13ULL, 0xB400BD8613413061ULL, 0xAE07ED2A8872E7FEULL, 
            0x564CEDD406A46853ULL, 0x9B5E5E3149B8C199ULL, 0x702F110B7AA3B80AULL, 0xDBD9E423584E8784ULL, 
            0xA2BF080432A06632ULL, 0x90C7A38C59757DD3ULL, 0x3AF5E11D65A5B5CEULL, 0x7AE0CE85F2172BB9ULL, 
            0xE566481C2FCDAE02ULL, 0x1A31EFC50B541ECFULL, 0xCF72B9EEC60A3E91ULL, 0x9D80FEE14162FDD7ULL, 
            0x6EF2087ACB837597ULL, 0xE104E8FC618BD75CULL, 0xF339950B194A6B86ULL, 0xAA82A932F93925FCULL, 
            0x87248C2B9196FFDEULL, 0x36865025881D347FULL, 0xB56E69A717942B4EULL, 0x7C8A682259FDF406ULL
        },
        {
            0xE54FC1FF3D1CC713ULL, 0xC5B3A240BD3C6DA9ULL, 0x1D4E8F96774B7673ULL, 0xD6D067FB82DA674AULL, 
            0x581CD676ACE6FB60ULL, 0x5404020F6D45422CULL, 0xDCA6248CDF367E6DULL, 0x2D5F64AEE153FC93ULL, 
            0x84082484E9FF64D2ULL, 0x626D0A66E0C53B70ULL, 0x6034F8CF58EC6CFDULL, 0xC8EEA078E50031CAULL, 
            0x8FF77CF90C7B7C9CULL, 0xEC7E24E4FC7EDB2BULL, 0xDFCFFD8F9EE6882FULL, 0x129518F6FB93A22EULL, 
            0xBACEA26A6655C720ULL, 0x521061A4D5BC0F62ULL, 0x0F4825AB319F5B1FULL, 0x514CE17EC21418E7ULL, 
            0x791FAC365E510DD0ULL, 0x37EDBD3C840E7DCBULL, 0xB88F2F1EDF07A976ULL, 0xA3D0FA07976BF065ULL, 
            0xBC4DB6494DAC338CULL, 0xA91028C71DAD4514ULL, 0x3A0FB68C2B7535DAULL, 0xD73045CAAFB23B0EULL, 
            0xF127B6D2093E95DDULL, 0xB492BE950B0DE42EULL, 0xA26135292FF22088ULL, 0xA0334D0F685C7CB6ULL
        },
        {
            0xD8418D69575549D6ULL, 0x72676F96264107EFULL, 0x0DCDF60C371597A9ULL, 0x85809080FF6960B3ULL, 
            0x46BEEDE29C1FA0FBULL, 0x12D73B7DFA4CE2E3ULL, 0xEEBA51E5E754A30BULL, 0x6CD8D3535F42B3ACULL, 
            0xB5EFB8229F841926ULL, 0xBD8897774FC45D4EULL, 0x3928CC1F5FE9B0A9ULL, 0x84381085273995CCULL, 
            0x9EF5EA91B85293E2ULL, 0x6E4B1C5EB0459293ULL, 0x8A2476F55FB4FD83ULL, 0x96C4A610915018A3ULL, 
            0x98281E1BB08852B1ULL, 0xEC5C933CD7C4AB16ULL, 0x700B3C6F7731B77FULL, 0x1546D0424C6843A2ULL, 
            0x940EE6F21C10108DULL, 0x82747FB70D54EEBDULL, 0x0405004D930B4937ULL, 0x0905452D8B495F1EULL, 
            0x7F0D7C912EF2A288ULL, 0xC1CC365A490C75B9ULL, 0x8624B5209375084EULL, 0x632B49B11A4D0A81ULL, 
            0x1CDB718A8EAA9560ULL, 0xE91F14BD37752268ULL, 0xB4A5616C6F5102A7ULL, 0xA92ED750675AA5DEULL
        },
        {
            0xF8BD8061551FEF39ULL, 0x80639337F7977C21ULL, 0xEE9951313694CB96ULL, 0xB2716EDBB90D5B0DULL, 
            0x113DBCA29371509EULL, 0x27F2FDD9490B481FULL, 0x728BC15227E9872CULL, 0xA0D97987734E7E3AULL, 
            0xE0518866B576B163ULL, 0xF8E0653A9A35A190ULL, 0xB0E430643BA59505ULL, 0xD818774DC8F0A79EULL, 
            0xCC3B9D86521D708CULL, 0x4731E5008444BD20ULL, 0x3DE17B138F7FEB93ULL, 0x9226C4904C557C7CULL, 
            0xC60EE2F483802BB2ULL, 0xD4A756EB70D64781ULL, 0xF8AAB2CB7F4FEDEAULL, 0x0EA725A2AD310A03ULL, 
            0xC1B7380305BC6429ULL, 0x5DCB56FC56312069ULL, 0x2EFAD2CCE6ABBDB5ULL, 0xB2595F8921FBD06DULL, 
            0x8278C94313AA2E67ULL, 0x0D4E52C9FCA7D40BULL, 0x5712A24C50291239ULL, 0xE66A011D2BD44CA3ULL, 
            0xF0BE38A7BF19EA84ULL, 0x885284341884A017ULL, 0xEC25E644B69AFD4DULL, 0x02A369E6E5BF9D6AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseAConstants = {
    0xF8B87EF43A61EAE9ULL,
    0x89E540C50562DBBEULL,
    0xB89C04FD0A0D39C5ULL,
    0xF8B87EF43A61EAE9ULL,
    0x89E540C50562DBBEULL,
    0xB89C04FD0A0D39C5ULL,
    0x4E1FA9FAB1122C81ULL,
    0xE8B5A181DF7429C0ULL,
    0x3E,
    0xE7,
    0x91,
    0x1F,
    0xBE,
    0xF9,
    0x20,
    0xEF
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseBSalts = {
    {
        {
            0xE55E191CF9F2CF08ULL, 0x4D85DCC49572527FULL, 0xBC035C9B26A28D37ULL, 0x4A493B561B3FFC6CULL, 
            0x886B62127F0BE60FULL, 0x53282A0E4529736AULL, 0x9B3310952109BE5BULL, 0x20427F8ED7A195ABULL, 
            0x3052901CAC9FE6C6ULL, 0xAEB854EBD81C835FULL, 0x53F8A10B400EE9E6ULL, 0xA778F58C4DAF3F72ULL, 
            0x67461EBECC1AE2D2ULL, 0xE06FE2CEE9A0379CULL, 0x3A6949929826C6D7ULL, 0x49C3CEC2AD488AEDULL, 
            0xC6AC2E072A3F74EAULL, 0x082573FF432EDEB5ULL, 0xF2F7A6329E4F77B5ULL, 0x93E2E5F09AE458D0ULL, 
            0xB54EF718F4333310ULL, 0x89EE711B8E669A0EULL, 0xF0FA369220DA67BCULL, 0x69A916E3EC25CCE3ULL, 
            0xDFD6A1AD75A878CFULL, 0x297038D7C9E7506DULL, 0x3E9D386C12517D76ULL, 0x32F4BB4E303BD9ACULL, 
            0xD4304F1228A3C742ULL, 0xDA590174575EFD07ULL, 0xD3F43F25775DA971ULL, 0x8962B0CB4E357D86ULL
        },
        {
            0xF35D09768EF3F5D9ULL, 0xABA84CE4548EC57DULL, 0x3594F7458CE95DFBULL, 0x88C5E3782A5542CBULL, 
            0x4995EC78C06E2845ULL, 0xC48423080CE20BE9ULL, 0x4BAFE4AE5E070D60ULL, 0x6A48B03E98D0D705ULL, 
            0x794D314EA1B31846ULL, 0x156FD6EC8F483328ULL, 0x3E247B8757A2FA8FULL, 0x8E1DA300109D2183ULL, 
            0x45A048E8CC8C2626ULL, 0x711A81DB7F0C8E34ULL, 0x38C49BE034607A4DULL, 0x9F414D633CB018F3ULL, 
            0xEAED00C38E443AA9ULL, 0x7ECF30C73366B740ULL, 0x2C392C962BCCEDBBULL, 0xD187E8A57A826898ULL, 
            0x6FE987DCDEC2CF88ULL, 0x3A17176AD7F9FF50ULL, 0x1E721F138FF6F1ECULL, 0x1C5F4335814AA365ULL, 
            0x65B9B2E22847EC56ULL, 0xA039BA4EECDCFEB3ULL, 0xBAC35040EBF7DCD1ULL, 0xA642F1DC117C6FFAULL, 
            0xC6E929362F22D902ULL, 0xB06E9F3D1C35435FULL, 0x1A1A7AFE864ADB35ULL, 0x6CEDF561A66CB5D3ULL
        },
        {
            0x767274AC1B3A9651ULL, 0x1061715B6AADF8A8ULL, 0xB4B6418424DF1EA7ULL, 0x4AC4604915482104ULL, 
            0x2BBD63C1164FE63CULL, 0xE243EA3D019679B6ULL, 0xB105BB7315146232ULL, 0xAD383E62AE6EDB8FULL, 
            0x0A250FA30B2E9861ULL, 0xC9FF57DB979C38DAULL, 0xCFDDA0541E36C8F9ULL, 0x9B10E38862942935ULL, 
            0x9D00A3A7ACF6006BULL, 0x116685B3E8D26AB4ULL, 0x73420B82D9E3A389ULL, 0x87493FAEAD7A55E0ULL, 
            0xEF060860E29C7EACULL, 0x4E7E93023D677D3FULL, 0x86D1254757CF1061ULL, 0x70BE1C77E3C929D3ULL, 
            0x6F102903634E54B8ULL, 0xCD1E38C1147E1EBCULL, 0x69A92A7123D88286ULL, 0x43D694ACD6B54B38ULL, 
            0x7F6FFD18CCE40112ULL, 0x9E0FCD420C2D63A9ULL, 0xF8BBCDEA9AD62C68ULL, 0x79783C7BAC19F139ULL, 
            0xAF54EFD22DBA975EULL, 0x09C821424C1BF817ULL, 0xB7966761FC69DBBAULL, 0xA36DFA5468469C17ULL
        },
        {
            0x88753A4FE6487507ULL, 0x6F37159511A1975EULL, 0xD92284A231A7F8A0ULL, 0xFC960C418282EA56ULL, 
            0xE4D78C415F0F3C16ULL, 0xAF4441960B7648CBULL, 0x93F2FE1A7CAE3BD2ULL, 0xAD1E095342712218ULL, 
            0x814645116EA8BA9CULL, 0x373151D181031C60ULL, 0x5355C93A730A0EC2ULL, 0x42763CA59E3121D0ULL, 
            0xA3CC73655540D4BAULL, 0x3B6D9495F08313CBULL, 0xD06031FEF2194E73ULL, 0x3190319AD3776FDCULL, 
            0xB8DCBE57AE14FE6AULL, 0xF0ACE8D59781654EULL, 0x73BBC9C680A53CDDULL, 0xD9E88F621E11F18FULL, 
            0x41D28A1C4546A9A7ULL, 0xFC72E4604C0A7763ULL, 0xF0ED1EA0D63A5431ULL, 0xA9DC69D1FE49DCCCULL, 
            0x6BFDE5CA522F7663ULL, 0x4A7FCA1C3E4857DBULL, 0x919C49D2A2621807ULL, 0x7C41FA093419A67FULL, 
            0x301CFE055B5CFFF6ULL, 0x583CE0F3BB3A4D1CULL, 0x5F7D8B2D97C63842ULL, 0xD83C90725676C1BBULL
        },
        {
            0x15142DD986E69893ULL, 0xCC9C7514036F32D2ULL, 0x3321AB40CFDD4D86ULL, 0x8A2A16A856FB3C1AULL, 
            0xF36A8F9719822A4FULL, 0x44D8B7DBF31993BDULL, 0x32A0827F39FE9023ULL, 0x88E3FC5D4FD4D615ULL, 
            0x9605ADEC6EFA0B1AULL, 0x851F200371275B7EULL, 0x39AB1FA4F4782B2CULL, 0xD43E3AD1B3709E8EULL, 
            0x265DE05E345BF166ULL, 0x3DDB0CDC18E4AED1ULL, 0x4AEEE1BDCE8830BEULL, 0x6413CDC85D3A1AB5ULL, 
            0xA46120B0E40725B5ULL, 0x9E7F8E5061448764ULL, 0x63FC1936DE7B2BFDULL, 0x48C978199D08A400ULL, 
            0x4EC10E6699DB1453ULL, 0xF46BFE7061DB4FE4ULL, 0xD8EE154FA00FF8B9ULL, 0xA1E3BB0534090744ULL, 
            0x52E5FB5E6D6FDFD3ULL, 0x3F8786EE10E927A7ULL, 0x7279CB4426B530E0ULL, 0x9F47B1107E92823DULL, 
            0x07BF6AC72792270EULL, 0x7F5FF63FBAA529E4ULL, 0xD9601DE646E3124BULL, 0xFBEDFC24EDD65D98ULL
        },
        {
            0xBA2534DC5FD6BE6EULL, 0xB3F584AEA218B0BBULL, 0x5839617C41976AA6ULL, 0x5B3B0AC408293F48ULL, 
            0xF60878E0521D0638ULL, 0xF2FD51BEE2123C3BULL, 0x4B3B088764656558ULL, 0xACD71380AC429463ULL, 
            0x2AB4A2A0F2F74F14ULL, 0xE005D96ED7E5A1B3ULL, 0xBEB01215B5B92CB2ULL, 0x6E50AEEC4CE5BEBCULL, 
            0x27CB97C5D2EDF0AAULL, 0xDF8B9C251216D175ULL, 0x7281B4991C70334CULL, 0x30CF8F48C303F962ULL, 
            0xCA25BDF4DBD169DCULL, 0x1ECE9D4232B3C5F2ULL, 0xBBD1A47BDCF4DA36ULL, 0x1E01C1F727489FF2ULL, 
            0xB70427883478C130ULL, 0x8D34DC4DCFE91D95ULL, 0xD2B4E4BBA78B0B7DULL, 0x89AB8C83B5C7F35DULL, 
            0x89900327AE545165ULL, 0x322EFEDDE485A745ULL, 0x45CD38A455718566ULL, 0xB74E5E6B44195C9BULL, 
            0xFDCD2C56F1B33814ULL, 0x822B3D357A9B0D72ULL, 0xE2AF46E9DBD00F21ULL, 0x892E0BA5CA7DC728ULL
        }
    },
    {
        {
            0xFA958825CE3780BAULL, 0x5A04920BC112934BULL, 0xE747E102AC5C2DE2ULL, 0x28B4114DC02CCDE8ULL, 
            0xD7AFBB2A52EDC287ULL, 0x61B04E6F62ED4628ULL, 0x70644CE08244EDE1ULL, 0x9ABB8B8922B85270ULL, 
            0x49D0268B7BA8D0E1ULL, 0x3B18C85707CE0188ULL, 0x834FE1EE005C9827ULL, 0xC5DAFE40F612635BULL, 
            0xE952B770829D91F0ULL, 0x3C820BADCF8E6F2BULL, 0x645CA59FE053DC4CULL, 0x8C8C255AB399BF6DULL, 
            0xA648E10CC135B3EFULL, 0x9DD0CC71BC98C3A1ULL, 0xB6F0C2B92164DC7AULL, 0x5E1CBE1FDFDFC33CULL, 
            0xBCD2D5FE7F0E96E2ULL, 0xACFCFB0E291D452EULL, 0x331428BF192B5061ULL, 0x88E963518F48FE51ULL, 
            0xDF42E00260DB188BULL, 0x83634A16F1FA3B43ULL, 0x7423BBCAAA7C2F96ULL, 0x2EC17C717FCDD499ULL, 
            0x238B2569F148FC63ULL, 0x3FCEF1E50F09FA88ULL, 0xC23B4E8A1E233685ULL, 0xA6FE40D25D8A5C79ULL
        },
        {
            0x60DCB744D191F116ULL, 0x530B448A0033F47FULL, 0x22B3C8012B1CA1D1ULL, 0xB18A5FC9F1F9F1C6ULL, 
            0xED9EF0AF57C9F168ULL, 0x4A0B1FEFE70DC4EAULL, 0xF38232704ED8EC86ULL, 0xE07FD3ABD4553C16ULL, 
            0xC0A4A0ED979DBF6FULL, 0xF00E6E4CE5840540ULL, 0x00EEB7552FCFF806ULL, 0x08F45C09F0C97499ULL, 
            0xAAA98EB490621C07ULL, 0xF2198C49D6D3BD52ULL, 0x35B498862EAC2026ULL, 0x54849B6AE57DC556ULL, 
            0xAD23E46DB079DC40ULL, 0x436D5FE0AD88A700ULL, 0xC04366C8086BC68FULL, 0x52D732B5BEB9F2A0ULL, 
            0xF8A52064C5913E96ULL, 0xC5936F8D51374C6DULL, 0x1F59AEDEF9A0FCEFULL, 0x82AABBFF1F37469BULL, 
            0x9E01BD368FC2C9F3ULL, 0xFE24ED8CDF25850BULL, 0x30B0495FEDE5950AULL, 0x778BCA46BD4CD018ULL, 
            0x8696B009A15B9000ULL, 0x613B0D67A853A5A7ULL, 0xE301B0609AE148ADULL, 0xB78521B3C7A2190CULL
        },
        {
            0xE6CD0465F79529F7ULL, 0x9BAC90D2442403A3ULL, 0x22DA08DF355D5A9BULL, 0x8155DA7538073CE2ULL, 
            0x1E2D3320DA601E0FULL, 0x135B221D1D0470C4ULL, 0xAC450F84F7B2F4A9ULL, 0x2B195009A5B84588ULL, 
            0x46613742C9D7FDF7ULL, 0xE9ED949D1E35E5EBULL, 0x34C6CC21E2802ED6ULL, 0x281A8AD8F9F4C483ULL, 
            0x03C954987C0E748EULL, 0xDA06E6469766CCE0ULL, 0x0C07BAE08DF4DEE8ULL, 0xB24820CC93197229ULL, 
            0x1D6733B794CBBD9DULL, 0x0E01FA30B9997E89ULL, 0x141EFD8B61D24B35ULL, 0xF8D9DA0B231CA69FULL, 
            0x6CD547EDFBEC5DBFULL, 0xCBE0C708EEF451D0ULL, 0x8E3F5A5EA752B325ULL, 0x5B2100BAF9EB9338ULL, 
            0xDF0149C1C4CF0CE5ULL, 0x5F274E72900BDA7DULL, 0x1C172333E74D78DEULL, 0xDB10E180CC2CA7A9ULL, 
            0xD59EF98CDE99084BULL, 0x1EEFA5E4D565BB3CULL, 0x3AE14B15950D41D2ULL, 0x43213F94DBEB07F8ULL
        },
        {
            0x2EE94B3D73C6C7E4ULL, 0x145DAEF570695955ULL, 0x8AEB6D74391CEABBULL, 0xF39F00BB0B03976FULL, 
            0xFD32B64B9E8A8DC6ULL, 0x9E05E446647E4368ULL, 0x34F5BFB9836A0320ULL, 0x46581F123D45BF14ULL, 
            0x864DB62363709D68ULL, 0x775A785DE2FBD939ULL, 0x0ED26866201B991FULL, 0xC2D21D851797D2D9ULL, 
            0x357F6A743D58F01DULL, 0xDD5BCA3C87F8FBF1ULL, 0x96615FCFE6C6B332ULL, 0x3098694064C51117ULL, 
            0xEF057A6F23C43E87ULL, 0xCC7C0F478D6BC633ULL, 0x56386B314E6A4C86ULL, 0xECB3D160BFD278F5ULL, 
            0x4A6CEA908AF92502ULL, 0x73A3A08176BC7275ULL, 0xB99B26BD3693F089ULL, 0xAF3538128D02824EULL, 
            0x57F6ECA5BA2EC2E4ULL, 0xA7DD68937448835BULL, 0x5D648F857B9B4EE7ULL, 0x1BD7C5E7221D743AULL, 
            0x47D4D0C8F7738ECBULL, 0x4EF0EC9DBFF81551ULL, 0xF98008A987AC445BULL, 0xD4C4F28F700720B2ULL
        },
        {
            0x0DFB3D71DAD5B485ULL, 0xE80FA77B33CF74ECULL, 0x9B4A62680F267C91ULL, 0x85A64C289E27579DULL, 
            0x057B37AE83364869ULL, 0x3E13E029CBD069B3ULL, 0xF8867FAB567CC1A8ULL, 0xCB5DC5A91F95684BULL, 
            0x28FB8C31919F5ADDULL, 0xE8A581BEAE408223ULL, 0x117F4855FAB994A8ULL, 0xBABDFACEFE974395ULL, 
            0xBDBABE90201E2FD1ULL, 0x3B5E7B0091EF0DC7ULL, 0x2D88588A40FF4DD9ULL, 0xA3593A3AAA33083AULL, 
            0xAA95F72C69817356ULL, 0x564FBD3E359FCC12ULL, 0x75A7B19C91238F1BULL, 0x55ACF0EBAC55C15FULL, 
            0x645AEEF992EB5D92ULL, 0x2F453538C46B46E4ULL, 0xAE994E0569BCA0A7ULL, 0x66D15B9B4AD8C8E0ULL, 
            0xD18DD588C460DDBBULL, 0xEE10565E4B188A24ULL, 0x589D641B25B0F44CULL, 0x83B76312B9B3D944ULL, 
            0x6C094C01B8E56ED1ULL, 0x52FFFF913C0B3AADULL, 0x119C29A518D4A9A5ULL, 0x9B88D4898FC17574ULL
        },
        {
            0x159DEDD073703E4CULL, 0x2859A59B3BDA4EC0ULL, 0x9C5584157BC19A7DULL, 0xB7B14965518D7C9CULL, 
            0x988D084018ABCE58ULL, 0x98F2F5F63F2FA288ULL, 0xE5B490ADDCF5D95DULL, 0x612B0D664C12DBB5ULL, 
            0xF05264A7C355AB84ULL, 0x3F4C4E3A6EBF7262ULL, 0x1389F6ACA5A7B683ULL, 0x4D8F506B4F29D483ULL, 
            0x6202A704705203CAULL, 0x2D9E44DB692B8C6BULL, 0x63F2378D597D0A29ULL, 0x80E51880186BFC17ULL, 
            0xB1957DBBCB247397ULL, 0x6671F9995EB16CAEULL, 0xC325A1C24AB342D6ULL, 0xD8F544D96C327FABULL, 
            0x0AE6F23834313329ULL, 0xC73DCCF313EF4505ULL, 0x8E7A268C3596B377ULL, 0xAC71CA693C67C70EULL, 
            0x8A9258973D1D836FULL, 0xD45B52552F202451ULL, 0xBE09456FE45970BDULL, 0xD49D37253AB9D35CULL, 
            0x908F9A2318D636A4ULL, 0x1E753B77007C1FCCULL, 0x89D1324C6342E4CBULL, 0xA2682C7B1999D41DULL
        }
    },
    {
        {
            0x963AC375BDBD9C77ULL, 0x56F1FCE0325EEEEAULL, 0xAA6CF249759F4561ULL, 0xF9B4F2A8F5BA2103ULL, 
            0xA7F63A42DC9570CAULL, 0xCC50DAAA8058ADDBULL, 0x5CD3AA637A15E01EULL, 0xB361C54C072B4C92ULL, 
            0x769167A6106B3518ULL, 0x88D6C97EE5E0F556ULL, 0x166B842C07B8B576ULL, 0xE1752C146E1FB461ULL, 
            0xC6301C5DA5B8FD8DULL, 0x1858C43F8C29C45CULL, 0xA64B2528597A6EC9ULL, 0x005981775EC43BD4ULL, 
            0x282AEF178B1BF3CBULL, 0x04CC691CC59C59DCULL, 0x439889049AC8F8E0ULL, 0x6049F50B25538D2BULL, 
            0x07604EC85044D785ULL, 0x1AC8A98442AF1AE7ULL, 0xF75742A4E4440EFEULL, 0x36FB931C3FED8E8BULL, 
            0x87C2FB40035BE1EFULL, 0xE52BE463ECA9F962ULL, 0x9057A58D44682750ULL, 0xF3258C7D3CDE5AC5ULL, 
            0x2FC63B344E148851ULL, 0x60658E84B431B425ULL, 0x595D54704C7439ABULL, 0x3AA678C743AF6681ULL
        },
        {
            0x41E1CBFB67CF67E0ULL, 0xDE04803B43C07766ULL, 0x338803CA6F4196ACULL, 0xD1F5C073C3274076ULL, 
            0xE62599A4224D4028ULL, 0xC7659C7CB72C8FA9ULL, 0x2D691C5595C88A70ULL, 0xC533552E922872FFULL, 
            0xC083A9A0A3DE17BBULL, 0x08076F0DBD2D7F68ULL, 0x9B25592CE73A712CULL, 0xA920693E8AB0082AULL, 
            0x26828090E4981546ULL, 0xB94EBD20EEE63317ULL, 0x568F477EDFA9567AULL, 0x2028816CF82A3749ULL, 
            0x4DC6A53DAA153133ULL, 0xB37C4FDC4CA00841ULL, 0x3BA8313294E7AECAULL, 0x2CDAE65F3E8EC86BULL, 
            0xC81E8B8AE367D71DULL, 0x07C70AA0C48148B4ULL, 0x643AC0F61D19A179ULL, 0x29FED56192C74D0EULL, 
            0x47E37B5A7F08B60BULL, 0xFF366E2BCAD7BA00ULL, 0x807E5A67313BBA3CULL, 0xA4162D74597FE427ULL, 
            0x9079A62BEB7C86E4ULL, 0xA6089F125ADB6EA6ULL, 0xF37760B27B63E310ULL, 0x0535D24BDED89451ULL
        },
        {
            0xCF09C0CE9D598489ULL, 0x59E219E15688BD60ULL, 0x3142FD5D25998444ULL, 0x2A37BB22AB53E4AFULL, 
            0x5D07CF806ED3D12AULL, 0x336C3B132D14D088ULL, 0xBEF8F83430CA858DULL, 0xA78699B7F2AF4411ULL, 
            0x1C132F41281B1D04ULL, 0xC9946F0B58501C8AULL, 0xF7C7C2773F2602BAULL, 0x19EBF9D47C7E4632ULL, 
            0x52421FD538B44F16ULL, 0x2503C1A4B8B45A86ULL, 0xA30D1D3289205B45ULL, 0x8657DACB75A3D556ULL, 
            0x06D2A48DDE0F7200ULL, 0x70B9B0E507A0F253ULL, 0xE583D89B10B95081ULL, 0x9E8EC6FFDC0902BBULL, 
            0xC83BFA1129591B06ULL, 0x52ADA313219D7B57ULL, 0xC869AE07C8771321ULL, 0xADFB194D25C09DEDULL, 
            0x2DA8805F8472A39DULL, 0x70ADE82E7916DBFCULL, 0x237CA60AB82D2298ULL, 0x501B180B7BE8E03FULL, 
            0x163D3632CB4D76F8ULL, 0x6BFF1C76F6666581ULL, 0xE98B0765D23A0693ULL, 0xD192C3F6BFCA24E7ULL
        },
        {
            0xDF1B36A2C659A968ULL, 0x8C572DA2077A02A2ULL, 0x7A2A6573FC2AE6EFULL, 0x9BD9C446A24C7EF2ULL, 
            0xDD5522C4B5274434ULL, 0x7A49C9CCBDFA0437ULL, 0x657384A7FCFFE84AULL, 0x7FA3B85FC413C7C1ULL, 
            0x68026B7593B5EC7CULL, 0xBC70FE35F7F9045AULL, 0x119A90BFABD58292ULL, 0xD458BABED5F89F92ULL, 
            0xCD4405D9CDEC32B6ULL, 0x657A84FC2B50E8ABULL, 0x8D368ECED1B88970ULL, 0x3DAC1B64D8C09AF6ULL, 
            0x05182E5EC25950A3ULL, 0x745D76D5AAA1C696ULL, 0x59FBB042BF661B1FULL, 0x7D89BCB9F755FDC6ULL, 
            0xB44675CE9720621CULL, 0xFAA0581A6D935AC5ULL, 0x549687575561E69DULL, 0x9C2FAED26C2F26ACULL, 
            0xEA0EBCF77A387147ULL, 0x450AFC61E7F396A3ULL, 0x036B9C4C18B8CD53ULL, 0xC4F54513F8BB35D4ULL, 
            0xB37F0A99088C72F1ULL, 0xE8DDC3792926ABC1ULL, 0x515C45B0FD10A0FDULL, 0xB3CB87E3D90E3001ULL
        },
        {
            0x75A4D2572AFCEE8EULL, 0x97AEC151DBE976F8ULL, 0x2EA7903D9625FC63ULL, 0x405847C177F839E3ULL, 
            0x0CBF02283A948742ULL, 0xAC82C2DA7C0AC99DULL, 0x5FD4736E47A1BCF4ULL, 0x2AAAEC5E04F2A6B9ULL, 
            0x9B2234274C18B2C4ULL, 0x2FB7FB9B8DD92445ULL, 0xA55D13CD51ED10A5ULL, 0x3E0173534898CDE3ULL, 
            0x7C483EF043DB7E69ULL, 0xC5E9C72B9BE5C783ULL, 0xBC54E05C51BAE961ULL, 0xAA4FCDBC8F6F5369ULL, 
            0xDFD41C90A00FADC3ULL, 0x8F17DCA1930DCFEAULL, 0xA93DAB1386AEA314ULL, 0x334A788D1515DC46ULL, 
            0x945BEAC1DCA3E095ULL, 0x3EBD8B662F2CD76EULL, 0x0878764FD06325F9ULL, 0xA4AA95DDD0875631ULL, 
            0x7F75E21854D5A5A6ULL, 0x98E128780B21CA97ULL, 0x37FBD0D4855644BBULL, 0xFA3F9D4EBB291F7CULL, 
            0xAD8DD97A14AC6055ULL, 0x72A4EDF3489F8692ULL, 0xB0DCE1C199F606E9ULL, 0x556C6C99D199DD04ULL
        },
        {
            0xDC9F49316F847D8CULL, 0xDAE361E5C29C715CULL, 0x5E8202DC8DF7F2ABULL, 0xB03720BE7BFEE31DULL, 
            0xCC52176B90E9A071ULL, 0xE5B56C79BC043DA4ULL, 0x53721FEAB5BFC840ULL, 0xE68444944C758B2CULL, 
            0xEC5951BBAF479DA2ULL, 0x864A6423226AF566ULL, 0x0A9F83B88E751C23ULL, 0xD769110C3C5C2728ULL, 
            0x2A2D9C71C78E2293ULL, 0x49307338453304FAULL, 0xA4BCAAB8CC6D9FA9ULL, 0xC2F835775C8E1D84ULL, 
            0x4217004E6C8CC2BBULL, 0x67A07452A1F8A1D9ULL, 0xC385FFD37CDC1482ULL, 0x8644719EFC096612ULL, 
            0x8E4792CFB15C4C32ULL, 0x9F5E85846812AD18ULL, 0xF268D9AE69A58815ULL, 0x86843400F1107428ULL, 
            0x1A079057332F171CULL, 0xF50D7570B9DE2DB7ULL, 0x27032788BB5F30ADULL, 0x90EC225C13479EBDULL, 
            0x63BAA09F0F69861EULL, 0xF54B0B7FFF253554ULL, 0xD7D3CB47EF8EFB8BULL, 0x5CA68C057FC8F62EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseBConstants = {
    0xBD49B6261D3428BAULL,
    0x094C8E82E8D718C6ULL,
    0xAE75A0B45A075B80ULL,
    0xBD49B6261D3428BAULL,
    0x094C8E82E8D718C6ULL,
    0xAE75A0B45A075B80ULL,
    0x48C269045A3F3451ULL,
    0x3A670BD6DD0490E1ULL,
    0xA5,
    0xF8,
    0x82,
    0xAA,
    0x9A,
    0x84,
    0xC0,
    0xA3
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseCSalts = {
    {
        {
            0x342F6C188948253CULL, 0x1C216B8A03B7F7EDULL, 0x79C81D08F50E1594ULL, 0x3DD96921EA17FA4AULL, 
            0x60512B5BA1D5C2C6ULL, 0x2719BC9815A0B7F9ULL, 0xC1FDAC81DC53E408ULL, 0xDACDF73404B9E4BFULL, 
            0xB310BA6887F261E0ULL, 0xE37454538BF087C9ULL, 0xCA70B45D7557D815ULL, 0x17B77F37A67D3C6DULL, 
            0xC177E7AE1704B0ABULL, 0x6BA9E036C15013AAULL, 0x9158173F09075E51ULL, 0xFD396D9DCBB68994ULL, 
            0x9514111012DC4EC4ULL, 0x7154CCBBDE6E44FAULL, 0x85C1DE1838DA5285ULL, 0x7DA308BDF779D33FULL, 
            0xAE94C10779AFF62BULL, 0xEA2E27A80582ACBFULL, 0x3E9A24EC3E1D69BBULL, 0xA1D2DEFC49A521F9ULL, 
            0x0850E22916A6750BULL, 0x64B91407B240FED9ULL, 0xD3C944A7D8C74224ULL, 0xAC3988F673FE26A4ULL, 
            0x4BFF477E67E3E5D5ULL, 0xFD8C327ABFAC84DEULL, 0xD21FB76F95B06EF8ULL, 0x0B083D1213E935F3ULL
        },
        {
            0x31B82BBF32EA1680ULL, 0x97A94A4F4B52D448ULL, 0xF58D74019FBF830EULL, 0xF6CA789983A6FAAEULL, 
            0xBBE0E0074BEB98D5ULL, 0x7E35CEA374738050ULL, 0x69646D8A0B7EB792ULL, 0xACC0BC263204C397ULL, 
            0x41FC90732BF3E68BULL, 0x224C4AD2E9C96804ULL, 0x57EA102DB43398FBULL, 0xB4C4797538510FB8ULL, 
            0x51856E63C49D6708ULL, 0xF99A0E4863C9F86DULL, 0xDD71B70ABC138540ULL, 0xD73110219E88BF38ULL, 
            0xB280A6B467F5266EULL, 0x513C35185E6A8026ULL, 0x554C347B20796B44ULL, 0x44767072BFAA3867ULL, 
            0x37B761A0AA5A74A1ULL, 0xC0B54AE319DB4A70ULL, 0xECB8A55DD9C617E8ULL, 0x3A45BB5AC64502B8ULL, 
            0x9D2E3AB338CBEB1CULL, 0x69860DEFE5481487ULL, 0xEAE4BCAA58229135ULL, 0x0C30B759F488349EULL, 
            0x6C9257FD0DB17645ULL, 0x81746748E4D6E926ULL, 0x96E0FE2EAA68FBFDULL, 0x4619239D96E6E1F5ULL
        },
        {
            0xC9D3CEA5BC59E20AULL, 0x931217EC42D404A0ULL, 0x0DD41A84553AC080ULL, 0xB9C24B8BD079E20DULL, 
            0xE6574511A3E56A4AULL, 0x124D1E29D83490F8ULL, 0xFD1C041F3BFE33D3ULL, 0x67E2D113412805D9ULL, 
            0x063F384576D36946ULL, 0xC12122A008B9DCFAULL, 0x162A74720BEBAA0FULL, 0xF9F946017B942C11ULL, 
            0x363E7D98B47AF704ULL, 0xB4BBCBDAABF0E428ULL, 0x01219CC71D32F838ULL, 0x085EC4B5A49B4F30ULL, 
            0x5713F31E5F231800ULL, 0xBF56BC5541D617A3ULL, 0x07BCD03979CDBF3CULL, 0xE0E898E3BEBDD334ULL, 
            0xC791D3466345426FULL, 0x2F1B4C90B751802CULL, 0x7DBA19C0D313A836ULL, 0x994F2F7D57FABE95ULL, 
            0x9F3D683C84912CEDULL, 0x67A5FC80AD2385CEULL, 0x54C8DDC7F25F6CF4ULL, 0x8D6F9E4C8C180EAFULL, 
            0x77EDDC298BA4EC0DULL, 0x15CF6E23BE4E400EULL, 0x1B80FAE941583956ULL, 0x21B55ACBF2AC664CULL
        },
        {
            0x65B1BB6E820529D6ULL, 0x45137AE98AA2FE3FULL, 0xB6A75241D2C48E7EULL, 0x0E5F9FA0E5BC9862ULL, 
            0x7A45E4C43FBD7498ULL, 0xA686F0DE7B67452BULL, 0x3165E16357162949ULL, 0xFF906622F9DB8842ULL, 
            0xECB20D27970DEEE8ULL, 0xA44C3447EBAC8E6DULL, 0xD4D634FE14CD9BCEULL, 0xC178D3DFA423C840ULL, 
            0xBD338A8F77FD2E0EULL, 0xDB5362DEB54BE8FFULL, 0xFE20605E7BA48329ULL, 0x3CE5662BF5208732ULL, 
            0xEE443584A32937DFULL, 0x1FB14457D1278248ULL, 0x0EACB710C6DE3A41ULL, 0xB00BB512DFBFC842ULL, 
            0x6C5633860BED4E6FULL, 0x7D4FF2EA46FAE852ULL, 0x65B33C18492490F0ULL, 0x1B504BC72DC2AC7AULL, 
            0xB9499260C27184B6ULL, 0xE4D3D3BAE9639AA1ULL, 0x21349AA5B0191A05ULL, 0x882C4B188DDADDFDULL, 
            0xF2275425B1395B31ULL, 0xD95E5992374052C3ULL, 0xA291DDCF5953E6C8ULL, 0xA7F1EB56BFBBF0ECULL
        },
        {
            0xEACE55016261B1B1ULL, 0x0A1F9841286AEBE7ULL, 0xFFDE5D6B0C0BA53CULL, 0xD97ECFA5958795EDULL, 
            0xF36B3C4877953B8CULL, 0x28267F2E4EAF87FAULL, 0xA1CA1F570711E374ULL, 0x776FD595C983EF23ULL, 
            0xFC5A87FBA91A4648ULL, 0xFC05AC4BB6990D5CULL, 0x7FD7E4EAFB2C3EC6ULL, 0x515FD44201530827ULL, 
            0xD79E38398C9889F0ULL, 0x4CBFBE00B3E7A48EULL, 0x2CE056C06EE234C3ULL, 0x8D8E0B608EBF9A9CULL, 
            0x749180D2D02E7A09ULL, 0x04E72C3F9DCBB338ULL, 0x7B9AE235E9D10352ULL, 0xBA70EE30102D69D1ULL, 
            0x6A7EEAF86B8EE6B2ULL, 0x22736FF5DBBCA9F1ULL, 0x65D8EBD3DB8A83D1ULL, 0xF42CE628132A7475ULL, 
            0x74054526DEFD583CULL, 0x2DA19B9669AF2872ULL, 0x2CE729C5ACC06F1AULL, 0x39523BD0C04F4D45ULL, 
            0x0C1067FC46DF4A5BULL, 0xE95973D9A37D8E08ULL, 0x98907AE95018A7F3ULL, 0x82923FF0AEB26119ULL
        },
        {
            0x6B0ABCA9DC764415ULL, 0x9A34842FE9E2946DULL, 0xC7F2F46DB5D024E4ULL, 0x79EF2D61CE6472E1ULL, 
            0x2C659B86A45981C5ULL, 0xB3FBC2438A6B0038ULL, 0x65CD84314B00516BULL, 0xD5652340AE0D3309ULL, 
            0xE31364D62C46F141ULL, 0x4F8D7F4F7CF6DE46ULL, 0xA16E09ACA87FB614ULL, 0xE75A15A0D5F74EFAULL, 
            0x060A0CF079033EDCULL, 0xA743B751706ABAABULL, 0x8BAD7CA60AF5B288ULL, 0xC6F1C11F0E9C8BF1ULL, 
            0xC5B0F7E966E503C7ULL, 0xD790B8768CCF061BULL, 0xBAA2E20DAEC3C7F5ULL, 0x22FA28A488E0D77AULL, 
            0xABB3F61AD0D36320ULL, 0xACBFCD07E242F36CULL, 0x3CC26EFC24FF1335ULL, 0x4C12974FDC93F2BFULL, 
            0x8F374BF53E79D68DULL, 0x8620D13380BADA7DULL, 0xA166EB8A2F091104ULL, 0x21EAFFD8B6C00C0FULL, 
            0x38550D183AF17CD0ULL, 0xE32B6DD2E7579A8DULL, 0xB083FA33F5FDEC19ULL, 0x8F97162FF4F1A664ULL
        }
    },
    {
        {
            0x3E9EDD2B46E3FE39ULL, 0xAE094A598021016EULL, 0x8435BDCEBB09353AULL, 0x3B8B0FF78AA981D6ULL, 
            0x0D0BAB53351A905FULL, 0x11AB2B2ABFE3D918ULL, 0xD072787B121C99A3ULL, 0x79A4CD450F23EC6AULL, 
            0xE93F9ACC2259682EULL, 0x9205DA03EC120EAAULL, 0x7187B046F9B0972DULL, 0xB0B2EDFDB7853356ULL, 
            0x9CB86B0AC3DD8CB8ULL, 0xEA3B8DD7900092E5ULL, 0x0BDE427B544CE288ULL, 0xB7B6B14AC914075DULL, 
            0x3E71DD1EB18D6356ULL, 0x7FDECF1550415795ULL, 0x21A24BA2AE3EF42EULL, 0xDEE8198B468057E9ULL, 
            0xEEA6A9B7C98A487BULL, 0x842C4C7EB55E3F6DULL, 0x69342DA4BA4C0DF9ULL, 0x2AE0EE289594BA18ULL, 
            0xDA1156CAE923E1A3ULL, 0x958778B39248F8AEULL, 0x9F92C99C696912E2ULL, 0x899F978CA1BA0AA4ULL, 
            0x7086010ED4432948ULL, 0xA5AF485A60BA05C8ULL, 0x0852B707823C0707ULL, 0xA9FA805FBEE6B931ULL
        },
        {
            0x609F295C6D970269ULL, 0x83CB9A53E8C3AF45ULL, 0xA3BACC25063F58BCULL, 0x4BE76377DFE18A99ULL, 
            0x40EFC1C2D6263D7DULL, 0x1DD48E2F0E052892ULL, 0xD2D9646CCEAC08FAULL, 0xCE3AA1206BD7E594ULL, 
            0x9F3CAD57CF47E9ABULL, 0x0E04EFB5A6A3674CULL, 0x2D94710C2CA7F6A0ULL, 0xD012E792080756A8ULL, 
            0x9D283F762FDD0B06ULL, 0xB465E79511827965ULL, 0x3B4C16956BC3C4D5ULL, 0x10F717BD12651BF9ULL, 
            0x3991CC8A4EB781ACULL, 0xF5D0C7342AFBB7D6ULL, 0x0A577C5EFBE65C8CULL, 0x674266F06E15B093ULL, 
            0xC9EFC393C29C449EULL, 0xEA0F67F603450257ULL, 0x879718A21C07F2F8ULL, 0xDBCB92C14CDCE6B4ULL, 
            0x8E7A8A61453A9EA2ULL, 0x84032799A18821E1ULL, 0xC278E358AF1FA686ULL, 0xB0C262CDD1E18800ULL, 
            0xF1901B2F5022EEC6ULL, 0xF2D392683D9AD23BULL, 0xDB8D73DDE5409120ULL, 0x38B2F32D81E5BD80ULL
        },
        {
            0x6CD2F93F433C3AFDULL, 0xBE9CBB4371F543DBULL, 0x6408CAEF5CFA1E3EULL, 0xA9C622DCDBE869C6ULL, 
            0x2C8BD48C75A15D93ULL, 0x68F7FBB888986AF4ULL, 0x288E52D9C9C9980EULL, 0xB88158C46DB4411AULL, 
            0xDFB166E8FDEBFC99ULL, 0x20DD8EDDDC25E916ULL, 0xFC87D9A9E99A27FBULL, 0x8DD893B0ED6FFB4FULL, 
            0x096555ECEE9BF135ULL, 0x044B2D2C2E141B2BULL, 0xFD8F91BE727747C8ULL, 0x66095D027078A6C1ULL, 
            0xEA5FADB98A1E3EB5ULL, 0x73B3C8D4227719DDULL, 0x51C6E61221BB5F55ULL, 0xAE400ABB5788E870ULL, 
            0x802EB5FD0D5E4C79ULL, 0xDE38C401D584DBA0ULL, 0xA575ED6952EE2234ULL, 0xE0D498BB3C588D2FULL, 
            0xE3E012F78E092797ULL, 0xABF6A85821E589DEULL, 0x4C1AAFC103709DD0ULL, 0x323A632966436820ULL, 
            0xA0E6A36B152F2F39ULL, 0xC059469B0D48877BULL, 0xFD09F053E3BF8941ULL, 0x80FF9B4006532F64ULL
        },
        {
            0x2DFD19EB499CBB8EULL, 0x9F23B8B28D4F7F2DULL, 0xF54A438B1FB66D76ULL, 0x3ABB31A26B5F2B98ULL, 
            0x78F5E805B10BC3BAULL, 0x507E92B6262F9640ULL, 0xD374C2F6EC073207ULL, 0xEA94D8AB7FE4BB70ULL, 
            0x9A5311EA90AE4593ULL, 0x25607B67A088CF08ULL, 0x4D0A1276CFB1FAF3ULL, 0xCE242F0069BFFAEBULL, 
            0xB5F4358F2843F6B4ULL, 0x7F180ACEA45849ADULL, 0xEECE3D32961B79BDULL, 0x56A4BCA469F9DEA2ULL, 
            0x08737A7C2E793000ULL, 0x713A3A014CE76048ULL, 0x458D8C4506C9E8C9ULL, 0x80F7C277D54A0B08ULL, 
            0xEF936C208FE8BB82ULL, 0x5787C197D53A8AC2ULL, 0x983A87039EBA0A75ULL, 0x233BFC72045990E9ULL, 
            0xA310BB030E154025ULL, 0xA5F49CA952DBF3CBULL, 0xB6B86C89AC5C24E2ULL, 0x72712DAE3906D28BULL, 
            0x305A56E5EBFDE6F2ULL, 0x0952873B4CE05C5DULL, 0xF2AF1486305ABAFBULL, 0x66F3F3CD3181EB31ULL
        },
        {
            0xEE0E145DBA31B1FEULL, 0x0E405A8E6CE13FC3ULL, 0x4EF759D6F0CD7CE2ULL, 0xB13AF8C8C9941078ULL, 
            0x96489A78A19F8C14ULL, 0x902BC34C29FF0099ULL, 0x9EFB2B157F8E66C2ULL, 0x57046E81030B0E05ULL, 
            0x875236FCB0D58042ULL, 0xA7B4E561B7F5D772ULL, 0xD7FF1BE60767FB64ULL, 0x5AB2D0C8AF5C7615ULL, 
            0x2807432CA98AEEA0ULL, 0xD1563623CAEB7E78ULL, 0x0F3539FEBAD17302ULL, 0xD2775BC7492119FFULL, 
            0x47EFE811BD1B5440ULL, 0x072293960107CACCULL, 0x56860163B28E8B49ULL, 0x9C17C823DFC00C51ULL, 
            0xB82CDFE8781C89F1ULL, 0xF3BBCD2D08ADD61AULL, 0x1A70A44FBD4F9597ULL, 0x38FD4471532B6EC3ULL, 
            0x6499698D223E23C3ULL, 0xC5039C9D7B754C7FULL, 0x9867C1E75F81D519ULL, 0x2F8602CCDC2B483EULL, 
            0x71A312D65DAD494BULL, 0x0F03B404F901248FULL, 0x5EB2C1A11B775405ULL, 0x4827093CB71E7BDBULL
        },
        {
            0x249C621EE8C20C72ULL, 0xA4E2CC78476658A3ULL, 0x505475F4DDA9A873ULL, 0x5E25BE6258E14FC8ULL, 
            0xFC5E235553356249ULL, 0x3E7F8889C0A26E68ULL, 0xA023829EDE40F5B6ULL, 0xCAF7391A010985D3ULL, 
            0x375557279B918D94ULL, 0xA3317D7D1F7E4AD7ULL, 0xA2B72684CFC07842ULL, 0x63E6DC4EC3008220ULL, 
            0x2ABEFBDD7936FE58ULL, 0xBD063C3E75ED642EULL, 0x95B37EE50F2C1C3BULL, 0x1E1A34C20FDAF9CFULL, 
            0x22A0146580BA0E44ULL, 0x826CB1395BF53C7BULL, 0x5C24AD968EC95B58ULL, 0xF541EF99E4CEEC7DULL, 
            0x4E972747A8A0C0DDULL, 0xB7F2185BE3FA57FAULL, 0x5CD4D3F27ECFFC55ULL, 0x7066B943780D30C2ULL, 
            0x35DD484836904749ULL, 0x59F12D9AD9A297AAULL, 0xEC75788F9E5ECD7BULL, 0x7953607E5D1D0D75ULL, 
            0x54BBEF9F637BABD3ULL, 0x582CC834565D5268ULL, 0x952823FD20CE932EULL, 0x4B51058DF6480C08ULL
        }
    },
    {
        {
            0x231E57B74213D844ULL, 0xB8A3A17EBC11F2C0ULL, 0x21B41F93AECE6FB0ULL, 0xD5F3EDD433700D8FULL, 
            0x80BCE026C0E93109ULL, 0x53B72F0902DF006FULL, 0xD9E4A547927BA70CULL, 0x376CBF384D92B0ECULL, 
            0x525F645234630D04ULL, 0x2284084199533955ULL, 0x9590BE8654680CFDULL, 0x1B3BAE62CADA87E3ULL, 
            0xD056A07B67787588ULL, 0x889FB9B8AE8E6C4DULL, 0xBCBCFDCE4AB762CBULL, 0xAF4EE644877CC171ULL, 
            0x088003D179862420ULL, 0xEB7D2D42867FFFAAULL, 0xB11B31342050C1D2ULL, 0xB6B5A9CF7F8453BEULL, 
            0x6DE0E8B4C733BFA5ULL, 0xAB958653ACCA3634ULL, 0x31D0891DB1254569ULL, 0xA500ABF1A647CDF8ULL, 
            0xB3043E4D4E13C8A6ULL, 0xC8B1F7C652D93AA0ULL, 0xA0DE34CB9FC7C09AULL, 0x54DEFB8828349A42ULL, 
            0x3F258B3CBEEF2F19ULL, 0xD0D652EC3EF14590ULL, 0x45D05B766D0C66AAULL, 0x916600427BD3C841ULL
        },
        {
            0xB62575B6BECAF624ULL, 0x55E623CBDB352C4EULL, 0x7E669DF9B43DAE58ULL, 0x49AC2112CAB74F96ULL, 
            0x5F4560B3BACBF172ULL, 0x32AADB8C7926971DULL, 0xC0D89913D1D8C9DAULL, 0x3B3B38CA802790B6ULL, 
            0x5BBEA653529AEE67ULL, 0xD44BEC46F3B62673ULL, 0x93075248F42F3B20ULL, 0xF9D133864B5A2126ULL, 
            0x64459272EC23E793ULL, 0xC1C2F4A5A80731B1ULL, 0x368A072B2A083D66ULL, 0x1B1D136B4A546FB2ULL, 
            0x2BCBCFCBC253E55CULL, 0x5700E46F73EA51B9ULL, 0x6005C10829BB3B37ULL, 0x92B105D08ADC0C2AULL, 
            0x58A8E9692CE79D03ULL, 0x9E813E45FF7E61F9ULL, 0x30F415FAFDB92B56ULL, 0xB19E7A9D146585F9ULL, 
            0xDA2780C0CD6BECF0ULL, 0x2A88EFEF35AD78B7ULL, 0x6E401FAB23BAF48FULL, 0x8CEEABB281C12F1BULL, 
            0x1D62BBD1A66C019FULL, 0x76F497C0B57AB971ULL, 0x1050F8ECAB16994CULL, 0xA0EBF3B5416FB198ULL
        },
        {
            0x71DA39D149813619ULL, 0x8C8B4ED29C93C749ULL, 0xFD10B4B858B11416ULL, 0xCCC5FCD8A36A3805ULL, 
            0xC366B5DA41887B34ULL, 0xC6E433665A8570B4ULL, 0x9759C3EF6C61C341ULL, 0x30618F40C8C99A5CULL, 
            0xC79CE6F0B0BAFAB2ULL, 0x3AA65566CED5FFA4ULL, 0xBE5203CE8F72FBE9ULL, 0xC33EFFCDB97D0456ULL, 
            0x6B725847F8B2FA9FULL, 0x07CBE2A45048579CULL, 0x2CA3DECA2B0763C1ULL, 0x8ED1CCCAE2335CF3ULL, 
            0x311844A006EF416AULL, 0x7209D2ECD5F8B079ULL, 0x5F24BDF1809EBEE2ULL, 0xD28B38C02CA4AE06ULL, 
            0x90FA93E918D42BA3ULL, 0xC47CBA122BA3BAE1ULL, 0x33086260F7715623ULL, 0x62FE3F28F24340E5ULL, 
            0x07A8A6F5A927E943ULL, 0xFF53EEB74F3C4A72ULL, 0xC4C219AADA1E2C63ULL, 0x214D302629572B46ULL, 
            0xB31FA6D7761AD390ULL, 0xC78AD7118CAEFD38ULL, 0xD2EF932435B9E1EFULL, 0xA75D59CC553BDAC1ULL
        },
        {
            0x6615751C75301745ULL, 0x9B8B1B65F557A6B8ULL, 0x36CE2DB3EA9ADE2CULL, 0x495D2022340DFFC8ULL, 
            0x134698A3F58D1939ULL, 0x72665B012C35BDA0ULL, 0x207C4CF5927A45FBULL, 0x01FD4978D756E01AULL, 
            0x7A40777E6F8C9033ULL, 0xAD5F3E320DEE368EULL, 0xC90BE2FC304941D9ULL, 0xFFD7970A1ACB99D9ULL, 
            0x008B090BFCB6D9E8ULL, 0x73B2F041C9575968ULL, 0x1C635C00B3681DF5ULL, 0x99CE33D70EC40214ULL, 
            0x7F7AEF17E7C9ED88ULL, 0xEC2C55EC6793F8FFULL, 0xDC4798817B05844AULL, 0x76B9F05A87FD9E8EULL, 
            0x3F119D4CAB4311BFULL, 0x7DD195868DDE4DDBULL, 0xD84C27A17645BC2DULL, 0xBCBC641356612BE1ULL, 
            0xADD61E0A3B7FB80BULL, 0x4743A0F9CBCC7CB2ULL, 0x3294E2D5BEC5E4FCULL, 0x49BC6CA1F96A290CULL, 
            0xE8944BFC23008D16ULL, 0x8864884BE7FC01B1ULL, 0x80192CA54CD43D29ULL, 0xC1C6C30F13515AF9ULL
        },
        {
            0x8888840F1D8651B0ULL, 0xB0C2501E34254D8AULL, 0x2A52A1A4C8208CA4ULL, 0xF78394418ECC451CULL, 
            0xB6E516B0E57472CBULL, 0x90D8749712FA081BULL, 0xD46B386EFC07E104ULL, 0xCAA214F4822154EBULL, 
            0x6346920B78D138A3ULL, 0x7C5A0CAFAF50CBECULL, 0x996671D0B999AED5ULL, 0x8E3B4237876B643DULL, 
            0xC29858EDB38F6D18ULL, 0x19D76BF89FE95442ULL, 0x0A5EA7CBD568A655ULL, 0x2D3CF53A514370A4ULL, 
            0x874FB39BBF8E337CULL, 0xC6D34D6EED774955ULL, 0xFFC7E51B92F8670BULL, 0xA379674A22C2C5E7ULL, 
            0x4925DB2DAEDBB620ULL, 0x64D5D789624468E6ULL, 0xE3D94B306115C6B1ULL, 0xE2F43B571679ED58ULL, 
            0x09361DD2043B4DAFULL, 0x45D4BA05249062D8ULL, 0x665EF74B75387692ULL, 0x24735B058DC07FDFULL, 
            0x5C82157047F4CF39ULL, 0x83FD7E9899889C35ULL, 0x9D06A0F2EAD38FD3ULL, 0x1E5B0E67D6D986DFULL
        },
        {
            0x51E443BBE23FE377ULL, 0x10DBB5DA59BAF2EAULL, 0x38190F2771D2128CULL, 0x9B24EB3DA4356F67ULL, 
            0x91D0C96A7D109102ULL, 0x4EB9A80A8A0149ACULL, 0xAE01BAC8AEF6869CULL, 0xE511DDF9B36A01A3ULL, 
            0xAAE3D7E8ADED4F3BULL, 0x842DB36C1AEEB7D9ULL, 0xD01F852277563F1FULL, 0xAAC1CC0F5274D1C9ULL, 
            0x492EDB5FFB919EC7ULL, 0xFB783AA5345B5381ULL, 0x0F077FB9ACE10A23ULL, 0x833250D8BA3CABEFULL, 
            0x04D8E4E9EE8D6632ULL, 0xFAE77C67F147510FULL, 0x773D04FE6DF2ACECULL, 0x5076CDE2D3529205ULL, 
            0x322041A8CBD966D8ULL, 0x4B9FC64D96B0C9A5ULL, 0xB55AD5C6F22FD8D4ULL, 0x907EC6F7D0D39317ULL, 
            0x09084C5D197CFDBEULL, 0x461F089DD00B4907ULL, 0x28177EC44A67509AULL, 0x7BE38E5FCC6F5751ULL, 
            0x5094A80E0D0C3FADULL, 0x909F50F55D69EBE8ULL, 0x641676E13BC7E36DULL, 0xC606E1411AACF5E7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseCConstants = {
    0x6F6937FA1FE3F49CULL,
    0xAE9A59032E5EC274ULL,
    0x8E061FCAAFA99688ULL,
    0x6F6937FA1FE3F49CULL,
    0xAE9A59032E5EC274ULL,
    0x8E061FCAAFA99688ULL,
    0x0818D0D8563F5C13ULL,
    0xD370E35A9395199AULL,
    0x9B,
    0x61,
    0xAA,
    0x15,
    0x63,
    0x6D,
    0x4D,
    0x3D
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseDSalts = {
    {
        {
            0x43F66BE461369A49ULL, 0x399FAC3744C96114ULL, 0x0B5540EB49BE0177ULL, 0xC2F00462210F95AFULL, 
            0x5455282C1EA31F91ULL, 0x54E6B01692B82511ULL, 0x84C232168766D726ULL, 0xE5E7044AF8840B81ULL, 
            0x7BA4BADDFCE4414AULL, 0x61646AB7D637B467ULL, 0xBBB9192AEF162557ULL, 0xFC40C6E82E97B8E8ULL, 
            0xD1DE46C77AFF6F56ULL, 0x61C346A118213BB8ULL, 0xE5A6650E7765761AULL, 0x117A68A726DB0596ULL, 
            0xF73691448D34B07DULL, 0xA8626C236E86DA67ULL, 0x489518C8110028B2ULL, 0xAB1AA682CDFA3467ULL, 
            0x7127612355E00D86ULL, 0x005B7C78B8532C17ULL, 0xD33BD21CD24EAFC8ULL, 0xEF09F4E1204E6FADULL, 
            0xBD3B99B391218138ULL, 0x1E82F624CF75737AULL, 0xC9CAADAB3D5D35D6ULL, 0xE95D99C828B10698ULL, 
            0xE152E06E39573E0EULL, 0x440F480796337A43ULL, 0xCBB908E06C0AF452ULL, 0xC34709F434D4B24FULL
        },
        {
            0x8D384721F222911BULL, 0xD541C863F8B4839DULL, 0x1FE9804753014679ULL, 0xBF14A727D92518BAULL, 
            0x9CAFF6A2DAA5764AULL, 0x76DF5020ED6D9981ULL, 0x60C545B41D420655ULL, 0x03535E67A3FF584EULL, 
            0x297CF2102B255950ULL, 0x9E989973F1E16FDDULL, 0xB3E32E6EF4492D6AULL, 0x9CC3C8DFBF15F9D6ULL, 
            0x99BC9EB3790F138DULL, 0x4FCE2EBBB2FB0DCAULL, 0x3FE6F25380C0D327ULL, 0x910CF6074362A29BULL, 
            0x7CD3628A83A62239ULL, 0x23E186070AB91382ULL, 0xF6170C761757C9B9ULL, 0xB25A24F13562E1B7ULL, 
            0x363F80F0F1B9B2FDULL, 0x00BB0E2C717C32F1ULL, 0xD66E18384B2D5FFAULL, 0x963A44907A585F21ULL, 
            0xED4DFC7C351C7A4AULL, 0x7BF6443D5B26B659ULL, 0xCBA22A7A2E6CB49AULL, 0x4B69395AA31CF0A5ULL, 
            0x1056A70A73E7E7ABULL, 0xF4DEDF2158CFC2A7ULL, 0x67501CD38B3F8296ULL, 0xC1CB119970A15138ULL
        },
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
            0x48F561A725F1F2C0ULL, 0x320796D23F3BC92BULL, 0xB7AF38AA5E445993ULL, 0x909980D022CC3A61ULL, 
            0x82189B8EA4059744ULL, 0x70B5FBF5259BB4F4ULL, 0x64DBF7241E44438AULL, 0xFDEB67033E3A13A4ULL, 
            0x2295B600137E4F07ULL, 0xDECCF4C616E3A6B7ULL, 0x2A2DEF88DC323FB6ULL, 0xD381742041A8C23CULL, 
            0x6C5C1C350158AA7DULL, 0xF0F4DD26180FF4E8ULL, 0x6A60A7957992F1AEULL, 0x6EB844EC460932A1ULL, 
            0x6A5779D4EAC08E4DULL, 0x5CDA20EFD59739ECULL, 0x4E4497B9AFF07756ULL, 0x5BBA1BAAB14EB9FDULL, 
            0x35DD08803FF863E3ULL, 0xB0301DA0DB91774DULL, 0x1BF12781F8A75D7FULL, 0xB3E7AD94AA515D88ULL, 
            0x4A294EED8BB5A378ULL, 0x604ACF6B11B045A9ULL, 0x54BB9C487C9B95D4ULL, 0x8E7CBBC2C5E5BAB8ULL, 
            0x478A462782E65C4BULL, 0xF072AD08FF9B7266ULL, 0x0B1DD3A1075CB102ULL, 0x3A6D5664E4EF2CB9ULL
        },
        {
            0x9033CBD21564B0FEULL, 0x99168B660C094534ULL, 0xD40321C75EBE27A2ULL, 0x77A4EAF3E3A8CE8EULL, 
            0x11251BAF21D10B1BULL, 0x2EE943F3DCE78074ULL, 0x15E40D580E59CF15ULL, 0xAB987DBC34C519D1ULL, 
            0xDDD8F64FEBCA3057ULL, 0xA2DE0308A9E5135EULL, 0xC3C9A74191EE7905ULL, 0x86E47D3507EF9A83ULL, 
            0x21AE8E62A734C0ABULL, 0x4D72AEC3816CA645ULL, 0x5BA42473603F97B3ULL, 0x33A8B589AEFACE31ULL, 
            0x1231698FCFECA353ULL, 0xCAB60691684C5F29ULL, 0x2C04CFFC7BBB34F5ULL, 0x61E6944D01ED1C42ULL, 
            0x7798594E638D468BULL, 0x1097D49DB496E381ULL, 0x57FBB6D71C438C6BULL, 0xEAC52A25B320D161ULL, 
            0xDF8085FC7A21EF7FULL, 0x95FD04B69CD5BEB7ULL, 0x7252994F4923581FULL, 0x869D0134E0F786D9ULL, 
            0x5AFC1F7C56422F0EULL, 0xF1733F0B5BB60DDBULL, 0xD7F532C4396B3365ULL, 0xFF96C30C571E7696ULL
        },
        {
            0xBB7CC5A2B26C8EF4ULL, 0x2F60C5D992307A19ULL, 0x57424A140D044165ULL, 0x9CD38557D2C295E5ULL, 
            0x430D68F028D8ACAEULL, 0x5E0D77025C615AA9ULL, 0x3C7646A4F5379C2FULL, 0x694A1F61F3BBAF95ULL, 
            0x91488FAD4DAB0E57ULL, 0x89AEE6A8AD6F9AC1ULL, 0x1D67CBF18F0A3AF7ULL, 0x70E756C24E6BABB7ULL, 
            0x0341709A9D3B1BB0ULL, 0x1EBBB25CAB9C4B52ULL, 0xCABB966241814AC5ULL, 0x82B2406888B8AD20ULL, 
            0x5B3CEFE7DEC8833EULL, 0xFEC49E30E9041C81ULL, 0x7ED6A723416729C2ULL, 0x859BE0E80F9168CAULL, 
            0x062941659A298D1CULL, 0x12B1B05090BC58AEULL, 0xCD83E8AB9E71528CULL, 0x24A447F0E5B95937ULL, 
            0x79C287A950347682ULL, 0x7D3403410ABE41F3ULL, 0x5FF8898D243DDCA9ULL, 0xA85D32EEABD4169EULL, 
            0xECAE18F7CA3CA81FULL, 0x0CD20C073B680D43ULL, 0x3DE7F1D2F69BC6D5ULL, 0xC9F6F68AAFBC5729ULL
        }
    },
    {
        {
            0x746AA1C03E7AEDABULL, 0x7D975E9F9A69042EULL, 0xC45F8DCFB9E36BEBULL, 0xEFC853431E816A56ULL, 
            0x0226AD8497A0CEC5ULL, 0x74DAD665961E4EDAULL, 0xD5CB86FDD5FD2D5EULL, 0x3D714D3AB33B4D56ULL, 
            0x2C898E554C144E86ULL, 0x67A4DFF3BF87A669ULL, 0x00ACFC6AE8C5B00EULL, 0x2A2BE7FA52F860A3ULL, 
            0xB7498B3D7B341F83ULL, 0x20F1720FB9803BA8ULL, 0x18B1F84CCC77C8DDULL, 0x8092EE07641551F5ULL, 
            0x82D4D86EF772CDAEULL, 0x7FB65E2B714795BEULL, 0xE25BFF8A2F33E368ULL, 0x77A5CB9AFD77CD46ULL, 
            0x8172F06E2C1296A7ULL, 0x07A04FFC302A2317ULL, 0x6FBEF366FF1F83EAULL, 0x1C840774132568B1ULL, 
            0x564A7333451D6CD3ULL, 0xB0BC7286ED7E98ADULL, 0x5A8932AB6F7213D7ULL, 0xB0F631F5FCE5AD5DULL, 
            0xC9433BDA2E593315ULL, 0x5FCEE24ECCA5D3CEULL, 0xA79EC0D9952500EAULL, 0xA0F25E9AA0986817ULL
        },
        {
            0x609B1E8B89AC9CF7ULL, 0x42C28CF491FEDBD7ULL, 0x0DA11D1B77CE9193ULL, 0x37123B58FB5F68D2ULL, 
            0x4A892043B28AF25CULL, 0x4885BE2DF57D350BULL, 0xBBEA490EF8512389ULL, 0x23C7174D913A5B5FULL, 
            0xB2A6C9F0F5A735EFULL, 0x8716A8D7B118ECE5ULL, 0xB78C64361AB381FCULL, 0x9951175868EF8354ULL, 
            0xCB7D931E04B79F68ULL, 0x95971DCADF8698B3ULL, 0x90C9B5ABE57DAF8FULL, 0xBECFDDD80383DC0BULL, 
            0x76C15CEA28E9FEC2ULL, 0xDC8974BF10FE9054ULL, 0xA6400BD1A5F610F0ULL, 0x8EB33AF5B3472854ULL, 
            0x8EDB592D0AB25A44ULL, 0x759878FEEA8C3640ULL, 0x61BDF5B56C21C6ABULL, 0x26EFAAAB695A9614ULL, 
            0xD2DF839B3B79BACCULL, 0x72FC0F20878BDB56ULL, 0x341D0F77740381D6ULL, 0xDEBFACE9A1D1F650ULL, 
            0xE78B2C6E2E095306ULL, 0x03C637BF8EABC858ULL, 0x30A3DEFD88E3C8F4ULL, 0x10ADACCCFB03C171ULL
        },
        {
            0x0F94DC6B29AD3D52ULL, 0xFAF45118130968BDULL, 0x347E0BB1E077C14DULL, 0x5E022D9A5B8ED47FULL, 
            0x3679E081C46F33D0ULL, 0x4F26E1CB4FEF6A35ULL, 0x02EDA7CFA4D3CDBBULL, 0x1735774430B6C83EULL, 
            0xB6B587D8CA528A41ULL, 0x5AFFBA4B5F4935EEULL, 0x6E5E4749990783F3ULL, 0x7E805D1FD2ED7D3EULL, 
            0xE2088DEDDCE75AD2ULL, 0x71B2BCDE42A7477EULL, 0xBC4198E0AFFD68F6ULL, 0x11ECA69A01BCE088ULL, 
            0xBB27DC66FA0E780EULL, 0xF7CA642877EE14FBULL, 0xCE0AEACE3EA1ED94ULL, 0x37463B60D52E0EB9ULL, 
            0x05950961F4436B36ULL, 0xD6A44FAEE64B96F1ULL, 0x60AE3D1C71837443ULL, 0xB40717196B68FAD5ULL, 
            0x06C79ABB0A9003FEULL, 0x46D04801662E5CB8ULL, 0xC764357673FE68B2ULL, 0x4959A225AAD688FEULL, 
            0x8B4DC72DB9F8B815ULL, 0xFF373C44A52DE635ULL, 0xE12F3F1F102B0D61ULL, 0xC4BCE21F351638E3ULL
        },
        {
            0x6FAEBAB436C52E92ULL, 0xD67E365930685445ULL, 0x620FB0A7C960FC42ULL, 0xD216D289DD86C44AULL, 
            0xD16BF1579E4DFB60ULL, 0x82A5F5DB86114556ULL, 0x44DFB4ED39448107ULL, 0xE73286919307B8F5ULL, 
            0x6AA92FE1D71461DAULL, 0x50AE5797AFBD59C4ULL, 0x8D41E26691FD9712ULL, 0x551EA1945C1BA41EULL, 
            0x0C481FA165E9CA30ULL, 0xF8CE2CB9DDCDF013ULL, 0x981DA2D9E17849C7ULL, 0xD35D37B2A8BC2257ULL, 
            0x864DF36B3EED1A61ULL, 0xD6CDDBBD2E70627EULL, 0xE52D4382B5B6AB33ULL, 0x13FCF07135027378ULL, 
            0x5AC76DD9AD8EAE9DULL, 0x88BE5983270E699CULL, 0x4B3AC1189CB88F62ULL, 0xECF57A0613959982ULL, 
            0xB79AB2E8D28B9BB0ULL, 0x80860FA96F5810B4ULL, 0x03A304D577E875E2ULL, 0x19EC86703487A315ULL, 
            0x427EEC5281ED8841ULL, 0xB045ED024BC01E2DULL, 0x6F942993EB6BA619ULL, 0xD97E3D2358E058B0ULL
        },
        {
            0x49327FE567CF5E6AULL, 0x8E11D98E0E9B0A99ULL, 0x3A6499177B6B7997ULL, 0x1E90B714D1A6C120ULL, 
            0xE7F0AA9D2516B169ULL, 0x575870281B530F65ULL, 0xCB57AD5820357FF3ULL, 0x5C183B74D4D57099ULL, 
            0xC5D6BDDA7245F2E3ULL, 0x402F5A557E6E0B3DULL, 0xE63EB83876C35DF7ULL, 0xE602B016F6CBDF7BULL, 
            0xE0E5E6FCA83A128AULL, 0x2C591EB3BD3F269AULL, 0x70CFB883FD134D9FULL, 0x4E5F13BFFD92CCDBULL, 
            0x592C991D007854E2ULL, 0x407129BFD9CACE0FULL, 0xC5DBA65471F0141FULL, 0xE8EF616F7F8CC2F4ULL, 
            0x582FF0717373E1F7ULL, 0xF30E3E37FD60F853ULL, 0x363F8242CAE0521CULL, 0x8764D4721AE46004ULL, 
            0xB6C899A896C3D54AULL, 0xA6455CBB6914A858ULL, 0x0DC44EAE730C2240ULL, 0x4B8136A593B03A9CULL, 
            0x27EECC05820679DEULL, 0x7AB1FE55F7E4BD4DULL, 0xACE4C43219B1D612ULL, 0x2D4314B80221AF61ULL
        },
        {
            0x6C8BD48ACF4D124CULL, 0x74DD1A1DA3B4B119ULL, 0x6DD553D85CBAA2EDULL, 0x3307FC5AE1C8E221ULL, 
            0xB862ED5E001D4CE0ULL, 0x8FE91DDC4D4A9A8BULL, 0x22C1490A07CA6A57ULL, 0x068A67288543034AULL, 
            0x10627C5A40EC25D0ULL, 0xF35C55B20931E17AULL, 0x3EA23B0B788D4AC9ULL, 0xADB66E9E7FBA9F03ULL, 
            0x02EE4E3A6754BEE9ULL, 0x4609E38A4CEA9139ULL, 0x702CC6EF8040B878ULL, 0x05D112B3F9AB58D0ULL, 
            0x61CE8273363C6EC9ULL, 0xD16288370FC50438ULL, 0x97B5F33106A9A6F8ULL, 0x79CB73363320E044ULL, 
            0x70B2480A9B72E559ULL, 0x9A849D32911F0DEBULL, 0xE1CCE9E004DBF5D3ULL, 0x16856EFA87D8BB5BULL, 
            0x8618AF358F12BCECULL, 0xDC4AA5CDBF9F6C64ULL, 0x2998E6BBAEC8E758ULL, 0xB4C33F9926FBFC4BULL, 
            0x7E9B03BE393F5DBEULL, 0x7BFF4C19A59076F5ULL, 0xFF6CB1E309F6AA9FULL, 0x2773DD613119E12BULL
        }
    },
    {
        {
            0x04974DFDE296686BULL, 0x253490429981C829ULL, 0x74FFAADDCC533907ULL, 0x2C7ABF700B047272ULL, 
            0xA92EDE60989EB1E9ULL, 0x29D43CFF84DE1750ULL, 0xD49CF42790224A22ULL, 0x2868E6B4D14467FAULL, 
            0x15D15AF71715792FULL, 0x941408797A7A1F34ULL, 0xAD983885C6948C4BULL, 0xBD16CA0E969F0C75ULL, 
            0xE7F42416B009A800ULL, 0x9E10A196CB2F0AEDULL, 0xAFC6F98F49F3E927ULL, 0xC045F01C32954817ULL, 
            0x472E880C45BA0CE4ULL, 0x7951538E99591945ULL, 0x72BDDC98955FE8EFULL, 0xA43C22396CC9426BULL, 
            0x6447C558E4E2CB33ULL, 0x21AB1BE1148CAD5FULL, 0x8994DB713A7A1DDAULL, 0xF9FBE67F8A59E7DCULL, 
            0xE8A3C392DAAF6FBAULL, 0xA5157414A34F2A7BULL, 0x1637433520904E0AULL, 0xBB2D5BA5096F798AULL, 
            0x75D48A1E99C5771CULL, 0x37ABBF869B2B6232ULL, 0x5C1413BFB602174EULL, 0xBDEB517226CEC4F1ULL
        },
        {
            0x83838E88124FD253ULL, 0x113A0BC2B35C35E8ULL, 0x1674FD6D87374681ULL, 0x9B1DC3416ABC5153ULL, 
            0xEB627DC4AF2659FDULL, 0x7EF7790EFF9F386EULL, 0x5473D9ECA98AF950ULL, 0xB5659E61D7EC34FDULL, 
            0x63BE9E540611E756ULL, 0x921F9C09DD46C0C8ULL, 0x4C78C45EE9501B9AULL, 0xE3D4A9E79638E0DFULL, 
            0xBC8B7029AA750A51ULL, 0xBCF58EB2BF054B42ULL, 0xC62359D3C959666FULL, 0x52FB3546EB65E03AULL, 
            0x7CDABE79FFB158CFULL, 0x89EE1BD8669E851EULL, 0x7CD9F676AC9DEB4BULL, 0x1029DF115C5E7B72ULL, 
            0xB739653D314810D5ULL, 0x601A8E6BF253506AULL, 0xDAC711DBC5198B41ULL, 0x4FDD3B552A88B3A5ULL, 
            0x9E11274ACC10546DULL, 0x35E542429BB6F3ECULL, 0x68B3418EF362AB4BULL, 0x783D353729ACE4FBULL, 
            0xBD0847156978E4AFULL, 0x53AA06154C319C0EULL, 0xCE16D0A606D607E5ULL, 0x821B6C76269FA1CAULL
        },
        {
            0xA5A10401D291BBF9ULL, 0x77753328253CF87DULL, 0xF7345423209CF251ULL, 0x63B086F8A6D51067ULL, 
            0x497DED587E7224EBULL, 0x4540ECCCE48604D9ULL, 0xEA6BB985EE422005ULL, 0x930D97696CC089C2ULL, 
            0x46384FC31BA2F095ULL, 0x2BA5F39FBF2156C3ULL, 0x145D8CC5BF1BCA5FULL, 0xC5FB47954F3E4328ULL, 
            0xA0C10ABF347B2099ULL, 0x36B28FB0AF6D72A5ULL, 0xCF83890778B4B0BCULL, 0x08541F1671324DB4ULL, 
            0xB639B2FBDDE09C8DULL, 0x802E7C5B682EBD93ULL, 0x037F00C35B9F4EB1ULL, 0x4A411AAB1D109397ULL, 
            0xEC8A2623A1E7F0C6ULL, 0x122802637FA7EDB8ULL, 0xBAB99A4FD227FCBDULL, 0x1BCC0A1D14D3A114ULL, 
            0x6206E6E5E37E55A8ULL, 0x841F61939179C824ULL, 0x10DD62C487482FD3ULL, 0x27CCE78A80890342ULL, 
            0x08B01C5D6C5176CEULL, 0xCA1B77BD4D59273AULL, 0xF3E70A4576F4C4CCULL, 0xEF68ECFBC7E08DB9ULL
        },
        {
            0x5E356C95E1EBFAB6ULL, 0x834B6B6EBF4C5C0FULL, 0x9B130001FAEEFC95ULL, 0xCA995E46AB2E8DCDULL, 
            0xBAE345E20EBD29FAULL, 0xC6523681C67658B5ULL, 0x88FDF22518A4BC15ULL, 0x93FED596DD4533BEULL, 
            0x8A55BD7A31257198ULL, 0xDE4549368D250170ULL, 0x4498A8C87A926B7DULL, 0x333CA5AECF454CF9ULL, 
            0x6F19D899753A142CULL, 0x8C2C6931FD8AC1E2ULL, 0x5CD802B40EB39844ULL, 0x2C7DBC361CFE0071ULL, 
            0x878205C0E013FC92ULL, 0xD23B42F5D5653854ULL, 0x185BBD75C05352A2ULL, 0x19424C57DAB86AE6ULL, 
            0xE8E77138E9F78CE5ULL, 0x2C7398449ABEECD3ULL, 0x9201D988E780C4B9ULL, 0xB8B16CE5142A8E46ULL, 
            0xC1ACD787C30816DEULL, 0x23B15B273985FC85ULL, 0x1D2CFF5FAAC0B3E2ULL, 0x807A655034FF0977ULL, 
            0x3DA9E8F8CC2DA417ULL, 0xEDCB2F509A5F99B0ULL, 0x2DE476E1BCA1B955ULL, 0x552235EDA04305FAULL
        },
        {
            0x3034B212A9FACEE0ULL, 0x9F6C213731116A19ULL, 0xF522D7A7DE551B6BULL, 0x7BD409256521EF90ULL, 
            0x043CC313BD75E93FULL, 0xBEE7B11AAD945EE9ULL, 0x417AF165E0A0E72EULL, 0x414BADECDD4959C6ULL, 
            0x2D8AF112BEBCC55EULL, 0x1CC8D67642AD4926ULL, 0xBDC4574C1B8C145EULL, 0xE11DD9E6D95D2774ULL, 
            0xA11B2EA4E5B6FC34ULL, 0xB9F0A71166F769A3ULL, 0x447B770758C526A5ULL, 0x9EADD94FE3F45405ULL, 
            0x69CCB924B7701D94ULL, 0x40E251F043D26EC2ULL, 0x732E3A2500AE7786ULL, 0xA64AFB13BA4C0C88ULL, 
            0x405E27D4553544CFULL, 0xAF18CA621C4F06D3ULL, 0xCEDDF64F053F790AULL, 0x9EE311D40BE585BDULL, 
            0x04A6883A579A1D89ULL, 0x264F06AE6E37D70CULL, 0x267A88641A859CA7ULL, 0x7422BF908EB6A698ULL, 
            0x9D5476A69CFD203EULL, 0x75796DBBC7AE0DE7ULL, 0xBF25ED6C2A9AD7BAULL, 0xBAD2E4499D2DEDEDULL
        },
        {
            0x7D69AB80C487ADCCULL, 0x4E5EE3602EDF3F32ULL, 0x9C65B65B09283F6CULL, 0x0EC105AEAB864EBFULL, 
            0xF48986B8B41A1084ULL, 0x9FE5EB149E705E11ULL, 0xED807F2668D89114ULL, 0xD85E24FFE774D978ULL, 
            0x92C4E9D343A338A2ULL, 0x18BE0C36CA154AB1ULL, 0x73E240B12717502EULL, 0xBE800879C0625DEAULL, 
            0xA4F755C25B2EED8AULL, 0x5174D5063E8B3DDDULL, 0x9D18FBD18BC099C1ULL, 0xA5EB1672DEB0C630ULL, 
            0x015D3854608E440BULL, 0xD24A4CAC243DDA66ULL, 0x6D73EBF6164F81D2ULL, 0x5F999E99514A389EULL, 
            0x168D8455C41A3182ULL, 0x55105AF6B36D5C65ULL, 0x594A4B0433D215B7ULL, 0x1B398AE04723DDCFULL, 
            0xBC21B33FF362A6BFULL, 0xF061815EF29DD979ULL, 0xD8E8EF1C401FF46FULL, 0x0E1627BB00F11C6FULL, 
            0xF1E8B45D944991B6ULL, 0x5EEFE977884509C0ULL, 0x063F4A1FDDF62325ULL, 0x90C3CA65FD9510CBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseDConstants = {
    0x24D4647AC1F5CEA1ULL,
    0xF6C4A337DB768C36ULL,
    0x4193D390E0DA10EFULL,
    0x24D4647AC1F5CEA1ULL,
    0xF6C4A337DB768C36ULL,
    0x4193D390E0DA10EFULL,
    0xDDA107E929373E42ULL,
    0x84103C03F32FB643ULL,
    0x2E,
    0xBE,
    0xD3,
    0xD0,
    0xA6,
    0x67,
    0x72,
    0x21
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseESalts = {
    {
        {
            0xC0324A362B63CCB1ULL, 0x2320AD06A65AA268ULL, 0x32F86CCF531294D2ULL, 0x9B1815EB038101B9ULL, 
            0xD2FFFEB4FB4CDD38ULL, 0xE3A05DAAEFE84768ULL, 0xD1C9FAFF12B05C0AULL, 0x6452C913C5BE38AAULL, 
            0x11D2B8C20F79195EULL, 0x8DD1D45351299E3AULL, 0x6775A667A63D7A7AULL, 0xD924469CD1CF94B5ULL, 
            0xFC3036C398BB37E8ULL, 0x79EE4C20863A63E2ULL, 0xC9A7729BF479CC06ULL, 0x8D8DE3AE93BF3C92ULL, 
            0xCA357865A54877DCULL, 0x8F7573B0C38DAA52ULL, 0x0D55A7B11D58E136ULL, 0x0EB18490CE619E95ULL, 
            0x8654C9FC6066390EULL, 0x660B74809E895ED9ULL, 0xC4FB930487C9B65CULL, 0x1AD24C9BAA3DFD7FULL, 
            0x114D8EC9A7D262D4ULL, 0xA58E626F71CCDC61ULL, 0x4BC4670453A2A8ADULL, 0x46BCE3C617FF1FF6ULL, 
            0x4BC4DEBA7170F1A8ULL, 0x5050AD634A3D8EACULL, 0x7D52087EF31DF908ULL, 0xFC0BB11708D61543ULL
        },
        {
            0x0DFE2E6E40038E92ULL, 0x448D04952257A17CULL, 0xE15CD085C9B285E0ULL, 0x967494FC6C0239B6ULL, 
            0x2551E039222E86B3ULL, 0x9BA9EEAFFDAC3BCFULL, 0x054D2035414C72FCULL, 0x034ADE8C47C3D8B6ULL, 
            0x6999A177E65AB8D8ULL, 0x4A93F3928577D281ULL, 0x9CC05C4CAAB31935ULL, 0xCC2B3E1BC35B144EULL, 
            0xB975AB1ED00D4C40ULL, 0x5DAA720A1EA9F1CBULL, 0xA625387B5BDF804EULL, 0x5D62A22F57B3C883ULL, 
            0xBA2AF27C525DACC9ULL, 0x014B305507D21ED5ULL, 0x5D3F0861D0596122ULL, 0x7E1AA929CB76A079ULL, 
            0xFFA86B4886389CB1ULL, 0x7AF2D1A688BF85B6ULL, 0x836173D18A0D267BULL, 0x0EEC87FAE55A2670ULL, 
            0x102F7D50671DE895ULL, 0x64453FCBE76B249EULL, 0xB70BDE5BC677F41AULL, 0x23316D8A9DBA1B6EULL, 
            0xDE605B661BEB843EULL, 0x37D82334644A7AFAULL, 0x3A6BF64A0C0EB722ULL, 0x99E168D2A777A57CULL
        },
        {
            0xEA240528E2DAC574ULL, 0x169CBC3B9480F82CULL, 0x6BEBBEFAB730D634ULL, 0x3D76966F09C39C6CULL, 
            0xADF568364A22CEA5ULL, 0x1967D8D044802C68ULL, 0x59ADF3C0D19DE400ULL, 0x6A5801002D7FF662ULL, 
            0xB2A09D58DB58316EULL, 0x02ACAA60CCC556C4ULL, 0x02398338FB5CC909ULL, 0x7053B33B6566714CULL, 
            0x1214F83881A4BB16ULL, 0xC5361EBBA435456AULL, 0x87D0444572BE1F48ULL, 0x179D29AAE7B16854ULL, 
            0x7697FC071DCB286CULL, 0x5298E44F0705D264ULL, 0x3E6444CFCD2D1F87ULL, 0xFA94D6561B4C739EULL, 
            0xD214A47DE4D3BBC0ULL, 0xE06CE91D9401E9F6ULL, 0xAB6744E536998CDFULL, 0xFB9945C76784E85CULL, 
            0xCACED80FDB9BDBA7ULL, 0x217F63C748C38580ULL, 0x86F55EDD6C7C52EFULL, 0xE1FFC175DE666355ULL, 
            0x58C10945513D048BULL, 0xF6C4A404AA4B18EFULL, 0xE17E7F3231574C69ULL, 0x9F52B74090899DE2ULL
        },
        {
            0xB48EC7DDAF01E67CULL, 0xB9E75612717CBA65ULL, 0xF182A9C77E9F4175ULL, 0x895848512979CED6ULL, 
            0x1E8D6476213BA237ULL, 0xDE578A3D30A2DBFDULL, 0x6A00044F915C0EA5ULL, 0xE36BC0E097F4F280ULL, 
            0x725F03B1096759C9ULL, 0xD5729563B7119D47ULL, 0x535980B12A17A466ULL, 0x2130CB733A5AC32FULL, 
            0xF57062B8488B5594ULL, 0xD0F2B855A72C8589ULL, 0x1934E2523662F7D8ULL, 0xF41A414FB47DA885ULL, 
            0x61352D93316DDD52ULL, 0x9FE63113509B335AULL, 0xA82E37DDA1D59C35ULL, 0xE4D06990AB79B21CULL, 
            0xAABBCE00A0CB26C8ULL, 0xB79EED7A17344A26ULL, 0x2DC8A87D4226D42FULL, 0x0B2DA70366D4A7D4ULL, 
            0xD23AD35E93FAB6D7ULL, 0xBE2B0C003DF34553ULL, 0x7EF6D9B0F1D5C143ULL, 0xA4704A9CA38F5070ULL, 
            0x92775AB58773C687ULL, 0x3D3DDF0C18985DBEULL, 0xAB9ED49372EE188AULL, 0x62C94A23F910C671ULL
        },
        {
            0xDA3C8A931196E9E6ULL, 0x9851768C04F1A6E7ULL, 0x5AD615C0855F2D94ULL, 0x85355953DC657756ULL, 
            0x2E30A4B893992989ULL, 0x04563B5278CCECF7ULL, 0x6E9DDFB3C9806388ULL, 0x27D7664567174276ULL, 
            0x548E56A5CEE9EF48ULL, 0xA58CF8FDBF86796CULL, 0xBED657704A82A4E3ULL, 0xCBF2179F6E48D650ULL, 
            0xCBBED8A535CCB328ULL, 0xB0674AD419E07AB0ULL, 0x79C5CDCE5F436ADBULL, 0x24BDA89B0C9BC0DEULL, 
            0x86B8E352FC00486CULL, 0xF76483BAE07F7350ULL, 0xBCC04A8BC7937D34ULL, 0x5FDCE29A2DAF9AA3ULL, 
            0xFD13B586A3FE854FULL, 0x38041D4E626D3034ULL, 0x31DF5E67655A03E8ULL, 0xB4DB2FBAD0AF9539ULL, 
            0xD0E01525E67A5C12ULL, 0x6CDFF3BA5A5DAEBBULL, 0x2A59019A54F83CF2ULL, 0x3E06FB6541597B17ULL, 
            0xA1E8BB2BFA20891CULL, 0xE3AE5462BDCD23C3ULL, 0xAA710881F9AFAD7BULL, 0x7A1AA7545711508BULL
        },
        {
            0x54A509346068CEF4ULL, 0xD8092EC3FBA2E69EULL, 0x3A35D26017CAB53EULL, 0x5868FE2D6560DC62ULL, 
            0x58D67B07BAE5F717ULL, 0x771D7D5048FF4983ULL, 0x09763E8898182CE6ULL, 0x266A7E68E630B94EULL, 
            0xD059E6824BD4DFB2ULL, 0x3F434EC99C7B82D3ULL, 0x0A946CCC410FAE77ULL, 0xB9A16F98173FCB66ULL, 
            0xB4868687D1B84D76ULL, 0xCD19B835592CE6F6ULL, 0x6A4E3FB8BD645110ULL, 0xC2DD6AA34E143219ULL, 
            0xB56322756639C7D3ULL, 0xF78A5CE5B0529149ULL, 0xAB02192A0713FD96ULL, 0x5496BE7CD3A6E476ULL, 
            0xEF7A3E08DBC78274ULL, 0x125A7D389C9C300BULL, 0x0E8299CC8E486A34ULL, 0xE22E136F9BFA59F3ULL, 
            0xA03435661B18A81CULL, 0x0CEFE0F31C402E5BULL, 0x0A90FAE61D397C0CULL, 0xC34AEBBD3B4D0065ULL, 
            0x0D4B8A89E2FF0BB6ULL, 0xACF1772CFD2DD0C4ULL, 0x1727D62DC06FF7D6ULL, 0x5D43F96AF7D134C8ULL
        }
    },
    {
        {
            0xBF3C5343949B3A35ULL, 0xCE38CEA304F6E11BULL, 0x891AEFEA064F4A8CULL, 0xD9D4840903F0FFC6ULL, 
            0x386280511D359FD0ULL, 0x7EF8E9831DE3B172ULL, 0xCA1716728D77FEF7ULL, 0x85230CBD08D16C92ULL, 
            0x64FE108C5F24FBE6ULL, 0x134D4DC81BF7AB1FULL, 0x67C4FD81AC20DE79ULL, 0x51EBF5AB1607C113ULL, 
            0x7184EA3345CDF96BULL, 0xDB2ADBA8272A19A0ULL, 0xE017B7A9B5CBA1E8ULL, 0xF27E7FEDCA9C55C2ULL, 
            0xC353AC0AAECEF033ULL, 0xB31949983F7F9DCDULL, 0xE854E7E2E5F9CE97ULL, 0x8B5B580D04930E86ULL, 
            0x5F0558C6B66F8FEDULL, 0xE588F6C94788FE45ULL, 0x203BB86CF6E8BFB8ULL, 0x0D70E1BCA7F68008ULL, 
            0x2B29743C3BA43F3AULL, 0xC7C7E176464E10F3ULL, 0x4E62E251D847F013ULL, 0x200D4A5CDD5CDD47ULL, 
            0xE603A4EB737F03D8ULL, 0x9725716C41E2E608ULL, 0xB3879044FEBB791FULL, 0xC35D355902DE662DULL
        },
        {
            0x2E01880F3A531097ULL, 0x048CBC90421CEEC1ULL, 0x9E67FBCE5BB4C804ULL, 0xF9B537BA1A15F887ULL, 
            0x6EA0AD275BD2C54FULL, 0x67F2518FB1A9F4E2ULL, 0x4E85D5502E533986ULL, 0x97845CDB9603BC9DULL, 
            0x71FA337C91DC1B62ULL, 0x2BAF444F59B272A4ULL, 0xB5917641EA2850BDULL, 0xFDD96E96B6DB96F8ULL, 
            0xC775DC15047A4FACULL, 0x917049902E5F7CABULL, 0xCB326CDA605816C9ULL, 0xD4E2FB2DDE3CFF56ULL, 
            0x16D05001F845B349ULL, 0x1E1F85DF2D17B798ULL, 0x38B1E697311CDDC9ULL, 0x57EFCE3F2ACD3477ULL, 
            0x144D91C06534AE63ULL, 0x95BA31AC141BD2F4ULL, 0x6D6DF7449AEAEA99ULL, 0xA78ED8FA4F2986FBULL, 
            0xC5FAD587F617DC85ULL, 0xC30D9EC0F5F9FC68ULL, 0xE417628EFE7B2E8DULL, 0xB6E48D89AB27FCE3ULL, 
            0xB7B33B5D3AD913C0ULL, 0x1EB01D95EFA51B27ULL, 0xBC63E15BBFD2882BULL, 0x092D3CE227F92930ULL
        },
        {
            0x63C17715FC7082E1ULL, 0x2D379FA69F13CB51ULL, 0x21E297DAF5765B63ULL, 0x21E9D01C3D511DAAULL, 
            0x3CE7CE535BC2F254ULL, 0x1BA92926C3164532ULL, 0x69EB7C273CD8773FULL, 0x7A2B21FBA903FE90ULL, 
            0xABCEFA1AEC3C6E44ULL, 0x4BE8C65BF613201CULL, 0x7A2BD37C20E756AAULL, 0x0638C1623A0A11E1ULL, 
            0x36F73C7BEE8D3E80ULL, 0x81DAE3111C9B625BULL, 0xFA4174D4E4F6D984ULL, 0xA1E89D03C40F06F7ULL, 
            0x11517F126F670C2CULL, 0x7B89BA44C0A316D0ULL, 0xC3D508495722B93CULL, 0x505C4A5342E15A53ULL, 
            0x57C081FAEA4B8E51ULL, 0xB0A4E8F873118C09ULL, 0x63EC27BFDE43E1B4ULL, 0x9D4D875EE122D8FDULL, 
            0x9589DCE3E80E84E9ULL, 0x9065BB31CB1A1390ULL, 0xB99756C29DEA3F74ULL, 0xAF72807BD70B7281ULL, 
            0xAA706F8091F2EAF2ULL, 0x0550E4F0BA0EDA56ULL, 0x7104A0C40DD266BFULL, 0xCC7E188957B71B51ULL
        },
        {
            0x3398EF19764B1E15ULL, 0x99142AA83B89CF8BULL, 0xAAA1E748F19EA990ULL, 0x7F6036E73F740928ULL, 
            0xEC09705B12C09BF7ULL, 0xFF47F04111CE4255ULL, 0x01E1ED8637AF557BULL, 0xAD540AA941C4A8DFULL, 
            0x46719E229959EE08ULL, 0xA6D2B696F3C154FFULL, 0x9B6CC88FE8958C62ULL, 0x754CB750C7D9075CULL, 
            0xCA155C220E83E7B4ULL, 0x374BD50C72C23ABBULL, 0x633280374764F537ULL, 0x055D7BA126CE09EFULL, 
            0x92B137C821519A10ULL, 0x337A1EB2EB95D497ULL, 0x9A1C2814567BF2EFULL, 0xE886051209CE02F3ULL, 
            0x5F40E553BB2DBE19ULL, 0x170479AFEEFD1C99ULL, 0x86D9999B7D913293ULL, 0xABDFAD7BDC12FC43ULL, 
            0x729F75A6AD348918ULL, 0x30465E94F954A1A8ULL, 0xEBF6C188E645C8EEULL, 0x51FF70D4C42954FAULL, 
            0x6DC3C6D496B8CE7DULL, 0xCAC854D8E3CF48C8ULL, 0xDD581202F15CAD35ULL, 0xA8CCD5E9963AB244ULL
        },
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
            0xE3BD78D652902181ULL, 0x1FCC8276E221C3DDULL, 0xD26B380C46C72209ULL, 0x0638C6346BB9FD39ULL, 
            0xEB4B0C2E8F520020ULL, 0x0198BAE3C21A653FULL, 0xE2D20CC496B34451ULL, 0xC96EACD69D201BE4ULL, 
            0xEB1DBCC6E3AA57C3ULL, 0x9D938F3FFAA28508ULL, 0xBEF8B539BD2DCC95ULL, 0xFB267163DE5D2CBDULL, 
            0x8DA4A4FA1A7AC044ULL, 0x7BE199E67148D46FULL, 0x3F00620DD0595B85ULL, 0x48E5EA855253143FULL, 
            0x80CEF66443548B5FULL, 0xA8E763AE1C172337ULL, 0x1257072759B82C9FULL, 0x9D34DD9E768BEC90ULL, 
            0xA7F72A50B0C1C9A6ULL, 0x463E5165750C1867ULL, 0x5EE0A760436B33E9ULL, 0x76E713AF1C5CBD96ULL, 
            0x6D21F02A3668D77EULL, 0x5F03C6BC6A07252FULL, 0xDD510F9092F79194ULL, 0xAB82871853AD2915ULL, 
            0xCE8F8F4B5036424CULL, 0x9C228CD498826951ULL, 0xD9E699C4E9100978ULL, 0x034F8ADF5DA23751ULL
        }
    },
    {
        {
            0x79405A447E3732CCULL, 0x3B6F85DDB0FEE2CAULL, 0x5A6AB420C6ED63F8ULL, 0x2C717C47532AAD9EULL, 
            0xA6C8EF82D9F8C22CULL, 0x3F22408D8E09A5FBULL, 0x1A25BA2CB8D52071ULL, 0xCF29DBA267149D6EULL, 
            0x78F6830DBEC60C3FULL, 0x6E3FC0F32CE89BF6ULL, 0x18040622A505424EULL, 0x6A972DAE3F33C7D4ULL, 
            0x8B8F3F6036FD8DB2ULL, 0x8E60E79940EBF8B4ULL, 0xC895613B8C9F6795ULL, 0xC887F87D1979D9EAULL, 
            0x96B5A47FE0858DA1ULL, 0xE74F89B8FEE77E3CULL, 0x184108EC5C0D3A6CULL, 0xFCAD3639DE999394ULL, 
            0x81675D7ADB09A63AULL, 0xAD1847DD1046A57BULL, 0x773927DB3A1CDCABULL, 0xFCB94F55CC5010D0ULL, 
            0xA9455A643F49A970ULL, 0x8F2C1664EEB670BFULL, 0x5B624CE91368A4BDULL, 0xFC17FA7BD07C7773ULL, 
            0xF3028329F1DA1AFDULL, 0x1E9FCC9E9682FF9EULL, 0x5111C3EA6B82C312ULL, 0xA43145F47BE45025ULL
        },
        {
            0x0A63EA0EFCDEAF06ULL, 0xE54869282CCD754DULL, 0x212CE17FCFEB7569ULL, 0xC6228942A219D969ULL, 
            0x7A77B873537D4378ULL, 0x6E8961EC36BD2EDEULL, 0x001E53074D01F0C7ULL, 0xA3B4C8B5EEF180D0ULL, 
            0xB5C7A6FA76ED6967ULL, 0x32A1C5AFA66BC1ABULL, 0x2854F5B26E28CD1BULL, 0x6870091A1084783CULL, 
            0xF519A5678DD0B327ULL, 0x451D39CFF43B186BULL, 0x76A3B0EB63B4DE27ULL, 0x30A6F4F195613639ULL, 
            0x648C31CE05C602B9ULL, 0x002606CC1A3313A8ULL, 0xE330B78ACA5087D0ULL, 0x34530413CBA4A804ULL, 
            0xECD1BC1A50A2D6B2ULL, 0x9E42C0D04E1450DEULL, 0xA4618FBA2B963CD6ULL, 0xC788B222EBBAEAB1ULL, 
            0xC98C6BF1490F7D38ULL, 0x12686BF432B54094ULL, 0x312876DDA13B2936ULL, 0x9E86F4B8292A4EC5ULL, 
            0xA5A0B2D344E7D286ULL, 0x98497B5DBE9F2030ULL, 0x32DAD8073E170043ULL, 0xD8FC4DEEED50C6CDULL
        },
        {
            0x3ED5C649B913C5F9ULL, 0xA9701D6604983134ULL, 0xB54E585041CF5D84ULL, 0x2AB7F0B5865CBEC9ULL, 
            0xB6F8332340C24EBBULL, 0x67ED415B7B6131C4ULL, 0x1ABACDAABE3F32C1ULL, 0xC7DD9FCAB66D5C29ULL, 
            0x24FB7041688EAF3CULL, 0x6300938FB72CB764ULL, 0x22884401F2EF46C0ULL, 0x474AE6FA69CDD155ULL, 
            0x144EB48E3924BC1EULL, 0xA7F9AFCC7BDFB245ULL, 0x51A48B4E8C1FD42DULL, 0xDCE551AB95A40E87ULL, 
            0x2423ECF5091AA0DFULL, 0x12E4E12078AA291EULL, 0xC4A0B66C8F821CD4ULL, 0x0E3ABAB31CD66958ULL, 
            0x8909DBF8F95947EFULL, 0x8F1B0C0632510E99ULL, 0x1484BA12CA5EE6E6ULL, 0x715A915232C18B3DULL, 
            0x5CC2CA1063EF84FAULL, 0xC7166F4A85A283D5ULL, 0x886F1E4C07362D01ULL, 0xDB31171BD8178210ULL, 
            0x17183C16FB75EC46ULL, 0xF934454814DC2F42ULL, 0x50303C63A7B833A2ULL, 0x11EBB433248FBD65ULL
        },
        {
            0xCA227CD9E43928AEULL, 0x0502AF55FF780CCCULL, 0xBFC9BB1C80347840ULL, 0x3C2142F960F97EB6ULL, 
            0x6F9CE35862AD4A3EULL, 0xC87031931C82A022ULL, 0x66E36F42975C83E9ULL, 0xA00550747EA273F7ULL, 
            0xC17650F917F2C547ULL, 0x37AFD3BC26A6C564ULL, 0xF454267981562EF2ULL, 0xAF3665DEB1030369ULL, 
            0xBD8149B18D4549BFULL, 0x8D6D5D94477FDE7FULL, 0xA01323987FA80180ULL, 0x0903AC5728E0C2BEULL, 
            0xE548FA4A1311A9DDULL, 0x1FB6EBA1C962D4B3ULL, 0xE8157BAED1C69D53ULL, 0xA7AC2C32770BA005ULL, 
            0x700925E055454582ULL, 0xCD112E1D7B0750F4ULL, 0x3FAED8D4767B47EEULL, 0xED8A53D722C7C054ULL, 
            0x6D59A3F424A27DD8ULL, 0x649C0FB259FDCFF6ULL, 0x76B4D8F8F10ACD2AULL, 0x8998B874A1BB8A63ULL, 
            0x7F3F663553B2A6F1ULL, 0x1EFC91CC6D1FE9A9ULL, 0x36D8BB2DDA01990CULL, 0x06FBD347458B2615ULL
        },
        {
            0xD9ABEC225D1EC3C1ULL, 0x85F0FE6473781C9DULL, 0x0DB0A8D7D6EA4D11ULL, 0x5FD42611A26B337BULL, 
            0x6404A9435ECEFE79ULL, 0xE3B0B5CBA02A2F92ULL, 0x565116171AE3FBF9ULL, 0x31979E9B1E38A3C4ULL, 
            0xD59A8C5AC69D45A2ULL, 0x747D6FE5C7FC612BULL, 0x05945DFEFD433755ULL, 0xE89F44182E4F7C74ULL, 
            0x606600B3C699AE39ULL, 0xD0163A8A24E3C7CFULL, 0xD5EEA13AD81FCF56ULL, 0x184A00846F02F66EULL, 
            0x16AD99E5EBF6DE1CULL, 0xF419173F7B44E6D3ULL, 0x4CF39AA1524BC025ULL, 0x25C3E61472DAE22FULL, 
            0x0AADA00E0043528EULL, 0x64E77A5E6FEDDCA6ULL, 0xD74FFE5E80E081B6ULL, 0xA4B18FC5432E430DULL, 
            0xB7EFCFD1C8C43A32ULL, 0x2AFAC60C7B7355B4ULL, 0x0B6942ADAB7B0F06ULL, 0x9552DCCBFAB29A70ULL, 
            0xE8572C15BB4A1C3BULL, 0xD3561F592392C3A0ULL, 0xAB207CD94EF3550EULL, 0x243E7EA36A9C170CULL
        },
        {
            0xA26BF0F660A571FCULL, 0xE3353CAB98713596ULL, 0x5B864FEDA939CA3FULL, 0x964AB2C1F032E120ULL, 
            0x0B1C8DCD5290F532ULL, 0xF7CA759875C8B747ULL, 0x2C0C3F9B5789393CULL, 0x4A4A6F03A2242B3FULL, 
            0xCF3174E68521DD5DULL, 0x8E54C641B6B25B2CULL, 0xAA2DDC4146250593ULL, 0x646C83F954175E0EULL, 
            0x20872545EC98126CULL, 0x88B2454A30D2D301ULL, 0x67E1EC56B4D8DD6AULL, 0x0591F0E04F0C69D6ULL, 
            0xEA518073EFBE0E06ULL, 0x07491A8878EEBBDDULL, 0x08B166A1CF14A8FCULL, 0x4243E85DDD465EF3ULL, 
            0xB0B24A8B013C1093ULL, 0x63CFA455404AE04FULL, 0xEBE3FE538C9A0487ULL, 0x9135EE3B52700C86ULL, 
            0xCF556A9CBCE3CE75ULL, 0xD05795AE3E44A30AULL, 0xADBA07D36A1B2483ULL, 0xDFED64BCB8C9152DULL, 
            0x0D4BFB4F1354E69BULL, 0xB039862FED7B8730ULL, 0x19F91BB0A07720A0ULL, 0x3391A71C8115DC8AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseEConstants = {
    0xE031FC1461FE5835ULL,
    0xFAF4905751600714ULL,
    0x56BCD93E49CF42BDULL,
    0xE031FC1461FE5835ULL,
    0xFAF4905751600714ULL,
    0x56BCD93E49CF42BDULL,
    0xD1C981B9A038D753ULL,
    0x4432B1229338D7E0ULL,
    0xFF,
    0x1B,
    0x8F,
    0x63,
    0xD0,
    0x37,
    0x0E,
    0xC7
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseFSalts = {
    {
        {
            0xA035B10AECBA58C3ULL, 0x02836179CF3A1D71ULL, 0x1527A8FBB911151FULL, 0x31A843D159914149ULL, 
            0x9A805082AFCA1F75ULL, 0x7A5F1D7FF4583CF0ULL, 0xC44A06C15A857B88ULL, 0x308667B4EC9F7DABULL, 
            0x72266F89342BA294ULL, 0xDCB9E8126796AA10ULL, 0x9DA6491BA1744FA9ULL, 0xAB7744B7D69B7C97ULL, 
            0x0C798314BEB46BC5ULL, 0x570326384DFF8FBDULL, 0xF71CFB73ADDFBBBCULL, 0x442EEB7B1824DE66ULL, 
            0x5C290EF2A391DF10ULL, 0x0E2433A453D54E7BULL, 0x0EC534411B4C0471ULL, 0x79DBEC4BA884E8F3ULL, 
            0x59FE04E351F7F107ULL, 0x311E734127C7059DULL, 0x5586D171693B6F9AULL, 0xB12388FB42684DF2ULL, 
            0x57115E50EA86853BULL, 0x1CE3DCB36A607DE7ULL, 0x0CA4E34B1C4E1E47ULL, 0x4040FCEF36E5BE24ULL, 
            0x3FEA6BD9CF178896ULL, 0xC06FC37E2E9E57BDULL, 0xDCC21456987FF3D6ULL, 0x37D3FFE91A377F98ULL
        },
        {
            0xF0FEDC3E1231D540ULL, 0x8C67D234C36E8908ULL, 0x6AE699C4D3903F53ULL, 0x7DA425F6304EF12CULL, 
            0xAFC824CACD758116ULL, 0x79B15C2D40F7BA90ULL, 0x4243AFEFD962790AULL, 0x7ECDEAB05D2417B8ULL, 
            0xAFA2C63E0B424F22ULL, 0x977575D59D946D15ULL, 0xC96744265E6B60B3ULL, 0x19EA59AE6DE814DBULL, 
            0x1AF673FEB6CDEB34ULL, 0xA14D0B8D7253C371ULL, 0xC22C7ED464278993ULL, 0x90385E9111F8D4B2ULL, 
            0x06AFEA7AD7DB5E19ULL, 0xAFB19B8174F6941DULL, 0x675EAD4DEC2C9FEFULL, 0x1240BF5DA59AACAFULL, 
            0x3BE59FBE7C3CAB67ULL, 0xCC0542F87409DB84ULL, 0xA5D2F7F2847ECD49ULL, 0xD5EC9350410CFAD4ULL, 
            0x66C65BC74CFCAB20ULL, 0x403EFDFA46299D8CULL, 0xE8F4B210C1168A6CULL, 0xE480B12B32B9B392ULL, 
            0xCEDCFCF979BC5074ULL, 0x1D208DBB673D4B95ULL, 0x0F4DB13E03FBA453ULL, 0x8A6766CA14381DCCULL
        },
        {
            0xCD61267EC4BEEC1AULL, 0x269F475C4BE1F3E0ULL, 0xD702AFEC0BC5C267ULL, 0xB23B6746F79C9A5EULL, 
            0x0BA847BA01220A91ULL, 0xFF18248F24FFE071ULL, 0xC0933565A8775A41ULL, 0xEE689ECE3A966F76ULL, 
            0x983C7D2AC63A10A9ULL, 0x7FD076ABFB1E6BBEULL, 0x4958CCF846FBB9AEULL, 0xC89483FA79AFD4A8ULL, 
            0x4EF239A669D858F1ULL, 0xE5AE6E48EAD72C75ULL, 0xBD87DEC3FEC6F9C0ULL, 0x4B9427A4E74B7364ULL, 
            0xCBB413E5CABBF3C1ULL, 0x9915A7636FDFA98DULL, 0xAAC4A673B601F043ULL, 0x351A697F848C4638ULL, 
            0x78BF851B47960333ULL, 0xBB540835F5A6BBBDULL, 0x782DF5AE77D4AEA8ULL, 0xF4D0EF77DED84087ULL, 
            0xD0A9A25EB94F0286ULL, 0x33946A973906E1A6ULL, 0x2E43C9C68A5922BDULL, 0x6E5C2A74BDB4D0BBULL, 
            0x22C7DE3878D22F32ULL, 0xB55AEE5CF07AF9A3ULL, 0xD51D6FDD1C935BA0ULL, 0x1AC598154A170125ULL
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
            0x38E234022F5ADD1FULL, 0x848C7F2CB7BE5FADULL, 0x869E74B472FF382FULL, 0xDAFADB4F958808CDULL, 
            0xB5F270140FB30C24ULL, 0x06D351F62B092FD4ULL, 0x1AB665D6CC379DFBULL, 0x9540DE612CFE78FBULL, 
            0x775511BCEDAEAB4AULL, 0xCBA244CED7A32610ULL, 0x11D7D35E7E0F47E5ULL, 0xA859597E90BB64AEULL, 
            0x0E002BAA34A99641ULL, 0x0A7108601A5E1444ULL, 0x40639F727CB15779ULL, 0x1A0B4E030474CAEDULL, 
            0x3092673C333F2861ULL, 0xCD6DE56BDB08C410ULL, 0x2A34938FC431298DULL, 0xEC8405B2655A26B8ULL, 
            0xD883BCB412DB97F9ULL, 0x488CD3E9E968FAB6ULL, 0x2F62E033B520AB5BULL, 0x05162312CCC1B5A0ULL, 
            0x1AA3ADA5603DF6D8ULL, 0x971691AB36C16499ULL, 0xD827A702DCE44FF8ULL, 0xBEBEAF56E08283BBULL, 
            0x98A46C12114DA31EULL, 0x85F2BDEF5B5F53FDULL, 0xDE42F8A9BBFFFB27ULL, 0x7CEACB12DA91F741ULL
        },
        {
            0xFBA4DB3E1D421276ULL, 0x892DD9001BA2BA32ULL, 0x8D8A15EE13BCFDA4ULL, 0xD23D36A99AFFFC5EULL, 
            0x4F1A7071CA5F069AULL, 0x18AB3D8414F04E8AULL, 0xC9ED777BD935ED2EULL, 0x40C23620E12F92ECULL, 
            0xA52B53B01FA6C9E2ULL, 0x8A56824F87A409F3ULL, 0xF422ED4C9C6A1FEDULL, 0xF00611216B62ECD4ULL, 
            0x5E37B2BE53F956C5ULL, 0x5DF1A9D42271FB31ULL, 0x44E63872BBCD8700ULL, 0x5EAD8FAB30FACDAFULL, 
            0x26B09E8CDA9F6308ULL, 0x17A92F42485A4B67ULL, 0xE73DC9D6994022BEULL, 0xEAE392DD6E01B63AULL, 
            0xC3E632AAE9736991ULL, 0x84CDC66B14F116CFULL, 0x4085D288485E0258ULL, 0x6DEA24BC37199955ULL, 
            0x5D95AEA8BDD062B4ULL, 0x4581AD5B8D08EBA1ULL, 0x815CBE003BE30DBDULL, 0xEC6D195F00246BBAULL, 
            0xEC2B5825F05949D2ULL, 0x3C9DACD5FC75458BULL, 0x5B719FBE65146AFEULL, 0x19D350F5E638BEA2ULL
        }
    },
    {
        {
            0xE02BDF2C15B9380AULL, 0x31898CA8DE7F7DE4ULL, 0x085E24861CE552F8ULL, 0xE6BF6382ACB62144ULL, 
            0x522AB30D31E165A0ULL, 0x11EDB5C9EA182368ULL, 0x7DAB23596199F047ULL, 0x64F137B462E56411ULL, 
            0xE372CB1AC5159108ULL, 0x7E7CB65F90B5E825ULL, 0x2A8E9F4CEDC219ADULL, 0xC847652D8F931B30ULL, 
            0x2F84C4C20467FEB6ULL, 0x426DD7AB73679AADULL, 0x0196E97F5402584BULL, 0xD8B74C754BFFADCEULL, 
            0xBA12E70CB1394A8EULL, 0x803385A724F9AE23ULL, 0xD2284751300F7BE0ULL, 0xCC77915E2B125566ULL, 
            0x377C5BB29BCB481DULL, 0xBBF9CE40C8205A18ULL, 0x45A1216DB4E6A733ULL, 0xEDD8462CCF412195ULL, 
            0x73120A1D519B5A39ULL, 0x3DD2954E774B6C57ULL, 0xD1F1DA4C1F56DC2CULL, 0x2A74D9D922BF741DULL, 
            0x6880D7433F920705ULL, 0xD10764D5E191F919ULL, 0x4B519D0CC2FC7EDFULL, 0x4DEF6ACB6E4A2AD4ULL
        },
        {
            0xF859844808040F5DULL, 0xE637F7F7DD44BC87ULL, 0x63372E20A76C5AE7ULL, 0x242F0D46EA1A2EDFULL, 
            0xC8565891AAC81A22ULL, 0x4B797A4051E91DAFULL, 0x6CF351A032FE7AE4ULL, 0x9625A811FC456687ULL, 
            0x45FA188A86322AE7ULL, 0x789534BB6565D4F3ULL, 0x6A561C130F8ADFA4ULL, 0x247303423AAEEEA6ULL, 
            0x2EF83DA29D0D4319ULL, 0x07C3F726277B7CEFULL, 0x524A0CA6ABF50D0EULL, 0x0FC0350B4257CAADULL, 
            0x0FEA2E9EF994AB55ULL, 0xE64434EA4053C9F4ULL, 0x29173FEA643692AFULL, 0x742B2021D70324E0ULL, 
            0x9EEAB36FA6EA3F83ULL, 0xFF446EAA726C3F3CULL, 0xF6587AEDBB1D8F6EULL, 0xF25AC7A274915371ULL, 
            0x32B7E613348D127DULL, 0x9EB81D939EC64895ULL, 0x549AE5128C60B075ULL, 0x209E214EEA4B93A7ULL, 
            0x70FC01692956329DULL, 0x03D5CF463FC29510ULL, 0xF4A85250745B5DDAULL, 0x52B583A4E1F17D10ULL
        },
        {
            0xA2CBF122C8356199ULL, 0x63C902E2FD711395ULL, 0x1F81E2372D091DC5ULL, 0x59FBA28498ABDD65ULL, 
            0x11F84BAF1C3BBBBDULL, 0x2F3CDF0A84A88BE6ULL, 0xBE06495BB8131150ULL, 0xFCCE08D471978449ULL, 
            0x64E76FAF9A1F8DBFULL, 0x67E6C2FE94F4D5C3ULL, 0xDFEBF9F6EB78E3B8ULL, 0x1367DE293F75A9A5ULL, 
            0x02B7678C18736873ULL, 0xA671A71AACB11B21ULL, 0x3FA15A1FC183D1C8ULL, 0xC3810BFB59036877ULL, 
            0xF3453052B1B9555FULL, 0x1C4054D9DA64EB06ULL, 0xD2980D380BB268FDULL, 0xFD10E1D62018D497ULL, 
            0x9796EDE11BD70773ULL, 0x85BFFD3FAB6DCA4AULL, 0x36D17B38435F89BEULL, 0x5A6C45B2F747AC1FULL, 
            0x26C96D915B751D5DULL, 0xDD7059962AA97507ULL, 0x402A4B013FFAB3B8ULL, 0x8FCEAE73785BFA3BULL, 
            0xF0DCB9D5A317C338ULL, 0x03164AD029F4FBEFULL, 0x8F30CE4594823C59ULL, 0x7D6EF569EB765752ULL
        },
        {
            0x418D2216FBBDE41CULL, 0xDE8C6E53D3D2728EULL, 0xF9EA5DA50FA24378ULL, 0xB5FB41859BCC1354ULL, 
            0x4544D807EDD4DF05ULL, 0x989A4BA73E5CE353ULL, 0x7ADE61CD17C6066AULL, 0x621C1661C3F5E98CULL, 
            0xB3BDBF39CA7F9392ULL, 0x2D93EDADF3E567CDULL, 0x90456F2A44D0BD7FULL, 0xD9B284B90D67D3B2ULL, 
            0xB554396708769605ULL, 0x19C933C46CD30E95ULL, 0x021B27E5182D32FDULL, 0x535159CAAF7ED9C1ULL, 
            0x1D1A026F88978294ULL, 0x8280FB06CE4F1B1CULL, 0xEA362993EFA75925ULL, 0x719AFE7F632F42F8ULL, 
            0x9FDB031D5538C245ULL, 0xE73DFE41EF2E2768ULL, 0x285900799C0FF761ULL, 0x9EC5B7AFE7649D57ULL, 
            0x9B619A4973EA567BULL, 0x229628AE31224230ULL, 0x7AB8C80346D91E4EULL, 0xC898FF4E62065C58ULL, 
            0x2203D986B629E69BULL, 0x58AFB78A6293AF1BULL, 0xD16D0B27B07333ACULL, 0x9DA55ADFF04E28E3ULL
        },
        {
            0xD35897C6B85202E3ULL, 0x4417BCE6015696D3ULL, 0xDF03FDF1E9DFC40BULL, 0x49ABE0C2C55B0129ULL, 
            0x542A8168FE153DFCULL, 0x176AB1D7C698E135ULL, 0x1A564DF99D845C66ULL, 0x0572331E87BBFC87ULL, 
            0xF94510F2BF7B2E0FULL, 0x1A53B82C27D4C4D3ULL, 0x8CC28A49665C3C59ULL, 0x6495C2C2C3468BEAULL, 
            0x9FCBB95FD284A8B2ULL, 0x779384C416DD9BC7ULL, 0x021CCC95DAA2BD47ULL, 0x0667F07886E45BEFULL, 
            0x59D90082514F85D3ULL, 0x167EC3D3D0739838ULL, 0x30CF7808ACDE7A9FULL, 0xBB2F4EF0E43A607CULL, 
            0x85C5BBD914B453B9ULL, 0x9CD078BDBBC05939ULL, 0xA1FC8A4B643BD677ULL, 0x636C3D5F94384976ULL, 
            0x7C347E6524F1C1C6ULL, 0xF7B875C2D225567AULL, 0x637D56FAD78C1D95ULL, 0x4A94E9448FF32F5FULL, 
            0xF3551CE58F33AEC3ULL, 0xAAE2F0C31B3F93F7ULL, 0xA832A6E52953A405ULL, 0x7F45F7EEC89D0EE1ULL
        },
        {
            0xE08B1B07A8B38716ULL, 0x0D519C9A64FBA261ULL, 0x353A2E662B0C52C2ULL, 0x46A5B42F8CEE7EB7ULL, 
            0xF92DBD190B05FA8DULL, 0x285B201EA4EC9474ULL, 0xFE599A13F73E1739ULL, 0x5A0AC3DF4FE85A37ULL, 
            0x63A6BE1AB2599849ULL, 0x83DABBBCC48E688EULL, 0xC47A5780C6306727ULL, 0xA2C6868AD8209F9AULL, 
            0x032312642D09C18DULL, 0x8A47C97136E62330ULL, 0x42AD98DD436687F8ULL, 0x12260EA726A7ED03ULL, 
            0x84EBABD1F77FADC6ULL, 0x35E469AFB721C60CULL, 0xA7AFB3572D267798ULL, 0xFF55C5B3B52346F0ULL, 
            0x27FE32250002747AULL, 0xD9D82A4A122E6689ULL, 0xD0AC9977C7540771ULL, 0x3F628592DD766920ULL, 
            0x52A67F259962C47DULL, 0x5770694DF4B6394AULL, 0xD688456BD5E722C8ULL, 0x477EEE9B6EF12B42ULL, 
            0xE5B3E1A032CE3319ULL, 0x4A290A349C3A72DEULL, 0xAA51055F73A032D9ULL, 0x0753F26E0FF9AFD2ULL
        }
    },
    {
        {
            0x1DFE6F7F0A584857ULL, 0x351AB9BF9E5C7018ULL, 0x69CD834E03E25793ULL, 0xB9C054A61B865447ULL, 
            0x99CF7396D79EA935ULL, 0xCF6D827D52BB0CE6ULL, 0xFA24DB62F95EC4D0ULL, 0x14A7E7A298356543ULL, 
            0x2A70D7FF5EF27355ULL, 0x7E7C363065F6CA24ULL, 0xD2B05C86F2ECD28AULL, 0x03EEA6CF28497779ULL, 
            0x6AD35B367A1A0440ULL, 0xFB356E0A16345577ULL, 0x1A66E5283DB5D1FDULL, 0x8325C11E4A055EC2ULL, 
            0xB3C121CE40E01DF2ULL, 0x76FBC2FE96173B9BULL, 0x7E845977D0DE529FULL, 0x364F172C31A3AA40ULL, 
            0x59740367565D8A12ULL, 0x24EA9CC9186F69D7ULL, 0x57716D12175C0AE2ULL, 0x96B77D7E3AD1F7F4ULL, 
            0x7C4FDB4C9B581F1FULL, 0x3D725C9E4D940463ULL, 0x5FAFC7FB0CF2BECDULL, 0xA14AFE1FDA237880ULL, 
            0x54F1D2B9AFFA6DC3ULL, 0x08C4F9EA33B99C8BULL, 0x92F750507622C53EULL, 0xFE56D6D0AE9DF237ULL
        },
        {
            0x9F1134862064C001ULL, 0x2618478DAE69E4B6ULL, 0x6FC915074A7C8DB2ULL, 0x3860801EB6FC6288ULL, 
            0xDAED074A8594FF54ULL, 0x6FF63A7F32C6D1FAULL, 0x73234CD759E64EA8ULL, 0xECCDF9FE235EEEE9ULL, 
            0x3B9B486C4C2C5D38ULL, 0x88CD971DAA2E5DB8ULL, 0x54392AF4F4A6859CULL, 0x481F3FAE3875674CULL, 
            0x7957D023732C3586ULL, 0xE8520111EB075402ULL, 0x654EEED25390B09EULL, 0xABEB4191EA0F957EULL, 
            0x531CEE96A4B21150ULL, 0xF5F3E0EE9A5EACC4ULL, 0xC5ED05AD82A6AF4AULL, 0x4768459D7869F798ULL, 
            0xE30D3888555B05A3ULL, 0x3B9E2D647545FEBBULL, 0x404CF762813D0F84ULL, 0x1E1AF19C1D1A3772ULL, 
            0x8EE244EABC0A2E49ULL, 0x51C0ABD8769B44E9ULL, 0xB78D32F7E91EC6FFULL, 0x64097BD85DF03BBDULL, 
            0x878BF6C4BCD13C8FULL, 0x18133CAD02A3B198ULL, 0xB59AD42CDB6EC24AULL, 0x9B7C164AED20FC7AULL
        },
        {
            0xFBB8EC1B50C114F9ULL, 0xAF843D0AB3BA79B2ULL, 0xDD45702B90F22676ULL, 0x0D916F836D421957ULL, 
            0x55609A7FACB7EE00ULL, 0xBBABEC8105666F5BULL, 0xDC31A48FC2FEDB4EULL, 0xE469B4B4537CCD53ULL, 
            0x65BE71C1453AF5F8ULL, 0xFF1CBED97B2E4BBAULL, 0x575F4BAA041ACAEEULL, 0x6D220FCC4F4E39B4ULL, 
            0xA55477D23F96C0BEULL, 0x143F2B856BB3C8EEULL, 0xBB981465A3E1C302ULL, 0xF5B977329C5B2E25ULL, 
            0xA1A2260013CB121DULL, 0xAA834B3BF136D813ULL, 0xCFDD4D2D0A1D51B3ULL, 0x169048C5A5789DDEULL, 
            0x9CB6FFD6D79E7604ULL, 0x112D022221392B0AULL, 0x7137283E385CEB50ULL, 0xB1170C0C1C823DC4ULL, 
            0x34A973B2A89C44C9ULL, 0x981ADDB205E5EF18ULL, 0x2B08F8775EAA2588ULL, 0xBA8CF2710776677FULL, 
            0x4EAA19A8C936A95AULL, 0x457B1AD7B8F25F42ULL, 0x3D3B157F140A105EULL, 0xE895533A6D914FA4ULL
        },
        {
            0x282E58152D919287ULL, 0x005973DC2DA0D946ULL, 0xCE36504917648ECEULL, 0xF9B5D2FEFEBB585AULL, 
            0x3A75952D3F2B4DE8ULL, 0x49A334B7ADB15ABEULL, 0x74CB5253A8E7C36AULL, 0x8095A77F194B7ABEULL, 
            0x14BF04A93C3AD0F5ULL, 0x0D3AA3D7EBA4C92BULL, 0xF17F447FCC77F528ULL, 0xBDF12924915EA67FULL, 
            0xFCF8546789EF0AD2ULL, 0x809064044BB26F83ULL, 0x60DE3D29EB8EFEACULL, 0x66A015A0E2ABC9DFULL, 
            0x2746B6175782F051ULL, 0x8AD0DA7ED8FE5408ULL, 0xDA0F7A5BC1CC94F3ULL, 0x777388E4B370F13CULL, 
            0x9B079304A4C23156ULL, 0x0A49B9AA1E24B19CULL, 0x9EE278CD8E788DFFULL, 0x45D421ADB4318D6CULL, 
            0x8C0C455ECCC190ADULL, 0x92A3DF1B6B0F4C09ULL, 0xC7A11C0A390F5087ULL, 0xAFA2C9F0FE9AC901ULL, 
            0xE37808DE83E9EC64ULL, 0xC06CD16EF3F249A8ULL, 0x9B8E4227E258A6F4ULL, 0xB62D141738F735FDULL
        },
        {
            0xA02FB36E84B6A9ADULL, 0xDF7B4BF2A7FBED41ULL, 0x434EA068C134D9E7ULL, 0xAA81C0E2F506D0DDULL, 
            0x2A8F611ED3F9BEE9ULL, 0xC6DACDF3655AF2C2ULL, 0x05013015E2BFB6B5ULL, 0x8DD27897DED58658ULL, 
            0xABBBAAD3EC0A9DDCULL, 0x6F81660407402AE0ULL, 0xAF0079255C4BB333ULL, 0x306684BFB228C301ULL, 
            0xEADA713D2D5286C6ULL, 0x48830F5C9EA57AA5ULL, 0x9CAFC3A9A7CC3712ULL, 0x08373505B30A6D99ULL, 
            0xFE48702BF7FFD964ULL, 0xBC37413B8ED2B216ULL, 0xFF5DB64DB0D94423ULL, 0xF4B41792A4420DDCULL, 
            0x40D2E5BEEC598690ULL, 0x962DAFD812260463ULL, 0x5ECFA04A594BE804ULL, 0xC85BEAC2B30BE3ABULL, 
            0x9CFCD58B47D4E736ULL, 0xC2ABE2B96B31E80AULL, 0x67B4BE0B29EC46DDULL, 0x72795080088ECD27ULL, 
            0xD298C81E393AF23DULL, 0x1A8973E397D950F6ULL, 0x14C173A3CE245571ULL, 0xBCAD071D529D6C70ULL
        },
        {
            0x7E7078EFD694B2A4ULL, 0x1E294306261C10BDULL, 0x72B3A7A0D75A6043ULL, 0x148A45F88CE43B97ULL, 
            0x78641D7437C39E44ULL, 0x847ECFA56077A71EULL, 0xA07BE56289B8CE19ULL, 0xB29E563B940630D1ULL, 
            0x038BFA97BF8BD760ULL, 0xDC2CB28286C875E1ULL, 0x8007F15BD9CAC82EULL, 0xCBEA913021DB9CE7ULL, 
            0xED7C69D51C8B7A94ULL, 0x389D21D301D907A5ULL, 0x7E434C5F36600C16ULL, 0xC6BACACB679BF968ULL, 
            0xE9C2FBE3D51A2BF1ULL, 0x6412367F9DB7770FULL, 0xA54B03CDE701EBC5ULL, 0x46C2ECD3F3B5A104ULL, 
            0x9BF8BF3B57231245ULL, 0x21B014785AC7E017ULL, 0xC0E2FB1161B24B1AULL, 0xA564DFE4D6036B11ULL, 
            0x5C76893F6CF8A9FAULL, 0x0481C791373C10A2ULL, 0x4FC9139765CBCE5DULL, 0xA787080D5EC68E5DULL, 
            0x21C5071C43BAAAB4ULL, 0x99343FAAF09E6431ULL, 0xB4C286A98F8D2589ULL, 0x2FEC3202D7747C33ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseFConstants = {
    0x3F48E837DCF20A41ULL,
    0x8CBC8D60F4E0C6ACULL,
    0xC56383215104D688ULL,
    0x3F48E837DCF20A41ULL,
    0x8CBC8D60F4E0C6ACULL,
    0xC56383215104D688ULL,
    0x04F256A76DE8735CULL,
    0x61D5FA957D75061CULL,
    0x5D,
    0x86,
    0xD4,
    0xE7,
    0x26,
    0xC4,
    0x38,
    0x90
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseGSalts = {
    {
        {
            0x42B2FCFABAE19A4DULL, 0x0CCC2761CAA607E3ULL, 0x612F122CEB21E2A8ULL, 0xEEE68E076529BF60ULL, 
            0x1A76AF5187C98759ULL, 0x7C339B863178ABB9ULL, 0xEBED5950FB14B00FULL, 0x01DA5B7723DB8AFFULL, 
            0xA3E2B92C18CD5FADULL, 0xC796418F29AFA9FDULL, 0x37C6352FCCD888CFULL, 0x9E39FB91D90AD0AEULL, 
            0xDD51C20B8EA0B3ECULL, 0xCFD5844B9F7D1E99ULL, 0xE97B35DA1CA8611BULL, 0x7FE4DE1008990D14ULL, 
            0x86739EB19F963F49ULL, 0xE9C32D9A38EC1BC2ULL, 0x678B871F99DE3FAEULL, 0xDE15DC0DCCAB2F6FULL, 
            0x6090F6B32AA6FD52ULL, 0xEC69162F87A05B7BULL, 0x70217F607798EE13ULL, 0xFB1A13F3CFA10442ULL, 
            0xE09ACCDD0C5A7196ULL, 0x8C117F6F9738BE97ULL, 0x370C70B21269F722ULL, 0xC0906FC465E7DAF5ULL, 
            0x4FF6089B03E5EDB7ULL, 0xF2461E540A27A55DULL, 0x4E895F133D92BB74ULL, 0x600E531D64A49791ULL
        },
        {
            0x245F35D49D70EAA0ULL, 0xABB9D79F0E4A52B4ULL, 0x8C67108554F5F467ULL, 0x81F54FC551CCE179ULL, 
            0xCD88F437DC9808AFULL, 0x5BD320528B1C3E02ULL, 0x115332BDA4DBDE73ULL, 0x02F033BF7480568BULL, 
            0x996E1542C76B1B93ULL, 0xA6EB2356349439F7ULL, 0xD34F3A1015C369A4ULL, 0x37EBE0E6C9147EAFULL, 
            0x9EEF639C3ED2433AULL, 0x5454966EB71D8873ULL, 0xD88236D2CCB04577ULL, 0x1DBE613F499B9268ULL, 
            0x6EA5C6BD0151B24DULL, 0xA1449C6DF92543DEULL, 0x21D8EFC6A87797C3ULL, 0x847F1A2249D20B74ULL, 
            0x1F5D996A406B4B29ULL, 0xC78DDF71A55C3CC9ULL, 0x076AE6C9EAD9C943ULL, 0x9A77D6F1A87F7CF5ULL, 
            0x843300460314F27EULL, 0x246E0A4C5905E890ULL, 0x7113F018EB9E601AULL, 0x3DF71162F10ABFE7ULL, 
            0x4C907CBF2C8347BAULL, 0x13243F6FE5339FE8ULL, 0xCE39098FFCADBB93ULL, 0x082D18776ECD3194ULL
        },
        {
            0xE2A75C0AAE436280ULL, 0xB62CFC1D1871BF26ULL, 0x256A179614478083ULL, 0xB22BD46FE203B3D5ULL, 
            0xFA0B8F1524918B5DULL, 0x6B606CE0B3855E95ULL, 0x886388D8A244AC14ULL, 0x5626C03980295E8EULL, 
            0xE2A9DBF2F13C01EDULL, 0x3FE432CE3F9D9F3CULL, 0x401527BCA8AB8ED5ULL, 0x4365C0DB8CE66905ULL, 
            0x288272D190088C21ULL, 0x6844CE45C7524DCCULL, 0x5CDF5F1C1DDD91D2ULL, 0x6F3EA33AFC67520CULL, 
            0xED67BF3B6CBFE97CULL, 0x1F98E08BF56C3FFBULL, 0x256E143138FDEB53ULL, 0x23616E7EB7A4CA38ULL, 
            0x11D681E9A77BB26EULL, 0x84368C6BDCC26311ULL, 0xACD3F599C64028F4ULL, 0x191F5CD1F738915AULL, 
            0x33E73A6103E0F71EULL, 0xEC71937D18D98D65ULL, 0x76FE34E7539B746EULL, 0xC2DF11D5A11CB804ULL, 
            0xDCA2CBC7E28156F8ULL, 0x35B07FCF3F396E21ULL, 0x6FDDDC7F5F67B63AULL, 0x929052F362D081BAULL
        },
        {
            0x522C0886B90EF7D1ULL, 0x9ADC3205B5578CB8ULL, 0xE261132C6748734AULL, 0xF6A2B73F720335E0ULL, 
            0x88890C47EC57505EULL, 0xD21F261DB11CFC47ULL, 0x553B703FFB463CBCULL, 0xE8EA5D5FDCBBC070ULL, 
            0x8D96FCFDDBB14D81ULL, 0xD99464412C588E4EULL, 0x16829AA08CE11F29ULL, 0x1AB7D08DE7A3F173ULL, 
            0xEDA97B6B8396368DULL, 0xB7F574EFE0EA3BA0ULL, 0x233A582EAC93AE9AULL, 0x4BA9ED9AEA06411AULL, 
            0x5DD86B3C5B59EEEDULL, 0x02CA007ECBB603B3ULL, 0xBBA63F442FD03F73ULL, 0xBD6A592E3CBEC89AULL, 
            0x874705115D377789ULL, 0x7475620A9DDFA6A8ULL, 0x84C1CF60F4B761EEULL, 0x688CB2F72FA3A7D0ULL, 
            0xB688B8824B7C0CDAULL, 0xADBC3E1E837998DEULL, 0x9B22229B162DAB6AULL, 0x217C58CC5A8FEE83ULL, 
            0xF466AD802DCBA9DFULL, 0x9E9455A4642CE475ULL, 0x9CFFB9A3ED505A51ULL, 0x6A9A74527E3AF608ULL
        },
        {
            0x3F73C24EFFD2A0D4ULL, 0xB742B7757E44C558ULL, 0x16E57B8D95218947ULL, 0x6FE2CE61C60184D0ULL, 
            0x09920CA36EA61350ULL, 0x4894007C56CCEB60ULL, 0xAD67D71EAE832A0BULL, 0xC33C24CD5EBE877EULL, 
            0x1A4A5E093C067AB8ULL, 0xB1DA4D6250BD6528ULL, 0x42D058D2B77BB2C1ULL, 0x644D015AC042E512ULL, 
            0xA34EFF963E864C37ULL, 0xF917E3DB28833217ULL, 0x5C29699163218B24ULL, 0xAF3177943873C3BFULL, 
            0x305EAFEDBE9BB86EULL, 0x3DE47529B029D54FULL, 0xECF0D4ED3096FC16ULL, 0x28F08E6EFDEF5CFDULL, 
            0xB3B1736A22D58160ULL, 0x92B7C31AC1EA3674ULL, 0xDD8122F3D35A295DULL, 0x99E0811CA342FF1FULL, 
            0xB2A3DD96416809EEULL, 0x652175A1CDC8478DULL, 0x9A95804EE0510281ULL, 0x2714913E323020ADULL, 
            0x2DCF47EDFA9CB526ULL, 0x02E6D5EF55815D39ULL, 0x19CF401CDF1D633DULL, 0x1BED9DAB4AC537E1ULL
        },
        {
            0x63FE317827A0F037ULL, 0x234265E7E4F64B35ULL, 0xC93CAC52269A11E6ULL, 0x3DE564ABDF691416ULL, 
            0x76B172C68E0150DDULL, 0x991EBE293DE137CFULL, 0xB9B26AD4B9F7F251ULL, 0x7995DDCAADC9036EULL, 
            0x535248AA2890FE51ULL, 0x96477310FEDD9EA6ULL, 0x991A3A0159CFFA31ULL, 0x8B15B278B2348D55ULL, 
            0xD6F954645C5F7FA6ULL, 0x44D04B6C7D4FC26CULL, 0xAA6059DC1D9EB7DCULL, 0x7F9D94467C07D993ULL, 
            0x3F64BD0FED05E95CULL, 0x87753E87F6C01E9BULL, 0xAC65BBEAA00B5FB0ULL, 0xFC64247F7600DFB9ULL, 
            0xEE32AD615C6EC22AULL, 0xF81A2EA9F08AA0A1ULL, 0xA56585726EE758F1ULL, 0x1D8399C715490FC5ULL, 
            0xE0D9BC56EA8DCEAEULL, 0xCFC863534399FFE4ULL, 0xE30F8862870F87E6ULL, 0x6E9D59EF489AE999ULL, 
            0x27ECB87DABE2919FULL, 0x115E8D61142262FBULL, 0x3CC653EFED50D03DULL, 0xA1BD57ED5468C2C7ULL
        }
    },
    {
        {
            0x89C78590D1785289ULL, 0x0C90DE837C55FA68ULL, 0x4C3AAE03490BDE4FULL, 0x78E95E0E7E385DCDULL, 
            0x3858351ED36E1535ULL, 0x822B9A67C1D16837ULL, 0xB8B58677C17FD669ULL, 0x886712FBAE0FC5A0ULL, 
            0x204572649077D14DULL, 0xAE90CC36C416EB36ULL, 0x9A28C0773386B40EULL, 0xA786D6D8E93A8919ULL, 
            0xA3540467E76C3D04ULL, 0x9E4F4395BD9C476AULL, 0xD69BA594A2275530ULL, 0x173CE73406B6BFBEULL, 
            0x50560CCBFCABE16AULL, 0x77BFDB9B732E547EULL, 0x491B764442F8E3CCULL, 0xCA1A4CF4F2273070ULL, 
            0x4BBBCF21313265C2ULL, 0x9B638EFA5E47B4F2ULL, 0x056FA5CB85946641ULL, 0xB023226C83F016E1ULL, 
            0x08860C47165583FCULL, 0xB46341818F40C637ULL, 0x0312FC36CABF8C8AULL, 0x1A6A97CA5A04397AULL, 
            0xFD6E136B3F414303ULL, 0xCD96917F4B998B86ULL, 0xC8528B5073237496ULL, 0x068DAAE8B71097C5ULL
        },
        {
            0x1EC96E10A6CFE478ULL, 0x4761E857F23C4C97ULL, 0x38A376F7405789AAULL, 0x124341FFCDCC0A8CULL, 
            0xF5AAD21FA719681BULL, 0x5FCD9F9819D983D3ULL, 0x451FC381968066E1ULL, 0xE13449DE8012D835ULL, 
            0x92E3FF95A166F101ULL, 0x6C1D4BC6E7239748ULL, 0x64B9AB6C8489B354ULL, 0x6252B12B1F28AD8AULL, 
            0x12A63F8EFC80B4B3ULL, 0x5027F7668A659676ULL, 0x9348FF565102D37EULL, 0x64816DA3B0F935F1ULL, 
            0x8174D132FADF4E6AULL, 0xC1573001C00E453EULL, 0xE031856D68BBB67EULL, 0x224BE0E5D27347CEULL, 
            0xDBFD9CF8813F5189ULL, 0xDC9E215C82127EB0ULL, 0xC13DF656CFD7A814ULL, 0xD6D6673A47737049ULL, 
            0x09497D9E232B90F2ULL, 0x92400B2617766C8BULL, 0x6D36140F3853BC64ULL, 0x094F3064C0B736C4ULL, 
            0x89F861CA3ED06F75ULL, 0x5DCB1160BBFD0457ULL, 0xFC5E7C9FAB6F22E6ULL, 0x757EB1E9AF1E3456ULL
        },
        {
            0xF242E8027B4E2C2AULL, 0x5A50B1FF5B24203FULL, 0x40801BF07F46AEEBULL, 0x4926BFD7F5E0A724ULL, 
            0xA532741BD939DA08ULL, 0x03B63361FC3D9D4DULL, 0x5DBBC1341C767637ULL, 0xF5DBF05B5018FDAEULL, 
            0xFB4E3A619DDDC8EAULL, 0xEA52524CA1EC813AULL, 0x04CF879F366456F0ULL, 0x6A50EFC3C679BCF9ULL, 
            0xD77328052F47D6E0ULL, 0x460FE2B9C84B0AE3ULL, 0xD64B2BABC0D2A683ULL, 0x19B8B7172F5C9949ULL, 
            0xC83FD8FDED7949B0ULL, 0x3616259C890FA5B8ULL, 0x7D468C11077B934EULL, 0x5FE415051B1A90F2ULL, 
            0x294105798311B59DULL, 0xBC1A8F01F1C06631ULL, 0x7AE1645586856677ULL, 0x2982D658C9F48BFCULL, 
            0xA419FF1FBA30484AULL, 0x7C37C7F9D30904A0ULL, 0xCA8667B4BCD5B5E9ULL, 0x828CB5A9B7352761ULL, 
            0x5BDABA4AB3080763ULL, 0x2C1D693CF2386086ULL, 0x3486D3753EC99AA0ULL, 0x8C868732D4482936ULL
        },
        {
            0xDB2582C823027303ULL, 0x988480FA14C7F9C4ULL, 0x3053BA161295AAE9ULL, 0xFD0BB59D61C8A3EAULL, 
            0xFA7BCD01923220D7ULL, 0x51271207602F25C1ULL, 0x010661F3B1E17443ULL, 0xAE7B295833FD45CDULL, 
            0xE1FE3408DCD8B3B4ULL, 0x911674E599B4A3F6ULL, 0x0E20C104BBE6A051ULL, 0xF5D1AE8885A5C500ULL, 
            0x4EBD2C129838A847ULL, 0xEBEC26C13CD617F0ULL, 0x381405C4CD613354ULL, 0x901A264F86533CA8ULL, 
            0x40E3D38084956CCBULL, 0x0B7EB66F28BAE1ADULL, 0x60CC38AE2B3DA9B9ULL, 0x0884BB30E5682BECULL, 
            0xE91189769B638AC6ULL, 0x301EEE8F340FCAF7ULL, 0x915C666BE3113756ULL, 0x645A1EA0E075DC0BULL, 
            0x1B4B373A2F7A0704ULL, 0x7353E9323E7FB8E5ULL, 0x9ED23DF6629BA7C2ULL, 0x8D912A2A476D7B69ULL, 
            0x5A32B638FE73E74DULL, 0xC1ADD034BACEB895ULL, 0x387238444B302CABULL, 0x02EC85BEC9761EB2ULL
        },
        {
            0x0C6AE9180BD42B06ULL, 0xEA5F082C39DB58A6ULL, 0xDB02EF7912A81525ULL, 0x02A6CC40D474B090ULL, 
            0xAD1B03D9D948E39FULL, 0x66CAFA428BD02EE9ULL, 0x246324CEA9C70A5AULL, 0x05FE7ECBA4AD2FBBULL, 
            0xD86F7AEF99002928ULL, 0xF6824196845E8E37ULL, 0xDE2DB02569C1845BULL, 0x307ADCC6E7FA7232ULL, 
            0xA47DE5A14335E643ULL, 0x715C15E1BE12815FULL, 0x89A27A42BB26DB77ULL, 0x33B9741C2C0DD5EDULL, 
            0x3F53C772CBE279CFULL, 0x16E883D9DF64E0B7ULL, 0x5F1A0A0288911CDFULL, 0x29E06BF4272EC211ULL, 
            0xAE251BDA673E5B13ULL, 0x3604F28204816726ULL, 0x1E6167FEAB3D5B5AULL, 0xE834633749F969FFULL, 
            0x480403456FAD1018ULL, 0x411137A90E2578B0ULL, 0x7BADA7D4ADAE2CA6ULL, 0x42BB370BA7E8DB05ULL, 
            0x132DAB3B70B0B6F1ULL, 0x73D2C71C1B15F658ULL, 0x691490DE7AEC6770ULL, 0xBBE08B6F51DFA37BULL
        },
        {
            0x6FABB90C362B27C2ULL, 0xD0199826122137E4ULL, 0x0AEBE1E83FE902E6ULL, 0x2635CFDCFD03BE93ULL, 
            0xC5B793BF577E7CBBULL, 0x8FC55A085B09B28EULL, 0x5064FEDF9DF96CF2ULL, 0xE544AEFA4A1D8373ULL, 
            0x2C23C4C37E057D53ULL, 0xD7F821C3197FA953ULL, 0x2F11D758346BD362ULL, 0x7EE51A7C39250DE4ULL, 
            0xA629FB360F82F7CDULL, 0x5AABEBFA63EB30EDULL, 0xE4378376A1ADD073ULL, 0xCC231A2E64FB145CULL, 
            0xF849098A84ACDC47ULL, 0x6C1AFED55AF9AF12ULL, 0x583AD92EA8C9B548ULL, 0xD1B8973BC94FC2F3ULL, 
            0x7CE61DCB14C478E5ULL, 0x0D47684B54B5B725ULL, 0x21E75555F511ECF8ULL, 0x9A05AA7495A1922DULL, 
            0xCA07BB8B8BE09E16ULL, 0xCAFD1A8D6098F671ULL, 0xBB257DE3B32208CCULL, 0x7D9C58C872254C07ULL, 
            0xB30659640142005AULL, 0x1BDCDAB7BBF7B37EULL, 0x83BE13070D2403B0ULL, 0x61CDD68FAD068468ULL
        }
    },
    {
        {
            0x21E0587250363C0CULL, 0xF4D7E7530DA075D4ULL, 0x3B70FBB05E952242ULL, 0x59981A171E586B83ULL, 
            0x9BD957C5D3FD4C4DULL, 0x93713CA27D834DACULL, 0x819B1F430D2528DFULL, 0x5E19F5B011BD9657ULL, 
            0x14E410379485016AULL, 0x6198D971B5A77CD6ULL, 0x8F496C74637A044BULL, 0x99AFFED3A60D8005ULL, 
            0xEEF4587C27AEA3CCULL, 0xD36DC57E39366EF5ULL, 0x365E1C632DB729E1ULL, 0x201F7058FF74BEA7ULL, 
            0x7593AD0A1BCDF7F4ULL, 0x9BB7B390F1EF4548ULL, 0x96A6911350DC4F57ULL, 0xC48FD2811484AC4EULL, 
            0x23F10E3DE37930B8ULL, 0xAD3C0835F3C7155AULL, 0xA67C1AD34CABFA5CULL, 0xE3B70CE65F0ED431ULL, 
            0xEC4B8C73F1F11EA8ULL, 0x20A7467DC5741151ULL, 0x56DA0F10484756ABULL, 0xBA98F38FFAFB9E00ULL, 
            0x3C1084F1E2043E80ULL, 0x958BE792D349D2A9ULL, 0x71A406D2337B0434ULL, 0xB8989DCA5126FA53ULL
        },
        {
            0xEEA1FF881A772A43ULL, 0xA7062CB2A6C5B3E9ULL, 0xA8D18F15488371B9ULL, 0x4D4D4B4647208D1AULL, 
            0x23F79F0A59828CFFULL, 0xF178D5553D712451ULL, 0x9C99C48623A82B97ULL, 0xCC8C047C66E3152DULL, 
            0xF51825E48535846BULL, 0xAA2F79A9A08CF02BULL, 0x135C799AD0118F27ULL, 0xA0D1914E7291BB7EULL, 
            0x698E05AD1E66E8A7ULL, 0xC0B8D88096DCAB3EULL, 0xA3EB48A4AE93AF6CULL, 0x8592FC35E8C6B416ULL, 
            0x417AE1CA5E7A8F96ULL, 0xD904DFAB38145962ULL, 0x2F6CD7AFDFF6C2F6ULL, 0x164E9AE18BDED064ULL, 
            0x1BD8415387814BC4ULL, 0x15BF984E7C7CEE37ULL, 0xADA705BE7A179224ULL, 0xF2A0247E71E7F928ULL, 
            0x414840949932B7E1ULL, 0x68F508D28C47C526ULL, 0x14413227C8283865ULL, 0x5C934E6308FF3EBFULL, 
            0x07A95315633DDBF9ULL, 0x983306F372BA983BULL, 0xF41F1C7165CF20ECULL, 0xEF0CCF680C8817F6ULL
        },
        {
            0xA6252361D02EA597ULL, 0xC84F6913325F814CULL, 0xF69BCE1BB5EA2FE7ULL, 0x93A2E263302E4817ULL, 
            0xFE4C499DC9937519ULL, 0xA210B36F5DAB907AULL, 0xE864EEAF5CDA3BBBULL, 0x1F7A8B4576B73795ULL, 
            0x93CBC820C7E98675ULL, 0xF4B78B8C715A7698ULL, 0x325984CEFCE91383ULL, 0xB226E975E5A56AB6ULL, 
            0xC11FC9F067A4C002ULL, 0x941E2C65539B61E8ULL, 0xD8B10F187C0B130CULL, 0x082A644BC6C1518CULL, 
            0x8A7FACA68B7E6A30ULL, 0x57904732DAC72502ULL, 0x8B5C354D8EB54814ULL, 0x57569B359426E1E8ULL, 
            0x0844688BE5D719D4ULL, 0x69D4F214D3AF7E85ULL, 0xB30545F8EBFCFE9DULL, 0xBE583DBB23779A1FULL, 
            0xE4B33FBA54DF0F43ULL, 0x0C4668ED6E5A3F9FULL, 0x0E5A37ECF92B1ACAULL, 0x166CA2C9BEE022F3ULL, 
            0x4B1B6B07E0D7B98DULL, 0x3F2D9847CF19B318ULL, 0x879007136435DC54ULL, 0x0DFE738B36761BB7ULL
        },
        {
            0xB9CAAA1B438E0390ULL, 0xAF974FB2A79932D3ULL, 0xB311776ADF5947D1ULL, 0xBA73C03318D27A49ULL, 
            0x085CE020D3412B59ULL, 0xCF302D4349D5418DULL, 0x706B39B44F7C1ED6ULL, 0x4B3B1DABC0F81AE3ULL, 
            0x698820B082AACBD1ULL, 0x2159F815292B3319ULL, 0xD58836482594FD2CULL, 0x8BB94D3C6275D52CULL, 
            0xDAAA00F2116A72BFULL, 0xD855E3701C18D666ULL, 0x414799716EBF66B7ULL, 0xE99B58364329DD5DULL, 
            0x591BCCCFEA29A680ULL, 0x70D7B95E57F612A4ULL, 0x10D071187B389202ULL, 0x4D1BCC2CA0FA80B2ULL, 
            0x048B5D36E761D2E4ULL, 0xB817BD28D1D683ADULL, 0x01E49B677A8A9ACAULL, 0x7C430ACF1FC7F608ULL, 
            0xD83CA97F640B0639ULL, 0xC5D7F7BC9E8CE2CDULL, 0xA9ECB42BF04A298DULL, 0x59363642425FCCE2ULL, 
            0x1F9F280F4F50E575ULL, 0x2636039FA2A022ABULL, 0x90417F14DFBBE041ULL, 0xE6610DB8E3A00F26ULL
        },
        {
            0x458B3A62926E4287ULL, 0x5BE720CE8148CB7EULL, 0x372711DF278F1ECFULL, 0xC81F1F8CAD5557C3ULL, 
            0xEFB24EBBF2AA6212ULL, 0x5B9187141693E136ULL, 0x120704A816BCA25EULL, 0x22DD74BF79EC9ECAULL, 
            0x83BB53916C0607BCULL, 0x7F03994B26D95FF9ULL, 0xCC4FDD1B080AC025ULL, 0xF652D352697FBC9DULL, 
            0x40955EFB0D7802F6ULL, 0x3992955C94ECCC03ULL, 0x2C362307643E4D98ULL, 0x2C95199DCDB309CAULL, 
            0x44B71C57D955E88DULL, 0x2D4A2BC7B9F7F745ULL, 0x42A1CCCDD72DBE9AULL, 0x272D133E08C6DE17ULL, 
            0x8765F78EE37C3024ULL, 0x9555402C73D06BB0ULL, 0xF2455D6517D3934CULL, 0x6948D8E0AB6F2887ULL, 
            0xBE1D65E4D132CBB2ULL, 0xB5AF45F4557F6017ULL, 0x5129D2AFF4436CE6ULL, 0xEF59751A2744BB62ULL, 
            0xF7474D074EF2BA2AULL, 0xC571AB22E2795E87ULL, 0x8BE91183A6C9A3C3ULL, 0xDACF23635B714D4AULL
        },
        {
            0xA47FE28CAEBE09B2ULL, 0x64B986268A99126DULL, 0x4808043A846FCC9BULL, 0x340070C6C8FF7F4CULL, 
            0xCE4D90E8718CE34DULL, 0x9C2ED70C768C7DB7ULL, 0x2B4BD6D46192F75AULL, 0xE30E827653519B35ULL, 
            0xBF8E7DFB0AD200CBULL, 0xA9DFBD77D443489FULL, 0x4553FDEB73BAFA0BULL, 0x89E4DDFDCA2E6F31ULL, 
            0xF6DA6B8408CC6BC4ULL, 0x7BD7D838A9D1C155ULL, 0x072F0F132FEF9400ULL, 0x7197BFC02CEE0240ULL, 
            0x3181B091BAB224BCULL, 0x21765B02A0B50084ULL, 0x88C8728274250D8FULL, 0x8508F2B2E6A93A34ULL, 
            0xAD9105AC4D9E2C78ULL, 0xE24F831B3A1037FAULL, 0x5D6D51816AB705ACULL, 0xEDD556DA59664ADFULL, 
            0x7141E4C890CB9506ULL, 0x96818931F9B5B5C4ULL, 0xC8A7601AE6F1BAD2ULL, 0x235029A1F8472D3CULL, 
            0x1FCDB273224C42E6ULL, 0x536B0DE636187888ULL, 0xDE70558ABF52DA7BULL, 0x8A99476F7904F156ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseGConstants = {
    0x0F2AF39BE23D041DULL,
    0x5D5719F631D2E5B1ULL,
    0x07913CECA607E808ULL,
    0x0F2AF39BE23D041DULL,
    0x5D5719F631D2E5B1ULL,
    0x07913CECA607E808ULL,
    0x64268727473470E4ULL,
    0x5E9FEC654C6ECBEBULL,
    0xA5,
    0xE0,
    0xFA,
    0x46,
    0x60,
    0x9E,
    0xB4,
    0x9D
};

const TwistDomainSaltSet TwistExpander_Bellatrix::kPhaseHSalts = {
    {
        {
            0x21637917C8158F4CULL, 0xCEC700CEBD802E48ULL, 0x470F08840FFF9863ULL, 0x69176A105B734CC5ULL, 
            0x60B0CDE60A903C1DULL, 0x1B250DB21EC301ADULL, 0x7865820D8404445FULL, 0xCBDC89D0925485B7ULL, 
            0x785B0B8F9135545BULL, 0x6B75DD95A268182FULL, 0x1A49F9F61028E5F9ULL, 0xA63B1ACECE465BD5ULL, 
            0xC01F786978B1BB52ULL, 0x70020B904DF182A2ULL, 0x1A8CE5A4CC8289BCULL, 0x8998075E4EED1408ULL, 
            0xED00967E007028C7ULL, 0xD8DBA0FC912BBC20ULL, 0xDE623004F1B1BF49ULL, 0xBD7EFF89E2A097CCULL, 
            0xF37730B48D96EED3ULL, 0x6BDEF86EF17EBD98ULL, 0x529C5D89A05B42DDULL, 0xEB11CA2B490C03B0ULL, 
            0xA31616628DF35EB6ULL, 0x2B6285858B70DF8BULL, 0xDA6ADFB1E6AD2B36ULL, 0xB8BBDC07AEE584F4ULL, 
            0x02FAAE9518F2FFDDULL, 0x8FE8702C233A9D4EULL, 0x0B2C65AED597A307ULL, 0x740A1C23B3F3C414ULL
        },
        {
            0xFCA04178D30327E9ULL, 0x805FC9C0708E3564ULL, 0x8E74B0E4BF6D885FULL, 0xB1A4E8CCECF0DF09ULL, 
            0x49200DB5BBC632A2ULL, 0xCAA1CFA814AACF47ULL, 0x284BA673B173CEC2ULL, 0x0CA824FDCDDDDF83ULL, 
            0x0AD2E3DBD9F2DE12ULL, 0x07027CEDDFB65C57ULL, 0x53E8F9B5B8B2E126ULL, 0xA47F135F5C0AD5ABULL, 
            0x5AD13DEC1F7914F6ULL, 0x740DDF8BFEC8FD13ULL, 0xD2543304D331C1BFULL, 0x5E48BCC0520F1738ULL, 
            0xC48F19C566F8E0FCULL, 0x9507EC116A303426ULL, 0x5C4D0C159E91A0ACULL, 0x9F3044C3813CB39FULL, 
            0xAD1FD99C5878B01EULL, 0x8216EEF8D0575BE2ULL, 0xB8B80D9B8D57E745ULL, 0xFBA7F795175917D0ULL, 
            0xA0409B01E0FEC181ULL, 0x6DC6E28183154DD7ULL, 0xD2D55FA57E52723CULL, 0xBA6A845E0B61E26BULL, 
            0xD43E628DA6EF08F1ULL, 0x82612A7F7116BB08ULL, 0xA62B39BF25163E95ULL, 0x2402ED60C2B8D270ULL
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
            0xAE82993F4AF8288DULL, 0x8234A0039DF588A9ULL, 0xA5DB16F7A550BED7ULL, 0xB95502E727FDA9EDULL, 
            0xD724D25543C4956DULL, 0x98F91CEFE42F6281ULL, 0xFE8A6C73169D2D1CULL, 0xFF9EA3C11AB8FEC6ULL, 
            0x9FE0AAC4EACA93E6ULL, 0x4F9FBAD5F38D55C0ULL, 0x941934807728270AULL, 0xA76822B316B5A1F6ULL, 
            0x33CBE3E4F23DCCABULL, 0xAF31E9C0B8A03EACULL, 0x515D6E53016EB529ULL, 0x966D5561216F9284ULL, 
            0x328387FD6800B360ULL, 0x626DC84774DAB9FBULL, 0xC3DBAEE0D01A7EF1ULL, 0xAC638C63C3CF1B70ULL, 
            0xA05562D16363287EULL, 0xEC0563AC4CE682D0ULL, 0xA8B164F6C1A3C892ULL, 0x7E125E99319583EEULL, 
            0xF9B1997B9850AE42ULL, 0x48F3E6A2F07640F3ULL, 0xBB843D63670A6F43ULL, 0xE32694127BC6E649ULL, 
            0x9C9AB8C7DA38F04BULL, 0x58769095C9635F65ULL, 0x12CF54ED4C32C8B2ULL, 0x55060C01DA1A69BFULL
        },
        {
            0x3415681C6BDA6FF1ULL, 0x1B8433053597EDA4ULL, 0x2B49C6D906322178ULL, 0x464862D065E0FAC6ULL, 
            0xC3F02B433FC2F378ULL, 0x1A9B618F98D8843EULL, 0xF1AFCAF6E3EEF398ULL, 0xFEA56F5BEF387092ULL, 
            0x8AFFF15C4C11CBBBULL, 0xA0B31FF481E99AE4ULL, 0xCA688E42C51AC38EULL, 0xFA38CE791F4CBB43ULL, 
            0x102AF635D4F87E8BULL, 0xEB0C19B98199A232ULL, 0x28076E9121F6F00EULL, 0xCF7C728170143ABDULL, 
            0x885E0C15B6018FDEULL, 0x138370AC38B99279ULL, 0x3AA089050BE828B4ULL, 0x4B60EAE4F8684F23ULL, 
            0x956D91963B2383BBULL, 0x5E634DB67EAFE33FULL, 0xED14A8CCC889D3E4ULL, 0x1471C3A965669E14ULL, 
            0x6AC79EC6B7A9CE1FULL, 0xADFC9DE8AF174AE9ULL, 0xAE0BC4B7E6C28CBDULL, 0x1B6BDF0BA2B2518CULL, 
            0xFD831D70BF7E7DA2ULL, 0x20E0BF36C6925F77ULL, 0x46912407B2564A65ULL, 0xD17CCB14D50D8E90ULL
        },
        {
            0xD4715444EE3878DBULL, 0xC67C27BCE95509EDULL, 0x102F1218BBDC0253ULL, 0x70585B7A69E67AC1ULL, 
            0x0DECDCE989E23C4EULL, 0x7B2EA736BCF8171FULL, 0x50BAA9EC67907279ULL, 0x052219AC3AD308EDULL, 
            0xB8932AFCBA6175DCULL, 0x72895C67C59A85A7ULL, 0xD9B6C01AA4602436ULL, 0x79689EA4F276C718ULL, 
            0x7157BC934A48A6DDULL, 0xDFC732D3EA5A1E70ULL, 0x560864A5286BF85BULL, 0x49F93DCB0F422E1CULL, 
            0x0FE979D1F1430D6EULL, 0xA225297A28D92552ULL, 0xE8E083BF35F62575ULL, 0x1146DAD1C04C5C07ULL, 
            0xB0B5833E6369861CULL, 0xA0EBD3E4A119C68BULL, 0xEA56334002D6852DULL, 0x2C052D214B2A5B71ULL, 
            0x50DA2B113BC3AD43ULL, 0x217542BDA4050B7FULL, 0x8A10D6F7DD0200B9ULL, 0x2D7484C05BD0DC69ULL, 
            0xF5A044857A4D3EC7ULL, 0x65DFCB482FD04151ULL, 0x41E90DD27F0688EAULL, 0x8EC88627AC8BA9E3ULL
        }
    },
    {
        {
            0xB06D7992076F9A9CULL, 0x4B75F537C6D62FEAULL, 0x6076BDCBC775A8C8ULL, 0x86EE6766E46C3BEEULL, 
            0x288DD0A48F2F8C8EULL, 0x955A731594FD0816ULL, 0x260F99CA7DEC49E5ULL, 0xAE495C96039D0BB6ULL, 
            0x51C7BA68B92E7EFBULL, 0x54E75B065595CAC0ULL, 0x2F6AC5F1427CCB41ULL, 0x8FA77B0D76E39525ULL, 
            0xC753E3AC8A6B6701ULL, 0xF72F9CF5B006BF71ULL, 0x018C9399A970385AULL, 0x8E00C29FA5823B38ULL, 
            0xEFE5070CBD1E8AD8ULL, 0x1D5F83968EC7650EULL, 0xE3032A27CC891662ULL, 0xE60EDBB697B46633ULL, 
            0x11EC7FA59EF9354DULL, 0xEC99573462796887ULL, 0xC0CC2A5B597618D7ULL, 0x1D9D95B202668C62ULL, 
            0x2DB6469F7F61803DULL, 0x35F93311304EF09FULL, 0x2FE6E55B99693C99ULL, 0xFD9A8033518E402FULL, 
            0xB01017A5617159ACULL, 0x40DB288F68C8F9B1ULL, 0x15935A54246A2DFEULL, 0xF032484A7B4C0D1AULL
        },
        {
            0xF1D63ECC45572163ULL, 0x3FB3DABD59CD8E75ULL, 0x1E942066BF0395B1ULL, 0xAEF6D8CF63B5C984ULL, 
            0xB129CB428899598DULL, 0x0D04D811815CA87DULL, 0x5F2D3D26B9DA0A6EULL, 0x16C14B38F08F0A74ULL, 
            0xAFC4752C61A7E0C6ULL, 0xA76165B2CC35AA6FULL, 0xCEFAB9D47DBB6562ULL, 0xE0CA2FC7C971375DULL, 
            0x1D46E04447A0ED40ULL, 0xB96236DBC25688EDULL, 0xFE11B1C9AA914214ULL, 0xADF801F6341BA6EDULL, 
            0x087BFA4D4D71FC61ULL, 0x59275B9405206695ULL, 0x64CA777985EBECB8ULL, 0xEB14E56A64F1E3ADULL, 
            0xA719F0B74851FD9EULL, 0xD34834AB33D14BD7ULL, 0x7463D14AD3E57854ULL, 0xB2FD6BC6BE0AE37FULL, 
            0x9E58458A7CF30703ULL, 0x448970F240C73CEAULL, 0x818F8494515979AEULL, 0x89D48BC091C32A72ULL, 
            0x00259A3FB8BEA960ULL, 0x5161841AD8F4EE9CULL, 0x2741C6CECFD80ADEULL, 0x6C3199A0B473C30AULL
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
        },
        {
            0x6E3088E9685E00ABULL, 0x9A1B5344C7008276ULL, 0x6D4D936359581568ULL, 0x84EFFA1467654E96ULL, 
            0x7231934BC381A2ACULL, 0x1E7F209363112001ULL, 0x7A3470FDB3A02722ULL, 0x762A4D3BC03EEE98ULL, 
            0x3E5B2C99C2482214ULL, 0xC66D97C8C6621981ULL, 0xF2E886F8404FA034ULL, 0xEC451CB073DD5D52ULL, 
            0xF8295F3D0B2F5781ULL, 0xCAF22012E0342691ULL, 0x5162D36CD4C58CCDULL, 0x461AC378A1EEA4A5ULL, 
            0xDCC18D691FEA7BC9ULL, 0x703B0A46860A78ACULL, 0x8401D717C799BBB3ULL, 0x50BDD45AAF8A65ABULL, 
            0x799936DCDEF57E60ULL, 0x3C083D1DC429A6E1ULL, 0x9B70933F842BFF9DULL, 0x3D154A67178102C5ULL, 
            0x852949D09BBA93CFULL, 0xEE26BB0CB213B981ULL, 0x47B597C440340D58ULL, 0x86F5274505DDA7D6ULL, 
            0xC79DD392979BAA44ULL, 0x931CE10909C7D805ULL, 0x5F743C5702A9DBBDULL, 0x73440F4731B15BCCULL
        },
        {
            0x69B554C6FC53B086ULL, 0x5C2F161940BE30E8ULL, 0x0A27AC9E1AB56B20ULL, 0xE500A52AA1649D00ULL, 
            0xC304ACF03A26B493ULL, 0x5EE04CD662D920D2ULL, 0xF714874C436B3509ULL, 0x3014DD6DFF44E010ULL, 
            0xFFEC5E369A0B19E7ULL, 0xD95855381198B619ULL, 0x5737A1C38776785AULL, 0x518D63A53857D964ULL, 
            0xB8C54936C51B6169ULL, 0xC4C044FDE0057A9CULL, 0xDC73971748BB5A88ULL, 0x3F9406525D75D65AULL, 
            0xFE7E8978483EA0CFULL, 0x5E8741333C26CED5ULL, 0x5A66EE73FA04DFC5ULL, 0xBFFC0D8B940ACC21ULL, 
            0xAFFC050BA239B959ULL, 0x79F7353379942D57ULL, 0xD59AD2669F8EAA89ULL, 0xCB925E8EC324B8BFULL, 
            0xA2C530CB5517CD7EULL, 0xA63D1D0D392084F8ULL, 0x19E998F2B3C293DEULL, 0x536F57A5E1F4E7D8ULL, 
            0x76CBAABE8F492DCBULL, 0xE7699A1F7A478A8FULL, 0xBE32A4AA4F8B9D70ULL, 0xA6A6F3E4479BD4C2ULL
        },
        {
            0xF1A8AF3B450A4187ULL, 0xF499013EBFCBBE9DULL, 0x588CC423EF52FC7FULL, 0x3A05C99F1BB7A2D8ULL, 
            0x70960EBADAB078F6ULL, 0xBC08A462F46D7E4FULL, 0x9A6A4722271313F9ULL, 0x81A5C9E32A1C5DC0ULL, 
            0x69F4B36EE797E85EULL, 0xE94C9E34D7572A1DULL, 0x9A130CD55E4EECD0ULL, 0x964BEB01565B7A7CULL, 
            0x060C623AB14E9387ULL, 0xCEC703079D7B9194ULL, 0x7F4F524D42FF011FULL, 0xE91F963DA422C0CAULL, 
            0x24178D75C0FBD4EFULL, 0xA0B7BD658F0CE91FULL, 0x906E33C19619F1C3ULL, 0xFDD566379595A6E4ULL, 
            0x73F0485AC9F28D03ULL, 0x674AFE4924292092ULL, 0xE9F03B1502A0CDCBULL, 0xA42423DEFB40269DULL, 
            0x2833938C2FAFD381ULL, 0x6DB2B1C26610403AULL, 0x4DC17776FA536769ULL, 0x0249FD22FEB7AF13ULL, 
            0x56FFFBF58740894DULL, 0xEA8AA6EF6FF2CF01ULL, 0x7C7529CA8359F049ULL, 0x44E9B3844330A827ULL
        }
    },
    {
        {
            0xCC7DABBF2F52C195ULL, 0x900273975C447A8CULL, 0xF3C852A1C65F3254ULL, 0x1E4B323CE3AF5E80ULL, 
            0xE79BE66F2ABF6659ULL, 0x0BD56EFDC5DE49B8ULL, 0x2E9E1B7FF2CC93BEULL, 0xD1EA7137CE9A784AULL, 
            0x5ACA1648DD57B44AULL, 0xAFC5A33E56A9C7B4ULL, 0x8BECBC0266484C00ULL, 0x0A65B11F0D359DE6ULL, 
            0xFB6932C001DA5159ULL, 0xC58D251496603791ULL, 0x68F03FDACFA0E96CULL, 0x49CACE15E2ED8851ULL, 
            0x122E3ABCD6FFC6F8ULL, 0xF05C31CAAB5A5150ULL, 0x4187C919A544A7EFULL, 0xD400AFC5FDD41039ULL, 
            0xCEDC43FDD721E7B6ULL, 0xB4DD5E90B0781AE3ULL, 0x912174557E3C6AA0ULL, 0xB7D21E38DDA630C8ULL, 
            0x3278B2C5152D3680ULL, 0x3343F282C0BDB907ULL, 0xB23406DC0E9035D9ULL, 0x054519859AFF9E00ULL, 
            0xF36280557AA4D593ULL, 0x1EE86CA2D9F3791DULL, 0x7CCB8C33EC43C448ULL, 0x00E64D11C5EC859DULL
        },
        {
            0xB80D95DE966845A6ULL, 0xA3FC2F0E006B834BULL, 0x08E3AD89E875F847ULL, 0xAFBE68C5C8421EC2ULL, 
            0xD7C79E8D25A49C0AULL, 0x432A7987B034C29CULL, 0x7B45CAE4505EB112ULL, 0xBA7E49F5E0111DB3ULL, 
            0x92FF249AD5DE3536ULL, 0x2BD9814528DE9F19ULL, 0xB278F49122CD25ABULL, 0xA3AFB6BA4F21DB97ULL, 
            0xDE6D02EAFFF3581EULL, 0xD0879747575E8615ULL, 0xC5236554D8F2C2F6ULL, 0x655DD90ECB8D7097ULL, 
            0x1EFF346A407DA42FULL, 0x14C56E13DC88691EULL, 0xD2EB730B8D991C0FULL, 0x5B3B3E33E46B4498ULL, 
            0x94B39FBD0B04D603ULL, 0x3DC7A62D9FAE32CDULL, 0x7D9DD5D621F36BCFULL, 0x92D4C801245BEB87ULL, 
            0x8B5EB956AD8DF6C1ULL, 0x2049C1CC758CA74FULL, 0xACD266873633283BULL, 0xB0991D6198F86A39ULL, 
            0x93288DF0234D2C86ULL, 0xD24EB81FA2C18B46ULL, 0x225E81F364462E30ULL, 0x47EF43B64BC2CBDAULL
        },
        {
            0xE3F9F041D24704C6ULL, 0x8B3F8C5749FA03C0ULL, 0x65E5B158DC67C080ULL, 0x229D14434B37E16AULL, 
            0x1E875CC7B6E8B10FULL, 0xDCC6ABC199FB6E35ULL, 0x50AF003F535D0CACULL, 0xF920C098F80B6403ULL, 
            0xF8D8F98350162271ULL, 0xF19245CCB2423425ULL, 0x762EAED0493FF96BULL, 0x195701E4FD1E771AULL, 
            0x8B134827C5DB553BULL, 0xC9C54C7F1C3F6EE3ULL, 0xDE68615DFA15C97EULL, 0xE6419C9176929D55ULL, 
            0x824CF973B14EB72CULL, 0xDF61B581AD933B5FULL, 0x194F8273E7314099ULL, 0x9FCB41FBB469F1DBULL, 
            0xC8B3C214E377CDC0ULL, 0x2F1900F798AF2CA2ULL, 0x2092F45EEFB9A7D1ULL, 0x674AAE953D64B2C7ULL, 
            0x31AB24446F8BC96AULL, 0x8D1D10D8C9BA5BABULL, 0xBD5E73AE90E13362ULL, 0x1F8851BC552B9628ULL, 
            0x2B2AFCE6D4F2730FULL, 0xE9DE2E1A177DD22BULL, 0x380A18E269847FCBULL, 0xBEA49ADDA2EA6CF3ULL
        },
        {
            0xD9A11DD5820D232EULL, 0xD40161182D2EE01CULL, 0xD03C33FB17DE9354ULL, 0xC21A8E7EF1BFAF40ULL, 
            0xB6E47D0A811AACBEULL, 0xB241DB747F6484DBULL, 0x7C193F603FE5B4D1ULL, 0xAAB1F5EFC737EB3CULL, 
            0xB9593DBD6F3DEF23ULL, 0xC5FA7FD137A847BAULL, 0x163CEABDB4C3B6DCULL, 0xD7E1041E50C39DC5ULL, 
            0x2B1D369FD8A482FAULL, 0x1E70426F88B2B4FFULL, 0x6810EC397838B087ULL, 0x6144C1EAA8EE3603ULL, 
            0xFB1D07E3B69B6AA7ULL, 0xB05EE664DFCF08F6ULL, 0x0AD6E959A25936D0ULL, 0x044D75234EFEFA97ULL, 
            0xC6E4FE2CC3BEB810ULL, 0xCB4675C72305CA19ULL, 0x082DBCDD3ADB89E2ULL, 0xB360D3BCB2C2D0E9ULL, 
            0x15205A71E58B0317ULL, 0x0F62566B80D0902FULL, 0xA7F16523213EBEB6ULL, 0x85AE7886C9ECBD97ULL, 
            0xBA43D1FE50A06D7FULL, 0x8FB7767387E30347ULL, 0xB9DB53E4F3E0FE4BULL, 0x4C2C28C723526851ULL
        },
        {
            0x019DC32B4E5683E2ULL, 0x65A22D2E089C9AC1ULL, 0x06BFE802D38B60E0ULL, 0xEC3F0F0E7B68C003ULL, 
            0x5FC63525CD339E46ULL, 0x11430D8B8BE862A5ULL, 0x77CECE6AD60B1F9BULL, 0x1A0CD5F61D58C6D8ULL, 
            0xC5BFF224356FFCB8ULL, 0x55712E1178B5E76EULL, 0x87B227EEAD1F869DULL, 0xD961EBB749EBFF99ULL, 
            0x5222B900BBA4C2FCULL, 0xC22327587C825921ULL, 0xF83BEAEF9CEB178FULL, 0x20D2B900D1FBD631ULL, 
            0xBCE9889996FA07DCULL, 0x04477A23C8D655A2ULL, 0x6EF6BA7CAB421768ULL, 0x81B9FE2BBA181631ULL, 
            0x5895EE080AA27035ULL, 0x82A29CB17D82700CULL, 0x89D7C82EF780DDCFULL, 0xE51B92E347437034ULL, 
            0x65534C9AA363CBD2ULL, 0xE7F4497C9110D34FULL, 0x476FFD79872E5D47ULL, 0x6C6A282EF75B52B7ULL, 
            0x8F24E5E225921C71ULL, 0xB16B27769668314CULL, 0x11753A8620E37668ULL, 0x28401EA5B963CFB7ULL
        },
        {
            0xA537EBA414A13BDDULL, 0x0D6967115D430E48ULL, 0x5FD6A2A1E0BA5493ULL, 0x6822C56D736335E1ULL, 
            0x96D5E9443B030A7BULL, 0x633C1A52EC885569ULL, 0xA29FE0F7263D9E16ULL, 0x47F69F38C143386BULL, 
            0x5A5AD53D559322D5ULL, 0x2CCB350AEB292AABULL, 0xEB878F18EE1FE0E2ULL, 0xC32D364CDAC90AC1ULL, 
            0xC638A526FB614A24ULL, 0x6DB40E04C82CFC70ULL, 0xC1D5F9ADC9042303ULL, 0xBE76E2D57AF38681ULL, 
            0xC624101A7652EF2FULL, 0x34C89F00209AC639ULL, 0xB34B2CC38B64CC4EULL, 0xBB7DB3D71B7BB11CULL, 
            0xE66602B0B383A520ULL, 0x9B00B287B57569D0ULL, 0x2732D8010ABBDC31ULL, 0x3DA9ADBA687C41F6ULL, 
            0x8401B8FA18E1F30AULL, 0x010CDAF06453089CULL, 0xE910777E80894088ULL, 0x69728A95BEF019E3ULL, 
            0xC9FC7537CDB2A07DULL, 0xA9EF5BD932C7F5C7ULL, 0x74136D1C7C6D36A9ULL, 0xF6043864C35DE96FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Bellatrix::kPhaseHConstants = {
    0x77B07F2760898B8CULL,
    0x527D1440980C8346ULL,
    0x462697364301AE2BULL,
    0x77B07F2760898B8CULL,
    0x527D1440980C8346ULL,
    0x462697364301AE2BULL,
    0xA1B111B46284C489ULL,
    0x981B040399C05E41ULL,
    0x72,
    0x3D,
    0x64,
    0x8A,
    0xFB,
    0xE4,
    0xE2,
    0x4B
};

