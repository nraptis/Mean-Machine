#include "TwistExpander_Regulus.hpp"
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

TwistExpander_Regulus::TwistExpander_Regulus()
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

void TwistExpander_Regulus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC24CF82F5EB34CF5ULL; std::uint64_t aIngress = 0xAEAEE0A7841DBEEEULL; std::uint64_t aCarry = 0xE39877639F7A0D0CULL;

    std::uint64_t aWandererA = 0xA808F573EDA71CDBULL; std::uint64_t aWandererB = 0xBB9373E43E2BC5EEULL; std::uint64_t aWandererC = 0xB3EB24FE74B07B39ULL; std::uint64_t aWandererD = 0x98AAE5CD2214A4BBULL;
    std::uint64_t aWandererE = 0xAC8411EBE39984B6ULL; std::uint64_t aWandererF = 0x956756972FF67435ULL; std::uint64_t aWandererG = 0xD1361DBE08C08C57ULL; std::uint64_t aWandererH = 0x83F13B407065099AULL;
    std::uint64_t aWandererI = 0xAC2D6B52DA97F60FULL; std::uint64_t aWandererJ = 0xF98B66D9EBA69E38ULL; std::uint64_t aWandererK = 0xD1505005F7E276D4ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16767432130481355368U;
        aCarry = 11436204117099482411U;
        aWandererA = 17188941542513295052U;
        aWandererB = 10636461704792553587U;
        aWandererC = 11926703753295368394U;
        aWandererD = 11181830344823378222U;
        aWandererE = 9944825144209077050U;
        aWandererF = 11681482162326375476U;
        aWandererG = 9977886512957790316U;
        aWandererH = 9454059201440272219U;
        aWandererI = 17639859906906501119U;
        aWandererJ = 16335084889872895433U;
        aWandererK = 16738092078176374302U;
    TwistExpander_Regulus_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Regulus_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Regulus_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Regulus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Regulus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF583EB1E478C78B4ULL; std::uint64_t aIngress = 0xF3547CF6EC75FEFBULL; std::uint64_t aCarry = 0xA4BB3B05870C513DULL;

    std::uint64_t aWandererA = 0xCE3E63DC56AC5244ULL; std::uint64_t aWandererB = 0xB3975DAAAB1878C7ULL; std::uint64_t aWandererC = 0xB34308F7E1B83A70ULL; std::uint64_t aWandererD = 0xA5FD4405C6D7B632ULL;
    std::uint64_t aWandererE = 0xD4D0FE28A834169AULL; std::uint64_t aWandererF = 0xCBA1147FD94AF05AULL; std::uint64_t aWandererG = 0x8DDF1A8157CF2174ULL; std::uint64_t aWandererH = 0xC59D15C743A7631FULL;
    std::uint64_t aWandererI = 0xF1937343E0E5FCA6ULL; std::uint64_t aWandererJ = 0x88FAB3A0D46B5A54ULL; std::uint64_t aWandererK = 0xD8C5205291252755ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10632342675699420128U;
        aCarry = 18185078615938037999U;
        aWandererA = 10360550925193504925U;
        aWandererB = 9575140541935571571U;
        aWandererC = 12259121822610663404U;
        aWandererD = 10575660769924895354U;
        aWandererE = 15232844275380487516U;
        aWandererF = 12365304189421782598U;
        aWandererG = 15499700067250068758U;
        aWandererH = 9830589277657264325U;
        aWandererI = 13013019825428097790U;
        aWandererJ = 11503079519172304969U;
        aWandererK = 15393446035534883643U;
    TwistExpander_Regulus_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Regulus_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Regulus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Regulus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Regulus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8450AE80C94BF6D0ULL;
    std::uint64_t aIngress = 0xA66B137D525FDE36ULL;
    std::uint64_t aCarry = 0xDB5849156EDF130EULL;

    std::uint64_t aWandererA = 0xEFA61F9B1BA66343ULL;
    std::uint64_t aWandererB = 0xA5A0A545872B841CULL;
    std::uint64_t aWandererC = 0xBAAAF14E1B841E1FULL;
    std::uint64_t aWandererD = 0x9BCDCA80942890E4ULL;
    std::uint64_t aWandererE = 0xD2CC4AC87F4404A6ULL;
    std::uint64_t aWandererF = 0xAD387595E24C7E24ULL;
    std::uint64_t aWandererG = 0x826DC72741FB9E36ULL;
    std::uint64_t aWandererH = 0x8F055FE69EB1D440ULL;
    std::uint64_t aWandererI = 0xF7F671A3AA0124A0ULL;
    std::uint64_t aWandererJ = 0x800A3FD330FB4C6BULL;
    std::uint64_t aWandererK = 0xA63FFCD1E13D7F21ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
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
    TwistExpander_Regulus_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Regulus_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Regulus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Regulus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Regulus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 27 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 47375
void TwistExpander_Regulus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1569U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 129U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 952U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 849U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 531U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1317U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1565U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1597U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1680U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 56U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1954U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1743U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 793U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 205U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1256U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 681U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1104U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1355U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1963U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 306U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 803U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1389U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 594U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1073U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1885U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1625U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2018U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1273U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 445U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1966U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1206U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1515U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 218U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1125U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1578U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 912U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 364U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1491U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 624U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 138U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1591U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 861U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 351U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1081U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1933U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1360U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1965U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2027U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1028U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 401U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1679U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 17U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 893U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 858U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 497U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1022U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1093U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1866U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 524U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 708U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 678U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 983U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 184U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1862U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2029U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1455U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1881U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1178U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1452U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1025U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 998U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1213U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2012U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1824U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 741U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1613U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1388U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1220U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1662U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1129U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 170U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 162U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 215U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 318U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 99U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1412U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1517U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 682U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1350U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1945U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1951U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1703U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1560U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 333U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 115U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 111U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1397U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 161U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 810U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 75U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 797U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 966U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1970U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1813U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1867U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 62U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 157U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 92U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 148U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 408U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 560U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1630U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1185U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 855U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1934U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2044U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1189U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1096U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1435U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1105U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1992U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1996U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Regulus::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xBCD9548899D9A2E1ULL; std::uint64_t aIngress = 0xA4647379E0462115ULL; std::uint64_t aCarry = 0xA602D0903AD4BECEULL;

    std::uint64_t aWandererA = 0x9A48DF5D9B74F04DULL; std::uint64_t aWandererB = 0xB5A26FFF506B89F4ULL; std::uint64_t aWandererC = 0xA00835648B1B4A6CULL; std::uint64_t aWandererD = 0xB62C1150B70FB01EULL;
    std::uint64_t aWandererE = 0x90843277AB4168C7ULL; std::uint64_t aWandererF = 0xD32A5A450DAC8B5DULL; std::uint64_t aWandererG = 0x81BB8B29D502A669ULL; std::uint64_t aWandererH = 0xA6B7045D52A1FEC9ULL;
    std::uint64_t aWandererI = 0x984D1C07AB047D4EULL; std::uint64_t aWandererJ = 0xF9028D2855B6B686ULL; std::uint64_t aWandererK = 0xEFE8F3F11172FFF6ULL;

    // [seed]
        aPrevious = 9354475680426541806U;
        aCarry = 14713545087702013005U;
        aWandererA = 17171763149659613362U;
        aWandererB = 14839003887960689306U;
        aWandererC = 15287483168647568521U;
        aWandererD = 9472006360304517752U;
        aWandererE = 10166121289452793591U;
        aWandererF = 14292637360625347620U;
        aWandererG = 18077252157784133987U;
        aWandererH = 11475551017325703311U;
        aWandererI = 9837899805378359019U;
        aWandererJ = 13452600966028977980U;
        aWandererK = 10872170310553633686U;
    TwistExpander_Regulus_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    TwistExpander_Regulus_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Regulus_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Regulus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Regulus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 27 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14074; nearest pair: 479 / 674
