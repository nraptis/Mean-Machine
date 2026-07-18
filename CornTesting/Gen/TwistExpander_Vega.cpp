#include "TwistExpander_Vega.hpp"
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

TwistExpander_Vega::TwistExpander_Vega()
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

void TwistExpander_Vega::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEC3299C29525A078ULL; std::uint64_t aIngress = 0x9B058342DE07B4A4ULL; std::uint64_t aCarry = 0xB377F658EEC8206AULL;

    std::uint64_t aWandererA = 0xE68A5A9480EC8A7EULL; std::uint64_t aWandererB = 0xABE030D2ACFE4314ULL; std::uint64_t aWandererC = 0x9E591E9FA6912307ULL; std::uint64_t aWandererD = 0x912AF71DEF8010CDULL;
    std::uint64_t aWandererE = 0xBF75643EFB4674BDULL; std::uint64_t aWandererF = 0x8D6A192982BA058DULL; std::uint64_t aWandererG = 0xF0FD4418B56B1E4FULL; std::uint64_t aWandererH = 0x8CA3421A2D292B68ULL;
    std::uint64_t aWandererI = 0xD8A766268CF0D78FULL; std::uint64_t aWandererJ = 0xA20966360998980AULL; std::uint64_t aWandererK = 0x8FD8E934CF0F7DFEULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17473091794150413380U;
        aCarry = 15690886787228321818U;
        aWandererA = 16305124285141362190U;
        aWandererB = 9231890160834973262U;
        aWandererC = 9678691357105051786U;
        aWandererD = 16975648650228862474U;
        aWandererE = 14826361246050794744U;
        aWandererF = 15011092594788856739U;
        aWandererG = 12061567345782245350U;
        aWandererH = 12120300710847283887U;
        aWandererI = 12158625965738824229U;
        aWandererJ = 14509683666806833481U;
        aWandererK = 11134939264404165090U;
    TwistExpander_Vega_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Vega_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Vega_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Vega_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Vega::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x95AFBE836B38517CULL; std::uint64_t aIngress = 0xEC37D73BE27BDE05ULL; std::uint64_t aCarry = 0x92C180C47339857CULL;

    std::uint64_t aWandererA = 0xECFA01DE13FDAC73ULL; std::uint64_t aWandererB = 0x9DA550554F2236BEULL; std::uint64_t aWandererC = 0x8E57EBD50E61AC71ULL; std::uint64_t aWandererD = 0xCA39C5A4096E085BULL;
    std::uint64_t aWandererE = 0xBA550E2865002BE1ULL; std::uint64_t aWandererF = 0xD435090CB79BD2FAULL; std::uint64_t aWandererG = 0xE3DF8B1543F20258ULL; std::uint64_t aWandererH = 0xEEBF173601CD75F8ULL;
    std::uint64_t aWandererI = 0xDB31AE9A68D6CE2AULL; std::uint64_t aWandererJ = 0xD31F9CACE7B7F796ULL; std::uint64_t aWandererK = 0xE504B9B7FB14DCBBULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14366448704515603874U;
        aCarry = 10650454010740720850U;
        aWandererA = 12303824490423990295U;
        aWandererB = 17483350062884202054U;
        aWandererC = 13821111517458002923U;
        aWandererD = 17321415798165512544U;
        aWandererE = 11856582881588064998U;
        aWandererF = 11794854344970461051U;
        aWandererG = 18351709242321609508U;
        aWandererH = 11083691336532376228U;
        aWandererI = 11692661906585014621U;
        aWandererJ = 18339854930924581812U;
        aWandererK = 18342706117319024270U;
    TwistExpander_Vega_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Vega_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Vega_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Vega_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Vega::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x851333C81C887E49ULL;
    std::uint64_t aIngress = 0xC759057E80F903B8ULL;
    std::uint64_t aCarry = 0xD5E2CBA3C25C92A5ULL;

    std::uint64_t aWandererA = 0x80124BFC2C24536FULL;
    std::uint64_t aWandererB = 0xC56951D975A1B3ACULL;
    std::uint64_t aWandererC = 0xF9D13B64331108D3ULL;
    std::uint64_t aWandererD = 0x826186FA656A490CULL;
    std::uint64_t aWandererE = 0xB7BCDEABC9BFFD19ULL;
    std::uint64_t aWandererF = 0xFE0C0C18C67ACF11ULL;
    std::uint64_t aWandererG = 0x80FDCE63EC7C3777ULL;
    std::uint64_t aWandererH = 0x85FC2CD468A0C407ULL;
    std::uint64_t aWandererI = 0xD75B7001367D1F7CULL;
    std::uint64_t aWandererJ = 0xA6020698ACFA75E2ULL;
    std::uint64_t aWandererK = 0xC26E9361F1F9DE6FULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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
    TwistExpander_Vega_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Vega_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Vega_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Vega_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Vega_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Vega_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Vega_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Vega_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Vega_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Vega_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 33 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1785 / 1984 (89.97%)
// Total distance from earlier candidates: 58165
void TwistExpander_Vega::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1842U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 345U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1238U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1350U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1018U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 856U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 295U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 636U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 868U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1860U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1253U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1851U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1526U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 733U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1761U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1614U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 165U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 482U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 118U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 95U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 183U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 723U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1631U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 310U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 202U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 991U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 167U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 121U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 26U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 455U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1421U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1000U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1572U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1021U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 113U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 141U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 139U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1077U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 83U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1099U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 960U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 737U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 413U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1845U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 779U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1606U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 51U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 561U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1045U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 259U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 241U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2047U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1015U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 974U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 840U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 777U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1695U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2027U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1902U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 20U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 486U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1883U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 88U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1022U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1756U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1908U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 536U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1150U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1564U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1956U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2026U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 496U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1479U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1112U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 147U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 282U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 93U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 336U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1139U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1733U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1649U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1095U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1402U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1671U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1219U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1749U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1365U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 866U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1673U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 705U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1105U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1009U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1855U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1579U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 363U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1049U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1080U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 255U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 758U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 432U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 33U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1615U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1235U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1404U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 220U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 393U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 791U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1550U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1837U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1383U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 982U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 587U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 7U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1074U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 14U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1998U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1538U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 435U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1474U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 411U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 119U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 375U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 606U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Vega::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA54C63E98C2ED3D4ULL; std::uint64_t aIngress = 0x92818098294917FEULL; std::uint64_t aCarry = 0xDEFC30858D18AD4FULL;

    std::uint64_t aWandererA = 0xB7F86016C7CC63E3ULL; std::uint64_t aWandererB = 0xA5AB69F7FE09C4C2ULL; std::uint64_t aWandererC = 0xBE7310C5FDFE1CBEULL; std::uint64_t aWandererD = 0xBC3D5CB5E4D3DC4DULL;
    std::uint64_t aWandererE = 0xFCF0ABF20D143699ULL; std::uint64_t aWandererF = 0x9EDBD63118352978ULL; std::uint64_t aWandererG = 0xAF89709C68913DC5ULL; std::uint64_t aWandererH = 0xAEFA4181D6F1C43EULL;
    std::uint64_t aWandererI = 0x8769D20211B5D796ULL; std::uint64_t aWandererJ = 0xC1FDB716C0E54968ULL; std::uint64_t aWandererK = 0x8C633084227B1363ULL;

    // [seed]
        aPrevious = 15100251001718466778U;
        aCarry = 18208742002533616586U;
        aWandererA = 15719130172070422875U;
        aWandererB = 17279710824336137770U;
        aWandererC = 11185818601096086095U;
        aWandererD = 16772391372661285931U;
        aWandererE = 12545791342695380275U;
        aWandererF = 15806004004253935939U;
        aWandererG = 10956879207733506727U;
        aWandererH = 14961453006383918619U;
        aWandererI = 10149328550779019348U;
        aWandererJ = 16181172464023186643U;
        aWandererK = 16315453175197054234U;
    TwistExpander_Vega_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Vega_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Vega_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Vega_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Vega_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Vega_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Vega_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Vega_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Vega_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 33 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 17281; nearest pair: 447 / 674
