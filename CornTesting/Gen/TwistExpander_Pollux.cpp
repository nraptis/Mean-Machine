#include "TwistExpander_Pollux.hpp"
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

TwistExpander_Pollux::TwistExpander_Pollux()
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

void TwistExpander_Pollux::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB785A88226628F42ULL; std::uint64_t aIngress = 0xE36666EE167CAD15ULL; std::uint64_t aCarry = 0x9D80C22CCEF9B534ULL;

    std::uint64_t aWandererA = 0xC0FAFD1AC72DC33DULL; std::uint64_t aWandererB = 0xDDAA646140CEFEA8ULL; std::uint64_t aWandererC = 0xC77438DB7A77A5E0ULL; std::uint64_t aWandererD = 0xF79AC165BEBB3DB8ULL;
    std::uint64_t aWandererE = 0xDBA44608037C35D6ULL; std::uint64_t aWandererF = 0xF4B6CBE7E8237416ULL; std::uint64_t aWandererG = 0xE0EA0D864C0D8511ULL; std::uint64_t aWandererH = 0xE66CA73EED3AB51AULL;
    std::uint64_t aWandererI = 0xFE6737D46FC60991ULL; std::uint64_t aWandererJ = 0xC09625D3DDDF1CF1ULL; std::uint64_t aWandererK = 0xE1C64B5C45FC87EDULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16040257315580678543U;
        aCarry = 10317320086932476010U;
        aWandererA = 12821135325594604128U;
        aWandererB = 16105202773605590304U;
        aWandererC = 10743735251659461026U;
        aWandererD = 15690671194894996197U;
        aWandererE = 13679654581270837704U;
        aWandererF = 11583294190530237618U;
        aWandererG = 14604682191060982271U;
        aWandererH = 14392789914514733223U;
        aWandererI = 10135680658894670449U;
        aWandererJ = 16467480359780373159U;
        aWandererK = 16298080545337407061U;
    TwistExpander_Pollux_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Pollux::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEEAC63FA88FEC642ULL; std::uint64_t aIngress = 0xF2A3BF486C8DF635ULL; std::uint64_t aCarry = 0xD2DF9ED8AD3CB96EULL;

    std::uint64_t aWandererA = 0xBA2D004D6DF1A703ULL; std::uint64_t aWandererB = 0xA69E3CF358DC7625ULL; std::uint64_t aWandererC = 0xCA4D2B174F1B9152ULL; std::uint64_t aWandererD = 0xE99A430E3DF9AACBULL;
    std::uint64_t aWandererE = 0xF9F9C2112E768E59ULL; std::uint64_t aWandererF = 0xE8FCE4A55B229C0AULL; std::uint64_t aWandererG = 0x86EA767EE525016FULL; std::uint64_t aWandererH = 0xF46526DEBA9E3998ULL;
    std::uint64_t aWandererI = 0xBCBBE283B43E7132ULL; std::uint64_t aWandererJ = 0xFCD7410D2B8DFCECULL; std::uint64_t aWandererK = 0x857F23D5242B60C3ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13907644813611478681U;
        aCarry = 18081900321422664604U;
        aWandererA = 13652320207771946925U;
        aWandererB = 13547341895320443631U;
        aWandererC = 12236722327868738328U;
        aWandererD = 12903580419623721233U;
        aWandererE = 15249198656536546258U;
        aWandererF = 13758582999156998235U;
        aWandererG = 15401627396592342317U;
        aWandererH = 16008668179735661435U;
        aWandererI = 16859074349796323947U;
        aWandererJ = 14984937453588126297U;
        aWandererK = 11400017290115697833U;
    TwistExpander_Pollux_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Pollux_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Pollux::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x924B4CB34CBD7F5AULL;
    std::uint64_t aIngress = 0xEB1F0D9896B88E5AULL;
    std::uint64_t aCarry = 0xB230B803DD33D5F6ULL;

    std::uint64_t aWandererA = 0xA8AB094136490BA3ULL;
    std::uint64_t aWandererB = 0x80E8779DDC300F74ULL;
    std::uint64_t aWandererC = 0xF32EF094C15E58F6ULL;
    std::uint64_t aWandererD = 0xDBD54210C2248837ULL;
    std::uint64_t aWandererE = 0xE0F56DE601BA75A5ULL;
    std::uint64_t aWandererF = 0xAA8CC4245AEC8ACEULL;
    std::uint64_t aWandererG = 0xD46A6AC68789FBF8ULL;
    std::uint64_t aWandererH = 0xB282A697C4FDC035ULL;
    std::uint64_t aWandererI = 0xCA599134B2AE84F2ULL;
    std::uint64_t aWandererJ = 0xBDFFE6FD657BB4D4ULL;
    std::uint64_t aWandererK = 0xB9175FF96EAF3CAAULL;

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
    TwistExpander_Pollux_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Pollux_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Pollux_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Pollux_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 25 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 43600
void TwistExpander_Pollux::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1350U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1160U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 818U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1402U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 638U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 220U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1918U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1634U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 353U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 465U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1851U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1661U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 919U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2043U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1921U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1401U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2004U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2002U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1074U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1032U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 84U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1965U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1110U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1223U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1477U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1546U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1608U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 974U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 142U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1815U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1330U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 448U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 522U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1705U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 216U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 498U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1678U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 531U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 841U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 430U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1776U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 106U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 422U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 314U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2033U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1760U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 880U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 459U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1525U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 932U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1308U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1994U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 307U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 409U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1777U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1593U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1906U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1513U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1860U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1363U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 126U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1369U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1329U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1589U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1392U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1257U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1111U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1558U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 56U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 143U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1342U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 631U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 612U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 262U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1028U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1426U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1202U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1644U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 539U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 204U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 920U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 178U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 69U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1475U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 481U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1394U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1648U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 441U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1795U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 927U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 338U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1789U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 467U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1125U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 402U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1154U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1838U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 18U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1850U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 910U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1012U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 302U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 212U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1341U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 179U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1638U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 672U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1943U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1382U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1218U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 233U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 187U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 16U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 715U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 80U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1238U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1255U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 989U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1079U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 916U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Pollux::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x90ACE8C504811E2BULL; std::uint64_t aIngress = 0xA7AF11D76019D0C4ULL; std::uint64_t aCarry = 0xD19B42E717732B80ULL;

    std::uint64_t aWandererA = 0x9A4DE869E3139DE8ULL; std::uint64_t aWandererB = 0xF2426437EFBF79ACULL; std::uint64_t aWandererC = 0xB4961D438CB85350ULL; std::uint64_t aWandererD = 0xE53B26A56A67707AULL;
    std::uint64_t aWandererE = 0xD4D8D62AAC4BC673ULL; std::uint64_t aWandererF = 0xE91E9F88F5F5202EULL; std::uint64_t aWandererG = 0xE5099DE124DCB8FCULL; std::uint64_t aWandererH = 0xDA411AA422DF4026ULL;
    std::uint64_t aWandererI = 0xA8A350F35184EABDULL; std::uint64_t aWandererJ = 0xCBA088259D8E3A07ULL; std::uint64_t aWandererK = 0xEEDF3E6C1EF3E34DULL;

    // [seed]
        aPrevious = 15387417194781725732U;
        aCarry = 10465139239389118860U;
        aWandererA = 14503252997898204313U;
        aWandererB = 10997479359594774125U;
        aWandererC = 14404887978832241823U;
        aWandererD = 12741413306584168662U;
        aWandererE = 13565819464228555689U;
        aWandererF = 13490337937780724087U;
        aWandererG = 10494398526087565728U;
        aWandererH = 13344044399999453521U;
        aWandererI = 18040044671981140640U;
        aWandererJ = 11790386888003379611U;
        aWandererK = 12558768415608188510U;
    TwistExpander_Pollux_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Pollux_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Pollux_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Pollux_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Pollux_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 25 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13011; nearest pair: 492 / 674
