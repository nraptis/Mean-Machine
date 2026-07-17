#include "TwistExpander_Miram.hpp"
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

TwistExpander_Miram::TwistExpander_Miram()
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

void TwistExpander_Miram::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xECAEF43BB036F0E8ULL; std::uint64_t aIngress = 0x8F9C9AD692A30147ULL; std::uint64_t aCarry = 0x8E4804B7A094DFC5ULL;

    std::uint64_t aWandererA = 0xC67A6A11D939C210ULL; std::uint64_t aWandererB = 0xB5E7E980B93BA436ULL; std::uint64_t aWandererC = 0x9CF614972ABFA999ULL; std::uint64_t aWandererD = 0xA56586CDB4F0F08CULL;
    std::uint64_t aWandererE = 0x992F74646936A01EULL; std::uint64_t aWandererF = 0xE2E0DFE19CF4F006ULL; std::uint64_t aWandererG = 0xCED7947C61B20AA1ULL; std::uint64_t aWandererH = 0x9B2EF2F7FB738CF9ULL;
    std::uint64_t aWandererI = 0xD4BA240102A7E29BULL; std::uint64_t aWandererJ = 0xA95E0B5FF0A15FAEULL; std::uint64_t aWandererK = 0x8447592B3696FC1EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18242982245470447681U;
        aCarry = 18440349168160985497U;
        aWandererA = 15684462357874160102U;
        aWandererB = 10360893791604545055U;
        aWandererC = 13135420959110165448U;
        aWandererD = 9584881881220705769U;
        aWandererE = 17418112011018911077U;
        aWandererF = 12586027578931371108U;
        aWandererG = 14958639079598096158U;
        aWandererH = 10060036641672136469U;
        aWandererI = 14503253945113561380U;
        aWandererJ = 11627419799724829442U;
        aWandererK = 16102611342419904997U;
    TwistExpander_Miram_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Miram_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Miram_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Miram_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Miram::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA3D83A33351E3916ULL; std::uint64_t aIngress = 0xD79A506A441D1392ULL; std::uint64_t aCarry = 0xE222F36F143BE2CBULL;

    std::uint64_t aWandererA = 0xB930DC5B2D7A8CC0ULL; std::uint64_t aWandererB = 0xBF85FB376A7D17FDULL; std::uint64_t aWandererC = 0xB0F415218A0D4811ULL; std::uint64_t aWandererD = 0xFEADA2B613115FBDULL;
    std::uint64_t aWandererE = 0xF7C6609BD47CAAA9ULL; std::uint64_t aWandererF = 0xFED662CF3BA18656ULL; std::uint64_t aWandererG = 0x94A3CAC5EC07F583ULL; std::uint64_t aWandererH = 0xCC8CABBD3FEFE183ULL;
    std::uint64_t aWandererI = 0xB60CCE511ECE27EAULL; std::uint64_t aWandererJ = 0xC24FFB49AC596F0CULL; std::uint64_t aWandererK = 0x8648EB20F7715FC7ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18007794482178697304U;
        aCarry = 16553340932814439441U;
        aWandererA = 14447849694440236528U;
        aWandererB = 17804021431860362132U;
        aWandererC = 9265773618461230237U;
        aWandererD = 11624906600146452696U;
        aWandererE = 13099069393718835245U;
        aWandererF = 10279243090506226244U;
        aWandererG = 12184070800409865185U;
        aWandererH = 11444286571125493116U;
        aWandererI = 17182827668401208834U;
        aWandererJ = 15462191905875038200U;
        aWandererK = 16081729431587583158U;
    TwistExpander_Miram_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Miram_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Miram_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Miram_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Miram::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA1ABC7F4004CCDA3ULL;
    std::uint64_t aIngress = 0x986F03B920B2E55CULL;
    std::uint64_t aCarry = 0xD8F29535DF23B71BULL;

    std::uint64_t aWandererA = 0xC05E0E7F0E741DFFULL;
    std::uint64_t aWandererB = 0xCD78F21F3698603CULL;
    std::uint64_t aWandererC = 0xB56C3AD4D308BECAULL;
    std::uint64_t aWandererD = 0xFF0CA145C9D3E9B1ULL;
    std::uint64_t aWandererE = 0xE8AAF0AE9686AB51ULL;
    std::uint64_t aWandererF = 0xB113F0ABFB03D6EBULL;
    std::uint64_t aWandererG = 0xF25FC2817EF81731ULL;
    std::uint64_t aWandererH = 0xCBC7A825528EABE5ULL;
    std::uint64_t aWandererI = 0xFCE0197CED1F941AULL;
    std::uint64_t aWandererJ = 0xC75780DB1ED530BDULL;
    std::uint64_t aWandererK = 0x9F78E6A425D16473ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts), aSnowLaneC, 1);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseFConstants), &(mDomainBundleInbuilt.mPhaseFSalts), aSnowLaneC, 5);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneG);
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
    TwistExpander_Miram_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Miram_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Miram_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Miram_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Miram_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Miram_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Miram_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Miram_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Miram_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Miram_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 20 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1797 / 1984 (90.57%)
// Total distance from earlier candidates: 34426
void TwistExpander_Miram::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 579U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 311U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 0U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 360U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 348U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2002U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 340U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1287U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1594U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 924U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1866U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1009U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 111U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1721U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1077U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2013U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1700U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1858U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1515U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1339U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1187U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2036U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 196U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1955U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 854U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1011U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 872U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 795U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 85U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1439U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 946U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1172U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2006U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1240U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 413U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 828U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 701U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 190U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 912U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1532U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 13U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1130U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1857U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 412U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1604U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1125U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 44U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 480U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1884U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1166U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1182U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 183U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 499U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 276U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1253U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1569U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 665U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 503U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 376U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1218U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 387U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1365U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 609U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 52U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1988U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 941U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1361U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1460U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1421U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 761U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1219U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 978U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2037U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 834U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 357U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1538U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1704U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 515U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 69U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 240U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1153U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2032U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 36U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1101U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1471U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 225U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 262U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 114U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1654U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 934U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1249U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 745U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 657U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 929U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 364U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1220U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 523U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1827U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1879U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1241U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1634U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1747U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 683U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1137U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 124U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 421U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 398U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 67U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 20U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1035U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1150U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 992U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1841U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 760U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 890U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1022U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 775U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1342U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 200U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1551U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Miram::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE8405F241F9290B8ULL; std::uint64_t aIngress = 0x9A65FB73AA3B5BECULL; std::uint64_t aCarry = 0xAF237CE98B734B6DULL;

    std::uint64_t aWandererA = 0xACE53477CF57E76CULL; std::uint64_t aWandererB = 0xCB2A020790AC9A39ULL; std::uint64_t aWandererC = 0xC806372C8319EFC1ULL; std::uint64_t aWandererD = 0xE5E25B8D8BF99A1EULL;
    std::uint64_t aWandererE = 0xCA3BEDA140FD7077ULL; std::uint64_t aWandererF = 0xF035DC829D0A3F21ULL; std::uint64_t aWandererG = 0xFFA0C1CA8268E31FULL; std::uint64_t aWandererH = 0xC741DC07FC26637DULL;
    std::uint64_t aWandererI = 0xDBED5C1FD1958C34ULL; std::uint64_t aWandererJ = 0xFCA3EE18BBEF4BA7ULL; std::uint64_t aWandererK = 0xB185560EA636BA82ULL;

    // [seed]
        aPrevious = 10944017997687221222U;
        aCarry = 17692254118621509024U;
        aWandererA = 12625314169249577489U;
        aWandererB = 17816186768438696844U;
        aWandererC = 10215025240622697148U;
        aWandererD = 16553259457485795359U;
        aWandererE = 14183053309168368220U;
        aWandererF = 10215873554913997669U;
        aWandererG = 10897398529416362089U;
        aWandererH = 13285383006935168207U;
        aWandererI = 13833940017844120099U;
        aWandererJ = 18319129310844287281U;
        aWandererK = 18359960279411468338U;
    TwistExpander_Miram_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Miram_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Miram_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Miram_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Miram_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Miram_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Miram_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Miram_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Miram_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 20 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10373; nearest pair: 507 / 674