void TwistExpander_Vega::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1786U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3425U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 738U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3328U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6165U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 158U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1071U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 600U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5750U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3821U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 743U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4840U) & S_QUARTER1);
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5389U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8111U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7429U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6886U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 902U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1250U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 934U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1328U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 466U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 837U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 257U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 483U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1254U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1934U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1697U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 489U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 641U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 714U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1795U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1382U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1642U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 575U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1463U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1654U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 33 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 17279; nearest pair: 474 / 674
void TwistExpander_Vega::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6904U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6303U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2031U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2161U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2873U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3629U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3678U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3664U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8128U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7390U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1912U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6413U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2151U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4133U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2095U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 214U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1894U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1087U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1807U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 547U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1941U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1110U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 942U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 938U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 816U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 252U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1867U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 254U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1061U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 203U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 567U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2024U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 935U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 411U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1970U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Vega::kPhaseASalts = {
    {
        {
            0x3C1054F11C0278B5ULL, 0x48A71C37DABC623DULL, 0x9E65F3A4D4C3BCBDULL, 0x217DB2F9BB5CBB0DULL, 
            0xD8BBA491190BCD50ULL, 0x1CF23EF88910D245ULL, 0x67437A44DDE2F69EULL, 0x47DC2A17A94BEEF3ULL, 
            0x278C2AFC23096C7BULL, 0x9582E87D7B04067AULL, 0x6206F770498202F9ULL, 0x9C2A02CDC6A472C2ULL, 
            0x4EF116068A854FCEULL, 0xBC3BDAA9562F013CULL, 0x6FF2E460A68A0D55ULL, 0x3F8E1DA8821AFE12ULL, 
            0x8306D63C4FDE5E3BULL, 0xD0CBF9C589CF4E44ULL, 0xB790CBD4833C2EFBULL, 0xDBF652B2A9E4CA4AULL, 
            0xDA00640CDE26AF6EULL, 0x97593D30F9350956ULL, 0xAE2921AA9E0CB7B2ULL, 0x0E40F8EF4ABF9769ULL, 
            0x26E6CCCAC1515E1CULL, 0x8F2225A907BA45A8ULL, 0x3C57BC7696EA8329ULL, 0x7593C5C9473DCD8CULL, 
            0x726AD01BD87BD2F8ULL, 0xCC29C23D1A36B994ULL, 0x222B8D41B6E3017AULL, 0xD674BD74979C2E74ULL
        },
        {
            0xE61A2915DDBC2EDCULL, 0xF5EA188CF350B0D4ULL, 0x1A8105A8182C2CFEULL, 0xAFDD763043B8EB97ULL, 
            0x4217F9DA8781B2F6ULL, 0x0A311F901873BF0FULL, 0xBA584744BD787D97ULL, 0xBF7CCEAE33D4AB62ULL, 
            0xB089881B3BA57659ULL, 0x33521975A2D64EB1ULL, 0x63F35D9D930A2CBFULL, 0x8913A901EA7BDB8EULL, 
            0xDB64DF3C2EDA4378ULL, 0x46D5376881AFD062ULL, 0xBE1B7221FAB0334BULL, 0x94F58344FDC34F71ULL, 
            0xF36B992541FF742CULL, 0x03E6B10CE269FFE7ULL, 0x16B977DEF9D1EBBAULL, 0xF7E171475D7D0E2EULL, 
            0x36DEBDB9BA4E07B5ULL, 0x093C81FE53151CF6ULL, 0x935FD2619A24D4CFULL, 0x0D110192A7BE875EULL, 
            0x031B906D1B08C352ULL, 0xE8238EE2C04F25EFULL, 0x6178B271BAE4500DULL, 0x0E8441E4B9570182ULL, 
            0x54CCC74E40C8DAE1ULL, 0xBDA19FF2967503A8ULL, 0x6A270536E5642891ULL, 0xFDC0945A493237F5ULL
        },
        {
            0x1A0886A4E540F6A4ULL, 0xFA765FEE0657D8A4ULL, 0xBA3F039C11B23FB4ULL, 0x0E13C57593E43ACCULL, 
            0x7D324D8CAC21D2C3ULL, 0xF80FD6F2892885D2ULL, 0xCFDD50BDA4D9CEA7ULL, 0xEDB68CB1BBD17008ULL, 
            0x4B63200571C71E67ULL, 0x816B17F4EBB9C2DEULL, 0x5E6729CC9751646AULL, 0x3D359DBF4B2A345EULL, 
            0xBB72C6746C92C001ULL, 0xC3F866C2ACD9CF2DULL, 0x227CC2099DE7629AULL, 0x1B2E7511C73224FEULL, 
            0x81678A498A7EC346ULL, 0x555D8AAD2522C64AULL, 0x9F4E4E3AC3743470ULL, 0x478A13BE32D55756ULL, 
            0xA25E689941C24C6AULL, 0x4271FAF60673F6EBULL, 0x12121C0DB29E7BEDULL, 0x2C21658280B2B093ULL, 
            0x6A738F7798E0A03FULL, 0x449DF4FF318F062DULL, 0x92F5B627AC5BC6FAULL, 0x21C391DCB0AA682DULL, 
            0xC564E9FD0591DC65ULL, 0x88FD15FBA7FE2F55ULL, 0x462A12FE01C7D3C4ULL, 0x88B0F8E42A4D6555ULL
        },
        {
            0xF5875374F9F018E6ULL, 0xB9D0AACC4A8D7483ULL, 0xD0FBE057C2AA00D8ULL, 0x968D3A47E7BB3915ULL, 
            0x688B0E9A636B4034ULL, 0x8E01BC4D97649DB5ULL, 0x7981A8259FE5E915ULL, 0x05C1B0F73AF6A756ULL, 
            0xD6AE68EC27DE828BULL, 0x82759AA9D440C475ULL, 0x8AD3CF5BC8F382FCULL, 0xA483C3FFD84EFB86ULL, 
            0xB6B2FA5DB8B921DDULL, 0x45A4D85EF71CB58CULL, 0xB24AD3418B54DB71ULL, 0x6947B3B65E008948ULL, 
            0x7D56648913A17BCDULL, 0x93425B37BA917CA6ULL, 0xECAE8A895A75FF75ULL, 0x91214A5E02E65024ULL, 
            0x68CA46F1BFC4A79DULL, 0xCA04D863725C96BAULL, 0xFA620F479E842653ULL, 0x373BBAFA41DF5A0EULL, 
            0xFB837793A3A1A3C5ULL, 0xB7597073CF47A81EULL, 0x11E36BC5775F0613ULL, 0x4C849DECD8762AFBULL, 
            0x25A75066B0C22261ULL, 0x3810603683FD2D53ULL, 0x80ACEFB6FDD925DEULL, 0xD0B421222B08B671ULL
        },
        {
            0x1245FD9B2181D9FEULL, 0x66D54F4A94070A08ULL, 0xD2D33111E0C4391AULL, 0xB0036E47C2187205ULL, 
            0x93FEC43D4CE18ECEULL, 0x175CE6E4D8EC6FB7ULL, 0x7BA07389DD8015DFULL, 0xEE67882CFD7C9342ULL, 
            0x1A9E28E585678D85ULL, 0x71BBBBCB655FFC0CULL, 0x71768FEE10B0EABFULL, 0x05C9E7227CF3A348ULL, 
            0x3F1E812E9A726D49ULL, 0x48B42B54C8DA6F3EULL, 0x04701AF37DB6D9EDULL, 0x2DB2F2444779D200ULL, 
            0x70801F2EA0A9EBE1ULL, 0x175E91A93E9DAEC6ULL, 0xD8A396414DAAFFFAULL, 0x83D78940A0E594C3ULL, 
            0x9E4B18C3AF0BC220ULL, 0x058E3F2A031B7591ULL, 0x4C01911ECC2B14ECULL, 0xBC28A26EC60F8C2CULL, 
            0xDA18357AFEC83A05ULL, 0xD147965E3E0CBA8FULL, 0xE06BE5C06F058459ULL, 0xEE16F7AD2914139CULL, 
            0x85710A867994813FULL, 0xE6586C99445850F3ULL, 0xBC074D6C2CD6DF72ULL, 0x5691CBC29492229DULL
        },
        {
            0xBA8C4D63B56E1EADULL, 0x5E49BE4111D81679ULL, 0xC66E6D2795309DE1ULL, 0x13FAD643E47BECEEULL, 
            0xEF19DE39322AF6E2ULL, 0xF141A377E1DA496CULL, 0x47E75F7325976F0DULL, 0xCE654545B4AD6AF8ULL, 
            0x39731DB28D3E429BULL, 0x9BCD544A69EF08C1ULL, 0x8F56ED6C5985EE35ULL, 0x117F521FF8B47D6CULL, 
            0xDEC159D843FA1943ULL, 0x792C3E8C83615AC4ULL, 0xA0125970A5AF10CBULL, 0x43B3EB18590A3660ULL, 
            0xA1A0965BC9F3346FULL, 0x7450D81F1A6FA22FULL, 0x32826438A2E27B26ULL, 0x6DE592818FEE8697ULL, 
            0xD85F11B91D4C6440ULL, 0xF9AFE12CFB34A43FULL, 0x5F5392D64D370C8BULL, 0x78E0929CF37BD2A9ULL, 
            0x101BA7CE91B835D4ULL, 0x902CD8DE2B5948A0ULL, 0x77FA35339F4AAEC9ULL, 0x1A0B41731A873B8CULL, 
            0x4A034D588236C875ULL, 0x34260B8D20661AD8ULL, 0x1F75A4594D71C2A0ULL, 0x177565A167A4DFC6ULL
        }
    },
    {
        {
            0x8A7AAD11CD181750ULL, 0xED877E3CF486E22DULL, 0x7A87FAC0F4C0A29CULL, 0xCD0420351A03F67BULL, 
            0x9BBF414937218B67ULL, 0xAAD2CA533D8662DBULL, 0x5B19B799986942DEULL, 0x9278653B6A0806A2ULL, 
            0x4F6FCB20E019F81CULL, 0x3D057F0AB7126B91ULL, 0x82DC38FE3488CDD6ULL, 0x06DE6C16F110CCFFULL, 
            0x425381A343A9ABE8ULL, 0x4365023E389AEF32ULL, 0x89F5AF9C4A1FEFF1ULL, 0xBF32326132BFEA8EULL, 
            0x217266DF11BC0EA6ULL, 0xFA8787BBB422991FULL, 0x47D0DD943ED10AD1ULL, 0xB16E7D680F20AA9DULL, 
            0x9AD634E188D27E22ULL, 0x67F0E180257AE2C5ULL, 0x4B34D2B15E5F34CEULL, 0x4215A8EFABDCC563ULL, 
            0xF5315DE80BD4A3D4ULL, 0x8506B8B87E40B881ULL, 0xEC53FE5F9D3A980DULL, 0xDA5A5E61A6EA7D86ULL, 
            0x931A61BE0098C8CBULL, 0x1AB93E7F82117091ULL, 0x0A601DD7CB162BE1ULL, 0x9C2D3F9AE0D5941DULL
        },
        {
            0xB85F02B6BB54CA54ULL, 0x3A048F1E785E13A9ULL, 0x13C8B21520016C85ULL, 0x00E80B0E77AE537AULL, 
            0xD1D23B4E9E71475EULL, 0x79A956B10C1819EDULL, 0xCD3EB84FC1228EB3ULL, 0x14A9ED051F7E8E5EULL, 
            0x1C0BD1E050F054E7ULL, 0xF6CF843A31A18F07ULL, 0x15B274A824C9FFE3ULL, 0x0EBD5D1E2C5C64C6ULL, 
            0x9CD224730AD028B5ULL, 0xA6CEEB37F683EC98ULL, 0xCF428C064BB53660ULL, 0x479665C587AF3780ULL, 
            0x8DCF594620CD541BULL, 0x1C42A13D0B15454CULL, 0x698F4F62415BAD2CULL, 0xEA11065F0E6DDD60ULL, 
            0xF84C828DECB01E8DULL, 0xB49975DC21D6C9AEULL, 0x6B08BF176062FAD6ULL, 0xAB1ABA8BCBFE8752ULL, 
            0x28AC48641A334042ULL, 0xF28C50E4DEBB9CB0ULL, 0xF6891080ABF5DE66ULL, 0xF20B6D9126756A11ULL, 
            0x933EE1C04CF6F586ULL, 0xD68EE029B157A62FULL, 0x55473B79F768CCBEULL, 0xBEB4FF421E5F7D9DULL
        },
        {
            0x6E6A2CE9DFAC255BULL, 0x8E1F5500597B9007ULL, 0x04E984AC99829590ULL, 0x3E75B47E048F3591ULL, 
            0xD9FF359CF27914C5ULL, 0x96E467642D140DF2ULL, 0x535154EB9B132668ULL, 0xB4307685A5D7A7D9ULL, 
            0xDB656CD27139A832ULL, 0x02F7F3974A922F4DULL, 0xC523EA52DF503F5EULL, 0x43C32D398E96A890ULL, 
            0xE1ECC64BF7DFC0F4ULL, 0x8A720F3946095C1FULL, 0x2AEDC17028E83506ULL, 0x5F17316B727F2899ULL, 
            0xB32D812D5B2AF219ULL, 0xAD70F151FE9A26E6ULL, 0x4B245C884DF86E87ULL, 0xDDF2782FD3588AE7ULL, 
            0x914AFA10B1F47C0CULL, 0x6B43287F1EDC547AULL, 0x41AF145119F0BDE0ULL, 0xBD64EE1280DDCB87ULL, 
            0x4C456C57C6A832E9ULL, 0xC5CBE603BBC94C03ULL, 0xB0EE7B3C3D0388E0ULL, 0x5E04507778D9BBEEULL, 
            0x2327DE979EEEA7B5ULL, 0x44CD282693E67849ULL, 0x30FB014603973D0BULL, 0xEB0F506FC2D6CD44ULL
        },
        {
            0xDF8F18AB3A0D2B03ULL, 0x59E9F790A6109063ULL, 0x8596408903E71228ULL, 0x5DBA0E9BDE15D4E8ULL, 
            0x2C08B15D8ADC9EA4ULL, 0x2FDC53DC074029E7ULL, 0x2B868CBF86848E88ULL, 0x87C082F19FF4D660ULL, 
            0xA6A3FD8EBE757B98ULL, 0xDFA9643D681017C4ULL, 0xF17C734817665EBAULL, 0x47C01677CA9B0AC3ULL, 
            0x6E0F54E08DB6AE24ULL, 0x8B963FB86E566923ULL, 0x5F190AC37FE36C0BULL, 0x469E45FA823AB06BULL, 
            0xFF0AABBE322B2CBFULL, 0xBDD71542D26842F0ULL, 0x0FCEE9D89E229D6AULL, 0x8D065295D3B229C6ULL, 
            0x9EF91F3C8945B39AULL, 0x9FBB33A30EED4FC9ULL, 0xCFDD3040F6B05BB0ULL, 0x09355256F01BE9FFULL, 
            0xFA3A77BFF1D82777ULL, 0x27CB9A0EA6E7E914ULL, 0x428DA1CFAED7E2DEULL, 0x9D4F4A7BDAA24FDFULL, 
            0x67936E929CB6032BULL, 0x82D20D0117C20B35ULL, 0xE333F51757C36947ULL, 0x50DB870BBE6FA8EAULL
        },
        {
            0xD6B0034151DD51B8ULL, 0xF153BF0C55F02983ULL, 0xA57A971B831F4332ULL, 0x439BA2E4E50B7BF8ULL, 
            0xC4CD56361AC0F241ULL, 0x0B50BDE902F67BFEULL, 0x0CF7A921679B7641ULL, 0x818B34564511C93AULL, 
            0xE4FD46135962A6E5ULL, 0x634008839AC763B3ULL, 0xCA4FE6D51B7E8068ULL, 0x5B4586082569F238ULL, 
            0x741A8BA7648F581FULL, 0x7678117281EC4D1DULL, 0xD80A2FE002281613ULL, 0xA8B691AB5598881EULL, 
            0x610A4C23AC02AA4DULL, 0x52474CAFFEFB57BCULL, 0x1A30794CF499AA83ULL, 0x54C52C70B450F426ULL, 
            0x4B6BC031E4A672CEULL, 0xA181439FA9E1EA06ULL, 0xF2607897EC663028ULL, 0xFC6EE3F7D7AB7D95ULL, 
            0x764EF1B08B8A13DDULL, 0xB7F9CBEAB463F037ULL, 0x2EA60DD279C7FFB3ULL, 0xA85EC539A13526AFULL, 
            0x5678FE8A0B8A292AULL, 0x98B771887357AE99ULL, 0x6C31B6C8CDEF7283ULL, 0xC9DA4885DE6CF483ULL
        },
        {
            0xD67BCCFEB7A17125ULL, 0x80BD2FFE012256B0ULL, 0xCE9432A1F80849D5ULL, 0x790B7D75F975D311ULL, 
            0x4182F6504DF1097BULL, 0xA6187C2F3257734AULL, 0xDE30F37429417ED9ULL, 0x7093BA15B26F1ADCULL, 
            0x52B6C0E99295F293ULL, 0xF0A08C7B59C97B7BULL, 0x2D4DDB68D8D47C79ULL, 0x58730CC8BF408B09ULL, 
            0x986F33D280833DBEULL, 0x1015484E32952775ULL, 0x5980531D0C0C6CF8ULL, 0x798523ABDE757269ULL, 
            0x7383E30BC3610530ULL, 0x0E155A37986890CAULL, 0xFB5D2EC46C04DA57ULL, 0xFCD6ED603A5B94ECULL, 
            0xEF17E6187FB452C6ULL, 0x2082192DFC504BF0ULL, 0x723CCEBD06109019ULL, 0xF6055AEC258B74EAULL, 
            0x7566E668EFE4DC6FULL, 0x462C1D1C71B245D7ULL, 0xDF717426A70171DBULL, 0x36CEDE21EF185406ULL, 
            0x3D66DDF35A16981AULL, 0xAC2B0C321672DEB5ULL, 0x284F1191AD72C0C2ULL, 0xEBD9325F6EFB0C1CULL
        }
    },
    {
        {
            0x97FC66B5EC734B25ULL, 0x26D3EED63E69FEEFULL, 0xEA50A853F6DD073FULL, 0x36164477DA10C91AULL, 
            0xFCB4482B68282C87ULL, 0x1545BC5FE6F68C24ULL, 0x16A1371974C71144ULL, 0xFAA258090F73176DULL, 
            0x18C43FD98205928AULL, 0x552D43CA061D5C58ULL, 0x6AE12D1035F0CEF3ULL, 0xE2EE8D18DCE6C56DULL, 
            0xB8DEC07BC380F9B3ULL, 0xF44E0C3794FF353AULL, 0x11494FCEC3ADD3A3ULL, 0x878B11A2981CD6C2ULL, 
            0xA4495E29719DBB8DULL, 0x98C45FF9F9477C0EULL, 0xA20A5A739E4F8A43ULL, 0x856602345A57C214ULL, 
            0xF6F7182AFB8C2E4FULL, 0x2ECA67B473994743ULL, 0x6F847DE26CE0987AULL, 0x734FA8FAD9A35982ULL, 
            0xD23671E46C1DA0B0ULL, 0x801208C571863BA4ULL, 0xEB644DCB4F5B36C1ULL, 0x111CA3A100A33362ULL, 
            0x198AF4F927AAFCDBULL, 0x8AE0A8E35E58F098ULL, 0x4D5FCD1AABB5CFD0ULL, 0xFAF846E111027D44ULL
        },
        {
            0x8B30FFF390DCB568ULL, 0xE42CFF7042250F28ULL, 0xB905F07DF9C4BE65ULL, 0x5981B225D94FC1F3ULL, 
            0x3B2BF87C3E8B2080ULL, 0xF7EA3DC935C27A56ULL, 0x462A676B4325FFEDULL, 0x3AB15747C48EB4B7ULL, 
            0x5D508905CABEF5B1ULL, 0xC3D4A07784DCB8BEULL, 0xF299E1FC49B07ABCULL, 0x128AA0107B3BECD9ULL, 
            0x89BEDB27F22C5EABULL, 0xBB247EABC64CF58EULL, 0x95A2D60DA14DFF49ULL, 0x6D40A37863BB51BEULL, 
            0x900C9E4DF9FAFC90ULL, 0xA8DD809875243FA6ULL, 0xB9D6A14804C3D98FULL, 0xB6E2F5D22ECA722AULL, 
            0x031472ABE5B23A6DULL, 0xABF86B5CC2638F3BULL, 0x353370C8D1AD2796ULL, 0x2B39F7564F342045ULL, 
            0x92B5BD9B2E236B70ULL, 0x559EBF999EDAD058ULL, 0x60E377164AA502AAULL, 0x0C921B0FB8B725ECULL, 
            0x925D3BF533475852ULL, 0xFBA0553EC6513953ULL, 0xEF7314BF6FFD280AULL, 0x6F0E2C28F628B8D6ULL
        },
        {
            0xC390A2A6624A4D66ULL, 0x35D975FE374CDE8DULL, 0xFC7171F49CA2417DULL, 0x8D493C128111387BULL, 
            0x722637788E884E79ULL, 0xAFF09F76C4758F50ULL, 0x6CF2F5F44B5CB3E3ULL, 0x57C325A1DA5A6203ULL, 
            0xC44C313F93C33EE7ULL, 0xEDC5F84BD0C1B5D8ULL, 0x8E55E44E5010C558ULL, 0x654FE3C64439B55DULL, 
            0x536B501B473DC715ULL, 0x9F050C88555DCDB2ULL, 0x8A897CC22AC5BE3EULL, 0x750AD10D6A34716AULL, 
            0xA035E7798B8AFAA8ULL, 0x16114D0DBA744703ULL, 0x5F96AC606470EBCEULL, 0x0A251635DC8197D0ULL, 
            0x5071B44F51775153ULL, 0x3DE0782CC23DF131ULL, 0xDB0A19134C65FD74ULL, 0xF34F16FC9555D1ACULL, 
            0x574A01EDE052BFB9ULL, 0x01103F65EF699A1AULL, 0x5E902331CD2CC1E0ULL, 0x55BB1DD78420A052ULL, 
            0x72F914E213F2F713ULL, 0xACD161D6EB9EEAECULL, 0xAA91E0124C9C0336ULL, 0x8824844410C67179ULL
        },
        {
            0x177227E4C538AAAEULL, 0x39230CED71165C3BULL, 0x0791F747AE9AC9CAULL, 0x9E1B6747D85B7F59ULL, 
            0xD4618A4D226D8CE9ULL, 0xA38C00BAB990D330ULL, 0x34716E9AD21D34C6ULL, 0x4803F17B1248739AULL, 
            0x9C62D2B99D90BA9CULL, 0x6C27B10BC8152161ULL, 0xAC379A917F3D33EEULL, 0x7675FAC5A27A5768ULL, 
            0xAD0D4BE6A8A67FB4ULL, 0x6C3D342EC3AAAA9CULL, 0xEC17F7C1A2CFEB49ULL, 0xDFC8E9D1387C3529ULL, 
            0xD29159A69D6E28CFULL, 0x01191A31A656807FULL, 0x2F0540E688B9FC3CULL, 0xE4317938A9BE2D61ULL, 
            0x949B5F6CEE84D276ULL, 0x2BB0E301E6DFEB41ULL, 0xC8D4358862B95F94ULL, 0x5B0134953B8ECC73ULL, 
            0xC714545DF779A5A3ULL, 0x0AEDD916D2DF15DDULL, 0xF3EC4461FC1A3F79ULL, 0x44CC7E8F6300297FULL, 
            0x2E084620B80CB134ULL, 0xCED41DA125E74037ULL, 0xC668821AC7A62E42ULL, 0xF03730D878AB53B3ULL
        },
        {
            0x3B3500FCB3527D42ULL, 0xF9B4632988A44C9FULL, 0x53B4C4AD7D7FE714ULL, 0xC304EF60A787FDEEULL, 
            0xFE77922B41E782A6ULL, 0xAC57A65682D3B7F7ULL, 0x2A7E6E9C9F674596ULL, 0x59351F0E39564AEDULL, 
            0x5EEF26BC98B14344ULL, 0x6A7431AAFEED99CDULL, 0xBF51AB7262DA394BULL, 0x67E61E1176EC58E1ULL, 
            0x63983B9F831C75FBULL, 0x1064F40EB75CCB7FULL, 0x3D91186A07BDAA4BULL, 0x31DB47920B70EA96ULL, 
            0xB7295B2CE87F0C1DULL, 0xA990340C8BD93A2FULL, 0x1B23FF599ED79FD8ULL, 0x281568AF19B485A1ULL, 
            0xAAB22B228F822800ULL, 0x03769C3D069AB999ULL, 0xEC2707533070A4F4ULL, 0x8B05D5C12E5AA6D5ULL, 
            0x69A5C08752B51398ULL, 0x6D294F92F98CBE6DULL, 0x4C4E3CF0805DF61FULL, 0x4503CFAF5093F7BAULL, 
            0x1B05841D15006A07ULL, 0xFF7A56EDA1139006ULL, 0x8697841F4815FEE5ULL, 0x8A96ACF1A4869D22ULL
        },
        {
            0x228AA1B74D0C697CULL, 0xC86DCCC895D90CF9ULL, 0x682A54BAFD28BEB6ULL, 0xF3E6D6926F992071ULL, 
            0x9BAA47EECE49026EULL, 0xB8A2C3FA9082837DULL, 0x69135D9D97416066ULL, 0x7C47CEDB14DF30B9ULL, 
            0x88BCACF3A4398F90ULL, 0x15E1CB2E1E8A0EA0ULL, 0x37DD18FD8E1C0F5FULL, 0x3D6AEED704087962ULL, 
            0x25E85AE47BB1CB57ULL, 0x7AC449BEB64632A2ULL, 0x1CDEA179BF2E8161ULL, 0xBAB1F7F9DCE6A6B2ULL, 
            0x3DEACA32E29B57E2ULL, 0xC5C7F331D10FFC75ULL, 0x85E6998A47792939ULL, 0x516BCFC22653E7B4ULL, 
            0xAA732F4A29C7893AULL, 0x7D9DFD6261CAC393ULL, 0x7F18A67763820056ULL, 0xA84F4E6DAF0FE8A1ULL, 
            0xC960022A61148EB6ULL, 0x4AA2C55F331450D7ULL, 0x7F8920F28BAA0FBCULL, 0x3E49B2F610988DFAULL, 
            0x725626BC1B66A0FBULL, 0xD4053E129D581802ULL, 0xF0D2642C4CF8E152ULL, 0xC3E708D3AD6B0251ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseAConstants = {
    0x22A495977C4B02BAULL,
    0x9A7EA899CBBAFE08ULL,
    0x062A0D1B0CA1144EULL,
    0x22A495977C4B02BAULL,
    0x9A7EA899CBBAFE08ULL,
    0x062A0D1B0CA1144EULL,
    0x9520878ECE5D5C72ULL,
    0xE2A5232182A5BEC9ULL,
    0x5C,
    0xF0,
    0x18,
    0x0A,
    0x01,
    0x5F,
    0x97,
    0x97
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseBSalts = {
    {
        {
            0x60D351DD4B456BAFULL, 0x008CC39F7A54A699ULL, 0xC53E70EE186BF81BULL, 0xDFA2C8B2441FED14ULL, 
            0xF7293FD4FEDFE76BULL, 0x7E39FACFA7C0BC6FULL, 0xBEB9047173CB448AULL, 0x68694CAB030A3C4BULL, 
            0xA6562A96E67AF6BEULL, 0x7595896BB4D22E05ULL, 0xC4FA605EB1C1F036ULL, 0xC129E64A0B019DA0ULL, 
            0x47014F980D00EF2BULL, 0xF2BA9860752B797AULL, 0x44C30A912791CBDDULL, 0x1267D10A00769B26ULL, 
            0xED3A0FA11B93B865ULL, 0x67DF602B230BE8B3ULL, 0x284E394855A2282EULL, 0x4B0DE3FA0D923812ULL, 
            0xBD11B1CC8C21E6C5ULL, 0x4357126AABCC1709ULL, 0x037E64DE39FEC0EBULL, 0xE9325623AFDB2471ULL, 
            0xA287B47A2EC304ECULL, 0xECC65344C43E76E6ULL, 0x145D0352AA3A114FULL, 0xBF1F544EFF7925E6ULL, 
            0x8640D3596BAB2816ULL, 0x9DC6B94008D280AEULL, 0x829A3AEA3EEB7C4EULL, 0xB03906CBB251B3B2ULL
        },
        {
            0xD3623A1130976073ULL, 0xEC523EDEFC220E77ULL, 0x9E7CB6BE578CCCEDULL, 0x1C8C60A232AF2348ULL, 
            0x75B5FE215048C145ULL, 0x199B44A2ADD99064ULL, 0xCE9734BC3CE67AD8ULL, 0xDF9949C931E1CDCDULL, 
            0x3B1550CCC7F9301EULL, 0x702B4778747AFEA6ULL, 0x01326391479299E5ULL, 0x0044A8C6DC2EA9B7ULL, 
            0xB96703F606C823B7ULL, 0x599805FDC0A38219ULL, 0xFD78C5AE6AE13ACFULL, 0x4E2B6958F6CCB1E5ULL, 
            0xB39210673E7E498FULL, 0xB399B4DE8682553AULL, 0x47A7E6CB599CF774ULL, 0xF08082EA7E0D651BULL, 
            0x74498202114E1893ULL, 0x35447FDD48A99E93ULL, 0xF8C5FEC541371B80ULL, 0xA273B55D64DAD933ULL, 
            0xBEF00CC1DEFBBF5EULL, 0x2D3BC28DF1694C84ULL, 0xC5821456FCA8D44FULL, 0x5D33F85FB18CA74FULL, 
            0xAC165088D699C6ECULL, 0xB01D70B91F1FB245ULL, 0x91D3D492D461C19AULL, 0xD833F3AA2A6013AFULL
        },
        {
            0x674CB707AA39EF05ULL, 0x6DDC7AFE35C947F4ULL, 0x3AB76186043A951FULL, 0x2A34454F28DC2A61ULL, 
            0x575ABB54B888622FULL, 0xC21B3E3E020B7EB9ULL, 0x13AC05A7F81BC721ULL, 0x0C3D344FD0F44493ULL, 
            0x18EB1BFB915CFFD8ULL, 0x6051E37B6AC30E61ULL, 0x90461D071C171F51ULL, 0xB7415B05D7591FB9ULL, 
            0x2308B5DAB3A839A3ULL, 0xCC2938BAEB09A3C1ULL, 0x159E3AC07BA75D7AULL, 0xEFF2EA0FB6DA294CULL, 
            0xFC96EB9D48E36762ULL, 0xBA383EDCA66C9946ULL, 0x5D4DB10794AC98FBULL, 0x3191804397E0C73EULL, 
            0xBB44EDB0476A58F3ULL, 0x951B6BABACD467CAULL, 0x45262B03F054D9E7ULL, 0x123407757599A1A9ULL, 
            0xF9364E1A3F92B7FFULL, 0xD000896A9E171AFDULL, 0x7D47533D0A258609ULL, 0xFF89FB80E8CE3F1FULL, 
            0xB84CCEDA0995F8A3ULL, 0xA86D54DDB8389C9CULL, 0x0BB917CC75FA614FULL, 0x3F428BAABFC0542CULL
        },
        {
            0x46CB4220076B2386ULL, 0xBEAE1E4DC827DB05ULL, 0x2774E6DA0006D02DULL, 0x69AC7FABED9EFC98ULL, 
            0xEEB0071C678FD0F9ULL, 0x510A6E5C582CF85AULL, 0x52C123E1FDB29BB4ULL, 0xA7E8C87BD141C351ULL, 
            0x92E7A029B648CDD9ULL, 0xFF8EC82EFF205C4EULL, 0x1E06D1A2923825A8ULL, 0xE89E6A22BABA907BULL, 
            0x17B089DE2820B32FULL, 0x16700092F60D965BULL, 0x0ED57A7959466C2CULL, 0x2226D201A831342AULL, 
            0x71C625AE92C35978ULL, 0xA82C1C62206366D5ULL, 0xA81C8B5350E5BA48ULL, 0x49A74F72CB8D7B64ULL, 
            0x6B98CFCFB2D32EDEULL, 0x838FF885B659803FULL, 0x59D032FA1FD987EAULL, 0x55A9A6CF43E04E58ULL, 
            0x62B850871C50AB75ULL, 0xE71F10E99ED9CDD5ULL, 0x5161BA0BC8B29935ULL, 0xBEBC6F4CCCFC9633ULL, 
            0x2B4456EC1FF6D5C6ULL, 0x38F991B4D8A193DAULL, 0x2176265F418339C0ULL, 0x622AB2AE66F17D5DULL
        },
        {
            0x4022F55197155562ULL, 0x5FF6659732514E03ULL, 0x451C924CBE4AE679ULL, 0x3268A8B139CAF50FULL, 
            0x3FE10BAD5B893AE0ULL, 0xDD1DAB32D1FCE64DULL, 0x498C94899759098EULL, 0xD265566167B92A24ULL, 
            0x46E0C7A05E8186C3ULL, 0x897C154EAD9BFDFDULL, 0xEEF6E1B3FC523597ULL, 0xE504EA16F2234D2DULL, 
            0xBE67901F6CEA54ECULL, 0x4C80E318B9C96A3AULL, 0x6C67DCD57DFD3EF6ULL, 0x13B5E37A0423C6DDULL, 
            0xD6EC34F42C4807D9ULL, 0x5B76D8E9A292E8FDULL, 0x61C6D369DDCA85D5ULL, 0x01BF84E70D100C4BULL, 
            0xC0D5A44DAAB98F9AULL, 0x6F33736E57A13C60ULL, 0xA4E9B8CA151D65A0ULL, 0x7718403FDAD3C6D4ULL, 
            0x1A352F6EF68ADEBFULL, 0xAB43984DB55EB5F5ULL, 0x353E8C21D721AD7CULL, 0x36A4F30711F41AC4ULL, 
            0xD0C8F4AFEF9F50E2ULL, 0xC7C4565956D31454ULL, 0xB28602A8F7F72BBFULL, 0xABE96F8631D66309ULL
        },
        {
            0xE50D22F3F021523AULL, 0xC7EBCAEB1D9CD84FULL, 0x217078803BC72949ULL, 0xDB974C038BFF17FEULL, 
            0x876A2A2EF85AE912ULL, 0x7ADAF85D2B99AA60ULL, 0x0A23155A1F5192B0ULL, 0x6119826D8CB0BD5BULL, 
            0x9746CBC30AAE0315ULL, 0xF89940C5727D6A53ULL, 0x8823DB0AC3C570EDULL, 0x72938FCF5CADF3A5ULL, 
            0xEE9D4CA86DF78212ULL, 0xCDACF9FAB0EED084ULL, 0x375A2C3E519FCB04ULL, 0x11CFF170C3DC1A7CULL, 
            0x8107877E6E299121ULL, 0x13B38A8D532F29ABULL, 0x3EB1829DBBAC8979ULL, 0xA584C20253808ABEULL, 
            0xC174433F92A3CE45ULL, 0x6D0E81978DA3481FULL, 0x6B641D770594BD9EULL, 0x719FDDF850A3C887ULL, 
            0x323FDF6DFB8E480EULL, 0x17E7B8F7D30EA433ULL, 0xC3BD6EE83BF3C7B4ULL, 0xD9BE284C8DFE19B7ULL, 
            0x53CE6C66E04CF95AULL, 0x7A1DA3671EC26384ULL, 0x98B7873888FAD248ULL, 0x5FB1890ADD5A4850ULL
        }
    },
    {
        {
            0x2D136C5DFC8BF941ULL, 0x4F6AA5E788EFC6A5ULL, 0xBA50C61D97F5D45EULL, 0xC1F06F9B7D93E9B0ULL, 
            0xBAA998142BF80E66ULL, 0x30E062F4580A1E47ULL, 0x420EF6413120E97BULL, 0x800EB741B8A3DB97ULL, 
            0xC339EECCF60FA8B1ULL, 0x85F24A3306B8F2B3ULL, 0x80395C0A6A69DD21ULL, 0x1DDEC8C08D46B204ULL, 
            0xE8A212C56268CAF4ULL, 0x59D92503A580DF41ULL, 0x4E64E8CB29DFB2E0ULL, 0xBC013EDF46AE828BULL, 
            0x534D313ADEEFB948ULL, 0xCAD14A466A0A4352ULL, 0xA760A8A2534D8BE1ULL, 0xF1753CA0C1253841ULL, 
            0xCF859C2E7B84DF82ULL, 0x1FDAB25CD809FD7CULL, 0xACC593FC91D600EBULL, 0xF50152CBB963E4DEULL, 
            0xB9F67B203B71B735ULL, 0xF014472E47ACF7EAULL, 0x835F9ACFE156872BULL, 0x7C4DA03C53DFD012ULL, 
            0x96E5090C2FEDA8D7ULL, 0x94DD997668549B90ULL, 0x3195B95741AABBFBULL, 0xA43B58AD8D91ED2DULL
        },
        {
            0xC2B4E472894D14AFULL, 0x79DF68D9EDF62DE0ULL, 0x7169E908067251ADULL, 0xA6E743D8C7847DC2ULL, 
            0xAC1D8561C2EE4911ULL, 0xBB3B81866699D566ULL, 0x33001526B3CDC406ULL, 0xCAC9508BC468F5C2ULL, 
            0x6FA1C13DD7CC9455ULL, 0x79E92FAA91555786ULL, 0x130F8CAA3A57BF31ULL, 0x08151D63AA0F172BULL, 
            0x0080787AE1729A2FULL, 0x538C6DD762DB8C0FULL, 0x2BC5D7277C4AE734ULL, 0xC700FB86D8C179F7ULL, 
            0x499576E6672C1083ULL, 0x20AD4E7A593A1548ULL, 0x53115B08054B00F9ULL, 0xF030A10259914FA0ULL, 
            0x9D8EF5D359094D97ULL, 0x5CC74C21963D3560ULL, 0x34100C12539E98C9ULL, 0x8C5C21C8BDE92533ULL, 
            0x2EA747C13EFDF328ULL, 0xC23A0D523F560410ULL, 0xD3C09354A1687375ULL, 0x00BB0E0DAF1DE1BEULL, 
            0xDA0FE32D1F79A09FULL, 0xF46B9E144FE5FACBULL, 0x2007B248D5E3FE48ULL, 0xA7668F43F158D015ULL
        },
        {
            0x6DB7F50085BB565AULL, 0x369C72BDDCFA73D1ULL, 0x60F560918B3DE967ULL, 0x4F2D23A7BDA937EDULL, 
            0xCBE3D261BEC35226ULL, 0x306023B6F871FF1FULL, 0xB248D2C6DAF5CA55ULL, 0xF32967CD3A3ADCF9ULL, 
            0xC08EB984E472EC29ULL, 0x8B5C85778EFD11A2ULL, 0x534406E73F5942B1ULL, 0x73D0B624F84A2E0DULL, 
            0x621C6382349B519AULL, 0xFC42114E898BDC62ULL, 0x64578DFFB6A0DF0CULL, 0x2121B6B0DE730DC2ULL, 
            0x07391E4D02A9044BULL, 0x3551785CFBF62E96ULL, 0x12C97A65C726B05DULL, 0x60B81FFA635B5304ULL, 
            0x6C6E6CA837A385FAULL, 0xC890B78A4E8AA5D9ULL, 0x0B169CFA9F282087ULL, 0xBD82F03BCF36690AULL, 
            0x8BC68E82A0493C09ULL, 0x8BB299F2586D5881ULL, 0xE163DCAC1F9B0914ULL, 0xD8F327BED10E3744ULL, 
            0x1D36EAB00ABD6095ULL, 0x15AAD813AAA5860AULL, 0x00248A6B54415B68ULL, 0x25AA25B56B9B8C60ULL
        },
        {
            0xC69C0661BCE1BEC5ULL, 0xA9FA32B531779F25ULL, 0xF6FA0B5CA3916D6BULL, 0x553604882BFFA84FULL, 
            0xDA9059264D739B75ULL, 0xCF93A20E68EE6838ULL, 0x3A76C6D8E134069AULL, 0x9D0EB1ABFFE097A8ULL, 
            0xB0B038B696E0A408ULL, 0x7D576A08C4C3F435ULL, 0x2853511C5E6BBF3FULL, 0x1C1B192767B7FC02ULL, 
            0x8D8F2A35708B4F9EULL, 0x46BFCD2EE6A9C32CULL, 0x6891F43B3DBB685EULL, 0xB6FE3BFCF3DD5876ULL, 
            0x4925149173A0BF60ULL, 0x324A5209978A5740ULL, 0xC79CD0693C25CD34ULL, 0xF64862D940357920ULL, 
            0xB61A12362A3C7F46ULL, 0x9C884638B3BCE5D6ULL, 0x1B32823A625275BDULL, 0xB55C379A7BCBD27FULL, 
            0x50A1CEAB71A086E2ULL, 0x85ED293472A5D5D7ULL, 0x4FDB3011684376D8ULL, 0x8EFD2CA40551935AULL, 
            0x3CA3E6A70B5C8019ULL, 0xD866B9A2F5608EB1ULL, 0x6161F9F9BED04D0CULL, 0x09A8C9232F4408F0ULL
        },
        {
            0x11ECD2FE8D1EF01BULL, 0xFA1948B8709F3AEFULL, 0x58B3F9E4C1451942ULL, 0x3C03123445D433C1ULL, 
            0x07149B9E9E6A90DCULL, 0x53F0BEA6C1676B8CULL, 0x9BDCCD6C2A49FE38ULL, 0x13CF9EA8FC68B203ULL, 
            0x350F992706B0D810ULL, 0x98C0DE450F8DADC6ULL, 0xFD181C6B491070C7ULL, 0xDF609C099BC49F25ULL, 
            0x6DB4AFF77CEDE1C9ULL, 0xE3D7C487E011D00CULL, 0xBD67246B52FA3390ULL, 0xA5854B102C4AFAD1ULL, 
            0xF3634E8D471660B7ULL, 0xA48D84F1D04D3190ULL, 0x42CB14F8FE10B528ULL, 0x83C6E1CD39620DDAULL, 
            0x76EBDB6F691CACB1ULL, 0x19DDBFA82E5137F1ULL, 0x1663915C17E913E8ULL, 0xA7651638F4BEE738ULL, 
            0xC5E27D9F548DB365ULL, 0xC6E62D29949C11C9ULL, 0x39D585918D2201F3ULL, 0x872DCE39F378293FULL, 
            0x72CA53344A388BBAULL, 0xB2BA4B3FC63CA025ULL, 0x8DC091BBB282680FULL, 0x4EFFD7754B19C6C4ULL
        },
        {
            0xCCCB2643D19B4845ULL, 0x31F6D4143B5E6A92ULL, 0x76AAE9CE9DEC63C9ULL, 0x90BB608EA683B701ULL, 
            0x129585164DF2BE7EULL, 0x51C8922EB53EE9CAULL, 0x9EC61453ACF16C29ULL, 0x481F71B85DC7512BULL, 
            0xCDF268D7EFCA1A61ULL, 0x04E485179AA11CE3ULL, 0x57ECC0BD2CDA144BULL, 0x63116BAA9B646B14ULL, 
            0xE6160E35C740B928ULL, 0x2020F81DE1085581ULL, 0xD312FB234EB95031ULL, 0xDF027FAA230B83A3ULL, 
            0xA3EDCEEC90953520ULL, 0x30C6A54E01C180C8ULL, 0x429A3B7BA3C7CDA3ULL, 0x2D4CEC1086F71C54ULL, 
            0x98D1F94C4781454CULL, 0x67D2400C6E2376E4ULL, 0x1F3E9F5D43E83615ULL, 0x85A4CA832059AF34ULL, 
            0x988A3990545E09EEULL, 0xEC336F183F5167B7ULL, 0xD74A97708746AF78ULL, 0xF54721B390646B1FULL, 
            0xDF4736B1E56378E6ULL, 0xFCAD38821754F22BULL, 0x1901BDD1A54E3E1FULL, 0xDE4DF261ACBA66FFULL
        }
    },
    {
        {
            0x3CC3C90731CB43FDULL, 0x192708394BCE2C78ULL, 0x522E8166349B34ECULL, 0x1CB6BEFE39DBA8FCULL, 
            0xFF193579C5D71D74ULL, 0x7EE80081D53B2D77ULL, 0x263CE4C5526B8671ULL, 0x5E9DC29BDD87AD51ULL, 
            0xDC746D6FB918F3C7ULL, 0x0820059639062845ULL, 0x0CBC2346D15CE74BULL, 0x01FC587DC60E5D62ULL, 
            0x52906D2CCACE95BDULL, 0x1C2A7876253281EDULL, 0xA178D1DFCD594436ULL, 0x2CEF3C8EC4061658ULL, 
            0x02355DA29EE7EECFULL, 0x8238C30D6E90ED7BULL, 0x50D97138BC5B05FFULL, 0x49B8FCD19EE0808AULL, 
            0x762EEB718C48192BULL, 0xD5716DC717670BE2ULL, 0xF31133C99D9762CDULL, 0x32A784CC03A91EACULL, 
            0x4388519F30EAD517ULL, 0x6B830E056622F49FULL, 0x77D808B27D8A4598ULL, 0x6B9CFFF0288DAE96ULL, 
            0x89338D5D4B393240ULL, 0xD1DCE1AC6591EDFDULL, 0x2C96EA77FCFDDCBDULL, 0x04E225A8E7CAA74FULL
        },
        {
            0x0C8F60AC722A7922ULL, 0xCE20106855BD5ED3ULL, 0xCCCC1302DD746A52ULL, 0x4D8C894FCCF7C1D1ULL, 
            0xE8B2DBD247EF0889ULL, 0x8823051EBB3DE815ULL, 0xB3A29394D5D74A35ULL, 0x8CC82D5652D25112ULL, 
            0x12203E24219B891AULL, 0xE27CAC19E326A20FULL, 0x03F252404A90430EULL, 0xD6812FDFF8F9FBBDULL, 
            0xA02C552092E04050ULL, 0xE0D98E582BC8E00CULL, 0x8356C7A457F1F1B0ULL, 0xB131A6DE03A6A64DULL, 
            0x633C66AE93352AE5ULL, 0xB5CF15A705038AF9ULL, 0x5447E2D6B1DBD77DULL, 0x00C48A945A7A2841ULL, 
            0x0F5006D910D824E1ULL, 0x9D24F987C496B14AULL, 0x0FF2E858678D2165ULL, 0x99FC1F9B02EE26D3ULL, 
            0xCEEF405B63051E2EULL, 0x404CFB9696BA26F7ULL, 0x6297CA6DBFC5E37EULL, 0xCBA7C571024C6E8AULL, 
            0xC70CF066675924E5ULL, 0x4CABAA8AFA42CABDULL, 0x8B4F9C18AFA69C81ULL, 0xB76E818F9600F57FULL
        },
        {
            0xDC14A6CD1C86C7B7ULL, 0x436B1C99BF019C74ULL, 0x43B7D340B031A473ULL, 0x051E00F8D8E1B431ULL, 
            0x95A0D8B80488E1EDULL, 0x0AEEEE3DE3A4441EULL, 0x3EA9851EB9F5BAF2ULL, 0xC2C708FCBA7AAA00ULL, 
            0x08355218C4E07A1AULL, 0xE4F33D22204A5C3DULL, 0x816197AACC4E9550ULL, 0xE343CED662D413DFULL, 
            0x18EE055E6D2ED3E9ULL, 0x2CFF9D91C5632988ULL, 0x871DD12D2BF9442FULL, 0x126CA130469C391AULL, 
            0x227A037C2CA7DAA7ULL, 0xA1ECCC26DFB82586ULL, 0xFEE8AB9311733850ULL, 0xD11827C1C3E8BDA0ULL, 
            0x21664B2A5B148752ULL, 0x57E443946C88559DULL, 0xFF97BE8D69E8193CULL, 0x7AE1866A7C09F05BULL, 
            0x212881205A6E0A08ULL, 0xDB71A5712A529720ULL, 0xE32DCABAE096CA15ULL, 0x041E5D3E52D2F2F5ULL, 
            0xAC15C0CD9E8222C9ULL, 0xA513FD94CAE5A3FBULL, 0x991A6FFFA9286F3AULL, 0x217C6BBBF99220BEULL
        },
        {
            0x2B833F8DF8C8574EULL, 0xA8BB642013BB23B9ULL, 0xD61A2C85598C2E13ULL, 0xAA66845100F86795ULL, 
            0xDDAF21591113F865ULL, 0x8E128B1EB064CBA8ULL, 0xC34419ED03EA1259ULL, 0x19AC57092595044CULL, 
            0x9EB7885BDC1C0C01ULL, 0x824B0F5174F902B1ULL, 0x61C98DD32CA0CF3BULL, 0xC68253DA95433E79ULL, 
            0x3B99A0B4D72FEBCEULL, 0x6A16D9F6A71DE7FAULL, 0x79F934C90245EB9AULL, 0x2BC41FFA7EEDF123ULL, 
            0x19F9FA4260528F50ULL, 0xB14A6633E1CB9B4EULL, 0x4F8B80A8AB16386EULL, 0xB8234D89C0FF9099ULL, 
            0x9259337D07D33378ULL, 0x69890B013D8D0484ULL, 0x2522AC1575D9F31EULL, 0xA7D43D12D1EB8BE7ULL, 
            0xDCFB596490CEF890ULL, 0x5C45431EE9F77482ULL, 0x9ECA7C221DC2CFA6ULL, 0xC1EA54506F4AE685ULL, 
            0x1CA001259BF8FAB1ULL, 0xC55AC3750314571CULL, 0x104C8147753A043DULL, 0xB89C7D58A4E52E53ULL
        },
        {
            0xB5E2E34D0342F443ULL, 0x38DAE256AB67703FULL, 0x96E089B6D917ED82ULL, 0xEC8F3B03662A5370ULL, 
            0xDAF074F87B121544ULL, 0x1DD7120D623F6A11ULL, 0xAB508E472232A559ULL, 0x2601D65B7417BF52ULL, 
            0x05A5D7F254124A86ULL, 0xF9A3DC8962EAC349ULL, 0xDFC28F99A07AC2D7ULL, 0xB17278858CFD4267ULL, 
            0x028379C7192D6CFEULL, 0xAF4E20E6CB0D4D2DULL, 0x6C71108012590410ULL, 0xC218ED90DC3E16FDULL, 
            0x1F01A616A7ECCF29ULL, 0xC39434B6FE25CF5AULL, 0xA9633F465A17404DULL, 0x0EB23F3C572105BDULL, 
            0x72CED1E87F93C9F4ULL, 0x5E111737F8FAA1CDULL, 0x0DECFB4797750F86ULL, 0xD9914ADC5A63CCA6ULL, 
            0x80E724BD7D140E6AULL, 0xB692B44D39E25CE3ULL, 0x4DC77B6497B7F609ULL, 0x5A38EE884ED8363FULL, 
            0x0F4B6EB4BAACE570ULL, 0x7040561730211216ULL, 0xD0E411241A558806ULL, 0xD72E92CB4019D6F2ULL
        },
        {
            0x796A77CDFF214336ULL, 0xE934DEC94E7FBF34ULL, 0xBD3EC1645DF39C73ULL, 0xA995AAAB58E665A1ULL, 
            0x48140B09319EE48AULL, 0xB7B22D8126994E9CULL, 0x4FE2602A059FB532ULL, 0xDE55F479CA4488A0ULL, 
            0x00CB8988EE309FF1ULL, 0x6C1C28C3B1C0A8F8ULL, 0x1C9907B689912D64ULL, 0x733438C416A68F21ULL, 
            0x2C24CDDA7D2837AEULL, 0xBCAF4596A01787DDULL, 0x9C20DCB39A0C0DA1ULL, 0x7760EB86D695CEB1ULL, 
            0xF4EF1C94BF84268EULL, 0xB8F3347E9FC529E1ULL, 0x3063BAAD888660CBULL, 0xE9CB9259269CDAC1ULL, 
            0x6D3B45792BFC1BB7ULL, 0x9E0240670EF31E9EULL, 0xE597D0F857DE3AFBULL, 0xF1F35CA282B4DB35ULL, 
            0xF64B5DAF940901CEULL, 0xD8B32E9D7E2C8A7DULL, 0x85212F520E76B715ULL, 0xA72B212E32E701A5ULL, 
            0x601F4D645899009BULL, 0x1AFC785D1CE79C89ULL, 0xAD0C1DFD4B7089D8ULL, 0xBBECC4EFDCEBC4DBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseBConstants = {
    0x9C0FB5E0A9165FA4ULL,
    0x1CE5BBBC376F390DULL,
    0x2D2D6D1D570FD6E3ULL,
    0x9C0FB5E0A9165FA4ULL,
    0x1CE5BBBC376F390DULL,
    0x2D2D6D1D570FD6E3ULL,
    0x7CC8C0A49350CCE6ULL,
    0xABB057E1C636283EULL,
    0xCE,
    0xB7,
    0xEA,
    0x90,
    0x54,
    0xFC,
    0xDF,
    0x96
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseCSalts = {
    {
        {
            0x7704A3985677A486ULL, 0x156D77C2FB66AF38ULL, 0x9CCFF124D1275FB6ULL, 0x3FD64CF426F26F8AULL, 
            0xD86E81BF2AF4F0BEULL, 0xB214613E258D9105ULL, 0x0F065449988FEA34ULL, 0x34EEAFF7FEBA9353ULL, 
            0x50E1D57909384CCAULL, 0xDE5E4EA15740B4CBULL, 0xDCE398B436D21794ULL, 0xFBBCF1661EFFF8C1ULL, 
            0x482CF5CB48881F32ULL, 0xC857D69E072D9872ULL, 0x1BC68347AB9D3A62ULL, 0xB766E36F7E0BAA70ULL, 
            0x7A30544524859F18ULL, 0xAEF6FD17A463004CULL, 0xC4E62FAD00121F6BULL, 0xCE9A508C543CD781ULL, 
            0xC91D800357974965ULL, 0x0F0B1ED0858D1D71ULL, 0xAA48E5F5E48A5C2CULL, 0xF7D8E78FA50FB3ACULL, 
            0x87527B0E850AFB02ULL, 0xEC788B6A173DD3FDULL, 0x05B1D409554A9AAFULL, 0x2AFCBCCF14014203ULL, 
            0x13BF5C1C7D771A1FULL, 0x236967DE9E732AF1ULL, 0xEEA5D2293DF0BD36ULL, 0xA3248D159928EF2FULL
        },
        {
            0xD7AAD2229AD1C3F1ULL, 0xD49F587BC5A95726ULL, 0xF5496EC2A1E6B7FAULL, 0x23C25CAD188C4639ULL, 
            0x00AB2BC31F01FF3FULL, 0xA3E238CB05A401FFULL, 0xB486B1E73B43A27DULL, 0x2E2645D627CEBB03ULL, 
            0x7CA9186E9C89C090ULL, 0x949501B06BD14CFAULL, 0xF4E3BF12E6452923ULL, 0x2CADFFFB20B1B6F5ULL, 
            0x81CDD4777BD28BA8ULL, 0x84B42C2216E5EB43ULL, 0xF221CCF2F1FE16B5ULL, 0x74B4BE585BD1BA07ULL, 
            0x39EF324FEE7EE941ULL, 0xFD3CF72EA88DF94BULL, 0x55F3BD2D4F79206AULL, 0x4CF2498B41CF3007ULL, 
            0x274C80EB41E7B9B9ULL, 0xB6313DD3E902C962ULL, 0x0A170D50D926E8D4ULL, 0xEC05E39BD1B0868EULL, 
            0xD657DCD9E4698B70ULL, 0x24501E2474445508ULL, 0x22EDEA8B6B41D349ULL, 0x1A2D45E01B295652ULL, 
            0x7FB6D7D0B3DF482BULL, 0x851E62EB3B5D98CEULL, 0x7CC23BB327CFAAB7ULL, 0xB0A3449D70EF6168ULL
        },
        {
            0xC890D4DC4264CE32ULL, 0x90A9387C4629BD5DULL, 0xA4D637750FBDE84CULL, 0xDB65BCC0C6EA50F3ULL, 
            0xEB6134464C3C5ED2ULL, 0x6DA5B7C733EC40F1ULL, 0xCA85C00CFB8E21A3ULL, 0x5582B20AC04F7EA1ULL, 
            0x78399C99D8C9B9A2ULL, 0xE84AD2B2A45860ECULL, 0x08119FC6B740C1A1ULL, 0x697CAD19E55D63B3ULL, 
            0x7EC5D0E3DA682BB8ULL, 0x5C8C1598653C2E1AULL, 0xDD29E11FBD278C03ULL, 0x358D2F7696E3C7A6ULL, 
            0x3EDC77D7DC3C4BE8ULL, 0x9C8E9BECD46FC7B9ULL, 0x2741F3C0459E6661ULL, 0x37E92B15D4ED47CAULL, 
            0x9513A200A4A9F20EULL, 0x8CC6221D72648CE5ULL, 0xA4FDAEFFE56E4E87ULL, 0xEF9AE6B0A82BD293ULL, 
            0x31646CEFFA1272F7ULL, 0xBF40F7594EB87B4DULL, 0x57965285AF75A58FULL, 0x327C2B61FEA11FD4ULL, 
            0x889EAF2A6EDB2EFEULL, 0xFED786F5407362CCULL, 0x959E122F9F40BC00ULL, 0x233C479AADB531FDULL
        },
        {
            0x5F7EEDFB5B57B63DULL, 0xD4382D5880CF01FEULL, 0xB7DF8A73FEA2D206ULL, 0x6F79FD37C89E3D08ULL, 
            0x41ECF4FFE660A16BULL, 0x8E77947CECF1683AULL, 0xA2272AEEBB6A4D8AULL, 0xC627C62F7B8FE295ULL, 
            0x438C6388B1696157ULL, 0xB2EE4350C28C6795ULL, 0xC1B46C166FEFE595ULL, 0x9BC6267468F737C9ULL, 
            0xB1D73DE4050E2221ULL, 0xDA693B0B85B913EFULL, 0xD6B6F04AC8C78F7AULL, 0x0F1FF14727AEF97EULL, 
            0x161AEAFC1637C31EULL, 0x1F045BD95D8F71A3ULL, 0x2A76340E3E1B789EULL, 0xD787FC3F73E5B90FULL, 
            0x55D442C499651FF0ULL, 0x0B97F71AFF4F2229ULL, 0xAC0B85593BC442F5ULL, 0x1CED664A83CB2CB6ULL, 
            0x3F91EFDD1F2B577BULL, 0x710CC3776E7A5259ULL, 0xD79379DC3E435BF7ULL, 0xC8ECD0E6DF37F545ULL, 
            0x7604DAD0250B94EBULL, 0x5468594A006AE4E7ULL, 0xF9A9B4A51E8B8984ULL, 0x9C40AD98E77DDF66ULL
        },
        {
            0xD4E8334434B156FEULL, 0x70EE2262C8F683FDULL, 0x1615B9A6472E07F3ULL, 0x0D7E15B6214AE515ULL, 
            0xA9B64D477E5CC61CULL, 0x0303064EF72D3F4AULL, 0x867CDA5CE7980F2AULL, 0x8452D643EC7504DEULL, 
            0xD7A8705F9C9CE713ULL, 0x3CFA3A888CB4D921ULL, 0x8A1C4E3317FB831CULL, 0xC9667458006B45F8ULL, 
            0xEC0A20782201492FULL, 0x1C00B78FF7D75562ULL, 0x11F47BC38A74B4AFULL, 0x8BCFB6E48DC3CF24ULL, 
            0xF1D0E3992151C4BFULL, 0xB1AD12B309F9E94BULL, 0xD4A72D8EF8B30CC6ULL, 0x0241B12905389565ULL, 
            0x3682CC4BF9EEB405ULL, 0x0F6957D3416FA4A2ULL, 0xA5E0C909B9CD4CFFULL, 0x526EFF2B04A40B66ULL, 
            0xED043977B65F487BULL, 0xBEA1BBE151B5EC9BULL, 0x2D38CB5E630BCEB8ULL, 0xBAE6682B08D9FDD1ULL, 
            0x7EAA8FFE7C7B3E46ULL, 0x3E1CFF3508BBD608ULL, 0xF82CBCE1099248F2ULL, 0x587247BF88B839BCULL
        },
        {
            0xBCA569FB1A20E36AULL, 0xB3EADAA7017DDD17ULL, 0x36879ED90272BBD9ULL, 0xF9254E08641A8B41ULL, 
            0x171578ECB78F5BD4ULL, 0xA361C83561A12BCDULL, 0x8B65CED6767A2B53ULL, 0x719F9BC1F3C38EEFULL, 
            0x8BD41189B64766F4ULL, 0x1E6966E3E735B4E3ULL, 0x0761B0468B7E16DEULL, 0x87676D8E9C97F52FULL, 
            0xB80270C8CFC7B903ULL, 0x0848D70751C29B65ULL, 0x32FF9E0621F23D35ULL, 0x94F99D09A9522D00ULL, 
            0x0BB8339FE1A311D6ULL, 0x7692B2B699C9114CULL, 0x5083EED0D9700D34ULL, 0x35302AEC41419424ULL, 
            0x049B3F773BB03E4DULL, 0x5FAE4FBB98193F80ULL, 0x0F6B8272AD59D5D7ULL, 0x169DC2552730F9D8ULL, 
            0xB81F0CA757847B3FULL, 0x4E3BB6E9A7CFDF97ULL, 0x72C5D625C65F3A7FULL, 0x3E0D70DC798A8776ULL, 
            0xF6287523180E514DULL, 0xA934D278BE2A711DULL, 0x99D3B7186E45AD4FULL, 0x4F6650F18B09F8ADULL
        }
    },
    {
        {
            0x04DDE395B06831ADULL, 0x818E24AE569B49AAULL, 0x6DBC7135B8DB1137ULL, 0xFDBC8B4C1C8B5808ULL, 
            0x6C7E3056AD23C35BULL, 0x291D8B7D4383B1B3ULL, 0x272C5B50F1424B77ULL, 0x13106B50400528C2ULL, 
            0xBACACE2782DCF306ULL, 0x1F6FA0A45D5DEEB4ULL, 0x98D6D24C5F99B882ULL, 0x148956E260DF032FULL, 
            0x738E3A9F135E5586ULL, 0x85E3D5E786BD731BULL, 0x8B9A8CAB3A9EF02EULL, 0xA0A052091E7C8C76ULL, 
            0xECA2CE9DF612F076ULL, 0xF0C68E8F6DF1C4C0ULL, 0x1F2CA10CEFC1001EULL, 0x43907C5E111581EDULL, 
            0x2701F9F9ACCF8F5CULL, 0xBF20FC335FCB1F3EULL, 0x11474EF4E0CF4D57ULL, 0xFD9E586BFC1F4863ULL, 
            0x83AE90CB1B658160ULL, 0x99523D848D9E7A1AULL, 0x7FC94F2B9A67FFCFULL, 0xC1C4CD2DD96314A4ULL, 
            0x7D8D4738A21CB80CULL, 0xC14B06D547F1EC41ULL, 0x6535D9B762714F2BULL, 0x6F0033EBE36B092AULL
        },
        {
            0x365E95597F35080DULL, 0x586C31941E0A4BA3ULL, 0x8A596F9C6ED93AE2ULL, 0x0745F214A98F9FB5ULL, 
            0x6431965692CDC693ULL, 0xD2E50FE36E9CAE4CULL, 0x505F75EC18928D17ULL, 0x87A9CBE6236A5EC7ULL, 
            0x2AE180A9B337A36CULL, 0xD1667824DC04A027ULL, 0x697853114629A5A6ULL, 0xFF390AE46C2985AFULL, 
            0xDA62C7389D189E53ULL, 0x87D8C6AE1BD18CB6ULL, 0xAB68103896D7104FULL, 0xC672DCFAC97E8470ULL, 
            0x053F98B97CED94BDULL, 0xB0BFE694BF7137DEULL, 0x9BA4F16327CB5B8EULL, 0x9BA460DED46B4E7BULL, 
            0xB4017DA06C790896ULL, 0x7B9A09C8CB26A36AULL, 0xE8F2495B12CA4688ULL, 0xF99FFCA026C22DF3ULL, 
            0xC957E3FAD2EB391BULL, 0x98BD91425DB8F005ULL, 0x434509D3F3D14271ULL, 0x24984BDC61DC21CDULL, 
            0xC6C7B5F07F3D6934ULL, 0xBFE5632F34D4066DULL, 0x7B15887E57BF9A5EULL, 0xE7BA58D8D1293D6DULL
        },
        {
            0x123CA8B725025954ULL, 0x54ADDC2984C5B455ULL, 0x868A78432666D2CDULL, 0x1C530F6BFD32F46AULL, 
            0x01AA7F66900735B5ULL, 0xD3515A350755ABDDULL, 0xC25542AB3DFF451AULL, 0xBD20CB4CC3605994ULL, 
            0x04B223B8BE0F1B61ULL, 0x1E91C375632BAFABULL, 0x142B11365C3EDF26ULL, 0x2FD568D893E087D9ULL, 
            0x402184E162DD0092ULL, 0xAFD845D302E5F6E5ULL, 0x8D261EB06D72CFE3ULL, 0xC4450F919F40D15BULL, 
            0x44F1304133142BE3ULL, 0xDF36893B6B8D5F32ULL, 0x0C5BB551DD76699FULL, 0x3F01F12023E4395DULL, 
            0xD1DF1BE79CFB35A5ULL, 0x1C100A1139DC86F1ULL, 0x2C6CBFD1296F045CULL, 0x20FEA88686B51ADAULL, 
            0xC8137079DCD6C953ULL, 0x5FE5CBC322952B0CULL, 0xC161F03185049BACULL, 0x03D1FAF5CDC3C731ULL, 
            0x5212550F55BDF607ULL, 0xC45C2E251B4944D1ULL, 0xD38C1A00DBE52195ULL, 0x9E9766E59D8CD203ULL
        },
        {
            0xEAA6C3AC7B5C77B6ULL, 0x0007CA8878E05366ULL, 0x30A568B60E592C8BULL, 0x7997AAF40BE39061ULL, 
            0x17E6E0BA24006234ULL, 0x1DDED9A4ADAE6F78ULL, 0x126C87C9FCD35725ULL, 0xCDF3E3FAE040DF12ULL, 
            0x4A94C83C010C911EULL, 0x41B194E00FE41751ULL, 0xF9B5EE99472E9E3FULL, 0x792AF12F4637CFD3ULL, 
            0x6DB939AE39F12A2EULL, 0xF81CDA8A6BDA6421ULL, 0xE6C2BBB9D8F8F3EAULL, 0xCE010248D1F96394ULL, 
            0x303B72C14653532AULL, 0x9BFA16B7A099C5FDULL, 0xEA8B7F1CDCEFC0A7ULL, 0x8C56A3FE1F2B858DULL, 
            0xC7FB468D74804016ULL, 0x134E0171E643BF27ULL, 0xF320F7C66D1265D5ULL, 0xBD562361AE949415ULL, 
            0x204A7CF5B0E7A643ULL, 0x60E4E67515B44B30ULL, 0x6F506BA3EDA68FD6ULL, 0xA2E83659BDE5945BULL, 
            0xA4D760FB4AF70530ULL, 0xACB4C2BC736971ABULL, 0x352DD12D7F9A19F1ULL, 0xA42D2D50186A0DF6ULL
        },
        {
            0xD04706FF5970E4BEULL, 0x7010ECC3DB95AFB4ULL, 0x9F2F56C3ED13694EULL, 0xDD48E6249B262417ULL, 
            0x6C6824123AD0F113ULL, 0xA6D996F7DFB423C3ULL, 0x0A985F474630968FULL, 0x982CFB50CD9D1434ULL, 
            0xD61799C55408A652ULL, 0x2BA96A843E4006C9ULL, 0x21669215AD184B41ULL, 0xC4F8CC239D267AF2ULL, 
            0x358D4D9396C411DBULL, 0x05ADC2587BB01572ULL, 0x0EB14AF65A783C32ULL, 0x08D97F9D42792DA0ULL, 
            0xF2FCFB05CC7AA66AULL, 0x6BE1E32D2005CD0EULL, 0x480CA21679884AD0ULL, 0x616708CEA409E708ULL, 
            0x7F70FEF91925CA10ULL, 0x1CE32ED464A67C44ULL, 0x2E4FBB5E038D2E37ULL, 0x0A775B15241B814AULL, 
            0x6D58FE287FB1C950ULL, 0x2687A1A06DBF21A9ULL, 0x22BEABB50132ABC2ULL, 0xEAD758DDF926720DULL, 
            0x6F906B2261CEEB8CULL, 0x775C300EEEE32D9AULL, 0x273A7D691D437B54ULL, 0xC6240975A78364BCULL
        },
        {
            0xC50F2B9F054AD1A0ULL, 0x1B921A0C352C10CAULL, 0x928FA0D29F60038BULL, 0x2C2AD39DCEB179FEULL, 
            0x5DA7C7B3C3C41B3AULL, 0xD117459CA5F05C10ULL, 0x6CB4DD79A77081D8ULL, 0x849FF5228C22B9FEULL, 
            0xB3D89E3859CBF904ULL, 0x441CA71CEA9A8991ULL, 0x241CDABDF7000DFEULL, 0xA875A731C0D55825ULL, 
            0x803306AAB222C449ULL, 0xA6222A1D08CA38B7ULL, 0x1B0386EEF6BDAA96ULL, 0xE44C4BFA2FD98BC8ULL, 
            0xFE74CEDEC0D48F3BULL, 0xF4D54E59C15628B6ULL, 0xB8717FE463DC2957ULL, 0x127BC4BC56B8F6A8ULL, 
            0xCF4930E0C76AC0A2ULL, 0x54FAD84E0CFAC0EFULL, 0xF61AE4EE6A5C60C3ULL, 0x8C0140D0B4506F02ULL, 
            0x2F6A8E57937048F8ULL, 0x6AD66D3ED117375CULL, 0x50DD536AF2E426BBULL, 0x0AFF8C5AF84E2E2CULL, 
            0x331905761C051CA4ULL, 0x0EFB0FFB6F85F1CAULL, 0x2B5B588CB547F012ULL, 0x4B08C7EE04C7A732ULL
        }
    },
    {
        {
            0x73E04BA478D7D73DULL, 0x67A56A97BDAF6AA9ULL, 0x6A3B4379E75D40FDULL, 0xDE09D09E3EC0700EULL, 
            0x5500CAED9AFB6E0AULL, 0x524DE93FD7E1DA0BULL, 0xEB2B9DDC72C0A2A7ULL, 0x33C6EA7A295D10C4ULL, 
            0xC14ADFB11B738A80ULL, 0x5730F13D59784BBFULL, 0x91CFC8B2B80E97C3ULL, 0x46B29110F31A9E31ULL, 
            0x592202A6E3C58721ULL, 0xC29C7C341B8B9763ULL, 0x0EC0EE0E1274324CULL, 0x45FA6D134D69291CULL, 
            0xB713E189223B2A33ULL, 0x9DA05BDC161C602EULL, 0xEED6ED4519639DCEULL, 0x2EDE784383D06F70ULL, 
            0x91ADE2123234044AULL, 0x7438E9E0C88DC0B8ULL, 0x1265FC6207B4AC67ULL, 0xDD64F0A4BF1F4D7DULL, 
            0x3234DE134CEB8E6FULL, 0xF0BBE22E0BF91C8BULL, 0x42AF53A461EEBF02ULL, 0xEEF500CDEFB0C5A5ULL, 
            0x2865EE22DB45B5CAULL, 0xA4F0555F39D8961BULL, 0x776DC6DE0381AD4BULL, 0x81C129F27307552DULL
        },
        {
            0x30E9CD105A8DCF3AULL, 0xE1AF2F08AF26EA22ULL, 0xBD0E5EE71BEB043BULL, 0x62B378A13057FE54ULL, 
            0xEA4E1C5E8A2FFB3DULL, 0x2E96809C716475E1ULL, 0xC3081978668C15BCULL, 0xA65BA6F87906CD04ULL, 
            0xCAA0D0702FCBF469ULL, 0x273A2577734D5468ULL, 0x8E3F3360544CDCC2ULL, 0x451E91D34954E6F5ULL, 
            0x244698B47ECA1D19ULL, 0xFDD89553A4CB37A5ULL, 0xE7B2D78FECC31AB5ULL, 0x848FCBDEC449A74AULL, 
            0xD2771593227C0000ULL, 0x2AD92A9FB7B7683FULL, 0xB4EC8255FC15FA5BULL, 0xE63A4B93908651F2ULL, 
            0xC2B0F6976A76217FULL, 0x442EEA4845F8C231ULL, 0x3FBD8E5C22F5F346ULL, 0x593AE55857C5A9C9ULL, 
            0x5374B50535FA8876ULL, 0x3D13B87A5915A0D5ULL, 0x2DACC84B3418C916ULL, 0xCB2190B22740A01AULL, 
            0x75F17D2DD04E7D2CULL, 0xDD38E742426F1D0EULL, 0x69A0ABCE7B46ED18ULL, 0xBCF9475499AA0F09ULL
        },
        {
            0x38579678B32D480BULL, 0x01646F7630DCA369ULL, 0x5BD8AB39A4336CF4ULL, 0x7EC7ED5908200B85ULL, 
            0xB365DE5C6403E416ULL, 0x00E6390BACCD2E2CULL, 0x9AF3654080121C35ULL, 0x07A4624755EA60A8ULL, 
            0x42CBE14784E8A919ULL, 0xA049F292E8B93D0AULL, 0xA67D3C865DAEC6E1ULL, 0x86CD8B72E960E1E1ULL, 
            0x6B4B696C929CFB23ULL, 0x66B3A0C8F30A74AAULL, 0xAE4D419F842AF041ULL, 0xB0A782BB82B509F3ULL, 
            0xFE7BEC7CBA13483CULL, 0x9A47A1C5358F6103ULL, 0xAF81B16EE56E8594ULL, 0x5D5A3682925E13BEULL, 
            0x7AB92C3A1544E433ULL, 0x49EA7693F60B08BFULL, 0xB60BBDB253381730ULL, 0xC656689F3971FA6DULL, 
            0xB243110038E057E6ULL, 0x9EBB41EE8EA59DAAULL, 0xD60AB7E2D890AD44ULL, 0x05FFE26E79540440ULL, 
            0x523C7AF86E6C8110ULL, 0x8BB68BBFAAE351B2ULL, 0xFC0680BA7CFAAD03ULL, 0x367D7FE57668CA97ULL
        },
        {
            0x5242F3062E652870ULL, 0x796D0A07EE2AE943ULL, 0x59A3035D2A813218ULL, 0x06DDC4010E30948AULL, 
            0x7D4C70FC9346AEF2ULL, 0x7D3D6A64A4A434FBULL, 0x82D55D08E65CA1BAULL, 0xD20FBC9C023885BBULL, 
            0xFB3451A8421E24E1ULL, 0xA2105447E611EC9BULL, 0xC51950F3D23CFB5AULL, 0x6B3A0661AA5F605AULL, 
            0xDC4610ED061950FBULL, 0x803B6891F7FC5074ULL, 0xD2EB7E3801127E85ULL, 0xD4B61C02B3C5F8B8ULL, 
            0xD23CEDB32A1C4449ULL, 0x6EC8DB45BE5C85F4ULL, 0xFE09AC14C20FC96CULL, 0x8EDB71B62BF07014ULL, 
            0x5640E6B22A56A2BDULL, 0xC4FEDA4A81CEA939ULL, 0xEAAE51A2D93381C2ULL, 0x9B6685D49E3C3843ULL, 
            0x6F3E1BA786F1C8E6ULL, 0xBC87F17FE3C7D819ULL, 0x5FF9A46D9B13DA8DULL, 0xB76D052BF45F6054ULL, 
            0xE69BD66F0E2467E1ULL, 0xBB749F96BE278A00ULL, 0xADCFADE52BCDE6B3ULL, 0x0747A592CCA61069ULL
        },
        {
            0xAD41F5ECFCF176E0ULL, 0x7252C2E1A982F724ULL, 0x2594C8BB76F9BF52ULL, 0xE0565EADE6866F1DULL, 
            0xFA70D661E3BB05AEULL, 0xC9E1BED833B2A92BULL, 0x74A3C0A5D49E6804ULL, 0x534C0989FB576AF8ULL, 
            0xF32840E8A0911D23ULL, 0x791FB3D9C65EE10FULL, 0x206782716152ADABULL, 0x6D6142188635A20BULL, 
            0x1FF563F23811BA7BULL, 0xF7CF2E47BEDD4E2EULL, 0x7877836613AAB208ULL, 0xEF3843F4B43B9DD4ULL, 
            0xEB27BD11D5BF37ADULL, 0x0238AFFB4CD4CD5BULL, 0x79C4BBC2B206B9C2ULL, 0x4F4E4B1542B4FB44ULL, 
            0x3FD090D759F6E240ULL, 0x63033E2B0AB7A300ULL, 0x9CFB5F4AB4419F7AULL, 0x5B0577CE106BBFE7ULL, 
            0x1194DAB0CF3BEFE8ULL, 0x1E901716A01F3D22ULL, 0x8FED642B1B00B4C7ULL, 0x6367B437DDFDDCE8ULL, 
            0x8A3B473BA84EE2EFULL, 0x071D4BBAB855B14DULL, 0xB7009150BC73EA53ULL, 0xBACE046C7525BADBULL
        },
        {
            0xB394773F7AF4B8D4ULL, 0x86BC280E0B63F771ULL, 0x920DC703B12096FAULL, 0x85EDDFA6EA1CC3CAULL, 
            0x352F360B328F8D99ULL, 0xD8D053EAC6533F6CULL, 0x4F2256EE6BA34ECCULL, 0xE634965ECB032A6EULL, 
            0x9A28083236359516ULL, 0xA7B92EC2F18FD057ULL, 0x1205EF6DE92ED27DULL, 0x915485F2DD0EDB08ULL, 
            0xE05FCEEE867F9A4AULL, 0xEFE064CA38D62B12ULL, 0xC5E60209DC0C111BULL, 0x34D100DEDCAC1847ULL, 
            0x8FE1A03166ED0E40ULL, 0x853E974F320E6ACFULL, 0xC264815B6F0F2604ULL, 0x4FCE0AD82B636A39ULL, 
            0x0752F6DC4FE235A0ULL, 0xA208DD5132A6132FULL, 0x287C5E3A05A5F818ULL, 0x72E4B2BD8D26866FULL, 
            0x09097FE7716D8503ULL, 0xEB624610F26C698BULL, 0x817017753B2BF5AEULL, 0xF90141662D2A4B36ULL, 
            0x7E186C39BC401FE0ULL, 0x1B034A1D3EE78F0BULL, 0x04B88D2B87CAD01EULL, 0x4E19EC05B1DEECEDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseCConstants = {
    0xD8D869AD2BB76361ULL,
    0x48214AF9D8E05272ULL,
    0x4AF376E02BA025A3ULL,
    0xD8D869AD2BB76361ULL,
    0x48214AF9D8E05272ULL,
    0x4AF376E02BA025A3ULL,
    0xA237393FF0B0E0B3ULL,
    0xC81E9860AC8F66ADULL,
    0x8F,
    0x02,
    0x35,
    0x18,
    0xA8,
    0x10,
    0x08,
    0x71
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseDSalts = {
    {
        {
            0xFE7135BA0E1DFA9AULL, 0x7548B301DD2A58BAULL, 0x83FEEA0CFE7EEEDFULL, 0x488632AA3D91255FULL, 
            0xFE876DA6265B27B5ULL, 0x764D54C93A22A0AFULL, 0x7BA142AD62D760E3ULL, 0x80B4A4B87B50023BULL, 
            0xD38F832043A49741ULL, 0x0A4C74C8587329F9ULL, 0x7A6A43119070F330ULL, 0x5C81B1625127263DULL, 
            0xC5D09370581223D2ULL, 0x9F9FFC6A1E0E512FULL, 0xC45E41A6FD8E6BBBULL, 0x23694081B228B1ACULL, 
            0xB9F6AA2044C50964ULL, 0xF36040747523889FULL, 0x2FD65E6678858A13ULL, 0x3F2E94F93AD63D5EULL, 
            0xA58BB96B4F318B6BULL, 0xA0592F1C8FE7F404ULL, 0x516F4878929AE416ULL, 0x658892945F23BD64ULL, 
            0xD37F9D828644C2F1ULL, 0xA382CD8AB1A4D5C8ULL, 0x2516A98C9A1516FEULL, 0xE80FC3CAA693C870ULL, 
            0x06D05BECC6874D61ULL, 0x0678E074F41C93B7ULL, 0xE88CD6AD54082DAFULL, 0x7C11C799D28BBA12ULL
        },
        {
            0x88CEBF8A617700E3ULL, 0x791080D850BDD2EFULL, 0xA48C15BE21769D43ULL, 0x95D4E2A7223F44E4ULL, 
            0x25FC939755525508ULL, 0x96190AFBBB90A1F0ULL, 0x949425C639E731C7ULL, 0xC439B20C6B6B0BCAULL, 
            0x04E3AA0D032C886CULL, 0x5DA4D76C0EBB0605ULL, 0x3D49795A17B8FD90ULL, 0xAB0DE1DE5BE0B051ULL, 
            0x3489DBECF5450462ULL, 0x05CC25B478A04CFDULL, 0x115C4F9153C0DF93ULL, 0x9E85D3017F8E758EULL, 
            0x90DAE043AB35AA8AULL, 0x1850E13C287124E7ULL, 0x1CB816C4213576F8ULL, 0xC84DE05619B4C80DULL, 
            0xCAC1FE5F76EF415EULL, 0x5EFCB9985BC17DE7ULL, 0x68564F4579F325B7ULL, 0x249ADF17BFAE1427ULL, 
            0xCD6E58C03526312EULL, 0x21EF99F54E77AEA8ULL, 0x464BDEDED470FBA7ULL, 0xB3EE1261947E0922ULL, 
            0xE38E483CCE8F923DULL, 0xB8E6EF10F171C740ULL, 0x252B1A74F6218744ULL, 0xF34B82D8E8B823A2ULL
        },
        {
            0xF271853BADAD8F72ULL, 0x44F8468B089FF6A8ULL, 0x8D706EB2B0E2F8C3ULL, 0x556FE8971808D3C0ULL, 
            0xBEBABF1B1B3C4F11ULL, 0xB258214E35F89221ULL, 0x347E16790A5ABDA9ULL, 0x9A38A95750584F33ULL, 
            0x7340B14A0D0BD3DEULL, 0x31E5EDE51485826CULL, 0xD39AE605ABEC38F2ULL, 0x40C0C2A9943ECBC1ULL, 
            0xF2C227941422D458ULL, 0xC11B4F193FCCF1C7ULL, 0x95186412113D3FA2ULL, 0x99930B0BC000A9C3ULL, 
            0x3B3EBA5925B05B5BULL, 0x433360CA988EA643ULL, 0xBEA31591AE3FBED4ULL, 0x346E7F5DC6BD5061ULL, 
            0x83505907B092943AULL, 0x261AAD18EE6EB39DULL, 0x9545679465D9D42DULL, 0xD76775FCC5335EB3ULL, 
            0xECB183E4AC665AC6ULL, 0x7E1FC5A3A166A3C4ULL, 0x671566E577F687F4ULL, 0x60F6AE83BADACA64ULL, 
            0x84EE0C6B7E755915ULL, 0x250651DB394B69A2ULL, 0xE17799618A485339ULL, 0xD2B9326E2CF259AEULL
        },
        {
            0x66EC7D1CF36660A4ULL, 0xC40AAA7C9B0233E2ULL, 0xFC6E6D5000BDFE71ULL, 0x812CA939474D040EULL, 
            0x048793E641375D74ULL, 0x48F74651C452DDAAULL, 0x7A1F27CF31F06112ULL, 0x0B1D13B2D58990C6ULL, 
            0xF6081A7DE26E56F1ULL, 0x9457A4F4E4DB3851ULL, 0xDB48B1B11C7E0D48ULL, 0x0C5EFAABF491720DULL, 
            0xC813FFCEEE4501D9ULL, 0xEF9D9517DEC71DFFULL, 0x3C33DC598674C53BULL, 0xEF6CD2987C0A5862ULL, 
            0x81723AF4068D3347ULL, 0x535026CC146873FBULL, 0x46352416E1F0CF43ULL, 0xEA0F6F7D5AC2446FULL, 
            0x8AA574D13F0034A3ULL, 0x36077AF2ABD0390CULL, 0xA895F017DFF0DA30ULL, 0x299031295FAA32A6ULL, 
            0xDBD8B78EC27989ADULL, 0xD116ABC187517D9AULL, 0x600A503060EF6689ULL, 0x288440659EDDA7EEULL, 
            0x2F26CFC6F0C07EB5ULL, 0xD50B748510A9DA98ULL, 0xD54CAF62E5F0A0AFULL, 0x82D8151A4A2DE900ULL
        },
        {
            0xBDEF6FF3390C94AEULL, 0xFC67587AF53F4571ULL, 0x5896549830F78F89ULL, 0xFE5714DF8986AA76ULL, 
            0x6FE56FC416DA0B29ULL, 0xC7E559EB042432DBULL, 0x2F376285E4874817ULL, 0x3A23C9B2B8B4B6DCULL, 
            0x141BF2791D3B67D5ULL, 0x0F56AE8FE4FD5C3AULL, 0x705F237B275770C4ULL, 0xCA5B225E3456AE61ULL, 
            0x3A784613E2B992EAULL, 0x5B4FDB47D0ADF4E3ULL, 0xF03CCD106701B2C0ULL, 0x0C8264FFF74DF8FBULL, 
            0x6E620BD47879AC46ULL, 0xCFF4E325D9F4634CULL, 0xB8D5EADBB9152766ULL, 0x345F27AC46E6F3A0ULL, 
            0x4B253ABD2C201B77ULL, 0xF98D387F6E5EBAE7ULL, 0xACF6F40E84CF3B9EULL, 0x5C563FE5B689D98EULL, 
            0xCD417663F3722D7BULL, 0x51062A0B203AAF16ULL, 0x5150353CF7D2B35EULL, 0xC4680980BB5B1988ULL, 
            0x7E4E853522C4063CULL, 0xDDCF6D107CEF931FULL, 0xF97D7D6816B1C49FULL, 0xEDE12B9D093F51A1ULL
        },
        {
            0x03C716DD3BD0F75EULL, 0x08B654F5EE6AA036ULL, 0xF85E9D5FD8E9616FULL, 0xCC234E43DA1D0E3DULL, 
            0xB7D6DE2DC317F3AFULL, 0x8EEC4279685CED7AULL, 0xAACBC13AD76D2555ULL, 0xC015BB2BC2BAAD56ULL, 
            0xA46660470175B104ULL, 0xA6877330CB0BC173ULL, 0xD69C869B0A384DDEULL, 0xF2A64B049FCDC07AULL, 
            0x44971F45D6AA16CCULL, 0x94428D83D9CA0EAAULL, 0x6EBE9EE681D76402ULL, 0xB3A6D35686B5F77BULL, 
            0x8A486398906100B3ULL, 0xF730832E2E4E7899ULL, 0x81EEBE9FBDA5CBB8ULL, 0x1466E9E7DCE8E11DULL, 
            0x51E84F853616D502ULL, 0xD7F1D07C010F329FULL, 0x02C9C25D0E7B17E3ULL, 0xF800BAA0399ECB6EULL, 
            0x612FDAA52148F727ULL, 0x674D4C80A729DC59ULL, 0x1F71E06EFA082358ULL, 0xDBC2E7A391B42957ULL, 
            0xF20C15AA35F0F291ULL, 0x45CC0E82C61FEE9FULL, 0x2447F0453672906FULL, 0x63B79CBBB8BE1DA8ULL
        }
    },
    {
        {
            0x162118590735A189ULL, 0x6B4288D3F1821EE3ULL, 0x17F522B6758B7612ULL, 0x1952403BDD87CC69ULL, 
            0x34A007337CA55604ULL, 0xB53ADA4CB0FCFE54ULL, 0x1FE4FE1FFAE50006ULL, 0xE397FDEE7B9C2A99ULL, 
            0xFF02EB8C79DC95D0ULL, 0x1AB58673338797E3ULL, 0x0B2749472CCA0C3FULL, 0xCE1DD4CBBC284420ULL, 
            0xE096A40BACC49DC2ULL, 0x6A151E2F02E443F7ULL, 0xBE2684F804CE259DULL, 0x41388CF80CBD75C6ULL, 
            0xD46EDEF9714239ADULL, 0x3428BF2BA0318C6FULL, 0x888D2262E90E84B3ULL, 0xB91757486D5D0CDBULL, 
            0x3D9AC8BE336CE34CULL, 0x23895CF5799304A1ULL, 0x449A3E0F46BCC8DBULL, 0xDCE1FD5F5AA668DAULL, 
            0x9C92261979646ECFULL, 0xE08A0058A4A192D4ULL, 0xB610E47FA1CA784EULL, 0xE6241ADC3DA795CCULL, 
            0xDA63353C783B6997ULL, 0x9D66CAE98F3C234EULL, 0xCBA4B36FEF441DB2ULL, 0xB2B0D1055B6555C9ULL
        },
        {
            0x007A257C98B23134ULL, 0x298454193DFCD8DAULL, 0xFD49B684142808E1ULL, 0xC3569086147D38EDULL, 
            0xFA7347962301C21FULL, 0xA7E6C77C0AAC1173ULL, 0x802917840A1E4A83ULL, 0x6E45A80DD9D68B1DULL, 
            0x94B6F401016B2A17ULL, 0x57F7A4FD3BF4287CULL, 0x2BF2BECD6B678E3BULL, 0x79889965AF5849F8ULL, 
            0x3DCB0F383893F48FULL, 0x846B933A28B45384ULL, 0x582BD66BED80476EULL, 0xB70410183E248C7BULL, 
            0xC93FF25F9AECACACULL, 0x6E9797C79B265DABULL, 0xC0601483458C0B9DULL, 0x89C0C7B6489E32FBULL, 
            0xE7086E3EF2046BF6ULL, 0x9EE202C1BB7C9651ULL, 0x929D3213EF02A306ULL, 0x09FA0456F8D6E73EULL, 
            0x1D46038222CFEE23ULL, 0xC86572DFC48B8CD5ULL, 0x85C39531BACD4EC4ULL, 0x6D2E8C6F0F2CF981ULL, 
            0xF2DD66D110C8DDE3ULL, 0x3FEAC264B9AD3908ULL, 0xCEB26FABDEB9BFFEULL, 0x7630A924A1CF878CULL
        },
        {
            0xE9E732009F1A8E6BULL, 0x5FDAFF8F4B1AF2FBULL, 0xCED14C5C9ECACD10ULL, 0x54A9913797852CBDULL, 
            0x303069F466A8ED00ULL, 0xEDB0F47A3D91DBABULL, 0x2A584A397864EB63ULL, 0x37D7212CD2C56403ULL, 
            0x3C73C0D86544AC6AULL, 0x543ADFFB644F4F06ULL, 0x0251F4DA7EB996CDULL, 0x55066991B3EB3E53ULL, 
            0xFE45403FBA633749ULL, 0x2CC1C556088D0F2FULL, 0xFA70039B122FF1E8ULL, 0x949F94DBE97DF3D2ULL, 
            0xF8E4EACEB5234173ULL, 0x6ACC64145093F93DULL, 0x7835905FA9F6803CULL, 0xA02BDF0B3469EE4CULL, 
            0xD96E26344B3DBA2DULL, 0x7077A245E756B2FEULL, 0x286D16E3016E7F96ULL, 0xB2AD8D830796BBB8ULL, 
            0xDD6833B988772800ULL, 0x59383D8419915579ULL, 0x04431CEBF9347ED5ULL, 0x9BCE1D3FD74808A0ULL, 
            0xFE1DE4194DC2C624ULL, 0x8C4C3E42DC22F1ACULL, 0x18FCD2D441EBE97AULL, 0xD4F3BFEADB2FA902ULL
        },
        {
            0x534500905D305E0CULL, 0xBED22DD8A858F829ULL, 0xA5CF12EA987578BBULL, 0x2ADF323F9B72EC00ULL, 
            0x940D17E4A7399050ULL, 0x3836A42E2CCEB9C4ULL, 0xDCA481A91294A6B2ULL, 0x585D888A31FB1B7FULL, 
            0x4F2D1948B7AF9CD6ULL, 0xA9FDC575891895F6ULL, 0x3B3208F579215674ULL, 0x8C23BB7BAD0BA589ULL, 
            0xB738B576EFC7D677ULL, 0x9299A8A78CE3AAA0ULL, 0x6A93EF0867C4C024ULL, 0xEF7721C450E7B60FULL, 
            0x370AED696C82EAF9ULL, 0x80986825EB8C4AD8ULL, 0xA4F1D2FECA8D54EAULL, 0xB714812790EFA321ULL, 
            0x5DD3655AECA04CA1ULL, 0x02C1872519C63BE8ULL, 0x9823CF09ABCE1445ULL, 0xB7CDD8F85621F0B1ULL, 
            0x99654DD3668FF7B8ULL, 0xDB828E46F385A8CDULL, 0x35C769DEC023A0BFULL, 0xC199AC3968BB7460ULL, 
            0x91919268DEC28860ULL, 0xCE423D93AEAA0299ULL, 0x61C94E4391F2194AULL, 0x4269CB2E360663F3ULL
        },
        {
            0xE2D3FE321E4D7586ULL, 0xE7F5C1B865161D9FULL, 0xF181DE012DBCE83BULL, 0xF13941B8D0533A24ULL, 
            0xC76292496200AD51ULL, 0x6EC340C3BB52A06EULL, 0x49BA3004EF7B064FULL, 0x55802EF6922F3C67ULL, 
            0x724B556D5941E0F5ULL, 0x6AA4D0FCFBE1B8D7ULL, 0xE1B8E304FFB722E6ULL, 0xF69F5744D0189B04ULL, 
            0x1351A98DA45A9979ULL, 0x8253129987A19FADULL, 0xC1A6C253DAEC3D49ULL, 0x8E3C8DCE628D6D1CULL, 
            0x80A5B0C39EC69BA7ULL, 0xED31FB7F1028D8D5ULL, 0x55D5C8BDF0099E97ULL, 0x76ABB8310CFF3AAAULL, 
            0x298A1B77899C551BULL, 0x64D5DE5618CC3A73ULL, 0xE934CB1EE05F3C81ULL, 0x0F6853E2F573D494ULL, 
            0x221EB260300C484AULL, 0x7FA5D884CC768DDDULL, 0x5133BA6ABCF5FB65ULL, 0x86E4B21690C8DEA9ULL, 
            0xB8FA0473544A96DDULL, 0x397756B34D27D68EULL, 0x4C7754D92C407AAEULL, 0xBDA3F2B2C9F745A8ULL
        },
        {
            0x5A9A75A7B7FDEDEEULL, 0xB83984CA1057C904ULL, 0x67A305A54A31C2BAULL, 0x73E02D10C14526B1ULL, 
            0x01A0378C870C0181ULL, 0xFE9DD80D30C94055ULL, 0x501F25CA6D94239DULL, 0x70429607E176C026ULL, 
            0x73603CE9F7147221ULL, 0x4D0DA4778E941388ULL, 0xB572420577D53A39ULL, 0xF82D80C3793FFD11ULL, 
            0xB109154F44F3A3ACULL, 0xD6380F1E419ADED5ULL, 0xDC6DC34C93531AE7ULL, 0x452C495F293715C3ULL, 
            0x42146F2AE5DB3024ULL, 0xE9A691BDAB7606A5ULL, 0x5C1BC0C2A8BD5F4DULL, 0x971648C1486655E9ULL, 
            0x10B301F1B4345158ULL, 0x5E1BF05860ACC6A2ULL, 0x69FBB1E22722847FULL, 0x61374A7E8D1FD945ULL, 
            0xB510E1BAA1FFE584ULL, 0xFC1A1C9E1DCE2D8DULL, 0x5B1D2274FAB861BFULL, 0x40C1C59C33BCFCEFULL, 
            0xC3D7A90F0D65C2C6ULL, 0xFD3A9D66FAD5CDDCULL, 0x6BFECB74F5A33C44ULL, 0x730FEE17BFCD21ACULL
        }
    },
    {
        {
            0x84E1E7F87F8737ECULL, 0xF064136E57DCF929ULL, 0xE4F76D8555E5BD84ULL, 0xF6C091B9245EE6CAULL, 
            0xA1532731A2CF835CULL, 0x27793DDD1D5C115CULL, 0xEE7002826D46046AULL, 0x7A8773A2532E67CFULL, 
            0x33691E4B9023D42BULL, 0x80D0CE7A8D7CFB7AULL, 0x04A6B63B5E98EF63ULL, 0xF6E5FDA7088132DCULL, 
            0x8A23A98BA38C19EFULL, 0x180A17F60B3FE537ULL, 0x9DBF00B93387619FULL, 0x2784D094AFFBD70FULL, 
            0x1A63476F791E254BULL, 0x3BBC93D7B2EC8C4FULL, 0xD640AB6DC693F7EDULL, 0xE2A3BCF7435FCB05ULL, 
            0x32ECE66AF5BC71E7ULL, 0xB4F67BDA5501AB5FULL, 0x6407814A352FD84DULL, 0x39757446C6EBF35DULL, 
            0x8D6FEE4556489D56ULL, 0xF01AE1F2F9D8D612ULL, 0x3B8883EEE4518079ULL, 0x65F0B4E25AFBF3B1ULL, 
            0xC529D40B441F703AULL, 0x90945C8AD519DED7ULL, 0x9F1A7E2CE15A5CBEULL, 0xA52495E029B0196BULL
        },
        {
            0xE8FCD39AFC183ECAULL, 0x80F52A631ECE7D67ULL, 0xC834F193AE742CCEULL, 0x3938467D7E9D4434ULL, 
            0xBDD1650C6B32CCD0ULL, 0x163B97374E20DFD2ULL, 0xB88C459150652952ULL, 0xD81A4139C5AEF4D2ULL, 
            0x746587BBEE4237D3ULL, 0xD95FCBF5D338BF15ULL, 0x0909AACEAA48C8D0ULL, 0xAC58A299DA705EBFULL, 
            0x0E0B4D4B20298E74ULL, 0x9365743E6F4D731DULL, 0x8C9D6421DE9C0B81ULL, 0x6BE5CF189D31EE33ULL, 
            0x200311EDEACD5B7EULL, 0x2FF6BCD0F07A7282ULL, 0x564EDAFB0FFFEE4AULL, 0x5F569C1DDD81302FULL, 
            0x6B23645795E1251CULL, 0x4B0368D15D6421C2ULL, 0xAE8DFE082C406BE9ULL, 0x7F2F845EEA7C980DULL, 
            0xC3ECB05C1AAFA301ULL, 0xC1E1CFEEF94FD768ULL, 0xCF0FF5A17D0C1447ULL, 0x723F4C60349B2498ULL, 
            0x812967C3A5EBBE0AULL, 0xA283ECA7411048F1ULL, 0x71CDBAB0319F0710ULL, 0x51BFE541551325BBULL
        },
        {
            0x1F238D5E93527BF8ULL, 0x2027C35DF14B17A1ULL, 0x68BE807B85247E5BULL, 0x2DC168B284761920ULL, 
            0x117647843D4F659BULL, 0x9DCFC712CD5BB1D6ULL, 0xC21FA24642269DB4ULL, 0xE9579ECEB0DB3599ULL, 
            0x7718101DB8D5FB85ULL, 0xF577977FFDE5519FULL, 0x973A16DCA715955FULL, 0x4CE511BD965623C9ULL, 
            0xB4D13E0074567E4DULL, 0x5AAB3261B730A8F9ULL, 0x1466E9CC21C34086ULL, 0x8F01F09E71E63723ULL, 
            0x2C9D25F5698AD54DULL, 0x1E0A82FE01B574F1ULL, 0x8FA4E3FC804B7ECFULL, 0xFEDA48F82B1FB83FULL, 
            0xAA3977FF20457EF3ULL, 0x7F3FD00F32E5E917ULL, 0x04C7F00A98CB16CFULL, 0x035F3BD25477E734ULL, 
            0x4F127D9EE66523B5ULL, 0x83A7B03D8695BBFDULL, 0x69B3083B186C32C5ULL, 0xD96E9731DE589AC2ULL, 
            0x66DB7AE31CF610A8ULL, 0x82550831D796DF37ULL, 0xEF7768783102EC75ULL, 0x9668F743F4936CF7ULL
        },
        {
            0xAD8D6B58EECCB1BCULL, 0x5E0AA0107D605B51ULL, 0xE7A1E3170B173CBFULL, 0xDC2835A4341F6452ULL, 
            0x43FEC5BD77ED6B9AULL, 0x38473ED57EB894EBULL, 0xC96DAC5CCAD7CD81ULL, 0x7367182645403543ULL, 
            0x676F8F611EA7DA3CULL, 0x7CE6BBE2B616573AULL, 0x015D01113FFAF323ULL, 0x41E76FD2004BE607ULL, 
            0xDFAB4A4D8D5D266DULL, 0xF5F576879DEACF9CULL, 0xECF29F40EE8BDB8CULL, 0xA31EBB4464E800F4ULL, 
            0xFA5953CEF407CECEULL, 0xE3649E6FC3A8D422ULL, 0xD88F02C1990F93CEULL, 0x236D98EACF49F8A5ULL, 
            0xFE456E2ECE4E3F0AULL, 0x05F420AA444BDC0BULL, 0x39653C4669751C8FULL, 0x65E14547FBA70907ULL, 
            0xC147624D225F85E4ULL, 0xADF07262DCD6835CULL, 0xAB2D588057504458ULL, 0x65FFAD64AA0BA24FULL, 
            0x6EC03F6A3F82D2FBULL, 0x8F09FDA36DFE6694ULL, 0x52F32BD06687360AULL, 0xBED27C335D8F517AULL
        },
        {
            0x428D4D4385777EBAULL, 0x86410B000D535E8CULL, 0x1C8CF68B46B8D5D2ULL, 0xFC920EA040EDD3E0ULL, 
            0x8D4E3FB2BBC692F4ULL, 0x6C91493F4472B4C2ULL, 0x4E0C60EA0ADC9BA1ULL, 0x4290615022123B8EULL, 
            0x9CEFE5983D7609C1ULL, 0xA317EDE976954AADULL, 0xE6F6AB8F79BBC040ULL, 0xAB4489F271F4F7B6ULL, 
            0x5CE7D9BA20417533ULL, 0xD355A664E5632E67ULL, 0x50292ED930A34338ULL, 0x6AB8A0FF43801837ULL, 
            0x1868382EDE059521ULL, 0xF7A9D5223FF166DBULL, 0x08D1CD7E65F6E992ULL, 0x9122FA49AD98204BULL, 
            0x4197A21645108121ULL, 0x82C4F6D27BE12C68ULL, 0xA1489E51E929B33FULL, 0x71C7E45BB02CFDE4ULL, 
            0x29C1D89ECF0AF520ULL, 0x726423015F4C6D43ULL, 0x01921200D62EFAD8ULL, 0x8A8D8ECE10FE4892ULL, 
            0x254A0BE3F1C21DA4ULL, 0x7F67947E73A54E47ULL, 0x3C6F7AEF0D27955CULL, 0xF0EB3E91F0229ED8ULL
        },
        {
            0xBD6BE6094927C952ULL, 0xC2E9F2C125E74599ULL, 0xE89C27E7A6E4D14AULL, 0xD938FFCDD70FFE84ULL, 
            0x4D05090D91065B19ULL, 0x5E3D7F2CF465C2B2ULL, 0x181BE9594DB87BF6ULL, 0x5E363CDB4C386005ULL, 
            0xD5777B3DB54C6FEBULL, 0xFD605FCA3C22717FULL, 0x8EFC3A411634D858ULL, 0x14F9D430BD200A55ULL, 
            0x9FE03CAEC76458C4ULL, 0x66285881FD7ED95AULL, 0xDCA8CA468ACBFC9DULL, 0xE04CC01F739952CEULL, 
            0x83D0F50F69C3FB16ULL, 0x98E756831E0EA1D7ULL, 0xA75F8F026AFDD5C4ULL, 0x7C1E7F16C58BF8ACULL, 
            0xE0D061767AF0FD98ULL, 0x688BC4B2ACF7099EULL, 0x26F766DF381599B0ULL, 0x3E508E104EA2399BULL, 
            0x06D9D8A0F9BEA705ULL, 0x06A59C3D3E073065ULL, 0xC00DA61E6528354BULL, 0x75DE7EDCBEF3D5A6ULL, 
            0x98F4880F4B054398ULL, 0x987D9F26DA59BF70ULL, 0xC9D287455E888E39ULL, 0x6E59F1828889849AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseDConstants = {
    0xCB988A3A31ABAC10ULL,
    0x1728A8E0E91E3DDDULL,
    0x45752A1480D5D210ULL,
    0xCB988A3A31ABAC10ULL,
    0x1728A8E0E91E3DDDULL,
    0x45752A1480D5D210ULL,
    0xDD2C3C571AA761C6ULL,
    0x5B4A72A0082FFEB7ULL,
    0x07,
    0x4E,
    0x5B,
    0x9A,
    0xE3,
    0xB3,
    0x22,
    0xE9
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseESalts = {
    {
        {
            0x2FA35A69835F4341ULL, 0xC08C34C9A9833F22ULL, 0x83BA080CC977C6A7ULL, 0xF3C744D3F113D83AULL, 
            0xB9521A62213A3FF4ULL, 0x22119292D6CB76EFULL, 0x35B9A2518A90373DULL, 0x442DEAA7A5338281ULL, 
            0x0DFE8642F7D5B41CULL, 0x8BDB18F1DC69F3BBULL, 0x95DC8E6AEE79FD93ULL, 0x8D43B6930D8A0CD4ULL, 
            0x3D2DDCB2DD9865D3ULL, 0xBF76400917A9BDD7ULL, 0x9D03FC04CB6E0471ULL, 0x018DC0C7869C398CULL, 
            0x97153115B2B50FABULL, 0xD6CD0C028E75CE0AULL, 0x9C966C67AA212A70ULL, 0xBBA3A3F1B5BDD4BEULL, 
            0xE704D4B2B5AAEAA8ULL, 0x456F6B2BBC018D93ULL, 0x2D24AC31D115C230ULL, 0x29BCFCB76040D5A6ULL, 
            0xA7CA104DF85C6A08ULL, 0x37D85CEA8502CD44ULL, 0xFC1F23643CAD7D2FULL, 0x6BB9BA8D148E729DULL, 
            0x4211DF4521FB34EBULL, 0x5132099D47C687E5ULL, 0x8AFF4C3F8E337C57ULL, 0x1F2B6C3F1D274D5FULL
        },
        {
            0x4785FCD658F30887ULL, 0xAD6DAA39C413DAC2ULL, 0x28818535F03344F8ULL, 0x34384C4664DDF8F8ULL, 
            0x11706CC9586B98F7ULL, 0x057B9C6102CA509EULL, 0x572E211D68A480E4ULL, 0x0BA02EAD80811FF2ULL, 
            0xE6703288CA841E50ULL, 0x1FE42DBCDC378116ULL, 0xEB9435C67B7D2DF2ULL, 0x073AACCAE6E1BC4FULL, 
            0x53B3319E7515290EULL, 0xAF3DCEB186D7FE22ULL, 0x84C4A3FACC82778EULL, 0xF47DAD4B7A9B9597ULL, 
            0x36E7DDD57336B9DEULL, 0xC7E02BE12C6CFBB2ULL, 0xB0CC511FD279AE97ULL, 0x0690DDEB27096E09ULL, 
            0x16D8662F69F10A9FULL, 0xB53297F92B310DE2ULL, 0x98BEC6A1353466ECULL, 0xEB5F74E4B93E31C2ULL, 
            0xED2E24998E9BFEDCULL, 0xC41576D501AD302BULL, 0xA3E00EDB3F6ABAE9ULL, 0xC220FDCD7B653AE8ULL, 
            0xAEF237B270A36AABULL, 0x9880CC3646E5165AULL, 0x21A7986313A1E920ULL, 0xB8A3EE6822D05AA9ULL
        },
        {
            0x4CE8D94CC7E1CAD9ULL, 0x46C03A2EB8263BF0ULL, 0x412A9C468E2D59A4ULL, 0x37D4391092058239ULL, 
            0xA098EAE307BD1009ULL, 0x0C3E9DA6DD5E3CB0ULL, 0x4DDF5CDA244A2451ULL, 0xE4595345D31E1DAEULL, 
            0x8634EA90593D577EULL, 0xCA8B2AE41F3ABEB5ULL, 0x2C90BBE3DDDC8856ULL, 0x909C4B1D50DEEBA1ULL, 
            0x4A71B4FE3DBEF49BULL, 0xE6661180899AA25BULL, 0x973C6A6C001C166DULL, 0xE58A84D75C48417FULL, 
            0xC32F18449B6C1F89ULL, 0x403E73AEFE3465F6ULL, 0xDD6BAFF6EC066891ULL, 0xF397B9D367983776ULL, 
            0xC739E1C425AC1AF5ULL, 0x3E363FA582533001ULL, 0x6505125E1208246DULL, 0x483782FDA66B6480ULL, 
            0xB2A538B9021D8E63ULL, 0x900E4D9E0522ED12ULL, 0x9CF14A72EC7F805EULL, 0x465E35441DBC4985ULL, 
            0x790531540EC1A71BULL, 0xE0969CB771D7BB7BULL, 0x67F7E678E90385F6ULL, 0x8105A7A9A4D2FE17ULL
        },
        {
            0x4D3F4B04853F4780ULL, 0xB2F5F180B353548AULL, 0x5F25309C7EBA6777ULL, 0x95DD981C057B4416ULL, 
            0x7EE8494921AA25DDULL, 0x0C3E8142479A2B81ULL, 0x938D0E9A8F845740ULL, 0x9F237409392C9681ULL, 
            0xBF359AC70AC20AFDULL, 0x4BAD12D8E397B21EULL, 0x31FEB6BC995B598CULL, 0xF6CDF93DAE9F17BCULL, 
            0x3D84E2CAEB8B2B66ULL, 0xF3A55E691F95E09AULL, 0x341F10342AF0B269ULL, 0xA0D6EDEFD86B3A79ULL, 
            0x4C91219F5CB9845DULL, 0x62843BF9860DBC57ULL, 0x639DD4143C32C09CULL, 0x50A6EE06916852B7ULL, 
            0xA14D597D074AB474ULL, 0xEF9452ECD1D74667ULL, 0xBEB55442290E2ED1ULL, 0xB9A855D071CE4BC6ULL, 
            0xFE2BFF2BCE6532C0ULL, 0x3BBFBF0AFABE47D3ULL, 0xDDFABB946169D8FEULL, 0x236B39ADABC00207ULL, 
            0x3C13113E2FE207C9ULL, 0x37B79FD4EBA7634EULL, 0xEF248D9595BEB7F1ULL, 0xFC3D0DA2952994A6ULL
        },
        {
            0xF860A9554146CC70ULL, 0xA90C328A9B428972ULL, 0xF2F3F8D2926B8EC9ULL, 0x05ABFBBE0031F623ULL, 
            0xA95FEB91151E23A4ULL, 0x571BFD9A4E1897FBULL, 0xBB79768F9414BE06ULL, 0x63CE8A2E97F2D517ULL, 
            0x3552B71922FE3821ULL, 0xB814F4329BB4E79BULL, 0xA06BC45A47019609ULL, 0x49ABDF955AB75193ULL, 
            0x5A1B449A11FC002EULL, 0xDA10849414C16128ULL, 0x89A61C58C03104B3ULL, 0x476D490C59EC8958ULL, 
            0x7F379F62FB1B562DULL, 0x520746CD3E082E37ULL, 0xE1AFE630E360CD4FULL, 0x5CBEE7C231AD80CBULL, 
            0x2A7256571AD1E9AEULL, 0x680DCD60FAFED4AAULL, 0x33AFBB7D024F96E7ULL, 0x9276A57A2223C829ULL, 
            0xB2FD4C42C7DA118CULL, 0x77B325F0951EAF11ULL, 0x25D359975113679AULL, 0xDF91BA1C34A36C74ULL, 
            0x16E44FA14C0292D9ULL, 0x3FF5CB1EDB94FAA7ULL, 0x9533C7FF555F4CADULL, 0x7C256C4206099EE7ULL
        },
        {
            0xA632732F9FA98BC9ULL, 0x60A27D88E73204EBULL, 0x65E3867E73292B7FULL, 0x725394756668DE75ULL, 
            0xB8DA8791DD2AF5ABULL, 0x58C757745064F599ULL, 0x8004E907A43072D2ULL, 0x6C105C9A789631F8ULL, 
            0x4B39910C345C9C8DULL, 0xC95BD97082620691ULL, 0x4B1BDB01E2E1ED02ULL, 0x135FD3D7376C404CULL, 
            0xA5CFD2BD81DCB320ULL, 0x21BDD4EB35732EF9ULL, 0xAE435458A541496BULL, 0x8C6C224797BACFF1ULL, 
            0x8AD5691FC543CF7DULL, 0xCC4984482B0C3321ULL, 0x1B6F92A7E5183B68ULL, 0xD420BE6952CF095CULL, 
            0x12C37263D27151C6ULL, 0x6492C19BA8E77E6AULL, 0x3FA4A9DAE9C521C0ULL, 0x1FCFE7006C32255CULL, 
            0x9D5AC970F090C337ULL, 0xD84CCF642EF543DAULL, 0x925C5EC2385443AAULL, 0xA095F6DA3A8AF635ULL, 
            0x5A3FDE21D0052CB2ULL, 0xF8D8F66CE1D44EAFULL, 0x70D5F305230EF458ULL, 0x2EECD65F9BA51FF8ULL
        }
    },
    {
        {
            0x7C59BABE70D5EB26ULL, 0xA1563D63A404E60EULL, 0x887324FFE6BFB3EEULL, 0x46D1F78CD94305ADULL, 
            0xB628B3E65A897389ULL, 0xA3EAF6DA3B4312EFULL, 0x67F6E9B2E31CACE1ULL, 0xA1A9006B386567FAULL, 
            0xF3F7FEDCB83DDA44ULL, 0x234D84A0D3BD16A9ULL, 0x4B5139E64E28288CULL, 0xD9258DEEB0314A7EULL, 
            0xB8311EC000A6C6C9ULL, 0xA7D553A7440ABBEBULL, 0xE1537060B5C5E318ULL, 0xCECD76097C22B5B4ULL, 
            0xC2768554BFBF0546ULL, 0x9DE2445B65B2662CULL, 0x7CB65B7F4D2B4D49ULL, 0x7243B4464E0D95DCULL, 
            0xC310F816DC77A2E6ULL, 0x34EC4F6091ABF158ULL, 0x22FF0FFAA7B817E9ULL, 0xD0D0DD4E203BE90CULL, 
            0x0C455A0253C84444ULL, 0x9455B5F680CBD7D7ULL, 0xAB08985B9F75BDD3ULL, 0x5A9BF9470F6EC1FDULL, 
            0xB0143C495B8C9E78ULL, 0x1C71A33665B014D6ULL, 0xC315BEB2C37CD25EULL, 0x50B97C9BB2ED0871ULL
        },
        {
            0xC4EB61E7511CF314ULL, 0x6843793AA9BF1B8CULL, 0xC82CD6E936BD9494ULL, 0x0D4BB44E3C648217ULL, 
            0xE01F7605B378FD9FULL, 0xF9CBE11D2138959BULL, 0x0DD2D2D9D486DC50ULL, 0xA1C7407E13B929E9ULL, 
            0x9CE07442B9EF9C0CULL, 0x24E3A0AFE3CB50ACULL, 0xA0AC28F07074F014ULL, 0xCC9644FA61568199ULL, 
            0xEB02A2B5B57B8DC1ULL, 0xD1FB45D596965FB3ULL, 0x90250575AAC59C34ULL, 0x2FBBFC7233C4ADD7ULL, 
            0xE4B8E358090C383DULL, 0xB7717EBF2C67714DULL, 0x10FF347199B985DDULL, 0xC76E8B6EFE04248CULL, 
            0x42613B5BA204D8FFULL, 0x6069DEAAD2A09B2CULL, 0x867802E8561A35EAULL, 0xBDD1816BD5D774EFULL, 
            0xF4019A53EFFBDC56ULL, 0xFCE47529612AD9DDULL, 0xD41F791CFE58D82CULL, 0xE480EB01D27D2609ULL, 
            0x99557FF8B14196B5ULL, 0x73B502DBF27C430FULL, 0x9B8CD5389358F0C7ULL, 0x4859B0716864B2D9ULL
        },
        {
            0x0B5926805821D09FULL, 0xAA8C6F5FDA0EB3ECULL, 0xBAF9798DD194CA05ULL, 0xBA7AE7A54F8D5F51ULL, 
            0xBEBCF9156471D865ULL, 0xE54FAE8ACEF93880ULL, 0x05E471BB31D19DA9ULL, 0xA4C3F9B882BC62D0ULL, 
            0x87B78E19756C2E7AULL, 0xA1E9E3F26449F582ULL, 0xA818FD8C189607B9ULL, 0x1EB70717C478CBE7ULL, 
            0xCF66FDF10703AB83ULL, 0x0B82626FF4E523EDULL, 0x1F90533E4D31DD9DULL, 0x730523378F90A4D9ULL, 
            0xCC0EAD6EAFFD477FULL, 0x54F0DB2D22BD3939ULL, 0x2A04EA105E292530ULL, 0x5AF58F00515959ACULL, 
            0x0AE2A7B6B07D8D64ULL, 0x59C9E920DDCF1DCDULL, 0x072FAB7DE4F55E10ULL, 0x13E81F9AC304E9A3ULL, 
            0xBB89D714DF82C2C5ULL, 0x0F137C6CC4C28A51ULL, 0x40875D0CFC282647ULL, 0x4A09E444F1A04DB6ULL, 
            0x7DD40B3BB00C64E0ULL, 0xEA18BAA763D1412FULL, 0xCA99395ED697A42EULL, 0xE91F082F08B2DF79ULL
        },
        {
            0xF8372C52F5273119ULL, 0xA5E6A3B6618C7272ULL, 0x1C391300B72C2658ULL, 0x464CABCCF456EF75ULL, 
            0x3FB8EE8DD50213FBULL, 0x6A2CC0A0224E0D24ULL, 0xE4702B55A172889EULL, 0x28035BAF99CDFFCCULL, 
            0x8B57EF11E6D2FB20ULL, 0x82107E1F065FD12CULL, 0x98C6D46E7CB1A984ULL, 0x6A045A90CFFBC795ULL, 
            0xBFE2B1F7666A70A5ULL, 0x60C103B99B38856AULL, 0x443B1CBC90DB34C2ULL, 0xCF06D68588F04ACEULL, 
            0xA4B1C8C865539414ULL, 0x38A7D329A0F620A6ULL, 0x142EAFFC4627A86EULL, 0x2D65D14E45A1B4A0ULL, 
            0xAD5FFF78BA83424CULL, 0x103C3FA9BE18F61CULL, 0x378E3F9CE37A6029ULL, 0xC12AAC9C278F6092ULL, 
            0x1FA847E51B357651ULL, 0xE9C05E3EF6DC4281ULL, 0x3F91D416386088C6ULL, 0x5BFC4DA7A8CC41DFULL, 
            0x1BC8C837FA114362ULL, 0x5053712D6036C4EEULL, 0x8B6EDC7C58E94427ULL, 0x840138BDEA30D7C4ULL
        },
        {
            0xCD7059DF8BCDD13BULL, 0xECCA38C0607856C9ULL, 0x0F1F56921409F3BEULL, 0x7D445F1E3B8A824AULL, 
            0x964CE400DA3F1692ULL, 0xDB70B08B69176934ULL, 0x8A4892A8018C08ECULL, 0x99E6130AE3EC571EULL, 
            0x7456025ADBD808A3ULL, 0xF33A2F26C140B4E3ULL, 0x40008BC17F9E7FCEULL, 0xA97D73AC0B3274E7ULL, 
            0x81C2BACCA199843BULL, 0x8C5D35FBCD52D0A9ULL, 0xF4AC900F182FA684ULL, 0x8FFC972E90EFE889ULL, 
            0xDFBD4A5B165501F4ULL, 0x2EC31D83A9D861E0ULL, 0xFE5783758A6A61C2ULL, 0x46107491376D37B5ULL, 
            0x3D2D3780279B6510ULL, 0xE574A4E3D84C8E3AULL, 0x9E76A82DBD7AA6D6ULL, 0xF63E92EA9566D2CBULL, 
            0x65DA7DD93BFEE4BFULL, 0x6EA3D824C9E3191AULL, 0xF2852FCD2DA09AEFULL, 0xF6ACD7387D78E088ULL, 
            0x75780AF5F4EA6F6FULL, 0xDF90D8D710D15704ULL, 0x33F5A5B283172307ULL, 0xDF7BE5EA4C597FEDULL
        },
        {
            0xD849BB8918B1A149ULL, 0xA61CFAC25D9C5975ULL, 0x19A99FC9A674B153ULL, 0x80F47D00E1B777E3ULL, 
            0x0AA7EFBEDE8B224FULL, 0xED994EF900649B03ULL, 0x797B03461F7931E9ULL, 0x136F5EE4E3FF7695ULL, 
            0xCC9EBC3A2274365EULL, 0xBC11DB7D823DA759ULL, 0x60F1179DCB381865ULL, 0xA2BDF5F9578F2301ULL, 
            0xA82095A957FE5E68ULL, 0xDE2AFE50C7CB6991ULL, 0x039C078AA3F2A1C6ULL, 0x46BF0E62350A50C5ULL, 
            0x42BC5E61A6DC2838ULL, 0x5D1164BB47295FEDULL, 0xD4E22E713AAB12A7ULL, 0x79B60F88019608CCULL, 
            0xC7F36723B39184D4ULL, 0x5E141084189703B2ULL, 0x51D529D95E12B2B9ULL, 0x82D302DFBCA0B097ULL, 
            0x4F5A6E2156B10DD3ULL, 0x0CFA853F619CB411ULL, 0xF4F80666B12FD748ULL, 0x5E239C918AE946C7ULL, 
            0x66209DA65A5F18F9ULL, 0x89BF08499782F71DULL, 0x02B3E99ED3D621E5ULL, 0xC064F5E86B3E6ECFULL
        }
    },
    {
        {
            0xAE04D7AFF3652D67ULL, 0xF9BB163C45795871ULL, 0xCFACF2D9A756CC5BULL, 0x99E08CCEEB545830ULL, 
            0xEDFDB096EA90886FULL, 0xAB58DA9616A4872EULL, 0x409BBE9F159034CDULL, 0xAA15833D058BE9BAULL, 
            0x8CDB36067947FB07ULL, 0x0C5F6CB296BEAC0CULL, 0xFFDC91C90314EDD0ULL, 0x270BE6A73AC1DAFDULL, 
            0x30C25228F9614F1DULL, 0xD82396691F8E488AULL, 0xFFCACC1013909F8AULL, 0xB18DA64FA95ACF42ULL, 
            0x13DF8BFDD00DA6F9ULL, 0xDE1584AE693EB4BCULL, 0x6F5D39C8835EAC2AULL, 0xCA16669056D1959AULL, 
            0xDE6546C882EE8561ULL, 0x21AB92CA506F0803ULL, 0xAF0B70A2B72409C8ULL, 0x20F9AF03566742F3ULL, 
            0xA8AC97293A59D8E5ULL, 0x3556F5AA543690F7ULL, 0x234E4F8CF55E5C91ULL, 0x1E360B69F2255C11ULL, 
            0xE6C67B154EE0AD9DULL, 0xF23ABADD964737D5ULL, 0x62AAECB637845C9AULL, 0x2813EE7D5F82287EULL
        },
        {
            0x6EC4FAC4490E7BA0ULL, 0xBB50EA73AAF3C639ULL, 0x9E2B827BB620CE04ULL, 0x9C417CE075E7ECBAULL, 
            0x71E19EF6368D0A12ULL, 0xB598AD03870780F2ULL, 0xAF1A78B24555EA8EULL, 0x6DA2593DEE1D572FULL, 
            0xE2E6F16DA648FEDAULL, 0xF0732F7D263F3C02ULL, 0xC107AD3F69E3A92BULL, 0xD3808BFF2A3F2698ULL, 
            0x911B1377B7EDD980ULL, 0x11583915C02EA0C7ULL, 0x457EC5BFBB5C006FULL, 0x9F327608DBC72FDBULL, 
            0x8A28994632523E04ULL, 0xE69C706FD8A1C4E9ULL, 0xC31E9798547127DCULL, 0xC69ACC8BD55E09E3ULL, 
            0x2E26D50F550E842FULL, 0xBC60CDB710BD49ABULL, 0x3D0462AED1446731ULL, 0x66CE7EC77683BFDCULL, 
            0x9FFC24DA84CD8C77ULL, 0x534B18F5A731CC89ULL, 0xC34244A456F3500EULL, 0xB4EEE44DD0CA3FC6ULL, 
            0x34B71C634BE6E620ULL, 0x6C97E28CB62E45DCULL, 0x238C2DBB9342C67BULL, 0xC0666500310D3100ULL
        },
        {
            0x46AB745299D7770CULL, 0x4F2B15D24FC5E0F9ULL, 0x25950E060FDEBE22ULL, 0x7080B24B53074F52ULL, 
            0x8F431B8D6C9B49B7ULL, 0x35FACDA2FF0CAF84ULL, 0xD980743EAA4A8B4EULL, 0x3D661D5F4FD58665ULL, 
            0x4C25055F971CE5C0ULL, 0x0268521CF52D524EULL, 0x8782DF6A0D925E8AULL, 0x8A5315A7CAF2DD3FULL, 
            0xB95559521A833E3DULL, 0x7A3CE8DBAAC77751ULL, 0x1CD03AADC57ABF97ULL, 0x672F09AFE484A77BULL, 
            0xFA635B426EF44F9FULL, 0x6F9008DFC6A84442ULL, 0x506353AE23BA1183ULL, 0xEA9CD9A121696168ULL, 
            0x5200B2ABAD408383ULL, 0x6A9702041039185BULL, 0xAE1CE33DADEB2787ULL, 0x5D4017629E110546ULL, 
            0x92DFA40AAE1C967FULL, 0x4D17C94C5F61620BULL, 0xE9E56F687DF36FF1ULL, 0x2D0FA848DB70A712ULL, 
            0x01C571ED268948D2ULL, 0x5459736D7F5A2B9DULL, 0xFE68C22003EA6DB8ULL, 0xC8DE159FBF1BE043ULL
        },
        {
            0x0969FB50F31BD62EULL, 0xF7AEADDEEA0D9516ULL, 0x903A7CA0EFEB3BF2ULL, 0x71A17920887C5884ULL, 
            0x03ED50ADC689FF3CULL, 0xB62CFE4096CF94FDULL, 0x806E118C21C43DE3ULL, 0xF1376A8D1F8D6447ULL, 
            0x0BF4CF41BB38A252ULL, 0x3742C34D258C1A8DULL, 0x4A6C1974FEB3D4EBULL, 0x9B5448EF4D776D5DULL, 
            0x034313D88A8A6B4BULL, 0xB62FA2446ECD9627ULL, 0xF6A4C2676733DC9FULL, 0x52E8057340B70A8BULL, 
            0x837D5C233DA6CABDULL, 0x87F0DD52382131F5ULL, 0xE37687DEC5B49B97ULL, 0x7DF33232BD44DE13ULL, 
            0xDDF4AF123359F6ACULL, 0x3A5790362566178EULL, 0x3E917804DE589A6FULL, 0xBB8C8415854A820EULL, 
            0x622F5A0BFF43D281ULL, 0xDFE05872C1A3AF10ULL, 0xEAE2BC8D5EB36C82ULL, 0x878E16756A321354ULL, 
            0xD90E913A895A7E0CULL, 0xFC49097BA499B96AULL, 0xEBFE3D4781B89CBFULL, 0x34A06770508A53CBULL
        },
        {
            0xED58974D60D45363ULL, 0xCEE6A6A0B23781B3ULL, 0xE34AC8FFAA15988AULL, 0x1FA59D382F9670DAULL, 
            0x443C037A62EC2ED7ULL, 0x98AFB428731AA620ULL, 0xF1DF1AD8A6782748ULL, 0x0996060C698D8D57ULL, 
            0x9D074EB05BDB2C78ULL, 0xB57BA74056CEC54EULL, 0x141B2F35EBA5A792ULL, 0xFB6F6217EFF25023ULL, 
            0x0C205255AADB9692ULL, 0x9DFE2F82C4C0BADCULL, 0xC0566F852CA496F7ULL, 0xD2B3E77D68B856B0ULL, 
            0x5D6E5405A59CF60EULL, 0x208BA5A7CD5B65DFULL, 0x588A71EA5D8FF35EULL, 0x0D13769C089EAAC5ULL, 
            0x0178F40CC7AC9B54ULL, 0x7BC637BD4B116DCBULL, 0xDB06ACEDD5EC9429ULL, 0x41167D4236D824D3ULL, 
            0xCFE79D9FB3060719ULL, 0x0472057C7EC0187CULL, 0x74658F8C5007D066ULL, 0x35C3FBE5FBE417C7ULL, 
            0xB999A7936F58CC91ULL, 0xE1E775C0776C690DULL, 0x124A86B6609AC70EULL, 0x3F2A5EDB2BA9FE9BULL
        },
        {
            0xAA33AF05AED965C2ULL, 0xE2715E2A4944E00BULL, 0x3A6839136B8B89B5ULL, 0x0FE9F33BCA10E89DULL, 
            0xC0F6D354ADD0E97EULL, 0xF46E490266145F5DULL, 0xFDB07FDDEB6F862AULL, 0xFD2D9FA107C23A87ULL, 
            0x1E34F9D3E0BDCFDBULL, 0x96884F81B294AF1EULL, 0xDCB24FBBA167B190ULL, 0x096743CED5C45E94ULL, 
            0x683910C54AEE3FD8ULL, 0xEE71CE00766F4289ULL, 0x4EA481D594FAA244ULL, 0xD997B89B59BE5A7BULL, 
            0x114FD11504356C37ULL, 0x1DC9A75DA0628675ULL, 0x7DDB6095CC4305D7ULL, 0x49C4B79E756C591BULL, 
            0xE659A875FFCF1611ULL, 0x15F0C5CDBA327784ULL, 0x1EE7F22AD8D76A35ULL, 0x19EA9716C983F9D6ULL, 
            0x69B76D615DF58A9CULL, 0xE5976E1137422624ULL, 0xD5A285A772CD2D0BULL, 0x5B2186082967C6C8ULL, 
            0x02A2CAEF3D5C5873ULL, 0xD03949F94816DA7DULL, 0xD030C3E4F4F11374ULL, 0x0AA2A85E219428DFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseEConstants = {
    0xDDB8DC176E7AA3D2ULL,
    0xFB8B5E3E8568681AULL,
    0x5DB2BA84EADC5BBFULL,
    0xDDB8DC176E7AA3D2ULL,
    0xFB8B5E3E8568681AULL,
    0x5DB2BA84EADC5BBFULL,
    0x44A660BAFEA41FDAULL,
    0x070D4E549BF89F1DULL,
    0xA3,
    0xC6,
    0x3B,
    0x91,
    0x37,
    0xAA,
    0x78,
    0x70
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseFSalts = {
    {
        {
            0xC5E9A4989DB75D06ULL, 0x73F5EBA642480671ULL, 0x905C3665F3CFD68EULL, 0x097A271A03470AE8ULL, 
            0xA085162A5A5C11B7ULL, 0x346380279AE9C36CULL, 0x084F5B70E079BF40ULL, 0x305421F2A8DD5790ULL, 
            0xEC70BDA387DA8E3EULL, 0x38CD9B36D2517235ULL, 0xB01FC7F262C8567FULL, 0xB669306E8D3232E9ULL, 
            0xC0ED9FF84D1F5040ULL, 0x42F1672739CFD2FCULL, 0xD121AEFC5CA19E56ULL, 0x6F63ECFAC372080EULL, 
            0xF26C59FA911F5250ULL, 0xC339E9865C2F5230ULL, 0x01AA84261249E674ULL, 0x41D47808ADB1206FULL, 
            0xABEE8F7F88D6AD5DULL, 0x967748DF3EF0F1DAULL, 0x47697070DFA35DF8ULL, 0x705821F3B6ABAE55ULL, 
            0x5D7A2AC2D391A62BULL, 0x87523F82232E1314ULL, 0x7BF62CFE22A68B9EULL, 0xD5F59890AA7539E8ULL, 
            0x24E65B9F8B5FCF6AULL, 0xDA9D494E631DBD2BULL, 0x3E82A128FE2FCDF9ULL, 0xCF1272D5D68E4B33ULL
        },
        {
            0x24433BEE6719E452ULL, 0xB2E19A5D146F74DCULL, 0x18DBB802B412433EULL, 0x25DF2327AEA35D42ULL, 
            0xB67D577B39B9EF13ULL, 0x84656D6DB6DDC633ULL, 0xB388591AC4955F8BULL, 0x14C6115A1DE56A00ULL, 
            0x2DF8703FED4AE88EULL, 0xC6173231C3CA77AFULL, 0xFD677C5272B7B328ULL, 0xB52F9797C3F07CEDULL, 
            0x700D0A1B5D70B811ULL, 0x20D54D7B272E745CULL, 0x110BC597151B2A21ULL, 0x8379E5B91CD2FA51ULL, 
            0x656ECE4429C05DAEULL, 0xDC641DF5299A1872ULL, 0xA2E7EA120BD8F20AULL, 0x0DC14EBD1AB02261ULL, 
            0x0E7533E2C4DB8AFFULL, 0x443D4F16D3C9B2C5ULL, 0xB2EC334529524614ULL, 0xC70B832E908C2B5DULL, 
            0xF06E5CCB4B2E87EEULL, 0x187304EA2B91A0C7ULL, 0xB2D76908228BCC1EULL, 0x20B4A11FA17AC566ULL, 
            0xF37162F481823322ULL, 0xF3A3083F293CF72BULL, 0xF7E9C8777239A043ULL, 0xEAC3A0215E9E84FAULL
        },
        {
            0x7746B70D512D1C8DULL, 0xDA89D887C9E9D477ULL, 0x87FF77CD2DFA12B1ULL, 0x1C2C44F122ED517AULL, 
            0x55F02E0377DFD239ULL, 0x774E5BC9934D6D25ULL, 0x84F3CD47AA990529ULL, 0x371C8CA38D1F6800ULL, 
            0x7007CBE1CA211A5FULL, 0xBF67BB0767ABA891ULL, 0xE4DAF0FC6D8FAE3FULL, 0x808531EDDD353DEBULL, 
            0x0671AC9DB2B25149ULL, 0x7823FAF141869FF4ULL, 0x81841E9EFC9EF5B3ULL, 0x6D4F9AA0E6524255ULL, 
            0xCC95D08EF4DA454BULL, 0x187FD148F062CD23ULL, 0xEDB32A02D2DD4265ULL, 0x7D7460A7ADFEC7B3ULL, 
            0x8E99AF0E97A6CDC4ULL, 0xF9C17BBC7C675A51ULL, 0x4DCE7A5212E8143EULL, 0xB35A926473922731ULL, 
            0x900BFAEC6B5CDAA1ULL, 0xD4C920D1B096F89AULL, 0x30E78B79A3384AB5ULL, 0xF0CAD214FC0B2A71ULL, 
            0x616AB891AC610194ULL, 0x5637F5814D8B8B9DULL, 0xD152C8A47F857960ULL, 0xBCA9BEE23FE0480EULL
        },
        {
            0x98AA59D29DFD5749ULL, 0xF0C6EDB37848E414ULL, 0x1B8C6982D5198B3CULL, 0xBE85E7808D884EC1ULL, 
            0xFBEDCCCC8BB1211FULL, 0xA116F6ED18250251ULL, 0x61107FBE6FCF25DEULL, 0x4315CA4AD5741562ULL, 
            0x8327AF036AC98126ULL, 0x20B0BDD1BA788229ULL, 0x3393F82F035C29AAULL, 0xAC7E5449CAC0664CULL, 
            0x9119B2CDB89D1F58ULL, 0xF7E5B7600B23AFD4ULL, 0x4BC7CAEAA4438220ULL, 0x03830D76673456D6ULL, 
            0x958379BBD6FB146BULL, 0x5CFCA39AF4273B8BULL, 0x75D67F3CB2689689ULL, 0x49CF9FAC006373A7ULL, 
            0xE8EB66869D4C2874ULL, 0x86E303630C1B1519ULL, 0xEC17229699BB771EULL, 0xCDC82A5059A3177AULL, 
            0x36EA0CBB2ED4FBFDULL, 0x23E9EB983DDB8AC8ULL, 0x774AF5E1DCBD45E7ULL, 0xBF914B65C4755A10ULL, 
            0x87F54D8FB25F0543ULL, 0x02E92898B9A264C5ULL, 0xBAEC85EB317A2E35ULL, 0xFC477AAD5EADBF54ULL
        },
        {
            0xE4AB12402423850DULL, 0xDEB683AC2A9D3442ULL, 0xFF75FD50DF3B261DULL, 0x886A6E5C1859B9F9ULL, 
            0xFC754283CA62D3F1ULL, 0x825C3334AD7FF5A1ULL, 0xDFB50DCDDA9DA4F0ULL, 0x60BC9ACC27A9E082ULL, 
            0xE228ED264C2616D6ULL, 0x98263C0334AA001EULL, 0x595D139E0491AD7BULL, 0x51E426CDB82801E0ULL, 
            0x6B30FF6EAB7296B9ULL, 0xEF85E7867A6E4F31ULL, 0xF977771D6912C4A5ULL, 0x65A47FD592D4AB84ULL, 
            0x7697265718CDA09BULL, 0x1FDA8643FA16B9CEULL, 0x311D41DCF9483FAAULL, 0x990142690BA5ACDDULL, 
            0xA3643CB02391195CULL, 0xAB458655003D1E5CULL, 0x28C990C368AB5AD1ULL, 0x2ABED345AED0C831ULL, 
            0x6AF20A805569DEC1ULL, 0x3E6E4DD6C6F4EB84ULL, 0x5B6E98BD0EC34AA5ULL, 0xB0AC71B44D9E2725ULL, 
            0xD72EED5F7AE083C4ULL, 0x63AD1CB844A8B27AULL, 0xF41C1EBC018B3CB2ULL, 0x9EC957B179BA19A0ULL
        },
        {
            0x4E2BADE033B7F85BULL, 0x9F3178ABC2280454ULL, 0x5A2E0B21B2B934E6ULL, 0xD95A7C6468D6290CULL, 
            0xBA3636E067E1F6BBULL, 0xEEC6565E3FF87F2CULL, 0xE7636B8DAE03D636ULL, 0xC659B1C15C6086A0ULL, 
            0xCBEDA4FFE32DAF62ULL, 0x127255D855DAA0F0ULL, 0x3AC52095D39BAF29ULL, 0xDE8C3D70AF100447ULL, 
            0x64E8DCEB53446EF0ULL, 0xB6E31727DE99F9FAULL, 0xDE2D5ED4A78A1B94ULL, 0x2D53A676F57A8D61ULL, 
            0x65052EA13CC1A405ULL, 0xE9DC2029DC29EFF0ULL, 0x19809EE5CD2CE838ULL, 0x1023069D40771CF8ULL, 
            0x686597DDD1EE70FFULL, 0x149DC5BB59405E1BULL, 0xA974D2CF3AA0A19AULL, 0x3494795A07CDAE84ULL, 
            0xBEF5CFDF757F7CACULL, 0x6B61B7FD840A9857ULL, 0xE38E8ACD4723B09FULL, 0x71C1E56EC36A8C01ULL, 
            0x98DB8D4E7B9884BEULL, 0x32CE774C4D828164ULL, 0xFEA0E1C8190EABFFULL, 0x20FF0867718FF82EULL
        }
    },
    {
        {
            0xECEB4714EFBA3C46ULL, 0x41C527D9E8232029ULL, 0x51577F8CE3A58B0CULL, 0xA8FA23E4BA1C351DULL, 
            0x0F01ED68674359C6ULL, 0xA337A8EAFE5095D8ULL, 0x9CEA8C3CB6A43F01ULL, 0x4AA165379651D792ULL, 
            0xA06E37788D0A98BAULL, 0x68EC0CEC66688476ULL, 0xDD3FE18526387FE8ULL, 0xA7E36EE51CA45BF3ULL, 
            0xB1BC59E6210FA5AAULL, 0x53793EC772E2DA20ULL, 0xDCD4B887C0CCECF3ULL, 0xE4BCD4216A227D33ULL, 
            0xDFD7436C75485019ULL, 0xE1E759439166EAE1ULL, 0x8563A273EFC8FBE0ULL, 0x974401A5C966F371ULL, 
            0x31B59F1BC5806622ULL, 0x73285F2A419F14FFULL, 0x98CD0697ACA13340ULL, 0x447B68F4AFCBDCE0ULL, 
            0xEA859DD52165B720ULL, 0xB993B7BE4549A63CULL, 0x9164AB2353724BE8ULL, 0x36FE98F3CD981ECDULL, 
            0xADFB94DCEE70818AULL, 0xD2994B22455F9160ULL, 0xAE9CFAA29471F97BULL, 0x4BBD613B6599E724ULL
        },
        {
            0xE4D6DF634EC33BDFULL, 0xD87A614FEA709196ULL, 0xAEAE3C39A2512791ULL, 0x048B63E64E00697CULL, 
            0xAA6D4D0C18AB7C67ULL, 0xC08FD4B400789D99ULL, 0xEAE68BB186AB8604ULL, 0x3B49F2BBE1AAA3F7ULL, 
            0x73994338DBEF8214ULL, 0x941767E71EB8349DULL, 0x58722CF5A605CBCAULL, 0x17DA76B9CB5E032BULL, 
            0xDC4F45BE44DF146CULL, 0x71676B3B6D7AE64EULL, 0x4FA96DDC783D44ACULL, 0x1354ACB61F57CEE2ULL, 
            0x74E706DFCDDD3FA3ULL, 0x8F6C313DAED57CA3ULL, 0x75A8904E253D63E2ULL, 0x9B8C9037DF2BE7C4ULL, 
            0xADF0FD90526B8CF4ULL, 0x69CDB58D63BDE6D6ULL, 0xC0CE4899DE344FDCULL, 0xC98CCD6FA49EF329ULL, 
            0x0C7F87B0D49BD848ULL, 0xB7BC9EE145F33C23ULL, 0xAEB4EFB9A9B5F2D0ULL, 0x3C35C4B8996BDF84ULL, 
            0x85B440E0CB80B3AAULL, 0x5DBD660DA1930256ULL, 0xCD7932637C1ED40AULL, 0x742A24B8348BD0ECULL
        },
        {
            0xEC07C7E5D1AB8124ULL, 0xBA8FF7ED2E51F32EULL, 0x3FF0D8B2A47768E3ULL, 0x74C178BF8421A7D0ULL, 
            0xB458B5BB25051C8BULL, 0x1917145C55416E18ULL, 0xBB1A7452BFDDCBAAULL, 0xF984BEBEB6F6B379ULL, 
            0x1898ACBE380CF9DFULL, 0xE8F257E73E6A458EULL, 0xE9B6126D7DC46706ULL, 0xB6A6327C919E9E5BULL, 
            0xE4253C16EF06F050ULL, 0x1BEE517099BA5A9AULL, 0x248B0B13EFD16E11ULL, 0x571DD031DC35DD8DULL, 
            0x1A5DA653D881C1ECULL, 0x322136B07F82AE6EULL, 0xCF0C459EB392A6A7ULL, 0x5C5D51EF2564767BULL, 
            0x8E054ADEF960FD66ULL, 0x70AE15E054A41C36ULL, 0x6EA7F7894C37C738ULL, 0xECD838F4085AE180ULL, 
            0x203ABBFB9FDCE520ULL, 0x00F5112A1DE19A63ULL, 0x6511C10F6B6CE7C1ULL, 0x53DDB669A5A38C02ULL, 
            0x8C7F29C2A01E09CEULL, 0x223AD7F48AFA70D1ULL, 0x3D5F71011BF793F9ULL, 0x8A2784B5E7C051CEULL
        },
        {
            0x0AA6F19FFE1471EAULL, 0x792174D8F00C96D2ULL, 0xA21FE4AD6097C443ULL, 0xA6DECE2568F9D857ULL, 
            0x5ED098019379973FULL, 0x1C688B12BBFE47FBULL, 0x337A7F8FE70D8258ULL, 0x31AE90D5DE046574ULL, 
            0x293972105A04B983ULL, 0xD60D71EECD17F705ULL, 0xBEBAC67CD6D65A8BULL, 0xABE661762B4614E6ULL, 
            0xCD9BF98FF343875FULL, 0xE4928879C4B8E673ULL, 0x80BE71EFB67AE8A9ULL, 0xF5B3CF311BA071A1ULL, 
            0x279D48B5A305C2C7ULL, 0x1BA4E046143EF27AULL, 0xCF1BEAABE71CD345ULL, 0x6B7A1D8E44B5AB08ULL, 
            0xF2053FBD54353F07ULL, 0x4F2A6FF99D14D4AEULL, 0x0B4366B8FEEB3B22ULL, 0x980A1A18CC87C680ULL, 
            0xA3A45C4CE224CA2FULL, 0x96F0DA21595CFE7FULL, 0x75AEC000FB129177ULL, 0x91710189495BD141ULL, 
            0x07D45959F570E551ULL, 0xBA21FF0BE85EEDA3ULL, 0xFECADC26B9C39E92ULL, 0x56E5A04E6903BC6AULL
        },
        {
            0xC2B62A293C45B634ULL, 0xF701B92567CA428CULL, 0xC3322DC0ECAC9F87ULL, 0x531C7A616F12FEDEULL, 
            0x541ECC20B72DFF0EULL, 0xDECD28ABD00DEDB7ULL, 0xE2B88F4134130206ULL, 0xE19D501AE6423081ULL, 
            0x506F3ABBE1F3A74EULL, 0x63515428BB1A54A4ULL, 0xA186A9090D2796CCULL, 0x7B34D935D0D3A764ULL, 
            0x89C2A0D969A400B2ULL, 0x7A001771D5BF54FCULL, 0x9CDF08A0CCA22824ULL, 0x8B59B0EB34D6C138ULL, 
            0x80D395D6B4234761ULL, 0x2F1C6EB2D5AAAA31ULL, 0x5EA0B807A5EAA6F1ULL, 0xF1E8B4614139AEABULL, 
            0x7921C2FA649D10F2ULL, 0x75740AC696DF3400ULL, 0x87CAC1ADB75EDCE0ULL, 0xA5ABD1FB40CD09ECULL, 
            0x6924A317612BEAF2ULL, 0xC88019B918342064ULL, 0xA15ABF9D41845B37ULL, 0xEB8A431B2347772FULL, 
            0x0935856AA0D4C253ULL, 0xE761DCCCFF274178ULL, 0x629DCC2C7709C1E5ULL, 0xF2BE85DEE974D1B3ULL
        },
        {
            0x41D74C2C8A7857A5ULL, 0xE5770FA2A78B018DULL, 0x89C613F942075E0BULL, 0xD669230B4E94A5E0ULL, 
            0x98BA6AF628144507ULL, 0x0A89E8B204D8BBF9ULL, 0x1CC6EE27807B1FA5ULL, 0x5EDF571A68BEC6BCULL, 
            0x68CF7D1D87901A62ULL, 0x6F9B0C5C14AB3172ULL, 0xC43D6C75962A56AEULL, 0xD9A48BE81CB7B6A1ULL, 
            0x6D858DE8D7620299ULL, 0x9BEF6DB22011CC48ULL, 0xAE275ADF223D8123ULL, 0x677133FCBFF97771ULL, 
            0xA53448C12B13C392ULL, 0xDDFED8F155E9B689ULL, 0x9BC12D86F7E88820ULL, 0x3D39B68850769749ULL, 
            0x41C55B42ADFCE372ULL, 0xAF3745B018A1B1A7ULL, 0x3166B35BE3E231B2ULL, 0xAE0ECFA5E3E5638CULL, 
            0x10B628785F21AC2FULL, 0x299576B80C4BFC1AULL, 0x1C749B393C2968E0ULL, 0xD25474A1AA6C2919ULL, 
            0xC8E20FB3371D7657ULL, 0x32C2919443905714ULL, 0xD0E2F0D8FF654BD0ULL, 0x6EA09E377DA38BECULL
        }
    },
    {
        {
            0x3A4AA3C8C991D299ULL, 0x172F3AA785F63576ULL, 0x59E37F6EAD1232D4ULL, 0x8100912E27F77AD9ULL, 
            0xC29AE6A36932F2EFULL, 0xF78291B40D1AFF59ULL, 0xCF3AEEBF09B9248EULL, 0x461DC96616ED663CULL, 
            0x951FA2DE845B30A9ULL, 0xC34FA6B03A76AF31ULL, 0x205CD13ECB4D49A3ULL, 0x13682631C867A1CDULL, 
            0x6A9D2321C219DCE2ULL, 0xA875B82224B9DD67ULL, 0xAAE979F7E67A4849ULL, 0xC1961C0B42771E75ULL, 
            0x24CB9BEF674D3625ULL, 0xEF6D7C7649080CF1ULL, 0xCC1FF33D9265B12BULL, 0xC11C54A2DC8435F0ULL, 
            0xC797BB9EB340A056ULL, 0xAD1BB04486CD7B09ULL, 0x2784287D7F8A033AULL, 0x3391C85402A9421FULL, 
            0x18CE662B9A614801ULL, 0xF8C07936DA705243ULL, 0x7055DC214CA5C89DULL, 0x1F1B5408F1C55301ULL, 
            0x10C7EC68597153A7ULL, 0x207DCB6AB0064082ULL, 0x82CEEF1AB9774704ULL, 0x340A15ABC859563BULL
        },
        {
            0x7C5AAD7522F07C41ULL, 0x836491267E4057D2ULL, 0xEE12DEA82EB173C5ULL, 0x16C6F387D664C4A7ULL, 
            0xAEA81864955A8453ULL, 0x5436FB8C1B9D88B6ULL, 0x90847D4DFFD787DBULL, 0xD50AD8DEFC3E9D66ULL, 
            0x37314E35BBFC2197ULL, 0xF1BD847A02AF2145ULL, 0xD14D3E9041A30379ULL, 0xC476353CC1F9BCD3ULL, 
            0xD3B70D06B36012FDULL, 0xC8BD1851D880D4B0ULL, 0x6E2D4AAD2352783CULL, 0x31000C7B5358C9DCULL, 
            0xC801911390B1A057ULL, 0x4B051E813E1708CCULL, 0x31B68B356E3E4B20ULL, 0x0BD7B794BB737C75ULL, 
            0x5259917A83084325ULL, 0x9AFC049280E51C60ULL, 0xB29A9183F70D61D1ULL, 0x0B52F7B636F99239ULL, 
            0xC24C4FF51D4BF309ULL, 0x7B27621BDCE91972ULL, 0xB89BF7D40341A0DFULL, 0x39B69378A201180EULL, 
            0x28BC896A56FB357FULL, 0x5790D2310558390EULL, 0x8C8CA7DE694C1FCEULL, 0x934D0879EB047B8AULL
        },
        {
            0x408FF3A3D2986125ULL, 0x4B82D5098ACEEB42ULL, 0x44AE7E727783FC8EULL, 0xA72C932191C58B26ULL, 
            0xBF5B23CCABE5DC76ULL, 0x8A9B3C5AC1703596ULL, 0x65EC63099DF18348ULL, 0x0A10671CA86C76A1ULL, 
            0x6AFA5C7594369172ULL, 0x80CD0A251ADC7346ULL, 0xEC92856D992B4A50ULL, 0x3DCA2C7C6F644703ULL, 
            0xD8F7C7E30EBD3A63ULL, 0x0C4C653D6E25D2E4ULL, 0x9A2089D09AF93654ULL, 0x28687A6091702C18ULL, 
            0xFC3CFFF5C17907F6ULL, 0x2BD9F7D7C0AB788CULL, 0x870EE5CEFA92CD6DULL, 0xD121A58A44029654ULL, 
            0xD0927475CA7B46DBULL, 0x27AAB410CF486156ULL, 0xCD52B8F12A425D77ULL, 0x990C34732B20A0F7ULL, 
            0x7F2DAA7EB8377030ULL, 0xA45F4310ADDDD114ULL, 0xA608091744E3B8D7ULL, 0x8B32A02A60E68159ULL, 
            0xE704D77FC1F85600ULL, 0x037D682D28B5CA91ULL, 0x18706750D1DE5284ULL, 0xA898889D042ABC15ULL
        },
        {
            0xF025C9A4A7249E8FULL, 0x1FD70E590ADF29E0ULL, 0x3A385A0F4842023AULL, 0xA681903793CD5EC3ULL, 
            0xC3F6F565A643652EULL, 0xA8C469E24BF8DE93ULL, 0xE46923F582A0E178ULL, 0xD22FEFE26697DAC5ULL, 
            0x11F12E596C8FF616ULL, 0xF8480BE12C0C9BFBULL, 0xB55ED69F5DEEC7C0ULL, 0x33A1183648E76BB8ULL, 
            0x3BE04C7C5EF37450ULL, 0x02D448CC03AD8E4FULL, 0xC73FC703A6E1F6AEULL, 0x51525A6D530189D6ULL, 
            0xFF2E62A13D284EAFULL, 0xB4F8926BBA8B36E4ULL, 0xF46F584FEA956E4AULL, 0x7E4E3E5564F175EEULL, 
            0x76F81BEA21962885ULL, 0xC8B71CF1934FFA02ULL, 0xD7B7EFFC939FBC89ULL, 0x008F08DDA4E25FC3ULL, 
            0x36D37E7476EC7916ULL, 0xED516619D98C63BBULL, 0x4F8AAFD8622E892FULL, 0x0A3BD5356AEC15C3ULL, 
            0x8733324F39012F1EULL, 0xFC2DA4FE7EC1FECCULL, 0x92D7C644744E1A98ULL, 0xDED660FB7EEC288DULL
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
            0x21D4882BF5F2F1CFULL, 0x328F087801B2D790ULL, 0x5E0D70340A060AC1ULL, 0x65A5A2BCEF52DB46ULL, 
            0x8F50CCCA69456B99ULL, 0xB7EBC45733B5526AULL, 0x4C71E4EE33333F13ULL, 0xBFF185F19D070ED1ULL, 
            0xAC37A2FC72AB827CULL, 0x522930DF2AE1A552ULL, 0xEE2D4A6141D43F04ULL, 0x2AFD5A608455958BULL, 
            0x2369E6E30FC48E89ULL, 0xBACC7280A1AB3F87ULL, 0xEB1B2B1669191D30ULL, 0x8AC66EA51AEC334DULL, 
            0xFE0FD4FF2C60A275ULL, 0xF03B64DE043FAAC8ULL, 0x43A2B62A78587F00ULL, 0x7288DDB5AF8E1DE2ULL, 
            0x87E2B7EEF8D11A99ULL, 0x6A06ABC304C61525ULL, 0x92AEC1EDA94058B6ULL, 0x07F020AD540088B7ULL, 
            0x12592DB5EE8DD464ULL, 0xB405CD55261F8A40ULL, 0xB78C9382D82B94F2ULL, 0x346BD08C05DE8981ULL, 
            0x21791B247230DDE6ULL, 0x075525FD25C17F51ULL, 0xF02BC57645D7508EULL, 0xE379B894EF5A84D7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseFConstants = {
    0xE0D90B69CB8B573AULL,
    0xDD3454BCFA3F7F05ULL,
    0x8A28C79DDFB94E9DULL,
    0xE0D90B69CB8B573AULL,
    0xDD3454BCFA3F7F05ULL,
    0x8A28C79DDFB94E9DULL,
    0x5C1E9904BFF0E597ULL,
    0x8E69602E55E429F5ULL,
    0xF6,
    0x17,
    0x26,
    0x97,
    0xCA,
    0x3E,
    0x48,
    0xA4
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseGSalts = {
    {
        {
            0xF0EE47F953C82E62ULL, 0xD06A2DF6711304C1ULL, 0x3B398D63C0FB328AULL, 0xCE68DB85AF97AD42ULL, 
            0x7FD59EFC2A760EB6ULL, 0x559F916872B4CC1EULL, 0x94CC4E2F59D45029ULL, 0x7B0692EC81E71EFAULL, 
            0x1ED59C4746E40F3FULL, 0xFED4BA4205E92884ULL, 0x9749EB503FA3F3ECULL, 0x8A1D5A0BEA49C1A8ULL, 
            0xE40CA22F91034F4AULL, 0xBA98E1D2A2AAF993ULL, 0x4D7EF9A605AD69B6ULL, 0x8243BB6325488C9DULL, 
            0xC991DB86EC8C2E25ULL, 0x664716DA1A37CF43ULL, 0xECC738C480F81D64ULL, 0xA9A8E3B6F7AA2E7DULL, 
            0x8476BFB117F6B2C5ULL, 0xE4384E54E40E2C41ULL, 0x97CBCD4CDC7907C4ULL, 0xD8C037662F330005ULL, 
            0x03217503D5DED3D0ULL, 0xF6A4EEF6712A92F4ULL, 0xD0FA6DE54105F3D2ULL, 0xEA0931ED0A564FB8ULL, 
            0xE77B542746AB30ABULL, 0x02F5AEB0E4D8D719ULL, 0xD7117E20183FBDA0ULL, 0x90F802C13996D2E9ULL
        },
        {
            0x56CFEA8716B5EAF3ULL, 0x2BC33F08C16778CBULL, 0xF42721EBB541088FULL, 0x374AD63B6EDDCDF1ULL, 
            0xF18967BFCC694317ULL, 0xF6C79F091B8F385BULL, 0x4656AEE7614A955FULL, 0xD1F04C8AB394B9CBULL, 
            0xA32A8BD78A5C3877ULL, 0x082AE80EC6E36025ULL, 0x2D9619F8B585E05BULL, 0xE5BEA6E00E6BA499ULL, 
            0x168E5D5D2B3904EEULL, 0xA70A06A9DBE9E6A1ULL, 0xA3151FA0D121151DULL, 0x48A214B7793D146FULL, 
            0xE130BA712ACB2913ULL, 0xBEC01C79B4793EE3ULL, 0xEB4A94576A35FEA4ULL, 0xCD73740CA9A58044ULL, 
            0xB90EAD7CFF5ABBBAULL, 0xB063EFB253DD3A49ULL, 0xFB759A8E88431B44ULL, 0x958D3FFEA68217EDULL, 
            0x79E97CEDC99CF490ULL, 0x68675BE9B33946DBULL, 0x9D56ECBC909D7A97ULL, 0xDBBB52DDC8C5E338ULL, 
            0x3701ADF821EA7D28ULL, 0x84AE6EE366865142ULL, 0x866299B9C3659C56ULL, 0xFA65D5FD1DD5ECC5ULL
        },
        {
            0x2F4627F8D06C8BDBULL, 0xC6FB2C7E94B0217BULL, 0xEA2B3EF547512BF4ULL, 0x04247660A5C55136ULL, 
            0x4AAF74741CD0532EULL, 0x4289DC105DFA82E1ULL, 0x857A44B5B5214B9CULL, 0xB7E7E431F66DBADBULL, 
            0x9BFB4F09DDE1CC09ULL, 0x63A4E8A9F6124C74ULL, 0xDC0A46B02BA67C74ULL, 0xB1CBEE6E68F85DFDULL, 
            0xE7F91AAC8B9923B5ULL, 0xCDF828D39824B589ULL, 0xD69D88D371902538ULL, 0x1442B49FB408A942ULL, 
            0x0F8B58E3C6B75743ULL, 0xC87F61170CA05A9BULL, 0x5937CC76EFA8DBC5ULL, 0xF118711BBE15F63EULL, 
            0x4FB1EBE3842E95DCULL, 0x42A7B5A916044538ULL, 0xACE6DFB4AB493F8BULL, 0x500754D66F1DE391ULL, 
            0x760DFE8DEEACEE7AULL, 0xF66E893A88C53FBFULL, 0x4A1504017012AB08ULL, 0xEF0F84BDFDF39CBEULL, 
            0x2D8CF10575E53D71ULL, 0x9B96E00137ED3305ULL, 0xFDD26C2E184F8B2BULL, 0xFF1B212E826676D1ULL
        },
        {
            0xEDDD77AC3FBFE9ADULL, 0xE33241F1A8999436ULL, 0xA8DCEC0620B04BECULL, 0xD99C827BA75CCBA8ULL, 
            0xCEB86B8247CF91CFULL, 0x3E2543960BD6D6A1ULL, 0x6832E63A5587846EULL, 0x1C65B5D33D8EF613ULL, 
            0x7B6A6047404D6BC1ULL, 0xDCF768E14D070DD7ULL, 0xDB8432F77C28CE02ULL, 0x9C68CA05EABC151EULL, 
            0x4753B6389C02E8E6ULL, 0xDFCF8B6229E72716ULL, 0x05895027BCCB298AULL, 0x95543C5ABE03B26DULL, 
            0x7C9BA688970BBE8FULL, 0xE9B502A460E82A38ULL, 0x5ADFD39C35046155ULL, 0x2818EE5786102495ULL, 
            0xE044262B64E58B46ULL, 0x27C1547C1797A92CULL, 0x6C6891373448A0BDULL, 0x64D47DA90C171E4DULL, 
            0x68C49B02C82C7611ULL, 0xE919CEF35BBB8571ULL, 0xC8977ED029531165ULL, 0xBA30DBAFAC2EB001ULL, 
            0x64F7390D67B69C41ULL, 0xC4E103DD8B948C6DULL, 0x0D0B1CD8AA9D06F6ULL, 0x46F6F18671464585ULL
        },
        {
            0xEB0B69DF6261822BULL, 0xE7D59A655CFE964AULL, 0xD068C2CA25013036ULL, 0x9DA21B00E6070FCBULL, 
            0xD5B8FB8819B5FD7AULL, 0x4FE4313BD21D60A5ULL, 0xF673A0446D7460A3ULL, 0xE8CD09C2ED3F4F65ULL, 
            0x374B9DACC18DEACFULL, 0x5F78DF6DDD0CA2C1ULL, 0xDE0C13D99C9D7E19ULL, 0xE898B2C79CA9A49DULL, 
            0x5BD71AA87B02C719ULL, 0xD0F142ED02AAD37BULL, 0x5FB078107D1BB3CDULL, 0xB1C85D5C37B54EC1ULL, 
            0xFD07209BD4A2D583ULL, 0xE5E5E44FDCC3C150ULL, 0x3DBCB6E13065FFC0ULL, 0xFBAA796ECC34CC48ULL, 
            0x755C400E8B1C5DC6ULL, 0x74A36EF68B03A048ULL, 0xCB207C43110F6D74ULL, 0x39F927595275BAD8ULL, 
            0xA16D44D099CF55E8ULL, 0x9A9D7F680687D232ULL, 0xC3E0FA4546FCBDE6ULL, 0x3BBB2BC752EDA8F2ULL, 
            0xAD5FE5A9E9E4B97AULL, 0xBF2F217E501E207FULL, 0x3AA65A62F1E356E7ULL, 0xD325881240EC9777ULL
        },
        {
            0xCAFD0601B812ECF5ULL, 0x4190C5435EFB7E33ULL, 0x537362E0BD8C89F9ULL, 0xC682316058A635CDULL, 
            0xA4B8ADFEC911BB8DULL, 0x1BB389ECA4708C10ULL, 0x2CAF6638B2820A6BULL, 0x4F60CF0288635B50ULL, 
            0x235B55D6AB4F1157ULL, 0x4F43051545504F79ULL, 0x31161D8D7E8AB161ULL, 0xFB4846EB7259A109ULL, 
            0xBDB993CA1C4F9259ULL, 0xDD85BD187EC5707FULL, 0x27231BBD02C36D4CULL, 0xB7F2F99925F1C33CULL, 
            0x79444C4BB0EAD846ULL, 0xC4A7CB63AF05486BULL, 0xFB4AF8AE0FD3C09BULL, 0xCC3C1D1B30F9A079ULL, 
            0x50A57053FB504AF7ULL, 0x340BCC8A54EE979AULL, 0x77AAAE5D34ABE64EULL, 0xAD14BAB5CF946C3FULL, 
            0x4D3425E190FDB169ULL, 0x22F2DAA08BF36197ULL, 0x7AB2BBC8652EF847ULL, 0xDBD5236170B5758FULL, 
            0xDC23AC3EEB1A3D56ULL, 0xFB900B33792AE9C3ULL, 0x32C85380EDD65666ULL, 0xAC9BA8E1DF3D80A2ULL
        }
    },
    {
        {
            0x89DB01BFE580C08CULL, 0x41936A2EBDD3858BULL, 0xBD02BCD2CD189D5DULL, 0x868913872853A36EULL, 
            0xAA79B96EBBA86A3DULL, 0x400696B9FCBB47F0ULL, 0xF63DB3397C76643BULL, 0x64EE205C0364C51AULL, 
            0x886A3C47C26CE2C0ULL, 0xDE8AF485F90B9295ULL, 0x1D129B8B1A768E65ULL, 0x2FDD4C10C2FA2F02ULL, 
            0x09ABC642BE813BB3ULL, 0x92FB3C1EDE348E92ULL, 0xF67539F353FDF367ULL, 0x0CAF38B044082268ULL, 
            0x3C4E338F56548EB5ULL, 0x36022723E89378E3ULL, 0x24EF20015DCA3A30ULL, 0x2ED866A02DF5A19BULL, 
            0x898314D427C0A29CULL, 0xC2E053263D200996ULL, 0x886BB7A7E74D7909ULL, 0x476AA07E687DBD92ULL, 
            0x839BA23924F2C8E4ULL, 0x2DF89B056FD6E8FFULL, 0x35BEF6218AE2BBACULL, 0xB9602EEBB78C8E2BULL, 
            0xC2AE5DBD67C7393DULL, 0x63F5E172129F2086ULL, 0x796036EA01907986ULL, 0x8B5830F49279C557ULL
        },
        {
            0xC93565001BF764E8ULL, 0x1CCA323EDB719539ULL, 0xCF23F7B03FFA7DD1ULL, 0xD8B3790482DE6FFBULL, 
            0x11EC9CAEF4BDA35CULL, 0xF2A8D1962C8A1B7EULL, 0xB0BD2D72E25844C4ULL, 0x5FA51DE8B7F94F25ULL, 
            0x0606E95CC12D8FEDULL, 0xF48952243AEA004AULL, 0x3B6749986C0E051FULL, 0x6B31EDD09A146BBAULL, 
            0x6883B086D534F9B7ULL, 0xB834FD7429657C23ULL, 0x13C54202AF8CE966ULL, 0x9E047F2E6F84E162ULL, 
            0x1D9F2CDED31C7197ULL, 0xBB45B53C5725D326ULL, 0x41AA29210778B925ULL, 0xC0137993EBFD217DULL, 
            0x11F33B9F42552ED2ULL, 0xE3EEE934FA0739C2ULL, 0x6381905CBCC18C4AULL, 0xC3799500A4078A37ULL, 
            0x06BA8A0A776FC462ULL, 0x1D00669FD3B78D66ULL, 0x2A5F627773457465ULL, 0x5A98BB03772FC8DEULL, 
            0xA8FB8FE5EC60BE88ULL, 0xA50E989C54C0DBB8ULL, 0x3C4FBE24A7B49C51ULL, 0x3593A6C8048F9E3EULL
        },
        {
            0x4A82D9F3118601B4ULL, 0x2555B7E4378F6218ULL, 0xFF44C10D25BDB98BULL, 0x0C9EF8054F3F477BULL, 
            0x1803D4FA957F38CDULL, 0xA31A14FE40C15514ULL, 0x0FB14738BC4CD1F6ULL, 0xACD9ABB8DBBAE3A3ULL, 
            0xB5B1300C7A931F85ULL, 0x078C7142380440A3ULL, 0x178D3BF454CE9276ULL, 0xA592FCEE496562FCULL, 
            0xE5CC304B79E81B71ULL, 0x6ED86BBF13212020ULL, 0x7BB7B593DEBE82DBULL, 0x144F1A09629D363CULL, 
            0xF958877FE8598D9AULL, 0xFEF7FDA5F6A15B32ULL, 0x965F14893C001A8AULL, 0xDC5AEAE8F74F5119ULL, 
            0xC7794C59ACA87C86ULL, 0xD984E4DB6379B7EAULL, 0x6B9EE44315988291ULL, 0xE62B0D16618DF39BULL, 
            0x13E6369D97E9E4E1ULL, 0xAFBB1E2867D625D4ULL, 0xE6FB6D42907BD995ULL, 0x42EA04C871E5F2DCULL, 
            0xC41125BA999C86F8ULL, 0x0E651746D6B22258ULL, 0xDEED5ECDFC326948ULL, 0xE90F8B601F6B3B33ULL
        },
        {
            0x5010E6466D96CAD2ULL, 0x4CA24CD6F4094554ULL, 0xF9E2D0F91EF4759BULL, 0x5A36F7B2F5C7780AULL, 
            0x99AD1AB4AF271B41ULL, 0xAF87EF440B0824B4ULL, 0xFECACD2C8514D157ULL, 0xD11E83DC3CE7B6A0ULL, 
            0xD749A4DC320FFD26ULL, 0x7BA497D568030337ULL, 0x6797AE5F8E3272F7ULL, 0xBF0A3D275078A8E8ULL, 
            0xDEFD810A2C0089F3ULL, 0x618212B9BAAA0373ULL, 0xF1FBF70CA2F49B69ULL, 0x58C0B3BD8E703516ULL, 
            0x2D61AEF85D9E8F33ULL, 0xEA994E99E43D363CULL, 0x7FF5663784044A39ULL, 0xC7DC04534426B028ULL, 
            0x4571F03FF673A84EULL, 0x0C136C97EBABBAFCULL, 0xC23A19A4CA003DEEULL, 0x78F2BFE745A33178ULL, 
            0x928C64B0008C5478ULL, 0x2A4D398A9FE625ABULL, 0x67BF7CB76C71253FULL, 0x53021044C7053CD8ULL, 
            0xB19EA73F36017389ULL, 0xC5C34D5270D97B8BULL, 0xC5081634D2A79CE8ULL, 0x3F3D8EA74DCB437BULL
        },
        {
            0xC9873C3CDEC834D2ULL, 0x9E87F08BDC511CAAULL, 0x799CFD01CE5061E3ULL, 0x785E082C618F5DEFULL, 
            0xAC3FE9DB9BBD80FBULL, 0x836D23BAF3170FCDULL, 0x765C02B7FBBF4393ULL, 0xE5092BD89B3EF6B0ULL, 
            0x73C41A191DA2568AULL, 0x1553C531AFD824EDULL, 0x300C8826977431EDULL, 0x6925AFD848235E6BULL, 
            0xABEF0B65C9544DEBULL, 0x4CC7FD4BFB59E8FCULL, 0x39FEFC3258F070CFULL, 0x87CBE71EEB11CD12ULL, 
            0x5BB98E8B5AD5850BULL, 0x86E307389EA248DBULL, 0xBA1E65BC304E9CBFULL, 0xD8A432E35B29B582ULL, 
            0x41E3ED5FD54A02E3ULL, 0x7658C3503815B28BULL, 0x0F95E01F4ECF8271ULL, 0x52DD1D1CE3D02E99ULL, 
            0x9A0A87EC86CE44EEULL, 0xE35D597009EC691DULL, 0xB3E7817F23607D7FULL, 0x76553F0E266A489FULL, 
            0x0D538A43063CD7F0ULL, 0x19D598AF48E33F74ULL, 0xB6A3344995014C8BULL, 0xE554DA428DFBEDEBULL
        },
        {
            0x64738BB1F0BD5E4AULL, 0xCFC004DA0B3689D8ULL, 0x858C28EE5C02B5D2ULL, 0x2CDDC2D5E56584A3ULL, 
            0x162747CE12A2C6A1ULL, 0x4D81BBD325C1B0D6ULL, 0xD7B4B6F411C0E187ULL, 0x471E05914AB19B09ULL, 
            0xACDDA66C2D84764BULL, 0xB76C77882C03E6CAULL, 0x954B2293C59BD947ULL, 0xEEA1A626EA642CD0ULL, 
            0xE3FF872634137496ULL, 0x62291533FA0EA82AULL, 0xE1D9ED5F0D7BB6E8ULL, 0x6A0481534C29252EULL, 
            0x6287D7ECE75D9EB1ULL, 0xC5F5DB4A8052E9D5ULL, 0x93EEAFB29F7C5C9BULL, 0x2A403C2F2C020C29ULL, 
            0x0A65F2C11A000339ULL, 0x9D6E53F97D34AAD7ULL, 0x861DB7EF4D55F2B2ULL, 0xCF42DA7AD129E835ULL, 
            0x46445B165260481CULL, 0xBE77A43DA9CA0B0CULL, 0x67A6F5FE7F0818E0ULL, 0x47DCD2349CA4AB21ULL, 
            0x2F7823C41FBBF7E8ULL, 0x9C373FCCCE9454D6ULL, 0xB391C7C4B72023ACULL, 0xB203AD87F0708357ULL
        }
    },
    {
        {
            0xAED2D5FD9B4EB215ULL, 0x410DC8FC47334796ULL, 0x5941E0ADF38ACE8AULL, 0x11801633C0293EDAULL, 
            0x7CCD70A29C3D1271ULL, 0x700EB32DDABB361BULL, 0xD4A8A86B2465AE01ULL, 0xA55B5CB23C56D213ULL, 
            0x07522DE8F7C594F3ULL, 0xF5EE772B300F149DULL, 0x661C8288B37F1D73ULL, 0x7876995B8B33F14CULL, 
            0xAA8F5952C5C15232ULL, 0x2884B835D3D5D473ULL, 0x00C011DEBC7EC45CULL, 0xCFA16E2D0ECCCF6BULL, 
            0xEC74366D73E373E5ULL, 0xD3C19C24EBB3CDE9ULL, 0xC9A8B69AAA666275ULL, 0xE311C90D474CCFF6ULL, 
            0x694A28F19A215652ULL, 0x865C6B097A7000EBULL, 0x76C636E44B91F4A8ULL, 0x795954C4CB909FF7ULL, 
            0xF78F9CF848988AA0ULL, 0xF261D573D5B2578FULL, 0x17350CDE3D053A72ULL, 0x912FE912944EB83FULL, 
            0xAB776DDBFFB60B33ULL, 0x685FE9B5FE63DBD0ULL, 0x3F38F4192023FB33ULL, 0x0A6E54407825C363ULL
        },
        {
            0x41E0F4F7AA3B1A99ULL, 0x1D770E7C02A20CEDULL, 0x8D43394EBF060639ULL, 0x9C0DFEB929ACCF65ULL, 
            0x2A443B29677B9AAEULL, 0xE59D9B686DC41092ULL, 0xD446CC99F207629EULL, 0x329415430D32EDDFULL, 
            0x6885EB1BCE08D273ULL, 0x0E23F5370FBAA034ULL, 0x36BC7903031C07FEULL, 0x758F64A3A1912998ULL, 
            0x10A010E57CA25F90ULL, 0x8A5EBD2574A83D8EULL, 0x3902F8915F0F6A1EULL, 0x83B6C520E03D3577ULL, 
            0x64C3E7726354EF8CULL, 0x9EFD2616AAC69802ULL, 0x90FE8B631A40D565ULL, 0xA7460BC72BCB959DULL, 
            0x3F3F72E823942AC0ULL, 0xB199DF1D940F6914ULL, 0x2B1DD2189A14654CULL, 0x2575379CEC9C23CDULL, 
            0xDDC53CEBC3ED628BULL, 0x4C70E5F360BBD83EULL, 0xD22FD0A42F901CDDULL, 0x0D554CA99429DFA9ULL, 
            0x312A3C2C1105864FULL, 0x0956FE3A503DC094ULL, 0x2D91A63B10B64309ULL, 0x9E33169BD3870375ULL
        },
        {
            0x829A54830E7F28A2ULL, 0xAE298B38279F7385ULL, 0x8873CDBC4F9870F9ULL, 0x95D7A5FF7B86F5B0ULL, 
            0x44216CF76EEC67D7ULL, 0xC2F81D0EEF4EB2E3ULL, 0x233A8BD7346EA228ULL, 0xE069A56D197A809FULL, 
            0x38117DFD5927D084ULL, 0x937F578CBF83EEEAULL, 0x6EB1059F3A8B25DDULL, 0xD2F6909F8490BB05ULL, 
            0xEB82A098BDF2C855ULL, 0x5DC4BDA0F951EC6CULL, 0xF4EED4709D3E4EB8ULL, 0xA4DEF004DE50A01EULL, 
            0x0E30F51B79EE2430ULL, 0x8FA81AB2D37B5D04ULL, 0x9BD2458304C2CEC0ULL, 0xBD672958E4886959ULL, 
            0xE94EF39B2B5C607DULL, 0xD91810F701F4626DULL, 0x3EEC475CB8266022ULL, 0x6997C259D239925CULL, 
            0x6E19EF13052B772BULL, 0x6AC0435B4A143B21ULL, 0x55A5EF0AF17B46A6ULL, 0x3C3B3EC56955274DULL, 
            0xFABE106052CBBCDEULL, 0x1D633A7D8CBF84C7ULL, 0xE052707704380AC0ULL, 0x9F3327161B90F085ULL
        },
        {
            0x2109866DB8297C29ULL, 0x656729C57198FCF1ULL, 0xFC30009B7D1A3D56ULL, 0xD3D018F807A19B58ULL, 
            0xF569552624F39567ULL, 0xF5046DE5FAB6972DULL, 0x591797C3F8902E5CULL, 0xA1E95172F7A0FF32ULL, 
            0x7BFACF13813A4DF7ULL, 0xD45A1B46D52C7033ULL, 0x1E36059469EFDDB5ULL, 0x4B68DB9504407272ULL, 
            0x494EEA70C14A7109ULL, 0x5543D9D52BB8580DULL, 0x315BE87EF940BA38ULL, 0x7C4CE1733F54D416ULL, 
            0x761420734DCCD871ULL, 0x4EB23171F49A0821ULL, 0xC6BEBB36D609287AULL, 0x557889F22EA27F23ULL, 
            0x30B59FDD7C2DB140ULL, 0x0C411A99447F98A4ULL, 0x7EE0D031E10A8AD2ULL, 0x8B1E2DB154A35459ULL, 
            0x11CE2761C16CB61FULL, 0xC6F5340808C0DBA5ULL, 0x4E144D7D3341C674ULL, 0x6C001A4B262DC120ULL, 
            0x8A2BA09FF9CE255BULL, 0x3134A69D47F31473ULL, 0xFC3EC4F16E75A86FULL, 0x4CD6A93512560616ULL
        },
        {
            0xB8956EE72C440C0DULL, 0x0E4A5585BA7F14C4ULL, 0x0ED50B62E6DF3C5EULL, 0x502FAB3BD97A8FFBULL, 
            0x139506D28CFB9A27ULL, 0x930443D2D6AF43F1ULL, 0x5071D7285A4CB0A5ULL, 0x798370FEC4FD4BBEULL, 
            0x7ED70DA6A40E0E71ULL, 0xFE0F5832E451B867ULL, 0xE27FDC6A587BFFE9ULL, 0x63919244CA3F1749ULL, 
            0xD7DCDFB5F19C945BULL, 0xA3FB59916FC87848ULL, 0x2633CCBF33F77516ULL, 0x9C200A4260277EA3ULL, 
            0x66062E2797A51B2CULL, 0x82AD49E10B1CA83FULL, 0x306395A13A1890AAULL, 0xCBFB70E2053A64C8ULL, 
            0xC3D1CBF04BC53E40ULL, 0xF4B5D127D22ADB84ULL, 0xE121DEDAC8A42348ULL, 0x7D04C0D0213C228DULL, 
            0xCF952F38695F9234ULL, 0x3A87283A83B4D5CDULL, 0x768D8B2D873CB241ULL, 0xC1E1EC3BFE0EFCA6ULL, 
            0x8DEF563F047F0F06ULL, 0x79AF264FE8FA0AC1ULL, 0xF2F766113725DEA2ULL, 0xBE1FD42D861FD814ULL
        },
        {
            0x034DEBCABFF4AC6BULL, 0x0C6B4A5768D45AA3ULL, 0xA169C10689B94C27ULL, 0x4641ABD85D4F0619ULL, 
            0xE62AD0D94E8E4524ULL, 0x0AED6EF54FCC4E82ULL, 0xCB900FD5E82D2B57ULL, 0x2FBAABF8ED670ADAULL, 
            0xF5522A35D394EA0DULL, 0xB4B7A6B5DCE26BFBULL, 0x2EF85E135D1632C1ULL, 0xB75A5052915E5948ULL, 
            0xBCBE6FE217BB42A9ULL, 0x8322AFAA7719711DULL, 0x08CB91EFBD8937B1ULL, 0xB55AFE0D89F8CD22ULL, 
            0x27FAF7DB4499E5AAULL, 0x42D65B2679266E1CULL, 0x64A8910052401B30ULL, 0xD49507C4AA66A6DAULL, 
            0xA8890F82B8219505ULL, 0xCB2479E12A7D57E3ULL, 0x1D21741852999744ULL, 0x50442E4BAA77F228ULL, 
            0x922A57C5C0477B05ULL, 0x88C28B4F53128760ULL, 0xCD15B4CDC1B74895ULL, 0xF949F8C075F326F1ULL, 
            0x33214BB1331C65B4ULL, 0x4344ACAB3FB25235ULL, 0xA3D4C45F0BA99682ULL, 0x5332588843C447FAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseGConstants = {
    0x1F9D67DF4CBACD0CULL,
    0x9DF85CD5355487C7ULL,
    0x528253835530284FULL,
    0x1F9D67DF4CBACD0CULL,
    0x9DF85CD5355487C7ULL,
    0x528253835530284FULL,
    0x6F081998B57AA9AEULL,
    0x6F0FB58A09B63B46ULL,
    0xB3,
    0x77,
    0x7B,
    0x99,
    0x71,
    0x25,
    0x06,
    0xB4
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseHSalts = {
    {
        {
            0x314BF058B4AAB64FULL, 0x51B2CABB2B112978ULL, 0xC9368C7070A88BE4ULL, 0xCB9AB014067C4AA2ULL, 
            0x9BED43884A1147A0ULL, 0x11FC371C6656282CULL, 0x5A9DE724F1C93D21ULL, 0x3D7E06D17CBB769CULL, 
            0x7E65EC52D6E9AF6FULL, 0x2800569C4F4CBF47ULL, 0xA6B0AFAC7B1E4ECDULL, 0xE553EA00F72B337EULL, 
            0xB3622B9BFD426DEDULL, 0x53692A5B7C50FEADULL, 0x8E669A6AD9A54E0AULL, 0x0E6CFD46D3335DDEULL, 
            0xE97744AA0B7EA727ULL, 0xE8C0EAE8BA871804ULL, 0x63D95D42F1BB1806ULL, 0x4200F47AD8E1BB6AULL, 
            0x5D2B94564498DEDCULL, 0x9BAB438B8AF5CF6CULL, 0x3E0989CAA9C7FDB0ULL, 0xA95BBE54C23A0F44ULL, 
            0x604C7E659026F534ULL, 0x5E6CA7A8291B9811ULL, 0xDD6BE05E579AC0CBULL, 0x1FE2BE4AE72877FEULL, 
            0x716291D294A259A3ULL, 0xBC2969987AC4421EULL, 0xF1FAE9518E0E5F2AULL, 0xFBF27D9FEDC1449BULL
        },
        {
            0xCF189F0ADDED6498ULL, 0x475614D64ADCAE4DULL, 0xE390598F2C790B46ULL, 0x55EC5BBFB84B2E0DULL, 
            0xBBE2E008E686183AULL, 0xB1C48F1BE72910ECULL, 0xF9F875EA8B088E77ULL, 0xB4302A54404C6381ULL, 
            0x90C9014E1A46120FULL, 0x044771DDFE8EE350ULL, 0xD0879C0F3B87E6E9ULL, 0x5452C0ED5D29C3C4ULL, 
            0xB13B6BFB79B27AE5ULL, 0x7C46F94ADED7A5A5ULL, 0x6003D8E1950C63DDULL, 0x09FB1783776C6899ULL, 
            0x76B7A8067F5C5E4EULL, 0x625A4AAC7241F20DULL, 0x3070AA91CD4124C7ULL, 0x873CF2B849AD3C2FULL, 
            0xD0829397ABE5C6F9ULL, 0x9C8F8DCC088F51A5ULL, 0x2006A65A17A41A52ULL, 0xA6E158C60FF8ADAEULL, 
            0xE7FCD2649A0B14E4ULL, 0x3AB60558443D3883ULL, 0x266F3FCAE7B9DFE2ULL, 0x210B573FFD90EE88ULL, 
            0xC5310CA9C6A32DB7ULL, 0x8F8F622BCF04999EULL, 0x9BC4F95560266403ULL, 0xE0EF77B3E4808418ULL
        },
        {
            0x0FEC0E88F5032B77ULL, 0xBF1E069604E14912ULL, 0xE45788878677DA7FULL, 0xFB3FF527DA38BA50ULL, 
            0xDB7524DB472D180BULL, 0x586AD6E038C47A8CULL, 0x548429D4DA119E06ULL, 0x01BDE0C1A1453CF1ULL, 
            0x7E0B2BC9FEABA986ULL, 0x035A11F67F63390DULL, 0x3B391F471BEBE2AFULL, 0x5805D0FCD5030E45ULL, 
            0xB00EE61D25C3A8D9ULL, 0xB5B5A48975C8A59BULL, 0x95CD5BF496519869ULL, 0xB0F8F2752603DD2CULL, 
            0x133CDA958F7859EEULL, 0x52DD09B0FC1A9EDEULL, 0x87243223D0338CFAULL, 0xB693A0DB5399325FULL, 
            0x8D9C1736362EBE18ULL, 0x98648DF71969A766ULL, 0xADB782209157BC45ULL, 0x4AFDD970C12AA291ULL, 
            0xC7708E54087C9E5CULL, 0x0EC834CA209B753AULL, 0xAC8508FD1E642D50ULL, 0x6AE2A54660FAECD0ULL, 
            0x52BE5975E2296748ULL, 0xAFD2487B18F858B0ULL, 0x3D595A30C6C4CB4BULL, 0x3F64AF5F93D0A792ULL
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
            0xD39CD0198352B257ULL, 0x9FF153453B8BCFA4ULL, 0xE17D398C53416F5EULL, 0xF5B39E31E618EA4FULL, 
            0xBDEFB86B08D163CDULL, 0x9F62B0E6342AAF15ULL, 0x5466393658B827D4ULL, 0xE90D53A1C752FD09ULL, 
            0x4DAF81569EF9E1A4ULL, 0x55082891E9EB3950ULL, 0x9052E0A9AF4C00BDULL, 0x086D12B1ACBAD9BFULL, 
            0x57C6BECD5B257549ULL, 0x78B1190DA48C436AULL, 0x72195C31AFFF18B0ULL, 0xF3962A0806235263ULL, 
            0x92F912195F018B97ULL, 0x4676101DC9C67A27ULL, 0xDB5BB6F5E33BDCACULL, 0xBCE67186D7A25FC8ULL, 
            0x485A99B6C0F13698ULL, 0x256F6FD1E13A060CULL, 0x39D859CA94AFA70BULL, 0x9942C5E49AE7B711ULL, 
            0xADBC485EF0680315ULL, 0x12E3AE72FE2E98EEULL, 0x199C8D2448996D74ULL, 0x4E5A66225AB8E0B4ULL, 
            0x0631196B9F12ABC1ULL, 0x6E357FF254B3ADC9ULL, 0x43A244DF217003E2ULL, 0x9269299C4BD969A4ULL
        },
        {
            0x4B7FEDEBA0E0C6C7ULL, 0x8F166B70DC8414ADULL, 0xDD490DC4DA45C39FULL, 0xF156013695002A53ULL, 
            0x1A008003EEF88075ULL, 0x7123FD308E39EFC0ULL, 0xF5F7C8436AC6BF8EULL, 0x6E9A585564F74AEBULL, 
            0x0FD607DE77876136ULL, 0x71E332F87A1C12B8ULL, 0x68E98A5FBF3D2603ULL, 0xF3753D2F3AFFD759ULL, 
            0x50B83C76CEA44E99ULL, 0x0E74E1C446DFC12AULL, 0xA37FFBFF319057EEULL, 0x6FB0A4BD22C710EFULL, 
            0x67AD2967BE91B002ULL, 0x271B3754558D15F1ULL, 0xE0190AC99494A5EAULL, 0x16A573D6A974FBC4ULL, 
            0x8401E9A40DD6697CULL, 0xA37A6B125BA7C4C4ULL, 0x28C3DDE2B26CF46FULL, 0x417FC345C7D885A3ULL, 
            0x4BAF9BA42BE95A6AULL, 0xA52EFF6A66678919ULL, 0xCE2D787AF113ED51ULL, 0x7C178778206463FBULL, 
            0x3615B9CB1721173EULL, 0xFE94E734F74AA3C6ULL, 0x26522226094EE71DULL, 0xB31879D61227AA0EULL
        }
    },
    {
        {
            0xD9D9A41E01439212ULL, 0x0D867D191489CE1EULL, 0xA551FAF5DD8F68E5ULL, 0x9C8F8D4D7814D9CBULL, 
            0x0865B337D0D307B0ULL, 0xA5532198527E4044ULL, 0x3A12F014E81B982EULL, 0x1721A165C6A2B311ULL, 
            0x2F95E0B003890A4BULL, 0x0729F3507945CCF7ULL, 0x2526A98B8F36EDC9ULL, 0xFBEDC616B9773EEBULL, 
            0xF66444F5A2D4C6AEULL, 0x557A7B58727F3B89ULL, 0xCDBD02FB3FBEB895ULL, 0xE7A7C4214689830BULL, 
            0x19AB5879990560BDULL, 0xA4037DC632831CC7ULL, 0xF8503936C67BED06ULL, 0x0A476EE1D3B06242ULL, 
            0xCF0C1A597B774DFBULL, 0xB78522C30238958DULL, 0xEA52F172C435EB98ULL, 0x7146B54F52778A6DULL, 
            0x2BD280BAF430FA98ULL, 0x7030D05D530AA09CULL, 0xCDE37F30B56040F4ULL, 0xDE3863D1071F3A64ULL, 
            0x27456678E06E17DFULL, 0x9E0D016B2A73BD8BULL, 0x64461BCBB9BC93A3ULL, 0x38C8F021F0045CB4ULL
        },
        {
            0x8FEE8B540D76EA0CULL, 0xEF5A20C09D918AE9ULL, 0xEF64E87412B0FE31ULL, 0xB1540D32FDBF63DFULL, 
            0x2C84752741EA9873ULL, 0x934FD8043984CFAEULL, 0xECFC7F13B87FC4B0ULL, 0x7EFEDC525C72D907ULL, 
            0x09C4416E4CA1B362ULL, 0xBAA1ED173D558F2AULL, 0x479D23C92CE9E4C0ULL, 0x2849785B9451C343ULL, 
            0xFE5A3A933E6D4920ULL, 0x021E7C6CB29FE442ULL, 0xA42BEE2F183B20A1ULL, 0xDC785C020FC5853DULL, 
            0x95092FDDDB2D8BA6ULL, 0x3AC3497CCE0EA36BULL, 0xE3CC78F402306F31ULL, 0x265263550EA72A65ULL, 
            0x0D0DFD3F37773D66ULL, 0xA4B0FFC5F99DD108ULL, 0xFF0934A9919F0771ULL, 0x3ADC4E1DAC5EDA0FULL, 
            0x51EF1F3FE4FAE507ULL, 0x5FB1CAE77F89E849ULL, 0x015A6C8A9F9A9D7BULL, 0x8D2491B1477DA6A3ULL, 
            0xD1E34B3F1D626CABULL, 0x1A3C8F6D2D82B906ULL, 0xB0A8F107F4323154ULL, 0xBA14B7B45EA3D979ULL
        },
        {
            0xEA1A7D1CC43375DBULL, 0x07355392CB83A987ULL, 0xB82B991FF0689702ULL, 0xD2566F973A7E76E7ULL, 
            0x5E8F268FD89C8A37ULL, 0xD765CCE94C2FECE1ULL, 0x453A2FE90D52FA62ULL, 0x002D3DA87EE43C46ULL, 
            0x18D60E1C73C7F65AULL, 0x233C2A7352CA8C11ULL, 0x515AA2A9474CC0EAULL, 0xB709AF8A8FF88C28ULL, 
            0x74BD246BBCB3F694ULL, 0x2E1C86A9441B9433ULL, 0x44BDE69A110552B4ULL, 0x17556F9AE4435D99ULL, 
            0x7AFC74D5497768DCULL, 0xC3487AC5A2489ED4ULL, 0xC5FB65196D72F6ADULL, 0x5AAC7E382108125AULL, 
            0x165CAA197EEF8646ULL, 0x51AEEDD1CC09A948ULL, 0x97ADFBFBF7E27964ULL, 0xE951BAA92DDE1E12ULL, 
            0x8F12AEE69D89FF8EULL, 0xF46B699C8C1858F9ULL, 0x119763CD894E1F42ULL, 0xC7FB0520E4820FC6ULL, 
            0xA513E5E5B80D1A8FULL, 0xBA73328AD5955F8BULL, 0x174F05BB6E450BA9ULL, 0x4D283468D65898E1ULL
        },
        {
            0x7F95403C903B86B0ULL, 0xA74BBE2CCA164E00ULL, 0xC313A65C5A15BE79ULL, 0x73C3FA774A9F44E1ULL, 
            0xDB8C3418E59A467EULL, 0xD9566E1725820B8EULL, 0xDFAA7018F9912B21ULL, 0x2870E09E775F7612ULL, 
            0x82BC1E4315FD7E5EULL, 0xCF94910614EC7FF5ULL, 0xC09A6C16EF69C554ULL, 0x3C034F25ACC43508ULL, 
            0x1E263BF363EEFC45ULL, 0x793316C348BC8883ULL, 0x9790F8EB22FDF77FULL, 0xCA0CF1451ABF3E13ULL, 
            0xF01C3EF28366738FULL, 0xCEA9352527064F7DULL, 0xC6540712BC9DB732ULL, 0x9E30D422F4ADB4D9ULL, 
            0x164222C3E1835294ULL, 0x21DB706F04231D1DULL, 0x9B72C11E9D03C152ULL, 0xA761FFDC96E8C292ULL, 
            0xD170A24F66A1D398ULL, 0xDC780A193D02E48BULL, 0x6593EFDC74423A75ULL, 0x4FAFDA0A291CF0B5ULL, 
            0x041AEAC0264AF497ULL, 0xCBFCD0987D7645EEULL, 0x33FF1C288F9009EEULL, 0xE9957C718156D61FULL
        },
        {
            0x94A4CF43A7A1CED2ULL, 0x06DA58C43AA2D890ULL, 0x34EE9BD5F43FFBF1ULL, 0xBB4EA46B4A1FECC4ULL, 
            0x79211C923660BDFBULL, 0x2316DD8751F68F1DULL, 0x8D23E58E171F8231ULL, 0x1D2F52C88B5334A0ULL, 
            0x7FCF7237C37CA061ULL, 0x68C3DCDDF827CDC6ULL, 0xDF90BCF195EEA412ULL, 0x7BE1154C0EF7FD38ULL, 
            0xDB0098320B7994DAULL, 0x11E2B83E97ADD263ULL, 0x70C8DBDA4EA0448DULL, 0x545F19D1AC06477BULL, 
            0xFE6780D6006173FEULL, 0xCDF25814D4041B9FULL, 0x14086C121889E8BBULL, 0x3EE9123586E5F70EULL, 
            0x960C4A25FC801415ULL, 0x6D3E25576F807996ULL, 0xA2F5B639B73ED641ULL, 0x492897611DFF7F90ULL, 
            0x886604D10DE9D69EULL, 0xCF5910678D0657ADULL, 0xA8BBDA435D9E6A85ULL, 0x4E6020AB2ADA1BA9ULL, 
            0x0E902F4419B189F1ULL, 0x500855540808F36CULL, 0x9AAD2D00E8BA0639ULL, 0xA287C470C4797C95ULL
        },
        {
            0x4F6EDF278414E109ULL, 0x2EB9F9359DCFFF94ULL, 0xC20E57DA8DE77223ULL, 0xA62916CDDF368C69ULL, 
            0xF1A03FDA9A6CD7ABULL, 0xC606D21C9553C923ULL, 0xA43AFA0EC02F9A07ULL, 0x07FA79E4AB56A1BFULL, 
            0xF738CD5828AB359BULL, 0xF5EC4F92294BFE74ULL, 0x375F4A52D721DCAEULL, 0xE7FD0D0FC03AD05FULL, 
            0xDAFD214E88405D43ULL, 0x55611F2A3021B7D7ULL, 0x9145346179A64B3FULL, 0x0C0B51EB733E35AAULL, 
            0x6EEDF1F700E726F2ULL, 0x929C602A7EF8E20AULL, 0xBE697A5751422424ULL, 0x08E4593DB445ECA5ULL, 
            0xA65987CBDC24D37AULL, 0x1A0A60154166E1C2ULL, 0xCF83E31885E76DCBULL, 0x2849DF0961A55E16ULL, 
            0xEE1415E08486AF8DULL, 0x24546E2028878316ULL, 0xDCBE2F126E4BDC47ULL, 0x271B62186897981EULL, 
            0x87C222226386DF2AULL, 0xD3C14CDC0C6D9E3AULL, 0xB3266698CA4ACC76ULL, 0x8CAEE443DAAAE524ULL
        }
    },
    {
        {
            0x06D424985B14499EULL, 0x18AE6204D61D7ABFULL, 0x0E677F5EB8A0F923ULL, 0x854E332FAAA0EF7BULL, 
            0xE724380B019A9AE4ULL, 0x47F7A1C0578E69B7ULL, 0xF58BD467E3163247ULL, 0xC4D11C8FD236AE1AULL, 
            0xF1BB4077FB21EDA6ULL, 0x8D5DA98C1F077278ULL, 0xE800A64516E55D1EULL, 0x3867191D89DE516EULL, 
            0x199CCD1EE088AAE2ULL, 0x272711F355EEBD8DULL, 0x98ED2F84C1989E3BULL, 0xEC493629F0AFFEAAULL, 
            0x67161553B97A765CULL, 0x093465771B72CD24ULL, 0xF16F606C07413C74ULL, 0xD64FE6C6D6B99DCEULL, 
            0x557221774868AE9AULL, 0xB13941BA110B058FULL, 0xB9815BDF5D9FDCFDULL, 0x9986D37FF2082FF9ULL, 
            0x6780DFBD76DC2EA7ULL, 0x59E30F8FDB7D659DULL, 0xAB69520CA83EB4BCULL, 0xB443988BF00BE249ULL, 
            0x1EC327A4A33B32C6ULL, 0x5EE7465AD7B8E0F6ULL, 0x2B14D0626938C470ULL, 0x268065113CC95E11ULL
        },
        {
            0x02472B674B280651ULL, 0x78A7B20AD6FF9EB8ULL, 0x12CA1B3BD7E1FD8FULL, 0xFE9959D87220273CULL, 
            0xE032F1BFB0866552ULL, 0x449DE764B3B313EAULL, 0xBCBA77163F8F930DULL, 0x0FB32C1DF5FD8C5AULL, 
            0x576ADF668B7053D8ULL, 0xA55ADEE54FDBCFB0ULL, 0x33CF05C301B0E197ULL, 0xDC3F579185D7A976ULL, 
            0x67F9736C29704FD0ULL, 0x62AD28674839CAFFULL, 0x13EC5539EDD40B5DULL, 0x1E98C9C970C928DFULL, 
            0x68AD5BEE00FA30CFULL, 0x828ECA73C2CAEFB5ULL, 0xC249502754324675ULL, 0xF8E1E5EDFA7F8273ULL, 
            0xB9C370803D345A64ULL, 0x79D79B525C68C5ACULL, 0xFA548398BDED3869ULL, 0x19121E769E6CDD9FULL, 
            0x5AB7B7ABDCA30F68ULL, 0x5E9E4DA588C78700ULL, 0x180ECD3F4812BC86ULL, 0x128F8FFA0EFC9C6EULL, 
            0xDFD60DD54126C013ULL, 0xA7A1F53E5A347F80ULL, 0xA7877C34A3B7D3F5ULL, 0x98C3CB35B9989649ULL
        },
        {
            0xC8828F8FE5CF6535ULL, 0x48687325AC469749ULL, 0x73A643E2285CFD85ULL, 0x1BA25031F9679955ULL, 
            0xEC832C96C48D3AE1ULL, 0xAA58E2DBB099103FULL, 0xE9D2EABC1B790B58ULL, 0x219C9C75D4DFD829ULL, 
            0x65DE4ABB6BE9FA1CULL, 0x7C88C9F46197513BULL, 0x4A30196BA8CA32F0ULL, 0xFF0D88B64789B5F6ULL, 
            0xA9A63B008B97DF70ULL, 0x5BA6623035617627ULL, 0xFBED2CDBA8DAB448ULL, 0xF56600714E8F2E67ULL, 
            0x1FA0D005D9AAA419ULL, 0x57B7DAB4C798471BULL, 0x561FC30AE745B06FULL, 0x2F7D632EB7E1C758ULL, 
            0xDDA79C3350C498B8ULL, 0xB7B3602C0BE041D1ULL, 0x9F967331E20FCEACULL, 0xEC2D33EC5416FC81ULL, 
            0x7FB31115A9ADBDF0ULL, 0x1154388CF87FF76FULL, 0xD24DCCC18B8737B3ULL, 0x8B0E19EF0DA33A9DULL, 
            0x6ECC5D1267861743ULL, 0xA32EC4B7D797C802ULL, 0x34CE16B057371BFEULL, 0x74717E6D1C730F07ULL
        },
        {
            0x0D4C6CA427D77AF9ULL, 0x6DA7CEF3B7C0D2BAULL, 0x6D276BE204814F7BULL, 0x9BFE9D38ACA5BE0AULL, 
            0x519C85D87DE5480CULL, 0x6E3B0A13E7AEF827ULL, 0x547FCFC0B1679CAAULL, 0x5E7B1A67E207287DULL, 
            0x89B89404630DF38DULL, 0x5F06726E83D5A98EULL, 0xE6483968C665D96CULL, 0xC4DB1409632B3D83ULL, 
            0xA8BEB8DA0DCE78E4ULL, 0xF22E9E0DA0E18614ULL, 0x084078F2A745D6DAULL, 0x5FC6276929052036ULL, 
            0x78BE13330F66B17BULL, 0x5A3A7EBED1FAF7F0ULL, 0x00DF2D2875A060F1ULL, 0xA8B869E7B059D352ULL, 
            0x103A49B038C195F9ULL, 0x9CD77CF55FC7907EULL, 0x577855ABCDA16A0AULL, 0xCA30F27B66CAA806ULL, 
            0x059B529FD4980C9AULL, 0x67BD2FFA6DE251D3ULL, 0xD64DA6D11FD79212ULL, 0x42C5C697911B8FB2ULL, 
            0x06D71B35180F5480ULL, 0x7CE85727ED804581ULL, 0x98F143C06EDE51CDULL, 0x4C9F92B08F2550B3ULL
        },
        {
            0x7E65BCF4959064AAULL, 0xD80A62EE0016B3A0ULL, 0x0FCF52271FD4420DULL, 0x1145AA84FF45119BULL, 
            0xED4F84ACBAA16E82ULL, 0x78DDE48E44607288ULL, 0xC07CF7ED7C9F62ABULL, 0x68D187DA4D5874ACULL, 
            0xF028F2E8620F7A4BULL, 0x2058AFDB6B9178FFULL, 0x381CC71624FFDEBCULL, 0x6F3EC95ED9987F0CULL, 
            0xDD7F0A0C3D3B817BULL, 0x63521F30C5CABB17ULL, 0xBD43F5CEFD1FC907ULL, 0xE97B42C9E3F95C2FULL, 
            0x1136233B32CDF881ULL, 0xC73B780EAC3BFD68ULL, 0x4BDC331B261A8305ULL, 0xCC946E140924C84AULL, 
            0x601D50252B80D6DAULL, 0x2EFD88602B089C7AULL, 0x4AE8994084EA76A8ULL, 0xF9D5787322F19138ULL, 
            0x41F8080993E75D3AULL, 0xA3BB7EC6BBB032D2ULL, 0x118FC7C575BE134CULL, 0xC2497C8E98426D76ULL, 
            0x00DE0F21F0069105ULL, 0x2F90A7BA7CD95A36ULL, 0xB752AD462F576DB8ULL, 0xC05D36D6F76E1834ULL
        },
        {
            0x3316AA20AB779D95ULL, 0x8712A28070871EB9ULL, 0x6EA1A5B4815F51BBULL, 0xCAA644F63363768CULL, 
            0x77DFF9D7B1C055DCULL, 0x700CFEE07F9DB843ULL, 0x052780DC74418B6BULL, 0xB849C020E4DD0213ULL, 
            0xAD2485B456B3E2C9ULL, 0xEB8DFDBF06B67733ULL, 0xCC6C88193797B995ULL, 0xDA3FDE25ECECD571ULL, 
            0x87A9F41F6246A95BULL, 0x15CE4FAE815D7C9BULL, 0x78F7E9D34974C597ULL, 0xD77C626DE30D6347ULL, 
            0x547DE085CD0C3722ULL, 0xBF304626177A3D1EULL, 0x0A29B46F99BE7E33ULL, 0xE9F47732712E692DULL, 
            0x5523BDC3940551D7ULL, 0x7C00C08BB325351EULL, 0x14BA5A531636835CULL, 0x53384AECF33B6D8AULL, 
            0xC048325344924A51ULL, 0x5F4B8F4C98874D37ULL, 0x641F61D3F6E570FEULL, 0x747A1E7D658416ACULL, 
            0xEBD2564F076C2221ULL, 0xC671EAC2005992EEULL, 0x161BD217FA22E69EULL, 0xEDBDBA8DEBBA7F8BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseHConstants = {
    0xF9E65E1D243FA8AFULL,
    0x33D04B71ADC94A1BULL,
    0x95D84529DF31CAC3ULL,
    0xF9E65E1D243FA8AFULL,
    0x33D04B71ADC94A1BULL,
    0x95D84529DF31CAC3ULL,
    0xF33FA1A27291FE38ULL,
    0x78D0380B49B97B75ULL,
    0xBC,
    0x23,
    0x70,
    0x6F,
    0x61,
    0x48,
    0xC1,
    0xE7
};

