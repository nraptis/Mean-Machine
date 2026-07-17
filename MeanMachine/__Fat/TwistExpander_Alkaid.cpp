#include "TwistExpander_Alkaid.hpp"
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

TwistExpander_Alkaid::TwistExpander_Alkaid()
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

void TwistExpander_Alkaid::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB69FCD73B1557C38ULL; std::uint64_t aIngress = 0xE3202CF69981A78BULL; std::uint64_t aCarry = 0x8649F5E9FE9F04AFULL;

    std::uint64_t aWandererA = 0xC7E17A4731D5A4AFULL; std::uint64_t aWandererB = 0x88DF2A381F8A3FC8ULL; std::uint64_t aWandererC = 0x8308E03DD3FE480BULL; std::uint64_t aWandererD = 0xEA318D33C1300F4EULL;
    std::uint64_t aWandererE = 0x8B95B2EBEB19AD4DULL; std::uint64_t aWandererF = 0x938D086294FED574ULL; std::uint64_t aWandererG = 0x9FBD04A50587A43CULL; std::uint64_t aWandererH = 0xDCA5FA48E5A43A91ULL;
    std::uint64_t aWandererI = 0xE9F6569DE6E7430EULL; std::uint64_t aWandererJ = 0xE668716394A8E674ULL; std::uint64_t aWandererK = 0xD2BF122CBD61E3E2ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15135899929970036323U;
        aCarry = 16934354210145041105U;
        aWandererA = 13429895345807631866U;
        aWandererB = 12699122877794399556U;
        aWandererC = 10927456682687343069U;
        aWandererD = 15613945165389866029U;
        aWandererE = 17634705040216774329U;
        aWandererF = 11266430891107294955U;
        aWandererG = 17578375809613177646U;
        aWandererH = 12323234572136658273U;
        aWandererI = 17631279071924762326U;
        aWandererJ = 14277934815851476262U;
        aWandererK = 17608798069637971119U;
    TwistExpander_Alkaid_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alkaid::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xBA6361F4975BD85AULL; std::uint64_t aIngress = 0xF125CF8FC44D5433ULL; std::uint64_t aCarry = 0xA3202B7B94765A27ULL;

    std::uint64_t aWandererA = 0xA5848B24B34EF861ULL; std::uint64_t aWandererB = 0x818C5D94D30D16B6ULL; std::uint64_t aWandererC = 0xAABD49C13B5E2E8DULL; std::uint64_t aWandererD = 0xC01237D5F7837B4EULL;
    std::uint64_t aWandererE = 0xA1F34A573C99E81BULL; std::uint64_t aWandererF = 0xFDDEC0E07473EFF4ULL; std::uint64_t aWandererG = 0xDD36986C4CEBA3D2ULL; std::uint64_t aWandererH = 0x9F4D1145ADB3EC95ULL;
    std::uint64_t aWandererI = 0xEFF26DE840BB2D4FULL; std::uint64_t aWandererJ = 0xD49A473AD1486436ULL; std::uint64_t aWandererK = 0xE03C0C9C77D0D73CULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12865834717797283904U;
        aCarry = 12432595411799725761U;
        aWandererA = 17393883236363693615U;
        aWandererB = 15062563442724229296U;
        aWandererC = 18099371403639620018U;
        aWandererD = 14512639405084242939U;
        aWandererE = 13909421739562731296U;
        aWandererF = 15755813705916556982U;
        aWandererG = 16070732754241677707U;
        aWandererH = 11449247570660048812U;
        aWandererI = 10950310337863800304U;
        aWandererJ = 13383438421544669836U;
        aWandererK = 13498281882504075968U;
    TwistExpander_Alkaid_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alkaid::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDBF574E37E76F57EULL;
    std::uint64_t aIngress = 0x83E652404A727B47ULL;
    std::uint64_t aCarry = 0xDC0C3097EA0A60ABULL;

    std::uint64_t aWandererA = 0xDE872CF7AFB2DF48ULL;
    std::uint64_t aWandererB = 0xA3AA9BC4288B411EULL;
    std::uint64_t aWandererC = 0xB4B266960552B808ULL;
    std::uint64_t aWandererD = 0xB35D9BB009B5B226ULL;
    std::uint64_t aWandererE = 0xBBBE36E8105C1403ULL;
    std::uint64_t aWandererF = 0xE2D9EF2DCE59ED5CULL;
    std::uint64_t aWandererG = 0xDBC999BA8EC599FFULL;
    std::uint64_t aWandererH = 0xB04F5677AC582611ULL;
    std::uint64_t aWandererI = 0x8D753F63B751E631ULL;
    std::uint64_t aWandererJ = 0xAEC96692AE2B691CULL;
    std::uint64_t aWandererK = 0xC17A7662808AE52FULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
        TwistSquash::SquashC(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneA);
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
    TwistExpander_Alkaid_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alkaid_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 5 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 7732
void TwistExpander_Alkaid::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1243U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 548U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1920U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 684U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 608U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1307U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1331U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 591U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1468U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1439U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 633U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1939U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 89U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 855U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 423U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 491U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 848U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1595U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 717U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 876U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1621U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1669U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1002U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 300U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 862U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 469U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 708U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1379U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 390U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 86U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 104U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1020U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1613U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2042U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 589U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 197U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1107U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 732U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 949U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1081U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2031U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1448U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 835U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1408U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 784U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 963U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1717U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1377U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 926U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 852U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1477U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1861U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1816U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 16U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 213U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 531U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 326U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 727U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1475U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1120U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 856U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1351U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 342U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 3U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1832U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1641U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 8U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 910U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 84U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1406U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1720U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1127U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 292U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 723U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 159U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1940U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 695U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1309U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 744U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 391U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1409U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 947U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1156U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1631U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1947U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 696U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 394U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2005U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 956U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 582U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1152U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 616U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1150U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1357U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1766U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1432U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1189U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1271U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 374U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1356U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1072U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 606U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 605U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1954U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1370U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1380U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1233U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1202U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1761U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1471U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1452U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1967U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 984U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 689U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1794U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1780U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 151U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 307U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1663U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 280U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1508U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1030U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 452U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 858U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Alkaid::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB73CE6443395607AULL; std::uint64_t aIngress = 0x8444839590F9A30DULL; std::uint64_t aCarry = 0x9294D89CE2629EF9ULL;

    std::uint64_t aWandererA = 0x81FD77AC9507A6FBULL; std::uint64_t aWandererB = 0x8436DEBDDA1C9920ULL; std::uint64_t aWandererC = 0xBB1A7A016E975169ULL; std::uint64_t aWandererD = 0x9A1020CE16F4A3B1ULL;
    std::uint64_t aWandererE = 0xB0E5282241914476ULL; std::uint64_t aWandererF = 0xACFFB884E2ACE51FULL; std::uint64_t aWandererG = 0x97A38AC110D48ED6ULL; std::uint64_t aWandererH = 0xA1FE6D2E8AD8CB79ULL;
    std::uint64_t aWandererI = 0xD08DBBED298EB7E7ULL; std::uint64_t aWandererJ = 0xE57F2234772D70D5ULL; std::uint64_t aWandererK = 0xFF6F75FDE713293CULL;

    // [seed]
        aPrevious = 17978944811903547925U;
        aCarry = 14755095887023853903U;
        aWandererA = 16651417236806345979U;
        aWandererB = 16123070668351010915U;
        aWandererC = 13369643457312365242U;
        aWandererD = 18225780088213036238U;
        aWandererE = 10729261083608867116U;
        aWandererF = 11894710474074655594U;
        aWandererG = 15828730204457587906U;
        aWandererH = 13061943214505784875U;
        aWandererI = 17816535201183023544U;
        aWandererJ = 14375029515738973833U;
        aWandererK = 9788463950518327547U;
    TwistExpander_Alkaid_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alkaid_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Alkaid_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alkaid_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 5 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2321; nearest pair: 533 / 674
