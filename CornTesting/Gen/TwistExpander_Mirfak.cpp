#include "TwistExpander_Mirfak.hpp"
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

TwistExpander_Mirfak::TwistExpander_Mirfak()
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

void TwistExpander_Mirfak::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF7BEC1A27EED7396ULL; std::uint64_t aIngress = 0x97969ABFA7481729ULL; std::uint64_t aCarry = 0x87BA1CDBF9A765C6ULL;

    std::uint64_t aWandererA = 0xEB45C16CA6166754ULL; std::uint64_t aWandererB = 0x8C9F6A6CA2984294ULL; std::uint64_t aWandererC = 0x8E0F3787FC1272D7ULL; std::uint64_t aWandererD = 0x87268B2ADB6BBCD6ULL;
    std::uint64_t aWandererE = 0xBDF67E6EC0CE116BULL; std::uint64_t aWandererF = 0xA1E17D55B4886214ULL; std::uint64_t aWandererG = 0xCD6A95662D76471CULL; std::uint64_t aWandererH = 0xB3EA621FB740C7CCULL;
    std::uint64_t aWandererI = 0x83F6D1DA007DBD7AULL; std::uint64_t aWandererJ = 0xE5E72A6D0475641BULL; std::uint64_t aWandererK = 0xE214B37455E63233ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13621551754160667186U;
        aCarry = 16116992627398308966U;
        aWandererA = 17606082882500042444U;
        aWandererB = 11667580334259421779U;
        aWandererC = 10147248254160056844U;
        aWandererD = 17485090950030884198U;
        aWandererE = 18299067601031185731U;
        aWandererF = 12554573755676831133U;
        aWandererG = 16153949448491959484U;
        aWandererH = 10467194707327616706U;
        aWandererI = 12348548616210526824U;
        aWandererJ = 9453695437178950376U;
        aWandererK = 17694795652635462641U;
    TwistExpander_Mirfak_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mirfak::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF9137C18CE429C87ULL; std::uint64_t aIngress = 0xF342A984235C100FULL; std::uint64_t aCarry = 0xEE702F990FFC1D7EULL;

    std::uint64_t aWandererA = 0xFA5567EA70A7F43BULL; std::uint64_t aWandererB = 0xAF219977DB982EBEULL; std::uint64_t aWandererC = 0xAE2753DEC8311509ULL; std::uint64_t aWandererD = 0x960882ADB274C497ULL;
    std::uint64_t aWandererE = 0xE140EDCBBCB19273ULL; std::uint64_t aWandererF = 0x9C9FF7D2FAD1386BULL; std::uint64_t aWandererG = 0xD5C82A589921A9C0ULL; std::uint64_t aWandererH = 0x9D8F46A405DA7735ULL;
    std::uint64_t aWandererI = 0xF5C182E8FDCA601DULL; std::uint64_t aWandererJ = 0xB60199F3EF588B5CULL; std::uint64_t aWandererK = 0x8ED2429BFF6A95FEULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10306998230526460609U;
        aCarry = 11457918307636989552U;
        aWandererA = 16699606296214352168U;
        aWandererB = 9491985530111995828U;
        aWandererC = 14675421991846315177U;
        aWandererD = 10052171452239785737U;
        aWandererE = 18128975532085183740U;
        aWandererF = 14030005688663056294U;
        aWandererG = 9403608432861419610U;
        aWandererH = 11077893132713606611U;
        aWandererI = 9966201824801544654U;
        aWandererJ = 17318923365518469311U;
        aWandererK = 12499047076788914844U;
    TwistExpander_Mirfak_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mirfak::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE1FC3DE26078FFE0ULL;
    std::uint64_t aIngress = 0xACE8FD0CB5CE32E6ULL;
    std::uint64_t aCarry = 0xF47349F8FD1C71ADULL;

    std::uint64_t aWandererA = 0xD815EFFB140FCD78ULL;
    std::uint64_t aWandererB = 0xEC1D352184B680EFULL;
    std::uint64_t aWandererC = 0xB4AA1399B77D92AFULL;
    std::uint64_t aWandererD = 0xC3B466B11ECF4E68ULL;
    std::uint64_t aWandererE = 0xFF2D770FD064C386ULL;
    std::uint64_t aWandererF = 0x9FF2ED3EDD116F2FULL;
    std::uint64_t aWandererG = 0xFB91F6170E83F6D2ULL;
    std::uint64_t aWandererH = 0x89C981D859995213ULL;
    std::uint64_t aWandererI = 0xE5956D71527A9E46ULL;
    std::uint64_t aWandererJ = 0xA5E49DD947195A36ULL;
    std::uint64_t aWandererK = 0xEDF0CD90A696A2A2ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Mirfak_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mirfak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 21 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1798 / 1984 (90.62%)
// Total distance from earlier candidates: 36343
void TwistExpander_Mirfak::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 944U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1911U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1515U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1836U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1223U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1426U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1037U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1888U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 221U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1395U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 467U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 310U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 619U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 97U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1745U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1076U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1141U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 865U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 202U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 572U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 873U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1581U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 481U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1473U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1207U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1128U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1176U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 997U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 294U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 428U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 36U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1633U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 427U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 260U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1520U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1992U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1238U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 413U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 995U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 914U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1375U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1743U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1151U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 899U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1208U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1610U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 402U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 492U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1511U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 455U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1756U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1362U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 626U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 457U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 681U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 262U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1152U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1704U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1272U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1053U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 87U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1889U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 269U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1539U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1498U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1587U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 192U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1179U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 911U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1999U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1019U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 963U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 458U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 94U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1247U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1826U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1482U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1726U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1624U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1732U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 883U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1246U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 996U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1317U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1590U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1927U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1599U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 781U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 225U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1941U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1026U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1399U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 633U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1486U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 757U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1064U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1640U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 15U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Mirfak::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCA1B5099E433B50AULL; std::uint64_t aIngress = 0xC557FFAE52E8D23CULL; std::uint64_t aCarry = 0x8943A5C3BB816C1EULL;

    std::uint64_t aWandererA = 0xD59D33EBA6CB9F77ULL; std::uint64_t aWandererB = 0xEA4B0DB7DCD3E9E2ULL; std::uint64_t aWandererC = 0xB6AB93B58A684CA2ULL; std::uint64_t aWandererD = 0xCA40FCCFC73D961BULL;
    std::uint64_t aWandererE = 0xEB83C505740E4707ULL; std::uint64_t aWandererF = 0xDE8F0BCD3647028DULL; std::uint64_t aWandererG = 0x80BFAAAA543CC324ULL; std::uint64_t aWandererH = 0x9C24515972D994ECULL;
    std::uint64_t aWandererI = 0xF922158EB8668D18ULL; std::uint64_t aWandererJ = 0xB914F8260130E165ULL; std::uint64_t aWandererK = 0xAAF1C4AF06C7A92FULL;

    // [seed]
        aPrevious = 12834422715621473221U;
        aCarry = 16034610697256757498U;
        aWandererA = 10801487043593633101U;
        aWandererB = 17136913636317723723U;
        aWandererC = 15397181426259149133U;
        aWandererD = 12817571316988429046U;
        aWandererE = 12131008086192712253U;
        aWandererF = 15943428365036665318U;
        aWandererG = 14003986250520885506U;
        aWandererH = 16419160110666299810U;
        aWandererI = 9727308526555755226U;
        aWandererJ = 14292891248981552963U;
        aWandererK = 12704971780010264540U;
    TwistExpander_Mirfak_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mirfak_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mirfak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mirfak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 21 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10868; nearest pair: 482 / 674
