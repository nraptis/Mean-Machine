#include "TwistExpander_Castor.hpp"
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

TwistExpander_Castor::TwistExpander_Castor()
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

void TwistExpander_Castor::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB621A04CE34A3506ULL; std::uint64_t aIngress = 0xB577AC79FF10EA1BULL; std::uint64_t aCarry = 0xBE10FD1BCDFCED0AULL;

    std::uint64_t aWandererA = 0x849A1D7123E34DCEULL; std::uint64_t aWandererB = 0xEB84A992F6691E18ULL; std::uint64_t aWandererC = 0xF841B0424013560DULL; std::uint64_t aWandererD = 0xEDAA23F5DB684BEEULL;
    std::uint64_t aWandererE = 0x8E80D6AA2CDE45E0ULL; std::uint64_t aWandererF = 0xBA1ECF5592FF4DE4ULL; std::uint64_t aWandererG = 0x9A81987FF6C0EE36ULL; std::uint64_t aWandererH = 0xE91CD0DB8DDFAFD8ULL;
    std::uint64_t aWandererI = 0xB235EED234BEBEF2ULL; std::uint64_t aWandererJ = 0xAD2AFB7D9F23B3F3ULL; std::uint64_t aWandererK = 0xB80524D9B19BCE73ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14214082691657394947U;
        aCarry = 16238092025459952206U;
        aWandererA = 16798809414173029861U;
        aWandererB = 10822122366469817058U;
        aWandererC = 16141992629126826277U;
        aWandererD = 14068138624047970185U;
        aWandererE = 12603583944440328005U;
        aWandererF = 15735932263418841825U;
        aWandererG = 16164765899042028896U;
        aWandererH = 13448762933025022642U;
        aWandererI = 15375905873870196169U;
        aWandererJ = 15628487949888696158U;
        aWandererK = 9627856348254286197U;
    TwistExpander_Castor_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Castor::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x914D6243DD557A6DULL; std::uint64_t aIngress = 0xB407CFEE0BC1840FULL; std::uint64_t aCarry = 0xEAD8AB3632C588F6ULL;

    std::uint64_t aWandererA = 0xF237746D9443C1DBULL; std::uint64_t aWandererB = 0xDCCFE439C8569B01ULL; std::uint64_t aWandererC = 0xD4D0D043602A4FD5ULL; std::uint64_t aWandererD = 0xCBA23CE3F49ACD9BULL;
    std::uint64_t aWandererE = 0xA6DB385B90D1AA06ULL; std::uint64_t aWandererF = 0xB24B87383C17C02BULL; std::uint64_t aWandererG = 0x9AFCAB39A8E7BC15ULL; std::uint64_t aWandererH = 0xC28AA4882932E2C8ULL;
    std::uint64_t aWandererI = 0xCFA57A7F48A0B841ULL; std::uint64_t aWandererJ = 0xDE883AE6733C5826ULL; std::uint64_t aWandererK = 0x9F901FB884DD6B24ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11981921891182319573U;
        aCarry = 9320575732278270852U;
        aWandererA = 12115396455865374938U;
        aWandererB = 16010897992419381313U;
        aWandererC = 15669932286196374425U;
        aWandererD = 17855760760885426136U;
        aWandererE = 14761871873543907724U;
        aWandererF = 18273161131882336663U;
        aWandererG = 12569555518646152452U;
        aWandererH = 16342824256433549225U;
        aWandererI = 12884570949403060046U;
        aWandererJ = 13184432373583935657U;
        aWandererK = 17113670817692293703U;
    TwistExpander_Castor_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Castor::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x89B3C3A6CD5569A9ULL;
    std::uint64_t aIngress = 0xB6C2195AFF09E532ULL;
    std::uint64_t aCarry = 0xF133BAF442246AEBULL;

    std::uint64_t aWandererA = 0xC018C4563A0F43B5ULL;
    std::uint64_t aWandererB = 0x8A5DC82023FBFAC8ULL;
    std::uint64_t aWandererC = 0xB77D1FB4A36916F7ULL;
    std::uint64_t aWandererD = 0xA76D9CC78936FA8DULL;
    std::uint64_t aWandererE = 0xD69E297EF2C0FF4EULL;
    std::uint64_t aWandererF = 0x9A0EE065B31D4068ULL;
    std::uint64_t aWandererG = 0xEFEA9ED730D9DB16ULL;
    std::uint64_t aWandererH = 0x9BD3D1FF1EB37CFDULL;
    std::uint64_t aWandererI = 0x91395B703BDA316EULL;
    std::uint64_t aWandererJ = 0xDB04403F0EE2BEBCULL;
    std::uint64_t aWandererK = 0xF19745E44B72855EULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
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
        TwistSquash::SquashA(aExpandLaneA, aExpandLaneB, aExpandLaneC, aExpandLaneD, aInvestLaneF);
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
    TwistExpander_Castor_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Castor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Castor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 16 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1827 / 1984 (92.09%)
// Total distance from earlier candidates: 27815
void TwistExpander_Castor::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 744U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2014U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1430U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 52U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1227U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1137U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 685U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 398U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1084U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 64U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 739U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1176U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1820U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 343U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 18U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 387U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 140U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 670U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 24U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1693U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 295U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1624U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 257U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1981U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 274U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 291U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1055U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1608U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1818U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1988U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 864U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 657U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1556U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1462U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 230U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1643U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 304U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 424U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 933U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1726U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1734U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1740U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 60U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 589U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1319U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1962U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1286U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 336U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 5U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1135U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 828U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1272U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1910U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1035U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2011U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 796U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1500U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 773U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 44U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2007U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1331U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1931U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1082U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1574U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 197U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1252U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2024U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 706U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 3U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 158U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1772U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 188U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 972U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 603U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 233U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1906U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 477U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1148U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 472U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 338U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 651U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1954U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 640U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2032U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1410U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 789U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1143U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 783U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 812U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 593U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 754U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1600U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2029U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1194U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1122U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 36U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1898U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 193U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 652U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1957U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 169U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 27U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 199U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1229U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 725U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 204U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1315U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1423U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 702U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 767U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1506U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1239U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 831U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2027U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 134U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 751U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1953U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 786U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1975U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 770U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1948U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1815U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Castor::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8742CD22FFDF9871ULL; std::uint64_t aIngress = 0x91DE8CA67C02A966ULL; std::uint64_t aCarry = 0x83DDEAFDF090A496ULL;

    std::uint64_t aWandererA = 0xC8D6790ABC221BE7ULL; std::uint64_t aWandererB = 0xCDF1A765230F2974ULL; std::uint64_t aWandererC = 0xC2AF00CCE31C0B09ULL; std::uint64_t aWandererD = 0xC875403D55E58217ULL;
    std::uint64_t aWandererE = 0xC67B823FD196425AULL; std::uint64_t aWandererF = 0xEE5F4CD1AF0951ACULL; std::uint64_t aWandererG = 0xE546E3E311268BCCULL; std::uint64_t aWandererH = 0xA1073B78C47502B2ULL;
    std::uint64_t aWandererI = 0x8FC34313878CC4C2ULL; std::uint64_t aWandererJ = 0xD3AA7E716B548FFDULL; std::uint64_t aWandererK = 0x8E9D312C8414D5F6ULL;

    // [seed]
        aPrevious = 17718757237652265542U;
        aCarry = 13413509715350917493U;
        aWandererA = 12013567894418672705U;
        aWandererB = 12346872541300567516U;
        aWandererC = 17101241835285272469U;
        aWandererD = 10256772542759034627U;
        aWandererE = 17016408951546655762U;
        aWandererF = 12376090052053457939U;
        aWandererG = 10664851761588602288U;
        aWandererH = 14716974001594477321U;
        aWandererI = 9724212102575465014U;
        aWandererJ = 10034349997038047514U;
        aWandererK = 16196981321883109631U;
    TwistExpander_Castor_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Castor_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Castor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Castor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 16 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8207; nearest pair: 515 / 674