void TwistExpander_Regulus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4611U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6476U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2522U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6992U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6951U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6682U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5364U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5130U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2067U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3173U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1710U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8114U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5243U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3658U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2054U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4245U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2026U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1973U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1888U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1701U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1008U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1547U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 720U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 618U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 108U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 139U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 977U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 95U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1918U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 953U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1945U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1809U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1574U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 166U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 897U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 195U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 27 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 14075; nearest pair: 499 / 674
void TwistExpander_Regulus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4419U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2750U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7974U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7062U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3395U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2555U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5046U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4402U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4129U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6877U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7508U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1683U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1355U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7885U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7796U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1745U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 215U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 558U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 956U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 227U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1413U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 442U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1380U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 204U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1606U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1439U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1600U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 538U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 625U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 514U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 362U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1591U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1707U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 958U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1255U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseASalts = {
    {
        {
            0xC740784A983DDC8CULL, 0x397EC284865970FDULL, 0xE4A7AC20F5D5E28BULL, 0xEA0BA6906663F115ULL, 
            0x6E1B6E078FAAF0AAULL, 0xF417317924BFA259ULL, 0x88A292BF3AEF5D64ULL, 0x80B5DAA1329FDE31ULL, 
            0x70B46D2486BBDBB6ULL, 0x315A770816F14E23ULL, 0x8D0D341130FAF875ULL, 0x656D7C080275DEF3ULL, 
            0x531FC86305B9D41FULL, 0xB021E4CF29C1D1B9ULL, 0x9C9B67CBE413FDE7ULL, 0x30812A1592B6AEACULL, 
            0xD7B28E08C3BBD6C6ULL, 0xFA687D419C24B417ULL, 0x007BAF258F0B0FE0ULL, 0x4D0E86503A5CC955ULL, 
            0x04455399FCBFC04DULL, 0x6DFCDC73B384E63AULL, 0x3DEA2DEBE5A3987CULL, 0x2FD299CF92FAF66BULL, 
            0x97ABCE50C869D187ULL, 0x5470E0920DD4C874ULL, 0x9527136BE7116378ULL, 0x52E5AA94E17CDC34ULL, 
            0x1A3F45849126CB04ULL, 0xE608421585A78B73ULL, 0x2B053C380DA80CE4ULL, 0xFFB89865B785A621ULL
        },
        {
            0x7D99ED8CE7F642DBULL, 0x926D2D056770600DULL, 0xB940DF0AFA0CDEE8ULL, 0x24F9620B76B4B29CULL, 
            0x843EA791C9155DA7ULL, 0x0A688A124602A41BULL, 0x3D541081A96E5AB6ULL, 0x52FF06DB05EB6912ULL, 
            0xD435BB420FA02B0EULL, 0x7E082DECF36258D2ULL, 0xDCAE2910AA1FDCBAULL, 0xE78D918C161DE7EAULL, 
            0x0C5A35CFE48177E5ULL, 0xCE90B37859FEDCFDULL, 0x83FD9505E2449BDFULL, 0x64AB9A474FD127CEULL, 
            0x1CD4B5BA97545CDEULL, 0xEC821EB80DAFAD5FULL, 0xDD35E650908120ADULL, 0x505DF6ACD1C18931ULL, 
            0x0D561D035EE8E1D5ULL, 0x4D65699B92D11805ULL, 0x17003CE865E0D948ULL, 0x2DCDB65DC910BAFEULL, 
            0xC9F8DAEF9FC9AA0EULL, 0xAAFB1A62492DEF96ULL, 0x96A189A205C6EC19ULL, 0xADAB2902648137B1ULL, 
            0x738E32F6CAA1F442ULL, 0xAD49BE3B9511435FULL, 0xFE79EE87CBF49EBDULL, 0x61E79226E870379AULL
        },
        {
            0x9C6B43F2DF41CB0DULL, 0xA15001750A0F64B8ULL, 0xAA9541C4E7BBE861ULL, 0x80F54311E38D8211ULL, 
            0xCCA10278DCBC4B9AULL, 0xB60F9E20E524B19CULL, 0x43C5E6881871E524ULL, 0x7BD0BA3F7DE31F2CULL, 
            0x054678988242BED3ULL, 0xC041021D1FF4C4ADULL, 0x263E7BC59486EBACULL, 0x62BFAC28750B6B02ULL, 
            0xA38212A3525F1968ULL, 0x6C555F7D34278493ULL, 0x47977E37C12952DEULL, 0x5DEFAA4F282A7FB3ULL, 
            0x579CF630FFE1A829ULL, 0xCB9B34C8A1F35E93ULL, 0xB995BF2F3B2615A2ULL, 0x0B7787E969914C95ULL, 
            0x0D5DB0D94EC9C492ULL, 0x844109F338F02AACULL, 0x3D5E61DD5E43F38AULL, 0x047DEEB9FA43ACB0ULL, 
            0xDF0EAE87B5E7C021ULL, 0x2E41C0DA5D1485C8ULL, 0x2F7E3771FBCEE268ULL, 0xBBCFC7A023CF8F39ULL, 
            0x858EA56316154FB1ULL, 0xFBEF7E30678A178CULL, 0x693961FA953B448DULL, 0x4A58DD0A5F5A0A2AULL
        },
        {
            0x95E02F550F45396DULL, 0xA25E0C1D51C98E26ULL, 0x307540320A90070CULL, 0xA918A2D05C05B3CBULL, 
            0xAA78DE6F0946B4E2ULL, 0x7478C3BCEEF58F9AULL, 0x65CA279709BD523AULL, 0x610EE0A61E4BF9FCULL, 
            0x16DA6815A9F09D72ULL, 0xB3B702AC78E4E6A8ULL, 0xD26FBB9E0FFFB34BULL, 0x8DD71618E49B0001ULL, 
            0x97F9AE45BA880C94ULL, 0x014D03A45BB2F3CAULL, 0xEB5E170B084F0175ULL, 0x2FF0317EDD977EAFULL, 
            0xCC02731EE3A6F432ULL, 0x4FFF2452BCAD037BULL, 0x084D9F93BB653BAAULL, 0xD69334C9588FF69EULL, 
            0x5655F63BB08142C8ULL, 0x5E71231C0EB85EF6ULL, 0xA55E4600E08986C9ULL, 0xD39821B7B1EA63E6ULL, 
            0xB9BE5F8DD4019756ULL, 0x5F819A6C3FB3E977ULL, 0x13BD8CC5ED8F9F29ULL, 0x3EDF2110BA7F5777ULL, 
            0x6BEEB338C85CF9F2ULL, 0x8E5B9F37EA1A128DULL, 0x25E4105A982C2020ULL, 0xAEDD8FB9CC4F8F5FULL
        },
        {
            0xC866C107EDCC0A22ULL, 0xE67A9F43278E0FCBULL, 0xC4683F793C8F72E3ULL, 0xBE0C608D962810B0ULL, 
            0xDF0AD6B714735730ULL, 0xFA82D0398AB3EF5CULL, 0xB3362405C1F78C8EULL, 0x00ECE46350E14D6FULL, 
            0x89F23A7A9F1A154DULL, 0xC118FB328EFA7470ULL, 0x03C09CEE103FE1F4ULL, 0xBDC1837212632824ULL, 
            0x2329DE0D7FD95398ULL, 0x45F709ED10CF60A9ULL, 0xBAC908318C9DD9C3ULL, 0x2EF1E733CA6A9943ULL, 
            0xF6C292097E179C57ULL, 0xA3D939E02F8A418FULL, 0x7E1BE5B802E0727DULL, 0x0CFD6EDB88AB98F9ULL, 
            0xF69F91209A14B632ULL, 0xD5F0CEFBA7D78BEBULL, 0x1FDA313815D36FADULL, 0x479F4D62926F8907ULL, 
            0xD5453EBC4EBA33E7ULL, 0xDD78BA00A1802FE9ULL, 0xD7F05086DDA6B5A2ULL, 0x5B7F2BD632C08A88ULL, 
            0x5513097ADB55B2BFULL, 0x67296DFF63820D9BULL, 0xDDEE6C5AC9532E48ULL, 0x6AD4BFB98CFF1DB5ULL
        },
        {
            0x180D60F6EDDF959EULL, 0xFAB9B2BB17E68B0EULL, 0x46F0CACAE2A07E7FULL, 0xB6A2BE1C7C9A961CULL, 
            0x26009B8591624BC9ULL, 0x487D99A91A3D37CAULL, 0xA3E25D884D7C863DULL, 0x15191829E3B00D2CULL, 
            0xE079A220CAA4E20EULL, 0x5D0B1C2336B16D21ULL, 0x8E6C97666648BEAAULL, 0xEE44056E0A83DAABULL, 
            0x5FF173FDB7479D87ULL, 0x5A3159DEA156379DULL, 0xAE2959DB30832382ULL, 0x3E47C0AA06768C79ULL, 
            0xC913F9066BD33C04ULL, 0xF33CD67B7ED686E1ULL, 0x64B10CFBD5F7B120ULL, 0x38F52FAFDCC3182BULL, 
            0x8A345BB28D0E27B4ULL, 0x7E38C0E20203588EULL, 0x9ECB06F0C9226B6BULL, 0x186F702FC6414D9AULL, 
            0x3EEB62D36357B115ULL, 0x74F3FA5225727606ULL, 0x1A51EF5ED4F46093ULL, 0x7B8802BA0593569BULL, 
            0x04AD442051738F87ULL, 0xDDD8D2D2A1C16EE5ULL, 0x61678693ED29C646ULL, 0xD0F4CDE2184CA18FULL
        }
    },
    {
        {
            0xC19717304D3965F9ULL, 0x06A436F93E940EABULL, 0x4332181EE58D626CULL, 0x98FA0D0F552DC8F8ULL, 
            0xBFE6E9BCD529FD74ULL, 0x161477FAC89FD4A4ULL, 0x477D0B9B5DD9C8D2ULL, 0xF27DA0DF4B5859B5ULL, 
            0x2BEAF5EEFAA19F08ULL, 0x20726528A0F2EFB5ULL, 0x0D51BDF3E33F6A34ULL, 0xD61A74BABF381320ULL, 
            0x76E402DD99C3DC36ULL, 0x1240D857D23284DCULL, 0x612EFC1A6B7B1E8DULL, 0xD6B275300D525527ULL, 
            0x666F25D7F93B2A54ULL, 0x90A2B352F70AA214ULL, 0x12A1268B3FB928E0ULL, 0x6AB9A5B04DC5CF2BULL, 
            0x79225950E7C0883EULL, 0x41220CFACB031F30ULL, 0x31A499F7E1D7EA28ULL, 0xB82FA7EFAFF9FF6FULL, 
            0xDE10BC7191CDEB08ULL, 0x76AB7C9A57710650ULL, 0x30FA61850B936135ULL, 0xB8AE5D6E3672BE9CULL, 
            0x700C57E176465399ULL, 0xB57431C4BAE5C706ULL, 0x2762E9E6ABB70FADULL, 0xD247D8DFC161DE60ULL
        },
        {
            0xF30FEA9833D2E20CULL, 0xC95800CFC691E4A5ULL, 0xCFBEC87963B3D0F9ULL, 0x92C88801964CA734ULL, 
            0x1DB7DC407F3D78ADULL, 0x7E5BFD4D4A198A66ULL, 0x3EBCB7990BCAD7CBULL, 0x87F8E0018DFEEBE1ULL, 
            0xC0F66D9EDE5915E0ULL, 0x53EC3226533825FFULL, 0xC54DFD19DD6BCD07ULL, 0xC07DC0D18D4411CDULL, 
            0x473E8A996F641AB3ULL, 0xF891926918205627ULL, 0x41229E383DBCC3E3ULL, 0x4DD6583D7AF3951BULL, 
            0x502AC736F5E163D5ULL, 0xC9D53882D6B9987BULL, 0x25B2978089D070DFULL, 0xE346C3A21B9AE052ULL, 
            0x8741A01500696C60ULL, 0x9CFF15E733D43CD6ULL, 0xC42239B4660B0E84ULL, 0xC8B3BACF38BB89A8ULL, 
            0x14B4D3A65465067EULL, 0x69413FBF3C17345FULL, 0x2A058F48466F00F6ULL, 0x68BDC34FA67B2496ULL, 
            0xA898F4EDBDDE353AULL, 0xD760A2F3A2130FBEULL, 0xB6FF14A2D245EC62ULL, 0x946073359AFBAE4CULL
        },
        {
            0xF95BD13E4C18D087ULL, 0xFE3F707E432C9EEBULL, 0x5964174FB66C1E66ULL, 0x75F65E2878188E18ULL, 
            0x004AE58837D2BC52ULL, 0x728BC982A8E7A03AULL, 0xEF00FD56D69569C5ULL, 0x54624D52C19BC156ULL, 
            0xCE990E31BAED3BA8ULL, 0x8922339F06116DB9ULL, 0x40F684C382733087ULL, 0xC9B44666E08146B6ULL, 
            0x62B3E8EBB09D4D7BULL, 0xAAE5DFEC3847E1ABULL, 0xAB8C3A8091CC042FULL, 0xE360422CB261636FULL, 
            0x17BE70A9DDDE2B4BULL, 0x1532C4C99BD61076ULL, 0x544FB71120B2AF5CULL, 0xD2D862E840A7C57FULL, 
            0x6C0F92810A99A7AEULL, 0x6EBCD04809099EA6ULL, 0xFD672AA53E0822B2ULL, 0x05ADAB5616B90EFBULL, 
            0x923D224DA88A76DAULL, 0x5341DFE6E7EFE2BFULL, 0xD5C84C7C109F39FCULL, 0x0BAAAA1E4E597A8CULL, 
            0xF7954412293BBA4DULL, 0xC3DACFA238DB9F21ULL, 0x4A5B0680A932683DULL, 0xB4C72CC4E0096A07ULL
        },
        {
            0xD0199F48772BEFDAULL, 0xD4F87F64D5A0A38BULL, 0x36A8458DA725874FULL, 0xC04C5A31E9002DA7ULL, 
            0x8367DD626E1761B4ULL, 0xDC79B0D15175F9C9ULL, 0xA83D1AA9F95BF51DULL, 0x0ED3C36E051211F6ULL, 
            0xA386D76B603A4888ULL, 0xA0E09EE06A654C55ULL, 0xFECFE475ECB0BB0AULL, 0x5761FAB6C6881D48ULL, 
            0x41D6E2D094C131A7ULL, 0xC4F36E992A2EEFB1ULL, 0xB08F2D41A239C9FCULL, 0x718DDBE0C30488DFULL, 
            0x65D5BE7D9AE4E4C3ULL, 0x8E0B4667C7D10DB3ULL, 0x46BADCE61E306165ULL, 0xE0642D5BBF45C572ULL, 
            0xBA14510AA45EC8F0ULL, 0x438D8A3C520858CEULL, 0x8489E40AD66B7E18ULL, 0x84CB5C229D9F7F0CULL, 
            0xC4F588D4DF410E8CULL, 0xC13F0E2547BE2066ULL, 0x25F8ADEBD20E359FULL, 0x015DE286B487C386ULL, 
            0xABA802FED16E738BULL, 0x4CA78D372F612D23ULL, 0x897B26B83797653BULL, 0xB2F753355CE291BFULL
        },
        {
            0x65182F1EECA8C846ULL, 0xF2D2924972378E7AULL, 0x4388EC083E93E2FFULL, 0x0A8DC1CC60EFE752ULL, 
            0xC778CD119F309125ULL, 0xD9621ACAAD02699FULL, 0xF72AAFCC1D6288F8ULL, 0x8904A59046CA3A90ULL, 
            0x9EFDDD8E6159ADB8ULL, 0x6E641D4AEFED9E52ULL, 0x3474D49599022C49ULL, 0x0433862B8ADD193AULL, 
            0x5A011E188B8BCD1DULL, 0xF5D82153B79A46B0ULL, 0xD82ACD68D0693493ULL, 0xA3CE1A3EA6A3E31FULL, 
            0xE261CE3945081A1EULL, 0x596D32F7456DD215ULL, 0xBFBFCBB7BA64D6A5ULL, 0x6BDB0D48BF4B2EB4ULL, 
            0x65873DE2C9EF9764ULL, 0x9C430DE1DF0F3767ULL, 0x67DA9C053CF7D08CULL, 0xCDE3481E6ECA2CA5ULL, 
            0x0FCFF6C4320A031BULL, 0x7A8567DB99346C83ULL, 0x8B3D13F6BA1A46DDULL, 0x5693E823C0254364ULL, 
            0x355C62B86987D51CULL, 0x480CC03272CDE362ULL, 0xCF73BC2A49CF0F86ULL, 0x392478CB04992EDFULL
        },
        {
            0x748A4A15542F45B1ULL, 0x4F1068496DDB0EA4ULL, 0xAEBD5C8A46CBA23CULL, 0xB9F5BCFFAD23ABB4ULL, 
            0xAE8E83F76E4F4C2BULL, 0x45ECA48B7C44AB41ULL, 0xDD0D974B1216BC9DULL, 0x873C11BED1A27FF8ULL, 
            0xE7B095B2A14B529AULL, 0x6EF0B63DD74E8087ULL, 0xE739A8A82EAD0EB0ULL, 0xA3825D0FA96D8443ULL, 
            0xDEF5A16251C7C35BULL, 0xE0FBA072D1BF3852ULL, 0xA711F5A5B042FA1BULL, 0x9A6944E53192FFE7ULL, 
            0xD703F8DC3967A861ULL, 0x32A1810C2234E520ULL, 0x2993B0E4A465B845ULL, 0x7B847179E8D11D8DULL, 
            0x9DC6F7B3F9552BE7ULL, 0x14614C606B08AAE9ULL, 0x0857EE73A8C9B793ULL, 0xE7F28BAACC554201ULL, 
            0xB60DE49C38169545ULL, 0xAEF96CD5DAA55A02ULL, 0x50DD53A728953750ULL, 0x1F58B0FF9719E689ULL, 
            0x24DF560EA3A3E4ECULL, 0x6B7289B8C9B5C830ULL, 0xEEDD1B6DF94A42EEULL, 0x6ACD31A7C685E270ULL
        }
    },
    {
        {
            0x98406323A9E01B9FULL, 0xA25907070F269317ULL, 0x188744E86D6A36CAULL, 0xD68D2E840147A207ULL, 
            0x474900B8B481BF50ULL, 0x32F50EDE284A338AULL, 0x5EA6B3D7D14C2ADDULL, 0xDB73A8BB53D45A16ULL, 
            0x2419B2ED0E6013AFULL, 0x6DF408724579F12BULL, 0x16CE048605A10664ULL, 0x11AA6ACA523AB670ULL, 
            0xECDE6D758DDA338FULL, 0xE03DFB4B919D6206ULL, 0x5C04035104AFBF76ULL, 0xCD85AE3FB8B0CF80ULL, 
            0xA43DAE1D64A009E6ULL, 0xE764B05F4EFD59F3ULL, 0x538D32F2EBBF8D9AULL, 0x588FA425227D2C12ULL, 
            0xD3B4AAB56BD293DEULL, 0x2A7AE2E1B7B39AF2ULL, 0x691F8D110DB5738FULL, 0x728441D605903EC0ULL, 
            0x29C1C6C41962BA81ULL, 0xD24F9DEB4C4B35CAULL, 0xB8C5B7CD258C91B3ULL, 0xD45E17494E798DE8ULL, 
            0xE030191CA741CEDEULL, 0x043F45A66AAE2AD9ULL, 0x4BD31E9DCA094478ULL, 0x03C4BFBB42BC7D07ULL
        },
        {
            0x19FCD1F7F9789A0AULL, 0x82084FB0A0065284ULL, 0xEA21DAC98E9F6993ULL, 0x40C848F068625670ULL, 
            0xBB7BA3840A857AF5ULL, 0xF4B22B0B1C55A308ULL, 0x9643A9894C2F6FF8ULL, 0x1C88F6637B1FD16BULL, 
            0xCAA5EF69E9462D1EULL, 0x907D1762846F12B5ULL, 0x58CE517D936E4E73ULL, 0x9C2B0FB72453FD4CULL, 
            0x9B8BC0B01AF952AAULL, 0x3E73610E1E732090ULL, 0xA3E2363760CE8F95ULL, 0xF7BE741D36BE76D1ULL, 
            0x4035F6F2F85202EFULL, 0x23BD798E347E1AB4ULL, 0x2363B2F82AF7CAB4ULL, 0x0FF34775B79A360BULL, 
            0xF367EA4D92816488ULL, 0x27B8A7E375F88AEDULL, 0xE13219F43D0DB456ULL, 0x484398204CCFD6CAULL, 
            0x050AEE4878B0B462ULL, 0xB0D65BDE44A69486ULL, 0x5B5355EE829BBDE9ULL, 0x632D9F18DF1BBDEAULL, 
            0xFAE9B8EFF84A8153ULL, 0x1E4D47885142FD25ULL, 0x3D38F60505FC723AULL, 0x36B6A9999140D9FCULL
        },
        {
            0xE8F5B28D3A047571ULL, 0x23D211E5497D4592ULL, 0x374F6F4B5D9DB3B3ULL, 0x88318326208966A4ULL, 
            0x9A70C6316065DC19ULL, 0x1BDE101599B8F71DULL, 0x011C63D39E4C3CF2ULL, 0xE0BFA0D6BAC6D401ULL, 
            0x059A6F62BB335837ULL, 0xC10C5572E8EE8ADEULL, 0xF802CF54C095EC87ULL, 0x9614A79E7E1B9072ULL, 
            0x49138499F4252C60ULL, 0x3FAD2E35480EFA4CULL, 0xF60290BF4CC5976EULL, 0x4848E84B3B9AF926ULL, 
            0x9130BB71EFE0741FULL, 0xECE9C24F1480B414ULL, 0x7948CEB9C71EC23AULL, 0xCC9EEEF9CBB01B19ULL, 
            0xD76930457E6158D9ULL, 0xBD828C23F3EE8001ULL, 0xBB7AA040F8304D6EULL, 0x146DA3F08D3E108AULL, 
            0x22374B3DF63E62C9ULL, 0x5DD7CFCC84A7E2D6ULL, 0xF2CA959680D9EF3CULL, 0xD608AC864A4E44A6ULL, 
            0x59D2A5EFE158AE96ULL, 0x94C9D34601A6DD81ULL, 0xE5699012DE2A45A6ULL, 0x1C51FB4B134713F4ULL
        },
        {
            0xD15A61C15ED09DAEULL, 0x22CCFEAC19064B24ULL, 0x9CB8EB53EB5C9276ULL, 0x513A439CAB62A686ULL, 
            0x1CD74704E9370D5FULL, 0x63820A142332C49FULL, 0xC37214825D9832D9ULL, 0x4291F84055942030ULL, 
            0x57683BF597F9D44BULL, 0x8E088194BBDE30E4ULL, 0x984349884347CBE4ULL, 0x9CB311C31B72A118ULL, 
            0xC12C51B7B70E9B4CULL, 0xBCEB97AC94A502A1ULL, 0x4449282A5FDB190FULL, 0x93E4409B7D199981ULL, 
            0x08098AA68BF4EDC9ULL, 0xEC800CD9212B86F4ULL, 0x5D37E179159C3DEEULL, 0x4D175463AC4489B3ULL, 
            0x0C1FBB432E4C78BDULL, 0x9018ECC264801046ULL, 0xC4DCF18E48484731ULL, 0x9E160D657F7F56D5ULL, 
            0x7E71AD2035A487EFULL, 0x911F6C8081EF8321ULL, 0xFD654E3181EC923EULL, 0x85972BB5FE267E30ULL, 
            0x47E4D9FE65062CE3ULL, 0x9B9646814E63AF11ULL, 0x3EB5E7CF4C6E02C6ULL, 0xE906D6C3386576EAULL
        },
        {
            0x84EAA96521FCF8BBULL, 0x3D75CC0361406206ULL, 0xAB9F6A360F595764ULL, 0x30601CB22A06CBC8ULL, 
            0x317B405221C441A5ULL, 0x2C31D4E64141174FULL, 0x59F65573F385866AULL, 0x18E831EB5562F981ULL, 
            0x5657CB1B8BC8D824ULL, 0xCC5B32B00C9307EAULL, 0xEB9985879B3B72C7ULL, 0x096611E96A4C9CD7ULL, 
            0xF04EE842AC35CA09ULL, 0xCA9AE024196E295BULL, 0x8E331525590B3C9AULL, 0xD672E7EFDA7A1238ULL, 
            0xDB7ED002A7D1E27EULL, 0x18FED2F2045BF0BEULL, 0x7CA5C8B32D9F33D4ULL, 0x297DBDC00E1BDA51ULL, 
            0xD4C3A9D79DDCAEE5ULL, 0xACB924EDE4AE511BULL, 0xCBC625B66E07FC63ULL, 0xA5AB7C1B32C6B6C0ULL, 
            0x3F60477481FAB8D3ULL, 0x7872B89339660B75ULL, 0x4F5C34DD2C65640DULL, 0xD86354F686D078B1ULL, 
            0xE942BADD9D9A4454ULL, 0xCFBD7C735585B74EULL, 0x5AE3C362446A3D75ULL, 0x0EE5E6F33E4FEB25ULL
        },
        {
            0xB9D3FE486A19FBE1ULL, 0x5922199FCAEB73CDULL, 0xB34BA21CD8462D50ULL, 0x5D86FB7356EF3C9EULL, 
            0x61B5E8976560D575ULL, 0x56EE6A6992017C10ULL, 0xF139F7B462FB2C30ULL, 0x726E46C54AA6D157ULL, 
            0xD1ACBD93BEAE41CEULL, 0xE40B0D2DED1E517EULL, 0xB98070DC0BCAA6EFULL, 0xD953979E0B389A98ULL, 
            0x79A912901732EA21ULL, 0x1E35418277B62D28ULL, 0x5BF88C4CB1EA61CFULL, 0x394CF862E92F6CE1ULL, 
            0xB974C3C0D779065AULL, 0x0DE577E56838E74CULL, 0xB226B3A54E173828ULL, 0x31758BEFE32030B8ULL, 
            0x160BB0376AF3AE37ULL, 0x0F4FF86D1A6D2549ULL, 0xD1D00F21159230FAULL, 0xD099931F720986BBULL, 
            0x6BD733613383F7C4ULL, 0xAD16A9243750EF38ULL, 0xB1372FEF6A858A5DULL, 0xE632E64A08AD9032ULL, 
            0x0A1FCE5D4D9E67C1ULL, 0xD9BA0EDC87E572D0ULL, 0x367E371E17BC1843ULL, 0x82F7E66C5ECF615FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseAConstants = {
    0xE46B32FF16F3B645ULL,
    0xD4510473075D3DE3ULL,
    0xA9B750E055B7BC6DULL,
    0xE46B32FF16F3B645ULL,
    0xD4510473075D3DE3ULL,
    0xA9B750E055B7BC6DULL,
    0x6A41F67F7F2464EBULL,
    0x0DD2AB0171F4F509ULL,
    0x3F,
    0x42,
    0x16,
    0x69,
    0x87,
    0x82,
    0xDF,
    0xCE
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseBSalts = {
    {
        {
            0x94BA62D7E7FFC9CDULL, 0xADD2D1FE7A08A7F1ULL, 0x697C7A90CCE9550EULL, 0x3245306677E6EF02ULL, 
            0xBB716DD98C431E77ULL, 0x224A95768CF1A840ULL, 0xC420B185A8DF4F27ULL, 0x6F39E870B2CFC860ULL, 
            0xD79C8C90F8A3235FULL, 0xC5E8AABB276FC00BULL, 0x645C23614C8EA3E0ULL, 0xBB0071EBCC681AF0ULL, 
            0x90C07B76F94BA5C6ULL, 0x6179409CB8E2F486ULL, 0x2313717978E28C16ULL, 0x76DC4C384897C1C3ULL, 
            0xD11818CA2D54D8C1ULL, 0x6B52C3599C1A974FULL, 0x4FC50DBA53A85885ULL, 0xB2BB7CA8D3447CA4ULL, 
            0xA581AAF1C53A24F2ULL, 0xF3A5B1568C7720F6ULL, 0x65E95BAF26BBF468ULL, 0xBBBEFC4A2D011024ULL, 
            0x439D1D016A80FF4CULL, 0xEA48C473AD58D73BULL, 0xC691AD5422377348ULL, 0x48798C49E780C82CULL, 
            0xE1CD49F78B4807F3ULL, 0x023D2AEFB8C5B4CCULL, 0xC9ECB4E417AD6DBDULL, 0x617038EFC6C31A40ULL
        },
        {
            0x714E2B524CA798B4ULL, 0x0480EA77316A30B4ULL, 0x9B626FEF51F14AC1ULL, 0xE2640E0542E89ADBULL, 
            0xE4959341D1958466ULL, 0x06FFB49AE91A494CULL, 0x60E0B86FB5615E58ULL, 0xA3AC19ABF13E1409ULL, 
            0x55F2193C1BDE7F2EULL, 0x14FEE98552491437ULL, 0x03930CADDF904DC7ULL, 0x460CEC9C93201591ULL, 
            0xAEDD8475A9D0CFE1ULL, 0x0F38C5BF8D7B4909ULL, 0x1D1AD214E25FC22FULL, 0x0765047EE2BB1184ULL, 
            0xA6B14C85ABE5B9ADULL, 0xA2CEBBA853EFFF56ULL, 0xC500964762EF2FE9ULL, 0xBA5CBEB0AF12E169ULL, 
            0x0E85EED1E73DDC86ULL, 0x0E3350CFFA8AD433ULL, 0xB1FB28C25E43F7ABULL, 0x838A1CF75E836A3EULL, 
            0x096136E18E5471ADULL, 0x072EBA10CF7C3D83ULL, 0x379F67980693A688ULL, 0x73438BF797CFF1AEULL, 
            0xB6E970AEFB3CE76AULL, 0x9DEF0F74E1E85760ULL, 0x33376F9AD071B56BULL, 0xD53F089DE1360C95ULL
        },
        {
            0x9637AB79C9777035ULL, 0xEF4803638FC931A5ULL, 0x688E718F28A662A1ULL, 0x59391BED178EDD18ULL, 
            0xB4D5E91E4A5B29E0ULL, 0xB638DF1E37EB5EC5ULL, 0x02B3AE724E425452ULL, 0x867E8BA3D57DBB43ULL, 
            0xAD0BA2B0C51CB0FDULL, 0xE7B02F887A1C89B0ULL, 0xB7588748E9707D4EULL, 0xCA14A332520573E0ULL, 
            0xC0812FCCA2FF5F33ULL, 0x3FF7420A121D4E57ULL, 0xEEA697A4A29FDD8EULL, 0xFE0CD1DAE178C84EULL, 
            0x05C6B501129B66DAULL, 0x5CAD64B7E93EE855ULL, 0x9DCF1B7603EF7EB1ULL, 0xBB484D4F4F4CF5FEULL, 
            0x32CB3C2215293C89ULL, 0x6622C1672011672CULL, 0x03A26659CD25799CULL, 0x1703E9C64AA19710ULL, 
            0x9164346F75CD28C5ULL, 0xF8B981DB9C2085E4ULL, 0xCB7E73A7660BA1B8ULL, 0x05F9FF2E6E28E942ULL, 
            0x252BE8CA0CB6A253ULL, 0x2CE03734C8DFF746ULL, 0x35B8B152A8F805D2ULL, 0x26E2EF67E0CCF641ULL
        },
        {
            0xCF2047C266C756A8ULL, 0x9CC826138F38A233ULL, 0xAE6DFB746C40B159ULL, 0xCE6E118E1AC39165ULL, 
            0x28CF268C2D0C92B8ULL, 0x0CCA428D11B6D87BULL, 0x80E0A317643D4930ULL, 0xE7A82D8E55134055ULL, 
            0xDBED84B674913D36ULL, 0x5D63DBAF460C026BULL, 0xB902E7B0EDFD3643ULL, 0x3A0BFA0C74A7EDFEULL, 
            0xDA32E2644052E9E5ULL, 0x1176B288AA3EB983ULL, 0xF9AAEE2509C5D139ULL, 0x481CDDE41817DF7DULL, 
            0x715A43B132446BC8ULL, 0xA15269ABECB0AE58ULL, 0x6AED972150D331D9ULL, 0x435C88EE2E9EB7FCULL, 
            0xDCAE41F0B581CCAFULL, 0xCF8E16851C75CD49ULL, 0x8772495913D5E1D8ULL, 0xE348316C78E837B6ULL, 
            0x33843FAC6B251491ULL, 0xB5568D3AD51DBD00ULL, 0x54C37CF39567829AULL, 0x61B8A4F12725BF0DULL, 
            0xA70A8893001A792EULL, 0xBC647456EC7AE772ULL, 0x971DC9B41CC4916BULL, 0x6BEB39F5C458D748ULL
        },
        {
            0x16363393E007DE04ULL, 0x138FF13894539E7DULL, 0xE0E2F6EB44B39EBCULL, 0x05A7BCAC7E443211ULL, 
            0xAC9BAB0B44283253ULL, 0xD3184B144B7679F4ULL, 0x3A75155982A9DF17ULL, 0x62F8358B355EF9C7ULL, 
            0x13C244455B8067F6ULL, 0x2A313E88FF366E06ULL, 0x7BA78629A1A2BE89ULL, 0xD1C4DC2A20BA5A2DULL, 
            0xD21A0E8EDB539E38ULL, 0xB73F9408898CA84EULL, 0xF427F0142237C294ULL, 0xB45CAAABFC645C3AULL, 
            0xC2160D24294A9809ULL, 0x1E5EBC446141595AULL, 0x50560AFC980D6449ULL, 0xE772A56C2B3FE2EAULL, 
            0xE630F790F8A74C01ULL, 0x405FDE0641DD8CF4ULL, 0xD9233798626BD63AULL, 0x4870886248ACA64EULL, 
            0xE1411CBCC841D541ULL, 0x85325D29B08F41EDULL, 0x3BC0462028AE3E40ULL, 0x9BEB833F2A05DE4EULL, 
            0x3ED21772390CD37FULL, 0x62C444F196C3EAF6ULL, 0x35C00DF442319399ULL, 0x6306C21804C08ECDULL
        },
        {
            0x43DFD89A14EC7E0CULL, 0x7433C8B6CAA4A140ULL, 0x794787E7F0238ED1ULL, 0xC32BEC5A58C12413ULL, 
            0xDB9D70F5971F42CBULL, 0x7A630654F84A8D00ULL, 0xA1B5518837E5E1B1ULL, 0xF91ABC5601217863ULL, 
            0x7F6E45E07B2A9F48ULL, 0xD379370916D68422ULL, 0xFF5DD1E8E5C4D935ULL, 0x8BE5B8D493964154ULL, 
            0x6106DF675284323EULL, 0x3C57CFCE5EBDD0F2ULL, 0xFA48931602449E5FULL, 0x6155898249A7D467ULL, 
            0xC34F98BB557039A8ULL, 0x0C7FDEB52A2A4ECBULL, 0xB2E62D7B03B2D618ULL, 0x2A4562AF9B19370CULL, 
            0xD53DA877E1D5CE12ULL, 0x4E4DADD7C6E5333EULL, 0xD242E3D3668289C7ULL, 0x7913D22E7564E8ADULL, 
            0x4E49000E0C927781ULL, 0x862EE7F7F17D1039ULL, 0x4491BECEC835C0FAULL, 0x39066E37A1BC7F9CULL, 
            0xF4F72C71F7BCF64AULL, 0x587932D1B06F252FULL, 0xFF362B502A81AB6EULL, 0x355919274856EAEBULL
        }
    },
    {
        {
            0x37BC5074BE183553ULL, 0x55A71FD43D45608DULL, 0x8B80AB0D6D994BB1ULL, 0x1DDEE82CCC500D25ULL, 
            0xAA82E66CEA3B3CB0ULL, 0x3972796B16E4F293ULL, 0x669BF260FA35EB41ULL, 0x8B50957EC923F50EULL, 
            0x2741A0C51F4CD57AULL, 0xE3600B5618722FBCULL, 0xAEE0180838F72F83ULL, 0x3043C3AC8BC3A53EULL, 
            0xD3E257F2D145045BULL, 0x82CD8ED15F07BBEDULL, 0x299E9549C62D3DFCULL, 0xCC5A17F891F1AD4DULL, 
            0x0A402C5F1018D3A5ULL, 0xBE598AA42D62F11BULL, 0xA240F3BB90127EC2ULL, 0x716B4D2344D785B1ULL, 
            0xC702DE4861DF5FC8ULL, 0x1629E69AD7FC0CB9ULL, 0xFC1CCBAAD3CD0D05ULL, 0x2E4A53569F808BABULL, 
            0x7C607C82D3CC4BFBULL, 0xD24A54FF7D0BEFA8ULL, 0x9FBF202023572F2BULL, 0x9D435D4310FF26AFULL, 
            0x0893C22835FF4C99ULL, 0x718C590E541174C0ULL, 0x6A0866D6CB2911C0ULL, 0x3953DED0C231B615ULL
        },
        {
            0x9B0833B7B3A81C61ULL, 0xC26944CF9BE65D69ULL, 0xA264795EAD97BE05ULL, 0x86C934D12A670D1FULL, 
            0x16DBDC47DFDC7C4CULL, 0x87A2B072CF646CB1ULL, 0xEABCB8395476CECAULL, 0x100B310070830EC2ULL, 
            0x1A608462A05EA430ULL, 0xA3CBA66517B7460EULL, 0xE12EE3C23BBD0EF4ULL, 0xBD0C9DB4AE294BF4ULL, 
            0x18EB66375E51979CULL, 0x4EC15374FF193DE7ULL, 0x33258AB74CCA2433ULL, 0x97E9D6419FE54BA9ULL, 
            0x8AEDF0926CCF4A8BULL, 0x94EB3440D880903DULL, 0xFC0386A80346D2C3ULL, 0xB24161CA0BA307B3ULL, 
            0x51BF08AAD81AE40BULL, 0x847306EF4E316118ULL, 0xCEEF91A1AE5E9586ULL, 0x19FA66CAF03D3797ULL, 
            0xE63F4627934A9E19ULL, 0xD43434944D29C0DCULL, 0xB7843F58784A33E2ULL, 0x3242AE9AB0AD0FFDULL, 
            0xE4FA968870A8FBCEULL, 0x49D516920ADC3F52ULL, 0xB7E14FD30F94F52DULL, 0x0B6B1120253B0008ULL
        },
        {
            0x7C18160972928D1EULL, 0xC3A6F73EC40C2E8DULL, 0x8E73E0F36F5EB2BCULL, 0xC91F8F0C56339B99ULL, 
            0xB5C0E16E17DA1DCAULL, 0x3C47D08E1B21F2FAULL, 0x1A48AD2218C77146ULL, 0x80B44A6B51DA7D91ULL, 
            0x7C46522F668A6734ULL, 0xEC130B9F7EB81FF2ULL, 0x036DB6F11C4A510FULL, 0x2A7402ADCF69817AULL, 
            0x0F9914115C3C497BULL, 0x4BBEE560698ED56AULL, 0x3B97F6559FADA1EAULL, 0xD814366F1CFDD987ULL, 
            0xE65321DE6ED4AB1BULL, 0x0FDD95F7E936A9B9ULL, 0x28590E38AB70A14EULL, 0x641A188B203D1309ULL, 
            0x89753EC9EDF6B506ULL, 0x76319F51CDFD2A78ULL, 0x50BECE6A08AC4E8FULL, 0xA0799813D010DD8CULL, 
            0x156D3174BD4BC6C9ULL, 0x5C3DFD41735AF1D7ULL, 0x166B70525B5B88D5ULL, 0xF5A2EEC62DAE9B97ULL, 
            0x6E0CFF5E5B37E386ULL, 0x113297B0739A413CULL, 0xB44E8C591495B7D0ULL, 0x397B8349D28FDA06ULL
        },
        {
            0x3642EAE3AD422255ULL, 0x01FF573F9D536861ULL, 0x7100847ADFDE2DEEULL, 0x3A5633519A6F06EEULL, 
            0x0768212BEDF5E594ULL, 0xEB5BF80884056167ULL, 0xDCC8ECB573E25808ULL, 0x8B4F35EAF5182D23ULL, 
            0x6C005AC21B8A1AEBULL, 0x72D3470E379E85D5ULL, 0x463581D64580C2C0ULL, 0xD242328EBE6A8A50ULL, 
            0x90DBC82A3F1DB2DDULL, 0x78C43DFD58A7F08BULL, 0xFB344E45225229F7ULL, 0x0CBED35C33474032ULL, 
            0x873914CE27B7DA5EULL, 0x21F70F5641362C33ULL, 0x715FDF09BEDA9B2DULL, 0xE3DAFAC53FE4958FULL, 
            0x512FB8A0465CD07EULL, 0x25681A32886D1294ULL, 0x4160D73A0A4244F0ULL, 0xCD47E1C7CD89E8D3ULL, 
            0x60AFCD484900FA7CULL, 0x50EAB02837490D35ULL, 0x6E451640C92AE334ULL, 0xCC264B28B74AC497ULL, 
            0x47B2D51DA62EED60ULL, 0x7B4C449E29088A48ULL, 0x44E69BD9B027B42BULL, 0x11990DDA28B65D1CULL
        },
        {
            0xA48776C138FE2F30ULL, 0xE214E57D7420E4C2ULL, 0xEA92C7466BCE33CBULL, 0x8D4B021C43ED9C2DULL, 
            0x0E620D0709296339ULL, 0xDF120BFCE514F3CDULL, 0xA8050CB508953F77ULL, 0x70A1B211422FB59BULL, 
            0x1410F3C9DA38BA30ULL, 0x0A4B95D1CDA360DAULL, 0xF727F583958995EDULL, 0xBD491288B3E7AA72ULL, 
            0xBC5F6530B9A7D648ULL, 0x353957A3802E70E3ULL, 0x0F2143BF1407754AULL, 0xFF1D3CCBFFF8664BULL, 
            0x6191E7BC947ED331ULL, 0x133E115260DA8DACULL, 0xADAFEAC2C0B63AB6ULL, 0xD9B3168645BB0D88ULL, 
            0x0D11395C0852AF01ULL, 0x67CB5D149A2929AEULL, 0x8C6F059B26C6AB39ULL, 0xF7BD7045345886B1ULL, 
            0xC37E8919491C5B1CULL, 0x41B2CC06BFAD3107ULL, 0x9AB04B73C9E5C642ULL, 0x9DD812AE7A39E690ULL, 
            0x65EE721F1600BAF1ULL, 0x5C05F32A95017DBCULL, 0xE6FA576D12C0BE0CULL, 0xF40B9BDB5A855719ULL
        },
        {
            0xE3CD9D22CA9A53F5ULL, 0x8D2DE725CB443EAEULL, 0x8431CFB46E5B1798ULL, 0x1392C1D4353BE1D2ULL, 
            0x2AFB39E95D0A518CULL, 0xA042A4FA3DB0D30CULL, 0xE7AD1C3F8A885911ULL, 0xB05AB4014D6A192AULL, 
            0xEC8560E4A9CBCC30ULL, 0xD90C530ADFB9FF2AULL, 0x0CAB21100C97E59EULL, 0xAA4A1572A3777713ULL, 
            0x5CC3D5CE6665E688ULL, 0x73F2B7978EE9CEF9ULL, 0xB8B5F37FBA4E5577ULL, 0xAB8674207570A652ULL, 
            0xDEE49F8D8EC0F4C4ULL, 0x13545D112ED17A60ULL, 0xDA03BDF13A492F3CULL, 0x88D40EF1131D100FULL, 
            0x69430495D0EAEE89ULL, 0xBCA87E225A3635C7ULL, 0xFDF6D37524EA6D15ULL, 0xB97A774A9720817FULL, 
            0x378A197CF976863DULL, 0xD84DF60E7FB2DD84ULL, 0x69742E3AF857A3AEULL, 0xF9F83A7543E5E5F3ULL, 
            0x3D07C7A55EAA25DEULL, 0xE6EADF017EB7069FULL, 0xE8CFF09DD317308AULL, 0xB83175333A1E4757ULL
        }
    },
    {
        {
            0x387CF632415D4BF8ULL, 0xA42AC20AA596473BULL, 0x104DFEAAF9E8F3F2ULL, 0xDBDA18A25CF32FF8ULL, 
            0x9D74C9D59DAFBC86ULL, 0x48CAD85F32D3507DULL, 0x20A035FA863D8033ULL, 0xE2D9DB03630C8C0BULL, 
            0x2BA01302B6E1456FULL, 0x7640F8961C56E13CULL, 0x49E78CBA97D4872DULL, 0xE3D0DDA3AF21669AULL, 
            0x3A45ED3D38805874ULL, 0x4064D06E7E9F444FULL, 0x5B7397AB9A98961DULL, 0x785C64F5BD7F5574ULL, 
            0x063BB88DEFC76035ULL, 0x6CDA0CE0D75EAC8CULL, 0x7029A8E6D4415961ULL, 0xC264027DB7979ED9ULL, 
            0x9FCEB4E63C886EADULL, 0x597767184C61A6F5ULL, 0x274FFD68013C4568ULL, 0xCAC6E46E6FCDD7BFULL, 
            0x037556FEA552B2C8ULL, 0x5966F63E7F05B593ULL, 0x9A46EC5876DC9794ULL, 0xA3486C91ABD5F0CFULL, 
            0x9A8DA7E0B92323B3ULL, 0x2FF270E52C23A480ULL, 0x9992E8704677D23CULL, 0x26441127939CEC2BULL
        },
        {
            0x9BBA43A0EB374A8BULL, 0xB83AECFA3184DEA1ULL, 0x12BC8CB64CA13A8BULL, 0x87EA621177D64E83ULL, 
            0xD7A234B700179D9BULL, 0xC57E3C105A8F6486ULL, 0xCDFE1A04AB5F2F1EULL, 0xB41683D97BE00DC9ULL, 
            0x8B382B2EAFEE38ACULL, 0xEE691D3532CB9B49ULL, 0xEB9B4296717C2139ULL, 0xE3923C9975B384A5ULL, 
            0x24456A45C772B96CULL, 0x4A08183282ABD3B9ULL, 0xC479451ED947585CULL, 0x21098836D84E77D3ULL, 
            0x8A150B4B152E42E5ULL, 0xE7B368AE1127CD09ULL, 0xACE08700AFB22F62ULL, 0x7E1A7965D7AF18F6ULL, 
            0x4B25C594BBEA7288ULL, 0xA507D3061C205E9DULL, 0x7661923B2D228D7EULL, 0x8A1A774D121227BDULL, 
            0xFDD4E67D4886025BULL, 0x1EBB038D0E22118AULL, 0x87D09F8DD0DE5FDDULL, 0xDD14292106BF7BCDULL, 
            0x095E3A94C6760354ULL, 0x918CC6EF77B7763AULL, 0x548A6F90184C394CULL, 0x2E10A6B39905DBC9ULL
        },
        {
            0x8A830242C150802EULL, 0x39FC8E3423788CCBULL, 0xD1E65DE7C0E9DEFCULL, 0x067427D0BC77B0ACULL, 
            0x648A59C7CA6598E9ULL, 0x09ED3EC0E08F72A3ULL, 0xC26CD6CB78919A53ULL, 0x2B9D29CE75399A69ULL, 
            0x70D5DA1F36591254ULL, 0xE3C29AD57D6D2A65ULL, 0xB7A468B2A64D342EULL, 0x0BDD6CAAFA05618FULL, 
            0xB2C5693FA379EE9DULL, 0xEBB6B8449999C182ULL, 0x5D90B080180EED26ULL, 0x64C7F9F9ABF717EAULL, 
            0x0ECB51BE20B34B1EULL, 0x4CDDE94BF96CA455ULL, 0xBB964DC4196BD329ULL, 0x076F6AA362232E4AULL, 
            0x896A3D857E2250EDULL, 0xA4B57EECA679B7C4ULL, 0x1BF69CCCBF5F053DULL, 0x056C25E350FD0E5EULL, 
            0xDA2A0FA3C1D3C15CULL, 0xC0B5C1F657DE5CE4ULL, 0x9A48359D8A3827E7ULL, 0x93101C4AEAA87903ULL, 
            0x70F129FCC4BF541DULL, 0x180EEA9EAA3B2C7FULL, 0x6C1149FEF58B8BB2ULL, 0x9670FA086A18C42CULL
        },
        {
            0x69E00D56FD1C09C7ULL, 0x5151D5FD3324CF64ULL, 0xE951FF1C72C57627ULL, 0xD2D2EAB5B553D9A6ULL, 
            0xC204348F8F868677ULL, 0x7590995740C1701DULL, 0x910FD3676EAA20A8ULL, 0x1DD154903739C195ULL, 
            0xD027E462773E53FAULL, 0xE1B0254A7C36D647ULL, 0xFE49A23706AB6BCFULL, 0xAC83E5156199C6B6ULL, 
            0x4E03DA00BCE37541ULL, 0x1F3EA13E25FA5D14ULL, 0x66AF65078145F36CULL, 0x6F23CD91EFDA289DULL, 
            0x41A8BAC42F426074ULL, 0x3F597CDFE37871F0ULL, 0x2DEBE9259157905BULL, 0x509412D88ED15B64ULL, 
            0x89EF7779DE8A5BD2ULL, 0x937FFB51B93EB227ULL, 0xDBB56ED62C7F8360ULL, 0x3A3EE7C74CA55370ULL, 
            0x1BFC55E9575281DBULL, 0xF238AC400181BB21ULL, 0x239EBBCDA575EBF6ULL, 0x2EB20CB70370E354ULL, 
            0x1C9BDB9AC2E2CDF3ULL, 0x3D9171745D30F2E4ULL, 0x0F74E4975E69653FULL, 0x287279DA53F3CA89ULL
        },
        {
            0xBDC5A79CE16897F4ULL, 0x470135B8EC0E0953ULL, 0x6FCC18186C15FFDFULL, 0x5A78E5E7956AC95DULL, 
            0xC93FE24924C4BEE9ULL, 0x5AFE321B3810706AULL, 0xE8C94D4294FD7257ULL, 0xDFC41DAADCC99F77ULL, 
            0x6C312866252FAE45ULL, 0xED9038D784F14A20ULL, 0xA999B74C1FA3BF38ULL, 0x249B82E7BCFCA896ULL, 
            0x968F285113EC7BDFULL, 0x987180E0FDDF489EULL, 0xE9D72F53ACC7C12EULL, 0xE19EDCC002ED0692ULL, 
            0xD768C165B98D37AEULL, 0xF375A19D981929DDULL, 0x1954B937C15AE827ULL, 0x4474E129F478922CULL, 
            0x3FA813E15C7A7516ULL, 0xB040CC2B94249D81ULL, 0x6CCFA552F7D62363ULL, 0x2F95D9E1E4DD371DULL, 
            0xB388B06DFB9EE659ULL, 0x541BE0AEF6AD4BD8ULL, 0x372A8A38472E58DCULL, 0xD90F5A5AA88F4960ULL, 
            0xC6AB60A1464FB555ULL, 0x8DFB8735B7A3B783ULL, 0xFFE619CB98C43A04ULL, 0x8CF39E4B4403DD7EULL
        },
        {
            0xBDF6CC216DE0AB40ULL, 0x4236A1160B3755D5ULL, 0xE0D721D39F7CABEAULL, 0x3656FB5E5E1A3F0EULL, 
            0x1BD27ABB65805AA5ULL, 0x531F3EC0107AAB50ULL, 0xA6962F76722A25BFULL, 0x4FC9A9E5232419C6ULL, 
            0x78219FEFDF02F591ULL, 0x6804BAB9147E3B56ULL, 0xC8FEB5A8DE9B44C9ULL, 0x92E0CAE36FD060EDULL, 
            0x3D338571384FE85CULL, 0x42B58D44FAC32003ULL, 0x2C990C22FA012CA6ULL, 0xBD0B50F9A77A4D86ULL, 
            0xBA5296E4503F29C8ULL, 0xCAB950009B43BB08ULL, 0x64AAB0BDD132DF14ULL, 0xBDC7F5CCB13A623DULL, 
            0x1AFBB24DE48AD2FBULL, 0x3BD3ABAD0F3B6652ULL, 0x958DBABB479D401CULL, 0x960F503F01CA827CULL, 
            0x10739158FA36AB69ULL, 0xA09EABD7F3CD9F56ULL, 0x09D9F5B11200B3ABULL, 0x4D593AAB81A0F198ULL, 
            0x32ED39D9203B98E3ULL, 0x9A060A8119BC97D4ULL, 0xABD4363C3FCB2217ULL, 0xFA1FF84AF75E100EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseBConstants = {
    0x0668141EDACD0311ULL,
    0xD62D0DE635BE71A6ULL,
    0xB43B75B4E1C703CBULL,
    0x0668141EDACD0311ULL,
    0xD62D0DE635BE71A6ULL,
    0xB43B75B4E1C703CBULL,
    0x119597E7FC514808ULL,
    0xF5DAB66C1206143BULL,
    0xDB,
    0x4A,
    0x9A,
    0x5C,
    0x40,
    0x8D,
    0x22,
    0x9F
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseCSalts = {
    {
        {
            0xA6B621AC52D2D543ULL, 0x21B3F67BDA228645ULL, 0x71CEDC89E87D04E0ULL, 0xFCD76D2C1F9A2112ULL, 
            0x3D04120577A733D4ULL, 0x3D197B6C83B8C0A3ULL, 0xFB82C4567E67C8B9ULL, 0x6016EC2D8E42B203ULL, 
            0xF06F2B60F44D0692ULL, 0x91C8BAF5B4044E4CULL, 0xCB37797BCC9A6151ULL, 0xC8FE9B9CB665B98FULL, 
            0x7B9E6D0DF038109BULL, 0x4FB9DB1F2CD09512ULL, 0x6E9ECDBBF5300C9EULL, 0xAD6CF65F39C4F45AULL, 
            0x8FD3CD525EAA093BULL, 0x2DE8856E8413B79CULL, 0x6C52ED7B6FC32F7EULL, 0x44F99AA33D685B69ULL, 
            0x00597733D8045CFDULL, 0x99E71501FD670C0AULL, 0x92B5F33DD4756CE9ULL, 0xC7812C8FBAE9FF0AULL, 
            0x06AC9FB3EDA4391EULL, 0xF0B9BC1E37878A07ULL, 0xA9473F771C864A34ULL, 0x25080EC53B78C3F6ULL, 
            0x2AD5B7D79DDE3EB2ULL, 0xF4EF0CFBFF9056BAULL, 0xAF5C9AF733EE17B3ULL, 0x03851FAD79EBAD2BULL
        },
        {
            0xDC2F960A10A98073ULL, 0x2648F034637A5CA1ULL, 0xAD36832978E43023ULL, 0x10843C21433A12F0ULL, 
            0xAEB69BFC222DAC79ULL, 0x927B5A7D5F74574CULL, 0x77D2BBF30A63477EULL, 0xE42DDFFB261D3354ULL, 
            0xE00D1EB73E307D16ULL, 0xC5F118DACD49B7B1ULL, 0x949C80360E7A0C02ULL, 0x3AEAC6290FF29CDFULL, 
            0x64F12F9F11468B82ULL, 0xE47A7B57726F6B84ULL, 0x18909C656A0B4A63ULL, 0x4C5E8B88852CD53FULL, 
            0x97C891B1A57A6243ULL, 0x96343118EE8510F5ULL, 0xC3DF513AF7F945D5ULL, 0xF09E92753B04F7ADULL, 
            0x5ADE2F0B9D92D168ULL, 0x9392481D7D15BE5FULL, 0xD5038255642A3B84ULL, 0x645F93B97B3C426BULL, 
            0x15A47C606FA79853ULL, 0x062E614B963E0BE3ULL, 0xF618C2AD2D1DDAF9ULL, 0xFBB0BDC210414307ULL, 
            0x19F0565B2C208C8AULL, 0x95CFF071E27DD087ULL, 0xB5DD05E3CDAEA4ADULL, 0x30F92F105B834AECULL
        },
        {
            0x967B175C233289D6ULL, 0x43AA599C899B0298ULL, 0x46526A74FBDA83C0ULL, 0x0E79D4D8DF796B5FULL, 
            0x283B2B63A7489B79ULL, 0xA849A005BEBE78A1ULL, 0x92A0EAA6735000BCULL, 0x3CBDCE2EDF72CE53ULL, 
            0x5261F726397F743DULL, 0xB03A12B45432608EULL, 0x6C84517270AE4434ULL, 0xE93FE022B8AF79D5ULL, 
            0x8C2D61F251FE243FULL, 0x8DF607B8D24BA168ULL, 0x21FE47981DEF2598ULL, 0x752C9EED5B9D7FBCULL, 
            0x0E6C119B28F5E4ECULL, 0xD141506418936D1DULL, 0x2B2208D5877FCBE1ULL, 0x7A1BBFF8E54487C6ULL, 
            0x7A0F5AE3484E225EULL, 0xC15ADA13AC0A3B61ULL, 0x17A947BF0A2547C6ULL, 0x18F7AC61A063EEBEULL, 
            0xD554AC58D4271069ULL, 0x066EEBF58C1FE82BULL, 0x7817305F46B6A2DDULL, 0xCA678FE1408320A5ULL, 
            0xAFA009161B93D1EFULL, 0x5C75907A5D289E4DULL, 0x7AB3D13E88456A03ULL, 0xE20103D35F5C23C9ULL
        },
        {
            0x36C63D27FDE78DF7ULL, 0x83F0835633090A54ULL, 0x4DC3228B7C10217CULL, 0xA85AB54E9FE3DA0AULL, 
            0xF7FFD341D070968FULL, 0x840C595CFC5C4606ULL, 0x07C6E95D1AAE0546ULL, 0xCDE62E6E66C5767EULL, 
            0xE17B19E4856BE98AULL, 0x5B9D5FE39893ECDEULL, 0x28961B8C4ADF8DC6ULL, 0x1C9430CE72C5C526ULL, 
            0x93CB7DACCCD2BDD2ULL, 0x758702B9BDA6EF4CULL, 0xF7CBA64A2BBECEF1ULL, 0xD1798374B3A3A93AULL, 
            0x2A908B7D27D7631EULL, 0x6611E41057E6F95EULL, 0x2BE5D8307C7319BEULL, 0x21A0D2CF57C54716ULL, 
            0x09965B30068A59E7ULL, 0x532DE34C843438ACULL, 0x51E60D7D4F5AE6CCULL, 0x3C628D11ACDB15BAULL, 
            0x39054B42BE01865AULL, 0x70A72ED49995BC54ULL, 0xC89EA1E7812AEB4DULL, 0x82E6C6D9C6D42056ULL, 
            0x0AD6C4E3AF992764ULL, 0xA9A58969DD708554ULL, 0x5C9FE9E75E2D4585ULL, 0x86235B554E75A0E7ULL
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
            0xB5B57430F6061DBDULL, 0xF58BC71DEC2F843AULL, 0x7FAF050B5CD2392AULL, 0xED2E32625EE4262CULL, 
            0xEC29B50370738BD2ULL, 0xB117C764C5DB8797ULL, 0xDC8764D94C39A951ULL, 0x405432DB93B4F8D8ULL, 
            0xCFF01958B51C221CULL, 0xB168669D0F6CB4BEULL, 0x6D228E13924E80B0ULL, 0x14C0D877A8F5951FULL, 
            0x3F91744BA0E8C988ULL, 0x859E150D3781823FULL, 0xAF9250E7E95FA97EULL, 0x4FDBEC7926819D48ULL, 
            0x7458E3B1554ADA72ULL, 0xDC8144F62B4A076FULL, 0x79B7E28F1316DAC4ULL, 0x8F2EAECBC95FAA86ULL, 
            0xA0F95FBFFC448A0EULL, 0xC61712B7F3D56334ULL, 0x66C3685B47081A25ULL, 0x9AC73FE1B87F786AULL, 
            0x70776C6FA4C305F2ULL, 0x045EE7A1B2BE5BECULL, 0x790D98AC2C5BD2C0ULL, 0x51951A17D27F32CFULL, 
            0xCE0F543433FFC898ULL, 0xD5D4BF0CD5A08568ULL, 0x2659F5E3C1111901ULL, 0xA3368FF3CBB8BADBULL
        }
    },
    {
        {
            0x6D660A48C27DA018ULL, 0xE98CEC080AD515ACULL, 0x4C650BC7F1970433ULL, 0x4C523F54C3C0ADC6ULL, 
            0xC8A56C98A71D4539ULL, 0xA676D510A78E44ADULL, 0x26455DABA527EA6AULL, 0xC6D27A0A0A130B7FULL, 
            0x40902A5A6DFE6C7BULL, 0x5328BDF3B79BB1EAULL, 0xDCB3A808740CD611ULL, 0x02BA082EEC08AFF2ULL, 
            0xFEAA5A2C310DBB90ULL, 0x8348FECB8A175038ULL, 0xDC2BE6DE975E29A5ULL, 0x25B73646DED8345AULL, 
            0x0F4BBB94A0A1E2F8ULL, 0x5463EADB4E0D5D3DULL, 0xF358D9EA7FBA4348ULL, 0x191DC385AC9F0FBAULL, 
            0x5A318DE6838AFE3DULL, 0xBAC51F22CEFC1B98ULL, 0x91229E602ADC2435ULL, 0x16220B0BD680CDF6ULL, 
            0x15081D949D6EFBF7ULL, 0x025272CE43D37E21ULL, 0x6A41882D239F1752ULL, 0xF751800E601FE888ULL, 
            0x284E5DF1653D587EULL, 0x986A2E6F280FF2AEULL, 0x93908D8EA5074212ULL, 0xE5897E59D0C817FEULL
        },
        {
            0xC2994941101F31A5ULL, 0xD75D1F66B9E63B6EULL, 0xEF37F0027FE40476ULL, 0x85B43ACC20C3F60EULL, 
            0xD65ACB9D09ADDF41ULL, 0x301F7B255ADE8881ULL, 0x3925FB7F00BD3350ULL, 0x73D3EFDDA8DFB25DULL, 
            0xEA1ADC00F04F19DBULL, 0xF1C00BF3076AD9DDULL, 0x1B4E940F19113F46ULL, 0xFDFAA25D1DDF5A1BULL, 
            0xB059E2945ACD40E8ULL, 0x74AE185D46E37FEAULL, 0x22A09B0602008C07ULL, 0x04288FA418A9CB3AULL, 
            0xD5C73BC4ABD930C7ULL, 0x3A22302070A59618ULL, 0x7AB9553301AD9CADULL, 0xE96FB5A4A4D1B591ULL, 
            0xC17B93B37FABDCAAULL, 0x5DB316F72717E8CEULL, 0x027363003B2DB92DULL, 0xAF240DF35D52E431ULL, 
            0x91C0A0189CE73824ULL, 0x5B70D6A8ECB7A3A3ULL, 0x51E78D48140B2E6AULL, 0xFAA4AE3617A9A324ULL, 
            0xD48F56D476277F50ULL, 0x0E8CBC2B22EC9004ULL, 0xF2D6C42EA2B7F4B6ULL, 0x1E4F5A2E011B5E33ULL
        },
        {
            0xCBA6450584CF5DEFULL, 0x5D9B95AAF294AE16ULL, 0x10DC8E75AB29EDB1ULL, 0x59617A3E668F9D41ULL, 
            0xEEA6EF480C804AEDULL, 0x924EE6BB7DE52692ULL, 0x2DDD734325C8BFB0ULL, 0x16A8071560A6F9E6ULL, 
            0x04A680C887261888ULL, 0x71E74159383A0D4EULL, 0xEF985D61FB45109AULL, 0xAD8BC9E38EF9CF15ULL, 
            0xAA02377B7D8BB1A9ULL, 0x4248D61BED682F28ULL, 0x8BBB30F9585CF73AULL, 0xE8C6E17A179E6B20ULL, 
            0xC100DAE2727F8275ULL, 0x0F3C24C78C247CF4ULL, 0xE12638E329214A89ULL, 0xE3F3CFB850010C8BULL, 
            0xE9FF021085D9959DULL, 0x273934395C331850ULL, 0xB5A3088760A2D4B8ULL, 0xF69AA6AED9FBE8E6ULL, 
            0x5C07FF3197DE4010ULL, 0x950F16AC640F65DCULL, 0x88DF5DB7B6499B9CULL, 0xD98F5B85C22D8722ULL, 
            0xC81FECD144756770ULL, 0x09D022A190D0CC83ULL, 0x8B5F6EB1EBB462DAULL, 0x89DF85676C5183A5ULL
        },
        {
            0x418E57D797B809C5ULL, 0x5D105A676813B6DEULL, 0x3ECBA1508F6D7770ULL, 0xC24FA64EFB8EC50BULL, 
            0x39ACBA8038BCB2B2ULL, 0x85393D625CA7E318ULL, 0xFA710507D032C2F9ULL, 0x857AE0DEC7FED76AULL, 
            0x2B7718DCD64489F0ULL, 0x5580AA6A3219AD31ULL, 0x15C37CA33A737DD7ULL, 0xC0E9EE7421664F9BULL, 
            0x8376C635D43DB209ULL, 0x8962BD21E93C9F0BULL, 0x79159E58FC618915ULL, 0xA8CB2505C9484F74ULL, 
            0x6B90C58633A954D2ULL, 0xF27987CBC0FEC7F0ULL, 0x3316A21FAE1A835DULL, 0x92B49CBCBB83576BULL, 
            0x585B1AF8D77297F8ULL, 0x60FFEE92FD3B43B2ULL, 0xE324B5C72C5ABC8DULL, 0x49D00D16CDA530ACULL, 
            0x9D5AB39923F19D0CULL, 0x1625BBEDBA3E0A5DULL, 0xA8691F9CA97F84BEULL, 0xF5446D656077AED2ULL, 
            0x67A852E19573C5ACULL, 0x36C60B6BBAA39A97ULL, 0xD202E7BF726EEE82ULL, 0xC366C5F1E82BCB32ULL
        },
        {
            0x019B573E14DBB51BULL, 0x684674F42B05B04BULL, 0x65C2F4B7046B932DULL, 0xF4EB91CC11879CCFULL, 
            0xF13EEA1A41BFE405ULL, 0xA462824155AF7D49ULL, 0x04F65E86BF4C5979ULL, 0x777448AEA9AE7556ULL, 
            0xE792241EE76AF46CULL, 0x0B3287427E549043ULL, 0x7EF626A3FAA1DDEDULL, 0x8854D18E43F66F56ULL, 
            0x60780A0A7DE9F527ULL, 0x1E68FA3E0B1DA4D9ULL, 0xCFE73135C17EFDB0ULL, 0xB57A02236DCD7C13ULL, 
            0xB9F0BD246EAAF4E6ULL, 0x94FBCD57134FBA4DULL, 0x44A92C764BD77E77ULL, 0x6EA703605FCDCAD5ULL, 
            0xFBA2EC6D342F4BE6ULL, 0x54896D772BEBC77EULL, 0x387640CB5CDC0E76ULL, 0x9A2C152B7576490EULL, 
            0x3AF6BB8FCD47D2E2ULL, 0xC0938E2F39A7A91BULL, 0x9680F97046E4EEA8ULL, 0xA05C284B721A6C3CULL, 
            0x31973C6EB474340DULL, 0xCFCDA7C6FD17084CULL, 0xD583F2A702813A36ULL, 0x04B75072A292425EULL
        },
        {
            0xF190267E241CA844ULL, 0xA6D1CE3E03374B29ULL, 0x7DA9CB61778BC2B6ULL, 0xB346AFF9EC63FA71ULL, 
            0xEE2F34520BA73EF5ULL, 0x6E5293790864B970ULL, 0x89DEFC84FDCDB2FFULL, 0xD9AAAAA6D17917B8ULL, 
            0x06966924846685F4ULL, 0x6424EE8E7A135CBCULL, 0x6306B0DA6F5D205FULL, 0x168D6EE7DC118500ULL, 
            0xB5E7D7305C729791ULL, 0xA30B322A77E5D3CDULL, 0xB9F091DC191EEFB6ULL, 0x2C4E637C06575105ULL, 
            0x540D13B3F0FD2E31ULL, 0x96388731383CAD6AULL, 0x8135045A32289555ULL, 0x407E7945E492C4ACULL, 
            0x422A5772952243AEULL, 0xDBE2089921766897ULL, 0x4A6F3C55CD4C7D28ULL, 0x13632918EC45AB4FULL, 
            0x1ED28B8D8638B4BBULL, 0xF65691E9A90E6D84ULL, 0xB99128B058FBAD59ULL, 0x9D0427DC970F89DFULL, 
            0x8F71E716B944A399ULL, 0xEDFF6290016DFDF9ULL, 0x0CC4C13163C686B6ULL, 0x3D0F8116D2EC4DEBULL
        }
    },
    {
        {
            0xEA38A001A3EC0EE9ULL, 0x6B85F5E5C6CD96EFULL, 0x5B799635D6D71D91ULL, 0xE6FA1CCA35DCAF80ULL, 
            0xCDAE7883BD2E9CE7ULL, 0x87D2423EBD0CED1AULL, 0x61EE40FD9B0B20B1ULL, 0x1470D321F8FD4834ULL, 
            0x2218CD3E193266F4ULL, 0xA90CB1560311765DULL, 0x38F61AAE793E3C66ULL, 0xA31E72438FABD4FEULL, 
            0xFF5FE5B7893BB98DULL, 0x0797F400AD07BE3EULL, 0x1C14FC47E74E47D8ULL, 0x623DFD37159656C0ULL, 
            0xF00E6E04F520DE74ULL, 0x369D4AEFFB62C19BULL, 0xF777CDE81B5B9E18ULL, 0x26B9D25FBFD8FACFULL, 
            0xF787C9967A51EB52ULL, 0x1059EB23A604B712ULL, 0x2C53D509442774D6ULL, 0x2CA157DBF2E6B62AULL, 
            0xCB3F30AC9C7E456DULL, 0xF31D54F3302F03C3ULL, 0x4C366EA549C0B6B7ULL, 0xBBF8A3FE046CF468ULL, 
            0x88B9AD1F07170C8CULL, 0x8B9D53DEE4139451ULL, 0x8D5453930D1ABA8EULL, 0xCB40694B239B567DULL
        },
        {
            0x902CEA6B4BCC4093ULL, 0xBDA2749D5EDEC7ABULL, 0xE74AB825B802A4A6ULL, 0x3EB92D80CD755C4BULL, 
            0x0B650AFF31A9B4C1ULL, 0xA61F7ECCABD1C6A3ULL, 0x2C00080FEB52F5ACULL, 0x32A582174FF7334CULL, 
            0x6F941F91C85345B4ULL, 0xDA218A6F917E3335ULL, 0x7615E04DFBE703E5ULL, 0x83B6158540119E84ULL, 
            0x85472DFEDEBC7102ULL, 0x1EABFAA54EADD66FULL, 0x400F2BB38E40C7BBULL, 0xCDA2489D1EBD5CAAULL, 
            0xF684055B567408FFULL, 0x45C9076D3A1930A4ULL, 0x840E445452F43358ULL, 0x17C33437844E2924ULL, 
            0xDAD44C2E5F4209B6ULL, 0x4E345B8A6C942B5DULL, 0xDF798237F1A87B63ULL, 0xE54CE6714076ABF0ULL, 
            0x4DADB8BC93949EBBULL, 0xC42C02D68D01E102ULL, 0xDA3E2BD76B8F36FDULL, 0x3F9837441EBA33B8ULL, 
            0x821B6075D16E0059ULL, 0x34972C6156676C79ULL, 0x62208C1DAA0674DCULL, 0x599345D6DB84FEB4ULL
        },
        {
            0x70C86DAE4CD4B0D4ULL, 0xC9C5C0E939191680ULL, 0x8972116352C686BBULL, 0xFB3E7C06E6A989DFULL, 
            0xE12747B04926B47DULL, 0x08A36FF1F05D2D9BULL, 0x60BC32C55848546DULL, 0x5D52039C08DDB735ULL, 
            0xCEE869FBD0E4E396ULL, 0x7820F8B68AA462CEULL, 0x34E484FBF46AFBBCULL, 0xEB00F768A6B11099ULL, 
            0x3BB4A92929AC73EAULL, 0x9F6ECA6037158B3DULL, 0x3DBD0DB4BFCB3FC7ULL, 0xAE04C94797D85A37ULL, 
            0x745024F8A95FA22AULL, 0xDB74CA07FA4EACB5ULL, 0x4F478491D48A57D3ULL, 0xCE1A072CAE4BDA8DULL, 
            0x2318E5904107CED2ULL, 0x3583081D3C2C34EAULL, 0xA5D4DFC629F38545ULL, 0x5F8011D6F1D6D040ULL, 
            0x26320D13CB0D0207ULL, 0x3901FB6E22FA05BDULL, 0x3995F9A87BBF5652ULL, 0x24B79F34400337B1ULL, 
            0xF5BCCE6C0A38F223ULL, 0x549C8DAF21E87A5CULL, 0x1B305F9416AE707AULL, 0x81532CD10E6B0438ULL
        },
        {
            0xCDEF2294CEBE46E4ULL, 0x708B54CD6D357EC8ULL, 0x5C0806C20A1C0749ULL, 0x989C89BB07002EA2ULL, 
            0x14780339682FC4E8ULL, 0x8B706AD33DD1B597ULL, 0xFB8C9B5537A8D2D5ULL, 0xE01F405F9003D6ADULL, 
            0xECFE8A6095BB8E2DULL, 0x60CC58CAC0CD5242ULL, 0xEDEF7D200B8A2B61ULL, 0xDD1D411F07CC1805ULL, 
            0x04D1E6627BF270A5ULL, 0xE748221D6AAE817CULL, 0xC2F185EF562912DAULL, 0x254B61851E2BFAFDULL, 
            0x16AD7FCDD09E7D40ULL, 0xF28EEDC8E59F8B4BULL, 0xCDA777F995589962ULL, 0x6E1E43645B6D0D4FULL, 
            0x72D0D7EC640C73E3ULL, 0x7B269C306CA25EB8ULL, 0xB256FA19E8645C6EULL, 0x60C3F3DE4754FD65ULL, 
            0xBB939A6B596BB0F2ULL, 0x7EAB858775400371ULL, 0xCB47E488D7FD96CFULL, 0xFF17F3C726D4E7D0ULL, 
            0xD12A5F182A4CF885ULL, 0x23520481BF4C71E6ULL, 0x436A9D625F4D4345ULL, 0xE426E6C2E731CFCAULL
        },
        {
            0xFFDADCD114B0A697ULL, 0xA10E7FE9D604B080ULL, 0x4C8DA619EF1A3697ULL, 0x70697B22D32749A9ULL, 
            0x58D04EF6B37D2685ULL, 0xE38B0549ED550E46ULL, 0x0B62130904704D9BULL, 0x39D70097E934C740ULL, 
            0xEFCA6AFC325EBFCEULL, 0xAC8A80C5E2887A8EULL, 0xFC0195CE8362F41AULL, 0x36C9EC6B98603530ULL, 
            0x477AE7C8BAC5D317ULL, 0x64E0ECE251AFABD8ULL, 0xD0F3505F83E60CA2ULL, 0x896B698FF98181F6ULL, 
            0xB42B47E1D8318505ULL, 0x9C876555DB4A3C5AULL, 0x25C3FC1F81FC131DULL, 0x2313E6457D9D5B8EULL, 
            0xA675C3329D9435A8ULL, 0xC486A3FEF50AAC91ULL, 0x2056D322E00B7AF8ULL, 0x96B863FF3BC40490ULL, 
            0x408430FBDE810412ULL, 0xC7C14E6CFD524BACULL, 0xDDF2610BBCD592FAULL, 0x2BC1B9E01DA6FADAULL, 
            0xBCD5675CDD59FE69ULL, 0x856F618AA078850CULL, 0xE51B53C3883AE1C0ULL, 0x9270629865D4F4BBULL
        },
        {
            0xF3A6D9047E952DF1ULL, 0xC6D92C4C7F45ED53ULL, 0x6F6615AA5E70993FULL, 0xD57FCEBBB6913F42ULL, 
            0x6B5BABD1BDA6DFC8ULL, 0x7E32A2814C828193ULL, 0x03D8BE239ECDD854ULL, 0x2C96BEDEC823B9A4ULL, 
            0x022D791B4D146791ULL, 0xAF5360FB4BB42A1AULL, 0x64EE8D5F6A2C5903ULL, 0xE07B9455DE43190EULL, 
            0x98AFB369199E489FULL, 0x382CA3D946056D20ULL, 0x84C7B544764575E8ULL, 0x9793142D1DED998AULL, 
            0xA9278E043901F812ULL, 0x3A52C5E5F8E87B0EULL, 0xDD6DE2B0A8938073ULL, 0x91D7DA3D71FD0227ULL, 
            0x6DA3AE156F107EE0ULL, 0x165E1227D114B522ULL, 0x3EF422EA81176077ULL, 0x162B2694255CAD09ULL, 
            0xD917E2FCFCAA98BBULL, 0x6FB85ACA58A90815ULL, 0x39FCCC8AADEDBD41ULL, 0x6966FBA019123B8FULL, 
            0xC92C650FDBBBBD8CULL, 0x106BEABD7D4A93BAULL, 0x482F611DBC5B3A9CULL, 0x36C6606FF8EFC702ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseCConstants = {
    0x507AD9C446F73BB5ULL,
    0x9A4FC6AC43A3B0B3ULL,
    0xEAE16962ABA06863ULL,
    0x507AD9C446F73BB5ULL,
    0x9A4FC6AC43A3B0B3ULL,
    0xEAE16962ABA06863ULL,
    0xB54D4BEFE3999095ULL,
    0xA5D710F8FA267708ULL,
    0xBF,
    0x12,
    0xF5,
    0x54,
    0xFF,
    0xB3,
    0x2A,
    0x4E
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseDSalts = {
    {
        {
            0x54158C210D6B0EECULL, 0x26A6A4688187AF2BULL, 0x5347997B123C13D4ULL, 0x7E8034DDDCECCA14ULL, 
            0xDB9D0B2AC489F649ULL, 0x23BF11A07E33AE23ULL, 0xDCB5E27A3A7A00CBULL, 0xF50E87FD94E59ACDULL, 
            0x2950B0A72EC13E86ULL, 0x239F4BC8B4AB0E3BULL, 0xEA15B7818636E23BULL, 0x2A4BC155B1371756ULL, 
            0x180DB2444B34F841ULL, 0x4539310E5480400DULL, 0x6A63E74C94864D2AULL, 0x0E6B40BC91799C5DULL, 
            0xF5B5E6806212B574ULL, 0x945C4D3823A73350ULL, 0x1EFB90E440C9CFCBULL, 0x272DB3E1B85667E1ULL, 
            0x92AB971B97B5A62EULL, 0x4C4C96529B98DDDCULL, 0x0CABC3A249D00C2EULL, 0x61A81750E80430B2ULL, 
            0x84DD36F6A24FC1DEULL, 0x1538598A3BDEB983ULL, 0x4692948F5742495BULL, 0x44571D1115AC1721ULL, 
            0xE7377BAF707E8CB5ULL, 0x00ED596CC1461DECULL, 0xD8662AEEF1FD75CCULL, 0x2B883E8CC61750ECULL
        },
        {
            0x1D91B09C3B4A4989ULL, 0x59B8843CA0F86D5EULL, 0xC91DBF5C84EBEAA1ULL, 0xDB51E28433E50CF0ULL, 
            0xAE50B232632D88DAULL, 0xB9576807B44F8EE6ULL, 0x0DFE7723DA8908C0ULL, 0xDE9CB130BD105E45ULL, 
            0xFA3C6FB21E6F452BULL, 0x122BC46314E82E17ULL, 0x76D87816FE812E27ULL, 0xEF432A27262D5366ULL, 
            0x04D7F4E9BD07CDDAULL, 0xF4B39EA7BCE225D1ULL, 0x11EC7D3B883E7308ULL, 0x0C3E62D290F5D95FULL, 
            0x5AB15E3379224A31ULL, 0x344EFD56B7A4458FULL, 0x3054E6AAFCF5A778ULL, 0x28030704DEFF3D22ULL, 
            0xBEDC4C4CF0FE3047ULL, 0xEFAF19A8FD06A8ECULL, 0x00C5A6453D87E918ULL, 0x2271BC8F81A10431ULL, 
            0xD710440B5DEC86F9ULL, 0x585850FAB71DBC97ULL, 0xD6EBE9E3533E33E6ULL, 0x1CB18222D00D3E58ULL, 
            0x6A6C0D3AFA5C0047ULL, 0xEE08047BA9B11429ULL, 0xA327B6EDDBE742CAULL, 0xE41E273F155A0F1FULL
        },
        {
            0x0B550DEF24DE0BFDULL, 0xC79B9704212DECE4ULL, 0x460EE9260CA6F887ULL, 0x4313C12EA70B00CFULL, 
            0xFDD3E5DD61C1B049ULL, 0x3633A7DC57047069ULL, 0x760E94A5A3656B1FULL, 0x60D9005D5C84EA8FULL, 
            0xB5B0B6CF3220EC15ULL, 0x5466EC48B9B8A292ULL, 0xFAB1ADCBD6DB2004ULL, 0xCBAAE1BFC247C4ADULL, 
            0x34433CB8BA00CA78ULL, 0xD7C52A0E8F35A462ULL, 0x27F281AB5FEB942CULL, 0xA6DCF2A46EC39C23ULL, 
            0x25BFFB396D080C25ULL, 0x9A2FCF71B483EA17ULL, 0xDEB5D4140210F624ULL, 0xBA5FB41AA1B9DA91ULL, 
            0x60137A269E88E05CULL, 0x027C01FBD6BBBB0CULL, 0xAC85FA98935C1A8CULL, 0x5FB2BE10D15C8000ULL, 
            0x66A15607B6B7A3F8ULL, 0x9F4F8E05FE03E6D5ULL, 0x317DA2CD51B68AE1ULL, 0x9A335D6325A4931FULL, 
            0x6BD0286D5A92B6F8ULL, 0x7ADCBB458DD19674ULL, 0x2D148FEEEA628CACULL, 0x45EB8DA1FAE2D01CULL
        },
        {
            0x32CA912AA7B53FD2ULL, 0xCC0CF8B5AB555E2FULL, 0xB76584DADEF1306DULL, 0x63BF1C94A015486AULL, 
            0x0FF1B6B3A159905EULL, 0x45A073A2B0CDCAC6ULL, 0x63EB91A49C252B23ULL, 0xDE956D7E0B6C3342ULL, 
            0x69711FDF38211D7BULL, 0x8214869591490539ULL, 0x9F269F06D580BF31ULL, 0xB11C2A297EBB6F3CULL, 
            0x34CB7981D05ACA6BULL, 0xEB9E04F65FE71B50ULL, 0x2ABC745D9BE66F6BULL, 0xD4FFC8F5C5225DC5ULL, 
            0xFA63F1E5B102B35CULL, 0x9C2816EA8EB134F7ULL, 0xA97ADB9A0E21E7CCULL, 0xCC897D5CF268730EULL, 
            0xF61C7793CEE81838ULL, 0xA1468B145106D6ACULL, 0xAB145ED584CDF920ULL, 0x0EB43DC324BC4AF1ULL, 
            0x0D811DDF6DB05570ULL, 0xCCA92A4F8106C765ULL, 0xD49DE4A1AF47D1EFULL, 0xEE9575108D065261ULL, 
            0xC41EFCACED35DD66ULL, 0x83645A10437F97BEULL, 0x8A607CC294EEF304ULL, 0xE8F1FD1C9C4173D7ULL
        },
        {
            0x7FDCE5FC29FD4C3DULL, 0x4DCDDB89E274048AULL, 0x02E15C72F0EB666EULL, 0x7187DD1A88A48321ULL, 
            0xB84935626DAE2F32ULL, 0x3715CBA57AC691EEULL, 0xB3562DA4B5A6D655ULL, 0xA879679079A3C427ULL, 
            0x982FBF8782C2D3CCULL, 0x933855CFD8EB8106ULL, 0x5A1E6CA00309511AULL, 0x621D11BBA32826D9ULL, 
            0xAFF59D769C14AFA9ULL, 0x700063F4A654E0ECULL, 0x9966F8D561396C3BULL, 0x25F0AB9856FA33C7ULL, 
            0xF717830029CD5586ULL, 0x1B6F21CBF9125F10ULL, 0xC12BFF4644EB2FF0ULL, 0x0164CC3F9D787395ULL, 
            0x85E4BA80835642A1ULL, 0xD8D2C9BBBB79728CULL, 0x5FDB6DCA951FF12BULL, 0x17047F6731AD4529ULL, 
            0xD367B481E36AFC3CULL, 0xA504770C59026736ULL, 0x5F2A473D5DD32C97ULL, 0x5B3AC85EBB76DEE6ULL, 
            0xACCF1A957009F4BDULL, 0x0E7CA7D22F7B8119ULL, 0x4B6DCAD0CA0BEC3FULL, 0x302218858F03E5BDULL
        },
        {
            0xD5F1B6020BBD0EA6ULL, 0x5DBD1B78F131A2F5ULL, 0x6B2A180DD45FE2D8ULL, 0xD81939CDBD64604EULL, 
            0xCF3D794785AC1CFEULL, 0xD200665E184F1E53ULL, 0x38181F0214C532C5ULL, 0xD057B465205BFE75ULL, 
            0x57A6AE33FC82B4FCULL, 0x1882C00D83AD1CA6ULL, 0xCE89A9FC224459D3ULL, 0xC2E23C5B5875F6F1ULL, 
            0xD962DB62858A8B2AULL, 0x84AA7D0CF1F6F605ULL, 0xC0984383D23A7A62ULL, 0x02667AB4289E57FBULL, 
            0x6C35D6E4187BCAE1ULL, 0xE431845A25D38C88ULL, 0x4860D275BB54C6BBULL, 0x01F8D8B8CCE94165ULL, 
            0xCF3A3048A49B2435ULL, 0x9BB92C03F94486A2ULL, 0x287D6B02C955B20DULL, 0x40DD6611DB38F2FEULL, 
            0x33730CE4AE16ED82ULL, 0x36E31FC71438C855ULL, 0xDE1CAFB02E8979F4ULL, 0xD06B63055A74FEFBULL, 
            0x5BA50D3F3123DDFAULL, 0x96D4006A0A762E73ULL, 0x5F90FC95C45D7F0EULL, 0x4F99575F7C50AFD2ULL
        }
    },
    {
        {
            0x99E4D49BC9278E99ULL, 0xEFA28EE0BE7F5320ULL, 0xCBE6081659AC2374ULL, 0xB6B9AA1A4D02C8A2ULL, 
            0x1D37C6982E8944A8ULL, 0x163A4FF764AE1ADEULL, 0xEC3B441DCFFBBB75ULL, 0x3C9DF25D7BB32798ULL, 
            0x2E8CC879372A7110ULL, 0x197A9F193C25974FULL, 0x7001BA9309C2DE66ULL, 0x4B00CCE10B279F99ULL, 
            0x1C8BBD421184F578ULL, 0xE0B3DA25A7029946ULL, 0xF51094927C1638D2ULL, 0xD591DFD135E8BD7AULL, 
            0x3F3307D2B52F15DAULL, 0x969389D2B8BBEEE7ULL, 0xB2743255F008A177ULL, 0x6FA3D01E229ACC2DULL, 
            0x306809BE961C273EULL, 0xD538388541FDF123ULL, 0x5FC4BDE6B64916F6ULL, 0xF577796A88ACA585ULL, 
            0xAE63BB60199F564EULL, 0xACBFAFF6EDCAEA5FULL, 0x38FE1138C24187A2ULL, 0xFB9851DF35010A13ULL, 
            0xBAEF5FD318CBD7F7ULL, 0x2D0430748584D9EFULL, 0x0F038FDF15F49F91ULL, 0xC130D90D8958B1E8ULL
        },
        {
            0x8623130933885CA1ULL, 0x1D3F450B211291A6ULL, 0xB14FD48CD58A5900ULL, 0xF0E6834561A515FFULL, 
            0xA4CD31A079BAA3C9ULL, 0xD25A24B7A151D7BEULL, 0x9BB8C2BC8C3E8745ULL, 0x2E23B0C9BFF92B1EULL, 
            0x082BCDD7F5F58C0FULL, 0x14BC43594E61120BULL, 0x15336A6FC9EC723EULL, 0x549B4DB45091EBE4ULL, 
            0xD3ECE24678969ABFULL, 0xCACF6E08B137DCB4ULL, 0xF53A7A4725D32982ULL, 0x8E4A2AA8CF5CCA37ULL, 
            0xB81B2FD0302C23CBULL, 0x84E8BB7D40E39D5FULL, 0x9C5C44A8DDE020EFULL, 0xA4A4512095B85BBFULL, 
            0x9A3B19179F76A827ULL, 0x471B8ACBC8CA83D1ULL, 0x9E7F6AEE41A5EF2EULL, 0x676E0EAA71ED8767ULL, 
            0x158260D66ECFF219ULL, 0xF37B71C5E0F1C51DULL, 0xFEBBAB2B7AA5B3E8ULL, 0x86B1BBA2CB7FDA5EULL, 
            0x8E11BDED87F3A224ULL, 0x6178D41C1D05ECBEULL, 0x1C45E758BBDF6DF7ULL, 0xCC2C9ACBF5495CB0ULL
        },
        {
            0x10A834D3B47C353EULL, 0xA0A65C6C24E306B0ULL, 0xBA7B1AAAEAC205B8ULL, 0x84282E2BD20AC746ULL, 
            0xE48DF01EB0240F33ULL, 0xA2DBB81E4747BD93ULL, 0x5378D679D916455BULL, 0x6D7C427BBA993B60ULL, 
            0x0402491EFC76F0AAULL, 0xBC26E893CFC7BB43ULL, 0x80848D68E49BB9ABULL, 0xEF799DADD7576435ULL, 
            0xFF7FCB56EF52D871ULL, 0xE2FDFA18EDD016A7ULL, 0x97D3BFF970034509ULL, 0xEB9A4E1B3E81CB3BULL, 
            0x4981021C2DB29054ULL, 0x61BC5C0531EDCC1FULL, 0x3CE17459CDA9F9BFULL, 0x1FDE6F9108C8B71CULL, 
            0xEB2130237DA99AC8ULL, 0x5BDE3C4540B801A2ULL, 0x0385A581BD9FFE9DULL, 0x7036B3059D6ECD97ULL, 
            0xD4BA118C36B6E859ULL, 0xA82D636523277E1FULL, 0xD23630BBD3C41E8CULL, 0x1F9FACA590D2B4F1ULL, 
            0xB77854FDDB31D6D2ULL, 0x151F68B244C82172ULL, 0x6E719BC1D958E7D7ULL, 0x419621211DF9596BULL
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
            0x56D097CC8D79CDC8ULL, 0x54C319D9FC7C98B1ULL, 0x9F65B43F97AC1FE7ULL, 0x53D752A89C210C74ULL, 
            0x6071027ED551BE7BULL, 0x53B2689EDBBAF106ULL, 0xBC1D1D816B7A8BF4ULL, 0x25B7CCEC586075B1ULL, 
            0x433F54B9B52E3855ULL, 0x0C058C10A8D3E614ULL, 0xF15C66C7FA97BBE8ULL, 0xDEA271624B514803ULL, 
            0x6B2BAFE32EC8CD8EULL, 0x60C90DC4CEB9F7EFULL, 0x481F93972802C616ULL, 0x773B62B1BF410C4EULL, 
            0xCBC4F83C2DC5891CULL, 0xFC3E727A46D375DAULL, 0x10F26405B883445AULL, 0x85204A5D62498013ULL, 
            0x5483497D52A7C8AAULL, 0x2C7F600AFC13DA5EULL, 0x7EB8E8DC2A1646E8ULL, 0x0F7DEE6E1FF6AB31ULL, 
            0x7EA1DB1AF3A032C3ULL, 0x601DEFDAC002E8E1ULL, 0x1AA2BB2417B455CCULL, 0x648B554A2459464FULL, 
            0x566DA4D7D03BA3BDULL, 0xE4E70ADDEC6AC61DULL, 0x6D61ABA3337DC89BULL, 0x237BA920E669CCECULL
        },
        {
            0x40562C38777E4854ULL, 0x77DD633028068FAEULL, 0x4A2A7271E8655C4DULL, 0x2B47279A127DA622ULL, 
            0xD05E2C622A31A5A9ULL, 0x57FF4CA591D76A21ULL, 0xC52992CBFC773508ULL, 0x1CB08B107C456B53ULL, 
            0x72EFBB8619C7C827ULL, 0x48D565C78051C55DULL, 0x17994830D49E3EEFULL, 0x6639DB226DE8E1FDULL, 
            0xF59F0D441A5FDC5BULL, 0x5BD2CD84600C069CULL, 0x2F1A728A70E80D0CULL, 0x7BD6CE76D583362DULL, 
            0xE7DE51037AA5C97BULL, 0x5F2854151F7E7B12ULL, 0x31E44A8E931D899CULL, 0x8C2FE6DB50B5A8E3ULL, 
            0xE018E866338AE998ULL, 0x14F5B33EC41075B4ULL, 0xD6EB8A3BD1E190B3ULL, 0xFAB84D8E24ECA959ULL, 
            0x0977CCCF31784CEFULL, 0xF1BC5FA727DBCB52ULL, 0xDBF10E20A70A1F84ULL, 0xCC938455D466CE44ULL, 
            0x1E727FD3C26D05A6ULL, 0xB42E487B878CD705ULL, 0x8905CFACEB40A292ULL, 0x1501925B0B8E3DEAULL
        }
    },
    {
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
            0x8CAA7573B8AF7A4CULL, 0x13BB7896D27EBB99ULL, 0xE4B8BC20737B40E9ULL, 0x1D64B81A5E530433ULL, 
            0xD83F168DD0220C3DULL, 0x0CB23DF56838446FULL, 0xA248782BE06E2D38ULL, 0x02542BBA0FCBD3E9ULL, 
            0xE702A53599CDB824ULL, 0x0EEA06A02FEB2327ULL, 0x792F754927312637ULL, 0x309D07B63C4FC7CEULL, 
            0xB92B740BA7C78C87ULL, 0x9FF099444B2CFACBULL, 0x9E1EBC54B7F7B5D1ULL, 0x4C79DDEF9E05BC1FULL, 
            0xD8877D54B9525F50ULL, 0x2BF07D685917F58AULL, 0xAEE315D5F578A794ULL, 0x2B974F45D867F710ULL, 
            0x8E5D10F4CA54D1ADULL, 0x5A637E8728A50296ULL, 0x6FEDFE575BDACBACULL, 0x63E72E2DC84BE3D4ULL, 
            0x606D24C5F615218EULL, 0x7241C66BDE71F5CAULL, 0x77432A2E93BEC8E1ULL, 0x902056C5EE6700C6ULL, 
            0xDD882B92AF1D3BEEULL, 0x682C4A0B191C6F06ULL, 0x5CBF79AD8EBCE730ULL, 0x8CDF7C5765E2E9CCULL
        },
        {
            0xD4B9F34B36DD0EBEULL, 0xC775ACAF56E81BFAULL, 0x38BB0D3374BBE754ULL, 0x0E8ABF63F1F2E494ULL, 
            0x5C212D361247BCA0ULL, 0x81E2C292615FE7FEULL, 0x577FD868286504DDULL, 0x6071DF3A7FFA52F4ULL, 
            0x6EEFBABB27C38400ULL, 0x6FB575B70C657F01ULL, 0x04474E672B19830DULL, 0x3FAA6C3104528B9AULL, 
            0x8EF491CC9518A018ULL, 0x0F361DD65997E6D2ULL, 0x75E6632912E5A595ULL, 0x05BD38D428323EADULL, 
            0x6AA5821D0976AAB5ULL, 0xD443F85E63FCA409ULL, 0x339EC9511C45955EULL, 0x15AD7E9804BB4167ULL, 
            0x684682F60437F7D9ULL, 0xCA2D0441945013AAULL, 0x1615213F8ACAE4ABULL, 0x9A18A48E893E3504ULL, 
            0xC857408D5DB7CC02ULL, 0x1F923E3401D1C0F9ULL, 0x9E6CBFD282B75803ULL, 0xBFEEE801277DC1DBULL, 
            0x54B188406F430096ULL, 0xF8F837B75C8A1E89ULL, 0x76A8B496ABD95827ULL, 0xA17F338001A2E88CULL
        },
        {
            0xECF3DDCA2FBD3246ULL, 0x7898C3A7B03F32EEULL, 0xEE25AAE2FEC51643ULL, 0x427BF74F92EBECD6ULL, 
            0xB27BEEAF09D36C64ULL, 0x9686F1AE78A34E8EULL, 0x6BF8963CA3E0BCB4ULL, 0xA78C1D0D226C2565ULL, 
            0x41BFB45A3D2A3361ULL, 0x8EC20EAEE6C5A358ULL, 0x1FB797F63B4F5165ULL, 0xE5F907EF928D14A8ULL, 
            0xA7DFBF2CD0CA3D3FULL, 0x223B611ADF70B603ULL, 0xD90D7CE9F93E7BE4ULL, 0xBE67A0A33325F7FAULL, 
            0xA37985A150250F3AULL, 0x7D9A0CAB70BF4B8EULL, 0x8B90EABE92195312ULL, 0xD823F6DE050BCB35ULL, 
            0xC1B36A61C773D31CULL, 0x45C069FACDC86AE2ULL, 0xBDBE90C8A43FC2BFULL, 0xB793FEEDB13E943AULL, 
            0x4D0C8DFE5DA7EBBBULL, 0x0ECB0A24E271528CULL, 0x3D7F873CF1DB57ABULL, 0x2D4D3CFFF6A540FCULL, 
            0x900A9AAE181903C7ULL, 0xC854829A5F352848ULL, 0x5CFC3A8EB56DD599ULL, 0x22D28326CD26969CULL
        },
        {
            0xEF9291F20467E50EULL, 0x684C8661DE4FBA72ULL, 0x99A45E81BB176247ULL, 0x94B0BFB93B225736ULL, 
            0x4577DE7E543D2EDDULL, 0x9F035248EE653AB1ULL, 0x817BE259CB516A59ULL, 0xD7EC9311312FCDFBULL, 
            0x2E800AF1E73F0B02ULL, 0x182848D981CD3FF8ULL, 0xF1BEC1E4F6E1EA7FULL, 0xAE1AF7F495BE3934ULL, 
            0x59BBE7D6C21248ACULL, 0x8F0CDDF4C1EF0506ULL, 0x573E16BD999325B3ULL, 0xB4DA48F65D54DF6BULL, 
            0x26FAD9701C50BB5DULL, 0xAD7A9AABFFA7A558ULL, 0xFBCB00CABF9F9DC9ULL, 0x96B7664A2C57FEEDULL, 
            0x5D2BFEDDC60F20F7ULL, 0xA27861AA1DC840BDULL, 0xA13F08589EA9B931ULL, 0x06491480DDF0F40BULL, 
            0x22E2F965C2800E14ULL, 0x522B7D5998B7CF76ULL, 0xE381E74EEA60AFE3ULL, 0x104C1751948ED729ULL, 
            0x6E7AED8069A506CBULL, 0xDC0173D1699C7021ULL, 0x02677B6EFB29A87BULL, 0x9B6F294E409D7634ULL
        },
        {
            0x245493AFC2C24B26ULL, 0x3FE48B3E702E7467ULL, 0xC8A886F16FEAFA9EULL, 0xAC617D4F9A16A588ULL, 
            0xC2D67C0FB04569F1ULL, 0xB5375672EA644484ULL, 0x37AF4A836B71DB28ULL, 0x51F78D370F8D9053ULL, 
            0xE3217012CDB199D3ULL, 0x73666D6B5FBE14E7ULL, 0x1E50C81A19AA21C9ULL, 0xF0747E7E51FD1798ULL, 
            0x74BA2943C28A3025ULL, 0xC001C21EAA04C408ULL, 0x098AB64187FEBF12ULL, 0xF29DC19C1A6ECF72ULL, 
            0x76BAC913A598F619ULL, 0x82211957A3130C72ULL, 0x6DBE310D549499EEULL, 0x1E1E243E0A827E7AULL, 
            0x0549716D4574A14CULL, 0x8D5C7724EA8E82B1ULL, 0x3F2F93F59BE6BB62ULL, 0xBA7832576C1DF899ULL, 
            0xD72E34BFDE782E2DULL, 0xE55654E72AAF4EB6ULL, 0x61DF711F9733E4F0ULL, 0x64E7B3D0B398D1F8ULL, 
            0x814BFA77F970E817ULL, 0xFE32B51CEC029BFEULL, 0xAD34E8A8D0FAC3B6ULL, 0xCAEB6C46629F5762ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseDConstants = {
    0x4F22A866F7D1FD8CULL,
    0x9A62D6B6A6FE651DULL,
    0xFBFA93593A6B83CFULL,
    0x4F22A866F7D1FD8CULL,
    0x9A62D6B6A6FE651DULL,
    0xFBFA93593A6B83CFULL,
    0xBA440C9EFFA9D053ULL,
    0xBCC90AE46AD5F249ULL,
    0x8E,
    0x6C,
    0x11,
    0x9A,
    0x6A,
    0xA0,
    0x79,
    0x15
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseESalts = {
    {
        {
            0x96661BEE4586D25CULL, 0x18AE749ED03454B4ULL, 0x93645E20FA1E204FULL, 0xB242307AC3DD180DULL, 
            0x55487F59632069F2ULL, 0xE09B5267877DD0AEULL, 0x4751BDF95D377F77ULL, 0x3902C73C19691404ULL, 
            0x373BE4AAEBAA2F87ULL, 0x61B602130DA9624FULL, 0xA6FFC6D6D3492274ULL, 0xB978403EA7A18C87ULL, 
            0xF76A36EBFC4338C7ULL, 0xE29F4B588D127E2BULL, 0xCCBC4F10B2128A52ULL, 0x8787F7E17C7AC66DULL, 
            0xA54D59CA57AB2AFBULL, 0x336708FD36FDEB10ULL, 0x1BED88527B2C87F8ULL, 0x543878DF1412197DULL, 
            0xEE657FFC1510F61FULL, 0x356DFDC13A51DE0EULL, 0x2D47E718B71E4768ULL, 0x44BDDE1CD6A3A79CULL, 
            0x3183D05DA8E813B8ULL, 0x5C19EEB614C2AFC2ULL, 0x2633FCD17CA89C13ULL, 0xA44994D59BF8114CULL, 
            0xB2EDDFDA27631710ULL, 0xBC9C229F8CF9141DULL, 0xE9F7EA8220A7A34EULL, 0x20084968B7424C06ULL
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
            0x9695506535A11956ULL, 0x2F8C1E3292E770CCULL, 0x5543094BC20F5EF6ULL, 0x3A0F82B51E35BED9ULL, 
            0x0050D14B4EB60866ULL, 0xA51FF86E961984BBULL, 0xDD12207E0D9DFAF0ULL, 0x4D9FB4F3498840DFULL, 
            0xAFAD2406F478BCA2ULL, 0xC675701FEFD104F4ULL, 0xD32776A14A3100B8ULL, 0x01F6C54D6D6FF33EULL, 
            0x655EBA47BA09EF5EULL, 0x45A18D9E136EA355ULL, 0x8C468B3CFA5E2399ULL, 0x5C08B8C9F7669F4AULL, 
            0x04616D3614249533ULL, 0xE7F68933BC0BE8AEULL, 0x6D674B4F693DF0ADULL, 0x9E097CBF2162C927ULL, 
            0x218B84069D6F34A6ULL, 0xABE15E34BBC40330ULL, 0x59DB829773B4AB6FULL, 0xAD2C93E9E6093613ULL, 
            0xE702AC3D2CDD58ADULL, 0x1703C036CB189F4AULL, 0x77C164C3CADC9815ULL, 0x92E33F3EAF507245ULL, 
            0xF42EE6557A2FEBDEULL, 0x48FB6FEC4B57F20BULL, 0xCE8E97A58C6009E3ULL, 0xB584E352D77D1B19ULL
        },
        {
            0x634F790467A50F27ULL, 0xDD95647859E47373ULL, 0xE6B5DC46E8E06580ULL, 0x34C552B31A8EF802ULL, 
            0x369DDFF69BFE14F7ULL, 0x142D0F9F5537B613ULL, 0xCFA9CDAA439F36EAULL, 0x68494A558A6B444DULL, 
            0x20B0795DCF91FD6DULL, 0x67EDBB07A79E521FULL, 0xB6F43EB8C911600CULL, 0x19EB1B42EF8D711DULL, 
            0x9FD247CF544308FFULL, 0x47FC3DE87C6DA46DULL, 0x6D26DE07E95427BAULL, 0xC05A5423BA67D50DULL, 
            0xCFAA8EBD7470FF2EULL, 0x06672AAE46FA9C3DULL, 0x703040E0BB260CADULL, 0x7B48D5D83827A9A0ULL, 
            0x6E965CBF0EAC51EEULL, 0xC5B4F00351C14856ULL, 0xA24B276DEEB00B95ULL, 0x33F54B53FECD7C20ULL, 
            0x604E51A304AB3905ULL, 0xBA44412408639FD6ULL, 0xDDCDFF48CBFAE7CCULL, 0x0051C933610D4EDEULL, 
            0xACC45BF8E38828D7ULL, 0x2069F74DC8448E92ULL, 0x8270E37EF1460652ULL, 0xB8783685E039C69DULL
        },
        {
            0x35651269FD31FBB0ULL, 0x8996D9CF908FB3E3ULL, 0x649738E873940511ULL, 0x666127C3C1028965ULL, 
            0x0B41223FA36358A4ULL, 0x988522B329FC466AULL, 0xF08C26978CE8162BULL, 0xC827A3D8AC4B1B32ULL, 
            0x002710884933BA72ULL, 0xCFD60D0681D79297ULL, 0x283DD5F2F9E4A86BULL, 0x3F224305707403DFULL, 
            0x03F7EBF9E5885761ULL, 0x2DE7C6711D700028ULL, 0x2703E984F9C93F28ULL, 0xD97577BBBE9105B1ULL, 
            0x16F5D5FD12C684D5ULL, 0x1D2498E6436A6ABBULL, 0x1BF7BCB9568298A9ULL, 0x41312710AE48F462ULL, 
            0x4362EB45C7AB98D6ULL, 0x486BDEC6D13E1A7AULL, 0xCCEBEAC2C452B921ULL, 0xC9196A5C255E59A2ULL, 
            0x66B919DBC8DA4A93ULL, 0xC42C15A1346FF982ULL, 0xA3F6095FB2F8B56AULL, 0xEB7CDBDE0340F431ULL, 
            0x86186A42DF2580CFULL, 0x33113BFE3CFDAE7EULL, 0xC59EBC2DE1F4DFCEULL, 0x5BFE13CB61AAC560ULL
        },
        {
            0xBBBC06216A134CD4ULL, 0xCC69D7E158166729ULL, 0xAEE13B5B05E8C4C2ULL, 0x7369EAF2F11081ABULL, 
            0xAF786132D3133520ULL, 0x637FA04BBEAC3134ULL, 0xD1C5EE6C137E10E8ULL, 0x5817528460CE55B9ULL, 
            0x2DE487B2E5CA7F20ULL, 0x7F0681A9B295936DULL, 0x43F27A0D91DF8067ULL, 0xCABCF81AD0C1D299ULL, 
            0x51A90E545A58D32FULL, 0x6DC94D2FC62BDE5FULL, 0x74E8081BAA82AA26ULL, 0x322C767C780A2366ULL, 
            0xAE9C6BD8E5B9E8B1ULL, 0xA57A7F4250254FF1ULL, 0xA5F025869474FC4FULL, 0xAC49737A868E142BULL, 
            0xD797F336F922A347ULL, 0x3874BC95FDA85C1DULL, 0xA40942EBA04BBDBBULL, 0xABEE5BAB8AEFE119ULL, 
            0xD1012E22EF2D458BULL, 0x74E010A721BDB78FULL, 0xE1C9FDA5B4C51A2AULL, 0x5CCF6A558733A6CAULL, 
            0x263A1AEB1B904B13ULL, 0xA9A73705D9AFA077ULL, 0xF7963FC4317FEAACULL, 0x7CDF9C0051F0ADAEULL
        }
    },
    {
        {
            0x0D29DA85F6F66780ULL, 0x457C3D8C8489C9C7ULL, 0x860CF2001D610468ULL, 0xA1D73F68CA63138BULL, 
            0xBF6A9383188BF5F9ULL, 0x2C224DC88BDD9D37ULL, 0xBD195FCC2797A3DAULL, 0x82DDB24DA5CE8004ULL, 
            0x8CBA554B8C117140ULL, 0x7A88695763E6E642ULL, 0xEDE9B336F1DADFB6ULL, 0x875596E0E2A223DEULL, 
            0x8CF7533A23A168F2ULL, 0x2165E9D9726FCD64ULL, 0x0564551AEA3870E5ULL, 0xE1A83D3A308A0467ULL, 
            0x8657390A642ED334ULL, 0x8DD095B8E4FA1BD3ULL, 0xC3AC20EDA93594C2ULL, 0x7B68320BE8009EF3ULL, 
            0x720ECB561B5F1D94ULL, 0x7377325A17BD92CDULL, 0xA649CC5F4A81989AULL, 0xF919B9CCFC748400ULL, 
            0xF6C38FEF01759D15ULL, 0xDD9D9460637839F9ULL, 0x3186DF6487A41E9BULL, 0x5FFEF692354996FCULL, 
            0x5254DEC2BD8EDA14ULL, 0x559FE8414AA8E7A5ULL, 0x96E062117C9E04A1ULL, 0x905FDFC170ADBB86ULL
        },
        {
            0x397C10C322CD4C23ULL, 0xA4132AD2BD9173BFULL, 0x0734AC9646891172ULL, 0xF54677AE5D2C318BULL, 
            0xD07A1BFD67C84AE8ULL, 0x2DBBF8E98DC1AD88ULL, 0xB1F6B6C9DC73F911ULL, 0x464159EB34E2F3CBULL, 
            0x204FCD50C3B1800CULL, 0x00B5D6BC6EB89B9FULL, 0x543E477F3E869F64ULL, 0xBE38FCD12B432BF9ULL, 
            0x02346E3AB9DF6EDEULL, 0x864A1FC1A222F323ULL, 0xE834743C80983287ULL, 0x1E3ACAE47E68F252ULL, 
            0x255DE10F4643C818ULL, 0xE050638B24004978ULL, 0x1D2440E5A3182D46ULL, 0xE5CAA2E0FAD64A04ULL, 
            0xE067BB6865BEBE66ULL, 0x72A8432979E7F6EBULL, 0x58E11EE7928C49EBULL, 0xD598320003396921ULL, 
            0x19D2EC95A83FBAF3ULL, 0xB75F4B401C4F3789ULL, 0xCE34443CAC292E72ULL, 0x8C36D0D064896DD3ULL, 
            0x0BA05064DC450D06ULL, 0xCA3108CB886AD5D0ULL, 0x1E371C8946C4046BULL, 0x24C426726F0A1E68ULL
        },
        {
            0xCDD5967EAC4A02D6ULL, 0x769218C8463883C6ULL, 0xBB29A8F446E06D51ULL, 0xA75A701B6B799F10ULL, 
            0x8ABCD0B404572A7FULL, 0xAAA15BF0C6513DFEULL, 0xEB28ACD3246D9493ULL, 0xF0B897F33FCAB7DBULL, 
            0xDAAD9BC2759CF509ULL, 0xCCC0C14F9B4CC14CULL, 0xB924BEB169D2E444ULL, 0x2A24CA05129A05FDULL, 
            0xC8F3FE1238F53E27ULL, 0x46DB7DAE6565772DULL, 0x2FF4208A9F77CC18ULL, 0x9ABD86C7B8019C39ULL, 
            0xD38EA5437A4B22D5ULL, 0x0A55547C80617846ULL, 0x3A8D7981CE51F098ULL, 0x4019D8107C9D74B9ULL, 
            0x73088F9722670A89ULL, 0x907ACD0DC05109A3ULL, 0xAB047A483557B637ULL, 0xC413FD244D26BD52ULL, 
            0x9515E3BE5E075D0AULL, 0x8336AD3497A2CA34ULL, 0x4DF9CBF282317310ULL, 0xA583C9FBE9DC60F0ULL, 
            0xE4174C715A49DCB0ULL, 0xC0EC1043A48E6298ULL, 0x55A7C72D40498CE7ULL, 0xDFC1A7D782CB56F0ULL
        },
        {
            0x2E07D8AAA740F5ACULL, 0x3ED3E30D2091FDC8ULL, 0xC6DA4996FA284974ULL, 0x2E7136920F48A8D7ULL, 
            0x64F0909B6206523BULL, 0x2E30ED16EC38EEA9ULL, 0x64B31C98B5DF8A53ULL, 0xB978424FCE2A652AULL, 
            0x288E392EE19B9A16ULL, 0x3FC4DC498FCC8292ULL, 0x59BE61EC91408DA3ULL, 0x7274E63AB2D4DC1EULL, 
            0xED0CB08F18B95924ULL, 0xEC1D9A0EB169CCF8ULL, 0x92719C22BEA02B6BULL, 0xE2544E393E0B3509ULL, 
            0x734F532974FCF9D5ULL, 0xA9743721D770E475ULL, 0x546A6E6CDBEBAB6AULL, 0xF96FD760525B0D8BULL, 
            0xB6AE2660186D06F8ULL, 0xECC90E49375700A9ULL, 0xC9F30771394779E8ULL, 0xA9143608BF55062CULL, 
            0xDD923D2943980343ULL, 0x8D5F969E7942C7B2ULL, 0x320699B92886C724ULL, 0x389C7C46FECDBD5DULL, 
            0x15C7370767E85700ULL, 0x08CC0DDACFA004EFULL, 0xAF13085C7669D607ULL, 0xDA2166E8CBBB9EC0ULL
        },
        {
            0xC31AD4C568D11043ULL, 0xF3D832192BFA2866ULL, 0x781520A7CBF4D70EULL, 0x9F188CD350BEEB37ULL, 
            0x364868614196C3E7ULL, 0x44D7732EC364AA4CULL, 0x78C3789DECC6F559ULL, 0xC73AEA71F3608FAEULL, 
            0x661A917BBE524FF1ULL, 0x7998515FD4DBAD30ULL, 0x190410578DB07416ULL, 0x4ADF715A3311B8CFULL, 
            0xDC0664B44D401D6BULL, 0x4D0D47634D74F4A2ULL, 0x01C10CB0B392746FULL, 0x6ABF9005EC79D90BULL, 
            0xD33A23C3327618C7ULL, 0xAA0CED7FF0E650E9ULL, 0xD9FEA2C9D83786DDULL, 0xDBC546F13EFCDAAFULL, 
            0x53254E46A0727552ULL, 0xE1C758A8D79E2A14ULL, 0xCE65FE8F70433BEDULL, 0x2CE577C51B7BEA91ULL, 
            0x8E8E0F87F04B0173ULL, 0xAB5896E41062C0B9ULL, 0x631BA0F38A867213ULL, 0x9C265A4F8AC8A06AULL, 
            0x3D9B6F3A29942ED6ULL, 0x45A20023CC53F94FULL, 0x5956B07FB3B2A492ULL, 0x9DA3A6467E7DA680ULL
        },
        {
            0xA9C2FC14754570BFULL, 0x0AD26927FB335FF2ULL, 0x112F75D44573C468ULL, 0x22BC7077D818175DULL, 
            0x9FB41483F8A1D8A0ULL, 0x4E855BDB4A6AF8E3ULL, 0xB00FC33D153078EBULL, 0xF7CFCBE7BB49738AULL, 
            0x5DEBD262A1F6874BULL, 0xF90FE9BB6F880132ULL, 0x27F8CD29D7E02430ULL, 0x8FA9AD24D3F1FE6AULL, 
            0x2DA0050E125DA2BDULL, 0x30332980F0E8E427ULL, 0x0B08FC5265A0BE32ULL, 0xAD0D7E6350E5AE3AULL, 
            0xFAEC368DC058156EULL, 0x0CD68ECEA4D29821ULL, 0x8C3AC677333EC2FAULL, 0x733A47389AF086CBULL, 
            0x8129CE3A5DDF2019ULL, 0x3BF93859C9AA425FULL, 0x96DA53651DA945E4ULL, 0x742640FD8515D698ULL, 
            0x4AEEBA48725DFFE8ULL, 0xBCF5129AF04289C1ULL, 0x55664F1D14445D24ULL, 0xD0742304F6CDBDA4ULL, 
            0xC4476F7387AD4482ULL, 0x5B9A61638E7695E3ULL, 0x267CB022B909C824ULL, 0x2F8479964A87BAEEULL
        }
    },
    {
        {
            0xA6EA2784257FD953ULL, 0x8ED6266473D272F3ULL, 0xEF348D9F4606C685ULL, 0xD6D6421CCE88EEF9ULL, 
            0x2F27C8D23B5C3F47ULL, 0x938F55DB892C2EE7ULL, 0x15C34EB66632146FULL, 0xB7E23699F679F2F8ULL, 
            0xF6EA705DB20D162EULL, 0xA79A1590F878C925ULL, 0x34967EEAD159BD24ULL, 0x434F6EF0B8DF02EAULL, 
            0x2BBF60EFCB53F0EFULL, 0xBD5A5ACBA66B05D9ULL, 0x1BA5F6C8F528B11BULL, 0x9FBC0DF80E84671BULL, 
            0x3469837B01ABC0BAULL, 0xE88DBA5B64760ABAULL, 0x04122CF6077F1D1AULL, 0xB78F577EAFDE3FFEULL, 
            0xF9C90335B59DE9D8ULL, 0x9FACB931FC7DD821ULL, 0x8761B9C5081F106BULL, 0x283B17C034F5185BULL, 
            0xB83220339B60C746ULL, 0x1EDD4DFA1C837F17ULL, 0x52264051CB7D4D24ULL, 0x8D55FACDA0F8F145ULL, 
            0x3B960698EE69B73AULL, 0xA8303425B40AB6FAULL, 0x55AF8F7AB800ADE3ULL, 0x2FBA6A4ADEEBC5C5ULL
        },
        {
            0x68BCD379CB426100ULL, 0x0DE1A6CC655E9BA7ULL, 0x4EA15A9757591ACCULL, 0xCBF84C05CCD50008ULL, 
            0x209063B7A1E36C8DULL, 0x186B16693923D434ULL, 0x9FB66B848F82FCF1ULL, 0x70559C3F3C98E82CULL, 
            0xFD1555C1A30C3BE1ULL, 0x225B37B51C6BC15FULL, 0x7BC9D31828845A97ULL, 0x4C8A6A8F5FAF9049ULL, 
            0x3634DFAB24375967ULL, 0x4EE2D0CD97FA4E61ULL, 0xD80AE31A2E9305E1ULL, 0x8592A33559493F8DULL, 
            0x465DD8DBBF18F689ULL, 0xB9765339DFD92B63ULL, 0x74A5F7786A4CA98BULL, 0x492DE8F679C72857ULL, 
            0xB9FCA267661D7D1AULL, 0x2B2DCC81F2A38CB6ULL, 0x501E84E850C430C5ULL, 0xAF040BFA60D0A25FULL, 
            0x981645E55D1F03B8ULL, 0x5A769B9A26E5F744ULL, 0x15640D724E83FE1FULL, 0xDD4A9CB0825D2967ULL, 
            0x279483E0D5819921ULL, 0xF758E6AEC3FD3AC8ULL, 0x90DD285000D34289ULL, 0x9BB9DE4AB84D2BAFULL
        },
        {
            0x1F82C1677B2AEA0DULL, 0x5373A1D769920520ULL, 0xBD10B0BFDAE2ADDAULL, 0xFF32AF6ECCE356F6ULL, 
            0xF8E5C5CC88595383ULL, 0xF22D2200BE6628AAULL, 0x5FBDFC2D5C0A0B80ULL, 0x300BE58678EC8565ULL, 
            0xA51BA6F8639695D4ULL, 0x5029CB63A923F123ULL, 0xCBE017B699F0B432ULL, 0x850A6D1935A46F83ULL, 
            0xEFC7FB1C29784089ULL, 0x9349532DC75FEAE2ULL, 0x0264E32A24E44792ULL, 0x44284ABEA88E807AULL, 
            0xCD4D3A143F3AA8AFULL, 0x51476EAB7972031BULL, 0xD4BA7CF653D43A79ULL, 0x93D668451CC2F2CEULL, 
            0xBCF4CAA66BDBF019ULL, 0x1066B39D9B5B19B1ULL, 0x2BB0B88D855754FEULL, 0xB730AE0A0296E5D9ULL, 
            0x596D55F67533150BULL, 0x61CF405BB8436866ULL, 0x315299A019A8D35FULL, 0x8520AB4595C71672ULL, 
            0x27A0396D67426C96ULL, 0xF6A7970E979DB7FFULL, 0x0C4F1C99B8387687ULL, 0x37D2EEB14B29A5FAULL
        },
        {
            0x570924C5016A4481ULL, 0x281F13E198024E8FULL, 0x8BF92AB34D546291ULL, 0x9EC5B2473AAA993FULL, 
            0x20AA10F895CAAA88ULL, 0x7BE953BF0A3CD8F4ULL, 0x91E8604F0EAABC78ULL, 0x0C6C0ED9D4E58101ULL, 
            0xA214680BDBBE2F35ULL, 0x4DD61E46614EFB00ULL, 0x340D91BB2EF28E93ULL, 0xC7BA7F596723984FULL, 
            0x7B3EF8E2975C9421ULL, 0xADB6EE13C46D6D22ULL, 0x7E3CB88CC481F90EULL, 0x97C4E171170861F8ULL, 
            0xE3BB44165CDC1794ULL, 0xC20603AB9EC1A002ULL, 0x410D520329004B9CULL, 0x7B5D7CC342D22CD0ULL, 
            0x4254BE6919BCBBD8ULL, 0x1F514683951EF4C8ULL, 0x00735D82DE5491F8ULL, 0xE4054BFCBA743642ULL, 
            0x36DE717E27957033ULL, 0x8213C76E120D952FULL, 0x8C2A9D3A636172EFULL, 0x75F8EEDC988CC807ULL, 
            0x9E10D52882CCFDDBULL, 0x52A9A7D769226457ULL, 0x22416FE54533DEC3ULL, 0xB1D69BB3BCB10CA3ULL
        },
        {
            0xF564F3C0E2606AADULL, 0x6026E8F27DF957B4ULL, 0xB2441B00AE70F495ULL, 0xE82606C446382901ULL, 
            0x23ADA19526448AF9ULL, 0xD1E3EBA5D977D357ULL, 0x6E71650B3144E076ULL, 0x8F6EFB1173F0DBECULL, 
            0x2623656A5182EEF0ULL, 0x751A0FC19EC2F3D9ULL, 0x004B226EAD9BCEC5ULL, 0x83C6EA9AF3C743A2ULL, 
            0x183BFFA54C606FC6ULL, 0xEEBBC318C690CF9AULL, 0x9B62EDA070CAB2E9ULL, 0xBE03A844F886661CULL, 
            0xFED5729CF59C1AC5ULL, 0xE73DCEE3EDAED431ULL, 0x560BA84257E83F03ULL, 0x19466139E31D7F41ULL, 
            0x78AE7F1F2FDCFB73ULL, 0x0DE4FC769F19EBB6ULL, 0x05AD4928AA59A788ULL, 0xE74E61FC80B9A0A1ULL, 
            0xF12A90D8E2F6B490ULL, 0x81740E5D05EABCF6ULL, 0x2029703E1981FF9AULL, 0x7831965F5954FC23ULL, 
            0x2CEC14A754669455ULL, 0x0C758C9C71ED0AADULL, 0x76E20568760E09EBULL, 0x6634B1A112E48383ULL
        },
        {
            0x9EEA29A9514152ACULL, 0x2F093EF373EABB0BULL, 0x5F2FF3C5FB46805EULL, 0xBFCB84D0E77DC453ULL, 
            0x3D3354027F6086CAULL, 0x96F3D0482F783E95ULL, 0x9A86B38A9F67097EULL, 0x1BB926A3D62997CFULL, 
            0xE45387C2EE918D13ULL, 0x2115C9373E3D5F5EULL, 0x9343CEEFA189651FULL, 0xFFD9B68121AD99D8ULL, 
            0xEFC5ACF93300AE45ULL, 0xE2B5871E0C1F963BULL, 0x1607B5B576F3A7E7ULL, 0x2D63D794FBBA7C79ULL, 
            0x50CD5D3BEEC2AB6FULL, 0x9AC5CE141FFBF463ULL, 0xC7BC70421AD17429ULL, 0xD2E88AC74C351B42ULL, 
            0xC96AA860EC5C6B62ULL, 0x0A0C1F123F0BEB87ULL, 0x470D51EB4C8AA9C3ULL, 0xB53055BD5533FC51ULL, 
            0xF5A5F3BA8D4F8173ULL, 0x710DF80D77420D7EULL, 0xD2FA13393523B6C0ULL, 0xB0ADE7AF622143E1ULL, 
            0x7A657D78D8DC516CULL, 0x4CC791E9E69A8F61ULL, 0x31EB9E739DE4A9E4ULL, 0xCCD377879EBA1CA1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseEConstants = {
    0x51B21B58BF2558B4ULL,
    0x6230765575830AE8ULL,
    0x2985A324193D5F53ULL,
    0x51B21B58BF2558B4ULL,
    0x6230765575830AE8ULL,
    0x2985A324193D5F53ULL,
    0xB291F22BAB0F4BD6ULL,
    0xF59F997C1067B889ULL,
    0xF0,
    0xA3,
    0xA2,
    0x1F,
    0xF9,
    0x02,
    0xDE,
    0x62
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseFSalts = {
    {
        {
            0xF9D3A0E323D96159ULL, 0xF530DBFD508E6C0EULL, 0x2BFC99551606EC17ULL, 0x2C312B9FEF93C26DULL, 
            0xAE97F84B2F8A012CULL, 0x1F51635DC15693DFULL, 0xB4C98936BDD2FB09ULL, 0x67D4C6A79B6C9261ULL, 
            0x934169F765D1D76BULL, 0x5399D0ED19EA5022ULL, 0x90CD0DE20BF16870ULL, 0x9967DC1A59FEC03DULL, 
            0x5EEDD68B6DF88447ULL, 0x3002809253D0BEE2ULL, 0xCC1FCDAF591CAF31ULL, 0x1F3234BA99C30CB9ULL, 
            0xA16A6C82588647D7ULL, 0xFFE7329E976E5094ULL, 0x15FA346AA3F18D4AULL, 0x2E21A0F9B912871AULL, 
            0x8EDCA384996DB58FULL, 0x465F456454B346D0ULL, 0x906DC486A91AB7B7ULL, 0xEA38B676EE922E64ULL, 
            0x757034FEE2D7C632ULL, 0x31BE18D9E676CB58ULL, 0x58E7950401452FEBULL, 0xB782E011DE96A49FULL, 
            0xE0A6E3C5F4331AD8ULL, 0xB10CC565EB9D8516ULL, 0x791DFE19C30C8198ULL, 0x9F048343696EBB7AULL
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
            0x4FE1A5453F502619ULL, 0x9B157C2B014E8E9BULL, 0x9C9FADC9DD79D38DULL, 0x19063296A3C94C9BULL, 
            0x2F9926DD61586E5AULL, 0x70EEBEBBE57774DBULL, 0x8D89DA0F4EA16FE8ULL, 0x774467C0D1AA22DFULL, 
            0x9B7BE63A8807985BULL, 0x4C6B74C6CD1CE109ULL, 0xFC0EDF9439D185E1ULL, 0xF1B023834F3A09C4ULL, 
            0x6439469E7BCF59F7ULL, 0xF01C9AFCCE81F054ULL, 0x90B19E912EF61101ULL, 0x35E6CF97C622169BULL, 
            0x3F6251A557517B02ULL, 0x0083C3A9B1D6FEF5ULL, 0x6AC2EB7B9746BAE2ULL, 0x3A962453628A9894ULL, 
            0x4732559BFB3FB98CULL, 0xCDB902E67FB3ACC6ULL, 0x6B4654A73988F530ULL, 0x34EB2BFC58A9F312ULL, 
            0xC64D1D644680AAB5ULL, 0x77D8FCE8E4B1979DULL, 0x70E43014462B43D5ULL, 0x0C4972C2BDE20651ULL, 
            0x5EA202DCC68D3807ULL, 0xD9868A75DB28EBFEULL, 0xA6476E9BCC2193D8ULL, 0x1E924C1E0B723166ULL
        },
        {
            0x245E8DD8B360CAD1ULL, 0x675232761A1E97EEULL, 0xA8417CB013BB03CAULL, 0x3106C18754F7E5A9ULL, 
            0x5610876CCEB28101ULL, 0xE4C49780278C2757ULL, 0x16F2C738611CD57DULL, 0x088A5906C9FE046CULL, 
            0x4D664FCED8D9B5C9ULL, 0xBDC9DD3C3872DAF6ULL, 0xCD7440A4CA84F27DULL, 0x72FB212F5EDD919BULL, 
            0x7F646E046D48D272ULL, 0x26405B90492FC5E5ULL, 0x111763F28F6CD54BULL, 0x278CAF9D9678AEFDULL, 
            0xB9E243ADEFFDEAC4ULL, 0x501658CC200B5251ULL, 0x6741469669191861ULL, 0x8EF3604EB6D4DB5FULL, 
            0x53B5A239E1870D98ULL, 0x695424D10558C913ULL, 0x69B8833E8FE5BA9BULL, 0xC78E9CF11066B6FDULL, 
            0x868AF9DC2192CBA3ULL, 0x6C57E05A5B1F4CBAULL, 0x8D50575007582B0AULL, 0x304FD1ACEDA4472AULL, 
            0x7049F0179B819D8CULL, 0x8813FEAC7057D268ULL, 0x09FE7A7577B7CD69ULL, 0xD534D0D976902465ULL
        },
        {
            0x3CD4E40E40EFD6FEULL, 0x0B452CB5B3787596ULL, 0xBEFDEA21F0E07078ULL, 0x010FE7C67A2489A3ULL, 
            0x2B38DC3D53E87E18ULL, 0x23A601AB46A7CE41ULL, 0xA646F843C7DBB495ULL, 0x7DCB256E5855C85FULL, 
            0xFA6486DDE04AF5A3ULL, 0x00AD72324BCE98C9ULL, 0x0218E6ECEBB823B6ULL, 0x20B814FDFBDF449CULL, 
            0x9DF5A8BE7F813574ULL, 0x6DF39B79FC16E8C7ULL, 0xC58DAC762EDDF230ULL, 0x25128DDD61D68DBCULL, 
            0x23B0170854371E28ULL, 0x14B4A0F91AA4767FULL, 0x3FE4FCCC36D6837DULL, 0x8E55C9236B9DE82BULL, 
            0x2096A5D1738324F7ULL, 0x0A3F4E0D4A4D8B69ULL, 0xAE66179C405F7467ULL, 0xBA7DAFE808018852ULL, 
            0x661A9435F9BD6A9CULL, 0x4DCF6724670C6047ULL, 0x508A6D840DDE9DBCULL, 0xC236517C5017E8F5ULL, 
            0xBEF0E9259F868206ULL, 0xAE9ECE2DA2D8336BULL, 0x007B8249E40E776DULL, 0x016B4C508F85776FULL
        },
        {
            0x1360982237D9E9C5ULL, 0x6D71158AE1398779ULL, 0xE796DA219B8524F8ULL, 0xF4A04077331FC951ULL, 
            0xA4A10E51D2784F47ULL, 0xB7FB7343BD16F906ULL, 0xD787A1D1D72CB6B9ULL, 0x1ABB66D161DC04BDULL, 
            0x20DC045753309C36ULL, 0x8AF589C87C7DA778ULL, 0x111C3149DE4D7FB7ULL, 0xD0008D234B703964ULL, 
            0xCBB6DCC5565E85E2ULL, 0x50EF68D44C9D1DA6ULL, 0xA4BEC85BF980F427ULL, 0x02D895362DB1AB7BULL, 
            0x5BB15880B5CF85B7ULL, 0x809A977416197E2FULL, 0x8BD43250CBFCAF50ULL, 0xF8E342BF7CC4DF79ULL, 
            0x69B55D7C3C24A3F0ULL, 0x13A88B87D2DAECECULL, 0x2C8A43E218188ED4ULL, 0xBE58152244DC38DBULL, 
            0x9233F9F4B8CADE2BULL, 0x937730D81EF2A55FULL, 0xECBAF58C0BFC550BULL, 0xA2D0A9C3627C81C5ULL, 
            0x49D324FE3D2C91DCULL, 0x2B2B15FDC23538D2ULL, 0x203FE0A4D7913AEFULL, 0xCEF44791153C9903ULL
        }
    },
    {
        {
            0x842FA049B7820476ULL, 0xD966BECF7B0F9001ULL, 0x79A27AB0FFD6612BULL, 0x3687A55A91FA0985ULL, 
            0xA14FCA3FA2AC88B3ULL, 0x567E474C48F2E541ULL, 0x10DA8D78B98BEF78ULL, 0xEA9D69ED622585D3ULL, 
            0x72E636616276BEC2ULL, 0x2378720A1C298072ULL, 0x33C13810593D8B0AULL, 0x032DC23228F37EFEULL, 
            0xA8CE995090DFBD78ULL, 0x6F43FF884C22856AULL, 0x5631FB0E94EAB6C8ULL, 0xE45576DA097C01B1ULL, 
            0x95158AB1FB6B848EULL, 0xE978ED62415517CBULL, 0xD100ACDC906B49F4ULL, 0x70D65B8F3FF895DDULL, 
            0xE68110F6B3818612ULL, 0xEF258889C0AEA0D6ULL, 0x0510331CDDDA709DULL, 0x8887C9D00395C855ULL, 
            0x5A4FA916A35C8645ULL, 0xA767AB220D1B3D2DULL, 0xCDC9AAE38A6952A6ULL, 0x0548A7B9EA364ACDULL, 
            0xC6DE75904308E3F7ULL, 0xDAE1F205EA2CDA43ULL, 0x9F98EA77B49BF116ULL, 0x4AA96DD06279F95BULL
        },
        {
            0xE4F1D36B836CD64DULL, 0x50B6648333F4053FULL, 0x2E164889FC140BEBULL, 0x99E3F216F6F9A406ULL, 
            0xC1C5C817E66F1429ULL, 0x0F7F84954B38A8C8ULL, 0x96498150791FB72CULL, 0xF37DD49790ABB192ULL, 
            0x75BAB261BD5908C2ULL, 0xC46BD72536ED2048ULL, 0xF40F48FEE539F5CBULL, 0x78BE06BB8E941114ULL, 
            0x5ABA79DCF1623A2CULL, 0xC4D05889079E365DULL, 0x7889642EC8652CE0ULL, 0x52BF90B477A3155FULL, 
            0x944F27A15E5ADE25ULL, 0x2A62DF14B8CB6DE5ULL, 0xBA8B586749B84BC2ULL, 0xF519741318E1F91BULL, 
            0x5B4A6397FF4E380FULL, 0xDF47D28932447AE2ULL, 0x9C040BF8F0ADE7FCULL, 0x21F1DEADF6EC3C45ULL, 
            0x44C4AE6F42ABCEE1ULL, 0x19A7F17FBC67FF6FULL, 0xB4A97DAF75090D54ULL, 0x492F558DE192ECF3ULL, 
            0x6C203DBD8A914F7AULL, 0xA285B1838461C9BBULL, 0xFE68F6B6E9C2C8F3ULL, 0x5071345B1DEAA17AULL
        },
        {
            0x9DBE04CA7FD0E9B1ULL, 0x19A23363F6A43771ULL, 0x0CCE578BCEBA97FEULL, 0x801879E3B4AADF96ULL, 
            0xA74C927CD592BE4FULL, 0x851191ABB55D988FULL, 0xE5D7621CF03AA1CBULL, 0xC51537B9F35A847BULL, 
            0x4A7C5145AFE21503ULL, 0xD2DE09318D62CAABULL, 0xB6F3523EFE6E6782ULL, 0xA42FA3BBDD6E8AAFULL, 
            0xDF45D0A55DA3A12CULL, 0x2CF5151D05123E6AULL, 0x6B2C81810D50940CULL, 0xC2A9A2B38555676DULL, 
            0xDEE5117FBE3A11B9ULL, 0x3B4A4FB63F586DE7ULL, 0xCB87122FEE88953FULL, 0x4A58314290B514B6ULL, 
            0x0BBBF8C53C88CCE7ULL, 0x8E4A235A94F4A29CULL, 0x8BD64E4A35C0CF14ULL, 0x9E96958517A27B4DULL, 
            0x106C9B6C82038FD5ULL, 0xEFA42A2B1FFE8C6BULL, 0x46F4AEFD0DCA17A2ULL, 0x1915B25A2DBF0AFBULL, 
            0x79280EA1933D852CULL, 0xD2FED841DCD14BADULL, 0x811B41798A852A11ULL, 0x7FAF56B676930F72ULL
        },
        {
            0x98AF7A34044C2E48ULL, 0xB06DAE6CBBBB7C50ULL, 0x6CB6BD34EA7C8978ULL, 0x3E7D5A0FD85A8F53ULL, 
            0x7125760049382CF8ULL, 0x742E4EAE49751C10ULL, 0x700A6D176D9F1DEEULL, 0xF9FB65E2DCF35C46ULL, 
            0xA46D01EDBBF7D695ULL, 0x5C1D0CE05E9FE672ULL, 0xE1C13013C22777F0ULL, 0xDFDF4B29FBEE40C9ULL, 
            0x0FD2724C860D9B02ULL, 0x73E4CE20BEC4A0FBULL, 0x542F265ED9F37AA9ULL, 0x02AB3AFD92D6B55AULL, 
            0xE0EFCD914FE8FA1BULL, 0x31F0B6085A397D54ULL, 0x4B0935F29B419A9AULL, 0x33FA77051310D390ULL, 
            0x7E2EABB3D108DA09ULL, 0x319760F521C3D5EEULL, 0x6ADDD27D7BAD8D09ULL, 0x83A0126B2128DC85ULL, 
            0x10CDAEAEAED48E22ULL, 0xEB83E6115692158AULL, 0x4260281DDDB291DEULL, 0x645CA391582B3841ULL, 
            0x414B7E6A0613206DULL, 0x52A3F150D9A7EA2BULL, 0x5F66353C43E28967ULL, 0xAE5D5D44394B1FE7ULL
        },
        {
            0x7019C97B74353E2CULL, 0x2CD0580667A47139ULL, 0x9EF302875D11BDE1ULL, 0x1910CBCBCDD4F105ULL, 
            0x1F6EBB233E71D9D7ULL, 0x24247E66C4C40DFCULL, 0xEF752DF465EAE86DULL, 0x8CAB53B5AF8E3870ULL, 
            0x48D7BC09F165646DULL, 0x1B876829A283FF19ULL, 0x4745AA20D6684B0DULL, 0xD8B9A800304EA59BULL, 
            0x700058F0C9FD5E0FULL, 0x9C428C9E07D2BB23ULL, 0xC30022B84300E7A4ULL, 0x4C2420D0AD1BE030ULL, 
            0xE96FA8F1D25143B8ULL, 0x75634BD9C6AC29CDULL, 0x19618BFD5F4CF6C0ULL, 0x39ACBF2965CD59EAULL, 
            0x70145D3A78367D2BULL, 0x1AFFC52E929796E8ULL, 0x13F215C5E86D837CULL, 0x929A6DF898BA61FAULL, 
            0x1A90002D7DE31DFDULL, 0x924AEDA1586B78A4ULL, 0x847DA17C204B813FULL, 0x875F3FA7D56E06FEULL, 
            0x6CC32F5905ABE495ULL, 0x6CF4F76F83067DFDULL, 0xBD80BE69469B45E9ULL, 0xA2787F98D5557D79ULL
        },
        {
            0x137CD3D5C345A459ULL, 0xB37D43D1E9F96D3BULL, 0x71D0150989F00FB2ULL, 0x0B2637E932510475ULL, 
            0xBF4AB3DD05CDED1CULL, 0xF05D5333540E5399ULL, 0x57F4A41DA3A4B447ULL, 0x7FD8331AB74F7A05ULL, 
            0x28FF642926D4054AULL, 0xB9EEC04FD5450BACULL, 0xBD9AD61A3040E3A3ULL, 0xB56AF947F9180066ULL, 
            0x24C4B69E5B4C32A8ULL, 0xDFB8346B68BEC882ULL, 0x407D30AFBAB57FEFULL, 0x0E56AF20D27D0DA4ULL, 
            0x9A56D8049D69C130ULL, 0x20BC6C894C4C50D4ULL, 0x44D0FD7B2237AC95ULL, 0xEB6A4E7BEBE9D9B4ULL, 
            0x126CBD215619321BULL, 0x22495DE287FB44A0ULL, 0x2E1E6E1339FA5B55ULL, 0x1B08B1A61F865641ULL, 
            0xE6EAE91D4DED1F45ULL, 0x8368FFD397B11994ULL, 0x7D2720930215AF78ULL, 0x7AF10E7A8D5AA593ULL, 
            0x009E419943BB1A5CULL, 0x37D87C5D9AD2EE50ULL, 0xD874538327165485ULL, 0x6C15CFF1E41BE072ULL
        }
    },
    {
        {
            0x7634ACC597FA34A4ULL, 0x5D8591624BF4942DULL, 0x44CEFE7FE0901431ULL, 0x09F6D06D2EB0DA04ULL, 
            0xA3B9D402A25BC4EEULL, 0xD52820FCCF0C2D03ULL, 0x1A9EC0FF86959116ULL, 0x22656C0BAAB2DAEFULL, 
            0xA9B56A63BD795CBCULL, 0xC9E1D9D0D427D655ULL, 0xA412DCB9298F93C1ULL, 0x89EFD67B68C6C3C1ULL, 
            0x1615364A1EDA6FE8ULL, 0x661405726391BDF0ULL, 0x1E501027B2BB923EULL, 0xBA67E64A3A57427DULL, 
            0xE82B649423270175ULL, 0x2B2B651A9F021BF0ULL, 0x695DD7AD9FFFF59AULL, 0xD467D33758EB3C5DULL, 
            0x057CEA4DAE05934EULL, 0xDC145FD6B4E558D2ULL, 0x443633B9056CD998ULL, 0x92CACF2EC1ED5E4BULL, 
            0xCA0881D640605D18ULL, 0x2FAF9A9D614806A3ULL, 0xF2BAB5E5DF9571AEULL, 0x24F1D6842837B202ULL, 
            0x83FAC178B7A871BCULL, 0x8C9538A89BB57964ULL, 0xE9F185BBE5F74284ULL, 0xE291290A64CC8743ULL
        },
        {
            0x4B340D0C63663A99ULL, 0x4521290D53FB814DULL, 0xE4F71A1252F4574AULL, 0x6F588828B2B200D9ULL, 
            0xD20659F99AF2A1D0ULL, 0x4AC0B5F1381C11C1ULL, 0x95FEAF201BA77D1DULL, 0x6E6850A14DC93FE3ULL, 
            0xB84148B077750305ULL, 0x2E18164706D763FBULL, 0x539C7344D8DE46AFULL, 0x0183C80A0147262DULL, 
            0x64BACD77EBC42163ULL, 0x9C9C6F776ADCAE19ULL, 0x347176D215756A28ULL, 0xF8DF99C2B9690B8DULL, 
            0x3EF91AD9BADCF616ULL, 0x12FF558D48FB7A5CULL, 0x0AC8904EDACE0CEFULL, 0x348F7040DBF6347BULL, 
            0x76687D80042D2D0FULL, 0x91DC1C502F3776BDULL, 0xD241DA1F99A9AB6AULL, 0x8EEDD0A8C9F96433ULL, 
            0x730E80623372DF79ULL, 0x749FB91A4332BA3EULL, 0x7244EE1CE44AA6FAULL, 0xCC81D5969B3DF815ULL, 
            0x11D5707B8E3DFF13ULL, 0x13EBF8C53B6427F8ULL, 0xA70491023C72DF11ULL, 0x19EF35045AD5CE49ULL
        },
        {
            0x94D74261104B841CULL, 0x4512274572FD2AA4ULL, 0x472CEB761B6B48DCULL, 0x9CC814AFCCD1E1CBULL, 
            0xA17301C4B3EF0225ULL, 0x01A580698EA71EEAULL, 0x085DB9994AB2DB2CULL, 0x1325371456822B04ULL, 
            0x6ACA93559A5C20EBULL, 0x0EB4AAA421E2FE19ULL, 0x18FF3011C2037015ULL, 0x26B980956A45693FULL, 
            0x7EC8E6096B4439A2ULL, 0xD61A5D6254C64C9DULL, 0xC3E08FAE5B5912AEULL, 0x304F69003649AE8BULL, 
            0x4CE707663D2B6C01ULL, 0x536FD49F968FFDD5ULL, 0x7F02A5923EB8A06CULL, 0xA3531A494B50B204ULL, 
            0x6CE7855C40FB65DCULL, 0x210EE18F139D0490ULL, 0x3E9B89869A697B89ULL, 0x75CEC6C0B94BBE05ULL, 
            0x1F11AEA7A84D5BB5ULL, 0xC90EF47F74D8F0F3ULL, 0x0B7F3C4D21555E40ULL, 0xA3E509F750F5D86DULL, 
            0x68FA57D62C0D4890ULL, 0x1087E02EA29FC5A6ULL, 0xFA65B3ADA00A0036ULL, 0xF5B0753C443B8513ULL
        },
        {
            0xBFE5B3DDB743C504ULL, 0x864E36D687B84A44ULL, 0xBFAD7FD8E963C936ULL, 0x6EE57111BAA93F6AULL, 
            0xA0D461D012E2EFB1ULL, 0x9D9758E474D68B87ULL, 0xC0450F30ACB38B66ULL, 0x5E1757FFDADF77DEULL, 
            0xC9007FB59E4B1F67ULL, 0xC311341072799D5FULL, 0x913CEAE213A0506CULL, 0xC0D61F4033251E86ULL, 
            0x47AE031E86DEA91FULL, 0x5CDF10404B79CEE2ULL, 0xC23000D278104DBBULL, 0x63A69709CBD6875AULL, 
            0xF63E60284C193F46ULL, 0x6C21DEFCCBF9AC3DULL, 0xDA46F0596FB445C9ULL, 0xF6BD86B1F4FB8A9FULL, 
            0xBFFA2477D2B27E6FULL, 0x9D56D421E70093BAULL, 0xB42E6B849BC1E736ULL, 0xACC0EA2B3848AEEBULL, 
            0x7E97840F3FC17BFCULL, 0xB79DCA6652C66E23ULL, 0xFE2778FA74F059CFULL, 0xF829E8FBCBA30206ULL, 
            0x9CE421F79F43C7B8ULL, 0x2C262AC134E03E7EULL, 0xF3DA9BDAB0D891F0ULL, 0x39B9029C0348F0C2ULL
        },
        {
            0xB60B4FD4E78DF92CULL, 0xB4C4A4D27A726CA3ULL, 0xE41DB5F7D94AB107ULL, 0xB2CBC62E31B2ACB8ULL, 
            0x166DF66DD9C9EEE0ULL, 0x820257C9D433A233ULL, 0xAD4E3CDDDC968A5CULL, 0xB91C3983237F368EULL, 
            0x94E905C1886306B8ULL, 0x78A97A37E9A26B0EULL, 0xEDCA4E4D684C87F8ULL, 0xD4A38759118008B5ULL, 
            0xFD8F8FC4FE30AB64ULL, 0x8A037223402A0F88ULL, 0xE16780915F32B265ULL, 0x2B8779DF0DDD39E5ULL, 
            0x5D8950AB3D3C8819ULL, 0x5ABD1C18269E7F30ULL, 0xBB1457C8FEC089CFULL, 0xD75E397B0BD3BACEULL, 
            0xA1B1B60358EDF56CULL, 0x0A290F3E1188D528ULL, 0x144FA32A3FE0E799ULL, 0xDF7D1D62E7AAC397ULL, 
            0xA112D16A28937054ULL, 0x27DD515C766C6948ULL, 0x7D30BBE03CD62940ULL, 0x8363928B2CCF48C1ULL, 
            0xCB23511DA81D8D0DULL, 0x123B9CFCB8EA1DEAULL, 0x457841EE2BAE773DULL, 0xA1167D07538EFCB9ULL
        },
        {
            0x0798545E9639DF79ULL, 0xF0E47D163D53E8EEULL, 0x1D0F85EB97274B2EULL, 0xAC78318739648668ULL, 
            0x3A55FC529EBD6E5DULL, 0xEF1E99808CDCFD25ULL, 0x27642B376BAD20A8ULL, 0x7D123DB45D00029FULL, 
            0xEA42356F93FA016CULL, 0x92E85F894B566CB8ULL, 0xA3A3ABDC5E7F2581ULL, 0x213EDA25D0131D74ULL, 
            0x20D7E20BF79561E0ULL, 0xE8190BF6CAE4D6DFULL, 0x43C1E99B5507C395ULL, 0xE280E771AA24F529ULL, 
            0x41AFDAAE5B550EBBULL, 0x4B10445154788744ULL, 0x9786FE5333191504ULL, 0x119C61723562D924ULL, 
            0xA82837CD427D933EULL, 0xC7D73BEC2C818AC4ULL, 0x942F1A79C269FE17ULL, 0x6831296559D5FF2DULL, 
            0x65D2DD1E72132A8EULL, 0xD330CF029596F94AULL, 0xC7E54E4C5C9E9D79ULL, 0xA803141324D1090CULL, 
            0x77D57479AB4C7EB8ULL, 0xDF272358383BFAF2ULL, 0xC392438DCC019716ULL, 0xC4030CE443D727EFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseFConstants = {
    0x532470D19F4A7181ULL,
    0x46E0E9DF29721632ULL,
    0xF6A915577422CD99ULL,
    0x532470D19F4A7181ULL,
    0x46E0E9DF29721632ULL,
    0xF6A915577422CD99ULL,
    0x2DA203C63E0CE58AULL,
    0xA50597C80432F8ECULL,
    0xAF,
    0x60,
    0x32,
    0x8F,
    0xAB,
    0x81,
    0x3F,
    0xF7
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseGSalts = {
    {
        {
            0xC404A3B47CB3C1C2ULL, 0xBEAAD53A0366308FULL, 0xA65D463472C84BF4ULL, 0x465E416CAB2474F6ULL, 
            0x53013AE1EACA46B9ULL, 0xE6B027F1E6FB97D1ULL, 0xF195C9E659C3AE12ULL, 0xAB6D3EA6BA4C974AULL, 
            0xE0F5C5B57673EA3DULL, 0xCE8C0993BBD851B1ULL, 0xE5BDB18BB5AA2104ULL, 0x8CAFF9B246CF0C96ULL, 
            0x1657AFBB8E95BBF5ULL, 0x03957A7E8093DF3AULL, 0x17CF804AABDF876CULL, 0xC72915C7B3173498ULL, 
            0x60E135C2E94F4684ULL, 0x1DE66DECF636EA98ULL, 0x17ED20BDE787E693ULL, 0x7420BB827346F77CULL, 
            0x448EEC8BB4651F54ULL, 0x3CBCE668DECB1900ULL, 0x7A03AF947BB5A74DULL, 0xEFA2ACC0E257DE24ULL, 
            0x4CDE62CE7D64D3EDULL, 0x9F3647A1500CD832ULL, 0xF4A986D1168AECEFULL, 0xE171BC05202155EAULL, 
            0x8CA0B4CD55E8A098ULL, 0xEA2021D81C72DC84ULL, 0x33563E5BB270712CULL, 0x1F25B747D5B72563ULL
        },
        {
            0x33D51768777E06F2ULL, 0x2A449BA2A7B6ACDDULL, 0x15CAED80898D5D75ULL, 0xEDB0E77DF8353937ULL, 
            0xD263F8507E921A67ULL, 0x3B15A70CEC78275CULL, 0x882E2EDD8CC3ADF2ULL, 0x65D71D864CC7F697ULL, 
            0x70981457066177F1ULL, 0xCE60FD2BE47BF7D4ULL, 0xF1D08F16406B4067ULL, 0x7C69A1A671ED5AA4ULL, 
            0xD9202F44EE76E406ULL, 0x25C7A78E0AFB8AE9ULL, 0x52F3217D82F18C74ULL, 0x3D7ADB57382E0CE3ULL, 
            0x9580E51FA5654A93ULL, 0x2CE7BC4B3468489CULL, 0xCBEB839A25F11484ULL, 0x6FD8A662FCA97191ULL, 
            0x25051FE7BA1B9EF6ULL, 0x2A9AEFE80252CE46ULL, 0x3BFF679126FBB91FULL, 0x8B850A95477FC9C8ULL, 
            0xB1C4AE4DA7054EC5ULL, 0x70AA6ADA9D68B7B0ULL, 0xE056083C6E97965CULL, 0x33E98E1071941DE8ULL, 
            0x09CA7DF165D0CE66ULL, 0x1D301B611AAA6AEAULL, 0xFB5581A95630E773ULL, 0x067A4AB8804AE0FEULL
        },
        {
            0x32489170111F9248ULL, 0xED44F808B2349B71ULL, 0x3C73FD30904D4780ULL, 0x67E67633AA414A42ULL, 
            0xEB590036BF1D0B6CULL, 0x5108DAF310967F40ULL, 0xC7C37F8736469B82ULL, 0x4561FBFA48AF0864ULL, 
            0xD7E8D50A37F0B504ULL, 0x8030B398D5419A88ULL, 0x95E4F20A0169D38EULL, 0x6FB62213F85AC077ULL, 
            0x5CEDD30B6B19F487ULL, 0xA2C20A7B71209A84ULL, 0xF1C4C4420800E58DULL, 0x07A7775827F3E024ULL, 
            0x664790C215D82CC5ULL, 0xF9A1E6F4BCB58323ULL, 0xA4BACD59E4BA0927ULL, 0x28014E7ED6930C66ULL, 
            0xE7A61B06A4AF9740ULL, 0x06EDD9983C918ACBULL, 0x6C23E4BB22AB001DULL, 0x0BC2956F380EEAACULL, 
            0xBB68B0F84ED0E5DAULL, 0xBA8BCCBC1DB8113AULL, 0x2EF61BEE3831B310ULL, 0xC05AEFABE42F659BULL, 
            0x606C3E6112740A90ULL, 0x65322B22383EADD4ULL, 0xFA4AC99635B24304ULL, 0x374E0CA5C8F87E1EULL
        },
        {
            0xE2E8411F13F8892DULL, 0xEFF98270D0508511ULL, 0x2EC972B857407854ULL, 0x846F3C2D795AB437ULL, 
            0xE0C1F0EAD1D3E57CULL, 0x8058ADB7662B9D53ULL, 0x09A69F7B0C442720ULL, 0x4E3ADF0E52C725C4ULL, 
            0x56CE3117F31558E0ULL, 0x2040B8DD97AA0725ULL, 0x72E4AA4E983F6A4FULL, 0x0191EF6025AED361ULL, 
            0x6C0A8C68CFEAB328ULL, 0x042A4584A1991638ULL, 0x88D981A2DE117304ULL, 0x2EFB2494003AAD57ULL, 
            0x59A1994C7B19FFB0ULL, 0xDEAB24121B84605FULL, 0x78CE7D7900120C36ULL, 0x8593EE82BA9A9CABULL, 
            0x081C40E0B1388EE3ULL, 0x4783D06F497E6515ULL, 0x35D10902119D7CCFULL, 0x5D4A96BE3B7DF3FCULL, 
            0x1D29309BC93F84C8ULL, 0xB22382A4C841EB44ULL, 0xEA35D786A2B8303EULL, 0xC06DCC132FE83291ULL, 
            0x0BAEEB12FDC63692ULL, 0xFBF71C3C064A6C80ULL, 0x64F070201A2FC5A2ULL, 0x95535EE6F3A2DE95ULL
        },
        {
            0x425663E4A6CDE4D6ULL, 0x81FC19C6D1EA22C9ULL, 0x88D2E06496D55A63ULL, 0x6D493B805D5E4811ULL, 
            0xAD4516B9FD672327ULL, 0x980FD13BCB5F5C4FULL, 0x9D1F9EB5D348D946ULL, 0x0238DC3FBC95122DULL, 
            0x5526FDBBF9185EF5ULL, 0x84C8C476A5F1B262ULL, 0x88985A55DFC8F098ULL, 0x149ED17986ED1728ULL, 
            0xCE2458CB49D508A9ULL, 0x4A9595F2E8F6B194ULL, 0x65AE993C39393301ULL, 0x3732E8EB1525F6D0ULL, 
            0x33C28919E3AF4135ULL, 0xA558B35F2CDEF3D6ULL, 0x519B994A04BEBEC1ULL, 0xF8DBFF5478F73A6BULL, 
            0x8E99FC4BBB692F0DULL, 0x469A10FB262FE62AULL, 0xAC181ED28F6CBE4EULL, 0xE38E1F9297CDE40CULL, 
            0xED33A196A984DEB5ULL, 0x5CB9C70E6320FB78ULL, 0x1464CB5A5BDD83BFULL, 0x359A06FB1D0FAD56ULL, 
            0xE5D578B43E2F1F3EULL, 0xB0B816FC5FF13B9BULL, 0x3873F445ED1F1535ULL, 0x5E4224FA95EC283AULL
        },
        {
            0x5689E029E72593ACULL, 0x6485E64E939FEE2CULL, 0x1E9017A741E2C825ULL, 0x0043426FDE946FC4ULL, 
            0xE4482C36FD7D4E56ULL, 0xA9A19F1DF2757F90ULL, 0x1AAC8004244B45C7ULL, 0x0128D8FBDC85BB0CULL, 
            0x9F8D6CCACBA36084ULL, 0x71BC4B67DBB2087EULL, 0x9A22A4E8775241BEULL, 0x16A7F1D69842D31EULL, 
            0x84103C03F32FB643ULL, 0x547BB05BE6288AEBULL, 0x7609B7CE0D7C0DC0ULL, 0x6AFD1C512C531E8EULL, 
            0xAECD42EED7F04DA9ULL, 0x4FC22A738C89DB74ULL, 0x6CAA95FB4AACFA5FULL, 0xFAA95A052DD3EFF0ULL, 
            0x4CB5D23C047CC452ULL, 0x605456D8BD5489A3ULL, 0x1A1F8AC9E88297B2ULL, 0xBABFB4199B52FCBEULL, 
            0x5EF6E3B7859BD7ACULL, 0x7AEEE919F5C44EC2ULL, 0x6DD9A3ABE3A042C6ULL, 0x31782C1D494EB1A9ULL, 
            0xAA21B2CD8325690FULL, 0xEB07480A730DCBE3ULL, 0x95C548E400F8A691ULL, 0x72E0034AEA7FEDA0ULL
        }
    },
    {
        {
            0xADE17ED07FE8A5E5ULL, 0xE93B09CBD6C94401ULL, 0x3F9E9A7970CEABDEULL, 0x27D472C0BAB6E3A9ULL, 
            0x07A936B94882CC59ULL, 0x5CD950116761D9B6ULL, 0x2F025EB2420BF817ULL, 0xB62DBC273665DBF4ULL, 
            0x6F30FEBABE5E8EF7ULL, 0xD43555903D0DE135ULL, 0x45FFA142C1FB4B00ULL, 0xD14A9019D06701DAULL, 
            0x8C6EE459BEAF466BULL, 0xA59DFC1C745B1650ULL, 0xA1BA573EB4317929ULL, 0xE551F37EC02A4669ULL, 
            0xAEF6A660DA2572BFULL, 0x484DD94110B01FF0ULL, 0xA30615EAFFB49E92ULL, 0x9BE913A957D0BAB1ULL, 
            0xF6BE27FA4386CD4FULL, 0x3A8707397C241ED9ULL, 0x522A03C9A44B0AB9ULL, 0xA92CDD78D899B6B7ULL, 
            0x0415C36D37A720AEULL, 0xB015E7CF450524E0ULL, 0xC07C4578E2727DABULL, 0xB0F3665A0F94EFB6ULL, 
            0x22AEFC164BB743E6ULL, 0xFC58B193034D0988ULL, 0xBE2F15E9B55AA378ULL, 0xAF8745AE13827361ULL
        },
        {
            0x479D6A0AB7E2C710ULL, 0xB413A3F89E2D599DULL, 0xEE4464B4D655AD27ULL, 0x629CAEB488C94A95ULL, 
            0x986E061BD7418D69ULL, 0xF4D5E58201EF3B1DULL, 0x42B9CCDD0506E6F1ULL, 0x5C244B2A9E62477BULL, 
            0xBD8D962DA7C48546ULL, 0x32C68F1C153FFFA6ULL, 0x80BD9CF402FE5629ULL, 0x5E7FB1B67B087B2CULL, 
            0xE0FF67E413EE2C61ULL, 0x679E738D2F4ED17AULL, 0x46F72918CC11915BULL, 0x3803E379EAAF5BB1ULL, 
            0xC2173A53566DD1B1ULL, 0xC8F276BC019771E6ULL, 0xCE25DFADE5C4981CULL, 0x56D43FAFC01BBA49ULL, 
            0x2CEE5E546880AE07ULL, 0xB39CEED52D0A4A4AULL, 0xF0059447459971A9ULL, 0x31D4ED11E3A72CE8ULL, 
            0x71AC8177D4E89135ULL, 0xDAA9C2DEB208B8FAULL, 0xB884D520C85FEE97ULL, 0xD3E4CB7085637713ULL, 
            0xD6CE7F185933C52EULL, 0xD8A860133E0BD886ULL, 0xD17E7953CFA38C83ULL, 0x18A5A65CC71BD3D6ULL
        },
        {
            0xE8F914F6CFB0B9C7ULL, 0x64CD29DD5621CE63ULL, 0x493CD28D0B7F412EULL, 0xCC1950335128EEA2ULL, 
            0x7EB6BFA32360F9C4ULL, 0x176DD88573932A90ULL, 0xAC092CD412ECABB2ULL, 0x4F261C203C3DFF5CULL, 
            0xE2ADDF450F880446ULL, 0x9F4E56861C8BB2CBULL, 0x47830DC482DC0C31ULL, 0x09F8D5B190E83C47ULL, 
            0x2F160CD0384ADD3FULL, 0x01D7612E13CADCAAULL, 0xF7FDDD5C55D4A75AULL, 0xCBA2B1C43A9E333AULL, 
            0x96E95395FBDB2C13ULL, 0x7660997539C11855ULL, 0x48369116876BECF4ULL, 0xE04600632431074FULL, 
            0x4D9068C6CA573780ULL, 0x9F65B12E0DAF3C5AULL, 0xC59A6962B1ABD7F8ULL, 0x3B6DF66B9C0F9801ULL, 
            0x5C5263C1849716B8ULL, 0x27A35DB8ED715D0AULL, 0xCACEA356E3632979ULL, 0x13CA196C05FEBAB2ULL, 
            0xC85F9791C01FA4F5ULL, 0xB434EE9F51764004ULL, 0xAE2497476F29244BULL, 0x7F61CB324454C576ULL
        },
        {
            0x4398C56DF3E0A7DEULL, 0x4D9FE76B0078AF5EULL, 0xC844C0F3E6118813ULL, 0xAEC0E192CA35043CULL, 
            0xB78502DDFECF2011ULL, 0x08DB662BC796FDC0ULL, 0x474E3F2BBFFDBDC7ULL, 0x562D834F0A4A779DULL, 
            0xF106CD8CAC67CA76ULL, 0xCF58B9046E43690EULL, 0x7B9F87BA987B4DE5ULL, 0x8AE2C206A477CB92ULL, 
            0x82B42331308AA6FBULL, 0x87CD7095CE0C5494ULL, 0x41A99816F2336F7AULL, 0xD6FFB295CE241284ULL, 
            0x2D7B7F3D129C2456ULL, 0x7F7810BB2DA179ECULL, 0x6C9B1760246942A5ULL, 0x05B6448A26DC25D4ULL, 
            0x6672654D3A1ECFC3ULL, 0x988A58072355FEF8ULL, 0x74D77668EB7CEBD4ULL, 0x0C7DE20DD2A8FF22ULL, 
            0x3AD08197F81DAF48ULL, 0x407AB587ED9DEEBAULL, 0x8C46CC2350DD4A5CULL, 0x6402E77C2BBA14F9ULL, 
            0xA27EA4B9C702D2C3ULL, 0x2DF783753CDAC778ULL, 0x57029DED3A919A69ULL, 0x753396BD255EA596ULL
        },
        {
            0x2B00B12CCBFCA7A3ULL, 0xA82FCB32A808579CULL, 0x8C6E732DA79D85A1ULL, 0x492760FF921C3264ULL, 
            0x94F165E942EA986FULL, 0x9473370DCD8AF719ULL, 0x772F178F5D507CD1ULL, 0x358BC894C0807D6BULL, 
            0x48E53118BAC2F723ULL, 0xF8BB078BC17964B6ULL, 0xAA6B20A9F1B46357ULL, 0xB2F95D5D03352621ULL, 
            0x6C094D29EDABBA95ULL, 0x9E8D6DA7767A0C61ULL, 0xB9F55E2370BDCF54ULL, 0x2CC58C1B2063DCF6ULL, 
            0xBDD210422E17501FULL, 0xB70CB1F29ABBFDDDULL, 0x047AABD3D8728EEFULL, 0xFFC5E9B8AD2181B9ULL, 
            0x6EBB7150E55378D9ULL, 0xE8CD23A4481DFE97ULL, 0x04A0F91B91ECE501ULL, 0xF1EC9E0412DFEFB0ULL, 
            0x2D1DFB37765EFE2DULL, 0x500656764F252C2AULL, 0xB08A1A018BFBB9CDULL, 0xFEA6B1F62A7296CEULL, 
            0x821F31DE3C07FB22ULL, 0x89386078B9A4934BULL, 0x079F3D99E01B82D9ULL, 0x2ABE38E21F34AF19ULL
        },
        {
            0xB17A5C06032A6BD4ULL, 0x16A603F7BE9CEC1AULL, 0xF52DD747052C676DULL, 0x755AA5394002A04AULL, 
            0xB05449B30410CF65ULL, 0x987CDE2BE5257CE3ULL, 0x635B08CC6FD193D4ULL, 0x68C9CBBCFFC0B8F8ULL, 
            0x1600EEF7D304754FULL, 0xC7B02C3EFBA2E008ULL, 0xC16958520AD2697AULL, 0x7AA5D8560C5EF318ULL, 
            0xAC8BFCB8CA5E2902ULL, 0xBF58FBDF0A0E3BDBULL, 0x6D7027C4710DF3DBULL, 0x99A7869A735CBC38ULL, 
            0x0BA7E70628CF9B33ULL, 0xD2097C1E22D2E951ULL, 0x90EEC1F6DA1E6FA1ULL, 0x9C80A751527E23C8ULL, 
            0x6D217D76586ABCA8ULL, 0x8FAB6A90EFDFD4A8ULL, 0x5BB9E37C4124B82BULL, 0x64C647304A659938ULL, 
            0x9AB2930866CC9E6CULL, 0x9F9BA585EBE6B038ULL, 0x5031D97CC91CA7EAULL, 0xF8FB8D7F38834BF5ULL, 
            0x0FDE9EA486D52E97ULL, 0xC4BD5FFAE1DE58E2ULL, 0x34EA66BC70F29261ULL, 0x90B2A0E543BD6AE3ULL
        }
    },
    {
        {
            0x16147D8E041B3EBBULL, 0xEEDEBC7478C2F7E5ULL, 0x85B851FD626C2C6BULL, 0x79AF82DEF4123C85ULL, 
            0xA9CF849F6D44DC36ULL, 0xB3B08B25C072E110ULL, 0xFA97FAE58706593BULL, 0xF7FC1E60D8C58B11ULL, 
            0xDAF953CC6E606AA7ULL, 0x7D0E1D8B2795A883ULL, 0xC79C975C586430EAULL, 0xEED594C519BDC0BFULL, 
            0x379D5DBAF249D108ULL, 0x94D25F29CE0BC1BFULL, 0xE99588583F98E8D2ULL, 0x61D943F3749443B2ULL, 
            0x0ADD82E7FCE26E87ULL, 0x662CFF5F5D8B4F69ULL, 0x5C40DBC522F34595ULL, 0xA292DFC60D444D2AULL, 
            0x0E199C42A1EAE60FULL, 0x6D826E5A4B574989ULL, 0x9694D3E986EECF47ULL, 0x98FDB3CF50AF841BULL, 
            0xBFBAA11DD6B36E57ULL, 0xB8A814EAEE5704F7ULL, 0xD683B4A3EE26351CULL, 0x44490AF1C9A335DAULL, 
            0x89E249FFDF48FF73ULL, 0x88B7F6C7CCB8762DULL, 0x29F080F8B6FA1374ULL, 0x99229385D02F3DCCULL
        },
        {
            0x9EB9E61A73949EA8ULL, 0x930015796561B99AULL, 0xF582BB99B60A8B9DULL, 0x6A84A8AD22300DC8ULL, 
            0x511B5F821150C4E4ULL, 0x3617B26513B632F5ULL, 0xC6D875E2DE20DF1DULL, 0x23CCDFEA9D6EDB25ULL, 
            0x9E4A31085E721DD5ULL, 0xAF8A9F929A5D2AB6ULL, 0xD22D669DFB092AE4ULL, 0x4B7AEB0E4527FF4AULL, 
            0xAD804057CE1C97A7ULL, 0xA764D43CF5429FB2ULL, 0x33DB93C3B6E292D0ULL, 0x032E980C7913CD80ULL, 
            0xA13CBC1AD32D1068ULL, 0xBBCB0ED467D30C45ULL, 0x01A2AD1B2BF1D730ULL, 0xFF997FEF0B3C74F1ULL, 
            0x1E88A76D3E1E0813ULL, 0xF27311E63B5CFE5EULL, 0x576ECEC2E5278EDBULL, 0x4A67756E76F6D81DULL, 
            0x1959897AF40DFDA8ULL, 0x3B230AF3BBF93F98ULL, 0x65B64AC7DD0A06D1ULL, 0x08DAB6C54061BE00ULL, 
            0x00920B08C7FCCC50ULL, 0x2CC8AF0DA0447540ULL, 0x43959C1506A768F9ULL, 0x2D2DD22F2393B70AULL
        },
        {
            0xD7DF82C9CAD5FF93ULL, 0x5C734D571A0EEBA9ULL, 0xBF0B7EA80880528EULL, 0xC6A0E1A0D48D1B61ULL, 
            0xF39475E3A2F0A0A1ULL, 0xB26471024A1FF2B7ULL, 0x4C0CC90DAAF8F990ULL, 0x3D5CB415089B426AULL, 
            0x0FA10D3FAF411AFFULL, 0x9AAEB961D1CF5401ULL, 0xF763213116854113ULL, 0x6D7D1381E5425ED1ULL, 
            0x15FD47D24CDBA105ULL, 0x214C1F01FED35EEBULL, 0x9B1259B7C2A1FF29ULL, 0x2BAEBFD6A3FDD073ULL, 
            0x75CD4E12EB4582F0ULL, 0x6380AADB7D65E9B4ULL, 0xC8D00A34777BC9EFULL, 0x4F259CFBB8CBEB95ULL, 
            0x9037B1ACC2B7BD9EULL, 0xDD2DC0E579526AFFULL, 0xED40C5E4D64D0CD4ULL, 0x72FB18DE1B16F8DCULL, 
            0x958211BB132F08B0ULL, 0x6B84FAA5708751D6ULL, 0xC2EDBB4B86FC859BULL, 0x33039F18235ACD71ULL, 
            0xE6F776BEEBE501B2ULL, 0xD19C67C6D13EF7F2ULL, 0x1D03FAF4C3255367ULL, 0x6CEE02D81A6BEA58ULL
        },
        {
            0x3227E1A43EA843D6ULL, 0x525DBA98D7A65620ULL, 0xA9C98BEB0749C28FULL, 0x6FE7B61CE07ECE04ULL, 
            0x4E365B39442B4387ULL, 0xFB0FB141D49EE6B4ULL, 0xAEDC2388451C7719ULL, 0x0193C94BF9D3FC8BULL, 
            0xF0A9AD3EE87EF064ULL, 0x04341270D4C6A913ULL, 0x59F511E3C2D4CF79ULL, 0x70884B38C216DD8AULL, 
            0x4FD68987738B931BULL, 0xCBB37CD83FB78BE2ULL, 0xF6CC630347CF1536ULL, 0x7D8C1DC2C810A0BCULL, 
            0xB41C2073739CE518ULL, 0x2098DF185BBCA71FULL, 0x16F65EFB1253DDC1ULL, 0x7025EA9AF4ABD10FULL, 
            0x58CEE334085F3A72ULL, 0x321098828141AE02ULL, 0xAC7AC3848BABF66EULL, 0x31183DE61F99B42CULL, 
            0xADFB48326D7E97BAULL, 0x0A8714C1D7B11412ULL, 0xEC2CF98BEB3BBF57ULL, 0x2DEA335C7E3DB7D6ULL, 
            0xC013842B87355712ULL, 0x05EFAB98A270F868ULL, 0x7F1D0A37E543BFAEULL, 0xB26A337FDDDAAF18ULL
        },
        {
            0x69DC1E4A0DD865A2ULL, 0x678EB911C0AC4320ULL, 0xA29BD10B0FA0BEB4ULL, 0x642E7D12DAFB1614ULL, 
            0x5B72868746762B3EULL, 0x575FC2CC9BFE243AULL, 0x46D9ECACE7AA2170ULL, 0xACA6D0C7977B5E89ULL, 
            0x3CDD7E65B44A668EULL, 0x83FA087E222D9736ULL, 0xFAA49BC49E387B92ULL, 0x9E7F67BA0FE92038ULL, 
            0x9202260BEDBA9FCEULL, 0x49D0A8DD46A85CFDULL, 0x58C73CC1096B4E36ULL, 0x2FFEC3A3E60B7390ULL, 
            0x0793C088C867FBF0ULL, 0x601CF4FACD89A955ULL, 0xD61EC5399FD2EA81ULL, 0x8038791EAAFA93FFULL, 
            0x4D4FB09F556C6786ULL, 0xAB753F186E4F3B5BULL, 0x78BFC6AC792FCD0FULL, 0xBDCC2A13B36A902EULL, 
            0x074B51C8AA206E6AULL, 0x9656E20E782D8D48ULL, 0xCE38F18D2D1A4B09ULL, 0xE4598A9C9ED5628FULL, 
            0xD01616A4A30D74A7ULL, 0xAC1DF1565D859C4BULL, 0x48F1099D9EE4A757ULL, 0x652C32AB4C8611E2ULL
        },
        {
            0x685F749DDD3F429BULL, 0x088C08171363840DULL, 0x824AE23F4529E2F6ULL, 0xBEA4B09BFD718DF4ULL, 
            0x3F611EC2B14C2090ULL, 0x60497850B255D866ULL, 0x34DF2C54D14654E9ULL, 0x0C8AFA77BD8C574EULL, 
            0x1C13CB4BFA00F585ULL, 0x20ABF8BC6166636DULL, 0xCC4E14BA0197E69DULL, 0x517E2450E32ABA3EULL, 
            0x48D58E8D98C8E2C6ULL, 0x9A353FF40A6186EEULL, 0x2A543D35D2C1295AULL, 0x4597F2407BEEBBD6ULL, 
            0xD49E687AA038E19DULL, 0x25DA74F0120C382CULL, 0x0E98E284038D2314ULL, 0x5A953B7627D69C96ULL, 
            0x00C9FD50325F6276ULL, 0x9E861AD7E40EB022ULL, 0xBA8B6655D2AC0D94ULL, 0xDFF656A5DFA1FB75ULL, 
            0x7C3975862B57B15FULL, 0xA035364012616A8CULL, 0x137D4FABBFDF5774ULL, 0x1E91D3D48A94846CULL, 
            0xC30FA0FD52CD5356ULL, 0xC8BEBFA791485B74ULL, 0x2EAD484F5D6B92ECULL, 0x1FA1BA16B36C1ADDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseGConstants = {
    0xCCD8EDE4A67B2966ULL,
    0xF74307643A86A1EDULL,
    0x228BF88E24FB3A46ULL,
    0xCCD8EDE4A67B2966ULL,
    0xF74307643A86A1EDULL,
    0x228BF88E24FB3A46ULL,
    0x03CEC5FE813F62A0ULL,
    0x0FCFA27C76A0E957ULL,
    0x69,
    0xB1,
    0x9E,
    0x07,
    0xBE,
    0x6D,
    0x33,
    0x5B
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseHSalts = {
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
            0x3D89C06F3B166B84ULL, 0x2195298E46B2D17AULL, 0x851337E5B0166CAFULL, 0x464F883BF88E487AULL, 
            0x60CCEF0BB8B59352ULL, 0xA9FA8BAF1DC03706ULL, 0x3622D8BEA5EFC909ULL, 0x3058DDDEEE08A225ULL, 
            0x9E7F7C9DE4E358E5ULL, 0x7EDA4A4A23597024ULL, 0x7989AA13D55D6106ULL, 0x0466FCDFD754D3C7ULL, 
            0x7B567389F3A97CCDULL, 0x65BAD636C64294C0ULL, 0x83295EA34021FCE9ULL, 0x4710FA78ED230ED7ULL, 
            0x681842FD7032ACFEULL, 0x4D2E3456BA7BD0B4ULL, 0x11B54390E92DC8B8ULL, 0xF95F7A8B5A2053E2ULL, 
            0xB4EC591E316871ABULL, 0x2154CA7E510B270FULL, 0x6627C6C95F6D9172ULL, 0xE503CFE6603368F9ULL, 
            0x26D130609F202344ULL, 0xC7E4F014FB78B769ULL, 0xD12B24FF3A303255ULL, 0xEDE0CA2BF7839E92ULL, 
            0x93C76FCA5E95D6D3ULL, 0xC0055CE000EAE09FULL, 0xC658FFD2A11D642FULL, 0x8B2DB42C1C1EE90AULL
        },
        {
            0x999F8A1E3B0C8EEEULL, 0x34C4AADE355F4226ULL, 0x08BA6E540FB04D0EULL, 0x7C7F2738A62E5F2BULL, 
            0x32A0DA56765D6E52ULL, 0xF1E0CE4412620DAEULL, 0x75EEC98BF395DB78ULL, 0xCF73D84E7DAD518CULL, 
            0x508CFCBCC41FC777ULL, 0x2F833CC50F40E3F4ULL, 0x6EA496CDE65ECDF3ULL, 0x5F193F08774010EDULL, 
            0x4EE7EEBF108C11C3ULL, 0xE79FAC33617D4EE4ULL, 0x777F2162F1D1B5EAULL, 0xCFE2177F56182B03ULL, 
            0x1D689A33253221CAULL, 0x2A7EEB76B4660391ULL, 0x9867528D44E45ADAULL, 0x8CBEF02C7922BBFCULL, 
            0x77A43C4779291003ULL, 0x1223B0CEF71001EEULL, 0x51C1AF7F9B8D0CF8ULL, 0x989E788495F1336DULL, 
            0x7DDCA7CE59A2385EULL, 0xF62C1296C191D1C5ULL, 0xDCAA8DB0E59EA04FULL, 0x7BA2841EF207850FULL, 
            0xC35A396B4EF92E09ULL, 0xA0D9B9F1194FE8A0ULL, 0x4B51F675913BCAF0ULL, 0x564D1DFD5B8C2526ULL
        },
        {
            0xB20A9A42969E87EDULL, 0x81B11C1CBC250708ULL, 0xC969D8EB3848111AULL, 0x19AFB4DB59DCAE01ULL, 
            0x3269A6B2074C7707ULL, 0xCF65F8F0C0858199ULL, 0x38FCEF25592B3243ULL, 0x15B5D9B54F2E7578ULL, 
            0x376278509042E2BCULL, 0x3FC59A3D199EB048ULL, 0xB2726C7140DF9673ULL, 0x9178E16D9CC7953AULL, 
            0xDF1F6DFCE3868A0EULL, 0xE7C76DC524E67CCBULL, 0x42A56AC561FCEA8CULL, 0xAAC8C5C80FD781F6ULL, 
            0x3D42406F8C8D1D6AULL, 0x703E86B9B68B0505ULL, 0x77175E6E2C6C8457ULL, 0xDD9BE7F3928BEC31ULL, 
            0x6095AA433B0F5B2DULL, 0x1C6F2275BF3FD318ULL, 0x8664A1F2586DF48EULL, 0xAA2CA9BD1D5D0DF3ULL, 
            0x1AE785C617CDF08CULL, 0xB8DC63DDAB99A1FEULL, 0x7629342A21DAE11DULL, 0x7BA2FA9462F8121BULL, 
            0x960A02546390AFF0ULL, 0xD4D1018496002404ULL, 0x1A118A20C5A69CC2ULL, 0x92A367C80A99DE51ULL
        },
        {
            0x79A1D6584A7F39E1ULL, 0xF0E20567C05DCFF2ULL, 0x4D4440804D89A661ULL, 0x726334B570FD5D08ULL, 
            0x1681929E1BCDF993ULL, 0x76EDE056EACFB04EULL, 0x7517E5972CC1673DULL, 0xD914359E783A3CA8ULL, 
            0x668A0BE2DC09E9FBULL, 0x8059A94E4907D82EULL, 0x7F2C60D29D37876EULL, 0xFF51B497E93EAF75ULL, 
            0xD9E41C08281C42BFULL, 0x822B5614F3410F61ULL, 0xE66FB04CE1DF1591ULL, 0xEBC89628EEDF5DA1ULL, 
            0x482F774BF1FDD824ULL, 0x20A6DABA624A936FULL, 0x4B83B6D470457029ULL, 0x1DF7C77A32189217ULL, 
            0x49D87ADFB756E4DEULL, 0xB44DB5F02D9D2A75ULL, 0x2949084CDA1363D4ULL, 0x62D9DD56675A2C52ULL, 
            0x26FF703F076ADAE2ULL, 0xCBEA80A4B76B3234ULL, 0x771E959F776CCCD7ULL, 0xF7C88F970F4802DEULL, 
            0x4CF85EE4528EEDA2ULL, 0xE09286BCCFDF2975ULL, 0x7C9BA3EB5439B977ULL, 0x2DFD018F82A64D9BULL
        },
        {
            0x78601BCFDC28509AULL, 0x4AFA1F0A6336EC4AULL, 0x3FA687764BC8CB81ULL, 0x5B7B91A4B1CCCD99ULL, 
            0x3EC846641E19DE7CULL, 0x14C849255270C4ACULL, 0x77C9921883B3DBA5ULL, 0xD18F7FED061E6781ULL, 
            0xEB31345B631F6A5AULL, 0x41BD8B31D47D4C3DULL, 0xCA7B616F6B79E851ULL, 0x742AD69D50C5D1ACULL, 
            0x6EA44C3F88BD5F35ULL, 0x6CAA13B6D47CC00EULL, 0x2E8037C24D4D737FULL, 0x8DBE76D5E4DF7481ULL, 
            0xF278500DF7384AC7ULL, 0x7FBBF6FD12C8FC1CULL, 0x072BAEC166246B9CULL, 0x3F203331BAAAE8D9ULL, 
            0x5032536D47296A39ULL, 0x1A7FAD95E3977D93ULL, 0xC0CF0F7DDED47C03ULL, 0xD647A8A78AD056BFULL, 
            0x8096BCA72F2178A0ULL, 0xA4D14E541E252334ULL, 0xDA931619B2C98F13ULL, 0x730B4C71E890192AULL, 
            0x978CB51580E698D3ULL, 0x072C11DC56CDA419ULL, 0x54DB6A4214395C3EULL, 0x0C26C17FAFC71007ULL
        }
    },
    {
        {
            0xC4996B426BB35E5CULL, 0xFF141219F20127B4ULL, 0xF6E921CCBFE107E8ULL, 0xE91117FC42AD822FULL, 
            0x327E93881F3CFBEEULL, 0x725834607FCFC0D1ULL, 0x3EBC8956E2AB2A21ULL, 0x100F81DCD04EFA42ULL, 
            0x3CA1931A3F5C5055ULL, 0x589FFCF3F4AFBB05ULL, 0x048C21D88E67D872ULL, 0xB6DCCD98649C3E00ULL, 
            0x123409084DA18005ULL, 0x527EE95466564BF8ULL, 0x4B9C61FA0E13AD01ULL, 0x62D68039A83FA542ULL, 
            0xB04D739F1BBA165CULL, 0x59E3BD2EFCA00C57ULL, 0x55A656F4E973D037ULL, 0xAFE6F0793919EA22ULL, 
            0x0A81EC2FBAEB7304ULL, 0x003E81028E96E046ULL, 0x344B3FF5865B1333ULL, 0x8845C78351DC78F6ULL, 
            0x5838E1089A5C2FBDULL, 0xD4EAD012F78A21C7ULL, 0xC0F8F23353CD2F1EULL, 0xCB292D573FE321C3ULL, 
            0x455C47D5CF426407ULL, 0xCD691039F2637CE2ULL, 0x28637A2014CBC4F3ULL, 0x3EC69D574A7B9403ULL
        },
        {
            0x3289724476309D7BULL, 0x8EA9CBB7561274E8ULL, 0x6738ED4968F72606ULL, 0xB0ED0925A1DAF1D3ULL, 
            0xA39CEB08CAB1A1D2ULL, 0x14533C7DD4CB0BE9ULL, 0xE4C1259C4B4D6FB8ULL, 0xED32F2D5EA47110BULL, 
            0xB694ABFB90875242ULL, 0x1D97909E3F575783ULL, 0x0C4A3A58D21A55A5ULL, 0x16FEF1200CC3A146ULL, 
            0x4AF8B5C60ABFEC9DULL, 0x4385F13CA97FAAA5ULL, 0x4536BEF525B1E4F8ULL, 0xFEEB9595B8F1EEF4ULL, 
            0x382C0BD67EDDF9F7ULL, 0xCD06ECADD115ECF4ULL, 0x00055B82FC634A5EULL, 0x65D20965B3EA0C7FULL, 
            0xD5BCCDDC38FFD96BULL, 0xE03FA35AA98FC9B3ULL, 0x64D934BA709A390FULL, 0xAAC0E411630C62ACULL, 
            0xBB978BE8E4DAD09CULL, 0x616A2B0F4BF1B64AULL, 0x23D2FF0F45CFA5F5ULL, 0x23618090EC54F51FULL, 
            0x2B72B4FA4F6E7BF9ULL, 0x055130193954FD1DULL, 0xACAD63D1C54D1029ULL, 0xC9DD7A1DA35732AFULL
        },
        {
            0xD2B235AF979DAFBEULL, 0x0EFAC78866640540ULL, 0x1DAEC99E8CAF1FE5ULL, 0x91A0DABC14E4FCA6ULL, 
            0x089888D85C5A589EULL, 0x33ED8A5285CBCFE9ULL, 0x24A565F77A59F0BDULL, 0xC0C86012442BD87AULL, 
            0x75C89D0682BAC5C2ULL, 0x80418AD8AC3469A0ULL, 0xE1B6169930B3A583ULL, 0x0C422DE77D6AE99EULL, 
            0xBB6368CCB0C7B9E3ULL, 0x9ED69963A5B3840CULL, 0x5D2E0A0939ABA896ULL, 0x84552A4C7D2C7BD5ULL, 
            0x2B54C5708C9E6724ULL, 0xCE58316DF89BFF95ULL, 0x4DD6CD7845B06F72ULL, 0x7AC38BB877F483E4ULL, 
            0x367DEE2AD66EB4E4ULL, 0x37FB1ABA41B3E832ULL, 0xA0BE6780D2E77469ULL, 0x16C6D5A051B8ECF5ULL, 
            0xCE688EE3C8FC0DC0ULL, 0x22FA611C42B403CDULL, 0x0FCE8552E2D294C3ULL, 0x4A5170786299F173ULL, 
            0x6834E6ECC15FD50AULL, 0x3FDF613FD8FD6506ULL, 0xF35359D505E8AFAEULL, 0x7751B9AE8F402FD9ULL
        },
        {
            0xA5BFEF3F8AD1D3AFULL, 0xA9001E0C1D56292FULL, 0xA7BBF039A46F87E3ULL, 0x54027A2F09F4CDBBULL, 
            0x5A0530513CCC5DC6ULL, 0xB017B0397003E72DULL, 0x13E10004C81DF97AULL, 0xB3265444D84A828BULL, 
            0xF7DA82BCF13E1020ULL, 0xF590CC6619AEEF53ULL, 0xC54E92E2562BCC26ULL, 0x81F3384F0F2F01D4ULL, 
            0x6A8336F6922CB4F2ULL, 0x69F1816D18512214ULL, 0xBC64C58C0DA6A4EDULL, 0x42ACA60A62B9A178ULL, 
            0x1814BA499CE7301FULL, 0x8436232EA6DABF74ULL, 0x6C589968A9739E46ULL, 0x583DB320F8BCCBF5ULL, 
            0x22DB37D1E26EA016ULL, 0x90817F7803C29166ULL, 0x2231C7A4B39DBDBFULL, 0x274F2247425C6C69ULL, 
            0x071CB6FABB8BC57EULL, 0x5DCC5F2759CF2980ULL, 0x91E0DEE30149BC07ULL, 0xFE66A8A11BD1A432ULL, 
            0x771BA480A8928905ULL, 0x212C16AF9A89B0E0ULL, 0x41006BE9C5DC9FEAULL, 0x81A2722FBF9AD447ULL
        },
        {
            0x257DBB87AC38D318ULL, 0xF9A2EE4C0A2E40BDULL, 0xAFDC93FA8642B1A9ULL, 0xE53CDB9A4D39FDA0ULL, 
            0xFFDAE5B7043BD518ULL, 0x752F59454369E4A1ULL, 0x3B1C6D901A52318EULL, 0xABF2010FCFC7EB61ULL, 
            0xCE331ABC26F7FAC5ULL, 0x23CEFE814AD6651EULL, 0xC80496CFE2762018ULL, 0x3FCC8A783954C524ULL, 
            0x0E78A16B6C17236FULL, 0x4ACB7DA8B94B3255ULL, 0xE28ADBF4F05B015BULL, 0xFC9C020B8D35937EULL, 
            0x46C7A355E1064D08ULL, 0xDFDDB47BA74537DEULL, 0xED016E88D776B217ULL, 0x0C64030594835541ULL, 
            0xB10FA53D2A2216DAULL, 0x1DD5C8378828E8E6ULL, 0x259B753D8D1F9D2DULL, 0x0E7AA3E12DC6699DULL, 
            0x361738A944C1136DULL, 0xA1378E004687977FULL, 0x7F2C1512ED5CFCA2ULL, 0xA3BD0E174FD4C140ULL, 
            0x945C49D7160A7A03ULL, 0xC198656F0BAFF2F5ULL, 0x889BE83DFD396C27ULL, 0x7E238AB89A6386F0ULL
        },
        {
            0x8E7C27E3FE90C192ULL, 0xA46BE4B293B9B36BULL, 0x5223FD0F44655E05ULL, 0x36C1EFC388E72A7FULL, 
            0x0476D9683EF0AD94ULL, 0xC1DEFEF5811837E4ULL, 0x4D7C6F92E00D793CULL, 0x1E43DC96C9F88003ULL, 
            0x73E4BE85C78E06FFULL, 0xFFFB7E28EAA7CB5AULL, 0x37CA771B8A45347CULL, 0x9C9610D6D42BCC50ULL, 
            0xE03556FD2A1BC625ULL, 0x7A3663F468B2AF90ULL, 0xFBF941115143CC1EULL, 0x18C7617C6FBB1500ULL, 
            0x4D8D371A2EC42818ULL, 0xF16C83D7FF67BCCCULL, 0xAECE1B77D649F5ECULL, 0x7FCF522E4CAB18D8ULL, 
            0x1353584F7CF6C059ULL, 0x067658BBCFCDEFCBULL, 0xCB4FFF1A97A83761ULL, 0x26850FBA841DE1C8ULL, 
            0x2E0B0E24DDAF101CULL, 0x146E4131D4C4016EULL, 0xEBE12721ED7D426EULL, 0xC8CBE56660879F37ULL, 
            0xEAA6B8EABF30C2F0ULL, 0xF707207B750BAFBCULL, 0xB68B3FC1649ED54BULL, 0x11A03082ED9B6F89ULL
        }
    },
    {
        {
            0xDF445306116C137AULL, 0xCF2616A9A1140F60ULL, 0x16FD5F4D7A627C7BULL, 0x0F408518A160BF3CULL, 
            0xD92C5D37310F92A4ULL, 0xEC7055BD9ED70B1CULL, 0xC82FFD73B44FC743ULL, 0xC2B06024755F4D9DULL, 
            0x6EE391DB87857B36ULL, 0xEC643C05EECE222FULL, 0x36E55E746B2C23A6ULL, 0x9E30B979E4B1221AULL, 
            0xDA356F04519AE2FDULL, 0xBEA3EE637280B519ULL, 0x22B6518EE88D7114ULL, 0x53E8623CE479E8DBULL, 
            0x276F79C0A81A7A2DULL, 0xD40761EA1E2C4975ULL, 0xBD63032747984568ULL, 0xB5F4251B3C5206B9ULL, 
            0x5A596900CBBE68F8ULL, 0x79790EFCFD494836ULL, 0xE82AD40A406A224BULL, 0x12E6C0422A827FCBULL, 
            0x6F5058FB0DBCF1A1ULL, 0xB06D4DE4EED8E457ULL, 0x62421822100EEC07ULL, 0x859141FF6FD9DBE9ULL, 
            0xA6EAA9AD2DD832FCULL, 0xE18CE37C12F6997AULL, 0xA0BA109F57AD8A0DULL, 0x230599E3C87BEA2CULL
        },
        {
            0x9DD39196237CC0E6ULL, 0xD227F6B17F8B98D2ULL, 0xD06B3AFFD3322169ULL, 0x0AA45CC004D926E6ULL, 
            0xA1684CF0C5B8B488ULL, 0x4AC76C10C7DBCB55ULL, 0xBEDC496A25D79576ULL, 0xCE3A9A966DC8A8C1ULL, 
            0xB0043E1FAC4BFDB7ULL, 0x187DEDD7ABFCD7BBULL, 0x37CFA28022654431ULL, 0x3DF52465C87D0645ULL, 
            0xA6E5EEFCE2801318ULL, 0xA27DC8E2C1F74B2EULL, 0xE72E91D496C99549ULL, 0x5D68FE1896DA3276ULL, 
            0xAC178B9F87F3BD5FULL, 0xF5F1BD8300F80E42ULL, 0x20082A94B813ED09ULL, 0x7FBD5B8388C9A07BULL, 
            0xE0457A7E514E82B6ULL, 0x777C419C7489C725ULL, 0x6C3C0DC1AACD05F7ULL, 0xA27A4C86608A728BULL, 
            0x1BEDD7E1A370EFB6ULL, 0xF29189E28BF4953AULL, 0x7B0BF1B0515521DDULL, 0xA36A0594C131E6F0ULL, 
            0xD22B188B1F259E05ULL, 0xBE50C3C49EBBA34AULL, 0x2D8769CD8F1ADC22ULL, 0x9C2137FC45E4E3C1ULL
        },
        {
            0x2B9693AF9B5AF08AULL, 0x1946DEB16A17B8CDULL, 0x9BE35BBD3D927BC0ULL, 0x47E2C188549728B0ULL, 
            0x9760435CDC696029ULL, 0xA2EE441B043E36B2ULL, 0xF1F98841B5B94A5FULL, 0x3D99739BEA4D8347ULL, 
            0x11784F68BCBCD7C2ULL, 0xF719F0E7611567BFULL, 0x0345E9EF4F79C579ULL, 0x69EA980CFEC577ACULL, 
            0x4EF9843D0D0611ABULL, 0x1AD44FA978F8830EULL, 0x228DA2288BF160C1ULL, 0x5B46C75346C8CED0ULL, 
            0x2A9B41F8F8AEB99AULL, 0x753532343EB72693ULL, 0x669C141F84CFB1D9ULL, 0x56F4A07D01772519ULL, 
            0x57777F2737246AC9ULL, 0x1956AC1D73D2363DULL, 0xAD4CF215BA6AFC3AULL, 0x464C4BB15922A1B6ULL, 
            0xE16CB2C003B47B9DULL, 0x57212B17DD1E3877ULL, 0xFEDFEAEA405B514FULL, 0xD2B47E8581D8729AULL, 
            0xFF32F711E73700A8ULL, 0x30F560A4AAAAEA32ULL, 0x94CDE604739BF0E4ULL, 0xBD12685D73024819ULL
        },
        {
            0x03E5335969A25A5AULL, 0x3994C16EDE13CCB2ULL, 0x6645BB4E5399B01AULL, 0x95EA91C9EFC5F465ULL, 
            0xDF98512244CB8AE3ULL, 0xEAF15106D30578BDULL, 0x7DEE8A28878FEA59ULL, 0x487E69928031619DULL, 
            0xE097482A19B77C87ULL, 0x48DE746ACC24B02CULL, 0xF5BE71E61336EC31ULL, 0x0C72459EE293553FULL, 
            0x609F6F8503EE786DULL, 0x1CE77E8CBA925E51ULL, 0xCBC758401949072DULL, 0xCC8F55BCFE06D405ULL, 
            0xB5D963BBAADD71C2ULL, 0x22022A6344E4C84CULL, 0xB79FDFCBC91EA01CULL, 0x76063685B82A5BB8ULL, 
            0x08FD9CD843869CF3ULL, 0xA53EC403DB381B8AULL, 0xD7388AD9966FBAF2ULL, 0x121B6DA5282ECFBCULL, 
            0xA9EE4A216DBEF74BULL, 0xB1DCE8E5CE3922EDULL, 0x5D28BF052B30049AULL, 0x3950C368F70617ACULL, 
            0xDA3F1B01472BCA1BULL, 0xCE9CD10673F7E7E8ULL, 0x5F7B3050A3DE293CULL, 0x84B39D52ACC9F9E1ULL
        },
        {
            0x559DFBA7F0CE92B3ULL, 0x88B6DBA7189A0D4EULL, 0xBD291F11A98E630DULL, 0xD3220082CF16EC9AULL, 
            0xF64FA99F13C443A6ULL, 0x79781E8E6832D87DULL, 0xF0341FC3C7AC0D79ULL, 0x6FD9B7FE6D76B939ULL, 
            0x2688C5EF257E2EE7ULL, 0x50C98DB36427BBD9ULL, 0x740133D8CF26DCAEULL, 0x93797A602AAE7530ULL, 
            0x4D4FC3E8BA2DF9A7ULL, 0x3641EF702BC22328ULL, 0x5A032CFF2848C97BULL, 0x19A60470CEB0CFCBULL, 
            0xF69C5C03920ADB8CULL, 0xE1BBF644BD034DE4ULL, 0xD824513FD2B4ADEEULL, 0xB07774E1509C4E29ULL, 
            0x03F27367C48954E8ULL, 0x3E7A8D2DB4351A17ULL, 0x2F93402BEA21FF23ULL, 0xCA016B25028AF7CBULL, 
            0x377DE7958D5DBE89ULL, 0x88ABF2E6A826E8F4ULL, 0x1B49B8D21F21C897ULL, 0x19001893EA604CF2ULL, 
            0x74ECBBB7056A79B9ULL, 0x15E527697A4EBE3CULL, 0x9D5C97FA3273DF62ULL, 0x5610503A3B9D94F5ULL
        },
        {
            0x96787F44DEA4B445ULL, 0xB2313B66F89D4AACULL, 0x69D0242BE56BE942ULL, 0x3FEA96F2720E55D5ULL, 
            0x45767A2E613DC100ULL, 0x93245A43BAEAE8AAULL, 0x61F8E1A90A7AF477ULL, 0x3B1A3736B1D18C93ULL, 
            0x68FA7F8B7CAB0D52ULL, 0xCFA8EBC0CB12678DULL, 0xF374FA5F95EAC9A2ULL, 0x899DA1A9944928D2ULL, 
            0xD148873E0FC8998CULL, 0x58DC8A93B09C2245ULL, 0x7EA987B9D4CD18F5ULL, 0xD835021A881E4498ULL, 
            0x5A9C15F5BAC24AC4ULL, 0x97268DB66B55E64FULL, 0x8044126DE4253001ULL, 0x5607BD2E009E34DBULL, 
            0x57232FD93734BC8BULL, 0xA1B8AC2ACD49C6DCULL, 0x8E1648499259D359ULL, 0x0362519AC00550EBULL, 
            0xE5E4B3E641B9D416ULL, 0x0539C18D50E8EA0AULL, 0x2B0A7C354496B2F6ULL, 0x639E25EB585B6FAFULL, 
            0x1BFFBE5403717EACULL, 0x59CE002B6486C7FDULL, 0x12AA9836C3C10561ULL, 0x38F717D2E90BA5E9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseHConstants = {
    0x94CE431445E2AB67ULL,
    0x94C5A01D8375DD8EULL,
    0xA4884574099B9EB7ULL,
    0x94CE431445E2AB67ULL,
    0x94C5A01D8375DD8EULL,
    0xA4884574099B9EB7ULL,
    0x6BC862860CE166A3ULL,
    0x65BE2BCA823335C7ULL,
    0x7C,
    0xE1,
    0x6F,
    0x27,
    0xF8,
    0xB3,
    0x3C,
    0x4D
};