void TwistExpander_Pollux::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5659U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5986U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1041U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7139U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 108U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7544U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1333U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5795U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4231U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6522U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6590U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1490U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6492U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3712U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7420U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1088U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 874U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1588U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1054U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 278U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1472U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 878U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1177U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2038U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1183U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 60U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1490U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 355U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1949U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 259U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1818U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1294U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1772U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1648U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 25 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13023; nearest pair: 484 / 674
void TwistExpander_Pollux::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1410U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1227U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2668U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5970U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1534U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7969U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4985U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5489U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3577U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4088U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1307U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6338U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5500U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6229U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7096U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1136U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 660U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 978U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1237U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1187U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 492U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1077U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 926U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1380U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1620U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1386U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1078U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1567U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1719U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 725U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1665U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1659U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1784U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1220U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 2037U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseASalts = {
    {
        {
            0xC595D055997CDF84ULL, 0xF4A23706CB7A50A7ULL, 0x0AD2AD23783C2020ULL, 0x90285F1C10E43FDDULL, 
            0xCD05EF78CCA37E93ULL, 0x11E458E7AC17B8BAULL, 0x5A7E9020319DEAC9ULL, 0x58193EE6C42F4A87ULL, 
            0xB6E9CC0CEA3CDA8CULL, 0x12043CE7D7FB0782ULL, 0x34586DA2109F1816ULL, 0x340595D837B9F5F8ULL, 
            0x63207D52C6FC7DF7ULL, 0x0714ECD07B7B960FULL, 0x7F5A384BAA7B8CA0ULL, 0x127043E8393C9ADFULL, 
            0x53FBF19907408EE4ULL, 0xBCF14F8350143528ULL, 0x047FB21234FD8E01ULL, 0x0266021090A94CB3ULL, 
            0xADFA2F6238B3A81FULL, 0xE2511657FF320B9AULL, 0xA1EA176D273BE501ULL, 0x6707ABF2D0D67A8CULL, 
            0x1E7223B10BCE3CF7ULL, 0x1639B79ECA41A973ULL, 0x688CFCD19B7B9A05ULL, 0xE937F1EBAF510198ULL, 
            0x8CF7A7A762DBDAC9ULL, 0x403447F53282C65EULL, 0x3A57F4277B50F923ULL, 0x2F4FB14FE5E82837ULL
        },
        {
            0xD551BD978EE133EAULL, 0x2DE3736DB38C3B46ULL, 0x432FC6CA576E64EDULL, 0x5B296FD1B2734176ULL, 
            0x484ECB2CF0922314ULL, 0xEE4DABDA2AE6E12DULL, 0x0D9B94297F5D22D4ULL, 0x055DD925DC433943ULL, 
            0x32C7FB7B318A3B9CULL, 0x6C30321DBD064CD1ULL, 0xE5D358C47D591871ULL, 0xB5B052D3A5DCDFE7ULL, 
            0x7017C3F1E7574456ULL, 0xC8357E7D81F700CFULL, 0x22B987F9D4E3160AULL, 0xBAA68248F05B380BULL, 
            0xA9C1DF360F9F04CFULL, 0x84A7DFA0F1F89E8CULL, 0xB95F596516CA878BULL, 0x4701D2CE594CD3F8ULL, 
            0x0B2F91F697A1C8A0ULL, 0x33F7401E1350C45EULL, 0x8A91DF2C70894605ULL, 0x40B17AAC71683DCFULL, 
            0x63C908E7E1EEEABDULL, 0x1B179F17217BE194ULL, 0xA05B0A957436F8ABULL, 0x24E540C68881F6D9ULL, 
            0xAD2E7DB7A8AD345DULL, 0x4C3041F2F04FF04DULL, 0xDC4189A5C251C1A7ULL, 0xA229B218FAD016E5ULL
        },
        {
            0x12B5080F5FE2C2F8ULL, 0x08F6C7934077052BULL, 0x00948AE103A4C654ULL, 0xEF8385B155C77972ULL, 
            0x562B21E702A4207EULL, 0x9C27B84C46EDFFD8ULL, 0xF0D1175ACA381F7EULL, 0x9C071AB083AFB29DULL, 
            0x2CA8B545C8518DEAULL, 0xFB4973948861CBFAULL, 0x9272A0CB55EB695EULL, 0x412B53EFC583DDBEULL, 
            0x62FFA5CFB4EF0CBEULL, 0x1FB7665DEDFC7C63ULL, 0x7C58D4C9C736A868ULL, 0x1B86905929163654ULL, 
            0xAF70BCF16A607D9FULL, 0x4E22E25BBAB2263AULL, 0x979162104B5F7F8DULL, 0x7E3787A1EE15D20CULL, 
            0xFC558A45F96F6670ULL, 0xF31B2BCED00E0ABFULL, 0xD2A3DFC2020E1274ULL, 0x772BC396DCF4BEF9ULL, 
            0xA7CFDC5B8CFAD846ULL, 0x5C9A2643F4F1BA68ULL, 0x7542F2FBEE97D167ULL, 0x2B96E4B53923AF44ULL, 
            0x8EE4509441B3551EULL, 0x850D3DFFB99A6EAFULL, 0x0EA2E34F11AA3105ULL, 0xC93F676C5A9F2F77ULL
        },
        {
            0x1FEE8A4F2F26EE8AULL, 0x7C7651A5184C4984ULL, 0xD7388DB37B235C33ULL, 0xF5867EA23F4093FBULL, 
            0x24A9F42DEFA54671ULL, 0xD0A016B29E630C22ULL, 0x315F877D774E5CE7ULL, 0x9F29DFA2510FBD99ULL, 
            0xAD11136AE0B64691ULL, 0xA472BA33C9B893C9ULL, 0xC26DB2584E807A4FULL, 0x36F00FB702C78451ULL, 
            0x3E730FC1143FC507ULL, 0xC98F4EF85ABEDC94ULL, 0xA7BDFF34587FCE63ULL, 0x69D41B14D8916B54ULL, 
            0x5167A00B02ADC3F3ULL, 0xD23928AF901ADE86ULL, 0xEF14E4B60C2F4AC0ULL, 0x466125734704000FULL, 
            0x9C0A4A5ABCFE57E5ULL, 0x58402CD8833F125AULL, 0xE45F09D68CDB2078ULL, 0xCDDDB38CC90DA030ULL, 
            0x379B7EA91C15B09CULL, 0x64D8A154E9359401ULL, 0x0DC82809B4FACF8CULL, 0x2832CF176AA9C573ULL, 
            0xE63484C3C37597DFULL, 0xA9CB25CAC1EEB0E4ULL, 0xF8F1B1A0DF4895B7ULL, 0x829D948F5DECB1A1ULL
        },
        {
            0x1B0DCAD2E334C6A7ULL, 0xEBE70544390A3BF1ULL, 0x207282A5742D182CULL, 0xC1ECF5CB544324C1ULL, 
            0x8A2F84D44CCF6920ULL, 0x605D0D53BB4F5E4DULL, 0x8E29B6E0BC94B410ULL, 0x207710DA21CC90C3ULL, 
            0xC520947173ED949FULL, 0xA98B929BA239728FULL, 0x828D59B780EA3B24ULL, 0x206253BA4F33E263ULL, 
            0x80629560D8BE0BF6ULL, 0x2367A0C7452200ECULL, 0x61AACCD3797ED72BULL, 0x742588A3347AD680ULL, 
            0x34EA7F8E393B5F09ULL, 0x9196C3F124DB50B9ULL, 0xFD0C3BEAB57BEFA5ULL, 0xA92B070893725807ULL, 
            0x34F00D07965F7AA5ULL, 0xE9FF0052F34E7102ULL, 0x65C1E47A4EA12365ULL, 0x7BF8495D23152F86ULL, 
            0xBE0117F0E85BE6B8ULL, 0x6669CC16C91BA8D5ULL, 0xA934F149F2DCA2F4ULL, 0xB76173C42CA7C06BULL, 
            0xA53F9CF6A90A4213ULL, 0x6B1F870988A5E31FULL, 0xCB86BD159467B058ULL, 0x0D3F7580F9BCB371ULL
        },
        {
            0xE47258EE63C5AF34ULL, 0x88859CB782E9B0CDULL, 0x92413C41DAF61147ULL, 0x624DEE1CD8D54DA5ULL, 
            0x8F57B83BDD1AF545ULL, 0x1D8B2B17D2A7001AULL, 0xDA39286A65A81352ULL, 0xF243E7324B300B89ULL, 
            0x72DBAF519F0A0035ULL, 0x63611561FFB08A0BULL, 0x983987968BB50DC4ULL, 0xC35FD27167396E37ULL, 
            0xE890D8108F75ACA3ULL, 0xB282A672A30E060FULL, 0xDA172DE2B66E7BA4ULL, 0x8318947A5185459DULL, 
            0x7F259E28558DC496ULL, 0xA51E26E466581065ULL, 0x938D0F4C8A44AA59ULL, 0x73F02F4624ACFE07ULL, 
            0x3B399042C1B40880ULL, 0x13362539EF7DEC39ULL, 0xA43EEEF55BBD1366ULL, 0x1A559B3C05320AA6ULL, 
            0x9D0659F7F7E1B736ULL, 0xAEA4DA2D25049CA9ULL, 0x4CB16C5E9E578F00ULL, 0xD4BBD6808D43888EULL, 
            0x8496961252481493ULL, 0xF4A20643F57E541CULL, 0x8ABB54D3C7FEF561ULL, 0x737125D015CC449FULL
        }
    },
    {
        {
            0x32A36F8555823FF4ULL, 0xFCB76C5C747FF59EULL, 0x960319CE9F9952F4ULL, 0x0D6941A6437EA0CBULL, 
            0x731FD950A5A39E2DULL, 0x2329FB604D284E77ULL, 0x86D45F46E12F5098ULL, 0xB5758EB7C0D22127ULL, 
            0x42AE43AF8D3AA99CULL, 0x27591B695CEA6A10ULL, 0x044AB74AB9EE742EULL, 0x8871D990AE6C5F06ULL, 
            0xEAC342BF248151DDULL, 0xB9C2F01AEE890BF8ULL, 0xD276F20EC891C776ULL, 0x1B018EDB1A8AFD8CULL, 
            0x66E0A32922275536ULL, 0xA4B761494FC950C0ULL, 0xEB20C20FD0A6D40AULL, 0x265AD8CEC5A3A4BDULL, 
            0xE0532EAF9E9665D1ULL, 0x8AA02CD3F5278935ULL, 0x87587980C342B3BFULL, 0x10DA847F40BF5C87ULL, 
            0x4DE546D89E178AE6ULL, 0x7229126D39734E38ULL, 0xE137376BDCDD8506ULL, 0xEB26D28623C84CDEULL, 
            0x4724F91CFED0798AULL, 0x6F6DB1E4903B7DB6ULL, 0x594DA7D054936764ULL, 0x14CD92C53B11189AULL
        },
        {
            0xE9CE427BC3896D5AULL, 0xAACE3DED086AFDD6ULL, 0xB45491791777CD72ULL, 0x6A08628E063CBA04ULL, 
            0x2A06988B45A3742CULL, 0xD2A759B1385C8BF4ULL, 0xB054B4055D4223B2ULL, 0x37EAF984A2723A38ULL, 
            0xE1DD08D5F171244BULL, 0xAC78C79FDC857E0CULL, 0xE94125346FEAC3C2ULL, 0x047DF6773BA2FCB1ULL, 
            0x0B679A307525A9F1ULL, 0xE62AF88203BDD1CCULL, 0x45CBEB7B6D878D86ULL, 0x636641B963028D44ULL, 
            0xA7E17224942F17E7ULL, 0xAB0169EC9277C38CULL, 0x49EAC9B18BCE01C3ULL, 0x9EAA446D5EEE2A39ULL, 
            0x16F97002EF887770ULL, 0xA42A64AB5EBC0C5CULL, 0x9AE6183EFB9BA8BAULL, 0x46B1C934B6966832ULL, 
            0x33D52FB72CDEA599ULL, 0x70E1961542CB16DBULL, 0x6CFB1DA90CDE45D7ULL, 0xE4225AB1FB1588A7ULL, 
            0xF4E873435E10280DULL, 0x631F15E92A99C059ULL, 0xE104CF305223078AULL, 0x464B577921757430ULL
        },
        {
            0x2ED91419516258DCULL, 0xF6189205ED9B8D13ULL, 0xA68F3AE48FBA87B4ULL, 0x3C4CB854E95DC668ULL, 
            0x1784E927ED88FFA6ULL, 0x3D358F8C87EE35E2ULL, 0x7B32BC073087B6CDULL, 0xD6E90EBCED428F8FULL, 
            0x657BB3BEAE03B8E2ULL, 0x12F6AE820545586AULL, 0x246F22AEE4537F1BULL, 0x6980F4303E263B43ULL, 
            0xE64C18EEBB9334D0ULL, 0x5AD935F6D5D2683AULL, 0x4BFB9440597F7074ULL, 0x883F9102904D2C90ULL, 
            0xB75029A3AF1ABCDBULL, 0x17F07C675078859CULL, 0x3E1C9B9FCB689F1DULL, 0xDDACBB10D9D3D2CBULL, 
            0x142E37D9CF65F0FAULL, 0xE96959DA4AA21BBCULL, 0x26244148D2978821ULL, 0x33B0330576E83EFDULL, 
            0xBCE61A8562AE2A0CULL, 0x3A58481DD6F56255ULL, 0xF41831673EF585FAULL, 0x90C6552527E67630ULL, 
            0xA2AC711EB6EB0934ULL, 0x808FD84D3530F901ULL, 0xCB1FB5EB04C2011CULL, 0xC42022BDB31FA930ULL
        },
        {
            0x45F4868D632338E1ULL, 0xE9427D19E1E1C2B6ULL, 0x89404A9DF5C093C3ULL, 0x6F86C5E460B9751DULL, 
            0x9EA64A88A628B838ULL, 0xCCDF4DB9153A456BULL, 0xD43CC88986A6C7B4ULL, 0x2E381BB57C9930EFULL, 
            0x897B8B76EBACEAF6ULL, 0x3393710514B76B1BULL, 0x85F5CF275ECDF22AULL, 0xD532E4288ED357B3ULL, 
            0xF4E8F7FBF1FB279BULL, 0x36579C71E4D2DD5BULL, 0x6A2119B3A19109E8ULL, 0x36CC106C9D172708ULL, 
            0xF00CCA34DA0CD542ULL, 0xE9D5A4978BA5DA21ULL, 0xD5D6F15012A6D993ULL, 0x584228EFB1AFFD73ULL, 
            0x440F3855E1B3BAD2ULL, 0x0E5CC5F38DE63D82ULL, 0xD578B4EEA681BEF7ULL, 0x4719E9CB7EEF3F79ULL, 
            0x9446007046FB1A8AULL, 0x193EEFECC28BAC35ULL, 0x43B6C72E8B11FA09ULL, 0x1FACF15FF68979AAULL, 
            0xB3C89AD395087F92ULL, 0x220D8D40E7BBC269ULL, 0xFC618FD36EFCDC15ULL, 0xF0C4E16C5ABA60DFULL
        },
        {
            0x1C8D144C956A1998ULL, 0xF03DB9EC69100536ULL, 0xB2DFDC7B5F937010ULL, 0x70A01ACE2AF383C0ULL, 
            0xA43CB0A24823BC6CULL, 0x43BAF39F7AFBB22CULL, 0xE8425553775904B6ULL, 0xB883991D74800D7BULL, 
            0xDD932F7910D1853FULL, 0x7A10C5E60FBC9A7CULL, 0xEDCD9074E23486BBULL, 0x704E377B7CC4FD9AULL, 
            0x999E59B31CFD505FULL, 0x0F2CC833D0217935ULL, 0x35A4BE0AD5397E3EULL, 0x71FA75B0E2A106F6ULL, 
            0xA26F3D5A89135E0FULL, 0xC7D2485B9D424370ULL, 0x4DFD7B98D5BEF119ULL, 0x7A4CAD6B7DF2A96FULL, 
            0xBC19805DC19ABEA0ULL, 0x0A76F73F3A93C484ULL, 0xFA3C4E2DEAE1A66EULL, 0x42DD16C2BAE431D9ULL, 
            0x44E0BB95FE478B61ULL, 0x6326F667EE35A700ULL, 0x279655F1CD2A4A36ULL, 0x97BE61C540213500ULL, 
            0xFADF3178399517E6ULL, 0x128BC811E90A6234ULL, 0xC224D6211184E12CULL, 0x303BA10BF16798BEULL
        },
        {
            0x61C29D7774E86168ULL, 0x8E3EC52A04683478ULL, 0xC209EE65B5FD4351ULL, 0xA488D0F11CA4D2D6ULL, 
            0x0578F672E0DF5E6DULL, 0x79B527E1D8D5AF64ULL, 0xE2AB0ECC4D2382C9ULL, 0x380D44AB44F6A82FULL, 
            0x800D71F17DFAF005ULL, 0x2CE1ED00C8C88CACULL, 0x534D92C4EC38F123ULL, 0xB5A91FBE393B9173ULL, 
            0x1557E40FB81783C8ULL, 0x8F32AC76BBC60751ULL, 0x6BE8A17E94CB0AB3ULL, 0xE8213D6798CA151BULL, 
            0xD98450F6E856D4BDULL, 0x293647D037AC9CE0ULL, 0x58AAD1DE96E34A62ULL, 0x0732DDAC861D5DB4ULL, 
            0x2AFD7A6F3700F004ULL, 0x0F410100E7957823ULL, 0xD8E72FAE25465B16ULL, 0x5DB5C53EA9117EB8ULL, 
            0xF64CCE761BE7C26CULL, 0x263359966EA6E437ULL, 0x51AF652431B6C597ULL, 0xAD00725F116FD3D8ULL, 
            0xAF10FAB6E07D5445ULL, 0xFBCDA3CB25AAB8D1ULL, 0xEBAE4A0237732683ULL, 0xE7450B11430D4CD9ULL
        }
    },
    {
        {
            0x8852E409CB89943BULL, 0xC3325BE832120DA6ULL, 0x0214CEFD09FC53D4ULL, 0x45670D4C995F34D8ULL, 
            0xF00BB7F0A7FEE53CULL, 0xE990915926472747ULL, 0x8E2744936C6CBC31ULL, 0xF969173121C720F5ULL, 
            0xFE8662901DBCE390ULL, 0x036D077D5BF48F7BULL, 0xE2A076B8F012AC7BULL, 0x01723CA69E5B3974ULL, 
            0xBDEA2AC9C8C09415ULL, 0x5DADD3A0E2C69BBDULL, 0x24A4E280F0178E59ULL, 0xC94DD5AC5CC80256ULL, 
            0x9EC18364DE60F75BULL, 0x5B1DB6E188167A67ULL, 0xA3645DEE01D15804ULL, 0x9ED80ADF830B875BULL, 
            0xDD36C0ADA8D17825ULL, 0xEEDA0727EC3A04BEULL, 0xDBC614954B735E96ULL, 0xFC044037EA950103ULL, 
            0x33F3415322B622F5ULL, 0x1FA356B06E7E11BEULL, 0xB0D5A962EE5D3576ULL, 0xF52A9220363F519AULL, 
            0x4E695BD035A75DA6ULL, 0x109B7B0AB92A3918ULL, 0x37B525C778F1ED28ULL, 0x014C3C19F039D510ULL
        },
        {
            0xDEDB3F463A46C533ULL, 0xFE89DDA7E931CD3CULL, 0xECFCE7D848776EECULL, 0xE0A5257994A4737EULL, 
            0x8DBCF464312B8F96ULL, 0x641A4DA0CE6A5ADDULL, 0xB1DC5FD8C2D5483AULL, 0xC0FC5EC7FED77D0FULL, 
            0x85CCD503B0C044C9ULL, 0x3C70649FD3F54315ULL, 0x64B3004782DD657FULL, 0x5AEBDED9740E1339ULL, 
            0x60CBC1C2D71039E0ULL, 0xCC383272B4A37D3AULL, 0x8AAD1EAB96F7B468ULL, 0x82B7B4D545DA2863ULL, 
            0xE1E713CAC1F81CCFULL, 0xC165880524F640AFULL, 0xCF792AF672AC3A98ULL, 0xFF455EDBCAE871F2ULL, 
            0x79893EB47BF7FB6AULL, 0xA23B4B4BD46CAA80ULL, 0x88ECDFF66D96519AULL, 0xEF4389CA6952F7A5ULL, 
            0xE30DB8AC27FA4E22ULL, 0x44B2417B949CCBFBULL, 0x203A8B019B21BD51ULL, 0xF532D0E7382155B1ULL, 
            0xB186611CF9A68950ULL, 0x91D01C2A06F27418ULL, 0x40C2675570C196C8ULL, 0x313A1B4EECCEC379ULL
        },
        {
            0x182D5D6AE1C87DF4ULL, 0xBCB2570F5EDD299BULL, 0x2EBF00F2998E91A1ULL, 0x6439885E3BB3BA24ULL, 
            0x106F5F730B5A528DULL, 0x2828FC484BDEBFE2ULL, 0x93DAC56FE27B2756ULL, 0xD69C9D8D40D9333BULL, 
            0xD2C0071FFFBFF44DULL, 0x01EAE20E857BFB3DULL, 0xB511C2A934EE8834ULL, 0x1D178FFB84D502AAULL, 
            0xA81813543CBA74E4ULL, 0x94762222F3D30B4AULL, 0x3C0CB08B11B29BDBULL, 0xE85FC7EF6A134962ULL, 
            0x0D394E5F282F5BE1ULL, 0x23ADC9F6D7E984C0ULL, 0x7E234F9FD2B45328ULL, 0x37DC22D379294684ULL, 
            0xBF402F467FBD9254ULL, 0x3F98170D049524F6ULL, 0x952831AE2E406361ULL, 0xE43EE02D250C46F4ULL, 
            0x9EC3E6D750AC264EULL, 0xCAC47A528F566F87ULL, 0x6FD42C798C4D66A8ULL, 0xCB2F7AFC5FAB4CB4ULL, 
            0x9CB4504818D8BF4DULL, 0x9184AC7107998AF1ULL, 0xF78DF79CCDF51240ULL, 0x00FC8675B44A4AEDULL
        },
        {
            0x871DC7AE641E02BDULL, 0xC805053C74795561ULL, 0xEDDD853121342B68ULL, 0x7552A2CB06B4567FULL, 
            0xDCB4645AD38BD7F4ULL, 0xC6CE4B5E354AAE83ULL, 0x5007F1B10AF988FFULL, 0x2BEB86014BEFB2E9ULL, 
            0x99E2C0B0EA06CDA1ULL, 0x3E815BF256541664ULL, 0x3D9E36F591D765F6ULL, 0x6FC11C020FA6E167ULL, 
            0xD6F78739DA1FE262ULL, 0x078A43D8612FC679ULL, 0xE5023E4A4C307729ULL, 0xBD9F7D573EBF78C6ULL, 
            0xDBC9B0C7D6CAC976ULL, 0x7FE8EF5EFDE0F17BULL, 0x1E9BF666C5595646ULL, 0x59E727AF2E92897BULL, 
            0x9668C480ED77D448ULL, 0xB2432C361CD5B867ULL, 0xE61B51662B6FA784ULL, 0x5AE94069978C3DC7ULL, 
            0x8EF745C4BEA580A0ULL, 0x41A5B28DF1F34338ULL, 0x3DF78B4AB2C4A09DULL, 0xB7ED305E8974CBCFULL, 
            0xE34BF2BF18A113F8ULL, 0x654B16A87B4AE09EULL, 0xECAD49A0C5153BC0ULL, 0x156351D82EB73CD8ULL
        },
        {
            0x433994463B6C9252ULL, 0xC7072C9F7C284783ULL, 0x595D2217737284D0ULL, 0x347B9251408D7CEEULL, 
            0x2C42B22A14F0A58AULL, 0x8566B2CFA40B972BULL, 0xE83D2CF0471F8F4DULL, 0x71EBA836F290F417ULL, 
            0x508795EDE0D575E6ULL, 0x7714EBE27A20FC20ULL, 0x24E27258B9FC277EULL, 0xE651922EFDAD411BULL, 
            0xD02BFE244321931AULL, 0x794B6D0C100812ADULL, 0xE5D340D7E22E4936ULL, 0xB6AAAFA038C3ADE6ULL, 
            0x2ABC5232BFD3B5CEULL, 0x7CC954702867A119ULL, 0x22C0D6A025F0FCD0ULL, 0xFD16AEEEBFB1D6B9ULL, 
            0xE8ECA324B5E422BAULL, 0xE854E80340C186BCULL, 0xE79CC3DE321438FFULL, 0xF9A41B18142FB810ULL, 
            0xBAFC0A9428B37963ULL, 0x43E696BCE6540FDBULL, 0xA9B45EB60DA96EBFULL, 0xBB87496E7884CF79ULL, 
            0x8B905443AA6D3419ULL, 0x98FA73F7B62E700AULL, 0x8A63E3867C5A26ABULL, 0xE81B95152B4D434DULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseAConstants = {
    0xBCED716AC00ECE06ULL,
    0x923407E311543C4DULL,
    0x3860801EB6FC6288ULL,
    0xBCED716AC00ECE06ULL,
    0x923407E311543C4DULL,
    0x3860801EB6FC6288ULL,
    0x65498A09EC1E03FCULL,
    0x8431B5EC3755E46EULL,
    0x8B,
    0xED,
    0x96,
    0xD3,
    0x79,
    0x25,
    0x80,
    0x1C
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseBSalts = {
    {
        {
            0x22EFBAE9D67EB8F7ULL, 0xFC535EAD1925D0DFULL, 0x5D5A8875D0B114C0ULL, 0xB97C8885CBADD1B6ULL, 
            0x92CDABD5CAA6C996ULL, 0xD14926F412D31455ULL, 0x76F24615D7AEE0BAULL, 0x7EC20F947BC7D531ULL, 
            0x834FC1C65B0E8E92ULL, 0x5283B364B1F4CA1AULL, 0xA63B0DB04A27CFDCULL, 0xBD975974D95C9C64ULL, 
            0x3654C42A49C67837ULL, 0xA282BF04D932E7F1ULL, 0x3C9608203B80CF79ULL, 0x9AE5199DE69CCF87ULL, 
            0x9A2810CD0B1E7ABBULL, 0xE34258BB0FEF4B3EULL, 0xD1B5B097BF47C40BULL, 0xC48544DD69F15FCCULL, 
            0xA09F56CDF6F3CD96ULL, 0xFB7A337D9A061BECULL, 0x763493C18671BC2FULL, 0x138D4F059A375F94ULL, 
            0x521347AAE1C72695ULL, 0x490EF53A3D7DDA32ULL, 0x61B1EA4F202E7F3AULL, 0xEB8EB6BFD7D6B817ULL, 
            0x31FCB7ABB5FD165DULL, 0xDE313B61FB917896ULL, 0x2C5C55AE0951FE00ULL, 0xF0458192E8B01D34ULL
        },
        {
            0xDAF9E1AE346B3B25ULL, 0xC00F40FD87B8D2D1ULL, 0x70A0D659DE2A4564ULL, 0x4D626934D3CD55EEULL, 
            0x8DC8E68A7EBA9DE5ULL, 0x8ACAC88F1F1C9148ULL, 0xC9434C1EDF718D76ULL, 0xE7FD5812CC281C9EULL, 
            0xC5FDAED9916E5F47ULL, 0x75E5A007454DFA84ULL, 0x31CD34587B707E31ULL, 0x024B06BB0567C08DULL, 
            0xB5902AC952CC3D67ULL, 0xDEC2FAE7535D7C7DULL, 0xFBE38997372C9CC3ULL, 0xE15FBE6ECE5291ACULL, 
            0xE6949929E5C56BBCULL, 0x14B592A08ABCAC8DULL, 0xAA3CA9DB18781E6DULL, 0x762317CD01F111EAULL, 
            0x48ED27C5892AB3BCULL, 0x826495578E9D06F9ULL, 0x8220342888D93240ULL, 0x64B98FDA7E3255DAULL, 
            0x3DDE7E299C50D074ULL, 0xFDC8BA39970E01D9ULL, 0x448738BFC0E6C809ULL, 0xA6DC8B7A7EE15C28ULL, 
            0x64074F86C7337410ULL, 0xDF70FB4F8BB3B3BFULL, 0x5B6D6CC95E190998ULL, 0x359D427D763CDE9BULL
        },
        {
            0x850086402B997FC5ULL, 0xAC47EBCE7D8BBE8AULL, 0x6099F6743B4EB20CULL, 0x0B9963EBDF2FA701ULL, 
            0x50A66F587B7BB3C6ULL, 0xDD23BC548BED317FULL, 0x7169F2887E0A46ACULL, 0xE5762B65F1C12025ULL, 
            0xB4589C0F5FAF4138ULL, 0xF96FFF1BC0734E2CULL, 0x7C3B0876D0FF9900ULL, 0xE12F5823BDE12B8DULL, 
            0xAA5D1B4C88079273ULL, 0xD398E11CE1C7580DULL, 0xFA1B613B17006999ULL, 0x6D8610D8CEACC29CULL, 
            0x178FC0B3DD110C2BULL, 0x5B49B0506946C7C4ULL, 0x2B433431DEC551EAULL, 0x8E08984C150BE4DCULL, 
            0x1B05DF43D9384DCFULL, 0x4CC9E294E6BD98E5ULL, 0xC5C2E07942ADC53CULL, 0x063B2F0E03B5D172ULL, 
            0xFD3AA551C797E107ULL, 0xFB769DE0739CB97FULL, 0xF6DAA0A64F55547EULL, 0xAE07EBDB1A3EA3D2ULL, 
            0x19370407D7E2220CULL, 0x92C378AA8AB8EC1AULL, 0x03A4E89FBC74B790ULL, 0x73CF5D824F4F1796ULL
        },
        {
            0x679C1BA98683FD6CULL, 0x0CB28FD145873F55ULL, 0x975D72FFBD07267FULL, 0xEF4DA69C203EF0ACULL, 
            0xA9DF0953F3A08FE0ULL, 0x5E857F23C9C9F6B5ULL, 0x52BE06237385F9D2ULL, 0x4AF09CF8637CD64AULL, 
            0xB1DBA72ED3D02FA0ULL, 0x31E1C015955C4A77ULL, 0xD47C7302CE1CCC4BULL, 0xB1868A5C9F0B4368ULL, 
            0x35892DB49A3D33C9ULL, 0x9D4301D820C38A00ULL, 0x6983EF2DF7175D83ULL, 0xC5D16CCB1B29D346ULL, 
            0x7F7FFAC9BDE87C24ULL, 0xA02A3C201C53451BULL, 0x49A189934256A5CFULL, 0x4CDA417A2AAC6914ULL, 
            0x9920E4CA5663824FULL, 0x5561F50DF8D91B9BULL, 0x40DC6CEBFAC9DA78ULL, 0x8C8F87121C80413BULL, 
            0x3C0B31F06C612D22ULL, 0x487232FE2EF0D819ULL, 0xBCE4E29A0EBBC64DULL, 0xC178FA04FF93E60AULL, 
            0xB78BB8ADFFC39D64ULL, 0xB01CDB16C8C2B3DCULL, 0x585019A9EB17A6E3ULL, 0x90F3AEAB1F6B62A4ULL
        },
        {
            0x098394F22B71EB95ULL, 0x26DDB02AA85855E8ULL, 0x0292D68445FA615AULL, 0x7223BE40B34097FEULL, 
            0x039E0C7CC012AF9BULL, 0x25A90FE62C35749DULL, 0x1E489E982A34ABE1ULL, 0xA9F90A835BEC23A4ULL, 
            0x12253A05B024D787ULL, 0xC5DF79E6EB4AFA78ULL, 0x27952C77FB0B068BULL, 0x5272739D61116E3AULL, 
            0xCCDCD0D6B81244C1ULL, 0x5F1D73DCDCEF1D58ULL, 0x52BCCDDE7BFB2C4CULL, 0xB32D9F6FAE4952ABULL, 
            0xE347CD24EFD422C0ULL, 0x1999D90BF20A6A36ULL, 0x5CB1B5052CA4E15CULL, 0x034058CA5DC614B5ULL, 
            0xE1B8D0F41FE7F2A2ULL, 0x96FB1469FC8F4113ULL, 0xA5EBD79C981684ECULL, 0x978D983FCC580A9AULL, 
            0x1CF966F07EF69051ULL, 0x772BAD21C4DB8C2EULL, 0xDFED83869BA493B4ULL, 0xC7FEE3894BB0024CULL, 
            0xB8D7BDBEEF69036CULL, 0x86FB2D7CAA515CC4ULL, 0xD4F560A6E39A7AB2ULL, 0xB3874A3F79487B41ULL
        },
        {
            0xD7F355BD2340E938ULL, 0xEBD5CE2117B1B446ULL, 0xCA3B8185E7EDBF4BULL, 0x1E1B7E51067F4A46ULL, 
            0xB7255A45FB626096ULL, 0xC5EE5023155ECE66ULL, 0x67274ED191ABC747ULL, 0x884C13FB5A3C87BDULL, 
            0x47EA5EC0C403E319ULL, 0xF665D57E4E6276B4ULL, 0x5B0AD50597CC35D2ULL, 0x6BC9059AE0A33460ULL, 
            0x967F8F1D1D5719D1ULL, 0x09F8D06189EFB748ULL, 0xBB24747283AF5CCEULL, 0x9910DF3746047569ULL, 
            0x47347047F6400CBAULL, 0x8A70349620F0FDB2ULL, 0x3BC3B7C118266E59ULL, 0x503B44AA80839431ULL, 
            0x8FBCB4E12D2CB2A1ULL, 0xC5E37EB4A153F126ULL, 0xBCE8829D0596665FULL, 0x558B47D4622158B0ULL, 
            0xA8C6AE63046CB8FAULL, 0x8872B95032A7557AULL, 0x962220759A71BE7FULL, 0x2E7D520BDE2B6792ULL, 
            0x963BAC147B3954E3ULL, 0xCF58F2C6369E7D3BULL, 0xA992740ABB13B76DULL, 0xDB2EB27B6FD854ACULL
        }
    },
    {
        {
            0xAB33440B9FC9420FULL, 0xC52F2F8462406E94ULL, 0xCBFDD780DC7CB363ULL, 0x106247360EBB9B23ULL, 
            0x5CBD2D703CF4B2DEULL, 0xEEB7FE0DF0B9A3C2ULL, 0xFFE72AC2BF788767ULL, 0x71349CFC5C659152ULL, 
            0x1C5BC5E6373F5389ULL, 0x9D2F63AA2F97E1E6ULL, 0x923DFE92E2FE6A71ULL, 0xF841EA71AF946DD7ULL, 
            0xBF05AAE40BA20E86ULL, 0xB9B21BF4957C0419ULL, 0x7A5B5FB3316F5673ULL, 0xC906095EF97317A8ULL, 
            0x35FC16AA3FCD3A37ULL, 0x34BD67928AADD2A2ULL, 0xBA380E996B40A6ADULL, 0x80E9D4D67A487693ULL, 
            0x6A4E8F6BABC082ABULL, 0xDA1152F3F2EA9C5EULL, 0xB4F419EBA6DEA80AULL, 0xEF0BB1A99A26F37AULL, 
            0xCF264D0FA417F6D1ULL, 0x588CF767005CA73EULL, 0x919F71CD8C233F5AULL, 0x01EB7C009876113EULL, 
            0xA75A2FF8EF923A57ULL, 0x6C3EF7F89C81A4C0ULL, 0x332E922747AD227EULL, 0xB23C1E8169C5A5A0ULL
        },
        {
            0x9A50808341A3E590ULL, 0xC8F4E4D520632013ULL, 0xC7F60C1A27DE3E60ULL, 0xB7A22F048C4D23C3ULL, 
            0xA862E2123ED1E626ULL, 0x0CFE93D1AC3A9C42ULL, 0x0475602BA3717890ULL, 0x86D97F9884967FD5ULL, 
            0x23794D5FE60320B4ULL, 0xE393A47DED216884ULL, 0x864724005B590286ULL, 0x505FE85C6722994AULL, 
            0x0F95C7416D6E1FB9ULL, 0xED5E9FE8B728BEF2ULL, 0x5C18923B0DDA1802ULL, 0x1D5DC28D86945F5DULL, 
            0x02F5789C638D2266ULL, 0xE4E054F71EFF6719ULL, 0x9A3C3045BD2933BCULL, 0x2C60A7040A23C745ULL, 
            0x153F2695C4268E19ULL, 0xC8BD4878F1BE9B2FULL, 0x9580AD91C017564CULL, 0xCF7800EAF48D5A8EULL, 
            0xD7D1F55008C62D87ULL, 0x893E0F6FBF6EEF82ULL, 0x1888C9ADF1080373ULL, 0x2472079140BFEF06ULL, 
            0xA6B58321212D293CULL, 0x4AD5C21B56FCBC0BULL, 0x9259AA57DE7B87E7ULL, 0x6BC4A9A95ECD32FDULL
        },
        {
            0x0D0CADA3CDB3FFCBULL, 0x0EC4DCF0A0C48F63ULL, 0x6C7FBF51DDE3EFC5ULL, 0x2096F0A5EDDF1A2BULL, 
            0xA4980932D940B8CCULL, 0x81EC160870C6DB8CULL, 0xD4D0ECD9D88395BAULL, 0x0D543B2D81550077ULL, 
            0xDF8173F701BF805CULL, 0xE08BAC8EDC459CE9ULL, 0x72C57B357FE617F3ULL, 0xC6C26D5B87588997ULL, 
            0x5F1BC23A62CC1AE8ULL, 0xD0785C04344A96BAULL, 0xC409B8631E68136DULL, 0x7FD882D4E9ADFD04ULL, 
            0x963D2D2AFBE2D571ULL, 0x69BA45549F5ED5C2ULL, 0x4BC820A1328DEF7FULL, 0xD4CE05EC72C7F19DULL, 
            0x66EB228A77D4AD88ULL, 0x2412182FA4473EB4ULL, 0xBD655AD0EA4BEBBEULL, 0x0678FA55483F362CULL, 
            0x44476086AE403207ULL, 0xD9A3B8E93D0FBD7BULL, 0xD78FCA7B47BF0DBEULL, 0xCCBB259516944C5BULL, 
            0xAF3C3E9E76DCB875ULL, 0x32D26EB9B10EB6FEULL, 0xEB8875B185FD3079ULL, 0x12252C514E5E75D9ULL
        },
        {
            0x070D6D9B09E407BDULL, 0x10F384F11F98A55FULL, 0x9ACCADC718A8872EULL, 0x166838992E4D0942ULL, 
            0xEAB746BA2C60AB31ULL, 0x2A1733E93CC7EBF4ULL, 0x808DE2D77D72BACFULL, 0xF4271358628BF347ULL, 
            0x338D0128533F54BEULL, 0x7B5D5842A34DF0E1ULL, 0xA1E04BBCB886D375ULL, 0x47F436D24A9A4E01ULL, 
            0xDEBC2DB97C98EFA9ULL, 0x13D5C1697E73795AULL, 0x450FA71CE5735018ULL, 0x0BB558EE34654D61ULL, 
            0xCCA5F9FCEEDA37A0ULL, 0x151EDCCFF0E9EBF4ULL, 0xACDB284D1BA523AEULL, 0x61CC083F0DB31185ULL, 
            0x9712CA7345DD5BA4ULL, 0xFD04C93B1055CE76ULL, 0xC8D43DE83FFB1A15ULL, 0xBC053D3AE32D71CEULL, 
            0xDFF99C1B11291379ULL, 0x09420B5C2CD65522ULL, 0x74CACC1AE3F08A4CULL, 0xD73B893727AAEF52ULL, 
            0x8B81C1E0E3BCEC50ULL, 0xC01E6BCA98D1DC02ULL, 0xD9A7221EC2BF55A4ULL, 0xCAB647EC8E3EF4CCULL
        },
        {
            0x8A1A62B8AD188AD5ULL, 0xB0BB969305B69C6AULL, 0x753613D15AF5E08DULL, 0xA9E08F122A19FC95ULL, 
            0x92D12C6192B8AF28ULL, 0xACA5A09DC7238F8FULL, 0x4E6A1FE874B47C12ULL, 0xA9CF103B892CE5CCULL, 
            0x4CA5A981C3C06EADULL, 0xD591A6A28A05B7AAULL, 0x2A1DCADA15531841ULL, 0xE86B442EC6B9A720ULL, 
            0x37E332465CE6D864ULL, 0x3BE2D2C3702948BFULL, 0x3D5B02332484C504ULL, 0x43D39024F2D2C7C0ULL, 
            0xE76938126E98310FULL, 0xE2250A63B01862E9ULL, 0x16F1ADF09849A0EDULL, 0x3AF6212E5600DE33ULL, 
            0x299DA925073F26E0ULL, 0x11F16556C9D0AEA0ULL, 0xC3FF0ED9303BD66CULL, 0x7C318701F527C555ULL, 
            0x8656D9BE7BE32873ULL, 0xE4A77DCBF3F0D4E0ULL, 0x263F17DDCB3D0DA4ULL, 0x719EBA237C0C5BD2ULL, 
            0x471CC03724171F9FULL, 0xE7B1D07B848EC9F9ULL, 0x85DA2799E29C395FULL, 0x207502B326E9CEEAULL
        },
        {
            0x07F3FB1CCB5E5AE5ULL, 0xDF2D923BA0F782EBULL, 0x177A8320CFDBAD45ULL, 0xAECB4481C1F27516ULL, 
            0x7A3897522DDC57D7ULL, 0x96E7ABF72DBBF59BULL, 0x2772E2153F1EFC7BULL, 0xD26E49524F548138ULL, 
            0xE661A482F43D955CULL, 0xAAA63F4A6ED7BAD7ULL, 0xE92EBAF2F99E2C16ULL, 0x78A4FB0E543550FBULL, 
            0x572036D7E76F93DEULL, 0x396ACC3DCE83E6B9ULL, 0xBFFFAAB13506A939ULL, 0x71ACE12F547C5E03ULL, 
            0x249C2384D80A2EC6ULL, 0x95863D6EA0D21A09ULL, 0x0222C99EF2A3F2DFULL, 0x19EECA8193ACF238ULL, 
            0x0A641DA43167BF56ULL, 0x0081FD5AA65C511BULL, 0x70DEC801B1ED218FULL, 0xEBF53372F6A44005ULL, 
            0x34C82F2FFDE67F47ULL, 0xF2E03DF9DF01307EULL, 0x52FBA100E98A2847ULL, 0xE140929BC9408573ULL, 
            0xDF81CD59C8983955ULL, 0xC48E245CB44646C6ULL, 0x8D99FF631D24FF31ULL, 0xA633C7DD1EA0620EULL
        }
    },
    {
        {
            0xEF16460C40F849FDULL, 0xB7952505B713C3C0ULL, 0x4D53F1FFCC85FDDFULL, 0xE2DEF1122D7688EAULL, 
            0x7480F7113D2935D1ULL, 0x2F547566E27736BBULL, 0x016F4DF8570A03C8ULL, 0x3BF8FDF697C78A78ULL, 
            0xD1C5C0BEBB01788FULL, 0xF4CB97CCC2A70F3AULL, 0x0F94CABDDB9E3689ULL, 0xC3394D53C9345A39ULL, 
            0xE24B0F816C4A61A0ULL, 0x39BD5AAC20D6D041ULL, 0x627F94B92CC258E5ULL, 0x36CD4D4751FB7E25ULL, 
            0x0B090F9F7CF8785BULL, 0xDDD56CF45600E29AULL, 0x5BB226ADE06A4D0BULL, 0x6B60AC2D314E2F48ULL, 
            0xE431632193BECA5AULL, 0x6F8440D7D457F7E9ULL, 0x36F208880CCFD2E7ULL, 0xA91E98EEFDA4EF4BULL, 
            0xBFEF551326803747ULL, 0x172E8D788047088AULL, 0x060FF696806E5889ULL, 0xC5D74DD6D8A7C01EULL, 
            0x6BF58A43FF799D72ULL, 0xD85B3FAFCE2B48A0ULL, 0xAC8C2D0D8379FAC2ULL, 0x0549389ADE06AFD2ULL
        },
        {
            0x9C28994D53EDEC31ULL, 0x4FA8588A1597CD69ULL, 0xE9C7EDDEDD50F128ULL, 0x110F06B145D6A152ULL, 
            0xA41700D527F97523ULL, 0x55D12AF8A33CE9BDULL, 0x64A17FCB2B0FFADCULL, 0x46C4E4C33702B5CBULL, 
            0x5FD933F2F8FFB8F5ULL, 0xB8B2D34F9BAE83D2ULL, 0xA89B026CC38F728AULL, 0xE82872DF55E46E9BULL, 
            0xC300A08A11EC25B4ULL, 0x3EF2B822B24CECE8ULL, 0xC41A78D20642BD44ULL, 0x82837C394E0982A9ULL, 
            0x505D3B91927DBD7EULL, 0x43D383ECE1715D6CULL, 0xC1954C25D3AAD572ULL, 0x64B4F10DCB3F614AULL, 
            0x33CE9484C3503A90ULL, 0xFCEBDB6DA356CCA0ULL, 0xFE8F2B1F91B6E8DEULL, 0x35889A8F41677095ULL, 
            0x36786731183DAEC6ULL, 0x2A4912433610CA5FULL, 0x14861E6FC75857FEULL, 0xD95CBD1ADC78FEBEULL, 
            0x55501C174CA42003ULL, 0xC459D30C8E1B4597ULL, 0x091252D40AEA0488ULL, 0x9A0D032E88C35770ULL
        },
        {
            0xE4C3F39453277533ULL, 0x9EA3749038DAB016ULL, 0x94BE5538E8D510E0ULL, 0x74DF91F353104120ULL, 
            0x8C2C2F2B251DCBC6ULL, 0x48732218C63F05FAULL, 0x7F3BF04AFD747A30ULL, 0x830961B26213D640ULL, 
            0x14E0C6717B9CC321ULL, 0x1B78798F631D50E8ULL, 0x48327A9B33B7B98BULL, 0x843A8E47A790DBCEULL, 
            0xCD85229987AC8718ULL, 0xF7FF95BB8430C682ULL, 0x475A1586D8E23641ULL, 0x778E0E831AFDF0EEULL, 
            0xD093B4D5B3FD5A2DULL, 0xB8B46C6481DAB383ULL, 0xDE40DAF8B26B0A6FULL, 0x129CB5073D819F30ULL, 
            0x5DF70B01365806F0ULL, 0xE25FD5184B6A3952ULL, 0xD7546958EBC05BE7ULL, 0xA3F858D0A52AE86BULL, 
            0xF08F7938CB2B6790ULL, 0xD8D9B59F952B8E2CULL, 0xBB12A0E8DF3F9022ULL, 0x70BFC1E6D627BC8DULL, 
            0xE18612488BCDD0D2ULL, 0x0D3E95FFB2B60F4EULL, 0x8674693649828476ULL, 0xEC961C6E07739BEDULL
        },
        {
            0x59803543C46E5F3EULL, 0xE948D8133531775EULL, 0x1FD9E2A755E21D13ULL, 0x4451503BD5B25A07ULL, 
            0xD97EF94A53B08205ULL, 0x54564F41049A04DFULL, 0x48CC9B8447F096E9ULL, 0xF9FA62848FD1C374ULL, 
            0xAA69D52EC185C1E2ULL, 0x39CBA731F4F05CCEULL, 0xE908A63A20CC5E1DULL, 0x04BEDEBCADF5E802ULL, 
            0xBDA62859102C523CULL, 0xAC721E4787D7C186ULL, 0x8349956FEC92986DULL, 0xA25BE3484E78D40CULL, 
            0x13851CB1D6B4D97BULL, 0x8C63319132CDA982ULL, 0x68ED326A3E889394ULL, 0x5A212938851887F3ULL, 
            0x8A72C0F361715EA4ULL, 0xED72D9DCB5B1B379ULL, 0x81A09D5043C47CDCULL, 0x188DF418E6CC9B1FULL, 
            0xBF272266F1C1DF2EULL, 0x1A84C46D949E1216ULL, 0x0A05CBCA97CA8728ULL, 0xE1F2BB34C082132FULL, 
            0x61A9284ABB341BAFULL, 0x9E6E4803B0B82170ULL, 0xDAC87BABCC5CB98FULL, 0xFC429BB75F615B1EULL
        },
        {
            0x9E774C072502091BULL, 0xFDD42A85F5DAFA96ULL, 0x2ED3E87DD1EE835CULL, 0x9B3CD463E3B3B5DEULL, 
            0x7E00B507261F6666ULL, 0x0BD05A65FDFA8C5DULL, 0x1AB0F20978AB567DULL, 0x5BE646E5CD8B4EA2ULL, 
            0xAD39DC654FEC03E1ULL, 0xFB6C335B72B38EF5ULL, 0xE7107D277EF631D9ULL, 0x97271E492AE5E56AULL, 
            0x074E0098C366A3D9ULL, 0x0896C777E3D53019ULL, 0xE8F4026345445E02ULL, 0x59F177BCF5F03569ULL, 
            0x8A6E01E8FA78C163ULL, 0x1EB0220793175D57ULL, 0x9F20FA294F42DC9FULL, 0xEC0748B89E0DEA42ULL, 
            0x889AAD7EFEBA6330ULL, 0x86586C7D8F333433ULL, 0x20F4B4C31EF20565ULL, 0xB4DD3F397BEA76A9ULL, 
            0xAC21B2FFC8EACA03ULL, 0xCC37D8BCD96B04AAULL, 0x16DA8BD69EDAD087ULL, 0x1038EC3D8D26206DULL, 
            0xEC7DD828F7E74CAAULL, 0x0C86628B7E55DE7BULL, 0x3CB111171CA40F72ULL, 0x0F4796819C546A4EULL
        },
        {
            0x372DDE8DC9093AC0ULL, 0xE75C02ADC889D0D4ULL, 0xC5D7317F01779490ULL, 0xEC583128BB8AA4D5ULL, 
            0x11C91C068665ABD5ULL, 0x546A7FE8EBA366A9ULL, 0x60EB8FBE15F586D1ULL, 0xB98C21AE5DCFE47EULL, 
            0x9579F9A306BC2220ULL, 0xAB689D312F4007FEULL, 0xF270D02BEE9C3157ULL, 0x036BEA92E6B3A4F8ULL, 
            0xF94B10733F5D6E1EULL, 0x858871708F1D41D4ULL, 0x294F4F8B72778A94ULL, 0xF7CA448A39FD807DULL, 
            0x17407AD2553310AFULL, 0xB6C901D8C0AE5973ULL, 0xDC071A3E59752F83ULL, 0xEBBD888608E965DAULL, 
            0x25A10C7885FFC025ULL, 0xB1654C8B210FA29FULL, 0x4292DF2A8C33D04CULL, 0x0F7948F042CEA641ULL, 
            0x24FCB7AAACCC57A4ULL, 0x090F81C40ED75AEEULL, 0xAF004EAEF54BE6FDULL, 0x0C6581620840648CULL, 
            0x01A8A607BA4F4AEBULL, 0x278C4A298F65AACAULL, 0xD180811F2B821FD0ULL, 0xE204822483096D1AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseBConstants = {
    0x5AAE83B6F8005A2FULL,
    0x74CEF4130D4119B6ULL,
    0xD8D360671C6DB647ULL,
    0x5AAE83B6F8005A2FULL,
    0x74CEF4130D4119B6ULL,
    0xD8D360671C6DB647ULL,
    0xF460D1A2CF9FA0FCULL,
    0xD3FAC1255C4F04A5ULL,
    0xA0,
    0x28,
    0x98,
    0xA9,
    0x9F,
    0xCC,
    0x8F,
    0x1F
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseCSalts = {
    {
        {
            0xA10350D978E11DE3ULL, 0x9128A70CCE74A996ULL, 0xEDBC1361B263036CULL, 0x5FCADB854DA78CA6ULL, 
            0xB34CC48645C1DC9EULL, 0x88EEB7D3C05FF0CEULL, 0x133662BDAA9F69B1ULL, 0xA8E23BDA171885ACULL, 
            0x5F0DD1F675F803DDULL, 0x0A30657C35480D5EULL, 0x86B715B069252484ULL, 0x2AFB5EDD4C7A7BAEULL, 
            0x001EA811A7473A98ULL, 0xC93F7C4DA755A583ULL, 0x5D05165973D41911ULL, 0x083BFBBB1345F5BCULL, 
            0x0B7D13CDB9527D7DULL, 0xD8D93B1021EB5551ULL, 0x40E24D1271D3C6A8ULL, 0x8E98C177904C7878ULL, 
            0x8B49C5B8692A1AEEULL, 0x85E603AE4920BDD4ULL, 0xFE141D94D05263B0ULL, 0x314E15370DF71D83ULL, 
            0x54488DA0C8A47E0FULL, 0x60995B6B249EE46EULL, 0xFE5CEBE7760ED29AULL, 0x1EA434E49FA73094ULL, 
            0x50A2DC8AEEC726D2ULL, 0x15D7F598112D5F78ULL, 0xB5E945CB8F74A8D5ULL, 0x7A5EB65A4FEDD45AULL
        },
        {
            0xE8A12646BD86E89CULL, 0x06BC4FD1AC6BAC53ULL, 0xDB3411D3031C8B29ULL, 0x27E5122ACDC53C7AULL, 
            0x3BD446B3A051671BULL, 0x540E3E8DB946AF8EULL, 0xBBF7560AFBAF0563ULL, 0x08CD39CD0320FE53ULL, 
            0x1B2BD005868A9EF2ULL, 0x7274797E0FDC3A73ULL, 0x0E7415667A1AEF10ULL, 0x6DA0FC6C309DC110ULL, 
            0x3AA0624F5F345897ULL, 0x8D4D1EB2AE98A62FULL, 0x151DD3DC1AB0EFF1ULL, 0xB81AD2575FD1527BULL, 
            0xE9B7133428A1DABDULL, 0x3D687EB72614880AULL, 0x1AB5E6D1899D6ABFULL, 0x63E251D2369742B7ULL, 
            0xE751C7DD52B593C3ULL, 0x6B167DEF050F2E03ULL, 0xB91D05FE14244290ULL, 0x34F70F44EB8DBEC4ULL, 
            0x5B872BF9C0FDDDE4ULL, 0xE158556A4991CA68ULL, 0x62C807EBD7139948ULL, 0x727E6596592F4F04ULL, 
            0xB63C817E16D6ADE6ULL, 0x7A3B1F0E38446B3CULL, 0xC787E1CE564A4002ULL, 0xBCD0ABA65F25B749ULL
        },
        {
            0x896D2CB283F33879ULL, 0xC48389DA12652DB6ULL, 0xA3D84551FFC14927ULL, 0x7B0456B43D9B33AFULL, 
            0x7DC9D4E2C7F296B9ULL, 0x79C4A81B603CD868ULL, 0xD308128252CE8067ULL, 0x02A3ACCE6D4A0900ULL, 
            0xCE0FF2A828143822ULL, 0xDCE0C704A2ADC7E6ULL, 0x976BA902E46BC55BULL, 0x8B982A4D94FC707EULL, 
            0xEF277EC42859FA0CULL, 0x3E6E156FF1445A41ULL, 0xF165F12399EDDC0DULL, 0x522AB51C9C8E24B4ULL, 
            0x138708D947CFEF14ULL, 0x89C411F174827CEDULL, 0xCADA72984896C7A1ULL, 0xCC29638A3D6B16C7ULL, 
            0x8A287BAE095B55A0ULL, 0xD6C203C94A5FEBE5ULL, 0xF42713A8975DF68BULL, 0x6DE599306E33B91EULL, 
            0x12E26A468AF65EAFULL, 0xB98E1B1025F0405CULL, 0xCB768B2901F96DE7ULL, 0xD0A6B7FFBAE4AE34ULL, 
            0x6BBFB7A04CA0EA29ULL, 0xBE8BF1FF217DE37EULL, 0x6F53513E4579479DULL, 0x8C8557C55A855E1EULL
        },
        {
            0x9CCF3A0A08F0F45CULL, 0xE2E2250B55298176ULL, 0x40104B213C0BF281ULL, 0x613066FA7B937B4EULL, 
            0xBEF66746AB47AED5ULL, 0x614242202759BE8BULL, 0xABE53765FED11F78ULL, 0x3DD25071C33E5288ULL, 
            0xBFDF933CF342F5EEULL, 0x8A2833EDC44BC2D2ULL, 0xF99F5402519D5B3CULL, 0x0A6C98154CDEF07FULL, 
            0xF4ABB88977E071F2ULL, 0x23EB024DAF1C9BA4ULL, 0xF5D3F8231DC8787DULL, 0xEDE03BE6178CFB33ULL, 
            0x6CEF3628F00D7843ULL, 0xEE297D6EC7144F2FULL, 0xD62214EB9444C49CULL, 0xE0A1147D73652CBEULL, 
            0xAEFCF983240D9769ULL, 0x8F7D22C5C0AF19A7ULL, 0x67B6BA3719E61F38ULL, 0x6744CB3C0F6791FDULL, 
            0x03B31DC92117D09AULL, 0x22BBF92A6AB472D9ULL, 0x3F9EE509A4992701ULL, 0x500685CEEB11B84EULL, 
            0xF58FBACAC3772314ULL, 0xF64E006F40C26169ULL, 0x5361A4880EAC00C6ULL, 0x0087DEE7826E1621ULL
        },
        {
            0xC4A0AF4AE6B6941DULL, 0xF89FC760A1F64CE5ULL, 0x4957FF7DEFF48240ULL, 0x53459034F9DDF7A4ULL, 
            0x6114545D4A374327ULL, 0x5E701FC4EAB03DBBULL, 0x75EB41F888BE86DDULL, 0x44ABCFAB1BACE405ULL, 
            0x4AEC13FFB5B0FF0FULL, 0xEC700BE72ADA352CULL, 0x19C3C1B208C530F5ULL, 0xBF08DFC9ECBBBD12ULL, 
            0x65251F6DFBE72B62ULL, 0xF1456B34FB982FECULL, 0x478C206021B856AEULL, 0x45D192E2189C1C9BULL, 
            0x1FC44B2EE6494506ULL, 0xCAA6D523016740ACULL, 0x09C00A5E37494BB8ULL, 0xCAF9099066710E6CULL, 
            0x5133080AF3E40EFDULL, 0xD5E1671296F07DA4ULL, 0xA87AE0DEB49E5E2CULL, 0x17B3F14A6F545C8DULL, 
            0x6A2C54E029238CEBULL, 0xD2F1D1998C1D0C1DULL, 0xB0C9EB256052A039ULL, 0xFC9C6CFDB61727DEULL, 
            0x94F360948E743C37ULL, 0x9F899A73723AF0FFULL, 0x48F73F8214B614B0ULL, 0xB700B006F26F1CB6ULL
        },
        {
            0x6DE5D98D5BD0372FULL, 0xD7DC72F6AEF8B8FAULL, 0x0EEDE75EE3F0336BULL, 0xB611ADFF96172177ULL, 
            0xD51A0072851A1ED5ULL, 0xED4CED440B86EE43ULL, 0xEEED76A3815BD06DULL, 0x51ADCE2E5CC4AD59ULL, 
            0x38D2239E67BF9172ULL, 0xF684B1F333AEA293ULL, 0x894FD11751A1435BULL, 0x78C45A4955E5A368ULL, 
            0xACB3E396BF9126E5ULL, 0xDBECDBC42FD5D174ULL, 0xEE758545556FD653ULL, 0x4E270F0338F828CAULL, 
            0x182477E96C20890EULL, 0x0C4F739FCD45D31AULL, 0xBCE90F02505CBE2FULL, 0x4343298CC9B1B50BULL, 
            0xA8100FF9F7EF0A96ULL, 0x19FD7856C7521034ULL, 0xB9595DDA461DC6C4ULL, 0x3F78C3800A2AECB5ULL, 
            0xFE5D772D08E6D765ULL, 0x93291CCF2F93864AULL, 0x8805BCCA09E56E37ULL, 0x9039E7CB9B6C78C0ULL, 
            0xFB748C3DB4EF0D61ULL, 0x847733C16E87C848ULL, 0x9201AD67692C9302ULL, 0xF2C25FB7BFF16E13ULL
        }
    },
    {
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
            0x1BE450B1B551F9C1ULL, 0x2E6F5E4F8D52EC79ULL, 0xD5FBF21E84D7E6D4ULL, 0x13F872CB71DF2880ULL, 
            0xC08914B74A99A5C8ULL, 0xCA883D88947FB486ULL, 0xC1921B7C4CD8351CULL, 0xD8D983CF2A4A64F9ULL, 
            0x1634DD36BE784908ULL, 0x890351592CAC5A3EULL, 0xDB366EB6F76C2508ULL, 0x73E2A61CE3D4C8A6ULL, 
            0x3ECDBB364B03AA66ULL, 0xC22ED85085C81671ULL, 0xFBD5A361B5B0436FULL, 0xAD8BDEBA9B498D21ULL, 
            0x2DF1BABFAD2FEC09ULL, 0x15F36FF11ED56742ULL, 0xDB0EBE79853E9F36ULL, 0xC426393BDC158C40ULL, 
            0xF44B23630257BD45ULL, 0x7BE852226A76036DULL, 0x64CB6875866EE424ULL, 0xA0DB8668DE8414CEULL, 
            0xF134D09B408BE8A6ULL, 0x3434F71681447FD8ULL, 0x6271442BF5203D5CULL, 0x3A6978DB2918BB16ULL, 
            0x75C855F7FB008B6DULL, 0x837B38DB8C99AE42ULL, 0x0E2EE848632C92A9ULL, 0x170C6B9FA5647BCEULL
        },
        {
            0xD19586458D85A5E4ULL, 0x186E96C28A68281EULL, 0x43E9CA4634F4E240ULL, 0xDEEAD6A02549A301ULL, 
            0xBE3B0686A360DFF6ULL, 0xDD82E4A8EA545C86ULL, 0x23BD4480705C3E22ULL, 0xB91F208B4ECEBB84ULL, 
            0x5D1BF67E284F05D1ULL, 0x6A9B902C12DD0D8DULL, 0x1B66B8A1027BA3E8ULL, 0xC5B3F306A0D54465ULL, 
            0xED37D98295F39FD4ULL, 0xA24F5F57B86494C6ULL, 0x688D9B30438C479EULL, 0xA6CBC6E25ADD4049ULL, 
            0x0401C25119CC05E2ULL, 0xB0A392BC3C87EB76ULL, 0xD81CD2478AEA78F2ULL, 0xFC8FADE33627DDB4ULL, 
            0xB4DA4ED8DAB8B53EULL, 0x171326F2F32729B2ULL, 0x240243650F53BFEEULL, 0x697E491FB7E031E5ULL, 
            0xCF547FCABA03DEAFULL, 0x2CBA07E293FC4F8CULL, 0xDED2EAE04F521F1EULL, 0x1978B523B4CE2F18ULL, 
            0x39AE3A133CEF49D6ULL, 0x223AEED4CB13BE27ULL, 0x82FEA62F0CC02B12ULL, 0x0C42FD6EA357A260ULL
        },
        {
            0xF2E4513431B800A8ULL, 0x7DCF175FDAD1636AULL, 0x958F494436B104D0ULL, 0x4042A684280EB5EDULL, 
            0x238941667D09CAC8ULL, 0x2031ABAA227EB9EAULL, 0xC953E07BE0AF1B26ULL, 0x249B1EE2D372E518ULL, 
            0x0EB01215D26E8127ULL, 0x3EFB2BCD68AA64D1ULL, 0xAEB9547DDC630DA5ULL, 0x3796209B8258B2B6ULL, 
            0xCC037096B48D7B87ULL, 0x57ADCAA1EDB2F912ULL, 0x7C241DE61468B8ECULL, 0x483B077BDF1DC9B9ULL, 
            0x1F66246874CAA63EULL, 0x35BB4AF0239EFC38ULL, 0x0C520C36421C378AULL, 0xF611D6D4B1A18C1CULL, 
            0xAB2E2A6F6D7F796AULL, 0xE13607DFD0C61DE9ULL, 0x26DD101FAB34B4E3ULL, 0x07458FE96F7EB2C7ULL, 
            0x2DF24746C6E2935BULL, 0x8FCB075ED6434AE0ULL, 0x10EF9873A9DA718EULL, 0x3BF2DA39937CA8E0ULL, 
            0x99AAB3957743204AULL, 0xA98097411618763FULL, 0x706912762DC13C52ULL, 0x719F48FA03BBDC8BULL
        },
        {
            0xB4B807AC59D7BB36ULL, 0xADB4416CA59D5309ULL, 0x86C72E96631D3A12ULL, 0x264F77951B67AE11ULL, 
            0xC95AE61573CA73D6ULL, 0x867B78D83E8E1ED8ULL, 0x3D61619B058204CAULL, 0xE55E95841454E60AULL, 
            0x3DB7664944172049ULL, 0xABDC1719C2FFEF4EULL, 0x6928F89F30B20587ULL, 0xB51D9238F92AD172ULL, 
            0x4A115A738E4AE022ULL, 0xA5E8C1BEFD663E35ULL, 0x1DAF2B4D9E0C6159ULL, 0x8E3C052E65468587ULL, 
            0x79FC4B684FF9BABBULL, 0xD34E5C10D91B9657ULL, 0x4DAB86A0F1980A4DULL, 0xA833FE3A4347F6B5ULL, 
            0x1FA7135F9CFC27DBULL, 0x56CC52828DD4B8D0ULL, 0x0872A51979CBF92DULL, 0x55D5B601F28D0661ULL, 
            0x866E5D4BB56F45ACULL, 0x8084D79417238F24ULL, 0x2326A683315D0A41ULL, 0x28280240C54EA925ULL, 
            0xECC443F9334D6AC8ULL, 0x83FF4744738C1E07ULL, 0x5682A0A865A990A3ULL, 0x9B2C1158A3B16D30ULL
        },
        {
            0x6D19C3593A2E89B0ULL, 0x3A1B17343EA2F197ULL, 0xEB6C819E5FEDDFC7ULL, 0xC5F747C2313A184CULL, 
            0xF8071D415BA2860DULL, 0x553D6FFAC4599C8FULL, 0xBD754AE79BC6C818ULL, 0x53DA767661D33E46ULL, 
            0xA72EAA32C6C97E45ULL, 0x0269C914DD545E3DULL, 0x76C46C1CCA68BA41ULL, 0x2C30C0EDAA1E59AEULL, 
            0x0E6C4695AD416DEDULL, 0x5238929DBFBA9DEDULL, 0x6DD9EF4FF3EAF816ULL, 0xB8CBEAC1C13006D4ULL, 
            0xCF19D7746EF020F0ULL, 0x50AC339B2FB19050ULL, 0x7B18F3ACD42A7607ULL, 0x24A8E04562AA3A5BULL, 
            0x946243A327A94593ULL, 0xCD90A2FF03459DCDULL, 0xA545E0AACCD11CB3ULL, 0xA10AB740394F6740ULL, 
            0x08DBCBC517105F37ULL, 0xDBA21A1769ECCDB8ULL, 0x0CE8121C9D69BF26ULL, 0x9887019DA9611694ULL, 
            0x1DCC91F314D7230CULL, 0xF7873D6B038348C3ULL, 0x3B4E2292611F539EULL, 0x31CD631BBD61F223ULL
        }
    },
    {
        {
            0xB47314F2745439D5ULL, 0x3CBEA8318B4AF183ULL, 0x7B89635DA6A237F7ULL, 0xE35E96357BB2CFE7ULL, 
            0x594452C42DF30F6EULL, 0x23A2C70A9F0D1DF0ULL, 0xE7231E6EDC171248ULL, 0x982FC18B94DA7ECBULL, 
            0x553F8F25177BAB92ULL, 0x73CAF512430AD7E8ULL, 0xB632C62DE9679086ULL, 0x86EE38CF012D9CEBULL, 
            0xCDD7DAB30AD1EF48ULL, 0x0EA850B6CE672C06ULL, 0x88BF8ABACAC0C741ULL, 0xE42E2F94EE42AB9CULL, 
            0xB2FE1031FA13775DULL, 0x3489590A63455DD8ULL, 0x37A9EA9ED303E88BULL, 0x08067A6831F23442ULL, 
            0x3FE9E310E2C505FFULL, 0xF6FD6BFFDABF3FD8ULL, 0xAB7E2DEA5ACAECAEULL, 0x740B9407956A825AULL, 
            0x5F7C5D0A56F461F0ULL, 0x5E793DA6B2FEC364ULL, 0x55BC4942754B9B1EULL, 0x6682756EB1C72946ULL, 
            0xDE93DB4A837D5617ULL, 0x4331B9B3140925DDULL, 0x44E82E3AD88D0EC8ULL, 0x2328551030DD90CBULL
        },
        {
            0xFD6C59B90844F478ULL, 0x12CD561F742F5C8CULL, 0x1E6804436F895D23ULL, 0x1EB4BF769F98A2B7ULL, 
            0xF489498D2C42EEB9ULL, 0x52BFAE584747F2BFULL, 0xDADA6E91CBCC9F1AULL, 0x2D00757CCFC947CAULL, 
            0x4AD68ABE45093905ULL, 0x7541C687405878F1ULL, 0x5CA667C61F3EE3F9ULL, 0xC4968A129BA9AB9AULL, 
            0xB3A5647C57BFDE2CULL, 0x8A32D50B6BAAAABFULL, 0xD0D7FA8BF29FA8A2ULL, 0x43E305CA3AD5E543ULL, 
            0x3E0AD7F455541359ULL, 0x3B6C4FA9F2D3360CULL, 0x684384A3CCC988AEULL, 0xF7DBE5B810B56EE1ULL, 
            0x51063F25544E1E36ULL, 0xF863F9932786BBF1ULL, 0x31C04D47855726F5ULL, 0x31547735182A1FA5ULL, 
            0x4595CED2BFF6BD69ULL, 0x05DB9D61AE501C6BULL, 0x7B153709142D5F02ULL, 0x4C3B0FF4E4B61581ULL, 
            0x3E2420C62A4A850EULL, 0xC7B5BE99CC4CB595ULL, 0x3444E5B315B15914ULL, 0x7326BB6F0A9DFCD4ULL
        },
        {
            0xEC171F752F0F1B09ULL, 0xE3F1ED799E724C46ULL, 0xE5CF6B43A33CEAEAULL, 0x3366349A26C38A9BULL, 
            0x80D6C0AE1F7F9D2DULL, 0x18B9469C26680FB1ULL, 0x050890B42D4BE3C3ULL, 0x8F50AAD5E4DEB4F3ULL, 
            0x051F3F1A8CEE11D8ULL, 0x059E3CCEE5241CCCULL, 0x0C16A6306B017A68ULL, 0x5A447BB3F25616FCULL, 
            0xE89692DFA5325962ULL, 0xE2BE5531DF127FF3ULL, 0x47730C419A2AA418ULL, 0xEC885E3761E16F2FULL, 
            0x13DCE3099C514EF3ULL, 0xC272B6938EEA2B92ULL, 0x5B19D896A61A024DULL, 0xE57D70E8521BE08DULL, 
            0xBEB05076ACF7B691ULL, 0x5DB084C7BBE382C6ULL, 0x27F92C7A90EB8346ULL, 0x3CD7ECF57C02CA9AULL, 
            0x61E13A88555FC912ULL, 0xBCB670D64ED8524BULL, 0x02AD71615161DA63ULL, 0x22FF72138006CA35ULL, 
            0x80BF1AD522E258CAULL, 0x50C4CB18C9107DB2ULL, 0xD0CE766E5064B6C5ULL, 0x9AD88C5563DA2267ULL
        },
        {
            0x7D07497F24D46B92ULL, 0x77DCD0D3B84BAA9CULL, 0xFA8833AB8DA1E912ULL, 0x10D1DA3A529DDC98ULL, 
            0xB82197E4DDAD1E91ULL, 0x621572FA5B97102FULL, 0xF009A387C85DA7DFULL, 0x8703CE12462C64B3ULL, 
            0x6161F23C8F05CAA3ULL, 0xC9EFAD3907A84C41ULL, 0x828F56EE6BAA9EC2ULL, 0xA637F849CAF7BA7AULL, 
            0x2F8999C2AEEC761BULL, 0x89B18D7BB65DCAB1ULL, 0x053E81C335C3E085ULL, 0x5770B6272D9837C0ULL, 
            0x6A0A0A544B9BC0CDULL, 0xC6BFB734996FE787ULL, 0x1AB13FF009699C67ULL, 0xF22271392188E5ADULL, 
            0x129C162EB74DEA60ULL, 0x59769853CC91EC5AULL, 0xAE5CE51AFB4F89A4ULL, 0x02E97D813CE2A56DULL, 
            0xEC77277DD1A18C66ULL, 0xBE713C539D07473FULL, 0x6405DF52B886ACCCULL, 0x9651C3EEDF4EBF95ULL, 
            0x2B3417AD9045FCC6ULL, 0x73CD216FD275C792ULL, 0xC44B4FD005D46835ULL, 0x91B4EE226BAB038CULL
        },
        {
            0x17C27577F16B409FULL, 0x3F1990AA30C01B2DULL, 0xC20EDCB0E40AE4A0ULL, 0x80315752FBF848E8ULL, 
            0x3506D9E99078D86CULL, 0x61F2ECFDD2ECBA65ULL, 0xFD6DC8760FBB4F67ULL, 0x881EC4C0CC1495C0ULL, 
            0xEB7CD15F0A67D78CULL, 0x8CAA96C42D44B182ULL, 0xB552CA3C92756D44ULL, 0xB9103997EC49CCA7ULL, 
            0xD57EC07B137D73E7ULL, 0x2F64D4F11308B3D1ULL, 0x24430CCBFF6EB0F9ULL, 0x77F0D8F7B7F68E1BULL, 
            0x6DE67057EE9F7154ULL, 0x5679EC9C559A2BCBULL, 0x66404C599F8A08C4ULL, 0x3E04FAF756EFBD74ULL, 
            0x678AAF357AE2091EULL, 0xF051CECF950BA426ULL, 0x4D7B61E7392FF93DULL, 0x2EEF3111ADD3397AULL, 
            0x372600783296DAE9ULL, 0x5C417B418A9CD95AULL, 0x985E006ECEE46DC8ULL, 0x06EB5651CBB7BC9CULL, 
            0x322101118ABEB5CFULL, 0x0ED30DEAAF45FE12ULL, 0xDDAE89184C9D4EAFULL, 0x43E4CF1EBA6FDE82ULL
        },
        {
            0x36DF78F085F63737ULL, 0x2E5A3CF79E76C81DULL, 0x50C0B69EB8015693ULL, 0xC4964672B3B2E1FBULL, 
            0xE8ED920D63772CBFULL, 0x3F4B67B54791691EULL, 0xA2A1AAEA60DF9380ULL, 0x6407C7F7358C2BECULL, 
            0x159BF86134D9D602ULL, 0x569CCE556070C451ULL, 0x3DD0C4EAE1D7AFAEULL, 0xF249A123B1B04BC7ULL, 
            0x283D533D0C62B7FCULL, 0x20B6D99F23B1B806ULL, 0xA534325BBF04F3D7ULL, 0x4F5BA51584E9CF16ULL, 
            0x295BB07B9B6FEF31ULL, 0x0E60C21EA7F42223ULL, 0xAA72DAAA7D5D8B0AULL, 0x7CE12C65637ECEA9ULL, 
            0x59B871B809C49E90ULL, 0x65F42B195B467F85ULL, 0xC4192491788A2F1BULL, 0xFB513124BE2CCE25ULL, 
            0x9A4F92F5A2802B04ULL, 0x379B157DCC56BFFEULL, 0x1DC1FB745CEE19DCULL, 0x89B3066D6D3E9B61ULL, 
            0xC921482DB7A24047ULL, 0x108E7B63E57AA194ULL, 0x15D37F5F06A67FADULL, 0x913B07D1FE28FECAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseCConstants = {
    0x0CCA50A90C354D5FULL,
    0x9985091180F94C3CULL,
    0x280532FB8F7A9AD8ULL,
    0x0CCA50A90C354D5FULL,
    0x9985091180F94C3CULL,
    0x280532FB8F7A9AD8ULL,
    0xEA31EFAC47E16103ULL,
    0x0B27BEA0A0573531ULL,
    0xA8,
    0xC9,
    0x6C,
    0x78,
    0xB4,
    0xB4,
    0xA1,
    0xA4
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseDSalts = {
    {
        {
            0x0CB71BF15ACD6A89ULL, 0x39AB22570525D69DULL, 0xA40D9F0859DF8478ULL, 0x9EA8F15FF8E4C820ULL, 
            0x1EA6066683A1E9BBULL, 0x64F4975FCAE23641ULL, 0x6D5D2CC82A2D3597ULL, 0x7178465855341B66ULL, 
            0x89D3324757DC403CULL, 0x0FACAF04DF52350FULL, 0x18A679D296B01B9FULL, 0x0F78EEB68891E420ULL, 
            0xAF84ACA7BED401A3ULL, 0x704B012A76545E5CULL, 0xFA6FC615FBFF2E51ULL, 0xA20DBE11421D1D28ULL, 
            0x1F55EA1550ACF0C0ULL, 0x25295C6040EEEE01ULL, 0x246897ADEB923EFAULL, 0x2266FDCB69D98236ULL, 
            0xC2075466B2AA702CULL, 0xFF04DE1A79BC0C63ULL, 0x62DFE20DC16990DCULL, 0x80346372409897F3ULL, 
            0xE5D44B27F2756839ULL, 0x60CC459518A41F8FULL, 0x7518B84AAA517665ULL, 0x1C620260198BE184ULL, 
            0xCC623B28900EB30CULL, 0xCDEC5C56D4566236ULL, 0x799B521768A1F9BBULL, 0xAC3C96825E2784CBULL
        },
        {
            0xB49BC9AB86CBF716ULL, 0x1CAD937362DFFF6BULL, 0x98FD078E0211334CULL, 0xE8A41A7A2B0A84D8ULL, 
            0x82FF95E62F41046AULL, 0x8AEF49622B3AA6E2ULL, 0xD6B6978E7E927C5AULL, 0x335EA4D6D35E685FULL, 
            0x105E7E855ED9D8F3ULL, 0x4DE9849B07B8A5FDULL, 0xAD50DF633CC4B5D3ULL, 0x329902E5676566E9ULL, 
            0x4051EFA0DD54809EULL, 0x10CBF0A264F4B1B5ULL, 0x277B75C4F61ABBC0ULL, 0x082ADDB88198309FULL, 
            0xBA5316A7D6108DC9ULL, 0x18DF3A6D7488FA24ULL, 0x8EB637E89752AFECULL, 0xCF50F61E8EC9CA03ULL, 
            0x4052AC561F34F728ULL, 0x466248D086400E40ULL, 0xC9FF0E2E14680C7DULL, 0xB49E1C01546728FBULL, 
            0xE3ED68D79F00AE49ULL, 0xAE100AA1027794F3ULL, 0x11E8DF639060CEAFULL, 0xCC342B2BE81FC0CFULL, 
            0xFCDE473EE354CC68ULL, 0x39E8BFB23488BD39ULL, 0x7C26EB7F55C1A853ULL, 0xC1261DFE276C756BULL
        },
        {
            0x52D2AE7C273C0F00ULL, 0x1D3BA2C815DF7B6DULL, 0x78745C82156F3A34ULL, 0xD03C1CA374420143ULL, 
            0x0B10F7D202FF0F08ULL, 0x9D77D3503981AD9AULL, 0x640274315DB05154ULL, 0x2D5D351BC55C84DFULL, 
            0x1F5776EACF4304B7ULL, 0x01C32FA772D02C2DULL, 0xE99C89B0FC3182CFULL, 0x505B8D5532F22E3AULL, 
            0x5F4FB5B451462B82ULL, 0x3C69BA33BB4A021EULL, 0x144990222236C7D8ULL, 0xE6AA2941DBA7ADE6ULL, 
            0x3620C4446F41C881ULL, 0xF684B9C6B5DCF390ULL, 0xE29B1ED3006CF81DULL, 0xFFA27CB913EEC783ULL, 
            0xA2DAECC9E0D15D5AULL, 0xAC0BED29B35C1152ULL, 0x3C9B6B7F5CE20848ULL, 0x8BF4F26C049CD150ULL, 
            0x30B5A0D0DAD127A5ULL, 0xFA3BA3B35E1C308CULL, 0x935BB3DA3D3D6F35ULL, 0x21B211B3FDAEB05AULL, 
            0x9249A346BB3DC534ULL, 0x30B92DF122547ED8ULL, 0xBD5DA7633B3DF218ULL, 0xAAE00D3072DA400FULL
        },
        {
            0xAB5E3BE91253421CULL, 0xFF80A3231F1F597AULL, 0x6EEF8BE05B4796C5ULL, 0xE22620B276EAEAC3ULL, 
            0xD045FB5709E7AA2BULL, 0x915EA1EB8B539FB2ULL, 0x7DE2D9D43AFA5B85ULL, 0xA1DB8BB279B85E8AULL, 
            0x33695E2C4550684EULL, 0xF5E0966B945FB87BULL, 0xF6E7280514009060ULL, 0x52AE5FABD4129819ULL, 
            0x848123776CA77355ULL, 0x721ECAD4ADC16A5AULL, 0xFBBC47F836845B69ULL, 0xC273AA9385619823ULL, 
            0xBCE7A17F5D1DDBE6ULL, 0x34675F64348E319FULL, 0x1D004E1C83324BADULL, 0x084F17CB85ED2AAFULL, 
            0xC4E31B97D126600AULL, 0x11E908E4697F3B8DULL, 0x196945EB99CC2910ULL, 0xD28DBFEF3A0EEB37ULL, 
            0x6DCA3BE08E72CF88ULL, 0xE47ABDC953AD2EDDULL, 0xCF3AE80150E0E39FULL, 0xC80AF0142F49DBE7ULL, 
            0xEBD99DC8A7A23DB7ULL, 0x23C6401EA53F035AULL, 0xF59FBB3720137D39ULL, 0xB45B84855ACE5FB0ULL
        },
        {
            0x04E8DBA817817177ULL, 0x7E9059F644572022ULL, 0xDA657C6AF9A24097ULL, 0x2DD6B468B4F241F7ULL, 
            0x188CC6C7A03DF26AULL, 0xC97FF870C0DF8B66ULL, 0x67553DC71B307777ULL, 0x2D5FA4825BFB98B1ULL, 
            0x9A595774DFC3D4DBULL, 0xD888647891CE99F3ULL, 0x18E6831F6ED2C143ULL, 0x4F2A3BA4AE1DD95DULL, 
            0x6EDD023145369236ULL, 0x6803214BEA01AE9BULL, 0x5214D802DA2A81C4ULL, 0x68E93D64CAEF653EULL, 
            0x45174ED927D3DA5CULL, 0x98A9D8613BE9CBA2ULL, 0xA50042B8B7CADD78ULL, 0x9012BC07102633F3ULL, 
            0x39C1F74E9A24CC2FULL, 0xD48E7993761CAD55ULL, 0xFAECCA391CF92876ULL, 0xD6D67C2E6A82FD2EULL, 
            0xA6BAF8FF9FD2E3D7ULL, 0xDBF7D8A6CA9018BBULL, 0x6C3F72F3A3B406E9ULL, 0x4CD94AA53F41040BULL, 
            0x02E6D68C87BE2821ULL, 0x3D6E86A195263810ULL, 0x922455F9237A1F53ULL, 0x0DA7B40820BDF93AULL
        },
        {
            0x9DA9E3C7905B36EFULL, 0x22985FDEE3250C2BULL, 0xBF27E3A13F2B2E1AULL, 0xC5B8B27E82D6C76FULL, 
            0xE3CC9CE7339B1B00ULL, 0xFD7B3B08EBFAB1BCULL, 0x1F23566A163D21C5ULL, 0xC88E379945A004A9ULL, 
            0xA2CBBC8439F37F4EULL, 0x3D01D4254560F53EULL, 0x9714C04774371C61ULL, 0x287810D919943267ULL, 
            0x53CE8F9789FA6DFEULL, 0x94F7E81C4206A95CULL, 0x66446C19367E997FULL, 0xD8A0C63F06588D91ULL, 
            0x3E3AF4AB564B2846ULL, 0xF841098EB7F0B1B3ULL, 0x5C56FE3D2BCE8253ULL, 0xB0D5FD243A392554ULL, 
            0x4F8BDB7A1569CBE4ULL, 0xAB4D80FA7EA484BEULL, 0x3077D2F46E65CF76ULL, 0xCDA548E575E86B14ULL, 
            0x302B3385391F222BULL, 0x96BD1BBA5570A062ULL, 0x684E70A4135CCBAEULL, 0x6213628D167479E3ULL, 
            0x423333F47CBD8F0BULL, 0xE01FDF918D08B239ULL, 0xA829D7677C0C889EULL, 0x8311295D0E5DFE0AULL
        }
    },
    {
        {
            0x0D3533C7BB36DA03ULL, 0x6273F9EBC3543FEEULL, 0xB21209CE06C617A8ULL, 0xDC0469B931606CFDULL, 
            0x65AF50FF1B5B3B11ULL, 0x2F7EAD6BBB13B332ULL, 0xEB98819D39EEA1D8ULL, 0x11F964DD1C05BDB8ULL, 
            0x6822D8977C2BA4A7ULL, 0x4489AA7E542C3F75ULL, 0x5FBFA98C495638E2ULL, 0x51D1620962D8600DULL, 
            0x5452606594ACA4D7ULL, 0x2FE01476359CB8E0ULL, 0x2495BE1159A77188ULL, 0xAA1E31CDE44CE353ULL, 
            0x277B1EAABD15B25BULL, 0x6D7B2E3959EE945BULL, 0x4D27D166826FB2DFULL, 0xBEADF3E979725135ULL, 
            0x4A2AFBC3E5B594C5ULL, 0xF618DFD317217DE6ULL, 0x4DCA771AB859F316ULL, 0x1BAA83C216943C6CULL, 
            0x59112A1A870F227FULL, 0x7B08AAB0D7AD0B53ULL, 0xCC52BFC7EDB665C0ULL, 0x74CC4F2CE8E9C34BULL, 
            0x856B71ECBD767B61ULL, 0xB88055A9CAB41FE1ULL, 0x3A20817FEF20479EULL, 0x4A2B0AA3DBF6EA79ULL
        },
        {
            0xF37DCA19B233FDE0ULL, 0x42458B6905E15ABAULL, 0x92E9A21EA7DC2E7CULL, 0xC238E865A3E27140ULL, 
            0x095E576F685FA9EDULL, 0xCA27C989AF6ECDB8ULL, 0x009E936AB9AFF17AULL, 0x022D8CFD47CBE6FAULL, 
            0xACFFE528D25BD9E1ULL, 0x7A219CEF9D1B5F02ULL, 0x55A5CD0DDA98ADDBULL, 0xDD9AD0973A5A0AE6ULL, 
            0x5FB1D015F0A34CCCULL, 0x4C3BC8106993CE59ULL, 0x4DA153B7966D6CB8ULL, 0x9C1189B82DB4EBD9ULL, 
            0x606C10A3651A8FFAULL, 0x1D7F28033188B577ULL, 0x0A8F087634913155ULL, 0x157639E984565EEEULL, 
            0x483155D2B6E29F3FULL, 0xE755872D81121C74ULL, 0xC2296235EEA5916AULL, 0x0835787ECF5E3F98ULL, 
            0x9015A3B2A4B6C83FULL, 0xD136BC5CDEEE870CULL, 0x0087E53B863B2681ULL, 0x2151BBFBAB17609EULL, 
            0xA4114EFA6A919B84ULL, 0x0CF1F4C84E074B3FULL, 0x8872D7F05479B347ULL, 0xB7520397E7BC9CE8ULL
        },
        {
            0xB92FA289FA4B01D2ULL, 0xB2F46376F6571236ULL, 0x471963B0A704C1B4ULL, 0x6C093777C0F65BBFULL, 
            0xD25642F3DC933853ULL, 0x86F6C788D465D48CULL, 0xF17AABB622468E71ULL, 0xC14F225C18BA3AF2ULL, 
            0x9AC980DDC940BC15ULL, 0x42203A92E8049234ULL, 0xE62B288F9BC9285BULL, 0x044C09832A43A10AULL, 
            0x307301E4A54F9FD1ULL, 0xCF7A87D3C5771B48ULL, 0xF67F1E4BEA2A0C7AULL, 0x2123831C78B8DA39ULL, 
            0xC6BC6BAAEA59EE80ULL, 0xAF87F12E55CCC883ULL, 0x49A287DA6C73488DULL, 0xC0CDFBE86B84BDCCULL, 
            0x964940A3A117DF15ULL, 0x96B7A9A45C0086AAULL, 0xD7061B64F3DB2365ULL, 0xAB9380B38056AF92ULL, 
            0x506E17C68331554FULL, 0x32853B3621FFB6BFULL, 0x1B51B6253A6C169CULL, 0x46CC6118B4A12E3DULL, 
            0x4F623191BC788F44ULL, 0x7210B2AAEB2D87E7ULL, 0x4FC05CECE3DCE3A9ULL, 0xC4B1DEEFA58B7A8EULL
        },
        {
            0x0B9574C707FE776BULL, 0x2486D984F2F72AC3ULL, 0x7D129F92DA1B81F3ULL, 0x878A8BD776379A63ULL, 
            0x5ACD65D03A2EB30DULL, 0x262C2B721E6D4E02ULL, 0x4F9414C392EEEFE9ULL, 0xAC954A1184A4B990ULL, 
            0x307B5006EA309F55ULL, 0x0590AD4E83E0D5DEULL, 0x2C742F4CA2C1D76DULL, 0x15C2B9F685AE8F79ULL, 
            0xD7D4E66F986E0CE7ULL, 0xB983EEEFEF7DDDD1ULL, 0x914DC13025280D8DULL, 0x400077739BEAD95AULL, 
            0x17B9F704198DFB52ULL, 0x5DD7E961C0E7D283ULL, 0x3D1CE0F269EAFDBAULL, 0x1F4BAF4F86CC4A4BULL, 
            0x34B9DF5967EDE09CULL, 0x75BBB0F1174AA332ULL, 0x0C31434F40CA14AAULL, 0xC87A8DFEE76505FAULL, 
            0xCA7563012C182A70ULL, 0x350754B77C81A546ULL, 0xC969BD2D9A06DD9BULL, 0xBAF28A4FC774799EULL, 
            0x180A9AC4FDD5D095ULL, 0x82FE110EE267E7FCULL, 0xA815DF94DDE75DD4ULL, 0x51EDB6E5A43BAA75ULL
        },
        {
            0x544F9127CE93B86DULL, 0x27AEF9AC59A53CC4ULL, 0x1C93FB5CB810BC64ULL, 0x04DAA44BC4C4F759ULL, 
            0xFA46457E35CDFA07ULL, 0x5D15A3B14A3D4D5FULL, 0x4333DE37BD5AC248ULL, 0xF0D8209231113696ULL, 
            0x5EA03D60CB4CAEBDULL, 0xF54C174FC63D6C4EULL, 0x6737E27B9A94325BULL, 0x54629D4F78C67368ULL, 
            0x0C8D7FFA94C7C947ULL, 0xDA0C7648291A7E65ULL, 0x0E6208F6D8CDEB11ULL, 0x1A9A4E14EEEB25F9ULL, 
            0xE2914145166F0EACULL, 0xFC706146ACE85031ULL, 0xCD8C33395120AD7BULL, 0x8BB25D1ACE4C9F2FULL, 
            0xFA485621D237B843ULL, 0x01C0AAB4C1D08346ULL, 0x6D508C42DB1D93B3ULL, 0x0BCF51E5789C5757ULL, 
            0x308F450AD4DA116EULL, 0xFC78AB19EB393830ULL, 0x1BFCEB0C264D6C5AULL, 0x37F8F55AF24CDE1CULL, 
            0x936A4969938BFFF3ULL, 0xA2737C5BDC6352CBULL, 0xE9B8F29B865BC3B9ULL, 0x28BF0FB85F2E85AFULL
        },
        {
            0x4CC1BAE985B1B7ACULL, 0x83F39BB605ED5B0EULL, 0x3129543E2043FF33ULL, 0xB2A9237584D57BA8ULL, 
            0x92C3620B2AFECCA5ULL, 0xC0ECAEE78936B8C0ULL, 0x69F472E5BD203640ULL, 0xC56673490ACDE12EULL, 
            0x9E29D832734A920AULL, 0x79D94933A9BDFC2BULL, 0xBC6229D2E9163C2CULL, 0xD2C89C0E082F1F4EULL, 
            0x5864963FD2A1BD1AULL, 0x359112F379F7F7A5ULL, 0xBFC841DD09266B15ULL, 0x314BA7B11421D894ULL, 
            0x224509285E4C40A3ULL, 0xB58FEFDC44DE7515ULL, 0x8BFEAA99BFA8B682ULL, 0x533E9F8B1BCE58C9ULL, 
            0x7E892B04A696A089ULL, 0xB840EDDA770A0AE9ULL, 0xE6CE8A9B2279C1F5ULL, 0xC0557E925B20A2C4ULL, 
            0x80C9852564483CBAULL, 0xFF50B0B7372112A9ULL, 0x7A647EE4FD5C241CULL, 0x9FA7AB9BA3A35E15ULL, 
            0xA5F630778B228ED7ULL, 0x4F42AE7D0391E17DULL, 0x85DDF4F23F87876CULL, 0xE0FC8E8058ABB0CBULL
        }
    },
    {
        {
            0xC6BFEFC9428748ABULL, 0x79322B2CF43797FAULL, 0x60E52D95D3A9AAA7ULL, 0xC9F84EA7AF0A0ACCULL, 
            0x9641DEC7E5C606FCULL, 0x0791F5FC8837A8DFULL, 0x2D24435C9E865023ULL, 0xE0FFBB94195B3F89ULL, 
            0xCE8578C84A8722D1ULL, 0x93F25E9616D50986ULL, 0x4C0406D4C7A37DD2ULL, 0x5681BD334C8C21B4ULL, 
            0x1749813DF49B5973ULL, 0x8FF98B9E83ECB515ULL, 0xBD9CC5BD284A11E4ULL, 0xA137396FCD1F4787ULL, 
            0x2353E45C872C8AB8ULL, 0x55003B9590223661ULL, 0x3D9409D9F81A760EULL, 0x44410CB244E15817ULL, 
            0x683C728DCCEF9D79ULL, 0x5F29DAFFE1FA235CULL, 0xC3546FDF805152C4ULL, 0xA49A0C279AC30F88ULL, 
            0xF0B69C48F286C475ULL, 0x4DF2AB733DF0F4BAULL, 0x7EFDBF026D701520ULL, 0x6887BCA968521B79ULL, 
            0x99FCF517890C0604ULL, 0xE923390A04706536ULL, 0x2FB7E846E6EE6A93ULL, 0x3FB3C70EEE440F47ULL
        },
        {
            0xFE758EE3F54F08B3ULL, 0xE7F4DA7A8144F213ULL, 0x83936409E25DC64FULL, 0x6D29218E3413BF7FULL, 
            0x6E9B7A2B88F2589DULL, 0xD63F44ACD66356A4ULL, 0x1D4C1A9013930AAEULL, 0x55C6994B2E18807FULL, 
            0x8D71BAD901A52612ULL, 0x58F004E81A0FAA43ULL, 0xDD940CD3C299EC49ULL, 0xEBF7200C1614EED4ULL, 
            0x023F77D7E11AA278ULL, 0xE396712B919A87B7ULL, 0x2E9D84F2B23C647AULL, 0xC1AE70291D0D3433ULL, 
            0xDD84E2A676789D01ULL, 0xAC3684AD645E82F5ULL, 0x697CDD6C5069A0C7ULL, 0xBB0CDC0FC16C6B76ULL, 
            0x0587FE6DDCB3D9E3ULL, 0xE4067C6F503E71DCULL, 0x67DCB03417D0B564ULL, 0xCB390D153EB2C31DULL, 
            0x821F80663117B775ULL, 0x0AEC140FF1B3E133ULL, 0xFF74962DC7D008C9ULL, 0xFA6CE7F069602A60ULL, 
            0x055E958A2AE80EC2ULL, 0x98F94E01544E5597ULL, 0x4EEC123FD0293947ULL, 0xFC3B9A4BC56D2341ULL
        },
        {
            0x7B3D7ADC13428B2EULL, 0xF6A3B5F4644499B5ULL, 0x90959A947ADE6F2BULL, 0xADC9CD81959297BCULL, 
            0xD91E90D059492B8FULL, 0x99AAD900AACD7A0CULL, 0xED7766260D55A0DCULL, 0x2B8D6C45169BA2EFULL, 
            0x6260CF133A298B83ULL, 0xDA2383BAC9290342ULL, 0xB2A9E8D4E8053C24ULL, 0x2B7A3CD57F592218ULL, 
            0x3DA5BB043DC38FE9ULL, 0xAB0C76E7725EA257ULL, 0x4CBCED0BA724FD27ULL, 0x3FE3ECC567198DCCULL, 
            0x6F5204B81731A18CULL, 0xD41778578F737161ULL, 0x52DC50A16AC10644ULL, 0x9427EBD65BDB6EB9ULL, 
            0xF1E397AF67F30EDCULL, 0xC166AD73CECCF6EAULL, 0x885EE97051AA405BULL, 0xD5CB4ECF885FB37FULL, 
            0x8FCA5C7110F951A5ULL, 0xB8CAC71BDC8677D4ULL, 0xDEE8AB46750EC90CULL, 0x83AD3C3BFA7EBB70ULL, 
            0x54B642C15AA22081ULL, 0x4ADD6F383C2C7972ULL, 0x69D5CDCFA5ED7929ULL, 0xC7417C8B12AF9ED1ULL
        },
        {
            0x227C5FAB506C37ABULL, 0x2141D8E61DF9554DULL, 0x0FE2CD3906917BCAULL, 0xFB7ECFEFE9626804ULL, 
            0xC6E496AC46B6833EULL, 0xD089B3CDF6D9B2B5ULL, 0x5D11F1E4B6ED4250ULL, 0x927DFB4631EF6BC0ULL, 
            0xC5DD2DD1DC9AD21CULL, 0x88FCE1B966E4C983ULL, 0x9252E0E7BA50268CULL, 0x793F4A8880365F83ULL, 
            0xA472510224A55C48ULL, 0xC9D73A17C1A116D2ULL, 0x4BDCD2287A918FB9ULL, 0x7A698510C217E9DBULL, 
            0xD4EF980421A8DD6AULL, 0x14AE567453F2A37FULL, 0xBFCDF689C15EB923ULL, 0x3EEA8E2A10D2A54DULL, 
            0xE87F27556F53C4DFULL, 0x87D6AEDF7C43D02EULL, 0xC685652281C7C23DULL, 0xD6C8E446133AB0E0ULL, 
            0x40A49525CEA5A6A3ULL, 0x201AB558CBAFF622ULL, 0xD88AB03A3A2E737AULL, 0xBFBB757CFFD8018DULL, 
            0xF180B759E3C82041ULL, 0x3FFDA4B59D942399ULL, 0xDCD1FE3D47202C03ULL, 0x00BA215FE176AC8BULL
        },
        {
            0x63B4486C998A4491ULL, 0x16CB5AEC4C0CA25FULL, 0x6B0902D52F01802DULL, 0xF7945696BC3F786DULL, 
            0x945FF3A8A7439A25ULL, 0xEF0E487EE790043EULL, 0xDBFB185F261729A5ULL, 0x754CCBFA2982F13DULL, 
            0x074749DE55DD5CB0ULL, 0x88BA478D43570204ULL, 0x70DFAB84EC94CA52ULL, 0x13DE5AF211722993ULL, 
            0x74C550B3D5638B5AULL, 0xE423433ADCC13324ULL, 0x537AAF07F7F8C155ULL, 0x117CF03BFAAB3194ULL, 
            0x811D429850418118ULL, 0x49973F8A6B05345DULL, 0x5D2C5144EF74D31DULL, 0xD40EDEE52A1FCF97ULL, 
            0x2175A96315F0E75FULL, 0xB9DA60B6957F2AC1ULL, 0xB83482E776FCCA03ULL, 0x1D2D2B8C80FB24D6ULL, 
            0xA84D38F06AE68FEBULL, 0x8245E0C53CE6F185ULL, 0xC7E2ECA3EE1A7125ULL, 0xA08F962A27F10749ULL, 
            0xD1AC6BAF5D00C359ULL, 0x60AE74910164E3B9ULL, 0xC3A252C09D626F89ULL, 0xDBD488AD43C0108EULL
        },
        {
            0x47D5101763467CA7ULL, 0x5062C090B48842D5ULL, 0x0A43CA2EC39B80E8ULL, 0xE24AF3A302C1A9F0ULL, 
            0x8004F8CA7413C4ACULL, 0xE8F41D31ADDE660BULL, 0x129890617CEB55F7ULL, 0xE767580BCBBE5C5FULL, 
            0xA4F986C1497B5453ULL, 0xE7C8A2FA6A050973ULL, 0x64200EB0E95B3E64ULL, 0xF0E409F8337DCE54ULL, 
            0xFC6BC49518CDA27CULL, 0x116313B2A53F6222ULL, 0x503167D44A162855ULL, 0x0BCD004AFF46E68EULL, 
            0xF3DBBE87BD293A06ULL, 0x144249A25E730153ULL, 0xD70A729A003B5F36ULL, 0x8FA606E387ED261EULL, 
            0x49C7CE5C041E9DF5ULL, 0xA1113D61C6C198EBULL, 0xB8ED3E09E32B056AULL, 0xAEB0E8716382C67EULL, 
            0x41DB83C4E2060264ULL, 0x45153C9BB340270CULL, 0x9692BEBC139EB03AULL, 0xAE822C216FC77E07ULL, 
            0x918369D08F9656CAULL, 0x397E5C4A48B8B378ULL, 0xE513FAA92D35B40EULL, 0x3569C5EE04C05E02ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseDConstants = {
    0x707C38BC3DD04A9EULL,
    0x49F53575362E54E3ULL,
    0x516223D42BC990FDULL,
    0x707C38BC3DD04A9EULL,
    0x49F53575362E54E3ULL,
    0x516223D42BC990FDULL,
    0x9F7F5603945B4539ULL,
    0xDAEA4205177BCD6DULL,
    0x23,
    0xC5,
    0xB4,
    0xF8,
    0x6D,
    0xCB,
    0xA2,
    0x13
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseESalts = {
    {
        {
            0x7B656AA7D61183EFULL, 0x643398BE5CB8B101ULL, 0x253735E561837E1EULL, 0x9447C277ACDFB350ULL, 
            0xF250186DA0E0F372ULL, 0x53DF3527ECD23459ULL, 0xA3E21293E7985977ULL, 0xDBEE77236A327E5FULL, 
            0x7E4DAA316B25B7D0ULL, 0x76DBC58967D109B9ULL, 0xD6CBBC2019F75D48ULL, 0x939183E7A04149CCULL, 
            0x827A5B334F9B57E9ULL, 0x2C5B2B2A4273B550ULL, 0x0DB205B7DBCDA9DDULL, 0x751B8DB19D0FC262ULL, 
            0x452F4082514FECD4ULL, 0x02AEFAC33419808FULL, 0xFB2B3411C801A441ULL, 0xD85AD6AFD6438383ULL, 
            0xB5D5BFBDDA20F240ULL, 0xC7334DE99A7048BCULL, 0xAC95F0E1A2F052ECULL, 0x306AE20BEB093220ULL, 
            0x4FEA8DE9BC813BD7ULL, 0x2D79FD680D90461FULL, 0x2DA71DDFDC1EF01EULL, 0x4E0B6DCB81DFD847ULL, 
            0xA416D0D8CF796F64ULL, 0x8DA0D8302B834017ULL, 0x988CFB37717339E9ULL, 0x345166F519F9F2EAULL
        },
        {
            0x60CFD571E0AC930EULL, 0xB5DF6B86130B5D82ULL, 0x1AE7DC17E67EAAC7ULL, 0x391EAAC8992636EAULL, 
            0xD4C6D0B3D1D47CA4ULL, 0x1F802CC50B9F470EULL, 0x8B02E010BCC7E850ULL, 0x7A0B1BA1B879D674ULL, 
            0x231139896FA374BCULL, 0x55FF7325478D8745ULL, 0x0BB6604DE17C987FULL, 0x3D462E719B8369C7ULL, 
            0xCF0A40EA2F636240ULL, 0xCFF134C25BD21794ULL, 0x902FD85B4D09519AULL, 0x186097F2642F09D3ULL, 
            0x2E6508D1974DEB71ULL, 0xC9EBFAB8C63ED324ULL, 0x912014EB7CE274D3ULL, 0x1BD3545B6F13CFDDULL, 
            0xC05863FED65B999BULL, 0xE293A432C39061E7ULL, 0x53494E8A02155D15ULL, 0xA49A4A32D43EF043ULL, 
            0x2D9FE5815B4F4C16ULL, 0xF1FD24E27164037BULL, 0xDDD3B00A9BFC3060ULL, 0x0558F38AACCF3A68ULL, 
            0x9902D1A972B21ADEULL, 0xB9B31F5BB2000176ULL, 0xFA9B64EFEB9D5BE0ULL, 0x9E41BEC9B49CFB18ULL
        },
        {
            0xA16C99D192E350F0ULL, 0x36E99EE877D3788EULL, 0x795AC047176241B0ULL, 0xB678382BB7E118B4ULL, 
            0x2F7373B7A75E85CEULL, 0x17D2B91AFD050F57ULL, 0x81EA4836E3BDB0F0ULL, 0x611EFA5ECDFA5A5BULL, 
            0x1D77B973F6FBEE6EULL, 0xA9FDB21322655167ULL, 0xEC77C58D7DE7FBCFULL, 0xADC03D3E5DF5BDF2ULL, 
            0xD295A1B6B1B54BD7ULL, 0xAC71920D19FF23E0ULL, 0x4697BB91644FF18AULL, 0xB5802BEE2FD70857ULL, 
            0x1E7C5D704F53618FULL, 0x09958428989A27B1ULL, 0x3172976F7A6D6A42ULL, 0x9E21647A488EF6D5ULL, 
            0x21EE35D6B7041EC6ULL, 0x289ECAA8ED2367BAULL, 0x46E3F7CC2F1C86B6ULL, 0x990A033A8DCF9CB8ULL, 
            0xD44C85FA1EA4FC88ULL, 0x4ED63EA23348BB14ULL, 0x7D0FB23E8549886FULL, 0x3E9325A3746F8E34ULL, 
            0x3F3DD12655536F3DULL, 0xD3F0CB1B0EE74F9AULL, 0x4246B8BD8DF1A161ULL, 0x9F863EF9EF51B3DEULL
        },
        {
            0xA9D6A616B6504E92ULL, 0xB108E5AE0F8A62B5ULL, 0x19BF5E3E2211A949ULL, 0xF1FD61EA45132952ULL, 
            0x186C1A473152E3F4ULL, 0x7DE5F9CC62162FAEULL, 0xAD28D8144F2355B3ULL, 0x27B5742A7C2F5FCBULL, 
            0x6AE7B88BC610F589ULL, 0x838893FF6BD01149ULL, 0xB85F160B083F6E90ULL, 0xCECABD4E548232C8ULL, 
            0xEC553739FDAEA564ULL, 0xEDD8F98A7716D494ULL, 0x4D76D5AF6D25F07CULL, 0xC6A60A0716A94BBEULL, 
            0x7DC2D498892F65AEULL, 0x527CCAE136199704ULL, 0x9E933AC139D34AD0ULL, 0xA1B88A1966149A14ULL, 
            0x142969D9EBA24DC1ULL, 0xFB1FF730DA5C507CULL, 0xB07120190419A0E7ULL, 0x4C881BE5F894AD20ULL, 
            0x37360D79C40500E0ULL, 0x28F8D420C307CEB8ULL, 0x5B217A8CE3825A11ULL, 0x77B8C5695AE1513AULL, 
            0x0F2A0C7405B867BCULL, 0x7DEAF869A2FC4AA5ULL, 0x693271731D1ECE9BULL, 0x0ABBABE6856FD59BULL
        },
        {
            0x5EA45844ED86FA74ULL, 0xA9FAFC088ADF6CE1ULL, 0x33BC34FFBC31B928ULL, 0x7F9C0392E1A0125FULL, 
            0xC125EC3B264CE1CEULL, 0xA4BAB8302ECFDA25ULL, 0xE2ECA336CA1A1407ULL, 0xF08DBD5998720E31ULL, 
            0x2CB65C0BBC54C8F8ULL, 0xA58DF47918FFC9A5ULL, 0x3708F11D4D76C2D0ULL, 0xA4118FD17091FF10ULL, 
            0x9468246B84920C8FULL, 0x0BBC03419156F511ULL, 0x79172AFA0FFAF8B4ULL, 0x3623F6E9918EEF52ULL, 
            0x2FDEC6B0BB1DDF1EULL, 0x9B7D26B2CB09330AULL, 0x7F77B3907935232AULL, 0x2436BC4380EF4571ULL, 
            0x620C62F3337BA6B6ULL, 0xDEBB1FAA32DCA3C6ULL, 0x461B2A34EA3E206DULL, 0x64B8A2CE9C49BA76ULL, 
            0x7F4509BE25D67BEEULL, 0x7B5F59DF6B51F200ULL, 0x2D6D1ED0F7ADEA6AULL, 0x9B19F3F96A88AE25ULL, 
            0x825FF02FF9382FE9ULL, 0x6BD00E46C11DA085ULL, 0x9D5BD57D60AA365FULL, 0xC75F42FA148C8657ULL
        },
        {
            0x8F19B69A2C6C50BEULL, 0x2828DE50361C3934ULL, 0x45145442852BB3FCULL, 0xAFD3B654D39C7FB5ULL, 
            0x935738441E80C5FBULL, 0xA00BF0359DB1F3C0ULL, 0xAD19123FC749C7CCULL, 0x2B72CE72D6189966ULL, 
            0x2FB344BFF43F7351ULL, 0x17AB4EDCA5DB407CULL, 0x8F84DCBB087B2605ULL, 0xADA22D778A1FC3E1ULL, 
            0x7A8B68526B22CD29ULL, 0x9CBC959DF6B2D084ULL, 0x78335BAB64A09632ULL, 0x1F05FA517F3A4BD2ULL, 
            0x40D16748229D37F9ULL, 0xAC60DC39D3A480C2ULL, 0x3892AF80EBBACD1EULL, 0xF4B9E73C3F9E1CAFULL, 
            0x83DE87AFC7092208ULL, 0xF88A4D2AB4501049ULL, 0x7B81AECDFD04E125ULL, 0x402994290ADD5B58ULL, 
            0x90C5F1E49D8C0B2AULL, 0x3664E384F7368EF2ULL, 0x7D5460079C4FA27BULL, 0x53A144DAF930222FULL, 
            0x948AC49CFB4068D9ULL, 0xFEC1A1FD3EDFF235ULL, 0x5477727F32B5B9C1ULL, 0x495BF11D9F0A4F8DULL
        }
    },
    {
        {
            0x7D4C9E5433425C53ULL, 0x82AB217470099118ULL, 0x3DE45B25EDA489CBULL, 0x5F8D9375D6AA8FB0ULL, 
            0xE89B14547786D2BEULL, 0xD7E9A364DE33DA88ULL, 0x338E44D40B3BAECEULL, 0xDC89BAD0E222CD59ULL, 
            0xB6F6B8FDEED08A30ULL, 0xAACC3756568EB387ULL, 0xFA67FCB43D703251ULL, 0x9F33D4575C00FA3AULL, 
            0x4C9A23D53AA5254AULL, 0x6D423F92750D89B7ULL, 0xF85FD6AE60A160A1ULL, 0x18816BFEF4C290DCULL, 
            0x3628CD62CBE67414ULL, 0x3BB8A2526B55A476ULL, 0x948662F2510D3FB1ULL, 0x02BF8E0D193B811BULL, 
            0xA25921022D38B052ULL, 0xFDF24167AB8F833EULL, 0x816CD08C6A1FD228ULL, 0x2E6A0A6A45B959AFULL, 
            0xAE6210F282E48AABULL, 0x0086FB52F88E254DULL, 0xA971831C6F2AFD18ULL, 0x0F68B0A261805C84ULL, 
            0xF45CD5D62A43E6EDULL, 0x0945E5947A3EFAA6ULL, 0x079F7C05D0F40322ULL, 0x46358243A0F0026EULL
        },
        {
            0x7A00443A0D4CC058ULL, 0x8E64FB5A1DE0EC19ULL, 0xCFFD29DE4B8F26C3ULL, 0x928918D9D0351769ULL, 
            0x9A3C13A742C47E02ULL, 0x1C90C7EC08AD9C6FULL, 0x6E9B7F0D296222B4ULL, 0x0C9F612D33CF6BB9ULL, 
            0xA4F43C3625498F7DULL, 0x46CDE805AC058FE7ULL, 0x4C94BDF69A49F84AULL, 0x7A330B83F9AF2454ULL, 
            0x44656A34EF50A9AEULL, 0xBFDACB2FF071EF9FULL, 0xF9B04DDB5D14A2EEULL, 0x47820DF306C46513ULL, 
            0xDD6574C84F95823BULL, 0x1ADCD8C81D752BB6ULL, 0x4BF62FE7F9AB7A55ULL, 0x5CEE526990015A82ULL, 
            0xE8F732C837F3431FULL, 0xB033DE9BF9C8E0E0ULL, 0x8D4D1B5556D83FF7ULL, 0x68B7D5C07DDCCF90ULL, 
            0xAAE4CDB7F0139FF6ULL, 0x305F4C9AE1368715ULL, 0x86D9515D201E963CULL, 0xE4BB8C0F3C391969ULL, 
            0x522E8F9C30DCDAD3ULL, 0xBF61A584A6BD7873ULL, 0x9128EA8095737397ULL, 0x91F329A0B7531342ULL
        },
        {
            0xF3F72562411AB816ULL, 0x8D8CCB781F88CEC8ULL, 0x156A995BD00FCC5BULL, 0xCB6816F621F4EAB3ULL, 
            0x4D55B53DF6679860ULL, 0xFCACE7385D26550CULL, 0xC827D2806646EDB7ULL, 0x3C0C20FAF9B58FB8ULL, 
            0xF7EDE464CBADFFDFULL, 0xE250B8F0444D6BECULL, 0xE2FB7664946A3255ULL, 0x72B0DCFD787432B6ULL, 
            0xB9F70DE70AC28EF4ULL, 0x6F6F1AC379F22DFDULL, 0x511599D17013137EULL, 0x63E9D03365183872ULL, 
            0xC1FA56DEB81D2FD6ULL, 0xC4302912600FC438ULL, 0x006CC5A0C64B4C71ULL, 0x59B8068480C013CAULL, 
            0x234A9046C7FE825AULL, 0x55726877B85558B9ULL, 0xB77B6FE10B327A61ULL, 0x9C5A279DF53D9D9CULL, 
            0xF716C2E3E81B536CULL, 0x583E318E5F8EA554ULL, 0xCEC2D801A4FF458FULL, 0xF7D02229F5682341ULL, 
            0xFBA08C6F1CBB2AE3ULL, 0xE1894982CA0924EDULL, 0xA3CC2C85D91E15B8ULL, 0x3A0191CF4284E532ULL
        },
        {
            0x2E9E4062CAD05BDFULL, 0xF351D82420FFA2B5ULL, 0x9E786C7192FAA608ULL, 0x2E04CDAAB0B83FD7ULL, 
            0x9DEA34494CAF4F18ULL, 0xFCBBB75ABE05DE98ULL, 0xA53691AA0A44E2CDULL, 0x1AB94D1ABFC656ACULL, 
            0x7DBD854DED8C5EDFULL, 0x7B711526A2260374ULL, 0xFB007E3015442064ULL, 0x33F79978A1771A04ULL, 
            0x420227BBFFEAE440ULL, 0x9681ADBF5948ABB0ULL, 0xEF087F4BA0BB9CEBULL, 0xAD1ED0E8FE0ED4A6ULL, 
            0x8C288686B08720BCULL, 0x20522DE67CFA2B9DULL, 0xDBD7E15D5DED1F58ULL, 0x1C47411D67F44C9CULL, 
            0x84305DEBC7153D65ULL, 0x763C426CB0FF9618ULL, 0xBE4735D27CC0DC15ULL, 0x7512024CFFF0C02AULL, 
            0x93247550D84CDAECULL, 0xB59DA3CC5CF5D58FULL, 0xBFF9AFFD6141B68AULL, 0x02634BD1B43EA04DULL, 
            0x430E79245E1F64DDULL, 0x6E702E220CAE03DFULL, 0xC2C6DE1F1C9F55BCULL, 0x9347079C9AD8E0A9ULL
        },
        {
            0xCC3BA49727B9D495ULL, 0x6F14CFF3F15341AAULL, 0x78847CFC82B95788ULL, 0x767E7D65B938C033ULL, 
            0x30813ADE385E5F6DULL, 0xABE6F67C91C72EC0ULL, 0x3EE7EC90D919678AULL, 0xCE0DC605A8A6BA63ULL, 
            0x0DFA990576995B87ULL, 0x648BAEC5BF7CA4EAULL, 0x8441599F2588A83DULL, 0x33B495CD5B4B25E9ULL, 
            0x27DB48BF42061B25ULL, 0xF4044A0D3E7792B2ULL, 0x9B81588D9E9B96EFULL, 0xB847EE96DBFD6441ULL, 
            0x1E3ECDF2D50C7049ULL, 0xBCB1C2310A744CA5ULL, 0xC582D6D7DC4796C1ULL, 0x0466FEDFB82B5D29ULL, 
            0x2233BE6FE2B04E0AULL, 0x02A583C0AAE5ED64ULL, 0x0D4844BA3540A899ULL, 0x1DC97343B3C292DEULL, 
            0x06310DA02DC09A50ULL, 0x621B53DAF112875FULL, 0xAE6AFEB1906338EFULL, 0x0355E0E8D0A2A2D8ULL, 
            0x417C0BA47A5CF4ECULL, 0x7A65E19041D4CB5BULL, 0xD3CD212FE3CE23F6ULL, 0xA955A5538B5D2194ULL
        },
        {
            0x8C114336A98BE928ULL, 0x2C88612630D1924EULL, 0x94A4AA21347B481BULL, 0x43066B129F8F8DFDULL, 
            0x2026CCF0DDDDD043ULL, 0xE5280DEDEF41BB12ULL, 0xFD37D9B3A6F3C321ULL, 0x4F4C799403131C50ULL, 
            0x17E1E7847390496FULL, 0xB4B0BC005D80F82CULL, 0x9573FEEE58BF5172ULL, 0x292CBE17B5A0FC41ULL, 
            0x6F2CA82AC2017AB7ULL, 0x47CBDADCF241E669ULL, 0x78194BF9D44583ECULL, 0x402CD7F443A7D383ULL, 
            0xF33B6B0B2AD62C04ULL, 0x9FD7C819A442418EULL, 0x8619B7F45B9B55D4ULL, 0x5171FFC7277E890AULL, 
            0x688D0907DD68BD1EULL, 0x8E253EA962FE8C48ULL, 0xF45E9F922A21DDCDULL, 0x73CE97811B7C04E3ULL, 
            0x336A2EBF5CC6694AULL, 0x009DC9A49F33A016ULL, 0xCABB747E1250DAF1ULL, 0x33E7D322BCF26A8EULL, 
            0x3D50AE16883AA817ULL, 0x9D94CB44511DCC48ULL, 0x63AF1574237F8B5FULL, 0x067BC54B20E9F737ULL
        }
    },
    {
        {
            0xDAF80CCC8706878DULL, 0xF6ED370BA31C20BFULL, 0x5B265225D28DE0EAULL, 0xD174B1083FC7DDE7ULL, 
            0x018C66CBE2849953ULL, 0xFD18D857B2C70E10ULL, 0xA3933AF2A672C279ULL, 0x94CE3517BFFBA311ULL, 
            0xD8D75997D7B3EAAAULL, 0xE1EE6EA6DB69AA5EULL, 0x47A0074AA862D166ULL, 0xED932763ACE3404DULL, 
            0x5819AC86AAD7F11EULL, 0x9368F7B2B099749AULL, 0xFD839CC5366A9967ULL, 0xAE1553C092E15A0DULL, 
            0xF5996E365894A797ULL, 0x54C413A35770362CULL, 0xF5ECBD7E82699849ULL, 0x9A92DCE596722164ULL, 
            0x7203A00873956153ULL, 0xD71C6C2464424F67ULL, 0xDE8D1148EBAA47F2ULL, 0x4A10FFFC195ED644ULL, 
            0x75BAE9217E3FC433ULL, 0x121A07EBD6474AADULL, 0xE852ED8A6BD689B8ULL, 0xE3A15BAB17CC0C9BULL, 
            0x8ADE6E146AE86F7BULL, 0xA989E70823EE702BULL, 0xDDC30E8636EE5622ULL, 0x3B523EE7B4636CFAULL
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
        },
        {
            0x4D125330CED139A5ULL, 0x22DE495AD0C9B931ULL, 0x40BCE04327713C24ULL, 0xA8325E9CF93F929DULL, 
            0x0F234C7549BF9BF4ULL, 0xD527F66BB65BC7ADULL, 0x2D0BD29E0F50BE68ULL, 0x5BC349D1D90950C1ULL, 
            0x7AB9B523ACAD038EULL, 0x43933AA94CD7A409ULL, 0xA19BE2A06C7D5C6BULL, 0x6159906B10FF1020ULL, 
            0x7C1F412CE53AF8AAULL, 0xFF400AF19727DC26ULL, 0xF80738D09A00C37DULL, 0x9488798D19530097ULL, 
            0x81FA50E55A392A1EULL, 0x1F500155C49A8AD1ULL, 0x82486B4A120752FCULL, 0xB8285E447CFAA948ULL, 
            0x36FF283F63A579DCULL, 0x08C479E39DDE9E7CULL, 0xC077729321D275AFULL, 0xD9E5609B1211FB77ULL, 
            0x809A6201B6375A23ULL, 0x7B62372CFAD0A82FULL, 0x34E70EEC8D846794ULL, 0x651439CE99E38447ULL, 
            0xBFF6C0B4F666C726ULL, 0x164B6A58D23C9260ULL, 0x35B8401A3AC65051ULL, 0xF7975E4B1BA93A9AULL
        },
        {
            0xCCA6011391D447CAULL, 0xE4517672619C6A2BULL, 0x9631F6790C884E51ULL, 0x9B6386C062967068ULL, 
            0x18ED1E146FE0353FULL, 0x49AF7764EFECBFB1ULL, 0xEEACEC11C9DC713AULL, 0x239C758B46DFAD6DULL, 
            0x2BD62300A4EE909FULL, 0x7D68B42C0ABD8A1AULL, 0x0A7290CCBFD0EA9AULL, 0xCFD0F5029D22FE16ULL, 
            0x320EEC0BCB36A05AULL, 0x21B84485041FCB3AULL, 0xC3C3709EEA2AA998ULL, 0x8C96361018CF0475ULL, 
            0x64A704E289A3AB9EULL, 0x759595B4E0B60160ULL, 0xA7A95354220886DEULL, 0xFB8C010C030C8085ULL, 
            0x1B47E06A448CE9C5ULL, 0x4442BE0D9022CCFBULL, 0xB123D8FC121F617BULL, 0xB0D0A241F67C3667ULL, 
            0x1B4143BF3235F4EBULL, 0x66CBD94101997B65ULL, 0x36D10B78BEEA2E56ULL, 0x5F84AE6D7729A92DULL, 
            0x30CCA611A8B74059ULL, 0x5A4E98B2AC616E73ULL, 0xF96FA6E875E37B99ULL, 0x8297D8F8DE1E6FEFULL
        },
        {
            0xD13628D55641A004ULL, 0x19B4C58177DFF1A5ULL, 0xC32B79E30322A24BULL, 0xDF69E6D00B7B4A74ULL, 
            0x73D98AF01FB462E4ULL, 0xBF88217308B43760ULL, 0xEE426E0115CC755BULL, 0x8145F5B4EC29B444ULL, 
            0x670B1339F0FC677FULL, 0x9D6DC1F0143DF0EDULL, 0xA50AE43E4160E4C0ULL, 0xA7E2377134139368ULL, 
            0x63768B6CB06BAD27ULL, 0x6A5B1D666B085B61ULL, 0x1B4EF3B01CB44AFFULL, 0xA981BB21B6E11894ULL, 
            0x7FDC2375682DE393ULL, 0x3698420FD2034C95ULL, 0xEC1F9534AD07B7CDULL, 0xC9092EC1700EDEBFULL, 
            0xEA7BCECDD2EA42B7ULL, 0x9E0223888A39E8F7ULL, 0x241B2DB4078961ACULL, 0x4DC8BFE0BD15DB6FULL, 
            0xE6E99F1EAC065587ULL, 0xA069F98F6C3BC5ADULL, 0x71BCC9423AB7B15EULL, 0x1BB48374752F8220ULL, 
            0x1286AB7D2739AF99ULL, 0x6AEA0D0E15BC314BULL, 0xF30FBFB1C87606D7ULL, 0x2F0F60D282836A69ULL
        },
        {
            0x74EF93D0C8C389F9ULL, 0x052223A7C8139C1CULL, 0x33EEA268AB61F40FULL, 0x42FE052C248090B3ULL, 
            0x27CE0894CF7039B0ULL, 0xCE5070531F3BF1C8ULL, 0x647245AA44F49A23ULL, 0x75E8FF7CAADF8C58ULL, 
            0x8399A2ECFF085C7AULL, 0x0492063C52EBB0E8ULL, 0xB0CA7D8A9E4B8423ULL, 0x4E6F919E94D21A2EULL, 
            0x6A9313ABE93813CCULL, 0xCBA7B59DA4393A14ULL, 0x6325D5092BF37DBBULL, 0x92EA1379AA2574ADULL, 
            0xA6F81DC70AC0AF6FULL, 0x201B99D05C32C41AULL, 0x2030B9A6083B8AC0ULL, 0xBAA2D58636D3D78CULL, 
            0x30195FB009FD9C4EULL, 0x93C67CBE153C7F1CULL, 0x49EC4F4161361091ULL, 0xBA7CC8B400839835ULL, 
            0x2BCA1B60439D06CDULL, 0x361669F65EB37977ULL, 0x53F0892DE8FA2500ULL, 0xC4CF5B7517782366ULL, 
            0x9E5EE587ACE070BFULL, 0xB642F209233FE948ULL, 0x576ECE5A4570B172ULL, 0xBB58CDCC127F9894ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseEConstants = {
    0xD937C2362450173BULL,
    0x0DD7233A59B1CF09ULL,
    0xDD16BCD47487E81AULL,
    0xD937C2362450173BULL,
    0x0DD7233A59B1CF09ULL,
    0xDD16BCD47487E81AULL,
    0xC12376E6C3FEB021ULL,
    0x72710ABA911A0F8FULL,
    0x9C,
    0xA8,
    0x48,
    0x08,
    0xE1,
    0x82,
    0xAC,
    0x2B
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseFSalts = {
    {
        {
            0x9D4A9C39F8BC3CA4ULL, 0xA404FB6B8DF91627ULL, 0xD17C34E38FEA47AAULL, 0xDC34AE25F22E29D4ULL, 
            0xC73EF73E96F464ACULL, 0xB091764046D9D9F5ULL, 0x131A9C049945569AULL, 0xB30CDDBC086655A5ULL, 
            0x74BFFFCEE26EF2EBULL, 0x92D127A7B87B3DC5ULL, 0xC1FE0F08594F4E7BULL, 0x00DDC1346A039E91ULL, 
            0xE340DA1CEB1980AEULL, 0xEF6F30EF86D94098ULL, 0x7D639ECF5C238AB5ULL, 0x3B4F82F2447F670FULL, 
            0xF303C683877CD99CULL, 0x98A656FCBCF0F601ULL, 0xDCA1858A324C63B9ULL, 0x4D9AE572FC4879EFULL, 
            0xB8F7093FEBA38DAEULL, 0xF2A87E0CCF4D2477ULL, 0x709389D89C836E13ULL, 0x4BCE686E997C39F8ULL, 
            0x886613C16887B75AULL, 0xDE7F2C9FF8772E1AULL, 0xB1458EC2ABAA9C44ULL, 0x319D005EF6E7D9AFULL, 
            0xD407BB0E18040CFEULL, 0xFF703FD875727E2FULL, 0x75AEF6FDFF5E2A43ULL, 0x90A561EC2FE5EBBBULL
        },
        {
            0xDF02249242CF3232ULL, 0xFA8001FDEAD727EBULL, 0x3DB268D0627C2FA2ULL, 0x10F05BF6F13ECB10ULL, 
            0xE8D72A7B0F79C988ULL, 0xF895389879F04A8EULL, 0x6211CA4903692DB7ULL, 0x249134ABFF8A1445ULL, 
            0x25A666AFE819149AULL, 0x32F0D3792AE4EDA6ULL, 0xC52E15E3C79021A5ULL, 0x4658659C545369A2ULL, 
            0x2DAD57E89BA9C943ULL, 0x6A631E6F83707389ULL, 0xC0AA61CE555B1411ULL, 0xFD419DE502D7C75CULL, 
            0x08C27128AEC0876BULL, 0x897AA7E7926DE4E5ULL, 0xB2ADEBC51D70B93AULL, 0x220CA897FE412C6BULL, 
            0x0D2D977BFD416C25ULL, 0xC47921C5A1919363ULL, 0xAF188D577638DE30ULL, 0xA8F95613B6A32BD3ULL, 
            0x9C93D00B4931BA6CULL, 0x64EDB59540490224ULL, 0xF048E6E0EC0878AEULL, 0xBADF0C9B7BBA8757ULL, 
            0x536DDE6FC90EE141ULL, 0x93A242EC639B9160ULL, 0x14A83A3655B5C283ULL, 0xDBE5E001BBF56D82ULL
        },
        {
            0x3C5EC04A16B5831FULL, 0x8C9D6B062BF69279ULL, 0xFB4E20EDB56B86A6ULL, 0x9CEF9444AE9529DBULL, 
            0xE0E9DC40F0C432AAULL, 0x56518813A32D456CULL, 0x307492BD3581F0F2ULL, 0xC62279AE3D533402ULL, 
            0xFE7C84A847EBBF20ULL, 0xD16E09E88DC7D105ULL, 0xC078DBEDD7081570ULL, 0x9C5B1551823AC366ULL, 
            0x8001F66F46499AC4ULL, 0xD9FA50214E2F93EFULL, 0x181ECB8AC2970268ULL, 0xA4B851815AF9463AULL, 
            0x56069017B0D2F857ULL, 0xFA866444BE6A11ECULL, 0x8EC8FDC623E78A7CULL, 0x06BF6D12FB6D12DAULL, 
            0xC5ADDE9DBDBBFC3DULL, 0x8C0634E6E829ACA6ULL, 0xF16639BC46CE6937ULL, 0x46B415302A37E75BULL, 
            0x117E3AD0B0D35138ULL, 0x1F9AEBC6E89209B0ULL, 0x789DD1874007D6C9ULL, 0xCF465555473AC791ULL, 
            0x80CCD95582F5D864ULL, 0x99EDD2E484139D13ULL, 0x9645DDA194AFA39EULL, 0xC547B8C3A9D69B67ULL
        },
        {
            0xA757949AEB8E37A1ULL, 0x734D7E4D1C50F49AULL, 0xA3C62CF129A299ACULL, 0x355BAF17D7759403ULL, 
            0x021E7442A833BC0EULL, 0xF0F515ED523B4235ULL, 0x9A146DCA8441A1D8ULL, 0x5C0F5F5F2C9588A2ULL, 
            0xB51C0ED8291A34DAULL, 0x5E25D33406139F55ULL, 0x308A3CA70957C6ECULL, 0x6EFBD54F376AA7ABULL, 
            0x13E12C527B8D7302ULL, 0x9909568858090AADULL, 0xFE3B53780A4CB883ULL, 0x7E0A60D449B2B3A1ULL, 
            0x931D9A970CE9A3FEULL, 0xF08C3F020EBD67A0ULL, 0xA39172506D0C4DBCULL, 0x688F69CB2441CDE0ULL, 
            0x37C6364A4A49DFB8ULL, 0xD50372EDFB923BC1ULL, 0x8898551172800C7DULL, 0x7B158323DEAEDD55ULL, 
            0x902E2BED5C1FE5CFULL, 0x8BDC02EE36A641E6ULL, 0x3C651C1F4DA10C1CULL, 0xB3358897C20CAAACULL, 
            0xF75F28E2767835CCULL, 0x0AE62738717A1F43ULL, 0xEE6DC9B028715089ULL, 0x58BDED7FFD697449ULL
        },
        {
            0xE3202844502FBEB2ULL, 0x74FA5867CCA47F3FULL, 0x57D2994952AF45A2ULL, 0x0D51E42AA6BE6092ULL, 
            0xB3C48D5D4279EF90ULL, 0xDF113E6C18011171ULL, 0x8C058FEFE72747E6ULL, 0x8E849DABEFB04F98ULL, 
            0x8B7AB8451C4223C5ULL, 0xCFFA7DC318C41BE1ULL, 0xC540BE58181050D7ULL, 0x2E226642226E8F7AULL, 
            0x25824A1ABCD02F9CULL, 0x2F71AD798132681AULL, 0x5C4A5C0F4AF99A10ULL, 0xCD31D3E8ACC02EACULL, 
            0x233BB324459C1C41ULL, 0x1656B992E35BBA38ULL, 0xAF3A2D8CFB7851BCULL, 0xF10CB0329D3F38F7ULL, 
            0x332DC07A806DCA15ULL, 0x651D1551B8DBF42CULL, 0x5C2F32CA7AB54553ULL, 0x02A1EA5208796FA7ULL, 
            0x2E55BC1F752B944FULL, 0x3946150C5B2DFC86ULL, 0x7A2AEEF3C9585FEBULL, 0x5B4FED5DDAE2B266ULL, 
            0xFF87E41D5827DDC6ULL, 0xB1CE20C0EE3452FEULL, 0x44EEA60E466BA868ULL, 0x15A50A6ADFDC32E0ULL
        },
        {
            0xCDA963606D8EF672ULL, 0x503B53B56DF2D1C0ULL, 0x434B78B3C402BD0AULL, 0x0D24CC9BF775598BULL, 
            0x3DB7D808420E33DAULL, 0x50E504B619420B9FULL, 0xA77FAC8B61F28817ULL, 0xBC6270E1CDD04723ULL, 
            0xE10A147C0FD3EEC6ULL, 0x18C64059C71EDAC1ULL, 0x9F07F7F714E7B372ULL, 0x7DED1BA8C4685960ULL, 
            0x0C67BD6A8983C6B9ULL, 0xC8758E54A1CDBD4DULL, 0xE3AFB654B826292AULL, 0x2E480F39024C7E20ULL, 
            0xFD73E6A76F4FD537ULL, 0x3AA16CCF1CF51B0AULL, 0xA96D4658086BB838ULL, 0xD89A351BBF8D2097ULL, 
            0xFF4C7655188BDC21ULL, 0x4FB0FDC3133AF33EULL, 0xCEEF879AC2DD4C2BULL, 0x0B634D5BCD0280F6ULL, 
            0x9455E049482EBEA6ULL, 0xCD206AA67B26D62AULL, 0x42D2E1B5C08085ACULL, 0x69F865EFA184CE88ULL, 
            0x36CE83B84D5DCB32ULL, 0x000C5AA8D275D4DEULL, 0x3D0687717CE59EF7ULL, 0xD24A061216E3B007ULL
        }
    },
    {
        {
            0x3D93533C81828050ULL, 0xE0A5CB5FFEFEBAC5ULL, 0xB42E1DA649332FECULL, 0x84876B2CC3BC31BCULL, 
            0x9C2A9D9670A6F94DULL, 0x264B1FD714E61AE5ULL, 0xC08B3B8BB4A83CF5ULL, 0x2DD5E8A0677CC30CULL, 
            0x4806B71421EE1003ULL, 0x6B8B807A25B0B0DFULL, 0xEF868A65A6A04D83ULL, 0xAC17E7FDE8696E10ULL, 
            0x6B982283FA646186ULL, 0x03470DE82BED04C3ULL, 0x39A93B1DBCF05D3CULL, 0xA300936BA0AB98E3ULL, 
            0x4721842AB62C5D06ULL, 0xFD08005A36B994B0ULL, 0xDAC262D03A68E10BULL, 0x83E8385FD72EFDE2ULL, 
            0x4EE13F2113172289ULL, 0xFD72CC1D35E584E2ULL, 0xC83C41834E4661BDULL, 0xC8143E077D4428FCULL, 
            0xB39138016E36A078ULL, 0x11CE529F27FF5E49ULL, 0x816A8789D3E77088ULL, 0x7B8024B95BFE1F17ULL, 
            0x9D240D23DC78FA0DULL, 0xAAF465B40F94DBD2ULL, 0xEE961DBFE17FA76BULL, 0x08009D54C0CD8EF4ULL
        },
        {
            0xFC43076777258999ULL, 0xB6CEBC33076D388BULL, 0x9763187E6F1F3996ULL, 0x7E0403E532AC55BAULL, 
            0xA129403C39B103ECULL, 0xEA664D6D2B23DE9CULL, 0xC39C3C5899E1B3D5ULL, 0x6D8FA99A57DE6F56ULL, 
            0xC36CEF82D88EF483ULL, 0xD5481391F7121245ULL, 0x1ED3FEC0040636E5ULL, 0x0A023E2D608EFC02ULL, 
            0x45FA9DE988D51F7FULL, 0x8150DAD292C0B623ULL, 0x3E9B02337613BA74ULL, 0x3FC5592F816097F1ULL, 
            0x24E753037565A1AAULL, 0xC3BDACA67DD872D5ULL, 0xDCAF99B4D96BCFF7ULL, 0x502002DDF1457989ULL, 
            0xB785292DED3FE6B2ULL, 0x625EFBD5E1E8E11BULL, 0x119C843AEB4DB4CBULL, 0xA340FBFBA8B30E7BULL, 
            0x9D017670381B4710ULL, 0xA267096AF6741D18ULL, 0x9733E0094E169317ULL, 0xE6768EA325DFF1DBULL, 
            0x221D758E2B8B8836ULL, 0xA662EFD1EEAD8082ULL, 0x701B37350F89B23FULL, 0x27235A39725DCE94ULL
        },
        {
            0x4C39DA276E8E5CAEULL, 0xE504208FE4A9B8D7ULL, 0xC35114358A2CC74DULL, 0x6742342A118226C8ULL, 
            0x2CE5726BB4A33B11ULL, 0x0F339C9E4BA5B82AULL, 0x7D348442E7396A44ULL, 0x56A3DE6335E66D3FULL, 
            0xDAB4E2BA3285C4E5ULL, 0x18D47B9B0D661FF5ULL, 0xDCCED6FFE9335F04ULL, 0xEBA5BA9AEDD7973EULL, 
            0x4FF6F3880046D6B2ULL, 0x22519D4DD65EAF0DULL, 0x45C50A3AD2E2FCC2ULL, 0xEAF70C05CE360B87ULL, 
            0x137FDDF4B5232114ULL, 0xD26B5C22BC48CEE4ULL, 0xCE4B302B54061CE3ULL, 0x956D39CE026AE85FULL, 
            0xF32D26D929D23321ULL, 0x820E5D9D2685EB06ULL, 0xB7DD74DE0BF858EEULL, 0x9E8EAADEE63EBB32ULL, 
            0x421733931D4182D7ULL, 0x33F74ADC1B95A478ULL, 0x4FC3AA96DFA3E3C3ULL, 0x913CDDBDF24FC14DULL, 
            0xC729F6AAAC405BA4ULL, 0x638D85EBBFF668ECULL, 0xDC00B183064304E7ULL, 0xB6559798B9624E4BULL
        },
        {
            0x7F6CB8641DDCC8DBULL, 0x3E17BA0403DF4A42ULL, 0x601E4815701D03B6ULL, 0x102E1367003F8A69ULL, 
            0xD74F22AB5F38F3C9ULL, 0x689744E5B9AB5725ULL, 0x3948DCD0C587FA20ULL, 0xFC7615E91987F92AULL, 
            0xCF12CFBE4A5480B7ULL, 0x36B929D28FCC9DF2ULL, 0x7B14C4B4350410B8ULL, 0x2387CF8DAA2E8C2CULL, 
            0xA10D89A9D27A2A15ULL, 0x977712F69CCB7F85ULL, 0xB4E370C86FB4A405ULL, 0xC5EC563C44F33336ULL, 
            0x9E191FBD7B1A084AULL, 0x33E4D8C9E2A3A304ULL, 0x09F16DBC43CAFCCEULL, 0xC0E83E9798173F42ULL, 
            0xC1866B429A9F0BC1ULL, 0x283F91FD32EEE813ULL, 0x913B906B69380870ULL, 0xF14452B0758E470BULL, 
            0xC712BFA80694CA80ULL, 0x3D9A323A6BE6033DULL, 0x91F31B73F35B591DULL, 0x6B0E0BE36C56A703ULL, 
            0xF69E461E47882060ULL, 0xA7FAFF3446BDF6D5ULL, 0x3328C12CD56E59B0ULL, 0x455B928EDAF0132BULL
        },
        {
            0x2BCE8233E2003BBDULL, 0x83C2185AC2CF68E9ULL, 0xEFE5754E169373FFULL, 0x3439421C00A2523BULL, 
            0xDA844F92E17515BAULL, 0x829F360A7ADB7781ULL, 0x97A4AA57D92F1961ULL, 0x1C5DB92D0F022196ULL, 
            0x9C975AA0DBD5A5B0ULL, 0x733180718CF09801ULL, 0x100E33F294F8EFCCULL, 0x4C2DA73310F78F19ULL, 
            0xEDE6EF7ED6A83170ULL, 0xFBC71AEB596EC6C1ULL, 0xD08279EBE394B3C4ULL, 0xD3AE8F6CBBF8985BULL, 
            0x61195A8849761E66ULL, 0x5117720220C8E511ULL, 0xBD0A591AED373995ULL, 0x7B383EC6F9822D1CULL, 
            0x8CB8AF4A9727AE24ULL, 0x00D4483D3F318EA5ULL, 0x671695B3FA30A960ULL, 0x46DC85353C72C073ULL, 
            0x801912C450CAAAB0ULL, 0x8284EB4190B73B4EULL, 0x1C79CAD491B0AAD3ULL, 0xCA75117964CA4744ULL, 
            0xBB0E15E51096EDD2ULL, 0x52B7E3AA458E4B96ULL, 0x6C9A1ADF97A220A9ULL, 0x8A201D597FDD4D35ULL
        },
        {
            0xFA99D537C9A787DBULL, 0x563A4F30A5DD23F9ULL, 0x8E68B2F10807CB47ULL, 0x7D54D63E344310D5ULL, 
            0xCA0DACEAD5F5C187ULL, 0x658DADF0CD451578ULL, 0xF0D9ABAE948D1584ULL, 0x8FDED27CDD552C1DULL, 
            0xF14C8D6152C2A103ULL, 0xC02218AAB7FF6BBCULL, 0xAB58C0D00E413D45ULL, 0x123CD4D6897C9C39ULL, 
            0x396313D221C10C19ULL, 0x803152FD7E4A7D36ULL, 0x406BC690DC596CD3ULL, 0x84E8C877DB56EB53ULL, 
            0xEC49CA6476C247C8ULL, 0x572C37EC65ACA109ULL, 0x0EAA796B05EA67FEULL, 0x317E4AADFBAE3AFAULL, 
            0xC88AA893526AD07CULL, 0xC7B9D401A4B20B06ULL, 0xDD8B7C7FC2CED1FCULL, 0x82E425EADF44C7C6ULL, 
            0x0D3DC421752EEDFDULL, 0xFB816C79D58A7B91ULL, 0x9D7E325B64989445ULL, 0x635E92BF1E18BF5AULL, 
            0xEE90F88CAB9F762FULL, 0x433A196D69130B89ULL, 0x7841E43D54070588ULL, 0x80CAF86822554731ULL
        }
    },
    {
        {
            0xE308B271A73BB088ULL, 0xF3A141D583430C7BULL, 0xB6F70334451EC344ULL, 0x8224DF04F5703189ULL, 
            0x2E8C0BF4DE3020CAULL, 0x70CB5C37CA865A8CULL, 0xCE866A419C41C1FCULL, 0xD17229DA88089C45ULL, 
            0x0BC1B87ADD068B14ULL, 0x89CE403728231409ULL, 0xAA2BFFDF1EEDFE02ULL, 0x6C28C5BC4F0428ECULL, 
            0x7191E4DEC2F914FEULL, 0x805AFE08101D1E6FULL, 0xBDBC246D0E067736ULL, 0x2BD15D7420963D9AULL, 
            0x2E08ED9874B4EF9CULL, 0xCF42F0553010EF81ULL, 0xF137A91FFAA3B968ULL, 0x051DB3F14B6C7416ULL, 
            0xC044663C4D501D0BULL, 0x9D1067A506628C47ULL, 0xB67180899780F153ULL, 0x4300CE783A541DBBULL, 
            0xF6D934BB0315545CULL, 0xEC12F75119F29E1EULL, 0x7613536803E815FEULL, 0x6AD2AF6D2856F104ULL, 
            0x26B39682726E50E2ULL, 0xEA07FCA7E1EB9337ULL, 0x66CBC1B3459664EEULL, 0x79642D8585524579ULL
        },
        {
            0x8BA060B457BE0BBCULL, 0xC4AC6DE8FA60F3C4ULL, 0x09D959A07E534CD1ULL, 0x67E340E88E163404ULL, 
            0x7FB649E3DB31996AULL, 0xD32A6DC907BE040BULL, 0x637BB167FADEFB7FULL, 0x41185B89CE7CDB4FULL, 
            0x93EC4B0F167BE360ULL, 0xA5BF84780173F7C1ULL, 0x45456BFE69DFEF1BULL, 0x0DBA8D58C8555471ULL, 
            0xA56C1B851E3C641DULL, 0x3F5EF813DEAEB7ACULL, 0x15234A83DB591C88ULL, 0x7D43928925E19EDBULL, 
            0x2B2637B6BC091559ULL, 0xD3DE765A079D9A6EULL, 0x03B89CBB7FF30AFEULL, 0xF3B0E66B4720DCCEULL, 
            0xAC0D44C3EDFDA28EULL, 0xBBBAF14D2FE74703ULL, 0xB460917D49217CBEULL, 0xFD6478759311AAD1ULL, 
            0x244BE1C11083FC0FULL, 0x23E937D51BEA51D5ULL, 0x7F063EC9DD62C6A5ULL, 0x3D2274E911BD358FULL, 
            0x86CD126ADEBC5338ULL, 0xE326E6BAE97EBB63ULL, 0x57982AF204887A50ULL, 0xAA21ECE3FAB50BC9ULL
        },
        {
            0xD856E6DC75A02D2CULL, 0xF587DA6225CF2F6DULL, 0x650C0EA84D933878ULL, 0x84DF464F4A3578FBULL, 
            0xBB60BC5B4D151436ULL, 0x00AC5C70BD8B3514ULL, 0xA38D84517F3E5DDAULL, 0x328C5AC8D73238B6ULL, 
            0xEB5FF96628B5E210ULL, 0x131F0AAF79A45647ULL, 0x619420A4B4B660BDULL, 0xDD479D75164813E1ULL, 
            0x81339E9277E797E8ULL, 0xA0342226DCF3FED2ULL, 0x62DAF674A0B9E991ULL, 0xFE0068FD4D2C2F11ULL, 
            0x9C409A49513BB951ULL, 0x38C3FF83C0534F59ULL, 0x34C079DB9E281B83ULL, 0xFB6EBA6F6C0B8B28ULL, 
            0x8DC2302250DC2BE9ULL, 0x0969B6E54D9A61E0ULL, 0xA8554F4FE29F0444ULL, 0xBBDF114A4285109CULL, 
            0x8B8E36A5F90C4A07ULL, 0x958EB61360473790ULL, 0x472321B1CC16E04FULL, 0xC37E5BCA9DF3EA3DULL, 
            0xFF7A1A7D551D8F36ULL, 0x85A0EAA136D8B428ULL, 0x6B671BEF12599443ULL, 0xFB2F1AECB3746F5AULL
        },
        {
            0x9966E9B23EE5352FULL, 0x441EA00AF89DE865ULL, 0x939DAE5C9CF896C0ULL, 0x050CAB13324A24C2ULL, 
            0x51CD3E1E2B424033ULL, 0x41E7B2457988B1B5ULL, 0x10B997284039393AULL, 0xDD2D978836403600ULL, 
            0x731E8E34EDF45674ULL, 0x8D4D656DEA7B377BULL, 0x8C624948C44C946CULL, 0xBD53F1BFEBD4D4E0ULL, 
            0xC0B908BEB710779EULL, 0xF45B14469689C7AEULL, 0x45E4F379968B77B6ULL, 0x0D7C462A97FC19D0ULL, 
            0x870F90BC03F937E4ULL, 0x6F62AFB774532FC8ULL, 0x79B3C9678E945BF3ULL, 0x906EC89AEF6A544FULL, 
            0x20C58829EAECF481ULL, 0x134E1E672D6A9A68ULL, 0x514DEE9E5F558798ULL, 0x307075E674617E8CULL, 
            0x3E3E715DEF382D16ULL, 0x16739EE30B2CF3D6ULL, 0xB16A1AB65CC9AA29ULL, 0x789B0061B2A3D26EULL, 
            0x89E9B4A5B7566963ULL, 0x64D94048684D4F0EULL, 0xFC0BA27778668DD6ULL, 0x65AE0E17A2C6B2C2ULL
        },
        {
            0x22B0069E350706A5ULL, 0x48AE2F830D78160AULL, 0x77835AB48E7FC104ULL, 0xB690EA59888986D1ULL, 
            0x22EA2233FDA384E2ULL, 0xB9E830825ECE6143ULL, 0xCD1F27DD9303186AULL, 0xA1CB28FE0FCA1C05ULL, 
            0x127E6C04DD72E69FULL, 0xA6D55E0D7107C20CULL, 0xF66ED26B56DB34B8ULL, 0x0D93276FE892FF7EULL, 
            0xDB2DD4EA31D31B6AULL, 0x75AB706E1F5712A0ULL, 0x3BABF39F879EF75DULL, 0xBCB114101658C3C2ULL, 
            0x9D6238815F302E3EULL, 0x8E4885B6CD0CE228ULL, 0x55131B28C6F859AAULL, 0xAF88864E2915EB97ULL, 
            0xE560C10B79B6CD48ULL, 0xE5BBA03AD2B8754CULL, 0xA0BE6806C4241BF6ULL, 0xB3CD783D4E807E26ULL, 
            0xA1368E8A4CF4DDC3ULL, 0xC8C66A5BC54468A1ULL, 0xB12D51250C53DE96ULL, 0x01409060D133AC12ULL, 
            0x6A22F3C301CF60A5ULL, 0x264F877DFE99A00EULL, 0x3F038D56EF9266CFULL, 0x69DB572973A27D62ULL
        },
        {
            0x87E346BD15A7080FULL, 0x6F995ADFEF7B177EULL, 0x3F357F62771A8B7CULL, 0xE6943D45D26C52ECULL, 
            0x69AB4113DB363EC0ULL, 0x0077D09D2665FD18ULL, 0x00608CF0DA591DCCULL, 0x8425FFC4257BEA74ULL, 
            0xF5887C4D7204CD44ULL, 0x5B3F1A0B15BE70D7ULL, 0xD5CD84C8E2AD6E64ULL, 0x6BF39494EA6EE5F7ULL, 
            0xA2C69906A84DAB1FULL, 0xF90A6E29797EDDDBULL, 0xE69B31533CA80EB0ULL, 0x2D327687E05E9660ULL, 
            0x742752DB71684CE7ULL, 0xE9346D446978F742ULL, 0xF2C989FB7F4C4214ULL, 0x34BC9C5D31F65CA1ULL, 
            0x2FE9F76E41EAD480ULL, 0x0521B7B1562C05B2ULL, 0x8D42F0AB1417A052ULL, 0x09161D1D34FDE156ULL, 
            0x6AE1B150C5C3B83EULL, 0x59EB961E2C78DC00ULL, 0x379E4956AEDB6533ULL, 0x5091577B80838748ULL, 
            0x4979A7D6BE0C2505ULL, 0xB53A18005F6BC4DFULL, 0xE8C1119E53E5CBF7ULL, 0xA8DF640A57BD3A6BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseFConstants = {
    0xD17A9C889F2CBD05ULL,
    0x5E84ECA026844B6FULL,
    0x2595DA74D3D583D4ULL,
    0xD17A9C889F2CBD05ULL,
    0x5E84ECA026844B6FULL,
    0x2595DA74D3D583D4ULL,
    0xFDB726F3D2BD886AULL,
    0xCCAED994E5BFF6F0ULL,
    0x7A,
    0xFB,
    0xB8,
    0xA2,
    0xD6,
    0xC0,
    0x55,
    0x02
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseGSalts = {
    {
        {
            0x0802870203D0E587ULL, 0xCA5E954305FE9FC8ULL, 0xA54251844D76D33FULL, 0xD5321D39B1658B0AULL, 
            0x245AA5A5AEB3065EULL, 0x29D88E598B22E940ULL, 0x0A68C5AF1D413E22ULL, 0xADBD37EC7D2CCD8DULL, 
            0x40711360B5234BCAULL, 0x267414FFC525D743ULL, 0x12A674D45FEB0D16ULL, 0x7027E19FFF411F0FULL, 
            0x7B71873F5005EEDAULL, 0x23BC501B778FDA89ULL, 0x051D1C6ED0988743ULL, 0x43E7AD7D3C06F7B5ULL, 
            0x012BFD15E404D1C1ULL, 0x0E7B98E36B394B9DULL, 0xEFF810722275593EULL, 0xDD930573FAB124A5ULL, 
            0x681C2F05CA40AB52ULL, 0xED0FB15856AF36A9ULL, 0xCE8B3FDF45051B6FULL, 0x7DBABBE090D5AA28ULL, 
            0x56E00ECDAEF755CCULL, 0x83DF863430EA1722ULL, 0xE40E843C15D7ECC4ULL, 0x74331FEA19A24019ULL, 
            0xFBDE8978F4FE9C75ULL, 0x7FB3B1F54C58521FULL, 0xE8E1157EA7F10699ULL, 0x10907E7287DDC8A7ULL
        },
        {
            0xCF1EF72B7D8C3B95ULL, 0x59A5671D6A6B80CDULL, 0xD30A16517A61CE4DULL, 0x99813D18F6A4A87BULL, 
            0xD6EE0FF16FEFE2BCULL, 0x3DD2F0DDF0CFF382ULL, 0x17259998C66C0F51ULL, 0xE1F17A70097AAC70ULL, 
            0x917F2E675F48410CULL, 0x9938D418F79B229CULL, 0x2FB14E80B1F1FB4DULL, 0x8B9DBC1BC7D1EBC1ULL, 
            0x8A2E9F0FC7EBB06BULL, 0xDDE299E94629473EULL, 0xB7ADF02418D6BBB1ULL, 0x03384E3F83D7B766ULL, 
            0x571645D8A5AFEFA6ULL, 0x72A9B79B86EEAD5EULL, 0x3A5FF676A85E3F08ULL, 0x4D700D79AA67EEEAULL, 
            0xCB6C9C4B6E927088ULL, 0xA382F985F4237873ULL, 0x28DF8193F2F5D472ULL, 0x12603F8A4314D195ULL, 
            0xA98FFE9474654DB0ULL, 0xF27694724D0AB470ULL, 0x7CC44FB2D849ED98ULL, 0x32AEF51D0717B6F3ULL, 
            0xC37F68747942F408ULL, 0x3A1566E747F4F118ULL, 0x3891F5BA70592A28ULL, 0x6F68418E65086127ULL
        },
        {
            0x6260868207824F24ULL, 0x57263FFB5D9B374DULL, 0xE9EB9DB685B13595ULL, 0x7F6133584CB60035ULL, 
            0x7447A0A7174F59DFULL, 0x6275AA3C08E87D68ULL, 0xA23894C82CE8CCA2ULL, 0xAAE0170D0CE3CF0AULL, 
            0x3503760C7475E69CULL, 0xDCAB1BE27090421BULL, 0xDB638439461A09AAULL, 0x1E3F561E23493C3FULL, 
            0x2674E94ED219D38DULL, 0xBB238751DDC4F8ECULL, 0xE86EF65C2465ABEDULL, 0xBE3256EB6A93198AULL, 
            0xC15FD9082C6156A0ULL, 0x42CDF24631BE2E1AULL, 0x5A2AACD6F6B0D7EDULL, 0xABA48B0914975DA0ULL, 
            0x37E150E4F8968C38ULL, 0xE9C1DF7F95FFB946ULL, 0xF4B8E9E3379B1D80ULL, 0xD4FC00B75951574BULL, 
            0x9329F9034D5A6822ULL, 0xADE8474BF1DC0C61ULL, 0xEDCEBFE42F003AA1ULL, 0x4F766EDD9AF0F5B7ULL, 
            0x8535E7244271904AULL, 0xB5FC3AEFA9BEAB13ULL, 0x8E6271F5A7E79F9BULL, 0x917A9E3DB72395FFULL
        },
        {
            0xCFD140E56784FB4AULL, 0xF362E5BD956170A3ULL, 0xB47875F70C10C729ULL, 0x129A62C07CCC62F5ULL, 
            0x87E5E6F477E6067DULL, 0xEEDC720DC16A0CDFULL, 0x821274D32ABAFFDDULL, 0xD0AE09C258B6C161ULL, 
            0x3181593EEC7D1BAFULL, 0x6AF7ACF08E087539ULL, 0xDCDC59CDB228C34EULL, 0xAA18287C10687D71ULL, 
            0x83BB5998A741E711ULL, 0x9295824AF6CBEFBDULL, 0x23059C64F2FB8D3EULL, 0xD9D6C91FD64E0CE6ULL, 
            0xF574FB018BA02653ULL, 0xA99A9FD00F49E447ULL, 0x5EC9C5872861BDFAULL, 0xBED47BF81DD023E0ULL, 
            0xDB6727676427A93AULL, 0xE333D5E0F7662F74ULL, 0xC32032E32952CBC7ULL, 0xFB5F491D2F9AB3B9ULL, 
            0x22274AF4823350D0ULL, 0x8C64328641104EA4ULL, 0x01229B7EA2D92AF3ULL, 0xC1AADE98BA5F70D2ULL, 
            0xC5A04B1572D49795ULL, 0x0EFF65B7927DEE15ULL, 0x1B00B4864882C77AULL, 0x2993B878FC68B494ULL
        },
        {
            0x4BB5A4E9863D280CULL, 0xFA5925429E8E59D3ULL, 0x281566366538B0DCULL, 0x6F6A4B81CDB83EA0ULL, 
            0x1DBB9633435366AAULL, 0x8BBF3A55CB72E062ULL, 0x3AA37DC8F128DC90ULL, 0x758F0AE0C7F3562EULL, 
            0xFDEAACA8C3BF064DULL, 0x40E5F4B1908CEE34ULL, 0x86C5BF17AC0E43ABULL, 0x74CE5BC7D244D1D1ULL, 
            0x85B3EDE2C8BA6F42ULL, 0x1B328725A0356D64ULL, 0xC9A0A2A4562F79DCULL, 0xB50CAA86647641C8ULL, 
            0xB8CEBD6876F8C36FULL, 0xA8B90CD8B90592C6ULL, 0xFD139AC91C2D0EE3ULL, 0x4662A2E943107B5BULL, 
            0x038BBE109299DBBBULL, 0x3CB4C8E187545AE9ULL, 0x33FBF85D06CCF401ULL, 0x9423DA83AB218C57ULL, 
            0xD77E8B452E53A4DAULL, 0xA6D5D7218FCE9949ULL, 0xFF9AD6F0E201AD67ULL, 0x2AD44C5E13DF3039ULL, 
            0xC36E216AFEEB65F4ULL, 0x88BF8C367A69CEC4ULL, 0x720F64F3CD9C80B6ULL, 0xE13E7E53F5737D9AULL
        },
        {
            0x119C949A904FDADDULL, 0x3F38D3F0D62D44B3ULL, 0xD508CC605000B4AAULL, 0xDA270E42E442933CULL, 
            0x799C5B5884771757ULL, 0x83CBA90313663BD2ULL, 0x51A3C39069731583ULL, 0x8736F51C4361F401ULL, 
            0x5C06BD16F9AA25C7ULL, 0xE975166091AA3A63ULL, 0x3F154D27CB0A8CFDULL, 0xCF6AF87C1E7119C6ULL, 
            0x0B3D7CC0D6EEE931ULL, 0xAD4F94A0F846EECFULL, 0x080E6A0CDD4A2B57ULL, 0xF8BDBE486DA6FFA9ULL, 
            0x4E21B6EF39EE4A4BULL, 0x285FE634F754D3F1ULL, 0x779CF91F719F4F11ULL, 0x3299DBF2016A4B66ULL, 
            0x39FEFCCA8C77CBAFULL, 0x82A09C96C49E1349ULL, 0x9B9A9AB4BF12236FULL, 0x49AED7B17B55F53CULL, 
            0x8983855A5AD724BFULL, 0x0F66A80322A12C6CULL, 0x357455B4A682DEF1ULL, 0x26C356A7D78FA8A6ULL, 
            0x2D9D6FBDA58220F3ULL, 0x01E36CC93BDC6C36ULL, 0x65EF03A0AC5D008DULL, 0x874E71FF779BF6EBULL
        }
    },
    {
        {
            0x3B58A7A8F339776FULL, 0xE6B89AB85CAF1765ULL, 0x7B2B3083E8448037ULL, 0xA91B87A313016218ULL, 
            0x8245E321E06A9BD3ULL, 0x176A256A59AC5BAFULL, 0x47151CE5B43CD518ULL, 0x6F357F0D82831992ULL, 
            0x9BE1C38B086E138CULL, 0xB29EF7DB496FAFCDULL, 0x148E2ABF06FA0582ULL, 0x552CF462D31A097DULL, 
            0x7D3783887D640468ULL, 0x7CA276AECEC7F5A5ULL, 0x2F44E7FCDF79D70CULL, 0x732B1618901CD396ULL, 
            0xCAD797265550C8F0ULL, 0x7C60C6CDD8E76BCBULL, 0xEADC534C65F8AD30ULL, 0x3107C7DAAE9A4F22ULL, 
            0xD7FB5163121D9B8EULL, 0x81DD4EA2BF32E358ULL, 0x20B788C643B2929CULL, 0x28AFF3DDA0256BB5ULL, 
            0xB434E80F608EDAC3ULL, 0x0068387281EF65C7ULL, 0xA3309B6DCD8D060FULL, 0x01B32BC4B0528BD0ULL, 
            0x5D5C23259261B9A1ULL, 0x6D262FC7F0373523ULL, 0x603B42BBBCE8B936ULL, 0x7C751E9D494611D9ULL
        },
        {
            0xDB0ED3602EB83D23ULL, 0x4D33F837D4C91EF0ULL, 0x4B481508C9B467BFULL, 0xA9CBA1D2A65E77BEULL, 
            0xF8E9DB094BACFB94ULL, 0x453D4BE9FD4392D6ULL, 0x49A072933904C656ULL, 0x28D22A8B8FC7D3B4ULL, 
            0x1ABCE2479847D4A4ULL, 0x70F41764A360A37BULL, 0x3318DF000A47D53FULL, 0x5306343CF5E69C7CULL, 
            0xB22D58595009BA96ULL, 0x464A2FF95A75A00CULL, 0x4485A9956C2F29E7ULL, 0xEABC4FD079388C46ULL, 
            0x3FEF23EA70A57CACULL, 0x51889CC9EB38482CULL, 0x5CF018BFD0930372ULL, 0xC7D7E0FD44EED39CULL, 
            0x583AB214030C70CBULL, 0x35C4D03E30400B6EULL, 0xFD4B76B2345AAE87ULL, 0xDCC5500E3BB14595ULL, 
            0x6A764A3A072AF57BULL, 0x3382CEC1DAC352FDULL, 0x834E8B9CE061276EULL, 0x3C16BC5906827B5FULL, 
            0xB83AACC9B241BAB7ULL, 0xB3C1047D9CB6CEB7ULL, 0x09030065CA12CFCEULL, 0xEAB85A2B6C4A6B0AULL
        },
        {
            0x6D253D25B400F3A6ULL, 0xD104B34AD7F82BF7ULL, 0x1E4B230BBCFDC666ULL, 0x6EF1E77A0042E698ULL, 
            0x77247EA958879EAAULL, 0x1D6D98FE0DF0B006ULL, 0xFD61EA202B641986ULL, 0x905C7DD2F1D1F89AULL, 
            0xBA7E32E7BFAEA7EEULL, 0x9E84B36D61368299ULL, 0x31CA82034CF778FAULL, 0x2CCF3072FADFE202ULL, 
            0xADBD836D9AB234C6ULL, 0xF8A6779218A0727CULL, 0x14DD62882AE6043FULL, 0xE71AD4349ED78E90ULL, 
            0xF160C5261D358F7FULL, 0xC17F45D068C5761DULL, 0xAC2A137A30A069A5ULL, 0xF212380A95D79A8EULL, 
            0x5A529B0C7570815AULL, 0x82DF5F1E61F2A46BULL, 0xD90ADBC11E7646A3ULL, 0x351D388169E089E7ULL, 
            0x620D300C29A26828ULL, 0xC4A16B0857B0B4FEULL, 0x3F2FC2B0F839E5BCULL, 0xA70388ABE97B86BDULL, 
            0x14E2B9926061A750ULL, 0x3C8C166630B22E09ULL, 0x1790D150BD259AFEULL, 0x0BB3E9B26B263BB1ULL
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
            0xE799796FB6687849ULL, 0x2B76D27186C87099ULL, 0x453A06E0DC26FE50ULL, 0x61B0C899A07517CCULL, 
            0x83B2AB322A89D798ULL, 0xA520BD9BB6CF9DE3ULL, 0x5CF9A482AE8719C3ULL, 0x67DBB8CDC45E54C9ULL, 
            0xA3DB61F889C6C8D9ULL, 0x65D2CF85925984DCULL, 0x6EE1DBC4C88E4917ULL, 0x028CED9BE236932BULL, 
            0x53F29A5911344FA1ULL, 0x6FE42F0EDCAF706EULL, 0x6974EBDAA84DAFFAULL, 0x6B4F164709ACBD5AULL, 
            0x168177ECDB565D96ULL, 0x4896F49DF160ACC0ULL, 0x059406DFF1C4DB78ULL, 0x73C72D149E55D1DEULL, 
            0x77EE21DA3E535973ULL, 0xE8A57BDDB7A1209AULL, 0x5F2185E04D6F1FA3ULL, 0xBAF7084920E228F1ULL, 
            0xD7415499A616798DULL, 0x62008210952F0695ULL, 0x11F8E8213173DA53ULL, 0x8900625919E507C3ULL, 
            0x7FD794D7977A72ADULL, 0xCE9C85D72062E295ULL, 0xB61B0FF1DCE5E662ULL, 0xF6412902AE0C66C2ULL
        },
        {
            0x5F29CDEC147B8C87ULL, 0xAAAED027C4C2E958ULL, 0x556FB417CE8A5E4BULL, 0x474D665AAAB2AF46ULL, 
            0x0E5D52BF39BB52E8ULL, 0x852B739570545DDAULL, 0x6FAEA537FF995842ULL, 0x5D9A3EA013CBFC01ULL, 
            0x41E09F439B403B7EULL, 0x84026599DE661E99ULL, 0x9AB664F057061101ULL, 0x31A91BEF83D19F93ULL, 
            0x8B9A6773ACEEC927ULL, 0xEF36EC7C2AD20E74ULL, 0xB3C4AA89C80D33D0ULL, 0x56C13E72E8A1C55BULL, 
            0xE9855133EB1B6D2BULL, 0xEE44546AA21BA88FULL, 0xD9132E879CCC88CEULL, 0x5AC61A80CA469642ULL, 
            0xFF92DBA76BF4E42CULL, 0xBCBA10CE0162E331ULL, 0x519C85710352F18CULL, 0x39F1EBA537907439ULL, 
            0x0425836DBCDFA2F7ULL, 0xD46E23008F8C2A2AULL, 0x1B6C7A26AC954C12ULL, 0x82F4B66AB4F3CC9BULL, 
            0x6C39549C3AAE2525ULL, 0x494ADBBAE95D3053ULL, 0x3C886943A540F1EDULL, 0xA84B303A90DCDA9AULL
        }
    },
    {
        {
            0x56E69508ED4EC632ULL, 0x8ADDA2853CBD68A6ULL, 0x58BA62B589ED64E5ULL, 0xA3E57A0E50F98847ULL, 
            0xD960882BC9D78200ULL, 0x4975EB9128B0B40AULL, 0xB55A005682285A7FULL, 0xD0A0DB24668942D6ULL, 
            0x438DD3989C4E4A14ULL, 0xB44D46E1DBA9B320ULL, 0xB97AF6B81E514127ULL, 0xAE10C19FDA00CCC8ULL, 
            0x18ADBA88700FA92BULL, 0x519402B52667C747ULL, 0xD0197328A2674A49ULL, 0xA10C1D14F2E88073ULL, 
            0x0FC61625033C2062ULL, 0xBD14BC5995B0B940ULL, 0x07A4BE2A6DD081AFULL, 0x340F080F56225D10ULL, 
            0x5E1335A405A8F192ULL, 0xB2EFE90168BA8D35ULL, 0x6CF94A19940CD7BEULL, 0x903C86092393987CULL, 
            0xEF2939A1A6A91BC9ULL, 0x5597EDE2B0444E0AULL, 0xD65551D128210C2EULL, 0x84AB145C868DDF79ULL, 
            0x5F1E6A9169A8323BULL, 0x2BCE52E04191516DULL, 0x84762636E56586EEULL, 0xBD004D3769A984B7ULL
        },
        {
            0x2FA340D6993823DAULL, 0xFCED5E2109EE8620ULL, 0x45E4A87AFA22B33CULL, 0x9895333A0A2D2034ULL, 
            0xB89D5257E40A1C76ULL, 0xCC92181B3438A3AEULL, 0x712C91E5FB2F851BULL, 0x657EF76DED28565CULL, 
            0xFB28CB66F40DEE38ULL, 0x974BFCC73059F79EULL, 0x58C0ACA9AD811CFBULL, 0x568CEBF221F022E8ULL, 
            0x532177CE112EB06BULL, 0xA8E428CE2C34BAB6ULL, 0x82A987B1DF82939BULL, 0x9827069846CBC525ULL, 
            0xBAFEA1FE34DB98DCULL, 0x970EA82CF2FBAA50ULL, 0x7741A0789F76589EULL, 0x41A8B935EA94968EULL, 
            0xC94B67F6C51768DCULL, 0x13EBD027170F5CB5ULL, 0x3F6D6A6B61503069ULL, 0x79CB696FAC7145DDULL, 
            0xE2C4685F788DF404ULL, 0x307E7FD33308CE74ULL, 0x76973B5FF0A3CD8CULL, 0xFC01B5813B3E0667ULL, 
            0xA693BCC04AC1A3F0ULL, 0x8F7B09FA77B848CDULL, 0x2048891D4DDA29E4ULL, 0xE48F10D2E6D42BC6ULL
        },
        {
            0x6BA83B9553A2681DULL, 0x4D7B19CE0E392499ULL, 0x0EE139CCC6BD3490ULL, 0xCCDF3906F7E8F28FULL, 
            0xD6AD4827BDF0AE63ULL, 0xBFBCD3013FA53873ULL, 0x5888EC9430ADF2BFULL, 0xEDD89F76C6C363DCULL, 
            0x87A547169E8E8289ULL, 0x682CF8F25797A72CULL, 0x8D30AD186B21FACBULL, 0x2138153400D5317EULL, 
            0xB59BC04E2017551BULL, 0x49C7C95BBE27BAF2ULL, 0xF7C9B11A61668007ULL, 0x7A7182D1A370B690ULL, 
            0x67E4C86A0B6D20F6ULL, 0x7A2B86892837C143ULL, 0x74A4B96BA7BC31C6ULL, 0xB22F859076B7449EULL, 
            0x7D425133C52F4F2AULL, 0x77119966B54255ECULL, 0xBAADF4B4D572AEB7ULL, 0x770A93F62B691BDEULL, 
            0x7ADF227501C2D430ULL, 0x221452D2AFB07270ULL, 0x645E1F150A99EF5EULL, 0xB415759143E54B0AULL, 
            0x2A41A61E2794E25EULL, 0x3930C7C42AD499ECULL, 0x87E970064601A943ULL, 0xFDDF7A71670CDD95ULL
        },
        {
            0xB6ABF009B77CFF6CULL, 0x79E10886E958670FULL, 0x823ECF953E9BB7DBULL, 0x43D576F5189DEBEAULL, 
            0x1E2D6C1FB274F175ULL, 0x80D52F7E0F272AE5ULL, 0x2B78B912F69966CAULL, 0x50E5161C9980EE88ULL, 
            0x61A02ABD1A0F9C9AULL, 0x5AC38502349F6AAAULL, 0xBF29B1D0AD9FDFE3ULL, 0xFF8E595F24ED2693ULL, 
            0x0FA15FDF0DC08E62ULL, 0x95A370D3306B40EAULL, 0xF9F03FE7713BAB39ULL, 0xD7490E00A0B2503FULL, 
            0x1A6CC0AB21F2235CULL, 0x4A849B5C7E0B3662ULL, 0x90E7C5A8502BD804ULL, 0xE080265E0A79C081ULL, 
            0xC6AAB5C0FA11C67BULL, 0x66D8757C87C8FC58ULL, 0x3CCD75FF2F60EDCFULL, 0x8960729EE9ED905DULL, 
            0x6D19A3B9264C2414ULL, 0x8CAEEB01D8FC5B9CULL, 0xEE48FBE6882D082BULL, 0x74736CF4432E0957ULL, 
            0x2FFDD7CFB1D239ABULL, 0x188004841DA2AB4CULL, 0x68016831A9CA4ABEULL, 0x8714EB1DDF269FBFULL
        },
        {
            0x7C23B78C5A4A63FCULL, 0x9B99A8785F9D2790ULL, 0xA0151111480ED3BBULL, 0xE6CC7F20AF4A4A28ULL, 
            0xECF99724BD43B9B9ULL, 0xFB7B0B64AC263524ULL, 0x5975BC24DD23A651ULL, 0xB2CF3DD43AEA3DFCULL, 
            0x0FBDABD584463192ULL, 0xEF41EBA426502C88ULL, 0x215703D2D8EBAB23ULL, 0x3DDD19556F508FB7ULL, 
            0x8A978C59DE41B23AULL, 0x5FB03602D96B4105ULL, 0x2E8341F8BE43449AULL, 0x67349C89C52BD550ULL, 
            0x51D0C4741BDB6824ULL, 0x7760EF04CBE9F7BCULL, 0xF5620E2C073E4645ULL, 0x4D3C772AA163CADDULL, 
            0x1E009C63A6E1CE7CULL, 0xD9E7724FF5D5DE9BULL, 0x244404DC41509353ULL, 0x7B132A0764CA4301ULL, 
            0xC085108D044B0C62ULL, 0xA05C59AB2CF5BE19ULL, 0x7F0566B92A3844BBULL, 0x8DBB19B230F876CAULL, 
            0x329707CA94ED8D2BULL, 0x46EF03F7DBD7CA08ULL, 0x3D1E0E5B0F31C85EULL, 0xF314310612B6557CULL
        },
        {
            0x577CAA65503FC9ADULL, 0x694A7F41701F888CULL, 0xD36E7A90B90A4CC2ULL, 0x6F7B35E69AD1C093ULL, 
            0x23ACF25184855C35ULL, 0x326E60C810038F28ULL, 0x799F5D25AE600C06ULL, 0x76DA663FB556917DULL, 
            0x0CDEEC01CAF99C73ULL, 0x120674FD3760CEA2ULL, 0x58086C699E8244C5ULL, 0xF0D896210E5A28AEULL, 
            0x1B90FDE2FE7BE584ULL, 0x9C9B43A39DE9B87CULL, 0xF6EA2BF2F0DB7915ULL, 0x6C5D17DC4FA319F2ULL, 
            0x4B9BB60C723868E9ULL, 0xDAF896E3B1891926ULL, 0x84D6109E02ACC3A1ULL, 0x62ADC93CF4C7D90AULL, 
            0x9FB5D9718CB3E7EEULL, 0x211DB22AE719920FULL, 0xF3839141F02170A4ULL, 0xED4D0A90107C316EULL, 
            0xD40DAE22AD4600E8ULL, 0xE2A84BB17DE732EEULL, 0x723CFC3641F47C1DULL, 0xE45F75B39648CE8FULL, 
            0xF5585D041B9B68DCULL, 0x19714990BC43FE55ULL, 0x8983B1221ABC6F87ULL, 0x32EE597F79E55A99ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseGConstants = {
    0xBA33463523CADC14ULL,
    0xFB9F8CCF95BA101AULL,
    0x9CD009F31757BB40ULL,
    0xBA33463523CADC14ULL,
    0xFB9F8CCF95BA101AULL,
    0x9CD009F31757BB40ULL,
    0xB5339287B74E008CULL,
    0x64795BE88D268C6CULL,
    0x70,
    0x57,
    0x8D,
    0xF5,
    0xD3,
    0x29,
    0x5B,
    0xFD
};

const TwistDomainSaltSet TwistExpander_Pollux::kPhaseHSalts = {
    {
        {
            0x1B86A7E32CD2DF78ULL, 0x27B2A9444F034EE7ULL, 0x2DBF636673510584ULL, 0x4FC29A5542932B2EULL, 
            0x358B6BC015A0ECBCULL, 0xEAF9CA54A17A618CULL, 0x3478AB0AAD3FFA13ULL, 0x1396E67D6F47EF03ULL, 
            0x17133CA254393642ULL, 0xDDF4D85707C28D49ULL, 0xA7785EE6EF7DE76FULL, 0x93DDAC66EE80041BULL, 
            0x323CAC524C47B9D0ULL, 0x25C15051A3B72CEAULL, 0xCCE085FEEEC050D9ULL, 0xC56E6755AD9BC5F5ULL, 
            0xA86DFB89F84BE981ULL, 0x1EB3CDBF25ADC2E7ULL, 0x06B6B93EC9DA6BC6ULL, 0x6F802118EFA60919ULL, 
            0x94A97441A15F73F6ULL, 0x4C3D7C6D8034C15DULL, 0x6A2A54DBDBC76183ULL, 0xA946C9DBD20C9059ULL, 
            0x60D4B3494CED86B2ULL, 0x5A301C2DC8B4BD58ULL, 0x4620F1249C135F26ULL, 0x124E9C7CF0A26538ULL, 
            0xF756E5D8794D6345ULL, 0xD1F76030367BA619ULL, 0xA4276B27B90AC0E9ULL, 0xC15625FF7AD5AF43ULL
        },
        {
            0x3C3C89CCC106A28BULL, 0x2990578AD5526B2CULL, 0x26D1662BD3EEA2C7ULL, 0x4F99D183C925BFFBULL, 
            0x14D707934C4F4E55ULL, 0x05E5094B5003BFF0ULL, 0x3A4D858265B89A74ULL, 0x665D61B190723D35ULL, 
            0x33E346A2BB6805CFULL, 0xB1B6E52D807A6275ULL, 0xA75E5BE699B6AA12ULL, 0xEE98AA955CF02216ULL, 
            0xA92AD49BBFADECBFULL, 0x52737216F6502B95ULL, 0x374A095EFE4C8B24ULL, 0x650498FA6F380C5DULL, 
            0x0C4092BA63E04A44ULL, 0xC53D53E407759E81ULL, 0x3433318C0F3605C4ULL, 0x4DB52DE3DD87C5C9ULL, 
            0xBF201F1864D1CC2DULL, 0x5351CC619D40E63AULL, 0x26ADD29DD86E580CULL, 0xB833614903AEF5A0ULL, 
            0x077645A475BEEB18ULL, 0x4D60CEB9E0D1D712ULL, 0x6231E45B6A1DB281ULL, 0xE12633AC72F0400AULL, 
            0xD7CDD60CE0D9F18FULL, 0x63C04A62E7CB7CDBULL, 0x48E7C296808D4221ULL, 0xB20E83B8A9E8E964ULL
        },
        {
            0x24BFDF0C0ECFBFB7ULL, 0xA8F09A0B525FCDCAULL, 0x6B0CF931E5033AACULL, 0x3996B0DFA74A3657ULL, 
            0x6893E23D0417D170ULL, 0xFA246D11A7E1BD71ULL, 0x477AA7B8FB5FBA4FULL, 0x8BBDCA4EB22C496BULL, 
            0x9808FAC78955D56DULL, 0xB43170F81636E502ULL, 0xC16A57BCB5715A18ULL, 0xEBABEDBADEFD4A80ULL, 
            0xB0964E9EA1405AB5ULL, 0x29FCD2C004CB210AULL, 0xD855064CB8D54C30ULL, 0x97834F139FB3A3C0ULL, 
            0x45A07D45FA5ADD73ULL, 0x37D3A1C2BCF0366CULL, 0xFC610016D97E7CD4ULL, 0x7EF3B914814696B2ULL, 
            0x56D48008E3C4E226ULL, 0xA23F6695AF9D319FULL, 0xDE974E9A90AB3F58ULL, 0xD55E7EDF7A6446D6ULL, 
            0xB367A3766F8F5CDAULL, 0x2BD41B9DECE66E07ULL, 0x68BBAE2B58795259ULL, 0x36BD15C734A0B262ULL, 
            0xBAC7AAD4680A2A17ULL, 0xC836FA91C11B4808ULL, 0x25C59B59CBAB2FAFULL, 0x928CD3B4C12CA67BULL
        },
        {
            0xB518B022413D3371ULL, 0x0DA8A743D06BE97DULL, 0x3B20D7CB9B25A39BULL, 0xAF69BAA63D08FBF1ULL, 
            0x429AD3FE02C7C64DULL, 0x4FA9F79915CF2B4CULL, 0x0A0F305D28065D48ULL, 0x43265C9D9EBB9987ULL, 
            0x59C1AB113639053EULL, 0x5C78AB24D60F33C2ULL, 0x6A69CF346073A9F5ULL, 0xAB77F63717D351FBULL, 
            0x4A2DC60106E5FB98ULL, 0x460679B823E21738ULL, 0x57B320C1313B6B42ULL, 0x75FE41EF54D6355CULL, 
            0xF947A179161A62C1ULL, 0x2A15025FE9B773B6ULL, 0x8FF6D2EB695AC85CULL, 0x7D0CB67DEC7E7431ULL, 
            0x111655FC77C146EFULL, 0x1DC086791BF825F8ULL, 0xA69B6B549AFF6DF3ULL, 0x67038AC24AAE3E81ULL, 
            0xDB111649EE0FD3EBULL, 0xC055CEF405ED7E7EULL, 0x36E91FA4F7CF890CULL, 0xCF759CDB1D7A055CULL, 
            0xA2A00A3F42FC7AF7ULL, 0x5C0D28E6D48EBD91ULL, 0x98879E388A2EA449ULL, 0xC547B8BB8784CEE6ULL
        },
        {
            0xF585CAA65497F173ULL, 0x9002568EF43BFA15ULL, 0x54D49FCF22F591DEULL, 0x51268A2FC5B7B4D5ULL, 
            0x886E8804BEEA85B0ULL, 0xA1CD329FA3F69EF2ULL, 0xCBD2860C65B3ED56ULL, 0x0B891C12514F7465ULL, 
            0xD98C9FD85B25E75FULL, 0x94143BCDCFBDBE52ULL, 0x80DC6FCB27CA6EC5ULL, 0x5D561CA397A3A031ULL, 
            0xBC441D16451DE6CDULL, 0x1A91A84D83313F05ULL, 0xC14C6960F091FC4BULL, 0x1A345EDCFD661F07ULL, 
            0x7053AB7886940B04ULL, 0xA50FE448CE3C1ABDULL, 0xD3D9AF0CE56A5EE5ULL, 0x3534A72FB2091F36ULL, 
            0x26A5D1819D7FA4C9ULL, 0x78366133FD51C693ULL, 0xEE52D28D20CECA90ULL, 0x8E5EA431B42B37E1ULL, 
            0x055B4CBC4F5CF56EULL, 0x7A1FDC717FA50AACULL, 0x5D19B5A7BB66CEDDULL, 0xB8D6BE07AEBA1BB6ULL, 
            0xAC1BA49CE4A56202ULL, 0x6ED02084370D133CULL, 0x0597E53CEBEE3E0CULL, 0x47082549D2594EBAULL
        },
        {
            0x299BC2AF7424DFCEULL, 0x4439BE94EB908AC1ULL, 0x76ECD292B17B05D5ULL, 0x45582906864E15EDULL, 
            0x0926BB45C6969C32ULL, 0x177124F132B72331ULL, 0xC6794436EC3A36CFULL, 0x438D3AB15F6FBF7AULL, 
            0x5228D77F08D7BFE0ULL, 0x4712647106559FF5ULL, 0xA41221BF924ADE32ULL, 0xC0F5677F6DF08364ULL, 
            0xCEEDAFDFA827B6E0ULL, 0xD251D498E82B82BEULL, 0x7BBA65FB6248155EULL, 0x7A4210EB59B67622ULL, 
            0xB36FCF5A4C7A0DB7ULL, 0xC922A155DF277603ULL, 0x5B8C9AC5C0AE59E2ULL, 0xA1E21CAD6399F83EULL, 
            0x73A0614C9492AE23ULL, 0xC10E1CC7669941DAULL, 0xC6D4C063D265ECE2ULL, 0x21A358FE2545F6BDULL, 
            0x1EE7B730D434922EULL, 0x26066ADA24700062ULL, 0x4C8F0F0820583278ULL, 0x1A439516AE5B63AFULL, 
            0xC09778C3E6A982C3ULL, 0xAFA49BF972779954ULL, 0x9F8D8B98D9A8B927ULL, 0xFAA5163BF958FACDULL
        }
    },
    {
        {
            0x11823DCF07CDC0F9ULL, 0xEB3FADB76807DB34ULL, 0x6C3CE87152E58267ULL, 0xA00AD1F897524FFBULL, 
            0x877BAB23CFC989D0ULL, 0xECDCE8509E363070ULL, 0x54D630AEF643CF0CULL, 0xD83B80D645E877CDULL, 
            0xCEF5993C50F6FEBCULL, 0xC167286B68D13923ULL, 0x52CE7A9029BC31D4ULL, 0x4745096DA92FA5DDULL, 
            0x40F00444D2FEA63CULL, 0x686659E2147EBF58ULL, 0x305BD688FCE48490ULL, 0x04A51B2CE7C537B0ULL, 
            0xEBC33228A55BECFDULL, 0x2D5C657DB80FED2AULL, 0x158A58CB9A672093ULL, 0x1A95BCB69FC25107ULL, 
            0xC9ADA3FC6DD3C190ULL, 0xF42E3BEEDBD8DDA4ULL, 0x4CC2D477E15AFEBDULL, 0x69DB48E1614A4138ULL, 
            0x9B1E0EFC49BC87A4ULL, 0x58761426A234936DULL, 0xB9389F191F051D9DULL, 0xBD45E98B714F0D2DULL, 
            0xBD6D2B36FA596976ULL, 0x8E30AA6332E62AE4ULL, 0xD0A29FBC2738FAC4ULL, 0x80C5C6ED4946D4EBULL
        },
        {
            0x69C878141552BCC3ULL, 0xDF6CF05112E45ADBULL, 0x91AEE1202EBE0E2CULL, 0x60F16FF9ABCA1288ULL, 
            0x0220ECFE4ECC7D27ULL, 0xF246865E511EFCE2ULL, 0x0C87AA8C369E03DDULL, 0xF992F5DDE21FA0E9ULL, 
            0xEB4A065AD438BF4FULL, 0x8BB8D1DBFD36455FULL, 0x631C7673530C8C82ULL, 0xFD03B1E478FA3155ULL, 
            0x4DBC659A0246CBA7ULL, 0x3B62AA3558773E8FULL, 0x9F4F6349ED71A53BULL, 0x83C00131245EAD89ULL, 
            0xBEB3FD5671D1FC7CULL, 0xE45FFE27A34A26B5ULL, 0xB39EE458B9F582FFULL, 0x0C96AA8BB01458AAULL, 
            0x6BA0130D4A0DF8D4ULL, 0xB31C50780D9B43F5ULL, 0xD7D75487546B88D9ULL, 0x38DECECB71AA9F1FULL, 
            0xE6A96AFDA955D30EULL, 0x03DC02D074F0B620ULL, 0x1CB5E4DD9CF9925DULL, 0x3E0E9CE258F6D840ULL, 
            0xF00C55D49F4682EEULL, 0xEBBA02DAB2873199ULL, 0x4EEB8130924D530CULL, 0x407BFD4C9F800E22ULL
        },
        {
            0x84BCC4D1C5A24E61ULL, 0x9F724F281ED7E2F7ULL, 0xAEDC39477DE93A85ULL, 0x890D3D197614C584ULL, 
            0xA06F291A46B764B6ULL, 0x830C11B138A22ED0ULL, 0xE416F333EBDB54D4ULL, 0x2DBD9EF186E14000ULL, 
            0xAC08576985B4051BULL, 0x2B5C6097644D3950ULL, 0xE76EA05FE4358E80ULL, 0xD2CBF4E27C48B944ULL, 
            0x784D6239E41AD5DEULL, 0x81CB85B2DAE80EBFULL, 0xA4150608F97B48CAULL, 0x7579E85E7C5E890DULL, 
            0x959AF10C42F6F065ULL, 0x9EC2F9993D1AE8E2ULL, 0x513E6903AAA62ADFULL, 0xEDAA5701CC6418D1ULL, 
            0x2FF438697749B582ULL, 0x6CC842976FA2CD03ULL, 0x4EA25041448D2F47ULL, 0xBC46B723F844847FULL, 
            0xE3BE73CC65489214ULL, 0xD0A527DFECBB93AAULL, 0xDEBF3ACC252349DDULL, 0x6040B07CED2E4EB6ULL, 
            0xF4DE719B001B24A5ULL, 0x9E11458049A036A9ULL, 0x5F03D369B7D2EE86ULL, 0x18BEDBE383F010C6ULL
        },
        {
            0x0D31D0E52C50B807ULL, 0xCB0B2BA55AEE8A7CULL, 0xE73453455DD161A3ULL, 0xFFD3D22288C4FCE5ULL, 
            0x6CE2948EF52B3EBDULL, 0x2105E2B6B05D6BD7ULL, 0xA210B9EFB6B92006ULL, 0xE0F7983B3D8D6D38ULL, 
            0xD62516DDC486576CULL, 0xCC86DD716C4F1B77ULL, 0x0B40DC3997088632ULL, 0xA7635C460361A201ULL, 
            0x74C79B48BB890A28ULL, 0x21027E973237FF57ULL, 0x9FD3A72B108CEBBBULL, 0xC9E78268E5403D65ULL, 
            0x8B895886C7DCEC59ULL, 0xB866D4AF68236A5CULL, 0x367F3386C889D2D8ULL, 0xFB33CBA1537A1952ULL, 
            0xBFA0A4103EF0A591ULL, 0x5FC7AA3F2E770A00ULL, 0x6EC1C90EE67244E8ULL, 0xFDAC5A7F3EFDB97EULL, 
            0x077E848BF3F6D65DULL, 0xEB5888199CAB1FCEULL, 0x40F7CC452587BE9FULL, 0x5827C847B699F7BEULL, 
            0xC86A80E66EC569A4ULL, 0x9076F51C5A859E1FULL, 0x5CDC56C283A26442ULL, 0xED52CBA0369A6748ULL
        },
        {
            0xCD74D85160F466A7ULL, 0x417EC940B6BAAC0CULL, 0x55BC0BDE247A6BF2ULL, 0xBE08ABE01ADA777CULL, 
            0xEBD34A4D59D11E84ULL, 0x4B88614A1145E231ULL, 0xC3BEE17825C66129ULL, 0xFD29F3EB045A53B1ULL, 
            0x96796387C5E17391ULL, 0x6AAE99549D1A33FDULL, 0xA29D0D026CE73AE8ULL, 0xF22A6D6540C7577EULL, 
            0x4D0AC614088C13B5ULL, 0x811CB1B2733179A9ULL, 0xC17AA6A6E9DF00BBULL, 0x44E6E6F5527C63FBULL, 
            0xD0FF875127F9372EULL, 0xFEC44AFED4DEC32FULL, 0xB1F2EF4E7F2AF092ULL, 0x3155259D253D9B4AULL, 
            0x6AD58BDFA767AFE9ULL, 0x344490216FD5AF63ULL, 0x104B644A92C6A003ULL, 0xDBFE2DEF1A0E1C33ULL, 
            0x199B0FA6FE536DEFULL, 0x73125DFFEF2D1B6AULL, 0x389527B663035DEFULL, 0x0756607761707E50ULL, 
            0x3259A626FEF0AAD9ULL, 0x9C1452A5D532C71EULL, 0xAB73967D1D1DE5D7ULL, 0xA173D640D83C9D27ULL
        },
        {
            0xE247BA2282813BBFULL, 0x9A948C38EAC6C3D5ULL, 0xED7A07A49A213F21ULL, 0x192A0FE7FDC09351ULL, 
            0x70CBBA56B822D6ACULL, 0x7EF43206EC58066DULL, 0xB604CC428AFDC9C8ULL, 0x775E5FA9E93A7099ULL, 
            0xC2EABAA3EE6C7EFEULL, 0xD2F292A83157457DULL, 0xDC26C2F644D87D07ULL, 0xBDE017A69FB0ABCFULL, 
            0x92E7AE714D9CFF6EULL, 0xF4FC9AF06BF3FB32ULL, 0x345ED0612533F33FULL, 0xA617B259B8EAA1B2ULL, 
            0x577C59BE4A727CBAULL, 0x9C18944638F77E19ULL, 0xB5EF146BFF4506C1ULL, 0xE5B42F59B503CDFEULL, 
            0x0EA5A4F9DE76B897ULL, 0xC0753BDD8A0D911EULL, 0x31A17D3D58F9A5CCULL, 0xCDAA0ACCBCEEF797ULL, 
            0x1AB28DE7F248F7DBULL, 0x8A0D396C30B0E493ULL, 0xEC0B1E6A07220FA1ULL, 0x6B71BAF79A23CA79ULL, 
            0xA8457D68D6824728ULL, 0xC2226B9A40E0DAD0ULL, 0x8E7A4628F8CB9BFBULL, 0xF05AD91B2D60EAD3ULL
        }
    },
    {
        {
            0x8E479550B05E097CULL, 0x5B3160190B6E7048ULL, 0xEC042C1EBBFA1189ULL, 0xB0F35EC23804AFFAULL, 
            0xFCA4A00D0D40DC8AULL, 0xB59E2C8313906A3EULL, 0x620578BF4CB71A28ULL, 0x6F53EAA75F1C7309ULL, 
            0xA185872CF88684CFULL, 0xA130675C5AD1FDA7ULL, 0xF3DE0A25D8A8F4E5ULL, 0x4B60A24CC7DBC724ULL, 
            0xA29109D18F7ADDC5ULL, 0x58D0718087783812ULL, 0x7A3E702DF79BDE26ULL, 0x0A7F072F93A2513EULL, 
            0x8BEB2DD54E2193DAULL, 0xAEF2F2AE19C69E8EULL, 0x5C9CC8319DF90F11ULL, 0x8AA8A869D617AC4FULL, 
            0x2D14866819F30766ULL, 0x9D86E4EB1DB89C10ULL, 0xDD8FB64B138F5BA1ULL, 0x008CC1F4B560A719ULL, 
            0xC419E7E2F8E4A95AULL, 0x1F26EAFEC21A479FULL, 0x502973FB1A9EC3F7ULL, 0x0C9F8CC39C4526BFULL, 
            0x69DA56862896A48EULL, 0x52FB82B83FF3F602ULL, 0x54889ED5E4754D52ULL, 0x000E0AFA07B87A92ULL
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
            0xF8DDB526FDF1B228ULL, 0x9EAC21AB4E21D543ULL, 0x8ABA42A1CC0285FFULL, 0x01A8B65525AC7CDCULL, 
            0x0D5B9D1C14ABDF30ULL, 0x44B0118C50CEE8A6ULL, 0x86D27B23F8693AD0ULL, 0x0E8C0CC76A637122ULL, 
            0x08C974A2A004C75FULL, 0x480A2A6BA1B83279ULL, 0x1278E2FB6EFB3391ULL, 0x438BEE07562F2FA4ULL, 
            0xE1C3CD451A602606ULL, 0x0C7D52BBF488A598ULL, 0xAC90C894AC758170ULL, 0xB7C29D21ACEAB193ULL, 
            0x8117DB7B96219CBEULL, 0xE04D35EF008D9FB1ULL, 0xA4A1B3E5060D2F5DULL, 0x91A7552B7F57FADAULL, 
            0x547976BA6643C897ULL, 0x9F3C6C1D5D755C6CULL, 0xB38AAF97C0461F41ULL, 0xE01BD070D7F1E1BDULL, 
            0xC36401073E600A26ULL, 0xFCEF6274E25CFC90ULL, 0xDBA7F2D275B66103ULL, 0x4ACDCAE7695A8556ULL, 
            0xFCE85CF5A94F36F0ULL, 0x1B62304DE8081FD0ULL, 0x5154A1648221C2D0ULL, 0xB7D3DAD5D5C13F42ULL
        },
        {
            0x0BF971B37C8AB2B2ULL, 0xA7C6C2CAAB49BC65ULL, 0xB2CEC8647B774315ULL, 0xEB2DB61C83E0823CULL, 
            0x2500CF7D33231DFAULL, 0xDFF052A465FF8BE8ULL, 0x2F41F54159508B20ULL, 0x6287F9E612F740BBULL, 
            0x6DE8428E19A7FB13ULL, 0x1FB0C4393C9A57FBULL, 0x93C2D0C3C5663074ULL, 0xE820AB4A358A1F60ULL, 
            0xDA9AF205722B716FULL, 0x35D17BBBA644ADCAULL, 0x3FD3E4A84183A2FFULL, 0x0B22473DFB55B6ECULL, 
            0x4DAE7EF06015169DULL, 0xBD2790931797F9ACULL, 0x80ECB74644FD3926ULL, 0x597DDE0AE850294BULL, 
            0xB24ACA1506C71583ULL, 0x2CFB22997B1E18F6ULL, 0x2AAC8D4D653956A0ULL, 0xCAD44F555411C858ULL, 
            0xFC46B804B6E33016ULL, 0x9AFF41C87451956AULL, 0xB1EC5A5281AA71A1ULL, 0xB160391175478E0DULL, 
            0x2A50563A8136F354ULL, 0xB9BC44E838CAD1B0ULL, 0x55B69259F5E8EE76ULL, 0xBC44F98DB6AEDA47ULL
        },
        {
            0x8F178CE12D4428EFULL, 0x7F33AEC180A67219ULL, 0x757A7680297EB5AEULL, 0xEA4606CED2578E0AULL, 
            0x17AE872EEE4DFA3EULL, 0x81C504583C84BA71ULL, 0x8AA98B22B3AC8DA0ULL, 0x98A068865A7BA7D2ULL, 
            0xEB52DE611B0CB1E2ULL, 0x32B77C43B72CA774ULL, 0xEE180FAA0CE6F8BCULL, 0x7DF1DD9E54885DF1ULL, 
            0x5B9285B87F329237ULL, 0xB409B2DD6623AFCAULL, 0x1D2D9F9CE4C2DE08ULL, 0xC145917CFF7C3540ULL, 
            0x09A2D6D5ACC53407ULL, 0x9E857CEE6A9831B6ULL, 0x857A2875462DCA51ULL, 0x71656A3340355448ULL, 
            0xA1A150E82987389DULL, 0xE03ADC8037824A85ULL, 0x4BED27BE5A5F595CULL, 0x1ABD7E822264F783ULL, 
            0xD43F1418A65C7F0FULL, 0xA902B00D5E3445ABULL, 0x7D3A92EFC942F9C1ULL, 0x8E46553155308DE9ULL, 
            0x13723BB77EF26181ULL, 0x7C1931F7087BED31ULL, 0xD49254218FA91BB7ULL, 0x01DB53AEE6DA3518ULL
        },
        {
            0x5012A46AE12CC8C7ULL, 0x0CA1C789E101AEEEULL, 0xF73841D910966D8FULL, 0x6EBAA1FAC3B43A27ULL, 
            0x6B82AEA59A34ACEBULL, 0xF0021D399E043E6BULL, 0x5AE1D47E18DE9162ULL, 0xF1A5B0D2B99E2A24ULL, 
            0xF699E518BE9D17A9ULL, 0x42930C5CB465ADC2ULL, 0x46FB32BCDED98BD8ULL, 0x7F9EFCA73826328FULL, 
            0x67A86170F68B4504ULL, 0x3C4757E463E00399ULL, 0x3C9023C74773E40CULL, 0xEDF3A00D00644B85ULL, 
            0x9D9F79EBE933B041ULL, 0x22D423A269F5E659ULL, 0x22491AC56CA074C1ULL, 0x02B2902569912E45ULL, 
            0x7693F24509D0AB92ULL, 0x53E7A3D586A2286DULL, 0x497465562835446BULL, 0x0B6A82A7984AE6A8ULL, 
            0x874215B8A59ABD09ULL, 0xC8F9CED3681F5762ULL, 0x0A5B209D85D75991ULL, 0x7E191DAE95E79586ULL, 
            0xD85FF3F7B41DD960ULL, 0x444B9D7D7FAEF725ULL, 0xBE32D07227C1633AULL, 0xDEBD91277962D0BBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Pollux::kPhaseHConstants = {
    0x1930000F0A17BAB5ULL,
    0x1FBAE5596210418BULL,
    0xDCC56E04AC598E95ULL,
    0x1930000F0A17BAB5ULL,
    0x1FBAE5596210418BULL,
    0xDCC56E04AC598E95ULL,
    0x80C9342093E34895ULL,
    0x2B03C4C64AB32F81ULL,
    0x81,
    0x66,
    0x7C,
    0x41,
    0x5D,
    0xE3,
    0xE1,
    0x69
};