void TwistExpander_Alkaid::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6121U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4939U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7910U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1439U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 759U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2844U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7512U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6357U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 352U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 810U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5766U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2165U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2697U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6718U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2381U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1890U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 629U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1049U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1314U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 741U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1078U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 811U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 973U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 390U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1022U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 577U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 265U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2036U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 733U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 230U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 649U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 73U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 23U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 261U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 5 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2321; nearest pair: 540 / 674
void TwistExpander_Alkaid::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 812U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6682U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 43U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5906U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7889U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5405U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1822U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7722U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6003U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7254U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3418U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5369U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3631U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7618U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4224U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5697U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 115U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 744U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 947U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1724U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1965U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 44U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1429U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 108U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1023U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1114U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 721U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1302U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 798U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1544U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 500U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 973U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1834U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 260U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 806U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseASalts = {
    {
        {
            0x54CE2752A41881A2ULL, 0x92452240C2B7790BULL, 0x138C6CC5D06D2314ULL, 0x837C8C7E1A1DD167ULL, 
            0xB73956A699239BFBULL, 0xFE5F9F9EAF34A907ULL, 0x3B14A968E2D645C4ULL, 0x874893D7C96B004EULL, 
            0xDEC307D680EA379BULL, 0x7F4E17D30812E22AULL, 0x60390FEA71969567ULL, 0xC50214E16F1404F0ULL, 
            0xC73BF12F7B2CCBB8ULL, 0xA083B86132DE714FULL, 0x0BDA65DA3BB9942AULL, 0xCA0742268D97369BULL, 
            0xB334C376F97E77B1ULL, 0x3D9F17B93E65F939ULL, 0x8446FD6F90608A26ULL, 0x7B8FF22E3F1810E3ULL, 
            0x187D6E264047BCBAULL, 0x2D6C50A3E0CDF5EFULL, 0x7CA5EAD8BF415002ULL, 0x20B5C51FAB456778ULL, 
            0x90A5740B484081BBULL, 0xC6C75ACD09FB5ABFULL, 0x7C1EACB1756EB22FULL, 0xD18CBBBF15990457ULL, 
            0x5274E78FAFEE8FBBULL, 0xF3BC0491B89BFF54ULL, 0xBDEF90208FE9F5FCULL, 0x0CB7C1DC5EC876DDULL
        },
        {
            0x8507B00442AF2E3BULL, 0xD6131FCA822C046BULL, 0x6146E152C49D6B5FULL, 0x66629E7A6244D737ULL, 
            0x25ECCD25316502B2ULL, 0xE6FB844602788BE9ULL, 0x9BC7B8CE5D736BD6ULL, 0x906AAE598F51BBA0ULL, 
            0xC0D8FCF64BB4CCD2ULL, 0x638892B050311957ULL, 0xB9FB779D573C9F9BULL, 0x6B1F803C11BA0E21ULL, 
            0x4545C302AF332C8CULL, 0xF2E3AFEDAC1370F4ULL, 0x2D667D7C09A0F817ULL, 0xFDC0F302B3326CBBULL, 
            0x3D306814F300F561ULL, 0x6B726C753E05F804ULL, 0x97B53D1DFFA22B47ULL, 0xF4A8E56E368D45F2ULL, 
            0x51CE84566D9ADACAULL, 0x83EE6279FA0CD129ULL, 0xCEDEB03FF2C33970ULL, 0x7154ACB2DB91E861ULL, 
            0x475B4D04E93F7753ULL, 0x68273AD620AF1CF6ULL, 0xCD6A45C4E6435FAFULL, 0x7E69B218D1DD84A8ULL, 
            0x914A23C31AD793C2ULL, 0x290D9B1A91665CE7ULL, 0xDF41E7D81B1ACA2EULL, 0xE108170ED7BC28C5ULL
        },
        {
            0x5BF59896694D7539ULL, 0x41606FB007108563ULL, 0xDBB5775D8C2331A7ULL, 0xEA4D7C07642E1DF6ULL, 
            0xE433A7B0407457C2ULL, 0x3EC8247E7058885FULL, 0xE0B286670501AA8FULL, 0x2F2C18735E04141FULL, 
            0xD3E1A120D9CCA49EULL, 0x880992941F23BDF5ULL, 0x381D2FC6ADE6DA78ULL, 0x5F798889A5EE9EA6ULL, 
            0x9AFD7BDF0FA7ED97ULL, 0x03D3C2CDC09470D1ULL, 0xDB3110EFE91442D1ULL, 0xB3C541C164720737ULL, 
            0xFAED8662944C429BULL, 0x9814ABB86337AC12ULL, 0x6CEB680C0E42ECB1ULL, 0x6F6DFF86022EF139ULL, 
            0x14C92E8503B0EA25ULL, 0x2D21299009331C96ULL, 0xE5A1121D9D008CE7ULL, 0xB17433BD278F38B0ULL, 
            0xEAEEABDF08C23025ULL, 0x6A6082E554A15B8CULL, 0x2B7795A3182F44B8ULL, 0x39C46DD856983E31ULL, 
            0x09D607FABDB3CBFDULL, 0x130CABB957E6D4E2ULL, 0x69D9C0888B7F04F9ULL, 0xA85E2D437BBA1B2DULL
        },
        {
            0x7512A233D7C2AB6FULL, 0x1C1A04F5BA0CAB3BULL, 0xAA8545BDB8C255E6ULL, 0xC811EC24698F5EB3ULL, 
            0x6224A4122B3AAF0FULL, 0xE5BE29BCAF0B0BD2ULL, 0x4A092D969A5669C8ULL, 0x7D3BB5874B35899BULL, 
            0xB87661D96409E718ULL, 0x68001762235BC1E5ULL, 0x295AB6BD2B205375ULL, 0x00CD88C015452F89ULL, 
            0x716BE20F60994A20ULL, 0xC79F4CD138937E2AULL, 0x8E2443A8F0C98B37ULL, 0x2B45BD9B356335F5ULL, 
            0x760FA5C2E8558D9AULL, 0xD3E5D3344AC2F5A1ULL, 0x865ADF61C9F41265ULL, 0xE8FED35FAF6B1BE8ULL, 
            0xD3DDAEDA1413496CULL, 0x7CFBD91421594720ULL, 0x841783F3CEB8A4A7ULL, 0x00F33A02AE596C75ULL, 
            0x21C7D83E912B6B31ULL, 0x7DA1F6295BCFD7A3ULL, 0x47FBC057E5CC69CBULL, 0x339F4F8127C4E1DDULL, 
            0xDB38C2470D53D39DULL, 0xDB76AA8025EC3B21ULL, 0xFC922A598DF30070ULL, 0x0E7414A6A9EF6673ULL
        },
        {
            0xE20E14E5F3B9CD12ULL, 0x984B130552C23432ULL, 0x6232DFBA09599E87ULL, 0x30A723922C16A024ULL, 
            0x183EF2CA6121916CULL, 0x87803B7CB1337ED8ULL, 0x7F7A06A8931E9E97ULL, 0x6A6CF3E5A46CC5EFULL, 
            0x081D7602ABFCF5C4ULL, 0x641C8AB2E02D3149ULL, 0xE7F3AAA41B749D50ULL, 0xF92910C95F500DCAULL, 
            0x59CDED74197AA9FDULL, 0x70F2B969AC462CA3ULL, 0xA674F5309BCF768CULL, 0x789E1119544E2F34ULL, 
            0x0A436958FD4AA46EULL, 0xA5C848E8186D40ADULL, 0x8C9930943670AB47ULL, 0xFC3E7285B3400E04ULL, 
            0x873DDAAF63BBD53EULL, 0x6B85965FF1297A1AULL, 0x80228CB866683A66ULL, 0x831095EFFBD0AD4FULL, 
            0x61E1B1723BC31D1FULL, 0x91D6E0E5DED5A096ULL, 0xC26B5357656A8ED8ULL, 0xC139D2D7106CAA43ULL, 
            0xCE46B612FF835939ULL, 0x443A1195EC7A960AULL, 0x9053FF06C2F19471ULL, 0xC9CD6AC8A5AB06D9ULL
        },
        {
            0x4B422C64623014F1ULL, 0xC6F90F8C51C2BD0DULL, 0xB25B818F41F3B748ULL, 0x38655C3BB8FB0366ULL, 
            0x57AB5A90128BD7BFULL, 0xBAB7C5A5FD311BADULL, 0x2B9878C13C3DA435ULL, 0x8E7B8D60740804CBULL, 
            0x3952D3F9E8454F62ULL, 0x8E2C5ACD56A5F307ULL, 0xDCADCE6400C1B475ULL, 0x386162AE1E8C9D66ULL, 
            0x1CE61828251F6B5EULL, 0xDD6A28312D30D952ULL, 0xB2F6C2C6993E2F60ULL, 0x82A8F1FF3209ACCFULL, 
            0xACDA97F12691E1D1ULL, 0xED8247EA1026F8B3ULL, 0x9102FFC08A6EC338ULL, 0xA487870B26EB05A8ULL, 
            0x671846D10FEC638BULL, 0xF2A4E1F224AA1566ULL, 0xBADE2B7248F8D9BDULL, 0x51FFC37269DD6178ULL, 
            0xA08951C133BA4294ULL, 0x8499228E8A90F5BCULL, 0xDEE5A71FB5C0B221ULL, 0x202FECD7C49A67A2ULL, 
            0xA13E731C3E794460ULL, 0xDBB6076562F18D28ULL, 0x6F3E922807861F39ULL, 0x270EEAFEA5F98245ULL
        }
    },
    {
        {
            0x8E383696BC999A04ULL, 0x59AC97C5C07839B7ULL, 0x03BC58352F2512ABULL, 0x68ED1C2BBBDC3317ULL, 
            0x647C2FC26AB2D519ULL, 0xB0C8A0668013BE18ULL, 0x65133AFAA1719620ULL, 0x7C9BE2779496CDCAULL, 
            0x460D8E606711F81DULL, 0x3F2CEFE1E58611EFULL, 0x8302F3D08055D05DULL, 0xBA0B55B2783FB406ULL, 
            0xB315357869FAF6AFULL, 0xB7F64AD36787D898ULL, 0xE5D5F632D7C80B9EULL, 0x32922916D099664CULL, 
            0xA87F23A9D9E37850ULL, 0xE7AEF63DA331A55CULL, 0x397A0C84C352EF0BULL, 0x1DC694A9D9CB7BA8ULL, 
            0x6F8904EF83F4137DULL, 0xB4AC8D0DA8C0CE2AULL, 0x29F7AFA169FD9519ULL, 0xE5C6947212C1696BULL, 
            0x74B733A3737BD353ULL, 0xE40542855440C415ULL, 0xE09CFA73EC2A06C7ULL, 0x05479D18771790ABULL, 
            0x533A4D82A7FEB933ULL, 0xAFAF310B2B1DBF9CULL, 0xCA0F3AFFA659D061ULL, 0x53AABD257F20B5B5ULL
        },
        {
            0x22FE98D17748D660ULL, 0xE37F3CE42E8E7FA8ULL, 0xAA96A29A15FAD4F6ULL, 0xC0AFABDE9E661969ULL, 
            0xBE0AE0CCC9C41C45ULL, 0xD7C6665C687E7C05ULL, 0xC7BB732266DDE3C1ULL, 0xF4477F73D5736802ULL, 
            0x4EB08C8EE6C0B22FULL, 0xF84CC84233548BAEULL, 0x590EFEE672167BABULL, 0x283E0F3B87B856FFULL, 
            0xFB9B72B8394E1209ULL, 0xC99B9379C97C1F2DULL, 0x667B4EBD586EEEE0ULL, 0x9807FE9024851174ULL, 
            0xD5D51D69E3AF945BULL, 0x8FCDD6FE58269782ULL, 0xF1B7732B89B8D1BAULL, 0x953882A58AD0537BULL, 
            0xCB60733B86E6112DULL, 0xAEFF72FB184270E4ULL, 0x19116F1C81F77B58ULL, 0x22E053C2F870CD52ULL, 
            0x616795EA6F256A7AULL, 0xFCC13D04F87F8164ULL, 0xEBF21FDD30004D0FULL, 0x9F4ECBD15DC66EDAULL, 
            0x87DC48CE64A73D7FULL, 0x617817177C76C50EULL, 0x4400F6979A31B63FULL, 0x03A4DAF37E397A39ULL
        },
        {
            0xD0708D4B6AA5D2D1ULL, 0xB5E5283B711DAA2FULL, 0x33AF6138F75229FEULL, 0x81188337C05732F7ULL, 
            0x5796BDF79E750581ULL, 0xC9764AD510B98938ULL, 0x8342910C5E13808CULL, 0x226D71BDAC29CF1CULL, 
            0x2A4E3D94894AEA70ULL, 0x43C38D0F89DEAEFBULL, 0x54C81080FBBEA424ULL, 0xD7E78A6C7CAF9B58ULL, 
            0x3AA56E3BD88B3422ULL, 0x02D0440D26544D2CULL, 0x842F22D3437365AFULL, 0x95A0F34DC1829A68ULL, 
            0x5261FC15854BED80ULL, 0xB43F9B5CEBCD2E53ULL, 0x65C92DB67F351C78ULL, 0xED5E7D227989C2A9ULL, 
            0x99F173EBB41EB0DFULL, 0x0D6E0BCC93D910C6ULL, 0x092D53FE32A12F99ULL, 0x74FF96A204F33134ULL, 
            0x91597F621F4C792AULL, 0xEFBE8A381C0D3094ULL, 0x256277AADB4152EDULL, 0x31C54E873C1A93FEULL, 
            0x295336DBEDE79A40ULL, 0x119653AFB7441702ULL, 0x57A77457C0860E28ULL, 0xD37399264728C07EULL
        },
        {
            0x74AF932B192E4E1BULL, 0x83AE28EC6A6D2608ULL, 0x41DDEF0C311554B7ULL, 0x9064FBA0A4CA89F9ULL, 
            0x5C719A4A6675A2D6ULL, 0x25491C8ADECE1EA7ULL, 0x11C9944D59D39984ULL, 0x221D862451ED1C54ULL, 
            0x5E3DBF408142A743ULL, 0x04184868E11D9352ULL, 0x0462FFC8127D6E87ULL, 0x42E78682EC26909CULL, 
            0xA1D8BF91CB62F453ULL, 0x47E7EE3145E3F5DEULL, 0xB21164A8713AC4F8ULL, 0x6DA2881F9F847284ULL, 
            0x6F14A5EBD828072BULL, 0x29F05C31DDA93BB7ULL, 0x0EF55CE4739F9993ULL, 0xF71252C96E905BB8ULL, 
            0x615A64F7EA3F3873ULL, 0x5B370901B63F8BF9ULL, 0x8A2887F72CA2DA53ULL, 0xC98CCE12757B6579ULL, 
            0x43FFD04A3C7220C4ULL, 0xEE1F1881AFA0144BULL, 0x8817D3DB813A3BF1ULL, 0x95397AA472582AF9ULL, 
            0x45E4B611B5912FEFULL, 0xE8556BBF35FD83FBULL, 0xE51E0C82AD31D261ULL, 0xDBF6628E7D16D0FAULL
        },
        {
            0x62308F0483C0AEC0ULL, 0x2A470A91D4FC01CAULL, 0x49F222177664B190ULL, 0x7D09972662B246D0ULL, 
            0xD9D375E7C3A10C5AULL, 0xFA7BCCDB9D9CC3B4ULL, 0xE68BCA272919B5ABULL, 0x3BF596FEC315B964ULL, 
            0x17905072789C48EEULL, 0xCA18DDEFB836489EULL, 0x20C115FFBBA0A930ULL, 0x352C74F7857740F9ULL, 
            0x8C3A0231D393E6C5ULL, 0x80E21D22D57D026FULL, 0xE428B45C0A44B2FCULL, 0x243CDAAB9EC84050ULL, 
            0xA59E14ABC4A54141ULL, 0x79B0103032E3B0ABULL, 0x4B2AF5E1AA25EA70ULL, 0xAB5E9BA1BF4C02B0ULL, 
            0x8F51722F984C5CCFULL, 0xC5F072D4ACB529AEULL, 0x1B4FC817AD352BD8ULL, 0xAA52D96E19CF2355ULL, 
            0x05D6E9312371EE3FULL, 0xEEBD28D9139EC9EFULL, 0x4C5304E538346F2EULL, 0x8974315D0DE24533ULL, 
            0x85FE4E01FE04952EULL, 0xA632E3E6C247C2F0ULL, 0xC321D3C0E41C432DULL, 0x4DB191EE56E4A750ULL
        },
        {
            0x5095A793A48E3C51ULL, 0xF79E1E4EB86483EEULL, 0xAA34936E00BA4384ULL, 0xB34B63451E57AB31ULL, 
            0x4130F4F0037ED14BULL, 0x5A20A44B504C3563ULL, 0x327D54A42B56ED7EULL, 0x8A252858392A9455ULL, 
            0x264AE325925F8E6DULL, 0x5596A5DE68051543ULL, 0x4525ED62CEC34C14ULL, 0x627676D5731BF0F6ULL, 
            0xCAAC9BB311E39F2CULL, 0xE3826C236BD95BCAULL, 0x2CD941C77170F162ULL, 0x9820B81D174B6773ULL, 
            0xF2791040CBFFC48BULL, 0x430BCDC45802A744ULL, 0xF96838C26C6098D3ULL, 0xB0044D12AEFA55B1ULL, 
            0x5FE2FA62FCD38464ULL, 0x256F1179330DDD94ULL, 0x329D491BE69ECA72ULL, 0x7D5DFCFF854F95B1ULL, 
            0x9149017F2A6C192FULL, 0x15BABEA9D77E11FFULL, 0x35687D1866393714ULL, 0xA4FF88F188B3B885ULL, 
            0x4464935F8EFDA6E3ULL, 0x9F87313E3F44AAE9ULL, 0xBC606AC31406950AULL, 0x3AEA7566A1A75D1EULL
        }
    },
    {
        {
            0x7EB6196EECE2E9F7ULL, 0xF3F31B8A1286195BULL, 0x69C1CCF92E2876B1ULL, 0x10366BA99ABC7CF7ULL, 
            0x316A95B904464ABFULL, 0x74C333B3E6C2BD0FULL, 0x0D881732E5BEB120ULL, 0x913A4383DDEC63A1ULL, 
            0x10769FAC33977D20ULL, 0xE6EBF2E28458D9C6ULL, 0x06D09D7CD2194D8BULL, 0xCFFE9DEE9B5F27FDULL, 
            0x49AEE81A3106762FULL, 0x0CC0620630EABD24ULL, 0x5C25CFE9D0AC62D2ULL, 0x7480A040287D57BFULL, 
            0x1B642CAC6BD8ABA3ULL, 0xF3F1B24CCB49947BULL, 0x06592B7EF0CDA68AULL, 0x35EE7F91AA4382D3ULL, 
            0xB417363C7345B534ULL, 0x9167A6B8DF849A09ULL, 0xD6354823F37A5ACBULL, 0x6D7304A3D7412763ULL, 
            0x77EF1A635093AA5CULL, 0x7C173B5E127EA07BULL, 0x2B3A164289643F96ULL, 0xD9BB896FAB04469FULL, 
            0xD60A11FD6E951487ULL, 0xD3E38DBF425E569EULL, 0x41D9007972201387ULL, 0x8AB3A929D196CB78ULL
        },
        {
            0x8467DC2F2199AE2FULL, 0xF2BB63922D556F1BULL, 0x57A23E8CA6EA43A5ULL, 0xC1519D5A089D5290ULL, 
            0x1162F1B7BD0F794AULL, 0x08EA9C8D71E70B30ULL, 0x481D70A7083DD024ULL, 0x950AA3B9AC12D0C4ULL, 
            0x5268898B998A0E8BULL, 0xE9B43AA7885FC3E3ULL, 0x8E20090947AE5B8EULL, 0xD66F6946A4C442C5ULL, 
            0x92A0DF40358A36A8ULL, 0x00A37FC8939D0BA7ULL, 0xAAC64E257C9130E3ULL, 0x8C555D8BA4EE0CE1ULL, 
            0x33450C0074534B36ULL, 0x2ACBFAE6EDE0F40BULL, 0xC74A15D839D38CF6ULL, 0x5D8ACD4A5A56E19CULL, 
            0xAB2A85CA36282C85ULL, 0x89357E9F740B373DULL, 0x6DA25FACDC92BE7EULL, 0x65257A7181100F15ULL, 
            0x1162FF131964609DULL, 0x95DE5FCBCCF08422ULL, 0xE0732A3431FED586ULL, 0x467970ADAA1EBD83ULL, 
            0x0F25C0786E15AB86ULL, 0xC6D58765337CD9A4ULL, 0x22F40DEA40BBF80AULL, 0xAF321B23CE6B09D6ULL
        },
        {
            0xCA223B821A6839B2ULL, 0x47CBF8F586E75064ULL, 0x990EAA57E3B1C19BULL, 0xC6DEA1DD56066588ULL, 
            0x6622E9CC16015EE9ULL, 0x4535B98CB39A4232ULL, 0x58A62A79CA000100ULL, 0xCAEAEF9390FF360FULL, 
            0xADD8AFAA3DE69095ULL, 0x8F15E0DFB284A5BFULL, 0x9F74C983E9D7533CULL, 0xB58163CED79CF0BFULL, 
            0x281E3B9805F3100EULL, 0x376A9909D9AC4B2FULL, 0x0E45DADAF618978FULL, 0x5AAE3B59E1F3F237ULL, 
            0x670187770B9A9798ULL, 0x1355465A52BD3CCAULL, 0x9D43AB5F8BCD8ED0ULL, 0x81FCB2C02CCB0F00ULL, 
            0x58AF65B91B80B249ULL, 0x07B9FB57F008FFBCULL, 0x0870B961E29D8D85ULL, 0x2A3E002A8A65EFFCULL, 
            0xC5145B05DC5E10E5ULL, 0xF14ACF43C1E39D80ULL, 0x239DF427019BE56AULL, 0x56B419783DBFDF4BULL, 
            0xA6EBABE58330106AULL, 0x2C4E8EE2C70A6ED9ULL, 0xF14369E61600BD67ULL, 0x915E1B417623B812ULL
        },
        {
            0x0972AC49CE76D6B0ULL, 0xC50A1890740355EDULL, 0xA51167540FA0F20BULL, 0xCDEA1DB8A3301848ULL, 
            0xF188CC97ABAB2B55ULL, 0xE2A5232182A5BEC9ULL, 0xCD7F7332ED2E98EDULL, 0xFD10B4546E144B61ULL, 
            0x30D2FDD480F7F6FAULL, 0xBE1BD40581CA57FCULL, 0x4179F6D62317D511ULL, 0x9E6D7A03AD5BBE68ULL, 
            0x7763C9F352A1D8C9ULL, 0x4572C8826F4815B3ULL, 0x71461404279BFAB0ULL, 0xAC708FBA2D897E6CULL, 
            0x6F68ED747C18AD92ULL, 0xA9E287E1EC0B0FF0ULL, 0xD7083BEEC14847D8ULL, 0xC1AFEFE2E6C59860ULL, 
            0xBC39C9A6CB10AC46ULL, 0x12D7E8591E197AA9ULL, 0x6848421E439A4EF5ULL, 0xECD039131EF1243FULL, 
            0x13D1A671A51B9650ULL, 0x8A6F1A82F15F8473ULL, 0x4E6E5EE87DA10674ULL, 0xCE3459A129244799ULL, 
            0x483CE968844E86DBULL, 0x99AB1E5267F77F02ULL, 0xC61B2867EC9BA7E6ULL, 0x205B02FA533D5E6AULL
        },
        {
            0x8C994178F4FBA775ULL, 0x9BEDEFE6B8B97A2DULL, 0xE3E901E962CB9969ULL, 0xAF998F17DCE16E56ULL, 
            0x57734F2543A47924ULL, 0x0365ED82BEC1735DULL, 0xE8BE5B90D2EF0893ULL, 0xED90DC43AE249ACFULL, 
            0x3FE72A64A35F0F84ULL, 0x105A381301B694FDULL, 0x6A9D1230CA64F261ULL, 0x4B903A0A8E3F2FC2ULL, 
            0x34145671C94FBDCDULL, 0x04F4B97868BCCBDFULL, 0xBD58A9E7943D4586ULL, 0xAAB070FF6C34AC60ULL, 
            0xBFC1E7B2FA79D613ULL, 0x5809C2C09C297E0CULL, 0x36CBBC68C47F316EULL, 0xD09C622408EF5E84ULL, 
            0x56C61BD7960B33D4ULL, 0xAF8A6B3476CAAAE3ULL, 0x485C7A60320285DCULL, 0x44023C59912C8248ULL, 
            0xA235AFEE1D6C9E4FULL, 0x91CBEC92B78D21FFULL, 0xEAE4B369D81B6C17ULL, 0x4392F8402D6C85BEULL, 
            0xA7FEEC80A54D91F7ULL, 0x5719496D7B9D5877ULL, 0x861D8FC304E79E52ULL, 0xA9C0B1527B9DCEC9ULL
        },
        {
            0x3C2D753B60560FACULL, 0x9B04B13B60BF8455ULL, 0x36509D04C97D3DB6ULL, 0x7EDBF6FCE12FE226ULL, 
            0x3288BF95D48EAC53ULL, 0x0FFCA7E5CDF58928ULL, 0x6DB40CBD3CE263CEULL, 0x7AC073D9A624FF69ULL, 
            0x5016B3584E82CDCDULL, 0x1CA37AA2393616AEULL, 0x3AA1A6E3F598A59FULL, 0xC4FF4815F09B18BCULL, 
            0x0D73CED9CDE44E04ULL, 0xA4CA23FBD3CE7F7BULL, 0x91DD7C80C092A016ULL, 0xF3869DA96F1E85F7ULL, 
            0xDF946C23BB540481ULL, 0xBED265D2E4EC5DAFULL, 0xCE82564ABE5DF7E5ULL, 0x75A668252CBBF30AULL, 
            0xA5E1EE9B69F0F318ULL, 0xA56CF16CD9839969ULL, 0xFBB6810C1D6A27CBULL, 0x4CC8603F50895890ULL, 
            0x06B3B93F905964EDULL, 0xBCF32FD3B9475223ULL, 0x2C08A9E642F47EA2ULL, 0x4195F69FAFB4E278ULL, 
            0x95593DC14A23DADBULL, 0xFED8108A8BA587C2ULL, 0xB6B94F3039957CA3ULL, 0xA3D01717D1F8D3EAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseAConstants = {
    0x49C1F8C0CCF3D00CULL,
    0xB864812F692EAACFULL,
    0x29F17FAFC3C47430ULL,
    0x49C1F8C0CCF3D00CULL,
    0xB864812F692EAACFULL,
    0x29F17FAFC3C47430ULL,
    0xA125D5B3C692DFEEULL,
    0xCD109C2BC9D59EC9ULL,
    0xCB,
    0x39,
    0xC9,
    0x53,
    0x45,
    0x9A,
    0xD5,
    0x3F
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseBSalts = {
    {
        {
            0x5C33176A216FE7F3ULL, 0x8E8E7B2893F2AAD3ULL, 0x92E6654EDBEFE6D3ULL, 0x7D5413036083F34BULL, 
            0xEDE6D89C15F04CD0ULL, 0x0953888ECA7631C1ULL, 0x55C13A774DE084AFULL, 0x55704A353C95D717ULL, 
            0x0B9584FAE768ACA1ULL, 0x21F49E8112D06150ULL, 0xA1E94590951D404BULL, 0xC6088D9A6C7E5327ULL, 
            0xEDEA9A183C6024BBULL, 0xFE5B0B53E88FB1EEULL, 0xB9A3A611E7E5CA1DULL, 0x5ED536A3641854D5ULL, 
            0x632D9997268C9F36ULL, 0x2899B25D0D91F8F7ULL, 0x629632A06326B4DCULL, 0xE793CDC083AD0495ULL, 
            0x30E0F112E865DB33ULL, 0xCAE30E2480FAB043ULL, 0x6E1D6E1A43BE014BULL, 0xC5952C9860C6AF16ULL, 
            0xDA312351DF6358F2ULL, 0x097419C8EB4EB8E2ULL, 0xB943BBC44ADE0107ULL, 0xD96BE8560EE8F1CEULL, 
            0x0370FE54E1B9541EULL, 0x50C4116018CAC780ULL, 0xBBE88F810BB6B6ABULL, 0xA1792C2482589C26ULL
        },
        {
            0x51895A712519B9E1ULL, 0xF11626F34055343EULL, 0x7329C432A32398FDULL, 0xE28B8A81E2647FB0ULL, 
            0x28BA19035248FEDEULL, 0xDB2582F7D76C1C93ULL, 0xC460757B24A28B12ULL, 0x7B3BA6A1D1648412ULL, 
            0x54EAEF748C7DB117ULL, 0xC0D8611AEB5CBA65ULL, 0xE16AA6C60A21DC5AULL, 0x6B1D20989D8639CDULL, 
            0x1CD8B9148396A6E2ULL, 0x2B28194B0F8BCEC2ULL, 0x5D90C545CAA3BCFEULL, 0xF5E9A97510901378ULL, 
            0x1DB65DF440AD8B9EULL, 0x3B95B2684D4D9D5DULL, 0x9D7B5E1241DC0758ULL, 0x684639039E649F75ULL, 
            0x5909CFD30DF67B46ULL, 0x73D98070C14C54CEULL, 0x4CF71E1E32B50AB0ULL, 0x0AF31871E67D604EULL, 
            0x7DB035C6C8C00B23ULL, 0xFE1EDA5E98F24D3EULL, 0xE3D09F40C128F5C8ULL, 0x2C4D8CDD2DD27537ULL, 
            0xAAB78A0B7B0A7149ULL, 0xF26EC292A97FDC3FULL, 0x7C4D50C9E92DE339ULL, 0x1631E4614EA9E94FULL
        },
        {
            0xED8FE81F06EF4074ULL, 0xE88FB4798AF24842ULL, 0xEF6E373908001FF6ULL, 0xBFFE680181C85155ULL, 
            0x05EC1DC2446F1AB9ULL, 0xAB5B7AD10DD7A7D8ULL, 0x0810B6490195B4C4ULL, 0x7A1DBC437A0FD204ULL, 
            0xF2B2A48EC0A08E55ULL, 0x6CBD85BA640DD41EULL, 0xEEBA0AB539061A03ULL, 0x9F5950680AEDA87DULL, 
            0xB4587F0315879661ULL, 0xC732A8383D0BD919ULL, 0x709A57D7502512DDULL, 0xA78BC69CCBB640C7ULL, 
            0x767F6884ED3BD73DULL, 0x74E5B4DF14E878D7ULL, 0xBC568B0B9559D153ULL, 0x25CB54CFF29590EBULL, 
            0xBFF5FBDDC79523ABULL, 0x00B70B27D6585EF0ULL, 0xB47B780EA12E049AULL, 0x079EAFEBD52EC2D4ULL, 
            0xCF41223B5758D030ULL, 0xFF44D97E139AD5D9ULL, 0x30E4EDF7B280FDD4ULL, 0x0BB292638D5ECB11ULL, 
            0x38A1C7B73DDF2AEDULL, 0x55907124B35A2BAEULL, 0x896B2D8238EA375AULL, 0x50FE8CAC41C877FBULL
        },
        {
            0xD9B44DC69772A047ULL, 0xD1AC79699FB00AD2ULL, 0x36C3317F231313F7ULL, 0xE8F5868DDBE826DFULL, 
            0x77040310F03B7F40ULL, 0xA30EBBF84FD4D571ULL, 0x732AF5BB757316F2ULL, 0x73D4FDAC189881BBULL, 
            0x753C2F908286091EULL, 0x0789208CD4566681ULL, 0x0E0ECD5284AB8871ULL, 0x91094509B3AC95E5ULL, 
            0xC4781E34C1195D84ULL, 0x3153885BB5BC596DULL, 0xFEC4BFE3983A550BULL, 0x635D19D314425799ULL, 
            0x43843596C10FD4F0ULL, 0x910D6990B400FDB2ULL, 0xC25EB409618D2791ULL, 0x8473452126C4AA4EULL, 
            0xDBA7DB923C2319A6ULL, 0x71E74157239A46C5ULL, 0xB4640AF6FC81EF84ULL, 0xA2BEB966341EA558ULL, 
            0x3AAA11EE9A822134ULL, 0x961BE6BACA1E1770ULL, 0xB386F44F4B76E966ULL, 0x7CFF30D99C3F933DULL, 
            0xC8059369E895A694ULL, 0x8C99D65AE60C1CF8ULL, 0x1440D4AF30036C6EULL, 0xFEB35C730A8EE86DULL
        },
        {
            0xD4FE1EE2F923A83FULL, 0xD048223E6204C65AULL, 0x751609F1C8F6ED12ULL, 0x426EF9EFB6D4E60FULL, 
            0x0270C9AE667D10AFULL, 0x89D56472E19689F3ULL, 0x2E095BE7F55C3ECCULL, 0x6A8625B7542706A0ULL, 
            0xC6C052197337EC96ULL, 0x880B02635C4626F4ULL, 0x1213693AA88276D9ULL, 0x2EFA3F4AFA019244ULL, 
            0xF568D3F421B0DCB6ULL, 0x7FB06999343B6222ULL, 0xB1777DCFC7DD81C4ULL, 0x9FD4DFF503A2D5E7ULL, 
            0xA8FC01E055040FE4ULL, 0x6B27C47CA6724E9DULL, 0x6A8EBFDCAEB30B0BULL, 0xF9CD25CD9FB66691ULL, 
            0x173B9B8B23040CC1ULL, 0x056066C0ECDC31E0ULL, 0x604F42E3A10CA070ULL, 0xC8FFC4ACA6354629ULL, 
            0x37AFA68D2738D0EDULL, 0xC229D16CBB306202ULL, 0x3085EA455E87E8A7ULL, 0x307ACC8C93634F21ULL, 
            0xF0B8475AD844F73DULL, 0x0B9BDAE6B97A825BULL, 0x10D859A083A67A02ULL, 0x6F9EADB094F99D67ULL
        },
        {
            0xE90880102D0D6F00ULL, 0x16551A6B438CBCCCULL, 0x7974A0912DD1E14EULL, 0x96CF57718A626CF9ULL, 
            0x60748B3A90A036E4ULL, 0x85C55D497FB16E6DULL, 0xE0798500E754D32FULL, 0x4F658107192D7E41ULL, 
            0x32B5D48D99246FC2ULL, 0x03B1E558B831AD39ULL, 0x4E5A63818F4E8C6EULL, 0xC0B4504FCD47EF72ULL, 
            0x3129518E9FE76880ULL, 0x4D4A19EAEE3DAEB5ULL, 0xA3EBD14166A9BC51ULL, 0x1A9E678ACDE0470FULL, 
            0x7CAD4294C0F47FF7ULL, 0xD75B895E1797703AULL, 0x6FD555ADC42BDEE8ULL, 0x2ADC16F68F4D380AULL, 
            0x009BCB07BFC9AC0FULL, 0xE8C243BFBE559775ULL, 0x3C418E1778908D39ULL, 0xFDD7E044ADB6B03CULL, 
            0xF01E8DE4D19F166DULL, 0xA4A5B104B4C7CC7CULL, 0x8A44D1FD53692543ULL, 0xE2E9F94C40C7CB10ULL, 
            0x4AE1AE62AED78609ULL, 0x2A59C278D62D6089ULL, 0xB571E3CE11ED3C94ULL, 0xC84A02C038112BFFULL
        }
    },
    {
        {
            0xC80BA7B461919AD2ULL, 0x7919543E6F7E698DULL, 0x469143B1E0BF242CULL, 0xDF4534D3DCA5E4EAULL, 
            0x962833A0544302ADULL, 0x15CBE1B356836AD3ULL, 0x85E9AE038A0D49D2ULL, 0x2D96823B099E654CULL, 
            0xF86B46B10D84B715ULL, 0xF5F2B84C6381A638ULL, 0x3B39BB927F7459FDULL, 0x7233A6C05868502BULL, 
            0x6E37988F5006FDE3ULL, 0xCA041BF55AADA178ULL, 0x467747AC333BFFDEULL, 0x0CD988FD17C8F88AULL, 
            0xDB2A1555FBA4D0EDULL, 0x551EDDF21A37143AULL, 0x8E05403444D10BAFULL, 0x34332F0FFB71CC01ULL, 
            0x0FDD0487572F326EULL, 0x08C76D4B30EF2770ULL, 0x93F48811698F1DB6ULL, 0x5475210464B19547ULL, 
            0x64D4B6322DE40C65ULL, 0x2A0EC613D0F35B66ULL, 0xF82446CBA324BA4DULL, 0x6FCB2E5803B6E2E8ULL, 
            0xDF924C041FA1130AULL, 0x259F8165F10D7C61ULL, 0xA1F6FCDC75C02CB9ULL, 0xE85B9FC77A96A33CULL
        },
        {
            0xF77F84EC21F81D3FULL, 0xF2FFC8874EFF1679ULL, 0x8D88A81EC4C887F9ULL, 0xD74E3973961CE652ULL, 
            0x309A68F949D0551DULL, 0x87D42BD21E2F312DULL, 0xE3924C025F394EE6ULL, 0x15C5B4089EB7E8BDULL, 
            0xA21E5B8515FFE1C2ULL, 0x8DC2A880CA6CE8C6ULL, 0x1A617F9A582E54DCULL, 0x72775FFD965F7529ULL, 
            0xFE2FB6A192703FC1ULL, 0xF745593BAD4AD692ULL, 0xD9D4860BE8F04414ULL, 0x14CEA851FCFA4F99ULL, 
            0x0FE5E6FDE32BC365ULL, 0xB191691925D1200EULL, 0x53AB859707A958DDULL, 0x72C954239CB9FFBCULL, 
            0xC8EFA1134974EC8FULL, 0x20E045AB0325F61CULL, 0x1D8C5AADFF6BF79AULL, 0x957E6F45AB0288EFULL, 
            0xC6CE604B7456AADAULL, 0x8B6B4DD0136455B2ULL, 0x1659A634D833D0AAULL, 0xA7B3F127706471CAULL, 
            0x367ED23E98F89FE3ULL, 0x4F2AF4F469A9C967ULL, 0xB4961FC4D7C86B3EULL, 0xA2700C3EE36963B8ULL
        },
        {
            0x3FCC9367B04C210FULL, 0xE121FC7BB46465CBULL, 0x6A5753A63C73144DULL, 0x306E4F26ACC181BCULL, 
            0x8E9CF0C81BCFB0CCULL, 0x337B940385C92CA9ULL, 0xE100DB3EDCF37A46ULL, 0xC1DF9C0820E1F498ULL, 
            0xC6E271655258CB59ULL, 0x4222038EB0FFCEA0ULL, 0x996B3FDC529D6C79ULL, 0x1460B37258D472BAULL, 
            0x837FEE4CFC526483ULL, 0x4A5BE23CA48D974DULL, 0xD8A41368851FA39AULL, 0xCD4A2F07DCC705B1ULL, 
            0x6419B429578C039BULL, 0x84ED0E555758DF50ULL, 0x6F9D01EECF078E57ULL, 0x140268F73B1C09EFULL, 
            0x1FBAE840597260E9ULL, 0xF5E15C4182998FB5ULL, 0xFF5521E243338DB1ULL, 0xA1E7D52883A8BF7CULL, 
            0x95194C4325679D86ULL, 0xA9D47028573F7937ULL, 0x860903D8DD6F14BBULL, 0x7493604F94947521ULL, 
            0x5DD83DECF771BBABULL, 0xEE3B00BA18A22D0AULL, 0x0333E303447A05AEULL, 0xFBAD9A0ED396B089ULL
        },
        {
            0x98753CA847A9A113ULL, 0xEF8EEF718F11389EULL, 0x15F5D76BC1815B33ULL, 0xCBA6EC617C751C91ULL, 
            0x57179ED8DE69A8D2ULL, 0x172527F3C6001843ULL, 0xD320AD0ADC4BF9A6ULL, 0x9199E632DCB62928ULL, 
            0x092C3CA7439CF35AULL, 0x6E12792C837E0F19ULL, 0xF93B9AD1B526EB30ULL, 0x1557B1B4EE3391BAULL, 
            0x386EE7E7B4E17642ULL, 0x35EF6E546A5CE4D5ULL, 0x263DBC02455EC14DULL, 0x4163EDD22A25F702ULL, 
            0x30A802FDE7320229ULL, 0x2B070E492FE4ADFEULL, 0x511C57F3639EED78ULL, 0xE4900F3A208A1411ULL, 
            0xC1C5B1802746E60FULL, 0x026AFF0D125B2C66ULL, 0x5BD402981D05947DULL, 0x53A939797E880979ULL, 
            0xB0F96BAD0679AAD8ULL, 0xBE728F82A0ACA27BULL, 0x285F5B8EBD9D8F25ULL, 0x5216F9525F29CD42ULL, 
            0x843EA3B24C5AF0A1ULL, 0xF0BC3C3C7142615CULL, 0x6965DE596164E3C3ULL, 0xE3DBF6DC2E62E1FCULL
        },
        {
            0xEC38ADA5F737CE92ULL, 0xA967173CDBD9BE5DULL, 0xFA2B4B711A604CA3ULL, 0x7BAAFBEFABA644C9ULL, 
            0x00018A60AB0960DAULL, 0xE754193AD3E65964ULL, 0xA7DF6ED6B9684CAFULL, 0xF549E609EE3A958BULL, 
            0x672A233DA11330C6ULL, 0x4A20CF8AE20DB25CULL, 0x8A183C64ED25DB33ULL, 0x548F3380B56CA64FULL, 
            0x972819D5855072D2ULL, 0x106845B81909444BULL, 0x0ECA9206EB5310ECULL, 0xBEEE8D2843A69384ULL, 
            0xBBFA65D23877E239ULL, 0xF7123DE54F3DF30DULL, 0x84129EA973DF412BULL, 0x9F1C2C045A4D1053ULL, 
            0x1F14F8171AAEB983ULL, 0xB05D78B88629ACE3ULL, 0x46ADC8CCC24C032AULL, 0x27A1446D67E4AC7BULL, 
            0xD43FAABA920042F7ULL, 0xED2F91F0A1EBBBD2ULL, 0x3AC7186DF3E219E3ULL, 0xF45E31D3E6DB9AA9ULL, 
            0x5BF4EF20ECC3070CULL, 0x61266DEF4D15D6B2ULL, 0x206D0E22ABA2A71CULL, 0x236D12B9E7F67FBAULL
        },
        {
            0x3FA8A0DC2E566F2CULL, 0x3775943DCEA1E56EULL, 0x57D6B67FBE343316ULL, 0x9348410801992B45ULL, 
            0x7E1102576FFD3B11ULL, 0x0078CB5786BD427EULL, 0x81106B2D16FB22F2ULL, 0x91337A6A72101031ULL, 
            0x18AA744F35CCF9B4ULL, 0xAD06668E1F043B68ULL, 0x4952691860F21433ULL, 0x315940FACFFDDB73ULL, 
            0x445049BE28233FC1ULL, 0xB44B8E0B4AFB2AC6ULL, 0x34AD6A218CF418A6ULL, 0x430D151635BB44C4ULL, 
            0x59BBDF5E0FB934B9ULL, 0x5D1832B4573A7AD0ULL, 0x5AAFE9C1D53EBF2EULL, 0x5E644B1ACA0FD70BULL, 
            0x25B950EC70375487ULL, 0xB057577474F2ABA4ULL, 0xFA7D88AAA79B5254ULL, 0x3AA50C061C20CA4CULL, 
            0x57FDD74B7493F16EULL, 0x0C0D9592B112974AULL, 0x8A3B452107FC7118ULL, 0xF98651C0355BE82EULL, 
            0x5C39E691CE9190BAULL, 0xC7D8B26932AD1F4DULL, 0x00D41660E02B3EFDULL, 0x2DF846D8A0F54DE7ULL
        }
    },
    {
        {
            0x97300510468C1FB7ULL, 0x50D60DF9144B7C8BULL, 0x08D46772350B5E8BULL, 0xD93D560849A93754ULL, 
            0xE11DEEE38B0CB1CEULL, 0x6B95CFA0F385E9FBULL, 0x1BFC38697B1570DFULL, 0x3D25AB36928F699AULL, 
            0x12E8DC153BAC345DULL, 0xF901381AE2C072C7ULL, 0xE1C071EFFDE38822ULL, 0x6250E1A2F885C16FULL, 
            0x4DE01A151E99095EULL, 0xBF589A8E6EC9B7EEULL, 0xD366820C98B35FEEULL, 0x4947FE6AB2A32D99ULL, 
            0xE00D01DD5DF6CD90ULL, 0xFBFA85E32D8DEE9AULL, 0x14ECB745B6B4825AULL, 0x1577829C532AA87CULL, 
            0x12ABEE2F9DDE3D44ULL, 0x9A5D19BD50B2B54AULL, 0xDF2EA13D57D52B73ULL, 0xFD3662148DB814F2ULL, 
            0xAC8726466E4A037CULL, 0x55C0186628879D78ULL, 0xB61B9A7F1C3838D3ULL, 0x77491346572ED5FBULL, 
            0x54FAC50871B7C756ULL, 0x68FDB3F841AEABF7ULL, 0x9623E343B485C88DULL, 0x7CA868829F909D44ULL
        },
        {
            0xE9D40C59C706A9B1ULL, 0x29DF381F5451577CULL, 0x7193ECD76A666D38ULL, 0x69806D7FDD7584C9ULL, 
            0xF33743E5E7098E47ULL, 0x7E001CB75B4EF0D0ULL, 0xCA4A78F9348761A2ULL, 0xADC76F352DE67896ULL, 
            0x39679B7EC9241B3CULL, 0x368A5E05B60A559DULL, 0x1C27F32599CC6E92ULL, 0x83E1211D63AA9EB3ULL, 
            0xA17F18C6754051D0ULL, 0x3AE4F05E6DE4D64EULL, 0x753F6F8BD481A772ULL, 0x7CCB01E8859CDAA7ULL, 
            0x7D699C57F631BF50ULL, 0xC0281C3FA5E5D56EULL, 0xD2167A24CA916944ULL, 0xC4C74EBF0D890E74ULL, 
            0x5CFD628E8DA10CDEULL, 0x0B3B8595827D87B4ULL, 0x7B79DD83163D2903ULL, 0x49C9C1BF5E13CEACULL, 
            0x86B56A5DE75A2491ULL, 0x5A4FF4AA0D4E49D2ULL, 0x3D19F088EE552045ULL, 0x13F7FDF252FCB511ULL, 
            0xE317E0CF197B4B98ULL, 0x57C4C92039C65922ULL, 0x693BEEBA88478EC8ULL, 0x959A6BF31D931019ULL
        },
        {
            0x9F249B7B72D88C96ULL, 0xCF1BF7798F991232ULL, 0x458CF3105C896D5AULL, 0xDB822713404B653BULL, 
            0x9D60FDA939FA1AF1ULL, 0x74F56968FE9DE511ULL, 0xAD7708474741D466ULL, 0xD0FCF9FFBA38BCFEULL, 
            0x40C88337166828E9ULL, 0x86D76D7DC7012059ULL, 0x3CAB81786BC16D93ULL, 0xD2B2C05E302BF0A2ULL, 
            0x9D9FB41F892B8621ULL, 0x744B9F1FF2503228ULL, 0xA528702081A381BFULL, 0x073B02BB4750160CULL, 
            0xEB54AFC0ECF93331ULL, 0x99CC995F543B822BULL, 0x220C769A69B084E3ULL, 0xD474D0453CDDBE77ULL, 
            0x613FFCF6A6871FFFULL, 0xE25C2651818CA6E5ULL, 0xBC9DEF0F9E868D99ULL, 0xB23DBED59B71B036ULL, 
            0xA768F6EC3F0BB553ULL, 0xA9778D92281A4F40ULL, 0x4A0875BE08E56C4BULL, 0xFCB9944F24406AD4ULL, 
            0x560E3CCC4B4BBEA4ULL, 0x1045AAEFF5742661ULL, 0xD13D11B48FDD8B01ULL, 0xD9BC73F9A69DCEDCULL
        },
        {
            0x942CC942A16E0DFAULL, 0xEE44BD5B96963672ULL, 0xFC56ECA19CC5C020ULL, 0xE4DBE76902623D36ULL, 
            0x15EA102755D8E9F4ULL, 0xD98FAB7CD5E2F93AULL, 0x14A6F8EF99D267FAULL, 0x28B29215EA285012ULL, 
            0x2FB1AB56A8E2DE2DULL, 0xC36BDC65E471F113ULL, 0xA1E5C00DC5271D18ULL, 0xEF75D00A50EE00BDULL, 
            0x043B6DC3AE90C7A5ULL, 0x152F59E3678E218EULL, 0x7FAAC3F70B34129DULL, 0x25DD4A1EB84A649DULL, 
            0x5B57A40E207398B3ULL, 0xE61DF825F1B12610ULL, 0x579D46BA2BF39821ULL, 0xAE8F53913D07A890ULL, 
            0xC56BB3481FC955C7ULL, 0xBCB807D6A1FE2979ULL, 0xA5FB4C471C52E232ULL, 0xBCC9073D6BA9744BULL, 
            0x4B2E14438A091AD3ULL, 0x06A851BFBC6FD6A9ULL, 0x15FF1A20B9715B69ULL, 0xF96C45CE45DAF755ULL, 
            0x1B284B3342526128ULL, 0x5887E9F6CFBF49EDULL, 0x525906B05FB93979ULL, 0xB7CAE7D8292C0EFEULL
        },
        {
            0xAA838C92635BAD14ULL, 0x55C199690CE4B656ULL, 0x14E4BC2A7C06D3B9ULL, 0xEC7025073907179FULL, 
            0xBBD27D7E231CC58BULL, 0xD97281553D5FCB5CULL, 0xA7D3EC69B48CEC12ULL, 0x5760274C45073B50ULL, 
            0x479ABDBDF6BD9103ULL, 0x6590D5C6BBE42D8BULL, 0xAD1349B2D9DA1CB9ULL, 0x61E6976709E8FB00ULL, 
            0xBA497A551AF56954ULL, 0x238FF15C0B91DF50ULL, 0xDECDFA16C4ADD339ULL, 0x00E4A30BEAB60EAAULL, 
            0xE6DD21B3AC0103F6ULL, 0x9365C325FDEE2873ULL, 0x97F309D4AD172702ULL, 0xAB316E74B4B3868BULL, 
            0xAB5BC8548CF9DE0CULL, 0x65A13AA1817A04C7ULL, 0xD206E2D6CA4F0F10ULL, 0x6D414E0CFC6C798EULL, 
            0x2C9B4F2A53EAFB38ULL, 0x426CB80C74C26361ULL, 0x934B7A7E64221F92ULL, 0x67A44DB38DFAD3B5ULL, 
            0x645ADA3BB89275BDULL, 0x9C592F515E95BB8CULL, 0x05AAB435E6F9BFC1ULL, 0x35346795B9B969ADULL
        },
        {
            0x97525A9954678295ULL, 0xACD0243A492A1F32ULL, 0xF0B056A441CD2034ULL, 0xD647B622149D28F8ULL, 
            0x0B397C51ADAD1010ULL, 0x45AAB11C138AA287ULL, 0x070A68684EE8696AULL, 0x2C5CB0C6399E1DC6ULL, 
            0xE17EC038056C747BULL, 0x29B91356F4B9DA5BULL, 0x113CF8FF3D548B7BULL, 0x70806F716374B1C3ULL, 
            0x0691D31773D37E30ULL, 0xDB3041ADBC05814FULL, 0x64F4383FB844467DULL, 0x05323D478E0CAB11ULL, 
            0x5D37F660DC1763DAULL, 0xD5C8FD2BCA4C9DD7ULL, 0x6F8D3E1C8CDDEEE7ULL, 0x4BBF55927FDC2918ULL, 
            0x63AE8D0224CB9B52ULL, 0x1FC64DC613D42C91ULL, 0x8BD60865A23C0714ULL, 0xFC6752B8BF43332DULL, 
            0x3802AEF7B2A1733BULL, 0x8A18C635AC3F5149ULL, 0x6F552563064A5A1CULL, 0x24DE72CB235CB641ULL, 
            0x22222DC59B11AE47ULL, 0x920F1D18D791A7B4ULL, 0x616E8C8806EE0988ULL, 0xFA1C641A966B7641ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseBConstants = {
    0xB65D724F293C19F9ULL,
    0x95E4F095B0FD4E93ULL,
    0x7713137189BE1A49ULL,
    0xB65D724F293C19F9ULL,
    0x95E4F095B0FD4E93ULL,
    0x7713137189BE1A49ULL,
    0xFFE4ACD9BF314ECBULL,
    0xC114C1B96DC4A0DBULL,
    0x7B,
    0x71,
    0xFD,
    0x62,
    0xBA,
    0x98,
    0x20,
    0x6A
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseCSalts = {
    {
        {
            0x356DD229B063E85FULL, 0x02391982774EB36DULL, 0x5EA2B17816A02F49ULL, 0x28F15EEB1CEE47DBULL, 
            0xF63D677A7B729FD4ULL, 0xF01AFC8388FF9EC3ULL, 0x0DFA20412F617E9CULL, 0x68F12F7CFF17115AULL, 
            0x26E084D5C74CB72BULL, 0x5269BD58ADB16232ULL, 0xBF0E455BC7C818E3ULL, 0xA06A439B4AE1C409ULL, 
            0x1695B289321DA1FCULL, 0x462D6C35E7180049ULL, 0xC65B321D5E9A2B5AULL, 0x4CCB15DB3C89D75CULL, 
            0x5B9617F345CB0E1CULL, 0x2DF90AF9FF97D686ULL, 0xA08E4D3683203D53ULL, 0x2C0F948418DA6D30ULL, 
            0x34E77D68B7180707ULL, 0x708E39898E7EC380ULL, 0xA5CFD17D3A6A4305ULL, 0xD989D3C38B2E513EULL, 
            0x6FF76441B8F7F7F6ULL, 0xC7FDAE6DA355C549ULL, 0xA95F0C5978A8BADDULL, 0x3C4C4D0526344084ULL, 
            0x0350F9B81FFAE1E8ULL, 0xC7251083742E03EEULL, 0x352CB921C1A76D37ULL, 0x80F04B299194A1DFULL
        },
        {
            0x51D9822F11093CC4ULL, 0x8C8EDDCACE0D3733ULL, 0xAA6E1F10AD21B321ULL, 0xA776BE9169FBD9FBULL, 
            0x54B1FE96234F68BDULL, 0x5B287BFE370D967BULL, 0xD6C299D6B1EFF0D8ULL, 0x2B9B88327A594B3CULL, 
            0xB33250452D8BDEB5ULL, 0x181A13DDFD662842ULL, 0xFCB4E6739E9F46B9ULL, 0x3A70E6BEA8ACB4C5ULL, 
            0x9F64018C17638A2AULL, 0x956362445934DE94ULL, 0xC4C9F3BB68339B27ULL, 0x8FB5D9FFE165FE5AULL, 
            0xE1B07ADD819173A6ULL, 0x81AAC8407994FA5DULL, 0x0AE7EB0AC081124EULL, 0xE9B53ED209D863DEULL, 
            0x28133E275590C32CULL, 0xB0C866A7D9E87B93ULL, 0x0F6207C09096183BULL, 0x3C14AF7BCB56B84FULL, 
            0xA8DC00C84BA45737ULL, 0x2FA62C527B1E8789ULL, 0xED66C4433279660EULL, 0x7FF4E7B213D45316ULL, 
            0x4DA6DD3BCB91DC89ULL, 0xFCC6852F8EE4AF8CULL, 0x306E3C685CF245F7ULL, 0x32B1109A08725EE7ULL
        },
        {
            0x2C087AEB916F76A3ULL, 0x6B7EFD4BA7E30950ULL, 0x5C9E1D1EE4F9ABECULL, 0x4685F2BC58C5C17FULL, 
            0xBBFB90BFDCC6A3B2ULL, 0x28BF5A484B487429ULL, 0x60E5B8A9BDCC37D3ULL, 0xC4883528053B5A96ULL, 
            0x545BD6CDE2ED0021ULL, 0x6BA848279681A439ULL, 0x4E10CDFA33296706ULL, 0x8AFBC5BFB590B9AFULL, 
            0x13B9E8F7EA8CD14DULL, 0x3DD8D083F6420267ULL, 0x30635F73599BABB6ULL, 0x595C95A20EDFE2BBULL, 
            0x670304A9585DF252ULL, 0x3924F8898C6B41F4ULL, 0xB39D4F7FCFEB3EAFULL, 0x5072CFBEDAB52982ULL, 
            0xEDC5C9DFF8663E70ULL, 0xE76B31F2BAF0FA36ULL, 0x4619E2F986D30A5FULL, 0x52E73BB05569CBA7ULL, 
            0x3BFE80270C8B893DULL, 0x8EA5A634B95ACA59ULL, 0x275A31454633DE19ULL, 0x9DFD5C96B00D0D95ULL, 
            0xE270DFC9DA221A65ULL, 0x63CBD5CA0148EC4FULL, 0x131053AAB2D643E0ULL, 0xD966D58C88BC372DULL
        },
        {
            0xC2D68362B46551D9ULL, 0x706570BD59C7D9C3ULL, 0x1080B3160BC65257ULL, 0x2CA1B590895AB4F1ULL, 
            0x0820AF0724BD357CULL, 0x19B8FF111D14B9D1ULL, 0x46B488D0280B9CC6ULL, 0x5DD5DCCC5E2BA378ULL, 
            0x0E4477EDF0F87C3EULL, 0x960FF4F74C4224B7ULL, 0xB358A0602E240488ULL, 0x5FFCAD0438456A05ULL, 
            0x0C8C28483F67A039ULL, 0x94EE8C1BA5F7E270ULL, 0xF838CC8DA8850DF6ULL, 0xC57D3686061F63A0ULL, 
            0xCAA20F50538D05F3ULL, 0xC68A51229FC7F648ULL, 0x6172D97E5D3A2C91ULL, 0xE05ABEF56A0DB94DULL, 
            0xF5C660D31D1DE7DFULL, 0x5ED2528BAB726704ULL, 0x4CEA6F86F9115318ULL, 0x432EC2569C57797BULL, 
            0x7E16D97C1A570E96ULL, 0x14703F77B6ABD7C9ULL, 0x6BCFB766184ECA60ULL, 0xD4FBE27491DC6CBCULL, 
            0x5F13654E48F1ED6EULL, 0x307F1347BEF3E7B3ULL, 0xB349355F4F131B86ULL, 0x494F234424093711ULL
        },
        {
            0x34E8234F691371E4ULL, 0x0C93B1118BEB672BULL, 0x2C3FDFE42DA5BFD4ULL, 0xB0E691EC65ACE5B6ULL, 
            0x3BD45C9061E70967ULL, 0xA5EB23D26CCABD87ULL, 0xF4BE8B01451732DBULL, 0x8E54AB1D307A577BULL, 
            0x4985680E82C0D60BULL, 0x1E8F185B77A98266ULL, 0x817144D5D52BF999ULL, 0xAD97E290D118C2EDULL, 
            0x0E4092399C26C6ADULL, 0x73AF41534AC9B7B1ULL, 0xBCC93F1DC1600F63ULL, 0xFC633B5866048C72ULL, 
            0x7E5C50D83A6F1829ULL, 0x1EB5CD7462D90F21ULL, 0xBEBF4CB2E2FC9185ULL, 0x8FD0814B7C9B7E11ULL, 
            0x73BE39735ECE0D39ULL, 0xB95BEB2E163B14F5ULL, 0xC7CD7ABDCD90A3E9ULL, 0x5803ED7C43D0F80EULL, 
            0x633507A6030FB2ABULL, 0xC59C3D64F9CC1257ULL, 0xD15E1FBFB400E688ULL, 0x1891CAF66C73D358ULL, 
            0x4887ED997DD23285ULL, 0xB75ADCF45E58F6B5ULL, 0x44A1F3497202A41FULL, 0x1D814B5BFF7E73C3ULL
        },
        {
            0xEDA8101C51165142ULL, 0x680AA8969282F886ULL, 0x5F7F4AD01E0A5E1BULL, 0x2990219F10D57A21ULL, 
            0x20828E6A71124CFAULL, 0xBC2AC4C22C8095B2ULL, 0x1DA7A3CD3143B084ULL, 0x68A55A9413C31979ULL, 
            0xB3A2882EF3F2257AULL, 0xDFBF099A0C9054BBULL, 0xD6B4A5AAC7F06705ULL, 0x0AE7508560134EB7ULL, 
            0x674C60BABB786D71ULL, 0xAA5065BCF8BD8E92ULL, 0xED557A0BC8CFA3F6ULL, 0x944F5956E548875CULL, 
            0x227ED63C33FE022AULL, 0x2C9F2D2E2B07B45EULL, 0x7EFBAD40C1B5511CULL, 0x80D7B1CE529DE137ULL, 
            0x8638A66684DE6690ULL, 0xA496D43CA90EFB86ULL, 0xFB8D3928771CAD58ULL, 0x1A8B49C74461C7ECULL, 
            0x5F84197722FF287AULL, 0x1CBC3D5C033D3049ULL, 0x42D8B9D439BCEB3CULL, 0x50F461A0644D3E7DULL, 
            0x6048C19486754D91ULL, 0x6E820C4E93B315CCULL, 0xEC28C8BA99BABBAAULL, 0x79F943D5049BEE7EULL
        }
    },
    {
        {
            0x2FD245B9D81595D8ULL, 0x132AA81738FB8A0CULL, 0x47B7F925A1910055ULL, 0x0BB149051FFA7103ULL, 
            0x6B5A4F0C39C59B9DULL, 0x0A3A3BD3918A0512ULL, 0xC4E48F1D8EFC61AAULL, 0x9DEFC4937E3D4A88ULL, 
            0xE6FBCC77ADEAB463ULL, 0xB26135B220C0B636ULL, 0xB47861A211D2E6DFULL, 0x2E90BC098E0D44FDULL, 
            0xF955BE2A3B9A9672ULL, 0x8E827CC4483448D9ULL, 0x67FB13950EA81D16ULL, 0x637DFD4988492567ULL, 
            0x3347DDF71CF44EB4ULL, 0x0632B59215AC9F19ULL, 0x55A545F3DCE7DD00ULL, 0x3F2A373BAD81CFA4ULL, 
            0xBE5838D75914CE98ULL, 0x72ABDC644DC8E3A3ULL, 0x1F711C9626B72F8EULL, 0x2DB2ABC0582DC28BULL, 
            0x22189746473B0DB7ULL, 0xDA872D76E51665A5ULL, 0xD196AA649B34A118ULL, 0xEE317F271B3F9DCCULL, 
            0xBBC5CF8D78E94119ULL, 0xAD847ECD18954768ULL, 0xC62CC44F28A5E48AULL, 0x39ADE89A153CE5D3ULL
        },
        {
            0xC5E7C1B85D1A51DEULL, 0xC160D3445163E7F8ULL, 0xDD5BDFDCEF1AE413ULL, 0x4FA8DD98BD951B1EULL, 
            0x3378FBEE1ECC5305ULL, 0xBE498D07E28681EEULL, 0x97581286BBB51A68ULL, 0x001A4F94BB270BDAULL, 
            0xA2747830B4AD6900ULL, 0x37AE037C5EA6CDB2ULL, 0x8FF2A99995BBE931ULL, 0xEFB5FF0516BC1840ULL, 
            0x3F5E9C0EEA8C90B8ULL, 0xA8427B1611B473DBULL, 0xC45E5A52377EC5E4ULL, 0xFAF370F769318DA4ULL, 
            0x0C7B94ED236C23AEULL, 0xF7106124B928656BULL, 0x8088777C765BA14FULL, 0x3C4488F8D9C11796ULL, 
            0x682BB124C1483A73ULL, 0xF34632C508C4FAB2ULL, 0x51295CFAEFA95983ULL, 0xB087B6895C54D7BEULL, 
            0x2D549268655522E2ULL, 0xB142190869EF69A3ULL, 0x8F46D0118F05A229ULL, 0x4F6921ACB7E0085CULL, 
            0x5CD6E3EE18F0E62AULL, 0x553742B02ACB91E5ULL, 0x0197F5F617774523ULL, 0x1EB15BCEA33F8CB0ULL
        },
        {
            0x11CE2183F0CED2A7ULL, 0xA3577141FB3AC750ULL, 0x1DC4012967605DC8ULL, 0x9A519826079F411BULL, 
            0x578C78C29AE80A85ULL, 0xCA2B5558F318B37DULL, 0x3C6F50E6EA036FD4ULL, 0xAEE3EDEA2D857EEBULL, 
            0x756EB40399763E71ULL, 0xAD9DF001500EA20AULL, 0xE10D4E314731828AULL, 0x0640B39073554E7BULL, 
            0x427D955EC46802D3ULL, 0xF5B68FA365A2F884ULL, 0x93432327C9ACB76AULL, 0xA4B8FAA8011C7574ULL, 
            0x460ED2D72F47DA71ULL, 0x3895F0C2B7A4007AULL, 0x393D1946063C45DBULL, 0xE26894D1C0D700D9ULL, 
            0x6540F912B48E7B77ULL, 0xA3E30C40EAF101A9ULL, 0xBF5C034B6F66E569ULL, 0xEE3473D69D0836B7ULL, 
            0x9CE406FE46B016D8ULL, 0x6434D2F525ED733CULL, 0xB55772EE74D813E0ULL, 0x430F01F5AC06CC8FULL, 
            0x1290F9ED499433FEULL, 0x7B96D76F3B89BF15ULL, 0x64CA98034E6E5296ULL, 0x3A88AFF7BBC4D543ULL
        },
        {
            0x0D4AADFB6C81A915ULL, 0x00DD2756A4BF1887ULL, 0xF1C35789203B6EEAULL, 0x4E54306B48802A3CULL, 
            0x4EF2E0CEA7BEFBB7ULL, 0xDE7543C505603880ULL, 0x31BA267FCAD7E42FULL, 0xC3274114DE9FD356ULL, 
            0xB85E771E4710A0ECULL, 0xF0C8BFD4C155AE24ULL, 0x51270D6A25E4D14DULL, 0x7ADD953C64A00D4EULL, 
            0x386097D90E0FCDE6ULL, 0x2327A94F826D39E7ULL, 0x445882B44279EDF1ULL, 0x24286A57C889B6B5ULL, 
            0x6FEB18AAF07A0430ULL, 0x8A22FEB033EB4F2BULL, 0xC3996B9D4D1B6EEFULL, 0x282836575A4FDF79ULL, 
            0x34A11580F05646C0ULL, 0x735F7A2A1CAE58E6ULL, 0xB4F740C829690CA1ULL, 0x34AED4DCB25B46B5ULL, 
            0xA7FF7BAEC2DE8096ULL, 0xEE0CD6D92794D417ULL, 0x1E045F4A204BF39CULL, 0x19766D98AE2C60D3ULL, 
            0x1B5B1B3C203C172DULL, 0x8EF39DF8635FD8E9ULL, 0xD345CFE44574CDD9ULL, 0x6DBB67CC43F4DB29ULL
        },
        {
            0x66019F8AF113AFC2ULL, 0xC98364D5C6316B13ULL, 0x2E0870795ED823D8ULL, 0x56765533216CAB20ULL, 
            0xC60A6D27DBF274AAULL, 0xD8DAA1106724EE0CULL, 0x7903E92F7B604D35ULL, 0xF1A252F980601ACDULL, 
            0xC9A56EADEADEFC23ULL, 0x56F3185AF194905DULL, 0x50973674538ECC81ULL, 0x037A46D0596DB12AULL, 
            0xFB3CC7B73499F050ULL, 0x6B1E499FD4EA79A9ULL, 0xEAAAD49C141B59D0ULL, 0x5B57A992F7EDF487ULL, 
            0xBE447CAD8C535C87ULL, 0x18882EDB84ECF8EAULL, 0xB3DDF02C0315CC1FULL, 0x52C30852F8E9901AULL, 
            0x8C3841636C09A57BULL, 0x96814AE57D1C15A9ULL, 0xD2812B32F2CE3A6CULL, 0x4362976A073EAA2DULL, 
            0x2294D4009DB795CBULL, 0xDCEDF46A06CDCFA3ULL, 0xDB342FDA18A0D9B4ULL, 0xEC203EA88BA8076FULL, 
            0xA9DF91DE63ED4FB5ULL, 0xF3EFADEA0D7EB903ULL, 0x47E931F994E81C8CULL, 0x7C358AE27EB5EB8DULL
        },
        {
            0x841A3A762D2AC85AULL, 0x100EC252AA12E013ULL, 0x7B70EAF1A016CFB1ULL, 0x6243F78B2A8BF20BULL, 
            0xC3B7686053626F6AULL, 0xBFD6C20944969AB6ULL, 0xDF94E1732AB80792ULL, 0xE880DEFA359F0672ULL, 
            0xE658A560B925AE86ULL, 0x71550FE794ED96E1ULL, 0x16256794B8EB7357ULL, 0xE7DDF9D8DBC1AB49ULL, 
            0x89F60B98E381901EULL, 0x7F8DDE9BA23FB624ULL, 0x7DE1E07058C43EFFULL, 0xDE22605561C9C8C4ULL, 
            0xF556A65084875B9FULL, 0x6335D39CECEA87D2ULL, 0x8C588DF3B6DD42B3ULL, 0xB0A5C04499AA5055ULL, 
            0x3722CB087E9E598BULL, 0xAE39422091C68EB2ULL, 0x4DBFF7F9D0099742ULL, 0x76D5C3E39B5DB21EULL, 
            0x0D8ECC8B8B95553CULL, 0x4540A8B0D7337387ULL, 0xAC8F5795D1E1DE0BULL, 0xB2EA9E1E25ED1832ULL, 
            0xA8046988586D5D0EULL, 0x3F4B74FD6932D1D1ULL, 0x418ACA13BC44A486ULL, 0xAF6126957613DF1CULL
        }
    },
    {
        {
            0x050AE0EF520514D2ULL, 0xCC0FE03CA4936013ULL, 0x8BCFFA43F47B2A34ULL, 0x39AC9080735DB6C8ULL, 
            0x525BA617A2AFB615ULL, 0x9CBBF70A254AD42CULL, 0xA4770D1476CD1895ULL, 0x7066BBF8228E5D2DULL, 
            0x2A33C5F191806BAFULL, 0xAE4AB906D411A368ULL, 0x8279558D22C6E5ABULL, 0xCC073E0C890C6AB3ULL, 
            0xF5F945186DB8D9B4ULL, 0xD7FC202555D43281ULL, 0x51F32AB6D45BD595ULL, 0xB825E828B6DE1A56ULL, 
            0xFE8A66144AE66791ULL, 0xF5D1034A1CDF5118ULL, 0x5ED8A6F0E4E3C878ULL, 0x56E4F2D7250B592CULL, 
            0x26BD095CDC28B83DULL, 0x77CDA2FFED69A9E4ULL, 0xCA5DF11669B6A71FULL, 0x3A0B0EF104B3F940ULL, 
            0x98BD60D0BC91DBEBULL, 0x9FF6F6E330C737D5ULL, 0xBF931A36A0A29B5BULL, 0xB690AF7BCA5A2FF0ULL, 
            0x80B75EFD1B0A0AAFULL, 0x6CF8716EC5B51DE6ULL, 0x3B565BA9A5FAF67DULL, 0x058E1A86C4689C40ULL
        },
        {
            0x8912988DF32304DDULL, 0x5A480E628A14A80CULL, 0xD864B303FE3874FEULL, 0x730A4C6662676F7BULL, 
            0xB62FB041A689F5DAULL, 0x13E1B45C0FE3B7FBULL, 0xBB96F752C1470FC9ULL, 0xD08F3DA3AC7C8B92ULL, 
            0x05B6AF07AD19E9ECULL, 0xA84788890642BA82ULL, 0xB550914A075A1704ULL, 0x68011CC02D191598ULL, 
            0x000C7166C8DC93B0ULL, 0xB6ACBA8DFE8F716DULL, 0x16B63FB88295510EULL, 0xB9AE934B01349EECULL, 
            0x00F0E2D85B1959DAULL, 0x30225F49E701EA61ULL, 0xDE8169C1DA067AA5ULL, 0xF65E805DF8A5BB38ULL, 
            0x798D4C4F9650C1FBULL, 0x1D5BFCA7F0CBE547ULL, 0xD4F6FCD1CDA98BB5ULL, 0xE9063C20C9475DF0ULL, 
            0x5A65EF6B46442741ULL, 0x0FCC4D11999BE280ULL, 0xD95F017FB07F17AFULL, 0x01CC7531B062C8DBULL, 
            0x551855B64478BCDCULL, 0xD4588F507398E68DULL, 0x0F1FC246C44818A9ULL, 0x1D24F116BE7CF8BDULL
        },
        {
            0xA12C02B1232C8B51ULL, 0x268BA659F2214B53ULL, 0x07F9446CA56A6243ULL, 0xF96A88CAECF2B08AULL, 
            0x95DA34A596C172EFULL, 0x9F4354FE5F62B524ULL, 0x035BBAF6B179A66CULL, 0x755F41744D14CB6FULL, 
            0x4F0A8A6253DBFB33ULL, 0x40C45D8A6136F4C6ULL, 0xF0313438E15C14D1ULL, 0x8FC765ED9EE42B3BULL, 
            0x7DC2B8F3999758F6ULL, 0xF13029D92421A363ULL, 0xBF3AF96C5C52C932ULL, 0x8A9CAFF6B5FCCE7EULL, 
            0x35C1E7D7A791C4D3ULL, 0xAA739264BEA27F38ULL, 0x3C83A7D1BBAB9C3FULL, 0x1D6CAB47A1B1EB42ULL, 
            0x0EA51014559815DAULL, 0x0A812490FDC637AEULL, 0xDA7D5BFF3313D441ULL, 0x81E9DAB91C12218AULL, 
            0x9B8845DD71E47D71ULL, 0xE58274A6640D72F8ULL, 0xBD061608595EBF66ULL, 0xAB7D7E0193D2C392ULL, 
            0x278BE92A3BC10C1DULL, 0xAE3EE38A7EE96205ULL, 0xDE45749F83F10EECULL, 0xEB2C2FA6C303C8E3ULL
        },
        {
            0xFE4B7683EE68EB6CULL, 0xD7B948FF142B4D75ULL, 0x223C434EB91BD28AULL, 0x62C16BFC1C2BB119ULL, 
            0xAF59023F31A16B5BULL, 0xD9191C1195975301ULL, 0xD5EE14D58CD7C911ULL, 0x0D91D114D07C67A4ULL, 
            0x04F0A75AE6C03A48ULL, 0x2BB175D9ABE9EDF3ULL, 0x593ACA6C0F53EF6EULL, 0x6327AC921FB5E6A7ULL, 
            0x8A88593A8C0E2019ULL, 0xBA59CA8295B45C12ULL, 0x96B33A3B393C7608ULL, 0x5DE9F2B94A6AE93DULL, 
            0xBE30D59031783147ULL, 0x68C781B7965AED3CULL, 0x67DE0EE15351F3A9ULL, 0x9FBBA3B8115A5931ULL, 
            0xFD68B5BD449085AFULL, 0xFCC2220A83EE582BULL, 0x804E53B975CAECD8ULL, 0xB6B25A93173B00F1ULL, 
            0xA210CFEBABCAAF8CULL, 0x7799C9EAE1ACD79BULL, 0x6D81BE8E0E7CF245ULL, 0xDC89AC537BCCD0ACULL, 
            0xC879135AEF4E3CF0ULL, 0x59BEA4AA58422723ULL, 0xE3A72821B3B02526ULL, 0x4A9A2A6D59CE6BA7ULL
        },
        {
            0xE664B86664B0753FULL, 0x51A4C1027E7FB9ACULL, 0x9986C98FCD6B5850ULL, 0x43C93F1D70A6967FULL, 
            0x2F4EBA254343EA0CULL, 0xC03934AC01B1293CULL, 0x96A1BA7BA7BEC6CBULL, 0x7C6F91FBFAD54E5FULL, 
            0x6D14E828462FD3AFULL, 0x8DD822DC363D6AFBULL, 0x1A19DCAFF26AE280ULL, 0xEFFD42796270745EULL, 
            0xA3750B46F49EBA61ULL, 0xEBDCD5596F431C38ULL, 0xB107B0B047AB96ECULL, 0xECED6345F393A045ULL, 
            0x6F83AA70A010534AULL, 0x29B450B44A4D98BBULL, 0xC2D42938B9F68853ULL, 0x9BBFA4C8286C4118ULL, 
            0xFDD1F08CE7FB83B9ULL, 0x0AE8406BEA2E5E3CULL, 0x7BF2898F2A38D3D2ULL, 0x0340B9EBA9346EE8ULL, 
            0x7895B7AB63B1AD63ULL, 0x5E1272512E1C8A98ULL, 0xE125D2BC72F49E86ULL, 0xE86C5B870E029BBAULL, 
            0x578DAD21230E76B7ULL, 0x6DCA00981D7A0998ULL, 0xA932C26C7598093DULL, 0x6BE4FA23CACC31DFULL
        },
        {
            0x6E14BC08E00FC0FDULL, 0x0BDE3650AD590A57ULL, 0x75B567AE013A0833ULL, 0x583831D4B1DDC18CULL, 
            0xE321826E1191D435ULL, 0x904E4531F9DB3C97ULL, 0x424991245A33E5CFULL, 0xB105C1A26D1071B8ULL, 
            0x2C0234B17CA40665ULL, 0xD92F4B6AC21CA9B1ULL, 0x13A979251459158BULL, 0x0576408F30C35A03ULL, 
            0x65C4100E6C615167ULL, 0xDF84B486030AC7D9ULL, 0x0F1F8788091EBF0DULL, 0xB72B197726D4EEABULL, 
            0x05A2307926C1B7E7ULL, 0xEEE09235246BEEF0ULL, 0x129098DA43F64565ULL, 0x84AFF69E82745055ULL, 
            0xB84E1E3A50603A09ULL, 0xD5752ED19A1DB68DULL, 0x53C331D9718D1F65ULL, 0xF669C58850496318ULL, 
            0xA1FEE6527B30500EULL, 0xE2BD38F7DA40EEA9ULL, 0x33EDF0C1E9917FBDULL, 0x6BFF688EEFF44B07ULL, 
            0x3E631F29A12C317CULL, 0x7BB04607187C5FFBULL, 0xEEAE5A4BEF47D3FEULL, 0x3270634849A550F6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseCConstants = {
    0xCD435741A270FA29ULL,
    0x6D862B6AB39DE83BULL,
    0xCA01E1D49C954663ULL,
    0xCD435741A270FA29ULL,
    0x6D862B6AB39DE83BULL,
    0xCA01E1D49C954663ULL,
    0xFC00489AFEB30A96ULL,
    0x1E06A2AF9FDB0F86ULL,
    0x81,
    0x12,
    0x85,
    0x59,
    0x69,
    0xE1,
    0x29,
    0xE9
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseDSalts = {
    {
        {
            0xA1A456399176D4BDULL, 0x487E46E46E81FD82ULL, 0x988B52723B32E86FULL, 0x6FFDEB8688C99FAEULL, 
            0xC06302D318F67790ULL, 0x9576D4390E1A1A32ULL, 0xE8CF37F317C9BDC4ULL, 0x4D4012DB2C9151A8ULL, 
            0xE3BD17FE2266883CULL, 0x6D2F9DF37D7F1F09ULL, 0x12590D52EAF52EA2ULL, 0x72DA54008EA09FA7ULL, 
            0xAE82BD2AD8814102ULL, 0x4E094BED4ECBDA68ULL, 0xDAFCC6AEBA5B6C7CULL, 0xBFC3DB9D067A7536ULL, 
            0xF81E87067D4B147CULL, 0x130C397B670F919AULL, 0xE7488FD8D77537A0ULL, 0x84DDBA8A0C6C1DB0ULL, 
            0x122C99362B771F9CULL, 0x1B60A5972D6B0F39ULL, 0x0E03F645E3D09D8EULL, 0x5F41EA9CF8D9E5B5ULL, 
            0x0065394B7F9D1B04ULL, 0xE7EDAFD2A87D9945ULL, 0xCBCC4191E99CA84DULL, 0x2339A4E95E4D7F0CULL, 
            0xEB6CAA75F564337AULL, 0xE8B326F862277D61ULL, 0x249D1E6F00192F63ULL, 0x06BBF0EC0F34B13CULL
        },
        {
            0x721A0BBA3774F1B0ULL, 0x06B550264920C0A6ULL, 0x6F3AFF2A8337AE28ULL, 0x1721480CB360A7EDULL, 
            0xC2EF7E1CA156A97DULL, 0x3FBD3DBAD34503F1ULL, 0x322FB059DB37B119ULL, 0xC9424A42352C1423ULL, 
            0xDC50CAB51D95D414ULL, 0x5681632FF2311FCFULL, 0xD64FA4F223743DAAULL, 0x5D05795424ECF105ULL, 
            0xED439BA66D8E946EULL, 0xE5DC62B272D21B42ULL, 0xF7CB8792E61EBDACULL, 0x005389582549CE1AULL, 
            0x771D8856CDBF96ABULL, 0xD76BCBEB9CE2E123ULL, 0x6A899363E179513FULL, 0xC4B916115F541465ULL, 
            0xA86DDA374A193646ULL, 0xF9103EE60990273BULL, 0x39427FCFCCC8E070ULL, 0xFC10A15B46F58A09ULL, 
            0x73D76CB6773BE891ULL, 0xB5BEDE0FC5A61BF1ULL, 0x30C9607B4BE6DC05ULL, 0x21D0E1F5BD87340EULL, 
            0x7C1EDED40DB3FC3AULL, 0x7BD26E65F190D5BCULL, 0x0F747D5C447F7152ULL, 0x29F0390C366F6130ULL
        },
        {
            0xDC5CA1768124319FULL, 0xB470132E56DF46AEULL, 0xCF05D9B81622DDBCULL, 0x4D532D68392E6275ULL, 
            0xF691194B8199427CULL, 0x1898409C3F4F457AULL, 0x503F28C74FB0AF43ULL, 0x7CEDDF380FAE47E8ULL, 
            0x7C260137A948A736ULL, 0x0C8A290D07BD6110ULL, 0xD3FFC8E4DA556972ULL, 0xE55B188135076529ULL, 
            0x92D502ABCE128DF1ULL, 0x0C98CA352464C0FEULL, 0x8A34655BFC85D399ULL, 0x76E886604F08E500ULL, 
            0xF20E64AFEF7B0565ULL, 0xC8E36ACEF6E0922DULL, 0x4DDCB93D26D0F63DULL, 0x2AFA037B8BDB2CF6ULL, 
            0xD803E22967EE0966ULL, 0x843E02D1E911F0F5ULL, 0xA6C742B9AC020339ULL, 0x00EB73C8CA0C18ACULL, 
            0x6374D06BF0C5CE5CULL, 0x1A52FE113557511BULL, 0xB84EB78B2500EA26ULL, 0x2473148B93AE725EULL, 
            0xB0EA1C4BF0469132ULL, 0x134B820B4A6D9870ULL, 0x09B8098A6BA5AC16ULL, 0x23E7954F67B997F5ULL
        },
        {
            0xE87E68CBCF4AB714ULL, 0x0D15C5481C4D8AF1ULL, 0xD401D4E326A6074FULL, 0xF8A01CE979246D9DULL, 
            0x2C09AD9AAD8379E5ULL, 0x926947ECA55D86FEULL, 0x25BF95D61DFDA488ULL, 0x9F180966D06C79EBULL, 
            0x451783ED8691B0BDULL, 0xDE4BFDA0CFEA4AFBULL, 0x583E3DE17E1DA636ULL, 0xA47184448C26E109ULL, 
            0x38A1B4922A6C9F44ULL, 0x798D96D9C40B4EFBULL, 0xD1ABECC1AF1B7FAAULL, 0xE84F3103900C0195ULL, 
            0x8F336D5949D34612ULL, 0xB4FF77BCA1217D3DULL, 0xA6D8D221390EF16AULL, 0x60809F5F557E226AULL, 
            0x40D7E0BD8AF5AB35ULL, 0xDEAE33A27EF6938CULL, 0x0B4EFBB9FBFA9A30ULL, 0x5198CD3BF8249C31ULL, 
            0xC3955B6C247E6CE1ULL, 0xB0601A995B2C3CD6ULL, 0x99706E291E2FA821ULL, 0x70928418D4F7E45EULL, 
            0x73FEA631F14E6031ULL, 0xF9AC0CA3E2BCEBDBULL, 0x4F781D4AC0C8144FULL, 0xB4739C9FD09E94D3ULL
        },
        {
            0x0747EBB6C58AF9AEULL, 0x4A74D497E25FBB53ULL, 0x43825983EFB6ECE5ULL, 0x071D9A2ADAE93296ULL, 
            0x83FE6FE4C1532DF1ULL, 0xDDCE312164CB5F4EULL, 0x92062E649FF1A46EULL, 0x0DD652980C96FDCEULL, 
            0x64DD435A657C4024ULL, 0x4503F92BFDA525CAULL, 0x8AC8AC706F2B58C5ULL, 0xAAE97B2E0FD81C6CULL, 
            0xE445D0BF9C154C08ULL, 0x87D5DB15E39DE4A0ULL, 0x6E987DA7DCB5E781ULL, 0x76FF51DCC3D12185ULL, 
            0x3CC69551324CFD8CULL, 0x26398B1832C03C35ULL, 0xED8E821A03618A8DULL, 0x7E9C7F1E6E7FAA83ULL, 
            0xEA3A0E2E14FDCDE0ULL, 0x7CE5467CCD5A8E2AULL, 0x14924AEAA6802A06ULL, 0x9BF0542AA2275F91ULL, 
            0xE95432F6953962C1ULL, 0x87923300DA791E5AULL, 0x31CDB02DF73E2CDBULL, 0x1CC82A8C019366DFULL, 
            0x09382F39329F9D51ULL, 0x4B860145D5891C1CULL, 0x73D9F7220CBA9119ULL, 0x1CB9F96FC353D5D5ULL
        },
        {
            0x5131C84AD5CAB3AFULL, 0x9624CFEA1B2AF2A5ULL, 0x0265FE72AB4D97E6ULL, 0xD0BEC2669C53539AULL, 
            0x615CD2999F24A83FULL, 0xDB0968527A95431AULL, 0x189BAC208ED62D45ULL, 0xFC32AAE050BD70DAULL, 
            0xE237FF56FA01DDEFULL, 0x0D10DC097678469BULL, 0x23503D6EED27818FULL, 0xB499EA35006152A0ULL, 
            0xCB6B24BABB2B2A1CULL, 0xF45027BBA554A549ULL, 0x2FEDA5BC256649D0ULL, 0x578DC73E1086917AULL, 
            0x98A66D1FFC84AE6DULL, 0xF0DF63E402D31917ULL, 0x660B6EA769E979E4ULL, 0x485B357840D399C3ULL, 
            0x1CEE9A5630C0F432ULL, 0x7F542CF8758047FCULL, 0x487FB4ABCB5A111BULL, 0xE69AD0CC366FD7B2ULL, 
            0x72CEC401D2273C1BULL, 0x4AFD0659CD1B3326ULL, 0x7CD3FBA321C3DD03ULL, 0x8D983E478377E7ACULL, 
            0xE450BBB48833471DULL, 0xBC4D2D5F95EEADBEULL, 0x8312B3CE3D8CB1B9ULL, 0x493F15C11E4AC970ULL
        }
    },
    {
        {
            0x542B1304476D4AE0ULL, 0x259A454E2414F3E8ULL, 0x229531B982F87958ULL, 0xFBF0AED005839C25ULL, 
            0x3C2F42555E2B054BULL, 0xE83216E4A2FE42EBULL, 0x42DB75BE051A00E6ULL, 0x86F3F6E485EAB7B9ULL, 
            0xD34C7CE6C3A3B7DAULL, 0xF1A8B15EE93346C7ULL, 0x15D1C1F06A1D7F91ULL, 0x903171686E65CFBFULL, 
            0xDF8D6F65595D4509ULL, 0x0A908D8C125C9FFCULL, 0xE7A0E72FA4ACE163ULL, 0x471D5AABCAC38169ULL, 
            0xFBC1159D93B96E79ULL, 0x02FDC026E4A287A3ULL, 0x891E97A30C7EC6FCULL, 0xEB4BF8D698C7CA88ULL, 
            0xFAFDA683D442F89DULL, 0x62E9B7C54D8A454BULL, 0x24A36053ADB5F25AULL, 0xFFB2A433CB148B4EULL, 
            0x3BDA0B8A1C3CA00CULL, 0xD25E0BD63F55474FULL, 0xD389EB61D9A81480ULL, 0xF14D87765C84760CULL, 
            0x895E09E1463F2C89ULL, 0xEFCBB7CB80238CC9ULL, 0xC80EAF7F3BAED7D8ULL, 0xE6F220EE7DA4E672ULL
        },
        {
            0xD808A2A4514E5AE1ULL, 0x7508B4A87A33F040ULL, 0x77ED5A0BCD977A28ULL, 0xB45A82488ED89EC1ULL, 
            0x8D4EC5E88F6984BDULL, 0xF4B3C539B833E1C1ULL, 0x2281987144DBA033ULL, 0x1D10DB4714E2F34AULL, 
            0x6617CE68A68FFBA1ULL, 0x4E993558718CC1E2ULL, 0xA298EFA631C05036ULL, 0x02D92CD1588ACD13ULL, 
            0xF37C7C05D91E17F2ULL, 0xB9DBABCA1AE18F92ULL, 0xA410E3BECB8C96D4ULL, 0x877E0E123F85002DULL, 
            0x85B66490BBD720F6ULL, 0x7D39435ECDD5C9B7ULL, 0x296AA86046BF4D27ULL, 0xA981EFF0417AFBD1ULL, 
            0x9F50556A107B4244ULL, 0x49D179256208F10EULL, 0x50BFC51ADAB66A65ULL, 0x5E618DE7F1AFD24AULL, 
            0x0758E623E5BD6C00ULL, 0x42DCA5EB130C158CULL, 0x3824EBF77AF79A3DULL, 0xA3F535827DD13593ULL, 
            0xC630DEE5DB870E71ULL, 0xE15D00D22E97A81DULL, 0xEB0C7BDB191BCC0BULL, 0x42CCF0B4B4F0DA3DULL
        },
        {
            0x3CA855A0DC1EA9A8ULL, 0x0778A9B2AC6862DBULL, 0x26CC73830899A748ULL, 0x9A43661FCCB17134ULL, 
            0xC71AB1AFC3666FDCULL, 0x5C83C623E68DEBE1ULL, 0x11AF7C03A86351C9ULL, 0x40A33DD24D30A97EULL, 
            0x7C4824F1C96DFEF8ULL, 0x5505629A262D4983ULL, 0xE3CD4CF4A38E98D8ULL, 0x343038F3449BD7C2ULL, 
            0xE949E4106C53C401ULL, 0xF2DB7CFC45731A6EULL, 0x5C7A7785C481590BULL, 0x792B93167284E9FAULL, 
            0x96EC14600EAF3153ULL, 0x84881CA2BF7B3E71ULL, 0xB65D72C085C2C140ULL, 0x3CEED83172954C54ULL, 
            0x4BA308FE2B0C87C3ULL, 0x28DEEA9F8C6849C7ULL, 0x7DA25BA0BA5D81B0ULL, 0x958A24B35632C478ULL, 
            0xE6BDCD7AD101F054ULL, 0xE37F818E8E935360ULL, 0x11343F9D26E5CE6FULL, 0x8BA9A306211C34D0ULL, 
            0xB4528A848E57DF54ULL, 0xCBF70B2DB4C4E7A6ULL, 0x19063CA0B5509D28ULL, 0xB7B982F7BC460041ULL
        },
        {
            0xA5CB837C2A515E8EULL, 0x1C2723A2C47FA82CULL, 0x50289E6D8CF555FBULL, 0x229CA8A90F584507ULL, 
            0x05910FE3B561E190ULL, 0x49BA2BAC9295D5E7ULL, 0x26780B8F6B3D4842ULL, 0xDAC88AD64043581EULL, 
            0x1A395E0853E18142ULL, 0xA1F734EA32B2B530ULL, 0x6C857B2BA648F9FEULL, 0x1AACDA0F237F0E12ULL, 
            0xB5E359999FE4DB64ULL, 0xFA00B54D56A0EA9BULL, 0xB563174340541CB7ULL, 0x571DD7C6635CE762ULL, 
            0x4B862F6C3F9EFCBBULL, 0x4EF7793659B7B325ULL, 0xC2E7CBD6C6B5A443ULL, 0xEBDCF1B265BE0B47ULL, 
            0x42633858190483FFULL, 0xE0B017A5FB6C3D17ULL, 0xB762E36423F7E031ULL, 0xAA53DD3C6B7B39A5ULL, 
            0x13910AD5C0EC1303ULL, 0x92D4B6EDAD9445DBULL, 0xD37FE129BD338A13ULL, 0x7BA5815FCFD59DB8ULL, 
            0x45470AC9FF983EC7ULL, 0xE976B526B2ED2A6FULL, 0x385338336E5F2036ULL, 0xE21B045A5F919E22ULL
        },
        {
            0x84759A393B3FA952ULL, 0x05DCF7F3CC27001EULL, 0xFEBA61F40710BA1CULL, 0xD1D2897BCBE5A8A7ULL, 
            0x9D341A1163CF3021ULL, 0xB60771BF0B21572FULL, 0x8079AEDBC0F7709BULL, 0xD22B6D2B03D61305ULL, 
            0xA71357420E2B790FULL, 0x9CE6A8A51186F478ULL, 0x83F3EC3A05DB0F88ULL, 0x4401EDDE4BDBA5BAULL, 
            0x987CF0D6CC23DEC9ULL, 0xD7202A1611584980ULL, 0xDF29016C864774EDULL, 0xE1447C63CD70A1D7ULL, 
            0x998ACFFC8D6E1CD2ULL, 0xBEA114C1008E6863ULL, 0x72EEAD0BF6307EC3ULL, 0x27EB0D76CDE33A0EULL, 
            0x01D596128D2E9BF7ULL, 0xEC7A9CCF56103630ULL, 0x2896D1CC857DB782ULL, 0x64015BD3A99EE847ULL, 
            0x49756C3C9D4683ECULL, 0x79DB3DCF3D0C36DFULL, 0xF56A9FFE39912273ULL, 0xFC86B14A96CD6B4EULL, 
            0xAC41F3180D58D06CULL, 0xC2C5386728E7CADDULL, 0xD5BE3C2E09D152D7ULL, 0xAEDAC06597A0B84BULL
        },
        {
            0x4AC7F7333EEDE673ULL, 0xDEEE26627CC52385ULL, 0x3E2EB028FA49445FULL, 0x85C72B58BF8ED8EFULL, 
            0xA7507FF8CC1BA3DFULL, 0xF2F91BB84DBE6FF8ULL, 0xD41582CAB2C7AF8CULL, 0x9C24F3E7D802FAEBULL, 
            0x85C6A16A9668D259ULL, 0x1A927400A9F4A5B4ULL, 0xA737C0BCD3A7F408ULL, 0x0D6499D011962E73ULL, 
            0xC46999301FC258CDULL, 0x38BC84A43F66B0CEULL, 0x8DAF1B14B3F80CAAULL, 0xB7B5065E53C878F4ULL, 
            0xE0B3BD7DB9C2E79EULL, 0x4DEA482E2D6A75D7ULL, 0x2A49DE363B8D8B27ULL, 0x935BE4D13FE8CA45ULL, 
            0x3CD050A15B5EAB7FULL, 0x4DD30C580B3857A0ULL, 0xB5283F92179981DDULL, 0x5237044D93C80264ULL, 
            0xD910369F30F8580EULL, 0xFAE8EC5BDC7C52CCULL, 0x3876BC95DD5744C5ULL, 0x2B0E3868EFA0C193ULL, 
            0x95971820A228FA07ULL, 0xAC1E473FADC8B466ULL, 0xE75700D61CC384F1ULL, 0x157EF4A82CBD6794ULL
        }
    },
    {
        {
            0x3C09900E9EE772FEULL, 0x2D22DB3578104E2FULL, 0x6077D7515709C446ULL, 0x38284A3B62FA5F48ULL, 
            0x9A8511EB102EFF44ULL, 0x5751373D13DE4E41ULL, 0x98143B8E667A455FULL, 0xA2F70A2844FCC73AULL, 
            0x8A5839FA39E4C2E9ULL, 0xDDAED237B16FA1D0ULL, 0x8511FE1BED4C041EULL, 0x26704FEC4355E79DULL, 
            0x7D09133992931438ULL, 0x329954508F278E4AULL, 0xB723E2F6CE370A9EULL, 0x109BC6E73E295479ULL, 
            0x8C3BC9886294C050ULL, 0x6DA09DB48FED881AULL, 0x9170A029A74E8046ULL, 0xB5EBCA3A1E58AFE8ULL, 
            0xC4B543882A7E3672ULL, 0x50AFF344450D9BE6ULL, 0x48A80239FA4F5EB2ULL, 0xD1B9BC2DB9143262ULL, 
            0x900C230D1FBE5B6CULL, 0x7CB280D5D1145F8FULL, 0xE563F1CCC268812BULL, 0xFACE2CC39A8057F6ULL, 
            0x75D2893893199568ULL, 0x1A78B5315DFE039AULL, 0x0D8D26D96F055D3FULL, 0xB223EF05576FD943ULL
        },
        {
            0xB6AEFA0E79A5F50BULL, 0x257F205C27FE46A0ULL, 0x128A8299A4FCC490ULL, 0x9BFF8FB865971C08ULL, 
            0x6602F73C2F6F434BULL, 0x11C47E7C5E5B1F43ULL, 0xBE0056411B90A1F2ULL, 0x2C785171DDE6EE61ULL, 
            0xB4895700CFEE29F2ULL, 0xCD9786E1D9982E6FULL, 0x09C2ECB2AA858701ULL, 0xA1A85A313D143CF0ULL, 
            0xE95D2FE36558F237ULL, 0xB45EFF060AA90B0DULL, 0x963012C67C817165ULL, 0x6A4EFBC67A379A6DULL, 
            0xFAA8AF65400DEC8DULL, 0xF78D9BDF54904197ULL, 0x12DE72572ED96109ULL, 0x60E105C7730FFA9CULL, 
            0xBD27ED7F0EA6DCC9ULL, 0x09B6C9F482A8E036ULL, 0x2C418AD9FC5C9F14ULL, 0x219F3FBDE3E42759ULL, 
            0x349FA40F29B8EF94ULL, 0xFDF9C0456DE85527ULL, 0x79C792091004CABAULL, 0x9A9131F5ACD7AA10ULL, 
            0x008D2F90B1222928ULL, 0x799B93D99D19574CULL, 0x18B61B0303E2C830ULL, 0xC436750ED6FF943DULL
        },
        {
            0x71C1B0ED7C57BE5CULL, 0xB960E0FF9AC5740FULL, 0xE6212AFE109CC423ULL, 0x2653F7B86DC8B2CEULL, 
            0x48E1F04F83D5851BULL, 0xA8A28F4ECC0B1764ULL, 0x693D49D302381229ULL, 0x74AEE46494A453ABULL, 
            0xBF997F43C8CEC615ULL, 0xDB8CF958093E3D7FULL, 0xC9F700DA0703AC90ULL, 0x45807318122B5448ULL, 
            0x4018BBCA3A481541ULL, 0xF27BC59269909188ULL, 0xB94D9A1AA4D471A7ULL, 0xC69DD3B6BA2586E8ULL, 
            0xCE6C554A20684C97ULL, 0x6038E03A7B164547ULL, 0xFFFAD0163B8BFC2CULL, 0xF0759B11D43556C1ULL, 
            0x968BBAD67785B4FBULL, 0x9F645D7CB6C75E96ULL, 0x9755C64D3ED4715AULL, 0xB0C787C175A10FA6ULL, 
            0x87F110BEBEDEA557ULL, 0x523A9BA4FD26C373ULL, 0xB8B3EFFB34E08439ULL, 0x65360F731B4FA22EULL, 
            0xD6F8063A1F7DFAEFULL, 0xAAF6BE9200CB79A0ULL, 0x15343D73F2B5FEECULL, 0x3CAB2C15418DE446ULL
        },
        {
            0x30E7ECADD35245B0ULL, 0x12DF2B43857921EEULL, 0xA2524185BBE4C610ULL, 0x41360875A706D3CBULL, 
            0xCD76A0652E9A09E3ULL, 0x33FAA18CFF670AB2ULL, 0xC2A59A898DF7EE79ULL, 0x769FB68DA73821D9ULL, 
            0xA610485E853F470BULL, 0x76485D347264E4D8ULL, 0xC2630FEF3146F027ULL, 0xC871F70CA2887DD1ULL, 
            0xB9C58369DD402382ULL, 0x372A5894359703B7ULL, 0x59451B136A92D93BULL, 0xC5725BE0910B941EULL, 
            0x10360C1B95F89D74ULL, 0x03C6186A235C3207ULL, 0x11A01564106460D6ULL, 0x570BFE4838A7F984ULL, 
            0x632AEBA2FE57F983ULL, 0x1AFA67219345E806ULL, 0xC7ED6318D4A66964ULL, 0xB7332274EA9B0E55ULL, 
            0x00C8B2D7C4054C82ULL, 0xBE7C3E2B428C074CULL, 0xA80814250E80458BULL, 0xAF175D9D954724A1ULL, 
            0xD9A97EED3619CE0EULL, 0x449A8C5098676414ULL, 0xED204432C2D0477BULL, 0xCDEEE24D7F06CDC2ULL
        },
        {
            0x7490CE34EAC67E68ULL, 0xE30791CFB942398DULL, 0xB18941A5DA872251ULL, 0x9C2E96FAD24A46E3ULL, 
            0xD8D2AB5C867E5242ULL, 0xC1D433E73A50E8BCULL, 0x90EC4794EECCA649ULL, 0xBB129AF8AFE9313FULL, 
            0x3D958AA92F983EB1ULL, 0xB270B45BBB7108BCULL, 0x7D56A8514F4C0E52ULL, 0xD8A84901A63F1745ULL, 
            0x4E9D1B49D7D015A7ULL, 0x11B8C84D9E53875CULL, 0xF318B5F7DE8F9BC4ULL, 0x8EEB4650FB129C62ULL, 
            0x784ED27C72ED76ABULL, 0xC744DE01AD69CD35ULL, 0x15F6E2494DDF2BA7ULL, 0x53E576B421B1EF2DULL, 
            0x55D492DC217B0969ULL, 0x013AD7CB66202048ULL, 0x1618ED1D49F7CA63ULL, 0x8A636311546E6781ULL, 
            0x639F942E53111962ULL, 0x5D6EC7534D2CB680ULL, 0x7830E610834C6F49ULL, 0x7CF2C0CFD1625B3BULL, 
            0xB29A75EBBF253112ULL, 0x5A65A450672275F3ULL, 0xE21496EE01B9CF4EULL, 0x953CA1E6013DA3ABULL
        },
        {
            0x7B656AA7D61183EFULL, 0x643398BE5CB8B101ULL, 0x253735E561837E1EULL, 0x9447C277ACDFB350ULL, 
            0xF250186DA0E0F372ULL, 0x53DF3527ECD23459ULL, 0xA3E21293E7985977ULL, 0xDBEE77236A327E5FULL, 
            0x7E4DAA316B25B7D0ULL, 0x76DBC58967D109B9ULL, 0xD6CBBC2019F75D48ULL, 0x939183E7A04149CCULL, 
            0x827A5B334F9B57E9ULL, 0x2C5B2B2A4273B550ULL, 0x0DB205B7DBCDA9DDULL, 0x751B8DB19D0FC262ULL, 
            0x452F4082514FECD4ULL, 0x02AEFAC33419808FULL, 0xFB2B3411C801A441ULL, 0xD85AD6AFD6438383ULL, 
            0xB5D5BFBDDA20F240ULL, 0xC7334DE99A7048BCULL, 0xAC95F0E1A2F052ECULL, 0x306AE20BEB093220ULL, 
            0x4FEA8DE9BC813BD7ULL, 0x2D79FD680D90461FULL, 0x2DA71DDFDC1EF01EULL, 0x4E0B6DCB81DFD847ULL, 
            0xA416D0D8CF796F64ULL, 0x8DA0D8302B834017ULL, 0x988CFB37717339E9ULL, 0x345166F519F9F2EAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseDConstants = {
    0x6249AC2902620111ULL,
    0xE0415A357F475631ULL,
    0x1606969E439CC824ULL,
    0x6249AC2902620111ULL,
    0xE0415A357F475631ULL,
    0x1606969E439CC824ULL,
    0x239AB1C640E296CBULL,
    0xE0A71EBB2B17E76AULL,
    0xAF,
    0x44,
    0xB7,
    0x90,
    0xCD,
    0xC4,
    0x7A,
    0x29
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseESalts = {
    {
        {
            0x9D1795D80C74CA3BULL, 0xCC7EC648BFFDBB99ULL, 0x3E9E54BE38AD9C7DULL, 0x7039084C5116D074ULL, 
            0x1A8C57A8E0B16AE6ULL, 0x70F607EEBCD724EEULL, 0x4EBCB22544189A31ULL, 0x50AD0D4542E08BEFULL, 
            0x6403DCD2F3220514ULL, 0x04C149E1D8EFFCEEULL, 0x031C3968BE34F92DULL, 0x6D76EF6262253954ULL, 
            0x1F3E50EA2148375CULL, 0x7ED2C1D36518B301ULL, 0xB31103EAE4A4B548ULL, 0x1D741F7B48D4BB40ULL, 
            0x5E8131A9DD4CEE50ULL, 0x31AADD83EC6CA642ULL, 0x971C0EC16D25E56BULL, 0x95F61A2E2BD8B0ACULL, 
            0x4259E73D4106EC5EULL, 0x6B145B4EEB58A487ULL, 0x88002C97018DEE3AULL, 0x38EC0B8881255FB5ULL, 
            0x364185386DB3A878ULL, 0x0CDE5178E5B250D4ULL, 0xB2808205F677FFB8ULL, 0x62DAE9A8B3C1D8F8ULL, 
            0x75C4EF866AD9E58EULL, 0x50B7FD918C0DA481ULL, 0xD9074E40C186374CULL, 0x4559B26AAE813368ULL
        },
        {
            0x0BFC11829F1C273DULL, 0xB20ECC3B6D4645B3ULL, 0xFBB2C32312F87E39ULL, 0xD7F85DE833EF9082ULL, 
            0xC736EE7EE86D9661ULL, 0x9CC5E0CDBA30A21EULL, 0xED09629ABA538239ULL, 0x7B58BB1ED2D0291AULL, 
            0x0D9810C80153BBA4ULL, 0xF78C2F3510457C71ULL, 0x54CDE55F1FBFC7DCULL, 0x8257492D9B8F01F4ULL, 
            0x18FAF7F7C8A88727ULL, 0xBB47D2D5BB7A6954ULL, 0xCFD00DFB8D3BD977ULL, 0x32B689998AB013F5ULL, 
            0x4A4E56357EEB24C6ULL, 0x1947A488DA9A1159ULL, 0xD172ACCC5378C9ABULL, 0x9644E0E7DD05661DULL, 
            0x9A562CD7F220565BULL, 0xD47CEF86029F5D9DULL, 0x31751B2271FF7C4CULL, 0xD954F92A2895DFF6ULL, 
            0x1B0136CA3A07C18BULL, 0x8CC5B07FE983A6B8ULL, 0x0CCDD547BACD20BCULL, 0xEAB30AB737619827ULL, 
            0x17F373BB6E54A94EULL, 0xFBA19E48856D5057ULL, 0xBBAA1F0B98FA7C35ULL, 0x609AB4B8E43922A4ULL
        },
        {
            0x4C0FF8C7BB727FFFULL, 0x5B884524D4855759ULL, 0x977485441CABE88AULL, 0x70CF7FAAB0E177DEULL, 
            0xCF1545C0E9ADCD34ULL, 0xDEF671A7BB9C3D97ULL, 0xD2C1FAFCAB13236FULL, 0xB74D66E01367CC73ULL, 
            0x96D84304DBBE1E42ULL, 0x2840BD5447CECCC9ULL, 0xA5E24CE7157CB0B2ULL, 0xE7419270CC896AE2ULL, 
            0x0FE5B06C92B91D34ULL, 0x8F267E4A3CCDE005ULL, 0x49FDF1948AAF8E15ULL, 0x475F3C59D555F4D6ULL, 
            0xD828D5ED0CD95695ULL, 0xA0328CBBA5FFC4EAULL, 0x27E598492125B071ULL, 0xEABB4D083EBE25DDULL, 
            0x58666A314F255D49ULL, 0xF6D39D1D615DAC45ULL, 0x389F610A532B77D3ULL, 0x8A578999BC7B713CULL, 
            0xF82F88B8CB0388AEULL, 0x01A1C7E9903252DBULL, 0xAA949D608E6FCF2AULL, 0x04EC9DFB740E6CFEULL, 
            0xB428C66DCBC31AC4ULL, 0xD0D76647025F5028ULL, 0x251856798AD77166ULL, 0x7FD85FF53D479789ULL
        },
        {
            0x3421A1FC0367D6C2ULL, 0x7097985FD1FE2D71ULL, 0x4F6E7C935DA9E406ULL, 0xA24377F3F25C966DULL, 
            0xE20B46DA8AD6BA58ULL, 0xDDAA9F8EA729762EULL, 0xFB42C257C4A312CCULL, 0x54631AED7B967361ULL, 
            0xB2C29A341DEF5B86ULL, 0x09271155260AEF0DULL, 0x6BB06239C011C070ULL, 0x3012E453D3949E16ULL, 
            0xD02E6777319C061BULL, 0xC14EA16A746BC76DULL, 0x7423A7CF4A89D519ULL, 0xA5810A2FFB7F481EULL, 
            0x757B1EE71E61DDBFULL, 0x9B707BC9EAC53A1BULL, 0x8BB3AA3627F4F9DEULL, 0x70EDFF50E836AD59ULL, 
            0x4DF73776A03FB39FULL, 0x365C1EB1DFA377A9ULL, 0xF07D49A7A2BA4606ULL, 0x8FE3EFCBBD3832A6ULL, 
            0xE1473221BEC75DB7ULL, 0xE517C23062B453A3ULL, 0x4B477A16DA3CCE76ULL, 0xD557A2C7C6336058ULL, 
            0xF6DE31C8A60EFE85ULL, 0xE8D2A1AE704A7126ULL, 0x63451B864AA607A6ULL, 0x8FA0C1BBF57C8C81ULL
        },
        {
            0x5BB3E82065C81EF7ULL, 0x3C04460F0C1D41F8ULL, 0x00FC1AC7B9C468B0ULL, 0xDF821328E48F86D6ULL, 
            0x84CE591D22E75F67ULL, 0x1355435B52656933ULL, 0xFBA461EAF398E105ULL, 0x112F8176C460A608ULL, 
            0x6599F7FD96652247ULL, 0x6E5A444F24E3481CULL, 0x0F2FC1CFF604135DULL, 0x64C64C3810DE570CULL, 
            0x23B3257EA0D21B86ULL, 0x9CC63673EA4F1888ULL, 0xB164D8EB7BED1B01ULL, 0x5C807E8DA7EC78FAULL, 
            0x9913D5CD9874CF46ULL, 0xAAB464743284F0AAULL, 0xD55065EB118BDC35ULL, 0x8BE2715032BF3E59ULL, 
            0x67AF289450323C50ULL, 0x0C9DE993152F93ABULL, 0x5903EE95EC5F38BDULL, 0x753D18CDF9A8CB03ULL, 
            0xF7ED0E4794F33FA9ULL, 0xAFE626213AFE4A98ULL, 0x059FCF834B80FD92ULL, 0xD6987618F64FB346ULL, 
            0x1B5030D708DCED1EULL, 0x3D4D0643277E67DBULL, 0xA248FF7AE9AB0F81ULL, 0x63976671E106EC28ULL
        },
        {
            0x363F380B3B61DC48ULL, 0x65F4D98EF2995D5CULL, 0x08860FA69FE654B8ULL, 0xF9B7AB6F89043797ULL, 
            0x8327A2573E517954ULL, 0x2BFD1672CDA2A8E0ULL, 0x040572A1094D7FEDULL, 0x2DA3E17B20EE8502ULL, 
            0x04778AFF8B01BB67ULL, 0xB6DEB3FC5271A216ULL, 0x955CA4495B4447AFULL, 0x47B8DB89E793070EULL, 
            0x033FADE9BEDBE863ULL, 0xAB5D6C6417F287C9ULL, 0x425F25570A4F7298ULL, 0x16F3D55CDAEFB4A1ULL, 
            0x0CDB90F3DEB5A4A4ULL, 0x4D77C704CB2CA2E9ULL, 0x318559E97429D3E1ULL, 0x76828636A976805BULL, 
            0x22315D532EB25713ULL, 0x019F2C7D970E7837ULL, 0x1A6CF2084F84BECBULL, 0x966DF1AE2D8FDC8DULL, 
            0x6DA936DC2DADD968ULL, 0x5AE5FAC2138A6F17ULL, 0x0A27FD9899D15E7BULL, 0xAF3F6F6EA1975F90ULL, 
            0xA74F3A4DF8A442F8ULL, 0x1420477285F6D176ULL, 0x1BD1ACB1638999ABULL, 0xD17B48ADCD291262ULL
        }
    },
    {
        {
            0x2D0954C436B26414ULL, 0xE3CB2DB5F85E53FAULL, 0x70CA62190F59AFB3ULL, 0x900F6C4B88332B56ULL, 
            0x1AEC35241B950592ULL, 0x92DEECF4F5D5B5CCULL, 0x9CD8C76CA4900157ULL, 0x861905577B7FF060ULL, 
            0x18F8B120F0E16D38ULL, 0x20CC8954A5070664ULL, 0x1644A77D04843A8CULL, 0xECAE1FAAAB596828ULL, 
            0x0AB2E80E6771005FULL, 0xD304DEF90B015412ULL, 0x5E606795355BDAAEULL, 0x7C32A7196E48355AULL, 
            0x389B4FF8D5D39399ULL, 0x5C0AAAF0A5A5CD97ULL, 0xC1037BDEB4589468ULL, 0xE4FD45473CCD7526ULL, 
            0x4711E10D90C2FDEBULL, 0xE99CE1C9CCEF91E1ULL, 0x13F2259586ED788BULL, 0xCEE265AE7BAB7079ULL, 
            0x7292B0A48ABE3F8AULL, 0x1E1DFD9F175A0E00ULL, 0xE4006B0FA72B7327ULL, 0x5BE07BF36A0452DDULL, 
            0x82BB1976C239198CULL, 0x8B358C7FF096743FULL, 0xDCD3E28776102AE5ULL, 0x3D73D2903FD05B9DULL
        },
        {
            0xD3C4A54A39C99036ULL, 0x5F78C069B700B34BULL, 0x65E239725E75C5DDULL, 0x9E1385907B6E5197ULL, 
            0xB31AF8375E203F6EULL, 0x2D1F31625D22A131ULL, 0x2313F11B5B0D583BULL, 0xB56619D9A165119AULL, 
            0xBEE2732F36E5A689ULL, 0x8D2210E0A084928DULL, 0xEAF3AD11508C7526ULL, 0x0AE4DEF5F7D5ABB8ULL, 
            0x4AA1F1E0C51B60D7ULL, 0x058835ADDC687973ULL, 0x21B98F32361F052AULL, 0xF362A5EEEE287FB2ULL, 
            0x98F234483E6A3F84ULL, 0xD90A62F6274D54F0ULL, 0xF59E43DD8107CD61ULL, 0xB9307FEE1DE5FA05ULL, 
            0x2E1B8F07FA78EC18ULL, 0x816EFF2E8FBDD749ULL, 0x40C1ECBD3D4CCC1FULL, 0x80A04A9FCA8AD654ULL, 
            0x83B80F337634A0A9ULL, 0x2E4CE790B6697503ULL, 0xD0ABAD1EC93DCC68ULL, 0x0853713417C1BB94ULL, 
            0x80EB37B8D8FA49AFULL, 0x60D2F34034A5B94CULL, 0x8A6C56C9071FC5FCULL, 0x3830C62936696B78ULL
        },
        {
            0x38EC5C53FCD52B7FULL, 0x5E8F14966AD325BBULL, 0xEA08199BC40F0B0BULL, 0xFE22257E870E2474ULL, 
            0x0002A938796F0369ULL, 0xAE01B0576838C6F0ULL, 0x9000178DC15ECDEDULL, 0x9A9FEB2D896081CEULL, 
            0x251AB22323BC3AEBULL, 0xC0B309F31AA12C4EULL, 0xD647A0BA63DECE98ULL, 0x9DC9FDE414C5D61BULL, 
            0x698AB295209497B2ULL, 0xE004CCB5381AE54BULL, 0xB4F7F41B58C348ABULL, 0x1DA88741D8944D82ULL, 
            0x82AF1941DBE7D021ULL, 0x718171342E6A72D1ULL, 0xC2C03163AC946C57ULL, 0x316F92F220C782CBULL, 
            0xB097603BD0E947A8ULL, 0xA4B78985E54C72ACULL, 0xB766EA5728960285ULL, 0xDF6D62932082CDE7ULL, 
            0x9166D63E23F18EB3ULL, 0xE2B24DE0533E1148ULL, 0xFF15CDC3BE0F1CAAULL, 0xCBCEA415AED1DDBCULL, 
            0xD53D6D1D055507D0ULL, 0xC78204389CDCBAE6ULL, 0xB34AE6489A05C0C2ULL, 0xFAD517E6D93D39DFULL
        },
        {
            0xD44B8FBBAD9C2A48ULL, 0x2BE8FDCC8316C2E7ULL, 0x46B0C8360DF886A2ULL, 0x960657A2A5062509ULL, 
            0x56C7A559F0776C2FULL, 0x9AAA69B887DD03E7ULL, 0x4BD9C2D805441A7CULL, 0x20F674C8AE8C464EULL, 
            0xC9596E0BCF726DE5ULL, 0xE76B9170295EF73CULL, 0x35D8E67523DAAF12ULL, 0xEC3DC28F4C2CF2AEULL, 
            0x64D0FCBC6D190AC2ULL, 0x692EBD23F22DCD8BULL, 0xC770B8338CA6256BULL, 0x563E8E7BBC493A17ULL, 
            0xBCD8143C2838C23EULL, 0x098F010D2C59680EULL, 0x9F569715F7CD7796ULL, 0x7263C9DB3CEF6C1CULL, 
            0x10DEDDE1934F020CULL, 0xF9C44F378F73ED6EULL, 0x8B1D49A4E114B540ULL, 0x1DF6736CD7592E99ULL, 
            0x1C36D75F908B22C2ULL, 0xB82EB007FD936DF1ULL, 0x4E4A80ACA93CDEB8ULL, 0xEA553D7F9A7B56EFULL, 
            0x89FC8E2866A164FBULL, 0x10DB4E0D39FE8F9DULL, 0xD7DF2C8B2138747FULL, 0xCE30F25717EB592FULL
        },
        {
            0xE286EA42A87EB8BFULL, 0x81D9435FFCA99F73ULL, 0x14AD39CA0A913946ULL, 0x122495F83E3D2FA5ULL, 
            0x14B0E5D4E94A38D6ULL, 0x03CFF73721121B93ULL, 0x1081391AA58D36C9ULL, 0xA9F2B3BD5474E3B2ULL, 
            0x9DEB8455F6C13CD0ULL, 0xE5BC9B78E357FEF1ULL, 0x648E1ECD4D5815A3ULL, 0xD491521C3C744BB8ULL, 
            0xE34B4682CA52237DULL, 0xF28A05B411F53D0BULL, 0x4F0C946B9305A704ULL, 0x506BFEBB1111DE25ULL, 
            0x4ADDC655A5BD4D94ULL, 0x07862F5D8521FAE9ULL, 0xC29A5FC0FEE9C4DCULL, 0x7AD4D28E2AE51B05ULL, 
            0x6E1A41D46B770701ULL, 0x21E5ED8F302C339DULL, 0x42E841E336A5E3D5ULL, 0xB91F786436467B5EULL, 
            0x971507821A5DA7FEULL, 0x82CC97845D536491ULL, 0x9CB3947D39179E41ULL, 0xE92EC44C5E2585BBULL, 
            0xD5265AFB0485833AULL, 0xD778DB3C1CE42A0FULL, 0x6436AE9FDC6F9E85ULL, 0x635BD83228D6E1D8ULL
        },
        {
            0xEBA038815A976F2BULL, 0x49173451203EC6CEULL, 0x9831200A79D94035ULL, 0x9F60CFA91455DA19ULL, 
            0xF6FEA2F1DC917457ULL, 0x0A38AC3EC2FC7E89ULL, 0x9791B6374313480DULL, 0xBE8616DF62097914ULL, 
            0xA0D4543F474C3FCAULL, 0xA0EE9B1E4AC324F2ULL, 0xFF43159BF8C78E25ULL, 0xC41838994A466E88ULL, 
            0xBC8D4039C58B3991ULL, 0x08E1D2442CA09562ULL, 0x701CF932BDCBE637ULL, 0xDF4C90E4D1F3004AULL, 
            0x94C4E4EEE4A0C021ULL, 0x40D477E63721F7C9ULL, 0x9AA0D56C56B68EFBULL, 0xAA0C09F2E474D898ULL, 
            0x620751364FF626D2ULL, 0xC021F5EE3EFF8E49ULL, 0x1C420C29CB0D4D3CULL, 0x280431BDC4AE2B3FULL, 
            0xD10E67DB5DEA1D99ULL, 0x6E341E404D836FAAULL, 0xA7167E46B398F76DULL, 0x43C4D2CFD0D21FD0ULL, 
            0xA658CF60062F1759ULL, 0xE62A44C93D6AB98DULL, 0xDC4C98D98288F0C7ULL, 0xCA6078AAA93D44F8ULL
        }
    },
    {
        {
            0xEE3A70AC139BD562ULL, 0x207DD82150318615ULL, 0x39E34EBE2AB16866ULL, 0x5A930AE1488C630EULL, 
            0xDBA5136A8E510EDFULL, 0x7B2A6224D23D2356ULL, 0xA8729F6C70D41E5EULL, 0x2DF4C58D5E99175BULL, 
            0xD8F109CFEEB76E55ULL, 0x7E5660C0B5E55FE9ULL, 0xB3F37ADCCDECC287ULL, 0x064644DE92A86B99ULL, 
            0x29768CA0EB240D56ULL, 0x34692092E24F7BBEULL, 0x69220FD2991017A2ULL, 0xDEE61BDE1D0A0BC5ULL, 
            0xB4CE6676526DA38EULL, 0x6FD17BD0436ACBE3ULL, 0x75A55ACA69AD858EULL, 0x031F33486E0F6789ULL, 
            0xBCE5C0FDF0538160ULL, 0x668712B917707EC2ULL, 0x73D7596D26432A1AULL, 0xC801B00B35AB2FBAULL, 
            0x11242037CEE2D7A5ULL, 0x682216616EA91A82ULL, 0xA8AAB89AEDAB090BULL, 0xF998CCDF6E89C0E9ULL, 
            0xD8F75910F25F09D0ULL, 0x3D8FF851746853D4ULL, 0x805F0F7D35926C9FULL, 0xA2D70A2979D0DFF6ULL
        },
        {
            0x45B6C201A20C8B01ULL, 0xDC9BCE4F5395027CULL, 0x08AF1ED060A1BF12ULL, 0x776011B7683744B0ULL, 
            0xA782494AD8DB7598ULL, 0xB13F84427F9F6759ULL, 0x5DD48EDC998F8BE1ULL, 0x790CE5A3351833C9ULL, 
            0xC3E9017F6C284E8AULL, 0xFF933C3C0FB72002ULL, 0x62F89BC08F60CCA8ULL, 0x8D34A5C14E6D1CB8ULL, 
            0xC854565B5253C3A7ULL, 0x3BEC2B9DFCAAC68DULL, 0x72CC95970B063755ULL, 0x0D4CADF74FB5ABC9ULL, 
            0x91F02FF0AB9A50A5ULL, 0x293072E3B8B05F5BULL, 0x0BBEE84C9F58095FULL, 0x1561F18B5643180AULL, 
            0x41CFF7EBEEBDCF92ULL, 0xE31CDFC4D874CEFDULL, 0xA2D3016D8692EA7FULL, 0x75F3B4D773702164ULL, 
            0xF0E70D15569A089EULL, 0xAE2076F6019159BCULL, 0x1DE0C7FDAB98FB3BULL, 0x3FDFB49CD422418CULL, 
            0x110ED8E9C9E7E5FAULL, 0x82E996FCF9C85B68ULL, 0x80F7710BA3B1731CULL, 0x8E2102F4DA9617B5ULL
        },
        {
            0x4D1E32B9A1B6318FULL, 0x24F74148917A819AULL, 0xD2120A2B1114FA8BULL, 0xBAD77D084C7CC2B8ULL, 
            0x4F18EC38B62430A3ULL, 0x99D834F26662C319ULL, 0xA2EC559970C72A12ULL, 0xA0A1AE4C5FED7241ULL, 
            0xDFCF03C6FD78E2CDULL, 0x57A5E444911639F9ULL, 0xC275BE5A13B0F915ULL, 0xE731B8E7AF8DF27CULL, 
            0x6C3F113D3C9A8F29ULL, 0x1D80B9F130022F7DULL, 0x8B8F605A6C31F967ULL, 0x3445C130D7D3C815ULL, 
            0x0BF71D30199E2341ULL, 0x5FF9113471400DE0ULL, 0x97507CF93B713D71ULL, 0x0C6461AB98B13527ULL, 
            0xFE34FD56E6AD716DULL, 0x971CB27B05C7AD02ULL, 0x995204908344F6B4ULL, 0x09934791E4E11391ULL, 
            0x62FD32627E334EFAULL, 0x0359104BFABC96A3ULL, 0xFF0436FDFDB62E88ULL, 0x78009511AB5E4C2AULL, 
            0xE755643D32982F77ULL, 0xF3D6A5AF22ABBD91ULL, 0xC41B16167B9046A1ULL, 0x0FF6820968DD9B92ULL
        },
        {
            0xE2D0AE20555FE0F9ULL, 0x93C7C2FA6318EC8BULL, 0xAA643A19C51E05F2ULL, 0x38274939071E97C0ULL, 
            0x12C2796FE858CD1BULL, 0xDC9C1143768AF46DULL, 0x3FABF95F4E801C7FULL, 0x6E5FB74192735F55ULL, 
            0x9F61F35F3F287004ULL, 0xC3A8B4799022F51DULL, 0x62891B397CE72DC4ULL, 0xE754FFC783FD8014ULL, 
            0xA7A192A84D09FC2CULL, 0x1A022A7CBF19D1A6ULL, 0xC9A25ABB23BF4AE0ULL, 0x5CFED04B6195AE83ULL, 
            0xEB8CAB598897DF73ULL, 0x7BCB9E7A2457A190ULL, 0x9639F354C859B87BULL, 0x96F6A8723AC3FAD3ULL, 
            0xF3C8676DB5E1F1C6ULL, 0x99466E2AEF0DABF0ULL, 0x3020094E0227A231ULL, 0x18A1964215E340ACULL, 
            0xD08B03CC6A37627CULL, 0xE0DD4A659268589BULL, 0xE252B567381E1D7DULL, 0x84FF7AFA728225A0ULL, 
            0x24C94D93AF417A85ULL, 0x452365B02A8D4403ULL, 0x34F08DC0AA8E033EULL, 0xB151CEB043679F4EULL
        },
        {
            0xA2CBE2FFA07F7E39ULL, 0xE422AD9476E25557ULL, 0x450F488995A2FFD5ULL, 0xB63A02443FD82562ULL, 
            0x2F1B0E3E0284F714ULL, 0xF159908E1578B96EULL, 0xA11775FCE7848D04ULL, 0xB363F31B75732EDEULL, 
            0xF4E5E07FFFC8CF9BULL, 0xA5DDE14FFAF219C5ULL, 0x86EAA5E10C490D59ULL, 0x4311EE66CD00A024ULL, 
            0x34D06C15226A0264ULL, 0x638370A6FD50CA4DULL, 0x52CCFDF9392317F6ULL, 0xE6F4A4A7904EC76CULL, 
            0x95E19A7D612D4C55ULL, 0xDA0B127AC012DFC7ULL, 0x5746919A4A4DD2CFULL, 0xC1F02F9FB259BE89ULL, 
            0xF17D5B9176A366CCULL, 0xA918FA1C3C22F90CULL, 0x570E5F20D8E9C0BBULL, 0xE5056DEC7929CD8EULL, 
            0x38EF9A1F8EFE500CULL, 0x5253A747EB61DB06ULL, 0x0ABA28BEBB39D97AULL, 0xAC6622E2EFBF7885ULL, 
            0xC3B9C2122EDC6D5BULL, 0x45D5B02214C46148ULL, 0x7AE3C83C17B9FB7BULL, 0xBE156C243297BAD8ULL
        },
        {
            0x4E62DBD47D191E91ULL, 0xFC6368736B7688E3ULL, 0x0F12A2D6F47C83A6ULL, 0x593AB38B87024068ULL, 
            0x5CAA7CED1510F074ULL, 0x51B19AED97268AFFULL, 0x6B10E1DB85FD46F0ULL, 0xC7AF2CAE279E78CBULL, 
            0xDE8CBDCC74FB4F67ULL, 0x88022D86E1C0E984ULL, 0x6E476669E4D72EC6ULL, 0x2413C3D1FE38319FULL, 
            0x1FCBF69A81582ED2ULL, 0x8416D826820CFA98ULL, 0x917271B424834C99ULL, 0x92382563505CFE0CULL, 
            0x9840C8521ADFFCF8ULL, 0xB4CCAA9F8D631516ULL, 0xB5EB7CFD1131246BULL, 0xCF4072F69B7487AAULL, 
            0x175761E86A2B9B98ULL, 0xD21A31DE082FBC6CULL, 0xE3DBD3ED789A9DA1ULL, 0x98DAFBF3BC09CA45ULL, 
            0x9BBEFEB79C1FC9B4ULL, 0x9FF175CA1AEAF3BAULL, 0xCDB50EF51619AC64ULL, 0xE9D26864EBB3D342ULL, 
            0x42CBBE21CB0884E0ULL, 0x3441C657E2E7FCC5ULL, 0x3D8392639F1F96B9ULL, 0xBCC83BBC14EE1338ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseEConstants = {
    0xDC64850CB9FB7CBDULL,
    0xF64FF7025BC5F25BULL,
    0xD181A4B307636F10ULL,
    0xDC64850CB9FB7CBDULL,
    0xF64FF7025BC5F25BULL,
    0xD181A4B307636F10ULL,
    0xDEC2A2AB054B2F47ULL,
    0x4A0928C84B880A6AULL,
    0x63,
    0x28,
    0x29,
    0xBE,
    0xAF,
    0x52,
    0xE7,
    0xAE
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseFSalts = {
    {
        {
            0x575CD29E6D0D27EDULL, 0x54B97B22C1C45C02ULL, 0xC789A7AE68503587ULL, 0x8EA81D94E3793101ULL, 
            0x86E2EC20E4096872ULL, 0x37275967B612B8ACULL, 0xA137DF1A4BF281E4ULL, 0xA37391BEB55A5FD8ULL, 
            0xDC5B9442080B3D17ULL, 0x93A19A5FA84E88A5ULL, 0xADC0363D55F7572FULL, 0x744D9953A26A44B5ULL, 
            0x37360357002B85DDULL, 0x8C3997A58DCED7B4ULL, 0xD7EA5709D54C01B8ULL, 0x8B73F8036D12B5D4ULL, 
            0x9DE8D74BBFDC668CULL, 0xA52A1E08EC232380ULL, 0xD2BAABCE7DAC6CECULL, 0x257364C58202218DULL, 
            0x17AF97443A37125FULL, 0x4B099649F859F4DCULL, 0x7AD70C0C82751EE6ULL, 0x0C330F0FD886C096ULL, 
            0xD1AB43662BE7DB61ULL, 0xBB94A7C71C7EFB98ULL, 0x31ABF43EFD469FFAULL, 0xA62D69631D9760ABULL, 
            0x69322CAB6D894B39ULL, 0xA770813D6ABEE23DULL, 0x870B86B67A01F9CEULL, 0xD46B4C3C052174F4ULL
        },
        {
            0x18D7104B843CB92FULL, 0x175FBF718B82DEC7ULL, 0x2715402869459D9AULL, 0xCF9C17C5AC2BA00EULL, 
            0x3C02A6479184E638ULL, 0x81BC2AF4D07030EDULL, 0x6EE6E242F9FDAC03ULL, 0x4BD4ADF23E74D3C4ULL, 
            0x1C6B67059658BB3AULL, 0x493B46A781EE8DD3ULL, 0x09AA13C295FDB5D4ULL, 0x607D8AC27E068171ULL, 
            0x9D8AEC38AA92EAFEULL, 0x7425998D60D28937ULL, 0xED2AF69B852A5C3DULL, 0x9DAC2A8B7CF54091ULL, 
            0xFA14138ECED51246ULL, 0xDAA4A05C2F833473ULL, 0x1DCC697CEC6B3808ULL, 0x9BBC834A6C66D1FEULL, 
            0xCB95C85899B46A89ULL, 0x7F877E63AF1769F2ULL, 0xB1502FADF5C7D615ULL, 0xFB48CBDD912CC534ULL, 
            0xDE994FA111F7EC00ULL, 0xF0AC6EBD39713D32ULL, 0x83B1B87A3AAB1259ULL, 0x581AA713F8B4111EULL, 
            0x64E35A5E79D31DA7ULL, 0x3EFF5ED205B9F507ULL, 0xDF94686C8585814BULL, 0x940008CFB01D4D8DULL
        },
        {
            0x6FF9C35254FCFB06ULL, 0xBEAAFFE12C164D28ULL, 0x5722441D97AB6123ULL, 0x87973A5B84D1853FULL, 
            0x3C4060B9A5BDCDB0ULL, 0x3FAFECD98FD88F5DULL, 0xA65C38518C430CFAULL, 0x1835DD97D6514CE8ULL, 
            0xF62F58C3F7430034ULL, 0x2990384D0BFF5D11ULL, 0x4AE9C15346D1C89FULL, 0x402A7A757CC7468FULL, 
            0x68C94923A86E01D4ULL, 0x7A0025F5C10418EBULL, 0xDB2C52667E89C11FULL, 0x169E5024EBD7C718ULL, 
            0xDE0168C8DA4C9B13ULL, 0x923657F9712ADFB0ULL, 0x8AD1AA3DEFFBC494ULL, 0x01EEE0721FA56418ULL, 
            0xC10A4E346F0EA0FAULL, 0xDA2830EE61665EE4ULL, 0x2D50D3B0C9FC806DULL, 0x8B36C1DCF2E3AB05ULL, 
            0xFDF03E9BAEC38A0CULL, 0x34C86262F619A0CCULL, 0x39CBCED8EA8EBB8EULL, 0xC0F5F1BC45849787ULL, 
            0x09F3D4C589C1EA13ULL, 0x89CA55BB8092B441ULL, 0x5227F0DF8016F1A1ULL, 0x8B8B57DB6571D718ULL
        },
        {
            0x12274EA7CCE68563ULL, 0x8C3CEC57E82C9E63ULL, 0xCF7B85680812555AULL, 0x252A6A1BC2CDEE8EULL, 
            0x04BCF4F8035708DDULL, 0x1D90B8AFDC586EF1ULL, 0x7FF1F21985ACF8D5ULL, 0xFEBB7F3981262114ULL, 
            0x1254A6B50243EC16ULL, 0xCF3BBFC172309F01ULL, 0x2FBBAABDDB154D25ULL, 0x1D2EABB6CA83A236ULL, 
            0xBFB7B74943F75962ULL, 0x274FED96D10FB5A2ULL, 0xECEEC7B5EA382E6EULL, 0xD57BBAC036066E98ULL, 
            0x84DC494065C08228ULL, 0x39F5D7C4BBB3EF32ULL, 0x10D75049E7E87C31ULL, 0xCD4CF64CFC810896ULL, 
            0x9C9F13B150F61AA2ULL, 0x06EF40DB0D6F1854ULL, 0xC9059A86689FDAEBULL, 0x6FA565E8807B358AULL, 
            0xA18DE39EA8767088ULL, 0xB9033133DDBDA849ULL, 0xDF0B0E2E768BCD73ULL, 0x9A47E924BBFFB6C0ULL, 
            0xC341C0B43A8F69FCULL, 0x6877E0D9FEA63EF2ULL, 0xD8736B0D90826172ULL, 0x0C040314C8269D0CULL
        },
        {
            0xBDD9291460BD8E1DULL, 0xBB9C5F9B0866DDC5ULL, 0x57BE30943E803E5DULL, 0xE0EBCBF67FC8BAE9ULL, 
            0xD9AFA6592FECFE15ULL, 0xF32D02A577045B00ULL, 0x4C241624932842EAULL, 0x8BBA0DF355E30994ULL, 
            0xC982CEFBD8C81B0AULL, 0x7884F1D3D0204C8AULL, 0xC5039733C9A94751ULL, 0xD042F4E08794909CULL, 
            0x7049F28E0E06A7F5ULL, 0x97FC2473F2803E41ULL, 0x3AA0F527E88201D0ULL, 0xACC4CA2F46208934ULL, 
            0x13C1938F505DD01DULL, 0x8C65B93297717085ULL, 0x21D756E141D2C40AULL, 0x310C6E4956E8752EULL, 
            0xB2A27536D4714641ULL, 0x73D2D21C1D8FDDFDULL, 0xC677F7D32450D043ULL, 0xB9DAAEAD8DF055F8ULL, 
            0x7E12B8A44423E7C8ULL, 0x25FCE9600DE76050ULL, 0xD87C9C79F0D778F2ULL, 0xCF3D737CD7B2870BULL, 
            0x5E66A85A4979BDE7ULL, 0x417D5BE82F5469A4ULL, 0x9C2C159B0AE5D4EEULL, 0x92B9973BA34BFF62ULL
        },
        {
            0x54EC106BBB8161F9ULL, 0x730AA20C4C42AEEFULL, 0xA3079EC20C6832BCULL, 0xC9B263095DB2ECD4ULL, 
            0x0B9754C096B293ADULL, 0xDC8D562EA47A599FULL, 0xBA0F366828DFF0C0ULL, 0x927E42E38FABE8FFULL, 
            0xE1E64A01A188FB9AULL, 0x40B8E2AA0E2E4BE1ULL, 0xB6A6CB10AD7CB160ULL, 0x0FF0A56D370AAEC8ULL, 
            0xE0A7AB0DF19286C0ULL, 0x47C1F249EADCF697ULL, 0x477842E509D64143ULL, 0xB1A1A5223636DD6AULL, 
            0x0CF9E63767B9D537ULL, 0xAFF929537DB1D4B6ULL, 0x03F184FC7EC3650DULL, 0xB476179ADDDA0A4EULL, 
            0x95EDEFC7DE761BBCULL, 0xCCEE46211D1ABD98ULL, 0x0C20AF6150734296ULL, 0xE154F60B183D2AE1ULL, 
            0xA9CC8A8232E49021ULL, 0xA2596F703AAFCC64ULL, 0x96E8A2BA86CE1E4EULL, 0xCDCFE6A92620E61FULL, 
            0xAFCA0418B89A8986ULL, 0xB41A3DA12AAC905CULL, 0x80E04CC632C2E7C5ULL, 0xF67830A094BAE0F4ULL
        }
    },
    {
        {
            0xF248591B9F2C7478ULL, 0xAC6F4935AA0DC6E8ULL, 0x52C6FEA02E9951C1ULL, 0x517493B8AED00FB0ULL, 
            0xB84B090A5ED7F7A7ULL, 0xF73441126A069E53ULL, 0x91C88017552F6812ULL, 0x8DDA265CB26DEF03ULL, 
            0x69A6B4E1683AEE4FULL, 0x8F7933C329F0F60FULL, 0xDF0FEB677E44B71EULL, 0x4B224BE5FF4B37CAULL, 
            0xC76B80F4292D5280ULL, 0x4C71D25AAA91D904ULL, 0x0723971A8F19C47AULL, 0x7AAAAA3667698C60ULL, 
            0x22E10796F2E353A4ULL, 0xE9C1DDBA056E1DB0ULL, 0xC94245C702E06353ULL, 0xA11F317F3A82F2A2ULL, 
            0xBE6A7F4C14AEAD18ULL, 0x00969A31488A68DBULL, 0x73C27B09282F87DBULL, 0x150993B86DB33788ULL, 
            0x5A2E9B69576A11CCULL, 0x16E8B3AAFC231466ULL, 0xAE4FF39B4EA596C1ULL, 0x81FD11B973C6497FULL, 
            0x4A353EED71DBE8EBULL, 0x2875E28CEC58CD40ULL, 0x7DC7972FDF596DB7ULL, 0x4487E0C77D998A87ULL
        },
        {
            0xFC476F9D2C2A489BULL, 0x8EFA93A23D45D083ULL, 0x024764F7E3814E34ULL, 0xF7637927ED965C5EULL, 
            0xEAAF062B332F9D70ULL, 0x022F60F60D46B515ULL, 0xC52840BC2C97DF62ULL, 0x4C97A48B0240A868ULL, 
            0x7C15F50A51241875ULL, 0xD94DDE91633F8D61ULL, 0x2FF199B599226E3FULL, 0xE6D9EEDB0C009F18ULL, 
            0x18B729D84BC235D4ULL, 0xA1AB405D0D6FCB5EULL, 0xA0AE8F344D8E64D0ULL, 0x96A3D9A8194511E7ULL, 
            0xD5FDACC5B357B622ULL, 0xC3091848B8B2D0E1ULL, 0x7693A7A98E8A3922ULL, 0xBECD53803869C6DBULL, 
            0xC834A568B6374FEAULL, 0x49C15A7244E62DC1ULL, 0x24420D709BAB3BD9ULL, 0xE57BC2FB2BF9C033ULL, 
            0x77B3B6E9E2A91E36ULL, 0xD361A4D59431A3B1ULL, 0xD5D823BD8E50736EULL, 0xA22B8F858D512EB6ULL, 
            0x14DA50BB9A99839BULL, 0xF812956F935761FAULL, 0x1E902B4D649B26FAULL, 0x9CEF2282B11E61AFULL
        },
        {
            0xF4EE0C046B0A9C2BULL, 0x5A414AC1F9C3F63EULL, 0xD264F92795D0BDDBULL, 0x83B709F2A0A52893ULL, 
            0xA6C76227E75AEC41ULL, 0x552F715C535E2FB8ULL, 0x96130D3DB0BA65E2ULL, 0x080A09A2F055EC46ULL, 
            0x319DFCC5B33F1D95ULL, 0xEF78DD7D51032350ULL, 0x850B7105FE57262CULL, 0x3D9B79148F99D985ULL, 
            0x58DB25AC27DE8872ULL, 0xE4E8853DC8646167ULL, 0xA7D0FB45FC360E5BULL, 0x27187A46FA659ECFULL, 
            0x25C13F2C4B12D156ULL, 0xD2E1E2AC988BC771ULL, 0x65A46A77B30449FFULL, 0xA28DC47266878970ULL, 
            0x772F26B81B8B4E1CULL, 0x815C97328C55243BULL, 0x73C0AD0B808C92BFULL, 0x11294499B939A339ULL, 
            0xEEC8B06816D6AAB0ULL, 0x3F5676AF5DE4AE7BULL, 0x12FC72B777F4A6A5ULL, 0xD15FDEDA22F5587DULL, 
            0xECCFA4A5EC520945ULL, 0xEE52D3DE4B6816DDULL, 0x48ADAA3643E91C0BULL, 0x428D8A503DF3DA8CULL
        },
        {
            0x98635900D44B5169ULL, 0x098C9747D490523BULL, 0x8E71AB1C4C7D3B68ULL, 0xEC41C665A9047C7DULL, 
            0xA33D91BA0E0E0A4DULL, 0xFBDAE19FD9380ABDULL, 0x5FAA7FEC1EB4044FULL, 0x50E1B90B54F8A5FEULL, 
            0xBAF928EAED7E1CD0ULL, 0xFDE53F4D662AE3FBULL, 0x8ADF4178F9D7109AULL, 0x7F7632BE90553944ULL, 
            0x115E60690EEF6CB9ULL, 0x12EA8FAEFA5414A1ULL, 0x2F59489AC58B8E28ULL, 0x4D887FB64B12EF8BULL, 
            0xE49121A4139DF469ULL, 0x34B09AB90EE86DA5ULL, 0x3EC6EFA0595F0353ULL, 0xD05F3D18C4D38FC8ULL, 
            0x2C72E04BDED42A5FULL, 0x815A73BA0A99F7D0ULL, 0x01880E3040A4B9B0ULL, 0xD21B11ABE592E6FFULL, 
            0xF5515B8DA1F37A34ULL, 0xEE69C3D86ADF367EULL, 0x51E2939C3C6E8C81ULL, 0x74A4AC04429146BDULL, 
            0xD0C8ED3A173E2EF1ULL, 0x5935C3F2023B30EEULL, 0xE81037D45AB5D7C0ULL, 0x538ACD9BEE3EFDBFULL
        },
        {
            0xA889A262D15EC1D9ULL, 0x876E96857C6E942BULL, 0x9129F0A76236D570ULL, 0x91816BD054E9B245ULL, 
            0xBE009789BF717D32ULL, 0xEFBF7D8D1D99C4BAULL, 0xCCA9319ECEF62951ULL, 0x63C92F113D9033FCULL, 
            0x720391541CAE7840ULL, 0x28E7360C948FC869ULL, 0xE11DE08B337E9BAEULL, 0xA27E2D6417CA80CFULL, 
            0x7895FF7C0679FDCFULL, 0xC3311664F30BDCDAULL, 0xFC7AE1C598A8D4F6ULL, 0xEAB9AB0414F10B18ULL, 
            0x83F2170A629EA2BEULL, 0x334228B152C947DBULL, 0x4ECAE855A3F22A0CULL, 0xD091C3BFB0043C0DULL, 
            0x085863866ACD24CFULL, 0xD41B7943195467F6ULL, 0x163F00D528A88A90ULL, 0xDB540B01007567E1ULL, 
            0x0E20505934C467E0ULL, 0x67BB2235B14A5D48ULL, 0x47A26475E562C24EULL, 0xC4D633A95EC576BFULL, 
            0x901E616F53D02CBEULL, 0x0DBD4F8E1884A590ULL, 0x799BEDEF5146C885ULL, 0x9F9BE7FA16D093CAULL
        },
        {
            0xF611C9B648FF3D3FULL, 0xEE7DF1825E787856ULL, 0x7807E06B76F85572ULL, 0x31A67249A1CCC33DULL, 
            0x2542DCB097C3637DULL, 0x91B0173922A91966ULL, 0xCB63994F63190A2FULL, 0xB4F9A0A300A844A1ULL, 
            0x90B6C955993714FFULL, 0xF2C1FDFB3469BC72ULL, 0x8EC558769530E8FAULL, 0xA5B84E3F7BF05985ULL, 
            0x3E18C54B6476F301ULL, 0x6F6CB055B180C090ULL, 0xA7194D2372B3B3AAULL, 0xAFC792CD3E0C6C97ULL, 
            0xBE9F5CE92D656698ULL, 0xD94A9B93CBCF4463ULL, 0x41E19039358BC400ULL, 0x9A37228F6DD3F206ULL, 
            0x001EF19CA90528F5ULL, 0x5506705D14C09414ULL, 0xCC1E875ADCF1A0A0ULL, 0xC75E3068F894C142ULL, 
            0x3EEFBA21B6EC96C4ULL, 0x4CB70DD1FFCA2096ULL, 0xB7CAD2E55E3DE98AULL, 0xFFB6E851D914B238ULL, 
            0x60E02BE63CDC7020ULL, 0x35C9B2B5C63C51FCULL, 0x2C151B73E65973F2ULL, 0x68F0C46BDE8FB148ULL
        }
    },
    {
        {
            0x8C453B59DA60E6EBULL, 0x903111F9650F9155ULL, 0x4C066C14924D922CULL, 0x37D41CBDE2280936ULL, 
            0x75ABCFCC864887BAULL, 0x0A7F01CB911FE80CULL, 0x046B8C1C33B9BB06ULL, 0x71A38C3404EE9245ULL, 
            0xAE10D99174FAA79BULL, 0x8ED4CDD4BEC54AF5ULL, 0x807496356DD0F150ULL, 0x238B55530289C5E6ULL, 
            0xAD77F36B27E378A4ULL, 0x0A303A679D82DFC5ULL, 0xD08118BD67DF32F4ULL, 0xBD2E644121A41504ULL, 
            0xCED8E1FD7F177527ULL, 0x091FFDA9CEF0448CULL, 0x57CBD88A7BBD03C3ULL, 0xE8D1633178025385ULL, 
            0x5BB3900C56E71979ULL, 0xA3705F935D9CD28BULL, 0x89EE546856BDF0C5ULL, 0x7B12B66D0338D7C9ULL, 
            0x05CC7B4476FC3823ULL, 0x0DB19AAD3CAE4026ULL, 0x2799C807B4A07C7DULL, 0x2F9C3D736259B8F8ULL, 
            0x3111A617EF903141ULL, 0x6049517221C1AA69ULL, 0xF74DA6B8006243A8ULL, 0x551F2D4F2CC2C6CDULL
        },
        {
            0x53D730DF013171F3ULL, 0x98FD6DE0C8441B0DULL, 0xF76EE9ABA6F9BD8AULL, 0xAF96CA8176F3999CULL, 
            0xDA7E10A03D135F6BULL, 0x058558A58C50CFB2ULL, 0x40FE9650151C3CFEULL, 0x3C7649C408A78A65ULL, 
            0x4165E389BC894D24ULL, 0xAE028ACE12FD223DULL, 0xFC957C36F961CC75ULL, 0x9EBC4FC8203743ECULL, 
            0x7CDD8507C355B3C6ULL, 0x5222E4192E981FD9ULL, 0x3E6D9CC2DA68F71EULL, 0x086F76E3CA84BC4FULL, 
            0xD9D61B1DF05B7A30ULL, 0x7A80D01D054ED7D2ULL, 0x6EC4A05C9445739BULL, 0x286D280F890F3A23ULL, 
            0x447FA4A8EE5ED035ULL, 0x4BD9569E9F1CEE8CULL, 0x3D8F1E0EE0845436ULL, 0xC1B040D23F9CF5F7ULL, 
            0xDE3424FDCC5CD589ULL, 0x84BF5E8ABA1B2537ULL, 0x09AC7E624716CB1BULL, 0x545BDA0F6764288DULL, 
            0x8222336200C52FA9ULL, 0xDC3867027C5DA0D6ULL, 0x95EA7BBC42850D8FULL, 0x0146E7998B13C4D0ULL
        },
        {
            0xE7A8645C6352522EULL, 0x878E402403A4CE29ULL, 0xDA36CE070E556A85ULL, 0x0D4D5D95EE997B3FULL, 
            0xE4802113E4AC7D9EULL, 0xA3605F03AA4EAC35ULL, 0x475F2DD2ED06BC38ULL, 0xAFC278C638FD797DULL, 
            0x9012F81C780CEF63ULL, 0x98C66728271B7B96ULL, 0x312A1D9978BE4045ULL, 0x445CB2198AD5FBD4ULL, 
            0x9A2C97CC7E57D869ULL, 0x58DD9FA61D880D8EULL, 0xD91195BEB777F035ULL, 0xAF5F66FF32F6476EULL, 
            0xEC620EB69D5A70F5ULL, 0xF6E8E042D527C048ULL, 0xAC541E9D599A46C6ULL, 0x05E75B785DFBF503ULL, 
            0x79EC988E59B60052ULL, 0xA7FB0B9BD1A90385ULL, 0xE02B085DBDE8A337ULL, 0xE2F498B99B8B46BBULL, 
            0x0C1E465D9690D648ULL, 0x5C211CCBF7CCCE21ULL, 0x68DC3CFC681F7963ULL, 0x552A7B758DBCB1A1ULL, 
            0x1F33AD37A5053D7CULL, 0x255861C366C5D70FULL, 0x337B3F52AD506873ULL, 0xFA9852D987CA3EEEULL
        },
        {
            0xB39A60019E6905E0ULL, 0x5CC70AC02C8D2DF7ULL, 0xE4F33677220D68D0ULL, 0x7B9A274FAAB6B0F6ULL, 
            0x3C56BA5A972FA3D3ULL, 0x656AA151FD4D6D87ULL, 0x0B44EB2C5245E05BULL, 0x788D040EF6EF6FA4ULL, 
            0x941180709EB0318AULL, 0xC802F727E62A2F6AULL, 0x24160D6FFA6BE6ABULL, 0x02F677B4F84E7E86ULL, 
            0xEC895D330F5B1026ULL, 0x09C06BD6E509BE0DULL, 0x1AFE90DE6AEA1BECULL, 0x674BC091786AFCBCULL, 
            0x4FE3615D30614D8FULL, 0xE9835844D62019DFULL, 0x3B5D47E19E67FC07ULL, 0xADFD9292B8BEBE38ULL, 
            0x8F7691C15DE38C44ULL, 0xDD40D0C28893600BULL, 0xDB2702AA2250C3D6ULL, 0xC124CA33E0F949E8ULL, 
            0xFB255D63952A45F5ULL, 0x13036F97D28A4924ULL, 0xAEBEB754F629A160ULL, 0xBFF868EC124879E9ULL, 
            0x98344290D513FFCAULL, 0x256F52CB516C3F0EULL, 0x908D09745CB25DE0ULL, 0xD931F6F202D69D43ULL
        },
        {
            0x4C9F81925483093AULL, 0x8EA483D26F2267E4ULL, 0x2CA1389652EC24B1ULL, 0x47174B4442617472ULL, 
            0xCDFCC7C8A595166AULL, 0x4AC5CFD259412992ULL, 0xC813F40463B3578CULL, 0x1DA577BB6FAE169AULL, 
            0xF3804EC4D29D61E2ULL, 0xFDEAD3EE7DDA842CULL, 0x807380F44BB3265AULL, 0xB1BA14BF1211A5E7ULL, 
            0x50B13FD5C2E65565ULL, 0xF4F80E39A29270ABULL, 0x1F2FF0F91BD1CDF1ULL, 0x0F54715A8490F3ACULL, 
            0x575F86A40C840B46ULL, 0x25E8F182286871B4ULL, 0x574269125F80CFBCULL, 0xD184E83969436AC0ULL, 
            0xDC14EB4DA519DA16ULL, 0x9ED1DAC6EF51AA5EULL, 0x3E70ADD973C42F13ULL, 0x7C713316475AB651ULL, 
            0x940C192CA5711510ULL, 0x469E171C14983534ULL, 0xF7EF9B17C1871D66ULL, 0x305B0D96D9DD1589ULL, 
            0x1B4E0E1CB0DBBF46ULL, 0x05B5BF19C272FD92ULL, 0xBD1B616209736673ULL, 0x339B451BD3E8FA05ULL
        },
        {
            0xA994A947D93F082BULL, 0x3C3D098DB18F3233ULL, 0x1DEB0EF73608222AULL, 0x4C51236CAB689A09ULL, 
            0x9DDA778A4E6C0F20ULL, 0x675BAA18BEFAE5F8ULL, 0xA752A3C88DB891CCULL, 0x8A1B8CA69C627EF9ULL, 
            0xC1FB4EA31CEB6854ULL, 0xF0BE0C385AA863FEULL, 0xC6993AD861FE40ACULL, 0x56518188095B6847ULL, 
            0x8771F13D7362447DULL, 0x25793AEF436A0D7FULL, 0x482168FB094B06A1ULL, 0x2C5CB9DAFF7C260CULL, 
            0x26F0255E82500A55ULL, 0xFD1298C29CD1C2F9ULL, 0x2D1C00CBAF890DA7ULL, 0x4915E0A8581FF674ULL, 
            0x34D9861F8EBF8887ULL, 0x6611BC62D2AB3921ULL, 0x75228302FA07D3E2ULL, 0xB1A69C70A8EC7400ULL, 
            0x455A2F16D02BAA17ULL, 0x31E73210983F1ACBULL, 0x51627B4BFA27BEF6ULL, 0xE167343E30F316B0ULL, 
            0xD85E125ADC1F02E0ULL, 0x7030AF3E270FDFA2ULL, 0x3491548AC9E0149BULL, 0xBD4D3F5927381AD0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseFConstants = {
    0x0CA862F5DDD1BF6BULL,
    0x9F8C98E83ECAFE99ULL,
    0x85DF73F1F946B0DFULL,
    0x0CA862F5DDD1BF6BULL,
    0x9F8C98E83ECAFE99ULL,
    0x85DF73F1F946B0DFULL,
    0x832B02DF04E25CFFULL,
    0x7DAC2A0B3B078031ULL,
    0xF3,
    0x85,
    0x1B,
    0xFD,
    0x40,
    0x93,
    0xC6,
    0x8D
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseGSalts = {
    {
        {
            0xD12D650EB8475EEFULL, 0x93ED286D84ECC138ULL, 0x008111E101922BD2ULL, 0x15E5516B3DE4A055ULL, 
            0x4A8752EE5E513442ULL, 0x8EE168A77F69D7B8ULL, 0x24B6152B76E17FA2ULL, 0xD5D38DBFD7CA7D7BULL, 
            0x0B25EE450A7A085EULL, 0x6F0DCABC1E31743CULL, 0xAA48ED6FBA2D6005ULL, 0x98EEB703689D6B1FULL, 
            0xBE89773F967E55CEULL, 0x189770A78B0E3710ULL, 0x397B8953307E2D7CULL, 0xBFD23E7BBE7A44BDULL, 
            0x2ADB21276EC82E0AULL, 0x4A4A30F24AAE86B9ULL, 0x21B2FE97C6B3B2DFULL, 0x9864473A4B73A8D5ULL, 
            0x58A6CB9BEA5E76D9ULL, 0x9488A0DA95FF1AABULL, 0xDDAD6E0ED3D43CEEULL, 0xB9DE743BE76DEF63ULL, 
            0xED3066FD0EB5CFA1ULL, 0x740C568EFE9556FFULL, 0x0B967A3C1DEEFECFULL, 0x50F71B647DC5DFA9ULL, 
            0x492798F72E0E0977ULL, 0x48052F32FDFB41C5ULL, 0x5ED19DE7CD4A7154ULL, 0xEC2067725B99A97AULL
        },
        {
            0x3912110B27C2098EULL, 0xED35CB098EA4CAB1ULL, 0x2DEC874B55986CC0ULL, 0xC6991FA4BA24BCAAULL, 
            0x35E9C8CF97371856ULL, 0x4F13A9479D26F17EULL, 0x329AB7D1E00D752CULL, 0x9A75799392205D0AULL, 
            0x55E0033C4FC17465ULL, 0x0F6F2356C31262C0ULL, 0xB84F9ABCBA46FF85ULL, 0x47C4BEE4FF2DDA0AULL, 
            0x09ED63D5F95C1B0AULL, 0xFF540C83304BCB57ULL, 0x9FC4C142F510C978ULL, 0x0AB7391D30597F51ULL, 
            0xEB6B593C214F87DEULL, 0x05B933F00F6DA983ULL, 0xC6DA755BD6398A29ULL, 0x45234F93C75FB7CBULL, 
            0x2DB76B7C71DFE8C7ULL, 0x684E21D29AE5E29EULL, 0x95FEE72C9BD97A00ULL, 0xBB9C1A8A7580F1DAULL, 
            0x488BE9E0230EFB8DULL, 0x41380252FBE1B544ULL, 0x602385E0A878199EULL, 0x12DDE198EEB2C551ULL, 
            0x42AD187AAFBBA362ULL, 0xD0EE11B0CA6AB2DAULL, 0x34A431AA7C8AE558ULL, 0x89F51CD71BC5E5E5ULL
        },
        {
            0xA785F995E4921DD3ULL, 0x50A50E6E32F335B7ULL, 0x39FDB53698B497F7ULL, 0xB9EC76641187560DULL, 
            0x8BCE9E942DDE7067ULL, 0x4C27D7D3DA13FFE8ULL, 0x5DA5A33C38FAC1BFULL, 0x31528F9D5589F92CULL, 
            0xB569D40C55E5B0EAULL, 0x2FD711F1DB6E0953ULL, 0x4D5AFAC86817030DULL, 0xB5EE1F10F2E4EE3BULL, 
            0x3394489FB87C27F9ULL, 0x5C68D74834099723ULL, 0xD4CD9B87546E1B4FULL, 0xA96F00951B0BD517ULL, 
            0x7A374954322FC82CULL, 0x0E37340E1AE5FD8BULL, 0x7B91D6B98A3DC40FULL, 0x3C6E80EFAD9DE296ULL, 
            0x91B611AE4E85852FULL, 0xD7E9703FCF57985AULL, 0xDEEBB84718D236D8ULL, 0xE32C6B6591402CA2ULL, 
            0xA181134F5BEC6123ULL, 0x3F919FEBF886FC65ULL, 0x33C07D3AE0A1E1A4ULL, 0xF1CDE10C6C8C0AF0ULL, 
            0x9A129CF736E7459CULL, 0x0D499A609F613951ULL, 0xA5BB0C079CD0F894ULL, 0xC95168670F56B773ULL
        },
        {
            0xCBB416CC78729FE9ULL, 0xFD780CFD8DA4E7AFULL, 0xDA1426446E716532ULL, 0xB0BE71A13ADFC271ULL, 
            0xDBF8F7C6BB7973FCULL, 0x747B3F89B372D590ULL, 0xC949A3F99A00402EULL, 0x17F501336D51B03AULL, 
            0xC2588AAF49B8713AULL, 0x25D60CC6A61125AAULL, 0xAB1B7E204045A317ULL, 0xEA847750E05E63ACULL, 
            0x7174CA2109110DEAULL, 0x1FF5D589F81CD831ULL, 0xD0DAE188E831C891ULL, 0xC05DC86CD4BB4C23ULL, 
            0x2623F66BA76DC8B6ULL, 0x6B77B0EDDFEE5607ULL, 0x4213988C0E60DB84ULL, 0x27EA1889F62CE1C8ULL, 
            0x74FD33DAF6F0A005ULL, 0x402EA7DF78D8FEEBULL, 0x79D527CCC91A4484ULL, 0x8754375B569980D4ULL, 
            0xD49D9C8833595E72ULL, 0x133689B8E88EA789ULL, 0xBA8E74FFF1D07D7DULL, 0xB8914EFE4171CB3FULL, 
            0x06DBC29C6D140DF9ULL, 0x9D546DBC54E631B1ULL, 0x787A11C11D12A1C0ULL, 0x33BB89F8ECFC9393ULL
        },
        {
            0xE33DB5B6F7EA257DULL, 0xD1923E1A68172BD5ULL, 0x8A2E856183636345ULL, 0xC2A1E5D0271563F6ULL, 
            0x6004029FC516214DULL, 0xA4E14DFEA1348E8EULL, 0x27AB8BE8FFC69A68ULL, 0xF30540ACBEEE9942ULL, 
            0x6391F6E9555C3A94ULL, 0x13B4B71BA42A0CDEULL, 0x43ECCC78D87C252DULL, 0x5A56C117B8EA49BEULL, 
            0xF184C7C5A4CF5AC3ULL, 0xE315771030266E26ULL, 0xA3E5862CCA2D0C98ULL, 0xE80C99FB7ADE4FC5ULL, 
            0x8AFE87D6F2D76E74ULL, 0x8E9589E522C5EA56ULL, 0x42588BCD546670B3ULL, 0x1F31BBA216BC4E7DULL, 
            0x262BDBAF73934C80ULL, 0x71FAA9E6098BF48EULL, 0x56F45F53903D40BFULL, 0xF572ADEE466CA873ULL, 
            0x8A4142373C262465ULL, 0x13F30FD0FC5A9874ULL, 0x838BC9EC0EDA1C92ULL, 0xB9C746934B5AAD3DULL, 
            0x892A0730FD1AD088ULL, 0x07DCD51A806612FEULL, 0xB44305F19DA98EC6ULL, 0x31F7DFE4255E078BULL
        },
        {
            0x9C8A1C4A7A0B7DD0ULL, 0xC660F0E75BFADDA8ULL, 0x9004AC32AF9AAF77ULL, 0x41BF88A769B6AB2AULL, 
            0xA05ED13614B4CDBFULL, 0x8D8C3D42A20A799EULL, 0xB4E9BB7C961F46B3ULL, 0x729DD1BC8AEFD8A2ULL, 
            0x2F95337714F4B70FULL, 0xCB91B6A4C24AEE31ULL, 0x6D18990982F6816AULL, 0x3D645E2DE00DD3AEULL, 
            0xA977FDF2E2226D9DULL, 0xA6BE6520CDB4A2BEULL, 0xFDFE012A8027297CULL, 0x5F002B38BEF034ABULL, 
            0x629021EF0255193AULL, 0xDA2549041E92A412ULL, 0xC43AA88122F674A4ULL, 0xE7C1714216AA409AULL, 
            0x16248605A06DDDC1ULL, 0x418B5F5802E7294EULL, 0xE27A37A1E2599390ULL, 0x8DADDABFF61D80AFULL, 
            0x19D42B388FBE2B73ULL, 0xACF14FF3A27DCB09ULL, 0x388C3E0AC5BA3DCBULL, 0x148A1B6C31F128F3ULL, 
            0x5A0EEE3C9351358FULL, 0xCE265CA9B781097AULL, 0x52E9A55E37FAE511ULL, 0xC305C6ED06AD04A4ULL
        }
    },
    {
        {
            0xC464AA3E09EE46A6ULL, 0xC1D91BBDB5B2F7C0ULL, 0xD32D4739F6135DB1ULL, 0x5748E44A9E3925A6ULL, 
            0x461EDE7AB2C3E051ULL, 0xAA4E172073A04204ULL, 0x05119A13C79C115DULL, 0x84AA986CB32DC13FULL, 
            0x8918B0B4E7784F7FULL, 0x8DE29297794D3268ULL, 0xA4AA4A53BFF22E83ULL, 0xED0BCE3AA964B23EULL, 
            0x1023D4F6EFE54DBFULL, 0xF2F8060757D01FA7ULL, 0x017A7906F3A53FC8ULL, 0xA42B45F5D6DD2ED2ULL, 
            0xB90CAD7AE03D0C3EULL, 0xBEEF82397291A9E0ULL, 0xDD222D86952B210DULL, 0x128C18EC6B00235EULL, 
            0x84E33988B4512BECULL, 0x2356C264310FF8DDULL, 0xB868683CD48B5FDEULL, 0xB4C363AE352628D5ULL, 
            0xD24638160F21B982ULL, 0x268DF8846B1BBC2FULL, 0x1F0B9B275D90B036ULL, 0xF1E681B3180F6AE1ULL, 
            0xE39383E08026D9BAULL, 0xA3AE7CCC1FC8D2E9ULL, 0x112844C78D0F8734ULL, 0x86FA5B2D079D67F2ULL
        },
        {
            0x391392E4D87CF2FFULL, 0x3CC136A1497DB97BULL, 0x629439A9C593B980ULL, 0x417D8583A430E1E0ULL, 
            0xB4B9E27EBF0EC772ULL, 0x1F812E10711CEE52ULL, 0x482358D309FD8105ULL, 0x0073D1D16D0FF1F7ULL, 
            0x6B042DB09A8F531CULL, 0x9BD0FD55F25854D5ULL, 0xB00533802A53CF93ULL, 0x58B38A80C35EC793ULL, 
            0x252A50A32B9E8ED8ULL, 0xBFB4A1AEE3660BF1ULL, 0x07E4D3BF074F8879ULL, 0xDD961CA35F5344E7ULL, 
            0x0C99A0229FF1E80AULL, 0xBA9EEFF05EC66D51ULL, 0x16A8651E8B940281ULL, 0x5D457A6471665134ULL, 
            0xF71EC51A6D49406DULL, 0xE0C688C124748681ULL, 0x6B96A1790BAAD7FBULL, 0x0C0116AFDE845D15ULL, 
            0x2A4B6BF71FE54B62ULL, 0xDE6698714C1F8933ULL, 0x655200F12810B2D2ULL, 0xF53967FEFD5A1A5BULL, 
            0xA846F6ADE54C9F3BULL, 0x7282DAB12E4EB289ULL, 0xE9EBAFBC0C161021ULL, 0xD20002AC134C7E2BULL
        },
        {
            0x43CC5FD39FECF1F4ULL, 0x5371968DAF751C6AULL, 0x61E09A56858B7CEFULL, 0x99EF1433D01931DDULL, 
            0x1DDF32606C2DBD4EULL, 0x4550C0DA29D8916FULL, 0x846CA07BB9B4352BULL, 0xE56C56FE4F88258FULL, 
            0xD8F5A58F53B149D8ULL, 0x3A1B477443756E81ULL, 0xAAD3C845A9416891ULL, 0x8F6C7C74118EE5E8ULL, 
            0x9801D4E767EB6D99ULL, 0x9D7E46A092F53C7EULL, 0xAF435BFAE5125E28ULL, 0x766FFABEEEDA72F3ULL, 
            0xBBD2900F965B83B3ULL, 0xBC926375ECAE5786ULL, 0x053C05DAE7774CD3ULL, 0xCA3AF155A2DD3AAEULL, 
            0xDB90DFB8E93821FCULL, 0x7EB23880E88C3493ULL, 0x5BDD5B6BB90272BFULL, 0xEF83308E27B5316DULL, 
            0x490D0B6E5E62C62FULL, 0xF0AEB51C9355955DULL, 0xB0ED611D868B96D0ULL, 0x43239115E90C0E9AULL, 
            0xC84B029A5359DD62ULL, 0x01638860C5EFCC72ULL, 0x58B6B4BC3E1E2161ULL, 0x174E9F4D0508DD15ULL
        },
        {
            0x9ED33A3B9535A710ULL, 0xAE1F8CD4795780BDULL, 0xFFA76BFBF4272DB5ULL, 0x507D2D1C564C1F76ULL, 
            0x11C9099D37EB527BULL, 0x76B1F3E4FB370C84ULL, 0x6AF7B20CDCDA7838ULL, 0xD197297D8F4131C7ULL, 
            0x09DB07F0CD095060ULL, 0x021302FC237816E0ULL, 0xF167FA8ECAFEF1EEULL, 0xE077BCACC67AB5F2ULL, 
            0x7196175575368194ULL, 0xFD3A9727E4566CCCULL, 0x49A98BD8E45AD4D5ULL, 0xA451B7A4F57E302CULL, 
            0xCB762A73BB5AAFA6ULL, 0xB7463D7F5FD3B938ULL, 0xEF3FE2BFB36DB626ULL, 0x74051EB20D34DC93ULL, 
            0x3C0CB5E72961D34EULL, 0x83BABA24A08CFAE5ULL, 0x8B06E77BAC26C5EDULL, 0x6080146A44B41274ULL, 
            0x67205C1E56593F12ULL, 0x2F2C428E48E49556ULL, 0xD0FB7291672BC34FULL, 0x0485FDCB64FED0E4ULL, 
            0x230E7C17543AE58FULL, 0x8F647999966B05FCULL, 0x2BA2050C830FA79AULL, 0x76D2C7217A4EAFA9ULL
        },
        {
            0x22F3A6B6C7263F5CULL, 0x7E173E4C5C04D727ULL, 0x098140287C79C4CDULL, 0xF0712D99D137C972ULL, 
            0xE06E63368CA4F0E6ULL, 0xE4CB241216293D94ULL, 0xDB63AED96BED527EULL, 0xB4B9E804F28ED6EFULL, 
            0xAD0E199FC70AAF38ULL, 0xED9CAC31375121FFULL, 0x6C4725269F669FD9ULL, 0x313A7FAFF88AE2F6ULL, 
            0x9637C9CDDD8700AAULL, 0xCBC74E044E82018BULL, 0x5934346DD6D99133ULL, 0x460A74E9C7D910A1ULL, 
            0x898A4B499F1612B7ULL, 0xDF125143FF4AC936ULL, 0xDE51BE25FA89A7ABULL, 0xD1F331C911733DB8ULL, 
            0x154E3F125873FD93ULL, 0x94508E11736D3BBAULL, 0x4AB58166C76DBAB5ULL, 0xFB824F0BA02A04F4ULL, 
            0x5E08DF17C32CA72DULL, 0xD11C1E123BE62931ULL, 0x5B3B2ED89CFEE301ULL, 0x278216C86EAF7547ULL, 
            0xCB2648D20C816F6EULL, 0xD694A26AB766733DULL, 0xC7B0F66C8F39E240ULL, 0x5585CDF4367ED3CCULL
        },
        {
            0x6C67A6053B604CCCULL, 0xAA870588BC1CF6DFULL, 0xF6F3E625432A7F19ULL, 0x946540633151407AULL, 
            0x051BDE3A8D579193ULL, 0x6CEA7724DB3B9168ULL, 0x385DF91FF914CD13ULL, 0x6288CC7D3FE2D177ULL, 
            0x09354F176091FB5DULL, 0xE9D28628A783DC07ULL, 0x6050F3064C9FBE3BULL, 0xF24CB2F873E3111CULL, 
            0x2B953EF4A0304C12ULL, 0x9B5DC7B0DEAD01DDULL, 0xD9D641B5DBA69136ULL, 0x20E52735A5989049ULL, 
            0x2043FC61D3641D57ULL, 0x087DF2071B62196DULL, 0x8DD9FB8650B580C4ULL, 0x10B312373259C928ULL, 
            0x29FF91F64295A024ULL, 0xED9907CC3B15BB65ULL, 0x1F7F0D153686C267ULL, 0x6021C3A86DA1BA17ULL, 
            0x5BE9C5904075FBF8ULL, 0x735D8BBBD7B1D7A9ULL, 0x4558D25B0DAA854CULL, 0xC4A572D9CFBD905EULL, 
            0xDA4B9F4FB3956970ULL, 0x062772B7A46BEB51ULL, 0x2F3542A7306F6CE8ULL, 0x60C766D5FC9FE42CULL
        }
    },
    {
        {
            0x4B8D53BA56BF4CEFULL, 0x0A75E9C4DDCE4741ULL, 0xF4BAD3DC93B41602ULL, 0xAF4914FA6029E023ULL, 
            0xFE4A9C6351B21724ULL, 0x156420D6340D97DAULL, 0x9E4E51F380A57046ULL, 0xB26BDD95475AD57DULL, 
            0xFDE9E46E5DBE3867ULL, 0x95CDF16C0B4BB3F5ULL, 0x3BA74F5D733343AFULL, 0x05C668BF0EB2EBF7ULL, 
            0x9B1EFC4CC360D27EULL, 0xE1BCA149F66DD814ULL, 0xDDDA961685596239ULL, 0x00ACD11B36D47F1DULL, 
            0x29CC9B0AD04F9232ULL, 0x0C545EEE71AA8E23ULL, 0x69172DA2592889B6ULL, 0xD3B5CFF429F1DF3AULL, 
            0x377679A555F8C9DFULL, 0x0737A51FC2B1A9F9ULL, 0x7703F96E750EA9B9ULL, 0x606F55C4D167BE27ULL, 
            0x4942E6C8AC96238DULL, 0x8A664CB735758759ULL, 0x6FA08040119CE0A0ULL, 0x998F0E825D0184E8ULL, 
            0x706EA3167647A9A7ULL, 0x54F44734F45CE97EULL, 0x242E9F6666DF45CDULL, 0x8AED34941671E887ULL
        },
        {
            0xC0A83F8787C19F6AULL, 0x51F90D46BD35E74DULL, 0xC3FFA0B53F2076C9ULL, 0x8F4AFFCD8F88A707ULL, 
            0xEF45001CEFEF7E96ULL, 0x269122A005B9D6CBULL, 0x8F6DFB04032C0EEAULL, 0x31F3BBF1CAAB7EB9ULL, 
            0xD058A451A804CEF5ULL, 0xDBB40F9DDE93B9E5ULL, 0x799B447933A32547ULL, 0xD79A4C2200ED8F6DULL, 
            0x5F15A1744848F949ULL, 0x4061CE6CCA20A65FULL, 0x479306726CE723A0ULL, 0xA3E716B274811228ULL, 
            0x87EB04CB7ED4417BULL, 0xCAEB6CE35DF069E6ULL, 0x12A527E18AF56392ULL, 0x05703C8A99224974ULL, 
            0x46CFA0891C510AF8ULL, 0xB6353CB65345CEB5ULL, 0xC5642A65ACD8993CULL, 0x0A318A6D74EA6B9AULL, 
            0x21BDDC3743FC1B24ULL, 0xAABB372C4716EF7AULL, 0xA8C5AEFE58DD2682ULL, 0xB2B1799DE83218ACULL, 
            0x2A01AC6876D0A82EULL, 0xBFC103A8A0E943FBULL, 0x7CFD8837C1919D91ULL, 0xE7668055941605C0ULL
        },
        {
            0x9F6383F5D1848C0EULL, 0x0479B85D0C9450D8ULL, 0xCFDC79085D0A116FULL, 0x490A54C5F18D637CULL, 
            0xACDF41B85453589FULL, 0xCF7A15FD89B29E4AULL, 0x812C27D54874C99DULL, 0x13A5F6C42EC0752FULL, 
            0x788D13EAE4191C65ULL, 0xD3868877C177F3F5ULL, 0x4312BA4FEA7AD4CBULL, 0x69E94FD55D6D7BA1ULL, 
            0x599D318EC52EF1C8ULL, 0x412815D26A084158ULL, 0xB856A399402841E5ULL, 0x4C7737AA976F18EDULL, 
            0x740E614DFF369336ULL, 0x992DDC43F4D5B899ULL, 0xD929BBD863DD9C90ULL, 0xE88EB25B59E52D06ULL, 
            0x89FF3932279C493CULL, 0xEFCF85635DBDB0EFULL, 0x908ECB44E041D5D7ULL, 0xFEF7E45BED47FC45ULL, 
            0x6A3483B4D4014DBAULL, 0x844A1BEBF6A5EA94ULL, 0x4B0290410E3437D4ULL, 0xB3F8B00BCB687B58ULL, 
            0xE28DE43EC85A128FULL, 0x9487779D07273A3BULL, 0xC78122F8F0AFD139ULL, 0x50CFCC74F6C68699ULL
        },
        {
            0xE9ED0036FF765DE4ULL, 0x15CDDC78E4C44B9AULL, 0x8700A4203B658B30ULL, 0x7DC99CB4851F1192ULL, 
            0x6D0D39087614C82AULL, 0x8B9A21EA912BC6E9ULL, 0x896422BFF8D26445ULL, 0xD10969E91610930BULL, 
            0xFC2D1B825EE8C54BULL, 0x6F8CA18CEBEB439FULL, 0x3DA87522E1B550DAULL, 0xEED6B291831BA56CULL, 
            0x5CD4197624781FB1ULL, 0x0BDAFBAC5E7F8B12ULL, 0xDA0773393D26DA16ULL, 0x19ACB9895FBF123EULL, 
            0x6C883EF6396AA6F1ULL, 0xC9463ECD31145412ULL, 0x9138CD9E79775F6CULL, 0x8511105DE7CA9AE6ULL, 
            0xC0AFE4E84D98FB92ULL, 0x0ABA87E3D72ACA38ULL, 0xDAF7234DC3332C51ULL, 0x291B63BBC5DBC829ULL, 
            0x30A883BAA81B25EEULL, 0x4FBA0FCBA9D125EDULL, 0x88D7D630BD71AD9DULL, 0x575FB712C3B5D7C0ULL, 
            0x68810D6136B88003ULL, 0xF68A9CAB1FFEBF03ULL, 0xA557C711C22F7395ULL, 0x88520614413983F4ULL
        },
        {
            0x225DB973C26F6C8CULL, 0x3803ABC374DBC276ULL, 0x723F6D7BCA959372ULL, 0x6DD5EEB74B16E43CULL, 
            0xFCEC76B770A321BBULL, 0xE9EF695FED41A2FDULL, 0xCD059F86C698D0C3ULL, 0xB43B02676795477BULL, 
            0x93E0C47157DEF757ULL, 0x70F5CEDD070B0DCEULL, 0x744839E347561888ULL, 0x0A7B2866BDBE2F26ULL, 
            0x206B2458A31DA573ULL, 0x8A7601CA8ECEC248ULL, 0x010846885BC7CBDEULL, 0x32D2BBCA6346BCE8ULL, 
            0x3CF81796F0D268F1ULL, 0x1D3289ABE8F939B2ULL, 0x22E3FF488D071154ULL, 0xD683964E113AC1B0ULL, 
            0xA734F0E777EB9A92ULL, 0xBB8E74C63BC4DD1AULL, 0x1A2B779C4822C6CDULL, 0x083DBFD4FE3C0498ULL, 
            0x6C2AD2B0938A7792ULL, 0x0450D396BE6B0D88ULL, 0x92D26352D7FEC3AFULL, 0xA30665990E4C8091ULL, 
            0x8EEC09704A0E3306ULL, 0x5B8B1185C3A84B84ULL, 0x2389D77F8CD249E8ULL, 0x127163FB620AAEA9ULL
        },
        {
            0x417AA54B244AD5C0ULL, 0x5527234EE20256AEULL, 0x3F452BBB893242F5ULL, 0x785A30BDFBDCA27DULL, 
            0x75CD38EBF8A3C57CULL, 0x35AB9B534EB344C9ULL, 0xE1C23C4EB914117CULL, 0x872A63B1EA87671CULL, 
            0x79F912C87BEDF15FULL, 0x4EEC630308E4B8AFULL, 0x2DDEBA2A8E7D02D8ULL, 0xCDE7F2ECD0DA55D9ULL, 
            0x8E440DADE4386C6AULL, 0xB354D3080D945681ULL, 0xFA31058179660616ULL, 0x6A433C0DF3D87336ULL, 
            0xF3D4BFCF62C946A0ULL, 0xD956F4FB8E26F426ULL, 0xBFFE7982C0A6E454ULL, 0x3FBA61BB0F68ECC1ULL, 
            0xD1DF845CFC0A708FULL, 0x6BB735C84E4F4432ULL, 0x19E487462A416C4FULL, 0x4BF80A0D790A07E1ULL, 
            0xCDEE2F332161E190ULL, 0xFB397EA63C7D45E9ULL, 0x8C5E963616CDFD91ULL, 0x7C99EAE8CE584528ULL, 
            0xBBF399F61CD9D59CULL, 0x61725109D0ACA7D7ULL, 0x9AC165FD1F37437FULL, 0x02BD4F57868E3500ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseGConstants = {
    0x9F4637AE6171E0D9ULL,
    0xABDE05E9F41A8563ULL,
    0x946DD9BEDA0994F4ULL,
    0x9F4637AE6171E0D9ULL,
    0xABDE05E9F41A8563ULL,
    0x946DD9BEDA0994F4ULL,
    0x66E3B9F862E057D9ULL,
    0xABF327B8BD7CCA62ULL,
    0x48,
    0x55,
    0x5B,
    0x8C,
    0x49,
    0x93,
    0x2B,
    0xC9
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseHSalts = {
    {
        {
            0xAF2E6F543ED7E29CULL, 0x75A4B8D4953B5776ULL, 0xEB88093EC6777AC4ULL, 0x8523CB1D1D09F012ULL, 
            0x2E90A01F8DFF3DC6ULL, 0x97FE9BC325A0DA0AULL, 0xD39E0F2417CCCE8CULL, 0x19796FE9175D2291ULL, 
            0x90FAA71E1D712FF7ULL, 0xE4E35BB2AA67C30EULL, 0xD0E2A7D97B821200ULL, 0xA02FD530B5CB8A2BULL, 
            0x4E944ED4FDD90312ULL, 0xCF642694B065EE13ULL, 0x32B962AA51DBF570ULL, 0x1E993955FAC63722ULL, 
            0x05F7EBEFFDB46AFCULL, 0x55838EDF8F84E55AULL, 0x4714AE20ABB73EB1ULL, 0x80275E39697EDC56ULL, 
            0x55FDC738B992B28EULL, 0xBFA4C7C6B29FEE36ULL, 0xCADEAB13C0ED3414ULL, 0xA2E86E29E9AED5A5ULL, 
            0x2F13575A24C1FE0DULL, 0x230EC18357EA15E0ULL, 0x073C37175050DE08ULL, 0x05CB4F59237C2783ULL, 
            0x9A0BCA5C91B97E6DULL, 0xA4D1D96DF69725A0ULL, 0xBD03B4ED4FDF4941ULL, 0xDEF5C82F079AA869ULL
        },
        {
            0x83C4158615FB2A6CULL, 0xB73E0EC155B8AC81ULL, 0x9DC675389663CBD7ULL, 0x37914A17FB03AAA8ULL, 
            0x8FE960CF5432EFCBULL, 0x8797BFFE010C42B5ULL, 0x4B4A9E14985A03E9ULL, 0x788AA88FF8D0CAB0ULL, 
            0xFE33D77E94CA619AULL, 0xE40EEA3510F6B08EULL, 0xCFF191B7BFFB06F6ULL, 0x8A49BF31EDB00DD4ULL, 
            0xF5CBE6D168611B19ULL, 0x78E044D694C97C72ULL, 0x3D60910BF7EA71CFULL, 0xEB1DA651693FCA3AULL, 
            0xFBD78690BE4F646EULL, 0xB8E1AFBA44B019FDULL, 0x38F636AE61C6BC51ULL, 0x6BAEB86BFC90C57BULL, 
            0xBB82ACDC5E2BB949ULL, 0xC9DE8D42D76D80C5ULL, 0x8978349AE2988789ULL, 0xEE0F24FFC47FE4FCULL, 
            0x7F30847B026D87E5ULL, 0x66E68ABBB33BE9CAULL, 0x0162B702DA1D888EULL, 0x4F11E1C4AD31C26DULL, 
            0x888CAD08FB2CB3D8ULL, 0xA016219CDC28B13EULL, 0xBD68E45CB9DEC717ULL, 0xC586CF34AF213A25ULL
        },
        {
            0xAADA32ED561710E3ULL, 0x2B24314FD6F0357EULL, 0xF63468A17F71879DULL, 0x9D5BEAE032D033AEULL, 
            0x3D348762DDA2F65DULL, 0xD6EC50DBCD35D700ULL, 0x1E813445055041D8ULL, 0x420EB2614CC1D2B9ULL, 
            0xEC4A52A20EE65C5BULL, 0x27CDACE894D8AC80ULL, 0xD677226C4B115AD1ULL, 0x58764E7FAE7F27AAULL, 
            0x0DB1024ACE5500C7ULL, 0x96BD58E0C8E33253ULL, 0x3E5AD97DD5C8D06AULL, 0x5CA49BB3B48CB059ULL, 
            0xB4D260753E22DC0CULL, 0x12F6FB43A43A2509ULL, 0x68E7CAC8D304AAC0ULL, 0x0A8EEAC37F4A9AD9ULL, 
            0x25F4AEF5752970ABULL, 0x874308A126217AF4ULL, 0xAC254C87DD3D7D0BULL, 0x2B0D7963EA6697F6ULL, 
            0x1EE9B0C3A5D6F9F0ULL, 0xF212F5A380021741ULL, 0x1A7E7C9B4086B56FULL, 0xD9C8AC316CE43662ULL, 
            0xA7354AC7978C768CULL, 0x8045E67C02A98CC8ULL, 0xF31DD8EBA5534014ULL, 0xAA985521D50FAF4DULL
        },
        {
            0x9FAB5317DE254AADULL, 0xE1070295AE51E4BCULL, 0xAEB3918B327CAFF6ULL, 0x40EAFF20D370B8FCULL, 
            0x47BC72AA2E85EACCULL, 0x21090F2C4F902E13ULL, 0xFD1C1F804A6B6957ULL, 0x2D7D58A321D1CA56ULL, 
            0xFA04830B73744678ULL, 0x82183F6A76CCCD9AULL, 0xDD09A9E78C741239ULL, 0xF9C35C9F7B321C26ULL, 
            0x0CB0F0061173B9B0ULL, 0x5D2799B9CAB58381ULL, 0x9EED67315E77FB8CULL, 0xE4E9C641987F6D05ULL, 
            0xC2F9D3241F06A05BULL, 0xD16639C33234D85FULL, 0xD803DFD3114BD802ULL, 0x04DE5C05BD743EE3ULL, 
            0x95BDB2352BA1418EULL, 0x98BABADD89E6DCF5ULL, 0x54EF8648DEF8FB41ULL, 0x5009B7CC79403F29ULL, 
            0x38FF5A1F8C47B0BDULL, 0x5FD446386344A2C3ULL, 0xD0640B318F50A9B8ULL, 0xC58EEABDF90C6BA1ULL, 
            0x30CC9A66DD4E2A7DULL, 0xDDED4332BB1D3A48ULL, 0x07B2B80AAFECF75BULL, 0x773A44367CB3B680ULL
        },
        {
            0x5C67860BFCB2E160ULL, 0xC026458D0F5D497AULL, 0xBF66268C9332F77EULL, 0xB270C04037E6DF89ULL, 
            0xBB5D10B837931EBCULL, 0x5C44D2B3B4F57781ULL, 0xFDDAEF39A1ACA11BULL, 0xF50FEAF53E926050ULL, 
            0x649631BFBB2585CFULL, 0x9311D5A85D416A5CULL, 0xB3CAF925C272559CULL, 0xC20DE3E73FC737E7ULL, 
            0x112AE20A6AF08E7EULL, 0x64F03E70F033052CULL, 0x99D2DAF60D3D3D61ULL, 0x61D44B7421606AF8ULL, 
            0x54CDFD02791965B2ULL, 0x1C79BFB9D8BE1EA8ULL, 0x79022838BDCA0C1AULL, 0xD1FF6628A1379017ULL, 
            0x004960219CE39272ULL, 0x814BB1F55ECD86F9ULL, 0xD4062CA726156C4DULL, 0x6DF1C3A0AD2B39D2ULL, 
            0xEE0AC3EEAE6B6527ULL, 0x0182423639D9A885ULL, 0xCD12A248B30D4004ULL, 0x9614BCAF094716E3ULL, 
            0xA13B70E259D3E7EFULL, 0xE5FA6AD3EF432286ULL, 0x640959A39F00205BULL, 0xFBC41A771B777F12ULL
        },
        {
            0x8EA82F92C3AB89A4ULL, 0x581B62A0129FFBA4ULL, 0x9665D00DCDAFBA35ULL, 0xE227DCDD58C743B0ULL, 
            0x1446891A33C8D93CULL, 0xD2C1FCD64529398CULL, 0x417CD0C3F6DA4749ULL, 0xA6279AB8378AED87ULL, 
            0x4871477F0DD5EF55ULL, 0x4C7E60D4509C8AA7ULL, 0x6B39D87FEA5B3C56ULL, 0xA6B3C1571AEFD34AULL, 
            0x9DE6A1996FAF2B4DULL, 0x00AD4B7D355913A7ULL, 0xB1150618907AA951ULL, 0xDB97F813B0E6E4AFULL, 
            0xE1B4E7D960244C7AULL, 0x96A0C88A649DCE6BULL, 0x36241C93405BDCDDULL, 0x19F51E71F0809037ULL, 
            0x33446683DEC90F78ULL, 0x1DA6C86653E59B7EULL, 0x2C41BCD61F203D2CULL, 0xC4CC51FEBFA4C930ULL, 
            0x6B2373046BDBE109ULL, 0x133C709C128DF93FULL, 0x59EB66DF15C3BFB1ULL, 0xA137C13EE0337A77ULL, 
            0xEB2A3F4C25DAA5A0ULL, 0x88B7A6CC072D67B1ULL, 0x384B90DB319E867BULL, 0xBD8EEC24B0203ECBULL
        }
    },
    {
        {
            0x3D2DDB2C62218E28ULL, 0x856EB9CBD0D674C1ULL, 0x3ACB571DBE134649ULL, 0x980D96CAC9906399ULL, 
            0x0BA4D64141DE7AB5ULL, 0x5E24F9CA89BE1908ULL, 0xB33CEFB488DFF0BFULL, 0x9C82D6CC5B0DFDF1ULL, 
            0x0552070AFEB6571CULL, 0x8A209D1E72E8AD61ULL, 0x66153247575CB7E2ULL, 0x52C412F0C28E09FAULL, 
            0xB16E17ABF096FEFBULL, 0x3875BB35BED31D5FULL, 0xE42F86D9EB315561ULL, 0x8E506CE4B8A97D42ULL, 
            0xB894A2E490C29169ULL, 0x5835D57436DC71CCULL, 0x55560DBFCCC92742ULL, 0xFEB9814BFBEAFEF6ULL, 
            0x49A6B693C71AFC79ULL, 0x369C319C55CEA248ULL, 0x0B6439201E4883BBULL, 0x329B3C8B5347974FULL, 
            0xA76B7C2AA54E6712ULL, 0x9AFB00B7CF5C9AB6ULL, 0xCE7ECAF8DA20583EULL, 0xFCD4CE7BB7779797ULL, 
            0xDE5500142D83C06FULL, 0xC6ACE012BA89FCB9ULL, 0x6DCD9F71E8EC2815ULL, 0x613CF166AC0F7638ULL
        },
        {
            0x985C4F4F00588CA0ULL, 0xEE318B551EE38CF3ULL, 0x7BB4CE2D5137923DULL, 0x12754213454F32B7ULL, 
            0x47B39C003E9FD5CFULL, 0xB35875009E3E1A06ULL, 0x6612E37A882C82CAULL, 0x6CB8896047A84C1EULL, 
            0x3B409290746AC500ULL, 0xAE7AABEEC3EDD7E8ULL, 0xC3B48956FB571BABULL, 0x72F5746892943443ULL, 
            0x7BAD9A2B38AF08B7ULL, 0x8AC4B12FE948C33FULL, 0xEA8AECF181843047ULL, 0xB13B3DA5C8230A2AULL, 
            0xA6F3DCD77D38A1EAULL, 0x5C3127209CA4C7FEULL, 0x40E955C321A49B5DULL, 0xA60460E41CD8BE32ULL, 
            0x071FE48F24CC0ECFULL, 0x4DCA667E0FCEF496ULL, 0x5D9EC1355E2C9047ULL, 0xAC5171C47647D228ULL, 
            0x0DA34275752A9FEAULL, 0x70C3CCB109EBC728ULL, 0x7581820C95EB4C7EULL, 0x8A9957EE148D48BEULL, 
            0x4B2F7D86D3DF31B5ULL, 0x5C7B9EAB8F33354FULL, 0xE31E63089D2381ABULL, 0x6BB6A99FF80B1AEAULL
        },
        {
            0xBC3CD61071ABD722ULL, 0xF1C2AD3BC5A56ECEULL, 0x213EE4F0307B46B1ULL, 0x4F18568D15B6092CULL, 
            0x3B355336049AC821ULL, 0xAD43483CBEACB186ULL, 0x2F39C854CB75C5EFULL, 0x6804ED964B016D4AULL, 
            0x92499CE4D13BDFEDULL, 0x266BB1DF842DD7BBULL, 0x24D4009E82F34992ULL, 0x0F317F5B7F19899AULL, 
            0xA6E55B16C846DC45ULL, 0x923BA5CBBD9FE69DULL, 0x7DFEDE0EC1961E6BULL, 0x28DEA06F26DEEDBBULL, 
            0x0F559E8C6B7F2FBEULL, 0x0A375BDFC017CC62ULL, 0xA0942B3354D22DFFULL, 0x6FB0BD4930BE58BAULL, 
            0xA2118B3EE8D690CDULL, 0xC08297B28371CB94ULL, 0x1EA206AE6AE69E8EULL, 0x730D46C317F58864ULL, 
            0x2302F97D5D7F6D04ULL, 0xE33CEF999B2467F3ULL, 0x6288F849485A5735ULL, 0xCCCC08CC6351BA1DULL, 
            0x770F5E78B9D55255ULL, 0x92DA5A13665A0FFAULL, 0x8C7B47B2CBDE36E2ULL, 0xBD6553B3C27C4BBFULL
        },
        {
            0x07FF329BF52DC6D0ULL, 0x844E4A0506A76243ULL, 0xA6758CACC966B8E1ULL, 0x064C9BF17E074471ULL, 
            0x356BA215A1C70054ULL, 0xBC00505849B758A2ULL, 0x496FA04D35F0491DULL, 0xF365DE12D78FD07BULL, 
            0x1EE85EA5F9B7AA20ULL, 0xF5771011B9D1C3F0ULL, 0xB0669A8EA6F536EEULL, 0x3729CBE63351C7CAULL, 
            0x3A282BB7CD056387ULL, 0xB9B7B6DCA4E12548ULL, 0xC8D264630BDDA500ULL, 0x2870608A57C8A9FBULL, 
            0xB7BAAF0E9EBA645BULL, 0xD6EEC21E651B5530ULL, 0x7592BF8D04D03DD3ULL, 0x0F2BDB8B36061B0DULL, 
            0x8E1C3D820EE40326ULL, 0xFA93F656C1D0061EULL, 0x00469189498E1F3EULL, 0x89C98BCB4E3B874FULL, 
            0xAC169DBA9E7FDE2AULL, 0x883B60BA0911AEBCULL, 0x7D03C07D8B32A923ULL, 0xE3E359A159BCF4DBULL, 
            0x4792732878F6C5B7ULL, 0x76073B44E846C054ULL, 0x6BC3E8B271F6F48CULL, 0x7A7A5C654356CEA5ULL
        },
        {
            0xA59C6BEF216EA5A8ULL, 0x9AA245C6D97D7D2AULL, 0x1C29AA7DEAC77FC8ULL, 0x68C8A3DC233E70E9ULL, 
            0xB9E63FD26CBBDD3CULL, 0xC4E0B087A4DBC244ULL, 0xED58A9F5EDE486E2ULL, 0xB652D2E99770C761ULL, 
            0x645AC840AC48D439ULL, 0x967C8A84ACA020BEULL, 0xFD128129114A7633ULL, 0x430D6D39FFD5552FULL, 
            0x8D114E4C10974B58ULL, 0xF724C0A9E335F260ULL, 0x6CD7571A691DB43DULL, 0x28DE4610F7D97E7DULL, 
            0xE939F484C2748CFBULL, 0xAC9939212625B9B2ULL, 0xAAF370336DDB2EB7ULL, 0x528407D782E316D6ULL, 
            0x3845760F5F5BBE86ULL, 0x067ACCA86362E30CULL, 0x9FA6B7633D63640DULL, 0x896A956AF03AE35FULL, 
            0x214327EFD6BA8C95ULL, 0x1821CBD692DE5EF5ULL, 0x32A970B4D33B754EULL, 0xD5CE4F10534F80D5ULL, 
            0x5C519C2F37F58CB0ULL, 0xAD28D1D6BFC36F01ULL, 0xA48F1747C54FE68EULL, 0x2D4DD55453B9608CULL
        },
        {
            0xE2A77CBE88F864A9ULL, 0x6C04374C1EFB7DF6ULL, 0x9355338D9B093B15ULL, 0xA96DBA5467F28116ULL, 
            0x6B3905E3C5DDB9FDULL, 0x1BCB69BEDA5EA2B4ULL, 0x4C4AAC3DCCB4CD7FULL, 0x70852C8F6F5E34C7ULL, 
            0x7FDF41093B7E11E7ULL, 0x88EDA751F40541BCULL, 0x709FE20936197B09ULL, 0x7D202CB2C51AECAEULL, 
            0x8236483111F29F9EULL, 0x90EFD2AE7644B13AULL, 0xD3CB6317D4B4546CULL, 0xF29C40B9D9914596ULL, 
            0xD75AB84CD84A69B2ULL, 0xFD5DD2F492DEFC73ULL, 0xCE33F328735797A2ULL, 0x89A213823F305A8BULL, 
            0x068034F4C79A57F2ULL, 0x1343701944F170ABULL, 0xDEEEC4CAC8B73492ULL, 0x6D4DA95E84E7DA0CULL, 
            0x17F3667660941E28ULL, 0xA090E1B58D985EDEULL, 0x40DF907184037052ULL, 0xCB9F9891C619D016ULL, 
            0xF72050829972E3FDULL, 0x13BA34D299E9E3F5ULL, 0x25866BFF8398D6CAULL, 0xE6570E61BD9D4ECBULL
        }
    },
    {
        {
            0xB8853D60788A8E3BULL, 0x3172E4D0EC994855ULL, 0x9FA208070197358DULL, 0x22763C963011C025ULL, 
            0x5907937C060E54A0ULL, 0xC431BEF5829C9EEEULL, 0xF3691F2BE9AE3FA1ULL, 0x7A162E017860E868ULL, 
            0xA08FC09B4FB1B51FULL, 0xB64DA6FD77D63EF6ULL, 0x4D80FC7CD7741046ULL, 0xBEAD12636E571EDEULL, 
            0x44E99C989971AA92ULL, 0x2F0BB97A91F36A9BULL, 0x8A7BAC317A98D21EULL, 0x70FCB417FC569293ULL, 
            0x65E0A42301637039ULL, 0x1F17A620A6E4B7D8ULL, 0x5BBD7FDBCABA204FULL, 0xEFE0E8811303397AULL, 
            0x4DEE3118B372848EULL, 0xF290720DED5EB3DEULL, 0x1B0484C6A821EEC1ULL, 0xDA9C1AF1C8DD0446ULL, 
            0x88C6D1CE786C07F5ULL, 0xF0123973A28839C7ULL, 0xB4A68A82E991F02EULL, 0x0EA7F7B73D002B4FULL, 
            0xBBAA72D6F7E83D93ULL, 0x72FD78BA1BBA56AAULL, 0xE9743F1926623DBDULL, 0x2CA86D1C95E68DF5ULL
        },
        {
            0x3AFCFA66EE2C8416ULL, 0x7897E58D8BCD724EULL, 0xD32854F43E9A0B02ULL, 0xDA810A55C33822FBULL, 
            0xD8C37D24DBFC7EEBULL, 0x0E9F2535418D28B9ULL, 0x4CA30E14F14CA146ULL, 0x803194D773AEEED9ULL, 
            0xC27ABC0E9E672FE8ULL, 0x91FD4EBE6E5936A5ULL, 0x17BD6F575F71B385ULL, 0x009F36AAE8F91B03ULL, 
            0xEF6CAABE9DEDFAA0ULL, 0x5297FE59ED8B0411ULL, 0x1C1F4A50354B23CEULL, 0xE2B850C74E8A3088ULL, 
            0x2604B3D18CBDE43FULL, 0x62FAC72D3EAB6FE5ULL, 0x9ACBF038B3A05B6AULL, 0x85F8528FE5DCF1C8ULL, 
            0x3F14F1953B809A02ULL, 0x4737229CF0D95638ULL, 0xD21E3F1B0354EB20ULL, 0x3D5BD5507F16565BULL, 
            0x4911CC55294241F7ULL, 0xCC1C2520C4BDA668ULL, 0x9C23A5C455C91992ULL, 0x1DAA63981453707AULL, 
            0x03F42C9640D45C3BULL, 0x271ED129250A8D60ULL, 0x621B18FE3BEC8D58ULL, 0xC38FB23752B7FDE0ULL
        },
        {
            0x9C2A4EFEC337600EULL, 0x44FC0FD07EB290B6ULL, 0xAA5A9987E31BFC2CULL, 0x629D0EFD2CCB19E4ULL, 
            0xC3EB0E099F5BF64DULL, 0x02083E9BF6A0C5F9ULL, 0x33CA5AB50CAE3C54ULL, 0x07873278C46390A3ULL, 
            0xECB77FCF131B07E9ULL, 0x1B197A9F864560B5ULL, 0x8240BFB016B7C8E3ULL, 0xA1ECAFA67F3E0C8EULL, 
            0xABBAEE9E1F8FE458ULL, 0xC3AA302321793877ULL, 0x6BEE63007BBD6788ULL, 0x86F4EAA09D37F923ULL, 
            0x2C0641CCDB21DC9EULL, 0xF254D7E0F3CBBA4CULL, 0xD9ECCB948D32280FULL, 0xDC0ED8455C974A64ULL, 
            0x920E13BE1E77B2F1ULL, 0x9F70540498877BC1ULL, 0xB16D80A3CD1B5D23ULL, 0x331CBA576482B004ULL, 
            0xCB0EA12D31252445ULL, 0x7A80922232285E34ULL, 0x3635E90E0EA7BEE2ULL, 0xB22185247DCE7428ULL, 
            0xAA9A8B189C3D7E2FULL, 0xC9C6356017576B2DULL, 0xF1800130D6AB410BULL, 0x4BA1408CC3847FB2ULL
        },
        {
            0x7D63DFEC673B0D1DULL, 0xB18A802862ED7C79ULL, 0xE22866B93669C7D2ULL, 0x3A2EFBD45A167C43ULL, 
            0xD2F72DED691DA510ULL, 0xEC5452AE82847161ULL, 0x35727F66DD1D46D6ULL, 0xAFD76B774D48FE8AULL, 
            0xE862E5D203AA5FC0ULL, 0x48D59D00C6EA612EULL, 0x202CDEA954DF57E6ULL, 0xD058ADF76E3E934EULL, 
            0x12D811EFA5ACA8BDULL, 0xAB604E97210D2F4FULL, 0x77202B46FF044F07ULL, 0x808587E0AE8EBB1AULL, 
            0x4CB00F437F3E8487ULL, 0x69D4EC592DDB79DEULL, 0xF720DF81DA8E45C9ULL, 0x6BA83A8AA5ABC24CULL, 
            0x857553063A724A9AULL, 0xCEACA975C9E11661ULL, 0xD49BF3871C32110CULL, 0x48F14194A2510DB5ULL, 
            0xCE99F8030F7AF981ULL, 0xCEE6AE8E06221D6DULL, 0xBBD64F745D40BB0EULL, 0x8E8C47933A406F67ULL, 
            0x66E1BDB455408D38ULL, 0x92EF1560602679D9ULL, 0xA44865DD4F4AC1DFULL, 0x8793EE4E783B2EEDULL
        },
        {
            0x8A742FBE5272D5AFULL, 0x946D6432764244CBULL, 0xE3CBF02FC1EE73CCULL, 0xA3A3773881743CBAULL, 
            0xAE668145ED65F931ULL, 0xF4F964864A3CE87EULL, 0x969C416CF1CD73D3ULL, 0xE7E7AC7918DB19F0ULL, 
            0xD9B9562F1CB3D50CULL, 0xEF8F22BE816ADAE1ULL, 0xD7F1D7E51ED3C0A5ULL, 0xABE70AE5439661CAULL, 
            0x9A338C3A220E1FDBULL, 0x6E4E958E2015C907ULL, 0x7CC827B893129E21ULL, 0xD954A10A5062166EULL, 
            0xB05E0FE266CABBEFULL, 0x7C07691DDBDE8049ULL, 0xF581AF378DF4668CULL, 0xD7A84529D6299FC1ULL, 
            0x6209A7A3098AD15EULL, 0xDDB69B6D61764A20ULL, 0xE3B8881E772AD022ULL, 0x8C38E7F3D5A195F7ULL, 
            0xB404BB615087DA91ULL, 0xF3969547C19932B2ULL, 0x3876C0AFFA311446ULL, 0x091C230DB8631CEAULL, 
            0x2D373D584E2312CEULL, 0x12B7BF83921506D7ULL, 0xBA0CB4B74278C83CULL, 0x0FD8C470CDC07307ULL
        },
        {
            0xC268046EFFA404B4ULL, 0xC4582B134E019BB0ULL, 0x8DE005603AD9B082ULL, 0x35037B11E4922C8CULL, 
            0xCEBF6B91C209170FULL, 0xD12F8193FD39F556ULL, 0x34B61513D4AFAE18ULL, 0xB896EF79126729BEULL, 
            0x42E208C128D6753FULL, 0x2DA69869D4DCCED1ULL, 0x9E5F9F9B6EB5E3B5ULL, 0x5AD62017A5B22D98ULL, 
            0x0A9C91CA3A070786ULL, 0x94250186D7EA9EBBULL, 0xBC8A51BE082AA786ULL, 0xA73856F9E090910BULL, 
            0xE22C21A6C88393ADULL, 0x8C7FDC7BEB03C323ULL, 0x776499F746D4BFF1ULL, 0xDACB425CCCE0F988ULL, 
            0xC230CAC481A422C0ULL, 0xA21C639D1E865BBAULL, 0xAD4A737C7EA127B6ULL, 0x84F6E90BD516B4B3ULL, 
            0x03A403268B7244FDULL, 0x8C220216BB27E226ULL, 0x822B31953C88E43AULL, 0x134B09E7B620E20DULL, 
            0x6FBDBD6C9EFD887FULL, 0x8BB75DD1C7E9F1C0ULL, 0x391FC6FDEA765468ULL, 0x70C916E265BA3BBBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseHConstants = {
    0x2FBC7A5D4B311A99ULL,
    0xB777FCF0B6151487ULL,
    0xC578D9005D09EA74ULL,
    0x2FBC7A5D4B311A99ULL,
    0xB777FCF0B6151487ULL,
    0xC578D9005D09EA74ULL,
    0x0B947ADDED1F08ABULL,
    0x40B9C3AA5D57B1C9ULL,
    0x60,
    0x53,
    0xFD,
    0x42,
    0xD5,
    0x3C,
    0x11,
    0xC4
};