void TwistExpander_Miram::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 459U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3778U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3132U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7710U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5247U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7730U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7814U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4157U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7441U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 659U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7317U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 316U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4876U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5706U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4063U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3595U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1158U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2023U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1249U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1164U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 795U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1777U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 62U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 408U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2027U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 415U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1259U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 524U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1402U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 529U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 275U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1834U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1630U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 605U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1466U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1216U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 20 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10358; nearest pair: 481 / 674
void TwistExpander_Miram::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 751U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2393U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 290U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6840U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6623U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3622U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8078U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3549U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7063U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2450U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1266U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1285U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 701U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3023U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5761U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4537U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 897U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 241U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1408U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1811U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 357U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1164U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 740U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 150U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 48U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1816U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 599U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 730U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 520U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 18U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 437U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1071U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1663U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1192U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 643U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1511U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Miram::kPhaseASalts = {
    {
        {
            0xFD0C78430A2C7F62ULL, 0xA00DC9D2906AA7D6ULL, 0x62A31CE18E6025E4ULL, 0xADCC13F6AEFF8A05ULL, 
            0x9CDEA2B747E52694ULL, 0xE6E6009E128336B0ULL, 0x030FCE5810644149ULL, 0xA0CEFBD72C69F6AFULL, 
            0x4670AAC2CD5BD5BDULL, 0x4538E375117CEB9BULL, 0xD651D9BC932D4106ULL, 0x721A1151831AFE05ULL, 
            0xFCA953B92F441514ULL, 0x2F93D03EFB36CB61ULL, 0x5163B102B4F32C0DULL, 0x46869F6B9C93C19CULL, 
            0x3CD6BADF5AE1B2FCULL, 0xC8CDAE1009E4A0EDULL, 0x686D82D18BC83353ULL, 0x391FC6E7B0C47BD5ULL, 
            0xF0646BD69331FF33ULL, 0xAF56541B27C95428ULL, 0x808313C62D6B16B1ULL, 0x5D08AE2055779485ULL, 
            0xE11AB82D4350FE22ULL, 0xB5A73EF4785AC431ULL, 0x00C810827734A26FULL, 0xB02D983A0391D097ULL, 
            0x4D320DAE3E248B59ULL, 0x24BE72603DE0F5E3ULL, 0xEE3F0F7D4B3A411AULL, 0x504CEB80A04AF1F1ULL
        },
        {
            0x01EF917B38866777ULL, 0xD14F6B7B0B2AFFD9ULL, 0x432117A938330BBBULL, 0xE57B1840B961C6BFULL, 
            0x9ACAFE81517DCC49ULL, 0xD445C6BFD37D6E40ULL, 0x7D77A3DFDEA4C403ULL, 0x4709BCB29011AE74ULL, 
            0x8F7E2EC0827CF7B7ULL, 0xE3EAE8B2D821BD5FULL, 0xFFF92D0B01036FCAULL, 0x3DEC942929555A27ULL, 
            0x55B5BEC35FB8574DULL, 0xA8E9BD5A166380FDULL, 0xBB12AC176BAFF8EDULL, 0x2E622DF7241F27C4ULL, 
            0xCD2B62EE0EAF81A5ULL, 0x10F4D097E389785BULL, 0x23C480092FBE22DBULL, 0x3925550401A37A2DULL, 
            0x44CB312E9BF38A38ULL, 0x3CF38CF9E0BC343DULL, 0xEC3635969DCC4895ULL, 0x5AA16E02E1D54E53ULL, 
            0xDFB59C29AF1FD9B9ULL, 0x999FFA21D73C7DFAULL, 0x3748EB52A50D2CF0ULL, 0xB00A0D20DCDA0FC4ULL, 
            0xFEF91F911FEA15F2ULL, 0xFBB668D55F999802ULL, 0x8920485C7B6E9502ULL, 0x87B3ED32145E95FCULL
        },
        {
            0x48804972C3F742DEULL, 0xCE39410C022271CAULL, 0xA334B32301523485ULL, 0xDCA075064900CD58ULL, 
            0x6FF8D73EA21C440EULL, 0x54457F30CFBB35F8ULL, 0xE0905593E041C100ULL, 0x3074684704D15906ULL, 
            0x89519FB103A4026FULL, 0xA8DF4E46AED4BFDDULL, 0x07EEB77BC7EEA034ULL, 0xC5A304CF0E7BEF37ULL, 
            0xED38AF978DD10550ULL, 0x73DEF8DFCAA7F298ULL, 0x55B17AE57824229EULL, 0xC681211AC56658B6ULL, 
            0x70FDCF6F48B6CC0CULL, 0xFB7D6A89D05DB4B5ULL, 0xA58CDB81DC4ED96DULL, 0xFCCD1D1FF209C57FULL, 
            0x3CE5E5942D954D55ULL, 0x07EA9648360AC757ULL, 0x0714573EA1BA2E0DULL, 0xE37C3605CCD3E839ULL, 
            0x397A16F27C9E1F71ULL, 0x35878D1DC9DE8EC5ULL, 0x376CF9583E676885ULL, 0xE18CF0FD7F1B10C9ULL, 
            0x7D4E9A4BEEE492F5ULL, 0x90316D9873D4B12FULL, 0xC267B415844C9A2AULL, 0x78EC4A2C8F34493DULL
        },
        {
            0xD305561723D86AD5ULL, 0x330F16DC8AC38E57ULL, 0x72CA7D9FD50C2068ULL, 0xCABCAC6925DA3FEEULL, 
            0x2E69A6854B3D84A5ULL, 0xDDFEFF41015DF1DFULL, 0x0028335FB13D03B5ULL, 0x8DBD6B072C67EE74ULL, 
            0x31EB0672B0A6FA37ULL, 0x9D02B767907ECAE7ULL, 0x1AD94D6B53899D64ULL, 0xEA78A090ADF94247ULL, 
            0xDDF19BCE4889B85FULL, 0x119D1537E8CA66EDULL, 0xF05E10C78B92DBE2ULL, 0x4985B8300F11E15CULL, 
            0xBE2BF93566ECBEC7ULL, 0xD1026B01A2792A3EULL, 0xA2FC5CAFFA4C16F8ULL, 0x6214EAEA84E814B0ULL, 
            0xEF0D9296E6ABD371ULL, 0x33AABFEA2101D7ABULL, 0xF1A495830B91777CULL, 0x4B4AA0B26D7ECEB3ULL, 
            0x52FA90A7998C746CULL, 0xDC2E9A747564A600ULL, 0x8EB2EA8A5C1AABF9ULL, 0x63AA2DBC18500212ULL, 
            0x4C702A29BD00C37CULL, 0xFEC0D727C558BD34ULL, 0xA089B0BFC208FF8CULL, 0x11CB7AA53AFFFCE8ULL
        },
        {
            0x0E6DDE094C8FF660ULL, 0xD4A0795FB1C46457ULL, 0x481EB888EA68D152ULL, 0xB8D0E1A3F60724C1ULL, 
            0x3919296327BF4852ULL, 0xA8BF6D8BB09C1417ULL, 0x420BB0BC206D7BAFULL, 0x0C1B9E3EF0A16036ULL, 
            0x56E9407F1037ECA8ULL, 0x7FD983EBD54D68C5ULL, 0xBABE8BC19428E847ULL, 0x59C622190E59CB4BULL, 
            0x3C39F647CE806FBDULL, 0x7A2EE53864EEF393ULL, 0x80EE07D7C9A6EEFFULL, 0x0FE9538D87CDCCC3ULL, 
            0x98A5140D4DDA813EULL, 0x9E70DF726CCD163FULL, 0xC776066773FCC5FAULL, 0x4DE35534F5C35CA1ULL, 
            0x935F9F03DB913606ULL, 0xA8765DA4B428F372ULL, 0x87F7BF479C7EFB1EULL, 0x42C0A67659BB03DEULL, 
            0x606FFBF8B8A8FB62ULL, 0x36E2F23D20CA12F3ULL, 0x069C45E59D2E537AULL, 0x3D9F94BDA0F2A0BFULL, 
            0x51C0B3C96EEB70AFULL, 0xC573E33F507CC529ULL, 0x18F9B43112A13955ULL, 0xCAA60A8D2E233BBCULL
        },
        {
            0x9DBFF3D3CE8AC18DULL, 0x45FD208A8C7F11A1ULL, 0xE524CD07758A8802ULL, 0x6C7AAFE7F4CFA4A5ULL, 
            0x9B10FFA05405049CULL, 0x67ABAFF07F9A2046ULL, 0x67D3FA8D3DCD7B88ULL, 0xDEBF84DED0643DE6ULL, 
            0x976B0EED070234A9ULL, 0x6A483983AACA44CAULL, 0x52B458F153045565ULL, 0xAEE59A14C5317C1BULL, 
            0xABE5875C8BFD850EULL, 0x44FA325397D0FE33ULL, 0x1DDC74477D9948C6ULL, 0xE2E14A728E5B6AB9ULL, 
            0xE8BC365681F19161ULL, 0x4D6C53A7994D6846ULL, 0x5C1B7E36BFE51CFAULL, 0xD8E37F1325B511EDULL, 
            0x32A829F94212848AULL, 0x7EA46ED95AE9897CULL, 0x8B758AFDFCFE9079ULL, 0xBA47ED73CE1B6739ULL, 
            0x652220F9C86C260AULL, 0x899DC4FBF4069A66ULL, 0xD5C02A0BC759EB26ULL, 0xB1845FAF63C59EBBULL, 
            0xBC3A1570614DEDF3ULL, 0x8B8D847FDD5E4C41ULL, 0x93545709DF19DFF4ULL, 0x1C27C08E5F4FE6ECULL
        }
    },
    {
        {
            0x15922DB76478D960ULL, 0x5D4A6DF286B288C9ULL, 0xD23F895A4E05A614ULL, 0x456F1C5F9FDE9CFFULL, 
            0xFC8EB128839E0D48ULL, 0x347A9DF4EDC291E3ULL, 0x73859510CD709662ULL, 0x37E917A0B5A2FF2CULL, 
            0x31B65AAA73A2DCEDULL, 0x166AF89D12B972ECULL, 0xCC6F4D701947B6DEULL, 0x5673D52A63392824ULL, 
            0x020FC50A4E3EFF65ULL, 0xC97838DAEDF6FC1DULL, 0xFAE4AE96C24195DAULL, 0x35C4AFCBA5C9C46DULL, 
            0x085B03E5E03BF04FULL, 0x66740D5968944278ULL, 0xCA626BE7DEA41B0DULL, 0x167172A51819C4D0ULL, 
            0x6B2EE581D24FC632ULL, 0xC9D4E1F39723FD0BULL, 0x003FD752EE6703FFULL, 0x1AD17579C667BB61ULL, 
            0xB6463513203A6B33ULL, 0xFF811E175DAA1F8BULL, 0xA7B84B85AFF21DE0ULL, 0xFE01494C7B93FEBCULL, 
            0xC017521E3507382EULL, 0xDAD259887D30A990ULL, 0x227FC150B60BF80DULL, 0x7F8FE7E6FF0997D6ULL
        },
        {
            0xDF9784EB2F678F44ULL, 0x0B544AE3E43E2C60ULL, 0x2CD5775989D0B8DAULL, 0x1AAEEB903AA6CD4AULL, 
            0xD483A47AB68E0498ULL, 0x5545B49348DE945DULL, 0x142C6B9AEFA0B82BULL, 0xB151B9900C3F4039ULL, 
            0x0D6AAA5489D32AA0ULL, 0xB0EB5A754FC928F7ULL, 0x6F9C10B89F52843DULL, 0x12A3F82D6F4C244CULL, 
            0xEA95A8151AD1C33EULL, 0xEC32959C7629AD8BULL, 0x4AAE120B69B24FC4ULL, 0xBCACDD808DD2A4C8ULL, 
            0x9D860BD422AF114BULL, 0x15213E577E22B7A2ULL, 0x969FB255966A00D9ULL, 0xE9F2F627F0E77986ULL, 
            0xF6F96A7DED5B4A6DULL, 0x4FE0EC7FCCBD1A83ULL, 0xA62AE2C65E823564ULL, 0xCA530B041F8AE1CDULL, 
            0xA90066204A4E59E2ULL, 0xE88FBEF90E5E0489ULL, 0xEFB4AA5CD0ACA7F1ULL, 0xF2CA5409745DC3C2ULL, 
            0x6703A46FC0126EF6ULL, 0x6173B1B6CA111749ULL, 0x1CC617C2056C1FC5ULL, 0x8CB1B2437E8BD3CCULL
        },
        {
            0xC51C5F98BB4E2E0EULL, 0x5242030260A5CE06ULL, 0xBCEDB2AB78F5E660ULL, 0xD56CD9E341F2E0ACULL, 
            0xA355BEB09EAD52C7ULL, 0x93D5A2F17DCE7046ULL, 0x6AE4D2D0D870F15DULL, 0x2357E65D411579DEULL, 
            0x63559F571C12EBDDULL, 0xDAE0A00B7AFAAF4EULL, 0xAD94C8A334F075D9ULL, 0x6EA70AB572777312ULL, 
            0x27656A5280C43B86ULL, 0xAC62652B731E112AULL, 0x9528BC0C758093CDULL, 0xD20DA2C43AC9DB8AULL, 
            0xEB532208A94A9AC8ULL, 0x7CD47F978FDA8D9CULL, 0x177DA329EE12C0E1ULL, 0xE64435BE92413546ULL, 
            0x62B032D35F0276DBULL, 0xEFE3D0F42E5F88FFULL, 0x6C9C4561BB0A78DBULL, 0xB0F6E0C731228478ULL, 
            0x4A5556082103BF4BULL, 0xA7BC7CE967978F11ULL, 0xE32028131A575CE7ULL, 0x2C872E39782BF95FULL, 
            0xFC429964E52FDA09ULL, 0x07FD5F00BF9F5AFCULL, 0xA9D6B278AF60B4D3ULL, 0xFAE95C01C8FB6DCAULL
        },
        {
            0x724E6B4DA1CE2E1AULL, 0x2DAB4860713BC768ULL, 0x7634ACADEDD6EBCBULL, 0xE4307C9695BC5222ULL, 
            0xBD1F1A41DD2D3BAFULL, 0x83E66CA2AB5482E9ULL, 0x1F4698224E3C15D1ULL, 0xF9AD491ED0FCB209ULL, 
            0x771B1DEF85A2E130ULL, 0xDD2A856E1BA1DE56ULL, 0xBC41311405105524ULL, 0xE07A529BA249A2CFULL, 
            0xE1B45CF411FA6F0AULL, 0x96060C88034BF7FCULL, 0x29619C8D8FD0FCC2ULL, 0xFEFB15D6102F9C3FULL, 
            0x2D9D604F3478AE95ULL, 0x210E101722BDB530ULL, 0x00299250DBC3C41FULL, 0x66C5C0449C66E9D7ULL, 
            0x3F9C3A20945CDB0CULL, 0x61CCC3711880C9A2ULL, 0x417949073C4C023EULL, 0x4AAA0406EA296004ULL, 
            0x59B0FD5F324B856AULL, 0xA967BDBBAE82AF81ULL, 0x950DFD0A63B69040ULL, 0x3F2D45A676DB4E5DULL, 
            0x0346577445855FB8ULL, 0xEDD62E70EE9B01E7ULL, 0xACAAC026C57501BBULL, 0x4EF552274B3E5E2BULL
        },
        {
            0x8E64980B0A6005C5ULL, 0xC50C5C6ECF3C5CD0ULL, 0x35063F72EB0C3B1CULL, 0xD27883877DB58CF7ULL, 
            0x1FA623CF92BE502BULL, 0xE59FADCA439D9904ULL, 0x038A461821224401ULL, 0xEB3CF397574BF944ULL, 
            0x9627DCCE488859FFULL, 0x33EB64F9AEC68CD3ULL, 0x3AD93E0699AB1992ULL, 0x1597DB273A753773ULL, 
            0x95DD6E6FEC2DEE96ULL, 0xB1F7BDCCA230199DULL, 0x2119E762361FF406ULL, 0xD82C6375521E4254ULL, 
            0xC656DE8377721BCBULL, 0x57E45F59D26184D2ULL, 0xCB7A156F281ED67BULL, 0x67ABD64C5451965DULL, 
            0x127345C2D43213C7ULL, 0x90A28AF82119767BULL, 0xF1298A7E2812707AULL, 0x4ACD43BDA67C75B8ULL, 
            0xA6B21A03B7810930ULL, 0x9E37C2644541F79CULL, 0x2D0B7EE19BB34011ULL, 0xF38957BE1E97D673ULL, 
            0xDB99C7C85EF916BCULL, 0x1F4398B41D95326AULL, 0x7E9E94CE197A15F7ULL, 0xC6561C4472D092A6ULL
        },
        {
            0xBA1DBC954E4DDA33ULL, 0x3AA19355BB3B99B1ULL, 0xC1DE07F6ADE971EDULL, 0x7225EB448178F998ULL, 
            0x340558FD02B8CCF2ULL, 0xA2634E55A1C1F56EULL, 0x1D49F564C596092AULL, 0x2A452A4DBE0EC5E4ULL, 
            0xFC6CD8A5C8405368ULL, 0x778F867A7058BBFFULL, 0x91BC43ABA09B1C5CULL, 0xD9297FF67742FBC3ULL, 
            0x17D27741076F2831ULL, 0x101B1C86EB58218CULL, 0x234F0E516118B954ULL, 0x0B25E4239B481651ULL, 
            0x78372253519E900CULL, 0xB9D2FBC3C0F91E33ULL, 0xB6B111B5D7463023ULL, 0xF3821D3A6D53C050ULL, 
            0x41C3095C8AA24707ULL, 0xA55871DE9C0E5BE0ULL, 0x17A961EB5475CD7EULL, 0x17360212F8387349ULL, 
            0x66A7F861D054CD13ULL, 0xACE92195088A977CULL, 0x26A832C769EAD139ULL, 0x9227A926ADBA7C6BULL, 
            0x955B592981FED5FAULL, 0x576187E8116C4932ULL, 0x713562D446390582ULL, 0xC888F5E1258013B7ULL
        }
    },
    {
        {
            0x5D8A5C6CB2C567EBULL, 0x132DECD218A1EA91ULL, 0x56F67B6AB5ABB07AULL, 0xE3039445D2153D27ULL, 
            0xDCFFC1E96B5E5EBBULL, 0xAF79DB620326669AULL, 0x0DF5D5314EB3941BULL, 0xA9D8E4E75913D43BULL, 
            0x4142B3A71DF6DFC9ULL, 0xD31A7F1C5D8F5A4DULL, 0x150C701C3C62B432ULL, 0xE9F6758C8A676479ULL, 
            0x6CA37843153CCDCCULL, 0x42D34C9B80F37B1EULL, 0x5717B5863DB3103DULL, 0x761AFF02DD01597DULL, 
            0x0B8A5B0FED2CDA86ULL, 0xA3370A3642CB8AA9ULL, 0x0D86F7B34ACB9805ULL, 0x8BA7AB46AC0D9EE4ULL, 
            0x32B05619C06A27CBULL, 0x8A7DE3F0853323AAULL, 0x85F325D9A5523607ULL, 0x035EB335206A9D10ULL, 
            0x4A3B7A6B5FD8F4DAULL, 0x10C02A8B76BEAFA2ULL, 0x053441B5F8D610CDULL, 0xB218BFF763B5AB00ULL, 
            0xC3235E9155C294B0ULL, 0x3A8AE482BC74EFD8ULL, 0x8E3DFDC953AC1184ULL, 0x24569C4AEC21644CULL
        },
        {
            0x82FEEC40909915ADULL, 0x0989D91421918D35ULL, 0xD6FF051C96649BBDULL, 0x970799B1133A3D08ULL, 
            0xA15474028167AE01ULL, 0x743C98927D641AD8ULL, 0x0C83D18D71960F8FULL, 0xC3FCC48C6F1BA362ULL, 
            0x8C9D863FDEC88E65ULL, 0xC1291C91FB1843EBULL, 0x8D101D0773D0BC29ULL, 0x40BE2FE91E0B3423ULL, 
            0xA2A5A7A6A361583CULL, 0x9636C4729586E5E0ULL, 0x5C5B0C2D62201F72ULL, 0x2416F3BD1F1A2336ULL, 
            0xB10EE6F101BD34C6ULL, 0xE1F7941AB0064C04ULL, 0x20E9C0A4345D7BDFULL, 0xCB2B50E5A344DA88ULL, 
            0x24A1957470695115ULL, 0xA09D5D928E6A1373ULL, 0x95147C1C685FB7EFULL, 0xA9504401D5F2B1B5ULL, 
            0x678A0FAE7C523510ULL, 0xD206E424AAB619CEULL, 0x55E75A9B8F695E41ULL, 0x82EAAFB5B7584788ULL, 
            0x2713F4FD42458FDCULL, 0x3D5288D7EFBE29DBULL, 0x7482887A38AC154CULL, 0xF333BA3F7A5C239BULL
        },
        {
            0x34735162C10BF394ULL, 0xD157222DAF752262ULL, 0xEE9F3251E37E751DULL, 0xD63343F7257A5478ULL, 
            0x7F95107757873897ULL, 0x34B131530BC667DAULL, 0x6FF602151AAFD31AULL, 0x18C7A160DBE11385ULL, 
            0x48B6F599AC64250AULL, 0x5F91BB4074174AD9ULL, 0xD77A6FECE7B0B3AEULL, 0xE9CCA1274B75E8C6ULL, 
            0x784E114BD762CBCFULL, 0xF7E66B7182629381ULL, 0x5DEBCE0EB5B7CD16ULL, 0xEBCCCC673B99F1E3ULL, 
            0xFF6FED19F5EA6473ULL, 0x0ED34D9021037103ULL, 0x48EB9358D5819C63ULL, 0x310FC7AA8BDDEBAFULL, 
            0xF0C6A8C01D768F67ULL, 0x10F4573310EB1B85ULL, 0xF0FAD6680652B8A5ULL, 0x755725039DD695FFULL, 
            0x552AA00F1C8DEFC9ULL, 0x55AEBBECEC23421BULL, 0x015E9946967CE0BBULL, 0x5488D2FF6AA26652ULL, 
            0x3B0DCB33DA1C5191ULL, 0x617AC4E280C62C6EULL, 0x6ADBF093389611F9ULL, 0x9232458AF26472FAULL
        },
        {
            0xD7C6941989E90EF6ULL, 0xDBFECEB7361AADEDULL, 0x1BF62849EB010520ULL, 0x9276FD9890CBCAD5ULL, 
            0x35F270C9C33EBF00ULL, 0x73525301CFC436FAULL, 0x9B7A24AAF2E3DBC3ULL, 0x7E7963CC2F0281D3ULL, 
            0xB922D1470B7055BCULL, 0x52FEED1201203F5CULL, 0xA0C9CA2D0665AE61ULL, 0xF11CC001B54FEB55ULL, 
            0xE97AFBEA72CF54E0ULL, 0xCCB31D76B48E8E09ULL, 0x91019006BEA88C69ULL, 0xB07915FFEEB6E37CULL, 
            0x50C244514CFB80DDULL, 0xE62948DA7A2C7877ULL, 0xF6F5CF22C9C74F79ULL, 0x1F7F0C8142458512ULL, 
            0xA2297C0E23C5A0CFULL, 0x3EA7FAFE2C359C57ULL, 0x7F0E13AD7A7F7B67ULL, 0x9E557F4AD056E739ULL, 
            0x9D4AAC73B1AE84EAULL, 0x693719664A075760ULL, 0xAA6BCDB161716CC4ULL, 0x32786CBEFE64207EULL, 
            0xE91E29A493797958ULL, 0xC2587EBAD8909EEBULL, 0xB3F073D56AE77EB6ULL, 0x48806D23C0AA2503ULL
        },
        {
            0x1334C42A1D6EEBC2ULL, 0xF79872C9DC312277ULL, 0x54D32DA05D9525B3ULL, 0xB1F5E72FAC9A593AULL, 
            0xFB92E89E46523765ULL, 0xCA136E7B707CC720ULL, 0xA17843BD09EA42CDULL, 0x1D914B79D4C8F397ULL, 
            0xED81AB9BAD1DC282ULL, 0x5BB0984A0B22D574ULL, 0x853C6300DCE2EA95ULL, 0x080FBF0D19435690ULL, 
            0xD7688DC57CB14194ULL, 0xC42792A1EC7CF21BULL, 0xA757BC30944E8415ULL, 0x1990CECEA9B2C5E5ULL, 
            0x8686FF03B41BC56CULL, 0x95EF7DC8874959D8ULL, 0x12640B33CF754A3DULL, 0xA7743CC8E1EFD800ULL, 
            0xAD1974307ED07BFCULL, 0x0913DC357AF1C04BULL, 0xED31F482AB9C32B4ULL, 0x5ADC9C61CD146747ULL, 
            0x1FC73B95E34962FCULL, 0x6F9E6269C4F2658EULL, 0x582F0403CFDADF40ULL, 0xD4E94EE1BCAFE595ULL, 
            0x5D05280C0DFE4ACDULL, 0xBAE0A1EBB64C6F9BULL, 0xC34EF1A7688E3141ULL, 0x014A84735D120B5DULL
        },
        {
            0x4FDC7B5EAA0AFB08ULL, 0x0F77A1CDCC1CAA6FULL, 0x39DD98BDA9FF0C00ULL, 0xBB36817E8B94A71DULL, 
            0xE8CFA3DB15E4E4A9ULL, 0x8297CADFCBF607F4ULL, 0x86A6068DC56F85B6ULL, 0x49D5F6BC839FA0E2ULL, 
            0x00DB6D90F30DBCF9ULL, 0x0A1B7AB5492B0942ULL, 0x0D34F17C411C71C9ULL, 0xF9D0C0352B646190ULL, 
            0x54A3B48100BD93ECULL, 0x87C6C793A6FC65DCULL, 0x99698FC7B7CB1299ULL, 0x9DA4E1F2955FD3E1ULL, 
            0x76A86757BF5C3863ULL, 0x2140BF382D77A18BULL, 0x71C6BADA97574348ULL, 0x5010B2FBB3D61CF8ULL, 
            0xFE9EDD6EEE7112FFULL, 0xFEA6EAD75CD16644ULL, 0x47F2E083CE5FF973ULL, 0x5217CE77D311A1CCULL, 
            0x61F44F89C1EE2015ULL, 0x280A1FE98E8EB2C8ULL, 0x02357B8F0DE7DADAULL, 0x6270AE44EEAA8BA7ULL, 
            0x5AF5548174D9328EULL, 0x55C6B09D04A2ECD9ULL, 0xEE5DF8273B821907ULL, 0x519ADE0139F14D08ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseAConstants = {
    0x64425F0307C79F96ULL,
    0x9FAAF08C0ED7042DULL,
    0x71BBCEA209F957EAULL,
    0x64425F0307C79F96ULL,
    0x9FAAF08C0ED7042DULL,
    0x71BBCEA209F957EAULL,
    0xAB3DB97D7C6163A0ULL,
    0x7E16255417C9F11CULL,
    0xD2,
    0x0E,
    0xDB,
    0x4B,
    0x56,
    0x6D,
    0x49,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseBSalts = {
    {
        {
            0x4F4393EDCA637AE6ULL, 0xBB5A5F01DEE483C9ULL, 0xCA7391B72EA89839ULL, 0x439861DA8E920597ULL, 
            0x5C6F5A3A8B94BD2BULL, 0x473913128D6BFE62ULL, 0x1D1A3919854F37FEULL, 0x76A6E1CE19E4780AULL, 
            0x5FDF9D94F88D6F3FULL, 0x8C33DF121A1576A3ULL, 0x3793D2C812EF5672ULL, 0xCC79C598BE04B592ULL, 
            0x9B5B4E42F522C8E3ULL, 0xD6E7FA7DB9603F27ULL, 0x5B3045E27F171DAAULL, 0x3A3961E6711F05C7ULL, 
            0xC3A382AFCC482A35ULL, 0xF07ECDC45F10FFA8ULL, 0xE7386A3385EB0CA6ULL, 0x1DB31F5C35A0100BULL, 
            0x1E68A20BBD48B413ULL, 0x2217A422E584CBBEULL, 0x3DFE84CAD438621DULL, 0x0949ACEF75C32533ULL, 
            0x2DA2516A8E1BCAA5ULL, 0xF4C4981BFDCCD0DDULL, 0xE7DB9293209C6783ULL, 0x715EEE691D144E68ULL, 
            0xDBE622E48D2778CCULL, 0x0156EE8ADDC86F5EULL, 0xAA0C2675FD5CE6E5ULL, 0xE44BB3C4D0FF1298ULL
        },
        {
            0x02B876EE445FB5A4ULL, 0x4AB7FEFE0881E12EULL, 0xEB8C32E0EFD319EDULL, 0x6AAB1B7F4C40CFE2ULL, 
            0xF7E6A4A741FBEAACULL, 0x1E22C7081E8548B7ULL, 0x813CA3529D5108C0ULL, 0x479A97CC8A1D83DBULL, 
            0x20F37DDFAE4D82AAULL, 0x8E95E0A2B34166B4ULL, 0x0458DC8C4D49839AULL, 0xA64E85669883462CULL, 
            0x10B60E3B5E70DE16ULL, 0xAA862D589CB41110ULL, 0xA72EAA6F5E7F92A5ULL, 0x557F71F96553D5AFULL, 
            0x9665D3EA086765FCULL, 0x8810F3E8E5D52F11ULL, 0xFE1299545C2FF767ULL, 0xE5755394726DCD5AULL, 
            0x3114C602A16746B8ULL, 0xDCA7E5BEA97BD8CAULL, 0xF999592D995CC4AAULL, 0x8D5C699E9327FFB4ULL, 
            0x4B1001D5E8353B5FULL, 0x96FC9787B35CB5B5ULL, 0xD34984E08F773A94ULL, 0x3588DA06C577199DULL, 
            0xD0126F44F83E930DULL, 0xDE96D64DBAB55216ULL, 0x088657C9349A8C1FULL, 0xFE42F6496D581211ULL
        },
        {
            0x9425F4BF15E173C9ULL, 0xE3F08BCAE74B5AB1ULL, 0xB5D3E02A69175171ULL, 0xF094C6862569AA03ULL, 
            0x2AC7B94CD12A17E5ULL, 0x288FAF7E63BBD9B2ULL, 0x7CA5E5842C47F5B5ULL, 0x2C6E7A08882783AAULL, 
            0x5B3CA024345638EAULL, 0xC5929AB62599F116ULL, 0x829EAF2BD903BCA4ULL, 0x12B2F2FDA65B5223ULL, 
            0x9ECF7263BD6D745BULL, 0x8B61DB8DF786A4D3ULL, 0x331155C7A9DA896CULL, 0xEAEEE384B6506FBDULL, 
            0xD42468733A14BEC1ULL, 0xB2F14CEA6CB11EB3ULL, 0x16702A1DB4FF8258ULL, 0x7D20BA5F0667E8F5ULL, 
            0xBD4132BC923FDFF8ULL, 0x3E5DEE244F49F46CULL, 0xD3738E4511656164ULL, 0x10D447BD86C6BCD4ULL, 
            0x15EF0949CA273B96ULL, 0x2145B1DA5E47AE32ULL, 0xC9C4254DCBB61A89ULL, 0xC351066B0D5D4D15ULL, 
            0xAE36A2056F0EE7D3ULL, 0x30C902B65238A879ULL, 0xEB8785090DD1CD03ULL, 0xCC145054AD570A35ULL
        },
        {
            0x61864336234DC121ULL, 0x001C73F3730B90E2ULL, 0xD16C05F6F6B49F51ULL, 0xCC6ABBAFF99216FCULL, 
            0x1150F0BDC30117C8ULL, 0x0CC97058A85B95F3ULL, 0x488CDB22C9B71F07ULL, 0x0160BA3D6FFB76AEULL, 
            0xA8292D2901D9F933ULL, 0xAC9414772D355E13ULL, 0x86994EC665879738ULL, 0x0C7E4E8ED10923DDULL, 
            0xB0766D6E2862B19DULL, 0x125E276DB3F61511ULL, 0x8B5515E70726E0AFULL, 0x13896C29366AD242ULL, 
            0xA758066D28C518B8ULL, 0x6B9F2F4DDD829341ULL, 0x2471D53D05122924ULL, 0x4DFD80A6B9533352ULL, 
            0x3DDAA1112219196AULL, 0xB481908636A84AA8ULL, 0x6B6D94FA73D9B721ULL, 0x572A86C0F1B7BDABULL, 
            0xF95AD237E1B33E48ULL, 0x97FC90A319520F27ULL, 0x1FAD3815D787FED6ULL, 0x9D49D05A5EA05BA8ULL, 
            0x616F9632C63AA362ULL, 0x1199E19DE88D73C5ULL, 0x7D7D140D93554936ULL, 0xD2F1D53F7629CEB3ULL
        },
        {
            0x53A01C852729B7BCULL, 0xAC17B33778E88914ULL, 0x5BE2D6B5CF6562C9ULL, 0x438C90E934E8E6F0ULL, 
            0x04AEDF3CF05607BAULL, 0x34DCE2E12ABD5616ULL, 0xD87B589D10C8F47EULL, 0x15FB4EE298CD1AD0ULL, 
            0x24D6532808E45A99ULL, 0xBC5C5FC9773F30EEULL, 0xD9E1B9AEB425F625ULL, 0x27B4738494BD9DEBULL, 
            0xF0B820D683D3C569ULL, 0x086DC04AABCE80E8ULL, 0xCDB2CA19A7D1CD45ULL, 0xD638964B6D12FB36ULL, 
            0x40971E846C0E8F64ULL, 0xEB0537581FBACD55ULL, 0x7DFEC06E1AFAFFBEULL, 0x4490A328E959BBD2ULL, 
            0x6F160C55EC2B3B78ULL, 0x65A606F1EC1CBCACULL, 0x08046179FA42C1EDULL, 0xF2D0043D59441102ULL, 
            0x5D55FC1D70C0CEFAULL, 0xC059D1330589B025ULL, 0x81F0C35A330D7C03ULL, 0xB5631BD54F7A612EULL, 
            0x1DC94B71FBF86526ULL, 0x24AC45347EDCF8FDULL, 0x1DE4DE2A28028B66ULL, 0x3111F164F9B67E05ULL
        },
        {
            0x1D99635AB21D1C99ULL, 0x7ADBCD64382B0162ULL, 0x3B5FAA2220162A86ULL, 0xEFC9778E0DD9A2A5ULL, 
            0x1D77E18A0986CFA5ULL, 0x8EF75F4EB463ED4BULL, 0x5903220010E00303ULL, 0x207312CF75124E74ULL, 
            0xB219EE1BFE274810ULL, 0x70867DD68B3B428CULL, 0xC92E773CF4F6852EULL, 0x3EEE1BEEDCF67971ULL, 
            0xE10FDD3AAAE53E07ULL, 0xD460A6B85EB43057ULL, 0xC9940D13AA631E09ULL, 0xD93E45EB7CAF9FB5ULL, 
            0x1541F82907DD5254ULL, 0x925AFE0480A7DFE8ULL, 0x59D2C1AA70CDFF31ULL, 0x957C26175945FF36ULL, 
            0x61D8DCC294398EB4ULL, 0x645AB2DFABD66BAAULL, 0xC4F9BA9968467DD7ULL, 0x4736D5CF8022F4A8ULL, 
            0x660B9E7354211DA1ULL, 0x386FE8C0A870FF59ULL, 0xD44158A7D339978FULL, 0xBB7BBF6E4D00D55BULL, 
            0x246F1FCD35B1E723ULL, 0x81959EB5A6577062ULL, 0xC7808312BA1F48F8ULL, 0xB1D80B7F5A4607DCULL
        }
    },
    {
        {
            0xE19088986322FFDDULL, 0x61EA52717BA3E3B3ULL, 0x966B9134FFE33E22ULL, 0x1ACA7F70A78E374AULL, 
            0x4CDE0FAA5BD63C7CULL, 0x78ADC6C387ECA7ACULL, 0x188E3523B560C845ULL, 0xB91C1769E884322CULL, 
            0xDAC502AE9410CD05ULL, 0x988AD28DCDDC003DULL, 0xB28EC808AB938550ULL, 0x93CA2FF523693B16ULL, 
            0x95959B9C4934CD57ULL, 0xA50ADC987862EFE3ULL, 0x3CCF9EEEC8F68905ULL, 0xF97D981B197C9297ULL, 
            0x53C640A592D4FE34ULL, 0xB7E19AD050196781ULL, 0x7A4EFCC5FCBC4B1EULL, 0xF4680E6825DA06D0ULL, 
            0x82AA00B1A7191F8EULL, 0x7B883534D710B3CEULL, 0x84817D4030CA47BAULL, 0x0E0DB37C3D6DDC49ULL, 
            0xC04FDC39AA45C2C6ULL, 0x69BD965E2E2E7786ULL, 0x348A4D46264F21C1ULL, 0x3958F00F2E7A52DDULL, 
            0xB3694F4776D044E2ULL, 0x90D92298473664B3ULL, 0x14B3FF2D98385E2FULL, 0x513581C6AE5D71CBULL
        },
        {
            0xC33714414028DB73ULL, 0xF581D6280EDE666CULL, 0xE0C2AD9ECEEAFD6EULL, 0x89B4525230B4B8B2ULL, 
            0xA091453C3B4D4286ULL, 0x032D44A6C82CAE6EULL, 0x7CC2230EB134C0D4ULL, 0x4FF2F7969E935E5EULL, 
            0xCC346D9EEF7BCC22ULL, 0xD2373384F91D1CBEULL, 0x0050BF15026C95D1ULL, 0x40FFCA2F01D17402ULL, 
            0x55D93562E74F4937ULL, 0xF7DCC9B99755D2F3ULL, 0xB0382C5DB88B7DAFULL, 0xCF83075BE42565DCULL, 
            0xF877D91808976BF6ULL, 0x76C50C66C1A43196ULL, 0x7234706B9F575303ULL, 0x55F1219370BA2030ULL, 
            0x8A727541110F3D4DULL, 0xE30138667AD0526FULL, 0x04FCA91D7D5CCC43ULL, 0xE11E194AA9FDFD64ULL, 
            0xE6E59BA8EFCBC0F7ULL, 0xD2C794D5FD24F598ULL, 0x4B5C07FB512C3714ULL, 0xE78BCA9847065193ULL, 
            0x9D74581C9BDB4BDFULL, 0x5A764B545179C50CULL, 0x60C7A2C7456F2900ULL, 0xB24D70B365E44F29ULL
        },
        {
            0xB7181F59A1A4990BULL, 0xA9D308419F369833ULL, 0x1C90069CDE9AFE6BULL, 0xC94C9443CC4DF7DFULL, 
            0x17B1DDC8BDCE159DULL, 0x364E7B8CEB675E8AULL, 0x17CB831CEC3391B2ULL, 0x28C83364180F90DBULL, 
            0xD68845CFC947B8E7ULL, 0xC1B0127FB8D1DF01ULL, 0x4916F36B10FC2FC6ULL, 0xE9534F623C3F58B9ULL, 
            0x17A1DC0E05B1B994ULL, 0x985D23496D3BED6DULL, 0x636714C9D328D958ULL, 0xA3DA880153BB3204ULL, 
            0x525FDA262FCF5E49ULL, 0x14D776F8618E91BCULL, 0x846078129E8F6DD9ULL, 0x91FF243238645D6DULL, 
            0xA366ED6E451AF63FULL, 0x0B3712FC24C27B73ULL, 0xDF09FC97A2945C8CULL, 0x15A16C693AFE7B7BULL, 
            0xA9D9753A942F2CD5ULL, 0x53D582EAF721DF19ULL, 0xEBD78C40260605E4ULL, 0xF621E731E169351EULL, 
            0x3385B82775418357ULL, 0xE2C0C29658921453ULL, 0xF21A8AB2A33310D2ULL, 0xA78EE9BBB2C40CC8ULL
        },
        {
            0xBDD4E73003D4CF3EULL, 0x0DBD087B637E71BAULL, 0xB6D9A57AD6100061ULL, 0x8A36029FDD608E21ULL, 
            0x5147B52EC0FC77F0ULL, 0xDA0F91FB75EB432DULL, 0x1CA31D1ED76F4DE8ULL, 0x43AC23EF8F2A3743ULL, 
            0xABA62FCED5DE42E3ULL, 0xE6818B1B91A7F5E6ULL, 0x2BED9D6B719285A8ULL, 0x820DA3DF666D905BULL, 
            0xCAF43B0F1DE2EA6DULL, 0x9993FC2B40D55564ULL, 0x75DF34A0CCDA3194ULL, 0x7EF76717661B22DFULL, 
            0xE9C909A47B95D049ULL, 0x6D4EC5855A48E386ULL, 0xF99168A6B6F4F7D4ULL, 0xB5D4699FFFED9C76ULL, 
            0x3F88BE531D2F92F1ULL, 0x213F958D728678A1ULL, 0xF7FEE829D70E111EULL, 0x04A6205BEF176E0CULL, 
            0x7C0897BB7D2CF0B7ULL, 0x7EC20C5B25956833ULL, 0xF4ABCB63EE8700CFULL, 0x0A641A6A1602615FULL, 
            0x0C6EFEB57B17A966ULL, 0x5C2F766005947244ULL, 0x54D394DD0FF2453CULL, 0xB4F7A9CF243FB30FULL
        },
        {
            0x15E54A3EA4118731ULL, 0x6BCD7680CED3CDA1ULL, 0x6223AE20139F480BULL, 0x152C39F1B0BCEE6DULL, 
            0x56DE1ABD7EAE461CULL, 0xB5CCE37C16CA0C7EULL, 0x3453C3FC3FD50DB7ULL, 0x80E08678732600B8ULL, 
            0xE29C5671F099F6C1ULL, 0x90FAB9D14087CAE5ULL, 0x0CF772393D8DAE8CULL, 0x5255A0EA1A809338ULL, 
            0xFB6730D843219691ULL, 0xE9B81E0FF87B7FFAULL, 0x7660AE117C80F030ULL, 0x3588438FF87FFA4CULL, 
            0x40399E47C4227C7CULL, 0x74CF28C53863ED66ULL, 0x9BEF060FA00EF2DBULL, 0xEB8BC3030249269FULL, 
            0x3B881F29D8401B65ULL, 0x111A4677C3B6FB7EULL, 0x3EB1F3252D4D1CC5ULL, 0xE66931E2581E0FCDULL, 
            0xA8FAD88C5AFEA28EULL, 0x53CB2F23739977CBULL, 0xDA5D3A6D276CA211ULL, 0x99034DEC9F2F2A00ULL, 
            0x0E768264BC38CC74ULL, 0x28273A6146380AF9ULL, 0xF9FA6CBD04727F2AULL, 0x3768203AEC764FBAULL
        },
        {
            0x6447D5336B6D7705ULL, 0xB4B075D0E4F09049ULL, 0x42D9231758F4B63BULL, 0x08B87491FDEFABEFULL, 
            0x3E0796DC49CEAB2CULL, 0xD597A1A4971D9B7AULL, 0xEFCB8F24150C2997ULL, 0x0FE793C9B51037A3ULL, 
            0xFEC7AF7E5962D12BULL, 0x97CB02D4CBB19986ULL, 0x98D136B0688A77A1ULL, 0x0363E45F272F413AULL, 
            0x85B11F2CA3829032ULL, 0xC1865429E7F82E22ULL, 0x669FBEB74CFED0FCULL, 0x37A8E3234272A589ULL, 
            0x681E1BE50C9585F4ULL, 0x403058C2A68A51F4ULL, 0xE89E2E63EB18DF15ULL, 0x1200C22EEB29C4B0ULL, 
            0x2AB91A12791E19F9ULL, 0x21689A0FE81477BAULL, 0x57EE51B2C1A01B0BULL, 0x3892AECC058BAF66ULL, 
            0x33D4FC98B8F660BEULL, 0x4839E8B0773E3783ULL, 0x2F92FE8692D44623ULL, 0x034C4F259834946EULL, 
            0xFB00550F59414D0DULL, 0x25BAD76C5491BDB1ULL, 0x6F2B1A4B626410B8ULL, 0x08E1A459DD68E808ULL
        }
    },
    {
        {
            0x60CF7CC0BA60B062ULL, 0x14CDB66C2A2FF894ULL, 0x549E3CDAA7AE0AD9ULL, 0x94FEB3C8BD0E9333ULL, 
            0xC7BDE2E809DDA86CULL, 0x7BF4C1687E056902ULL, 0xE25EA3C89AE583CAULL, 0x4F06DAD019D73087ULL, 
            0x8F23DE8FC40C87EBULL, 0x3F733C8713885D78ULL, 0x5877444E094FD3D8ULL, 0x2217341F97FDD391ULL, 
            0xE970445C6F6AFDCCULL, 0x104571A680BED42DULL, 0x4E03019923931FA2ULL, 0xBE9317B5D86482ADULL, 
            0x335F25BBFB3979B6ULL, 0x566F222EBCF282DBULL, 0x3FD59497C9123FF4ULL, 0xE451165FB5B3CEDAULL, 
            0xA949FB6690B8D3CAULL, 0x5E16F032BBA3B422ULL, 0x930D39A3234A6448ULL, 0xF8578D2F134F4D8FULL, 
            0x39E12C87EBE15F0EULL, 0xAB95A1D6FA00846EULL, 0x020B9EE37E5606A0ULL, 0xE24305A8398763A5ULL, 
            0xEFB77B90D329E23AULL, 0x9E396AD188494AD3ULL, 0x3AF2D563F379E051ULL, 0x0E1D0E4EC054DE0BULL
        },
        {
            0x1551DA309FDF2EF3ULL, 0x694617B650840A3DULL, 0x7ADFD9C2A4DAF8BBULL, 0x83DA3EB11C07CC2CULL, 
            0xF68D94D78B73FB31ULL, 0x1BC85A78F1453A75ULL, 0xCEB0F83BA24F6398ULL, 0x0FBC1125103C63B4ULL, 
            0x570F8DEC13F49536ULL, 0x62C9C13BAF5A202DULL, 0x4E79B31D91C9FE96ULL, 0x15CB6F75FFD1AE68ULL, 
            0xF699BADB2B2CAC4AULL, 0x68F44364516B11B3ULL, 0x6E94255D2382E6EFULL, 0x1BA9C6183C41EE2DULL, 
            0x391B54863D67A5F8ULL, 0x719184D4F096DC72ULL, 0x3A1C14DEF195B34CULL, 0x8C3C553E7333276EULL, 
            0x84F72A267CD26C77ULL, 0x4C8A41C67DB29E39ULL, 0x3D6CE58DD5D409EDULL, 0x05FBD4DB111A092CULL, 
            0x3F554B5C07335D54ULL, 0x0067E26DB70AFF2CULL, 0xC82A2572FF18F8DCULL, 0xC4571E77753C07AEULL, 
            0x8C8B793852320297ULL, 0xC0D958C3DCA07C30ULL, 0xAA412B0C186B37CBULL, 0x4FB587EB0F17C092ULL
        },
        {
            0x12AB55B9A9B4772BULL, 0x1CE2663171B1D9B6ULL, 0x8CD5FA6996019601ULL, 0xBA486DE0F4A58799ULL, 
            0x3C592AE9BAA07B97ULL, 0x2ACE4A5D8041163DULL, 0x12B96A959182466AULL, 0x9E273CDDEB44AC75ULL, 
            0xC183DBF361098395ULL, 0xBF2CBD0D19DCFD18ULL, 0x4054F7C9C2948229ULL, 0xF02A62A2105E246CULL, 
            0x0B493B0316007386ULL, 0x69B18942DE256331ULL, 0x7EB55914CF81275FULL, 0xFE2051E3D4A459AEULL, 
            0x42F121E72047AC1AULL, 0x0D9755CC152FB55FULL, 0xCF6006DC4A021704ULL, 0x3CEA2B863A73B087ULL, 
            0xF1B1E770E5B93BB8ULL, 0xAE1F4F3CB2BB093AULL, 0x03B2660BDB090A08ULL, 0x2F6EB484C987A63CULL, 
            0x1217783F9A419CB1ULL, 0xB6DFFA6E7432EFD9ULL, 0x7B45D511BAD99FC9ULL, 0xCF32028353073AD1ULL, 
            0x4743015D1D6EFE0DULL, 0xFE06BEE3615C3FABULL, 0x23C953233E51DBECULL, 0xC929E670015C95DBULL
        },
        {
            0x3272312E668DD6BBULL, 0x1564746459F68694ULL, 0xFED9C92F297961C4ULL, 0x9A5CD639F24FE8A3ULL, 
            0xC5DED8D542F57F21ULL, 0x00E81522197E5533ULL, 0x89F1FBFF4380451AULL, 0x50B618665BB2A0A6ULL, 
            0x3E6B69F4705D5718ULL, 0x8538BF6815BC673FULL, 0x418826BF0EDB42E0ULL, 0x72B936F86A20CE8FULL, 
            0xCED93246FB5FCF91ULL, 0x6D19303EB0F84FD6ULL, 0xE071BBB9E249435BULL, 0x0F4088C47FDB65D6ULL, 
            0x3A0F9027A9989920ULL, 0x90834BAF487905C1ULL, 0x11530C964FA92B34ULL, 0xB845D1B568C91AB1ULL, 
            0xBCAE8FA55C392FFAULL, 0x3D1A5BAE4D3599AFULL, 0x956A3493B47A974EULL, 0x4FA75D4D9227CC4EULL, 
            0x52031CBCB1890D77ULL, 0x4B89238D6959B77FULL, 0x3352AEC719570EBAULL, 0x58E4E4448F606AA0ULL, 
            0x97697A2136D0F249ULL, 0x5F2259FF2EB6168BULL, 0x251100E559D65E39ULL, 0x7C4797E9CF5605DEULL
        },
        {
            0x709034AC5CC62327ULL, 0xFE1B1D083DD08286ULL, 0xC3AB6920A95456DFULL, 0x146305BED77A0CD5ULL, 
            0x244EE023F605DF69ULL, 0xD3FEF054F7FA220CULL, 0x1F139B722E3237EAULL, 0xF3C3258B6F93D0C4ULL, 
            0x28073586BF716FF7ULL, 0x9B8B28834038B2DEULL, 0x9EAE260C20696DA3ULL, 0x20785D002485D598ULL, 
            0x7C020736EFB697F5ULL, 0xFBB08812ECC34E84ULL, 0x117A69776E7DAB48ULL, 0x5773579DBF6CD938ULL, 
            0xA77E46B9C109F4B5ULL, 0x4CE19D4221465AD2ULL, 0xEF0E9943A4843792ULL, 0x3B9DF9C313842486ULL, 
            0x3BD000A5E564CD1AULL, 0x6E57DF1CA4207F7CULL, 0xAEB0871FCBFA9D9DULL, 0xB379DAE3C3D45032ULL, 
            0x899F1BF493DD67D6ULL, 0x76497808E801BF3CULL, 0xD068BD17E400E53FULL, 0xEDBA684682542670ULL, 
            0xA7E67A18DB350EC8ULL, 0x6D79191AEA67E1F7ULL, 0xE3E76B1AB05A93D4ULL, 0xEB2DB88F8FD8CEF0ULL
        },
        {
            0x44159A72174D3D9DULL, 0x7E13D04B84C023ECULL, 0xE68A7A40D4A7EAD4ULL, 0xCFB491CFAB6A5BD9ULL, 
            0x8BB9C2EA3E7E2A04ULL, 0x56F563D15A23417BULL, 0x6B8D07584F555BBCULL, 0xE52BE98EFCB1C4FEULL, 
            0xCC6108B9F9477316ULL, 0xE1EBD9C087162FA5ULL, 0x124C9D615A4D8AD7ULL, 0xE4E918E648CE9E83ULL, 
            0xD1BF2CD7EB6FDD80ULL, 0xB25F2FE32EF3606EULL, 0x93C6A4097CF650E4ULL, 0x760EB91A117C0992ULL, 
            0x1BE1A569C8FDDDC1ULL, 0xE85A663DFB228455ULL, 0xEC0457D5F19BCE8CULL, 0xB93D2B89DD3100CDULL, 
            0x9ABABE9C34DDA845ULL, 0x47ABC97E80C66D78ULL, 0xFC728448DFE781F7ULL, 0xAA15C32D47405917ULL, 
            0x62A62C4556506F87ULL, 0xE6F9EDA4338AD8B5ULL, 0xE9957DCE8FE87B53ULL, 0x87CA656CB3262EFCULL, 
            0x33A2A30FBC48EA68ULL, 0x2AD20968BA2A49AFULL, 0x9A75240D036433B8ULL, 0x2E2C75522F3F5413ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseBConstants = {
    0xB30C39D645E38DA7ULL,
    0x787677C70EB39F1CULL,
    0xC5032654AA55AF79ULL,
    0xB30C39D645E38DA7ULL,
    0x787677C70EB39F1CULL,
    0xC5032654AA55AF79ULL,
    0xB9A92CDC8342D548ULL,
    0x55522646A463482BULL,
    0x7E,
    0x11,
    0x98,
    0x32,
    0xA6,
    0x34,
    0xE4,
    0x87
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseCSalts = {
    {
        {
            0x528FA1195B5E03AAULL, 0x51B78DE02889DA28ULL, 0x322A76792B917F79ULL, 0xC58B2F2EC75E704CULL, 
            0x135F7B5E335B842CULL, 0xDF5B4F6D9A26B0EFULL, 0xD4F7BD1E0B0ED710ULL, 0x153C16641CA28860ULL, 
            0x725BEC217172502EULL, 0xD49B6CDB1BAEA0A5ULL, 0x5E56FDA9B76BE719ULL, 0xE25C9620CEBF7612ULL, 
            0x6D413A55B6834DEFULL, 0x6668BC946EF26EC4ULL, 0x3B1BC23BDC5AB9C3ULL, 0x0B88DCD81000C8BFULL, 
            0x95A8DF139B30D544ULL, 0xB7A92312A3667FF8ULL, 0x83875C975C94409AULL, 0x056EBB3D3EDFEA8CULL, 
            0xD868A584EAA3B8BEULL, 0x9AADCB238BFEA38CULL, 0x9985AED57CECBA71ULL, 0xC6257B8AAF0D3C3DULL, 
            0x8325DFE9B12E0215ULL, 0xC19E46B0B94E24DEULL, 0xFD90BAF2DFBD4212ULL, 0x6198C42A6C029C14ULL, 
            0xC254A1AC8C319891ULL, 0xB54B1F3F3E9AD090ULL, 0x1FB2FAA548209C04ULL, 0xD9788C6197CCF874ULL
        },
        {
            0x06B8F337B331A29DULL, 0xBF7B995073C45DA2ULL, 0x10C3C4D359E96840ULL, 0x2CFDA4D79A80ECF2ULL, 
            0xE250B1F267A9DD95ULL, 0x6CC58A472A99CF5DULL, 0xFAAE9ABDA45B4C3AULL, 0x9BAB5B35A84A252FULL, 
            0xAA0AB2E2F8511D3CULL, 0xB815E9C3D62FD785ULL, 0x0D5AFC459B9134A2ULL, 0xB4B11D2528C96C7EULL, 
            0x99B4B43EAA7D5B5DULL, 0xCB70937C7C6DBD8CULL, 0xFEBBBD1F6CC1C26EULL, 0x6237FCA90834ED93ULL, 
            0x3DFF570FE31954BEULL, 0x517C93B29A6BA9B0ULL, 0xD2042E31F11BF031ULL, 0xDD8013D039E1FC09ULL, 
            0x43D08FA75DAFDB71ULL, 0x3F8AAC5001599E2BULL, 0x18A9075A788B5AABULL, 0x4DAA6A3C53CB0A57ULL, 
            0x272F963DF57E736AULL, 0x24CF4CD2C87C2DA4ULL, 0xFFBD814FA11AF5AFULL, 0xC6906A5BA14B92B1ULL, 
            0x8BD7D41B9427AAEBULL, 0xD36CE2BF233973A3ULL, 0x97AD9045835ADA3DULL, 0xF9163244CD5D9F68ULL
        },
        {
            0xA0D739157EAB1BCFULL, 0xB86EE044258B4802ULL, 0x2BF950067AFB0322ULL, 0xE45C6356FB8E448DULL, 
            0xDBBDC59A3101B7FEULL, 0x8DEB879AF30909D1ULL, 0xEB4D3644B64BD289ULL, 0xB8C8EBCE5632CBF9ULL, 
            0xA91094A76CB6F68AULL, 0x31A02F01AE5A5601ULL, 0x35A90D4BBFCBC4AEULL, 0x40D3FD746CCBB937ULL, 
            0x516BA467363C328DULL, 0x7268B7DA80A07EB7ULL, 0x1548C43C14622AB8ULL, 0xBB1AEA1C4D27E23EULL, 
            0xFD997176991B3CBBULL, 0xE068358BCCCB5BA2ULL, 0x9423BFDE0584C15BULL, 0xF43D8DD55BF43959ULL, 
            0x38C1D16AE0BE8413ULL, 0xF4CB2F5D9CF6F6A2ULL, 0x2BEF46B5EDEE06D9ULL, 0x6FA0E44773307105ULL, 
            0x46F6212DADFCAFCFULL, 0x2C80EF7E3E5A402EULL, 0xAE9EEF5B78FA9F59ULL, 0xCFBEDAA73177E7AFULL, 
            0x7EF378D70E64A952ULL, 0xC781705002BFBC19ULL, 0x141887340FAF9598ULL, 0x3085721938FE7B7BULL
        },
        {
            0xF5896E55E02BE863ULL, 0xF4ED519FE1FBB3FAULL, 0x87751A65796727D8ULL, 0x47A46E7DFD8353F1ULL, 
            0xABB57A33C8BA8175ULL, 0x46AF6F253B1DF0C2ULL, 0x1733DABE1A36D121ULL, 0xFFAE886C303C050DULL, 
            0x9092BDFCE6D6C7DFULL, 0xB7CD7D56E4C8616BULL, 0x3DA679E499D32977ULL, 0x82DF702E1AC01D6FULL, 
            0xEB7D8AA7DDA19B06ULL, 0xDBC35F25055809E4ULL, 0x5945636FB7E3117BULL, 0x2741D3457373D904ULL, 
            0x33455D141BD23BECULL, 0xE8A29847D115B23CULL, 0xBD92F3EB254A3269ULL, 0x1AF00F566B0FA2BEULL, 
            0xA91F094190B9E45CULL, 0xCE7D87434A14A4AFULL, 0x0FABB127374E42CFULL, 0xAA85CC925E47B889ULL, 
            0x2EE78F491F717047ULL, 0x9242C1DD57E2A9EDULL, 0x12A1B4DAE004E582ULL, 0xCA0E2484F26F6236ULL, 
            0xEC6E32D01FEAA162ULL, 0xAF2D661EE052B329ULL, 0xEBA212A2CB1976A9ULL, 0x9D9F7CC003794CE7ULL
        },
        {
            0x6016D986E72A3325ULL, 0x137811C0D149C0AEULL, 0x3FD1E1E9F7D106D9ULL, 0xC47157E1793519FDULL, 
            0x8C8D150FBAF1F658ULL, 0xCCA82CBFA7BD2739ULL, 0x35AF8D55A794D6E2ULL, 0xECC2AEC0AED13B59ULL, 
            0xAF642530D5EE6044ULL, 0x3ED52AFC4F81E2AEULL, 0x376345646A6C0C1AULL, 0xE39FA731F26DEC54ULL, 
            0x3EAE9594ED24603BULL, 0xBABEC21345428EBDULL, 0xF9FC8C8D2796C9AEULL, 0x1AE41734E06A5AA0ULL, 
            0x9ABF1DDDF6F44DB2ULL, 0x9F3D6597C05DC5B3ULL, 0xA8E00F792E77D586ULL, 0x690C3F0A04707FE3ULL, 
            0x57D167D08E954268ULL, 0xFB4116825E1B70A6ULL, 0x5A994B11825AEFE1ULL, 0x26497C96117EBB16ULL, 
            0xEE47DFA043997DD6ULL, 0xC5F76BA232EFF283ULL, 0x15BF7B56B31226ACULL, 0x4E050ECC94E961F2ULL, 
            0x6953B2CB88ED6C50ULL, 0x8D5EFFBD5EBD6E1FULL, 0xB391FD0F96E0A867ULL, 0x686792F32BEEFB36ULL
        },
        {
            0x8FF9ACDAD0A1530CULL, 0x09C7066E8ABF2D87ULL, 0x8D0C804419975EA8ULL, 0x29EFD2DF63633398ULL, 
            0x4E32A474A40E6B90ULL, 0x50A2D48D9C09314EULL, 0xC689A387B00080A5ULL, 0x24F378F8941B1E94ULL, 
            0x76E6CFB690AAE512ULL, 0xD851A77BBFA28AAAULL, 0x8A0A6A58D31EE7B5ULL, 0x44FE3CE34D23240AULL, 
            0x50F826A2DB61255DULL, 0xDB834CDFCCAE4319ULL, 0x31CF1A88218311FCULL, 0x988E5069D0577129ULL, 
            0xF56DD646E5530643ULL, 0xF9C053B0EFD9D321ULL, 0xE3385CFBA615259EULL, 0xC9664609638DDDB0ULL, 
            0x9BC5AF7F63953B60ULL, 0xBFEBA7B1C44D7310ULL, 0xD91B30E0EED70FA2ULL, 0xB0AE7B29D66892D2ULL, 
            0xCD2B2BADEE1BFEDFULL, 0xE475FEF3DF7A6393ULL, 0xF3F00880B2D36F99ULL, 0xCD2C1F730D4B9926ULL, 
            0xA7B4A89B5F8C38E1ULL, 0x042D1CBDDBBFC09DULL, 0x0BC1E88EA2299983ULL, 0xCB1DFA191B70EE2FULL
        }
    },
    {
        {
            0x379017462860F65AULL, 0x8E189A6218AD1348ULL, 0x4933AB3CDEAFC638ULL, 0x4E7DB3A8AF6B4C35ULL, 
            0xFFCA38445789958BULL, 0x00BE74EB84D5AE22ULL, 0x76B59B2F1D471E29ULL, 0xF051D486F8D3B794ULL, 
            0x09F4A0C31F8C44E8ULL, 0xCB946DCDA47D97F5ULL, 0x9E6F8092DF4C472FULL, 0xE314A3D07DA3BF1CULL, 
            0xB759C82803DAF6A6ULL, 0x04497723F7A21441ULL, 0xECC7192E9B4BB587ULL, 0x15B32BF6ECC62318ULL, 
            0xF46A2654EEB07DB6ULL, 0xED62595A09BC3B5BULL, 0xD42DD9782AF4DD1FULL, 0x14E52DB4F6D8905BULL, 
            0xF6789D3B0843EBADULL, 0x0CE1D227B09CA953ULL, 0xB9A68C9F5EDD9688ULL, 0x868FABF5229FDABCULL, 
            0xF48659ED714D51B6ULL, 0x3737EA25A16B8907ULL, 0xA715D2935702AF30ULL, 0x72FE81BB555B8750ULL, 
            0x1491D4017FC1623CULL, 0xE9B47C024639A244ULL, 0x47EF550BD4F4A92BULL, 0x2B77EDAFB8949823ULL
        },
        {
            0xF8156A2997FEB8F6ULL, 0x19FB659BE83565A2ULL, 0xECB576626E0A84B2ULL, 0xD56D5C19B102164EULL, 
            0x0C335F49ADFB0608ULL, 0xA0BA4B991D956DD0ULL, 0x552AF6D50DAD0853ULL, 0x8C10152EFEF64BFAULL, 
            0x0BFD912A0CCF302CULL, 0xDA5E4FAAC5BD57A9ULL, 0x4C3B2079F7E57D68ULL, 0x8752BC536888EC36ULL, 
            0xE848F2D0AF100158ULL, 0x425D0081568D5DFEULL, 0xC3FE9658D2E62820ULL, 0x577161F9FF18C17AULL, 
            0xD917618E193996AEULL, 0x5DA7369504EBB2C6ULL, 0xA3430CDF47D70994ULL, 0x24E0DD3E579A298CULL, 
            0x0C435A0D9D6075ACULL, 0x40A357F201752BB2ULL, 0x4F7A53749267313EULL, 0x0EC1B0B264993E1DULL, 
            0x056A9C41FE905297ULL, 0x9C5A5A08027688D9ULL, 0x564BC66F31DEDAFAULL, 0x5D4CD145930601DBULL, 
            0xB1838C60ACFED3A7ULL, 0x612BDF4540E0B32EULL, 0x8C8DBB5E194F8748ULL, 0x7E8A2499EE1FF064ULL
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
            0x463794537F35EC20ULL, 0xE779D445E83F0E8DULL, 0xE5637031EE957046ULL, 0x12C68D6BC5118190ULL, 
            0x05B31C8CB6BBEA81ULL, 0x41A27D07E89ADBF2ULL, 0x2E40A9CE33DD174AULL, 0xC52CF35961D0542BULL, 
            0x59D47BAD4DF44BBBULL, 0xC3931DAC41F4F1BCULL, 0x1F0C8E1A6E01AE97ULL, 0x0BA7B1894422C74CULL, 
            0xE38EDB3C834B759AULL, 0x1192D46032C16470ULL, 0x16E2DA95AC101650ULL, 0x01DB203932963043ULL, 
            0x9F00058C7C6ABFCBULL, 0x42228C4D93F1B3EAULL, 0xCF51BD80F4865EABULL, 0xBF78E13609AC2C07ULL, 
            0x4D7295A0FAD8270AULL, 0xE3728777C1EE86CAULL, 0x5E9F3E7499B05FAFULL, 0x886C04A45A888F47ULL, 
            0x4F5F05C0B0B9402BULL, 0x5046063451D119A7ULL, 0x2B96E6424B639FDDULL, 0x7AAF0463673641FCULL, 
            0x78A152ABB20AC3D0ULL, 0x2FA59A7A48D42E5CULL, 0xFDACD8F9E4C65EEBULL, 0xA20774BA99CBA2A1ULL
        },
        {
            0xC960136A4D5C68AAULL, 0x788424FF6CAB1FC5ULL, 0x5408E0F8C2113850ULL, 0x4025F4D16978A496ULL, 
            0x5797F048A81B9349ULL, 0x08B489CDC1D42992ULL, 0x78AAE6E6219E4471ULL, 0x20FF4FC29A7D7440ULL, 
            0xE50E1A2D0CF3FF2AULL, 0x31F7FE48D8EFF47BULL, 0xCCA1C29D4D918657ULL, 0xB96ABE67EE9E3B46ULL, 
            0xC8D25196977A7FF8ULL, 0x932F65A66AE8342AULL, 0xA6E846D50A59832CULL, 0xE77A5B2BADE2C89AULL, 
            0xB2099E30F848A326ULL, 0xE97C311F6C04618BULL, 0xDD4FF946E824BE9AULL, 0x9A8081658CF0B40CULL, 
            0xECAE23BD6339FF93ULL, 0x38FAE591CBE4E0A6ULL, 0x04FB5A995B3B7F51ULL, 0x0157C49456C5DCD5ULL, 
            0x83DF912AF212D4E0ULL, 0x1468C830A871969FULL, 0x70081CF59894AE80ULL, 0xEC2B437E69A4CFFFULL, 
            0x96FA10A681D43DC3ULL, 0xCE416062E2B99A81ULL, 0xF03CC2BCD36637F8ULL, 0x01F3C95F4D62BC97ULL
        },
        {
            0xDA460EF2C09025F2ULL, 0x158FBFCDB695596BULL, 0xC37F1A12AABDB8E5ULL, 0xA970312887D0FB74ULL, 
            0xCD7EF422A3EDDBD0ULL, 0x3D2EBCF20F109666ULL, 0x888E5E233FE2A317ULL, 0x9D88920AB045A320ULL, 
            0xF98B8475EEA2916EULL, 0xEAB119E4B51E495EULL, 0x4B16C0F7BBE58FD3ULL, 0xEF0F21D5FA2698BFULL, 
            0xD1A079E98C43C6FAULL, 0x70D20B8B3ED864BDULL, 0xD03505EF3CEC0D45ULL, 0x3D5E0A9DEEDE74DBULL, 
            0x5C1D53EF7B35A535ULL, 0xA98D5AD4EB37D272ULL, 0x992E46181E1FA5FFULL, 0x4C2C1E8F08E12533ULL, 
            0xB54D38078783CEE7ULL, 0x6E11C432CE7F66D4ULL, 0xDFE8ECB9515DD914ULL, 0x248F3FA6F8F9CCE3ULL, 
            0x4CBE7F768CC5D103ULL, 0xD0E12E430C8C53FEULL, 0xE74A1CE851398493ULL, 0xCB1BF3FEE3A13ABDULL, 
            0xC6DE18952553EF90ULL, 0x21EA3849E60637A8ULL, 0xFD0A7B57C1DE9A5BULL, 0x11596D3CFF180917ULL
        }
    },
    {
        {
            0x910662664E968F4FULL, 0xE4D46B9EFD53236DULL, 0x69608910767EF587ULL, 0x58F2F370AB859BA1ULL, 
            0x86DEF4E256925C6AULL, 0xAF3E5499AF628CF1ULL, 0x46B7D8D6A30FC7F1ULL, 0x05B36FE618A87A05ULL, 
            0xE46A5E1577E950E3ULL, 0x102F0CCD16413219ULL, 0x4648D68790034B3BULL, 0xA1009D665B2C4BA0ULL, 
            0x96D821A0EDEE1EBBULL, 0xF76C4699D545F857ULL, 0xF298DED70C172321ULL, 0x842F55D70589362EULL, 
            0x3CB8FA6B738D4794ULL, 0x42740F413C10E164ULL, 0x954CB8E5A079517DULL, 0x2823F845AC7E383DULL, 
            0xF93A01BEF85A9FA8ULL, 0x379FB8C9089EEAC6ULL, 0x8B2F2A32998C3157ULL, 0xDBC1FA7B172A8BBAULL, 
            0x4945584C32353085ULL, 0x48CC3D386EDCF55AULL, 0xD198E809E944F0FCULL, 0x950477949C061765ULL, 
            0x5B51C9B50D68F3A4ULL, 0x13409CD65F7826D1ULL, 0xFCE0D4FA727FA0F8ULL, 0x2D5BE61A1C989FDAULL
        },
        {
            0xCF0A1A8AF930CAB0ULL, 0x878F22D908FBD528ULL, 0xCF4B683473D6EEF1ULL, 0xC5BC8C5EE64DF1BBULL, 
            0x9CC5154B24A104E4ULL, 0x591D592A6EA328C4ULL, 0x9A401A66BBE6C3B3ULL, 0x3315A9D4C6DAB3B9ULL, 
            0x451D85926121BA75ULL, 0x3ED20FBA62E59CC1ULL, 0x5A9E34E993AD69CDULL, 0x8B51CD7E20699DF5ULL, 
            0x90EC99309632B13AULL, 0xFA689BE1BD1F8B3FULL, 0x37087DA61AC5DF83ULL, 0xD14188E60028868AULL, 
            0xFCC4A730EC089E48ULL, 0x3D07EDC3451E6D8DULL, 0xFFA9259A1D080A4EULL, 0x5C69EE6B05D32260ULL, 
            0xBED1A465FFD3EF4EULL, 0x82330BE0B3B2C22BULL, 0x7179446A8F288B4DULL, 0xF590991B46B62FE2ULL, 
            0xDF2C376E5C4AE355ULL, 0xDBB7E59949278120ULL, 0x83951A832AAB7D66ULL, 0xD0BAC7FB8E1EF5A1ULL, 
            0x3C7C96FD6564A470ULL, 0x29CFA192D46D7746ULL, 0x13E6D1CD23373339ULL, 0xE5350180697C80CAULL
        },
        {
            0xD8AB26EB6A4D92C4ULL, 0x7FDAD5C762A704FBULL, 0xE4ED8CA01140EEA8ULL, 0x897151FE3BD7449FULL, 
            0xB527C3B3FE07520EULL, 0x219C23E83EB50045ULL, 0x9C21FB7B8092D26CULL, 0xE05719C16A7F109AULL, 
            0x55DF912A20706187ULL, 0x34F7B45B9D7CB2C5ULL, 0x48F2F043B501A920ULL, 0x0460414AFFA306FBULL, 
            0xA7F55486A8B9894DULL, 0xD438E36ADAB3AA8FULL, 0xFBBD40EE9501BC22ULL, 0x02EFB8C985322B9EULL, 
            0x398085FD270C5AE1ULL, 0xE659B3370DF085D8ULL, 0x805F22CF30C81C37ULL, 0xA96E545C3D8ACF20ULL, 
            0x8DAE6BC88220BC8DULL, 0x30C6AE83795D7532ULL, 0x5987ECC9427FD843ULL, 0x42E8FD71283BBEADULL, 
            0xAE4FB3E0CC5437EAULL, 0x63E488BE8AEECC8EULL, 0xE686FE14237AECFAULL, 0x109B55475FD2F010ULL, 
            0x7BC67173E8B1AC6BULL, 0xD4F05A3C5E0A517FULL, 0x4FCFCEC9C90FEBAAULL, 0x7B5796956B0D765AULL
        },
        {
            0x1FDFF0506B667EE1ULL, 0x3B49923AC10DBCEEULL, 0xDC2298CB4662119CULL, 0xFB7EC385A4391C4CULL, 
            0x97BD95A307A48255ULL, 0x9CBA045F6338FC17ULL, 0x4AAD25E05752FF3DULL, 0x9435D6A1D50BB160ULL, 
            0x0AAD72E6B59128C0ULL, 0x79E4AE32863A3C8BULL, 0xB8577C84DAC2F4B1ULL, 0xA93B9DC601C292DDULL, 
            0x1D70257CFA8F3268ULL, 0x1DE398D0EAC75629ULL, 0x7F77B2EB100A9848ULL, 0xB34DA91E4FB31CDCULL, 
            0x421034519B581A4DULL, 0x77D085A5D74ADA04ULL, 0xB2D12B54676C54CEULL, 0xB38B74C0499A4310ULL, 
            0xCD355081655CB45DULL, 0x177C7566258BBF52ULL, 0xFD82BC35001BFE8CULL, 0xAD0D50EF610C10F8ULL, 
            0x793AAF14B2A92528ULL, 0x1824B10FCA11BDA7ULL, 0xE0BF9F28FBEBC3FCULL, 0xD4B79A29EA39E708ULL, 
            0xECA0CF3CECC53BBCULL, 0xD9B73C4B4886E2E5ULL, 0x5102D9F92383E183ULL, 0x2A6CB54DA96A9D43ULL
        },
        {
            0x29FF521D53B536DDULL, 0xE7E610B0172F7EDDULL, 0xCB37C93A5AE442F7ULL, 0x8F9CA772BE44D177ULL, 
            0x7FB5BC1F3A3F0526ULL, 0x91EB93342E1DAB04ULL, 0x24F13AC44CDB4565ULL, 0x3BFB2513CB90AC19ULL, 
            0x9C2B10685DEDC546ULL, 0x8D6957288AE22DABULL, 0x0C8232A06771A45AULL, 0xF9CA7D30778E0D1DULL, 
            0x21E7657F502E2E42ULL, 0x88ADE7DB1ADB1301ULL, 0x24F5B8BF541867E6ULL, 0x06968DB8CB304BD9ULL, 
            0x70B2C85BA6ED299CULL, 0xB210A3C84DD49143ULL, 0x0E36B9BDBDE009FFULL, 0x8FAA03C52E53DB57ULL, 
            0x8107266F889BEC77ULL, 0x1597BB92B29E3236ULL, 0xDAD284CF3DB04599ULL, 0x2B7B6ECDB4BF2924ULL, 
            0x075131298BAA5355ULL, 0xE5C8000ECE840C4BULL, 0x18A551CAEE7852CCULL, 0x8F5EFA53E6CA103FULL, 
            0x9D7B40039CED3B7AULL, 0xFFCE409027066D1DULL, 0xAE1BE60248E8F3EEULL, 0x0DDD7499181B6196ULL
        },
        {
            0x6748AFF9E2DFA6B4ULL, 0x287FD33A8135323DULL, 0xB50159FE05F9B1F3ULL, 0x0F8F0AFFB8494F75ULL, 
            0xFF99997E9998EF08ULL, 0xF41EA6CA34738546ULL, 0x39BF214666BACCE3ULL, 0x230FB9097F1A520CULL, 
            0x099E6D42755A25ABULL, 0x8017B1B2EC4B02CBULL, 0xE950552556D767CEULL, 0xD9863EDEDFBB8B0FULL, 
            0x981E0DD80D2F8B28ULL, 0x300586A0DC750D99ULL, 0x81BD378AC077A010ULL, 0x767301EC17D07299ULL, 
            0x9D0D8D31A6A8CD07ULL, 0x83F3C324FC569334ULL, 0x73B94E03E633D6E5ULL, 0xA018F3AD7D65643EULL, 
            0xD16AA92951AED4BCULL, 0x12465A11AD003B4DULL, 0xCA210AA50258F7FFULL, 0x991A95032379CD90ULL, 
            0xB50DAE8A2E53D078ULL, 0x28F08B532102F07FULL, 0xD5AF7C7A6AE341D4ULL, 0x87CFE969712165B0ULL, 
            0x6EA6B96253E42CCDULL, 0x02E241E58B0BA229ULL, 0xA5804F9DC0BB782FULL, 0x834FAC6F73DB1A1BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseCConstants = {
    0x83B1A87505EAA0AAULL,
    0x5CB9FC6BE73B286DULL,
    0xAF5E755D1B224811ULL,
    0x83B1A87505EAA0AAULL,
    0x5CB9FC6BE73B286DULL,
    0xAF5E755D1B224811ULL,
    0xD6168F83A1AB4D7BULL,
    0xFFE904889F9EE1ADULL,
    0xAD,
    0x95,
    0x0A,
    0x4A,
    0xF4,
    0x16,
    0xE2,
    0x5D
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseDSalts = {
    {
        {
            0xC9AF7B979969EF2EULL, 0x27131F8AD6A0BAB3ULL, 0x5EAA5336D8C533ADULL, 0xDF1D77FCAB60265AULL, 
            0x288995E8AEC540ECULL, 0x9D2226F1AB1D0844ULL, 0x52377CE572B86CFCULL, 0x467912CA0063D1DAULL, 
            0xAF52E00E72BDFC0BULL, 0xA7EC1885B46EFAC5ULL, 0x977EB605149C3761ULL, 0x5F7008579335DE7DULL, 
            0x35E7A7CAC0577946ULL, 0x5552C385956199CFULL, 0x272D1369AD8A610DULL, 0xBB0EBE0ECE488401ULL, 
            0x3C63564D7E24D663ULL, 0x5A3513A8691794E1ULL, 0xF7D558A2FF7A2686ULL, 0x680BA3B027308C42ULL, 
            0xFB499D9C6AED85D1ULL, 0x3B7DEF9E92DE265DULL, 0x3CB76AD50B29267EULL, 0x1F1569F17F96DFAAULL, 
            0xFDFC461CB2658E1DULL, 0x8C740CFBD5D64054ULL, 0xB6D6C4F0F9413C64ULL, 0x9F41AD8BBA55159BULL, 
            0xAD2ECF1731F6733DULL, 0x73ED94CED2FCE7E9ULL, 0xF0FAE0A833EF2FA6ULL, 0x9ECEBD52EA863AC4ULL
        },
        {
            0x6884B3D226714EF1ULL, 0x93338044EF91E5F1ULL, 0xAC311EAC44F684C1ULL, 0x53FF4E1590C284F1ULL, 
            0x07B5B1E590A1B607ULL, 0x5129EE8396E23F6FULL, 0x393E12DE2A56A6D6ULL, 0xCDD48781E3BAA2ADULL, 
            0xEE79E4C45F72DBB5ULL, 0xF47C3C40E44D661AULL, 0x61CCBF9135A21403ULL, 0xF476F60BF6BBF071ULL, 
            0x558BA8B5A562F53DULL, 0x0EBC54AD05262F6BULL, 0x56DF4B8E4E8A3F27ULL, 0x586BE6FB2B26E8F8ULL, 
            0xE6C6C44546C96679ULL, 0x208B9A8DD48724DCULL, 0x2EF23B6D2559A0F1ULL, 0x2280AAF8EE252A7CULL, 
            0xCF8122C13B831A68ULL, 0x8B442850BE5C59E2ULL, 0xD0558CF5DA9EC96FULL, 0xC5C0A33CA009D26BULL, 
            0x69D7CE4FB6AD1706ULL, 0xAE452407DB6F8778ULL, 0xE4E83682549EE58EULL, 0xB802826B12D2C839ULL, 
            0x1D7AD81C45FDE294ULL, 0x86C43DCE216F3BACULL, 0xC3A747B40FF343A1ULL, 0x3A6AA800517880B6ULL
        },
        {
            0xE97F2B0BABAC4859ULL, 0xC5A80BF90D89631EULL, 0x9F80F7B78D06BA3AULL, 0xCC869CC9FDFC1C6EULL, 
            0x56DC09FA9A9DADD5ULL, 0x681D5FF8285B0D02ULL, 0xFF8FE714546FA710ULL, 0x247AF6E651EA6A72ULL, 
            0x8C5D21553A4BD9FAULL, 0xBC53DC7B4397106EULL, 0x06604DAF963C14D0ULL, 0xFFEF7CBAD8509E80ULL, 
            0xFFE2E41C4FBF3543ULL, 0x9D611AA9243D33F7ULL, 0x4DD6BD51B1E25AF6ULL, 0x04A538B7FAA99C5CULL, 
            0x7D7615F12D77C7CCULL, 0xAEBC212830F50BD9ULL, 0xDA5B8B25A90A1833ULL, 0x9B5EF31836BF41FAULL, 
            0x03702BD2EDEE8986ULL, 0xE39FA4CF01D04EABULL, 0xB5D8CDA8373CDF25ULL, 0xC1E2A4B2F40F6C7EULL, 
            0x62E23D5161B87206ULL, 0x0DB1089BB4510C01ULL, 0x133AB2ADF7DF0C72ULL, 0x5C84B765750659D8ULL, 
            0xB63FBA142781F89DULL, 0x0C0C0BA5E3A9AB71ULL, 0xE158B6F1AE6B02BCULL, 0x19E64635E1F90C46ULL
        },
        {
            0xC13CF7BFCB6896F2ULL, 0xFC4A31286BA3EB10ULL, 0xD132C2D161C9991CULL, 0x27B629CDD794285FULL, 
            0x13A7DAAD49F90A9AULL, 0xE48BB3FDF5DCFA7AULL, 0xEB9167D51A359B04ULL, 0x36EA422E95013343ULL, 
            0xF97D24B26247489EULL, 0x833CDDFF4E2A7032ULL, 0x738A8B02C24E44A4ULL, 0xDA4E083A67D895E3ULL, 
            0xA722C35AB377F45AULL, 0x3BDB1B49DC8DF26CULL, 0x6DF0DBF244EDA9BDULL, 0x97FA1B8499BE90A2ULL, 
            0x9D0D0D690B0F250FULL, 0x878FC0D599BB343EULL, 0xEF2A3713DEF091BBULL, 0x46E40398DA9D3DEEULL, 
            0x88558C24E1417F78ULL, 0xE6B3F293D79F071FULL, 0x3932557CDE36E98EULL, 0x48B662DF4840FE7DULL, 
            0x99B30067BD1027CCULL, 0x3A23B19E6AF6CA1BULL, 0x813E47119D4EE8D4ULL, 0x5B9B5ACF07258DC2ULL, 
            0x396649F70DC29BD1ULL, 0x4EFF4EE0AA130CABULL, 0x27519D72E360AC27ULL, 0x1A7FDB2D12522023ULL
        },
        {
            0x33463943D40C1B4BULL, 0x880EF21157F328DAULL, 0xE48B0913D53F8B57ULL, 0x9CA95C5E69EA60BCULL, 
            0x6D0774368993E39AULL, 0xCE9924F8BEB173B2ULL, 0x7F88A15CCF53A2B3ULL, 0xA41FF53F70FC8C60ULL, 
            0x78D81763951F5027ULL, 0x7FF2479F3A078042ULL, 0xFDC3F2F9644B6839ULL, 0xD61B25067A1FE8A7ULL, 
            0xAE55C285F25C60B2ULL, 0xC9022A2816080FFCULL, 0x8A321098B73C4086ULL, 0x0855AF76265E51E3ULL, 
            0x46876C6E8DA3E311ULL, 0x68F6BF11F8B0D8C3ULL, 0x7B4B7D3E32B9A90DULL, 0x90FC3B38BA3C88CEULL, 
            0x73FD8C087B3FEA04ULL, 0xBEA1378D49599E20ULL, 0x3AF40170145E1EE6ULL, 0x7532CF6135894DADULL, 
            0x3064D50DF40144EEULL, 0x8A351A3D91B20212ULL, 0x9C643CF5493B0D14ULL, 0xDDB4604F0E642D6BULL, 
            0x85335DAD8391E549ULL, 0x14236605D916D8AFULL, 0xD83D96BE171BC1C3ULL, 0x8FBB2D23C7293F19ULL
        },
        {
            0xA272C1801E8E918DULL, 0x142E33481E16D93CULL, 0x0C0AB3E4F1DBD949ULL, 0xDA8DCF3F35C89144ULL, 
            0x77E90C1CED083E39ULL, 0x328D1DC4D5151931ULL, 0xA540056932BC130DULL, 0x8784869DAAC03F18ULL, 
            0x586DD66E7188611BULL, 0x41063118A016BF7BULL, 0xA9206F4093172D90ULL, 0xFD6823C1D9CB9967ULL, 
            0x7CAB36749177CFC0ULL, 0x682C65A1FAF4E09DULL, 0xCA5D3E39555B5A08ULL, 0xBC95C4269AFE2289ULL, 
            0xEC9FDD75D503AB8CULL, 0x702B7F1B2D0B05BFULL, 0x5A114971A5D083E4ULL, 0x4002908DD1C8D4D1ULL, 
            0x2784B9E7CD13D744ULL, 0xF7F63E34F8AD4321ULL, 0x6928B65DEFEBC85EULL, 0x262F053D7EE22A93ULL, 
            0x6AAC7B473259B107ULL, 0x3819B0DFC6F0B754ULL, 0x615921834DFF3545ULL, 0xEBA2CC17ADDBBA4AULL, 
            0x4428CD315782D116ULL, 0x926431B090EE67E4ULL, 0x419A917DA4E80B51ULL, 0x22194EE162D55F7EULL
        }
    },
    {
        {
            0x0A0FB03567092A23ULL, 0x92D78CEFAFBF8AD9ULL, 0x68A7E20B99B38A60ULL, 0xF36CC393ABA39FF0ULL, 
            0x77F2F738A2473651ULL, 0x9FEA431FDAC54447ULL, 0x29180DB172ACA4CBULL, 0x7A69374868A89179ULL, 
            0x918D085D7E31DDBAULL, 0x6FE281B24C764BF3ULL, 0xD5DC89777ACD9E03ULL, 0x8AC3EEB67F9060A6ULL, 
            0x8BC7195C48F80F67ULL, 0xB35A3C3B61F19F72ULL, 0x764F010F0D2EEEC5ULL, 0xFAB1446F7E8CD242ULL, 
            0xA41E1C39B8549C2FULL, 0x15126CF376173D9AULL, 0xFBE93E5FED996675ULL, 0xF2C6D57264A04332ULL, 
            0x01EF4E74E817DD8EULL, 0x669BB27C886C0950ULL, 0x2584900C4C0799C5ULL, 0x2E56A69D9D714939ULL, 
            0x24768EBC011F540BULL, 0x223349E60C4D7DEFULL, 0x18C2C83372E2633AULL, 0xCFC28C9FA8B2FF98ULL, 
            0x8B10237FC307F7E4ULL, 0x2009EB9FAC50B792ULL, 0x069F616722BB89B2ULL, 0x89C83EE6C5EE0FD8ULL
        },
        {
            0xAE566F8777D1A8FEULL, 0x6EBDC904EE2DDA62ULL, 0x0CBEEFC5184B203BULL, 0xA3F85B3168AD420BULL, 
            0x9C9304A590B6A9B7ULL, 0xDBC4D04B64223933ULL, 0xFF56DBC7E228918FULL, 0xB8E6AAEA119BE4F9ULL, 
            0xC4A12169E932769AULL, 0x70F872ED8DDD4132ULL, 0x70546FB65FB0C95BULL, 0x1BFFBF4907984CC5ULL, 
            0x60459A6C3A82E045ULL, 0x077417B0F03DE530ULL, 0x387F96CBCCF238BFULL, 0xD0BA4D8895F2AF16ULL, 
            0x566B03253FDD17EEULL, 0xAFE8FF9DC819A2D3ULL, 0x9FB18C24753A739BULL, 0x1EF2DDF077952CEAULL, 
            0x6FF5CAED22351D49ULL, 0xC1049850E46E69A5ULL, 0x3A386A7AB17DCE82ULL, 0xFDC1C5FF6C296C0EULL, 
            0x8C075A8EE0628310ULL, 0x087F45578B98043EULL, 0x63DC25BE0A37A680ULL, 0x4FA7D295B81CC2B6ULL, 
            0xBD5BEB04F4C74FA4ULL, 0x82F52883D5044F41ULL, 0x5A262CF4D3984A0DULL, 0xCE3DFC7BD5BF7B7EULL
        },
        {
            0x7CDB24A00751FD08ULL, 0x55E482563242CEAAULL, 0x65EECDDA555492C6ULL, 0x9A0E8BFE6E9B02DFULL, 
            0x17D05E6A0E9E418BULL, 0x369562B203FF8121ULL, 0x1FF66ECAFFF43A6AULL, 0xE53BD0A50F6B2273ULL, 
            0xED8106AF374EBD19ULL, 0x4AB8C23E78694370ULL, 0xA315C49BFD4245E9ULL, 0x6371EF42ADD02E02ULL, 
            0x435C2979FA5EBCA6ULL, 0x0E771E618E501AFCULL, 0x36A5EA2DD77C8155ULL, 0x69E0FACD215AC08FULL, 
            0x529A78ADF086F2E9ULL, 0xB175B98E518AE6D8ULL, 0x467081E2DD7C6AEAULL, 0x5A02E27314FD48F9ULL, 
            0xB4D787B2D49022FCULL, 0xA512032D64E400E7ULL, 0x7FE3DC9A4B193AD2ULL, 0x13BEF207E36F202BULL, 
            0x2D5919B8E46481ACULL, 0xAF0C730CC04245D7ULL, 0xE899D3B5588AE036ULL, 0xB9438F878CFF183FULL, 
            0x52F26B23D61898B4ULL, 0x68921AD518A2FAA4ULL, 0x80111A8F7DF156ADULL, 0xF60834F987094813ULL
        },
        {
            0xABDCE5CF13DF68D7ULL, 0xB8D8DBB6312043EBULL, 0xEE5A10E2FBF6BB61ULL, 0x2B7B56CC3692CF33ULL, 
            0x8262411B1E0FAC54ULL, 0x24D968B678B6F99AULL, 0x211C7630C49DA028ULL, 0x6BE1B42E49CDED88ULL, 
            0xC4E7DF30A423F9FAULL, 0x08DC2BF22AC22697ULL, 0x185AC812AC964152ULL, 0x13A1CD7C79BE4C09ULL, 
            0xDBBF1FEF38BC77EEULL, 0xF42AD25E0FC6216AULL, 0xDD947943ACF1D7C3ULL, 0x36D4C3297475FC78ULL, 
            0x697F0ED757009FBCULL, 0x2A7C5AA4B29750EDULL, 0xAD541A0DAB382C02ULL, 0xD15A33C83666E7D1ULL, 
            0x27FB42EBFC2A59CFULL, 0x054039F1878BF395ULL, 0x524BA525EA925080ULL, 0x14F3FBF8FB3D869DULL, 
            0xCB70EB62C9EFDA56ULL, 0x30A4C77F18C446F5ULL, 0x6F8BE9230A142D00ULL, 0x7E559816ABBC53C2ULL, 
            0xEFAC44CC920B5E02ULL, 0xB1C18B5BBCD969C6ULL, 0x748802F8AA823E78ULL, 0xD0BBDEB51DCA7EAEULL
        },
        {
            0xC4738A347E21ECF6ULL, 0x9C12EC3BE9B5C392ULL, 0xDF4FB7A9A540AE02ULL, 0x0205756BDA6D466BULL, 
            0xECFD1FD313562004ULL, 0x7E10E54E3739D7A0ULL, 0xE64EDFF2C4201364ULL, 0x234543A221C33D25ULL, 
            0x09C5A0BD8922591FULL, 0xC18177DCDAB142A1ULL, 0x287991631009F5BFULL, 0xE7D7E049C72C1759ULL, 
            0xFDF1257A53B2A1CEULL, 0x27D2308D9CAA941AULL, 0x9626A24750721978ULL, 0xE5EDD224CD26D560ULL, 
            0x34F6A7FF0B8094FCULL, 0x675CAA0B23BD0E84ULL, 0xED19959758F19E64ULL, 0x2D4AD857B88687AEULL, 
            0x09814D523683A59EULL, 0x62F651284E4CD400ULL, 0x77D4BAE448C249BFULL, 0x947B83F173C44EF2ULL, 
            0x30505E0ADA63885AULL, 0xA0277034ABD3E59FULL, 0xA60DAD8AE0EAE1F6ULL, 0xED2760EB5319B887ULL, 
            0x8311469BEAC4266FULL, 0x1A2F8F884DBD20D3ULL, 0xFBE30D1425E7EB86ULL, 0xD40F30867533A711ULL
        },
        {
            0xC341D4EA6EF5C9CCULL, 0x9749ECE206BDB0AFULL, 0x941EA0DA85A2EFBCULL, 0x97BFC7B5C1ABF81FULL, 
            0xE0AD8717AD72CB45ULL, 0x014545FA3205D07AULL, 0x598F24661F18FEE6ULL, 0x498A7E5EB9B9FFCBULL, 
            0xD70E79DB445A687AULL, 0x76F64F449CFEA125ULL, 0x07FF3CDD97392EE6ULL, 0x0D072B756FEE2011ULL, 
            0x807F7AC53D2728A2ULL, 0x0F50467ED62D8E55ULL, 0x98B403C91A922235ULL, 0x5ABF97051073114DULL, 
            0xBB082FD55E69B406ULL, 0x9E561C51501FDD45ULL, 0x2A20240CD363AD64ULL, 0x095CEFECC682C697ULL, 
            0x89242C092013DA74ULL, 0xE7DAFEA1520E3640ULL, 0x5ED3963F8429808BULL, 0x8662C872431D941BULL, 
            0x288DC6885972CD8EULL, 0xCADFF0C6E5B5400BULL, 0xA9E86FF2D01F8B78ULL, 0x21C255BBF93E9DACULL, 
            0x826D9E0FD3045867ULL, 0xD7E05A171F90575AULL, 0x8EF16D6EC0F27A8BULL, 0xB2C6CE1656DD9059ULL
        }
    },
    {
        {
            0x05BCB59B2DC09470ULL, 0xA916FDDFAA80602BULL, 0xF4C39812BFC8B6D3ULL, 0x2E20C2AE833F7649ULL, 
            0xE7B4EB736976A9DEULL, 0x6AB4CA8759738A51ULL, 0xF6AD77D49F0AC675ULL, 0x6594C36AE1A4CA3AULL, 
            0x2E8A9B62495B382DULL, 0x162CDD77B2EB7823ULL, 0x018F4D71CF6C37BEULL, 0x4EB784C24ABA9001ULL, 
            0x5245D4BAC0CF6DDAULL, 0x7BFCFBFB9262F344ULL, 0x5D1F18E336BA0EAAULL, 0xD611F7B7696FD92FULL, 
            0xAE06775EFB8A6A9EULL, 0x565A4B20996A03E7ULL, 0xF33D815BBFF7352CULL, 0xB3C30615AD17255BULL, 
            0xA83F437CF0BC7107ULL, 0xE5B4907AD924FEC3ULL, 0x64C8E323195AAE3DULL, 0x754678CEDEC6895AULL, 
            0xC4464AF9BFE286D6ULL, 0x4542EF3A3A948CB5ULL, 0xDB8EB2F579330C68ULL, 0xAECC6EB8C9AEA1BFULL, 
            0x8B72C1B3EC7198BBULL, 0x728BFBFA784CA52FULL, 0x61B706C52487725AULL, 0x8D9499F13D10AB64ULL
        },
        {
            0x9207BC711A96F3A5ULL, 0x656722C45B2BAC38ULL, 0x81A9556F79F99B3DULL, 0xB9423E0E44DE1A21ULL, 
            0x6558C989BFF25C2DULL, 0x95E778414BBF1B11ULL, 0xF2765A3E6C49AAECULL, 0xFA83D162A8E8ADDBULL, 
            0x3868F453A85988B6ULL, 0x9438B6055D224380ULL, 0x206264E20212635BULL, 0xA4A81AB6BA1DE400ULL, 
            0x081FF1C768B2C3DFULL, 0x23104DA65DD95B34ULL, 0xAC42488E665BCFD4ULL, 0x5324323789CCC725ULL, 
            0xD707F0F99AE1426FULL, 0x5F2BF5F6FB0E3EE3ULL, 0x3197938682884321ULL, 0xDE466D2FF68226BDULL, 
            0x658D382A6E0B21E3ULL, 0x47726AB282859A9BULL, 0xBE7765385ABD985BULL, 0xA84279D81AC423F4ULL, 
            0x09CEF418268865D6ULL, 0xED07B97AF4C84D46ULL, 0x7F2424A8F436E7C5ULL, 0xA042017933BFA2CEULL, 
            0x45DA50D1ADFC5BD9ULL, 0x3591420BC891D26EULL, 0x34DAC0BD02268F35ULL, 0xA5C09EF5D1A0C562ULL
        },
        {
            0xA6E50622ADB868F6ULL, 0xB568407D9F7875CEULL, 0x58874F04E0A37AE8ULL, 0xB8703CEDADD463C3ULL, 
            0x6CCD426B0D1C3DBBULL, 0xAD0E01C6F5B16C89ULL, 0x99F325432DBA7E87ULL, 0xBAABC1F62DF6CE3DULL, 
            0xAA4DC90BB7A1381CULL, 0xBA308A7065F5D3AEULL, 0x056076F0608A768DULL, 0x88DAE44C4BD5A989ULL, 
            0xEF70DBEC649EE023ULL, 0xD01D451B705E19C7ULL, 0xAF695D5353080610ULL, 0x4147B5CCF8FF394AULL, 
            0x52846058D546CF64ULL, 0x82A4C5315733C6C3ULL, 0x680E72EAD3EFD5B1ULL, 0x89B5B7B544890886ULL, 
            0xB349EB381A754B1DULL, 0x00A420CA46DF719EULL, 0x99F6087EDD78F375ULL, 0xC3E83D7AD1FDB6A9ULL, 
            0xF2DC3530FE910730ULL, 0x011633E4B89289ADULL, 0xBC3A813D09FB6036ULL, 0x2994F1BC684B689DULL, 
            0x1A9D744F7CEB918BULL, 0x772CAF946A88E6BFULL, 0x5F71CD76CEEBCA01ULL, 0xEED0C6C6D5966CD4ULL
        },
        {
            0x085800117F9158B0ULL, 0xD0719E6BFD953A3CULL, 0xE87CB93455D158FBULL, 0x91BA014F41AEF6E6ULL, 
            0xE7D552C9B4584460ULL, 0xDCB4D02DB2315CD5ULL, 0xDEFCCC300E8CEBF9ULL, 0x2CF1F70904E659F1ULL, 
            0x940BC09AAE0CB03BULL, 0x51FFD7416A7206ADULL, 0xB41B2ED40D8025CDULL, 0x12F6209A5621948EULL, 
            0xDA7CD00D3D84594BULL, 0xC6287D51BA019272ULL, 0x4FE3DDE5B41AF11DULL, 0xE85AE4F3ABDAAA1EULL, 
            0xE307206E9C25142AULL, 0x201E5E7C580D0852ULL, 0xD0B8D9426EF19BCAULL, 0xB4CAE863DE507C44ULL, 
            0xBD24D8BDFD23FCD3ULL, 0xF412E86A2151EAE9ULL, 0x4FC3AF24DB584E11ULL, 0x290C8D721CB7181FULL, 
            0x0100E52B07F585CEULL, 0xBBE9DD091BC51668ULL, 0x33B47AA69CE25E5AULL, 0x379E962A6E6CCC18ULL, 
            0x0D7298ED2F6E856EULL, 0x885AE7A00134C57AULL, 0xFB223B45BE894007ULL, 0x8E03B75581893AD2ULL
        },
        {
            0xD64787BD681F7CCFULL, 0x7ABCFC75126E554AULL, 0x708496A74AA1801BULL, 0xD8160384CE241302ULL, 
            0x54645DE13212499FULL, 0xF845FF4B136DC73CULL, 0x16845605653EC6A9ULL, 0x362F69EB88675446ULL, 
            0x1EC7D0917103CDD0ULL, 0x9A9C930283B6D571ULL, 0x6CF3DE3D8BF6CF89ULL, 0x53773DBC597C3863ULL, 
            0xA3F2BF10C13D985AULL, 0x5C942ECEEB217ACFULL, 0x78B0E2BCE9C7A147ULL, 0xE633C72638AA85DCULL, 
            0x490CB133A23F59AFULL, 0xBB978C590D2ABD5CULL, 0x99C19B9AEA8A9227ULL, 0x172B8D25E3BC8008ULL, 
            0x4F1C26C9D5CB88AAULL, 0x6E4D18E694DFC6A0ULL, 0x43BB62FC2009FC14ULL, 0xAAA37A4D2D53F0FEULL, 
            0xE66D8DD94D5DC08AULL, 0x81E6B23743037278ULL, 0xDB36F8B7EE80A623ULL, 0xAEF601B512EBE6F5ULL, 
            0x49AF476CD74696CFULL, 0x4B736AEF4D35E2BAULL, 0xEAA3A627FF7E97EFULL, 0x427FD2E4516B2213ULL
        },
        {
            0x00B77B4A9C13A68CULL, 0x6D305B2A7813C6C8ULL, 0x4A084B3054F802B2ULL, 0x25469F37AD105C26ULL, 
            0x49BBD6B781406E4EULL, 0xBF5A193A45BF6A5BULL, 0xF958000E99220093ULL, 0x6EC3BD63D381A1A8ULL, 
            0x547506C73D4BA390ULL, 0xD6FAE9B978FA53ACULL, 0x3E5AE4FBF2CE89F7ULL, 0xA997D95218F2E0F4ULL, 
            0xD69BC285DF98E9FCULL, 0x62F53803395BCE8FULL, 0x9A59ED74CB651DF8ULL, 0xA3290EFAFF8D8DE8ULL, 
            0x801ED99A16C196ECULL, 0xA076C8A7F75E2CDAULL, 0x85FD70DA6F613FCFULL, 0xBCA6CBB5B3ABCB65ULL, 
            0xD767D233F364A665ULL, 0xA25C50FC7685B6A0ULL, 0x297BE4A1BD7A7610ULL, 0xF52819A621280DABULL, 
            0x078868924E45B158ULL, 0xDBF2FD5B48005947ULL, 0x5CEF5F779BA948D7ULL, 0x0611FAD6B9582737ULL, 
            0xF4F04AC352FD50ECULL, 0xFCE9FBAB70891C4EULL, 0xB8473AB4DBE77BE3ULL, 0xDE93E9277B6550EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseDConstants = {
    0x3C695921A98127B4ULL,
    0x153395A37A1C2F40ULL,
    0xDDFA61226630D3B7ULL,
    0x3C695921A98127B4ULL,
    0x153395A37A1C2F40ULL,
    0xDDFA61226630D3B7ULL,
    0xCB64E1CF53AF74F8ULL,
    0x5F22DB724EF27F6FULL,
    0x56,
    0x53,
    0x7A,
    0xE0,
    0x65,
    0xD4,
    0x4F,
    0xDE
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseESalts = {
    {
        {
            0xAA62BDE40255D2BAULL, 0x3BDDA404D1CE5CAAULL, 0x8F0120B186C68239ULL, 0x6E75E76C67423BE0ULL, 
            0x2F0D9EE3CD227EA9ULL, 0x057A7FA3D498F023ULL, 0xD53A3905A41CF15DULL, 0x337F2EB79179E72FULL, 
            0x9665ABD334A5CEF1ULL, 0x99CC8A979E6FAFD3ULL, 0xAA7A70FC78310394ULL, 0x6812D90763324E87ULL, 
            0x0FEEB203B7E97405ULL, 0xD9F084C955C56202ULL, 0xC7F5E67C8A70BAD4ULL, 0xC658C753AAFBD1FBULL, 
            0x7E6AA5A5D387CCD3ULL, 0x9A382B99A9CBFFB6ULL, 0xE5C1128043AFE08CULL, 0x09F698C87134D15FULL, 
            0x22750AF0ED76D801ULL, 0xE90A9B5E59C6FFFFULL, 0xAD0D29E9A3FD60B5ULL, 0x8C1032260E5FCAC9ULL, 
            0xD0C46BC4B0292989ULL, 0x76AC4CFB279EF74CULL, 0xF0E10C242C625A02ULL, 0x54FF3C93397D2764ULL, 
            0x1FAEB77DE05F986BULL, 0x701EC037068DD7C7ULL, 0xB48D7D12F256B26DULL, 0xD38158E37BBA8D0FULL
        },
        {
            0x002686081F15B13CULL, 0x4326673E679D571CULL, 0x83FF277D42DE9C1CULL, 0x488B563B98E98B14ULL, 
            0x321461BA8ED9F03CULL, 0x7E79883E89B5C982ULL, 0x7A51F02EF784DFF8ULL, 0xCE4095783C5401BAULL, 
            0x066DA170627090DAULL, 0xE597388530CB6B77ULL, 0x4CE8EBD616781E6EULL, 0x08794AB9E9F28C9DULL, 
            0x279F163B96A6B350ULL, 0xD842E7F7078A08F3ULL, 0xC81F85830004E76AULL, 0x16AA51B9D4C0A530ULL, 
            0xE92D12ED27E27D98ULL, 0x8150F08F5605D2A4ULL, 0x47D83B8CD682BA53ULL, 0x743D386ED1EC34D0ULL, 
            0xCB40BC86DA0AFB62ULL, 0x7FFE634E77036993ULL, 0x663DA9ECB6CE0311ULL, 0xAE0C7FD897032680ULL, 
            0x2B21D0D450E79036ULL, 0xE16795BDC9B8D895ULL, 0x24F7B2A2CDF39712ULL, 0x502F922A61BED74EULL, 
            0xBED2B162F62FA580ULL, 0x218C8D70B257A268ULL, 0x37DA0D29EACF3DBEULL, 0x73C004921116DF0BULL
        },
        {
            0xF0CFA8FBD8369E10ULL, 0xAB9AA55457536589ULL, 0xD524388C035F8493ULL, 0xD86D5600748C907FULL, 
            0x88F751E2D7222CB6ULL, 0x1FD8A80C2C3EBA28ULL, 0xC04B2B22862E1938ULL, 0x258060518B4BDA13ULL, 
            0x0D36EF8C99A737A0ULL, 0x80953745AEACA089ULL, 0xE8F3E663C2564BDDULL, 0xCC90F75181315837ULL, 
            0x7EA106FF5AD0AF50ULL, 0x76D04710DD742100ULL, 0x9B42A725A93734C7ULL, 0xD81ABF09B2543F0EULL, 
            0x9FF160FBCA5A9230ULL, 0xC400605A9ACF52D0ULL, 0xC006370E74603943ULL, 0xEF797EF7D5727CBDULL, 
            0xD108F1F914874BE9ULL, 0x4601AEC8533CE223ULL, 0xF08381F416A59785ULL, 0xF0FC290F81C896BCULL, 
            0x758F24EB3DE8231CULL, 0xA403B17F4A3BAFAFULL, 0x083E07F1A917F437ULL, 0x3ACE2153FDD15546ULL, 
            0x103E987AC3B6AE10ULL, 0xC0748D9A6E60CD74ULL, 0xBBFD6B9F65F867B5ULL, 0x55BCFE8BD31DD4F8ULL
        },
        {
            0x50C973B6FC37ACEEULL, 0x872BEFDFE3AFA88EULL, 0x13BF4930CE86C6CDULL, 0x8E49CC715E3D939CULL, 
            0xED2AB3465E70497DULL, 0x8C85D0E3B92EE30AULL, 0x10FA2C8F20EEE578ULL, 0x652C0E43072F2C31ULL, 
            0x2EAE12AD782E36CDULL, 0xA08AABD02ED299E8ULL, 0xC65AE846F63EA4ADULL, 0xE7148845387F48CEULL, 
            0x81EB741D07EC12AEULL, 0x5E58F1CDACB66C23ULL, 0x3A2E48A49760DF3FULL, 0x0C00626AEBEC9B12ULL, 
            0x6FC81D1E229E544AULL, 0xD4050357C31A00F5ULL, 0xF1022DDE4922B141ULL, 0x1DC04C54FA6CDC0BULL, 
            0x1BF94BE853E4F091ULL, 0x9E082B8BAAC4AE5EULL, 0xCD6403BA16553F1CULL, 0x68F41390EC1B4019ULL, 
            0x5F4CD20FC8D84B0AULL, 0xFB633ED77243E632ULL, 0x4419FB831AB0D350ULL, 0xF404908B618BB107ULL, 
            0xEEF6700D384B8D76ULL, 0x48348DD647F086C4ULL, 0xF2F45B43B47ADDCFULL, 0x2B15484313E67B5AULL
        },
        {
            0x7D8D6B3549CC28C3ULL, 0xB26DCCE77EB481EDULL, 0x64C11AA8896537D3ULL, 0x0BC7EFB40E330619ULL, 
            0xCC24BD9AFC53F066ULL, 0x8BB3EBC5C16B1002ULL, 0x6920A7115F56387FULL, 0x2EF2CA3F6B789423ULL, 
            0x95DF4FF329AB91C9ULL, 0x063F95D37AA56890ULL, 0x5DA7C3BE84D2DD6CULL, 0x01AA8E6D97DE0062ULL, 
            0x53D2C8ABD511C96DULL, 0x2B28612F405B3C0EULL, 0xA2BCBB3304B1879DULL, 0x2F8441B76C06DEB5ULL, 
            0x948AEFDAAA8C39EAULL, 0xF2EE789C8EBFE0EAULL, 0x217EC7FDCC229CACULL, 0xDBD31310ABB8E0F9ULL, 
            0x4AD70D84741533A7ULL, 0x99EC8FE4C6E758B0ULL, 0x31A5957BF2E678A4ULL, 0xA7D32BB3A47C028BULL, 
            0xC08AC29D625B8874ULL, 0xA42FED33CA17A1A8ULL, 0xA3DC697519BFF661ULL, 0x684700D12FB59BDFULL, 
            0x751C5B60AAC67B2BULL, 0x1EAB05E1FDEC4159ULL, 0xB6D52A4D976BBD16ULL, 0xD2384EBACB9C7762ULL
        },
        {
            0xB4037299EA3E4976ULL, 0x785A74522A32ADA7ULL, 0xC8E460D181AB0699ULL, 0xC7A1454C064CEB5CULL, 
            0x838AF6A1E1715588ULL, 0xD2A6F9BD39C45216ULL, 0x82DBB6DC0878B222ULL, 0xFEA457E322BEFDC0ULL, 
            0xA34AF010286906FBULL, 0x0EE06F6DBA63672EULL, 0x80D7AE330706CEE2ULL, 0x7019E44E7EC3489AULL, 
            0x3E669A7583792B29ULL, 0xA865BF5C70D865F2ULL, 0xC0BFE74EE67B7E34ULL, 0x798288933B09C46DULL, 
            0xFCBE01B17F5C8D08ULL, 0xB085A3C06A5D23BAULL, 0xF9D8094F7BE786DBULL, 0x185656239A48E0AAULL, 
            0x1450BA7723FF02D6ULL, 0xA306DEC5D79C0562ULL, 0x3CE2AFB5734A0948ULL, 0x18AB38D3193F2E94ULL, 
            0xFC89F19D018A5742ULL, 0x1504AB36B58F66FFULL, 0x970190F0A1AD657DULL, 0xB07F2C44276AFF6FULL, 
            0x73DA96C80D8FE8AAULL, 0xB677B811DB4BDB98ULL, 0xD9D250D710300ACFULL, 0x47108B2E39802A55ULL
        }
    },
    {
        {
            0x000A994D36D2060AULL, 0xDE49835D6A45009DULL, 0xEB298A233FD714A5ULL, 0x17FDEE43E6079FA2ULL, 
            0xC4E1713BF799755DULL, 0xC7C31B010A3D9585ULL, 0xEF00ED1DF4D81AE7ULL, 0x282A62101D9435E0ULL, 
            0x426CD25FCB81383BULL, 0x12A120E59B977DF5ULL, 0x6C6D5EC81ACA3727ULL, 0xFD2BA166BB2D8999ULL, 
            0xFD181159E1D6B28AULL, 0x768F3F0D5B619DB4ULL, 0xBC40CB034E565546ULL, 0x55DF4C1399E69B41ULL, 
            0xAF75162820EC2F5BULL, 0xFA9A8D624AB61916ULL, 0xFF5272E0D2C3A93FULL, 0xB2E4C424DC53D4CEULL, 
            0x48D7264BE6D82361ULL, 0xC266A55298117A42ULL, 0x0163FE58399F99E8ULL, 0x83A4220B7B50A0F9ULL, 
            0x0B348D8834FA2377ULL, 0xDCD2CABFD4CB7722ULL, 0x38929BCBDA0BEEDBULL, 0xE50AFB5EBEADCBC4ULL, 
            0xA6B1764D48086500ULL, 0xDD715803F7065C3AULL, 0xC574C9743D004572ULL, 0x95B759E8F0970DFCULL
        },
        {
            0xEDEDFE0EF98157D2ULL, 0xB0133018C24306CBULL, 0x15237F5576C11D14ULL, 0xD8F8589F9195405FULL, 
            0x4414D0C4D2036142ULL, 0x468A5F4311E98079ULL, 0x0F0E6EC0B2B3E4F2ULL, 0x2B2B4555F3C6E907ULL, 
            0x81827D2564E7B986ULL, 0xCCACD2FC2EA3B5C8ULL, 0x0DD615837BE55529ULL, 0x9EE951B62734E232ULL, 
            0x7F84C200488FEF1AULL, 0x504B1EA88952B9D6ULL, 0x64B1F5870C30C9BBULL, 0x953E65CD31B7BF83ULL, 
            0xBE4A8177925942D6ULL, 0x37311567BD819961ULL, 0xF54562476C13B4DCULL, 0x5B1D588E3F4E62B9ULL, 
            0xE964FD4E2C6E1613ULL, 0xE2FF1138C3777751ULL, 0x1F8D1B0D3D86BC23ULL, 0xC9485D96577AA52CULL, 
            0xA70E07F7105172CAULL, 0x2F7C6A73B36BC114ULL, 0xF11277D7E5F7FFFAULL, 0x2848AA8FBA7E13B1ULL, 
            0x70F16CD61BCB674DULL, 0x0250903DFBBA9639ULL, 0xC738CCCC0D1712D4ULL, 0xEC0FBE100A458725ULL
        },
        {
            0x7AC02EE1E770FB6FULL, 0x015F04D7A9C79428ULL, 0x4A463F1EDBC37685ULL, 0x694170DA686946ECULL, 
            0x7A850198725B8DCAULL, 0x1B821666E54A256FULL, 0x3B5BCFBFE40027B6ULL, 0x696A08BA1F5D515AULL, 
            0xBBC2AA72413502E5ULL, 0xD80A88A2BF1A57D6ULL, 0x5066DCDA57A12F83ULL, 0x29E802595F1C32ECULL, 
            0x5C0215B29E05FFDEULL, 0x78FA8384FE898E82ULL, 0xCD1B4A5589835747ULL, 0x166542A26E00AF45ULL, 
            0xC275A86C8A98FF37ULL, 0x71AD1A588F672AACULL, 0xF2E29AE1516DF875ULL, 0xB63CF9FB39F50FAFULL, 
            0x749B7F0BA05618A2ULL, 0x88214676E0459E65ULL, 0x0A3B7DD6D79EE7A0ULL, 0xCCD0D0FD2DEED998ULL, 
            0x757BB11A14645514ULL, 0xCC13CAA8441B9019ULL, 0x322AF2DF055D3CEAULL, 0x10446A13CD7D5BFEULL, 
            0x892FF58123C1452CULL, 0x63FF499811152A36ULL, 0xF46FAC155F801C0FULL, 0x5E91601D33A00377ULL
        },
        {
            0x883DBA3526576F7CULL, 0x97DAF76338750130ULL, 0x219DB899B940D063ULL, 0x9E316373EF778B23ULL, 
            0x4B2119F9BEB7F71DULL, 0xB36DF79F219C020CULL, 0x2F7F6735A678E572ULL, 0xFBB11C0A302BE0F4ULL, 
            0x8874031E0CB989C4ULL, 0x44C36A4D436EBBD1ULL, 0xAB310D938C29A17CULL, 0x6818A666E8822AC0ULL, 
            0xBAF4A1594657693CULL, 0x34F0B411D53CE0EAULL, 0x5B01813FA9AE0DD3ULL, 0x87BBCBDC4C3550D9ULL, 
            0xADF4F25BBA8CDD87ULL, 0xF3296E23C7DCFC6DULL, 0xD79DB745ECA5C18EULL, 0x3A5A5D392E294067ULL, 
            0xAFF6455A2E1FC991ULL, 0x28B4EE6AF045187FULL, 0x286FA5EAE6E9EBB1ULL, 0x44819DA83BEAB1ABULL, 
            0xC99FA9544B01590BULL, 0x1870B27E48C94AD6ULL, 0xFB390DA437E789CBULL, 0xC6D3B7A2FD2AB797ULL, 
            0xBF605B8AFADF665EULL, 0x1BA56E53E105F7B9ULL, 0x60B1FB0979BE8D10ULL, 0x272549E2812E6271ULL
        },
        {
            0x39C89D696B352886ULL, 0x43334B927C6E9FA3ULL, 0x0159EE72F7852106ULL, 0x9F481E4F505588EBULL, 
            0x18DCB7141FEA0F9AULL, 0x2A12151DF7F299D4ULL, 0xE92191ABEAC090F5ULL, 0xF1F2333494067C56ULL, 
            0xA7124DBEEB4D5134ULL, 0x7ED4FCBB4CE3B416ULL, 0x06221BCC328884A7ULL, 0xD27C2D5408B2AA94ULL, 
            0x84BB9FC0D97142F5ULL, 0xC4489E735B49C973ULL, 0x1768415A860AA215ULL, 0x03F7830174A6C7CCULL, 
            0x043EDD3F65515BE2ULL, 0x2DB54FA8C204317AULL, 0xBDDEEFED637D5D31ULL, 0xF2DD2F465BBCD0CBULL, 
            0x45A2F4F691725C39ULL, 0x02F42999ED569760ULL, 0x5D5C4EB4A45EE6BFULL, 0xE63B87002F764F7AULL, 
            0xC2F9A6E7EB54EC7FULL, 0xB2DDA2DFF19C5FA6ULL, 0x554C68CAC2AA3AABULL, 0x2A87ED6A38B6BF6CULL, 
            0x4F37F9C5ED056F25ULL, 0x5EE3685090F76BACULL, 0x3A6EA733AE00F191ULL, 0x840BBAE885F6C259ULL
        },
        {
            0x8A5CEEF6DA22DC71ULL, 0x1E74F372155FFB52ULL, 0x8D241876AF8120ACULL, 0x201F76C758316858ULL, 
            0x214237C25DD8AAD3ULL, 0xA35B714CB76F03FDULL, 0x507A1EBA8599C51DULL, 0xA97F8DFD9DC49FB4ULL, 
            0x0CAEB70F777EB1F0ULL, 0x26344D3C4B40092BULL, 0x224EC379BA6C86F6ULL, 0xE6ED2921598E4CF8ULL, 
            0xA17C337FF3403F8FULL, 0xE79A873FC7B8312FULL, 0x7E121DBEA3A7F21FULL, 0x6DAE43E282B80EB5ULL, 
            0x6860765587852B54ULL, 0x9FE3D6E29D9044F6ULL, 0xD8EB5A96D9512A1AULL, 0xA8EA77EF7E555C1DULL, 
            0xCD1C77D9841E97CCULL, 0xE226FC4351827604ULL, 0x212AE879444BBC16ULL, 0x822025909660D46AULL, 
            0x2BD750B8CAC3280CULL, 0xD514A630DFC0AF41ULL, 0x7851EE903D5FA47CULL, 0x9F90468887F5CA91ULL, 
            0x2DEC37E1EC359005ULL, 0x9656D707B057D45CULL, 0xB3A730789EAE7852ULL, 0x86CB72689E8AA7A3ULL
        }
    },
    {
        {
            0xB5FD3D5EBBCE2145ULL, 0x33D54DC8D1BD2F53ULL, 0x006C46995777A7BDULL, 0x5CB076B650ED8B71ULL, 
            0x1F66B28C480BDFEAULL, 0xF4E1B31911C3A202ULL, 0x02B7343E40B62D56ULL, 0xB94E7BB97464CE06ULL, 
            0x3BB60FCC11978D53ULL, 0xB03397E14DE6A044ULL, 0x2BC7CC0E4E87A098ULL, 0xCF5E7B1D2E503B9EULL, 
            0xB107D60F0B282F26ULL, 0x193BB038771679B3ULL, 0xD1BD760343B4A08BULL, 0x7375261E87B324EBULL, 
            0x6651D2EB905E9563ULL, 0x321AF300EDBF8739ULL, 0x5D1BC3FEF419313DULL, 0xA9FCDECDAC615E27ULL, 
            0xB8A7AD0B4A263882ULL, 0x61EA53430751F727ULL, 0xFEAC659FEDC6A8B0ULL, 0xCBFB43A647AA3AAFULL, 
            0x0C39EC51315B813CULL, 0x7E4CEB32BC6AFE68ULL, 0x687394FEB09F1B65ULL, 0x3BA8373203042F91ULL, 
            0xB83A99D400320EECULL, 0x7F4CEFBE32F321ADULL, 0xA27E0331D949627EULL, 0xDD90CBC96D765A68ULL
        },
        {
            0x16BB8B37B827906EULL, 0x3739CA0F3400A309ULL, 0x9A36BEA5E4DB1A31ULL, 0x5E9D2FE5C6E2C308ULL, 
            0x4E32571A6BB43B58ULL, 0x08E57CD4C935736AULL, 0x54D6A5BB8A00C089ULL, 0x7D39F6BD7F70456FULL, 
            0xE0538F57EC087F3EULL, 0x2A7D929466C0EDADULL, 0xA6CC5E31E4495552ULL, 0xBA3DFB0CD3023085ULL, 
            0xE8E8DEF7475D790FULL, 0xC5C78EDE6EC5BD08ULL, 0xE9E7BD620B7C9BDEULL, 0x9E8839FF54CAC5B8ULL, 
            0xBFA2BB77BECB5A85ULL, 0x2F28F6DC2AC0C2BAULL, 0xF24F7392016C8881ULL, 0x380F34EB703C98BEULL, 
            0xD7631C1F1DC6AE62ULL, 0xAC18755DD0C2AEB9ULL, 0x45A3BA477012546FULL, 0xD7DAFB37DE4D3AB7ULL, 
            0xB7A455A1FE2AC586ULL, 0x091DDA308E8135DCULL, 0x8EAC8A0100E8EE22ULL, 0x117E09B2924A5FF2ULL, 
            0xD5660643DE402571ULL, 0x1EE44A116A823A66ULL, 0x969022667FDB1731ULL, 0xB65A2EF228A2A698ULL
        },
        {
            0x3E402F12A400B9A0ULL, 0x8AE128C7BB0FD3CEULL, 0x892F888E1D67624DULL, 0xFFD7403796109B81ULL, 
            0xA5FE4111F862E421ULL, 0x8760997D7B9BBA11ULL, 0xEAD9791AF3D8A692ULL, 0x427D31A6D991D920ULL, 
            0xFBD6B89E52F9A57EULL, 0x825759F9A546FDD6ULL, 0xB58D4DC1F7DF1AF4ULL, 0xAB9819C964E5ACA0ULL, 
            0x2D68B1D2105838E7ULL, 0x0AF81103C14C3338ULL, 0xE72C6B75584B26E2ULL, 0xAF9065B2449D3987ULL, 
            0x8D4877D4A9BA1910ULL, 0xBE7D8677F41F4B2BULL, 0x49B05C7C7C22614DULL, 0x9EAEEB2E4F709D62ULL, 
            0x0FBFCCA949644394ULL, 0x0F2D197010F221D9ULL, 0x3963F61A0799A843ULL, 0x8F9480C51E76467BULL, 
            0xAC5A25595A357492ULL, 0x8EA3DE9E3A92A653ULL, 0x2A77E6C022C93631ULL, 0xEF92D5FAF62861B1ULL, 
            0xF78BFABB1A7D1830ULL, 0xC1BA7DC3B9472C49ULL, 0x12522DAA79B7A4CAULL, 0x4D90384F0DD93281ULL
        },
        {
            0xAE6E6571AB9DA40DULL, 0xA4F9BAD52451F7A7ULL, 0x1FB6B368F1DA2005ULL, 0x6A3A8746380A4DFCULL, 
            0xCBCD1AEDBEEAC8A3ULL, 0x7AF662A4EB63F74AULL, 0x9393A8CA61D79A70ULL, 0xB105838E67F0FAA2ULL, 
            0x341BBE30A4CA6091ULL, 0xC7F1460CF7D775E9ULL, 0x1D3F2F187206F5F8ULL, 0x43153F0E2267D51DULL, 
            0x01C709B0A21307ECULL, 0x29655AAF63ED5D05ULL, 0x99FD9B63E043F25AULL, 0x5CB0598A279038B8ULL, 
            0xDF24ED3AA182665EULL, 0xD72DD71FD9AA0C3BULL, 0x3F06D4FB57760621ULL, 0xAE51A6FF246CECACULL, 
            0x163EDF4E038309ABULL, 0xCCBAEDF8BC0E9B5EULL, 0x705D940E8722C000ULL, 0xFBA145061AD3C9AAULL, 
            0x721F4EA3E489D411ULL, 0xC12B640EAE619194ULL, 0xD6C915845EE3170CULL, 0xBF7F2CE94524D427ULL, 
            0x78FE1EF2BF057A00ULL, 0x47744A590041EE69ULL, 0x30BF608ECA06E4A3ULL, 0x64585925F0080414ULL
        },
        {
            0xCA8AD535C9C3B44DULL, 0xEF52C8D1FBF5E2DCULL, 0x45D2BA581A32AAEAULL, 0x3B5366FA1C81319FULL, 
            0xC2102F4F83557EE0ULL, 0x299ED924ABAB91A8ULL, 0x0BDB5D98F17D2664ULL, 0x66AD4E071FF03DDAULL, 
            0x3D0D708FF79607C2ULL, 0xA34D7D84B5EE1905ULL, 0x49D4CAE2D4BF4B1DULL, 0x15785D6F06E6099BULL, 
            0xA0684871B0CFDBD6ULL, 0x80EFD8EE4C692FCBULL, 0xF0FAC8D39FEB62FAULL, 0x5E5D39186C1E8663ULL, 
            0x81AB68108E481310ULL, 0x97D06285F5E715D8ULL, 0x4FC8B62014715B10ULL, 0xCC8683D48622A710ULL, 
            0xAFC6A7AA121741B8ULL, 0x4969BCCC30B22CE0ULL, 0xECEE1B4EED7408BAULL, 0x48FA60D2B2C0BB8AULL, 
            0xF24260CEB8E117DDULL, 0xDB691484B9E73A26ULL, 0xD1BD0794CA931571ULL, 0x65E484A9D6562325ULL, 
            0x05F30EA97D07037CULL, 0x5E0D7591AD8A67C4ULL, 0x5062852EC68AA4B2ULL, 0x647D06AC33C63848ULL
        },
        {
            0xB1E21B4AEF2D3DE9ULL, 0x398698DD9992E390ULL, 0xF0BEBD823D750EB2ULL, 0xEE12121ACEC1D065ULL, 
            0x654C6056126D17DBULL, 0x4892538C226EEBD5ULL, 0x9E49D6ECC0CC1FA6ULL, 0x367A17CE987CF155ULL, 
            0xABD0AE723C29C9FDULL, 0xF799F38263C1FAB3ULL, 0x8C00DF3EA597945AULL, 0x146D2D1334A5AE90ULL, 
            0x3F980E58480C6297ULL, 0x758FF12EBA0E69A5ULL, 0x55783B4E655E5B44ULL, 0x09F62D0DE02E12CCULL, 
            0x28E88FD366D4384AULL, 0x6CD90B8942BA2A14ULL, 0x34FA87FA37B984A8ULL, 0xD367E9575EBE445FULL, 
            0x2E293FF93DF14903ULL, 0xF4CD0BCB330CAB61ULL, 0x1F0E95FC08D6BE97ULL, 0x75492A8AFE8A8582ULL, 
            0xF6A0A91F314132F2ULL, 0xB3F67B336C492EC7ULL, 0x0626A8BAB1B99C29ULL, 0xBB009F0EA5FEBD14ULL, 
            0x6AEC05572E4212ECULL, 0x57D941584DFCC9EEULL, 0xD9ECF8BC5471D598ULL, 0xE5F6E79CD65E9878ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseEConstants = {
    0xA44CB9CEEEE35CC8ULL,
    0x2396B9C10FCB43E0ULL,
    0x92C1B38E8E99CC9EULL,
    0xA44CB9CEEEE35CC8ULL,
    0x2396B9C10FCB43E0ULL,
    0x92C1B38E8E99CC9EULL,
    0x61163EF7FD510EF6ULL,
    0x3BD8532FB73AA343ULL,
    0x7D,
    0x57,
    0xF9,
    0x95,
    0x44,
    0x79,
    0xAA,
    0xD6
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseFSalts = {
    {
        {
            0x0945AA979B9EA042ULL, 0x33B41269199EB841ULL, 0xF231C9F7FA80ECF8ULL, 0x48B4C5C30840A845ULL, 
            0x13F11EADAE84FE22ULL, 0xEFF9802AB038E80EULL, 0x6A3AFFED75D31A07ULL, 0x407AFD0E6F9837C7ULL, 
            0xED3CB5250A663507ULL, 0x372CCF7C3A27F3ABULL, 0x66B9DEF8E589B2D9ULL, 0x2FA513B386D737C1ULL, 
            0x960C4DBEF336E731ULL, 0xD3919A1C2BD97682ULL, 0xE5896FB6D3E706FAULL, 0xEA4FB7E311E5F2F1ULL, 
            0xA996FCC615DBD0A4ULL, 0xEDA998EBA6A9CACDULL, 0x424B2E3C16EED900ULL, 0x3257C2D889C44C64ULL, 
            0x50ECE7B6DFA03EBDULL, 0x29CA41121B234F21ULL, 0x58EF3547EE8CDB53ULL, 0xDC2FB47E545E98BBULL, 
            0x5D4F4052DD581AAAULL, 0xD0627955C22C0215ULL, 0x2324005EB5BA3F1EULL, 0x57CC7C94F1945676ULL, 
            0x99A15DD3D94FCADFULL, 0xCE6CF67FC8F6F3BAULL, 0x0227DAA791A683A1ULL, 0xF826F20C07BC46CFULL
        },
        {
            0x8A4F0102D94D0314ULL, 0xDFAB19B5F53FBD8EULL, 0x71A5107A03046585ULL, 0x25A9621261722D46ULL, 
            0xCE1269EF58761252ULL, 0xE4B75FFC219EDC72ULL, 0xC74639D09F36D240ULL, 0x561127DC10521272ULL, 
            0xCDA95E506ADDF89CULL, 0x110DAA4194E1D0A0ULL, 0x625960B34E33AC46ULL, 0x10F8D7C888D508CBULL, 
            0xEC3A5D19CC4669FAULL, 0xA9FACC5F8C0FC810ULL, 0x22390E61348BDFD8ULL, 0xA033D95307E45041ULL, 
            0x2FDE39A47FCD4A07ULL, 0xD7E38956F5C30C97ULL, 0x90D1530E4767C011ULL, 0xF4F71B888AE20CBFULL, 
            0x0F7F524610342CCCULL, 0x94B98343F1969010ULL, 0x1E32126B0330788FULL, 0x38C48173EB985413ULL, 
            0x6E6BD60AC04C17C1ULL, 0x2F186C9C6E3A8A3FULL, 0xF34F04447E57C620ULL, 0xD362419BF7EF3E9BULL, 
            0xBBFD359FFB6C19F9ULL, 0x0EB1590485AF8729ULL, 0xDA78087F6E4DE32AULL, 0x4C0E3DFCB167EEE0ULL
        },
        {
            0xE086675332284470ULL, 0x8DEB3AB9A2FC0686ULL, 0xC97EB6EB134880D5ULL, 0xB7B56D4AAAFAE530ULL, 
            0xCA9DDD1C1B054F75ULL, 0xB8788B8979D16FE1ULL, 0x900A50D3CE7B5E89ULL, 0x2B63DCD98225667BULL, 
            0x44A25669E7BE23E8ULL, 0xFFAE27587E95478FULL, 0xF43D94C6957225F7ULL, 0xC8D0B39FC2E675E3ULL, 
            0x30A1A394D51507DAULL, 0xF7BCAE4FAD6F250DULL, 0x27A87E7CF0375C41ULL, 0xD76120886C5F7452ULL, 
            0x6C39972256BD4C71ULL, 0x78D575149A2D5744ULL, 0x97E6147D9CDEAA1FULL, 0x51DC4D2210C45E62ULL, 
            0x3757BA77E63FD00DULL, 0xC466E72F31EFF12BULL, 0xBF9A0E86BDBC8A8AULL, 0xDABC4EEAEAB3B9E4ULL, 
            0x15E7340FCD3CB8E8ULL, 0xF53D5EC32CD2B15AULL, 0xE1591A85A4567FF5ULL, 0x1CBA5FD680EFDA9BULL, 
            0x4F865A00B775E9ECULL, 0x6D0EACB9F3D66B86ULL, 0x85F3DCB77CCF67E0ULL, 0xCDC7DF4E09B34593ULL
        },
        {
            0xFD96DFBE5A42806BULL, 0xF45CBE2178A26D76ULL, 0xCEA2A6136923A09FULL, 0xB38F95042C3D84D4ULL, 
            0x8A8DB6E6F95B5BFEULL, 0x28DDB503A64AB3D9ULL, 0x3442F75BE8263303ULL, 0x459A89F80F170DCAULL, 
            0x322AD3A435485D71ULL, 0x938A9FBD26A3C742ULL, 0xA2316D0C08D90B68ULL, 0x0913EF3BB00DB6BEULL, 
            0x30195B06DFFFB5E0ULL, 0x0A893DD836D05D84ULL, 0x279211E40DF47DDFULL, 0x20D5825DC30D0D3EULL, 
            0x426BC53C82109995ULL, 0x5A83D8D01698D515ULL, 0x030A8E908DE83FE2ULL, 0x1840257F812A920DULL, 
            0x14BB7C597E3D2461ULL, 0xDE55CEC18B603A2CULL, 0x6D669440788BD37CULL, 0xCBB7900F107DC05DULL, 
            0x03EC3E9FC81F823DULL, 0xA604F41F5DED5358ULL, 0x59FACF4457DE4B2DULL, 0xA95FCEC0AE91D9CBULL, 
            0x20E69E49830B441DULL, 0x4CF65E3649E9C204ULL, 0x295491BDDB86E7D1ULL, 0x6F2A741EFB8B7BF5ULL
        },
        {
            0x8BB934351BA49C46ULL, 0x66234459D9B1B9DAULL, 0x4FE39C6594C4CD79ULL, 0x840BCC9A382ADB8DULL, 
            0x9B25EABFED0AEACCULL, 0x253B92AA818D3EE3ULL, 0x3989EE67924BD50BULL, 0xB72727B9A5F8FC12ULL, 
            0x75E590F4EF922C42ULL, 0xA1EA6DD4C35BC89EULL, 0xD47A4A86EB101E81ULL, 0xA89020544FCC1643ULL, 
            0x92738547317AC6EBULL, 0xA1332315D0988D9DULL, 0x1AF03222F208712BULL, 0xE7C71A114DD2453CULL, 
            0x11DBDA0F2DD477DCULL, 0xFE8342278F1E4F80ULL, 0xF3071900963BFFE4ULL, 0x800FED081F296E34ULL, 
            0x15F76AED6DD4DF4FULL, 0x45910A1BFDDCD274ULL, 0xB154DDB26723D0E6ULL, 0xE4C8EED709A54DEEULL, 
            0xF13F3BF3566618F6ULL, 0xE994DD4CA86C5421ULL, 0x0DB41CAED735C752ULL, 0x2499914AD577D931ULL, 
            0x462D36D022415AD0ULL, 0xB829DEE55E5D8057ULL, 0xF0116E1404EA1433ULL, 0xB384D2862A88F573ULL
        },
        {
            0xA28FB789EAD5ADDDULL, 0x3037A03833F7284AULL, 0x2F740E6602B9E8B9ULL, 0xA1F4C9EE1F416698ULL, 
            0xAE93A6CC08725589ULL, 0x036A30BF70A7FECDULL, 0x4927F553C18533F5ULL, 0x99AA9AEBCF9FA3B0ULL, 
            0xD838BCDD9E73179BULL, 0x59979DFD510BBEE5ULL, 0xF3EE465A29F50BF3ULL, 0x20D4B7FB5F22CEE5ULL, 
            0x6ABE0444DAE34A99ULL, 0xFE7F68F390C45576ULL, 0xCA991F4D4342A791ULL, 0x09D3B0ED6F2DE922ULL, 
            0x4AC8D33610A2EE13ULL, 0xBB5A8B66F7E17587ULL, 0x3950E3ED695BEED7ULL, 0x0DDBE11794F96AAFULL, 
            0xA992C7ECE3CD51D5ULL, 0x096A52CB349671C4ULL, 0x942A069D3A7D84DEULL, 0x04C296CA98A2E31DULL, 
            0xAE681AC487358871ULL, 0xB69A2A650FF4366CULL, 0xADB3A3475501EFF8ULL, 0x0E323F5B75ED3F49ULL, 
            0x8CC1E4A1A93753E5ULL, 0xC5516DB907F71D07ULL, 0xB62F6E8C8A71D76FULL, 0xFD410CF66F64A5F6ULL
        }
    },
    {
        {
            0x67F0EB14FBBF95C7ULL, 0xA00D3E0C6D437DE7ULL, 0x6ECA746CFA3EEFC9ULL, 0x249B6F08A174CEE3ULL, 
            0xA262CBE2A1C1FAEBULL, 0xDD9CABC8F75B319AULL, 0xC15B801286A27224ULL, 0xF16523D2848C8233ULL, 
            0x5CC69D3F60126E07ULL, 0x476D51C60D1864F9ULL, 0x2BE4DB6FD8448FC8ULL, 0xE8B426DF04CE1AAAULL, 
            0xDFAB62A5CA234F37ULL, 0xC7A0748F25116917ULL, 0x2C2785846A1E1C82ULL, 0x30E1294A05AEAEB7ULL, 
            0x67FAA2565A279549ULL, 0xD5D3981045462B21ULL, 0xCEC01834EC3619E6ULL, 0xDE35333B9CCFA2D7ULL, 
            0x0C2523B98A269551ULL, 0x850023DA58562157ULL, 0xDCC98E9F335FFF16ULL, 0x5B8D4300724B77CFULL, 
            0x553AEE05821AFC0DULL, 0xA9900A0646DF4E69ULL, 0xA5A9E1290A1236E1ULL, 0xAFC4894DFFB9B0BBULL, 
            0x13C9F738A5CED859ULL, 0x5A9C6F7315EA399AULL, 0xA93DBCC4D0C197CBULL, 0x427EB5B7B9309211ULL
        },
        {
            0x5E06C00C77225532ULL, 0x74BCD6075EBF482CULL, 0x6AFCDF9D68F9719CULL, 0x39327477935056C1ULL, 
            0x543348A49D95942FULL, 0x2C4B36629CD781CCULL, 0x5BFC8140CB4433BFULL, 0x428B5B430A0DCE12ULL, 
            0xA6F0E8C56A2BB4F9ULL, 0xB7CB13E50E13A01EULL, 0xAF0E0933E109387DULL, 0x42B7C295E4CA37CEULL, 
            0x992B902FD9887C5DULL, 0x536DB08C13144770ULL, 0xD76D8CA3796BDC9CULL, 0xFD21A939FA0C3711ULL, 
            0x362DC35381BCF61FULL, 0x09BA111119F5DA3FULL, 0x255402E22ED30536ULL, 0x48EB03056B9EEB83ULL, 
            0x2E97869EAC5E9D24ULL, 0xD74467E5BF132E8EULL, 0x5C9C54C743D81628ULL, 0x37FC1FA305961C5EULL, 
            0x26EA3FA17EAE655EULL, 0xA6DC6D922145F110ULL, 0x027ABE239A6EFD4AULL, 0x926316A02CD5CCD3ULL, 
            0x7F80D2D8322D9FA3ULL, 0x058E49766C2834F4ULL, 0x437CB38ED722C3D2ULL, 0x0A6143ADC65FCEAAULL
        },
        {
            0xED451C6949D2F4E6ULL, 0x2096D955D7AB66DDULL, 0x7A15D070F3EC86E4ULL, 0x369038C29DFD3790ULL, 
            0x113A8285EF78CAC2ULL, 0xE334F98565FA6EC2ULL, 0xEC46A87767AD972CULL, 0x6D30F1ADFCF32BD4ULL, 
            0x64860E099807739CULL, 0x0AAF16ED94342862ULL, 0x82D657A30D3F556AULL, 0x664908432F035F8EULL, 
            0x00F9ED4782ECBD38ULL, 0xA8CA22A701F90A47ULL, 0xF26BB41C22CAA5CFULL, 0x10E3AEBD1075BF70ULL, 
            0x0AE3FE929E65092EULL, 0xF5C29874223C2AA5ULL, 0x6D666AB007183496ULL, 0xE6BF888639692304ULL, 
            0x5D93C7AE4DD436A4ULL, 0x552CD187E666473DULL, 0x3E298EF4E592DA5BULL, 0xC4FFA3BDFCF93E17ULL, 
            0x8FEAC3FA947FA740ULL, 0xE4343CA776775D7DULL, 0xC5DD292E7FC0F24CULL, 0xF9FE9AF2DA147195ULL, 
            0xF4D83CB42A64E2FAULL, 0xEA47B395649D5A34ULL, 0xBDA33FE3CBCB671FULL, 0xDE351468D163E9A1ULL
        },
        {
            0xFA6019B6BA417915ULL, 0x11A1D75B21D00C55ULL, 0x30E157CD886202E0ULL, 0x64994E4562AE31ADULL, 
            0x445285AE537F619FULL, 0xA4F62AB037C7968CULL, 0xE523ABADC1BAE935ULL, 0x7BF0919ED5A7B0E7ULL, 
            0x4B1D553E4C256FFFULL, 0x4D38EB98B1ABCFF0ULL, 0x32C22A8C626F2FF2ULL, 0x7D47994F5886E2FFULL, 
            0x4C2334CC912E9C84ULL, 0x9B8A9638B7C598E9ULL, 0x00C5C789170F89D9ULL, 0x956D04E552C0B2E7ULL, 
            0x9E946F50754D37D1ULL, 0x53723B177F13B801ULL, 0x16BB9D71B1C95B64ULL, 0x8DEDAB81831CCBD0ULL, 
            0x8CF2C872AA96F729ULL, 0x82D8584E4C405686ULL, 0xA1C3FA0107731817ULL, 0x4E5BC18F37B43E72ULL, 
            0xCCE98C89425FF624ULL, 0x6BB55A6B69AFB95FULL, 0xAB22CEEF3D54E6EEULL, 0x50E18C813A3CCFA1ULL, 
            0xCFA4FA448F189F13ULL, 0x8B480F5E842BE76DULL, 0x5F5A3FB218CC2901ULL, 0x62FE78D80FA5A511ULL
        },
        {
            0x1C8BBFD07C7C3E6BULL, 0x604DF46FDD99A1CBULL, 0xD89F65E8C8F0B8CCULL, 0x59DDC08AC23D7034ULL, 
            0xBF2158F296D38219ULL, 0xF9CC254EBE21071CULL, 0x03B68B0699942785ULL, 0xFE81F581435B1A74ULL, 
            0x96893D5E43E5E407ULL, 0xD3A836F2943DC5CEULL, 0xF05548E64C995EEDULL, 0x7624125CE88AA18EULL, 
            0x3D23DDA4E029A1F5ULL, 0x101BEEC1908DF8FCULL, 0x33FDB9235FE93FD0ULL, 0x704F59B78CB5206FULL, 
            0x4EF7F6953324B072ULL, 0xD2DF4F045468BF03ULL, 0xFE81D7A68D2D0CB2ULL, 0xF2A2850D6F5FDD64ULL, 
            0xC708047E2E1D85B3ULL, 0x09111735DDDDF63EULL, 0x446938AFFADB8194ULL, 0x38940EC725C80D2FULL, 
            0x5322E5377FA40B28ULL, 0x528581690A4D4666ULL, 0xCF781B12E98A3E12ULL, 0x65167C910CCC016EULL, 
            0xD951BB9A848D06D6ULL, 0x6E3E124D2E4996BEULL, 0xC299E421CE6753E3ULL, 0x4FF7EFA93D0553FEULL
        },
        {
            0x2FF081B8E70AAA08ULL, 0xFACD90206220C6FDULL, 0x460FD444A7D4BF09ULL, 0xAAAC8CAB35B9CF07ULL, 
            0x6853854E530EA083ULL, 0xF2D8BF69E3CAB416ULL, 0x2148D6E2EA7A3AA6ULL, 0x3803422DED437EF1ULL, 
            0x53F51C623041C8C2ULL, 0xBD2CFC755F1AA000ULL, 0xA2429CE1C977AC6EULL, 0xAB000DD1883B23EDULL, 
            0xF3850AC593E6BDC1ULL, 0x5011158F11B74946ULL, 0xA074593043537C9FULL, 0xB3D48314054866F3ULL, 
            0xE3E25B94822134FBULL, 0xCC11F7CCD305683BULL, 0x73164CB8FA33B95EULL, 0x0190DC630FF7251EULL, 
            0xA96BF93BF2C19E60ULL, 0xE31F2F3596FFD514ULL, 0x79702B502B7ED105ULL, 0x35D6EFAC132FAA8BULL, 
            0x7512DEEAAE7E2ABFULL, 0x419392FF0B7BD394ULL, 0xB901CF4EA804AB8FULL, 0xF5AF780A5EA5F0CDULL, 
            0x78A77302655405B5ULL, 0xFBC13ACBB6535AC0ULL, 0xDA49CB7599C9649AULL, 0x8BDA6D5DD92C3D4BULL
        }
    },
    {
        {
            0x92BBC5E08871BE08ULL, 0x6B0DC920488D6F46ULL, 0xC46AF3D07E1DF7D3ULL, 0x79002B44C93AB09EULL, 
            0x6023A2902CCFE02DULL, 0xDE8AE3D28F9B0A83ULL, 0xB4AE88F06C6817BFULL, 0x325F02A57E34E322ULL, 
            0xFE4C7C3F03A6F342ULL, 0x702AC90A81A6C209ULL, 0xB6BF9BF55728417CULL, 0x7143A64BFA03585AULL, 
            0xC57F2B065F1BC4BCULL, 0x1561EECD10DCF751ULL, 0xF24EE435D891B644ULL, 0x3943D28F50257AF6ULL, 
            0x5F12D3A8DE0852D4ULL, 0x5C317EB8820E8801ULL, 0x9CE38FDD6F2316DCULL, 0xE3EFDC7E6DD97887ULL, 
            0x3F139314E33AE392ULL, 0x12F908290F7745B4ULL, 0x5125B518807EC52AULL, 0xDAD85411D5CC36F5ULL, 
            0xC8B66307BDC236B3ULL, 0x5303914FCBEB1994ULL, 0x883C87303ADD4BEDULL, 0xCC64377EB0DAA08DULL, 
            0x7221841214EEB55CULL, 0x000928809C2C5618ULL, 0xD43D48E5D41FFC87ULL, 0x96A95C1135E95ADEULL
        },
        {
            0x15D2DEB4D0B10C57ULL, 0xE44A3DE09EDC254BULL, 0x04D41CEF07FFCAB0ULL, 0xF60A6C2D4B84EF54ULL, 
            0x3DFE32CE9C5F8EE7ULL, 0x84DAE9015540F4EAULL, 0x8641DB72FF16D748ULL, 0xD1586D8BB32005ECULL, 
            0xF8CAAD8FF4B6206BULL, 0xF62A4DC63A7F82AAULL, 0xAE5141FC9E9ED192ULL, 0x569A684815410D2BULL, 
            0x437FC1B1AFB00C1DULL, 0xE895728492608593ULL, 0x325B39B5E9995D6AULL, 0xFCBA7AF7DC9990B0ULL, 
            0xF1941CCF742712C6ULL, 0x9510FB70B84C5FD2ULL, 0xD452C7F9E5071EEEULL, 0x39A081C153E93974ULL, 
            0x537448B6157C852BULL, 0x6E571A5BE5113415ULL, 0xB0D5DDCAFC9421B2ULL, 0xD8D2F0C3A18020A1ULL, 
            0xA2422B0E78D4C386ULL, 0x6ACCAEA5302C4BE5ULL, 0xD0F8B5848F779A05ULL, 0xA8E31E44ED64F1BAULL, 
            0x4484DB42525197EAULL, 0xDA3D50FA202D447DULL, 0x94A829C0BFBF2507ULL, 0xB228EE7706ED7A0DULL
        },
        {
            0x55A8BE5CB6E90A43ULL, 0x051EB147FA76BB62ULL, 0x4D759D472C4199A8ULL, 0x8A0EAFD098F1CED7ULL, 
            0x40C3FB67F7371C47ULL, 0x2663109E0494B878ULL, 0xB6352D785CEDC19AULL, 0x38EEA01DDF0A2627ULL, 
            0x9AF6792D3A77CA4FULL, 0x8C3B223D14EEBF41ULL, 0x2C2EB2762684DC9AULL, 0x9F116E4825C20DF9ULL, 
            0xDFD3EBC2C1048A85ULL, 0x5B22706DCD71866EULL, 0x79464916F22B2E37ULL, 0x544CC411A10AFE6CULL, 
            0x7935B837F56914CAULL, 0xC76066C8A1EBD71DULL, 0x88271968D7414FBCULL, 0x9517394738C4FDC5ULL, 
            0x577A5724F3E2B6E9ULL, 0xFF889C8EE37C3088ULL, 0xEDD3FAD2F436EA33ULL, 0x1C81A0DAEFFE5F26ULL, 
            0x32822BF6402C2C96ULL, 0x2516D8D1E514C52AULL, 0xA4448C14A1C1111CULL, 0x72095F151F2BF666ULL, 
            0xDC947A338238064AULL, 0xED433F9DAC7C2C28ULL, 0x9BAF728C70F059D7ULL, 0x0287DD466E8F8D10ULL
        },
        {
            0xBEF6F29202CBF147ULL, 0x3848B311BBE69234ULL, 0xA3F41FF8E6F34A6FULL, 0x8D27072E07C5D7F9ULL, 
            0x22275834EDCF9888ULL, 0x991942CAC60E9ABCULL, 0x8A3928EE8260CC44ULL, 0xB6FB1DD7AAEC6709ULL, 
            0x05927C5763EA0736ULL, 0x8553E37A49894F6EULL, 0xD18BABC4DA92B45CULL, 0x262372FE81A01D69ULL, 
            0xA5A3B90A23E71647ULL, 0x89DAED06381492B8ULL, 0xB9350A9107D9B141ULL, 0x0652AF90C3794F2FULL, 
            0xB56BE5A4574506E3ULL, 0xC7DF094B418266CAULL, 0x57409D8314599C16ULL, 0x4B583428A076DFD0ULL, 
            0xF8CE57DB1CE996A4ULL, 0xB2447F618F06EC3AULL, 0x13708F6D238C89CEULL, 0x03131C473AA08DFAULL, 
            0x8BAEF29E4C5A42C9ULL, 0x48AC8ACEBB5CF47CULL, 0x7A9E2DE23D532776ULL, 0x8D9646A438421AD3ULL, 
            0x934523584ED57894ULL, 0x17170F49CA7F6DD3ULL, 0x1FB31D9B72A593F4ULL, 0x5B4405BC8614B5B2ULL
        },
        {
            0x9992F7DCFF8E4016ULL, 0x579D4C11AA297B6DULL, 0xD4704AD2B30F1873ULL, 0x28F79403668A2AD7ULL, 
            0xBFDAACFCF9DB67BAULL, 0xB4314342E23896C0ULL, 0x638BFDF0A39E28DBULL, 0x87533CF255157AC8ULL, 
            0x92F77302713399B0ULL, 0x6DD2AC02B6A95E4AULL, 0x96B12D34EF3DF9C3ULL, 0x0E829D64DA28F159ULL, 
            0xE6B210D64AEB5814ULL, 0x5D243ABC634F7B46ULL, 0x90E52E8A45F3F784ULL, 0x3F6E5609101C0EF5ULL, 
            0xDD5DF5E8E62343D2ULL, 0x942EDCC807FDC4FDULL, 0x3382D5E5E525CBA5ULL, 0xEBED6FDF8B6D441DULL, 
            0x9163088955C1B45DULL, 0x9CFF4CA5B6E92207ULL, 0x1874335EF9DD700EULL, 0xDB36328A00C73ADAULL, 
            0x0FB39DDD497D9E37ULL, 0x6E33D7F1D2E74B63ULL, 0x988878151D70FD9FULL, 0xA7A506260DE7B17CULL, 
            0xABB0FF16B178902AULL, 0xB755B6CDA3DAAC14ULL, 0x0AB38599BDDFDF80ULL, 0x8B6E7081BADF179CULL
        },
        {
            0x5621F25E3A23215FULL, 0x0110F8208EAB620AULL, 0xA06B09BF1A994E4BULL, 0x6F14026BB537AEBBULL, 
            0x2625626A1A70FDD1ULL, 0xA1DE124BA6BB5AF5ULL, 0xC956FEA758FB0EF1ULL, 0x8337AE1F94A71528ULL, 
            0xEE7DBCAF6C983899ULL, 0x13533C82EC1DA0F8ULL, 0x66CB031CE7096FF1ULL, 0x6C427C0FF4DEE44EULL, 
            0xFF3D54A305335A99ULL, 0x76DCD32AA1AD0F5FULL, 0xBCB10FCFBC253BAFULL, 0x264D189691887487ULL, 
            0x4AC2F96D852DAEFAULL, 0xC50BB3191990D87BULL, 0x411110EC7272327FULL, 0x2B8CA2E7C74AABC9ULL, 
            0x3528BCBB5D66289FULL, 0x0F7998A9384785FCULL, 0x6F823996847C054DULL, 0x52224D3566357295ULL, 
            0x9052EC8E6F5D1428ULL, 0xD817480A92139F2CULL, 0xACD54150B9FC03CBULL, 0xD7D9869222590F62ULL, 
            0xF1600DAF3BFBEC67ULL, 0x056232DEA4C24134ULL, 0x026C1981AD779550ULL, 0x7106D6E7A93187CBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseFConstants = {
    0x7360954BF3D50EDDULL,
    0x10F05BF6F13ECB10ULL,
    0x86B3E5CC91BD2F9DULL,
    0x7360954BF3D50EDDULL,
    0x10F05BF6F13ECB10ULL,
    0x86B3E5CC91BD2F9DULL,
    0x88F1D2C5B551308EULL,
    0xD38763C4B12732EBULL,
    0xF9,
    0x72,
    0xB9,
    0x41,
    0x35,
    0x36,
    0x2B,
    0xB6
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseGSalts = {
    {
        {
            0xCA428BF58C3A597FULL, 0xD7F878A160D84AE4ULL, 0x46D50B972019254DULL, 0x58DB42C13F308594ULL, 
            0xB5F32762AE6CD5C9ULL, 0x4252BD33BD64F1E0ULL, 0x3C65317E2B2166C0ULL, 0x64D96CFBEA5263A2ULL, 
            0x9ED8CA7B45ECBC90ULL, 0xC7B307294DD1E9E2ULL, 0x8169B58DD3B45795ULL, 0x7EC53BA18225B342ULL, 
            0x1FB4C42DB59E4260ULL, 0xB8F3CD677711BA2DULL, 0x2792EFDCD250B2CBULL, 0x8D85555F4340421CULL, 
            0xF6F62B0B2C23A99FULL, 0xCA5E3D0D7CF57826ULL, 0xB47FF18E10EF0058ULL, 0x881CD246FCCB2E09ULL, 
            0xC2C4A50CC0DF8A29ULL, 0x848C9C166729CD1FULL, 0xB2A9ED4EEDF145A7ULL, 0x230A242A9E3BE7D9ULL, 
            0x584DE38AD3BE66EEULL, 0xEDFE38459696E41FULL, 0x1DB207DEA3A396FEULL, 0x9BEDD62C56CE6847ULL, 
            0xAF9BA8344E8102A5ULL, 0x809DD216A081D77DULL, 0x0819C4D212FD11F5ULL, 0x5C3E9165CFF15EB6ULL
        },
        {
            0x492037CD06FD17B6ULL, 0xE90303DA516357CFULL, 0xF687E79A90A4A37AULL, 0x61E8ACCB6F091CFEULL, 
            0x36FA8B3CBF96C3EBULL, 0x734051B9D2D16782ULL, 0x9B53558C8B513DFAULL, 0x02B449A0969AF80AULL, 
            0x32B763D89B8DD9FEULL, 0xA528CC71273E2D77ULL, 0x4E756CF4DE0BE1CBULL, 0x0D941EEF9833A630ULL, 
            0x91A920315416DF91ULL, 0x89C4CB816240DEEEULL, 0x7A938AFB7774852FULL, 0x96412A7EC2F11FDAULL, 
            0x19E2A9F6575C8A99ULL, 0x92E7CCD6F2758702ULL, 0x975C0D65D88AA4DEULL, 0x56B115787D87059DULL, 
            0x1A9687FF1287CABFULL, 0x8AB4DCE55CB26AD1ULL, 0xAAAD16EC6F3FE01DULL, 0x35834459EC4859A4ULL, 
            0xFC74E7054AAAB135ULL, 0x440ED9D471224A0FULL, 0x11DDED1407C535B9ULL, 0x9114D9E98B783BF4ULL, 
            0x50772796227970E5ULL, 0xF00E627F26D01090ULL, 0x26BFF4F61A7F11DCULL, 0xEBFA91BD9EA1DE45ULL
        },
        {
            0x22B27C2FA1D2D2E1ULL, 0x3CDE6F3545695983ULL, 0xEFA2883363414237ULL, 0xE2544C82931A07B9ULL, 
            0x7C7546406F561215ULL, 0x62411FDBC547B071ULL, 0xEE24492FF697ED9FULL, 0xBA482379CD472E96ULL, 
            0xAFD1B9002BD4421DULL, 0x4DB014BD677E7E0DULL, 0xFBC80B63B6CC47EDULL, 0xADF44690B14BD60CULL, 
            0x51DFF8CFB157C101ULL, 0xBC1BA655C89EF5CFULL, 0x94B69049FDA37925ULL, 0x9ECB215CA7FF9A7FULL, 
            0xA2F40B24B2731A2AULL, 0xDF172F5B3E08F1BCULL, 0x674DAF32C5B9CA73ULL, 0xC0FDED52E72FF0F9ULL, 
            0xF4F73D680CC515C9ULL, 0x471BCA2C61E073D8ULL, 0x726DB9F83522F5B4ULL, 0xECB53365531F19D5ULL, 
            0x85454A37490DE11DULL, 0x3D9C8482ADB6F3FAULL, 0x49170B82DB637166ULL, 0x4F1EFD1A41A4F477ULL, 
            0xC6F94AE739E41FA2ULL, 0xA10E0AA75EC6B197ULL, 0xA43617AE1ED5890EULL, 0x3F9161680A9D9819ULL
        },
        {
            0x7456FC6EC3F525D2ULL, 0xD88434F7EFA1888CULL, 0x8FD1AC282FBA66FFULL, 0x5A7C5B6F2D794B28ULL, 
            0x53B86606A672354DULL, 0x0881CB77CF629D9AULL, 0xDCB4B2D039DE9B34ULL, 0xAC38C6B33C58401FULL, 
            0x1753E2FDBBDC46AFULL, 0x2C64CD80650CED12ULL, 0x129955FDBD39B3B3ULL, 0x62021286EF978A21ULL, 
            0x1E1551D9279B99B8ULL, 0xC6B81243C7FA926CULL, 0xCDFB031D002ED56FULL, 0xE2A135869BDA0084ULL, 
            0x9CBD044D7F4AE39BULL, 0xA4E49BD345D7B334ULL, 0x0D90838483EDB0E9ULL, 0x0357D0A226C90E86ULL, 
            0x1C8F47854C3EB36CULL, 0x02E49EF33FD37796ULL, 0x250940E3A346C360ULL, 0x89216B375AF6B048ULL, 
            0xF07561E2A0BBE012ULL, 0xB6E642C68AB43672ULL, 0x64D7EA5C0E562263ULL, 0xBA03EC73AF9A4A02ULL, 
            0x5FF8641DBE7632CDULL, 0x17A1E70E6081D139ULL, 0xA17202E07CA17BDAULL, 0x3B5A4D4320D050FCULL
        },
        {
            0x87A0D1C9AB0DCC64ULL, 0xB271063089B412ABULL, 0xEFE9B3E981595D68ULL, 0x5C4910EBBA83BE06ULL, 
            0x7B801820F6DB60F7ULL, 0x6E9988E42E8FB23CULL, 0xF671D941346261B0ULL, 0xDDB8CF20352AD1C2ULL, 
            0xA7A9A3C61B2F2150ULL, 0xED164DACF487FEACULL, 0x339766AB466F55C8ULL, 0xBBD297615BA11245ULL, 
            0xE797F98111CD2504ULL, 0xB09608E56E2BD836ULL, 0x644ECA84BADFF140ULL, 0x734EFD480708A8D0ULL, 
            0x6AA24F70517BBBC5ULL, 0x2EFB588FD3C2679AULL, 0x0E288B0758AC2CA8ULL, 0xB8AFED8E720BECE5ULL, 
            0xCFFA2D3B81AF3E29ULL, 0x7C805253E166CCFCULL, 0x99663E7B5F83C30CULL, 0x74CFFCD034DEFAF1ULL, 
            0x0457A9EB70E1348EULL, 0x55708ED1EAAF5668ULL, 0x609752BCEAC6E5D5ULL, 0x70AFD2BEBAA4BE14ULL, 
            0xA6F955881DD5A653ULL, 0x0B9408DBCE00D0ABULL, 0xA56F478833A189E6ULL, 0x1EAAF27D83454496ULL
        },
        {
            0x55C9B6DED8E21A53ULL, 0x6D5EDB1245382290ULL, 0x2519DEA5B6ACE68EULL, 0xAF37B982A5441F90ULL, 
            0x28371E4B6E65D761ULL, 0x308CE323C89EF7A6ULL, 0xB7AB051B7BB01AFBULL, 0x2DBB003AF67E85E4ULL, 
            0x12F8F5F7112C43B7ULL, 0x08A86C786BDBB71AULL, 0xFE55DCE90B9B4E2FULL, 0x3C65A315A0991B20ULL, 
            0x7DE8648643F5C518ULL, 0x8FC999362CE0DBEEULL, 0x334D88668B6CB473ULL, 0x783E52A7EA444B09ULL, 
            0xF1FB2A8E0230D912ULL, 0xEAB827FB2C254636ULL, 0xB64A4173E1F0ACDDULL, 0xE8E3D4ED7251DEDAULL, 
            0xF3A86CB5F4EB2157ULL, 0xC7DE53C22D6BD578ULL, 0x5117D1364B405114ULL, 0x5EFE16DE184A79CEULL, 
            0x959273F5D4A1A268ULL, 0xF6152CBD40E1CCE0ULL, 0xBFF0B1AE8EECC36EULL, 0x40967B0245A6469EULL, 
            0xFA1660C95D7928D2ULL, 0xE7049514A5F80DC2ULL, 0x9D38564BBA5F2291ULL, 0x00213235D0E53083ULL
        }
    },
    {
        {
            0x770107501FD02DD7ULL, 0x36D552CC966B9AE6ULL, 0xDEB0CC64735D6A18ULL, 0xA85E763F4AD5EAB6ULL, 
            0x0F2C4072C79BC153ULL, 0x12EAC70BEF0C4B76ULL, 0x2BB350394EE5D175ULL, 0xB9CF4E76FBEA6059ULL, 
            0xE12EBD125364F139ULL, 0x2FFC5E817D009756ULL, 0x76CB24D3AF158EDDULL, 0x24C8F54724DCE9C9ULL, 
            0xB9F3D496822BA8CCULL, 0x75F27EC1A06EEB34ULL, 0x74B0765A9E79CF21ULL, 0x60745EF4F5453B6BULL, 
            0x1C224214C61DDD70ULL, 0xB231C32093A641F7ULL, 0x9C87D816CBE112A6ULL, 0xF03A302C845026A4ULL, 
            0x273BC63F8F10318DULL, 0x9192E9ABEDA5A4D6ULL, 0x99E48CDDA03BF340ULL, 0x1892333AF16901F6ULL, 
            0x2FF62BDAB79D5A69ULL, 0x3E6FCAC39E20D0F3ULL, 0x54751AFFBF44FCC3ULL, 0x4F608F88F33B2292ULL, 
            0x212E1E1C25894134ULL, 0xD5A62D7F6E18DDDCULL, 0x47ECE91226FC2054ULL, 0x6706962398AA794BULL
        },
        {
            0x3D5274F4FEFC4F7EULL, 0x0AFBE8ADAE6260F8ULL, 0x0F245B2B17EE1E56ULL, 0x82843D8453119F9AULL, 
            0x6ABBFAB63ED81E8BULL, 0x1F7D080CE69E4A71ULL, 0x73607E0033F76294ULL, 0xB94E4EAE0DFBF40AULL, 
            0x1413F18C575ED0FCULL, 0x6308F298F42BA6CCULL, 0xF90B9DDAC5D9B3A4ULL, 0xDE8E71624B1A1807ULL, 
            0xEC411F0A561365E3ULL, 0x18B053D2D5D0013AULL, 0x14038991907C1B1FULL, 0x6C5EB3DDCAFC6045ULL, 
            0x39E799FBE8BE3844ULL, 0x3B4F55D97508F22BULL, 0x1264DF20CB578315ULL, 0x43B516E85BECEC35ULL, 
            0x3783061F55E31C05ULL, 0xE4D2257CC82B987EULL, 0xB46E7ECAD617C639ULL, 0x6ADF39DA9EED342AULL, 
            0xBEBAC4049022C61EULL, 0xAF8A1F85437A5027ULL, 0xCD6628CD6C58D422ULL, 0x01BB7EC89F00D78CULL, 
            0x19DC729BDB127F7BULL, 0x9F86EA0DCF1F16A1ULL, 0x081991D27D8981EAULL, 0xF1180738BB81D6EFULL
        },
        {
            0x16525EF09322C751ULL, 0xE6A97A8034E49A56ULL, 0xB56F0E13DA6D11B8ULL, 0x550412A7A5A18F7FULL, 
            0xC59FBB9C906D9024ULL, 0xD10624FA5FEB8B99ULL, 0x5934A3BB8215E419ULL, 0x4A1D8C86E55A66B9ULL, 
            0xA326513383AB8A48ULL, 0x5EE30077C81F5626ULL, 0xAB27BACD424B01A9ULL, 0xE0DCDEEF364D762EULL, 
            0x3535D0873E7C6654ULL, 0xF4B7862A0CEBDFE4ULL, 0x77E3442526BEA4C4ULL, 0x874768832ADFB855ULL, 
            0x162073494521F5B2ULL, 0x54043B3DB02882EEULL, 0x48972EAC233D532EULL, 0xEAC0C32583E2500FULL, 
            0x160BC449E6ECC51DULL, 0xDF8E25B6CDEFC93CULL, 0x7109962236D9D72BULL, 0x2DEA7D9C0371A97FULL, 
            0x14DF0C6B84D2F02DULL, 0x1CDC29ACFE4CB9EEULL, 0x95671FAD368BBF8CULL, 0x0DC37918861CA8C8ULL, 
            0xD3F5F4B54C4D079BULL, 0xC30E60C64AAB03E3ULL, 0xCBE81B4AE20387D5ULL, 0x54B4C62A3BE73573ULL
        },
        {
            0x10F76BE6712AFA26ULL, 0x97D43CB4A5237035ULL, 0x00E04F5715991096ULL, 0x4B51E21408AA7B73ULL, 
            0xE143E24301AF6E8EULL, 0xF081DEDA53B95091ULL, 0x628268F0001D5F7DULL, 0x12FECF0DC45CA0E8ULL, 
            0x70A02D659F1B888AULL, 0x12BFF541AE3DD6A2ULL, 0x0FF88D89BC0CC4D1ULL, 0x0ACFB348C5964EE5ULL, 
            0x3563D2F38DAA00D0ULL, 0xA6DE88E6CBE5525FULL, 0xC699829DF5001C93ULL, 0x5AD940AF2F5AE8D3ULL, 
            0xC34A0B7BA308314DULL, 0xB2CC7B5CE04E618BULL, 0xDAADAACCA4512266ULL, 0x2ADD203D0E810FE7ULL, 
            0x528E42C112076217ULL, 0xD012C835071AA880ULL, 0x657697A957A36563ULL, 0x906FD123075AB6DAULL, 
            0x7E8950465D43DE50ULL, 0xBB8DD599E17B86FEULL, 0x01C0419598C21D1FULL, 0x9974762BF79F93C3ULL, 
            0x2EA604DFF69F37D8ULL, 0xCF484DE004ACC99CULL, 0x73A611E2EB2585ACULL, 0x84731168A8CD2020ULL
        },
        {
            0xD46DBCDC745AB737ULL, 0xE0BCF63E83ABFA3EULL, 0xA7A084B9C6B312DCULL, 0xD986AA49CD39FC5BULL, 
            0xDD04467C0CFEE49FULL, 0x1D716E9AF522D1B1ULL, 0x6C528C1389FB0AC9ULL, 0x9A9AC7364DF8A02CULL, 
            0x162B7CF88FE05070ULL, 0xF5ABB8CD519F2B4BULL, 0xD7FE0FD9CFCC367DULL, 0xAA17D6A8F1DCA596ULL, 
            0x2309A3BFB238B24AULL, 0xAE83111F3EC9A2F3ULL, 0x7C92550AF966869EULL, 0x232B723371AB2385ULL, 
            0xA66F867DC67FEC00ULL, 0x0C7CDA5F132B71EBULL, 0x3B4C209FAEFF5027ULL, 0xFAFF86790C62259BULL, 
            0x7903133445DDD82FULL, 0x753A7BACBB8D41A4ULL, 0x83367AEFE2643550ULL, 0xE3B5FB511F8D3D6BULL, 
            0x73395129F376EEC4ULL, 0x2DA242E50949B087ULL, 0xE81733D446B1BC86ULL, 0xDCD6EA8499E215D5ULL, 
            0xB4B70B1530C720FAULL, 0xE0D68E14D158A493ULL, 0x9933179990C87CC6ULL, 0x1616AFFB92659B1BULL
        },
        {
            0xA5988BE099F16A8AULL, 0x64F5732167392E8BULL, 0xB2BB647338B7EFCBULL, 0x87652AA0681489A5ULL, 
            0x31E1C4B1A70E0B57ULL, 0x7547DDC984A6CF68ULL, 0x692003ED8B6C2568ULL, 0xFEE8EEA90DD8004BULL, 
            0xA8258C80BDD2AB1AULL, 0xA21C62F72DAD7CCAULL, 0xDAA052DEFD1AB268ULL, 0xB2E86DA9C176E363ULL, 
            0xB7FD0AC3A73A681EULL, 0x80C720377BD1B565ULL, 0x37EAF8FB595C56D5ULL, 0x5842C15966A5E1C5ULL, 
            0x8FFB0A76E15FFD4EULL, 0x2092207372C59A37ULL, 0x9998EF0C3CDEF7EBULL, 0xA4CF515A6B321743ULL, 
            0x1FDC8429EBE9AD2CULL, 0x173A2155E64AEB28ULL, 0xF2FB70DF9B4ADABFULL, 0x6300E56F464852A5ULL, 
            0xF12C9B87BFC31052ULL, 0x06582BA66064AD43ULL, 0x5CE77FE2BC18907EULL, 0xAFEFD84B0215C19BULL, 
            0x7DDCDEDAD0299142ULL, 0x918DAE66F996DA1BULL, 0x5F534052B2BD9209ULL, 0x7A1459FF54E3E6B5ULL
        }
    },
    {
        {
            0x3EB10E857A4BEB47ULL, 0x924C7EA5358DEF65ULL, 0x1D3D709050CB40BBULL, 0x90BCF63A1612D821ULL, 
            0x85E4CB6B98DFA773ULL, 0xE179E3A807EBA23DULL, 0xD5533605661D10B3ULL, 0x41E22B656779F891ULL, 
            0x47FCFC240A290620ULL, 0xA3975EBDE15854FCULL, 0x33A6D6B4AE48005BULL, 0x4B39ACE08271666CULL, 
            0x00285B318E5717B8ULL, 0x354FD4EBA3AB8BDDULL, 0xF6522C9FFED24D88ULL, 0xD1BEB7192CE068A8ULL, 
            0x0C1A962C91F6EE44ULL, 0x0BE3C0D8266E0470ULL, 0x9BC75D45BC03B1AAULL, 0xFB37D73621F46C05ULL, 
            0x21EA3EC0397E4BABULL, 0xA61389FDE1B3B572ULL, 0xC592B007B8395C1CULL, 0x18337220FA2FF706ULL, 
            0x5D7CE03BCFB96ACAULL, 0x0FE8D37A3D4EE5BDULL, 0x9C921C63D52E8307ULL, 0x282C9510AAC264BEULL, 
            0xB3B47DA2BFE7EBCFULL, 0x3C219457059A1D71ULL, 0xD2D018D35C6201D7ULL, 0x7C0B8D8438D3146EULL
        },
        {
            0x0D1400035FD15F7DULL, 0x263D2C8033C19445ULL, 0xEEFACE78ED39410BULL, 0x060ADB1C88F60E47ULL, 
            0xEFEACEF1D6963A01ULL, 0x5B76EC8A178A6268ULL, 0x50CD59F1636F1222ULL, 0x28A398DC9A7F5D17ULL, 
            0xADAB4979142D6957ULL, 0xEC1AFF8DD5B43585ULL, 0x9489A050A3BE6F48ULL, 0xF903431D6B807938ULL, 
            0x14AD4434890DB516ULL, 0x04A71D3DFC59ED41ULL, 0x52BDD1412888E82EULL, 0xD6F5405DC8453F0EULL, 
            0x40B922F36C0598D9ULL, 0x8B962B03791C8E66ULL, 0x46C6EC8E898DA21DULL, 0x1CEC8786907F4EF8ULL, 
            0x75704B5EFD531834ULL, 0x08EF02F3EC429A90ULL, 0x03807F9EF0D9179EULL, 0xE41CA937B14E875EULL, 
            0xEC0795FBB1A4C35FULL, 0xB0FD8F4C37771994ULL, 0x92F25D496C36AA44ULL, 0xFFFC797FD351E03EULL, 
            0x27A596395920D000ULL, 0x33346C0CFE9AAC9AULL, 0xD8C8E0CF877C9A3EULL, 0x127DF604C1291ACEULL
        },
        {
            0x22A848979DA1E051ULL, 0xF194F497A089BCB4ULL, 0x7FF7DB1B6C0B0253ULL, 0xA869B2CAC350B749ULL, 
            0x2C2F960B00EB17F4ULL, 0xEA986AC055F99DF6ULL, 0x46A80D970D7D5BDEULL, 0xE9B860BB8C13F9AEULL, 
            0x8CC0FF96AFCC0207ULL, 0xA46924702A53B26DULL, 0x341C398C77FE8AE2ULL, 0xB168A0106D4987A6ULL, 
            0x69512243D0509D2AULL, 0xCC1A907CAC5795ABULL, 0x9AE483707679D544ULL, 0x5E4EADEFA92C9CA3ULL, 
            0xFA44EC3101EED2BEULL, 0x32906B5E2DC3134DULL, 0xB102E18BFA5CA6A2ULL, 0x3BB68C0CBD4C79A9ULL, 
            0x12EC5339353E2DC7ULL, 0xD6CEB7E65CC84695ULL, 0x22546D26553B8428ULL, 0xF9247E7F1E6BEF03ULL, 
            0xAECF8E65782B8DA7ULL, 0xA4DE7F8417A43393ULL, 0xF38B49809032E177ULL, 0xF5177FFA9CB3BFEEULL, 
            0xA9CB4D3222C234C6ULL, 0x1AF74F58F3E9953DULL, 0xE89BA24B6ABBA694ULL, 0x33DD9AAC73D7C5DAULL
        },
        {
            0xF9AB79D739ED9605ULL, 0x58F94B137A3CC5F1ULL, 0x2F51FFC98862BA43ULL, 0x65107BF57E6BBDBCULL, 
            0xF6A0647C789DC35BULL, 0xCA66C5C331B14A7DULL, 0x635457862A329EA3ULL, 0x446CBF6468BEC0E5ULL, 
            0x9E8F746AC6A6E585ULL, 0x9EDF1ED7E028F7A2ULL, 0xBFE2A7A811A380D8ULL, 0xB461BD6D0AC755C2ULL, 
            0xB78C5E9DFE468CA7ULL, 0x34B078E1088A5B0FULL, 0xF627ECE4CA4B6706ULL, 0x90D30CA2E1043C15ULL, 
            0xE7BF77BAFEA38333ULL, 0x4572DF404904DA60ULL, 0x26964EDA5E4C3A51ULL, 0xDA2E55527B769101ULL, 
            0x44777C5B788EEA09ULL, 0x061DD15BD5B456E4ULL, 0x8E29CE9815192CD3ULL, 0x6E0AEB8B487833DBULL, 
            0x2A1937F2AE053A8AULL, 0x7753A8B8DD415278ULL, 0x44DA97778325D4D3ULL, 0x1C92D3E4A186051CULL, 
            0x9A5B629FF48583A5ULL, 0x307D5E780072DECBULL, 0xBC93CA5D934CD5CDULL, 0xAE55563139B9D2DBULL
        },
        {
            0x33C32A4A00A89EABULL, 0xD15DEE6272C5EE96ULL, 0x2F8A126B44FC019DULL, 0x7CA8277D17EFB529ULL, 
            0x9B594360EDBDDB67ULL, 0x482772A37049F9A3ULL, 0xFB8BDA4E3BB4A515ULL, 0x068B5A55CB4753C9ULL, 
            0xBF1BF40A399AB1BCULL, 0xDE3467F216AD5CFCULL, 0x845DDF42BB70CA43ULL, 0x73A9A453C8EAA881ULL, 
            0x1B469F9C576B6149ULL, 0x13DF413FFAC0D472ULL, 0xEB6AF2F812F21D96ULL, 0x7BAD1554012D75A6ULL, 
            0x7D6D8F3F23DB8EA9ULL, 0xA35211360AC6E361ULL, 0xAC2FD9F0C80770FFULL, 0x7A4D65AE3D28917CULL, 
            0x8E1CA8B8E3919582ULL, 0x06C904B6577FFABEULL, 0x6F89C2F712BFA9E7ULL, 0x50F08D1C50605929ULL, 
            0x94516BE0B3B4E0EDULL, 0x9553435EC21781BEULL, 0x15DB36843717C759ULL, 0x3B7F5FE0003C653DULL, 
            0xAA36BA175DA2F2B6ULL, 0xC2BAFA51F424CBE3ULL, 0x29C4870B7D0C2073ULL, 0x1C06F3F99EB38384ULL
        },
        {
            0x211ED91D6E6EBCF2ULL, 0xC465B026AAA0E906ULL, 0x0F0082C376664747ULL, 0xC62D811394AAB78CULL, 
            0xA74A31203B30087AULL, 0x422B434556104941ULL, 0x2A83F40309A3E2ECULL, 0xC93DDAE634BA2068ULL, 
            0x2B73EDFEC2D328D4ULL, 0xA787DE312C695E30ULL, 0xFB5F4ADE7C09AAADULL, 0x0F1B976C168C2C3BULL, 
            0xE0AF59F0CF557C92ULL, 0xEDDF3A35FB8D9FCFULL, 0xB313362441E47F89ULL, 0x611F1DEEF9A97D81ULL, 
            0xF795E8496EE95925ULL, 0x8A9E12ED9317662EULL, 0x8AC36436CC76BC83ULL, 0x59493F611FCAA6CEULL, 
            0x44BEF61F643023B4ULL, 0x16C1A7A7D01DBA2EULL, 0xE0125E1A2325984EULL, 0x2C7EC59473E2415DULL, 
            0xF1CB20154B4DFA65ULL, 0xA9D8F50DF6A58BB0ULL, 0x8CAC0245C82A2B49ULL, 0x8872B5761B53A98AULL, 
            0x07EF899C87380FFFULL, 0x31E11D5B267C02DAULL, 0xB6049BCEF8026229ULL, 0x9BED110812D4F337ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseGConstants = {
    0x3F717E9E1569FC2BULL,
    0x0BBD52075A55780FULL,
    0x1FB2732CCB0CFA5BULL,
    0x3F717E9E1569FC2BULL,
    0x0BBD52075A55780FULL,
    0x1FB2732CCB0CFA5BULL,
    0xC3F6407B54618B6FULL,
    0xF0D177AC01A9A2FBULL,
    0xFD,
    0xCC,
    0x4C,
    0x05,
    0x9D,
    0x02,
    0x6F,
    0x20
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseHSalts = {
    {
        {
            0x2E0EE41901F5A21CULL, 0x6792FCBC0E4CF815ULL, 0xF686418CF5A084DDULL, 0xBAC596739BFF98A3ULL, 
            0xAAA6546F4353D7A9ULL, 0x508EB68419D27902ULL, 0xDA5CCF1590E59E4CULL, 0x1325B3B7B63FA8A3ULL, 
            0x4C54658731382B29ULL, 0xE3A803CE4ED5C1D1ULL, 0x4CC46AC79A2B21DCULL, 0x539B8C39608EFF0AULL, 
            0xFE620D077AB9C865ULL, 0xFB5812F7A6F0AB42ULL, 0x7668C87186B022FFULL, 0x9E4D52F6451B36D2ULL, 
            0x05BC6E26A6FD2F90ULL, 0xD5CD9385AC620FCBULL, 0x094CD61E405782EDULL, 0x3F14A3555B704E7EULL, 
            0xCCC96C753E6A1702ULL, 0x99A48BB391DD81F1ULL, 0xECEC5B99BFAC83FCULL, 0x2339F113AABEC9DCULL, 
            0xC5F37EDE9D495EDAULL, 0x00785C60ABF6498DULL, 0xEB9DFFF3D2A1A8CAULL, 0xDEC2C4A424B3C6CBULL, 
            0xFC61C654DC2C43DEULL, 0x64E3B6859BE25B56ULL, 0xFA333DE599CB0F5FULL, 0x4CCBDBA7993FE2D5ULL
        },
        {
            0xBABC7CEEB2552005ULL, 0x1CF48DD212000F4DULL, 0xC62B15EA2F38A0BCULL, 0xB81B0F5506EB5614ULL, 
            0x149DBCD2376CFAEFULL, 0xCA235FBD4C7A1971ULL, 0xE132D3878DD465A5ULL, 0xFC2C0376F24387D9ULL, 
            0xDF589D393B26699CULL, 0x1E49FAC4497AC224ULL, 0x4DA7AF02C660C50AULL, 0xE975886D8C70102DULL, 
            0xD11C5D34A0BE1E85ULL, 0x2F7B363549611F34ULL, 0xC8E5E16A71E4AA15ULL, 0x12CE77A9878D3859ULL, 
            0x220BAFFFDB59980BULL, 0xDD381DCC23CB61C0ULL, 0xC0FF8658F9654526ULL, 0xF351F87EF6E5259CULL, 
            0xEDAE0C44432BCC26ULL, 0xE8477C05F38D804EULL, 0x66B17FCD5AF11270ULL, 0x550AE6D8A9493D50ULL, 
            0x156FF5828A5A8782ULL, 0x1A42FC412A577AF2ULL, 0xB3F525D32134FBC9ULL, 0xE738F22C91008838ULL, 
            0x620BA04879C6AC9CULL, 0x398E3F8070336D62ULL, 0x2CF2D79A32CFE562ULL, 0x7F4DFDC463B7D72AULL
        },
        {
            0x24B5B173D08C904BULL, 0xE19FB63630EFB82FULL, 0x0AF26A8E7929B3F8ULL, 0xF312C864731F33D7ULL, 
            0x5EF853F73371B5AAULL, 0xFD35E9CCF2C3E655ULL, 0xE77AEBF3356F9FA2ULL, 0xCD657F7117F023E4ULL, 
            0xC0B06F6DBAA5DF85ULL, 0xBCDA4AEB8474F7F6ULL, 0x4418DC0450D5A989ULL, 0x84A5B2F3A6877BC7ULL, 
            0x3B5ADD5DA181892AULL, 0x3B76B1ED387C31B3ULL, 0x99145E83FC8A664FULL, 0xBB7E0270E02672FBULL, 
            0xAD3CC76716CFAA68ULL, 0xE412A5842CC082EEULL, 0x1253E555E6734B77ULL, 0xAC453AFF991DCA4CULL, 
            0xE6FF876D4047B491ULL, 0x258D142CE1466086ULL, 0xE71A8EDA52D8CC1CULL, 0xA893CACB9F7DD7B7ULL, 
            0xC7D52796D81884CFULL, 0x7F6804A287A3A7E7ULL, 0x25AC1FE4AC2F9662ULL, 0x99F02F1281618850ULL, 
            0x5E30EF635D5E89AEULL, 0x00C39FD801D0D335ULL, 0x179150B56D55667AULL, 0x0CF77F055041CF25ULL
        },
        {
            0xAFB519523102A450ULL, 0xA2AC04FD8F87BECFULL, 0xD308268B469B41E4ULL, 0x7862E0F8E11AD054ULL, 
            0xE98C83DF12C8D072ULL, 0x4278F61D6FF9B7A2ULL, 0x7658FEDCB81D61BAULL, 0xE1A206465B287B4CULL, 
            0x4294968BA4A9EE56ULL, 0x97908508C1D774F6ULL, 0x02A71DCBB064E268ULL, 0x12686627D541CB61ULL, 
            0x4DD55CFA0B3E9120ULL, 0x0B0EBFD136991CA5ULL, 0x3FDF84BDEA851CD1ULL, 0x18414DF5F8F0271AULL, 
            0x1881A54E7DD1FFCFULL, 0x5E96B1BF14FDC431ULL, 0xC596DBD318C7F765ULL, 0x2068E0ACBF6316B3ULL, 
            0x41BD1EA816A823C2ULL, 0xA77E9F712F78EF71ULL, 0x06EBD12A2F736216ULL, 0x47B61D1A57E0BB6FULL, 
            0xD47759F118A17598ULL, 0x7652B247B13DBFECULL, 0x9838F35A9D3B55DDULL, 0x3090FDB88CEAB841ULL, 
            0xAB8D8610831FCF3EULL, 0x2D2693C6AF06E6B9ULL, 0xCF95B6B344E32BC0ULL, 0x45B4026657CEE199ULL
        },
        {
            0x0F71FAA7A2F25941ULL, 0x1E80922A3A5EA3C0ULL, 0x41F3104EF4700EB7ULL, 0xCD44C5993BE19917ULL, 
            0x8BCE93B27F77D10AULL, 0xB29AF0CFFBD87CE1ULL, 0x12BE2021E4FF4949ULL, 0xFF6DBB10E5E581A1ULL, 
            0x9AF9A6427642AB4FULL, 0x3826844844E75D1AULL, 0x82CFD1799F17D5AAULL, 0x44604F3CE95E5523ULL, 
            0x76F085EC6B79470BULL, 0x927F6A936F2478BCULL, 0x3811D1BD56839918ULL, 0xE397CEA9378F3365ULL, 
            0x9427115FBAD9D055ULL, 0x2C95C387B67C5759ULL, 0x8D0E0388BC9B73FAULL, 0x720E33D92DB04FCEULL, 
            0xF3F750CAE2EA0BFEULL, 0x2CC2B9E8AE3CCC33ULL, 0xFAEA5ECB31B3B30AULL, 0x09FAF4191889206CULL, 
            0xBEBEA840CAB28CF4ULL, 0xFCDAC40574CD4DEBULL, 0x90A6F0B0C6D5644EULL, 0x3E4671BF71A3DA87ULL, 
            0x0736607FCC112738ULL, 0x27CF4FEE2454E70CULL, 0xC382D261A1B48204ULL, 0x2566831B41203C44ULL
        },
        {
            0xA1B27C0A502D2505ULL, 0x07593B36E60A7A27ULL, 0x84B14226083897CAULL, 0x17FE704075B80B2CULL, 
            0x2C6098B5BA3478DCULL, 0x54CB01EDD0B23E7BULL, 0x037B57D9B780A4B3ULL, 0x943E6CDE2D95493EULL, 
            0x08EFE925310F13DEULL, 0x582159D86B47CB1BULL, 0x6ED188DA1C83B039ULL, 0x395C44901A990C94ULL, 
            0xC8BC77716678A6C4ULL, 0x9F6F9796E156FFC1ULL, 0xDD424D832BACCC45ULL, 0xF9C1BDCFEF81C775ULL, 
            0x9C337266CE71ED44ULL, 0xB242A32AF460B712ULL, 0xCD040ED7CC1ECE08ULL, 0x86A4AE1646BE9101ULL, 
            0x72B468914E5E3E0FULL, 0x277271299E6E6CDBULL, 0x5EB058D2752FD1B9ULL, 0x5382142F6349D3DCULL, 
            0xD75B7906EE9213EAULL, 0x8A91237CABE15A00ULL, 0x7B1BAE5AC7B8F80AULL, 0xA8B1A8562961EB01ULL, 
            0xECF208DD03873479ULL, 0xF7EE24C636380CBEULL, 0x6D9C42ED47B33EBCULL, 0xFB17CD17022BF608ULL
        }
    },
    {
        {
            0x7C074964F3F9D9B2ULL, 0x96266E95EFB18A4EULL, 0xCF97FB151F446ADDULL, 0xA170FEE23972BBEFULL, 
            0x2393B655C5694368ULL, 0x4EA9108DDD58D45AULL, 0xE68BA2D0609ED906ULL, 0x70B092A0C68CF928ULL, 
            0x6DF1B7014E78292FULL, 0x461F15222C72E227ULL, 0xB792DD7A4CCEDF16ULL, 0xAD4837275355FB8EULL, 
            0xDFD269E24C47D416ULL, 0xFE7676BFC783DAC2ULL, 0xAA8AA2752601D0E2ULL, 0x6F0BAAA94D5D8336ULL, 
            0x987BEB8147AD4D86ULL, 0x2BFED7A4359989EFULL, 0x8EBA29387D077244ULL, 0x683A56B77D652D5CULL, 
            0x145518B22C55AC6AULL, 0x485F500C0643E053ULL, 0x61D2C8A8468CEDA5ULL, 0xA0ECF46F50423D37ULL, 
            0xA32259C8DDB701E0ULL, 0x86A1D26B68F16B59ULL, 0x064A550FC938F6ACULL, 0xB729E8E21C5BC252ULL, 
            0x07256E6ECEC04BC4ULL, 0xE47E38C5FC9E8F6CULL, 0x8CC17FE8E0AABAB4ULL, 0x7DF8E93125F0A2E2ULL
        },
        {
            0x8F7A4B294A082017ULL, 0x93FA5FBE41606DB3ULL, 0x8804FFA9545FDBCEULL, 0xB5E5915A49746B71ULL, 
            0x55A1FA11C466B72AULL, 0x46EA656C92879A8CULL, 0x1BDA73C58431FD20ULL, 0x85A3646D13AE461DULL, 
            0x8D50D28A3EB52E37ULL, 0x01C3645D4D4432B7ULL, 0x4B754FD8A37962C9ULL, 0xCF5AAC5F5216CC7DULL, 
            0x671537E030239A95ULL, 0x0A318139B5DBF83AULL, 0xDEB8562479D4A0AEULL, 0x6A414879573EA255ULL, 
            0xF651A875B8F148AFULL, 0x03752A201494285CULL, 0x490C494058AB6706ULL, 0x32B6A8EF9628EADCULL, 
            0xEAE7219DD09EBF9FULL, 0x49BCA39F216696F1ULL, 0x0FCF78C3C18154FFULL, 0x3AF223D279E4FA0BULL, 
            0x5CFFD66CEE1D48ABULL, 0x594568C9C84FBCEEULL, 0xADFD468DB98E2E32ULL, 0xC961034AAF620950ULL, 
            0xE3B870FD240B5C1EULL, 0x665A32AFE979B65FULL, 0x4ED206A908226391ULL, 0xDF3EC4CFD9E4A192ULL
        },
        {
            0x600DDB5A27158768ULL, 0xA78605416AB9F567ULL, 0x611A2DE41A526FE8ULL, 0xD92213E9607186DEULL, 
            0xF2116F059E040EA4ULL, 0xC8F47E1623E04005ULL, 0x7CC217AF063DE5C1ULL, 0x2B4612F6517F057FULL, 
            0x17B5E9A7265CAE3CULL, 0x83F7F67C392DC411ULL, 0x8F7C7886E29A4F16ULL, 0x8BB7BB3CFA3B9FBDULL, 
            0x243CBAF445585972ULL, 0xCE7F17AA0EBE21F3ULL, 0x71099EDE090161E3ULL, 0x19C96C414C39C61AULL, 
            0xCED86FA5FCD9C0AAULL, 0x8B361C719F50E9DEULL, 0x5A1381ABB2B41080ULL, 0x0D03855438853EAFULL, 
            0x9CF79CEDA534DBDDULL, 0xDBC2247B5E18D9FAULL, 0x93309AA5C4879038ULL, 0x7646B1F5267DC29BULL, 
            0xBAA4E98D58B5F08CULL, 0x576A8AC6DA5089A1ULL, 0xBAAB649357240288ULL, 0xB2D61C775C8F0B81ULL, 
            0x015F65C927D41E30ULL, 0x76F92C6DFA1C10CBULL, 0xCC8D22672C527689ULL, 0xA6DE588EBEF18302ULL
        },
        {
            0x3AB5BED39B350D25ULL, 0xD3AD3FB446E9DBA4ULL, 0xDBF1D8EFB8E21857ULL, 0x5BCBFB38284639C7ULL, 
            0xB31E3C986AE8335CULL, 0xEB9932B57BB59C03ULL, 0xFF4A740CE0A9BBCAULL, 0x60A5AC44F72EDA3EULL, 
            0xABDD7571CFDFCAF8ULL, 0x7B0907C1394BECB6ULL, 0xD7B11E1F2F380932ULL, 0xD12AE9BA9A84E7ADULL, 
            0xCA069AC9A3B69CA0ULL, 0xF0A44AE8DC48F641ULL, 0x433ED438FEBCADA5ULL, 0x382A6521484FD126ULL, 
            0xA792D2F5C37509E4ULL, 0x70AF635EC411B500ULL, 0x9B45DD8CAF4F6410ULL, 0x1E9E037333FA395CULL, 
            0xA4095607600C1191ULL, 0xC09BF3F7C91A3270ULL, 0x94B1CA350FF58E0DULL, 0x2E866B4F55653671ULL, 
            0xDA06E33DF97232B9ULL, 0x7D0E02CBF70901C6ULL, 0x6C6BC35F41456598ULL, 0xDF1177712B98D9C4ULL, 
            0x364F8FD025D34D91ULL, 0x6876E73A7004DB4FULL, 0x02576C906B0B03C6ULL, 0xA03DDE42C14D8CCCULL
        },
        {
            0xA7E35CAFAE4BE651ULL, 0x1D262A2D3E396987ULL, 0x28F70436A5C1BE14ULL, 0x3C3254489A7CF593ULL, 
            0x680048970A826D96ULL, 0x18BBCF0BE80AC2A4ULL, 0x76F1965E11C71251ULL, 0xFD296F25C627F072ULL, 
            0xE57FF853D46697DFULL, 0x43AFAF11F8E4C1E1ULL, 0x1C46BFAC178A301CULL, 0xF5587C0F7E92B4EFULL, 
            0x703E894BE3050C66ULL, 0x1C4409DFE378329BULL, 0xB564AB0F1E2C9BB1ULL, 0x894E2612EE3EBDF9ULL, 
            0xB59000FEAA3A8A8DULL, 0xC46B83769377C1D1ULL, 0x38DFAF638518E564ULL, 0xDC292786F65E70DBULL, 
            0xFEC678E138DB7D9FULL, 0xCE0496D6D1C59640ULL, 0x92968AE2B0822569ULL, 0xFF71F5459BC33C42ULL, 
            0x72A4DDDCBDE17D7EULL, 0xAB8DD69B215275ACULL, 0x6A6A482BCB1EE393ULL, 0xA74B022AA812E33EULL, 
            0xE3F79746659F1A9DULL, 0xAAAABEAE8A2E80CDULL, 0x3ADCDF3DA5AF748DULL, 0x24CACBE63F94780FULL
        },
        {
            0x73BFA9411435FF8BULL, 0xA683D2FDDEBB33C4ULL, 0x5E5B2C4E48F20178ULL, 0x367A0227C1CD9A01ULL, 
            0x7957A2B4A16E4717ULL, 0x2A633BC29AAFFE95ULL, 0x385360331FEA962AULL, 0x8BF7A0CE3FCC3711ULL, 
            0x61D7684DF59FAEB8ULL, 0x8B401EED1E12A1E9ULL, 0xD5354AB7442AC35CULL, 0x4E11C963BBB58460ULL, 
            0x23C3D2E4A17406CBULL, 0xB86E1C46B04C35BDULL, 0xABDF2CF61805BFE5ULL, 0xC7307BD91A7B3384ULL, 
            0x7B5430A24A8A9621ULL, 0xCE2B9BF361ECDCBCULL, 0x35743F740DFD7EF8ULL, 0x6FF56D680D5200FDULL, 
            0xB3E129326FC0CA23ULL, 0xECE0E9D5AC667024ULL, 0x79CDE169BA7245DCULL, 0xFDF9035BEA48D6E6ULL, 
            0x67DBC2C30104A188ULL, 0x81D47A6F110DEB41ULL, 0x5264C7BB8FFF83EBULL, 0x12D4B597664DD43CULL, 
            0x35705D68FDA1D8B5ULL, 0xED1DD185E65CEA3DULL, 0x85F3790176650651ULL, 0x1AC9457323E1ED46ULL
        }
    },
    {
        {
            0xCCAE700D6A3266F3ULL, 0x354A02D26A6BA448ULL, 0x408F58E5E9E71481ULL, 0x434B6A69078C8595ULL, 
            0xBBB2F03C92184FD2ULL, 0x879ED0B30BAD4032ULL, 0x1AD7F06841C93AFBULL, 0x2AC8A1009203F051ULL, 
            0x32D11C3168729342ULL, 0xDBFEE60DB0C51A98ULL, 0x9B54020B821EEECAULL, 0x27DE399634E1F6BBULL, 
            0x4A2C231EA297723DULL, 0x85FE42DA370F915CULL, 0x7F364FF486025BCBULL, 0xD5DD9F77E6FA3A64ULL, 
            0x5ECB1D67571D1BD1ULL, 0xCF641B38D85E901BULL, 0xF6A16E901F9C8AD8ULL, 0x920D1C849EEB7EDFULL, 
            0x9FA9102D6A4D385DULL, 0x104C55C87EB15883ULL, 0x1EE46ABB26E2485BULL, 0x743756522B6A32C6ULL, 
            0x0FE9B219850CF052ULL, 0x2143AA687BA61160ULL, 0x496B7C943EE79FE1ULL, 0xE6EE5109D744B77CULL, 
            0x88B707B554EFE986ULL, 0xC51DDDB757576FC3ULL, 0xE53FBB0E28F96CE4ULL, 0x158734F57563DB33ULL
        },
        {
            0xD14511D4E8E3D428ULL, 0x0275A3FCD2B01F13ULL, 0xF44D59B61F7F0881ULL, 0x0371AB9FA83A43DEULL, 
            0x04B54BB8FE4D6F11ULL, 0x044D3122763F8363ULL, 0xA8C2C9A6C42400D0ULL, 0xD7F1689C24502F4AULL, 
            0xB4BEC35B8FBD7D93ULL, 0x5D0370CD3AF6CD55ULL, 0xE4B2EA44050B5D13ULL, 0xFB0BB68C5188FF30ULL, 
            0xBEE17ADAEB95EF49ULL, 0xE6E1ED94B871E6DBULL, 0xAEF404FE6CC802B6ULL, 0x86484FACF1F7CEACULL, 
            0xC24032EB53D112EEULL, 0xCC86038DCD9871DDULL, 0xCF6AB2F9538DD1B5ULL, 0xA1E5C0F30CAA5102ULL, 
            0x3502BF9678CF54AFULL, 0x16161BCB752C6A44ULL, 0x698C25606B9939F3ULL, 0xABF1809DFA698EB0ULL, 
            0x5FBE5D8FFE48221FULL, 0x2852589401D9AE61ULL, 0x1E76C6697CE2F428ULL, 0x077C790B52B690F2ULL, 
            0x3A3CFA5509FFEB71ULL, 0x2E42D58A168EB628ULL, 0x150A195365AB8DC7ULL, 0x100E3EC1C12121E0ULL
        },
        {
            0x091F4BC773F5D8F6ULL, 0xB877BB856D577D8FULL, 0x8159BC5A901D6D28ULL, 0x283850B271CE07A3ULL, 
            0xD45CF9ED6D891C1EULL, 0x65DAD1BAB3DCB022ULL, 0x20638EDB72BA946CULL, 0x5E9F1474EF9AB740ULL, 
            0x72BD72FECF4D80DBULL, 0xF49CFB5DA5E4BD74ULL, 0x6947E7766C8D44F5ULL, 0xCD87A826D18C4B0BULL, 
            0xA7DE39AF97B03C01ULL, 0x94F1833DDC59E5D1ULL, 0x7F4CD827F5B38567ULL, 0xD3A4CF5BDF59EE38ULL, 
            0x3AEF1DCD70D82170ULL, 0xA7AE630153629FA8ULL, 0xB2099ED2F58F88C2ULL, 0xC99D80E8D559016CULL, 
            0x38E7AC89AB139433ULL, 0xFE81C68073090951ULL, 0x96AC5EFB4F5C0EC2ULL, 0x2108CB5409BE9C9BULL, 
            0x3F948BBAC93A2953ULL, 0xA21C9268BD8EC984ULL, 0xC8CAF97DA11AD8BAULL, 0x9B9A887E394EFD01ULL, 
            0x93A47F28F24247E1ULL, 0xC76BB16D5A1A5761ULL, 0xF6EAAE1E115CE7FEULL, 0x6529E4CB54E85EB2ULL
        },
        {
            0x77B9D8E3626E28CFULL, 0x0F187AB1BDDF8751ULL, 0x2103356430D670E9ULL, 0xA4C0FA6AC31273CDULL, 
            0x98B8AECC081F632BULL, 0x9EF989C11A1D94DCULL, 0x4CB997F3096BEAABULL, 0xDD64588B0F14142FULL, 
            0x496A4A7442F6E3CCULL, 0x6A31AD023F5B07D1ULL, 0x3BBFBF69ECCAD806ULL, 0x44D066C49019CDBAULL, 
            0x26B557F7D3BC92FDULL, 0xF06713861F68ECD6ULL, 0xE517420F462F1578ULL, 0xCCE780C6C9C2E808ULL, 
            0xA809937EFF96B556ULL, 0x8E69224DD94908D9ULL, 0x5A0C1C684239AF24ULL, 0x50E59CF908D21ADAULL, 
            0x5FE4E05FC2051767ULL, 0x5283196096F47BFCULL, 0x0E1E276FDB9CC5ABULL, 0xF23469092F4F6978ULL, 
            0xCC32589BAD41BC6BULL, 0x099FF4087231787FULL, 0x812567B101E086D3ULL, 0x85AD0788F105E045ULL, 
            0xE44002BB69E55D55ULL, 0xD0D862C8C5DA0D55ULL, 0xF3812E494D7609E5ULL, 0x040E65F90A61D793ULL
        },
        {
            0x165673FF2D42F577ULL, 0x2BDA81B6E566EE02ULL, 0xD8C7C83928CD835EULL, 0xA8121CA92498C2DAULL, 
            0x4D3BC9D21A3D8DA5ULL, 0x3670D72B2F581C32ULL, 0xCA42C2ED05A63BE3ULL, 0x594A08227FBDCE6CULL, 
            0xBB140B57672C410EULL, 0x929A3ED3AF5E92ADULL, 0x713313E55C22C426ULL, 0x0A46A117895AF8AEULL, 
            0x1B6306A7FA747500ULL, 0xB53E7A9E91D2979BULL, 0xB8FF0BCF8830D718ULL, 0xF0EDB5803EAAF21BULL, 
            0x7B1CA5F394A7EB67ULL, 0x52934DB8A27AACAEULL, 0x02C5C01BB6746838ULL, 0xDB80B47A2253AA17ULL, 
            0x44E8F7733EE0EE86ULL, 0xEC87FE19FE664E9CULL, 0x5F1972F54E76F37DULL, 0x41C5336169B96BB1ULL, 
            0x9111A6AFC3CA30F9ULL, 0xC29F68E4C3B90427ULL, 0xFAB0F07BF84689CCULL, 0xAC0E722E830C14D8ULL, 
            0x14B99F0295DCCB2EULL, 0x981F70CCB2B2829FULL, 0x31B97E83778E8AA9ULL, 0x209FB75FDB8206A5ULL
        },
        {
            0xD3B392BF509EE170ULL, 0x49EF4794BBB48F39ULL, 0x6A7DF63646278B41ULL, 0xE3D1385B79E72CD4ULL, 
            0xD89B821BE5C30749ULL, 0xE2942C6A4AF2325FULL, 0xBCC061A22DBDC95BULL, 0xA816DFB674341EBDULL, 
            0x6AB7B79B227FEC69ULL, 0x4AEB93FED6A7B961ULL, 0x97E691ABD20800D4ULL, 0xA9E72E741BCB5972ULL, 
            0xA223AFDE0C3D2E3FULL, 0x507C7D3DD14D697FULL, 0x39572E49BE02958FULL, 0x7267624A13D036B4ULL, 
            0xFE98B154A3A4DF4CULL, 0xEF2CE8C4B261195BULL, 0x0B61F59ABC10A390ULL, 0xA8993C2C2AFD84B1ULL, 
            0x25673B22B9A3EB53ULL, 0xF3F5F9BD349CE806ULL, 0x4C38A3AE26B97186ULL, 0x38F30D8EB5FE79B6ULL, 
            0x5605B21DB9DDEB94ULL, 0x651D8787629FBDD1ULL, 0x9B0EFD2F7049B8ABULL, 0xC2DC87AC1196BB39ULL, 
            0xCE01C0A6EE5FE603ULL, 0xC67EB60336D35AB5ULL, 0xCE8A84DDBF38B33DULL, 0xAF75BDD4566E2C6FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseHConstants = {
    0xE22607A20E92B5B7ULL,
    0x2362A7C088939BB0ULL,
    0x96FD0C9B5F8515F6ULL,
    0xE22607A20E92B5B7ULL,
    0x2362A7C088939BB0ULL,
    0x96FD0C9B5F8515F6ULL,
    0x9B68A110E2198C37ULL,
    0xD05DC6312E9EB837ULL,
    0xDB,
    0x30,
    0x2E,
    0xDD,
    0x76,
    0xC3,
    0x95,
    0x88
};