void TwistExpander_Castor::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4733U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6947U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2120U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8143U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6712U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6603U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7473U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6962U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4735U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6160U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6172U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3086U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2965U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7724U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7709U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5628U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1653U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 513U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1835U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 820U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 339U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 22U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 485U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1839U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 200U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1679U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 73U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1178U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1884U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1347U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1060U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 746U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1284U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 163U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 947U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 702U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 16 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8225; nearest pair: 502 / 674
void TwistExpander_Castor::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4990U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1232U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7442U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4652U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5630U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6760U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5025U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2783U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 543U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5470U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6611U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7289U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3268U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1416U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4107U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 269U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 281U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 185U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1964U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1756U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1580U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1745U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 568U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 837U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1181U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1363U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1958U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1091U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1647U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1987U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1872U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 315U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 513U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1490U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 903U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Castor::kPhaseASalts = {
    {
        {
            0x76639017A2215D36ULL, 0x50394E14ACB117E5ULL, 0x9EE86D922AE9CE19ULL, 0xC1877B391C178C28ULL, 
            0x140646821FD459CCULL, 0xC05EBB09E9093DC2ULL, 0xC9278803841244E9ULL, 0x4CB97CBB751625C5ULL, 
            0x8CFE0BA3DCF88096ULL, 0xCA84102B31ABC662ULL, 0x8ECD52E493B01584ULL, 0xC1D529E236256D12ULL, 
            0x947B87E33627311FULL, 0x3C59C71F5719AA3AULL, 0x60AD56B7B3F79BCFULL, 0x953CF2CA801380E6ULL, 
            0xC963790B0B99CB45ULL, 0x39F404362D7B3233ULL, 0x01283738CE76DA1BULL, 0x46D2BFAF247AAA48ULL, 
            0x2DA8C6946208606DULL, 0x5DC277FCBBCC6C48ULL, 0x0BDBBA0876C80A41ULL, 0x8ADD23BC1648041AULL, 
            0xB3875AC06DA09FE5ULL, 0xD2B998FFAADAD883ULL, 0x8CADD2E6260AFF31ULL, 0x498F1A1EF32FA10CULL, 
            0xBC90445324CFF2DAULL, 0xD3F192B9CACC0B0CULL, 0x0E8B87521D675845ULL, 0x947DB441194AD597ULL
        },
        {
            0xF94CD3141A5B0821ULL, 0xA249AE6FFBD62B43ULL, 0x809FB4EDFC32CB3CULL, 0x247FAB9A501E3338ULL, 
            0x378FB78C1926407AULL, 0x756DA421CA78B036ULL, 0xBFF81072C6F0BEE7ULL, 0x5715D9E9B6030861ULL, 
            0x202D40BBE3F14C5EULL, 0x51441641C2F2CDE7ULL, 0xC5796F7FF10FC50AULL, 0x78E46A573B993BA1ULL, 
            0x0002D83F8C69752CULL, 0xA89FFA00829B66AAULL, 0x25031F8A62462881ULL, 0x39ED057DAF2746ECULL, 
            0xE918AEBE371B183DULL, 0xED1B850D3D578B63ULL, 0x5087C80540663E17ULL, 0x19ECD11BCC5F7A0EULL, 
            0xF26F89B48D466978ULL, 0x16C17FCC1BA2E607ULL, 0xC01E32B7DBEBC801ULL, 0x77EA85750336CA69ULL, 
            0xD5B99D88F1EE0DC0ULL, 0x6C3EB486C9809C92ULL, 0xB17831C379F697C5ULL, 0xFFD9080E7C387500ULL, 
            0xC6DCD19F55D1F6E3ULL, 0xD9F9C02EEDE2D98FULL, 0xF82CF9D0F5BA88A3ULL, 0x7EC9791DF4D831CCULL
        },
        {
            0x6A7FFEA197E7AA83ULL, 0xE179AA206CCA5095ULL, 0x52653F1218EAA094ULL, 0x778BDCE8DA09BBC4ULL, 
            0x59FFD7060B30F303ULL, 0x4E5DDD63350357D6ULL, 0x264BAE516921D6D7ULL, 0x622CA899972FFBE4ULL, 
            0x336365C62773D014ULL, 0x8A904E9947D82557ULL, 0x2F09AD1FEDE50C60ULL, 0xD41739E0C1C34A67ULL, 
            0x39D4DD04FDC7500AULL, 0x1E20F734D05EE3A9ULL, 0xEED73BF2153D34FBULL, 0x5EF97E99510DD570ULL, 
            0xB15C9506ED402ADFULL, 0x18E189C8EE3FD42FULL, 0x6CC09506F83090E4ULL, 0xD6E02092903D6392ULL, 
            0x546AAC382554373DULL, 0xF3A5584936E4234AULL, 0x0094EB4146E9EB09ULL, 0x6426D09121AE8F43ULL, 
            0xB448056C5542D6D2ULL, 0xFFE5C4BA81CD0B3EULL, 0xAC60F465888362B4ULL, 0xA69434FDC5F848AEULL, 
            0x97EF390DCC182461ULL, 0x5C1B3F852D736D62ULL, 0xF542C28D6D3D6124ULL, 0xCB5661B8171D4861ULL
        },
        {
            0x016FB6716387784EULL, 0x98E75BC6A5F5D05DULL, 0x465B1BE1CEEEE3AAULL, 0xD0E0602E5CD10587ULL, 
            0xDD15F1F66A616C29ULL, 0x0966B7447C305302ULL, 0xBF3D04EF36C84E72ULL, 0x70F757B20C30038EULL, 
            0x79DD0507F6250832ULL, 0xA9BA33912B11A7FFULL, 0x61365F3840ED12C1ULL, 0x84AE231D4188A282ULL, 
            0x65ACA031305AFB5BULL, 0xF58F99F3F7C86406ULL, 0x8B07152932F2FB63ULL, 0x67C7197D46637DB1ULL, 
            0xD9E42BD7EC48FAAEULL, 0x9B1FEED75750106CULL, 0x80CEA2CC89411A8FULL, 0x6DD02DB9129E5A2BULL, 
            0x36F42396BC12C5CCULL, 0x56590AC9521A37EEULL, 0xFACE786FC63571CCULL, 0x78A793187EAEF154ULL, 
            0x8695A2F2C84367E8ULL, 0xF34559EA10F8AD4AULL, 0x342D698B09DD8447ULL, 0x6F3C47D78702469CULL, 
            0x82A11649DEE280B6ULL, 0xCE8FCC8FDC59F084ULL, 0x8EAB7990FCD03D4AULL, 0x9CE2A58013DF88BAULL
        },
        {
            0x00197188A48763F8ULL, 0xE200C1F3173021D4ULL, 0x2C966CBC2BF24D3DULL, 0x9CFA9A489E4DA6B7ULL, 
            0x3A4C3E660505AEC6ULL, 0x77068885C45B7210ULL, 0xE30AD9607194B7F3ULL, 0x451CEF206BAF1811ULL, 
            0xCF57CDFE33A14CE2ULL, 0xE786F09C17F5186BULL, 0x51C7AF1D8ED17B7FULL, 0xDD11E787F6132013ULL, 
            0xC8E23086662627AEULL, 0x0BAD4C412D101D61ULL, 0x1E68A7973ACD3293ULL, 0x94A8592CD94DF12EULL, 
            0xD6459FAEA3C9601CULL, 0x91A9E4855A7D8D31ULL, 0x8C88F88D9B6A0009ULL, 0x3E5DC9E5538928D1ULL, 
            0x2C5B9E1BE4ADA15DULL, 0x75D9DBDD4856AD41ULL, 0xE73F993AA8E1DD97ULL, 0x541AEBBB90D4F9A2ULL, 
            0x420274A617006AACULL, 0x961975534138DD8BULL, 0x342BF9098C85CD9AULL, 0x2DAC75D1EA339B7CULL, 
            0x4E9E09D11804B00BULL, 0x3C6AB2C111D8B330ULL, 0x9FA046066AB9CB50ULL, 0xC73DBC65F2110C04ULL
        },
        {
            0x68BB6B28AEF5CB8FULL, 0xBF77E65DF45EE55FULL, 0xCAF76B9A8E70B93CULL, 0xE961126EE9191BCFULL, 
            0x8C86202B63FA3E76ULL, 0x9E5EDDD20E2AFE83ULL, 0x2462939E3CCCB03BULL, 0x081CE0458EBE05DCULL, 
            0xB6CF53CE01583E0CULL, 0x648409AD442AF88FULL, 0x0007A7F4544588C5ULL, 0xDE2F11A6CC0DBFC2ULL, 
            0xA2F6022FF20441B1ULL, 0xE373E77088438FEBULL, 0x350C6A09B5C3370FULL, 0x43F82F41CDA77390ULL, 
            0xC1E8325F2DD10756ULL, 0x8760EE213592E2ACULL, 0x84E9A1FD3DE7FF97ULL, 0xF25C14A927D2E562ULL, 
            0x446C2A6E37330410ULL, 0xF84B84F82C1FBEB6ULL, 0x2C2373AB2069F07BULL, 0x862EAE70F69C5631ULL, 
            0x05A24A3223F995EDULL, 0x151E9F4ACAA3A4D7ULL, 0xF8D77CAA07676341ULL, 0x4DCAA31DE099BF6CULL, 
            0x8F945100D2A8720BULL, 0x841C36850DE9D89EULL, 0x1F8F9B1A90AEA406ULL, 0x89EBDD93897A45E3ULL
        }
    },
    {
        {
            0x7202B1E1AD9985FBULL, 0xB1519C795861D8D5ULL, 0xF1A3F3548D998E4DULL, 0x544AB8C1261C7F17ULL, 
            0xF7CD1918552C88E6ULL, 0x1BAA59DA0A68C68CULL, 0x942F111B3943564CULL, 0x343B352F2FEC721AULL, 
            0x8AB032912561C2A9ULL, 0xA979677AC44587D4ULL, 0xEA738A373F421265ULL, 0xD76EC9977A748224ULL, 
            0x5D62A135A0CA8ECEULL, 0xF6FBC5A86F31CB5CULL, 0x40129E5EDB1B45E6ULL, 0xE84B0079E6DD5F99ULL, 
            0x272E97E204DF7EDAULL, 0x20A09174BA9D088AULL, 0x8FC8A17E4CDF5E10ULL, 0x7D2629FF32E0C7F0ULL, 
            0x8E9695A1A87E1EF2ULL, 0xDD372F5E1FEA8360ULL, 0x2FA1D4F56C1C0C70ULL, 0x6B69DC8F041F880FULL, 
            0x24B0D927C2437481ULL, 0xAD091E2DE535760AULL, 0xDDB5F4EBBDD67114ULL, 0x43D093B6B7573C7CULL, 
            0x01C96F276783B5B4ULL, 0x39654BF5B3949C13ULL, 0xF98AB3944AC06B27ULL, 0x21D063DB02F9749BULL
        },
        {
            0xEAC9DE99F159997CULL, 0x69C388D15DAB2A41ULL, 0xD29469B18C08153DULL, 0x47236FE466A53FD6ULL, 
            0xAAB4AEEB00286E43ULL, 0x4775795099815A78ULL, 0x2C699B89B4351972ULL, 0xCECDE03D90178519ULL, 
            0x2FCABBA14344D0A0ULL, 0x0D5490F792876690ULL, 0xA9683B12E3926E33ULL, 0x961B8D5C58033C81ULL, 
            0x143C1D81EE93B64BULL, 0xA1254167177F713BULL, 0x6E8A6C1CB28475E3ULL, 0x327F2001ED778F4DULL, 
            0x326DB5C8CFA43367ULL, 0xC884606479818393ULL, 0xA711A5E5DE29A69DULL, 0xFFCEA49160E3F88AULL, 
            0x792B4F86B27FEC09ULL, 0xED703372E0C2DD8BULL, 0x788BE8B6EE37BA7AULL, 0x82EF72395BE011FCULL, 
            0xDAE22FF67116EBEDULL, 0xAA6198A8429ADE5AULL, 0xCE9AA304D7E10CFCULL, 0x42E8F1BB3CCB504DULL, 
            0xE6F1C5E971C0BD88ULL, 0x5149C4601E568226ULL, 0x4BB287E3B1350F7BULL, 0x4723DA8EE45AFB4BULL
        },
        {
            0x43928BA3F32E01F8ULL, 0xCBAEA745728E34C3ULL, 0xD5DAFCD9BCA84AE7ULL, 0xA0AE8D3E38C95F6DULL, 
            0x0D1DA4615A541AA0ULL, 0xE665CB876F74E8BEULL, 0x000BDB6150D8CE36ULL, 0xC58D90DFD8CB3F66ULL, 
            0x87AA0C1EA8A8A8BCULL, 0x0ADE4678002C1B98ULL, 0x5EA115ECCC2752B5ULL, 0x12D1AA40FA6930C8ULL, 
            0x6E440ADFC119AA54ULL, 0x2DEB6366EAA99589ULL, 0x05D6A7B69B04AD3FULL, 0x4FF525AB338B59E2ULL, 
            0x6031C62B9A8C0AE7ULL, 0x5F55D0ACB4B11A98ULL, 0xA9E38E4294733194ULL, 0x409370A1A7817508ULL, 
            0xA77DA047E222C3A3ULL, 0xD080BB2A0A3FDA80ULL, 0x01B94D3140296161ULL, 0xD3C426C005A361E7ULL, 
            0xE8C44F496CC439A1ULL, 0x2392DBA516A2C5D5ULL, 0xBFA633730D33C853ULL, 0x064417005E27DC80ULL, 
            0xB528E288A27711D2ULL, 0xD29511302DD87FA5ULL, 0xB1AEC126B904AFABULL, 0x9E76C569F2FA4775ULL
        },
        {
            0x54EC57D04004F245ULL, 0xFBC14B762540B2DEULL, 0x12925A14E1D6747DULL, 0x2943D5CA4EBF7B1EULL, 
            0xD2ADDEB3B286B7A4ULL, 0xF8F49A3FA0CE38BDULL, 0xF3DDE977F9BB248EULL, 0x1903A91D085E21B7ULL, 
            0x9E94ACE247187D03ULL, 0x99AD2ED488631620ULL, 0xA85319D019A5E7BCULL, 0x855DEDB990135813ULL, 
            0x04419309596A3DCBULL, 0xBA5F62DF85F428A2ULL, 0xC3F29CD29C708911ULL, 0x7A6E46C6C0166614ULL, 
            0x32879E35D199AB80ULL, 0x39333233D21BC989ULL, 0xB7D2E0F699869091ULL, 0x7361A42F0F20A6EDULL, 
            0x3DA303C9056DC869ULL, 0x8D5D8ECE119CDE87ULL, 0xBAD2D6B7521521F6ULL, 0x6F008FFA30AE9EA6ULL, 
            0x9A9E878528704E64ULL, 0x533C708C34D33908ULL, 0xAC487486ADD4FAB1ULL, 0x90250F81BA1065E7ULL, 
            0xD8BFBC50FAA287CDULL, 0x214437AFE4809099ULL, 0xC808F9482E220AEFULL, 0xF3BF7F34DCE10BB0ULL
        },
        {
            0x0AD5341635D5BFD4ULL, 0xB18154AE89D8DC51ULL, 0x4A44653533E87248ULL, 0xD51090404E31F09FULL, 
            0x18A2C012B32DFB91ULL, 0x3A2F6B4EE0387221ULL, 0xACF9D306DF95F7B0ULL, 0x376F030BF43EDE22ULL, 
            0x516460D1B2DF1951ULL, 0xFE7CA64D6292783DULL, 0xCC40F7210B832E3DULL, 0x5BD81CFBFCEAFD63ULL, 
            0x96702853A1F28F1DULL, 0x51E8EBD8CE8E25FAULL, 0x7306BB56FCBD4DC0ULL, 0x0D06B8990F977EF0ULL, 
            0xA920FF469DCBE871ULL, 0x191715C312C59295ULL, 0x560EEEE0B8AB73A5ULL, 0xF23D44C247330981ULL, 
            0x0CC2D15F367553DAULL, 0xB3DBBD035679F160ULL, 0x43EB9C2F7AA1CC16ULL, 0xFFF9DB64BC2A9D38ULL, 
            0x5430D8AD7C38E573ULL, 0xE619AE2659C1E11DULL, 0xCC704B48FDD5FF53ULL, 0x13151465FBE2B306ULL, 
            0x31F0C4EFD13A5AA4ULL, 0x679DC791D6B5AA82ULL, 0x2A0A19A865839DE8ULL, 0x39F8DE81350714A3ULL
        },
        {
            0x5E8C484E67401524ULL, 0xB9DA6F7735F7B1D4ULL, 0x1946C425615E40C4ULL, 0x511CF2D6B832C753ULL, 
            0xE2AAD07D9593888FULL, 0x8FE37D7F033F2EDAULL, 0x5CBC6820F4E9B66FULL, 0x0F1B4BCE1CFCEFCBULL, 
            0x12F6AF05AFCDFFEFULL, 0x0602659F21065168ULL, 0x44C8896B24B0D80BULL, 0x2C169ED25BB21258ULL, 
            0x3A85CE5A3A3D5A8AULL, 0xAA72AE93B024C0D3ULL, 0x76B9E32C021129DFULL, 0x58269D53791FD240ULL, 
            0xA9901E37934BDA7EULL, 0x155A710109B7908AULL, 0xFD90C074A78D548FULL, 0x2A5F57D45ECE9E52ULL, 
            0x8F2034C6CB1E30D4ULL, 0x84D0F763BA45B8B9ULL, 0xF4C1B6016049E0AFULL, 0x9E6E0F6133576D86ULL, 
            0xE7D673E474248CC7ULL, 0x098FA5F412DD6F50ULL, 0x284B1CB6B6B6BA41ULL, 0x33CFE1F34290EC2BULL, 
            0xD0F1D8D5BE882049ULL, 0xD468FDF6833D4636ULL, 0x11A17DFB60AA1142ULL, 0x68031986E82B2D64ULL
        }
    },
    {
        {
            0xF22EBACA477D7BD7ULL, 0x064DBADA577B86EBULL, 0xEA36A532ECBC2D32ULL, 0x09AA760E7C602A14ULL, 
            0xEAFFB39894F17290ULL, 0xC982A9D6E018826BULL, 0xA76507926D14DB89ULL, 0x8D971C2AF8EC3C28ULL, 
            0x0478728474060F2AULL, 0x45C4D8812DE1B914ULL, 0x9F4E3E0F319E64DEULL, 0x966C73E8B51CFFC3ULL, 
            0x0120F8D15CD7D0CAULL, 0xF74A94379420192FULL, 0x3F50323F253D3820ULL, 0x2A181C3295FE9C3BULL, 
            0xFDA21702D1E3B1CDULL, 0x32A50F69F8B6683CULL, 0x89E05CEE4DEF76AAULL, 0x59C142B8FD1B237AULL, 
            0x6FC549BCE2226327ULL, 0x6306A0A35ED5F872ULL, 0x8495973EE46EA237ULL, 0x96AD3A2D33F3CE3AULL, 
            0x1D79D871D29D4343ULL, 0x7C355275DCC6F87EULL, 0xF11A7FDD945363CCULL, 0xE076EDB132EDB377ULL, 
            0x9E7ADE8D31ED5686ULL, 0xE3A95D85E2A9FEBDULL, 0xEAB2547E3368746BULL, 0xB0FFA61EE0F7F27DULL
        },
        {
            0x7BF8DDBDE7A3F049ULL, 0xFE1A144020C79836ULL, 0xE5D7A23BBF0CABB5ULL, 0x3762413C555B4007ULL, 
            0xEA76DFD2FEF490BFULL, 0xDCCEDF1EBCAD797BULL, 0xD2E5247A00C9F2E6ULL, 0xC73CA12B32721DE5ULL, 
            0xC6EE5CDF9FCA0A59ULL, 0xC01A002D5EFABE35ULL, 0x63D33156805878FBULL, 0x56173FE8641DE168ULL, 
            0x2FE94E8900DCA12EULL, 0x02344A4225CC87C8ULL, 0x62F00942ACCAC81FULL, 0xF37A8CE3AF1A1F21ULL, 
            0x988E0634C5139294ULL, 0x3DCE3685228F4168ULL, 0x66A9ACAB394F6312ULL, 0x01C4C0D11375D8FCULL, 
            0x76F9DD1128BE3D42ULL, 0xC97BA25D2C45C70DULL, 0xB7CAE86413C29205ULL, 0xB2DCAB577BA55D9FULL, 
            0x1A46C4F86A9135E5ULL, 0x8EFE5D14B9C7D71DULL, 0x782D0064570B90FAULL, 0x44CD78D954B95CFEULL, 
            0x39E3D59E4374BD6CULL, 0xFE55B7025160A878ULL, 0xC2EF19DAA6BC24DEULL, 0xF19A71B41A1E7CF5ULL
        },
        {
            0x429B0DE1AE199208ULL, 0x386853D92397D9EAULL, 0x8C4F73F7957C3526ULL, 0x9D07AC9A993A9CBFULL, 
            0x74E7C4B0FF097027ULL, 0x78266EF870B2FC9BULL, 0x69AAA5B9CF0D7CD3ULL, 0xA0296428D023EA83ULL, 
            0x9FF7032FBBC578B3ULL, 0xAFE979BA1177BDCDULL, 0xE6B56DECABBB134EULL, 0xF393135174313DDBULL, 
            0x45D43D44D01E76C3ULL, 0x2402EAF98D473BB7ULL, 0x6F93B5E9BD5C1DE1ULL, 0x429AD2425D7C7885ULL, 
            0xF5814E766415F7BDULL, 0x6E9E4C1F0666F41FULL, 0xEB2C8B31D696FFABULL, 0xBB15878278C97893ULL, 
            0x9C39F3580A108A89ULL, 0xF2E81C0C59B121A4ULL, 0xD640937BF74337C7ULL, 0xE4FC98E2349F2727ULL, 
            0x48E2C7D0F2734135ULL, 0xF970BEC832FB106AULL, 0xA084DDB82B287683ULL, 0x9C614965FEB763A6ULL, 
            0x7E6CB92EDC78E7AEULL, 0xB79B56A647C90CDAULL, 0x08D29704CE3B7743ULL, 0xD214F2A41FBE6A65ULL
        },
        {
            0x20529BC4BF56FE54ULL, 0x9D829560B7031152ULL, 0xCB29C8FC17FB12D9ULL, 0xF558AA54379BA43FULL, 
            0x0EA2D6B44E04F2C5ULL, 0xEBDB552DCED497A8ULL, 0xC66D34C20EAF6201ULL, 0x74556BD27A076478ULL, 
            0x874C99B06475086EULL, 0x7A82F9F0F2C53EF1ULL, 0x7A1E9E8D53B88D4FULL, 0xCA0D46177E38377AULL, 
            0x0313F741C135B602ULL, 0xF83FE0E82A1E93E9ULL, 0xB17AB7CD937E33EAULL, 0xCD1B0FF399ADE8D6ULL, 
            0xFA52A9193242D0C1ULL, 0xD7F55781C1190DC8ULL, 0x608C02C55CCBF2F0ULL, 0x43DEDF42BC4B7A76ULL, 
            0x7765688141CBDB25ULL, 0xF286BA202BB85637ULL, 0xBA8BBFFEFD2E363FULL, 0x9B87AF09FB12D028ULL, 
            0x0D072FA7933685B9ULL, 0xADB4C6F279AD56AAULL, 0xFE01D611BD1AC302ULL, 0x35F64E9E6892DB90ULL, 
            0xD64B221A80C0E16AULL, 0xA8077A212246AF90ULL, 0x76EC9E48E2A7530CULL, 0x6CFBC47FA909BCFEULL
        },
        {
            0x31A85470D6814A90ULL, 0x7E865CFCD93EE83FULL, 0xFA942804F948680FULL, 0x1D7DE458CADACFC2ULL, 
            0xA5F865DA83593204ULL, 0x125F9694954F00F8ULL, 0x06423D794FE2BDE0ULL, 0x637CF2F0F1818358ULL, 
            0x035B171E6A7A341FULL, 0xADF8C343CB3CE93CULL, 0x46B883BBAF9D37FDULL, 0x0DF1991F12C7BCA5ULL, 
            0xA56983A7D3F1286FULL, 0x5D78B4FB55543026ULL, 0xE48A79D3CE813367ULL, 0xDD909D865EA79252ULL, 
            0x52589EE8FA30741AULL, 0x640F1CA6DAD964E3ULL, 0x70C6DBB864D71516ULL, 0xA2E723B96CB08709ULL, 
            0xAEC3FA04B7D49BFEULL, 0x4150674E185869A9ULL, 0x55611511D4CA08A6ULL, 0x6EEAEF11E7AEB3D4ULL, 
            0xE91C3C039488DECBULL, 0x15FEED795618758CULL, 0xC66867054985771DULL, 0x953DB1768513BBA0ULL, 
            0x5A8B4484007F4EE4ULL, 0xDAE9AE95F760E618ULL, 0x42441900C862E374ULL, 0x1A8BE3F7EC927169ULL
        },
        {
            0xBF413833453A5736ULL, 0x377430DA9B6E659DULL, 0x60637782F99A21C4ULL, 0xF27F6AA717CCA94DULL, 
            0x94D41EDD0AFDF917ULL, 0xF905406712D26EF3ULL, 0x77A2898980BDB41BULL, 0x9CF75E4E4D27385BULL, 
            0xF6C78B96C7991D7EULL, 0xDC95558B38541157ULL, 0xEF526C93B605D33AULL, 0xD44954DE7A56F445ULL, 
            0x9F8C5B2D5C5A6ABBULL, 0xCD288F8E5E646BF0ULL, 0x64B1455991016B40ULL, 0x56088C9C2ABF3085ULL, 
            0x39AA1AD1C5A86CA3ULL, 0xAF6D9C1C35F49831ULL, 0x232C4F1FF84DAF4FULL, 0xDEC82F0F55E54763ULL, 
            0x2601B1D8E4AF503BULL, 0xBC087D522994A116ULL, 0x1286EFAB742DB1D5ULL, 0x5490A538645D1AB9ULL, 
            0x78B42D7B2A3DCA20ULL, 0x3E959B9E28B96CCEULL, 0xE6A97D649314FEF7ULL, 0x2AAB371B05A979C3ULL, 
            0xA5654A08EDBB9B12ULL, 0xD61B07DF462D61B9ULL, 0x0DC571CC8D7B710FULL, 0x9993EE1587DE0063ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseAConstants = {
    0xBA3D7B8A55C67ACBULL,
    0xE5708301E1484E77ULL,
    0xB258492C1538C1B6ULL,
    0xBA3D7B8A55C67ACBULL,
    0xE5708301E1484E77ULL,
    0xB258492C1538C1B6ULL,
    0x67FEC230B7C8F697ULL,
    0xC17A41F81495860DULL,
    0x38,
    0xC9,
    0xD2,
    0xCE,
    0x67,
    0x13,
    0xD6,
    0x8F
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseBSalts = {
    {
        {
            0xDE6F2FD8A0B3424EULL, 0x7DC5A3620C40D85EULL, 0x2DF0A4F60990CC8DULL, 0x583F7FF5E7AEE2D8ULL, 
            0x91CC91B7E6FE288DULL, 0x84E6EBAC479D8845ULL, 0xE4DFF5B49F88A9ABULL, 0x21910EA7BB30DF52ULL, 
            0xCE76FC10CEA69208ULL, 0x2230C733E966E389ULL, 0x0EB8CE821D75B19CULL, 0xE5EC1D666B8D4C1AULL, 
            0x09A3F755C4EB0BB2ULL, 0xD8A4728DDFAA0B28ULL, 0x6E8986BACDDF75F9ULL, 0x0640D649E958EA95ULL, 
            0x0F91D378674DD062ULL, 0xA058D92038315718ULL, 0xD2FFDBD9A1810E16ULL, 0x98C7CA5FEA887B15ULL, 
            0xF0E302B9FBFB0337ULL, 0x1912D2D4BD4B5401ULL, 0xBCCD4757D25B0A6BULL, 0x9CD8648BCBF03054ULL, 
            0xD6B6C1D7F61F3FCEULL, 0x68C5AD19510B21E4ULL, 0xD449DD7D5B67EECFULL, 0x67A8E4323DF05B17ULL, 
            0x83EE44EDA4974517ULL, 0x4D7D20B921F3AF8EULL, 0xEBFEFD9CD5E41294ULL, 0xD592733FF2EAB043ULL
        },
        {
            0xB03D3A779FDC38CEULL, 0x200FEBACA53D574EULL, 0x96E05279AC9E8F83ULL, 0x1E176979E6798D31ULL, 
            0x65656C04AF326DBFULL, 0xD2A99A52315C6C14ULL, 0xCEBA5F7198F0C977ULL, 0xE92B38DF10C14EA6ULL, 
            0x69EE797ED45ED4E8ULL, 0x711E770C40C80B39ULL, 0x4F876760701FC3FFULL, 0x7E3983CD90EA4F1CULL, 
            0x9497B5B6540AB70EULL, 0xD842B14FD3CC06BEULL, 0x344345FAADC7C74CULL, 0xA00D5E1B0CD0FFA5ULL, 
            0x8B20D8A37E73D682ULL, 0xC4F391DF6B38ECC4ULL, 0x35B5CDE4A95F125FULL, 0x16570DFD543150F9ULL, 
            0x21E9DABC53D944DCULL, 0xA682A75013D49FAAULL, 0x313A8B7ED32D269CULL, 0xE84A0DC0769C2B26ULL, 
            0x074F1B212E204072ULL, 0x0827B0C0828115B4ULL, 0x955B2FC82265A0C8ULL, 0xBE44CAE30B851A76ULL, 
            0x3000F60E79A29F83ULL, 0x9702D2FF5E26C901ULL, 0x09888574619572F2ULL, 0x6CBF62F5ABB28C2BULL
        },
        {
            0x02D7F926CA100F60ULL, 0x0259EDCAAF1D2BC5ULL, 0xBB63D7DB8A9038E4ULL, 0x433E4984104244DEULL, 
            0x1C2C5FA33C4AEB7BULL, 0xDDEE4661850FA525ULL, 0x9216F596B92B201CULL, 0x63FADC938DAEF2C7ULL, 
            0x49069770433F0BEAULL, 0x08777B8F159A1410ULL, 0xFCF053F269232436ULL, 0x8872B1B2A6A6CF6FULL, 
            0xD342F151BBA56C18ULL, 0x6BF7B78ADB6C7916ULL, 0xD3415850B15862B3ULL, 0x9A767E369742B5CDULL, 
            0x1879094A8F7130E9ULL, 0xACDD1A65BF236A92ULL, 0x5D4118C755FEF865ULL, 0x7DA9DC6866DE2EE9ULL, 
            0xF1C0224F129C20ADULL, 0x6172F1D81A889CA9ULL, 0xC70191C1C672B8F5ULL, 0x86C6009A9394CBCFULL, 
            0x23653618EC6CE988ULL, 0xE8C7B1C519EC733DULL, 0xA32D09F33D7B5B91ULL, 0x1150E2A22EE9F4FAULL, 
            0xB8E1664B352A1CD9ULL, 0xCD9499525AAF8D63ULL, 0xDD1DA0FC16FB932DULL, 0x137BA5F5F4F3C37AULL
        },
        {
            0xCD29CA7AFE1CF0ABULL, 0x7765D80D139B4725ULL, 0x762A95BDCD17038BULL, 0xB2211D521E748EA3ULL, 
            0xCEE3B67818EAE196ULL, 0x4EE4D56B9E787980ULL, 0xA8E3DFF7039A5C5AULL, 0xDD433B6201430156ULL, 
            0xBF6C35A7B281D2D6ULL, 0xC445505AF0813901ULL, 0x2316AEC189F868E5ULL, 0x41F3AB1D70ADFDE1ULL, 
            0x885C787344586E83ULL, 0x5BD2B19CB13A2854ULL, 0xF8BE16550D671CAAULL, 0x7E43C7CCA7F519D4ULL, 
            0x8D65B311F0A39B3CULL, 0x2B767654B2DD0E59ULL, 0xAA57F2CDE6F25DE1ULL, 0x99BF0F1537B76ED1ULL, 
            0xD27D21C6938F02B9ULL, 0x0BCF418C4D68CC9BULL, 0x876E76594F84208CULL, 0x1F5AC97B5664B713ULL, 
            0x728C0358D61C15A2ULL, 0xEBC2992825E09666ULL, 0xA14846DE36EB0749ULL, 0xDC612C62255B0ABCULL, 
            0x0BADB5DD01C70ABCULL, 0x24C857391DBC296DULL, 0x90E3AE5F4CC3E01EULL, 0x983E048A04F43040ULL
        },
        {
            0x3C05249B3A6CB319ULL, 0x34D16390198A092AULL, 0x34E320CFC2895FA7ULL, 0xF75E94C5374DB309ULL, 
            0x323EA5214809CBE5ULL, 0xE5BEFBB05C48C512ULL, 0xDF60925CEF6C7E5BULL, 0xC91D9C7AF170BB03ULL, 
            0x39F685CF05E9319FULL, 0x7FD7038155CCAB0CULL, 0xC0846F77EA2F7B8CULL, 0x90F32D2CFA664E49ULL, 
            0x3168526E253CC478ULL, 0xF10318060D819E45ULL, 0x297488CDE9D6592AULL, 0x5729D0FA638B07B6ULL, 
            0x5E1B8D2CF3C83719ULL, 0x93EFC95E100E0663ULL, 0x2E5824B449A7919EULL, 0xDA2FF38E4FEF1CD6ULL, 
            0x9413C029FAAB027CULL, 0xB86B23EDA9659252ULL, 0x8A3E278D4FC5EDC5ULL, 0x94070BA26471111AULL, 
            0x77C8E8573E3E8391ULL, 0x847B9BDBBE01793EULL, 0x76FFE5510EDD998CULL, 0xCC45F302BE04FF4CULL, 
            0x56877F1F889BB723ULL, 0x1AF7AE353BE3C332ULL, 0x6051BB0C19396BD6ULL, 0xE9188141A394642BULL
        },
        {
            0xB6FEF1C98B3A76ADULL, 0x8D327F21095B51B9ULL, 0x05FE3D5C7D378E81ULL, 0x02542567956A824CULL, 
            0xF8CD7DB3F59E4EC1ULL, 0x21BD85BC4655749CULL, 0x87EEA9255C43FEB9ULL, 0x0AB9C2681564B79DULL, 
            0x0D41A249B2480EB9ULL, 0x4885E1927397E57CULL, 0xD64D59CAD035C336ULL, 0x42DD9937461636D7ULL, 
            0x52CD573757D5A25FULL, 0xE00CDA057A7163B2ULL, 0xE48C346DED66048DULL, 0x2A71E2A4546F9D1FULL, 
            0xC0F6DD3D8BF3537FULL, 0x78ABE1D09CD7D6A6ULL, 0xAEEE3E4C932BBE06ULL, 0x20D00F9FAE37BC15ULL, 
            0xBF3322109E8CBC52ULL, 0x8DCA0EEAF6A4045AULL, 0x514563F43C610B0CULL, 0xEF3EAC12AA85C28BULL, 
            0x566243E0DB40F1D2ULL, 0x24610CB98E6B829CULL, 0x60577BDDD25CDF86ULL, 0x3935333E17B3F81BULL, 
            0xA4974EEE16CA1B4BULL, 0x33C2E68D21EBDB7FULL, 0x85AEA66B93A8C624ULL, 0xEB437219786D3F72ULL
        }
    },
    {
        {
            0x07900E03FADDCD57ULL, 0x04E39C678DB3DC0CULL, 0x96AE86AD22E8D46AULL, 0x5442C220567437DBULL, 
            0x31F3EA6693CA3661ULL, 0x2F20E7518C966759ULL, 0x2796974EC1A62827ULL, 0xCAF5A327C908B584ULL, 
            0x0CC1498CE995B966ULL, 0xF8A12F0A300642AAULL, 0xE702911E8CECFCECULL, 0x9B47E76A3230E6AFULL, 
            0xFBE18B4982F8D901ULL, 0xC3AF992650F21B2EULL, 0x943E50D43C802B6BULL, 0xFAC8C5D6E3F979EBULL, 
            0x8E166D90E6CFB5E7ULL, 0x19324736624EA42AULL, 0xF862D12F909DABD4ULL, 0x31365DA8713B04BFULL, 
            0x1B4BE43769EB2843ULL, 0x180EFB24C795486FULL, 0x3154A49D0D7AF56AULL, 0x2D39A5CEB5147A1FULL, 
            0xF6A7B802B645D627ULL, 0xBCADA12BD2C51EC1ULL, 0x893E324D36C015A7ULL, 0xBDAF133EA8B87C03ULL, 
            0xA94233CC81912FABULL, 0x8A8849FE88AB924EULL, 0x27545D0DDEE1FA47ULL, 0x83D55D6C3F671B0FULL
        },
        {
            0x4CC4C68BA626DA47ULL, 0xCC1C14AD14EEF0AAULL, 0x794D78EF592F8560ULL, 0x437159BC1C36E11CULL, 
            0x699F17682786225EULL, 0x6C18D45740D4C891ULL, 0x526C8AEB1109D109ULL, 0x14228E6C8364E153ULL, 
            0x15AE04B4D7AB2885ULL, 0xAEE774C7936FF6A5ULL, 0x56549440C3CFFD29ULL, 0x1343DAC642FAB844ULL, 
            0x9ECD852407AF28EAULL, 0xAE746DB2F323F23DULL, 0x276E6CC48FD8AE91ULL, 0xBBEC21148C07117EULL, 
            0x68AA22B4494B2539ULL, 0x112F4530486AF6DBULL, 0xC79272F26923D57CULL, 0xE09A27AF48ACD482ULL, 
            0x995CC8EFA33AFADFULL, 0xC5A1C224049D076CULL, 0x6C508ECBF015DAF5ULL, 0x121BA474AAF3E357ULL, 
            0xDC337324E4697BF7ULL, 0xFDB3EB9673A5613DULL, 0x256C2D78BBDA284EULL, 0xF4EFA1B156C19237ULL, 
            0x2F1D3F0AC723E6DEULL, 0x414D59D93FA2CAF8ULL, 0x2966E0B4E5CAE828ULL, 0x34FD1AAC5DB9B3D3ULL
        },
        {
            0xB4912141BA45F54CULL, 0x5E6BBB609EEA39D0ULL, 0x66030C5782C301E6ULL, 0x63E71B699645F35BULL, 
            0x98D4C9D1769EFE83ULL, 0x0E716EECF9A89DE0ULL, 0x54141A452FC48C53ULL, 0x7AECF8FC60C79C5CULL, 
            0xBD7D9CBBB042D80BULL, 0xE3510604DD58F5A5ULL, 0x56897954B1A54055ULL, 0x9A3CE883CE854DACULL, 
            0xA3D79606F71E5DC0ULL, 0x2D152EB0271F848FULL, 0x8B033C381519C92FULL, 0x9C0082D8A406A3C2ULL, 
            0xEFAB15D6D93E4AF1ULL, 0xE2E33CEE0F049C58ULL, 0x602425FE24EFCA0CULL, 0x38E43D71C72006E3ULL, 
            0xF816162F4EF4B06EULL, 0x49C2CC43B99A02D0ULL, 0x69FEEDEA1520048FULL, 0x97A1BB519DBA0C39ULL, 
            0xF19E17B72781FFAFULL, 0xCD62491B0BFBE2BEULL, 0xFC93EC44E3667CE0ULL, 0x43AFD6332DB320C5ULL, 
            0xD081E1DD7A63FD8EULL, 0x9390A75F4221EB64ULL, 0x5A24E314CC20D5D8ULL, 0x1651EC271F45AC1CULL
        },
        {
            0x76E45EA064E1105AULL, 0xDCE267FBE3438E3BULL, 0xDF584D63927FEBE8ULL, 0x50C62D6839BC2BAEULL, 
            0x2BA64A0EB0DAFB5CULL, 0x4490A6A166330B57ULL, 0x2E9A67C293C51A78ULL, 0xFE394D8D3A7153A5ULL, 
            0xEE452AE7E76373C4ULL, 0xDC18DE576A01CC9CULL, 0xEF90C9FE151E2E8FULL, 0xCBEA19CB40919954ULL, 
            0xA2290867509F01D9ULL, 0x0731F6C219F5588FULL, 0x8D585ABAB4A3C66FULL, 0xB21D82163A5AA97DULL, 
            0x8D1DEB1690C9B8ECULL, 0xBCEC75313458D18EULL, 0x0D6D0EE08DF3D005ULL, 0xD19BC0A70BC0454EULL, 
            0x3A7EB1A81558D75AULL, 0x99B1D6434C0B75A2ULL, 0xA229B2EDF62AC3FCULL, 0x21C8E5027B9F11E2ULL, 
            0xA67E6F3CFC31C505ULL, 0xF4F4825741DFEA19ULL, 0x73C490F3514A4DD1ULL, 0xA34CEAE0A43ACC6AULL, 
            0xCB5D5043034DAD53ULL, 0x86A0FF3BBBBC5CE0ULL, 0xB12644E3005478C2ULL, 0xBDD2E352BA08845AULL
        },
        {
            0x631479E47D8A88BFULL, 0x306BCEEC61B2BD20ULL, 0x45106AE905E53C8FULL, 0x138F235FFB638F59ULL, 
            0x7045BA20966A9C58ULL, 0x1D5BEA46A5F0B74FULL, 0x1178895C90808D6AULL, 0x2636846E103105FCULL, 
            0x829DAAB6A15C0384ULL, 0x3B26A3E97BC3F4B7ULL, 0xDA230F787C387B1EULL, 0x8988A72A8F4A59E4ULL, 
            0x366F311A6BA22BEAULL, 0xE627394F3B77D312ULL, 0x7FEFE28C4A0BD21EULL, 0x9DFCD7A7827CCC42ULL, 
            0x82467A6A73287648ULL, 0x34A2077DC444A2CAULL, 0x82B49637B297ABBBULL, 0x60690C948862EBA5ULL, 
            0xBCC17970178245F2ULL, 0x51CC476538E45158ULL, 0xDCBC84C7FBA8E572ULL, 0xF18C0E52A8F8B1C7ULL, 
            0x5063AB7301803505ULL, 0xF7BD8E631BFE9774ULL, 0x42D5A418E7A5401FULL, 0xBFB31DFA58713DC2ULL, 
            0xF340955FF030B10AULL, 0xF85AF40F5AD75CF2ULL, 0x48DDF670CE9F5CA0ULL, 0xA36D56AF182953F4ULL
        },
        {
            0xC8FA479BE30BA403ULL, 0xF40E89F020A3F51AULL, 0xD6FF9FE72829780FULL, 0xDB74548F845DB6CBULL, 
            0xFAA3489AC5413631ULL, 0x71639CD01FB1FD08ULL, 0x08FE12BFEB37C884ULL, 0xFEA2CA9BB550F19EULL, 
            0x2EF735FE18EE127CULL, 0xFD6435581CFBD5D0ULL, 0xD151EFAB2DCBF194ULL, 0x07EEA7EF706AA55DULL, 
            0xB46185DDB5854723ULL, 0x748FE5F67986A841ULL, 0xF4A35C8D8CA2A410ULL, 0x9F91989C697CC1C9ULL, 
            0xE20A3C6BCFC08FFCULL, 0x5545B25F5569A1D5ULL, 0x419E51A5CB1D9C87ULL, 0xDB88527D40FCFB22ULL, 
            0x46AD776127C5A762ULL, 0x5742E297C3AE292FULL, 0x528E3F70253B3A3EULL, 0x486199926386F509ULL, 
            0xD46EFFABD26E8282ULL, 0x1811B0ACBCDD81E9ULL, 0x2F8CBC784EF27651ULL, 0x364A5DC03EC03576ULL, 
            0x294550970286004FULL, 0xE716E6B51CD71EA5ULL, 0x29F43A3576497193ULL, 0xDAAE105387C5017FULL
        }
    },
    {
        {
            0xDF764AD72A53D25CULL, 0x4A21168AC0A0CEB1ULL, 0x9F463B20CAF69470ULL, 0xDE50534642E0F040ULL, 
            0x4E30D2C9BE12E633ULL, 0x8CD8013D5CE85EE5ULL, 0x38F21A76AAAB3876ULL, 0x722977253DEDD746ULL, 
            0x5B9522E1C02869F9ULL, 0x4A4626CE0613DD49ULL, 0xA7E6CDEA585D6B5BULL, 0x550617E98165F207ULL, 
            0xAFC1DF095E3FA398ULL, 0x03C68042A1E516C4ULL, 0x4DA638D9B3574D55ULL, 0x3A6EFD552C296A42ULL, 
            0x7E8B30996F4CCF1BULL, 0x15F629AE1B2043C8ULL, 0x523743A2DD0A6A38ULL, 0xBF90BC9E69461735ULL, 
            0xDBA120F054A58D6EULL, 0x7FD21CAAEA657DE9ULL, 0xBA708F172D4C4CB3ULL, 0x3D121E20055EA38CULL, 
            0x40669B8564B0A3D0ULL, 0x18126328EA0B7299ULL, 0x0D9C8320ADA3C538ULL, 0xE396E3280A1BB706ULL, 
            0x503FF1E7F697C86EULL, 0x707A0C1741C53603ULL, 0xA51D032B612633C5ULL, 0x295D0BAE7EB58964ULL
        },
        {
            0x6F6A8C642493995BULL, 0x48BEAE2C05C15070ULL, 0x68AC402BEAD7796CULL, 0x7E7988665521DB49ULL, 
            0x0D705F0CF5877BCDULL, 0xAF16A4ABDE307466ULL, 0x6979285A1E7B60C0ULL, 0x30973EC7A158D09DULL, 
            0x1B0A8A2BBDDA020CULL, 0x51BB1072A0C8F55FULL, 0x87EBF8F051A23008ULL, 0xA5FCC6B55E1B8E92ULL, 
            0x2CA51A4EF4CF2BFFULL, 0xEF2FCD91D60EA4EBULL, 0xA31BB6DBBB389805ULL, 0x0836D9230E11AC64ULL, 
            0x0ACC1202D2671A12ULL, 0x044892318B058CD2ULL, 0x844AD9D5548E753DULL, 0x1C848AE80E21E564ULL, 
            0x89249BFF4C7D2AE4ULL, 0x63C517898E7DB9E8ULL, 0x3F94BB3325AB7722ULL, 0xD5E95A86CE5BE7BCULL, 
            0x58BF901F11995338ULL, 0xDB966275778BCBBFULL, 0xB3EB0F90D2BBADFBULL, 0xC917AA70B95073F1ULL, 
            0x87D019CF67E3095DULL, 0x17AA2FDA1CD7F1C6ULL, 0x27383F9C1F7241C8ULL, 0x2B956AE49C9A3B40ULL
        },
        {
            0xFA0E9B88DEC1C84CULL, 0x694D2752880C879DULL, 0x74E824B7A84E3040ULL, 0xECB6E1282AAD3BA3ULL, 
            0x96FE09BA3921D249ULL, 0x85189BBC35384BFBULL, 0x06D254A58B809D73ULL, 0x49E19DBCFE034B42ULL, 
            0x9C8A955A18AAAF96ULL, 0x4131F56616958FBEULL, 0xF6518F3C67C835D6ULL, 0x1D0CC4FC54B1300AULL, 
            0x9B9C125937836742ULL, 0x904610FDF715892EULL, 0xCA5C3B81AE442F1BULL, 0xD2141B9CF52E6085ULL, 
            0xCAD9B09BF1C93522ULL, 0x5C573F14A257FE0CULL, 0x0DD9D7140CFEB45EULL, 0xEA83A5577CC82E91ULL, 
            0x2CD82605001C1828ULL, 0x435326FD9944B5B9ULL, 0xE47D440E705882E6ULL, 0x068FD3E56E549C25ULL, 
            0x3A5D482A7702CB83ULL, 0xA53BB1A6F9F080D8ULL, 0x6941093ED0395418ULL, 0x5DC9152DDD47763AULL, 
            0x5BB9C0D8A308635DULL, 0x68A61CB51905B60FULL, 0x7643FE10CECAD714ULL, 0x499F74F89377D225ULL
        },
        {
            0x97764BF6850BF663ULL, 0xE755C43C5545F90AULL, 0x8518168A65FA0CDFULL, 0xB7899D04D775767AULL, 
            0xB40E9159A561BA6FULL, 0xEC5DEFE7053FA436ULL, 0x523EAB6194E0B36AULL, 0x207D80323810B115ULL, 
            0x955E7D1C14A5354FULL, 0x893898A52B25EC91ULL, 0x2F04FD48DD25D38EULL, 0x7BE1AC713D5226F0ULL, 
            0xE5475F928FE7FB6FULL, 0x753A0FD08676C8F6ULL, 0x7EB6CDD48FA5FDD0ULL, 0xBCFED1439EA78C7DULL, 
            0x27EAF03FCF4EB9CBULL, 0x73D9CFA2C4E7112CULL, 0xDC4C428EB5953135ULL, 0xB779160A419B7486ULL, 
            0x92D059832AA1437DULL, 0xAD47CF3B8F7F70F6ULL, 0x00BFA9492F645CE0ULL, 0x52DBE12956D3E9BCULL, 
            0xC4F72E17DF7D5548ULL, 0x9DC2FAA340EFAD09ULL, 0xF4B87E66468B61FCULL, 0x072B216AF9E97AAFULL, 
            0x939665582A22F077ULL, 0x637BEE16BEA507DDULL, 0x05BFFD7AD5FB4EF1ULL, 0xDAA8AF86A417F300ULL
        },
        {
            0x0BAC535CE5D8DDF8ULL, 0x46D934B0710E8D68ULL, 0x4AE55ABE12C5A915ULL, 0x0E59158BEABD8CBAULL, 
            0x144AEF767FDE26ACULL, 0xEC44F67603187936ULL, 0xDF1D47CE2716D2ECULL, 0x8E743ACD990E7B96ULL, 
            0xAEFE95747DC44900ULL, 0x67348341C54F5AF7ULL, 0xDCFC2AA128C552FFULL, 0x21EB9A7FAA55BCB1ULL, 
            0x0FD4DA1425E3AA85ULL, 0x74E6021302F73CC4ULL, 0x7A3C9E42C8E872DAULL, 0x6497E2B2512E605BULL, 
            0x4EA184D91F17F9C6ULL, 0xE053329A9C37A113ULL, 0xFA862E2A0CA9A52AULL, 0xDAD2D4987F1CFC20ULL, 
            0x2FE148571EBB824DULL, 0xAA7A3D26A82D0485ULL, 0x240020B851FDE2CEULL, 0xF44995B8C4C388AEULL, 
            0xA9EDB11024BC0D57ULL, 0x1E43FB390F5A321DULL, 0xE7C4D8B31224BFFBULL, 0x9D193DA59435369EULL, 
            0x297BA9744C80EA90ULL, 0x004BBF4BCE6A4E90ULL, 0xD931AE7BD15A202DULL, 0x7C1DA721E5FA14E4ULL
        },
        {
            0x5176A9B7037587F4ULL, 0x58A5E000A7BA3D5CULL, 0xB3D13705B67B66B8ULL, 0xD8C3AB9983385C7CULL, 
            0xCFB99F1C23442188ULL, 0x4439F40CB73E2EA5ULL, 0x9CFAEA2A84709B0BULL, 0x1140ADB8C792AE05ULL, 
            0x4DC3E26EE28EB495ULL, 0x9ABDB28466EE598FULL, 0x0C9A14E3E661CEF2ULL, 0x7851123F213961EFULL, 
            0x6C90A48AA478087EULL, 0x5B452ADABF58F584ULL, 0x10D46C02A429869BULL, 0xF348C4FA0E0BE028ULL, 
            0x7C7F54C8DE645CBCULL, 0x6908196798FF9F02ULL, 0x51A1D37EA80E9FECULL, 0x81C1806D5B9596A0ULL, 
            0x87720AE41025CC08ULL, 0xB79195E35D831CF4ULL, 0xDC83D616DF21EC60ULL, 0xE84B838BC314B42DULL, 
            0x5A2EAAC0538ED064ULL, 0xA4A15A3EDB787AB6ULL, 0x7BD5D95954E42F8DULL, 0x5A93F0219FAF2F27ULL, 
            0x6999797D3BF36A80ULL, 0x4582D1AB235EB6D6ULL, 0xAAEE938DDB656E27ULL, 0x51F0C89E62104491ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseBConstants = {
    0xF69C2E36602068CDULL,
    0xA1E89D03C40F06F7ULL,
    0x5690A0EA373D9C7AULL,
    0xF69C2E36602068CDULL,
    0xA1E89D03C40F06F7ULL,
    0x5690A0EA373D9C7AULL,
    0x76A1CDE2D0325942ULL,
    0x4257B9CE89777130ULL,
    0x83,
    0x9F,
    0xD0,
    0xA2,
    0xC5,
    0x47,
    0xB1,
    0xC3
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseCSalts = {
    {
        {
            0xF5BEF550298FE2A5ULL, 0x28E7A3D1452D49F0ULL, 0x854AB11BDF496BABULL, 0x3402B2C981273C7EULL, 
            0x3FEAEFEEBAC5C460ULL, 0xB2485FDF084CF0E5ULL, 0xAE5258D4BF872E55ULL, 0x145C44598E3029D2ULL, 
            0xF9141F9C98EFFC87ULL, 0xD219BF416E046EE5ULL, 0xC4422100861B155DULL, 0x9585307D6218B2C8ULL, 
            0xBD9EFFE21F1C3BF9ULL, 0x1E760B4CA725CBC9ULL, 0x4E458447526D9E6CULL, 0x086F6A847159BA4CULL, 
            0xA1BCA7F22C798318ULL, 0x00635912D2F33980ULL, 0x5A8F4DDA85EBEC0FULL, 0x5B2EF60FE4A43918ULL, 
            0xB83520FBDF87816BULL, 0xE30592929244F675ULL, 0x0C9A9C36989D5A56ULL, 0xDD71F2654CB05C5AULL, 
            0x2E2973E844DF06FCULL, 0x6A6FFD2B649F20DAULL, 0xB92D035EE0F0B2ACULL, 0x410EDA240F0BE680ULL, 
            0xEB575F82D982B514ULL, 0x7A3DC9242C3FA96FULL, 0x2397E78022E8E6DFULL, 0x8E779A47E71F2A4BULL
        },
        {
            0x51ED9F0BEEE70C7AULL, 0x8D133FBAA879142BULL, 0x3066DBE327CE3001ULL, 0xB0F0BE6E23AFF6DFULL, 
            0x58ED390E19EABD05ULL, 0x7D3400012E233C47ULL, 0x53D2125597F585F1ULL, 0x856DAC6A54863B54ULL, 
            0xE9A05C9222A440E2ULL, 0x717718C17FC14EA0ULL, 0xC3185C171B6FB67BULL, 0x1DB546FF040BB741ULL, 
            0xC270D1F2AAD14CCBULL, 0x6A3933BCCA52C903ULL, 0xBE6E7C6E24AC80E4ULL, 0x45E5CFE207EEEC9FULL, 
            0x2ABA175C5C77F480ULL, 0xA368D32F55E0B8A4ULL, 0xD1F1ACFE1E2BA5EDULL, 0xE0E38038A9243431ULL, 
            0x14CEDFA166695B65ULL, 0xF8B9AF0138F490F2ULL, 0x0C0CE54541F22048ULL, 0x6722D8FD7FF1DDF5ULL, 
            0x531DFD2FA7CE54B4ULL, 0xF2C2C9692167DB78ULL, 0x063DAACD5D51446CULL, 0x7D2D522A46091263ULL, 
            0x176CB62B67EB7E54ULL, 0xA37FFC77D3A9A0C3ULL, 0x57188BAB8D4EBC11ULL, 0x518661DB4B344AEBULL
        },
        {
            0x451A38EA2393D90EULL, 0x951AC228F2AD4C9AULL, 0x19F2BCE51239DF55ULL, 0xADAFF4C876048074ULL, 
            0x3314962B7EFC1F0AULL, 0x6478EFD583844894ULL, 0x9332614465A3D473ULL, 0xE844B456A2766910ULL, 
            0x36DFF0FCF29248FCULL, 0x67DD7AE1CA8340C1ULL, 0x256638213E5B0594ULL, 0x578E91CA5149DAF3ULL, 
            0x88DE7C192CF46A06ULL, 0x6A7BE10E786093E0ULL, 0x5983C927BFA4CD94ULL, 0x0F3AA30FA0E329DAULL, 
            0xDB9F80470738EA4EULL, 0x4181255730C5D124ULL, 0x56A52A4C858204D6ULL, 0x1651A156AE2E1A3BULL, 
            0x91D958BF80F72AF6ULL, 0xA1825358714D1D27ULL, 0x349B6F8E506D0CB1ULL, 0xFE1A4697EAFDF77AULL, 
            0x713D916C7BF359C3ULL, 0x7268BC6591E25B64ULL, 0xFC585D2352B4BA47ULL, 0x55DF43B1239338F9ULL, 
            0x683F6A18F9952C35ULL, 0x5395C16A106C73F9ULL, 0xDFBF71B7C3B62DDFULL, 0xF0B542EB4AC0A8B0ULL
        },
        {
            0x823A685B9438A9E1ULL, 0xF8F69584583B98DFULL, 0x8C61F09BDFB6D5D7ULL, 0x5ECC4B458B5C422DULL, 
            0x6E8DAA9428C7C789ULL, 0x0E15C7E2D5F727CEULL, 0x2BA16D74E4726D96ULL, 0x04D0EA09FCEDED7CULL, 
            0xABC1D285079536DFULL, 0xA0A90D20CDB1E3AEULL, 0x4E69005A0C9A338EULL, 0xF2EF578E3372DE8DULL, 
            0xA575D5EB31E10D55ULL, 0xEC9F9FC4E2EB70EDULL, 0x2FE431FC5A740E1FULL, 0x01A0F56E38281229ULL, 
            0xF23EC50C58EE6666ULL, 0xF9C165E319128AC2ULL, 0xF8055CAAE81AAF53ULL, 0x844B5FA8762D790FULL, 
            0xD7A0BAD0B2048D11ULL, 0x975389C7522F0ADBULL, 0x4A3F98487EEBA442ULL, 0x1B5CE805268D9DA0ULL, 
            0xAB30C661FBE78113ULL, 0xD5755596995144FFULL, 0x07DA3F5B46BA4A29ULL, 0x1B6C24D19F905ACCULL, 
            0x9E9E4764F0B797E7ULL, 0x881B530981706D74ULL, 0xCE34FD41D2644489ULL, 0x1EBE0A2B0BBCB17BULL
        },
        {
            0xB241C2782AF4F80DULL, 0xF425190E5FD585A8ULL, 0x3C1537EE58858DF6ULL, 0x54765B00E3129094ULL, 
            0x789560636427C8D1ULL, 0x3461C0ED7C7561D3ULL, 0xDC7D2441BBB51373ULL, 0x90508EA5997A8211ULL, 
            0x8A23D585EFE925F0ULL, 0x98BC9CE63F062CBDULL, 0x2614A2B1FD0C2A62ULL, 0xDC38DBCFCB1EEF32ULL, 
            0x91C987026D13D102ULL, 0x961A7B543F636C5DULL, 0x6EC2C78C02AC3589ULL, 0xD8EE44A4F1F8E7EFULL, 
            0x89896E1462BCB50EULL, 0x4F6D3DC3903B85D4ULL, 0x5242875D572907F2ULL, 0xB9CD33C1A2D02327ULL, 
            0xBC0909482BAEC4E2ULL, 0x8B2DFAAEB4475D76ULL, 0x7227360A28B7D761ULL, 0x2D971ECBB3860A6EULL, 
            0x575D1D1C60C98607ULL, 0x1BBC97E46650D777ULL, 0x92CC3BCE14881C29ULL, 0x100300CFF5BC76FBULL, 
            0x6148472CB8258EFBULL, 0x0A7E3ED26D1A3217ULL, 0x1FF792B65CC609ACULL, 0xA5FF9C31C9438C94ULL
        },
        {
            0x8D3EF1E0025DCF85ULL, 0xB64574C05387104CULL, 0x7D270F29FBC0C9C3ULL, 0xCF0ADCCC0812C953ULL, 
            0xE2A445221A9F3D8BULL, 0xA6D263D1F404C69FULL, 0x132DE1639AD2AA91ULL, 0xF5A9F01A28BEDAEEULL, 
            0x720AAE6E34EDAC42ULL, 0x12CB68F8D5875A3CULL, 0x2EC0824A700BBBF2ULL, 0x555B1CD0C6329F53ULL, 
            0x422A0241055F0B46ULL, 0x6AE235730A5908B3ULL, 0x04C71B76B8FA6206ULL, 0xD7B145A1F58DC693ULL, 
            0xCB87014CF5F70C86ULL, 0x967919EF2D7A272BULL, 0xCBE5F71B9FFCF035ULL, 0xCCFB9849E901354FULL, 
            0x9FBAA901E56E73E3ULL, 0x68DCD52333595D1CULL, 0xE5B7495871B5E016ULL, 0xAC7771246CB96F71ULL, 
            0xE46769BA467EF0DFULL, 0xA0C7C0B66B805F11ULL, 0x61008619BA2094CEULL, 0x66ECCF5E93CCA1F6ULL, 
            0xE9F3EEFB5394B939ULL, 0xA4BDB4387A3AC003ULL, 0x142563B6880655EFULL, 0x0EB1DC92DE2B08FBULL
        }
    },
    {
        {
            0x7695DA8C5D8DC111ULL, 0xE1B2B291EF7DACD4ULL, 0x614A2CF43E8CEA19ULL, 0x8D94A61C6B7D4CA0ULL, 
            0xC2E72E4990E405F7ULL, 0xD7BE03EC1F568FA7ULL, 0x30041BAED5EC7750ULL, 0xD6FC18ECB39C4FD9ULL, 
            0x6E6498147A511534ULL, 0xCE7E771936E25E48ULL, 0x0EF9816DB900C972ULL, 0xD4C6F11828B3AEEEULL, 
            0x75012D3076E21A47ULL, 0x79A411A36C7D82ABULL, 0x3308BA1C40AEDECAULL, 0xF92F9511E4009C3DULL, 
            0xEB437C865AE746B0ULL, 0xD47238425F7C338CULL, 0xF6FAD07268F87CAAULL, 0x5EEE387A2588A3E7ULL, 
            0x2C09F6A706EEED02ULL, 0x43576EB711C97413ULL, 0xE4DA969373D93E58ULL, 0xCF697803EF540FF5ULL, 
            0xA99E95D3A9A4A947ULL, 0x92CBC1EE2EC0FA4EULL, 0x9254706826D3C8B7ULL, 0x713A3C49137663E2ULL, 
            0xA50FD1E6D62CB1B1ULL, 0x00970883D25823B8ULL, 0xD28B4F2A8982BE9BULL, 0x368CBD6274D74E53ULL
        },
        {
            0x9A666356590CD558ULL, 0xF3CD9616FEF6B334ULL, 0xA8E47FF9BCD261C1ULL, 0xD87E3190730AE339ULL, 
            0xFDF29CD610A17E7EULL, 0x52A9986C55B7AD1BULL, 0xB2299EB8BCB2688AULL, 0x1E59CE938B331B6FULL, 
            0xB414B5ECCCD32654ULL, 0x0F26D7DFF074A43DULL, 0xC834BA203B00AA5FULL, 0xA267214887F55A78ULL, 
            0xA80CD91815030F04ULL, 0xD84991DED7019D06ULL, 0xCCF5BB0051E7DD47ULL, 0x84F685316DC4C291ULL, 
            0x81B4F7E25947F8D5ULL, 0xA5203F48C5C9036BULL, 0xFE47BA3205A59126ULL, 0x4EF196685553DF6CULL, 
            0x124F477B694BBD20ULL, 0x5FE3B980D6675A0CULL, 0x8B591298F1D31307ULL, 0xAF3074A416390ECAULL, 
            0x8D04BDA998E125B1ULL, 0xC7ACF0AC7F85678CULL, 0xE1A5547DDA9CF56EULL, 0x6F94AD49BF7C66C2ULL, 
            0x62DAB77094DC9F97ULL, 0xCCB096040262CB68ULL, 0x4120E1CE24BFF446ULL, 0xE7BCD6428271C0D1ULL
        },
        {
            0x439BF2B2AEEA0B77ULL, 0xB5323732A446F90DULL, 0x14A21166853741EBULL, 0xC962265EA65C1220ULL, 
            0x086263AD10672181ULL, 0xD0D0687674623EE2ULL, 0x1E005A92E2D435D2ULL, 0xAAB376FCE085E53BULL, 
            0x97EE11966BE26906ULL, 0x62000CD4AA15E42AULL, 0x1D7ED25ED4D7664BULL, 0x697ECC37123FCA61ULL, 
            0x54B65B43651061B4ULL, 0xEE3BFF5C21B708D6ULL, 0x526CC80E53DFA012ULL, 0x7EB4C031FA4266CCULL, 
            0xE3BC588070F95FA1ULL, 0xA9D9CC62698AD637ULL, 0x3A83F4D126495731ULL, 0x3CFEBB565F543120ULL, 
            0x46A0C20AAD3921C1ULL, 0x875D9665CE022C98ULL, 0x942A467CAE60873AULL, 0x55057600C05EDC83ULL, 
            0x33127A92668FBDF2ULL, 0x79ED1B705057BF68ULL, 0x6BF863EE9A36EAC2ULL, 0x69A44B41C9E94EE0ULL, 
            0x046E328140FD5925ULL, 0x43B56EC5E9AB29C5ULL, 0x333DE9CA036CD16AULL, 0x31A1CAFDA3273C80ULL
        },
        {
            0x1ED1DC13B7353BD9ULL, 0xF5629DAC9862070FULL, 0xEF72773EEE7A423CULL, 0x7B0A27D00C4553CBULL, 
            0x97C0DB0C7A7B765EULL, 0x1E5D983064FBBE3BULL, 0x525EE31F2DF6E72BULL, 0x9F8CDA6617B65A6FULL, 
            0xCE040A66CBF5919CULL, 0x0C23859F9F6CA269ULL, 0x18609C345372E558ULL, 0x29570F2927FF714DULL, 
            0x3008EC133F1A695EULL, 0x340550BEA3A69926ULL, 0x20E1BD2D0C8D7F35ULL, 0x9DCE0E984A4365B3ULL, 
            0x0200A409FCD4FC91ULL, 0x63944F639150D27FULL, 0xC922D9123D0D0110ULL, 0xCB7FA479519BA381ULL, 
            0xB9BAE8BB21A454B8ULL, 0xAC9B91F4C5A9769DULL, 0x414123D630EA31D5ULL, 0xE7DCAC73FA3AF716ULL, 
            0x44652247F515E44FULL, 0xB6ED6FD0F3993BA1ULL, 0x1E6916B7D57AF458ULL, 0x514B7BCBE7B1063EULL, 
            0x1E37FBF29EAA7F2CULL, 0xED57EFB86868BA47ULL, 0xE18EAB2EF36F27C5ULL, 0xB2B2AA41D1FE51FBULL
        },
        {
            0xC206C5256DA6A7C0ULL, 0xFD47390748A57020ULL, 0xD13C28CE92F12CA9ULL, 0x08AB684D4CC7A17DULL, 
            0x9D1350821EA6507AULL, 0x3A224DF0F5B8B2C2ULL, 0x323B379A2FA4CC5BULL, 0xD11966B3D4640598ULL, 
            0x84216D96639BF642ULL, 0x1E8AE1078A619E83ULL, 0x216BFB297AE6E2D8ULL, 0x14D25E89D1454DA8ULL, 
            0xB2756BD23B8F1EC3ULL, 0x155E17C42B62E709ULL, 0x947C2E2BA9C9404EULL, 0x27C5E24D18C0E7ECULL, 
            0x67078597282A29DFULL, 0x6753B5B167F0542FULL, 0xFA529BAEB7CCF3AAULL, 0x828570ED2506E2D7ULL, 
            0x37738A310AB164F3ULL, 0x94835810DEA6CBD3ULL, 0xDEA5E7B01ECF01C2ULL, 0x7EAF120E73B3402AULL, 
            0x6D27934F9D424416ULL, 0x40F3D29F876BB340ULL, 0x4D5F1050AC0BA8FAULL, 0xA802C6FD79728AF0ULL, 
            0xB58DD12883358382ULL, 0xD9F3088A9E6F235FULL, 0x5B709AD48DB8FAF3ULL, 0xE7C9B8AC8C0883A4ULL
        },
        {
            0x52B1CB20C33BC1BAULL, 0x5D0A64A81011A51AULL, 0x9B6F62B4EAE301B4ULL, 0x793A30957A462693ULL, 
            0x6B1E0ACDF8696971ULL, 0x58E295FB945F9DF7ULL, 0x4D0E824815A38B57ULL, 0x166F8B7F558A31B4ULL, 
            0xD62E8862A185A7ECULL, 0x87C69845BB007139ULL, 0xDA0DF5150F2BF446ULL, 0x8EC2384BB2063523ULL, 
            0xA3ABE90B3F4F0876ULL, 0xD7CC2B4DE389C49CULL, 0x83B737BD4166AA51ULL, 0x103A3EF6AFF7EB05ULL, 
            0x38B60A0CC5A7BB86ULL, 0x262BE995BD9F4CF4ULL, 0x060E8B84E17F2C29ULL, 0x6E586BA4C9F3F428ULL, 
            0x895F56DD204FC21FULL, 0x87DA1148D2654EABULL, 0xF5C0CB89A10CC304ULL, 0x057D9E84937990F3ULL, 
            0xEF2C370CC4859BEDULL, 0xB91C5CA99D589A99ULL, 0x045A7B216AF2DA0AULL, 0x0A06C74DE25B7EA2ULL, 
            0x6C11A89973BC8EC0ULL, 0xCA557026373A30A4ULL, 0x9AA5DED4A128D744ULL, 0x8A891E8C19004DE6ULL
        }
    },
    {
        {
            0xCCD8C8F72FB381F9ULL, 0x5CC37B801BC4F112ULL, 0x978419CA67AB67E9ULL, 0x267FF898DE894D62ULL, 
            0xA98111FBCA036220ULL, 0x062FF6CA8097A7D5ULL, 0x1130FDA51F9CA1CEULL, 0x8E0D0ED237119834ULL, 
            0xF2191545BF17952DULL, 0x47006B11BEAD5719ULL, 0x1DFBD1CB214F58B1ULL, 0x25D9B542B3D87618ULL, 
            0xE7458F6DDA3DA7DCULL, 0xA3AD307D2F2D5A99ULL, 0x57AE5CE67AE444DBULL, 0xCF145CA21130849DULL, 
            0xA0CD222D40C37AD2ULL, 0xACA4A75759C666F4ULL, 0x912246DA9B25105CULL, 0xDF2C056A80CF1923ULL, 
            0xA69575DDEC0EB1FFULL, 0x3DC4AE2F28914A72ULL, 0x784A254A9D94B173ULL, 0xD1005DE4872808FBULL, 
            0x7CE890B4EDF2D9A4ULL, 0x6EB47907F87ADDE9ULL, 0x334CE55A88718718ULL, 0xCF7ED1BB4662B591ULL, 
            0xD6F01BE5A31DCF42ULL, 0x9E6F30A5E29D8963ULL, 0xD08AAD1178E87745ULL, 0x1C1FE6200E731E0CULL
        },
        {
            0x68C49F13A8B76810ULL, 0x162AF4AB39C0CBDAULL, 0xC5B9393BF0915293ULL, 0xD469EE950C6F7375ULL, 
            0xDF4E076F01C7D5FFULL, 0x421B18960DB62B50ULL, 0x1FEA79422933D35CULL, 0x3693F40F7B0EF757ULL, 
            0x79F8BD6F49096728ULL, 0xEF1D9F26EBAD2252ULL, 0xE1DB0419F927B58EULL, 0x9E8DC6E60C03860EULL, 
            0x608546531A45F01FULL, 0x1B47303BABDE5175ULL, 0x35979A464888E767ULL, 0x2F3FC29B8BB95BD8ULL, 
            0x6CD5843EA32C2990ULL, 0xA8ECEF8A00DD5437ULL, 0x8D5529629F272CE9ULL, 0x779E2DDA1E0B5591ULL, 
            0x80362E745D06E2EDULL, 0x7F752F290F5D8705ULL, 0x2F849AF5FE91929EULL, 0x4137B9622C70316EULL, 
            0xFD0F414C8C9FF1D7ULL, 0x505FF7A02563CB19ULL, 0x0A723121A51C6BB0ULL, 0x632F2706D1A3CAFCULL, 
            0xD1F60E7996B4DC7BULL, 0xE697600C55D15C1DULL, 0x876ADBB9DE94138FULL, 0xC542C49FA131E956ULL
        },
        {
            0xFB86417F2CE8F267ULL, 0xA1E7D066962C295EULL, 0x80EE6D6AC35E9514ULL, 0x17294448A8A09B42ULL, 
            0x4C02AA64944557B8ULL, 0x083C9B8D2120767EULL, 0xA4C00C6E2C719015ULL, 0x2EFAA6E5E146C442ULL, 
            0xEC19C5FF0DED32CCULL, 0xA52181274061A345ULL, 0x38A2B7D797C3916AULL, 0x6CABE3DDC324E5C4ULL, 
            0x1BC7E9677B34861BULL, 0x715B78F53FF7E396ULL, 0x581871F345D2CCB2ULL, 0x64FDB06B02755061ULL, 
            0x6331F51C6253B97AULL, 0x10A6104E176A1A30ULL, 0x4966F978A7910D5AULL, 0xAB02AFA58BDF0828ULL, 
            0x2583CEB0FF131F51ULL, 0xE92ED2688E0DC7B1ULL, 0x20E60D1CB15BB561ULL, 0x31B8AC4C0EDA2106ULL, 
            0x12870639F3C17AB0ULL, 0x7720BD0E01C510AFULL, 0xE984C16C9F9966ADULL, 0xEE50811C2F09FAC2ULL, 
            0xD7A31B0B0B7EFD41ULL, 0x64E9AE6F7FEADDA7ULL, 0xCC8E044C188F84DCULL, 0x6706D79960F40EFFULL
        },
        {
            0xF9DC876FD49DEEE9ULL, 0xC99FA5C7D3E04F2EULL, 0x60856A7927ABEBD9ULL, 0x81143CFF858C3689ULL, 
            0x333A14225CBA12B2ULL, 0x3AA38A0D1442DB58ULL, 0x90B64B270A7FC761ULL, 0x81324E1CAF72E44EULL, 
            0xA7605AF47CD041C8ULL, 0xE5B55C2CEC4214F0ULL, 0xFA8F4509D7B5705EULL, 0x6335B3AAC1297D96ULL, 
            0x40516D4FA7D4CE1AULL, 0xA4C5A6F2412F4A78ULL, 0x712FAFDB58C66F56ULL, 0xBCD6B0CE106AA9A0ULL, 
            0x760AB57C088E1ED7ULL, 0x18D0F172A8EC0CF3ULL, 0x557089A608279A61ULL, 0x9DBD8230CCCFE9A1ULL, 
            0x911C6E810A3806B8ULL, 0x515E1EF5907ABC48ULL, 0xC6FB77BE873743A9ULL, 0x2A78D7C329D5C2CFULL, 
            0x6D05AEDDCC237101ULL, 0x00C3939F9CAA0D90ULL, 0xF5843431B6793DBDULL, 0x8383D07E32050AD9ULL, 
            0x9A27A55EED330D66ULL, 0x82EEA9B8EF7CCA70ULL, 0x9CD4AE4840445743ULL, 0x319F5CF9B45404BAULL
        },
        {
            0x5504AC8898CCE696ULL, 0xF5EA96224125BD67ULL, 0x229F0D3E8C06CA7DULL, 0x909D2AD3C15BD3F1ULL, 
            0x29A5D7EC92B94435ULL, 0x52539ED308A65439ULL, 0xBB285363FE84C69BULL, 0xC43C818F7B1E9BF2ULL, 
            0x85FA8ABB7571E662ULL, 0x01B37402B5E2C5AEULL, 0x27AA210E612E33D1ULL, 0xCAC2631DA46FBA9EULL, 
            0x08C18EAE55A98FE4ULL, 0x6EEC3CF112157050ULL, 0xB9A4A4F6B28E3F7AULL, 0xAA496DFDDDBE7EF5ULL, 
            0xAB3E3AD54DA145F8ULL, 0xB1E533532C5362D5ULL, 0x71021D68947AFB24ULL, 0x8523EF4CCEF11146ULL, 
            0x982A3DA0B41AF00BULL, 0xB6B80161F7023673ULL, 0x372D2EE5F6CD962AULL, 0x9927EB79D80FBF65ULL, 
            0x804F32E95EFA0E05ULL, 0xE6A5AE7CE703F24CULL, 0xE2249F03D80BA240ULL, 0x867512CA9D21046FULL, 
            0x3CBCEABEE9417519ULL, 0x66CB6D2FA23B67B2ULL, 0x91CD086F1887498DULL, 0x9F07BD79549D941AULL
        },
        {
            0xD0974085DB1CCC35ULL, 0x9E8EA886B6EABD01ULL, 0x27AAC0C59D5CC939ULL, 0xEAAB01C72EE3836DULL, 
            0xF1C66A9B64BEDB1CULL, 0xF94124BFB2D60736ULL, 0xBC462CE16FBC6BA2ULL, 0x3FC07ACBFF3EB39BULL, 
            0x31EA127634ED5866ULL, 0x048B27276D52D430ULL, 0x7763AE226FFD59A9ULL, 0x164D25138ABF2EE8ULL, 
            0x9B33AF4E41DD351DULL, 0xD0146EE9B0CA1313ULL, 0x66BD6DE68C495E84ULL, 0xFFAC8CCAC366B99FULL, 
            0x9F3C4DDB9D28F6E2ULL, 0xF5CAF59C05A2DE4DULL, 0xED541DC37C6A7A1AULL, 0x5DDD537ECDA4D8DFULL, 
            0x1EF9662BA3A3A931ULL, 0x73653845D597F1E3ULL, 0xF08E13A578FA8534ULL, 0x516E365F0BF4663BULL, 
            0xA34473CD6D5C7357ULL, 0x120E335C250175D2ULL, 0x326B116793CC62FBULL, 0xD3A71E665535D5FEULL, 
            0xDE901BA255D1A8C9ULL, 0x56E5E41FDC3010C4ULL, 0xD474717FF9A5899AULL, 0x5627584FA07505E7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseCConstants = {
    0x83DF4F68B3B02CE9ULL,
    0x0C7470DCBCF3588EULL,
    0x8444D4B4214B2745ULL,
    0x83DF4F68B3B02CE9ULL,
    0x0C7470DCBCF3588EULL,
    0x8444D4B4214B2745ULL,
    0x0B44D896FBDBAC04ULL,
    0x8C120477C631A5BEULL,
    0xB5,
    0x51,
    0x81,
    0x0E,
    0x9F,
    0xAC,
    0x36,
    0x58
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseDSalts = {
    {
        {
            0x37BC970FAFC5A855ULL, 0x30518708DA755DBCULL, 0xF80DD9B23FC153D2ULL, 0x7DED691A725631DDULL, 
            0xA002D56A6A37C449ULL, 0x2F843A72E4A832D4ULL, 0xEEB92350ECA9FA65ULL, 0x2330F483B4C0A569ULL, 
            0xC8A97BA3013977D2ULL, 0x7D5BA8BAC98150F4ULL, 0x5B6F417658C35A21ULL, 0x92708060B884A18CULL, 
            0x46CA522E2AD6E811ULL, 0x0E5D8B3578177C41ULL, 0xF8F699C83BE6440DULL, 0x19C104CB60C66B34ULL, 
            0x11906646E2AAE568ULL, 0x1A6B203518AD360EULL, 0xF8704D803902DC4AULL, 0xEB9E53212BE32040ULL, 
            0x25EA718F828E234AULL, 0x68F4532F76164C19ULL, 0xB7F95154362D9B47ULL, 0x6B400B97367F3990ULL, 
            0xDC72D11F1994CEA1ULL, 0xAA9F87F2A0964975ULL, 0x9852CFDD9775862CULL, 0x2CC1EE99DF2296D0ULL, 
            0x889EF5FB3B006E8AULL, 0x57F42C9ACEE1F74AULL, 0x92798E0365B4A039ULL, 0xA36386D05BB5A347ULL
        },
        {
            0x5D3B485C5C10C958ULL, 0x86307FCD0B3D0E49ULL, 0x821CC35C7DBD427BULL, 0xA32BA6E28CE74523ULL, 
            0x69C4A44F4E1A4EABULL, 0xE80455AAFC72B64CULL, 0x0936FC6261AFCC71ULL, 0xB397B6EEC1EE8C3CULL, 
            0x47DE2502A307F683ULL, 0xD7496F34A8820734ULL, 0xF439694D782A5C50ULL, 0x739C6BEBFCF4262BULL, 
            0xDD68403385A22188ULL, 0xAE1B41BE1C2303FFULL, 0xC11D70E07182DCD0ULL, 0x6D2C67D3856B1E48ULL, 
            0x56AB456E1A57245CULL, 0xB5B469FBE41B7068ULL, 0x5ABD331A18190538ULL, 0x68C4EEB1714031C5ULL, 
            0x1F7C43B15E2C7D21ULL, 0x62FE87ED72BEE193ULL, 0x8B831107DB59CE7BULL, 0xA0A4902DB077C09CULL, 
            0x94721A989828A596ULL, 0xB97CA8675FAFFA73ULL, 0x0DCC0D82E8971C2DULL, 0xD89312F17282EEF8ULL, 
            0xE09325CEBE544F22ULL, 0x930E54BD4FFA77FDULL, 0xB53EA2E10C6406C5ULL, 0x4034B99465C82BFBULL
        },
        {
            0x7AADE8ED6F72C3B2ULL, 0x8FB582DDEC7E991CULL, 0xBC6B302C16C23653ULL, 0x8DE51B6E1CA238FFULL, 
            0x40CDE01705E3659FULL, 0xD73D3F68B5CB73DBULL, 0xE768C47377D761EEULL, 0x7C69AAFC010F75CCULL, 
            0xDD4D447CA6F0B282ULL, 0xA85BD9FB5434C47BULL, 0x270985F1EE1FF5A8ULL, 0xE9FA7D17A5C13836ULL, 
            0x864D3FEE1CD3F440ULL, 0x6FABDAA1D710A09AULL, 0x8E95F756127073D9ULL, 0xEA3C05734B8504D4ULL, 
            0x9F1A1C02649115EFULL, 0x5F1C0B98C4F12321ULL, 0xB05CCFC7DCC8D2BDULL, 0x6B7B8AA29E72B1DAULL, 
            0xA1E873F7B958737AULL, 0x6ACED1DE4D987C24ULL, 0x0C5EE5E3C349D4A2ULL, 0x4C596DE51BCFBE9FULL, 
            0xE21153B8E3461DFEULL, 0xEF5FA8A179B1B3F6ULL, 0x12903F5FD194F8BEULL, 0x1777E2F4A7ED0F37ULL, 
            0x8D4C26C2C7142828ULL, 0xEDF0BC6AC737C5ECULL, 0x0C1B28A3BA467E4EULL, 0x150AA2B875F5A7ADULL
        },
        {
            0xA060B312978ABF60ULL, 0x3B220CA91AF2B70DULL, 0xB74CA9096A38C192ULL, 0x46D6F806CA1786F1ULL, 
            0xD0EF5CBB5DB483E4ULL, 0xCF6266493B952676ULL, 0x9E5D15E284820B30ULL, 0x1E060FF3039F256DULL, 
            0x4ABB166A3CD8993BULL, 0x8BB1A322F66DF207ULL, 0x9A64C9ECA725171DULL, 0xA4C0D634265BD33CULL, 
            0x3766CD593E796298ULL, 0xE98CF3B5851EF04DULL, 0x1AC03399CA585507ULL, 0x2B064EE0388493DAULL, 
            0x8A8084510EB4EB70ULL, 0x85E6E0E7642AC7F0ULL, 0x77B997C35FE8D2AFULL, 0xF5095A4E089A340FULL, 
            0x0629A6C499B993C5ULL, 0xD6E1E32B812E94B2ULL, 0x29895920A0D15408ULL, 0x80A3BD5F1B123725ULL, 
            0xC58F5AF1205C98F7ULL, 0xC4D290FDAB5F1C16ULL, 0xA074E32C7A794E85ULL, 0x93F6F21B0B750F9BULL, 
            0x6F97A8EEA21E8506ULL, 0x8C1934BC9682EB74ULL, 0x45453C625A183E01ULL, 0xB7638C4C03CD06D3ULL
        },
        {
            0x8000EF441285D243ULL, 0x21DF1CD7E02DAEDCULL, 0xB28ED771895178E2ULL, 0x93A995FB6C981EAFULL, 
            0xC23CD63A5ADD18E4ULL, 0xE370E9C57418A96DULL, 0xC0760E544DB5E450ULL, 0xBBC452933432B5EDULL, 
            0xBB2879B281AC51DAULL, 0x255A336222512CA2ULL, 0xE6F2BDC9C5CEA850ULL, 0x89B7B3670EB823F8ULL, 
            0xF73B1CC7DAA3D2C1ULL, 0xB0D92DD3A9D8FB46ULL, 0x3452BB881EAD5FBDULL, 0x72135A7A41DC8B3EULL, 
            0x90F3C6C8AA91D95EULL, 0x055F70F45653B8BCULL, 0xD6C35B72B017585EULL, 0x1B794E29271EC388ULL, 
            0xF7A7E144D5EB2C02ULL, 0xE682525CCE80AEAAULL, 0x54055BBA4BA2EE8CULL, 0x2C64F9EE3AB062ABULL, 
            0xB6689D2F51F1E264ULL, 0x0727BFD909403DCEULL, 0x4AD7EC6ED4BD1688ULL, 0x7B46B083085625BCULL, 
            0x785C2842BA9AA5DDULL, 0x676F1A98645345BBULL, 0x5E4721569FFE104CULL, 0x5F42328CCF120924ULL
        },
        {
            0x3AD218178681425BULL, 0xA6C2E4FDFFF3EAF6ULL, 0x208BCA8A1C995D54ULL, 0x9DC6FFCB63F75280ULL, 
            0xD0F6A61A95D17194ULL, 0x9C4E9195E0167F58ULL, 0x0855850214467748ULL, 0x33D8EF4BBFB28E12ULL, 
            0xC9D29599441FA729ULL, 0x05C6DB4283139861ULL, 0x076BD28BB783EE22ULL, 0x44A571352ADE4BE6ULL, 
            0xE393CE91249FCC71ULL, 0xE32152FED214393DULL, 0x879883EE9B22750DULL, 0x18BCB15A33FCF5D0ULL, 
            0x44476DEFFEEE8BA5ULL, 0x3B30CF7F2E23EB90ULL, 0x3A8F3995186E3B9AULL, 0x27EBAD9FE568207BULL, 
            0x1173B5F9280C22E7ULL, 0x0EDE4E0A969E661EULL, 0xB2E12C164E2953C1ULL, 0x5719C6427DC37245ULL, 
            0x2AD5E060E3DB4F1AULL, 0x7A07E678936241D0ULL, 0x1F43468C5B191412ULL, 0xE5BB2C18D853D1AEULL, 
            0x46D63E95A7655133ULL, 0x8512BC930387E8B3ULL, 0x0F2B373135872613ULL, 0x5D8523B0607382E0ULL
        }
    },
    {
        {
            0x9A7BC11B9B762EE7ULL, 0x79C1AE30CC1EE9ADULL, 0x3D347F9AC5016FC1ULL, 0xE259060057056BEBULL, 
            0x95579346DFD07A1FULL, 0x6AA042EF1693413DULL, 0x8E7FF5E54700C12AULL, 0x96655F0524E47489ULL, 
            0x37C163B50FB72140ULL, 0x5F8A023F9A52C905ULL, 0xED8E96008D530B7EULL, 0x07F59D1BC1282D65ULL, 
            0xEB4F18FA945DA6E6ULL, 0x773C802E58387DFBULL, 0x67EE28927C6819D3ULL, 0x4DEEB32873A01CF9ULL, 
            0x41B23BC904F02C83ULL, 0x15E71DA0328B4AACULL, 0xF293D3598A321762ULL, 0x307E0C0DB4252593ULL, 
            0xC77F4ACE9FE4913CULL, 0xD0BB0E021C8DB473ULL, 0xE85E41B5D47EC3B4ULL, 0xDC8109AED6FAFCBBULL, 
            0x110F06E8AF7D1747ULL, 0x14BD9941C0556A96ULL, 0x103392C5EF1BF793ULL, 0xBE00DC168AA0BCADULL, 
            0xCD89A0FB2067C527ULL, 0x888C714B29DBEF59ULL, 0x1A4076AE2535CE8EULL, 0xE35D98FC922A54CDULL
        },
        {
            0x644996488A37F188ULL, 0xA31734B15246575DULL, 0x477F78E0E1BB389CULL, 0x4BD8B9A8D27A73A9ULL, 
            0x9EB59C62461370A8ULL, 0xD68F497BD60574E3ULL, 0x2B836AA27A361C52ULL, 0x010FB7995B7E2C41ULL, 
            0x230F7D2CF3AAB81DULL, 0x0C1F9030FF1AC12FULL, 0x82BE368EC0149DA3ULL, 0x4B592CDF10A70F78ULL, 
            0x5CEF7E9E1651809EULL, 0x5CCB29BF1D688AD2ULL, 0xBDB983D7E69A14D2ULL, 0xB6267F0799160560ULL, 
            0x0493B8265AB8330EULL, 0x67E01105E679B1C1ULL, 0x38C86A1BA5D00675ULL, 0x4FEA607E80CE39AAULL, 
            0x708044D80C690505ULL, 0xE3BC59514F7DB459ULL, 0x2C3A91F91FF4169FULL, 0xF2501E139FCDF844ULL, 
            0x7BACC62ED6DD1ECDULL, 0xAD38EFF29E9B39C8ULL, 0x64C719EF4096E4CDULL, 0xC72D261EC5238260ULL, 
            0x07C01E89F116701CULL, 0x43B94CF7AA86627CULL, 0xEF5B55161ADBC447ULL, 0xB4AEAB9EA4E50489ULL
        },
        {
            0xCE20CDC7D53EA445ULL, 0x27EC3B4807FF6447ULL, 0x57DBB4B2275E91BDULL, 0x0B57A98F094416CBULL, 
            0x49ADE6EF974F5A04ULL, 0x365F8F26A924590BULL, 0x661C69EC7E325B01ULL, 0x29E35F70D6AF4CECULL, 
            0x749F919FDF8A1A44ULL, 0x1E23337A09267606ULL, 0xAC3B6343055F9716ULL, 0x9A479EF9DB184799ULL, 
            0x7A12BB44231808FBULL, 0xA6130693935D1B0BULL, 0xEFB123AB8FF3FF96ULL, 0x84A0C83D0C526AECULL, 
            0x070E16DC2680690BULL, 0xA321224B0484FABFULL, 0x7069B491298BF1D6ULL, 0x96FCA199400745D1ULL, 
            0x4EC95216E5BDD8BDULL, 0xBC6D892D9D16C922ULL, 0xE49DED040F6A8CBEULL, 0xD3C55BB3AFFEE0E1ULL, 
            0xA3B8A7891FFF1271ULL, 0xDEEEA0D95A0D3FB0ULL, 0xFD2E8A31FA7C7B99ULL, 0x09A3A1825E0D214CULL, 
            0x58BC7F4534EE74BFULL, 0x6E82BCCBBB540846ULL, 0xFEEBAC211F4026ACULL, 0x38A6D05CFDD9E5A6ULL
        },
        {
            0xAEE687F390FFE951ULL, 0x246BEA6EDC96073EULL, 0xC198F60B6BEA260FULL, 0xBBB0210149CBF85CULL, 
            0xE89B685DEAFD0A74ULL, 0x3F3E16C1D5B09D35ULL, 0x2782C0E35F0698DDULL, 0x881624CD10387723ULL, 
            0x61730DFCC4E00CEAULL, 0x6BE9FEC086E7EBF1ULL, 0xD55A52107D0E7F50ULL, 0x562FBE9A9FB4C7C0ULL, 
            0xF3D8717B07BB4700ULL, 0xBE38E4D280561BC1ULL, 0xFDA3F126CCF92E32ULL, 0xC32BFEFF85E48780ULL, 
            0x667A2F41EBA1412FULL, 0x1919F8B0128FC9F8ULL, 0xE3C31E18AC9637DDULL, 0x9D4D990B56569043ULL, 
            0x324687CE38A05518ULL, 0x8ADAEB4BC00DDDC6ULL, 0x6483B385E51CAA1CULL, 0xE93C9ED84C905541ULL, 
            0x388B6925AB5326F2ULL, 0x4BC6B6B6C4BC8070ULL, 0x2BBC87AA688370E8ULL, 0x6CEADFCF577ECFFDULL, 
            0x4717C9FB51D90002ULL, 0xAFEDD3F441A83701ULL, 0x73B57DA730E13C79ULL, 0xDAED5D402D4CF5BBULL
        },
        {
            0xCB8A0D18425C4EF2ULL, 0x8BD82FEB8CA79F94ULL, 0x2B4EE13F789F93B4ULL, 0x0A0E784CE1726C10ULL, 
            0x868782D6A755B03AULL, 0xB1E2742572BDDA43ULL, 0xBE5BCED7F1BFB044ULL, 0xACDEF93E4DD36B90ULL, 
            0xF78BB9EC2BB503B3ULL, 0xC15952FD1A7ACF05ULL, 0x431B2799D70D0278ULL, 0x8BFCB600EB79ECE2ULL, 
            0x62D5190B70B94D5FULL, 0x3429419B35CA27A3ULL, 0xD907FD50DCA49F79ULL, 0x6C38AAFEB96DD015ULL, 
            0x6BDDCE01AC3BB57AULL, 0xEF212054399406A4ULL, 0xF391DBFE0C0F3300ULL, 0x2EC8474056AA01CCULL, 
            0x5542F369115C3640ULL, 0xF7336043F737C3DCULL, 0x3CFC69F9567E5011ULL, 0x75BAACFB3ECC0821ULL, 
            0x34E8187A56AF359EULL, 0x2876F0D241BA186BULL, 0xB8AA10A8A330CF67ULL, 0xA1F8CCFD25F67C30ULL, 
            0x3A14218995B94CB9ULL, 0x891DE11EBA2E4BCDULL, 0x61424081B1B2FC84ULL, 0xCC5CD97A59F91FF6ULL
        },
        {
            0x1D24EA9C8467CF1DULL, 0x8C2F96332F423BD2ULL, 0x0EF0E4B3ECB82B79ULL, 0xE03D92C5730C3C9CULL, 
            0x093D7B5BF90D696AULL, 0x9FD29CEA893B8091ULL, 0x39D5995245DA5CBBULL, 0x49E75536C2B95D32ULL, 
            0x65FDDBC7D8CA8B69ULL, 0x1DE1A26906771FF1ULL, 0xB8B052AF576A166DULL, 0x93CB125CCD83C89EULL, 
            0x92AA447115B7ED1EULL, 0xF3CE8EC5C0D65C92ULL, 0xA6743DAD95BF6482ULL, 0xDCF2ABFB7BF14185ULL, 
            0xA06B05F33D942FB6ULL, 0x305514D0ABCA62C2ULL, 0x33261FF38725D3F3ULL, 0x4E6B8166A50ADB33ULL, 
            0x3C70259C8A94CDCEULL, 0x13B9F330C5B5E237ULL, 0xBEBBC0C808898127ULL, 0xDA46437053543AF3ULL, 
            0x511EC375634464A6ULL, 0x3F9E770312BB6510ULL, 0x1382802A8CC8B0A2ULL, 0x6FDFBE59859928D2ULL, 
            0x6975D8599384B8C7ULL, 0x617872AEE3F3D59DULL, 0x0CE911E228858D10ULL, 0x9D9A221A738ED024ULL
        }
    },
    {
        {
            0x34A21B22A76643D7ULL, 0x32EE348398E45E6DULL, 0x31A10235B41A1698ULL, 0xEEC9E8C324DCC085ULL, 
            0x5AD828EDAC4340B1ULL, 0x81566A883C3958E2ULL, 0xDEE6AE8B7D38B00DULL, 0xAD2524B4F815DA5AULL, 
            0xEF5CAA272BA51147ULL, 0xBF50667749D10313ULL, 0xDC248DEA294080F2ULL, 0x0BA9EE979EFED9C2ULL, 
            0xEC9F27DCE1E3988AULL, 0x70D6937FFF75EAD0ULL, 0x0ADA11D9A75EF399ULL, 0xE209F5BB61E70B68ULL, 
            0x1FCC5BA4ECFBAA17ULL, 0x4B12AC18194E4000ULL, 0x212EBFAB275B8DB6ULL, 0x49364226FD1E98FFULL, 
            0x44FF502A70E7D284ULL, 0xE2146717405A8BF5ULL, 0xC667018BE5F5EF9FULL, 0x9EB599E60E75354CULL, 
            0xD07F51BE1222375AULL, 0x2591A42BF5425544ULL, 0x09AAD0E668D4BCA5ULL, 0xD2082716D1EED4C4ULL, 
            0x06EDA67FF78DF0C2ULL, 0x2CE4D2FE83065B44ULL, 0x4D136843AF3B8B15ULL, 0x2C0BB45C63B180DCULL
        },
        {
            0x87F319F26DB7E1BAULL, 0xCD93E802618D9C93ULL, 0xAECA731534BF76C1ULL, 0x0A8667A76F7D6856ULL, 
            0xB6BB78E0DEA51237ULL, 0x686E07C8E62224F0ULL, 0x37006B01D1E6886EULL, 0x2B745EC694113E94ULL, 
            0xA22F030C9611CDB5ULL, 0xCB8F70824B32AE74ULL, 0x59450FDF946B4A06ULL, 0x81EE4EB014125044ULL, 
            0x523CB60DBF2595ECULL, 0x3110030A83AEE078ULL, 0x4EA0D8D7041000E2ULL, 0x9F9F49A775871D6DULL, 
            0x29EA1819DC60DBC4ULL, 0x7F4182C280C349C8ULL, 0xA30096F4FD463D00ULL, 0x0E32DE0188ADBDD9ULL, 
            0x877D45EE0210937EULL, 0x20409B91BBA15211ULL, 0x499F3AC9DA6A06DEULL, 0x7D62CC8E9FECFF43ULL, 
            0xBDE2A99E44754A8EULL, 0x39333FF57C2750D9ULL, 0x1B73FE61D2ECA627ULL, 0xCAEE377BCF7BAD34ULL, 
            0x89C21284B939AA30ULL, 0xF6FD4625C8DA5CDFULL, 0x006926B8FDB9BBBFULL, 0x668707E27D2F92F9ULL
        },
        {
            0x24CCDBD3E47556ABULL, 0xB3B058FE9907EE83ULL, 0xCC80058E0BAD6042ULL, 0xF2F84ADFDB6CDEF3ULL, 
            0x2192F1C20482C4C5ULL, 0x41D2D748681A1E76ULL, 0x87F60A4C31967D0EULL, 0x7B9B9150F900D00FULL, 
            0x6F44EDA1420EA01EULL, 0xC7C4250FA93E4281ULL, 0xA0A29E03E72B8049ULL, 0xC6CACD668F2E1B5EULL, 
            0xB6F08F589C91C5DDULL, 0xEF93C58EC695B5C1ULL, 0x882B552A6B358631ULL, 0xDBE5B2C70A224EF6ULL, 
            0xBA5881900C10151EULL, 0xB25FBB98C8E905A3ULL, 0x122F06C27B24D9A8ULL, 0x7FC2C75AC4351974ULL, 
            0xD32BBA6A2FE60B99ULL, 0x58EE8DF854E758C1ULL, 0x880551451ED52348ULL, 0x97C893504D98EC4DULL, 
            0x5019581E03F6FE18ULL, 0x343CC7B4B83FC4CBULL, 0x67FF4A4FCE19A009ULL, 0x1DA7651F4EB989DAULL, 
            0x4BB8BBF09EF9BB34ULL, 0x82E7D5F39899FCEEULL, 0x9B2715385B342D16ULL, 0x6860D5B57939EB22ULL
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
            0x96968255DAFF5178ULL, 0xAE5EBDD0EF73449DULL, 0xE2D196664C4C5D17ULL, 0x04B1D488BD580B7DULL, 
            0x3550392BC1F80C8EULL, 0x73EB8DA75EFA6ABAULL, 0x256C49762188275FULL, 0xA003DF3695DC6CE8ULL, 
            0x168B46D4596C6307ULL, 0x1C639D9907B58C7AULL, 0x5F4715FDEB4E92ADULL, 0x35A81A3A1AF532FFULL, 
            0xD7FB8045E45C1DB3ULL, 0xF037395FCD2D016CULL, 0x4892E04510CAA37EULL, 0x2091F7CAC5D46290ULL, 
            0x2D40784018A2AEF8ULL, 0xFC1CEFA8AA21F27AULL, 0xB62652B8ACACBFFAULL, 0xBA9DA91AF4AE591AULL, 
            0xA37035D5EC30374CULL, 0xE740329DF8BEF074ULL, 0x561DF517DD206727ULL, 0xA9FDF0ED9BB90035ULL, 
            0x254DFD8AA2D75828ULL, 0x58504AD20FCCD079ULL, 0x6FE124BAED1359FDULL, 0xEAA3BA10321E49D6ULL, 
            0xE942BDC89BB92998ULL, 0x9812542055CA4658ULL, 0x26E9E14BEAC7ADC5ULL, 0x380741A8C15668A6ULL
        },
        {
            0xF6AF6CC5349F06ACULL, 0xED35A78A573D5946ULL, 0x5073C12145D4135DULL, 0xD22A976C6B81CCEEULL, 
            0x72187C7E56DE5B61ULL, 0x9B1101D5A0FC9681ULL, 0xB4937043C0F668E7ULL, 0x145AF85C3CEB915CULL, 
            0xE9D4DC811670ED38ULL, 0x886A2D60FA0D142FULL, 0x8EFB17E9F70D42CAULL, 0x95808743D661B175ULL, 
            0x105EAB13149B4508ULL, 0x553CB7500C74495BULL, 0xD7339DB5953ADA20ULL, 0x93CA8850B08A13BCULL, 
            0x6B73AB0B6CB14F02ULL, 0x20C75D1BB0372ECDULL, 0xA9A14103E87772E3ULL, 0xD09D57831F7FA487ULL, 
            0xC2FA78BE2DF6E4DEULL, 0xF262C7E5EDC9900EULL, 0xF617F26491846695ULL, 0xC33EA2F93B0E0D83ULL, 
            0x8E65C43210ACCF2EULL, 0x9711AC11EBF7046AULL, 0x7539CDEC7F6114E9ULL, 0x0A9D26B20C869CBBULL, 
            0x7486541DB397977BULL, 0x3E6E7D69D0F045C1ULL, 0xCE6643C4750F6744ULL, 0x55394ABAF88C6095ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseDConstants = {
    0xF8D75C288D6A33FFULL,
    0x7370A26D03FBCFC9ULL,
    0xBC97ADAC7BA7CB34ULL,
    0xF8D75C288D6A33FFULL,
    0x7370A26D03FBCFC9ULL,
    0xBC97ADAC7BA7CB34ULL,
    0x50C9BE7635DC79EEULL,
    0x3D0ED7ED1EC99C0AULL,
    0xD1,
    0x86,
    0x75,
    0xDD,
    0x32,
    0xE2,
    0x12,
    0x38
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseESalts = {
    {
        {
            0xA71C29D15EEB18BAULL, 0xD10B2CF358E244DBULL, 0x532DDDA10D0C1A9BULL, 0x77CD2CC0E185D773ULL, 
            0x28A2202E32506D68ULL, 0x2217EAEBD157CD04ULL, 0x3ED325461533BDCAULL, 0xABBDC8828710DA94ULL, 
            0x207B253E68B6F679ULL, 0x6AAFE09FB19185FAULL, 0x7C0C760534B9621AULL, 0xE0704DB8EA250189ULL, 
            0xE50014023DACE1AAULL, 0x62199A7119D6EEB3ULL, 0xA82A7DEA190CF033ULL, 0xB7C8D54168740C60ULL, 
            0xF2422AFB3B3771ABULL, 0x11BB8B8985130317ULL, 0x34B90A0626F98A71ULL, 0xFACC1F9E2E4EA344ULL, 
            0x5456F40CF0BF87DDULL, 0xF72202AC36BD3294ULL, 0xBF4F0DD66D1E9BEBULL, 0x65D43D6B6BEBACFAULL, 
            0x9982C507EE2E2FE9ULL, 0xAE4250591B87E5DFULL, 0x56231AC512E9D985ULL, 0xFEC1C47E1C265F69ULL, 
            0x164C41468F2B8266ULL, 0x004FF7A0D454701BULL, 0xF1D0229F81607FBEULL, 0xE4F9C95E56A89B8BULL
        },
        {
            0xB5C1E891AE9BFE57ULL, 0x2A855FD5F672ED10ULL, 0x6DA92B567FB6A370ULL, 0x06AA7535D92962CFULL, 
            0x34EE607C37FF271BULL, 0xBE3AFCFDC73AC4BFULL, 0x28F11F2D814C5BE3ULL, 0x56B6736109C16052ULL, 
            0x10190ACAD5D00769ULL, 0x25B1A3BFBF35E6D7ULL, 0x0639FB35B4F709A0ULL, 0x3A86741027E41D65ULL, 
            0x298CB1FE8C18A53FULL, 0x1827A76B1EA158C7ULL, 0xA4E0F29A2B386ACFULL, 0x5CA4CA284E0B4006ULL, 
            0xCDAFB3073ECD5A1CULL, 0x44127A0E041AD1F0ULL, 0xAEC464974121B206ULL, 0x4DDEBE8571A450AEULL, 
            0x131A743713705307ULL, 0x72A5AB1B7EF41E39ULL, 0x9735B5ED48E5BA94ULL, 0x0A6259FFAC473BBBULL, 
            0x0C4302A7EFD017D5ULL, 0x8D1A8843ABBBB54FULL, 0x20D424958B10F259ULL, 0x98B7DFFFC459C98AULL, 
            0x962E914EFF97D445ULL, 0x07BBDB1A4BDB6328ULL, 0x11CFE246264951B9ULL, 0x0DE6A36672111897ULL
        },
        {
            0xBE860AE680F61055ULL, 0xAB8F9057527D91FFULL, 0xBA654C4A18F98CFAULL, 0x74FDD9EB520CB0ABULL, 
            0x2D1860A3B36B302AULL, 0x24D84C24C8D9D2B8ULL, 0x1E0BDABC2DBD460DULL, 0xC47D641ECE75B4DBULL, 
            0xD981A8CA3511AA37ULL, 0x5DEF7F9104BBBA62ULL, 0x1238CF8A7DEC3DE4ULL, 0xFA9FC1A315A7463CULL, 
            0xFDA8D95BE0FEE5BFULL, 0x8C0D11F9F61C0A5CULL, 0x3D23DD8CC0F23A1FULL, 0xE3ADA79C4DF5170BULL, 
            0x491A481B59EE78C8ULL, 0xD1913592A3A82E9BULL, 0x5D2BAD8AB3C2F59EULL, 0x4AFFFD273A4BD9D1ULL, 
            0xF813D45E51446A3BULL, 0x844ED786479D92C2ULL, 0x9C5793A14E0A497DULL, 0x57A205EF265662D4ULL, 
            0x44465E086C1EFBD3ULL, 0xC983897B99B9B60CULL, 0x97C38ADC7219D261ULL, 0x550A8F677B3D9C42ULL, 
            0x2E05F556BB128864ULL, 0xCB38079DB49AD18AULL, 0x6F3CF67852D6990FULL, 0x0C76F9AAC98D7B4DULL
        },
        {
            0xB5AC52C96BEBCDDEULL, 0xA53F77D4F4E5FAAFULL, 0x03A338B0B985F77DULL, 0x6048623AE8EFA718ULL, 
            0xEB4F55C4A053B223ULL, 0x04B4ADA3A0292FD7ULL, 0x86788364FE0E6344ULL, 0x02DB44B863D7F1C8ULL, 
            0x12288179CE17701AULL, 0x5BC70C0B65B6987CULL, 0xB75395FBE7A4423CULL, 0x06E89EE2234AD6BBULL, 
            0x3CC610EBA18F4D53ULL, 0x18A661ACBE76244CULL, 0x80C57F1DB42F82BFULL, 0x5B3A46911F7D639AULL, 
            0x9B9923926D195A09ULL, 0x389152A8B4271420ULL, 0x8B05169D18C1DF24ULL, 0xC2347F50185B5748ULL, 
            0x03AB5CD9D0D3A5B2ULL, 0xA67CA7871FE2FF3BULL, 0x9742062375878078ULL, 0x73FE4859CAD18A7BULL, 
            0xEAC807B94FD0A8FAULL, 0xA8CAE619078462B0ULL, 0xEB633DB99C07628CULL, 0xD392D3B7F0CB217EULL, 
            0xDF0DAAE8EB5B4275ULL, 0xA8E9351EBD821D6EULL, 0x1E7E099A0059E401ULL, 0xDB12F90BC5E18074ULL
        },
        {
            0x0F2250BE6CCA13D8ULL, 0xA9FC31D6B63888CCULL, 0x4330AB290E474B0CULL, 0xE9063B394262D6CCULL, 
            0x28A6156F906E5055ULL, 0xA56F7AED71207691ULL, 0xB77A6341348341FEULL, 0xE965771EEDBAA5BFULL, 
            0x2A99C66C377FE8F7ULL, 0x6E4A1AE6C05B9826ULL, 0x4A426790121795F8ULL, 0x1BBF64AF275C3336ULL, 
            0xDD2EA822AEDBA784ULL, 0xF6C933A3B93927C3ULL, 0x258ADCE89735ECCCULL, 0x7ECDF7805F80E9F3ULL, 
            0xF4553ED634DF5C45ULL, 0xC83810748B039EA6ULL, 0x5FC1E6ABD0DE98F0ULL, 0xB8100B9C3C789371ULL, 
            0xE817502E9F39130EULL, 0x6E9512E9F2F90FF5ULL, 0x9F29AF90A33BECC4ULL, 0xEFDEF3FE55A1517BULL, 
            0x78394846ECA36348ULL, 0x5B35DC25C586A000ULL, 0x91CFFF0A47214090ULL, 0x9BE8D2F407DF4D2CULL, 
            0x73E7070C0609B1D3ULL, 0x6D5689B4DD4076EEULL, 0x775A4485A874ABD1ULL, 0x8BE276D4E865D5BAULL
        },
        {
            0x7DF5419BE65E9F3EULL, 0xCAEF34C85BB4C056ULL, 0x657B88C25BB8FD47ULL, 0x656F93563C100587ULL, 
            0xBE278B634680E9E9ULL, 0x615E6C42410F5900ULL, 0xBE3675E4326EC624ULL, 0x7330FD457AD95E72ULL, 
            0x042C14408E7CBB97ULL, 0x3E5D5798DFE4F69AULL, 0xA33FA48E4DAF4EE7ULL, 0xB875AD231743DE78ULL, 
            0x3C4A13514C54E620ULL, 0xBA437D33385831F0ULL, 0x29BA77ED9A352EB3ULL, 0x0091A2ED81740E88ULL, 
            0xBAA1D33D2A4AF544ULL, 0xDB2B9F2F85B2880FULL, 0xE1FE73E76135840EULL, 0x82A14990C65DAD2CULL, 
            0x2C2D59D7E359901FULL, 0xC82B8C232766FB5DULL, 0xB9DBC9CA4836CAF1ULL, 0x6C27757F62E9AE9DULL, 
            0xA2D5070BC873EAB8ULL, 0x3863D2DF54B21F4DULL, 0x8A5A89AAC685569BULL, 0xB5DB998C44E2D695ULL, 
            0x17E7D21803ACC8BAULL, 0x82EA04CE7523CA07ULL, 0xE8BB791BA0C45303ULL, 0x19FC935771710B23ULL
        }
    },
    {
        {
            0x24DF199E1832F8EBULL, 0xC86D3468FA4633A4ULL, 0xA3931AA43870D7F3ULL, 0x609842D2D5D4D6D7ULL, 
            0x6640B0CB41EF1E6CULL, 0xB44E0EB43DADD70FULL, 0x205AFC6B9F6CCD9EULL, 0x77C057FF657A0821ULL, 
            0x4426EC01F732E42EULL, 0xD8313642C8A4DA18ULL, 0xF62FE55D0145D372ULL, 0x22C744C8CDED2439ULL, 
            0x6220155DF24A1A6AULL, 0x900CFA91F9A5050FULL, 0xB8904BD74981ECFBULL, 0x8BC5418FC2942EA8ULL, 
            0x2325826357805A2FULL, 0xB443F324987AC4D4ULL, 0x631F91005113A8BEULL, 0x96F0D161F3153E7DULL, 
            0xDB6BA05247E9394AULL, 0xD73E319BD230A1B3ULL, 0x02F80BF1B8FDFFABULL, 0xF6AA44EF7AB658A4ULL, 
            0xF6CE90329BB38422ULL, 0xA7909BFED6F0C8AFULL, 0x144E993CD85ECB5CULL, 0x8DC6654A17A84D5AULL, 
            0x075302FE75F47B19ULL, 0xFE7457C786B816E9ULL, 0x194D390505991696ULL, 0x6AF0D9A3487EC950ULL
        },
        {
            0x41EC97CE35EBF6A4ULL, 0x27E988FB6F576154ULL, 0x7E211B0899DE74F3ULL, 0xB72D8DC59684886AULL, 
            0xA12A3FA55EE18B8CULL, 0xE75BC5503B30D6FEULL, 0xE8DCC9373D9FAAB0ULL, 0xBB600DD22256B204ULL, 
            0x4C45A79E524B6367ULL, 0x6F660DBDAFA01CCCULL, 0x1407C9EBF85040F6ULL, 0xAD4B766098E78C45ULL, 
            0xEC1AC21D2532CCFEULL, 0x23245A2C4D7ED6A4ULL, 0x015C144459ED201FULL, 0xA6B57241E9277B50ULL, 
            0xD72CCD254E2B4B75ULL, 0x9530FF80DF6548F2ULL, 0x685BD06EF1BA7AF9ULL, 0x53045DABF82E66D6ULL, 
            0x27430D7E4E2571F7ULL, 0xE9E2E37664FBD0F6ULL, 0xB285E78B3ADE19A2ULL, 0xE23064D99AB5882CULL, 
            0x6F07D8A918D4990AULL, 0x05A42294049A6430ULL, 0xD1355F6DC677C96EULL, 0xECB5DDF78C283393ULL, 
            0x61C3F1BD318AFB67ULL, 0x5B46CC465B707C7EULL, 0xDC17C91995112749ULL, 0x4D893EDCD6D81938ULL
        },
        {
            0x36A9668DCACAF032ULL, 0xD2DF9A5E75108C5EULL, 0xC61B952C7DB5AE13ULL, 0x777EF1C1CD4B9A2FULL, 
            0x792129180FABE04DULL, 0xC08DB01C4530473CULL, 0x17E4BA31CF508CF7ULL, 0x59AE44B76B91E5EFULL, 
            0x615A80A0351BEF25ULL, 0x4CBDEB2B88643205ULL, 0xF226802E65CD6759ULL, 0x263FD58513069877ULL, 
            0x77D9A60E690D3F48ULL, 0xCBBA88F84CE8B91CULL, 0x76BC173EE5900B1EULL, 0x61B4B2261323748DULL, 
            0x20A52B30552C9FBDULL, 0x80A9F6614E29F40FULL, 0xEE7AB8E9CFE673A7ULL, 0x7C39F1AB5DEA74A3ULL, 
            0x2008A67D05D044B9ULL, 0x976267067D9C3E6FULL, 0x657D3CB7F162E762ULL, 0x362296DA65A76512ULL, 
            0x658B93A3107FF8C0ULL, 0x968D7CC13A304D94ULL, 0xC9B31161E1F82759ULL, 0x171D8E7AA019A429ULL, 
            0x4A9BF429AA6B1897ULL, 0x107F9A35C10255C3ULL, 0xC19B52CF5F5E2F50ULL, 0xBAC946B64792ACA8ULL
        },
        {
            0xB7478F7A8570ED4EULL, 0xD2F3335618706E8BULL, 0xE10044631B1D9711ULL, 0x55146EEECB829FD0ULL, 
            0x7DBFFAB39D43EEE4ULL, 0x8859435F178D44EAULL, 0x585E06254032BA90ULL, 0xA70BA16B369523E0ULL, 
            0x5222D0916FE232AEULL, 0xA445F71B285F2F27ULL, 0x401E702A0A30D6C9ULL, 0xDBDA4A15AB82C031ULL, 
            0x714CCD884EA679B6ULL, 0xFDA237602D3F0425ULL, 0x05710BBD06245E06ULL, 0x8BCDC922AF5EE5FCULL, 
            0x406BE9E6E45ADFE8ULL, 0x8979748351FB1429ULL, 0x88412D86D1DA00F5ULL, 0xA80ABAE248396996ULL, 
            0x39A55210088410C6ULL, 0x181C3207EB77D6D6ULL, 0xB220F54D4F4608E3ULL, 0x6E5EE6DC697C2511ULL, 
            0xE7C54F8C272EDB25ULL, 0x9C80B3E2D827C2C9ULL, 0xD70A5E77A7086CA8ULL, 0xFA9C3AC0120E49EAULL, 
            0x58C64EFC6C7061B5ULL, 0x5FE0BB60AB482CD6ULL, 0x29A5238EE97087B5ULL, 0x0E055348FA7F2283ULL
        },
        {
            0x4C7757A60FE5956BULL, 0x425414E9A947570AULL, 0x8FEDF13CD5F1811DULL, 0x6BE12AB9C3930A9BULL, 
            0xE8DE3463CDE805EFULL, 0x110017C7E751A831ULL, 0x424AD934427B96DDULL, 0xB2443E074F8AD206ULL, 
            0x794AE6619ED6A117ULL, 0x7CFB6B0E2A040045ULL, 0x058BA62FA5155BCBULL, 0x67311C126E2D72CDULL, 
            0x7A85BF9E75B2F98FULL, 0x33C42AB66C063370ULL, 0x3C2707A75E1497E1ULL, 0x741D587DC6640469ULL, 
            0xF49A21815F240C2BULL, 0xD9DF943516C040C1ULL, 0xE9EEB7B52A617D24ULL, 0x1F3B6AA6706489E5ULL, 
            0x17F9FDC741BD720BULL, 0x052AB2FF888493E8ULL, 0xCD168BAFA613F0BFULL, 0x82BFB8AA47E2BFE3ULL, 
            0x5599C29EFC69C15DULL, 0x7B2985B9809E9998ULL, 0xEA02C7D106B654A6ULL, 0xAFDF28206E7D2BBFULL, 
            0xAF5722B08940CF99ULL, 0x5F52B58DACE59C35ULL, 0xCFE31B2D2A460E01ULL, 0x456F37A1DA332E1FULL
        },
        {
            0x56655450CC1FF300ULL, 0x9EB679BD870513D4ULL, 0xF6B18B0FBA726649ULL, 0xA6071512FEBA93E6ULL, 
            0x773018F4B6E70FE6ULL, 0xA71E92D732013EF8ULL, 0xDA028BB48BCE06F7ULL, 0xB1BE4A2578CE3DAAULL, 
            0x14A676B2D420EB14ULL, 0x135AC5D1E03A8BABULL, 0xA74E0050A57F5F7DULL, 0x9D76E25EAAF7687DULL, 
            0xD1B348D0E47813C3ULL, 0xB3EC37BB8E6138B9ULL, 0xF60E1D5B163E9A4CULL, 0x8F50A5086EB64575ULL, 
            0x34038103DEDADEB7ULL, 0x121E68352B4EC9BBULL, 0xB7A929D96FDC6F1AULL, 0xD0A2FC5A019FF375ULL, 
            0xCB394B588DFB9AAAULL, 0x8C62CB6A645226F5ULL, 0x6BCF1DCCCD62D8BAULL, 0xD57B275E656CC215ULL, 
            0x3B3350B8F32E1859ULL, 0xEF174598C04D2A91ULL, 0x168EA17733237BF5ULL, 0x350737E2EB73D303ULL, 
            0x3395EA43C35F6A87ULL, 0xB44CCC2879FA0127ULL, 0x70625735599F7B95ULL, 0x7B22C9D03F719648ULL
        }
    },
    {
        {
            0xC0601040D2FE29DAULL, 0xD179491F38BCC13BULL, 0x2CB06A14D57D165DULL, 0x86B074744A7013C9ULL, 
            0x7780688F208F7AFCULL, 0xC4DCF7FB1C519A32ULL, 0x3CE04FB7AD732822ULL, 0x5BC33F17E32BC88BULL, 
            0xBF0DECCE5CB9E66CULL, 0x08D17545209C3637ULL, 0x4CAA0D29E3D0F82FULL, 0x65518BA6C84D1B4AULL, 
            0x2C4D3A5294D26BC9ULL, 0x78A87EA2B01D261EULL, 0x330E177FE584D85AULL, 0xB959BF6B4F790081ULL, 
            0x6FF5B1004992A5A2ULL, 0x9F7A232503C5D8F2ULL, 0xA11A8E45B1AB28C2ULL, 0x9D9F33B93B51F735ULL, 
            0xCBD76939FDA312E2ULL, 0x6E50AA285C3BEC0EULL, 0xFF33D525D513C519ULL, 0x3C788E60E2099DD2ULL, 
            0xF702AF1AEA7EBF0BULL, 0x4A8D958EF245E206ULL, 0xC928F5535F9A17BCULL, 0x82E76A9E3AF7EA6BULL, 
            0x0476603B0EC1B545ULL, 0x302BE874E020F6BDULL, 0x1A67AE4C63CFB240ULL, 0x6BEAE0BAFEB3D5F2ULL
        },
        {
            0x0E1D5CC112837C80ULL, 0x8160AD465773A86BULL, 0xB37B46E3E95EE968ULL, 0x8A935F73D4BA1FB4ULL, 
            0x2FC4F70D50D0AD40ULL, 0x1148047DC69EB943ULL, 0x4C58152CD501E8CDULL, 0xCE29E4CB6202D8B9ULL, 
            0x4A2734CA60444B53ULL, 0xC45C55D8AA6518E3ULL, 0x29247D30D379D5FEULL, 0xDB9E03DC0325C633ULL, 
            0x6BFD52B1B86EF431ULL, 0x71744381D0EAD564ULL, 0x98F0BC32D265E91CULL, 0xE8158A8EA17C615CULL, 
            0x97E0EE75721C4507ULL, 0x68317A1F46272CF8ULL, 0x8BF3CC71AAA45F63ULL, 0x69622CF1DCE92EB6ULL, 
            0xFEB0BBD8230B9DC7ULL, 0xFB84B2AA4BC1A32EULL, 0x2220BE9AFA294C0DULL, 0x20A4DE79F9ED9AA7ULL, 
            0x4789B34B8A9024CCULL, 0x104BE21A95F23242ULL, 0x403B3A92AED21224ULL, 0x37B8800CACD91A6FULL, 
            0xEB25FDB1701D7D96ULL, 0x7FBF07307889F59EULL, 0x99D123054C47438EULL, 0xD49EBE60FEFBBF70ULL
        },
        {
            0x96484A57FE858521ULL, 0xD07CA1ED3A45175AULL, 0x172C55A12BA7CC01ULL, 0x60381CABFE82C167ULL, 
            0xB14B5D54E5FC4CC6ULL, 0x583E7EAE298E9C3BULL, 0xC5199E18768D6797ULL, 0xA5D649A87DDBA091ULL, 
            0x644E0288253FD8C8ULL, 0x03B5B998A7F5D79FULL, 0xBB9C158E816ECAE2ULL, 0xF50CD4482098EE51ULL, 
            0x6BB49AC24BF00921ULL, 0x3EDAB26FEAF310C3ULL, 0x153899B3BAD9E1D9ULL, 0xB5792B7952297FAAULL, 
            0xFD98F41801618BB4ULL, 0xAD0D11D822FC4E94ULL, 0x66D09D15CD356A0AULL, 0xB806CEE1BC21BAE4ULL, 
            0x1FF187CC194AB655ULL, 0x0B000E3588B8A32CULL, 0xE9C6D310EE80410FULL, 0xC00F2DD6FFD3BEB5ULL, 
            0xCCDEDA00627AF498ULL, 0x58CA37450885CB22ULL, 0x438560213836691AULL, 0x6A59ED1071144BF7ULL, 
            0xAAE6E73AA7E7C9F4ULL, 0xD475ED6A6CB12054ULL, 0x6606AC25B0644250ULL, 0xAB60BF79A99185A7ULL
        },
        {
            0x50CD7C556A2DAF73ULL, 0x4B71D8891B0FAD0CULL, 0xD844D0213F39C4ADULL, 0x1D7192643C1540A2ULL, 
            0xF04CFB1759E7E626ULL, 0x40284E0D230400AEULL, 0xEDE05F1CDF17CBF9ULL, 0xFC566D769431A37AULL, 
            0x179CC2AB94E3238CULL, 0x7ECD4A6827379A0AULL, 0x9D4933E2523E5AABULL, 0x2F3164352BDFB73BULL, 
            0xB160C0B515D9B668ULL, 0xB9A20099C3CEFB43ULL, 0x941BB81A578C3AD9ULL, 0x06D2E12CD432FF40ULL, 
            0x92A36BD051AEDCD9ULL, 0x394B922A9837842CULL, 0xAE368A0252DA02FAULL, 0x2BC0DD7130223FE1ULL, 
            0x245BF249A3EA3808ULL, 0xB7D4FF40FB147999ULL, 0x865B58F0429EFF83ULL, 0xEF3ED4C70E4EF86EULL, 
            0x938D154F64C4D81CULL, 0xB746EAD699F91A73ULL, 0x6547C956EF765C63ULL, 0xAC170E48497FCA90ULL, 
            0x2E83A60A574C100BULL, 0x2691C5BBEA5AECD4ULL, 0x5B47649E528BC0B0ULL, 0x6BDC6C496FF1D110ULL
        },
        {
            0x686A523D89D4E568ULL, 0xAE4FF052903E9906ULL, 0x1EFB34BB8CED4874ULL, 0xB492E2BF71AEE299ULL, 
            0x4EE47574658CD51CULL, 0x5BF1E60A323621E0ULL, 0xC63FB167C51CD39FULL, 0x2BF56F94406D26B4ULL, 
            0x8C3E5ECEE8E28F27ULL, 0xB924A83352F5BA3EULL, 0x978319B23C4AAEA4ULL, 0x166EE59E7BEB31EAULL, 
            0x058ABC2988B838A7ULL, 0x26469FBB59D87142ULL, 0xC723B2281CD2B7A6ULL, 0xB39BB91DAC9CFED5ULL, 
            0x7BDB6E03F0B9CFD5ULL, 0x1BE2BC87739E989BULL, 0xEAF38AA558535C00ULL, 0x94414868AE91C4E8ULL, 
            0xFE71D5BD0EF0A591ULL, 0xA894DB6A2A5C6E11ULL, 0xCE280FA7DB0A8130ULL, 0xC69E52A672603805ULL, 
            0x75D8AB9F9A2AD7ABULL, 0x0B4451F79AACB6DAULL, 0xEE22AE23138CED16ULL, 0x26F1F7B8264D8397ULL, 
            0xE28941E65B066658ULL, 0x7F249306E636DEADULL, 0x98744D0645E2D0EEULL, 0x5D192F80B361BD5BULL
        },
        {
            0x10B5712A25581644ULL, 0xD27B1E5446D4649BULL, 0xF2087F94EAB95427ULL, 0xD22CFA74E7361932ULL, 
            0x5463FF35E249C24AULL, 0x158DD8FC7987ED3AULL, 0xD4C7624DEB3D5D78ULL, 0xDA9B73DE373694CAULL, 
            0x6AD0614AE870B3F9ULL, 0x4FF80C066E337E4BULL, 0x55BBCD6D7FC96D2BULL, 0x939D8F80482FA198ULL, 
            0xD200987FEF050F6EULL, 0x1C04C6BD38450B62ULL, 0xA8AACF3D41F41A40ULL, 0xB82B0CE791EB3EE4ULL, 
            0xAC78082461874230ULL, 0x0DD30AB8E148652AULL, 0x4561714391260B24ULL, 0x867519E0D4198485ULL, 
            0xB2621FC21732FB8AULL, 0x75CE0565BD1D3A3FULL, 0xA724D6608EE3AC76ULL, 0x63698B9BAAB86F7CULL, 
            0x8A9AED9D29038A80ULL, 0xAA866E4B7DD71732ULL, 0x3E020A9E080543B6ULL, 0x16D85667592B7337ULL, 
            0xCC1369D790A6B707ULL, 0x4144CE746CD8984FULL, 0x5E0CA0302385CBEFULL, 0x8FCF331CFB06BCB8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseEConstants = {
    0x191DD5F799F47E10ULL,
    0x4D368D38B2D96794ULL,
    0x64E8B4B3D53C1FADULL,
    0x191DD5F799F47E10ULL,
    0x4D368D38B2D96794ULL,
    0x64E8B4B3D53C1FADULL,
    0xF362F83B62261C2EULL,
    0xD444E509ED43F5F0ULL,
    0x15,
    0xC0,
    0x66,
    0x1B,
    0x5D,
    0x77,
    0xD0,
    0x2A
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseFSalts = {
    {
        {
            0x72CDF2326585AD4FULL, 0x05D52D0CC33CBCAAULL, 0xE84A8F920E64F74FULL, 0xA476CBDC106B0A23ULL, 
            0x45CD4E63FCBA66BBULL, 0x6D568C9574063295ULL, 0x86131FF7FFB6E641ULL, 0xDA7DE583625C70AFULL, 
            0x4F276A89110F59EBULL, 0xE0BFBF057DC19105ULL, 0xB7B1ED594CA8787CULL, 0x5797B8DEA1470D65ULL, 
            0xDF20E32F4111B26EULL, 0x750524CF12B02E2EULL, 0xAB73E0348B40AC27ULL, 0xEFC9490CCE18243BULL, 
            0x51989EDB24B70994ULL, 0xAD5BAEC8DBA4743DULL, 0xBFB2B7DB84FA7CA4ULL, 0x7C346EE992062442ULL, 
            0x8E51872CF8E21417ULL, 0xA2D838625CBB133DULL, 0xE80A07452FB16AF3ULL, 0xF068D5FF066F6ABCULL, 
            0x0B149581C368B264ULL, 0x4D2C4B6A62EBE265ULL, 0x7314CA7C0B04B6C1ULL, 0x8A0A4D43910099A9ULL, 
            0xF589B59962157C17ULL, 0x2555F11747D353ADULL, 0x50716D49B2D9F9EAULL, 0x6D0C8D606F05C943ULL
        },
        {
            0x3677AEAE06DD2F22ULL, 0x16EE1A660349A5D7ULL, 0xDD39A1FF1F356197ULL, 0x1993CE8978704FC0ULL, 
            0x323382875DD3FD2EULL, 0x222F33A712E85DB7ULL, 0xAE10D1C683030A30ULL, 0x3FD993710C632898ULL, 
            0x4E3CA065B0FD41F7ULL, 0xF0FAC65828B0E9B2ULL, 0x49280BC2A8F7625FULL, 0x4D3AA00D814EC0BBULL, 
            0x0720BA6E0314CC86ULL, 0xBC70351D18B36E29ULL, 0xB53674BF859EAFDDULL, 0x204DBD8AA94DF6D6ULL, 
            0x44ED7D32C85234D4ULL, 0xB82F652148A06554ULL, 0xBA3C0E4A25E8989DULL, 0x93C2D3E42067E0A5ULL, 
            0x97E698F964A13454ULL, 0xA56B1EECCB9B7624ULL, 0xA74523788607521EULL, 0xCAC781372340C12CULL, 
            0x48756FF5043F820BULL, 0x469A819867CC7439ULL, 0xAC360942949AE913ULL, 0x46330149CDC76913ULL, 
            0xE428E20E4FA2704CULL, 0x2C8209EA9BB947C5ULL, 0x8D12DF610F0E719FULL, 0x6EF04E8B96883109ULL
        },
        {
            0xF71096A3673BA742ULL, 0xEDAEE95EEAFD111DULL, 0xF371AF8EFC32F43EULL, 0xED8DAAEAF41C80E1ULL, 
            0x3CA5373AA027E8F3ULL, 0x635B28AAE8D4C314ULL, 0xCE1919712A7BD8BCULL, 0xAEF178269308FAF7ULL, 
            0x92AF21966ADF8BA5ULL, 0x2CF9283ADF30D2C3ULL, 0x5DC0D7E657E4736EULL, 0xBECE648C06B9B6CDULL, 
            0x59297E0D29C19615ULL, 0xCBE62C0E487409BDULL, 0xD10972DB9A2881F1ULL, 0xB741053217F3590DULL, 
            0x351BD5BCC6314F3DULL, 0x234F332D1DDDA2BAULL, 0xCDCD59A3BE35BEDBULL, 0x92F10B552D98BA19ULL, 
            0x1FD3F8939F70FF89ULL, 0xC96D066F7CC5EC74ULL, 0xA06B72F8A700DB2FULL, 0x82260186390CEB85ULL, 
            0x2742B67116BC92E0ULL, 0x9F37F865ECD5AA57ULL, 0xD3A1DA1DB8E41946ULL, 0x2D1D3D085F503D3BULL, 
            0xFECA391C3ED8E207ULL, 0xBF5E48E7C6C57C39ULL, 0x7B4A0890C5772897ULL, 0xF19A75D443A85BA8ULL
        },
        {
            0xA5EA659548F947BCULL, 0x147AF344A94ABE1FULL, 0x38A0EBABCDB36CC2ULL, 0xAAB45D49A2734C0BULL, 
            0x5B9E23B0B2643FB3ULL, 0x3AE4194A224DA393ULL, 0x6848593DF67C60F6ULL, 0x533447ECC2063F48ULL, 
            0xF2BDCEA4ABEDA998ULL, 0x7161F1DCD306DBD7ULL, 0x45BE2C29AFB22DF5ULL, 0x7304DC125B4AFC0FULL, 
            0xB23B67FB01AD6F3EULL, 0x8F2B19BA91CD0508ULL, 0x25796C5A00550E82ULL, 0xDB23427E4B18001EULL, 
            0x7D5FB5E153E13FE5ULL, 0x17057B1220CC60BBULL, 0xA3FEC351CE8CFDCDULL, 0x63F16041A545F1F9ULL, 
            0x52BF4316312E54F2ULL, 0xE1621FDF635BDAD9ULL, 0x8949FEB365D1255CULL, 0x0DA824560EB39CBFULL, 
            0xA7F2A218A1AA6643ULL, 0xE950C4569CFBC89DULL, 0xF10C7351BA06C0BDULL, 0xBE5EAAC16A302257ULL, 
            0x0D1CBC32C4FCDB6CULL, 0xE304EEAF1B90B8D4ULL, 0x1344C318A18F1D2AULL, 0x0E2184778D8C1AF7ULL
        },
        {
            0x77954809504D34E3ULL, 0x3AD24D37BB283868ULL, 0x628BBBE5844CD230ULL, 0xF35E09A88574AE43ULL, 
            0x1F1F4BC896348B0DULL, 0x2F7EE889A7038D2CULL, 0x7FEDCD7643C84DC1ULL, 0x6737371814B0F9F3ULL, 
            0x85E43B2924783560ULL, 0x73ACB5BE40440606ULL, 0xFE8D5687EEF20075ULL, 0x8C4ED5CD978EFEA4ULL, 
            0x725822674ED14587ULL, 0x281244B384631464ULL, 0xEFB5471F681190F2ULL, 0x0B8E1720B7C6ABEBULL, 
            0x536896942D07D04EULL, 0x86D198E1BADA15B9ULL, 0xF8DE616F72A45042ULL, 0xA1F1810B1933CCE3ULL, 
            0x4D6DEDBE07C08B21ULL, 0x5485500DE08814DBULL, 0x19AD8699D506E710ULL, 0x7941AB873E055C1CULL, 
            0x9C39A5DF9895F662ULL, 0x00FD7365FA04C0CDULL, 0xC6A1A8507521F7EDULL, 0x5F69E8824363680CULL, 
            0xB82FCCA6E871ACF0ULL, 0x315E97FDA3313B3DULL, 0xDFA914D77FE5C435ULL, 0xC8B573182D4774FDULL
        },
        {
            0x42D7E3863E42B166ULL, 0xD3E7B24C1910CDBEULL, 0x9E4B570420CBD86DULL, 0x82F05E96F929A46CULL, 
            0x055FB66D6AC26024ULL, 0x6B6DA72A4CD81126ULL, 0x9D895D04B72460C3ULL, 0x76A3F4FF2786581AULL, 
            0x0D3808ED89E45FE9ULL, 0xC96A9C2A23DA7718ULL, 0xD17618C532F1B36AULL, 0xA9F232902D28C1FEULL, 
            0x1FA5C05B09C8BF8EULL, 0x269A79CD81B04B2BULL, 0x27D058A935798CCDULL, 0x5F028802FBF616E4ULL, 
            0x40EAC8396A2C1392ULL, 0xDABDCF47C89C7DE4ULL, 0x3D877CAFDE7C245BULL, 0x906DE3DE36601571ULL, 
            0xBD2CA8E04BC97BF5ULL, 0x13487EBBFBFC71F4ULL, 0x8107D5615C45534EULL, 0xD858D8EE190DCB61ULL, 
            0x304641CBFF053716ULL, 0x0CE3B144AB208220ULL, 0x5982D7E53DA47511ULL, 0x4F838AD49AD42C54ULL, 
            0xDD42A09B1B8C35F6ULL, 0x2A4F49B84AB4CCB9ULL, 0x5B73019AECC8E6D4ULL, 0xD651D4ABF6B9CF5DULL
        }
    },
    {
        {
            0xEDCF86923156E4C6ULL, 0xFCD56669FA284BBCULL, 0x5E786BCDC3F54297ULL, 0xF8D05335A05405D0ULL, 
            0xC91BA6E19AF2EA43ULL, 0x135351065EEA10AAULL, 0x433D7AF774B13E9AULL, 0xBC9FCBD5A8198683ULL, 
            0xB58C3E749988DD46ULL, 0xC6D955CE51AC5DF9ULL, 0x6A0071D405441B0EULL, 0x52A071E28595DEFFULL, 
            0x3DB9107E1E941A91ULL, 0xE963E240094DFEFBULL, 0x8ADB04E6B5F3237CULL, 0x9A88B79506D918E9ULL, 
            0x70D04C47F705EBC4ULL, 0xC30653E4A39DE8D8ULL, 0xD8A86950BCFBB3A4ULL, 0x80A4C8C25B5DB2E2ULL, 
            0x55C5F05D68D28CDBULL, 0x5CC392C42956B63AULL, 0x7ECB44552C8C6DFBULL, 0xD787058729F15C4EULL, 
            0x2331738634B80F7CULL, 0x6AC365FE7C96E28AULL, 0x1C6C729267DAFAC7ULL, 0x2E8796F406856567ULL, 
            0x656BF251FD31B5D0ULL, 0x9DA2A9DE38785D8EULL, 0x84CDD1F83265E14AULL, 0xB7D5058B6FF1129FULL
        },
        {
            0x399287480632B1FAULL, 0x21D62FD0D55352B5ULL, 0x9F4EE6BC02C01C36ULL, 0x836C47FE8DC5278FULL, 
            0xD0AC76F5343E2693ULL, 0xF1572E4AE5AAFB31ULL, 0x0DD118B25E03CEA3ULL, 0xE9E72DB005AB2A1BULL, 
            0x4FE353EDA28FDDC0ULL, 0x5E2F2A151BD173FBULL, 0xA0C44229E577328CULL, 0xD60FABA98BA36F4AULL, 
            0x2B89E99314DC600AULL, 0xCA48AAC044F2E3CDULL, 0xCD9C33EB6EBB178CULL, 0x0F8D13D2AF2F42D6ULL, 
            0x53C9A2F13ACCE35EULL, 0x10AFF94AB648EFFEULL, 0x6A7775990FBA1BCBULL, 0xE8569EB1224C7C84ULL, 
            0xBD8B987B7649DB38ULL, 0xF0C33311CE8EB98FULL, 0xA95E115C216CA810ULL, 0xA208D342932998EBULL, 
            0x2D871D59626DA807ULL, 0x69E786925F170F77ULL, 0xB28FC51BFF3388A3ULL, 0x1CC3AD705334DE02ULL, 
            0x5F092B9A38350F2DULL, 0x478AB033ACE0505AULL, 0x105EC1C519910606ULL, 0x15C916B00425530DULL
        },
        {
            0x7E426B3870649ACDULL, 0x9AC9CE4A843264E0ULL, 0x3A26D086B219FE41ULL, 0x08A8FE46C3053313ULL, 
            0xA725768D3DF2CA5AULL, 0x1172AD906FCC40C0ULL, 0x266631457F656CD1ULL, 0xE2D4D756B5DE2192ULL, 
            0xAC3DB9C747B77867ULL, 0xC9D3DF36657ADB17ULL, 0xE96D17574FDD621AULL, 0x0F91043F5D6CFAC4ULL, 
            0x27EFECF7417CCC23ULL, 0x7AC63F008ADBDAEFULL, 0x68F8B27D09F0994CULL, 0xE0047E1BBFEC57B6ULL, 
            0xAAA1F16B35198D74ULL, 0x6AB7D3F33ED786CCULL, 0xD7D292BB0DDB7ACBULL, 0x950FE092BD663A28ULL, 
            0x0731157DB55E2493ULL, 0xA225858616FD654CULL, 0x15B0E1AAB73B68ABULL, 0x226004B463849983ULL, 
            0xCEED787B0D263407ULL, 0xFBD9E478A3EA15F4ULL, 0xE52F0A9990F245F3ULL, 0x9F80C33AC76D30AAULL, 
            0x173F92CEADA625C3ULL, 0x5B76C670F54F6216ULL, 0x5CFE8199F18E7BD3ULL, 0x9A7327EF3F641058ULL
        },
        {
            0x521E0437F34A5841ULL, 0xA7D848D85CB3BB92ULL, 0xD14702946C810CD9ULL, 0x400B936B05081B3DULL, 
            0x9348276B6AC39A4FULL, 0x89EF29CDE261725DULL, 0xC1F8C24ABD12F29AULL, 0x449E23EBD1195956ULL, 
            0x6B8898B01B86D5D0ULL, 0xCBCBF79F8FE5FF43ULL, 0x427DCFE87395EA42ULL, 0x8C9EBAD7752FC2D9ULL, 
            0x07D9495B345F8417ULL, 0x6C970B73EFF96AC1ULL, 0x212DBC7DA5EA52A7ULL, 0x55EC4DD8E1E1D201ULL, 
            0x7291DF679E989DF4ULL, 0x45EEB561AA48E35EULL, 0x77248D1F3BD77D2EULL, 0x423526B15BE06F9EULL, 
            0xB98074B291932D24ULL, 0xA79D6107FE793D52ULL, 0xFF47E3197F101CFBULL, 0x9960D7E3E15F57E4ULL, 
            0x1E30CDCDC901EE48ULL, 0x82847DFFA0D46ED6ULL, 0x4E78A81FAE9ED7CDULL, 0x4072376A69FCDE9DULL, 
            0x183EA9CD5A99522EULL, 0x5633CA7BA103D5AAULL, 0x7004C6F817C8800CULL, 0xC7666CFC6A4ACB7BULL
        },
        {
            0xEE357E7B51FDDF53ULL, 0xDC15F1DC6550FC95ULL, 0x130BD9B1FAC02455ULL, 0x5CFA48E4934ECF36ULL, 
            0x35B7D2351FFF5CA4ULL, 0x3C631EFBC7C0A5DEULL, 0xFBFD04825A587988ULL, 0xCB5CA136C7E546C0ULL, 
            0x82331B1D764938D2ULL, 0xF766BC7D6CB179EFULL, 0x5CCDF05578C4449CULL, 0x2BAF44939286C793ULL, 
            0x03CE5E94EA2E1184ULL, 0x59F179397FEFD6ACULL, 0xD7495E765FE6303CULL, 0x79E68706BB2FB83CULL, 
            0x79364829D55BF2B6ULL, 0xA3D9C72877F06E62ULL, 0x6EED4A68C99BDE52ULL, 0x144283AC3E45D6CDULL, 
            0x93438E859C15B908ULL, 0x2D1AFFEAA965703EULL, 0xEC54184B0E83807EULL, 0x97E7719AE9D942F9ULL, 
            0x53BBB6DAFF1CC6E1ULL, 0x7BE7F49CC210C59CULL, 0x706E70123804B0CAULL, 0x9B538C774B161307ULL, 
            0x8BF5FDBA131D73CBULL, 0x9CE49E63FFD54C8AULL, 0x8B6D6592AFB120C3ULL, 0x45DEBB4FD817C336ULL
        },
        {
            0x2E9466FEE5916362ULL, 0x36C3FB8F70587899ULL, 0x780C3EC95836753EULL, 0x4B5273B646D14F06ULL, 
            0x477914E450AD8CBAULL, 0x80ED7AC45195D596ULL, 0xDE35D77BE399E42DULL, 0x50D0E67992662BB9ULL, 
            0x2536BED372102DCFULL, 0xC626D16C4FEC7B5BULL, 0x5E09AA77F11F8CC6ULL, 0x0013D0FB42F8E153ULL, 
            0x0F4394BC541DE3E6ULL, 0x4445175A22A608A1ULL, 0xD8AB631C6A88086DULL, 0xE6CE0372E6E0903FULL, 
            0xC126A4D23548430FULL, 0xB5C7F7D6B4785D6AULL, 0x99BE4E10A0600D71ULL, 0xB39EFC0E3CA60B37ULL, 
            0xAAEE7A703D6CF065ULL, 0x3328A8AABBDE5AD5ULL, 0x6BDC7B10FE758CD0ULL, 0x077306881C937C1EULL, 
            0x231705F3C0F543F1ULL, 0xC0A2F20221DC64CEULL, 0x5C081DC884360565ULL, 0xE021C7C3CEAF61D0ULL, 
            0x375803AAE1F03F20ULL, 0x27BBA25A31C6FA8CULL, 0x8F807AA64646EC6DULL, 0x74BED082E077B64AULL
        }
    },
    {
        {
            0xB6D88D6144915676ULL, 0x0C1E11AFDB36D694ULL, 0x22291DF9D696EE8CULL, 0xAA6E036DEFAEC859ULL, 
            0xCA93174280636359ULL, 0x65090160613B72B4ULL, 0x520190965A9DEC15ULL, 0xE2AC11C9311AD991ULL, 
            0x15EA3B536118BB48ULL, 0x021374479A99FDA8ULL, 0x49878A3A8DB5CDACULL, 0xAD0C44C33A3E193DULL, 
            0x2050EBA251825642ULL, 0xD6D12674854C182AULL, 0x54EFBE39AD9D9F75ULL, 0x4099705E1D814C92ULL, 
            0xB62FD9E9031C2011ULL, 0xE279FA3B8A69A83BULL, 0xDA88DF268978A098ULL, 0xE34B2A58ED067683ULL, 
            0xAE4E591543AB912DULL, 0x99B058C67110ED5CULL, 0x22B956451CBC8276ULL, 0xE9685BE58B026619ULL, 
            0xAFFC9A7E64168918ULL, 0xCD9DA86C7FA18EB4ULL, 0x674C638EE9F4FE54ULL, 0x8016C7E2D669A9BCULL, 
            0x665A3C9F57250A0CULL, 0xDBCFF6D72353DE08ULL, 0x283BF8AFC3A50BBDULL, 0x17DEFC2596999114ULL
        },
        {
            0x09B8F2D7CD1DF647ULL, 0x3C78DC0826E5D95AULL, 0x7218DDE37179A422ULL, 0xD274CF83031C8BF9ULL, 
            0x319685BF797F15B3ULL, 0x3F89CF44406F8008ULL, 0xADA4314E6FCBB990ULL, 0x398F4ADEEA1FEF4DULL, 
            0x45488565A1E70610ULL, 0x5DB4BEFD9B5BA92EULL, 0x6477F1DEB4EF289FULL, 0x405D63D0BCC03C12ULL, 
            0x0A74B837E0A80FEDULL, 0xECFC350C0B3B13D6ULL, 0xB89678F81A7877CBULL, 0x699AA92B48DA651FULL, 
            0x134EF73EA4A8AA92ULL, 0x96B0DD9CDBB3A5C5ULL, 0x2EED20D859E11829ULL, 0x4F60DA012B288124ULL, 
            0xF9CD3BA0B8817685ULL, 0xB828D60F33CD6641ULL, 0xCB360FA793701092ULL, 0xAF2D42F5A295D4D4ULL, 
            0x4F4D522346DFC356ULL, 0x3B5A2E19B3F0CA60ULL, 0xE649CC0C720CFCE6ULL, 0xBE0D1B5CFCDADCECULL, 
            0xE4F83F7C26F976D1ULL, 0x8F65CAAC1D662450ULL, 0x4AF42A74AAC66CF4ULL, 0x3DE3962CE8AF01C0ULL
        },
        {
            0xC4452ACDF92C1391ULL, 0x1BE32A20678E22E3ULL, 0x21A11CEC137B7C42ULL, 0xED90C739AF6771D9ULL, 
            0x1F0862BD31CF251AULL, 0xE72000DCA3B70B9AULL, 0xB01E8CE8A8AC7E6FULL, 0xB8DF3BBDD6DC2D3CULL, 
            0x5D06EAF602C48318ULL, 0xC28C9AC2108937F2ULL, 0xB517ACB730AE8B2FULL, 0xFCBFBA05AAFA54DEULL, 
            0x1601AA45DCD2E6BAULL, 0x5BF1F09DDF82C746ULL, 0xF473344078215E5DULL, 0xB3A453A8640F8520ULL, 
            0x4ADF0688BEDD1BB0ULL, 0x391BCA8CE7BEE895ULL, 0x89251A2402BF1F45ULL, 0xC773FBE49C304D24ULL, 
            0x0459A9E16C458623ULL, 0x97460285FBA1A091ULL, 0x1D9B169C584EACAAULL, 0x830316735540556EULL, 
            0x43D6CCC46123748DULL, 0x84EF28F51D8E0E73ULL, 0xF8F4B9F64C0E78CBULL, 0x1E9B6F3BB16CC21BULL, 
            0xBCBF8CB7F7998960ULL, 0x6C2B194900FE6978ULL, 0x340F12C43B2C13D0ULL, 0xF9F393ED9DC0025AULL
        },
        {
            0x314F7D974E1B1B11ULL, 0x555357677403A18AULL, 0x58AF075583BE9EABULL, 0x4D121AB35BDE276EULL, 
            0x0F4D9AA245D88458ULL, 0x0D9C04C22763026AULL, 0xCDDB6A5DA194880DULL, 0xC9234B235B108F6AULL, 
            0xA4E49639826A519BULL, 0xD9407BD3A431B287ULL, 0x059596735AB1E724ULL, 0x1E58782C359CC637ULL, 
            0x5CF634F917DA43B5ULL, 0xE7CE20C1DE8AA449ULL, 0x803341926DA2B9B3ULL, 0xB94CAC8D49926077ULL, 
            0xDD7B866C5AD22BA6ULL, 0x351705BA714AEC1EULL, 0x1C39DB7CDF0CBE99ULL, 0x61DAF1C9575B5141ULL, 
            0x2D0736F45C8BDA64ULL, 0x01FF557D49A2EC65ULL, 0x34C1A07BE11F5594ULL, 0xEE9039AEF5EC6B60ULL, 
            0xC59EF6CB5EDED2D9ULL, 0xDC016159A5574514ULL, 0x53807158722660E2ULL, 0x2EEAC1C5562AF117ULL, 
            0xFD749CE1D933A918ULL, 0x398CC756472B76ABULL, 0x55BA761B04F33ED2ULL, 0x09F0BD8B2E89BC86ULL
        },
        {
            0x073C69A5F594E5D2ULL, 0x8CDCC86D2D30598FULL, 0xF925D6D8B15BDC1BULL, 0xCCBEC106ECB14B6BULL, 
            0x32D21AAEC36BB142ULL, 0x28267F36B10CA19DULL, 0x2B776638FF3F9D99ULL, 0xEFE7A8295597957DULL, 
            0x8A47D03F06C9A6AEULL, 0x466DBC94477110EEULL, 0xAD9AC564302BC8C0ULL, 0xB618FEBD7B4B58A1ULL, 
            0x6E8C2E6353B98F18ULL, 0x42820FCCEE79993AULL, 0xE0BA264B9B02BB15ULL, 0x5EEBBC38F0634F4CULL, 
            0xC7F8E754DE90F856ULL, 0xCAD58FF38AA09DE1ULL, 0x9BA67D5F0D625CF4ULL, 0x0CEAF6896FA22F85ULL, 
            0x5756BA22EBEB8C3BULL, 0x19EF34C9E35ECF3DULL, 0x8FA773ED96458204ULL, 0x3F0E3FFE78E498F0ULL, 
            0xEFD7C1B3F7E31619ULL, 0x16A1A8560665387EULL, 0xC4E853CC1C03546AULL, 0x0C41F77D2107302FULL, 
            0x721BE97123793699ULL, 0x6262323F193EAA9DULL, 0x938F3D81ABC9A406ULL, 0x0F45661F7E88BAE1ULL
        },
        {
            0x68A96C9FBDF15739ULL, 0x51B68CA97F522ED2ULL, 0x1E32A44A8D4997EAULL, 0x27C9155A83EF026DULL, 
            0x25F4CB764E2A8A8BULL, 0x697057C8C25C2FA8ULL, 0x404E87C241C367A2ULL, 0xC2B54FB968F25D4BULL, 
            0x3E8D4204B67F0CDDULL, 0xBD282E79645994A9ULL, 0xD2007D17FFFA3F90ULL, 0x5533FC1013A9DB94ULL, 
            0xD0EC25849D8DB5A8ULL, 0xDAFFBB1BD7E53752ULL, 0x3D1F62B856170FD2ULL, 0x6204EFC67E404185ULL, 
            0x9831B0973103FB94ULL, 0x053D9398216ED834ULL, 0xFD493905B2ABC1F3ULL, 0x7F3FB92F5872D35DULL, 
            0xB82AE19A4D3C60E4ULL, 0x144F5C1913DD9928ULL, 0xFB2E7896B566E85BULL, 0x208DFFAB20F18A24ULL, 
            0x0506272BED57C381ULL, 0x07C2F0349C95C0B5ULL, 0x6B90FAE3BA2A85FEULL, 0x96114B0D7C83F395ULL, 
            0x5DAFDE7C64596E58ULL, 0x1118BE45B6018F12ULL, 0xE6F94A4145691CA6ULL, 0x7360DFF738B3F9DAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseFConstants = {
    0xFD3989C27608A5B1ULL,
    0x25B44966574FD5F4ULL,
    0x0B6608EBF3339AB9ULL,
    0xFD3989C27608A5B1ULL,
    0x25B44966574FD5F4ULL,
    0x0B6608EBF3339AB9ULL,
    0x15102CC8831AA478ULL,
    0x270F75FF39D0914CULL,
    0xC5,
    0x42,
    0xE9,
    0x03,
    0x6D,
    0x06,
    0x74,
    0x93
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseGSalts = {
    {
        {
            0x0B347EBD1B01D381ULL, 0xAB9000A57741E18BULL, 0x931F867B10A6A856ULL, 0x92B7E24F08F8B5C3ULL, 
            0xD938276A15C885FBULL, 0x0A9AB002AD9B22F7ULL, 0xE73D000E5A8A08F8ULL, 0x001DEA56985B18C5ULL, 
            0x934799AB087963ADULL, 0x8AF7D8B1DB65CDFCULL, 0x9124916C7AC785C2ULL, 0xE16F2D7B63D39AFEULL, 
            0x4C74FA20ACFE516BULL, 0xDE107D77CB90C184ULL, 0xB483535AD98219CCULL, 0x8E27C4B9D08890FEULL, 
            0x41DFEDE19E8BBEDCULL, 0xD7F0740925A4F711ULL, 0x8F8CA27F3C1A5AAFULL, 0x0DF24419DEF9FE3BULL, 
            0xCCDCA14585B00DDFULL, 0xC5E9B954F0A4F049ULL, 0x2DDC4C5C1940334EULL, 0xDF292655D98C278CULL, 
            0x86636FD45429E58BULL, 0x216692DC5FDF214EULL, 0x8DD58DE865D6CFAEULL, 0xFEEB94BF2D464877ULL, 
            0xD9A93ED80492C08FULL, 0xABAEA203113BED40ULL, 0x7D61CD3CEEBEE4BDULL, 0x39BE0E53CAB535CEULL
        },
        {
            0x1CA5BD3BE8725D41ULL, 0x42214C3F9DBEB00EULL, 0xD066A89FEA4326E7ULL, 0xCB9C7E280175446CULL, 
            0xC70BA2CD8B4F4C09ULL, 0xD08D359B8F6FDC07ULL, 0x7B4DC7B0D7AC9CE7ULL, 0x0B9FA137037AF7DCULL, 
            0x119A978062423904ULL, 0xD93EB80EAE1A08C9ULL, 0x54482BE28EBD4668ULL, 0x42AFECA220B96086ULL, 
            0x86C6E3D34E8BAAE4ULL, 0x4C1703FBF69A39FAULL, 0xC80B6451B9416436ULL, 0x046F78BDBDDA7DAAULL, 
            0xBBFDC68BC041450FULL, 0xD372F1D133D389B5ULL, 0xB29B08E756C4D18AULL, 0xD26746A539F705D3ULL, 
            0x0DE46752116FE365ULL, 0x88173E67D52A65D3ULL, 0x93CB374E3C45276EULL, 0x60692A05FFEBA74AULL, 
            0x54B44013B1504E2FULL, 0x5CF91CE853C7EC33ULL, 0xE4AAEDE6D2D98EDFULL, 0xF75D031A868A251DULL, 
            0x8B63001082C0EDD5ULL, 0x3A3B0D6D40A6B871ULL, 0x36CD40E3A06A6169ULL, 0x5C48D2B3FF3CAEB3ULL
        },
        {
            0xF212F56940F306F5ULL, 0xE03827CE7F02AA30ULL, 0x8146459D058AFA2BULL, 0xABDC95FC82370CF2ULL, 
            0x2AF82B700E1B63ADULL, 0xB5960D4DE1FBCA9AULL, 0x0AAB7A1375A5524CULL, 0xC26B5235241507C1ULL, 
            0x0E23E0B61FD03426ULL, 0x91A10EEAE71A2EF2ULL, 0x141B354C094F2FBAULL, 0x775EF5C1A4400D10ULL, 
            0x5D1EC22DF88ACACCULL, 0x4BA700269ED55677ULL, 0xBF65E943B9E502AAULL, 0x9DA39611F0E68DB8ULL, 
            0x1999381E9CDE069EULL, 0x343BC44F2D886758ULL, 0x84B5FD3051129AEDULL, 0x6B81396854716E1EULL, 
            0xD258A5D7CDBA615EULL, 0x157BE8A310705A6EULL, 0x5A6A4A6E5D8942FCULL, 0x7A19F7FA32911619ULL, 
            0x598293933B0E9845ULL, 0xE922062792D5F7BBULL, 0x362E590A80812195ULL, 0x4B4E9AC442A288C8ULL, 
            0x85A5BD8B4E3731DDULL, 0x57D41FA853589996ULL, 0x02FBD76048467DCCULL, 0xEC33BD309FCAEE46ULL
        },
        {
            0x155A37618E90B8DAULL, 0x6094C9904BEE4820ULL, 0x256848930C3AD08DULL, 0xA84AEB4716AE3048ULL, 
            0x5E7F7F4C5B5407D5ULL, 0x7D387D1EA4984885ULL, 0x93475F831C457F7AULL, 0x928B05A088409195ULL, 
            0x9042DB7C66B28378ULL, 0xEA2EA72E158E4E82ULL, 0xC36120C51BF295F8ULL, 0x43433DA11689B308ULL, 
            0xFD1050BF178918B8ULL, 0x204E6E2E8B7D8036ULL, 0x6675DD451C949E0FULL, 0xE1A4A7441953227CULL, 
            0x7FBD4E77F28597AEULL, 0x3572A23505F986D6ULL, 0xFAA7EF83F5136243ULL, 0x221A2A7B66145EFDULL, 
            0x0AD67822294F3056ULL, 0xECFA073220FC5C08ULL, 0x15B6DA4AF553D497ULL, 0x008CD0282A3391C9ULL, 
            0x5D66AD30B0B52AD2ULL, 0xF723E633B674661FULL, 0xE4E3A6018289B781ULL, 0x492BA705550FEE76ULL, 
            0x342F9164003D8488ULL, 0x5807423E7CD6AE30ULL, 0x0ED664151D4453BCULL, 0x41E3B2FC35D1BA47ULL
        },
        {
            0xB2A398B26E0B60CFULL, 0xD48A8CC3C404E496ULL, 0x23139191C29FB7B0ULL, 0x2521500CD967E9C4ULL, 
            0xECFDE2DB3A563F85ULL, 0x793C2EB7A4C0E959ULL, 0x5B489F08C4F7AB0EULL, 0x3C5E2BB6B109FE8FULL, 
            0x6EAA34F3C9E68F8EULL, 0xDF399A6251D386BCULL, 0x3F14125713BDA36CULL, 0xC27F48EBE2BF6063ULL, 
            0x2014DA2CC5C064DCULL, 0x3E0A38747538733AULL, 0xEEFC3B02131CF908ULL, 0xEDDBBF139037E4ECULL, 
            0x95D8F49D68BAD2ECULL, 0x53BC20A541F604F9ULL, 0xF1FBBFEECBAC6DCAULL, 0x36C9050081B860FCULL, 
            0xF012025AD8E1AABCULL, 0xB62ECA165541EECAULL, 0x4792E086C0E71402ULL, 0xFAC59EADD51721A8ULL, 
            0xA7081286524DE25BULL, 0x4ED9147680B8DF19ULL, 0x52305720A0A9263CULL, 0x9F5605D5A4B5A8EEULL, 
            0x63236D53B7815718ULL, 0x2DC19053C6EA22A4ULL, 0x455549F8A55C3EC0ULL, 0xF8567C0168FDA6D8ULL
        },
        {
            0x2915ED4C0663E615ULL, 0x6CD88B0A9D3204A0ULL, 0x8EEC882F0CC462D3ULL, 0xA1603B3044B82882ULL, 
            0x1C4E2FC9422A0C5CULL, 0xE02B49B9B35F9A24ULL, 0x83163B80745BFC4CULL, 0xCFEFDE4EF58CEC96ULL, 
            0xD107F72A19D517F7ULL, 0x4BC1F98462ADD2ABULL, 0x9047A0F3B5D6D45EULL, 0x86D3DF3ADA4CEBE2ULL, 
            0xB89ECCDF1467CD5EULL, 0x35E0050B0858614AULL, 0x219029150713040AULL, 0x2CAE7940A49F935DULL, 
            0x6F4453D1403DB0B2ULL, 0x10161B9DCDFBD2BAULL, 0x3A670BD6DD0490E1ULL, 0x7531CD6F6F574B3BULL, 
            0x5764FB7DB6F9EE3AULL, 0xE23868F4F8D3DDB5ULL, 0x9C94E551A957FA62ULL, 0xD7AA7ED3330A4F26ULL, 
            0xC0151E9A15FB451FULL, 0xF21B42DDC936A37DULL, 0xFA4A8D6AD99C148BULL, 0x60CFD7DA9FED8137ULL, 
            0xE956D782ACD21527ULL, 0x04D6DCF7411D5619ULL, 0x08822B5A33BE773DULL, 0x066A57B96C586E69ULL
        }
    },
    {
        {
            0xF8F5C055EADFC8E6ULL, 0xD8EA3513D30219AFULL, 0x1F5C4FE206ADFB26ULL, 0xEA7392B3AEFCB324ULL, 
            0xE294D0EC2ECF2116ULL, 0x555DC5000F3C14DEULL, 0xE32EB704EA13797CULL, 0x86DB3796957F3822ULL, 
            0xBE3C666A86C5E205ULL, 0x8C3B3D1C03C84B0FULL, 0x72A1F66D0FC3E4F2ULL, 0x0D50B9CC31BFF2E2ULL, 
            0xFD385385ACC2705BULL, 0xBBF7225125501082ULL, 0x24942F0851EDC68FULL, 0x03D35DA91DA82569ULL, 
            0x10002503C9518A8DULL, 0x1CA8FE5F4617B744ULL, 0x38CAD3CB610FAFDFULL, 0x0EC419DDB4891409ULL, 
            0x96A28D839D945DFAULL, 0x9B6C0EAC36107688ULL, 0x184063AE62BC848DULL, 0x26A4C5301EC07827ULL, 
            0xFC7B346863658B11ULL, 0x9AD32C2640550A0CULL, 0x3109F38C7FB7EF7FULL, 0x4EC33C5F61519B53ULL, 
            0x9848A0614BE0CA08ULL, 0x0A819D8EA6B9507CULL, 0x28C0880EC81467C8ULL, 0x747C012067E24486ULL
        },
        {
            0xAB83ACF6A97EB99CULL, 0x59ACD7B59172A3F1ULL, 0x2E1CEDAB70B799EFULL, 0x55584BCF16D94CBEULL, 
            0x9651A12BBC4D80BEULL, 0x946A0D06649C6E20ULL, 0xCFEC13771C92E066ULL, 0x9ADA6D6E22569C94ULL, 
            0xF1157021F6B93970ULL, 0x8EA542CBE9E2634EULL, 0x30774E9E3D88CCFDULL, 0xC9267567D713C4E1ULL, 
            0xE31D61114CC7AB70ULL, 0x57D2C679E6179FAEULL, 0xB28ABAA465F24BFAULL, 0xF2D896932E0ECD41ULL, 
            0x7246230E31CC40C8ULL, 0xB552579F222BBB1DULL, 0x98B6EC90DFF4A34FULL, 0xD682CB384010A0E2ULL, 
            0xD9715CB1911395E5ULL, 0x1AC0EC69D2DB4229ULL, 0xD7767DF19376FE20ULL, 0x865FBDE97D28BC6FULL, 
            0x7B1EA5D7F37B97A6ULL, 0x5C2ADB16C7EA669BULL, 0xAEDB3CFF9E037971ULL, 0xB9630A4EBB30904EULL, 
            0x55E49CEE72C2C70CULL, 0x6EE509B03838F9DEULL, 0x28C1A0468DA17880ULL, 0x585F90DCD42145E9ULL
        },
        {
            0xF95FE6D4AAB8F972ULL, 0xBC297BAD8DD0B273ULL, 0xEAFE83264C8F75C0ULL, 0x29AFE1CDCE7DE062ULL, 
            0x67DE58CBE26FF823ULL, 0x6E723528E76D6D39ULL, 0x4DF9BD69A846BBB6ULL, 0xC9F6457235F5CD27ULL, 
            0x79F67E2BA8A1F367ULL, 0x0F09704FEC1AE3E3ULL, 0x81FBDB72DB7E3864ULL, 0x052AEAD093DC2570ULL, 
            0xA5F24539675F96D2ULL, 0x3D01607D4D3A98CEULL, 0x4677198DAB46CB7FULL, 0x69D22E3BDF7F9BDFULL, 
            0x97125139DE720D62ULL, 0xE510843F1D111C5EULL, 0x74CBA953BBA094F3ULL, 0x919258B94D269B35ULL, 
            0x42B4F4B1F4999058ULL, 0xB9AD7F6223E7169CULL, 0xE5FDD55549823429ULL, 0x71879A0AB93F3F26ULL, 
            0x97F91F03A0E4976AULL, 0x072C988643269089ULL, 0xB538BF271148A8FDULL, 0xB62C690F4139D455ULL, 
            0x9E15B8D99038B806ULL, 0x1AC8EF177F64C8BCULL, 0xCD6A6EBEF2AA19DFULL, 0x95A7012F33A168F3ULL
        },
        {
            0xFDB4F5517B2D7EAFULL, 0x58A984A64D644521ULL, 0xC44BA6E894E5CB74ULL, 0xED0BDA88A92B98F7ULL, 
            0x0248C918B5B70668ULL, 0xD632FB97E8807C21ULL, 0x0A887CA52DA0099FULL, 0x0FD88C9973CDDEBCULL, 
            0xCD37C2CC06D2FF34ULL, 0xDECCA07F0723FB93ULL, 0xD8C3050271D06742ULL, 0xCC0D084D070FFCBEULL, 
            0x51C4E646D8B89810ULL, 0xCE9EA902C9A034E4ULL, 0xAE21F4F06F1E8766ULL, 0xAA74201C85AAC171ULL, 
            0xB306473C629F1861ULL, 0x7DB84622F0C46DD0ULL, 0xE9B5004203CABEE8ULL, 0xB456312240E1CA71ULL, 
            0x776FD6CE5977DB15ULL, 0x97B261BB4CA90E78ULL, 0xC9E3A79D6CF8F05BULL, 0xD5D9E74827EFF3BCULL, 
            0xA5929052A588551EULL, 0xD61BF569F6F0F1F3ULL, 0x794BE78724ED0C2DULL, 0xDA4ED4F0AAA639D7ULL, 
            0x42C86AB5D571424DULL, 0xFCE8A452C9448914ULL, 0x1AB4C60728EDF06DULL, 0x34E34BBB100A0F9EULL
        },
        {
            0x90274A8B655D165BULL, 0xB0D2C6C9CE33DBD9ULL, 0x0115896F931B8DCAULL, 0xBAFCC938E5DAC907ULL, 
            0x4C52E6173C283743ULL, 0x3F07146F66BF0230ULL, 0xDCDB6D28D8A79B70ULL, 0x0A9E4C1CC1033D01ULL, 
            0xDC04F1B04E9D53E4ULL, 0x17898371FB339879ULL, 0x552BFDD5577CFA1FULL, 0x27AFAC736EAF9700ULL, 
            0xF3EC7D2B9682E1E6ULL, 0xE94F2D48391334F6ULL, 0x0BEF5D69876E6CF7ULL, 0x75AE6065DB09BED9ULL, 
            0x34A57D46ACDCA952ULL, 0x38C5FEAFB459DBCDULL, 0x6E480D79CE391567ULL, 0x4578A9626F9D58F5ULL, 
            0x98922C2C810A1876ULL, 0x9FB2B5AD3EBFC1F2ULL, 0xF3DDE0DD5DD3AC1FULL, 0x7FBE6435997D690DULL, 
            0x4EBE2869D78280CBULL, 0x184E709CEBDE285EULL, 0xC3D02EF4CC274EEDULL, 0xEB446738A8DD54D3ULL, 
            0xF1395E8478811779ULL, 0x110F326FA839CE62ULL, 0x0E1217FEE495CFE7ULL, 0xBE9841978E95E6F9ULL
        },
        {
            0xFBC029E3D139CD5CULL, 0x60BDDB2E1C532752ULL, 0x75E2E6304E14EEAFULL, 0xD8074E19BEEE8C70ULL, 
            0xB7D9E5FB6C2F7F24ULL, 0xDC1FAD03E19826D7ULL, 0x4D7D7D5F8EFDE247ULL, 0x935882786073B7C8ULL, 
            0x7A6C7561F6AF4F00ULL, 0x91362615ECE8E275ULL, 0x90F9D9FDBB90CA49ULL, 0xE2480A20B001D7D1ULL, 
            0xA9E0A1C3CA04095EULL, 0x9A9A920EDB5DE13BULL, 0xB3D3257702BA2926ULL, 0x866734E44B81F24BULL, 
            0xB5858DBEFA4E9C80ULL, 0xD2509E1F4BC07042ULL, 0xE006423A5D2E929EULL, 0xC6D3FA1FFBBE9928ULL, 
            0x8529708345C5D841ULL, 0xCFDC8C1EBBBCFD24ULL, 0x79FA1BBAA4D0ED6AULL, 0xD26050DEF30106D6ULL, 
            0x49EF9851C56A1800ULL, 0xB2CF5E0556D1D8D2ULL, 0x8833C54C6DC9B941ULL, 0x2D326266EA5A86A7ULL, 
            0x95DB7B8A28A9D471ULL, 0xF830BBBD1B9C8FEFULL, 0xF9F692F41C5D7EC9ULL, 0xB9B09F7FD6B4E121ULL
        }
    },
    {
        {
            0x45B4AADA0AD5775BULL, 0xA42B2A0501903F0BULL, 0xBCF3ADB1D5C53B80ULL, 0xC96A0FC059FF9B18ULL, 
            0xE4DDB6F225885580ULL, 0x432485A2FF94B509ULL, 0xDEB20F3C7051360BULL, 0xE05124F9636A177AULL, 
            0xDC2565E4A374A46BULL, 0xC9D47EDC441EB3F1ULL, 0xD612D18F94B036B5ULL, 0xA71E69C8A0C550FEULL, 
            0xE6CFBFDAC0211C70ULL, 0x8CF9C2EE85B84DC8ULL, 0x2822DF70AB905A5FULL, 0xF1D736528625D75BULL, 
            0xC31DE88349D0C837ULL, 0xD99FE6F8192D4B92ULL, 0xF1BB356EFBF069BBULL, 0x8AF2EE09C55F776CULL, 
            0xA56D4818574A34AFULL, 0x71BED7BB037FA6DFULL, 0x0DE4A21A8B61C3F8ULL, 0x5D4A582BAA8EDD90ULL, 
            0xE1702A7FF173DF4FULL, 0x5E6E0D878301198AULL, 0x96BCFCA4915885D5ULL, 0xD5409E34E832B921ULL, 
            0x588C23D1BE622759ULL, 0x27FAF0BECC0DA1A2ULL, 0x822A4E412F9044C4ULL, 0x39C1D0C144CFCFEEULL
        },
        {
            0x664164B8B2E3A485ULL, 0x49F301B77ACDF16EULL, 0xB110D9A994D21EB4ULL, 0x03DDF57D05EFEF87ULL, 
            0xCEB978931380E04DULL, 0x3D5497DA58A0BD7AULL, 0x761CEA4FD56F0DC8ULL, 0xED238B5709B9615BULL, 
            0xBC2A92513B639046ULL, 0xB4D2B5AE8D1F862EULL, 0x6070937380C82AA6ULL, 0x4BC005681AC599C0ULL, 
            0x14BC9CDCED5F4007ULL, 0x254AE8960E26227FULL, 0x4124BA9BF1FEBECCULL, 0x9E23EF94A5022B4BULL, 
            0xB1833F2AF43BD998ULL, 0xFE2E6546E4E010D7ULL, 0x5445023A8F169F8AULL, 0xBBA8913AB701D42CULL, 
            0xDDBA77DD1D475657ULL, 0x49CBEC56F5E88221ULL, 0x315E268139E12B36ULL, 0xF9F18C0EB03FB6E0ULL, 
            0x43A2DA803665F74DULL, 0x2803667E717074B8ULL, 0x32F47F6B7DB48AD8ULL, 0x9B9C1FE88B873B49ULL, 
            0x371B0A0FE06C1E91ULL, 0x7B83C7650C605F5AULL, 0x26017FA024D16A95ULL, 0x7C516BE1525C171FULL
        },
        {
            0x6795C31D98C96D28ULL, 0x82632DE4959028A6ULL, 0x7060B41A0C6C9B85ULL, 0xBD50B4E38CCD421CULL, 
            0xF0D0F0AC76D3C2F8ULL, 0x6806EC5553997FB2ULL, 0xDBB9D89997ED1890ULL, 0x73173871F490FF25ULL, 
            0x27133C2834D2A2E1ULL, 0xBFDD7EA769C5AD4EULL, 0xF150D5E8BB0E84F1ULL, 0x1CD0E980E4B86E1AULL, 
            0x198A283792CA2258ULL, 0xC0FF52960BE4B624ULL, 0x0CA89416AE106FC9ULL, 0x61CDDF244E48A486ULL, 
            0xF8D4F646FB66CB9EULL, 0xA2BDAF6824086885ULL, 0x1DC1AE397D9C0060ULL, 0x2520033C8C456E42ULL, 
            0x9F0FA67AFD6F90AAULL, 0x04AB14DD4D500274ULL, 0x3E28A722593361FFULL, 0xBD9AE0813B3DB316ULL, 
            0x2DEFF6E6D4D92087ULL, 0x6FE26A470B0A6586ULL, 0x5E2362BAFAE33A03ULL, 0x948402F6E0ADB20AULL, 
            0xE1D6F45487707CEDULL, 0x5FAE9F52B281C9ABULL, 0xC1C19AD40871078EULL, 0x5FBE979269F2431CULL
        },
        {
            0xC7DF50D49D41B434ULL, 0x9E5AE150AC3E4C0AULL, 0x4B82BA3D1AD2AC34ULL, 0x649E65E9615F251CULL, 
            0x460094C93857579CULL, 0x125151996683A556ULL, 0x80EB67011F21B1AAULL, 0x000C2F52FD798FD1ULL, 
            0xE0491A51E0A1EF0AULL, 0xA32D44EAA0E17A54ULL, 0xC06BBD24FA1C2D1DULL, 0xD361A4695DC9FA65ULL, 
            0x01CBA20B858E1B0CULL, 0x6951B6FC95FC4314ULL, 0xA465F0A896A27A2EULL, 0xA7486611727AADEBULL, 
            0x88BB47039683F258ULL, 0x7AABC00CBB2E3019ULL, 0xEBFA7C9B48310DAEULL, 0x5B12556896B6150FULL, 
            0xCB7001DD34004309ULL, 0xFD20BAC7346BA5F6ULL, 0xC661AC2C0876DA6EULL, 0x815068582D00508DULL, 
            0x534E57E6861DB073ULL, 0x043B7E90051F623EULL, 0xD3DDE29C6AEB08E2ULL, 0x0FF504DBCEC03861ULL, 
            0xC4B65CC922C2120AULL, 0xB255619F4E809D77ULL, 0x0CFE7732542995B9ULL, 0x6127B157F7480AB4ULL
        },
        {
            0x5F2F83A92BDC6549ULL, 0x6342419428C62562ULL, 0x7DEC5E6F4F7C70F8ULL, 0x27CB99F806DBE1A5ULL, 
            0x512C55933B1F3F77ULL, 0x82ECF59ABCB05181ULL, 0x92B069904222406AULL, 0xF7A193287A0BF1BBULL, 
            0xC399E78FBEBC8AFEULL, 0x96231958DE7E6BCEULL, 0xADB16741BAC23F0FULL, 0x30633678998CF293ULL, 
            0x28D1E4C4EC8F87EFULL, 0x06D0C07E8CD2D577ULL, 0x0F6DEF65048D7A06ULL, 0x19E24DD732F204E9ULL, 
            0xBF226C372C708150ULL, 0x89F6F3963EABDD9CULL, 0x1C069908B83A2E5FULL, 0xE373C4C4C8D2935EULL, 
            0x237CFD65FF26C97BULL, 0x2BB9C148DB7150CFULL, 0xA42526F728E451F0ULL, 0xEB95BA1E340DCC79ULL, 
            0xCE0D46C78A601B26ULL, 0x42CD1EB43E9EAE49ULL, 0x76B59EA20580D8F1ULL, 0xC5BFBCAB253F7C27ULL, 
            0xBEFA3F73252AF474ULL, 0x0FCC07F6A92160F2ULL, 0x7BE4AADC7CD468B1ULL, 0x3744AB085DCD38F6ULL
        },
        {
            0xD28F9EB6EBF9AC41ULL, 0x8D70C45E8BD173AAULL, 0x2F6EE5263FE33B8CULL, 0xC62B7040127035CBULL, 
            0x91B81DD6D931A1E5ULL, 0xEF5A658483EAF3C5ULL, 0x8DF8CB059A822A9BULL, 0x10A8CEF08C99C891ULL, 
            0x8D10591D3FF9B2D8ULL, 0x078DDBDFB8C450F9ULL, 0x0F29AF9AD671629BULL, 0x6414EC4E6D67850EULL, 
            0x843CB9F545E5253BULL, 0x5FE0C22B3C89572BULL, 0xA35EAD6E0E24F8B9ULL, 0x1C679FF189EE3A13ULL, 
            0x375CF225BA5BE1ECULL, 0x566F7C828BED4E85ULL, 0x2697B07A6CAB24B4ULL, 0x96704D817EAEB08BULL, 
            0xE59A97BA40A89B14ULL, 0x1B8BE344A1E3D35FULL, 0x55A6A72EB4F6D9D1ULL, 0x1FBD3CF2F575B940ULL, 
            0xA861E78F1ED395DDULL, 0xF3987F4366F07870ULL, 0x820D456CB5ACE496ULL, 0x7963C1C014DF6C88ULL, 
            0x43EDA10783E4349EULL, 0x782A9B2BFDD34FF2ULL, 0x900898EB3AD67814ULL, 0x8B334E54F67965F7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseGConstants = {
    0xE6EE605B3E46439BULL,
    0xCE42E973EA4F0601ULL,
    0x0007109D57CD8812ULL,
    0xE6EE605B3E46439BULL,
    0xCE42E973EA4F0601ULL,
    0x0007109D57CD8812ULL,
    0x06F21B1F6BAD849DULL,
    0xFC6F0B004A43396FULL,
    0xF9,
    0xDE,
    0xB5,
    0xEE,
    0xFC,
    0x83,
    0xB7,
    0x89
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseHSalts = {
    {
        {
            0x28D928B9BDF07868ULL, 0xF831F93C70D5CEE8ULL, 0xE3D1400D5427BE4FULL, 0x07B7ABAE5234A911ULL, 
            0x516F06BFB13190F4ULL, 0xCE25F1FA8D784AB6ULL, 0x61C268DABC0A7748ULL, 0x5E844C559A4248A4ULL, 
            0x05EDCDAAB5EC8C02ULL, 0x25EDE8140FD37873ULL, 0x348184657F8C9E15ULL, 0x4094E8A12DBF87F4ULL, 
            0x31A0CE88CAA7E895ULL, 0x98A9C6102250701FULL, 0x71D3997B2B0B98AFULL, 0xB509B14BAF9B77F1ULL, 
            0xF60B148D70025A28ULL, 0xFAFAFA3297B88CC7ULL, 0x9512FA4982D7CD14ULL, 0xF1D7E3CD356E0210ULL, 
            0x3AAC9CDC590756AFULL, 0x1D95B26B6DCCD927ULL, 0xA7BEE3FB843709C0ULL, 0x62CC87EABB038563ULL, 
            0xB9D9A94D1D306591ULL, 0x8B5AE6D33E55C5B8ULL, 0xD4B704F67868B3ECULL, 0x0134AFFAF90A6228ULL, 
            0x1B45343E59D0EC02ULL, 0x5332C242C9012353ULL, 0xFDE5A87A2A3C7121ULL, 0x92C077852EB58140ULL
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
            0xB2267A53545E9092ULL, 0x6C0E481953ABE7E5ULL, 0x7877B42F7A2CF7D9ULL, 0xDEA3F59D8274F029ULL, 
            0x94F0BAFDBADAC99BULL, 0xB2413CEC47BC2E9FULL, 0x78315B4F29978678ULL, 0xE83037BE6C774DB4ULL, 
            0xF3A9BBB1FFC24F0AULL, 0xADD5BB65FD858D74ULL, 0x1435DA0AA5A8233CULL, 0xB6C185A9CAFD2D4DULL, 
            0x19770DB42109F4A0ULL, 0x97F88BD6D5E85B6DULL, 0x70A58B6B8E34EDE0ULL, 0x8436D059287BDCD7ULL, 
            0xDCB30A397F9D5C80ULL, 0xF103B8E06AC52D89ULL, 0x31596EC4E9BCD2E7ULL, 0xED652EE3076A9AFBULL, 
            0xE9F8E4845A01B6AEULL, 0xD9F3B752ED23C4CBULL, 0x6D018CD06B9CC2CDULL, 0x0D64CA480D87383EULL, 
            0x3FAE85AA934EDE1DULL, 0x93B03B746562DACCULL, 0x2CFD6F728F80FD9DULL, 0x0CE53703C5509571ULL, 
            0x59CF591003CC8C0EULL, 0x8569F48396630017ULL, 0x9F861F3CA7EA5130ULL, 0x0FBAF31E0C79B0F8ULL
        },
        {
            0x57A016615887A890ULL, 0xF0518900FEE97B60ULL, 0x3EC2D3D7B96C509CULL, 0xEC5C2730B3E714ADULL, 
            0x7F3257843CF4CAA6ULL, 0xF45205B0770F8A4CULL, 0x12B9D5F5D3710D1BULL, 0x556D560086D7600FULL, 
            0x34B047E14051C5F2ULL, 0x980F4B10CC541C50ULL, 0x3F73CD0CA96216CFULL, 0x25586639B7194B63ULL, 
            0x5D0EE32999EFD1B5ULL, 0x36CE1B3707B8CDF1ULL, 0x0DD0C231AB225E4BULL, 0xC22398AF30DD4E91ULL, 
            0xA1DA76A5107992ADULL, 0x220E640616EFFEDFULL, 0xEF1B2E0FE227A0D0ULL, 0x6DD2109F70B01EA2ULL, 
            0xCA8CF8129E08697DULL, 0xA61F42636E1089D7ULL, 0x36C18C81CBFD041EULL, 0x009D8122607E7341ULL, 
            0x9E7956DDD86851D9ULL, 0x668CD42A3557ED42ULL, 0xF6BAEC7AE1EACB5BULL, 0xB2642AB27280B3BEULL, 
            0xE91F58739BABA036ULL, 0xCD9604A551CBD01BULL, 0x0D5AB6F35FC90EBBULL, 0x943A5BEBC118BE4FULL
        },
        {
            0x7426B2F8D4138846ULL, 0x636F20CEB1B974E3ULL, 0x0EE712E32FB22A48ULL, 0x13FB95FFBA56DF09ULL, 
            0x95C7FA798C8AA774ULL, 0x2A8B548980C81512ULL, 0x960757B88FFF53E8ULL, 0x002863DB5AFCD474ULL, 
            0x4D98F87BE9DFEB30ULL, 0x96E9F782DCFF961BULL, 0x018B8A214B074841ULL, 0x7E0385C2C353CD0AULL, 
            0x130C1F5503DFA812ULL, 0x2CD53E4A66B88F9BULL, 0x32B279A78D95BF72ULL, 0x7885B9CB3145322FULL, 
            0xAB3897707DE4B92CULL, 0x31C4BDD45CF1E4E0ULL, 0x6927F4B47B366CF3ULL, 0x401A575F65D107A9ULL, 
            0xB8A424B1682A8284ULL, 0x7085970E43BA7081ULL, 0xC97A33872A5D775BULL, 0x4C8B6BFCED6C1A9BULL, 
            0x48C0C59C19A5AF52ULL, 0x7BFAC0826D395E7EULL, 0xB6FE06CC84F9B470ULL, 0x102ED2AF6C5E2107ULL, 
            0x4979821DCC7B0BC4ULL, 0x16FC7FD170780AACULL, 0x27135499509292DAULL, 0x0B4F0E7FEC8252B0ULL
        },
        {
            0x1E5BE23D8C1FC309ULL, 0x9E0F085E0E2AE82CULL, 0x92C89D63656C9662ULL, 0x521EFEBA45B4068DULL, 
            0x5676301669553D42ULL, 0x9C88B32F50AA4999ULL, 0x54A886DCAFEA50EAULL, 0x5C6810813A927ECEULL, 
            0xC3A3F0B3D6185FCCULL, 0x1B668D297C2C2CDDULL, 0xCFBEABA5D11A1B41ULL, 0x5E9BECCA819C8D70ULL, 
            0xA10E91510DD68E51ULL, 0x8955D40AE1191DACULL, 0x0EA13E00F4F2C61DULL, 0xCF9F87609FA480FBULL, 
            0x638D15F30EDF1175ULL, 0x016F4CACDA09FF31ULL, 0xFEE22DC537394EFEULL, 0x709EA7F3AB67BA9DULL, 
            0xFBB0C30702C359C8ULL, 0x57DA8E0339C8B9E7ULL, 0xFA386E1AEE7BA528ULL, 0x66826E4AF1C763A2ULL, 
            0xB50BE3C2023C6040ULL, 0x884B61542BAB26D3ULL, 0x21A5A8308997B88AULL, 0xC9E81FC7D45CD02DULL, 
            0xEC5CD2F32979BFD7ULL, 0x82B75C96C5963319ULL, 0x585239B0093E6C14ULL, 0xC97F2747CDA30F58ULL
        }
    },
    {
        {
            0x69FBDC42CCCC58D1ULL, 0x42C04ABFC2D32ACDULL, 0xD68931AEF4E3D051ULL, 0x9285510E63967D1EULL, 
            0xFF8D42B2F5C7D200ULL, 0xC63D185CBA159D5BULL, 0xBCE14D424BBDEEC0ULL, 0x2A1B514B099C9BFEULL, 
            0x125EC1A3A582DD0BULL, 0xD13B70B1CFAD9E4EULL, 0xE4BB06AA86125CA5ULL, 0xEF206F5C3BB5B542ULL, 
            0xF66A02B9CE5DC6CCULL, 0x98E10036349785E5ULL, 0xC1C10D4251B7BFB9ULL, 0x249312DEF765F3B6ULL, 
            0xE137E6E02AF4CDE3ULL, 0x39D5F693265DEDC9ULL, 0xC34EECEB0E8A0614ULL, 0x4F7C5D9F30A27EE6ULL, 
            0xAD23A1C2F3E46CD9ULL, 0xF5A0473CF50797D7ULL, 0xDE61A239256CEA71ULL, 0x46F03448769A1DB9ULL, 
            0x202571CA50B1DD15ULL, 0xBC2B48E421BC9411ULL, 0x611A4CAF6221989BULL, 0x87FEF05F3D6A2BD8ULL, 
            0x3DD42490239A6C80ULL, 0x94AB997498A626A4ULL, 0x1DABA86D97F4AB8FULL, 0xA23C84990A45AD9DULL
        },
        {
            0x6F284D587A0E0043ULL, 0xC2B85C52A5C2673EULL, 0x46159D5E513043F0ULL, 0x985BBC09B6C6C256ULL, 
            0x24F286375801B327ULL, 0xD8394D5B28B80723ULL, 0x2883BED29B4457B2ULL, 0x5952755BCB822578ULL, 
            0x668AC04B40E3C1E0ULL, 0x4EB8719736B11855ULL, 0x885AA1AE8A28D5A3ULL, 0x810BFF35E2B4E4E8ULL, 
            0x5C579EB1AFF354A6ULL, 0x87EE2353B6F4410BULL, 0x5BC3161350773162ULL, 0x14D085A940C0B67CULL, 
            0xCCCFF8A61A632F05ULL, 0x187E055216BAA617ULL, 0x7EAC868A35F17933ULL, 0x64D58B9681637749ULL, 
            0x3E536A195642FB34ULL, 0x9A5CB4AFBA5C1633ULL, 0x121DF39BC099B5CBULL, 0xADEEA357AF0F0E9BULL, 
            0xBC3CA43CDC19FE23ULL, 0x3E115DF81494A354ULL, 0xCCD15A65818054CBULL, 0xCBEC81351F8AC153ULL, 
            0x74AF41C1F7042612ULL, 0x811F5C6BA951E22FULL, 0x592A8F91AFABDF34ULL, 0xA0B949B0543A5329ULL
        },
        {
            0xAD8D268C82DFC707ULL, 0xCD1F3A776891CEC4ULL, 0xA79CB73CF7A4F76BULL, 0xC9211A37F24CB04FULL, 
            0xA30253DB73DF9889ULL, 0x07501483B0A722E2ULL, 0xABA5188762AD0939ULL, 0x81FDF0960EC15688ULL, 
            0x498A7FAD353E2D79ULL, 0x1E4A3B0AB347C33FULL, 0x9E7C8BFE563DD339ULL, 0x0C44A5CF2DB5789DULL, 
            0xFFE0372E477F07E9ULL, 0xF0E6626FF690FC3BULL, 0xDA9A2C13D4414CE6ULL, 0x31448C5F876595CBULL, 
            0xFC365FB8EFE242E0ULL, 0x054235FC3FC08FA5ULL, 0x96671D96E66FE7D2ULL, 0xDCDD2A2C7C87C49DULL, 
            0x2656E5336098ACFDULL, 0x6C296AAE2B6CA3E9ULL, 0xD11528B7E5CA3B99ULL, 0x39114C4046167A7CULL, 
            0xB6EAA722179F4730ULL, 0x91F17381D19FDEB7ULL, 0x629DC7667D4AFB55ULL, 0xA5A3AF88012859E3ULL, 
            0xDCBB1221C4B4D13CULL, 0x40F98DCBEE3FBC43ULL, 0x3BDFCB6DB8EBE86CULL, 0x58A680AE10EFE25CULL
        },
        {
            0xB3B89A93AEB4C8A8ULL, 0x55FD49C8B67BF5C9ULL, 0x579D45A08F933313ULL, 0x6A59FC2E7CA220C5ULL, 
            0x0E5EF31EC98315E6ULL, 0xCBA0BCB323C87B1FULL, 0x98B04983050976A6ULL, 0xFF556CDE2AB4E11DULL, 
            0x5993CB34BDA8F94DULL, 0x257CAFFF31FD3BE5ULL, 0x7E2E603323233FCAULL, 0x29EC91898243D583ULL, 
            0xAF0FC6C2ED2E6A47ULL, 0x52AA7140C6B5CD30ULL, 0xEF5B0F1D65EDB632ULL, 0x5B9E5BB7DB75E92FULL, 
            0x029978DEAD965535ULL, 0xDF0773FF667390F9ULL, 0x959ACFFC39562025ULL, 0xD22760D84E7A2EB6ULL, 
            0x5FAB1B579E32E789ULL, 0x4DD89B1DAEF4E26BULL, 0x17AA7E6B6A7B50FDULL, 0x2E252D197ED24258ULL, 
            0x69819774404809C4ULL, 0xE7B616B10B8B5F14ULL, 0xEBF44C4395E5F8F4ULL, 0xAE375DCB41D1DA83ULL, 
            0x7290919F32BBD4EEULL, 0x3D91937FE45FD6E0ULL, 0xA9C0FB966862DA4AULL, 0xE33B9056A8F93F53ULL
        },
        {
            0xD689EBF4B6FBEC21ULL, 0xCB90D8A6D40A45DFULL, 0x510D492B271467C3ULL, 0x2CE1FB43F4EC5E9FULL, 
            0x7097230B08E5DA3EULL, 0x65D8D4D2905B1BEFULL, 0x3B85E0262082E9F6ULL, 0xA322A5E8656B6B1FULL, 
            0x9A241B1087EA6807ULL, 0x51CE9E50BE58DAD6ULL, 0x12F43230546AB08FULL, 0x738D4651B3D340BDULL, 
            0x36C397E787A00995ULL, 0xB69D87FECBCF4C03ULL, 0x790334BBA57084A5ULL, 0x6B03A580396BA416ULL, 
            0xBE1390E9BBBDCD4CULL, 0x2196FBB6A78EC569ULL, 0x180ACEBBDCD8F82AULL, 0x78EBAD4988D8CE25ULL, 
            0x4A3450ED4DCB3D92ULL, 0xDCF5E582392D78C2ULL, 0xC7D5CD7C1F34E29CULL, 0x068EF7BC7215FA9FULL, 
            0x83514423632EE3A2ULL, 0x5B7A30854DB3B87AULL, 0x2FD69285C3154621ULL, 0x6ABE9B52E20D3EEAULL, 
            0x9C12D3918EF298DFULL, 0x2E936411BA237064ULL, 0xE241C54D907094C9ULL, 0x3E862AD5DB786FA0ULL
        },
        {
            0x2DBF9E0F55BE8B4AULL, 0x5E1CA580D7507B44ULL, 0x6A52C801A28F5E92ULL, 0xAE2D849C5D889117ULL, 
            0xB176DCE1222FB203ULL, 0xA5F13D72E34A62F3ULL, 0xD0799D7B31F21085ULL, 0x50EE61C630FCCD0FULL, 
            0x86DBCB22BF22AE56ULL, 0x353C43717D28DFB1ULL, 0xFC26AFED7448F8C9ULL, 0x4BCE8EBAB4707DC0ULL, 
            0xE59261CA75FAE6AFULL, 0xA6ED2B587E373E39ULL, 0x124F146305C9EDBDULL, 0x55AF4C34E373D9CAULL, 
            0x8A9CA6850004433DULL, 0x6804CDA5C8A0C8B6ULL, 0x4774960A5763A8D8ULL, 0xB89747CD5FCD9FC0ULL, 
            0x1ABFDC4E7D618CD6ULL, 0x8C17BB90814FD016ULL, 0x7DD5A51BBCC7AF5DULL, 0x1EC3FCB7FF843224ULL, 
            0x80663B4045182DAFULL, 0xD13D22EDC5BD1C91ULL, 0xF4860D8552F5F55EULL, 0xCE9EEA4BD311E89FULL, 
            0x983BD9A0C86E52A9ULL, 0x1538FBD2CB7CD7A2ULL, 0x44C02A471504271FULL, 0x2B32D5C0BF199FEAULL
        }
    },
    {
        {
            0x8B1AA2D63DBFC194ULL, 0x3F3CEA0FFEDE0B4AULL, 0xCEB57B79C68CC13EULL, 0xB0B6CEAB9C44A0C8ULL, 
            0xB2D0A7F31DA8E680ULL, 0x07D18EF8E7A55BA8ULL, 0x5F9A548074416310ULL, 0x2C8EC03E1E5C1FFFULL, 
            0x686575B1CC12192AULL, 0xC01A342174CE0094ULL, 0x6C21516BD04D90A9ULL, 0xF89B2827DE86C38DULL, 
            0xD85215A5DB88B0D1ULL, 0xD1177DFED372D47CULL, 0x776802F266751173ULL, 0xF0358225FEB30926ULL, 
            0x092BB06CB1D3EB88ULL, 0x7FF57CCB745E32D3ULL, 0x0E7BE76E15A0EEE8ULL, 0xEBB107AE81C21778ULL, 
            0x70A637B9E4A32C71ULL, 0xC681E5F93098565EULL, 0xC8987CB7BC482CE3ULL, 0x836F27ED2F605B5DULL, 
            0xF8CD9E05E984AA81ULL, 0xBF64D34821EBB069ULL, 0x1D24B082BD676D14ULL, 0x781590661A38F8BDULL, 
            0xACA2EA7176ACF4F9ULL, 0x2937E9C78C8E1773ULL, 0x89927239F2E36893ULL, 0x165453C2A4F6E60BULL
        },
        {
            0xA0894F486E17B08DULL, 0xBA22F22E7CCC9AB3ULL, 0xB2E671436A6BFA66ULL, 0x68E4A01D6FBCE74BULL, 
            0xA1C6AB4F9F922A76ULL, 0x312AF42364856D66ULL, 0x868D1C7CE58D8F53ULL, 0xFA05B5ECC5C208A6ULL, 
            0x031A5E7629FE61F6ULL, 0x4D3B7DB2822C92BBULL, 0x615E62B77B53FD3DULL, 0x815AD4D125813C35ULL, 
            0x0DFB1A62665D0B8EULL, 0x22158CAA3D61F007ULL, 0xEC9292E6663B8C9AULL, 0xE14095CC9B1059A8ULL, 
            0x70F0005C1B5753B8ULL, 0x952FF00D5513C15FULL, 0x448CD777804F92A3ULL, 0xD13CF6B25A552F88ULL, 
            0x58F86A44F7AC95D2ULL, 0x737A973532939212ULL, 0x1633F04BF1ED070FULL, 0x2AEF4B2BC2DC3818ULL, 
            0x1F497B866913AB19ULL, 0x894BB9BAF8514375ULL, 0x96979E5517B808B6ULL, 0xF0CD8580C91E1FEFULL, 
            0x0E44E655D907F9F8ULL, 0xC54941F60E09CFAFULL, 0xA5B401C9CBA7D80DULL, 0xBD47B6359C23EE2BULL
        },
        {
            0x0771E431D7C8233CULL, 0xCC1A2363ACA00B3FULL, 0x57A612802C9C298DULL, 0x4A1C687383065796ULL, 
            0x85A50DA2B9ADE15FULL, 0x7A38B8C52D6A37F6ULL, 0xB9A560799B671C5FULL, 0xE35390E0558D5725ULL, 
            0x2E7E3C8E578483E2ULL, 0x0EEBC12AE8D6CA76ULL, 0x5926032885FEBE33ULL, 0x1E6CDCB65D559123ULL, 
            0x29C4D4288D62258AULL, 0x628C9033A9A49281ULL, 0xC777CD9BF31D0F0CULL, 0x27FD6C648CB9D32BULL, 
            0x0E334A56DFF36059ULL, 0x5BDF3E4C4E5B4BCFULL, 0x28B6ED14DEC03D51ULL, 0x06045E77A2A7523BULL, 
            0x0EADCE4444422103ULL, 0x79F9F8C914CA41A9ULL, 0x58FFDBE9A8F908ADULL, 0xEA0DAE40A2005011ULL, 
            0x75E4B5C4C6BF25E3ULL, 0x626B65029E44BAA1ULL, 0x7604798B18C1495CULL, 0x258B3195A3745F39ULL, 
            0xBC9CC318E5C0795DULL, 0x64051E14F1106BD2ULL, 0x1203C2683E5BBF79ULL, 0x0109C4721F274436ULL
        },
        {
            0xEB4D9D04814AB729ULL, 0x1925EF6C7EF6848FULL, 0x711125647B65D2E4ULL, 0x722008A1091FCC3AULL, 
            0x8FC2D9862DD24855ULL, 0xFC1ECBF88DB23D9EULL, 0xCA20A5ECA4E41583ULL, 0xF05FB377D49F7295ULL, 
            0x719D0611A5CF73B1ULL, 0x9F7899E433821B3DULL, 0x060141E6FB436674ULL, 0xEB84C05CDF90D008ULL, 
            0x245B81974130C598ULL, 0xCBE9818ED3CFF2C4ULL, 0x6C8E80CC093B21C3ULL, 0x7A6385831BD66241ULL, 
            0xB95F5C35F50C270DULL, 0xA3F59293273AC94CULL, 0x086D28AB857D7B9CULL, 0xDD0AAC33E5943222ULL, 
            0xC7B05E1F8189FA43ULL, 0x27D661EC72A7F7FFULL, 0xE60D293479BF26DBULL, 0x042D078681D8A914ULL, 
            0xA6C96CDA6F1FDC4BULL, 0x07273BF5196A0134ULL, 0x3D1ABB6EC36AAFB3ULL, 0xB9A7A8E539C72668ULL, 
            0xE61ACD1C6E9C887EULL, 0x66D85FA63449300EULL, 0x56757E93B7C08453ULL, 0xA7472EB41972C4DCULL
        },
        {
            0xE04B7FFCCFAD5974ULL, 0x007F5F0AAF226CBCULL, 0x62AE4457CC92D953ULL, 0xBDA76385A221384BULL, 
            0x34E3848C2D0C8CB1ULL, 0x690373D3116A8012ULL, 0xCE5E34D6E9B70201ULL, 0xED0048D098BA1727ULL, 
            0x4537D771DFD6742EULL, 0x0181695F3F6FC0A2ULL, 0x8D8C9DB4F1E73E43ULL, 0x0079CB93E0B663ECULL, 
            0xC3FAC2A09494E8E3ULL, 0xF1B947D57D3BFAB8ULL, 0x449C393C0EA5A5E4ULL, 0x43B98F2949EB6657ULL, 
            0xD6F7F3F60A991051ULL, 0xA8613F46E115F054ULL, 0x6CA7867F63D39C41ULL, 0x2C0C794A81D23C92ULL, 
            0x6A29B27018787638ULL, 0x13E8F2693E5A138CULL, 0x155F4D06257C6382ULL, 0xDB972484DB519C28ULL, 
            0x12E0F316AF2C440FULL, 0x00796F0CED902350ULL, 0xB9077446BF046D1EULL, 0x7A1F5C7A4676D9BBULL, 
            0x6F2E4DBB7A057B0CULL, 0x378B0A106FD4B96BULL, 0x787E0386ADA2B65AULL, 0xDD269390CA41033CULL
        },
        {
            0xF24A2555F8C28587ULL, 0x091BB54677BA4452ULL, 0x1E5FF45D7DFABDDAULL, 0x289A71919F4E2328ULL, 
            0x1442155996A4F8EAULL, 0x738E9E8FCDAAC498ULL, 0xF53ECFD3B3AF43B2ULL, 0x7EE596DDC9D2731EULL, 
            0x84469EEE74EF7432ULL, 0x1A531DEE7CAE14B8ULL, 0x909EE6805BCE7078ULL, 0x67989E2A026462FEULL, 
            0xCD9ACD2D27CC1D86ULL, 0x41B18D7F8B167DA6ULL, 0x42057C8D0D649A8DULL, 0x30F6363C168AC4F7ULL, 
            0xF24831D635AFFB8CULL, 0x95D2DF67210A6A69ULL, 0xDD39284E17ACEDA9ULL, 0x307A3DD0213E4E04ULL, 
            0x874B4617E8607B26ULL, 0xA3BA8EEF3334CC90ULL, 0x734CE89D62E41422ULL, 0xC1CD4EDA40D9EDEDULL, 
            0xC675C5A3ACDFBEE0ULL, 0xCFF4D47859798CB2ULL, 0x1D470058E32C5C00ULL, 0xC310589B622EBCC5ULL, 
            0xF9D49D3EC9503145ULL, 0x70343FDA2E1E50DEULL, 0xC1E09D04E17850CCULL, 0x44D34736AA13FE16ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseHConstants = {
    0xF39582A61064B8E5ULL,
    0xFC70B5BCFB7D4416ULL,
    0xC96AE36736034D78ULL,
    0xF39582A61064B8E5ULL,
    0xFC70B5BCFB7D4416ULL,
    0xC96AE36736034D78ULL,
    0x07ABB9506FABB9C3ULL,
    0x165B71F7E769A751ULL,
    0x98,
    0xD2,
    0x18,
    0x64,
    0xD6,
    0x05,
    0x55,
    0x5B
};

