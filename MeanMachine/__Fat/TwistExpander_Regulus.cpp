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
    std::uint64_t aPrevious = 0x9E8661E969D0D0FCULL; std::uint64_t aIngress = 0xF57D5F8F049F8EE6ULL; std::uint64_t aCarry = 0x992BA0F90A2B9314ULL;

    std::uint64_t aWandererA = 0xCDCCD2AA8856FE58ULL; std::uint64_t aWandererB = 0x986BE80E5E0A8308ULL; std::uint64_t aWandererC = 0xE6B10B739AD0CD73ULL; std::uint64_t aWandererD = 0x9F960E94BD707E5CULL;
    std::uint64_t aWandererE = 0x83E58AFBA2EB6D72ULL; std::uint64_t aWandererF = 0xF3803E1305B90F44ULL; std::uint64_t aWandererG = 0xA0C5C56A614645A9ULL; std::uint64_t aWandererH = 0x887533A5DCC83684ULL;
    std::uint64_t aWandererI = 0xA338153BC9D733ECULL; std::uint64_t aWandererJ = 0xD9E1ADC087A471FFULL; std::uint64_t aWandererK = 0xD5171120928CA37BULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16242433297767716434U;
        aCarry = 12662272494401095176U;
        aWandererA = 17186278157653165772U;
        aWandererB = 18408290556858093623U;
        aWandererC = 12335093104510066950U;
        aWandererD = 16801663889246089514U;
        aWandererE = 15937656346185892245U;
        aWandererF = 9446337049854614263U;
        aWandererG = 9278452735781361995U;
        aWandererH = 18082246496527180089U;
        aWandererI = 10530656089048295108U;
        aWandererJ = 17559366887177603315U;
        aWandererK = 17357785769850913270U;
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
    std::uint64_t aPrevious = 0xB0C000E410171B58ULL; std::uint64_t aIngress = 0xE2F05B0D78649F30ULL; std::uint64_t aCarry = 0xF4F7D3E4A05016A9ULL;

    std::uint64_t aWandererA = 0xD982BF4DE2F1C6CCULL; std::uint64_t aWandererB = 0xBB353216B7089246ULL; std::uint64_t aWandererC = 0x84ED223E4C66830AULL; std::uint64_t aWandererD = 0xA6C7DB6C0B414542ULL;
    std::uint64_t aWandererE = 0x985C03E6F511B2BBULL; std::uint64_t aWandererF = 0xC59A7A4DCA2B915AULL; std::uint64_t aWandererG = 0x972CE4C0CAB2D534ULL; std::uint64_t aWandererH = 0xDF80663F39F25B9FULL;
    std::uint64_t aWandererI = 0xE68A620644B1C3A1ULL; std::uint64_t aWandererJ = 0xD9194FE4D6DD006FULL; std::uint64_t aWandererK = 0xB1B33CE594E8A825ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16196456260512690873U;
        aCarry = 12730445220255651862U;
        aWandererA = 10409054057775623023U;
        aWandererB = 16808250791782136698U;
        aWandererC = 10973752743450844040U;
        aWandererD = 15677223923402737579U;
        aWandererE = 15840151369125034195U;
        aWandererF = 15026119012636220848U;
        aWandererG = 13360929001243738384U;
        aWandererH = 12845745039212265727U;
        aWandererI = 16422683088071222813U;
        aWandererJ = 18065571273193743798U;
        aWandererK = 12748440301935549204U;
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
    std::uint64_t aPrevious = 0xF417BBFF54B40580ULL;
    std::uint64_t aIngress = 0xB4BD20DC7D634CD9ULL;
    std::uint64_t aCarry = 0xAF1E98D108B6F4A3ULL;

    std::uint64_t aWandererA = 0xE12632E1BA1D41E6ULL;
    std::uint64_t aWandererB = 0xC79708D8D384AD46ULL;
    std::uint64_t aWandererC = 0xEF8A8D06E5F5E64EULL;
    std::uint64_t aWandererD = 0x915B1EFC9D09D923ULL;
    std::uint64_t aWandererE = 0x903B0D71AB5A049FULL;
    std::uint64_t aWandererF = 0xB1E179E916967645ULL;
    std::uint64_t aWandererG = 0xB920948232352458ULL;
    std::uint64_t aWandererH = 0xEE33BAB0F7FD5A31ULL;
    std::uint64_t aWandererI = 0xBDCEA4830664ED95ULL;
    std::uint64_t aWandererJ = 0xF81D76B16B2C35A4ULL;
    std::uint64_t aWandererK = 0xBF4EC8797DDAFBE4ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseDConstants), &(mDomainBundleInbuilt.mPhaseDSalts), aSnowLaneD, 3);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseHConstants), &(mDomainBundleInbuilt.mPhaseHSalts), aSnowLaneD, 7);
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
    std::uint64_t aPrevious = 0xB3C016FEDD4C088FULL; std::uint64_t aIngress = 0xCA0A83DC83306C35ULL; std::uint64_t aCarry = 0xBB7D6599C042066AULL;

    std::uint64_t aWandererA = 0x9BDD6879E9D53214ULL; std::uint64_t aWandererB = 0xDB1D5A2DD5432C0AULL; std::uint64_t aWandererC = 0xE972E7739F02AB8AULL; std::uint64_t aWandererD = 0x877EC6F1010F5BD8ULL;
    std::uint64_t aWandererE = 0xCF117AA2161D3484ULL; std::uint64_t aWandererF = 0xDD2625D472F6205CULL; std::uint64_t aWandererG = 0x9E9ADD44988422C2ULL; std::uint64_t aWandererH = 0xE7BBB02E6F8301C3ULL;
    std::uint64_t aWandererI = 0xC2A49BF5D1092161ULL; std::uint64_t aWandererJ = 0xDF88896311BD4A43ULL; std::uint64_t aWandererK = 0xF7909A2D421CD52AULL;

    // [seed]
        aPrevious = 10460874817188425807U;
        aCarry = 10079535737651725182U;
        aWandererA = 17271216681154310956U;
        aWandererB = 17488129684281832084U;
        aWandererC = 15937776710933933380U;
        aWandererD = 15463522221343387821U;
        aWandererE = 9396264197081824234U;
        aWandererF = 16852190416841417792U;
        aWandererG = 11249560930690057568U;
        aWandererH = 12213495481402791080U;
        aWandererI = 15077949538013951181U;
        aWandererJ = 10919848318505575764U;
        aWandererK = 18042448424937983588U;
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
            0xE1642ABB9912F54BULL, 0x8426DE3C5B7982D3ULL, 0xA6BDECC560BC2DA7ULL, 0x076FA32163A10DBAULL, 
            0xB021B891C527A24FULL, 0xAB55AD902C3D3314ULL, 0x8035F24CE9C01B49ULL, 0x5E93292B8074D476ULL, 
            0xDE47BAE23F08E8B8ULL, 0x212C05840DAD5AF0ULL, 0xEE21D5B892A22B76ULL, 0x45492D9F910EE2B7ULL, 
            0x2CC31CBD4EF994DAULL, 0x8FA97C6C9185BE64ULL, 0xC05B7A6190508C53ULL, 0xB26DE345CCE98202ULL, 
            0x8352CA1573AEBAFAULL, 0x6C5999DA925CB79BULL, 0x9C5F933BE541194EULL, 0x838952FFAC6EB720ULL, 
            0xAB67F267CE2B8B91ULL, 0x2FBACF0ACED345D1ULL, 0x0BE31E30452F0EA1ULL, 0x9BD88519392CB3CEULL, 
            0xDD152703AA5521D6ULL, 0x842FAE9929F1FF60ULL, 0x5F7972E5A8ADDCA4ULL, 0xD3567F2E4D5C7C4BULL, 
            0xEDB563AF9D18BD33ULL, 0xF7CFF61409E6C7D9ULL, 0x12E672269F1237F0ULL, 0xE65CB2BFEC67F8BEULL
        },
        {
            0x31F4DA07755D5FA4ULL, 0x76E1A437B5BE584DULL, 0xD961DA64CC4FCC03ULL, 0x5BA69775BA5A3EF6ULL, 
            0x349C6E6983C89951ULL, 0x90F0EB2AABF19D93ULL, 0x4445252148C809D5ULL, 0xB924570C554C6A6AULL, 
            0xF98456B4B4F91329ULL, 0xC2EFA98ABC54B689ULL, 0x6B41B5C883118859ULL, 0x8394FE814E09CF30ULL, 
            0x33EB6D19EBAC4B9DULL, 0x7B8D0E9DA09ACD95ULL, 0xC67060D843C2A160ULL, 0x3D1DAC76DB212938ULL, 
            0x938FBA2F8EA21E6BULL, 0x34D66D6D2A8C1B02ULL, 0xCB04CA22FF2BA824ULL, 0xC775F37E8C3E7BD8ULL, 
            0xCD83301744C54A23ULL, 0xC82EF82D14A6E73CULL, 0x6CCA51A29F6750E1ULL, 0x00C01FEB1A0C2FDCULL, 
            0x9538E58BBC9B103BULL, 0xBFF2FBA2E00183BCULL, 0x423CB60E6250A51DULL, 0xB1D10A05FCB08E9FULL, 
            0x5455ABB473E098A2ULL, 0x9D6059B075A3F038ULL, 0x56AA5C20A5B97685ULL, 0x76156E6E45108285ULL
        },
        {
            0x82C30EAFBC40072AULL, 0x22926AB227972BD5ULL, 0x0BDEB43778EA070EULL, 0x457698C13CEDD201ULL, 
            0xA12481CA0F29DF7FULL, 0x7A794EC68D156CE0ULL, 0x36C7BA4CC4633DCCULL, 0x60881DA49A815361ULL, 
            0xB5125C66DA9093EFULL, 0x5D7010A562841C9BULL, 0xB1AD43233E86CD36ULL, 0x3EF2BBF934E88AD3ULL, 
            0xC35FB6069A3D5C9FULL, 0x4215155B1AB9ECE7ULL, 0x01AA4316A7A9A109ULL, 0xACC3B9D38101D2AEULL, 
            0xA4CFB7839E71C32CULL, 0xCD9A9DC6E44468A4ULL, 0x693D8A42F4BDB3D2ULL, 0x64E3999240F62B02ULL, 
            0x66C3BA90D41A56F3ULL, 0x6A7D29B029258CD4ULL, 0xC259716938F80280ULL, 0x2F2D7106BD00FB0CULL, 
            0xB790D030A8D753CCULL, 0xB0893DD9A625AF75ULL, 0xD28957AE1A4C104FULL, 0x1D61C3F72F7FE7DCULL, 
            0x7D06FAAEC06C41C2ULL, 0xD9AF101605CB90EDULL, 0x4973C1F6207F2043ULL, 0x449D9A74F3ACA844ULL
        },
        {
            0x886808C37F9F3986ULL, 0x1EBCE0DE246582F4ULL, 0x8D9450C4FE85033FULL, 0xBEB3C9BD2BBCF4DEULL, 
            0xA5F8035B0802AA89ULL, 0x295DD3528E3CCA11ULL, 0x43226F49D58AEA6FULL, 0x4386F8C30AB957DBULL, 
            0xC48CC530EAA7E9DEULL, 0x9841602A4CAE33F3ULL, 0x0DBB84012E78E6B4ULL, 0x163FFFC342554795ULL, 
            0x64FF6EE8481C9D67ULL, 0x4D25E263D0DD2528ULL, 0x67A99AB3DDA078E8ULL, 0x3FD39F57381B8BE9ULL, 
            0x5EB456B971842F44ULL, 0x9F4C5503D0261A83ULL, 0x94F09BDFA7557ED0ULL, 0x67F3AA37C7CB6FF1ULL, 
            0x5841B6223CB7B965ULL, 0xAA7BBA00E8A0CB24ULL, 0x30A6D5AB39F5C507ULL, 0xDC8924AA75F1F401ULL, 
            0xC2462C708D0C6B99ULL, 0x241AA1E3281371E4ULL, 0xDCA3FC018BEC10CEULL, 0x18947844538C129FULL, 
            0x02E1BC74CF3DDD90ULL, 0x8441828A09D2BDA2ULL, 0xBC67E692C5F01E37ULL, 0x3333796729229565ULL
        },
        {
            0x7741D326990610DBULL, 0xAD399602A35A3613ULL, 0x40C2EB8DF5F8A8C0ULL, 0xD574E08C1DE5F146ULL, 
            0xA0B17580E9BE174FULL, 0x92E25E47BC557749ULL, 0x88911C3BB6EA88BFULL, 0x5738ED5ACA40B4F4ULL, 
            0x2C3D283D958F3AD6ULL, 0xEE274E5881C9DCAFULL, 0x8A44042891C45DD6ULL, 0x677A9017D2941C26ULL, 
            0x1430D766E1AE0F75ULL, 0xE0A49B47A7C1B912ULL, 0x40D1FC097993A3D1ULL, 0xEB948DC361D62DA9ULL, 
            0xF7F65AACBD5DD849ULL, 0x0E5D4CC3C3983F8EULL, 0x60023F81E87800E4ULL, 0xF5AAD3B0C5CA14ECULL, 
            0xE87C5F65065C897AULL, 0xE9BFE519A0A28C47ULL, 0x50E70968DB231A11ULL, 0x07D7DCFAA1094BE8ULL, 
            0x18FEAC7AA22082D0ULL, 0xF0C44E79BB9BB45AULL, 0xF517CF82F9881315ULL, 0xF205A3EED9B04E27ULL, 
            0xEF3EEE02148C871FULL, 0x59EA7E1530C701FAULL, 0x63CAF3A600E0539EULL, 0xA9F62DC5DD071E07ULL
        },
        {
            0xC7DF1C17B84AA2B3ULL, 0x3EF61093661AC5B6ULL, 0x9993DF1345A90CDBULL, 0x8E8BAA0ED6E0DA56ULL, 
            0x4FA67E8709F5C50CULL, 0x50F49CE7D6ABA97FULL, 0xABCDD91726C7DDC5ULL, 0xF208C93CD2B1CA36ULL, 
            0xA264550E2A7EFA6CULL, 0xEF13A9DD953635DBULL, 0x6F08CAF23510B31EULL, 0xC95B09B288CE2888ULL, 
            0xE8F173D0E55A5CE2ULL, 0x0E11386CEE8912B1ULL, 0x32004E31546D5BF0ULL, 0x564CB15838C28629ULL, 
            0xA4E3DC32947033DDULL, 0x11D5B95DBCE54309ULL, 0xF0B51A6F77CC9B88ULL, 0x62C23849BF15A221ULL, 
            0x446DB8B02688E662ULL, 0x4085571D8B98B147ULL, 0x466A9271B6FB86C3ULL, 0xBE561A68B165987AULL, 
            0xCD1D897EEDF340D8ULL, 0xF108995124539916ULL, 0x1FC18C79130BA35BULL, 0x271B0205B5627444ULL, 
            0x6AEFEBACEEC46DCBULL, 0x59AE296912E035F8ULL, 0x28382731223B60D5ULL, 0xA013DAC916519057ULL
        }
    },
    {
        {
            0x472D1B654D27B08BULL, 0x7953D0D5A33E50FAULL, 0x1F376F4E10116E7CULL, 0x0866B099E6ABD6B0ULL, 
            0x3C01673E9F7BFEA3ULL, 0xDA9253FE49ED416AULL, 0xF32BEF08CF4ED663ULL, 0xE054A23F3AA33499ULL, 
            0xB34EF5498C0D9A5CULL, 0xFD8A9F974B363E7FULL, 0x3B23FAC3AF1EDD3CULL, 0xB5572516682B42C2ULL, 
            0x5B4BEEC9BF4B4A3DULL, 0x2F8B286C939A3137ULL, 0xF08584EDBC6A024FULL, 0xA60FEC580E2147EFULL, 
            0xD55A7ED78D368FABULL, 0xDD1D23ECAE2636DBULL, 0x7BAA096A26D7DFEFULL, 0x01BB453B8384620DULL, 
            0xAB71B5623B05FA6BULL, 0xFE97D6DAA3F240E6ULL, 0xE4E966E24EDAD029ULL, 0xD1AED8062609B76BULL, 
            0x5EA32EE77ECF32B5ULL, 0xC5AF1C15864D7F73ULL, 0xBFF7268E5CE331E4ULL, 0xA9680D48BE452561ULL, 
            0x93114D86346ACC2FULL, 0x8EE04B2941E4626AULL, 0x49D0143B0D840EABULL, 0xB1516148CA82D87FULL
        },
        {
            0xE79FA3F36AC28F96ULL, 0xE3A5572C4C31ABA1ULL, 0x1D3EAD3C17BC7796ULL, 0x75AA7A45DEC2D07BULL, 
            0xE00C6244496917E6ULL, 0xFE486D7F11317A94ULL, 0x2DB13F25D52CBB92ULL, 0x3AD55A04511018CDULL, 
            0x3D56EB79193C5BD5ULL, 0x6195E3E42EBA824DULL, 0x514AC8B16B73AD61ULL, 0xA5213F3F1DA1CE65ULL, 
            0x091CC8DD894D79C5ULL, 0xBCEC356C5E1BA207ULL, 0xEFCAC272FA497C7AULL, 0x3E1A58FDF9AC8971ULL, 
            0x451BB9A98EEEE646ULL, 0xA05CD861415CB8BFULL, 0xA5F46B357C1406C1ULL, 0x404D7EEED2641771ULL, 
            0x308EAAA3E121F94BULL, 0x192ED881CD9C423AULL, 0x5272ED165C2B4640ULL, 0x0CB9FF48FB430776ULL, 
            0xF7E973A130618FA5ULL, 0x8679DFABA2593BC6ULL, 0x231506DD435B999CULL, 0xC5D674A148FE10D3ULL, 
            0x793BD7F8EF9E13CEULL, 0x8865743A603C8C69ULL, 0xDA0D1226C43EB86BULL, 0x5C9408624586959DULL
        },
        {
            0xC730B536639F973BULL, 0x68E6F9AA0DCE68F4ULL, 0xAFDDBD8695E95972ULL, 0xBDE7A77503D26845ULL, 
            0x02DFF091F2538771ULL, 0xAAE03C6CCE1A336FULL, 0xAD50535547DD838BULL, 0xCD9C0C52990EBEC7ULL, 
            0xE9942E73B6754B44ULL, 0xB2E4E73270B24689ULL, 0xED2724619A8862FAULL, 0x40392A99517512B3ULL, 
            0x27D60D2DECA3F8A8ULL, 0x03936730451DDB47ULL, 0x95DE241F1ED353F4ULL, 0xF57203D1C1EA6592ULL, 
            0xD472217B38700475ULL, 0xF59271328D2053D9ULL, 0xFD92514D6BA76868ULL, 0xCF450AD5AC24CCFCULL, 
            0xB2C70EBB6456EFC6ULL, 0x52AFD3BC483E63EDULL, 0xFE00CB609CFD1145ULL, 0xC6F6E6E126E841E2ULL, 
            0x6E1DADF59E056EA0ULL, 0x880DB2AFB21918D4ULL, 0x1916A73770D68F49ULL, 0x5C3B38FDF828770FULL, 
            0x3393A8275E8FE523ULL, 0xD7FF5B03C5E0BB7FULL, 0x1623244AB9A3A315ULL, 0xF09A21D8DA8FDE20ULL
        },
        {
            0x4EC892DE2A0AB648ULL, 0x68827B0011BEA6C3ULL, 0x428105C84733B4B9ULL, 0x4F0BE7D57E29DF1CULL, 
            0x47B40C82B4A8631CULL, 0x57CC0B4CD6753439ULL, 0x3C815838FC348AB2ULL, 0x5F6E70ABCA72E0F5ULL, 
            0xDDD5F259A2F74732ULL, 0x019D644A77C5E249ULL, 0xE46DF8FF70CD84E2ULL, 0xC71F47663070DD9CULL, 
            0xF6001A6092989C3CULL, 0x09AAD6F7B9312847ULL, 0xE016EBD25AA26FF6ULL, 0xEAF4E9F511788445ULL, 
            0x4A0F3A8BB6BDE0C4ULL, 0x3F655E7BFA43FD66ULL, 0xDDAA4DBE5FD38058ULL, 0xB168928EA5949132ULL, 
            0xC2FBB5214E7D1F78ULL, 0x4D951F01E7A02969ULL, 0x7381E83BCF02E7E4ULL, 0x2D322CB964B14AE3ULL, 
            0x6E296EBC0157296CULL, 0xC30AE3D42CC294B6ULL, 0x1D4F4B4902792AA5ULL, 0x5EB9D387B9EBEA35ULL, 
            0xB5A9DB49B72E50EAULL, 0x8678244D5E9C1C12ULL, 0xB0BCF825A25FD5B9ULL, 0xD711D315AF6AA22BULL
        },
        {
            0xAA74C5C5E430B1AEULL, 0x522D35CD6FC20047ULL, 0x01910C6F7B564DF8ULL, 0xA78A4F65A6D47BC0ULL, 
            0x9F2012396E202ADEULL, 0xAB475B2C9D58268DULL, 0x91A750659DCE292BULL, 0xEA142F84BA34B620ULL, 
            0xD2AF0CF25CE9ACCBULL, 0x60E8B3E529611ED3ULL, 0x2E2793921D6D51F7ULL, 0x8182587FECB43668ULL, 
            0x8D9A450B12F0AF58ULL, 0x817FBC6DBF7FC8FCULL, 0x2A4CF9BB52C5E876ULL, 0x781A151860AF2DBDULL, 
            0xB4CF94337381F2C0ULL, 0xB184C4C82C2CFB30ULL, 0x3EFB1E91A198BE39ULL, 0x7B83761D4CEC80D5ULL, 
            0x2550E6FD7F5275A4ULL, 0x602195C53C3C24CAULL, 0xBEF04A043559F263ULL, 0x9AE7F95B6A8BA853ULL, 
            0xF5453DE49DCFF636ULL, 0x94D564DA5163AA89ULL, 0xE39CED886027A3C1ULL, 0xD36390D61981182DULL, 
            0xD6D0F59EDB0C503EULL, 0xFC1CCB88D0A160FEULL, 0x6C9690DF362A7D55ULL, 0x857CF74DD7027141ULL
        },
        {
            0x8E6D4C0B6CC902FCULL, 0xB9202E93B5F3AADEULL, 0xDE37DD8BE59242E9ULL, 0x1CACFA31C5B7272CULL, 
            0xDE9742D918A53971ULL, 0xFDA6F28E11D3EA78ULL, 0x9BCA39854818F556ULL, 0x611A1CCA4E44A4DBULL, 
            0x77EF04A1A8D20095ULL, 0x8E6D3665BEE72AB6ULL, 0xEF54DF123A0185E0ULL, 0x2D744CEA30B40533ULL, 
            0x79528C9992388A53ULL, 0x28B9D0B8A12F9284ULL, 0x283D2A92C5157D6FULL, 0x7C7A9FF41818B042ULL, 
            0x051F15D9DD8C880EULL, 0x69048CD7EB97992FULL, 0x340BAF1B5629BDB1ULL, 0x8205909843519EECULL, 
            0x0D52135D6926C455ULL, 0xE434B4214D12D50AULL, 0x0D9C3B711ADEE897ULL, 0x97F29701B97BF068ULL, 
            0xC70D8F0D3A2C6BDDULL, 0x1ED77262413C27A2ULL, 0x1BAB6AABB7109839ULL, 0x4C4C027F9E58F0EDULL, 
            0xF351ED1F8B55C2E0ULL, 0x6456DFF823C9DDD4ULL, 0xB48F88F92C0AFF84ULL, 0x5C1BE791CA5BE138ULL
        }
    },
    {
        {
            0xAE1E975D24B12661ULL, 0x7332EEB3539C7019ULL, 0x156D5C8812AC8A6DULL, 0xD905335715B61E57ULL, 
            0x0DC4EB6863C5830FULL, 0x1510C67325DBE7F6ULL, 0xFEB68C8BBE39CA3BULL, 0xAB304C176F3D8C12ULL, 
            0xBA4FA571B3B8B908ULL, 0x3A2524593A7C4CAEULL, 0x08997BF6BE3C3265ULL, 0x8B0096D67093E148ULL, 
            0xB731E83F6947BF92ULL, 0xAA214514F79925C8ULL, 0x9969E9A4640044FAULL, 0x53D57E30CDF5B4A7ULL, 
            0x47E8B28771F2554CULL, 0x018F0D5B66DFD47BULL, 0x3487E3091DB8BF81ULL, 0x5E18EEBFEDD91F66ULL, 
            0x926B36DF21B36403ULL, 0x0023B3FC32051CD0ULL, 0xA4CB01AF2B5B8FCAULL, 0xA4C718C23DDF2BF9ULL, 
            0xE93E2D0DF83DCB3AULL, 0xA67F830A08B008E1ULL, 0xB4CA0E54D48D6234ULL, 0x57DCF882C4A981BAULL, 
            0x2F18C1FBD3AA7653ULL, 0xE826D795282E2DD0ULL, 0x8C29720D5077A653ULL, 0x4AE29FC9AE0FABCBULL
        },
        {
            0x8B34DEDF533EA504ULL, 0x935A29FF9D85B843ULL, 0xE0BD9009993D6622ULL, 0x934F3D20CB7D5A89ULL, 
            0xDF67B582F000A776ULL, 0x35D342EBB5D83375ULL, 0x3D7C4E53A9F6AF0BULL, 0xC617F4B2AB2979BCULL, 
            0xA168926C6BE693B2ULL, 0xA9502E3B1ACE1B1EULL, 0xD819550E93DA5673ULL, 0xFD740C98F0B90C43ULL, 
            0x39F437F229C610B1ULL, 0xB36A44DC683FA352ULL, 0x498428145DE283F7ULL, 0x5B70959A28E633ABULL, 
            0x664C8A403504287FULL, 0xA309FAA82D7962BDULL, 0x6C6B864A2C8891FDULL, 0xDB040F883E001314ULL, 
            0x1CACE59D57402BC9ULL, 0xE1E0F80B58A4CB98ULL, 0xDF267A52770B9DE7ULL, 0xB82A96E6D41959B8ULL, 
            0xC7B899827BEB427DULL, 0x5D007D4D386DB6CEULL, 0x2F089188BB6302C6ULL, 0x56AAAB27571E67A8ULL, 
            0xAE4833B9A0131EB1ULL, 0x2BF423AD0FD54CF2ULL, 0x4FDC769E52B09C94ULL, 0x10CA894A487EDA9BULL
        },
        {
            0x635DE7B9EEB79BE2ULL, 0x123CD4A30C1FD27DULL, 0x1DE7AB40B1085AE8ULL, 0x6E2ACA6AB0904963ULL, 
            0x8B36C9DED3C24F01ULL, 0xC33D6293D6B73730ULL, 0xDBA3A7E84F149E5DULL, 0xD004A9704AAEF679ULL, 
            0x9AB641FCD6B7D7EEULL, 0xD535379DBCE0BB71ULL, 0xE1E9B21213B8B4EEULL, 0xBC7041BA1F0B5E6AULL, 
            0xBE7BAB3D0A52838BULL, 0x5A1BDAE01B81FCC7ULL, 0xBB35116FE07E3EA8ULL, 0x53DA2BFA18814769ULL, 
            0x94C32263F1C8DB7EULL, 0xF697CF846619B39FULL, 0xFDD2F0F7C6E89FE2ULL, 0x37864C82F8E26C8AULL, 
            0x8BF48E5768B66C2CULL, 0x9B5A5D5B4CFE1F1CULL, 0x9418CC2BB30E626EULL, 0xAE040B143D3D833BULL, 
            0x04419529E75A394BULL, 0x76D5A2F0EE500234ULL, 0x7FAF095D96DC2576ULL, 0xA62B4FA5A0414D69ULL, 
            0x597A990236FF2AB7ULL, 0x7D7D02B5B34376A0ULL, 0x3AE136093D1920A9ULL, 0x06F892F4ED10D527ULL
        },
        {
            0xF6CB4C9072437F6DULL, 0x8ED6E9F00BF6B79EULL, 0xFF7D9E6226EFD7FEULL, 0xF93C1E3250CBA280ULL, 
            0x626048D918CE6D1CULL, 0x828DC90B82D7284CULL, 0x83C2F42C4725C4F0ULL, 0x922D6BE28357E904ULL, 
            0xAD072F3053753D72ULL, 0x5AF3FBA65451FC3FULL, 0x761111C5F7A64839ULL, 0x6FE2BD273A0A452EULL, 
            0x212F341F1FD42F17ULL, 0x96E3FB2399CAE9E8ULL, 0x6819F5EDF06EE148ULL, 0x514F8CCA77AD1037ULL, 
            0xD5850F3AC7C7DBC7ULL, 0x96683F86218F628AULL, 0xA79EAEB6FDE36355ULL, 0x308C8E0500EC557AULL, 
            0xEF3E672607D48F33ULL, 0xEBC5E00B5995908AULL, 0xD59A24C996B01E10ULL, 0x4ECF45287E44E282ULL, 
            0x8DFA7E6820314D9AULL, 0xD51EA84AC598C4C3ULL, 0xBC5BA1577A694F3FULL, 0xA2117C63541F6DC4ULL, 
            0xDD14200662893082ULL, 0x52EFAF5FBF69F5B8ULL, 0xB088929124DE323EULL, 0x67171AB0A356011CULL
        },
        {
            0x734D4F753648AA57ULL, 0xCDBECBD35A939BB0ULL, 0xF993649CBF3933ADULL, 0x8F8C96DE983582A1ULL, 
            0xE952B0971EA8EF3AULL, 0xABE382BA9544AE72ULL, 0xEA2A572D6E02444AULL, 0x36CD375D32991B00ULL, 
            0x42F835AAD7D9A0B6ULL, 0x3A1AEA4F74ACEA58ULL, 0xB56FD9D391EEF49AULL, 0x5002AAB46415DE9CULL, 
            0x3F0B412E6594BE4EULL, 0x29B088782D9D6167ULL, 0xAE03368FD7C3F409ULL, 0xA3F23329DFACEA60ULL, 
            0xBB25BFF7EF13206EULL, 0x230992A43BF49315ULL, 0x5CD8CECF066ABB81ULL, 0x366AA37905D8BDF5ULL, 
            0xA41FEB688089243AULL, 0x3771B57D4FC20285ULL, 0xC37B554BC5AD4BD1ULL, 0x074E3DAA587BF1EEULL, 
            0xA3035E6D094C07D2ULL, 0x48662D2B6237DD69ULL, 0xF08617482A5E78BEULL, 0x2D9DB0C52E15F019ULL, 
            0x9BC1F8928D4606E4ULL, 0x6858132613A12F0CULL, 0xBA6045E52C4DB354ULL, 0xB4BB0C2199F5A1A4ULL
        },
        {
            0x0150A501C428FAD1ULL, 0xF6DDF98707E0CFCBULL, 0x0ED2A2EB1249F5DBULL, 0xC30204196473A7ACULL, 
            0xDD2FEDDC67566A0FULL, 0xCB254F64D45AA4E3ULL, 0xEE16135242E407C2ULL, 0x1DF98EBA6FDC04B9ULL, 
            0xCA1B359A05FDB6A1ULL, 0xB6515F8737DF8074ULL, 0xD3440A8E0EC5D87EULL, 0x3EF29D9EB5DDD6D8ULL, 
            0x1097A8F0D4F7E221ULL, 0x489B0DC0DDF3AD13ULL, 0x0353E3202055EBD2ULL, 0x39017DF3015494CDULL, 
            0xB19953ADB4226935ULL, 0xE76468B07A88D75CULL, 0xB7FFC4D466212E26ULL, 0xD22FD401E2B1C285ULL, 
            0xFBAFD54FDF5DC69FULL, 0xACF9322001997BFAULL, 0xC242475E5B39E17DULL, 0x56325B4EB4A02353ULL, 
            0x0F85328276906004ULL, 0x70C5483DFBA3EEDAULL, 0xB19D1D46EF90FED9ULL, 0x04A270450E479C79ULL, 
            0x3CEE80BD2BFA01B2ULL, 0x3911CA87B3B596ACULL, 0xD16D3411117F345EULL, 0x28854A6BC3B25AEDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseAConstants = {
    0xEEE0D2B70B0EC181ULL,
    0x590F21386FE4CE6AULL,
    0x15FF590C395D9E57ULL,
    0xEEE0D2B70B0EC181ULL,
    0x590F21386FE4CE6AULL,
    0x15FF590C395D9E57ULL,
    0x698712946D25F76CULL,
    0x6BC2038B08D81A46ULL,
    0x79,
    0xA8,
    0x50,
    0x4F,
    0x44,
    0x62,
    0xE3,
    0xD1
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseBSalts = {
    {
        {
            0x81CDF9028E326168ULL, 0xBF937BC6A1E8F70CULL, 0x6E2FDFF390CEA250ULL, 0xDD14842373988E2EULL, 
            0xBE741B41CA4C61EBULL, 0xAAC9373103948E61ULL, 0xC849F12E8DD8A4FAULL, 0xE01161FC57E8353EULL, 
            0x5FB7B06AED99C52BULL, 0x485711DF25474FBBULL, 0xBE6A20BB2EB4D7A9ULL, 0x3395C3454114B43CULL, 
            0xBB6C96BD87D59F10ULL, 0x1A729BC1C118BE69ULL, 0xD77866663173E921ULL, 0x3ED42BA31374B15DULL, 
            0x1B55C6E10DB5592CULL, 0x6471C4F99EC14A6AULL, 0x5397BEC09290B763ULL, 0x574C7886F8504640ULL, 
            0x18B1194F63D71433ULL, 0x6745CDAE9390D6CDULL, 0x513B5F723448C276ULL, 0xC795D564F5279081ULL, 
            0x22D74E8EC658361CULL, 0x30B9807ACB022927ULL, 0x15D93CECF82A4EA2ULL, 0x454CEB154C49AE93ULL, 
            0xAB5F0AA8ACBA04C8ULL, 0x818F7BC0F1AFEDF4ULL, 0x76666897860E7BF5ULL, 0xC981076085792D19ULL
        },
        {
            0xEBC8FC1E13852B4AULL, 0x9E36D92076A5A37CULL, 0x921A051342CB1744ULL, 0x8F39C4E8973F5C65ULL, 
            0xA1FB5807FA00E253ULL, 0x040DE8D3448C72DAULL, 0x113920E53D318689ULL, 0xD4DCED0029736C38ULL, 
            0x7E96D41CE9CCCC63ULL, 0xBDE8FA52128E91B2ULL, 0x342EC8BF2539B991ULL, 0x20108C3E51CCE744ULL, 
            0x47F01D7D1A32F9D0ULL, 0x622AAE000F43AFECULL, 0xE26B544265B1E30CULL, 0x3C164CB2A8E4A055ULL, 
            0x16DED6FBD4800E47ULL, 0x9039D1422A3DB330ULL, 0x2908B8117590D4E0ULL, 0x4E3A03CB38CFBF7CULL, 
            0x5E7FF1B906E8C09DULL, 0x794A0C7D48F87218ULL, 0x5048ED2E4977447BULL, 0x3C3B36E381BD784DULL, 
            0xAF02F1386E161C27ULL, 0xB1908476D6B774D7ULL, 0x6D7B65681D42D479ULL, 0xCE347BBD1529E536ULL, 
            0xE490C1CFE110C08BULL, 0x007FFE46405F14BCULL, 0x89F98CA347A25599ULL, 0x167B2C16845473EBULL
        },
        {
            0x37D74EA5C967E35DULL, 0xCEAAC3A0C70D9B74ULL, 0x3721CDEF7AA9C32FULL, 0x04C1AEA26AE3D25EULL, 
            0x74499C7431449C1CULL, 0x8FDC9965F4EF9F1AULL, 0x9AD9172789E51445ULL, 0x92F65AD7ABD0B42DULL, 
            0xBB8A6304EBEC0DF0ULL, 0xE6049EB6DE606035ULL, 0x69434DA121A7F386ULL, 0x6C98CD98F8E3F2EAULL, 
            0x3B9054E2865D8A19ULL, 0x99D7051B255F663DULL, 0x76803D2441ECEF5DULL, 0x127F812AD16EB5D9ULL, 
            0x02C2FD4D650488ABULL, 0xBEF5B4B59CD23B41ULL, 0x971CFFDEC8FAE12AULL, 0x4128370C2684314BULL, 
            0xB5334FE9D4A5E113ULL, 0x1DEB6352B6793541ULL, 0xF561C8298C4E6752ULL, 0xA879EE40B21AD497ULL, 
            0x65A4B399E6BFEADFULL, 0x6B9AB812F6773C18ULL, 0x76E52853941FA6FBULL, 0x16185FEFD22CA711ULL, 
            0xF5ECC8087602DC22ULL, 0x4B6505CC51915A5DULL, 0x1BE7F7450568F9CFULL, 0x4E0BBAFFD8342C51ULL
        },
        {
            0x2A2ABCD6BA70BBC8ULL, 0xE35ADEDCEEA5D71FULL, 0x76AFACB3BC359F09ULL, 0x590A7518D697A18AULL, 
            0xD04B7FA73C5733CAULL, 0xD95D41683957C737ULL, 0x863E2C23540031F5ULL, 0xBF7685DFF3412120ULL, 
            0x66A10D8CD181D1C7ULL, 0x590C9174F4F3FC5FULL, 0xA6A6710BC931CA1BULL, 0x36D08DF62BD04896ULL, 
            0x75F83873E600BA93ULL, 0x2DC1A99234E8BDD7ULL, 0x0E160BBE4D555174ULL, 0x77CDF34531C7EAF5ULL, 
            0x60B2C196FE3C7C72ULL, 0x649CFE34E774E847ULL, 0x5F97BF00CA25824FULL, 0x23184A34FF299199ULL, 
            0x55B87205DA5B34B3ULL, 0x13D803E67E0B7616ULL, 0x9860448B44E544ACULL, 0xB4D4AFF3A582F8B6ULL, 
            0x6DE1472A103956B9ULL, 0x54C2583DC3D414C3ULL, 0x80FB024EAA2AB241ULL, 0x8D1CB9C35574892AULL, 
            0x5A24F7353BC53A4AULL, 0x58C5EEE8D21BAEB4ULL, 0x55A374B8C92F918BULL, 0x63E009991B7CDDC8ULL
        },
        {
            0xF35D92E6D6B33DDDULL, 0xE384BA0F9DB196C1ULL, 0x88EC37192EDFF405ULL, 0xF5800B4909EFB223ULL, 
            0x2930C4191B729E93ULL, 0x794DEE7CBC937795ULL, 0xD4FF20A3BDB9EC6DULL, 0xBD2DD418A76D2DD4ULL, 
            0x56B775D4996E078CULL, 0xA7229074B0C51965ULL, 0x4A2B79E38EEA5489ULL, 0xBB7C0A3EE2F45ABFULL, 
            0x8F00A181B8A8A4E6ULL, 0x8BCE4D5696A1B55BULL, 0xD9088995F74B632EULL, 0x637AEA09CBF825F4ULL, 
            0x4098BA6237B71083ULL, 0xA4A27316386A284FULL, 0x05939EB0A01E139CULL, 0xA6FE03122AFA4B6EULL, 
            0x5C499A25EFF0E967ULL, 0xD9CA72537CC2BB14ULL, 0xDF0434B2C9E63B37ULL, 0x7BC9FBDE483206E0ULL, 
            0x825A3AB849507A79ULL, 0x1D57663875EB8B17ULL, 0xF73F881FDF139BB2ULL, 0xCD3C9DD572FFE3DBULL, 
            0xA484514C2F84CBE1ULL, 0xADABE8366A991D53ULL, 0xA28F9D5978013370ULL, 0x4EF42BA4C9CC73F5ULL
        },
        {
            0xA1AF0F37BE8C993CULL, 0x62DB8288CFD0A6FCULL, 0xA691B5049081E9E8ULL, 0x3E8A7DC86997A5FFULL, 
            0x400466993E7AD781ULL, 0x7D4B1FB92283CBECULL, 0x05D35792B2D4D846ULL, 0x5DA6B40B054BFA06ULL, 
            0x573AC3E7E3C0F019ULL, 0xE4E036ADFBC500CAULL, 0xF1ABCA2D763E6920ULL, 0xEC86991E8F8903AEULL, 
            0x0D4A08AAEAE9F9C1ULL, 0x20ED0D69F9AF7C87ULL, 0x1776E7D24A396432ULL, 0xB737E5B5591F47B7ULL, 
            0xA95532F0A587B0BBULL, 0x11C0E491F989DF83ULL, 0x7055585B6BB9254DULL, 0xED33FCDAEF1DE081ULL, 
            0x22AD0BCD53355862ULL, 0xC9563C607FD7D58FULL, 0xBF02C74975CD5303ULL, 0x4FBB07DE0670EA63ULL, 
            0x58680C296F9D72F9ULL, 0xC93F91081EB0E885ULL, 0x7F7D3E2D7F613507ULL, 0x807E72A6CDB2F947ULL, 
            0x7608B67E15A20672ULL, 0x090D538475A05535ULL, 0x0A2B448E1F3AB069ULL, 0x681BB2E93FE55510ULL
        }
    },
    {
        {
            0x18C720FF417794C3ULL, 0x33D51C5B12E716D9ULL, 0xC4D45C7028A4CF81ULL, 0xE8318951205A0409ULL, 
            0x2EE7475734316641ULL, 0x0010027F29C3480AULL, 0x391E748C16C340EDULL, 0x7A17A79F866961CCULL, 
            0xB79BCEA401C1B1CAULL, 0xB5BC0487410C359BULL, 0x358D4DB3147DA9C8ULL, 0x74765C592CAEB2E8ULL, 
            0x68EA92AAF766A09FULL, 0xEF3B5BB88504B6B2ULL, 0x0B01F5339093B6AAULL, 0xAFAD23A133EEF325ULL, 
            0x68BE3FC14075AA9DULL, 0x57C8AB2ED84FF7A7ULL, 0xA864A637D3CEEDD2ULL, 0xE8B22BCB0B333117ULL, 
            0x5CE12B5BA8FA5991ULL, 0x376156C16E8ADD55ULL, 0x633990C3456466D6ULL, 0xFF4AA82EA5B036CBULL, 
            0xF0D249C5E77C3E5CULL, 0xD8B067EF3B47BCE2ULL, 0x4E99D5D719D13157ULL, 0xE6E06670D482DA2EULL, 
            0x8ABC775FC58F16F1ULL, 0x9DA3B4F86D9B4ADAULL, 0x6E41A553FF20F75CULL, 0x7610F217CF48560AULL
        },
        {
            0xC070FCF176C965F2ULL, 0x82601B6D314E99EFULL, 0x18BB5ED48FBF40EBULL, 0x203F537881052486ULL, 
            0x1633DE1286EEFFF5ULL, 0xD605CA19E553B0DBULL, 0xBE83697B14EA09E3ULL, 0xF12AC0C32D091900ULL, 
            0x7FC32539C088BAA0ULL, 0x6A520D21F5DD256FULL, 0x25A51198E6F9C98EULL, 0x623E971EDA73184EULL, 
            0xFA295D79CF2F41F7ULL, 0x6069F40078257E60ULL, 0x3CD5BC0EB25B4209ULL, 0x30229D01851DDAB9ULL, 
            0xC4B5DD67F9062FCDULL, 0x1D4A8BEE53F67CA4ULL, 0xF7BDD4D32B5D8718ULL, 0xFDE7A954682427B2ULL, 
            0x77C145B5002AAADAULL, 0x9FC13A2A0F3DC1F0ULL, 0xF2F70D054932C843ULL, 0x58C78CC70B5F0554ULL, 
            0x0745B71DC75C9CDAULL, 0x6F92F06C41408E8FULL, 0x3CFFD21CAE2AC9FEULL, 0x813B12E0FA139FADULL, 
            0xED08885CFD8357B9ULL, 0x5BABE03463CDDDEBULL, 0x26720A3D9D26B4D9ULL, 0xE35204F9F2712A0BULL
        },
        {
            0xA9C695590B6A3BB5ULL, 0x826A7D582F8287BFULL, 0x293BE43AC13692C0ULL, 0xE79795C1F641C158ULL, 
            0x45DDC44F35F56849ULL, 0x99241E9AB477048CULL, 0x8F92A8BEED7B50AEULL, 0x8723E45412AD762FULL, 
            0xE84289C4D6260D3DULL, 0x249772B9DC9A0D1DULL, 0x5DF26557741703F4ULL, 0x7EB30EC9D408BB6BULL, 
            0xCBABA1B30F0A6C4DULL, 0x326D12499067DE43ULL, 0xC655A4760E890530ULL, 0x425E165A43741A81ULL, 
            0x0699411152809BBAULL, 0x4921AC7D367D793FULL, 0x41C3B1A3E7D86BB7ULL, 0x34A4DA79EA70EA15ULL, 
            0x81BFE95C44E664C8ULL, 0xDF832163A4B7AF1FULL, 0x8A1A69DD84B04A08ULL, 0x9BD58FAFD4BE03A0ULL, 
            0x252B9C8081B7921FULL, 0x4B4D59C841891347ULL, 0x9B56A73431A64C71ULL, 0x8BA72F174E3DA235ULL, 
            0x209F0ECE96B30532ULL, 0xBFA380034E3B976AULL, 0x78BAE64557E6377DULL, 0x5562EEF9F9CB8CAEULL
        },
        {
            0xDA5ACEFBB90B6A39ULL, 0x15CDB7EE42102D3BULL, 0x20073CD1EB1ED93FULL, 0x0E9CC91A27CF24A3ULL, 
            0x6156FE6D7B508235ULL, 0xF98D8E15CB2059A9ULL, 0x45E60D374084CB50ULL, 0x1CC96F86BCB6BD02ULL, 
            0xE79EE69AF304CFDBULL, 0x3B8D00A298CF5FDBULL, 0xCC4CBDD608FBCF8EULL, 0xF043781C002F475AULL, 
            0x1BDBDF659792E9E3ULL, 0x8007C6EB9AD80F41ULL, 0x5392F23F26156CC8ULL, 0x78D3AA9A0A578C89ULL, 
            0xA4380D44BB3682AAULL, 0xB95D3658367ED075ULL, 0x2871C29F38EFB345ULL, 0x7A2D47189E9D7E62ULL, 
            0xE1F91880213CA508ULL, 0x31BB177C5709866DULL, 0x0F01F8F4432083D5ULL, 0xEE0A18F0A117BF56ULL, 
            0x4C659150EF12A583ULL, 0xACFB9772F62B3539ULL, 0xAA005C2C0F8F0D87ULL, 0xCD0BE5442EEB05A0ULL, 
            0xB9BA1B955CBF92DEULL, 0xEC1429054D18BF68ULL, 0xBA901F1DEC375032ULL, 0x2B4FB429FC51222BULL
        },
        {
            0x6D7969D2EAFB088BULL, 0x3B01832EF892A6BFULL, 0x895EF810BED4C000ULL, 0x24BE3CC6ECB4D0B3ULL, 
            0xF34AE65EE4A4F52DULL, 0x07AFD8FCB9A27BA7ULL, 0xCA031ACD0C052A3DULL, 0xAFFD43321DB3593AULL, 
            0x61F8BC063EDBD9E2ULL, 0x55CEECB37AC3FEC3ULL, 0xE238728589ABFDA9ULL, 0xBC2F5D4512592A2BULL, 
            0xACB9C1B61D675B6DULL, 0x11C0CDF64104327CULL, 0xA130108E77DECEF9ULL, 0xD182E5F886652A66ULL, 
            0x709CD423CFBB2A01ULL, 0x585FC0A9A8745956ULL, 0xD58E5B3DD3241363ULL, 0xF8DEC86E5CAB58E6ULL, 
            0xF73F22D4EABE66E0ULL, 0x21D2CF5667B9FF89ULL, 0xC840BC81DB7AECFDULL, 0x2C5DEBA0C545E46AULL, 
            0xD015E6FE7AE59134ULL, 0x6F5F0F99464BB5B0ULL, 0x601098785A3B095BULL, 0x04754669017CE4B2ULL, 
            0xB5CE9A8E640CCD10ULL, 0xD232F581614C08C6ULL, 0x24E538BC0B09C277ULL, 0xF90E922CB28EAC79ULL
        },
        {
            0x2B59DA072B7A6D9BULL, 0x408CBCC5F9C27ACCULL, 0x2CDBC1FE3C581E1AULL, 0x9E1AA4FE869D231AULL, 
            0x4067E9DA34919C76ULL, 0xB6626AB672489E0DULL, 0x71C7EC2C250C05BBULL, 0x6FC373DF7AFED273ULL, 
            0xEF178B3DC20CBFD3ULL, 0xFBBC388837B6B027ULL, 0xE9F85DCD56FAAA06ULL, 0xD86B1C252C5BDEC6ULL, 
            0x854CC076377F6E6CULL, 0xC9F2F650D414CB22ULL, 0x1FA407AFE38F73C0ULL, 0x35C4EF4E0366218BULL, 
            0xD8FC728F0F1CB443ULL, 0x178D9D9808D2B53DULL, 0xE2CDF8F1F404871FULL, 0x27C71307337C9395ULL, 
            0x5904AE86CD511C73ULL, 0xAE47ED3B3A8D9EEBULL, 0x18C69E2A9C56A06DULL, 0x88192E14EC460411ULL, 
            0xA88A86B75D5780EAULL, 0x8499B77AF769546FULL, 0x4C7FE3BC36BEB0C3ULL, 0xB9CDF15E33DE3DC5ULL, 
            0xAC8A1FF08FC607BEULL, 0xEA8CCC65687BEEF8ULL, 0xE0DF01B3530FBB47ULL, 0x7760479C02F33F66ULL
        }
    },
    {
        {
            0xBB9C74A407B8ADAFULL, 0xCFB836D21A2B1CDCULL, 0xCB87F336A05B02E3ULL, 0xC14796A6CCB95075ULL, 
            0x042763BFC0548E2DULL, 0x92935A340297FE35ULL, 0x1F0FF505E6A91672ULL, 0xD4634D87AA3B8523ULL, 
            0x03F15E8E46FB8D81ULL, 0x783ED5FEFFE8D601ULL, 0xBC9EB7FD85E69D28ULL, 0x31C174C510D421F4ULL, 
            0x206082C6DA13D216ULL, 0xDA82B86843FA2B52ULL, 0xD39D7A451610E7F0ULL, 0xBF6546FC33A8956CULL, 
            0x9C469CE9623C7E63ULL, 0xFC8F2A5E6200CFADULL, 0x6F39447C6048B635ULL, 0xC2E9CDE423888178ULL, 
            0xE778FE00B9DC4D97ULL, 0x9183A8336AD490F8ULL, 0xDB90A5CE293E4623ULL, 0x1641E0055D16B496ULL, 
            0xD17767D1FD9B1A20ULL, 0xC00AE911620B5DDFULL, 0x1F0C1489DC60ED97ULL, 0x9E7A2A1C57CED7AAULL, 
            0xB9164E8F0AE6EDD1ULL, 0xE7825EE729DD5226ULL, 0xF12419635A1D7F89ULL, 0xEDD896CF9CAE9081ULL
        },
        {
            0x10E63B766707578CULL, 0x135F02E259EA59FFULL, 0xB9494E24D94D4BC5ULL, 0x27A59FEEEECAC7ADULL, 
            0x0CADECCF6662F6DDULL, 0xCD2B7F07DEC77926ULL, 0xFFE2CA3F75D36AECULL, 0xAF7EE682DEB92658ULL, 
            0x21C0446FECB5DECFULL, 0x9C77FAAF57581A08ULL, 0x6A77608DB3F6DFDBULL, 0x1C9456CABA81559FULL, 
            0xB3111DD4194C7B70ULL, 0xFD1111F80D1FC199ULL, 0xD6B616338EAE4F37ULL, 0xFA5B99C933B69F70ULL, 
            0xB417B4B0BC64442CULL, 0xCB0E667F52BB9559ULL, 0x36CA1E9F91EF275BULL, 0xD22CFA700B491E02ULL, 
            0x291E959761A1AB26ULL, 0x9DAF0FFD14FE25B7ULL, 0x8B5854717DAD1D79ULL, 0x3F5EC30806ED3F5DULL, 
            0x1C7B5AC6EE16EBD9ULL, 0x29F4CA063AE532F5ULL, 0x27FD4A2DFD5591B0ULL, 0x8DBE60DFF6347B30ULL, 
            0xDF6A9B1B593753BEULL, 0x1A109FDECA9BCDEAULL, 0x2F241AD6C4058792ULL, 0x58FD05390BDB60C5ULL
        },
        {
            0x4D0793BAB2975EF7ULL, 0xD8C7109932CA47FCULL, 0xA09C4EDA69B99373ULL, 0x2CA3AB458761147CULL, 
            0xABBE82D28BBD3662ULL, 0x45E617EFCAE9349AULL, 0x7A782815682A2F42ULL, 0x011D9A79E5439032ULL, 
            0xACD6EC390FA053FCULL, 0x6B59E86C809C4C63ULL, 0x827675E64B0E8059ULL, 0xA94651439191B85BULL, 
            0xD190B89B9056D13DULL, 0xE1ED8A059F440099ULL, 0x3CBDB0AD6645058AULL, 0xCDF1EE801EF77EB0ULL, 
            0x3A58EBABBAD4A946ULL, 0xB218EB90556506F3ULL, 0xEA13928CAEF30D39ULL, 0xD212C827EB39875FULL, 
            0x26BAD2925BEA72D6ULL, 0xDC7BD917B6AE1CE5ULL, 0xA2A899731AA95260ULL, 0xC77C3540CA167C3BULL, 
            0x125B7B617D6E0CC6ULL, 0xEBB3058AA2D9CB1DULL, 0xDA9AC7593F51D1ADULL, 0x23ECC4950227E89DULL, 
            0xEDA8310D54C60F12ULL, 0x463F1E6B4A75495FULL, 0xC0C3597DF20856B5ULL, 0xE2B5A72AFC309093ULL
        },
        {
            0x0E211CC56454A68DULL, 0x961CA1F671A595ACULL, 0x859BE99F10F35CEBULL, 0xA131EEC6B13D1899ULL, 
            0xAEE2E0EA235A5AD2ULL, 0x4B4B22FF929ACDA5ULL, 0xDD03B9C592780126ULL, 0x760210C2D49FAAD0ULL, 
            0xDBEC4AC8C56617AFULL, 0x9392D7122B7445F0ULL, 0x85E8BF5867C11419ULL, 0x7802FCFF3A320059ULL, 
            0x8D27625CA8E1863AULL, 0xF34ABF08340D142FULL, 0xFFB4FFA929FC3CE8ULL, 0xADB591352DD1955BULL, 
            0x80FE3FB2606F2EEBULL, 0xF6C7F803A859E2FBULL, 0xE6E84D9561EEA76EULL, 0x8D4D7B0DFF3BF0D0ULL, 
            0x46DD1168CEC54A64ULL, 0xBF5EAE21AE58CE9EULL, 0x552A2EB68C05035EULL, 0xE1D3DB0B3200B5F1ULL, 
            0xC2F6F4AE868B225AULL, 0x3EAA2CA57B9DDEC4ULL, 0xDA9C2204BD4EA87EULL, 0xE6758CC616B6D503ULL, 
            0x7792F5A4B6C843D1ULL, 0xAF83510B7AA88A1DULL, 0xFA85EEA26891F81EULL, 0xED8BADDF41CE2418ULL
        },
        {
            0x6F5859D1C35FF355ULL, 0x085543AA0D75EBD4ULL, 0x363B5A7F55CC9671ULL, 0xCC2B1771287DB6AAULL, 
            0x9AC2D574EACFFCCBULL, 0x72F5BF1FB42ACC00ULL, 0x066D74CF51E9137DULL, 0xA86CBD8E913844C4ULL, 
            0x92724501B60EDC95ULL, 0x95D3E3726EB16378ULL, 0x686593CB335761BFULL, 0x7A79C6319447BBEBULL, 
            0xE261633F871A069FULL, 0x7FFBA5E358563AF8ULL, 0x2DB6B579460227FDULL, 0x300545285D25674CULL, 
            0x292CFD532DB330E0ULL, 0xB4EC33236A91936AULL, 0xE8208FD9416D5D5CULL, 0x0A99C6351B2DA342ULL, 
            0x2CADB857D54F25A7ULL, 0xFB832233C0EE760BULL, 0x778B886EE4E9FA7AULL, 0xEF1566A611BA4114ULL, 
            0xFB84AF62320E6C7AULL, 0xC7EE42A318C9C8C4ULL, 0x249699B0E1D3A08EULL, 0x284EC30025147B8EULL, 
            0xAB12D488A65F17A5ULL, 0xE81D0FAEF1C9219BULL, 0xE36F5F5D468384F9ULL, 0x4F7BA9002BD11BB6ULL
        },
        {
            0xE9025F3F3A4DEFECULL, 0xE4C993DBB538F930ULL, 0x1347E4C5D49D5FC3ULL, 0x2CA23E61D16F45EAULL, 
            0x795A2B2426589BF2ULL, 0x022EA09D9E72894AULL, 0xB851D562CB73FF5DULL, 0x49D0E7E351884032ULL, 
            0xD843F940CC3F13E7ULL, 0x482CAE7B6C6C7911ULL, 0xE09F511D219694E2ULL, 0xBE77E73993D98BEBULL, 
            0x5FAF67CF8DD28CF7ULL, 0x257107D27712996EULL, 0xD80DC5A8E2E8BA91ULL, 0xE79E8B22C57B975BULL, 
            0xDE7C65F9052C760AULL, 0xFFC009F4D6D43CFBULL, 0x8D37CF37800D6D54ULL, 0x786E2DB07B9B55F8ULL, 
            0xAEE23A9C877D7765ULL, 0x5F9E069478E9165EULL, 0x20831E265070EF05ULL, 0x84A87E5FA8F3CC95ULL, 
            0xEAFCDED9FD45A989ULL, 0x149B971C15976882ULL, 0xAC2ED8C5B5FA3E64ULL, 0x74453388E39409BDULL, 
            0xD714BA10D9388FC0ULL, 0x2F49397607DF731FULL, 0xD8836C6505817EEFULL, 0x430E5445FA817190ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseBConstants = {
    0xD582BFD6A74393D2ULL,
    0x844998A0DD412C52ULL,
    0x6843DF4BF2678067ULL,
    0xD582BFD6A74393D2ULL,
    0x844998A0DD412C52ULL,
    0x6843DF4BF2678067ULL,
    0xCA7AA79AF8CD368AULL,
    0xB71A56A92BE329F4ULL,
    0xBD,
    0xCB,
    0x5A,
    0xB2,
    0xC7,
    0x74,
    0x03,
    0x67
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseCSalts = {
    {
        {
            0xD427E0025FE8FC1BULL, 0x5DD17A9C9CC3E431ULL, 0x864F167393B5A62EULL, 0xCB2F15DB5F98597FULL, 
            0xD789D20D44622C02ULL, 0x65C1A1B7C519116AULL, 0x19CB52A5B068F9D9ULL, 0x493F119FA58E3784ULL, 
            0x0A162078296362ACULL, 0xF615BDC088763FE6ULL, 0xD55E5FDD4F0C5300ULL, 0x4C3338E246D8EEF7ULL, 
            0xD295E1B9738D22CCULL, 0xE4AA3CB22620C81EULL, 0x90C15B57A08EB002ULL, 0xE3570ED6961B47ABULL, 
            0xB1EEBC775DE405D1ULL, 0x97172257D9C733FAULL, 0xBB309701FA4DF894ULL, 0x20E22D908A9A193CULL, 
            0xE3DC2C2C3A9E4606ULL, 0xCCED52590C186E66ULL, 0x8BB81C80E4929A9CULL, 0x83BAD51B163275C9ULL, 
            0xFA0DA0CEBC71BE82ULL, 0x7A963DD83E436674ULL, 0x96EFF630A723C2FCULL, 0x7CB197F9E089DD9FULL, 
            0x2533ADA6FE36D2E8ULL, 0xF59692D29404E747ULL, 0x47DC0E18D00078C3ULL, 0xFA367C7F2EF2BED9ULL
        },
        {
            0x049365EF5925357BULL, 0x8B2A96F7077B6331ULL, 0x7FDAF3DE5DE4EF5DULL, 0xF2AAE89409CFAB68ULL, 
            0xF3236CA9D82085B9ULL, 0x7E7282FC98611C1CULL, 0x8BBDA84EA2880EDAULL, 0x90D02B613E1D0EDDULL, 
            0x86839BDB73DD1205ULL, 0xC13D384611A6F055ULL, 0xC89351504CA18DFFULL, 0x921955BE3497F554ULL, 
            0x0DF9003F5FB66464ULL, 0x0167FA51E7F39EE1ULL, 0x4D2E733A4A43AF9FULL, 0x3AD54DA2F54BBC49ULL, 
            0x54814C7DE141BF12ULL, 0x1C9A12C95B838E0BULL, 0x80821113CC01D871ULL, 0x0EDDBFE9A1C6FEA7ULL, 
            0xFC1A86ECEA763A68ULL, 0x536B54F9A35C3D00ULL, 0x21A9A3417E1C8F07ULL, 0xA4B7972DA3C7A2A2ULL, 
            0x6EF8074D232C077CULL, 0x4C3E960472DE345AULL, 0xA172C2B35DFE2FE7ULL, 0xE56458A83B10EF7DULL, 
            0x7C63DF2103A8E55BULL, 0x6A0CDD748603110DULL, 0x80068DB7C95C349AULL, 0xEBA8A61F74596954ULL
        },
        {
            0x589CBFA7FC19B5EBULL, 0x9C4F242826433E12ULL, 0x9F017D4BAFE01978ULL, 0x3F111F1FE9819467ULL, 
            0xA75CA52EE98BC584ULL, 0x8B712C53A9B85953ULL, 0xC02DE69AA95F491EULL, 0x2E733AE1FE6CBDA6ULL, 
            0x5555D3205CFBB7FFULL, 0x9221F26F70040904ULL, 0x227E390397710B38ULL, 0xBE3003556E928910ULL, 
            0x1D70477EA2F449C0ULL, 0x765163D539D23867ULL, 0x22A96F4E6E1AE157ULL, 0x188FF7CC6B00624FULL, 
            0x10D5F59EE824D8E2ULL, 0x4BA668CAF90A185AULL, 0x664452558C8C5AC0ULL, 0xC213203FD8E03E32ULL, 
            0xBD5FFB32D6D58DE8ULL, 0x05F7002A5BC131A8ULL, 0xE253ABECA299096EULL, 0xA61110E80D72724BULL, 
            0xA50089E0B4C664D5ULL, 0x26364DF2D3820656ULL, 0x55DB23F1804981BFULL, 0x92E9ABD89C0D2745ULL, 
            0xFA6643311355CF26ULL, 0x2DD31EE96B8CBFEDULL, 0x1A0AA863A6803A06ULL, 0x365E2D7B1AAEB9BAULL
        },
        {
            0xD15C251FEB546A16ULL, 0xFC8BEBA0246DE26CULL, 0x879DCA7A0C8BA8DDULL, 0x251878CDC201E912ULL, 
            0xA2B10D2CBADA2BC4ULL, 0x70F21AA2941223CDULL, 0x569918677950AC4FULL, 0x5FBDF79889C63819ULL, 
            0x20E83F2D714A7D73ULL, 0xA2D762EAA38D3CB2ULL, 0xBFE621E5CCFAFD96ULL, 0x7019D662C9A945E0ULL, 
            0xF1EA0CC1C01DEDD6ULL, 0x06605EF2D70DECD2ULL, 0x1955A2D42BC9685FULL, 0x5EB12DE32D48241BULL, 
            0xED9DB001970B85BBULL, 0x8DAC9D5E4D3A9B7AULL, 0x98C9E93AFA1ACF96ULL, 0x447F4819A64C22FFULL, 
            0xC9135B77C6AB80C3ULL, 0xFEA7EF2B70580C79ULL, 0x8147120A9E76B221ULL, 0xE271FFCABD7B35E8ULL, 
            0x5A7000F578970F59ULL, 0xB1AA6EC95F3526FDULL, 0x251A715AAE8E1654ULL, 0xE3F01EB293303DA5ULL, 
            0x03219733A1BEE20BULL, 0x73BE3710EC810E00ULL, 0x20240624F34D0B89ULL, 0x0CDC7C7C251F8762ULL
        },
        {
            0x893005E9C71F632CULL, 0xDD61852014C44F16ULL, 0x7C69F7F73565D0B2ULL, 0x062E0A580D998F66ULL, 
            0x9AAD2BBF44831F5CULL, 0x202AC89E7C66574AULL, 0x4136B8CA9F854DF4ULL, 0x2E0B9234C3D7D22FULL, 
            0x8C0B2005D3E6DFF2ULL, 0x6B4657FFE81F892FULL, 0x3E098854695F5A41ULL, 0x6C20F20B3A3899E4ULL, 
            0x373E7CE0F5CFF26CULL, 0x4B2CDF235D725E74ULL, 0x94680BB9FB5DCC50ULL, 0x2A660BEB611F4DD1ULL, 
            0xCB411C1B97516578ULL, 0x250B634E5CC7BCADULL, 0xE7538B629CD67F16ULL, 0x1F0BA401AF65AF36ULL, 
            0x5074A9B41267DBEBULL, 0x4BA1EF47176463C4ULL, 0x931324EF70250582ULL, 0x671A7B5C7DC63A15ULL, 
            0xC518A48B665F91C4ULL, 0xD9D326E49A1E5D76ULL, 0x87619AAEB242906FULL, 0xEE25BC1654FE7B93ULL, 
            0xD7946600931239CEULL, 0x5A592638ECA02DCFULL, 0x20B466815BA68E35ULL, 0x5FB55A2A568BF729ULL
        },
        {
            0x83ED519D7C4AA7AAULL, 0x3E04E4C0BB4846D5ULL, 0xB475964D6E402F51ULL, 0xD32694E1AC6212B0ULL, 
            0xE7E514F5AD4D7CE5ULL, 0x0EF2E0EA2032E7AAULL, 0x780A8B18638F63F7ULL, 0xBF6305BE45D171EFULL, 
            0x5573CC75F8642852ULL, 0x76F6124F68D2B400ULL, 0x4C83DA04E1442D00ULL, 0x5E7DC7CDE3CF82F3ULL, 
            0xED3098C5FC1D551AULL, 0xA48594D3F478ADE1ULL, 0x3D6BDC80F32D0382ULL, 0x3FC36C0860135000ULL, 
            0xBCA66B4E0357694EULL, 0xF64E783552538091ULL, 0x820CCC5E132F4E33ULL, 0x0948C3852E5EAEBCULL, 
            0x9713C5EDCF4E7056ULL, 0x2AFBC9F5B837F072ULL, 0xCF8BE6CA42CC15A8ULL, 0x94A9DE206D8EBC60ULL, 
            0x71452E9D3E5178D1ULL, 0xC17E2B6E0425AC2AULL, 0x22E0893810118CCDULL, 0x15A4C35F5A836545ULL, 
            0x30E8100B13BBC7FEULL, 0xD0760DBDC3F51FA9ULL, 0x808E38CE76B0F970ULL, 0x0EB5C1E7029B2AB5ULL
        }
    },
    {
        {
            0xF01DA9266676476EULL, 0xE03F08E7EBE094CCULL, 0x2B262A0B1FE5416AULL, 0xAE7280BAC1C7F9F9ULL, 
            0xB7E67F568E9E08F6ULL, 0xAABADA7F26D5E50EULL, 0xBB761EA86E50578BULL, 0x0E8A300CF9C16387ULL, 
            0x80D10E828DB5623FULL, 0x218886DECD9BF219ULL, 0xFA689C4D8A397318ULL, 0xDDE0D54DE301AF50ULL, 
            0xAA43DCEF89781931ULL, 0x21498FE1E7182259ULL, 0xD57843373D1269FAULL, 0x9DFA23128238A46AULL, 
            0xCAF33FA958D383F6ULL, 0x9AB5D40E4DB2AEB9ULL, 0xE24E287C2CCC54DAULL, 0x38FBF472677773DAULL, 
            0x78912AE81E46476CULL, 0x674EA7EEFDB5058FULL, 0x3BD08A22072A1BA4ULL, 0xE857A6794B35EFD4ULL, 
            0x811B698B10BADB96ULL, 0xE7595AB83105DDB0ULL, 0x500C3F659A36855DULL, 0xD269CF0C6CDCAB0CULL, 
            0xF1CA804A6214B43FULL, 0x7A05E0F052782BE7ULL, 0x34D416EAC893FAFBULL, 0x0F8773BAEE2177F3ULL
        },
        {
            0x3451674AD5BEEEC1ULL, 0x6F2603AEE5BEA758ULL, 0xC2854E412423A594ULL, 0x80CD8E0AE1CD7139ULL, 
            0x49F7EBCAD2365B05ULL, 0xF6C6B426B9DE6360ULL, 0x0D800320820ECF07ULL, 0xF5977FB89461AFAAULL, 
            0x5BAC37D504A72F81ULL, 0xB4341AB1588375F5ULL, 0xAF37DD91CA0E254EULL, 0x7D2EC3DE62973260ULL, 
            0xF93F905CDEDC12E5ULL, 0x32B22480BCB19F6CULL, 0x7AF130B696B37A36ULL, 0x964FB4AFF9EC9475ULL, 
            0xBD15C71B45084549ULL, 0xE1BFF96DAA2821BFULL, 0xF27C082FF7AF620AULL, 0xAA5791383AB1721DULL, 
            0xEAF9F78127060AFFULL, 0x37E6C0CC80F0F6C2ULL, 0x766173EE7AF42ADAULL, 0x32AA72E49BCD8A27ULL, 
            0x8C5E36D1009DBF14ULL, 0xE4D91F5F54555774ULL, 0x763E6A4191405301ULL, 0xE894CF3CF65BE132ULL, 
            0x073057CB19FA730DULL, 0x72A8C9B3DCFB5D01ULL, 0xC0D0DE5349A7CF6FULL, 0xA769DDBB9C5DFAF5ULL
        },
        {
            0x5E08925B143C0D34ULL, 0x761F2BFE7327574EULL, 0xD4EBED356EE6FAD6ULL, 0x109E69B275F15BBEULL, 
            0x1488473E5715AFAAULL, 0xC0EFB446F51A2C22ULL, 0xC46AA80CA1C0F2F7ULL, 0x39F248B52C0C5EA8ULL, 
            0xE4AB465263B6A7F4ULL, 0xED1B5480DA8C9A24ULL, 0x1A917A36A0B09D9DULL, 0x3E82DBA7F0BFEB70ULL, 
            0xD284880F4EF104BBULL, 0x5244252230275200ULL, 0x394D8C1CEC0040E9ULL, 0xE861BCB0177F833AULL, 
            0xE6FAB174B24B1DBFULL, 0x2DA9A11B30C8AE92ULL, 0xE4ACF9C306DDF4A5ULL, 0xEE02C895D081027EULL, 
            0x5FBBF237F88FD55BULL, 0x8B2166E71445E104ULL, 0xD82BE2A812CDD6F6ULL, 0xD6DABF0644A1553DULL, 
            0x6A9A3CF1D3BFEFB0ULL, 0xDBAEB9116C4DA174ULL, 0xA3BA20D29AF063ACULL, 0x9237AE18002F97B1ULL, 
            0xD3F5BA47CC3928D2ULL, 0xD1E921D8CE9B9EACULL, 0x13CA0036CA01D356ULL, 0xCC827E74F2D2597DULL
        },
        {
            0x8236AFB9EA7949E6ULL, 0xF496A784DF2AC775ULL, 0x265987AF48F1DDD1ULL, 0x1B3C6032FBB3BD5DULL, 
            0x1CF26D6695576460ULL, 0xCC1AD34872BB464FULL, 0xC63E7F322AE094CDULL, 0xB741BFF6A923DCDEULL, 
            0xA48DDA484EAE8CA4ULL, 0xCD624BB9C43D57DBULL, 0xFE1F05F7E3418254ULL, 0x386A7F9C36A633BCULL, 
            0xF83219E3C0466602ULL, 0x93B6B60EC80E05F7ULL, 0x7D4CAAAF13E91A4DULL, 0xD365ABC295949AB5ULL, 
            0x19D062EB994537FBULL, 0x6BCE24F5785C548BULL, 0x0FDBF6B196D77962ULL, 0x23DDEBA0CD599929ULL, 
            0xDE983FACFEB8979AULL, 0x3072B26C4B597890ULL, 0xCAE036E57249E55EULL, 0x3DF11D93088128C5ULL, 
            0x6441A69E1C5D4EB1ULL, 0x54B54EA70A52C577ULL, 0xBC3D28FF3C4AE410ULL, 0xAB31EEEC1EFFE1A3ULL, 
            0x93364730DF9F1FA5ULL, 0xC34BA3E85B799FF2ULL, 0x73FC6679336D867CULL, 0xAAB45A0DEB739BA5ULL
        },
        {
            0x557B6EE9638C5D95ULL, 0xB1D711538B691033ULL, 0x78C3354FF1AAA9BAULL, 0x53AFE5A7EB6D75B4ULL, 
            0x4F87334F3EAE2D86ULL, 0x9FAB733C79B8BBC4ULL, 0x0B0CE0528D6C46C4ULL, 0x789FF2E4226E0D2CULL, 
            0x11FD6CDB80EC327CULL, 0x0B5009AC030E5D5BULL, 0x72D66AF89491CC29ULL, 0x3987190F93354046ULL, 
            0x029A8DB4D1428AC0ULL, 0x6722B12831CD2F42ULL, 0xE97A283B9D41DE8EULL, 0x84D10595B8398FB1ULL, 
            0xF46D1847C26914FEULL, 0x2CA138246F74C8B2ULL, 0x5A15BF721A4DA02DULL, 0xACB5F3A43754B70BULL, 
            0x99E9BE1D3E733927ULL, 0x68C3CD1A774DF262ULL, 0xE8800A9A52906058ULL, 0x5BAFFD727425B579ULL, 
            0xC601AB74DCB125ACULL, 0xFF0EACF3117DC000ULL, 0x78A09CE278EFB35AULL, 0x5E7104A4EAC99722ULL, 
            0xF54DBFAA1A0F8C0AULL, 0x3EB3393E4B46E74DULL, 0x94046243DAD748DBULL, 0xED02CE633D96E537ULL
        },
        {
            0x6F13838DDC6B0490ULL, 0xAE8B4310BE7DE6F4ULL, 0x1C68280FE90C463DULL, 0x6CF2BD78B6F8E602ULL, 
            0x3B86A1F7CA5F6F2EULL, 0x84A5EC8920061B08ULL, 0x44B9F51DB8AB8727ULL, 0x92210058E94B5633ULL, 
            0x1B97886D3552F45DULL, 0x1A262AF16B6C4AA9ULL, 0xA3986084B4AAFDBEULL, 0x0B74F7FB09427A8DULL, 
            0x30E7A9F7F525AD6AULL, 0xF16508D2F9494652ULL, 0x2761258CA4B3FB99ULL, 0x4C686F72AD09C4FEULL, 
            0xCDF8474B1E1928A9ULL, 0xF9A5F8A12226E8F4ULL, 0x54145A9F6EFC007EULL, 0x1994C0A0E34136DCULL, 
            0xA33370589EFF0116ULL, 0x4E97D2DE4C723832ULL, 0xE01195E534D07ECFULL, 0x64CBCAEAF62C78D1ULL, 
            0x794282700714F4FFULL, 0xFAC22C77C15A87B5ULL, 0xCC137D3300D08D50ULL, 0x85234392BCEC46B8ULL, 
            0x4DAF722E37B4AC0FULL, 0xCB7741919BBA51ABULL, 0x812E90F99815201DULL, 0xAD66DBC0E890BE24ULL
        }
    },
    {
        {
            0xF4AD458C278F0337ULL, 0xC3633063A28BD11DULL, 0x450E1DE6A80D4AD2ULL, 0x799CC12A87A685A5ULL, 
            0xA4A60875868F3A66ULL, 0xFB9989F2EDC60180ULL, 0x1BFF793371E3B354ULL, 0x3CC9F7E6C563B1D8ULL, 
            0x2BDE85C5F501E162ULL, 0x30143A4103D6F484ULL, 0x0B13E65CFEFBEDA3ULL, 0x465F65FC992C1D66ULL, 
            0x7A72B35F11A77D6EULL, 0xEFF9D5AD58825087ULL, 0x894DF32D046D06CDULL, 0x6835440C035DE70FULL, 
            0xA0BD2B50532B69AEULL, 0x7262965F7DE4B8CFULL, 0x8D0F26E89F36398AULL, 0x79ADCCC354490119ULL, 
            0x0C4CEF9DA8C49A17ULL, 0x8B34E1F5444532EEULL, 0x349471CAE44E72ACULL, 0x1045AB939A3B6C36ULL, 
            0x25ED16694EBD97DCULL, 0x0A0BA9C943FFB175ULL, 0xA073AE4EA6EAB03BULL, 0xFBA3359604DA33DBULL, 
            0xF67A3C4191F62099ULL, 0x94A5C024A01D800FULL, 0xC86AB09D51E8A49BULL, 0x648CBA84CF18DDB6ULL
        },
        {
            0x247614AEDC3940DDULL, 0xF95EAE33DA7AC241ULL, 0x569965F822ED9F53ULL, 0xE86C4989730AF291ULL, 
            0x3BD58A6CEA0617D4ULL, 0x65546CC4E7576D0DULL, 0xBED74765EECD6DCEULL, 0xD8143ADAC78466F7ULL, 
            0xCD29CC9ADA638E4CULL, 0x348273B575E7FC8DULL, 0xEDA1FA8D4BB6790AULL, 0xAD66ED1CDA19FCD3ULL, 
            0x7EDC5D20B3C174B0ULL, 0x730CAAC8AE97CC08ULL, 0xE707F2719F08D8F5ULL, 0x7B4D79F3E906C39FULL, 
            0xEE84F68022709C33ULL, 0xEE1BC1CC5605770CULL, 0xEA8A2E5C3751AEF0ULL, 0xA0CE01DC379CD9E0ULL, 
            0xAAB2B153CB46305BULL, 0x523F48247F350C46ULL, 0x8AD80F35CDA585CBULL, 0x61597ECA27611F7FULL, 
            0x6AF2FF192E7E197CULL, 0xDFCF53A5B1BF5C40ULL, 0x4671E29833B2CF36ULL, 0x2F9B1CE50B03CFE4ULL, 
            0x9BDF38EF3B2336D0ULL, 0xDFC2BF687A97B143ULL, 0x5A3ED5DC7B9F8FF8ULL, 0x50CCA81008A5E130ULL
        },
        {
            0xBDD8711FC6131DD8ULL, 0xA3F952FC75A885EDULL, 0x047E98FBEB16044AULL, 0x2854A8D41E361E10ULL, 
            0xBDEB5079C8C20BB9ULL, 0xCEA13CCEA9C949D2ULL, 0x69F32766E64C137DULL, 0x339951472BFDC8E9ULL, 
            0x4434678DF5BB6334ULL, 0xDA13C10CA05A6463ULL, 0x4DF57031F956628FULL, 0x24E65A93359C2615ULL, 
            0xB8001F6C2D0A919DULL, 0x194BDEA4708CDC69ULL, 0x08A2FC2B88007FBEULL, 0xCDF7DB8BBF8E5BE2ULL, 
            0x396789146C9976C0ULL, 0xE50F6F1CA4F961C2ULL, 0xD7100F06ED88A766ULL, 0xDF1E1AB135F34E87ULL, 
            0x154A0D2BB6054188ULL, 0x358842AA54D8C9CEULL, 0x380D0917A5D3DAEBULL, 0xAECC08FDBB52B7BDULL, 
            0xAB8FBFDBCF0B8412ULL, 0x3CDA42E280BD9CDFULL, 0x25B4C0FFF5500591ULL, 0xDCB707785B8619F8ULL, 
            0x764906CFE6C512A2ULL, 0xAA500E0DAB3976AFULL, 0xBE5BE22B75D54299ULL, 0xBD1F7A0FF8B70B86ULL
        },
        {
            0xD34C188B9648BA9EULL, 0x17AED7A3F94281A3ULL, 0xD4ADCB716DB9CEF1ULL, 0xC18168C0E1F1F3A2ULL, 
            0x4165694C41057E58ULL, 0x3CC44D747144A8C2ULL, 0x354A2F3994022612ULL, 0xB46F7EEC32C36776ULL, 
            0x99804404B9B3A94DULL, 0xEC4F6C4D9D51A22CULL, 0x386600FED0B92B9EULL, 0x0FD74F6F09468685ULL, 
            0x495E2A6493B364DDULL, 0xED84F5037B153A2BULL, 0xADAE767317C73C7AULL, 0xAD863F117C6948FEULL, 
            0x6465A9A07675C947ULL, 0x66261FAD1C0A872BULL, 0xFD6ABB7143568012ULL, 0x3CF4F7AB07F6DCBFULL, 
            0xCF132B36FD80DB06ULL, 0xA65B8081834DA845ULL, 0x587C88A475F0F5C1ULL, 0x302B49936058B684ULL, 
            0x38765166B361B837ULL, 0x571D8669FAE9AFFCULL, 0x1AC2AB3BCD03441EULL, 0xAF6F8C7EEDD1EEF1ULL, 
            0xDB01BA9361D51F7FULL, 0x530FDB8F5351CF4CULL, 0xA67D8E6323E4F5CEULL, 0xBEBB460CC551FBC5ULL
        },
        {
            0x3A1C1E07B2DA741CULL, 0x424D52BE7ECE3069ULL, 0xE308EDFEA7F0839DULL, 0x0DD524007C963688ULL, 
            0x58784FAED4B3B80BULL, 0x2ABF7E5F3A8AB64AULL, 0xCE0A114C7456132BULL, 0x802C7B86262A04C6ULL, 
            0x60B68D8C903303A9ULL, 0x5D2C985EAA24ABF8ULL, 0xB7F7C30A39641B19ULL, 0x7818132BD49581BBULL, 
            0xA6F379D442D78D64ULL, 0xA40FD0CBC83B4027ULL, 0x0C810724B94D52ACULL, 0x356A61158487B987ULL, 
            0x0CCDABCE540E5982ULL, 0x17F1B87B282F6401ULL, 0x415F2150297B4A26ULL, 0xEB2C981E22975394ULL, 
            0x99E8A62F114F13FEULL, 0xBDDC6553BBA97F41ULL, 0xE56AD9A0E3CA8645ULL, 0xA91216F999A79BFFULL, 
            0x3191ACF32A31AAE8ULL, 0xAC15ACE561912A08ULL, 0xF2F7415B88052E0AULL, 0x51D5BBE39B750FE5ULL, 
            0xDD71B00BFFE9A1C8ULL, 0x2623D8821E92631AULL, 0x654444B3593AA90FULL, 0x2B6FEE98E0E9AD72ULL
        },
        {
            0x261E91188E30F191ULL, 0x1E44BB92CE1E62EDULL, 0xC28A262EE779F337ULL, 0x76BA2BD5C3A8024CULL, 
            0x597ED151F824210CULL, 0x40AA8859F55C051BULL, 0x340074565A6E4FD5ULL, 0xC94F77C73D00F761ULL, 
            0x9E4DDDE237CF3CC8ULL, 0x4565DE9D6DA6066EULL, 0xAAF0D756B6E37567ULL, 0x8D79DC259DC14713ULL, 
            0x5DE6F93496F81A2FULL, 0xC3840751713F1652ULL, 0x0C5F751B83FAC155ULL, 0x375C038C15F36AD2ULL, 
            0xDFCB02FFBABEF38EULL, 0x37ED761D855FA41CULL, 0x65653F23B931D74BULL, 0xAB4A9E75D7E595F9ULL, 
            0xFEEC9D43773BE3B7ULL, 0x263C669EE21026B7ULL, 0xE4918541E13C86E8ULL, 0x23617867B2004D87ULL, 
            0x16D7B36B1EF0C7D5ULL, 0x291852DC2D265BF9ULL, 0x7A2F87E9C71FD4DFULL, 0x9F627802720BD18FULL, 
            0x5AC0FA5ACAF02CBAULL, 0xD7FB3A46BBF608FCULL, 0x45F2BD3AEEC89077ULL, 0x68F3530B7D0CE820ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseCConstants = {
    0x77B6E396BC6D4331ULL,
    0x6DE4F2A1EDCD1140ULL,
    0x9E3154F98CB617BAULL,
    0x77B6E396BC6D4331ULL,
    0x6DE4F2A1EDCD1140ULL,
    0x9E3154F98CB617BAULL,
    0x63EF894BB7B0722CULL,
    0x7D511FEA477C35E2ULL,
    0x3A,
    0xA1,
    0xCB,
    0x2A,
    0xC2,
    0x17,
    0x1B,
    0xA5
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseDSalts = {
    {
        {
            0xE3CBD061317D8F87ULL, 0x1E4DC426272FB0B8ULL, 0xEA52697C9CBCC157ULL, 0xE07730A3735822EBULL, 
            0x8DDA5ED5E7381F88ULL, 0x5B653BCB4529278DULL, 0x011051D291F7DA6BULL, 0xA851BEA4710F4EC0ULL, 
            0x03021B548D244F0BULL, 0xE2C5F7561E93505BULL, 0xBCC4B7A6BE470FA3ULL, 0xCEF1226519F92129ULL, 
            0x744ADF04185E263CULL, 0xFB98AF6232F681BAULL, 0xA1726D43C39C464AULL, 0x54CFC8B17FC1C75DULL, 
            0x5E38607B524395AFULL, 0x5B21B637FD053057ULL, 0xC0E9021EC16E4AC4ULL, 0xC3804FF1F4282DD0ULL, 
            0xBA13B2E0A8A026C5ULL, 0xAE096922E24D5700ULL, 0x26001052685B2DA7ULL, 0x5E0AB58F96940BBDULL, 
            0x0846DDCBC3335DE8ULL, 0x950B8D614FA5E3ACULL, 0xC595060D82F6F504ULL, 0x45B423824C895B3FULL, 
            0xB7A154001C941842ULL, 0x6822154C44EF4C72ULL, 0xF699AD1A9EEAB470ULL, 0xEC4BCB1ED616B1BFULL
        },
        {
            0x10023400A6742863ULL, 0x9A0BB705170D1DD6ULL, 0xE27E7DB14C66B515ULL, 0x9ED591D0FFCC3D22ULL, 
            0x024497ED72305686ULL, 0x846874BE2BFAF030ULL, 0xA3ED743E726AC6BEULL, 0x6005610AD3F808D2ULL, 
            0xF588F52B5F6D304FULL, 0x5A1D5BECC47DFBB2ULL, 0xCFC94F6515818389ULL, 0x6D68B80F1883F6E3ULL, 
            0x89A4598CFB704350ULL, 0x0CA1F9EF33265F10ULL, 0x9F0786772A0C59A3ULL, 0xD1431527AFDF0C0CULL, 
            0xEC5CB023262D150FULL, 0xFE9388C1252D1F54ULL, 0x0AB136BAD7A9682EULL, 0x557C209A16B80A86ULL, 
            0x7B02CC250188CC75ULL, 0xD20F49A7DD7141E3ULL, 0x84A0A65435A6CE3DULL, 0x6313D38A5A9D2367ULL, 
            0x6474EA3FAE1DBAC9ULL, 0x0FE64F9EDEC07031ULL, 0x5074DF16E70D774DULL, 0x3A36D6C52BBBB5D3ULL, 
            0xC7766F247D02CD38ULL, 0xB6B6847D81547182ULL, 0x7F71EC0B9315220EULL, 0x28EC36CDA49EC848ULL
        },
        {
            0x3A82451319D9CEC9ULL, 0x9F92945F879E1583ULL, 0x44B08D3E7DF1194DULL, 0xB546F4C051C6DAE8ULL, 
            0x2E2D760A77BB6AB4ULL, 0x410DA34A6D243B2DULL, 0x22742138ECB2E7B3ULL, 0xC9CD15AA28E53615ULL, 
            0x12B61E92B4F35B80ULL, 0xAA3F715CE92590FEULL, 0x0E6F8F5B185E6BA5ULL, 0x6867DEC3AF5E99E4ULL, 
            0x7D9D2A3910042B59ULL, 0xC8EAF210F0A1DAACULL, 0x90BBE20E23541441ULL, 0xC4C25C44184BB9E3ULL, 
            0xB8920903CB30375AULL, 0xC2284ED287FD5DDEULL, 0x59FB8B7ACE6B42F3ULL, 0x5D51048DFF6428C4ULL, 
            0xFC68B56368BBE270ULL, 0xD61627668CA643C0ULL, 0x71CC7C87C65D72E1ULL, 0xD0BE5AE1B4EC3BC6ULL, 
            0x3C832C53DBD74246ULL, 0xEAFA897B3B7CB3E4ULL, 0x6F070E2459262955ULL, 0x2AB2D633638EFCC5ULL, 
            0x79CEF9579632F66BULL, 0x1A6972241C81147EULL, 0x61425C46364DC91BULL, 0xDCF8FB6C22F83DE7ULL
        },
        {
            0xA4202E1D0CD2F2AEULL, 0x75DF95CCAED7C67DULL, 0x7A34A8106644FC00ULL, 0x0FE36F2823761FCFULL, 
            0x35CC835FCE4CCCB7ULL, 0x765A37DF51913A79ULL, 0x6787BDA3DBE3F370ULL, 0x510C0FEE569F1687ULL, 
            0xE3C389C1FAEB4E2BULL, 0x42DED907534B57A1ULL, 0xD933CF92B2FC555CULL, 0xFC4B2B7FA2682B95ULL, 
            0xF107337E8D91CDB2ULL, 0xC2BB7B1B4D41DD42ULL, 0x5805E33DEB234689ULL, 0xB497C97881CB884FULL, 
            0x07A2268A9E996A78ULL, 0x6006C207EB099172ULL, 0x70AD084954B8D782ULL, 0xA92D1BA65CF9A9A4ULL, 
            0xC46A825513AA0853ULL, 0x976ECAD526010F58ULL, 0xAF1BB1248732BFCAULL, 0x56D089E685472AECULL, 
            0x4B0AC25A92374AC1ULL, 0x402FD2680C759C0FULL, 0x3D660A55AD6B9F30ULL, 0x4E9BA91D674F9E84ULL, 
            0x76FC61C08D711D91ULL, 0x8EEC94851E6DDF9DULL, 0x4D026250D8F4A0F5ULL, 0xB3E26A1E62493BA5ULL
        },
        {
            0x0C8535EC57FB772AULL, 0x732B384779257FC3ULL, 0x90AC983FEF5E0F9CULL, 0xE7476BAEFFAEE6D5ULL, 
            0xFE5CB7423CF8AB8DULL, 0x511DC66712027C50ULL, 0x4020D82B3435624CULL, 0xCE09912783878AFDULL, 
            0x4739AB4C164F93F4ULL, 0xCB34F1EF97FD79FCULL, 0xA65C009B30D06952ULL, 0xC0F3B2AD39FCCBCFULL, 
            0xCEB6C6D0DAF1049FULL, 0x71B0995065CF83BCULL, 0xCEACCF607B1768E9ULL, 0xFE1397750CBE8184ULL, 
            0x9B94B36B8475F917ULL, 0x2525E8A522572148ULL, 0xA6150E619E09385DULL, 0x042894316B749F92ULL, 
            0x533FF1C7AB6EDEDEULL, 0xF1C44F5003B68C29ULL, 0xDD61A55DFE5DA6ADULL, 0x78CADCC6C9A3BA22ULL, 
            0x507458C037A98DABULL, 0x9039CDDC9534D708ULL, 0x5EE03AD577C986E1ULL, 0x0778EBFAD746153FULL, 
            0xF58D5B8C4607B7AAULL, 0x5376E4C2EF330129ULL, 0x4DE5D77CEBFFF4C6ULL, 0x7DE3B97AF7453F4DULL
        },
        {
            0xAA8E087E01DA7B72ULL, 0x3EE4850FC0F67F58ULL, 0xB685B01D387AB863ULL, 0x605FF3B3A0399750ULL, 
            0x3CF81B137CC463B3ULL, 0xE63647F8D16995F8ULL, 0xB6B5319AF44495EBULL, 0x537B9136813C1327ULL, 
            0x608979EE481608CAULL, 0x94012F5E5D696C27ULL, 0x1554214A403D5244ULL, 0x4B4F3263B788D7AFULL, 
            0x40537E43BABB2435ULL, 0xD34D13FAD325CF3AULL, 0xD3400E01F25BD1ECULL, 0x4463B37E0BA7C31DULL, 
            0x2765A7AF282E4A4CULL, 0x9DCC81E1E6D55B65ULL, 0x8864FAE26FB0DD2AULL, 0x413F7AB55E1F9175ULL, 
            0xDF619723B2C22771ULL, 0x35FBE7E3006A700FULL, 0x2FD2F81CC8B0FB0EULL, 0x5956F7F4C665B6E9ULL, 
            0x7169AF55117FC390ULL, 0x5CA99C60F9A12700ULL, 0x752DC19E12E75D7BULL, 0x8461EC8CB88AE76CULL, 
            0x6501071D304C6A1FULL, 0x29E9707D64510968ULL, 0xB6D9E44AF3EEDD7EULL, 0x30EBA88D2F03586AULL
        }
    },
    {
        {
            0xB1BC8B19DA7C7FDAULL, 0x5CA424B9DEAEF25CULL, 0x14EFB1F8259DCB46ULL, 0x066700F3FC19DEFCULL, 
            0x31E17B7B2B8FD7A2ULL, 0x687DFD152E30D190ULL, 0xFD20F051B8298E5CULL, 0x2914D573EDE3F9E0ULL, 
            0xE3EB2E8D975BBCF8ULL, 0x556587CF3990406EULL, 0xA17A99B40E8C7F17ULL, 0x19FFF316B319A829ULL, 
            0xCC35AC824A85C88CULL, 0xEF6BA14D532AAF8EULL, 0xE0BA2BBE471822CDULL, 0x49F8DF30704466B0ULL, 
            0x0DFB0257B9F9AB29ULL, 0xEA3D1D5FABBB4709ULL, 0x80F6886347D701B8ULL, 0x7ABF2FE915120678ULL, 
            0xF66A8953CCE5BD32ULL, 0xC3A5798A1210CA4CULL, 0x57A4E8925DE95529ULL, 0x40724EE6CCF27FDCULL, 
            0x296D3F9BF814383CULL, 0xA284BD9B4C5B916EULL, 0xE7F36FF73987D103ULL, 0x8177E02C9A50707DULL, 
            0x8847159FAD6840F2ULL, 0x0E86C67636D5AAB3ULL, 0x6FCDA5C4EE06914CULL, 0x476523B1728D6521ULL
        },
        {
            0x7998E0485AF8796BULL, 0x55C66C63527A8DB3ULL, 0x6DB1D768286ABF44ULL, 0x19070A5AF2C6C4AEULL, 
            0x573A5BDFEA6E0926ULL, 0x179671D3F81928BFULL, 0x8E13E8B8162F881DULL, 0x4E5D10E446298E2AULL, 
            0xA0EC78A84AA774A7ULL, 0xF0E6CF03BF10E1F4ULL, 0xE4F9A1BA9F8353FFULL, 0x9CAF7D519F2D0A79ULL, 
            0x15496A58B2B5E797ULL, 0xA33EB2E04120D714ULL, 0x5B859577378A8DEAULL, 0x8C1E2CDAE9725EE2ULL, 
            0xDDFADB107FD98FF5ULL, 0x14A9E93FD3E74B91ULL, 0x9EE8E31AA1DEEEE6ULL, 0xA75827CC029AA723ULL, 
            0x3875E42998FA6D35ULL, 0xFA978DB133D149EFULL, 0x491DF317AF835913ULL, 0x70428270114F44D7ULL, 
            0x9D745B1DE5C0E262ULL, 0x94A34BC3997C932FULL, 0x211F2DC760F502ABULL, 0x2F28AFB38E1C6C6AULL, 
            0x9401698A64A2C817ULL, 0xF0A296B21A5E9BCCULL, 0x08475C611724DD62ULL, 0x3F8A3E67D1DA874EULL
        },
        {
            0xB928A0224AC956C1ULL, 0xCEFFC90DEF85E942ULL, 0xD81485E0C2FDF15FULL, 0xDE79EBD251A656C3ULL, 
            0x20F20BA4673FC69CULL, 0x556FEDDDCBA4FFAEULL, 0x1253224F4B06E26EULL, 0x4811980D5B84DED6ULL, 
            0xB8BE66AA23B2CB2FULL, 0xE47F0ADA65759296ULL, 0x83DF68E0462E5F5CULL, 0xB61E9FEE4A9B1F79ULL, 
            0xF006B8D40A8B3783ULL, 0xCD9E3C7C08D46B02ULL, 0xEBFB42DD528DA591ULL, 0x2ABB30C2AA7214D6ULL, 
            0xFCAC8C42B6ADA2DFULL, 0x1EF9C7E34F997541ULL, 0x52719127BEA3612AULL, 0x879DD18A73F11B6BULL, 
            0x04BEF20F66D7106CULL, 0xACA74BA6422C6D8EULL, 0x197492140F58C7FDULL, 0x5914867279292217ULL, 
            0xD274D601A0F56658ULL, 0x32575369031F8031ULL, 0x851C31C0B72B2A53ULL, 0x830837FD7292FE19ULL, 
            0x58FBC724661F9B23ULL, 0x4A2902EBA7A0CF52ULL, 0x4837A83B7E155576ULL, 0xC3728F158CB18865ULL
        },
        {
            0xFB3126B84DE55996ULL, 0xDA851B36ECD669F6ULL, 0xC63F37D2AE4D3694ULL, 0x1D8F1B1A4D8CDA39ULL, 
            0xB967A42A27E60F89ULL, 0x1F0558012D174B1AULL, 0x2178B9D36CEAD494ULL, 0x8184F08E52A6ACB1ULL, 
            0x30555765A136B6BFULL, 0x9D2E8D6FE4FA8F92ULL, 0xDF0E38B8E8DA3921ULL, 0xBD5914F52792B449ULL, 
            0x82B167C58FF4B5ABULL, 0x0B5FA7401C559906ULL, 0xD9D10D716CE128E0ULL, 0x89577CC7BE4624A6ULL, 
            0x5F7B47728BE36AB6ULL, 0x4FCC5ABC1CEB9D64ULL, 0x3C69276631C95EB6ULL, 0x3C3454F3A4DD4319ULL, 
            0xF0EBA0CC71E9E01DULL, 0x43338C19F2314CD5ULL, 0x0AFC1F1A56A080DFULL, 0xEA209281A211E061ULL, 
            0x927E112B8A27E014ULL, 0x6E882A08AED26829ULL, 0xEA059665A13B8EC1ULL, 0x8A3E30439F1336E5ULL, 
            0xBAC3B88CAFE92869ULL, 0xA0807C0F73DBA9D7ULL, 0xA43B14CC74A91EE2ULL, 0xC350ABA0A5068308ULL
        },
        {
            0x8195612627DA9AF1ULL, 0xEC36F44D648DACCBULL, 0x9B25F5A53D7203D0ULL, 0x4A6EE5E2C1E3E083ULL, 
            0xEA0B842855A8DBF7ULL, 0x53D8853CEA9AC7ACULL, 0x1DCE26CF2A6DF080ULL, 0x8A638F4A13984BBDULL, 
            0xAB361BAE051414BBULL, 0x80238F940E0946A9ULL, 0xF25178C539AECFB4ULL, 0xDDBB52084B63655CULL, 
            0x8957AAEB1A543A13ULL, 0x08E917BADC93D619ULL, 0x85E34B6804D35E34ULL, 0x95D2CF58D87BCA6AULL, 
            0xEAA5B0D8F19F4C80ULL, 0x55EBADC79062D322ULL, 0x9D31CE9BAE0CB292ULL, 0x97B19087DB106EF2ULL, 
            0xCE760E87CF4EEA99ULL, 0xC7CBA950D05E3891ULL, 0x8ADA1222D2BE6F4BULL, 0xAFA5643BDFE0DB82ULL, 
            0x73CB15C578939BDFULL, 0x48B4F0152C7153C4ULL, 0x97BBB70294F2EAE6ULL, 0xF324C0C254BD9602ULL, 
            0x9241270EC4AB71DFULL, 0x92C2F7F28330D07EULL, 0xD932DAAE617491C3ULL, 0xEB8A6961489DA9BFULL
        },
        {
            0xB8ADFAF2BA704F2BULL, 0xB8C57E687324F9A2ULL, 0xA1D7FBA22D4D1E08ULL, 0x703B4C17EF23FC9EULL, 
            0x91E09E3FE62C89DFULL, 0xDBFC45952BF1E187ULL, 0x4B8DE301BC9FB969ULL, 0x224D62293C3B6079ULL, 
            0x9981A3B39DEAF0C8ULL, 0x48C3A4EF2FD1C839ULL, 0xE7F4000019948BFEULL, 0x2AF4060A4313C5BAULL, 
            0x99799CD8AE7E5720ULL, 0xB88D4916C5C80D6BULL, 0x5518D8CC7EF7224AULL, 0x3D90B3FAA0398B46ULL, 
            0x937484809506035BULL, 0x57A3484DC6D78A36ULL, 0x148141EBEA5A4222ULL, 0x5C76758977F9CEF8ULL, 
            0xFE2C4FF64C2BF706ULL, 0x853DB6EB361BF598ULL, 0x0D618E0810D51CE4ULL, 0x30C2579DA0810F3EULL, 
            0x0977B53BA3E501C6ULL, 0x790A4864CFAE1AAFULL, 0xB4B2ADA3D08D0857ULL, 0xD03433A73D6F99FDULL, 
            0x520D53304432E07EULL, 0x3F83C3B7B63B8AE8ULL, 0xB539BDDCD89BA4F8ULL, 0xEB17279CD933C639ULL
        }
    },
    {
        {
            0xB57679321861B9FAULL, 0x440E0E1CA230264AULL, 0x8188CCC6BA811ECFULL, 0xB94E8EF0D0F8394DULL, 
            0xCBE8452DF4D33C5AULL, 0x04ACB9A9C682E688ULL, 0x4D7B523548DFBC50ULL, 0xD25D6FDC4665B7CCULL, 
            0x537F91D746FB5621ULL, 0xFDC522D97BF6E7B8ULL, 0x9616AD14849ED62CULL, 0x9ABBBD74E30F68ECULL, 
            0xDA8D42AC1AB699E3ULL, 0x7851595F171FD9FCULL, 0xDC76A7AA1D3759D2ULL, 0xD6C7FF94BD58593FULL, 
            0xE40CEDE616788717ULL, 0x9FE4138257E411FBULL, 0x63D6D635996B1191ULL, 0x72EF62DD38913940ULL, 
            0xE8E805B239BCE921ULL, 0x980A65A400144B22ULL, 0x15243F3E313FBBF7ULL, 0x45D7DFA677DBD226ULL, 
            0x40059493F8E07F55ULL, 0x6720D5844C9EDBD5ULL, 0x88177A81F3CFD48FULL, 0xD4C75FBDD3B1A78DULL, 
            0x967ECDB04A5C395BULL, 0xFA2C5224AA997C0DULL, 0x1CD83BECC5075B7CULL, 0x9145B745B9318298ULL
        },
        {
            0xAEBD40D3BDE223E1ULL, 0xCA482CDC182DDD09ULL, 0xB032B7969307408BULL, 0xE62EA6F2C2F3F1A5ULL, 
            0x6D3A67E7D38EF069ULL, 0xCA02015305A73281ULL, 0x247698D3A75A4937ULL, 0x22B8C1DF66BCFA21ULL, 
            0x7A6035DBC0595020ULL, 0x598C20EFFCC50E37ULL, 0x6EB33A4C1DB31394ULL, 0x2C9F7E3D3B77E570ULL, 
            0x1112A954E46EACC0ULL, 0x7980FAF5F6AB0D81ULL, 0xB8713DF400B99695ULL, 0xFB6B4976031C471EULL, 
            0x28438DE1C35C7430ULL, 0xCF2CD18B0D6238E1ULL, 0x598958C2A75A1D4FULL, 0xFFAE281D139FC63DULL, 
            0x851FD007C0E1B0F3ULL, 0x25678FD3FA3EF00EULL, 0xF123B2E598723CD1ULL, 0x06D53E9BB56D0937ULL, 
            0x37E3AC0467C72134ULL, 0x2007465A8FA55EBDULL, 0xBC6208ADEFBDFADCULL, 0x5378FEEE0495A12EULL, 
            0x7EBC740C8FD5F7A7ULL, 0x45AF92BFE836B806ULL, 0xDC194D98DC367C73ULL, 0xD545B3E72042B6C5ULL
        },
        {
            0x9FF5FF66E2C5B58FULL, 0x7509FFDAC48AA6FEULL, 0x8F28F95CB7E7D49AULL, 0xBFBD481BFCFA32DEULL, 
            0x815C81A38BAD5494ULL, 0xAD213FEA0D1623AEULL, 0xD1B5212BF50384A2ULL, 0x70487A4B4D2A72E3ULL, 
            0x44B0223ADEFCF94BULL, 0xBE583C2C6B322311ULL, 0x51F6310510D344EEULL, 0xE5308E8E8D09978CULL, 
            0x853C2AD62D895FB4ULL, 0x3218C4E7D144E10EULL, 0x9370FFE262224C24ULL, 0xAAEE7E07490904DAULL, 
            0xE6F36D3DE73C2A75ULL, 0x7D05643BF29F99AAULL, 0x510A4ED615B32852ULL, 0x2E0477EBACCBFBFBULL, 
            0x8E4A1E764864242FULL, 0xD4823E1C660619A8ULL, 0x87CC51B0A50F39AFULL, 0x86AF7360D3B07BC5ULL, 
            0xBE41C93C9E4019B2ULL, 0xBBAC359F3EF76D14ULL, 0xF3E469B790C6BDFCULL, 0x76C832E5FFA31E19ULL, 
            0x8E16999E6AA2E4FDULL, 0xB21FBA09142201D4ULL, 0x99910538B30A3385ULL, 0xB26187CF5C518461ULL
        },
        {
            0x42310FD80E881891ULL, 0xD745BC10156D67E5ULL, 0xB5D36941A3711963ULL, 0x8DDB7BC9518D615CULL, 
            0x5ED3F7B41A273302ULL, 0xD4A2D0B2FD78E0C4ULL, 0xA562F24874A73447ULL, 0x4FC848E63221F690ULL, 
            0x4E42F75A2D4EFF11ULL, 0xD09BAD0471EC0D79ULL, 0x7F43F31AA5734795ULL, 0xDA3464E58058D4E6ULL, 
            0xB27D4CB8FEBE371FULL, 0x51EC797DC625D110ULL, 0xBDFD20F752A998CCULL, 0xA811C289A6698856ULL, 
            0xF1E7A099687ED48DULL, 0x1B5293CCFCD15CE0ULL, 0x12F76D1B0A616EF5ULL, 0x1161012EF5D3A2C4ULL, 
            0x97381DEDE601BDD9ULL, 0x506D2AE069B5EDE4ULL, 0xC6CB00EA87EB9C34ULL, 0xBCD17315A4C083B8ULL, 
            0x38589316F61FAF24ULL, 0xAF4041E4F4A36C3FULL, 0x9DE6A26E857AC201ULL, 0xD221E34248DB90D3ULL, 
            0x7EC69B8E32F320D4ULL, 0x118F1A1FBB6EF13FULL, 0x19DED6FB2E77F8C0ULL, 0x2B941C6753CDE269ULL
        },
        {
            0xEF2E7C38CE0A93F1ULL, 0x240D2AD6B5697630ULL, 0x4091343D1DAC2CE8ULL, 0xDFCA39E64909E17FULL, 
            0x6A7D748CCAA9D881ULL, 0xD19453717A58308DULL, 0x7CE3C117663CAB7DULL, 0x4A7F3DE691E1B8E5ULL, 
            0x542A24554FACCBF6ULL, 0xC9174F5A5FBD235DULL, 0x36DDC3827D0A80F1ULL, 0x971C713FCEA65F8DULL, 
            0x4B7CA68D8BB9B970ULL, 0x831F87E63F2BDA29ULL, 0xB1DFB080A79CA2BEULL, 0x6BF19B29F0361CC4ULL, 
            0x6BC3E48019E104FEULL, 0x9053EB354FA67856ULL, 0x3BFED7DCBB8D726DULL, 0xAAEFA08D0B89E886ULL, 
            0x8E6E5DBCD70D7493ULL, 0xBC731C0B60A9CCEDULL, 0x04B7969CC4630A6AULL, 0xA8621E33053D8D1BULL, 
            0x6F3B6494AFC80FCFULL, 0x39D3272B0C8D8BD8ULL, 0x9EA4769399D47791ULL, 0x93A45BA82F28169BULL, 
            0x3106FF08F1757993ULL, 0xD345A4B58D40B86AULL, 0xE3E8CD59E2E79486ULL, 0x01B5FD8E8B722F90ULL
        },
        {
            0x5337600A414E6CC4ULL, 0x1BAFC3AE2C8C470FULL, 0xD00A7BE2BA7E1184ULL, 0xCB6BB17BE6AD0BC1ULL, 
            0x7BB26AD34D626BFFULL, 0x5E2E18ADFBAE6C53ULL, 0x54D5B5AFF8046596ULL, 0xB2CE1BDD9BE7F176ULL, 
            0x3C3513C8698E6EC7ULL, 0x7194A2A771DEDDACULL, 0xCAAFC7A266B21298ULL, 0xCF76C173223F12B4ULL, 
            0xE2ACBB0F35B976E0ULL, 0x57AD4724F2C72E29ULL, 0x6FB7A6D704786DB3ULL, 0x5963D33609CB4BA6ULL, 
            0x5BD50437E4BE6C1BULL, 0xD53CC4794AC6671EULL, 0x9FA4BF0B3284E259ULL, 0xDDBD689667ABE2F1ULL, 
            0x192A6C1C79AF2110ULL, 0x85693ABEDF0F1A0CULL, 0x696492A0A499BA66ULL, 0x233FD5522DCBA67CULL, 
            0x16F0EE73B13BAA22ULL, 0x500FCF15260DDE3CULL, 0x2705788040D80DFAULL, 0x21931846F632B89FULL, 
            0x6CEAD29EBA8A2254ULL, 0x821991348B2CFBD0ULL, 0xF656F542F18B7B8AULL, 0x3081FAFC87C10C21ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseDConstants = {
    0x780EB707FF626371ULL,
    0xACBD8197909369A2ULL,
    0x39532D971FA2217FULL,
    0x780EB707FF626371ULL,
    0xACBD8197909369A2ULL,
    0x39532D971FA2217FULL,
    0x98A0827F3CC6B424ULL,
    0xCBA2D5953A2077AEULL,
    0x01,
    0x37,
    0x77,
    0x01,
    0x66,
    0x0B,
    0xFA,
    0xC2
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseESalts = {
    {
        {
            0x03106348B825523DULL, 0x33C2D594934CC769ULL, 0x44A3233C8306EB63ULL, 0x29EEAFA0390241A4ULL, 
            0x2294178857DDE6D0ULL, 0x9E876541723645C3ULL, 0xA95EADFBEB17DF3DULL, 0xA28ACC00CCA695DCULL, 
            0x5BB40046F905B08EULL, 0xA5E02B53EB9486C8ULL, 0xEFBA6208C9D64592ULL, 0xE2F8236CE81C31D3ULL, 
            0xFA4C39691ACDB533ULL, 0x54EBB1DCC89148BCULL, 0xF23F6CD145838137ULL, 0xCCE76A3CA4814CDCULL, 
            0x4D04F1F684E93DAFULL, 0x12621809C858CEBBULL, 0xA531DB680955A8A1ULL, 0xB6C9E15EA4B4F724ULL, 
            0x1A61F2C5CC2C03D1ULL, 0xA5CD4E2D047C9742ULL, 0xF47DA208270073DAULL, 0xDB28AE33243451B5ULL, 
            0x30E3C2FC3F159BE7ULL, 0xF1B80A3F4730EA83ULL, 0xA260F65A90127BEDULL, 0xDDC5C0361D458441ULL, 
            0xB3B8496D605774D0ULL, 0x36E91A67A32F1CF6ULL, 0xF64A9FBB52D4BF74ULL, 0x5DE1518DF4B02F22ULL
        },
        {
            0x41ABEB252ABF4AD8ULL, 0x6F5D588B047E54FFULL, 0xCD18B2CFF4E2059EULL, 0xBD24B53AD94511B6ULL, 
            0xF022EA3884CE293BULL, 0x1DA3A276A42C03CDULL, 0x0028BC578302C60BULL, 0x8AA2D8F1FAEB6D44ULL, 
            0x288627EE4A5D05EFULL, 0x85398A5E8A940E38ULL, 0xBBC2F71E075F7CB2ULL, 0x2035650AF5F65699ULL, 
            0xF0C28CC3FE13B1B6ULL, 0x095422538AD69A47ULL, 0x7897D65D5E68F2F0ULL, 0x55076F29A79D720EULL, 
            0x54FFC8E5FBE92CFAULL, 0x66A171373D1472EEULL, 0x02C40094C0C9A03FULL, 0xBB69468CBF5102F8ULL, 
            0x528C520E4B865D50ULL, 0xE30103A86E357989ULL, 0xCC50B88C017A38E5ULL, 0x0F967A91378F06E5ULL, 
            0x58B978812431D6F2ULL, 0x8C2F55A9E23D9F7EULL, 0xC8FE8FF6248D516FULL, 0x0A44F630D6381E2DULL, 
            0x0EA45EC1CD216196ULL, 0xBEAA2361C886BE66ULL, 0x5901C0D33B84EA24ULL, 0xA5275A471F5C8A74ULL
        },
        {
            0xAC3405611FB9FD9DULL, 0x0347A3D844AA9243ULL, 0x912AED9FB8AA5A16ULL, 0x285363EC87D8B0F4ULL, 
            0x99F7FC5411CF5F82ULL, 0xC956CE9FCB1C041FULL, 0x1EC2087D6EE97B91ULL, 0x410B42C2C208721FULL, 
            0xE507D675CFFF6A6BULL, 0x656794564AF559B0ULL, 0xE43495066FA3597FULL, 0x567D863E5FA4B785ULL, 
            0x9C70DF61444574D8ULL, 0x086AA9C0E7449F31ULL, 0xD243DC624A07DB50ULL, 0x2313F975B5A2D6C9ULL, 
            0x8677A338E38AD813ULL, 0x2DE16FB7A4A54204ULL, 0x1B31EF509D4B7CF3ULL, 0x9B97F1DB82769CD3ULL, 
            0x3B8F0B3DF08AF6AEULL, 0x1FDA7E2A501FBCD2ULL, 0x71B22CDC1764C4C2ULL, 0x67B9B3089B0ECFE0ULL, 
            0x194FEF63BF2F463AULL, 0xB6BE8C6D0FBDCE65ULL, 0x7C40CF7C5123674DULL, 0xC4873900115F386CULL, 
            0x4F9C3346F0188437ULL, 0xF47B6554A26807F5ULL, 0xC4604A28FDD9FD21ULL, 0xC892F2FF057E6CC5ULL
        },
        {
            0xDE5F4D92EAF5DC46ULL, 0xB106B06BC992F60AULL, 0x502D264BBE46833FULL, 0x808CEFF4C6CE248FULL, 
            0x9EC55B3C5BE75221ULL, 0xBA221B02A79579F0ULL, 0x805C085F0678D4AAULL, 0xF584084A1C3B65DFULL, 
            0x82A803DE0255FA7BULL, 0x5B3CB476880C2FBCULL, 0x2DC6111305B0E89BULL, 0x21BF6FC9D65BCB34ULL, 
            0xF85C26AB511B6F08ULL, 0x522FAB63B8E34046ULL, 0x0001AD6A9502BB09ULL, 0xAC31E1860D5F547DULL, 
            0x259D364E382D589DULL, 0x1445D3009205C423ULL, 0xEE96362595C1A584ULL, 0x17F6DB6439B65A9DULL, 
            0xFDDF9F5CDEEF62E7ULL, 0x7E109101DB49A30BULL, 0xBF17F1307160D4AAULL, 0x616B7592E12358B1ULL, 
            0xF0CAB2E459DDDF51ULL, 0x4560A76C13CBF8A2ULL, 0x0AB9C8FEB038851CULL, 0x35E7B12A99B60E19ULL, 
            0x09284F45D1E1C581ULL, 0x956F2827BDD85062ULL, 0x46B6B2133F03EBA3ULL, 0xA3878E4FDC9C20C9ULL
        },
        {
            0xD74DFF9403D30D50ULL, 0xFA93D8CC60825C1FULL, 0x197745C318FC1285ULL, 0x61B309FF7CF5BF58ULL, 
            0x98FBAA95EE1E868FULL, 0x2227DCF115D2867CULL, 0xA75A41BE8A9B0452ULL, 0xC3DDC31220465C35ULL, 
            0x6BCF3E30567CFDBFULL, 0xBCA1D781BB133C57ULL, 0x77CC53522F031F95ULL, 0xFD6DCD8511F8E4BAULL, 
            0x77AB3270B33CEF6AULL, 0x3C23B388C4FEBCD3ULL, 0x054E57924FA1DA55ULL, 0x1AB7874B5CBF5DA5ULL, 
            0xA90300343C1D6217ULL, 0xD15F31A74289FABFULL, 0xB737EB3EB4C1BEF2ULL, 0x6BA4C537FCE9AC0AULL, 
            0x631F42F03E6C02A6ULL, 0xD49284658FA4B6E9ULL, 0x19E75F8A92EB7731ULL, 0xF538197FF4E5A95BULL, 
            0x852DBD9FF90AE17EULL, 0x28319DB80A1B2677ULL, 0xF32AC851FDE59B61ULL, 0x898C0F5DAD1A6181ULL, 
            0x3A50CCBCEAC491AEULL, 0x3CF7431F7BA1E833ULL, 0xA87265A025DD0AD7ULL, 0xA0C7D5E2AD52F3DBULL
        },
        {
            0xDF322A000571ED9AULL, 0x2E8483828F752718ULL, 0x9C2D18F19881BAC5ULL, 0x02229AE3D1F3A583ULL, 
            0x0FA4A87FE228588BULL, 0xEC338AB054C2F91EULL, 0x55FE60F94E8997CEULL, 0x23058D587C5A3192ULL, 
            0x668DB297EDBF9D03ULL, 0xBF963E4F16A3B8DCULL, 0x6C0B6D0080872CD1ULL, 0x0EBFAC732A4AF46BULL, 
            0xB365B2E112C1D4AAULL, 0x8864C947B30651F7ULL, 0x3B68D34C1FD4BFE0ULL, 0x1A2276F03632F6E2ULL, 
            0xC2A3C795FACB58D4ULL, 0x6FA43C0890C9F62FULL, 0x53E3B8B962A810EDULL, 0xBAFAFD365FC5A49FULL, 
            0xACA1F1960E61E31BULL, 0x85C8FBF389CFDD7CULL, 0x8F909C7935C9B8CDULL, 0x8806320659159498ULL, 
            0xD8B76C0A29B1F254ULL, 0x0C04F838C030366CULL, 0x159A0AA30FBAF215ULL, 0x975E9F57672C368CULL, 
            0xFDC47BD27C692828ULL, 0x3B6F6D3F21B1C95EULL, 0xB4A5AB976F1066C0ULL, 0x0248964AC37D14FBULL
        }
    },
    {
        {
            0xCA422F41A1E94ECDULL, 0x3BF61AA461A3F44EULL, 0xB5ACC7582C1713F3ULL, 0x817C089782E6FBCEULL, 
            0xEF29233221DCB96CULL, 0xB8CEB79B27ADF333ULL, 0xA01CB2029C30C791ULL, 0x20343329B8C75D24ULL, 
            0xB87293B0A9D89C74ULL, 0x17472C8391024E36ULL, 0x861C0EA432232F9DULL, 0x16E7C9DC146C24B8ULL, 
            0x77DED3F9727149E1ULL, 0x6284464DC44CACAAULL, 0x0FA5053894416E43ULL, 0x8E54196C2BB41983ULL, 
            0x261C4CA317928292ULL, 0x0DAF0107B4DB098BULL, 0x5FDFFF654E879868ULL, 0x31390CA7BCC140E9ULL, 
            0x7C73A2A2468A7E14ULL, 0xD261610B6A042717ULL, 0x1EC439C50A655704ULL, 0x761A1EA2E985DE62ULL, 
            0x4D4B310C4F33A67FULL, 0xB4035668CA67C740ULL, 0x81952A1AC040C6DFULL, 0xEA6BAEA2E74A6A43ULL, 
            0xFD57973D15112E2DULL, 0x6665A81646BD71E0ULL, 0xD620C0C2259F1DB0ULL, 0xCA4D5C55A2690340ULL
        },
        {
            0x4A9903E1BAC77200ULL, 0xEF32262E348278A2ULL, 0xCB6A3B26FEFB4D45ULL, 0x0509D397ECDC868EULL, 
            0x14BA92DE2B6B8E0FULL, 0x5465BD47CA082B98ULL, 0x18FBC6C7D3D5E9C3ULL, 0x84EE7C0B82C8E788ULL, 
            0xD955C278058D90A1ULL, 0x79F90D5D2BDA8008ULL, 0x1A4C1E735F957E06ULL, 0x6380CB260275C434ULL, 
            0x353664618FF48B0FULL, 0xBE0ACC2C10602461ULL, 0x8942C6D946A95642ULL, 0x0F0398B1BB11CB33ULL, 
            0xD771D7CFE75D7824ULL, 0xAF736175DD5C03F2ULL, 0xA2B22DE657865B08ULL, 0x6D1E228998FA31B9ULL, 
            0x84EB8615FCF4D9BAULL, 0xE17556787E30F419ULL, 0xAF29AC55E20253E1ULL, 0x12C790DD25A9354BULL, 
            0x82061F2B40D708B2ULL, 0x34FCBD41A6E367E6ULL, 0xB391A4937839C3ADULL, 0x2E2F25A05D40CA84ULL, 
            0x39A46D87E737D30BULL, 0x6C059158A514B9FDULL, 0x9D00A3BA9B5C27CBULL, 0x3C9E542631043E35ULL
        },
        {
            0xEA1BA3A6807C8CF5ULL, 0x00B6E68D7A5DE4C6ULL, 0xD76C8653FAA423F9ULL, 0x2114FE6D4ED0AD4AULL, 
            0x3A5037776CC8B1E8ULL, 0x29FE798C422BFD5EULL, 0xAAD58805035AC52EULL, 0xDB053E3A1B3E72D4ULL, 
            0x21D500F477F0E0EDULL, 0xD880B4E1ECAA73EFULL, 0x05910E1EFA359E94ULL, 0x7A89ECACD88625A2ULL, 
            0x0989DB45C6236DA8ULL, 0x2A7C47D047FEBB63ULL, 0xFBD5CE2ABB381B81ULL, 0xD83AD067593A3338ULL, 
            0x8D0ED2B45B13177EULL, 0x32F3F7F11FB33B51ULL, 0xA715065CF86E36B0ULL, 0x3BF645FE0379E7B4ULL, 
            0xA378900ADADC5632ULL, 0xEFBBC0AC1391451CULL, 0x40AF087A6ACD5686ULL, 0xDA087ADB1279E028ULL, 
            0x96F2312ADB6A417AULL, 0x31EEEAEF77953A8AULL, 0x4BEC2001C7B11184ULL, 0xD140EFC5B68B7ABAULL, 
            0x77A14B751B996026ULL, 0xFDF51D39C4237FCBULL, 0xED7B37A0D592C66FULL, 0xD9A2DF66E2B6D671ULL
        },
        {
            0x7D62BD1C14714CF8ULL, 0x23F54AC1D13EB1B0ULL, 0x2CB5C09339F24C08ULL, 0x669A1B00A2DA9DBCULL, 
            0xB9E5453A1D2FC0BAULL, 0x90210DFF20B70F29ULL, 0xE50CF98E21B5F6DFULL, 0x589DF13B66580E8DULL, 
            0xE92CFB464F5DD64FULL, 0x5EB4A698F24F77CFULL, 0x2168E45A9DA9C155ULL, 0xD62E45ABE461D0E2ULL, 
            0x68E1325D5482AA7DULL, 0xDB517A8665CB9109ULL, 0x40D1127C1400C522ULL, 0xE6FCD836FBF19DA4ULL, 
            0xAF2DC5AAEBF4CCF6ULL, 0x6FB56CC453E02CA5ULL, 0xE1F30DD21578E6FDULL, 0x656E851FE2A874E2ULL, 
            0xA9BD4F674AAB78E2ULL, 0x553B398EFC009C88ULL, 0x992AF8C73CB1A4F7ULL, 0x713BF868A6132A32ULL, 
            0x8BF0BB4FBBE027BDULL, 0xD103607733CAC31BULL, 0xD1980BCE75A3C392ULL, 0x8010B3DBEEA5D8BCULL, 
            0x15F0548A3EC578EDULL, 0xC7AF8CF4F8AEEB53ULL, 0xF1EF16427B439BEAULL, 0xDBC1722B2265EBC0ULL
        },
        {
            0x29F03EDA62C44D91ULL, 0x40E84F16BA45A1B2ULL, 0xA0F72EAB06412729ULL, 0x255A7A3527369436ULL, 
            0x73AF288C06A97F1DULL, 0x7C811F6D9BE3AEB7ULL, 0xD8EB4F7174DB4F9FULL, 0x9EBC24A590B7FD45ULL, 
            0xE4729CD95768E1CAULL, 0xF27B36E0DCF2A18CULL, 0x20BB4C0A2E0942D8ULL, 0x9CDD5AB9F3074A95ULL, 
            0x857294106D8CA260ULL, 0xB392CB4B0F2E7D29ULL, 0x10AB30A0EA88B1B4ULL, 0x05B87DD0F19545ACULL, 
            0xA85FCFA18CE99E5AULL, 0xAABF84F82D3E9878ULL, 0x0B4974C3591F247AULL, 0xAD9090C220027C65ULL, 
            0x7C14D95A6F5FB591ULL, 0x7E5C55C102A63554ULL, 0xF02C0580AE8E00E0ULL, 0x0105629A73DC0D13ULL, 
            0x696DAD5F6037AA2DULL, 0x99B6A3ED8646478AULL, 0x001DEB318326BF0BULL, 0x527D38249D15CECEULL, 
            0x75B67CAD80A1F403ULL, 0x74B6057E5C5815D6ULL, 0xF34B29D647C43EADULL, 0x6D84F2BF98D1A3C3ULL
        },
        {
            0xFD2AA00DD6C648BCULL, 0x10EC2A95258BA9D0ULL, 0x2D40D346A8D3B750ULL, 0x94656402B7A561FBULL, 
            0x0B423AE9532D540AULL, 0xECDDD2F1D4B36DBDULL, 0x5B2B4DD479D3AB4AULL, 0x14078916A09C8BEBULL, 
            0x40B7886EA8E330F6ULL, 0x2CA5C769FE9499E3ULL, 0xABA9ABD44F893166ULL, 0x1BA854A4CDBBC753ULL, 
            0xEB38F08BCAB549EAULL, 0xE88802C0AE9A0304ULL, 0xB6E6958353563EE5ULL, 0xBD7A081ACC7EF806ULL, 
            0xA2E4799723B01EDDULL, 0xA4469522B5B1C22DULL, 0x895A868829067AA6ULL, 0x52337A9FFE8917AAULL, 
            0xE7FA0D57A081E1B8ULL, 0x11F63D1B3E7F82A9ULL, 0x0936ABCD77C55E86ULL, 0x7F3E5CE9E8CA4A7AULL, 
            0xC270B21611FFF2A9ULL, 0x97BF23F88E1D97F4ULL, 0x16A92614BE399802ULL, 0xEDA0948C1F847553ULL, 
            0xD2B8909C55B80061ULL, 0xA7C6FFF7D0D7D14DULL, 0xA192645C9492FE30ULL, 0xBA9A746D091EADF0ULL
        }
    },
    {
        {
            0x1C8A34DEC4FA99AFULL, 0x85CAC15437D21BE0ULL, 0x9CFB86D08435DEBAULL, 0x0127DC35B42E06CCULL, 
            0x75466797BC3B9708ULL, 0xB09175350961E48FULL, 0x27273A697114B427ULL, 0xA3B780D81365839CULL, 
            0x9CE11D70B5E91B12ULL, 0x55D0A3B7C502353EULL, 0xF1B2649B8980738CULL, 0xF37D7BFE38DDCD5BULL, 
            0xA4CCF9E7E715C11CULL, 0x621905963DB2E87AULL, 0xDC542FEEBF90C3E3ULL, 0xA55E63C060390D3DULL, 
            0xA5EFBBC893CAEA33ULL, 0x3A1DF826656823DDULL, 0xC83BD0F7708AEA33ULL, 0x5588E62F15E01682ULL, 
            0xFC04D0E78B2F7349ULL, 0xD30C61291F2AEFAEULL, 0xC442C661216DB35EULL, 0x76227C34FBEEDC88ULL, 
            0xBD184D33A3EDF6CBULL, 0x403665B93B259639ULL, 0x174141F0C466EADBULL, 0xF28DAF258DFD0712ULL, 
            0x1CA4EB84FC2D9790ULL, 0xE5872FAC81A61352ULL, 0xFEE5EE6F51159FCDULL, 0x2ACE373CC663C07EULL
        },
        {
            0x0C2E88B041E5D6B5ULL, 0xB6722EF5D1633C1AULL, 0x52D9C1AA75EC5B21ULL, 0x8D22D15ABB1A660DULL, 
            0xFE8F83AA5A083F5EULL, 0x4273B695705508DEULL, 0xFA37AFFB9BA30107ULL, 0xAED7470546ADD50FULL, 
            0x2A85877091462B4BULL, 0xC644D365F6AB1E7FULL, 0x1D298585B0A54A8CULL, 0x49706ED84A868C68ULL, 
            0x4E25B4B0BDC3ED36ULL, 0xEDF07286DECA096BULL, 0x92279212C3D15CDCULL, 0x6F2A2887845A4565ULL, 
            0x5FE6EF1FD19FB75AULL, 0x36F39CBF59FDAE6BULL, 0x58EF0B281CFA3406ULL, 0x7025B4272A0841DBULL, 
            0xE1B0DC4D38B414EBULL, 0x1D587CF9E752B875ULL, 0xC802E77C8D5E9B66ULL, 0x375309D1BE9C932FULL, 
            0xBE4FEB9CDE6928BDULL, 0x688F461EBFB58A1DULL, 0x75CF61BE7A58AB38ULL, 0x0CA5E2E2F07DC37FULL, 
            0x9AD7ED20C4B3C145ULL, 0x219209DB84F14C7AULL, 0x7903FF63044BDF60ULL, 0xF9C8EBEEAE3E3681ULL
        },
        {
            0x56F43E525C6C5C1DULL, 0x03F301D0F41AE0FAULL, 0xBD96A2B57E8D8A47ULL, 0x6C1F88E50963F101ULL, 
            0x750D2CD80D4D9811ULL, 0xE499B1F942EAB78DULL, 0x34EB5FC16E49748AULL, 0x0BE278CCB8EE0F86ULL, 
            0x2FCD297FCA851516ULL, 0x6DC593B588C122F4ULL, 0x8490344B94DA23B9ULL, 0x14CD6CA8BD05A5BFULL, 
            0x56963EEBFB58C5EDULL, 0xE26DB79778933C49ULL, 0x7CBD8C658DC0BE1CULL, 0xCEBD484779FD6651ULL, 
            0xC7940282124EAFC8ULL, 0x2A0DF655E354CFC6ULL, 0xE404FB751B3BEF19ULL, 0xDA0013667AD9CA7DULL, 
            0x1BB21FBA94B21B7AULL, 0xC81A01347C9DDD35ULL, 0x0A01376F01172AF0ULL, 0x514941665E10507EULL, 
            0x1EC5B89B36AC6E13ULL, 0x1C3B9E96C146E6CBULL, 0x4154D76216936BC1ULL, 0x1D1B908A6D6C1933ULL, 
            0x12DFEE00BCD8B2A6ULL, 0x15D0AC687BF3C93EULL, 0x855053089D4A44FBULL, 0x143750DC3A90B608ULL
        },
        {
            0x7660131E519085B6ULL, 0xAFF71104B6711D2BULL, 0xBCBBDA27E9EC6F4FULL, 0x6612244EBDFCA16BULL, 
            0x2DE91180AD23B4BCULL, 0x7FF1131C26F41E12ULL, 0xE8EF52C6FA7E811BULL, 0x4AD789497C6311D6ULL, 
            0x36DF9264349B64E3ULL, 0x052CDDA2A6DE6380ULL, 0xCD8DEB557381F3B9ULL, 0xB36252EF27357A63ULL, 
            0x3921B3CA5777E02DULL, 0x1B508DD1D6F89A7CULL, 0x5EF44CB062FF70DAULL, 0xB1361548CA0129F1ULL, 
            0x97592CF4D6EC7190ULL, 0xB40E98FD0846D5F9ULL, 0xEE7997B39E9C2108ULL, 0xB6DBEB28FD2DBB23ULL, 
            0x87D44F7F661A47A5ULL, 0x3D8EC43B81F9A97BULL, 0x5DF44D85ACE13FDFULL, 0x8983FEF93FC1F3A5ULL, 
            0x792C1D6F61210BCDULL, 0xB2E55C646DD69AE6ULL, 0xAC290003CD14A76DULL, 0x426F1555428176E7ULL, 
            0xEE962B876F805AB3ULL, 0x96F4973DF448A223ULL, 0x7138811619CCEF02ULL, 0x44026A0232F52A79ULL
        },
        {
            0x528B1B3834C1BA67ULL, 0x905B810D597B08CEULL, 0x0A6CD2F35C6A299BULL, 0x7842C6540CAA6373ULL, 
            0x80D8DA0EDF6268F7ULL, 0xF5A0941535715858ULL, 0xC926F98386ABCE6EULL, 0xE0F648A966F4F45DULL, 
            0xAD11A7C38B90D025ULL, 0xA632D2B081717052ULL, 0x5B63D6F57603359DULL, 0x736E199FF10A027DULL, 
            0xAA41AA6128D30121ULL, 0x11E068E700B1EC35ULL, 0x42F6800E99B71ABCULL, 0xDA0EB0F30F063060ULL, 
            0x4CAD03A1F05E0750ULL, 0x653AF97D028413E7ULL, 0xC4925AF4A861C45FULL, 0xE836C65512A3DFF5ULL, 
            0xC9037F66CC898A49ULL, 0xCCBFF47832F37DBFULL, 0xACDDAF418330DDE7ULL, 0x9F3128E330B4ED4BULL, 
            0xBAC4BD6BD8F491F7ULL, 0x9ECCF49AEC881DBFULL, 0xEE2401130E182F64ULL, 0xA5496149442D9171ULL, 
            0x73B5CABFEBED9DB5ULL, 0x35D6227471C9052CULL, 0xD93914D978760B9FULL, 0x7B5670BEE39BE2AEULL
        },
        {
            0xE4A7F1505AA762ACULL, 0xE384E9212DD3DFF4ULL, 0xD5F667B369D25D70ULL, 0x69C40890A5D60C39ULL, 
            0xC5851EA4848055DDULL, 0x7D1DAD7925D9ADDAULL, 0xF65237E88922C726ULL, 0x622FF8E3C24F939AULL, 
            0x48AFC2ED305F0780ULL, 0x30EEB0FB92C0D054ULL, 0x17449B6A7C71E1F9ULL, 0xB07A3D564619FB7AULL, 
            0xA26D45139553E84EULL, 0x71B776FD38EA9DA2ULL, 0x8B4215D9B277B66EULL, 0x5D4D5498007E3B67ULL, 
            0xF8F02AEEA93987D8ULL, 0x2FF4BFCD3BFADD57ULL, 0xAE7EF0C3FE609794ULL, 0x81A202F1B9137FFFULL, 
            0xB097DF8C111435AFULL, 0x562131E7BC53F8E7ULL, 0xED62E776AD2EEC72ULL, 0x00A4FC193BEABB26ULL, 
            0x16C198E084E7BF1FULL, 0x6C66C47E03E2C88CULL, 0x2E6B9287D6D4283CULL, 0xE8A8946BC4C95803ULL, 
            0x0494070B99D62967ULL, 0x3B2FE5BD14F9C184ULL, 0x1DC3EC9F40501665ULL, 0xFE80371D2B196D68ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseEConstants = {
    0xB70F744E3800EC9DULL,
    0xBE1B2C6AC7488728ULL,
    0x288E6744687C07E3ULL,
    0xB70F744E3800EC9DULL,
    0xBE1B2C6AC7488728ULL,
    0x288E6744687C07E3ULL,
    0x53099A9702370B67ULL,
    0xC45B2076D79A0157ULL,
    0x2B,
    0xB9,
    0x9C,
    0xB2,
    0xE7,
    0xB9,
    0xA4,
    0xA4
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseFSalts = {
    {
        {
            0x7DE7FE9BA50A6AEBULL, 0xA212FFD944C7A837ULL, 0xB57861BC637D57C2ULL, 0x5906497CB8D65201ULL, 
            0xB4891C1EBF22056DULL, 0x61BD7D59372F1D43ULL, 0xC825F1E8C12F74E6ULL, 0x85343AC489FA1A48ULL, 
            0x4D160F1A16B73119ULL, 0xDA6B4DAB4D5101D6ULL, 0xF16C58ECDE1976ECULL, 0x0002673C2F96880FULL, 
            0x27825BF74D51F3D1ULL, 0x27B3A4D15E09BE44ULL, 0xD4D4A68F24AC9293ULL, 0x957A8C6DC8248A6DULL, 
            0xC855F9D7E2A06D07ULL, 0x89EBAF9BDAF58001ULL, 0x6684BA08F90B6100ULL, 0x5468370CF27A3666ULL, 
            0xDA0B6C16DEB8467FULL, 0x0C42F400DC90FACAULL, 0xE19FD89A88A9CDC1ULL, 0xCDBFD35A6156B9F9ULL, 
            0xFDDBD3DF5D8A23F8ULL, 0x88C9B7BD6D47D8F9ULL, 0x0796744102A1CA45ULL, 0x34B5F2BB7E32B06BULL, 
            0x767FC845B7A580CCULL, 0x49070D0BB7A84673ULL, 0xCE2DCD9353E6B556ULL, 0xE5DA983E23223E9CULL
        },
        {
            0xBC3EB518EE4D09F3ULL, 0x3FA8CE6566CD4438ULL, 0x64589F38CF06DDF6ULL, 0xE5FBA29DEE7EA1C8ULL, 
            0x9119E6F56669A133ULL, 0x78C0C361654ED7E3ULL, 0x97ABCD789BC0D843ULL, 0x5A1A7C9E0A40E1BAULL, 
            0xF9ED02A18A77C052ULL, 0x25425AA3F776E245ULL, 0x57045B37865B2116ULL, 0x09A477F8B52D73DBULL, 
            0x59AE68F8ABF3A60EULL, 0x0D4DE1557C62B0E7ULL, 0xC6B5B8D04BA6596CULL, 0xF5F7EFE7515BFB8BULL, 
            0xC4639F8079AF5726ULL, 0x506E554F53800BA7ULL, 0x1DDA4044EBDD2824ULL, 0xD9D5C50B25AF23D3ULL, 
            0x31EE9635F93FFE0AULL, 0x1C7F3BD28755985EULL, 0x48D1BA4393D01FD4ULL, 0x1B561DCF42132057ULL, 
            0x556B229DA1ACCC48ULL, 0xDFDE3F7D39F2B1FCULL, 0xA63F8CC596A8655FULL, 0x0B0745ED85C872DAULL, 
            0x8FEDB85E511CC263ULL, 0x7BFC20C49F0EF6D7ULL, 0xB91090AB0D2E9CE2ULL, 0x68D86495B184D189ULL
        },
        {
            0x41822DCA8C69BAC5ULL, 0x9D69CE4436A146FEULL, 0x527A86B58EF7CB19ULL, 0x5E0D92954174F3CBULL, 
            0x727FB23FAE802968ULL, 0x405CFD4DF29998B6ULL, 0x2057BC5450A225AFULL, 0x4B768D00D09E8524ULL, 
            0x0D3B939D1C1EE9A3ULL, 0xF720BA652A79E7C2ULL, 0x86BF0A4BCA85AB2BULL, 0xF6C737CB610F638CULL, 
            0x3C2B6011D26F0AFAULL, 0x006D9C46260DF886ULL, 0x1DEF5DD0FAD62D49ULL, 0x8AA7B6440143C314ULL, 
            0xA50B5B97D5DD8F28ULL, 0x6298D38ED1B434FFULL, 0xEC1B5BF6193C0831ULL, 0x2E7E208D8D683CAAULL, 
            0xEA70ECAE94A87E82ULL, 0x9F9A8A3A566F9289ULL, 0x98B64038F2671540ULL, 0x804CB2ECE14175E1ULL, 
            0xDD58A58ED78F4BD1ULL, 0x495D70E63E779975ULL, 0x0DB83C2E1FA3086FULL, 0xFFC6877DC7311563ULL, 
            0xF70ADC7A1E13AB21ULL, 0x76E608D7DCB1368DULL, 0xB1D22D447F2C42A4ULL, 0xEA560532700B0DDCULL
        },
        {
            0xEE93FAA738CAC687ULL, 0xF035D73AB5305567ULL, 0xFCCBC9F572DC4418ULL, 0x8FFC5AC02F8FF01CULL, 
            0xCEC0FE8BAFF130C3ULL, 0xB58F17F00A8F4EBDULL, 0xC34F412E7BEEBDDCULL, 0xF09DB0F481372C5CULL, 
            0x67E92D279BE70353ULL, 0xB4C5FF92268F8F73ULL, 0xB1E5D0AD2FD7004BULL, 0xCED2428E010A19F1ULL, 
            0x42A41F07BFBD6586ULL, 0x660CC0850FCDB2BCULL, 0x439C4584D9B09ADEULL, 0xB9FF6A46D49E34E7ULL, 
            0xE8F085E8CF3C3EA5ULL, 0x10E527B36CFC285CULL, 0xE18FC383E08A0274ULL, 0x7F5F9AFF2C24790BULL, 
            0x787F4E612F4AFC1AULL, 0xD7E3D802958F63C2ULL, 0xE84BF2ECDA2B7764ULL, 0xC9526EFBFC3023A6ULL, 
            0x76D2F384EFA18EAFULL, 0xD310F96EC85E9A99ULL, 0x73C2B92D0C85C857ULL, 0x1C8B703F56C748B6ULL, 
            0xC01EF02CA60D4235ULL, 0x6439B8D76DFC437CULL, 0xFAB64A8678773CB1ULL, 0x3CFB353C21E2AE18ULL
        },
        {
            0x1568A5AB800B39DBULL, 0xB2A4F2A875C77469ULL, 0xF2354E8B09E5B2D0ULL, 0x2728D13A331B1712ULL, 
            0x7D7B32FB1113FD10ULL, 0x957935F7FE868FF4ULL, 0x618DD044725B6298ULL, 0x395274EFE9708A65ULL, 
            0x90034B337F3CC0FAULL, 0x04DE3E09F10EC423ULL, 0xD4FAFB5F536DA9D3ULL, 0xAAD04FFC2735086DULL, 
            0xC0F757666C3CDE39ULL, 0xB10EB4B20F0E83E3ULL, 0x69F587E8AADEAB6FULL, 0x804E53F2CB0973B3ULL, 
            0x1808ACDBC14F31D4ULL, 0xAC7D8CB8E290EFE9ULL, 0xC4730DDCB7EB3759ULL, 0xF07660573CE3EB8CULL, 
            0x97D3D95440BF644DULL, 0x9772F77748616EA3ULL, 0x3576240C7515D401ULL, 0xF3504536B50B12F7ULL, 
            0x85DC61D93BF86BFCULL, 0x4EAD03F2E84548FCULL, 0xF2792B237E4A4B51ULL, 0xAE19C7A93C6EC383ULL, 
            0x13B106F89D3DBBCEULL, 0x6E6BA6D22EEEEA7AULL, 0xF67D41D216276A01ULL, 0x7E368A8A5AD5664EULL
        },
        {
            0x30CD5C6DC0F8B79BULL, 0xA90779AC368BDE08ULL, 0xAAE781CDAF57F3CEULL, 0x7D81D700EB1F17DFULL, 
            0x141E4FC4FC0963D8ULL, 0x3533A565B4ADD452ULL, 0xE9E0623EE2B67E80ULL, 0x23EF9799EDE7A6F6ULL, 
            0x9216D7FDC02354BBULL, 0xE65689C2070E6261ULL, 0x2ABE1FDEF5CDC548ULL, 0xB90563170236F42BULL, 
            0xCCDB2DBEACBE3773ULL, 0x938598CA47CC6633ULL, 0xA1B806D63C04F636ULL, 0x98A19AE4AB0737ACULL, 
            0x30FA6BA9A545D04EULL, 0x2A2C8D5E25B3336EULL, 0x6B21D254F0719AFBULL, 0x465A282D9A8179ABULL, 
            0xA556D1A048230EE6ULL, 0x865905F111FD7317ULL, 0x503D2E6017344B7EULL, 0x537ACB0AF3530099ULL, 
            0xEEE71844EDA56475ULL, 0x3EBC05BF1D18D28AULL, 0x417301F046C3CB0FULL, 0x89BD49D6AD515FE9ULL, 
            0xC4643343DC114BBEULL, 0x7CA19F18C32BA5EFULL, 0x2AC4038FC71EDF62ULL, 0xFA77E2E4D1DF1D60ULL
        }
    },
    {
        {
            0x2BAACDAC3D01C4D3ULL, 0xD72DBBF122F3E17DULL, 0x4B2D9AB6F5D926E1ULL, 0x997E038D904F8044ULL, 
            0x17E9DD1019FC83A9ULL, 0x31AB741C6B0248B8ULL, 0xBE32CCBA203AA2BFULL, 0xD892972438AC4F54ULL, 
            0x5263CB07B27D17CDULL, 0xA0AEF86A467D38DCULL, 0x71E0F3945448AFF1ULL, 0xBCE205183C4B9A96ULL, 
            0x1307B71FF1A5D7FEULL, 0xC5C26B21D0ECB416ULL, 0x53028CADAC832D11ULL, 0x195CB4083A92903FULL, 
            0x8F9722A63FB39D69ULL, 0x279F9479FD85A2DBULL, 0xB075E554D3804814ULL, 0xB77286B1246B4FB9ULL, 
            0xB57F97EE78A7BF42ULL, 0x9D8B0DFDEA4F7892ULL, 0x053410A29EC4BC0EULL, 0x1FA4650FD59163AEULL, 
            0x3613F68EE9E8770DULL, 0xCD57D7BA06D752AAULL, 0x9ED810B323D83DE5ULL, 0x406A8FADC8443064ULL, 
            0x07C654D512224156ULL, 0x0B71883CB45B052BULL, 0xE6491BD008756120ULL, 0x2238959AFC4A32C0ULL
        },
        {
            0xE7011149796EEA36ULL, 0xA801AF6C1389F7E0ULL, 0x23B3124D6BC88816ULL, 0x3B40D8D0B8FE5561ULL, 
            0xEFD72C7D478451F6ULL, 0xCF31FAB0D71336E9ULL, 0x7D181376C0589A26ULL, 0x11E49BFDCF4B4EBDULL, 
            0xC01265DEC25CBA20ULL, 0x8E1F32C04BDF56E0ULL, 0xCBA52C17FBCDD4D1ULL, 0xA31C477C906393E5ULL, 
            0xD312F4B570806A5DULL, 0xAE9766C54493F637ULL, 0x26F3F597D1403E11ULL, 0x0E4E012CF45FC02FULL, 
            0x064ADDBBBCD7212DULL, 0x84E715D937DC9FA9ULL, 0xADF5D1A8E9743A4CULL, 0x65473E5742AB05B5ULL, 
            0x639C6403261368B8ULL, 0x34AA04F057F52D9FULL, 0xCFF808CBC544EC5FULL, 0xFF56AE98771C4AF8ULL, 
            0x7CEDC6EB699C8F95ULL, 0xA08C1DC17990AE55ULL, 0xD73530E7F59ADAFEULL, 0x3331197D90F5CD7AULL, 
            0x0B714D80021BAB81ULL, 0xE0A5690BB3928690ULL, 0x9303BF42182B5DC9ULL, 0xFC16C0849FD7B810ULL
        },
        {
            0x43132D8DEF235B1DULL, 0x2995FDACA8C0679BULL, 0x688A74FCAAFB8B42ULL, 0xE9A1C3666BCB248DULL, 
            0xA46A0F3C6D236779ULL, 0x817AD8355B2B7B5CULL, 0xA043A1F8E20627AAULL, 0x191F65B919036B6DULL, 
            0x084B76CFEB1FA78AULL, 0x329FE766A7195155ULL, 0x9FB4DFF8535A1394ULL, 0xFD79889C5BD8450EULL, 
            0xC381A2C5D8573B66ULL, 0x9B2C7D8EFD572008ULL, 0x55D28D7574228247ULL, 0x9096FF47EAEEC663ULL, 
            0x356741337BCEF8BDULL, 0x6F4B7607D2506BE2ULL, 0x31AD19351F0506F2ULL, 0xBAA59E7F1869E0FEULL, 
            0xE207C8D578750C9BULL, 0xCE3BD61CDF1DD364ULL, 0xC9009ACC0BEE040FULL, 0x9B749266C4F842BBULL, 
            0x3FD0A41E662E68D1ULL, 0xB30532BA5394AAF9ULL, 0xB0E2B5423016C80FULL, 0x934CBF823A8D84FDULL, 
            0x3A97C391C2766C60ULL, 0x4F8287CB9DADF98FULL, 0x5E439CF6F0D126B7ULL, 0xA51B831A9705C30BULL
        },
        {
            0xC58F4EBA40DF3CC9ULL, 0xF12BC13A4A90917CULL, 0xCF10C7CA73027E74ULL, 0x2171C6CADE25654FULL, 
            0x02C321062341D6A3ULL, 0x584198351454A4E8ULL, 0x799766CF4DB29DD9ULL, 0xC592573BA576B8E3ULL, 
            0x067961C5A0EC208BULL, 0x9BFC1C7FAC34BF3DULL, 0x1206E7591E0A468AULL, 0xEA7EB0293596FF9FULL, 
            0x0FC380C11F47ADC4ULL, 0xA520BF2009144C63ULL, 0xBB3FC68B8B3E745FULL, 0x56414CAD72AE7DD5ULL, 
            0xD0EF2D1DCE9A761DULL, 0x5D5DEB9A9AE458CAULL, 0x79888AADE09A644EULL, 0x8517B413C6F471F7ULL, 
            0x13491A62CD5D9D02ULL, 0x11442DFEDCCECFE8ULL, 0xE7ED43E98F39EC64ULL, 0x9701E378FB2425CFULL, 
            0x21C7F27EF2C544C9ULL, 0x34D90BA6E99205CBULL, 0xE00FB839675B0A84ULL, 0x2ECFEE3CDC0AAD7FULL, 
            0x2F961E820673E35FULL, 0x0C49FB05EE80954BULL, 0xF8DDAA2C1600D8FBULL, 0xC19B69A7611E91FEULL
        },
        {
            0x4AEF0B97EAE65940ULL, 0x4DDEBD56186C0F8EULL, 0xDDD7C93693BC233DULL, 0x44D181CC7A9E2339ULL, 
            0x1C8FB779BD68E649ULL, 0x5538329172338657ULL, 0xF5A63F35FDB1F2F2ULL, 0x19586DF3820FC433ULL, 
            0xC754412184B5CE94ULL, 0x2B93A6FAD695AFEFULL, 0xF6C0B7769A5FB3F2ULL, 0x1FE506DBC12C7B70ULL, 
            0x543A968A3640B97FULL, 0xD467C1569CA7426FULL, 0x68F33701F5263384ULL, 0xB86D278139FD5249ULL, 
            0x5B4ABBA0267F3687ULL, 0x9EF61152935B5964ULL, 0xFBB798468B5E41F8ULL, 0x36D056B7C40401FBULL, 
            0x88D7D6C83C8BD7BFULL, 0xC5419596F5C24958ULL, 0x08954D1AD0D1993BULL, 0x9109CA2BD501B60EULL, 
            0xB57603F297354E46ULL, 0xD4791FB4BAEB326DULL, 0x62F2B69ECF55C938ULL, 0x1CAE5F35BFA106AFULL, 
            0x933342E0CB05F378ULL, 0x4908D465581C3EF0ULL, 0x61995A0F3D5C0793ULL, 0xB1596E3631F7328DULL
        },
        {
            0x62E1D27DC642F21AULL, 0x38FD71527657EFC5ULL, 0x3DEFFCCEB3567A76ULL, 0x02EA2CB55A64FA44ULL, 
            0xCE7367059EE5B9ECULL, 0xC1AC8CB2C4A56B5CULL, 0x2981DC4C61E00BB8ULL, 0x993988376891B897ULL, 
            0x512E06AB12EA1304ULL, 0x6B67F4C711290143ULL, 0xDBE591F4AF99BA53ULL, 0xDA3F01931F158F51ULL, 
            0x396756B423533967ULL, 0x6B1AF98254F69840ULL, 0x8EF1578DD7FF01BDULL, 0x35A177612A17D20DULL, 
            0x49B02B0C2B038F49ULL, 0xE1E35E9F67B7955DULL, 0xCF04F71E048EE4AAULL, 0xB0677048DAADCE2EULL, 
            0xE53B8E2977B6E505ULL, 0xC43DDA27A791304BULL, 0x3FB5B672F0685DB1ULL, 0xF1D99F5AF0A198CAULL, 
            0x8AB4DBB6F9F12CEDULL, 0xC7ED320FE6E3C6BEULL, 0x552277709870066CULL, 0xF50F88EE2704D61BULL, 
            0xFE0F06D4D6975FB5ULL, 0x747C39D28127F4D7ULL, 0x39A885B9AD40F185ULL, 0x9FCF1EDCCE9A9271ULL
        }
    },
    {
        {
            0x624921C78FF1205FULL, 0x7052F9C0E5E46E4AULL, 0xB2CB6C98F645830AULL, 0x8E3D1647A141BB52ULL, 
            0x0F7CB16FD3BC6C95ULL, 0x86A49C3B98C6DE3FULL, 0xFEA010048909BF96ULL, 0x5877477092B4592DULL, 
            0xAB9F7E0F62D8B8DAULL, 0x8C189A313238D9F0ULL, 0x94EDE64C7B93B642ULL, 0x0419F0B68E889696ULL, 
            0x4E760033693B1B8FULL, 0x4FD68AFC6083D73BULL, 0xDBA36EB49158136BULL, 0x255DCBB07F232627ULL, 
            0x2FB6A49F058AA708ULL, 0x927530746159C39BULL, 0x2F28B8DFD64A37A4ULL, 0x6B8C8058281BBDDAULL, 
            0xEEDB2AB76C2155D8ULL, 0xEA19E28C1D07398CULL, 0x898ECFF85EF96759ULL, 0x622B88100370BCE2ULL, 
            0x8B29800BF64C7174ULL, 0x79DEC4611A6E1EC9ULL, 0x540122A998BCDF39ULL, 0x5DED5AF63A5A6912ULL, 
            0x74FA9B6BB5881B79ULL, 0xDDFE5770ADF51E81ULL, 0xB8821AE73124C04CULL, 0x3F1DB11EB043E9D9ULL
        },
        {
            0xCA44884DBAD762D3ULL, 0x97777A1F8012B689ULL, 0xBF093E841C894BA9ULL, 0x2C7ECFCF178BC2DFULL, 
            0x69721A64CA394690ULL, 0x59D48CF4045DBED4ULL, 0x6A0050F477BE31C1ULL, 0x70A1CA58A2124481ULL, 
            0xAA13F96E29430FC0ULL, 0x7DC4BE424D4ADF05ULL, 0x804940AF5F3C85FEULL, 0x472BBE76F9966336ULL, 
            0x69521A107ECA7246ULL, 0xF9F2AD48CB36EB37ULL, 0x459E6F0E1AFC9018ULL, 0xD4EE14B03C5B03ADULL, 
            0x96BDA8A6321AC9D0ULL, 0xB1604E046380D347ULL, 0x39FB4B2D6E11A166ULL, 0x62AF12BEAF4FC60AULL, 
            0x2E42125FA6C4211DULL, 0x0E10A2FAC28F76CAULL, 0x832178E81446BBB4ULL, 0x0E228444F7DDA69FULL, 
            0x41BEE3DF6B1AB1B2ULL, 0xA7912B33DAFF0485ULL, 0xB5BB2A3757596708ULL, 0x3D69F77607B4E5D2ULL, 
            0xC121420AFED69AF1ULL, 0x7D11F8F47C6ACCF0ULL, 0x031FA58FA8BC3A22ULL, 0x528063CCDDA5588DULL
        },
        {
            0x6E705A37C113BC3AULL, 0xBE1CB4A194211FC1ULL, 0x23D7FDBBC01A6B50ULL, 0x5498D26801C52A8BULL, 
            0x81D16B7A63028AB2ULL, 0xEE7FB67601B39940ULL, 0x687C76B38F30E48FULL, 0xC02C748E778D6948ULL, 
            0x9D71BA1A96EADA42ULL, 0x975B37FB761DBEACULL, 0xD3489E0F19B29E4FULL, 0xBC5B7F4FE2A449C1ULL, 
            0x53FC51D881F7E66FULL, 0x4E84F1D4CD8D5638ULL, 0x713C7EBB430CF2D0ULL, 0x4DAD6B7C7BC18B42ULL, 
            0x0C7D5CD510CD92BBULL, 0xAB62EA66E9A8A8CEULL, 0x1EFCE1D897FC1CA0ULL, 0x8D03CC67600C9034ULL, 
            0x6C4F44D6A970AA29ULL, 0x01C3938F47BB8056ULL, 0xBB493442B5E33DBEULL, 0x1CDF4992F05C6765ULL, 
            0x2DA8BE6BFDC78493ULL, 0xC3D45FA7C329A0AEULL, 0xD5DF377340421E38ULL, 0xCDBCC9B097BF376FULL, 
            0x33A88631E18E4401ULL, 0x0AF0154CA76BFD0BULL, 0xC273834210256A94ULL, 0x7A72B3AACEB95D2FULL
        },
        {
            0x45EA40062CF4AFB6ULL, 0x28AFF5428D6B29ABULL, 0x410E689D2BE0DEDDULL, 0xEE8CCDD91D20CE8DULL, 
            0xEBC1F2F2599C9DDAULL, 0xA974CB362C4261E4ULL, 0x06ED1B17B2C396EFULL, 0xB7CACF715EFF80CFULL, 
            0x5D35AB89F5AAF63BULL, 0x017F980C852E5E24ULL, 0xBE860E758D4318C9ULL, 0x35578857E3E2E375ULL, 
            0xB842C02995123B46ULL, 0xA2F2AFF7DBD5DBAFULL, 0xAACB70E9D4BC4429ULL, 0x383D9B0B50761C3FULL, 
            0x0ED55007531B89C5ULL, 0xFC19887480800D5BULL, 0xA731CD509126BBC7ULL, 0x245A1875ECD7310DULL, 
            0x89C3C4197C862D6CULL, 0x5EE58ABC6F3EBE04ULL, 0x3FE71938E4AFA555ULL, 0xAF1F1C96211C660FULL, 
            0xC6ADEBC32487DB30ULL, 0xF37A7B37A29ADCFFULL, 0x1490C3BA11CE2C17ULL, 0xB13DAB35B2382DBAULL, 
            0x794FBC4A4A8DF972ULL, 0x5E89F37E39C82208ULL, 0x1FE15CFA9C6F836FULL, 0xAFDCF1C5EC0DB470ULL
        },
        {
            0x00759F94CECD571AULL, 0x8C6E0AD85E796B91ULL, 0x15E1EC7D99963BBBULL, 0x6EA7B34BA3352D66ULL, 
            0x0BFBC8FEED3CCD35ULL, 0xD7DBEF98A39352E7ULL, 0x4FC854DD3DB36954ULL, 0xE72071A3A356807FULL, 
            0xEB968618674299FEULL, 0x88D2CA5D520021C9ULL, 0xFC0BF17A8935013DULL, 0x84DD76F5231DB798ULL, 
            0x0FAD83D768329B94ULL, 0x5A02DFD8628EE210ULL, 0x40CCAD3B2C194475ULL, 0x53548A8D64C73A82ULL, 
            0x94F461E2C5CC53E2ULL, 0x7628FA9EA7435328ULL, 0x07528DE57B60BF79ULL, 0xBABAD26D304E8106ULL, 
            0xD6D24CB4887204ACULL, 0x9CA6A0FA09909D42ULL, 0x0D908C7FC5478419ULL, 0x4686C218202F7A66ULL, 
            0x6937959ACFFF6C1AULL, 0xBEDC4369E969A48FULL, 0xBFC750B416B0DAE6ULL, 0x45DA9C0934E3A3D9ULL, 
            0xE820BF79738CF388ULL, 0x8A33CF821AC44749ULL, 0xB9F3B36E9AD1D53AULL, 0x805EE333C7AA98FEULL
        },
        {
            0xD698C1A6614D0695ULL, 0xA0C1139F490DDEF6ULL, 0x15D0CDA6D1E4A6C1ULL, 0x1C543A7CE2897C04ULL, 
            0xD6088A646A4A01FFULL, 0xFC436E5D6E3F33D8ULL, 0x1DFBD62DE0EB6AF5ULL, 0xC362629EB9948327ULL, 
            0x513C23B033A97A38ULL, 0x9E645782E0CEB160ULL, 0xCF0140AA34CE61D7ULL, 0x2B0A0CFDA77F9B02ULL, 
            0x3B6BE00C81012C36ULL, 0xE4F86205781E4A68ULL, 0x0755B5667C9C0A90ULL, 0x67368D94EB41A99EULL, 
            0x447081ED5D0FE7BFULL, 0x6423498BC8AC2BF3ULL, 0x14AE79A7B0E88AD5ULL, 0x87FDD7159F577290ULL, 
            0x94F716446E4656B8ULL, 0x7414BFE90019C084ULL, 0x9834BEFA7CF2CC3BULL, 0xF76C3B38629A9742ULL, 
            0x16212568C4F540CDULL, 0x7CD3E13894EA36D0ULL, 0x8417F918C7F55437ULL, 0xB3896E4DFC6A4E62ULL, 
            0xDAE1CAF255EAB5FDULL, 0x6451EB4E721B8A81ULL, 0x67DA8544A618618BULL, 0xFF5EF1FDD0BC734AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseFConstants = {
    0xFF2065F1D8E1ED45ULL,
    0xABC47E76A7EC97B4ULL,
    0x945FFEBD2B020B4AULL,
    0xFF2065F1D8E1ED45ULL,
    0xABC47E76A7EC97B4ULL,
    0x945FFEBD2B020B4AULL,
    0xA83B38D538EE86C5ULL,
    0xD2C01F7254C751C8ULL,
    0xBB,
    0x50,
    0xC3,
    0x39,
    0x1F,
    0xCA,
    0xCE,
    0x55
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseGSalts = {
    {
        {
            0xA33F6560FCE92174ULL, 0xD1572B00BDA52FD3ULL, 0x25F873D4BDE6D07DULL, 0x524E935F3594601FULL, 
            0x826FCCBABFF7C4FFULL, 0xC3193BD5A6C9FC25ULL, 0x3F1A7C652D6BB3C8ULL, 0x35550221CB33DEA1ULL, 
            0x89346D0BBDCB316EULL, 0xB4B9D42FB0BA0B16ULL, 0x2EE623919E9ACBEBULL, 0xF0143C6C0FA129ACULL, 
            0xFFD25E6A0E35D304ULL, 0xC4C0874A730F1B90ULL, 0xAD16C400CEF6DD47ULL, 0xEBD2E7BB20ACC761ULL, 
            0xCA405F0A5D6F390AULL, 0x17F0D0E55FD88341ULL, 0xD63E12A2F088275AULL, 0x8CFBA0F563D18276ULL, 
            0x781D8772D4A969C2ULL, 0xE0A38ECDAC377D92ULL, 0x8CADC36880493F94ULL, 0x3BC71F74800378ACULL, 
            0x67BE3442FBBAAABDULL, 0xED568FCC7AEBFC51ULL, 0x68CD8D8081995604ULL, 0x983F7E02C659015BULL, 
            0xBAF2F7C27F3A7D95ULL, 0xE28FE1F05264E326ULL, 0x71847DA73AA8F2C3ULL, 0xD964AE524D0C19E1ULL
        },
        {
            0x561F89538B92F05AULL, 0x8AA47B3B4D7A67C1ULL, 0x8CDEB56766E0F963ULL, 0x4A19CB9B995C03E7ULL, 
            0x408E3DD377F0DB6AULL, 0x1C10F3C11D9E985AULL, 0x3F7D29FC98D3F0E1ULL, 0x76B01B8B4623D919ULL, 
            0xC2256606A51E78A1ULL, 0x6324F64CE99E4901ULL, 0xB88F87472E290C85ULL, 0x8AF6DA045DECB07FULL, 
            0x2E94C8F3085A9001ULL, 0x51095B5DCC7E8AC4ULL, 0xDAC5C6563226AF30ULL, 0x7E9AD16F0AFD9F87ULL, 
            0x6628A40C8EEF458BULL, 0xB473EAEF17EEB34CULL, 0xB496978AB49B3054ULL, 0x9067613C1ED5686DULL, 
            0x03FEDAFE9ECF45F6ULL, 0x6D37F5A23BF18AA3ULL, 0xB45F69356ACF8341ULL, 0x378FEC1B3EEB83D4ULL, 
            0xADED7F2B3DBED0E6ULL, 0x627A8FCC340C4323ULL, 0x97123255B4AC060BULL, 0xEB72DE977484B0A3ULL, 
            0x2DE09B5C47264A11ULL, 0xCF65969BEA473ED4ULL, 0xA614654FCFDBCA2CULL, 0x370B3E0A2567022EULL
        },
        {
            0x830B7B901E95944BULL, 0x1D9D929DE637E76AULL, 0x81CD6CF0363A18E7ULL, 0xA4E6B268FC528952ULL, 
            0x6C86D0DCE6EA36FAULL, 0x537A84E9A605FED0ULL, 0x6C69E4B71EA89A5FULL, 0xCAF9B003FFCCB080ULL, 
            0xA87126C7B7745E1FULL, 0x8AE2F4DD4C7560A8ULL, 0x5E57D6D8D7C3B006ULL, 0xCD7CE2CB5D693184ULL, 
            0x32AA334087031507ULL, 0xCD60F253D3A23715ULL, 0x51880D5F7608C8D4ULL, 0x364A97746E05F335ULL, 
            0x81BF45837141BB50ULL, 0x21CEC6202CEFA907ULL, 0xB2BA57AD55EEFEABULL, 0x639DDB614293A5DEULL, 
            0x9920DB980A3315D3ULL, 0x3C1E5271B2FC8C84ULL, 0xA425586553B4391AULL, 0xAEDDBB0B5235C582ULL, 
            0x47906F5230B2DBF9ULL, 0x880EE444B7FE0DA8ULL, 0x4CFFB650F21615DCULL, 0xDD496C7069D6DC01ULL, 
            0xCE89C0A8B1B363F9ULL, 0x7865A302DDB90007ULL, 0x4E67074719B93E9FULL, 0x0FA934A9A15C2095ULL
        },
        {
            0xA1A4452E610F5842ULL, 0x60E8F28D3319F526ULL, 0xA7064147C4D66E17ULL, 0xDB2D0960CE9BA8B9ULL, 
            0xE3EC9C9CBC019775ULL, 0x0E2A6BF9EBD47657ULL, 0xB94220A59ED74542ULL, 0xA65C8B9178F298AFULL, 
            0xEA064E37B6274293ULL, 0x51F61946408AD5EAULL, 0x64DB8CD6E9F6A2B6ULL, 0xFBE60857FDAE5C80ULL, 
            0xF8C6628329A98E43ULL, 0xE521A42D5B3C3FEEULL, 0x0D770E92B5A5D1EBULL, 0x9EFA23AE19A4FA58ULL, 
            0x9C4B0AF52BE70DC8ULL, 0xF5C7AA768CCFE2D5ULL, 0xF16AC28B835E83D9ULL, 0xFC0DDC5A446FAAD7ULL, 
            0x0E4ED3EC7F828D36ULL, 0x6E2C35DA30293974ULL, 0x58BDFD1F490AA0DDULL, 0x5936507C2B1F03A6ULL, 
            0xCB357ECFCD67D3E2ULL, 0x3747A29441E6A4BAULL, 0xE211E6511AB1D249ULL, 0x7C553F0D8791ADB2ULL, 
            0x5F53A71834290F6BULL, 0xFF0BB7A4AAA9E4B4ULL, 0x944E8B5327FFFA24ULL, 0x0470EAE05AC31569ULL
        },
        {
            0x669561FE57F16C9AULL, 0x5846A0D0DF8F1729ULL, 0x304412DD56CD74A0ULL, 0x9D4276547A8F03C6ULL, 
            0x1B46E19B96F514A1ULL, 0xBF156AC5ED8E6F24ULL, 0x16C583889695CCE2ULL, 0x96835299DD711BCEULL, 
            0xFBC3E3966C6FF1DCULL, 0x9A142DC3FB4C76B1ULL, 0xF6F2D5FA1F4DE9C2ULL, 0xCBF17650A1CD1EF7ULL, 
            0x2E69B854C0E5A392ULL, 0x671865DD390539D7ULL, 0xB1F878697B4BD068ULL, 0x5B3F8550C5EBCCF3ULL, 
            0xC771A1BA6C56D5C2ULL, 0x4DA7B10C73556A42ULL, 0x66D2C6C030C72256ULL, 0x5EA1D83C14E41439ULL, 
            0xFEA6ECB466128C61ULL, 0xBC7497CDDFFFAD7EULL, 0x399F574130256396ULL, 0x22254EF2ADC58854ULL, 
            0x5C64E4519E2FD7D1ULL, 0xB146A795896AEC33ULL, 0xCF6598AFBFD8ED7BULL, 0x6AA2786627EFACCEULL, 
            0x8038AEB27E48ECE2ULL, 0xF7334DF4F67DF020ULL, 0xA441DC5EC8C5F71BULL, 0x21E71103DDFB1784ULL
        },
        {
            0x4D4A792270B04F6CULL, 0xD37ABCC2A11277CEULL, 0x7C3D73926AF4CED3ULL, 0xED27832A68FF537BULL, 
            0x900C8CD6515B824AULL, 0x66A42FC6232F4AA0ULL, 0xDA19EACA67DAC3FAULL, 0xC7C1E025274391A0ULL, 
            0x2AF97F5B807ED797ULL, 0x4131A8D3A3198DEEULL, 0x33BF1B3625847E1BULL, 0xBF308C7ECEC28E75ULL, 
            0xBDF8BC8216620924ULL, 0x18EA729105506D56ULL, 0xEFF9F83FB352E93DULL, 0xFE4DFC8418CCA99BULL, 
            0x0CB7C46488B8030CULL, 0x2799B52AB330C241ULL, 0x477A6FF47CE82E04ULL, 0x6ADF1DA7AC82745FULL, 
            0x306F052FE4FD0FE0ULL, 0xA58D6B8939BDDEC0ULL, 0x02080188B0D2C669ULL, 0x281CA5D69158204EULL, 
            0x3675CC3304E5820DULL, 0xE13266B46413E86BULL, 0x41195FD3C9613F6AULL, 0x43AD452909C277E0ULL, 
            0x99A2B2568D7A7C62ULL, 0x1C563F88313CC8CDULL, 0xA80EE865271C13DCULL, 0x0CFA2C327EF6E715ULL
        }
    },
    {
        {
            0xFA8E2600B3B98C14ULL, 0x4D17B30B43C910EDULL, 0x6BB31644B17D640FULL, 0x51FA220C4CF81C42ULL, 
            0x21908123CFABFA7FULL, 0x44022A11FCE033E3ULL, 0x14BE1C06A3178473ULL, 0xA838D15BD7DC3359ULL, 
            0x36D41F141C54F035ULL, 0xD86D848A1BC861F0ULL, 0x2E236C7E34C28FD7ULL, 0x5DF57808ABF7C652ULL, 
            0x07B521956920BB8AULL, 0x5D720E7BCA36F8DFULL, 0x78A6B4BA85DC098AULL, 0x77D8961EEB66FD87ULL, 
            0xEE71AF91265D401AULL, 0x9AA4B4328C38E3E7ULL, 0x412F1557D49A2019ULL, 0xFEA2D13031D8C395ULL, 
            0x08E261E3037D668DULL, 0xD58E2C4E7319E4CAULL, 0xAF6E7A0E0B0330D9ULL, 0x40B25264C0852D41ULL, 
            0x8489D5AE18B81081ULL, 0x423EB3BBE2C24D56ULL, 0x34CD1A793C0DEF84ULL, 0x314CC16067A60DEEULL, 
            0xC559510DFD37F664ULL, 0xB76FDCE9E7E8B7C5ULL, 0x2D282BD723551E67ULL, 0x41B6C9B8631846AAULL
        },
        {
            0x17D361342B2E7897ULL, 0x8F5D09214F3C6C58ULL, 0x6A44AAEF8CB1D4D8ULL, 0x52D89D5AD79DC1A4ULL, 
            0x5A52946CFD61DDF1ULL, 0x1674FFBC1A080EA3ULL, 0x63DA9A74E42AD52DULL, 0xD113400C4E0B9CBBULL, 
            0x8A452E51C4C2F7BBULL, 0xEB1578BA62B2E80FULL, 0xD044C8EB050B69E7ULL, 0x461429DC8E57727DULL, 
            0x60E898BDAB70F20CULL, 0x2CAF73978A62CEF4ULL, 0x3BC744C24EC2213BULL, 0x57E2AC29CA3C8D25ULL, 
            0xF11188878333FFD5ULL, 0xF33B79DF58F86DB8ULL, 0x16E84FBFDABD34F6ULL, 0x2D974A7E0E43C4BAULL, 
            0x1493E8FDBA4567A2ULL, 0xBD1C4BB2521135C2ULL, 0x8CCA7BDE2D8D9E19ULL, 0xCC74495E5BD22FAFULL, 
            0x7847BAAA43097FA1ULL, 0xDAA1FCEF33F725E5ULL, 0x5160791915DA8EE0ULL, 0xAA699A6CB88F00B6ULL, 
            0x150D4C72DC1D5EDAULL, 0xA8CA11EB60901247ULL, 0xAAF606E95C47A23EULL, 0xDFDF4DA36AC1917DULL
        },
        {
            0x54F82631BA2C469AULL, 0xF6C5F2F5E5624D9AULL, 0x8097B948A69A9BE9ULL, 0x99AF016DC739AC3CULL, 
            0x9FFF75E9F8CEA404ULL, 0x45AAC871E99D64DCULL, 0xE3323991F5FD3483ULL, 0x2D2F5753DEBE30D7ULL, 
            0x24C34C10AE480978ULL, 0xFF31438D665BEB74ULL, 0xF4F429EB957DA6CCULL, 0xC692BFD39F2D4C90ULL, 
            0x09ADA1973A108DB4ULL, 0x8279A71F8FC18D6BULL, 0xFA6C14642F4828FDULL, 0xAB8CD0E4300CB16CULL, 
            0xED4D7949F60CFCECULL, 0x7CA3708332A2E59FULL, 0x3702633BEFFBBCE9ULL, 0x1BDA3A49BB0BBE97ULL, 
            0xC843DFDFC87BDB0FULL, 0xF2846443197F7902ULL, 0xEB6A722F83A1CBF4ULL, 0x29352167C0D20D13ULL, 
            0x70A81C653B4C7EF7ULL, 0x471B57226671CD59ULL, 0x6F5E5992ED0E9441ULL, 0xD7CF308DC9EFD2BFULL, 
            0xD1E11F4FE3E16231ULL, 0x1F3D384FDAD8F9CBULL, 0xBFB0CFC3EDFD44EEULL, 0x5A77D59F2837E862ULL
        },
        {
            0x75D979EBBA3C2961ULL, 0xF2B59B300E9DC866ULL, 0xC042CCBF520632FAULL, 0xB6D065D3F15F48C1ULL, 
            0x466AA6B08810A986ULL, 0xAA695642687D620FULL, 0x17EF6D20858EF0D5ULL, 0x0F22246C4C23FE02ULL, 
            0x542E474E27D0CB28ULL, 0xEAF525EF31B8AD21ULL, 0x9C8F705F59D3AC26ULL, 0xCAD0FADC173BCF37ULL, 
            0x0F327458EB5F566CULL, 0x97FF2E22D294CE7FULL, 0x54F51D59DB9A6167ULL, 0x9541346113D4339CULL, 
            0x2E4B98D733A4D0D7ULL, 0xAF643E798D0A0C71ULL, 0x15FF939EC021BC7AULL, 0x00603E750D15D9A0ULL, 
            0xE51142153D0E565DULL, 0x6172B473280C688CULL, 0x5DACFE196AFE3F24ULL, 0xA06B4BE4120B0EA9ULL, 
            0x908A67B9D082CD59ULL, 0xE37FE036A1A5A873ULL, 0x1C97009A4F0E140CULL, 0x7FFD13A0FA3CA968ULL, 
            0xD636A7FC5A0614FDULL, 0x0FD22CBB1DF5E4C1ULL, 0x93139DE7828674E2ULL, 0xEA600879E4C9EEE1ULL
        },
        {
            0xFE26D0364F3945E9ULL, 0x2704720D4FAA89C5ULL, 0xBCA9036A4F58CB80ULL, 0x5CDA8645F9F983F6ULL, 
            0xD84CB70BDE14F21EULL, 0x91FE75BF61023CD9ULL, 0x5EDD99066E5AE60BULL, 0xB31C8B5406D9805BULL, 
            0x7860DBE62C5EEBFFULL, 0x2EC3BB46E5D33774ULL, 0xD8BA1A1CCE3FF04BULL, 0xEBA5FE1720AC545FULL, 
            0x723E400D70CAF0DCULL, 0x2574FBBC8C53F3B6ULL, 0x71C1A6B432D61D3FULL, 0x903D313069A60C01ULL, 
            0x4943ED1000E1DF96ULL, 0xC87E316CFF9423F0ULL, 0xF5CFBEE8725E2EE6ULL, 0xEB11B39F315D357FULL, 
            0xB00EFC5AE96AC0BDULL, 0xEFA3DEF474591662ULL, 0x7A31CDCF97DB4038ULL, 0xDFC8C028C4AF4BCAULL, 
            0x9270ED778D43FFD9ULL, 0x00CBDECCEAF070B5ULL, 0xE45854EC83E2DFFFULL, 0x3B6EF2C164F5F1F9ULL, 
            0x4BF6EB462C713518ULL, 0xED15C0CCCD4DA32EULL, 0xF050C44456F9E4CAULL, 0x2D3670E6A97647BFULL
        },
        {
            0x2CD39BE11FB5E7D0ULL, 0xCEA261D726C31345ULL, 0x1986E46AEADBD3F7ULL, 0x29BF0A472B03069AULL, 
            0x038C82E3AA2BBD81ULL, 0xC96151DF58463A99ULL, 0x59DDAE7B512CE637ULL, 0xC16AD5F6581444D4ULL, 
            0xCCFAE7FE88DE602BULL, 0x352F7038CC7DF413ULL, 0x0742468F5843CC11ULL, 0x40DD0FE33A5660D6ULL, 
            0x2DE3CB713C886857ULL, 0xE95F6DF475562D6FULL, 0xDBE76F63A24B6EADULL, 0x820058187C9EC2FCULL, 
            0x1EF5AC2E35C0C07DULL, 0x414BF3F234BD63B0ULL, 0xDF7D07E8414707F4ULL, 0xAE91AA270D957630ULL, 
            0x33152F34B295B8B7ULL, 0x6B60B8C2BD847EF0ULL, 0x4791A2C4B2E51E7CULL, 0x8AEF38751CA2C434ULL, 
            0xB1E02413DD0903E9ULL, 0x3FBB5C410BB8F54EULL, 0x48C3078D12944C6FULL, 0x8499324EE7CECBAAULL, 
            0x16FEAE6122485637ULL, 0x80FB1419A5263110ULL, 0xA3061D0FA472FAE2ULL, 0x845C5FB4F7D03A3FULL
        }
    },
    {
        {
            0x1BAA5C9EF7CD2B1EULL, 0x7D28FDB8EAC6CDD3ULL, 0xF262B5AB50380DD3ULL, 0x2B6B05D0849BFAE5ULL, 
            0xD105FF3588926086ULL, 0x7A73FC88C56410CFULL, 0x12242F3E38D2734EULL, 0x85C8B5698E211B7BULL, 
            0x6B1810915F63326DULL, 0x4378A61E50A9BC3EULL, 0x2198F9B311B27CAEULL, 0x3097F85AE990BD13ULL, 
            0x05B787C7C6410BFDULL, 0x55C3F41DAFAC1CCFULL, 0xA442E99AA5C2A502ULL, 0x75442BEFBE4EBC68ULL, 
            0xB03DC5381BA50B19ULL, 0x18B4D2767D246C20ULL, 0xBCCA179AD7C18FCBULL, 0x613D6DA8ECEC8D73ULL, 
            0xB860108BF457FE90ULL, 0xA89EB9FC6BE95A34ULL, 0xAD8E2F07261B7028ULL, 0x9B6FAA2577AA48CDULL, 
            0xB00B184DCB03C5C1ULL, 0xEE69CEFC8D6A0A11ULL, 0x28294A7E8C19270EULL, 0x9E00A48B10D815A4ULL, 
            0xC828D974094F82CAULL, 0x65753EC3C3767A7FULL, 0xE4EB01A7EC7557D4ULL, 0x885D96D70AA5D704ULL
        },
        {
            0x55D124AFDFA21234ULL, 0xE8918F5E7706AEDAULL, 0xF7BEE9990781DF71ULL, 0xC8083AAE2825AF87ULL, 
            0x71A265AA661C27C4ULL, 0x532A8976D3118A56ULL, 0x49C724DB18CD0B1AULL, 0x4D157531604B29B8ULL, 
            0xFB7A39EC10B8EAB7ULL, 0x1FFADE748B4DC7EDULL, 0xA51A95A80694B803ULL, 0xCA17B8A8E2D42990ULL, 
            0xCC8F9E5DFABD3800ULL, 0x148BFD40E2173B6CULL, 0x9B607E94C90BF507ULL, 0x2ED5A8DB7941A986ULL, 
            0xA2D520D475A498D2ULL, 0x3F8E43A533E16E39ULL, 0xA4D0516636C42465ULL, 0x0A7CC0E955B5DC42ULL, 
            0xF0A2BBCD8E73507CULL, 0x7EDADF2E27E15E3FULL, 0x49CABCF3E0524B4DULL, 0x44E31DEC87C55714ULL, 
            0x3394C4E7DC61E2BEULL, 0x7F46F91BB7FD0418ULL, 0xB22C3AC84C521029ULL, 0x0B40A25355D8AEABULL, 
            0x6CCE58334F3886ECULL, 0xC940A8101599BAD4ULL, 0x87FEF84C7ED56F6DULL, 0x6BDF0402D86386BEULL
        },
        {
            0x61B950A6EA7E543FULL, 0x2BD957DF252E6647ULL, 0x2F37E7B216094FF2ULL, 0x3086129EE09219C8ULL, 
            0xA2FDF4240A6742E8ULL, 0xC55D277167E36041ULL, 0x16A2D760B0989A3EULL, 0x7787D52AD51A2D04ULL, 
            0x01E5206861F2017BULL, 0x669EAB735FAABC85ULL, 0x0A69FCE6C4DD8556ULL, 0x85925F41A781FA2CULL, 
            0xB3587F1F22376AE2ULL, 0xB2EED6A22E6F3561ULL, 0x3BD1B9EFA7421A54ULL, 0xC0071ED0A5E65EA6ULL, 
            0xC88A882D44F09CD4ULL, 0x17470441C881B092ULL, 0x202CD135B451E0D0ULL, 0xCBF2359A544B97EAULL, 
            0x10D6483F8573D502ULL, 0x6B8DA132468F4602ULL, 0xB49F1C2E19D6A733ULL, 0x61F0C8A2E4533669ULL, 
            0x906AE2B2D4A61B88ULL, 0x1D87D6184C6BF8BAULL, 0x1893D3F1BEA2E04FULL, 0x02086E19129371E1ULL, 
            0x771475E1F9D1250AULL, 0xEFF392C81DD27013ULL, 0x11820EBB7090635CULL, 0xB50E5A8EACA70EB2ULL
        },
        {
            0x8A050BC2CB9019D5ULL, 0x24B104DC84C3FE1CULL, 0x7940CB77ED5D89B6ULL, 0x8E60FF76D0911CD6ULL, 
            0x6BB45A56DF724BB9ULL, 0x1C1DB83BAB777104ULL, 0x6D3F77DEA2C46284ULL, 0x8F75231FD07BBA81ULL, 
            0x84EB09A0D0510E62ULL, 0x591774E28C77EFE0ULL, 0x4B28F5B874864010ULL, 0x7F1A214B5F6CE40DULL, 
            0xD5442A869E589D49ULL, 0xAC2A49F230E5B338ULL, 0x4450F306470400F2ULL, 0x667D92A654FD3C03ULL, 
            0x569D415A14D714C1ULL, 0xC566DDF432C8895BULL, 0x51738D2EBF163392ULL, 0xC5151975415D2323ULL, 
            0x55C434B02ABD359AULL, 0x4FAC626223803889ULL, 0x276E52E50751A86CULL, 0x5184A9D79433E30DULL, 
            0x1A025BE85B5FF76BULL, 0x240BE2CCF9091DE2ULL, 0x057CA4417693E9B1ULL, 0x1394D6DAB551A71FULL, 
            0x021D467BC7232F51ULL, 0x827FA991E687559FULL, 0xB924D5054301C526ULL, 0xF68CD72878540B33ULL
        },
        {
            0xE656D41EF9951595ULL, 0xF83AE0B1B24C6134ULL, 0x4FB45245A320F374ULL, 0x0B4BE04AA5BB16E0ULL, 
            0x7EC86E0FA16CAA4CULL, 0xB0494AD93F8C53C5ULL, 0x05A6106C8A8A49C7ULL, 0x1FF9B470421F1F41ULL, 
            0x545470F4B0F9BEA7ULL, 0xE25279FC08BB3C0DULL, 0x3EB8343531EECACEULL, 0x2CAAAE3C20B49D6BULL, 
            0xF06CDF8765EDB3BFULL, 0x004888F57D1927A3ULL, 0x22AE3745B9EB083FULL, 0x5487D7E5A4A9BF2BULL, 
            0xFB4726265252779CULL, 0x908FF159F768595FULL, 0x002F7C844BD58974ULL, 0xD2E867BBEC3C2720ULL, 
            0xFDC34758ADD221ABULL, 0x530E2E0885A6D406ULL, 0xFD62480E9F2F04D7ULL, 0x497BE6A38D36A832ULL, 
            0xAA75291D144D0495ULL, 0xE7CF8C8E7D977065ULL, 0x9B2ED3A87BFD5259ULL, 0x4950282BACC4244EULL, 
            0xB8500EA712A3B674ULL, 0x4B1BC73E70690E6DULL, 0x6DF63A4A92082833ULL, 0x0987069A7B5EE8EDULL
        },
        {
            0xB92B95088DBBD510ULL, 0x47A76B9C5BA6E57DULL, 0xD01353781776DD3BULL, 0x6ABE4FEF70DDFB79ULL, 
            0x9DB965AA527A3098ULL, 0x3C4DC463D7570464ULL, 0x9BE4EB6D1E646B7FULL, 0x387197CF43103703ULL, 
            0xC81F2F826962FA30ULL, 0xAFEE1CB808CDF872ULL, 0xA8D36906DF78F680ULL, 0xDF33DFE2DE5B9A26ULL, 
            0xBCFE51411F954612ULL, 0x04C1CA006D291E99ULL, 0xB276B763F122BA02ULL, 0xB14158BBFB320A40ULL, 
            0x5D9A9B9979F3D38BULL, 0xB039D2AC4DFEF164ULL, 0x734E2AD77A58396AULL, 0x0188ABDAE7E05E8DULL, 
            0x2935B84A967DDAEBULL, 0xE8F417A537481413ULL, 0x5AA59822082E0C15ULL, 0x1F88656146FB1295ULL, 
            0x6CBCA50B381FCA7EULL, 0xEF6F4CC11550F093ULL, 0xEADDC61CD55E7FF4ULL, 0x2BD09C45857D9ECDULL, 
            0xE2BB7E93E124B427ULL, 0x6642D8559E330FA0ULL, 0xB33CFFE69D7A5813ULL, 0x3B3BF94451EE04F8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseGConstants = {
    0x57AE211EBCF5E56DULL,
    0x5F0D56BB53373E21ULL,
    0xB9D41E89903EFFE8ULL,
    0x57AE211EBCF5E56DULL,
    0x5F0D56BB53373E21ULL,
    0xB9D41E89903EFFE8ULL,
    0x6BCA9501D5734A79ULL,
    0x3900663FEB45EC19ULL,
    0x11,
    0x27,
    0x8E,
    0x67,
    0x14,
    0x39,
    0x02,
    0x11
};

const TwistDomainSaltSet TwistExpander_Regulus::kPhaseHSalts = {
    {
        {
            0x45EDCC6CE6C03EE9ULL, 0xAA27E9ADAE96A48EULL, 0xEA03D115E2E68248ULL, 0x1E40B580D7936818ULL, 
            0x0BCB2B7E539168BBULL, 0xDA77C51797E22EFDULL, 0x8D14849125AABDC8ULL, 0xD0A33CD4C21B1C6DULL, 
            0x656DC8F31E00E7A5ULL, 0x9E83918FA8B63AC4ULL, 0x624F9433FB9B7AE6ULL, 0xF3BA4D8BBF45B7FEULL, 
            0xA42E0B87DADB0947ULL, 0x238B4A0ACD024AEFULL, 0x7A015C52C8F76DD4ULL, 0xFA0110DACD9F55EBULL, 
            0x0A7B51A39D2CA51FULL, 0xCE730BB5F51624A0ULL, 0x619D6D3C94839E87ULL, 0x40180CF6074D54EEULL, 
            0xD24D0FBC4911CFDBULL, 0x3399AF0E11B662E7ULL, 0x4060A5A64BE13E59ULL, 0xEE72CF7B43B6F218ULL, 
            0x5EF9901CC7B6703DULL, 0xA915BB8DA97D1A56ULL, 0x38FADC11B2417FEBULL, 0xEED8D370FA7B08F9ULL, 
            0x706EB80AB1A86BDEULL, 0xBC8D7F17202ABB41ULL, 0xD520CFBB40DE6A4BULL, 0x9443563D3EBF8DDFULL
        },
        {
            0x51214EC676DCB71FULL, 0x11D73353C09198AAULL, 0xA318577B002B3129ULL, 0x289A6A7A21467EEAULL, 
            0x6AC3D8467257A217ULL, 0xF5A9BDF465142C5FULL, 0xCA7E6860CBE6865CULL, 0x3F5CAC465843F232ULL, 
            0x9E21D58613C5BFD3ULL, 0xA9BE4C56582C524EULL, 0x172F3D5FE0A413A0ULL, 0xD1CBA6524C993AB4ULL, 
            0xDFD9451A22A706A0ULL, 0xAC28C237DA2D4F0CULL, 0xCAC76FB96376B434ULL, 0x95A7C6E234D7721BULL, 
            0xDAE725927581CC21ULL, 0x8689C7352F3D52BEULL, 0xB2B0B19454AC758CULL, 0x97FFCF9B3D38CD89ULL, 
            0x9EFD2E1B8692EB29ULL, 0xE27FDD37420EA453ULL, 0x1889CFC3E3B5BBB3ULL, 0xCD65E9F935FE5483ULL, 
            0x3DF540C1C24AA9EAULL, 0x035193A9C303DCE2ULL, 0x81135CA94070F53BULL, 0x2A5BB4B99ACC804EULL, 
            0xE26EB551A386BFA1ULL, 0x97F1918695B69B6DULL, 0x644DF58D404A67D9ULL, 0xEFCE6DBB3CA74755ULL
        },
        {
            0x1DFA65603E860F04ULL, 0x802A404E6457DC1BULL, 0xB83D26895CDA582DULL, 0x220B0031DC8C5BBDULL, 
            0x1A7B37B8406E7EBEULL, 0x6868BBB65AD6C6CAULL, 0x665094010EC76B39ULL, 0xA6494E445A18ABA0ULL, 
            0xA7E0080744051479ULL, 0xD6587E98CA6A3ECFULL, 0x7575F1D956E6D22CULL, 0x777C1AD5B84EDBD1ULL, 
            0xA59CBB4B9B6A305CULL, 0x46353C6D27FA05EBULL, 0xEC3417EACE25496EULL, 0x4557C4AF2144B9C2ULL, 
            0x21DD7B57CE869E9DULL, 0x0714CC915F06F997ULL, 0xD87AA3C9164658A7ULL, 0x1FAF3538384B6EA6ULL, 
            0x7A956F5A06EFE2F9ULL, 0x809460F04480C1A7ULL, 0x97C9FCD2F9E3D745ULL, 0x2C6C5014E3C93B76ULL, 
            0xF90016C146212A80ULL, 0x19448117B99AB2ACULL, 0x6BFB3E4AAD963447ULL, 0x2CEB77DFCF0EE10AULL, 
            0x8D9F1CC37AF3E6F2ULL, 0xD0F15B0A24054A50ULL, 0x9789645D5963FC02ULL, 0xA5BE950C4695856FULL
        },
        {
            0x68FA1CDCCED8637EULL, 0x523662982F843366ULL, 0x46D6164B842BDBE3ULL, 0x61D95F2178A8ABB8ULL, 
            0x2E266033EAC590CDULL, 0xAE7D47BBAFC9C5CAULL, 0xD865FABAC8DE487AULL, 0x588CF1E92FA2215EULL, 
            0x95FD5413ED13EAF2ULL, 0x81BCEED923475215ULL, 0xD43E391E8149A5F0ULL, 0x79D6BFD674132CD4ULL, 
            0xB3F6A309CFB7810CULL, 0x7361AF98ECDFA591ULL, 0xDC5C23DFDB7ADEEDULL, 0x30FD84A8C4142520ULL, 
            0x4C723D25E37AAE96ULL, 0x199E10592E33F4E5ULL, 0x62CF086BA76BAB67ULL, 0xA5BC86CA3E81B8F8ULL, 
            0x5082F6101C5E1450ULL, 0x9020D7745DBC8DBAULL, 0xC766961D27D4CBF0ULL, 0x5CBF199BCB971B79ULL, 
            0x7720302C32963076ULL, 0xD356631970129DF7ULL, 0x23AE607F836079F3ULL, 0x9225245A90028542ULL, 
            0x877682AD239C9A7EULL, 0x168371C4C8DEE9CAULL, 0xE3B0E7EDF89588FEULL, 0xDF807DA048C0CFF1ULL
        },
        {
            0xD06D0A9A4A718F30ULL, 0xBCB7BC3BD801CCEEULL, 0x40FD9245320090E6ULL, 0x8F84CD5A4D1A00BDULL, 
            0x27E65E32C335A045ULL, 0xCDF25A0FA86C4506ULL, 0xD6042FF01DC1FA03ULL, 0xF36BA8135A059E15ULL, 
            0x24597C84C19025A9ULL, 0x66871398AE57AEBEULL, 0x52C36C9C3B846398ULL, 0x9E82C09C9085DEB3ULL, 
            0xEC0563A01C4E9A32ULL, 0x64AD66849F4C64EDULL, 0xDCA24F0F5CFF94A5ULL, 0xAB751A8AC65DF551ULL, 
            0x48A782BDE853CC3EULL, 0xAB6E831F50DB5AF4ULL, 0x67B4F315C3651058ULL, 0xE11D4AAB29956884ULL, 
            0xE618380DA841D335ULL, 0xB9455EA4485CCFF6ULL, 0xA5CABA1F4D05576FULL, 0x55EE0C30E042333CULL, 
            0xCB40D06F3623F963ULL, 0x3178D3763CA3A3EDULL, 0xBCE46C38C3475C92ULL, 0xBEC24C026728FB4AULL, 
            0x3C951DBA9E092B23ULL, 0x37FA553298BDE946ULL, 0x66098EE6F23A0891ULL, 0x44E5A6CB442D2102ULL
        },
        {
            0x6835EF75845339CAULL, 0x63036238F4D74FF6ULL, 0x6237146BAC427A8FULL, 0xF708A286E73560CFULL, 
            0xAC970998EDC95518ULL, 0x81040A9C9B0D1197ULL, 0xEDB389C1C672F637ULL, 0x4826FC2A40FA5E4CULL, 
            0x3CAC8879AD1E0C3DULL, 0xC1741ED258C6D7B7ULL, 0xB89161302D805ECEULL, 0x8E00770CEF737A4EULL, 
            0xAE4D5986923D1EE0ULL, 0x2F5D5CB3A2D02AC3ULL, 0x71B9A30C1DC4EB8DULL, 0xFBF16B664D968EBDULL, 
            0x1A3E868E64F49CB4ULL, 0xF94568F29D5AF0F6ULL, 0xF33A6E6BBF1505E0ULL, 0x2D1FBEC990C3DF24ULL, 
            0x9FE1E8E92DDB7EE6ULL, 0xE3DC9D5E70DFA2B3ULL, 0xFA7455FB7BAD8892ULL, 0x7EE046E1F8A060CBULL, 
            0x7811C5301B3A8878ULL, 0x705B7DA18AA7B77CULL, 0xAC47E727252FAF4CULL, 0xEF3962D25C0F09E4ULL, 
            0x65C10C75F9D0B88AULL, 0xF94E7DF587334928ULL, 0xF0088E4472D78FB3ULL, 0x919B77FFE5A256EDULL
        }
    },
    {
        {
            0x9EA30125813A0401ULL, 0xAAE64096B7148148ULL, 0xE217270517E9CCF3ULL, 0x6495EA36B56A739EULL, 
            0xD845084F49C7AA96ULL, 0x90902F1731948E94ULL, 0x8A13C787DE293249ULL, 0x7F67F66E095AE327ULL, 
            0xD5F4A9689903E5BEULL, 0x65D8A2D1C55790F7ULL, 0x9144CFFFBB6180B0ULL, 0x1422154575C3F9E5ULL, 
            0x8B910CF5A3FD4B87ULL, 0x1E02E2E4C1084A97ULL, 0xCC89DDEA9DF1705AULL, 0xA224FC5CF4E1CE2CULL, 
            0x09EF101D8D1364AAULL, 0x339C92ED67158802ULL, 0x7BF75CBF234B3E6CULL, 0xC6762BE39BB77B57ULL, 
            0xE850975F9DB0CB22ULL, 0x924E8B8BDF823E4FULL, 0x989AABABA6E70F53ULL, 0xEF49D16CC869989CULL, 
            0x617E2E9B4CB3C4A0ULL, 0x6D0B627844C8209EULL, 0xA74F07392D71C90EULL, 0xF2645F4A061CA6E8ULL, 
            0x54E906B876E3F402ULL, 0x7469702D87484558ULL, 0x94836D5130D0C992ULL, 0x64CA0A39092BE10DULL
        },
        {
            0x5A01257915E40755ULL, 0xF67BD6718A68048CULL, 0x32EBD0A5DAF95DE6ULL, 0x0F5F5CEF391A9441ULL, 
            0xAF413561A263CF22ULL, 0x2329D6FBC6ACBC7DULL, 0x8DF25B16805CD974ULL, 0x62540282DB868490ULL, 
            0x43F84C88125A77DFULL, 0x71592F0BA13100ECULL, 0x047CE1F06FF1AF09ULL, 0xEEF2FCDCCCF12004ULL, 
            0x37D1B69F232C392EULL, 0x32A01B0C92F55389ULL, 0x9FD18E070852BFBAULL, 0xE33CADF298A3A67EULL, 
            0xA2629E16036A8BAAULL, 0x4C02399BE94A16D2ULL, 0x00235BD8284E0230ULL, 0xFAD8D468CC717F0CULL, 
            0xEF46E511844FD1CFULL, 0xBF6B911A7307643DULL, 0xEB8E91BB6FE81F05ULL, 0x30154E379D874B79ULL, 
            0x3FB35EF0EE09A61FULL, 0xC412794CF797B6B2ULL, 0x4A609DEDA2F69A91ULL, 0xA9441D1F668D990CULL, 
            0xF3471A6D91EF3D2BULL, 0xDED66AA6E461FCF6ULL, 0x6DED06575E5AF37FULL, 0x9C2C2579AEBE6F92ULL
        },
        {
            0x8459829F752D933DULL, 0x601FFAEEFFD68AD2ULL, 0x0D49884B77549169ULL, 0x05BB2260CA96BB72ULL, 
            0x5FEC7B90C4371F13ULL, 0x1A643F8200BA6EEDULL, 0xFA045E0161A20948ULL, 0x2DDB287FF9C680FBULL, 
            0x745A766FF975D979ULL, 0xBDACFB44CD372C64ULL, 0xB35D16133AC059AEULL, 0xA359757068F331B7ULL, 
            0x03D19E9A898B5553ULL, 0x0C05A622CFB1B531ULL, 0x1BB8E6A177EE2F64ULL, 0xCD67991E77D95EE0ULL, 
            0xE3122550B0F590BCULL, 0x2C1C3AEF83D97D8FULL, 0xBEC6F0C7BE7B79A8ULL, 0x65D0839875CF22DDULL, 
            0xB6806EB5080D6A0DULL, 0x2DAFD3612F79ABD4ULL, 0x2FDA88CEB5DAAA60ULL, 0x70BBD6F55CA14F88ULL, 
            0x8871C7E00118B443ULL, 0xC1C79F0439A0FE59ULL, 0xBEB36AEDC720458CULL, 0xFDD8CABEBAA0F3E6ULL, 
            0xDA31E2CB8F4C1735ULL, 0x387EDD2D26FD6B96ULL, 0x815D3F15CF1EBFA1ULL, 0x30B752B462F4408EULL
        },
        {
            0xABDFBFE8AE75C59FULL, 0xEE096C9D35604DE2ULL, 0x7DC265148F64EE60ULL, 0x65EF2A3CC99B8FC9ULL, 
            0x5B9AD7D797DB5FA6ULL, 0x8D83C487C3EBDFBAULL, 0xCE371FD21067589FULL, 0xDFAFEEB83C89EDDFULL, 
            0x27F00DBDC594E997ULL, 0x16F7C801F70B2C6DULL, 0xAC984F23A3A783DDULL, 0x07EB242FEFBBB329ULL, 
            0x7D36720FFD9BEE5DULL, 0x34F8603869AF4553ULL, 0xDADE69012713EDA6ULL, 0xC42E588564098911ULL, 
            0x032267E8AE77F84DULL, 0x4EB4953FDC9DBCDAULL, 0x6AE35E00CD0BDAADULL, 0x6AFF83358B3B75E7ULL, 
            0xB17403B4C46D4C22ULL, 0xDA30BB362F2E3609ULL, 0x8CA5975D7A771FC8ULL, 0xD030ADEBD8C6B0A9ULL, 
            0x8A37C4E8E021C9E8ULL, 0x20AE992ADCA394FFULL, 0x8913616C0243CC34ULL, 0xAD0EC0F3C51CAF51ULL, 
            0x434FBD27629A93DCULL, 0x2122C7F961162380ULL, 0x6243DE164FC613EDULL, 0x6F3755C172D144E7ULL
        },
        {
            0x2942D260BCBFA45FULL, 0xEAD1056D1EBA06B6ULL, 0xA8C838369D570150ULL, 0x0359A90E0099BF00ULL, 
            0x8878B7619BFF8A79ULL, 0xAE7AB7E15F88DF87ULL, 0x756DB9DBCB5432FCULL, 0xA4870887DD027A44ULL, 
            0x57E2EC92030C30CBULL, 0x54DE49F1F9558603ULL, 0xE2DB146F2AFE669DULL, 0x4BDA56B97DF6FF35ULL, 
            0xF573908290F06579ULL, 0x118A569B0B75EEEAULL, 0xF9E9047CC32FC287ULL, 0xDDA78B8CAECD0B45ULL, 
            0xB01AE7A3BEF4B548ULL, 0x0F17E2184B76328BULL, 0x3F30324BD8B38212ULL, 0x5BDFDE5A59A4785BULL, 
            0x9C576A59D8F14FB8ULL, 0xB19EE3BD65FFE4B7ULL, 0xE896983F94865F58ULL, 0xFAB9B862971F5579ULL, 
            0x20E6D925C5AF5C12ULL, 0xFAF0B9A853AC1569ULL, 0x58578D12DF911903ULL, 0x89AB2AB404C0C9D8ULL, 
            0x503B5993CEBB3EF0ULL, 0xA12DCA1F90945542ULL, 0x8A9D250640BC3423ULL, 0x32983B730E91442BULL
        },
        {
            0x229A26BC7AD7E5D3ULL, 0x54D78182585A4CDFULL, 0x523E2E4882674C65ULL, 0x2B9DA43FDEB117D3ULL, 
            0x6E1221966CAA9018ULL, 0xC7783A9288F9A00CULL, 0xB448384BAE4C81E8ULL, 0xDFD93ABE2A959C3DULL, 
            0x0AB99AFD9A5547D6ULL, 0x8AE43786F1CA3089ULL, 0xD0C3A97621BBEB77ULL, 0x2E04AACF94B5F118ULL, 
            0x7CDD1479FE276D11ULL, 0x42121F4C9270E424ULL, 0x09D0E416BA468E7EULL, 0xD418A446445ABBA2ULL, 
            0x9CE28B0CC5C232A8ULL, 0x1B398A48214C9BA4ULL, 0x77356281C559705FULL, 0xF3B3609CFA61DF71ULL, 
            0xEAC3044F4F331B81ULL, 0xD1DE24D8B7E4FB92ULL, 0xEE0F00EA5A599916ULL, 0xB5F57B5D55386298ULL, 
            0x6EF42CED08870FA1ULL, 0x523EB413B9727429ULL, 0x9BF2CD1F1AF30449ULL, 0x5C61C3355292C9CEULL, 
            0x30DDF91F78BF433FULL, 0x50EA7101A14BF840ULL, 0x9784FFDB4864DA65ULL, 0xC9E1F16920C09F6CULL
        }
    },
    {
        {
            0x51B4A507C72F137CULL, 0xEBC2B7D892688BC6ULL, 0x40CF56DF464AE915ULL, 0xA80F28129D3D51FEULL, 
            0xDE8EBA6115A9B157ULL, 0x026A72DAA7A633C6ULL, 0xA170C5B6F237EA7DULL, 0x4F7E647E8142FD2FULL, 
            0xE236B17989C16C40ULL, 0xD961C10BB0242B93ULL, 0xBE360806A0F67818ULL, 0x93A8B1E22DF60945ULL, 
            0xF4012E512D76E8C8ULL, 0x76139FE6A8E2F6BEULL, 0x962C9DFC6A90FF93ULL, 0xA3CF3F079BE674C2ULL, 
            0x1E58C33D647A9170ULL, 0xB64C0DA13110FACFULL, 0x2BAA575B0E1DDD64ULL, 0xCEC62B35D45742D1ULL, 
            0xF426D2DD7CBFE3A2ULL, 0xF13EE42F2BCCC772ULL, 0x95344DEFD4C2D6AAULL, 0x73E800206A195D00ULL, 
            0x814579A605A9DF03ULL, 0xC43800D7946847DCULL, 0xE648CEEF0E1BBB5BULL, 0xB9DABCE0F8AC2732ULL, 
            0x7924F94EE489EC37ULL, 0x924B88413D54D2EAULL, 0x12C586DF2E6950DAULL, 0x219ACB9BC533E770ULL
        },
        {
            0xF992D5991B2BF3CAULL, 0xF2ADF04224FC72A2ULL, 0x37B6F018A79AC852ULL, 0x15DC74ABC7658C2DULL, 
            0xBD8EBA0BD80EC3AEULL, 0x4CE4D1CF1FE64D79ULL, 0x558E681E18BD9695ULL, 0xDB5CE2529CF12E76ULL, 
            0xC4F5842647AFA6A4ULL, 0x72E1263222692777ULL, 0x8DC1E869C4395621ULL, 0x94644D35A0F69265ULL, 
            0x212056B6C8CDB18DULL, 0x28FC8C4DBEE0B9BBULL, 0xD466EDB49118F7C3ULL, 0x6B0FEA8F317F88FCULL, 
            0xDE36FD2A1BE4B30DULL, 0xC30C3F5C92DBBC95ULL, 0x200ECE099473B03DULL, 0x6D454F7E8BD7DA5DULL, 
            0x678E32817D265D59ULL, 0x018A00074A5106FDULL, 0x9DE233DF9B030EE9ULL, 0xB2F071A223B1499DULL, 
            0x3966EE71B5E3AE5FULL, 0x28E3D3BAD6E5A7C1ULL, 0x65585D0D851D5428ULL, 0x631685F941D2E2D3ULL, 
            0xD45D39DBFBBB72AEULL, 0x549D33A5D0DD2D8AULL, 0x147863D75227B840ULL, 0x67E0EF9F9D98E901ULL
        },
        {
            0x21BC51C99D73CD9EULL, 0x47787B28EE602F87ULL, 0xD0984A78F1160008ULL, 0x0D21983214292D0DULL, 
            0xD939FB4BC577F4D1ULL, 0x84996097C470EA87ULL, 0xFA9DA6FF146CB254ULL, 0xA398AA1F49242EE9ULL, 
            0x366E03F6C3A816B9ULL, 0x6CFBE28CCC47C92AULL, 0x798019180AD072F1ULL, 0x247479557937A615ULL, 
            0x70DD45D290ED6608ULL, 0xA75FB08E87E7F477ULL, 0x68F3E997E94230E1ULL, 0x928AEE4A5AE7AE7BULL, 
            0x58AE729BA0180F33ULL, 0xF237D9EECFB0E763ULL, 0x1FB90055850D6601ULL, 0x0EC3E5FFED17BEC4ULL, 
            0x1991557952AD8B3DULL, 0x99142F59F04BBE35ULL, 0xF19CA10122582633ULL, 0x171D9EF22A30D3AEULL, 
            0x3CA062FF146A28CEULL, 0x334A2792772B2559ULL, 0xF5A81A0785EB8B24ULL, 0x1D83057CA3FF5C18ULL, 
            0xE4B41AFD797637C7ULL, 0x4297B1CD7E71107EULL, 0xCB1959E377AB1463ULL, 0x0C8FC48A323002CDULL
        },
        {
            0xCE00DAE3E5360D0BULL, 0x715F2483073EA9F4ULL, 0xC58C1679B2B53189ULL, 0x35ED8FDA969AA3F4ULL, 
            0x6409C866DB942604ULL, 0xA367B5C87B6F0B62ULL, 0x2BCACA52ECB9DC5CULL, 0x1AD3E8608FF324B3ULL, 
            0x1268A019F0F9F0D3ULL, 0x9504D53672876726ULL, 0xA32C37F54E25778EULL, 0x78E4F2E5FCF24541ULL, 
            0x94916411D9C706A5ULL, 0xC586A3E8CD81602AULL, 0x84E8628F1748F336ULL, 0xA75D447622E9CBB4ULL, 
            0xBFEB0BD8880D901BULL, 0xAEFCC0CD02A709E4ULL, 0xA0A802F8D2835FF3ULL, 0x5A7D1E866C132B0EULL, 
            0x0CA26B9E77CC38CBULL, 0x30D371F4E650C784ULL, 0x462D1D749976D738ULL, 0x0DC46E011EB140E3ULL, 
            0x278766752E63319EULL, 0xED78DFD08B48B70AULL, 0xA1237AF36BF3C9C2ULL, 0xCAD7032F4F4F44A1ULL, 
            0xB2AE230BC9E41513ULL, 0xCF14172FAA4F74ADULL, 0x78805A1B01CA3E68ULL, 0x6F254D3CCD359237ULL
        },
        {
            0x668134628C3374C0ULL, 0xCAAB2AFC74BB90D4ULL, 0xE4A152596F3ACF86ULL, 0x56FB0BD1F70C0E7CULL, 
            0x78BD8CC42F1BADDFULL, 0xA74D052FE02F68E0ULL, 0x86FFC930536E0CA2ULL, 0x6E4659925FA846D8ULL, 
            0x74477E95B62A37BEULL, 0xAD4BA9FCA3B6139AULL, 0xE2F438E8E9495A99ULL, 0xC1EE248C1C3EB28FULL, 
            0x2296C8B6E8263CFEULL, 0x8BB1F9E69C56B1ECULL, 0x24F030B22B3C0245ULL, 0x8B0907B1E3FE84CFULL, 
            0x1FCDEE5CB75392A4ULL, 0xC254E6D20FC9275EULL, 0xD4FCBE552A781030ULL, 0x60D67C37FB5B2629ULL, 
            0xFDA4562A7F9B2238ULL, 0x95B99255CBE8D1DBULL, 0x8912C70C72AF0096ULL, 0x27D0B1E4EC11A158ULL, 
            0x2436A768E9092A2BULL, 0x3978EA22768DB953ULL, 0x68518253130814B8ULL, 0xAB855BDB11114B5DULL, 
            0xEACBEB3CE701EADDULL, 0x3FC79BEBEC2A353BULL, 0x674A460685AD7E5FULL, 0xE85DD842C0AF7838ULL
        },
        {
            0x3B657124E1451D74ULL, 0x620B426AD9486154ULL, 0x376859CBAC981B16ULL, 0xCB3349EC55D1406EULL, 
            0x38EB5CB8A8DA3F2BULL, 0xCF7D239EF6AD964CULL, 0x4E255DB0881303A2ULL, 0x194018583885BE00ULL, 
            0x901906B0F473E833ULL, 0xC08F5678A22DD3BDULL, 0xB6DB567EA1306650ULL, 0x8506705782EB014FULL, 
            0x6544AC4D8A0F140FULL, 0xE78A74318A97E1A4ULL, 0x0774FFD52B125FAEULL, 0x072BABC9F2B1DFA7ULL, 
            0xE102EB5DB6804E61ULL, 0xA9CE52A9D8E55E51ULL, 0xB25CEB92EC7EEC2CULL, 0xC2178C81E189B8DFULL, 
            0x684D886E8283451EULL, 0x5379371295DE77FBULL, 0xFF94A741C72909E3ULL, 0x4AB68BEF99C1C21FULL, 
            0xC481EBE67EDE67D7ULL, 0x8ECBBF66CEEA01ACULL, 0xEC074CF3FB90CBC2ULL, 0xAE5DF63E83CEFAADULL, 
            0xFF2ECF504E5D4443ULL, 0x2F1B9D9C239D75D5ULL, 0xB7D484EEC333871DULL, 0x6DB5CE6B3BFBDD91ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Regulus::kPhaseHConstants = {
    0x88C8C793488AD4B3ULL,
    0xF5D6E497F88B1E2AULL,
    0xAFB8D7692A5C355FULL,
    0x88C8C793488AD4B3ULL,
    0xF5D6E497F88B1E2AULL,
    0xAFB8D7692A5C355FULL,
    0xB16D56C617F72BADULL,
    0xE4AB12402423850DULL,
    0xDF,
    0xCA,
    0x3B,
    0xDE,
    0x7C,
    0x1C,
    0xB7,
    0x09
};

