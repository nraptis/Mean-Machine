#include "TwistExpander_Alnitak.hpp"
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

TwistExpander_Alnitak::TwistExpander_Alnitak()
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

void TwistExpander_Alnitak::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE0A15386CA6D51DFULL; std::uint64_t aIngress = 0xF09329D11601DA5BULL; std::uint64_t aCarry = 0x8B1A6AE9FE746790ULL;

    std::uint64_t aWandererA = 0x8946B869EF5A180DULL; std::uint64_t aWandererB = 0xE128E81AFB57C9F7ULL; std::uint64_t aWandererC = 0xE1F597ECFFB76757ULL; std::uint64_t aWandererD = 0xC5E6A4595A2B774AULL;
    std::uint64_t aWandererE = 0x8090CD60BAC692A7ULL; std::uint64_t aWandererF = 0xDF91CE6E1B0110E3ULL; std::uint64_t aWandererG = 0xE3273D6C5B2F1E84ULL; std::uint64_t aWandererH = 0xDCA93CECCD584AF2ULL;
    std::uint64_t aWandererI = 0x9803D7E7C828FEC6ULL; std::uint64_t aWandererJ = 0xF418FAEF2CDC330EULL; std::uint64_t aWandererK = 0x9302C0765A456B6EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15534652218364916592U;
        aCarry = 11191340460598283568U;
        aWandererA = 16698513350042042198U;
        aWandererB = 16592399797803654903U;
        aWandererC = 17279095850655630816U;
        aWandererD = 9986317875131434570U;
        aWandererE = 16823564909810067491U;
        aWandererF = 11098771134432619197U;
        aWandererG = 14148095654648595495U;
        aWandererH = 9773024197562366925U;
        aWandererI = 13122187948750517428U;
        aWandererJ = 16571773275665082789U;
        aWandererK = 12886603532630657674U;
    TwistExpander_Alnitak_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alnitak::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC7DC80D70262251AULL; std::uint64_t aIngress = 0xB1A61FB2C2C4F7A5ULL; std::uint64_t aCarry = 0xCE255909F639FD61ULL;

    std::uint64_t aWandererA = 0x8885FD0C0B094B3EULL; std::uint64_t aWandererB = 0x8B7725BFA55FA86FULL; std::uint64_t aWandererC = 0xF31949ECB6B7B826ULL; std::uint64_t aWandererD = 0xA6F1200AA2691D5EULL;
    std::uint64_t aWandererE = 0xEBB575954A173683ULL; std::uint64_t aWandererF = 0xC664924E4977F177ULL; std::uint64_t aWandererG = 0xC3DC3C3588811FDDULL; std::uint64_t aWandererH = 0xAACC1B3B35A0794CULL;
    std::uint64_t aWandererI = 0xFA0AFC478BDD6125ULL; std::uint64_t aWandererJ = 0xB91F6E002656DAA8ULL; std::uint64_t aWandererK = 0xBA06949FE04F9CE5ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17395916281119268431U;
        aCarry = 16572994033499897032U;
        aWandererA = 9388017785021260747U;
        aWandererB = 16780032167233906609U;
        aWandererC = 9778921725141366672U;
        aWandererD = 15252459969047469019U;
        aWandererE = 18198134377929670829U;
        aWandererF = 10971954259506055419U;
        aWandererG = 10997610333524881230U;
        aWandererH = 15392115012395542449U;
        aWandererI = 10862188562674802663U;
        aWandererJ = 13277068138250505688U;
        aWandererK = 17888086597559525759U;
    TwistExpander_Alnitak_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alnitak::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xF4040F51187DBFCBULL;
    std::uint64_t aIngress = 0xD1486701A95838AAULL;
    std::uint64_t aCarry = 0xE15B772242CC62DBULL;

    std::uint64_t aWandererA = 0xCCB4F250B2FD1B76ULL;
    std::uint64_t aWandererB = 0xD1281A16985C383CULL;
    std::uint64_t aWandererC = 0x89752787976D26C5ULL;
    std::uint64_t aWandererD = 0xB1F0D222BDAECA79ULL;
    std::uint64_t aWandererE = 0xA02BDD389681DE3BULL;
    std::uint64_t aWandererF = 0xE77E82724B841E1AULL;
    std::uint64_t aWandererG = 0xD484301A33E6CC99ULL;
    std::uint64_t aWandererH = 0xAB894A5E140C8A06ULL;
    std::uint64_t aWandererI = 0xF6FDA3B04E998265ULL;
    std::uint64_t aWandererJ = 0xC8ECB9C9ED13374AULL;
    std::uint64_t aWandererK = 0xDCE9AB2ED6C0FCF3ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneB, 0);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneA, 2);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneB, 4);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneA, 6);
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
    TwistExpander_Alnitak_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Alnitak_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alnitak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 6 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 9668
void TwistExpander_Alnitak::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 237U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1902U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1679U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 460U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1899U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1203U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1881U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1900U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 742U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1283U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1629U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 66U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 803U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 184U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 81U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1359U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 538U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1261U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 709U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 425U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 458U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 836U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 839U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 674U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1710U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1845U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1154U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1295U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 810U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1309U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 732U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 660U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 329U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 960U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1450U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 808U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 777U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1979U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1221U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 160U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 578U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1270U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1635U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 740U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 374U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 944U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 951U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1795U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 981U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 819U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 377U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1942U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1930U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1756U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 378U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 964U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 929U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1174U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1691U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 522U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1076U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 451U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 208U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1253U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 942U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 697U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 150U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2037U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1773U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1757U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 181U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 900U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 872U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1977U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1746U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 794U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 102U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1926U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1248U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1218U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 492U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 924U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 745U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 282U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 122U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 49U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 790U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 32U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1092U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 465U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1068U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 756U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1311U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 501U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1576U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 400U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1009U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 801U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1202U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2026U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1928U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1764U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 955U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1310U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 990U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 828U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 603U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1627U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 802U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1534U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1167U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2015U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1729U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1975U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 143U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 304U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1035U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 636U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 920U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 605U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1713U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1308U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 368U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 48U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1095U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Alnitak::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA4CB5E090CDBD18BULL; std::uint64_t aIngress = 0xFE4D4DB389207437ULL; std::uint64_t aCarry = 0xB7B5D41DCADF1154ULL;

    std::uint64_t aWandererA = 0xB7960D45CC9F88B2ULL; std::uint64_t aWandererB = 0xA24609E1DFE0FE1DULL; std::uint64_t aWandererC = 0xA16A734F33FA7628ULL; std::uint64_t aWandererD = 0x8BD1C728006B1B5EULL;
    std::uint64_t aWandererE = 0xF72295050F6A799CULL; std::uint64_t aWandererF = 0xA74BC1C20F5FB7D1ULL; std::uint64_t aWandererG = 0xAA6CB4476162396DULL; std::uint64_t aWandererH = 0xA6420EEB1DCF152DULL;
    std::uint64_t aWandererI = 0xD840D8E7CDC4750FULL; std::uint64_t aWandererJ = 0xFA0049CF4352D29CULL; std::uint64_t aWandererK = 0x947271F831D2641FULL;

    // [seed]
        aPrevious = 14129100716522249289U;
        aCarry = 11010957921489752569U;
        aWandererA = 15025547679645816041U;
        aWandererB = 11396413569524882522U;
        aWandererC = 15865358887401160056U;
        aWandererD = 15625358990799026116U;
        aWandererE = 10053697276788923284U;
        aWandererF = 18311722889026405893U;
        aWandererG = 11001459531738535816U;
        aWandererH = 16532668383416976512U;
        aWandererI = 13922023720657244499U;
        aWandererJ = 12999329962149920645U;
        aWandererK = 14035426704949903745U;
    TwistExpander_Alnitak_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alnitak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 6 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2850; nearest pair: 521 / 674
