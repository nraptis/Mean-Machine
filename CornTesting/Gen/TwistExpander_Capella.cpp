#include "TwistExpander_Capella.hpp"
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

TwistExpander_Capella::TwistExpander_Capella()
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

void TwistExpander_Capella::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB5076C46DDC0A89BULL; std::uint64_t aIngress = 0xFFD71D60698B7A8BULL; std::uint64_t aCarry = 0xE24AA065D8A57BDEULL;

    std::uint64_t aWandererA = 0xFC15A8CB41865FCDULL; std::uint64_t aWandererB = 0x9FB2423A26DF95F2ULL; std::uint64_t aWandererC = 0xEA26B8DEFE6A9470ULL; std::uint64_t aWandererD = 0xA9283AA07F3319E6ULL;
    std::uint64_t aWandererE = 0x89982FF51B147BDBULL; std::uint64_t aWandererF = 0x8E2E017F4F21BC62ULL; std::uint64_t aWandererG = 0xEFEEF05BAD56FFCCULL; std::uint64_t aWandererH = 0xF4AFEC7C62E410EAULL;
    std::uint64_t aWandererI = 0xF06EA60225640B0BULL; std::uint64_t aWandererJ = 0xB65013A12A714105ULL; std::uint64_t aWandererK = 0xC0D06F5AC0AAE34EULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18182607997184344833U;
        aCarry = 10597432183878062397U;
        aWandererA = 13404276755822529069U;
        aWandererB = 13202351437792370609U;
        aWandererC = 14406105662014068567U;
        aWandererD = 13132643140135278190U;
        aWandererE = 10919845678075260581U;
        aWandererF = 15094903003009306002U;
        aWandererG = 17608210747360311457U;
        aWandererH = 18036182850331170078U;
        aWandererI = 16468805396846981097U;
        aWandererJ = 18037616792531640781U;
        aWandererK = 11295592753291183409U;
    TwistExpander_Capella_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Capella::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xBF4CC73EDE872DFCULL; std::uint64_t aIngress = 0xCBBE75B115250816ULL; std::uint64_t aCarry = 0xD47D39838FE242B3ULL;

    std::uint64_t aWandererA = 0x8800B3039042CC03ULL; std::uint64_t aWandererB = 0x9D22860081D17647ULL; std::uint64_t aWandererC = 0xE0D3B7872DCF4543ULL; std::uint64_t aWandererD = 0xEBF24576409A6C75ULL;
    std::uint64_t aWandererE = 0xB7EB1FAE4E4C33B7ULL; std::uint64_t aWandererF = 0x85F36E300D84081DULL; std::uint64_t aWandererG = 0x9C63CCA88EC5720AULL; std::uint64_t aWandererH = 0xEFC49C8C7261F98AULL;
    std::uint64_t aWandererI = 0x8A6F5609E429E5FAULL; std::uint64_t aWandererJ = 0xD958B8885E23C240ULL; std::uint64_t aWandererK = 0xD86FE23E738A323BULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18314330178153714705U;
        aCarry = 16392105282040209895U;
        aWandererA = 15324710532891501006U;
        aWandererB = 10426340142203436897U;
        aWandererC = 10414641458777305429U;
        aWandererD = 12316285493817246194U;
        aWandererE = 15286673808875649508U;
        aWandererF = 16709135502920266449U;
        aWandererG = 10424075074328437503U;
        aWandererH = 9570952330588856560U;
        aWandererI = 12633568488652446023U;
        aWandererJ = 12118478792650629426U;
        aWandererK = 11856083453806954870U;
    TwistExpander_Capella_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Capella_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Capella::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC89B1C06D275792FULL;
    std::uint64_t aIngress = 0xE66AC4CEC3631ECEULL;
    std::uint64_t aCarry = 0xE3CD1F21203A1A5FULL;

    std::uint64_t aWandererA = 0x9485D94DAFC5E2D1ULL;
    std::uint64_t aWandererB = 0xBDE730A49CE60210ULL;
    std::uint64_t aWandererC = 0xEFF4B8F80A147BB9ULL;
    std::uint64_t aWandererD = 0xF7716EAC0C7E8E14ULL;
    std::uint64_t aWandererE = 0x9C870CC610FFD8DDULL;
    std::uint64_t aWandererF = 0xDC36F39DD6404C72ULL;
    std::uint64_t aWandererG = 0xAF3EDDD4BFADF191ULL;
    std::uint64_t aWandererH = 0xEA7E0E0CF7A9B79EULL;
    std::uint64_t aWandererI = 0xA8F20C9D21F44838ULL;
    std::uint64_t aWandererJ = 0x8F7E721357B79BC8ULL;
    std::uint64_t aWandererK = 0xE4A8A5E27A8733C3ULL;

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
    TwistExpander_Capella_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Capella_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Capella_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Capella_Arx::Seed_I(pWorkSpace,
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

        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Capella_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Capella_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 15 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1839 / 1984 (92.69%)
// Total distance from earlier candidates: 25994
void TwistExpander_Capella::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 689U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1446U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 89U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 382U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 489U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 90U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 485U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 792U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 734U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1133U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 237U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1939U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1197U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1722U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1273U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 782U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1472U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1272U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1746U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1002U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1410U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 790U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1311U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 830U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1080U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 343U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1607U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1908U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 909U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1052U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1642U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1457U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 899U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1636U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1759U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 356U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 838U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1173U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1285U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1999U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1290U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 583U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1116U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 926U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1293U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 867U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1716U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1810U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1209U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1563U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 660U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 320U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1011U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1032U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 201U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 454U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1841U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1053U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1334U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 592U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 745U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 317U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 603U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1162U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 338U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1165U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1309U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1409U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1983U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1614U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1632U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1301U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1282U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 548U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 400U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1143U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 874U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 477U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1134U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1694U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 329U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 319U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 618U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1203U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 475U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 394U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 255U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1786U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 535U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1506U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1164U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 978U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 955U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 632U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 799U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 479U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1646U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 980U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1010U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 458U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1861U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 691U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 93U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1418U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 366U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1241U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1073U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 368U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1520U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 789U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 566U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 35U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 755U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1448U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 560U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 823U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 259U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1579U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 798U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1121U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1963U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1443U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 159U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 630U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 564U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Capella::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFC1E0731E7BE0817ULL; std::uint64_t aIngress = 0xE3E3BE4CDE73CA97ULL; std::uint64_t aCarry = 0xDC798B2FBEB8A79CULL;

    std::uint64_t aWandererA = 0xC5490B63463BC691ULL; std::uint64_t aWandererB = 0xADCC461C954BD064ULL; std::uint64_t aWandererC = 0xA2D69A97C8B1B26BULL; std::uint64_t aWandererD = 0xB0267EAF13546C66ULL;
    std::uint64_t aWandererE = 0xFD7C05D212D10F5AULL; std::uint64_t aWandererF = 0xAA4185E0B10204F4ULL; std::uint64_t aWandererG = 0xAC7ADA823EC69264ULL; std::uint64_t aWandererH = 0x8912E00094FA791EULL;
    std::uint64_t aWandererI = 0xE2EB2CC263704F95ULL; std::uint64_t aWandererJ = 0xB442933F6AD3250AULL; std::uint64_t aWandererK = 0x9C07902A5F2C1C1EULL;

    // [seed]
        aPrevious = 12817917473859137023U;
        aCarry = 12146188286362293289U;
        aWandererA = 10475265461640151531U;
        aWandererB = 17465051605152453301U;
        aWandererC = 12122124258179639135U;
        aWandererD = 10171848832427553724U;
        aWandererE = 12775498727201754145U;
        aWandererF = 10679136202984711350U;
        aWandererG = 16689974082414724313U;
        aWandererH = 18268250099836966245U;
        aWandererI = 12250928759846552493U;
        aWandererJ = 12581478553252939313U;
        aWandererK = 10753639693265732764U;
    TwistExpander_Capella_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
    TwistExpander_Capella_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Capella_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Capella_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Capella_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 15 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7671; nearest pair: 470 / 674
void TwistExpander_Capella::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 195U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2083U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5606U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6914U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3602U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3035U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5589U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 157U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1066U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2230U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6951U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5306U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3181U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5274U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2260U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5045U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 406U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 995U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 588U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 468U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1238U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 383U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1141U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 710U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1851U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1731U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1654U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1781U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 538U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 908U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1221U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1134U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1289U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 2043U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1034U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 15 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7668; nearest pair: 481 / 674
void TwistExpander_Capella::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1869U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2845U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6848U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5352U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4550U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2089U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5183U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 928U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6838U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2628U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6842U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5853U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6180U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7636U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7881U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1242U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 453U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 646U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1645U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1267U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1868U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 864U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 55U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 491U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1844U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1213U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 462U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 105U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1699U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 737U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 342U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 288U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 926U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1789U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 519U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Capella::kPhaseASalts = {
    {
        {
            0xEEDB256E730ADF74ULL, 0x5CEDC2520560AADAULL, 0x6AC7D5F0AFCE1C19ULL, 0x981946104BB71CBEULL, 
            0xBA553DD6ADF5FBE7ULL, 0xD441A054B6B88E5AULL, 0xC110539DDD2EF00AULL, 0x643FD616FB61EEDCULL, 
            0x7CA89C6D54DF2462ULL, 0x2DF3F5D3A878A404ULL, 0x4E773467187C78D5ULL, 0xE69586F1806AD733ULL, 
            0xB293A17ED3C4714DULL, 0x987D12549FACB318ULL, 0x8216F82D94F38F33ULL, 0x3C80AAFC09DAA995ULL, 
            0x84F3286AE86797EEULL, 0x2B83EFE945D48069ULL, 0x54E44B556F48CC64ULL, 0x08057270905E4764ULL, 
            0x8BE16D5D9BBCCA7EULL, 0x58A81925B44E5D63ULL, 0x43CE27B2A94ABDBDULL, 0x1C150EE8D56B771EULL, 
            0xB405EB64410F0781ULL, 0xEEE14EEB4321B208ULL, 0xA5A7563DF43CE1E4ULL, 0x4894DD1FFCAFA474ULL, 
            0x3538F5F59F0604C4ULL, 0xFAF98D8D6A44A2F0ULL, 0x89C8216A12BBCB32ULL, 0xF90D76508F79C471ULL
        },
        {
            0x7C1A325A66A9B25CULL, 0xDD0643EC2D472E3FULL, 0x22CD4B821F0775CFULL, 0xC212976AE0017BC8ULL, 
            0x4C531CE38DCA5FF7ULL, 0x606623D86E17D215ULL, 0xD361AE089994F0C7ULL, 0xAB01AB3BF163EBE1ULL, 
            0x56488AB4EAA8526DULL, 0x9B8276CDFC93CAA9ULL, 0xB334C446A0DBAC4EULL, 0x71716D9098A18990ULL, 
            0x1A9BAC48381E9568ULL, 0x1EDD5F809C3AF3D1ULL, 0x2265729A449F7A53ULL, 0x26BAFFDD85A2B406ULL, 
            0x84EE939E6EC333BDULL, 0x1F74F5ED9D5B7960ULL, 0xB6A6BB50A25B9E9CULL, 0xDB4A0137A4C050A8ULL, 
            0x0812D5E2E0E5D110ULL, 0x971FE97248D29BAAULL, 0x7E15B01D5EE6BCF1ULL, 0x52599AE5FD0064EAULL, 
            0x0AB157FEE816DEDCULL, 0x6FB971F780ED1AAEULL, 0x44AE154892F65B1EULL, 0xF8E31EA7450C5295ULL, 
            0xA0C0D1A898E82D6FULL, 0x2800AFE0C27823A5ULL, 0xE4E2E3D407B75C47ULL, 0x39F3C156C4D5BF9EULL
        },
        {
            0x4CB1EE0941AFC3E3ULL, 0x88E77C86C5AF0656ULL, 0x2BD331DFEE404D9FULL, 0xD1EE46BFCAF0AC25ULL, 
            0xDEF4F15412B6AB44ULL, 0x05D4C6D10BF722D3ULL, 0x9E2562D00020C385ULL, 0x7E2C0BFB1E05B5ADULL, 
            0xA6A35170452AD412ULL, 0x89E7B1607BA4E066ULL, 0x4818B9F999729E6FULL, 0xAC7DE7F5507EBCCEULL, 
            0x10B007B171C06FD3ULL, 0x448C98181B8DB61CULL, 0x2E53C83CF03D2208ULL, 0xE644CA0BBDCA7FA2ULL, 
            0x13108667FCF6B922ULL, 0xD109D88CF8AF6666ULL, 0x71711581971DA16FULL, 0x0B5A002BD902C505ULL, 
            0x1B19D7A9645A9AB5ULL, 0xEACCACA8E27D25ACULL, 0x81A46B48A5440F99ULL, 0xB3F77F3263A046F5ULL, 
            0x65C1C8715B98ACFCULL, 0xA41D33FA84A04F90ULL, 0x029A5CBD05B38B17ULL, 0x118A41C110B16E50ULL, 
            0x5A6E7BBFE36ECF50ULL, 0xE532F964AE0E369EULL, 0xAAF81D3BC78F92D9ULL, 0xC9B8656E051E4422ULL
        },
        {
            0x90BD826ACF177E90ULL, 0xDA6C78D5B2C3C852ULL, 0x7E55DE879D40249CULL, 0xC74C60BC588D4CE6ULL, 
            0x916F4372E5E499A8ULL, 0xC564E92DB75C1D3DULL, 0x18B23EB130E0B173ULL, 0xAC74ACDB09DD0068ULL, 
            0xAE224E7630AAC8D4ULL, 0xA79EA571131DDEAFULL, 0xA00CAD38114FB383ULL, 0x9BDA6F95AC1931F5ULL, 
            0x19B633E8218A2FF8ULL, 0x5EC0E9A023CC9B4AULL, 0xB28D04AAF4C3F1C9ULL, 0xAAC18E8A5B1DA82EULL, 
            0xBFF1E655AF90D25BULL, 0x2E1C6804CEC9C3F7ULL, 0xDC94CBED55CB3CE3ULL, 0xF95CD6240D6D3F22ULL, 
            0x548D89135BFA8574ULL, 0x3FECB254C36BDAACULL, 0xF055ECB071E7DB73ULL, 0x0449447AFFA3B7DCULL, 
            0x333D9F570B01C0CAULL, 0xBFDEC5F89D9B45B1ULL, 0x1143E18E7816C375ULL, 0x3BA23F88AB4E130CULL, 
            0x1169D0F2EACDDD17ULL, 0x27B147D15EA43230ULL, 0x197F42B364F74B90ULL, 0x1F506648886C11C0ULL
        },
        {
            0x3ED7D035BCFAF3CBULL, 0x75C2E7965D9FE30BULL, 0xAB9BF1AEA502AE64ULL, 0x40422BF6F1178601ULL, 
            0xC18C466ACCDB129DULL, 0xB5EB150F61424B54ULL, 0x02D7D681AE8F287FULL, 0xEA5A06F27BDF2D33ULL, 
            0x9E1CFAF4425D69DAULL, 0x20A9118AA45167BAULL, 0x995B2931EA82DD1DULL, 0xEAA20C5FF05A09B0ULL, 
            0x657D51B6978FCEEFULL, 0x616F5FC182F5A56FULL, 0x5CE46348A9E4E8CCULL, 0x628F7B5F3B93E368ULL, 
            0x9C6B890B987CBA56ULL, 0x82504EB96D4115BBULL, 0x660979DFD5F4BEDDULL, 0x3FD62257721C7DF1ULL, 
            0x48F43D14F247F1E6ULL, 0x0C61809A14A8731DULL, 0xACA77781BE7B9942ULL, 0x904E02B849306209ULL, 
            0x79CF7D346137E78CULL, 0xAC7E168D04E1EA3FULL, 0x4535B56CDFAE1B5EULL, 0xCDD2CE0F87EB356FULL, 
            0x9F96C2A39ADB3B67ULL, 0x141F55DEC8766328ULL, 0xAA689C344A9AF01DULL, 0x48CDFDCF250A7D4AULL
        },
        {
            0xC143799AD88E29F1ULL, 0x802A6179B3986E9EULL, 0xD599FA567C7E4C1DULL, 0xCB9E51E8725B9047ULL, 
            0x34FCB72F2AEB1EBDULL, 0xD7909678AB8FB3CCULL, 0x4901C54A7C053620ULL, 0xBEEA0F818CD26B18ULL, 
            0x4312E6E61831B768ULL, 0x7D1CBB997EE9E41AULL, 0xBBFEC0835F621F30ULL, 0xF609D96E5956D0C5ULL, 
            0x646B77AA2F45B199ULL, 0x15AC4A764A41BBD3ULL, 0xB95CED6CC0412C3BULL, 0x9FBECE0551429104ULL, 
            0xA47C949B4FB4543DULL, 0x8B86B2C7D0748AC5ULL, 0x6FC35F7E3F5D9696ULL, 0x09F6BD25518F66B6ULL, 
            0x5994E7DB6DDA650CULL, 0x2E8A2F9E85771D1DULL, 0x25BC0733C563D828ULL, 0xFE4D144F17D8BA2AULL, 
            0x0700BC5B2E193571ULL, 0xA61306135698C2E9ULL, 0xC3817886178DCE16ULL, 0x1082ABC6C0BADF4FULL, 
            0xB21AB263BB7B170DULL, 0x8E4421814058EC05ULL, 0x212F5D0F04736FB5ULL, 0x4AC326571D843B83ULL
        }
    },
    {
        {
            0xD00160184CF35EB3ULL, 0x7A85C7560281AAEAULL, 0x1EF8F637A6831027ULL, 0x25A67E63AB4ADE94ULL, 
            0x9E0038CD75EE246BULL, 0x6A19D66C98717663ULL, 0x1D8CA009E4D76D05ULL, 0x6401A9D709C5F15EULL, 
            0xF720FCA558E460F3ULL, 0xBB92AE32B3B71230ULL, 0xB7D2A952546E1320ULL, 0x614A627A6BD9E7C9ULL, 
            0x0D3BD60EE4BEA269ULL, 0x4AB185A75DDA3386ULL, 0x9EA8C611F6BC9B59ULL, 0x3D96885C0D99E52BULL, 
            0x959FB9A208769348ULL, 0xA2883926D8BEF744ULL, 0x156F22F80A5D705BULL, 0x0748A55103D1B878ULL, 
            0xA103C3C8C1DC918BULL, 0xEA0A40BCB37C21FCULL, 0x48BA1D21000A099DULL, 0xF470849EE07A27BFULL, 
            0x278D46D403C177E4ULL, 0xD614120DC14BDDA9ULL, 0x0E07CBD2A5892E81ULL, 0x4D0C4935A7B0169BULL, 
            0xD6B8172278A9088FULL, 0x87B3123FF4A018BBULL, 0xB34CFFCFA140DEEEULL, 0x47137B612DE89E6FULL
        },
        {
            0xC9A21A1F642BC938ULL, 0xD888D72E8FD67834ULL, 0xB8EA9E079B0EA227ULL, 0xBDDFD07A30B05576ULL, 
            0xE0C690012388EE90ULL, 0x0A1C82314561AB99ULL, 0x11538C0C4EE493ACULL, 0x7B6857B3B7E55501ULL, 
            0x9964782362C216E5ULL, 0x0652498A65E2C621ULL, 0x50F8B1974D1E7406ULL, 0xBF6751EDF534AA35ULL, 
            0x0BEADBF06FA59973ULL, 0x0E9B9D78F95F21B3ULL, 0x8FCD9974C35B9DF7ULL, 0x04D3EF71251A414EULL, 
            0xB37C24764A772CABULL, 0x4454C78347BB8EE2ULL, 0xCFE12A65DC5B0AB6ULL, 0x070D1943B10C06D0ULL, 
            0x4BD7389697BC3DEDULL, 0xB6D3419E53D19F43ULL, 0x5F4D653850C9386DULL, 0xAB99D6463E0F8EDBULL, 
            0x769D9535F0CC4F31ULL, 0x322814308AF03F99ULL, 0x40BCE60B44E90E90ULL, 0x675F782BA36300CDULL, 
            0xB871B764A7D5182DULL, 0x633788510E3F71A2ULL, 0xF157F7CD341A3EDEULL, 0x30DF80DF511125B3ULL
        },
        {
            0x904C5D153FEF6866ULL, 0x051E92E09826F48AULL, 0x77E07A91F0528007ULL, 0x4FA1E6F60C2FF8D7ULL, 
            0x014FAED240498E13ULL, 0xC380D50B85FCEF9DULL, 0x6460AC56D609D392ULL, 0x40C0421C59CA2CD1ULL, 
            0x40BF367BFD388930ULL, 0x39ABB8213AE2C5CAULL, 0xEDAB09BD78C7082DULL, 0xDE291A72D874E490ULL, 
            0x9593B6E7C375F160ULL, 0xA74B22C481483D76ULL, 0x19E15AF3ACF83CC0ULL, 0xF5AEF48891A24E83ULL, 
            0x5DB6A1D6024F5843ULL, 0xE48E33CD67525A84ULL, 0x48DF400B5F7ACDC3ULL, 0x5D4926F49B1BEE04ULL, 
            0xEC9EE13C86C2DC02ULL, 0x0A4AACEC077C94EAULL, 0x68CC39B5783969C4ULL, 0xB0BB59B83803DCE7ULL, 
            0xB20B9F103562B796ULL, 0xDDA5E2AF76E7E41EULL, 0x498052B4F43FB08AULL, 0x0D049D3DA8B66B9EULL, 
            0x9EBD0C278327AD2BULL, 0x8DA2C8909C194600ULL, 0xD7E85823416FA84DULL, 0xA8D54609C024D13FULL
        },
        {
            0x785BC1CEFE1CAD65ULL, 0x6EDF7E7B8E79DAA5ULL, 0x26C684491D2D0648ULL, 0xCF5B0F9B68202D9EULL, 
            0xF9473D5E37D9C9EBULL, 0xC2AF334CD2E1AF53ULL, 0x18504B5853221BF8ULL, 0xE8A458893610C3F3ULL, 
            0xEB2BA9A2FE1C47B6ULL, 0x092418B3F4A954D2ULL, 0x905AC2CF1843239BULL, 0xFD22BEDA763F58E5ULL, 
            0x343AFD6493F7F4F9ULL, 0x1409A719AEBCC884ULL, 0x6025ED5B2D9972C8ULL, 0x838B73079D45FF82ULL, 
            0xB9F1B82C127BD7FFULL, 0x4B8E1B5AF53A4F1AULL, 0x105A34F3DA1EFEB5ULL, 0xC94776AEF5CC714EULL, 
            0xDFDEA1AC09F8819AULL, 0xB008F3445F54EDC3ULL, 0x062A9772D9F0EEA9ULL, 0xD105E1F07EB6E5E1ULL, 
            0x09FBD4FF062D69AAULL, 0xC48A11DB60B57865ULL, 0x636E9EA3A6EAFB21ULL, 0x669FA5BDB2DB4B88ULL, 
            0x415BEAC7F4CF85A4ULL, 0x30F439AAD10CD58FULL, 0xB02F5FF587FF76F3ULL, 0xE9E3C50BADE73E81ULL
        },
        {
            0x02E3BAE9FFD3D0D1ULL, 0x4C2BEAFCC18DB22AULL, 0x43559D8581BE152DULL, 0x4F4904F9FE74ED77ULL, 
            0x5D6672499A7B2012ULL, 0x306612F07955123BULL, 0xC4145C4899E4B1D1ULL, 0x898275848712B741ULL, 
            0x8E76A5B7BB357085ULL, 0xBBE52D16676634EFULL, 0xA1F92326B9DAA429ULL, 0x6B004E3D181EC1B9ULL, 
            0xA34802FA7101B64BULL, 0x6355591BB5DE885AULL, 0x210F044B759B3963ULL, 0xC51E6B27768BEE61ULL, 
            0x0892A2360EB18FEDULL, 0x383A2E912EEDFA02ULL, 0xB39B8776B1156041ULL, 0xD560A837F5D38D88ULL, 
            0x66AE80DD2EBCB023ULL, 0xC07BC532788B409EULL, 0x5C5E39841669B27AULL, 0xF778FE28E6E1A75CULL, 
            0x818852E9AA27603DULL, 0xB5B9BAD1616F209DULL, 0xDBB7E3DE361C4654ULL, 0xB07FA3612D0E0BA3ULL, 
            0xD6AE37D4F994DB16ULL, 0xCA97F532609F56B2ULL, 0x97D5ACB3AEF17DBCULL, 0xD1BEEB05127CF01BULL
        },
        {
            0x9670F760CB55256AULL, 0xDFE870CAE8591737ULL, 0x5869BE74FCF5AD3BULL, 0xD1DE34EAE6266B53ULL, 
            0x99C6C4DB5DBE07D5ULL, 0xDE62CDE7CA4251BBULL, 0x38CBF55D1155CF1FULL, 0xF7316705C638D6F0ULL, 
            0x2128CA0CD0FAE336ULL, 0x4917C6FD7B3013F2ULL, 0xFF6BF8CF08FEEAACULL, 0x37CB26E428260966ULL, 
            0xCC5FEDD1B3D81223ULL, 0xBFBC0D768D401318ULL, 0x660021366CAB2A8DULL, 0xC7F9C2CDA6774C33ULL, 
            0x541562D676EB8739ULL, 0x6571B7CDE096C614ULL, 0xFE799F5E7BFD3067ULL, 0xEF68D3C87BC02C6CULL, 
            0x3E09E1EA6F7EF296ULL, 0x2D8E39B7B81A4CE8ULL, 0xEE3D818E918CE410ULL, 0x57652CC918614C96ULL, 
            0xB2D9CFE3564E6E9EULL, 0xCEAA9C4C6D3D754BULL, 0x7327FF7B8282E01DULL, 0x8FD6897668013C71ULL, 
            0x012C9EB15E8EC7FDULL, 0x8BC8F3C319DAFB0EULL, 0x1A30B04E06B281FDULL, 0x45B04BC9191D16B1ULL
        }
    },
    {
        {
            0x8127ACA3E4551C44ULL, 0x38DBB271C31A3F0CULL, 0x0BF4A6035604C655ULL, 0x36EA2DCD271C1C00ULL, 
            0xDEFA2B14E428FFB0ULL, 0x3439026B97EF70DFULL, 0xE9F1EBA42AD09386ULL, 0x1F9B357E090A7AFDULL, 
            0xC938EB11B1A79CCAULL, 0x02FB5FE81ABA5C1CULL, 0x3BA6B2F5E0B6BAF4ULL, 0x699FF298AF16F8D7ULL, 
            0x850D6FE85D89B5A9ULL, 0xDC392C09A0389ECBULL, 0xB32CC08F9AE1C7C6ULL, 0xCA52C4FD9D1F8D3FULL, 
            0x72626613BF61A3FBULL, 0x278E183891B13F6EULL, 0xEF2CAB300B39FAE8ULL, 0xD324890F8E3B2EA1ULL, 
            0x1C31CF63D3023BE1ULL, 0xC3E2FDAA644393C0ULL, 0xAE32AFB6345303D3ULL, 0xBE16F930F189016EULL, 
            0x34932FFC16088FD0ULL, 0x9220C933EC48BAAAULL, 0x29C394630E8E1575ULL, 0x117AF58361FEA71EULL, 
            0x40474047A03517FFULL, 0x57A6280C4323AF50ULL, 0x71A2F9FA5C6C571CULL, 0x49E746C8B266A5E0ULL
        },
        {
            0xB6FD5EB34AC0FD86ULL, 0xAE97BC61237B6A5FULL, 0x92284F5C54448EAEULL, 0xC1CE20E480FF05A8ULL, 
            0x96AFE3F0022DB1E0ULL, 0x44E60E870786DBD8ULL, 0x79A4491B4BBB137EULL, 0x2E93F45F698B8A0DULL, 
            0x365EC05F98DD3F6EULL, 0x9B48DC29B1853C23ULL, 0x423AEC3B76A91D22ULL, 0xCF32BC0468711B0CULL, 
            0x76B1983B9D10E331ULL, 0x6FCF73F314C90C83ULL, 0xC8C55EADC32DCF6CULL, 0xD97EB8013EBC7C5BULL, 
            0xE800042DC8D7F9C5ULL, 0x40C5C8243552296AULL, 0xC05ECA757FE81DA7ULL, 0x38A39542CF0AB65EULL, 
            0xD21608738FB53DC6ULL, 0x67C1219B79758F72ULL, 0xE0B72E38CBAD7796ULL, 0xF487586D7A02C5CCULL, 
            0x7D55E39D218402E7ULL, 0x31025606492F1080ULL, 0x3E02AED559915E71ULL, 0xE90707ABA100C932ULL, 
            0x2BB50C14966B6827ULL, 0x5B7B8AB7A2977391ULL, 0xBE7E75514121206FULL, 0x1E031DF1C3D57632ULL
        },
        {
            0x54DB3CC8B2E107E2ULL, 0x60669FABB27677EBULL, 0xB604E23A85F98AFCULL, 0x9CCA5DA3DE16E78CULL, 
            0x44A4BCE44DB1FE9FULL, 0xD1006ACE1DECB0B7ULL, 0x0628816B3C22C0FEULL, 0xD625D3A4CC7C240EULL, 
            0x4D41A2786BA93A82ULL, 0xFE1126724CFFFD29ULL, 0xC3A277182B32E64DULL, 0x1E0B5590B4F833B9ULL, 
            0xE3BA0A10A81B3929ULL, 0x58F49C86CA5B5447ULL, 0xF56E84B5EFAB56FCULL, 0x24C59BA6F78033C9ULL, 
            0x49ECEF14D73B006AULL, 0x6C675E143A0B10C1ULL, 0x9809FCB918246469ULL, 0x7627BB112EA42DA5ULL, 
            0x997AA463A68EF83FULL, 0xCDF454D514936C96ULL, 0xB73A16FF148EA924ULL, 0xC6C21B56FD414260ULL, 
            0x757952703DB02C78ULL, 0x9B74B47AA61BAE5AULL, 0x7D50610BC0859DBBULL, 0x58A2D6E5852CA7BDULL, 
            0x16FE087EDCE4E199ULL, 0x07308EDBAB3413AEULL, 0x6BDB735BB331743EULL, 0x7ED60726A08E617FULL
        },
        {
            0x293B042058F37AEFULL, 0xFBE38D49D60D1823ULL, 0x7372CEF0344F65B0ULL, 0x1A1D5A7B82C0860BULL, 
            0x7FD64EC6D862AEE7ULL, 0x8233F777B75DF92BULL, 0xC5132EA9C4B25CCEULL, 0xAA56571D01E81274ULL, 
            0x9C08BF4D9116BDE8ULL, 0x557CF5EA177DBA6FULL, 0x67A1D0EA8A785CBAULL, 0x864A3394ED5AD901ULL, 
            0x482D177D1E9ACCADULL, 0xD286B1E3056036B9ULL, 0x81CBC3F708EDD996ULL, 0xBBBC50303499EBEBULL, 
            0xAD72128031C1B5A7ULL, 0x7183575E890E06F4ULL, 0x8A838229A46BFC33ULL, 0xE05604213E94EC74ULL, 
            0x626F9F49C360C9D1ULL, 0xD21FC946F34B97FDULL, 0x457C7B2F430DE4CAULL, 0xF427E9A03D4B6C7DULL, 
            0xC27B9B74E34331A8ULL, 0x1B280DB98CF1F665ULL, 0x3C954F9E3D72B940ULL, 0xA378A2D065EE0EB0ULL, 
            0x28863D298843A5C5ULL, 0x1EF7BF2CC9FEB95FULL, 0x8E4512A023296B1EULL, 0xEA03C994DCBEC527ULL
        },
        {
            0xDA74C92C5B619669ULL, 0x167D2076976504ACULL, 0x287511F7F37E0122ULL, 0x666F3C6152AB1A74ULL, 
            0x00233A29C4E71C43ULL, 0x226C89E26B9E2330ULL, 0x9479774ACC528B38ULL, 0x415DC6AD318C5D3FULL, 
            0x5F2E2D1CF7A0B7CFULL, 0xC2F9FAD1A86F04B3ULL, 0xB12C705542F5EAC9ULL, 0x50DADADBA9800FA0ULL, 
            0xEE2B9028043BEA77ULL, 0x905403942E1C4D68ULL, 0x929F38BE90631E23ULL, 0xCE6086B278B6CA55ULL, 
            0x275A388F9FC8E456ULL, 0xE501D85F3DA4B75BULL, 0x5AA083E1FF1FAB4FULL, 0xDC5829B7B75F8BD8ULL, 
            0x3D54219087C2E4F7ULL, 0xC18907C48206B3DCULL, 0x53CEE8A6B6B2E6A4ULL, 0x5C0707F84C5AC105ULL, 
            0x58562A55315A248CULL, 0xD9071FB940C51356ULL, 0x132B9003AAED78D7ULL, 0xE06E525CE9DD5E74ULL, 
            0x56BD39EEF2C5A356ULL, 0x9D2908434879A932ULL, 0xF81482DAF3344D72ULL, 0x91249342037DCE18ULL
        },
        {
            0x66D10E7AF1F2B8B9ULL, 0x0967A1DD605F1BBFULL, 0xB33018AE30C3CE8EULL, 0x277BED65317C0B7EULL, 
            0xCF57B299E760A220ULL, 0x2F8E663E1F7CEFC1ULL, 0x2ECABCB79F759F00ULL, 0x824AD819D20D6580ULL, 
            0x47BE0DD87F97DE6FULL, 0x6860D68140EB2213ULL, 0x08DFCD34A615FCF4ULL, 0x0C9D8A02403BD79AULL, 
            0x3DAA14362EBD9186ULL, 0x39A866059D22D92EULL, 0x30E27139DE374887ULL, 0x57857DAFC0D29693ULL, 
            0xF35F49E254BA38DCULL, 0x6ED8B75C831404C3ULL, 0x8F1D7435D823AD5DULL, 0x8A8A98F76B3C6745ULL, 
            0x247C0176F1F006D3ULL, 0x8D5A4F3E37EC5590ULL, 0x4339F8C59E594388ULL, 0x9B0DD9E775D3BE8BULL, 
            0x649A39B8B168E0F6ULL, 0x7A93CB88B6B65958ULL, 0x24A383F8D256DC89ULL, 0xE1D9433B3CC8B7D1ULL, 
            0x4735843634F73B54ULL, 0x764BDC74518369F1ULL, 0xC1623E699EB27826ULL, 0x086D0F69D6D0D4BBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseAConstants = {
    0x96C45F3C40708ACAULL,
    0xE03534C4F2F9DD0FULL,
    0x5A58DA79E3F82F6FULL,
    0x96C45F3C40708ACAULL,
    0xE03534C4F2F9DD0FULL,
    0x5A58DA79E3F82F6FULL,
    0x7A346CDE801DBB75ULL,
    0xD861A3C398D66F44ULL,
    0x5A,
    0x36,
    0x1B,
    0xE7,
    0xE6,
    0xE1,
    0x1E,
    0x8D
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseBSalts = {
    {
        {
            0x7F47CD74C607AB6BULL, 0x190A8AF48A048900ULL, 0x601106DC40DBE70CULL, 0x0EF10D87D61ED00EULL, 
            0x71EB067C46D8B840ULL, 0xCFC4985705F1040CULL, 0x4ACA26541977F103ULL, 0x756AF5C26817D37FULL, 
            0xB0D66E96A9C62F53ULL, 0x49B89D52C26DFD5EULL, 0x790796FEDF1F21FFULL, 0xCD1BD9EDC9A2CEC4ULL, 
            0x554B85711B072F3DULL, 0xD5837A988ADDD8FAULL, 0x2D2967B97BD3231DULL, 0x6C9A62F3DE93DB18ULL, 
            0x991B381FA45F95C2ULL, 0x46935D90F2B80DE0ULL, 0x87A2ED88AEE1E1F5ULL, 0x692B20A26F50A67EULL, 
            0x4213905CB0D1D682ULL, 0x1776788CE82CF1FEULL, 0xCA92ED22788090D2ULL, 0x724FE74A0984A2F0ULL, 
            0xF6AD42AF551777A9ULL, 0x9A2DA46A4C6081BFULL, 0xA2F06222E4F1DBE2ULL, 0xDD2FD9B0A8B49CD5ULL, 
            0x2FC5BEBC061A1A0FULL, 0x7506DD091F1B28B6ULL, 0x8F896BC6973BEC67ULL, 0x0904EB78A7D310A2ULL
        },
        {
            0xC99CE47AB1D5BFFFULL, 0xE5DA04CC08FC9D2EULL, 0x36A49562EC67FD38ULL, 0x02672BCDE0E5B213ULL, 
            0x3820F298F9377D84ULL, 0xCB96C9328209FCB1ULL, 0x2804EFB4FE12BC4BULL, 0xDDE8A1DE5BBF164AULL, 
            0x4DF8E71FF56E1699ULL, 0x613E71D896047DF1ULL, 0x30511625387CC063ULL, 0x6676C1D55A33DE6CULL, 
            0x79C6E9E211F9FAD9ULL, 0x64CC6F532EC1F8EAULL, 0x6E7381D66E9C1ED1ULL, 0x7A4253731E7838A9ULL, 
            0x62D56913CEC7E5D4ULL, 0xFA8AC9E15757F6F8ULL, 0x5B6755CE6D47D8E1ULL, 0x43689DC8CB072DF2ULL, 
            0xE93EC04F2BC5F54AULL, 0x95F72DDCD59B0F99ULL, 0x028BF2443234E526ULL, 0x5E40C7984C61651DULL, 
            0xE598A026D6236B8EULL, 0xE2FDB052F5743906ULL, 0xC01FA265ED9B3F2AULL, 0x5EA1F09D4F8E09F5ULL, 
            0x5821994C9AA1B1EEULL, 0x7EA10A1D2C0A33B4ULL, 0x75572C2F8A764D4CULL, 0x9F06F7C38BF6973FULL
        },
        {
            0x371831DD1EF835CCULL, 0x229C812F65943078ULL, 0x51C1F78A1D43ABA8ULL, 0xDA45241984E0C644ULL, 
            0x43405BE7651EED37ULL, 0x535378BB6501B3ABULL, 0x2D662538B1EEF871ULL, 0x5EB5A242BAAFC60DULL, 
            0xB93D80ED947D5D4FULL, 0x75758D8D02259D71ULL, 0x56EF6FE5FBE9E455ULL, 0xC8EFD48EB87C8045ULL, 
            0x97CCFD70D7C4D7B1ULL, 0x5391D09AAA8C3C88ULL, 0x085037EC82FD3080ULL, 0x2280491CBDC015BBULL, 
            0xEE73F7C25EEF484FULL, 0x2249366810FFAD56ULL, 0xFB9055EE343A4960ULL, 0x54D90FAAACDD9AF9ULL, 
            0xD626D150DBCC3E39ULL, 0x2FDB7735B94A5DADULL, 0x37F1932BD83AC43EULL, 0xA4822EAA6B6F2AFFULL, 
            0x97D45A98820A4E79ULL, 0x203B4BFD60D36044ULL, 0x85B8D0D81EDB2980ULL, 0x05F0B1037F59414EULL, 
            0x7DE6697DC6CEA53AULL, 0xEA24C1B1E9DC408DULL, 0xB69FAA0A12D752A8ULL, 0x4B585732D84C6EE8ULL
        },
        {
            0x2DD6199C94A04E62ULL, 0x69DF12DBD62A833AULL, 0x038782563BA7CA3FULL, 0xAA2F6ECCBB94F55CULL, 
            0x5C4374EF26625094ULL, 0x8CE497EC31C6CE5FULL, 0xE0B2D81A51ED9FF0ULL, 0x7F7C9A0FA7B2B883ULL, 
            0x740A67B531D2E45AULL, 0x7D47792D348455E9ULL, 0xE42056A39609C22FULL, 0x8D07C1C1B140285BULL, 
            0x14C6B6546FC5D476ULL, 0xA86E5AA57FB7236BULL, 0xD9539A4995B96343ULL, 0x3A87DC958D2A8C44ULL, 
            0x088427FC42CEBE4BULL, 0xA81773B3BE6CDC75ULL, 0x37FD89864C3F4758ULL, 0x01EB479F6863ECD7ULL, 
            0x04429C9017773632ULL, 0x80E405A4B86AF780ULL, 0x0C944A49C8DA61A7ULL, 0x0B789BF6509AAD97ULL, 
            0x7FE4292A4A77CB98ULL, 0x627993314AD760B4ULL, 0x709BE5E184F3A35AULL, 0x0F2CA9C9FA7E1A12ULL, 
            0xCF7EBCB3E7615AD9ULL, 0x3C521C0D74F710A8ULL, 0x7C09243FFAA965EEULL, 0xC819AC9232E13E76ULL
        },
        {
            0xDA5BD6BF4BC237BCULL, 0xE75FE736B94235A6ULL, 0xE7F5FE0DF6E88ECCULL, 0x2109BE7361AA1FAEULL, 
            0x312CFB2A9EF93A44ULL, 0xBD0F310EC26F8388ULL, 0xE10FA3E7D65DF491ULL, 0x4F589D8DC6D835C1ULL, 
            0x86A623EED5067B7FULL, 0x2ACE2EFBB8EA0157ULL, 0x099802F5E5006386ULL, 0xD7EE1002ABFF42F5ULL, 
            0x5A36DC6639B98FA6ULL, 0xB9004F5A5906B926ULL, 0xDCC2DB61EB086E58ULL, 0xF07EFE197D2EFAB2ULL, 
            0xB916A43179FB2063ULL, 0x3819193816B936EFULL, 0x9DC916F77808157EULL, 0x3A92C7F293C0D12DULL, 
            0x453D2490110832F5ULL, 0x367A80643BF88E2EULL, 0x91F6886CCBE67493ULL, 0xA3BFBA8ABE92252AULL, 
            0xBBB61D8561879FC3ULL, 0x3249E0C1438BD765ULL, 0xB4BEDA46F40525A4ULL, 0xC9107344F1F09A60ULL, 
            0x9DAE3A07C37776A4ULL, 0x73F309DE8A4610DBULL, 0x056DBDC729B79638ULL, 0xB82821B34A753156ULL
        },
        {
            0x3368B6776D612114ULL, 0xC38C5CA9A5CEE82EULL, 0x47D6B8F56FCA6BEAULL, 0xD366D1F841344B51ULL, 
            0x3EFCD6A9713DCDF5ULL, 0xCAF6F557709BD054ULL, 0x78DDAB93B9B8CEF8ULL, 0x220EEA3D10C21422ULL, 
            0x8C3E137375EDA9C8ULL, 0x3D97EF096FF9B9B3ULL, 0xBE317F8C0C4F0CC0ULL, 0x090E7F8E27D7F9FAULL, 
            0xC96F2455F8C97EF1ULL, 0x4DA38B8DCE84D37DULL, 0x3201D78B19C72994ULL, 0xC37509C77BD196E3ULL, 
            0x4880B9D9DE693077ULL, 0x667AD612057310ACULL, 0x0D0819EE2B3EFEFAULL, 0x7B2D32E0466370F4ULL, 
            0x2CDA0032252BC223ULL, 0xFBBA7DFE5F242A2CULL, 0x7A0B8273DE642F25ULL, 0xE8F5D6C4799273E9ULL, 
            0xFFFA25DAB01483D1ULL, 0xD64587122CF8FEECULL, 0xB3CFC0A19D63F61DULL, 0x63A317D899CD9D76ULL, 
            0x3289CBF0FB8C69DFULL, 0xFD33DC390C8D1AC9ULL, 0x294BA2D06C37D9B6ULL, 0x195159D437A72802ULL
        }
    },
    {
        {
            0x8AE54290F522B402ULL, 0x1E7A2FBB1B018BABULL, 0x084AA8B5FFCCF825ULL, 0xCE5B3C62DEADFBE7ULL, 
            0x1D0F4718829252C4ULL, 0xA61613E7F2BC084AULL, 0xB39A4634D2C6DCD0ULL, 0x1028C1A89321436FULL, 
            0xD53DA3F075567ACDULL, 0x6F1A712058874E15ULL, 0x653C641522FC641AULL, 0xA425054106DB6D2FULL, 
            0x2007F294F1F99359ULL, 0x49832D2A0B6EB00BULL, 0xA99BBFC28BF21574ULL, 0x7DA8A65440B36CBAULL, 
            0xDF3E2FCD1EFDB01EULL, 0x8470EE72EBDA8B5AULL, 0x8F550E18C59097A5ULL, 0xA9A84AD94099E5DCULL, 
            0xD2654CD687C219A3ULL, 0x2231B3B4B6C3529CULL, 0x929BA6D4B6A6342CULL, 0x5BA061F28EC4D5FCULL, 
            0x194C4C570D631780ULL, 0x749B232718094A73ULL, 0x72F59E687CFBA190ULL, 0xF32B79E085A79582ULL, 
            0x0303B6E9B3B4C9EDULL, 0xD69201CE15126D9BULL, 0xA110B970C8788573ULL, 0xD849AC4F326107B4ULL
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
            0xAD5072C7290F9631ULL, 0x22516C8C597D3D15ULL, 0x1AF25711EEA73E81ULL, 0x392B561B13196F72ULL, 
            0xD747A79A7263398CULL, 0x3D11C3CDBABED85AULL, 0xA13F917C52F91E1DULL, 0x811EC72DDCF7FC0CULL, 
            0x6CE688ABFAFC03E3ULL, 0x9C8847DB15199735ULL, 0xB694DB1787647977ULL, 0x060DC97655197490ULL, 
            0xBE8A5A530B59B2D2ULL, 0x3C71B528A0EAE8CAULL, 0xCC59A1ACE00A3DF0ULL, 0xC91FD9D6821B46A1ULL, 
            0xEB140FA3D17363F0ULL, 0x9F28EC74B95A7847ULL, 0xE78F7219CA0ABCEBULL, 0x45301D9565AE1D96ULL, 
            0xE42E5A52555E4939ULL, 0x9132F7B9307528C5ULL, 0x75F27494AADC11D1ULL, 0x89B82931D257655BULL, 
            0x033082C99B12EBCCULL, 0xDE40C2FED9ED5EF2ULL, 0x465766DCC112D911ULL, 0x21644E535173ABCCULL, 
            0xDCDDB832CE1C1E8AULL, 0x64CA566DB7ADDD2BULL, 0x3D51A2ED115E60C4ULL, 0xDFC9B21E5359734AULL
        },
        {
            0x0C9BEFB043A4E378ULL, 0x751140121698A798ULL, 0x9FB66E1B499F08B1ULL, 0xCF137617EC3445CBULL, 
            0x90931C40C36C6F9AULL, 0x81067AEFFFBA4376ULL, 0xE81EE86420580749ULL, 0xFBC13BE390BBC6D7ULL, 
            0xCB515D67C7E25355ULL, 0xD3E3AADBCE1567BEULL, 0xC82AC6CB5A597F4CULL, 0xC23CA034AD8BCD8EULL, 
            0x9947E670ACADEE80ULL, 0x73F989B9ACE068DFULL, 0x202DCC98928D460EULL, 0xBD131D9477D33DCAULL, 
            0x9756C82DD7EB3982ULL, 0x392592F2EB7D1D2CULL, 0x4E4DD28D684A750FULL, 0x2CAD471DAA38EE60ULL, 
            0x6267158D09ED6A36ULL, 0x1EB73AAB2C9BD900ULL, 0x95D4EF57639889B5ULL, 0x125056079CB9A29DULL, 
            0x85753107034C80B0ULL, 0xCD32C2306B0A9E21ULL, 0xF901F27BA7434B0EULL, 0x88B31A702006BE10ULL, 
            0x9E3D87A74A01719AULL, 0x4F885691BB0E207BULL, 0x99CC0AD595E4C168ULL, 0x0D5D2DCB252E321DULL
        },
        {
            0x46BADE1B2D7D6AA8ULL, 0xA3C806014C8C34E4ULL, 0xF9215FAF59E209FEULL, 0x740736E659C19671ULL, 
            0x27C0D6DFD3B5968EULL, 0x44C555D20BAF870CULL, 0x6002362A5C8DFF9AULL, 0xAC1A291E0E35F7A3ULL, 
            0x00BDB59EF61B6388ULL, 0xD29E15B36F12CF60ULL, 0x4DD9EC947F25B96CULL, 0x9DDF3EE4AAA0979AULL, 
            0x98D663CE28CDE1C5ULL, 0x831511F7CB6A313CULL, 0x5FEE95A685F80250ULL, 0x9649F866DF27193BULL, 
            0xA2DCB036456F571FULL, 0x20383DAEB94CC1F7ULL, 0xC33619CC3D0C6598ULL, 0xA8148D9CE0FE1412ULL, 
            0xB129EDD034683B09ULL, 0x7AE292AEB0665065ULL, 0x9CC85EB2CB58C943ULL, 0x613A1E1228C644CBULL, 
            0x3AF0891AD1D9EF5FULL, 0x9D181498381634CBULL, 0xA96E19FE179B9E14ULL, 0x66910115EEE6092DULL, 
            0x30999ED07C4C7172ULL, 0x3A9BD8ABBCC8917DULL, 0x96C5913BC98A8DC5ULL, 0x30085882E788B021ULL
        },
        {
            0xB405BEDF82458EA2ULL, 0xFE31E584893E9FEEULL, 0xB9143022F7F02C7AULL, 0xAC6320619B18D09BULL, 
            0x9B32A2F1278B9AEDULL, 0x1AEB810B0AB2EECDULL, 0x684F1D1E3DBC9BE2ULL, 0x9BC365EFAEA372BFULL, 
            0x09ACC46D6D854D83ULL, 0xD7A7495BB99498EAULL, 0x7365BE236479C7FDULL, 0xA16A015D5D1093C6ULL, 
            0xAE4D435D3E6EBB56ULL, 0x5E94FF85EB650D6FULL, 0xB0839831421E4D71ULL, 0xC953A0ED684E3560ULL, 
            0x2A1CE78917C13111ULL, 0x5126FF9536BEF380ULL, 0x0536328D6F102DD5ULL, 0xF015C65413CA2599ULL, 
            0xDB846279B948DD62ULL, 0xBD83FAD898B6D56FULL, 0xB8AEF446FA428806ULL, 0xF0C89631483A683EULL, 
            0x8F03FD1ACE1B3BB4ULL, 0xD491EEC5A5584916ULL, 0x482F8C69F7BCBA70ULL, 0xFB6090B04423AF12ULL, 
            0xC07B0BE7A3E0B983ULL, 0xA3C8411982DA1B4CULL, 0xB536E0AD586FC344ULL, 0x1469080915179357ULL
        }
    },
    {
        {
            0x297B47D6840F3432ULL, 0xE02B35B68C8CF4D0ULL, 0x39EC980C68C08957ULL, 0x0D4514D02D7AF5A1ULL, 
            0xC8F725EBCDF78488ULL, 0x53B141DFCDEE1E59ULL, 0x1A7F116BF6BBB2CFULL, 0x8B80C19298EC2C8EULL, 
            0x60B0A44DABFFD14DULL, 0x4B164F8DC74DDA32ULL, 0xA48C14527C982F1EULL, 0xA7EBB3A6B9BE1932ULL, 
            0x9975D3CD61B4C7E0ULL, 0xA786969046FAFA57ULL, 0x998C2CFFA9F169A9ULL, 0xED6C797A38D0A0A8ULL, 
            0x3F9339460D8F1D2DULL, 0xAD9F62797DEA3B14ULL, 0xEEDED51A73EB6106ULL, 0x44F9B9C86571F793ULL, 
            0x116D8A394CD0C285ULL, 0xBC6540C529A0CFC9ULL, 0xEF0243A02479C85AULL, 0x873689236644B315ULL, 
            0xEBE82C84E6405233ULL, 0x8B9956F986ECBF7FULL, 0x2ECA81D78BAE950AULL, 0x4993CD5E231985D3ULL, 
            0x2DB0779084FE4256ULL, 0x6820A532CAEFE689ULL, 0xE1C995D9D854E36CULL, 0x381A0C3B9DC715E7ULL
        },
        {
            0x833324F652F1110BULL, 0xF1E1888BCD2CAD32ULL, 0x44EBFD288977F2BBULL, 0x4F0DBBC3106298A8ULL, 
            0x168B6B2DB54E9A26ULL, 0x6FF8AFBA80D87774ULL, 0xEACD7B833844E3FDULL, 0xA1C0D252B6868913ULL, 
            0x6FF701152A87FC10ULL, 0xE2BE24CADBFF0D72ULL, 0xE08037C928474F8BULL, 0x46F0E93A52696647ULL, 
            0x1FE62ED3C2BFE39BULL, 0xAB6C4C4ADC21F7B4ULL, 0x04FE7049E997AAA1ULL, 0xA9CEFC6FCBD66950ULL, 
            0x34B1CF5D95862719ULL, 0xBB2096CE6BDE828DULL, 0xDE66C3DEFC0681DBULL, 0x58B574E38120C94DULL, 
            0xCD852B234C5B57B0ULL, 0x8A9C4CEDF0AD73F2ULL, 0x0D0B40F8398AFBC2ULL, 0x76A954A4CB07CB59ULL, 
            0x6C50046F35491115ULL, 0xE5B263649AE270D7ULL, 0xDCC3F896EE7F7756ULL, 0x779D4F2CA6B625AFULL, 
            0xABC42FC6D07B27C3ULL, 0x596904DDD8FEEA79ULL, 0xEE32846C00ABF8D3ULL, 0xDBA3295BB0A52B57ULL
        },
        {
            0xF83B32939F4F8F51ULL, 0xC2BEA3AFB26A51FEULL, 0x553E0E0CEAF11C6BULL, 0x02F5491968B029CEULL, 
            0x1BF3B78E0240D1CBULL, 0xE244BD99578747D2ULL, 0x63B1CC0FC43CF111ULL, 0x60E3DEAECD28DA41ULL, 
            0x4B454FCD0716E617ULL, 0xFA91A97BBFCA9D9AULL, 0xEBBDEC0271682273ULL, 0x902E3117620377D4ULL, 
            0x9850F12F9562A302ULL, 0x5445FD61C1BE588CULL, 0x55CD674FE7B72A2FULL, 0xFCAC80078C6A35F7ULL, 
            0xFA28CEFB80CDAFC3ULL, 0xE89FA2E63D8391E6ULL, 0x4858AFAE58E64EC0ULL, 0xA5AEAF0D06EFD128ULL, 
            0x6354FF4BEC375CFBULL, 0xD40C941558C7D791ULL, 0xFB78F29D0A3730C6ULL, 0x38FF18754BC4DC23ULL, 
            0x234B056C396C8486ULL, 0xF906B0410F3A86BBULL, 0x336771F4FA49F613ULL, 0x25A59A7A175C2D53ULL, 
            0x85A2BAF546BE9591ULL, 0x7F53E8B757CBBB11ULL, 0x93D13D8897BF3287ULL, 0xC044519B0784D4FFULL
        },
        {
            0x5EDAD36FA7AB6C53ULL, 0xA8AF36E9CF7168D6ULL, 0x142EE9380815DC99ULL, 0x583376469E587325ULL, 
            0x8A9DD5F211610351ULL, 0x5363DFD5B40BD094ULL, 0xE3E5FADAD72A3C0FULL, 0x7DA8F4BBB3EA0FE5ULL, 
            0xE47EFED3F350D665ULL, 0xF5CEE152AFBFE1C7ULL, 0xE0073CF7B1D4CF18ULL, 0xED03A12A9A616EBEULL, 
            0xC0E03979A1AEA7ACULL, 0xD05E1C41CDC2A53DULL, 0x4C7619F9B75324EBULL, 0xD51DAB022BB7F603ULL, 
            0x95CEFB651C8EA9C9ULL, 0x01289B2E2DFA6A64ULL, 0x11E039E4AE1E81F0ULL, 0x5E704B29DE0640E2ULL, 
            0x63D6E665CE3CEE16ULL, 0x8F2E305D900126C3ULL, 0xA765287926A03529ULL, 0x089733829C6E53DEULL, 
            0xC892147A64085FABULL, 0xBDDC924561913178ULL, 0x4C2230DC3984D487ULL, 0xB4AD716C36850F98ULL, 
            0x57C7B298D84BAE7BULL, 0x78E136CCCB5CF778ULL, 0xE4E8435A5B98D7E7ULL, 0x52603D5EF7C10182ULL
        },
        {
            0xA4105EDA93A68CE4ULL, 0x24E6A953070CEE22ULL, 0x789EBDCCD20F22DBULL, 0xFD83A4BF06CEE07AULL, 
            0x3211A07673A6F003ULL, 0xC433507619A25A54ULL, 0xEFB12C0298D8C89AULL, 0x2DDAD8E141F8AA4CULL, 
            0x102703014DC99402ULL, 0x6C8149C78B30A64CULL, 0xF663D22A33F5F62CULL, 0x19F51685C5365A91ULL, 
            0x1C7BB87DA7181C95ULL, 0xD80DBF222997B111ULL, 0x3DD0BA8BE5FADF00ULL, 0x554CD023A15BE4FAULL, 
            0xC3425B54FF2CB4DEULL, 0x089DE838689CC279ULL, 0x30EB8164D41AD023ULL, 0x09A7F97BBB310205ULL, 
            0x69D195DEB7F96253ULL, 0xDF72BF63C3E6426AULL, 0x2E2776FB74621B50ULL, 0x9F0B049E6E2F10DAULL, 
            0x6322B9F281BE6552ULL, 0x452ADC52E94408F5ULL, 0x082C2B8D1E2CE6DFULL, 0xC60B74B9445AD597ULL, 
            0xE02CF5BA6015B809ULL, 0xAFF105BC92F9219AULL, 0x97BA39F4C2DF7BD8ULL, 0x546BA666FA6C5786ULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseBConstants = {
    0x4E562F861F3CA5BCULL,
    0xFEDE7A03DE602E67ULL,
    0x5DCFCD1101AA9EA1ULL,
    0x4E562F861F3CA5BCULL,
    0xFEDE7A03DE602E67ULL,
    0x5DCFCD1101AA9EA1ULL,
    0x400347EB8673F70AULL,
    0x7B68F21C46B9AC2FULL,
    0x85,
    0xD3,
    0x03,
    0xAF,
    0x1F,
    0x94,
    0x6F,
    0xCC
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseCSalts = {
    {
        {
            0x07019ECBB4274C67ULL, 0x1F3F16449F836B9CULL, 0x2B0156FD79F13C25ULL, 0x058678512572B8C4ULL, 
            0x147BBB885C7B238DULL, 0xD15A594A72862356ULL, 0x8DC25EBAF36D08D5ULL, 0x6464F18F84F26CDDULL, 
            0xC0CED25E0979C467ULL, 0x6BD9D2F087BD62CCULL, 0x89C849032E56CBE7ULL, 0x846CAFE96C298C50ULL, 
            0x44ACF2E705FCF8ACULL, 0x4185A3D30E66B0F0ULL, 0xD50A538B62E06992ULL, 0xCF67580B21C24EB9ULL, 
            0x826BBDD45B68A96AULL, 0xE425FE91A7089C2FULL, 0x55C1B58FA63F3AF2ULL, 0xFC36E58F4830A354ULL, 
            0x6174826DC4F7E288ULL, 0xC75AC26B8F6FE9C7ULL, 0xAD1DF6A9B45198F5ULL, 0x67307E2A753AECA0ULL, 
            0x9284D1CF70BB5BE7ULL, 0x5EBE186886366C40ULL, 0x6450F174D369AC6EULL, 0x6B832A5B12EADE4BULL, 
            0xFBBA671AEBB39458ULL, 0x544EBD59DC03E1ECULL, 0x9C023E2A6D9D28BAULL, 0x8AE09B83BE3D1C81ULL
        },
        {
            0x96C10615E315960DULL, 0x3587DC8EF949CE03ULL, 0x8823746498CED0D1ULL, 0x3BC384E38810F91BULL, 
            0xDC4DA97AE223D1E9ULL, 0x02086CDB1C25A80EULL, 0x1DB82D2314B4DEC6ULL, 0x01BBA119F70032E8ULL, 
            0xEE71EDC9D17A999BULL, 0x3B61BDFA8B54233EULL, 0x15640D794E9EB813ULL, 0x59575A5E7C6F61EDULL, 
            0xAE5D2F2FD18205D3ULL, 0x27F0F0E3464ECB51ULL, 0xE13021612FF56F00ULL, 0x7049A753D834CCD2ULL, 
            0x3E13A81E4D6E93C4ULL, 0x6366D11BF016A3F5ULL, 0xF1972C7974163E57ULL, 0x54C16B7C8B2EA3BBULL, 
            0xE5840072E09A9D13ULL, 0x42558232E7473FA8ULL, 0x58A35A6967AC4614ULL, 0xDB1920C5ADF3FC29ULL, 
            0xCB0BC067F864FB42ULL, 0x1337FB068E1CB96BULL, 0x68B7DD5409BAD2FBULL, 0x0E5B325382C0898FULL, 
            0x04055818C8E51EB7ULL, 0xAF60D55F64E645DEULL, 0x9B643B6E5508F7B2ULL, 0xA9EF39DA0DB4B836ULL
        },
        {
            0xAB157F70463C6A18ULL, 0x2E62684ECD9673E3ULL, 0xA0F43DC3495B737FULL, 0xB64676710055C909ULL, 
            0x9F20A5FBA317C237ULL, 0x3FB240DBF7A993D2ULL, 0xB6C9FE8A3A971133ULL, 0x43772838926CA86DULL, 
            0xF5CEC370C353B0FCULL, 0x55999A69083F147FULL, 0x9A48DF72F493A011ULL, 0x00915214D2B5AD46ULL, 
            0x2109573226148A06ULL, 0xC333C090D6D0C4FEULL, 0xDD790B2D3CF4D9ADULL, 0x900068252345F1DDULL, 
            0x608858A1CFF1541CULL, 0xEB53FDC2CFB9C94FULL, 0x6AE589A5E91507BAULL, 0xC622DE2FC8E66F5BULL, 
            0xDC97664214E6756BULL, 0xB6CD76552299B443ULL, 0x3BCA2A448F93CAA6ULL, 0x057E4032BD61936FULL, 
            0x211E0A920A1629C6ULL, 0x29C12DCB68775AFFULL, 0x0D3E59F47F3820A0ULL, 0x538E256DB36C0AA0ULL, 
            0x760464F1FA5D55C3ULL, 0x4D09D3D99EAD8A84ULL, 0x56AEDDAFA625CB0DULL, 0x68A0C8F6AF33B85AULL
        },
        {
            0xF8DAE65487270DF6ULL, 0x6990C9A337ADA990ULL, 0xD13F6B8FE40A5B25ULL, 0xB45EF503A5F88E2AULL, 
            0x68A2211FE43D3058ULL, 0xC3087C7D927E174CULL, 0x0CFBC0478C848CACULL, 0xCED5379A245DBBD3ULL, 
            0x4CD29F2DE38D1DF9ULL, 0xA9FAD7F86BD6A9FEULL, 0xC26C5332EE349657ULL, 0xBC4B874CD75CEA6EULL, 
            0x54C7561B736E3138ULL, 0x41488BE77732BAC7ULL, 0x1409247358DA58EBULL, 0xAB5A63CFD98BD2A6ULL, 
            0x531660ACC2887FF4ULL, 0xF11678B2F34A50EBULL, 0xF9A7C547B4A809DAULL, 0xC4B65BA051BC7449ULL, 
            0x58B1923021EBC64EULL, 0xE0F893598C8FEF6AULL, 0x7460A8051A0CD7F3ULL, 0x6003571069CAF17AULL, 
            0x406CC49B5221AE0DULL, 0xED221087DD244489ULL, 0xD12311F15708ACF3ULL, 0x8F332BCA0AAD6CEFULL, 
            0x5AC8A4AA8F398941ULL, 0xCB031A65B5189063ULL, 0xE935B5F900EC1FDDULL, 0x382DB5E56CE93F19ULL
        },
        {
            0x103EC4AD582F924EULL, 0x803C24FB3D655A87ULL, 0xE82738FE0CF821CCULL, 0x6E5EC000F11EFB6BULL, 
            0x41A04C4B5963C0A8ULL, 0x89F82BF0BE15A6B4ULL, 0x1523CFEC2F9EC7C0ULL, 0xE8DEC7A2A45EEFFAULL, 
            0xA95C307D9825BC89ULL, 0x88F79EE4BF071E4BULL, 0x7455D038577B3D22ULL, 0x2F784393A699872BULL, 
            0x58F6AF73439AF153ULL, 0x55098334D94E6454ULL, 0x279C216231E53BE7ULL, 0xD4B347891D57012EULL, 
            0x80B6CD52C262DAA4ULL, 0x02BE83E85FD255B9ULL, 0x29B670B334582F0CULL, 0x450743D07B99D4E8ULL, 
            0xCDA0C8583683C949ULL, 0xA675277188A1B4BDULL, 0xFFC678FDD2779933ULL, 0x36619ED6750855F6ULL, 
            0x576EC6D38EDD4508ULL, 0x3D7737D2F3A739FCULL, 0xBB03073D5549DEEAULL, 0x7A4E2C27318E37E5ULL, 
            0x87A07BDA088AD21DULL, 0x706E6F0E85E3A675ULL, 0x2D816A51360A7872ULL, 0x66C7866BB2F6A2CCULL
        },
        {
            0x739B9771FA748605ULL, 0xB4FDFDCA50D9FD62ULL, 0x71AB564A4AC1FFD4ULL, 0x8ADF3BBE727BC0C8ULL, 
            0x50DC5A7903DA6F78ULL, 0xF7A46465DE92629AULL, 0x14C43C22CE85D21BULL, 0x088425FE66C33422ULL, 
            0x8966BFAA34FAEF28ULL, 0x4F9824D4ED4EF754ULL, 0x950FD4120CEEF8F5ULL, 0x8764082EDF12C265ULL, 
            0x6427C9F506858B86ULL, 0xEB158A8DB2F887C2ULL, 0xF4CC9C8A5D23BE2BULL, 0x88DF0ABD6978FA37ULL, 
            0x28CBF399A3E4D0EFULL, 0x925ABA16E31BF089ULL, 0x61405ACF59A69710ULL, 0xAF106A443D5F1519ULL, 
            0x339493A179A41BD3ULL, 0x5F60939988791F19ULL, 0x14D7C90E5DC00772ULL, 0x68AB652780F8980FULL, 
            0x28476E1D1BFC7F86ULL, 0x2A87179A43BDB9F8ULL, 0xF5EEC1CF53AF3031ULL, 0xE672D91354578CCCULL, 
            0x151E760D44B08311ULL, 0x6B74B99CD7BBFD6EULL, 0x0F629FA150820948ULL, 0xCE1C6C17EACDF324ULL
        }
    },
    {
        {
            0x9D05A8022A3471FAULL, 0xEB7980758E407F0EULL, 0x761D0DA30FA5B574ULL, 0x5736B8E1EA98F8E3ULL, 
            0x3411EED63E138292ULL, 0xFBADC53D99422503ULL, 0xC404C69E70D0A358ULL, 0x8C025AEEF3915964ULL, 
            0x0B8BF167F1AEA76FULL, 0x78881EFC58474E92ULL, 0x38F97EAACA6ED08EULL, 0xBEE4569A71EFF145ULL, 
            0xA369F030B12B30DCULL, 0xA7DA255D9950BD8DULL, 0x5CDD7180C94605F5ULL, 0x1FE65FA1239559EBULL, 
            0xE1B0C2D004244DDFULL, 0x124AD7D7756A8EF9ULL, 0x8CD6500D9F9BBCA7ULL, 0x1238E798D407F081ULL, 
            0x99FBB8BB69F234BCULL, 0xF6FAFD36B8ECEB00ULL, 0xADBBF11F3B9B2202ULL, 0x9B980B470755DDD2ULL, 
            0x95068A1C2B16C201ULL, 0xF1D24E4F4E09A29DULL, 0xCBEF121B948EF306ULL, 0x60DDCD7A5B81B10AULL, 
            0x73E721CC21EE018BULL, 0xE35DF7C6E12204B9ULL, 0xF138156E882108C2ULL, 0x2AB0EB8441E86220ULL
        },
        {
            0xED5DE1E0B81E8E80ULL, 0xFEE638DA2B9C0DEDULL, 0xE58C7BA399269431ULL, 0x6DFCFE475D4B9F9AULL, 
            0x88DB6E33A12DDF59ULL, 0x310F37DA1EE55A17ULL, 0xCC8B8C0C66E310A8ULL, 0xAB9616636D54A477ULL, 
            0x87008A9E21785C56ULL, 0xAA9A74E99EE5A5C2ULL, 0xA74B560DE65EE4EBULL, 0xE579F9BB322627CFULL, 
            0xD837D80CAF896687ULL, 0x552A8DA2F04FF937ULL, 0xFB14DEEE4384E3D5ULL, 0xD25C41328A68350AULL, 
            0x5871ECC07CE9FFE9ULL, 0xAB7D5C99A3CC19CFULL, 0xBA815BA5DD1728CBULL, 0x3E8A7D15695181CDULL, 
            0xD4E1BC4CC7FBE0FCULL, 0xDB9AA2E036B43E66ULL, 0xDDFCECBAA0531361ULL, 0x8D09DD1321990A95ULL, 
            0x9F26F90AE75A9EDBULL, 0xD5C3CDE202068B51ULL, 0x93A6905642FB53FAULL, 0x5DDD192D0D4B9C0FULL, 
            0xF1D5BAA3C358A44BULL, 0x23E06C8E7C48D2B7ULL, 0x695BF058FF5B183FULL, 0x49DF659767F03C91ULL
        },
        {
            0x5E39FE059230FD6FULL, 0x4F613BD99F78A94FULL, 0x300A00412CF7BF1AULL, 0x844F29F64BCE50A5ULL, 
            0x9C13E17439A0C528ULL, 0x9761D301CAED2FC6ULL, 0x6B48B3C2409B8F27ULL, 0x7AC3C2D2807A3B70ULL, 
            0x411AC95D31220232ULL, 0x74189B0B955DCD45ULL, 0x2E5B870420A9D70EULL, 0xDC7B7640B295EE49ULL, 
            0xF927E46FBA3FD773ULL, 0x34AE7D3E31B59DC3ULL, 0x52759F1D3F02594EULL, 0x5AFDF74DC07134E8ULL, 
            0x89E847A438C7C1C6ULL, 0xA5274EC364C35492ULL, 0x65420919E6A70D57ULL, 0xEA105115A00B0D23ULL, 
            0xDE03EF4B4FBA594BULL, 0xA7267F401EB2F445ULL, 0x6764D78B88204FDDULL, 0x34E9DBA8552C4EC2ULL, 
            0x60209D2A0B6E7E16ULL, 0xB2C4167C10C0BE7CULL, 0x78FD2A16E8772167ULL, 0x2D0837465521ECD9ULL, 
            0x388E1B60454EA94EULL, 0x96848BC1F6977318ULL, 0x397885E5494C594FULL, 0x80E981A48E98D8CDULL
        },
        {
            0xCA0C25DF6F1C9D39ULL, 0x301B2A9879CAD804ULL, 0xB420A286B30D66EEULL, 0x2ACA8592908F64CEULL, 
            0xFE96B16DCF988ECBULL, 0x30C497CE893EB319ULL, 0x1BA43C84612A0670ULL, 0x698FE323F397D062ULL, 
            0xC3F90D19C5BBD20FULL, 0xA1B5060AE0870A19ULL, 0x23324792D9C8FB02ULL, 0x1D183B0E6BCD0156ULL, 
            0x42C9F7B52F2E222FULL, 0x9E47E74EEF1B4103ULL, 0x5814DC04D1E74DBAULL, 0xCF187E28205B639FULL, 
            0x0445C98E1CEB32F4ULL, 0x152377F9A1325A53ULL, 0xA18385460B35FCC8ULL, 0xABEC744961B65A84ULL, 
            0xB668FB7E4FA1F432ULL, 0x02B687D29B034C6DULL, 0x9A1CBAC68D5E7D86ULL, 0x19D16BF8D70D43FDULL, 
            0x710260BE4C4C6B9BULL, 0x9E8F273DA03746BCULL, 0x1B19DCAF94122878ULL, 0x30104CB4501BA3EEULL, 
            0x124DB954661E38CCULL, 0x959122AF28D56D26ULL, 0x5C19158EBE45CBE2ULL, 0xCEDA1723161A5124ULL
        },
        {
            0x7F1C09EF2783DC03ULL, 0x624DF27D70C71EB4ULL, 0x491B2992AC6288FFULL, 0xAE91D4AC9BA755BEULL, 
            0x54CCDE5AB147698FULL, 0x90BABB451A8AD8B3ULL, 0x6125FF295217C921ULL, 0x2A6FF0BB41736F6BULL, 
            0x1DEA0977FF15311EULL, 0x998C050413BEC74FULL, 0xD1FC61F6DABB7710ULL, 0xCC88C2430083B175ULL, 
            0xCBD04042ADF2EE9CULL, 0xD61AF1ADDA03DE47ULL, 0xBB82C9AE56D6C5DCULL, 0xBE6B824201962EA5ULL, 
            0xB75FC7240D9934B5ULL, 0x30EA575E75B1E79CULL, 0xDA5A318FD17DD957ULL, 0xF32B2FC32C9CA8E5ULL, 
            0x9DBE6E572D92EBFCULL, 0xBB183EAD2E1EDE1CULL, 0x68D4AD408302CA7AULL, 0x07A6A30FF46F8D46ULL, 
            0x464A140BA3848894ULL, 0x7E72AD4557F8D617ULL, 0xBDE2CFA2CCBABECEULL, 0x3A73F06B16032CC1ULL, 
            0x6959F8CC3F3AD3B8ULL, 0x58790E8AD052A2B7ULL, 0x5C2260FC8B837939ULL, 0xA480071AB8BB5575ULL
        },
        {
            0x15DBCC53229C2DBCULL, 0x9BD9556F0D4B7187ULL, 0x07C32A44799457D1ULL, 0x8C0019BC871B6574ULL, 
            0x17C4D85EE7B82ECBULL, 0x99C8CE183A119E2EULL, 0x8C90DB03188888A0ULL, 0x1840EB116DF44AAAULL, 
            0x791DA4EB6116E71AULL, 0x9935E302427965CCULL, 0xB7E1D6A962149F51ULL, 0xAAC86839B9AD54D0ULL, 
            0x34E295C0FC3E7B86ULL, 0xC8C44AADAB6CE7A5ULL, 0x6B74046590B3642FULL, 0x3CAB45BA37F6FE9CULL, 
            0x4AB23BB28CB128F0ULL, 0xAC6358301FA01E2DULL, 0x3EF1A2053497FE20ULL, 0x7CC244E584E5DE85ULL, 
            0x769F41E66E25351EULL, 0x2BC832959EC1F94DULL, 0x6CCC519C4A051926ULL, 0x9E4085DCE13F341AULL, 
            0x52E4CA2CCB4ADAEEULL, 0x5A628F7F345BDE1EULL, 0xFA0CC2D931F5E8E6ULL, 0x3341078B95736988ULL, 
            0x14A8CB5175495F7FULL, 0xD54E644952091678ULL, 0xC2B97CDC43C1D3D2ULL, 0x0D9CEA8C3438A3D5ULL
        }
    },
    {
        {
            0x309BE9D506E1987CULL, 0x0FF678E0EEDD33A9ULL, 0xC04513202EA4B37EULL, 0x74192C02F5A0B483ULL, 
            0x5ABA7A6CDEF8A0FFULL, 0x337E7671E0C3A592ULL, 0x904AF9A7F986C7D2ULL, 0x2240A7D57D51CD0AULL, 
            0x393277B17180BE4BULL, 0x720F4EAFCB8DDD64ULL, 0x527D08E8F35BEE3CULL, 0x5EA1F2ADD38839CDULL, 
            0xB52DF7D8F72B6A9FULL, 0x5CF4C0E3EB525B30ULL, 0x698AAD7C095F81CCULL, 0x5D1242FE45A868FAULL, 
            0x1B8CD14B0746EFC2ULL, 0x289721B9DD9543C7ULL, 0x9E17B968324BF8E0ULL, 0x5FEB4CE358285DBFULL, 
            0xC07C85A934D46140ULL, 0x6CAE13BC57C177D4ULL, 0x29F9B3AD29912FA3ULL, 0xFD99D8B6D8CDBC06ULL, 
            0x11061CA96A9CDC5CULL, 0x6FB676E291A84274ULL, 0x4364C0AAFC3029BBULL, 0x6A2BF8618CFA151CULL, 
            0xDB6A116004D614E8ULL, 0xB6BADC5FEE87AC06ULL, 0x82E4FED34BD62430ULL, 0xFF808189F5A9FA20ULL
        },
        {
            0x549114E23CC7F48DULL, 0x4A1BDCBE2CF9ADA4ULL, 0xDFF28BD839BB2E0FULL, 0xF8D30E446F92FE9CULL, 
            0x0B51702EB25633F0ULL, 0xFE411EEF24E59F66ULL, 0x8EC1EE1324573221ULL, 0x9EED1926049D549BULL, 
            0x50503B319A8F8590ULL, 0x5F47B2B896860DE7ULL, 0x7CCD90A065687738ULL, 0x250AEDD4D4CB4249ULL, 
            0xFC8466762323290EULL, 0xA08FD8F08779A8F7ULL, 0x26E3415DB242EAD3ULL, 0x38F798B21CEDCB00ULL, 
            0x1D6EFA5C671A792EULL, 0x3BBC6441DD4920EAULL, 0xC1CFBC5081232393ULL, 0xBE274835239C3DE5ULL, 
            0x5ACA9CD937F5E6ADULL, 0x86B6FEFA82B04489ULL, 0xDD54588E186717AAULL, 0x3DD32ACE2284680DULL, 
            0xE3D3EA80EB7A2BF7ULL, 0x32C69D471260E0A4ULL, 0x7666E2784088345DULL, 0xD72DF5B625533E38ULL, 
            0x16E054DC6E3BDA8FULL, 0xF11171F4086A6ADDULL, 0xC5F6CAFE86439F0BULL, 0x7538DDC6C00A7F1AULL
        },
        {
            0x390BFFCAD7BDCC03ULL, 0x72656676E313AC37ULL, 0x4F8647363C41164BULL, 0x09CF00CDB4EE2B83ULL, 
            0x072CF4BB53C3707FULL, 0x670B22AF42719BB8ULL, 0xEE29FD344FDBA7CBULL, 0x0EFE0993611A6832ULL, 
            0xF4EC9ABE125A97B5ULL, 0xC40A70A6A4D415F1ULL, 0x7D3BCA7CC3821AE1ULL, 0x3B957ABFF1204A5AULL, 
            0x6F97C6A63704D438ULL, 0x03CEC870AA2B6240ULL, 0xB0CBC2B1EE213C34ULL, 0x7480BC08A9FBF7A3ULL, 
            0x311EB65EA167A984ULL, 0x8E8B748AA8E3F695ULL, 0xF4302773F5D9DE15ULL, 0x642DE611C96A458EULL, 
            0xD26D60C1509D0F4AULL, 0xCA793095AB9F74F1ULL, 0x654C747C5F3041C4ULL, 0xCC1E3EA0C82DC65BULL, 
            0xEF50D0B87648BF9BULL, 0x9A4477FBC5FC96DFULL, 0x6353FDEF02328F63ULL, 0xF6E4B1515D47B1DCULL, 
            0x7DC9AFFAD7DD81EFULL, 0xD0B96834F84C3099ULL, 0x3EA570DE0F45252EULL, 0x28846EA6CE729538ULL
        },
        {
            0xD1CBB3A647FFDB3CULL, 0x155E129E440DBD05ULL, 0x477997B93B8CBF35ULL, 0x49118552F185A897ULL, 
            0xB723784512BC9FBAULL, 0x4B73DCE5BCB2E133ULL, 0x3B01A35E5BF1F198ULL, 0x08E8615D221D38E0ULL, 
            0x73734EE489231535ULL, 0x8345624623214D4FULL, 0xDFE36BFF35BF7235ULL, 0xEFB7E4F87BE1CBE5ULL, 
            0xD6FB8FA91D7F4B9DULL, 0x664BCB7B2EE9832EULL, 0x9B2990F837940836ULL, 0xDEB459349CA90591ULL, 
            0x1800D6490B0D69F0ULL, 0xED77185E40708B52ULL, 0x791A8E3E63096330ULL, 0x100F857238306015ULL, 
            0x02E3AD40635C669AULL, 0x407D4ADFF7FACFEEULL, 0x82805AB1CBD1DD59ULL, 0x925E5119A0E25BBBULL, 
            0x389AD82BFDFD1297ULL, 0x1A651A38A022D391ULL, 0xA5C64C1E0E5C0E39ULL, 0x1588A6A12787A8C1ULL, 
            0x11750E1B99812866ULL, 0xEBD7922834DB5655ULL, 0x7DE82927AB351D07ULL, 0x03B9BB18C7348D63ULL
        },
        {
            0xD727BD7B0C2F52E8ULL, 0x276E77A1F8860F88ULL, 0x702239A97FFCF695ULL, 0x9DB9C45553D2E3EDULL, 
            0x1548DB1832741105ULL, 0xE1211B509BDC76CCULL, 0x298EF0A0467D10DFULL, 0x855AB4E9D2E78921ULL, 
            0x39767E0B432D018FULL, 0xA6AC5034B106648BULL, 0xBC70BFDFDB85A380ULL, 0xDD921DC2FE9B85B6ULL, 
            0x085D8BE4AB699A6DULL, 0x49FAE647ED00D8FAULL, 0x734FB21FF74852E0ULL, 0x616DC81A8BD477D7ULL, 
            0x9DE76AA89C0CC79EULL, 0x839DCB2D41A56872ULL, 0x55EA17A780F16745ULL, 0x76BBDDF9A7CD3EC2ULL, 
            0xBC94351C4A654322ULL, 0xAFEF19FA75526A31ULL, 0x924D273BD79FE07CULL, 0x9D41E8B770C1F689ULL, 
            0xABE6BF97D95E0E0EULL, 0xD880D26214901DFDULL, 0xC66093900AB43D65ULL, 0x84BA5272E3851453ULL, 
            0x60A86FEFE4B2AC68ULL, 0x68E9B90ADC17B4FFULL, 0xCABDB1FBA440E508ULL, 0x68E254C052C1CBA5ULL
        },
        {
            0x67A29907D450CF77ULL, 0xB50FF6927A1C1B61ULL, 0x31807BA905415F9BULL, 0x597F3719E5AF799CULL, 
            0x4A5150B5A0605507ULL, 0x3FFF1357F4A001E3ULL, 0xEAAB692BF1AAA421ULL, 0x077901577E166AD1ULL, 
            0xAD1145D59A705CB6ULL, 0xA88D3203083AC314ULL, 0x35DEDDCE25013639ULL, 0xDE93C02E86D78B33ULL, 
            0x009F4A1E3BE4FF0DULL, 0x2825A48E06C00C95ULL, 0xFE97454035E8AC8FULL, 0x7DD914D3B1D13343ULL, 
            0xAEF3D6CD444ADF83ULL, 0x69FE250ED74D7822ULL, 0x2C036BE8B560E636ULL, 0xE2097A76E7A99BC1ULL, 
            0x34BCA6F1FCCA167EULL, 0xB432AAEC89928431ULL, 0x0F918183EF4CF3CBULL, 0x7A23AFAD790B98DFULL, 
            0x394BE6150B36620BULL, 0x8059E216A8D6936FULL, 0xB9D1B078C3A68094ULL, 0xA6FA8E023D1CE090ULL, 
            0xB1DCFAA98B7D8C79ULL, 0x716E3A44FE6E1040ULL, 0x4D62C07D0C4A760CULL, 0x1E7AD17719B5D1C0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseCConstants = {
    0x0E6006F3A01CEC5CULL,
    0x24DFC36BA6C55AADULL,
    0xFEEDF251F1EE1749ULL,
    0x0E6006F3A01CEC5CULL,
    0x24DFC36BA6C55AADULL,
    0xFEEDF251F1EE1749ULL,
    0x5BC37A03375CFE24ULL,
    0x5D36F4855FA4C3C5ULL,
    0x0D,
    0x1A,
    0x5F,
    0xF6,
    0x52,
    0xB1,
    0x7D,
    0xAA
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseDSalts = {
    {
        {
            0x9BEA7DB037023943ULL, 0xEA65832BA70BC3ADULL, 0x7872F7E5F1664BCAULL, 0x17F0EE6126853A6BULL, 
            0x80F10BFBEF905B97ULL, 0x3CE628F421B7E234ULL, 0xCB9C227AAA36AE1BULL, 0xC2E65A31DDA21070ULL, 
            0xDD074AB66F51FBD1ULL, 0xB751652C176E8542ULL, 0xAC9BFED549E1BA0AULL, 0xF6779F9158102D33ULL, 
            0xD99837A1C30DCF20ULL, 0x3A1DEFB8AE845176ULL, 0x4DDCF7190037F90CULL, 0xA2E1A695B8F32FE1ULL, 
            0xD99FD69B9261DD05ULL, 0x088A72078BBB3195ULL, 0x15C76FDC54BDA3CAULL, 0x3143220CDCEB2BB0ULL, 
            0x3AE8DACE84DA397EULL, 0x8859E3DFA76E7964ULL, 0x2DEE348C48F4D8EDULL, 0xE28BBA52FA51CF1CULL, 
            0xA939D825B33B6994ULL, 0xC935511317984311ULL, 0x9548D20135C39602ULL, 0x0CA5CEF43AF917EDULL, 
            0x6CBB0F79A6BB1F75ULL, 0x68C4BC340FB0220AULL, 0x8AF7204910EA6CCCULL, 0x7658A55B36A9A3BAULL
        },
        {
            0xE3E1B545F164A4E5ULL, 0x7ED7985E03645756ULL, 0x0E502C2E6DA59811ULL, 0xE947B2F04F8C1745ULL, 
            0x6AADBA0FA28282CDULL, 0xA510F33E160F8FF9ULL, 0xAA3A000D126EBF91ULL, 0xAC689386F89080FCULL, 
            0x55D10F7C3280FBF6ULL, 0x7943C07A3E4C255AULL, 0xC78D2E04BF840C69ULL, 0xCA21FA9AF9A280ACULL, 
            0x18AE904EF13FE411ULL, 0xEDEBA243FF9168E9ULL, 0x6385D20DBAC5DDB6ULL, 0x8BF4F328379F59EAULL, 
            0x447A9AF785E7C41DULL, 0x26FC486CA12AE6DBULL, 0xB2A042B35E0AE398ULL, 0xB3A91964B410B09BULL, 
            0x6AB79F1EE5804301ULL, 0xF5CFF8528DAB188EULL, 0xF0B0F97D2B7E154DULL, 0xE23ECB3EED11CD8DULL, 
            0x8CB04480B8D88C18ULL, 0x3686F0F72B2E30D8ULL, 0xA7E83546514B4F35ULL, 0xB9C2034B00922FD1ULL, 
            0x87716DF2669C405EULL, 0x8BFD51B971C33C2EULL, 0x31FB633686E5D500ULL, 0x887B9CE73A224636ULL
        },
        {
            0x15BBEDA307CD0A74ULL, 0x887DE8BF47675387ULL, 0xB6D03CF660F5AA2DULL, 0x077164EA9742A8A5ULL, 
            0x3F734D071A57AD8FULL, 0x4452C5EBD8A4FC8BULL, 0xC641C309DBE3BDCBULL, 0x3DAD75533A270CA4ULL, 
            0xABE82A0D05A8661EULL, 0x7E7BCB5CF15692FAULL, 0x32E5E7CD9F557A9CULL, 0x0E07BD7F3655A182ULL, 
            0x77900F425DE363CBULL, 0xFCB1F19FEB669807ULL, 0x98B653649B42F800ULL, 0xCD68CF6C1C28AC02ULL, 
            0xC576DFE45B3CA053ULL, 0x761442B66FD769A5ULL, 0xC1B89D1A7F5D5B53ULL, 0x2125EE4E4DA49E93ULL, 
            0x26FAC9CB272231E7ULL, 0xB62F014C7E48434DULL, 0x676D7A4DB4734737ULL, 0xA7D20C443F6DA4B3ULL, 
            0xB6CD23FCACDC910FULL, 0x51E9625DD0C6467BULL, 0xD80EA16ABFF44BBBULL, 0x59BEE1307402EF70ULL, 
            0x154F4AE277EE64B1ULL, 0xCFA3E326DCECC387ULL, 0xD7DAAF2E22452A4EULL, 0xC063B4BB91209F23ULL
        },
        {
            0xC691F1EB5A976FB2ULL, 0xA1EB10478ADFB044ULL, 0xF1FABBF0940B7854ULL, 0x56B9F79BDB3F8CA7ULL, 
            0x52206716307BF806ULL, 0x4FD1AAC086E084C5ULL, 0x4CE5F2E5DCC5F5CDULL, 0xB8D2616D2CB0CF65ULL, 
            0x94DC0148E81D61EDULL, 0x1757CB9CA7A8BAF5ULL, 0xFD0D7D16C06EF0D3ULL, 0x0D86901D756364DCULL, 
            0x60FAACCC6B638D8AULL, 0x8C39F37D699ACD03ULL, 0xA590FA28CDBBB0C1ULL, 0x738A8365333BB508ULL, 
            0xFD68B27FC88D1C57ULL, 0x252315675366AC32ULL, 0xFAA940C763FFC5BFULL, 0xF7BF614E0600A4D5ULL, 
            0xC584F2DD929DF3DCULL, 0x771D1C3FDC56FF0BULL, 0x4AED2A2EDA9D8FC5ULL, 0xBAF95A1E8E9C7812ULL, 
            0x7BE698D5A7484885ULL, 0x7019E93BC67ABF70ULL, 0xADF9C605DFF119E1ULL, 0xEEF4811E7C86BC17ULL, 
            0x7DF191013F3FFC2AULL, 0x84A63004DABE6DADULL, 0xC3CA6DCA978D05A4ULL, 0xB4324C25082B507CULL
        },
        {
            0x0ABEB73EFAC3ADC5ULL, 0x2472D79E7F6B0C6AULL, 0x256C0EC2088BFC90ULL, 0x0482505DEDCF980EULL, 
            0xD52473CDD73A3139ULL, 0x0F83FE2971995DCEULL, 0xE493ADDF525B1CBDULL, 0x52CF6B17DCF31C22ULL, 
            0x9651408369D62B4BULL, 0xFA058945262D89E2ULL, 0x616C5B17D3DEC2D1ULL, 0xC8FA8F1BDFEB67C2ULL, 
            0x9180CBE694FDADCEULL, 0x05DD3A5EDF5F8867ULL, 0xC355890265CD6834ULL, 0xBD7FB36D76ED5896ULL, 
            0x34BCC531B6C88896ULL, 0xDDA46A873C746881ULL, 0x0448BC7657B8319DULL, 0x3E48405E61A826EFULL, 
            0x7CB36A2F4C64DEBBULL, 0xC7056B3E362F84ADULL, 0xF3203FAB2354ECBEULL, 0xCC47CE90183909BEULL, 
            0xEA8DCFCEB5F6A531ULL, 0xE35470F032A1B5E1ULL, 0xCA703580762A9CC2ULL, 0x9A0E3A15F430D2B4ULL, 
            0xE37254D6851793B8ULL, 0x1F167BC140FCEE6AULL, 0x8BCD83921A11AE94ULL, 0x9223C6B60FAF51C8ULL
        },
        {
            0x4CAFCEB672F34D23ULL, 0x2AA0C171029C8A76ULL, 0x51A6CDBFEF1031EAULL, 0xF102246911C40E01ULL, 
            0xF3E02756E88A6A87ULL, 0x129A43F3BC81D807ULL, 0x3EE03291329B8C9BULL, 0x8A77CDDEEF798DE6ULL, 
            0x76762E6B1AD1F25BULL, 0x98B3049A0102C3DAULL, 0xCE172DD2C469089EULL, 0x982FCBCCB25FC481ULL, 
            0x626625E9BBAA1BE7ULL, 0x3CA889B6DED486EAULL, 0x8EB54DD814C53131ULL, 0x65C20D056BC3BCBDULL, 
            0x57872C73502BEAACULL, 0x68A3589DEDB3B60BULL, 0x3FB393A5DAC115C6ULL, 0x1DB1840908569CACULL, 
            0x05520CB71388B78CULL, 0x617CEA9B54F2BA0EULL, 0x847E43AF72F7C728ULL, 0x4336062522F6845BULL, 
            0xC1430DE3D6F94B4BULL, 0x489CD9FD6D0BFA87ULL, 0x1E0CDDE00FCA87ECULL, 0x61823AF58BC1950AULL, 
            0xEE1DAC38A4716F30ULL, 0xDF840E74301B04B6ULL, 0x5BA0082AE97ED2C0ULL, 0xB7129C6A6450FE04ULL
        }
    },
    {
        {
            0xAC881E1412F3364CULL, 0xC2EFEE0A0D0D4F3BULL, 0xA165FFABC1E9489BULL, 0xFA0A93258AE0A789ULL, 
            0x5509C2E523D0AC5DULL, 0x5CC6CE38E0CCBA0FULL, 0xEF7586C6F5E8A169ULL, 0x35DFD4936EF8CE8DULL, 
            0x8AE2CA13ABF56621ULL, 0xDB725180ED2DB7D9ULL, 0x5C3C88730E66D930ULL, 0xF37FF6EB986641B7ULL, 
            0xF5E7FA48457BD4C4ULL, 0x4A644C6912D4660BULL, 0x973CD874F5F2E17CULL, 0x1C48C46EF62F423FULL, 
            0x937668AFDB17B7F8ULL, 0xB8551CDC82969B7BULL, 0x0D933EE1EAB21758ULL, 0x099FDB994770D260ULL, 
            0xF5F987E2F23EEEF1ULL, 0x68F276DFDB4E3B50ULL, 0x8C20327D71967927ULL, 0x484BAFAF6C2332B5ULL, 
            0xAA86B042C8B931BFULL, 0x5DA0AD724521E5CAULL, 0xCDC9B6EF0D9E8112ULL, 0xAC779D2655BC59C4ULL, 
            0x9AAB9658AAF4CB68ULL, 0x9ED84CF7843A2DF0ULL, 0x133067AA1D78B9AAULL, 0x8221158BEF472F51ULL
        },
        {
            0x8F51D59737F914BFULL, 0x6DB7C6B7C3A8F35DULL, 0x64B3AD5AF700FAFAULL, 0x1528E32248510A1AULL, 
            0xF92E1CA6AF9FCD72ULL, 0xB7AD68AE6D64C3F5ULL, 0x6691F67EFA0241BCULL, 0xA39A60F1DB6BC868ULL, 
            0xB07E1FB67AF8785BULL, 0x9D6A459988FFF989ULL, 0xDBFDDA64B8D34310ULL, 0xDDEC27981372912AULL, 
            0x976A70E709D6AF96ULL, 0xBD21F54A79E2AB01ULL, 0xB812F5F3F177A9E4ULL, 0xCF551A21334BA062ULL, 
            0x4417FEE575267E9AULL, 0x9DCD9F6E1F26AB54ULL, 0x93088655558ED697ULL, 0xBA8999A54C573C13ULL, 
            0xE26206F6EDC02029ULL, 0xE5E6F12913ECA425ULL, 0xFDCEA59EDEB9D46BULL, 0x3AC5B2A1257D0F13ULL, 
            0x697A862DC67A790AULL, 0x27C161066178C558ULL, 0xB5267FB2BD7F1CB1ULL, 0x08C413A4F3B4A939ULL, 
            0x12CEFF9B19565BF2ULL, 0x7E7076115808588EULL, 0x72299655DD94F2D1ULL, 0xFCCF737461C1A821ULL
        },
        {
            0x4AB82B68728A56ABULL, 0x597CE6A86ABA1B6EULL, 0x85D0153D6703069FULL, 0x8167FCEADF5CCF6AULL, 
            0x4BECA07160B2DB68ULL, 0x50B2EEFCBAC9EA36ULL, 0xE93338D1E2DCB2CEULL, 0xF14B01B83771BBD0ULL, 
            0xD5FBB3D3B5A5D6C1ULL, 0x3B537A2E6034AA9DULL, 0xF18BAAE6CCDD5179ULL, 0x7C84CD3FEBB3C5F6ULL, 
            0x9F323E70A8F251A1ULL, 0x5BED0B906C33CA28ULL, 0x458E48081A654CF4ULL, 0x757601B69B951DCCULL, 
            0xE8FEE445805389BFULL, 0xBA6057BDCC7D9DABULL, 0xE28708B88C56D784ULL, 0x76812758C955BD14ULL, 
            0x9201D84F985AFF84ULL, 0x4138AE61D41C75D7ULL, 0x3B3B3A350A49133FULL, 0x75D9AB5659EA34E9ULL, 
            0x4E8D67EEE49D1673ULL, 0xAAFB36F0CD04795DULL, 0xB64E4D75AE2A29FFULL, 0x61CEE138065C63F0ULL, 
            0x87FDE85B74ACB725ULL, 0x394B4481E2744944ULL, 0x2726944C9BDF2C2AULL, 0xE4F8203A839AE9BEULL
        },
        {
            0xAF3785D5942143D1ULL, 0x97BA0A9ACD8B9AE1ULL, 0xED5505AD9C82228DULL, 0x7D4032B8A281AF64ULL, 
            0x3286260223AC125DULL, 0x545C9513E3D10CCEULL, 0xC4D0073B3A16DAAFULL, 0x52E46519135CC155ULL, 
            0xC4603911C37CE743ULL, 0x6562D59C8997FBC9ULL, 0x95E9EB91C1665910ULL, 0x68ECE1B27C361905ULL, 
            0x9C2628658467A6B5ULL, 0xE2DEFB8F3A19DCFBULL, 0x1A9E68DE8E8A8717ULL, 0xC6951B8011B7D39DULL, 
            0x3CA22DA6430B4498ULL, 0xF7A43988A5402238ULL, 0xCA273F1D0B39B32AULL, 0x48E574438C018DE4ULL, 
            0x9D55724E71121B48ULL, 0xE8E5F2B2023788ECULL, 0xA1AE827BD6DC56B8ULL, 0x166BDBAC5BBFE3C3ULL, 
            0xE8E509F8E8BA7357ULL, 0x46AE95B95D6F32D0ULL, 0x30730F1BFB9324EEULL, 0x01A5FA09591387A8ULL, 
            0x9406949BD8395932ULL, 0x39AE297A0DBF9981ULL, 0x179B7C98DB0A2F6DULL, 0x5E892DC921D2B115ULL
        },
        {
            0x8787EE1A95C89F33ULL, 0x6349CC5DA58B28A4ULL, 0xBC7771E0411DFFBBULL, 0xE4F9CB860A9129BDULL, 
            0x4B5B5A0341AE0323ULL, 0x96FE274868BFD49FULL, 0xE29BFA4F1F4240A8ULL, 0xB92FC72FE10C6B5EULL, 
            0x6BFB07E92AD8522FULL, 0xF412E280625E6170ULL, 0xB5E6CE41CDDA391EULL, 0x4A2589E78DDB27CBULL, 
            0xFC80300CACFF24D3ULL, 0xCF8BAE558D4EDC8DULL, 0x8CD2E145DE4B6A09ULL, 0xF99E18C3C5AE822CULL, 
            0x78851A2F8C1CD7F4ULL, 0xC06C13A6271CB28BULL, 0xB944A17278B1BABDULL, 0xD678981296650ACCULL, 
            0x6B3592D879FE7D4EULL, 0xC1BA6D4E0E18D5CFULL, 0xEF977200173E20B0ULL, 0xDEC91D2B5B8A063BULL, 
            0x01D7231A1439694EULL, 0xC02D7E55B54D27F5ULL, 0x3E5D50344890DC5EULL, 0x63619B9802B18B38ULL, 
            0xBF706E80353D73D5ULL, 0x1FE46AE40E3AA5CFULL, 0x76015C622674AB39ULL, 0x1D38A9620FB58574ULL
        },
        {
            0xD4A468085ABCFE16ULL, 0x3C9F0C49E1C900B7ULL, 0x113D3A1F86CC72FCULL, 0xF4DA3A76B66AB24EULL, 
            0xEA6BCAD1057A2036ULL, 0x6D23F16CD48C068FULL, 0xBD319922A5EA8095ULL, 0x5F2888326A587551ULL, 
            0x2F6C96C4B4AF85A4ULL, 0x6A595BBC93B0AD0EULL, 0xA677782F80239EC1ULL, 0x913B853497BEA890ULL, 
            0x0BE44930039B917FULL, 0xA8F5C3EF1919773AULL, 0x0A4312D10E3C4810ULL, 0x41E821E25A96D7D5ULL, 
            0x415DC0ADB3C029EFULL, 0xEC2B0AA9250B15C7ULL, 0x048218E0EAE09F38ULL, 0xFF615C7AE43B61DDULL, 
            0x6456307A7E0C18ACULL, 0x5F8CC3CF5971E0E9ULL, 0xEF2096B157449610ULL, 0x0086BDEF3926E2D1ULL, 
            0xE42EE65144E04C09ULL, 0x375FE05787374487ULL, 0x8E3CD12C99DD1F84ULL, 0x5416B7A5174F125CULL, 
            0x76B1A26B473B5123ULL, 0x5DB98BF2FCFEB6A6ULL, 0x06DBCD2E066E6A19ULL, 0x1E515615614736E1ULL
        }
    },
    {
        {
            0xEA9D1ECB99156BF6ULL, 0x54FDBC70CD6E2036ULL, 0xE9A892B0F06FC79CULL, 0x2276F181C8692C15ULL, 
            0x419770F4BFEB9D14ULL, 0x2AEA3854C8926BF3ULL, 0x4F8C654F198B9A8EULL, 0xCF002E88733D991EULL, 
            0xC6C34D7A3432CA62ULL, 0x1CA1B2F2FC770548ULL, 0x7BE72ADF2251E9DFULL, 0xC04CF6495BCF924CULL, 
            0xD466B5AB11F0AC76ULL, 0x9F3214AA4E9EA651ULL, 0xBCC1650836F90F42ULL, 0xC9089503DB4FEC97ULL, 
            0x9C096C51B54C4059ULL, 0xC953A7B9B5B4706DULL, 0x7DC4ABAC45B6945EULL, 0xD58491CAE06C3E4EULL, 
            0x80A7961D275EBBF7ULL, 0xA15A4311E5B272BCULL, 0x11BA1D24A6EC049EULL, 0x4323B2E0E1EE1827ULL, 
            0xCA736D7E77030DF7ULL, 0x101344D092AD2B0CULL, 0x43DBD95528190037ULL, 0x831837EE5A40CBB2ULL, 
            0x9226116A4D0A59B1ULL, 0x14259B82AD852429ULL, 0xD066905945C77669ULL, 0x0C2C373162646F37ULL
        },
        {
            0x0D423CC99F23BA00ULL, 0x1DE2F7FC1EDA37B5ULL, 0x0E27EF62612D4886ULL, 0xE216DCDF365CA6B1ULL, 
            0xC4B486FA642789DAULL, 0x4DA5D61EED7AAB80ULL, 0xBEC011CE155BB377ULL, 0xB6F6C4BC9B373169ULL, 
            0x6D197D79F85C09AFULL, 0x27885CCAF291107FULL, 0xD5A71CED2859C0E5ULL, 0x718068946B85E723ULL, 
            0x939D71945542C0C3ULL, 0xDA9F9167DEA5CFF3ULL, 0xA99FCC40101A8F9BULL, 0xF0AA9F56735243B8ULL, 
            0x97348B3D91B7B0D9ULL, 0x160008D8176E2EF9ULL, 0x7BA26DFA0F14150BULL, 0xE74C0A5C10915AABULL, 
            0xBF945FF7FDB26C58ULL, 0xA7A178C6213F70A9ULL, 0x41B05517FC81ADC7ULL, 0xAE29B68E8A3F745FULL, 
            0x2E78BCC90924C9FFULL, 0x3373E08F048C0A5BULL, 0x324F77638BA3915DULL, 0x2C64DEB03BDEEF86ULL, 
            0xC1A5F9039CD03882ULL, 0x92A31CD130335067ULL, 0xC46978AD235CE35AULL, 0xDA80DB3F53339661ULL
        },
        {
            0x06C1055CC88F9011ULL, 0xA837569F0911059AULL, 0x03B0305D2DF89DB0ULL, 0x8BE8FE99A52B5E47ULL, 
            0x50B52B467CA358B8ULL, 0x6F8D4DF952819B2FULL, 0x8DE3ACE70BCF0474ULL, 0xC757B11978344B4FULL, 
            0x8BFC7A0A06870E41ULL, 0x32B46FEBD5818DDFULL, 0x6B29410E93DC12CFULL, 0xB561A86CF1481E8EULL, 
            0x6F7C80A24F54F1A3ULL, 0xDB3E53ED2F947420ULL, 0x8000DBEDE11C7182ULL, 0x8592AD122114C0C2ULL, 
            0x99288FAA4E475C62ULL, 0x61656223155682BBULL, 0xA69FB1A10974253CULL, 0x2E2F6CE8C1F7824AULL, 
            0x65D736B41CC14AEAULL, 0x91C5FBE3C6CAA2C0ULL, 0x3AA8FABF915D7844ULL, 0x777EB432ED4337CFULL, 
            0x83C52D9FBE1F2A74ULL, 0xE308787C56B7F5C5ULL, 0x562F86F908CBD7C7ULL, 0x8B9B0DFA267659B9ULL, 
            0x87FF025C5AFC715CULL, 0x9735269C68C0394AULL, 0x3DD1C4CAE522EB87ULL, 0xD7202F4867D1F67CULL
        },
        {
            0xC2376212807EAD24ULL, 0xBD73637820E1A318ULL, 0xB097D7D19F65B011ULL, 0x2192439084845C84ULL, 
            0x74BC0C7ADD54321DULL, 0x1066BA8F560014FFULL, 0x94CE6237537EC2AFULL, 0x408D576E65ED45CDULL, 
            0x05D18CA79DF34521ULL, 0xDBD120F8BE10E1E6ULL, 0xFB967B621A269411ULL, 0xD864DC5B495A023CULL, 
            0xEC5156048C1E1DCAULL, 0xC3BAEA036474EE55ULL, 0xA4EFA1637A952467ULL, 0xAF71DA017A697AD9ULL, 
            0x1CFDF78582E182D1ULL, 0x75C5CD0DE0B4BD4DULL, 0x5DE7D796202D805EULL, 0xAD170EA6E10F1CDBULL, 
            0xB8B75359654B46B1ULL, 0x46E01FC35B4B31AFULL, 0x2204B2A79CACD99AULL, 0x20D703B0A5A3572AULL, 
            0x89963E598F8E8422ULL, 0xDD38E5804C39A771ULL, 0x8798CE8C9AA86765ULL, 0x2282E7D2221C6505ULL, 
            0x73547AD6F852A1B9ULL, 0xF1B90E046A2DA1C5ULL, 0xDF59ED84DD95F067ULL, 0x9B1D0042088A6077ULL
        },
        {
            0xDDE33815C40B12C1ULL, 0xD8CA3581DBD02DA7ULL, 0xF3C47481551F7901ULL, 0x208B914F0F74E34CULL, 
            0xB642E0B597CD9BDAULL, 0x6BF4F85BF3EE7E9EULL, 0x8003EFBC9DE87569ULL, 0x59E6E7FB40D71EEBULL, 
            0x6FA1FF82DDC43430ULL, 0xCB0F52A6CCC77D15ULL, 0xB7551F040D15EBA7ULL, 0xAE934CC0FC82DFF8ULL, 
            0x7994166B8B1E92D9ULL, 0x6B17BA20C7778733ULL, 0x922B1FCBC17334D2ULL, 0x6C3E97B7AA31FCAEULL, 
            0xD9B6A437CC9C5CA3ULL, 0x582E626A668FB865ULL, 0x9C9EE2FDB764AA10ULL, 0x7D9D767DD5420ADDULL, 
            0x2A3745B27AC097D1ULL, 0xC9BF552580981517ULL, 0x6AEAFB9A66AFAF1AULL, 0x191DA3A3A860F8F7ULL, 
            0x6085120AF7107662ULL, 0xD0D0A90BB4AA725DULL, 0xDB5B39FA386B6BC9ULL, 0x5A528B0458A16688ULL, 
            0xEA4D4A1CDD7EBC60ULL, 0x7A364A0679B5B15FULL, 0x0DADB73BAA04A1ABULL, 0x694EEC1FFEA77751ULL
        },
        {
            0x2AF08F82816B9CEDULL, 0x91ECF771E026759CULL, 0xC38CEAAB84CF1A01ULL, 0x3AC79512B5719E63ULL, 
            0x96D51B3CFF2F5148ULL, 0x93E6004D1F4C55E6ULL, 0xA25DADE2ED536ECAULL, 0x72BD1DFE1582D4D4ULL, 
            0x07FCE9B78099FC59ULL, 0x8748A17BD57D7888ULL, 0x72F4840134E45AFFULL, 0x966AE878E7B67B21ULL, 
            0x1384CD1F59976873ULL, 0xDC482070902152D2ULL, 0x9961CB4634E58879ULL, 0x9290FF56E2CD1C45ULL, 
            0xC7CCE1E817146051ULL, 0xDF1EF1F288974482ULL, 0xDE6063364E3996ADULL, 0xBDCE8D789D6375FDULL, 
            0x7E92EC590541B36DULL, 0xBBC286515CDB5BCCULL, 0xBD71DE261F38E282ULL, 0x5AA942A8A96BE6E2ULL, 
            0xB019EB3FDA546DDCULL, 0xFD3AE657784F482CULL, 0xDB0A383EE8FC6FEDULL, 0xE491405712809C82ULL, 
            0x0B7CEBBF4BAE2169ULL, 0x93E9740D08DB5AEEULL, 0xEA9E0DFB4C264296ULL, 0x6EE35F559AD6E1A5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseDConstants = {
    0x4E751EC2E00675DDULL,
    0x75CCCFDDD747A3DCULL,
    0xBF0DC945A691FA11ULL,
    0x4E751EC2E00675DDULL,
    0x75CCCFDDD747A3DCULL,
    0xBF0DC945A691FA11ULL,
    0x7D4B86A7AC39EA4CULL,
    0x0CB95BB21448B09EULL,
    0x15,
    0x3B,
    0x1A,
    0x69,
    0xA2,
    0xDA,
    0x84,
    0xD3
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseESalts = {
    {
        {
            0x121EBA968D83E4DDULL, 0x64F379AC4A3E7820ULL, 0xD4AD5DD69549B2EDULL, 0x8B201BFF9AF1D074ULL, 
            0xB13635CE245EDFAFULL, 0x7A7543644ADEC732ULL, 0x3DDAA15D61E0B43CULL, 0xA14B05CBCC09C4ACULL, 
            0xCC5DCAB0457E0865ULL, 0x01BDCA1B65BE5755ULL, 0x8978D4A2B8390204ULL, 0x65A7CF99D2988757ULL, 
            0x678E1763577C921FULL, 0xA26C13E6A72D0062ULL, 0x14F00D2684CA633BULL, 0xBAF8E373962DD4C3ULL, 
            0x0209FC39ACDC4542ULL, 0x98D68E1017FD029DULL, 0x304E02459325423CULL, 0x20634D309327337AULL, 
            0xEB7D3806E4AA1413ULL, 0x44BEFB529F0A1ECBULL, 0x4B96EC35CC8303DFULL, 0xBBE61D7DD1B9F0B7ULL, 
            0x65A5644F4E408CB9ULL, 0x7852FBCA5B55944AULL, 0x2C3D13FD7F122385ULL, 0xE567C692C9EE76D8ULL, 
            0x044FA011F246B033ULL, 0x1B93470A7485B2BBULL, 0x5AA12AB9BC2E4261ULL, 0xDA62712C59A367BBULL
        },
        {
            0x32E5D02EFA318F8FULL, 0x1F34601451BFAEB7ULL, 0x2909680D2B91C8FFULL, 0x26A036042B6A96F2ULL, 
            0xC0EA1AB266855EEDULL, 0xAB38373AD1341B0FULL, 0xAEB1706FC2FCB7E3ULL, 0xAAE2899952E025E8ULL, 
            0x7D8D24BBABD8E6C1ULL, 0x5E18496D2975A6E0ULL, 0xA215D6043FAF811AULL, 0xC913D6A362360BEAULL, 
            0x6208B9BA8214973EULL, 0xAA862551F4FB12D2ULL, 0x6CB1086242AACE8CULL, 0xC7B1D3E37C2E13EBULL, 
            0x25BC6F6D8716D9CDULL, 0x3FBDFFA3E48165B7ULL, 0xE414E7CA31D02986ULL, 0x54B7087D5340EB8DULL, 
            0x629D6AE409997DB8ULL, 0xDA5B7DD7D63B0B6AULL, 0xF8F37AC1CADE3CD2ULL, 0xF12A5315702E8C45ULL, 
            0x095D71A2B619AFD4ULL, 0xA6B710090E46340FULL, 0x6860806E8DC99EC9ULL, 0xE91B82BE08BAC1C7ULL, 
            0xD84E7D543C93B580ULL, 0x1A4ABCB677F981F3ULL, 0x558801141481166BULL, 0xC74E1089EF6BE403ULL
        },
        {
            0x408EA6FF541E4155ULL, 0x23A0552AA757F6D3ULL, 0xCFB4D9D0F128AEF1ULL, 0x2C1880F00236294EULL, 
            0x5E81EA850B773CC1ULL, 0xD847B85A09EA06E8ULL, 0x632359D7BCA60AC9ULL, 0x515DF83586F89DA9ULL, 
            0x259B3DE02DB878E6ULL, 0x4542A278F3D88F76ULL, 0xC4D68164D7E79A6EULL, 0x530C880A26A74D9AULL, 
            0x8875FEFA0AC57018ULL, 0x2461BF1ACF0C7ED1ULL, 0xFB88B2925DBBF5F3ULL, 0x340EEF064CA99E7AULL, 
            0x9FFC877EDB42A5F4ULL, 0xF6EFEE39472D47D7ULL, 0x0DC9272BF4205550ULL, 0xEFEC46CAB3DB48A0ULL, 
            0x49C23BAFBB1B47F7ULL, 0x730EAAAD56189BEFULL, 0x1920F21F890E4B6CULL, 0xFBA052D21A118AAFULL, 
            0x5ADEFAA913F3CD3BULL, 0xFD3E60A0717FF112ULL, 0xF106DBF74DD88461ULL, 0x23E6BA641B691FE6ULL, 
            0xC161DE970A643474ULL, 0x31CF04378CF2647DULL, 0x39E2EFC2A8C34CA5ULL, 0xEB5BA1C2D9E61D59ULL
        },
        {
            0xCA51F73CF8876293ULL, 0x130B44A7D2521DE0ULL, 0x2A50FA84C8146F4DULL, 0xDC42E2830EA96E2EULL, 
            0x599D36DD171E39DDULL, 0x7417E168EED5E1DDULL, 0xD5EEBD5DF9CE8D51ULL, 0xEC6265BFEBCBA280ULL, 
            0xA5623C5D74F2231BULL, 0x25315C318DCBA061ULL, 0xB7DFEF5F2C5384FEULL, 0xA7E16D1011854878ULL, 
            0x8288182F75CC0865ULL, 0x67F7DBA1255F5B59ULL, 0xE2564A75F044C09BULL, 0xBA1ED572DBC224B5ULL, 
            0xB9CF422FFF38F73AULL, 0x0AB2FEC8F2719758ULL, 0xA3660A37C65969F6ULL, 0x51BB3B4222CC1248ULL, 
            0x0A90EAB3A42868A7ULL, 0x3900905D4829BD74ULL, 0x05606252E1A0648BULL, 0x3B556FAF287FFC82ULL, 
            0xFFE0A5C22A152173ULL, 0xF52DF46AFF511DA8ULL, 0xA4A04CB92DE6948FULL, 0x0CC39B4EC3D193A7ULL, 
            0x26A437F22BE13883ULL, 0xBD27BE933A49F1BFULL, 0xE72160A08BE1804EULL, 0xA0DA486B184D5866ULL
        },
        {
            0x9D91C38AD3311138ULL, 0x20DBE54180351BACULL, 0x20C92B4AED9C19C7ULL, 0x13BF4EEAA991C467ULL, 
            0x12CDC070CFE28C01ULL, 0x382F95017032F90AULL, 0x2532494F52B523E7ULL, 0x37B11006B8EC6C20ULL, 
            0x7ED5C1BD35393B47ULL, 0xA129F852AFF119DAULL, 0x5F15B8184960AC9FULL, 0xB4A1C24A73128E6FULL, 
            0xC7130E15C192E5D3ULL, 0xA1A1EF0578C737D7ULL, 0x741BF15F427B88B8ULL, 0x31FE4BF8042BEEB6ULL, 
            0x8991600F32646D4FULL, 0x0F9A46DDEAABBA14ULL, 0x4492CBDF016F1A72ULL, 0xDB93FBE97522222DULL, 
            0x950CD019367FE77EULL, 0x8A82F21F8C02F971ULL, 0xC3F6E5739BC92B88ULL, 0x084783A30A001022ULL, 
            0x8674AF4BDBE97A77ULL, 0x2E373B79D66ED46EULL, 0x8C88C85D34DC58CDULL, 0x8546A55AD3B5F859ULL, 
            0x0F959358A7228660ULL, 0x8C43BDD0A571B163ULL, 0x1F48A7478D005763ULL, 0x99A10D9AF7B2CE48ULL
        },
        {
            0x878B165016377B29ULL, 0xA6FE20523C1B1B11ULL, 0x7083F2FC2FFE0679ULL, 0x6AAF5D788B8266FBULL, 
            0x93CF0DC2ACDB055DULL, 0x29FD64E48C53761AULL, 0xCA59C467728D5636ULL, 0x0E86B668DD64D824ULL, 
            0xA501663AFD4AF411ULL, 0xF3BEE3153C149FEFULL, 0x894373BFDEEFC83CULL, 0xD1B186FF10086F35ULL, 
            0x8D24FB459C4B53F6ULL, 0x8D283B20C2B0FF43ULL, 0x75B791AA19E6F7B1ULL, 0x6E0736EE0DADCFA1ULL, 
            0xEA17D416BC62E9D1ULL, 0xFBA5ED2AD57AA622ULL, 0xCE0C9488DAC40084ULL, 0x3ACA911BCEE26503ULL, 
            0x441730688B01BACBULL, 0xC76E1C5FCA2D8BFCULL, 0x744CEE25B45B4860ULL, 0x359F03EEE515C5BAULL, 
            0x7D77F1D746329FECULL, 0x27D18408FCC446FFULL, 0xBB4AA30A6FAA3443ULL, 0x97AD6E1C578439E4ULL, 
            0x486D23D98360FBE9ULL, 0x96991E4E832E4FA1ULL, 0xDE18D63B6656ACAEULL, 0x713889D504834A65ULL
        }
    },
    {
        {
            0xE18D7E83D003BF11ULL, 0xB8581697520CA0E7ULL, 0x6088219CA2DCD5BDULL, 0xE754FD1CA9C8B4B2ULL, 
            0x9FD2FEC01D6581F4ULL, 0x847E5998B5D85368ULL, 0xC587DC2EB03FAE87ULL, 0x4FBA091BA071CD65ULL, 
            0x650194FC8599C64BULL, 0xB314FBFDFFC0B749ULL, 0x7EB6173EDDE2D9FCULL, 0x1014937FD32C9A4AULL, 
            0x9DF4BD49F69322C6ULL, 0x3A5C92EB4AF37E3BULL, 0x54223A64987CA0DAULL, 0x8604DB64A46E2DC4ULL, 
            0x3B12CD006B1BB88CULL, 0xF94A7068D0BAEDF9ULL, 0x5F4350CF2AE41BD5ULL, 0xCCF190F1C9BF7C3DULL, 
            0x15BC94FFD93203D9ULL, 0x565F3B0D09AD5DF2ULL, 0xC1BC1901DD6E8E24ULL, 0xF23CD0CF2829596BULL, 
            0xF669C74022E6BC32ULL, 0xEA604D05425E9ADCULL, 0x9C4F79A553FDE703ULL, 0xBB035B0752728638ULL, 
            0xAA081B93E2229C9BULL, 0x14A056BDC055AAC7ULL, 0xA2BB7732D34925B3ULL, 0xF2FCBD66D49698BAULL
        },
        {
            0x772AFAFBEAD997C1ULL, 0x4FAFB22676C594A5ULL, 0xA1410473CB86EF21ULL, 0xB84CA23838173C45ULL, 
            0x19C509C2C3808567ULL, 0x6E650F43BBF0111AULL, 0x656B87B95CACB4D0ULL, 0x3DD790E87657575AULL, 
            0x14629108B2A4D54AULL, 0xACDC252EA8B4ACF7ULL, 0xD7693A05BC2FC7E8ULL, 0x39743500688D45DFULL, 
            0xD6626854077845D1ULL, 0xCF70F6F38A88B20BULL, 0x45D2106B66915CBAULL, 0x2C5BBD60406A43FEULL, 
            0xF4436AA1F197990DULL, 0x3A4A4BA77BC1CE84ULL, 0x34217F8D0EA744CFULL, 0x5CD88F882125DB52ULL, 
            0x9F43E351266097C4ULL, 0x5CAC75CA6D32C6F5ULL, 0xFE4FE2E377DF1BB6ULL, 0x9EE7EF4353C4620CULL, 
            0x4EB3C5071920207EULL, 0x67FF82C1CA8542FBULL, 0x9A709F54EE3253B8ULL, 0xA368073AF99812B0ULL, 
            0x0646971FEEEC0C64ULL, 0x5C9DBBAC7A91351CULL, 0xC57DD002DC39C1A5ULL, 0x3E5489DC0945F3FEULL
        },
        {
            0x9318FABA49DFF37AULL, 0x6ED316E5DC0009BFULL, 0xDB5366FCA802337DULL, 0x200A4D4D3F98A04EULL, 
            0x4B2159B227231078ULL, 0x9743C3C28DBB3B81ULL, 0xD6A57A2A5B6D7265ULL, 0xA7DEEF850A2DFAB5ULL, 
            0x3D13C5CB6B70D2CDULL, 0x98DE804A07738528ULL, 0xF3670D7FBD3502ADULL, 0xE1FDDF0E6D29C0D0ULL, 
            0x8AC43EF3000CEFE3ULL, 0x4B1F9B9976B41EE0ULL, 0x341BA75247C7D15AULL, 0xFB7DBCFD1207A133ULL, 
            0xB9EF8F78E266E131ULL, 0x6AB0DCA40D163183ULL, 0x9E639A7EFC733BBEULL, 0xB42495BCE7CD28AEULL, 
            0xDB1649FC1A8908A2ULL, 0x9CD9A65AC3B78963ULL, 0x39244E0389BAB8EAULL, 0x0ABC3E7760C361E3ULL, 
            0x57CC5CBCE13E4D3FULL, 0xBE89D18DC8A044E8ULL, 0x136317E5EB0519B7ULL, 0x08226EFEDEEB643EULL, 
            0xB25A633D3DB371C7ULL, 0x7F5A70C333799FA7ULL, 0xFDB40BD44DA9BD30ULL, 0x602EC83D76FBFCFFULL
        },
        {
            0x7112FFF3876260B0ULL, 0xC1CA303C99ACB4BFULL, 0x1DBFE60F10B2D0F2ULL, 0x69E8670F2C5C94E3ULL, 
            0x8951B3BCF56B671CULL, 0xA316AE583A624A1DULL, 0xBE3571D8E15E3483ULL, 0x7052B6CAEBC4C3BAULL, 
            0x29E130B8A7224C6DULL, 0xFFCBA4D2631A6B77ULL, 0xE1BD9A8F0F04EBDCULL, 0x57BB9F97E443801DULL, 
            0xB57B93A3854BD31EULL, 0x9BCBB43DA85159D4ULL, 0xFD3A924DBC9079A5ULL, 0x558326388F66DCF1ULL, 
            0x3D40B04AAD76BF46ULL, 0x96FA61F216F788CCULL, 0xE9128CAF5399DF13ULL, 0x7CD9E32495580C60ULL, 
            0xFF1FD64AC494D39EULL, 0x4E5096F2CA1A1DFAULL, 0x0C448E91B2C08177ULL, 0xCE1EAA486150652CULL, 
            0x2D285072D2F49F7FULL, 0x39440809C464E175ULL, 0xE2D1FC39E39860E1ULL, 0x7B065998CD6B5257ULL, 
            0x9F2110DF3AD70948ULL, 0xDF2803192DDD5174ULL, 0x8658F7AEA8913163ULL, 0x85CFCEDE8870821AULL
        },
        {
            0x22C2DB0D9ECE0716ULL, 0x4A296F934807FAE0ULL, 0xE83D499190EAAB2DULL, 0x11536FB66D87BBDAULL, 
            0x0B282123B314B4D9ULL, 0x7D00894B184E9952ULL, 0xC33D47693400E85EULL, 0x8B733BB2F65776A8ULL, 
            0xB079266598B5A7E1ULL, 0xD6714B5875487D6EULL, 0x3560A0D4B0BFD43BULL, 0x40242B2444FA16A5ULL, 
            0x2A5E2130DA2B8C82ULL, 0xE4C585BCCEA1778CULL, 0xE3879E54C83082DDULL, 0xA08D70430927AC0FULL, 
            0x740B063608788995ULL, 0x696141C0D2E350A5ULL, 0x04B72BD8B6995F88ULL, 0x898FCFB8CDC30CEBULL, 
            0x4E75D405722055A7ULL, 0x882FA02549677659ULL, 0x0768DE9D283AF3E7ULL, 0x671AE1D6260A1EFDULL, 
            0xCBD05A198345997CULL, 0xE8AA33DBBBF71683ULL, 0xE4A1E8186F489100ULL, 0xFCB9DE4AEC5209F2ULL, 
            0x50F2DD0470ECB9FDULL, 0xF6DC21C0480DB119ULL, 0x127979D5535B7400ULL, 0xA2C710798D42B130ULL
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
        }
    },
    {
        {
            0x49F88DD535CFC13FULL, 0x4C4AB4EE65A191AAULL, 0x2F962DF91ACE07ACULL, 0xAD6A3A7A2AA41673ULL, 
            0x73B116C8DAF7AD4FULL, 0x81A5FB65E0792BDEULL, 0x6699BC8F5C9141CEULL, 0xEA004BF2C60014CFULL, 
            0xF1E58C198FBCC412ULL, 0x6828DA3865EF6602ULL, 0x9EABAFE1A355C999ULL, 0x76D90F2A150943D4ULL, 
            0x2F91FF53DCEB3F26ULL, 0xD4DCCD519FE938B6ULL, 0xC274BCB7F1724317ULL, 0x1916DAA7634B8595ULL, 
            0x90939E51816A6117ULL, 0x7C878736C160B7E4ULL, 0xA6293FFCE391FB60ULL, 0xFC7B8E457665F570ULL, 
            0x2FF7E1F62E9EC11EULL, 0xA7C2440DC4325B1AULL, 0xF40EEE4EE8CED0A7ULL, 0x5790FA3C3AF2D157ULL, 
            0xE4DFFB81E4DE02E4ULL, 0x0BD90DF34F910214ULL, 0x0A0508387E1F1610ULL, 0x51CA98F2EAF78A05ULL, 
            0x5FACEA7AE2DA52AFULL, 0x3B6FD37689914C4EULL, 0x2CA0B6F59A44B8BBULL, 0x2A1321ACB2D59C95ULL
        },
        {
            0xC63F789FBD555BDAULL, 0xBADAA5033F723B6AULL, 0x7BA77EB99D1752EDULL, 0xA11D80E1E6DA3F16ULL, 
            0xEFB7E1BE30C30F36ULL, 0xDDFBEA9D89280A3DULL, 0x32E3D46E0DF19A58ULL, 0x07DED5B537EA2803ULL, 
            0xA4ACFEDB6A9A4100ULL, 0xF362F0FDCFD0F9A1ULL, 0x44E213C76C7E9B88ULL, 0x00C5E0C01384497FULL, 
            0x57608B838E4BACDCULL, 0x7F6A4D794BCD3046ULL, 0x2B710C412E9B23E1ULL, 0xA1FD7E494E1D3D14ULL, 
            0x0015A25D3E0264FEULL, 0x4E3446DC56DEEB5AULL, 0x0B72BAAEE80FF046ULL, 0xC66E9C1EFD11EA9DULL, 
            0xC6B9EEF81DB4D732ULL, 0x7D5173EBC76B4D50ULL, 0xE4C335776B83614FULL, 0xDC1D851FAB0F74ADULL, 
            0x960FE87E4EABF939ULL, 0xFD0E6715843F7501ULL, 0xC6136B4B132DDFAEULL, 0xBC01E9FCBCFDF917ULL, 
            0xD4A942DD8669A14EULL, 0x40D4645044FBAC9FULL, 0x5EDC16DF21B394C6ULL, 0xEBD8445668FFADE5ULL
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
        },
        {
            0x358EF4D666DD4273ULL, 0xE1CF82D02DACAC38ULL, 0xE1F56F8C30520D48ULL, 0x576C17ECECFD5A63ULL, 
            0x3D4B02AB1AB05587ULL, 0xBE0FC77ABFD0DD40ULL, 0x2C9043AFC8FB3C67ULL, 0xBC2A58C28125FB66ULL, 
            0x8DCE31242C027EE7ULL, 0x6407805A57B13AB5ULL, 0xC72ED8867B672448ULL, 0x9BA6BB0084C67C14ULL, 
            0x521244F99A6EF492ULL, 0xB106250A738514D4ULL, 0xCF3C47DDCDE03F1DULL, 0xCDD5E9E7979D61A0ULL, 
            0xD9EA007F37432325ULL, 0x31FA706C6D5210B7ULL, 0xC2EB6C5F0BFB08A2ULL, 0x8C6A073C429EB448ULL, 
            0x69AF97136F5E3055ULL, 0x719CD6FB676C224EULL, 0x67BC56E3FC55EA9DULL, 0x756C5329F646B1E3ULL, 
            0x5765F73ED4DD7343ULL, 0x7B7AC680E25F341FULL, 0x63FEFD03074D9F89ULL, 0x85B7D89F0910A3CEULL, 
            0x2634E3C7C0233268ULL, 0x6E579D18E5721FC9ULL, 0x06E08CAC3634595DULL, 0x481CC425C8C5723CULL
        },
        {
            0x79983A848D306131ULL, 0x909D2D95245314DEULL, 0x0796AA6670AC722EULL, 0x802795D77BD0F84FULL, 
            0xFBA1E87AA55BD906ULL, 0x172C077136A73BCFULL, 0x73263195E29625D5ULL, 0xE35508B5C033794FULL, 
            0x647031199DE8DE14ULL, 0x3430B23E2B4FE50EULL, 0x7320655941643F28ULL, 0x1ABADB4FE25686CCULL, 
            0x17C516E7B3D9D5FCULL, 0x8A074C587B320A22ULL, 0x43B4491006644866ULL, 0x2E39EB819B2C77F2ULL, 
            0x5F9203FC28A8AC0BULL, 0x913F9AC05A7FF855ULL, 0x7B6B513B26157E5AULL, 0x0EB709D07D9EB89FULL, 
            0x96DB8D8C3F0E665BULL, 0x65DCC281B52C238BULL, 0xBEBFE7C34B2D5205ULL, 0x77FC27B1EE8E428DULL, 
            0xE34CEEE3B02EA896ULL, 0xED0AB5353F6BDF52ULL, 0x58E7117512D6A609ULL, 0xEDADB0466D428028ULL, 
            0x96A22FFBD40CCC45ULL, 0x2EE4EEA30EE2B8C3ULL, 0x28CBA83C2E81CCACULL, 0x84D75C4882F69AB4ULL
        },
        {
            0xD5A23663E2C895D3ULL, 0x6493BF47A6BC49EFULL, 0x4180C2CDDFE6F675ULL, 0x42CA3A34E35A56F9ULL, 
            0x421D12DFC50F70D7ULL, 0x5F80716315092F92ULL, 0x531A93EDBDFF0C14ULL, 0xB71F77C5DCA3A605ULL, 
            0x29676061DDC241EDULL, 0xEB3EA57E752C6D1EULL, 0x576652C5517EC646ULL, 0xF142E417D6B27A30ULL, 
            0x99B4C9F24D0C306AULL, 0x8CE0D277075719C5ULL, 0x1FA8FB3A1A58353CULL, 0xDD9E7E7DBA97898BULL, 
            0xEFBECA545F725D93ULL, 0xA177029323B89DABULL, 0x8CA79A2C482AEF50ULL, 0xFBFA52D929AF50C1ULL, 
            0xD884F670185EA59EULL, 0xB3C76E466D4B5A4FULL, 0xED0E6C058838F72BULL, 0x4B18F2FB6F119134ULL, 
            0x3B748E8BA370EE9EULL, 0x1AC24B9A036A31E2ULL, 0xD7C99502CA8AB10FULL, 0xB18B000150B402F2ULL, 
            0xA0DA4B2A09AD68B4ULL, 0x16DF96A44CC53C34ULL, 0xA8EAA938E63DF632ULL, 0x5AC21A354267E77EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseEConstants = {
    0xDB21D761502E15E2ULL,
    0xF473DC3AADA188CDULL,
    0xFB3E45EACA633CFDULL,
    0xDB21D761502E15E2ULL,
    0xF473DC3AADA188CDULL,
    0xFB3E45EACA633CFDULL,
    0x1E0D33F076A3F42AULL,
    0x5896DF4BCE9950B7ULL,
    0xE1,
    0xD2,
    0x2F,
    0xF5,
    0x62,
    0x27,
    0xEB,
    0xED
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseFSalts = {
    {
        {
            0x2D92CAFFD179D402ULL, 0x0C44535998027630ULL, 0x3B34F4489219C602ULL, 0xB59DD763EB4DE51EULL, 
            0x6EC7FA02BD4CD3C3ULL, 0xAA74C25D5A025464ULL, 0xEBF2A68A80790567ULL, 0xD245BAD59354CF63ULL, 
            0xF2C83BF139810312ULL, 0x4F81A86203C6FDD6ULL, 0xF8D88E75576F8C45ULL, 0xA32D452266ADDEC6ULL, 
            0x9D405068B33981DFULL, 0xA92830B355AF3741ULL, 0x33B073316C04ABBFULL, 0x3B17B165982532DBULL, 
            0xF17828AF10FD4C41ULL, 0x4DA653838DE99188ULL, 0x996F59472ED6301DULL, 0x68037DC7FD459059ULL, 
            0xB1FACACD220B999CULL, 0x3168A5B8B55CE1B0ULL, 0xBC527B4BA95205CFULL, 0xCF1B341221947BF8ULL, 
            0x723E858D87D03265ULL, 0x4C3CF6B6B4D123B1ULL, 0x4AB469E448067554ULL, 0x6E27C5BB875207ADULL, 
            0xAF618A34EC257D76ULL, 0xA0A56BB561944226ULL, 0x36A59A22CE240FD0ULL, 0x9285852FA8AC69FAULL
        },
        {
            0x13DF455BC335DE4BULL, 0xA7D817403E0982EBULL, 0x334CE88A17016DB2ULL, 0x009CF6CAAD4F9129ULL, 
            0x48FDE31FBD4AFCE8ULL, 0x100761530A147F47ULL, 0x1A9BFD1FD4D32AC4ULL, 0x002D9DA88F55D202ULL, 
            0x1F6FA4375797F9DDULL, 0x7D4E378789953287ULL, 0x6951B82916C79496ULL, 0x3F37527D5AC2CFF7ULL, 
            0x9AB2CA40B4A48B85ULL, 0x816EA6D8478B6DE7ULL, 0xE91F1F68DC8714ADULL, 0x43C08604AA51EC2AULL, 
            0xA61046DBE63E12D7ULL, 0x009F7B6E51C453E1ULL, 0x6A4CBADD48D99E5AULL, 0x83A90129FBB9279BULL, 
            0x4F33D023F4A1BFC4ULL, 0xCA4F94A09FA5D51EULL, 0x98498A98DB96EB37ULL, 0x7718FB6279BCD257ULL, 
            0x8295986C2E3F68C1ULL, 0x2E59C836667C1C05ULL, 0x84AD22F1E826912FULL, 0x267A44EA9FF43DC3ULL, 
            0x773343ACF40AD63DULL, 0x57C51CA3FAC147E8ULL, 0x1E14A24E254505C7ULL, 0x2D4C7AC623680606ULL
        },
        {
            0xAF53D500AC8F4B3DULL, 0x356892F0678370C5ULL, 0x6F4A03012790FFCCULL, 0x0434CA0D6DDB46F6ULL, 
            0x33090E37991AF6BCULL, 0x30FA79501381D13AULL, 0x4B9D490A994DFADDULL, 0xF4DC1C6DB4841F15ULL, 
            0x72FC178FF35E04D2ULL, 0x8689F9DA45936839ULL, 0xDAC70A76A49816C6ULL, 0x2F11D8DFD37AC246ULL, 
            0x692840A3613306F1ULL, 0x526BD18672EDEC19ULL, 0x741804F546630795ULL, 0xC158B20774EA99F8ULL, 
            0xA8CB0BF1CC6AAA92ULL, 0x5A52F4C2C6F67BDBULL, 0x0E8B42295E302A61ULL, 0xE1A9DE0117B798A5ULL, 
            0x224A48D71E751F9EULL, 0x271B329C1819D2CFULL, 0x8982C607B2A61D5CULL, 0xF8B1F10834B3076FULL, 
            0xFDD1939E66D1F919ULL, 0x0587DF7821F2762DULL, 0x9DDACB2E576AAB50ULL, 0xE4CF4A17D994A46EULL, 
            0xF2005010074A843FULL, 0x201EC8DAEF203736ULL, 0x9E65C5D99D652E6BULL, 0x44C4BA5393631A0AULL
        },
        {
            0xCB70A7F2ACB396ABULL, 0x33AB36AFD18C4D56ULL, 0xC1CB19F1FD188BA6ULL, 0x94756467862D256FULL, 
            0x24FF3A40E82C9B97ULL, 0x9F05E32086D84D3AULL, 0x60C4E761C62798E4ULL, 0xCEF6D862D30FB104ULL, 
            0x9DAFDA6CE45A7DDBULL, 0x9DBC58B1E8B0E31FULL, 0x634C2122D0E7F694ULL, 0x1B44CD8B4422D2DFULL, 
            0xC69851AEB2009C0CULL, 0x31B03E7F4E420F59ULL, 0x2FB1ECAE50469F9CULL, 0xF211468D6DFE5442ULL, 
            0x0F6C4116220978ACULL, 0xB5E01E0F3031579FULL, 0x68A829B3099D49D4ULL, 0x4B3B7509F5EA1903ULL, 
            0xAA16EDE486D6DA21ULL, 0x1E1CC7B5D21806D8ULL, 0xEA64DBB7E95A9D83ULL, 0xA101C41B8A2AD13EULL, 
            0x3AE45128D7A53F48ULL, 0xB9C04A74C1EE669DULL, 0x46C89A64408231ABULL, 0x2F27E45FF3433D2CULL, 
            0xB8DC64F4A0D9006DULL, 0xD525B0ADEA3735DAULL, 0xC012E847654D6952ULL, 0x16F970C80D85D937ULL
        },
        {
            0x084A91553DF7561EULL, 0x686F7166FCA3D6B3ULL, 0x3BF69DAD158A408DULL, 0x88AE5920F63AD43AULL, 
            0xF1A9007FD811F2E3ULL, 0x1F14C4E2414B01DCULL, 0x53E1A2968284AF56ULL, 0x5E46EAB2616D2EAAULL, 
            0xAE7B4AE59C5B476AULL, 0xFC7F9225AC8657A7ULL, 0x8999ACAC9F7A26FAULL, 0x9C1E7CA2592D0C9AULL, 
            0xC859A7A27C3543D9ULL, 0xD086BB35F1E64AC3ULL, 0x102561E075BC75F3ULL, 0xA7ADB1015968452DULL, 
            0x2C09C699B341E464ULL, 0x3CF1A2D6DDBAF374ULL, 0x8844EB0B4E31468FULL, 0xD5D0973E852925D3ULL, 
            0x5F783C853CE8778EULL, 0x23C55EDAD7469216ULL, 0x0761F97DCF3A98F1ULL, 0x1BABBB3125E26736ULL, 
            0x385D27C764E184D0ULL, 0x1E87006E500F165CULL, 0xE46E77098A4861D0ULL, 0x0221B7839E9E32FDULL, 
            0xA964131CD8EA67B4ULL, 0xAF9BF8606B83AA48ULL, 0x2766E6FFECB82AF2ULL, 0xE5E036E48DB88824ULL
        },
        {
            0x5B00B0571E43A7B8ULL, 0x159B7FD84221D4B4ULL, 0x105057595103552EULL, 0xDAD5EA48E2C52949ULL, 
            0x2BCA992FA256EBA9ULL, 0x18EE1AA24CF0F05CULL, 0x430A16A0B3853A44ULL, 0x6541666A2C233183ULL, 
            0xAF8777B496A2B391ULL, 0xA12246C76C1A22D3ULL, 0x75DB8BCA04C0BEE6ULL, 0xF479A2F52E3776C2ULL, 
            0xC24C03B59AAEAC3FULL, 0x9B55963EA234628DULL, 0xD0656DB4DC4EE4F6ULL, 0x9506092B4F2E572DULL, 
            0xC9C879920CBEEADDULL, 0x55C516E31302B4B3ULL, 0x5AB7CA0B0F9304D3ULL, 0x7D0A91AC29D16A08ULL, 
            0x3E6B61ACEE4B25E5ULL, 0x6A06A70D8731508CULL, 0xCE947169373451C5ULL, 0x99EEBA2055FAD5FAULL, 
            0xD7DAB1BBEC49FFBAULL, 0x8487EAFFB4E40851ULL, 0x726C194BA07F452DULL, 0x230805A2C4447C46ULL, 
            0xEA081C6CDC8E869BULL, 0x59C577007D89BC0FULL, 0x0AB3358B9BCB0743ULL, 0xC7F7A535E2F58951ULL
        }
    },
    {
        {
            0x1A8A42F382574C00ULL, 0xB07B5BB95DC56DD5ULL, 0xA4DB11539CB35A3FULL, 0xD92AF9AE6A6C4C12ULL, 
            0x70A761AD6AC0B533ULL, 0x334C657A94EFC202ULL, 0x89B96CDFFC67176DULL, 0xCB45D11938D3C1BDULL, 
            0x96905919619B48C6ULL, 0x2B599EAF93B5D27FULL, 0xB419DCC574FAF96FULL, 0x5C88D45FC16D63F4ULL, 
            0xECA428E53150EFE6ULL, 0x0D87C3FF71A76BB7ULL, 0xDF29D01B8FBA2251ULL, 0x62972609E5821FD9ULL, 
            0x28C7F2A8D43A56F5ULL, 0x2FF5F0C30CED9823ULL, 0x47281039F89548EFULL, 0xB11E886A7587FF8FULL, 
            0x6CE2EA13C93B06F8ULL, 0x136FB80DE2E341FDULL, 0x326FA6A40DB77815ULL, 0xE6FACBE499D605BEULL, 
            0x745195CA98A2CBC1ULL, 0x642A22B89A3404D8ULL, 0x45C6C9BC6E831273ULL, 0xBEC5BD2FE3B0A07AULL, 
            0x64D75AA1F6D57E4FULL, 0x036F0282248D260CULL, 0x1AD462ED017B053CULL, 0xCA82361685968727ULL
        },
        {
            0x28B692C35DE6E52AULL, 0xC1BBF525CDD99DE5ULL, 0x26E944EF6F07EA59ULL, 0xAA9BD4FF2F1CED28ULL, 
            0xC84C6AF9F7900C61ULL, 0xE271FB33D6E1268DULL, 0x3C91298926A54078ULL, 0x05084546C26EB90BULL, 
            0x0444D3CE849514C2ULL, 0x7A15CD6FA6161D49ULL, 0x395599F68CB50E0BULL, 0xD48B97F0113ED83BULL, 
            0x1815FA47CD256102ULL, 0x23712051A6155393ULL, 0x3E21CE1F07AFF49EULL, 0x0163A456FFA77945ULL, 
            0xA8EFA354094FD2B7ULL, 0x199D61898AD19580ULL, 0x2975ABCD6FABD712ULL, 0x3D8521156F3CE63DULL, 
            0x3BF497ABD8FBA87AULL, 0xF2C23F3F0D1D507DULL, 0x5EC01D6086713016ULL, 0x149FF15818A615C6ULL, 
            0x6545E6C61DF986CDULL, 0x5C2A8600DA68F9D2ULL, 0xF639340A363B3BBEULL, 0x20A481580D6C8906ULL, 
            0x1116C0B92B1439DBULL, 0x27ACC064BF85E4DEULL, 0x0252655505F57925ULL, 0x0BAC9889EADCEC82ULL
        },
        {
            0xBE8910B993C95F8EULL, 0xFBC18D1E46F6C1BEULL, 0x7E8A2AE68322BB9EULL, 0xD2B4D0F581FD7A38ULL, 
            0xD1879926393EC323ULL, 0x0940BFA723EF3FEAULL, 0x95D20EB9B4B48EEDULL, 0xE3FCCF0CA8991EB3ULL, 
            0xF26AE99EA4B233EFULL, 0xF7FA5560FF7B9285ULL, 0xCB908A0D9DC7F1A8ULL, 0x7A5024DC425746D8ULL, 
            0xD7898A80D5C0D085ULL, 0x8C263E949AB83E4AULL, 0x9D4126C90327A899ULL, 0x29A1A7E9E5312CACULL, 
            0xCB9A69E9A5D8FBB2ULL, 0x3A0F1A81ABE948CDULL, 0x1DDDB5CD6F43711BULL, 0x8181AAE4ABE796CCULL, 
            0xC45D3C906F4C4123ULL, 0x0F8D150B60369B86ULL, 0xF8B0BEBEC81E9396ULL, 0x32BE67ED113B8CC3ULL, 
            0x56A977DBC0EDCE4CULL, 0x15EC66AF6AA3E678ULL, 0xF3275202D44276DBULL, 0xFA2CEE2C8CCAF48CULL, 
            0xFA0A6E83CD50681DULL, 0x180ECD16C38FA43AULL, 0xEB812608B5252134ULL, 0x1D2FE428DA3C4BBAULL
        },
        {
            0x10D555AC39461161ULL, 0x4C64BC38E49BD755ULL, 0x40F030B8BF004350ULL, 0xB4E7CA3993446B28ULL, 
            0xB7002EA83934276FULL, 0xCE6389FB93DCD165ULL, 0xA84CAC56FB3D315FULL, 0x0912F3BC1CD4FDD6ULL, 
            0xFC9EAFFFCBBAE2B9ULL, 0x16C0391380E011D3ULL, 0x4DE545138143F031ULL, 0x2D5311EC8A417DC4ULL, 
            0xEC1FE03850A8BB88ULL, 0x4B375C3B01746292ULL, 0x6907B8269A23C559ULL, 0xC64CC485D81871B0ULL, 
            0x0A6385361A6E95CFULL, 0x4E9F3C78A5B8337BULL, 0x814C1E81E8EF4E0FULL, 0x9F2993444D6BFF94ULL, 
            0x27ADDC60A271A449ULL, 0x23D79DA01C1AA244ULL, 0xAE093A42144D9D2BULL, 0x1DCF092E00B40225ULL, 
            0xC80D4AFAF92C6540ULL, 0xE1A30CD6CC11587DULL, 0x6A62306CE7B5A76DULL, 0x98006C2EB9D83647ULL, 
            0x4B3E1E61E8B1E1ECULL, 0xA20B60BB23679540ULL, 0xA6D6F551C360B3B5ULL, 0xBD7058416FCB0E8DULL
        },
        {
            0xE528BBE39A0A5BE6ULL, 0x4B90DFD28787AF3CULL, 0x3C4D1A72FBB969E9ULL, 0xCE548C6006350F61ULL, 
            0xDEF105A4315484C3ULL, 0x7065A67DCEAAB827ULL, 0xAB4E8F21EFB1E21AULL, 0x15461CC22A333BD7ULL, 
            0x146033E6C63E76EFULL, 0xF661C5FDFD2ED240ULL, 0x603A2A3E9A41B457ULL, 0x278B5333A5F155D6ULL, 
            0x987597096A2C5F9AULL, 0xD27F60B07AC3A930ULL, 0x9F2AFFBD57C28EDEULL, 0x8355C44C33FACDD4ULL, 
            0xFA82CAF34D5F48B0ULL, 0xEE76A8421DF74817ULL, 0x3309867B1F43E0B7ULL, 0x5AECB505554909E2ULL, 
            0x926869AAA4195B48ULL, 0x295EDD76FFD22352ULL, 0xB3EFA330A6DBCDC4ULL, 0xA2A6337BC2E2B70FULL, 
            0x5FB5F262AAEF434EULL, 0x6703054650DC3A83ULL, 0xD38D59BF454FB243ULL, 0xC4B17BBC36981301ULL, 
            0x19DECD1B1B38E22EULL, 0xBB2B720ED3A8CC0EULL, 0x192B1B17B5EBC131ULL, 0xAE52ADD061ECC1CBULL
        },
        {
            0xA95331D12C9DE692ULL, 0xC46CBBAFB1F27F78ULL, 0x1CECF114649DB521ULL, 0x786C909BC85A5CA4ULL, 
            0xCE87D610516C44FCULL, 0xAA0C1CEDCFDC65C5ULL, 0xC51D689502BD4959ULL, 0xC65D0A13BDE105A4ULL, 
            0xB5D2A12D51C47A37ULL, 0x9110F57BEAB89367ULL, 0x4F8B0C3762BEB69DULL, 0x9BA8972EDD164BA8ULL, 
            0x5ADDB968CB37C22DULL, 0xDB4E1A9CD03B9B2DULL, 0x525357CFA1DA2C30ULL, 0xD94237EF1ECE1C74ULL, 
            0xEAD04E101E0F190AULL, 0xBCD9663CB4EEC59BULL, 0xEE384A9CECE621C3ULL, 0xE6C566081128191FULL, 
            0xCB531EBBA3462BE0ULL, 0xBFFFE5D2F4358C2CULL, 0x0019BC044CB4D3A8ULL, 0x196798573A3829ACULL, 
            0x9F39409426C53817ULL, 0x98B722BC3E798AF6ULL, 0xEBF9967BD66D2E85ULL, 0x72492491CAA11E27ULL, 
            0x342E6143FC2C16DEULL, 0x5C8C927021B54971ULL, 0x22DA2DA56B51AED4ULL, 0x06BD771E79F3FE63ULL
        }
    },
    {
        {
            0xC70880B6CDEFCC52ULL, 0x70AEBA2678CBB15EULL, 0xD38011CAE6271D3CULL, 0xF8D36BBB7C7806F2ULL, 
            0xF4E43368CD95C465ULL, 0x93CAE3C67C36BA74ULL, 0x1B822E51CC7443BEULL, 0x50917AE6EDC0DC9FULL, 
            0xA1C2B4E871B7C3FBULL, 0xA48ADCDE08CD49D1ULL, 0xB51440F4D2116944ULL, 0x6C26E6AD4EEAA506ULL, 
            0xA70F81BE59800170ULL, 0xC2163E287818EDFEULL, 0xA72C6BACBE82584DULL, 0xF48E5EDB39049E3EULL, 
            0x0D4DE0227EF5C6C6ULL, 0x6B70B746E288271EULL, 0xD3F1FBA11CA13A65ULL, 0x842A08EDECECD654ULL, 
            0xEAF43EAEB6B29A22ULL, 0x9C7D8ACFE5585EB5ULL, 0x332556CA79DC30C5ULL, 0xC299982DF38E08EAULL, 
            0x85D0869C65D277B6ULL, 0x99B95F44252DF342ULL, 0x7C0C0DB252DF649AULL, 0x1BBCAD30776AE951ULL, 
            0x8B4226C2EC747907ULL, 0x84017D0C1933A188ULL, 0x45E65688C7CC9A46ULL, 0xF9B5269AD42EDFF2ULL
        },
        {
            0x701F5AB0ADCEA7B4ULL, 0xF79FA9A7039024DFULL, 0xE0B418ABAD8CDB78ULL, 0x555D66BEFDA0C635ULL, 
            0x41F8C5E5DA969306ULL, 0x740321A6AFF931C5ULL, 0x4E6BB926C7E1240BULL, 0xA62C287F200A6D06ULL, 
            0x6CAD97D4468F257EULL, 0xBC67DA41062FDBB8ULL, 0xCB706A63973D201CULL, 0xB09FFA5B659F0FDFULL, 
            0x08C6B3C0A3E2FCEDULL, 0x1557FD7D578272D7ULL, 0xAE4B112985EE5680ULL, 0x72E2F8A831DCE6B3ULL, 
            0x79E3B0822257759FULL, 0x25FB61A9EF38F76EULL, 0xDB0F66F89F4EFEB6ULL, 0x9384D428341B6BADULL, 
            0x34FCE2D4AA6B8591ULL, 0x75B1DC7506A7EEACULL, 0x344296D9F2CB896EULL, 0x45158BBD0DE3191FULL, 
            0x87F2AA2A099C5620ULL, 0x2658E826F89C682EULL, 0x17DBD49D809CC30CULL, 0x86711DD875EE3508ULL, 
            0xD34D48284F13D6F1ULL, 0x50A22CC3A847D1C6ULL, 0xBAB0BFFB8F3251EAULL, 0x3FFCE3E11BD15FB5ULL
        },
        {
            0x2A0D201EFE4D2179ULL, 0x471BF3D428099C28ULL, 0x6A96B6B361528E07ULL, 0x071143F1FF7E6C01ULL, 
            0xEE7A2A40653D5F92ULL, 0xA05AA820B19F816EULL, 0x73F690750A74D271ULL, 0x6BEA8FD4BAF545ACULL, 
            0xADC7061779DA4F93ULL, 0x3C72E65BBE252992ULL, 0x9581A7F37E8C722EULL, 0xF818654CDEE3B3D3ULL, 
            0x8715F4A941CB9FEDULL, 0x45B4C82249572D77ULL, 0x511766B79E004B9EULL, 0xE558B53B56A0C709ULL, 
            0x2034E16395F64179ULL, 0xF4897377D0B6A9CBULL, 0x4DEB62B57A2D8345ULL, 0xDA30A41A4C6CC3F6ULL, 
            0xFFD0D4C41CA9BCC3ULL, 0x45F1B43A80255591ULL, 0x4DB21945D942EB1DULL, 0x824EC71AE73DBBC9ULL, 
            0x99B51DFDD927F814ULL, 0x4E0A376010791A42ULL, 0x08226181B98646DBULL, 0x8EE944486319F97DULL, 
            0x400B5C4642A8E7FCULL, 0x475B4E1D32B6FD8DULL, 0x45BA673BAF03B52CULL, 0x102161D410AFEE3CULL
        },
        {
            0xB3F759CDFA48E51EULL, 0x65A301996D1DE67EULL, 0x4FBA314C488BC5E0ULL, 0xCE3F92C63A0E8EE1ULL, 
            0x7133FC2E240E3A0FULL, 0x93D82DFE1DFB683CULL, 0xFF06EF0A1AF03AC7ULL, 0xFC4459DD637EEFBFULL, 
            0x2E1C79D38ACB333DULL, 0xF8A8E32670292F21ULL, 0x2A2989D6C16760E0ULL, 0x00FC997010B33DA2ULL, 
            0xC6B5C56798D028A1ULL, 0x0578BB95C82BB790ULL, 0xB9A2B631BCC81EE8ULL, 0x880BC4F7DC986139ULL, 
            0x45395B815D07927AULL, 0xCF99051068570B5DULL, 0x8E80AC2A7BE184DFULL, 0xE3473A04ECF350E3ULL, 
            0xB97B5FA8C49CDA0AULL, 0x9B1BA9CC76EB0255ULL, 0x4B501E58D1E4AE7CULL, 0x451864BAFA3718D6ULL, 
            0xA912CCADA3F50A88ULL, 0xBEF7B1CB0F2300BBULL, 0x1FAA8AB9985C0F02ULL, 0x7F1119DAE8A8DD39ULL, 
            0x237AA2937F8B8435ULL, 0xFACC66486A9FCE55ULL, 0xC4A5235A03CAA89CULL, 0x654E3FB210BA5A08ULL
        },
        {
            0x9981EDDCAC8D38E9ULL, 0xFF3B6B3DB7855C5BULL, 0xF46F3DC9319E9A4DULL, 0xDBA698A150B17563ULL, 
            0x8F9F7CA2B549D776ULL, 0x47F3B8DD9789D6DAULL, 0xB11A72DD9F7A866EULL, 0x4BCECC705A415B8DULL, 
            0x79C3BC5589ACAC0DULL, 0x9BD191A072C83F4FULL, 0x16D5446D5BAC3556ULL, 0x1075D20159143CC5ULL, 
            0x81E1A6D835E911CFULL, 0x999247D078880923ULL, 0x2EF36ECFB11F694BULL, 0xFE93798FDA94A790ULL, 
            0x836CAE01EAFE9B67ULL, 0x026973F9792F7C31ULL, 0xCE9208CD0DD9A395ULL, 0x91FBA7E63408F63DULL, 
            0xFA540075ADFC1AE7ULL, 0x3B6CCBF7F02931AAULL, 0x3E87D41977ED3844ULL, 0xC7478296FE9564DDULL, 
            0x1C80BB5108EA07C8ULL, 0x2C550CD66B8758C9ULL, 0x70A42C8027CD46ACULL, 0x704D3430D54EF540ULL, 
            0x098469F06989E430ULL, 0x6346637D11612DE4ULL, 0x6E6F1B9C3397FC99ULL, 0xCFC48572A81B365EULL
        },
        {
            0x7E1981D1DB3CAE22ULL, 0xA459652EF5CFFC3EULL, 0x2F70D54F7166A5B2ULL, 0x5530067063232514ULL, 
            0x412FF1B9E1F18433ULL, 0xC3CD2EF37E553611ULL, 0xA5F1BA7D17421537ULL, 0xDA6330217945C0C1ULL, 
            0x0369EBC1FCCDA00AULL, 0x94C1C828F909A9C7ULL, 0xA34CDD50F8F7F52EULL, 0x4E725458C673FFA6ULL, 
            0x5E515AF9A5FE4F37ULL, 0xF6438F2053C46052ULL, 0x7D1FD6BDF0C08F3EULL, 0x39BA1A902B9E4852ULL, 
            0x7338C9A2ED6EE313ULL, 0x0117DFA368F6860DULL, 0x032DA0A46BA6CE11ULL, 0x00E37951968101A8ULL, 
            0xBE2F484BFDCFAB7EULL, 0x49651D6AF90FEC12ULL, 0x83CACA4EE048F47EULL, 0x6077E1F03C0C6576ULL, 
            0x8A2034928BA8C7D9ULL, 0x0DB4F0ACF63DDA39ULL, 0xEB753040ECB0F11FULL, 0x1C0F1550E6280493ULL, 
            0xC3484E14E52E970CULL, 0x82956D5E584A337FULL, 0x2E9F46A14C1D4265ULL, 0xE6C880F2B52056F3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseFConstants = {
    0x0384BFBEC73C5284ULL,
    0x3E6C223AD7C57C45ULL,
    0x7A2F5B56AFAB2265ULL,
    0x0384BFBEC73C5284ULL,
    0x3E6C223AD7C57C45ULL,
    0x7A2F5B56AFAB2265ULL,
    0xE376A631AB6597FEULL,
    0x832A7FAF658C08F6ULL,
    0x0D,
    0xB8,
    0xEE,
    0x39,
    0x9A,
    0xBE,
    0xF0,
    0x97
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseGSalts = {
    {
        {
            0x5F87F7292CC7E30FULL, 0x173B21EF43B2BD22ULL, 0xB74CBA37C177148BULL, 0x49E6B8407B809B2FULL, 
            0xC86EEC49E4A7910DULL, 0x6C27F69129E98817ULL, 0xC458523EE1CB6481ULL, 0xA1F2757FC9FD1405ULL, 
            0xB51C18F2016F7628ULL, 0x2A9AD3186DCC0392ULL, 0x842382DBDD2C4C97ULL, 0x6CC71A666A347327ULL, 
            0xD6E36A279C20E8AAULL, 0xAC3FD49870C60AEAULL, 0x4741A056C77C9103ULL, 0x08F76E67E50CAD15ULL, 
            0x5D5E7A2339A71CB3ULL, 0x61C8F8491572D867ULL, 0x62E3F735F90B5202ULL, 0x46561B8E87F05E96ULL, 
            0x5A6F63BBF7B094F9ULL, 0x21DC11048E172E39ULL, 0x295C6A67EFDBE59DULL, 0x70C954454F31C91DULL, 
            0xC64AAE81CA356171ULL, 0x287702232DB0F70DULL, 0x23DF2D98087D57D2ULL, 0x53F9E260FE4F7CBAULL, 
            0x1D3D7DAC66E96344ULL, 0x76441B960EE478E9ULL, 0xBEC95C0AB9B2D74DULL, 0xD55EE15A28E6F9E4ULL
        },
        {
            0x48185B4FB95E7CEAULL, 0xBCD61ED65583C654ULL, 0x8CA3D26B7B8D7C63ULL, 0x1317B3B95A5FD8C1ULL, 
            0x5FEB476DE5A06426ULL, 0x750041DC9DCAEB2AULL, 0xD28CCECCF8FF20C4ULL, 0x2FF6E25960C96350ULL, 
            0xDD4207941376506AULL, 0x6A7CF860984FD848ULL, 0x1F49AE9BA762F98FULL, 0x2E07B1A420E158CDULL, 
            0xC76AD53B9E4EEFCEULL, 0xF270220B04C2B195ULL, 0x3F8A0F96F53744BBULL, 0xE9A7FE576C19B5F2ULL, 
            0x001D8260A099AF20ULL, 0xB4495E7114303789ULL, 0xED14B32546D0A453ULL, 0x04C68B0F25C2BF8EULL, 
            0xF9BDF76B4C00AD8DULL, 0x52D6F57B19DB7EF4ULL, 0x3ECF712C978B0CC0ULL, 0x73E36EC2A66DA7ABULL, 
            0xEA05E78522A1E042ULL, 0x34046E00CEFB5B54ULL, 0x7E26390DACE798FEULL, 0x9F7437B0EEA68B08ULL, 
            0xAB3B614D7875DBBBULL, 0xDC4D0E9A7D5D8F96ULL, 0xABEB627B5DACF127ULL, 0x4FA1C7C34EED21ABULL
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
            0x9929E7F02473F5CDULL, 0xF04DD03BE1A3687FULL, 0xF288F8E404E58754ULL, 0x319380C6BF9C656FULL, 
            0x2962FA4EDDFF1CE9ULL, 0xFDA3BB6415F547EBULL, 0xB2A2194804053B76ULL, 0xC148F2C59A8E9556ULL, 
            0xADD3FB637599D88AULL, 0x402EFCB03F32BC03ULL, 0x4CD08A9C98E2C1C3ULL, 0xF2F7223E7888AE7EULL, 
            0x3DD1EF0F4372CB0FULL, 0xA11DAAEA50B4CF77ULL, 0x374EA2F70D28680EULL, 0xBB00B840833F8C46ULL, 
            0x9C402708B1CDDF0DULL, 0x12D12477F158D138ULL, 0x66639D74A6F7C1B2ULL, 0x2BCFA2209E62F36DULL, 
            0x1FA2AF4EABBCDB66ULL, 0x3230E60C3D14158EULL, 0x4F61C09CE0A43BF5ULL, 0xAF7684BCB68AB960ULL, 
            0x2CC76B1552042F14ULL, 0xF5D71389F5894911ULL, 0x8621B890AE90ED1CULL, 0x35EC719A5F5D17E8ULL, 
            0xDCE5C7AC7B54E731ULL, 0xB8BE6A190DAE0CEEULL, 0xFFEA33BCE91E3880ULL, 0xEC21FC6242844BD1ULL
        },
        {
            0x2E9A734826E920B3ULL, 0x7005B9842721B55CULL, 0x6D214ED9A5751C9FULL, 0xF2D13CC671F5697DULL, 
            0xA88E3002E998835DULL, 0x258E41D976533C0AULL, 0xC12C514315B802D6ULL, 0x600BE114FBE0F412ULL, 
            0x85F98B25BC16C8D4ULL, 0x3484F4B62EF2B9C5ULL, 0x6F9301962BB7E600ULL, 0xDC9D7AE37EFA42D0ULL, 
            0xA5F42F81812248C3ULL, 0x3E8E0CB8EFE6ED2AULL, 0xF74DDE46AB96AE37ULL, 0x9278A9501A939EFEULL, 
            0xF0349BCFB4E67776ULL, 0x0EE20F6F345948C8ULL, 0x482807B20AB31724ULL, 0xE7D7C27937CE88EBULL, 
            0x0FD4F271EAD28109ULL, 0x59E0CEA4C94D31AAULL, 0xF2279C61EF16B2EDULL, 0xC8F22490585978B7ULL, 
            0x838155A0C14C154BULL, 0x4D667F99732D96F2ULL, 0x98BFEBA2D63A7C5BULL, 0x1AC9166800C45A54ULL, 
            0xC6DCE80903BAC5C4ULL, 0xBEF37EDE6B0B7C28ULL, 0x3503ED42259DCBA6ULL, 0xA7ACA397A378EC7DULL
        },
        {
            0xAEBC129ACFF3AB8EULL, 0xE91CBA24546A696FULL, 0x4BE9F3FAB6C2A786ULL, 0xA07143430DC8DDCAULL, 
            0x95B452BD4BC56DCAULL, 0x9908181356B29A93ULL, 0x046820EF7D43384DULL, 0x9A0197219A871363ULL, 
            0x1EAA086EC6850D5AULL, 0x91347E6CA5071F4AULL, 0x0F1A9C372CBC1014ULL, 0x69C6F243E0B657BEULL, 
            0xACBF6DB4054EB822ULL, 0xA9A7AF9C14D81B24ULL, 0xFA014233F49369A2ULL, 0x42B7B8932616F8E3ULL, 
            0x3EB92470437BA976ULL, 0xEE7AB1D83C4463B1ULL, 0xC320E781979052B4ULL, 0x249E9B6A55C7B9D9ULL, 
            0x8B717A8C44F6A8A7ULL, 0x853E138CE91E5292ULL, 0xE79855D364FF1771ULL, 0xA03888D242DFA319ULL, 
            0x90D62CD59955B07BULL, 0x43BAA11FAF031801ULL, 0x5D8A9585BFC40661ULL, 0xE46EBF278DC62C2BULL, 
            0xCF42DDEA6B4F4B99ULL, 0x796EDACC6F823C28ULL, 0x28FE55DABD27A8E3ULL, 0xCE5588489F19C538ULL
        }
    },
    {
        {
            0x7E21140F367BECBAULL, 0xAAEB76F0B4D6DFF4ULL, 0x056D031F04C566C4ULL, 0x4544FE6D2A0FA0F5ULL, 
            0x30D0F7D7436EC533ULL, 0x47D1FBF5CC34F331ULL, 0x616683DA3F190089ULL, 0x0BE3D3C2093CC485ULL, 
            0x7F59A32CFD870EB1ULL, 0xD84A4E9A04DE1857ULL, 0x9DBCE3DD22070087ULL, 0xCFC92659320A3EEDULL, 
            0x2A3716EA8CD8C51CULL, 0xD234448A1E1B50EDULL, 0x21B897547A0C843AULL, 0x1A145008650AA8F8ULL, 
            0x952A7A0EDCBC0013ULL, 0xD4706DB365C3B3A5ULL, 0xDB44A419495E7518ULL, 0x97D11956051074B6ULL, 
            0xD48C34225F374751ULL, 0x84DA22DAABC80F59ULL, 0x3D042544A370421DULL, 0x989F18B4C879AE4EULL, 
            0x80ADA0B0622A585FULL, 0x0662E22BBDB2BC69ULL, 0x157A338E366DC531ULL, 0x82FABCE731D46DA9ULL, 
            0xC5124C145AD3D0EEULL, 0x9A88CB14BC2F7485ULL, 0xFE5724F514A05AC3ULL, 0x193A067454A8E4C7ULL
        },
        {
            0x534303828D6F6724ULL, 0x2759C51EEB7E470EULL, 0x1243F0D327403B59ULL, 0x5C7EA6AA609523CFULL, 
            0x44F112AC25456C7BULL, 0xABB2A7780A1534D5ULL, 0xEED4BCE06CAB518EULL, 0x15F96944273C238EULL, 
            0x9B993C7C2D9ECFB5ULL, 0x0472DD313237C1C3ULL, 0xCBAF0E972120E55DULL, 0xB991888827E92583ULL, 
            0x15508D3041F0C969ULL, 0x36B7C081428E7DE9ULL, 0x57CC5AC08CFD4F86ULL, 0xE1613D34FE95B9DAULL, 
            0xAF90B06DA84218F9ULL, 0x02BD97909DAF6FABULL, 0xB77E20DA6E109534ULL, 0x40BEAD60FDD272A1ULL, 
            0x7384995B213F8194ULL, 0xF965B3CEDD6D77CFULL, 0x59F935F9C9E649A9ULL, 0x7C989753E0228665ULL, 
            0xE9904BF8FBCE3385ULL, 0x95495CBD95F8C55FULL, 0x267C2F993EDFC15CULL, 0xBC37E79C3B2DE160ULL, 
            0x33BAAB28867F29D4ULL, 0x0C5CC81E7777D138ULL, 0x33FC33CFD1848EF9ULL, 0xBFC47E272745BE4FULL
        },
        {
            0xF48EBCBB11BFAE70ULL, 0xF7E66074323957DEULL, 0xA8F099641162D640ULL, 0x76AE1174BF5B5176ULL, 
            0xA1A523E7DF0FCC80ULL, 0x13E44B783F20DC23ULL, 0x73CF9DFFDC4879A7ULL, 0xB4C6C00F12DE059AULL, 
            0xDBDE042FDCC7EBF3ULL, 0x30A568E64EE5F251ULL, 0x37D1683A3706E3D9ULL, 0x16D69DAB4BCC7571ULL, 
            0xC09A10962164ADFBULL, 0x333CC0E2AB33917DULL, 0xC050CF97494945ADULL, 0xBF2763E9BD235DC9ULL, 
            0x8DCF2B0D3F27A33CULL, 0xD25D68C113CB9E79ULL, 0xF06F625B67CE2402ULL, 0x452624C015125B79ULL, 
            0x71605A4A4FB2C7F2ULL, 0xDEA5543569CDCA9EULL, 0x9EAEC851DABD9F07ULL, 0x2BF33F522575F3E1ULL, 
            0x8F4D76E08ED41E4CULL, 0x771A56BBF3EEA1F9ULL, 0x47223840117C6611ULL, 0xA26A9E86EA9425F4ULL, 
            0xBD46A9DF3B11E5D9ULL, 0x4B5BDCFE0D88EB73ULL, 0xFF9FEEDC44A6DC57ULL, 0xAEAC2CFDA7E5F2AEULL
        },
        {
            0x5D84DB04E71BB10CULL, 0x401775C2427F417FULL, 0x8FCD82A82BFC05EBULL, 0xF4369D1213FBD37CULL, 
            0x29DB91C501704802ULL, 0x5E1E858576A0F460ULL, 0xF9AB5921356F241BULL, 0x2854B1DB6FDB1BFFULL, 
            0x4E99523657610A45ULL, 0xB9CC87D5AC7C50DDULL, 0x1652211FE8D1BC91ULL, 0xF2BFDDCE36833787ULL, 
            0x3844B4537B1CC69FULL, 0x5A3BF262EE540BFEULL, 0xB0DA7AF8FDA520A1ULL, 0xFDB2FE43846CB01AULL, 
            0xC13D52A9462E525EULL, 0x2F2FF0470615F0A5ULL, 0xD57AA9597F24BED3ULL, 0x21BBB43DE6AA4B20ULL, 
            0x28E9A5AC9FCA9B40ULL, 0x10869DA7F85AB418ULL, 0x7EB802CA3EA9661BULL, 0xF454FFCCEA0C7465ULL, 
            0x8496CA3A1C1BA7B5ULL, 0xB4083A6631F23CA3ULL, 0x3E13018F573B3687ULL, 0xBBA3A85BF6F01542ULL, 
            0xC077295D5BA00259ULL, 0xACCC0102EA256A58ULL, 0x452C42218D8BB7DEULL, 0xC9B4302B3CA9CC2FULL
        },
        {
            0x7EE3CFDE05422F9DULL, 0x9D634B6306D7FD24ULL, 0xE812E50E75105CAAULL, 0x8BC733396CB22CF6ULL, 
            0x41275590D56A9C70ULL, 0xA20ACFFFD5727FF4ULL, 0x8B1D3AB9DD953208ULL, 0xCA3684E0347779DDULL, 
            0x46F5C97EE0ABE2E2ULL, 0x619B19622623DD4DULL, 0x6BC6C1CECFD5F00DULL, 0x83E7672FE17A955BULL, 
            0x797126B0BEA161AEULL, 0x2411F042955E92AAULL, 0x2189F5EB91D22D5CULL, 0x3AA12CAA7ED96906ULL, 
            0x64EC683CF3A14307ULL, 0x8615B05EE54C999DULL, 0xBD5B1CB1FE6EE0B1ULL, 0xB8F198BEAD703144ULL, 
            0x365852561E6200CAULL, 0x1A81822B8F079E50ULL, 0xFFAE2F1FBF725B16ULL, 0xB6046700D6E10AF5ULL, 
            0xD8DE15F334ADBC18ULL, 0xEC5CA58EB124FFB0ULL, 0xB4CA16FF37425EE2ULL, 0x5F5C9364038287FAULL, 
            0x0C80DE5EE13E81E1ULL, 0x08B10AC3706A731EULL, 0x3F3DD2AB58250A6FULL, 0xF62E5F82F7974949ULL
        },
        {
            0x4A87477D2A9E577CULL, 0x6CD3D83D5050F899ULL, 0xF607CE229F51066BULL, 0xFD70385296BF216FULL, 
            0x4CF53AF16F66E1C7ULL, 0x36787853B4BB59E2ULL, 0x45222693A52E139DULL, 0x9C5994062E8D12BAULL, 
            0xAD663CDD4D4F838CULL, 0xB645B7735648DD01ULL, 0x71FDA7AA24E6884FULL, 0x11FADDED8F9D7CC6ULL, 
            0x040A3EC2AA55F7F6ULL, 0xB087454CE980FA19ULL, 0x52FB2C9305463829ULL, 0x72393730CAA536D7ULL, 
            0x2272DB1A6BF95A88ULL, 0x928D6E9EE3A4051FULL, 0xF723B24F12C5DA21ULL, 0xBABEF3F359EBDE20ULL, 
            0xB1F98C93371AB42BULL, 0xE57ADBF91683DA1AULL, 0xEC57A93620DA9E7AULL, 0xD64953D9D74872AAULL, 
            0x77C716786C3DC11FULL, 0x7333AAF0B8E5C8FEULL, 0xAD8385203FDB2452ULL, 0x59D6515BD572C4CBULL, 
            0x069188B0A69B159FULL, 0x62AB0F18C776B15EULL, 0xCA3EA31782F08D62ULL, 0xA0D0E4AFF5986202ULL
        }
    },
    {
        {
            0xB6CCC795F1A67600ULL, 0x4E768A3E9D7723D1ULL, 0x3B6780B1807F7F1AULL, 0x226DA9F398944CACULL, 
            0x9CBBE0768CDB6278ULL, 0x1F498BB84FF604C7ULL, 0xF3FB0EF5499C992BULL, 0x1AC029BA3C290D35ULL, 
            0xAA75C532B22B4CE3ULL, 0x33C419FA00589637ULL, 0xB8BC0D37D25261E3ULL, 0x8B53E6B5997043DAULL, 
            0x6088A3F274732945ULL, 0x06A069AEAF125619ULL, 0xAD976AFCB8E4D41FULL, 0xCA7A1C102FC95E5EULL, 
            0xF3950672D8112D4FULL, 0xEE375585F34553F1ULL, 0xA38D764767321927ULL, 0xC94825165BA9312EULL, 
            0x5D9E4A72EB9152CAULL, 0x5D8505D2B419D01DULL, 0xAF50D165CB443522ULL, 0x5457102D105E2DECULL, 
            0x32057E35402934BEULL, 0x76434D2F24CA1BC5ULL, 0x962F95BC1DF84A11ULL, 0x3C5E70FA95FF27B3ULL, 
            0x0FF4A54DD346DC63ULL, 0x20A1A060884DAF38ULL, 0xA3674D45892E32A7ULL, 0x827A0724C21D2CD5ULL
        },
        {
            0x07400E3091F848B5ULL, 0x8E4128AEEBD25167ULL, 0xFC73764F536D0035ULL, 0x3BBE5207FA66AA8FULL, 
            0x428464697C5EE11FULL, 0x36C04C1CAAF703BDULL, 0x5F75462F799720F2ULL, 0xFECB53E1A2A9D208ULL, 
            0x6374F822BAA9898EULL, 0x44AE00766FA8BC65ULL, 0x1BB8E51B329C7B17ULL, 0xAD90D55647701281ULL, 
            0xAA1604D01D84FAE9ULL, 0x484EAB5CDD540F8EULL, 0xDD096E1E54B1A93FULL, 0x314B9E022D2D2626ULL, 
            0x1E1C378CA91700B5ULL, 0x62C1DFE0730D657AULL, 0x7AA29EE5F17DD0BAULL, 0xF2019822BD68A452ULL, 
            0x705E4FB6A02A3B3AULL, 0x29355C4D935203A2ULL, 0xA55EDE35E544A172ULL, 0x1F9951C0E476B2A0ULL, 
            0x0F2E99678B22BF1FULL, 0x43C303C0456AB298ULL, 0xC9199D5D4B850DF0ULL, 0x3C74AA052A1F94ABULL, 
            0x1AAF31A8DF1E0E0BULL, 0x58912239B33BB6BDULL, 0x12012A919712C127ULL, 0x938C8834B28EDBD9ULL
        },
        {
            0x6863FC45CAF1B3D8ULL, 0x0F256F93F1BB9242ULL, 0x2D472ADD46E2D30CULL, 0x87937DDE30119FEBULL, 
            0x54B52D620BA4A727ULL, 0x2BE43B9D4A4F931CULL, 0xFEE15E5819408B7CULL, 0x51CCC65787E850C5ULL, 
            0x25D521365CD5D07BULL, 0x3A260157B4851350ULL, 0xA05CBB291405807CULL, 0x2D597CF714F0261FULL, 
            0x0F7D03322072A02DULL, 0xBC0C5182CCC65585ULL, 0x4B887A038C3F857FULL, 0xCF6A9B2394625AC9ULL, 
            0xE63D3E7A312D549FULL, 0xF50144C87A564E21ULL, 0x30FE1F85C6540F93ULL, 0xADAD919E0A2968BAULL, 
            0x04D25C3BFFED8656ULL, 0x0FE05341FFF4F1DEULL, 0xC38F620321EE9EFCULL, 0x62BCF0377A6AA00EULL, 
            0x644762DB5C15136AULL, 0xCA461A585B12D86AULL, 0xD78AC2B764E2A606ULL, 0x28507D2F0904ED2CULL, 
            0x3342F35D2BC5EFD1ULL, 0x9C133CCEDB552D57ULL, 0x8F4C04E1E508AC63ULL, 0x930E81AC41A9E8BCULL
        },
        {
            0x8BD505676ECE56F3ULL, 0x43A13741220AE295ULL, 0xA45F46686D0228E8ULL, 0xCE04387E92A76FE6ULL, 
            0xE4B8A28257E4550EULL, 0x3E71D085FB2D1D6BULL, 0x13CFE9FE627D9E04ULL, 0x56724F9F50DDA1CDULL, 
            0x25A571B4B388F808ULL, 0x8149EFF33984C0DCULL, 0x3A94A678F0551446ULL, 0x59CC3575327C5BB2ULL, 
            0xFC08E47F44218662ULL, 0x676B98AAC9FBEE23ULL, 0xFE6531EC3E25E759ULL, 0x897CCE4E41A41952ULL, 
            0x78EFC2BD6431855EULL, 0x2DDA327682473D22ULL, 0x3502EA1136CBF38AULL, 0x9CA3021AB5316B8EULL, 
            0xE482663CA5868F28ULL, 0x0A1EACBB3DD185A1ULL, 0x304CBC649920A037ULL, 0x025A287A3B6BBF4BULL, 
            0xECF15F0793F9D308ULL, 0x5620631FF2027582ULL, 0x40AE2CD114A67D04ULL, 0x4CD7B72D74C8ABF1ULL, 
            0xCB23072685F8CD4BULL, 0x598680B911CDE176ULL, 0x6A8375103CBD73C9ULL, 0x62AF7D7C9EB8525FULL
        },
        {
            0x81138EC9E26D65DBULL, 0x02D19CD73942854CULL, 0xD08ADE855BF76637ULL, 0xE0532777390FDDF8ULL, 
            0xCDFF288B3092AFA8ULL, 0xED31B1BE5074CCA4ULL, 0x720D7518456E86F6ULL, 0x34854107DB00FB9DULL, 
            0xBF8E28F415ADAF20ULL, 0x8370FF87183381B8ULL, 0xD33ED341191AC1C3ULL, 0x4FF2AB2275BAE2F9ULL, 
            0x1D18B50E6D6159F2ULL, 0x28048C55959F4A3BULL, 0xE744399267DF8BB2ULL, 0x41BC92287A45F4F5ULL, 
            0xDEC6618FD427BB59ULL, 0x2A782AFA2E4477F5ULL, 0x6D307BC19387290AULL, 0x96D0E43F42FD8BAFULL, 
            0xFC16E13A21CE9AE0ULL, 0x3F917B293F9D1EC3ULL, 0x02D044BCAFCC3E59ULL, 0x84D47FE1F7017588ULL, 
            0x92976E8BDDB08DC3ULL, 0x17B5C88B927534BBULL, 0x86A320BC27FBA7A8ULL, 0xCA4D848FC73A315CULL, 
            0x5C4CFEC27EA1DB6FULL, 0x89A884ACB8A5E17DULL, 0x389024A3C297148BULL, 0x7F18A0D1CB5BA5D1ULL
        },
        {
            0x4EC876E32EB3FF61ULL, 0xA1C3ED64DC784709ULL, 0x5E8A35552F001270ULL, 0xF26D1AB2677B8AD4ULL, 
            0x4DF8FABA507557FDULL, 0x67B1FD474C412242ULL, 0x832A4A6892057709ULL, 0x7A5D8A38EE00473DULL, 
            0xCBE9B1F2E7E69BF4ULL, 0x2358B1F671B8B90EULL, 0xCF2A67D9E16E24C2ULL, 0xAB236269DCC4AB10ULL, 
            0x84F664DCA4DF1094ULL, 0xF270DD1AA2810663ULL, 0x6D4BFEA145602D0AULL, 0xD69713637AF98F57ULL, 
            0x5EE203CC80015114ULL, 0xF01458620DE38FE1ULL, 0x7C732ECC67DFE3CDULL, 0x0156B4F02258A0E7ULL, 
            0xCBD39A02BB7B9E3CULL, 0x63C50D3EBEDB4DC5ULL, 0x68D6E062884508E6ULL, 0x3A7E084D0EDDCF1AULL, 
            0x7BB8420CEE40A91EULL, 0x8A9FEF382A1F9B28ULL, 0x0DD2171F616FD433ULL, 0xAB6B754512711D93ULL, 
            0x48B0DF61C7515BFBULL, 0x0CF315F5D83A07F1ULL, 0x35CEA05C0ABE7A14ULL, 0xB99838AF9594F907ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseGConstants = {
    0x6E377CC3999CC021ULL,
    0x6FE398063FD37E10ULL,
    0x26B2C7AAAB7EC35DULL,
    0x6E377CC3999CC021ULL,
    0x6FE398063FD37E10ULL,
    0x26B2C7AAAB7EC35DULL,
    0x55D4692A8CFA311CULL,
    0x2719B73458AE1D77ULL,
    0x42,
    0x51,
    0xDE,
    0x16,
    0x15,
    0x4D,
    0x35,
    0xE2
};

const TwistDomainSaltSet TwistExpander_Capella::kPhaseHSalts = {
    {
        {
            0x0728CD993626EA95ULL, 0x6DDD1B3FB6CBD4CCULL, 0xD7334BA66317C836ULL, 0xAE9AA3204F1AE4C5ULL, 
            0x7E3AC78EB707518BULL, 0x2EF095FF3B8EDD5EULL, 0xC4A163DCC88B3F59ULL, 0xC050E03F464E6460ULL, 
            0x4F56552B32C4F19DULL, 0x891A900D5FC40C31ULL, 0x3DC059E298DAD58DULL, 0xFFC0D038FE331A2BULL, 
            0x0EB00FFCA821FD9DULL, 0xB622C99DA606781EULL, 0x0C22CD2E257AA4D6ULL, 0x70C32E58F771D26FULL, 
            0xA2FDD5F1D9F759A7ULL, 0x5D9EF644DFAFCA42ULL, 0x1BFED3E2958550DAULL, 0xD49412EBD10D683DULL, 
            0x4C51C526DA7B1315ULL, 0x81337392083EC01EULL, 0x50BBBA1E493503ECULL, 0xCC9BCB9E0CF641ABULL, 
            0x4AAC90CD0B5F4F2FULL, 0xAACFB40249B232B0ULL, 0x8546014DCE2C2426ULL, 0xCD363E2373E0BF74ULL, 
            0xA4934474C036FF1CULL, 0xA9A86A702A67B168ULL, 0x3D2AF12CCE5B94FDULL, 0x7B8B641407654DE7ULL
        },
        {
            0x5D57D65C9267C3B5ULL, 0xBA4931DDA0244328ULL, 0xDAA006584B12F920ULL, 0x30B0F779B2D954D8ULL, 
            0x72E298820F492018ULL, 0x83608E4164A5AFD7ULL, 0x7619B75DB704EF3AULL, 0x33E69004D3C8AFCAULL, 
            0x6543F69AE8D3AD08ULL, 0xAD130C0D4E2D3D42ULL, 0xAD5D705FD9C3BBFEULL, 0x932B7A27BFBA035AULL, 
            0xD4EE5F9BCA6104D7ULL, 0x70F82A53A555192FULL, 0xC4939DF10E19B68DULL, 0xD883080E85D16C16ULL, 
            0x9405B94AEFA350F4ULL, 0xC2953336CD12DBAEULL, 0xA7B19C0EE04E3CE5ULL, 0x99E2BAC8FA35AE45ULL, 
            0x8575806EB5EF67CDULL, 0x59CA67A6D5B86952ULL, 0xE1058E371CA1496FULL, 0x33FEC0C0910F2979ULL, 
            0xE9FE287C33408BA3ULL, 0x6554BE7A80DACEA3ULL, 0xC1BFE454A5EB791BULL, 0xBFB15C2918BD6D39ULL, 
            0x2030BA31F3C81D10ULL, 0x5D050DD8BCDDC208ULL, 0xA1150125BE4938B8ULL, 0x5DF89A42947F4958ULL
        },
        {
            0xAB4D8EBC210B61B7ULL, 0xDC35BD6AFD4BD8F0ULL, 0x67650AFF19FAF015ULL, 0x1866B702D64DE839ULL, 
            0xB12A37D8F0D7C115ULL, 0xE3B40CE55E95CBACULL, 0xDF10821C2BACA370ULL, 0x86AD9C84FB302959ULL, 
            0x7CDC7339912B75E1ULL, 0x0ECF209989934178ULL, 0x908D1122B4F62CE3ULL, 0x76FC2CBCA3A1D6B4ULL, 
            0x937EF6CD63A815A8ULL, 0x4984F46A025A3472ULL, 0x2C94D1A1266F304EULL, 0x12DFDC490B49BC2FULL, 
            0x00C9D6DEB29C0CB1ULL, 0xB5E2BD109EDBF342ULL, 0x7D6F5ADCD325BF8AULL, 0x9A10E3F19028AA42ULL, 
            0xFFA2AAD16C43E324ULL, 0x61E1C6329FC46647ULL, 0x101B700148618C8AULL, 0x6BCBFED7A48FAD7FULL, 
            0x51F33D3E24FAD83AULL, 0x23733007621AABEEULL, 0xF0F23005378C63D8ULL, 0x7B285731B66B04B8ULL, 
            0xD160F30C98F96F83ULL, 0x3C5F45D73D8DC365ULL, 0xE9BED0B495EA39C4ULL, 0x86F1894267CB7652ULL
        },
        {
            0x75B32DBA235A3759ULL, 0xED740BE473CA420BULL, 0x0A988DFD282EDCF3ULL, 0xC5C381B461A93523ULL, 
            0xB4F5A417BB6514D2ULL, 0xC9E31E642ECA0B86ULL, 0xD7CADEF598CF80C4ULL, 0x37CFA2B98B0A074EULL, 
            0x0878498C1062F516ULL, 0xEE4E4BE1F88D7717ULL, 0x9A50E88B5FCB2496ULL, 0xB475B1F7C1BDD879ULL, 
            0xB2A1051AE764797BULL, 0x41697D0DD88EEE44ULL, 0x86D135CBE90261D2ULL, 0x8E07953F0312B815ULL, 
            0x9D0A0D5B9B94F567ULL, 0x87AB4C8B0932D8B7ULL, 0x7A32F391CD552F23ULL, 0xDCB86EEB6D66F1BDULL, 
            0xA93F96D0F2C61027ULL, 0xDD9563518FBC11E4ULL, 0xF09EC90C215816F3ULL, 0x8744F7A280780C25ULL, 
            0xE0D2CF70C90544D3ULL, 0x1FAF2282BE22F3F1ULL, 0x73E91638707E47F6ULL, 0xAB07121F7092555AULL, 
            0x7D2F4ABEF0EB73CEULL, 0x18FF05C4F76BB9D0ULL, 0xF69EA91F1E452F3FULL, 0x9A9C429DB92CAE74ULL
        },
        {
            0xD82210C53E3690E1ULL, 0xEBD616B94A2DF46CULL, 0x522B2E13BED4EF1FULL, 0xCAC83E6109EACEEFULL, 
            0x5D874F31F50CF8EBULL, 0xD3020A9039F53F15ULL, 0x7E45AF57F4F026EBULL, 0xB25365BCAAC72A1CULL, 
            0xC9CDC03E5FD6812BULL, 0x42A6D0BF7B8405AFULL, 0x3C27E828399DF756ULL, 0x660D692C50D289A6ULL, 
            0x78C75C69842384BDULL, 0x85BFFF9FA89FE879ULL, 0xB86C5B65CD7370D2ULL, 0xB413047DC763A278ULL, 
            0xB6DB552F6332C86EULL, 0x307F52B01B520836ULL, 0x20A176A0036F32A3ULL, 0x9D6EA013744A26E6ULL, 
            0xE13F0862157FFE2EULL, 0xA2B4A6CE4E24BCE7ULL, 0x35760A7D222922C5ULL, 0xDD79A36CBDF93D53ULL, 
            0xF42753D6D6F16994ULL, 0xB5F9FF1BF72F6C36ULL, 0xAF6F0D61507CCB63ULL, 0x6A39914336863E59ULL, 
            0xA79A9F15829CFEC2ULL, 0xD9C36206360E672DULL, 0x033F9888D3130E3AULL, 0xD20815CF6E219CA4ULL
        },
        {
            0x0F8CA0993946DBFAULL, 0x5B579170C3BE02E0ULL, 0x19C37923580D32C7ULL, 0x1E3EAB3AB297B215ULL, 
            0x550EC92D7AA881E8ULL, 0x11791D8A571DFFA0ULL, 0xFB63BE80A3872A76ULL, 0x584A18843DE05A56ULL, 
            0x6C21F23FA7A69D99ULL, 0xE851E415C72EE662ULL, 0xCD214528F812E097ULL, 0x51103FA1ABC6CFE4ULL, 
            0xC5FF106BB69B2258ULL, 0x7A77A09CF02491A5ULL, 0xC0ED1DF9019B296AULL, 0xA5419B2B53219B22ULL, 
            0x728FACC906262EB4ULL, 0x5D7AD43E2F7CABD7ULL, 0x64E9581391AD7A10ULL, 0xC5FD3FF254E25E0BULL, 
            0xF11A9FF122256F13ULL, 0xE7F902F20E845BDAULL, 0x5E58C42F53F24838ULL, 0xB96A048004D537B4ULL, 
            0x024B81B18E636C72ULL, 0x479C27EAB91B856EULL, 0x7B9ACE939BAFC979ULL, 0xB19FCACC666B0E16ULL, 
            0x3CD10E0BB18EE8B6ULL, 0x8FB3D17CA18D3CE2ULL, 0x6FF023E7FA85ED6EULL, 0x220DEC050BA11544ULL
        }
    },
    {
        {
            0xA491E538DA3B4126ULL, 0xB7E0DE2D11902F2EULL, 0xA07FBE2849506D28ULL, 0xD9AE46C99FD6005EULL, 
            0xB96A8B0DE23A3119ULL, 0x98349499FE23DEE1ULL, 0x9B880CB57F1629CFULL, 0xA0BA94A5F191B006ULL, 
            0x5494CB44BBA906E7ULL, 0x98C7A560B0CFD6C9ULL, 0xF97D379F00B66E00ULL, 0x7DBBD88A4745B0E6ULL, 
            0xA1CE7793B9313770ULL, 0xF66E847C54305648ULL, 0xEAE62C1D27CA0DA7ULL, 0x1295192A2611F215ULL, 
            0x750AFE2B881BA6D0ULL, 0xBDA28ED82849D339ULL, 0x50DC241818853225ULL, 0x809FB12092E91417ULL, 
            0x73ACFEAA046ECFDBULL, 0x78E78C1BD8F43686ULL, 0x8294221427EBCEECULL, 0x5FF7BC710BE74526ULL, 
            0xE9F2ECF143CA27A1ULL, 0xAAC4F074E9688D3AULL, 0xFC894EA5573E6B0DULL, 0xCFB3BFF3EBCF7267ULL, 
            0xFD2D8929776558A9ULL, 0x8C55986D5E275A86ULL, 0x04D93D135E8886DDULL, 0x59D220640E5D8003ULL
        },
        {
            0xC54BAF0973B66718ULL, 0x9358223C632CC105ULL, 0x94014A4BEE8B3FDBULL, 0x84B0CE375DECF2C0ULL, 
            0x1826B86C23D3FB59ULL, 0xBA47FF73B076EEF0ULL, 0x9E2F9A7C2C5F65DBULL, 0xBD6801A4453211EDULL, 
            0xD910CCAB0E8FAAB6ULL, 0x48E764522EF803DCULL, 0x43C94F042136F7EBULL, 0xB4E49ACFD6D0B5D9ULL, 
            0x158E88A349CB1C95ULL, 0x5AA0B3EFD58E4D2CULL, 0xF02020259DB1D9BBULL, 0x1CD93535F0CE6903ULL, 
            0x471CEBA2D506B2B6ULL, 0x77C8FCEB63A017CFULL, 0x08F46DF8EC2F9CF7ULL, 0xB981A2C89F9D46C2ULL, 
            0x8C499D1097265EADULL, 0xEB54BBBE7EAD341EULL, 0x47779A6E2E16235BULL, 0xE56605F6F2555D72ULL, 
            0x2C5F6F2E4EE04F0CULL, 0xBF96B52421DD8778ULL, 0xC31B7B0E4B88EAEDULL, 0x45873C9752861454ULL, 
            0x252257CE49C3FBAAULL, 0x068AA445D5322510ULL, 0x2DA62D28013F64C7ULL, 0xA651A7E530D4541FULL
        },
        {
            0xF648FEA54D6EDAE6ULL, 0x3E179DC14D8C4710ULL, 0x476BF98D6874BB9EULL, 0x2873691B4594F64EULL, 
            0x3971165ECAAD2E1BULL, 0x5D4700C245077D80ULL, 0xE252E4D4DFBCF0E8ULL, 0x2A8296E3788FC210ULL, 
            0x9E71F903441E9E2FULL, 0xADC895045B6E324CULL, 0xD24095006FB375A8ULL, 0x97B25AC2C8DE6A4DULL, 
            0x03BB675687821248ULL, 0xFB5FAC0939598A55ULL, 0xDBCE341F4BFD3831ULL, 0xA602CB83240B61DEULL, 
            0x67046383AE42F472ULL, 0x3FE919E6CCD5C8BFULL, 0xCA03068A9E9E7A2AULL, 0x6E81627C7A584EF1ULL, 
            0x3312923842995D66ULL, 0xA27096E1442B6C06ULL, 0x7FE9FBEA0E41A371ULL, 0x644EA759AFA313DDULL, 
            0x23DA3DC5C9F7E4FCULL, 0x428D28EA84FDBA57ULL, 0x9700D07E2047F3CAULL, 0x8666904EDF3F45D2ULL, 
            0xE29B41DBEB61543DULL, 0xCCF3911C2AB0ED82ULL, 0xC9307F5DA4F37A58ULL, 0x394823CDB20C7786ULL
        },
        {
            0xABF928DE107787FCULL, 0x5B09B22F997C45A1ULL, 0x7A2DAF1932E0FD7CULL, 0x378DEB9F8B886E34ULL, 
            0x7CF59D43658FB855ULL, 0xBDD81037923E0533ULL, 0x65E233D3670A9D94ULL, 0x34484BD0B33D05E2ULL, 
            0x02693FB190CEAF1AULL, 0x23A062EBAF3FDC88ULL, 0xE25362E5C0079F1BULL, 0x18F6F5DC8299D511ULL, 
            0x95A215D744C0C758ULL, 0xA36DF5E6B617A391ULL, 0x75893B46F8A8AB60ULL, 0xF4F95505DAAFDE58ULL, 
            0xDBE4667E669EF8E1ULL, 0xFB47659AFE14A372ULL, 0x3A9E7ECF34D6B474ULL, 0xDF67BEAF501671E4ULL, 
            0x4F166062B0CDC90CULL, 0x38201A1F5CD73D92ULL, 0x6482069327B27FC5ULL, 0xB96CC3612D591A59ULL, 
            0x1FD797E47FF88ACDULL, 0x3DBDFC8F75275727ULL, 0xA9EE8B49D95CEC34ULL, 0xE120513DDD196F06ULL, 
            0xE92F9B17CBF85CABULL, 0x7775AD0A2DAC85ABULL, 0x01B667E8ACBBE41DULL, 0x6ABD6E3F9EA03765ULL
        },
        {
            0xD039E50EE363AD2CULL, 0x18D03D7C110540F2ULL, 0xE88D72672A3B6FBAULL, 0xDC2C10042B67F13BULL, 
            0xF3706EB1ADCDAFBDULL, 0x3A59008AE9090E00ULL, 0x82EAAD46DD3CED7CULL, 0x9E1B0223D1D58213ULL, 
            0x1F2925C9FB172667ULL, 0xC20422873C4A7CB0ULL, 0x82A0A838C20840B1ULL, 0x5BD98EB64F8C035CULL, 
            0x4005CBE0F48376EFULL, 0x9DE967BFA2F48B45ULL, 0x0BE0D7DA1893763CULL, 0xED30A4744D96A26EULL, 
            0x9876A235D7ECED15ULL, 0xF9B22BF149EB3FE2ULL, 0x2292CEDCD230BB15ULL, 0xF0A97CA744CC286DULL, 
            0xF7D591C3CE026B19ULL, 0xA2353B2B6D45D2A4ULL, 0xBB7737ADF4656629ULL, 0x611CA0FE6CDC6C70ULL, 
            0xDA915C1F6441E889ULL, 0x695C86A155D6CBF5ULL, 0x1CCAF817E736FC3FULL, 0x169C6A77E2C3B060ULL, 
            0x365B1B6D03789931ULL, 0x8DBEA720BFB62EF6ULL, 0x60558B44AE9023C9ULL, 0x381EA0FE49D82725ULL
        },
        {
            0x8437FF709CF4267BULL, 0xA03E4C0865FBD9D3ULL, 0x430E6A7805AFDB17ULL, 0x9C5BC32A0AFB4BCBULL, 
            0xE94501D4F1499D72ULL, 0x0758F8F1B4911326ULL, 0xA1B04493676A01D5ULL, 0x9F9DA9AEFF5E45CAULL, 
            0x05598A7321A19FA9ULL, 0xA1EADDA2BA1C0CB8ULL, 0x4E4B2A53303D25D3ULL, 0x2D6673991FF52CA2ULL, 
            0x709C4D4F8393FC01ULL, 0xD4518FA38BD1A40CULL, 0xE9017B206A262B75ULL, 0xE9E8E39130BCFD92ULL, 
            0x3F58E5A0B1758971ULL, 0x9758D9E7876ED27AULL, 0x6B33E9B27DD03FCCULL, 0x658956262D5B8587ULL, 
            0xF50146DD975D21A2ULL, 0xAE47F6F92BC827D5ULL, 0x9B33F3DB31C21D63ULL, 0xE8FF740CA4219A8EULL, 
            0xBB6431B6F0A67CE7ULL, 0xC918F8A62C62F81BULL, 0x2F96FB6E1517E056ULL, 0x09EFC26BF3E9A928ULL, 
            0x068035FCAF764A21ULL, 0x6897930C749DEA18ULL, 0x7C11308217C907E8ULL, 0xA8726880305D6903ULL
        }
    },
    {
        {
            0x0C664CC9554C3ECDULL, 0x755B044400EA1EA2ULL, 0x340C2888769DEC9AULL, 0xC5EEF39AD3AB5631ULL, 
            0x9CE67BA5A6EE7158ULL, 0x38A700B68E527CD1ULL, 0x5729BFCD7EBB48C7ULL, 0xD33590C23658EEDEULL, 
            0x7259C68EA2889D07ULL, 0xE67E8AD2C0B642F6ULL, 0xC68C2662A491D60DULL, 0x6B5BADD606B95086ULL, 
            0x35010230995E5477ULL, 0xAE229B46AFC11E5FULL, 0x5184D10D12B05110ULL, 0x658FDE8174ECED02ULL, 
            0x5FF7A016BA1D2E26ULL, 0xADB9F3988399F337ULL, 0x165921DCB691C25BULL, 0x6486916AEB4D185EULL, 
            0x4739A8BCE2EC306BULL, 0xCF4AF72475A18490ULL, 0x7D78824646C18551ULL, 0xDE5897C63E9DD9B7ULL, 
            0xDF12C03CFAE1BA78ULL, 0x6AF64135D4B48A0BULL, 0xE99CDA1D6EF2B9E9ULL, 0xBA4F87FC789132D2ULL, 
            0xCC28222E2831918CULL, 0xA7C75DA4BBF69671ULL, 0x2D672159D75635B0ULL, 0x01380760E52C9340ULL
        },
        {
            0xB10FE35FFFADD0DDULL, 0xC412F277AEEE8F77ULL, 0x0C6D940930EA2784ULL, 0x8E7D3CA4094C7C5DULL, 
            0x8F64B0FDC44C3A1BULL, 0x68F36944A9BA08BBULL, 0xE6AA5B1BA243013EULL, 0xE35D26B67B67801DULL, 
            0xA989E66BFC4F16DAULL, 0x5C968DD27D8D2E79ULL, 0x06A1882E6CB63F7DULL, 0x87495F7484594036ULL, 
            0xE7C9FB84A7628A03ULL, 0x9E83A3B4C3ACBDC8ULL, 0x082EB99EA4D6E34EULL, 0xFA36AAFC7FD87B86ULL, 
            0xB7D9A12E5E113A5CULL, 0x5AD75D769E65ED74ULL, 0x557144231718E686ULL, 0xD3A7608DB5E999D7ULL, 
            0x82261EA4F233410EULL, 0xF5B9E186145F8DBEULL, 0x2E45398D05CD20ECULL, 0x7E1D886FDFF6DA20ULL, 
            0x065150022A6C0508ULL, 0xD8EBC4F1D170693FULL, 0xA31592B01647F9FEULL, 0x4896262A638B57D0ULL, 
            0x731F9919F8D40679ULL, 0xB6E28EF190F8CD54ULL, 0xAFA7EDA7A99F7794ULL, 0x4940D9106ABED03AULL
        },
        {
            0xBA795FBEA311A2EBULL, 0xDAC16C10C28A04EAULL, 0x1B1A7857BE4A9143ULL, 0xC7EA166C010ADA7BULL, 
            0x8EF8E5ADFA241B57ULL, 0xDF548DB812C1CE55ULL, 0x544EF83E5B88C1F4ULL, 0x7DCC79D6B97529DAULL, 
            0x3AB2569B7EE06365ULL, 0xD6377033A21C100EULL, 0xC6EC707F60B081E7ULL, 0x097D5057249831F3ULL, 
            0x437F612488E2F1A9ULL, 0xE4DB4A026FCACCBAULL, 0x3F1D8A1E183C83D7ULL, 0xEE5EFD51BE890C49ULL, 
            0xDA1CEAE621611CF7ULL, 0x9A29E6A108C358F3ULL, 0x768CA6A1B35CA95CULL, 0x46D6CE7D62D4BD80ULL, 
            0x7355BE483A3CC5A5ULL, 0x9788CA9B7F1301C3ULL, 0x7A0DF61A26A8935FULL, 0xCBC71B62E42E6EB0ULL, 
            0x984B98DBBE9C6D66ULL, 0x4F605B95E15D1076ULL, 0x17C3BBF7CA64E8B4ULL, 0x3D672610015418B5ULL, 
            0xF1DD10BFFE949FA3ULL, 0x9A2466E90079781EULL, 0x054796B41D01FB5FULL, 0x03CC766909AC4C97ULL
        },
        {
            0x1AC8B627D4DBD77BULL, 0x54D47AEE626CDFC6ULL, 0x1472D145C2E94457ULL, 0x8783FB95312B8D21ULL, 
            0xC42B6FF8B78B865EULL, 0x6D70B7350FF38909ULL, 0x475377D0226148D3ULL, 0xB96D40E132CEF9E1ULL, 
            0x4D7DBDB7931BA779ULL, 0x0CD9AD811C114BEEULL, 0xF614450F5A321F75ULL, 0x0401DC165970CE05ULL, 
            0x90BA92495469E714ULL, 0x991C3323061702D3ULL, 0x925AEB7F6F926F06ULL, 0x929811F65DCC7E54ULL, 
            0x808DAC1732AC9920ULL, 0x3AB87B63986260FDULL, 0x18F924BA234CF1C9ULL, 0xE52ECB495EAAF4E2ULL, 
            0x14F78ED002F2DF46ULL, 0x197D8DCAE4AE0AB6ULL, 0x30B62448F9CB71F3ULL, 0x4D1E548BB803E7CFULL, 
            0x2DF425598C3FCDA4ULL, 0x839E69879A3F6941ULL, 0xBFE9514B82C9F431ULL, 0x779D8ED1665DBBE5ULL, 
            0x0E83036C05768FF4ULL, 0xE285135DAAADCC40ULL, 0x04D330D4EEEA067EULL, 0x74B4906925D70199ULL
        },
        {
            0xA8F2AC165056EB1FULL, 0x0D3A845D3DA920F2ULL, 0x235FB1709217E07CULL, 0xB4964DB0EDF73019ULL, 
            0x54897812B55C8119ULL, 0xB53F0339A667ACF4ULL, 0x18AE9046DBFC58F7ULL, 0x9F9ECA320DD5AA0FULL, 
            0xED21AEB49A504EC2ULL, 0xB65EC1232F3D50CCULL, 0x2D00B7CC1033D8E0ULL, 0x41C17E6C68005F8FULL, 
            0xE3BFEB9BC80F2352ULL, 0x8B490FAE9E115059ULL, 0xAE048C23EF8DC92BULL, 0x98C10E210319991BULL, 
            0x021FFC9ADA1537EBULL, 0x6870F44196CA9FBCULL, 0xE39CE2EF2B0B7180ULL, 0x4B8DCAE5ED9210C1ULL, 
            0xA3BE18A5697F48B0ULL, 0xED7FAD5C03FD96A4ULL, 0xA51C4D76049AC06DULL, 0xFE21422AEA82752FULL, 
            0xB25D8AF13C9B15CFULL, 0x21CFC6A4F0C74479ULL, 0xC6AA1526D88F0EB4ULL, 0x0F5E06649B1C4143ULL, 
            0x71042F9CBB508823ULL, 0xD8EA5E7BD414DCF2ULL, 0xAA9FC9885700860BULL, 0x6CC31784FC049249ULL
        },
        {
            0x969A0ED9A3145205ULL, 0xC7F532B68D18DD87ULL, 0x3151BAD87F04E90CULL, 0xB8CEBDE7D8E01780ULL, 
            0x45C364B311557AF3ULL, 0x000F5F9D00DBCCD0ULL, 0xB06AE048B8A54C6FULL, 0xC9FB974F473ED549ULL, 
            0x40313A43AA150D24ULL, 0xEC7BFB9F5F797797ULL, 0x8D43B1444FD160F0ULL, 0xAD3375FBBF7ADBEDULL, 
            0x89C940AE357BDC4BULL, 0x3415494494E2CA77ULL, 0xB99A96F8BF483F53ULL, 0xBA8EAFA6E43F9DD7ULL, 
            0xFDEEA3B3E91C707EULL, 0x8692ACF36B0AD226ULL, 0x69861A271D23E3ACULL, 0x0E6D2FEC33C1A86FULL, 
            0x2DB627A96AA20583ULL, 0x205C068B555C0F9EULL, 0xFB6AAC06B2FBE679ULL, 0x5DC9BAFA60CFF046ULL, 
            0x57E961420FC5060AULL, 0x8544349395ABF6D8ULL, 0xC0F7E52CAC21A37EULL, 0x78F81D1699E0CE69ULL, 
            0x1569F095D509746FULL, 0x5FAA4E272D8C4EA5ULL, 0xB66063C0458B5943ULL, 0xC67C705FC72EB16DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Capella::kPhaseHConstants = {
    0x6EB811B1F64EA10EULL,
    0xF8E7F2935E5090E4ULL,
    0xF2ECBF4A272DAE30ULL,
    0x6EB811B1F64EA10EULL,
    0xF8E7F2935E5090E4ULL,
    0xF2ECBF4A272DAE30ULL,
    0x7AC477D24123F559ULL,
    0x9BD51E9BF5809458ULL,
    0x99,
    0x9B,
    0xC4,
    0x9E,
    0x0A,
    0xE7,
    0x70,
    0x1B
};

