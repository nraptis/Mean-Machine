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
    std::uint64_t aPrevious = 0x89E3A710F2645426ULL; std::uint64_t aIngress = 0x82743C3A8CAB2C3EULL; std::uint64_t aCarry = 0xAE52245D9A72D7C1ULL;

    std::uint64_t aWandererA = 0x8CA4566492694C11ULL; std::uint64_t aWandererB = 0xACC53B845FDF80D2ULL; std::uint64_t aWandererC = 0xE5BB83B4FCCE2F12ULL; std::uint64_t aWandererD = 0xFDEC8CE7ED62D0CEULL;
    std::uint64_t aWandererE = 0xCA07692B31B4B9AFULL; std::uint64_t aWandererF = 0xD7102A6F8FE18F37ULL; std::uint64_t aWandererG = 0xC6950A5C31453042ULL; std::uint64_t aWandererH = 0xA5C73335AFC020C6ULL;
    std::uint64_t aWandererI = 0x95A386460CBB0539ULL; std::uint64_t aWandererJ = 0xA67EABD7C3C5753CULL; std::uint64_t aWandererK = 0x8DC71C648AE54D43ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17102519085896000335U;
        aCarry = 17323928881106996944U;
        aWandererA = 10570302756458188307U;
        aWandererB = 12113514181841686815U;
        aWandererC = 14500270124011605810U;
        aWandererD = 11862741830905573639U;
        aWandererE = 9374186333021159820U;
        aWandererF = 18378068070369206951U;
        aWandererG = 9424778579825345138U;
        aWandererH = 11842896425424856462U;
        aWandererI = 17948976361485005660U;
        aWandererJ = 12082720847832307082U;
        aWandererK = 16011078533312267859U;
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
    std::uint64_t aPrevious = 0xD80149A5C316F952ULL; std::uint64_t aIngress = 0x96BC438E1D7778B7ULL; std::uint64_t aCarry = 0xAD2DDB64C0CBF364ULL;

    std::uint64_t aWandererA = 0xAADFD57334791AFCULL; std::uint64_t aWandererB = 0xAA59BB975855D9F4ULL; std::uint64_t aWandererC = 0x8DB1F76DC94759C8ULL; std::uint64_t aWandererD = 0xB5DB0EA36B836CCAULL;
    std::uint64_t aWandererE = 0x81E29C0243005E6CULL; std::uint64_t aWandererF = 0x9DBDC463486371EEULL; std::uint64_t aWandererG = 0xD2B4E95447B34DCFULL; std::uint64_t aWandererH = 0xE2F56D27B22C1C6AULL;
    std::uint64_t aWandererI = 0xAC4C494B5334DD39ULL; std::uint64_t aWandererJ = 0xDC3256C846F5F9F9ULL; std::uint64_t aWandererK = 0xD5D3A3696B1A45A4ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16986070331902034148U;
        aCarry = 11976452916796029728U;
        aWandererA = 13304505918688065883U;
        aWandererB = 10644028745298068816U;
        aWandererC = 16230450686087934926U;
        aWandererD = 11011747783929025551U;
        aWandererE = 10621858458251917633U;
        aWandererF = 11560994800418961593U;
        aWandererG = 9872379006811977220U;
        aWandererH = 17075254003903397969U;
        aWandererI = 11137120521824887754U;
        aWandererJ = 14209002383226385491U;
        aWandererK = 16127005343851910216U;
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
    std::uint64_t aPrevious = 0xD01DEBAE2C8C9869ULL;
    std::uint64_t aIngress = 0xA4075D4B7CBC35EEULL;
    std::uint64_t aCarry = 0x97040106DD7CCE98ULL;

    std::uint64_t aWandererA = 0xC8E71514E9E17597ULL;
    std::uint64_t aWandererB = 0xD2702C0F507CB3F6ULL;
    std::uint64_t aWandererC = 0x9E32493E376DCFE1ULL;
    std::uint64_t aWandererD = 0xC34D6C8142F8869CULL;
    std::uint64_t aWandererE = 0xE740257817035B23ULL;
    std::uint64_t aWandererF = 0xF7EAEBE6FCA28305ULL;
    std::uint64_t aWandererG = 0xC2E6ADAB1C57418BULL;
    std::uint64_t aWandererH = 0xF05D3CFD193B6D52ULL;
    std::uint64_t aWandererI = 0x99CE62642EB83F02ULL;
    std::uint64_t aWandererJ = 0x9A36C430D8020D1CULL;
    std::uint64_t aWandererK = 0xB3FECA1CF37B562FULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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

        TwistSquash::SquashC(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
    std::uint64_t aPrevious = 0x966806A6532262B1ULL; std::uint64_t aIngress = 0xF6BEE72697C5F97CULL; std::uint64_t aCarry = 0x93FD248A1CE6691FULL;

    std::uint64_t aWandererA = 0xF53DB3672D34AC8FULL; std::uint64_t aWandererB = 0xC5F855C02315AC60ULL; std::uint64_t aWandererC = 0xE314D73C136D2023ULL; std::uint64_t aWandererD = 0xDDCB19717073AD32ULL;
    std::uint64_t aWandererE = 0xE4DFA35E533D18BEULL; std::uint64_t aWandererF = 0xE821CD575E48728DULL; std::uint64_t aWandererG = 0xB7AC487DDD03976BULL; std::uint64_t aWandererH = 0xEA139042988B4354ULL;
    std::uint64_t aWandererI = 0xC2F8E95002DDAE4CULL; std::uint64_t aWandererJ = 0xD8B0B865A8C8EDF8ULL; std::uint64_t aWandererK = 0x9BBE7A3C6D416D3FULL;

    // [seed]
        aPrevious = 13869434195645057535U;
        aCarry = 14124905191382656389U;
        aWandererA = 16831021403653906796U;
        aWandererB = 18280845920465082245U;
        aWandererC = 14300408367288024784U;
        aWandererD = 17043822352236227372U;
        aWandererE = 13551824476025876079U;
        aWandererF = 9581245132483146165U;
        aWandererG = 15177719349593598442U;
        aWandererH = 9362536995092668293U;
        aWandererI = 9388622231215856403U;
        aWandererJ = 11728814873016997472U;
        aWandererK = 11014668246510948188U;
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
        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
            0x301A966BFEFDBF5EULL, 0x52D2DE8A08971102ULL, 0x2A9B518E4C53E691ULL, 0x224D2EC32256AAE5ULL, 
            0xD07DD9A43A948F1BULL, 0xE612757BD8BC054FULL, 0x5323ADC4A23F38CDULL, 0xBCF6786440F3E01FULL, 
            0x5752E8B1E77488CAULL, 0xC3484BDE3127D67BULL, 0x64C245F8E8642BC3ULL, 0x68688AE4074BB1D1ULL, 
            0x74E23EC1650992D7ULL, 0x8C5C2302191DEB6DULL, 0xAE844B8467F608B0ULL, 0x06CD0E5C12281CD6ULL, 
            0xD15DCCB83638933CULL, 0xA083494162DDD18AULL, 0x9263D76F6CDF3A6EULL, 0xEC472C8D14143C78ULL, 
            0xBDD5B53C0485E6A4ULL, 0xE4C5D41E60E264ABULL, 0x756BBEFA7761AAC5ULL, 0xEF4FFCB7A8B22DD9ULL, 
            0x51E4DCF1564E1E7AULL, 0x490067E34096BC03ULL, 0x96A37D487724C218ULL, 0xC01496FEA971811CULL, 
            0x1EA6D9CB6160E28DULL, 0x7C3C7F05DE88BEC3ULL, 0xB94A6E3364186C21ULL, 0x08EEDCF47714EFAFULL
        },
        {
            0x8AC8CE6FC1769F32ULL, 0x21B374BAD974DB59ULL, 0xA9573C42A53DBCF6ULL, 0x2F0E94C3A8BE0B58ULL, 
            0x5036E6C7BAD4E408ULL, 0x2AA3104119B23A16ULL, 0x0C50E567EB895C2DULL, 0x3AAD1D0A66720CD9ULL, 
            0xBF02AEB11FE243D5ULL, 0xB5CD8E3C0E09659DULL, 0xB2764F8A9B9D0F0DULL, 0x47E113EB25831353ULL, 
            0xF807DD34E7347795ULL, 0x90FE4DB9A0CCD088ULL, 0x7F9C73D29F2EDD00ULL, 0xC1AFA2340E3D9667ULL, 
            0xEF2932563CDF1D7BULL, 0xEA2959C2E02447E5ULL, 0x3D180F563FE860AEULL, 0xA8C86E982D953924ULL, 
            0x0C18707A7FCCDDFFULL, 0x66944771A8A6E542ULL, 0x5FE43CB28E11B308ULL, 0x53153FBB0D011C58ULL, 
            0xE70E09F8B9F7782EULL, 0x148574DED2FA0BF1ULL, 0xB30C6604FEE035E4ULL, 0xF2129C28CADC9100ULL, 
            0xFFE4CC8F1170D94FULL, 0xC905C34D7E6DADE4ULL, 0x0B3EE65FE713C123ULL, 0x91C79D87D630D55FULL
        },
        {
            0x00A453F635185D73ULL, 0x0BB5679C57CCCE3FULL, 0xF7DAF494E5880A78ULL, 0x42E7DEE88C0BF722ULL, 
            0xE32C8E4F6C6D4B70ULL, 0x9636F353414B6D03ULL, 0xE295023ADD936360ULL, 0x0F1EF35294516F8CULL, 
            0x15E26045CBC21ECAULL, 0xC7DC1916BA18B50FULL, 0x8EBBFC68C88BC3C2ULL, 0x92B6E6D99E981228ULL, 
            0xE08521862B843F74ULL, 0x5FC99F90CB2AE2D7ULL, 0x0643580D4F02FEA3ULL, 0xC4F98B6BBE0CC522ULL, 
            0x529B6E04AA40CC97ULL, 0xD10152DD3609D34AULL, 0x781A81DC780A2EC5ULL, 0xAD0D0A8671A213F6ULL, 
            0x82E7BA59BB8FBBC9ULL, 0x4575DC75EE860DF0ULL, 0x646FD116224AFD44ULL, 0x7A135EC10BC482F7ULL, 
            0x20DCFD0FEAFDB741ULL, 0x11C926183669035AULL, 0x0E8FA7C23786ADE6ULL, 0x02DE54011F02F3EDULL, 
            0xA3E549B80C1416D4ULL, 0x361C6B23B929C1ADULL, 0xE27DA072C97623E7ULL, 0xCFB36C37169D6503ULL
        },
        {
            0xF6F57CD757403050ULL, 0x2E8F811C2A1A6328ULL, 0x35869DF6C9650A7AULL, 0xBCBB898BD64FE779ULL, 
            0x4DDD09C9F31375CBULL, 0xEE62434917BEFD7CULL, 0x27268457499521C5ULL, 0x5D0549BD1D2C64F2ULL, 
            0x44763F7327749A1CULL, 0x88EAE57C72BAE029ULL, 0x7602F0D8FCA4D5A9ULL, 0x7432D7D7E8D31C55ULL, 
            0x6C7459AD249BC418ULL, 0xE98843813FFE542FULL, 0xB59F8ACCF2102169ULL, 0x01DF4E40FB120958ULL, 
            0xA129A62DDB64E6B0ULL, 0x78F0F13EC2274B7CULL, 0xC3437C28D46A1312ULL, 0x66725F1B2F2FF23AULL, 
            0x222480A46F0B8E55ULL, 0x441903CB802ABD11ULL, 0x0B901E7FE65DEF83ULL, 0xA9828878516E53AFULL, 
            0x9D36F8EBCEC66173ULL, 0x7FF7134477977C57ULL, 0x8D39A945C9BD46ABULL, 0x62953050F4055E64ULL, 
            0xE740F7828FAEF5D4ULL, 0x3B6A29CD14B9FB36ULL, 0x42A9E481078A7FCDULL, 0x9B6E752CC267A6A6ULL
        },
        {
            0x65099DC545896432ULL, 0x0FC0B34D82D7B327ULL, 0xE5F0BA086191A7D2ULL, 0xD10EBC8B04822A45ULL, 
            0x2B41E23F727E7EE5ULL, 0x359B2690B81850D5ULL, 0x7D56AA4C7B542D3BULL, 0xC706C0F3767F0DBDULL, 
            0x70A76C31848B3627ULL, 0x72AEBF39B919D528ULL, 0x101B74AF2BCDF3BBULL, 0x86B50EF3BC4AEBE6ULL, 
            0xB330007FC04727CDULL, 0x1CA4A4B086D8EDD4ULL, 0x4005C6AE7050D181ULL, 0x68FC4CB9EF7F7BC2ULL, 
            0x380538B0B596E8C6ULL, 0x1C8ED577483E59E3ULL, 0xA28EC759E71896F6ULL, 0xBED13F2A221173B9ULL, 
            0xDF1B2362E1698479ULL, 0x3A93903A91408C63ULL, 0xA630985E582C1FC4ULL, 0xAF98CCD7EFFB5D64ULL, 
            0x629BADDB29099D08ULL, 0x5A4193828E70A2AAULL, 0x3B98712690ADC20DULL, 0xA90882EFBADD8A88ULL, 
            0xDB64AB1C9C1933C0ULL, 0xDC0EBACD653929A9ULL, 0xE66F018C0F553830ULL, 0x0DAE64EFF33185A8ULL
        },
        {
            0x35D358D08193FAEDULL, 0xE7A0299900CA8081ULL, 0xC9AC83B715E5936BULL, 0x9AEAE715A6C765E5ULL, 
            0x772ABAFD057CB1D6ULL, 0x77090017208E0FCAULL, 0x2F58A141E6D3A4F7ULL, 0xA6F80EF51D2991B3ULL, 
            0x7C100C41CB586A94ULL, 0xC42CECD04F21DC13ULL, 0x9F9749828DA64C94ULL, 0xF8F14A2B95ADF74BULL, 
            0xEDE417C1A67E00EFULL, 0x1CB431FA6D956CBBULL, 0xEE1E12BCF5F4916BULL, 0x5260866B1B9CCDCEULL, 
            0xE6CFF6A6000E1849ULL, 0x195F28C209FECF64ULL, 0x5EA4A1B03097B3DBULL, 0x96FB14AF9EC31E92ULL, 
            0xE09A681CC8C20D3CULL, 0x3F996040C70B17D0ULL, 0xDB0B26FB17BB00A4ULL, 0x70ABD5F3852C5304ULL, 
            0xD7200B9B17535E73ULL, 0x93CD766207C6357AULL, 0xA53E93576CF46EF6ULL, 0xA3152D88ECA1F404ULL, 
            0xE70C20D7B67A3773ULL, 0x06064091FA357FEBULL, 0x37BE7D76A5ACAD8DULL, 0xFC3ABD887DA46B8CULL
        }
    },
    {
        {
            0x1730F74F667523B2ULL, 0x51D9C4FDA2D551D6ULL, 0xBF44FC70114AB587ULL, 0x4205B1E7BCBEF4D2ULL, 
            0xA68294ECADEE1A95ULL, 0x222B2E3E4B6FFE2FULL, 0x0838B207CA4C6AFBULL, 0x2852D2FB84867005ULL, 
            0x3D93B452C1D33D58ULL, 0x4A00D9C067E0ADC8ULL, 0xE077E47A2362E5F0ULL, 0x6CDBEE01DCF0FA03ULL, 
            0x441A53584A9607DCULL, 0xFFAD9FA27BB6AE6BULL, 0x0E9BE4C915AF6569ULL, 0xCB1F86275E057AD8ULL, 
            0x6112D793DAC0E4DBULL, 0x12F056180F46AA1DULL, 0x20BD4F4A79B744B1ULL, 0x65909260E5CB8D5CULL, 
            0x4AC1044B38B5FA0EULL, 0x838EA8829B1821CAULL, 0xAE3BAAA1684E1B27ULL, 0xCA9B4ADA282C177AULL, 
            0x5B6ADA71D094D251ULL, 0xA9E83D5750F6FC01ULL, 0x494864EEDFB57EACULL, 0x46A706BAC78C76DEULL, 
            0x3813FA9B33DFA935ULL, 0x4D54476260026846ULL, 0x2CA00F2FE107DA7FULL, 0xA211014B740F952CULL
        },
        {
            0x7B4247A14B160505ULL, 0x340D4A0A773FBEB9ULL, 0xD811EEDCC651EA09ULL, 0xEBB0EF33F6DD1601ULL, 
            0xC8DB36D2FE4452CAULL, 0x3EB935F8FC57CF08ULL, 0x65852A631142BCAAULL, 0x01DB28EAE3EE66DCULL, 
            0x616DA93D46732107ULL, 0xFAA4D04D201CE683ULL, 0x78A6153222C4307EULL, 0xE08AE92194851131ULL, 
            0x7714D9CA6E6AF30EULL, 0x04B35DE025A45D24ULL, 0x3CBFF979D9DF9AE5ULL, 0x9E13682E4CCAB665ULL, 
            0x0899A7E17E763FA7ULL, 0xC6595790A4827674ULL, 0x3430800FE62790D8ULL, 0xE91340296F205B20ULL, 
            0xDAACE0DC3330676DULL, 0x438459991636C38FULL, 0x6A92D992712B7BB7ULL, 0xCFAC28A2D22A7683ULL, 
            0x3E4A8682ED5700B7ULL, 0x0D63B4D8AD15A156ULL, 0xDE7BB2E589F43E48ULL, 0x81B646E729B3DF12ULL, 
            0xF8191FD5FE8B47D1ULL, 0xE5F92BF5186A1255ULL, 0x6619EB6F9D37DE51ULL, 0xFE9B0506D5DE2CF1ULL
        },
        {
            0xF9BBC22DBF8883D2ULL, 0x39067CEDAA8EAC3CULL, 0xC26133E4E4EC8217ULL, 0x84B5A2AA55ACBC24ULL, 
            0xF2518BE65EEE84B0ULL, 0xF1DAB2268163ED12ULL, 0x37676D3C02D49658ULL, 0xB63842E8F3900D3DULL, 
            0x91088AAB3645297FULL, 0x8F9426EC0C180EBBULL, 0x0CDD6BC6B7D44628ULL, 0x6ED1C46E0972532AULL, 
            0x610BB66E89117572ULL, 0xF47B9E48E10A2AC1ULL, 0xA5DA9C33771A7A53ULL, 0x23A8DFAE6F39915AULL, 
            0x196311F144278045ULL, 0xA2AF1F2DBDEECA4FULL, 0x731CF2E501C58B0AULL, 0xC42762224570B755ULL, 
            0xF831DAFBE9D80B7DULL, 0x767C448F53FD5FF8ULL, 0xA07E483D7C04C206ULL, 0x03C38193F1707D69ULL, 
            0xF0AF4234635193C8ULL, 0x79C4A0BF36312FC3ULL, 0xC60855373BDF0646ULL, 0x7BE307608C0DFF48ULL, 
            0x0B44CBB0D06517FAULL, 0x1B2EFDAC08FE3244ULL, 0xB76EBFD33891D3CBULL, 0x1D069D627ADB347EULL
        },
        {
            0x371904D42A11809DULL, 0xC73DDD16511B9B41ULL, 0x87A1FA74F84A33E9ULL, 0xBBB5F1CFD95070E2ULL, 
            0xA2431614FA04CD27ULL, 0x3E83424745686753ULL, 0xD1BAD448D084EB31ULL, 0xF9739E854A8E3356ULL, 
            0xD5B99E7B56B6F0EBULL, 0xF1DB9812DD2D970EULL, 0xA3D525C7DA1C94EBULL, 0x94102AC96423C793ULL, 
            0x5DE98E5FB877BDCDULL, 0x1F4818A3ECDCEC01ULL, 0xD6D59D5184DADFABULL, 0x4A192B8C10D707ABULL, 
            0xF2FFD107D4682436ULL, 0x4D4509D0CBA2A895ULL, 0x9F4AA2FDE846A91CULL, 0x8088F998DAA7F8F4ULL, 
            0xD61919196E20FFE9ULL, 0xC470041D3FC8C031ULL, 0xC0626AA15FC702A0ULL, 0x5DA156BCCE59926BULL, 
            0x3D16DBE355D57E4FULL, 0x792DC9BB0D2742BBULL, 0x322B05F6B31DC4B6ULL, 0x4E070FBB7E324F6AULL, 
            0xDDD4267297422922ULL, 0x3192F1399E5FB191ULL, 0x3C360B65BA4AED4EULL, 0xB1588C4928EE349FULL
        },
        {
            0x587BDD6B938A37A1ULL, 0x7B0738F437105D28ULL, 0x2E8761FD2035E949ULL, 0xDD934EDE33103FEFULL, 
            0x48A510F62629EDD7ULL, 0x70B1D1AA3910E9D0ULL, 0x0B26B5184F4698CFULL, 0x5923CBDFCF44A6F2ULL, 
            0xF2082651FDF898FFULL, 0x38CF7EF1CF83C74DULL, 0x7084DF46849D721AULL, 0x34568CA54793CFABULL, 
            0xBCF9BC0098A9E3A0ULL, 0xBC08D6FFEFFAEC1AULL, 0x7C6A4245F59BCA4EULL, 0x15CC243B8B559613ULL, 
            0x497A31CADD1E1C84ULL, 0xB98091305E8B0F84ULL, 0x30745293F7B14CD0ULL, 0x123EDC0252CBABB3ULL, 
            0x3DB4BCBA943C0D2DULL, 0x1108F7215FBB8A53ULL, 0x0D8AD942158FF7B5ULL, 0x3B21136AB36EC7D6ULL, 
            0x046AC564547A6EF4ULL, 0x15322CBEB2692B50ULL, 0x9FD85BC5C5F606D2ULL, 0x569DBF6361DDB591ULL, 
            0x3F189ED677E74B13ULL, 0xB59686FB51E09ED8ULL, 0xEF215A6BB201B3ABULL, 0x19D2C9BDB699123DULL
        },
        {
            0x681B24EADA4B1E41ULL, 0xFB25C707D78D0C39ULL, 0x9926F62BB8815862ULL, 0x184A92A58495AAAAULL, 
            0xCB40A2983571CBBCULL, 0x9184BC5F424D5AF4ULL, 0xB466CFBBF1622429ULL, 0x80DE10F47F51C273ULL, 
            0xF510980EE764DF7CULL, 0xB27EF546D8D5428CULL, 0xD64FCB6CDF623105ULL, 0xA88137F62447C3FDULL, 
            0x23ED7DB5BDA6CF62ULL, 0x2D5337E5A19804A8ULL, 0x68659102F6CB52FAULL, 0x5945B33B7BBDBFC7ULL, 
            0xFCAD97D70C457C14ULL, 0x31BD5DAB4A803A26ULL, 0xFBB29A52AF1AAB43ULL, 0x8EBD356BD64DF58EULL, 
            0x5969DF99B025E214ULL, 0x409708FED066FC01ULL, 0x934BDBCBF25F77CAULL, 0xB53C4838F2D9F7C9ULL, 
            0x88EEC4938046589EULL, 0x14878472466A4C60ULL, 0x306841C581D69CEEULL, 0x37C649B6ADAD795FULL, 
            0xDDAEDBA4582C161EULL, 0xB98B73343AAE5344ULL, 0x97646FAF01115D6DULL, 0x0A5F2545A0C389C1ULL
        }
    },
    {
        {
            0x5FE9F3F5AC69ACEFULL, 0x6FA11430DEB49785ULL, 0xB5426CC039017E29ULL, 0x97AC53F2A7191F15ULL, 
            0x7815880D9A32CC51ULL, 0x9CD4BFEF966883BDULL, 0xDE86C618CF879DBEULL, 0x634A7B963677CD4DULL, 
            0xB7A06131C1E7FC8CULL, 0x23C1E2237BD05816ULL, 0xE7A011B212AFC2A9ULL, 0xD43002185D3F9F17ULL, 
            0x75E9492181C3DFC2ULL, 0x93BFDF0D752177C1ULL, 0x672C91E442C34475ULL, 0xC60706756BD53F22ULL, 
            0xA12E579991E5F59FULL, 0xCCB786EB0F5E3171ULL, 0x5E7E4CB2029CD1D9ULL, 0x66F09FA5D611F61DULL, 
            0x8DF4ED2C6FA7DDACULL, 0x72DC96AEFB60AD58ULL, 0x19F09A2DB5457E52ULL, 0xA5B9B11EA30DE7AFULL, 
            0x7212CA340D8D8F0AULL, 0x0247F8AE805CFE7FULL, 0x7B81E5BC0D074D3BULL, 0x7C7655A61D23E654ULL, 
            0xA1CD19D8DE54D818ULL, 0x7C04B4AEE005620BULL, 0xFEE770AEF42BD2F6ULL, 0xAFD8A51414E87458ULL
        },
        {
            0xEE98EB1CB33845A8ULL, 0x89F977FB0AEAC55DULL, 0x6C4A8732DD8ECF2CULL, 0x0EC8CEE39635BB17ULL, 
            0x7B4791BB1B19945DULL, 0x64B9605D750EDB32ULL, 0x38794CF4C42A9114ULL, 0x3C1E450B2AD499E9ULL, 
            0x56AD65344DB0F64FULL, 0x1E999A76452F59E0ULL, 0x1502A25E609F0386ULL, 0xD7712D86317B6955ULL, 
            0xE72C20A3D1BB369CULL, 0x8524806C6C5027FCULL, 0xB0934D8420403FBBULL, 0x5547D1B0445CADD4ULL, 
            0xFF9112FB73356C08ULL, 0x0200EFABE2AF737FULL, 0x9684AC91E7FEFDCCULL, 0x463CC539E6685084ULL, 
            0xE45E661707272D19ULL, 0x117C82632A3FFF9DULL, 0xA712E096D6D3F5E0ULL, 0x19AAE50660A8EBD4ULL, 
            0x669FE0F9AECFD860ULL, 0xF8F49B291B307D4FULL, 0xAE8250D5C35C547AULL, 0xD283E23CEE6ABCC8ULL, 
            0x5148B72BFBE5FDCFULL, 0x9B5BB776F7808908ULL, 0x7E3E8B9DF968ADA5ULL, 0xDAF0AC2A04401347ULL
        },
        {
            0x5D3BF12FF7CABE00ULL, 0xDD4CFE4E93D82580ULL, 0x9D2B299CE6F64CB5ULL, 0xF9174391D04CF01BULL, 
            0x210CAD42E939251EULL, 0x229B6FA21BC1CF94ULL, 0xE8C9BC6130AFE7C3ULL, 0x09F17D8F8A03C56FULL, 
            0xBC6702FA24F060ADULL, 0x2BD81BA38E40C4E8ULL, 0x161D524474E0AA8EULL, 0x8F7857360A6EE429ULL, 
            0x3F421BFFF3B3266FULL, 0x96707A2D492CA020ULL, 0x443991C7E4593A79ULL, 0x26FF2A5AA2C3554EULL, 
            0x032FE66BF31BCF8EULL, 0x466250F45D5EF598ULL, 0x013B892849771C07ULL, 0x85AB813783989667ULL, 
            0xE7371280A2631ED9ULL, 0xF525A1A631AA4A56ULL, 0x311B912D7FF97F2CULL, 0x57FE5AC678EFDA2CULL, 
            0xC3453FAC820C9787ULL, 0x395EDD58A6C9A7F0ULL, 0x89460D5A92D537E9ULL, 0x8D234600D5EC6B86ULL, 
            0xD2ADDB19D47D36DFULL, 0xBEAA04715397D11BULL, 0x7353BB4462935505ULL, 0x3918E2B7CA6B3E21ULL
        },
        {
            0x7F941C96EABF5357ULL, 0x6B84940BC3877F07ULL, 0x804A146D018996A8ULL, 0x96509EF74FEA7D4CULL, 
            0x38861FF47882FA25ULL, 0x7BC1CF89C2116A55ULL, 0xCC5A6DEFCA20330DULL, 0x2E60F0F12B9AA2BBULL, 
            0x71975A0EF78AA49AULL, 0xDB3A140FAAE6FC62ULL, 0x773314E9FFA6EF14ULL, 0x8345FEF5C5484465ULL, 
            0x36C137E879C6E690ULL, 0x67EA1613BC179E57ULL, 0x4C57BFB4FE3E2355ULL, 0xB0ACC4C52A3C4D3DULL, 
            0xABA61B4D0D839A4CULL, 0x4DA6C70240779D98ULL, 0x30F3C0CFCC93ABDDULL, 0x49C05B3290FAE84EULL, 
            0xBAC5D6BBF8107839ULL, 0xF3B0FBACCFF6D25FULL, 0x7481E3CDB44546E6ULL, 0x8C650472E85D5957ULL, 
            0x8D0FA6CAC49A3592ULL, 0x3ACBD4BCC6E5EC9DULL, 0xADA3DE919AE35900ULL, 0xEEA660FD6944F735ULL, 
            0x8DE0CCA393AF0DF9ULL, 0x82BF93D0CF9EED54ULL, 0x637EF17BF9428915ULL, 0x5BC61F036165C35DULL
        },
        {
            0x0A76237D1E2AF86EULL, 0x75D1DA0631D628E1ULL, 0x29B8BCAC51439C52ULL, 0xDD544D3AF9CF74DFULL, 
            0xBCAC4DB5CAAABB11ULL, 0xB11A8059A6FD756CULL, 0x60694B7F4AACC0F5ULL, 0xA2DD90FDBDC94633ULL, 
            0xB2B1AB2C96E1A70EULL, 0x7C00B7B9F2E9E884ULL, 0xD52F53F51DD2814FULL, 0xC6EAEA5734A179FFULL, 
            0xC336DFF59EA3CE96ULL, 0x519E3A0D330ECC17ULL, 0x7DBFB6C7F4C6D9D5ULL, 0x0EFFDDD1ABBEB3CCULL, 
            0x06CE08B63B2335C7ULL, 0x51A360A5DB88F43DULL, 0xCB2057C755633368ULL, 0x5ACDDDC6613BE721ULL, 
            0x70FA551E9ADBBAF8ULL, 0x89B98E18277BCAD7ULL, 0xED4A056805FFE7E1ULL, 0xC6B80F18135149EBULL, 
            0xF334D46CE95E9858ULL, 0xF89979331E1EA806ULL, 0x0E147C7920576DE8ULL, 0xF2F70D13C29A82D9ULL, 
            0xBDF4A562F91AB92DULL, 0x86DE8ED05CA29BEAULL, 0x1E4E218EA36122E4ULL, 0x6DF708C2BEA4F642ULL
        },
        {
            0xB7E9083FB63B48C1ULL, 0x62799DF1DB2A487DULL, 0x9352C4CB02853555ULL, 0xA7B21EC10FC3951AULL, 
            0x44AD10F26DE9A434ULL, 0xC8DEC4A1548BFA6AULL, 0x73C7CE5A67DE1C51ULL, 0x4214B80CE95AB1B1ULL, 
            0x7A1F0672B2A303BFULL, 0x08334ADAEC124703ULL, 0xF65EE070C704C5EAULL, 0xCC5D9C190E08DC21ULL, 
            0xE310AB7E718B2D50ULL, 0x6382B9E93526F38BULL, 0xE2A2FCD91DC0357AULL, 0xA60019EEAF7B5C44ULL, 
            0xAE117BF248209B31ULL, 0x940D92C00BA95C4AULL, 0xC95786235220DC31ULL, 0x9B90D1D1DCFF323AULL, 
            0xDE222B5F76756D18ULL, 0x8F4A3E435AA7A682ULL, 0xC3FF10E725AA4E45ULL, 0xC7F0AABAA67E8D2AULL, 
            0x6D1BC28E02577A3CULL, 0xDC82F502BC139BA6ULL, 0xA5966E98A9E8BD1FULL, 0x346A4BE9765A504FULL, 
            0x90EF47FFF6917E36ULL, 0xD14D5CD36AFF2095ULL, 0xAB3935891CAE12EAULL, 0xBBA4D26CC5F68D0CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseAConstants = {
    0x0F1FDEEBC011D219ULL,
    0xDB271AD53ABD05E1ULL,
    0xFA9809F507DE2EFFULL,
    0x0F1FDEEBC011D219ULL,
    0xDB271AD53ABD05E1ULL,
    0xFA9809F507DE2EFFULL,
    0x59C287EC7094DBDDULL,
    0x122AE49F64E55E55ULL,
    0x09,
    0xC7,
    0x2D,
    0x09,
    0x6C,
    0x41,
    0xB9,
    0xE3
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseBSalts = {
    {
        {
            0x0AE2A0394F418249ULL, 0xFE485F52C42B4419ULL, 0xB211D35D616AC094ULL, 0xB227B7E853C17D4AULL, 
            0x60169BD165B147F2ULL, 0x6E9977F161736B09ULL, 0xDFF8CB891F292B49ULL, 0xDFD166E61D805ACBULL, 
            0xEF1EF4606A50AD85ULL, 0xC14AB8CB20A2A3A5ULL, 0x54BD1EF60E0F721EULL, 0x521737545EB48994ULL, 
            0xDCBA1C1D723CF23DULL, 0xA5A6B5C4958F7445ULL, 0xA208F5113FAC151AULL, 0xC996879B8ACCE215ULL, 
            0xE62A6421F7989878ULL, 0x137335AF364D3C11ULL, 0x260BE0F2ECD6CB27ULL, 0x3A9FE0A99DE5ADFAULL, 
            0x255D804456B49E6EULL, 0x4B47A246D15442D7ULL, 0x6E6BCD3DAF058B88ULL, 0xBA2B9477577540AFULL, 
            0x7FEF9192B738D1E0ULL, 0x4A73B0E519526D61ULL, 0x9164BE7F1A26D407ULL, 0xEE9CC9707EB2195CULL, 
            0xEFFEF5F326045E4DULL, 0xCB79303ADFC91450ULL, 0xD5F57B3E01975BC7ULL, 0x7C50220BA494CE68ULL
        },
        {
            0x828290444256D2A4ULL, 0x6874CA24B8BFF8D4ULL, 0x150B8A31C159F545ULL, 0x8393F48E8367FFF7ULL, 
            0xA9E40A9FBA15BEDDULL, 0x3A7C753DCEAD960CULL, 0x58DF5298A831E831ULL, 0x5C1F8253A2E28634ULL, 
            0x80F28C962A788EA8ULL, 0x74878C66B421429DULL, 0x0C3D6EBC86E6C8E9ULL, 0xC6D1A99CDC26445FULL, 
            0xB8532D2B420EA9A6ULL, 0x0AB7470B2FBB7BDDULL, 0x8FC0C9C22649B421ULL, 0x591FBCFCA46A77DEULL, 
            0x0E7C18F481647A0DULL, 0x297B1EFBE8292405ULL, 0x4DF20BA3A18F9ADDULL, 0x97E82C27A3394257ULL, 
            0x5B0DA51280A348BEULL, 0xBBB0783B643C3DD3ULL, 0x9230AC976236E89EULL, 0xCE870132CD26C229ULL, 
            0x23B407EB1849DAA8ULL, 0x01C25E22C16DD76AULL, 0xC57FC24173FDA378ULL, 0xD9D976C57AEF45E1ULL, 
            0xFC02A0DD5D763C45ULL, 0xDBC8733A03D655B7ULL, 0xB4186ADD5CDAF4DCULL, 0x8161585422EF8EE6ULL
        },
        {
            0xFC7B44784BACC21DULL, 0x4C88CC9864331166ULL, 0xC3000E7610F253D1ULL, 0x0CA188A180C9FD0DULL, 
            0xA6865DAAB3A49372ULL, 0x4B6022A712F28D5BULL, 0xD066F2EA03B3D5CCULL, 0x840C6F5D7A406D2AULL, 
            0xF7913A7957EA2A52ULL, 0xEBD155619FCB62DBULL, 0x4319C4212C5DA9C3ULL, 0xB25E5A152AD10844ULL, 
            0x38ED363DA9DA9E23ULL, 0x503F86DF0C1DCFC7ULL, 0x8612EE44F39F82C3ULL, 0xACBA5F1E3BA76CE1ULL, 
            0xB4757106313C1865ULL, 0xEE1BAAA3F037937EULL, 0x4C9E22B7490366DDULL, 0x8EFCAA762A69AC86ULL, 
            0x080ACADB32CB26BCULL, 0x02D27B3C89D1A3B1ULL, 0x179C2D2F3D3FD84BULL, 0x90A93AD82BD62CC4ULL, 
            0x81FB6807889AA94CULL, 0xF6FC5AA2A33F1792ULL, 0xDF9CCA90AED1CC45ULL, 0x10A21DEBBD456021ULL, 
            0x722D498106227807ULL, 0x17B93DBFDFAD78D7ULL, 0xF250D84D01EA4395ULL, 0xC65F707DA5B13CB6ULL
        },
        {
            0x3B3D3350E9D277A0ULL, 0xCC8C72221C922FE9ULL, 0x61D0E3164104AF8AULL, 0xA153A0BE27661937ULL, 
            0x4FB855D35B9FC487ULL, 0x3299B0ECD68E18DCULL, 0x6CD76B780F7AAD2FULL, 0xFC8C48D63669890BULL, 
            0x6155A7C6333225ACULL, 0x0374F607E4855F3EULL, 0xCA94B3B613515B37ULL, 0x707350D127961CF2ULL, 
            0x53765B922C558FABULL, 0x6EFDC4DADA2849D1ULL, 0xB77464C27FA1CCAFULL, 0x17C5BB71D8C2DCBBULL, 
            0x520F1692860023F1ULL, 0xEE44033E60F5C630ULL, 0xF2BEB2507458F8CEULL, 0x6FEA492E14B821D6ULL, 
            0x0311239651CDB246ULL, 0x53B388114D4E2A9AULL, 0x90845DB9C5785336ULL, 0xD3BD6BA9AB78D926ULL, 
            0xB775AD456252EAB0ULL, 0x87C4F7FDF225F7C5ULL, 0xBBCAFC9D693B986EULL, 0xC11805F504F62A59ULL, 
            0xA9D84ABFD9971927ULL, 0x085E0531CC0DD26FULL, 0xFF3C9CB30614DD90ULL, 0xAA6BFB24277AD297ULL
        },
        {
            0xFD1E99563E971D88ULL, 0x87DA987B85CB7B0EULL, 0xFB994E29FC278B02ULL, 0x1E023FC40EE4DF5EULL, 
            0x15AFCF664FA387C6ULL, 0x3A29D8045B615DF6ULL, 0x3C671FB6FD231937ULL, 0xB3AE8336CEEF0C1DULL, 
            0xACAB39F570959281ULL, 0x4451EA745AA8F01DULL, 0x2DDA0A3BA8039622ULL, 0x120CE43B36F6909DULL, 
            0x37E3D6CA6D505743ULL, 0xF26869E1C4992DA8ULL, 0x589FC843E368C881ULL, 0xB68A4D0EE9D70FD5ULL, 
            0x68C79EA71C1C4256ULL, 0x9AAB053A357DBA71ULL, 0x70F404A31F6F4822ULL, 0x21E2843281FF00FEULL, 
            0xAE73A3D46F9F4E5DULL, 0x1EEBD3F459718451ULL, 0x42C7FF3164FE3F5EULL, 0xFA8E65D048E280D7ULL, 
            0x68BAED466C905D1AULL, 0xDF1FACF1F5EB4275ULL, 0xB5DFD9F116DCDCA3ULL, 0x16AE9041B316D486ULL, 
            0x2B4BF7551432EFB2ULL, 0x176F6FD084BCD7ADULL, 0x4286D58EC27E7D76ULL, 0xDFB30BD5BA0E8851ULL
        },
        {
            0xC33F2CB820F24218ULL, 0xAA62B4DCFDE90E98ULL, 0x6C9FBEA0FBAFBF78ULL, 0x5032DF1E776AE202ULL, 
            0x61D9F64C50F49A5FULL, 0xBB09193636EE11A3ULL, 0x303B5B1EE3B2E974ULL, 0x159EEEDC6ECBABAAULL, 
            0x86B6B613BE3194A4ULL, 0xFD14BC3B69FA7A35ULL, 0x92CE34B6327DA1BCULL, 0xE5592BD64EC02E0FULL, 
            0xF2D421771998B5E7ULL, 0x8998F00F97B5A7E0ULL, 0x53719E45FD113BECULL, 0xFB4B29EC4CC81EF5ULL, 
            0x3E2B6ADCB263DE17ULL, 0xF2A4C8CE14F89B1CULL, 0xC09657C50A693011ULL, 0x77F5F444877F0B40ULL, 
            0x6D12E424B477CF40ULL, 0xABE499A0F9BEEFCFULL, 0xBE0485677401D58DULL, 0xAB947F4C6A35658EULL, 
            0x8BC82F6B1812691EULL, 0x017DB45137FF4130ULL, 0xAA384EAA8561F13DULL, 0xBF2CCCF144E3D62BULL, 
            0x1EBA6E19C1B3A150ULL, 0x6DE0DAD90A0CA2C3ULL, 0x19AFAB39A335A4DFULL, 0x9898A737E6AC8E73ULL
        }
    },
    {
        {
            0xD020137848AC0F97ULL, 0xEE400B8B0E4298FBULL, 0xE81D5F5A2A529EA0ULL, 0x21BD42511E1E4AACULL, 
            0x021F0C1F41BDA177ULL, 0xBA03DAC90046561CULL, 0xA7C888C56F7CE7E3ULL, 0x5FB53790BE12188FULL, 
            0x429942B4E20392CDULL, 0x21A62961B3F24E31ULL, 0x6ECF2068FEF34A35ULL, 0xD4EE839A27537226ULL, 
            0xC1B389531A4B2846ULL, 0x061AFFD6709B4300ULL, 0x33A4D17235160987ULL, 0xA1DD3BC91CAF72D8ULL, 
            0x6D2AA3A9AFF11112ULL, 0xD5FA180C25F22F60ULL, 0xAADBD010B4564335ULL, 0xB0B93860177F3417ULL, 
            0x9BAEB5F116E89E31ULL, 0x9EA9D149A16E2FA5ULL, 0xCFF2B89E411A98AAULL, 0x2A484C3B38E73E91ULL, 
            0x9E656659E96077B3ULL, 0x3D784B2051A2058BULL, 0x0A1558A402A6D9BBULL, 0xE8A2C0AE4268C255ULL, 
            0xA87221E2E13F6D35ULL, 0xBFD2C90BB019D20EULL, 0xB1C109177B7CD8DCULL, 0x30734632DB316DDAULL
        },
        {
            0xF4D6BC9E2100FDA7ULL, 0xCA7B80EC1C7335A3ULL, 0xF51C6C0D5F4041D0ULL, 0xDE1774DABE3310A6ULL, 
            0x2B4F1AD05ECFCCE2ULL, 0x068A9345CF8C3F03ULL, 0x697B41D1F54B4665ULL, 0xB89F84C8FC842D22ULL, 
            0x985ACBE64EEAAD42ULL, 0x786E3C6BD37C8E1CULL, 0xB6BBBFEB9D09634AULL, 0x25FEB163CE560D60ULL, 
            0xFD635315734839D8ULL, 0x9CDE0F603F24F39DULL, 0x744D02E6197DB639ULL, 0xE09DBBC283EBBF4AULL, 
            0xC6912F06B7B6ABA6ULL, 0x8B1F6FC439AFB4F2ULL, 0x0030662E78670CA0ULL, 0xCF69E8646CC6D0EBULL, 
            0x518BBD7DC0C251C8ULL, 0x8EC0DBC857C744E9ULL, 0x9A9761B1926062DFULL, 0xAB64309067DAC943ULL, 
            0x6C758EA4AC3F2EEAULL, 0x050F3342EE8F8390ULL, 0x73E3758614781CD3ULL, 0x5145E00CEA3EC8B6ULL, 
            0xF19DCA2EAFCB7AD0ULL, 0x042CF5617BDA0064ULL, 0x99FB791ECEAC182EULL, 0x73B37DA052197BE1ULL
        },
        {
            0xA11C979C175E30F3ULL, 0x88D0B91AB229B594ULL, 0x747D5DFABDF903DCULL, 0x117FFE81FF34CC62ULL, 
            0x639156E7AACB8707ULL, 0x60042EC126F8960EULL, 0xE1BC5482D3400319ULL, 0x8669C6E958B9A4B4ULL, 
            0x1D2BB04C7924EFF1ULL, 0x33CC7F1C13AE0B05ULL, 0xD853359C497005A6ULL, 0x579567F3020C9F81ULL, 
            0x81E265E8EEA2E76FULL, 0x6F10D6ABC7BE83F0ULL, 0x8E06B8E833C42E7FULL, 0x16D41ECC90E7CA8EULL, 
            0x63999E17A0A6EBC7ULL, 0xE70A1185F1D4579AULL, 0x8F1117A7A94FA892ULL, 0xB01CACB9B8FE14B0ULL, 
            0x57F60A78047A6734ULL, 0x1FD8210A76964264ULL, 0x0BCABEBCC1FC7C8FULL, 0xF36157547A80552BULL, 
            0x955181D8E794668EULL, 0xA9AB129398BFA018ULL, 0xFBC767C3805B666CULL, 0x017775E1812597CCULL, 
            0xBAB637806B3D23DEULL, 0x08DA6150898A41C1ULL, 0x5B24BB8A185CD11BULL, 0x857A2CE5397CC24BULL
        },
        {
            0x12776370971265AEULL, 0xB52D40D2B75CD7BFULL, 0xAF6CABA2362BAADEULL, 0x314EC9DDAD6AC5D8ULL, 
            0x4D20D2CA9AD969D6ULL, 0x3C8E69DE819BF871ULL, 0xC0CFCFB454859EFCULL, 0xCA74280257BEA3FDULL, 
            0x3A43136DEA8652EBULL, 0x992023443EF132EEULL, 0xA8F5685267945A17ULL, 0x9D8776DB460DBA4DULL, 
            0xA2259F3D60A646D3ULL, 0x0D747EDB9A463772ULL, 0x57DFBFA8FEF6AC8BULL, 0x44FAF26BE91DE7F0ULL, 
            0xFA9703DCB91FCFDAULL, 0xBAFD459AEF977B9CULL, 0x345D8F162BEB4F36ULL, 0x92C82AA8544C30F3ULL, 
            0x5422187A9138C353ULL, 0xDA25074B757BB958ULL, 0xB48FACD91CA9924AULL, 0xECC6079FDEB1E8A0ULL, 
            0x825AA27E3FE22AC8ULL, 0x3852A9BAB15D6925ULL, 0x61A88855B2053417ULL, 0x94778B9E87D43D15ULL, 
            0x42A6E412A4BC4DB5ULL, 0x722A4122281F24C6ULL, 0xC68388C72224DCB5ULL, 0xC3E0BC1AF7390C02ULL
        },
        {
            0x39FDC91FEDCEE93AULL, 0x4B68676B4E7836E4ULL, 0x2BEC557F615F2A56ULL, 0x803FA91B1C1F0321ULL, 
            0xD16BCCE0B67B2590ULL, 0xC3018BC331BD8813ULL, 0x7B42A8D0681E9152ULL, 0xC5B505E56C3BCA60ULL, 
            0x84FFA7434BEEC92CULL, 0xDFD87C549C85AD48ULL, 0xBC541B9E9A25E94AULL, 0x15091022E199C6B1ULL, 
            0x57950B563CBA1EDEULL, 0xA0AAD5DEFDBFC0D6ULL, 0xBD4124E0F20EECB1ULL, 0x9EB0EF3B37E2E488ULL, 
            0x376E7019038CCD16ULL, 0x9E52CE65D356956EULL, 0xA0D3D65FA4444303ULL, 0x367613652B326272ULL, 
            0xE32B704F09526428ULL, 0x42486F5B77C48C4CULL, 0x87969BC60980F3D2ULL, 0xDB575C8B50FBE35EULL, 
            0xBC8187E2DECA5ECBULL, 0x9C29F3AFF927A1C3ULL, 0xFE0C46F7AF01C502ULL, 0x085B0B0C98CC44FBULL, 
            0x1178231522351EC3ULL, 0x38EFB6E9A88A9216ULL, 0x434B72493177883CULL, 0x4D9B4F5B04F5B72CULL
        },
        {
            0x5A2E5F12ACB7710FULL, 0x32138D31D99154CEULL, 0xB04E88480AAC0949ULL, 0x736E084733F3110EULL, 
            0xD14C2B53565FF9AAULL, 0xEC46B75045B00193ULL, 0xA8584C4D57FD8BC2ULL, 0xDEE4B4A3399B9F7DULL, 
            0xBEF6E27AF14E26ECULL, 0xB41DBEE9798DBA60ULL, 0x4CFF1F570C677631ULL, 0x20D43F05B7B4B30CULL, 
            0x263F9F9120085BC1ULL, 0xB53BCC859F9C296DULL, 0x9F3C8A8F99BEC78DULL, 0x2F9FF7B8019F5C3EULL, 
            0x0C72DE03F2CEA6EFULL, 0x20F3BDBEF62331C2ULL, 0x52BF1C259602DED6ULL, 0x4156D284F3DEFEE4ULL, 
            0x1A1FD9BE2449DB85ULL, 0x49FCBB1336019A0CULL, 0xAEC4094E1AF1909DULL, 0x5FC31B824C1262C8ULL, 
            0x6FF9E192AE7C15ACULL, 0xF8BB0BA6F8E059C8ULL, 0x22D9BA172764612FULL, 0x4F8F11904995C603ULL, 
            0xFE659C178C26BBB7ULL, 0x3E654A699044D499ULL, 0x7539C66B9ADB5F2EULL, 0x30F7CE8EA4A5FDD9ULL
        }
    },
    {
        {
            0xE82FFEBDBBB36350ULL, 0x0A363F2F3EE39DCBULL, 0xB6EE31EF7BCE3DDDULL, 0x0ED27F5AE0AEF80AULL, 
            0x1901BCCFC1900E34ULL, 0x023D7BCF2AF41D1EULL, 0xAA138F6D0CF7B5A3ULL, 0x2FCB0B5EE6FF25AEULL, 
            0x0EC8515D451456F3ULL, 0x0D53AAED974CF366ULL, 0x9F11C4D6E84DBD2EULL, 0xDDC589C3340F079EULL, 
            0xD31FD2519AE5543BULL, 0x7867579F5FB2CF01ULL, 0x081345BA1F831481ULL, 0x939BBDD4287BC1F9ULL, 
            0x22852D9CEBD5CE85ULL, 0x83FB075B596D4DBCULL, 0x03363648B11CE25AULL, 0x90097DC0374274F4ULL, 
            0x9E67DFA32FA75991ULL, 0x465BA81596C1371DULL, 0x197F4EE0CF0710C2ULL, 0x2A90D2751FB53109ULL, 
            0x1934B3924E197BB5ULL, 0xDE7622D6707F4E99ULL, 0x46BD40D769BD1683ULL, 0xA5B4D8A886EF74BCULL, 
            0x499C6155166A326CULL, 0xB683C005ECA0B60BULL, 0x2D686174247D5CB3ULL, 0x3CA121F7D056C8EFULL
        },
        {
            0x4BBD73F98D438422ULL, 0xF1DC58FD0D832BA2ULL, 0x80C2291C67E06F09ULL, 0x8815C2E69327F7E9ULL, 
            0x48DE6B27CD95DEFCULL, 0x32DD1314BC09F84AULL, 0x16285B857FD83534ULL, 0xDA3D845D2058E4ACULL, 
            0xC505D4E5831253D7ULL, 0xAC469F04DD23FF32ULL, 0x091F644AB74FC241ULL, 0x83B4821D7B5538FAULL, 
            0x194C573CA153A3C1ULL, 0x09F4CD3AB4F71597ULL, 0x44850CC6A1DE822BULL, 0x21682251BD70F5D2ULL, 
            0xB83481BB6C7220B1ULL, 0xF1166747F712DCE6ULL, 0x0828B62DD9BE796EULL, 0xFADEF441DD28823EULL, 
            0x553B5F1D0F40895FULL, 0xB323DC27BEF5E366ULL, 0x598A56511E6E3C7DULL, 0x094B0DD54C63B3C9ULL, 
            0xC86F1BCF7556D7B0ULL, 0xE6A510E0DCAA15C8ULL, 0x305C28A198D75C09ULL, 0x98D5849D788ECBEEULL, 
            0x488ECECAF9C71056ULL, 0x94DE5FC1B76E66CBULL, 0x2E45D46EA104D1F9ULL, 0x1455288F4400D117ULL
        },
        {
            0xDA98A53D92D1282CULL, 0xB034C99A0CB2C398ULL, 0xFCD66A694CF30495ULL, 0x15792DC91FCAFB28ULL, 
            0x80B99A27044B64EAULL, 0xE5B2F1EC8D48F1F3ULL, 0xCF6CF73AA9279A8FULL, 0x25B605B99A1F6FF4ULL, 
            0x0E0D817DADB5CA3BULL, 0x2DC651551C929481ULL, 0x840A1389C89B5856ULL, 0xBDDEEF4BCCA0402EULL, 
            0xFF5A1D5D707955E4ULL, 0xE11335E53C467BEFULL, 0x3049AAA82D36E989ULL, 0xA4BA35C40C5D5BE5ULL, 
            0xF5044D99D851DCC7ULL, 0xAC31B7C141814953ULL, 0xF4441AE4648E3636ULL, 0x86DB2826D097BE02ULL, 
            0x0A3C25C02E94A8CCULL, 0xD6BBA3E8ECEDC1C2ULL, 0x9A6C33FB7BACA16FULL, 0x2A57899793CB7389ULL, 
            0x769F9DA9BC22A358ULL, 0xD70E99AC32F61691ULL, 0x40AF135D30DE8CBBULL, 0x6FE4FED042838F73ULL, 
            0x020C78ABB25A3D29ULL, 0x90E23916315A214EULL, 0x03B3C600A86CB1AAULL, 0xF8FD391D48FB5EEEULL
        },
        {
            0xD08C11F7C5C7134DULL, 0x0F60810E6069461CULL, 0xA5EF47C0257F40FFULL, 0xFCEEEB4E3383E5A7ULL, 
            0x68120260672853AFULL, 0xA024F8006ED1C87BULL, 0x31CB53AD19CCEDE9ULL, 0xF4C4FFE732A2B4B5ULL, 
            0xF8C4539533D62C4CULL, 0x9B40F8322AB4CD17ULL, 0x291063E2CABA732AULL, 0x0728C5BCE047AB1AULL, 
            0x560512A9D0253AAAULL, 0xF77F56F4B6FE9836ULL, 0x5B44658EDF0A6402ULL, 0xD604213033D49618ULL, 
            0x8BCAA1FB4E5473E0ULL, 0xA8E0E9E11E5C9254ULL, 0xB71975A4F5EED418ULL, 0x86902AE0E63AA515ULL, 
            0x5A79B8C7E3CB9B91ULL, 0x4992B756780667B0ULL, 0x1A86F27F02934F5BULL, 0xF9D13EEDA1421740ULL, 
            0xD3F2F1982B83D42EULL, 0x8A0832CDC405B3EBULL, 0xCAD7BB2F1973A7DEULL, 0xB2085AFD1D6FA3CEULL, 
            0x3CA2DE7DB008A016ULL, 0xD70D2F2599DCA51BULL, 0x21BC651792F57962ULL, 0xEEBB7BE2F302EFF3ULL
        },
        {
            0x2C96DADF598EE62DULL, 0xFAEDE5971FE07C25ULL, 0x99487D281B8A9A77ULL, 0xD92788DCBD8819A4ULL, 
            0x76DAF28D711F1973ULL, 0xEE90867C9DA1636DULL, 0x8E55D01F49D8707BULL, 0x9986C97F4ED30F8DULL, 
            0xF265138E0A0D8C9CULL, 0x3DC10D3F36FC0833ULL, 0x93B0238FD9E3CE74ULL, 0x009C2E105785C88FULL, 
            0xF53C843343004775ULL, 0xB3E53E33C0D2576BULL, 0xC544C5C3BF714830ULL, 0x61CB04484E1B3348ULL, 
            0xB8DD14D74CB96FDEULL, 0xD8D0407B04BF3A2DULL, 0xD2EF4BEC6BA212CFULL, 0xD0583BCBBB0A8023ULL, 
            0x54BE05508A06474BULL, 0x025EFFA6B629F8B4ULL, 0x2E1E66732A5E86ACULL, 0xFD5833988A32D72EULL, 
            0x623EFE7D0D390D69ULL, 0x4FC533BD80A3BFD7ULL, 0xC2927FBE3CAE46C6ULL, 0xE2C828F9C0F249A6ULL, 
            0x2CCC06FED707F141ULL, 0xC253AB3C1515B3CAULL, 0x1BDDB3BDD65F8E5EULL, 0x4623AAB64AAC228DULL
        },
        {
            0x841830FD23A08FD1ULL, 0x0F77606289C4BED8ULL, 0x486CA86096A4122AULL, 0xB206A9434239BAACULL, 
            0xE0F5BE561FB1B656ULL, 0xC59BED0FC8A424D8ULL, 0xACD0736C17F7D69DULL, 0x642A3943F8218FEDULL, 
            0xF71B56AA3B9223B5ULL, 0x11BA7D199C38B9F0ULL, 0x0C091E5B20C290A2ULL, 0x8AD29212F64B4CFFULL, 
            0x6B3DC451EE778911ULL, 0x28D19B8CEE63D7D6ULL, 0x76299C4BDEAF648CULL, 0xF6B99F1BB5C2A95AULL, 
            0x79CB4B687AFDC3DFULL, 0xB09D0D1F305C8EC6ULL, 0xB3C79806852645DDULL, 0xCED8CC343857B6CAULL, 
            0xA31F2AA04957096CULL, 0xA2C7297D96D56B5FULL, 0x955C8682EE37389BULL, 0x08ED5FD1727AB927ULL, 
            0x5A179C9733201324ULL, 0x869E2CFFE9704FA3ULL, 0x5C624D3C64F76348ULL, 0x12567B616D5D2D2BULL, 
            0xE7CF49116FC68DEBULL, 0xD8B59862DBB663AEULL, 0x407445CB2FD28962ULL, 0x6E238E3D76BC35D4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseBConstants = {
    0xCE3D83C559318B82ULL,
    0x0BD481B620CAE3A7ULL,
    0x54307961103CBC87ULL,
    0xCE3D83C559318B82ULL,
    0x0BD481B620CAE3A7ULL,
    0x54307961103CBC87ULL,
    0xA476AF7DA70B011FULL,
    0xCBE8045999F8114EULL,
    0xFC,
    0xB7,
    0xCC,
    0x16,
    0x4B,
    0xAF,
    0xFE,
    0x76
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseCSalts = {
    {
        {
            0xB4E10A36ADE08B60ULL, 0x072E5342E3411AABULL, 0x8BB69DF72A8EE58DULL, 0x5BD9E5C5DB755ABDULL, 
            0x29BA92A58E6EC14FULL, 0xC7A8A32E8085E504ULL, 0x3F1C626126591947ULL, 0x3FAEF7A726CECC08ULL, 
            0xA1A6FB46993070AAULL, 0x6DEDCBCD6BAFBB85ULL, 0x2E966FB093FB8C69ULL, 0x04814426C68FA69DULL, 
            0x167845EBBCF72E52ULL, 0x5C1B1487F022EB4BULL, 0x9FB9C35A5A28CCA1ULL, 0x0BDAD4F4F1BEEEC3ULL, 
            0x8433557D3711733FULL, 0x31C0BAD0ABA28C72ULL, 0xE5F58E24BAA38B8BULL, 0xED10D0ACD50FD141ULL, 
            0x1B57B25ADB1CF910ULL, 0x0DCA22C2B4218813ULL, 0x29A030CCBE055F5AULL, 0xD15B417600D36F37ULL, 
            0x6246BDF43012FB20ULL, 0x54265B99DEC00D05ULL, 0x2CF105DD53732B8EULL, 0x71E2A375C5210778ULL, 
            0x9F3F0592576176CAULL, 0x45BDDFD593B9F09DULL, 0x7B469E126C532ADDULL, 0xC3617B691DB42078ULL
        },
        {
            0x0A714F3BA65A4530ULL, 0xD9A8D72CB17E73E2ULL, 0xFAC5E7DB95BE7714ULL, 0x415751F9727C649FULL, 
            0x2910F068F4543F55ULL, 0xD98318972AAE684DULL, 0xC99857726B69D72CULL, 0x49655DE29784C335ULL, 
            0xC46D0486B1EB02A4ULL, 0xBACF398DDDE871E4ULL, 0xEA71B70727466135ULL, 0xA2651C3A2775165BULL, 
            0x3273BA5F1FF0CEBDULL, 0xA13B2A0988DDE4B7ULL, 0x885F33759C2D5337ULL, 0x89E16F55B8ED8FF2ULL, 
            0x026E71309DF2F30DULL, 0xC7605DC90155CF8CULL, 0xEC977BE037338E99ULL, 0x6DC63D32BC3F67E0ULL, 
            0x34C4ACDEC66F20A0ULL, 0xF8FDDFACBC7BCA0FULL, 0xD5C06E5DFED55B73ULL, 0xA501D629FC766159ULL, 
            0x87D66327B151DEB9ULL, 0xB3248F0EACFA95FEULL, 0x6152A0097008F1ACULL, 0x8833A1AF67AAF50FULL, 
            0x4D4EFBBB2DF34B8AULL, 0xEBED8FB97AE89AEAULL, 0x19E486E696C936C5ULL, 0x0417E34AACC3B99AULL
        },
        {
            0x2D0D7D5C26354C4FULL, 0xBCAC59BD2A683409ULL, 0x9308DF56887B2148ULL, 0x76A436925F57EC82ULL, 
            0x22A86E9CBED1F01BULL, 0x5B42F5FBDAF4C47CULL, 0x572D339219E819CCULL, 0x6970EE7F5E127350ULL, 
            0x1286B4304E4197ADULL, 0x7A86EA75F470AB52ULL, 0x48C770DBDA4850AFULL, 0x790523772FBAF41BULL, 
            0xCEA90A99A81D95B5ULL, 0xBA28D1F5E13ACC6BULL, 0xBD62F9C1E6E19ECFULL, 0x246FB2BC821F348BULL, 
            0x84C69496CE4B1D0CULL, 0x92C594A809590AE9ULL, 0xD82FED2F42AC2E84ULL, 0x1298CC6C1D7DB0BFULL, 
            0x39BDFFD5C2CCB460ULL, 0x06A2424EDEAB4DABULL, 0x83567470CA7E579AULL, 0x122E4271D8E4E08AULL, 
            0x0CFE56CD3129E849ULL, 0xB04E3E8044BEEED3ULL, 0x80406C640EA67659ULL, 0x6788819B28832F2EULL, 
            0xAC60EC7EC6D8F5D4ULL, 0xA10FAFFA169F2CEAULL, 0x885CEA7BC8AFF452ULL, 0x21D08D9FE68E22BEULL
        },
        {
            0xDA42FFDCC73ACCEEULL, 0x918382D025F169E8ULL, 0x42CDE3A407FDC157ULL, 0x21E32885C8E5B176ULL, 
            0x4FD238EB8FA2B838ULL, 0xF0F683287826C9EDULL, 0x179C15357E5F33A5ULL, 0xA28F6605E3DD9EA6ULL, 
            0xBCB742CEF76B05D0ULL, 0xC2A9731227838EF0ULL, 0xB44B9C3B631DBC7BULL, 0x3496E63009E651B8ULL, 
            0x50D4AFB0811926A9ULL, 0x3E6A6BFF1003E548ULL, 0x83572637F0D556E0ULL, 0x10319261877C200CULL, 
            0xDB336152622BB7F2ULL, 0x4D0BFDF0027CFF5DULL, 0x5C7B96319EFA2B92ULL, 0x3E9EA4E46AB4AB8FULL, 
            0xA2AD90941996AFC9ULL, 0x7EC1659350A0FCE9ULL, 0x56610139C53065AFULL, 0xB4826D39EB98FF9BULL, 
            0xC202F065D1FD5D5BULL, 0x40A9B88D43CB7668ULL, 0x6642640866447AE4ULL, 0xCE2CE5A8182EC606ULL, 
            0x6D0A9CEFD6BB77AEULL, 0x4E91B72E87FD0F9BULL, 0x6A997CDE11E69EA4ULL, 0x6D102334F2D98FD7ULL
        },
        {
            0x6F5977E4938AB514ULL, 0x910D6762CE09FEE2ULL, 0x7882B7ABA041E2D7ULL, 0x58D15045A888D42DULL, 
            0x5C483692EC4D32DEULL, 0x799D89AD4C6F172AULL, 0x4E977638E9813891ULL, 0x1B87593049CE2E37ULL, 
            0x27DDA6739D82FEA8ULL, 0xD29FA4540A748F9CULL, 0x66282551CDAFD583ULL, 0xC3256B00FCE6DE93ULL, 
            0x167AA0451C25C370ULL, 0x39A0C0BC497CBBCBULL, 0x69826065E183C8E7ULL, 0x273508840D13B379ULL, 
            0xEAA9694419D228BEULL, 0x9CDE8519E49E2AE1ULL, 0xF1AB684E854BB3A2ULL, 0x48B744165E2B0867ULL, 
            0x28D18C2A3D7A0718ULL, 0x93805206DA9DC224ULL, 0xD0BD9AE4B18EB0C7ULL, 0x23E9AB1E68B7285AULL, 
            0xF14650F1D0CAFD73ULL, 0x6224BDD40FB872FFULL, 0x540044D5532AC55BULL, 0x4749E1B0FA29BF1CULL, 
            0x8EDF8EF2CB747FF8ULL, 0x960CC9043D6E0635ULL, 0x3D797074560F2CB5ULL, 0x13A9A89691A42FA5ULL
        },
        {
            0xD37738F8DF598FB6ULL, 0xF1EEF05DD43A70AEULL, 0x8C5E1C6E6E18CE6DULL, 0x848B43F5B2CAA569ULL, 
            0x5A0C81499E1C7D60ULL, 0x2E9B0F5140FA7F58ULL, 0x788D66F07BEAF86DULL, 0x3EF8D0E9D91D68A3ULL, 
            0xB05618F4D53676CEULL, 0xEBCF748D99459B2DULL, 0x23157B5A84092698ULL, 0x61FA25ED61C12BE7ULL, 
            0x0B7DF9DB748FEB64ULL, 0xFC9311FED712AC67ULL, 0x270AB6CEC0ED604AULL, 0x069DEFB4D261276BULL, 
            0x64812C885C809CB6ULL, 0x57C81E4DE3E07605ULL, 0x848DE75222209E15ULL, 0xDEFE67CD90EF400EULL, 
            0x86C24969945C35EAULL, 0x973B23D6F2C95759ULL, 0xB5DE9F9674117FBDULL, 0x54CE962C51C98387ULL, 
            0x540275735E7FE984ULL, 0x254143BBFFF7D863ULL, 0xF2BA21F99D8E4C24ULL, 0x53D476273A50D2BCULL, 
            0x0C43069D52871801ULL, 0x8B02F55B70C1B392ULL, 0x94ED78CAB3B12C25ULL, 0x16FD887CB2C5DCF5ULL
        }
    },
    {
        {
            0x0285488EDECC2569ULL, 0x8801355C0E8FAA1EULL, 0xD71F91B51CBA8E5CULL, 0x2295EB046E0D6EA1ULL, 
            0x265FAF659E53470EULL, 0x7A74A0DBEB4273A7ULL, 0xD66B07B344A60EC4ULL, 0xE3E0C22DB3A8FA63ULL, 
            0x9A654C5CAE13A106ULL, 0xFA639500E0CADE63ULL, 0x86463F67DD69A4C6ULL, 0xBC0441B298B3186EULL, 
            0xC31449C139482607ULL, 0x45A5AD6E9B469AC9ULL, 0x0139EAB33E3FE3ECULL, 0x3D80AE0DECF5E36EULL, 
            0x775B835EE390965DULL, 0x8987962923A965ACULL, 0x08FB64F8AA2BF503ULL, 0xB364248FD8CECCF8ULL, 
            0x246D47B0AF991332ULL, 0x617ACDAF25959064ULL, 0x868B64E15529DB6BULL, 0xF727CF83D582B44FULL, 
            0xECD1930A4D8E0E4FULL, 0xE130575E7F8E5003ULL, 0x10C47C16202BEF5BULL, 0x0368BA0952F20038ULL, 
            0xB248A106B3BCCA7AULL, 0x31D61A7FA4441C9BULL, 0x39B026EFAE263BE4ULL, 0x9AE5628B2D910DFFULL
        },
        {
            0xCCE1A129D8AD3210ULL, 0xD767BA77A6AD6082ULL, 0x3EB38D4CC223B78AULL, 0xD9FA35AE88D9D8DBULL, 
            0x1922C02225D1C7FDULL, 0xDED7BDA8CF4B72B2ULL, 0xEFD770386D7A1614ULL, 0x4A1EACD69EB4EB3BULL, 
            0x337789B26B37488EULL, 0xA3812252F52538D1ULL, 0x2EC28E229675C376ULL, 0x30BC660AE110E1CCULL, 
            0x614C49972490C594ULL, 0x0BD3B9D81BBAA735ULL, 0x63EE8CAA1F862954ULL, 0xA5151C16FA1F7DB8ULL, 
            0xA84B67E5CA54EC30ULL, 0x5DB655882AE3725CULL, 0x60350F4D52D97758ULL, 0x895EDFF3CB39646BULL, 
            0x3C24D6D4FF86CF30ULL, 0x8F08C9F6FEEF1228ULL, 0x39739D80220E22D8ULL, 0x48C98C1A68253504ULL, 
            0xF8F7D196EF3586F5ULL, 0x8F41E5C0013D3910ULL, 0x213C2C9AD4F22BD0ULL, 0x45F0DC443B1171CEULL, 
            0x52E2D2EE28819686ULL, 0x62BC4FFD82C3989DULL, 0x41EB44AE2F4A2EB7ULL, 0xEE85F0CB1508DE9EULL
        },
        {
            0x7A8BBB7370F233A2ULL, 0x0D72791A9FD28D03ULL, 0x11CDC86946735742ULL, 0xD6E412A1E0DFED2EULL, 
            0xC4C46B8D6792CFE5ULL, 0x9CA393761C5FD188ULL, 0xCA21A29DC2ADE19FULL, 0x5F5B4E7BFE5F8F37ULL, 
            0x395C7514F6461FF3ULL, 0xCAC0DDC2EFE5DB7EULL, 0xB6F5595F9186FA71ULL, 0x70881F8AA40F9F4AULL, 
            0x7E282A6973DB1AA3ULL, 0xA425AF5FE54E5047ULL, 0x2F0A4677F8186CDDULL, 0x2E4DDE78EC3F2CB2ULL, 
            0xDD693153E2156532ULL, 0xDCE9A655BFD36B15ULL, 0x9CEC275EFCFAC622ULL, 0x01AC6556E5FAC59FULL, 
            0x3A42C3DB7B8C1185ULL, 0xB8C981AFC1E6F8C0ULL, 0xCCC2E47F887C8255ULL, 0x791B87350AA59303ULL, 
            0xF6A872E11A3BE8E5ULL, 0xDDF6EEDAD5B615BEULL, 0xA59924F10F7B89B6ULL, 0xC296EBAC2A26CA91ULL, 
            0x575C78E99AD71B3FULL, 0xF872A4ADA5422BDAULL, 0x04F9191D2AFE2614ULL, 0x4715B9B43B8B37D2ULL
        },
        {
            0x8B08F5F1AECD84E8ULL, 0x186E9FA6FFD884D7ULL, 0xBEF87901F86F39FFULL, 0x68B557F6985DA10CULL, 
            0x3A923DE3A4D49969ULL, 0x1DC629515FF2F613ULL, 0xCABC71A0A7C211AFULL, 0x04F882D0F9C076E6ULL, 
            0x3F223A932FC79FEAULL, 0xF94B95BB481E740DULL, 0xC4EDC0FD2C99DB2AULL, 0xA92FE6910F8669E0ULL, 
            0x36AF19A8A7709B07ULL, 0x3C90E8E299CEDF86ULL, 0xCDA5F43AFEA89E4AULL, 0x1A827C6F468F68B6ULL, 
            0x5832BD2063BD07D1ULL, 0x3C10A725DEE40468ULL, 0x3E1A6DD685623127ULL, 0x25600A2A69B2E330ULL, 
            0xB9A11DA1051E74BCULL, 0xE6F676F6E20FE138ULL, 0x6BA30F6AB4BDDC5EULL, 0xA5EFA34A9523CC15ULL, 
            0x1D47DB6D8A7AC630ULL, 0xE780F0947805E519ULL, 0x9DB2F227CA1A7006ULL, 0xB482377F567BF31EULL, 
            0xAB00A44CE68951E1ULL, 0x19854F3887CCF609ULL, 0x1E472A5BD033444AULL, 0xC37E0E54E61792ADULL
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
            0xFB80C2A7B5570D91ULL, 0xF79F1AB4DAFA973FULL, 0x81497EA0739DEF4AULL, 0x58647BB8A0D311EBULL, 
            0x0C8D04DBA0E6C19DULL, 0xB50D792047F367FEULL, 0x0DC5C13B90C31CF9ULL, 0x72C11B537965C89CULL, 
            0xD8006205AB7473ACULL, 0xACC10AE2C608FC45ULL, 0x579F719C15A26300ULL, 0xA7E0923DF7F85A02ULL, 
            0x5A16F6D6C8E9274FULL, 0x61B550DB4CDAF1CBULL, 0x850E12A196BC3E2CULL, 0x5E032FACD938F5CAULL, 
            0xD3C24377DD2B267BULL, 0xD9679B53D7C5C6B4ULL, 0x96275045FF5D2B64ULL, 0x2447E5E7F2D8C2D0ULL, 
            0xE226213B3CFC59F6ULL, 0xBB5A21179824E822ULL, 0x6DDD6018FDB4F7FFULL, 0x8D63FD0D7E61F663ULL, 
            0xB6E7546DF934B209ULL, 0xAA0F50713ED09ABAULL, 0x20F5A1D6B0337C6BULL, 0xEC9A23400D5709FBULL, 
            0x5A4677E4FA308C96ULL, 0x9CDC2C75205ECF53ULL, 0xCC98B3CDCD411B3EULL, 0xB0F2249F49435930ULL
        }
    },
    {
        {
            0xD838EC9C50459730ULL, 0x908D06B52C0F9066ULL, 0xF763D805D4B7DD5CULL, 0x2CFC978DD9147A6EULL, 
            0xEDB6863C200A4EB8ULL, 0x4A99AE250A92F0DAULL, 0x0DEE5150BA1A090BULL, 0xBAFE12EDC6BD5A85ULL, 
            0x8883C510DB1ED685ULL, 0x37097B87D76AA11CULL, 0x37A1D84178186B3FULL, 0x1B9905530B7766F1ULL, 
            0xE09FC273E38F383EULL, 0x487D9A9D5F0F44ABULL, 0xB2B4B775650F4C80ULL, 0x1A2E617DCEC86D94ULL, 
            0x33437DB4EA7F66E0ULL, 0x30683D8226AF5456ULL, 0x61B7048BED19C15AULL, 0x450D1B256F10E3CEULL, 
            0xF3C677D746E16734ULL, 0xDEEBED5E7FF982CAULL, 0x9453DEB9064DA4E2ULL, 0x4B5BB5DB817C1B8FULL, 
            0x7D391BFE47677442ULL, 0xF39D0F0C7ED0A103ULL, 0xCEB4825E6A3FC9F7ULL, 0xE04DE25F65F42252ULL, 
            0x386F9D741C6F3CFEULL, 0x714566B813F5C974ULL, 0x8690CA20C36935DCULL, 0x2DBBD79ACFCEC23BULL
        },
        {
            0xB28B6F44D6E2C54BULL, 0x8681BBC3CD25674AULL, 0x107EAE0CDC0F9B21ULL, 0x37C161B6A38DC859ULL, 
            0xEF68D036EDAE821FULL, 0xA59F4C45251490C1ULL, 0x3F5EF431F971619CULL, 0x25E0B4E41D2804FEULL, 
            0x478F0AAB9E83C098ULL, 0xBCFE123A2660614EULL, 0xDE71852E223EBA25ULL, 0xC0808A9361A46787ULL, 
            0x7A6C427B761068DAULL, 0xFCD701BBE4F08E47ULL, 0xEF44277159D7F415ULL, 0x4E0E0259B67D547FULL, 
            0x5AA5196F9D03E6E9ULL, 0xEB3A6909404201E8ULL, 0x076EED6985B9BC9AULL, 0x6AD28BDBD2B756DDULL, 
            0x051BFB3FB72337F6ULL, 0x84342B9E4991F43EULL, 0xFDA9274BF6888AFDULL, 0x69EECE980F3F1688ULL, 
            0x643D957535656C84ULL, 0x48367A6C779FAE11ULL, 0xBC902A30C35228ABULL, 0x75891C549AA98AB8ULL, 
            0xE7A7E9C4452505B8ULL, 0x7DB5DF63C1184B2FULL, 0x8715EE4CCDFCEF1AULL, 0x3D6DA86169F5328DULL
        },
        {
            0xF093C10A9BF042CAULL, 0x3702EF3A2C4F5CBBULL, 0x52C4B86E7E31F8E3ULL, 0xBBF6F488B86BFA1DULL, 
            0xED983CD01444BB68ULL, 0x84512C3CDE427CA8ULL, 0xDBCEC63C9D00602BULL, 0xDD63368663E51BDFULL, 
            0x00A4A8844CA0118EULL, 0x50E4EA03607929B0ULL, 0xC768C45499D6B406ULL, 0xEF736F9642C91574ULL, 
            0x3040E64C839A19B2ULL, 0xF95B47FA8FB17C52ULL, 0xE32B315E1AF65560ULL, 0xE544AEDEFCCEEE9FULL, 
            0x0D6218C183854F23ULL, 0x3BD684BC34B66575ULL, 0x76A337F8257A2C9FULL, 0x164B8060AE055128ULL, 
            0xEB18219D43694BFAULL, 0x638ECF59180C26CDULL, 0xA4F83BC2D64A30ECULL, 0x47E970B1B2B252B4ULL, 
            0x60A5EC6E1B092F73ULL, 0xCC32335C06F53DBDULL, 0x626335B3FEE64836ULL, 0x3AE345659B0E7103ULL, 
            0x3FEFDC482D0A688CULL, 0xF543E6A4DF15BCAAULL, 0xB84AFAEC39757B01ULL, 0x261FFABDCB949FE3ULL
        },
        {
            0xFCE6D5923A27142CULL, 0x17E389BD9C2E439AULL, 0x5086323398BAC569ULL, 0x25A11E4CF27817FBULL, 
            0xF6B076BACC4105E9ULL, 0xB4DC124F50F7A76CULL, 0x075D9C57997E9C99ULL, 0xBED25B074D0CFC65ULL, 
            0xC5B22B40A5406804ULL, 0x38B3187EBA745B12ULL, 0xA9C0E55869D6817EULL, 0xF0CFBD40B20B28AAULL, 
            0xDF65425A0191E237ULL, 0xE472184B7A31BCB6ULL, 0x803D21EBE6D8F124ULL, 0x80441C861D783124ULL, 
            0x062D7EC3CDBB27E0ULL, 0x6722B980590D75EAULL, 0xE755C5EE07EA32AEULL, 0xEFEEAB6375CCAA1AULL, 
            0x752D1E137FBB15A9ULL, 0xAFEF6802CDDCFCB9ULL, 0x84730A7E5CA842E9ULL, 0x99247526E70C5EDFULL, 
            0x0925A0830D79A891ULL, 0x8B6B54AD87068345ULL, 0xEB3BA7465CB13F9AULL, 0x0787E504B8CD8CBEULL, 
            0x874C9B2D49EE4AF4ULL, 0x5669AD3F55F2AEBFULL, 0xC1661D8C6054A13AULL, 0x4D534DD9908115A2ULL
        },
        {
            0xE853F496DCE2CAA2ULL, 0x9F933FED938D6858ULL, 0x7C9FDC4E6E07CDD2ULL, 0x04D0719DC3F34EEFULL, 
            0x6D4594119158A109ULL, 0x71E5527E15644BAAULL, 0x054B4F777687E7EAULL, 0x8C3C49FB2E95E8F6ULL, 
            0x34B04D6A2EBDCF4BULL, 0x5942583A11189F5AULL, 0x46B605544C2DC03BULL, 0xF77634CCF024CFD3ULL, 
            0xE5BA7EF4E8CB5D58ULL, 0x3820523A12B9E3DEULL, 0x7CB7FF0E01A431D0ULL, 0x066F7F10302F6ADAULL, 
            0x392C8BD42A306258ULL, 0x78A2CB3B092E38D8ULL, 0x6CFE49879C33E614ULL, 0x82B1C8B27E2F2DDFULL, 
            0x0294E899213E434AULL, 0xCCF0D6B0D48FCCBEULL, 0x76D2852593576E26ULL, 0x8023558ED18D335AULL, 
            0xCB05417626793163ULL, 0x5AF9E59F3B8E718FULL, 0x3ED8A4F303B667C9ULL, 0x01CBA70A86A6220BULL, 
            0xBBEBDF3714A2C6AAULL, 0x21ACB6EB1D4ACFA6ULL, 0x002115596EE61B15ULL, 0x2122E3D09091DD09ULL
        },
        {
            0xE89C57432C1F27F4ULL, 0xBDA66038AE4E653DULL, 0x409E515864E6E1F4ULL, 0x46941803BFD8524CULL, 
            0x4589E1813C2321A5ULL, 0x15BDE5F224E6277BULL, 0xC9B844C4E5C1EAD9ULL, 0x6143D046C1F58685ULL, 
            0xFCB27E837035EEA5ULL, 0xCF71A1BE048A51CAULL, 0x8D7722F0C8D8A97DULL, 0x7A31F4E83DFB1DE4ULL, 
            0x707BBA3C1C819C75ULL, 0x80690605271EA678ULL, 0x5625E8A39CE7F90BULL, 0xCA1A745A3D865716ULL, 
            0xF74BD78359ACD8E1ULL, 0x36A3E0C118817285ULL, 0x784874B476AABD10ULL, 0x10F5368161D53BB3ULL, 
            0x4033AAE80225B24AULL, 0x779C742942C19AB3ULL, 0x004B0E8F02976EA2ULL, 0x77B022E425B96793ULL, 
            0x3C27062B635FE220ULL, 0xF8B469A430E8A5BDULL, 0x10952A26B0F8812FULL, 0x9F952A8FCA20C680ULL, 
            0x55A416B11C786CE6ULL, 0x595BC06CE35EA636ULL, 0x6A6A36FD023ECF9CULL, 0xE5E2CED425C5E562ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseCConstants = {
    0x7F0029301922BD7CULL,
    0x4853D500C26C89E7ULL,
    0xB2C71A72482B5B23ULL,
    0x7F0029301922BD7CULL,
    0x4853D500C26C89E7ULL,
    0xB2C71A72482B5B23ULL,
    0xFD69699440AD781FULL,
    0x81FD7F20953C43D0ULL,
    0x7F,
    0x1A,
    0xF7,
    0x4D,
    0xC3,
    0x2F,
    0x8C,
    0x37
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseDSalts = {
    {
        {
            0xC54E9448BA4A5672ULL, 0x3C3A346D362D6D0FULL, 0x6B683A2F7A24F319ULL, 0x0FEDEEFC60569542ULL, 
            0x25067F008AEAA91EULL, 0xC3DE0E51ADF9EBC5ULL, 0x295FE6CB9756C232ULL, 0x730AF76CD107082CULL, 
            0xB05D190ABEAD961BULL, 0xB8F06E726F510F71ULL, 0x1E97FFF3C3917756ULL, 0x3326999844D116FCULL, 
            0x9CADE5A03396589DULL, 0x9D90473F97F043FDULL, 0x5D48057D93E28277ULL, 0x7A54F56ABD413378ULL, 
            0x9C195AC6C7A36FD0ULL, 0xE82D33C0124D9D63ULL, 0xB9522AAC9D5598C0ULL, 0xC2C30D9563A04CF9ULL, 
            0x4A28809179ABA1A7ULL, 0x488CFFFEAA62EDADULL, 0x43CD0CF7749A82ECULL, 0xD194AB46D4DF2649ULL, 
            0xEADBCE588381EC4BULL, 0x03AB1D68B67E56DFULL, 0x0EC6454CAF77AD8AULL, 0x98557FFD159D565DULL, 
            0xD4F9D9D0351EB3EBULL, 0x741C5E538ED5EEEDULL, 0x9A2E5366AC70FA6DULL, 0xC432F355BCC9451BULL
        },
        {
            0x7E432594A19EDD4BULL, 0xDE81FCDD5B1D85BCULL, 0x86EBA8A97DB1260EULL, 0x68E3CBB5C6F83A99ULL, 
            0x2AFA5C28169AD0AFULL, 0xB0C5CAC78AE5D9E6ULL, 0x5B1BBE65BE7DA265ULL, 0x055516D2BD92460AULL, 
            0xA7C5A866C87427E2ULL, 0x56D2E89FAE0212D3ULL, 0x5C6655D8EC294492ULL, 0x9AA9FD0C15200A3DULL, 
            0x5D7847567CF6F37DULL, 0xE8BD38E3AFF8C460ULL, 0xDE866D0DE6999391ULL, 0xCF80E0ABCFF7EB32ULL, 
            0x9DCDF948EAB248EAULL, 0x2799F588F84A7FF5ULL, 0x79B42FD751D90104ULL, 0x90C656313FE7A4F3ULL, 
            0x8852ADC4D1C78BC5ULL, 0xF022572A66875984ULL, 0x6474918504747777ULL, 0xD1F626316D5D09E5ULL, 
            0x4CFE328B4043965DULL, 0xCBD9BCD6A818D489ULL, 0x05F0AD2A14C5AC50ULL, 0x23B9E390A326A05FULL, 
            0x80208782A22CEA2DULL, 0x1C250B7EAADFAFD0ULL, 0x591511B5BEE8B52DULL, 0xE2FF289174FD2412ULL
        },
        {
            0x11EB015A5EC295C8ULL, 0x0ADF93877EEA1159ULL, 0x66796F85797B8D22ULL, 0xD55DFE5E58B506DFULL, 
            0x735B889EF2BA2360ULL, 0xB88533013D9D979FULL, 0xA9D6BBFA3CC45035ULL, 0x0D178D675ED809CBULL, 
            0xEAA7F159DE853D7FULL, 0xDE8DA1C15343B4D7ULL, 0x94946822F144E541ULL, 0xD2ECE63F341FBCDFULL, 
            0x236BD9566E8D2A12ULL, 0xAACA8A06B8290D87ULL, 0x2E9CA2B80F02BC65ULL, 0xC71895C950EAB79CULL, 
            0xB05958CEBA3ABD22ULL, 0x7A51478932BE95E6ULL, 0xBF95CA0351F6591EULL, 0xF19AC6A0BF28A70CULL, 
            0xB735B4D55DE2E04DULL, 0xACFE0723D3120A23ULL, 0x807EF109CC2E21B6ULL, 0x335B9268D6E9CB70ULL, 
            0x353A4EE573C652D2ULL, 0x9A611D2A5E65371EULL, 0x47D9AB897BCE9C5BULL, 0xBE475543C9A690D7ULL, 
            0x751E1A0F5D82A2CDULL, 0x1F4493C50EA70A97ULL, 0x4D70CC08065F074DULL, 0x6053C10410FA6B1AULL
        },
        {
            0xD2FB372E39803702ULL, 0xE413BBA5C975381EULL, 0xB8CE127FD5707866ULL, 0xB1A35E9E252F3004ULL, 
            0xD4B3149F55CFBE98ULL, 0x72071D8DB16527D9ULL, 0x51E17A49DED27512ULL, 0xCA4756FC8735CD28ULL, 
            0x60FBE4E5BD5D6A2BULL, 0xECF6A1614345A01BULL, 0x11A211D314DD243DULL, 0x709766456F296D9DULL, 
            0xB30A43D2032E017DULL, 0x1F3A410682C5D3C4ULL, 0xF800D7869A36EB9CULL, 0xD5E770B62386775FULL, 
            0x7A1D4504CC99EFA7ULL, 0x691226B8B8961717ULL, 0xE245C9CC97F2B407ULL, 0x53EC2AFBDF25BE4CULL, 
            0x61C0DDC6C190E74BULL, 0x0996FFD5DA25019DULL, 0x7820F04070D36B35ULL, 0xEFFC01E31B5A782EULL, 
            0x98F814B17A18B120ULL, 0x7B723D4DDD58AB78ULL, 0x32F5F899E9183455ULL, 0xBE74E4AB004370D8ULL, 
            0xB9630A061E2107CAULL, 0xCF7E84A5BF59AB41ULL, 0x8F99F52402EEC5C6ULL, 0x0E31D6F1AE8B31FBULL
        },
        {
            0x483A73C72A4E8DB6ULL, 0xD22533EBCB543159ULL, 0xA81F5E1F716CB917ULL, 0xF4704B870D98C7CDULL, 
            0xDC6F965195296B3AULL, 0x99AC5E9CD12FF101ULL, 0x2703EBC0098AD055ULL, 0x93D017E4CE46FBD9ULL, 
            0xF7EC0E646FB5495AULL, 0x15EBC3C0013C259CULL, 0xE52259E359CC8925ULL, 0x5C5679F525DF58C8ULL, 
            0x5AE3C0D12F1C1DDFULL, 0xBD67777DF975DC15ULL, 0x7CC8D3C13191B043ULL, 0x0E4CAC2F9FCF3320ULL, 
            0x754ABDE60B014DB8ULL, 0x5F84A3B632B2CBA9ULL, 0xC1CDC0D9D689C987ULL, 0xA038C6A847725E04ULL, 
            0x8186488A4CF001A5ULL, 0x7B062737EB969BF1ULL, 0x7F7026DA601A1A97ULL, 0xDE84372077E6EE11ULL, 
            0x455C16C4CC272D66ULL, 0x73952967DDBCF376ULL, 0xEF68B2BB95BA8D99ULL, 0x29DE993601872AE7ULL, 
            0x4317619CD178641EULL, 0xB0137451FE794AAAULL, 0x42BEDF0347BF3445ULL, 0xD4143E48F8FB134FULL
        },
        {
            0x3C41280E409DC00DULL, 0xB63C14EBF3F58F03ULL, 0x989C2D7F760F978FULL, 0xED663286F19D2F7EULL, 
            0xE9AEAB4143B4EE0AULL, 0x93725A498F5F6F90ULL, 0xFF5E299632E8FA38ULL, 0x561BF5C761231319ULL, 
            0x197B00F8774511CEULL, 0xFF2E985BD6851336ULL, 0x1BFD8FF820429FDDULL, 0xE979DEA02974C17CULL, 
            0x03A547A5A1DCA6C1ULL, 0xF51DB3D21FB24BA3ULL, 0x8EB17EAB9629BD11ULL, 0xF3A48AF8A92A43AFULL, 
            0xD4B745205782BABAULL, 0x8CE68EB879AFE452ULL, 0xB297F442381E1D0AULL, 0xF8085EB8130BF0D2ULL, 
            0xBB7E47DCE613D6FAULL, 0x394F898995C09F8DULL, 0x3AA4513F503CC806ULL, 0x33A7FB5B2DE7D0D3ULL, 
            0xA46457FFDA7C27B2ULL, 0xEA4D90EE331C9326ULL, 0x0BF8CB940FA2C522ULL, 0x7B4ABC1F803B7E15ULL, 
            0xAFF41303ECD39CCBULL, 0x1FBBC5EBB0731C55ULL, 0x3D0EC1CB288171A1ULL, 0xB63063F910E92FE1ULL
        }
    },
    {
        {
            0xC2931F0161F35E34ULL, 0xE6B16108ED6D7698ULL, 0xA979401CEAA5767CULL, 0x59AF68809E0EE4C3ULL, 
            0xDEC1BDFC669714E6ULL, 0x0801FE59D3958C9BULL, 0x7B6CCC22BB4A7887ULL, 0x20F1B754DE5F2107ULL, 
            0x87D259D568E43730ULL, 0x62B9839D142BB412ULL, 0xC43E7D37BC78C576ULL, 0x27D1D3AFEB61022AULL, 
            0x162146D1AE7E4EEFULL, 0xE6D65F60765C456DULL, 0x607231ECFC8CE438ULL, 0x6F0819BE3F7AD085ULL, 
            0x8E9F038FA5C2C55AULL, 0xD7D2F2661CF95CF7ULL, 0x7B43147EC397A607ULL, 0x27AAC60C88D5D4AAULL, 
            0x8659540077C804C4ULL, 0x87D698BC4DB788EFULL, 0x5623868EABEB449CULL, 0xF02F789E6041944EULL, 
            0x2E89B595E98C9CF2ULL, 0xB7C48E0E8AEC69FCULL, 0x62BBAC70200E4C62ULL, 0x72EA979984F4D876ULL, 
            0xEA7A6F2F640CD1B6ULL, 0x5C85B2B17B00BDE8ULL, 0xC30579F7AB7D149AULL, 0xDDE058519E2CFBCFULL
        },
        {
            0x22D05628FE987780ULL, 0x2957DBDB5BF9D17DULL, 0xA0BCADE54745CF24ULL, 0x923906DDB8FCE427ULL, 
            0x55FC867C16FBB036ULL, 0x9C8CCA137097B5CEULL, 0xB52CC769A94E4A91ULL, 0x08C90453BC415384ULL, 
            0x8B18FF2800C1CE05ULL, 0x5FAC57625BCA4EB3ULL, 0x95F26704FBBBFDC3ULL, 0x67D3A3AD8D618B33ULL, 
            0x74F5D9DF35A8E365ULL, 0x8FBD32BE5A952675ULL, 0x5C791685870DEE27ULL, 0x12A22445D00D35DEULL, 
            0x80389C8FD77D00FAULL, 0x004B13337844C4F3ULL, 0xE2A41C9C804905E6ULL, 0xC2A10B31056C64CCULL, 
            0x03571621D658D9CFULL, 0x9FD5F303C137635AULL, 0x884732C6DDB1CEF3ULL, 0x8CE4CFF2908AEE95ULL, 
            0xC7493A8F4DE46219ULL, 0x6C60DDF21B6AAF5EULL, 0x51239133CBF9843FULL, 0xA5A038D4BBC86677ULL, 
            0x9127686FD805A4D9ULL, 0x0DE52A39126FDD1CULL, 0x00817F5CEEF864BAULL, 0x527C2BBB27973952ULL
        },
        {
            0x15ED41DB3458776AULL, 0xCEB21BD941E7929EULL, 0x26929625460986F7ULL, 0x74AEF2F070E45DD3ULL, 
            0x022E39D284B92D09ULL, 0xFDBB911AFB8DA2C6ULL, 0xB34E90E218EF7678ULL, 0x5D8A1C389E53746CULL, 
            0x4377632DE4AE0B79ULL, 0x4CEFD8B2D817A225ULL, 0x470AD817D88EEA15ULL, 0x0D5CE01879FF0DE9ULL, 
            0xB09CA79E336FB891ULL, 0x2036201BD1C5CF19ULL, 0x8A03279206218002ULL, 0x3C97D6B6C6E934E7ULL, 
            0x473FFDD8A237D664ULL, 0xF5E60193C0DE0568ULL, 0x7790D18591EF4B1EULL, 0x07B4FFD76843F306ULL, 
            0x53067A9705936951ULL, 0x2779335D2E6A254AULL, 0x76FAC43A0DF8E23CULL, 0x952861ACE93D8E4BULL, 
            0x8C278CA2D302ED9AULL, 0x0902A8188E2D6AF1ULL, 0x38342FB19B24A0E9ULL, 0x5C0CFE18F285B35EULL, 
            0xDD709544B41B62D5ULL, 0x939EABB0BE1996D4ULL, 0xDC5AFF870969F376ULL, 0x67202EDDC3336E57ULL
        },
        {
            0xF6341195C39DFA77ULL, 0xBB65D2DCF639AA10ULL, 0x9CEEDEC43752193DULL, 0xF20287AC70C1FA99ULL, 
            0x0DE4F5CF8D06117CULL, 0xED69626D9FAF51ACULL, 0x7057F3C0EFC18C69ULL, 0x2272D641E38C135DULL, 
            0x10B84A3D99CCA697ULL, 0xE447A2632A70F8A6ULL, 0x1D495D43D561003CULL, 0x7FA594AEF596F213ULL, 
            0x626672E0DF784A5AULL, 0xB5654137B629AFFEULL, 0x0A4BB2BD193E7DC0ULL, 0x96A7E1912A7A2AA8ULL, 
            0x0C2853CA6C2AA547ULL, 0x9ACA4CBF9617AD93ULL, 0x9FB05ECD8D0DC26BULL, 0xC4474EB98D6A647FULL, 
            0xF94B2E808D35076AULL, 0xF650AC05DB5E8C52ULL, 0x17C13F0C1E27BE4EULL, 0x567FD66EF929B218ULL, 
            0xFCCF28F0EF11AB02ULL, 0x929C5447C4B8F042ULL, 0x16E24FE61BF091E6ULL, 0xB4EEDBB2F7393248ULL, 
            0x2741D773E421D113ULL, 0x94BD3BC4EE57A6A9ULL, 0xB2A1A71960F8FE99ULL, 0xECED54653073E0D5ULL
        },
        {
            0x219806552C77BEB1ULL, 0xBB2246DC7B658B04ULL, 0xC76786BF34182DD3ULL, 0x02C094DDA788DFB3ULL, 
            0x2F2B66A99E67EE54ULL, 0x97E248ABE1C40F3DULL, 0x52B2FF17A065B579ULL, 0x703ABDF529102689ULL, 
            0x25CEBCC4EC5CCEBAULL, 0x83AD6C8DB9A0AFD8ULL, 0xBEBF45FB1A5C80F1ULL, 0xDE64DF8E4710E666ULL, 
            0x5BC3A73232B1BDD3ULL, 0x5DF9C825114BFD53ULL, 0x4F9E086C4E47DC17ULL, 0x112525528DFBBD25ULL, 
            0xD09706AD91729D27ULL, 0x2983F4842C12E669ULL, 0xD4538517FA808DB2ULL, 0x97E36304CDF5AE46ULL, 
            0x90BA3145C9C4D32BULL, 0xC09131F0D841F591ULL, 0x727F58B611650E85ULL, 0x960EA31121DDA2A2ULL, 
            0xD6FD0B5470312FDFULL, 0x51A5F52878777874ULL, 0x49B1EE15E3C57384ULL, 0x9BCAD90211A5DC24ULL, 
            0x43F99E8A781CAA61ULL, 0x33EDF53D0A63EA83ULL, 0x502117E3F5EC2C0AULL, 0x77688FF9A218151FULL
        },
        {
            0x322E0F411A2BE812ULL, 0xA3C4A180CED7C87DULL, 0x0BE8CA0FE473AAD1ULL, 0x4A4EC5EA13B92BE1ULL, 
            0xB7AAE4004066FBF5ULL, 0x49369CCF6F569506ULL, 0xA5F6A15C192756A4ULL, 0xDFA325A954787D93ULL, 
            0x6E874069530F0466ULL, 0x4BF642C36312C5F5ULL, 0xCAD2ED0E85010431ULL, 0xCB396100C95A7827ULL, 
            0xCDEBFE0407B26E92ULL, 0x7BA7FDA01C42E66CULL, 0x1A79BE3C88F9DC97ULL, 0xF98CF0E19675D041ULL, 
            0x84EF3B0BD89C45AEULL, 0xF55DCA6F1CC42533ULL, 0x21929DFF7876A02CULL, 0x68F0250E85F5E2F8ULL, 
            0x588727BABAE9D7BFULL, 0x14BFD6297E527216ULL, 0x8EF12B6653BB1B74ULL, 0x102A6FB22DEDEBB2ULL, 
            0xBA96D4F851ABD4B9ULL, 0xE144DCD4E8820E1DULL, 0xE488708E4BCB9447ULL, 0x44CDB4196F983F41ULL, 
            0x0785F5039633C010ULL, 0xA06274BD67453EF6ULL, 0x4A331C8974C1D065ULL, 0xF5E085919784707AULL
        }
    },
    {
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
            0x7506C35C08A2923AULL, 0x866EDE1BD1BAF74CULL, 0xF82F00FE93EC4A20ULL, 0xC51C800E9DDC7A01ULL, 
            0x87C5DCF17C3119C3ULL, 0x9B4E614DC184A53CULL, 0xE7B5EC4240EB003AULL, 0xF6D08089B3B46D4CULL, 
            0xC9EFCA41B05E5D18ULL, 0x37209B35E92B7014ULL, 0x0AD4CEA804701061ULL, 0x11A140A2D1EAD357ULL, 
            0xF613564E68987289ULL, 0x32A1A7EC12CCEA50ULL, 0x56CA6CD4C7678511ULL, 0xC3796C32AC4CBBE9ULL, 
            0x9AA351188A3759D2ULL, 0x3B38192F8C976F59ULL, 0xAC3388B7B83F84D8ULL, 0x7AF5D38905A8136DULL, 
            0x2AD994932B397F5AULL, 0x07D689F75C7BAFF7ULL, 0x0DD46C0AEE5609F8ULL, 0x0793D47E87FD64D0ULL, 
            0xB9B38C4A0569C669ULL, 0x0EBA51498BB46D3BULL, 0x0B82094E916867E5ULL, 0xF584B34278404BFAULL, 
            0x86E6510E8ABDEFA4ULL, 0xE329323526150086ULL, 0xA01FC9F87C109B48ULL, 0x07F4C0F8041328DAULL
        },
        {
            0x640D9638A4C48146ULL, 0x3C97C9113577D4B5ULL, 0x7549107FCEABFD86ULL, 0x23CB50FB47BBC98AULL, 
            0x904A69C42E2ACA0BULL, 0x68F1A468AC8CECF7ULL, 0xEF535F8C48D8C8F2ULL, 0x9BB2176C0084D5A6ULL, 
            0x3305229849BA87EEULL, 0x8174B54C82B46B21ULL, 0x017BA2A7F3AF01ADULL, 0x6C3193E05EB60162ULL, 
            0x080E6E60308B8EF1ULL, 0x74A739F82A4C4C48ULL, 0xDE6FA48F70197918ULL, 0x14BA2E6DE5AD7968ULL, 
            0x09A88D3E1F02986AULL, 0xA662533B7EB10E33ULL, 0x4F2BCA8178B21E3FULL, 0xE965A35E6FB60A44ULL, 
            0x5978B2E0A039BDDAULL, 0xFF0870116115BDC4ULL, 0x2CC05A00C0E26F72ULL, 0x057B0CB5DB9633F1ULL, 
            0x9EB71EA68EA0ABCAULL, 0x1BB2032434E61E9CULL, 0x2DE6361670A92525ULL, 0x823323EB24A2C0E8ULL, 
            0x24B29793805657B0ULL, 0xD1A457EAE73C8024ULL, 0x5866B494D9D923E1ULL, 0xCC63E25F56951D3CULL
        },
        {
            0x85B8060FB2E92703ULL, 0x2C05B83CBC5E7388ULL, 0xE0096E37EC5F8906ULL, 0x0E92229D4B433A0CULL, 
            0xA86872663A70C579ULL, 0x1D3ABA0487CF598CULL, 0xB4F84BD6AC8A76D1ULL, 0x5D06AE867FE12445ULL, 
            0xFF20042C4C103E02ULL, 0xBEE9314CF5E73A4BULL, 0x6DB53C7D39ACE722ULL, 0xDF7AD58F5927D677ULL, 
            0x7ECF0B3CF1F489A9ULL, 0x34B33623E847F1E7ULL, 0x2DCCBB2913C5339DULL, 0x620C59B9DB2EF769ULL, 
            0xD9C99950566FB88EULL, 0x1BF8D18BBCC5FBA5ULL, 0xFCB4D83EA48BB002ULL, 0x473D9F157884CD02ULL, 
            0xD01495DF7BED3C89ULL, 0x721C904FB6894696ULL, 0x574029096B5BEE12ULL, 0x207E98ACCFA21EA9ULL, 
            0x6BE51FED0406164DULL, 0x57803856CDE7004AULL, 0x3CAFFAB3E569ADA5ULL, 0x7B5EF4FD0514EF6DULL, 
            0x32665079D92A077AULL, 0x0BE1A2F6DD3A2EEFULL, 0xAE5D1101C293D9FFULL, 0x49744ED9126DC782ULL
        },
        {
            0x0E5406925999F18FULL, 0xDE4A61CCECB66D37ULL, 0xAEFA5EFE2C916C04ULL, 0x6BB08B45F799496EULL, 
            0x3203F86E325312FDULL, 0x80619AEC1B44128AULL, 0x2A8376EECCD20D91ULL, 0x24B7C109D3FCC3FBULL, 
            0x18C8E635751E09F4ULL, 0x174FC2AF88D5F505ULL, 0xB50182A0E74CEF3CULL, 0xFEE2D7481AAF8BDBULL, 
            0x12D65ABDBA340CC3ULL, 0x3C084195DE15F9CEULL, 0x4E1A32CA8A2256D0ULL, 0x4267B9AB5BC46B21ULL, 
            0x68183AD547148FE2ULL, 0x74BFEEAAC1C5614FULL, 0x614B535C4DF22DCDULL, 0x67B429C61FD5D70DULL, 
            0xE1224CAD48F9A2F4ULL, 0xDF095A971F9A2721ULL, 0xF7C00FBC5A0063F5ULL, 0x4DA1503D762BA427ULL, 
            0x7A6A71E43A1279E6ULL, 0x896633C79DED0B2CULL, 0x99F72D21718E7378ULL, 0x4E31ED13EFF9FDA1ULL, 
            0x98CFC659E4817A82ULL, 0xAC57B5ACFD948812ULL, 0x3DAE5DE1A7789CDCULL, 0x94EFBE8978368036ULL
        },
        {
            0x670CD4A3B2149466ULL, 0x1CC9DAC6ACF4528AULL, 0x27148D99BE0A4D09ULL, 0xBEEE1E49DFABE1D4ULL, 
            0xE67BAF1368B78B5CULL, 0x95C11C63F95C9F36ULL, 0xD3962E09A868C24CULL, 0x27190A5BE242070DULL, 
            0x3D95A320B0A6FC9BULL, 0xACEA0AC4E9A1029AULL, 0x41BEE15C88DB950AULL, 0x162B8C6060EDE519ULL, 
            0xE551C151562F01EAULL, 0xCB864E74CD9BF505ULL, 0xDE7A7F425952F4FBULL, 0x789ED9DC53F1CD96ULL, 
            0x880A57B0EEBF37AAULL, 0x2AD0F1266C7D9096ULL, 0x23674AA9225C1E08ULL, 0x712EA89FFCF46459ULL, 
            0x3F3F4F5CC1AC76B0ULL, 0xDD1A87E88543F18FULL, 0x221CD66D866A133AULL, 0xFE9AB17182A60D88ULL, 
            0xBBE2CB7D24DD083FULL, 0x92899E1585F6F654ULL, 0x413BFC3AC5AD7A2CULL, 0x06BDACB1FC7CB5A4ULL, 
            0x543DCEF04E072AFBULL, 0xFFED1110E7114A96ULL, 0xF45BA633C576D7E5ULL, 0x426E8E55392DC42FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseDConstants = {
    0xC39E7993A6C846AFULL,
    0x01E3BE6DA0BEE518ULL,
    0xD41E291C448AFAB7ULL,
    0xC39E7993A6C846AFULL,
    0x01E3BE6DA0BEE518ULL,
    0xD41E291C448AFAB7ULL,
    0x8B01D62B8A5FC226ULL,
    0xCDD7DAB30AD1EF48ULL,
    0xC2,
    0xF5,
    0x55,
    0xD9,
    0x78,
    0x4D,
    0xCA,
    0x93
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseESalts = {
    {
        {
            0xDF57250AE48D6836ULL, 0x49B0CEBCE4594F21ULL, 0x5ED182931288F1A7ULL, 0xD55DF0794146902FULL, 
            0xA8A9F7D901293D94ULL, 0xC36D19AF1A4B583AULL, 0xC6E99750BECF31FDULL, 0xBE746732B879B8ADULL, 
            0x7CEDED429EDDAFBBULL, 0x6BACF140F5607A99ULL, 0x41C826B7F2F03FFBULL, 0x1253DAEABED8EEB2ULL, 
            0xE09EB755C08E5697ULL, 0x16A8D6B4A4049568ULL, 0x891685C15F07F2CCULL, 0xDC682F752AA8F349ULL, 
            0x8077075542172FF9ULL, 0x3D4DE3CDD821CD7AULL, 0xCE4BDE4F6E0A4169ULL, 0xFBF62928BA2FE4C3ULL, 
            0xFF1BA0B5B7A00C52ULL, 0x67389473336D95F7ULL, 0x364D552650D8FB40ULL, 0x62282E45A10C8367ULL, 
            0xCF96D3D4CA995552ULL, 0x6524496D4AD1CD9CULL, 0x92E46518272E5209ULL, 0x5DEC1B47871BE71DULL, 
            0x5F125EDDCD0D0C9BULL, 0x7443DB6E980E41A7ULL, 0x05C72908E82130E6ULL, 0x1BEA736D75DFC581ULL
        },
        {
            0x92083FC015B2309BULL, 0x55D4FD60B8CCE3C9ULL, 0xAC8D4276634B4EACULL, 0x8241DC0DA2C00BD5ULL, 
            0xE6D6289BF5DAA4D3ULL, 0xAA0031947C545A67ULL, 0x487E631568A469E4ULL, 0x63DE3B23FA5350D2ULL, 
            0x222B3A737141B980ULL, 0xDAD1A2213D0F2588ULL, 0xC8E21193195C7B14ULL, 0xE9F53FAAEE47E7F8ULL, 
            0xE7BB963A81D67CD3ULL, 0x2B1EDBF1A3434DE9ULL, 0xB5A6E4D6195C9F60ULL, 0xB1EAA85EA5CFCC21ULL, 
            0x53560447C080B2ABULL, 0x56A5495C2DF6F4F1ULL, 0x3F2A07E86B3A45C0ULL, 0x29D3B672D2E51117ULL, 
            0x5BAD5F8923CE82CCULL, 0x19B5DAE581962955ULL, 0xBB1E5B312226765FULL, 0xA268DA14B5EC1396ULL, 
            0x6D3E4EBBBFB42AFEULL, 0x27E0331201B972EDULL, 0x60AB3E44E23119E4ULL, 0x137D46BE243F35C6ULL, 
            0xB52BFF48723C2263ULL, 0x59C2310826E739DAULL, 0xFBF43FC5DE538A13ULL, 0x226E761CE591FD01ULL
        },
        {
            0x7538FCB3EA9D0581ULL, 0x0AD906DCCF89E5D6ULL, 0x2213F051EE741F8AULL, 0xA7B5966919B71DAEULL, 
            0x894E0B3F789710A6ULL, 0x58BD0D9EF8379002ULL, 0x510C2A9A2A45DFD0ULL, 0x210934495071DC69ULL, 
            0x7B23140080F5BDDDULL, 0x68E7C862881C25DEULL, 0x25BD7244143953B5ULL, 0xFA934EE0698FD417ULL, 
            0x07B1587AA2DE86E8ULL, 0x8BF1A65F453DC55DULL, 0x3122D7C6DC661EFBULL, 0x6C7A0BF58E0DAC81ULL, 
            0xDB1D7BB1D52A609DULL, 0xDBB6B2E48568FB56ULL, 0xF9ECB363FE6FAFEBULL, 0xE43D2D9AA83663B1ULL, 
            0x252620E1822AB287ULL, 0x2150A01009AF3090ULL, 0x8733C901A165B828ULL, 0x33D65A6E1F769FE0ULL, 
            0x75A06F095F184A95ULL, 0x12F16EAE91394713ULL, 0xEB198117A40255CFULL, 0x32F9C93293FC47EBULL, 
            0x1D6A4DC26F46C1A5ULL, 0xC5F3B64E5D83EE59ULL, 0xB8F56250DD3DF233ULL, 0x0C7C5F5C32522D13ULL
        },
        {
            0x13366C16157B4D60ULL, 0x1F649E188D30CCF0ULL, 0x8C1EB22194ACF074ULL, 0x7603142741A630D5ULL, 
            0xE7B8136B13C47EFAULL, 0xA4E5662FB35A5B48ULL, 0x4753BAF2D299E2B7ULL, 0x856AA7A0F2086FC2ULL, 
            0x522C1E7688B96409ULL, 0xCCB1EE3C4E60E53EULL, 0x59AEF443BC8EC459ULL, 0x7E6F90DB949199EFULL, 
            0xAFF5FA581A2C698BULL, 0x35079D8573C463E7ULL, 0xD896D0E9E9BCDC6BULL, 0x708C29CFDABF60E0ULL, 
            0x5B75A5F79DD21496ULL, 0xDC674F577D3C9C75ULL, 0x489916278AE45B7FULL, 0x643F5122811303E4ULL, 
            0x7CFDEFD1668F5122ULL, 0x6D77CDE1DBE08EE5ULL, 0x56BF45320D732899ULL, 0x577E7ADFE4C006A7ULL, 
            0x38B187F9D74BBF2EULL, 0x2C702542C877C03AULL, 0xC32F4B0FAE5F994DULL, 0x46399133A17777B1ULL, 
            0x60B434D70645C494ULL, 0xE34418171661A814ULL, 0x00FA1ECFB2C9CF38ULL, 0xF6E30D8293705D10ULL
        },
        {
            0x6665D70E48DACAF0ULL, 0x0D4BBCDC64A55FB1ULL, 0x80AA76B414A7DD49ULL, 0xF649D075B787D829ULL, 
            0xDC123CB9A79A85DEULL, 0x34582C7AD5920DDCULL, 0x34C183E4A2CE42BDULL, 0x51048ED8DA0F4D22ULL, 
            0x518C7466DE8912AAULL, 0x59F5D93ABD210E9FULL, 0xC87F88B13F8E2A5EULL, 0xE8D2853D400CE654ULL, 
            0xE65DAB4E39751E4AULL, 0xAC2A7FC87F734C3AULL, 0x6E9317DA176E033DULL, 0xCFD335D21AB29907ULL, 
            0xF7ACCC2BF43B5A9DULL, 0xFF90A60CF4D63E65ULL, 0x40F513280E394C81ULL, 0x0AAFE0ECFDC3E5F8ULL, 
            0x9C11842BC97C30CFULL, 0x874A086C151480D5ULL, 0xF3B168CDE20FD1C0ULL, 0x4FA25C6B88AC8695ULL, 
            0x9B4E769A5BA26CE9ULL, 0x31276EB847DA73D2ULL, 0xF0CC80420D22D504ULL, 0xE0B507B1A2F927C6ULL, 
            0x7AA66C9092ED49B6ULL, 0x7A243B3EF81A9CF5ULL, 0xD96FEDB5D7EE71EFULL, 0x9D221DC31BE36A02ULL
        },
        {
            0xECD629E59DB5B10FULL, 0xC692815FE1899A75ULL, 0xA8A72EAE4EE99ADAULL, 0x348C27531020E27DULL, 
            0x7252182C1DD9B153ULL, 0x9E2D529255B22B0AULL, 0x1D1764301FAC0F1BULL, 0x8C157C51D2BD7989ULL, 
            0xEE2B88D8D3F22FF5ULL, 0xD2E5DB8BC6C314D9ULL, 0xDC432F7868E31538ULL, 0x29E98F9110C60868ULL, 
            0xBDE0DE31B80F0A61ULL, 0x3920A7E38D6BF511ULL, 0xCFD6F3781D93A262ULL, 0x45FF41557A8F9800ULL, 
            0x08E3E398E13F1D6EULL, 0xF71E73D66A141792ULL, 0x22CAE63C0A16090FULL, 0xF814080D1A7130C5ULL, 
            0x48C3C0456D5B6ECEULL, 0x4EA060E12ECE3285ULL, 0xB8ACD1365FE292DBULL, 0xCAAE1207C3C150BCULL, 
            0x023C866B663BA18BULL, 0x9470A30C6DBF5849ULL, 0xE2503F8FCE7C8459ULL, 0x72041694D7C537AEULL, 
            0x93B40401E5B0FE5BULL, 0x0303E69013230302ULL, 0xE61F7431C210C393ULL, 0x96C04105B5D8741EULL
        }
    },
    {
        {
            0x17B767F6463A1E86ULL, 0xE8517E81727BFCA8ULL, 0x1777D71A5A78C5B1ULL, 0xAFB03A94395BCDF8ULL, 
            0x7ABCF8D9420A186AULL, 0xBA4A22B1E77EA2EBULL, 0xC036571CFC8AE1B6ULL, 0xB3E15F5EBADB7113ULL, 
            0x273DA0DF744CE405ULL, 0xE0464355C94A4A5BULL, 0x9CF6561568383E2EULL, 0x5E21D52DA1B4D531ULL, 
            0x9687619F83C1202EULL, 0xBBFE349F9341BBDCULL, 0xC7688A1C100A1BDBULL, 0xBE9859AB4A385B5BULL, 
            0x983F74EDEE3D4065ULL, 0xA286261132D3AC76ULL, 0x0FD4E131265DC1E7ULL, 0x006F44F201F1E78FULL, 
            0xED9C5624F85A2062ULL, 0xBB3BFD9688B95B23ULL, 0x9C7FA9FEE8631528ULL, 0x29D4F525F47AF2C5ULL, 
            0x514E52917562B3EDULL, 0x27C15EAEA5E65F40ULL, 0xB73B6C7A5B62B58AULL, 0x0B0F1DAB1D0A460BULL, 
            0x43657898F7FD0995ULL, 0x4A456AECAE570A47ULL, 0x2C4BF75708DE91B0ULL, 0xC2CE9C74AECCC19FULL
        },
        {
            0x5B286068CDCDED6AULL, 0x807C36E0AAC64928ULL, 0x7352A4AA470C9F43ULL, 0x1A487C8E78DC663CULL, 
            0xA740DBCF798D4F61ULL, 0xF8C9C7F6ED64E59AULL, 0x5527A87A01E8A90EULL, 0xE98A751DC771E340ULL, 
            0xC68106E9979DF650ULL, 0x8CC115B928947224ULL, 0x505263D6BEB82635ULL, 0xEA44FF6A40766487ULL, 
            0xD4F4C54B50A1014AULL, 0x6BE73B1953EC87E6ULL, 0x6CD82CC982A34157ULL, 0x6814F01479045BDEULL, 
            0xEF281CB21DC01B6AULL, 0xC3A8D5C41182DD6CULL, 0x1ED77832C97C6D80ULL, 0x0187BA4D13DC0397ULL, 
            0xFC7C7255545274A0ULL, 0x62EE84B2831D679AULL, 0xE1EFD0D6DFDA97D7ULL, 0xCE78770788D35107ULL, 
            0x7CC1B6AD2B5C2FCFULL, 0x33FFD55E6C35EA29ULL, 0xBFDEC3381F2377EEULL, 0xF9B55E9BB7DD7528ULL, 
            0xDF8293E258128086ULL, 0x9E33885DD157CB86ULL, 0xC93E0986C27078A7ULL, 0xF5707D8F77DCB040ULL
        },
        {
            0xFE9492B01D95EFACULL, 0xF17D2FF9D543928EULL, 0xE2D8A26B83A42E64ULL, 0x86C50DC97D11DACDULL, 
            0x0E7A8B03FB477585ULL, 0x2A7D08D4026AC432ULL, 0xEB463A101E67299CULL, 0x53ABBCB36B048C22ULL, 
            0x0143673C67992D96ULL, 0x5A314543B77B4D4DULL, 0x2BBD5467D798FDEAULL, 0x9EAC6EF974C02856ULL, 
            0x7E06ACC82E4372A9ULL, 0xF9DDEAE822419F20ULL, 0x35C19EA835AC5562ULL, 0xCA436900C4CB8DA1ULL, 
            0xFF65239E65BDF5CBULL, 0x67BB32BC7209E7DFULL, 0x09DF46BDFC0D3606ULL, 0xC14F301D83C9FFE1ULL, 
            0xC1814FE7D79DCC1FULL, 0x31F350B200A4338FULL, 0x316DB042AB7BD769ULL, 0x1F678B36E448912BULL, 
            0x555F90C52834F2C7ULL, 0xF5C05A0CA313FD80ULL, 0x9FC619940DF5B087ULL, 0x36E62B569B41EC48ULL, 
            0x47779A724BFBF64AULL, 0x15AC3C034635B23FULL, 0x30955B9B175CAD66ULL, 0xB06C66D0FF8D35A4ULL
        },
        {
            0xFBB4DCF9D32C7E68ULL, 0x195774FC7DB28A48ULL, 0x72410D5519B8D4D3ULL, 0x7F7526769826B627ULL, 
            0xBD94ECE31893FA6AULL, 0x2412855813DDA2C6ULL, 0x5C83A0F517CAC010ULL, 0xDB9B7282E8B29070ULL, 
            0xBE64F6506E56F3AFULL, 0xBBB128F111B63FEAULL, 0x8B24085F31AC8583ULL, 0x3292B60AE691B4B3ULL, 
            0x533C424FE7620284ULL, 0xF81F48956558062DULL, 0xA2A6D3A22B967939ULL, 0xF152EF17C4CD8D7CULL, 
            0xCF6AEFBA55AE697DULL, 0xBBD69014C470F076ULL, 0xFC410EF6E2D79843ULL, 0x3D6DF4102C418511ULL, 
            0x621D123DB6BDD9F3ULL, 0x4567406E598C81B9ULL, 0xBC63C422E7847574ULL, 0xD8259EA786DE23B3ULL, 
            0x45C2F40590DF0612ULL, 0x052D69DC8D5B0A09ULL, 0xB8D11F0055C1A216ULL, 0x77D484A857BE9391ULL, 
            0x00B7733AF9652934ULL, 0xD895A085EAB63E1AULL, 0xC5EDBBC2CED389F6ULL, 0xC14511727D97ABB8ULL
        },
        {
            0xF4B381D0895F2297ULL, 0xBCBCD9A15D0202E3ULL, 0x24E079F7A83B75FEULL, 0xE03300F1D1327D11ULL, 
            0xDFC33E0485484941ULL, 0xB0AA8A7BA3DB118CULL, 0x8995CA45CC5473E9ULL, 0x437C194830451208ULL, 
            0xC56CEEB874F9A8D3ULL, 0xE340C4ED8368CB7FULL, 0x8D591E6C1305C13AULL, 0xB73D6A634E57E939ULL, 
            0xCEB6F48C7DC93D7FULL, 0x7846B3026117D197ULL, 0xD5173DAF63B77289ULL, 0xAFE9173BBAFDA5C6ULL, 
            0x2306EE40186D24B4ULL, 0x7C5E5293EFCEE8CEULL, 0x752F1AD1540AC70AULL, 0x5AA5B98843593682ULL, 
            0x3D5FA0CA949A32E3ULL, 0xC18ED6092CD884C7ULL, 0x0231ACF624AB45BFULL, 0x5364FFE9817355C0ULL, 
            0xF18A0B1EF0183B81ULL, 0x9E580CA265709954ULL, 0xE6F7C71F10AAD465ULL, 0x40469D67B59F7B60ULL, 
            0x81875FDEF629CF62ULL, 0x180942D6A6F0AA53ULL, 0x611F13246E3A6238ULL, 0x9E6B2A84793B848AULL
        },
        {
            0x96787F44DEA4B445ULL, 0xB2313B66F89D4AACULL, 0x69D0242BE56BE942ULL, 0x3FEA96F2720E55D5ULL, 
            0x45767A2E613DC100ULL, 0x93245A43BAEAE8AAULL, 0x61F8E1A90A7AF477ULL, 0x3B1A3736B1D18C93ULL, 
            0x68FA7F8B7CAB0D52ULL, 0xCFA8EBC0CB12678DULL, 0xF374FA5F95EAC9A2ULL, 0x899DA1A9944928D2ULL, 
            0xD148873E0FC8998CULL, 0x58DC8A93B09C2245ULL, 0x7EA987B9D4CD18F5ULL, 0xD835021A881E4498ULL, 
            0x5A9C15F5BAC24AC4ULL, 0x97268DB66B55E64FULL, 0x8044126DE4253001ULL, 0x5607BD2E009E34DBULL, 
            0x57232FD93734BC8BULL, 0xA1B8AC2ACD49C6DCULL, 0x8E1648499259D359ULL, 0x0362519AC00550EBULL, 
            0xE5E4B3E641B9D416ULL, 0x0539C18D50E8EA0AULL, 0x2B0A7C354496B2F6ULL, 0x639E25EB585B6FAFULL, 
            0x1BFFBE5403717EACULL, 0x59CE002B6486C7FDULL, 0x12AA9836C3C10561ULL, 0x38F717D2E90BA5E9ULL
        }
    },
    {
        {
            0x8B279156BC97F1D3ULL, 0xC924E04464305232ULL, 0x5D45B12CD0E59519ULL, 0x4B782CEEE1AEED8AULL, 
            0x30FB2198CE9A2216ULL, 0x39155FD3BAFAB0F4ULL, 0xDF80E4909B9DC955ULL, 0xBCAB54CA2EFDC218ULL, 
            0x8D6F635EFCA5D7EEULL, 0xA32D457112C82F06ULL, 0x2C8B1A38CF818C23ULL, 0xBBCC3728C615619EULL, 
            0x67803DE3BB5A3B10ULL, 0xC151722B6E4DFC41ULL, 0x563FC32F6451839CULL, 0x591345BF77F17F00ULL, 
            0x47B6316950540046ULL, 0x12572CCA36D7AA5DULL, 0x9FBA803130C4CCC8ULL, 0x5415E91B85D7551AULL, 
            0xDB7BAE662E5D0F6AULL, 0x6FD88A4E371BD889ULL, 0x5D4C0CA01F33C8C1ULL, 0x0A86B68B6230B9EEULL, 
            0xC2E72185F4657E58ULL, 0xFEF3D294B880972DULL, 0x575CB907C4E04C42ULL, 0x2A966D45127457ADULL, 
            0x8E08FEBD2C63872AULL, 0x7C9094318BEEFF5FULL, 0x65295F52A03B4AD1ULL, 0x989ACE454BC82FA6ULL
        },
        {
            0xC401808D544ADD1EULL, 0x302B232489669A7EULL, 0x02C0EAF450542740ULL, 0x9795CDA0918B7848ULL, 
            0xE871DA3F56B1060BULL, 0xD9DF311548870ABDULL, 0x2CAD770EF62D45F1ULL, 0x1EF0EEF05F9AFF61ULL, 
            0x6FD5771BD9D5F01CULL, 0xE52604523A8E6908ULL, 0xB5F62AE138C312E0ULL, 0xD33723F6106EF88DULL, 
            0x6CE66E785D6DBAEAULL, 0x2CEECB435C49660AULL, 0x8F44675D0D954379ULL, 0xE22740DA30991EB1ULL, 
            0xE2F1B065A2C03030ULL, 0x91300B42157694D8ULL, 0x722DD8BB86D9B661ULL, 0x0913A10B6DACE7D7ULL, 
            0x5245653C47429770ULL, 0x3B87155EB8AE498CULL, 0x2A8671105CF75044ULL, 0x47A631410E2B07ABULL, 
            0x7CA444DA390C1402ULL, 0xD76424BB69E5EF87ULL, 0x0E8855773D7980FDULL, 0xC4070BC3351AC469ULL, 
            0x8831A23AFA33722EULL, 0xA0B143122F17F909ULL, 0x29A98F016F670EFAULL, 0xD033718E6A76C70AULL
        },
        {
            0x2B5C9377739B93F8ULL, 0xAA160109606481BBULL, 0x940D4ED60D66EC34ULL, 0xD7417FD12B0BEF46ULL, 
            0x03DA8EE36688C216ULL, 0xDB885B7C90795109ULL, 0x51DCBD4FC94E1654ULL, 0x59C886877EC331BAULL, 
            0xB1E9D7E25ACB7DBCULL, 0xD3DD68ABAD4774BAULL, 0x9BDAEAB69623C7FCULL, 0xB07015C405CE0A6CULL, 
            0x603E3C9E9742F0F3ULL, 0xF45C3C18DA0C9A91ULL, 0x0901323710507932ULL, 0xC664F1D3EB66F2ECULL, 
            0x07BE428EAE7C497BULL, 0x83393B82A225BAE9ULL, 0x47DA1C43E44B2722ULL, 0xAE59AF8F8C62191CULL, 
            0x15428710941FF247ULL, 0x30E1729427949BE9ULL, 0xB8155ED020D8EBA2ULL, 0x8AFFA000A341F095ULL, 
            0xF452F71800F6C732ULL, 0x1C544D1ABFEA787BULL, 0x0FFB476E6F844243ULL, 0x089B0411463E8E8CULL, 
            0x6AB219013B880296ULL, 0x3DF11F4BF487CAC8ULL, 0x0EB8B2439A1B3594ULL, 0x9C577C629FB11900ULL
        },
        {
            0x4C97894F7DB13954ULL, 0x23C5DBAF3E64E652ULL, 0x601B007C1044F6EDULL, 0x334AB9178E6647F4ULL, 
            0x112B10DBC826792DULL, 0xD916D1C3E3B7418EULL, 0x903C6D657834F115ULL, 0x04A3F433E4F0EE19ULL, 
            0x442BBF07C6EFBD6DULL, 0x3622CD05B2250736ULL, 0x04D1C449EA6011B1ULL, 0x25475E181EFDC702ULL, 
            0xE15FC9C518E88FE6ULL, 0xB4011E5AA56332E3ULL, 0xF20F182D675F33EEULL, 0xB7A2C49BCF983E64ULL, 
            0x69B5F22D22A51B41ULL, 0x7700CA29F9D52F81ULL, 0xBCE39ED5E0279B87ULL, 0xC70822C95E5DCB44ULL, 
            0xD8E38F2EBFE33EFBULL, 0xF6982EB9FDD3EB59ULL, 0xB34C8E96DDA91923ULL, 0xE5F607CF15341D52ULL, 
            0x68EE98C6E4863D9CULL, 0xC6C7145D5C92FB9AULL, 0x1B296A35D97AD852ULL, 0xBA4AF764B9CC4B1DULL, 
            0xE3EA3319E46ED8A9ULL, 0xE8B129E0018ADF25ULL, 0x72E35804E5FF33F6ULL, 0x8692363A0824B542ULL
        },
        {
            0x898066B480746B24ULL, 0xDA904F44FCCA8C62ULL, 0x5A1CFC5C413DC2DBULL, 0x44168EA30C8C258EULL, 
            0x47CC6DDF4C311A01ULL, 0xEF8C071943AB351FULL, 0xB67ED1ACE8F96144ULL, 0x7600C9AB95FBC883ULL, 
            0x97C46A7D658CDB3FULL, 0xFAE8ACDFC401215BULL, 0x277CE7B761A63A08ULL, 0xA82C919F2ED849BBULL, 
            0xA35F3FBE6D768923ULL, 0xF4D698B42C7CE694ULL, 0x75C6BAF3C368765FULL, 0x5FC5D0AF6FD7E172ULL, 
            0xEB4DA0CC2A6C27A2ULL, 0x4DA2E47112BE6809ULL, 0xF544CE7F642064BAULL, 0x7BDDA91CEAC39961ULL, 
            0x9921B04C6F2356E5ULL, 0x628EDFFD1426C49AULL, 0xDDE6222004DA1F49ULL, 0x7AC5495A3C4F27E3ULL, 
            0xD4B82D4BB60B5D8CULL, 0xFDF4DFD9560075B3ULL, 0x1B38578620D9E8F0ULL, 0x9FE06BD522936935ULL, 
            0x3F94D2BC7A4EB329ULL, 0x42D62D3DBB756E75ULL, 0xE30FC3A8AF9C8F3AULL, 0xF322C3D0236A51E7ULL
        },
        {
            0x4D9D6C6F06CCE3CAULL, 0xE7A0B158149245DFULL, 0xD0458DFC8C45473EULL, 0xE2CAE616484E5E82ULL, 
            0xDD3064DB09C293C3ULL, 0xF83EAA47DE03A29CULL, 0x9C5FC53887744A79ULL, 0xAEF06C4F43C28B1DULL, 
            0xA2497FC07EAB4960ULL, 0xC7D6DD5F8223E2D0ULL, 0xD1B8485E88E11B9EULL, 0xEDD839E55B9840DAULL, 
            0xDF36E4091B607DBDULL, 0x842EBBB351A06974ULL, 0x2D739AE9D3C1B5FDULL, 0xF7D2B475824254F6ULL, 
            0x5FC38E60FADFE447ULL, 0xA06DAA61DE1E7180ULL, 0x829BA791C127176BULL, 0x380A889D39927404ULL, 
            0xBB94ED4101048C65ULL, 0x4902B16A57804ED3ULL, 0xA7CA27C3DECA8EA3ULL, 0xC8247B4A280E7BDCULL, 
            0xE786285CD1BC1B34ULL, 0x8927D86CAAD06E93ULL, 0x31BB5C223C979B78ULL, 0xC902BE42D7DB0B6CULL, 
            0x7C5D7DFDB06FFBBBULL, 0xC1454ABF30345B56ULL, 0xF808D020020EEBE7ULL, 0xFB2EEBB981D046CCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseEConstants = {
    0xF98BCAD572034234ULL,
    0x64BF8D283A34EFF2ULL,
    0xF34938E89360C299ULL,
    0xF98BCAD572034234ULL,
    0x64BF8D283A34EFF2ULL,
    0xF34938E89360C299ULL,
    0xB206B53D30CE15E8ULL,
    0x7FF50E403A21964EULL,
    0xA4,
    0xA6,
    0x4E,
    0xAD,
    0x69,
    0xAC,
    0xE3,
    0x44
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseFSalts = {
    {
        {
            0xE7E563A122CCAD1FULL, 0x22FAAFFDED6553A0ULL, 0x383371783897FEB2ULL, 0xCC88E6A6C0F51EF7ULL, 
            0xCE8583488FBB4A2AULL, 0xC0B54A1FE23C0200ULL, 0xBF7711DD4C555876ULL, 0x812B7CBED0064C64ULL, 
            0x922C095829A00121ULL, 0x8387D84173310127ULL, 0x80B77CB6A3F45640ULL, 0xED834C1BF05D8903ULL, 
            0xC862FA7AA66B26EAULL, 0x57368DABB45FFE73ULL, 0x469D301919E924C4ULL, 0x348FDF8F3717D1A7ULL, 
            0xB974706C92B6C05DULL, 0xA3128A5CA858F49AULL, 0x2A16E78A13AF3674ULL, 0x313A226D4288398AULL, 
            0x0EAD21F521065C59ULL, 0xD675A3A5EAB15BBCULL, 0x4D6EDB86DF1E6317ULL, 0xA6FB603BA1BCCBBDULL, 
            0xE5D00DAEFE9034BEULL, 0x4EF49AD7D6539667ULL, 0x3376E2C27323F613ULL, 0xB49192040E01F871ULL, 
            0x6FAC922CA781CF8DULL, 0x98EEAE5EB9489D73ULL, 0x42CE061D00D25FCAULL, 0xCF16F30B204AB3B3ULL
        },
        {
            0xE86FF25419FAE143ULL, 0x6DD02B10E218EACDULL, 0xAF19BB68B0FCDDF7ULL, 0xB32F41E6C9C81B18ULL, 
            0x15AD66E2CF6B6581ULL, 0x9D3B9818C1ED843DULL, 0x3D22AC4F70031190ULL, 0xE0B6FAA3BEFAF4EEULL, 
            0xA77129ED115B48A4ULL, 0x3516FD45C2E65139ULL, 0x9B88C76920B6D294ULL, 0x18C29012A5EA854FULL, 
            0xDB2F2D8561823E6EULL, 0x5B48D6DA41DC05D0ULL, 0x3B672D4AD548D951ULL, 0xB627A2336B95B03CULL, 
            0x2C74C05196B96B8AULL, 0x25E0331676791AF8ULL, 0x37D5D48232B7A176ULL, 0x1A0E01C279CE64F4ULL, 
            0xB888CD405929F5B8ULL, 0x0DE880ABC2E3D1EAULL, 0x1B52EFC86253AA68ULL, 0x3FAC1631E63C1516ULL, 
            0x5EE73865364C0215ULL, 0x5F2555EB010FB20EULL, 0xB4B37F946EDCF44AULL, 0x20B1C68FE846EB0DULL, 
            0xBCA7FB0F350F6DE0ULL, 0xF5A5E7F101351092ULL, 0xBDF3EB20D97155ADULL, 0xB785B7D08B259981ULL
        },
        {
            0xFA7E8C72921A1D17ULL, 0x34D7F868C800D98BULL, 0x798907A79AF4B0B5ULL, 0x6B1730966D16D5C5ULL, 
            0xFE7AB01EBB7528AAULL, 0x8524ECFC0E4BC82AULL, 0x2493D8A648163CD1ULL, 0x82B6B9E775661F9CULL, 
            0x1BE59207CBE8D83CULL, 0x10E4D4C6D21511D0ULL, 0x62D7EE244940D8CFULL, 0x2B2CC3D42C837323ULL, 
            0x41A949E956B17952ULL, 0x301B8220B5C2B04DULL, 0xB16DD8AFFA48BD41ULL, 0x5318537AAFAD6A93ULL, 
            0x90338BA5B346FF11ULL, 0x9192E04EAB8A5B06ULL, 0xD4971CA6F93FFA0DULL, 0x23586D2CD3998340ULL, 
            0xD951A3EE2B4C22FBULL, 0x7117AB705D065B07ULL, 0x669536C0DF25E261ULL, 0x8D9E1EFC88B2621EULL, 
            0xA0F911BD205C8F56ULL, 0x515A1AA75B258EB0ULL, 0xF4E8E9EB72142E57ULL, 0xC458573AF057A118ULL, 
            0x725CB2DE0431489FULL, 0x27272FE90CB364D5ULL, 0x5BDE5E69FE0F5263ULL, 0x6964B2276B6595AEULL
        },
        {
            0x34D3F9F0F073CBC6ULL, 0x7AFD904BA9889BDFULL, 0xD8CC4DDD5DDB91D3ULL, 0x30837C9A275D58E5ULL, 
            0x40FBD7EFD4535C37ULL, 0xFCC7FB450D219AB9ULL, 0xA5ED29399E3A60B2ULL, 0x13472BB3F724092BULL, 
            0xF223BB2FD375A1DEULL, 0x5DB9871CCFEA5F95ULL, 0x5C86B727C745CD16ULL, 0x92110CF40B8EF7CCULL, 
            0x91F6B4D8B33D6C8CULL, 0x88D166F1AAE7CF4AULL, 0xDE323F126D68774EULL, 0xE02C7C15995A4ED6ULL, 
            0x4AE0A6E3343EDCD3ULL, 0x81C5ED5BDF0B8089ULL, 0xC3BABDD1A20E4C56ULL, 0xDBD5283BFB4B5639ULL, 
            0xFEC5AB574CF41940ULL, 0x1218A0915FF3807CULL, 0x534CCAE7BACA2FF1ULL, 0x7909F70E9E8767D3ULL, 
            0x7F4D7AFF1C9B6F48ULL, 0x8C96A197D6D5087BULL, 0x8C56A838F700EC7FULL, 0x749C7413EC02BF65ULL, 
            0x0D9104A6A7A96EEDULL, 0x26CBD815DC77318FULL, 0xF0035AD374958CFBULL, 0xE36831E42E8512F5ULL
        },
        {
            0x9290B848D9E62FCFULL, 0xC81F0C5EEE9E65BEULL, 0x4B9A0A80C184159EULL, 0x55858E1942D1BF99ULL, 
            0xDF631A8C26901049ULL, 0x3CF60B16A50E65E8ULL, 0x931E51A1B7CD4D78ULL, 0xFFCCE9B4C1D461E0ULL, 
            0xA5190F2F64D058D0ULL, 0x63AB5A8F5F17F5EDULL, 0x6CDEA01F7474A69AULL, 0x90E92CB4659E750DULL, 
            0xBE3E2950A3372232ULL, 0x59C1F2A499D5D5D6ULL, 0x05EAEEEFF208D8DAULL, 0x4978087F428B3E87ULL, 
            0xA2BE6C000496E890ULL, 0x280D88437D5A7B85ULL, 0xB1E9060C21A2DE4EULL, 0xE352104CA75FC524ULL, 
            0xDC324BA5C6FD02FAULL, 0x6FDFB3D1FFDEDFA2ULL, 0x6ADAE120B2CC08D0ULL, 0xE002C252D4C2BBADULL, 
            0x3BE73CDF585F21AFULL, 0x67DCD271FD7F7EC0ULL, 0x66DEA9EF8067887BULL, 0x439BC0A25EB2181BULL, 
            0x77F1FDC6A8F5CB5DULL, 0xDF64DC41C4C11E21ULL, 0xDC8C02DB0CF665E6ULL, 0x6910B9F88C345876ULL
        },
        {
            0xB6AC8129588C2671ULL, 0xE95608405E989991ULL, 0xA327EB5B685BCC4DULL, 0xC4389FB6C6912CD7ULL, 
            0x8FA913B9E01F184AULL, 0xE7EE0A036C324DE5ULL, 0xB6DE52550785E50BULL, 0x703487E19BA87E31ULL, 
            0xE77680EE78C9817BULL, 0x568AA4BCD47F9D74ULL, 0xF76299CB9E5159F3ULL, 0xA80F40F76FA6B182ULL, 
            0x30284B4E310AB654ULL, 0x49429AB5C61E80CCULL, 0x8B8A366C366942C2ULL, 0xB7A0E00C98F44938ULL, 
            0xBC70409FB0835F15ULL, 0x7F58E9DBBADACE03ULL, 0x712EB4226BB3E993ULL, 0xE12F7DD8209BA761ULL, 
            0x613E8FA182B47B5BULL, 0x55C48B21C7600B54ULL, 0xA242398EEA7CC3A7ULL, 0xC5A1EF3C19B3504AULL, 
            0x4260D44C2994A892ULL, 0xEDF0C8577BF3B3F1ULL, 0x2CC9A35EEE69392BULL, 0xA58C18DC074EA387ULL, 
            0xE7C994B3956033C9ULL, 0xB2393C5D01CAE610ULL, 0xC6E93AF9197C3035ULL, 0x99BEF0A3C1202D29ULL
        }
    },
    {
        {
            0x5DC1E65251B17F39ULL, 0xE8FE858536A3E6D5ULL, 0x712973461EA47C06ULL, 0x816FECD082AAA1C6ULL, 
            0x5578339129BD19ACULL, 0x4648E06086C63A0FULL, 0x31EE954D12B73A0FULL, 0xD1FC34BBF390BE6BULL, 
            0xBB2491A23DDD7880ULL, 0x52E9B5A5DA761353ULL, 0x0AA94588A2FBB7FEULL, 0x0C2DA6FFAA7397D9ULL, 
            0x945F259B088167E6ULL, 0x30577548C1EF0C09ULL, 0x2D1E0012B246E001ULL, 0xFA0D52BBDD159C03ULL, 
            0xEBB06FD1BE3D628AULL, 0x53562C44529A38A2ULL, 0xE337DD06D764F502ULL, 0x443C082329428643ULL, 
            0xBBB1035040AAAE6AULL, 0x521F758B9F7B9559ULL, 0x6BB7133C617971D9ULL, 0x2278DBDEC56D5157ULL, 
            0xEC222DC0383F7066ULL, 0x12F962C181359A63ULL, 0xE3920FA054A5D101ULL, 0x6CA3DBCC1E888C64ULL, 
            0x8C361599F4E3F766ULL, 0x204BC7A9E85AC659ULL, 0xD691153E332D0684ULL, 0x1EA38E7AC6364EDCULL
        },
        {
            0xF17A36AF0E21F2C1ULL, 0x766450DAF3EA5837ULL, 0x557A183091FAEE1CULL, 0xC9DDCFFEC2E33D52ULL, 
            0x3AF6805FBD7A241FULL, 0x4446B8A1F46E0A00ULL, 0xBAB45CBD1C5BE6A3ULL, 0x909DAEB3A1C61A88ULL, 
            0x50B8DB3AF3169D3CULL, 0x0C8A19149798908AULL, 0x9A4E35579F784650ULL, 0x6C331CB772301A6EULL, 
            0xC0774433F55EDE22ULL, 0x80DFBB220A757999ULL, 0x52B9C2D6BCB9C311ULL, 0xD19710D54ED7406AULL, 
            0xF6312FC39FCB3BB9ULL, 0xB9E0537FACD93258ULL, 0xCE11D946EF134FCFULL, 0x050776876D5E97ECULL, 
            0xFD48CE7EC76C38B3ULL, 0x9F1978826B104205ULL, 0xE8368735FA2EAB5CULL, 0x9FD46BEF07274626ULL, 
            0x196E540D5CD2F88EULL, 0x8DB231D4D1DB0F49ULL, 0x85B311BB45ED741BULL, 0x0845175DD7980C9FULL, 
            0x36C66CAE2C530495ULL, 0xAB408965F12660E1ULL, 0xAB51EBCB39ED2112ULL, 0x2496F8C83682A3B6ULL
        },
        {
            0x4E7592EABA62D861ULL, 0x9901E06C2157E657ULL, 0xFE39D0F640551E45ULL, 0x59D24002020FDB50ULL, 
            0xAF359D306DAF7140ULL, 0x6B083B527DBE0393ULL, 0x5D3B93D1BA259D8BULL, 0xC8DD0A62B1A25099ULL, 
            0x50032696DE593E19ULL, 0xCAE765D380FA7527ULL, 0xE6E56B6EE5B39406ULL, 0xCF4467297C2AEBDDULL, 
            0x5AF7BBF5EA8522B5ULL, 0x2B2A35E60C4DC6C7ULL, 0x2DAD4B90FC38B61EULL, 0x7BDA68908B0401F2ULL, 
            0xAE9BD9FFCCC153CAULL, 0xE184F1F4B2EE5020ULL, 0x88954BFC9F01CD83ULL, 0xDFE39063754CFB35ULL, 
            0xA862EC274F746255ULL, 0x56340230C47AEDE9ULL, 0x0ACDA4AEB326BC90ULL, 0x846940C16916D0BEULL, 
            0x090FBA65165FEF86ULL, 0xBE5BAAB0A2701E57ULL, 0x0FA4743A7B1A460EULL, 0x81BA682941C3600CULL, 
            0x1EA9B8C3F8697720ULL, 0x14D88F75B0CCF465ULL, 0x4B072F0FDF058A7AULL, 0xD9B40F5BC9F45064ULL
        },
        {
            0x2B330047E04D1798ULL, 0x6976C633595B63BDULL, 0x798C1135A15E65A0ULL, 0x0528D9960984DC30ULL, 
            0x194DC1AA50054FADULL, 0x8E89A5E1327F77B6ULL, 0x937BF507047C4527ULL, 0x3DFBACF14397426BULL, 
            0xB6E9A3645C0480C1ULL, 0xD0BE8576EAC3D07CULL, 0x72458C88D0ECD89CULL, 0xF65CE0F0A6C903C4ULL, 
            0x1B0E3850B035D407ULL, 0x74B138B378ECDDE7ULL, 0x5E4F8A4F36837194ULL, 0xE965D159C1ED036CULL, 
            0xC5C5CCB93DFCAC2BULL, 0xE8EFACC32B808AB3ULL, 0x62281EAD43FA9F3DULL, 0xDF5DFDE83C3FD501ULL, 
            0x760F8A4872424F40ULL, 0xFB9ED60E08AF956FULL, 0x648ADC05DC57B068ULL, 0x417AD8E6CF1C59EDULL, 
            0xC69AC96402D39B49ULL, 0x23A9B1D19FB26C73ULL, 0xE8CE7EBFBE39BA87ULL, 0x5B220FE789777456ULL, 
            0x87562C8B8A259320ULL, 0x988934ADA376212EULL, 0xEA93C09B1C0FEC3EULL, 0xC303551C77DCF8E0ULL
        },
        {
            0xA1CBC9AAEBF9F278ULL, 0xEB58BB2AA56C387FULL, 0x82CB68AE7F195FCDULL, 0xD52AC80DAC4F25DCULL, 
            0x80F80FDD929CFDF1ULL, 0xBD354934F07E9518ULL, 0xDA4F86B67AEA5BC9ULL, 0x9916C522207E9FB8ULL, 
            0x50285D353837A49CULL, 0x3EBEC62878497217ULL, 0xEBCA75F1EDF274FBULL, 0xE51EB74F1806548CULL, 
            0xA2DA4B9024030EE3ULL, 0x7D63AE8B3D1ED550ULL, 0x7981B2517EF380DAULL, 0xA2FFB47A49F90BC3ULL, 
            0x681D7F583407251EULL, 0x9CBABB42CEEA545FULL, 0x0707724C2383A052ULL, 0xC5C0FCBA7D39F19EULL, 
            0x30AFD4AE94C30F3BULL, 0xB446A5E84804C39FULL, 0x9E4F656B46704553ULL, 0xA79F0807038CC80BULL, 
            0xF8D1CE9F8D482DFFULL, 0xEAD6D1BC1F5B9C4BULL, 0xB3FD688D803EA299ULL, 0x11B0273457725431ULL, 
            0xAAAECE11F0607E3CULL, 0xB8D8A6BF61D9DAD9ULL, 0xFDD7E15AE7B724C1ULL, 0xFA63FD5191BE2260ULL
        },
        {
            0xA2272F799B8F8411ULL, 0xFC7FD9D541FB6EF5ULL, 0xE70F5984C0AAAEE7ULL, 0xF0296C7980C1CC2FULL, 
            0xE9D86CD2F2A1935AULL, 0xA790593C17E96A44ULL, 0xC3D46332624817B0ULL, 0xD9AD545B99567AF8ULL, 
            0xC292D6EA8608215EULL, 0xC2F8D1E84474DC13ULL, 0x8FFDA95380558E6CULL, 0x71A4D7FACBC35900ULL, 
            0x9B0E2713D2F39874ULL, 0xDBD96BD00E851AC8ULL, 0x218FA748D7B41F5EULL, 0x93C7FFB8CEFD8C4CULL, 
            0x267B2A136D499EC6ULL, 0xC05F02654EB04ADBULL, 0xA49F1CA439F7BF30ULL, 0x655C9C5AF7E6D38BULL, 
            0x037D41A8DB2828B1ULL, 0xB5739BE4575ACE0EULL, 0xCCE6EEB76B777461ULL, 0x318CBDD2EF58C681ULL, 
            0xC32027EC73F7BBD6ULL, 0x24177DF8D46ADC97ULL, 0x696E0ABFC421D82AULL, 0xCFE0EA84109D5883ULL, 
            0x48DC62E4DFFF5030ULL, 0xDD942879A48250A8ULL, 0x99C5F757BCEDE6DDULL, 0x146CAE7D122DB371ULL
        }
    },
    {
        {
            0xBAC61BDCCBAF3382ULL, 0x088BBAABE7D043A6ULL, 0x3728CB5727FAAEC8ULL, 0x5CCEFDF29EAF4AA4ULL, 
            0xBBCFA65843AD1466ULL, 0x77D8781CE541C807ULL, 0x707AF922D4B36038ULL, 0xBEDF2E4C067E9791ULL, 
            0x988C4BEBAC6AA4E2ULL, 0x051B6BE77A9B0361ULL, 0x068F38431EBA3D69ULL, 0x00C876EB40B366CEULL, 
            0x5E65ABA3833E5189ULL, 0x09ECCCAF4926D804ULL, 0x322F0F4E8FA0741AULL, 0x1B76582210EA6362ULL, 
            0xFFF89F20D19352B6ULL, 0xD813BCFEBD52D999ULL, 0xBFBF409B5ED43B46ULL, 0x20B2CF06B8C01D14ULL, 
            0xE7B19F0BDCC5E081ULL, 0x96F82618285CDAA3ULL, 0x3BD106216CB62A0BULL, 0xFA341DDD4C28FE8FULL, 
            0x3BAA4589C8A20B8EULL, 0x8B24F9D922DEEA53ULL, 0x00288272DE5233C9ULL, 0xBFA80DC802C5EDA9ULL, 
            0x89EC9DBBF83E1DCEULL, 0xA82802F378DC2BDAULL, 0xB78A922DA547A7C3ULL, 0x251ECDBE4EAE0168ULL
        },
        {
            0x2DACC4F4F3229AC9ULL, 0xD1599136AE05863DULL, 0x703624C53DD9DF06ULL, 0xF00EB3555086DBEEULL, 
            0x205823ED838B993FULL, 0xEC5851A44221F455ULL, 0x6DE7BEF56393338DULL, 0xE4CFEA4E46B8977EULL, 
            0x12D396C4ABBA870AULL, 0xBD57C46B1DF41053ULL, 0x5C3494B9959750C8ULL, 0x56ADCA128B41D497ULL, 
            0x3C42816B79289932ULL, 0x9B4D7699AC27C5C2ULL, 0x3159DF84167C53AFULL, 0x7F71ABA56A9B3ECDULL, 
            0x0A56722205501269ULL, 0x25A1A0C6AE719A4AULL, 0x670AC455EA033CADULL, 0xF51DA97A8C683DB0ULL, 
            0x7A51808503640E4BULL, 0xD4468980BF857265ULL, 0x95E10E5C3E92567BULL, 0x93283DAA6809AA04ULL, 
            0xFC123243400E5D81ULL, 0xF4ADA6DB2A6A0A16ULL, 0x3E7E9CDF36C346E6ULL, 0x80DB4987458ABD14ULL, 
            0x55A0362DCA69DFDFULL, 0xF2C42946D758B1D4ULL, 0xB28D0549A9325FA1ULL, 0xEFB4745E5C221145ULL
        },
        {
            0x6D52D79BB0FD28CDULL, 0x1BB2C60BA2B8AA86ULL, 0x52E13E9F147DB231ULL, 0x8E1CA8515D05E821ULL, 
            0x411F186BE10ACAEDULL, 0x1E0FE2AA749C5935ULL, 0xF9457455BC82C47FULL, 0xB2552CB695209B6BULL, 
            0xC132C15C48E7BF42ULL, 0xBB11EE202C33CA60ULL, 0x950E27933DB4AAA4ULL, 0x10A5D9936F043733ULL, 
            0x40E565E1A4811A1EULL, 0xC1965C3C9AF8251CULL, 0x66A7970363B17256ULL, 0xC03B41B4C2BE952EULL, 
            0x04EDE76EBA1CC8F5ULL, 0x86BE020DB63702B2ULL, 0x89F9E8B968BDBAADULL, 0x9C484DFFE248A32DULL, 
            0x8980EF6CDB3927DEULL, 0x89DA4B4D75717127ULL, 0xAA37C9296856D21EULL, 0x4AEFB251695393C0ULL, 
            0x641156CD52A35CFBULL, 0x336CFD7D6BAF88A4ULL, 0xFD12554B555462E5ULL, 0x7306AFB52F05A9D6ULL, 
            0x66C43F87EE6E7212ULL, 0x959891B482F79011ULL, 0xCDAAB165E411D874ULL, 0xD62F4BC3DFAAB9E2ULL
        },
        {
            0x52308C8C5B4D7C8AULL, 0x24806F13F662B2D8ULL, 0x764C6A9E4FD3B7CEULL, 0x350B20D8B3840ED6ULL, 
            0x55DEBE59134190E2ULL, 0xA4467A0420E81B43ULL, 0x69CB199C1F62899CULL, 0x63DC85B61A823BAEULL, 
            0xDCDD02A6AC08A25EULL, 0x72FA721E32121E97ULL, 0x972643B8C41BC3FEULL, 0xA2841835F9BC50BCULL, 
            0x11D5D9BEDAED9B78ULL, 0x07585BB4AEFB722CULL, 0xDAB974807BAEEDEEULL, 0x58E8DA10D8B8A675ULL, 
            0x502E91C3F71E6021ULL, 0x98FAEFC6D92258A0ULL, 0x11972391DC884405ULL, 0x48958A2E91284F72ULL, 
            0xD1931A4214D84D43ULL, 0x654255D16D734B33ULL, 0x0CDC81A937BB27C6ULL, 0xE6834DC67B095DAAULL, 
            0x52100850591E1C85ULL, 0xBD91F4D02A7A3E91ULL, 0x315508582D6C89C8ULL, 0x80D1224E52B256BCULL, 
            0xB664410D3AB2164DULL, 0x858CE7301287C0E0ULL, 0xBE96B2C1CED649B8ULL, 0x5503F8F52C84CED0ULL
        },
        {
            0x1385889D3DBDC383ULL, 0xB36EAF69FEFA6326ULL, 0x26CAA40368A0C015ULL, 0xD49E00A5B4ABD45BULL, 
            0xBA31EFB51686FC60ULL, 0xAA23CDE3800AD9D3ULL, 0x078BEFFB85FCED05ULL, 0x6C3A9831B0F549BBULL, 
            0x4C27F250E7F2ECB2ULL, 0xA84DF82A3732D51CULL, 0x5EC1308481C024DEULL, 0x8C3C1B8B38B1AFE1ULL, 
            0x7528B8BCC2027358ULL, 0xA1487D76AD4EBC26ULL, 0x6D39EA9C89B23D91ULL, 0xA4A14C090044BF35ULL, 
            0x18CEDBB4DAA91F39ULL, 0x53E7AA5A127BD50FULL, 0x7541C615344D88A2ULL, 0x9E0CC8678947A364ULL, 
            0xDC6FAF91EC915AD2ULL, 0xCB0BD0B509FFCCDFULL, 0x36B098E2EFED89C7ULL, 0x4B762048A9225950ULL, 
            0x7E4987BA40D95D92ULL, 0x55C2A6A0EEB36C57ULL, 0xF58CF677A110BDA5ULL, 0xAECBC6899B0038A3ULL, 
            0x4ACD9B172F7CA45BULL, 0xFF116796A06934F4ULL, 0xF94A5C01036BDFD1ULL, 0x3C0766FA2E45F9E8ULL
        },
        {
            0x9B185D9E1A80AA53ULL, 0x5C5654CC0E06E194ULL, 0x9979A4F4D8562EDAULL, 0xB785EAB7BB8F6546ULL, 
            0xE7A9C45F96A3FF84ULL, 0xC717965E45970684ULL, 0xB52A6AA87EB22BD1ULL, 0xA2B7453CDFA62767ULL, 
            0xFB5FA349245B722EULL, 0xE899A92B64EE107DULL, 0x5A8EC85EF6780264ULL, 0x547963F56BEFB822ULL, 
            0xECF4F142A7342993ULL, 0x62B876CE3B8DD560ULL, 0xA4F829D4E8B22AAEULL, 0xC29518ECFB801DE5ULL, 
            0xAEF37DAF46E05B49ULL, 0x0B09856923C63AC3ULL, 0x81B9B0F8E0381474ULL, 0x69582603804C4563ULL, 
            0x636EE00C5A70CC7BULL, 0x22F8FDFB51C65115ULL, 0x7FF9B53BDE37028AULL, 0xF0A97163EB712B02ULL, 
            0x96D3BDE10794F376ULL, 0xED33BB709C845A20ULL, 0x3DEA5D747E4EA927ULL, 0x5A22367829F3F100ULL, 
            0x0F748580563856A9ULL, 0x3DBD89EF6C740D53ULL, 0x09B8811AE5033C28ULL, 0xA0666AF03FA63E96ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseFConstants = {
    0x31C4DFA93CDAC718ULL,
    0x5433F3BC65F9BBAAULL,
    0x072F0C2D9DBB7CD4ULL,
    0x31C4DFA93CDAC718ULL,
    0x5433F3BC65F9BBAAULL,
    0x072F0C2D9DBB7CD4ULL,
    0x531F3EC0107AAB50ULL,
    0x15512D3ED1826481ULL,
    0x85,
    0x88,
    0x79,
    0x69,
    0xC8,
    0x60,
    0xE0,
    0x50
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseGSalts = {
    {
        {
            0xCECF0F925C1D7D64ULL, 0x8E3B3BAABDC543F0ULL, 0xA6180398C6EFF088ULL, 0xFB648E4747FDB6B4ULL, 
            0xCC0E306C3AB12BD0ULL, 0x2867725B0A479266ULL, 0x81455C45F1E5C51EULL, 0xB0B3F4560254DB3BULL, 
            0x3E2AF29CDCAFAF3CULL, 0xC86B599CCD079E07ULL, 0xFCEFAEF5AEBB7F7FULL, 0xFFE32E009639E6A0ULL, 
            0x1E4B3E35731554C2ULL, 0x1BE6B15D76196F04ULL, 0xBD2DEC14FE696522ULL, 0xD6C0F652EBC8AF98ULL, 
            0x2229F1DCE1FDE323ULL, 0x8C659674D9809AA5ULL, 0x81DF6F26460F199FULL, 0x5C02864C97802C26ULL, 
            0x7B3D678CF3579EF5ULL, 0xAB8057614A91DF74ULL, 0x94C324056F306E79ULL, 0x1E94A081EC557B3CULL, 
            0xFA0D41CBE640A204ULL, 0xB163DC4C4E008E13ULL, 0x73AF87C58B77E5D2ULL, 0xF1E8B984E9BC6CFBULL, 
            0x6C77FA0A3CB0D84CULL, 0xAEECFB6729442A96ULL, 0x9E0A724FA2DFE27EULL, 0x6C1311FCD197C67FULL
        },
        {
            0x030BB40492ED9776ULL, 0x1924DD888AC378DDULL, 0x94F07C82B2332F3BULL, 0xF74D7C34BB89956EULL, 
            0xEC5EED1393B1F4DCULL, 0x9AD50538A3C167BAULL, 0x0BF72E972D7AAF74ULL, 0xD9CE5BFAD846F143ULL, 
            0x791689C21BBF22F3ULL, 0x710DA72C75E35570ULL, 0x5296E6511C38FEE5ULL, 0xB50C5B9ECBA5B308ULL, 
            0xC64667294A622ED2ULL, 0xD2163B25C86C7D83ULL, 0x06934189423296F4ULL, 0x5D570F29582BBC34ULL, 
            0x7091F55FB62B141EULL, 0x192D5C357FAF5F40ULL, 0xB741A710E7BA7708ULL, 0x36C1F279AF4946BBULL, 
            0xCA84C39F6B6C7006ULL, 0x1A8FB116A5E13C34ULL, 0xF4875497638C0BF6ULL, 0xAD3EB91A73DAAB94ULL, 
            0x748726EECB5DB948ULL, 0x5BFFDD1ED8BB1028ULL, 0x5E608E3B6041F99BULL, 0xEC38919544BFD35AULL, 
            0xC612AD8430F3B045ULL, 0xEDC01EA591B1ECDDULL, 0xB117DC7EADE373D8ULL, 0x4ACD3F83F0B50E7DULL
        },
        {
            0x68F4F39C5BE02500ULL, 0x8658E6554C37D05BULL, 0x7760A052623D70EFULL, 0x8C76F1B59EC758AFULL, 
            0xFC2D9B6F26CF7C09ULL, 0xD440F10C19D6767DULL, 0x6C259C0CB8FD2CA4ULL, 0xA9E7875045D1F079ULL, 
            0x2DD7D5E7771A6DEDULL, 0xAFEB3E9FFB0EDFB1ULL, 0x62E0EA7074207393ULL, 0xCCADC3AD15A29892ULL, 
            0x2ED6B751BD290F8AULL, 0x6293AA2D1416C1DBULL, 0x5AB46C5BE82DA3D8ULL, 0x24EC0FC7E4A04C50ULL, 
            0x2FAE3BEB5D679D5DULL, 0x183EA07572576D7DULL, 0x5667BA511147BF8AULL, 0x5B5CECE0D37BC440ULL, 
            0x959A445AA380A424ULL, 0xCB64736FC9D637A1ULL, 0x42C738027AD0CCA8ULL, 0x0E14D752748C74C0ULL, 
            0x4F6C97AF7389F579ULL, 0xF05D53C2E0374AB7ULL, 0xB3AFB268501B24EAULL, 0x5639C0D710D74F6EULL, 
            0x4979C780732D8EBAULL, 0xB48EBA6C7F549586ULL, 0xF4C449C472CC44F6ULL, 0x90351D2B9D2CB311ULL
        },
        {
            0x6B35EF7FEB0EB824ULL, 0xE6675A1F564AE642ULL, 0xD16E2663F61DDAC9ULL, 0xD20F57B882113CA2ULL, 
            0xF215034617CBE4E5ULL, 0x1A62909C5D4D534CULL, 0x4472F3E1A826FE33ULL, 0x32FB743DD0A43D1EULL, 
            0x8B60C1B76F131726ULL, 0xA38DD6D849C6C7E3ULL, 0xFE70D03ABBC69FE5ULL, 0x92632F124CD0BCAFULL, 
            0x626BC7D4D792B935ULL, 0xC35D00AF37C8C13DULL, 0xAD883B0D37EB8F2DULL, 0x4BC8E45D32A59050ULL, 
            0xC7C6BCCF4E5A011BULL, 0xF8B4041FD10934C5ULL, 0x7E6022D05A938110ULL, 0xB4D8EC4F77388162ULL, 
            0xDDCB98C44A534846ULL, 0xA050DE0B57AC7A5FULL, 0xCB44E7CEAC743B44ULL, 0x73413156EBE61671ULL, 
            0x7C85D93C0449F3ABULL, 0x654040D8C1B06973ULL, 0x0A17ED09A0241F25ULL, 0x8B2223B7E93E7BBBULL, 
            0xF6B4219893D7F2A1ULL, 0xB0D861F1B7F479B8ULL, 0x65F0259E150ABE17ULL, 0xEB20AF19A519DDFBULL
        },
        {
            0xCD5D911B24A8508CULL, 0x2487094D82FB26D8ULL, 0xD90CA976C62C535BULL, 0xDDA9DDC911BA917AULL, 
            0xC3E972C26981A141ULL, 0x13778C52CB5A321AULL, 0xD640A2025659E162ULL, 0x1DA44A80E8FD3DA3ULL, 
            0xA874EA3C09D540A6ULL, 0x66E63E766B5B83ECULL, 0x72DD667E76E7192CULL, 0xF65A7E7751FEFDB7ULL, 
            0xDC14CDBF7B6EDD5FULL, 0xBF2BB3158B0CE575ULL, 0xAC4117043CFAEF5EULL, 0x1AE7B4983137C649ULL, 
            0xB07675896407E33EULL, 0xFDB022B113BDFA42ULL, 0xAACDE6BF0D38AC16ULL, 0xD765DC23FF6EB675ULL, 
            0x176477906BA4522EULL, 0xEA7DF1DFDA46FAFBULL, 0xB926BF55FBD1AA3CULL, 0x2902A09F0163F739ULL, 
            0x14BF46BBA796A71BULL, 0x6570A0D6E26F38E8ULL, 0x21F6F8ECF9E8DC5AULL, 0x535AA4EAD341CF65ULL, 
            0x0C78BF3656E7AEA4ULL, 0x3482BF621F7BAD8DULL, 0x3A252F947DE5F638ULL, 0xED6B995CE5CBC3D3ULL
        },
        {
            0xD20922388A3660FCULL, 0xA20D3BDBC9D59800ULL, 0x0F28AE35DBB16D5DULL, 0xD002F1242A2D15FEULL, 
            0x7FF0D021FD60FBD5ULL, 0x5741460579EB1742ULL, 0xE4414310A377480EULL, 0xC74E694736446E71ULL, 
            0x073664AE5F421D77ULL, 0x7EAE5F2CEDD6533FULL, 0xBB60FCBFA9D03225ULL, 0x60D35130DDCF6CB7ULL, 
            0xBA874CF03F5A2C74ULL, 0x3BBB045A7B301EE6ULL, 0xFDD49FA27F20ACB5ULL, 0xC5E7A9FB2F4907E5ULL, 
            0xB2910FA968C3223AULL, 0xA4C99FDF11359211ULL, 0x170DF0673A702243ULL, 0x6953C964131379CEULL, 
            0x1F67C42354AE76B7ULL, 0xEFD7AA22921F8CEDULL, 0xE990D60BA3D49AFDULL, 0x5156C249EA1FD44FULL, 
            0xE7DAD9F2841BAF2EULL, 0x648DC3A63593557AULL, 0x81A3AA0015955537ULL, 0xF8054076D5D8D714ULL, 
            0x8965D8B54CC827EDULL, 0xD6892F70AE927207ULL, 0xE8A380BD8544B2A3ULL, 0x4C6481D1906DADD6ULL
        }
    },
    {
        {
            0x5581E72C362DE1F3ULL, 0x41646CF2F7E23527ULL, 0x02359F63BFCF1E47ULL, 0x76B4529F16F117D2ULL, 
            0x8059B302F903B832ULL, 0x52A66DBEE6CA3BFEULL, 0x45CF49E4E010E8B3ULL, 0x66A06380FBA68947ULL, 
            0x50BDB502BB5965A6ULL, 0xEEA5230101F2BF46ULL, 0x23161D37F5BCC0BCULL, 0x6EEB0CAD5AC83B3AULL, 
            0xBC66E1BF425A7007ULL, 0x30E03B5D4EEB3762ULL, 0x260266B415CF7EA7ULL, 0xB5D612526BE054CEULL, 
            0xE501E1CD8B7AF12AULL, 0x826070436F95292AULL, 0xAED71407ED850F29ULL, 0x0329BFE412B678A4ULL, 
            0xE72327CF6CE90D82ULL, 0x1B2BF2A49861CE6AULL, 0x1B513BF6BED30C27ULL, 0x38DDF93F2D4994AAULL, 
            0x1ADD5C3AA0BE822FULL, 0x760132372A0CC1FDULL, 0x5BECCBCD48D86305ULL, 0x77B048B2B7AC225DULL, 
            0xA1A23E93BBFE3B8FULL, 0x6434B1F0C92E9AAAULL, 0x705CC83AC2D1080BULL, 0x8C940131615E4AAAULL
        },
        {
            0x128FE157D0D0EE49ULL, 0x379F0D464AEB61C9ULL, 0xB5819A0D1A711DDBULL, 0xD58D3370349F8FD1ULL, 
            0xDBBDEF65F0BC4AE3ULL, 0xBBB786531B5B4E76ULL, 0xB3DF410FFCC26FA6ULL, 0xF6651B894DE177C5ULL, 
            0x827893067F55FF99ULL, 0xB4295AC928FFD0D4ULL, 0x915EE8C773BE3DBAULL, 0x612C868F560015A5ULL, 
            0xEE3D08D7F6C27AB8ULL, 0xCCB4916099DDAF7CULL, 0x7123A90571A15F53ULL, 0x4DD73DA128341CF4ULL, 
            0xDF11BC7BD027ABA7ULL, 0xCFC83683358609E4ULL, 0xE2D4A471B260E920ULL, 0xC313B75994192D9EULL, 
            0xDB2838E6DCDFB25FULL, 0x11775BC29E21A0C8ULL, 0x3298492DDB0A4D20ULL, 0x4FC02EDA2F856615ULL, 
            0xB0E20798F90C4A02ULL, 0x4F4C69E695CE05F0ULL, 0x8DFA37A3B4C2AC37ULL, 0xB5C83D234059EF91ULL, 
            0xCF4F75B6ADB32AA3ULL, 0xA69F7082ADE05FA5ULL, 0xFF012BC5FACE336AULL, 0x7CBC6C638D0916E7ULL
        },
        {
            0x92C45459AD170770ULL, 0x45F2C0D1DCD8FAABULL, 0x35415D7451A2A039ULL, 0xB615B7DA60CD546DULL, 
            0x16115FD9AAF5BF33ULL, 0xCE0CB77819E2006EULL, 0xCAE491ED5C4F5228ULL, 0x14683D12E43E1CDBULL, 
            0x8AFEA929A01A52E6ULL, 0xF085BDD3D3B48488ULL, 0x1B14119D817332D8ULL, 0x2DF1245B2998ABF9ULL, 
            0xAEDBDBEE09B60B46ULL, 0xD43562F83885E422ULL, 0x002D6BD55FC79E95ULL, 0xF1988276C00BCE8FULL, 
            0x69D2AF6CCB9A9B3CULL, 0x474294597787C18FULL, 0xBEA61CC71BCE4FF9ULL, 0x3C55FF6875AB9554ULL, 
            0x337D65DD77EDA2AAULL, 0x63CE7D42811AF043ULL, 0xD93BC6FC58BAB188ULL, 0x3B50F21187F919EEULL, 
            0xA048BA05E6A601DAULL, 0x8D9EAEDA6854DC1EULL, 0x0C310A4D8ED6789BULL, 0xDB8BCD9E7E157027ULL, 
            0xF45F2C030BB46447ULL, 0xD13DACF0CCF488ECULL, 0x8C996C1170E49ECBULL, 0x2CD6827D848517FEULL
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
            0xF2112530436C0D81ULL, 0x187F6DB3EF580981ULL, 0xFEB4F5D34059F28EULL, 0x0E4836092C33BC87ULL, 
            0x68A8E8283D80CE54ULL, 0x94B1D87FA310882CULL, 0x55FBCA6EF675E5A7ULL, 0x77198966023985FFULL, 
            0x0D214A9049FC2748ULL, 0x015E00C7A5532F88ULL, 0xA774EE4C8359CA20ULL, 0x47E42990B12C0BB5ULL, 
            0xBB7C218E80D2ADA2ULL, 0xF61E765AD8FFCEA0ULL, 0xC07F6AFD66C389FCULL, 0x70E7202C7196B80AULL, 
            0x252E67A27BFB8BCDULL, 0xF6ADA88B61A1B7E1ULL, 0xB201DA113BFCD3A2ULL, 0xA52F27BF74BC0AE4ULL, 
            0x2B45658C815E2A3AULL, 0xFD2A2B040E83A030ULL, 0x15F851490AB2355FULL, 0x2EC1782B038AEB71ULL, 
            0x3D74C8E7C54B1D0AULL, 0x3113FF9708903101ULL, 0x5E10354F40B611BDULL, 0x3E799A3CDAC95637ULL, 
            0x01B966699BBED254ULL, 0x9EE9ABAD789FE48FULL, 0x71AABABE20EBDE9AULL, 0x5D481D21E161D7E3ULL
        },
        {
            0x6D669FA093B627BFULL, 0xD7D9742810748907ULL, 0x82E337DDD4CB7F24ULL, 0xAC2AE5C4DD34A420ULL, 
            0x24528A1D56E3B1BFULL, 0xC29EB1B189062994ULL, 0xDD0A22018BAE08FBULL, 0xF49D07E0FBA7D12AULL, 
            0x9B17F8D1D696DB6EULL, 0xD2D135B9491A3D4EULL, 0x08D33D04DAEEE120ULL, 0xBB77651CD7F1F148ULL, 
            0x22109B3D8C7692A4ULL, 0x33FDE0E9BD9CBBCAULL, 0x77613B6814F9C773ULL, 0xA4BCDD92939E74E8ULL, 
            0x3651FE7207A05819ULL, 0x26BED9D79AEB5798ULL, 0xEF816966B9C4B25AULL, 0x08F99A43B9D1B679ULL, 
            0xC6D26B80287D0E56ULL, 0x06C860B1899C3B13ULL, 0x82333C0862BF7A08ULL, 0x5E233ABF2A701C55ULL, 
            0x8A719D6F8DC8F73AULL, 0x654C75632AD1E73BULL, 0x01E281DC26EF5EA4ULL, 0x866EA9C377356607ULL, 
            0xE11597D9BB0D96F7ULL, 0x1002B2EF51D9B080ULL, 0x0BFEE0D5373C9ED3ULL, 0xBCD489BE1DDDF095ULL
        }
    },
    {
        {
            0x3C6FFC6C85BAF3B9ULL, 0x5A3BE50841490BB0ULL, 0x45034D4EFE530F7CULL, 0x116B9A0C0995212AULL, 
            0x13650E1B79C74075ULL, 0x0B7A3450576C4DA2ULL, 0xB23B3E31123F192FULL, 0xBC4289376DD319F7ULL, 
            0x2AF20E30FD2D2E69ULL, 0x55F7D46EF48C0500ULL, 0xE71F7A2E1750AF85ULL, 0xF5D6AF6807571891ULL, 
            0x41276B161CC981A3ULL, 0x70EEF07A8E7F5256ULL, 0xD5F15AC843CA2FD0ULL, 0x72859D108A31B90FULL, 
            0x7ED7C4E3C27F404DULL, 0xC33DFA529EBC3987ULL, 0xD416108D8C279FBEULL, 0x570A26FF15F91F14ULL, 
            0xBE467FD6BB67C19AULL, 0x024C97B93B084630ULL, 0xEFF9DD661F724B2CULL, 0x8C4AB5AE8D5627B1ULL, 
            0x4A190AB0EB61ED27ULL, 0x87BB4F7126CB92EEULL, 0x89EB665AC2AE79C8ULL, 0x5C44E01C05DB95B8ULL, 
            0x531ED8DC464C9030ULL, 0x871FF6520C6844CFULL, 0x687FA6B6739CB1E6ULL, 0xE1AFBD503C513B57ULL
        },
        {
            0x9AC4F4A3BA443A3AULL, 0x845E3275A9F16218ULL, 0x61FBE50842B09FEEULL, 0xC42103E8B39CAEC3ULL, 
            0xB0FCE792CC2C65EBULL, 0x4BF4699308DF91D7ULL, 0xC865874EB4A26003ULL, 0x111C70D8801E72A1ULL, 
            0x82C7F698A1CE2F65ULL, 0x7639B1007BF10769ULL, 0xF93DDE0638C5C02CULL, 0x6A3B95A15845CDC5ULL, 
            0xCE4CA73584ED2669ULL, 0x99CF9A53D55EE405ULL, 0x6563BA7375678126ULL, 0x260C580D044B1C59ULL, 
            0x2F90D5CD7EE33CD7ULL, 0xC76AE2D21CFFA85FULL, 0xA02FD00E59C68223ULL, 0x1EE4CA967A09299EULL, 
            0xD22B6669952067BEULL, 0x2CF2484B847D00E6ULL, 0xC3AC87E50F25F92FULL, 0x14B3BFE4BC081912ULL, 
            0x99CFAE1A1D594E8BULL, 0xB597B1AEA776A3D1ULL, 0x6FC6CE1CE903ECC1ULL, 0xFDB5594449D7CD4AULL, 
            0x56DACCC119A705FEULL, 0x09D8B2B499AA7FFAULL, 0x8AF701052A6A62AEULL, 0xA20C479725A7F3DBULL
        },
        {
            0x4E0CF7CFCD82818EULL, 0x2FCE000C71CDA01CULL, 0xD453A09B925755E2ULL, 0x8118E01DEFE26372ULL, 
            0xF61BA14879AF5AEDULL, 0x13E1A0362B543AFCULL, 0x69754CA5B91940EEULL, 0xCC8F99C0A313F2A6ULL, 
            0x7C82ACB00064C5E6ULL, 0xD03CD4A32BC7635FULL, 0x92E7BFB28B795439ULL, 0xD18B6A10B916B54AULL, 
            0x8FEF269F45200F83ULL, 0x3C3F2D09A5850279ULL, 0xF4D6068D399CB080ULL, 0xDF3317AD3A349A17ULL, 
            0xAAD7DC4A95F527B6ULL, 0x63C6380163D8C88DULL, 0xA067FB476564719CULL, 0xACCCD48DA1900CA2ULL, 
            0x37542C80689B1073ULL, 0xFE5B42E79CDB710AULL, 0x47E38E6BC906A9ACULL, 0xD53D7A00CD8DEC06ULL, 
            0xE36649D0A7689641ULL, 0xE0BA1CCCD34839E8ULL, 0x153B943E19DA358AULL, 0x383113A2F97D6AA5ULL, 
            0x9A7E10519043A3EEULL, 0xFD6FDC092F21807CULL, 0x74AD3C7A7BDEC438ULL, 0xA09AE37549293A06ULL
        },
        {
            0x4DD169576EF001A8ULL, 0xE40C57EA46449200ULL, 0x08158124A1556F96ULL, 0xFE0A2DBA6D1B507EULL, 
            0x7F092A27E6283A76ULL, 0xC9D6EE17549E0100ULL, 0x9C25FF0A915C4DE7ULL, 0x5D9AEDA620397E0CULL, 
            0xF210A4BE31DFBCF3ULL, 0x72C53BFDEB533316ULL, 0xB67C13C5F5D8F072ULL, 0x7D231C1C2B93FEB7ULL, 
            0x45941B82D8738F99ULL, 0x380E1950A44B4B7DULL, 0x444782BD858119F3ULL, 0x38EBE2E579CDAF4AULL, 
            0x3AC414A4A2A7FF1AULL, 0x99D2DA0001139CE2ULL, 0x0BEF19885BC2CD81ULL, 0x6C250246BA27F2CAULL, 
            0x6283D5D07E643D14ULL, 0x7F384A6A35777E49ULL, 0x9162C4530C2AA36AULL, 0x88FADF1332A0D4B0ULL, 
            0xA431A62E87D51C1AULL, 0xDCB3D2D30FBB15ADULL, 0xAC80637E2F961BDBULL, 0xA26323553804BC6FULL, 
            0x68E9D6C01A65C3BAULL, 0xD698DEA7DB3C2B0CULL, 0xC4AF1B74B923AAF1ULL, 0x6CB92E67E2DBAEA6ULL
        },
        {
            0xD03F7FBDE72A663CULL, 0xF2F5F92EE003CC19ULL, 0xFE9CF0BD89161F9CULL, 0x937879C6C558A5F4ULL, 
            0x0DE6BC1167E85481ULL, 0xB58CC21049E17167ULL, 0x64B166D7D25C115CULL, 0xF3D514D56173AEB0ULL, 
            0x64A5C5694527D57EULL, 0x6B1419EE58630804ULL, 0x69D66D2BD11C1940ULL, 0x55DFAD77610DDA1DULL, 
            0x379173E8B275A4FAULL, 0x892EA53A58B6C0ECULL, 0x711FAEF349CA487CULL, 0x8345053C5090D123ULL, 
            0xE1E52A508F14B2EFULL, 0xDEDBEBE35BB77600ULL, 0x7178EB785AC68A2AULL, 0xCE8A3DC9303C1633ULL, 
            0xFF247E28252F2BECULL, 0x8BED53F08D1BE38AULL, 0x4E91DF6E4C53D0AAULL, 0xF7238DA1E616E1EEULL, 
            0xBC8155B73ECD6FF3ULL, 0x684DF7A1EB1D0EB2ULL, 0xF6F0A1197133BFA3ULL, 0x93FB95A6246D2A61ULL, 
            0xB6E6C8287C6B6841ULL, 0x9C25D855AABE746AULL, 0x66FB6FAA9A8BDDA1ULL, 0x7EE55A61257CEA14ULL
        },
        {
            0x5D9F49486E7B3260ULL, 0xAC025B9640B1402CULL, 0x238C2DFF8D36C4E8ULL, 0xDB5A59EFB73AB717ULL, 
            0x0CF86B0431E695A2ULL, 0x997DB8F4218F6EF3ULL, 0x2F3103AA6590BBA0ULL, 0xD6006C0C431C28DBULL, 
            0x5C7CAD31BB144B71ULL, 0xA1B789904F81D478ULL, 0xD68495498E0BF3B9ULL, 0x2662358E0D5A037FULL, 
            0x80B4EE09B04C5C12ULL, 0x9942E7484AD6C883ULL, 0xD8D97A5EACBAB65FULL, 0x2093010458E6CAF4ULL, 
            0xBA65879DCCE0F2FEULL, 0x3616737E61E932C3ULL, 0x0B27F39A5F6A4278ULL, 0x2BE65050D0739350ULL, 
            0x20A892D728078A00ULL, 0xEB8BA2DFFA7F1262ULL, 0x4F662B7B65B7B7B3ULL, 0x8FC072E628C2FA0BULL, 
            0x9AE75BD37F739FB1ULL, 0x8BF2BACEA58EB9F2ULL, 0xB9B40E8D8E872C3FULL, 0xF3FA60B882F9A35CULL, 
            0xC3E87214B7F48230ULL, 0xFFE4DCCE2DB96080ULL, 0x32F90BCB006253FBULL, 0x6D924BD534DD908BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseGConstants = {
    0x060BE761FC4D1B70ULL,
    0x05AC37B84DFAECE8ULL,
    0xE0D0AC94FD324A87ULL,
    0x060BE761FC4D1B70ULL,
    0x05AC37B84DFAECE8ULL,
    0xE0D0AC94FD324A87ULL,
    0x147EF10ED4EDFC29ULL,
    0x809E5B8B74F4A193ULL,
    0x76,
    0xE9,
    0x74,
    0x12,
    0xCA,
    0x4F,
    0x3F,
    0x5C
};

const TwistDomainSaltSet TwistExpander_Vega::kPhaseHSalts = {
    {
        {
            0x1706AFB2F91D0577ULL, 0xC23AAF8D5823B999ULL, 0x74C5054C7BB3E37DULL, 0x5E66328834B692D9ULL, 
            0x8470CE95216EFEABULL, 0x041A2F1707AD23F1ULL, 0xB2342B8459F3999DULL, 0xAA59F21776861230ULL, 
            0x6B9DBA3CBCF7EB07ULL, 0xC4DFE6FB1A150CD9ULL, 0xCF5CE61EB73D5D8BULL, 0xFA0C2E67E1ED0E44ULL, 
            0x5CE05E88BBC29075ULL, 0xFA3272F90C958FADULL, 0x88CFD1053CE9A56EULL, 0x74158C04BC30E270ULL, 
            0xA7DB2AE8AC061113ULL, 0xE23564C059CCBBB9ULL, 0xFA20DD1D100157ACULL, 0x8C6108A92C903E82ULL, 
            0xB934F5C5863927F7ULL, 0xE1EFBF6EA9E194ACULL, 0x6A9FB3769D9AD5CCULL, 0x0C4FB00E3B9591DAULL, 
            0x36279840CDEC01FAULL, 0x44E3073D147CB47CULL, 0xB035E0BFADA6A43EULL, 0xAF3C0804A0396D5EULL, 
            0xE8666AB3DCECE934ULL, 0xFAD1425B724687A0ULL, 0x6ABD3397A34AB52EULL, 0x3BF747809B3DD226ULL
        },
        {
            0xC760DEDEC74A8624ULL, 0x1E3131E485B4C470ULL, 0x1054DE592ADB0925ULL, 0xFAC7AC53056032AAULL, 
            0xDC39F3A8F7207F8DULL, 0xEA7B1E16EEF3686CULL, 0xEBD3585EF97DF135ULL, 0x30C5ED1A17928B47ULL, 
            0x26DF958A1629DCB6ULL, 0x300D419A08AF52BEULL, 0x13CE511AB259D7A0ULL, 0x849B2E4668322280ULL, 
            0x8AD26A011D4B8DA8ULL, 0x239C84119AEA66B7ULL, 0x3B4ED018E5A7A3CEULL, 0x317A37476689288EULL, 
            0x7E52F56D2EC2C585ULL, 0x996A671DD5CB4466ULL, 0x9281723F489968A7ULL, 0x70DA45EDE398E3F0ULL, 
            0xF84CB099ACF80CA9ULL, 0xFFE1FBC2C2797A89ULL, 0x3CF23C8629736CAFULL, 0x7F647AF54261A501ULL, 
            0x874ED8C9282B3655ULL, 0xC2F27C9F8E9B9354ULL, 0x2A2F37245E30FBCAULL, 0x9DC2191E605A8E34ULL, 
            0x92940D604550CFF0ULL, 0xEF00042CFC3FF7FFULL, 0x63A4AB55F2B384C8ULL, 0x9C9C7CEBE186E152ULL
        },
        {
            0xC5056E96C834EC2AULL, 0x2F8BB17EA6869022ULL, 0xCE5D282BE87E299BULL, 0x7A469723D517417FULL, 
            0x63E92480374383D1ULL, 0xC8BA5C1EE0DE3FFDULL, 0xFD12332A118A085FULL, 0x3536968E4655D1EEULL, 
            0x9796604BD7BD69A8ULL, 0xE8B8AB19A297F2EEULL, 0x9597260A26FFFEE0ULL, 0xB56FADBBFD835399ULL, 
            0xBD89A9563A1187C8ULL, 0x23AD0EEC68E6D6D6ULL, 0xAAE735ACD0CAEE82ULL, 0x5ABDD56F0AD6FA0AULL, 
            0xA4B5B58B937E6A87ULL, 0x8AE21FBE70450A32ULL, 0x8CD33D0A6AF87F1DULL, 0xB21FF1B8BB1BCA93ULL, 
            0x9966EE14D4FDB48EULL, 0xAC6588C9CB85CED2ULL, 0x9476F5E950C4B943ULL, 0x34B6DAB6E2FDB442ULL, 
            0x476CE749796A81AFULL, 0x2B26BD723881B22AULL, 0xB07A666E768ED889ULL, 0xE3AC965532BE15B4ULL, 
            0x456B5CBBD99C1D5DULL, 0x89C4D81A3C138DAEULL, 0x371A446C61ECF41AULL, 0x3816EB1BBA322725ULL
        },
        {
            0xF75E24D56E61C46CULL, 0x6A4C9E651A9BCC4DULL, 0xB133B4250B846D1CULL, 0xA45E0A05925D4182ULL, 
            0x1404EF4A58E0BC9EULL, 0xF1643E76E807FB6AULL, 0xFF0CADBDDF6DA8AAULL, 0xC478DAA6604296AAULL, 
            0x6DC6C859AADC8B52ULL, 0x8EED02EA6907A19DULL, 0x8E52112F76ABC4B1ULL, 0x5B1156BBC79CD6E0ULL, 
            0xEB94E1009EAB6F6CULL, 0x24AF96C2E0D84470ULL, 0x8B5D9DF20D952469ULL, 0x45003388FCE92435ULL, 
            0x39CE81998D34BC22ULL, 0x50E388A0D6A50A78ULL, 0x1B9EBEB5737D621BULL, 0x96401D3649A795C8ULL, 
            0x63E3A73CFB87330EULL, 0x09B46CD7D579BA65ULL, 0xAA96E3F768ED95BAULL, 0x9F454CA48314ADA3ULL, 
            0x8C306145918BA621ULL, 0xA062C667AA1840D9ULL, 0xA5603F1D7805D622ULL, 0x8824B3DB0B36EF4EULL, 
            0xAEC8F3DFC213C448ULL, 0xF8EF02DDA5FD7585ULL, 0x11BC88C87E434D17ULL, 0xA750A225E4EF9CA0ULL
        },
        {
            0xCB7BEAE5094CA659ULL, 0x8E7461FE04CE8740ULL, 0xCD4642E62DC16244ULL, 0xDD24D1EF95E3EBFDULL, 
            0x5046C242AC801506ULL, 0xCB13F0094C5D9E4CULL, 0x406BB6547CB19A8BULL, 0x0862980C8B4D21B1ULL, 
            0x8C02816573AB0942ULL, 0x0A37A013674534BFULL, 0xEE405615CAA5E930ULL, 0x034E9BAE72D2C5B3ULL, 
            0xF6161270674C3259ULL, 0xFA5C754D6500CF30ULL, 0x4B53CAD64B13CCA1ULL, 0x4D5ACDCC74530C23ULL, 
            0x46975DFE264D195DULL, 0x260576FA8CBD10A6ULL, 0xE05D19A353C607BCULL, 0x08BD0B62435C272DULL, 
            0x10FBD9E7A5CC8E42ULL, 0x3B8D041865F3B7E9ULL, 0x0158076EF3D9C8B6ULL, 0xB65400DDB6E7BFE2ULL, 
            0x8102AA7210A2362EULL, 0xE178F700C360AD71ULL, 0x2318FAC87CD57DC9ULL, 0x420B27345C7DC18DULL, 
            0x427231C62E2AC52EULL, 0xCD78DCFE30B0B658ULL, 0x87DD93BF0350A037ULL, 0x6875CBBB72DF0550ULL
        },
        {
            0xC08C63430B9E4DBAULL, 0x3B4F830C444C37C5ULL, 0x0E648CAAB931144AULL, 0x11323276F617E127ULL, 
            0xE7D4FC8A4AEA88F8ULL, 0xCB798D03B615839DULL, 0x62E84D9FDFD68C93ULL, 0x6633989EA0B9DB95ULL, 
            0x605333DC17638CEDULL, 0xEB6AFA3AA3F33564ULL, 0xD23AA40283CCE389ULL, 0xC8A239C39719B3ADULL, 
            0xB37BE0E6E653BE50ULL, 0x7C697EB333D5052CULL, 0x531EDF7AF5C2A6C1ULL, 0xD7639A91AA571F53ULL, 
            0x1FC258CCFA54B614ULL, 0x00A0BDA1DE7B53D5ULL, 0x8AEA9194BB53AEE5ULL, 0x99C2E9C9A0B05DF2ULL, 
            0xE5DBB8A19383CFCBULL, 0x444BA61CA1043382ULL, 0x2BE245D939FB7547ULL, 0x1D1B279F38240CBAULL, 
            0xFBA2E0813CF11715ULL, 0x5733E7E170029268ULL, 0x79617F2E5AF1672BULL, 0x4BE23A3D93E2CE62ULL, 
            0xF4F7C20D6E1C5445ULL, 0x6373485A1D56E1D2ULL, 0xA3D28869D07E66E1ULL, 0x130998F98C92499AULL
        }
    },
    {
        {
            0x6E370FD273A633B3ULL, 0xD767C2E8D5FAB8E1ULL, 0x8BF641CC6E5B83F9ULL, 0xA10FC93C59A93B45ULL, 
            0xED12F1BD848CC76BULL, 0x489E3F8ACD2E0BC5ULL, 0xB1C35A28D4CB8396ULL, 0x0A3E7AAAF3BA4AA4ULL, 
            0x1C660F72B93C81CDULL, 0x4268C0259068E17EULL, 0xE7E7BE291B7A42FFULL, 0x6C3DE8D452AA7D61ULL, 
            0x63B5225075BF33ABULL, 0xA33EB19979E69BFAULL, 0xC322257D5A1E244DULL, 0x7F3BF5BB61D55A64ULL, 
            0x991604BD1912BF12ULL, 0xF93A26D03D014228ULL, 0xF6E812D43FB57008ULL, 0xDFEC0297F0A6BDF5ULL, 
            0x6ABED97720BDE899ULL, 0x8CE5A2A0A78C2334ULL, 0xE9BF46C686F8BD93ULL, 0x69389FD8044EC8FAULL, 
            0x2267720E6A369322ULL, 0xF75EF970DB44E74FULL, 0xD5F1350AD0054B48ULL, 0x1D2F81BEA1F2B9C4ULL, 
            0x93FAAFD2D60E7C09ULL, 0x94C7CF5465135735ULL, 0x232A7950EBA5D850ULL, 0x9AD12B20DC36240EULL
        },
        {
            0xC7ACB40AEC4BEE53ULL, 0xD81512C79F847E7FULL, 0x93D9D83F341E6DD3ULL, 0x6D6ACF692E032B92ULL, 
            0xA306B319FA8E4F99ULL, 0x197659C9592AE06FULL, 0x0714EA90C2827DE8ULL, 0x19A064183B4CF3E2ULL, 
            0x5AF6B8D8B921ECD5ULL, 0xAD6CFCBA39EA4D4EULL, 0x8CA54F61959778BCULL, 0x948D0EF2D08C7A0FULL, 
            0x42B5D2B6254B4F69ULL, 0xA18C461D5CC3F9E2ULL, 0x747F64687CD63569ULL, 0x150FE3A70E9ADCF3ULL, 
            0xBD5AE2E3CCDAB213ULL, 0x9D1C85D8CD78E19BULL, 0x3A968FDCCE7D0F37ULL, 0x71C58BCD3E2E381BULL, 
            0xBEDA709B5728D5F6ULL, 0x5752D49F1FE6FC12ULL, 0x6787DBB65BE1EE97ULL, 0x8EC505CDF7B94462ULL, 
            0x398DC3C39D30A8F8ULL, 0x7B16D3C136A6A7ABULL, 0xA67A88A9819BC261ULL, 0xE80288A90DB4D442ULL, 
            0x3FF725782E6D1DD4ULL, 0xA1D457088BD8DDB4ULL, 0x3E90CA031D2FC3E8ULL, 0x75FDEE4867E031AAULL
        },
        {
            0x003F5A51CDE09C5AULL, 0x13FED96BB0D9E70EULL, 0x0A7D057795B8BAF3ULL, 0xDE6F6DFACF85E584ULL, 
            0xEF03EDA59FD70F09ULL, 0x2CEB0DF07921C8AFULL, 0x59DE84D1CAE2FEB7ULL, 0x37242683727CB60FULL, 
            0xEFF89F3E65731960ULL, 0xA4294249846F4BF0ULL, 0x56D57353A487933FULL, 0x0AF09F6E0B9D17DAULL, 
            0xD74BA3CDF157253EULL, 0x2B650254DC88DDB2ULL, 0x9C8E2AEB756A381CULL, 0x732C393AD498A968ULL, 
            0xF75B1DF7EF0E0675ULL, 0x7071309410ECD610ULL, 0x713BD1910960318FULL, 0x1169CF8A7CF1CFD7ULL, 
            0xE970D97896603CEFULL, 0x65F5033A7F158466ULL, 0xD370B43216D1E10DULL, 0x3D6C2F99ED53BC4AULL, 
            0x415E35237D409D88ULL, 0x1D5366E3EDF1EA21ULL, 0x93A6314B6328EA3DULL, 0xB22AC5FFE2E889C2ULL, 
            0x2BC500DDC044C3A5ULL, 0x68422BF69B23A9A7ULL, 0x2F5D8D33ED05ABE4ULL, 0x4D64B756255F2936ULL
        },
        {
            0xDF1D0130F55357C7ULL, 0x1CDB14EABFDD3AFDULL, 0xD263AF1C08B9F765ULL, 0x287D167C61B9CEE0ULL, 
            0x494BA0C6D007F3A8ULL, 0x973A5935751202CCULL, 0x49B49BCBAAC944E4ULL, 0xD29CF784078C690CULL, 
            0xCD8F7C121B086215ULL, 0x7F3435D6009999ABULL, 0x695FA7C5BA3E2F92ULL, 0xC4D6A80E7BDA3D24ULL, 
            0xAAAE626E56C195B9ULL, 0xF557AD1BA65F87BBULL, 0x5397939EDD1AC674ULL, 0xA8D489F1C1D7CF14ULL, 
            0x49FA599B5920B492ULL, 0xBA2687C5ED123B12ULL, 0x0852C226992F75CCULL, 0x9FA81AC01F4B00F0ULL, 
            0xCA62D0B2BC20277DULL, 0x5FD75574AE1880B1ULL, 0x309D6D117DD0D2C6ULL, 0x856BAE1B4DBC995EULL, 
            0x5ABCB9B7EA8347B2ULL, 0xAC2012FF4A23B3F0ULL, 0x883B8C168DB30EA9ULL, 0x3D7F33EA16E94E1FULL, 
            0x4AAA7117371C2C0DULL, 0x52632F4B049A1D85ULL, 0x97DD06AFDB43EF37ULL, 0x0B308E37C90D2464ULL
        },
        {
            0x3517870BEC625FF7ULL, 0xCA4918EF850F271DULL, 0x33D9C6FB52B3D792ULL, 0x29AED9E15981ED43ULL, 
            0x6C835DFEE9313CEFULL, 0xCE517F6699E11ED8ULL, 0xEEAF4893DBCD2C28ULL, 0x13AE72C4705567BFULL, 
            0x5313BC9DE33B54B2ULL, 0x9858821E4B88B645ULL, 0xCC3036A59B9D34D2ULL, 0x7872BD59A4315292ULL, 
            0xE4B2EC240762BE7DULL, 0x5281A2CE2DEA6E7BULL, 0xF16789E2E17EA0B3ULL, 0x3E5B814EC0727447ULL, 
            0xD8AA8CFDF4264577ULL, 0xC0208F539C47AFF8ULL, 0x6F04A6C16BA8ABDEULL, 0xC396396AC795586FULL, 
            0x30E9CD1148852ED2ULL, 0x346EEB6D8D883625ULL, 0xA71BA7C29C016533ULL, 0xC4FFA69706D5A119ULL, 
            0xDEA358AE90D791F6ULL, 0x29D8CEC24A18BB3EULL, 0xFD7431FF877FC430ULL, 0x61FC6BC8BB60CF47ULL, 
            0x941B591FC2CE7B57ULL, 0xD426F26BC8836E0AULL, 0x0CEBEFF558DB10C3ULL, 0xFE569011748CC72BULL
        },
        {
            0x5085762490613804ULL, 0x6013BDDA4796E686ULL, 0x81773C50E3400DEFULL, 0x3CFF51971ED00A2CULL, 
            0xF46393EFB9D002E9ULL, 0x6411211036F2C53EULL, 0xA4D056AC67460F71ULL, 0xA6868D33C1FE7D69ULL, 
            0xF9C070CE82D2257BULL, 0x7385FFCFD69312E7ULL, 0x1089FAC1EEEDEB0EULL, 0x203D07783BF53FB7ULL, 
            0x5E42FBA494863AD8ULL, 0xEF8EB80501E77B9EULL, 0xC112362BFD1140BCULL, 0xD8A59B3ED2D12D75ULL, 
            0x67FB6FC0EA341C1DULL, 0x0939019BFD9BE25FULL, 0x0199DA32863196E8ULL, 0xE1914AD98515633FULL, 
            0x8C94E6CEDF1A8BC5ULL, 0x24B2AFAAA5B9DE26ULL, 0x90A309174E58AD4BULL, 0x30CBAE5E29CE26F8ULL, 
            0x60F3C4D05434119DULL, 0x69BCF30CD5DCAB43ULL, 0xCA3743CEEF346C3DULL, 0x0FC4C9A2141CC2B8ULL, 
            0x538B27461EDCEF9FULL, 0x86AC38996B17C1B4ULL, 0xDEFC5147B03CCE05ULL, 0x283AB430B98B8F7CULL
        }
    },
    {
        {
            0x7509FC899184DA9FULL, 0xA23BAEA86D510031ULL, 0x3DA2D3E339A52606ULL, 0x849BEC447F14A183ULL, 
            0xC55BF4DBC7A771F3ULL, 0x9ED6EF2EC315F38AULL, 0xBC51435B787790D5ULL, 0x890EDF358BBB2A93ULL, 
            0x06568A59E5A2A38BULL, 0x70A2EBF068BDCE90ULL, 0x596C3869A30A1BEFULL, 0xEDD7635ABC758663ULL, 
            0x41EEA8DFE19064F3ULL, 0x767ECFB7E7893B11ULL, 0xE6D89FE5445737A9ULL, 0xB136908A06BC81D6ULL, 
            0x2512A3245EF9EE13ULL, 0xBE3BF2108182B47BULL, 0x4BD9F1B2AD097FA4ULL, 0x6C8134730C0EE2F5ULL, 
            0x9D94997D22431A9BULL, 0xFF10A2F3282FB26DULL, 0xB508A252F778ECB4ULL, 0x43F06A6A58B8A1BAULL, 
            0xA1CA7574156C7E1BULL, 0x82F00C0B9720100CULL, 0x7B0F63C42C9BDC1DULL, 0x7E464270171103FFULL, 
            0x1AE46182D013D348ULL, 0x1CFD606627B0FBC2ULL, 0x697C18F374951446ULL, 0xEBF30EE7B65EF1E8ULL
        },
        {
            0x309D738CC0E05D59ULL, 0x2501C18ADF41B784ULL, 0xB10B3DA4EB3717C2ULL, 0x5E25023DD6D0E812ULL, 
            0xAD330E38DAB0D9B2ULL, 0x8637878961DAA9A0ULL, 0x7D9DC4A7CBBA403DULL, 0x77D952C470936F9AULL, 
            0x78FCDAAB8012E5EEULL, 0x07F326180E7F92A7ULL, 0x28249B8E9D248C55ULL, 0x89EEFF58751005D3ULL, 
            0xF68A4185635E19EFULL, 0x8E739C105A12391FULL, 0xE6787E21FE521E03ULL, 0xF06C0BA0C04D33DCULL, 
            0xA27F278AF0FF750CULL, 0x6F37BF8AE4801CB3ULL, 0xFA9A48BF1BB64C28ULL, 0xCA3471E14913B46BULL, 
            0xF855D9501F13A7EFULL, 0x1A6099016AE8E084ULL, 0x13A96CC7BFC9B58DULL, 0x94B5810E1BA23F06ULL, 
            0xCCA729E6883F9117ULL, 0x3B9FEAA5CF04CD4BULL, 0x3381302E65FEC248ULL, 0x3D78B0766D170A52ULL, 
            0xBB3C594E974B7809ULL, 0x686074CE783B9382ULL, 0xC15B96B80C4AF191ULL, 0x2A70024C7630D5E7ULL
        },
        {
            0x6BB5B262C78F98B7ULL, 0x4CAF516393A87931ULL, 0x7B39679726B2037DULL, 0xD6DCC30CFB6E05F8ULL, 
            0xE126407B7A7F56DFULL, 0x8E5AF2F845A17259ULL, 0xEAB9F8449290363BULL, 0x10A2D4B291A0E72DULL, 
            0x60A7E079B9084E1EULL, 0x8D06B72D73829B81ULL, 0x2339E60843127F07ULL, 0xB30B35EB360C017EULL, 
            0x23AF4AC15E71D6A8ULL, 0x8F23A6CC7A58F01CULL, 0xD97620FA02597FCBULL, 0x457C6061C0373F74ULL, 
            0x8846781A447B916BULL, 0x4344B8870B9CBFF3ULL, 0x4546FD7CAF8A4F76ULL, 0x473EA7834C4CBF97ULL, 
            0x3AA4F2DDFD781F62ULL, 0x6C78B59F07107A8CULL, 0xEBE86227B31A21AEULL, 0x989DDD1148FA3161ULL, 
            0xD6B51BF46480A693ULL, 0xB87952A07D603B11ULL, 0x2C74804C95A83FA9ULL, 0x9E0A398BD4689A1BULL, 
            0x32C64E6E9BC12FA5ULL, 0x023C31C2649BFA6FULL, 0x47005997A757C1A7ULL, 0x8B6F43ACEFE75C54ULL
        },
        {
            0x1DCFBDE86D4875D8ULL, 0xB0B745C307CC6941ULL, 0xC0C35BF67B19B3F0ULL, 0x605A2985DD69C6FBULL, 
            0x5BBC0F4910BD3839ULL, 0x3C62D5FCC0030C5BULL, 0x8674EB5F0CC6A33BULL, 0xC0F29794AF18318DULL, 
            0x04DBD78981B6A21DULL, 0xE5565DAE539E6178ULL, 0x36E48E8BC4AB864FULL, 0x3F55881D3560F0ECULL, 
            0x628C229D06EDA145ULL, 0xD06B602149385E87ULL, 0x01F8A31948100582ULL, 0xCD4E378BFA70E55FULL, 
            0xE8845B31A0F99BF8ULL, 0x9095A65C80F9EE04ULL, 0x5F050A3366886113ULL, 0xBFEC23E59CFD9F87ULL, 
            0xD0590F55651166DBULL, 0x7E5FCCD0F0D5864CULL, 0xD67C64BBA14FE25AULL, 0xD02AD071B5C6E204ULL, 
            0xD9C7A6CF7C70A87DULL, 0x206E652C0DA1EC79ULL, 0x54C034A33BC49B2FULL, 0x9061DBDBB6F47AC0ULL, 
            0x2967D2EA9E99C61EULL, 0x35921B7444732A4EULL, 0xA11CBE607AD673CAULL, 0xBC32709C6FB53CE8ULL
        },
        {
            0xC78822CE3F4696DBULL, 0xFB521CB720ABA5BFULL, 0x9D6E093C42CE2C42ULL, 0x0E4F0AB93B821631ULL, 
            0xA72343AE7B1BFF49ULL, 0xA5C4336C39EF3C55ULL, 0x42ACECAA53E72C54ULL, 0x7D2B0C5923CF5D08ULL, 
            0x8D63D5FCA3EB83EAULL, 0x3F5D07A2AB65C180ULL, 0x5FE2750253620C44ULL, 0x8160EEB7574D9201ULL, 
            0x8F5E6A09E38F895FULL, 0x095266CC89D1EE9DULL, 0x833FC0201033DD0DULL, 0x178E7316E67E32F9ULL, 
            0xF9F1B2533F8C55F4ULL, 0x2DE37F0E39D84764ULL, 0x47DBCB9764F02EBDULL, 0x0E9158A11F6220EDULL, 
            0x21ECFD35B8FBD644ULL, 0x6AAF46FBFA43B5E9ULL, 0x40E9C145E60B15ECULL, 0x4AA9F4F5A62227CEULL, 
            0xF887455655F48FA7ULL, 0xE4B91787FD782837ULL, 0x686FA14379A13112ULL, 0xEDFDB7E3AF2AE32BULL, 
            0xD5EEAAB2B89E4D46ULL, 0xA3A1D02F325647CFULL, 0x538A54B954351BFBULL, 0xAA8DA3D10D61052AULL
        },
        {
            0xB98FC08AA6A471A1ULL, 0xA2B7B15EDB6D5314ULL, 0x07248EDBD493501EULL, 0xE09D6742695200FEULL, 
            0xAEA7F0061F0C1C6EULL, 0x65540B7A44179A0FULL, 0x5CA48801AC512783ULL, 0xCFC43060AF3BBFADULL, 
            0xFD911F7E07E5AB7CULL, 0xE34EA4C6D79D4DA3ULL, 0xC93BC356D55F077BULL, 0xFB113602E3552386ULL, 
            0x7AB975DA7D4133D7ULL, 0x69F87C76868923FDULL, 0xFA9626B04C89DC0CULL, 0x83FFA25A55AFC804ULL, 
            0xB52C4D17EAAFD09AULL, 0xFB0261AAAA53B973ULL, 0x9E82715385E9FF54ULL, 0x466A144241E5A968ULL, 
            0xE3448AD8A60490F4ULL, 0x2CBBC66A2EB129A5ULL, 0x471AA36AFDEE8511ULL, 0xB80D5EE1F62C1A1EULL, 
            0x3BD2BB39575E9004ULL, 0xE783AA5B048BDA46ULL, 0xB08E9C2B4EBCABBDULL, 0x12FCBA966B48FA55ULL, 
            0x053CBCC5462EE0C8ULL, 0x87FB80A9128ABF39ULL, 0xF1BC77D7ECE17D7AULL, 0x8F4A6095CE36CBB0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Vega::kPhaseHConstants = {
    0xECCD01F530E37F7FULL,
    0x996852AC36A72DE3ULL,
    0xD1DDF199A2DF7B10ULL,
    0xECCD01F530E37F7FULL,
    0x996852AC36A72DE3ULL,
    0xD1DDF199A2DF7B10ULL,
    0xF23EAFD87AA02583ULL,
    0x2F1D94ADFC1EBCBEULL,
    0x60,
    0xCC,
    0x01,
    0x0C,
    0x82,
    0x29,
    0x8F,
    0x9A
};