void TwistExpander_Alnitak::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3634U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4097U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 208U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6186U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2431U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5566U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7779U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7117U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2707U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 803U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1874U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2383U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6844U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4772U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 907U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 13U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 247U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1062U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1304U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1013U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1081U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2028U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1844U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 227U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1594U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 577U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 625U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1845U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1554U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 529U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 180U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 122U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 622U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1279U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 6 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2854; nearest pair: 523 / 674
void TwistExpander_Alnitak::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5903U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5231U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5002U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7584U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6072U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5565U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8079U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3295U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1547U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1098U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2767U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6547U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7270U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6573U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5315U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7556U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 326U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1975U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 763U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 95U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 72U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1276U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 51U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1663U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 579U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 578U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 23U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 723U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1971U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 279U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 736U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 828U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 31U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 322U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1626U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseASalts = {
    {
        {
            0x35F9493AAFAA5D89ULL, 0x932A1CC9D5E532D6ULL, 0x16985E02C19DD145ULL, 0x2BF798AB518413B4ULL, 
            0x11E46091093F776EULL, 0x8D2232AD0F16C034ULL, 0x42A751BBAEEF0730ULL, 0xF83FD173BA83271FULL, 
            0xF755FA2333C1BA5EULL, 0x8FFB7238259EF2EAULL, 0x5B098F324BE1D3C7ULL, 0xF3357184A9A3AE17ULL, 
            0x61FD480CE272F482ULL, 0xA89E24E64CBBF744ULL, 0x5628CA80FC643544ULL, 0x85C3A3912EC75E71ULL, 
            0xC7F14493A5060B1CULL, 0xF9DFCC210EA8A681ULL, 0x335BD8163D01987EULL, 0xEB728612EE77225BULL, 
            0x1D58CAFF83608AFAULL, 0xFB01A6C440A5F9DCULL, 0xEC71C6E5C0D5869DULL, 0x7E6D43C865C15FC0ULL, 
            0x460AC8E2EE663A49ULL, 0x17F32158DA3DE200ULL, 0x8DDEA854E149707FULL, 0x7658F8B1B104281CULL, 
            0x4A2C0E5D2D2D0D8AULL, 0xA5DFD8C4CE997316ULL, 0x3C2465F0917EB38AULL, 0x5F5DAE228573B62DULL
        },
        {
            0x07DA19C96019ED7AULL, 0xD8BBFC4100CD700AULL, 0x9FEED4A6404963B9ULL, 0x04D926FE7580C962ULL, 
            0x0E8DF10131109D50ULL, 0x33466983523BFE02ULL, 0x399B78AA4FDCEC56ULL, 0x15270B95716E3DC0ULL, 
            0x9BA74771764B7AACULL, 0x372ECA11A372E4A9ULL, 0xCCA7BD22F3523F99ULL, 0x74EA79CEAF181569ULL, 
            0x92EFCB2B47FF87C2ULL, 0x243330BA41D7819CULL, 0x845A0A2275C782EAULL, 0xD1FE7BA719C07289ULL, 
            0x5548488B54130D8BULL, 0xBD11BFF2C7FBE095ULL, 0xFFD42D91598CC504ULL, 0x51C04B356A816BD4ULL, 
            0x31AD8C1861009DFEULL, 0x70808875994EBC62ULL, 0xB4E91FE1333D0214ULL, 0x450A0AAEAB50B259ULL, 
            0x15E71C109F73D121ULL, 0x218BCCD1222CA74CULL, 0x06F3574BFD50F852ULL, 0x22315604322E80C3ULL, 
            0x9446DF629F3E2FC4ULL, 0xA0C7121CB7097D9FULL, 0x43BB1D553BD8BEACULL, 0x5C0C54B5F2F8E229ULL
        },
        {
            0x9B5C8B877DAC284FULL, 0xF782E37CBCB5EAA2ULL, 0xA3B5C0098181AE0CULL, 0x9FB8D25FDB819D32ULL, 
            0x76B22DE08D6791D8ULL, 0x68A34F3324F7E6DAULL, 0x1D43C411DAC25111ULL, 0x2817EED31E967CD3ULL, 
            0xABC9C8AE21C98E4EULL, 0x4F27D25AABDF41B3ULL, 0xD8BBAF3B0A5F0477ULL, 0xEB4CEC3C0812F8A2ULL, 
            0x4E33283C521B526FULL, 0x03A8CEF4FFBF67A3ULL, 0xE355A0F02C17CA9AULL, 0x911A34EB593AEC61ULL, 
            0xF5D8A53025AFF816ULL, 0x308D50EDE97CEB00ULL, 0xB984AEC00C31F719ULL, 0x45EABB6716545327ULL, 
            0xBF741079148ECEE4ULL, 0x6FFEBB409A254169ULL, 0x5EE34A16F69822D0ULL, 0x59291464AE7B4944ULL, 
            0xF0B280A5DBC8DC3EULL, 0xC82E692B24C1C041ULL, 0x71BE7E79436FAF97ULL, 0x4AADFC107C4DFA5FULL, 
            0x81EF1F62C120A278ULL, 0xE696E5642F7C0C7AULL, 0x3F405EC6F2BBCD33ULL, 0xCDD3969BD2918C1DULL
        },
        {
            0xDF8BA816AEBBB9DFULL, 0x79AC94922E4BA107ULL, 0xBE6636C2E63272C8ULL, 0x26807832FDFFCCD8ULL, 
            0xEAAB8F8F7C631D38ULL, 0xFA9DB4B69279CA85ULL, 0xA3440BA0AD31913CULL, 0xCAAE40047CC0309DULL, 
            0xCA7D0FFADB209CAAULL, 0x53C1B63532FE5BAEULL, 0xCDFA7341EBED1CB5ULL, 0x6C1FE744BDA02805ULL, 
            0xD1640CB786996678ULL, 0xD46ED22C2E32CAEBULL, 0x2E8CBD9F889A0F35ULL, 0x0F3CEDC686C6C804ULL, 
            0x14EE2CFEF80A4474ULL, 0x7CDA481BB820B1D5ULL, 0x65CC4AE741D48500ULL, 0x990AEF87BDA8B548ULL, 
            0xF6349F03E7D4B7A0ULL, 0x4B38512B571E439CULL, 0xB62A3EBEAB206690ULL, 0x6439C96B80FD5820ULL, 
            0x0371718D2BB25D1DULL, 0xC614A2790FF2ED94ULL, 0x3758B0D442A00ED9ULL, 0xE7A4C6526921CA08ULL, 
            0xC72930BE8ABEB669ULL, 0xAB42BD2E5D0C4914ULL, 0x22BEEA53517561B1ULL, 0xD036FB04E7DDF134ULL
        },
        {
            0x0BBE32107CCEBF17ULL, 0xEEE92AEEE554306BULL, 0x616A8575B0AD5330ULL, 0xAAE86E9D3D8907D3ULL, 
            0x25B5B4D9B7AD620BULL, 0x5145CEF7826D98E2ULL, 0xE3A7BB3196F9A380ULL, 0x1C2C15D10C5F13A9ULL, 
            0x34884DC13DE99344ULL, 0x731AA5402C500CDAULL, 0xA1F00010391D2AC7ULL, 0xB044545F46DE4219ULL, 
            0xC7AA79F4DCAAAEC0ULL, 0xD2D7A967A44F6CBBULL, 0xEC6EFE1DE6AC33CEULL, 0x426D5BD9D1EBC3DCULL, 
            0x037971BD83E08F53ULL, 0x8F9F1FEF20739977ULL, 0x39085C366D3DD11AULL, 0xBE6720DDA55FC354ULL, 
            0x413F78AC08A41F80ULL, 0x22D1EEE3F1DD7B15ULL, 0x9C56D7B537212894ULL, 0x92D9923554368A95ULL, 
            0x0B23563B3658983FULL, 0xEB46877756CDB260ULL, 0x6047B994F41CA354ULL, 0x51F1B5A8CBBFA046ULL, 
            0xF814F763007BE5EEULL, 0xEFC6A4002EB10DABULL, 0x22CF58AB6B6B5FEEULL, 0xA0A6245FCEF67127ULL
        },
        {
            0x9089BA5BE6584551ULL, 0xCB7BEA1E5FC6810EULL, 0x9438C444DE54A38EULL, 0x13B39EEBAC2C9579ULL, 
            0xCF48B7DE3C724EE1ULL, 0xADFD0180211402C8ULL, 0xA02F6F5E48FB77B0ULL, 0xF4CAE62CBDFB05FDULL, 
            0x58A66A07C6F8AE33ULL, 0x5B1AFB534FC1AC50ULL, 0x3A1BD2E8FF7931D9ULL, 0x036208229A76FA9BULL, 
            0xBE4D67DB4CE105DFULL, 0xF5DE70E0CF8F2A53ULL, 0xB2F20F06CC930565ULL, 0xC328871E7E371B71ULL, 
            0x9C63BA82AA70D756ULL, 0x8F8DD10D39F7B312ULL, 0xA82EE3515AF65C89ULL, 0x4AF088006E0A37F0ULL, 
            0x998D593749C8F3A3ULL, 0x2AE0A445CAD3EC39ULL, 0x8D946DBC1C742EFCULL, 0xA5F4A39C7B4DB2C4ULL, 
            0x6A7996D60AE17150ULL, 0x54C05BF8400D0578ULL, 0x14DBD0AF9C108D06ULL, 0x8564A53C3F639AB4ULL, 
            0xB459231D3A2671CAULL, 0xE99EBAE1E00C8DBDULL, 0xC11FB3D58435D178ULL, 0x891BB0C5FB170692ULL
        }
    },
    {
        {
            0xAA13EF81D91D8B0CULL, 0x27AC06EBB8CB87FCULL, 0xDF8C4C10D8E81C25ULL, 0xA09F0463D9D27B36ULL, 
            0xCEF3858787BDD5CDULL, 0xADEE46C9DA22C3B8ULL, 0xD015822FC4ED305BULL, 0xC937B2B38FA5A30DULL, 
            0xE1C40FF487626311ULL, 0xFF4CFA450C6C2EA5ULL, 0x76077FB36D4FCEDDULL, 0xD1A7462FD1910991ULL, 
            0x3877801108285FC5ULL, 0x2C1FE26886099B6AULL, 0x476235EFD0153D4BULL, 0x93017C0075D8098EULL, 
            0x2665877AEF27FE85ULL, 0xC5A290E1E6EBEFEDULL, 0x5DEA6ACDE23DC085ULL, 0x44E71FD89427D7BCULL, 
            0x5F0A186E365ABC58ULL, 0xFEA08E55FF7AD924ULL, 0x15AE3B30117C754EULL, 0x1FA74C209B4660F0ULL, 
            0x9704B1F622DB57E3ULL, 0x778539D04BA7C19BULL, 0x3A5BF74783BAA579ULL, 0x307A8B7A0A646C03ULL, 
            0x75E9E6293CDF26D5ULL, 0xADCB769E0CED35ECULL, 0x34D498C8AE4A760DULL, 0x807E526A27E38B0CULL
        },
        {
            0xC2BCC559AEB5D794ULL, 0x69941A29BEAB3ECAULL, 0xFE73719C324F886AULL, 0xEA75C664DF11A173ULL, 
            0x181300BCB44B23B7ULL, 0xCCEACDEF9D4DCBC5ULL, 0xE7F51DEAD2C57B1FULL, 0x9D4860445B6AFAEEULL, 
            0x3FFE5C572779402BULL, 0x299482A552796050ULL, 0xB64298DC98F201B2ULL, 0x58C14E31B3DDEDD4ULL, 
            0x6ABDE6DCFD8508DBULL, 0x2E1AC111FC85C54BULL, 0xDD27CB590AF361C8ULL, 0x9ABD37F999AB490CULL, 
            0xAD417A68D178C5F6ULL, 0x671BBC198EA41B2EULL, 0x0D2C1E606CB05166ULL, 0x145CDAD7C65BADE7ULL, 
            0xC620A3E818543A19ULL, 0xFD61CFCCE3F0607FULL, 0x2DA5FBAB3B6AB6ABULL, 0x0FB05177107BB687ULL, 
            0x7CC113FB9BD40FC7ULL, 0x68BC91CD8A1C1331ULL, 0xB06FA62526B1CF1CULL, 0x25D310B91E4A650AULL, 
            0x4112EE0B3FE2AEC9ULL, 0x15C3434CB942FA4FULL, 0x6441619E381120CFULL, 0x98F989FF4A7B629DULL
        },
        {
            0x12BBEDAEB6B11467ULL, 0x2AD2E4EEBAD76EDBULL, 0xEC9E4E27580ABB21ULL, 0x37C05F6EF11BBCA9ULL, 
            0xBC20B4B8DA660BC1ULL, 0x05D635155CB3C188ULL, 0x8EB706342BE22C40ULL, 0xDFDF0A3D10C57E92ULL, 
            0x6B87B84EF7861B99ULL, 0x8FF8D81280D9CB03ULL, 0x949DDB7E97E09AB4ULL, 0x258C628904779F28ULL, 
            0x8FF94FC5BFE09321ULL, 0xDAE53CEE627471C1ULL, 0xE6C8151833184F39ULL, 0x99464D9EA41BCFC4ULL, 
            0x49FA56EA1346BB56ULL, 0xB5573DDEE7D9F19FULL, 0x7481F3EB162A4E66ULL, 0xF757CB7E515D2F03ULL, 
            0xC9B44AFA8B4D185FULL, 0xF86C18F8051A0364ULL, 0x5B2C9A3E8BE63510ULL, 0x868401EF6C66C300ULL, 
            0xAAAB943D1B3887ABULL, 0x136CEB8BE7DC3526ULL, 0x23BA675DE961A7F3ULL, 0x2608A847BDE27FADULL, 
            0xC1303D31B637B2CBULL, 0x905EA63E6EA68E77ULL, 0x6F1249CEEA1482CEULL, 0x69C89A3DEFD4DB02ULL
        },
        {
            0x1CEBE216F1CA0EF9ULL, 0x3F2A5120E5C782A6ULL, 0x4092E387FFFFE21DULL, 0xEDA5618DB9182C22ULL, 
            0xED2555006FF9A616ULL, 0xEBA2943F8556C6EBULL, 0xF2DD093F9E5C7750ULL, 0x5AE4F22BEB6B6C28ULL, 
            0xD9F8BA9C729BB448ULL, 0xD13B8E3866DB5843ULL, 0xEF85C3669F95C80BULL, 0x6BC01BD46C42CBFCULL, 
            0x9A9F6091BA0AA68DULL, 0x5F6221926DD8D08EULL, 0x81E8FCF5861F5B73ULL, 0x350750E2B1AF402CULL, 
            0xF33E24C2FB51FCEAULL, 0x52E8F400332E6852ULL, 0xEA9A53C068C2A378ULL, 0x7155087B52FDA10BULL, 
            0xD1030AC681EDA388ULL, 0xA101CAEA7E1165C0ULL, 0xDF1BA455FDCBE991ULL, 0x7B345C4A9A8BB64BULL, 
            0x6B429DD3F5D0035EULL, 0x6102DB596F25D605ULL, 0x24C1231AA7A2F9B5ULL, 0x0CAD63F6C6E0EC79ULL, 
            0xC4357ACDA8EC7BE9ULL, 0xDEB3305AD2CB3EDBULL, 0xE40F6E11AA3C3FF1ULL, 0xA960725A34F65E27ULL
        },
        {
            0xFDE38A66B1739B82ULL, 0xBD34BAACA8D493AAULL, 0xB12B9DB2164CE20FULL, 0xF6F45BBFC01B4AFBULL, 
            0x46A41C4D6E334D44ULL, 0x37FE055374204189ULL, 0x50A0B54A5093C7E9ULL, 0xCA5E1D7F06878125ULL, 
            0x18E1EACB1E312A16ULL, 0x97D9149A0B6D268AULL, 0x3DF6AA95C0B84F42ULL, 0xE1BB442A39E584B0ULL, 
            0xB6C1CEE0762311A6ULL, 0x95DD8CF0B02BA8D3ULL, 0xE2F43602B20A6A1EULL, 0xCB2D49B52D5867B0ULL, 
            0x6244D663A561CF0AULL, 0xD6795C7E7A4A8FC9ULL, 0x2EBD155A945FC44EULL, 0xF3F495F7AC3249BDULL, 
            0x05692330432EC929ULL, 0x4779EA1A9D4A94A6ULL, 0x90F92F507998EAB3ULL, 0x31F8C63D727B5258ULL, 
            0xC734C1656906C9CDULL, 0x83CCC69FA9BA7060ULL, 0xDEEE30EA3C3B4AF0ULL, 0x0EB42E50FC2743C3ULL, 
            0x7523B2950236F94EULL, 0xCC6F0D1CC350A628ULL, 0x3B4DCBDAB8ABC1ABULL, 0x9CEEAD19C2806ED7ULL
        },
        {
            0x39D5A9CBC1751FA9ULL, 0x074B0FE295C83721ULL, 0x9940538A685F8446ULL, 0x1919A25923AD4BB8ULL, 
            0x3D5761DF528040F3ULL, 0xD0156F2430160DD9ULL, 0x0C7DAA2DFB6F56D6ULL, 0xC55B9AA98748D987ULL, 
            0xD80F5F38C60A6A38ULL, 0xE84014E5750E5A04ULL, 0xCD703D2DA6DCAB31ULL, 0xD4B53FA64C1B24ACULL, 
            0x6F741671F431AEE9ULL, 0x350D3E9A28DA56D4ULL, 0x66F6FF4FB7E48780ULL, 0xE11D24AD2FFC2B2CULL, 
            0x72B611AD81D68DB6ULL, 0xF88F7996E22DCC7DULL, 0x240D55C2843B6BD5ULL, 0xC00656A18A643B98ULL, 
            0xDB6BFDC031F9E8A5ULL, 0xE026B1DC0B75E451ULL, 0x7A1C6406859D09DBULL, 0xA9C88C5DFA6D49B0ULL, 
            0xFB184984260D2056ULL, 0x9F12A40D66247F5AULL, 0xE8F29023B41B164EULL, 0x237D416E5A5A3653ULL, 
            0x48F6CCA0C6A46657ULL, 0xB7F0546B5A1479E8ULL, 0x8B9A60D850E08BA6ULL, 0x33FDAD761107F828ULL
        }
    },
    {
        {
            0xF3D8224B0E475027ULL, 0xBDE18DDDFC53FF92ULL, 0xA742E1277E6757B5ULL, 0xFD58FEF5538E8F8FULL, 
            0x36349BA1B3FC11E1ULL, 0xEDFB6A147A384E69ULL, 0xE520120ACA15087CULL, 0xEA6ED5B5EC98F69AULL, 
            0x29117F66E049B45CULL, 0x2E43AC8E3DFE7827ULL, 0xE52ED611CF2A34B0ULL, 0x2A87C2F5B26AA7F7ULL, 
            0x5D277B8C81DC49B1ULL, 0x5415435F1D20C567ULL, 0x18D4BB07560CEB68ULL, 0x0D3DAB038291D907ULL, 
            0x6C208335AB4F4FC1ULL, 0x6B090940E00AF3ADULL, 0xC9EC54D54B8EC38AULL, 0xDA9E2B4ADFAB62E1ULL, 
            0x301D3FE7076D9A0EULL, 0xCBE00AE0CC72C8A3ULL, 0x9EE8D767039A0E39ULL, 0xDEF4CEC15426B7A3ULL, 
            0xC8F7F98B0428201AULL, 0xB0E66649DC5C501CULL, 0x7469E61A4D115D36ULL, 0xE8C40A931F2D8FA0ULL, 
            0xE7822FF41E7403ADULL, 0x4F350551C5B0C799ULL, 0x6CE2A9883F2A9E35ULL, 0x85D695A6C7F510D3ULL
        },
        {
            0xD3A1E3DE9523374EULL, 0x277FE22E336C6BB4ULL, 0xB63C19476057D73DULL, 0xAFAD2E4F5693773CULL, 
            0x4EA0D7022F649505ULL, 0x36EFA0E5C1AF203DULL, 0xD87D28F4EA779DEAULL, 0xAC0A268CE1A37B92ULL, 
            0xE8AFBF1D59607A54ULL, 0x554A778368A19793ULL, 0x169F1FFA65C6CF6EULL, 0x93774F65178016D1ULL, 
            0x10F924975E5BBA69ULL, 0x15C061046FC93ED5ULL, 0x09A85B6C7D43628EULL, 0x17B2EAB4ECD026EDULL, 
            0x562B4282D8DEFFB7ULL, 0xE1FAEA64A3683481ULL, 0x15B684D11B179FFFULL, 0x42959E5D89A96540ULL, 
            0x96C7243E97F1CF69ULL, 0x6F2677F9A81718D6ULL, 0x96C1DB630068A719ULL, 0x7257ADD32CBB7713ULL, 
            0x85E773825AEA9AA7ULL, 0x3317043DD187FD54ULL, 0x9CF6F1D301998148ULL, 0xE777B0953D35BC1CULL, 
            0x01040B32BCE3528AULL, 0x153C5B0DACBB3A90ULL, 0x3584F5F9059AB98BULL, 0xD1C70D63B8D5F691ULL
        },
        {
            0x34B10BFDC26C9186ULL, 0x48CC9D7942A2CFCCULL, 0xCAD7B65D19CD79DBULL, 0x9756CAAC379DC267ULL, 
            0xB5FE23125FF6C191ULL, 0x276D0E78AFF95B2FULL, 0xCE491ED5E38A7D86ULL, 0xB13D895807C1A5B6ULL, 
            0xCD91E1DE7943050FULL, 0xCF4DF1C9EBD1A974ULL, 0x614716DDF115DBADULL, 0x72E4FC179090E28EULL, 
            0x29FDE22E946EEA55ULL, 0xA7FCEC8D1F30BA4CULL, 0x2A6B1D7F4EF6CCE8ULL, 0xABF86B49A5BFC2E6ULL, 
            0xE9F4E17B051E21CBULL, 0x8FFADDD38094B595ULL, 0xFD6178D8E12BF4E1ULL, 0x56634AD9ED5EE719ULL, 
            0x98E9D1E99140C633ULL, 0x2E859057D6920E15ULL, 0x69C41D50ECA52944ULL, 0xBB9805E34CA46BACULL, 
            0x7440A35E9FBE4093ULL, 0xBF2D8C7719606CFFULL, 0x513A00A7CDF0C46EULL, 0x828A68EBEA1C6CDEULL, 
            0x0E19243BDC089A41ULL, 0x39DDA42020F0BE01ULL, 0x111661BF439E5A5AULL, 0x32E1E3CB1B393319ULL
        },
        {
            0x5AB4FC98EBB917D3ULL, 0x0F64074D0D2FA214ULL, 0xF881EEDBCCF5AA6EULL, 0xFA54B3E5C74B9DE6ULL, 
            0x90AFE232D23E861DULL, 0x11B2E06306DA10B6ULL, 0x1DEEA36B72D4E5C7ULL, 0x8AF90CF265537D64ULL, 
            0x335D82DD40E451B5ULL, 0x2A84D1047AA3679EULL, 0x04F0BBF0611954E5ULL, 0x2B417B54C7C779E2ULL, 
            0xCC5145501EC048F0ULL, 0x09F7D2CA257A2462ULL, 0x25252F75D53E0A42ULL, 0x376015C812C0E0D6ULL, 
            0x6CE8ED969C3A17A4ULL, 0x994CB20AEC4B8BAEULL, 0x52A79568FF0F3718ULL, 0xF99303F42CC99CC3ULL, 
            0x6B65C40B66B43234ULL, 0x722E3899D9609BB5ULL, 0xB936515BD565E4EFULL, 0x17E082A7887818BEULL, 
            0x542BC4A79FCEA832ULL, 0x904965FCB456B633ULL, 0x66D1E850484E311CULL, 0x4F91651A092140E5ULL, 
            0x88B31A8C99FCE838ULL, 0xEAABC1446DFCA4B8ULL, 0x4BA069ED0F31F38DULL, 0x71F3CD9615D9A9A8ULL
        },
        {
            0x30E2E4F82B5EB90CULL, 0x7A7460BBB22A0E31ULL, 0x262D34237FC53E99ULL, 0x49CBA18CD9FE4319ULL, 
            0xC20D600F22E2EE06ULL, 0xD48587EB0DCED071ULL, 0xA57A5F4AB9313699ULL, 0x13EC1F1665F75792ULL, 
            0xC0C819475BA57022ULL, 0xF6829668300B0633ULL, 0x4ADBFE905AFAEE00ULL, 0x957E99607D3C72F5ULL, 
            0x59231ABC048A3C53ULL, 0x0D37B8825BFFC0D1ULL, 0x4C4FA84E92107AE5ULL, 0xA096479A4426A268ULL, 
            0xF97B7C804CF53C9BULL, 0xE59AB5B3F1CB65E0ULL, 0x252A121A5C492154ULL, 0x57B6D5B39F351E1EULL, 
            0x918FF27F3EED6DB5ULL, 0x83DF3FBC386CF195ULL, 0x6B764073DC39D7DFULL, 0x6487553DCF748B87ULL, 
            0x2F876E45A8DC8A54ULL, 0xB919B50E232F71C0ULL, 0x542B6F7B0FC86C6FULL, 0x6EC0C9AA4B1A2CC7ULL, 
            0x03A45A571C70AC52ULL, 0xCA241451A91F2C08ULL, 0x4DD7C6C707DC7C34ULL, 0x327B1DD6C2B88713ULL
        },
        {
            0xFA77D59C2E1726BBULL, 0x49610677F4F4630CULL, 0xBC5D65D5E40D1719ULL, 0xCA104EBE5A6CDA3DULL, 
            0x58A5B469D3FA3944ULL, 0xF6CE95ED6D956C4CULL, 0xCA41BB45B94EE474ULL, 0x1349265066DBCE68ULL, 
            0xDBBBAC16AEDD8174ULL, 0x1477D0C1902402A7ULL, 0x356783592D4DB5AFULL, 0xE75B9158DC369638ULL, 
            0x177860218D8F2A00ULL, 0xDCCB9E295F5ACB0BULL, 0xE8FE79AF17C694B2ULL, 0x7976FBB87340BCE1ULL, 
            0x4D87AB1CED35AC4FULL, 0xD4FF4BB9F156F014ULL, 0xBC9B4865C0883AABULL, 0x1EE0CF19DE540E58ULL, 
            0xBA7CFE65711E78F8ULL, 0x08DB418B631FB032ULL, 0xD7FDAD867127B62FULL, 0xDA82841DD406A28EULL, 
            0xC8043B598369CF55ULL, 0x94BC36326D6E315FULL, 0xA15E40232D647280ULL, 0xD3C29BCFF6C8D9AEULL, 
            0x40ADDD56E15D1B1FULL, 0xB4C31580EC55B4A6ULL, 0x8370A92325807CDAULL, 0x530D7D4D77B805FBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseAConstants = {
    0x4DA02AAD2AF782A6ULL,
    0x4CFAF3B592A0988FULL,
    0x4E0FDC28A0CED528ULL,
    0x4DA02AAD2AF782A6ULL,
    0x4CFAF3B592A0988FULL,
    0x4E0FDC28A0CED528ULL,
    0x3C7B7D62CF2E4BF7ULL,
    0xAFA54BB91256347CULL,
    0x0B,
    0xF8,
    0xD5,
    0x87,
    0xBD,
    0x1C,
    0x60,
    0x70
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseBSalts = {
    {
        {
            0x6AC3601A7AA35535ULL, 0x8B4B870A7D8FFDAEULL, 0x1501144500E760D5ULL, 0x2BFB7E8BC472F1ABULL, 
            0x5EDBBDF975C6AEC1ULL, 0xBDC45B570F1FFED9ULL, 0xCC616708F9FD54DEULL, 0xA002AD7A08F21774ULL, 
            0x2CF44EA3FA471582ULL, 0xA716C830908A90F6ULL, 0xDA2F95780CF5B90AULL, 0x26ED2697C5EF3A22ULL, 
            0x83CAEB8D1ECB5D06ULL, 0x12FBADF5F66926D4ULL, 0x8FFD7521B25C5452ULL, 0x6B7CEC967A6C16A9ULL, 
            0x7080AE2F5F412247ULL, 0x959510E962663D08ULL, 0x8B06F7AB2E346172ULL, 0x4CD0F6D69CCEA3A2ULL, 
            0x34469388E782D96FULL, 0x6C4E685E380F35A7ULL, 0x9901E8F8194DC257ULL, 0x449CEA0501E5261CULL, 
            0x1BC008F42F0395FCULL, 0xC782DD0FF03B45CCULL, 0x38AF20A29BE23197ULL, 0xF59416DF98698BD4ULL, 
            0x1B9A59D63D547AE6ULL, 0x11AD1DF87E97BDAEULL, 0x996FE823111F1E64ULL, 0x0F99DFAC72442380ULL
        },
        {
            0x1949E3FFFEFD5662ULL, 0xC87878E5FDD3C8C4ULL, 0x03D256C601EC2E93ULL, 0xAAADA95B48EA4200ULL, 
            0x3D68A806858ABFA8ULL, 0xDC986FC3B0B59B4AULL, 0xF3BF82D2C801404DULL, 0x943D442194BDB859ULL, 
            0x3A390AD02CEDA575ULL, 0x7FB99338BFD5D3A2ULL, 0x4EB457C2918B28FAULL, 0x9B7C537BB7191BEFULL, 
            0x8D0111572410E7EAULL, 0x8C444426C0AA6E83ULL, 0xCFD52DE702ED2843ULL, 0xADC06D1CB95E6008ULL, 
            0x865D595DF2A80E28ULL, 0xA4904BE15201F090ULL, 0x72FD0609838E72B5ULL, 0x0EFC25FE4041E0B9ULL, 
            0x98B59B97AA11B221ULL, 0x295728AAFF751705ULL, 0x71FFFD2543FCA6F2ULL, 0x50FE64FB9E89E05DULL, 
            0x8261971FCA22D9F2ULL, 0x3A887C515488D09EULL, 0xC4852F8D96902F3BULL, 0x651C1AB54AE3EBE3ULL, 
            0xDF5BC4777BA1CD55ULL, 0x57177904B4321D7FULL, 0x939059D7F98A40E9ULL, 0x4C9FBE29A88A0DBFULL
        },
        {
            0x0113876B8F2FA434ULL, 0xCA668A6CB58AAB69ULL, 0xC543F1EF0D5F035BULL, 0x9833BE1EAFF7733FULL, 
            0x37A5F4EC00DACB55ULL, 0xEABA852B33BEC137ULL, 0x103B8E646C5D39B2ULL, 0x3539A6681C06180CULL, 
            0xBB7630D827BEC205ULL, 0x1F685E50D66801B3ULL, 0x96E97E84B40D1440ULL, 0x84BA5DF023A9D01DULL, 
            0xEEB773B67A03CD5EULL, 0x62820AF2C8ED91C6ULL, 0x9929CFF87B96404EULL, 0x4AA63D330C700CBAULL, 
            0x3FF58E5CEA7BA9F7ULL, 0x5421E66DCC70EA62ULL, 0x296AC616BB46744AULL, 0xBF85A0A2D46D76D6ULL, 
            0xBB1D9BF2A9041434ULL, 0x19914349428BCA20ULL, 0xB2C5430BB8DE9944ULL, 0x1209836A4FEDA2D3ULL, 
            0x9111389B9EE31F80ULL, 0x6B669E8F4FCF73CEULL, 0xE7C7D8AC24ED550CULL, 0x3B5CE3BDAF7992CDULL, 
            0xBF410255235615E5ULL, 0x01C73D4128631C38ULL, 0x6708A9FDA77F5F89ULL, 0xB28C406409F7FC26ULL
        },
        {
            0xE7F78E2E1CA2A9F1ULL, 0x11BA0DC90A683F4AULL, 0x423D7923038BEC0DULL, 0x87EEBC5745157965ULL, 
            0x049FFB7E85643EE8ULL, 0x0D76510559B41C69ULL, 0xC0B84AD791CE95A7ULL, 0xCD5A8F7C16FEA97BULL, 
            0x970E8BBA487FD015ULL, 0xA1E65707E1E08F97ULL, 0xC7DB31B0A41BD659ULL, 0x3D56199BCAD42C13ULL, 
            0x5D3141CD61A1B6C6ULL, 0x071823C1353EBD43ULL, 0x14CD5DE86059797CULL, 0x2628A79AFA3F83A4ULL, 
            0xA16C76F744D9CCD2ULL, 0x57CC72471D4272B7ULL, 0x6DA52272B5C4F58FULL, 0x9D43C1B3D10F9706ULL, 
            0xD9961CAFB78D7BB8ULL, 0x43CDAD673EC1B866ULL, 0x88512006FE57A951ULL, 0xF745378C32B1D8FBULL, 
            0xE193727902F4BCB6ULL, 0xD89801F19AD264AEULL, 0xA339D5284D5216F4ULL, 0x32292E7A5EB92A1CULL, 
            0x55F5B101268691B9ULL, 0x9C7B7018D52A7051ULL, 0x57ED2FFEED83F077ULL, 0x2B285ADD1448B3AFULL
        },
        {
            0xC77CCD833A910983ULL, 0xCA22A1F2DCD50474ULL, 0x59859BCEBDDB51D9ULL, 0x0E698274FC656E73ULL, 
            0xDBFCD667B6B67A53ULL, 0x0DEAA0D7D046F79AULL, 0xA152DE3609734B4DULL, 0x7E86EC0216D1AD72ULL, 
            0xD2B4E379B5851B1BULL, 0x169253F2D95D1387ULL, 0x9F9D6B64F706A95AULL, 0x13B1CFB53B985279ULL, 
            0xCEE98F858F0E5981ULL, 0xF2FDD5514F6F3176ULL, 0xCD2C976AE74ECFE4ULL, 0x7B4EA135175BF8FAULL, 
            0x182C5BD912E6E65AULL, 0x26CD3AD51AAD6386ULL, 0x86F907D1666A6036ULL, 0x51F83CEA1920D701ULL, 
            0x6834D7FFF72459E6ULL, 0x2A41E5FC699A6D39ULL, 0xF7AF1DDB81DA0BBEULL, 0xFB0EC22B8C40F777ULL, 
            0xA900C68F002BBD8EULL, 0x17FECBCF2CD0B2C0ULL, 0x5EA9988D717B73EAULL, 0xC5C064C52CBFA5F6ULL, 
            0x4BD4141C9598B66DULL, 0x936B5BF8F1359FD1ULL, 0xD11E7020A4246A14ULL, 0xC181967AFD7CD5E5ULL
        },
        {
            0x9CABFEA05639DB9CULL, 0x6BA5556EAAD7B1D2ULL, 0x2F56B770052D8B6BULL, 0x7E95DB7BCC089708ULL, 
            0x218B8E56F589395AULL, 0xC23B0E199D5B2AE2ULL, 0xE5C60258930E497AULL, 0xC1AD8040E127E341ULL, 
            0xC52473FEA7E6E67FULL, 0x8C7417D707586D7CULL, 0xC2FBE567ECFFE543ULL, 0x640FD854D2377A68ULL, 
            0x2918C93E3A2F36FEULL, 0x5073D8B8EF4E365BULL, 0x6E76490229A616F6ULL, 0x9F23182BF9E4587BULL, 
            0x9EF0FD18DB9FA666ULL, 0xB11F0DFD38634310ULL, 0x7E1732A5055BCD5DULL, 0x6425AF3E08D40EDEULL, 
            0x57BC41ED4834670AULL, 0xDD1AE878B79D14DDULL, 0xDD6770D57CBFF5C2ULL, 0x154EDDA160C9B9E3ULL, 
            0xA36EA2CB6D7FF96CULL, 0x3C4FAAFC7A856175ULL, 0x09BB24CE11E9A5A6ULL, 0xCC9AC4299E172C4EULL, 
            0x23DA10EB9FACB79AULL, 0x3887D0CE3F414D18ULL, 0x77BCEBE23B8C0A00ULL, 0x9170988F15311F7EULL
        }
    },
    {
        {
            0x1155B0E500F08C36ULL, 0xE8D102C36129B426ULL, 0xCC716EE3829B0A9CULL, 0x80B3A77ADD792889ULL, 
            0x59A9B248825C4944ULL, 0x44BD958A7848CD50ULL, 0x4001CC97B9FCE16DULL, 0xE7812351924D409FULL, 
            0x6A3F070E49B42DEFULL, 0x788ED6D4CF6F5F38ULL, 0x9C89A60118E0817BULL, 0x19E87275600C7E83ULL, 
            0x2E141F7E93EED67AULL, 0xE3FD2642C20BD8F7ULL, 0x50DFA5EF2D14CD12ULL, 0xB2C3CCB106F05DD9ULL, 
            0x59D4E910C3D59235ULL, 0x06922656F195078CULL, 0x587C51FB3E2502B0ULL, 0x7AB7CF50DB97537EULL, 
            0x27B806840320ABB9ULL, 0xB80E5A32DF8AFC6DULL, 0x74E7BF97069AB4BBULL, 0xBA917D0FBEAF2A71ULL, 
            0x773F1A5D1FE940B8ULL, 0x11A3E672CA95C287ULL, 0x6A36265ECD54C508ULL, 0x8ED084CF1A7B394FULL, 
            0x007477904E946FEEULL, 0xFF2B196484023861ULL, 0x87F31E3D4E5CBBA0ULL, 0x7C8CBCA39BEC290BULL
        },
        {
            0xAADFB850A7BCC545ULL, 0xFD2B0C2DF203BC77ULL, 0x0D80D8643B38689EULL, 0x3E1877C8CF72E642ULL, 
            0x023056E930E07ED2ULL, 0xDEE40AFEFD9E7E92ULL, 0x527109FF8602EE72ULL, 0xEDC6475EFE89ED90ULL, 
            0x895A145EFC61F2D7ULL, 0x8EE99CC64680FDACULL, 0x92372E862FACD5E0ULL, 0xA163F253475C42B3ULL, 
            0x16369833F059A674ULL, 0x559B4DD3C49673F2ULL, 0x0CCB9C416DFEC4E5ULL, 0xE13A01F5ABFFC0E0ULL, 
            0xA48B689CD410CD1CULL, 0x31C6345A80FF7675ULL, 0x03BA5757BBC5017AULL, 0xB5315C9D66832570ULL, 
            0x83021F7DC4F79BCFULL, 0x34FB235F220ED03BULL, 0xE2BE2488EF0A3E33ULL, 0x55BCC0C7964DE3B9ULL, 
            0x6F129F0928AED965ULL, 0xE05C4DB6D029B87BULL, 0x5AF554B8DEA5DBABULL, 0xDBDA38335939C7FBULL, 
            0x469A482969943F4BULL, 0xA95C256F360AF8F5ULL, 0xD9E9A01363EA9718ULL, 0xA73671820CAB26B8ULL
        },
        {
            0x1BC21BBA9166207CULL, 0xE5832493FD21CA51ULL, 0x01B85858FD647401ULL, 0x61C48ABA60413D54ULL, 
            0x61FE0E8434EBC631ULL, 0xA9DB8C5D83A78A18ULL, 0x3F42A516DC115AA8ULL, 0x22970B70F618322CULL, 
            0xABA05B92DC360D8AULL, 0xE7315AE61A7243A1ULL, 0x585793EE581D2312ULL, 0x08C9D9EA554B74E6ULL, 
            0xFF5624745AA9B857ULL, 0xA4308AF26DFF496EULL, 0x5230BB8D82780323ULL, 0xEB1B01F4D9DBD251ULL, 
            0xF557A23F77F06CD0ULL, 0x5A5B04FC1530DDEDULL, 0x54A04A4542CDBC87ULL, 0x503F715A82970FB5ULL, 
            0x6E7335543784C2A9ULL, 0x5989F496AA5E6EF5ULL, 0xD875BAC13C9FB175ULL, 0xE1A92F6109A6E4F6ULL, 
            0x0E24F42451389CCAULL, 0xBE5FF357A1123006ULL, 0xA86D62D78F0A64E4ULL, 0xA2FFCC5B39109227ULL, 
            0x0CF9D7AD4172227EULL, 0xB38A0F179C9E7799ULL, 0xB5269B3B7C35881DULL, 0x7875BF462E34BF69ULL
        },
        {
            0xE93C8C5A830B27B4ULL, 0xDBA6960D9F03CBD5ULL, 0x3EC0292528F7D53FULL, 0x18F56E8412E46442ULL, 
            0x7048DE0D18A9C4CBULL, 0xEDF1F4F3D66C4129ULL, 0x22392DDE4AE22F2AULL, 0x93AA23383635E7BBULL, 
            0x3B1864951320B40CULL, 0xAF0CF80AF3361EF7ULL, 0x2B36A210B0E605AAULL, 0x860711A02FFC839BULL, 
            0xF28A514EAE8292CAULL, 0x5A10DE2C3BCDE98EULL, 0x6E90B8EC06E16413ULL, 0x944F17F62D6B692AULL, 
            0x00BD76A621F398EDULL, 0x17D6CE6C8E63D42AULL, 0x0C7028C2B8677BD2ULL, 0xDA590282995956E4ULL, 
            0x5DA44C62DBCA028AULL, 0xC8E543C2A4E473E9ULL, 0x8DFA0730D625A748ULL, 0x9B820C3A6281F89FULL, 
            0xE23AD73EC426A2F1ULL, 0x9BA48AE717753926ULL, 0x280B9DAC664FB21BULL, 0x4FE3274E86883F33ULL, 
            0x232C8EAF5F49AB26ULL, 0xDB8BD3142371DC01ULL, 0x7A0DB0E7FA841B0DULL, 0xCDFB6BB4288EEB36ULL
        },
        {
            0xE3394417801BA815ULL, 0x492E833A05DBB602ULL, 0xEAAA29EB75331FC5ULL, 0x2E81B6FC31902BD2ULL, 
            0x43E6713B924E5E07ULL, 0xE52E0B1CF556A3C5ULL, 0xF57A7217B45B9AD6ULL, 0xBDF9C3EF4D6E3B9AULL, 
            0xA9081A087123FC5CULL, 0xD8E7CD82344B336BULL, 0xB8C5CB8E1C6145DDULL, 0x56DD5A579F57D030ULL, 
            0x3774F60076B90C11ULL, 0xB62002B8C5B14138ULL, 0x279E1744950C6C1BULL, 0xA62F79D01C9CC3EEULL, 
            0x5DD9CB4CE16AEBFBULL, 0x2A49CFBD0129749DULL, 0x3392034CD9D6148FULL, 0x568570160825066DULL, 
            0x0DE9F8A9AEB5F288ULL, 0xADA6450BDED8DF7FULL, 0xF11B5AB46F23D44FULL, 0xB0A22F756FFADB8CULL, 
            0x99FDAFD7751CC3E7ULL, 0x6DE6A657C198AD6AULL, 0xBEFB0889A9F68CFFULL, 0xBD2A2CC07B23B41FULL, 
            0x14F34C7797C505E1ULL, 0x64A6E7D1DA64F52DULL, 0x60B5485F4FD7B3F1ULL, 0x1E98BA294F8EE2BEULL
        },
        {
            0x4EA5BD225A6F4920ULL, 0x242FB19DC84E4B53ULL, 0x92254A318C20249FULL, 0xDF7EA54924F8D18CULL, 
            0x4CA017E53CB96899ULL, 0x787AC1466AB1F057ULL, 0xE8D8D72D121B3E5DULL, 0xD13B9287FCBACA0EULL, 
            0x85A6864FE63F13FEULL, 0x0724391FFE3271F8ULL, 0xC1B99B2E8FB125C5ULL, 0x64E40D8C6C00CE56ULL, 
            0x48F7AF38DC812084ULL, 0x71F14E452F602800ULL, 0xAE9AC870ED7F35E9ULL, 0x860D2D1DF4E87AD2ULL, 
            0x120DB9026F0E36C8ULL, 0xC6132D50E4548E16ULL, 0x04DB8F9A113E5020ULL, 0x03DC524BBA0087D2ULL, 
            0xC30565C9525B55FAULL, 0x8B230ECBD890EE89ULL, 0x1C8486FF62FD5FBAULL, 0x21CE3EADF2E9B3C2ULL, 
            0x19ADB8D8CDEFBEF7ULL, 0xC4FF2D1D35EF67BAULL, 0x0B16EB0799323090ULL, 0x6AD94C69AAEB59B1ULL, 
            0xFC9791A9113A9772ULL, 0x0F0EEAF3F968B9BDULL, 0xA733E20C2710C60DULL, 0xEA3E388A91BDAB3BULL
        }
    },
    {
        {
            0x531509F1B213D068ULL, 0x393138BE97F34F15ULL, 0x7D3F7BE403239BBAULL, 0x08EE4A2F98BA59DFULL, 
            0x7FECB4C60E6C049FULL, 0x459032E5F75DBB4CULL, 0xF53EACC80C468FDFULL, 0xD550C8CA259A1DA8ULL, 
            0x81DBEE5ACB6C7F7EULL, 0xD9C8775E2A3314A6ULL, 0xFCCEEC01265B624AULL, 0xC30F9360A2359DD1ULL, 
            0xB02ADFF53B4F80ABULL, 0x783FB35A072F7A4CULL, 0xEFC76925F9AAE8A8ULL, 0xB4494F350F578336ULL, 
            0x85CB8C82960BC2C0ULL, 0x47A21C8A13D42F22ULL, 0x94346608101C2AC2ULL, 0xC2B8EAC4D2C2A887ULL, 
            0xBF980E7CEAA22968ULL, 0x593DF13419D62612ULL, 0x226C0FA5E1B29A83ULL, 0xADD9AB23F4099FCAULL, 
            0xB16F0C92C517B69CULL, 0x956A833D343BC9D9ULL, 0x72E56097E1F0C30FULL, 0x6DF2FC30E4588B99ULL, 
            0x93657D943EB870B7ULL, 0x820E93D5A25BC266ULL, 0xED3B615BC6BB15BAULL, 0x70DBC245CFACA98CULL
        },
        {
            0xE5DBCF4847F5F779ULL, 0x5EC470C33B3E0FF8ULL, 0x109A918221AD9080ULL, 0x7148AE81BF101C99ULL, 
            0x0FCAD67766DC38B4ULL, 0xA9D19B6839EDC503ULL, 0xA145DA1F0F7054BBULL, 0x2CFBDBD9D0751FA9ULL, 
            0x0976B40BD5502252ULL, 0x0351DAA0163835D6ULL, 0xBEDBC2558219A327ULL, 0xB09F679625978EB4ULL, 
            0x626851902BAC65EEULL, 0x3A11336256186FF4ULL, 0xF31CFB1FC949837DULL, 0xF46062A3BBF43CCCULL, 
            0xEC5258ACE776DCE0ULL, 0xFD790D5DD9DEEFBFULL, 0xCFF982EAB71075C4ULL, 0x14A5D1BFC38B9030ULL, 
            0x34898DC3DF40B879ULL, 0x6CC668F0E157CFF7ULL, 0x41CE96A3B2C1376DULL, 0xCC430C1636792C43ULL, 
            0xAA671F93913C3E3EULL, 0x7876C605EBCC3E9AULL, 0xEEDD4A0AC7460BFFULL, 0x8AB0B3DB2E68E428ULL, 
            0x54650B0E1B862DD3ULL, 0xBBD0E35C12ED59AAULL, 0x5451E555ABA3606FULL, 0xC0829BEE3B3312EFULL
        },
        {
            0x2D6D75431B9B6940ULL, 0xFC2ED23D5CEA3BDDULL, 0xD45F147F72C45F53ULL, 0x11CBD4F6CD684D6FULL, 
            0x4E92E46C437216E3ULL, 0x27951F116F27A692ULL, 0x2E48A6E8C3D6DCD8ULL, 0x428B6D592B11C5EAULL, 
            0x8707C5701B71763BULL, 0x000D987F1F49B60CULL, 0xD56ED458AB60D1D4ULL, 0xA68E650DC1EEDD2DULL, 
            0x5835B818D7A19C06ULL, 0x4072575E34C498C0ULL, 0xE137E35632C99B91ULL, 0x6FC7B91AF7254987ULL, 
            0xF4F680A7FEFF85B0ULL, 0x791537C3FFBEE38BULL, 0x40567B0E450F3397ULL, 0xAC52D36696BE653BULL, 
            0x17D99A4C86867446ULL, 0xA880C727CF64D6EFULL, 0x902CD6F1358B236AULL, 0xB96CE110FB5CA1B5ULL, 
            0xB19E69B280F502C2ULL, 0xC2C76715E43CA5C4ULL, 0x1834019B8E9402A7ULL, 0xA1E75BDBE0BDBAA5ULL, 
            0x9A83D48326564C44ULL, 0xD28CE4E1CB0D29FEULL, 0x4948AFBBAD444B4DULL, 0x570FBEDCC5866A95ULL
        },
        {
            0xE1449DA25B432934ULL, 0x12852CF5939F6A25ULL, 0x03EA80E50177D045ULL, 0xBA805DBBAA02C575ULL, 
            0xB6F16FEB919A0563ULL, 0xA54F0CE970218408ULL, 0x9D6CC0F2B86E204DULL, 0x60FAE69779F2851FULL, 
            0xE9848633288D7C0BULL, 0xA6D96C07A5273964ULL, 0xDD7D0415074F4D18ULL, 0xA39616D431B57428ULL, 
            0x976118296CB1D466ULL, 0xCEBB5FD011470035ULL, 0x7B48AC2E1F1978CBULL, 0x8B903D617310D6CAULL, 
            0xB49903D19059ACC5ULL, 0x02DC686B3090FB56ULL, 0x7EAE92B0E9D0EE4BULL, 0x7830AB9B0D26FA70ULL, 
            0xE2324C64D4E895B9ULL, 0x59A1CAB7F5D960F7ULL, 0x987D6E57893EC86BULL, 0xECCE3D3C39F9FEEDULL, 
            0x289663025F9C0146ULL, 0xA57CC2A3A86C1E42ULL, 0x0DD76FC28BF87B8FULL, 0x46574B6ADCA2A25EULL, 
            0x1D57D857DD43040AULL, 0x5730020D8E3BA4E9ULL, 0xBAE16CBFB5FA5692ULL, 0xE8A07BFAE911D05CULL
        },
        {
            0xA83465F6645D462CULL, 0x5A9147FC2AC22317ULL, 0x84E0F412CB3ED845ULL, 0x25C9EE04D1A139C0ULL, 
            0xE5DD224B6C4D6CCBULL, 0x1D9C56C0CDC38618ULL, 0xD278EB7FA50D2CEAULL, 0xC8D176F9FC7390F6ULL, 
            0x3047AD730A2F165FULL, 0xC7AF0985B4A50076ULL, 0x0B748824AA3BE27BULL, 0xA8C75DE88DE8BE80ULL, 
            0x17FEA98270E9FD2BULL, 0x199BE29E9BA25D25ULL, 0x86627BB0150F2EBFULL, 0xA591E215BE43DE79ULL, 
            0x743E1CD6C1911349ULL, 0xEA216F679DBFACAFULL, 0x4517B6D9F519C524ULL, 0x9CB400B3EBEB92F3ULL, 
            0x839A86FAF942E2D5ULL, 0x47BA4A5BAE1AB7D8ULL, 0x8C0E9EA39BFEB6C3ULL, 0x6930F97277ABEBD1ULL, 
            0x83FFFF4E0CA2E372ULL, 0x3CCE5F14075DC04CULL, 0xA46602E882724D26ULL, 0xFB11F30F05F2D932ULL, 
            0x4DE36A0EAAA49517ULL, 0xC79A06C956950E66ULL, 0x2E1CB43EA84B62A0ULL, 0xD8FAD6E4DF9661B0ULL
        },
        {
            0x2078BEF49CDDC3BAULL, 0x19A41652330E651FULL, 0xF2F2551CEFF99FDCULL, 0x7FE567CEAEAAF3F5ULL, 
            0x9EA5AA35BF847D5CULL, 0xE935BB1F101B1857ULL, 0x79A2134966260E6BULL, 0x821A9B54B087CA88ULL, 
            0xE86B1CAADCFC6CDFULL, 0xE917EB8B9183A8EFULL, 0xFA0B8AD044DEA105ULL, 0x53ECE4438819525CULL, 
            0x34BC8E96983DEA08ULL, 0x07380F72E8FE18F4ULL, 0xA1529FC3063A0A0AULL, 0xD07BB1526CA598B4ULL, 
            0xABA0E1979FE79C86ULL, 0x035924E9DB18553AULL, 0xB53BBDAB0AC10AE9ULL, 0xACD9150A6EEF2075ULL, 
            0xA1832BBE07BDC138ULL, 0x5747C40E1AF42912ULL, 0x7DD81ED99082EBD6ULL, 0xC9A9D3C0F8936B6AULL, 
            0xE7B36A61D73887A3ULL, 0xDB790D27A426AE17ULL, 0xD4C4D3C6EABEDD2BULL, 0x67FE9D3D8AD839B0ULL, 
            0x9B8E1486B115B826ULL, 0xADD0965894D25B06ULL, 0x627EDCF6CF7D3B1CULL, 0x06FCAFCBDE516B31ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseBConstants = {
    0xFDA00055E5DC4C02ULL,
    0xA0019B9A5504DEFFULL,
    0xEFA9266FEC957CF3ULL,
    0xFDA00055E5DC4C02ULL,
    0xA0019B9A5504DEFFULL,
    0xEFA9266FEC957CF3ULL,
    0xE45FFE27A34A26B5ULL,
    0xD9FCBF2BE62CD264ULL,
    0x8D,
    0xF5,
    0x3B,
    0x59,
    0x66,
    0x2C,
    0xB0,
    0xBB
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseCSalts = {
    {
        {
            0x13E7E8DFB59C5AEDULL, 0x5AC065208A02AC7DULL, 0x9327C63E294D29A2ULL, 0xAF4A9DF3CD56F6B1ULL, 
            0x1D6D022252C20B57ULL, 0x69E924AF94BED68DULL, 0x303FF485BB100196ULL, 0x21E37ED59C0A9149ULL, 
            0x0A98845DD19B7C56ULL, 0x743FC9845EF3C0A0ULL, 0x1F8F11FC787D8D10ULL, 0x9D76CC1C5B578B8BULL, 
            0xB50BBAA8AC980044ULL, 0x62E8AD618BB1560EULL, 0x14D0A6A5194B0075ULL, 0x006F26BAAD6BE966ULL, 
            0xDA8B5C79520E63ADULL, 0xA9984701DBE08F28ULL, 0x42112DE969459054ULL, 0x3CB66A4818D6B5B3ULL, 
            0x4FBB664D0B12DB53ULL, 0x24BE6F711F3291CDULL, 0x697C3036A0356317ULL, 0x32805FFE93EEF7DCULL, 
            0xD88021BE6410063CULL, 0x359DFC1F6EC39E7AULL, 0xBDA60C3B48FB623DULL, 0x7F2C823843B14F90ULL, 
            0x2790C41F3DA1B0E9ULL, 0xA09A991136475DF9ULL, 0x88B98A93BB403B2DULL, 0x9112E94FA2EB21A3ULL
        },
        {
            0x65782CAC70CF7BAEULL, 0x4A9228881349AC80ULL, 0x6AA16476120C1D0FULL, 0xD283ED25828E023EULL, 
            0x6519DC12E7185528ULL, 0xC7641A4675F0C05CULL, 0xCC92330EA6C798F6ULL, 0x757F2FEBAAD090ECULL, 
            0x659D5C200D63D9C5ULL, 0xDD86BD1951DBE235ULL, 0x42A9F2D39C13D03AULL, 0x3B3607983F226148ULL, 
            0x4CB863F7F2E5D00FULL, 0xDDFB99E709049B2DULL, 0x683BADA237981515ULL, 0x311028DC5A723916ULL, 
            0x0B3011EFF0D0ADF9ULL, 0x14E8FC5DD8B8526EULL, 0x0D0105419FB4B1E8ULL, 0xBBF16D3DCC3E1D56ULL, 
            0x37E7BE021E6BAA81ULL, 0xB3B794DEFEE8819AULL, 0xD9963CA62E9D4C0CULL, 0x1E873373B0AB83A6ULL, 
            0x3A654982EED2A0A1ULL, 0x2A804B4E9AB4D895ULL, 0xE191ECE11612EF98ULL, 0x78DE6EA94434F336ULL, 
            0x95A343A1913AC533ULL, 0x20F9794E18610432ULL, 0xE7DB53BA49487C30ULL, 0x491E76473C1929E7ULL
        },
        {
            0x8BB62EFE41C57522ULL, 0xAEDFA03FC48C1B00ULL, 0x99BA74EDA8DFEAE7ULL, 0xB5BC1A232FC6E55CULL, 
            0x9086A5BE7D8F7E21ULL, 0x2BEB752F61E7FC15ULL, 0x242F3E868ECC1FCEULL, 0x203D11F6913E7B49ULL, 
            0xA96F9F82D48DE2BFULL, 0x3F769EB25558E2ACULL, 0x6820CE4834F32AF3ULL, 0xD64DB82F91EBCA3AULL, 
            0x4493D1F9E4EDAFE2ULL, 0x7BBF0B4C188CB7D0ULL, 0xA75EA9B871ED3371ULL, 0x5C469F8AD7B8BF09ULL, 
            0xA08766C06F7B39F7ULL, 0xC41E7ABE815E7B99ULL, 0xC6C732F103E63065ULL, 0x65FF5F5D20FC4240ULL, 
            0xD5EF5769BFBBAB8AULL, 0x2F1A2195EF91F98EULL, 0x823C048E5323405CULL, 0x64EB7003173D7855ULL, 
            0xB1BA62F869FF33D6ULL, 0x89A9451FD4875B95ULL, 0x1A39EA5ADBB9B034ULL, 0xCC4ACC41E6AEF6CFULL, 
            0x936C45C64BAD19CAULL, 0xE604727D81A6A79BULL, 0x3DEA0239BE79E94EULL, 0x02EAAAD7E8DF97A3ULL
        },
        {
            0xB86B8F95ABEBE9BBULL, 0xF650465F1329CEE5ULL, 0xF78B2B75FD3A0571ULL, 0x96CB9DC6393DBAD0ULL, 
            0xF30ED2468AC8F532ULL, 0x1D36B339420B7DA9ULL, 0x9686418AB218A4D4ULL, 0x5ECEC40ECA95BE49ULL, 
            0x755822AA3B5BFD25ULL, 0x6C136FEBCBE6F57BULL, 0x34C36EAF3C3D99DAULL, 0xCA1CDDDE98CA5707ULL, 
            0x89EA5213A38BD52AULL, 0xD30503850E6E789DULL, 0x4B58AB5BB2AA14A5ULL, 0xB43DDB647C36B556ULL, 
            0xFA565BFE86A3BB20ULL, 0x75857AAD5A3D0B79ULL, 0x90626BB4103AA0D0ULL, 0xA6F8EFC059E31A20ULL, 
            0xBE32C57BD74B769FULL, 0xBE3D0A6B3B2A9D87ULL, 0x34865BF963AC491FULL, 0xA4CA2C1403F8A5A3ULL, 
            0x32628D1CB21D7C96ULL, 0x127CAC804DF884E3ULL, 0x0EBCE28330F5D45FULL, 0x7BD2A15849D0A47FULL, 
            0x306CBD3C7B36413AULL, 0xF903B11CAE8ACA76ULL, 0xBFAB4687B313D1B0ULL, 0x5284100826F721FDULL
        },
        {
            0xC2BE963848E28627ULL, 0xEF663BEEC1FC7B1EULL, 0xB254784F40B255EFULL, 0x11D9A513E4A54861ULL, 
            0x37016205F521B6D1ULL, 0xA7BE7C5FD6C05690ULL, 0x6A9E99F872147199ULL, 0x4C3139E75C71FDCAULL, 
            0x69EBD72402BFBEAFULL, 0xCE39ADB4BE47D513ULL, 0xAA2DD5254D1A77F3ULL, 0x8A08F97408988DA9ULL, 
            0x8E3DDC5B93D10B77ULL, 0x5584F6F3BD34B621ULL, 0xD83342003CB13E0AULL, 0xAD782D5BE3F462B7ULL, 
            0xDDB943ACDA01A4E0ULL, 0x72B418FEC38012D6ULL, 0x8D892E9C9B97173EULL, 0x9D3069CB42861ED6ULL, 
            0xF22E4CBB76C10C27ULL, 0xF9F3F601B8500344ULL, 0x1A77DECE31F70C8EULL, 0xCE4F9581CFBE1E6FULL, 
            0x414D43F65074967FULL, 0xB71784F1F34733ADULL, 0x81D1A716F0AED7F1ULL, 0x59929A895F6A6278ULL, 
            0xB620B236C55BD805ULL, 0x7A4395B7CF9D1BE5ULL, 0x8E15B8911A0B9AF5ULL, 0xCC31D4AAD9BF9C58ULL
        },
        {
            0xAEDBA9B64F3FC477ULL, 0x075EC61CD54BEFD4ULL, 0x6DB2A2BA2F46B717ULL, 0xD7EFB732103CC9B2ULL, 
            0xA1D23A161552EE25ULL, 0xBA2803769CE298C0ULL, 0xE2D48D63B8F5A8ABULL, 0xC7EC9FBA4799F52BULL, 
            0xEECF52D7A031699CULL, 0x9CABAB279DDB0E47ULL, 0x3FB9392F6A790EADULL, 0xF675D506FD770CCEULL, 
            0x8FB9C7ADD339BA16ULL, 0x33F46EAD7970D460ULL, 0x46D8F294E7857366ULL, 0x9DC074EAAEDDE78DULL, 
            0x3C0E5811B4641209ULL, 0xD0530B445DA1BA18ULL, 0x6535F40D9FDAE18FULL, 0xBFEFE6B8272CD877ULL, 
            0x7BB239745B9E8BBDULL, 0x0E2C54B37B47B809ULL, 0x0055CB3A1421B873ULL, 0x9C0BDF524848F53FULL, 
            0xDE3D2AEFEE35AD64ULL, 0x1092B72396735482ULL, 0x7F2632E6FCB03261ULL, 0x63E9782C07F91F3DULL, 
            0xF12F3B64046C0449ULL, 0x378E704E948A5DC4ULL, 0x6EFCD54672CCBA54ULL, 0xCE31C4C44AAC16D2ULL
        }
    },
    {
        {
            0x5BC0351F88EA1C9BULL, 0xE594D3BB6A0519D0ULL, 0x2441DBA16BB6DF1AULL, 0xF217682143F9C872ULL, 
            0x08CEB6DE35330CF8ULL, 0x3570F95C5B339739ULL, 0x6F560C63D2ACB0DDULL, 0x50D6AC3B0F48F128ULL, 
            0x3F2279D5F138E82DULL, 0xE64F02FE00BF8D89ULL, 0x1B0EAAAF7B80A9F6ULL, 0xDC436739DB7B1CEAULL, 
            0xF6CAB1A8FF7B4B98ULL, 0x293AC46FBF3DC615ULL, 0xBE7CEB7D4B5BB164ULL, 0x423DDEFA94679E36ULL, 
            0x5FD1E830F8681EBAULL, 0x123EF4FF6A63A9AEULL, 0x40F96799B099F0BEULL, 0x9CB1CDE4F1086576ULL, 
            0x5973306F4B4FBB78ULL, 0x57D81B5CE7B461A4ULL, 0x83DCED4178A88877ULL, 0xC5BB92D0B9E2EA14ULL, 
            0x105D041E29DFD575ULL, 0xBED6B03C0FCB2CFCULL, 0x2C4667B21A7BC455ULL, 0x760F395878D53A15ULL, 
            0x711FCD9AC46AB2EFULL, 0x368973EBA4F673A5ULL, 0x66DE5681BC6CFE19ULL, 0xA1F85B0E396EB957ULL
        },
        {
            0x1C47F3CC4B29A30BULL, 0x90B6EC15B59CFB24ULL, 0x30AED171F0713AD2ULL, 0x0B189605CE1D2EA6ULL, 
            0xE40257FF34677693ULL, 0xF3A16141105D8F60ULL, 0x3EC872A6672C36D9ULL, 0xF8441943797CBC61ULL, 
            0x8033B2A63EE4E9A0ULL, 0x77AD157B8DB4EA8CULL, 0x944ACD01F8D079F5ULL, 0xD3589FA0EF4D972AULL, 
            0xAA07DD8498E04616ULL, 0x39A3739B0151F148ULL, 0x7A4B461BDF2B9A14ULL, 0xCCB42B4BB4AB1AB6ULL, 
            0xDAF91758CA260A75ULL, 0x5443F4137C13CF12ULL, 0x318CC252AF85D7B0ULL, 0x0FB313FA27F12AE8ULL, 
            0xD03E7BEEA83BE4ABULL, 0xC66391A75117EB6BULL, 0xDA878F04CF15398BULL, 0x06D23F6CB760BA56ULL, 
            0x1F035F50A15B3E35ULL, 0x334C56F863590BC6ULL, 0x3402576C2F2AAE47ULL, 0x1F7E9ECDDE7A6C99ULL, 
            0x58E58BC28CFAD3DBULL, 0x9C740A29EB233778ULL, 0x34F078DF96DF9C5FULL, 0x8AF61BB333C1F1E1ULL
        },
        {
            0x93E4A5B75021ACE6ULL, 0x10596323929B7B49ULL, 0x4E263785002D6DC1ULL, 0x6313867BCDAAB654ULL, 
            0x6E636DB11B1E3B70ULL, 0x73CCDF5B7800CF91ULL, 0x5E495DDF10B03C52ULL, 0xCDB5026202E5DD4AULL, 
            0x0CEBD30E241493D2ULL, 0xB3F53A30C0E8D07EULL, 0xF24F6BCD393A5EB0ULL, 0xAEB32078B4DD8256ULL, 
            0xC42381E13E050658ULL, 0x5556E9BBAFA03CB8ULL, 0x628AC338833B0F48ULL, 0xFDB40C2DD244A6D2ULL, 
            0x452B32FC4A3C8814ULL, 0x79801433320236F1ULL, 0xE0A98D08A9CF73A4ULL, 0xCBF8A234AE73ECD5ULL, 
            0xA6A5C191407864BCULL, 0x3C824E304267A06AULL, 0x7455570626465938ULL, 0xFD646C7F765C0B44ULL, 
            0xDFE0D4D2C7AB1AFBULL, 0xC0E1A74F02661D52ULL, 0x9C992E4EC60137B6ULL, 0xC1D25ACCD01F811EULL, 
            0x512C054EDB7060FFULL, 0x7FCA08C45F1AB8A5ULL, 0x28E82C9DEBDD5FECULL, 0xC8685C5966D7AF83ULL
        },
        {
            0xC154424A80B5956CULL, 0xA643D0FFCE6237B9ULL, 0x71A22905A49B3842ULL, 0x548F4E5CB1B3A2D4ULL, 
            0x1EEE6A236D4B7FF4ULL, 0xA92F0FE0B649D2BBULL, 0x6B81C33F4DCEE729ULL, 0x5B2D5202C560DDE3ULL, 
            0x508609A4EDD94726ULL, 0xA101DA01219224C5ULL, 0x124C7F0469159922ULL, 0xC9DF8F30FBBF5A87ULL, 
            0xA965BA882E785641ULL, 0xA73BFE3D2FA316F1ULL, 0x7E8AC752FB7ED74EULL, 0x42A4FFCA0FE41C8DULL, 
            0x4345D1F7BA1BACA1ULL, 0x7EC8748430C7820CULL, 0x147F1B26E5229953ULL, 0xD9DB86D4884DEBA7ULL, 
            0x6B36F47028C171A2ULL, 0xB576FC9C599CC2F8ULL, 0x341C857041DA4A20ULL, 0x1F284AA1EF8C49D8ULL, 
            0x4CEE981E690DD048ULL, 0x95658D76D249AC61ULL, 0x29701A096A609FC3ULL, 0xE22D4D7AD113F011ULL, 
            0x01918FF8320EE946ULL, 0xF4A16BABFA75AA6FULL, 0x72EAC8D0ECE3F309ULL, 0x8EDFD7B404DE6C63ULL
        },
        {
            0xF02BB674CF6EDC23ULL, 0x691B493230DFFDB2ULL, 0x65155A87765C43B3ULL, 0x9ECAD3D3796561FFULL, 
            0x4739C896EC22065EULL, 0x199ED7D102D78B47ULL, 0x83A2035BD3B2D1D6ULL, 0x15D7509B4C83F2F4ULL, 
            0xE6F0D180555F09D0ULL, 0xD04FCDE2E7FEE958ULL, 0xC37A0A612F5061F6ULL, 0x348F4D6E79B0A6B3ULL, 
            0xC6AC8C5642F90616ULL, 0x4D275C5582A9D264ULL, 0x154886BD8F97EAA2ULL, 0x057331A80FB8B0B4ULL, 
            0xD862160E32F704C1ULL, 0x8BC0CBBA54E72275ULL, 0xA9B0ACB89A2061E4ULL, 0xADF42433171E1C7EULL, 
            0xB08BD34B5BE409A9ULL, 0xE6DC3EC466A538E4ULL, 0x70873E63B9D85AB8ULL, 0x20C1B181E1CFA427ULL, 
            0xEC65B1607E872DFBULL, 0x882069D3CEFD3E32ULL, 0x174FABA5E1E1429FULL, 0x7D890ECD2BCC06AEULL, 
            0x10D672878FB7984CULL, 0xF403894FC561607AULL, 0x7762B49159D42D16ULL, 0xD3C88AF55B5AFF89ULL
        },
        {
            0x1B66E8400E100E67ULL, 0x0912B271DF91DD4CULL, 0xEA21B8FA52543422ULL, 0x2AB9CE2C5572EFE8ULL, 
            0xDEADBC5A050E5520ULL, 0x1C0CE1BE4DC836A4ULL, 0x8A038702C879D896ULL, 0x9CF62CAA6D3E3400ULL, 
            0x3FC4FFF166A069F3ULL, 0xC9C216411E836FEFULL, 0x4BBBF676F6CF4CD3ULL, 0x73F927531C1CB468ULL, 
            0x49DC61D696824C0BULL, 0x39E7D8EE8444B99FULL, 0x33867DC8226031E6ULL, 0xBD7A908D7C436C03ULL, 
            0x246945D53DBC35BCULL, 0x8F4DEF74A7481D72ULL, 0xD01E869B6BEB7FF0ULL, 0x2566121B8CDC689DULL, 
            0xED3E8756DD66108AULL, 0x01863308A3171C1EULL, 0x35C2E8D81F49EAE3ULL, 0xC72ACCC8801998ACULL, 
            0x8E4DAB1C687AEA73ULL, 0x93D589462C09E920ULL, 0x781C8C414A3EA32CULL, 0x23F93D178DAA6B36ULL, 
            0xDE363749C95FD479ULL, 0xFE91A368144003F8ULL, 0xF774601DCFD5C5CEULL, 0xF761CE5149F58A88ULL
        }
    },
    {
        {
            0x8A7D462B9EECFF93ULL, 0x087BE74F174A9032ULL, 0x202B76045F00530CULL, 0xEA149A64D11FDBE1ULL, 
            0x08EC9198F5089540ULL, 0x062C4F6497DF61ABULL, 0x01E2D0A4A9D63B80ULL, 0x3BDEBCB6A4A106B2ULL, 
            0x2AB6365907D2CEB6ULL, 0x89D456E251D623E2ULL, 0x2A961D5480311B45ULL, 0xEAF07E4BE0170D68ULL, 
            0x3AF07F0A5442BC2DULL, 0xA4D7BB230B50C357ULL, 0x08DB6D5E666253DFULL, 0xF69AA02CD13CA7B4ULL, 
            0x2320B0834BA14651ULL, 0x404084A239DF4036ULL, 0x9A5A8F09EA4CA502ULL, 0xFC275C04F9A81297ULL, 
            0xF7ABE4D71D07DCF5ULL, 0x6EE5455D07A3BE0DULL, 0x40766C8323E93EEBULL, 0x1336C9ED403C9DBEULL, 
            0x9912C6F8A103DD6AULL, 0x3D2DA59E71FA8BD9ULL, 0xDAC00415704C3F90ULL, 0x6D4EB6A23976DCA6ULL, 
            0x4165EB3C1D543050ULL, 0x381F320627584551ULL, 0x51E39B4E2D606CF1ULL, 0x97AE2C2083EF7D0BULL
        },
        {
            0x2D3ADC64D69DB839ULL, 0x3A94D32055DC881AULL, 0x89D479D8347C8B5BULL, 0x80D00FFDCDB8A563ULL, 
            0xF9F6DEBF3D7F9B53ULL, 0xF114C085B7639C2EULL, 0xEF719195C43B6BD1ULL, 0xF8844A6C46058F23ULL, 
            0x9347D25A55656BA2ULL, 0x6C8D4DC2F4268883ULL, 0x10BB25EC39ED154CULL, 0x4D96C5DD4E90FE4DULL, 
            0xC518E693F7B8A032ULL, 0xDB5E42AEF1BB7E90ULL, 0xCB995511A9772FA2ULL, 0x086CD7B215EFC095ULL, 
            0x836A6DE8E939A56BULL, 0xF936DBC468BF5324ULL, 0xC4CE043B347F9DD1ULL, 0xEC642AB7D0AF2E78ULL, 
            0x3F8A9307D8774BF3ULL, 0xA8C1A3C1BCBE3C23ULL, 0xD6167E6B9534C01FULL, 0xF3C50769E0DDA99BULL, 
            0xA411E446E4A07551ULL, 0xFFCDB7077F839436ULL, 0x9093DDFE9BBE57ECULL, 0xC7E1046F114FD257ULL, 
            0x5D9CEEACE1B44DA9ULL, 0xBFD96C81564C0972ULL, 0xF8912BC46D07BEFEULL, 0xCFEFDF13D2D3322BULL
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
            0x84C59E5339415246ULL, 0x3BDD9DE101194430ULL, 0x0B1A9598AB649041ULL, 0x389BB183A387D037ULL, 
            0xB393EF324A035B6AULL, 0xACE97C62A3B22F29ULL, 0x2D5088CED9E026DCULL, 0xC2EA2B4B191E3FBBULL, 
            0xB7633FC7B4591A8BULL, 0x3E119827291F522BULL, 0x9336BB062E877A07ULL, 0x8E6D8ECC4265651FULL, 
            0xFC1667C8B9379E1DULL, 0xC6DF6B0FFA4633ACULL, 0x19A8135EA41CAAABULL, 0x538CA3DB0B843BCBULL, 
            0x6A8BDACA0EC02A49ULL, 0xE92DAC0F5B03B93EULL, 0xC26BE862C1E905F5ULL, 0x3E1FB1DA8552141BULL, 
            0x0AC6E9AB556F9403ULL, 0x3A098F2BF758D77BULL, 0x711C78C1B64CC954ULL, 0x41CED41DAB455208ULL, 
            0xAEB4CDC6A88D9D0EULL, 0x3B48C772CEA73B6AULL, 0x6D525DDB84D3A788ULL, 0x57F3FC4FDBFF15E9ULL, 
            0x329EAA3DC5820DA5ULL, 0x0C1C7B72F7A204EBULL, 0xCD7061D5A4457A95ULL, 0x477BF2E2A0658A8BULL
        },
        {
            0x2B8CCD5DC85EB76DULL, 0x1D4CCF182CA95DE6ULL, 0x4E64B89AF6710E60ULL, 0x45B7214A6462E8E4ULL, 
            0xC3A9522A95FF8C2BULL, 0xD0165F4DB6BEB422ULL, 0xE8F31062EDBE7985ULL, 0x8A79C66A544421F5ULL, 
            0x1D6E7D39733B0B59ULL, 0x51458E5A6E2A5AA6ULL, 0xB66EE243DF1EB987ULL, 0xEE473362B3881A53ULL, 
            0x9C77BDD74CDA5310ULL, 0xC44FABF8C163AADAULL, 0xA634471E351C123CULL, 0xC3621F90F5A2ADC7ULL, 
            0x989E990FA463A683ULL, 0x686DB380DD228C28ULL, 0x5D7DF9A9507DDA2DULL, 0xB1068F8B77BCDF83ULL, 
            0x54FBC21C26047277ULL, 0x6517918BB4347712ULL, 0xC99AFC2B93E35597ULL, 0xDF24759EDB554BE5ULL, 
            0x3AD5371F762555FDULL, 0xE43F4003E4BF016EULL, 0x736F829A5ECDD85AULL, 0xB18FD18E816B5F06ULL, 
            0xB3554C005934BE4CULL, 0xE55DD6E1BFC758ADULL, 0x9A17D8D17E9B0802ULL, 0xAC304583CE11AEE5ULL
        },
        {
            0x09D8A3995CAD3EE4ULL, 0x9E7D599819696C63ULL, 0x2907E8B37C1AEDB7ULL, 0x7242972E93B9D18CULL, 
            0x3652593F3D1B0A41ULL, 0x6F3B7A822D484300ULL, 0x16189D8D01847C09ULL, 0xB257880DF736AC08ULL, 
            0xE5B4FA0700B176EFULL, 0x8E39A632BF533537ULL, 0x0A70F58CB9EA7BC5ULL, 0x8D1DE52BA0A8E9D3ULL, 
            0xF2C75E2D678B54B4ULL, 0xC8FE300FE8DF22B1ULL, 0x497B77F5DCA15EEEULL, 0x53D124B3EE742550ULL, 
            0xF15F0088A99ABE79ULL, 0xA813F62468512EAFULL, 0x3351B3C76065C9F6ULL, 0xC58953959CB9EF1FULL, 
            0x0465D95672BEB51EULL, 0x4ECD3BD7E0320980ULL, 0x330B5EBB659F32B8ULL, 0x0A392FA7F6B8760CULL, 
            0x66A3277687E68027ULL, 0x6D92858150571ABAULL, 0x0DFC7D67B538FEC7ULL, 0x72A80F7AC58E5D68ULL, 
            0x2359C01FD39EFB86ULL, 0x1C6A6C5B39F4ABFCULL, 0xA43DCEC2A390572FULL, 0x2CC0FD71C46CB574ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseCConstants = {
    0xCD00624519A5245FULL,
    0x52AA46149ACF5326ULL,
    0x974111C9FFB5FC72ULL,
    0xCD00624519A5245FULL,
    0x52AA46149ACF5326ULL,
    0x974111C9FFB5FC72ULL,
    0x3AF2A28AD26F9323ULL,
    0xC372BC3EA51A48FBULL,
    0x5E,
    0x3A,
    0xF9,
    0x79,
    0xE1,
    0xC4,
    0xA7,
    0x3F
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseDSalts = {
    {
        {
            0x0CC9B2A5F6968E82ULL, 0x87B268F75756BDB4ULL, 0x578F9013590D6A41ULL, 0x95FD6E8F4F3E0D03ULL, 
            0x8BB8FC538BAC17C8ULL, 0x20543E2CEB834C13ULL, 0xEB167DBDD0960849ULL, 0xA290B42AFD1D9357ULL, 
            0x7DDD03B489DF70C1ULL, 0x7B811CD8CC0B29F2ULL, 0x53AA40BCC93DAA07ULL, 0x5B990A9AF3956B31ULL, 
            0x64B750D65BFF8D14ULL, 0xC24840D4ABB958AFULL, 0x3A06A028F28A2B96ULL, 0x3DCF2C8ADED95955ULL, 
            0x4720A4A43D33B12DULL, 0xA89D05874139EA99ULL, 0x42AC570ECF3EF059ULL, 0xA2B77BB698635B1EULL, 
            0xB4821266CC61B8CDULL, 0x9BFB2364A0F3058AULL, 0x358C58F69385344AULL, 0xD8CB83CFD34FDE18ULL, 
            0xB0FA8905AAB837D7ULL, 0xDCD19AC3337E734AULL, 0x0B7CBDE49781277FULL, 0x15F34F994F60ABACULL, 
            0xE5177891A0ED6DA8ULL, 0x347930A6A41A1134ULL, 0x052C67BC4278783BULL, 0xCF1590B476925987ULL
        },
        {
            0xF72D1189095F6E05ULL, 0xA1D2A154C21C667EULL, 0x896FD4AA0C9DCE0CULL, 0x8332135D09F4739AULL, 
            0xE48135F600E6612EULL, 0x90C05A29E8292FC8ULL, 0x5DA4D3F233E3E78FULL, 0x40E137CCC3C0E163ULL, 
            0xC17771A895C24605ULL, 0xB65B5560301BCF46ULL, 0xBDBAE2A450B2E791ULL, 0xD571C784BF0B4F45ULL, 
            0xCB65A9636C94491EULL, 0xC1D012D03FECFF20ULL, 0xCE651D7FF3230553ULL, 0x6CC6D9DF6708B598ULL, 
            0x7D8C5B4812265551ULL, 0x7E688C5E2CDA5228ULL, 0xE39BD61EDBB59B2BULL, 0x7B60944F212209D2ULL, 
            0xD177EDD2EA310369ULL, 0x1A2FE8AC028E5257ULL, 0xDFB274F2E617AB8CULL, 0x802447EEDBB6F238ULL, 
            0xFDB29A24B7A7A23FULL, 0x709BA87DDBE6EF48ULL, 0x17AEDCF7811A3030ULL, 0xCE53317F72FE8311ULL, 
            0x00251F2A32FFA065ULL, 0x26F29B79D7C5FFD2ULL, 0x30AEB3E141E9D4E2ULL, 0xE401F06F07FAC55FULL
        },
        {
            0xB7D6CA246D0CD679ULL, 0x9628464065145B1FULL, 0x828BEB35B6FF1AF6ULL, 0x5D35EE0E8772F99DULL, 
            0x4F8E6B48F1A5A06DULL, 0x73F422B75682B0CAULL, 0xBD0968C5559AB449ULL, 0xBA6CFAFDE7469BE7ULL, 
            0xE7AD21BEBFCCD68EULL, 0x65DF0B6D1E550953ULL, 0x79E0CDCC80C2FF2DULL, 0xAC27B617153C9F61ULL, 
            0xE4576973416FA426ULL, 0x41BCA493DEFB96EDULL, 0x7F2A74E0818AE43EULL, 0xCBCC72AC58EB9501ULL, 
            0x5D61A912C4B16753ULL, 0xCC810F8F3114DC7BULL, 0xF384DD34EC73F59FULL, 0x346253FD93C47CBBULL, 
            0x824503FF6BAFF22AULL, 0xE8CE5C6EC0E3654AULL, 0x4FB6CFDD2D8FA4B0ULL, 0x4439B93C44F134DCULL, 
            0x9E3B48A552A0553CULL, 0x58F8FFD48422DDDEULL, 0x967DE09363FDBB47ULL, 0x7E6371A8F48BE4A2ULL, 
            0x3BA80108DF441F46ULL, 0x521DC228EFEA9F79ULL, 0x421D1D738017A3B7ULL, 0xE61D1432C1844D16ULL
        },
        {
            0x45FA9E9792871A4FULL, 0x4E27FD98D7702874ULL, 0xE1A685D580B8F518ULL, 0x290F52B415248F25ULL, 
            0xFBD8668942DB309FULL, 0x2FC621BCE7091059ULL, 0xED6A06002FDB5657ULL, 0xDB22EB1B05F8677DULL, 
            0x583441A928D5FF70ULL, 0xE78358EC83387840ULL, 0x8158567E765547C9ULL, 0x4B46E5C279F80BB3ULL, 
            0x959C4978F3E4436BULL, 0x060343EA09323E7DULL, 0xBA704AB38F1F8A44ULL, 0x19E6923CD5C377EAULL, 
            0x987D41EE9A9049ACULL, 0x2B13B8A3B890515CULL, 0x22E80A7D0C7BB6DBULL, 0x2BFEB53461957BBFULL, 
            0x9C911C8CDD0BA9DDULL, 0xB8175C6CF6266D2CULL, 0x99B77EACCABFCEA8ULL, 0xF03AF5601899CE01ULL, 
            0x69F1ABF36C53462EULL, 0xEC1CE5928101AFEBULL, 0xEE0D7F845518F12EULL, 0x52CE4CBB68507C7CULL, 
            0xF4D772A20001EFABULL, 0xE0FDA7ED58AF95F0ULL, 0xCD7EE06C032F5E25ULL, 0x82366DDF8C02F339ULL
        },
        {
            0x9F6B7E0B4A2B7CE5ULL, 0x10A0AB513EFAD942ULL, 0x0A0E77B04CDF97E4ULL, 0xF1E160DD6D5A9A1BULL, 
            0x265195965F74D3D4ULL, 0x06EE516461A083E5ULL, 0xDB4CDC4D10C3C17CULL, 0x20161CF6952D4799ULL, 
            0x4B98300534FABB6FULL, 0x9554EC4FACE45A40ULL, 0x0C186FECF611901DULL, 0xF81A46946FE1D5B1ULL, 
            0x921757A1FB5C3769ULL, 0xCFE59576D45460E4ULL, 0xC57B219686DB1147ULL, 0x66370105BBF43396ULL, 
            0x074D080899E6A4E3ULL, 0x3E5945406253857AULL, 0x777C067AAB10878FULL, 0x0A5A6FB3606843F8ULL, 
            0xC5BCF2986E94E426ULL, 0xFB9E26D46B63AAD0ULL, 0x55EFC992ECC64398ULL, 0x0021D215E3D37CA5ULL, 
            0x310E57E924AF8D7EULL, 0x24A334640B1C1927ULL, 0x482B4EEE9240C998ULL, 0x9081D2A641FE1D7DULL, 
            0x037FBF36A17CF982ULL, 0xB9F221D73E10E5BFULL, 0xB2CE0E56EF4EAEEFULL, 0xD29F5FC4A885A183ULL
        },
        {
            0xD6E8134A7480B71EULL, 0xEA89408947CFA889ULL, 0xC37442B6AFB7A108ULL, 0xA27F0D8852690943ULL, 
            0xD56087EB8E28F2F7ULL, 0xE606EAB059DBCD06ULL, 0x5D02BB5274890098ULL, 0xCFD475FA96A81B98ULL, 
            0x64F122CC526C0994ULL, 0x848AD62D2AEF3AF1ULL, 0xBC6395E112F7D73FULL, 0x0EC7F7E4BEC359E3ULL, 
            0x34347E1B5D5017C5ULL, 0xD4E013E14573561EULL, 0x1759388AFA1B2289ULL, 0xB5A6223F15A5B68AULL, 
            0x22F22AAE62D3E886ULL, 0x7DBBCDF617A0C277ULL, 0x8F1B4E623D5377E9ULL, 0xC644E50F4A3BB64DULL, 
            0x0C634487D3684843ULL, 0x9C8C9ED1923E0802ULL, 0xE8CF5037C8956E11ULL, 0xF9327AECB9B49F77ULL, 
            0x2D5891AEB34CCA5CULL, 0x68A85CEAB0CA005CULL, 0xE78B31CC652E4370ULL, 0x46CE1D627A8148B1ULL, 
            0x90E0707D82823FBDULL, 0x4D1870B0616B41EAULL, 0x4A7E634026545084ULL, 0x35F391797989FF36ULL
        }
    },
    {
        {
            0x3F27B19469830A6AULL, 0xED1797ACD9DE6B10ULL, 0x245E835D34E13CA3ULL, 0xAB430B1B3B488C8CULL, 
            0xAA7BFFDCC79E4DAEULL, 0xF864FDB14C2E9E55ULL, 0x58C96D5D4CDE2878ULL, 0x13D6FF2E771FFF76ULL, 
            0x6C9714D89E58C671ULL, 0xA137613291F78466ULL, 0x653B5406C1699184ULL, 0x979095255269B240ULL, 
            0xB9B98FBDF400D4ADULL, 0x86F03307C9100DC5ULL, 0x0014180B17B9342AULL, 0xE12D4632FB8D4090ULL, 
            0x7EF48ABE10CB36FAULL, 0x9AED1B6B017EADB8ULL, 0xEF203DE20EBEE3C1ULL, 0x08F53EE393A2DD50ULL, 
            0x3E8476CEAA8CC291ULL, 0xD54F2E8516A62DC6ULL, 0xD69F488CF031FDAFULL, 0xE52A7F28721C7CC5ULL, 
            0xD99967B9CE85746CULL, 0x610AD14BBC78C63AULL, 0x60E2479857E2F751ULL, 0x143E20C10498E386ULL, 
            0xEC54021AF9C0D35FULL, 0xBFB6AA09733A570DULL, 0xDBB68CA53922CD60ULL, 0x3950F1D5F5D1DE7FULL
        },
        {
            0x80BF87B3924B96B8ULL, 0xC2C13B3D6A8F5CA7ULL, 0xD00FC9BE76FF536BULL, 0xA6CA7D20CCB93BCFULL, 
            0xCA3BEA51DB609679ULL, 0x6B064B19AA79F4B7ULL, 0x6B4017CD89F9CDD9ULL, 0x50D96B0A7D4153AAULL, 
            0x5ABAD8BF9F71EBC1ULL, 0x6AE96B8CEBE24D0EULL, 0x31C1EC43AEFB98C8ULL, 0x9894ECB80A5E43B0ULL, 
            0x52A85A9FD2756345ULL, 0x72546327ED49CAC2ULL, 0x805BC7BB661CF678ULL, 0x03C468F60A7A384BULL, 
            0x2DDD268EDFC6652FULL, 0xA78C00AA5702D824ULL, 0xB82DE4C1C02B1E82ULL, 0x0AA797B44AA1C69BULL, 
            0x85925F197EC21F60ULL, 0x655B4CEA5D5D5DCFULL, 0x1FD70087570B57A3ULL, 0xDFF4DE0433534E00ULL, 
            0x0973DE34F31F6A94ULL, 0x7C4DB0102B6A16F0ULL, 0xD281DA2AEFCA1CE7ULL, 0x777A9F156FAF09E9ULL, 
            0x13DB2B3AF36FE2BDULL, 0xD5D14A735FC4EB75ULL, 0x1FBB00B2D45F620BULL, 0x90BBB2D0A7F17CB1ULL
        },
        {
            0x6B583AA53F0B0FD3ULL, 0x4F4337AB908EFE4AULL, 0x0970FFE0529FC84AULL, 0xA137C14D52CDF842ULL, 
            0xC1D9A6107E170739ULL, 0x3B81E2F83CA10614ULL, 0xF3A6CB85F0D8F588ULL, 0x1BFDCC104D2AE763ULL, 
            0x77EE7EF84AF95EC8ULL, 0x8CE890CA3058506EULL, 0xD8A9C13D60D7DB03ULL, 0x452A9899FF7D234EULL, 
            0x1B5DB3B14757B679ULL, 0xF1ECFD19CC7C3531ULL, 0x1A2BDFC32076AB98ULL, 0x3745E98DC7118761ULL, 
            0xC9DC455222716AF5ULL, 0x25C63EA18DEAC8C3ULL, 0x0534DF7E09EC1448ULL, 0xDFE2ED1B39E5DADEULL, 
            0x0876A208CA3C536DULL, 0x52B76788ADC95284ULL, 0x816AD9B090337B46ULL, 0xDE72F0704E774FFEULL, 
            0x14FD113630CCB00AULL, 0x27797E4BE373045CULL, 0xDF6D42B991F80FB1ULL, 0xC28532EDC69355B1ULL, 
            0x7D7C875660DB4130ULL, 0x63F43E22C96DC412ULL, 0x553E44692013DC24ULL, 0x950E424256A70C0DULL
        },
        {
            0xC65630A671CC34F8ULL, 0xD7A56C3700456FEFULL, 0x0EA711A636494AC9ULL, 0x1542A3CA777848F7ULL, 
            0x827FC5E886FA6258ULL, 0xED4ACCBB363FC390ULL, 0xFE3D258BF3159EC5ULL, 0x6B007FB72750DE81ULL, 
            0x1DF88C44C3808B8CULL, 0x0A37C1264D4D0031ULL, 0xA51BBA761ADE0EF4ULL, 0x0907E83F6068DB16ULL, 
            0x1A8F1240CED36A79ULL, 0x78159C31B0330D70ULL, 0x63EDC27564519D4BULL, 0xF14C7C005B283E97ULL, 
            0x2D20669D6FFBF97EULL, 0xC5717197AE39AD93ULL, 0x3D892812714FDD16ULL, 0x99257331EFB287DDULL, 
            0xE080695F882BE3B9ULL, 0x7DA05280F765C477ULL, 0xD68BFF2644BF6D32ULL, 0x3452A6B31741BF05ULL, 
            0x9BF2C8CDE475C84DULL, 0xB845830B7D1FDBDCULL, 0x88FAFF5AFEA5F2FCULL, 0x55DB1E008ECFA7BEULL, 
            0x37C08A3AD3A654A9ULL, 0x78D7F0D90B03A523ULL, 0x7181551FD036EBE4ULL, 0x8471678B29908BA6ULL
        },
        {
            0xFCC77D0AD94B8651ULL, 0x9AF3DF11A494C83EULL, 0xA572519C675DC103ULL, 0x37C2E9AB192EA79AULL, 
            0xA4DB231E9DBFECE4ULL, 0x787E78E50FE76459ULL, 0xB85B2AC08DF9B614ULL, 0xE1FCA3EF78F8946AULL, 
            0x2146F3A204A89F97ULL, 0x064607C00D0B00F5ULL, 0x3182B2F77131A6B8ULL, 0xCA16DF9F649E07D0ULL, 
            0x2CC458B43D3216C0ULL, 0x090EC7329397DB67ULL, 0xDAF35C8DBA4DE1D9ULL, 0x33B22C9AE8BBFB51ULL, 
            0x44EBD25F30A59123ULL, 0x984FB7E5F4732E9CULL, 0x71FD7B2EE5E4F5B3ULL, 0x976547AC51AC3995ULL, 
            0x09602AA45F88CDE1ULL, 0xD6BBD710B04533B2ULL, 0x5FC0B1AE7D29E782ULL, 0xAD58653E74A8CA5CULL, 
            0x5A280DF8FC1CF30BULL, 0x12B096BCB7B9DD76ULL, 0x8C0392CE1C0D01EEULL, 0xB92F141C7E886C63ULL, 
            0x1096BFC7C8161A45ULL, 0x2153F854654B5FE6ULL, 0xC87F270D835AD284ULL, 0x61729B1762D74825ULL
        },
        {
            0x13019B4D7B2CB41BULL, 0x0FA4921560E8649CULL, 0x55A4E6DCD79EA594ULL, 0xB20995B71BB1152FULL, 
            0x0AEB0CCD9278B56EULL, 0xB0372DE06D74AF5AULL, 0x831A097589BC0A3BULL, 0x3797475DA5FBDBFEULL, 
            0x3BD0CC734026A417ULL, 0x71CA329DDF601F84ULL, 0x45C457F8B9F53F8BULL, 0x372AC34F7177073FULL, 
            0x3AD7E9AAF96599A2ULL, 0x7DFD2DF45D81B941ULL, 0xC8CDDAAE677F11E2ULL, 0x17C8A22A3CBB7470ULL, 
            0x33C52065B80CE118ULL, 0xE05EE08D50FCC978ULL, 0x2D7D3FDBB120A388ULL, 0x618070A101C4E4EFULL, 
            0x6D805E2D9191F87EULL, 0x29A8CC6101F34CEAULL, 0x791BE3CE066FD200ULL, 0xF309B11F54A6B90DULL, 
            0x1B89664F02CA8F5CULL, 0x457031E73719876BULL, 0x5B8E2EC6CBCDB89BULL, 0x750708B88668A329ULL, 
            0x6F482B44FDC45D83ULL, 0x36C6C05F3C17A94CULL, 0x790FB5897F3C5B37ULL, 0xACCF2A3361E91348ULL
        }
    },
    {
        {
            0xC35D9F6AAF562A51ULL, 0xC8C3F1D4B0F057FCULL, 0x31EC24EDD1098E2BULL, 0xF8AD584BCDD3679BULL, 
            0xD0E10DDB2FB90CEAULL, 0xAC2EA227229878AEULL, 0xF42140F97AADF2FDULL, 0xCF5396D6B26AE8C3ULL, 
            0xCEB36F948A74F636ULL, 0x2C97D9AFEFF9EAC6ULL, 0xE17E0B830E68C9E2ULL, 0x97E4838037526035ULL, 
            0xF79F5C46E98A3993ULL, 0xB30C5060DB166E24ULL, 0x31BCFB53040BB2E4ULL, 0xFC51083E350B78B3ULL, 
            0x734662C4C0C15FFAULL, 0x05083A7AF7066F28ULL, 0xCA877C8D2604A504ULL, 0xB0EBA69D8031FB34ULL, 
            0x95C99634824B7A5BULL, 0xA65038A483F267ACULL, 0x095591159B80A2A0ULL, 0x0233522CFD7CBC8FULL, 
            0x30BBDFD43C8DB60BULL, 0x5AD2439ECB28B2BFULL, 0x5B5F3D65D72EB9B8ULL, 0x2E638B125F25F8D2ULL, 
            0xFA27C05582F436AEULL, 0x213B54242B2B2624ULL, 0xF9C7F081A16B7A64ULL, 0x3CEE64977F0AE8F2ULL
        },
        {
            0x7FFB19CF233F8BF5ULL, 0x65A6C032D02EBCF6ULL, 0x8E7FFA0676A4622AULL, 0x590BA8372A55003FULL, 
            0x8AD19A301369655CULL, 0xFCA5C101B1774AC4ULL, 0x6A93DD61AFFA0623ULL, 0xF78A3F36E17B13BBULL, 
            0x447E53B3204338ECULL, 0x147380575B1E0063ULL, 0x91F693A4DF502869ULL, 0x249A057115D0C33DULL, 
            0xDCC1BB309BED18C7ULL, 0x1AAD17BCA24F5419ULL, 0x930059AEBBC675FDULL, 0x5289C46ACA7E873EULL, 
            0x922BEEDEFDDE248BULL, 0x31F3D03715BE350AULL, 0x089CF459A2B819A5ULL, 0xA1F28D95903F49E9ULL, 
            0x6569F7A78AB7CEB2ULL, 0x0F740CCDEACCC7C0ULL, 0x0E2D0C963C398A73ULL, 0xDC559B72F197D349ULL, 
            0xE8B5D663118D4B57ULL, 0x1F39B7C8102D5228ULL, 0x4368C18FBEDDB742ULL, 0x49A71D90DE41AE2CULL, 
            0x04BDD259095EBF29ULL, 0x30213243BD830C68ULL, 0x4D9C78101DD589E5ULL, 0x047867E0A6D6E914ULL
        },
        {
            0xD6A22E77623FA591ULL, 0xD05F7B338C9D355FULL, 0x8B135B25FAB2D202ULL, 0x3EA65B7C066F91BEULL, 
            0x676CB48793B176CBULL, 0x35D62DE093D9D7FBULL, 0xA278F25EC40AF370ULL, 0x2FD10128CEC60784ULL, 
            0x80F60C5F1FC0963DULL, 0xFF9ABE7001745CA0ULL, 0x6048423718EB59D4ULL, 0xAE4111FC83F8819FULL, 
            0xF0893DB009AAB04AULL, 0xC5215115FA005ADDULL, 0xCC8B41277E885489ULL, 0xD3BA5F07EE488319ULL, 
            0x817691C530E3F9BCULL, 0x2843764289127859ULL, 0x9A2F5234BB90C731ULL, 0x5812F1F1190D13B0ULL, 
            0x2CD7EA615B0CF458ULL, 0x922B1D44C15FDFF5ULL, 0xB70DC1FF74DF3826ULL, 0x15D799719BD7AAE2ULL, 
            0x10096A484ECE5F32ULL, 0x549971B072417B98ULL, 0x4D09A907BD017BBCULL, 0x2D89D9C904746D32ULL, 
            0x380EE33234446342ULL, 0x24CCB242028610F0ULL, 0x07396E382B563129ULL, 0xC22DDE902DAAA833ULL
        },
        {
            0x005A6801D4D72D8AULL, 0x9911505707C9333CULL, 0x21BE140E4A611D77ULL, 0xFC75496422F3E61DULL, 
            0x902969A1E5DBB5A4ULL, 0x76345933E29EF28BULL, 0x6D8C7410433808A3ULL, 0x3827E6FF485639A6ULL, 
            0xDAAFDC0B70ADDB63ULL, 0x9A3B6DEACC5A9355ULL, 0x46282D8FB1EF5CDCULL, 0x1D3C3FB30A37294AULL, 
            0xEFFA1451DC560954ULL, 0xDB762279BE9490D2ULL, 0x47E836EDA7B2DC13ULL, 0x52DB63E41FB820A8ULL, 
            0xAE7183A37CDD221AULL, 0x68E02E4D9C7831B0ULL, 0xF6BAA7FED837C5A1ULL, 0x2452CC1DF7F877EEULL, 
            0x2F77643B6C4E895DULL, 0xD97DE9170C521CABULL, 0x51757E9B6E13326FULL, 0x766F5AEDCE0B6622ULL, 
            0xDFDADC09306D4A28ULL, 0x320E1814F2FC76DCULL, 0x21E15BA9D932D096ULL, 0x864B8B12D2EDA9E5ULL, 
            0x1DD9782D14CED7B5ULL, 0xB0633BBFA9DCE9B3ULL, 0x1682041AABD81511ULL, 0x3149CAF5B3DB4B1AULL
        },
        {
            0xB188DEE6287C545DULL, 0xBED612C9A38A45C1ULL, 0x5EF903460573F349ULL, 0xEC1FC416BB2C47F2ULL, 
            0xDCFA9920A72491DFULL, 0xD7CC7DDC1781BDF5ULL, 0x0FBF5E389A36057DULL, 0x35324CF5618921FCULL, 
            0x8BFADAA4238EE9D5ULL, 0xEC57E83A2FA9D8E9ULL, 0xC5B12409972B9CDCULL, 0x4E2745C9C8B96779ULL, 
            0x3656146F28BA5896ULL, 0xFD9F8EE01E903F23ULL, 0x915F9F08BD84B296ULL, 0x72A2F3337811502EULL, 
            0x493F8D0CC57790D4ULL, 0x84B5ABF40FD11DA1ULL, 0x62A6717C4B8F6AF6ULL, 0x4EAF0D01631BB185ULL, 
            0xE8A5B332820745EEULL, 0x4FCD86781A7B1A11ULL, 0xCF846A168B88A0B3ULL, 0x86CE6FCFA4E5694CULL, 
            0x1E2D6F41BC01608DULL, 0xE34A25C9FF79A7F4ULL, 0x17F159EB5EBD0CFBULL, 0xAD090B541A723D57ULL, 
            0xF0F44E5C23FACCEFULL, 0x4C51FCF6FF428099ULL, 0x2F693514797A94DFULL, 0xE4F0237CFE65341CULL
        },
        {
            0xF248A6670ED1AE94ULL, 0x2B347D03B1B43AF7ULL, 0xB79FF866CCE0F108ULL, 0x4FA8EA730699EBAFULL, 
            0x11F979AEB76E8876ULL, 0x38C8213D471DB809ULL, 0x50C68E12AAAA79E8ULL, 0x90E3C596A011D900ULL, 
            0x67C9B4E288733DBDULL, 0xFFC382A9100E924DULL, 0x70E29A3ADBEFD71AULL, 0x8298922E118158E1ULL, 
            0x2863D866DB56D6CBULL, 0x91E92CABD3AA5810ULL, 0xF1D31D51FAE9E791ULL, 0x1ADEDA1FC0164442ULL, 
            0xCA32C4B7A22CDC35ULL, 0x736DC9A4BFEC9E83ULL, 0x50B31634508A50D6ULL, 0x7A3FA5895B404FA6ULL, 
            0xA01597ACD1C56D0BULL, 0x130F8EC9EC1E960DULL, 0xC630A1138025EE95ULL, 0x24A2440420680D93ULL, 
            0x7AAFA350F07BAA73ULL, 0x8985ADA37A43B0A9ULL, 0x967BEAE3E0C4B9A7ULL, 0xFB0019D6B157D5A1ULL, 
            0x648514465CA17E8FULL, 0x685FD8EF17742629ULL, 0xFDD107E475F8E600ULL, 0x72E05511B8D7E2B6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseDConstants = {
    0xE286C028963ABB3EULL,
    0xF741CAD012946F35ULL,
    0x0FCB38A24A7F7575ULL,
    0xE286C028963ABB3EULL,
    0xF741CAD012946F35ULL,
    0x0FCB38A24A7F7575ULL,
    0x7C9BFA4F2B2E3B83ULL,
    0x2568133D636192ABULL,
    0x9F,
    0xA6,
    0xDB,
    0x85,
    0x81,
    0xE6,
    0x96,
    0xFF
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseESalts = {
    {
        {
            0x60F0E9F557C72E42ULL, 0x0A8CA22384D548AEULL, 0x128421081845C56EULL, 0x35D06ADCA4E1838EULL, 
            0xA30E6CACF93B3AA6ULL, 0x62B816D273F7D3E7ULL, 0x1AA5D24FC26EA2B3ULL, 0xEB4EFA9392FA27CCULL, 
            0x78DB6B32FBA0587BULL, 0x705232597AF52BF1ULL, 0xA1274BB9918C6FDBULL, 0x811377BE19624C9DULL, 
            0x2632A6F851DE1038ULL, 0x1A19F9268FEA2332ULL, 0x6AC5ACCA2DD7EBE9ULL, 0x39E6616B8A33A716ULL, 
            0xA42A9F219AA716D9ULL, 0xBCF3E455EB993CDAULL, 0x3CC70A47EB685DBFULL, 0xA443E4CE65B348B6ULL, 
            0xA89ABFA8BF182E1FULL, 0xBF9F8F62D88D4AD8ULL, 0xACFE48B8FDEBA32BULL, 0x3A3737EDDCAB7E90ULL, 
            0x32A3344375A534A9ULL, 0x1747B7B877E85346ULL, 0x728A91711CFF04C4ULL, 0x6059B4B6061391C2ULL, 
            0x19FD2F4ED8DD2835ULL, 0x1D5C773AC382CFBBULL, 0x0F3DE96A60F632A0ULL, 0x36BEDAFD06049B30ULL
        },
        {
            0xC540955DF839690AULL, 0x5D37F860F172D9CFULL, 0x79ED42F6367BA213ULL, 0x355E88F1078F3CF3ULL, 
            0x21201A69DB3716C8ULL, 0xE873CBF8CE51DFEFULL, 0x6EB7AC161CC2CAA2ULL, 0xF2122D91FCF66FA9ULL, 
            0x8CDFB71E9F972A5BULL, 0x9CF635462E24D9BBULL, 0x1A7E6B8F33B21D9DULL, 0x4659959C5900324CULL, 
            0x9D3BAF6C63862BF7ULL, 0xB98F3B6B286DC8E6ULL, 0xEF60EFD6AA83B45CULL, 0x78CB46B2082CCA2BULL, 
            0xD4D591B592AA183CULL, 0x2DA8FB1069EB5161ULL, 0x26F9AB179B0E4F70ULL, 0xD061999FF0999BBBULL, 
            0x56CC2C53976FEEAAULL, 0x276D135272C5ED5AULL, 0x5669FDE234CC637EULL, 0xE0CAA0621CE9C4CEULL, 
            0xAB8919267F7AC6FCULL, 0x4C09B15ADF4F83E3ULL, 0x77AE7D4DFE4977E6ULL, 0xA610044DBD30340DULL, 
            0x9A0A09E0B897979BULL, 0x70D26F8C430E709EULL, 0xBA283533C48E74C5ULL, 0x03058500E4D4DB25ULL
        },
        {
            0x085A56B8B38E7AF9ULL, 0x3F1BE7343D9A4F33ULL, 0xEBFF8FB0B558CB01ULL, 0x685ED1C5562D4082ULL, 
            0x52A1DC8D2BF93337ULL, 0x630CAA14CE7068DDULL, 0x935ABA673FF09751ULL, 0x4D8D9C15159A8FEFULL, 
            0x7D72E1B15C9D01EAULL, 0xC268F82AE6979C10ULL, 0x132D9BB2CD6B571DULL, 0xC30DD40F9F8F9F9FULL, 
            0xD5D5BEF03D7124F5ULL, 0x7BE5724662218F1EULL, 0x3BE5F0BC67F97937ULL, 0x2A9CF1DEACFDE287ULL, 
            0xCA1E035B7C26CF3AULL, 0x7ED746CE8D485FDEULL, 0x98E44FC40651D81EULL, 0xEB19682BF273D382ULL, 
            0x79FA539A7681AF32ULL, 0x39F0B77DB893DEF6ULL, 0xFB86156F76110E40ULL, 0x10B50A65F0DA2078ULL, 
            0x879BD4D94CA66F0FULL, 0xB22702BC0EDC03F1ULL, 0x3304CF9866CF8D4EULL, 0x62D2C31DB0A1C403ULL, 
            0x37F73285D14BA784ULL, 0xD12AAFE13BA239DCULL, 0xE67D540EAC04A708ULL, 0x60A9147B98EA7F65ULL
        },
        {
            0x1D424990C06D3518ULL, 0x2DBB321E555C6C77ULL, 0xFBEF1353B8417458ULL, 0xEEE4B99C2745F9DCULL, 
            0x9AE23355043B080AULL, 0xD4AB2F3247F291E2ULL, 0xF4EC34F720321621ULL, 0xEDAB5EE9AA6DA63CULL, 
            0x77AF3ECADD62250CULL, 0x65BF3DE4624176F1ULL, 0x354620461663BF05ULL, 0x21A0D582C63E80F4ULL, 
            0x948EE82D9F7DE73BULL, 0x789AD9E52124107AULL, 0x8F259FAC44C62562ULL, 0x7B6F40BA4DF5838DULL, 
            0x9ED9C0221C9EA0A6ULL, 0x3C7F36F84259970CULL, 0x2D77C7CE2AD4808DULL, 0x7ACC594BED5DDF84ULL, 
            0x43A78790BA2DCF2AULL, 0x8FAA93F7DDC11C36ULL, 0xE28A197C1A612F73ULL, 0x0854B1754B5F6C21ULL, 
            0x618B429C2B3968DEULL, 0x5BB4AC58B42DBD7CULL, 0xE3581209EE96FDBDULL, 0xD5A9CC4F0756933EULL, 
            0xDB1E1B25A58003BDULL, 0x28D4ADC61CDA5C74ULL, 0xEEC6FB35D77D9036ULL, 0x9DD768BACD1B9FECULL
        },
        {
            0x444EF3F91B3D90A8ULL, 0xDC7B97508C679928ULL, 0x1192F450016E9E3AULL, 0xF0EF21DCA029F4AEULL, 
            0x3B919D102D234B7EULL, 0x114FC38036C7AB1AULL, 0x8CB263D8B998EA5AULL, 0x360C2E2701A5006FULL, 
            0xCB52BC417192B526ULL, 0x57C4D04817A3DBDCULL, 0x0C1B8956EE0B94A7ULL, 0x7CB57BFFC83BEFECULL, 
            0x3075D36A84123110ULL, 0x975DB05B2107C1FEULL, 0x407B1FE447ED1CF8ULL, 0x2DA2EF9A1B036F67ULL, 
            0x731452116351C95CULL, 0xCC9F39A6D02EFB5DULL, 0xD9783EDF6D1B0048ULL, 0x50B37B321256AFDFULL, 
            0x7B1E174BCC956096ULL, 0x6019F1811248E7D6ULL, 0x346FDA02F6C0D339ULL, 0x39A6CD5AE78E8B23ULL, 
            0x8C278656C9F192AFULL, 0x87CA4A1AB0BF0466ULL, 0x7569D222A944F760ULL, 0x3101409014E7E92AULL, 
            0xEEA9E4E8DB589585ULL, 0x721FF4CB3FF3B401ULL, 0xD85B2549BAD3E6D9ULL, 0xCD358C34AD9FE92CULL
        },
        {
            0x40D1DD4AF39E2E9BULL, 0x1DC9BACC26B88F1DULL, 0x862424DC5A1DED17ULL, 0x24545C42CEA1BB1DULL, 
            0xE49EBE5F513AD662ULL, 0xC2F354BDAEB3611CULL, 0x3C09292BBD7A0464ULL, 0x018B148E4EC9609EULL, 
            0x07F543C9389FDA7EULL, 0xE8B02891C015DC57ULL, 0x6CAC5B58F4B08A6EULL, 0xD952931C67272376ULL, 
            0xD3DA05523CEA48D0ULL, 0x3D625F69AA46FFD4ULL, 0xB8BA6D0D59BE0758ULL, 0x9CDFCD79496B50CDULL, 
            0x5EDB09EDCF1C574DULL, 0xD666C82064D6BD1FULL, 0xD5CF9578489FC8E4ULL, 0x5F8B10CF38EB74AEULL, 
            0x7BC87B1BC6B3232FULL, 0x19B1AA5E16E6994FULL, 0xF9678C2D9A86872DULL, 0x2B769874DDD094CCULL, 
            0x60B7EDF721EA33D0ULL, 0x1F2495A5C7966918ULL, 0xB43CC1D8623B69B8ULL, 0x738AD86FFF6214A4ULL, 
            0xEE654428468632DBULL, 0xE0BAAE03479CAC80ULL, 0x95267BC92F603C46ULL, 0xDB39B7DF8BAD5764ULL
        }
    },
    {
        {
            0x7EE653E9EFA5A2C8ULL, 0x2DF636ACAC7A42F0ULL, 0x46C4C5FC28BAAE65ULL, 0x934D1F13BEFB1D4BULL, 
            0xCBE4063B74698376ULL, 0x1534361EEE924F81ULL, 0xBEBFD1294156F353ULL, 0xA7F51FB5D6A1ECFDULL, 
            0xAAAC274B8015A0CBULL, 0x5BCC816DD606C377ULL, 0x94532CB247F63B11ULL, 0x8EBAFCD2BCCFF2ADULL, 
            0xBCBDDAB299CCBDE2ULL, 0x72195EDAF5063981ULL, 0xFDC8AFF829496640ULL, 0x907A6BFC660E4FA7ULL, 
            0x5AF3EA411FCF162AULL, 0x5765A7B38D46E880ULL, 0xB4D4D3512E0206A5ULL, 0xCC933F5D8B0F65D1ULL, 
            0x77BB96973AD91DB4ULL, 0x07A7A10C0D5AB35CULL, 0x2B92E8F38E2F8FA7ULL, 0x000ACC0C9F8CC139ULL, 
            0xD7A0D8151D029F13ULL, 0xA9E1C03B393DC97FULL, 0xB5097AD58D3FF29EULL, 0xE86ADCC0F266036EULL, 
            0x1E88EFCD2CDA5D6EULL, 0xFB2F648CD2B88D2AULL, 0xFB5BCE6B901B041EULL, 0xA3CABE21CCF2B4F1ULL
        },
        {
            0xE3C0AC4AB18418D8ULL, 0xD26B896996B3BFEAULL, 0x687D089140DAE922ULL, 0x0EB4AFE736A8CE7AULL, 
            0xA688A7CA95802D83ULL, 0x6FCC928E5DFBA833ULL, 0x5D0AF3BDC1AB527FULL, 0xE36184F77C451233ULL, 
            0x3951FB8B8A99C349ULL, 0xC0C640C7404BEAE9ULL, 0xFE96BB2EDAB97551ULL, 0x19A903AEFD6576EEULL, 
            0x660241753BE03A63ULL, 0x150D735C7213E772ULL, 0x14731E3EB6A18881ULL, 0x2F44DF6FDAEE4F29ULL, 
            0xA07DDDFEA382E377ULL, 0xE85873B08E7CB0D8ULL, 0x1B55D959A83F6806ULL, 0xA2323D89C3BC8E39ULL, 
            0x63C6D41C9C78A9A2ULL, 0x179F472CFD76D945ULL, 0x4E67A8C6037561E4ULL, 0xF7811331E5183214ULL, 
            0xD557490565B99431ULL, 0x003A0E857D976DF6ULL, 0xB9A126E376889F9AULL, 0x141F23B03EFCF8AAULL, 
            0x19651BDE1FEDCBBAULL, 0xF3A26D878ED04E5EULL, 0x4F7783D3FC5FB998ULL, 0x47EE77C60050A85DULL
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
            0x8AE7D8671867C486ULL, 0x4AADFD608DE9C308ULL, 0xA1053A581EB25B1EULL, 0xD397222874926853ULL, 
            0x87EE6751B389C214ULL, 0xC4573AEB3DD4E4A6ULL, 0x6142B34051B98174ULL, 0x5D02A9F71804FCB9ULL, 
            0x07A0860CBC4984DDULL, 0x939F24D197A5E674ULL, 0x85AA786C6DA77AD8ULL, 0x0AC2F1C29A48522EULL, 
            0xBD1D993FB5AB4D0AULL, 0x050C40A0F47F3CA1ULL, 0xC14ED373C84D5DF4ULL, 0x1B40C933E8370A0AULL, 
            0xBA15F0D02372984DULL, 0x91F412C0128F404BULL, 0x1A0CC0B4F32635CAULL, 0xFACCE4BD6E93C6E7ULL, 
            0xFCFDD56A839E5E04ULL, 0x3700424F9A0A81FCULL, 0x578D9A475B309F40ULL, 0xF28AC6499D302596ULL, 
            0x07232E8FA31F2E88ULL, 0x3AE0B5D8D4104400ULL, 0x19B50FABE590EACCULL, 0x59146877689E13C2ULL, 
            0xEA689B594C28697EULL, 0x8593EC041ED353F4ULL, 0xE31AA1ECAD8D1562ULL, 0x34123E768BB1F667ULL
        },
        {
            0x937CA21F835889C1ULL, 0x0FD1EFADB2B09BB9ULL, 0xACAFFA5D97F3FDDEULL, 0x270F7553758AC524ULL, 
            0xA2E6EC3322318A8BULL, 0x544FFCDD6FAE4155ULL, 0xBE6E720366033DD0ULL, 0xF33207DD6BBCA9E3ULL, 
            0xCE92952DE7D86F02ULL, 0x609D97FE9109C8C5ULL, 0x5836CFEEEABB0DCAULL, 0x4DF6A69CB4F011A6ULL, 
            0x60B00F81A7A8ACE6ULL, 0xAEC4E8FF885B6FE9ULL, 0x10022ACDB3380EBEULL, 0x0124144572EF4B93ULL, 
            0xBEC7800A090DB739ULL, 0x948F83A900DC1C39ULL, 0x868EF869C68C4E5AULL, 0x85E4619DF198A2BBULL, 
            0xEC243530F7156678ULL, 0x7881BD202DF6D154ULL, 0x7B625379D446C4A1ULL, 0xFA5575ECCD6646DAULL, 
            0x429E2CBFB9A90997ULL, 0xB5410333AEE9CA25ULL, 0xC3D789873A7DB6C7ULL, 0x7B3474E301B3A939ULL, 
            0x86043BF761AB8942ULL, 0xA1E8FBDE7FEE02C2ULL, 0x3C08EAFD39C4AEE2ULL, 0xE86BAC76159C14BFULL
        },
        {
            0xDB88BA91390CCFE7ULL, 0xCA1CFE08D90C3ECFULL, 0x75FAE320DF095362ULL, 0xABAC123BACBCF3C9ULL, 
            0x94134F38569CD4A0ULL, 0x2F80CD56E6F8351CULL, 0x2901FA993D9C0EBEULL, 0x04B3AB759FF31E1EULL, 
            0x08235006DE167E6DULL, 0x2FD1E255B0A0B93EULL, 0xD5EA8824B78949DBULL, 0x7E45124F97ECDBFBULL, 
            0x81D68622AF517429ULL, 0xDD87188303088E51ULL, 0xA0DDD41E252256C6ULL, 0xA677E84F7BC9A97EULL, 
            0x53A89988A4842C45ULL, 0xF6E370FED31555ECULL, 0x354F3601859E7CA0ULL, 0xE67ECC2A55F0486DULL, 
            0xABB35E34AAB1787BULL, 0x63D4FE9784F435DAULL, 0x8F17CD38CE9C7277ULL, 0xE7FF4A1BECD6E408ULL, 
            0x2903B65049CC5BF8ULL, 0xDF7515748ABC8108ULL, 0x98A110CA274FECEFULL, 0x37CEC68FF0899566ULL, 
            0x97FB068BAEE55FFCULL, 0x5ED34D6CA40D8C03ULL, 0x694ADE4F097F64FAULL, 0x4506B14FB7E62E01ULL
        }
    },
    {
        {
            0xD618AD7088FA4544ULL, 0x9EA6ECE6E1B6377EULL, 0xD57C75103DDAAB0DULL, 0x50C1F996F2489393ULL, 
            0x0D010DD6B9910A1AULL, 0x031E9372D598B5E1ULL, 0xC8DE46A420ED9C16ULL, 0x311A17515A6453C6ULL, 
            0x19FF1DCA3CC3EC16ULL, 0x17894909F6322B20ULL, 0xCEE771240D00338DULL, 0x74EF787002F6BF01ULL, 
            0xE2115865473A8793ULL, 0xF9570DD08DBADD9FULL, 0xEBFCF2C0564C2796ULL, 0xF267C9ECEC8D159DULL, 
            0xD15654C326E40664ULL, 0xD2CABC4A1FB1ABC5ULL, 0xB96CD02222F3CFB4ULL, 0x2309B6F972FC2656ULL, 
            0xF052247C4BC873ADULL, 0x1F87EA98A0A45453ULL, 0x5649D66E990C309EULL, 0x50438CF8A8CE9ABBULL, 
            0x17C5D87A3B5584F3ULL, 0xF075535BB21E3772ULL, 0xCDEFB1AECEED6623ULL, 0x3517FDCC287CB677ULL, 
            0x710679F2360D7458ULL, 0xDAF5434DF93245EBULL, 0x3A9E422AB57BC69DULL, 0x52F27F99FA435402ULL
        },
        {
            0x2C56615AD95FE152ULL, 0x80A1386A1BE0CF37ULL, 0x18A5A9B15307E4DDULL, 0x19F52FC0F9BC53C2ULL, 
            0x95D88A5B94CFFA49ULL, 0x0CA35BBDA6CEA74EULL, 0xD9B7AF460FB0C9FFULL, 0x4C65D4217D37CC97ULL, 
            0x7ECBFC49B7421365ULL, 0x72428763A0FE27F4ULL, 0x21BEC7D3B31F22A5ULL, 0xD3C6A00BB1E7AD97ULL, 
            0x2D17AEE4C5E8A940ULL, 0x7E332771AF661CEBULL, 0xB39F4C7A3209BD06ULL, 0xB0B84A3D05EF0FC1ULL, 
            0x1F1346C2EBF3BBF5ULL, 0x12098B651EF4313DULL, 0x0FC1ADA6C3A63F34ULL, 0x12A69A7CC953FB3AULL, 
            0xE545407ED4ECDAE6ULL, 0x30BEC90E70ED6D87ULL, 0x59604600C6583CF4ULL, 0x105D1535A76C697EULL, 
            0x536B6BC5A5A8D7ECULL, 0xDCFE245DD2B4F7DCULL, 0xD9A209183D019743ULL, 0x940DD35C4A45F9DFULL, 
            0xA2B839442116855FULL, 0xC4112BF558472150ULL, 0x5E50D130A7DCC2DAULL, 0xE08FB0FA2B77D5F9ULL
        },
        {
            0xE61ABBA392C7615AULL, 0x179E583F017181D0ULL, 0x0EA158F4AB2BCB07ULL, 0x23342C976843B184ULL, 
            0xC3020A3BED173D78ULL, 0x7D9AB0AB8D2330E7ULL, 0xB4AFBFE58FFBD486ULL, 0x09CA46C7666C9E99ULL, 
            0xB1330B220515FCFDULL, 0xD382659A2D0E89BCULL, 0xE3AFD5AF7AB3C03EULL, 0x5BC0CC4CA2DFBBA6ULL, 
            0xC53EF316848C66A3ULL, 0x9E2CC80800B25A53ULL, 0xD74F2FD4CE920C5FULL, 0xE063C2FEF1142F3CULL, 
            0x2E3FB273B922E169ULL, 0xDA09960439BC51B5ULL, 0x701414A9D76E09F6ULL, 0x6E87CB9DE6ED4486ULL, 
            0x388E6B57580723FCULL, 0xC5441AC2F9FDC429ULL, 0x0D779ADEADBBD7BDULL, 0xFBEF9E6C35AFDE5BULL, 
            0x1CA9EFC4C890DA29ULL, 0xB3E38174A5C47096ULL, 0x2CB9BFA8E7DD4D49ULL, 0x0F1CFBA55440EFA0ULL, 
            0xEE425DB9E78B34D2ULL, 0xB97334A383BB1265ULL, 0xDAF21975B26225F7ULL, 0x824C45DA714DEFC3ULL
        },
        {
            0x1D001AE96DD9663FULL, 0xE756396964EA2A19ULL, 0x3151CFF4F50C6960ULL, 0xA9B249EB99955106ULL, 
            0x66A828D696B49392ULL, 0x9796A3783E01E8D7ULL, 0x32C6DF30A2D384BFULL, 0x7C9706488F8ADAFCULL, 
            0x1D5824A30C06BB72ULL, 0x7C7B335AD187A7A9ULL, 0xA24B52C3E8360074ULL, 0x07211D01368AAC5BULL, 
            0xF69A448C300599F6ULL, 0x0BB3D2D9E1DB373DULL, 0xD0E6C129762D47B2ULL, 0x0AFE33A3AE436AECULL, 
            0xAEA46D3A8EF9A242ULL, 0x91E46F1EAD64F581ULL, 0x7D22AD8E364633E3ULL, 0x8D27A4D0E79064BFULL, 
            0x6995CC1089670909ULL, 0x60916ED56DE5568DULL, 0x8D5FC7E8060A0E5EULL, 0xF0611249BC168590ULL, 
            0x2650A5EDEBE690B9ULL, 0xACB9D40E3F8C3447ULL, 0x7C9562FADEC4D5D0ULL, 0x864A436BB75715B1ULL, 
            0x07816E7CD0526B52ULL, 0xB23D4D67BAEDE1C9ULL, 0x5A89859CDE520CF5ULL, 0xAA914D4EB99AC34CULL
        },
        {
            0x3987BFF7A2AD51FCULL, 0xFB654404AA62F5EDULL, 0x5593F3849873CBB0ULL, 0x745F3995B9D8AA24ULL, 
            0x4835743D25C6B154ULL, 0xC958CB80D13C3875ULL, 0xB09CF08447C454C7ULL, 0x28782EB2AE9C27D1ULL, 
            0x1416D676ADBE55C8ULL, 0x9AC0AEF86F24E002ULL, 0xA25FCF4E6A31A45EULL, 0x2D1E6F7E27A6074FULL, 
            0xD15FEBA1FAE59CFCULL, 0x1D21A319E4CAA9E5ULL, 0xBA67973449042D08ULL, 0x018113A8DFA1ECC5ULL, 
            0x8A31CB137FD68192ULL, 0x330F3825E6851D1FULL, 0x89E362735680AF71ULL, 0x7043DC0B2493FA14ULL, 
            0x6864CC7AD18EE1B0ULL, 0xA6F5C90E49BC9C3DULL, 0xF88310180F2F14A5ULL, 0x9C4B05A8191D153EULL, 
            0x6B83ADBB3A077B61ULL, 0x10380202A59E2A55ULL, 0x4AE4BC3269067451ULL, 0xA77134F00C84D34AULL, 
            0xB2C05CFB801CB1A8ULL, 0x591A9FCB2F37F689ULL, 0x7AD01811EF6E6FBDULL, 0xD00C930CDD019F6AULL
        },
        {
            0xD9972B34FDD68D95ULL, 0x7F5260099E651E05ULL, 0xED37A35382585041ULL, 0x23A1BC2AF04B62D5ULL, 
            0x820C28E98695A31EULL, 0x5B5E651640BC6AD0ULL, 0x2319DDE7B8465C39ULL, 0x0752D90DC9E61895ULL, 
            0x8A6897AEF876D6EDULL, 0xEBC4836F93DCC744ULL, 0xD94D93F6C391746CULL, 0xF74494D89126705FULL, 
            0x53CDEB26B4AFFD4EULL, 0x50DCF3345DBEA100ULL, 0x3BBA4935554269D0ULL, 0x00D445F9E6C309CAULL, 
            0xB41C5FFCA91A529EULL, 0xEBF686860DE30ACBULL, 0x0E63497842030619ULL, 0xD712FD23FE6C391BULL, 
            0x47554E822BEDE197ULL, 0x9A7B35C5C052F400ULL, 0x664B751728FF1C54ULL, 0xB8EFF1EC9B2ED6D1ULL, 
            0xDB9F6220D532EE7DULL, 0xD39BA2A880BB54B7ULL, 0x452CDB760F1A0661ULL, 0x78EEE5825C8E555AULL, 
            0xA0D2B1AC7203CBA7ULL, 0x334BE2193A5CC30EULL, 0xA0A1E3B6DAED52CFULL, 0x8C8F1F88AB40D8BAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseEConstants = {
    0xEC07660933DFB3A8ULL,
    0x3E1DCB6CF6B64EC1ULL,
    0x5012C196F24FD40BULL,
    0xEC07660933DFB3A8ULL,
    0x3E1DCB6CF6B64EC1ULL,
    0x5012C196F24FD40BULL,
    0x5B1AC952B4F5A29AULL,
    0x366EFEC970BD54EFULL,
    0x81,
    0x22,
    0x13,
    0xFC,
    0x5C,
    0xB1,
    0x40,
    0xAC
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseFSalts = {
    {
        {
            0xD264E53BA2FB7E09ULL, 0x34BD4D66F1D12E1DULL, 0xECE7A70A7C3C670CULL, 0xAC0A9BD02CA84B26ULL, 
            0xA5B8F2D4CB23AE10ULL, 0x812AE8BE4A60E67DULL, 0xBF7F03F35258F8BEULL, 0xC7C8636920786920ULL, 
            0xB25B2C02343B36F9ULL, 0x468ECCE9AD72A721ULL, 0xD6E2BDFA7EA8272FULL, 0x67D6A4D07E27D48CULL, 
            0xA9859E1C408C3BADULL, 0x6E3E1F8596406BC3ULL, 0x21D238EA133C242CULL, 0x1820F12A44EB4F2BULL, 
            0xFC2A418EB18E774FULL, 0x897D841945FF7C9FULL, 0x26A4953E3D03E0E6ULL, 0x7173B871F5B293C4ULL, 
            0x90B6DD78B7801EE7ULL, 0x089A778617B8F438ULL, 0x2EB68165B3B94E1CULL, 0xF6C57EF99432ED19ULL, 
            0x829B9573272B4BF3ULL, 0x22A79287B29E9DC8ULL, 0x675D8BB7B9856E5EULL, 0x85CD4201B1FB3A48ULL, 
            0x73349C05B3FFE2A0ULL, 0x1DC3A011149A4FD1ULL, 0x1259BF4512375E59ULL, 0x5160A76413DC4C11ULL
        },
        {
            0xC3A99E9F3A612454ULL, 0xD7C67E6C5F4CC0FEULL, 0xB39A12C019019AE5ULL, 0x01B302EF2EA469FAULL, 
            0x1F1864F2CCAF90B3ULL, 0x927F64967F63A06EULL, 0xF4A023C6DAB4AC90ULL, 0x8E286D09824E1727ULL, 
            0x9DC1379665FEA83CULL, 0x7FF13EE3FB8D697EULL, 0x107C42E675984E50ULL, 0xDC35F94459AE1E2CULL, 
            0x90F262BA65FED892ULL, 0x94BBD5CFF66C73C0ULL, 0xF912A9D7626388E5ULL, 0x465A1642667F338AULL, 
            0xD50E979B45C23676ULL, 0xEBCB162B5ADEEFDFULL, 0x1FB37281A3EC87F9ULL, 0x25A8160FA5D2F964ULL, 
            0x2157375E7EC41B18ULL, 0xD6E44C45ABC2D0C6ULL, 0x5DFEDA693014455AULL, 0xE53D0896C26E5E04ULL, 
            0x11C7C8F180822970ULL, 0x295997426E4E765CULL, 0x41FC3BDE0B6712F0ULL, 0xCBAE399587B5DFB2ULL, 
            0x939EF6CE3422D78DULL, 0x8E1152454543B285ULL, 0x6E1B5718336D12C7ULL, 0xB10C831C4E9CEE15ULL
        },
        {
            0x73ABEED74A0B78F8ULL, 0xDF7796AAE8DE3CBEULL, 0x50A1290F006136B8ULL, 0x9CB02F06699E3718ULL, 
            0x23CEABE6E8F8E961ULL, 0x4F4550465A0A1D92ULL, 0x0008141C78260B22ULL, 0x0689C1429A02A79AULL, 
            0x126C5C02595B5C9AULL, 0xE67256F2C91BAB61ULL, 0xCBEAE8052B4EC927ULL, 0x217D080CFBEB40C4ULL, 
            0xB58E3370CCAFBE8CULL, 0x4BD489B491221AA7ULL, 0xD482113CFE2B97DDULL, 0x86FC1F12B1E607E9ULL, 
            0xB7FD47152A9F85FBULL, 0x42314DAFC1FF3492ULL, 0x5347EEF0FD34FB1EULL, 0xAC430FBF12D2FFBFULL, 
            0x50CE3A5222BDA1FAULL, 0x3CC14DA453DF2EE5ULL, 0xECDA345B1EC7F6D3ULL, 0x2B400456D25030F5ULL, 
            0x52838ED4CD05CDEEULL, 0xCDFE4EA3E523D994ULL, 0x5EBF01A39DE19C04ULL, 0x52E0804CA36F2BE1ULL, 
            0x995280571B55ADFCULL, 0x1C69AB1A040445ADULL, 0xA302925701C6018EULL, 0x498CB90C9AB02CDBULL
        },
        {
            0x93E1A62408672CE5ULL, 0x931BDBBC581B8138ULL, 0xDB15642BA8F226F2ULL, 0x44AB92FE7301E93EULL, 
            0x1D00D6E968B4BC9FULL, 0xBC1665CB2D815E8DULL, 0x9C402A92710E0869ULL, 0x195E3DC7C7C58CF0ULL, 
            0xE3BDC5F1B0B167F1ULL, 0x03DA7E6D9AE1D2B1ULL, 0x21247AB5866CECBCULL, 0x1FD31CE6D7D0B99BULL, 
            0xE52A7A90D47C5682ULL, 0xDDA54C01E91F146CULL, 0xE839DE5E9BD4AD4FULL, 0x0EFE0D818B65C905ULL, 
            0x99BFAD425D6ADD17ULL, 0xCCEEF6C2294ED3A5ULL, 0x781ADA4CC63990E6ULL, 0xEB450E258E450C4FULL, 
            0x130BCAC1A3AF6789ULL, 0xB4D904DBCD073018ULL, 0x31B3F24FEDE17920ULL, 0x8748E2002C2C2578ULL, 
            0x986F785A654519DFULL, 0x1AC031661A407504ULL, 0x15061677CBCD5E67ULL, 0x3205837C1FDA5930ULL, 
            0xF936DAFDF010D1AAULL, 0xACD263A7043D1F48ULL, 0xAD1A93D826A88A83ULL, 0x173F7FBE4D8457ADULL
        },
        {
            0x040138A4D41B970FULL, 0xD0466F208C1FF68EULL, 0x133638E99725FB03ULL, 0xD9CF2BDA1F33D076ULL, 
            0x6E3D0085720AEFE4ULL, 0x9A8BE6007A961E34ULL, 0xCC4BA36D7810C9B3ULL, 0x16236AE86ADDDD0DULL, 
            0xEFFB81C199DBF7D8ULL, 0x1DB9A9EEF4EC345CULL, 0xEA7078217134E3FBULL, 0x218D85ACF0E46F4AULL, 
            0x8E75EEED1AB8C065ULL, 0x7E6272A690ED6F73ULL, 0xEE75137FF2058F53ULL, 0xDAF781E220E53FB6ULL, 
            0xBAC22D296220DF63ULL, 0xA0BBA760395E85FCULL, 0x65445F7D9B4361F4ULL, 0x6A1B4AC1284B1726ULL, 
            0xF2767D9A0EEA379DULL, 0x3BDDCCFF492CC6ECULL, 0x7605E890E49E2DBBULL, 0x406132803233ACDFULL, 
            0x8E9AE7CCD966E6EBULL, 0x9BE2941D4C660201ULL, 0xB009BA6FB79A5F40ULL, 0xC28DE74C7116E515ULL, 
            0x364ADAA7FAF6C0A4ULL, 0xCAB3806E435F1B85ULL, 0x1F286951509215E7ULL, 0xEEC870F1BD7E25FBULL
        },
        {
            0xE7C7A4DDE75B6FF5ULL, 0xBFC94CF800872E11ULL, 0xBF1CA449E08C73F5ULL, 0xE6FF40D1F85F7E82ULL, 
            0x6DDFEE4918032561ULL, 0x040D8E310212A2FFULL, 0x9B9CA4D1CE88601AULL, 0x5F8700BD0AA0B25CULL, 
            0x1C46BACA7D654093ULL, 0x566FADD78EB8CB82ULL, 0x2017C5D925DE58FCULL, 0x316DC098731339FEULL, 
            0x89297306237952E4ULL, 0x602F5ECD73A22925ULL, 0x8B3943D7AE92C60DULL, 0x7C4FCE11F801AF8FULL, 
            0x69FA75F0EDB8499EULL, 0x05FAB6E64B31D95FULL, 0x45750BF4767895ACULL, 0x131A536B6507ADA7ULL, 
            0x93E97A2D9ADB326BULL, 0xB7F60CB8CC3BC19AULL, 0xF179D0795C593C9AULL, 0xF6A8C32478745DEBULL, 
            0x4F8AB7C7FCD2D069ULL, 0xD7F103E327BF58CDULL, 0x01D0DF1F1EA0879BULL, 0xFD772898761738AFULL, 
            0x703A32164C4F9BEFULL, 0x61E29894573FC223ULL, 0x4D6DB5405B0066DBULL, 0x5EC9102728408D8DULL
        }
    },
    {
        {
            0xC870C7F532A32B05ULL, 0x80C1CE661C944C6AULL, 0xF9BF84D10477BA75ULL, 0xC67A674D5F8EFC73ULL, 
            0xCEABE0247B8DF860ULL, 0x10343D0E603BF583ULL, 0x5C12A8F0BBA7BBD6ULL, 0xCE60BC18F0F693D5ULL, 
            0x30875318AA01A521ULL, 0xB8C81F5D15E96F77ULL, 0x8DC8019F397B26A9ULL, 0x5844DB9FCC94E3FEULL, 
            0xCC1E7AF64BA477E6ULL, 0x03AED1262D505690ULL, 0x1CC4D591D1518479ULL, 0xD71B84907A982FA1ULL, 
            0xBB8530D5A137B90AULL, 0x2E960761EC10F169ULL, 0xBAA009ABE1C2B602ULL, 0x3581140733E3918FULL, 
            0x40FF344EC8422CF4ULL, 0xD682826B03BCA30EULL, 0xD367B4501FC31AB0ULL, 0xEE03C7827D72D7B8ULL, 
            0x2E99D8CF6C61DD32ULL, 0x82DF1F77E30AF29EULL, 0x4F1D3AE7C296A3EAULL, 0x00C805F78ED6B43CULL, 
            0xF26E4730F54CE89DULL, 0x3E853057F6A0374FULL, 0x7A083792E080BC69ULL, 0xE54161B3EBFAE7C2ULL
        },
        {
            0x8E9D312D2C29E445ULL, 0x63796C59AF771F8CULL, 0xA96C4CA52DA2E627ULL, 0x260BC7CA1DF55D2EULL, 
            0x4E942B460859CB20ULL, 0x54F4609BE6E41E80ULL, 0x64D6D622623D8833ULL, 0x6771BF4C5AF69BA9ULL, 
            0x309358D0B33278DEULL, 0xB9EC5CF9BC7365DAULL, 0x15726634CC55D2D7ULL, 0xB70F32C45D0FD9E1ULL, 
            0xF8763A6B189D89F9ULL, 0x024A3A1047D7A385ULL, 0x570898C9BD439BFAULL, 0xEFE923446600F4B6ULL, 
            0x6DF3B64DC6338973ULL, 0x8B8636593A7C938CULL, 0x310A7903112B10ADULL, 0xE48C29F00EEB71DFULL, 
            0xBE25222DAA6B2542ULL, 0xB1321531878ED5A9ULL, 0xCB394DAA65ADC9FEULL, 0xF3232F46708F9534ULL, 
            0x7E5B97A9721DD5C5ULL, 0xD620DE3D13335B31ULL, 0x17DFB8DB629E3D4AULL, 0xE806DF14DEA188F4ULL, 
            0x4ACE5B3FC138CFD9ULL, 0x289B50A2D117B3B3ULL, 0x241CBE1C7FD58171ULL, 0xA900424ADD6A1044ULL
        },
        {
            0x00B5BAA5F6DAF1C4ULL, 0xB4931EC43975E2D5ULL, 0x57A571EC5FEEDF82ULL, 0x98B5454B8B2C8306ULL, 
            0x033DA38BCECCE025ULL, 0x9938533CC3052624ULL, 0xD0BAA8B56C0C0FFAULL, 0xB20E77881693285DULL, 
            0x75845A557216709EULL, 0xB8959B020B30B01CULL, 0xE50617856D49CB74ULL, 0x9420376ABEA701A0ULL, 
            0xBCEB3C84EDF995BEULL, 0xBDE6616116895A0DULL, 0x479D809440EC924CULL, 0xB7C80EDD4B9101B0ULL, 
            0x9E57EC9AACC3362FULL, 0xE8EBFA73C73B82D6ULL, 0x52569E6D62F80B06ULL, 0x76BCB510D54BDE90ULL, 
            0x703538F3394CB06AULL, 0xC4F932F4B9F74E60ULL, 0x54F3AA2FCAE4FC6AULL, 0x8E74D3C6E0DD03E5ULL, 
            0xC2BD9014DD109839ULL, 0xF47A23DA816B263CULL, 0x5B5612904C8931E2ULL, 0x822E399FA73E06DBULL, 
            0xA6CC8C6A068DA327ULL, 0xE2DF2B072650E4BCULL, 0xB6B8F1318EBF1BD7ULL, 0x37357CBB05AE0644ULL
        },
        {
            0xED212F04FDA0D4B1ULL, 0x30D3BB8446CCA864ULL, 0xDFA48C0F4371D824ULL, 0x2B4ACB8D41EB87A0ULL, 
            0xC3DD84F29C652184ULL, 0x01FDB33587B17719ULL, 0xAEA6A8937823E801ULL, 0x19FC334344803E2DULL, 
            0xF5E8CDA75FA6F930ULL, 0xF277BA39354C8BD0ULL, 0x6D8EC25B51B1B81EULL, 0xBA7C5CACC3C2DBF6ULL, 
            0x75B288812CB1012DULL, 0x623E215F691C1054ULL, 0xBADC09EDC7406675ULL, 0x7A0A7A2F99CC0BAFULL, 
            0xA3398A2E081DB99FULL, 0x49A95625B8D49780ULL, 0x798CC07A1B66866FULL, 0x59932C4020AD6FA9ULL, 
            0x3AC616D0D4AC4AF9ULL, 0x47FC8E2B0EC2E0D4ULL, 0x916211B66401EFF0ULL, 0x0750103AB89FC07EULL, 
            0xB1E48646E04A313AULL, 0x41F5D692A3C7AF5BULL, 0xDA4569798B388BD8ULL, 0x7A2223BD9C84BB75ULL, 
            0xDAF08232C7B77B77ULL, 0xC01EB051BDD8D4B8ULL, 0x59A67717507BEB38ULL, 0x7D6437D993525DAEULL
        },
        {
            0x8FAAD7462343C806ULL, 0x27B176248B8E5C7DULL, 0x4CAB68A45AF932E4ULL, 0xAD3B3581AAA60530ULL, 
            0x7B42301229A812C6ULL, 0x1A7996FE084F53EDULL, 0x370FC753B6F100F0ULL, 0x793ED9CD814A58DBULL, 
            0x91C5D75F377B21A0ULL, 0x5160FF28D590A72EULL, 0x8F02F26DF864146BULL, 0x95BA184EE63E0D3EULL, 
            0x1104559695F73DABULL, 0x8A9968AC32351EDEULL, 0x31DDBCE8F009A8E3ULL, 0x3B434115D9DA50A6ULL, 
            0x1D25DC5288E1E7F3ULL, 0x56BB5C1C9E0AFD90ULL, 0x10C10C9DE1B04DAAULL, 0xE8B6E365F8477F8AULL, 
            0x29965BBA82A47E8FULL, 0x4096C78168050097ULL, 0xB374A9D487963DC5ULL, 0x496F2A696CA25BECULL, 
            0x9E3C553BAA0769E0ULL, 0xA78FB5D4E0E92F27ULL, 0xD1D8A4A6768504F7ULL, 0xD0FAC7AD278EA441ULL, 
            0x558FBA2E369DF8B4ULL, 0x3759D7D58DFA4A57ULL, 0x5DEFDADA5D59CB81ULL, 0xF0596E3E8D0DB4C3ULL
        },
        {
            0x0F4C2D4D9F7156A8ULL, 0x9FB3D78EAA19110CULL, 0x1EBED85FEF41D755ULL, 0xB063410A94154AB6ULL, 
            0xC9206203CBB5D875ULL, 0xFF65D1E8E38BD437ULL, 0xA6B5FB98CCB2E6C6ULL, 0x8D0012DAA65D3B9DULL, 
            0x3FBA881E13F16E97ULL, 0x0D81C9E2C60DE055ULL, 0xED1073DA6FE0A6A4ULL, 0xE1FC36D338A5DEA9ULL, 
            0x4E1CF43117174060ULL, 0xE863DECF487DBAB6ULL, 0xC88ADE45F81D21F7ULL, 0x7285B89CFE171627ULL, 
            0x467D9817EA891F84ULL, 0xAAA9A96678A87B3EULL, 0x5261E0A20E7761DCULL, 0xAE350B30B7BAF48AULL, 
            0x7DD1AC4B0B6DDB35ULL, 0x45AAB7AA5F736EE8ULL, 0x1D846B44847D7BAAULL, 0x4EAEE31AD806ADF8ULL, 
            0xC3A7E23FB34AAC83ULL, 0xC3F43F995CD3564DULL, 0x8BE1E1B5DE356189ULL, 0x8D5E755037C95813ULL, 
            0xCA4792C8E856533EULL, 0x65CD9A02E3F2DB10ULL, 0x8580C9EB4DA04F17ULL, 0x7C5EC95C789D2497ULL
        }
    },
    {
        {
            0x97EC00C5932B4F77ULL, 0xB5E657C8F7848249ULL, 0x30A2BE2F1229C12DULL, 0x036B544EF0C787E2ULL, 
            0xC18B83E380562092ULL, 0x68D9B442F76A507FULL, 0xB31E7DCD5EFAD1D3ULL, 0xBCFC1CCA47AA12A5ULL, 
            0xEC8509C9E05D0A77ULL, 0xFD31F2CBBA1C50E1ULL, 0x425DF17CB1255115ULL, 0x7EEA15D1E6BD5920ULL, 
            0x990C468167F77C11ULL, 0xB9EE9FC510BA6C34ULL, 0xA444F74F9685F077ULL, 0xAA511768610F06E5ULL, 
            0x9A5E79E89B456634ULL, 0xAB31CA58030FF00AULL, 0x5D303FE52BE2896FULL, 0x9C8A3722810B5531ULL, 
            0x3737317E382097E8ULL, 0x88F9EFD04746CF45ULL, 0x20B7C639FFF5F79FULL, 0xECDF18EA468E7F6AULL, 
            0xB9049C0AAA3835E9ULL, 0xF2D8536E6504FDF0ULL, 0x80C55AF986461DCBULL, 0x9A5761294424CC50ULL, 
            0xAD033865760F171EULL, 0x48FAB18A01B629E6ULL, 0x0AE187060EAEE0A0ULL, 0x7E596816D96F4065ULL
        },
        {
            0x5D21004C428F77E5ULL, 0xD724B94B0090141FULL, 0x8D964D8AA491BBB2ULL, 0xA0502A38FA6F4C08ULL, 
            0x8E92F220528DB283ULL, 0x457819D3FB7C0CDCULL, 0xA08D39A389DD9C80ULL, 0x188A047A57CB1E89ULL, 
            0x9EBC767362D16375ULL, 0x6FAB7DE67507518EULL, 0x964522AD816BC781ULL, 0x19B23B72A2948BA9ULL, 
            0x5DD6F4C21662053EULL, 0x1FA6CB2F09FC0AD6ULL, 0x0817FCAA36590399ULL, 0xA6A0A5EA355237D4ULL, 
            0x8BA966DE0076D705ULL, 0x720239AEEAB62FD4ULL, 0x8247AFF21577EA60ULL, 0x697D7875E1EBF3FEULL, 
            0xCE6ED6E309906BC5ULL, 0x172D7035ED6C91F1ULL, 0xD58A4D908A404CAFULL, 0xA740B37C597F583CULL, 
            0x2BD8477CD239F6E9ULL, 0xF59E09CFE2B3305FULL, 0xD7F7B5CC9B4C8B22ULL, 0x0BF21F7991C9B0DBULL, 
            0x69EAC61278178CDBULL, 0x38C0BAEF82EA94DAULL, 0x0F129075296BA5B8ULL, 0x158649F23ACDE2F2ULL
        },
        {
            0x007B49366A71D6B4ULL, 0xD555B27876439801ULL, 0xA3070328341C1F27ULL, 0x9A1C8092ADD95C8DULL, 
            0xAC9C98B58C930D8CULL, 0x62C16F448CE3673DULL, 0x2727ECDE5114AAD2ULL, 0xF8C27D1B27F66C41ULL, 
            0x220DDDC7224E6695ULL, 0xACB667368660CC81ULL, 0xBFE91BF1F48B3AE4ULL, 0xD4B254119A724320ULL, 
            0x497AB7A70FBF090AULL, 0xE19A9D630FA63BB5ULL, 0x8DCD4660305144A2ULL, 0x67B69FC208094CF6ULL, 
            0x6BC169314E03C0E4ULL, 0xCFD6F2C17854FFB0ULL, 0xFEE7CE5965106909ULL, 0x989D2B76A54A26D9ULL, 
            0x75F2D9A1BBCD260EULL, 0x9F0880F0501F916DULL, 0x550BFFF14001EBBFULL, 0xB2D7FDA287C4D2B4ULL, 
            0x853BDE0547DF87E0ULL, 0xBF7C0D9066A3D22CULL, 0xBD55AE534EF254D6ULL, 0xCA487B5E729A005EULL, 
            0xF16F379F4FCC0E2AULL, 0xE49A51645B147757ULL, 0x7970A64ADC966E88ULL, 0x92262F865F8EFA6FULL
        },
        {
            0xA0394377E4FEFE46ULL, 0x0C1F545DE104D9D1ULL, 0xB121CA87E5F8C2C1ULL, 0x3D3004B0588BB61DULL, 
            0x13A5BFB0B43DE6A3ULL, 0x35D6F05D3A41AF17ULL, 0xC5B6ED75342ABB23ULL, 0x0CB0721581619F94ULL, 
            0xF345F80C9F98A0EFULL, 0xE93CD3442371184CULL, 0x9F50786FCF93A6D3ULL, 0xCD378F858D11A873ULL, 
            0x77AA36ED5E08810FULL, 0xE2F43188A62914F3ULL, 0x5AB9A67C950192D8ULL, 0xF68062630CC3DB63ULL, 
            0x645F11BB49858822ULL, 0x8430E1835E6F2E4CULL, 0xFC92342D8F63586DULL, 0xBD769AA3979DD76EULL, 
            0xEE62A2B1A7047C9EULL, 0x7BEB14887FC1166CULL, 0x787D8138E45A21F1ULL, 0x7A352A5FA1A6242CULL, 
            0xC1DE952D5CDDAFAAULL, 0x8DE7C33288FBB7BAULL, 0x15756F35CCAAC876ULL, 0x3D945DF2328886CCULL, 
            0x4DEA2CB366AB30B0ULL, 0x8E5081E389D5BD80ULL, 0xB06EC8CA86880667ULL, 0x6C55CE888456E30EULL
        },
        {
            0xF44B6494D72E6B6EULL, 0xE3745F42EE78260BULL, 0x5A49768EE2780C19ULL, 0xF9BAFD0DC200A64BULL, 
            0xFEB48E2FE8B8633FULL, 0xA312B04878217078ULL, 0xC7D4FACFB45324AFULL, 0x6F4AB2923833AAA1ULL, 
            0xD4D99F0BBC094678ULL, 0xE20F1C27557148AAULL, 0x5C299FB3D7705D9EULL, 0x6BE8DA800D18D4E5ULL, 
            0xBB337AE874AC11F5ULL, 0xF36CFB57F7AF50E8ULL, 0x29A40F4C6967F49FULL, 0x2AF9CD77171DB051ULL, 
            0x97298B66E1248800ULL, 0x2358201348B4431FULL, 0x9B33F73B9137EDECULL, 0x04C60625D6D61E6CULL, 
            0xDF8E09CECAE4CF60ULL, 0xF502A5283B94D126ULL, 0x6FCE38CFB845F206ULL, 0x1BCF35E4B6844C65ULL, 
            0x6C413B58982A293BULL, 0x2CFBFAC8D90D2B9FULL, 0x027403BEFF354199ULL, 0xEFE83006449723B0ULL, 
            0xE3DBE1B12BDDED1DULL, 0x44E5E49C28FAAB4BULL, 0x89BA8D6F47588E7FULL, 0x3EA6F928A04116E8ULL
        },
        {
            0x5C5769C687497A60ULL, 0x9D9B517AD506328DULL, 0x5B56AC3FE5550201ULL, 0x98A3CB763DB77325ULL, 
            0xB9FBE75C40568AC3ULL, 0x5F2214B5604ED275ULL, 0x32F1D63510E2D38DULL, 0x97AAB90E6DAFC688ULL, 
            0xD32E47FF2F6E4AF1ULL, 0x085092A365E5D083ULL, 0x9A39F199D013FEBDULL, 0x53C5A7D76BAF17AFULL, 
            0xCFCD14CD14650C5BULL, 0x5F2F797ED1F78450ULL, 0x9EDB214E7C747B9DULL, 0xE2B433152F7EA606ULL, 
            0x4B8B9D8D71B3ECDEULL, 0xAD133016AF2E2D35ULL, 0xEE3622186A24E776ULL, 0x38C1B46FFCFA248FULL, 
            0x75F191E7642FCC03ULL, 0x3AE474DC68629A86ULL, 0x35A1EF4C3E1479CEULL, 0x9A0306922AC57935ULL, 
            0x906FA0F605C5C008ULL, 0xF831D72BD1697998ULL, 0x102CC1D8F366F0C2ULL, 0xB8835FA0C4B0271DULL, 
            0xEC8F041ECE4502F2ULL, 0x349CF16E7FF9EA7EULL, 0x6FEDB12D4E24C293ULL, 0x4582053FF0B8E668ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseFConstants = {
    0xB21FF079674826FEULL,
    0x07AEF20DCF666AD4ULL,
    0x297E59608F70C62CULL,
    0xB21FF079674826FEULL,
    0x07AEF20DCF666AD4ULL,
    0x297E59608F70C62CULL,
    0x79EA9E31ACF0D92FULL,
    0xF7EDD4AA59827095ULL,
    0x49,
    0xC0,
    0xCE,
    0x9B,
    0x3C,
    0xE1,
    0x8E,
    0xA9
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseGSalts = {
    {
        {
            0x07A161F137D24FBCULL, 0x181D70603E45B556ULL, 0xFEACBEECC125709EULL, 0xB2637C49E87434C6ULL, 
            0x9FC8264A4E883A85ULL, 0x5B6DD216ADE84740ULL, 0x0E126A939FCD7820ULL, 0x30B7FC6E0AB30E07ULL, 
            0x5B0058E05769325FULL, 0x28030FD484439C2DULL, 0x7CE133C957B7D364ULL, 0xEF5A3A155554EA21ULL, 
            0x0B46EEBCB03D31C1ULL, 0x62A20708EA34D67FULL, 0x850F5B60AD479B95ULL, 0xC867F1B3743D0BB4ULL, 
            0xD6AA966EF71F3835ULL, 0xC052A82B23C122C6ULL, 0x3B54F9C4BD33D358ULL, 0x0EAFEAB13F6625DCULL, 
            0x733CC4C17917B0BDULL, 0x3E0E2EC7D3207AC7ULL, 0xF1618B3362BA433AULL, 0x0A834DC26763C5ECULL, 
            0xF7135CC1E64A2A97ULL, 0x9100021585C8A6B0ULL, 0xDA37121B66C9A315ULL, 0xD5F699E985C1E711ULL, 
            0xD684C3E2D57093E9ULL, 0x4186E129D324BF5CULL, 0x0D85614DDC5EF80FULL, 0x746EB8BC445BFC44ULL
        },
        {
            0xFC35643B095AD7E4ULL, 0x496CE91D38D10734ULL, 0xAF280A344D83D92CULL, 0xD49415B8794D2FB6ULL, 
            0x8B9FA7B56C6CDD7EULL, 0xE8D29D7BE1724AA5ULL, 0xDFF3487AB4F78DA2ULL, 0x9599021EC0B18FB6ULL, 
            0xE6D982E818AED378ULL, 0x63ABAFDBB5013CB7ULL, 0x782A7F56CFF6C901ULL, 0x0AC21F99D5064B54ULL, 
            0x518D9F50ED8517E9ULL, 0x3B34834D02026101ULL, 0xE75EECB75358507BULL, 0x6EB29751525D78F2ULL, 
            0x690B9EF3B009B7B4ULL, 0xAC72C6D7E29A6DB2ULL, 0x6ACCEA97B18A534DULL, 0x5563890FAFC4D887ULL, 
            0x39DB4B2896D06B2FULL, 0xFF8C4CB4043B5B80ULL, 0x9D195504B763C945ULL, 0x8FB60E1139EE9D37ULL, 
            0x50CE73A7AAD18C7AULL, 0x3933C54D89361DE2ULL, 0xBD03C6C7E12BFC62ULL, 0xEF3B62FDB1134EF5ULL, 
            0x28C73025E54721B5ULL, 0x8C3922711010E81CULL, 0x15D994363090EE05ULL, 0x24450A46743FB25BULL
        },
        {
            0xEDC4DFA5D90CF673ULL, 0x45C44A2438A6CDE7ULL, 0xFA9578E5E04F521BULL, 0x60A2B78ACADFFE91ULL, 
            0xBCBB76D2F771E00AULL, 0x356C3DBCF9DFC700ULL, 0x5A4F17984F675116ULL, 0x12C2C502A9BF0DBFULL, 
            0x0F391D14134114B4ULL, 0xD019409883533FA0ULL, 0x7000ABE02ADD69C5ULL, 0x5700921625BDE88EULL, 
            0x0063805C688ED24AULL, 0x7832BC5B14E82E51ULL, 0x328A13DB2D788DA3ULL, 0x480BA91AE57457C9ULL, 
            0x5A1F82DC0328EF80ULL, 0xC75CAA4DCA9A5F0BULL, 0xC6256D1DE5AAE268ULL, 0x183C861664F9D1D1ULL, 
            0x1100B9CBA0B9013FULL, 0x2EEA99ED0B856E5DULL, 0x399476929E766BF6ULL, 0x8986E181B2451F0FULL, 
            0x564B3C893C0B6759ULL, 0x601FD6A81B469E02ULL, 0x28AD5E497A4A0A12ULL, 0xD5BFFE683B0D4E80ULL, 
            0xAB19C68030F27C2EULL, 0x29412BA1DCEA8FE4ULL, 0x2F7CE19327BBDDF8ULL, 0x29E73C9E86DFB93FULL
        },
        {
            0x3752EFD9D21195E5ULL, 0xF9B269BC55FA15A9ULL, 0x0FDA6BA4C368953AULL, 0x1C843815A699ED28ULL, 
            0xD9CE3780787DCDDEULL, 0xE765692189CC18E7ULL, 0x1342D541525C4CBEULL, 0x31AEEADD62ED605DULL, 
            0xFC212EA8161FAD85ULL, 0xB0571E04729E091EULL, 0x0C8BA52022A1125CULL, 0x99A61BA3F10CAB7AULL, 
            0x1AFF42EE071C3402ULL, 0x5D3A65251A6EB0A1ULL, 0x24241C7581111992ULL, 0x57761295534B3C2FULL, 
            0x3BB897C210B48015ULL, 0x3F3CD45FEBBC4D0CULL, 0x6C40F1972FFEBB6FULL, 0xC93B9E608504E17BULL, 
            0x5FF4B7F8A30A9582ULL, 0x479B50D25A4323F5ULL, 0x0B672E7DB21B4AE4ULL, 0x032B5E0F86B24D24ULL, 
            0x6708094260921EEAULL, 0x12DD53E5692D4AF8ULL, 0x7CCB728153557372ULL, 0x4699BA85C79AA8C7ULL, 
            0x49FCDD68DF8386B5ULL, 0x1C446D369A25EA1CULL, 0x1A9BD9C089A25CDCULL, 0x9AB360AEF5C9A85DULL
        },
        {
            0x76AEB17E2EA48AC6ULL, 0x1244F4B08B5CF450ULL, 0x8D74AE372D12CDA5ULL, 0x7B7C4B468676FC94ULL, 
            0x225E9CA5BD89C2BAULL, 0x29EA0A22BB19ACF7ULL, 0xDF0E6F5C47D05EEEULL, 0xAFC5B73924747E4DULL, 
            0x372F90DEAADA864BULL, 0x5D9030AD38FEBA67ULL, 0x15441FFCD265BAB0ULL, 0x34FB0B5C84AFC800ULL, 
            0x22F065C9B66ADB25ULL, 0x5071CE5014194139ULL, 0x27C4F9616FAEDF37ULL, 0x49FF13011FB1C5F5ULL, 
            0x2FBFD8FAEFDF1DEBULL, 0x8E30C6C0CA249253ULL, 0x74C513381E71EE8EULL, 0x29CBD4290500F3ABULL, 
            0x417D44D8C96720C0ULL, 0x30757798851EDE45ULL, 0x7A36CB2DEE17DDD8ULL, 0x450E0525310AB2B8ULL, 
            0x1471974E15BC526DULL, 0x595230ABB0873738ULL, 0x5EB9B93DB7BDEFEDULL, 0xE2A20AD0E06BD15DULL, 
            0x3EEC5E3EBFBCFDA3ULL, 0x0B51FA695E6A0DABULL, 0xAF82612E96316F8CULL, 0x9E12CC84016248CEULL
        },
        {
            0x30F14BF9F678B55FULL, 0x911B3918F8BCEBE2ULL, 0x5BF7F2B1C9560FFCULL, 0x69C6DE1CD796AD09ULL, 
            0x22ED3E61E2540D66ULL, 0xA73872DD300637A0ULL, 0x8AE4B219E1D6A3BAULL, 0x08B1F66B24A1A544ULL, 
            0x9D134B293C41CE6DULL, 0xDDF007B1A6BE9C60ULL, 0x8A9AD16D28FBF08CULL, 0xD9AAFA8B8CE64682ULL, 
            0xF912CBD71CE06660ULL, 0x0860B528C38AB1D0ULL, 0xAEB5EC05BF76E9D7ULL, 0x5A418DD2EDD6E759ULL, 
            0xD6264A05A4244DC4ULL, 0x19AE7CE1C30E279AULL, 0x69568285C737C9A9ULL, 0xCBC518D82409900EULL, 
            0x749B9A6688C0CD04ULL, 0x59E725C34B2859F3ULL, 0xCD0AC520305AA6EAULL, 0x556BF0FD80B04C0CULL, 
            0x233BC6F7FA413D37ULL, 0x8DE00EC022A7EAD0ULL, 0xAD24D5224F344940ULL, 0x06E57BF63912C19BULL, 
            0xEF62B54CC83E51C4ULL, 0x7E493D497E2AA1F3ULL, 0x59D1681D2316CF49ULL, 0x7F32923D6031596CULL
        }
    },
    {
        {
            0x4D52AA9336131C1EULL, 0x091E04CA5C5FA6D9ULL, 0x89D2324340B50B06ULL, 0x2685870683F44C5BULL, 
            0xEB212E0C2012CDAFULL, 0x92B7ADE881F559A8ULL, 0xFF51A6564D9A61FCULL, 0x02B0BF09BFA9CF7AULL, 
            0xBAA4E265D97DAE8FULL, 0x0D9E4C9065782F48ULL, 0xC5E9C1908FE0F94EULL, 0x63DC9995A0750561ULL, 
            0x552C52414763ED22ULL, 0xE8534F0CA7937E85ULL, 0x2A0219A7C2DE2ACDULL, 0x3AF3668E9ECF70DFULL, 
            0x2F9B18E9380F3094ULL, 0x78AE113F4BBB5809ULL, 0x724D94176D1C7D83ULL, 0xC9B7FF58CC1DDB08ULL, 
            0xF61DB37768B69839ULL, 0x4A0F4A268ECC4A3DULL, 0xE5B8ABEEED4BDF65ULL, 0xF051915A5EF46C09ULL, 
            0x875F6B89A3DA1EF1ULL, 0xA47AF9E4D71FE2E3ULL, 0xBF8A22FB0CC5D718ULL, 0x2D6C64F215FF8C95ULL, 
            0x5F06CE3490B22235ULL, 0x87216E98FC99DA64ULL, 0x344D410B063B0B6CULL, 0xD5BE133C4815440DULL
        },
        {
            0xFD3CA82C99C32876ULL, 0x86154D42A357D25DULL, 0x89E3B0353C34FBC3ULL, 0x552E7F6A71FA957AULL, 
            0xEDE4907696AAE9EEULL, 0xEF6DA2961179D75FULL, 0xAD5886359ECE0189ULL, 0x7BCF103A93B454A0ULL, 
            0x87BC63153770C9C7ULL, 0xF7E211482AFEC57DULL, 0x56EAAB452AE58E46ULL, 0x0DD6FD009DD1E85BULL, 
            0x86613B9DB2F9B976ULL, 0x6FA37FD65B31C13BULL, 0x057420BC7912700EULL, 0xD6EE2249E806BA43ULL, 
            0xD7FF1BEF9C68C54BULL, 0x6C694EDD60FE4584ULL, 0x2DF4DA4461645543ULL, 0xEBC585420D356FB8ULL, 
            0xFF8BD5CF38E38283ULL, 0xAEEADCDD8403AC74ULL, 0x546495870118EFC0ULL, 0x37816FC5E28203A0ULL, 
            0xA7A3FA3A7C9CEF22ULL, 0xFC75DBB63D308193ULL, 0x5542E11439BC7574ULL, 0xE8C01B14CB78E24CULL, 
            0x45F0AE8F90725D23ULL, 0x09167B99750E4E12ULL, 0xEF0DEDBA2CA47247ULL, 0x86B71CC7C38391E9ULL
        },
        {
            0x5885C458E5584E9FULL, 0xF0D125FF7607F947ULL, 0x6A75DB409BEBE375ULL, 0xCA3B47D67C90D6CEULL, 
            0x66D364610402BE1AULL, 0xD626EEB4457891F8ULL, 0xDF6A6F90296D8617ULL, 0x43A0C632CE99954FULL, 
            0x6E2388030B3DBE05ULL, 0x9E7428D432CFB6DDULL, 0xE29CF4F85C3161E7ULL, 0xBE41C22C1ADF30FDULL, 
            0x9198EF247573C3ECULL, 0x75B9AF216DFE5597ULL, 0xCAEBE838C25E6166ULL, 0x8AA9C577DABA9EEFULL, 
            0x691CDED9F03962AAULL, 0x7541C3C99AD6DFCDULL, 0x44653638C5E69392ULL, 0x7AE709C0B609598DULL, 
            0x43367C6611C7B833ULL, 0x201FEB89998F9797ULL, 0x7CCDE79FAE26CFD3ULL, 0x6F466BAC069B7784ULL, 
            0xFF7F77B0E2BC6CF5ULL, 0x729A4DAD9EB05A7DULL, 0xFA56BCFDA7DF4C33ULL, 0xF2127B07C74D068CULL, 
            0xD87E3C164263ABA6ULL, 0x9F7493A0BC75BC09ULL, 0x950899095B3D5613ULL, 0x863D87F027781767ULL
        },
        {
            0xDA9A9006B3D025B8ULL, 0x1D5F901EE60275A6ULL, 0x6F129B92194DB745ULL, 0x703CA73527B5E827ULL, 
            0x8A3EFE65735E9F5DULL, 0x6F43CB0880D03257ULL, 0xA79C25298D742ACCULL, 0xF99E7E44B4ED9FD9ULL, 
            0x2DCD6D644A493987ULL, 0xCE89F821F285BB31ULL, 0x48BAD639A67C2BFEULL, 0x191D2B34EA8172E9ULL, 
            0xD53109856A2405C2ULL, 0xAA061DCF2FD6C618ULL, 0x00988393060EF560ULL, 0xD491584B636FE6EAULL, 
            0x1AE0D897D270070BULL, 0x28C4B0AC98318C9BULL, 0xC301EAFB7200F6B1ULL, 0x4703209FEF8DB144ULL, 
            0x2515B85B386C3885ULL, 0x044B7E22E38E83D4ULL, 0x67EF7BCFD41CCA1CULL, 0xDB7A867281BDF693ULL, 
            0xD3AA64BB25CFB8ACULL, 0xB3C1F8DA75FE0452ULL, 0x9E4A551F636FE4D0ULL, 0x0F514A6318861572ULL, 
            0x82F3D87D949DD8D6ULL, 0x36AAD55BC070894AULL, 0xB979C086668D1152ULL, 0xE1E1E79D59BC699AULL
        },
        {
            0xC315D7E56CDCEB27ULL, 0x3A67925314D9764BULL, 0x82523BB507ED13B9ULL, 0xABDA45862A53DAF5ULL, 
            0xADED6FBCC5FFC2A7ULL, 0x1A30BD0D7A49E710ULL, 0x49C229EAD582E12DULL, 0xCFF710CA4D6EF88DULL, 
            0x1ED553818DE83B4FULL, 0x02670BC253F9D534ULL, 0x5ADB400C784CB15CULL, 0xC65DF97EED93B4BEULL, 
            0x64F159EBADD351F4ULL, 0xEED8150E4E86F48AULL, 0x747C711D63DDFE97ULL, 0x7980173C82CFC90AULL, 
            0xFB87BF3EDBF23D8EULL, 0x7CD09B0AB22AA3B5ULL, 0x28A1B5EE5C36CAF5ULL, 0xDFD15CBC34E1C373ULL, 
            0xDCEEF9AA66364CDEULL, 0xE2DC661925FA5290ULL, 0x9D35369F3930C57BULL, 0x72417AF31A2518F8ULL, 
            0xE9B06E63BED5393FULL, 0xC5F3A898E25D81F7ULL, 0x9CA56F08DF9563C2ULL, 0x9C7BDDA831C4175FULL, 
            0x2F13C462B615AD75ULL, 0xADAE88C0E7B698B7ULL, 0x90B0D77A865870D7ULL, 0xB7DA535FEFC348A4ULL
        },
        {
            0x56294695EF47C18FULL, 0x5123D4148F4120FBULL, 0xCEEA896DFAC0670DULL, 0x70C0E5CC8B839E9FULL, 
            0x315D73BB07F913F0ULL, 0xF440E7C6113895D5ULL, 0x1B4D9551205A3A92ULL, 0x7C96424F68FE1ABEULL, 
            0x3E7FC5EAB57CF3B4ULL, 0x70126B1D066ED3F1ULL, 0x69077951DB3FB92BULL, 0xE05D40601E870FC3ULL, 
            0xC353DFDD38D0A95CULL, 0x700E9574CB9F66F8ULL, 0x55F6E0E636752FE6ULL, 0xD68199BD6418B039ULL, 
            0x84A6BC38BF44BC77ULL, 0x5F099FCBAE71B75CULL, 0x1C0256E824276C84ULL, 0xB7A95D14FB0582F0ULL, 
            0x5447534425398800ULL, 0x398E24DCA18AC150ULL, 0x62B08DFCFC874707ULL, 0xD64520E2DC8493CBULL, 
            0x457B72EF131AA47DULL, 0x2D073FD6B49970CDULL, 0x7EF33C2B041F36E1ULL, 0x90136BD9BE8E76D9ULL, 
            0xAA3E1C6C5E3FCBA7ULL, 0x36B597A1282A5125ULL, 0x87FAFD0994BD5180ULL, 0x8AB5FF2B0DC510C6ULL
        }
    },
    {
        {
            0xA04F8E45AFB3812FULL, 0x5485250765936EF5ULL, 0x5729233CE9D7551FULL, 0x26CD6418CEBA85F0ULL, 
            0x5636EF4C67E65D9CULL, 0x60D7BB4A5CCFE6CAULL, 0xFC4B8635E6664BF3ULL, 0xB3C890978FB44A1CULL, 
            0x266E7EA061885234ULL, 0xBF9F7BD4DB27C346ULL, 0x03B177BCDE01E064ULL, 0x054D2650004C3A21ULL, 
            0x5D45DCF237319E99ULL, 0x62DB26971A3434BCULL, 0x05C9463009930253ULL, 0x7F04EFEE3A36BF43ULL, 
            0xE57A6AB1EE97E4ADULL, 0x8443DF07FA0533C2ULL, 0xD363F588F76E63D9ULL, 0x8B42032ADED134C1ULL, 
            0x7B3F1E555450645BULL, 0xE1AAF45AF9A254F9ULL, 0x44BCE2358251C27DULL, 0x04A88D7523500BA1ULL, 
            0x4A63D94B9B6A203CULL, 0xCDC0DCDCAF579488ULL, 0xDE496782797D74C7ULL, 0xE595BB260DD341BBULL, 
            0x5DCFBA0C3AFFCF99ULL, 0x3A81B86A8513C8E1ULL, 0xB630C1EF1687A07EULL, 0x9A0551D526D4AE08ULL
        },
        {
            0x9B44A516E8C70798ULL, 0xD5D87C35782F0605ULL, 0x86412311C91C2DFEULL, 0xC754651685FCA429ULL, 
            0x309E72C864FE5BB0ULL, 0x7357D13D19B3C033ULL, 0xB5D04D1E28207ECCULL, 0xDC9F575C7CD6B403ULL, 
            0xA36D9CC7B6C2F337ULL, 0xBE42104539E43695ULL, 0x263FA08E4B7268F5ULL, 0x6EDBE7A476D0A61DULL, 
            0xABF5556C57C1F82CULL, 0x7409F361D0D0E3ACULL, 0xA12ECFA12172189AULL, 0x3FFF07AF21661C14ULL, 
            0x1838FA7B1FA995EAULL, 0x070993E4EC6AFC25ULL, 0x824CBEA6C0C37179ULL, 0x69CC67804BE4735EULL, 
            0x8E88415DF09DB506ULL, 0xD1799D1FE576A78CULL, 0x86A6D858D3AEAECCULL, 0x9E21B2BDDDF17183ULL, 
            0xB465CECA2AE84703ULL, 0x2D9E0242B9CA466BULL, 0xA6B45EB3F168E590ULL, 0x7D25332F6C99E269ULL, 
            0x221CEFFE96B23049ULL, 0x0021C2C6A0971F1EULL, 0xB5399185D432B238ULL, 0x03B5312B4C3FDE49ULL
        },
        {
            0x28827AC466684A02ULL, 0xEE045002D05E3CD0ULL, 0x9E4DE6F63F618A25ULL, 0xB00278DB1289D683ULL, 
            0xEF2136000C5223D4ULL, 0x4A4CEF2A0CE48008ULL, 0xA6E27ACC9234C19FULL, 0x184163846B164852ULL, 
            0xF5A8E24B54AFCC4AULL, 0x484D2918656481C0ULL, 0x027C974519582C40ULL, 0xB0DFB88F275F456EULL, 
            0xF8EF54EE3767A218ULL, 0x1A4D45BE97FC66C4ULL, 0xC49872FFDB051BF0ULL, 0x19C47EE57FD0EC43ULL, 
            0x7448E87E50B69429ULL, 0x9D9CCFD8A902DD12ULL, 0xEA6D3E90BE0F37B5ULL, 0x63277EC95AF4D74AULL, 
            0x26C9BFF8E159602FULL, 0x5F098CC587E299FAULL, 0xFD9D0F95167CFDEEULL, 0x811F5B824C948A0AULL, 
            0xC7745A9EB1C31963ULL, 0xDF201AC1B17F441BULL, 0x1A79616CADAB578BULL, 0x2C378E2CF0EBE217ULL, 
            0x0B3B9D47CAD0594FULL, 0x05EB5320A8529106ULL, 0x7E6177FF086F3F68ULL, 0xD779CD2F7B7B58A6ULL
        },
        {
            0xA00C0D308EB9981DULL, 0x434F715DAC57FC6BULL, 0x27E42A759142BCDAULL, 0x2AB87C86D94DA005ULL, 
            0x499DF82622EB55E7ULL, 0x0A18CEDFC6550D06ULL, 0x9EA167BF9D1FF67CULL, 0xB68963C7E52A4A56ULL, 
            0x63897CE89EDFC9EAULL, 0x8B9C3A89F474F52AULL, 0x3C280E2416C6EC1EULL, 0x60A002E0A74E00C2ULL, 
            0x6491ABB110951EC9ULL, 0x2F279119BCD744F5ULL, 0xA9814504CE6CF648ULL, 0xDA78C4093E337639ULL, 
            0xD0B496E73D53B3B1ULL, 0xC5CBDA72733747E1ULL, 0x09AF8575CF69CDB6ULL, 0x0942F1A74B61A324ULL, 
            0x2540D1E3FBC2CF11ULL, 0xF37D2C8538FA52E1ULL, 0x29EAEC65AB519452ULL, 0xBAB0F5481028982BULL, 
            0xFC1B07A72CEF62AEULL, 0x29F53C1C516B441FULL, 0x123500F980554947ULL, 0x3F6E4D236E5E715FULL, 
            0x5FD0CFF9379AC96DULL, 0xC55399B12395331CULL, 0xDF52F6F22AD5F53CULL, 0x614D436B727791B5ULL
        },
        {
            0xC0FB619DF50963B7ULL, 0xE7E857B8E646952AULL, 0x5A807CA98167BEE0ULL, 0x99283BEBCE6F905DULL, 
            0xFA2217A2A1E97117ULL, 0x53DAE57E3C427425ULL, 0x51396A6FE89E822FULL, 0xD3F2F88C8895CD2EULL, 
            0xE9ACB863B68CA1DFULL, 0xE21825A065BFE204ULL, 0x540A06DCFAF9C835ULL, 0xA6D7E2A78B13ECCBULL, 
            0xD57F204D2469A1ABULL, 0x9E2859F6F5D1C1D0ULL, 0x4AAF52AA7DCBA498ULL, 0xE607CBF2B787D280ULL, 
            0x86408A107AE150E1ULL, 0xE6C2D9DA445A30A4ULL, 0xC3B7EB6C2CB4AA2FULL, 0x0ECBE65FA9CEDB09ULL, 
            0x115C51D2440D88A9ULL, 0x212866A1AECD9B9AULL, 0x711373CE9680920AULL, 0x0B5101AB5943FA96ULL, 
            0xFCD64DFE261A51E0ULL, 0x9247750FC132A798ULL, 0xB65AC07F1E3217BBULL, 0xDF8877B92BFBD947ULL, 
            0x8BDC3D206709B3A1ULL, 0x8A0FB41F6692C0B1ULL, 0xC2DDCC98D67F207DULL, 0x0E63FB320EC2C806ULL
        },
        {
            0xABF2B23AE4A9DB6FULL, 0x4946D7AD3EA69337ULL, 0xE6DF4E5B453D2342ULL, 0x2D27649843D6E767ULL, 
            0xA4C8328A8C21B6B0ULL, 0x3C592933C716601DULL, 0x3B7E79B2C4AE30DDULL, 0x9C6511C99DCCACD5ULL, 
            0xBD3CF79CB40CBF31ULL, 0x8BB0915BD669321BULL, 0xCF2D7B53A10D80A0ULL, 0xD3BA7C020F6654C4ULL, 
            0x413AEC90D2A4AE27ULL, 0x81CE300AECF32550ULL, 0xC4836E05424C7CCBULL, 0xE4EB8265C4687CDAULL, 
            0x9D7024AFBD73D94FULL, 0x38033A7C8235FA5CULL, 0x19FF6AA89F647DE2ULL, 0xA757604206982D5AULL, 
            0xB845ADA45B5DA0E4ULL, 0x66178C92BCAE2988ULL, 0x879B317EF56D473EULL, 0x6C28FBE37D674C26ULL, 
            0x56272636DB1D9DD0ULL, 0xC192378F87BC3CA4ULL, 0x1D2367F4CF2FD6A0ULL, 0x67D95EA15E6F534EULL, 
            0x76518FFEBE3239ADULL, 0x0A8E8581EDCCB102ULL, 0x669BF5B213588C6CULL, 0xBB8767619AE8CC6CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseGConstants = {
    0xB04B11337967C79BULL,
    0x76630CCEA735CD58ULL,
    0x8370447DB592002EULL,
    0xB04B11337967C79BULL,
    0x76630CCEA735CD58ULL,
    0x8370447DB592002EULL,
    0x72CD574AB8EAA945ULL,
    0x4AE977F20A1D5CB5ULL,
    0x51,
    0xB6,
    0x17,
    0x1E,
    0xB5,
    0x7E,
    0x2F,
    0x04
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseHSalts = {
    {
        {
            0x7766CB3B20F39849ULL, 0xEB435558E41AFA86ULL, 0x3056A459376AFD47ULL, 0x54C9EC8AAE8EEACBULL, 
            0x45F74321468FEFB6ULL, 0x9E92F4B49F8F6C77ULL, 0x6AE211E791B0CD2FULL, 0xC83FAE0C5CBC2B9CULL, 
            0xF7E4DE91B486CC0EULL, 0x0F8DD2157DF71480ULL, 0xB5F795D12111FB00ULL, 0xEC8DEF031E8BAB7DULL, 
            0xD81B72AA19E6A663ULL, 0x1B8722CC73888656ULL, 0x7CB89CE2B5E71493ULL, 0x241ADD049A2DAEC3ULL, 
            0x30B9B63332E5E037ULL, 0x8D60A29490D590E7ULL, 0x5DE969547267B1B1ULL, 0xE203CE3C707F8863ULL, 
            0xB8EC0D7FDBF81D34ULL, 0x1156F680D05ABC1EULL, 0x5E5CB3839AF83B0FULL, 0xEC071F40A8993D7CULL, 
            0xD021C8FC34308F42ULL, 0x3513791FA61D9BF1ULL, 0xC44ECB4DB1B95EC0ULL, 0x2A736DEBE360AF20ULL, 
            0xA44DC56632EF26D3ULL, 0x54E507128594A0C2ULL, 0xF12AF741C3DD0597ULL, 0x2FD074D7284B36B8ULL
        },
        {
            0xAD157DEF71A9D3D3ULL, 0xB84E978459144996ULL, 0x4E0910E50C0FD93FULL, 0xDB609243DB91B0F0ULL, 
            0x12310B1E404C7E05ULL, 0x8DEB90B9F1839EE0ULL, 0xE5D67DB7BB35D4CAULL, 0x607213CBE09C0242ULL, 
            0xBA0772D7AE48C570ULL, 0x4BBA62673F048BF5ULL, 0x0AC2213D5BF4DC7CULL, 0x1E7E71B821EB4020ULL, 
            0x8729F353635A65D6ULL, 0x56D26991BC9FF195ULL, 0xC794C8BEBFBF97A2ULL, 0x2B5323FDF4F7B39DULL, 
            0x8F5FB091A494B3EAULL, 0xB3B0DC1C8F00965FULL, 0xE593403A444D320FULL, 0x88ABD0ED17D916E1ULL, 
            0xE949FAF956F8E183ULL, 0x41B5357184862419ULL, 0x3DCBCD96C8556D9DULL, 0xA52F04558F1A8007ULL, 
            0x15CBAFF3D4E68A42ULL, 0x8A739AF6B8C142D7ULL, 0xED78BCF58B27D71EULL, 0x7EE4E239CEA08DA6ULL, 
            0x702356A7EFD0A1DAULL, 0x4D9E7316CFF0ADADULL, 0xB2D975A4913C54B9ULL, 0x1927AB2A86644554ULL
        },
        {
            0xE43F21B509F08C54ULL, 0x97BDDC687EA67D27ULL, 0xD393D1EC608D7383ULL, 0xEDE39E1CEF41A934ULL, 
            0x014522198EB521BBULL, 0x6E624F78342E44BAULL, 0x357E9C72B00BD7EBULL, 0x4C712235661B1060ULL, 
            0x8CDFB3F3B0DB8D0AULL, 0x2054A9D0C1160D97ULL, 0xAAFB82252B034FE1ULL, 0x739BF2B828DB75A7ULL, 
            0x2C4F63DA2420D6A6ULL, 0x972230CBE7BE5150ULL, 0x576BD5B72D11F874ULL, 0x6F34C0CB3F9457E1ULL, 
            0x130131D40BFE3E8FULL, 0x56EC902614D01C2DULL, 0xB31B229BF577FBDEULL, 0xC34619E9D89FCCA8ULL, 
            0xBA9F5478ED1C5CAAULL, 0xC706D6F388B7EEE8ULL, 0xD8D5F8D9BFD86CBCULL, 0xF7F9D2EA2C2F3C7BULL, 
            0x4CF8A3E75ECBF6FCULL, 0xE5D5A9F15CFB574FULL, 0x6F8B7A734ACE6EC2ULL, 0xFB9CD895266B3BE3ULL, 
            0x9BE9537117F42440ULL, 0xAD794FB96515F3D1ULL, 0x38E696C129CDF098ULL, 0x5D3547A542CA14F1ULL
        },
        {
            0xDFEAA814BA58F7B4ULL, 0x6D49A575369C8982ULL, 0xFBFCBFF0D813573BULL, 0x04D244CA5B501108ULL, 
            0xCC44F85AAB35F58CULL, 0x26F37A388060588DULL, 0x9BC54F88111DBE5DULL, 0x0BB35EB02ABE943EULL, 
            0x952C658710614731ULL, 0x880DA2B4EB3DE4F4ULL, 0x33DC17556F64087AULL, 0x1E934CD86F58421CULL, 
            0x449197BFACB207EBULL, 0x268AB39789FF591CULL, 0x865F15CB3490848BULL, 0xFB8505B83F049D92ULL, 
            0x4CF203D29A7FE30DULL, 0x4DEB439E1980A199ULL, 0x48556F48F13900E4ULL, 0x1AF48C897487A091ULL, 
            0x268AF82BCB490A4EULL, 0x68A78B83C43D8A4BULL, 0x9CC43D8C6C4215E2ULL, 0xC5056AE907575EF5ULL, 
            0xF274E0710FCF11A3ULL, 0x9A9FBEBCCEB31454ULL, 0xEB20A64611FF67B8ULL, 0x3F046019A7EF942FULL, 
            0xECF4991D5F8ED88EULL, 0x6D57329CE32C497EULL, 0x3DDBBD0225E4E065ULL, 0x6209916A0A959703ULL
        },
        {
            0xB9798F19D41E945FULL, 0x2B2C7D78C582A8BFULL, 0x6CA12DD82C839CCFULL, 0x2BEDE1871CD0A6BCULL, 
            0xF070DF2E89F8C3E6ULL, 0xE829D22B5ACFEFEAULL, 0xAF040545A1DA2414ULL, 0x11996DE581542004ULL, 
            0x57751695912F1818ULL, 0x1E8CF4F0A3B0B80AULL, 0xA1C170D66D32BD24ULL, 0xE7AEE35E35DE73C9ULL, 
            0xD61F590C493DC000ULL, 0x023F682A10847B27ULL, 0xCEA8E78027310D5FULL, 0xA2079552C8BEF28CULL, 
            0x5B2CF61879FA1559ULL, 0xBC9CA214A89D8C31ULL, 0x38DB45ADAAA8F033ULL, 0x0F9D1F3539912EE6ULL, 
            0x03DA145B21FDCC09ULL, 0x913773AEC02CA36CULL, 0xB91167FD0F6064D5ULL, 0xB9D96EE362BE4ADFULL, 
            0xF65852F83782F29BULL, 0xBC919172FF9A6B54ULL, 0x4E1ADA3B9CBAA4C5ULL, 0x26A84A1B1ABC07E5ULL, 
            0xC01B06DFC86BD5D4ULL, 0xF5517F334233CFBDULL, 0x58F6107143CE2B29ULL, 0x2109F3A68B6B39C0ULL
        },
        {
            0x4BE277236408E765ULL, 0x6E9B16E42F13E843ULL, 0x6D09FDAF78028B37ULL, 0xCD05FA603CC5D5CEULL, 
            0x9C41E540AD3D5EECULL, 0x208D0A093215F856ULL, 0xC563BA5A89447FF5ULL, 0x2136747FFD056497ULL, 
            0x9B662ABA9D8FC4D6ULL, 0x06817D99C245474CULL, 0xF756F028FFE12155ULL, 0xD935FD3705473FDCULL, 
            0x6AF90930394D32D9ULL, 0x8358720BE03853B2ULL, 0x73FB966807DA721DULL, 0x6C64180DD69B3984ULL, 
            0x9AAEC30A7A618466ULL, 0x51E3BBF2520D2A7BULL, 0x6E70969807332D7BULL, 0x96E7A4349802F5D4ULL, 
            0x954C4ECC3D078F49ULL, 0x4D945BAE623251FFULL, 0xAE1798CD01176F38ULL, 0xCB46B25B4100A578ULL, 
            0xF1A45F607D069D69ULL, 0xE757D78B4E77046FULL, 0xF8396FD66B426E7CULL, 0xDD3F71EB19F095ECULL, 
            0xE2B8993947621515ULL, 0xED613C387003C301ULL, 0x9950B68C38B7157BULL, 0xBB75006EE7452694ULL
        }
    },
    {
        {
            0x58F1CEA60C84313EULL, 0xD4E070BED80DB9D9ULL, 0x67E64DEBD039BD3CULL, 0x5BD7800F9B8844A0ULL, 
            0x87044FCC7019010BULL, 0x3C01DDC4306AF2F3ULL, 0x57CD4D0183267AAEULL, 0xA8D44F1282A478A9ULL, 
            0xABC8FFE2BF5DFA82ULL, 0x385831266EB462F5ULL, 0x90B4F36920E6C082ULL, 0xE3509829779FA8D4ULL, 
            0xCD31531951A87FB1ULL, 0x68B6292BC88ECA90ULL, 0x26BDCE7BDE204FE7ULL, 0xCDCB7F0FF3F7D5C9ULL, 
            0x1326EE06514EE890ULL, 0x4C074962C3BB82F1ULL, 0xB566C0C1BC9A18CFULL, 0x43974EBC6795D6D9ULL, 
            0x726B6EF7D46470A7ULL, 0xD319F9C2FAEF2370ULL, 0x2C8EB4FB7FAF1354ULL, 0x4B9ADBE1730201D7ULL, 
            0x53717BFD9F0EA7D3ULL, 0x89DCC620CC297429ULL, 0x57CF8F68A781D617ULL, 0xBAE8E94DF273EC58ULL, 
            0xB86FEC79E9861156ULL, 0xDD7321DCA6A7D04DULL, 0x96DAFFBE204B4D81ULL, 0xF0CA5FE80D74EBABULL
        },
        {
            0xAFDAABDE628C5B28ULL, 0x1CA3DEF379D3B6A6ULL, 0x26D19D34BE249059ULL, 0xD6FCA34818A2C6CAULL, 
            0x0B2E353EB87BFA33ULL, 0x494D79054035C19AULL, 0x96D3951A9DBB322FULL, 0xF5B52EAFD07A2780ULL, 
            0xF18C95599AD1D520ULL, 0x9CF38C952112B951ULL, 0xBCA30E23BAABCA64ULL, 0xEC20CFEE4ACFFA8EULL, 
            0x5A8D19500669910EULL, 0xEB42C206D2E1DB18ULL, 0x2A0E19DA37142887ULL, 0x0AE244F55D1F1325ULL, 
            0x45A21BAFC0E0E224ULL, 0x514023E762CCE815ULL, 0x7E7401C2CD49AC44ULL, 0xDD27F7D71194B641ULL, 
            0x1C8FD4DEEC3B0C8AULL, 0xA92C08BB0A8E2B19ULL, 0xA4307B6E8560B5C1ULL, 0x98A81245D27989C1ULL, 
            0xB6BD20EDBAB7E4A3ULL, 0x2018693674852AD3ULL, 0x17A85AA210040E57ULL, 0xDE922ABF1A3C36C4ULL, 
            0xD55B15CD99EB7E22ULL, 0x9F45FEDFB23F64C6ULL, 0x5BB104E4576B742FULL, 0x0112FCA053CC16D6ULL
        },
        {
            0x356A74FCDFB5FE10ULL, 0xB75B6FA135802474ULL, 0x7553B0D392A125A6ULL, 0x5C473C9BB5FD1645ULL, 
            0x586FB914686A37B8ULL, 0x5C3446CC23265473ULL, 0xE4230562E0F954ABULL, 0x6B0D839BFBECCA7BULL, 
            0x846A765F62686164ULL, 0x62728235269931F1ULL, 0x0AF7679283A91F0FULL, 0x17E959196FA83F25ULL, 
            0xCFAE7FF8267F5DD8ULL, 0x5A35DECAAF2A5EB7ULL, 0xD8B1C014AD98D5F9ULL, 0x43889CE253C8A1EFULL, 
            0x4E973C8761A943EFULL, 0xF2C15C46473F6AA0ULL, 0x18801D0CE6EDAD00ULL, 0x35E26B389F6FFBA6ULL, 
            0x19CEBE2BBF5FF070ULL, 0xEAC48E8847B544D7ULL, 0x6450732DF1E629A5ULL, 0xB006B1F70EA96A00ULL, 
            0x270A033A050FC4EFULL, 0xCB2FDE4106276290ULL, 0xD852A157D57AD776ULL, 0x7F306522B5871F9FULL, 
            0x92AA66F733F04B9EULL, 0x5F608B5409AE90AAULL, 0x6A0C45847A4568CCULL, 0xC3ED4D4D24913B3CULL
        },
        {
            0x6DF2A72E7C37DBEBULL, 0xCDE54E78C3705063ULL, 0x2E96CE581C08BD9FULL, 0x277B8EFFEA8DBDECULL, 
            0x20C0076D348C9527ULL, 0x2AD9E612F992DE2CULL, 0x75BE57FA6980005EULL, 0x66441AAFFBE70836ULL, 
            0x725840E0C0C231B9ULL, 0x751E9CB5EE032E72ULL, 0x4D0ABC5C94265A62ULL, 0xFE1689C1A000F317ULL, 
            0x407D51CD0F9CABE7ULL, 0x4F2CD4DD5D85BA95ULL, 0x5192575E39CE86DFULL, 0x9BE33AED9289F3B2ULL, 
            0xD962F4802D3E106BULL, 0x352992B4CE76E59FULL, 0xE2B77F65B8ABE19AULL, 0xECEB7E57E0071960ULL, 
            0xF6938C594042435FULL, 0x993E4AB015ED4322ULL, 0x29D0ABFA408F00E2ULL, 0x1AA0A909A67A907BULL, 
            0xC6F2857B240ABCFAULL, 0x80278E3AAC116859ULL, 0x47A1088ED4134470ULL, 0xC7F009564C9B6448ULL, 
            0x7DCCB35794506D10ULL, 0x8CE09CEC1418964BULL, 0x1F97AD9A7FEC6D56ULL, 0x349B56DA91CD90E9ULL
        },
        {
            0xDDA6A8585F4C1717ULL, 0x58549A4DF3779856ULL, 0x75E903D9645BC800ULL, 0x557662FCFD10459DULL, 
            0xF3CABF4993F49C1DULL, 0x0A8385A470A04473ULL, 0x978DBEC7B7D2B143ULL, 0xF4FBDE5BCA0370E3ULL, 
            0x5804C018F36E3965ULL, 0x7396393672EE7C28ULL, 0xFEE91A98117DE847ULL, 0x1F2A2954E619C341ULL, 
            0x12524B2BD7AD3371ULL, 0xABFA1F6BA659A8F4ULL, 0x97CC443A8E28AD36ULL, 0xD6792B4E93D657F8ULL, 
            0xA7BE83B5BEF1A636ULL, 0xDAB0BBA49C3B59DFULL, 0xE198BFB6933A3B2AULL, 0xE7690C3E10D0DB73ULL, 
            0x4A3318EDBA495E69ULL, 0x86B1529D105B91ECULL, 0xD442A7B877949853ULL, 0x78FAE47F8D01BCA9ULL, 
            0xC9409DC901CAE142ULL, 0x6E270043F4952F00ULL, 0x992D70222B656725ULL, 0x15C29131C731C8E3ULL, 
            0xF7CACFCF15B54D17ULL, 0xEF243FB39B3895E4ULL, 0xF9F8C82479AE8969ULL, 0xC8BBBA23E9344CFFULL
        },
        {
            0x85D9FF2A68C030E6ULL, 0x774AEF2D773E15F4ULL, 0xE53C3A6E43BB887DULL, 0xAF27476F138F1ECCULL, 
            0xF764D918BF8DD815ULL, 0x56A69780E341D6D7ULL, 0xEDBEBF53623063DAULL, 0x08C130A9DB07E63AULL, 
            0xB60FF202BE14CE0CULL, 0x05280087E91ECC00ULL, 0x3497AB6308812F97ULL, 0x1331BD817E0A0748ULL, 
            0x94589CC2746D0502ULL, 0xCAC91AE5C5BBD278ULL, 0x665B83FED066CC12ULL, 0x474E7110CC45551AULL, 
            0x78F08385F268E749ULL, 0xDE6FED310CF5661EULL, 0xF098D8E23AADA972ULL, 0xB4E7202FBA45BAE8ULL, 
            0xC23907B131EC2EB1ULL, 0x6FDB2D2A0E12A3FAULL, 0xB0E5EA092271FC5FULL, 0xDBABC7D956A7C1B8ULL, 
            0xF822A9A2A401AE77ULL, 0xA3D2EF5E57B72A53ULL, 0x5818E754C45A2DB1ULL, 0x86B90BB281215112ULL, 
            0xA7C9955C11B09761ULL, 0xD92F53388A5BBBCFULL, 0x2909FD085D9FCCB1ULL, 0xA26EA811774548EAULL
        }
    },
    {
        {
            0xBB6BE8917215FEE7ULL, 0x0B4CFC0BF55FA009ULL, 0x684B28A511893796ULL, 0x04974F4AEC00639BULL, 
            0x73BE866BEFBB7606ULL, 0x91E3A4E255908870ULL, 0xB5DE18FCB542E026ULL, 0xC99E2CF8A32EC632ULL, 
            0x4B28269D90C34396ULL, 0x15FB7643A95E97E8ULL, 0xC8F4CAB7EB6885DCULL, 0xE83D204BF2490304ULL, 
            0x8BA8DDB2EAA3971EULL, 0x0D5662FEBEC36D1AULL, 0x97776D8E731E68CBULL, 0xF6C1C86299B57E6AULL, 
            0x53D8E2D551AB05B0ULL, 0x4EFC4A1D1E188820ULL, 0x0AE4FFD0BD9B559AULL, 0xCFD34125E98678CAULL, 
            0xFD6B4178F6B05C9DULL, 0x9A299BE92CF72576ULL, 0xDA7A27333C41A505ULL, 0xB87B2A1CCDD0B987ULL, 
            0x2F8126E3E8644185ULL, 0x8F0C33A16468D347ULL, 0x2547CC47EC2C0025ULL, 0xB731862F0D413B67ULL, 
            0xF0B60B93F7FD9897ULL, 0xDB77289246D54B9CULL, 0x356E5F3F7D5E60DCULL, 0x418045DBDADB8B44ULL
        },
        {
            0xC422C847F11FA14EULL, 0x572A14C65AFB6D50ULL, 0x5002BD01958E7A2DULL, 0x2D7071D7DB4173FCULL, 
            0x36A674DBC24177EAULL, 0xBA0D85F6D39527E8ULL, 0xA03BD35F3FA14CACULL, 0x13F1C92C1DB915FFULL, 
            0x80072309BBFB22A9ULL, 0xF11243F2A5883AD2ULL, 0x72B1EFB358E55489ULL, 0x46658F4998CB0130ULL, 
            0xD17666888DB1A379ULL, 0x784DAF4223FF15D1ULL, 0x396D79F7EDD58319ULL, 0x585D53CF00046037ULL, 
            0x9CCDBA02A7F87FEDULL, 0x39A1134CD45DB288ULL, 0xBF5A1F89C861EB80ULL, 0xCE86889DD1FA6232ULL, 
            0xCC8767934040E831ULL, 0x4FB350F9CC9290FCULL, 0xE13A6EFCF3735C04ULL, 0x9A18B057CD96B1EDULL, 
            0xD3507E3091300996ULL, 0x55F11D358172CF6CULL, 0xE7D45FF2A2FED865ULL, 0x93A999C7F392FC0BULL, 
            0x55D6143BD63F22EBULL, 0x2F8C17A5B7B30106ULL, 0x20138E92D01FD42FULL, 0x416786633C322676ULL
        },
        {
            0xB40CC79FC766BCDBULL, 0x584425C74FFE3193ULL, 0x25DA4B4260FCDF47ULL, 0x950D20AAC23C72C7ULL, 
            0xA604E9DECA0CF47DULL, 0xF0142D1C873CE2F3ULL, 0x1314EA1409287FA0ULL, 0xE9606F9DAA403A16ULL, 
            0x3C687A9A9AC5DE29ULL, 0x82AD06793B7BD375ULL, 0x6913E0020E8B3CD3ULL, 0xD848561681DFBE03ULL, 
            0x2A01B8DA521C1311ULL, 0x70FE6B6644733D1FULL, 0x8DFFEEFDEA4FBA9FULL, 0xB9FBF9DAFEBB40FCULL, 
            0x621E793DE3477C1AULL, 0x8CCFF5411B52975EULL, 0xEE8A961098A4C127ULL, 0xAFB36F7C52AC266FULL, 
            0xD441A5B6E37FC833ULL, 0x7E742BE5C12EAF14ULL, 0xB0C1176E2D48F8F9ULL, 0xD69A6ADB37498E28ULL, 
            0x5D0454B560205B9FULL, 0xEEFB60AD8031FDEDULL, 0xAD874D63417E3962ULL, 0xA34425A4EF874B95ULL, 
            0x65EF5AF9C1AB01C0ULL, 0x7ADDD836106751C4ULL, 0x973B63FB9A85314BULL, 0xE15C7ED8EEF7EA11ULL
        },
        {
            0x656796FAE0440557ULL, 0xEF24B711309BE953ULL, 0xC49C6A85761C9EACULL, 0xEDAB96B238A90313ULL, 
            0xD78C1D365BA917B8ULL, 0x4C0CD09EB4696A27ULL, 0xCF97A7F535A4360AULL, 0x64401A6FB5C87892ULL, 
            0x750BD9B277CD37FEULL, 0x22B89B0DCBFF21E5ULL, 0xC630BA296735384CULL, 0x1227E4C102CA7ADDULL, 
            0xD6EE7922A12DC5C6ULL, 0xADD569A129BB9C87ULL, 0x3B89D9BFC78ECBC3ULL, 0x441D06699F279B62ULL, 
            0x6F2B01BBBFB4DC65ULL, 0x757E717985FE0ABDULL, 0x15E7288FD9538F19ULL, 0x4C2E920880EB9C26ULL, 
            0xF75EDF80526D2B3BULL, 0xCC7B733718CE20C3ULL, 0xD67BC8606A3926E4ULL, 0xD4F537D57031A906ULL, 
            0x14941E672FD4F8DDULL, 0x9BDF188095675868ULL, 0xD6ECFC0831D8FAB7ULL, 0x7D3103BB3B1AC011ULL, 
            0x4F3CB5B593C70DA1ULL, 0xAD3A7FDC540A3269ULL, 0x813E3EAEA250972EULL, 0xC0C0502A8F02AB6EULL
        },
        {
            0xDD795C94970516E0ULL, 0xA9631772584D6E12ULL, 0xE94282570D881984ULL, 0x3D83DDAB73B97C63ULL, 
            0x8004927DE9524C64ULL, 0x673E88CBA28EBBF8ULL, 0xA9DB706A37475209ULL, 0xC00A045CFAC61F66ULL, 
            0x069E159C61EECD16ULL, 0x5129BB2AC7C52299ULL, 0xA0350EBD592D5D38ULL, 0xDEB40D956E9D9DCEULL, 
            0x04847B41A73759D1ULL, 0xFC76B0B5A326F493ULL, 0x8DA64865A67B33DAULL, 0xEB1C6317FBAC7AEDULL, 
            0x1E32A979019A7B59ULL, 0x6F7FF98DBC1DE07DULL, 0x251439F6CFC3E0F2ULL, 0xD76015D6E589D039ULL, 
            0x5D5BDA8414C7519DULL, 0xC00EB4F6CD22187CULL, 0x7BC292B665233E50ULL, 0xFD6529F0C50E8F68ULL, 
            0x1AEF14D07324F1CBULL, 0xA6AE35108CDB29DEULL, 0xB3826EAD170DBB8DULL, 0x47E44594630067B5ULL, 
            0xDFC6E78BF6630A54ULL, 0x02204A915EFA2475ULL, 0xE7466E87577CB748ULL, 0x9F37F0BCBDBDE218ULL
        },
        {
            0x8B16AF29FEC70EEDULL, 0x67A314FA93204D1BULL, 0x521BF161CC5509E0ULL, 0xDD053E756E8288FEULL, 
            0x416DB37E3C1145FBULL, 0xD0054D7D5B88E1E2ULL, 0x8DB439E860966308ULL, 0xB1E34A053642E723ULL, 
            0xAFE1709F7B493874ULL, 0xC450F0E5D82C1A5BULL, 0xD5CFD2612BC55779ULL, 0xA568FFB4624D2B54ULL, 
            0xF51207645D1CE5A1ULL, 0x0098E95CD09E6C59ULL, 0x257D13C8DE877723ULL, 0x895D8E818AB75F44ULL, 
            0xC6A3A840871D5E86ULL, 0xF39DC37A9F76DE74ULL, 0x4591F18DCB95F2F1ULL, 0xA778A56FFBA1FFA6ULL, 
            0xA0A0969834E60DA1ULL, 0x6D41F95D78F71608ULL, 0x36AE6F50CD102E4FULL, 0x0E4B858A7F3A3BF5ULL, 
            0x71417A1F170B257BULL, 0xD9A0F5A334F2EBF0ULL, 0x27F5DC1584BE672DULL, 0x02FB8EE224563B75ULL, 
            0xABF7A517D6779CB0ULL, 0x6DA92C8FC32E9C22ULL, 0x178D8CEDD1A5D86DULL, 0xFDFE321E89DF4F16ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseHConstants = {
    0x48BCB101DE0BEB0BULL,
    0xA4FA7143571D4535ULL,
    0x330319BE599F6071ULL,
    0x48BCB101DE0BEB0BULL,
    0xA4FA7143571D4535ULL,
    0x330319BE599F6071ULL,
    0x8FD8807CD78EA826ULL,
    0x368E31D82C2229AAULL,
    0x08,
    0x7D,
    0xDD,
    0x43,
    0x81,
    0x52,
    0xFB,
    0x92
};