void TwistExpander_Mirfak::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2553U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1836U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4145U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4513U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7248U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5185U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 819U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2799U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3860U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1280U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7836U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5141U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4808U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1462U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2625U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5887U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 719U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 476U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1509U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1590U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1561U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 529U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1029U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 464U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1997U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 926U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2022U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1352U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1437U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1006U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 671U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1926U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1933U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 21 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 10863; nearest pair: 495 / 674
void TwistExpander_Mirfak::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4511U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 126U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8102U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4504U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2569U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 687U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 535U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3238U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2515U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 801U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 821U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3585U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3004U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4255U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 64U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7069U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2011U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1840U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1298U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1810U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 174U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 766U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 845U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2028U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 650U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1336U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 872U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 553U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1787U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2004U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1204U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 501U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1909U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 537U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseASalts = {
    {
        {
            0xB6A66E7BAC8EB557ULL, 0x4FBA3E0FF4811773ULL, 0xE8C3CAB6E595DB29ULL, 0x37A1F753A9ADDBBEULL, 
            0x1CF4EEA18856AA1FULL, 0xD3A05E8E4AB688F6ULL, 0x840E33F41A5CC783ULL, 0x0A84B2B2E4CC872BULL, 
            0xA8114443731CE6E5ULL, 0x24348C4C9DA5732FULL, 0xB134AF88F2679FE5ULL, 0x5C5B949CCA3C1388ULL, 
            0x227AB425AC5333E4ULL, 0xA5C5163B4DD672E3ULL, 0x0AC0BD246C13D296ULL, 0xA6161BF4F800F19CULL, 
            0xEED0EC80FBBA3655ULL, 0xA07CC0049D1259DEULL, 0x653FCE19B31C1E46ULL, 0x14BEC10F3C746AA3ULL, 
            0x3FD179CF764602FCULL, 0x5EE21F1957BF7BB4ULL, 0x86E9713DB8CEFA02ULL, 0x4CA13510D477AD7EULL, 
            0xE4BEC65EEF95301CULL, 0xA87BEE03E988E3DCULL, 0x2888FA2C9EC314C6ULL, 0x4EC538C5A034CED3ULL, 
            0x9D1F93BA29A93495ULL, 0x6F8B563520D703E8ULL, 0xF99B762CC5D237E1ULL, 0x3313D303CFAA1266ULL
        },
        {
            0x4BA42A18D1DE5602ULL, 0x8CE458D1D1E0664FULL, 0x5907862A1D7EE1FAULL, 0x5FCB8BCD665ADD87ULL, 
            0x372431002538C6EEULL, 0x4E6A9D5BB0C3705AULL, 0x24590DA2416B6AC4ULL, 0x04E301AD8CF83897ULL, 
            0x8373AC554C2C62A9ULL, 0xB03E3B7FEBB08331ULL, 0xFA481CE128986C06ULL, 0xE03794AACB01406CULL, 
            0x10C84F3DE5FC3972ULL, 0xDF1E6669412C0DC5ULL, 0x197B1F3181D604D3ULL, 0x96DA0AD980A48D37ULL, 
            0x51F38BD20C36EB59ULL, 0xCC3C0E03C1F1439CULL, 0x3DE2C445E0D68554ULL, 0x9B898D244BF445A9ULL, 
            0x3BEDA6DBD83ACC4EULL, 0xD013CECC6742D484ULL, 0xD0AB7AA43507DE5FULL, 0xE1072ACAF85B3BD2ULL, 
            0xC3E9AE36BCDD988AULL, 0x4787AD5DE1703107ULL, 0xD3A9B890BF023ED0ULL, 0x4B9CF430892053B6ULL, 
            0x8F50535A1FEA64FAULL, 0x47DCDE87423010D4ULL, 0xDBF86280937AA235ULL, 0x78B28E29C56C476EULL
        },
        {
            0xE9C914797259D369ULL, 0xAC136EFB4D284DA1ULL, 0xB083998BD6999810ULL, 0x2ABFAEC929EBA952ULL, 
            0xD2B0C2EA31EFB96CULL, 0x480697CF001F9867ULL, 0x33D46AE8BAC6BE86ULL, 0x45EBE086CBF7FE06ULL, 
            0x791EE08942620C8CULL, 0xC82E5F7B271815DDULL, 0x030B78BD0BC93B2EULL, 0x21331E27CB3BEA5BULL, 
            0xA04930D18FA95715ULL, 0xE3384DBE59E16542ULL, 0x938C2DC0D13BA531ULL, 0xF5FA37027ED49204ULL, 
            0x7FCA71B84D2C130FULL, 0x7276085CDEF1E63BULL, 0x9D89B4110307A822ULL, 0x64449E207504213DULL, 
            0x730A6B7909B10D0BULL, 0x3835555552FCC059ULL, 0xA7F58738DB4CCB6AULL, 0x71C20B14BBBE6389ULL, 
            0x67B8E45A5D833D68ULL, 0xB95A25061BF4FB3FULL, 0xBDDC22A01BDFF16CULL, 0x00F53A961F8CAC29ULL, 
            0x787A820746982927ULL, 0xA100A367DBD71662ULL, 0x805A99EA6C8F128CULL, 0xF44DB786AD166F0DULL
        },
        {
            0x88DB57AB868C9E41ULL, 0x8ADB47E370D4DBB1ULL, 0x3365684696BE94C0ULL, 0x56B86DD67DF8B5A9ULL, 
            0xA74886BD82DF4932ULL, 0xBE4980DDD1C7AD19ULL, 0xC64545709C61C117ULL, 0xE77713F996A91D9AULL, 
            0x9919BC259A59BD2FULL, 0xA33D1153D5E136C9ULL, 0x3E7B67D4B0F45B1DULL, 0xFCDE426EA9B433B5ULL, 
            0x0FD049393216199AULL, 0xF222D4704290E649ULL, 0xC99871E53B8A2863ULL, 0xFF24A3AB01076317ULL, 
            0xC1B86C6054E3C3ACULL, 0x32CFEEB862992E39ULL, 0x72FD38EF16EEAB11ULL, 0xCED9F136ED72F89FULL, 
            0x26979E52F350A7C6ULL, 0xF5ADE62985A62A40ULL, 0xCB8A173E0E5E470DULL, 0xABF7E705840ECF9FULL, 
            0xFC49EB6E96302DEFULL, 0x18ED15959E1FC144ULL, 0x00B03068B6440F3CULL, 0xE1B18C013E46A5A5ULL, 
            0x37A90E55E6B34C6BULL, 0xC42D4CC75F7A703EULL, 0x8DF3E7E0A76378B1ULL, 0xBA32A9B54FD98DFBULL
        },
        {
            0x52AF76E64E7B98F7ULL, 0x2503C44507B8881EULL, 0x2EFE8CEB88FDE4F9ULL, 0x54193229D02F1207ULL, 
            0xDB40BEED4A09ED0FULL, 0xA45AC2E026450008ULL, 0x1B9248F57BEF3CD3ULL, 0x140DECF35EB46925ULL, 
            0x18311373F90F6CCCULL, 0xC761DAF472966098ULL, 0x1722B21C6922D5B0ULL, 0x8E9A173FAEF74DF0ULL, 
            0xE7E180D709FFE3B1ULL, 0xF45CBE1E443A198AULL, 0x52FA9D674AD5C24CULL, 0x1B894D2222333FD7ULL, 
            0xA22B31B1A8AB4DE1ULL, 0x79974E8BE2B57EA9ULL, 0xD1E824FA43845D6BULL, 0x040C998859590B3CULL, 
            0x3D0B0B280F3D4D47ULL, 0xA2A5C20F24A40FF4ULL, 0x703FA7E679B36161ULL, 0x5A08B1137479B550ULL, 
            0x077CC0C55FA078CBULL, 0xECCAA48B410FC5A0ULL, 0x70019DC2D77DF8F4ULL, 0x2AC8481C93B12A29ULL, 
            0xDF79D1F0F1390126ULL, 0xEF81F828CD00E35CULL, 0x903D4F2FE054578FULL, 0x59513177F0694CF4ULL
        },
        {
            0x5595AD035D5E80C0ULL, 0x1A13489433C3AF94ULL, 0x000B84B8A7D6BC2FULL, 0xF60035C9A64FDA9DULL, 
            0xB050142894FA1090ULL, 0x9B1D6ED8FA34B897ULL, 0xEA3AF8240151BE06ULL, 0x87B6DD5B0042A2C6ULL, 
            0xA335FE530120B363ULL, 0x3C60DEF2E0CF1D80ULL, 0x441839FFA246A5EFULL, 0x7BC275FA0773052DULL, 
            0x9787117A46A53D8BULL, 0xDBE1A62EA82E6CC0ULL, 0xE84A9D686F0AC626ULL, 0xD4365DF4552C98F4ULL, 
            0x66727246AF6B9C80ULL, 0xA688EF745094028CULL, 0x0110F9C2AA700E05ULL, 0xE64BEB9CFA8F4DD8ULL, 
            0xAD6917B4CFF5F332ULL, 0x609B23FE91F5352CULL, 0x5B6F6DEF4B7749E6ULL, 0x8BD69D06FFD9CCA6ULL, 
            0xD1DF61804B6F53D5ULL, 0xF2C52E9F181586D8ULL, 0x94E14E12AC5E2F34ULL, 0xCD3871EC7FB4374EULL, 
            0xDFE3D772F121B418ULL, 0x88DDF32A296AA661ULL, 0xEE0B25353F0C963EULL, 0xE423E31FC1549550ULL
        }
    },
    {
        {
            0x0F89B97B75C74A80ULL, 0xD804A7A92775A9F2ULL, 0x64590722B325382AULL, 0x88212BE7056A2EC1ULL, 
            0xAE1086A60344052EULL, 0x64A1B382FD5C46D3ULL, 0xD7EAA967FD257284ULL, 0x6E0A9A8788CB02C0ULL, 
            0x2E11FC6734259D22ULL, 0xF1203C8E9D3DE1F1ULL, 0x5CD2C0911DFE4E89ULL, 0x84CA6816738B7B91ULL, 
            0xE825A3E64F4D1270ULL, 0x9B5E35E34FF9ED32ULL, 0xFDFF51A2655C6B5EULL, 0x995C0AD8DC7DC313ULL, 
            0x382E7D41E3929C26ULL, 0x43EDE151755C9FC8ULL, 0xE7032BC86BCB6133ULL, 0x681CB3C0DB1F0007ULL, 
            0xCF4411D213544104ULL, 0x561720B514C02A2AULL, 0x47C6D385464D61ECULL, 0x125E3C51AF697469ULL, 
            0x3DAE37CEA6FEB09AULL, 0x67EB68BC1367084AULL, 0x3532A2BCD144B1C2ULL, 0x049A126B70BB3C71ULL, 
            0x37967D3FE429F9B3ULL, 0xFD7E89DB4BEC53EDULL, 0xCFF71C40DA37FD83ULL, 0xC03B875385E64F23ULL
        },
        {
            0x75E95E59D9D12C69ULL, 0xEC7066FC9D57E5B8ULL, 0x4C0315387EE55BE5ULL, 0xCD4FA011F0D38B33ULL, 
            0x075778F8AB6034BCULL, 0x3DF961AAF9A01DEDULL, 0xDC96E274B1BF322EULL, 0x2585E4349A796B9FULL, 
            0xBDB191413EACE2AAULL, 0x1111FA84AABD3D2BULL, 0x80C8863D5A59A7FDULL, 0xDEEFB97C53466D11ULL, 
            0xCA115547B84B7CC2ULL, 0xCB94AA6B9BCAE851ULL, 0xBE2E1108E1414F5CULL, 0x47C9940CA00BDBD9ULL, 
            0xFBFC152F310FB288ULL, 0x1EE0BD8D66EAE678ULL, 0x5B0BBEABCF00D486ULL, 0x974906EF6BC10CC4ULL, 
            0x543B9BCA93B6CE60ULL, 0x7D8DC4DBB331A82AULL, 0x993164D9AA6E4039ULL, 0xF4F0297E85D6F9D9ULL, 
            0x04462F83AE19FCB1ULL, 0x6A373F1EC4CDD7C3ULL, 0x59A69B0B89AD95F0ULL, 0x8B6CBF3F427E27F3ULL, 
            0xE73588EF3D9D2637ULL, 0x36D393386EE85E55ULL, 0x55966BDF82F95EEEULL, 0x8095B2C35562EB78ULL
        },
        {
            0xCE30B85BFD0325F6ULL, 0x4FB5BCC6528FD64FULL, 0xF74732C047EEB9D9ULL, 0xBAA18CEA6B4B1621ULL, 
            0x43FAC518B2EA2EF0ULL, 0x12FBD760243F409FULL, 0x1BC28D10A615E348ULL, 0xA0A427E99DC5F43EULL, 
            0xC973084F1E29CBD0ULL, 0xDD0C562128A59073ULL, 0x61B188BAF247F9A9ULL, 0x69B741549C7F9E78ULL, 
            0xACB657E4C142C131ULL, 0x548A6AE1A5EA956CULL, 0xDABF8958D2654E49ULL, 0x4DDD157D7155FFB1ULL, 
            0x29C86526E3D8A565ULL, 0xA03FA95876E6800AULL, 0x85411AAC594F8350ULL, 0x694D7F909811394EULL, 
            0x96CF414B6C8E66F0ULL, 0x8A5AF3D2CAF5DD71ULL, 0x382551F951B1900CULL, 0x1CBC486585D110CFULL, 
            0xB49B5470F1B0DE9AULL, 0x04179FDE2829D927ULL, 0x69257FEF23CC6FF6ULL, 0x479EB28ED8C080D7ULL, 
            0x5B15756F4FCE201AULL, 0x597D01739EBFDCE7ULL, 0x3984C9A336C406A3ULL, 0x61CBABC73965252AULL
        },
        {
            0xF0079246512960A9ULL, 0x07954486A5DD612FULL, 0xB7F6BA7591085C70ULL, 0x9E54A6211EC93867ULL, 
            0x7672C494ADB0BA1BULL, 0x86741EE5238331EEULL, 0x1AFC4AD52C966CF6ULL, 0x71F5EF06F2BD10E9ULL, 
            0x3C10D0D9AFEB6543ULL, 0x3CB8E2499A672BE1ULL, 0x25FC430A9614D993ULL, 0xB0C4099A101BFBF2ULL, 
            0x54AC677F363FF26CULL, 0x05E007115DD75041ULL, 0x91EEE02AA000D711ULL, 0x502F46EB8915A7F6ULL, 
            0x1387DFA73C34A0A0ULL, 0xD4815D54021CAA34ULL, 0x5F1189212239F965ULL, 0x0ADB0CC80CB4C3DCULL, 
            0x218A33C1447BAB6BULL, 0x5F953DA335DB46AAULL, 0x7AAA98EE834C7EFBULL, 0x22A4A5E405C35E0CULL, 
            0x6F80A4AA19D04B04ULL, 0x42189C4B17AA51F8ULL, 0xAB6B6816FAA44B2DULL, 0x0450EE98047B294AULL, 
            0xCF383E155E22198FULL, 0x2778601445C03D69ULL, 0xD93CFC12F8A794EEULL, 0xC98FAEF4A224E62EULL
        },
        {
            0x7774F2FE7EC4F44CULL, 0x97CE7972DE6D5F63ULL, 0xF57CB8229A5A0FE2ULL, 0x2B9EF3BD6475F78AULL, 
            0x72C2C9EFAE4CC7BFULL, 0x06BE09C7DC080B07ULL, 0xCBCF81FB8BA7AE6CULL, 0x077E062D144B6ECDULL, 
            0x54D9521751AEDB53ULL, 0x1019C5EC9993A2B1ULL, 0xBA90FED14545A757ULL, 0xFCD156E63057686AULL, 
            0xBABF266288FA8B45ULL, 0x602B7CD6301FC283ULL, 0x0B2AB460F5A2368BULL, 0x25034A7B2B483F86ULL, 
            0x3B0D713E85187C02ULL, 0x5CD562A4BC4DF012ULL, 0xFAEC816EF5665570ULL, 0xC6703D587BAAE3ECULL, 
            0xD77AF6D7B8FBD402ULL, 0x6BE4C0170F9F7FE1ULL, 0x556473D93A96C30BULL, 0x6A8D0A2B021032EAULL, 
            0x1F90F32C1D36C34CULL, 0xA9CCE5863A846FF7ULL, 0x4594B2C182741E70ULL, 0x201123AFD77B74A4ULL, 
            0x6FD2446D058DFFA6ULL, 0x4022C39A2AB6C77BULL, 0x83BCB23D5A058B47ULL, 0x9B3A08C0B793827BULL
        },
        {
            0xC6302D40BA05E6EEULL, 0xBF3A77166E441A7BULL, 0x5ED6ADFFF8E866A6ULL, 0x09E24379B3AD1DC2ULL, 
            0xD38DFA7307427D30ULL, 0xC25B63E9ABB2B1B7ULL, 0x6D8C05C8F1D02332ULL, 0x2ABE21D350608AB8ULL, 
            0x1575D74C2CCF7C72ULL, 0x4F63079FC3968CEFULL, 0xCB3B887BC6BBFC7AULL, 0x0CE541C009EBA15AULL, 
            0x96B427AA66AD653EULL, 0x29B982689252E7C8ULL, 0xF6EA9AF269F0E2DCULL, 0xC09E40FCCE319B86ULL, 
            0x43CDA3F6C1E13767ULL, 0x5699794E20C1CD19ULL, 0x73F01708100BE43FULL, 0x43D5D1E6FD7B8CFBULL, 
            0x4597D2DBB63C0E50ULL, 0x541D3EFBE30FD1EDULL, 0x481C09F9990A65F7ULL, 0xBF01C204B75C0B81ULL, 
            0x7F8F40E4F6733B34ULL, 0xD00D8DECE822046BULL, 0xCC0348EBD1B20939ULL, 0xE677411A296F0C09ULL, 
            0x2FEEB1830B89BF83ULL, 0x64EE6FBA0003812AULL, 0xEB3568B2E51C4606ULL, 0x0646775CA19F39E3ULL
        }
    },
    {
        {
            0xA8B71D7274C8002BULL, 0xC6E07345B5ABA470ULL, 0xD0C29B30136A4DA3ULL, 0x5CE77DE19348F6FAULL, 
            0x9A4A09783390C08AULL, 0x181090C313EE06ADULL, 0x4B9683B940F7617DULL, 0xFC8DAFAB7C3BDFF1ULL, 
            0xA9D1B7E41BBC0EA2ULL, 0x156AD4ED5DDDBAC2ULL, 0xC42E6CBDC9067937ULL, 0xD8C9BA7B822C721FULL, 
            0x737E42041FAEC454ULL, 0x96F5FEE42062AE46ULL, 0xC3051C1E86414DDDULL, 0x3CF849AC9E3A75DDULL, 
            0xE01F1F365A278C62ULL, 0x37CDAE010CACC519ULL, 0x07472C283E213887ULL, 0x61A3D4ED81684B26ULL, 
            0x69BF0CAF67FF8EFBULL, 0xB5A78D350B9F158EULL, 0xB879DE7B9328D158ULL, 0x6E8CAD9BCF981561ULL, 
            0x0078AD4A1C715B5AULL, 0xE3F97614DDA2DDD7ULL, 0x73C5AF738DFC8786ULL, 0x6E08F6E610DBA139ULL, 
            0x0485C42FF38B0CD9ULL, 0x3A2F76307E95BBD5ULL, 0xA4FE80CE53311DF0ULL, 0x429873EE4F34C74EULL
        },
        {
            0x229D9FB94E57C3F9ULL, 0xB8DAA91230E334BFULL, 0x6DC2D3C45B5609AFULL, 0xBE916EB727F99ABCULL, 
            0x9884105F02205A9DULL, 0x27656203FE41C510ULL, 0x5398DD58B7AB341AULL, 0x17D03006FB9229DCULL, 
            0x135690FA9D630100ULL, 0x4DB5196A581FDE7DULL, 0xE729824E1B6AD8FAULL, 0x915EF9E63D86A9BAULL, 
            0x32684CAA5885375AULL, 0xC6C31030472D5462ULL, 0x1A1E48E9BBA242DEULL, 0xD8CCD4D6CDCEBA86ULL, 
            0xB3E59683C2E98F19ULL, 0x9BD952BE574EE455ULL, 0x20BDA42BB200F4AAULL, 0xCAA3F4D68CBFE207ULL, 
            0xD40D1235497CB567ULL, 0x09CDBACE3D042CA7ULL, 0x68DD90BBB1798931ULL, 0x8092AE6D9AA9268EULL, 
            0x3FDDDAA459A8892AULL, 0xF9C7059030840280ULL, 0xC491EBDD229EDCD1ULL, 0x0739ACEB01833E9CULL, 
            0xCB81A73B1B321A52ULL, 0x02F20146FDED0CCAULL, 0x0C341B1FC6BAD69CULL, 0x34B010DC40DAD2E8ULL
        },
        {
            0xB3A93744B5A3C96AULL, 0x71E812D64B03BA69ULL, 0x8902524D68127E20ULL, 0xFBC684B053C27652ULL, 
            0x96030FEE6E3505AFULL, 0x6C90133788D5565FULL, 0x7C3DBE322ED5E92FULL, 0x565A28E59E9893DDULL, 
            0x9F70CA3EE74148BCULL, 0xE6396274EAF87BEEULL, 0xC99260B2D4CA43A4ULL, 0x31ECBB2B67DAC8EDULL, 
            0x1EC6A811ECA2E15EULL, 0xBA9FB6F559198D66ULL, 0x42B88F23D12C297EULL, 0x876D75269E5A1271ULL, 
            0x1B288BE0C09A4861ULL, 0xCC641BDF24291BC4ULL, 0xCE16FAFE28930A34ULL, 0x2CFC6ADEBD00F053ULL, 
            0xB94E0BC1E82A8BD5ULL, 0xA91216D5E9DCEF11ULL, 0x8C0A02BD96FD71A4ULL, 0x7E5118FD7AC7A09AULL, 
            0xEEB8F14EDAE9CDFDULL, 0xF46474C7214647CAULL, 0x3FD70B95EDA67D34ULL, 0x8646BBA62325A24EULL, 
            0x97636D04F6AA3795ULL, 0xE1C8B2B51665EECBULL, 0x74C867CB2917E783ULL, 0x8327F733CBC56084ULL
        },
        {
            0xB3DB81E2F7AAD3D2ULL, 0x5B244A932F70AE55ULL, 0x7D6AC22186278F8CULL, 0x76C06784F13B06ABULL, 
            0x7FA71B40DFB2321BULL, 0xEFEE4B265D19C121ULL, 0xF8211134C162E26DULL, 0x9FC3ADFD0779C9DAULL, 
            0x84C3784158FB9150ULL, 0x88B060702545E31AULL, 0x9136130F963CEFF0ULL, 0x6DE79731C4B60434ULL, 
            0x5DE169263B818247ULL, 0xCCFB47E25493011FULL, 0x08298056ECB94F25ULL, 0xBE32B6CD3CA9C49CULL, 
            0x8F4E14AE58C8E592ULL, 0x28191BC8CCC3182DULL, 0x34B00ACF2CFABDAEULL, 0x588F75E8416B0CFBULL, 
            0x29DCAB38D0368A02ULL, 0x3D920E502BD2FE8BULL, 0x78B08E77C8A21E72ULL, 0xC5FDC9EB22096466ULL, 
            0x19ECBF6F96A7DF9EULL, 0xA51A3F80D8F7E158ULL, 0x534ED886617D5318ULL, 0x7C09AAD8917B042BULL, 
            0xF08630DE60A4002AULL, 0x15ED3D2AB41C6FD3ULL, 0x4DFCEB75E8C22515ULL, 0x7FBCA814DAADB9C4ULL
        },
        {
            0x08AB11005B2CCCA9ULL, 0x3459C0390410C0A0ULL, 0xFDA5FE6A8CF70171ULL, 0xF3F3D44ACE1C0931ULL, 
            0xFB7DADE853A08DE1ULL, 0x86A39F7D21EF1D58ULL, 0x11C8BCAD6326D865ULL, 0x5BB40DD28DEB6948ULL, 
            0x60BD57848C87E5ABULL, 0x7C3DBB65B914557AULL, 0x6D4E893FEC88AD2AULL, 0x400DE957DBB4F103ULL, 
            0x937BD0FB4C7B426CULL, 0x06B54A1928C9FE15ULL, 0x9B19DC2DCBD6BF73ULL, 0x5CF5D50FD22C1384ULL, 
            0x495403B90C65CE99ULL, 0x4639502702ED2C1CULL, 0x02FC56782C86CCCCULL, 0xD4FC7E311122E61AULL, 
            0x529789EFEA76B323ULL, 0xC714F0765316A8A8ULL, 0x87DD8F0C9C33CFBEULL, 0x09620CA4112F42D7ULL, 
            0xB597CD7F2F3F885EULL, 0x84ADB306EB898EF8ULL, 0x1FA0CC87328146A9ULL, 0x9C4C13D2F86BDF18ULL, 
            0x529418F10AF2E1A1ULL, 0x1E2B255C3B294D19ULL, 0xEB476889A193345BULL, 0xB3C0EEE9158D0D1DULL
        },
        {
            0x7E2F3721D31F02EDULL, 0x808F967742FFA2BCULL, 0xCBBC4E16F4B28B20ULL, 0x32D4486B5682E9D8ULL, 
            0x21B3D800EE6B62CFULL, 0xC6AD0E31A7FCFF5DULL, 0xD88B7445C668A108ULL, 0xACE02B4F3A1D1D4AULL, 
            0xB479966729CB42F6ULL, 0x9672EDE12244649FULL, 0x615B35F310FB99B3ULL, 0xF9FECA04F599CA76ULL, 
            0xCFB56B60EB6B850CULL, 0x7AC251EBFAF2E4D5ULL, 0x75A99B556B16C274ULL, 0x7616468825290088ULL, 
            0xF2538C1CABE78809ULL, 0xCDC438E33B53149FULL, 0x7787F2713C917CF7ULL, 0x64DD32DE45ED43EAULL, 
            0x2A4DE2C23DB8761DULL, 0xB4D89C203E042D6CULL, 0x82739C4DA3612EB6ULL, 0x41CD1B1FF5878E37ULL, 
            0xEF3E85D4D5AAAEC2ULL, 0x25CE9B9D6B7AC9AEULL, 0x17EE8CC0773B6F1AULL, 0xF6E88C82A400D00DULL, 
            0x53FF57795C6A0A6CULL, 0x27370397242334DAULL, 0xEA9EAB95C89F6750ULL, 0x0D13FBCB5A308A98ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseAConstants = {
    0xB4ACDEAD67E918F8ULL,
    0xF8D4521352D5AFD9ULL,
    0xD01BDAB27FF6CC62ULL,
    0xB4ACDEAD67E918F8ULL,
    0xF8D4521352D5AFD9ULL,
    0xD01BDAB27FF6CC62ULL,
    0x04AEDF3CF05607BAULL,
    0x816BB2EFB302B888ULL,
    0xAF,
    0xCF,
    0x27,
    0x98,
    0x87,
    0xAE,
    0x78,
    0x7D
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseBSalts = {
    {
        {
            0x16BA354BD92EDC40ULL, 0xAF9BF6F8C3F408C6ULL, 0x94E31D37D454BDD9ULL, 0x955E60158492952CULL, 
            0x0D4747715026BC28ULL, 0x89A07D2D77776A56ULL, 0xCFCAAC4FC49453F0ULL, 0xC6B67EB269B151BBULL, 
            0x94E508EBACC33F15ULL, 0x306D1225F0E07DC1ULL, 0x5161C4D9FE7EEBD4ULL, 0x5D96546F8A039EB5ULL, 
            0x0BBD5997A19FCCA6ULL, 0xAB1B49ACF9AF82CFULL, 0x670C50450693C2DBULL, 0xE5E6376D75FA4495ULL, 
            0xD9DC8FF566FD62BEULL, 0x725F4345D805C6EDULL, 0x09684D1198C3B15EULL, 0x109FE5E080CF8139ULL, 
            0xEE75387D8A74B947ULL, 0xB0D56C90C5DDF963ULL, 0x8DB5DAA906111F77ULL, 0x42C4C4536AF073ABULL, 
            0xE0E4356B2265C1D2ULL, 0x2FB0DA55FA95BA9DULL, 0xB06CED6AC09439CCULL, 0x1DC9FF435C939A78ULL, 
            0x1C817DF6DD5C91F2ULL, 0xBA8429E9A1AAF343ULL, 0xD8262E0D69A73B41ULL, 0x267904C0D743482FULL
        },
        {
            0xBCD41D2365CE028EULL, 0xBAF98390C54AB8F5ULL, 0x769FAD878CF34255ULL, 0x152CD62988CA6263ULL, 
            0x94B0B644F79AE859ULL, 0x109F6B58E793860CULL, 0x669E388D7F82BBA5ULL, 0x15E29AC6393CD8CDULL, 
            0xCC4841B542B6D79BULL, 0x95C216807488A8EBULL, 0xC48B07ECD9C4B62FULL, 0x55DF53B02307CC13ULL, 
            0x1CEEDC3BD8CADA56ULL, 0x2F96899735210809ULL, 0x189E26225F423D91ULL, 0x8E84D4BC72D62A23ULL, 
            0x241FCF3A03F29AA2ULL, 0xDE3A9A6D5B7E4FFFULL, 0xCFF90913E6583D6EULL, 0xCAE99FE94D3ECDBFULL, 
            0xE19272F0ED0A386BULL, 0x839EC15324CDD244ULL, 0x85E69188268EBD2EULL, 0xCF7E3AD1C3121C58ULL, 
            0xD5EB64AB2DF3EFE8ULL, 0x2406A61E98ED957BULL, 0xD608010DD45D24E5ULL, 0xEBA6F01CEB60E64EULL, 
            0x758AA391990831DAULL, 0xB4DEFA1DFECFFFFCULL, 0x141054D73C443C37ULL, 0xCBD6DAE58A6F8042ULL
        },
        {
            0x35CAD22DCC399C15ULL, 0xC099EB98177D3DAAULL, 0xCE28BCC0C820BC18ULL, 0x1272B4BC103B1288ULL, 
            0xD670747094D0A9D7ULL, 0x010662BDF6E09A51ULL, 0x9719558A8190B38BULL, 0xA782E13691606016ULL, 
            0xD1698DBA79A32691ULL, 0x9F900DF1D711EB9AULL, 0xB7704FEB659524E1ULL, 0xD9AEFE9F6D1F2EF1ULL, 
            0x1AA8505BF8BF2C10ULL, 0x3C3C9690121A718BULL, 0x6FF3BF737B9F4F03ULL, 0x9A6AE37FDEDB630CULL, 
            0xCA54E7BD989F68ADULL, 0x4FCE1286A9EDF5A1ULL, 0x33D5AD22BA945C38ULL, 0x31035F105E0513CDULL, 
            0xDD1AB6D23A300DC2ULL, 0x605E3F7EA9971BDBULL, 0x583EFC9EC4207E3CULL, 0xE3144D1D110A75C6ULL, 
            0x044E5C01CB5DEE2FULL, 0x82626787F2FCBE78ULL, 0xBCBB554A0F8DF6A4ULL, 0xFE910C1ED31F58B3ULL, 
            0x76A95A1119075FA5ULL, 0x978997625F411938ULL, 0xD003ABEA70A95BA0ULL, 0x478199B3019B17C1ULL
        },
        {
            0xAFC5854231DF3CD9ULL, 0x6E98211A0E35219DULL, 0x59F95DB850854B93ULL, 0xE2E568648ED9196CULL, 
            0xD43EF3E2510B19F3ULL, 0x5E32DED7E3BA1F78ULL, 0x915D0C854B4BA31BULL, 0x216586CDFFCD78E8ULL, 
            0xB11D503A17CF3917ULL, 0x7692F38A0B95AA9DULL, 0x7A315AC4386424C9ULL, 0x2B27A4693656ADB2ULL, 
            0x47F4BE7E0997E7ABULL, 0xFD141DCB137A3BDCULL, 0x731185B02AC1DA63ULL, 0x7BE7710F34F56866ULL, 
            0x5BEE0611AEC30C68ULL, 0x12F8F7686E0AAA27ULL, 0x45671C686D5AAEFCULL, 0x14ABC9AC182DC826ULL, 
            0x178C7947222E70E6ULL, 0x2F7D8DF1A3AFF2A3ULL, 0x219326EB46D288F2ULL, 0x33B1843551D09269ULL, 
            0x832EBA03555ACC99ULL, 0x51AC9E327D3F5FC8ULL, 0x7AA7A7908C7C6B40ULL, 0x6DAF706A60DC82F4ULL, 
            0x8FAFAC4F7D7E7967ULL, 0xB261060DB45E516FULL, 0x7BD573C9FDED48C8ULL, 0x15FE0845D455DB5DULL
        },
        {
            0xA5391EF342EC58C4ULL, 0xC7D7248C79EDFA72ULL, 0x38436F4230C8BD9BULL, 0xA23BE1583DAF6922ULL, 
            0x2C69C5C2E8804552ULL, 0xA304CC1514943ACBULL, 0xCB36FF9C1409A5E5ULL, 0x22E15CBE1C86092EULL, 
            0x764E41C4878BD130ULL, 0xFCAD49C6DA601D99ULL, 0x0C76F7ABD7C19F76ULL, 0xF53B826C541C33B2ULL, 
            0xB88A07BA4554B16FULL, 0xE5F930FF013194BBULL, 0x7C36860A4127378EULL, 0x6E9131A48E90D3AAULL, 
            0xDEF43375F724A2F0ULL, 0xAA3339CB3D1F8DB9ULL, 0x545FBF0CF18E433FULL, 0xA0080B15889D9EF3ULL, 
            0x8A9372ADBFE71C49ULL, 0xFCE40AB02B4AE6B0ULL, 0x7ADC79BE8A120D05ULL, 0x82010D0A90837E57ULL, 
            0x7DF35278DA58D579ULL, 0x14E706BD297C193FULL, 0xEF58463C8328C5A7ULL, 0xD35BB4EE2E185104ULL, 
            0x462A1D7A1AAF9120ULL, 0x833F08C6C60791D8ULL, 0x0D2A0EA84669F38DULL, 0xA0D58E4BE699FC27ULL
        },
        {
            0x8C6D11D6C6FE9C41ULL, 0x39DF68FF3476BD6FULL, 0xAA1C47C9C691D359ULL, 0xD466C201C37607F8ULL, 
            0x587BEDFFF0A1BFD5ULL, 0x95D6C4F5B6BBF561ULL, 0x4E4B8213C8ACE73EULL, 0x22F159B075FA43E4ULL, 
            0xA601805A1F3944E4ULL, 0x105ADA6F8A4C338EULL, 0x527E206C07274A23ULL, 0xAD46A9F6A28B1E61ULL, 
            0xE11BDC83D2985128ULL, 0xEB40688DC14DA7E4ULL, 0x9886B3852B76FA1AULL, 0xBEA2387CE7A7DDB1ULL, 
            0x92429F4E6321AC8AULL, 0xF4AF876D5E14912FULL, 0xC47C5B168319ECC7ULL, 0x299F54271023C3C4ULL, 
            0x213B16330F3F3B8EULL, 0xABE1B73282CD34D7ULL, 0xFFDA32B89DF5B2DBULL, 0x0692264F98DAA2DDULL, 
            0xFA65484A8833527FULL, 0xFEA79B1C85899010ULL, 0xF2657B4FA9ACD5D1ULL, 0x98A62FD68A98F96FULL, 
            0x12085E198F31160DULL, 0x430517DAEB9CAA3EULL, 0x421834E5DDB33C5DULL, 0xE28117DE3E79D766ULL
        }
    },
    {
        {
            0x022006A400D1AFF3ULL, 0xAFC2655D25DC857FULL, 0x13D9C7EE67F02225ULL, 0x03E416EA8841DFCDULL, 
            0x173F1AD47982F3CBULL, 0xE488D8C146E78C6EULL, 0x98ABEC9DDCFC5D38ULL, 0x1B0BC72EABEE1489ULL, 
            0xD9F76F285C07AE3DULL, 0xB74411C2CF8B24A1ULL, 0x5F0F212883BA3EC6ULL, 0x74629A56929698C5ULL, 
            0x8DAC79121F19717DULL, 0xF1CC2DD57AB8BF62ULL, 0x39B9C25ECAE5DE25ULL, 0x965B07233877D7EEULL, 
            0x24D9D77496E62640ULL, 0xFFC1FC03546CAA7AULL, 0x9D32783E089ED900ULL, 0xA5B5EEF7199CD6D0ULL, 
            0x159DBEE4416CB997ULL, 0xC0F9ADD5A8D9FD25ULL, 0xEF354C61C53E1B44ULL, 0x3751551F545138CCULL, 
            0xF7A5194323684257ULL, 0x06BCC407F16E6101ULL, 0x44CEC832ECBF588DULL, 0xFD4F9B598093161DULL, 
            0xDE65288900938A3DULL, 0xA37A1A351AFCAEB0ULL, 0xFAC6E039A799ED3CULL, 0x4B77447FFA0A2EB3ULL
        },
        {
            0x80A1E97167D2F9A9ULL, 0x493BFC602A4EEE77ULL, 0x5CA50C98E79C57F1ULL, 0xEFE2D5AC6B9A5D0FULL, 
            0xD0102E72783F4060ULL, 0xC0280CE08AE47A93ULL, 0x0EA52873CB6B432EULL, 0x04BA01FBC2A2E90AULL, 
            0x73B7966103462195ULL, 0x1C85C70A1E9CEC08ULL, 0x4DF84165721172FBULL, 0x3B8001ED8F544142ULL, 
            0x3124F3193347A42CULL, 0xF972402359D38376ULL, 0xB0BFE2272A611982ULL, 0xA89AAD1AFCB65509ULL, 
            0xF19C44F9E1F07BDCULL, 0x00BC3C1D177823F0ULL, 0xF1CE32E2D17FF176ULL, 0xA6B14F51DC5B064DULL, 
            0x905AB90C92828EF5ULL, 0xA066CFA926B4C8E4ULL, 0xC76E1D0CCFE9A478ULL, 0xB38609012654EAD2ULL, 
            0x63B1D507BF172543ULL, 0x869141AC9ABA6730ULL, 0x6869267AE152FE15ULL, 0x210C0D0BFE36C86AULL, 
            0x68B0048AB26D731FULL, 0x0C4C2F6629632F9EULL, 0xC9C7AB21EC2C5013ULL, 0x66695C37F7760179ULL
        },
        {
            0x1A0575135355650BULL, 0xD9B6382AC23BA8A4ULL, 0x4EFE5D78133B1ACFULL, 0xFB4AF7B518AE0358ULL, 
            0x039727D171FA984FULL, 0x0811F6077D4F69B8ULL, 0x74D5DE967D706666ULL, 0xB197D737F53FCED9ULL, 
            0xF09D9C8596AD88C9ULL, 0x762B39DA5A1C2847ULL, 0x6405C44C50A9ABEDULL, 0xCCCF40B6AB77F936ULL, 
            0x899C6CADB05A7E6EULL, 0x480FCBADA0EBD454ULL, 0x490EB50B78D6C68BULL, 0x640A1E17E868BAF9ULL, 
            0x85E7CA524CDE88F9ULL, 0x19432C2836F06DDAULL, 0x8DE873CE6FCC742DULL, 0x44A3909190E27E2FULL, 
            0xB8BEC4BECE24663DULL, 0xC25BF39A9C81749BULL, 0x01C4A0C3A15B2189ULL, 0x689BA66CB564D29CULL, 
            0x2FA7A4A2726ECB1AULL, 0x71FA4104F552D468ULL, 0x8021243EACC29C4CULL, 0xE0E0666AD16F2EF5ULL, 
            0x2076E763C25FA671ULL, 0x48A966E72DE46243ULL, 0x30CAED2FD5EF4CA0ULL, 0x10FA7B666D884E4CULL
        },
        {
            0xDF4FE56168B9351EULL, 0x5DF0D1A835BDD2D8ULL, 0x197C7CEC7FDD79AFULL, 0xCDD8A5683AD18803ULL, 
            0x99B05A40A30E6CBCULL, 0x2F3854A5BC788BDDULL, 0x841ACFE653141C2AULL, 0x35EDD3D1F1DEC647ULL, 
            0x4F71282618F2AA0AULL, 0x73B83612D4F067AAULL, 0x0483FE1E7C0679FEULL, 0xD97CF64E04BABE87ULL, 
            0xEB18F85B04A0D3FEULL, 0xDEE3E37DFA571389ULL, 0xEC3F97724914D985ULL, 0x927D40935BEB341DULL, 
            0x2113A1F8E2A4D921ULL, 0x417F71097809EE60ULL, 0xB4017B7EA7C1653FULL, 0x77131C6D59F7331DULL, 
            0xDE7A123843CDB394ULL, 0xE1EBC2DB3E73AFB2ULL, 0xC64A0022DF10979EULL, 0x97676E0D744B3A23ULL, 
            0xC3C379C0DE2B0B03ULL, 0xF15FBF61C2D1DB8AULL, 0xDA955CF8D7452BEAULL, 0x4F8C9E70A33DA61CULL, 
            0x1633FE08A036B5C4ULL, 0x275F1790D6740C00ULL, 0x88E7183B6A5499B6ULL, 0x43CD3491EC166651ULL
        },
        {
            0x224EE70111F71F0BULL, 0x771A746E5ED44CB3ULL, 0x6C2CF5FD3ADCC5BDULL, 0xD0446E93E082D337ULL, 
            0xA40557ABBB2E1149ULL, 0x0CAFE4CE8C9B4888ULL, 0x020A57CF3FD5A67FULL, 0x1C24208B6272E2F4ULL, 
            0x91099C119A63762EULL, 0xC19323F82471FA85ULL, 0xD619CD18FCF4D57DULL, 0xA43A2CF16F3E6A32ULL, 
            0x827F9E407C0959B9ULL, 0x4471D09B5E891F5CULL, 0xBF3D26D9A084AA4BULL, 0x1B54CE5326858000ULL, 
            0x8A5E93A9A5BA86A5ULL, 0xA287EB09E79DC1BCULL, 0xFB7B92B16D1BD180ULL, 0xD8D730538B4975BAULL, 
            0x15DAD5006071A9DCULL, 0xDA0D39AB3E019591ULL, 0x9FA88A5253B0B6B7ULL, 0x0755E7446182E576ULL, 
            0x543FC0C39E8B6C64ULL, 0x87C7E54EF6B048CBULL, 0xC589EE7429EE1DA7ULL, 0xC2B5AC15BC307D1BULL, 
            0xEBCD0CFF286756C9ULL, 0x0F4367C1812A33F9ULL, 0xA1EAB43AE16E9C52ULL, 0x7E7D033CEC63A2ACULL
        },
        {
            0x1A04C242AE9FABF1ULL, 0xAD82347F3281EFBDULL, 0x421784B84931A1CCULL, 0xF3AF68FF4FB122B4ULL, 
            0xF67F2A9F4E29E598ULL, 0xCD5FCC1DEB413773ULL, 0x4203FA28F417DAA0ULL, 0xE5FA7996BACE8D3AULL, 
            0xF1BDD48DB2F0B67AULL, 0x84255F44B5B0DC26ULL, 0x44195A02E5001F37ULL, 0x8A16AC4E4EFB6864ULL, 
            0x06C9417477197472ULL, 0xFB5240DA5C2D3816ULL, 0x883BC9FEC32D1814ULL, 0xEAE2A886EBA48B1CULL, 
            0x141BA069DD2B563FULL, 0xE89E5AC12AA8F748ULL, 0xA0AD8794B4CA405BULL, 0xB811901342A1EF69ULL, 
            0x1A94A9CB143BEA99ULL, 0x34D3FE305E240447ULL, 0x564C72FB828261EAULL, 0xCB77BF18F07DDAE3ULL, 
            0x910D45787638F71DULL, 0x66CFBC57D758CE71ULL, 0x3CFE042A7B53DDF5ULL, 0xAFCDD1188D8F9C08ULL, 
            0x54174E54001EA870ULL, 0x20D46C2B501FF72DULL, 0x19971A1CBBD3110DULL, 0xA43E5E565F66EC61ULL
        }
    },
    {
        {
            0x4F5ECE40E59F1B7DULL, 0x30EB503BD9F87244ULL, 0x8A6ACDDD8A0BD74FULL, 0xE52E13DDA8A86E71ULL, 
            0xBEB8E8350D458C48ULL, 0x1558F9418F88F615ULL, 0x3DE21E96F78B9D96ULL, 0xF69C584C07299B7DULL, 
            0x365C38645C637916ULL, 0x867E4E5FA7E470F9ULL, 0x7A320461DEDF7B39ULL, 0x32855796BA8231A2ULL, 
            0x57E19EECE0231348ULL, 0xFF908AE4BA07FF56ULL, 0xC91BE73E1ED3EDEEULL, 0xCE1A15DAC6B2FB22ULL, 
            0x224F5202DA0623E0ULL, 0xCAB94D9687C802C1ULL, 0x9B7CF06A0C870F85ULL, 0xD2D3778E393163ADULL, 
            0xD459BE5E7E7282E8ULL, 0x024A92D57098266FULL, 0x40467834E27FD0C0ULL, 0x70A5DB8E3B92C9FEULL, 
            0x7DBAC6C968F3CEF8ULL, 0x7C5AE0B80951C24BULL, 0xF3CFD738FE980B92ULL, 0xDCB39E0E9922974AULL, 
            0x4235A0B201AF46ADULL, 0xA93AAF9ECA99915BULL, 0x43B026BE3B4F1EB9ULL, 0xD66287FE7D31EF79ULL
        },
        {
            0x3F2F38CAFCBF38DBULL, 0x8E84DAEB4145402FULL, 0x251C81DB13959F94ULL, 0xDF379A9DAA26E258ULL, 
            0x39F1A745B93559EDULL, 0x50BB48DD8E2393CEULL, 0x07E8E27310D76DD8ULL, 0xE587BBD49D288C36ULL, 
            0x3608CA87C651C7D4ULL, 0xA5B8B003327F2EA9ULL, 0x3261F0CA7BB47599ULL, 0x53BDA538FF32C905ULL, 
            0x5B6074FF0A03413CULL, 0x1940B414DD452746ULL, 0x7352D23BDDB74256ULL, 0xEAB3CB1F0048AF98ULL, 
            0xF533770312BD3EB8ULL, 0x82757B8B0A1EF725ULL, 0x893B1669280F75A7ULL, 0x61E844BA487CB43FULL, 
            0xE37007710131A5BBULL, 0x8C67D40B6FD9034EULL, 0x0DFA1C967C53393FULL, 0x3B4F0576FC76E004ULL, 
            0x6F599A62D1F4FA6BULL, 0x8918639EE98BE6D4ULL, 0x9B241B28D54BF1FCULL, 0x261F23E8213C7F23ULL, 
            0x58657A60D6BF6EEFULL, 0x575D034045503AC3ULL, 0x2EB7977908FF60D9ULL, 0x8C1AB60439591761ULL
        },
        {
            0x3D6010F3C235657EULL, 0x0C934E3D61CF392DULL, 0x27141F20240EA00FULL, 0xE7792AD446C077F2ULL, 
            0xF9C9EFC866783716ULL, 0xAAFAD134216D1521ULL, 0xC4DF05EB05D8C904ULL, 0x90B185A01FDCEAAAULL, 
            0xA8B6FE58DC3932F4ULL, 0xA3A73B17F30C8039ULL, 0xD3CF5FB3BC54968CULL, 0xF01E61E0F0BA0B27ULL, 
            0x3B771A16FBA53B32ULL, 0xD1FCEB0E88A9BDB7ULL, 0x0F520AF5F4B9898EULL, 0x493A2342640F69FCULL, 
            0x775CD1FD66D2371CULL, 0x8895965D639102DDULL, 0x310D608626E2454DULL, 0x775E7F8F5C2A024FULL, 
            0x44D54CAD9E4CC72AULL, 0x58EBBF7F5E0DE935ULL, 0x738ECED0FE982612ULL, 0xF259076F35175485ULL, 
            0xC68B05AC36868E9DULL, 0xA529170EA7918144ULL, 0x15D1E558C5DC4BB8ULL, 0x8DFD5EA2E43E5131ULL, 
            0xB45941F915E6CE03ULL, 0x8DD2BB7BB8E39664ULL, 0xA3653A8F9FDF7E49ULL, 0x569ADF8E3F422874ULL
        },
        {
            0x2A85A475BB5E3C74ULL, 0x037C00AB00D3249FULL, 0x3A3BE1B4B76A6284ULL, 0x2211B1B346789B0FULL, 
            0x1E56BE03BBD8A7BFULL, 0xDB52CD479C9789F5ULL, 0x42C6865128063E74ULL, 0x82DBF23B4DDA0628ULL, 
            0x9D2547FF41B9DF94ULL, 0x512F95D8433CD122ULL, 0x0A4067A08AE54D4BULL, 0xA4D88200795B5FBFULL, 
            0xDEBE4F4879B031B5ULL, 0x427CE1062565FDC4ULL, 0x994F7102F9F64A37ULL, 0x58ADA3C4EDEB2BF8ULL, 
            0x04F755437AAC119BULL, 0x173250E70B5C2C8BULL, 0x4CDAB3DA015AF075ULL, 0xC89B26A8902A6F8FULL, 
            0xBB77E50053C2C055ULL, 0xFDEA2E60822535AFULL, 0xE9D06FC45B6EEDEBULL, 0x5D9D449B92519058ULL, 
            0xFA1FAB271656D551ULL, 0x239CC3F96C0BB282ULL, 0xC60F77C9F88EB21EULL, 0x641FADED80EA0E5FULL, 
            0x858AC788757B7602ULL, 0x5A4361BB89BF695FULL, 0xAE066F98B6778E0FULL, 0x20D39585759904C2ULL
        },
        {
            0x6C3192E451DC8BD9ULL, 0x0966827CDEDCD1B3ULL, 0x2212BC69E1F27FC9ULL, 0xA38610312D809C90ULL, 
            0x8C442A5A84B0BE00ULL, 0x4FCE9A37591848A3ULL, 0xF2CEF29CEDAA7612ULL, 0xA11C7BEDBDEA3BC8ULL, 
            0x5EA4FA49F950BC25ULL, 0xA691004B8903E106ULL, 0xD4E1C0188CACFD1EULL, 0xF506E7979EDF3845ULL, 
            0x487D482C5C6E4B8DULL, 0x7FDD2BFF9241992DULL, 0x6108D7116E49E8CBULL, 0x9C9629773D3AC0B7ULL, 
            0xBBC7EA73F7437DBAULL, 0x11F92B7A2280C5BDULL, 0x758E56C1DDFC7AEAULL, 0x4AB966EB505B8EFFULL, 
            0x48DEB10688B43163ULL, 0x4BF3D5A5D8490589ULL, 0x2631C9C5D3009023ULL, 0xF413350D69AA3494ULL, 
            0x4A13600DA6DDD129ULL, 0x63B4949FB9EDE35FULL, 0xBD5DB3F91F9D6D51ULL, 0x4008592D1028274DULL, 
            0x9918D4E525116091ULL, 0x2C618969DBDCFF77ULL, 0x98E38A137F1B141BULL, 0x2F6E10BF7CE79FAFULL
        },
        {
            0xFD8DF4E89A9741B4ULL, 0x97900A7A5C19F2ADULL, 0xF927C739A0A20557ULL, 0x77AAD1C26D404B33ULL, 
            0x417E0F65D11EB5ECULL, 0x4479685EEAD3F468ULL, 0x5DFB688569A6E4D1ULL, 0x1F1643F0016AEB1DULL, 
            0x664CA2AD46A0EC89ULL, 0xDAF7A2E7238190DCULL, 0x5E219BFE86F5F9D6ULL, 0x1B89E1BCDD84EE7DULL, 
            0x720A5D9E926B5207ULL, 0x4741491EDFAE3931ULL, 0x659FF35389E39766ULL, 0x7AC74B9ACD9857B6ULL, 
            0xF66FD76A060379E1ULL, 0x6B1957058A665435ULL, 0x9639520C78856F76ULL, 0x99D4DA8DCCA01F2BULL, 
            0x1AF488C6B8B597DFULL, 0x1374AF30527AC217ULL, 0x84423D49F0C855CFULL, 0x7060FD5737A21688ULL, 
            0x8DDBACCDC5827EC9ULL, 0xCF2A353B207CF179ULL, 0xB57A5EA371C9F635ULL, 0x067FB689C09E3FE0ULL, 
            0xEECAF0976255B4A9ULL, 0x6EB2CE9BBD607DAEULL, 0x073FDA1A8AB56904ULL, 0x1252EC50489E61D0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseBConstants = {
    0xF4703B38C3740E1DULL,
    0xC6A85EEB02E014D1ULL,
    0x2FCB13A1B7FEBD6DULL,
    0xF4703B38C3740E1DULL,
    0xC6A85EEB02E014D1ULL,
    0x2FCB13A1B7FEBD6DULL,
    0x0C0733EE3E73DC81ULL,
    0xA3436311829CC58DULL,
    0xFD,
    0x45,
    0x20,
    0xAF,
    0x97,
    0xB4,
    0x2D,
    0x9E
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseCSalts = {
    {
        {
            0x179B36A6483D2992ULL, 0x5CFA973864C9A7D6ULL, 0x48FB9246B10B06C3ULL, 0xE256ED94557F7583ULL, 
            0x0E3362EDD1F63156ULL, 0x767C6E0363E3C42BULL, 0x69BA96B61FB53B7AULL, 0xE5117F3A08FCB0C6ULL, 
            0x356D0B08EA3365E2ULL, 0xD2A161D9513AA87FULL, 0x68B45C9DF39BA358ULL, 0x9E756C018A828AC1ULL, 
            0x1A31FCA7852C6AEFULL, 0xB201B9C68A524BB4ULL, 0xE1E26DC31F9A6A79ULL, 0x2B6664A48D560595ULL, 
            0xA555CBC262AFA36AULL, 0xCEF2A06750B3F1EEULL, 0x8CB311A6759F2FECULL, 0x138FE96EC9241AC0ULL, 
            0xB7FB5FA094A92850ULL, 0x223B2165C9457B3EULL, 0x52B343D6486F1B5FULL, 0xE7FAB9FCBCA51256ULL, 
            0xB45C7E7EEF11AC81ULL, 0x5A90E7C0B8DF3B29ULL, 0x6DF3B46BC47849C1ULL, 0xA4BEAF457602B6BFULL, 
            0x3F109321D9BF4E6DULL, 0x75C164E6D1350338ULL, 0x8C415EBA3A042E89ULL, 0xCDE474F913CBB5F9ULL
        },
        {
            0x8149AFCAD9E1DFE9ULL, 0x41EE5ACE52668994ULL, 0xE832DDDA0EFCCF8CULL, 0x6D79605A2548BF9FULL, 
            0x03689DD999AD5A9BULL, 0x91021B709FF12728ULL, 0x40381C5F16E10E6AULL, 0x4F838DB2F602922BULL, 
            0x195E6ACEF0EB283AULL, 0xE4017ACB0C673D0BULL, 0x834D73F801AA9DB6ULL, 0x04B05DA33C0212EBULL, 
            0x23C4CB5F90EE12CDULL, 0x891ADDB262D343F2ULL, 0xE8684DB99D1CFD88ULL, 0x7901C8999183A7A5ULL, 
            0x3D4AAFEF0D2C1049ULL, 0x4476A0AEF94AD823ULL, 0xF2AD8DDF9BF7F4E9ULL, 0x924D5F4EF14EC153ULL, 
            0x3AB5864B9BDC065CULL, 0x0580BD0D6504480BULL, 0x7EDDD0EF29FCD6BEULL, 0xF7030532EE4A67F1ULL, 
            0x1DC327DE033A9023ULL, 0x9861255D6203F9D3ULL, 0x3A9260E0A6E90ED6ULL, 0x13F74B1531C41B91ULL, 
            0xC74011A616DAE97AULL, 0x67316338E8595B92ULL, 0xEA030112543DBFE1ULL, 0x12C54627205B98CCULL
        },
        {
            0xF179AF3329D5FD10ULL, 0xC8D37A59CB6E82BDULL, 0x74BD749A029E53ABULL, 0x8507C00082EADECCULL, 
            0x8E9E25BA40B26D17ULL, 0x305A7CAFBEB4DBC5ULL, 0xEC3D129A2801D2A5ULL, 0xE3F724753FAFA87EULL, 
            0x2B204B108679751FULL, 0x7C4CC64820BE5798ULL, 0xD097D64E7041A716ULL, 0xEC6C997671934A1BULL, 
            0xFF9B648DAF9764DCULL, 0xEFD9458A74742A61ULL, 0x7F57B6D0C0E9CBAFULL, 0x4AC93C7436053C32ULL, 
            0xAAD018211F25D09EULL, 0x33AD344526317013ULL, 0x1C002F0C70EA1CC3ULL, 0x396B549B96FFCCDCULL, 
            0x523D55D6DB42192CULL, 0x2FFF8B5513A5146BULL, 0xD53FA5333F28FF3DULL, 0x08613C9626E46986ULL, 
            0x492B3F3F54277FE5ULL, 0xFAFD638C1C456462ULL, 0xB122DB34F842F722ULL, 0xC69BFE12E9E81AC4ULL, 
            0x72E6E081BBB4988FULL, 0x2B8D0A314744061BULL, 0xA5121ED791B5BD39ULL, 0xD406AADB5FDC89EEULL
        },
        {
            0xE94A9BCEA72B88F5ULL, 0xE3B67FADF558C3F0ULL, 0x7580E07A8F738EFAULL, 0x30BB1B489EAB959AULL, 
            0xEFAE8A7F65E672D0ULL, 0x76C41E7DF454226DULL, 0x3C372D51A8AB848AULL, 0x57E4AD335A43848DULL, 
            0x749E79D55035981BULL, 0xB4835F42D6BCA1ADULL, 0x050402A27125F367ULL, 0x9FC1F5412EB8888EULL, 
            0x7736DD3B9C22853CULL, 0xCB72DE54B45877CCULL, 0xB61383248E2717B8ULL, 0x0E7EA95D547E2B38ULL, 
            0x3CE1C8C22BB89A36ULL, 0x7B6B80143A5ACDEBULL, 0x3B5DA8A216EE0BE6ULL, 0xD8F685B84F19BC33ULL, 
            0x3CA75E62C289F6DDULL, 0xE708EFB33057904EULL, 0xF33DB0716E655ECBULL, 0x86D15BA541EAD5B0ULL, 
            0xFEE3F3A0C630C3A0ULL, 0x6B5E3C17FEF8433BULL, 0x72B487F2A58D1DD1ULL, 0x33D1A9C06C81BF39ULL, 
            0x1657A7A4798B9B52ULL, 0xF77597A524B5DACDULL, 0x177E9D10902D4A10ULL, 0x874FA99C422A52F2ULL
        },
        {
            0x9AA5E9B7E2CA4EE9ULL, 0xC3084AE788C1421BULL, 0xE0B4317ADDC85F6CULL, 0x2243A97FB8ACE4CAULL, 
            0x9303A6D53F9C8B27ULL, 0xDF7ED284C9855A41ULL, 0x9E1F778A5F2BB555ULL, 0x9AB09356DD6D1051ULL, 
            0x6E73A17B78824EC4ULL, 0x3EACC176741AB833ULL, 0x6AC7B260789221EDULL, 0xE4BE61AC5D37FC89ULL, 
            0x413C8F650D8E0ED2ULL, 0x38B9E89971D5F2BDULL, 0x6554B7ECEF59F95EULL, 0x2AE988A900326D5CULL, 
            0x14AABFD2AA308EC4ULL, 0x835E994D2C8EC074ULL, 0x761F82EE65A2D90AULL, 0x71FCAC43D272C9CAULL, 
            0xC2C742EFC89FFD23ULL, 0xC62EA8C15722AC8AULL, 0x4CD17325D9233A33ULL, 0x41628712B6EE1CB9ULL, 
            0x074A953FA22F3138ULL, 0xC3A81FFF9F01AFD1ULL, 0x831FD9D1B44CFFBFULL, 0x0D5C5798C326BFBBULL, 
            0x8C1B78F055F644EBULL, 0xA2385AE6C985CF90ULL, 0x938850FC1C7ECAEAULL, 0xAFB5208CCD2DCB31ULL
        },
        {
            0x4AA81805DDDA4124ULL, 0xE1BC62DB79006A04ULL, 0x15B80410AA0E5686ULL, 0x4DB6C3D8C53F0A5CULL, 
            0x2ED5F3CB611009D6ULL, 0xA9B798A995D874D0ULL, 0xD42773FEF99A42C6ULL, 0x77956E2977D1D0BBULL, 
            0x847D12A21A6E3F73ULL, 0x7E0CAF57511CB2B5ULL, 0xE67C83A940A09A61ULL, 0xB101A989F240EEFAULL, 
            0xE1EF08DB9D6869B8ULL, 0x27EC7A5A94897994ULL, 0x8D2D617E948AB9D1ULL, 0x8DD2E9F693B945DEULL, 
            0xBDC78AD96610E839ULL, 0xFD1EE935C36F0870ULL, 0x46D7E61FA828643AULL, 0x6640BC7F0B13500FULL, 
            0xA43DA0EE7DFCE39EULL, 0xDE887FC09795278BULL, 0xD38CE08C3D73BD66ULL, 0x2FAA7B3491720C98ULL, 
            0x67E23076CB6CACE0ULL, 0xAE9E0BCB93E6D656ULL, 0x9BFB3F6A9E7A9E52ULL, 0x6F19A801C3B80E65ULL, 
            0x53C3E2DCB20A0E6FULL, 0xFFCED5EA8E5201EFULL, 0xB8651631EADAFD33ULL, 0xD65855B931C19959ULL
        }
    },
    {
        {
            0x5D31DFFBE0CBBB49ULL, 0xB4D5A850D91E29CAULL, 0x45EB3CD47ED67841ULL, 0xBE81457D2FD109A7ULL, 
            0xD9883B273377A55FULL, 0x739DCD7C4A1A3190ULL, 0x02A9416032A7184DULL, 0x83D611645E8E6EEFULL, 
            0x6B66623E4A87FA5BULL, 0x47A60CF379D51153ULL, 0x27761FB07AD8FECAULL, 0xC39C9FAB7F26734BULL, 
            0x52CB9CD220ACA467ULL, 0x9C4E8670F545E67AULL, 0x06263CEA30751426ULL, 0x8DE14FCD3EA4B1EBULL, 
            0xF79D2F5F09746F68ULL, 0xBA8D9BF7B8FF11A5ULL, 0x8E0F888F48D79122ULL, 0x1EF67DB2A87C78ECULL, 
            0x9918495960CFD42AULL, 0x0CBD594D138197E5ULL, 0xEBCEDFA66FC6E105ULL, 0xAE6E3E62920E5FF3ULL, 
            0x399824DF794E887BULL, 0x316DB5878DF796D7ULL, 0x4CB86FE02131AD62ULL, 0x95A0CCDD5394145DULL, 
            0xB3DBC06A52609D89ULL, 0x028EED871172FDE6ULL, 0x24C97AF307F575A6ULL, 0xC75E3698EC2F932DULL
        },
        {
            0x8CF13C2CA24EC983ULL, 0x60DBF0A83FD9674DULL, 0x79EA197246142D10ULL, 0xA19C108C8A449B47ULL, 
            0xF1465BD548AB871BULL, 0x57EEC1BFAE60838AULL, 0x9815852BC750E97DULL, 0x44702F87FF7C47D1ULL, 
            0xB820F90CC7667AA0ULL, 0x2657182E8E57E5D0ULL, 0xF4CD1D5EFB51D3CBULL, 0xEB9074FD5C3DB100ULL, 
            0xDE993E2C6D580004ULL, 0x9CB82EA03ECF0D13ULL, 0x36A3DAB7C57554BBULL, 0x46BB25C97302A608ULL, 
            0xA5AEC9E4849B6573ULL, 0xEE01D8F481E14093ULL, 0x43BA22419E646CE2ULL, 0x61A0E1DB20D73283ULL, 
            0x47F75FFE203A012CULL, 0xE5995AC752BC3246ULL, 0x96FD7EE15AE7D1A6ULL, 0x2C2E8EF279819B1BULL, 
            0x07B58DC6EDB1C4EFULL, 0xF56058660935BE32ULL, 0xEC7F94DE6FD5E4D9ULL, 0xC7FED2714B06F3F8ULL, 
            0xE5D043ED24861A3AULL, 0xE77964A4B5E27B98ULL, 0x9CBD71DD1C8EA886ULL, 0x94BD535FDDF144BDULL
        },
        {
            0x1C09FEE86D9A5538ULL, 0xBB65F1E9F331CBFDULL, 0x27750C934092746FULL, 0x89687C3A21E5D92FULL, 
            0x38395BC52070D442ULL, 0x3F763A02C2B82EA8ULL, 0xB901239272834F63ULL, 0x8876FCA1ED730CA5ULL, 
            0xA44E5FC8E1147DB6ULL, 0x9E8BFE44807FE396ULL, 0xE4DF84805A38E660ULL, 0x02DC9FEA5836360BULL, 
            0x51014A85C8CC08DDULL, 0x0F97E46E1B12A3BBULL, 0xB1E9F1CB4DD743F5ULL, 0xA1DB95E87D24571FULL, 
            0x449AAC017410CDF5ULL, 0x3DBCAC0DA4A7695FULL, 0xB8634393DB093467ULL, 0x9046E643DC8E6FFEULL, 
            0x35F8AD87C7FFCE9CULL, 0x4BD1C56E725B00ECULL, 0x3C361152D5400F33ULL, 0x8E22DC91104F2A5DULL, 
            0x198DFFD55E6758D2ULL, 0x75C18B899AC8962EULL, 0x0BE95D4F405CA3A2ULL, 0xB4AE8F19B539196AULL, 
            0xC7D01877722D2E59ULL, 0xD9123A87A2F4E55EULL, 0x4DC10A2FC091CA84ULL, 0x5907418530EC9E70ULL
        },
        {
            0xDAFA64FA7420E421ULL, 0xF5585C2CB1B63CA0ULL, 0x33936352E5A96F05ULL, 0x7184D32108E0B3ADULL, 
            0x1F83AEDAFED4F716ULL, 0xC7658CD1C577FC1EULL, 0x9D511EC8FC83A69BULL, 0x5D987E131E4871C5ULL, 
            0xB2BA24D27A4E543EULL, 0x890521754B14537BULL, 0x4CEC31C12459E89CULL, 0x0C12A4C4E549C914ULL, 
            0x277580019C16D7A6ULL, 0x5728635F4A6CA50BULL, 0xF8CFA74A32579889ULL, 0x0407316CF74E487EULL, 
            0xE66181B484F3FB97ULL, 0x936C359E531ED318ULL, 0x2CAA46C3F4C8CB1CULL, 0xE7A233EEF20F0D6AULL, 
            0x3D70797F2BB24285ULL, 0xA794696CDD5F9F63ULL, 0x1546F3525D8EF081ULL, 0x201DEB47B2114BF7ULL, 
            0x0B71811B02CA1B76ULL, 0xBBD20973E691360DULL, 0xD3C4C281CCB2ACABULL, 0x056DB55B7043875DULL, 
            0xB3A97BC5D5462F0EULL, 0xFE03F3D2C3E8D8FDULL, 0x2CCF139338BE0B22ULL, 0x88D152E2696D9232ULL
        },
        {
            0x0242DEC9332A7A52ULL, 0xDD12ED62A238B36EULL, 0xAECDB8AEFE6FC41FULL, 0x47A4A8C25A849070ULL, 
            0x0389EACE240964C9ULL, 0x77AEE9C98749F8ABULL, 0x46077D89935A8E83ULL, 0x1027F5FCD568346DULL, 
            0xD13C926BFE8E7E38ULL, 0x5E336A489E759A27ULL, 0x0933706B178BD997ULL, 0x1C01A9F42B829913ULL, 
            0xB93669CBCA0BC51FULL, 0x52C8A446B49D7AB9ULL, 0xE950752E267C7579ULL, 0xBE3E64B6818541C4ULL, 
            0xFA4561E80E808B0BULL, 0x269091B0575252ACULL, 0x4DE91A050A415357ULL, 0x3289285EA2561BCBULL, 
            0xED2278949D9FB654ULL, 0x465FA25FA941A087ULL, 0xFE2879801EFD7987ULL, 0xFD53D465FA350896ULL, 
            0x11757350A2AF7082ULL, 0x405B5175B232CF40ULL, 0x308DD6A11A0B6EA3ULL, 0xA95B7FD56EE52D64ULL, 
            0x899076A1406F1008ULL, 0x7DC7E95C5948AFB2ULL, 0x9E4DD7F3AA26B707ULL, 0xE998D5C0DC5F4006ULL
        },
        {
            0x99BAF57564380FCAULL, 0x31A554E606A58E76ULL, 0x08D604FFD1EFC9FDULL, 0xA35EBA4F40AED5DFULL, 
            0xF0F69F7DAE9E349DULL, 0x7BEC3DE7C270CBF3ULL, 0x55EAA44ADE6C31FCULL, 0xFEE590863209F0CEULL, 
            0x0C2B477E0E942B94ULL, 0xF8FB95D5A20DFA48ULL, 0x46DFF8E5115D0267ULL, 0xAD02C00A0FA3A455ULL, 
            0x29CA50170A0909EAULL, 0x0ED551D6CD345A8BULL, 0x9ED209B9B2782925ULL, 0x90F1D567DD68498AULL, 
            0xCF3E2A8BDF589CCBULL, 0x722B9045FF0D35CDULL, 0x13C0B3E5EE3A3A82ULL, 0xCA14B12E36A7E283ULL, 
            0x0A3D4796711460DFULL, 0xA1BEB34ECCB920E5ULL, 0xC232F1627861D67FULL, 0x28FEA3685D3F8379ULL, 
            0x7DD09D1AAD1C2AFAULL, 0x388002BBBA904E5DULL, 0xB677A942DFE0ABC1ULL, 0x972FC2844CDF65B1ULL, 
            0x9332A278D0E3C9A3ULL, 0x21EAB54B0F7D67B0ULL, 0xEAFF30C00E159569ULL, 0xD16EBB25CEF32F6BULL
        }
    },
    {
        {
            0xE96F4B844DCE627DULL, 0x07191C5CDE24C778ULL, 0xAF1270BC6F5EBEB5ULL, 0x975B6EFE8CBFB106ULL, 
            0xC72857C0C1B7C470ULL, 0xBDBA29201FB006C3ULL, 0x5D7F61408178323DULL, 0x4410FF0B655B164BULL, 
            0x431955CEEF98BCD4ULL, 0x6CCA0D048CB2040CULL, 0x6DC910057DF6DF96ULL, 0xD150A4BAC417C70DULL, 
            0x4BB9209FE9555743ULL, 0x55F72F35B45743F2ULL, 0xF6B239372312238CULL, 0xD6197C962CB724FBULL, 
            0x35CCD6CE64895CEBULL, 0x39F0BCCC6AADA441ULL, 0xB1AFE5BAA4E442ACULL, 0x7B26AEB8FCF18D93ULL, 
            0xAC9AB0976B468486ULL, 0x27EB06B246944C77ULL, 0x403C46C083D3B4D8ULL, 0x20853A95AFF97DE0ULL, 
            0x105FF7D29F7DC7D0ULL, 0x14A1AB5B73505945ULL, 0x1E82BA8E2D824576ULL, 0x52B4BED9923DDB21ULL, 
            0x5B8CE85AE1758618ULL, 0xF8681D6E615C82CFULL, 0xF9F1D65CC8E046CCULL, 0x5F8223F311B4CB15ULL
        },
        {
            0x3873740094733E07ULL, 0x3A35667D2498D452ULL, 0xE8DAF45B0EFF4348ULL, 0x8A69C85BD373C6AFULL, 
            0x6064116E7D5E8A4FULL, 0xCE83CAC08EE73FD2ULL, 0x00ED56F1DFB6C61AULL, 0x25E8CDD9B983C62CULL, 
            0xB78A3287F812B08EULL, 0x7BC87C2B72555D71ULL, 0x1F5950BF9D04258AULL, 0xC36553E6780C2AD4ULL, 
            0xA13C6FE4C47E9AACULL, 0x3382265A2BD0D98BULL, 0x4B743794AB56DAC6ULL, 0x8A1B195217317E70ULL, 
            0x7BB2742CCE558774ULL, 0x70BD7E34295D5750ULL, 0x30A2E9C34F0929DBULL, 0x57B51F663B014329ULL, 
            0x5DE9DA7772984025ULL, 0x24D93E27D8C83785ULL, 0x2A044EDAE04DB908ULL, 0x0D0CD0FD6EA791A2ULL, 
            0x7A48EE511B77B52FULL, 0x0FBD4576DE160F28ULL, 0x0F9EAA62DB97FEDAULL, 0x2757F68989F8A473ULL, 
            0x43F20054F8E7C0A1ULL, 0x5500516D93AA88B7ULL, 0x6AF632797CAD308FULL, 0xFE924D8078AF8817ULL
        },
        {
            0x1D58EA2166519035ULL, 0xB0149F741C4BA4C7ULL, 0x41B585D7AAFB6C35ULL, 0x77AE3D6A6DC8014EULL, 
            0xECACB42A3B32070BULL, 0x6268CC9B981EA379ULL, 0xF82D47A14C892523ULL, 0x329DD9BC6263A1A7ULL, 
            0xD2DD62975124C27EULL, 0xA1DF4810DC3F757DULL, 0x0DE98B953216C9F9ULL, 0x309A22EA4194608DULL, 
            0x85D89EB2DBD26C99ULL, 0x1908DCCA591987AAULL, 0x9929F30A91A6697CULL, 0x8F9556BC9D993424ULL, 
            0x737F5E4642B313CDULL, 0xFC8285B5EF6E5A54ULL, 0x797C369AF48AF177ULL, 0x6D73BF5A15820792ULL, 
            0x99EC1AD7E62483F5ULL, 0xFCC86D045D4A2B33ULL, 0x838F73D6C28509D7ULL, 0x6AFA8F0ADA2CC7F9ULL, 
            0xF96A00D1EE921671ULL, 0xE09497D45C7E257DULL, 0x39CADED24287484CULL, 0x1EAA3227624106F6ULL, 
            0xC3189A258F8C6761ULL, 0xE3AD99812D9B3B3DULL, 0x7B184642FE49FB4CULL, 0xB0497D22897A1678ULL
        },
        {
            0x4C3CDFD1288ED98CULL, 0x165BC255B9837838ULL, 0x685DD470AA6DF83AULL, 0x4D02A4ED28BA7149ULL, 
            0x317D97B4A6F21EB3ULL, 0x41A0CD31486C3746ULL, 0x4CE9E46E9CAEF7BFULL, 0xDC5C2FB25283520AULL, 
            0x3000142BB5035EF4ULL, 0xBA7B5B59205AA3FCULL, 0xD6F7912C7282DE21ULL, 0xB66536F021392DA7ULL, 
            0xD6A66CE93F99D851ULL, 0x3DD8E7030C5D16E6ULL, 0x54C94B69D410B703ULL, 0x2DB3C3586389735DULL, 
            0xAF6C9D2966AF7946ULL, 0xA1641DF01EF73A0DULL, 0xF32F9668EA33CC5FULL, 0x732ED301533A545CULL, 
            0xF575E48CCC18E7EFULL, 0xA320879A7F59ECB4ULL, 0xD84560B2951496C3ULL, 0x9274F651F8010499ULL, 
            0x072A24A99A9DEE6AULL, 0x99AAB702C543A627ULL, 0xA039DAEBF0FF119AULL, 0x92C06FA68B3C1CB2ULL, 
            0xCEF2ED3DE364A821ULL, 0x1976838D85643A36ULL, 0x058BD0D6A732A987ULL, 0x13F491E8CA454301ULL
        },
        {
            0x9F98730F6E677204ULL, 0xE908E68E87BA1C51ULL, 0xA8FC21570220E8DBULL, 0xCD77EE39E324D76BULL, 
            0x4DDBDEE830295E96ULL, 0xE3EB8EDEB0D87B64ULL, 0x371AE7D3F5FDFF4DULL, 0x9A01E9550B2B44CEULL, 
            0x5E18336DC2B1DE32ULL, 0xBE4220013D9D3D5BULL, 0x9E1D643C17261FC0ULL, 0x3FD2017693D5C44DULL, 
            0x3FF776DE0EB39D98ULL, 0x12983BCC63609D1EULL, 0x92BBA016BC082697ULL, 0xF4AC106FEB2B9218ULL, 
            0x8621D74B404D08E3ULL, 0x151C6CE129724152ULL, 0x1BC59ACC2BF4A2D2ULL, 0xCC4455114C846BC4ULL, 
            0x2E5EF30A09CB4350ULL, 0x7CEFC2AB2C93F6D6ULL, 0x0CA0B72474137941ULL, 0x3D955222D942E622ULL, 
            0x9697BD03BCAA5DFAULL, 0x49F10DA3CC0895C0ULL, 0x0F1DD11CB59165F9ULL, 0xCFDB29D5A183B88BULL, 
            0xE83C92841B1BD2FDULL, 0x7D7E1634237DCAEBULL, 0xA2868F3CF3F0B1DFULL, 0x922679508E2814F4ULL
        },
        {
            0x2CFE6C213D86FE22ULL, 0x11FA74A5C4D21B83ULL, 0x04AB2AA467CE7233ULL, 0x77A98278C6940693ULL, 
            0xE32ED2966DA0ED89ULL, 0x7A6F82834BAAC9CAULL, 0xDDF465B35D1067A2ULL, 0x831D34E8926C81C0ULL, 
            0xDAF6F5750B3D0BEDULL, 0x6D0EE986087177A0ULL, 0xDB6174D0C8788445ULL, 0x5B5F73F9A19F81F3ULL, 
            0xFFD47AA1CA21A60AULL, 0xDF8C021E3EF4BD46ULL, 0xB85092D861DDB0BAULL, 0x0A92FDC6B241A9A9ULL, 
            0x6DD08E8CC82E0E1FULL, 0x4B22FCE88216F1D8ULL, 0x60AC3436D047C073ULL, 0x235236EE507BAD9FULL, 
            0x705A74EF8E4E82A5ULL, 0xB58ECF5F13A22DB7ULL, 0xD39AB4BF622F7644ULL, 0x2CEB08166183D47BULL, 
            0x021B4E26E1934CE6ULL, 0x0D6C5F2036541EF2ULL, 0x1ADFC93B9BCF4792ULL, 0x05335F963D4251E7ULL, 
            0x3C87CB89672D43E7ULL, 0x27CB05F66A817EEBULL, 0x74E0D679301BBE34ULL, 0xD1ABBEBB7F13FC6CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseCConstants = {
    0x3AFD24E656D997CFULL,
    0x4D02A2D1E0012564ULL,
    0x0F8D4E0C815703EBULL,
    0x3AFD24E656D997CFULL,
    0x4D02A2D1E0012564ULL,
    0x0F8D4E0C815703EBULL,
    0x53D7BB0B1AD795EAULL,
    0x6DE1DA8DC25F8D24ULL,
    0xE1,
    0xE4,
    0xE6,
    0x9E,
    0x24,
    0xA2,
    0xAE,
    0x97
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseDSalts = {
    {
        {
            0x64869F1D47A70FBFULL, 0x1AAF0D4681AA9909ULL, 0xB1794E98051D400AULL, 0xBF9127D9812B2774ULL, 
            0xC0ACD9C54C293A11ULL, 0xA786F9EDA6909876ULL, 0x0BC3A359A215CBC0ULL, 0x87808546E19F5520ULL, 
            0x6273868E8FD7B0BBULL, 0x72E929A6D3D8A09FULL, 0x2B63E4FA3D015FA4ULL, 0x9AC8301F606AFD64ULL, 
            0x3AD84A9F071E90F6ULL, 0x6C9E4E41C8755BC8ULL, 0xFA2DE2A97F9A7F35ULL, 0x0B294AB87978460BULL, 
            0x1BCEFA7DA4AE9A5BULL, 0xF339697BCB7D3EDAULL, 0xC611681D57DAFCC4ULL, 0x4450BDC91F048AD0ULL, 
            0x0FA1B43E0A01FB83ULL, 0x35A8F44BC595FA7EULL, 0xBE7865E1E0FC75B6ULL, 0xA5274F5DDE3CFBC2ULL, 
            0x24FEB73E7D74DD09ULL, 0xF866BBCA9D1C679AULL, 0x4D133FB4CCA742F5ULL, 0x6E614E59A207B630ULL, 
            0x8BA75E0CDC6A193CULL, 0x93E8700DBFA3C216ULL, 0xDAFD8A67079775C6ULL, 0x07E5A8202E4443CBULL
        },
        {
            0x1140C4D49A52952AULL, 0x094BB599E64E3FDFULL, 0x84AC13F5259A187BULL, 0xFD672BE97463C021ULL, 
            0x64497C8D3DA7E9ABULL, 0x8B9C3DC4E07657B7ULL, 0xA8CEB69677D60229ULL, 0xD566BA2C5E990863ULL, 
            0x954EA0D50BD73372ULL, 0x44DC25F98055DE35ULL, 0xC27D538641D9D73BULL, 0xCF30D73DDF46DA92ULL, 
            0x9F21828C869A142CULL, 0x43B4659BE3C01BFAULL, 0x6016696C0517F637ULL, 0x12585ED5BB8FE2F5ULL, 
            0x29DE524B67E9CE8AULL, 0xBBC8162D9EAEBF48ULL, 0xE2B4314BAB84D7F0ULL, 0xC104F76B3A685281ULL, 
            0xC8CF353DA9440265ULL, 0xB7A20E2FF1D1FA82ULL, 0x5DC1CA1DE8CA0BB6ULL, 0x89B52D9548755887ULL, 
            0xDF78E83DECFF4880ULL, 0xDB0CA990018A5AB1ULL, 0xC3FD50CE9C3DE739ULL, 0x3FB1CE8B841916FCULL, 
            0x40925BE9A199375AULL, 0x9BABAB49E8A1FEC3ULL, 0xB40282495E56055BULL, 0x2D7D4836D4EEB383ULL
        },
        {
            0x2EDBB9D17A893690ULL, 0xDFEBE85D3E125573ULL, 0xDD112FFC05B939EAULL, 0x3A8A9A20EB18E91CULL, 
            0xA7AF32544B3504A5ULL, 0x5628D2F95DDD73A0ULL, 0xCDDA85CFD39E93F6ULL, 0x1346931785944678ULL, 
            0xBABFA27B2658FDB2ULL, 0x1AFB4E42DDD57955ULL, 0xBAA50EFFB8610958ULL, 0xFEB22A399A616F11ULL, 
            0xEDDA22379FB57068ULL, 0xB371C431851D31D5ULL, 0xE5849E391F39886CULL, 0x26E988906B69018AULL, 
            0x522D12FAF1A00EA2ULL, 0xA3E4128B5583D46AULL, 0x0098CF76308ACBD0ULL, 0xFF4D9DE5C1B5FAD7ULL, 
            0x972EDB65EB0EF5ADULL, 0xC8D140BEC7953666ULL, 0xCC1F4AB49B2FA5BDULL, 0x65F3E8BB25265F7CULL, 
            0x8E29A06F646B0F27ULL, 0xE3724B154BFA1BCDULL, 0x31E760EEDC438639ULL, 0x63680071E52445BBULL, 
            0xC7DB10A424D5B6EEULL, 0xBC9FF3D17CAF815AULL, 0x9D2CF3EFFC9F5691ULL, 0x8CCD5302B2BE2A56ULL
        },
        {
            0x7FB2B7AE84BD0FBAULL, 0x612BA059A90AF1EFULL, 0x17F9BEFC690DC32FULL, 0x101DD8D04AE5DEE6ULL, 
            0xA90541EAD2F2D59AULL, 0xF0996853453D0BDBULL, 0x3BB2F64AA614E97DULL, 0x398B80554977360DULL, 
            0x9675AEAD18F61880ULL, 0x6D78352A0637C84BULL, 0xC3B635DB1E519FC5ULL, 0xAD23F5DEB59D06FFULL, 
            0xD82ED646CA726009ULL, 0x9408BF3544B3C490ULL, 0xABBA256E7CFFCE67ULL, 0x07DF428D2F2E6B56ULL, 
            0x3985D4815A9C6355ULL, 0xA1A910F7C937398EULL, 0xDA7FE031FE0ECAF3ULL, 0xB1443ABD40D19791ULL, 
            0x2302BD68A7C9E698ULL, 0xB42316D9B54476D8ULL, 0x1591C653353DD185ULL, 0xD694A7F788DB5009ULL, 
            0xDD6CD2BB708A2F27ULL, 0x46B12C701EBAC115ULL, 0x7E4B3B8E72F398C6ULL, 0xC4050AAA354DDAEFULL, 
            0xA79D879A86EC2E11ULL, 0xC20FD6BD46234344ULL, 0xACF200D51D2C9F06ULL, 0xE7AAAE10DD7DD979ULL
        },
        {
            0xEEDD6961558510ACULL, 0x1F2E0CDC4CEBC2E9ULL, 0x2462755FFBA62846ULL, 0xDCD5C199E853C2CBULL, 
            0xEC9B22490E6E934BULL, 0xA2FC29E3E19EE8ACULL, 0xB7A8220B7C363A0AULL, 0x7ED20922C43DA7A5ULL, 
            0x5EDAADC519611EEFULL, 0x8F0E2529309E81D4ULL, 0x67B578639B7A5E60ULL, 0x304D21B4003BCE35ULL, 
            0xED67CBD1C674352AULL, 0x1A1A511F609A83DBULL, 0xEFDD3AD6A80BADA8ULL, 0x03E5188807F09B0BULL, 
            0x5C65D77C001CF842ULL, 0x179AAB4159B79FA9ULL, 0xCEA01B7C4D60F0A5ULL, 0xEA8190C85D8FD99FULL, 
            0x7A2F9F011DB0AC93ULL, 0x8CDF6A1CF6FDF260ULL, 0xB0C5FBFE14FFC19BULL, 0x42021F4DEE657DA9ULL, 
            0x20DE3A32B1EB24F1ULL, 0x4ECE5570AFE74CACULL, 0x76C1F4311AFE36C6ULL, 0x192D6C61BD9419E7ULL, 
            0xCF16CDED5CAA4EBEULL, 0x06DF7C9F46FF65E7ULL, 0x915170A3315B4FF9ULL, 0x7C56A62FD4CE749CULL
        },
        {
            0x0E83677BFBDACE3EULL, 0x58CAD79A52888972ULL, 0xE4148AE4EC82E5CDULL, 0x41AE7AFB68D27B41ULL, 
            0x072D15B4C682EE6CULL, 0x8D8CBACF5C9BAA23ULL, 0xFCC52BDFD9EFE60FULL, 0xC073E57DC7A075CBULL, 
            0x8C8F6863B4C99EEBULL, 0x4C37797E5FEC0A38ULL, 0xA2A2BED5D3FEE005ULL, 0xA5883DADEDC00AAEULL, 
            0x9808687B7F8F37C2ULL, 0x5A09A5A89A3B5F02ULL, 0x0BC497650C4243DCULL, 0xFBA79F748211A5F6ULL, 
            0x469E7A9BF5EFA4D8ULL, 0xB986F32AC97090C5ULL, 0x5E5725E9C98F01B6ULL, 0x41BBFADF86219E1DULL, 
            0xEC8D727EC567A789ULL, 0x390A3E65EAC2AF2AULL, 0xAC9536369BBE66CAULL, 0x7A88E0D2EDB026D6ULL, 
            0x8F752B03668F7787ULL, 0xD747E825F3B5DB9EULL, 0x23D42194CF23FEB9ULL, 0x0144F7F37CBE72C0ULL, 
            0xCCA0E36811497C34ULL, 0x5BDDFEEFE6F46BECULL, 0x8207AC1433BFB704ULL, 0x04D1C3B184B3E9CDULL
        }
    },
    {
        {
            0x34108E71E9E8ADB5ULL, 0xFA8DA731AACB6B03ULL, 0x1D22CB329E7CDA54ULL, 0x177EA056DFC00F04ULL, 
            0x2AF24167880E378AULL, 0x5327EA383AF25435ULL, 0x6984378F52097EE2ULL, 0xE47FE9B8EB172023ULL, 
            0xA7CDAF806CF54C93ULL, 0x4F3218BF6CDFAFABULL, 0xFB70C994423D7421ULL, 0x7BF7E693AE2AB8FCULL, 
            0xCB3601E4AAA43795ULL, 0x20E48EAF0CA68F60ULL, 0x9E664EA6224BE421ULL, 0x6F49844A6FA89964ULL, 
            0xC5DD5C88645C9439ULL, 0x0C918CC66B1DC15BULL, 0xB9E6B08020C518C5ULL, 0x7BC22E2451FF4629ULL, 
            0xAF80D9783401E218ULL, 0x70000F4B64D6087CULL, 0x3DA0F039AB5E55A7ULL, 0x4120F7FE68D76189ULL, 
            0x2E9BA6BBE9B224F7ULL, 0xC1F9376CDD8C8AEAULL, 0x02839F454F67F77BULL, 0x2FFB805E92B20B98ULL, 
            0xB09D34BFF8E3E691ULL, 0x13C7B402B28F01A4ULL, 0x676EC778FB5EDD00ULL, 0x77633990264EC4BDULL
        },
        {
            0x93EC23771A601375ULL, 0xF0B931FC42BAAF68ULL, 0xB65B45A3BF2289DEULL, 0x160E991B07CD03B8ULL, 
            0xAA4D660BFF46CE34ULL, 0xBF2D939B86676919ULL, 0x84D5F8A73D9DAF00ULL, 0x87367589E37FE75AULL, 
            0xC869623999746A4BULL, 0x893E48C8C65DBE20ULL, 0x8E6AEFD865823DC8ULL, 0x578415F33389C3D1ULL, 
            0x479B452FC5454167ULL, 0x11F7D7E1A9043362ULL, 0x97814B89F52DBEB6ULL, 0x289122AA0B2A4C17ULL, 
            0x592FF2EBD93BAE98ULL, 0xF0A0BFB28ADE2530ULL, 0x63ABCEC12C13BAB6ULL, 0xDDADAE444B7170D4ULL, 
            0x380819A69875E36CULL, 0xB1B4836A72CA80EAULL, 0x296CC928F2A7D4B0ULL, 0x59E0BD4F5862A8DFULL, 
            0xD63D15B2D205822BULL, 0xB3BE9306120781DAULL, 0x96FDB69B664E283AULL, 0x67123A516F882330ULL, 
            0xBF02301C2CD32837ULL, 0x08C762471673CB0FULL, 0x2DC6D83D2C132BBEULL, 0xE1DA1FD6C83C2C6AULL
        },
        {
            0xEB5139CC2FD06CF4ULL, 0xEB8B346FA8531CA2ULL, 0xE2A6BF2D7F1FF926ULL, 0x4F107C1C18FD968BULL, 
            0xA30B799300B5825DULL, 0xEFBFBB41767F1DC0ULL, 0x002CF912D341C5D2ULL, 0x696AFBC1AF07375BULL, 
            0x392938B7E81904A8ULL, 0xE3A1A692084343AFULL, 0xD6AD5DDD9942C6F4ULL, 0x695A2E6AD9AB34E8ULL, 
            0x902A1701CD04148BULL, 0x8816882ADB405431ULL, 0xE36BC6E2949FDB6EULL, 0xBDEA1D8486E0EAABULL, 
            0x74A446A0BF4598DCULL, 0x82D1826D210998D3ULL, 0xCFF1E9FA98C6150AULL, 0x023FA1E0D60CB853ULL, 
            0xE6EED622AF63405FULL, 0x374C8F610FAA5EC2ULL, 0x93CD62330A3259A7ULL, 0x1A06F2B14F0431F6ULL, 
            0x000FE203066DB237ULL, 0x669592D04F7C18DFULL, 0x4A75FF594324C731ULL, 0x7DBBA1D8E7787F23ULL, 
            0x98BE16EBFAD2E267ULL, 0x6203282FDC3A3DC7ULL, 0x24FDBC417F3D1673ULL, 0xFF974451BB824023ULL
        },
        {
            0x32301731BDBDC288ULL, 0xAA69BC10AD645460ULL, 0xE8F8FA942D418F4CULL, 0x2D54429F9FD4A8CAULL, 
            0xA0CA4BA839E7AA03ULL, 0xC3ABC4199FBD99A9ULL, 0x7AA60308FE3F375AULL, 0x43FE35293938C1ADULL, 
            0xD8A66D62BDB9D77CULL, 0x8936E097B6FD73BBULL, 0x036591F0087E107DULL, 0xEFF41A00E1BCF44EULL, 
            0x70B7A35F6025055AULL, 0xE376E5627A41541EULL, 0x9DFD33BF561F4970ULL, 0xF19864A6B02BF912ULL, 
            0xFDE52CFDEFCB1155ULL, 0xC09EFD2FE9C8DED3ULL, 0xBBACD21D97768A54ULL, 0x97BD12A7D2899FDDULL, 
            0x4FE307AC68237F2DULL, 0x5C4FEB0886FD04DBULL, 0x7CAE2A1257C0F18AULL, 0x7808724A3AA4E1A6ULL, 
            0xC7A41ECE90BDDBD6ULL, 0xD3ADD0EE2B56D961ULL, 0x3545C09A776A721AULL, 0xE5DF209BF3BE82A6ULL, 
            0x9C5E2E63F444E34BULL, 0x94D5129F5F9B722EULL, 0x222872A2AAE861E4ULL, 0x6F0B2A87C15B334CULL
        },
        {
            0xD7B75609217AABC8ULL, 0xC7032C49B0BCED77ULL, 0xA1FD2EF263BF01E3ULL, 0xB19D61F2055458DAULL, 
            0x337D54C85324DAE6ULL, 0x8BD0D381B03897C3ULL, 0x63C8E7CB4DD80961ULL, 0xE396D88033B0C7F5ULL, 
            0x0A9A74EBD48577D7ULL, 0xA9B229A42E16C93BULL, 0x8F75574CA6D7B5DEULL, 0x36D81D76D4795C79ULL, 
            0x8F4FE2B6AFA7CD3FULL, 0xDFC25FFF67124D92ULL, 0x46B466F797E2B30AULL, 0xFFEDFAC8AC69CCD2ULL, 
            0xCE1B027EE9E3A5AFULL, 0x8BB5BC5341FE5ABDULL, 0x77F3105A31DA79B8ULL, 0x25876B6CACD83562ULL, 
            0x03049ED0D8F9A709ULL, 0x1228289C68CBAB50ULL, 0x2D90A245CBC21C83ULL, 0x6557A814ED3E7941ULL, 
            0x8AC45C77E30E6FFFULL, 0xB7FC8F708A33E8FCULL, 0x3258EFEF4BBA4431ULL, 0xEE8D64B05F6768E4ULL, 
            0x8119E69371456878ULL, 0x55400D0146CD0CF2ULL, 0x2E73D762DCE7C221ULL, 0x34C17954880365C1ULL
        },
        {
            0x79D7232BEE62F621ULL, 0x2207A9B6DC62ABFBULL, 0x590D9C1D1A087115ULL, 0xEFB5DC4B7A79C559ULL, 
            0x64FE8038DE57D7ADULL, 0xE1F59CF0ECE828EEULL, 0x44FFE8E6726F2FF7ULL, 0x220A017970A11DC5ULL, 
            0xA103E4D5892696B4ULL, 0x17460210C98E94A8ULL, 0xD443AEE33A6F03E1ULL, 0x8985650A36C7BF1DULL, 
            0x47DE279C9B4C3E0CULL, 0x431FA7BD9BF65CD8ULL, 0xCD208E2F0B7F7F1FULL, 0x9F48B2EC1DD269B9ULL, 
            0x36ACAA3081562802ULL, 0x20B2BCA3B23D6D94ULL, 0xEEF92EFF1B213898ULL, 0x4B3297F01B47DB04ULL, 
            0x4AFCD418AB300A33ULL, 0xE2EAE4B2BCC08710ULL, 0x3B2F56BB0C41CD24ULL, 0x21B545E64A2358B9ULL, 
            0x90A1BAF9DA85D0B4ULL, 0xF74AD752AEDE761FULL, 0xE444A747C8EB7227ULL, 0x928F00E0A805B600ULL, 
            0x4092187D2FE38FE9ULL, 0x057667B5A5A22B59ULL, 0xED9BB7154F7A7B4AULL, 0x29E916FED26BF915ULL
        }
    },
    {
        {
            0xA312E55A084C2A26ULL, 0x5E808104C0CAD275ULL, 0xE262CB73274AEEE6ULL, 0x447A60E2CF87F691ULL, 
            0x3A42880FAC9D5257ULL, 0xE3CE2DE63B37059DULL, 0xEA59DC5A52CE30A2ULL, 0x5C0BB748CDF2B30CULL, 
            0xC04CBA10D4EDC3A5ULL, 0x32C11B67DD115856ULL, 0x0176C3A39532A3A4ULL, 0x3DEF0306E2131EAEULL, 
            0x8AA1E4CBF88EDBA8ULL, 0x48C4590C0784EF0EULL, 0x31CC37D8AAAFF907ULL, 0xC9542B5BF411F1A9ULL, 
            0x8F8AD66396D32332ULL, 0x90A1DF886B0B3E02ULL, 0xAEDFC5F3583715C0ULL, 0x74874EEB663E7F3CULL, 
            0xDDE129E60D3E2F9EULL, 0x85E075849A02AB68ULL, 0x2ED3A9BC03BDAE54ULL, 0xF1B24C16F7AB47E2ULL, 
            0x5055636F5D01C81CULL, 0x37B72CC24772FBB3ULL, 0x82FBF76526758522ULL, 0xC94E3D33D4FF8927ULL, 
            0xF305B9C0A373477FULL, 0x37F27A13B183637BULL, 0x07D42AE1C22DC2F7ULL, 0x5F1D817C55FECFA1ULL
        },
        {
            0xA269831894497DCBULL, 0xBCCC506A6850A6F2ULL, 0xDF89309E968CFD20ULL, 0x3F748E6BC8CBBBBBULL, 
            0xAB5E2AA3FA5F5316ULL, 0xF2EC6D6AA2878EC0ULL, 0x235ECE89590C3AA3ULL, 0x8FC26769D27694B2ULL, 
            0xEECBB69ECA74857AULL, 0x304D62B9C692191EULL, 0x18EB9F5A559FFC38ULL, 0xFCA29A62394AFFE3ULL, 
            0x8C0F9EF5A840841FULL, 0x6B1B1C9AD70578E0ULL, 0xA7FBDEA29F8671A7ULL, 0x91A514434A3BFFBDULL, 
            0x19EFB3E0663FE9B1ULL, 0x654A0D74B9EFFC4EULL, 0x157D389E57FD8C5AULL, 0xA535961EC4D426A1ULL, 
            0x1C26C9FCD9EA0157ULL, 0x63281319CFDF12DCULL, 0xA8298CDDBB112F86ULL, 0xE7DC395193FCE8AFULL, 
            0xFF9F2633B9DC55BFULL, 0x494A87106EA9C2A7ULL, 0x603F5C2678A60411ULL, 0x8276F5FCFBF51393ULL, 
            0x3D66AC18FF79071DULL, 0x8F17564FBA754A8AULL, 0xA8993F80A7110D1EULL, 0x7A3218D3A4F8FE3EULL
        },
        {
            0xB4956EF5C8DA5CDBULL, 0x61FDA8D8EC137E0AULL, 0x8DB73A54E5443C5CULL, 0x7A81392DE8C25D9FULL, 
            0x3E61FEBDF185D287ULL, 0xA8C6A21BA70E1540ULL, 0x678F048A040BF9AEULL, 0x25879A642DEA6B4CULL, 
            0xC0D820CDA7D2AF4FULL, 0xF3E47EA4F8C1039BULL, 0xCAC75139D4C9AADDULL, 0x68A4AACD2A0F001EULL, 
            0xC3D55AAD23D41885ULL, 0x97603E0E57B0B6C9ULL, 0x76609C6EB9E4830EULL, 0x45ED0AD00D51C620ULL, 
            0xB9C946262128C83DULL, 0xBD5784AF69133AF2ULL, 0x8157496A88C7AB7FULL, 0xB0AEEF30AB0BE133ULL, 
            0x6D0A44D710A28CEEULL, 0x1F06E6CDE120D623ULL, 0x5CA92E140B09A58CULL, 0x837010ABD0A1A49EULL, 
            0x31FFFF29D1A33D0DULL, 0xDCF97992C6B91D7CULL, 0x804B396AC5CF1249ULL, 0x02EDFF3D97B5B880ULL, 
            0x656ED3C2B8A825D9ULL, 0x163213E837570B68ULL, 0x6EEA373E6D546EBBULL, 0x5561730FD34C840BULL
        },
        {
            0x1F8E34CFB5072C91ULL, 0xB6A72CA6BAB215E8ULL, 0x8FE54915A0D01EF5ULL, 0xB7F7A00C73759C6BULL, 
            0xAEC0A09C87C381ABULL, 0x9F87E0A6EA2D7E05ULL, 0x8152C1994497F2CDULL, 0xA4A7F77FE857A5BBULL, 
            0xDB3CFAF1604FC2ECULL, 0x08D8172FC4294570ULL, 0xEA154C159F9D7669ULL, 0x1CAB1BB5A20D62D2ULL, 
            0x7B7DE6B0DA324E6EULL, 0xBE0D4449EEED9701ULL, 0x98E6F7EE2C3F6436ULL, 0xFBAE9AE680A31225ULL, 
            0xC17F7255037E2A1EULL, 0xB9F908B2422E2B42ULL, 0x26C883783B7EF899ULL, 0x48F233A22991CE5CULL, 
            0xEB31A945B97B8DCEULL, 0x176E3ACA2825478FULL, 0xA5FAC823E88C6B1EULL, 0xA246779B007AF642ULL, 
            0x99A699CA4A40C05DULL, 0xE49000AF161C85E2ULL, 0x07DCD9C611633910ULL, 0x73F14F9700A50069ULL, 
            0x33768C8D3F666020ULL, 0x84D230F75046D8D6ULL, 0x72F2D59F8EDC9B1BULL, 0x59E7025B79730390ULL
        },
        {
            0x93C00A0CC53DDEB4ULL, 0xBAAE03F13E64DF7AULL, 0x621C41FD0B740ED0ULL, 0x65DC15B4A0FB0D3EULL, 
            0x808AB65B3A94580AULL, 0x5FE08DC93824ABCBULL, 0xA409A801E9B8B6A1ULL, 0xBD7CB65434C3842CULL, 
            0x510971FEEE22E367ULL, 0x7A4B195C68267C62ULL, 0x358DD1542A4E4841ULL, 0x9454B37C52B20AA5ULL, 
            0x30FC9E79C46CC4FDULL, 0xD204C19A4AFA789BULL, 0x4E34B2E7AED3AC9EULL, 0x33DAA5DBE11B2D11ULL, 
            0xDC1812DE54A428D7ULL, 0x3916438AAEA1DA39ULL, 0x6F6643EF41141E81ULL, 0x8D6AD149CD621509ULL, 
            0x1D7C658D9291BF64ULL, 0x691F25A96607AA8DULL, 0x0C61BF9F797D4623ULL, 0xFA47F52BC88D5695ULL, 
            0x8F3AA05E25119863ULL, 0x96DCCCFCF7A38C2CULL, 0xC74257DC3965B0B5ULL, 0x15BEE666A96DD14FULL, 
            0xF5E103A9A73D932DULL, 0xE98F20B4D5F86108ULL, 0x8263DBA379376B46ULL, 0x7BF2640C5B121B64ULL
        },
        {
            0xE4514C86C5CBF61EULL, 0x5EEFC4C46B8B162CULL, 0x4363FF8E01EC54ADULL, 0x190357BEC174237BULL, 
            0xD3F15FAA21112D6BULL, 0xD69EBB0D642AD706ULL, 0x5F3FC2D44B0E9FCDULL, 0xE2771D5FAEC2FC85ULL, 
            0x82031BB7A4631DB5ULL, 0xD0B6470A7C9AF17CULL, 0x39CBB622DDBFC5A5ULL, 0x6D60561BE61B99D6ULL, 
            0x5A0EC387E82A9CA4ULL, 0x2EE9B36ADE0CFED2ULL, 0x9A230FC7C3CFC5E5ULL, 0x60E4AD609BF53032ULL, 
            0xDE3436059E2D5AA9ULL, 0x07ACD73917B5C30EULL, 0x6AE5653EBA1A39E8ULL, 0x3F55D256BB15A5E2ULL, 
            0x35491687C9C9A48FULL, 0x8A146223CA7C7149ULL, 0x4F20F7A51609DB84ULL, 0x34138313388EFE30ULL, 
            0x239055797CC67641ULL, 0x5083B4359B060E86ULL, 0xBCAE2D5751241B46ULL, 0xD2315CE2156D17A7ULL, 
            0x29C6F1EDD1193738ULL, 0x4E395553D8C972B3ULL, 0x78BC878C5BA22B85ULL, 0x710176667047DEF9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseDConstants = {
    0x5A27BB47DAD189F0ULL,
    0x915D96A3FA0B806DULL,
    0x0E3F8B7C0AD0B956ULL,
    0x5A27BB47DAD189F0ULL,
    0x915D96A3FA0B806DULL,
    0x0E3F8B7C0AD0B956ULL,
    0xB2BB55E3DBE7ADFDULL,
    0x1695B289321DA1FCULL,
    0xDA,
    0x7C,
    0xC2,
    0x3F,
    0x52,
    0x45,
    0xBF,
    0x89
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseESalts = {
    {
        {
            0x7209BA2A0CA82634ULL, 0x0CB027E228430396ULL, 0xD10454495B54A201ULL, 0xD3B90DA90807EEDDULL, 
            0xCA67836312363C21ULL, 0x23B4170627EA19B2ULL, 0x76E030D745288EFBULL, 0x6D1E662F48BF738DULL, 
            0x1044480B6B07A402ULL, 0xDCC1C0DA7AAC07E9ULL, 0x5D672810C6644FF0ULL, 0x26ED03FCDC2FADC4ULL, 
            0x93B34C80E57DBA09ULL, 0xFCD00A57DEE8F578ULL, 0xAAE722F230527611ULL, 0x3B0ADE3BE876DFC3ULL, 
            0x1898BD914EFBE58BULL, 0xC877BEAEF0BAC877ULL, 0xBFA10DFE528BAFA2ULL, 0x00F81C10ECFA0E5DULL, 
            0xE4BA42C3A6438BE1ULL, 0x45C09A7100E46094ULL, 0x962D4152952BA26BULL, 0xF143274747130D45ULL, 
            0x6E275EACF2F60FFEULL, 0xFB03684A188DC77BULL, 0xE83B7D7F21738CDAULL, 0xAB0D4D7508E0E6C7ULL, 
            0xE3ADD7C43E0EDE39ULL, 0xF1CD4BB03390BA62ULL, 0xD2F949FC157D09CAULL, 0xCE6274A08E9DD7A4ULL
        },
        {
            0x590AA81A4C5F152DULL, 0x9CDE76B24486C969ULL, 0x313591815DDF95B1ULL, 0xA32A06CFBC2C6365ULL, 
            0x65815C60E32C098CULL, 0x886A1FA37ECD0805ULL, 0x2CD050174E04D1D6ULL, 0x3E036EBF61991CBAULL, 
            0x999FB90F1AB809D8ULL, 0x43F3A8ADCD3F84B9ULL, 0x89133DEE190DF616ULL, 0x03C15904323FCFADULL, 
            0x8A14DFB3C8068885ULL, 0x83602A5D9ADF23F4ULL, 0xEDAFA9BDA1518ADFULL, 0x110F091B2DD26BFCULL, 
            0x6D5BC638AAEDFF74ULL, 0x9829CDB00EA43B99ULL, 0x4E4AA493E0C5CB24ULL, 0xF9F2E8338C22B472ULL, 
            0xC969D19A6F4EE017ULL, 0x457CCEA3FB36D637ULL, 0x1860776CAF57F126ULL, 0xACE54E96A2B52CBFULL, 
            0x23360F541DF2C196ULL, 0xDE0DAE94981172D6ULL, 0x90AEDCEDC62D3F91ULL, 0x959402E27663D9D2ULL, 
            0x13EEB8CA037A52E8ULL, 0xED9B1A72B8D5BDB8ULL, 0x77B6649F14D7448EULL, 0x443BB0AF70C3FFB1ULL
        },
        {
            0xBE2D5ABC396CD4FFULL, 0x91B922A1ACF4EC10ULL, 0xE67EAD595C50DA83ULL, 0x1DC989BF838CFBF0ULL, 
            0x59A9009BB1AE4462ULL, 0x973A142009BD9EA6ULL, 0x603A73718E5F44E4ULL, 0x10FC61FDCE779527ULL, 
            0x956D72FBD5351D27ULL, 0xBE54DFE212399E79ULL, 0xC20736DC38B89593ULL, 0x904DF5C9A9C334EEULL, 
            0x7BB3806B7A099E8CULL, 0xF9C1B27D7498DE9CULL, 0x3705DD5F08E6EC95ULL, 0xAF051C5C5912F50CULL, 
            0xE33677F7E33999B4ULL, 0x635F5EC88B55CE34ULL, 0xD901EB5325CF3277ULL, 0x1F4BF37931191685ULL, 
            0xFAD6A8712E6E8CBFULL, 0x89F07130FCD816AFULL, 0x73BEE09FF7AACB50ULL, 0x1003FBB456A2D907ULL, 
            0x3DC5D2C10DDEAA55ULL, 0xB85488EE058FF8DCULL, 0xDCC831904FBAE3A2ULL, 0x75AB300F2DCA19F8ULL, 
            0xB37AE17C4E1E9F78ULL, 0x90447BE0B53E6C5FULL, 0x67EDC880FEAA1141ULL, 0xBF9E7AD110F9F4F3ULL
        },
        {
            0xDF8E9AFB0C9400D6ULL, 0xB5F4EF9C4E1C1704ULL, 0xA6D27763E9AF3D24ULL, 0xAA87FF1AC0CAFE27ULL, 
            0x656BED37256ECDE2ULL, 0x23F31FEDEE9B5CBFULL, 0x89CF15E0840EB085ULL, 0xFA359AED6089E8C5ULL, 
            0xEE09CB01EF45AB4DULL, 0x6379E881A0087A79ULL, 0x6E9EBDCF86577DC4ULL, 0x2012FFCB8301C4CBULL, 
            0x7F8E4424840F708DULL, 0x8527103AE63D1D5EULL, 0xC669A841D30D9088ULL, 0xFCC8EC1AEB2FEC86ULL, 
            0x5006DE74569BE937ULL, 0x0070A3A9DC645A6BULL, 0x1209413A53744E61ULL, 0x45059B2AD550CA31ULL, 
            0xA4C2BCC3AA4739D3ULL, 0x34F8143506E64385ULL, 0x890814EDEB3200A4ULL, 0xD1382342DF2DFFBAULL, 
            0x30B47D9AFFB1CAD4ULL, 0x8AA449F39D73C573ULL, 0xA20A76CE32E8CE55ULL, 0xBE47F5CAD2A7D5E2ULL, 
            0x0945EF2111F63312ULL, 0xABB997B99B7A6155ULL, 0xEFA0C3C3E9857A6FULL, 0xD24392DBDE9CC20EULL
        },
        {
            0x3D1657D6AC3E9AB7ULL, 0x30A1C4270FED4923ULL, 0x27A5D692ADA94748ULL, 0x8C9FE98478D908D0ULL, 
            0xC70DF3A8D05CDBA2ULL, 0x26B46B140A599423ULL, 0xDB66B5DB8FAC5B50ULL, 0xCF821716FB47E22AULL, 
            0x6F468B90D8220E73ULL, 0x0A95B500DEEF165DULL, 0x851469B77B5AC283ULL, 0xD2192C7883F40CC7ULL, 
            0xB4ECE4CE85AF6213ULL, 0x4B9F88AF4062A693ULL, 0x3BA1046B6FFCC6F7ULL, 0x969AA24E9E31B3F8ULL, 
            0x084B32A482FD86B6ULL, 0x8DDC9625270233C2ULL, 0x947426735D937E05ULL, 0x4A232FEF253A1A0AULL, 
            0xB9D95F20864A8C40ULL, 0xE1393C3331CEFC6BULL, 0xE2F60F07BCBC7166ULL, 0x7C27DEEFDB73A0ACULL, 
            0xEEB552AFB906EAE5ULL, 0x080B69621F0ABFB0ULL, 0x19D1FAB7023E4A5EULL, 0x059603FD4B2A8D3FULL, 
            0xADA025DD9474214EULL, 0x5C52BA73B6CDE333ULL, 0x64BF9A23509385E5ULL, 0xA0133CA63871306BULL
        },
        {
            0x7CBE0C87F7E2BD08ULL, 0xA592FF301518CD2DULL, 0x5F1CD84577CEB629ULL, 0xB152371EDB22FA6DULL, 
            0x83EAFA0E551B9664ULL, 0xDCF7D5DD7A8E5F2DULL, 0xE59D750F7F2EEA57ULL, 0xD19D08662BEDF209ULL, 
            0xD1C47F3AF237B4B7ULL, 0x99FB3714368003C1ULL, 0x0FE6758BCCC3DD7DULL, 0x6D3EC09771D2D125ULL, 
            0x1217471A40EDCF46ULL, 0x63FC16870C90B84CULL, 0x19266D4700089D1FULL, 0x1C83DDB06C1ECC6FULL, 
            0x5051DDE6C9FC4436ULL, 0x4997D201B07D4D2BULL, 0xFFF3B70788EAC6FFULL, 0xD6DC43EAEEE21E98ULL, 
            0x04F36311E276A8FAULL, 0x1E18DE74C0B1761DULL, 0x5BDCB3630634EF09ULL, 0xD7AF338DD2CD5C47ULL, 
            0xD3B6DDA083AEE281ULL, 0x8EACC0A2E7101141ULL, 0x42CC3EAFF510DC4BULL, 0x4E916B80CDD4C96BULL, 
            0x496401097ACF2C8AULL, 0x91B645BD95D88F26ULL, 0xFF6BFACBF09A8B0DULL, 0x14AD8EE984C03ECBULL
        }
    },
    {
        {
            0x38CA6924DF550973ULL, 0xEA0FCA50DEE08F4EULL, 0x123BE35F302E3B4BULL, 0x5D03F5543B8FAB23ULL, 
            0xF49DDAE3B0E69C12ULL, 0xE3300DC9495A5D92ULL, 0x7020483B17314EA0ULL, 0xF899D1779D5F07FEULL, 
            0x65CBFC32C2A1BD4EULL, 0x033D9C2B5BE36C7EULL, 0xF722A31776312224ULL, 0x480648C629D1CCA9ULL, 
            0x1C87C5E47BEA5971ULL, 0x956312C67E0E9B30ULL, 0x97F42CF89EC6B9D1ULL, 0x733C5E13B181F625ULL, 
            0x98FC6850662DF9FAULL, 0x04BE5D8858E552EDULL, 0x10CF4486AFD8EDA1ULL, 0x462CCCFCF20B2EB6ULL, 
            0x26C25809364C0770ULL, 0x98EC7A6452222EF4ULL, 0xECCC09440EB02E0AULL, 0xA424DFE07A0EE76EULL, 
            0x62C3D79ED45469A8ULL, 0x435EBF609721E562ULL, 0xD880065D73E49893ULL, 0xD13889D854351911ULL, 
            0xD133CC93364F0022ULL, 0x10D13A5A05660A43ULL, 0x264A4767BA1D66C8ULL, 0xE4A8467E85DE22CCULL
        },
        {
            0x3F790752683A02CFULL, 0x06D4D80751D3C10CULL, 0x725D028F13E6913EULL, 0xA792560C963EDCD5ULL, 
            0x1A24870E334CAAF2ULL, 0x7D171A8BC33C2D25ULL, 0xAE34C520C8172F5BULL, 0xFB901502A6B91D46ULL, 
            0xB57743B7672753DBULL, 0x6AAD6B007E0F8E92ULL, 0x3D2F9B6F987EEF5BULL, 0xD36C70649B0CA1ACULL, 
            0x89472D33A84D2E05ULL, 0xC578AC3B53BD3E45ULL, 0x7B9016811BC3FEC4ULL, 0xE308D8D0A1618779ULL, 
            0x2B1583BD1254E534ULL, 0x02AC98FFC25E2349ULL, 0x320D59537227AD7BULL, 0x609176B633F9B408ULL, 
            0xA95B88979A2CA15BULL, 0x8A47CD46248E67CDULL, 0x2E73FB640EE30916ULL, 0x585D06ABDF158A06ULL, 
            0x76E7B112D64184E4ULL, 0x72060D267984E79EULL, 0xC6F066367AD505B9ULL, 0x176429D659573469ULL, 
            0xB8FB56ACCC5B96D3ULL, 0x98D97CC9CA190444ULL, 0x24D80FED8076D93EULL, 0x32A3D062049C4B48ULL
        },
        {
            0xF7EF1C9517114808ULL, 0x0867A86496462BA2ULL, 0x7B5EEA5D825169B8ULL, 0x08A0697991FC5D4BULL, 
            0x63DCCA48853B786AULL, 0x03D80C4F2FB58C9DULL, 0x23A2E7CA90CDDDFDULL, 0x94588925030194F7ULL, 
            0x5A30E830A6EE46E4ULL, 0x7020D1B6541E3A61ULL, 0x2E26D4D39FEEDDA3ULL, 0x295863DBCBECE93DULL, 
            0x232C77F71CC6ED3BULL, 0x4B36FAA3C73A6E65ULL, 0xEA7868876A2EEDE4ULL, 0x44F746141F101EA7ULL, 
            0xD511F3A10D3E6271ULL, 0x0CCBB72EB4E3C191ULL, 0x66CFC1017F31251CULL, 0x36BF2F85828DDE64ULL, 
            0xCED5DDFD556F9C59ULL, 0xB5BD1AA80F7D6CB1ULL, 0x5F74F8595C47EAC5ULL, 0xD5B2089E77465C8EULL, 
            0x93AD895A2D1E8932ULL, 0xF9162E9620B332BBULL, 0x661659CA901DE69BULL, 0x72670ECCE4B4CC2DULL, 
            0x3C0AA86CDA7A1377ULL, 0xD75A9C6539AD4879ULL, 0x023F9DACE56D9201ULL, 0xBFEFB711FF4DC62CULL
        },
        {
            0x5BF402A58D14997FULL, 0x8BD82F9A9E39B34AULL, 0xDC2193DED1C35B06ULL, 0xE7BB0FE51B406950ULL, 
            0xCA0F7E2AB8ABDFFDULL, 0x6D59E6B3D18599A5ULL, 0xA7E6A750EAF4C23AULL, 0x123A1CE79AC608E9ULL, 
            0xE507D6E6AF7E4D1BULL, 0x2AA5626806EBC838ULL, 0xFD5DCE014B28FEC6ULL, 0x31064A9C141DB112ULL, 
            0x831ED0E9A7799BB0ULL, 0x679B54CFC3B1A427ULL, 0x93AE4BCA534219C7ULL, 0xBC81CC00E1EA5B91ULL, 
            0xBC35599353F4B700ULL, 0xDF16651E6BE6CC03ULL, 0x957BD52144BCCA9AULL, 0xA68CED96D4ED9D8EULL, 
            0x61892C901933D99EULL, 0xDD878C206A5CD204ULL, 0x115CF3AFCF1BD281ULL, 0xEE92A329079C327FULL, 
            0x0DBA4F98FFA2501AULL, 0xBE8CBD06CEA41C4AULL, 0x685D51EE5C3EFFDCULL, 0xD44798D069D961E0ULL, 
            0xD5E036C2EA3AA76DULL, 0xE8B302288FC1BED1ULL, 0x00E3190C6CA3D241ULL, 0xCD8B727FB19A7A5AULL
        },
        {
            0xD9ED6FDE333E7183ULL, 0x1A97C571C8B042B9ULL, 0x7C710995368D8472ULL, 0xBD72A1A8A126005FULL, 
            0x973F438C41207CB6ULL, 0x98322BDD14A94E56ULL, 0xD6664716EA6CF878ULL, 0xFFF0A5837B2254EAULL, 
            0x33AE9751F93800B6ULL, 0x43C8893FAE5D2C69ULL, 0x7EB99EB448287339ULL, 0xA789820CBAC73FDEULL, 
            0x25F9E38209A2A4B5ULL, 0xD573B216B1D5D279ULL, 0xE69AE521C9EE8D87ULL, 0x60F51727EC1B226AULL, 
            0x48C46CC39F2A923BULL, 0xA0CC46F2FB52EEF7ULL, 0x7A1A2213A02D8ED3ULL, 0x272BC05AF7807A62ULL, 
            0x45D3080335BFCEF4ULL, 0xF1E4A7DD64C86894ULL, 0xDFEF58856486F677ULL, 0xBC0A0FF42F308799ULL, 
            0x63577E1FE2572793ULL, 0x9AC7080BD2BFE44AULL, 0xD839CE7B3A879CBCULL, 0x1BDF28BFF1FDD972ULL, 
            0xDDC75D352B56FD1DULL, 0x145F5637F35611FAULL, 0x15E6C5E0136BFCEAULL, 0x3AB817E5C4C026FBULL
        },
        {
            0x7697F2C8D845ACF5ULL, 0xC7E04EC411654E88ULL, 0x74B25E50B70EF6AFULL, 0xB5844740D4332E08ULL, 
            0x5766356869295832ULL, 0xE5B4322A36142845ULL, 0x4557964EF7AD964CULL, 0xE2A6E2994A730FAEULL, 
            0x11F443F4B3B5A435ULL, 0xC9D6C29B192E0783ULL, 0x78BE0438BD4749FAULL, 0x0AF497F69C1F817BULL, 
            0xCFB42C0FD30D7E52ULL, 0xFDB5AB0FFF15C7C4ULL, 0x5D99C98D4FF9AC36ULL, 0x398105CA50D9A979ULL, 
            0x234097C602B5E8C5ULL, 0xD704B851A8EDA1ECULL, 0xCF9B674BA1E668DAULL, 0xA729CF802F772F6EULL, 
            0x8F9E30538857AFA0ULL, 0x3A051BD63D4950FEULL, 0x86EE06783FB27FF5ULL, 0x39BB8D4A980AC1D3ULL, 
            0x3DE88FD56342E4D1ULL, 0xCC034978978C6224ULL, 0xA1C11436DCCCD079ULL, 0xE0CB360F001E45DFULL, 
            0xC80F38C1116F5407ULL, 0x3BD9CF4AED839D98ULL, 0x0D6ADA6C5814E6DFULL, 0x4BAB4C57B15C55BFULL
        }
    },
    {
        {
            0xD0AB3C4796B771B6ULL, 0x05A9369B58D0ED68ULL, 0x0C328A50A37C99F4ULL, 0x1B23BDCEB40084ADULL, 
            0xECB064ABF5D8D3F9ULL, 0xC292AE629892606AULL, 0xBB09A94E65D2FF3EULL, 0x9B1CAB9C1BBAB48EULL, 
            0xDBE2EAC319B0EDD4ULL, 0xD160E5FB6A94F645ULL, 0x79AB9BC0F1D06A44ULL, 0x65102056AEA9117BULL, 
            0x8406DFC617A2FA85ULL, 0x017EB34F908C5BB0ULL, 0x98E3E073BB95C275ULL, 0x12595672AB162662ULL, 
            0x45AF210901046672ULL, 0x00497C25C778B94EULL, 0x15D28D012997BB98ULL, 0xBF77D118BB0470A4ULL, 
            0xE07234552EF17970ULL, 0xFAD6F0A11A13F23FULL, 0x22D1EF93B768F7E6ULL, 0x084BF1732D5F23B3ULL, 
            0xF2A2112CF711AFD1ULL, 0x8449503EAAC3DE48ULL, 0x84D97A92A8BF5FFFULL, 0x2BD24EBCF1878ED5ULL, 
            0xAED9D34B2D962E81ULL, 0x0925E89083DC63E5ULL, 0x5737E17B9FEC043FULL, 0x1A05C2315E839CC4ULL
        },
        {
            0x656EB24C77C518E0ULL, 0x8838D315E4033DE9ULL, 0x72EEB42F53D5BAC0ULL, 0x3B4B293EF6986752ULL, 
            0x7D8A5F788963EAAEULL, 0x978B939706B37593ULL, 0x130A92F20EA10E89ULL, 0x7660A724C2DD7AB3ULL, 
            0x79C519BB9616E8EBULL, 0x930E3BD2DFCC1F7FULL, 0x5D3B0B303A167556ULL, 0x5B4768C789E32407ULL, 
            0x00D86DD02D5C5B50ULL, 0x7FC520AF475D3E66ULL, 0x132F6A77E45619EBULL, 0xDF926C0B5C3755B5ULL, 
            0xA894122405B6E455ULL, 0x1029412503FA57ADULL, 0x1A6F9D919534E06FULL, 0x1A3F6727EF200B54ULL, 
            0x778EE15416605E12ULL, 0x79CB2FFC13AC6319ULL, 0xF9E73B72C802353DULL, 0x6723140CC12C9090ULL, 
            0x900D6DC9D8E63B45ULL, 0xBAFE5C06FC672F48ULL, 0xE3D2DD138397AD9AULL, 0x9C02647D6B497DB4ULL, 
            0x915FE58465F0C2C3ULL, 0xB80032A15EBA4138ULL, 0x7D6529B88592ECFCULL, 0xBD05082DF912BCDDULL
        },
        {
            0x25F4D2ADF5DC0145ULL, 0xA656EAD0C53FE6DCULL, 0xFAF89F0D7E19ACB7ULL, 0x005FE6AC7D220E5AULL, 
            0x38DDA45E8DAF15BCULL, 0x43A094D14C11CB24ULL, 0xFFCCADCB05F7A647ULL, 0xDD96E429F9B240E6ULL, 
            0x25507C143B4B002BULL, 0x98D878B1A11E6108ULL, 0x698543B8A072FA61ULL, 0x7B64C01D8BBDA029ULL, 
            0xA0F1EBA1AD83AE59ULL, 0x04AA4BC9D59E6613ULL, 0x0E19B354870E9EA1ULL, 0x5E6B2B2F833AC62CULL, 
            0xDD685BC9E8BDA581ULL, 0x9CF79F90179C5736ULL, 0xE5202AA42B088458ULL, 0xBCA384490C41E6BBULL, 
            0x1C7F933D6E665A81ULL, 0xA51C47F601AACC81ULL, 0xF7F567A9FAE5FFD9ULL, 0xCFE5DA7EBB246C98ULL, 
            0x0D12F96BEEF1B6D0ULL, 0x711993DFEE1824E2ULL, 0x6D3E667CAE786143ULL, 0x92CFA0B79CB1F364ULL, 
            0xBECCC5BC4DEC080DULL, 0xF15F63F656402DDEULL, 0x706C9163CC41F6C5ULL, 0x38705786548A1B63ULL
        },
        {
            0x68BFF3A6F0C00EA5ULL, 0xB68D66936CDB1759ULL, 0x07412D6416D7A651ULL, 0x50A46BE72C9CD3B9ULL, 
            0x830CE25EC38090DAULL, 0x94875D7D90A9357DULL, 0x1F1427CCA0B05EA5ULL, 0xB931C62F894E3516ULL, 
            0x74156D3927909DBFULL, 0x4EBF29E355F4F4D8ULL, 0xD13252BA09061972ULL, 0x3276DAF53CFE8491ULL, 
            0xF0CB71550091706CULL, 0xEECA13157989EC31ULL, 0xF8D2709C0C28D882ULL, 0x3E117576E499A20AULL, 
            0x9EBA3CE17A4AB061ULL, 0x6462EC70C17D6C1CULL, 0xD17DEE19C66230DBULL, 0x59504E33D57F8DC2ULL, 
            0x33ECE858F4FCD18DULL, 0x61CFEE8B2944760AULL, 0x111B81256461E668ULL, 0x9BD283AAD8F48014ULL, 
            0xA32E4472A5BB4EB7ULL, 0xA8471C14781B4A37ULL, 0xDF6964D197F8E3C3ULL, 0x63E83F7B35ADE1ABULL, 
            0x7A1ED7A408A26479ULL, 0x2C5D5A383A053CE8ULL, 0xE01D43DDBFCB05E1ULL, 0x81B3D43A714A1D0CULL
        },
        {
            0xA925A7ADFD02CE6AULL, 0xE2264D94D7CB7769ULL, 0x743BB022763DCE28ULL, 0x8AC4B0D5E0D6A99AULL, 
            0x99495340EB7FA968ULL, 0x84CF3A970A409C64ULL, 0x8D847B5C9A591CF7ULL, 0xB457D5792C2E534AULL, 
            0x13FE6A44A98B131CULL, 0x9EBF1478D323B4F1ULL, 0xB66405A8CE225B8BULL, 0x2CB1C94E161BB4C6ULL, 
            0xA6493BE8A3562B1AULL, 0xFF048C4C462AF43EULL, 0xB738AD121EA7887CULL, 0x9AE4D8C922ADC6E5ULL, 
            0x2A9010B446E13B79ULL, 0xDE8999E7AF268353ULL, 0xD0C5582C2ABB7F43ULL, 0x42BCBEE16674C36EULL, 
            0x60E87AC127A4694EULL, 0x2AF1E5A961C0D5FAULL, 0xEABD189BA3BE94F9ULL, 0x4406F355F76ED5F8ULL, 
            0x29A08079C86781F0ULL, 0x73AE8440F40E292BULL, 0x8E6A9D64EFE0A85BULL, 0xC2C49C91A0E0A021ULL, 
            0x8060BF2C1FEA656CULL, 0xA615450217099B4BULL, 0x5242932ECADD3568ULL, 0x87F403C340783F1DULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseEConstants = {
    0xA49B8B602121B66EULL,
    0xE7EA7CEB3E205044ULL,
    0xC66BE869EECE140CULL,
    0xA49B8B602121B66EULL,
    0xE7EA7CEB3E205044ULL,
    0xC66BE869EECE140CULL,
    0x2C5B45F00523915FULL,
    0x0739C1A805943225ULL,
    0x0C,
    0x33,
    0x08,
    0x0B,
    0x96,
    0xFC,
    0x5B,
    0x1F
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseFSalts = {
    {
        {
            0xB76A068191ECB0B0ULL, 0xC1E8782146EC908EULL, 0xA3A2C75BD878227AULL, 0xF8494A9AE6AC8618ULL, 
            0x4C25C7763105BE02ULL, 0xFEAAEF5411F4351AULL, 0x1021D18DE0093174ULL, 0xE62226F4E8CFF02FULL, 
            0x1AC69D0C55567E13ULL, 0xB4328D4164554DAAULL, 0xF499A13303503F89ULL, 0x9A5491E12B14AF2FULL, 
            0x48CDFCDC19B27425ULL, 0x8F2F9DE1BE2990A0ULL, 0x7926C426B8EA5FE0ULL, 0x57ABA30D1241C7BAULL, 
            0x0DB7F4E252DFA23FULL, 0x3DBDD73198D8A226ULL, 0x8CB6F58C199F926BULL, 0x72A819E45066FC1EULL, 
            0xF90D4A1F80A0BCA3ULL, 0x38B5E157AE106931ULL, 0x1C5C0505D139078BULL, 0x842BB32DC6E01BD6ULL, 
            0xBD4285EB7DFFC3C7ULL, 0x83AF2E9A0FC225D2ULL, 0xCCC98807DD5E4A26ULL, 0xCEDC955A65AC7336ULL, 
            0x557FFBC12306780DULL, 0xDFA8316EE41589B1ULL, 0x82B1FCC996CA1351ULL, 0xD9B1F01142CD1C29ULL
        },
        {
            0xA74101163DD854B2ULL, 0x2D7C0C387C7447D3ULL, 0xAECFE01593BEBCBAULL, 0xC9B45718D5A0AC6CULL, 
            0x90FD5FB887F0B283ULL, 0xDEF12E9F3040F65AULL, 0xF0F33095F71D5BE2ULL, 0x8D0972AFAB1D6345ULL, 
            0xD66A478502122C69ULL, 0xE2F80EFFEB412D3BULL, 0xB27B2E98F126E027ULL, 0x3C9117249E57E319ULL, 
            0x80A258F32E50EE28ULL, 0x2093AA3A8946DA69ULL, 0x2BDEBDC47BCF9715ULL, 0x29F876C67D9304F9ULL, 
            0x365E893F7A96892CULL, 0x36102AD3D14783A0ULL, 0x6AC638513482BE22ULL, 0xB47C80AEBFF8E2F0ULL, 
            0xDEDED0CC8B552683ULL, 0x5B81F134962329D4ULL, 0x4BDD87E5EF050F4AULL, 0x3227F128941C77C1ULL, 
            0xC6704696D62AA3B6ULL, 0x7542597857742FACULL, 0x603BD0131E61EA91ULL, 0xB35BA7D6ECB1E3AEULL, 
            0x9DE7F2E481841EE7ULL, 0x1B10C68A716F78F1ULL, 0xDB7006C9012E2B6EULL, 0xBA9B97D85E8A29B9ULL
        },
        {
            0xD08CB742E0E6942EULL, 0x0AB7EA88ACFAAB09ULL, 0x172709C5145AEDEDULL, 0x7B8F68CF4C4E4F37ULL, 
            0xAAE5E4CDA353EA74ULL, 0x982A22DC9E2C565CULL, 0x2504EEA243DF9D3EULL, 0x0C035CF5B104C086ULL, 
            0x25B4AE73CD325488ULL, 0xBB430FC402A2405FULL, 0x0DE3CC08160587C2ULL, 0x952058A15DA6EE4EULL, 
            0x64ED81EF29B30CB0ULL, 0x52B3DF1EB1C1F39DULL, 0x32D254BBE5F6E75CULL, 0xB088116EE1D344EAULL, 
            0xAA37C0125EB0A4A6ULL, 0x7E691EB03A475F4AULL, 0x7947860CB42C8C03ULL, 0x2F5ACD1ED32DE193ULL, 
            0x37C80C0E699C6B86ULL, 0xD3DAFB8616FCBA0BULL, 0xC91DF20BBF63B46CULL, 0x17A95844566C477BULL, 
            0x820942B60DE8D4A8ULL, 0xDE57AD2EE6A1E1EFULL, 0xAF34C426E2A4D87DULL, 0xBA57A8537B2DB5B5ULL, 
            0x89CFC2A7E19282ECULL, 0xB37F1394F23FF571ULL, 0x679B26ADA45A1B6CULL, 0x616AFA82BC24D92CULL
        },
        {
            0xBE896F10435BB342ULL, 0x96781368B6A7F22DULL, 0xF87F70341151DD63ULL, 0x964A904924F902D7ULL, 
            0x0FD13E6207CCC980ULL, 0x028593142CBFD733ULL, 0x436F5A5264884B7BULL, 0x402F9E7308BC01A9ULL, 
            0x53DD01CBE62FCCB0ULL, 0xDE22C94C65C37A6DULL, 0x856ACF9B9C9A8A28ULL, 0x0F2C11ADD14811E4ULL, 
            0x2BB3C4901D2CB1BCULL, 0x6FAD2767DE9AA60AULL, 0xC949F096F933E1B4ULL, 0x8E64FA57A6211CA0ULL, 
            0x3D8AC2E3755F207FULL, 0x9DE00D30D48D39A0ULL, 0x930174D689214CA3ULL, 0x6EB1CA0F9C86746FULL, 
            0xAEBDF20588AAAB1FULL, 0x72D3FF380D4F5092ULL, 0xD880180D5F9C5F5AULL, 0x0129B558C0DEE4D8ULL, 
            0x97617EE39CA6EBB8ULL, 0x535852890F27D2D3ULL, 0xF9A8CE8686818A1BULL, 0x5B4981F7AF6DE0ABULL, 
            0x86782A60C5DFBABCULL, 0xB48F14D751B3E862ULL, 0x0132E0B28E481A7AULL, 0x086497B380BCD9D4ULL
        },
        {
            0x21A37CC3438EEDD7ULL, 0xCF92487FFA25C2D6ULL, 0xDD6D0CEA5164FBC4ULL, 0xB2D187DAD5A936DDULL, 
            0x3A51971DBF1C4738ULL, 0x5343567E3AFF7E2AULL, 0x82FC46683E35DECFULL, 0xF72EC7AED31DE31AULL, 
            0xAAB23E15EFF27A0EULL, 0xB81B2A3F28E4FD13ULL, 0x45B8779C17E52571ULL, 0xD601E27CFB2F0CEEULL, 
            0x2856829034713791ULL, 0x7ADE335CF68386C2ULL, 0x63A87C1F03B0A448ULL, 0x82549F9DB57CB27EULL, 
            0x87A92B781A842D8DULL, 0xA2D3BE9327675274ULL, 0x7C0BA5BCF18CA69AULL, 0x49EFE443A9D33CFEULL, 
            0xCBDB089B77363FF4ULL, 0xA2A4D6B0E74F87F1ULL, 0xAAD2A3769F3DDCCBULL, 0x75D31426A61045F5ULL, 
            0xC0156FB1F281D0A4ULL, 0xA78C924EE97ADC47ULL, 0x991B968CE7D27371ULL, 0xC6C84DCE7536CAA2ULL, 
            0xB84C19801D7995BEULL, 0x029DE3F331D32E16ULL, 0x7C48982650971F34ULL, 0xFCD7F891810E28B4ULL
        },
        {
            0x7BE33D325D31B65FULL, 0xD45B06AC6FE525A2ULL, 0xD65732AC58D31B9AULL, 0xE0FA937600D1E4D3ULL, 
            0x0231AEB066F425F5ULL, 0xB60CD5DC0D321FE3ULL, 0x9817AD5A804CB3FDULL, 0xAAD3DB3583C991D5ULL, 
            0xB61091003241FB6BULL, 0x51B1A30698E9533BULL, 0x50E12FA597C0395DULL, 0xD243F6A26124242CULL, 
            0x1FB7B5F192B1429AULL, 0xDB699E9119828A84ULL, 0x00E7C709E79EB097ULL, 0xF3AF5E1325AC07E5ULL, 
            0x2554B71073821DA4ULL, 0x9CFBE3B6F6A05FBCULL, 0x59A26E721E33A68AULL, 0x5A746A5B983F03A7ULL, 
            0xC7D3B65B5D5EC153ULL, 0x4F3994238ECD152DULL, 0x105BD3A5BC4BBCF1ULL, 0xBF1C4073153A9E9BULL, 
            0x1BE9ADE6CED25ECCULL, 0x36C628CD2F4A5FB9ULL, 0x02794B5E9C6C875FULL, 0x38112B424A10C504ULL, 
            0x1780AACBE93A17FAULL, 0xA54A0CC297988D2CULL, 0x3DB28AA5591552C0ULL, 0xF0BED59597F4BB48ULL
        }
    },
    {
        {
            0x0A0AD6B496EB7CC4ULL, 0x805D1EBBFED0335AULL, 0x90FBEB5A3B9F38EDULL, 0xAC6AA1B39D73C3D2ULL, 
            0x8CD81B4AE328878AULL, 0x1015FED516F2F81DULL, 0xFB0849D4E27967FDULL, 0x334D5564D6489613ULL, 
            0x7B5E9B68745709EBULL, 0x8C97BEA44F4C5E07ULL, 0xB471BD8132AC3156ULL, 0xA7204FD7DCD5BAC6ULL, 
            0xB86C7434B6F291C2ULL, 0x54A797780C22CDAAULL, 0xC1FA95BA42B22033ULL, 0x310FAAE6FB093442ULL, 
            0xC0EEBB3936179F21ULL, 0x77E157A233E9D4E2ULL, 0xD05E4E4AF67D5D45ULL, 0x3FDB716EE35CADE4ULL, 
            0xEBD8126876DAF6A3ULL, 0xAB00DA0208916D39ULL, 0x50D0E156A3AFED8EULL, 0xA90F5FE2D4B35061ULL, 
            0xB7EE156DB7568FFCULL, 0x58DB99510E25DC0AULL, 0x5E6A931B29989FD9ULL, 0xC59A4A6A24CE8AA8ULL, 
            0xF77284D5609F0DD2ULL, 0x28B661E99217BABDULL, 0x41C6E357021CFF96ULL, 0x83ADC6E73C2607BDULL
        },
        {
            0xAD01E423B56ACAD1ULL, 0x706F149394BBF2A1ULL, 0xF691CFDED2B99006ULL, 0xB36D9BA2F62A1BB0ULL, 
            0x71B1B202D20F8554ULL, 0x58BD15849C1AE5C0ULL, 0x92AA84E6FB6EAB4EULL, 0x8A0DE158DD383A1AULL, 
            0xB320DAA05CEA784DULL, 0x06B216256A150840ULL, 0x243279370EEC1E50ULL, 0x2A6FB42191FBB380ULL, 
            0x07C75CAD5D5B437CULL, 0x217791319C0B48A1ULL, 0x09FDE3064AD9378DULL, 0x949EC39440D62AC4ULL, 
            0xB91A02D65E2CF891ULL, 0x2E538986E68432E8ULL, 0x35D12FE77B8F0D88ULL, 0x2E4B1801CAC1FF1FULL, 
            0x7490D7F081E14005ULL, 0x12DCB0BDDEA79B80ULL, 0xE7676E7F5CD99759ULL, 0xEDCE94CDB8077CB8ULL, 
            0x66D13C369DD88D22ULL, 0x3F50099426D00B6AULL, 0x675D15D4E4C770EEULL, 0x9F3E5816815AF14FULL, 
            0xB3DE72719F3DAC80ULL, 0xB0AE2469AD62F45FULL, 0x4719730AD3DA7EF1ULL, 0x1D00439585B50BC7ULL
        },
        {
            0x7A0F99A24E728DBCULL, 0xEF6910AEA8F587A5ULL, 0x23008E33819B5F26ULL, 0x204BFBC82F480438ULL, 
            0x9312441C22141D97ULL, 0x8C4F8BAAB6685451ULL, 0x058C9E60D1750586ULL, 0x8FEB37D47715571FULL, 
            0x9E3D32D973C24D36ULL, 0x186A1EE142ACA8B0ULL, 0x63EC17162305C903ULL, 0x286011AD8C49532EULL, 
            0xCDB7721CE8B13D48ULL, 0xB3B858EF346ABB9EULL, 0x81FD7378932A60ABULL, 0x6447C649FFBF5E9BULL, 
            0x7B7FE6854BE2B610ULL, 0x4B719362D10F133DULL, 0x1574923EF6293CD1ULL, 0x30BE4E41466E43DFULL, 
            0x9994277B3330D42EULL, 0xE2673B3E37EFAE27ULL, 0x852A24AE9C9AC874ULL, 0x053E632C6C548342ULL, 
            0xD590C8B3DE0D252FULL, 0x4BEC89267D371258ULL, 0x5FF5B71D1EA76173ULL, 0xE3DCB475880E2950ULL, 
            0x263E04397DD6C745ULL, 0x8C2C9958E266B000ULL, 0xE5CC9AFCC1C3AD18ULL, 0xA0A9014A45611F42ULL
        },
        {
            0x3A7E71E3FC0655E3ULL, 0x7B73EDF39834E27DULL, 0x2FA2AE52880F8042ULL, 0x31C5CF5C48E157F9ULL, 
            0xA2F7AD11FE32BD46ULL, 0x4929DD1030FE9875ULL, 0x15124921049994B8ULL, 0x2A626CC01A3DF82FULL, 
            0x44DAD1557B5D3183ULL, 0x964F201E126E3D28ULL, 0xB45950168B58A29BULL, 0xEFECFBE8B33B718CULL, 
            0x61C5302CF9101C60ULL, 0x308C3EF955FD1E71ULL, 0x6E3A6888578B4F21ULL, 0xD10CE189DD9AA9D4ULL, 
            0x21A065807792EF19ULL, 0xB95FA84BF6AE43BDULL, 0xFE2158C6121025CEULL, 0x9DBAA6B5CE7DA66AULL, 
            0xA515BA16B5815B6DULL, 0x338A04740111911DULL, 0x83ED32F55104A7ABULL, 0xCB84ABFC2D10C0CFULL, 
            0x18A24412F7FF2F69ULL, 0x49BCE4107DC555B1ULL, 0x317A6DAEA0001361ULL, 0x080B2FE425A7B611ULL, 
            0xDF30A7AD76125D50ULL, 0x1B4BA5FDEB2E7FFEULL, 0xB28B4F5232B5EF9CULL, 0x6031D7F18FB6C5C0ULL
        },
        {
            0x023528E1EF0DB319ULL, 0x4CA5C40F7A9378C3ULL, 0x2FA97A61865673EAULL, 0x91448C84E48397F1ULL, 
            0x6AC7644E606D864CULL, 0xA3656AA1DEF93630ULL, 0xE244833D585FAE40ULL, 0x6500073621C64D9EULL, 
            0x906CA9AAD54891C3ULL, 0x1899464385A2313BULL, 0x24E5B122C111BBA2ULL, 0x43FAFBAB946480DFULL, 
            0xB0040B26F19FD7F5ULL, 0xFF0A08CA4EA74B3FULL, 0xFCF0F3002CD8BF38ULL, 0xA7820F6CCA71F3DCULL, 
            0x658766FEC24FE765ULL, 0xF359310401CAB9B1ULL, 0x2B05F1DE2520F557ULL, 0x3DD6C4C7C50A9BA4ULL, 
            0xDE670FCD7BF4BEC6ULL, 0x76AB1DD41D307D5AULL, 0xEA5FF7CC85730E7CULL, 0x594E25EF1F51B913ULL, 
            0x0B252F5E4B2834BEULL, 0xE6E9D3F344E99F6FULL, 0x50A0A86BD59813BEULL, 0x1EB7FF477CF215D8ULL, 
            0x42EB534260957B31ULL, 0x31BD502CAECB7608ULL, 0xF7547144D2B0B262ULL, 0x6C15963C4CB4EB67ULL
        },
        {
            0xF6CA53421B9B582CULL, 0xBDDD4B9CC6C4393EULL, 0xB0ED307673FF28D6ULL, 0x4BC6A3055207EEF1ULL, 
            0xA78A9EDC61E2ACAFULL, 0x582CE4435C32C979ULL, 0xC923F239C2B209AAULL, 0x735B1E6BFC21B717ULL, 
            0xDC865E83D138ADF5ULL, 0x5D6824A7D733061EULL, 0x023A677C8132150CULL, 0x3939C54DC15EA690ULL, 
            0x0316066F85C1F236ULL, 0x23EE72FC490E458EULL, 0x9807FCA776AEBD63ULL, 0x8FE8F779FAE9E8BBULL, 
            0xFBBAC991D61D0677ULL, 0x1913757B31E24BF6ULL, 0x7D82EFB212D58B3EULL, 0xCB4008195A0E2D38ULL, 
            0xFE02F63F0AD1479AULL, 0xA836207A5DD67F73ULL, 0x0A79437A66C20C28ULL, 0x7774B18D24513C7CULL, 
            0x334CBC39416F88CDULL, 0xB95D19EA67334258ULL, 0x1D15428F7FC3F6EBULL, 0xE7470369BA4486ECULL, 
            0x7B8BECBB714D8B2FULL, 0x43C96B289C38AD3BULL, 0x06DA5FE5AE1B0DB7ULL, 0xAAA242FA50EF498FULL
        }
    },
    {
        {
            0xDF2DBADCB9241085ULL, 0x2CFB55644C84AB91ULL, 0x556DCB39BE0C672EULL, 0x6E78AB979E187200ULL, 
            0xA92D112CC1D5EA63ULL, 0x7D4FF925563F220CULL, 0x14365D87BC341AF9ULL, 0xFD0700D27A61973BULL, 
            0xE9E94C9BFE765B40ULL, 0x695508D1C58A0EFDULL, 0x570D9DEDD9FA9F95ULL, 0xA35941336A3224C6ULL, 
            0xC1E8EBA3D7AAD17DULL, 0xD49B8CB8E2D8AA81ULL, 0xAB49AD3BF7364276ULL, 0x210B01C53E962FF9ULL, 
            0xC74C6DCCE0955D46ULL, 0x0B44999A98E5DB44ULL, 0xC5D3E6A03669A697ULL, 0x1EF3144B3C600C2DULL, 
            0xD31051D8C0BB970CULL, 0x9F44D0056C8392C3ULL, 0xE69E637D63F41C54ULL, 0x10294D9AD41DB4F8ULL, 
            0x1033D003481847FEULL, 0xE840A9A06253776DULL, 0xA24E37B6A5DF2703ULL, 0x70F1B2B002D3BDA2ULL, 
            0xC27D7D831F9E978EULL, 0xF9666F3D9972F1FBULL, 0x801BE0D0F1534A9FULL, 0x4BBEB92B2631342AULL
        },
        {
            0xFBE25D92D895C4CAULL, 0x8A1A4474EC578A57ULL, 0x9F62BA911A6B9625ULL, 0x726DFCB43A80FAFEULL, 
            0x1602BB2F5AB4CEB6ULL, 0x1B9EA936F5F66966ULL, 0xC63FE230BCBAF9F3ULL, 0x229AE237610695F6ULL, 
            0xA3AAD62EE237CB6BULL, 0x31D7CA19E37AB3BEULL, 0x869280FFF412E350ULL, 0xA27CA7EB5B888771ULL, 
            0x5464D82B3519B783ULL, 0x32CD234815996485ULL, 0xF3EAE17B4981E2B2ULL, 0x29B1B6B4ED2E74CBULL, 
            0x648C983AC24B3752ULL, 0xFD6DECEAA578F71FULL, 0x73647263CC5B5542ULL, 0xDDB7AAA8843D5DCDULL, 
            0x5FAD3C5B038F94F1ULL, 0xB0C09FD34108E0F7ULL, 0xCB0807751079843AULL, 0xDB9D5641918BE6DAULL, 
            0x2BBE692AE0D695ECULL, 0x1CA2D134EA0061EDULL, 0xF948BD7AA3364275ULL, 0x713D5195146AE437ULL, 
            0x170D1F0B4A89BAA2ULL, 0xBDC6EDA79C746E66ULL, 0xD421F09100556F4FULL, 0x00002B6768612FBFULL
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
        },
        {
            0x309D07E5BA3A3FC1ULL, 0x390B2E59C5D61D43ULL, 0x1A6A6CA514156DC3ULL, 0x2B4596EDCC168721ULL, 
            0x95BDA1B60B945832ULL, 0x736C577B07146EF0ULL, 0x5BEB06DD0FED252DULL, 0xD5A8685D7DB1A6EEULL, 
            0xD116C9CACAF5731BULL, 0xBD4CC0CE575AEFBEULL, 0x3895937FAEBACA14ULL, 0x8795CEA1FD775399ULL, 
            0x17AE854AB1146E9DULL, 0xF09A4D9F56B04276ULL, 0x9821BE624A5ADD52ULL, 0x29451E28F5DE2E85ULL, 
            0xFCF961B6EB59B739ULL, 0x0DA77AF80E97081DULL, 0x78AB937048F2E265ULL, 0x0F2F3A5B6AE8D57CULL, 
            0xB0CD5FA2581EC9FBULL, 0xD55E6395B4702088ULL, 0xBBE8DD1B56DF614EULL, 0xDA44136978478320ULL, 
            0xE2D68935DD17D8E1ULL, 0xCE5F089A512DB98CULL, 0xD582561753C14531ULL, 0x4567854F98B2CE0AULL, 
            0xE21C83CB09CD3CEDULL, 0xA550CAA219B2CFD6ULL, 0x933DEB7489B59768ULL, 0xE326B530080662F6ULL
        },
        {
            0xA53AED78232860B6ULL, 0x073B76803E1C4682ULL, 0x1C05CB494DF73B2DULL, 0x53B6EC1229D8F283ULL, 
            0x3FDAE4913E02425FULL, 0x0E6773A8B58B9971ULL, 0x6D833805D9366AACULL, 0xE2C4E731AEF086CDULL, 
            0xB9B64BBCCF4C9FABULL, 0x461014F8B88F9B4EULL, 0xCC638BEC05C9BE5DULL, 0xFA78DD47921BAA11ULL, 
            0xBDB87B1EEE197948ULL, 0xDEB9AAAD09BE03E0ULL, 0xE4519B8EA4644F74ULL, 0x5C73190008CFF4FAULL, 
            0x97A8E782AC640FA2ULL, 0x5558F6722F1BE0E7ULL, 0x1ADC5D3F1E726682ULL, 0xAB89041B9A1FE7EDULL, 
            0x451B471A431AD4D4ULL, 0xD51D0F5A8235F946ULL, 0xDB017EE04DBBFFBCULL, 0xA89C1DA9A416F046ULL, 
            0x6AD23092B3CAF7B9ULL, 0xD925773707743902ULL, 0x72491D42782E9311ULL, 0xB214036B24F4C4EFULL, 
            0x8658A22591EF675AULL, 0x8F936E4AFD81BE17ULL, 0xFA0E9E40A98D9BE2ULL, 0x76C1612B2CC9FC2DULL
        },
        {
            0xC00B7095AC5D0C46ULL, 0x6EE5760844192BF1ULL, 0x3CF524186BF39706ULL, 0x6C14B9A069C76C6BULL, 
            0xAF47E0CA4C4E3193ULL, 0x3D31B3C0A4F6CA5CULL, 0x88B2CF7677E2BEC2ULL, 0xF08AA8FB08FC7661ULL, 
            0x97546C3D24582591ULL, 0x58C9E64CFE59C42FULL, 0x5403760729F7FD1AULL, 0x808521241329AF65ULL, 
            0x6714CE32B57C0AB4ULL, 0x8A902994575D18D3ULL, 0x8F1D99B62489B6FEULL, 0x3A98A0EA723C3A67ULL, 
            0xC7D3E43C20D0F2F9ULL, 0xB50148E5A3258420ULL, 0x8FF39330A49A2C43ULL, 0xB758CAAE89DCCA5AULL, 
            0xA25CD140787AC70CULL, 0x36E786A241D8C21AULL, 0x814267115308225BULL, 0xF80427F995F93636ULL, 
            0xC98C8C43B56252E6ULL, 0xFE6A112262509081ULL, 0xDE6AF901A70440DFULL, 0xA733824D7649EEB6ULL, 
            0x21A4F56C7E510C64ULL, 0xA4703040717CEDB4ULL, 0x85F1BB0FCA9ECDD6ULL, 0xA78EC6571DFFD299ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseFConstants = {
    0x58F77A76FAE443A7ULL,
    0x41DA71E7A656E69FULL,
    0xBB0A6BB8617957D2ULL,
    0x58F77A76FAE443A7ULL,
    0x41DA71E7A656E69FULL,
    0xBB0A6BB8617957D2ULL,
    0xF5B1E548602F19ECULL,
    0xC0478483F386E305ULL,
    0xEA,
    0x9D,
    0xFE,
    0xDE,
    0xB4,
    0x05,
    0x6B,
    0xA9
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseGSalts = {
    {
        {
            0x3D4252143104593FULL, 0x8903BF78582FC92DULL, 0x8D2F6E3F15806CECULL, 0x08E637863AEF9ED0ULL, 
            0x1952FA65C59FC009ULL, 0xEFAFD26F74310163ULL, 0x588C4581BC21B574ULL, 0x15098DBC57632C10ULL, 
            0x860E20AAE19771A4ULL, 0x5A56C0890E0FB277ULL, 0xF21F0D123C99D0BAULL, 0x300B3ABA8BB0D588ULL, 
            0x98674D4D729AD835ULL, 0x502D0ED4AED5DE90ULL, 0x94D66784967E9A13ULL, 0x461378D5A2720C5FULL, 
            0xFC489281C68B6C47ULL, 0xD6DCE3610982378AULL, 0x021701D7BE873803ULL, 0x120D550BCD0EED07ULL, 
            0xF0BA473ADBAC1D52ULL, 0x95F1F02064B2A3C3ULL, 0xB1184764B57245C7ULL, 0xE57C8FBFF2DE1080ULL, 
            0xEB0AB7F583B70632ULL, 0xCCA4D77E8ADAFC69ULL, 0x1A9A22ED7309FBE1ULL, 0xEE081C0FFAB3B37AULL, 
            0xBE6A2E9650B36C06ULL, 0x2E1CE6DD8E33CCF4ULL, 0xA5B42AAADC483102ULL, 0x994ED7323CB63FDDULL
        },
        {
            0x042727DB625BDD8BULL, 0x1D4614637E9ACBC9ULL, 0xD9F9BBC4D36F9832ULL, 0x599085EC0DA6A0D3ULL, 
            0x1AE284AFA65D4467ULL, 0xC46B34662C514B10ULL, 0xB3613D61CD6C33B2ULL, 0x29BDB366B212D6E7ULL, 
            0xDAD27609BBC2F5F0ULL, 0x5285C7B0B60825CFULL, 0xFDFA9BAC715EC832ULL, 0xC4E942A0AE641E9FULL, 
            0xF3F86AF657B47819ULL, 0xC729615E72B9682AULL, 0xA8451498ADE1D390ULL, 0x965E19B8AB558114ULL, 
            0x7AED516314CA70DBULL, 0xAF1A69C91D41EEABULL, 0x3B0386CFE1760BF8ULL, 0x5D5DAA31D83DDAC1ULL, 
            0x035C134E0ACD60B0ULL, 0xD338F2D8FA55484EULL, 0x3D60E2BADEE3FFBAULL, 0x7F4EA04CEB6D4588ULL, 
            0x8F11D8420E14D9DDULL, 0xE2D7123ADA44A883ULL, 0xC99318CD108FADE0ULL, 0xF33CC2C7E072A6EBULL, 
            0x924ACB8566DF6BAAULL, 0x608AC36C44F73F67ULL, 0x7CEE4F126D686FC3ULL, 0xA1BE0227DB19D017ULL
        },
        {
            0x7AA91BBFE9E646D6ULL, 0x7E5CFD561A5C1EF5ULL, 0xD1AC757002BF3DF5ULL, 0x8B5D0299FAED11AAULL, 
            0x50F723C9AA58E5D6ULL, 0x64706EFD65FB974EULL, 0xFA444CF24A86901AULL, 0xC58D3AD720DE97C8ULL, 
            0xE292A0932B0C4C67ULL, 0xE785A0A864F91CEBULL, 0x1E43F65AB7A6B74CULL, 0x5DA3F41CFA78CE29ULL, 
            0x2DD2120B3C2AA675ULL, 0x9B3DABC61A59B551ULL, 0xFC55B1ECFE36FD94ULL, 0xA2C0BE9802EBB9BCULL, 
            0x4404E6F83866D5F7ULL, 0x8E6BCC2589746502ULL, 0xD427263ABC109951ULL, 0x5FD2ABA916A2C15AULL, 
            0xD30C3380AFE87E85ULL, 0xCC6563E0A97DDF0DULL, 0x1757A17A5FEB31A2ULL, 0xA9F18B094A725AB0ULL, 
            0x655E8F86C61D53BCULL, 0x4E91A3E33D76A057ULL, 0x302DA647CE027985ULL, 0xE96B653EE37755ACULL, 
            0x0CE2DD33AF2EC3C8ULL, 0x76640056275DEFAFULL, 0xD271C7D7D466824CULL, 0x87899087CFB12DF6ULL
        },
        {
            0x0BF5B8A6E03CA1BFULL, 0x3B06CD420C7CB3B7ULL, 0x27F04F12A093DC45ULL, 0xCE2B445F9C4ABE5EULL, 
            0x669FD8C2FEB39ECEULL, 0xDBC313BA55EABE00ULL, 0xA300BCDD3CF79F37ULL, 0x64E19D5944749347ULL, 
            0x9CEED1AA0D46ABE2ULL, 0x104314E4BBCAB8F1ULL, 0xB43C5F40C7B9BC53ULL, 0xDEB85D3C4B7A7337ULL, 
            0xE1865A4911E98400ULL, 0xB09BF64B7967DA53ULL, 0xFA58DBBDA28ED875ULL, 0x1FD42580DF096C2BULL, 
            0x98B1F85F5F5F8118ULL, 0x6C232A44237CE887ULL, 0x0043AA2A4E78359BULL, 0x9CB728F0901750E4ULL, 
            0x6D8F9071EE86D0C7ULL, 0x3480AD457D547AF1ULL, 0x99615810AAE31E69ULL, 0x5EC78DCB5EC4BA01ULL, 
            0xD65D1E9A8C08A8A2ULL, 0x8AD1EB1064B791D4ULL, 0xAF0D8DAA7EB551C0ULL, 0x7B7165914FACB649ULL, 
            0xA7442FE31D1399CBULL, 0x2088F673938F3A66ULL, 0x8014278E0A66E9CDULL, 0x4F9D04F728A0533BULL
        },
        {
            0xCA03598B541DE06DULL, 0x289D9142AF2CF3D8ULL, 0x53A5B312F6DB8096ULL, 0x3B6016C913F41D05ULL, 
            0xB64D46E9009029D5ULL, 0x4A45A95171CE68E0ULL, 0x4309388C86831A1DULL, 0x0FD96FE0F48DABD5ULL, 
            0xE6290A5DE8DA495EULL, 0x86C76AC7866DA45DULL, 0xEE5C1DC41EA728EFULL, 0xCFD75471ECFF56C8ULL, 
            0x190649579AE56F94ULL, 0x0402F79AC64A0B2EULL, 0x3C6AEB28E6A08F00ULL, 0xD29677F138EDE486ULL, 
            0xFA4B974FEAA72535ULL, 0xE8166E1DD18EB432ULL, 0x494B0B81D8FD76F7ULL, 0xC008A52BBFC0266CULL, 
            0xED1978B5FF4597ACULL, 0x558570C8E44EE3F7ULL, 0x5C8BCB63644708B4ULL, 0x12BABBABF0F5729AULL, 
            0xE3BF3405FD4E6CBDULL, 0x3E5A91B97A0B5F7BULL, 0xC540E6B245935EEBULL, 0xCD5A7B7FE3B5E97DULL, 
            0x7EFDBC06A23C0585ULL, 0x51173EA3E7D9C0A2ULL, 0x6681152F2333FE33ULL, 0xF9CB2DF4EF6265E3ULL
        },
        {
            0x56A21F96B9CD2B94ULL, 0xC9609A9278F3C5E4ULL, 0x9B273546B25C1AA5ULL, 0x918A80D079B6A329ULL, 
            0xB84CED052A9D7567ULL, 0xA72421A598B3ED38ULL, 0xF011C47DDD91F178ULL, 0xAEBD64A110832C0AULL, 
            0x3DDA82112CFD8D69ULL, 0x3E809FB2F1B97150ULL, 0x7A32E6D5850A3461ULL, 0x131C5EDD11FA46CFULL, 
            0x868BA6066136A138ULL, 0x4ED18B7A67C45B98ULL, 0x6E282AAE0D335974ULL, 0x05A20AB1A6F760A7ULL, 
            0x9B59BD7AC13DF180ULL, 0x9849CC92B835AAD1ULL, 0x5D1E3AEB138D4E5AULL, 0x659AD6557E18D10BULL, 
            0xF6A3C322A968A4D5ULL, 0x5F7CEE10C2D8ED70ULL, 0xCF9E809FD0954D24ULL, 0x67D563F66A070049ULL, 
            0x794C3CFFCD7F24D5ULL, 0x5C043357153B59A3ULL, 0x1449603CE25ED648ULL, 0xC80B2B221294E65EULL, 
            0xC9821C2FDE1F0FC5ULL, 0xA47F0CDA5537688CULL, 0xF0FB089A1D8A407DULL, 0x11FAA62C5F9A45FDULL
        }
    },
    {
        {
            0x5DF748E36D738B40ULL, 0xD517E4556EA948BFULL, 0x5B2CB8D438F40FADULL, 0x037EA2C6FAB4F844ULL, 
            0xC6283132FACBFED0ULL, 0x27C8FEF4E868043CULL, 0x748977AAB939622BULL, 0xFDBEDDFC1ACE2699ULL, 
            0xEDD78F63716DBD92ULL, 0x9DFEB02A04B420EDULL, 0xBC59D51F5ECD134CULL, 0xC26E470E149E3F70ULL, 
            0x899FB58AC847D1D3ULL, 0x6484C426C9AF155FULL, 0x1055E32E3A57261FULL, 0x9D71B1F5BCE39206ULL, 
            0xA462EED0F050AFFEULL, 0x05115A419411BF55ULL, 0xD29549CAEF8105FEULL, 0x554FB13F36B3F978ULL, 
            0x27E777F3B114E31EULL, 0x62AB6A6389951CF4ULL, 0x683D2334003F9A7EULL, 0x4D1A28C6D2F5D259ULL, 
            0xE3651CBE2670F65AULL, 0x7A5F81B3E4365551ULL, 0xFEBDAD01738CFBFFULL, 0x66D96EA9F52F0275ULL, 
            0x6EA34E2A1741116CULL, 0xC67A564D9405CD42ULL, 0x9059409FCF4DE6F9ULL, 0xFD17C5BDA2C13201ULL
        },
        {
            0x8B48EF0A94CA2F77ULL, 0x7C8AAC898EE05022ULL, 0x2094DEB41CB5869BULL, 0x4A714ABB5066A77FULL, 
            0xFB49E0E395E6EA2CULL, 0x1BA802A9F9369C4DULL, 0xFA365C8CE20F3ACBULL, 0xD62A09E692121C58ULL, 
            0xDC75A4B6DE966B32ULL, 0x00EC998B484DF9AAULL, 0x7C1759F6D1A044D2ULL, 0x15C8A74B4758BD6BULL, 
            0xD4D466969EC4723CULL, 0x7E2463812CED1C74ULL, 0x6A1B69CF793150A7ULL, 0xA23C03DE0A4C8D32ULL, 
            0xA9D9BBC3D46FCB08ULL, 0xD0F41CED924C937FULL, 0x8BB0CDE191011172ULL, 0x1D3D684D5F5DB60AULL, 
            0x9B485D1A6EC57836ULL, 0x5551F04223025D50ULL, 0x247A739742B5298FULL, 0xB81612B3B16CDC2AULL, 
            0x2F69E082E19CC9EDULL, 0xB173905E68E47E3CULL, 0x8ACAA3C54135858AULL, 0x3D48F2EAC40347B6ULL, 
            0xDA71AD8505B306FEULL, 0xA0EB7FCE46FBC072ULL, 0x2A1E20EB77FC114AULL, 0x9CB52F76474E27F0ULL
        },
        {
            0x73A89DD4EDECD852ULL, 0x1D603843773FCE81ULL, 0x423145C1472993C5ULL, 0x3AD7C00C7B787484ULL, 
            0xDD00D1AE7EFED99FULL, 0xD43C7BFC0E2AFEA0ULL, 0xB9A6706D6DAB4058ULL, 0x492B07D5F7F46640ULL, 
            0x9E620B26265D3E99ULL, 0xAFE45FE2AE3737D0ULL, 0xC4B28F74913342C4ULL, 0x186B5F442DEF8EBEULL, 
            0x4019D9C157509640ULL, 0xCC5B5D1DDDBBD538ULL, 0x28F75BE585B67C53ULL, 0x4DDF5F0406532DD4ULL, 
            0x18564569B664FF81ULL, 0x54BF2AB5A7925E93ULL, 0x6CCCFB765C060021ULL, 0x01852C785C788C85ULL, 
            0xC03D267224F00DC6ULL, 0xE4CC2B7CE31CB15CULL, 0xBFF8B36BF30DB58EULL, 0x1FBE10A59021583EULL, 
            0x264D20C4AF154773ULL, 0x6F79F52BB508416EULL, 0xA313EA9F78CD187BULL, 0xAADB9DEA193E2B49ULL, 
            0xC646943E0D4A1DCCULL, 0x6A22D47DA5B774D9ULL, 0x2CDA4454500F464BULL, 0x95200630D5615D78ULL
        },
        {
            0xBCAA2E440901A018ULL, 0xD76BFACC24235424ULL, 0xD69583E8269C3F96ULL, 0x55EB41E78524AEE9ULL, 
            0x628BEA9C8DF46D56ULL, 0xD78C31812A2653CDULL, 0x906943078A2FF6BCULL, 0x890ADE5BBB9C7377ULL, 
            0x13903F45E465792DULL, 0x8F5B01481BCF2AC8ULL, 0x3C38C3A4A679FF1CULL, 0xAAA8BD247FDD9838ULL, 
            0x1FECCE50059B2AE6ULL, 0x976B62B10CDDA438ULL, 0x1E7C7B6BF15AE59CULL, 0x70EE13EFA23D43CCULL, 
            0x1B077A734B587977ULL, 0x9310F12DE102058BULL, 0xA78300C47C635C25ULL, 0x9CACCB28C4F0D8FBULL, 
            0x8ACE600A65B41814ULL, 0x83AB45DEF91C8547ULL, 0x6E3C9D08067BA3BEULL, 0x28CBEC70AA4FF922ULL, 
            0x45E106BDE4D8F663ULL, 0xAF00FFB01C4DE8C1ULL, 0x245F3BD1EF8EC464ULL, 0x52CD79A87CEA397EULL, 
            0x24380811F7E20A92ULL, 0x425A3A8197BDE2B4ULL, 0xD95934E83F6A3D2CULL, 0xFDFD62E8C156879AULL
        },
        {
            0xC873CC7A83326DDBULL, 0xFA657A57FABD29C6ULL, 0xBAE82090A0F3743DULL, 0x6B303F59E366A482ULL, 
            0x7EA78A73A5AB173AULL, 0xA4ED6F8D273E0164ULL, 0x7E39F807D6598D7EULL, 0xD68D798C50043106ULL, 
            0xA9C6A20608C0C74DULL, 0x6BA9E022A9750167ULL, 0xDF0E8079E72C3713ULL, 0x2765827BD56F954CULL, 
            0xB86F4A316E14EBB2ULL, 0x0ECF41C89D692BCEULL, 0x567DAEAF1E9F1A50ULL, 0xEA482F20B7FA7BB8ULL, 
            0xCE47C7406F266C43ULL, 0x820EB76BA3810500ULL, 0x43C85BE2BC7A7EB6ULL, 0x64C2BC03EFEF3FDDULL, 
            0x374708E562954B85ULL, 0xB1ACC5D983F7A0C2ULL, 0x1C5C4F0B6C2A82BBULL, 0x2D33DDB58F4BBE0CULL, 
            0x01B8671CE9C3B610ULL, 0x624B882220CDAB95ULL, 0x5697A86338405F4BULL, 0x0A846DB53161885CULL, 
            0x74D395C83925E32EULL, 0xB20BD8D4344BA70DULL, 0x661E42050F4AC89DULL, 0x1573B56CED4F94DFULL
        },
        {
            0x4CADDD2C012F83FFULL, 0x8EF5C4C600AED4DBULL, 0x552C65B6D7831C4AULL, 0x6B393689635DDFCBULL, 
            0x6C394B7B1EE9B9B4ULL, 0xB92EF8557E5209D5ULL, 0xA1D961843116C347ULL, 0x4BA147C3644672FCULL, 
            0x829991A0939D4890ULL, 0x39536153E61C3D86ULL, 0x49E9E89C6E000918ULL, 0xE76000C78C03F929ULL, 
            0xEDA91893DCF7791DULL, 0xE8611C868124621CULL, 0x901C915E394BC000ULL, 0x65E39983A1F06C0DULL, 
            0x57FDAE28910C8AF7ULL, 0x7633EB96C439A504ULL, 0xC19F1775CFCD2565ULL, 0x32396534805CFF4AULL, 
            0x976723B8D7185A6BULL, 0xFC10B05FC83133BBULL, 0x940A6D5D210EEACAULL, 0xBE0505501D089AAAULL, 
            0x3EC6974594BF321EULL, 0xCF97E0ED463622D0ULL, 0x0155ED3A638CA56CULL, 0x531D6BA96C88A6ABULL, 
            0x6668C6A670B3402EULL, 0xE27FE4D28BF034E4ULL, 0x166C155390BFADBCULL, 0x572401AAD48A0BC1ULL
        }
    },
    {
        {
            0x89F9A1FC1C886068ULL, 0x17154EA405A953E6ULL, 0x8B8B6C582F10A53CULL, 0xD214B5E9CB39B170ULL, 
            0xEB5204FE63EF6DC4ULL, 0xB44FE99D15CA9D72ULL, 0x9E2FFE6ED1435FC0ULL, 0x06A479B79EEF15D3ULL, 
            0xD95191D7A153DF47ULL, 0x59D5820A8B2C48C2ULL, 0xB62C92557FCF5B71ULL, 0x5B62233E4F3D8B88ULL, 
            0xDC87BD39D86F58A4ULL, 0x6FE68D5813D177D2ULL, 0x5D846ABD845AF9B2ULL, 0x1C155500C5D7AD70ULL, 
            0xE4331CEBC148D45EULL, 0x39C5E47E25EDDAD3ULL, 0x1D48D2F361CA4DD6ULL, 0x938E853F029E7399ULL, 
            0x8D5CF765598136DBULL, 0x2C2E49D09F265CE4ULL, 0x021DD68D6306F62FULL, 0xB5751110577964FAULL, 
            0x9B31ABBE47CDDF7AULL, 0x76D968E1BE686DC0ULL, 0xDB1D29E142AD0475ULL, 0xC5FEEF46EBA4D1E1ULL, 
            0x57004BB607092B03ULL, 0xF3CE4DD7C305BCD1ULL, 0xFB1872FEAC79A7D2ULL, 0x4FD3E393B0BA4464ULL
        },
        {
            0x85B5BC841FC0D9EFULL, 0xD326D1F251620FF7ULL, 0xA1CAFE9C6326698BULL, 0xAD3121EE00EC9C2DULL, 
            0x8171792A12078C9EULL, 0xD501F55E216EB4F1ULL, 0xF7733FD683795396ULL, 0x1AE432BFE1C72BABULL, 
            0xDAB7853FE4DBE1D4ULL, 0xB7C187B8746A3613ULL, 0x87089274A75F5F4AULL, 0x2027DF79A262C65BULL, 
            0x97F89D33F4B0090EULL, 0x94C3506BDE050130ULL, 0xBB52AE362142F39BULL, 0x5477DF1C152B02BCULL, 
            0x9F69266A8CBCC85FULL, 0xA6EDF4B7ABDAE194ULL, 0x4B1E718C58CBE2B2ULL, 0x2614BFAA44B7AEBAULL, 
            0x05E32E67FF7BDEE7ULL, 0x9B2BB46085CDB574ULL, 0x4AB0254BE25741FDULL, 0x811AFAF3AF03092FULL, 
            0x31FE295D48EE00FBULL, 0x525A8978A5681974ULL, 0xD344FCF9C199025FULL, 0xB39DCFF3FFEDA84FULL, 
            0x89FD75E3C3128B7FULL, 0x505645ED9263FC90ULL, 0x3CD438B225B7C820ULL, 0x2AEF9E648559A6CBULL
        },
        {
            0x435AEA767883286DULL, 0xB27547EC9E4FC77EULL, 0xC3A187C7CF45A698ULL, 0x45F058EF5DC09116ULL, 
            0xAD426A07D4F57E9AULL, 0xAE753017D7323266ULL, 0x2BDC1CFBD83B593EULL, 0x4920954516F8D0D4ULL, 
            0x18624DF7C8AE6399ULL, 0x652CA87A62360F5AULL, 0x6548B3A051C2EF5AULL, 0x804344190DB49714ULL, 
            0x9BD77505752C9A81ULL, 0x34DC1D70108E32D5ULL, 0xAFA744F92EA793F5ULL, 0x12FC3244DE5C5318ULL, 
            0x5FC7E0523716C669ULL, 0xCC3EA15A30559CD8ULL, 0xB59AA3286AF1C2C3ULL, 0x2D4C2C3DA719EDD1ULL, 
            0xB60213AB305730B5ULL, 0x5A6ED51EF171096FULL, 0x3AA9A85AECDD1AC4ULL, 0x53DC39BF9E911912ULL, 
            0x3FC8C7A682292AF6ULL, 0x7A2B02A534B2E6B8ULL, 0x67A5FBA28153C694ULL, 0xBE321522965E4BFBULL, 
            0x39656CAE4BED90E3ULL, 0x71BFFC6BB0D31849ULL, 0x2AC1003F3BDD7679ULL, 0x3AD2D748D00F0E98ULL
        },
        {
            0x879CC21FF78A0ACFULL, 0x9F32629710D62027ULL, 0x4C57BB2D0511BEEDULL, 0xE6F6452ACCD469B2ULL, 
            0x12248D1466E5F96BULL, 0x05FBCA875030B57BULL, 0x63539DE533B03E8AULL, 0xA5C9C4D1DCC802C0ULL, 
            0xC38899D4BBC444F8ULL, 0xC8366EEDBB41D913ULL, 0x87D10EE9869415EAULL, 0x4F6B61A8E1D8E911ULL, 
            0xFE6DB846A96BD0F0ULL, 0xAAC959A8D656F4E7ULL, 0xF0037B31E14EE324ULL, 0xCDFDEC4864BDAADFULL, 
            0x1CD743F04D858188ULL, 0xE4E26AF94543A683ULL, 0x0552FB82C333D080ULL, 0xE5223C031D5ED897ULL, 
            0x91E52E27B4D69ADAULL, 0x4E13C19F73156846ULL, 0x44F4B3558AC0541CULL, 0x8C144CDEB37E05E1ULL, 
            0x762E4F751D0C1507ULL, 0xE44491D2BAE4F160ULL, 0xABAE5F7DBB3B5BD3ULL, 0xF327FDD822788ABDULL, 
            0xA2101BE2B08C9B02ULL, 0xC7F4437E309D646FULL, 0xA68239C52235B7A6ULL, 0x7C18EFAA8C412BCAULL
        },
        {
            0x9F2C021B8F674A38ULL, 0x37C6811EB323D5CBULL, 0xAAA89F40CE857AFEULL, 0x6285CB428FD139BDULL, 
            0xE6CDA76B90C60C2EULL, 0x85B4F486C2055BBBULL, 0xD06E26697D972CDCULL, 0x59B8E8FC6543AB4CULL, 
            0x273602929555F180ULL, 0xCA5E89845651D997ULL, 0x9B91F37D5F84E838ULL, 0xD32ECD48861B8035ULL, 
            0x425AEC55E478321AULL, 0xB8F167330E58220BULL, 0x56ABB157478CD819ULL, 0xB405F556034E384FULL, 
            0x5DD327568079A466ULL, 0xFF83819C24C1B91EULL, 0x23DB51FD4841C394ULL, 0xA8BB2757D03FB37FULL, 
            0x7EE233459535072DULL, 0x7055077C908A2442ULL, 0xC42A6164A7A6A81AULL, 0x9CBB7EC516601094ULL, 
            0x9EDA622908913484ULL, 0xD2EF3CECFF294E6DULL, 0x89E2A248A48A8D8BULL, 0xED7AEB9F47BB4799ULL, 
            0x8485EEA1A6A109B5ULL, 0xB5D6915F6BB310E7ULL, 0xCE540976DFDEDADDULL, 0xE0F94DDCDF62D135ULL
        },
        {
            0x4667E4C3A6991D59ULL, 0xD8E686C9F69C7A55ULL, 0x6FA391B4B46214F7ULL, 0x56FF63EA1CA12811ULL, 
            0x15E6E803A0156D78ULL, 0x7D5ADFF3D75E17F9ULL, 0xDCB69BDCDD1AA6F6ULL, 0x95A4C36775BF0E32ULL, 
            0xA6D1CFF28EC00BD9ULL, 0x726426E2DDBAC3BFULL, 0x7CD1EDEE8F492050ULL, 0xCA112D324A30A8C8ULL, 
            0xFA930F871C667A5CULL, 0x6FFBF7C05C0AEE54ULL, 0x76DC582E41B3A008ULL, 0x65984B463DECECD2ULL, 
            0xC812433B09FC4872ULL, 0x9704C8254735D3B9ULL, 0xFC6E4D00A7F3CAB8ULL, 0xFBB44806BAE25955ULL, 
            0xAC496329F5317C5DULL, 0x7C9DE5E85C10A09CULL, 0x4BCC83001829CEB0ULL, 0x170103605732B302ULL, 
            0xD93A06D246C5C85CULL, 0xC40AF5AC1156FD83ULL, 0xD970658EAA4C7C65ULL, 0x6B61DB5AE179E6BFULL, 
            0x8C0E6E3778FDD82AULL, 0x0279FA535361CDAEULL, 0xC0D6F9F2473E1B16ULL, 0x1B6CDEB1579B0906ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseGConstants = {
    0xDF4C90E4D1F3004AULL,
    0xDE1042E353DE6F51ULL,
    0x81EB51515855DDFEULL,
    0xDF4C90E4D1F3004AULL,
    0xDE1042E353DE6F51ULL,
    0x81EB51515855DDFEULL,
    0x20010A8BFA3C3B54ULL,
    0x40D6D1A99CA4C187ULL,
    0x32,
    0xF0,
    0x80,
    0x8B,
    0x2E,
    0xC9,
    0x65,
    0x14
};

const TwistDomainSaltSet TwistExpander_Mirfak::kPhaseHSalts = {
    {
        {
            0xFF84917B64646C9FULL, 0xAEC887E396E55671ULL, 0x5708761B98CFE0BFULL, 0x6E8FA80D9026B475ULL, 
            0xDA85B149D3454136ULL, 0x687EEDCAC9BC338DULL, 0x8CED84C826AB0AC0ULL, 0x21E1995B4C0134B3ULL, 
            0x7C7344A0E02DACEDULL, 0x1813BD5FB4060DADULL, 0x8A7663288DA28563ULL, 0xA302B2A3E997E10EULL, 
            0xD70E39E7984ADD4BULL, 0xA7B7EFE85476A774ULL, 0x3380C2F43C12228DULL, 0xD15EDAA856BA4609ULL, 
            0x87F204904FFDACE9ULL, 0x5C4DB44291954467ULL, 0xB36AE0FA30E76057ULL, 0x19AA64CE3DA763DCULL, 
            0x60E6A0C874B3C436ULL, 0xBE5EF716372F8878ULL, 0x52D5DFFCE92DFDBFULL, 0x8709FCA287144975ULL, 
            0xD343CF1DA30B16DBULL, 0xABD5D5B2FEF5B609ULL, 0xC6619BA7F47D1098ULL, 0xC148BB4E05B73AC9ULL, 
            0x599D154CDDAEC8D9ULL, 0x2E5C71C0D3CE3A43ULL, 0xEB45BF682309EF58ULL, 0xA49ADABC8D50010BULL
        },
        {
            0xBE3C6E773EEAE599ULL, 0x2A7BD9CA5B59F376ULL, 0x8664968C3FDEA793ULL, 0x8F19B7AA6E079F34ULL, 
            0x9B364EC018E3572AULL, 0xAF0A0AD7C233B4F7ULL, 0x28478FDE7B5F3FBCULL, 0x5827618025B737C3ULL, 
            0xDDC15D385252D7FCULL, 0x2646755919E04683ULL, 0x4786543F091A9568ULL, 0x12C5A534958604DDULL, 
            0x0A765CE9950A1725ULL, 0xF84052893E5071E9ULL, 0x0911C1E733E53A62ULL, 0x8D94ABA4BAEBCDDBULL, 
            0x03F6AD1BD496143BULL, 0x58A488CA0B6A0455ULL, 0xA1D8EDB8C6CE375DULL, 0x93118666299AD934ULL, 
            0x07FAE3180CF2BF77ULL, 0x05F9F2420B81BDB2ULL, 0x1DC3DB01D7C944F1ULL, 0x66B81919553B6C49ULL, 
            0xB5C488C25A121B49ULL, 0x4E13FF73DBB20988ULL, 0x1AA9A5918E721499ULL, 0x61320DC53B0178AEULL, 
            0xF62B609796F37094ULL, 0x91FBF081933CE5D4ULL, 0x207D550413DF9DD6ULL, 0x4F1E2A24A7559B79ULL
        },
        {
            0x608B9641A26DA56DULL, 0xB21077A6E692F5FCULL, 0xD9081FDAA5DDBDC8ULL, 0xC73549803A8BE812ULL, 
            0xB6CD9E05DC7F9B5DULL, 0x711BBD5ABA229B9AULL, 0xF47F047984660418ULL, 0x5BC01FCCEB6A5370ULL, 
            0x780D417EF62BC51AULL, 0xF1FBBECFA17A51BAULL, 0x9196FCD8C450CCC0ULL, 0x41D00BD8949546DAULL, 
            0x7D595A6B64C5A411ULL, 0x7BF7095DBA5C2AA4ULL, 0x50E8DD60AFE80F27ULL, 0x7775C15519A330CBULL, 
            0xA18866BC9E72A1C9ULL, 0xDD3F81A8417506C0ULL, 0x64B72C7BB8FB80A4ULL, 0xF4978256A67187CBULL, 
            0x73B6ADE97B70F402ULL, 0x74FA0AF04D662AFFULL, 0x54DDBFFA33FCC936ULL, 0x3AE5BFD33C0DF01CULL, 
            0xEB0D5385E8FB589AULL, 0x22B533DF94E14084ULL, 0x0069441DF878465AULL, 0xFB2A89FA94C29209ULL, 
            0x3D4F8DF50A8D7AA6ULL, 0x55F0B6B506C37F0CULL, 0x781055DA9D2AFDFAULL, 0xDF98AE66D0FB60C4ULL
        },
        {
            0x5323B73A97B05680ULL, 0x0DB3CA519FBF9428ULL, 0x9303EF7166495556ULL, 0xCBCBA5BC19DD96CFULL, 
            0x76ABBA781E1CE7FFULL, 0x9B9292C0F17A56C4ULL, 0x972F16E5643330FAULL, 0x85C32B4A6C4C832EULL, 
            0x028997B5E05441A7ULL, 0xBC0E67ACA87C3269ULL, 0x1361B8C5E302F8F4ULL, 0xC3816CFEA05B509EULL, 
            0x281E6517038179ADULL, 0x37D9DE75CEC7BDB2ULL, 0x1981B4E4DEA68F4AULL, 0xA0D532BFB6A425CCULL, 
            0xFD8646C00979C741ULL, 0xCDFC897353D12236ULL, 0x05FC1843D4311EF9ULL, 0x8D6D8642B12EC6D3ULL, 
            0xFA9E09E7C3858214ULL, 0x4DA3860AED7CBC0DULL, 0x0F396D74778A570AULL, 0xF29D362A5D87757BULL, 
            0x3F2DD39575DFEC83ULL, 0x4E0D59B9E62D46F2ULL, 0x586E7661964909AAULL, 0xB70A66969E226BBEULL, 
            0x26CD899780B81B7EULL, 0x2E0D87888FEB2F62ULL, 0xCB6DAAA63BD52EEFULL, 0xFDD05E5432E9F23DULL
        },
        {
            0xAC4DCF3E59D9CBBEULL, 0xE7CB5C9E7573A617ULL, 0x4DD5E372A920903BULL, 0x03365B8CE0C14961ULL, 
            0x39D84ABDC8E29B31ULL, 0x7BA03F45E6B74F1EULL, 0xD3636B20168A586FULL, 0x289C0192185588D1ULL, 
            0x5628B37FF44109B6ULL, 0xA67F6B3EE7B91177ULL, 0xDC816C3F190860EDULL, 0x10EE379421296A88ULL, 
            0x323F9AB565F89BCAULL, 0x9DA01342F59C01BBULL, 0xC4A8B2C2504F099DULL, 0x223B42C00AE94538ULL, 
            0x97EC9067D052DBB0ULL, 0x2308C693E2481A83ULL, 0xF3484D2F72634D38ULL, 0x1A4F9763AF41D54AULL, 
            0xD451AB65EBA0594AULL, 0x6D1EF361CF66F020ULL, 0x35015EB3B4480A49ULL, 0xEEE25998F7FE0B40ULL, 
            0x332477AC34C83914ULL, 0x5C8AD2709214008FULL, 0xE544597578C253A4ULL, 0xB1F4FB76B4C7616FULL, 
            0xDCC20E43F9113A7CULL, 0xEAE9E9D56820401DULL, 0xF5F5BCD879054FF8ULL, 0xE07CE253B0A8262DULL
        },
        {
            0x30F0C84A5BBA3E40ULL, 0x6F34ED1FC704B02DULL, 0xF7701837B7BBBBEAULL, 0x0EA45CE32F5D12AAULL, 
            0x5CC910A4272B4AABULL, 0x058C8A5C6E1281E6ULL, 0xB78DB142EB222EB3ULL, 0xEA81C40B1C9DBF23ULL, 
            0x6A1448BF8E2E0F72ULL, 0x40AD75372EC66004ULL, 0xF8BA3C988EB4B67AULL, 0xDB84122293856F41ULL, 
            0x95D7A3A7B28C6D7CULL, 0xBD23668FD396A20FULL, 0xCD862356D697D21DULL, 0x31E2D174A93CFB34ULL, 
            0xBFE1CF0ADDE77C0BULL, 0x1C6DCBBACDD52030ULL, 0xD0E8EA688056CB6AULL, 0xD2AF6F4BBDEFA7FAULL, 
            0xDC7A93A95FEC68DEULL, 0xBF554D10EAF755EDULL, 0xF0F7AA9C95E924C1ULL, 0xBB10902F0DEBA5C2ULL, 
            0xF905A0E725D0B7BDULL, 0x8B6B951791FE4814ULL, 0xF6CD545BD7E40438ULL, 0xFC969E124642CF5FULL, 
            0xFFC1D195F98C73A1ULL, 0x96DBCCED5F6E59EAULL, 0xC319156BED724422ULL, 0x8732E099C6523481ULL
        }
    },
    {
        {
            0x75C20F0A7CA55882ULL, 0x6D3E9D64EFE0CD32ULL, 0x60D8E3ADE591649BULL, 0xC6E5463066546826ULL, 
            0x89086B7F31CD9DA2ULL, 0x8A36120A9FDA927AULL, 0xA69C53388B01ECB7ULL, 0x0C2AC8A36CD50A05ULL, 
            0x9D571DD12B07681BULL, 0xBE3344B64DA15F55ULL, 0xB400348818F8B4F3ULL, 0xAC601B82C457518BULL, 
            0x5A2CA1A227E16BD7ULL, 0xCE9D338F21024FCFULL, 0xC56B5CAF2B9CF73CULL, 0x7AB8DE1E35A125FDULL, 
            0x4C0133E61B1D809AULL, 0xC032C94B03A6D96EULL, 0x5BBA3042E0E56A57ULL, 0xE48EB205854BD8F1ULL, 
            0xFC14D92CB8979090ULL, 0x9727409BC2BDA61EULL, 0xEC440E29C98B1EB5ULL, 0xEE02A1FEBF41D63EULL, 
            0x682B93502D67673CULL, 0x5F274871FDAEDF4BULL, 0x597D3A16747CE676ULL, 0x4CBDB0BD0B747D7BULL, 
            0xA9677FB353D91255ULL, 0x30ACD18D9A1801F2ULL, 0x9EE3C872FAB8DF40ULL, 0x4880021DAB71B90FULL
        },
        {
            0xB42EC8C707F6C924ULL, 0x8288BCB30C0685C1ULL, 0xE5B9BF169204BF58ULL, 0xB4E0B57493A0DCE1ULL, 
            0x984C4CC3784D8EABULL, 0xF2F8D397BF129126ULL, 0xA72DF03D0E30CB0CULL, 0xCB578C6FBFF0B6F9ULL, 
            0xF5ACBE97E30E75F7ULL, 0x2ECC8C0A5D4AF72FULL, 0xFCEF5E34E411AF17ULL, 0xEC0CE98B49932C34ULL, 
            0x61A602851E0CF7EEULL, 0x5ED6A5C512A0C475ULL, 0x5EA479576926EEBBULL, 0x05008ADDE327D82CULL, 
            0x692853EA496F2BBDULL, 0x183380973BA1DCAFULL, 0x6F0C5065686C1B2CULL, 0x18814F0FBBD72C94ULL, 
            0xD836C096911DD00AULL, 0xB643D2941A8A027AULL, 0xEB95B9154DCB0BD4ULL, 0x9AB4D9E2CEDC05BFULL, 
            0xF2D990A88FD55B91ULL, 0x265B0C6842F4CB5EULL, 0xE45D697B469F3579ULL, 0xE2E85CC8B36D361EULL, 
            0x841107A0CBE6797AULL, 0xC89B413E73BF0647ULL, 0x6E8BC1B14128B4B8ULL, 0xE55CED068C9AFA14ULL
        },
        {
            0x54A1A86546FF0F9DULL, 0xEC5045504310B052ULL, 0x14C6EFAFF7B98F70ULL, 0xE4D1704167264F9AULL, 
            0xCE69A6EC8E1A32CEULL, 0xEBB71B22A6847020ULL, 0x65018C33A3ADCF87ULL, 0xAEE38BF843071643ULL, 
            0x05B83BD0D0C53F76ULL, 0xD417E8D3A63754AFULL, 0x550307B78563F9B8ULL, 0xD3429662725FDDD5ULL, 
            0xE095FAC3647DC75BULL, 0x926D4D9529946D60ULL, 0x07D3A735BB93B845ULL, 0xCE4AE2941A23CA43ULL, 
            0x7DFDD75987A18C02ULL, 0xD06CFFAA6E92A9B8ULL, 0x12ECC6818F2FF04BULL, 0xAADC1FE07B155552ULL, 
            0x1B30DE5F4CB8D9B8ULL, 0x20F0DBF5AA3697F1ULL, 0xED3A8FC3A7ADA6B1ULL, 0x93126910415495FDULL, 
            0xDF8AD046B488A11CULL, 0x631EA52F704AA9ADULL, 0xDCB187EB3E2E4116ULL, 0x231063F152A8BCD2ULL, 
            0x8974821ACBB12555ULL, 0xA8CE4E4388A4F46AULL, 0x56C7D51E5EE7481BULL, 0x8BCEC15B70B9499FULL
        },
        {
            0x699527B04BA382AAULL, 0xC5F48B9799228C2CULL, 0x9CCBC3F29D830DA7ULL, 0x74ED043AD156B630ULL, 
            0x711042CB0B90D549ULL, 0xB1CFC6039297CCE4ULL, 0x7C81ACB03319413DULL, 0xD8C3779117749831ULL, 
            0x0C637224CB2A4E68ULL, 0x614D1BAC1AEAC19CULL, 0x6C8293052994998AULL, 0x334BD698F2328F87ULL, 
            0x6BE3599FD4EA4B80ULL, 0x92D6ECB35A221063ULL, 0xB466755761DA2962ULL, 0x960DA8635AB5A491ULL, 
            0x12FCE73CFFFC2122ULL, 0xB2CA084537A3C5F4ULL, 0x8ED072E2BA697EB2ULL, 0x7289A9D60ECEEB30ULL, 
            0xC8C7567A3F70AF57ULL, 0x04727EA31F630657ULL, 0xF50C4E7A402848FDULL, 0x6677A35A3B000253ULL, 
            0x2EB7311CE80565AFULL, 0x11180AC3AC059E18ULL, 0x78DA1B6B8EBC54A8ULL, 0x1D9213A820265082ULL, 
            0x7C5483419E42694DULL, 0x25C4A7213E2E30EDULL, 0xC9DCC1C80DB649CEULL, 0x2A6C78C09100D756ULL
        },
        {
            0x4A341D67DAF84782ULL, 0x25C085D41B4DC919ULL, 0xA9CAF8046082D211ULL, 0x13082349E64A83B0ULL, 
            0xA3A8DAB460E38B69ULL, 0xB0167C78F0911956ULL, 0x64B2092660C3550DULL, 0x2808AE7A44EE8E5FULL, 
            0xA94A18D57F96FE52ULL, 0x8E9F2AC61BE341DEULL, 0x3F24F2364BEB4C54ULL, 0x463088AA2D61065EULL, 
            0xF212983E7C55249AULL, 0x6307599B947F8493ULL, 0x83BE6ECEBBBDFCDAULL, 0xF97683385A4393F8ULL, 
            0xDF33A15A3CB51F8FULL, 0x901845A2CCD4CB68ULL, 0x8568B1D9531BA417ULL, 0xE97975573C864D34ULL, 
            0x1A4B4904208A14C4ULL, 0x799C4586D75FD6D4ULL, 0x8A19FC12464396DFULL, 0x4991564C62443349ULL, 
            0x081F636BBB81DE6FULL, 0x6C966C7CFC8F3B82ULL, 0xB378655BDC9BA14CULL, 0x8A73401BB8593197ULL, 
            0xE41312E216B964EBULL, 0x169659F759307110ULL, 0xD6613D2F21C3AA44ULL, 0x9988079DEEB27333ULL
        },
        {
            0x166F4974E404FB57ULL, 0xC67BCC7EFAE0E561ULL, 0xE80958B73DD9DE46ULL, 0x30F253C17E4E6A7DULL, 
            0xB9A692332D5B75B9ULL, 0x46442C825F8A7465ULL, 0xAAD95E2319EE3D94ULL, 0x6A849F02B30CB178ULL, 
            0x55EED60B7C68CCD5ULL, 0x3F25C4F55E13A89EULL, 0xA51FC6E8B8D08DA8ULL, 0x39FF5CF2A6C6EAF9ULL, 
            0x0AF0542C99DA63AFULL, 0x08DBD3F5483B3182ULL, 0x243E9EC329FAA504ULL, 0xBE5D13B340ECF451ULL, 
            0x992C9DECA90BF1FCULL, 0x8A14F6B0A7B3EACCULL, 0x1A0FF46524A1BEF2ULL, 0x0FD22E03E79D62B7ULL, 
            0xC43986053EF1A781ULL, 0x8730073949BC8691ULL, 0xDC31ACBB0849633EULL, 0x851AA4F03D530D68ULL, 
            0x828E66D1EC156EF3ULL, 0x20BE3ED8CF8C8499ULL, 0xF080D1352F55B974ULL, 0xBCA10AB7A8D6161AULL, 
            0x0A6AC2211C381A08ULL, 0x5F6CB1F476025AC7ULL, 0x1E500DFF8FE47AF2ULL, 0x8530AA69FB61B93FULL
        }
    },
    {
        {
            0x4A8C37725B5AA6A5ULL, 0x7555EF3DA3ACFA40ULL, 0x7190C4584F8561B9ULL, 0xE828961E4451B16EULL, 
            0xD1A108F282278DF1ULL, 0xD3E464825101D4ADULL, 0xBB35C32B466CFD9FULL, 0x1152D1B4E8A780BBULL, 
            0xDAB81E1E648415E2ULL, 0x3A358A367AD38BBCULL, 0x01CF52D16D35AC66ULL, 0x91456113FE4E929FULL, 
            0x18AA691BF2F18F55ULL, 0xD2B4F2D082220C70ULL, 0x2084BB946DA68A12ULL, 0x3150523F357ACB3AULL, 
            0xDF67B25C63D22862ULL, 0x30048853B9FE92A7ULL, 0xFBF5D0FE90F29045ULL, 0x0461FEB44FCD35D2ULL, 
            0xF73D5D1566958930ULL, 0x8A5420A8051080A8ULL, 0x3B38C7D7A5A0BE84ULL, 0x9DFA05223ACDF320ULL, 
            0x547F7DA78B975A34ULL, 0x73AC63EE5563B9FEULL, 0x3F620D8283D6BACEULL, 0xDA370CECDC4D7353ULL, 
            0x0773F66480912D9EULL, 0x3EA0EDF692982B02ULL, 0xCFDA8AC9E148DC0EULL, 0xDA4965A70F1D751CULL
        },
        {
            0x6F6CAEBA2CB7C3F4ULL, 0xB508A397F0219CF8ULL, 0xA994E7043B91595AULL, 0xB0DE6873E5B91D34ULL, 
            0xC8FA6DF24D0DA796ULL, 0x75395E1148422B1BULL, 0xFFBA6BA642F6AC09ULL, 0xEEDA38119DEF5EE4ULL, 
            0xDB90259264A93CD6ULL, 0xE89C00A02BBD9AD0ULL, 0x19303D1211F1CD00ULL, 0x4F199C736354D5F5ULL, 
            0x8CD089C0C764AA17ULL, 0x452142F2A60FCC53ULL, 0x678E0195CDCA3A58ULL, 0xD11E092B17F8596CULL, 
            0x7C88588ABB94078DULL, 0x0E115FC4B9795591ULL, 0x14AA46B1868B53F5ULL, 0xABCF81734B6D0807ULL, 
            0xAA75B0C5FFC98702ULL, 0x88C872AE1FBEF93EULL, 0x7DD2194DA30A52FEULL, 0x64B6A80650313EF4ULL, 
            0x2B47AF10A2B1B7D0ULL, 0x3C1F9EA3D80A1747ULL, 0x7C1305B2C8250D57ULL, 0x6147E22B46A9008AULL, 
            0x075B866E9AB0D949ULL, 0x51CAEA897AAB6C55ULL, 0xC514E3E1F1B23B8BULL, 0x5C001C991A8EA18CULL
        },
        {
            0x628D516B968BB2F2ULL, 0x5ABF44E90E654B4AULL, 0x7F44BB18F2C81CBEULL, 0xA1650C9D263AB045ULL, 
            0xD38EF89724F6598CULL, 0x83EBBA324AB89ECFULL, 0x7A9D0FCE6B3783A0ULL, 0xBE9C995696094F4CULL, 
            0x6E6513F90F9CC228ULL, 0x93994BC66F2DFF36ULL, 0x50001ABE76F3B934ULL, 0x00B25A61B315305BULL, 
            0xB34C9142EA0B03A3ULL, 0x0008CE52A50FDB76ULL, 0xA07F9F167AC86791ULL, 0x25010719D50B5E41ULL, 
            0x77882A5942CBE065ULL, 0xAC9BDE8C1EBA4629ULL, 0x27E0A7A8C1B7D4E3ULL, 0xDF20327E0B0F0774ULL, 
            0xDA2C324103834A6EULL, 0x6B1DCE082B424752ULL, 0x87191168D2D82400ULL, 0x2DEC8964BAD8909CULL, 
            0x9D07EBB71414CCCEULL, 0x9CDB507F591CCBA1ULL, 0x4829B9FF5E14A490ULL, 0x9278B10F1F16F48DULL, 
            0xB0EA79E51D0A7AA2ULL, 0x7902A14B327FBA71ULL, 0x871CDE21D3B8B413ULL, 0xC21BB160205A9BF4ULL
        },
        {
            0x57070F0D8006F8DFULL, 0x27F3E6961BFA546CULL, 0x7CC588521AF2E48CULL, 0xADB4AF69CFB010E0ULL, 
            0xCB1B67CE9EA0B396ULL, 0xCD0D0D4AA66D03FEULL, 0x612930C104FB2C55ULL, 0x7B58B1439210FB5BULL, 
            0x7D3F50128AE1E313ULL, 0x9395BCAB44F2A4B6ULL, 0x5AEB93B630C7A1C4ULL, 0xDA179D0EE260415CULL, 
            0xA21CA8F8B284806FULL, 0x292B99F0E312C8F4ULL, 0x6251C86C032FD409ULL, 0x8ED8E76E36110C9BULL, 
            0x3AE613E214F7FA57ULL, 0x70F65A054FB333C5ULL, 0x3DF39DCE00CD37FBULL, 0xD90866C8C6071696ULL, 
            0xC5B7AD09FCCD4AECULL, 0xF14724EB63FD1F82ULL, 0xE63A04A34EB30FFBULL, 0x29665E2AA000022CULL, 
            0xE5D895D18396343BULL, 0xDF37D58C6A2F55B9ULL, 0x2DD4208F868A7CD6ULL, 0x8526F17ABF0A510FULL, 
            0x5C7508BE2D3044ECULL, 0x18A69D236087EF76ULL, 0x0888466AA74EACABULL, 0x0924AD9A9EB7BDD9ULL
        },
        {
            0x1EBBA6205BFAA7FCULL, 0x56CF4DB7465EADBFULL, 0x9CB9A46E19E334AAULL, 0xB839C4A170E28370ULL, 
            0x1E2B3BACCF0ED70FULL, 0xBE23D542F3E767D2ULL, 0x8689F0BD10AABDBBULL, 0x7818158C94F3CA0AULL, 
            0x925638D7B80EFEC4ULL, 0xFBDB5699514D9A2FULL, 0x7C5D1FEEEC1A8BF0ULL, 0xB4BF9F783B53B141ULL, 
            0xE3F03478BD1F7538ULL, 0x74CDB4A17720B903ULL, 0xE6D6F6BDB600FB23ULL, 0x5B13490545B7B4FDULL, 
            0x836DEAA8C24D1E43ULL, 0x863D51BFCF8E8F32ULL, 0x5D5AF28D2A8B8917ULL, 0x1AE92CB34F0F4C07ULL, 
            0x8987B278289A7FD4ULL, 0x847C225B1E972DDAULL, 0x5C8D44D1E5157C8CULL, 0x24A661FAF4DD17C0ULL, 
            0xC09B7F10CC2C32A2ULL, 0xCC31506A5ECD009CULL, 0xF6F70B34D6B7F744ULL, 0x027DC6AD449217B4ULL, 
            0x0D2E0185F155B7F8ULL, 0xEE33279094174166ULL, 0x8451FAD5678FEC4BULL, 0x3D51B1CAA0C929C5ULL
        },
        {
            0x4E27EDB3ADD647A6ULL, 0x89BB61EBD22970D4ULL, 0x68890C3B0EFF2DC5ULL, 0xB85DC44274E4B6D2ULL, 
            0xFA98A77A2AA10BAAULL, 0xCA046D604E8F0633ULL, 0xDC006788730ED314ULL, 0x219B08DCE8A2D929ULL, 
            0x8A4FB57062694208ULL, 0xC2F2265CC8D10187ULL, 0x80CA3F637B28AF36ULL, 0x20B06250C6DD95FEULL, 
            0x87F160471E85E888ULL, 0x18A925FC619C09CBULL, 0x250BD2E56A302F4CULL, 0xEBAC80AEA70B9013ULL, 
            0x28D53634DD4F3135ULL, 0x4E5D198D39037E45ULL, 0x504614403C27CB1FULL, 0xC1193A2D1E2E0223ULL, 
            0x3FF4CA01402C17FEULL, 0xD9A6D28128859151ULL, 0xC79488B7D112850EULL, 0xB65B5EE5B7A5AF9EULL, 
            0x130C1F8DF40BB362ULL, 0x8890606C1ACF509EULL, 0x4E4C7BE1C1ECC6ABULL, 0xB41266C731419610ULL, 
            0xF9E3B4E49772BFE5ULL, 0x709FF03E992BB928ULL, 0x083252BEE9831C42ULL, 0x17CD168A5E5743A1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mirfak::kPhaseHConstants = {
    0x7CFE69FBD1605CACULL,
    0x49D68A448432174FULL,
    0xD0E5189161D96580ULL,
    0x7CFE69FBD1605CACULL,
    0x49D68A448432174FULL,
    0xD0E5189161D96580ULL,
    0x6A617DCB11CA52D2ULL,
    0xB32AD6501241BAB9ULL,
    0x90,
    0x3E,
    0x8C,
    0x1A,
    0x34,
    0xEF,
    0xEF,
    0x0C
};

