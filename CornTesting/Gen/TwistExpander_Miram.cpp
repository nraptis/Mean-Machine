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
    std::uint64_t aPrevious = 0xA027FC5DD3A854C0ULL; std::uint64_t aIngress = 0xEA6A951BACDE52BBULL; std::uint64_t aCarry = 0x9CBEE81C54BB9E53ULL;

    std::uint64_t aWandererA = 0xC39DA90FB6DF36A0ULL; std::uint64_t aWandererB = 0xBE00E65E4C628A90ULL; std::uint64_t aWandererC = 0xA816A20973BA91B4ULL; std::uint64_t aWandererD = 0xEC9EFEA940FAA789ULL;
    std::uint64_t aWandererE = 0xE722A54ECCAA7F53ULL; std::uint64_t aWandererF = 0xA2845E2D1A30187FULL; std::uint64_t aWandererG = 0x888B5160EFA654CAULL; std::uint64_t aWandererH = 0xDAA5B70900835AE0ULL;
    std::uint64_t aWandererI = 0xB6A78AEC8D482D63ULL; std::uint64_t aWandererJ = 0xB70D8EB2C023142DULL; std::uint64_t aWandererK = 0xFD4A89A57B98143DULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15571051474475778847U;
        aCarry = 16233393208021751586U;
        aWandererA = 11936406453525528818U;
        aWandererB = 14030585966114891113U;
        aWandererC = 13756979996207114248U;
        aWandererD = 14296477245669487824U;
        aWandererE = 16285408797036073888U;
        aWandererF = 15791852632024572373U;
        aWandererG = 14788374824433409270U;
        aWandererH = 15752233757337681722U;
        aWandererI = 13961008445599980262U;
        aWandererJ = 10757442394401277911U;
        aWandererK = 14415357618683272555U;
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
    std::uint64_t aPrevious = 0xF1A0F6DA32C47441ULL; std::uint64_t aIngress = 0x93A96325A42E78CFULL; std::uint64_t aCarry = 0xEB67B7F43549FEB9ULL;

    std::uint64_t aWandererA = 0x9E6E5DEE2530012EULL; std::uint64_t aWandererB = 0x909363E523C6C898ULL; std::uint64_t aWandererC = 0xA9A02AF71FA6973BULL; std::uint64_t aWandererD = 0x8665B3B5518E2BB7ULL;
    std::uint64_t aWandererE = 0xC70C7AD20FB7DF94ULL; std::uint64_t aWandererF = 0xF13FC99ACCC49578ULL; std::uint64_t aWandererG = 0x9FF0EE6C28387B35ULL; std::uint64_t aWandererH = 0xE1110BDB44505E22ULL;
    std::uint64_t aWandererI = 0xBBB9DD0B0612E00DULL; std::uint64_t aWandererJ = 0xD116776144E9459CULL; std::uint64_t aWandererK = 0x9B0B34D7877FAA06ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15753417573951823138U;
        aCarry = 17471671468279126803U;
        aWandererA = 10023112209208869730U;
        aWandererB = 10342204540987704866U;
        aWandererC = 11524519695561141971U;
        aWandererD = 15364761674389812345U;
        aWandererE = 16955731585558597064U;
        aWandererF = 13083619926379279769U;
        aWandererG = 12719452440605106924U;
        aWandererH = 11564698108934614951U;
        aWandererI = 18132193349259655901U;
        aWandererJ = 16789251023014392451U;
        aWandererK = 15994417031766382224U;
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
    std::uint64_t aPrevious = 0x8A016CBF48115DCCULL;
    std::uint64_t aIngress = 0xD30EEA02E841D61EULL;
    std::uint64_t aCarry = 0xC41948DC1E7C5FC1ULL;

    std::uint64_t aWandererA = 0xAD450218E7C13DF7ULL;
    std::uint64_t aWandererB = 0xAAF7263B9B74D0F1ULL;
    std::uint64_t aWandererC = 0xDDE43998B5358C82ULL;
    std::uint64_t aWandererD = 0x9D41079EE117CF4AULL;
    std::uint64_t aWandererE = 0xC73A93FEAAEB75CFULL;
    std::uint64_t aWandererF = 0x956E62D34AF72B72ULL;
    std::uint64_t aWandererG = 0xBA25F3987D7BC38EULL;
    std::uint64_t aWandererH = 0xCA5F8090A80E313CULL;
    std::uint64_t aWandererI = 0xEB23F328BF204F59ULL;
    std::uint64_t aWandererJ = 0x94574BA4E93587B9ULL;
    std::uint64_t aWandererK = 0xB4A8C36DA4BC82C3ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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

        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
    std::uint64_t aPrevious = 0xC0D036814620486AULL; std::uint64_t aIngress = 0xBBF0A8EE2B0B50AAULL; std::uint64_t aCarry = 0x9FE252E5A41800ECULL;

    std::uint64_t aWandererA = 0xABE9A0FD27E66801ULL; std::uint64_t aWandererB = 0xD4B0A7906D361318ULL; std::uint64_t aWandererC = 0xDC2E84222ECA5892ULL; std::uint64_t aWandererD = 0xBD142849530C43D0ULL;
    std::uint64_t aWandererE = 0xD11B5F80063EEBE4ULL; std::uint64_t aWandererF = 0x9F0F56EF922E5156ULL; std::uint64_t aWandererG = 0xFCCCDF6E24EBBE56ULL; std::uint64_t aWandererH = 0xB73C8A6B6D191851ULL;
    std::uint64_t aWandererI = 0xB1566E2CAA2B2AD3ULL; std::uint64_t aWandererJ = 0xA27630FB9E316A0AULL; std::uint64_t aWandererK = 0xA875DAE43E9F7635ULL;

    // [seed]
        aPrevious = 15290896707107491630U;
        aCarry = 9965186060825360522U;
        aWandererA = 11975600135320167213U;
        aWandererB = 12745256476150591026U;
        aWandererC = 14347596040000356373U;
        aWandererD = 9546872744430174199U;
        aWandererE = 13625346445659612379U;
        aWandererF = 10581029198073092682U;
        aWandererG = 15785090615465702179U;
        aWandererH = 15402064200000737427U;
        aWandererI = 11984310630099920223U;
        aWandererJ = 15052224047371524564U;
        aWandererK = 13891876694975644842U;
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
        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
            0xF498212B6C5A5BC8ULL, 0x219B3677CE16E03CULL, 0x11784F83602A7A32ULL, 0xA9C217EB34327144ULL, 
            0x5EBF31EAFD3A33BAULL, 0x6686090CA9EFC8EAULL, 0xB08921C635C5A36FULL, 0x32DB9A82DACD4497ULL, 
            0x9D852FA2C2F70991ULL, 0x6A647480C76EC7BCULL, 0x8DCEA06FB67A2211ULL, 0x584B027FC3F6D2D7ULL, 
            0x8A2291F459393902ULL, 0x06338ACD2039C6E8ULL, 0xF7019292C7524683ULL, 0x3B686B70074D268BULL, 
            0x22E553F1B3AB9DC4ULL, 0x8F5C1ED8BDCF6355ULL, 0x8E640841B1AE5623ULL, 0xBED70422DDF6F3BBULL, 
            0x0C4743B5ADB8D703ULL, 0xD8D7A8E241F8C9DDULL, 0x89EC4874B0870C53ULL, 0x70BBB2E553F895DBULL, 
            0xFAC5639EC8643738ULL, 0xF767394E8FE14D71ULL, 0xBC80FF9CEFC905C8ULL, 0x8B0CBDA03D5989A7ULL, 
            0x02602290C9D36A4FULL, 0x0FE9314BD98432EAULL, 0x259795B018202E3BULL, 0xAC8EB809FE9CB425ULL
        },
        {
            0x1ECC233258CB45EAULL, 0xD0D8FFBB5830823CULL, 0x7B3064852D15F02CULL, 0xC0214675E38191C9ULL, 
            0xE55B5DE420787D16ULL, 0xA75DB16B80472B6EULL, 0x72CB4582B8CF5961ULL, 0x50BF0755AA11FD2DULL, 
            0xFF5DF072AE5B695BULL, 0x943495C3AB306445ULL, 0xACCBC236456F4BFBULL, 0x300D5B24A5F56AB4ULL, 
            0x90EA5E210407EB3EULL, 0x0CD56E04EF301DCAULL, 0x8A0A478FA6F092D1ULL, 0xB18C580581968EB2ULL, 
            0x743912C287E3C71AULL, 0x1A2BC5893179356CULL, 0x75DD60470239B408ULL, 0x59043E7FC44C4014ULL, 
            0x5F246AD0AA600BECULL, 0x4733B330CE30C15FULL, 0x2359377A60F2C09AULL, 0x53A91AAB06DE46F5ULL, 
            0x5C2F18DE8E2E1B70ULL, 0xA881859F3F3CDD42ULL, 0x4212CC110EFD1DE8ULL, 0x26E21D75286D3C15ULL, 
            0xAF0A634BA4DBF417ULL, 0x782C9F0E49076785ULL, 0x87AF7A099A8A288DULL, 0x837BAF28AC43C928ULL
        },
        {
            0x043C87992229A757ULL, 0x5589AB3FAA3F9410ULL, 0x76FAAA64966D73FFULL, 0x5D8043BB6D224709ULL, 
            0x26FA232D5C8592B9ULL, 0x1B11CD4A15927852ULL, 0xDCE313E3C71FD1BCULL, 0x10158666ABE7D806ULL, 
            0xEDC34E9BA3CEA9B3ULL, 0x07154F39689FBAB2ULL, 0x734DC986E2EFAD3DULL, 0x536EEC0D0545C714ULL, 
            0x930FB5F2BCF895D9ULL, 0x392FD62D7110D322ULL, 0xCF76FFC2D039B2AEULL, 0xBF090E4E58F23F5EULL, 
            0xB53415F785F33A95ULL, 0xBA6B895F76F7FA69ULL, 0x5E54E9F72935536CULL, 0x715591BF9A666B33ULL, 
            0x0F011BBC5242B70EULL, 0x9B2E207A9EE713FEULL, 0x69451A86A394B7E5ULL, 0x64358E19EED27DF4ULL, 
            0xA21DC648EB79CD95ULL, 0x4957EF2329865906ULL, 0x48DF2B72D1059018ULL, 0x15AE97DABFED7457ULL, 
            0xBF5E2BB4C65B65A4ULL, 0x7C62663C9063D076ULL, 0x28FA3BB6B0B1F679ULL, 0x92F669B45E7C2C6DULL
        },
        {
            0x7369714062770FA5ULL, 0x67812C8E4C7934E8ULL, 0x85733B991599393CULL, 0x130221118E2BB8F7ULL, 
            0x9DDAE76E49C98E1BULL, 0x0643779D49F58CB8ULL, 0x43ED1A4E92431A6AULL, 0x98045AD82BF26099ULL, 
            0x63302A2D0EB9DCAEULL, 0x2FC2F8B5047E653CULL, 0xB6D0B9B5D1B521E4ULL, 0x144C0BC97A655707ULL, 
            0x949E7F620FFE33F5ULL, 0x62EB56947DBEB8F8ULL, 0xBB319738C394529AULL, 0x24D518788F119C54ULL, 
            0x5748D9CDFBAB1C0EULL, 0x69664352AB8B1552ULL, 0xB91AAC9B8B312C47ULL, 0x9F08A5AAC481E891ULL, 
            0x51D54A66FFBFA4D5ULL, 0xAB81DAED40765779ULL, 0xB53B14C18FEC3BC0ULL, 0x7CEB778075B34900ULL, 
            0x99CF88D7BFB227A9ULL, 0x07B7EB319D9BC121ULL, 0x6D0C2FDD31317653ULL, 0x59A5785281ED1A71ULL, 
            0x49084E2D0EC945C6ULL, 0x382CAE1BC1D84E7EULL, 0xA606F084CE73C641ULL, 0x1477E60515DA90E4ULL
        },
        {
            0xCB73CF78C959EAF6ULL, 0x4C9886906962FEEDULL, 0x59D17CDECB83ED9AULL, 0x3EFD4707C97604B5ULL, 
            0xA32B62B8FBF31C1AULL, 0x5E17AD5F5499E1BBULL, 0x47478785E8AD8D37ULL, 0x12BBE408DAB11FC8ULL, 
            0x6F2133701954F7C9ULL, 0xF769F0F0A7D9F381ULL, 0x5579E07743FA9144ULL, 0xB7DB2F5E60EC2802ULL, 
            0x99E55E996EDC1B52ULL, 0xADD7195387EC37D5ULL, 0xCF4C92136B715623ULL, 0x82A4080829623DE7ULL, 
            0x898AA52962DE711EULL, 0xC214DD4263E3D372ULL, 0x83F14C59C9068789ULL, 0x27961DDF237903BDULL, 
            0xD8AC6CF1B3EFFD77ULL, 0xE37687058CED4928ULL, 0xB281BCDD68317A52ULL, 0xAB1E7B0D6A16C00FULL, 
            0x2BEE1B5A46914EB0ULL, 0xB96BB08A700E7BF3ULL, 0x3F5E0C40188BB602ULL, 0x1F08B288703C965EULL, 
            0x1B9814FEA1C6BE9BULL, 0x4F25A0727441FCF8ULL, 0xA11793F51CF87C1AULL, 0x08DE99AE95602E06ULL
        },
        {
            0x32F545CC685ABD4AULL, 0xEFA216FF328817C2ULL, 0x76E2E9C848C86108ULL, 0x2FB64C458F30034BULL, 
            0xF464D32DE948BCB7ULL, 0x0805CA13A2BA3A05ULL, 0x5747957585D15D4CULL, 0x8CDE774B58B6461EULL, 
            0x842B66A00BE3B743ULL, 0x72E6850F1976993EULL, 0xA3E1F2F6B2F22A03ULL, 0xD8621856747CF8D5ULL, 
            0xDDCDF50DFFE89048ULL, 0x5BA415B6C38E157BULL, 0x19D49344211B2D64ULL, 0x6F59165CE7D64273ULL, 
            0x75DC06451DB998E3ULL, 0x7F53E37B3F1B70EFULL, 0x3FA38DE7F7769C4AULL, 0xECAEADD2809F6920ULL, 
            0x57998A9BC3683442ULL, 0xD2A2157069A65984ULL, 0x500E0C7EBA877609ULL, 0x6737C95EBDF14579ULL, 
            0xABF9BB738681DA4FULL, 0x732C6CCD25993C21ULL, 0x30C2B52019907CB7ULL, 0xF96D034C419639CEULL, 
            0x119543FBA5B550F4ULL, 0x899BBA3D45A57B12ULL, 0xFBFF2A4AE53CD598ULL, 0x75ECDE30444E83F6ULL
        }
    },
    {
        {
            0xE17875E78ECA4D86ULL, 0xD0C2650920D5C554ULL, 0x682BE50066083DE4ULL, 0x16C8A30573301EB5ULL, 
            0xB122722EEA9DF770ULL, 0xDDD5999B0B0CE158ULL, 0x53EC4A25AA63E09FULL, 0xBD86D4722E72ACC1ULL, 
            0x7550E14977D11985ULL, 0x02854B6938658E89ULL, 0x3AAF5E75EBBF229BULL, 0x6F1CE16813592B8CULL, 
            0x8B534B4C393BE909ULL, 0x2FCCF35775D522A9ULL, 0x3019AC667ABAEDD7ULL, 0x90E235CFA452AB7CULL, 
            0x6BD01676988C4ABFULL, 0x927A33FB3F1AE175ULL, 0x802A9F1032956B3CULL, 0x062D64390136CD91ULL, 
            0xBE5AF4A66FA0A15CULL, 0xC01D7434DFAF90EBULL, 0xF06BF75FFCC9848CULL, 0x36F98CD0E4E9A0BCULL, 
            0xD4B82CC67990FE87ULL, 0xA0624B9D138291A5ULL, 0x434A1A6D93DAA7EAULL, 0xBD690CB70F9FE2EFULL, 
            0x13919A2846E7A400ULL, 0xF7CD16D96CF37C43ULL, 0xBA4B509A84C4310DULL, 0xD55C1300D7FD7A69ULL
        },
        {
            0x6453D7199FA36498ULL, 0x4B27F2B6B702A2DFULL, 0xFE06A6C4BCAFF989ULL, 0x1AF4EB7F8CD8DF08ULL, 
            0xFC408968B2BEE5B9ULL, 0x44C1E1479F3F4A01ULL, 0xC007CF723155383DULL, 0xA1D09950049E9535ULL, 
            0xEB0755DA34BC1A08ULL, 0x6C71AD7E10B1A834ULL, 0xFC546BA269294C0EULL, 0x08679CC3D69180A2ULL, 
            0xB2A821C04D33A5A6ULL, 0x73EBED34F91E720FULL, 0xCE3351B52853E20BULL, 0xAFF5D392AEA9D34CULL, 
            0xB5359CD33C831C3AULL, 0xF5557106FAD7BAB0ULL, 0xBF8280B21CBA4C39ULL, 0xC81154C80B205B2CULL, 
            0x5E3E6A66DF7B5AF5ULL, 0xA6B74034BAEAF333ULL, 0x888EBD5A4738FCADULL, 0x92E508D920608E82ULL, 
            0x63B8263B39391562ULL, 0xED5CAD572AE6942CULL, 0x215FA7C3B9B29117ULL, 0xFACE42E367A1F319ULL, 
            0xDEEA2C54E1408873ULL, 0x77E9ABC9EBB45800ULL, 0x4330E5981C91C214ULL, 0x239C0C28D10C0864ULL
        },
        {
            0xFF1255453C6D468BULL, 0x6563E405AF5563FEULL, 0x402B1FDEF0C2B8A5ULL, 0xE287BF092AE1F84FULL, 
            0x1FCE7037BF5B8E97ULL, 0x7F76BA6BC527690AULL, 0x91A58E08BE385E53ULL, 0x4A7B6B4FA0720693ULL, 
            0xFD1EF186A05D79E8ULL, 0x8007A6407F1A622BULL, 0xA731D2E307572820ULL, 0x7B15BC5C0E47C016ULL, 
            0x5BCEF88612BC0013ULL, 0x21E3650B9024461FULL, 0xEC29DA7AE07B06AEULL, 0x3DC2E7FD67B4A08BULL, 
            0xBE7865AB6DE9F5F2ULL, 0x5F69E70BFB9BDB6AULL, 0x83ADDB16331FF7D8ULL, 0x0F49B721177CCFDCULL, 
            0xF822110E7CB49C01ULL, 0xEED53CEF5DDDB2C7ULL, 0x198556B8975A4CEEULL, 0x3DF0BA56889D6C27ULL, 
            0x69A4DCD51FE14E5FULL, 0xECCCCAAAA2860A74ULL, 0xA6CDBAEF6BCBEB67ULL, 0x4185C3AA5C65EAC7ULL, 
            0x72361ED15C0A02E2ULL, 0x3DF12953ABBDD12CULL, 0xB6FC10B0CDA3F323ULL, 0x2E08E5A35BC93656ULL
        },
        {
            0x14D2CFC8C25A0A05ULL, 0x43DACC167E3B5AA3ULL, 0x8836226C1D55E72CULL, 0x188639F8AF03A464ULL, 
            0x3B3CF273CCDA094CULL, 0x5C6F3EC9151AE70DULL, 0x814B37A0A9FACA00ULL, 0xD6E6179B5B6B172AULL, 
            0x9DD9C888B64A90D9ULL, 0x812B90D0516538FDULL, 0x8AD7BF6E2727239CULL, 0xCE9D04E03717F216ULL, 
            0x40F3BD8517978600ULL, 0x171AF9E65DCF3A6BULL, 0xC27FE5850223B202ULL, 0x2D249BA6EA36D378ULL, 
            0xB2F5FECA2B1815A9ULL, 0x3F5E71A042ACFA24ULL, 0x5FF3A1570738B0F3ULL, 0xEA9DFE31F65C8A04ULL, 
            0xB38CA4D6470D6E41ULL, 0x07A666F83731605EULL, 0xA81AB1F78EA34665ULL, 0x2224589A45C20E25ULL, 
            0x6CBE9BB1BDD86317ULL, 0x07F2B43F2C7EDFD6ULL, 0x22AA030113442A2FULL, 0xD97775F7DFC5D9D8ULL, 
            0x426ACDEB8DC755AAULL, 0x8F61D7C7391CAC07ULL, 0x9C446D263311BD2BULL, 0x333C70D315922E54ULL
        },
        {
            0x9D6A1EB73806018AULL, 0x684999C6C7A1FFBFULL, 0x6811163A254F4C0AULL, 0x8FE5F636A56793DAULL, 
            0xA39C978025707588ULL, 0xFF6894A0B9A3B5C7ULL, 0x8BC7E078B115835BULL, 0x2B2FCDEB119DDDF9ULL, 
            0x4CB8D5D80FEFCACCULL, 0xF66BA2FBDFF5715FULL, 0xD83AB386BC6ABF2FULL, 0x91A2FF745BDF56DBULL, 
            0x977F62C402ABBCC2ULL, 0xE6C031186EB05BDDULL, 0x56D3BF9236B52E6BULL, 0x6089B7EC49E3C000ULL, 
            0xA13715F482302317ULL, 0x65746E30A65601E5ULL, 0x86DB34946A91096BULL, 0xDE86D8CF2B5E361BULL, 
            0x8C20CE44FC4C9F8AULL, 0xE2760EC59AF531E8ULL, 0x212A49DD5D0284BEULL, 0x0992CADF260CB5C4ULL, 
            0xB59AC2567F88AA07ULL, 0x53F8F54D26F18604ULL, 0xB48D631CF221FC60ULL, 0x872CB43A6EB28696ULL, 
            0x11826B000997C6FFULL, 0x9B5F9A7708616B0BULL, 0x915E1701F7BEBA4AULL, 0xB1459578ED00558AULL
        },
        {
            0x89611D1E485DB9AEULL, 0x984A7A3C639C2EA3ULL, 0x75DC460ECF7FE495ULL, 0xC4A063A76CDB3AFBULL, 
            0x337014C3435EDCADULL, 0xC337B854785616C3ULL, 0xF6A43B02A61935E0ULL, 0x2E21C3E96D2F3A74ULL, 
            0x1D546E652C6C2558ULL, 0x862D0E3CDC553760ULL, 0x58F8E7FDC9790AE1ULL, 0x72FD616C2059DCADULL, 
            0xCE660C070C8B47E8ULL, 0xD5807793E641ED22ULL, 0xB297F45A5722BCB1ULL, 0xBDCEB452253CCE32ULL, 
            0xC035E45DC29D33AEULL, 0xCAE2582D45FBC93EULL, 0x245D71DA619604A5ULL, 0xE961CEE23FF02C19ULL, 
            0x7971998C000AC1A6ULL, 0xCB51404BE3E557C1ULL, 0x89B7C0B11BB02870ULL, 0xD8974B90757E30F4ULL, 
            0x4171E31EAAC68F77ULL, 0xA0FD6603E01F57C5ULL, 0x6B28AF9697B75F6FULL, 0x2A26CE9ABC70011EULL, 
            0x1322F8A077845178ULL, 0x79D51FEC3EFC7AB6ULL, 0xA33B21ED1F7143D2ULL, 0xB2554BBF07D0D2B8ULL
        }
    },
    {
        {
            0x15741452EC3938E0ULL, 0x15E7F85ADC52A412ULL, 0xDE1C2BD1ABA9E542ULL, 0x4072F998E80E1CB1ULL, 
            0xD35130D26A2BA3F2ULL, 0x3A5FC7EE3B5FC9A7ULL, 0x0C736C819D8DE211ULL, 0xAA9EEC36A4A9532BULL, 
            0xE62B61D246CBE24EULL, 0xC5B0AD30CA2FD05CULL, 0x8013374F20E1A7D1ULL, 0xE71E9FC280730A5BULL, 
            0x1C33474CC798927DULL, 0xB0AC37FCABF103B3ULL, 0x354D107B8654E300ULL, 0xD3C754D753F50A14ULL, 
            0x1B97D37BBD1E89A4ULL, 0x572CAA2294022944ULL, 0xE452EAFA4B9DFC7DULL, 0x61ABB9238A12CFD8ULL, 
            0xA6BCE9D42E585D7CULL, 0x93C92EA7FAD3F490ULL, 0x9C7FBDCBCBA69105ULL, 0x778F84DD72E079F0ULL, 
            0xCF6DE7D81215F789ULL, 0x40570AC7C7ABA595ULL, 0x3BE65B76707175C0ULL, 0x0CDB98765411FF3CULL, 
            0x205D7C1AE21FF0D5ULL, 0xEF086275952F8EFAULL, 0x3E9181CDC9905125ULL, 0xDCF26E7DC8F32C4AULL
        },
        {
            0x0464AFF57F53167BULL, 0x7440C40C43EE47D5ULL, 0x34AB56F9A3290356ULL, 0xB7D8B2A6884CA91FULL, 
            0xA934374098A722E2ULL, 0x2837F6A011461B3EULL, 0x14C4FF84E3F9E783ULL, 0x65C9C5667080FB05ULL, 
            0xB034BDF51BF76607ULL, 0xCA5CAAF5C21EC409ULL, 0xCC30282FA7DC6EF9ULL, 0x99318417A5284E07ULL, 
            0xAB0F816B94A09337ULL, 0x924617076A43AA94ULL, 0xCA9AF4D567099270ULL, 0x36B4AA26CDF7D975ULL, 
            0xF14ABFD37C9B801FULL, 0x61321F2A6CE605A2ULL, 0x9C20EFC5BE5C654AULL, 0x6441C23F9F88C0EDULL, 
            0x3810197D935CAEF2ULL, 0x392153980305624BULL, 0xF5029C0F51A27D08ULL, 0x04DE7432D18CB838ULL, 
            0xB725B268CEA4B05EULL, 0x0F13DE7A4B53A796ULL, 0xEC50F2B545DE6E36ULL, 0x08AC58C47AAEF078ULL, 
            0x7D27342887F677AFULL, 0x78A2DF7066BEDE54ULL, 0x211ABEB44408B8F6ULL, 0xDB4C3C784E8AED63ULL
        },
        {
            0xFCBAE466D80D0A97ULL, 0x1668BBDFA8AEC169ULL, 0x1F5082DCD8D1B938ULL, 0xEB340F12F27FE3A6ULL, 
            0x55BB0E6F4802DF64ULL, 0x69A40C497DF2262CULL, 0x49CF3F0F789EDC9BULL, 0xA2B35045E89DC939ULL, 
            0xB7E54A636BA7DAA1ULL, 0xE6B8369FF8D8EEEFULL, 0xE977F27535994744ULL, 0x1B6616E901B562FBULL, 
            0x9E1388F3D6ABFC4CULL, 0xA27F720CB054A4A7ULL, 0x23B9FBCB0DF5563CULL, 0xC0AF3E457B05C5BDULL, 
            0x5A368040C1FFF222ULL, 0x511E632151579BA7ULL, 0x2367001906E73947ULL, 0xE8F5C6D2F3CB364DULL, 
            0x658535AE78558539ULL, 0xC410DCE0C24929E6ULL, 0x9BBB54C960DDB917ULL, 0xA1FC56A55FA64E85ULL, 
            0x246B2FC74F0E8A88ULL, 0x58A879E879155D63ULL, 0x77B2FC826D1112C3ULL, 0x1A87FC1A35BB336FULL, 
            0xC237137E8E1BEB05ULL, 0x8A147E382377B129ULL, 0x8152C3E890CC52D8ULL, 0x0148003E2B5A1A7FULL
        },
        {
            0xECB49F8729FB380DULL, 0x037AC84210CD1FDFULL, 0xFB6BEFBC992AEECBULL, 0xB2AE63B9E4802C41ULL, 
            0x982F0C511F216D10ULL, 0x9C92D98B6688C4D3ULL, 0x9E49377546DFE1CBULL, 0xB44A8E89941D0DB5ULL, 
            0x9553968D5EDB7177ULL, 0x808A5170A6C1A87CULL, 0x33D35323970FD8F0ULL, 0xB39780B61B01C633ULL, 
            0xA7FC28E6483228F5ULL, 0xC027C94984464A14ULL, 0x5C6CD889DC6D56ECULL, 0x7EF3FB6F55715EC9ULL, 
            0xAFF7DC73C9339933ULL, 0x4F237E8665637BDBULL, 0x462C6EB1AB564E9FULL, 0xC638394209556152ULL, 
            0x9E3201EDA65E70B6ULL, 0x58A25F67BB85DE18ULL, 0x65102FB4468D3944ULL, 0xDD986969DEC5B363ULL, 
            0x2B63B33B0459D60CULL, 0xB9876CC7F7D28BEBULL, 0xAF9B28F0F7CAFDC7ULL, 0x702638603702981FULL, 
            0x32D3A1B0FD73A89EULL, 0x968CD02894E71C7BULL, 0x5315E13148868B12ULL, 0x501FDB468B86F217ULL
        },
        {
            0xDC2CA7923D9CFD75ULL, 0xA6153FA3B41EB69FULL, 0x77D53512E25AF51BULL, 0x415154FEE1FBA50CULL, 
            0x6692589C318B7965ULL, 0x7735F507E7DAE6BEULL, 0xE0A43CBB11C34B18ULL, 0x6561BFEA6B265A14ULL, 
            0xD74A4B281AA7FF12ULL, 0x5360011AC58E4ED2ULL, 0x0F73F442A4A178BBULL, 0x83038E4211652A47ULL, 
            0xC379E666611A0E19ULL, 0xC318D3CD29D546AEULL, 0x276B5CC904484B87ULL, 0xB92F7E56D2C0A078ULL, 
            0xE1650757485318C4ULL, 0xA8486520AEE4E803ULL, 0xF6A5B7C8DD2812E1ULL, 0x07E1E435544F819FULL, 
            0x4DBD89A83C8CD875ULL, 0x3272E7D44A7CC649ULL, 0xB3ED3B37EFF10100ULL, 0x456298921826C258ULL, 
            0xEED089BFFD36726AULL, 0xE1D6FF8767DA776CULL, 0xA3A35BA8BDAE2148ULL, 0x19DAA59927FA00DEULL, 
            0x100408AA27E6AB5CULL, 0x0B36F21E372E87DEULL, 0xFE08A7456DA78A1EULL, 0x2C0194E51F5C063BULL
        },
        {
            0xEE3956690028A44FULL, 0x7E459D15C7A6E8A5ULL, 0x95DE5A04FCC28A42ULL, 0x0FC6E9DE8E813EB5ULL, 
            0x25C7ABA28EADCC2CULL, 0xBDAA66D31A6993DEULL, 0x1620E0E0DA2BA9FBULL, 0xD585319971E19920ULL, 
            0x41440FB5FAE1734CULL, 0x34DEE4D3D100AB1CULL, 0xD44908C5F7E56294ULL, 0x1D8C981C0D318737ULL, 
            0x4E2777FD87702771ULL, 0xE4C2F8ABE75179FCULL, 0x47769D18CC42A745ULL, 0x175FDF283D1C3823ULL, 
            0x7A48EE337A4AD347ULL, 0xC867910D4F2B2FACULL, 0x9A682FD8A975B4FCULL, 0x8A7B956B382B1942ULL, 
            0xC261145952657610ULL, 0xE58DBE9B3D49F265ULL, 0x67163436261D4943ULL, 0x5984B56E7238667BULL, 
            0x8B7E19ADD0478B56ULL, 0x7C0205CE9BDA98C3ULL, 0x8D06804E98416135ULL, 0xC323B3672715DE7DULL, 
            0x4CFB95F61FF58095ULL, 0xBA289599127B42D8ULL, 0x0B610B7E5D7333A3ULL, 0x03BA9859EA74B912ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseAConstants = {
    0x8B013E5FB2E135FBULL,
    0xF4B5111CE4FC9553ULL,
    0x9B24EB3DA4356F67ULL,
    0x8B013E5FB2E135FBULL,
    0xF4B5111CE4FC9553ULL,
    0x9B24EB3DA4356F67ULL,
    0xBEC012C9B0BAEBC5ULL,
    0xE3BF06563E0E2D88ULL,
    0xAE,
    0x11,
    0x92,
    0xA9,
    0x51,
    0xDA,
    0x2B,
    0xDA
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseBSalts = {
    {
        {
            0x50DF1079354D3978ULL, 0xD160FB2A1EEB9E3FULL, 0x7518DFBAB2BA9B16ULL, 0x919E13A8002CCFC5ULL, 
            0xB5412BDBF9FC0C1DULL, 0xC5BF2A0C8A368792ULL, 0x42DACF2CA5526E2EULL, 0x8634B4163A88C94BULL, 
            0xF2D1E537017743E6ULL, 0x1D1D8E5307DF1D30ULL, 0x7ECD67AB5C4D6568ULL, 0x6C2CF8E791406A41ULL, 
            0xB9D786E647136B96ULL, 0x9CDEAFEC4C203676ULL, 0xBE1C712A8D8C0B3CULL, 0xA4125BFCC22E593DULL, 
            0xAE7CC78676FBB283ULL, 0x5C5D653A688B9DC1ULL, 0x2AE14C15091A942FULL, 0xAAF726BFFEE766A1ULL, 
            0xCA4D8F89F27CE4E7ULL, 0x7A9BC64FB3886131ULL, 0x1D3DB9AE08920D93ULL, 0x6810E0F51F4EF377ULL, 
            0x931F067B01C28837ULL, 0x0710E15F66928317ULL, 0xD2B14894EEB78DF7ULL, 0xFB724024078F74C7ULL, 
            0xDFE32D0FA725A893ULL, 0xBDDF365A185CF13AULL, 0xB9E4A2F9A64E3839ULL, 0x6B5D67969D9234BDULL
        },
        {
            0x5EEA25AC4A350A8BULL, 0x01FDDF3BE4E54F67ULL, 0xC8FF5FEA618639ADULL, 0x4D3474A695F32C96ULL, 
            0x5645258D48D2A51CULL, 0x2B634A0DF5D8FB13ULL, 0xBBD46C8CE0EED767ULL, 0x6BDE97FD4C4D5E34ULL, 
            0xE14627D5F31479B0ULL, 0x2717F6ACDEED581BULL, 0xF68067749F3D92E9ULL, 0x6879E8B8F3A05A16ULL, 
            0xDD07E95B2B097F10ULL, 0x1CA2DB8186221864ULL, 0xEDC8B25CDEC85120ULL, 0xC240886CC196380CULL, 
            0xDA5A244A7BDC319AULL, 0x8C07D4563EE40EF4ULL, 0x1BF6322ABDE4D723ULL, 0xDFC393EB7A8DD493ULL, 
            0xAFA2F4D043BF0C5FULL, 0x0D305A3FADD9266EULL, 0x02D39B5B352490A8ULL, 0x73093BADE6932CD4ULL, 
            0x2416BBAC808D3E2AULL, 0x68C186A7D5EC322BULL, 0x6CC9857CF993C774ULL, 0x72574A43C6666D8CULL, 
            0x8C408FADA46C2CDCULL, 0x21FDFB28CC816B14ULL, 0xF0E1314686C63AFCULL, 0xC7C8A39127834B33ULL
        },
        {
            0x20767B44375813A0ULL, 0x07C941F6706FA6ADULL, 0x376FC74582514D68ULL, 0x68DCD07577C3CC80ULL, 
            0x2ECBBD081300EA75ULL, 0xE9DC05A17C221765ULL, 0xFF07A9592DE93688ULL, 0x2161524A4C080981ULL, 
            0xECC5D93D2D1116ADULL, 0x1651E90BCB2FC48EULL, 0xDA9B54C97DF63A81ULL, 0xF06F36990C583FCCULL, 
            0x44416BFD9F413BE6ULL, 0x558844B9350B4BAAULL, 0x3D5E26B6F3BEC72AULL, 0x593A1ED35A9433D2ULL, 
            0xD3C4C94B313EDB6BULL, 0x2EECF1055A836249ULL, 0x2D06029C1420AC99ULL, 0xDE4D655001E379B2ULL, 
            0x309BFA1CC132576EULL, 0xCB4A36CF8452F5A7ULL, 0x05B50058D0FC274EULL, 0x03571230DDBD05D4ULL, 
            0xE12D98C57B53E476ULL, 0x4965AC6EE3F5659DULL, 0x99EE1B40C0AAD6F0ULL, 0xC721746E1EA41DC2ULL, 
            0xED10FFF73098B5D7ULL, 0xD82383601305A13CULL, 0xD33DB32E756B974AULL, 0xCBA850F9435DE10CULL
        },
        {
            0xCD298F328EBEE164ULL, 0x6E178D591000CCB4ULL, 0x1DA3BE2260F0C2A3ULL, 0xB9EC64ABF75B14BCULL, 
            0x8A3FC9C9293CBCCBULL, 0xBFF02D726F5282CFULL, 0x3BE84267176B5EBFULL, 0x607872ABDD0D9529ULL, 
            0x3A40875F71301A0BULL, 0xD9E659DDFFFAD27CULL, 0x2AEE960C1436FF3EULL, 0xFFC81E1AADEB056FULL, 
            0x844C3FE9653E6C7AULL, 0xFD28768BD4F30E92ULL, 0xDC07BE13FD830A63ULL, 0xA021789E1D0B2E5CULL, 
            0x58AB2038CB03B30FULL, 0x70F256904A8217EFULL, 0xA9913F97EB73861EULL, 0x4AA751AEE06E9142ULL, 
            0x5AF77999BF654374ULL, 0xDF880E56E1C07338ULL, 0xB40228B810BB8D78ULL, 0x2AAEAFA8E14E4682ULL, 
            0x75979A30BD9A8548ULL, 0xC18489BA5892ECD6ULL, 0x9D54C951C7AEF60BULL, 0xF46516A18F4538B6ULL, 
            0xDC9F38C7BC6E2CF8ULL, 0xCCAC32905C11C9E0ULL, 0x8F0D6E4663759B6AULL, 0x23414216D3FC5054ULL
        },
        {
            0xDFED96C8507A5CB6ULL, 0x91CE67FDC9D50003ULL, 0x3B58419EF627EA90ULL, 0xC6ED6C98985D5AD7ULL, 
            0x76EC39D5FD8D4609ULL, 0x8F1B68C813D13162ULL, 0xC7D9D84FA5F60C83ULL, 0xB281C0AC2F9F92AFULL, 
            0x13C0821738A83755ULL, 0x6686312ADC635FC4ULL, 0x52B626049E3AD2DEULL, 0x375B1DEF35FC8CA7ULL, 
            0x7861CFDE52CC05DAULL, 0x332200E58A481BB1ULL, 0xEC6E8D41F8DE65F8ULL, 0x39D594C73F9723F1ULL, 
            0x53992D9D00BD3381ULL, 0x19CE898BD68E23B0ULL, 0x4F99C56EF86882ECULL, 0xE6B679BB2B1B119BULL, 
            0x8149919251BC0D24ULL, 0x85E78252A66264E8ULL, 0x823FA8078DD3530FULL, 0x3AB04A1BFE7568EFULL, 
            0x386930C5806DD4F6ULL, 0xD24610A40166999DULL, 0xB321545C80F730CDULL, 0x670DFC27839F56D6ULL, 
            0x0DE368C66B8685EBULL, 0x45566A19A2E49A6FULL, 0x539D31F014BECA9DULL, 0x2CCB21557B1E41F2ULL
        },
        {
            0x0BB38AC94A784C45ULL, 0x10A529595768B71BULL, 0x09B298139494293AULL, 0x763C7505A4D286AAULL, 
            0xBA22EE020B6E3880ULL, 0xB80120814DBD45F0ULL, 0xE5179448FBF0C151ULL, 0x5C48786E6E956667ULL, 
            0xDAD5264573F91934ULL, 0x67096053512DE515ULL, 0xE6F140980823A603ULL, 0x574CC97DFD9872CBULL, 
            0x1A567FE8023EC08DULL, 0x4AA940D613B98CB0ULL, 0x6DFA1263F23AA3E8ULL, 0x05698BAFFE7896A8ULL, 
            0x06268FB8DD51D52EULL, 0xAD85149B99CE39AFULL, 0xCF407B20AABAE64AULL, 0xBC1D894E36FA072BULL, 
            0x0705BE839B62E600ULL, 0xF2759B8637C25E97ULL, 0x6A4C967E951C1039ULL, 0xB2AF59B67953CF04ULL, 
            0x93B1155274E78E3AULL, 0x4E8D77840B5DF0B4ULL, 0x2805956529976F67ULL, 0x5E933465E3137D93ULL, 
            0xC4B50A1AE5A74806ULL, 0x11A236A2E6F3D8F6ULL, 0x98A5BCCE822DC756ULL, 0x332A8D5B298CEA17ULL
        }
    },
    {
        {
            0x8B3EAF038C639793ULL, 0xAEA3BE28559A8CE3ULL, 0x9EEBECB21AE58F1AULL, 0xB313E699B3976A40ULL, 
            0x0D3C1B25C5FB37B0ULL, 0x6F3C0F8B3578C393ULL, 0xB134C6999E527A71ULL, 0x9052D591DF9D4C60ULL, 
            0x0A6134633A0FE2DAULL, 0xCA3E055D3B8C33EDULL, 0xCBEB5DB8556B04FEULL, 0x8F4D3A3B5D577261ULL, 
            0x52ED5B33F1D68F40ULL, 0x53F220A33CA9D610ULL, 0xCFA02F31EAA6FA08ULL, 0x0DD438334244B923ULL, 
            0xA94436EF80209DBAULL, 0xE6E23B2970BCA93CULL, 0x2375ED85C4C8CA11ULL, 0xB2A1ABAEF5A0510DULL, 
            0x495CDAF732F7DB5AULL, 0xD8A068D316A25A1FULL, 0x87FC7F0F3E5C4827ULL, 0x5784113FA60AC441ULL, 
            0xE5343407FB39D1ADULL, 0x2C0A7BEE2B19ECF9ULL, 0x16DF6D1B577B03D1ULL, 0x1DBDA0CC4C00004DULL, 
            0xA008D9D21B7C4841ULL, 0x3636E650AC21E91BULL, 0xEB2E89B91A69D7BCULL, 0xEE56F6273D3BD0C3ULL
        },
        {
            0x45AA7C5B7C8284ECULL, 0xF491AF9167E12322ULL, 0x1202A8947A986B3EULL, 0x891E292109E07F52ULL, 
            0xD3F574D426C7D2D7ULL, 0xE8E385FF8BE13FD0ULL, 0xD1493E5701FDF0F6ULL, 0x2E9F2BB6FE735836ULL, 
            0x625D5B2B73812307ULL, 0x38FB556E18CCF7C3ULL, 0xA11A54299413DF1AULL, 0x41721267F89E96EFULL, 
            0x00A475B698EB850DULL, 0x219E0EABE7875894ULL, 0x96CB7C0593CEA20BULL, 0xBB83A36B21A9F88AULL, 
            0x78A9A4B4D8AECB69ULL, 0xEC230E94E3445EBBULL, 0x234BE3BC132330A7ULL, 0x30DEBBEA81A7EAD8ULL, 
            0x8C4985AB642DE8D9ULL, 0x154749AC79BE1DF4ULL, 0x4D541723732430D4ULL, 0x675EEDCEE0480793ULL, 
            0xBA1FDFA4B5E4D6A5ULL, 0x4C05D5CCCC80B447ULL, 0x4D25CAF1A86C0F97ULL, 0xF7C271562E77F6FFULL, 
            0x3F9AA59E0BD040D7ULL, 0xBB22E03429A65A00ULL, 0x62CB1C48F7000A3BULL, 0x834A7CD2B6F98D58ULL
        },
        {
            0x3088B712F20F0680ULL, 0x0508047A0ADEA601ULL, 0xAE8EAC12CCA5C314ULL, 0x7A74C79912EDBD0AULL, 
            0xF6F652515C26CED6ULL, 0xD4DF7BA26CC37F0BULL, 0x9156DD6509D671EFULL, 0x9099A9656598472CULL, 
            0x9DAEB86C1AC74438ULL, 0x4877F060D7FA8B68ULL, 0x2B8A3ABC6404B15FULL, 0xD56FA25B4EF3916DULL, 
            0x233E6C00FB02A6BBULL, 0x7D8259AAA7434142ULL, 0x75A34E5901D9C37CULL, 0x24896A80359DC7B2ULL, 
            0x853B54F14EB244D6ULL, 0xEF1C4488A16CA435ULL, 0xBED636439453BC57ULL, 0xC886236E3AC65C49ULL, 
            0x8D5EC9DAD6E29BD3ULL, 0xCAD1F24FA77BC718ULL, 0x632341D176CD5350ULL, 0x3ADB936D9CCAE228ULL, 
            0xA2333AD69669D625ULL, 0x4B2DA63CA77FA1E3ULL, 0x5EE717B09373FE84ULL, 0x9F95A7BEB1732DC8ULL, 
            0xD70E238611952D3EULL, 0x663ABD5D3F8CDC61ULL, 0x2BEB7AE290ED82FFULL, 0x316F238AAECD3995ULL
        },
        {
            0xCE07A5B21AE73C6BULL, 0x764B45EF552DE308ULL, 0x26487F4141F1BF91ULL, 0x64AE7BB5DC0462A4ULL, 
            0xCC6D1D32AB0EC8F1ULL, 0x3DD803A02D5A5D60ULL, 0x89E96D1A4101D919ULL, 0x9CE26DCCA8A248A7ULL, 
            0x2D302C4B1F891F15ULL, 0x236D3B74976E8D2EULL, 0xED18950EB1417E97ULL, 0xADDA06CDE6DBB481ULL, 
            0x2CFAD2C079C10350ULL, 0x457321CE91017B1DULL, 0xEEBDA39EA57C2460ULL, 0x46B08CF362E80230ULL, 
            0x17F92BDBC9FC6FD9ULL, 0x97641FBCAC0DD637ULL, 0x3EE007594587D688ULL, 0xFF5C01784FC54129ULL, 
            0x1F500B60D933A4B9ULL, 0x33E30150D70DD707ULL, 0x115CAC33D0BBCB0CULL, 0x80D33796DF8F14B5ULL, 
            0x2C95998BF2B78DC9ULL, 0x8B3BA5797E5BB0FFULL, 0x44DF7045E84A4B31ULL, 0x4BCB744B81575502ULL, 
            0x563FF12C7F8C3A6CULL, 0xCCEFA95505F89273ULL, 0x92F7307F58F55714ULL, 0x11BFEC673BD5965FULL
        },
        {
            0x3EBA2BC52CCD82ACULL, 0xA890A80D5EDB06E3ULL, 0x51E05850E0DD05FBULL, 0x6CE35354856D10DFULL, 
            0x21054304F6B92B7AULL, 0x5553C922E51A5BE7ULL, 0xD718BCFA00B9C21FULL, 0xA391C0694F77B3AEULL, 
            0x28DE6F81C7CA1F9AULL, 0x40719A552CB75104ULL, 0xBCA6C2CA14B930E9ULL, 0x4241D21BAE921B52ULL, 
            0xB5485AB6B43A164BULL, 0xE1FABA15660F0B85ULL, 0xA328D57A959E0438ULL, 0x8DC3D2B55167EA9EULL, 
            0x8BE3B7CD0A3CAAB4ULL, 0x8064B78E30B6EAD8ULL, 0xED2270B3F7C4FFE1ULL, 0x12E57CFAC0A1EEFCULL, 
            0x949D4682E64E29A8ULL, 0x7F4E1D443B66610CULL, 0x74BBE9D2155EAB9FULL, 0x6C85DE67418182A3ULL, 
            0xD6C9A7172A2F322CULL, 0x3F023A3ADF011955ULL, 0xE9117CA6A8F810F1ULL, 0x1367BF4B2816E028ULL, 
            0x0CE6776017110905ULL, 0x00C34E66EF828FADULL, 0xBF088172FB26712EULL, 0x3A5C7D3E04BFCF63ULL
        },
        {
            0x7F5C3542EE3C5709ULL, 0x33CD2BB1FF484F4EULL, 0xAD3671F405F676D6ULL, 0x442E105749F2C84DULL, 
            0x88579A12D52FA1A7ULL, 0xE4826A34964772B6ULL, 0x3BF4E2D7F07D069AULL, 0xAFE264AD88D6BA2CULL, 
            0x5600E5772F9F43A2ULL, 0xDFF2BBB661894823ULL, 0x41EFB0586E42758BULL, 0x629B09FD8EE84D66ULL, 
            0x9140490350113FE5ULL, 0x30D525FCAE8BA667ULL, 0xAAB27B475D681721ULL, 0x330521A7F57FF4DBULL, 
            0xF3F7CEC1BF423A5DULL, 0x14F5FBC04CDD48ACULL, 0x42A5F58B359CF9DEULL, 0x8F3B42AD8EBAD99CULL, 
            0x019CF46DA89C9427ULL, 0x08581802845F9798ULL, 0xF8A447170AEDF77CULL, 0xFA07A4C952827176ULL, 
            0x6690D60FF2FA475FULL, 0x62C566EC5B605566ULL, 0x74CC85F5563F6537ULL, 0xCF292E4E03667ED2ULL, 
            0xCD7D5996612FD19BULL, 0x640EE9728887747CULL, 0x1A6B21DE489C3DF2ULL, 0xBB7C9408DCBE615CULL
        }
    },
    {
        {
            0x99514ABA78464E0CULL, 0x5976D55D93AFE4D8ULL, 0x96CE42496DFB57A0ULL, 0x7065EDF5A8AEF8FFULL, 
            0x58B00A5BA0014FEAULL, 0x8006599E66E0D150ULL, 0x267F9992343FC78FULL, 0xC55A880841052A5DULL, 
            0xFED131E9D696DBA8ULL, 0x6217937F5CC7367BULL, 0x56BB77A0FF3756ECULL, 0x877C10BA71147E66ULL, 
            0xA1FC4F1EB40E4D80ULL, 0xF11322CCF0BE4093ULL, 0x24E4C88F731C138CULL, 0x1D38D01FFE26D7C7ULL, 
            0x6516A23F4BD02D92ULL, 0xBD7E3EF9C072E73CULL, 0x19CA0F271E1E1449ULL, 0x5A38480B947B57E6ULL, 
            0xEF2D2CFB7AAF2F5EULL, 0x48D263EBD1D69383ULL, 0xAF4D4CE3283B2BB8ULL, 0x923AAB46F6B41D2DULL, 
            0xB7D49A800F1BC6F5ULL, 0x0024E70E4EF4C005ULL, 0x98D66AFFC5FF3143ULL, 0x026B983D6D6A7ACFULL, 
            0x49FA1AEE255143CFULL, 0x0D13BC5785A55F08ULL, 0x146A56A0CF066FADULL, 0x8F2A696C6A4E771DULL
        },
        {
            0x80AD6B2662517052ULL, 0xC4C797A4882AD54FULL, 0x1E93AB30180AB712ULL, 0x60B765A7DE74D871ULL, 
            0x6DA9EAA95EFE24E2ULL, 0xC63C2309045FCDF8ULL, 0x0C646FC3421E1301ULL, 0xC402F651D03277ADULL, 
            0x993C2B9521125A3CULL, 0xCB106B33D4C27037ULL, 0x391F7B3C4E5C37D4ULL, 0x537894E3619DB52EULL, 
            0x79CD4DE5472986DCULL, 0x1BDDB936301EC2DAULL, 0xF721AB2C0210F682ULL, 0xADC488297F1BEF30ULL, 
            0xAD6AC0AE2671A97BULL, 0x70AD7E7D92FED8F0ULL, 0x45983883ED8DCDC1ULL, 0x64BAF32F57E2872CULL, 
            0x508FD30585AF216AULL, 0x139A0F01236A6C12ULL, 0x6017DA544425F215ULL, 0x2203BCBA3F2A05A3ULL, 
            0x5FD89AEF6D6FDBF1ULL, 0x67EA27E830408052ULL, 0x03192C334F657B79ULL, 0xD57720D3483306E5ULL, 
            0xF2185C20EAB2F747ULL, 0x458891CFDB447B9AULL, 0xE26921D5780CA6A1ULL, 0x7E221CAC0AD72E10ULL
        },
        {
            0x6BEE967B6B1C1507ULL, 0x44D387EC047D3199ULL, 0xB47392A44B0A797DULL, 0xC223F53BAF2C5B12ULL, 
            0xB73B32E42A2CD0C5ULL, 0x75F98A0E1D924183ULL, 0xEA34867DD0759A93ULL, 0x76B7D249523AE95DULL, 
            0x9B2AE18D7CD0C6F5ULL, 0x5D9E3172E7868B80ULL, 0x324AAF2A22567097ULL, 0xF15928BBEA3F0526ULL, 
            0x175DEF0A0BE8DD5CULL, 0xC32B3EECDA5FD7E8ULL, 0x35FD7494A36BFCC6ULL, 0xB07C25236E5CEC9DULL, 
            0xBBCAC48BD6A444BEULL, 0x90C3F3E68CC40A88ULL, 0x15B34CF828E17A6DULL, 0x7D00D62CE3F0D9D9ULL, 
            0x5B3BD516A5C607F3ULL, 0x83FAF19E8B14FD78ULL, 0xA760CF64269B1A32ULL, 0x54D8854A784A90DBULL, 
            0x0744E36E7902A184ULL, 0x3C9BA6DEC12BD1F4ULL, 0x8A68D3444BA8170AULL, 0x7FF6A8EB76406B46ULL, 
            0xC41C50A76A76A75EULL, 0x82165921DCF5A596ULL, 0x7C2630D56C30E202ULL, 0xF7D09C0CFACF16F4ULL
        },
        {
            0xAE7DF21AD191C647ULL, 0x176ED179BF4748B0ULL, 0x59AF2E6CD8FBFB02ULL, 0x8CB1C722ECA720A3ULL, 
            0x7766CA5ABA7F9474ULL, 0x4931DF38EFC7DB19ULL, 0x29ED99C8750B5179ULL, 0x79E7B093D2B9EE55ULL, 
            0x26B848A97EBB6AB3ULL, 0x4C935263450774BBULL, 0x8C0FD40750CE15A6ULL, 0xFC02F98B7ACB3AFEULL, 
            0xD2EC549F0CCA4B4BULL, 0xE1D81594176B58D6ULL, 0x8143F912269EFC95ULL, 0xD4A020815CD2FB99ULL, 
            0xF04189D127899FCDULL, 0x20D741E63EBF2547ULL, 0x8174A04E691EA558ULL, 0xD186656FD27BB5BAULL, 
            0x997471411752EFEBULL, 0xEDE53D2DC5FE109BULL, 0xE9EA467D3B7F2725ULL, 0x0C8168DDBECD5643ULL, 
            0x90AFF4D0BE6C4F2AULL, 0x3C3D3AC3E08D000FULL, 0x23C88F8437A0E998ULL, 0xA8DFAD4E94E0A56BULL, 
            0xC05036E3270EE4DBULL, 0x7519AFBF7AA68ACAULL, 0xA76AAB670F64F8FAULL, 0x82DE0177C0BD4E37ULL
        },
        {
            0x484D7C1B51B8AAD8ULL, 0x90116AA4F6334A29ULL, 0xAD1155B72D5C12F5ULL, 0xDA3166F88A00F69EULL, 
            0x7D3BA729CD8FDD67ULL, 0x76983CE4D0780D36ULL, 0x87C9F59C0BFD7D2EULL, 0x599C063B089F0322ULL, 
            0x462AB270B4BA487FULL, 0x33301931FF02A73AULL, 0xA8D682FC1A064FE2ULL, 0x6A6C4002F02ED52CULL, 
            0x4EC273B2732D5234ULL, 0x04A10385F71E54D9ULL, 0xA0AE4822D8B2D2D3ULL, 0x134669EF49AAC6BFULL, 
            0x4AA69498A0718303ULL, 0xC55E281E84C4A009ULL, 0x20017B8F00E1246BULL, 0x28B8D9F35FE1ACC0ULL, 
            0x0224B641DA780574ULL, 0x14905127BEA3CA51ULL, 0xA14CD823F8A99277ULL, 0x458242E1263D7C53ULL, 
            0x6766C21699502BD4ULL, 0xD59630C25B12B524ULL, 0x9054E58964621515ULL, 0xE691678084E4C2FBULL, 
            0x805F3F266027206DULL, 0xBE1A28A0913F9EF7ULL, 0xD78687BDEBA910E2ULL, 0x092CE13A4865D8BEULL
        },
        {
            0xED741883FAAE8541ULL, 0xED0F88D001BCFDD7ULL, 0x29236E18780E8716ULL, 0x6C3A0BDC26E34B75ULL, 
            0x95C2ACF7B8A968FBULL, 0x3433C529A3C7BF6EULL, 0x58C6043A374A489CULL, 0xDBEF28BF1C4F46B5ULL, 
            0x895E5C9F0A50B8B4ULL, 0x6B9E0B63A7998CB5ULL, 0x003D821CB2779DD4ULL, 0x3FEF03B596431FCDULL, 
            0xD6ECE6C47E34AF3DULL, 0xD27848133018CE25ULL, 0x3918C642B3CF5218ULL, 0xDF5E95C2D6F47F3CULL, 
            0x250F09A9F47F6DCDULL, 0xD5AAB58E7F443F1AULL, 0x486C5DB5CC8CB1BAULL, 0x4FCBDE821E2F2AC1ULL, 
            0x14EC40AC27F0396AULL, 0x9B52334B56BCC18EULL, 0xCB1732E6D8976C9BULL, 0x454D2A33FC74D608ULL, 
            0x7E85C0EA23BE421CULL, 0x50ACA6F104639CF0ULL, 0x618C86DC1E504094ULL, 0xE6D17D0057EC352AULL, 
            0xBF8E4DA9AD62C870ULL, 0xF8392974CD576B0BULL, 0x8C118C440D56ACB0ULL, 0xF88F81C1241EC747ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseBConstants = {
    0x5B35C7E57B4E2EE6ULL,
    0xACD9D05E02A018CDULL,
    0xEC2A8BBB8068D899ULL,
    0x5B35C7E57B4E2EE6ULL,
    0xACD9D05E02A018CDULL,
    0xEC2A8BBB8068D899ULL,
    0xA26ABAFC5B20CECBULL,
    0x8FB0DDDD44EB33DDULL,
    0x2B,
    0x0E,
    0x94,
    0x74,
    0xEE,
    0xFF,
    0x5B,
    0x40
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseCSalts = {
    {
        {
            0xD841FC1B7F1F4DF4ULL, 0x2BAA4D528FC6BDDBULL, 0x0E06605BE1B9B116ULL, 0xAAD72D24FE442574ULL, 
            0x94837AB026F05CDFULL, 0x5E7E3AA8D0061A20ULL, 0x21C551971A078132ULL, 0x6A5E22A6F8CB4DD0ULL, 
            0x89EE3A7DF3768B3BULL, 0xFEBB440312E01624ULL, 0xDDC1C52E3188D6F7ULL, 0x2FF8B0026EC9D084ULL, 
            0x5269C45B0BAB217EULL, 0x3FA39BAEBEB05DD4ULL, 0x2547459833C529CAULL, 0x83B570D255868363ULL, 
            0xE692A859775328A2ULL, 0x1355C292990FBFB4ULL, 0xF89254FFB4CDCED6ULL, 0x6BBFCED7EC778755ULL, 
            0x57866451D1E7A98EULL, 0xE7F952F513DEF819ULL, 0x15C42B8F881B58C3ULL, 0x2DC36B9D6DD77D86ULL, 
            0xD663C1E0C9DE50E0ULL, 0x2724F1F3045DBE17ULL, 0x16EC4FA0D7879144ULL, 0xED28F762C4BE63C1ULL, 
            0xB5DA84247BA285AFULL, 0x62CE488A31E50D19ULL, 0x954767B9E5832743ULL, 0xE58B633CE8453018ULL
        },
        {
            0xBE07CBC7D72DA0C8ULL, 0x6743258AF19C4D6BULL, 0xD0D77679A230C6E8ULL, 0x59BA002B4871DBA1ULL, 
            0x2B97FD98C3B37B39ULL, 0x8EA1AD225AEC9390ULL, 0x7AB0828A978C785EULL, 0x3358CF7C8401F788ULL, 
            0x801B468507D0DEB1ULL, 0xBDFDA5C4EC084EC4ULL, 0x729A68C15C04BBEDULL, 0x408C6264232A11E2ULL, 
            0xD1F1A07CF99E7639ULL, 0x8C59B1B565D1D0C1ULL, 0xCBD28B427ED2CA1EULL, 0x9D428EB49877B59EULL, 
            0xF09C7459A82FE48CULL, 0x74888922AA519EA9ULL, 0x1B8D0E9CAE82FD7EULL, 0x7715E74C2341A6B2ULL, 
            0x077E3DBB1D965E1EULL, 0x186EDBB1FFBC8D0CULL, 0x3AFFFC9C11B0A736ULL, 0x865DE1EBD96EF741ULL, 
            0x4607148D045DCD82ULL, 0x82D973F8FB2C2405ULL, 0x322D02E2E56D48D6ULL, 0x8514B047C8023F26ULL, 
            0xD7935347E5159C16ULL, 0xC3C109255378644FULL, 0xEFD9EF463B7FB041ULL, 0x30E1FC56240F8F48ULL
        },
        {
            0x5D6368BBF755F7B8ULL, 0x7178D426B8AF99D3ULL, 0xC378EC2CB4C854E1ULL, 0xC8B876B22FC79167ULL, 
            0x9807E359D3A6300CULL, 0xED315F407D4C66F1ULL, 0xA16EF2B538C11912ULL, 0xDC12F779C7AF6FC3ULL, 
            0x67B0865052048601ULL, 0xE42DB495C23EB210ULL, 0x5F8C815CD7C86608ULL, 0x16901D88729A560CULL, 
            0x41CFD3B99F86361EULL, 0x26F3145EFA98410FULL, 0x003A5A357F1498CAULL, 0xF06ADAF5A8E66B68ULL, 
            0x9F7FCB046775D118ULL, 0x7A8789F5A5B809B6ULL, 0xAE0459D7588D9F4CULL, 0x6759C2DCDE67F34DULL, 
            0x2A4381FD06C62A81ULL, 0x0C1D712550E6AE77ULL, 0x128E57094815C16BULL, 0x43D14669599C2A8FULL, 
            0x66AC62320D27D71BULL, 0xDF63F919CB8F5134ULL, 0x43EB25E742B31C74ULL, 0x32BC4FF24893AEF9ULL, 
            0x4D3974BD3AD277ADULL, 0xFF874C9B87CA50E4ULL, 0xCF825A2C57F453E6ULL, 0x75E09C572C45101EULL
        },
        {
            0x28A5EB1364DE0FAFULL, 0x0172C99ED4B48F57ULL, 0x7CABC4EB1AB7A7BFULL, 0x887372DDF9F8F848ULL, 
            0x5F69055C5320B116ULL, 0xF69092A53439B946ULL, 0x71CC9B5D9696A07CULL, 0xF6ADE39BBC63179FULL, 
            0xB97AD839F57A57F3ULL, 0x0F0B44C2FCE4B532ULL, 0x1C7571A712CBDEB9ULL, 0x286308E37534B397ULL, 
            0xF612CE66511DEAD9ULL, 0xA13B93E5F986078DULL, 0x432B833E9049B8B8ULL, 0x33922751620F3FC2ULL, 
            0xC3FB8B26D00B022FULL, 0x86BFEA43C77E439BULL, 0x38AA73989CE7EA76ULL, 0xF0A8EA653EF807FCULL, 
            0x22B60DF7733B2FABULL, 0x90DF98CEB52D6193ULL, 0x21B5849A12BC7BDEULL, 0xE4DD15521BCB3FC3ULL, 
            0xA47CC25119233A5FULL, 0x9E49EA678228415FULL, 0x2A6FC9C2CE991E5FULL, 0x0B10C93F30D1EA2DULL, 
            0xE338C42F96A2C035ULL, 0x0A395ACFD5E8FC89ULL, 0x0225C239ED2342C0ULL, 0x5525AF59333B7EE7ULL
        },
        {
            0x978DA65B36EDDE41ULL, 0x763A8F88E1556180ULL, 0xEC8CB50618EB2259ULL, 0x08F997EFF3A98DC8ULL, 
            0xBE4F0CC44E491472ULL, 0xC738019539EC73F2ULL, 0x29C31DE3A9E52C0EULL, 0x99D07FEBC44A6609ULL, 
            0x45FF60AC2A6EB65AULL, 0x35EBD12738D16034ULL, 0x652E1A5386762D52ULL, 0xBF9D0A988870167BULL, 
            0x4FBECC0109C8567FULL, 0xE16A5C8E9C2DDAC3ULL, 0xBF7452468EC83AF1ULL, 0x693C7560F59487D2ULL, 
            0x1590B4B676FB3453ULL, 0x0EA66AE7E08D5355ULL, 0x1AFCA27E789317BBULL, 0xC38652CE66590E22ULL, 
            0x10A7B78555119989ULL, 0x72275B73B9D7C2EDULL, 0x508CEBD7CCEAA6B3ULL, 0xD4B94C025CE84A81ULL, 
            0x255BBC42B6BDDD08ULL, 0xFB629E9F0ECF0204ULL, 0xE287F1A97A8B5007ULL, 0xE3A63A8E1D915005ULL, 
            0xAF19F0F5EC2D9EDCULL, 0x0047B4E595F15DFDULL, 0x822EAC7034AC4FEDULL, 0x32E47D7114733B6DULL
        },
        {
            0x02F1514D6FE31C71ULL, 0xB7BD599F9C2787C4ULL, 0x756622197D8C97D7ULL, 0xAE8A47B85A34ED50ULL, 
            0x961ED0DCFE55D2D3ULL, 0xC9E7678A64DB2FF1ULL, 0xD14A1C0A6DEF8348ULL, 0xF0888F447BAFDAE1ULL, 
            0x735AAAA95CF44795ULL, 0x7045D5290C0C3A75ULL, 0x37025066490D105BULL, 0xAE7B81DD24F498E2ULL, 
            0xB0A3ABB8B95BEA13ULL, 0xCB887CC58F1A5343ULL, 0xB03E4FC42B4F4EC1ULL, 0x8732900D42BDC93CULL, 
            0xAE7A84F2541B8065ULL, 0xDE3E765E1117BE12ULL, 0x088C32753CC079FFULL, 0xABB0889A8AC4B8F8ULL, 
            0xB445BB21901B2FE2ULL, 0xB7D225CBC3DEF286ULL, 0x7AD22120E7A0AFA3ULL, 0xDE022AC10D4496FAULL, 
            0x1E66D04C7F3EC73BULL, 0x9C8A6109041646C9ULL, 0x13CEFD854EB7F28DULL, 0x1BA897AFBBECE0DEULL, 
            0x71BA4E1FF58FBF0CULL, 0x92DD760E8C0DE7D9ULL, 0x4999250799D3BFA6ULL, 0x237B1D2BE3358CA4ULL
        }
    },
    {
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
            0x1D669DC77EA9F9F1ULL, 0x7E5AA9FF0E45D310ULL, 0x79C6BA75AE6699ADULL, 0x7179746EE2ABC387ULL, 
            0x83CF2065D2EFA19EULL, 0x77FD9382060FEB98ULL, 0x7724029598FE494FULL, 0xDBD7A8C4DDF4A729ULL, 
            0xA53E7A5014FE2A16ULL, 0x2AB7CB49AB5BD454ULL, 0xE1C3B0BC8E28A46EULL, 0xCBC05D909C5213D1ULL, 
            0xA711134798676A3FULL, 0xBB4BCE7A0A9F83B8ULL, 0x1C869EF02961FAD3ULL, 0xFC176601C4F69005ULL, 
            0x1FAB3A1524614B5BULL, 0x8D25D1E5EFBDF02FULL, 0xC9027FAFBE66E848ULL, 0xC23A8342E0C21A28ULL, 
            0x0E6B44DA9C5A23DCULL, 0x26961F4BB389336AULL, 0x855BAE8C66B30120ULL, 0x9D9CF23F07D15F91ULL, 
            0x37844A11D30EB127ULL, 0x1AFAAA65CA6B3D02ULL, 0x6AB1E7C2D7DBA207ULL, 0xEB3396DFB4322C03ULL, 
            0x4C510B238BF4F041ULL, 0xB9AE91734A8DABA2ULL, 0xDCE920983DCF95C2ULL, 0xE312486849EFF2B2ULL
        },
        {
            0x847CD35B7D25DF7EULL, 0x94D5E21B08D9D0D7ULL, 0xA49D388163A2E795ULL, 0xF43F1C82ADE7ECB9ULL, 
            0x62331EF6E06CAB6FULL, 0x5C012A692AE572EEULL, 0xBDF6F62FCC0D47F8ULL, 0x7202E2B6C9B595D6ULL, 
            0xEB27A87116704F07ULL, 0xAB1EFEBAD9DFB309ULL, 0x0A6F33BA5451E49EULL, 0xC8A8702C6A8C94BFULL, 
            0xD0574EE5601E7B37ULL, 0x637465F9E933CE76ULL, 0x660EB62AF816AEC8ULL, 0x1F3290A828407AE9ULL, 
            0xF626F9E9870C967BULL, 0x1786005F964ECB23ULL, 0x3EF8D912B194CE71ULL, 0x8F9B706627A675D2ULL, 
            0x1A6B12381ECD6C4EULL, 0x1E01B88E83C476B4ULL, 0x60967EB385A800C3ULL, 0x9E880777D5D039CAULL, 
            0xCDEDC536BCD70F8DULL, 0x5372ED9D9352EB10ULL, 0x9A801B3429DD8366ULL, 0x3F47F32177D4522CULL, 
            0x4AD6E43991BC79C3ULL, 0x84A0D55EC5B0760CULL, 0x11782C128EC78D18ULL, 0x4FAF1B361CEE5932ULL
        },
        {
            0x754B61F536DA46BAULL, 0xA09D15DF0E0501EAULL, 0x262846CD784BF1D3ULL, 0x3BD18448FBF5A114ULL, 
            0x3AFC8168B73C9D3BULL, 0xFB00EA1416EC359DULL, 0xCF4FCA27A0ECED5BULL, 0xD58F593E0CFE4607ULL, 
            0x624E782AD0DFDB5EULL, 0xFA89725FA0B7D3ACULL, 0x3334C741A6DE2C26ULL, 0x1500F8C35AD755E5ULL, 
            0x58D5277F6BEEBBE8ULL, 0xDD969B8E362071FCULL, 0xB4827BB295F2928AULL, 0xF763CF27C5296063ULL, 
            0x62180C6E50D6272FULL, 0xDAF7EFF8815E27C1ULL, 0x332758058536B149ULL, 0x448AB8665CAE4974ULL, 
            0x766FA5DF1A39A79BULL, 0x83B0F37F9E59CC5AULL, 0xFAFC55809818AEC5ULL, 0x52AD9FB6E2F41DD3ULL, 
            0xEB3A0C809B4DF8BDULL, 0x9E2977C22006A623ULL, 0x0A4CAF3D69994301ULL, 0x18F2FFD8F1BB2A0FULL, 
            0x6253646DFF628220ULL, 0xB5738FD5CC91837BULL, 0x1B77E22947E2FFABULL, 0xEBC38771C5D13340ULL
        },
        {
            0x45D0221FAF2FAE7EULL, 0x7C45BDC65CC96698ULL, 0xBA9D7F1693603EBBULL, 0x77B63172876E58FDULL, 
            0xBF2819C4DAAD6475ULL, 0x14DB73C1A43CE753ULL, 0x35A1D74BB61DF22EULL, 0xD6C4D24644AABB3EULL, 
            0x573469F46B143456ULL, 0x01330A1C716553CEULL, 0xC6CF7E7631DF0D4CULL, 0x25E54233F8620A38ULL, 
            0xC7BB675152BF9595ULL, 0x22AE8327FE54D4A1ULL, 0x1C2E2D3523904764ULL, 0xB753FEC53624CDE8ULL, 
            0x090C3C364EA2A9A2ULL, 0x761C3437FCCD8969ULL, 0x5262C6FAB2E25BE4ULL, 0x94CF67E72BAE7C57ULL, 
            0x6C7A7B9C3AF24848ULL, 0xAA90C2174B2E6293ULL, 0xE23BBB51E175ADFAULL, 0x590B6E2C82025A58ULL, 
            0x8AAAB97E1E1EA00CULL, 0x9A13D49769792CFEULL, 0x77053B9AA91E682EULL, 0xDEA1D2284DB01959ULL, 
            0xE6A439EDF6410A6DULL, 0x7005582C79033E6CULL, 0xA9D1C38A2AB5A7ABULL, 0x3556D792E5E1F7BCULL
        },
        {
            0x6D45DF6FAF1B7532ULL, 0x4A0D0280489AAECBULL, 0x10712BCD0AB49B65ULL, 0xC3123031FFE04A07ULL, 
            0x8D50B66A6E1134B0ULL, 0x89F37F09C88F2534ULL, 0x03F7DAD6E6F9125BULL, 0x3A78F5ABC2EE6A27ULL, 
            0x02D7945210B892D0ULL, 0x6F0D141CFCC4BDBAULL, 0xBFA62FAE1E837ED2ULL, 0x155FA2270157CE85ULL, 
            0x24E90FF0B873125DULL, 0xDC57E1A7E0D69422ULL, 0x95B87622A8FC0782ULL, 0x35925AEE4E53B99BULL, 
            0x7B7AA5C88D704731ULL, 0x9868611E3F5A2903ULL, 0xD19F6E468AF026E3ULL, 0x63F76E913A06EFB5ULL, 
            0x7FFC30FF849F6DC4ULL, 0x0B96EA3148F4C1ACULL, 0x96C3F30CB9C014E9ULL, 0xE8F8909D93336912ULL, 
            0x93A6A56FB6822236ULL, 0xB19E35109059F9A5ULL, 0xA13749B202BB0B08ULL, 0x7CA7C571F4D55C84ULL, 
            0x78AD83B039D6B686ULL, 0x8116EF06B8BE813EULL, 0x01B9835699D5C6D1ULL, 0x3191A2D4B89C6259ULL
        }
    },
    {
        {
            0x44AB17B5086ABF82ULL, 0x298BB0E199C73D25ULL, 0x98EB364267CD06E1ULL, 0xB2E6CE47E8B37160ULL, 
            0x6E8527C36A4FA63DULL, 0xA1FFB830DE632D94ULL, 0x4079A54BCB5D095DULL, 0x8E24D64AA5407525ULL, 
            0x6D4EAA64FA9067DAULL, 0xDBFDD82CB941B920ULL, 0xD44AFBA4ECC5431DULL, 0x17C05C691A6BE301ULL, 
            0x3E80376479F445EBULL, 0xDA9BBC32D140ACD4ULL, 0xED06E0D752EAC61EULL, 0xBB5450EF7A082516ULL, 
            0x77AEE4A9AB923B46ULL, 0x6279C4492523ABDBULL, 0xAD5556C781058188ULL, 0x75608BB9AC194452ULL, 
            0x1085CB531515B458ULL, 0xE9D6E1224B0D8E84ULL, 0x067EF5227A86A3D3ULL, 0x57FA87D799E54F5CULL, 
            0x98C241EAE1D40D82ULL, 0x22A27654135B825CULL, 0xA3051F1D209AEE7CULL, 0xC831C9C7BEF426B4ULL, 
            0x88E5C1F17C676047ULL, 0xD9E2F935BBAA053FULL, 0xFBDF75A4BDF44E5FULL, 0xDC2A387E22842A69ULL
        },
        {
            0xFE64357D4AB53823ULL, 0xCB2E98CCDF4CDF91ULL, 0x02B294FE8FECBABDULL, 0x95BAE0792EF57E44ULL, 
            0xD5A63EA72BBE5683ULL, 0x3E9BA6EB319FCA66ULL, 0x323EF69030504CD1ULL, 0xFC4A05AAAE2EFEE3ULL, 
            0x885EA3E3A938BF75ULL, 0x8EA34485FB140042ULL, 0xC8B3D5C9F16100F9ULL, 0xDC203FAD8D89E692ULL, 
            0xA75CDCAF2DBC03BBULL, 0x4E4757479E6C0BA4ULL, 0x5D43BFEDDF2217C6ULL, 0x1FC56C34CE6AF26AULL, 
            0x18B5DCE50CE5E46AULL, 0x5FBA300C3F4325A2ULL, 0x8019A72F0D3DBBDCULL, 0x55F61D7B39D9D584ULL, 
            0x25470F4B7899C7DFULL, 0xE533123E93326292ULL, 0x270210792473A194ULL, 0x61C15609FC75A0A1ULL, 
            0x70C607F984ABD500ULL, 0xA3B97C64F6916074ULL, 0x61121E07BF7B5174ULL, 0xD0F8A05F849C1175ULL, 
            0x1BFBFB0CDB3FCB69ULL, 0x21C974F4F2C5759CULL, 0xD17EDF5163D36E66ULL, 0xF847B2F650C6B08EULL
        },
        {
            0x390FA184C04BCC49ULL, 0xB884548428F5A70CULL, 0x930826888AC45A3FULL, 0x98FA9C489C77D722ULL, 
            0xCE15829746E9DFC1ULL, 0xB3406618E924BE93ULL, 0xB69C4021042CABD9ULL, 0xC110DC649A888848ULL, 
            0x2C389015029F9995ULL, 0xBF48CF99D4F6F25AULL, 0x3B1ED9F8B1F55772ULL, 0xE850C968754D3E9FULL, 
            0x1B06366A51629535ULL, 0x6B80D31C704B75A7ULL, 0x9A286557C9EF8C1DULL, 0x562ACD3F5E6F6CD9ULL, 
            0xB570660F3017A57FULL, 0x13CAAD5CF1FFEA7EULL, 0x7374A88500A51F31ULL, 0xB2EBD6157EC66C42ULL, 
            0x07EC741410CAB355ULL, 0x9DEADCC7CDE5E4A7ULL, 0x4E88D11F7C929B2EULL, 0x53AAAEFF23729461ULL, 
            0xACF2EA734A731153ULL, 0xD34E8BA61F3F72E5ULL, 0xFB39647442F22C83ULL, 0x0CE2B720C46059C9ULL, 
            0xFD788D13BCC686E5ULL, 0xF1178DBCA5584F15ULL, 0x911956C03EF88DFAULL, 0xE7972B2F9C15AD05ULL
        },
        {
            0xB737673E01FB55FBULL, 0x9A540B0D40A7C2F6ULL, 0x40BC451C5445EDF2ULL, 0x26A1287140B6CAA9ULL, 
            0x2E40F8A810C3D959ULL, 0x5B618189C2AD6155ULL, 0x454F4B9843FC444BULL, 0xAF558F9DFB3EB12BULL, 
            0x02CAFB113EF7D6D3ULL, 0xAF10C2B6658C0DE0ULL, 0xF08A05BA84EE9722ULL, 0x47A54CE4A2DFDC42ULL, 
            0x710227428D6B9145ULL, 0xCC4166D471C4FBE0ULL, 0xD3F0D94ACA45879CULL, 0xDE73FF0D55BA638CULL, 
            0x21A4C8733393E922ULL, 0x067F5A82FBAD0084ULL, 0x7FCC84F2B1BA4018ULL, 0x75EC2D8E5B38C020ULL, 
            0xBC9CB1CD5B084818ULL, 0xBE9FDB88AC14F7E0ULL, 0xA55AB783A8C70A81ULL, 0xA7C731984FBF49F6ULL, 
            0x66DD6F08706B8408ULL, 0x906F566AF6B7294AULL, 0x9C8ECD4C472C23E7ULL, 0xFA2185F64BBAF64EULL, 
            0x246B71926D86A15BULL, 0xA08DE49DC6A83DAFULL, 0xC4EE9EDCD8319DABULL, 0x9D928B8DEA8F67B6ULL
        },
        {
            0x15FC0843E52E3793ULL, 0x1C054CB9FFFBD8D2ULL, 0x7C4699D3BC04E9E7ULL, 0xFAB185F65F99B0F9ULL, 
            0xB8D9E8DAB34C8A12ULL, 0x9742261157BF7E59ULL, 0xF40393052C206BDDULL, 0x281859B52C64FADBULL, 
            0x8D41135AB2A6F917ULL, 0x95F1623A589FEF8AULL, 0xA3E1A34DCC62C550ULL, 0x6AE364104A7A4788ULL, 
            0xBD877A784C9841A1ULL, 0x25A8B0414566EBAFULL, 0xB73B29F40F85BD3AULL, 0x0E3298FBB4467430ULL, 
            0x6877DB086CC3AE5FULL, 0x0423BC96B0893826ULL, 0xAB7FBE0ABAA2A46EULL, 0xE4AC4E358DC03095ULL, 
            0x843445EB0309C431ULL, 0xD8340ADF56F9C5E9ULL, 0x50CA904C8E360AE3ULL, 0xAE040F7DFE8384C1ULL, 
            0x03E9DAB47F1C16E9ULL, 0xF37186492B4710ADULL, 0x97114674F0302871ULL, 0xBE8F9DF22530CCDDULL, 
            0x569E0C3EB67206E6ULL, 0x8EF0604CEA0D8B80ULL, 0x18DBF139D0607E3FULL, 0x92B3949A3AD51FDAULL
        },
        {
            0x6BAF61F469249620ULL, 0x5139E7B57EDA3A38ULL, 0x0D61E729CF9C9F60ULL, 0x2ADF84FEE92185D3ULL, 
            0x7AADA7A47247182DULL, 0xEF0696A0C3E65568ULL, 0x6AF2D61D110DA525ULL, 0x0670ED045551255AULL, 
            0x0EF0BE30DF0DED8EULL, 0xD6B8D526A74C9918ULL, 0xD52597E6586808D1ULL, 0x157BF269079B6438ULL, 
            0x5374EF6B37A6EFEBULL, 0x719E1C9EA83FEEF4ULL, 0x5F9B512C94D092C0ULL, 0xD1323173D08C45C4ULL, 
            0x868E670329BF3F22ULL, 0xE78AD7E8B4205802ULL, 0xF6063AA9C13691B8ULL, 0xF94834DCB6866F2BULL, 
            0x9CF20EBEA6F08D12ULL, 0xF87D2DC97FB9ABEBULL, 0x3F1F3E5FD2BAD922ULL, 0x9E43355F659A7721ULL, 
            0x8D35C611749AB2B7ULL, 0x02529C80F27FC1C1ULL, 0x165E7DF3A9DCD6D0ULL, 0xF2B54F5013E606E2ULL, 
            0x9F24240FCB34DF13ULL, 0xCFF4B2FFD8C526D0ULL, 0x5E0139C6CC6F755CULL, 0x91D0F2AFC839F1EBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseCConstants = {
    0x2F8B420BD6A5CC15ULL,
    0x5718DC334BF880DCULL,
    0xB282C52C32508865ULL,
    0x2F8B420BD6A5CC15ULL,
    0x5718DC334BF880DCULL,
    0xB282C52C32508865ULL,
    0xD6C9DA746A1EBF41ULL,
    0x08A56442513CFBC0ULL,
    0x8B,
    0xA0,
    0x9B,
    0x26,
    0x4A,
    0x61,
    0x4E,
    0x54
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseDSalts = {
    {
        {
            0x9ED4FEE1DB93F443ULL, 0xE6B5F901AC80EF81ULL, 0x98F8CC3490BB5836ULL, 0x47C92E5027F9C4C1ULL, 
            0x8D5A6833A499ACF7ULL, 0xA5FB4AFF30CE6341ULL, 0x856D51A14F46CB2FULL, 0x6A16CE7171ABDAA3ULL, 
            0xA5CD6FA7AD6FC4BAULL, 0x3CFCE4A4D527EE4CULL, 0xD0A7A67D5F9BB0C7ULL, 0x591B26C897694036ULL, 
            0x4881A7FB63263FCDULL, 0xED39375845B57DD9ULL, 0xFDDC3B008394C9CFULL, 0xA21B80E325C0B39FULL, 
            0xAB4B9630F336615FULL, 0x93BF358E717726EBULL, 0x221EBD5CD0CC7736ULL, 0xB416174A6E879EFDULL, 
            0xCEE28D311E2846C3ULL, 0x12E350A8A6E2FFA2ULL, 0x5F4ED8FC86C22557ULL, 0x7BA82DC5B0768D09ULL, 
            0x3255D6087C1FEACEULL, 0x8AE00BD9EB8DA0EEULL, 0x31FEEECF544D25F5ULL, 0x0811249B24DABB9BULL, 
            0x6E7F98490D3EA575ULL, 0xB02740A0AA3F3DB8ULL, 0x215B753FD91D85DBULL, 0x98D64FB65641A3C5ULL
        },
        {
            0x9D6C315439627599ULL, 0xF8F9AD77C2606B5BULL, 0x6E2D2530F17E71DDULL, 0x30D9BA172A16DD74ULL, 
            0x2804FD7510AE42E2ULL, 0xA64B73491657D113ULL, 0x6A9BDE96659F6DC7ULL, 0x3D4F5F037D8C5439ULL, 
            0x222EA0BCC9C79078ULL, 0xCEA440088DF10EAEULL, 0x54A4C045F44F6C12ULL, 0xD3361BD757425F9CULL, 
            0x1DACDAEDEBAD0DC6ULL, 0xF101610726DDBD32ULL, 0xDC49BF95C36826C2ULL, 0xE4885B15BCB08B46ULL, 
            0x4D8FB74764E68212ULL, 0x44543689A0939B67ULL, 0xAB4BD9E1258E7FF7ULL, 0x95FD96E10D7E70EFULL, 
            0xF6C66908C5CAC43AULL, 0x5972397A5E464CF5ULL, 0x0605C4BF8B66E7A2ULL, 0x401DC6CFFAF81ACFULL, 
            0x929C371EF1347CDAULL, 0x871CC3DBBF420B31ULL, 0xD469E7849D345F75ULL, 0x4C8C412590943DAFULL, 
            0xF4FC9C6D5179E617ULL, 0x933874F1792DF9C0ULL, 0xE90583D8B9A14D46ULL, 0x4887724E0FE6CB78ULL
        },
        {
            0x4279313B5DC7C2BEULL, 0xFA28DA03CB64B45AULL, 0xCAF63F2EF611C37EULL, 0xAA25CA23B904EDEEULL, 
            0x55E7005FBA1ED5A9ULL, 0x87B798C0BAE3BA0EULL, 0xAFEFFC564DA52639ULL, 0x8857956C38B1F26DULL, 
            0x70A82D064D3E1F28ULL, 0xA1DAD0E0C1548A4BULL, 0x5E1ED2D667377A1CULL, 0xB088FB45BC08E325ULL, 
            0xFB67B80D49B491BEULL, 0xA3AD42FE5CFF730DULL, 0x932B4DCE09F90033ULL, 0x0DA99C4F85BC4F49ULL, 
            0x4149F43A4DBACED0ULL, 0x3E1605124A15A0E2ULL, 0x014EF8F040F4F9ACULL, 0x47C14ED99998480FULL, 
            0x6A0A26AB14967648ULL, 0x2F69A1C69105FFBFULL, 0x88616F19F6C990E1ULL, 0x292EBF5DA8A35063ULL, 
            0x533564843FDB768BULL, 0xFAD0F83FC8D5EAC6ULL, 0xB507CC5601075D9DULL, 0xDB80DF74EDD74B1BULL, 
            0x1033D126B91273CCULL, 0xC9B08B7FE050F335ULL, 0x64945FF4B1A32A0AULL, 0xF30719B6E5CFC98EULL
        },
        {
            0x5F5CBC9CE381AD18ULL, 0x8B49048F9EDBA79FULL, 0x53E408C613BDDCC1ULL, 0x6763D73780D4EAA5ULL, 
            0x5A8DC50DEC8B9353ULL, 0x634F55462A8C95A5ULL, 0x76683EB7D86B5202ULL, 0x9EEE9E461101B790ULL, 
            0x5242E03582C02E01ULL, 0x7D9C67EA25D40F96ULL, 0x6D5E6FCF1D9713CDULL, 0x026DCE6F1B39763BULL, 
            0xCB6CA2ECD4FD05B0ULL, 0xCBB6C004E7324A3CULL, 0x92AE71BC57C21EF7ULL, 0x2660D38B4BBE9097ULL, 
            0xA53BF2969A57369FULL, 0x65A8EDCEA7BA6BF3ULL, 0x8689E2276AFE2237ULL, 0x61738D00BCA3E252ULL, 
            0xA2EEC4A53EBF4602ULL, 0x27049E16A5D570ABULL, 0x51C38B918C4F5605ULL, 0xABF71FD66A89548CULL, 
            0x77C838A2932B67C1ULL, 0x4CB06CF5B8F2CB85ULL, 0x516CD9D5550AA3C3ULL, 0x25239A2D1D0CE713ULL, 
            0xBE695C2D56302BCFULL, 0xA60671E4C045763EULL, 0x6D20C2E1E0944894ULL, 0xE2046A51CBBB07DFULL
        },
        {
            0x09C5AEAB0C69C23DULL, 0xE499F3F12406EC8FULL, 0x162CB291E176580BULL, 0x87EAB1E6BC920BAAULL, 
            0x92EDD58E760B7795ULL, 0x7659573EB85DFF2CULL, 0x821F72A7CA8EA677ULL, 0x03DE6FE8D8C93FE1ULL, 
            0xD0AF595C926CBDD0ULL, 0x4F8EDB742F1152F5ULL, 0x4A3709AFB3C157CCULL, 0x45EA82969787AB9FULL, 
            0xE149B978A27D70F6ULL, 0x22590B2F0180E0B8ULL, 0x7AE72BB1BD665733ULL, 0xA4AFB0B1DEC23797ULL, 
            0x26E48518D04B86D0ULL, 0x4B8D8134543495E7ULL, 0x9EC3FEF2403F9649ULL, 0xD924C4FFA4EFB11AULL, 
            0x46D99BD6092EFEF7ULL, 0x12C7B9B41EF351FFULL, 0x36754DE2789A8D42ULL, 0xB1B88893872773F0ULL, 
            0x4750099C47CF94E0ULL, 0x0C60FFBB4A25E295ULL, 0x9D9A1AB7AEF22E89ULL, 0x47DA2F04D240D831ULL, 
            0xBBB442A4CD6A0AE4ULL, 0xC2B8532F89397779ULL, 0xCA19ED836B10DF8EULL, 0x344751BC2E12090FULL
        },
        {
            0x8BC3A040A719954FULL, 0x3B3B071059645257ULL, 0xB8B96F603BA02C7CULL, 0xBA74CB90310A9912ULL, 
            0xDC232136A0F78448ULL, 0x533000DD97ED62D8ULL, 0x4A74AF1C3B6733A6ULL, 0x7D2F8EEBB85CF92FULL, 
            0x89E3D1235E279D6AULL, 0xA750CC86F7984B09ULL, 0xD3798D727CC97F82ULL, 0x21CBB9286C2AD58DULL, 
            0x54EB55F03F127F17ULL, 0xC5836CBC3AAE8AACULL, 0x2EEAA777117F66DFULL, 0x2A968CDD15796BABULL, 
            0x914F349A69048AABULL, 0xF21AD81AF60E3024ULL, 0x93464F895EBFB9C9ULL, 0x0A3054C3958BC001ULL, 
            0xA59FDE90702FC675ULL, 0x5A66037878E2CAE0ULL, 0x6531A107AD7A76F5ULL, 0x8EBFACDCCE481257ULL, 
            0x6C7C4B4ED268279FULL, 0x978FC9DFCB812946ULL, 0x422B173950F7EE31ULL, 0xCFB4400B6C106E49ULL, 
            0x9CA014298F885B46ULL, 0xC5C4A0BED8CFBCB1ULL, 0xAF048F9332A6BE3DULL, 0x067EA323F2FE0475ULL
        }
    },
    {
        {
            0x80953F2EAB16C2E6ULL, 0xB8C866B49EC2EF84ULL, 0x33EDB68A82BBEA1FULL, 0x1061CABDD9513DC6ULL, 
            0xC7B339C639A94562ULL, 0x59691F894D27013EULL, 0xFE210E61D279A218ULL, 0x561F89A44B40DC94ULL, 
            0x9856DE1CC1F68DBFULL, 0x4B7213C81DA7BA70ULL, 0x4F7AE5653211F8BEULL, 0xD028ECF121703BEEULL, 
            0x277025F5EC580063ULL, 0xAF12B44B67FE4929ULL, 0x387474799BDF27ABULL, 0x742FC8DEA6B90901ULL, 
            0x135A8409FEB7A0DFULL, 0xB79B64F4FB6C0B9FULL, 0x4CA2AE70A60168B6ULL, 0xB6ECB528F92B4348ULL, 
            0x91DB2AF5B6ED59A0ULL, 0xD9EE8EB38C67FC5BULL, 0x3349BEE843700C1CULL, 0xA1AF3D3A4738A44DULL, 
            0x76013A42C603E5F7ULL, 0x7051F2B17CE15268ULL, 0x2B8724DEBA4D256EULL, 0x852E22E1DA4E401CULL, 
            0x52A7605A4F86FF93ULL, 0x85A7AE4D74A5FEBCULL, 0xC4783858DDE6BE88ULL, 0x8CA45085A38ED383ULL
        },
        {
            0xC6C77CB00AAA2099ULL, 0xA188B34196F8FC6CULL, 0xDA53B3C53EC4F872ULL, 0x9538F2E25D8AC91FULL, 
            0x69001EE913DA8EC4ULL, 0x7DA7389514999D23ULL, 0x8BC9CBCACB677492ULL, 0xB5531D5C37DB6E27ULL, 
            0x8E73896023291FEDULL, 0xEF9CF8DA756EFA7BULL, 0xB7648A5C5BA5F1F4ULL, 0x62BBB0779A0BA81BULL, 
            0x481E0094380690B6ULL, 0xE6C4AEBB34CCDD47ULL, 0x803AEBE529EDE4AEULL, 0x0CDF931623808F42ULL, 
            0xF9D2912038159194ULL, 0xE6F434ADF0BD6FE6ULL, 0xF3074221FEAE3FF8ULL, 0xA108E4D8291083FDULL, 
            0x5121B9F3B7030689ULL, 0x5EA89E610E3873C6ULL, 0xFB6104BF4FF45EC6ULL, 0xEEAC47AD77325BB6ULL, 
            0xD6F855D8153E98BAULL, 0xEDA957302F3A2330ULL, 0x08A6C94210B7CF9CULL, 0x19D7E86C350F08D5ULL, 
            0x3D8E7201D0854328ULL, 0x778C532AEB727F14ULL, 0xE752134FDD6F38EDULL, 0x70522D125F828AB1ULL
        },
        {
            0xCC140DD4F2860A03ULL, 0x319C1EE0820CC092ULL, 0x227219E139A50EB9ULL, 0x7A926F3627F4FBB4ULL, 
            0x4DF35E3E217E348AULL, 0x725D769D21B7C65EULL, 0x87549A5064287E9BULL, 0x6224A82A2ADEDF8BULL, 
            0x6A7DBEEA92D28BCAULL, 0x67CDEFB1A28CF6CFULL, 0x090EAA0B7655DA7CULL, 0xAD4ABB1BE4FA26DFULL, 
            0x42AE6BA5F8422F4AULL, 0xD61673B7A7161402ULL, 0x8B5F546F024904B5ULL, 0x22EDFDBB7495714AULL, 
            0xC912F42FDC610CEFULL, 0x007413ED789D85DFULL, 0x1AB17744235237EEULL, 0x3F91D3F2E0F7FD5BULL, 
            0x15CD2D7A32993031ULL, 0x30288F5243CCBEBBULL, 0x64BE499E2021269AULL, 0x9A16D1793E13F9B9ULL, 
            0xEF9C6A18A609584FULL, 0x47FFF347435FF4EAULL, 0xE78C7CCBBD51B320ULL, 0x04842D83105BB739ULL, 
            0x2A63D94B3CDEC686ULL, 0xBB561044CBA328B5ULL, 0xE2D8F6C9F2727FE6ULL, 0x4497645E81C0B7BBULL
        },
        {
            0x890891D639A72A2BULL, 0x73DD6BBDD4EB2B8EULL, 0x7D356F6CB0C3F19FULL, 0x8B2EC391C0D8E51DULL, 
            0x07E7D8E1A4FC1F8DULL, 0xFE4EC759EE218201ULL, 0xEFFF067737D60F28ULL, 0x7B57CCAC02602F3AULL, 
            0xE5F4A4F86371AB94ULL, 0x005DE6F026B23EFBULL, 0x9D39AFC8D7A67195ULL, 0xC7D16F3999E97B17ULL, 
            0xA06364180C7772BBULL, 0x511C98D6557F0EBDULL, 0xE72FABFE6AA1EB7DULL, 0xBD592664C59E738FULL, 
            0xAC40B7B4CE5AEE16ULL, 0xC46F88950C457D98ULL, 0x58ED16C33F0E4AE5ULL, 0x9F6D93A98DE9275EULL, 
            0x439352CAF28F8115ULL, 0xD82D4D2DA1EDA45EULL, 0xE9C482E1E6767005ULL, 0xC0FEFC7C9DDE20BAULL, 
            0x68780B99F133230BULL, 0xFBD04301DA441D74ULL, 0xE314B93090FE22EBULL, 0x1630F7754028DB08ULL, 
            0xD3E341FC1C8E2762ULL, 0x52E25FAA9275AD27ULL, 0xAD67D4AF8C77ED3CULL, 0x1A03AEE868DE4799ULL
        },
        {
            0x90497D3DC08723D8ULL, 0xB6D296D5A388D205ULL, 0x8EE6039CF23E2ACFULL, 0xF037BA2BB8A12B65ULL, 
            0xA94E48E011231C3CULL, 0x99A97325428D3947ULL, 0x9A585D0451AFACBEULL, 0x1FE7872CCB19DC08ULL, 
            0x3EC4FB09780DE6F0ULL, 0xE3FDC1DF72883A36ULL, 0x2D4ACD1A5B75D118ULL, 0xF8EAF8F30954CA28ULL, 
            0x70685E20E4424D6BULL, 0x00474A9D575D6E53ULL, 0xAB6BF4BB4E162273ULL, 0xF998247B2CF94B08ULL, 
            0xD3B351A844E32219ULL, 0xD2A030897FCFBE73ULL, 0x879359B150374D1BULL, 0x88945E62E2E6A78EULL, 
            0x6E4EFEFF93E7611CULL, 0xE1872AB9EB3A5018ULL, 0x84F68D5DDD67629FULL, 0x9C1D838C7ECF0A05ULL, 
            0x06EE6ED2E6C470D8ULL, 0xD053C1C2F93824C2ULL, 0xD0676589A180E642ULL, 0xF20699C8779ABD2CULL, 
            0x092472BF97CEF180ULL, 0x18FCC8442C60AF96ULL, 0xB1E94A677F0DBAE8ULL, 0x8B17D8AB4E1EDD0EULL
        },
        {
            0xE6222866620DBD23ULL, 0xBF58558BC1AD406BULL, 0xAB27B0F994984C06ULL, 0x3A5BFC0C76F7480EULL, 
            0xE8CC4136B8FC025BULL, 0x3526FB739DB5CDC0ULL, 0xB729F30F988AB03BULL, 0xEDB32686EB1AFFFAULL, 
            0x1257C34B8E46B144ULL, 0x32D39D8883D91829ULL, 0xF86589A5979552AFULL, 0xCE808CF5CBE43ED7ULL, 
            0xF9812DA8C423FA3FULL, 0xEB16A1591A24B7DBULL, 0x0CB1F91B0AB1E698ULL, 0xFFA5C91E49D92317ULL, 
            0x6B09521C1D324D26ULL, 0xA2ABE3458C5C100EULL, 0xC485FBC8AE6E0A1EULL, 0x1F08812EC6CE5324ULL, 
            0x8EAB8023ADC35B60ULL, 0x60FF64DB7203E83EULL, 0x2B43B94859AC8455ULL, 0x9E48839B4717521FULL, 
            0x6B7AA59A901049C4ULL, 0x0017A8E4CC9988F7ULL, 0x1A9AD421CF36BC46ULL, 0xE7C3F690B9D4381FULL, 
            0xD7ED24D7E3971071ULL, 0xF8024ABF594BECFCULL, 0x02C959C428EAACC6ULL, 0x0621F3FB7D47127CULL
        }
    },
    {
        {
            0x6DEF7F175F483E26ULL, 0x3273D28CABF23213ULL, 0x02B693EE645A39A0ULL, 0xB0A81F8912F8F09FULL, 
            0x518D3C9591D4049BULL, 0x101A25A2DED6D3A2ULL, 0x9E8A1C507289F7DBULL, 0x10897AFEF5CF0A83ULL, 
            0x1A8E79A43A2375C1ULL, 0xDBAC531E4E886CF3ULL, 0xB45E0675B9FFE01BULL, 0x88D9EAE6ABFF46B2ULL, 
            0xA01B22E9D224C74AULL, 0x953D27A02D6502A5ULL, 0xCD70999A0215ED8CULL, 0x49E75411D1CA4744ULL, 
            0x50568EEA0825DE13ULL, 0x54706523C5F102CBULL, 0x4B331A4DE7BCF54BULL, 0xC69DDDF8CA2F15A0ULL, 
            0xAE0E04EC63BE78BCULL, 0xA8EA0951296169F0ULL, 0x1DD7F7CDE47E6E19ULL, 0xA6F6152099547F29ULL, 
            0x71D290D6C958C316ULL, 0x044E694657C618B9ULL, 0x85DF53DF445EAF1BULL, 0xC91899C4535D6A06ULL, 
            0x63D50DB02D8B1A63ULL, 0x9AAC21E6B89F6684ULL, 0x6423A10335B29169ULL, 0x48F363A8E8C369B6ULL
        },
        {
            0x5D64A10CBE52BBAFULL, 0x5DCA436BBF7555EFULL, 0x042C5462C3214431ULL, 0x7C645DF76A2E2A18ULL, 
            0xB04D9C82C5ECB666ULL, 0x60B4818C76AC3843ULL, 0x42797E5CFD47156CULL, 0x9F64B400CD6C9963ULL, 
            0xFBD7F211CC33BF15ULL, 0xCF81FDF2BDAFEB96ULL, 0x534B09A0C3E27361ULL, 0x2693A3D5C82CF3D5ULL, 
            0xF0FDFA76EBB2C8DFULL, 0x10BFB858EBF2D73DULL, 0xDFB45014A8062F90ULL, 0x072CF07FDE6465B8ULL, 
            0x353199E18D57751FULL, 0x753DA11E78FD2BBEULL, 0xA7FEDC3112A0532EULL, 0xE6508FB92D3497E8ULL, 
            0x5E0F594EB14AB3F0ULL, 0x97E1AFC5465DCACFULL, 0xB40ED8718D41452CULL, 0x20130684EA3BC978ULL, 
            0xEBBDF93EC221A32AULL, 0x866A9E1EF7635029ULL, 0xEC9F44D956B36150ULL, 0x9ED3CBA56C09A52CULL, 
            0x8BD9A7045621535AULL, 0x061617710C9937E6ULL, 0x51AED25D5840A121ULL, 0xD7B5585270EC48F5ULL
        },
        {
            0x52EF07289EA24614ULL, 0x2BE6E322D2E216FEULL, 0x7EC036D68B5AD615ULL, 0x746A19C3B5B619A3ULL, 
            0xA07C1AFE4F04C069ULL, 0x39321B61F831DE24ULL, 0xCD279D0510B9A760ULL, 0x11F84F9963C9A1BBULL, 
            0x96EF115C4EE842BFULL, 0xCE8DAC959E50B3B6ULL, 0xE721A1D78D409D3CULL, 0xA582F96A34925612ULL, 
            0xED23ED00C87D92DCULL, 0xDA0F63EC2EA6F0F7ULL, 0x67673D6A5BE5D6F9ULL, 0xADB6E22838E5476FULL, 
            0x9271F451597F01F2ULL, 0x076551D599C059E4ULL, 0xC55116534DF2B4BDULL, 0x540E426DDE258E73ULL, 
            0x6C8BB6EF475104D6ULL, 0xBCEF7F9C4311B4F9ULL, 0xA8C8C606F1BBD302ULL, 0x21C9FD26781F70D6ULL, 
            0xF4D8D673A4BDE1D8ULL, 0x59279B19A090ED48ULL, 0x93114F70541827A7ULL, 0x08482B6065C84370ULL, 
            0x6B082E5D60E8C17BULL, 0x5B03331DC428E5E6ULL, 0x971DFB6682CB996AULL, 0xA1B111B46284C489ULL
        },
        {
            0x7E09DE31A7109108ULL, 0xA8810B04E1340155ULL, 0xAC0DBB3AF6B761FDULL, 0x23D16B4E0435F87CULL, 
            0x6CC267CB23985EBCULL, 0x21DEFDF8B2B917C6ULL, 0x39B6AED12E7D0474ULL, 0xB8CA843D5953E874ULL, 
            0x730D5EE3B99ECBBAULL, 0x75174EADDB65A2ADULL, 0x1C0F94AA5B4E678EULL, 0x5DB2A5CC6A236F74ULL, 
            0x776688BA3D1DF6E4ULL, 0x6E2E4560A57ADACBULL, 0x3F8AC13E0F394EADULL, 0x948F1F2F1E2142A7ULL, 
            0x7DBBDE8DBE44959FULL, 0x2B6AEB4256D4490BULL, 0x500B20DD41CED704ULL, 0x3E04994B59E5381FULL, 
            0x78B75225E9A97DDCULL, 0xBEFD8938F1047F24ULL, 0x0FE31F3550C70E4EULL, 0xFF3BE227D1336F66ULL, 
            0x495E4DA98978EB62ULL, 0x1B361166433EED9CULL, 0xE66D62C0F1E11CA7ULL, 0x7E6DF5CF6E7805AFULL, 
            0xAD30877ED764C3E0ULL, 0x1270608EA0224F44ULL, 0xEDDDF1E9998F077EULL, 0xA3756C5129ACD553ULL
        },
        {
            0x622A89285E2D1EF2ULL, 0x32AC86B3221EAF0CULL, 0x68F452CCA44E1A30ULL, 0x712BAAD81446ED2CULL, 
            0x3F31D65661BA38ABULL, 0x36324693F5E12D4BULL, 0xE747784B0E532EF0ULL, 0xD2CD368B862031BDULL, 
            0xF8F39E0158E174FCULL, 0x3023268AF5118E22ULL, 0x5EBCD4A26A0B21D3ULL, 0x511E96859404DDA5ULL, 
            0xC69D435344186DDDULL, 0x43B4F724957DEC14ULL, 0x3EF2A3F2E49887D0ULL, 0x78B382C454C01182ULL, 
            0x3D758EB9CCC8A956ULL, 0xF660B2C8AC7B5018ULL, 0x91F6BD9599F7AEADULL, 0xEC9B72CE66CE6DF0ULL, 
            0xF941651D6C7B244AULL, 0x976D5BCD226266D6ULL, 0xE5A60DE3AC12ED9AULL, 0x6908483A880936DDULL, 
            0x59F0259E87C1D5D7ULL, 0xB22E1EFFB9EBFF3EULL, 0x55F2F0265D2C2F10ULL, 0x328AF4CF788DB21EULL, 
            0x18E70AF052815712ULL, 0x4B0543B5E3C8D283ULL, 0xEF267251C0AD3B39ULL, 0x5B5467EA60A14CA4ULL
        },
        {
            0x2742920F274AF596ULL, 0x8E74920948075BF8ULL, 0x292A9A04D7AFB79AULL, 0xB67AF02EF58F1F26ULL, 
            0x50E6FFD6334038CCULL, 0xB71C6259DADD6C82ULL, 0x6D9E1F8861F3AEA1ULL, 0x2E39931527832D0FULL, 
            0x09A29180BD272258ULL, 0x926400DF5AAE0217ULL, 0x7249916D2F58D329ULL, 0xADE088B0B5303969ULL, 
            0xC1C51B803BED87FAULL, 0x75402634D1607164ULL, 0xCFF28EFBD6516E2BULL, 0x63FF9AF296ECED77ULL, 
            0x50E03B65905170ECULL, 0xF9FBD9448AAF42D1ULL, 0x8C43E7332D515B38ULL, 0x25B6CC884D67CA49ULL, 
            0x5D4E4003C543557DULL, 0x615B3155DB96D44AULL, 0xDA880B562AC06912ULL, 0x672EC1AC231012C1ULL, 
            0x9AD8D67B03885231ULL, 0x670A9F50FA8E98A3ULL, 0xDFB507A011488842ULL, 0x6C22B16272EEF16BULL, 
            0xBA9CA6F3FA82DEA6ULL, 0xEF7634C8D78C4C9CULL, 0x61FE9888743C2643ULL, 0xE69638EE727F1542ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseDConstants = {
    0xAAD8842899CD15C9ULL,
    0x5E5C2D34286FAEF4ULL,
    0xBFDA838ABB1F14EDULL,
    0xAAD8842899CD15C9ULL,
    0x5E5C2D34286FAEF4ULL,
    0xBFDA838ABB1F14EDULL,
    0xDD9AD8D47999BCC6ULL,
    0xA25CA8C0F8D45681ULL,
    0x73,
    0x1C,
    0x65,
    0x76,
    0xC1,
    0x3B,
    0xBC,
    0x8C
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseESalts = {
    {
        {
            0xF73526D21032B35AULL, 0x42081BD7353182CEULL, 0x93E7C2752E7D2A1FULL, 0x7E8DA6860604D6C6ULL, 
            0xFEDE68B700136420ULL, 0x2C941533A7D8D07CULL, 0xA03D11F6C715D410ULL, 0x6BE0D4D340D8C45DULL, 
            0xD12B959D99131C23ULL, 0xC178E4F0C27C0903ULL, 0x00A35BD089BE5980ULL, 0x72F83976882DC7D8ULL, 
            0xA16CDBBA6A736734ULL, 0x8E1874F72B032324ULL, 0x6C4D00F03AEC9AA5ULL, 0x37ED9FB3300DFA44ULL, 
            0x9A544B66A25AD57CULL, 0xA0589D0EAB168946ULL, 0x857C09D6865B9F05ULL, 0x4AD7A457849909F5ULL, 
            0x144230FE50A8C3A7ULL, 0x22FC124A72BB46A3ULL, 0xBC16D500E3E8E40AULL, 0x665EBA4804A92934ULL, 
            0x81B249551E9B1E39ULL, 0x08030C369EA88629ULL, 0x19ADEFB7E91928ECULL, 0x4DB6F50CC4774223ULL, 
            0x51E05ED4ABE2DB43ULL, 0xEB038DC10CE1DAD8ULL, 0x48D38068C13C9EA4ULL, 0x00B9C319761BC2E0ULL
        },
        {
            0xD675CFB8EB0B4190ULL, 0xB81789FD68966EE8ULL, 0xAB6218B903A6F948ULL, 0x0AABD813E5D7A14BULL, 
            0xF1AA45691167EFF5ULL, 0xFC72F3142FAB261CULL, 0x3CC49D067667DB16ULL, 0x956610FFEC68F0CBULL, 
            0x8999FC8FE748FA87ULL, 0x8F854E0AAD25B0B2ULL, 0x352424A727B09607ULL, 0x22616510320AB33FULL, 
            0x715FCC9C14207F15ULL, 0x13A0C5E5C9BA7436ULL, 0x6FFBD1C43F0B56B8ULL, 0x5BA2D48B9C64244CULL, 
            0x6D953B8F8D7333D9ULL, 0x3671F24EFAB444DEULL, 0xBA27548C4C9ACD5DULL, 0x0C6928F18321AD56ULL, 
            0x039A5EFF85E94936ULL, 0xD9CEBC928800F32AULL, 0x2E9CA00B8F77C9A5ULL, 0x3C20C9CB24D3D118ULL, 
            0x0E2946F8DB68ED33ULL, 0x009CB79E6DFBAD74ULL, 0x8C1E8C42E964C94FULL, 0x8F2C610698F976DFULL, 
            0x11AF3E85DD9A2AE4ULL, 0x7DDE1A7F53EA263CULL, 0x146DDB768177D53AULL, 0xC66C92F11B5D3F85ULL
        },
        {
            0xA6EED63F40A3E1D0ULL, 0xF0EF84C7E5633D69ULL, 0xC7C4C917F35B34AAULL, 0x8B45A3A17E29176CULL, 
            0xBF20622068D2F99AULL, 0xE4A03966C95003CEULL, 0x15F168C5DDA023A2ULL, 0x85D83D54391392D3ULL, 
            0xC68CD0A423753C43ULL, 0x494BC988504F1EE5ULL, 0x25A8ED9557A25D62ULL, 0xEF11F5357FC9321CULL, 
            0x885FDB1025DD60F3ULL, 0xB504F848B0623A8BULL, 0x5FD02CB30C3C1944ULL, 0x1DBDC6C6FB7540E2ULL, 
            0x6E3694A44734E7BBULL, 0xD18401DA5C5B1213ULL, 0x1F76FA836289F44EULL, 0x95EF854C4675D57FULL, 
            0xC8AA456235AEBEFCULL, 0x5184B7EA048B034DULL, 0xA5A482EA5C2070A0ULL, 0x534E4632602BD4FCULL, 
            0x6D1F647C514A1E63ULL, 0xB3BFB5B544097440ULL, 0x5E865A3B43A9B367ULL, 0xDBD67622E67708E7ULL, 
            0xFCF35C2146B0A4A1ULL, 0x6E3D7C4C01539B4CULL, 0xCE673CB1071853DCULL, 0x1E622F6868499A99ULL
        },
        {
            0xB85B617296833E47ULL, 0x21B82698140C8488ULL, 0xD4CCD5620B1A89C4ULL, 0xB79A21CC78A38B66ULL, 
            0x5CB9E49499097A53ULL, 0xBA071FF42310DD25ULL, 0xB4A8F143308B923DULL, 0x094C57067C44E192ULL, 
            0xC466EB1F7BE0D791ULL, 0xA82841783E55E4F4ULL, 0xF3DEF5E0BD2B7D7EULL, 0xAD8E7E651EFBBF02ULL, 
            0xF3A1E60C42EEC993ULL, 0x7C9862C9BA274CB0ULL, 0x14AB804B30608679ULL, 0xFED3831F4A9A7A9CULL, 
            0x463FFBFD19D83958ULL, 0xF8C386E96948C04EULL, 0xED90C1280F2F054FULL, 0xFDAE90586645A958ULL, 
            0xFE41E372AC7DCD62ULL, 0x942636672186DE95ULL, 0x119DC465B7ECE8ECULL, 0xF9EAA8D26C2D0A99ULL, 
            0xB360EC823CB07DE7ULL, 0x93EB3DE493946A01ULL, 0xAFB55C6FB6AACE55ULL, 0xCDCE65A908CF8A8BULL, 
            0x3B77D8215DCA2371ULL, 0xA053CB445224C3B1ULL, 0x8CB85DA2009F687CULL, 0x5B469E5FEDE91B9DULL
        },
        {
            0x3DBEB055240B993BULL, 0xBE25FDB20D6B2CAEULL, 0x163644801BCC4E3AULL, 0x77D16C9B0318853FULL, 
            0xF7EB288D12A8E615ULL, 0x5C2024240AA576D9ULL, 0x256536B18EEB95C2ULL, 0xD9261903F1542707ULL, 
            0x43F87FECD55C357FULL, 0xFA2A1F052FC9A362ULL, 0xD510B21365378D55ULL, 0x1F7649E9CCF5F3A4ULL, 
            0x67B518FAB8081DC0ULL, 0xF6EC65FDA2A6D968ULL, 0x5DCCE4C7B024607DULL, 0xDD8EBB81B74D9F80ULL, 
            0xB7F3937EA568E622ULL, 0x47C68F031A4D2159ULL, 0x21C7521551EDB181ULL, 0xA84C280F189E075EULL, 
            0xB9EF355E46674913ULL, 0xAC76246328FE84B6ULL, 0x3C50D52D54FC335CULL, 0xCFFA247C05B0BFC8ULL, 
            0xC70A64D39FDD6130ULL, 0x64DDC19E08746D23ULL, 0xA742C43098CA1A01ULL, 0x5CCA42090A95E922ULL, 
            0x03ABB1BEE12113F8ULL, 0xA0D21227F4D35C68ULL, 0xE1859F727D4F5B30ULL, 0xB2FAD67B108598F8ULL
        },
        {
            0xB18D88C04E844480ULL, 0x8A2CBF8726654B60ULL, 0xFDD8D22ABE1F170EULL, 0x367E83E885694E39ULL, 
            0xECDE3441CCE20222ULL, 0x4FE0A19E79E15404ULL, 0xBB81E4A13222B4D1ULL, 0x9527DB7D09EDAE41ULL, 
            0x12AB6FD98CFCA9ECULL, 0xBBDB3160FC69139AULL, 0x38940BD31636F73BULL, 0x13A58897646AC79DULL, 
            0xDAA888246F67945BULL, 0x4DF7C87305FF1AE0ULL, 0x7220855B664FE5E9ULL, 0x2B5E122A522BF054ULL, 
            0x7C12B392FF1A6F93ULL, 0x28D2D704BF0E859FULL, 0xD3952694ADFB8B2AULL, 0xCDB1EB5ADCBA47F5ULL, 
            0xFD247D194D6FEDE5ULL, 0xAC2F292FD193AE9AULL, 0xEEBB3D530441B230ULL, 0x278BEDCF32595469ULL, 
            0x440A26BAE2B9118DULL, 0xD2DB480361DB3D51ULL, 0x592D855CA9F36AECULL, 0x7076F739F983B124ULL, 
            0x971B63E56D8D5E43ULL, 0xC19D8BD9DC24EFF6ULL, 0x0E9D0845FA7BE6ECULL, 0xEDE5CD7D00285E28ULL
        }
    },
    {
        {
            0x0174B8EE61A823C1ULL, 0x1747D5A4EC6D0028ULL, 0xE3506BF019CD6CFFULL, 0xE95F70E6B343E10EULL, 
            0x34BC5772328C7960ULL, 0x3D4D84BF89F7A73FULL, 0x96C6B2B766BB1651ULL, 0x3E68B56B2C3F42EDULL, 
            0x0715DE39CE673976ULL, 0xDE3CF0E3DDA8B854ULL, 0x0CED9948FF2CFAA1ULL, 0x712B1C7B97EA8754ULL, 
            0x3CC553037DEFA772ULL, 0x95C7C7258D1032ACULL, 0x45F13A123C1CAB8BULL, 0x65B19DB18F61693DULL, 
            0xDD4615DF17354D67ULL, 0x1112DFEEB0FF88A2ULL, 0x09B09B45D3E4EC44ULL, 0xBD6CF398B25ECF5DULL, 
            0x54698E9B56D394E7ULL, 0x50AF026ACE6B7488ULL, 0xFB29CF2D47255588ULL, 0xDB7B5A28510924C5ULL, 
            0xB5534E470D82E10EULL, 0x4431AC83BE845451ULL, 0x31CB1AB7ADD782E7ULL, 0x9EF21D028D58CCEDULL, 
            0x57FE8FD9C3A658B2ULL, 0x85F30A2BB0C85710ULL, 0x46FF09F2DA5B8928ULL, 0x51C42D8653EAAC59ULL
        },
        {
            0xC4D78F4F8845711BULL, 0x175155888555D8EAULL, 0x0728DD668714B242ULL, 0x83849B4EFDE1BBE4ULL, 
            0xDDA85925296D45BDULL, 0xD08049EF69B3608EULL, 0x046DEB11145BB977ULL, 0x34AA8A61FE9797FCULL, 
            0x7354FAB86D362221ULL, 0x01875D2601A6AFDCULL, 0x09279930565D8544ULL, 0x2BF84C4A54360CC2ULL, 
            0x96D1B8C7294FAC35ULL, 0xBF251ADC3EB5D21DULL, 0x44A02D99BCFB8A76ULL, 0x585B5FD08E10AB0BULL, 
            0x117AAA4D41E1804FULL, 0xBDBDE6CAF0550106ULL, 0x133B0A60B07E83D4ULL, 0xFDF0EBC7A817C28FULL, 
            0xC1D959FC620BDCC9ULL, 0xE1D1FC742D23ED21ULL, 0x7057A9DCFA9CE7DEULL, 0x9754F4AEE1D28B37ULL, 
            0x30F5D3326EF00142ULL, 0xBE2D12B47B70F543ULL, 0xCB053C9154AFE3F1ULL, 0xCA4AFE8FE14A0F33ULL, 
            0x8F7206D3BF1DDD83ULL, 0x3563D9D1617FC7B6ULL, 0xE1AFB6532556C093ULL, 0x016FE6AF0647062DULL
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
            0xD85D380C8D79BEDCULL, 0x43987A2FA2DA8071ULL, 0x75139B49A6613BCFULL, 0xA6AF95B16B24EC17ULL, 
            0x66A52D94BB4468C9ULL, 0xD407720467992DDBULL, 0x2AE0C62E81B328EDULL, 0x80178B1BACD386C7ULL, 
            0x80BB8176C639984FULL, 0xA2E37DED555A4A8EULL, 0xECA9752F9F0FCFFBULL, 0x372B9E3B86B58407ULL, 
            0x8D660186C957E733ULL, 0x08E214D0EA9A6204ULL, 0x01D798964DADF745ULL, 0xEE0AB4888803C695ULL, 
            0xCEA3E56D3570EC0AULL, 0x3700E3BC223F9B61ULL, 0xC2C0EF96B46A059DULL, 0xCAAE091EF248C039ULL, 
            0xFB98D94447E8F7DCULL, 0x9FEC21662D3FDC2EULL, 0x2227B930A50E841AULL, 0x433F8077AAC087EBULL, 
            0xFD67996B6DC0FFB6ULL, 0x7F9EE7F68070D778ULL, 0xADE708449A275EBEULL, 0x536DD5EB0BE94624ULL, 
            0xFF48A1913D90FE94ULL, 0xEDE4ECD091021F39ULL, 0x0345B88B21BC5EEAULL, 0x975181B63298C6D9ULL
        },
        {
            0xD93F47B075530DC6ULL, 0x7A4162D6A7A7A53AULL, 0xE4DDBF9C966A3A2BULL, 0xAE161560962DC4A1ULL, 
            0xB2A1CF6FD078A616ULL, 0x6F24B7DFF78C59A2ULL, 0x958C14B89A81C328ULL, 0xCC887197F2DF0510ULL, 
            0x21A97F05D84CFA66ULL, 0x8E801175055BF10CULL, 0x8132042015AB0F9FULL, 0xBF075D215B8275B8ULL, 
            0x08E0603EAA6A16E9ULL, 0x191094BF4DE721C1ULL, 0x0B7693AB61D984FFULL, 0xB5EBA8C7E738B4C7ULL, 
            0xF7EE8282EC5DA7A6ULL, 0x82594FAFE1EB4CC7ULL, 0x7D8B16E8DD773E74ULL, 0x09D6E9753F71DEE4ULL, 
            0x54140B40600963EEULL, 0x7466388DAEBA9406ULL, 0xD65F633D84FF9751ULL, 0x4046CBB1D6C5097AULL, 
            0xC2B700DF16975313ULL, 0xD8533DC68F878590ULL, 0xE6AAE6945B9F8F4CULL, 0x5A44A20C3FDF7B2AULL, 
            0xFD9E6B9D8592F16EULL, 0x89DF74006D7AC5E0ULL, 0x78A29AA876B38C70ULL, 0x34AF91E73BC527F2ULL
        },
        {
            0x7855D32E2D269C26ULL, 0xA372220217DF59D1ULL, 0xF24F64DBD322223CULL, 0x607A88F2CC7DFC3FULL, 
            0xD36EE96D7F9437F8ULL, 0xD83D63B4C9C18D66ULL, 0x91B871261FFE5E30ULL, 0x2EA6B196F9273AAEULL, 
            0xB7454901C833A070ULL, 0x2CEDC90B8B44325FULL, 0xAA8D9C0FF089F841ULL, 0x7F7B349862D25E8CULL, 
            0xAEF3F01BAC91A21DULL, 0x5A1495AA8079E162ULL, 0x59E5A49991B5ECECULL, 0xBD985F3133A69153ULL, 
            0xF04FBF2A4D1722D4ULL, 0x38B9FEE2712321C2ULL, 0xDEC9825AC702003FULL, 0x62F53A989CB55F95ULL, 
            0x709C420D34682C01ULL, 0xD31948E5B75F058BULL, 0x650F71CDA796F6DEULL, 0x3B1FF8E2FF87D9CBULL, 
            0x85D5A3EF1C590E8BULL, 0xA1F205000EEDBB78ULL, 0x5E7A72AC498A81EAULL, 0xB6571AEABA22DB5BULL, 
            0x6EF3AD0B5AF11DF0ULL, 0x5D9151BDE6A41EABULL, 0x8241B15F0787BB78ULL, 0x212834CDA3CCE5E3ULL
        }
    },
    {
        {
            0x8A29251450EC8F1BULL, 0x42538FBDA0A1DFBEULL, 0x3210A03021DB56B9ULL, 0xA1B5C3775DD2A28EULL, 
            0x595940718A0E86ECULL, 0xC16C9893511733BFULL, 0x452AEDADB8DF48C3ULL, 0xB9A3F21DC492BDEBULL, 
            0xE38F0D75A3409C0DULL, 0xED2663230FC19841ULL, 0x8AAA4E720D709B9FULL, 0x8234E1D3CFC1A45DULL, 
            0x680F5562689FCB6AULL, 0x6B1CB327E13699BCULL, 0x588A74EF026B1E3CULL, 0xB7D19C7E25F04EEEULL, 
            0xC26AC52A66C6A14FULL, 0x69778013CFF2B633ULL, 0xA0A34DB0339026ADULL, 0x45E51317136EC0F6ULL, 
            0x099B678977777637ULL, 0x8BA13CBE3B43F21EULL, 0x29C9CED0A8073847ULL, 0xBA320DB256068DC8ULL, 
            0xDF8EECEB6F35B459ULL, 0x42377602E1A72668ULL, 0x5A08CD02ADC4CC13ULL, 0x54A53A2A62B5C276ULL, 
            0x15A3AD3CDD809724ULL, 0xC85C7A7E91A464CDULL, 0x3F95623132152BDDULL, 0x360EA219AF3C92CDULL
        },
        {
            0x00E5C88E0F095B06ULL, 0x7CDECE241A086187ULL, 0x3EC87178AE8DED0AULL, 0xAAFA4045220559DAULL, 
            0x41D85C95F2639BE9ULL, 0x342DC1E7B2E5333CULL, 0x8FE6410AA424FDCBULL, 0xE288F0C7951BC57CULL, 
            0xC3C24B85230C9B58ULL, 0xC24ACD0800855441ULL, 0x3B9D6C24D0B17C56ULL, 0x3AD47E9870E04F3EULL, 
            0x63E585E9E777E1DDULL, 0x2BEEC50041C1E6CBULL, 0x70D690978087FBDFULL, 0x745202563DCB9B1FULL, 
            0xB337DF45A905BD6FULL, 0x97AB7F6D36073694ULL, 0x9F02C4E6B344AA8BULL, 0x324E3AE1032477E8ULL, 
            0x73702652E9CDEFD3ULL, 0xE9C2496754085A3EULL, 0x348E1D2587114DF1ULL, 0x6E8D55C8FB2301D8ULL, 
            0xC699051136F715C1ULL, 0x9212FDFC82A99666ULL, 0xC97908A530BCE0BDULL, 0x344F3399F8CAB143ULL, 
            0x6FD3E914A8A1835FULL, 0x6F9F1DBD46216E4BULL, 0x20933CAF130A8D22ULL, 0xD58642FFD5ED4943ULL
        },
        {
            0x86D6197F0608106CULL, 0x0431100757730A12ULL, 0x1C5A2EC7061688BAULL, 0xDD6A01A1D8ECE57DULL, 
            0x4D2C956A9BBDC93AULL, 0x4E24B919052A2309ULL, 0x3A0E1F2DF8AB5C37ULL, 0x2ABBAF91DD9C73FAULL, 
            0x6CABAC86428823FBULL, 0xEF7F22730B82BE5BULL, 0xFF220683358AA9FBULL, 0x3E9B9D163731E422ULL, 
            0x32F2868E28DFB5D1ULL, 0x5BF7F2A7188A20EBULL, 0x3AA1972AE06F481CULL, 0xCD8DBD6E5BB8A646ULL, 
            0x1EBB5443E428B600ULL, 0x7509B509012BDF2DULL, 0x6EF3290C37B4FD82ULL, 0x495C53F97F2093FBULL, 
            0xD4135D0AF18E4117ULL, 0xB95D4ABF076CDBABULL, 0xA0702DEF11FFF679ULL, 0x68E1631CB4A727A6ULL, 
            0xA8203902EE5434EEULL, 0xF7676932BBB0B393ULL, 0x921BE777A06888A1ULL, 0xB29BA18D20034A12ULL, 
            0x02F6D89AAB518AA0ULL, 0xCA8E84A1D390157AULL, 0x0262BB3A86D7C242ULL, 0xC73657AD8E10E9F6ULL
        },
        {
            0xC0DBA667170CAB14ULL, 0x4367D4C6F5FA7029ULL, 0x2BE25D2294739623ULL, 0x41F890B8BA7A28ADULL, 
            0x704DEB7924A705A8ULL, 0xD81A0E0DC91D0D56ULL, 0xA92F525A26615F94ULL, 0x32A914354A2B3FA6ULL, 
            0xEEAA8AD8812A453DULL, 0x91FCA784A4131109ULL, 0xECED780091180BCCULL, 0xDE22903FB94C4B84ULL, 
            0x4B6748DA6790C583ULL, 0xF3EE667A02D9AA76ULL, 0x1E0DB9962E9B2655ULL, 0xE5FA2064E0B7F5A7ULL, 
            0x4F5AED3CE290CDEFULL, 0x49183302D47528DBULL, 0xFAB3B735DB7FB4E3ULL, 0x6EE52F463FE3AEF1ULL, 
            0x54002F5C3D85D8D1ULL, 0xF7699331C1245342ULL, 0x889A8FE21E3D126FULL, 0xE4D81280DE5D83AEULL, 
            0xBE51FC62E7707E33ULL, 0x25B33E7CA5F1AFB4ULL, 0xAA988D571EC63445ULL, 0x363939D90A0E577AULL, 
            0xDFAB08E4AD538E25ULL, 0x677B70DEF81F8744ULL, 0x787BC0658AFF2F65ULL, 0xAEE02A79E6B0A23DULL
        },
        {
            0xC64C101F9398475BULL, 0x9A1F1688047A82DFULL, 0x6AD64465DE899096ULL, 0x4387739D786DE7C9ULL, 
            0x84887EF702A14915ULL, 0xFE5E5911DDE2CEBEULL, 0xE6D78282401A5C54ULL, 0xE1701E715D349D5CULL, 
            0x5D597CFE914842B4ULL, 0x49A9DC70D16344DBULL, 0x9D8CC9D61B7235B7ULL, 0xA9B124D8B67702C4ULL, 
            0x379AA8AEA7391907ULL, 0xC5856F09F05ACD26ULL, 0xB09AB1F06363B069ULL, 0x56C209D73EC0F0C1ULL, 
            0x675FF16ED11EC321ULL, 0x0994025658840B36ULL, 0x203ABDBAFC8A5A9DULL, 0x608B6351FDD85FD1ULL, 
            0xD23DB24AF7F9BC8EULL, 0x7F1B093707126B5EULL, 0x899415739B46C52EULL, 0x5E520F7068580726ULL, 
            0x8FEF94697D845176ULL, 0xEAE46E11656DA16EULL, 0x8F942763EEF57FB4ULL, 0xE6EB4F6FF598A393ULL, 
            0x0894C85852685F56ULL, 0xF3FFA36D85A9CBEFULL, 0x65E200AB6F648CA0ULL, 0x540E087105E381EBULL
        },
        {
            0x044C42EB49137538ULL, 0x4A179DF2330AC918ULL, 0xD266BF1FFB8F26ABULL, 0x2E57849E7611CC30ULL, 
            0x4E61608EDEF8DF8BULL, 0x5BC7831CDF7AE6A3ULL, 0x43D3013CCE6EA619ULL, 0x62B0001FEF9C4829ULL, 
            0x52071FF163AC3205ULL, 0x293BBEEDBCC3ED54ULL, 0xA0AFAECFA9F8B1A8ULL, 0xE24D99F330468378ULL, 
            0x45C769059BE4ABA4ULL, 0xDECF364E0FD6630BULL, 0x6BA5213FE2BA04C0ULL, 0xB80D87E1D9661749ULL, 
            0xFEF17F68FBDF15D1ULL, 0x25DBCCA0751E3072ULL, 0xF6667E1D9F0061FFULL, 0x23E8342CA5EE286DULL, 
            0x2601055CC29C6B4BULL, 0xBA8602382097D0D8ULL, 0x5559CED84119C290ULL, 0xBE3439419036B1E5ULL, 
            0xE96B87DFF18718D3ULL, 0xC98A0629FF5715C8ULL, 0xEBA7CF5C9B4077F2ULL, 0x5FC479D863B095FFULL, 
            0xAA3310C5A8014367ULL, 0x64AA379DA8DF1D06ULL, 0x587E9A7495F72CC5ULL, 0x13409264C307E02DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseEConstants = {
    0x6CCDB60AE38B86CAULL,
    0x81C11616223E7FAFULL,
    0x78CE010979E27E14ULL,
    0x6CCDB60AE38B86CAULL,
    0x81C11616223E7FAFULL,
    0x78CE010979E27E14ULL,
    0x82767961540033A8ULL,
    0xBE4CB456F861A7AEULL,
    0x72,
    0x10,
    0xA8,
    0x35,
    0x13,
    0x2D,
    0xC1,
    0x39
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseFSalts = {
    {
        {
            0xDF3C60B6DA92017AULL, 0x0A68D7C3FE633CC4ULL, 0xE5EE4DF9B1928EBDULL, 0xF653C0796B87660CULL, 
            0xE7C73D2C80883B17ULL, 0xD4E3392C17426512ULL, 0xE0468E51952E6B9BULL, 0xB829D7F4C2883292ULL, 
            0xBDF3EF5EF4C32FC2ULL, 0x42BEE8EC578790BAULL, 0x5DB661C5061D8EBEULL, 0x1951912CE34B745CULL, 
            0xFB9F4CFA0B71778FULL, 0xE457DBBEFB8DF700ULL, 0xD1158C00D8B620AEULL, 0x0EDDACCACB43FE5DULL, 
            0xD14D9DA22BF27116ULL, 0xECFDD69BE951C8ADULL, 0xEF759D47233B65EBULL, 0x7B737F6C007E9C12ULL, 
            0x28EB72F0707BA157ULL, 0xF851096DD903E472ULL, 0xE26957D57625C1B0ULL, 0x0381C3965BC2AA23ULL, 
            0xAB78FE588E0E85ECULL, 0x38F0C20F8AFA28BFULL, 0x8FFB91221FFC6219ULL, 0x94AA15A1C99B0844ULL, 
            0x41998CBC1B85B56BULL, 0x6F5BD2F2C5400AEEULL, 0xEA6001E44ECB9F27ULL, 0xCB90DA04EC9A242DULL
        },
        {
            0xB942B7F39D2EBEB0ULL, 0xA22D79E10D546A30ULL, 0x01164C2C26A1D232ULL, 0xF89737ED9A1C78B8ULL, 
            0xB79E5FBCBBF05128ULL, 0xCE0C9A3508EBB83EULL, 0x1655BAE0E679572FULL, 0x4FC141ECF6F9115FULL, 
            0x64D2E30A9D99438AULL, 0x108D12020CCF81A6ULL, 0x0CA6736FC1E92501ULL, 0xB0EA79943D9DC687ULL, 
            0xC23A57D1290145A9ULL, 0xC3ED1C4ABC987734ULL, 0xCF9EBACC36012E7FULL, 0x6B3B5C7E2C0BC2D4ULL, 
            0x114D75CC4EC37D3DULL, 0x51812C8B312CE13FULL, 0x8CCD352208938000ULL, 0xEE9D300D1D8C7100ULL, 
            0x094A29570A9C99E7ULL, 0xFA626EB845438BE8ULL, 0x9DC8B9AAC94E6E2BULL, 0x435EB7394F9C5B51ULL, 
            0x916C58015D334E38ULL, 0xCB0E0B7AD331FD4EULL, 0xD037D8E57B83503FULL, 0xE8E27B227A2B9C25ULL, 
            0xD6CDE0140475CC3EULL, 0x24B35E9EFE4B2789ULL, 0x06C1C932754F8F34ULL, 0xE71042FD470ED1A3ULL
        },
        {
            0xD6505CBDB8F6DDB2ULL, 0xC097B9613ACCF910ULL, 0x4033219D6E06CE0FULL, 0xE180CD1AABBB6A8BULL, 
            0x8E8A60262AE871DCULL, 0xC7F8F372B9403EF7ULL, 0xE1C97A2E2EDF233DULL, 0xB912BCCD5819332CULL, 
            0x0852908AC9A8B65EULL, 0x3320D88446FC63DDULL, 0x82F397CB01252621ULL, 0xB0E2A4A2E53BB0ACULL, 
            0x68C5BE1802ECCE22ULL, 0x2E07242B22B3A908ULL, 0x9CCB1316F8956F30ULL, 0xA7E02D2A23EB41C1ULL, 
            0x027EB28172D49852ULL, 0x6056AEA7C34CBC91ULL, 0x3D624BE1EA18259EULL, 0xF58A153D3ACD80FDULL, 
            0x00C5B5C68AD268CFULL, 0x1CD531D7BD944450ULL, 0x11C32B5241C2BE54ULL, 0xCB4C20DF5C691847ULL, 
            0x523F542D2250E0ADULL, 0xA204A609F262BB1EULL, 0x86549FB5E4B38C1FULL, 0xA6ED72E0D5747880ULL, 
            0x58746F64B50818F1ULL, 0x6B89BB995866265FULL, 0xB4740B95379C06E3ULL, 0x94AEAAD8381E932CULL
        },
        {
            0x7CA2ACE368B607BFULL, 0x447765EA8CFEE851ULL, 0x41EEB134532D98D0ULL, 0xEF80AF65416ED952ULL, 
            0xE2EEF65A023EB6EDULL, 0x51725FBF75FC7D97ULL, 0xF5286D5AB0A1D360ULL, 0x89E7127F56A471E4ULL, 
            0xE3C4063D8FEED21BULL, 0x06048E8549A7A54CULL, 0x9D2EBE2CE14A5905ULL, 0x14E3599CB30AFCA8ULL, 
            0x8A49B5626C93EF57ULL, 0x95BF429270B8933CULL, 0x13656D12AC6F77ECULL, 0x617DCB076C04AE71ULL, 
            0xC9C04E9E08356DAEULL, 0x3FD343F3F7896EEBULL, 0x147BA5D1B0CF27DEULL, 0x274D9ECD9BA48897ULL, 
            0xD2223822E69BC2ADULL, 0x0ABFF6E8F40B1834ULL, 0xFC16DFAB22F0F551ULL, 0x636F29D3ED627B42ULL, 
            0x2B42F1E71E140763ULL, 0xA05ED08ED8A50719ULL, 0x3E734F7BB747283CULL, 0x5872C3E9DC0CC4A8ULL, 
            0x374849E63261D13CULL, 0x3A3D563405CACCDAULL, 0x5DEF57435D863974ULL, 0xBD1CA87F34D489EBULL
        },
        {
            0x215875D761BA968DULL, 0xB413F50DBD681144ULL, 0x5FE18B15A26FDA3FULL, 0x37DC40EEC20582A3ULL, 
            0xC6EAEB0BAA4B3D0CULL, 0xC2DA66CB8370991EULL, 0x00270A7D85EA450EULL, 0x013944E1BAAD8644ULL, 
            0x41A3CCFB8FD1F035ULL, 0xE261B6B948712915ULL, 0x34EE723C316DDC95ULL, 0x813BED5E5F06966BULL, 
            0x9C6C2F14C8751D53ULL, 0x6B87AE78CDBAE21DULL, 0x9B3800E3C5F0DD45ULL, 0xC8811067F6F9515DULL, 
            0x2593325150933E66ULL, 0x9BB67491A1D64C2AULL, 0x76403D45702BBE0DULL, 0xF3E977ADCDC80AA8ULL, 
            0x138915FDA73C6D62ULL, 0xE1FAC94C06BE6ECAULL, 0xF7A77A53A2D84B41ULL, 0xA0AE20FC62B57A8FULL, 
            0x1E05DD4ABAFDC810ULL, 0x0D0839D9D6FF83DDULL, 0x5A30099F98D6D132ULL, 0xE4CB9B2A42EE0CD5ULL, 
            0x4754A20AC8B6DDF5ULL, 0xFD902CCD22E516ACULL, 0xA35E2B50833A489CULL, 0xFEF4FD60A8C352BFULL
        },
        {
            0x2EEA8EF7CCB94A03ULL, 0x9694F3779CCFBA1BULL, 0x27AA8EE7EAFDE752ULL, 0xA1EE6FEAD1753B58ULL, 
            0x05D76A5C1765D1B9ULL, 0x9A50276D4503F5BAULL, 0x48EFC3EDE82EFA0CULL, 0x195AAEB63F8D0792ULL, 
            0x4F4C128B04E02AC2ULL, 0x8B2D0381B9F8077AULL, 0x31C57C1FFDBFE21FULL, 0xADE0B6244BEE58EFULL, 
            0x62916C15E2F68A97ULL, 0x93766320D2DDD915ULL, 0x8A158D3F1EC623B1ULL, 0x6C59804F9289C3A2ULL, 
            0x48E7100D9BE149E8ULL, 0xC764285329F08EAEULL, 0x0A2561CE5E375280ULL, 0x319E8008BDE5FB86ULL, 
            0x774A3621624E90FBULL, 0x4C2A3E97842429A0ULL, 0x9C62B861450C1436ULL, 0x7FD3E4F5EEFC9472ULL, 
            0x94DD8309DEA16196ULL, 0xA3C5CD22D4CC59F9ULL, 0x4E79A595FDE680C3ULL, 0x848D64089FDF2033ULL, 
            0xF16C17138A478F63ULL, 0x2CD8BECC20B3C3F0ULL, 0xFC05B63285BFDC54ULL, 0x1B03E9A898553055ULL
        }
    },
    {
        {
            0xEF919DCB7265774CULL, 0x4AEF079E833EAB19ULL, 0x3D6EBCF73A4D71BDULL, 0x4F86A740089648BBULL, 
            0xC8BB56E4CAE105BFULL, 0x02FC6D65358BF833ULL, 0xF32CFA4475C00911ULL, 0x56CAAC30BF718CB1ULL, 
            0xF22905E93DCCD40FULL, 0xB2DB8E99FC531575ULL, 0x0FBDD3F6EBF56BCCULL, 0x055AA3A173EDF489ULL, 
            0x1C7B69111B96433EULL, 0x6D820A0E79655BF1ULL, 0xA4FAAA2CCC5997E3ULL, 0x2555312B637CC6D5ULL, 
            0x6666EC84DD7CCC31ULL, 0xCD1CDF79A4373EA5ULL, 0x481C77CBB4EE61F3ULL, 0x94E77390B2B2D985ULL, 
            0x74407067215975BAULL, 0xF7A10ABD44B16CB2ULL, 0x36F45E5E95DE69B2ULL, 0x62F2D630CEE88E67ULL, 
            0x406901347CD94504ULL, 0x242F96D76F1DE523ULL, 0x1302C2176D537E5BULL, 0x5B7949AD9A404157ULL, 
            0x75F2E4F34772EA34ULL, 0xACF351E1BB205815ULL, 0x9DF0E85CF9871CD3ULL, 0x446400962BEE2696ULL
        },
        {
            0x033BAE475D4782B7ULL, 0x7F476F2D5B3D09A3ULL, 0x95D1EDD9FADAE6B8ULL, 0xE5A543C9835B100DULL, 
            0xE432E09AA6AC1A0FULL, 0xA06467824FA0ABE5ULL, 0x88D166294948CBD6ULL, 0x4AB5F7159EA9F724ULL, 
            0xFDF992A2C2F31248ULL, 0x0889D3432124371CULL, 0x99FE610F1FE156F5ULL, 0x6580BEF8A298BD1EULL, 
            0x5ACE634879AF76F1ULL, 0xAE19FB41175D941BULL, 0xBB6B709694CD7EA4ULL, 0x500688655E3BE3E8ULL, 
            0x2512EA39F49725EFULL, 0xC2635D516D1769B8ULL, 0x8CB6193AF102B575ULL, 0xD434B212EA00651BULL, 
            0x8894C22858D6A196ULL, 0x2DA186E41FA8DEA9ULL, 0xF97D60D4B4D06616ULL, 0x53E7E1DFC583E009ULL, 
            0x0625ED133CACF02AULL, 0xD2934EB0E6842122ULL, 0x6036B19C00CC0C85ULL, 0xC05244A1505160EFULL, 
            0x51515E335B9291F1ULL, 0x008367DD7C98CA55ULL, 0x32AF44EF780F7EC2ULL, 0x5E7DD678BBB79C86ULL
        },
        {
            0xAC129828BDFE9A6CULL, 0xA9D3B5C92D1C2349ULL, 0x8AF3743919A1E8B9ULL, 0xF6DF9C69E14CB8AFULL, 
            0x599FF09B1D3178FDULL, 0xA3DC82B101103712ULL, 0xEC2642AEC082AF59ULL, 0x58008BE8EF00E6F1ULL, 
            0x81B0D54D61E21A59ULL, 0xF4D6865D3A18A5D7ULL, 0xF5D2FD60CF45C31DULL, 0x82821790E970D990ULL, 
            0x0CDE742538634D9CULL, 0x0809A14DA394D242ULL, 0x3F940C015814F12EULL, 0x30B4D6243960F1A2ULL, 
            0x2558A628964959A7ULL, 0xEFA020398324EA96ULL, 0x8BB6BEF404537B65ULL, 0xA3C3E69C21BA4036ULL, 
            0x90A003B431801A8AULL, 0x332F26A1E875B853ULL, 0x3801EBDEE04D9F1AULL, 0xA3DC8B2BAE374C11ULL, 
            0x4CA36364B9A6C82AULL, 0xD8371DA8746706AAULL, 0x40490BD6F6AD0B60ULL, 0xACDECA6A67BF83DBULL, 
            0x3482F5077ECD13CFULL, 0x67F96C8021F4672BULL, 0x5BDAA452EEAC9AD7ULL, 0x0EF3D31F4D05D954ULL
        },
        {
            0x35EC2D025BE50691ULL, 0x939CA43DFF72D170ULL, 0xFBADDD26B6B547D4ULL, 0x9E4C644EB4A94D51ULL, 
            0xA3CDDAEE4229043EULL, 0xC109B67E30BF7AD1ULL, 0x078069327589DF3AULL, 0xEA901923F041216AULL, 
            0x0BC22E7D6ABD31AFULL, 0xC1ED35C9E2009E92ULL, 0x0CE0D606FD0BFEAAULL, 0x013F6E0CB41B4821ULL, 
            0x3D68EAA26CFD064CULL, 0x8B904BA86C1061B3ULL, 0x6DF59DD42985D49DULL, 0x4A423425AA40E9D4ULL, 
            0x9075D485C321B5A6ULL, 0x2F32EB75D6B262E7ULL, 0x542AF97C2A0CFD4FULL, 0x2BBF6EFE18F8D7ACULL, 
            0x94B280932F74A4CEULL, 0x50927374EFED5705ULL, 0x2549DBB81AF24158ULL, 0xD4A028C54B96C945ULL, 
            0x34D7E60B0ED38263ULL, 0x42A78CF98A530624ULL, 0xD42DE0F42FA3FEE4ULL, 0x2ECABAFE676DE450ULL, 
            0xF8FE08FEB1CC6AC9ULL, 0xDC7A278E9013B4C1ULL, 0x0F3CA076FBE60BDAULL, 0x396535B4A389ACADULL
        },
        {
            0xA0FD64A39B2374DCULL, 0x0A13F553BB42DAACULL, 0x295D38BF1D5D4007ULL, 0xF76C380F816C6FFBULL, 
            0x7943C1E2E51B92D5ULL, 0xEB63E9AD18504565ULL, 0xBBCED1578A5085D9ULL, 0x2ABA91D411DA1D6EULL, 
            0x9A027F3BC2235E19ULL, 0x6924DACC095DCBF6ULL, 0x4522E6CFF4D61AA5ULL, 0x53A8EC4B16D7185DULL, 
            0xD5D9567EF2338802ULL, 0xFB8B706D31E067EAULL, 0xB8739937E531A7FDULL, 0x5D057F3945FF1587ULL, 
            0x3D3DDFA5813B78BCULL, 0xF46768275912163EULL, 0x663F868497DF8C37ULL, 0x701878AEB49747C2ULL, 
            0x7004477776D275BFULL, 0x33832DB4171AF814ULL, 0x4CC5FBF752121DE6ULL, 0xFD3C9337720CD9E6ULL, 
            0x86B51AC718D1C67FULL, 0x730C0B77FAE18995ULL, 0x3B119EA454C9F599ULL, 0xCF7DBB0A00B63E00ULL, 
            0x869B77853134D192ULL, 0xE562BE618E6FCCB1ULL, 0xFB98A88D174449EFULL, 0xDB45F4221B6DF221ULL
        },
        {
            0xFBDFFC33B803B9B0ULL, 0x3BBE3F00D9A7C4D7ULL, 0xD0902D8E6424ED98ULL, 0x015E0C360588A909ULL, 
            0xF681513DF01AB5B9ULL, 0x25DBAC6F0067C68BULL, 0xB8148C6901F1F8EBULL, 0xD1DAFF12D80A8EA0ULL, 
            0xD2CE2A96D392429AULL, 0xDDC4E793A576C9D2ULL, 0x2B92E56006EB4CB0ULL, 0x0B3E43D942162B28ULL, 
            0x81F3EC9360965A7EULL, 0x39D8BC6DA019624BULL, 0x4E2B8F955F4C5F59ULL, 0x0F03DA44071A7953ULL, 
            0x20B76C3639173C07ULL, 0x04C5483154FA2CE4ULL, 0xD4B60566700686E5ULL, 0x6B6047EF4D618163ULL, 
            0xD06CA8B68C31B8BBULL, 0xDA4941163F5632AEULL, 0x3D7E44F566637525ULL, 0x4CBDAE555BD82345ULL, 
            0x0C1B35004890D287ULL, 0xF56D80B973AB0B21ULL, 0x8B1A434A2AADD37BULL, 0xDFA2116C8929F70DULL, 
            0x97B0D2A0C3E84D44ULL, 0xE95750744BF56799ULL, 0x579A1EB5DA364B5EULL, 0xF28025A92DE1DED5ULL
        }
    },
    {
        {
            0x505B623133E7D88FULL, 0xB90A02F7A076C43FULL, 0x13D8ABE4BD512180ULL, 0x30E9EC3A7273B894ULL, 
            0xA2BEDFB3B562085AULL, 0x69B5E38B11196F65ULL, 0xBAE97B8A760893D3ULL, 0x66D218A0756462CEULL, 
            0xB475AAD73506B51AULL, 0x4BB510730012521FULL, 0x475CAE5F4D4B797AULL, 0x4DA6CA6A51097863ULL, 
            0x1C8D14F65C44E72DULL, 0x0A55378E061E67DFULL, 0x0632D3AED3623AE0ULL, 0xBE75DC7F29925BD7ULL, 
            0xCC63EB90F2C3A128ULL, 0xDA8478AD81C7F671ULL, 0xA9DCDEA067EF5A87ULL, 0x68850B7111E6E6C9ULL, 
            0x3209FB7C4B4F2BDFULL, 0xD9EFC6341FA7BD24ULL, 0xD1A85DF497E2EC93ULL, 0x98798CEE9811C51CULL, 
            0x9C0A0BE94A09E8E2ULL, 0x2CCC95532B79410CULL, 0x7F0B16594658EFB5ULL, 0xC8F644A745F73B56ULL, 
            0x91271BE05F1A8F64ULL, 0x0BC5FF2814C5EBA1ULL, 0x300D9D771BB4F43EULL, 0xD86C4D76F5FC69EBULL
        },
        {
            0x3BCB6920CF5B596CULL, 0x8F43BD4BE58DECE9ULL, 0xEE40A4A0FD57987AULL, 0xE3B53522DA4991F5ULL, 
            0x0FAD41964374AD57ULL, 0xEA57FF8091B9B9CFULL, 0x5247E13B6B9BEE2BULL, 0x5C983673E0F4A1E6ULL, 
            0x1E8BB4875B9389A7ULL, 0x9ABC0397AE383FE7ULL, 0xF421DA9AEFCD2092ULL, 0xE5D14B8A3D2ADBA5ULL, 
            0xDC2697370CB2FC88ULL, 0x22893DB6EBCB6B00ULL, 0x176CA2D78B626C3FULL, 0x92FFDA7F7A689B88ULL, 
            0xD238E67CE75D7A78ULL, 0x7C5AA483D2A219DCULL, 0xBFB1749591E3DA0AULL, 0x8637EA5EA0B6FD01ULL, 
            0x0A44B7DB66CE21ECULL, 0x2D68CB58455F5E5BULL, 0x7E78CD48AD999817ULL, 0x2D99E35FB2876FDDULL, 
            0xB73ECE74D3F56881ULL, 0x8EC2240A930DC6CBULL, 0xA2F72C5BE50DEF72ULL, 0xF479B61F4B1C84A2ULL, 
            0xAF64363AB078AD0AULL, 0xE787B6A60A4816CBULL, 0x9C48E1DC5E3B5AF2ULL, 0xAEABA19C91D8E2C9ULL
        },
        {
            0x9CDB4A435DBAAF81ULL, 0xFDE9067813608C6AULL, 0x4463D81E512440F2ULL, 0x027C515F09D41C76ULL, 
            0xEEC1BD25B1B47939ULL, 0x101949B8F8078240ULL, 0x5324138D68FFDA23ULL, 0xCC180D552D4A9C92ULL, 
            0xC620DD43D893AD3EULL, 0x416A740C03E073C5ULL, 0x71AF07CFF4784A99ULL, 0xA2E4572199C11D3CULL, 
            0xE6C5490DE371D7EEULL, 0x434796A8EF40522FULL, 0x5601C9BB8932050EULL, 0xC3699BBA24B4146BULL, 
            0x26650619DD5D24D5ULL, 0x8A2E7D9D2A6B8FC6ULL, 0x3D2D42D2491CDA36ULL, 0x59E6A34CD9AA0056ULL, 
            0x76E8FC6B235C4A15ULL, 0x13A4928062777996ULL, 0x675D79B34762966FULL, 0xAA540F705BA7D827ULL, 
            0x825C314D56856E1BULL, 0xD1924F9AE779381EULL, 0xA93545BDE922D712ULL, 0xFB2167D82C020BF4ULL, 
            0xB6F75BCB1EDF7C45ULL, 0xBE5E42F3D089E98AULL, 0xC6B851FF53DC8438ULL, 0x70BFAD1227562CC0ULL
        },
        {
            0x0E8F1CCDF7F03D14ULL, 0x1C6CD2BA34E7D202ULL, 0xF8D264433A168923ULL, 0x64268632F25461DCULL, 
            0xF45D59B8FF91F18EULL, 0x20C791962733D4D6ULL, 0x50D8DF22D6C92454ULL, 0x9AE78C0D2222B2ACULL, 
            0x8B3ECDA390720534ULL, 0xC068B12B853F0E38ULL, 0x1B6896AB4B12FCADULL, 0x140860F28B9B28A5ULL, 
            0x3B7DF1AD59B39FBFULL, 0x62C26BB97B455B70ULL, 0xF4D168BFA604C712ULL, 0x5FD736DAC869D2B6ULL, 
            0x638DB7C6FCF0EE75ULL, 0xD8DBAA948128E578ULL, 0x17FD5576F7EBCDD8ULL, 0x70CC9905593F9D01ULL, 
            0x71EB60A8CCA43814ULL, 0x2F56D1EEF97C9CABULL, 0x43C32276674EC823ULL, 0x769CAC3C7918F0DFULL, 
            0x3EF10448ECEBB64FULL, 0xDEA95DC01EBBD470ULL, 0x58A669E4480D37A4ULL, 0x5670B5E750576345ULL, 
            0x2FD34213F66EFC7AULL, 0xD4068C04C1C9C4B3ULL, 0x055B70A7655F83D0ULL, 0xE8E3CE90085D9973ULL
        },
        {
            0x109C28E323F0452DULL, 0x27FEBC4FACE57C98ULL, 0x059A2A6D0FFD54F4ULL, 0x40201D26FA757BA1ULL, 
            0xE2F917D9346BB773ULL, 0x34E510A20E488A19ULL, 0xB5189EA8ED37B805ULL, 0x47476874DD1C31DFULL, 
            0xCAEEED148F853F09ULL, 0x572AF4CA44CA02D1ULL, 0xD0564B088FF313E7ULL, 0xE676D151D6BE4CF7ULL, 
            0x880D0E8CE2FFFE9CULL, 0x909B2789467B7746ULL, 0xED6DE40B2D69DEA8ULL, 0x82ABF5E0552C9872ULL, 
            0x6083FE7B81D0723BULL, 0x5400EC4F7383A9E6ULL, 0xFB2B26726931542FULL, 0xE7FBE0CD0F5A0A44ULL, 
            0x6926B1F26477E1BAULL, 0xFADF1B7A67C73EAFULL, 0x9A6D6A8C99D4E8A8ULL, 0x5EA02264E9EA9E9BULL, 
            0x1E9D884C41C233B7ULL, 0x2CE0A96E5D38446FULL, 0x662CABA6AEC6048EULL, 0x890B103B8FB70D27ULL, 
            0x8312A80D1C37A0BAULL, 0x36415787EB22ADE8ULL, 0xA8FDB40A66FB3473ULL, 0xC05CFC401346425FULL
        },
        {
            0x360F4BDB91DF5B92ULL, 0xD15774EF415FE5E2ULL, 0x0A78FDA3EA830CCEULL, 0x98EBE3216F4CA4A8ULL, 
            0x87E3E3B147A4E5D1ULL, 0x12A220C8D56ECD2CULL, 0xF0C112C62A35CC60ULL, 0x28FEB903DA861DD6ULL, 
            0x38CB4FAF628E2BE8ULL, 0x92DEBD78CE8C1D08ULL, 0x023029DD5B04547FULL, 0xA9A2B3244569DB19ULL, 
            0x76B1E2B420EF0A57ULL, 0x756DE44B39DC0763ULL, 0xAB3298448E104DF5ULL, 0x4FE4C5B3C09E4E3CULL, 
            0xA46398B0A5E5D1F8ULL, 0xC8A7969822C5FB87ULL, 0x64AB8F28AEC2B47FULL, 0xDDA793E328B63CA8ULL, 
            0x42F17EAF1ADFF5FCULL, 0xABFA1C2EFADB4F99ULL, 0x47ABE9EB40D45ED8ULL, 0x7C4A4B1C9FD88E62ULL, 
            0x78EFD747C63C44C0ULL, 0x8C38461C0E8619D6ULL, 0xD5924425703E9D4EULL, 0x6620092E073D77CDULL, 
            0xD2F7DCDD31C689BDULL, 0x0FC9076441D9E500ULL, 0x8770CCBEC896E765ULL, 0x4DD8A3998EFD2DE1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseFConstants = {
    0x6BBD836DE9A228E8ULL,
    0x7704E32CBE8C9EB3ULL,
    0x9D7B1E156FF91225ULL,
    0x6BBD836DE9A228E8ULL,
    0x7704E32CBE8C9EB3ULL,
    0x9D7B1E156FF91225ULL,
    0x13ABD400A8A21CE0ULL,
    0x9185F273FFFE27A4ULL,
    0xA8,
    0xA0,
    0x3D,
    0xB8,
    0x26,
    0xF3,
    0x9B,
    0x7C
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseGSalts = {
    {
        {
            0xE211E1F2C10FF3CEULL, 0x8E22DBD862EB6C74ULL, 0xAE857A3F7531C0EEULL, 0xA2BDDBB353DAD5FBULL, 
            0xAE4B7682710DADF9ULL, 0x2D6561FF54D8B8D7ULL, 0xB5A6F004CAC4056CULL, 0x4490C250C7A0F47FULL, 
            0xF8186D2341ABDF93ULL, 0x12E60E5BFCD33CDBULL, 0xE12EFECCF9D3EC3CULL, 0x366060666DC0F4F1ULL, 
            0x4D9D7D0A4012C048ULL, 0x8FB48098531C924BULL, 0x6715F7B09103E53EULL, 0xB0866B18F0338B80ULL, 
            0xE8C9014C814F92ACULL, 0x8E0F7D9F7E38B2EBULL, 0x9BB8BB607774ADE9ULL, 0x6CE3FF0F0FD7CFE0ULL, 
            0xE79722C1CFC4FBE8ULL, 0x84E34AFF676DFBF3ULL, 0x572DCFAAD7455EAFULL, 0x363107E469F1B5D6ULL, 
            0x8A5D25705B204440ULL, 0x6EA53BF700D4F505ULL, 0x734CF626CDA65823ULL, 0x584367D6E5AD11EFULL, 
            0x2F1354F5AA1242FEULL, 0xB32E02B657F2D4F4ULL, 0x17B0A3FCDE54BF40ULL, 0x1226FD7F0E7C8E4DULL
        },
        {
            0xD6324222E6371222ULL, 0x20E12F508D285A21ULL, 0x15CFA467FCA0B73AULL, 0xF343C06B777F0AA3ULL, 
            0xC30BA914E86564A7ULL, 0x8C5E5ACC9E9E574DULL, 0xCDF5BE7A711E14D0ULL, 0x024CA5792D58BD77ULL, 
            0x88AE824F39AF3699ULL, 0xE6D340E778D220B7ULL, 0xC2BD9D448821C83CULL, 0x01A1D0D79B24FD33ULL, 
            0x0A2FC828A569A06FULL, 0xA71978ACA20F5A5FULL, 0x92281BD9D5117568ULL, 0xA0E1A03BEA684D83ULL, 
            0x2CB3638B71BAF5E2ULL, 0xAEC1C5A7B2F2493FULL, 0xF7316D65E3D538C4ULL, 0xA8836A7DE68AC056ULL, 
            0x5933A7B7090438B2ULL, 0x1CE53F069F4004C7ULL, 0x1D8B1CDBB59C5160ULL, 0xAEEB2FA95E63824CULL, 
            0x173A4CDBC17BECECULL, 0xC44CBE6B63821D62ULL, 0x0BBAB0A9F21FD8B0ULL, 0x7DC8B3C6A01C1CC3ULL, 
            0xF87F25229AFACAA9ULL, 0xDE4F39A8798F2436ULL, 0xE5A27ED99A69105EULL, 0x594CA4F3B3CF56F8ULL
        },
        {
            0x0D565D39564DF1B4ULL, 0x8D2773515ED68560ULL, 0x013941FF9E73C65DULL, 0xBC210573522949CDULL, 
            0x75F11F49BEA133AAULL, 0x70224E97D32A3EB3ULL, 0xE5626532DC35FAFAULL, 0x1CAC3CF4BEFDA2B7ULL, 
            0x7FA2DFF1BC75CB86ULL, 0x79BAFD0344BF5A43ULL, 0x9624FFCE2688151AULL, 0x00A6CEA0A5FC878DULL, 
            0x3EC5A4DDD9CFCAE3ULL, 0x5487DA52FB1FEF31ULL, 0x9DF95AC6733CCE56ULL, 0x9224AC3DBA4C4805ULL, 
            0x51D348C78745C2B3ULL, 0x4ABB18C770FB2043ULL, 0x30C26A9B4CD94912ULL, 0x237A0F3974AD4687ULL, 
            0xBBA48D690272C938ULL, 0xE8E2F096155B383AULL, 0x19631EAA05DF5263ULL, 0x9F2AC1F4B0DDD481ULL, 
            0x53431051502B2F15ULL, 0x71BC4ABD6D8DAC0FULL, 0xC7873CCC5E13EDE4ULL, 0x3D2D3D383FFEF007ULL, 
            0xA99946F170942D04ULL, 0x4B917B483752DE79ULL, 0x2066A930AC0247A4ULL, 0xDEA0F83802F8B6B2ULL
        },
        {
            0x4422B68ECD62588CULL, 0x6C075612E4E8CE66ULL, 0xF58CCCF8A6DBB537ULL, 0x5902F98D5A0B5ED5ULL, 
            0x8D98A2AA5D2C1F77ULL, 0x44F7A881AC4CA57CULL, 0xB2C85256AC139410ULL, 0x35EB524E7E96DBF3ULL, 
            0x54A3607951B4DB99ULL, 0xAB715D523F0F73C2ULL, 0x9732F9377A583F9EULL, 0x4B56D3F3EDCD8A27ULL, 
            0x23A2FBD3C8D55C1BULL, 0xEA254789B25A4FC0ULL, 0xA662C6CE1DD8D06AULL, 0x28D73DE8BDDF5CD0ULL, 
            0xE7BAC5CFDE78CAF0ULL, 0xA6B23082A454A52CULL, 0x63C262AE685ABB25ULL, 0x895C528EB37EF770ULL, 
            0x59355D0B0ABE5A47ULL, 0xD8E1EF974F14B46DULL, 0x14D3A882451C95FAULL, 0x8468D279D89D76B0ULL, 
            0x08F93012D85BCF48ULL, 0x099741B4EF85B90AULL, 0xACBC6853E16601F8ULL, 0x7BF1F6A21C50EAC0ULL, 
            0x1AB04BA36CAAE2D5ULL, 0x89C9BE4D8E512098ULL, 0x476690AF19A9480BULL, 0x7E4EF3C7A70EFF9BULL
        },
        {
            0x189267F605C5C6A7ULL, 0x666D8394F3DC3259ULL, 0x0EF33E54AD657674ULL, 0xF6BFDF193BC76918ULL, 
            0x9B1057F036E87ADCULL, 0x75509BDF8519ADF2ULL, 0x9B47307237F02C33ULL, 0x006F6265AB64AFDAULL, 
            0xF9D479F8185C0477ULL, 0x887BE99C30FE7C3BULL, 0x60F9C019E83A2960ULL, 0xF078012DE9533212ULL, 
            0x2238B027590BAAB6ULL, 0x044441D8C91C99DCULL, 0xC540BA8841D01BB6ULL, 0xFA236C49F6816C36ULL, 
            0xFA7488E97BFFBA02ULL, 0x64CFFC3C4CC631BCULL, 0xB4C646563D375B3BULL, 0xA91A5CA8AF6E224BULL, 
            0x3E7F49FBF6C245F1ULL, 0x256FCAEB9919E9C9ULL, 0xE43463047A7D1320ULL, 0x4E09BC5434B44561ULL, 
            0x177C08CAB06B84FCULL, 0xABCF9D9DA86FEDEDULL, 0x66B1D8813F72A06DULL, 0xEC1E1ADEDF8934DFULL, 
            0x2A31198E76FC4D16ULL, 0x1081861135E73CE1ULL, 0x15699E980499CB34ULL, 0xBA534D12528E6B96ULL
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
            0x474C2EC7A49E5BBEULL, 0x96485641FB7A2CA9ULL, 0x1D5D8BEAFDAA8C5AULL, 0x09E96D5D6D5AE6E1ULL, 
            0x73490287C713C30AULL, 0xA1DFEDB3FAA131BAULL, 0xA8F686D166EA334DULL, 0x312B7FD750CF6973ULL, 
            0x3A9F92D8B0970D75ULL, 0x8BFD133177B52A98ULL, 0x4F58A31112E48884ULL, 0x3FD810A759825A62ULL, 
            0x3FDC6904211F3537ULL, 0xF2EE36528510300EULL, 0xB5D17363CB7FD5C7ULL, 0x18936651EE2B0503ULL, 
            0xE7D797361D56624AULL, 0x7023C75F75062DABULL, 0x6C721D60FDD1502EULL, 0x05DFE20AD5448A95ULL, 
            0xD2F21654BE464FC3ULL, 0xFAEC25697FA46A73ULL, 0x9DCC67D94613168CULL, 0xFE98F683569FA4BFULL, 
            0xB1656BC41074C66BULL, 0x7E1468C1499444FCULL, 0x803373B32C3B474EULL, 0x514341F8ACA256E8ULL, 
            0x681004AB2531BBD6ULL, 0x2941487A5EE52297ULL, 0xCA2E6D0E581D58C9ULL, 0x2BBE098A8183A683ULL
        },
        {
            0x75D468FF00F03BC5ULL, 0x1F4B29DABA7D681EULL, 0x174B877AD1F31914ULL, 0xD28D89F08BA32075ULL, 
            0x154531D1029F0A68ULL, 0x8DDFC342FDAEE5EAULL, 0x9214613E4F84D343ULL, 0x8483EB6EF604F09BULL, 
            0xFFAA06D8299D0EE5ULL, 0x1D78DCA7B182E94FULL, 0xBF8CC2A9634E3826ULL, 0x35DC4C9761E59751ULL, 
            0x12406D168DAC7E56ULL, 0xC7709D30E1BAAEE8ULL, 0x768CF931D9B908E6ULL, 0xF684F29B48ACF273ULL, 
            0xBEFFF6EBBCA0ABF1ULL, 0x9ADF612B8E7D9072ULL, 0x01BB46FF9F559E8DULL, 0x2D4A1BC8EDABE21BULL, 
            0x162A1538319C2036ULL, 0x26904C75926FA444ULL, 0x380AA04E9193C846ULL, 0x946EC2E1F1B4FFCCULL, 
            0x2F44B015F3ECABA3ULL, 0x5F7CDDB666516D54ULL, 0x152C8EC366CA87F0ULL, 0x985242B2A91FE880ULL, 
            0xC590AEFEEA73097EULL, 0x5735EAFE53D77A7AULL, 0xA2F495BD7473718AULL, 0x362F8CD79154EC52ULL
        },
        {
            0x497ADACFD2A9BC77ULL, 0x6E0E2886CF47B559ULL, 0x392186D8571C01B2ULL, 0xD5EB869A78F8706BULL, 
            0x2DCE8D286ACE0FC3ULL, 0x5825CD980CB8D0C0ULL, 0x57FB56BCB0487FAEULL, 0x62EECE81BC856333ULL, 
            0x11BEA8DEE2F09BB7ULL, 0x076AB0C4576E9D6AULL, 0x8B763FCAA881FD97ULL, 0x24EB8A5C768A5753ULL, 
            0xC0651051CF6D8CB4ULL, 0x0F01AA4092BAF87AULL, 0x1D0F3352BAF84550ULL, 0x444F904B174155C6ULL, 
            0x36B4FE205F81B8E2ULL, 0x13A6B9485142CFB7ULL, 0x849459935F92CDCCULL, 0xF6205F573F3F15B0ULL, 
            0x2141E7ED0B502690ULL, 0x545B4CFBEAC82875ULL, 0x4CBED774DA000CDCULL, 0xED8DE70B0285C0A2ULL, 
            0xFBED44C261244512ULL, 0x810B8BD1CE6327BCULL, 0x37A681BEFA69AF86ULL, 0x920BEF4995D17BB1ULL, 
            0x189A1E444A167462ULL, 0x11956FD0289D450EULL, 0x2D5A2664026CF76EULL, 0x7B0408BC0D963A9EULL
        },
        {
            0x5EF242321FA9FD48ULL, 0xF957E97CEF5850D0ULL, 0xF6E0ABA69D311BF3ULL, 0xAF941DFCA1D65138ULL, 
            0xA0E582545AD4B9F4ULL, 0x28D68AFC900D7359ULL, 0xE75901DAC660D9A2ULL, 0x8A1CCCA9D6E362A3ULL, 
            0x45D71C30EB2E3455ULL, 0x11E9956695347C70ULL, 0xA4F9AB1A272DDE45ULL, 0xDB1A3399AA3B386AULL, 
            0x12387314D67133F9ULL, 0x882083DEA8A93D26ULL, 0x11D550282CB933B9ULL, 0x16F7540F455536B6ULL, 
            0x198C215A0594126AULL, 0x54C9B4F95CF2EAD2ULL, 0x2C5E95AD2E872D83ULL, 0x3499FDFCA2F29C80ULL, 
            0x40EFC04E3F8B0CD2ULL, 0xC02E0E135042E175ULL, 0xBEA084A00440903EULL, 0x098831C704C6AD58ULL, 
            0x1FCD3BECAB33A19FULL, 0xA0F4834ED00AA9ECULL, 0x691D9C175A325748ULL, 0x7CD9B67E3AEBE673ULL, 
            0xBFA88A41083DCB02ULL, 0x7003D58584E886ACULL, 0x26F6AA9EDD21D188ULL, 0x6959C965E8F623B3ULL
        },
        {
            0x1C9F7E1908E7D397ULL, 0x88E203B59CDF6219ULL, 0x5B0A6C79E49032A1ULL, 0x15FF590C395D9E57ULL, 
            0x1B564F76B3F2D8BCULL, 0xDAB59F2B21021A15ULL, 0x97D4B0F55EFF2658ULL, 0x311E67F9DA4A848FULL, 
            0x49621445DD6C373CULL, 0xBF75A3F9C75E5CAFULL, 0xD131F38246C1A207ULL, 0xE4FFBDDBDB8F2E3AULL, 
            0x6A3FB31E060C49C1ULL, 0xF84A7515094B8CE8ULL, 0xAD3B37FC6C6FE779ULL, 0xBA6E2225A44EAFDFULL, 
            0x1FA7FE6CBB197C45ULL, 0x5DDACB8794D9C51CULL, 0xD6C78EAC7DC14897ULL, 0x18D1BA603B84B27DULL, 
            0xC162FC5CD178F31DULL, 0x58BB923C818C0722ULL, 0x6F5A2C24063E7AAFULL, 0x7FC1011CB04B3D96ULL, 
            0xB716B6686C87239CULL, 0x8C34DAA561D649FEULL, 0xBBCC4D9221515760ULL, 0x006774E187025778ULL, 
            0xEC312DC321055FD9ULL, 0x18B936375B49B405ULL, 0xED812C3C9D4E53A7ULL, 0x3F4F2DD5CB37D834ULL
        },
        {
            0x9B29F26A6A545354ULL, 0xDC720DABCD6549ECULL, 0x080A53F228BA1474ULL, 0x7F6F8898CBDEBEA0ULL, 
            0xDB9CA32441DAB671ULL, 0xCEBD54DE3ACF532CULL, 0x823D3577BAB545E1ULL, 0x03011FAA5D8F6CF3ULL, 
            0x072C0DBB9D459A40ULL, 0x057C4E18996BBFFCULL, 0x5ECFD0A30096372FULL, 0x151270B493864596ULL, 
            0x736C9892F60CF304ULL, 0x8BA486900526F236ULL, 0xE00988AD401CD12AULL, 0xE5F08A8A65049707ULL, 
            0xB5D79447F91A6046ULL, 0x841D5EE9AE34E563ULL, 0x50EAC097A0C62B5BULL, 0x107C22EEEAEB6BFDULL, 
            0xE2C1067687CA68FEULL, 0x2C98507B07A6176AULL, 0x8DA12C1E36D17781ULL, 0xD9B49445C251128BULL, 
            0x0DE0D5B13178FECEULL, 0x8B6A41F213243435ULL, 0x8E9D60AD970497B6ULL, 0x46757605457800ABULL, 
            0xD87B3122DF326A84ULL, 0x568AEC0DAE666DECULL, 0x887F7F81638A06B2ULL, 0x5AFF280DB9A5A197ULL
        }
    },
    {
        {
            0x3C2C00759FEDFAF9ULL, 0xE3EFEE81A867ACDAULL, 0x0E173C6E73777F43ULL, 0x3F42DE5873697178ULL, 
            0x5FA83BDA5B9BCCB9ULL, 0xEE7E42E10FA66492ULL, 0x7D2A570C21DEB0F1ULL, 0xF3683E681BC0E8CFULL, 
            0x2BCD4BBD07EB086BULL, 0xD8C4017EE58CDD52ULL, 0x1B9A930B0FFD1E29ULL, 0x55284BF231E565F1ULL, 
            0x773E86C48EBA38DEULL, 0x707530F24CB56CC5ULL, 0x5A0F52D5E0F8CA13ULL, 0xB57D1CC2B88CA75AULL, 
            0xB6204906178F3618ULL, 0x94A50DCA12FD1DBDULL, 0xECCDF3C53384BD36ULL, 0x372953FB50BAF20AULL, 
            0x968BCA30B68D1E31ULL, 0xAC9F19AF0FD82E03ULL, 0xC1A24BA17416461AULL, 0xA8B95A872379386CULL, 
            0xB6940D7B086D5ADAULL, 0x9C65CC88E64E4765ULL, 0x60CBB7D6AB590533ULL, 0x8B9D544442E466ABULL, 
            0x35C503ACFEA2FB9AULL, 0xE87B47D474EE42C4ULL, 0x0A216C9DCADD02CEULL, 0x7FBBA214724F1CBAULL
        },
        {
            0x8A6EC9E9F8555B18ULL, 0xECE679C282778D6DULL, 0xBB473BFD2994EBA3ULL, 0xA6516E459071844FULL, 
            0x68461AECA554A232ULL, 0x311B773C496C6EFBULL, 0x19B4DF3A41D3D0D7ULL, 0x81CC1187F0AD1B35ULL, 
            0x8EFB34127C91F504ULL, 0xFB6EC45E355A1169ULL, 0x66EE19C2365E5FEEULL, 0x488A3AB172E68DB2ULL, 
            0xB3473304A919C86BULL, 0xEF30C91457321DC4ULL, 0xCAD7B1338C85DCBFULL, 0x404082D15570C346ULL, 
            0x1CA53AF990DA0CEFULL, 0xCDB8D713044DF451ULL, 0xBA1E03DEA44E1194ULL, 0xE925BC2CE7AEBB53ULL, 
            0x8F2FCD5FC67FB08DULL, 0xB7BD279B536B6B15ULL, 0xCB3D864C80C4BB4FULL, 0xB03A3291BAEB26E1ULL, 
            0xF14528D6586B71E7ULL, 0x187ABB231FF9871AULL, 0x4715F92FB10BE48AULL, 0x7192F6B30FC79189ULL, 
            0xF68FD11D63ECDAFEULL, 0x8F74273CECB16A89ULL, 0x0AB099650E49DBB8ULL, 0x4311D5F40EF71509ULL
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
            0x8F54C1C74B224AFBULL, 0xA45139AD92464DE8ULL, 0xBECC9127DCAC7191ULL, 0xECAC9330A3FF424FULL, 
            0x8B5A1B62357635EAULL, 0x87C2772AA480A918ULL, 0x8EECC95575122FC3ULL, 0x606F4588AEDE376DULL, 
            0x9A152D7435999538ULL, 0xB263300AB2671D9FULL, 0x46AEDBEE013C504FULL, 0x7A59A290B05CE83DULL, 
            0x620FA28445509CFAULL, 0x298FB408EB646FB3ULL, 0x13F1FF0DC1F95A91ULL, 0x16D2E1E405C89833ULL, 
            0xC788C9B123425BE3ULL, 0x1B9100CF63433E57ULL, 0x15E6E2F9C00EEA41ULL, 0x66671C8EC704A378ULL, 
            0xA5E316B0D785CAEEULL, 0x93AF2BDC2DBC594DULL, 0x06BEA79397D4BEC3ULL, 0x32548DC2E3502422ULL, 
            0x261ABB7A2EEADE31ULL, 0x90A03BE5A4719581ULL, 0xB20BF04A3EE19AB4ULL, 0x4C318EE038F456B0ULL, 
            0xB479DECDE7447B91ULL, 0x4D77B2653143C47BULL, 0xA1CB51DCAD9CCB11ULL, 0x4001432716F1F1BFULL
        },
        {
            0x1F02124A1DEEABAEULL, 0x89EDD066DC60CED4ULL, 0x1155D8A42D6A9706ULL, 0x5FC4AEAAE0B911F9ULL, 
            0x66CE67FC791B8390ULL, 0x019DB6FF0E991DCCULL, 0x159B7298E4AEB4C7ULL, 0x9744DD997BE1E4ECULL, 
            0x2D4EB9C62696EDB7ULL, 0xAD489AA975CDD449ULL, 0x14372AE062BCC788ULL, 0x470D9EC7EC4AE935ULL, 
            0x3944F096CE217126ULL, 0xB04E1836DDF57883ULL, 0x4EC446D6AD1D5355ULL, 0xBFFAF43368126835ULL, 
            0xF692E0381474BD56ULL, 0xBCBF1CF521A50AABULL, 0x77225B96CA53FFB8ULL, 0xE560CDBF8B1F6261ULL, 
            0x920F2CC772F4250CULL, 0xB8A9AAE2E8F52FFDULL, 0x2DFF702E47E941E7ULL, 0x779E7279FA32964FULL, 
            0x2D99D1443EC62B87ULL, 0xBDF012117D8EAA71ULL, 0x4A45011E924E7906ULL, 0x8F8BD2B40F3766D0ULL, 
            0xCAD10270681D037FULL, 0xB62E6AF522CA7051ULL, 0x410BE240AFD47526ULL, 0x7364842A64337A2AULL
        },
        {
            0x5F302B54BEC5E46DULL, 0x3DD0B81EE9B58B5FULL, 0x29FC95C6AB430CE7ULL, 0xD859E708BC0887ABULL, 
            0x8EBDC6413C848FBAULL, 0xC7B3C61EB528B17DULL, 0x5B36DB689ABD7564ULL, 0xE684BDE5DE579518ULL, 
            0x8671DB1E32535412ULL, 0xB3C4ABC48D65690EULL, 0x9BA96CDC4A9D2B61ULL, 0x8EB80CC4A368BE4FULL, 
            0xE1C259C2E42AAE52ULL, 0xC1366675CA1B31B1ULL, 0x09680B0B82E04007ULL, 0x4ED5C2BAFA8B0934ULL, 
            0xD1A9956258CD4600ULL, 0x417851BB44F516EDULL, 0x54122BD4F87EB21DULL, 0xD417B0DFABED2097ULL, 
            0x5824989CB6DB24C6ULL, 0xB968508800C05AE1ULL, 0x651E1E3BB3BCEEF6ULL, 0x6E8476A0BF1C218DULL, 
            0xC36172FD06725BECULL, 0xE5DED32D2F8F566AULL, 0x68D9CFC50FD1A751ULL, 0x0C0BA65672BB03B7ULL, 
            0xD126FE3091C481D4ULL, 0x974F9422CAAFCFADULL, 0x08C1773FA0DBAF56ULL, 0xC4A780728EE90644ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseGConstants = {
    0x42ADA109F91DE556ULL,
    0x64F374ED5AE48CE6ULL,
    0xCD0FFCD008365231ULL,
    0x42ADA109F91DE556ULL,
    0x64F374ED5AE48CE6ULL,
    0xCD0FFCD008365231ULL,
    0x5B5DF1FD1E5D6253ULL,
    0x8404F50856A2F6B2ULL,
    0x01,
    0x28,
    0x57,
    0x19,
    0x34,
    0x4B,
    0x28,
    0xF2
};

const TwistDomainSaltSet TwistExpander_Miram::kPhaseHSalts = {
    {
        {
            0x4D4DA2ED131C7308ULL, 0x499A7016A235BADAULL, 0x35CA849077E93092ULL, 0xBA9954C23F1AD2A3ULL, 
            0x507D6FE2BDCEEBC2ULL, 0xB7DC4FFB8B0F9351ULL, 0x599134518402CEDFULL, 0x2E06160AB433100FULL, 
            0xB4FAA6FF7E7465ACULL, 0x909BCC7B72FEBE42ULL, 0x0704C1B6EA6778A9ULL, 0x752985F8EA0A0771ULL, 
            0xF93899445B219306ULL, 0x87B6509662046DF6ULL, 0x16422E91A0267795ULL, 0xC3C67797DF2CD7DDULL, 
            0xE4B92F64F53EDFC6ULL, 0xD299E786B6485E58ULL, 0xFA088683928BCFC0ULL, 0x776F3120C6E90AB5ULL, 
            0x7C5BEDFFA7BEB2A3ULL, 0x8D16935B9CA460A6ULL, 0xE33C8B26AC353D81ULL, 0x6CDF46A7827A7428ULL, 
            0xCC733433DB67A4F5ULL, 0x4FDD3CE2D8988442ULL, 0x648BA125374A6F7CULL, 0x1BB05BB6653EDA94ULL, 
            0x44B9A1DEF37E9D40ULL, 0xAC6FCB416B1AB9B4ULL, 0x7848B65F0965E7AAULL, 0xF3D1BC160FB7374EULL
        },
        {
            0xC0DB590BC540BC86ULL, 0x5D0AAD963A6119AFULL, 0xC7544CE427DDF584ULL, 0x0BECC0AF680AF3AFULL, 
            0x0CEEB225E899ADBCULL, 0xCABC0E0B94B63568ULL, 0xC66AFE20100BAA49ULL, 0x673E8C7649EFD87BULL, 
            0x83D64B8A0119D0EAULL, 0xAB729B8336BB8612ULL, 0x7303A621D1EA99F2ULL, 0xEC925E7808B3E095ULL, 
            0xD2E5BFD9FB1ED231ULL, 0x5765DEFD29962F36ULL, 0x0024F267FC1FFEE0ULL, 0x3F8AFF8471FDF13FULL, 
            0xD3D8EE4F41132215ULL, 0xAC27D015E6A1C2D0ULL, 0xB547631EAA43FE40ULL, 0x3597127062CB4A70ULL, 
            0x9DFD29FF4868F97AULL, 0x94A1293514F4F439ULL, 0x85B044D71BC10503ULL, 0x9C9851A9F5646DCFULL, 
            0x92FB0F68926B5C2CULL, 0x5AC1614FFC7F8AD5ULL, 0x4C42CC195587A8ECULL, 0xC7CFEA72978B4CC4ULL, 
            0x1B850EF19F7F7BDCULL, 0x74ABABCDE3FCEC52ULL, 0x13DC6F0D26AB8E87ULL, 0x35DBEAE6324344E7ULL
        },
        {
            0xD36F32254F91360DULL, 0x886EFAD3D69703D6ULL, 0xECDA5424D68BBE34ULL, 0x315538BD8E3CE688ULL, 
            0x4CD43A26813B9F38ULL, 0x800649919E8EA152ULL, 0xEC3AA77DB68B51EEULL, 0x11DCAB20761C4394ULL, 
            0x66F34E52F6478C62ULL, 0x14E103097A9786DFULL, 0x2D1E2D761CF3471CULL, 0xA99294219C86EE26ULL, 
            0x7D63E1AF0F7DF4D0ULL, 0xFDF364B0496E4EBEULL, 0x9566704536797DC7ULL, 0x416F9878E6F7F19AULL, 
            0x1B99132F576B5474ULL, 0x6D98E4A06C392288ULL, 0xE9D117D29CB8A116ULL, 0x4670645875B5E6A6ULL, 
            0x12681A9C15F82A9DULL, 0xD5F6C131959EB0DCULL, 0xDFFDEDEF827B7B49ULL, 0x67E5A292E9D39586ULL, 
            0xD19356AC6D11F964ULL, 0x55C4C822DD574312ULL, 0xDFF23CBB3867ACF7ULL, 0x008613D04DDA36F7ULL, 
            0xD27EE8539A28425DULL, 0x4A4B6E3AEB31031AULL, 0x03A6618AE75EB870ULL, 0xAAEC3EE4C44E709FULL
        },
        {
            0x428558331A59F1D7ULL, 0x6BD86CDA033495AAULL, 0x45B165B722A91CB6ULL, 0xF942E9EA171DCD07ULL, 
            0x97974D7AB176DFB0ULL, 0x0BCF42E2DE17DE83ULL, 0x729979758670D38EULL, 0xE929AFCE5C30547BULL, 
            0xD481EC356C6AC7C0ULL, 0x9A9C0FEB8A5BFB9CULL, 0x0516D863456135CDULL, 0xFDBA79516296B648ULL, 
            0x9863F2FFC061CE6EULL, 0x9E040D90A2E73212ULL, 0x653326160E0ED84AULL, 0x8F896834EDA5193CULL, 
            0x1C787681B5E77B01ULL, 0xFC972FAA63164A42ULL, 0x5CE2F8F559035768ULL, 0xA5A951F221AC1099ULL, 
            0x1D9C7564FF8E2468ULL, 0xC9EBE726F3457AEDULL, 0x5C06B34D38BE4B86ULL, 0xCED5C42F9AFBC794ULL, 
            0x8C5AF5D633264A91ULL, 0x97A9276D75EBA2BEULL, 0x9AD3910E6D9ACA44ULL, 0x77990C7CA6AE88CCULL, 
            0x7069D2DCD4C25CC7ULL, 0x28F5BB63541EB0AFULL, 0xA3837BDB6D8879D1ULL, 0x62FADEE97FD6977DULL
        },
        {
            0x02B11AB210669A6FULL, 0xB1C342CB066E3FF7ULL, 0xE7FDE812A0B2EAC4ULL, 0x9A3BCE6F8160C96DULL, 
            0x1CEF397BF6B5E117ULL, 0x2FCEEFC73E0D8E17ULL, 0xFA28F1536A77D20BULL, 0x7F9558458CA1F011ULL, 
            0x05DCF07A8F014B7BULL, 0xD29268117C036135ULL, 0xFDD2071874E1E023ULL, 0xE8ABC634075F9022ULL, 
            0xB0C76A5B6FBA6470ULL, 0x62F58DAFA8CFF4B3ULL, 0xAF0235E8656C0826ULL, 0x97BD036CF2572050ULL, 
            0xC778B4A7A890CCFCULL, 0xB3B822D4E4388143ULL, 0x5A5D9404A502FA8AULL, 0x63427B470A937387ULL, 
            0x41B7BA06E4B1DBADULL, 0xAD1C23CB11166AD3ULL, 0x439FA9847497D6B0ULL, 0x3E14503AAFB985D1ULL, 
            0xACD3BA327E6D88FFULL, 0xB6F2C77F885DC432ULL, 0x6591D73F17B2E7ECULL, 0xA5787AE1389F1C51ULL, 
            0xB860A9CD4A399783ULL, 0x8E51FEF0038BC593ULL, 0x833512BFB5BA0301ULL, 0xF9A8FEA9721B785EULL
        },
        {
            0xBB8D94BB8D7AD69EULL, 0x8B3278623BE3730DULL, 0xC8C717B077D70AEFULL, 0x5EBF4F3FDD27E549ULL, 
            0x4B58F685AEE35A56ULL, 0x40411C62BD76DA1BULL, 0x260B85A6292DE7FEULL, 0x1306C5A1B31F49F2ULL, 
            0x58934FFF7BFC3FFDULL, 0xB7B311F494F46F88ULL, 0xAA457004DAE33430ULL, 0x0D66B4E5EE416D4CULL, 
            0xEFB376A9FCE108F4ULL, 0xB72DF6B3AAAF3525ULL, 0x4368FEFF23F4C974ULL, 0x261D3C98DA0EDF34ULL, 
            0xB3A878C9FBAB3003ULL, 0x3FB6BD7677AA5FF7ULL, 0x1C456412EBB29676ULL, 0x09AC74D6572462E0ULL, 
            0x6AA5815B8717BEE1ULL, 0x1F0C96F82132C004ULL, 0x5C5368BEC0B7AF01ULL, 0xD192260DE728CF60ULL, 
            0x51A3B7AC56F087BBULL, 0xDF84D569841321BBULL, 0x7C9FE9EFC732CA88ULL, 0x46F938BB05885B96ULL, 
            0x9241C664E940F741ULL, 0x5E782273AE2DB98AULL, 0x8E76C248FBF38AB8ULL, 0xFBD2B4A8D19168E0ULL
        }
    },
    {
        {
            0x3A5B43587879ECD2ULL, 0xEE6EE2A5A488D812ULL, 0x6F2588CE86E2F219ULL, 0x96E0AA56742DBA42ULL, 
            0xB3E90B651AA57E2AULL, 0x024F9E1DFA95C57AULL, 0x726412B3B3CDF80FULL, 0xB335FA22522A491FULL, 
            0x5E9CCE5D017508C0ULL, 0xDCCBF4A3D29A22E4ULL, 0x4334DC6052EEEEDBULL, 0xFCDC1FFB4147369EULL, 
            0x4F20693437E64EE4ULL, 0x87124EA597F29420ULL, 0xDAEF6E193640D505ULL, 0xC50253BC1C2F276EULL, 
            0xFAA4755D93539BF5ULL, 0x3E89F467A4336F44ULL, 0xECC0996F0125F738ULL, 0x4599A53FF1DD493BULL, 
            0xB7D38847644CFEA5ULL, 0x0534386442719E0BULL, 0xC143016EC8BFD815ULL, 0x0BE1AC672DA5EF42ULL, 
            0x94A7269ED5069E94ULL, 0xCF537E907FA83D88ULL, 0x4409942B7E4C69EBULL, 0xCF685440D98DDEEDULL, 
            0xFF6292B7DBD24F57ULL, 0x8A1DC9AD828435E9ULL, 0x2F071C0DCAC9E9AAULL, 0x8BBD702A3AC4B05EULL
        },
        {
            0xAE9B63233FC7A478ULL, 0xEAC2BED019E9B590ULL, 0x9AAF04CFCBF6DF2BULL, 0x6CE9FFC41D7C0C92ULL, 
            0xA5CC4EC9DFD4C052ULL, 0x7E5E1931985377B8ULL, 0xC4A6A30F74A4BA4FULL, 0x1CBDC186B1AE0D02ULL, 
            0x6F3EA26E883CDBEFULL, 0xE4CDB6DA7A62F0FBULL, 0x614E740DA1A8F667ULL, 0x0AB328EF32263893ULL, 
            0xBA62453A9504CC74ULL, 0x603BD86A5B9D1D0FULL, 0x89D3351DB65B47D5ULL, 0x8803FCC2EF647914ULL, 
            0x591F9D1A547D69F0ULL, 0xC55596899B488A46ULL, 0x1027A0B669EDBB74ULL, 0x8D67846E3EF5F3A3ULL, 
            0x15478019E7AB27E1ULL, 0x7EDDA1F23A72D6D2ULL, 0x3C3A582C03DF4171ULL, 0x8C84C63FA6D36885ULL, 
            0x8E219BE0D549CC3DULL, 0x9CA86461D54C5DB5ULL, 0x3F805E16A8B85458ULL, 0x51033A04B8760283ULL, 
            0x5C837D99BD45F555ULL, 0x750CBAA829D990CCULL, 0x780582777019A0FFULL, 0xF48C50A0642FD6E1ULL
        },
        {
            0x70D45E619A0CBBC4ULL, 0x5289F78334179387ULL, 0xB1B4EB2DFD783224ULL, 0x9A13903D97A190A8ULL, 
            0xB4C1D71D569D5090ULL, 0x90531C3123113DBBULL, 0xC3E17E906C42DE65ULL, 0x5A740589B3887580ULL, 
            0x664F74FE03B11889ULL, 0x161D27013E74E5B7ULL, 0xC7E3D007A7E61819ULL, 0xFFEC119C4FE59F4FULL, 
            0xDAAA6E6A69E253EBULL, 0x9A7E069DDE042220ULL, 0x33DB4BA4C405B6C4ULL, 0x6DD50B8E3A7DBDD5ULL, 
            0x096674DCF102565AULL, 0x0ADCE0494C8D7B88ULL, 0x3067E7934E9C0FE6ULL, 0xD43B973D28D323DCULL, 
            0x2D16F724C7A08630ULL, 0xBB21475B3C7D10FDULL, 0x6C6EFCFF814D369FULL, 0xF54D3B2BFB14B8D6ULL, 
            0x741D42EFF6F01CCBULL, 0xDF67B256D82F0A9BULL, 0x1511FC40B653ECFFULL, 0xA92741F73F273E0EULL, 
            0x3F8E071F7AA99C2AULL, 0xB066393F0EA47B64ULL, 0x9E317FE5FE8625A7ULL, 0x267EB3E704B55914ULL
        },
        {
            0xE633F760FF2C5636ULL, 0x3A5012C023C6AB8EULL, 0x07C086B8ECD76B29ULL, 0xF4DDA794534584DCULL, 
            0x76FAB9DBB4F28978ULL, 0x9AFD9BEF9284B5E7ULL, 0x5B60AA0C03CC537FULL, 0xF55C61EDB9B6D05CULL, 
            0xDC9E16A7028AF963ULL, 0x2ECE85D6F94CF09EULL, 0x58FEE1AF4630051DULL, 0x590B016F9A561A2CULL, 
            0x69A54043FB2666C0ULL, 0x6474C5E7457192F3ULL, 0x3DCC1A8263CCCF45ULL, 0xCD234DF53732F173ULL, 
            0x850B4E5CE668D46AULL, 0x2C52DC02309C15DAULL, 0x00F611215450CA88ULL, 0xC48677EFEA112312ULL, 
            0x48D3AF3437830910ULL, 0x7F494ABA33F0A4F2ULL, 0x6196FA7ADB6EBC39ULL, 0x12D4392D04416926ULL, 
            0x343861BD9BE9CFF4ULL, 0xD00C1916FBA07C51ULL, 0x90F00DC255A0B9FFULL, 0x89121B3242009D52ULL, 
            0x6EA0C5F652A60D1EULL, 0xC431BD6FDF0478F6ULL, 0x83E51C0AEF8D6D8DULL, 0x541C75AE29CEC3E6ULL
        },
        {
            0x327FFA22AA85BF51ULL, 0x5C5BC6EBF1EC4DEAULL, 0xCC9792ABB03F3E98ULL, 0xE89939E3AA8C8E23ULL, 
            0xA0BD0289E107AF11ULL, 0x70E329BD793A419BULL, 0x73127809E631E437ULL, 0xEC4B106028158A7BULL, 
            0xFBA57FDBECD6AE59ULL, 0xD479EDB57FD2F02EULL, 0xED9FD4C23FFA6418ULL, 0x6AACCFCC2A9B1BF5ULL, 
            0xE56EE59E79D0CF35ULL, 0x2CD17B1ED8407444ULL, 0x6A59D17816ACA74DULL, 0xB95A21136BAED9CEULL, 
            0x72218749C1871CDDULL, 0x361660B9EAD6B7A2ULL, 0xB85C92DA3C699E80ULL, 0x62408E13238A2E87ULL, 
            0xB35E1EF37DD2E85EULL, 0xDCF060F4E3D910CEULL, 0x90BBB84927C1F5EFULL, 0x477CFA3B9C07E5A9ULL, 
            0x858D863AB3E4B62DULL, 0xAF2F1C584E388A4CULL, 0x667B8BE1CFD6A107ULL, 0x470CDE0D4BCF85A3ULL, 
            0xFA0370F24528FF4FULL, 0xAC40D5862D75B403ULL, 0x75EF97CB293BC853ULL, 0xB15F4ED5F1B6FD83ULL
        },
        {
            0x9D8A1D9603A1B88CULL, 0xD516D010936D0CF3ULL, 0x72C949B4A14296A3ULL, 0x3D3760DCD240A344ULL, 
            0x5332F76A317460BCULL, 0x5E3974040D174B36ULL, 0xF26D2EADE27F40E6ULL, 0x763DCF38F6B9FD45ULL, 
            0x52E0D3683F1979AEULL, 0x3EA8E12EA26DB0DEULL, 0x16A37444307D3F52ULL, 0x95AB37D643158F82ULL, 
            0x5B21465487C69B9BULL, 0xC7B7FE82F3C977C2ULL, 0x7967ABFC07E741F8ULL, 0x1118F711B856DFEDULL, 
            0x19A1893894D33A72ULL, 0xD30375FC3DDD016FULL, 0xE473EDE5E8D4598BULL, 0x083526C804411B59ULL, 
            0x1B8CB0EBE1AF94FFULL, 0x4B0058DC00F25449ULL, 0x5DCC8F89A4E385E1ULL, 0x67F0A1FF31F0E7E8ULL, 
            0x37A9C66EF6B16559ULL, 0xC19558FEBC379C39ULL, 0xFE78012DD09622EDULL, 0x79FDC0E4AF15891EULL, 
            0xAE2973757945FEB1ULL, 0xF857B8E609D7FE07ULL, 0x93FD2A5B8FEC4C8FULL, 0xE3B0082707F45EEBULL
        }
    },
    {
        {
            0x0F66EDB83A3C8C8CULL, 0x4BFC679C8004DCC2ULL, 0xA97F55BDF3343372ULL, 0x99EEE076147E27AEULL, 
            0x16EB054FA5D3D9A5ULL, 0xCF0C9858E21B4BCEULL, 0x75F0707D991F3AB9ULL, 0x530F72AFB2D4F522ULL, 
            0x35648C69FEFAF35BULL, 0xFD19540360306CEEULL, 0xC01CE217BC3C3D18ULL, 0x9CB3308C00E67059ULL, 
            0x4800AB5D0F4FBDF7ULL, 0xFF59C75F9B295637ULL, 0xF1D6B8EC864429ECULL, 0xAE5E29F32A4F4650ULL, 
            0xAF83E9523BB2C122ULL, 0xB9B1E3A544E62435ULL, 0xBDAA7A0DCDF6ED81ULL, 0xF95C6E27577866E3ULL, 
            0x6C4E565FF2BA59FFULL, 0xDD99B717BC826189ULL, 0x2CC41262A3BB2C75ULL, 0x090434FA4AB2A342ULL, 
            0xFD0027DD2B4FC5D6ULL, 0x635ED7DB94607BF9ULL, 0x36EC2E874072F21FULL, 0x4D8200E0D5FE234FULL, 
            0x763EB614D9BB1FE6ULL, 0xBCD2006D8E51226FULL, 0x7BA82F9EFC4F0D3AULL, 0xA23863A32793797CULL
        },
        {
            0x81991D40F67691E9ULL, 0x011233D609C68AFCULL, 0xA55ACCE5FDF4E3F4ULL, 0x5EF5225495259641ULL, 
            0x5A45FDD3F14CE916ULL, 0xF7D814EE3DBDDF36ULL, 0xA17DC335A51EF232ULL, 0x18B532A013F8EAFBULL, 
            0x391A931B94E2B173ULL, 0x10969AC9882F6C8EULL, 0x2B186A0AE7D56EEDULL, 0x10FA36149BABCF69ULL, 
            0x81C91D7BDBC04B3EULL, 0x545B071216B1844BULL, 0x3092C9017C68ED9CULL, 0x7CC507AD0E64D10AULL, 
            0x69FFC4F6DCDD02D7ULL, 0x2A82D9F64A1AF9ABULL, 0xFF02638ECEBFF766ULL, 0xA29D363675C903F2ULL, 
            0x0C639D06CCD10D2BULL, 0xE83D39492180ECCBULL, 0x68FC6E579B896E5BULL, 0xE8CF9E03B06F5B14ULL, 
            0x6231E833EF7309A9ULL, 0xFB1D526FB485F561ULL, 0xBA4C8F2D4708583DULL, 0x5CA770B95DE99E9BULL, 
            0xF0BBE9FE52F4C5F8ULL, 0x321A1C5F24B9DC6AULL, 0x4BFC882ABCCEFDD8ULL, 0xAE77686B56E75807ULL
        },
        {
            0x65FE59B190C00657ULL, 0xD2CF8088F77D2352ULL, 0x0A0B1E298FD5A5C7ULL, 0x186AB862B8B7164CULL, 
            0xE9825E4620B5A80AULL, 0x15754031E868DBEEULL, 0x2D9C10CEBE28CBDDULL, 0xA5B1C480135D4B9EULL, 
            0xCF3FDF3EE9561345ULL, 0xCCB004908D3DD1ADULL, 0xB6BEA6AD9CE67717ULL, 0xFB1E1FB0B9355A30ULL, 
            0x4CD76289AC2C5F50ULL, 0x98E2E26A2B1FB1BCULL, 0x12EEA9909F231BF0ULL, 0x77CB76A977EB2588ULL, 
            0x8130571F2338C925ULL, 0xB176972F3AB6293FULL, 0xA3C24887AE4E649AULL, 0x339AE6BDEF1A1D04ULL, 
            0x640014795EA73074ULL, 0xFCE62EB3C12E0DAEULL, 0x95114C8CA940B46AULL, 0xC1670AD9D8E630DCULL, 
            0xF352B2DBD2005FC7ULL, 0xCF536F7E0ACFF2E2ULL, 0x53C089BEE5C1B292ULL, 0x8BF95DE3511072E4ULL, 
            0xB4B81232346166A6ULL, 0xC8A776ADB09D98C0ULL, 0x0C7CCBE62FDF18A6ULL, 0x4B91785E803C189CULL
        },
        {
            0xA58A3F2CC62D4CBEULL, 0xC21C28999EBDE150ULL, 0x8776C35C8650A30DULL, 0x4CC31A48E7341C12ULL, 
            0xD68C1D0708F342A1ULL, 0x53C493A7D35C0F16ULL, 0xDE04A5D187A5B62BULL, 0xBD935371A277512FULL, 
            0xC6A297E6A22DAC72ULL, 0xC5757A0A6A92857DULL, 0x2148740E45FF88BFULL, 0x099CD5E7993C5C10ULL, 
            0xC906BCEA7D34E2C6ULL, 0xBD704D3C92A5A517ULL, 0x516DFC3965DC953FULL, 0xEA23BAA0269AF770ULL, 
            0x1EF0071B3E747E19ULL, 0xCC639922EDB754FEULL, 0xFD244AEE999573FDULL, 0xBE803B58274E037AULL, 
            0x800020CBF45D8983ULL, 0x53BE664DD90C4717ULL, 0xCCEE9D1FB06B7A2EULL, 0xB202AC233E59F04CULL, 
            0xB36BD9BDE61170F6ULL, 0x8F4CF93B2802850DULL, 0x2AD4FD4D2A9EFBC6ULL, 0x61BC0ACE857CC445ULL, 
            0x843887574E88DBEBULL, 0xFEBA3DB13F433067ULL, 0xE4AF450C7DFDC7D9ULL, 0xF63ED9C0885F7A04ULL
        },
        {
            0xF9317A771261DE94ULL, 0x4E14664FB0D79252ULL, 0x0B6CA101368FB8E7ULL, 0x6FAECE9806A526D4ULL, 
            0x80D000C67366DA40ULL, 0x5B36C3DAACB9BEE3ULL, 0xC98F1F99EEFD8778ULL, 0x30025F5705C1D218ULL, 
            0x047254D82FDC24A7ULL, 0xBF78880ABAE4C076ULL, 0x7F16AE3563BC6578ULL, 0x19D69DF3AE6F6504ULL, 
            0x5F88ABE2328C600AULL, 0x0944CB7BBFEB5E40ULL, 0xBEA4C62DBF187137ULL, 0x7BC30017F86F73FAULL, 
            0xD74387B52C6098BFULL, 0x32405E98DA8D52EEULL, 0xAC0352396695D660ULL, 0x9DCD4713AD1C5F2DULL, 
            0x4CC2DB020C9F59F7ULL, 0x79DA3DB00BA01C11ULL, 0xDB222E158DB7D32DULL, 0xB04835DAC800BAABULL, 
            0x848154D458ADB2C8ULL, 0x0D7A779C93C47B3DULL, 0x50CCA11CBDEC6C0BULL, 0x51E0B89DA3871E1BULL, 
            0x7C40F907BE007238ULL, 0x950A8AC7C2F4BAD3ULL, 0x8B27EF634DBBBE67ULL, 0x35F5619ECB051D12ULL
        },
        {
            0x00145A5B5A5F22FEULL, 0x424A68319A592CF2ULL, 0xF13E34194D3CBDF9ULL, 0x432252FCABD280ECULL, 
            0xB8B9879E823A1B8DULL, 0xAD5CC90CC0F5A36FULL, 0xB3FB6206501BB2E3ULL, 0x8CF496594CCDAF71ULL, 
            0xB2D86A29572B21C7ULL, 0x05E563436F283EF8ULL, 0xBC4FBE77815FBE84ULL, 0x7F85E42932E48C39ULL, 
            0xFA1F5D92FF302B16ULL, 0x3CE2E7E7B09B7C35ULL, 0xA01E30C5B7F93AB8ULL, 0x95B6CECB04402C78ULL, 
            0x48DDA5654A2B669EULL, 0xA1E5B5E7E3CA619AULL, 0x0A7FCF7C189E988BULL, 0x21B5E778BE39CE32ULL, 
            0xDA15225B1BCCC607ULL, 0x9ACC268C132DFD4CULL, 0x6CE005F13FCBD515ULL, 0x875B36D9B1498CB9ULL, 
            0x302C298009570860ULL, 0x4E95CC66FAF612B9ULL, 0x10CE4DDB05E13668ULL, 0x5AA8C2BA70E2FD47ULL, 
            0xB4405BC58D946084ULL, 0xDB53FBAD676B9342ULL, 0x6AAA00C251FBF21BULL, 0x8309E40B83DA8090ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Miram::kPhaseHConstants = {
    0xE1D543F222CC49CEULL,
    0x343BAE8AF51B97DBULL,
    0x9044F955EEEF3167ULL,
    0xE1D543F222CC49CEULL,
    0x343BAE8AF51B97DBULL,
    0x9044F955EEEF3167ULL,
    0x50D1AF137FC05E0EULL,
    0xB740C782408C2AD1ULL,
    0x18,
    0x24,
    0xCE,
    0xB7,
    0xFE,
    0xE2,
    0x5E,
    0xFC
};

