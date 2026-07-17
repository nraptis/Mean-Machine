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
    std::uint64_t aPrevious = 0xE7B939EDDFAF6CE2ULL; std::uint64_t aIngress = 0x9137E84FC28E9700ULL; std::uint64_t aCarry = 0x9862A2978AE2555FULL;

    std::uint64_t aWandererA = 0xFA1639716F7E577FULL; std::uint64_t aWandererB = 0x95FFAB84AAF1D943ULL; std::uint64_t aWandererC = 0xCC90410A4364402DULL; std::uint64_t aWandererD = 0xFA35B73AE17E7FDDULL;
    std::uint64_t aWandererE = 0xD419F599AA1AE93AULL; std::uint64_t aWandererF = 0xCD9E979853C91546ULL; std::uint64_t aWandererG = 0x8670D6D7EEE99304ULL; std::uint64_t aWandererH = 0xE22F5B8B897BF7D0ULL;
    std::uint64_t aWandererI = 0xC7036DF2E9674757ULL; std::uint64_t aWandererJ = 0xC63D88408D0057EFULL; std::uint64_t aWandererK = 0xD55057682AB93A1EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15033912791938275667U;
        aCarry = 15543002269195866190U;
        aWandererA = 15744673506282509493U;
        aWandererB = 13193043539751126176U;
        aWandererC = 13927361170090211174U;
        aWandererD = 17937678513920060705U;
        aWandererE = 15620207214252894317U;
        aWandererF = 15040106541355379687U;
        aWandererG = 12956325918878974288U;
        aWandererH = 12217794172692436664U;
        aWandererI = 16338024570329969150U;
        aWandererJ = 10940211442158306377U;
        aWandererK = 14162423226737292584U;
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

    TwistExpander_Alioth_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alioth_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alioth_Arx::KDF_A_E(pWorkSpace,
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
    std::uint64_t aPrevious = 0xD571CC5216E8EBE3ULL; std::uint64_t aIngress = 0xC7C788ED9CEDFA75ULL; std::uint64_t aCarry = 0xBF36D745EFE92E08ULL;

    std::uint64_t aWandererA = 0xD6E9096821B00ED6ULL; std::uint64_t aWandererB = 0xAA856B83322DE6B7ULL; std::uint64_t aWandererC = 0xBD87F2EE984722AFULL; std::uint64_t aWandererD = 0xF2A5B161910030B4ULL;
    std::uint64_t aWandererE = 0xB9E4EAB286D8F3A5ULL; std::uint64_t aWandererF = 0xEF5766392B1EA5C4ULL; std::uint64_t aWandererG = 0xFEE7F457C7EC13CFULL; std::uint64_t aWandererH = 0xD8ED8590F49738D8ULL;
    std::uint64_t aWandererI = 0xAA1C7BD5C1987379ULL; std::uint64_t aWandererJ = 0x8120F386685E6452ULL; std::uint64_t aWandererK = 0xA5051FB313C66312ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13949374598214047386U;
        aCarry = 17143437547128104142U;
        aWandererA = 17042696305999856052U;
        aWandererB = 12958812127087918910U;
        aWandererC = 12801398753383343329U;
        aWandererD = 14858678211874653220U;
        aWandererE = 15353578611156049041U;
        aWandererF = 18035066437480529226U;
        aWandererG = 16359300831028216206U;
        aWandererH = 11979018199195816445U;
        aWandererI = 10165092964030245884U;
        aWandererJ = 9555681825032458865U;
        aWandererK = 11648022360012464079U;
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
    std::uint64_t aPrevious = 0x80D8F87D57663D4EULL;
    std::uint64_t aIngress = 0xD4EE700CB5436818ULL;
    std::uint64_t aCarry = 0xBBF37C916801B1FAULL;

    std::uint64_t aWandererA = 0xD975413E35F2855BULL;
    std::uint64_t aWandererB = 0xC8F71D2F19F8232EULL;
    std::uint64_t aWandererC = 0xDF75531EFCE2E7CBULL;
    std::uint64_t aWandererD = 0xBF37D5AEDE9B278FULL;
    std::uint64_t aWandererE = 0xB19D32B2EAB499DBULL;
    std::uint64_t aWandererF = 0xDE3BBB175E27E7A3ULL;
    std::uint64_t aWandererG = 0xF37DC2C9B0CB263DULL;
    std::uint64_t aWandererH = 0xC1032AFED1E071FDULL;
    std::uint64_t aWandererI = 0xA4EEA200494E81C3ULL;
    std::uint64_t aWandererJ = 0xF0D5C8ADBDB6BEC1ULL;
    std::uint64_t aWandererK = 0xDCB7D7E4F96A75C2ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneD, 2);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneE);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneD, 6);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneH);
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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

        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
    std::uint64_t aPrevious = 0xE6AB1C687BF3B3CBULL; std::uint64_t aIngress = 0xF4B524018F2A8085ULL; std::uint64_t aCarry = 0xCE5CB768E4D00CD8ULL;

    std::uint64_t aWandererA = 0xD157ED74ED40EEAAULL; std::uint64_t aWandererB = 0xAE41DE9059DE9BB4ULL; std::uint64_t aWandererC = 0x808340A3CC7C3C86ULL; std::uint64_t aWandererD = 0xE4CAA4A36286E266ULL;
    std::uint64_t aWandererE = 0xF3D724E56F95063DULL; std::uint64_t aWandererF = 0xA72678ED7B7EC64EULL; std::uint64_t aWandererG = 0xB20F8C3EB3F160AFULL; std::uint64_t aWandererH = 0xF876DFF9B5646B07ULL;
    std::uint64_t aWandererI = 0xB5478C461622C166ULL; std::uint64_t aWandererJ = 0xE80F831A39D55495ULL; std::uint64_t aWandererK = 0xCE72EA18B8536DF0ULL;

    // [seed]
        aPrevious = 12853050698793027660U;
        aCarry = 9573988882042513433U;
        aWandererA = 15438625207416163228U;
        aWandererB = 17603339387051239777U;
        aWandererC = 11102160611658153185U;
        aWandererD = 17239010737256009043U;
        aWandererE = 9790412726747168271U;
        aWandererF = 16514150160463507863U;
        aWandererG = 16991085361748232784U;
        aWandererH = 11191011480442004384U;
        aWandererI = 12912429807338005382U;
        aWandererJ = 10330052631430821899U;
        aWandererK = 16673782001156573089U;
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Alioth_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alioth_Arx::Twist_G(pWorkSpace,
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
            0x303F0DBEA304F096ULL, 0xF28EFCE3DACFF7CAULL, 0x00880818EC6CE7BCULL, 0xFA6BD99E544A3477ULL, 
            0xAD78D20ADAFE3D69ULL, 0x45927E3457C6EB78ULL, 0x34CEF8017E35D71DULL, 0x0DD8B99772D8BDACULL, 
            0x1D140D70A8B42477ULL, 0x35D3C1A66EA80021ULL, 0x26DF18D74C9BE099ULL, 0x1276391BCD57159AULL, 
            0x319796CDF79B89FEULL, 0xF951B554D0BC9C86ULL, 0x0A092E125429BB5BULL, 0x89E16CD218995F9FULL, 
            0x8185ED831DF0B4CBULL, 0x833FAD9DE3DD6A67ULL, 0xDCB3DD4001506B00ULL, 0x4BA8B321C66923C8ULL, 
            0x3360D873C41ECB1FULL, 0x09D8615FFCCE61DAULL, 0x88001C10ADAB2B61ULL, 0xA65A1D8A2186211BULL, 
            0x40EF882466979107ULL, 0x0336A33C9D6D688EULL, 0xF1F00F17EE70EC79ULL, 0x4FEDBAE67250E87EULL, 
            0x5D2D2B85B8C05159ULL, 0xE3010F31F444DFB4ULL, 0x5685712C0DACC7B1ULL, 0xF04D0F547D036FC2ULL
        },
        {
            0x7F3181CA0EE80F7BULL, 0xDCC0140600AD4A7EULL, 0xE0BDC35C3836F4E3ULL, 0xA178D442342AA8EDULL, 
            0x11FC17496B743399ULL, 0x713A16020DBB7A93ULL, 0x205A0EB6EB9CC85EULL, 0x23FACEAAEFE51E11ULL, 
            0x7B71B5EF12A8F092ULL, 0xFEEDB055BDB2437EULL, 0xFE2770DA2A894508ULL, 0xFBA0070073968EC3ULL, 
            0x9E1EEE24D5E4FE9BULL, 0x24E720850B923552ULL, 0xE934A36B9E43A14AULL, 0x1A26F5974CCD1824ULL, 
            0x67C8C2ECF56E1357ULL, 0x562810CCD8DB71BBULL, 0x660EBC32798ABC57ULL, 0x777B2404D8365687ULL, 
            0xF33CDD5D294DD0F8ULL, 0xC896B4B7E505CA91ULL, 0x3C9940B33543632BULL, 0xC3F1BC830A850BF5ULL, 
            0x898088C92C7CA0F7ULL, 0xE42F098A82310638ULL, 0x8F9CF943BF615244ULL, 0xFC280A0C227CF1E0ULL, 
            0x25B6A98838C4D56DULL, 0x3893E82B1C4134D3ULL, 0x1BF4404814E766AFULL, 0xA1DD883D0922131BULL
        },
        {
            0xF1FDDF1A79C75434ULL, 0xD2E22F2EE51807DBULL, 0xB1679CF368B53C84ULL, 0x89D8FECB2CBAA87BULL, 
            0xD930B680BF98995FULL, 0xDC933D8A4579945CULL, 0x30272A06D98CABF2ULL, 0x05E108BB1AF38637ULL, 
            0x8DFB753B4D69EA3EULL, 0xCAC73B425608564AULL, 0x78B1EE3D3BDED8C1ULL, 0x0C37CFCF8B6EC0A0ULL, 
            0xBBC0214AC7FD293FULL, 0xF0EC49B44895F3B7ULL, 0x86CBD03A56F42466ULL, 0x588BE3521F97935DULL, 
            0x003FFB95ADEEBE5CULL, 0x7264B78DA062EEFCULL, 0xE3305BAC92DF54ECULL, 0xC30FF55EA1979EB1ULL, 
            0x457BFB5ED4503858ULL, 0x6F39D1933BFFDA3EULL, 0xA89044C8B9D3D570ULL, 0xAB83C4593C5D257DULL, 
            0x43717498E98A7740ULL, 0x7B480214CBCD17DBULL, 0x0288095E7D18E2DAULL, 0xE863E0E4CADC64F4ULL, 
            0x8ECC6F6070727253ULL, 0xAB629922A7F26D11ULL, 0x1B15CEA4D2A2C05EULL, 0xAFE7B3C6D7ADFCAFULL
        },
        {
            0xB609511FF47E18B1ULL, 0x9DB20AA9749BF92CULL, 0x64B5E82D53A143F4ULL, 0xD4C52CA8C18C8EE1ULL, 
            0x7938B95F24EFAEEFULL, 0xC05620DB82D74D3AULL, 0x1A7CAB3D738487C4ULL, 0x6BB08AA41538A239ULL, 
            0x096C9C29DE10B123ULL, 0xEE0CC90635B73990ULL, 0xC90A54A045B9E564ULL, 0x68B7A5C5C0DD0471ULL, 
            0xA1427E0AC418D5C8ULL, 0x6D2E5815D3E81BCBULL, 0x1F3A3AEE9E1B750FULL, 0xB0E0DE0B55206477ULL, 
            0x1D8B851438875213ULL, 0xD05F1781E725B931ULL, 0xFEFD5ED1B8B08B4DULL, 0x480F1720A2D03482ULL, 
            0x517255027CEC5C25ULL, 0x368C1BC6FD82E780ULL, 0xB65F1E54F1A8537AULL, 0xBFFDE2077033FB7DULL, 
            0x577BE1E7F9A6FAEEULL, 0x7D88900120F5EFAAULL, 0xEE281F3EDB266008ULL, 0x66826AD587020E36ULL, 
            0x45460C685C67A8D1ULL, 0x17ABAE24BE084A88ULL, 0x431D7217ED34F918ULL, 0x3110A5DCA0C3683FULL
        },
        {
            0x05FC1AC73DCAC1B7ULL, 0xA31FFF6E6F8ED7F0ULL, 0xAAE9A59E6147BD44ULL, 0xDD11E4A5C8A2A7BBULL, 
            0x388D3188A93119EDULL, 0xEFF3CE81488852DCULL, 0xD729389417C0730EULL, 0x84305A951DFF6857ULL, 
            0x0DB1BBBEEA0322CEULL, 0xCAD77F2A2927751CULL, 0x91A57F92904A40C4ULL, 0xE33F4CD2B03BDE3CULL, 
            0x74FE482A2D7E301BULL, 0xBB538544F5CF4269ULL, 0x3F1D94F9E551CB3EULL, 0x0C6DB100740CC9A8ULL, 
            0x7E49C6FA273F39FCULL, 0xBE13CC4443F37000ULL, 0x593DB3F255C2331BULL, 0x89FBDEAB970EFCBFULL, 
            0xEA4C9BE38F00413BULL, 0xCA89F12E9E84CB66ULL, 0x31B40F283103581BULL, 0x2E82E96481F154A8ULL, 
            0x102C8E5A5C218837ULL, 0x2FFF79DA46B3DA8DULL, 0x5D2A359752ED346FULL, 0x111A9000C64E2C1DULL, 
            0x225D6D60CF022D57ULL, 0xCA86CBFA7BCB140EULL, 0x2EF86BA0758D9D96ULL, 0x1F6511B5A79F4972ULL
        },
        {
            0x9FC86733667A1A14ULL, 0x919CBD63723666C8ULL, 0x21E139A2C4DBBD6EULL, 0xBCCD7C2DC6D6DEC5ULL, 
            0x311F4E118B5346EEULL, 0xA8E22B5F45EE98D7ULL, 0x3BF593AC54754E94ULL, 0xD278E7ADE7BDA633ULL, 
            0xEE6735FF118DC947ULL, 0x249006E47BD5E091ULL, 0xF4667B7EAE12BB99ULL, 0x67EFC65A61CCEB78ULL, 
            0x3A08D3D5D7A43EC9ULL, 0xF3B1130CBF1219FEULL, 0x2EAF604982B4DCEDULL, 0x6E8C7D2B4F17900EULL, 
            0xB9B93C31F2F6C35EULL, 0xCBECBF049C3AFE73ULL, 0x354EF2D7F539A740ULL, 0x3D27DE11198DD47CULL, 
            0xD9EF154A20132490ULL, 0xB24D3428E77D3B35ULL, 0xCE73C490463D070AULL, 0x7B863850A686F965ULL, 
            0x4DE82E4BF7CA9E32ULL, 0x1E7E179A08A881C3ULL, 0xA0BF75C553778394ULL, 0xC5312ACC906A9E5FULL, 
            0x9DF327B622A4CE7DULL, 0x3A87076AD5A6EFBDULL, 0x81AA03AE0DE4D4AEULL, 0x4E40F1069620D903ULL
        }
    },
    {
        {
            0xB63D2776C14C425FULL, 0x4F97BCECA79B4120ULL, 0xF986AF0E8A67B099ULL, 0x3AB61F97F78375F9ULL, 
            0x1D8C438556E94FCFULL, 0x75C50BB4E6F38CDAULL, 0xEECE7BFB2619FD59ULL, 0x6DE7EC45CACE2BD6ULL, 
            0x21053846EEA9A36BULL, 0x981744B1BB9AB8ECULL, 0x9BB0EB3F5798C2B3ULL, 0x3F0566F2E323C1EBULL, 
            0xAEE3A81011277757ULL, 0x2D036FCF641D428CULL, 0xF11E6CF453B8280EULL, 0xDD40AE229BBF93DAULL, 
            0x6EC3DBD1568F5516ULL, 0x12D0DAF663FEF6C2ULL, 0x056D1052F3C4E148ULL, 0x6C95E26BC474FD32ULL, 
            0x50AE266E53E05D33ULL, 0x1D1E72F20F82A472ULL, 0xE1A7CA6279648D99ULL, 0xAB8CE6AD82B38848ULL, 
            0x779EE51D1D750458ULL, 0xE69A12BA302B2526ULL, 0xDBE87180F473D572ULL, 0x57EA395208CABCC1ULL, 
            0x8B47C2A033A6BB99ULL, 0xA86B6D7EE83ACB2DULL, 0xF5CEF7222D2453BBULL, 0xBC5CAA194404E7EDULL
        },
        {
            0x0AC4B65A20B98323ULL, 0xDF72336E80A3DA1EULL, 0x576CB3E52C1C5A9AULL, 0x5299E8C7A474C512ULL, 
            0xABE09B1CCBC62F31ULL, 0x6681141F752ADA01ULL, 0x1401EA187D8C37ADULL, 0xE392620F4A625B4CULL, 
            0xFD289B882518DE41ULL, 0xF87D01F2ECA261F1ULL, 0x2425DB2D59050386ULL, 0xC785B5D768B856D1ULL, 
            0x33FA413BA2BC45BCULL, 0x20B73843BEF9B776ULL, 0xE1ECDD23CBD62B43ULL, 0x46AE6F8E12C08611ULL, 
            0x96712E4988F6ED0AULL, 0x832380F5EAE2C762ULL, 0x9FDD81308FCFE97EULL, 0xEE00F5994AAC8D2DULL, 
            0xA853253137ACB2B3ULL, 0x0120EF95C38BA798ULL, 0x69A2C2164BE26137ULL, 0x7338821071054884ULL, 
            0x0D7B00A595A43BA5ULL, 0x2BC3FC729BCDF431ULL, 0x15D0E032EC51E8E0ULL, 0xB13D7E72EEDBC2E5ULL, 
            0x304525D00E3F3549ULL, 0xCC2325D44CC0ADC6ULL, 0x9CFA72C2E17EFF53ULL, 0xC2CAC8861A0486E7ULL
        },
        {
            0xA696A819B622FB3FULL, 0xFCB746CFF6745658ULL, 0x467282E68ACD49D7ULL, 0xEE8A2FC9C8F145DAULL, 
            0x7F9E61FF001E42FAULL, 0xFD8E3B90BED5265BULL, 0xD497504145979D43ULL, 0x4C683B41D5F3489AULL, 
            0x627D1864FC2A513FULL, 0xDA4FD7464619B011ULL, 0x5A5B401201BE3144ULL, 0x5FAE4447DD1D672DULL, 
            0xBF55DEDF24CC3920ULL, 0xB66277E566BC537AULL, 0xD19DF70AAD2952E2ULL, 0x1BAA1CD985E72B8AULL, 
            0x9ADCF30C30787F45ULL, 0x2CF1896AD1A13AA4ULL, 0xD9FFCEEA2A21DA75ULL, 0xCBFC5A88EF9FACF6ULL, 
            0x0C7171116DB6BE72ULL, 0xA0A99ACFF7102F9FULL, 0xDFC0FE8272836EE8ULL, 0xB8E1F471BD6555F5ULL, 
            0x9647507B9DDEFFECULL, 0xA35CF952EE182FEDULL, 0x60DF5777CD7BC142ULL, 0xD6A0CC1D1ECDFE59ULL, 
            0xD4BDA49D3700FC4FULL, 0x26E04F816FD33B0BULL, 0x9B65F05D5A316A89ULL, 0x591F167C9E7B9ECAULL
        },
        {
            0xF318D034913E686CULL, 0xAD0E2BD46D212BF9ULL, 0xD387E2BB9BDE422AULL, 0xF70AE35B541ADBDBULL, 
            0x7C0434F937D1DFB1ULL, 0xA4E26DCD7E22C9B0ULL, 0xECC871801E5286E1ULL, 0xA85AE810F628EE2BULL, 
            0x6607107629176FBAULL, 0x1F7712A94B517E42ULL, 0x0AE6B3DC29CEFB12ULL, 0x2DB92617FA767F2EULL, 
            0x5BFE60F7D2B769A3ULL, 0x0330D4619877DE71ULL, 0x480501ED695A20E7ULL, 0x0063BDB497CE7E3CULL, 
            0x451A4EEE3ED13EECULL, 0xA76D12E22987F1EEULL, 0xD4CB33D17BB68A66ULL, 0x52A7CA0D240CCCE9ULL, 
            0x8C4008BF9A30663EULL, 0x44E4A0657B183228ULL, 0x1764C3AC91F22FDFULL, 0x2BBBE48521A2E177ULL, 
            0xD93D453777807D90ULL, 0xA9DBB19AF3AC17B4ULL, 0xACE73A67A3064BF0ULL, 0x76D6B283374A8630ULL, 
            0x2289F802D4307DA9ULL, 0x3A0AA83A9176D7B4ULL, 0x175C6ED94FE349FBULL, 0x6D6AF51741B9C4C5ULL
        },
        {
            0xEA2507B7822C81E2ULL, 0x6F59D55B80EABCFCULL, 0x1C8FB3809B1BB46FULL, 0x2F6819969C5C445AULL, 
            0xB28720A55DE259B0ULL, 0xA128966104687749ULL, 0xA50508562E47DF15ULL, 0xDDF5611A606B0F33ULL, 
            0x0C603083AE5FC0D4ULL, 0xFFA384BF66AAC7C5ULL, 0xDD115D94E622C35BULL, 0x4CE4A7DD88940933ULL, 
            0x0A9A93EAE4040AE4ULL, 0x1ACCEE543FB160ADULL, 0x83104409A81E7CB9ULL, 0xB67B41567EF78B29ULL, 
            0x3237F3B20A4FDC58ULL, 0x22F2A98FED7EBAF1ULL, 0x99571257FF57B00EULL, 0x0A1505326F37247DULL, 
            0x2EF0A59253A3554DULL, 0x1A85A531D0F9310CULL, 0xB9FE4C03EB19F643ULL, 0x7532BD5E406FF3F0ULL, 
            0xE4685766ACC34F16ULL, 0x34A029667CA27DF0ULL, 0xA0F5DB7729901F28ULL, 0x5143ED616725E2ACULL, 
            0xB675CDD740BF773CULL, 0x5BDD67DE577221C3ULL, 0x15F4775BA6A91FCFULL, 0x9538585630489DCDULL
        },
        {
            0x79681A0BD01D4C84ULL, 0x67AF43E8FA14C781ULL, 0x8AC987151C800282ULL, 0x05A8C0A827DE3FBDULL, 
            0xBBDEB5C4A63016B9ULL, 0x2DCE210A7FDDB6E0ULL, 0xB5902650BF7CEFD5ULL, 0x692B79CE1D94D639ULL, 
            0x9362E4161CC4DBF2ULL, 0xF44E43E715BF9826ULL, 0x26DEEF5AB5A6443AULL, 0x73EBD6141F5E08E6ULL, 
            0xE42A207E28981357ULL, 0xF35B4C6F3FF8DA8CULL, 0x314956BC53788F28ULL, 0xF4B90C63E1791520ULL, 
            0x536D719119C97455ULL, 0x799D25032E63935EULL, 0x0DBD857589B46493ULL, 0x60FA603408C397DCULL, 
            0x877B620E08C78793ULL, 0x997B14E0C76CEE2AULL, 0x4CD3F121B2A78064ULL, 0x086122AD12F4DB17ULL, 
            0x2693083E5FF9ABF2ULL, 0x15887AFBD8E83CDEULL, 0xC9801E9B4E7AB21EULL, 0x247D78EAC550B535ULL, 
            0x8494EA3A7279621AULL, 0xE47B9C287A33B85FULL, 0x8911FE47033756F3ULL, 0xA930E3185FC768A8ULL
        }
    },
    {
        {
            0xA610D9507301B375ULL, 0xD67BAFF0771F2933ULL, 0xA06B42CD4199BCC8ULL, 0xA698C78A54EE994AULL, 
            0x4D5F0E478DB08367ULL, 0x4565EF7EF5C71DB8ULL, 0x4546F1744F18418BULL, 0x50FBFAC577BC1BCDULL, 
            0x75A335F18CB527F0ULL, 0x909AE389E9883CCEULL, 0x442C87B25FFC40D3ULL, 0xCCDBE6148AD6B7F4ULL, 
            0x17D29D27C02563D9ULL, 0x52816B291D218B3DULL, 0x71AA1CED7B39C8E0ULL, 0x9E01E11FA612A40FULL, 
            0x11285CA4E62D1DF2ULL, 0x1FC50B9CFA3FB33FULL, 0x619FF5643D27EE84ULL, 0x6DD6BE1F3E878CA8ULL, 
            0x9539450F6F518E5BULL, 0x5C0FA7D1B038E8CDULL, 0xBD148A6D9CE4306DULL, 0xBF69A6D21FA3182BULL, 
            0x7B43F9019CEA9C4CULL, 0xB5BEDF1E1CDA921AULL, 0x44D93628F1E4327FULL, 0xE81F458437E8AAFDULL, 
            0x83540A5486DA0601ULL, 0xE4C25AF33427E12FULL, 0x81D783063B14CFD8ULL, 0x52EAB65E3A62F3FBULL
        },
        {
            0xA0B826E3F6678BD0ULL, 0x60E9C2D170320BE2ULL, 0x7CF2D789D31A68EBULL, 0xA9B9806814AD4340ULL, 
            0xD78C19E98B0E7C13ULL, 0x061ABEA380D4512BULL, 0x2A1F120B80DACE10ULL, 0xEE8D3F8D16D4CEEBULL, 
            0x52F3221D5B498E11ULL, 0xACA30374CEA59FE3ULL, 0x71F5A08D07E68373ULL, 0x1D50702CEFBB40EFULL, 
            0xEEE24B3190FB0046ULL, 0xC6BCC8F22C8DD857ULL, 0xBA749E90A5D7F97CULL, 0x2CFE5EBE0552B35EULL, 
            0x38FC73165FC149EEULL, 0x5351C9436420A271ULL, 0x94926A9032913BB1ULL, 0x448A19070161CC21ULL, 
            0xF4E52530E9D656D1ULL, 0xBD99229A824B5904ULL, 0x79935067C19D1715ULL, 0xDDF2AB9DE2C510F6ULL, 
            0xF9D1C458E03FC15EULL, 0xA71AF24582426229ULL, 0x4C8AFFDC406CA623ULL, 0x431C861633F68BABULL, 
            0xD13B1E4B6E09B595ULL, 0x0EE9A0E7D921324CULL, 0x0BC209B99DC5F172ULL, 0x6046FC6B84A0420EULL
        },
        {
            0x7330DCF612C249B6ULL, 0x8D4C405E08E32B1AULL, 0x47F8E956731EC718ULL, 0x8E23895C3464C0A4ULL, 
            0x14E5550E1BB3D341ULL, 0x4EE187E051D39A58ULL, 0xD39029C98F5F9C0EULL, 0x24AF5404889C40BFULL, 
            0x72A93C34AFE5745CULL, 0x71BE17600750A6D6ULL, 0xBDA7CA8D10734B4DULL, 0x045B3230155A8348ULL, 
            0x5158D230786B6C75ULL, 0x5D69F668B311D074ULL, 0xA7D929801026660DULL, 0xCAAA751BE8825C23ULL, 
            0xDFB580C189194196ULL, 0xDB36816D0C4C6888ULL, 0xF18FBD29CD8FBC56ULL, 0xFCA0120D211887A3ULL, 
            0x366153A0A4E59BABULL, 0xEF0B61E5E2CEE391ULL, 0x6F93E112BAE21F50ULL, 0xA3CAEB5A36ABBA6FULL, 
            0x9B93373B138C12F1ULL, 0x3DD5166459DF593CULL, 0x5C6A6897D1FC0A10ULL, 0xC842A798EE7C611FULL, 
            0x56A1DC2947538417ULL, 0x936A3C85E6627725ULL, 0x0B99673F0463A703ULL, 0xB9D26CBC9B48B70BULL
        },
        {
            0x5C646B0201250D66ULL, 0x39B3C05AD986FD5AULL, 0xBE64DA7C39EEE390ULL, 0x6EFE295129F2DCA7ULL, 
            0x457E5DF8B85E7F23ULL, 0x3C19ED319CD710A9ULL, 0x36D0D84910499096ULL, 0x31FC1138DCA392FEULL, 
            0x81302BF5C195D021ULL, 0xB879B440E9ED1CFAULL, 0x2E7254A8BCE221DDULL, 0x540D46F08B248099ULL, 
            0x87883BFFA9EF461FULL, 0xD953662E2744EE23ULL, 0xB8A7ADE50C179E35ULL, 0xDB2C873A8741A3B0ULL, 
            0xCE59DAB6A254E9D1ULL, 0x4A7E7654DD6281D7ULL, 0xC400296AE4225970ULL, 0x9719CD8AD2747B5EULL, 
            0x13FD51B50DC382E4ULL, 0x50EB77D8F7DFC08FULL, 0x7936FD981605DC6EULL, 0x0D4B81B16A5D7E1BULL, 
            0x0804EC6B730FF531ULL, 0x360F80EE8397247AULL, 0x0020F80AF20A6C13ULL, 0x9C73A5D07E65A8B3ULL, 
            0x9A3506B66A0B2878ULL, 0xA5FCAC0E3EF3A463ULL, 0x697A6F148B27A3E8ULL, 0x2811DB3FEF4E7785ULL
        },
        {
            0x4D7C3C93D577FD8BULL, 0x0D6B346AB1A8886BULL, 0x06885BF349D345C8ULL, 0x2BFA405CE2B1DFE4ULL, 
            0xB25F667CA972D11AULL, 0x0A19E9A7520E938BULL, 0xE5C0DDC5EA0DF653ULL, 0xF615D2095CC2747AULL, 
            0xC80FB093FAAF6295ULL, 0x8419F4A9BFD8B481ULL, 0x999BE4AC0D149E90ULL, 0xE5B322E2539E4C99ULL, 
            0x0AD10B9369EA96C0ULL, 0xEE39B6691765B9F2ULL, 0xDD1699092F7EB0E9ULL, 0xE3D371BDA75E8445ULL, 
            0x066A752CE3E47E17ULL, 0x59256DF7C3E35C77ULL, 0xA69C1F15A431B610ULL, 0x44B119F7E9432CF7ULL, 
            0x13CC5B734331E334ULL, 0x050862C3024F34C7ULL, 0xFC18BC06BE058430ULL, 0xA26B06F37670FBC2ULL, 
            0x3420A3CB13501118ULL, 0xC75316004E7323CBULL, 0x4EF688AF120EF20AULL, 0x7F33D980BDEF94DEULL, 
            0x5FD6C321A8399784ULL, 0x0DE9E4A386E8525DULL, 0xF88FBB7028539A48ULL, 0x63A3F6CA0004FDEBULL
        },
        {
            0x66F1EEABE98827DEULL, 0x90424FD6BE5D607EULL, 0x1EB305D7A6B18851ULL, 0x2BFDF5921C9A08A7ULL, 
            0x096FE444FE63F91FULL, 0x34BCC2A42A3C633AULL, 0xA7F8BD17D2279057ULL, 0x803443CFE2712CA4ULL, 
            0xC30D235D2A928DCAULL, 0x71485DE56C07AE22ULL, 0xDE2A63DF17203B96ULL, 0xF732301DD3E459A2ULL, 
            0xB28CDA4754291576ULL, 0x36A4EF5721E6F600ULL, 0x9A9282E9A2B9420FULL, 0x757D8ABF0A370E39ULL, 
            0x60A133816BFF0196ULL, 0x4CE7E92AEC92684EULL, 0xC9D3C849FC90F0CFULL, 0x657CB4166AE7D7ECULL, 
            0x40110443041BF556ULL, 0x7592A6452114F8B3ULL, 0x458146A32743C57FULL, 0x4549C18BD15DB241ULL, 
            0xA19D96FDAD7E16AEULL, 0x70D18961167B7144ULL, 0x141B79AABBB6FF55ULL, 0x8817C3A931CAFD7EULL, 
            0xF039361E36D00469ULL, 0x6376CBFC9B6D438BULL, 0xA4062790010B3916ULL, 0xF07529CB9CB3FB88ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseAConstants = {
    0x986C9FA787B979FBULL,
    0xB1A1AC1DAE583D02ULL,
    0x453DB30A060EBF7EULL,
    0x986C9FA787B979FBULL,
    0xB1A1AC1DAE583D02ULL,
    0x453DB30A060EBF7EULL,
    0xDF143DB84A586DAFULL,
    0x6DAC898FEBFD5333ULL,
    0xF8,
    0xAB,
    0x7A,
    0x51,
    0x53,
    0xBA,
    0x80,
    0xDA
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseBSalts = {
    {
        {
            0xEB4E0BF48FA19EE0ULL, 0x7988CF765A4E35F4ULL, 0x2CEB19B090BB27EFULL, 0xEDACD29B2E6CF82EULL, 
            0xC73D7EB5258213DEULL, 0xB8D5667A1127FC6DULL, 0x75EF815CB7788D99ULL, 0x9574E0BA80F692FCULL, 
            0x650A207C7CA44C1FULL, 0xF83CC7B02DFD6846ULL, 0x3F88D63E8F47BBB7ULL, 0x7411F673F4AF4A49ULL, 
            0xDAEB890B61E34E07ULL, 0xDFD89A2E78126420ULL, 0xF43C8A5F560107C3ULL, 0x949E00A185BD755AULL, 
            0x078D1746740D9E3AULL, 0xBF39B3D4D52D454DULL, 0x901F844CCCF157F9ULL, 0xBF8C2E0BDAB51D7DULL, 
            0x69DFF1E3592379B1ULL, 0xE53670446DFFD4C3ULL, 0x4B461711FA460CB1ULL, 0xD068ECFB74A2A484ULL, 
            0x296D45851E691490ULL, 0x17345BA97838612FULL, 0x61F94D3C04EAEE06ULL, 0x726CC7EA1AFDB9A6ULL, 
            0x0457F2C38470CEFDULL, 0xB33B11200917ABE2ULL, 0x3CAC9325FA4B3789ULL, 0x37B0D3BA594AE237ULL
        },
        {
            0x696802C2B81ECBF9ULL, 0xB3F17968BB9966CDULL, 0x258FE51AEFC12EA3ULL, 0x95BC4C33E27EAC46ULL, 
            0x14DA2091BD2125E5ULL, 0xEC527FF59A51E6EFULL, 0x02584256D08876F1ULL, 0xA32766233B1EC1B2ULL, 
            0x29C2D84C09E19669ULL, 0x85320C6B763C0E9EULL, 0x931E45D86DB1B581ULL, 0x928B159F32B60DC3ULL, 
            0x1D1B5F375C0895D5ULL, 0x440EC32F55E625BEULL, 0x68122DF375D61C5DULL, 0x44EF728AEF1AC8B4ULL, 
            0xF7ACA54A4357E0A5ULL, 0x0BEB41A71813F7DDULL, 0x704AA7AE421DC165ULL, 0xCC997C864ED6BB35ULL, 
            0x2989CD350C415D84ULL, 0x9307353A2F777F23ULL, 0x99824D47AEE6EC1FULL, 0x57BF5F6171B16038ULL, 
            0x6F3E1F07633C062DULL, 0x5E5CE616B5E88B44ULL, 0x07824E6E2ACCA167ULL, 0x1D3734CB4BF311F8ULL, 
            0xDB4A2ED6914B2353ULL, 0x753560E30A3B5FC7ULL, 0xC9A0CAB0FA552ADBULL, 0x032EB59938D308EDULL
        },
        {
            0x2D5A397BA52EF9CAULL, 0x892449D8D03265E6ULL, 0x1A9C558C9E81A189ULL, 0x38AF241BE0C88359ULL, 
            0x492B8864A916BDF9ULL, 0x4EC6D1E127CD305DULL, 0x30E6AC67A3CA176BULL, 0xA4D9375E03A0F3D0ULL, 
            0x9BE3D787733A3FD4ULL, 0x4D78587AB6CD140CULL, 0x551E183050DEDCFBULL, 0x0310D35C46684A90ULL, 
            0x976DF139B6A2A4C3ULL, 0x4E3852D9F1764D6BULL, 0x3C06386441B0DC77ULL, 0x6D7A7B445DBA3D1DULL, 
            0x071BCD26875E4A54ULL, 0xEBF5E31D034F0450ULL, 0x7FCB8936BD353B14ULL, 0x604E42D22F69A697ULL, 
            0x0D64B58A910B15B2ULL, 0xD3D9753A6F18A5FDULL, 0x88DEFD77B5DBA2A8ULL, 0xE52625BFB0598F1DULL, 
            0xE5AEFDAFE483B54FULL, 0xD253BAE2D24F0A40ULL, 0x57DC3F1A0A5F3A9EULL, 0xA6A6252D0A21601DULL, 
            0x8AB7EF3F92579767ULL, 0xFDED77F310579AAEULL, 0xDF21FB13ABA73EA3ULL, 0x373E273323002350ULL
        },
        {
            0x1009AFDBA5155959ULL, 0x2462D756D64B3ACEULL, 0xF083E799500BF280ULL, 0xBD7208524D406A05ULL, 
            0x4D2CDFBFEDFFA8AAULL, 0xAC9A3CFD9CEC9EA2ULL, 0xDF3C267FC24E55CDULL, 0xA787BA65C8DEAB44ULL, 
            0x62654B03E21F1F9BULL, 0xDB9970B33F11D6D4ULL, 0x645EC6E341E933FDULL, 0x5825B0321A169CD7ULL, 
            0xE53F69A3ECA7DE86ULL, 0xA3EF04BA202F936FULL, 0xD80AD47B9522FE69ULL, 0xDA007EC31615480CULL, 
            0xFB473B16589D85F4ULL, 0x8264969FD3F25B35ULL, 0x98392ADE8CE58CADULL, 0xF087FA49B1DF0E58ULL, 
            0xD4F2A2C68FAAA9ADULL, 0x865C64D3FDB4D316ULL, 0xAADDC9E2F9B0D89FULL, 0x3BC3F79A6BBB180FULL, 
            0xB8A073A79B431D1EULL, 0x89E2EE10C44ACAD5ULL, 0xBBBA840647946ABAULL, 0x3C43155F9B82B419ULL, 
            0xE709F9BB2627931EULL, 0x72181067921DC0CDULL, 0x693B27015AB3AD91ULL, 0x18BE264BD7FB50B6ULL
        },
        {
            0xA575E8A0737324F9ULL, 0x271FA376AD9B1E9DULL, 0xFB57F4EACA6D535AULL, 0x8A29F034807ED5FAULL, 
            0x99A2289244DC056FULL, 0x566AA5316DEA5C14ULL, 0x3F9A14245CF6C9FFULL, 0x59DA796974E3A681ULL, 
            0xFBF9BDAF31DB69EDULL, 0xCC4F3EACA4DFE67FULL, 0x71E018276C6871A0ULL, 0x26264C6C9C575532ULL, 
            0x09A8F83524148DD1ULL, 0x61F0832252B0A63DULL, 0x715AA54A83685EDCULL, 0x5698D63E1CE41255ULL, 
            0x2194C2BD6048AAC9ULL, 0x0B5E4FB07A683F51ULL, 0x24B2BB178C8AA78CULL, 0xAD931FB7E82A2410ULL, 
            0x5522D6A2BD67CDB6ULL, 0x1A713E7777BD166BULL, 0x1D1F6018014AA66BULL, 0x8FFDFC7371374178ULL, 
            0x3472DDD76ED1E1ECULL, 0x54DD30BFA94B5E4FULL, 0xE4583818A0983842ULL, 0x67C1324487E66DA3ULL, 
            0x4C8A7650CCCE8F7EULL, 0x3A4E2301D683E3A3ULL, 0x69621C6013D8DF87ULL, 0x9B0425F056E2CEF4ULL
        },
        {
            0xF25F9508073DFA21ULL, 0xFD2BA6C29EDED430ULL, 0x66819D16831125CEULL, 0x07FE87FFE57613BFULL, 
            0xD71FF70CDED3E2FFULL, 0x00257D1ECAEBA022ULL, 0xB9CAF714905F17EDULL, 0x58EBE95EE226EA09ULL, 
            0x3EC0A5F5BEB76649ULL, 0x9E8B8109B57E8812ULL, 0x4FFD9A5A9C779202ULL, 0x60488323DE56223AULL, 
            0x3CE0471C391A5DBBULL, 0xA8207BDAC2DEE993ULL, 0xD39A16D9920E08B8ULL, 0xCA190651FACE3CCCULL, 
            0x61C1F0A7EDA5C264ULL, 0x0F26C08B5B231CC1ULL, 0x202995159825558BULL, 0xCE04C8B56C802B16ULL, 
            0xEDE35DE047B765F0ULL, 0x5A00796B3A0EB35CULL, 0xFFA59A1B103D5222ULL, 0xFCB245E81348D208ULL, 
            0x09701EE6F3FB81D9ULL, 0x0F0F5C6C6D61DC04ULL, 0xC5F4A6219EC40484ULL, 0x0B7B12F7314AE879ULL, 
            0xB8030FF784216DD4ULL, 0x267782B9EC242CE3ULL, 0x85EC41B2B674C780ULL, 0x034F2CA981054FDCULL
        }
    },
    {
        {
            0x001529AB7876127BULL, 0x8F51B07C5E843DFAULL, 0x21544FA72D42F227ULL, 0x35E1A6814EF78505ULL, 
            0x41B753F602519376ULL, 0x31A1E8236A4DEEDDULL, 0xA75890133966D078ULL, 0xB7623893F64DFD4EULL, 
            0xB5455CB8DA40D555ULL, 0x918B3825E7334BF7ULL, 0x03B9EDDE1FA49523ULL, 0x6CB696812B9F0E86ULL, 
            0xABE01E02373FA708ULL, 0x100A23DB0C34382FULL, 0x4B304B51CC0A3296ULL, 0x820ABF1A7D0C8759ULL, 
            0xEDE916FDD52478C5ULL, 0x077C4B80AB45B002ULL, 0x131786CA77E08BDFULL, 0xBF986769607DE609ULL, 
            0x020E64AF18F08024ULL, 0x3AC74CE1E15D70DAULL, 0xA7C3B449FC323447ULL, 0x019330E1EBAE9A59ULL, 
            0xF38D3C9387200753ULL, 0xDC426FA861710CE1ULL, 0xEDAC85A9366D5CE9ULL, 0x7891235FF3CE25E3ULL, 
            0x29E32DE2D2D69D35ULL, 0x01C3A1BDEE9085A6ULL, 0x0F6A9ABAF8FCCE63ULL, 0xF642F416D333238EULL
        },
        {
            0x1BDBF0EA915CE023ULL, 0x0DD819811817CD9EULL, 0xC0C0CA4408201E64ULL, 0xCF66601EDDAD9B86ULL, 
            0x821C3567A748E931ULL, 0x01D518A362A0D46BULL, 0x3490F20F1A11E752ULL, 0xA068BE59B5D56FE2ULL, 
            0x3BA8ECCD14EB5646ULL, 0x441C200307BC58D6ULL, 0x6E465E49AD9564B6ULL, 0x752761AA18C65B80ULL, 
            0xEDF5DE09D191F0C8ULL, 0x7E822C96AD722C25ULL, 0xD4E4E54DCB420F99ULL, 0x5FBFD2147081B66BULL, 
            0x363169704071104FULL, 0x95D6402C4B9FAC3FULL, 0xF74CC3DCD59F36FFULL, 0x1C8DD3D2C6388815ULL, 
            0x87CA9B0C94FF04FEULL, 0x86ECE048D2843F3FULL, 0x8BA663FDC00E5183ULL, 0x669E95606F4F07A5ULL, 
            0xDB855F28DE975EB3ULL, 0x64AA309B16396BF2ULL, 0x48A51AD31BF36140ULL, 0x7D452C3EC1AE68CAULL, 
            0x6499D8DCC7187B98ULL, 0xBB17E7944049DE0AULL, 0xE012B7E5BEB55151ULL, 0x33C05102CA192AECULL
        },
        {
            0x154703AC3FC6DB76ULL, 0x1B75800DE432D205ULL, 0x54724A4A4B755DA2ULL, 0x4A1AAD27EABAD7A7ULL, 
            0x57B27FF98CDDB7F6ULL, 0x147F13844B347F67ULL, 0x04CAB80FDD1FA35FULL, 0x3CF4821268F5DF80ULL, 
            0x1097ED466219168FULL, 0x59167BC0DA9687E7ULL, 0x80006C26C7B8AF9FULL, 0xD6EFA2DB7B10A503ULL, 
            0x330D763F3E617F39ULL, 0x06D911345788C3BFULL, 0xF1819EF912B3C947ULL, 0x9EF96DAC6EED3D75ULL, 
            0xFC5A242E4EE02247ULL, 0x45E945BCE9CB4812ULL, 0xB691057BC68B676CULL, 0xD97F83D09D3F1CEDULL, 
            0xAB9959AD7D4B2B85ULL, 0x6EDDD0E570C020E1ULL, 0x9B377119A87518D0ULL, 0xCEBC5EE56C4DB6A1ULL, 
            0x056E0850415B75BFULL, 0x5990ACDF03D72579ULL, 0x33AB44049062C194ULL, 0x08E27AF2E60EF1BCULL, 
            0xE37325504C642FC3ULL, 0x6CAABA8EC97A2004ULL, 0x8C85078837C8FF67ULL, 0xB273AD9DCE3637B2ULL
        },
        {
            0xF4BB41F55A069F6CULL, 0xF6A789DADFD1D191ULL, 0x47F86EAD20CC91FEULL, 0x035165196154F233ULL, 
            0xC8C3581D064B7DC2ULL, 0x95EB3C7E0A9B7271ULL, 0x6AFE77E8780664C6ULL, 0x885DDD8E63AAF241ULL, 
            0x029D1CC38518AC06ULL, 0x6EBEED4F135DCEDFULL, 0x30088DD30831F932ULL, 0x200B2C6A8CB4E806ULL, 
            0xC64E7DB668DE4BAEULL, 0x61116FD91CB499F6ULL, 0xFAB9451CB3224CF1ULL, 0x11357A98C5C8E4F6ULL, 
            0x81FF06F790E5D5E8ULL, 0x639885BCC100F81FULL, 0xDB1DE78192BE8090ULL, 0x8A12E8B85367CD64ULL, 
            0x6658A1814E27F4F3ULL, 0xC0CA4E7C54188407ULL, 0x8D298FB48D92F418ULL, 0xB791D7EF903934B6ULL, 
            0x3F6410B99231D2ABULL, 0xF66631A33583C722ULL, 0xD95B9C07A25A438BULL, 0x2F0D1FA70E548681ULL, 
            0x6020EA3AB11E72A5ULL, 0x7E9F63203C265414ULL, 0x8D3AE0721B0025A4ULL, 0x4B4FC887B4BBF658ULL
        },
        {
            0x62B37D6CDA43645FULL, 0xD638FD96E6F439AAULL, 0x204DC31DEB49E2C4ULL, 0xEFD9CF28D86F0C24ULL, 
            0xF258DEDB6E3D5AE2ULL, 0xA18C7FA9E53E9724ULL, 0x17FB9B0C9B2DF6F9ULL, 0x5A2A7BB3B1CBA7B0ULL, 
            0x89AFE74A7931CA76ULL, 0xE47618BEB4CF4C70ULL, 0x675B9D93EC83C558ULL, 0x3A4212710133321AULL, 
            0x10F39FB1B5F48167ULL, 0x6DA37EF0CF0F06EDULL, 0x5D0C263A9F2CAE9DULL, 0x2BC8B71AD0B97565ULL, 
            0x65934CE36EAC939EULL, 0x326C47303200B900ULL, 0x28DC8594F8688CF8ULL, 0x60B68B8B9D2EBD78ULL, 
            0xE8AF66951BC465A5ULL, 0x7BC381366FFA3893ULL, 0xD77624AC6835DA54ULL, 0x37A186E0BF189AA2ULL, 
            0x09CA98BF1E32BACEULL, 0xD69B6B195CCBCC48ULL, 0xAF1C7877C4C64D26ULL, 0x3B4BEBFD5EC008C6ULL, 
            0xA54861DAB528429DULL, 0x6799DE1767A4B4E7ULL, 0xF7B14317E137B1C3ULL, 0x66B6C79DD54DA87FULL
        },
        {
            0xB2BDA58ED4B39B38ULL, 0xF29633285DD25307ULL, 0x28DC2F170FDD1CA5ULL, 0x7316FC069EB5152CULL, 
            0xA6657AE910333777ULL, 0xBB158E1AB3D0206BULL, 0xA7BE9C7EC7A1A6CCULL, 0xE0585D13E8703956ULL, 
            0x1657271B27FE215AULL, 0xB8EF175890F9D005ULL, 0x27CA6EF80D66ADBAULL, 0x23FD4AC065DDE878ULL, 
            0x958E11D8B0E86216ULL, 0xC2B7CC1B54E5D22FULL, 0xDF2F01D3D842D1F7ULL, 0x2E63D1C03D3B4232ULL, 
            0x6F039751AF3AA8D5ULL, 0x5840C2BA63D855B3ULL, 0x69B5CF58CC11E2DFULL, 0x28324E739F869613ULL, 
            0xCC15B7FD822B43A9ULL, 0xB8DFC9C74EF99885ULL, 0x974BD2D6220A69D4ULL, 0x507914F2F0B45B69ULL, 
            0xF7F4944C9E400816ULL, 0x7F3E8E30F07F2371ULL, 0xB685BF6B328EDE32ULL, 0xCC667E4651286874ULL, 
            0x7B262F53532D1CF1ULL, 0xDFF6BB57405617ADULL, 0x3DB3EF7944D8330FULL, 0x6014B792C1F5D74AULL
        }
    },
    {
        {
            0x1C12030C450AFA78ULL, 0xC1D3E46CC95CB578ULL, 0x1328BE4F0F84FCEBULL, 0xE3AED7DB30F127B3ULL, 
            0x1DA2F552E1E7F09BULL, 0xFE8EE4E6181ABDDFULL, 0xA55CBACE99B34393ULL, 0x491103BCAE040488ULL, 
            0x26DA3C28AAE43374ULL, 0x18B36F820B699F67ULL, 0xAE0FE9ED96E1705EULL, 0xF4A4D54AE81D27E8ULL, 
            0xF001B647280E3DB8ULL, 0xAE6C12182ED72360ULL, 0x814B672EEBAF9274ULL, 0x72D615E6F765C6BBULL, 
            0x28CD8CA82F21558EULL, 0x385F4A7F6F6F619BULL, 0xC71C6BCFF47EFC6AULL, 0x2580F5907A2B69BCULL, 
            0xD83D97B1CF6E357EULL, 0x952EA5794A1BF6CEULL, 0x13FD471D1BF92CF9ULL, 0x3FECA3E9364B6132ULL, 
            0x6CFBDCA027574214ULL, 0x89D6431F6D4A9E2CULL, 0x8846D88D65C5AB48ULL, 0x78376BEB3197C8ACULL, 
            0x318921D1E29477F1ULL, 0x79CA266A7E24A3EAULL, 0x2FC2C25C22F6F895ULL, 0xCD191E8773186CB2ULL
        },
        {
            0x429375CCBDB1F825ULL, 0x2DB41FDF2AF43B04ULL, 0x72418CA3A7AB3E4DULL, 0xBCB750CFF0FBC718ULL, 
            0xB5580CE3693156E2ULL, 0x33E498DB9971F532ULL, 0xF1D69AE0D78A3DDFULL, 0xFBE30F40DA03119CULL, 
            0xD08A311436098F2AULL, 0xD989268E5143B66AULL, 0xD01BEAEE5FC069CEULL, 0x46E635B4B198B1CEULL, 
            0x7AAF2DAEDAB59932ULL, 0x18D498019D7D8E78ULL, 0x076DD2AD08D6DC8BULL, 0xE75FE6710B9AEF0FULL, 
            0x4A0BEFDFF66432B1ULL, 0xDEC60B66710E78E0ULL, 0xF776DEFDA2DB17A0ULL, 0x24BAA204F2A0AE13ULL, 
            0x5A278BE196B42BA5ULL, 0x086824320E584027ULL, 0x542D9C3C8FEA74DAULL, 0x16953F4D43DE1A85ULL, 
            0xD9230E8DEC30A009ULL, 0xC8F93545D43A6F5DULL, 0xE99ABA46A26B0500ULL, 0x7CCA3A07EB75A9EBULL, 
            0x9B7767CD6E7C9DA6ULL, 0xEFEAAD31EFB38E6AULL, 0x4061BFA4881FA24CULL, 0x0AC69179D3AA58F8ULL
        },
        {
            0x0DF3574D1440FF68ULL, 0x0C574EB304FDFD8EULL, 0x114A6034F19C685FULL, 0x76D8A4B4E6BD2CABULL, 
            0x096489C9AA36E80FULL, 0x043E910FEE73D284ULL, 0x101BFF8A722B9FD2ULL, 0xF2467C46D6640FECULL, 
            0x2F2D8A2CF23A2494ULL, 0x42B870DDD2D21E44ULL, 0xCB39F8A794387BFCULL, 0xB7B6CD1F90ED795AULL, 
            0xD7235E8669F4DB47ULL, 0x67B7802D73695C16ULL, 0x9579ABE12B532B54ULL, 0x480989E2D8DECBBAULL, 
            0xBD92589C296E9AA5ULL, 0x280E2708896DD84DULL, 0x3C09019FD075D100ULL, 0x14FB7722B2DB44DDULL, 
            0x7D984F84C90FC0CDULL, 0x7EED4B3B211B6E11ULL, 0x12C53675E29BDB5CULL, 0xA6DB13F9B03ADF51ULL, 
            0x0FF884AA9C2B81D4ULL, 0x4AA9AD9FF6BE8386ULL, 0xDD65360C82ABCE24ULL, 0xA0F188528B48902FULL, 
            0x2EE1A7B87ABDF8A0ULL, 0xC910919B6BC24E20ULL, 0x0E53E96113B34D3BULL, 0x2ADA91803D202600ULL
        },
        {
            0x51AE1071AD4244C6ULL, 0xE56EAF9CD24592A4ULL, 0x03DC584C6C1D4378ULL, 0xD31D917F0668307CULL, 
            0x894FCE79FFE286BBULL, 0x7452B8D574A1EE94ULL, 0x4D4DE3552A6E74E6ULL, 0x707EA6AF8BB63C3FULL, 
            0x49B619CB2B94E806ULL, 0x3CDF5D35887CF71CULL, 0x6214907C1B276DF6ULL, 0xF9C518C6B07A2CD0ULL, 
            0x2C4CCE975D9BA8CFULL, 0x22290AC345370FF6ULL, 0x619F500C2E0992D0ULL, 0xCA5E71FDF7784D0DULL, 
            0xCBA7AF2F20F536EBULL, 0xFEAA1654B2D89805ULL, 0x1824CAE319EF386CULL, 0x54B589450A25429CULL, 
            0xCE9D33D12B544D2AULL, 0x8B0057FB4EB82D22ULL, 0xD850FC4D0B97B520ULL, 0x22F9F9E32527DE4CULL, 
            0xA3C089731BE78BB0ULL, 0x21AE06D9F8600E56ULL, 0x047A99696F0E8598ULL, 0x4A4B3AE940D31DC3ULL, 
            0x26BC329E44D1CBB9ULL, 0xDD80754183728D73ULL, 0xB429151132B21DA9ULL, 0x7E93793FDA73F191ULL
        },
        {
            0x51F121CC921F88C7ULL, 0x18A80A1179B9BE08ULL, 0x14F7A31E83CDA0ADULL, 0xFD392263A532631AULL, 
            0x85B85BE04CFCC7E7ULL, 0x10345331A1DC55E9ULL, 0xFC5E916A76C4EBF8ULL, 0x7D32BF3E070D3F67ULL, 
            0x874221D5D298BD36ULL, 0x9BFB9F9ABAB54036ULL, 0x73E0CAB8DEE8FA15ULL, 0xB331847E0675CFD7ULL, 
            0x80EC4DC177A7455FULL, 0x94348A6B0777A112ULL, 0x89C30FF10C547A3DULL, 0x1A1BA8D50526D586ULL, 
            0xB8546F8BB2CC1AA0ULL, 0xB3F2801E441226EFULL, 0x3F3147066419BCDCULL, 0xF6DFBEEB4603ACD2ULL, 
            0xA62AF1A73E820707ULL, 0x2D0E6272B9DF5151ULL, 0xA43B6D471BAE3ABAULL, 0x05AC1B7B72A7D835ULL, 
            0xFA01C3D9AC333BF4ULL, 0xD843646CDA0A3519ULL, 0xCD6B9226A1FCBA55ULL, 0xD3602323217C4DC6ULL, 
            0x0564EE59B6DDEE0FULL, 0x35F9E90C45E624DBULL, 0x4CDBED63E68FA840ULL, 0x418ECF846E8809DEULL
        },
        {
            0x5E7120E40F67E68DULL, 0x288C02D2E39BDDFCULL, 0xFA290D1F1108D7E0ULL, 0x12D50FE6FAF0A25FULL, 
            0xC2C07179E417B09FULL, 0xB34D2466A39E86D7ULL, 0xC30CB10C16C204A7ULL, 0x9C53267C5D3DADEAULL, 
            0x1711D4EA4BDEC9D3ULL, 0xBE8B3703D7B005EEULL, 0x255EBAC6E2ADC724ULL, 0xBAD388381224A85DULL, 
            0xB0CB3F3F43B29195ULL, 0x6FCA140744A48946ULL, 0x8F12BB3A41A66DECULL, 0xD02294B8ADF38AFFULL, 
            0x55B527BAF9CCD91FULL, 0x9EB284F414A59553ULL, 0x8B732A2611FE1445ULL, 0xEE84E71CE1F5BAA2ULL, 
            0x384ED89F8D9F9638ULL, 0xD09BA4544902AABDULL, 0x002F138CC54DD97EULL, 0x5950C87FBA942A24ULL, 
            0x1207221AEE29C878ULL, 0xBD84FD7437E49F1DULL, 0x1A92372797FCE194ULL, 0x371F061DADFC5E4BULL, 
            0xC8A8ED524B109B27ULL, 0x5ED0AB144F082B33ULL, 0xB761CF2BC764821AULL, 0xB1935E3F1E97BB78ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseBConstants = {
    0x9CC798D0E79382A1ULL,
    0x08201C16FB0557C1ULL,
    0xA454CF9908D2A452ULL,
    0x9CC798D0E79382A1ULL,
    0x08201C16FB0557C1ULL,
    0xA454CF9908D2A452ULL,
    0x670A8F47C68380ACULL,
    0xDCDAAE77E136AAEDULL,
    0x09,
    0x57,
    0x3C,
    0xB3,
    0xD1,
    0x2B,
    0xF3,
    0x82
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseCSalts = {
    {
        {
            0xA52A87E4CF279929ULL, 0x39B9D1EA4C7E4072ULL, 0x34168CA3B7CADC18ULL, 0x8D8ECCADCB554CB4ULL, 
            0x91AEA26600D93810ULL, 0xD8EE9EF2FEEB51D8ULL, 0xD22A6E73518C5D27ULL, 0xEA256A37E2308487ULL, 
            0x9B984EC06B3EDB49ULL, 0x87B5A488C5055A5EULL, 0x1FAA02903A62B73AULL, 0x7DEB2271F62D1AD0ULL, 
            0x0C7F2406840A5417ULL, 0x532E7FD196A9EE84ULL, 0xB9ED9A98D1BDEC47ULL, 0x50342AA6E5FC0ED6ULL, 
            0x88D89EAA1901F06DULL, 0x4DA9AA95E09E930BULL, 0x3F1D5D44993DC5C5ULL, 0x6FAF00858D494316ULL, 
            0x720FB43E7BABC1D6ULL, 0x3A57FE6D95ED9484ULL, 0x2E0961438A9DCC1CULL, 0x03C3E769517B7AD8ULL, 
            0xEBE51E3D20E22A13ULL, 0xFE0DB12AF754CB47ULL, 0xBC6796203BEEF68FULL, 0xD7B48E6D3C956371ULL, 
            0x0254AF6F102CDE4DULL, 0xB7F1FA515AE3CB44ULL, 0x812D1791499E801FULL, 0x14AA853952A2F989ULL
        },
        {
            0xA07D99C1C51F2199ULL, 0x24AB01A5265895E1ULL, 0xB4904239EC186B64ULL, 0x9ACA909D7EDDA9EDULL, 
            0x3ACB96F951A8C60AULL, 0x8BEF955B0AB7B737ULL, 0x3B51F1870537EF69ULL, 0x25C0F497CF846C90ULL, 
            0xB559323ABA658D7FULL, 0x444C8107B3F655CBULL, 0xF1FC6C58A705C5DFULL, 0x7181F362974E4836ULL, 
            0x00F70ACD79753AFEULL, 0x2DAF9D48C8B47A1CULL, 0x1D50CC70A62F36EAULL, 0x56C9EAF2D61C3C27ULL, 
            0xDC0F391EE6B6D943ULL, 0x0013707DD0BF613DULL, 0x61A0EC4ECCCF3B5AULL, 0x6D942F37FA787C82ULL, 
            0x052DAA546291DF86ULL, 0x66C93D5E65CDB081ULL, 0x618911E9CC4F967AULL, 0x1DE2195354F9842AULL, 
            0xA0C08A73632400DBULL, 0x2E9767FB15F1180CULL, 0xCD3EA57681A43C8DULL, 0xB54382F46CEF337AULL, 
            0xD89C591613D102E3ULL, 0xB6D57A9943162C48ULL, 0xA80E476229F40EB5ULL, 0xDB6CF377BAE65AADULL
        },
        {
            0xB8D146D8E2D43D71ULL, 0xCE3E5EC6B9FCBB27ULL, 0xACB655430FCA8278ULL, 0x840D202CA6E82638ULL, 
            0xA558A8101373B4D8ULL, 0x975A36AE8DE58828ULL, 0x83F6CB8785A172CEULL, 0x9C1C61F14422936AULL, 
            0xC3B44CC1615B9751ULL, 0x331DF0105ED7010DULL, 0x9AF68F9432B74E0DULL, 0x5904DB1C29A73E29ULL, 
            0x59E69797B6CF1FB0ULL, 0x3A61367313EDB6E1ULL, 0x73A24F833DA53A1EULL, 0x10E1056C721B15ABULL, 
            0x794F84778BE32BE7ULL, 0x4B98BC1E32D6830AULL, 0x4BC7FCF3951E7A03ULL, 0x4B78FF0B3691F966ULL, 
            0x4138ADBF2EB09BF0ULL, 0x39897338DE92DAC2ULL, 0x970D43790FCCD844ULL, 0x0996F0CDC9A2A274ULL, 
            0xC382E63671A89896ULL, 0x47B1E66DEAA31B44ULL, 0x4D49113A6176341AULL, 0x1F63C339A98E6FA4ULL, 
            0xADF71262F1137BF4ULL, 0x9C0EF503E24D3D96ULL, 0x5E1CDB95DA29AC52ULL, 0xE661D7F1F0C48E54ULL
        },
        {
            0xC2108EABBDAA9FD4ULL, 0xC43F2FB35D513900ULL, 0x646E46B30CFB0C26ULL, 0x4EFC997ADFCBED86ULL, 
            0x0AE07C4B0739C30EULL, 0x2C09D7DF7813371DULL, 0x30596D5E410163B8ULL, 0x0FACCA92B65141C2ULL, 
            0xD256C4543450B489ULL, 0xE006C6F6A34E299FULL, 0x3F32EDA2A01D06E5ULL, 0x6F9754DB65ED4441ULL, 
            0xF3B0A12891DC9D91ULL, 0x252C37E48F5F7BF9ULL, 0x24729897E76B9F01ULL, 0x6CE2657FAF3988BEULL, 
            0x900F1BF86D8DCA63ULL, 0x3784E2AE53756795ULL, 0x847CE50FE649E852ULL, 0x7994D11E2CF9F7BEULL, 
            0x2BF841A25D9DF05AULL, 0xB096577022A3F941ULL, 0x4274A334B30E391BULL, 0x50965F1952706AC5ULL, 
            0xA021FD53B6C2CAF6ULL, 0x86A2C5D5A9B62C20ULL, 0xD673EF427421BA96ULL, 0xFF75C42A37C382F6ULL, 
            0xBB0F6FD3D77E4F05ULL, 0x90DD2367FFEB9323ULL, 0x2C91ED16FE72D472ULL, 0x30539FA9BC907E5EULL
        },
        {
            0x25290F9AC7706C6AULL, 0xB34A3626ADF21302ULL, 0xC66FFC5C92435054ULL, 0xE1A3160D8F2E76DDULL, 
            0x41CC4E4C2F61F08BULL, 0x7F6F5614ACCCDC46ULL, 0xEB5CF20EFAEC6DCBULL, 0xD69036FECCF438C9ULL, 
            0xE5164BA66B33DE60ULL, 0xB35ABC92DC598E5FULL, 0xB65E03CE6E346902ULL, 0x9D4669C8B047F0F1ULL, 
            0xAED18FB314816A2FULL, 0xA8080C7C4F694A42ULL, 0xD10D22BC4F6C75DAULL, 0x85C9987CE2A6E0B1ULL, 
            0x2C809DAE9ACB4283ULL, 0x713B8E8F49B33E44ULL, 0x83761BED3FFF99EDULL, 0x73858B5DBC961012ULL, 
            0x681EE21A0F268924ULL, 0xD0D9753984FF7A57ULL, 0x3458CBAB255EF685ULL, 0xD0E452463615FF66ULL, 
            0x4B62014B24BC4449ULL, 0x609E5D6C0133A186ULL, 0x1D1C99CF298B1929ULL, 0x9421E9654FC60F1FULL, 
            0xE62DD11EADDCA7D4ULL, 0x9B74CA50C281B38EULL, 0x19339A3CF2654812ULL, 0xC3E290AFA286B2CDULL
        },
        {
            0x64D9FCB1F3DFE53EULL, 0x3D556BCA8AC3B949ULL, 0x7CF24261C1B78212ULL, 0xAB9A0F81DFAD5E6AULL, 
            0x7352B025F625B849ULL, 0xF49ABECF096A44B3ULL, 0xAC0F660E9534AFCAULL, 0x1211960A995F8705ULL, 
            0x4B66BCC59DDBF3D3ULL, 0x7FEE054F759EF137ULL, 0x1F273A84D1C414E5ULL, 0x5870BAA03B7FD6D6ULL, 
            0x2672CEC006094AC0ULL, 0xA618DB9D6F50E64FULL, 0x15EC6C7E67B4DFFBULL, 0x6D970B0E5C5725A9ULL, 
            0x309000A824CA29BEULL, 0x371DBB789BCEBB5DULL, 0x2548B55110C9F81BULL, 0x94F2BBCEFA15EB13ULL, 
            0x1B4AFE2B7E69C537ULL, 0x3C384E258AD9645DULL, 0x153B490A98FBD9E1ULL, 0xFE78DEC983D3980EULL, 
            0xE4AF86F0F742DC4FULL, 0xF3D1ED9B9119F0B2ULL, 0xD8751D5A94EA21F9ULL, 0x87DD2BB4EFFB093EULL, 
            0xB2179F5FE53AA578ULL, 0xA1EE45CDB48882BAULL, 0xBE5A9A45D62D8D40ULL, 0x816F44345C206AD7ULL
        }
    },
    {
        {
            0x8FCE1E454CD2DC10ULL, 0x3AE8AF6BCA24F652ULL, 0x2D4960B314DF1237ULL, 0x32572DC0F1AAAC00ULL, 
            0x8729CE2719CA9EC9ULL, 0xF697D38B7F99E52FULL, 0x3785B1DCF4146F51ULL, 0x798BD824AC7E3B12ULL, 
            0x0FC7CDD26E9BB107ULL, 0xED3D2631F80D7A5CULL, 0xA3D0AF46E9FF08E7ULL, 0x9EF1A72585055D70ULL, 
            0x3F44323CE74BB95FULL, 0x352A106AD950D729ULL, 0xC07563F3A584D068ULL, 0xB80781E833DB6677ULL, 
            0xA03386AD590047A1ULL, 0xBA7DC9FDDBF94B6AULL, 0x3B59B569279C07F2ULL, 0x4BC3A80EF658323AULL, 
            0xBA6C3C4E72D0CA8EULL, 0x863C4F27DF429C5AULL, 0x7215CC8274E6E170ULL, 0xA0B3B96BA2B2FB3BULL, 
            0x2E503A521E961EC7ULL, 0x277E8063BAAB8424ULL, 0xAE7CFFA343725F79ULL, 0xBDB9B91B025F24C9ULL, 
            0x657A873E464207D3ULL, 0x2AF46063E33C1D3FULL, 0x0147475F97A0AD58ULL, 0x9712D06CBFEF0CD0ULL
        },
        {
            0xB2474195B90FBDC2ULL, 0x61BB13EE0B4CC416ULL, 0x6633F02A795C8372ULL, 0xA67F91F395FE5666ULL, 
            0x70E1A360A3C4DCC1ULL, 0x22115FCC494180BDULL, 0x9C8C925BB1EC8379ULL, 0xEA1CCD27F6D99675ULL, 
            0xCE24ED4A0CC54E32ULL, 0xA47AFBCF95C8A30CULL, 0x3B5990BC243478F5ULL, 0x1281CE86CFEB5420ULL, 
            0x1B7758FA99914062ULL, 0x92282F15D94EE0ABULL, 0xBB19FFF1E172BD98ULL, 0x1D714DCBE6C05C91ULL, 
            0x3B8355E6E58B10C3ULL, 0xE6C82B5A2480623DULL, 0xA168CD933B560AACULL, 0xF38EEE59A9399DB7ULL, 
            0x10E30954709DB627ULL, 0x6F9164439E197C56ULL, 0xBC3504A07C53FD15ULL, 0x1A6ECBB89ECD3E90ULL, 
            0x37BE036BC2283908ULL, 0xDEF3E14BC2555B78ULL, 0x02B55420DEA345F4ULL, 0x9C055B36354AB281ULL, 
            0x893E8291FABEFB99ULL, 0xC053AA839DDC107DULL, 0x0A528747D93BE961ULL, 0xCA65D89F8FBF37EFULL
        },
        {
            0x9E4CD4D386D81AF8ULL, 0x596C5A9BD86D2EBDULL, 0x881AFC7BEEB0AB8BULL, 0x772F1342A263A70BULL, 
            0x03BCB50018D577F7ULL, 0xBF8A3C4C51D87866ULL, 0x87057A44933465FDULL, 0xA45702F839806430ULL, 
            0x00BA5F2ABA33489CULL, 0xDDB6EB976BF40726ULL, 0x0177F65F663AC956ULL, 0x2087E6FBE8D7E424ULL, 
            0x5E1CAF1E867577F6ULL, 0x8F2BDD7BAC73B3D2ULL, 0x4A9B2C10A1573267ULL, 0x0DA91ABA70A9CE54ULL, 
            0xA59331D97AB74EA0ULL, 0x93DC54FCE4480A64ULL, 0xBF8B95114343C6E8ULL, 0x5B2EDFB1D10FC6F1ULL, 
            0x4263A6146DEDA562ULL, 0xA3B8AEE2E9C2FB27ULL, 0xBAB7C8FEC455F841ULL, 0x29835544E48FA6D4ULL, 
            0x3E313B3DC62851E5ULL, 0xBCF1D2E886CDB27BULL, 0xB2CEF3CE6107DB09ULL, 0xB75CFECDAC96C06EULL, 
            0x675CA4B80A2542C3ULL, 0xB9D0FF3AE8475E8AULL, 0x7B46D24FC4237C59ULL, 0xA1BDB53D3EECD8D9ULL
        },
        {
            0x55C46DE47868E0ECULL, 0x1AA350F21C57D7AFULL, 0x08DD58DD98217B25ULL, 0x36D6AFE8A9540DCCULL, 
            0xB833BB010AE479A5ULL, 0xF41B5FA9B8AE308DULL, 0xED61E5819047303AULL, 0x3CFD90B045C7A38DULL, 
            0x93E66108151CCB27ULL, 0x3649A31D83D82109ULL, 0x4798FF693ED0F389ULL, 0x7649C4057BE97282ULL, 
            0xB622758547416A23ULL, 0x1253C12D2FE9DB5FULL, 0x277F35626EDD642CULL, 0x84CA4F6920D65E38ULL, 
            0x902F0942F5A78D55ULL, 0x652129B70A38CA36ULL, 0xA86CABCB02199B29ULL, 0x941758C6E8042D5AULL, 
            0x9EE3DD83AB5CFD53ULL, 0xF4B198C86DDBBB2EULL, 0xE86A0FAEBE42F13FULL, 0x49F9BC84F1F6C0EDULL, 
            0x44A174C25A2A95EBULL, 0x85B62A7147118F56ULL, 0x1BB2F0B6FBF68537ULL, 0x8885A80AE721BABDULL, 
            0x99FEEFF6F47F1E71ULL, 0x52E6B9CAB5698EB2ULL, 0x58A3F00FA393A92CULL, 0x7BC819187C749A67ULL
        },
        {
            0xD5E3E1081376A6C4ULL, 0x5465BE565E42FDAAULL, 0xC8895BB1FE87BD20ULL, 0x7F3DD5DBB409308BULL, 
            0x13264FE64A1FFBF1ULL, 0xEF5752B27248B495ULL, 0x49AC56CBC7447319ULL, 0x769A09BAA84C1936ULL, 
            0xE845245749B6FE50ULL, 0xF1CFDCA8B46996A3ULL, 0x2657796DC5F5906DULL, 0xBFB3F6773AAEFA97ULL, 
            0x171664C56BD879F3ULL, 0x9B2446610266E8BAULL, 0x746AF550FF136FBDULL, 0xE5E9A624B0BF4FD6ULL, 
            0xD34DAC9994660883ULL, 0x183667A7A45455E4ULL, 0x71EFFEAD0FDF5091ULL, 0x499B19AC5D1F9B7AULL, 
            0xC334639A31E0BE59ULL, 0xB675DF1DDA284D1AULL, 0xA8CAB84730CBDE2CULL, 0x432F101BF3351977ULL, 
            0xAB527A1FD150497EULL, 0xF3C3C3F840CB00A3ULL, 0xBCD2119E154E8ECEULL, 0x9BF6628CAEEC2E44ULL, 
            0xCF41E71CBB4393CFULL, 0xAA072695BDFED498ULL, 0x84D93B1C8CAE9089ULL, 0x53102B94DDE9384CULL
        },
        {
            0xE3CC5988E2404C5DULL, 0x016E1A35C5431036ULL, 0x5DD88FAD711B1BCEULL, 0x97A1834EDB50E81AULL, 
            0x06B9468948A85F9CULL, 0x40B535F80FA1297BULL, 0xEF9C9E1A9478D0BEULL, 0xF9BFC0C7DDBD9A32ULL, 
            0x0FBADA65CF4BB29AULL, 0xE864E87AEE38F2ACULL, 0x93A48C018C6A5865ULL, 0x4298DF0C4DA28CACULL, 
            0x33CA7B2F9024092AULL, 0xEA4A2AA37898D9DDULL, 0xEAB8E42245698165ULL, 0xAB6F2A63587625BDULL, 
            0x4E5397B68C2E8D8DULL, 0x311CD35BC32E8B33ULL, 0xC2E835B1ED6014BAULL, 0x80F5F77EA2E75575ULL, 
            0x1D51138278674839ULL, 0x751C94CDB08D06E0ULL, 0x394E5110E43E969CULL, 0xBDB7867B44ACAAF8ULL, 
            0xFF0D27157B4CA9C0ULL, 0xDB0BF245B0C863FBULL, 0xA1CEB1285EF60880ULL, 0x0F7FC7F16B738569ULL, 
            0xD256D9D3BE6BA5ACULL, 0x0F5B767A69E86BCAULL, 0x2D1BA2A36AB451A8ULL, 0x72E626C33D8B6266ULL
        }
    },
    {
        {
            0xFCA11A1F9FD7CA82ULL, 0xC6917B6FB0905B58ULL, 0x284AF05C10DFCEFCULL, 0x85C8686EBB9121FEULL, 
            0x3680BEB788DBE735ULL, 0x919775357DE0923AULL, 0x8B92F6E41E73ECDEULL, 0xE5B0E85A565372BCULL, 
            0x6B794D334435CCF3ULL, 0x2097A5DFFCEE4CB1ULL, 0xD4DBF66F97F29870ULL, 0x053FA877A9A7D54DULL, 
            0x7E46ACA2C8CA9D0DULL, 0x3AE2938B960126DAULL, 0x68B38F544CFD7ABBULL, 0x0B3233C4DDE36B98ULL, 
            0xB1EDFF22F7B5B833ULL, 0xE159BBD70AC5F411ULL, 0x9CDBDAE90D9FE3BFULL, 0x1D0972056415F4C9ULL, 
            0x2810148EEE79613FULL, 0xD858D147838CD72BULL, 0xAA67327C73F64813ULL, 0x81C9B9237019DFD5ULL, 
            0x9253A8BCF0C1F998ULL, 0x4CA5151333CAFDAFULL, 0x10CB5D5A62644428ULL, 0x1DF05936C750FDD0ULL, 
            0xBACD238317B42506ULL, 0x7027C8FD0E81C27FULL, 0x4CA9A8B033BC4488ULL, 0xD8A19ECAC1A14FB8ULL
        },
        {
            0x5E0453AB0B2CC0D7ULL, 0x9FA50C37C33F06D8ULL, 0x88833E9E62AF0D5CULL, 0x4A36676E892E87FDULL, 
            0x710ACAA2D2BB7948ULL, 0xD703D1DAFB8551B1ULL, 0xD15A167375FE79E4ULL, 0x973A4A4C0A6E8A53ULL, 
            0x57B3AF946528C868ULL, 0xF6DF7B28177BE86AULL, 0x260B7594A656F366ULL, 0xF417A3C52FF59D02ULL, 
            0x18B035DB716FEEC3ULL, 0xA5A96E739B77DDAFULL, 0xE9D02BECB1469584ULL, 0x19079E1F1C9CAA88ULL, 
            0xB3D77D2E1FA7820BULL, 0xF64BE6714330212CULL, 0xC643A92024DF7421ULL, 0x90E8EEBE16D45036ULL, 
            0x3FDA95428D454632ULL, 0x7833FDC2F0F03081ULL, 0x5E03BE1FCF76D0F8ULL, 0x6754C2CD798E7607ULL, 
            0xECA2F5527B50D5C5ULL, 0xB8827BAF6720F416ULL, 0x87352CA62F9E5614ULL, 0xCB47B7F07D2E1265ULL, 
            0x3C31BB7B23000550ULL, 0xC18A0D3590B4C25FULL, 0x9D77DCEBCA2167FDULL, 0x8B48A4582B43DE9AULL
        },
        {
            0x7E96CA111F710BE5ULL, 0x87125F6650F910D1ULL, 0x983E36A0310BE553ULL, 0xD2FDE61FEDC98AAAULL, 
            0xA25ABE1F8C19F672ULL, 0x0EF7C474208D9F0FULL, 0x273FCA5C71DFF907ULL, 0x1057AEF94555F9F9ULL, 
            0xFEE14850AA080827ULL, 0x2707CE5D5AE45471ULL, 0x84B04741792EB281ULL, 0x16CA4BCE45EB1C00ULL, 
            0x093AB6FCAE1169E0ULL, 0xC04D2B55F7EE6C35ULL, 0x6026A718CB3E1C78ULL, 0xAB8614DBF7BA6A5BULL, 
            0xAA7443B22A50B354ULL, 0x79CAA2E076AEC12EULL, 0x117D2F351F2C447EULL, 0x259F804EDB3A7A6BULL, 
            0xE998EF7C19EE9CEEULL, 0xAB51B8821E313E27ULL, 0xE26B6747CC103A29ULL, 0xE2A5DF85D859D431ULL, 
            0x0F0A99BC87A3692AULL, 0x0BD8121DBD7289B0ULL, 0x0EFD13726C311AD2ULL, 0xAAF706168B89698EULL, 
            0x309EF250E406BD2CULL, 0xEDF13C912C2B76EFULL, 0x4B97250922ECAD79ULL, 0x06B42DE73729D1C1ULL
        },
        {
            0x294DAEE0D0DED865ULL, 0xB60D78E5B144EDB7ULL, 0x143EE6164463936EULL, 0xF0C4A6D9E77F88CCULL, 
            0xA110E3C455D92F7AULL, 0xF44F78CFE0AAC3EEULL, 0x669EF795AFF01B7EULL, 0x1C6D69C03EF72793ULL, 
            0x79FE351864550437ULL, 0xAA3B374F287F0616ULL, 0x1C71816B419DE883ULL, 0x3F28A503A36079AEULL, 
            0x473BC5CC5823AEEBULL, 0x353DA068598C35A6ULL, 0xE2B12D63A8413151ULL, 0x9DABB494CD10ECDDULL, 
            0x06E24F3178E46A75ULL, 0xC95A1203D92ABF07ULL, 0xC2524DF171E439E3ULL, 0x88FC64A5E7E6A82CULL, 
            0x475B94B38ED88D02ULL, 0xC6F4D5C8CD1798D0ULL, 0x948F1798B1B1FD2DULL, 0x6A133531C64662BCULL, 
            0xD4A8BB18023F5C12ULL, 0xC7056061E1F4ECB4ULL, 0x35F7D65E9CD17D37ULL, 0x7E26744E2E5FEF8AULL, 
            0x8CF1FED284E78093ULL, 0xC992C05D7953A153ULL, 0xEE7FCDFFC7692ED5ULL, 0x15978142A958063EULL
        },
        {
            0xA1303266084221FCULL, 0x621D87CCF26C38DAULL, 0xC015B07B933CEAA3ULL, 0x6994F768EB681B96ULL, 
            0x7E403B6C5F616DF8ULL, 0xC954E4B2AC712593ULL, 0x7B378FB41308C24AULL, 0x2A405F590BE8F851ULL, 
            0x3F4B1DF7E6F0CF30ULL, 0xA024D62DFEB0DCAEULL, 0xB2FB4760DA9F8D9DULL, 0x698BDFB71F3CA19DULL, 
            0x3389878345E629C7ULL, 0xB29E8A436FA5C515ULL, 0xAEAD8EB032ABBDEDULL, 0xF4607069CED4CC11ULL, 
            0xCFE24FB71C02B29FULL, 0xD6812C3A66B93F63ULL, 0x75BA30138BD80F23ULL, 0x2BB715F237A28E11ULL, 
            0x80F07798045CD579ULL, 0xE706AE64A20B38E1ULL, 0x05183A2F9752F9D9ULL, 0xFF5D532763D03B5AULL, 
            0xBF68E8E8F8B50030ULL, 0x1F320F04E89965DAULL, 0xE86BBFCCE3D03A66ULL, 0x0E031A0E6712F85AULL, 
            0x10A648B8D1719A8DULL, 0x8E5718EAFAF38FB5ULL, 0x2582276051E05780ULL, 0xB967532A83BA47E0ULL
        },
        {
            0xC5FC361AE767F950ULL, 0x8085BD5D721407F4ULL, 0x6D7C15996207B427ULL, 0xBB125C2BF8CF2E26ULL, 
            0xA816E6220688133CULL, 0x5BDAFFB512732325ULL, 0x864E262707A21AC2ULL, 0xB7E13C90773A10EFULL, 
            0x5B6103D57E017329ULL, 0x74D97BEB48367537ULL, 0xC0C1CE13685E3EF8ULL, 0xA441660F0EAA074BULL, 
            0xC5CAA1B28E31C590ULL, 0xC13E0D6377C919E2ULL, 0x656D80258CB82E59ULL, 0x4A847F48B3B073BDULL, 
            0xD4418F8BACA53F03ULL, 0x958E808E30206155ULL, 0x3C7842CC1C27B146ULL, 0xD3353A7936C0A66CULL, 
            0xEFA3463CD8617E8EULL, 0x52586803E2DD1F79ULL, 0xA872C39A72F67890ULL, 0xAA40C7A4A83E616EULL, 
            0xB436868EE157967BULL, 0x2351B4CA7E6F394BULL, 0x14038A315C34576BULL, 0x47DAC6554F04120DULL, 
            0xA4B3E1B930CD1756ULL, 0x748E52E9163ABFC6ULL, 0x2AB2B314C2CE2336ULL, 0xD7D9800A0D2BE99DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseCConstants = {
    0x672C590967032CEBULL,
    0xA2DCBEA090956B48ULL,
    0x7663F0DD702C7766ULL,
    0x672C590967032CEBULL,
    0xA2DCBEA090956B48ULL,
    0x7663F0DD702C7766ULL,
    0x5270CC57D4D9247DULL,
    0xC9DD7A1DA35732AFULL,
    0xD5,
    0xBD,
    0xC5,
    0xFC,
    0xCE,
    0x2D,
    0xB9,
    0x7F
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseDSalts = {
    {
        {
            0x7B8011D20A3D64B5ULL, 0x4DCB985B6DEEA621ULL, 0x28A495523CACE41CULL, 0x6C73F6B112F7D7E4ULL, 
            0xD0D17407AFC3AC53ULL, 0xF39C15FDE0F76513ULL, 0xA1C72DF258642FD8ULL, 0xE2F23E573AE784F3ULL, 
            0x73E596A4DA2FCA85ULL, 0xEF70225F55F9B28BULL, 0x554AA0858660005AULL, 0x57088A73CA396F30ULL, 
            0xF2F6BB6685195BCEULL, 0x500F4FFCB014BD9CULL, 0x284CCBA85B8E122BULL, 0x3B52A078FF1A7D98ULL, 
            0x5E4E362EF6332859ULL, 0x01457E9B1DB6F161ULL, 0x2260CD60B85DFDCBULL, 0x09382905140FA018ULL, 
            0x9BFEB4C0ADCB334CULL, 0x2B5B618F2BBC0C4BULL, 0x79A3E2B27CCD85F3ULL, 0xC26C43E29BDEDDB9ULL, 
            0xC4747DEBF0845464ULL, 0x1F668CA5DB8EF559ULL, 0x6FFB73A42F735DA8ULL, 0xD4E776CCBE3C905EULL, 
            0xD8D6AE43F4AABDCAULL, 0x3EC1EA134BDA6214ULL, 0x857AE638F03A94A7ULL, 0x6B7C794AA282039FULL
        },
        {
            0x487846A514EE0EABULL, 0xD07978F86F664C3FULL, 0x341FD6E108497E68ULL, 0xB42C7687165402E5ULL, 
            0x047CD33FCC997716ULL, 0xFAEF6C14C7A706E3ULL, 0xDA39CFB158CBE4E4ULL, 0x097A9A50A5ED818EULL, 
            0xCF2FDD7D16AAEAE1ULL, 0xFFF9A2CDB481A312ULL, 0xA0DFC92644FA48A4ULL, 0x624E8A928D955D9CULL, 
            0x0B04E266B2CDDB3EULL, 0x05474C815AA9D008ULL, 0x8E735EC6B1816042ULL, 0x2F10442A50C6E819ULL, 
            0x946A9976B8DB3579ULL, 0x4FABB8786ED18D0FULL, 0x2EC7A093D3D6E951ULL, 0xAE2EADF4BE9C04E5ULL, 
            0x29F41F5B4FCB347AULL, 0x9902B836AC81EF01ULL, 0x78BC26BC20BD44D6ULL, 0xA8B2CD29C0336099ULL, 
            0xCB96B3760A3A3050ULL, 0x7BA2B503A9F1FBF2ULL, 0xDBE8AB571910BA19ULL, 0xF1F9D25CFDFCCD79ULL, 
            0x900D959AA2600948ULL, 0xA5D3B4911D9A4B3EULL, 0x2149F9C3F9180B96ULL, 0x5F590E44355C0BF3ULL
        },
        {
            0x38E694F37CE03427ULL, 0xC8182A4B31117C40ULL, 0x1F8E8D6E98A6B7D3ULL, 0xD2650B9135C2AEB5ULL, 
            0xD3A72445279D62E6ULL, 0xEEC26B20B4F0DD44ULL, 0x6CF0658963957246ULL, 0xA5D6F4E3198E6D5EULL, 
            0x10007E6C0A14B2F7ULL, 0xAB8B8A968C9F15CBULL, 0x2E09AA498DCCD487ULL, 0x1CB5BE2FB7CE9383ULL, 
            0xF202C7FC9E16E8C0ULL, 0xC61EB5379F8B9489ULL, 0x22B42E26809DA3B5ULL, 0xBD5348ED9A4C7C87ULL, 
            0x9E0179FC79F69A7FULL, 0xB07DD65FD9CE015BULL, 0x122C5894B2229115ULL, 0x7EFE9ADF43872E43ULL, 
            0x7B0CBC5C61CA5889ULL, 0x591FFB75DA0A1751ULL, 0x6F900548F9F5BA4DULL, 0x27980BA4E10CA2E3ULL, 
            0x4E64664808AFC7D1ULL, 0xF79D255D1ADB1223ULL, 0xAF6B21C48725293CULL, 0xAD4950B5A647CCC2ULL, 
            0xB1D3C87F8A4EFC92ULL, 0x789717960EE414CBULL, 0x0CD95C8F30FD6FCDULL, 0x603CDCDA1FA69D94ULL
        },
        {
            0xD4A979834175D263ULL, 0x683767AA86C0349EULL, 0x29767453668C6BF3ULL, 0x6D47A7755AB4E381ULL, 
            0x3CC04855478F871CULL, 0xD66542E1192B5DA6ULL, 0x80CE1C80F706ABD0ULL, 0xB1BD4055D61BAFD5ULL, 
            0x33036FCEC6390794ULL, 0x4107692824819EBFULL, 0xA7DA746D223DF61BULL, 0x447BC9500CDAB618ULL, 
            0x0F14FA0AB3DB483AULL, 0x4D8F79035B68630AULL, 0x75388782AEF60850ULL, 0x23DACD841CF8862CULL, 
            0x14827B3FF0761F61ULL, 0xECF53DE2DF5E846CULL, 0x151D7EF08F614EC5ULL, 0x5A264FB8AD129EA3ULL, 
            0xEC298D58C16C4F9DULL, 0x8A23122E11B56A97ULL, 0x6CB2E951FC073255ULL, 0x664919E570D38953ULL, 
            0x9CAE9A440B406382ULL, 0xB118142ABD424E6BULL, 0x2DA050D45A1F0601ULL, 0xB421BF668896AED1ULL, 
            0xC164BA44ED0593E0ULL, 0x458C3BB25232AA20ULL, 0xD359EB5BF025DE53ULL, 0x3B9D11B976EF7582ULL
        },
        {
            0x13FEA96635C2920AULL, 0xF2428C155BEB2F7AULL, 0xD509F1998A0A43A2ULL, 0x0FC6E4121DB6566AULL, 
            0x3D1D39D11DE4E288ULL, 0x5DFE03C25D97E2C7ULL, 0x80E35B75DDFCE06AULL, 0x9512DF997F829E32ULL, 
            0x896267E4FB109AC4ULL, 0x6AF9F69C7EA24A19ULL, 0x3D9DF0FEB7F354B9ULL, 0xD8C492F174478FEDULL, 
            0x6AC4A7D5451AD62DULL, 0x9DE98C3E62410E9BULL, 0x6515E724F080A933ULL, 0x217A26E4EFE9C12BULL, 
            0xF46F4CC7FEB93171ULL, 0xB8273695EAFC9825ULL, 0x3B497AE1E8439D13ULL, 0x5AE2332E38EA6003ULL, 
            0xC48E0ECD3E722D0AULL, 0x6C7792F03D2884A2ULL, 0x47DCF73AE36319E3ULL, 0x2799213E4F5D2067ULL, 
            0x491F7EF9F66C49ABULL, 0x60164426743E894DULL, 0x00CDA4730D1F664EULL, 0x972B131E5A585221ULL, 
            0x8E227AD1A5FF87F9ULL, 0xF49DFD0D73A604D0ULL, 0xD03C41F6B0F55684ULL, 0x76578B9D7FFBE8F6ULL
        },
        {
            0x5DB37977E908BD98ULL, 0x7109EAC63F68A3E0ULL, 0x24A53401749CC450ULL, 0x930F02BD5371CC35ULL, 
            0xDC6C9020A3530551ULL, 0x02E14FF8F0966D81ULL, 0xB21CBDF4E1FDB0FBULL, 0xAC8BFF527A786C99ULL, 
            0x443B8F635427CCC4ULL, 0xFD36BC491255A692ULL, 0x319E091C9E7854B3ULL, 0xE8DFE59843AA677FULL, 
            0x093C18A91CA4024BULL, 0x04D0846DAC712D4FULL, 0x22C290B1B6267761ULL, 0x85D3F98D853133B1ULL, 
            0x4A1E9FFDEA8E313CULL, 0x34997FFBEC2C9424ULL, 0x734AB25089A4E018ULL, 0xC19362B877357973ULL, 
            0x3056A9DE7CD829D6ULL, 0xF91D17EECF3FE1D9ULL, 0xD4E0AF333206E793ULL, 0x709F0CBCDAC0FC2BULL, 
            0x6279A8B55EF7B69EULL, 0x40C865A03F6D24B0ULL, 0xB13FA38A21605822ULL, 0xFFB968FD5F9DC88BULL, 
            0xA775BAA4E439B7A3ULL, 0x7960DCD3CF37DD92ULL, 0x08A9583D073CEF76ULL, 0x94D31BE4980C07EDULL
        }
    },
    {
        {
            0xFC607B1C926694B7ULL, 0x1F78C48BEDA5983AULL, 0xF5F7FCAAA6B3EC04ULL, 0x70AF8491A1D05CA7ULL, 
            0x6F5138DF105AF4B7ULL, 0x5E0E25E64F9D6819ULL, 0xB717E688C3386CC6ULL, 0xA01E5E593D4B7AEAULL, 
            0x8C5A5A253477694DULL, 0x1CC16F10A03791B2ULL, 0x92E1BF9D8379FDC1ULL, 0xEDF92C1D66E11460ULL, 
            0x0736E804829A0078ULL, 0xCC30AB2C3CC08914ULL, 0x2B09C805EA0D1C69ULL, 0x0C3077FED56540C7ULL, 
            0x4DE34773A1901821ULL, 0x8598B70A8B72AA8AULL, 0x71F3DAC8D26C8AF6ULL, 0x1F33C1DB6BD318A6ULL, 
            0x4DC636D1B1FDD550ULL, 0x93AAAC2EC13B7FF4ULL, 0xFC26C93B5AAA0308ULL, 0xA219324F0BA34C5BULL, 
            0xA024B1A6F01BA8ADULL, 0xE13BFF5001A81CFFULL, 0xE737DB7060EDA29CULL, 0x23132BD2ED316E5FULL, 
            0xB8DED93E14FFF1AFULL, 0x51F7701C0ED84782ULL, 0xB2D344F2E92347ADULL, 0x1E83C3DC74E873A7ULL
        },
        {
            0x10A0F21100F65088ULL, 0x08EBC5BBF2E31C3CULL, 0x0C2C42687BA03011ULL, 0x2765253B0986B9C5ULL, 
            0x65167D6AD14DF4B3ULL, 0xA3DAB2F07588E4F1ULL, 0x9E60EAE0D41A521AULL, 0x137424358432B62FULL, 
            0x67638A4B4015BCBAULL, 0xB951ADCB53CAA29EULL, 0x619E445FB3FBDB61ULL, 0x1EB206EA367E082CULL, 
            0xE7FFAADC60435727ULL, 0xDC41C549591B6676ULL, 0xA864ADBC5C9ED1A6ULL, 0xC832BEABE659907AULL, 
            0x4FA8E10B0744D02FULL, 0x7A0D5727383B22EBULL, 0x89C8933FC04C67B6ULL, 0x88E7BACAAB4F5106ULL, 
            0x76D1F7DA56C034B8ULL, 0x73F6179EA62C8109ULL, 0x9A299880EE234B89ULL, 0xB266678F50C861BDULL, 
            0xADCFF1776FC3BCDBULL, 0x2839F6AB55E04CD6ULL, 0x6D91AAAEAB222197ULL, 0xEABE8BB93E6E14FDULL, 
            0xF1133F3B7535EDA2ULL, 0xE97A61F4BE111095ULL, 0x344DD6F7F59FD058ULL, 0xEDA9BCAD65E9A01AULL
        },
        {
            0x8794DFF9C18224C6ULL, 0xC860880C0ED680E8ULL, 0xCCB2153877A994DFULL, 0x9E78E37EE4B3482AULL, 
            0x4FF65CCBAB0946F8ULL, 0x40525C10ABB73DC4ULL, 0x0D57F2067E9B3772ULL, 0xEE3B8B65B4C7C583ULL, 
            0x06B1BEA23B1DBC4BULL, 0x3E5983C426CA1A3CULL, 0x70DBCF03692BA186ULL, 0xF52B5A36502540B3ULL, 
            0x5749E140B6E407E6ULL, 0x2AFD52EC33DE2ABFULL, 0xFF5CCFAF75E0B2C1ULL, 0x0B341F9D6DC83A9FULL, 
            0x2FE9A2EBDCDE7947ULL, 0x05ECF9724016C909ULL, 0xF549BD7D08953C6CULL, 0xBDF1F617A887BF9FULL, 
            0xD1AA19AFBC8AC408ULL, 0xADF9E36E441CDD5AULL, 0x9E272D70C0D5280AULL, 0x2818E1CD5E51A1D3ULL, 
            0x6114E66B81EF497BULL, 0xF56B9147F7FE3E84ULL, 0x4EAC4D843753EA8FULL, 0xF7721CBEB3F59C60ULL, 
            0xFE6E69B0CBE9168BULL, 0x7C36C04D8F1C3603ULL, 0x8F67A8B6D0E73AA1ULL, 0xDAD839A2F3E2EB81ULL
        },
        {
            0xCE252D17720F2A5CULL, 0x9A20BA60348404C9ULL, 0x7D0198378E4C8EA6ULL, 0x5922BC6E07D8D29EULL, 
            0x24F3F66E0E879CA9ULL, 0x9159153AB09C534FULL, 0xBF02D870CA2A51D6ULL, 0xF447059BAECCA8BCULL, 
            0x24659EC11A98D0EAULL, 0xD6824B5E75EA8803ULL, 0xBD4F279846DA8F66ULL, 0xE1DEF4C2B749F6ADULL, 
            0xBD1C9A7682C1B9D1ULL, 0xC7A990FBA049E0B5ULL, 0xFA705D8E0B96A72FULL, 0x7C94EFB609D1B33CULL, 
            0x780895E6F230138BULL, 0x3C808BF13CD8A5ECULL, 0xD790657D46B2263FULL, 0x8149CDC146FA3A81ULL, 
            0xF9DD1BF7C9D1B432ULL, 0xC5AFDE9092F0775DULL, 0x437C2AEA9393E48AULL, 0xB2C31F16E91E2405ULL, 
            0xA01B23D61FF48DEEULL, 0xDA02F2A784FF30D4ULL, 0x3CDE11B6B8A62A15ULL, 0x9BA5867CFDA62E35ULL, 
            0xE917C901F29CFAC3ULL, 0xE85D14F7DBE1306CULL, 0xFB397B4FE9C355B7ULL, 0xBFFE5EA4FEA0A6ADULL
        },
        {
            0xDC24219818E93DC1ULL, 0x3D22160130E5DB94ULL, 0xA8F16E08E9CC4F4BULL, 0x5AA0DD9A8E46E8B4ULL, 
            0xF2373D5794A1C092ULL, 0x9965153E6EB097E5ULL, 0x8D9FB76B5E7F6E8DULL, 0xF510BACBFC109336ULL, 
            0x070CFD36B49AF454ULL, 0xA3F44709134FA3B8ULL, 0x6A1F39C67E0E4F28ULL, 0x031126C9F34E01EAULL, 
            0x43835C976D17B794ULL, 0x0FCF79520D46A70FULL, 0xB5E503ACC420B5A1ULL, 0x140D05CCE1D1D8A3ULL, 
            0x2585694023DD8198ULL, 0x3677EBA1EE0EA19FULL, 0xEE5C1AE8A33E7B45ULL, 0x3ADC648097EE83DAULL, 
            0xE44FD15E58D4BFFCULL, 0xADE49F1BA814DEA9ULL, 0x2F2049914907BCA0ULL, 0xA7DC9A827031FD4FULL, 
            0x44DCDED81A75359EULL, 0xA95C0F917B067020ULL, 0xE13AE25480E1D65EULL, 0x1630EF8D4FAA97E4ULL, 
            0xD1EF91810769E2E1ULL, 0x5157C1140AE9E515ULL, 0x9A8B91F57231D919ULL, 0x4F15954F3D0843FCULL
        },
        {
            0xA93371E2FACC254AULL, 0xB0FEE141838C9F8EULL, 0xF64CCD2F2F16FCA1ULL, 0x3152F84A093D1CA9ULL, 
            0x5619D4B9D61E0312ULL, 0x12E042EB41680372ULL, 0xEA210E52A986B8C6ULL, 0xA2B25EE8AC4987D6ULL, 
            0x7FED326791FCAF2AULL, 0x6E83CE9C75969472ULL, 0xBA5DB994ED470F1AULL, 0x458C597C57785BEBULL, 
            0x72CF779FE999FE35ULL, 0x46DE3CDD15EEA5F9ULL, 0x861AC0BCE431E8EFULL, 0xBA63BF4FCD676E9DULL, 
            0xF284D39E0FE057D9ULL, 0xDE1DB97D80A045AEULL, 0x4BF9C990B046B983ULL, 0x240BD89F97C5D27EULL, 
            0x7449BF411BEB5857ULL, 0x1518A56B5EAD8753ULL, 0x614FD970FF5633B6ULL, 0x1641248CA41F6D5EULL, 
            0x235D0E03FC754E8EULL, 0x24E3A1F8677E46FEULL, 0xC00903378685BE6CULL, 0x05246DFAD560D414ULL, 
            0x0768FCAF03848D8CULL, 0xC39E85BFE432B21DULL, 0x5391C16C801956F2ULL, 0x0576C2047F4E8D98ULL
        }
    },
    {
        {
            0xA3FBFE5D45BB7F8FULL, 0x759E491FD15FBBBCULL, 0x9C4390B0BF8AE06FULL, 0xCBDBE1B18ADC1E75ULL, 
            0x28531CB9702B3B98ULL, 0x80735C94BBC14766ULL, 0x52C7BB20B40B8960ULL, 0x8FD82D16B1796FF7ULL, 
            0x1E3722032720F69DULL, 0x86826C15EEF11AEAULL, 0x138D6F20B6A9A616ULL, 0x7B58E27FBED8925AULL, 
            0x8810ABE10A485751ULL, 0x38870657B8500841ULL, 0xA7A39F0D789BC362ULL, 0x658A2D651EDAA6CCULL, 
            0x9504E892E3886D0CULL, 0xF5907A8DF6E0F103ULL, 0x17F88481242BCF9CULL, 0x056A15019D285153ULL, 
            0xBE8E198F1A220420ULL, 0x5B30F1FC318FC557ULL, 0x56199BB671AD6390ULL, 0x85D41B0B5A3BD113ULL, 
            0x6596CF12678C6287ULL, 0x98DFAB893D05AFE0ULL, 0x3547F583D3EB5998ULL, 0xE87AF3B14B0315CCULL, 
            0x6E5D158C0C0AE8E8ULL, 0xAD4F4ECE06A9AB9DULL, 0x6477A11B27300A73ULL, 0x322B1CFE6A253DE5ULL
        },
        {
            0x829D78202C1CBB99ULL, 0xF656F031E13CE214ULL, 0xC96C31BDE0B3139EULL, 0x8199DA8F7CCBD54AULL, 
            0xF9951E1F041FFA84ULL, 0x0205A93A918E0650ULL, 0xB710013E67409FF9ULL, 0xD2873BD42C5ECE52ULL, 
            0x8D14E6B1F87F267AULL, 0xE599D59A1254FE58ULL, 0x4C38C8F98936A20FULL, 0x747C18235DC2913DULL, 
            0x9F0B0DCF7668E45BULL, 0x335615807A576D14ULL, 0x74BE95D274BB7E05ULL, 0x1966D6186723F66AULL, 
            0x3E58D716BCADE301ULL, 0xF7159A6D17E8D066ULL, 0xD45068B57E385A38ULL, 0x3C3D243AAE943223ULL, 
            0xF1CB5F49799B36C2ULL, 0xE720481E5A7AD622ULL, 0xAF6FE20F378B4B15ULL, 0x48D3068560175F7DULL, 
            0xECBF93FB2CFE0158ULL, 0xD28BC7219A329C25ULL, 0x4ED83F6C2650C49FULL, 0x160B05067CCD6C10ULL, 
            0x4A5E17B412C801E8ULL, 0xC31BA36A67AEFC16ULL, 0xC67CCDD963D24A7DULL, 0x9227E50665E1D9C7ULL
        },
        {
            0x1C40E0DBCCC9A99DULL, 0xF07F5EA09FCA53BCULL, 0x08B99B0CE28A1EFBULL, 0x4221C341D4C69021ULL, 
            0x5B8EA1CBF926AB3AULL, 0xE62FC3D8437E9D2BULL, 0xFB7885F00AB221B1ULL, 0xD65ACA039303AD96ULL, 
            0x5BB9D511CBECD9C7ULL, 0xFFB4436081FC439CULL, 0x5B920BEB58FEBF00ULL, 0xBF7A471098706EB9ULL, 
            0xE34C0EEB48931C0DULL, 0xE8B39FEA4156C92BULL, 0x55B407FBC669BC49ULL, 0x505BBAA873ECC8BFULL, 
            0x0CE2BAB031B86E3DULL, 0xD6579145E9466A0DULL, 0x26D583B272252231ULL, 0x31B3568F5C8863F5ULL, 
            0x0B8FFB08CF5101B1ULL, 0x0F1716DB266D5413ULL, 0x6CED6573150C7BC7ULL, 0x5C0F33B5045A95FEULL, 
            0x28AB7735D3DAEDB2ULL, 0xFDB570707A155A2FULL, 0x7BF82BE8327E00B1ULL, 0x8D37501130AC433FULL, 
            0xC5E413BD720DA0ADULL, 0xCBD69933367B7E66ULL, 0xD6E3B18D20CF56D6ULL, 0xE30860E9154DDF11ULL
        },
        {
            0x20FEED323C2C4CF5ULL, 0xE285930062090F69ULL, 0x58DF32FCBBCC84A0ULL, 0x8D81E554EE5A73AAULL, 
            0x4A5BC8260D2A91DDULL, 0x10E093E5F5A36520ULL, 0x6B325823FB027DA3ULL, 0xB6E41C32CD7888DBULL, 
            0xA46133F314C434D1ULL, 0xE0C7B36F45D264B6ULL, 0xDE7B385B912E1A52ULL, 0xFCA2A426BB849AE0ULL, 
            0xAEE7BB3195F5F4CEULL, 0x5998FF5C6C164E02ULL, 0xBBCBB0EB9B5DB050ULL, 0x40E5A5CD34D3FDC0ULL, 
            0xC0C37CEBC2EC1103ULL, 0xDBC9F98128A5F1DCULL, 0xF4D2FA6B614F9212ULL, 0xBA9B6A1BC785C6B5ULL, 
            0xAF97E208494F58F4ULL, 0xB988510ACE5AC4E2ULL, 0x869C1410480CB0B1ULL, 0xF5AD9332CC678EB5ULL, 
            0x5D76328DA4BE0863ULL, 0x05A7BD432E51D268ULL, 0x957634F0B59B3F7BULL, 0x1FD1745D53CFB6D8ULL, 
            0xDC1ED0D785BEB12FULL, 0x6FB0F90A62F8D190ULL, 0xD500053E58029970ULL, 0x699227FE08B2259FULL
        },
        {
            0xF98A30B98A65158BULL, 0xD606B7A0316357F6ULL, 0x25F9D895A4528864ULL, 0x6FF145844658D717ULL, 
            0x5C818F27EE9F7B7CULL, 0xF633E15124EA0B52ULL, 0x2AC6D5E75DAD7DADULL, 0x1529938F21DE594CULL, 
            0x0FC8674E30821C85ULL, 0xA7CD002A6378A4F7ULL, 0x7A14D9F86CC98F2EULL, 0xBE21778F486BC73DULL, 
            0x067155C190A80823ULL, 0xB43C4E65996DC839ULL, 0x129C69DF0FDBF0AFULL, 0xB88484AFDC767544ULL, 
            0xA16B7104DC15BA62ULL, 0x729FCC24CB71AA62ULL, 0x37B88EDB3C313063ULL, 0x32752DAD2F9166B1ULL, 
            0xCA619DDE4AD8C8DBULL, 0xFF6FF7FD49ABFA0EULL, 0x6F11E2AE13183C93ULL, 0xF50FEEED4317A3CDULL, 
            0x0E1A5BB94A54C56DULL, 0x816E2E3520FF5AC1ULL, 0x2C4CBD61591F6966ULL, 0x345FEDB7E0350F63ULL, 
            0x321F7C474CB870B9ULL, 0xBF0D1E9AE64BDC85ULL, 0x14662AAFB8D4A42DULL, 0xA06D032BB3DA19FFULL
        },
        {
            0x7ED7453D6A45B4E1ULL, 0x53CCED21D7FE0D70ULL, 0x8E07ED16F8B21126ULL, 0xDEE8326DED412101ULL, 
            0xACA936E01FB47FB9ULL, 0x32CB9CDDA04BEBDDULL, 0x407A96B9DB0298A3ULL, 0x1AE0BEADA21CB86AULL, 
            0x60DB438880301870ULL, 0x44FAE682E371A50AULL, 0x7353E576473D2BC1ULL, 0xA605B35D1E98B3D5ULL, 
            0x698C26785040C9F2ULL, 0x84118A8820C62B1DULL, 0x7598578D0D79F686ULL, 0x01A0A64EB5B955BFULL, 
            0xC000E88782D24D9DULL, 0xA792B3151B8C3950ULL, 0x8897115DFF993ECFULL, 0x7AE57F508CD25274ULL, 
            0x0EE277627196BFC8ULL, 0xA8053158AF275550ULL, 0x4874C82323634759ULL, 0xFEE5015EF96F7E19ULL, 
            0x51305DBF11A2796AULL, 0xD8A8EB9EB744C14DULL, 0x283B87940B404F0EULL, 0x42B084695BD91647ULL, 
            0x9A6C51BAA6B645F8ULL, 0x17D8C2F8468D8386ULL, 0x311E3CDB3A568D99ULL, 0x7AA59F5D072280A5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseDConstants = {
    0x2294B6194F46048BULL,
    0xD03BDD75168BD19DULL,
    0x7EE88C717AE9DF73ULL,
    0x2294B6194F46048BULL,
    0xD03BDD75168BD19DULL,
    0x7EE88C717AE9DF73ULL,
    0x70884B38C216DD8AULL,
    0x7318DD544E4353F7ULL,
    0x4D,
    0xDA,
    0xC2,
    0x0C,
    0xDC,
    0x0A,
    0x59,
    0x7C
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseESalts = {
    {
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
            0x5688137DB74D7DE0ULL, 0xFE7FE43A49476FEEULL, 0xCFAE537CEA280D15ULL, 0x1B331743196D584EULL, 
            0xEC3409F9C6DE8644ULL, 0xA22A3B7C38211376ULL, 0xD3377B67E6032777ULL, 0x77E0D330BBD89186ULL, 
            0x8F777311ABD9D79DULL, 0x651B0586ED22CE7CULL, 0x89E44A75A064065AULL, 0x3ADE99CA43D5D4D0ULL, 
            0x16C00BBA024AC7B2ULL, 0x1CB633A8B46F95CFULL, 0x43AB685B9CD372C0ULL, 0x14174952249C28B7ULL, 
            0x878DD8940C5A604EULL, 0x4D6DCF2D614F03B5ULL, 0x2188746A4433F4AAULL, 0x0EE374B29D91BE19ULL, 
            0x6A5453F7C56A410BULL, 0x0DE23EF280D1ACA1ULL, 0x8B6851F7CBA3C347ULL, 0x920078D9C7408CE6ULL, 
            0xC2EC847D47FEC097ULL, 0xE6FF1E4ACC6E3CDAULL, 0x7E1A0A03B29215F4ULL, 0xDBA9E0B0E5466376ULL, 
            0x7D33C703E08F3FD4ULL, 0x91E13E92881B748EULL, 0xB207D22269B68839ULL, 0xECBB0424BB220337ULL
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
            0x4AA8E0E9B45AF3D1ULL, 0x71BE3BCF7DC182ADULL, 0xDD52AC5160CB7B97ULL, 0x006E6141455ED175ULL, 
            0x9BFCE212D4FE9197ULL, 0xE1C3F33A69482EB0ULL, 0xEE54BF08BE625696ULL, 0x8385CD96579F14ADULL, 
            0x1387A162FEC89DA6ULL, 0xD44BFB868DC68AECULL, 0xF39A5C5ECC4BEE6CULL, 0xEF9EE27FC847689EULL, 
            0x9985865C9C479231ULL, 0xE8EF12440D8AA22AULL, 0x5634672F7FCA1F7CULL, 0x6BB09037AA5C97FEULL, 
            0x3F191F4C2EFEF8D7ULL, 0x60CAB8DAC4F3C79DULL, 0x3C236F65801B8D18ULL, 0xBC2F137686FB7B72ULL, 
            0x042F7A0AAC527281ULL, 0xB2443CD0984F569DULL, 0x007FDF30FEE1DCE6ULL, 0x7720C3A890D449E3ULL, 
            0x56ED05008C3526DCULL, 0x654CFBD091513108ULL, 0x2664391365AF5E87ULL, 0x39356FE343EF1CB5ULL, 
            0x57D7D8A1A6B2B7CEULL, 0x036C459A2B32C1BBULL, 0x715537087086690AULL, 0xDBA9FF434CE79333ULL
        },
        {
            0xA03E823C2787A6D8ULL, 0xEAE0DC9BE7C02F9BULL, 0x191F636333B4768CULL, 0xDEC424FBB5761AAAULL, 
            0x6B45DAB5FB9870D2ULL, 0x41FCA29EE69A953DULL, 0xE43B5A43BDCFD346ULL, 0xCAD7691BC5F6AE2FULL, 
            0x28F9F85546B1F090ULL, 0x2D0AD2DCA3B943D9ULL, 0xBACC44326D146E26ULL, 0x8E54415650CE0438ULL, 
            0x0FBB929C300F8F79ULL, 0x66AD3FEF5E3493C5ULL, 0xDC3E8ABE4EDD0E68ULL, 0x0B98C8907DBAA6D5ULL, 
            0x6A334A823BFBD406ULL, 0xACD3645330187ABFULL, 0x979DEAA51A34BF31ULL, 0x2DE224B173888136ULL, 
            0x36200D47F6BDA1B2ULL, 0x674746C9E39F2E46ULL, 0x99AC6EF4C19CCA6CULL, 0x5790503A17709020ULL, 
            0x70FC1C6CC5BAF01BULL, 0xD088F7F66C5664E5ULL, 0x6245E5A0FE6EC253ULL, 0xE7D763CD54338BE0ULL, 
            0x6323849DE72BBDEAULL, 0xF83CA4D38C25ECC9ULL, 0x496C8E5F49D4ADC4ULL, 0xD31BBB7B1ED57DA3ULL
        },
        {
            0x25AEB8E8D7A9DA6AULL, 0x16994DB092BED03CULL, 0xBCEBE7C641699228ULL, 0xC9A18B5B103BC6E5ULL, 
            0x38E4EB8687A07F6EULL, 0x7976675949B71561ULL, 0x06BC9E7EDE1D2560ULL, 0x3CF7C7A7A0C8A0BFULL, 
            0xEEB7F2E0C88FBC57ULL, 0x15457EB6DE760F27ULL, 0xB30D81D34823659CULL, 0x3F27406A8EA262E3ULL, 
            0x5B8924291B528F9AULL, 0x71756377367FE991ULL, 0x99F94248FA0F4C1FULL, 0x1C2753468A4F25ACULL, 
            0x1C399CBC7705999CULL, 0xAAB248AD7ECAF1CDULL, 0xF3DE2E0615796971ULL, 0xB0C98C02E87E969EULL, 
            0x12DDEB74820DFCB0ULL, 0x2C54D88B66CA0BE0ULL, 0x64C41F5198601DADULL, 0x6EAFFAB57449AEAFULL, 
            0x2EFF005C7A33B4CFULL, 0x44023291B6FE641EULL, 0xBB6094F19215AB48ULL, 0x6B4DDB7EE931F710ULL, 
            0x7DAEEC91FFBADE10ULL, 0xC00D50080093E20DULL, 0xE2F838C27127585DULL, 0x7E71F3019094ACAEULL
        }
    },
    {
        {
            0x1CAD2529E1A0402DULL, 0xEC6106A4909494A6ULL, 0x4B91D81DF81224E2ULL, 0xBA2127178ADCAAE5ULL, 
            0x074157AA26C052C4ULL, 0xBBFEA5FCD670227BULL, 0xFDA14BF511E60739ULL, 0x4577612309B23D03ULL, 
            0x7817BAB3A432E806ULL, 0x5518199EA755976BULL, 0xE3B3D8BEABA7F7C4ULL, 0x8D4100AFB1794438ULL, 
            0x10951B04BBE32F7AULL, 0xE5CE88686C170A41ULL, 0x74AEE02B92444C7DULL, 0xC00690804B094549ULL, 
            0xF97AD286943767BAULL, 0x395329ABF282491BULL, 0xE3D45BAD88884FDDULL, 0x7F48844254AC0A61ULL, 
            0x1F1FF891EDF89F41ULL, 0x837530C23BA18483ULL, 0xCD588592BDE95AF6ULL, 0x8932A6E0480FF1E8ULL, 
            0x17B58EE538D89833ULL, 0x07960DD3531C05FEULL, 0xF17328243F61CC78ULL, 0x436C1630579FAC25ULL, 
            0x6E72D89EF1206B71ULL, 0xB67D13E97E2BFF60ULL, 0x71D31217097C306AULL, 0x360AFE25B6079265ULL
        },
        {
            0x4C42F5002A74DFD0ULL, 0x9238CC6109B5D90FULL, 0xA54526B8F079247DULL, 0xCD8396527CB36E32ULL, 
            0x4CD004DFBEE76815ULL, 0x0359BD5FB0AB6AF9ULL, 0xF015EE1615002FEEULL, 0xEDAE286DB40BB193ULL, 
            0xA0676BDB92DFB190ULL, 0x95CD35ADE73F4B8FULL, 0x4356751C5537EB9BULL, 0x7880A7D14A2D3622ULL, 
            0x61424A4996673B89ULL, 0x9CAB86C8D6099437ULL, 0x305ECCFBE377857AULL, 0x2D9C10BD8A1CB2CDULL, 
            0x112020EE9A7FFAB4ULL, 0x58E6BF13A498DF51ULL, 0x02438ABC21B28226ULL, 0x0CB5593FC8EFE6CBULL, 
            0x2BBFBA4EA7E331C6ULL, 0xEE89A4DE099D9185ULL, 0x164081A6F2E087DAULL, 0xCAC6ADFA46906CD4ULL, 
            0x6AE9F3E178B48061ULL, 0x50C17FB210FAA00EULL, 0x7107BAB23569E1F9ULL, 0xAAA1FCD6F4D87B9CULL, 
            0x1FF5BA26E5723821ULL, 0x9370FAD01FA721D5ULL, 0x9A76F42A4C4A9297ULL, 0x9017623717E4A84FULL
        },
        {
            0xE040491B585DD871ULL, 0x371867832161AB88ULL, 0x2ED073E352C5C57DULL, 0x925FABBDC4A0BEE2ULL, 
            0x30CD98F978D7242AULL, 0xA0A2EB73E8917470ULL, 0x0DBE66CA0CFC62C6ULL, 0x4383A5744CFFA436ULL, 
            0xF4CC2AB3CB574A30ULL, 0x403B6DF20117CA2CULL, 0x2B7B2D5990FC784FULL, 0x88F35F82AE71B9FDULL, 
            0xC97B6AB77F474CF6ULL, 0x8C5F781FA10B075EULL, 0x5E8BDB78E0EE7586ULL, 0xE53BB4C184AEE727ULL, 
            0xD6DB83E44C0B02C0ULL, 0x9EB9E8FA69B7CD05ULL, 0xF60F588343CAC8A9ULL, 0xB741E55C27C8C41AULL, 
            0x2F94A09FC05019A4ULL, 0xE13663770FEC73C3ULL, 0x11DA08B8AC46B3CFULL, 0x7EB0FB7FF9FA8FF6ULL, 
            0x271D732FA9BE26C1ULL, 0x828A55EC892BFA90ULL, 0x3BC4A10000732BACULL, 0xF47EE1A52057C614ULL, 
            0xA01124ADEF004C46ULL, 0x7F18940B776A768EULL, 0x84BA5615E385B7D2ULL, 0x9693D1716CE8B0D9ULL
        },
        {
            0x496902013EB2F1E9ULL, 0x7A2F17BEAE93AE62ULL, 0x2D49944C472DF055ULL, 0x25EE438996751707ULL, 
            0x53EF57AC1DB65148ULL, 0xC10AD483B84A2CF7ULL, 0xEC05C61881F5229EULL, 0x816C6CC698CAF697ULL, 
            0x1FDA4BE30C510FB0ULL, 0xCAD987037B2947E7ULL, 0xC9A94ECD302CA000ULL, 0x40648299209C766DULL, 
            0x7ED89EFED67F2784ULL, 0xA0FC4713DECC518EULL, 0x7ED21EA419DF960DULL, 0x362583D26F0FFFE9ULL, 
            0xC1AAE4B164DC26D1ULL, 0x71C18A29B9C6FB73ULL, 0xF545BD2D78D76386ULL, 0xEEC43238E0B46D8AULL, 
            0xC2543A27E9951495ULL, 0x7E8480E9B42FB377ULL, 0x61A6213410D85443ULL, 0x8F3F622BA7270373ULL, 
            0x2E33862CDE6150C7ULL, 0xC31673B00B8E4D2CULL, 0xFAF700D9F726F6EFULL, 0x4AB17A1D2B0334CDULL, 
            0xF289EC577B91B972ULL, 0x31D35E8C7EE836C2ULL, 0xDA15E6D0DE439368ULL, 0xE33E8DC7AA57BE95ULL
        },
        {
            0xC55FA9120B3D692AULL, 0x4E1987BDF941C05FULL, 0x4A8911AAE0F76CBCULL, 0x095D9765603367C9ULL, 
            0x7D8AB84D8D16BE93ULL, 0x8C63BD4020510EA2ULL, 0x533E3295DCEA2508ULL, 0x2606B5B6D2410E41ULL, 
            0x7127D063B58E36A4ULL, 0xB2EAA9EA7B9018D4ULL, 0x7530900057A8ABD8ULL, 0xE0D82E92E14EF884ULL, 
            0xCA8C7F45D6DACF2BULL, 0x9018113462A2629DULL, 0xEC8D8D12DD74BC45ULL, 0x2A1075343B09AF4DULL, 
            0x83D3A422077CF9CCULL, 0x005F8C64EC7B4363ULL, 0x220BB2755A14C9C2ULL, 0xF6FBED3C4A2E53FFULL, 
            0xFB7B110502B887E8ULL, 0x41C6798CDDA6F5FCULL, 0x57F5E9998C98B680ULL, 0x4D699C646B5768FAULL, 
            0xB311EFABA9E49491ULL, 0xFBD8F41AE28A3690ULL, 0x12F8BFDE4611458BULL, 0x775660EA27541047ULL, 
            0x068E46D06D412F77ULL, 0xDD4DDAEA9CD3D6F3ULL, 0xA79C9E53CDAE30A7ULL, 0x62D19D6953FFA299ULL
        },
        {
            0xD58C93B32345B11EULL, 0xA4280DAF169F8E8CULL, 0xACCC7C8E8DB0C6DFULL, 0xB7C2CD098FAB2018ULL, 
            0x8BA7476402E01007ULL, 0xE2C45A0E40AB98ADULL, 0x0015D284B9E03C37ULL, 0x61AF93F7D66A946DULL, 
            0x13662357D587BBD3ULL, 0x5FD408DA5BF3F3B0ULL, 0x660BDECC9E824E51ULL, 0x2E1747600828C339ULL, 
            0x5C3A402400D26E85ULL, 0x35448408A6968503ULL, 0xA8E4F13E6D79636FULL, 0x2DED8EB2FA7E8515ULL, 
            0x021E358227AA8358ULL, 0x70B32D7A7DFC2509ULL, 0x5D93F35529EA5ABEULL, 0x476A95ABB3C26E6FULL, 
            0x97723E95BD8CB5A5ULL, 0x13A875D77D0C0B4CULL, 0x95BBFC95F11BE42AULL, 0xB8870E689F7EB70FULL, 
            0x1CD4F45BEFD9272BULL, 0xD8C3DA1A3C13B1C7ULL, 0xA729C09655651052ULL, 0x4902736F38C4ABADULL, 
            0x83A5B8D745A84976ULL, 0x727AE36D14A1B59AULL, 0x8037787CFC52CEE7ULL, 0x23854AC29389FC9BULL
        }
    },
    {
        {
            0x3CDE624FFEEB1240ULL, 0xF4007A392BD4CA01ULL, 0x8A22BEDCABD4D671ULL, 0x691061CD9567387DULL, 
            0x32136F46B055D031ULL, 0x5BBFC614934C9CF2ULL, 0x6CBD9DB3BB18D832ULL, 0x2F8B23589DCBABF6ULL, 
            0xD7AB6933B146755AULL, 0x19350597AE0BD718ULL, 0xFBADAC5E19A4CD88ULL, 0x9C50D238FF961516ULL, 
            0x3BC21803CAC6BE72ULL, 0x26782A31302E15A2ULL, 0x72C7EE7139551A85ULL, 0x85D3B04EE9141B64ULL, 
            0x8844FC809806FEF0ULL, 0x33938CD2A4E20A46ULL, 0xD3B381C8958F5459ULL, 0x32081F7E22D0BBB6ULL, 
            0x4F3223191EA14BB5ULL, 0x1E9F0B7B75432DF3ULL, 0x0B69E36319E53029ULL, 0xD5BB65B49CDA5751ULL, 
            0xF3EA871914FEF48EULL, 0xC9CC7584F024085CULL, 0xBD4E4E895E75675BULL, 0xB394B25104D1BF89ULL, 
            0x17647D2DFBC416F6ULL, 0xC304DF9BE95C38E3ULL, 0x9C2D782A798C13C6ULL, 0xDDBCFC33DCBE259AULL
        },
        {
            0xC616AB98CEE81E62ULL, 0xC8E8B25D9BC1DF3CULL, 0x36A0F9F969EDB5CCULL, 0x9635D61798D95A85ULL, 
            0x77B3604495DC40B7ULL, 0x145ED1ADF1CCA84CULL, 0xED34E08F48579F9DULL, 0x833498592279CD05ULL, 
            0x957CAE7FF5CD72EEULL, 0x951BD666A8C10B23ULL, 0x47FFFA983E1A0648ULL, 0x02D62D12F3F5F969ULL, 
            0x3FB7DF2D5858628BULL, 0x59A7C0DAD5373EE9ULL, 0x27DD88C6767B7452ULL, 0x524A1EFA9AC16C60ULL, 
            0xBD59B0493EB1A1F8ULL, 0xA94FE0C6B32B0983ULL, 0x4D8AFAE728FD51A6ULL, 0xCF647DA5C4D30C46ULL, 
            0xDFEF3C641DCFCEE9ULL, 0x9C2B137E13F2C036ULL, 0x32E54797DCF063BEULL, 0x90399828A332074CULL, 
            0x36763B546EE53FC8ULL, 0xE9D7E414C918D509ULL, 0x7DF03E918A21F81DULL, 0x1A0D1D1E47074D0BULL, 
            0xD77520CB36338561ULL, 0x97CF8AE0192EF89EULL, 0x16F1FE422736B6CCULL, 0x8AFA95270AD9C805ULL
        },
        {
            0x7DF6B38FE8ED350DULL, 0xC297C57F280711B5ULL, 0x3B16FA1F85AA440EULL, 0x34543AC57B07235AULL, 
            0x3DF29D163434B6CEULL, 0xC2B5D2D941C462CBULL, 0x6FE154E73D333DB9ULL, 0x873C60EE6F39B0F5ULL, 
            0xE1331972421A64EFULL, 0x91FFFA05571F44DCULL, 0x015776A348802B18ULL, 0xDD0B761821DFE5FDULL, 
            0xB5FDDC710CD03B3EULL, 0x8570F73B4503499CULL, 0xDA85F1546074D9F9ULL, 0x35CD328FAE951C85ULL, 
            0x68BB30C8B90184ABULL, 0xDB1BE13B5B1A16F1ULL, 0xE184F6B24517F2C1ULL, 0x8A3D6605424E0D50ULL, 
            0x2858D605F5DC72F2ULL, 0xF453CA32BB338023ULL, 0x76140C9E8FDD884DULL, 0x762CA6117C30407AULL, 
            0x2E293D4A910918ABULL, 0xF176A38D7B94CE66ULL, 0x7FF10E5516B5BCD4ULL, 0x966D9C6530A17D3DULL, 
            0xEB55F56795CB2CDDULL, 0x89B62BB7D676471AULL, 0x7D5734B76EB785A2ULL, 0x241B91F787D3A977ULL
        },
        {
            0x976D7BB7296F8D71ULL, 0x0F5D4F2B493109E3ULL, 0x71D5C9BF1D994F65ULL, 0x96ACB86E9125F042ULL, 
            0x299C944C17BB7F48ULL, 0xEF82A2A767B094AEULL, 0x3244EB44FBC44C60ULL, 0x398AA9BACBCE9F3FULL, 
            0xEF0ED18C4E1EA9BBULL, 0x2149DF67A0D5ED72ULL, 0x1C41D060167D7CDFULL, 0x297857039424E308ULL, 
            0xCAF1B03A2F1CB94BULL, 0xDE167577DEE1C51DULL, 0x2BAB1FE8C203252BULL, 0x5FFBB36AB61943BBULL, 
            0xD813B161CE44E8CDULL, 0xAD69240B001FA06FULL, 0xDC1429F86549B0D9ULL, 0x941ED9F3D28D16E8ULL, 
            0x0827A6DC85A12A43ULL, 0x7248C15D1CEF3A84ULL, 0xE680307C2983AD29ULL, 0x0DA1C042A5BFB288ULL, 
            0x75E54835D650C3F3ULL, 0x4381073827DAC1F0ULL, 0x68BD858E412F199BULL, 0xDF550C2BEDA7DC61ULL, 
            0x7513AC5F4403A5F8ULL, 0x65E6A6A447B9BF1CULL, 0xE6643C2A76EA4950ULL, 0xD82314E607A6A925ULL
        },
        {
            0xFDE8CF718CA3CD64ULL, 0x6C1F4CB6B9A1D9B7ULL, 0xD8933A7612C85AA7ULL, 0x07698793E0EBBD27ULL, 
            0xD7CD478B33F8BC3FULL, 0x4A921794B79F4A8AULL, 0x2D242A1C72292567ULL, 0x73F453708FC273ABULL, 
            0x419BAA71662D44A9ULL, 0xF98C2D620B634126ULL, 0x545905F7CC1A5C4FULL, 0x48897E93CF4DE837ULL, 
            0x0C1A54AEFC3BF16AULL, 0x7BB7B0D722F88BC9ULL, 0x3F6FCB5ECBEE8911ULL, 0xC79BCDA2BD904B9CULL, 
            0xA4E1CEE4DAC76007ULL, 0x3DFD2A58A5152509ULL, 0xDE4EA3C4892213FEULL, 0x45FAAB45CA5487C6ULL, 
            0xDC33EB003BB95845ULL, 0xD48EBEBB2DF07DAAULL, 0x07DE06C212FAF1ACULL, 0x00A36838112BFA6DULL, 
            0x18F195A309DEFFDEULL, 0x08625EC551898ED1ULL, 0xA178A1CD80C92845ULL, 0xB40B8D6388A31B84ULL, 
            0x7725F1D172A056A5ULL, 0x0B05D72F2782FDA8ULL, 0x23448C59AFB38B6DULL, 0x347AFBC665AEF69BULL
        },
        {
            0xA710F5A92DF5BC9FULL, 0x52E851B8303E2957ULL, 0xEE7BC47204EA4617ULL, 0xD23ED226C68C7B34ULL, 
            0xC239FD4826A39FE3ULL, 0x5341292AD816D2BDULL, 0xD5EE3AE7D6D4C683ULL, 0x144160A65E1A3756ULL, 
            0xF272E155A81086E7ULL, 0xED75D7ABEC4A4AB3ULL, 0xABD120DB7C6AFF03ULL, 0x0A7EEF3697CC8516ULL, 
            0xDEED04F44ABFBD4EULL, 0xF6DE501787887CCDULL, 0x5BD9785872A37D81ULL, 0x2AD953E7A9897351ULL, 
            0xDA98C28DF832E5B8ULL, 0x810EF5B9ECF3D0B4ULL, 0xBFFD0C49128D6229ULL, 0x9B3E0E98E95CCFFCULL, 
            0x31452ED08C32E36DULL, 0xE6033A81F6D4EA1DULL, 0xC99D260CFFAC8378ULL, 0x13463D8233F469DCULL, 
            0x24C37B92ABF7136BULL, 0x08D63E943C0DDF19ULL, 0xD3431D7953630D7EULL, 0x423DBD479BAF95FFULL, 
            0x7798DEC223EC3640ULL, 0x8715D62DBB5E38AFULL, 0x77EA0C75F4D6631BULL, 0xE5C16A4E74367B6DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseEConstants = {
    0x5D31E8D0F33E0108ULL,
    0xDC3DE5F4847A5640ULL,
    0x01768FF451C8FA16ULL,
    0x5D31E8D0F33E0108ULL,
    0xDC3DE5F4847A5640ULL,
    0x01768FF451C8FA16ULL,
    0x488A15AA947B085BULL,
    0x7DFBC7964DA5EF53ULL,
    0x3F,
    0x93,
    0x07,
    0xF2,
    0xCA,
    0x85,
    0x2D,
    0xD9
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseFSalts = {
    {
        {
            0x3B57C8DC99F86218ULL, 0xFA1355AF87E55ECEULL, 0x01CC0DF1ED34A796ULL, 0x101BE01D54B92208ULL, 
            0xD177B5CFC840A7A8ULL, 0x4E517C5185C94E44ULL, 0x80A56742C1EF75B6ULL, 0x3EEFA21A3C6D20FCULL, 
            0x6151F9F145943F61ULL, 0xC525DDBBD0F8A17DULL, 0x88CB39991FF9E3E2ULL, 0xB2D82F5E0EB735EBULL, 
            0xFE5349E9457684C1ULL, 0x25A675CC8DB505A0ULL, 0xFFD1A04A4BB227EDULL, 0xD5DE705402518543ULL, 
            0x02368F3A549EDC36ULL, 0x038BD750F8CE9997ULL, 0xEE4F52E46D9C38B0ULL, 0x337153B77EA9223DULL, 
            0x55F114BA3820C878ULL, 0x9825136641D15F19ULL, 0x70FB8216048FD64CULL, 0xD7F4EC5D79346372ULL, 
            0x50C1D3262B963E78ULL, 0x9AE072AE8E6A99C0ULL, 0x460C1188AA16F309ULL, 0x9B5D4A354105E74BULL, 
            0x8268683B0B6BE9B1ULL, 0x9B56F1071151CBD1ULL, 0x774BF3C40D52F19AULL, 0xCCEA4D77331B9B46ULL
        },
        {
            0xBC3FEB3660F2698FULL, 0xF4B807A6D54E42F5ULL, 0xFEF435534C0401C3ULL, 0x889E0036CD34483CULL, 
            0x9184F77BA5395E81ULL, 0x6546ACC580B06CD1ULL, 0x5B7E369D56F258A5ULL, 0x1CA972F273178C4CULL, 
            0x3C0DCE6C29FF782BULL, 0x581D6042115931CBULL, 0x0F3F51C8622E87C6ULL, 0xCCDE384960E67274ULL, 
            0xB179C6F1F5C9BC0DULL, 0x0AC7BC6E7F72625CULL, 0xCE30EC550A009790ULL, 0xFDC5DC76FC7E8B32ULL, 
            0x20C70C9F25C366DBULL, 0x44E71FDFCC83DAAFULL, 0x91F4EA48879BE1A1ULL, 0x1469C214D23ACCB2ULL, 
            0xC7282DAF3EB3E0C2ULL, 0x260DA01BAA91B3E7ULL, 0xDB12413546D5FAECULL, 0x89D377231BBD9424ULL, 
            0xC7CDA17BA3FEF21CULL, 0x9D96A66F581B36A8ULL, 0x955881FFBA2BCF74ULL, 0x285524CF8B5FDB41ULL, 
            0xE6C99CD6CCC895E4ULL, 0xC792389A20EC0CB1ULL, 0x14977F430CF0E0C9ULL, 0xCF8546C5EF9774DAULL
        },
        {
            0x3E6C428A4EFE46D0ULL, 0x84691644494ACE8EULL, 0xBE3EC61DFA571DF1ULL, 0xE50C293D51D5FCD4ULL, 
            0x7F030E72D760E595ULL, 0x5852578B8362053BULL, 0xC44EB1A6D71594B1ULL, 0x64FCDEF94CE553E1ULL, 
            0x2F55BF890B18A1C3ULL, 0xF5A0083E606529C4ULL, 0xAF532A6597E1EFFAULL, 0xEBEC500666140204ULL, 
            0x983FD1B05A0CC4CBULL, 0x37856833D84C9C94ULL, 0x586CAF659EAFDCA5ULL, 0xB7F4E4ADD924BE10ULL, 
            0x958CC2F01F038AFAULL, 0x7F47D1377E28F21CULL, 0xA93F115AFFB83012ULL, 0x4251A3371105D173ULL, 
            0xF745C4994C1BDE3AULL, 0xF803E3FA928A6C89ULL, 0x39E0742D6EE13C90ULL, 0x0C3E2D6E0E0DA204ULL, 
            0x7DE873DEA0A6758EULL, 0xB2478213982C0BD0ULL, 0x3F02A38CC3B95ED8ULL, 0xCF3F78D09062A975ULL, 
            0x266B6463B33A1664ULL, 0x57F8598732502C42ULL, 0x5735CA80086BECAFULL, 0x86754E56AFD066BDULL
        },
        {
            0x133EFC99266327DFULL, 0xDD90EFACEBB6F122ULL, 0x3528520B08C969E7ULL, 0xC933FD67B694CEC8ULL, 
            0xC6118111CBE09B33ULL, 0x272834DC62BC9A55ULL, 0x7E7D8E3199CDD815ULL, 0x49C1CC28FA161902ULL, 
            0xAEB5EB7CC22266B7ULL, 0xDA52687BB93A92FFULL, 0xC9B3AC5D9287F4F5ULL, 0x32719FF14CE55AB3ULL, 
            0xD2AD3A9BF60CB13AULL, 0xD70D5092EDB8B1E6ULL, 0xC14A55F7778D5E9DULL, 0xA0D347A56B60AEE2ULL, 
            0x3E6B1B647F03679CULL, 0xB9D1269FAF4B7338ULL, 0x71EFD2FA71EB40D5ULL, 0x87EBB5DC5620A702ULL, 
            0x36E90E285FAD33E0ULL, 0x3873FF9D9FBEE746ULL, 0xD0A8238C474DB32FULL, 0xC43EA156CA5F1EABULL, 
            0x125187871497535DULL, 0x3A94F7EA3BD08E0CULL, 0x14FF85014295BFB7ULL, 0x01CC66196D8E966BULL, 
            0x0D56BE0E0D91C9D6ULL, 0xF8B9DD23B18582F7ULL, 0xBF6EFA3F40BB769EULL, 0x46E765E851638718ULL
        },
        {
            0x2E0A9B0E810D647BULL, 0x1D26DBA858E10DC5ULL, 0xF3B72BC41F0390B3ULL, 0xE2505B6D63E638E7ULL, 
            0x348B7945CBD96FD5ULL, 0xBEC023E6E5D8129EULL, 0x020FAFEA59537591ULL, 0xAC2C96DCA50F3226ULL, 
            0x5E56FAEE2949C744ULL, 0x1174694629782555ULL, 0xA83B7BA344BDAD40ULL, 0x76A6DED682F4CC14ULL, 
            0xE59E91E919027CCDULL, 0x1620A9FCA149D6A4ULL, 0xCE36681906DA0AEAULL, 0x0C5B3616B4550FFEULL, 
            0x1E0C6487523CF3F5ULL, 0x3CD3DCB4E19913EEULL, 0xD5F27C2B62149693ULL, 0xF01D458BCE812A69ULL, 
            0x3178374ACC86A142ULL, 0xB079379B64FF84F8ULL, 0x36EE1D1D406D4C67ULL, 0x2DFC871ADD835264ULL, 
            0xB4142FF6F8C691A3ULL, 0xDA0DDAF9CA400790ULL, 0xAA080CB652201B60ULL, 0x9CB28A35915A39C4ULL, 
            0x54D5A422DE0DA5D8ULL, 0x26079C83DD23207EULL, 0x8A7A36AC935103BEULL, 0xD42D7F04D6607041ULL
        },
        {
            0x07605654DDBF0167ULL, 0x4D6F5ECD1F5E9B89ULL, 0x103DCE9CBDCDF318ULL, 0x6FFC21DEBE5B6917ULL, 
            0x5524D326BA659A46ULL, 0x93563EA858E4245DULL, 0x53CA9EE23881305BULL, 0x3EC3AC6E3A2702DEULL, 
            0xDBDC53B7A17ADBA6ULL, 0x72F85AAD8603A236ULL, 0x2286CF7CF04C6694ULL, 0xFE760433ED9602F4ULL, 
            0x8CAA30DA7DEE9D37ULL, 0xD6B72DDB990024E1ULL, 0xE1037027662D1EF3ULL, 0x5E8CA099429448FCULL, 
            0xD86AE9234D45058AULL, 0x4766730D71E26468ULL, 0xEB4E0E6843D842A5ULL, 0x95812FB10DC29F83ULL, 
            0xFDF5F764B38042C8ULL, 0x0E8A306194A599BFULL, 0x97BD8589F70F3E7EULL, 0x7F6C69E91D4E6F79ULL, 
            0x0883E0F46AD8E2E9ULL, 0x377CACE189E4012CULL, 0xE5F09FB7FA7BEEB2ULL, 0x84AE25E0298F0F1AULL, 
            0xEA9C2FD600B14AFDULL, 0xE7B17C1F17EDA1D5ULL, 0x166AEC898465175FULL, 0x090280DDDD3C39F0ULL
        }
    },
    {
        {
            0x088C2384E7CBC334ULL, 0x136E7C73EA839150ULL, 0x76EF5632BB1A4D7BULL, 0x9E13963C9EAB1503ULL, 
            0xF474CE9663B56C9EULL, 0xB06D6CB9AB35246DULL, 0x61609E20F177ABD4ULL, 0x35CCECC21EBA8D8BULL, 
            0x3601EA60996F11F0ULL, 0x7400BD6F76A8BB1DULL, 0x7F70A79BD9D0E797ULL, 0x8E411C887AD658C1ULL, 
            0x4348C80B461DEAB2ULL, 0x5A3C1013F5CC4C47ULL, 0x5FF5FA3585421B15ULL, 0xA34B878C12AFB4FFULL, 
            0xE52B0C38286B07B9ULL, 0x791063051C8D1A74ULL, 0xF0014DF9DC07499DULL, 0x8C75EFEF87BACE83ULL, 
            0x31D4D3ABF26A9E04ULL, 0x9F96F6B883913CDEULL, 0xF12AB1865791D48AULL, 0x2B8D11920119F634ULL, 
            0xC5D46D8F1B153A36ULL, 0xA7F5849365C60DAEULL, 0x8E8129C54769C492ULL, 0xF4861B74211A201FULL, 
            0x7ACB41901D42EC8BULL, 0xA9D6157A97F32929ULL, 0xE5C925FDEEF24D3EULL, 0xA1FE35825AA0FDE6ULL
        },
        {
            0x9CC4D8348FC864CEULL, 0xC047419AB515272CULL, 0xBD287A8C755232A8ULL, 0x14F2DCC109AF2073ULL, 
            0xAFD8ADAE7807B5E1ULL, 0x2B1A2E4538695099ULL, 0x9E62D3003714A0F7ULL, 0x980D26F621AB6E65ULL, 
            0x14D0C02B2AB262FCULL, 0xD830BA2FAAF140D6ULL, 0xB849037E8E75456DULL, 0xC9BD035E9B84695DULL, 
            0xF1D328208D8702C8ULL, 0x18077158FCC22BF3ULL, 0xB8641908BAC92762ULL, 0xEA250885F0C9CC90ULL, 
            0xC1ADD8FB2FDCE023ULL, 0x5AE9B01D560FFF9BULL, 0x0153B8DC5ED9F3A1ULL, 0x15A1B5AF2F543873ULL, 
            0x615AA8D04FA71A45ULL, 0xE3779C53BB332F9AULL, 0xD8ED68871C8FD9F4ULL, 0xA1293405EF9412CAULL, 
            0x70524896FE1F2047ULL, 0xD21CB292A528D463ULL, 0xE7AA8F454B6689F6ULL, 0xAC746837487EAB00ULL, 
            0x6E216DFC59723E84ULL, 0x5926B561BF06638EULL, 0x350F3946CFD51BD0ULL, 0x12183262BC619F64ULL
        },
        {
            0x78643EB9C6748451ULL, 0xE9FDAF7F80B2012FULL, 0x9551EB2F913AD4B4ULL, 0x3D8956DDF2561B9AULL, 
            0xF5B9DF0A868F08F8ULL, 0xF3A0EAE73FBE6DE3ULL, 0x8590A446520F53C9ULL, 0xEBEA8919A6D0934AULL, 
            0xB89BCD54CB582592ULL, 0x2A83082415858C79ULL, 0xF0EE43ABEC9CF8A3ULL, 0x270D0A55A10EA79BULL, 
            0xD91F01794A4CE495ULL, 0x53BFFAEF36F0DB7CULL, 0x648708C3E04BE964ULL, 0xEF0EFFC2427BA63AULL, 
            0xBA5F9059B3F6E389ULL, 0x22E157194320ED2FULL, 0x2A5BBD73DD4D7B0CULL, 0x08C2968E081E0C16ULL, 
            0x606B1F3B4AB2FAEAULL, 0xFBCB517487B2C24AULL, 0xBD49F7ADD64EC24FULL, 0x3BCA77D828294F15ULL, 
            0x92974914C2ADCC59ULL, 0x9CA908E7D6838D24ULL, 0x1952C3E03831806EULL, 0xB4FD68A2013EB748ULL, 
            0x4F2AA7251EBC0F63ULL, 0x7C17C4DDC565297CULL, 0xAB5F102C8501264BULL, 0x5CB088605845B9E1ULL
        },
        {
            0x720533CACFC24FDCULL, 0xC0059E5A4E5B9651ULL, 0xEB98738BBA62D958ULL, 0x917F05D821AC8307ULL, 
            0x134416993238FCECULL, 0x850EFF413855B535ULL, 0xE4D53CE7409F92C3ULL, 0x84739D81E409EEA6ULL, 
            0x46252100C3D7F2BAULL, 0x32BF37379BB6E86EULL, 0xB42C455AD8FBC59EULL, 0x707ABF0899B42AE6ULL, 
            0xF43661779489D4F5ULL, 0xE8455A567AFC87A5ULL, 0x3604B5CB34B3445EULL, 0x4F7309AA8F480F67ULL, 
            0x1710B32DB71100FEULL, 0x5E8A712190060E92ULL, 0xC2265ACD18F5350FULL, 0xF606CCD35E4A8D61ULL, 
            0x5F68DF58071DDA0EULL, 0x8D0D8F31ADA433AAULL, 0x3B43D58D1CAF5B71ULL, 0x2A4B4E7BA7FC937FULL, 
            0x759FAB3D9D5BA946ULL, 0xA7FCC039FE06ED04ULL, 0x25F9917B83945E83ULL, 0xB7869625C5F53BFBULL, 
            0x38FEFB91FE496811ULL, 0x46B5E06DC0F1F681ULL, 0xC2C14DAE1763330CULL, 0x223E482BD832271EULL
        },
        {
            0x72A917FB72C1176CULL, 0x8682B1B45C948482ULL, 0x9506CC259CFCC5ACULL, 0x451482441083975FULL, 
            0x9B66DD5C7B20B450ULL, 0x11FCA02CB0FD5D5DULL, 0xB31129BBAB5976D4ULL, 0x1C022E90D88D893FULL, 
            0xB15D33040A49F094ULL, 0x62EE1C7FC6FF245EULL, 0xB3136DF008B3BB7AULL, 0xB456611BF194147CULL, 
            0xAC6EF410DE853D08ULL, 0x0F30F748FA6FB4F4ULL, 0xE5808AD469F970B3ULL, 0x0690BB614B262477ULL, 
            0x3DD02E01BF163B7DULL, 0xF9A2633F9C033DC6ULL, 0xA7BADC33E52011C5ULL, 0x15984A7F553D4E6DULL, 
            0xA02128568F59E01CULL, 0xF4E124BE0E6E1CC8ULL, 0xCFDCEBE7AE745F01ULL, 0xC142825FDB6B7D2FULL, 
            0x0DEAC49796EBC432ULL, 0x252B5D2D7D376C99ULL, 0x627FDE858C20EC55ULL, 0x3CDCAFAD3D461E62ULL, 
            0x3867B9C99DF62F2CULL, 0xA1F6E4849EE089A1ULL, 0xDA776551FA0A1BDFULL, 0x22E08DFADA34114CULL
        },
        {
            0x922F003B257CECF7ULL, 0xEC11E8BB59EE670CULL, 0x2D1AF792C3C7480AULL, 0x4CC84EFCBD28692AULL, 
            0x54AF233E932E1E58ULL, 0xB6704FC26CE911ADULL, 0x6F84A131CF5D00E0ULL, 0xE456F824CF6FF57EULL, 
            0x5F44526F18EB9997ULL, 0xDACE59D43F23C467ULL, 0xABE9827F31A1C8A0ULL, 0xDB8C495F05E86559ULL, 
            0xDADBC7B93A2B905FULL, 0xD432E77E0BAF5B8BULL, 0xAC557F88E1215918ULL, 0xC20C08F340C4DB1CULL, 
            0xBB595AE7CA1303F9ULL, 0xEF795041BDCCE34DULL, 0x11684838131D73FEULL, 0x197ADA6C6CD93D3BULL, 
            0x1C0F479647872F86ULL, 0x799E818614C40540ULL, 0xB060D8896B8A0EA0ULL, 0x91AB4ABE5490A5EAULL, 
            0x9C59FC0FDB276526ULL, 0xDB4BCAB7CF416538ULL, 0xBBDF3FAD9FEDD5D3ULL, 0x471EAAD29619D36EULL, 
            0x032B84A2C478297EULL, 0xC40128F0E9279164ULL, 0x232AD3845C7ED071ULL, 0xB9A4D6B692C191D1ULL
        }
    },
    {
        {
            0xCEC88F8005BA55E3ULL, 0x6AB9404DDCB804CBULL, 0x5546D930B3955E29ULL, 0x305433B0F7588D32ULL, 
            0x0C7963C519A69CF0ULL, 0x510E49E8106064A8ULL, 0xC8C79FE1C5E9D1AAULL, 0xF7CECA2588BDED7BULL, 
            0xB7E74EFB4E73B56FULL, 0xF19B92BE746ECE85ULL, 0x961AF95E519E8068ULL, 0xADBD07E8209EB147ULL, 
            0xC2FAEC569690A7A7ULL, 0x1850D8A989B02F7DULL, 0x61661546C76DD62CULL, 0xEA8547CE2493A9AFULL, 
            0xCDE797F366D07184ULL, 0x77543479F9564EC7ULL, 0xF0F38D1E6D792FB5ULL, 0x5749C10664CA50D8ULL, 
            0xCB7CC3D03877A556ULL, 0x46E115616BD53603ULL, 0xC010976589507452ULL, 0x78619A91E71604E9ULL, 
            0x635972F96D45B443ULL, 0x022CCA041CC3466FULL, 0xCF5D7A38A37EF13AULL, 0xA73A49CD8F700C71ULL, 
            0xD05725185BD0486FULL, 0x9C3C8ACC29006A3AULL, 0xA0913A5FC5225DB0ULL, 0x342DF58500820513ULL
        },
        {
            0xAED77F45BC513B51ULL, 0x9A2800B761F21553ULL, 0x9E46415AF3D88F9BULL, 0x9F2522FF66DA5103ULL, 
            0xCC02609B8AB6B587ULL, 0x3C43EFABBA37BFF4ULL, 0x4AD4FB46EB2B0294ULL, 0x88EC89B5A2C18E76ULL, 
            0x269A4F07DFA6BDFAULL, 0xD8507F5D609AA2B1ULL, 0xBFA9BDF7EF7428DBULL, 0x9A89D65141D74130ULL, 
            0x8B69A8A85E074A11ULL, 0xBA002014B957F0F7ULL, 0xDBCBA5F74B619139ULL, 0x94CEED0A7C9B745BULL, 
            0xC235034EF679BA66ULL, 0xE0DDA3EDAD17330EULL, 0x69B3E0AF4271A6E7ULL, 0xEA67CEBA7C4F1935ULL, 
            0x5B8FF40296E8A613ULL, 0x99BB1A9FABBAEAD5ULL, 0xAD3200BA7EC54599ULL, 0x8594E8F143A4C617ULL, 
            0x4591CD1D2B81F0D5ULL, 0xA3348CA1E62B68ADULL, 0x7483CDA4C16BE31FULL, 0x91122CFB56EC9C5AULL, 
            0xD16A5669FFB687C1ULL, 0xD9C84C957546F62EULL, 0x75EB2BD82EBE1B29ULL, 0xFF6A47633D221092ULL
        },
        {
            0xCD674F49A3A2B5C3ULL, 0x35FDBE5F5A9AB6D3ULL, 0xFE936F56BB8E9602ULL, 0x29B8DD8D7BDD9C81ULL, 
            0x03037EB762D6BD7FULL, 0xBFAA4C49409E5B5AULL, 0x3AA6E68EA296DE65ULL, 0x129EAAB4C4D72368ULL, 
            0x7E8ABA1E2A2703D5ULL, 0xE4EA0A0EC48D5514ULL, 0x3E697B59DC5BEEA2ULL, 0x70D60A59F80CA1C9ULL, 
            0x6A509BAAF6B3BA6AULL, 0xB3A98851132BD824ULL, 0x3399FB150423316BULL, 0x6B42FE4498807976ULL, 
            0xAF327CD68AF17DF1ULL, 0xDA93FAB26F98BE79ULL, 0x2B76AF4B7D514929ULL, 0xFC55749ADB46EAC2ULL, 
            0x129729F6F98BA8B2ULL, 0x1BC66D3CB9AF45F8ULL, 0x348A7F9975E7DB39ULL, 0x3578D93F1087BF2AULL, 
            0xC9EDCCFAD6B41D78ULL, 0x697B8CA028EEA711ULL, 0xD015934A4AA0E2C3ULL, 0xBD9392AA7EBF9414ULL, 
            0x60E84D6ACC9E2C96ULL, 0x634C834BA2723F15ULL, 0x9EC4F0835D7574F6ULL, 0x56775251DEA237BFULL
        },
        {
            0x285C06778A4680B3ULL, 0x2FEE2F7C0FFE9B6EULL, 0x13006B21EF1E2D10ULL, 0x3AB4EB46B2BDB67DULL, 
            0x21483149A04AD06DULL, 0x9EBA383C8840A2C5ULL, 0x5E44EC3DE57B1523ULL, 0x74F6BADE8B050207ULL, 
            0xED434FD3D380F9D9ULL, 0x06CF63E2BF162C19ULL, 0x51D685B0A79FBE33ULL, 0x04A23BB192424B14ULL, 
            0xAE1E2616EA31DBF0ULL, 0x0718557DC5985275ULL, 0x77AD71F4DE0AF58AULL, 0xDD3673B45E33D87DULL, 
            0x4C13A920F2043D4DULL, 0x47AC9682E1384171ULL, 0xB88B1F48950D9E37ULL, 0x71B96D7895885733ULL, 
            0xEB036DE058838FB1ULL, 0x9B54D2E503BC4919ULL, 0x27BA9671528AE6B8ULL, 0xE6872599E9B7D68FULL, 
            0x35EBE37146883902ULL, 0xEDE1DBEDFC1D676FULL, 0x8008034F5457F9CEULL, 0xFFAAE141864D9F6DULL, 
            0x39B3CD8250EB869EULL, 0x94C5A01D8375DD8EULL, 0xD180C03B8C963431ULL, 0x1CE072A02FA06F61ULL
        },
        {
            0x1FCC36D42BD78A32ULL, 0x58950FAFE00DF217ULL, 0xC7798E26989981C2ULL, 0x0F45A6BC0CF55DE1ULL, 
            0xCFD57F90F4C9B905ULL, 0x2652102FAD8B88C4ULL, 0x5144F6BBFBA7B907ULL, 0x353187500A348085ULL, 
            0xF66905E4737F55EFULL, 0x914BBAF22DBF992CULL, 0xB7B4FFFF4671BAA9ULL, 0xD059F77D9C222069ULL, 
            0x2312B74D5E9B338EULL, 0x87DC2319F32D4648ULL, 0x79E110C03140036CULL, 0xB8A6273237F41951ULL, 
            0x10155F558E310135ULL, 0x2A6609B0625E576DULL, 0x9E9DFB46404D1BA7ULL, 0x0D598E5D54A8C770ULL, 
            0x9CF8CF5C3C775EB0ULL, 0xF379DBCF9AAF853BULL, 0x67408D73DEE9D01CULL, 0xBC8EC4C77DB722D2ULL, 
            0xD7D4E1A6299F59FBULL, 0x859C75BABF961B24ULL, 0x14D08FB141F19CF2ULL, 0x35A17EF56413BDE1ULL, 
            0xB5F3410449C285F9ULL, 0x9F5323DBCACEEEDFULL, 0xF22531E67F1B7B62ULL, 0xB7CDCF6ACF320060ULL
        },
        {
            0xB7678CC562F3E126ULL, 0xB5C14994FC61A45AULL, 0x060451E08809F171ULL, 0x6AD9D2D745C03A3EULL, 
            0xA20C25B9231ECAB5ULL, 0x4F06C58C7BA0E585ULL, 0xEE417A9A301A597BULL, 0x5C8070888189E907ULL, 
            0x5B8AB68769737D74ULL, 0xE254F8209178C17FULL, 0x939D67DE88D9EC86ULL, 0x4ACB9B557A5B4086ULL, 
            0x7F35E1B4BECC9524ULL, 0x143906651B13DE42ULL, 0xDEBFC06FE518E130ULL, 0x366BB84A376A964BULL, 
            0x5575966C6D46884BULL, 0xB976651B05F4838FULL, 0xF8C2CDBCF76925C2ULL, 0x1FE709690001AAD5ULL, 
            0x2B0DD1845CACCC96ULL, 0xD242C6E8D55EE27DULL, 0x3D274632ADE8C843ULL, 0x24D017D265C9F878ULL, 
            0x98C8C720D5475FC7ULL, 0xBFB3D8F9D14F5D7EULL, 0xA2A50064581C584CULL, 0xE0E24AEFDC9C75E4ULL, 
            0x3442C48FA1BE3BA0ULL, 0xFB1A5D7DD75E8AE2ULL, 0xED4C66841AECAE67ULL, 0x1CF765901A1292EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseFConstants = {
    0xB7E7728F3D80C618ULL,
    0x58FA6CADDABADA05ULL,
    0x7F9403CD17DD0CCCULL,
    0xB7E7728F3D80C618ULL,
    0x58FA6CADDABADA05ULL,
    0x7F9403CD17DD0CCCULL,
    0xE91EB20303F2B0DEULL,
    0x539E979B9250C98EULL,
    0x28,
    0x68,
    0xAB,
    0x32,
    0xCE,
    0x6E,
    0xA0,
    0x62
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseGSalts = {
    {
        {
            0xAC58B00D596C02FEULL, 0x88D113B3F4705EC8ULL, 0xB94F37D9086CF9DEULL, 0x33B7091B38B0BB79ULL, 
            0x40C3F66EF318C488ULL, 0xEA7B3B253EBD719DULL, 0xAE642A3D51CCD1D9ULL, 0x22C5F62730F8BFADULL, 
            0x42FE47FB3D976B5EULL, 0x7F382A497954DBBEULL, 0xCC9FEFEE6B617060ULL, 0x0022E70D010D4615ULL, 
            0x2F7824555072839AULL, 0x253E927E413366CBULL, 0x16D5C0226B43BBDFULL, 0x77DCBB8FF5433604ULL, 
            0xC640D44A166DB530ULL, 0x872761B68D5AF583ULL, 0xD9E9BC541EDAE150ULL, 0x6A454A0317C15222ULL, 
            0xFBB0666228F43631ULL, 0x14A02EED37ACFEEAULL, 0x5ECBAFD16AFD45C1ULL, 0x094654A0F64DD997ULL, 
            0xD4E9841C5D7CE689ULL, 0x431C117B1EF741EAULL, 0x1D645EAA47E1E283ULL, 0xDA263C27E825E091ULL, 
            0x8EEAB35F03A560C1ULL, 0x41B5D4C09479DB0CULL, 0x2E1DCF537F0685B0ULL, 0x30C7AB898DC8078EULL
        },
        {
            0x6C1CEAF729BF2D85ULL, 0xA3167F84DD891B7EULL, 0x93F1D49F96654189ULL, 0xD498984C87C37D08ULL, 
            0x01B4FB3E923842E7ULL, 0xB9ABD7F7BB4A51A0ULL, 0x1E78B8F307E935F5ULL, 0x3EE88DEA20DD90B4ULL, 
            0xD9DBC1A97DD56B71ULL, 0x9BBECE5A12B20F43ULL, 0x0CF1A9424083C65BULL, 0xB97DD6B66BE26664ULL, 
            0x48E18EDDDAC681F4ULL, 0x3FE6BF7447F8E356ULL, 0xC20FCE9E38833F06ULL, 0x476BAC5C57DA236FULL, 
            0x37A48162B63A12E9ULL, 0xEB52B8348664BD2FULL, 0xFA40F63998C77C3EULL, 0xD87BCAD3AF8F1AE6ULL, 
            0x1583BF0AA09F7B82ULL, 0xD1A698C0E9896B68ULL, 0x3B09994C8448942AULL, 0xB81BD8832232DA73ULL, 
            0xEFF936844DF46732ULL, 0xDEA7723DE13D128AULL, 0x377C9260B9689777ULL, 0x0EBEE443612269C2ULL, 
            0xB638E30C07B1FC7FULL, 0xB6D3A004AC18597AULL, 0xD63DB89472283B7BULL, 0x46EE2B726266B3A6ULL
        },
        {
            0x04D7082716650DF8ULL, 0x45E7E1F26BB0C9FFULL, 0xD1D4475CBB78A7C3ULL, 0x9D19A42F9F251043ULL, 
            0x02A7B56381DB3FD4ULL, 0x3477F49C108F163EULL, 0xA7AF5A385BB0FE00ULL, 0x8ED2052EE19D9861ULL, 
            0x891D4BB65660FCE2ULL, 0x1F1C4CC1CF13FA07ULL, 0xB63A31D483D8FE97ULL, 0xF1C4EF06A743D58BULL, 
            0x7E32B0622C28FE5BULL, 0xB8DEEA6E72916BEEULL, 0x8558AA183735209EULL, 0x2DD03746A9A41138ULL, 
            0xD2CAFF2EBB3418C2ULL, 0x532758BACBB40906ULL, 0xDA60573D7A20707AULL, 0x498F0E22F6D3C9B0ULL, 
            0x2E52512EFBF28D42ULL, 0x45F51F584B33E0A6ULL, 0x741CB3A597291667ULL, 0xFDF79CB98E6A817BULL, 
            0x66BA143A1D934874ULL, 0x9D6CBA1307E89144ULL, 0x2F9DEEBB36B61DE5ULL, 0x34EE2C8A511D602BULL, 
            0xB798B64B05BDA8F1ULL, 0x77750EADC9750F66ULL, 0x2C929596EB62A41EULL, 0x1750E1DEF0F4BCBBULL
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
            0x6EC92DE225677442ULL, 0x24B73F7A9181DADAULL, 0xE063E0775ADCB9EDULL, 0x510E875C74ED757CULL, 
            0xFEB1B47012BD744CULL, 0xD3C0F384A5134DE8ULL, 0x11492E65268451D7ULL, 0x2E0583444BEF0897ULL, 
            0x0C5BD3DB61D32546ULL, 0xC7B0C8277E2D2B59ULL, 0xA0DE07ADF079FDCFULL, 0x490C0440AE3AD6E7ULL, 
            0x442DD21AB3E10B7EULL, 0x3068B24DE404397FULL, 0x2241EEA52D687A1CULL, 0xE12137F04177BA1BULL, 
            0x7DD4F117F245DB3BULL, 0xAB4FDCE216AA78DEULL, 0xF8DC552691A182EAULL, 0xABD242FA57069408ULL, 
            0x160EEFA25AFFF2EAULL, 0xBF082397D52547B4ULL, 0x747796023E40844EULL, 0x8C17EB157B731C43ULL, 
            0xDA2AA2C6F8475429ULL, 0x12E7B8E26863FDE8ULL, 0x1791B45AB05D0104ULL, 0x8A88952F7E25BD83ULL, 
            0x07E3ABFD2450AB45ULL, 0x24FB7B9A46803AACULL, 0x2A2ADC93F94BEE5BULL, 0xAA5C3806371D1858ULL
        },
        {
            0x5C3366D6C3272EC3ULL, 0x0343AFEF30C1A020ULL, 0xD23531B626526AF4ULL, 0x3FE0B3ADF9DF68B8ULL, 
            0x9A98CF4D099A97ECULL, 0xE9804A62038023C5ULL, 0x7E66151F345A95A3ULL, 0xFC41C1F89E61014FULL, 
            0x6CF8F1B0A516F7A4ULL, 0x2D4E88753D602960ULL, 0x473061FDC5427BC6ULL, 0x69AAE0BD03AB50F6ULL, 
            0xF4000ED128DB30DEULL, 0x5B8158ACB8758E6EULL, 0x51FE85EDBE3A88BAULL, 0x4F8B75CFC03701C0ULL, 
            0xD397AE67BF6BCB75ULL, 0xD74A1A9553AD4E25ULL, 0xB9C0E5E3A36A6B47ULL, 0xB2E4E0A59D88D5E8ULL, 
            0xB141FB56169DADBDULL, 0xE335A9D7C64EB163ULL, 0x5531F9301C3776C4ULL, 0xBADA4D2D79ACCB75ULL, 
            0x8732021ADB1040C4ULL, 0x490EC09DCF2A96FBULL, 0x7231EB1D8D0BE099ULL, 0x7B8FB4F4F2214A9FULL, 
            0xB5A4AE4CAE3AAA9FULL, 0x82352A17C5FB6E55ULL, 0x9733BF5DB784D914ULL, 0xA62DE0B69B575045ULL
        }
    },
    {
        {
            0x4D79F606A2AADAD7ULL, 0x80A9A83BB2315607ULL, 0x00E003528921105DULL, 0xFD1D3F127602DD12ULL, 
            0x1FC55E9CE3DB0B45ULL, 0x4252C327CEDC246EULL, 0x428FCAE567B61110ULL, 0x00FE41F534FBADD4ULL, 
            0x6DF41C14D7869216ULL, 0x943FAF50F4F91746ULL, 0x8534C7675057F365ULL, 0x20B80936C83F3ABFULL, 
            0x61686533632D627BULL, 0xDAE785E8E61A2C2BULL, 0xF0154DBA989C6550ULL, 0xF1E1CAF318CBF161ULL, 
            0xAFAB6A2CAD6358D9ULL, 0xA639A25E5F8F3D50ULL, 0xC2A2D790A7013CABULL, 0xCC26BBF28F24CD73ULL, 
            0xB571227FD0C0B035ULL, 0x16300FC286B90597ULL, 0x0F24C7589CDBDD95ULL, 0xDB0B1B39E747AD12ULL, 
            0xD7D3EFB972FA7554ULL, 0x8955D6CE3163A39BULL, 0x2FD18025A2C59901ULL, 0x87A55FAC51BEC300ULL, 
            0xC9C29D8E309716BEULL, 0xE7A69E294CF8AB0EULL, 0x783AB4DA3D8F345FULL, 0x69A60907877B15EAULL
        },
        {
            0x2714E9F378821322ULL, 0xEB1DD08E01CEA12AULL, 0x9506FF13DA2D9033ULL, 0xD80E6F7F9729591CULL, 
            0xEFE01BF6EB2802EBULL, 0xA1F481039A15B5A4ULL, 0xDBFCEE03840B2D00ULL, 0xE0937BE349916362ULL, 
            0xCBDC46859441DCA6ULL, 0x0879E77A4162CD2BULL, 0x85F09BBB148AC7DCULL, 0x4B9F60BF53BE6184ULL, 
            0xF4A5BBFB8EA8ADE6ULL, 0x717D21C4061599D8ULL, 0xC4EEF34689CB5B53ULL, 0xAB6B7244188906C4ULL, 
            0x05E3044234780F7DULL, 0x5F99166EA4FC728BULL, 0x3B2F1E89E5C76BA9ULL, 0xF5FD4D3B587DB242ULL, 
            0xF8D9CA620048DDA8ULL, 0x7604051D571F784EULL, 0x715998A655C80586ULL, 0x6B8333BB4F7CD186ULL, 
            0xD8F9A7817C9AF532ULL, 0x7820912F1D55152EULL, 0x68AE3C132180E8FFULL, 0xC39AE6BA571F9314ULL, 
            0xFC6CBA74E66B072CULL, 0xD09D02D0AE69A668ULL, 0x0787803370358CEBULL, 0xF61E9FEB375D652FULL
        },
        {
            0xAFA5DCD0A41529D9ULL, 0x738AA2BC79B39117ULL, 0x556B6C34F40EFA66ULL, 0x5CDC0C615981D325ULL, 
            0x9B7AFAC7465D32C8ULL, 0xBE3A22993AADA980ULL, 0xDCA5B4228B23655FULL, 0xF881EC7796DE1BE6ULL, 
            0x5E2F213FE4627E3EULL, 0xFD808E29C683230BULL, 0xAC364DBC67429F0DULL, 0x7A71DB5D25EF15BEULL, 
            0xB02D29EBA22848C1ULL, 0x73EC705784E4D41CULL, 0xBCD951159FA93044ULL, 0x86465DF1DF1CC323ULL, 
            0x005B093946BC2C76ULL, 0xBBF51A7AF0C4EF8BULL, 0x58633C2E8197542BULL, 0x34DE3E8C29647B18ULL, 
            0x05EF7C544E6866D0ULL, 0xC6DF0DE40D25F5A7ULL, 0x9BF147008B462B67ULL, 0x11E49B7594FDEF31ULL, 
            0x0CF91135A15239ABULL, 0x14D378E30F1F695CULL, 0x62987E05EC7950DBULL, 0xCBA21706762790BCULL, 
            0xEC54934889830CAFULL, 0x395E5EE7B531EC58ULL, 0x6B4BD0655E059834ULL, 0xAD1D6CDCD028C769ULL
        },
        {
            0xCA94CC48B26AECCCULL, 0x512B9874696FBAAEULL, 0x8104A0DB3FCFDDA5ULL, 0x6D87B0B02DB0BC19ULL, 
            0x2AD853333734E0C7ULL, 0x497EFBC5DD236161ULL, 0x5CEFEA9CD2F670D0ULL, 0xDBA8E782A6698874ULL, 
            0x1ECAC9D1E44D6485ULL, 0xF05A53EB60F4DBCEULL, 0x78F4221F2AA6428DULL, 0x0142D87841D66764ULL, 
            0x055877404B660B69ULL, 0x969F71DC98BCC333ULL, 0x0CBC9A43275B6518ULL, 0xCB403F2074B302CBULL, 
            0xB1DDBB3F0C846EB9ULL, 0x8BC35E36F08FE5CEULL, 0x3543F492F3AEBE58ULL, 0xDF5832942B4688AAULL, 
            0x13D17D050FF8D697ULL, 0x5B065C29D0305276ULL, 0x7B2498A2512CC9BCULL, 0x569A50E620A61EE0ULL, 
            0x4C92DB39D32D4446ULL, 0x1D95FBE9EA160439ULL, 0x54A5944E461D404CULL, 0xD5ADCF66D282861EULL, 
            0xDF2CE7C376C14ED2ULL, 0x436ABF3B08ACCC80ULL, 0x1450C0B6A0B4BF68ULL, 0x989E95A0ACE52A7AULL
        },
        {
            0x664E47A5B13D84E8ULL, 0xD92E9AEC42691A96ULL, 0xECF569F27E7FD930ULL, 0x91A18C4C8824D528ULL, 
            0x9D58F305EAE87B94ULL, 0x8736A09DF92639A3ULL, 0xF313014FBA0ECEAAULL, 0x949ED1627766534DULL, 
            0x0EBE9C1A5FCDA156ULL, 0x732458E86E6F6534ULL, 0xDB59C424AFC9BF79ULL, 0x7A0D01FF643139ABULL, 
            0xA92F3CD67389B860ULL, 0x1F79C5D32FB2F4B8ULL, 0x398856E40A28CFF7ULL, 0x2AAFD33A97E1FB94ULL, 
            0xD0848747C04FF036ULL, 0x029D05F9D5918022ULL, 0x30E8AF638513838FULL, 0x36736202AFEFC6B5ULL, 
            0xDA6ED2F279D2ED02ULL, 0xE56824F6995A97F1ULL, 0xF9FCC1951637FDB1ULL, 0xDD5F6F2054A64BE5ULL, 
            0x56909143E589DD20ULL, 0x9B7EB9F1A95409EAULL, 0x671AD385563BE99DULL, 0xD71374FBDB0077A3ULL, 
            0x67E62BA0D0783073ULL, 0x4B7C7F2832F11BC2ULL, 0x00033972D57AC452ULL, 0x142B838C7D2CBE29ULL
        },
        {
            0xF151F6A910CAA04FULL, 0x8727E21CE74688D2ULL, 0x2A4596080F4C2BF0ULL, 0x73E62D656A592418ULL, 
            0xEFFA07A597B8CDA4ULL, 0xAF814A082E88929DULL, 0x7CA44B129706AB6BULL, 0x4A6D620F88D1E969ULL, 
            0xEFAAEC6257B962CBULL, 0xBCF8469E08116D05ULL, 0x418633E86EF5AE70ULL, 0xD564526B1D417D43ULL, 
            0x7BABAD9E97EB113CULL, 0xDF1FE7EF059EB75EULL, 0xC97945EC6C3EA69FULL, 0x6D5CF96E1AFA065EULL, 
            0xF38E25E1B4791DBBULL, 0x620FB37F7AB07901ULL, 0x9345CD184303C954ULL, 0x9487498E268EE5DFULL, 
            0xCFA5EDA1B7EF549DULL, 0x0CC60AA42C59012BULL, 0x1A775CECD09FA17DULL, 0x0C250FBF0C54ED8AULL, 
            0x7D0E69AB1544923FULL, 0x1161B92338AF03FAULL, 0x0D0CF21DDA970E8DULL, 0xDC0A3238BEED7FDDULL, 
            0x16266E17F7040D13ULL, 0x48220D20A0F8315EULL, 0xBFC575F737DE2F45ULL, 0x6086914FD1204371ULL
        }
    },
    {
        {
            0x8D365EBE5FE63E02ULL, 0x6F490A02A8E7D35DULL, 0x368F7101855931EEULL, 0x03AEC4521A84F0D4ULL, 
            0x96967C61AC9B4E35ULL, 0xBDF5E0E0E5F9B674ULL, 0xCE73DCECDF20613DULL, 0xCE8179A8F31BDEE1ULL, 
            0x760A316F2381B7B9ULL, 0x3EE2D7EAF33D7EE6ULL, 0x85F932911AE8B3DCULL, 0x27A38727CACC9B4FULL, 
            0x5C0D34C006132682ULL, 0x2F04C7995F09CCBBULL, 0x2FFF39E9006B0608ULL, 0xA5594E18F68F9E72ULL, 
            0x75F79F2ADCC1221CULL, 0xE386A3637AAEB0FCULL, 0x52E17C415F7EC8A9ULL, 0xAADAA2211A3744DCULL, 
            0x488026F037ECAFA6ULL, 0xD7F47599EB546C3EULL, 0x781FE3B8C8F06C1FULL, 0x451334E69055A9DDULL, 
            0x0B1AF09DDD8EF9EEULL, 0x834F817AF8D6AA62ULL, 0x544D4253E835C88DULL, 0xCB56A8C7D85D9B90ULL, 
            0x951BFA0F289E3EC8ULL, 0xF2F6F392889E90DCULL, 0x4B2C5A2DAF4D6F96ULL, 0x1ECC20CF4679B617ULL
        },
        {
            0xEC8AEEDD98D1B344ULL, 0xC0D44CCF61AD2531ULL, 0x45E94B451413777AULL, 0x9F99127AB5D2FBC6ULL, 
            0xD6639598EFE52389ULL, 0xE6E0F1739DAE16BCULL, 0x6EC095FACBD8CFEAULL, 0x49B2D91A43596D9BULL, 
            0xC7ED5B00789CF96CULL, 0xA5E485AA4E912F8FULL, 0xB5367908FCE4FE39ULL, 0x8CA29A99F69016D8ULL, 
            0xBCD168D030D598D8ULL, 0x776E07DBD7DFE9F0ULL, 0x1046E229D3550BE2ULL, 0xDF5A1AA7A1877C76ULL, 
            0x0D199ED0C17FBC27ULL, 0xA64086A1CE1BA934ULL, 0x9A44DAC9EEF039F1ULL, 0x3202D379064D9740ULL, 
            0x5429ACCD5FC99B72ULL, 0xF12259F0826B3225ULL, 0x59E7A4465D3162B5ULL, 0xD93235151EE712A1ULL, 
            0x6093BD157140C1EDULL, 0xBB7F4593EA5499D6ULL, 0xCBFD1C2448C816E4ULL, 0x1A9B28D3B44A6C9FULL, 
            0x27D62449BAEBDCE1ULL, 0x56B2AB5AE14CEE7DULL, 0x69BB285EF4ED650CULL, 0x65FEF9C753FB5780ULL
        },
        {
            0x9FCFE80FFA6CAEA5ULL, 0x152A71CC44246380ULL, 0x5122CFC4A5E6756FULL, 0xD2D41293C57BE536ULL, 
            0x6C756A272D5AAFB1ULL, 0x4D8AFF486DD3E1A1ULL, 0x4C278A367EA8926CULL, 0x13806CCD545643F3ULL, 
            0x89BF1EDE2539CA7CULL, 0xFDA1E9659D3BD70AULL, 0x631F4FDD5F6E5E70ULL, 0xD0687D450C8ACFA2ULL, 
            0x20D60760C10037B1ULL, 0x8C59134136EC65D8ULL, 0x7BBDB20F29BA9103ULL, 0x72323AC88E2D84A0ULL, 
            0x5E6E0ED488E94143ULL, 0x2052AB4FDE3DCA97ULL, 0x79558D0ABDFFFD1AULL, 0x9741132A3A53D20CULL, 
            0xC08E383E15DFC9DFULL, 0x34D6C43CCC7F8838ULL, 0x216B24743FF1BD03ULL, 0xF0A04DF8A3AB9C84ULL, 
            0xDB782EE2E0ABE306ULL, 0x502B4B8D51425218ULL, 0x6CC97E71D56235CDULL, 0xEF3BD78CF17CC7E3ULL, 
            0x1FC1071DF9887962ULL, 0xA9DB33D70760E27BULL, 0x6FA2FFCB30BC3651ULL, 0x8C93D56A1C06F726ULL
        },
        {
            0x43E54CCF090D52E6ULL, 0xA50D3CCC66E4874BULL, 0x5EDD5C0F3B711D0EULL, 0x51F76CA010FFEDA0ULL, 
            0x56E95A6693524200ULL, 0xE793CA1E8F29375DULL, 0x0576581FAFD880D3ULL, 0x4AF9EDABEE6B6FE3ULL, 
            0xCB4A31DFDE192379ULL, 0xEA24D3FBFE3083A9ULL, 0x69C9EA5C3DCDCF86ULL, 0x14F83C82F470BF42ULL, 
            0xE53C07A4C0A52C65ULL, 0x73FB173DC58538ECULL, 0x8E085F708C40DE48ULL, 0x70EB4961783D79DBULL, 
            0x11D112805248AD59ULL, 0xC80AC58D6DF82231ULL, 0xB0A6118364890EE2ULL, 0x47250975F5939FA5ULL, 
            0xCC1B6D02FF73886CULL, 0x7808241DE08EC393ULL, 0xEC3ED59F95CA503AULL, 0x61746A26A305B262ULL, 
            0x0BA89BA5D13F4B25ULL, 0xC6A2AAD12F7EA922ULL, 0xBF941E5029932865ULL, 0x1EFC0F91317FB208ULL, 
            0xC48E92C896EFD330ULL, 0x9530FEAFA0FD7702ULL, 0xFA8EEBCF7C8F0415ULL, 0x66F2D621E81817B3ULL
        },
        {
            0xD0556CE06D355850ULL, 0x26D342EED23F6E81ULL, 0x9EA7615E7ADC9AEFULL, 0x0375F047BD87D0CAULL, 
            0x746BD0FBB2E6A38FULL, 0x644181D061B5105CULL, 0xB0BE2F294B665469ULL, 0x1765089603E17E22ULL, 
            0x1BC07799B5F1DEBDULL, 0x43B80C82BC8B17C2ULL, 0xE274CD71A0216309ULL, 0x05C0C16B120BBC85ULL, 
            0x54705318827C4AFCULL, 0xBCB5BDF3BB9E53A3ULL, 0x5062A6FB69688383ULL, 0x3D99153F58AD9150ULL, 
            0xBE23E2E0E0E784CBULL, 0x4765C3A1889A8DC2ULL, 0x3FCD355A8C2B4B07ULL, 0x64BCC6218B800239ULL, 
            0x8DEA553B75CB7393ULL, 0x4B79C965E2800AC4ULL, 0x83B92E21545D32A3ULL, 0xCBB2B7F73C026124ULL, 
            0x3AA2FE73A8BE963EULL, 0xABF8875E95EB6B26ULL, 0x91AF3C9DADA28490ULL, 0x038936FCDE86BBB8ULL, 
            0x776DB24398AF817AULL, 0xD0AB8F318A74FC65ULL, 0xE9732DD83184E47CULL, 0x50A91E069B86A225ULL
        },
        {
            0x9A98A9111FE07FD4ULL, 0x5ABF5304F77E30C5ULL, 0x674894CFE0CC070CULL, 0x5800D33899AA2BF1ULL, 
            0xBE89104A185A0965ULL, 0xA0FAF49780018B22ULL, 0x5F2650A7605B0AE5ULL, 0xB32DEF05A57511FCULL, 
            0x7D5840FB16BB52E0ULL, 0x25D0D1F1858547C1ULL, 0x295089FD79DAFF21ULL, 0x31E945863BF80D66ULL, 
            0xA12EFD707CEBBEDFULL, 0x1D7F6F453F1326D6ULL, 0xEF43ECF1551B3CEBULL, 0xECC2DE2019A67C87ULL, 
            0x2F92DBF6051FD68EULL, 0xF49D0FC3A3AA866AULL, 0x0DA617525D089B6EULL, 0x1D9203DFEE952CD5ULL, 
            0x3E27498EBDC53C4CULL, 0x297E3F944C0BDBB5ULL, 0x5726DF7199BCCA68ULL, 0xAC16B63115F341CCULL, 
            0xDE44B56D7511178EULL, 0x25C92D233C6F1202ULL, 0xFA914F4843B60288ULL, 0x33A8C77709D9E475ULL, 
            0x3AD05ABD15710381ULL, 0x10B555C983199806ULL, 0xC2049A9F1D47F480ULL, 0x31BDDFFA951D8F72ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseGConstants = {
    0x1F28F906101A9664ULL,
    0xAB06706C34761A60ULL,
    0x9587D5E686AB977CULL,
    0x1F28F906101A9664ULL,
    0xAB06706C34761A60ULL,
    0x9587D5E686AB977CULL,
    0xB31A425B4B46C2DBULL,
    0x399661FCF4910BF7ULL,
    0xD7,
    0x88,
    0xD8,
    0xBD,
    0x88,
    0xB1,
    0x6D,
    0xD8
};

const TwistDomainSaltSet TwistExpander_Alioth::kPhaseHSalts = {
    {
        {
            0x93121AF2C078D304ULL, 0x435AA1E9DF431665ULL, 0x8D3E722EA8FAD796ULL, 0xC6198C5FD7D94FA5ULL, 
            0x1A30C3534E433500ULL, 0x9C02A3B84FF455C5ULL, 0xE4A36E3F257B43C6ULL, 0xC260E9676BF33389ULL, 
            0xEDA6CD3BB1CDDA38ULL, 0x4C6248004F10A750ULL, 0xF8AB1A3D152D6F15ULL, 0x9074F644A18105E1ULL, 
            0x02560D0E9F51A499ULL, 0x438543379E399349ULL, 0xEC325A2D995341A2ULL, 0xDF630345615122C3ULL, 
            0x95D2F61FA4920F44ULL, 0x6EB1DE6E806B475FULL, 0x32C775AB55BEEC06ULL, 0x939EDF7DEF18E899ULL, 
            0xDEEDCDEEA8DCE2CEULL, 0x4C9A641ED8D0E986ULL, 0xB72E964775447EF0ULL, 0xE07CE710D61F5DF7ULL, 
            0xB2F33CC20381CDD1ULL, 0xD8DACACD9365DAACULL, 0xD00C7220B2338A4DULL, 0x7F0CD30EA22CF050ULL, 
            0xC3D8FC08FDCF1CDEULL, 0x394D3B04A538BA97ULL, 0x1646AC6DAA543339ULL, 0x6110F71306E1A7EAULL
        },
        {
            0x046D24CE11DC1E77ULL, 0x93DD68D0F73E1DA6ULL, 0x36F494BDB5C262F8ULL, 0xD53CEB432D79FC94ULL, 
            0x2C3015D60AAC1809ULL, 0xFCA581C5E1F3B989ULL, 0xD9329C9BFEB903A9ULL, 0x9025CB782031AC00ULL, 
            0x1308A3E51FB911D8ULL, 0x2AF9B756F77E89EAULL, 0x3BF1C27A9518C595ULL, 0xC56636B08FF30B65ULL, 
            0x5DA425C7AADEE5B0ULL, 0x57B9C064771AC21BULL, 0xF846FCBEB4C8E0E5ULL, 0x50BC5CCB5E706CE8ULL, 
            0xB4A93B126980F174ULL, 0x26F34EDFE28CFF03ULL, 0x45A437C0120385ADULL, 0xF2DAB75F1525315CULL, 
            0x4526CB59B2596E86ULL, 0x9501F8190746CCF7ULL, 0x05EF6AF3F56912D0ULL, 0xFFD4334B32474E18ULL, 
            0x49D1DBA3422F833BULL, 0x28EF233C7A13B790ULL, 0xE0B8302F007A3C3BULL, 0x00FD4673A3382391ULL, 
            0xE89DD12C21690898ULL, 0x578219A98D3E542EULL, 0x57977C5A0E197A90ULL, 0x4E8952C7889C78BFULL
        },
        {
            0xC6695893370EA7BCULL, 0xF9E382F42EF01061ULL, 0xC3C3B50C983075F4ULL, 0x64129517AFE92BA1ULL, 
            0x7C548D7F0B4750CDULL, 0x2FAF608964CDEFD7ULL, 0x2F33DF58580D2CDFULL, 0xEC1F656512F118E7ULL, 
            0xF45860B8D6520EF9ULL, 0x52C27C408D37CE15ULL, 0x4071A89F9B36CB25ULL, 0x22764A5518081E09ULL, 
            0x3C6A7311215BCFD9ULL, 0xC6B8906D10E7C73AULL, 0xF08F0664803C7A82ULL, 0xC2C22C37DAB4DA39ULL, 
            0xC469AB8437234EEAULL, 0xF47DEF026C83B960ULL, 0xCF0A2505382E33A6ULL, 0x3F16EC5153008A66ULL, 
            0xE7AD0E850F34C825ULL, 0x510CC48051D2E674ULL, 0xC9710D6E61EB42A9ULL, 0x8765D117B156AAF5ULL, 
            0xFA533436AEA25415ULL, 0x68B7F7191689374BULL, 0x614C1522ADC60D38ULL, 0x44084D1DEAA699AAULL, 
            0x1DC9E7F41A2FA001ULL, 0xC0B9927B15141A6EULL, 0xD5CEE7FCAD5E3B1DULL, 0xC365438FCBB50223ULL
        },
        {
            0x200095A68BC94362ULL, 0x579A8EA1B060A59BULL, 0x10B448F461767274ULL, 0xCDC3BA48A1B613E2ULL, 
            0x22E8A60D03E5F58CULL, 0xF3DDA527D7D8017FULL, 0x5915060512535A00ULL, 0x328C93EADFF50E70ULL, 
            0xBB8594B2DA5B4CAFULL, 0x0CEE1F2A31CC52DAULL, 0x35045EB354913420ULL, 0xB08DBF4BA6B9C278ULL, 
            0x5A118D3403A2A488ULL, 0x0838C57CEB219079ULL, 0xC68606B425B0A8AFULL, 0x4FB7B2CA953A68FEULL, 
            0x2E3326DD217EA7AEULL, 0x061BCFBBD6690D69ULL, 0x30FDFC14D9BAC0D9ULL, 0x31C567845D9BB3DFULL, 
            0xA30D95872CC46F1BULL, 0x9A77EACB0571E3BFULL, 0x9F1DCEF5E80D1E01ULL, 0xB0168A607BF7A917ULL, 
            0x5804FC333BB3AF40ULL, 0x2A2E07E7A8430477ULL, 0xE161BA133453EA58ULL, 0x7B88BDD11ED9316FULL, 
            0x05DA2F61F71CA912ULL, 0x4DB6DDE3FC2F8C79ULL, 0x3538FC5AC42A965FULL, 0x8FEA299D4CD5BFC0ULL
        },
        {
            0x3CAAF270358B74A5ULL, 0xFA8E9D594C05C57DULL, 0x493A6E4154C47F52ULL, 0x0F3A7B67822D3DA0ULL, 
            0x7FE3EA7DAE484D3EULL, 0x46A3AC87A77C5145ULL, 0x4EB8A0E7EE926ECAULL, 0x7C6AD80AA93CFAC0ULL, 
            0x559FC385B2486463ULL, 0xEFF336D973AFF642ULL, 0x684D55AFA96D10F1ULL, 0x4D0C0D4C40509B9CULL, 
            0xD0B999D7BD95B20DULL, 0xC3B279BD3EA547D8ULL, 0x02E0F304B6ED8A01ULL, 0xCFD6F9F3C44DB92AULL, 
            0xDA2C99D5392F436DULL, 0xC8CAFB5766E1B9B0ULL, 0xBA30EC941FCF001CULL, 0x9E422F217170E3A8ULL, 
            0x4C670C7F146CA2FAULL, 0xD6D8398FC0A6651AULL, 0x126C7051B64F34D7ULL, 0x4777F3571E279C45ULL, 
            0x2ABFA212150A2E53ULL, 0x266C92ECCB639BEEULL, 0x23956E738188E364ULL, 0x372AE0C1E4DB17DAULL, 
            0xBF14EAF110B15742ULL, 0x4964CF9226EB4878ULL, 0xF4CBEF643D5E2338ULL, 0x7835FC5556BBE39CULL
        },
        {
            0x4C48F0C0F488CA50ULL, 0xF9DFF62BCBACF411ULL, 0x0BEFBBABC7B8B4C2ULL, 0xA69B2C9304D17B4FULL, 
            0x1867455D6E833260ULL, 0x265D8C5D1AD8EC54ULL, 0xA5BE57199D4B8D1EULL, 0xDB631C8423D03FF2ULL, 
            0x540D7A57355ED819ULL, 0x6F2F506AB4FDE058ULL, 0x2AEF28AEB4BD7EB2ULL, 0x2BE3B345F43D31ACULL, 
            0x50581D5E6511B263ULL, 0x70913DAE04F9C357ULL, 0x916905E2DC9B29ADULL, 0xC271848BB5357A62ULL, 
            0x12530B6FADA9354DULL, 0xD5FBB14682FB1073ULL, 0xB59FF5F2B2406FC2ULL, 0xBD0A8CD506B5F216ULL, 
            0x66F4FB04E8AC22E5ULL, 0x8F4EA99B794996FEULL, 0x0A1D74EFA2F31D10ULL, 0xA0F7C62DA1B2E4DEULL, 
            0x34E568C2D020ABA4ULL, 0x147378EA7A8CC66DULL, 0x5A52D33880B6E535ULL, 0x3889216BFF3F29F4ULL, 
            0x44E86BE99F4E0CE7ULL, 0x7F1F7AA32636E73EULL, 0xFD1A054003A598B0ULL, 0x4A3850A81F4E6464ULL
        }
    },
    {
        {
            0xB1D0E9480F021D18ULL, 0xADCE9ED3233FDEFEULL, 0x511E48783B957857ULL, 0x63CBB7A5B768A45FULL, 
            0x1F95CE0D9029D870ULL, 0x048956EE55808AAAULL, 0xE15B63C033B66CE2ULL, 0x7A4064AB22FBCE20ULL, 
            0x9ED4CF1E5D6E0488ULL, 0x38C05A51A466F365ULL, 0x1F1870E35E047918ULL, 0xEE74C9BF0B2BB946ULL, 
            0xFAFA0D02586940C4ULL, 0x579AAF31BF019EC1ULL, 0x808BAC4BC5BCADD5ULL, 0xB30B24B652FA52A3ULL, 
            0xF1947935DECB9D1FULL, 0xC27F3E764442000BULL, 0x3499B417F98CA67FULL, 0x2A4BD58ECAC86E54ULL, 
            0x65B1E4DA3EA26217ULL, 0xFEC829821E1E7971ULL, 0xB8D91E64178F7213ULL, 0xCE64EA71BB81E3A1ULL, 
            0x54068F619851AA80ULL, 0xD78CA3AECFA9D977ULL, 0x648FC22513A6FA64ULL, 0xB6022056CB105612ULL, 
            0x929E442EF2656657ULL, 0x1F661ECA8BFB41BCULL, 0x7DC3077B058AD0F5ULL, 0x37520223BD174427ULL
        },
        {
            0x1013D9CE242AEA54ULL, 0xEE69985B4BF081C5ULL, 0x19ED2242DA5269B7ULL, 0x1242F9D63218C65FULL, 
            0x6542855DE925E3D0ULL, 0x28AF9D2A06201FEDULL, 0xB0A086792F389196ULL, 0xF2B3237FE6CC4A04ULL, 
            0x2FB61BCE5642208DULL, 0xCA24306E70DD94B5ULL, 0xC8F6D7EA2CAEFA78ULL, 0x5BC4435F540BEC30ULL, 
            0xBF6B5E5C7FE87A3AULL, 0xA082582B1CB64EE9ULL, 0xA2A93EA0BE6A42BAULL, 0x40E8DFD67F1ADF86ULL, 
            0x03AADF15BA4EA83AULL, 0x0923D3CB17EE9C15ULL, 0x954F0C26A7500EC0ULL, 0x27CC3058CB48F607ULL, 
            0xAB2A709A37B7F1F9ULL, 0x874C74E6FCF8C28EULL, 0x2E3F23B0D08198EBULL, 0x4CBD2484134D712BULL, 
            0x7608EC2C3FDD5F14ULL, 0xA2A8A9B5BD7FE55FULL, 0x61CE9EED04FC66B9ULL, 0x27FDAAF624D12B2CULL, 
            0x02596F265B1D27C5ULL, 0x1870A1D260B68929ULL, 0x4830ADE9125BDB46ULL, 0xCE26CF07374E0682ULL
        },
        {
            0xEAA0324865131B39ULL, 0x5225AEB575C65352ULL, 0x54EA96A60C50E69CULL, 0xB4C7EDE5A149B411ULL, 
            0x67BFF3338C950F94ULL, 0x873C29C86985C839ULL, 0xBE3E9D24507C8BB6ULL, 0x506B9CB768AB757EULL, 
            0x72F8B4A30007CA8FULL, 0x974F77F21849558EULL, 0x2A952995ECE9C3F4ULL, 0x376F1E1556F06E6BULL, 
            0xFA95D18E84CCE869ULL, 0xF87D991E943BC810ULL, 0xFCAB12F914DE9C18ULL, 0xE76C401016E2AFA9ULL, 
            0x6BC3E37DC0EA599CULL, 0x3035068E24FBE92BULL, 0x8AC2F87D11FDD56FULL, 0x4CD2AF2DF51A02D5ULL, 
            0x0E00C9F9C08A1CB7ULL, 0xA741874DB1FCFD7CULL, 0x7C2D770CADA09E08ULL, 0x5A826D16F55BA34BULL, 
            0x8AFBBADE2480AB70ULL, 0xD2883D5D39D28B02ULL, 0x8DF8A1E6DEE1A048ULL, 0xC4880756F0DA18EFULL, 
            0xD042A89AEB949305ULL, 0x3DC2C567DDD6954AULL, 0xA6C89F46D502CB16ULL, 0xE8759C568AFBB688ULL
        },
        {
            0x1C56FFEA08F8DE9DULL, 0x8340C884D513A2D0ULL, 0x0BF5AB680C2F3490ULL, 0xBD5549426E22CA07ULL, 
            0x45065961A0ED884AULL, 0xAA2154E9CFB9B1B5ULL, 0x7DA9AF2B67D97A24ULL, 0x7349F9EBB66B113EULL, 
            0x49554BB82D9294D6ULL, 0x2D18EFBDE3E1E9ABULL, 0xA2B2D9AC4888FDF0ULL, 0xA8A9FF7E6C03677BULL, 
            0x8EA89506CF9F57E4ULL, 0x49255159572DAA55ULL, 0x746E4674B51858D8ULL, 0xDF092E81B79ACED6ULL, 
            0x28C298D42A53A7C8ULL, 0xF4B231A0E2BFB6ABULL, 0x1435DBD8D0AFD937ULL, 0x88AAE3B05226D002ULL, 
            0x6CD531E13B3A337DULL, 0xADC2B79B1782CA6CULL, 0xF801EBAA116E739AULL, 0x71CDD87D974A8F7BULL, 
            0x8614800938A44145ULL, 0xA34178EC132FEEE6ULL, 0x7AA18FD2FD00A4CDULL, 0x55F40EEEF7599C9DULL, 
            0xB35CE949439E8531ULL, 0x19D2934FF2665106ULL, 0xC2820650EAAA653BULL, 0x5F3DCF67CC765146ULL
        },
        {
            0xBD4CEBCF33D45DD3ULL, 0x0A437BDBD1FD2561ULL, 0x2B556EA14735449FULL, 0x45B847F879C6286DULL, 
            0x0D63A40CE8CD8878ULL, 0xAD1D31FE34E9C161ULL, 0x7BE965E459567B11ULL, 0x7159B0102FA79BA6ULL, 
            0x4259ED8CBC63BF97ULL, 0xA7AC31B66D4BF371ULL, 0xE4936FD59CB5CB69ULL, 0xFA09E6C8589393D2ULL, 
            0x3C258B4FC5CFEA9BULL, 0xE30DFACD8F8BD054ULL, 0xAE7668D49E5267A8ULL, 0x15D47F044AEF2600ULL, 
            0x6E85491106FD7E88ULL, 0x2689EC366DA3568DULL, 0x1AA4DAFCB66D428CULL, 0xB217A34EBD2D060AULL, 
            0xA2C5DFFC07B1E9FDULL, 0xEE64419095BA150DULL, 0xF6D2023F74A96287ULL, 0x3E321F053AE2F923ULL, 
            0x9573327B02316485ULL, 0x89682B698A49E3FCULL, 0xB0A17E1F244038B7ULL, 0x844A8F77307D3ED3ULL, 
            0x83523F143AC8F9F8ULL, 0x9E4F96C503049A3BULL, 0x88F1F14F198E467AULL, 0x27D642BC4759768AULL
        },
        {
            0xF3A079D96139D4C1ULL, 0x793C720FB43539DBULL, 0x1ECEE544A8D7302BULL, 0xBBAB6096189EACE4ULL, 
            0x0B5392413253807EULL, 0xC939F069F50AEBCCULL, 0x7D2B5EC87E7D74B8ULL, 0x1BD5955498BB0960ULL, 
            0x4AB13B4088C61B71ULL, 0x6B663848E04B42F5ULL, 0x2C769764FFA5B9C0ULL, 0x4D84873CFCC10388ULL, 
            0x01A2545DB5F2719CULL, 0x35D5FD8AD966DDC5ULL, 0xD79233A4CF67CED5ULL, 0x58C08F0ABAC7E3A3ULL, 
            0xAFEEFCEC12532A4AULL, 0x987AAD1B4E8EE5AEULL, 0xB6EEE6700D47903BULL, 0x32FE7152E68BCDC9ULL, 
            0x69C0CF52E643163AULL, 0x2B2D811181A98B94ULL, 0xDF437B73FC438326ULL, 0xFB5289EC26A3C2C1ULL, 
            0x51DE6601FE13FEACULL, 0x5EB67A23884B96BEULL, 0xF9A67439D477ED63ULL, 0x43848B51E79EF271ULL, 
            0xC18E26974D606D56ULL, 0x5025A121E1F4AA64ULL, 0x5E77EAE45AE70F0FULL, 0x98ADF5B57BE72B6EULL
        }
    },
    {
        {
            0xD10CB84C5F183F28ULL, 0x6655AEB85253FAA6ULL, 0xC6323D5F00A8A015ULL, 0x8D34AFE275E2DD74ULL, 
            0x787004F0DDFA1332ULL, 0xB03F70E0B09F6FB8ULL, 0xF39DB7FD1054A3EDULL, 0xCE4B98CBD26596A5ULL, 
            0x533E7F7CEB29FC5DULL, 0x83EFE5E01839C17FULL, 0xD471241AB02587A5ULL, 0x55DDCAC959B535C5ULL, 
            0xB203586A25D4866CULL, 0x47FCDCD21C548921ULL, 0xF62BBAC8B7D5BD5FULL, 0xE1BF8A9615020BBBULL, 
            0x310368AB460552B2ULL, 0xA4FAE7E32A72045AULL, 0x6659B7D31B9DA28EULL, 0xF3D8ACDC5E198EFDULL, 
            0x380687B54E83607EULL, 0x1600D0E72364FE24ULL, 0xE86D1F209D9AC6D3ULL, 0x5064109BE577F4BFULL, 
            0x4895EB32EF8665D7ULL, 0x4D9233EEFB589814ULL, 0xEFD0C2717A143C1FULL, 0xA6A8318BC93A0810ULL, 
            0x1731AFCAFA29EF68ULL, 0xA8B9F1AEF3345ABEULL, 0xE324D3C845F2B2EEULL, 0xC22CD93C1C0D9AF4ULL
        },
        {
            0x6D7B617F5ED15A63ULL, 0x0620BF621169EDFBULL, 0x1C4D2590C909478FULL, 0xB9E3F938C9E68B98ULL, 
            0xB334CB32E8C98373ULL, 0x804BADC9699D0286ULL, 0xB1ACA4F7DA76568FULL, 0xDB1B2EA85291DD76ULL, 
            0x1BF23D38D2820A9BULL, 0x84F52122289E570EULL, 0xC9FFC9D84CD541C4ULL, 0x78F2967BB1DC22B4ULL, 
            0xDD26EDD7F84F641DULL, 0x194517BEBF51A907ULL, 0x0EBE03E561DDF855ULL, 0xEAD54A10BD5CB9E5ULL, 
            0x3AF72A8B95316319ULL, 0xBA5028B92CEF5ED4ULL, 0x9387D3A1253CFDDFULL, 0xF6A20DFE5A90EFC9ULL, 
            0x87D26EE62162A8A2ULL, 0xD809DB130C3AD415ULL, 0xD249A26B7C4EE38CULL, 0x1B2B1CBD5085D109ULL, 
            0x19B4676845AA62D5ULL, 0x054B2ECD817DCDEBULL, 0xA036FB3CB703AEB0ULL, 0xF6D8698BE5E3335FULL, 
            0x7F36179015C7C491ULL, 0xED5221F32504126EULL, 0xD4BA3AD3778FBAEDULL, 0x834D0ABE219C3FB8ULL
        },
        {
            0x49269A96D5BC34F0ULL, 0xA4C0AD51C9D25678ULL, 0x644522B4BC912545ULL, 0xCD441D06DE06727FULL, 
            0x56D8CC2E65D69486ULL, 0x509FAC061B52837EULL, 0xAE91735FE1F23143ULL, 0x0A9DF15845C2EDA5ULL, 
            0x3B501D06BB5EFF81ULL, 0x5219EA4B31B6775CULL, 0x255779488A06D636ULL, 0x976678AA44F9CC24ULL, 
            0x81B8492ADBEA873BULL, 0xEE824BA5E6E3D430ULL, 0x69BD68F12B33651AULL, 0x2E59A535BF61372CULL, 
            0xF514A591B21D606AULL, 0x69A2F0E62F4D7B3EULL, 0x1266153B8CCEFB43ULL, 0x82E3EF90E65564A3ULL, 
            0x93FDADB0F6F141FFULL, 0xC47D63A22D0B1E28ULL, 0xAA1BEC78D95775F7ULL, 0xE5A64C6F1F770CF3ULL, 
            0xE13D19DB719E48D9ULL, 0x7015867068ECB909ULL, 0xEE70A697CC397680ULL, 0x28D95DEB2BD68E9FULL, 
            0x685281C729127F9CULL, 0x0445C9593251957EULL, 0xEB5BD6F3D35A11D8ULL, 0xF14B1B90D5054928ULL
        },
        {
            0xC55D5197B6297052ULL, 0xF0B1A1F5670005C5ULL, 0x4AE8ED364D37CBECULL, 0xBE1D7547475C6C18ULL, 
            0x1715DACBA1B10C05ULL, 0x2A838AEA52BC2293ULL, 0x34E82465CFF31390ULL, 0x1EA731E8805F6B30ULL, 
            0x3F051D584AA39D72ULL, 0x4805F5AD1982F4C5ULL, 0xFB50D7108E429E1AULL, 0x9004D8A6603A92EFULL, 
            0xEF21572F9C950709ULL, 0xFA808FA974B9268BULL, 0x638E8BF417FBEF44ULL, 0xB575E315140FAB6EULL, 
            0x3BC2656C1BF91E9FULL, 0x8CCE61D9B62E4F60ULL, 0x18FE73D2C975003CULL, 0xD3236525BAD84D57ULL, 
            0x8893FE0C5012021CULL, 0x0002C2BE5136986AULL, 0xA8B2C46D4F728AE2ULL, 0xF600DFA9AADB3E0AULL, 
            0x52FAEB1B7A7B9D4AULL, 0x00B8D389B009478CULL, 0x13BDAB9405B770EBULL, 0xD3EB17AE1916D6FCULL, 
            0x6D4857F122535D46ULL, 0x2D71E61AC3093454ULL, 0x16B7907173042B81ULL, 0x6C782917FE3FC309ULL
        },
        {
            0x71B8A0ACAB3C43AFULL, 0x146DAAD6191E3D4BULL, 0x06D11D16D48B788AULL, 0xBE889C6E62C8F143ULL, 
            0x73003D60139863CCULL, 0xD96C56DF968BADD2ULL, 0xD162CB25F975C8E1ULL, 0x771E035397B5CB90ULL, 
            0x822EA0531B3E510FULL, 0xE6B22EC440226B7EULL, 0x77B694F34F5E0247ULL, 0x66EB44B8E7BA288CULL, 
            0xF5F5D4255CAC542CULL, 0x5199C7B4BA93D3C5ULL, 0x07A6062ABC9F129FULL, 0x01AD53C7FCA11526ULL, 
            0x332D00A0460BF650ULL, 0x4529B334EDC6EA89ULL, 0xC408A18DAC9C7CD3ULL, 0xBDB4426B90D3FF21ULL, 
            0x66B5A80E39390F91ULL, 0x225FCD788E3A556BULL, 0x06F2C90802CB5031ULL, 0xEABE32A2E900E7F7ULL, 
            0x486D242ABCBB0A34ULL, 0x5DC0DF9828B99424ULL, 0x2170552357D9ECD0ULL, 0xA46084F1DA21188CULL, 
            0x859D7368515A13E6ULL, 0x9247089C3C6B8348ULL, 0xF9FA0584933712A3ULL, 0x577DD4670EB51E46ULL
        },
        {
            0x30C53AFF03E52326ULL, 0x9DA03043E5234B43ULL, 0xD47680A133BFEE71ULL, 0x6E8D8B1DD5F6EAFCULL, 
            0x76261EB47F1C7A39ULL, 0xC7AA545E30BFE945ULL, 0x9469C2EFF8C85B96ULL, 0x3F0D3D70FCF08636ULL, 
            0x9F72EE5354F5B112ULL, 0x0C8ACA87D21ECCACULL, 0x001F53D2F6A8D6F2ULL, 0x7B41052C71F54A0BULL, 
            0x5615D714B4CF7198ULL, 0xAABF98E8D7EA2E0BULL, 0x4B52F36DBE2E17DAULL, 0x8C238E355A3DD336ULL, 
            0x965FA92DF114DB29ULL, 0xB4B1A6DC39B85DBAULL, 0x7F67C03DC042EA09ULL, 0x1E197A4B6298B9E0ULL, 
            0xEB13102ED190C798ULL, 0x568586776C7B5AC9ULL, 0xD54A828AE4BA1289ULL, 0xD9C41989C066A22BULL, 
            0x354012F13C2BB8C0ULL, 0xB89358A22AD95244ULL, 0x9AA7BEE59EA91155ULL, 0xC44A2E37D08978A6ULL, 
            0x1A4FB1C32F299A2DULL, 0xBB43D09C193159A5ULL, 0x5D4DAC535B9C18E5ULL, 0x877A3507D31F7834ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alioth::kPhaseHConstants = {
    0x00A26B8A2D595306ULL,
    0x4FC503A6EEFF26D5ULL,
    0xBAA122D299A1A1E1ULL,
    0x00A26B8A2D595306ULL,
    0x4FC503A6EEFF26D5ULL,
    0xBAA122D299A1A1E1ULL,
    0x1D9593FA72D42A5FULL,
    0xB8A5F638A3225A52ULL,
    0x7E,
    0xB8,
    0x41,
    0xCA,
    0x69,
    0x39,
    0xE3,
    0xEB
};

